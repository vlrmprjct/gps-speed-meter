void printDigit(int v, bool comma) {

    int ones, tens, hundreds;

    if (v < -999 || v > 999)
        return;

    ones = v % 10;
    v = v / 10;
    tens = v % 10;
    v = v / 10;
    hundreds = v;

    (hundreds == 0)
        ? lc.setChar(0, 0, ' ', false)
        : lc.setDigit(0, 0, (byte)hundreds, false);
    (tens == 0 && hundreds == 0)
        ? lc.setChar(0, 1, ' ', false)
        : lc.setDigit(0, 1, (byte)tens, false);

    lc.setDigit(0, 2, (byte)ones, comma);
}
