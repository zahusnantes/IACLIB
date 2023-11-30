# create_matrix.py

import csv

# Define matrix dimensions
width = 2
height = 2
depth = 2

# Generate matrix data
matrix_data = [[[i + j * width + k * width * height + 1.0 for i in range(width)] for j in range(height)] for k in range(depth)]

# Write matrix data to CSV file
with open('kernel.csv', 'w', newline='') as csvfile:
    matrix_writer = csv.writer(csvfile, delimiter=',', quotechar='"', quoting=csv.QUOTE_MINIMAL)
    
    for depth_slice in matrix_data:
        for row in depth_slice:
            matrix_writer.writerow(row)
