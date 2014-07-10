linzerschnitte-rds-bitmaps
==============================

**Steel** listens for frame data according to the Bitmap Frame Protocol on a local UDP port and issues commands with this data. A row of bitmap data is marked with the command number 20, 21, 22 or 23 (for rows 1, 2, 3 or 4 respectively).

**Flint** is a test program that generates some patterns and sends them to Steel; its primary purpose is debugging.

## Bitmap Frame Protocol

    FRAMEID=uint32_t\0
    TIMESTAMP=uint32_t\0 (Linux EPOC time with fractional seconds)
    DATA01=uint32_t\0
    DATA02=uint32_t\0
    DATA03=uint32_t\0
    DATA04=uint32_t\0

The DATA0X fields are interpreted as bitmasks, e.g. 0x00000080 == 00000000 00000000 00000000 10000000 means that only pixel nr 24 in this row is on.
