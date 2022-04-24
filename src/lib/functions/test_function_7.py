from PIL import Image, ImageDraw


def f(n, flag=False) -> float:
    n = ''.join([str(i) for i in n])
    x = int(n[0:7], 2)
    y = int(n[7:14], 2)
    r = int(n[14:20], 2)

    im = Image.new('RGBA', (255, 255), (255, 255, 255, 0))
    draw = ImageDraw.Draw(im)
    draw.ellipse((x - r, y - r, x + r, y + r), fill=(0, 0, 0, 255))

    im2 = Image.open("1.png")
    x, y = im.size

    counter = 0

    pixels1 = im.load()
    pixels2 = im2.load()
    for i in range(x):
        for j in range(y):
            if pixels2[i, j] == pixels1[i, j]:
                counter += 1

    if flag:
        im.save('2.png')
    return counter


def optimal(n) -> float:
    im2 = Image.open("1.png")
    x, y = im2.size
    counter = 0
    for i in range(x):
        for j in range(y):
                counter += 1
    return counter

'''
x = 70
y = 123
r = 60

im = Image.new('RGBA', (255, 255), (255, 255, 255, 0))
draw = ImageDraw.Draw(im)
draw.ellipse((x - r, y - r, x + r, y + r), fill=(0, 0, 0, 255))

im.save('test_function_7_pic_0.png')
'''