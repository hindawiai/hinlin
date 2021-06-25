<शैली गुरु>
/*
 * linux/drivers/video/hitfb.c -- Hitachi LCD frame buffer device
 *
 * (C) 1999 Mihai Spatar
 * (C) 2000 YAEGASHI Takeshi
 * (C) 2003, 2004 Paul Mundt
 * (C) 2003, 2004, 2006 Andriy Skulysh
 *
 *  This file is subject to the terms and conditions of the GNU General Public
 *  License. See the file COPYING in the मुख्य directory of this archive क्रम
 *  more details.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/fb.h>

#समावेश <यंत्र/machvec.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/hd64461.h>
#समावेश <cpu/dac.h>

#घोषणा	WIDTH 640

अटल काष्ठा fb_var_screeninfo hitfb_var = अणु
	.activate	= FB_ACTIVATE_NOW,
	.height		= -1,
	.width		= -1,
	.vmode		= FB_VMODE_NONINTERLACED,
पूर्ण;

अटल काष्ठा fb_fix_screeninfo hitfb_fix = अणु
	.id		= "Hitachi HD64461",
	.type		= FB_TYPE_PACKED_PIXELS,
	.accel		= FB_ACCEL_NONE,
पूर्ण;

अटल अंतरभूत व्योम hitfb_accel_रुको(व्योम)
अणु
	जबतक (fb_पढ़ोw(HD64461_GRCFGR) & HD64461_GRCFGR_ACCSTATUS) ;
पूर्ण

अटल अंतरभूत व्योम hitfb_accel_start(पूर्णांक truecolor)
अणु
	अगर (truecolor) अणु
		fb_ग_लिखोw(6, HD64461_GRCFGR);
	पूर्ण अन्यथा अणु
		fb_ग_लिखोw(7, HD64461_GRCFGR);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम hitfb_accel_set_dest(पूर्णांक truecolor, u16 dx, u16 dy,
					u16 width, u16 height)
अणु
	u32 saddr = WIDTH * dy + dx;
	अगर (truecolor)
		saddr <<= 1;

	fb_ग_लिखोw(width-1, HD64461_BBTDWR);
	fb_ग_लिखोw(height-1, HD64461_BBTDHR);

	fb_ग_लिखोw(saddr & 0xffff, HD64461_BBTDSARL);
	fb_ग_लिखोw(saddr >> 16, HD64461_BBTDSARH);

पूर्ण

अटल अंतरभूत व्योम hitfb_accel_bitblt(पूर्णांक truecolor, u16 sx, u16 sy, u16 dx,
				      u16 dy, u16 width, u16 height, u16 rop,
				      u32 mask_addr)
अणु
	u32 saddr, daddr;
	u32 maddr = 0;

	height--;
	width--;
	fb_ग_लिखोw(rop, HD64461_BBTROPR);
	अगर ((sy < dy) || ((sy == dy) && (sx <= dx))) अणु
		saddr = WIDTH * (sy + height) + sx + width;
		daddr = WIDTH * (dy + height) + dx + width;
		अगर (mask_addr) अणु
			अगर (truecolor)
				maddr = ((width >> 3) + 1) * (height + 1) - 1;
			अन्यथा
				maddr =
				    (((width >> 4) + 1) * (height + 1) - 1) * 2;

			fb_ग_लिखोw((1 << 5) | 1, HD64461_BBTMDR);
		पूर्ण अन्यथा
			fb_ग_लिखोw(1, HD64461_BBTMDR);
	पूर्ण अन्यथा अणु
		saddr = WIDTH * sy + sx;
		daddr = WIDTH * dy + dx;
		अगर (mask_addr) अणु
			fb_ग_लिखोw((1 << 5), HD64461_BBTMDR);
		पूर्ण अन्यथा अणु
			fb_ग_लिखोw(0, HD64461_BBTMDR);
		पूर्ण
	पूर्ण
	अगर (truecolor) अणु
		saddr <<= 1;
		daddr <<= 1;
	पूर्ण
	fb_ग_लिखोw(width, HD64461_BBTDWR);
	fb_ग_लिखोw(height, HD64461_BBTDHR);
	fb_ग_लिखोw(saddr & 0xffff, HD64461_BBTSSARL);
	fb_ग_लिखोw(saddr >> 16, HD64461_BBTSSARH);
	fb_ग_लिखोw(daddr & 0xffff, HD64461_BBTDSARL);
	fb_ग_लिखोw(daddr >> 16, HD64461_BBTDSARH);
	अगर (mask_addr) अणु
		maddr += mask_addr;
		fb_ग_लिखोw(maddr & 0xffff, HD64461_BBTMARL);
		fb_ग_लिखोw(maddr >> 16, HD64461_BBTMARH);
	पूर्ण
	hitfb_accel_start(truecolor);
पूर्ण

अटल व्योम hitfb_fillrect(काष्ठा fb_info *p, स्थिर काष्ठा fb_fillrect *rect)
अणु
	अगर (rect->rop != ROP_COPY)
		cfb_fillrect(p, rect);
	अन्यथा अणु
		hitfb_accel_रुको();
		fb_ग_लिखोw(0x00f0, HD64461_BBTROPR);
		fb_ग_लिखोw(16, HD64461_BBTMDR);

		अगर (p->var.bits_per_pixel == 16) अणु
			fb_ग_लिखोw(((u32 *) (p->pseuकरो_palette))[rect->color],
				  HD64461_GRSCR);
			hitfb_accel_set_dest(1, rect->dx, rect->dy, rect->width,
					     rect->height);
			hitfb_accel_start(1);
		पूर्ण अन्यथा अणु
			fb_ग_लिखोw(rect->color, HD64461_GRSCR);
			hitfb_accel_set_dest(0, rect->dx, rect->dy, rect->width,
					     rect->height);
			hitfb_accel_start(0);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम hitfb_copyarea(काष्ठा fb_info *p, स्थिर काष्ठा fb_copyarea *area)
अणु
	hitfb_accel_रुको();
	hitfb_accel_bitblt(p->var.bits_per_pixel == 16, area->sx, area->sy,
			   area->dx, area->dy, area->width, area->height,
			   0x00cc, 0);
पूर्ण

अटल पूर्णांक hitfb_pan_display(काष्ठा fb_var_screeninfo *var,
			     काष्ठा fb_info *info)
अणु
	पूर्णांक xoffset = var->xoffset;
	पूर्णांक yoffset = var->yoffset;

	अगर (xoffset != 0)
		वापस -EINVAL;

	fb_ग_लिखोw((yoffset*info->fix.line_length)>>10, HD64461_LCDCBAR);

	वापस 0;
पूर्ण

पूर्णांक hitfb_blank(पूर्णांक blank_mode, काष्ठा fb_info *info)
अणु
	अचिन्हित लघु v;

	अगर (blank_mode) अणु
		v = fb_पढ़ोw(HD64461_LDR1);
		v &= ~HD64461_LDR1_DON;
		fb_ग_लिखोw(v, HD64461_LDR1);

		v = fb_पढ़ोw(HD64461_LCDCCR);
		v |= HD64461_LCDCCR_MOFF;
		fb_ग_लिखोw(v, HD64461_LCDCCR);

		v = fb_पढ़ोw(HD64461_STBCR);
		v |= HD64461_STBCR_SLCDST;
		fb_ग_लिखोw(v, HD64461_STBCR);
	पूर्ण अन्यथा अणु
		v = fb_पढ़ोw(HD64461_STBCR);
		v &= ~HD64461_STBCR_SLCDST;
		fb_ग_लिखोw(v, HD64461_STBCR);

		v = fb_पढ़ोw(HD64461_LCDCCR);
		v &= ~(HD64461_LCDCCR_MOFF | HD64461_LCDCCR_STREQ);
		fb_ग_लिखोw(v, HD64461_LCDCCR);

		करो अणु
		    v = fb_पढ़ोw(HD64461_LCDCCR);
		पूर्ण जबतक(v&HD64461_LCDCCR_STBACK);

		v = fb_पढ़ोw(HD64461_LDR1);
		v |= HD64461_LDR1_DON;
		fb_ग_लिखोw(v, HD64461_LDR1);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक hitfb_setcolreg(अचिन्हित regno, अचिन्हित red, अचिन्हित green,
			   अचिन्हित blue, अचिन्हित transp, काष्ठा fb_info *info)
अणु
	अगर (regno >= 256)
		वापस 1;

	चयन (info->var.bits_per_pixel) अणु
	हाल 8:
		fb_ग_लिखोw(regno << 8, HD64461_CPTWAR);
		fb_ग_लिखोw(red >> 10, HD64461_CPTWDR);
		fb_ग_लिखोw(green >> 10, HD64461_CPTWDR);
		fb_ग_लिखोw(blue >> 10, HD64461_CPTWDR);
		अवरोध;
	हाल 16:
		अगर (regno >= 16)
			वापस 1;
		((u32 *) (info->pseuकरो_palette))[regno] =
		    ((red & 0xf800)) |
		    ((green & 0xfc00) >> 5) | ((blue & 0xf800) >> 11);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक hitfb_sync(काष्ठा fb_info *info)
अणु
	hitfb_accel_रुको();

	वापस 0;
पूर्ण

अटल पूर्णांक hitfb_check_var(काष्ठा fb_var_screeninfo *var, काष्ठा fb_info *info)
अणु
	पूर्णांक maxy;

	var->xres = info->var.xres;
	var->xres_भव = info->var.xres;
	var->yres = info->var.yres;

	अगर ((var->bits_per_pixel != 8) && (var->bits_per_pixel != 16))
		var->bits_per_pixel = info->var.bits_per_pixel;

	अगर (var->yres_भव < var->yres)
		var->yres_भव = var->yres;

	maxy = info->fix.smem_len / var->xres;

	अगर (var->bits_per_pixel == 16)
		maxy /= 2;

	अगर (var->yres_भव > maxy)
		var->yres_भव = maxy;

	var->xoffset = 0;
	var->yoffset = 0;

	चयन (var->bits_per_pixel) अणु
	हाल 8:
		var->red.offset = 0;
		var->red.length = 8;
		var->green.offset = 0;
		var->green.length = 8;
		var->blue.offset = 0;
		var->blue.length = 8;
		var->transp.offset = 0;
		var->transp.length = 0;
		अवरोध;
	हाल 16:		/* RGB 565 */
		var->red.offset = 11;
		var->red.length = 5;
		var->green.offset = 5;
		var->green.length = 6;
		var->blue.offset = 0;
		var->blue.length = 5;
		var->transp.offset = 0;
		var->transp.length = 0;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hitfb_set_par(काष्ठा fb_info *info)
