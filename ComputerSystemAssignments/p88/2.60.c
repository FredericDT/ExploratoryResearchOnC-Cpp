unsigned replace_byte(unsigned x, int i, unsigned char b) {
        *((unsigned char *) &x + 4 - i) = b;
        return x;
}
