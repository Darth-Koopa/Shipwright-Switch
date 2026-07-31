import sys
from PIL import Image, ImageDraw, ImageFont

def main():
    FONT = r"C:\Windows\Fonts\simhei.ttf"
    specs = [
        ("sTheEndCHITex", 80, 24, "结束"),
        ("sTheLegendOfZeldaCHITex", 120, 24, "塞尔达传说"),
        ("sOcarinaOfTimeCHITex", 112, 16, "时之笛"),
    ]
    out_dir = r"e:\Desktop\Shipwright-CN-cn-full\soh\assets\custom\textures\overlays\ovl_End_Title"
    for name, w, h, text in specs:
        img = Image.new("RGBA", (w, h), (0, 0, 0, 0))
        draw = ImageDraw.Draw(img)
        font = ImageFont.truetype(FONT, h - 4)
        bbox = draw.textbbox((0, 0), text, font=font)
        tw = bbox[2] - bbox[0]
        th = bbox[3] - bbox[1]
        x = (w - tw) // 2 - bbox[0]
        y = (h - th) // 2 - bbox[1]
        draw.text((x, y), text, font=font, fill=(255, 255, 255, 255))
        px = img.load()
        for yy in range(h):
            for xx in range(w):
                r, g, b, a = px[xx, yy]
                if a > 127:
                    px[xx, yy] = (255, 255, 255, 255)
                else:
                    px[xx, yy] = (0, 0, 0, 0)
        path = out_dir + "\\" + name + ".ia8.png"
        img.save(path)
        sys.stderr.write("saved " + path + "\n")

if __name__ == "__main__":
    main()
