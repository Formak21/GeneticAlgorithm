from PIL import Image, ImageDraw


def f(n, flag=False) -> float:
    im = Image.new('RGBA', (255, 255), (255, 255, 255, 0))
    draw = ImageDraw.Draw(im)
    n = ''.join([str(i) for i in n])

    for i in range(len(n) // 20):
        x = int(n[0 + (20 * i):7 + (20 * i)], 2)
        y = int(n[7 + (20 * i):14 + (20 * i)], 2)
        r = int(n[14 + (20 * i):20 + (20 * i)], 2)
        draw.ellipse((x - r, y - r, x + r, y + r), fill=(0, 0, 0, 255))

    test_image = Image.open("1.png")
    x, y = im.size
    counter = 0
    pixels1 = im.load()
    pixels2 = test_image.load()
    for i in range(x):
        for j in range(y):
            if pixels2[i, j][0] == pixels1[i, j][0] and pixels2[i, j][0] == 0:
                counter += 1
    if flag:
        im.save('2.png')
    return float(counter)


def optimal(n) -> float:
    im2 = Image.open("1.png")
    x, y = im2.size
    pixels2 = im2.load()
    counter = 0
    for i in range(x):
        for j in range(y):
            if pixels2[i, j][0] == 0:
                counter += 1
    return float(counter)
