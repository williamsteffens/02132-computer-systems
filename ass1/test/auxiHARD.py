import subprocess

for i in range(1, 11): 
    print("########################################################")
    print(f"\nRunning hard sample: {i}");
    subprocess.run(['./main', f'./samples/hard/{i}HARD.bmp', f'./output/hard/{i}HARDout.bmp'])
    print("\n########################################################")