#ifndef DSP_DDS_CORE_H_
#define DSP_DDS_CORE_H_

class DDSCore {
    public:
        DDSCore() {}
        ~DDSCore() {}

        uint32_t acc, pha;
        bool overflow;

        inline void update();
        void reset(uint32_t new_acc);
        inline uint32_t get_acc();
    
    private:
        uint32_t shifted_acc_;
        uint32_t previous_shifted_acc_;
        uint32_t shift_amount_;
};

#endif  // DSP_DDS_CORE_H_