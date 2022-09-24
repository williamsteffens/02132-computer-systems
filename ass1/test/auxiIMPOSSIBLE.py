import subprocess

for i in range(1, 6): 
    print(f"Running easy sample: {i}");
    subprocess.run(['./main', f'./samples/impossible/{i}IMPOSSIBLE.bmp', f'./output/impossible/{i}IMPOSSIBLEout.bmp'])