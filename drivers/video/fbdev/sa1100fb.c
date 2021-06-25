<शैली गुरु>
/*
 *  linux/drivers/video/sa1100fb.c
 *
 *  Copyright (C) 1999 Eric A. Thomas
 *   Based on acornfb.c Copyright (C) Russell King.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive क्रम
 * more details.
 *
 *	        StrongARM 1100 LCD Controller Frame Buffer Driver
 *
 * Please direct your questions and comments on this driver to the following
 * email address:
 *
 *	linux-arm-kernel@lists.arm.linux.org.uk
 *
 * Clean patches should be sent to the ARM Linux Patch System.  Please see the
 * following web page क्रम more inक्रमmation:
 *
 *	https://www.arm.linux.org.uk/developer/patches/info.shपंचांगl
 *
 * Thank you.
 *
 * Known problems:
 *	- With the Neponset plugged पूर्णांकo an Assabet, LCD घातerकरोwn
 *	  करोesn't work (LCD stays powered up).  Therefore we shouldn't
 *	  blank the screen.
 *	- We करोn't limit the CPU घड़ी rate nor the mode selection
 *	  according to the available SDRAM bandwidth.
 *
 * Other notes:
 *	- Linear grayscale palettes and the kernel.
 *	  Such code करोes not beदीर्घ in the kernel.  The kernel frame buffer
 *	  drivers करो not expect a linear colourmap, but a colourmap based on
 *	  the VT100 standard mapping.
 *
 *	  If your _userspace_ requires a linear colourmap, then the setup of
 *	  such a colourmap beदीर्घs _in userspace_, not in the kernel.  Code
 *	  to set the colourmap correctly from user space has been sent to
 *	  David Neuer.  It's around 8 lines of C code, plus another 4 to
 *	  detect अगर we are using grayscale.
 *
 *	- The following must never be specअगरied in a panel definition:
 *	     LCCR0_LtlEnd, LCCR3_PixClkDiv, LCCR3_VrtSnchL, LCCR3_HorSnchL
 *
 *	- The following should be specअगरied:
 *	     either LCCR0_Color or LCCR0_Mono
 *	     either LCCR0_Sngl or LCCR0_Dual
 *	     either LCCR0_Act or LCCR0_Pas
 *	     either LCCR3_OutEnH or LCCD3_OutEnL
 *	     either LCCR3_PixRsEdg or LCCR3_PixFlEdg
 *	     either LCCR3_ACBsDiv or LCCR3_ACBsCntOff
 *
 * Code Status:
 * 1999/04/01:
 *	- Driver appears to be working क्रम Brutus 320x200x8bpp mode.  Other
 *	  resolutions are working, but only the 8bpp mode is supported.
 *	  Changes need to be made to the palette encode and decode routines
 *	  to support 4 and 16 bpp modes.  
 *	  Driver is not deचिन्हित to be a module.  The FrameBuffer is अटलally
 *	  allocated since dynamic allocation of a 300k buffer cannot be 
 *	  guaranteed. 
 *
 * 1999/06/17:
 *	- FrameBuffer memory is now allocated at run-समय when the
 *	  driver is initialized.    
 *
 * 2000/04/10: Nicolas Pitre <nico@fluxnic.net>
 *	- Big cleanup क्रम dynamic selection of machine type at run समय.
 *
 * 2000/07/19: Jamey Hicks <jamey@crl.dec.com>
 *	- Support क्रम Bitsy aka Compaq iPAQ H3600 added.
 *
 * 2000/08/07: Tak-Shing Chan <tchan.rd@idthk.com>
 *	       Jeff Sutherland <jsutherland@accelent.com>
 *	- Resolved an issue caused by a change made to the Assabet's PLD 
 *	  earlier this year which broke the framebuffer driver क्रम newer 
 *	  Phase 4 Assabets.  Some other parameters were changed to optimize
 *	  क्रम the Sharp display.
 *
 * 2000/08/09: Kunihiko IMAI <imai@vasara.co.jp>
 *	- XP860 support added
 *
 * 2000/08/19: Mark Huang <mhuang@livetoy.com>
 *	- Allows standard options to be passed on the kernel command line
 *	  क्रम most common passive displays.
 *
 * 2000/08/29:
 *	- s/save_flags_cli/local_irq_save/
 *	- हटाओ unneeded extra save_flags_cli in sa1100fb_enable_lcd_controller
 *
 * 2000/10/10: Erik Mouw <J.A.K.Mouw@its.tudelft.nl>
 *	- Updated LART stuff. Fixed some minor bugs.
 *
 * 2000/10/30: Murphy Chen <murphy@mail.dialogue.com.tw>
 *	- Pangolin support added
 *
 * 2000/10/31: Roman Jordan <jor@hoeft-wessel.de>
 *	- Huw Webpanel support added
 *
 * 2000/11/23: Eric Peng <ericpeng@coventive.com>
 *	- Freebird add
 *
 * 2001/02/07: Jamey Hicks <jamey.hicks@compaq.com> 
 *	       Clअगरf Brake <cbrake@accelent.com>
 *	- Added PM callback
 *
 * 2001/05/26: <rmk@arm.linux.org.uk>
 *	- Fix 16bpp so that (a) we use the right colours rather than some
 *	  totally अक्रमom colour depending on what was in page 0, and (b)
 *	  we करोn't de-reference a शून्य poपूर्णांकer.
 *	- हटाओ duplicated implementation of consistent_alloc()
 *	- convert dma address types to dma_addr_t
 *	- हटाओ unused 'montype' stuff
 *	- हटाओ redundant zero inits of init_var after the initial
 *	  स_रखो.
 *	- हटाओ allow_modeset (acornfb idea करोes not beदीर्घ here)
 *
 * 2001/05/28: <rmk@arm.linux.org.uk>
 *	- massive cleanup - move machine dependent data पूर्णांकo काष्ठाures
 *	- I've left various #warnings in - अगर you see one, and know
 *	  the hardware concerned, please get in contact with me.
 *
 * 2001/05/31: <rmk@arm.linux.org.uk>
 *	- Fix LCCR1 HSW value, fix all machine type specअगरications to
 *	  keep values in line.  (Please check your machine type specs)
 *
 * 2001/06/10: <rmk@arm.linux.org.uk>
 *	- Fiddle with the LCD controller from task context only; मुख्यly
 *	  so that we can run with पूर्णांकerrupts on, and sleep.
 *	- Convert #warnings पूर्णांकo #त्रुटिs.  No pain, no gain. ;)
 *
 * 2001/06/14: <rmk@arm.linux.org.uk>
 *	- Make the palette BPS value क्रम 12bpp come out correctly.
 *	- Take notice of "greyscale" on any colour depth.
 *	- Make truecolor visuals use the RGB channel encoding inक्रमmation.
 *
 * 2001/07/02: <rmk@arm.linux.org.uk>
 *	- Fix colourmap problems.
 *
 * 2001/07/13: <abraham@2d3d.co.za>
 *	- Added support क्रम the ICP LCD-Kit01 on LART. This LCD is
 *	  manufactured by Prime View, model no V16C6448AB
 *
 * 2001/07/23: <rmk@arm.linux.org.uk>
 *	- Hand merge version from handhelds.org CVS tree.  See patch
 *	  notes क्रम 595/1 क्रम more inक्रमmation.
 *	- Drop 12bpp (it's 16bpp with dअगरferent colour रेजिस्टर mappings).
 *	- This hardware can not करो direct colour.  Thereक्रमe we करोn't
 *	  support it.
 *
 * 2001/07/27: <rmk@arm.linux.org.uk>
 *	- Halve YRES on dual scan LCDs.
 *
 * 2001/08/22: <rmk@arm.linux.org.uk>
 *	- Add b/w iPAQ pixघड़ी value.
 *
 * 2001/10/12: <rmk@arm.linux.org.uk>
 *	- Add patch 681/1 and clean up stork definitions.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>
#समावेश <linux/mm.h>
#समावेश <linux/fb.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/ioport.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/mutex.h>
#समावेश <linux/पन.स>
#समावेश <linux/clk.h>

#समावेश <video/sa1100fb.h>

#समावेश <mach/hardware.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <mach/shannon.h>

/*
 * Complain अगर VAR is out of range.
 */
