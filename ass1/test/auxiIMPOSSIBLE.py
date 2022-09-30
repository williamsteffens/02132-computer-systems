import subprocess

for i in range(1, 6): 
    print("\n########################################################")
    print(f"\nRunning impossible sample: {i}");
    subprocess.run(['./main', f'./samples/impossible/{i}IMPOSSIBLE.bmp', f'./output/impossible/{i}IMPOSSIBLEout.bmp'])
    print("\n########################################################")