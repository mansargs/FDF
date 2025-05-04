import os
from PIL import Image, UnidentifiedImageError
from math import log
import numpy as np
import sys

def get_image_path():
    try:
        while True:
            try:
                image_path = str(input('Enter the image path: '))
                image = Image.open(image_path)
            except (FileNotFoundError, UnidentifiedImageError):
                print('\033[31mInvalid Image Path, Please Try Again!!\033[m')
                continue
            else:
                break
    except (KeyboardInterrupt):
        print('\033[33m\n\nKeyboardInterrupt: Program terminated by the user.\033[m')
        sys.exit()
    return image_path, image

def parse_without_color(image):
    width, height = image.size
    image_matrix = np.array(image)
    
    relief_map = []
    for i in range(height):
        row = []
        for j in range(width):
            height = int(np.mean(image_matrix[i, j]))
            if height < 0:
                color_info = '0x333E65'
            elif height == 0:
                color_info = '0x626A87'
            else:
                color_info = '0x878EA2'
            point_info = f'{height},{color_info}'
            row.append(point_info)
        relief_map.append(row)
    return relief_map

def change_extension(file_path, new_extension):
    base = os.path.splitext(os.path.basename(file_path))[0]
    return f"{base}.{new_extension}"

def main():
    image_path, image = get_image_path()
    width, height = image.size
    image_matrix = np.array(image)
    use_default_color = False

    relief_map = []
    for i in range(height):
        row = []
        for j in range(width):
            try:
                height = int((np.mean(image_matrix[i, j])))
                height = round(log(height + 1))
                r = image_matrix[i, j][0]
                g = image_matrix[i, j][1]
                b = image_matrix[i, j][2]
                color_info = f'0x{r:02x}{g:02x}{b:02x}'
                point_info = f'{height},{color_info}'
                row.append(point_info)
            except (IndexError):
                print('\033[31mUnable to parse image color :(\033[m')
                use_default_color = True
                break
        if use_default_color:
            break
        else:
            relief_map.append(row)

    if use_default_color:
        relief_map = parse_without_color(image)

    fdf_path = change_extension(image_path, 'fdf')
    with open(fdf_path, 'w') as file:
        for row in relief_map:
            file.write(" ".join(row) + '\n')
    print(f"\033[32m\nThe map '{fdf_path}' was created successfully!!\033[m")

if __name__ == '__main__':
    main()
