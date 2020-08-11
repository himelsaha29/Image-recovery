# Image-recovery

This program recovers image files, specifically JPEGs, from a forensic image. JPEGs have “signatures,” patterns of bytes that can distinguish them from other file formats. The first 3 bytes of a JPEG are 0xff 0xd8 0xff and the 4th byte is either 0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9, 0xea, 0xeb, 0xec, 0xed, 0xee, or 0xef. These first 4 bytes signify the start of a JPEG file. In devices like digital cameras, photographs are stored contiguously on memory cards, whereby each photo is stored immediately after the previously taken photo. Hence, the start of a JPEG usually demarks the end of another. 

The program iterates over a copy of memory card forensic image file, looking for JPEGs’ signatures. Each time a signature is found, a new file is opened for writing and filled with bytes from the memory card, closing that file only when another signature is encountered.Data is copied and writtn in blocks of 512 bytes.

Usage: ./recover [location of "raw" format file]
