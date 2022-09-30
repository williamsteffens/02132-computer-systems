import subprocess

for i in range(1, 11): 
    print("########################################################")
    print(f"\nRunning medium sample: {i}");
    subprocess.run(['./main', f'./samples/medium/{i}MEDIUM.bmp', f'./output/medium/{i}MEDIUMout.bmp'])
    print("\n########################################################")