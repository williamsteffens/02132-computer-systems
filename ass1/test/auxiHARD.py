import subprocess

for i in range(1, 11): 
    print(f"Running easy sample: {i}");
    subprocess.run(['./main', f'./samples/hard/{i}HARD.bmp', f'./output/hard/{i}HARDout.bmp'])