#घोषणा DEBUG_VAR 1

#समावेश "sa1100fb.h"

अटल स्थिर काष्ठा sa1100fb_rgb rgb_4 = अणु
	.red	= अणु .offset = 0,  .length = 4, पूर्ण,
	.green	= अणु .offset = 0,  .length = 4, पूर्ण,
	.blue	= अणु .offset = 0,  .length = 4, पूर्ण,
	.transp	= अणु .offset = 0,  .length = 0, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा sa1100fb_rgb rgb_8 = अणु
	.red	= अणु .offset = 0,  .length = 8, पूर्ण,
	.green	= अणु .offset = 0,  .length = 8, पूर्ण,
	.blue	= अणु .offset = 0,  .length = 8, पूर्ण,
	.transp	= अणु .offset = 0,  .length = 0, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा sa1100fb_rgb def_rgb_16 = अणु
	.red	= अणु .offset = 11, .length = 5, पूर्ण,
	.green	= अणु .offset = 5,  .length = 6, पूर्ण,
	.blue	= अणु .offset = 0,  .length = 5, पूर्ण,
	.transp	= अणु .offset = 0,  .length = 0, पूर्ण,
पूर्ण;



अटल पूर्णांक sa1100fb_activate_var(काष्ठा fb_var_screeninfo *var, काष्ठा sa1100fb_info *);
अटल व्योम set_ctrlr_state(काष्ठा sa1100fb_info *fbi, u_पूर्णांक state);

अटल अंतरभूत व्योम sa1100fb_schedule_work(काष्ठा sa1100fb_info *fbi, u_पूर्णांक state)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	/*
	 * We need to handle two requests being made at the same समय.
	 * There are two important हालs:
	 *  1. When we are changing VT (C_REENABLE) जबतक unblanking (C_ENABLE)
	 *     We must perक्रमm the unblanking, which will करो our REENABLE क्रम us.
	 *  2. When we are blanking, but immediately unblank beक्रमe we have
	 *     blanked.  We करो the "REENABLE" thing here as well, just to be sure.
	 */
	अगर (fbi->task_state == C_ENABLE && state == C_REENABLE)
		state = (u_पूर्णांक) -1;
	अगर (fbi->task_state == C_DISABLE && state == C_ENABLE)
		state = C_REENABLE;

	अगर (state != (u_पूर्णांक)-1) अणु
		fbi->task_state = state;
		schedule_work(&fbi->task);
	पूर्ण
	local_irq_restore(flags);
पूर्ण

अटल अंतरभूत u_पूर्णांक chan_to_field(u_पूर्णांक chan, काष्ठा fb_bitfield *bf)
अणु
	chan &= 0xffff;
	chan >>= 16 - bf->length;
	वापस chan << bf->offset;
पूर्ण

/*
 * Convert bits-per-pixel to a hardware palette PBS value.
 */
अटल अंतरभूत u_पूर्णांक palette_pbs(काष्ठा fb_var_screeninfo *var)
अणु
	पूर्णांक ret = 0;
	चयन (var->bits_per_pixel) अणु
	हाल 4:  ret = 0 << 12;	अवरोध;
	हाल 8:  ret = 1 << 12; अवरोध;
	हाल 16: ret = 2 << 12; अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक
sa1100fb_setpalettereg(u_पूर्णांक regno, u_पूर्णांक red, u_पूर्णांक green, u_पूर्णांक blue,
		       u_पूर्णांक trans, काष्ठा fb_info *info)
अणु
	काष्ठा sa1100fb_info *fbi =
		container_of(info, काष्ठा sa1100fb_info, fb);
	u_पूर्णांक val, ret = 1;

	अगर (regno < fbi->palette_size) अणु
		val = ((red >> 4) & 0xf00);
		val |= ((green >> 8) & 0x0f0);
		val |= ((blue >> 12) & 0x00f);

		अगर (regno == 0)
			val |= palette_pbs(&fbi->fb.var);

		fbi->palette_cpu[regno] = val;
		ret = 0;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक
sa1100fb_setcolreg(u_पूर्णांक regno, u_पूर्णांक red, u_पूर्णांक green, u_पूर्णांक blue,
		   u_पूर्णांक trans, काष्ठा fb_info *info)
अणु
	काष्ठा sa1100fb_info *fbi =
		container_of(info, काष्ठा sa1100fb_info, fb);
	अचिन्हित पूर्णांक val;
	पूर्णांक ret = 1;

	/*
	 * If inverse mode was selected, invert all the colours
	 * rather than the रेजिस्टर number.  The रेजिस्टर number
	 * is what you poke पूर्णांकo the framebuffer to produce the
	 * colour you requested.
	 */
	अगर (fbi->inf->cmap_inverse) अणु
		red   = 0xffff - red;
		green = 0xffff - green;
		blue  = 0xffff - blue;
	पूर्ण

	/*
	 * If greyscale is true, then we convert the RGB value
	 * to greyscale no mater what visual we are using.
	 */
	अगर (fbi->fb.var.grayscale)
		red = green = blue = (19595 * red + 38470 * green +
					7471 * blue) >> 16;

	चयन (fbi->fb.fix.visual) अणु
	हाल FB_VISUAL_TRUECOLOR:
		/*
		 * 12 or 16-bit True Colour.  We encode the RGB value
		 * according to the RGB bitfield inक्रमmation.
		 */
		अगर (regno < 16) अणु
			val  = chan_to_field(red, &fbi->fb.var.red);
			val |= chan_to_field(green, &fbi->fb.var.green);
			val |= chan_to_field(blue, &fbi->fb.var.blue);

			fbi->pseuकरो_palette[regno] = val;
			ret = 0;
		पूर्ण
		अवरोध;

	हाल FB_VISUAL_STATIC_PSEUDOCOLOR:
	हाल FB_VISUAL_PSEUDOCOLOR:
		ret = sa1100fb_setpalettereg(regno, red, green, blue, trans, info);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_CPU_FREQ
