<शैली गुरु>
/*
 * BRIEF MODULE DESCRIPTION
 *	Au1100 LCD Driver.
 *
 * Rewritten क्रम 2.6 by Embedded Alley Solutions
 * 	<source@embeddedalley.com>, based on submissions by
 *  	Karl Lessard <klessard@sunrisetelecom.com>
 *  	<c.pellegrin@exadron.com>
 *
 * PM support added by Roकरोlfo Giometti <giometti@linux.it>
 * Cursor enable/disable by Roकरोlfo Giometti <giometti@linux.it>
 *
 * Copyright 2002 MontaVista Software
 * Author: MontaVista Software, Inc.
 *		ppopov@mvista.com or source@mvista.com
 *
 * Copyright 2002 Alchemy Semiconductor
 * Author: Alchemy Semiconductor
 *
 * Based on:
 * linux/drivers/video/skeletonfb.c -- Skeleton क्रम a frame buffer device
 *  Created 28 Dec 1997 by Geert Uytterhoeven
 *
 *  This program is मुक्त software; you can redistribute	 it and/or modअगरy it
 *  under  the terms of	 the GNU General  Public License as published by the
 *  Free Software Foundation;  either version 2 of the	License, or (at your
 *  option) any later version.
 *
 *  THIS  SOFTWARE  IS PROVIDED	  ``AS	IS'' AND   ANY	EXPRESS OR IMPLIED
 *  WARRANTIES,	  INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF
 *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN
 *  NO	EVENT  SHALL   THE AUTHOR  BE	 LIABLE FOR ANY	  सूचीECT, INसूचीECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 *  NOT LIMITED	  TO, PROCUREMENT OF  SUBSTITUTE GOODS	OR SERVICES; LOSS OF
 *  USE, DATA,	OR PROFITS; OR	BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 *  ANY THEORY OF LIABILITY, WHETHER IN	 CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *  You should have received a copy of the  GNU General Public License aदीर्घ
 *  with this program; अगर not, ग_लिखो  to the Free Software Foundation, Inc.,
 *  675 Mass Ave, Cambridge, MA 02139, USA.
 */
#समावेश <linux/clk.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/fb.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/mach-au1x00/au1000.h>

#घोषणा DEBUG 0

#समावेश "au1100fb.h"

#घोषणा DRIVER_NAME "au1100fb"
#घोषणा DRIVER_DESC "LCD controller driver for AU1100 processors"

#घोषणा to_au1100fb_device(_info) \
	  (_info ? container_of(_info, काष्ठा au1100fb_device, info) : शून्य);

/* Bitfields क्रमmat supported by the controller. Note that the order of क्रमmats
 * SHOULD be the same as in the LCD_CONTROL_SBPPF field, so we can retrieve the
 * right pixel क्रमmat by करोing rgb_bitfields[LCD_CONTROL_SBPPF_XXX >> LCD_CONTROL_SBPPF]
 */
काष्ठा fb_bitfield rgb_bitfields[][4] =
अणु
  	/*     Red, 	   Green, 	 Blue, 	     Transp   */
	अणु अणु 10, 6, 0 पूर्ण, अणु 5, 5, 0 पूर्ण, अणु 0, 5, 0 पूर्ण, अणु 0, 0, 0 पूर्ण पूर्ण,
	अणु अणु 11, 5, 0 पूर्ण, अणु 5, 6, 0 पूर्ण, अणु 0, 5, 0 पूर्ण, अणु 0, 0, 0 पूर्ण पूर्ण,
	अणु अणु 11, 5, 0 पूर्ण, अणु 6, 5, 0 पूर्ण, अणु 0, 6, 0 पूर्ण, अणु 0, 0, 0 पूर्ण पूर्ण,
	अणु अणु 10, 5, 0 पूर्ण, अणु 5, 5, 0 पूर्ण, अणु 0, 5, 0 पूर्ण, अणु 15, 1, 0 पूर्ण पूर्ण,
	अणु अणु 11, 5, 0 पूर्ण, अणु 6, 5, 0 पूर्ण, अणु 1, 5, 0 पूर्ण, अणु 0, 1, 0 पूर्ण पूर्ण,

	/* The last is used to describe 12bpp क्रमmat */
	अणु अणु 8, 4, 0 पूर्ण,  अणु 4, 4, 0 पूर्ण, अणु 0, 4, 0 पूर्ण, अणु 0, 0, 0 पूर्ण पूर्ण,
