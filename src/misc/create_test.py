from PIL import Image, ImageDraw

x = 70
y = 123
r = 60

im = Image.new('RGBA', (255, 255), (255, 255, 255, 0))
draw = ImageDraw.Draw(im)
draw.ellipse((x - r, y - r, x + r, y + r), fill=(0, 0, 0, 255))

im.save('1.png')
