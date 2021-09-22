from PIL import Image
import numpy as np
import csv

input_file = 'Real_Trezor_Startup.csv'
output_file = 'Real Trezor Startup.png'
start_line_csv = 1057
end_line_csv = 2080
rows = 64
columns = 128
inputs = []
pixels = np.zeros([rows, columns, 3], dtype=np.uint8)


# FUNCTIONS

def decimalToBinary(n):
    return "{0:b}".format(int(n))


# MAIN

with open(input_file) as csv_file:
    csv_reader = csv.reader(csv_file, delimiter=',')
    line_count = 0
    col = 0
    for row in csv_reader:
        if line_count == 0:
            # print(f'Column names are {", ".join(row)}')
            line_count += 1
        else:
            if line_count >= start_line_csv-1 and line_count <=  end_line_csv-1:
                # print(f'SPI.transfer(0x{row[2][8:10]});')

                for i in range(8):
                    bit = (255, 255, 255) if format(int(row[2][8:10], 16), '#010b')[2+i:3+i] == "1" else (0, 0, 0)
                    pixels[((col//128)*8 - i + 7)][col%128] = bit

                col += 1
            line_count += 1
    # print(f'Processed {line_count} lines.')

# Convert the pixels into an array using numpy
array = np.array(pixels, dtype=np.uint8)

# Use PIL to create an image from the new array of pixels
new_image = Image.fromarray(array)
new_image = new_image.rotate(180)
new_image.save(output_file)


