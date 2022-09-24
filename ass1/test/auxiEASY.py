import subprocess

for i in range(1, 11): 
    print(f"Running easy sample: {i}");
    subprocess.run(['./main', f'./samples/easy/{i}EASY.bmp', f'./output/easy/{i}EASYout.bmp'])