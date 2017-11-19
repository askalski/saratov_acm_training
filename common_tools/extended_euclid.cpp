int ext_euclid(int a, int b, int &x, int &y) {
    assert(a >= b);

    const int r = a % b;
    const int m = a / b;
    if(r != 0) {
        int tx, ty;
        int res = ext_euclid(b, r, tx, ty);
        //r = a - (a/b)*b = a - mb
        //res = tx*a + ty*b
        x = ty;
        y = tx + ty*(-1)*m;
        return res;
    } else {
        //r == 0 => nwd = b.
        x = 0;
        y = 1;
        return b;
    }
}