पूर्ण;

अटल काष्ठा fb_fix_screeninfo au1100fb_fix = अणु
	.id		= "AU1100 FB",
	.xpanstep 	= 1,
	.ypanstep 	= 1,
	.type		= FB_TYPE_PACKED_PIXELS,
	.accel		= FB_ACCEL_NONE,
पूर्ण;

अटल काष्ठा fb_var_screeninfo au1100fb_var = अणु
	.activate	= FB_ACTIVATE_NOW,
	.height		= -1,
	.width		= -1,
	.vmode		= FB_VMODE_NONINTERLACED,
पूर्ण;

/* fb_blank
 * Blank the screen. Depending on the mode, the screen will be
 * activated with the backlight color, or desactivated
 */
अटल पूर्णांक au1100fb_fb_blank(पूर्णांक blank_mode, काष्ठा fb_info *fbi)
अणु
	काष्ठा au1100fb_device *fbdev = to_au1100fb_device(fbi);

	prपूर्णांक_dbg("fb_blank %d %p", blank_mode, fbi);

	चयन (blank_mode) अणु

	हाल VESA_NO_BLANKING:
		/* Turn on panel */
		fbdev->regs->lcd_control |= LCD_CONTROL_GO;
		wmb(); /* drain ग_लिखोbuffer */
		अवरोध;

	हाल VESA_VSYNC_SUSPEND:
	हाल VESA_HSYNC_SUSPEND:
	हाल VESA_POWERDOWN:
		/* Turn off panel */
		fbdev->regs->lcd_control &= ~LCD_CONTROL_GO;
		wmb(); /* drain ग_लिखोbuffer */
		अवरोध;
	शेष:
		अवरोध;

	पूर्ण
	वापस 0;
पूर्ण

/*
 * Set hardware with var settings. This will enable the controller with a specअगरic
 * mode, normally validated with the fb_check_var method
	 */