अणु
	अचिन्हित लघु ldr3;

	चयन (info->var.bits_per_pixel) अणु
	हाल 8:
		info->fix.line_length = info->var.xres;
		info->fix.visual = FB_VISUAL_PSEUDOCOLOR;
		info->fix.ypanstep = 16;
		अवरोध;
	हाल 16:
		info->fix.line_length = info->var.xres*2;
		info->fix.visual = FB_VISUAL_TRUECOLOR;
		info->fix.ypanstep = 8;
		अवरोध;
	पूर्ण

	fb_ग_लिखोw(info->fix.line_length, HD64461_LCDCLOR);
	ldr3 = fb_पढ़ोw(HD64461_LDR3);
	ldr3 &= ~15;
	ldr3 |= (info->var.bits_per_pixel == 8) ? 4 : 8;
	fb_ग_लिखोw(ldr3, HD64461_LDR3);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा fb_ops hitfb_ops = अणु
	.owner		= THIS_MODULE,
	.fb_check_var	= hitfb_check_var,
	.fb_set_par		= hitfb_set_par,
	.fb_setcolreg	= hitfb_setcolreg,
	.fb_blank	= hitfb_blank,
	.fb_sync	= hitfb_sync,
	.fb_pan_display = hitfb_pan_display,
	.fb_fillrect	= hitfb_fillrect,
	.fb_copyarea	= hitfb_copyarea,
	.fb_imageblit	= cfb_imageblit,