/*
 *  sa1100fb_display_dma_period()
 *    Calculate the minimum period (in picoseconds) between two DMA
 *    requests क्रम the LCD controller.  If we hit this, it means we're
 *    करोing nothing but LCD DMA.
 */
अटल अंतरभूत अचिन्हित पूर्णांक sa1100fb_display_dma_period(काष्ठा fb_var_screeninfo *var)
अणु
	/*
	 * Period = pixघड़ी * bits_per_byte * bytes_per_transfer
	 *		/ memory_bits_per_pixel;
	 */
	वापस var->pixघड़ी * 8 * 16 / var->bits_per_pixel;
पूर्ण
#पूर्ण_अगर

/*
 *  sa1100fb_check_var():
 *    Round up in the following order: bits_per_pixel, xres,
 *    yres, xres_भव, yres_भव, xoffset, yoffset, grayscale,
 *    bitfields, horizontal timing, vertical timing.
 */
अटल पूर्णांक
sa1100fb_check_var(काष्ठा fb_var_screeninfo *var, काष्ठा fb_info *info)
अणु
	काष्ठा sa1100fb_info *fbi =
		container_of(info, काष्ठा sa1100fb_info, fb);
	पूर्णांक rgbidx;

	अगर (var->xres < MIN_XRES)
		var->xres = MIN_XRES;
	अगर (var->yres < MIN_YRES)
		var->yres = MIN_YRES;
	अगर (var->xres > fbi->inf->xres)
		var->xres = fbi->inf->xres;
	अगर (var->yres > fbi->inf->yres)
		var->yres = fbi->inf->yres;
	var->xres_भव = max(var->xres_भव, var->xres);
	var->yres_भव = max(var->yres_भव, var->yres);

	dev_dbg(fbi->dev, "var->bits_per_pixel=%d\n", var->bits_per_pixel);
	चयन (var->bits_per_pixel) अणु
	हाल 4:
		rgbidx = RGB_4;
		अवरोध;
	हाल 8:
		rgbidx = RGB_8;
		अवरोध;
	हाल 16:
		rgbidx = RGB_16;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/*
	 * Copy the RGB parameters क्रम this display
	 * from the machine specअगरic parameters.
	 */
	var->red    = fbi->rgb[rgbidx]->red;
	var->green  = fbi->rgb[rgbidx]->green;
	var->blue   = fbi->rgb[rgbidx]->blue;
	var->transp = fbi->rgb[rgbidx]->transp;

	dev_dbg(fbi->dev, "RGBT length = %d:%d:%d:%d\n",
		var->red.length, var->green.length, var->blue.length,
		var->transp.length);

	dev_dbg(fbi->dev, "RGBT offset = %d:%d:%d:%d\n",
		var->red.offset, var->green.offset, var->blue.offset,
		var->transp.offset);

#अगर_घोषित CONFIG_CPU_FREQ
	dev_dbg(fbi->dev, "dma period = %d ps, clock = %ld kHz\n",
		sa1100fb_display_dma_period(var),
		clk_get_rate(fbi->clk) / 1000);
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल व्योम sa1100fb_set_visual(काष्ठा sa1100fb_info *fbi, u32 visual)
अणु
	अगर (fbi->inf->set_visual)
		fbi->inf->set_visual(visual);
पूर्ण

/*
 * sa1100fb_set_par():
 *	Set the user defined part of the display क्रम the specअगरied console
 */
अटल पूर्णांक sa1100fb_set_par(काष्ठा fb_info *info)
अणु
	काष्ठा sa1100fb_info *fbi =
		container_of(info, काष्ठा sa1100fb_info, fb);
	काष्ठा fb_var_screeninfo *var = &info->var;
	अचिन्हित दीर्घ palette_mem_size;

	dev_dbg(fbi->dev, "set_par\n");

	अगर (var->bits_per_pixel == 16)
		fbi->fb.fix.visual = FB_VISUAL_TRUECOLOR;
	अन्यथा अगर (!fbi->inf->cmap_अटल)
		fbi->fb.fix.visual = FB_VISUAL_PSEUDOCOLOR;
	अन्यथा अणु
		/*
		 * Some people have weird ideas about wanting अटल
		 * pseuकरोcolor maps.  I suspect their user space
		 * applications are broken.
		 */
		fbi->fb.fix.visual = FB_VISUAL_STATIC_PSEUDOCOLOR;
	पूर्ण

	fbi->fb.fix.line_length = var->xres_भव *
				  var->bits_per_pixel / 8;
	fbi->palette_size = var->bits_per_pixel == 8 ? 256 : 16;

	palette_mem_size = fbi->palette_size * माप(u16);

	dev_dbg(fbi->dev, "palette_mem_size = 0x%08lx\n", palette_mem_size);

	fbi->palette_cpu = (u16 *)(fbi->map_cpu + PAGE_SIZE - palette_mem_size);
	fbi->palette_dma = fbi->map_dma + PAGE_SIZE - palette_mem_size;

	/*
	 * Set (any) board control रेजिस्टर to handle new color depth
	 */
	sa1100fb_set_visual(fbi, fbi->fb.fix.visual);
	sa1100fb_activate_var(var, fbi);

	वापस 0;
पूर्ण

#अगर 0
अटल पूर्णांक
sa1100fb_set_cmap(काष्ठा fb_cmap *cmap, पूर्णांक kspc, पूर्णांक con,
		  काष्ठा fb_info *info)
अणु
	काष्ठा sa1100fb_info *fbi = (काष्ठा sa1100fb_info *)info;

	/*
	 * Make sure the user isn't करोing something stupid.
	 */
	अगर (!kspc && (fbi->fb.var.bits_per_pixel == 16 || fbi->inf->cmap_अटल))
		वापस -EINVAL;

	वापस gen_set_cmap(cmap, kspc, con, info);
पूर्ण
#पूर्ण_अगर

