double randomDouble(double minf, double maxf) {
    // use 1ULL<<63 for max double values)
    return minf + random(1UL << 31) * (maxf - minf) / (1UL << 31);
}
