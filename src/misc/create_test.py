from PIL import Image, ImageDraw

x = 70
y = 123
r = 60

x1 = 145
y1 = 200
r1 = 40

im = Image.new('RGBA', (255, 255), (255, 255, 255, 0))
draw = ImageDraw.Draw(im)
draw.ellipse((x - r, y - r, x + r, y + r), fill=(0, 0, 0, 255))
draw.ellipse((x1 - r1, y1 - r1, x1 + r1, y1 + r1), fill=(0, 0, 0, 255))

im.save('1.png')
