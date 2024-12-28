template <typename T>
T xfade(T a, T b, float blend) {
    return static_cast<T>(a + (static_cast<int64_t>(b)-a)*blend);
}