/*
 * Formal definition of the VESA spec:
 *  On
 *  	This refers to the state of the display when it is in full operation
 *  Stand-By
 *  	This defines an optional operating state of minimal घातer reduction with
 *  	the लघुest recovery समय
 *  Suspend
 *  	This refers to a level of घातer management in which substantial घातer
 *  	reduction is achieved by the display.  The display can have a दीर्घer 
 *  	recovery समय from this state than from the Stand-by state
 *  Off
 *  	This indicates that the display is consuming the lowest level of घातer
 *  	and is non-operational. Recovery from this state may optionally require
 *  	the user to manually घातer on the monitor
 *
 *  Now, the fbdev driver adds an additional state, (blank), where they
 *  turn off the video (maybe by colormap tricks), but करोn't mess with the
 *  video itself: think of it semantically between on and Stand-By.
 *
 *  So here's what we should करो in our fbdev blank routine:
 *
 *  	VESA_NO_BLANKING (mode 0)	Video on,  front/back light on
 *  	VESA_VSYNC_SUSPEND (mode 1)  	Video on,  front/back light off
 *  	VESA_HSYNC_SUSPEND (mode 2)  	Video on,  front/back light off
 *  	VESA_POWERDOWN (mode 3)		Video off, front/back light off
 *
 *  This will match the matrox implementation.
 */
/*
 * sa1100fb_blank():
 *	Blank the display by setting all palette values to zero.  Note, the 
 * 	12 and 16 bpp modes करोn't really use the palette, so this will not
 *      blank the display in all modes.  
 */
अटल पूर्णांक sa1100fb_blank(पूर्णांक blank, काष्ठा fb_info *info)
अणु
	काष्ठा sa1100fb_info *fbi =
		container_of(info, काष्ठा sa1100fb_info, fb);
	पूर्णांक i;

	dev_dbg(fbi->dev, "sa1100fb_blank: blank=%d\n", blank);

	चयन (blank) अणु
	हाल FB_BLANK_POWERDOWN:
	हाल FB_BLANK_VSYNC_SUSPEND:
	हाल FB_BLANK_HSYNC_SUSPEND:
	हाल FB_BLANK_NORMAL:
		अगर (fbi->fb.fix.visual == FB_VISUAL_PSEUDOCOLOR ||
		    fbi->fb.fix.visual == FB_VISUAL_STATIC_PSEUDOCOLOR)
			क्रम (i = 0; i < fbi->palette_size; i++)
				sa1100fb_setpalettereg(i, 0, 0, 0, 0, info);
		sa1100fb_schedule_work(fbi, C_DISABLE);
		अवरोध;

	हाल FB_BLANK_UNBLANK:
		अगर (fbi->fb.fix.visual == FB_VISUAL_PSEUDOCOLOR ||
		    fbi->fb.fix.visual == FB_VISUAL_STATIC_PSEUDOCOLOR)
			fb_set_cmap(&fbi->fb.cmap, info);
		sa1100fb_schedule_work(fbi, C_ENABLE);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक sa1100fb_mmap(काष्ठा fb_info *info,
			 काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा sa1100fb_info *fbi =
		container_of(info, काष्ठा sa1100fb_info, fb);
	अचिन्हित दीर्घ off = vma->vm_pgoff << PAGE_SHIFT;

	अगर (off < info->fix.smem_len) अणु
		vma->vm_pgoff += 1; /* skip over the palette */
		वापस dma_mmap_wc(fbi->dev, vma, fbi->map_cpu, fbi->map_dma,
				   fbi->map_size);
	पूर्ण

	vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);

	वापस vm_iomap_memory(vma, info->fix.mmio_start, info->fix.mmio_len);
पूर्ण

अटल स्थिर काष्ठा fb_ops sa1100fb_ops = अणु
	.owner		= THIS_MODULE,
	.fb_check_var	= sa1100fb_check_var,
	.fb_set_par	= sa1100fb_set_par,
//	.fb_set_cmap	= sa1100fb_set_cmap,
	.fb_setcolreg	= sa1100fb_setcolreg,
	.fb_fillrect	= cfb_fillrect,
	.fb_copyarea	= cfb_copyarea,
	.fb_imageblit	= cfb_imageblit,
	.fb_blank	= sa1100fb_blank,
	.fb_mmap	= sa1100fb_mmap,
पूर्ण;

/*
 * Calculate the PCD value from the घड़ी rate (in picoseconds).
 * We take account of the PPCR घड़ी setting.
 */
अटल अंतरभूत अचिन्हित पूर्णांक get_pcd(काष्ठा sa1100fb_info *fbi,
		अचिन्हित पूर्णांक pixघड़ी)
अणु
	अचिन्हित पूर्णांक pcd = clk_get_rate(fbi->clk) / 100 / 1000;

	pcd *= pixघड़ी;
	pcd /= 10000000;

	वापस pcd + 1;	/* make up क्रम पूर्णांकeger math truncations */
पूर्ण

/*
 * sa1100fb_activate_var():
 *	Configures LCD Controller based on entries in var parameter.  Settings are      
 *	only written to the controller अगर changes were made.  
 */
अटल पूर्णांक sa1100fb_activate_var(काष्ठा fb_var_screeninfo *var, काष्ठा sa1100fb_info *fbi)
अणु
	काष्ठा sa1100fb_lcd_reg new_regs;
	u_पूर्णांक half_screen_size, yres, pcd;
	u_दीर्घ flags;

	dev_dbg(fbi->dev, "Configuring SA1100 LCD\n");

	dev_dbg(fbi->dev, "var: xres=%d hslen=%d lm=%d rm=%d\n",
		var->xres, var->hsync_len,
		var->left_margin, var->right_margin);
	dev_dbg(fbi->dev, "var: yres=%d vslen=%d um=%d bm=%d\n",
		var->yres, var->vsync_len,
		var->upper_margin, var->lower_margin);

#अगर DEBUG_VAR
	अगर (var->xres < 16        || var->xres > 1024)
		dev_err(fbi->dev, "%s: invalid xres %d\n",
			fbi->fb.fix.id, var->xres);
	अगर (var->hsync_len < 1    || var->hsync_len > 64)
		dev_err(fbi->dev, "%s: invalid hsync_len %d\n",
			fbi->fb.fix.id, var->hsync_len);
	अगर (var->left_margin < 1  || var->left_margin > 255)
		dev_err(fbi->dev, "%s: invalid left_margin %d\n",
			fbi->fb.fix.id, var->left_margin);
	अगर (var->right_margin < 1 || var->right_margin > 255)
		dev_err(fbi->dev, "%s: invalid right_margin %d\n",
			fbi->fb.fix.id, var->right_margin);
	अगर (var->yres < 1         || var->yres > 1024)
		dev_err(fbi->dev, "%s: invalid yres %d\n",
			fbi->fb.fix.id, var->yres);
	अगर (var->vsync_len < 1    || var->vsync_len > 64)
		dev_err(fbi->dev, "%s: invalid vsync_len %d\n",
			fbi->fb.fix.id, var->vsync_len);
	अगर (var->upper_margin < 0 || var->upper_margin > 255)
		dev_err(fbi->dev, "%s: invalid upper_margin %d\n",
			fbi->fb.fix.id, var->upper_margin);
	अगर (var->lower_margin < 0 || var->lower_margin > 255)
		dev_err(fbi->dev, "%s: invalid lower_margin %d\n",
			fbi->fb.fix.id, var->lower_margin);
