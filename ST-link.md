# WRITE BINARY
st-flash --reset write file.bin 0x8000000

#ERASE
st-flash --reset erase

#READ FIRM
st-flash --reset read file.bin 0x8000000 0x20000