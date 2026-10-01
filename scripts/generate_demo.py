from pathlib import Path
from PIL import Image, ImageDraw, ImageFont

W, H = 1000, 620
BG = (13, 17, 23)
PANEL = (22, 27, 34)
TEXT = (230, 237, 243)
MUTED = (139, 148, 158)
GREEN = (46, 160, 67)
BLUE = (88, 166, 255)
ACCENT = (255, 200, 80)

BASE = "/usr/share/fonts/truetype/dejavu/"

def font(size, bold=False):
    name = "DejaVuSansMono-Bold.ttf" if bold else "DejaVuSansMono.ttf"
    return ImageFont.truetype(BASE + name, size)

lines = Path("demo-output.txt").read_text(encoding="utf-8").splitlines()
frames = []

for frame_no in range(2 + len(lines) * 2):
    im = Image.new("RGB", (W, H), BG)
    d = ImageDraw.Draw(im)

    d.text((38, 28), "Smart Valet Parking Service",
           font=font(28, True), fill=TEXT)
    d.text((38, 66),
           "Hash lookup  •  dual BST indexes  •  delete + undo",
           font=font(15), fill=MUTED)

    d.rounded_rectangle((35, 105, 965, 570),
                        radius=18, fill=PANEL)

    visible = min(len(lines), max(0, (frame_no - 2) // 2 + 1))
    y = 130

    for index, line in enumerate(lines[:visible]):
        if line.startswith(("1.", "2.", "3.", "4.", "5.")):
            color = BLUE
        elif "FOUND" in line or "Loaded records" in line:
            color = GREEN
        elif "NOT FOUND" in line:
            color = ACCENT
        else:
            color = TEXT

        if len(line) > 100:
            line = line[:97] + "..."

        d.text((58, y), line, font=font(16), fill=color)
        y += 22

    if visible == len(lines):
        d.rounded_rectangle((285, 535, 715, 568),
                            radius=12, fill=(31, 48, 38))
        d.text((335, 543), "✓ deterministic demo completed",
               font=font(15, True), fill=GREEN)

    frames.append(im)

frames[0].save(
    "demo.gif",
    save_all=True,
    append_images=frames[1:],
    duration=95,
    loop=0,
    optimize=True,
    disposal=2,
)