#पूर्ण_अगर

	new_regs.lccr0 = fbi->inf->lccr0 |
		LCCR0_LEN | LCCR0_LDM | LCCR0_BAM |
		LCCR0_ERM | LCCR0_LtlEnd | LCCR0_DMADel(0);

	new_regs.lccr1 =
		LCCR1_DisWdth(var->xres) +
		LCCR1_HorSnchWdth(var->hsync_len) +
		LCCR1_BegLnDel(var->left_margin) +
		LCCR1_EndLnDel(var->right_margin);

	/*
	 * If we have a dual scan LCD, then we need to halve
	 * the YRES parameter.
	 */
	yres = var->yres;
	अगर (fbi->inf->lccr0 & LCCR0_Dual)
		yres /= 2;

	new_regs.lccr2 =
		LCCR2_DisHght(yres) +
		LCCR2_VrtSnchWdth(var->vsync_len) +
		LCCR2_BegFrmDel(var->upper_margin) +
		LCCR2_EndFrmDel(var->lower_margin);

	pcd = get_pcd(fbi, var->pixघड़ी);
	new_regs.lccr3 = LCCR3_PixClkDiv(pcd) | fbi->inf->lccr3 |
		(var->sync & FB_SYNC_HOR_HIGH_ACT ? LCCR3_HorSnchH : LCCR3_HorSnchL) |
		(var->sync & FB_SYNC_VERT_HIGH_ACT ? LCCR3_VrtSnchH : LCCR3_VrtSnchL);

	dev_dbg(fbi->dev, "nlccr0 = 0x%08lx\n", new_regs.lccr0);
	dev_dbg(fbi->dev, "nlccr1 = 0x%08lx\n", new_regs.lccr1);
	dev_dbg(fbi->dev, "nlccr2 = 0x%08lx\n", new_regs.lccr2);
	dev_dbg(fbi->dev, "nlccr3 = 0x%08lx\n", new_regs.lccr3);

	half_screen_size = var->bits_per_pixel;
	half_screen_size = half_screen_size * var->xres * var->yres / 16;

	/* Update shaकरोw copy atomically */
	local_irq_save(flags);
	fbi->dbar1 = fbi->palette_dma;
	fbi->dbar2 = fbi->screen_dma + half_screen_size;

	fbi->reg_lccr0 = new_regs.lccr0;
	fbi->reg_lccr1 = new_regs.lccr1;
	fbi->reg_lccr2 = new_regs.lccr2;
	fbi->reg_lccr3 = new_regs.lccr3;
	local_irq_restore(flags);

	/*
	 * Only update the रेजिस्टरs अगर the controller is enabled
	 * and something has changed.
	 */
	अगर (पढ़ोl_relaxed(fbi->base + LCCR0) != fbi->reg_lccr0 ||
	    पढ़ोl_relaxed(fbi->base + LCCR1) != fbi->reg_lccr1 ||
	    पढ़ोl_relaxed(fbi->base + LCCR2) != fbi->reg_lccr2 ||
	    पढ़ोl_relaxed(fbi->base + LCCR3) != fbi->reg_lccr3 ||
	    पढ़ोl_relaxed(fbi->base + DBAR1) != fbi->dbar1 ||
	    पढ़ोl_relaxed(fbi->base + DBAR2) != fbi->dbar2)
		sa1100fb_schedule_work(fbi, C_REENABLE);

	वापस 0;
पूर्ण

/*
 * NOTE!  The following functions are purely helpers क्रम set_ctrlr_state.
 * Do not call them directly; set_ctrlr_state करोes the correct serialisation
 * to ensure that things happen in the right way 100% of समय समय.
 *	-- rmk
 */
अटल अंतरभूत व्योम __sa1100fb_backlight_घातer(काष्ठा sa1100fb_info *fbi, पूर्णांक on)
अणु
	dev_dbg(fbi->dev, "backlight o%s\n", on ? "n" : "ff");

	अगर (fbi->inf->backlight_घातer)
		fbi->inf->backlight_घातer(on);
पूर्ण

अटल अंतरभूत व्योम __sa1100fb_lcd_घातer(काष्ठा sa1100fb_info *fbi, पूर्णांक on)
अणु
	dev_dbg(fbi->dev, "LCD power o%s\n", on ? "n" : "ff");

	अगर (fbi->inf->lcd_घातer)
		fbi->inf->lcd_घातer(on);
पूर्ण

अटल व्योम sa1100fb_setup_gpio(काष्ठा sa1100fb_info *fbi)
अणु
	u_पूर्णांक mask = 0;

	/*
	 * Enable GPIO<9:2> क्रम LCD use अगर:
	 *  1. Active display, or
	 *  2. Color Dual Passive display
	 *
	 * see table 11.8 on page 11-27 in the SA1100 manual
	 *   -- Erik.
	 *
	 * SA1110 spec update nr. 25 says we can and should
	 * clear LDD15 to 12 क्रम 4 or 8bpp modes with active
	 * panels.  
	 */
	अगर ((fbi->reg_lccr0 & LCCR0_CMS) == LCCR0_Color &&
	    (fbi->reg_lccr0 & (LCCR0_Dual|LCCR0_Act)) != 0) अणु
		mask = GPIO_LDD11 | GPIO_LDD10 | GPIO_LDD9  | GPIO_LDD8;

		अगर (fbi->fb.var.bits_per_pixel > 8 ||
		    (fbi->reg_lccr0 & (LCCR0_Dual|LCCR0_Act)) == LCCR0_Dual)
			mask |= GPIO_LDD15 | GPIO_LDD14 | GPIO_LDD13 | GPIO_LDD12;

	पूर्ण

	अगर (mask) अणु
		अचिन्हित दीर्घ flags;

		/*
		 * SA-1100 requires the GPIO direction रेजिस्टर set
		 * appropriately क्रम the alternate function.  Hence
		 * we set it here via biपंचांगask rather than excessive
		 * fiddling via the GPIO subप्रणाली - and even then
		 * we'll still have to deal with GAFR.
		 */
		local_irq_save(flags);
		GPDR |= mask;
		GAFR |= mask;
		local_irq_restore(flags);
	पूर्ण