पूर्ण;

अटल पूर्णांक hitfb_probe(काष्ठा platक्रमm_device *dev)
अणु
	अचिन्हित लघु lcdclor, ldr3, ldvndr;
	काष्ठा fb_info *info;
	पूर्णांक ret;

	अगर (fb_get_options("hitfb", शून्य))
		वापस -ENODEV;

	hitfb_fix.mmio_start = HD64461_IO_OFFSET(0x1000);
	hitfb_fix.mmio_len = 0x1000;
	hitfb_fix.smem_start = HD64461_IO_OFFSET(0x02000000);
	hitfb_fix.smem_len = 512 * 1024;

	lcdclor = fb_पढ़ोw(HD64461_LCDCLOR);
	ldvndr = fb_पढ़ोw(HD64461_LDVNDR);
	ldr3 = fb_पढ़ोw(HD64461_LDR3);

	चयन (ldr3 & 15) अणु
	शेष:
	हाल 4:
		hitfb_var.bits_per_pixel = 8;
		hitfb_var.xres = lcdclor;
		अवरोध;
	हाल 8:
		hitfb_var.bits_per_pixel = 16;
		hitfb_var.xres = lcdclor / 2;
		अवरोध;
	पूर्ण
	hitfb_fix.line_length = lcdclor;
	hitfb_fix.visual = (hitfb_var.bits_per_pixel == 8) ?
	    FB_VISUAL_PSEUDOCOLOR : FB_VISUAL_TRUECOLOR;
	hitfb_var.yres = ldvndr + 1;
	hitfb_var.xres_भव = hitfb_var.xres;
	hitfb_var.yres_भव = hitfb_fix.smem_len / lcdclor;
	चयन (hitfb_var.bits_per_pixel) अणु
	हाल 8:
		hitfb_var.red.offset = 0;
		hitfb_var.red.length = 8;
		hitfb_var.green.offset = 0;
		hitfb_var.green.length = 8;
		hitfb_var.blue.offset = 0;
		hitfb_var.blue.length = 8;
		hitfb_var.transp.offset = 0;
		hitfb_var.transp.length = 0;
		अवरोध;
	हाल 16:		/* RGB 565 */
		hitfb_var.red.offset = 11;
		hitfb_var.red.length = 5;
		hitfb_var.green.offset = 5;
		hitfb_var.green.length = 6;
		hitfb_var.blue.offset = 0;
		hitfb_var.blue.length = 5;
		hitfb_var.transp.offset = 0;
		hitfb_var.transp.length = 0;
		अवरोध;
	पूर्ण

	info = framebuffer_alloc(माप(u32) * 16, &dev->dev);
	अगर (unlikely(!info))
		वापस -ENOMEM;

	info->fbops = &hitfb_ops;
	info->var = hitfb_var;
	info->fix = hitfb_fix;
	info->pseuकरो_palette = info->par;
	info->flags = FBINFO_DEFAULT | FBINFO_HWACCEL_YPAN |
		FBINFO_HWACCEL_FILLRECT | FBINFO_HWACCEL_COPYAREA;

	info->screen_base = (व्योम *)hitfb_fix.smem_start;

	ret = fb_alloc_cmap(&info->cmap, 256, 0);
	अगर (unlikely(ret < 0))
		जाओ err_fb;

	ret = रेजिस्टर_framebuffer(info);
	अगर (unlikely(ret < 0))
		जाओ err;

	platक्रमm_set_drvdata(dev, info);

	fb_info(info, "%s frame buffer device\n", info->fix.id);

	वापस 0;

