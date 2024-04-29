# PHP-PGF

This repository is a PHP extension for decoding the [PGF](https://en.wikipedia.org/wiki/Progressive_Graphics_File) image format to either their raw bitmap form or directly re-encoded to PNG for ease of use.

The main goal of this library was to provide a simple way of fetching the thumbnails from a shared [digiKam](https://en.wikipedia.org/wiki/Digikam) database directly from said database instead of re-generating them.

As of now only these function used for decode are implemented:
  - `pgf_decode_to_rgba(string $pgfData, int $level = 0): string`
  - `pgf_decode_to_png(string $pgfData, int $level = 0): string`

As this extension was written purely for decoding images, I am not planing to implement the encode functions for now, if someone wants to, PRs are appreciated!

This extension depends on:
  - [libpgf](https://github.com/TheStaticTurtle/libpgf) (tested with `7.21.7`) 
  - [lodepng](https://github.com/lvandeve/lodepng) (tested with `ed3c5f1`)


Some checks were done to ensure that it wil not crash everything if an invalid use case is detected but please note that while libpgf does use c++ excpetions that are catchable it also contains calls to `assert` which will crash the php executable if reached.

The library has been successfully tested to decode digiKam thumbnails with:
  - `PHP-8.2-Win32-TS`
  - `PHP-8.1-Win32-NTS`
  - `PHP-8.3-Win32-NTS`

Linux build has not been tested!