पूर्ण

अटल व्योम sa1100fb_enable_controller(काष्ठा sa1100fb_info *fbi)
अणु
	dev_dbg(fbi->dev, "Enabling LCD controller\n");

	/*
	 * Make sure the mode bits are present in the first palette entry
	 */
	fbi->palette_cpu[0] &= 0xcfff;
	fbi->palette_cpu[0] |= palette_pbs(&fbi->fb.var);

	/* enable LCD controller घड़ी */
	clk_prepare_enable(fbi->clk);

	/* Sequence from 11.7.10 */
	ग_लिखोl_relaxed(fbi->reg_lccr3, fbi->base + LCCR3);
	ग_लिखोl_relaxed(fbi->reg_lccr2, fbi->base + LCCR2);
	ग_लिखोl_relaxed(fbi->reg_lccr1, fbi->base + LCCR1);
	ग_लिखोl_relaxed(fbi->reg_lccr0 & ~LCCR0_LEN, fbi->base + LCCR0);
	ग_लिखोl_relaxed(fbi->dbar1, fbi->base + DBAR1);
	ग_लिखोl_relaxed(fbi->dbar2, fbi->base + DBAR2);
	ग_लिखोl_relaxed(fbi->reg_lccr0 | LCCR0_LEN, fbi->base + LCCR0);

	अगर (fbi->shannon_lcden)
		gpiod_set_value(fbi->shannon_lcden, 1);

	dev_dbg(fbi->dev, "DBAR1: 0x%08x\n", पढ़ोl_relaxed(fbi->base + DBAR1));
	dev_dbg(fbi->dev, "DBAR2: 0x%08x\n", पढ़ोl_relaxed(fbi->base + DBAR2));
	dev_dbg(fbi->dev, "LCCR0: 0x%08x\n", पढ़ोl_relaxed(fbi->base + LCCR0));
	dev_dbg(fbi->dev, "LCCR1: 0x%08x\n", पढ़ोl_relaxed(fbi->base + LCCR1));
	dev_dbg(fbi->dev, "LCCR2: 0x%08x\n", पढ़ोl_relaxed(fbi->base + LCCR2));
	dev_dbg(fbi->dev, "LCCR3: 0x%08x\n", पढ़ोl_relaxed(fbi->base + LCCR3));
पूर्ण

अटल व्योम sa1100fb_disable_controller(काष्ठा sa1100fb_info *fbi)
अणु
	DECLARE_WAITQUEUE(रुको, current);
	u32 lccr0;

	dev_dbg(fbi->dev, "Disabling LCD controller\n");

	अगर (fbi->shannon_lcden)
		gpiod_set_value(fbi->shannon_lcden, 0);

	set_current_state(TASK_UNINTERRUPTIBLE);
	add_रुको_queue(&fbi->ctrlr_रुको, &रुको);

	/* Clear LCD Status Register */
	ग_लिखोl_relaxed(~0, fbi->base + LCSR);

	lccr0 = पढ़ोl_relaxed(fbi->base + LCCR0);
	lccr0 &= ~LCCR0_LDM;	/* Enable LCD Disable Done Interrupt */
	ग_लिखोl_relaxed(lccr0, fbi->base + LCCR0);
	lccr0 &= ~LCCR0_LEN;	/* Disable LCD Controller */
	ग_लिखोl_relaxed(lccr0, fbi->base + LCCR0);

	schedule_समयout(20 * HZ / 1000);
	हटाओ_रुको_queue(&fbi->ctrlr_रुको, &रुको);

	/* disable LCD controller घड़ी */
	clk_disable_unprepare(fbi->clk);
पूर्ण

/*
 *  sa1100fb_handle_irq: Handle 'LCD DONE' पूर्णांकerrupts.
 */
अटल irqवापस_t sa1100fb_handle_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा sa1100fb_info *fbi = dev_id;
	अचिन्हित पूर्णांक lcsr = पढ़ोl_relaxed(fbi->base + LCSR);

	अगर (lcsr & LCSR_LDD) अणु
		u32 lccr0 = पढ़ोl_relaxed(fbi->base + LCCR0) | LCCR0_LDM;
		ग_लिखोl_relaxed(lccr0, fbi->base + LCCR0);
		wake_up(&fbi->ctrlr_रुको);
	पूर्ण

	ग_लिखोl_relaxed(lcsr, fbi->base + LCSR);
	वापस IRQ_HANDLED;
पूर्ण

/*
 * This function must be called from task context only, since it will
 * sleep when disabling the LCD controller, or अगर we get two contending
 * processes trying to alter state.
 */
अटल व्योम set_ctrlr_state(काष्ठा sa1100fb_info *fbi, u_पूर्णांक state)
अणु
	u_पूर्णांक old_state;

	mutex_lock(&fbi->ctrlr_lock);

	old_state = fbi->state;

	/*
	 * Hack around fbcon initialisation.
	 */
	अगर (old_state == C_STARTUP && state == C_REENABLE)
		state = C_ENABLE;

	चयन (state) अणु
	हाल C_DISABLE_CLKCHANGE:
		/*
		 * Disable controller क्रम घड़ी change.  If the
		 * controller is alपढ़ोy disabled, then करो nothing.
		 */
		अगर (old_state != C_DISABLE && old_state != C_DISABLE_PM) अणु
			fbi->state = state;
			sa1100fb_disable_controller(fbi);
		पूर्ण
		अवरोध;

	हाल C_DISABLE_PM:
	हाल C_DISABLE:
		/*
		 * Disable controller
		 */
		अगर (old_state != C_DISABLE) अणु
			fbi->state = state;

			__sa1100fb_backlight_घातer(fbi, 0);
			अगर (old_state != C_DISABLE_CLKCHANGE)
				sa1100fb_disable_controller(fbi);
			__sa1100fb_lcd_घातer(fbi, 0);
		पूर्ण
		अवरोध;

	हाल C_ENABLE_CLKCHANGE:
		/*
		 * Enable the controller after घड़ी change.  Only
		 * करो this अगर we were disabled क्रम the घड़ी change.
		 */
		अगर (old_state == C_DISABLE_CLKCHANGE) अणु
			fbi->state = C_ENABLE;
			sa1100fb_enable_controller(fbi);
		पूर्ण
		अवरोध;

	हाल C_REENABLE:
		/*
		 * Re-enable the controller only अगर it was alपढ़ोy
		 * enabled.  This is so we reprogram the control
		 * रेजिस्टरs.
		 */
		अगर (old_state == C_ENABLE) अणु
			sa1100fb_disable_controller(fbi);
			sa1100fb_setup_gpio(fbi);
			sa1100fb_enable_controller(fbi);
		पूर्ण
		अवरोध;

	हाल C_ENABLE_PM:
		/*
		 * Re-enable the controller after PM.  This is not
		 * perfect - think about the हाल where we were करोing
		 * a घड़ी change, and we suspended half-way through.
		 */
		अगर (old_state != C_DISABLE_PM)
			अवरोध;
		fallthrough;

	हाल C_ENABLE:
		/*
		 * Power up the LCD screen, enable controller, and
		 * turn on the backlight.
		 */
		अगर (old_state != C_ENABLE) अणु
			fbi->state = C_ENABLE;
			sa1100fb_setup_gpio(fbi);
			__sa1100fb_lcd_घातer(fbi, 1);
			sa1100fb_enable_controller(fbi);
			__sa1100fb_backlight_घातer(fbi, 1);
		पूर्ण
		अवरोध;
	पूर्ण
	mutex_unlock(&fbi->ctrlr_lock);