पूर्णांक au1100fb_seपंचांगode(काष्ठा au1100fb_device *fbdev)
अणु
	काष्ठा fb_info *info = &fbdev->info;
	u32 words;
	पूर्णांक index;

	अगर (!fbdev)
		वापस -EINVAL;

	/* Update var-dependent FB info */
	अगर (panel_is_active(fbdev->panel) || panel_is_color(fbdev->panel)) अणु
		अगर (info->var.bits_per_pixel <= 8) अणु
			/* palettized */
			info->var.red.offset    = 0;
			info->var.red.length    = info->var.bits_per_pixel;
			info->var.red.msb_right = 0;

			info->var.green.offset  = 0;
			info->var.green.length  = info->var.bits_per_pixel;
			info->var.green.msb_right = 0;

			info->var.blue.offset   = 0;
			info->var.blue.length   = info->var.bits_per_pixel;
			info->var.blue.msb_right = 0;

			info->var.transp.offset = 0;
			info->var.transp.length = 0;
			info->var.transp.msb_right = 0;

			info->fix.visual = FB_VISUAL_PSEUDOCOLOR;
			info->fix.line_length = info->var.xres_भव /
							(8/info->var.bits_per_pixel);
		पूर्ण अन्यथा अणु
			/* non-palettized */
			index = (fbdev->panel->control_base & LCD_CONTROL_SBPPF_MASK) >> LCD_CONTROL_SBPPF_BIT;
			info->var.red = rgb_bitfields[index][0];
			info->var.green = rgb_bitfields[index][1];
			info->var.blue = rgb_bitfields[index][2];
			info->var.transp = rgb_bitfields[index][3];

			info->fix.visual = FB_VISUAL_TRUECOLOR;
			info->fix.line_length = info->var.xres_भव << 1; /* depth=16 */
		पूर्ण
	पूर्ण अन्यथा अणु
		/* mono */
		info->fix.visual = FB_VISUAL_MONO10;
		info->fix.line_length = info->var.xres_भव / 8;
	पूर्ण

	info->screen_size = info->fix.line_length * info->var.yres_भव;
	info->var.rotate = ((fbdev->panel->control_base&LCD_CONTROL_SM_MASK) \
				>> LCD_CONTROL_SM_BIT) * 90;

	/* Determine BPP mode and क्रमmat */
	fbdev->regs->lcd_control = fbdev->panel->control_base;
	fbdev->regs->lcd_horztiming = fbdev->panel->horztiming;
	fbdev->regs->lcd_verttiming = fbdev->panel->verttiming;
	fbdev->regs->lcd_clkcontrol = fbdev->panel->clkcontrol_base;
	fbdev->regs->lcd_पूर्णांकenable = 0;
	fbdev->regs->lcd_पूर्णांकstatus = 0;
	fbdev->regs->lcd_dmaaddr0 = LCD_DMA_SA_N(fbdev->fb_phys);

	अगर (panel_is_dual(fbdev->panel)) अणु
		/* Second panel display seconf half of screen अगर possible,
		 * otherwise display the same as the first panel */
		अगर (info->var.yres_भव >= (info->var.yres << 1)) अणु
			fbdev->regs->lcd_dmaaddr1 = LCD_DMA_SA_N(fbdev->fb_phys +
							  (info->fix.line_length *
						          (info->var.yres_भव >> 1)));
		पूर्ण अन्यथा अणु
			fbdev->regs->lcd_dmaaddr1 = LCD_DMA_SA_N(fbdev->fb_phys);
		पूर्ण
	पूर्ण

	words = info->fix.line_length / माप(u32);
	अगर (!info->var.rotate || (info->var.rotate == 180)) अणु
		words *= info->var.yres_भव;
		अगर (info->var.rotate /* 180 */) अणु
			words -= (words % 8); /* should be भागisable by 8 */
		पूर्ण
	पूर्ण
	fbdev->regs->lcd_words = LCD_WRD_WRDS_N(words);

	fbdev->regs->lcd_pwmभाग = 0;
	fbdev->regs->lcd_pwmhi = 0;

	/* Resume controller */
	fbdev->regs->lcd_control |= LCD_CONTROL_GO;
	mdelay(10);
	au1100fb_fb_blank(VESA_NO_BLANKING, info);

	वापस 0;
पूर्ण

/* fb_setcolreg
 * Set color in LCD palette.
 */
पूर्णांक au1100fb_fb_setcolreg(अचिन्हित regno, अचिन्हित red, अचिन्हित green, अचिन्हित blue, अचिन्हित transp, काष्ठा fb_info *fbi)
अणु
	काष्ठा au1100fb_device *fbdev;
	u32 *palette;
	u32 value;

	fbdev = to_au1100fb_device(fbi);
	palette = fbdev->regs->lcd_pallettebase;

	अगर (regno > (AU1100_LCD_NBR_PALETTE_ENTRIES - 1))
		वापस -EINVAL;

	अगर (fbi->var.grayscale) अणु
		/* Convert color to grayscale */
		red = green = blue =
			(19595 * red + 38470 * green + 7471 * blue) >> 16;
	पूर्ण

	अगर (fbi->fix.visual == FB_VISUAL_TRUECOLOR) अणु
		/* Place color in the pseuकरोpalette */
		अगर (regno > 16)
			वापस -EINVAL;

		palette = (u32*)fbi->pseuकरो_palette;

		red   >>= (16 - fbi->var.red.length);
		green >>= (16 - fbi->var.green.length);
		blue  >>= (16 - fbi->var.blue.length);

		value = (red   << fbi->var.red.offset) 	|
			(green << fbi->var.green.offset)|
			(blue  << fbi->var.blue.offset);
		value &= 0xFFFF;

	पूर्ण अन्यथा अगर (panel_is_active(fbdev->panel)) अणु
		/* COLOR TFT PALLETTIZED (use RGB 565) */
		value = (red & 0xF800)|((green >> 5) & 0x07E0)|((blue >> 11) & 0x001F);
		value &= 0xFFFF;

	पूर्ण अन्यथा अगर (panel_is_color(fbdev->panel)) अणु
		/* COLOR STN MODE */
		value = (((panel_swap_rgb(fbdev->panel) ? blue : red) >> 12) & 0x000F) |
			((green >> 8) & 0x00F0) |
			(((panel_swap_rgb(fbdev->panel) ? red : blue) >> 4) & 0x0F00);
		value &= 0xFFF;
	पूर्ण अन्यथा अणु
		/* MONOCHROME MODE */
		value = (green >> 12) & 0x000F;
		value &= 0xF;
	पूर्ण

	palette[regno] = value;

	वापस 0;
