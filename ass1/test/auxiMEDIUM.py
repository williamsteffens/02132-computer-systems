import subprocess

for i in range(1, 11): 
    print(f"Running easy sample: {i}");
    subprocess.run(['./main', f'./samples/medium/{i}MEDIUM.bmp', f'./output/medium/{i}MEDIUMout.bmp'])