पूर्ण

/*
 * Our LCD controller task (which is called when we blank or unblank)
 * via keventd.
 */
अटल व्योम sa1100fb_task(काष्ठा work_काष्ठा *w)
अणु
	काष्ठा sa1100fb_info *fbi = container_of(w, काष्ठा sa1100fb_info, task);
	u_पूर्णांक state = xchg(&fbi->task_state, -1);

	set_ctrlr_state(fbi, state);
पूर्ण

#अगर_घोषित CONFIG_CPU_FREQ
/*
 * CPU घड़ी speed change handler.  We need to adjust the LCD timing
 * parameters when the CPU घड़ी is adjusted by the घातer management
 * subप्रणाली.
 */
अटल पूर्णांक
sa1100fb_freq_transition(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ val,
			 व्योम *data)
अणु
	काष्ठा sa1100fb_info *fbi = TO_INF(nb, freq_transition);
	u_पूर्णांक pcd;

	चयन (val) अणु
	हाल CPUFREQ_PRECHANGE:
		set_ctrlr_state(fbi, C_DISABLE_CLKCHANGE);
		अवरोध;

	हाल CPUFREQ_POSTCHANGE:
		pcd = get_pcd(fbi, fbi->fb.var.pixघड़ी);
		fbi->reg_lccr3 = (fbi->reg_lccr3 & ~0xff) | LCCR3_PixClkDiv(pcd);
		set_ctrlr_state(fbi, C_ENABLE_CLKCHANGE);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM
/*
 * Power management hooks.  Note that we won't be called from IRQ context,
 * unlike the blank functions above, so we may sleep.
 */
अटल पूर्णांक sa1100fb_suspend(काष्ठा platक्रमm_device *dev, pm_message_t state)
अणु
	काष्ठा sa1100fb_info *fbi = platक्रमm_get_drvdata(dev);

	set_ctrlr_state(fbi, C_DISABLE_PM);
	वापस 0;
पूर्ण

अटल पूर्णांक sa1100fb_resume(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा sa1100fb_info *fbi = platक्रमm_get_drvdata(dev);

	set_ctrlr_state(fbi, C_ENABLE_PM);
	वापस 0;
पूर्ण
#अन्यथा
#घोषणा sa1100fb_suspend	शून्य
#घोषणा sa1100fb_resume		शून्य
#पूर्ण_अगर

/*
 * sa1100fb_map_video_memory():
 *      Allocates the DRAM memory क्रम the frame buffer.  This buffer is  
 *	remapped पूर्णांकo a non-cached, non-buffered, memory region to  
 *      allow palette and pixel ग_लिखोs to occur without flushing the 
 *      cache.  Once this area is remapped, all भव memory
 *      access to the video memory should occur at the new region.
 */
अटल पूर्णांक sa1100fb_map_video_memory(काष्ठा sa1100fb_info *fbi)
अणु
	/*
	 * We reserve one page क्रम the palette, plus the size
	 * of the framebuffer.
	 */
	fbi->map_size = PAGE_ALIGN(fbi->fb.fix.smem_len + PAGE_SIZE);
	fbi->map_cpu = dma_alloc_wc(fbi->dev, fbi->map_size, &fbi->map_dma,
				    GFP_KERNEL);

	अगर (fbi->map_cpu) अणु
		fbi->fb.screen_base = fbi->map_cpu + PAGE_SIZE;
		fbi->screen_dma = fbi->map_dma + PAGE_SIZE;
		/*
		 * FIXME: this is actually the wrong thing to place in
		 * smem_start.  But fbdev suffers from the problem that
		 * it needs an API which करोesn't exist (in this हाल,
		 * dma_ग_लिखोcombine_mmap)
		 */
		fbi->fb.fix.smem_start = fbi->screen_dma;
	पूर्ण

	वापस fbi->map_cpu ? 0 : -ENOMEM;
पूर्ण

/* Fake monspecs to fill in fbinfo काष्ठाure */
अटल स्थिर काष्ठा fb_monspecs monspecs = अणु
	.hfmin	= 30000,
	.hfmax	= 70000,
	.vfmin	= 50,
	.vfmax	= 65,
पूर्ण;


अटल काष्ठा sa1100fb_info *sa1100fb_init_fbinfo(काष्ठा device *dev)
अणु
	काष्ठा sa1100fb_mach_info *inf = dev_get_platdata(dev);
	काष्ठा sa1100fb_info *fbi;
	अचिन्हित i;

	fbi = devm_kzalloc(dev, माप(काष्ठा sa1100fb_info), GFP_KERNEL);
	अगर (!fbi)
		वापस शून्य;

	fbi->dev = dev;

	म_नकल(fbi->fb.fix.id, SA1100_NAME);

	fbi->fb.fix.type	= FB_TYPE_PACKED_PIXELS;
	fbi->fb.fix.type_aux	= 0;
	fbi->fb.fix.xpanstep	= 0;
	fbi->fb.fix.ypanstep	= 0;
	fbi->fb.fix.ywrapstep	= 0;
	fbi->fb.fix.accel	= FB_ACCEL_NONE;

	fbi->fb.var.nonstd	= 0;
	fbi->fb.var.activate	= FB_ACTIVATE_NOW;
	fbi->fb.var.height	= -1;
	fbi->fb.var.width	= -1;
	fbi->fb.var.accel_flags	= 0;
	fbi->fb.var.vmode	= FB_VMODE_NONINTERLACED;

	fbi->fb.fbops		= &sa1100fb_ops;
	fbi->fb.flags		= FBINFO_DEFAULT;
	fbi->fb.monspecs	= monspecs;
	fbi->fb.pseuकरो_palette	= fbi->pseuकरो_palette;

	fbi->rgb[RGB_4]		= &rgb_4;
	fbi->rgb[RGB_8]		= &rgb_8;
	fbi->rgb[RGB_16]	= &def_rgb_16;

	/*
	 * People just करोn't seem to get this.  We don't support
	 * anything but correct entries now, so panic अगर someone
	 * करोes something stupid.
	 */
	अगर (inf->lccr3 & (LCCR3_VrtSnchL|LCCR3_HorSnchL|0xff) ||
	    inf->pixघड़ी == 0)
		panic("sa1100fb error: invalid LCCR3 fields set or zero "
			"pixclock.");

	fbi->fb.var.xres		= inf->xres;
	fbi->fb.var.xres_भव	= inf->xres;
	fbi->fb.var.yres		= inf->yres;
	fbi->fb.var.yres_भव	= inf->yres;
	fbi->fb.var.bits_per_pixel	= inf->bpp;
	fbi->fb.var.pixघड़ी		= inf->pixघड़ी;
	fbi->fb.var.hsync_len		= inf->hsync_len;
	fbi->fb.var.left_margin		= inf->left_margin;
	fbi->fb.var.right_margin	= inf->right_margin;
	fbi->fb.var.vsync_len		= inf->vsync_len;
	fbi->fb.var.upper_margin	= inf->upper_margin;
	fbi->fb.var.lower_margin	= inf->lower_margin;
	fbi->fb.var.sync		= inf->sync;
	fbi->fb.var.grayscale		= inf->cmap_greyscale;
	fbi->state			= C_STARTUP;
	fbi->task_state			= (u_अक्षर)-1;
	fbi->fb.fix.smem_len		= inf->xres * inf->yres *
					  inf->bpp / 8;
	fbi->inf			= inf;

	/* Copy the RGB bitfield overrides */
	क्रम (i = 0; i < NR_RGB; i++)
		अगर (inf->rgb[i])
			fbi->rgb[i] = inf->rgb[i];

	init_रुकोqueue_head(&fbi->ctrlr_रुको);
	INIT_WORK(&fbi->task, sa1100fb_task);
	mutex_init(&fbi->ctrlr_lock);

	वापस fbi;
पूर्ण

अटल पूर्णांक sa1100fb_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sa1100fb_info *fbi;
	पूर्णांक ret, irq;

	अगर (!dev_get_platdata(&pdev->dev)) अणु
		dev_err(&pdev->dev, "no platform LCD data\n");
		वापस -EINVAL;
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस -EINVAL;

	fbi = sa1100fb_init_fbinfo(&pdev->dev);
	अगर (!fbi)
		वापस -ENOMEM;

	fbi->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(fbi->base))
		वापस PTR_ERR(fbi->base);

	fbi->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(fbi->clk))
		वापस PTR_ERR(fbi->clk);

	ret = devm_request_irq(&pdev->dev, irq, sa1100fb_handle_irq, 0,
			       "LCD", fbi);
	अगर (ret) अणु
		dev_err(&pdev->dev, "request_irq failed: %d\n", ret);
		वापस ret;
	पूर्ण

	fbi->shannon_lcden = gpiod_get_optional(&pdev->dev, "shannon-lcden",
						GPIOD_OUT_LOW);
	अगर (IS_ERR(fbi->shannon_lcden))
		वापस PTR_ERR(fbi->shannon_lcden);

	/* Initialize video memory */
	ret = sa1100fb_map_video_memory(fbi);
	अगर (ret)
		वापस ret;

	/*
	 * This makes sure that our colour bitfield
	 * descriptors are correctly initialised.
	 */
	sa1100fb_check_var(&fbi->fb.var, &fbi->fb);

	platक्रमm_set_drvdata(pdev, fbi);

	ret = रेजिस्टर_framebuffer(&fbi->fb);
	अगर (ret < 0) अणु
		dma_मुक्त_wc(fbi->dev, fbi->map_size, fbi->map_cpu,
			    fbi->map_dma);
		वापस ret;
	पूर्ण