पूर्ण

/* fb_pan_display
 * Pan display in x and/or y as specअगरied
 */
पूर्णांक au1100fb_fb_pan_display(काष्ठा fb_var_screeninfo *var, काष्ठा fb_info *fbi)
अणु
	काष्ठा au1100fb_device *fbdev;
	पूर्णांक dy;

	fbdev = to_au1100fb_device(fbi);

	prपूर्णांक_dbg("fb_pan_display %p %p", var, fbi);

	अगर (!var || !fbdev) अणु
		वापस -EINVAL;
	पूर्ण

	अगर (var->xoffset - fbi->var.xoffset) अणु
		/* No support क्रम X panning क्रम now! */
		वापस -EINVAL;
	पूर्ण

	prपूर्णांक_dbg("fb_pan_display 2 %p %p", var, fbi);
	dy = var->yoffset - fbi->var.yoffset;
	अगर (dy) अणु

		u32 dmaaddr;

		prपूर्णांक_dbg("Panning screen of %d lines", dy);

		dmaaddr = fbdev->regs->lcd_dmaaddr0;
		dmaaddr += (fbi->fix.line_length * dy);

		/* TODO: Wait क्रम current frame to finished */
		fbdev->regs->lcd_dmaaddr0 = LCD_DMA_SA_N(dmaaddr);

		अगर (panel_is_dual(fbdev->panel)) अणु
			dmaaddr = fbdev->regs->lcd_dmaaddr1;
			dmaaddr += (fbi->fix.line_length * dy);
			fbdev->regs->lcd_dmaaddr0 = LCD_DMA_SA_N(dmaaddr);
	पूर्ण
	पूर्ण
	prपूर्णांक_dbg("fb_pan_display 3 %p %p", var, fbi);

	वापस 0;
पूर्ण

/* fb_mmap
 * Map video memory in user space. We करोn't use the generic fb_mmap method मुख्यly
 * to allow the use of the TLB streaming flag (CCA=6)
 */