err:
	fb_dealloc_cmap(&info->cmap);
err_fb:
	framebuffer_release(info);
	वापस ret;
पूर्ण

अटल पूर्णांक hitfb_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा fb_info *info = platक्रमm_get_drvdata(dev);

	unरेजिस्टर_framebuffer(info);
	fb_dealloc_cmap(&info->cmap);
	framebuffer_release(info);

	वापस 0;
पूर्ण

अटल पूर्णांक hitfb_suspend(काष्ठा device *dev)
अणु
	u16 v;

	hitfb_blank(1,0);
	v = fb_पढ़ोw(HD64461_STBCR);
	v |= HD64461_STBCR_SLCKE_IST;
	fb_ग_लिखोw(v, HD64461_STBCR);

	वापस 0;
पूर्ण

अटल पूर्णांक hitfb_resume(काष्ठा device *dev)
अणु
	u16 v;

	v = fb_पढ़ोw(HD64461_STBCR);
	v &= ~HD64461_STBCR_SLCKE_OST;
	msleep(100);
	v = fb_पढ़ोw(HD64461_STBCR);
	v &= ~HD64461_STBCR_SLCKE_IST;
	fb_ग_लिखोw(v, HD64461_STBCR);
	hitfb_blank(0,0);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops hitfb_dev_pm_ops = अणु
	.suspend	= hitfb_suspend,
	.resume		= hitfb_resume,
पूर्ण;

अटल काष्ठा platक्रमm_driver hitfb_driver = अणु
	.probe		= hitfb_probe,
	.हटाओ		= hitfb_हटाओ,
	.driver		= अणु
		.name	= "hitfb",
		.pm	= &hitfb_dev_pm_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device hitfb_device = अणु
	.name	= "hitfb",
	.id	= -1,
पूर्ण;

अटल पूर्णांक __init hitfb_init(व्योम)
अणु
	पूर्णांक ret;

	ret = platक्रमm_driver_रेजिस्टर(&hitfb_driver);
	अगर (!ret) अणु
		ret = platक्रमm_device_रेजिस्टर(&hitfb_device);
		अगर (ret)
			platक्रमm_driver_unरेजिस्टर(&hitfb_driver);
	पूर्ण
	वापस ret;
पूर्ण


अटल व्योम __निकास hitfb_निकास(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(&hitfb_device);
	platक्रमm_driver_unरेजिस्टर(&hitfb_driver);
पूर्ण

module_init(hitfb_init);
module_निकास(hitfb_निकास);

MODULE_LICENSE("GPL");
