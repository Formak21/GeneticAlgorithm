with open(file='test_function_6.txt', mode='r', encoding='utf-8') as f:
    Data = [float(i[2:]) for i in f.read().splitlines() if len(i) and i[0] == 'E']
Answ = []

for i in ['classic', 'type-0', 'type-1', 'type-2_120x60', 'type-2_10x60', 'type-3_120x60', 'type-3_10x60']:
    for j in range(4):
        tmp = Data.pop(0)
        Answ.append((tmp, i))
color = 255

for i in sorted(Answ, key=lambda x: x[0]):
    print('------')
    print(color)
    print(i[1])
    print(str(i[0]).replace('.', ','))
    print('------')
    color -= 10