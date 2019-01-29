# Questions

## What's `stdint.h`?

stdint.h is the header file in the C standard library. It defines type aliases with specific width requirements, and also macros.

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

These types allow access to signed/unsigned ints of exactly n bits. Signed allow negative values using 2's.

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

1, 4, 4, 2

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

BM

## What's the difference between `bfSize` and `biSize`?

bfSize is the size in bytes of the bitmap file. biSize is the number of bytes required by the structure.

## What does it mean if `biHeight` is negative?

The bitmap is top down, with it's origin in the upper left corner.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

biBitCount

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

If the file specified doesn't exist for fopen, or cannot be opened.

## Why is the third argument to `fread` always `1` in our code?

As it only reads one element of data in the file at a time

## What value does line 65 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

1

## What does `fseek` do?

Set the position in a file (stream), for a given offset, from a location (whence)

## What is `SEEK_CUR`?

Current position of the pointer

## Whodunit?

It was Professor Plum, with the candlestick, in the Library.
