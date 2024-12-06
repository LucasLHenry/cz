from enum import Enum, auto
import numpy as np
import os

TABLE_NUM_BITS = 12
TABLE_LEN = 2 ** TABLE_NUM_BITS
SAMPLE_FREQ = 48000
PATH_TO_TABLES = "/tables/"
FILE_NAME = "waves.h"


file_header = """// autogenerated by scripts/generate_waves.py
// do not modify!!
#include<stdint.h>
#ifndef TABLES_WAVES_H_
#define TABLES_WAVES_H_
"""

array_footer = "};\n"
file_footer = "#endif  // TABLES_WAVES_H_"

class OutputType(Enum):
    INT32 = auto()
    UINT32 = auto()
    FLOAT = auto()
    UFLOAT = auto()
    
c_type_names = {
    OutputType.INT32  : "int32_t" ,
    OutputType.UINT32 : "uint32_t",
    OutputType.FLOAT  : "float"   ,
    OutputType.UFLOAT : "float"   , 
}

def main():
    saw = generate_saw()
    sine = generate_sine()
    tri = generate_tri()

    downshift = 32 - TABLE_NUM_BITS
    hz_phasor = int(2**32 / SAMPLE_FREQ)
    
    file_path = f"{os.getcwd()}{PATH_TO_TABLES}{FILE_NAME}"
    output_type = OutputType.INT32
    with open(file_path, 'w') as f:
        f.write(file_header)
        f.write(f"const uint32_t k_wave_table_len = {TABLE_LEN};\n")
        f.write(f"const uint32_t k_dds_downshift = {downshift};\n")
        f.write(f"const uint32_t k_hz_phasor = {hz_phasor};\n")
        write_table(f, "sine_table", sine, output_type)
        write_table(f, "saw_table", saw, output_type)
        write_table(f, "tri_table", tri, output_type)
        f.write(file_footer)
        
    
    
def write_table(f, table_name: str, table: list[float], datatype: OutputType):
    typename = c_type_names[datatype]
    f.write(f"const {typename} {table_name}[{TABLE_LEN}] = {{\n")
    for i in range(TABLE_LEN):
        match datatype:
            case OutputType.FLOAT:
                val = table[i]
            case OutputType.UFLOAT:
                val = (table[i] + 1) / 2
            case OutputType.INT32:
                val = int(table[i] * 2**31)
                if val == 2**31: val -= 1
            case OutputType.UINT32:
                val = int((table[i] + 1) * 2**31)
        arr_write_item(f, i, val, 32, TABLE_LEN)
    f.write(array_footer)
    
def arr_write_item(f, idx, val_to_write, vals_per_line, arr_len):
    if isinstance(val_to_write, float):
        val_to_write = f"{val_to_write:E}"
    if idx != arr_len-1:
        f.write(f"{val_to_write}, ")
    else:
        f.write(f"{val_to_write}")
    
    if (idx + 1) % vals_per_line == 0:
        f.write("\n")
    
def generate_saw() -> list[float]:
    arr = []
    for i in range(TABLE_LEN):
        val = 2 * i / TABLE_LEN
        if i < TABLE_LEN/2:
            arr.append(val)
        else:
            arr.append(val - 2)
    return arr

def generate_sine() -> list[float]:
    arr = []
    for i in range(TABLE_LEN):
        val = np.sin(2*np.pi*i/TABLE_LEN)
        arr.append(val)
    return arr

def generate_tri() -> list[float]:
    arr = []
    for i in range(TABLE_LEN):
        val = 4 * i / TABLE_LEN
        if i < TABLE_LEN/4:
            arr.append(val)
        elif i >= TABLE_LEN/4 and i < 3*TABLE_LEN/4:
            arr.append(2-val)
        else:
            arr.append(val-4)
    return arr

if __name__ == "__main__":
    main()