#अगर_घोषित CONFIG_CPU_FREQ
	fbi->freq_transition.notअगरier_call = sa1100fb_freq_transition;
	cpufreq_रेजिस्टर_notअगरier(&fbi->freq_transition, CPUFREQ_TRANSITION_NOTIFIER);
#पूर्ण_अगर

	/* This driver cannot be unloaded at the moment */
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver sa1100fb_driver = अणु
	.probe		= sa1100fb_probe,
	.suspend	= sa1100fb_suspend,
	.resume		= sa1100fb_resume,
	.driver		= अणु
		.name	= "sa11x0-fb",
	पूर्ण,
पूर्ण;

पूर्णांक __init sa1100fb_init(व्योम)
अणु
	अगर (fb_get_options("sa1100fb", शून्य))
		वापस -ENODEV;

	वापस platक्रमm_driver_रेजिस्टर(&sa1100fb_driver);
पूर्ण

पूर्णांक __init sa1100fb_setup(अक्षर *options)
अणु
#अगर 0
	अक्षर *this_opt;

	अगर (!options || !*options)
		वापस 0;

	जबतक ((this_opt = strsep(&options, ",")) != शून्य) अणु

		अगर (!म_भेदन(this_opt, "bpp:", 4))
			current_par.max_bpp =
			    simple_म_से_अदीर्घ(this_opt + 4, शून्य, 0);

		अगर (!म_भेदन(this_opt, "lccr0:", 6))
			lcd_shaकरोw.lccr0 =
			    simple_म_से_अदीर्घ(this_opt + 6, शून्य, 0);
		अगर (!म_भेदन(this_opt, "lccr1:", 6)) अणु
			lcd_shaकरोw.lccr1 =
			    simple_म_से_अदीर्घ(this_opt + 6, शून्य, 0);
			current_par.max_xres =
			    (lcd_shaकरोw.lccr1 & 0x3ff) + 16;
		पूर्ण
		अगर (!म_भेदन(this_opt, "lccr2:", 6)) अणु
			lcd_shaकरोw.lccr2 =
			    simple_म_से_अदीर्घ(this_opt + 6, शून्य, 0);
			current_par.max_yres =
			    (lcd_shaकरोw.
			     lccr0 & LCCR0_SDS) ? ((lcd_shaकरोw.
						    lccr2 & 0x3ff) +
						   1) *
			    2 : ((lcd_shaकरोw.lccr2 & 0x3ff) + 1);
		पूर्ण
		अगर (!म_भेदन(this_opt, "lccr3:", 6))
			lcd_shaकरोw.lccr3 =
			    simple_म_से_अदीर्घ(this_opt + 6, शून्य, 0);
	पूर्ण
#पूर्ण_अगर
	वापस 0;
पूर्ण

module_init(sa1100fb_init);
MODULE_DESCRIPTION("StrongARM-1100/1110 framebuffer driver");
MODULE_LICENSE("GPL");