पूर्णांक au1100fb_fb_mmap(काष्ठा fb_info *fbi, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा au1100fb_device *fbdev = to_au1100fb_device(fbi);

	pgprot_val(vma->vm_page_prot) |= (6 << 9); //CCA=6

	वापस dma_mmap_coherent(fbdev->dev, vma, fbdev->fb_mem, fbdev->fb_phys,
			fbdev->fb_len);
पूर्ण

अटल स्थिर काष्ठा fb_ops au1100fb_ops =
अणु
	.owner			= THIS_MODULE,
	.fb_setcolreg		= au1100fb_fb_setcolreg,
	.fb_blank		= au1100fb_fb_blank,
	.fb_pan_display		= au1100fb_fb_pan_display,
	.fb_fillrect		= cfb_fillrect,
	.fb_copyarea		= cfb_copyarea,
	.fb_imageblit		= cfb_imageblit,
	.fb_mmap		= au1100fb_fb_mmap,
पूर्ण;


/*-------------------------------------------------------------------------*/

अटल पूर्णांक au1100fb_setup(काष्ठा au1100fb_device *fbdev)
अणु
	अक्षर *this_opt, *options;
	पूर्णांक num_panels = ARRAY_SIZE(known_lcd_panels);

	अगर (num_panels <= 0) अणु
		prपूर्णांक_err("No LCD panels supported by driver!");
		वापस -ENODEV;
	पूर्ण

	अगर (fb_get_options(DRIVER_NAME, &options))
		वापस -ENODEV;
	अगर (!options)
		वापस -ENODEV;

	जबतक ((this_opt = strsep(&options, ",")) != शून्य) अणु
		/* Panel option */
		अगर (!म_भेदन(this_opt, "panel:", 6)) अणु
			पूर्णांक i;
			this_opt += 6;
			क्रम (i = 0; i < num_panels; i++) अणु
				अगर (!म_भेदन(this_opt, known_lcd_panels[i].name,
					     म_माप(this_opt))) अणु
					fbdev->panel = &known_lcd_panels[i];
					fbdev->panel_idx = i;
					अवरोध;
				पूर्ण
			पूर्ण
			अगर (i >= num_panels) अणु
				prपूर्णांक_warn("Panel '%s' not supported!", this_opt);
				वापस -ENODEV;
			पूर्ण
		पूर्ण
		/* Unsupported option */
		अन्यथा
			prपूर्णांक_warn("Unsupported option \"%s\"", this_opt);
	पूर्ण

	prपूर्णांक_info("Panel=%s", fbdev->panel->name);

	वापस 0;
पूर्ण

अटल पूर्णांक au1100fb_drv_probe(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा au1100fb_device *fbdev;
	काष्ठा resource *regs_res;
	काष्ठा clk *c;

	/* Allocate new device निजी */
	fbdev = devm_kzalloc(&dev->dev, माप(*fbdev), GFP_KERNEL);
	अगर (!fbdev)
		वापस -ENOMEM;

	अगर (au1100fb_setup(fbdev))
		जाओ failed;

	platक्रमm_set_drvdata(dev, (व्योम *)fbdev);
	fbdev->dev = &dev->dev;

	/* Allocate region क्रम our रेजिस्टरs and map them */
	regs_res = platक्रमm_get_resource(dev, IORESOURCE_MEM, 0);
	अगर (!regs_res) अणु
		prपूर्णांक_err("fail to retrieve registers resource");
		वापस -EFAULT;
	पूर्ण

	au1100fb_fix.mmio_start = regs_res->start;
	au1100fb_fix.mmio_len = resource_size(regs_res);

	अगर (!devm_request_mem_region(&dev->dev,
				     au1100fb_fix.mmio_start,
				     au1100fb_fix.mmio_len,
				     DRIVER_NAME)) अणु
		prपूर्णांक_err("fail to lock memory region at 0x%08lx",
				au1100fb_fix.mmio_start);
		वापस -EBUSY;
	पूर्ण

	fbdev->regs = (काष्ठा au1100fb_regs*)KSEG1ADDR(au1100fb_fix.mmio_start);

	prपूर्णांक_dbg("Register memory map at %p", fbdev->regs);
	prपूर्णांक_dbg("phys=0x%08x, size=%d", fbdev->regs_phys, fbdev->regs_len);

	c = clk_get(शून्य, "lcd_intclk");
	अगर (!IS_ERR(c)) अणु
		fbdev->lcdclk = c;
		clk_set_rate(c, 48000000);
		clk_prepare_enable(c);
	पूर्ण

	/* Allocate the framebuffer to the maximum screen size * nbr of video buffers */
	fbdev->fb_len = fbdev->panel->xres * fbdev->panel->yres *
		  	(fbdev->panel->bpp >> 3) * AU1100FB_NBR_VIDEO_BUFFERS;

	fbdev->fb_mem = dmam_alloc_coherent(&dev->dev,
					    PAGE_ALIGN(fbdev->fb_len),
					    &fbdev->fb_phys, GFP_KERNEL);
	अगर (!fbdev->fb_mem) अणु
		prपूर्णांक_err("fail to allocate framebuffer (size: %dK))",
			  fbdev->fb_len / 1024);
		वापस -ENOMEM;
	पूर्ण

	au1100fb_fix.smem_start = fbdev->fb_phys;
	au1100fb_fix.smem_len = fbdev->fb_len;

	prपूर्णांक_dbg("Framebuffer memory map at %p", fbdev->fb_mem);
	prपूर्णांक_dbg("phys=0x%08x, size=%dK", fbdev->fb_phys, fbdev->fb_len / 1024);

	/* load the panel info पूर्णांकo the var काष्ठा */
	au1100fb_var.bits_per_pixel = fbdev->panel->bpp;
	au1100fb_var.xres = fbdev->panel->xres;
	au1100fb_var.xres_भव = au1100fb_var.xres;
	au1100fb_var.yres = fbdev->panel->yres;
	au1100fb_var.yres_भव = au1100fb_var.yres;

	fbdev->info.screen_base = fbdev->fb_mem;
	fbdev->info.fbops = &au1100fb_ops;
	fbdev->info.fix = au1100fb_fix;

	fbdev->info.pseuकरो_palette =
		devm_kसुस्मृति(&dev->dev, 16, माप(u32), GFP_KERNEL);
	अगर (!fbdev->info.pseuकरो_palette)
		वापस -ENOMEM;

	अगर (fb_alloc_cmap(&fbdev->info.cmap, AU1100_LCD_NBR_PALETTE_ENTRIES, 0) < 0) अणु
		prपूर्णांक_err("Fail to allocate colormap (%d entries)",
			   AU1100_LCD_NBR_PALETTE_ENTRIES);
		वापस -EFAULT;
	पूर्ण

	fbdev->info.var = au1100fb_var;

	/* Set h/w रेजिस्टरs */
	au1100fb_seपंचांगode(fbdev);

	/* Register new framebuffer */
	अगर (रेजिस्टर_framebuffer(&fbdev->info) < 0) अणु
		prपूर्णांक_err("cannot register new framebuffer");
		जाओ failed;
	पूर्ण

	वापस 0;

failed:
	अगर (fbdev->lcdclk) अणु
		clk_disable_unprepare(fbdev->lcdclk);
		clk_put(fbdev->lcdclk);
	पूर्ण
	अगर (fbdev->info.cmap.len != 0) अणु
		fb_dealloc_cmap(&fbdev->info.cmap);
	पूर्ण

	वापस -ENODEV;
पूर्ण

पूर्णांक au1100fb_drv_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा au1100fb_device *fbdev = शून्य;

	अगर (!dev)
		वापस -ENODEV;

	fbdev = platक्रमm_get_drvdata(dev);

#अगर !defined(CONFIG_FRAMEBUFFER_CONSOLE) && defined(CONFIG_LOGO)
	au1100fb_fb_blank(VESA_POWERDOWN, &fbdev->info);
#पूर्ण_अगर
	fbdev->regs->lcd_control &= ~LCD_CONTROL_GO;

	/* Clean up all probe data */
	unरेजिस्टर_framebuffer(&fbdev->info);

	fb_dealloc_cmap(&fbdev->info.cmap);

	अगर (fbdev->lcdclk) अणु
		clk_disable_unprepare(fbdev->lcdclk);
		clk_put(fbdev->lcdclk);
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल काष्ठा au1100fb_regs fbregs;

पूर्णांक au1100fb_drv_suspend(काष्ठा platक्रमm_device *dev, pm_message_t state)
अणु
	काष्ठा au1100fb_device *fbdev = platक्रमm_get_drvdata(dev);

	अगर (!fbdev)
		वापस 0;

	/* Blank the LCD */
	au1100fb_fb_blank(VESA_POWERDOWN, &fbdev->info);

	अगर (fbdev->lcdclk)
		clk_disable(fbdev->lcdclk);

	स_नकल(&fbregs, fbdev->regs, माप(काष्ठा au1100fb_regs));

	वापस 0;
पूर्ण

पूर्णांक au1100fb_drv_resume(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा au1100fb_device *fbdev = platक्रमm_get_drvdata(dev);

	अगर (!fbdev)
		वापस 0;

	स_नकल(fbdev->regs, &fbregs, माप(काष्ठा au1100fb_regs));

	अगर (fbdev->lcdclk)
		clk_enable(fbdev->lcdclk);

	/* Unblank the LCD */
	au1100fb_fb_blank(VESA_NO_BLANKING, &fbdev->info);

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा au1100fb_drv_suspend शून्य
#घोषणा au1100fb_drv_resume शून्य
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver au1100fb_driver = अणु
	.driver = अणु
		.name		= "au1100-lcd",
	पूर्ण,
	.probe		= au1100fb_drv_probe,
        .हटाओ		= au1100fb_drv_हटाओ,
	.suspend	= au1100fb_drv_suspend,
        .resume		= au1100fb_drv_resume,
पूर्ण;
module_platक्रमm_driver(au1100fb_driver);

MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");
