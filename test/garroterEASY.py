import subprocess

with open('./ass1data/p4/programOutputTH1-20T1-20-100-500.txt','a') as f: 
    for i in range(1, 21): 
        for j in range(1, 21): 
            subprocess.run(['java', '-cp', './out/production/JavaConcurrentProg', 'ass1.Search', 
                        '-R', 
                        '10', 
                        '-W',
                        '4',
                        '-d',
                        './ass1data/p4/dataTH1-20T1-20-100-500.csv',
                        'shakespeare.txt', 
                        'To be, or not to be, that is the question',
                        f'{j}',
                        f'{i}'],
                        stdout=f,
                        text=True)

        for j in range(30, 101, 10): 
            subprocess.run(['java', '-cp', './out/production/JavaConcurrentProg', 'ass1.Search', 
                        '-R', 
                        '10', 
                        '-W',
                        '4',
                        '-d',
                        './ass1data/p4/dataTH1-20T1-20-100-500.csv',
                        'shakespeare.txt', 
                        'To be, or not to be, that is the question',
                        f'{j}',
                        f'{i}'],
                        stdout=f,
                        text=True)

        for j in range(150, 501, 50): 
            subprocess.run(['java', '-cp', './out/production/JavaConcurrentProg', 'ass1.Search', 
                        '-R', 
                        '10', 
                        '-W',
                        '4',
                        '-d',
                        './ass1data/p4/dataTH1-20T1-20-100-500.csv',
                        'shakespeare.txt', 
                        'To be, or not to be, that is the question',
                        f'{j}',
                        f'{i}'],
                        stdout=f,
                        text=True)