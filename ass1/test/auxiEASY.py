import subprocess

for i in range(1, 11): 
    print("########################################################")
    print(f"\nRunning easy sample: {i} (should be 300)");
    subprocess.run(['./main', f'./samples/easy/{i}EASY.bmp', f'./output/easy/{i}EASYout.bmp'])
    print("\n########################################################")
    