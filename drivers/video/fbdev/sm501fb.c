<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* linux/drivers/video/sm501fb.c
 *
 * Copyright (c) 2006 Simtec Electronics
 *	Vincent Sanders <vince@simtec.co.uk>
 *	Ben Dooks <ben@simtec.co.uk>
 *
 * Framebuffer driver क्रम the Silicon Motion SM501
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/tty.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/fb.h>
#समावेश <linux/init.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/रुको.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/clk.h>
#समावेश <linux/console.h>
#समावेश <linux/पन.स>

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/भाग64.h>

#अगर_घोषित CONFIG_PM
#समावेश <linux/pm.h>
#पूर्ण_अगर

#समावेश <linux/sm501.h>
#समावेश <linux/sm501-regs.h>

#समावेश "edid.h"

अटल अक्षर *fb_mode = "640x480-16@60";
अटल अचिन्हित दीर्घ शेष_bpp = 16;

अटल स्थिर काष्ठा fb_videomode sm501_शेष_mode = अणु
	.refresh	= 60,
	.xres		= 640,
	.yres		= 480,
	.pixघड़ी	= 20833,
	.left_margin	= 142,
	.right_margin	= 13,
	.upper_margin	= 21,
	.lower_margin	= 1,
	.hsync_len	= 69,
	.vsync_len	= 3,
	.sync		= FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
	.vmode		= FB_VMODE_NONINTERLACED
पूर्ण;

#घोषणा NR_PALETTE	256

क्रमागत sm501_controller अणु
	HEAD_CRT	= 0,
	HEAD_PANEL	= 1,
पूर्ण;

/* SM501 memory address.
 *
 * This काष्ठाure is used to track memory usage within the SM501 framebuffer
 * allocation. The sm_addr field is stored as an offset as it is often used
 * against both the physical and mapped addresses.
 */
काष्ठा sm501_mem अणु
	अचिन्हित दीर्घ	 size;
	अचिन्हित दीर्घ	 sm_addr;	/* offset from base of sm501 fb. */
	व्योम __iomem	*k_addr;
पूर्ण;

/* निजी data that is shared between all frambuffers* */
काष्ठा sm501fb_info अणु
	काष्ठा device		*dev;
	काष्ठा fb_info		*fb[2];		/* fb info क्रम both heads */
	काष्ठा resource		*fbmem_res;	/* framebuffer resource */
	काष्ठा resource		*regs_res;	/* रेजिस्टरs resource */
	काष्ठा resource		*regs2d_res;	/* 2d रेजिस्टरs resource */
	काष्ठा sm501_platdata_fb *pdata;	/* our platक्रमm data */

	अचिन्हित दीर्घ		 pm_crt_ctrl;	/* pm: crt ctrl save */

	पूर्णांक			 irq;
	पूर्णांक			 swap_endian;	/* set to swap rgb=>bgr */
	व्योम __iomem		*regs;		/* remapped रेजिस्टरs */
	व्योम __iomem		*regs2d;	/* 2d remapped रेजिस्टरs */
	व्योम __iomem		*fbmem;		/* remapped framebuffer */
	माप_प्रकार			 fbmem_len;	/* length of remapped region */
	u8 *edid_data;
पूर्ण;

/* per-framebuffer निजी data */
काष्ठा sm501fb_par अणु
	u32			 pseuकरो_palette[16];

	क्रमागत sm501_controller	 head;
	काष्ठा sm501_mem	 cursor;
	काष्ठा sm501_mem	 screen;
	काष्ठा fb_ops		 ops;

	व्योम			*store_fb;
	व्योम			*store_cursor;
	व्योम __iomem		*cursor_regs;
	काष्ठा sm501fb_info	*info;
पूर्ण;

/* Helper functions */

अटल अंतरभूत पूर्णांक h_total(काष्ठा fb_var_screeninfo *var)
अणु
	वापस var->xres + var->left_margin +
		var->right_margin + var->hsync_len;
पूर्ण

अटल अंतरभूत पूर्णांक v_total(काष्ठा fb_var_screeninfo *var)
अणु
	वापस var->yres + var->upper_margin +
		var->lower_margin + var->vsync_len;
पूर्ण

/* sm501fb_sync_regs()
 *
 * This call is मुख्यly क्रम PCI bus प्रणालीs where we need to
 * ensure that any ग_लिखोs to the bus are completed beक्रमe the
 * next phase, or after completing a function.
*/

अटल अंतरभूत व्योम sm501fb_sync_regs(काष्ठा sm501fb_info *info)
अणु
	smc501_पढ़ोl(info->regs);
पूर्ण

/* sm501_alloc_mem
 *
 * This is an attempt to lay out memory क्रम the two framebuffers and
 * everything अन्यथा
 *
 * |fbmem_res->start					       fbmem_res->end|
 * |									     |
 * |fb[0].fix.smem_start    |	      |fb[1].fix.smem_start    |     2K	     |
 * |-> fb[0].fix.smem_len <-| spare   |-> fb[1].fix.smem_len <-|-> cursors <-|
 *
 * The "spare" space is क्रम the 2d engine data
 * the fixed is space क्रम the cursors (2x1Kbyte)
 *
 * we need to allocate memory क्रम the 2D acceleration engine
 * command list and the data क्रम the engine to deal with.
 *
 * - all allocations must be 128bit aligned
 * - cursors are 64x64x2 bits (1Kbyte)
 *
 */

#घोषणा SM501_MEMF_CURSOR		(1)
#घोषणा SM501_MEMF_PANEL		(2)
#घोषणा SM501_MEMF_CRT			(4)
#घोषणा SM501_MEMF_ACCEL		(8)

अटल पूर्णांक sm501_alloc_mem(काष्ठा sm501fb_info *inf, काष्ठा sm501_mem *mem,
			   अचिन्हित पूर्णांक why, माप_प्रकार size, u32 smem_len)
अणु
	काष्ठा sm501fb_par *par;
	काष्ठा fb_info *fbi;
	अचिन्हित पूर्णांक ptr;
	अचिन्हित पूर्णांक end;

	चयन (why) अणु
	हाल SM501_MEMF_CURSOR:
		ptr = inf->fbmem_len - size;
		inf->fbmem_len = ptr;	/* adjust available memory. */
		अवरोध;

	हाल SM501_MEMF_PANEL:
		अगर (size > inf->fbmem_len)
			वापस -ENOMEM;

		ptr = inf->fbmem_len - size;
		fbi = inf->fb[HEAD_CRT];

		/* round करोwn, some programs such as directfb करो not draw
		 * 0,0 correctly unless the start is aligned to a page start.
		 */

		अगर (ptr > 0)
			ptr &= ~(PAGE_SIZE - 1);

		अगर (fbi && ptr < smem_len)
			वापस -ENOMEM;

		अवरोध;

	हाल SM501_MEMF_CRT:
		ptr = 0;

		/* check to see अगर we have panel memory allocated
		 * which would put an limit on available memory. */

		fbi = inf->fb[HEAD_PANEL];
		अगर (fbi) अणु
			par = fbi->par;
			end = par->screen.k_addr ? par->screen.sm_addr : inf->fbmem_len;
		पूर्ण अन्यथा
			end = inf->fbmem_len;

		अगर ((ptr + size) > end)
			वापस -ENOMEM;

		अवरोध;

	हाल SM501_MEMF_ACCEL:
		fbi = inf->fb[HEAD_CRT];
		ptr = fbi ? smem_len : 0;

		fbi = inf->fb[HEAD_PANEL];
		अगर (fbi) अणु
			par = fbi->par;
			end = par->screen.sm_addr;
		पूर्ण अन्यथा
			end = inf->fbmem_len;

		अगर ((ptr + size) > end)
			वापस -ENOMEM;

		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	mem->size    = size;
	mem->sm_addr = ptr;
	mem->k_addr  = inf->fbmem + ptr;

	dev_dbg(inf->dev, "%s: result %08lx, %p - %u, %zd\n",
		__func__, mem->sm_addr, mem->k_addr, why, size);

	वापस 0;
पूर्ण

/* sm501fb_ps_to_hz
 *
 * Converts a period in picoseconds to Hz.
 *
 * Note, we try to keep this in Hz to minimise rounding with
 * the limited PLL settings on the SM501.
*/

अटल अचिन्हित दीर्घ sm501fb_ps_to_hz(अचिन्हित दीर्घ psvalue)
अणु
	अचिन्हित दीर्घ दीर्घ numerator=1000000000000ULL;

	/* 10^12 / picosecond period gives frequency in Hz */
	करो_भाग(numerator, psvalue);
	वापस (अचिन्हित दीर्घ)numerator;
पूर्ण

/* sm501fb_hz_to_ps is identical to the opposite transक्रमm */

#घोषणा sm501fb_hz_to_ps(x) sm501fb_ps_to_hz(x)

/* sm501fb_setup_gamma
 *
 * Programs a linear 1.0 gamma ramp in हाल the gamma
 * correction is enabled without programming anything अन्यथा.
*/

अटल व्योम sm501fb_setup_gamma(काष्ठा sm501fb_info *fbi,
				अचिन्हित दीर्घ palette)
अणु
	अचिन्हित दीर्घ value = 0;
	पूर्णांक offset;

	/* set gamma values */
	क्रम (offset = 0; offset < 256 * 4; offset += 4) अणु
		smc501_ग_लिखोl(value, fbi->regs + palette + offset);
		value += 0x010101; 	/* Advance RGB by 1,1,1.*/
	पूर्ण
पूर्ण

/* sm501fb_check_var
 *
 * check common variables क्रम both panel and crt
*/

अटल पूर्णांक sm501fb_check_var(काष्ठा fb_var_screeninfo *var,
			     काष्ठा fb_info *info)
अणु
	काष्ठा sm501fb_par  *par = info->par;
	काष्ठा sm501fb_info *sm  = par->info;
	अचिन्हित दीर्घ पंचांगp;

	/* check we can fit these values पूर्णांकo the रेजिस्टरs */

	अगर (var->hsync_len > 255 || var->vsync_len > 63)
		वापस -EINVAL;

	/* hdisplay end and hsync start */
	अगर ((var->xres + var->right_margin) > 4096)
		वापस -EINVAL;

	/* vdisplay end and vsync start */
	अगर ((var->yres + var->lower_margin) > 2048)
		वापस -EINVAL;

	/* hard limits of device */

	अगर (h_total(var) > 4096 || v_total(var) > 2048)
		वापस -EINVAL;

	/* check our line length is going to be 128 bit aligned */

	पंचांगp = (var->xres * var->bits_per_pixel) / 8;
	अगर ((पंचांगp & 15) != 0)
		वापस -EINVAL;

	/* check the भव size */

	अगर (var->xres_भव > 4096 || var->yres_भव > 2048)
		वापस -EINVAL;

	/* can cope with 8,16 or 32bpp */

	अगर (var->bits_per_pixel <= 8)
		var->bits_per_pixel = 8;
	अन्यथा अगर (var->bits_per_pixel <= 16)
		var->bits_per_pixel = 16;
	अन्यथा अगर (var->bits_per_pixel == 24)
		var->bits_per_pixel = 32;

	/* set r/g/b positions and validate bpp */
	चयन(var->bits_per_pixel) अणु
	हाल 8:
		var->red.length		= var->bits_per_pixel;
		var->red.offset		= 0;
		var->green.length	= var->bits_per_pixel;
		var->green.offset	= 0;
		var->blue.length	= var->bits_per_pixel;
		var->blue.offset	= 0;
		var->transp.length	= 0;
		var->transp.offset	= 0;

		अवरोध;

	हाल 16:
		अगर (sm->pdata->flags & SM501_FBPD_SWAP_FB_ENDIAN) अणु
			var->blue.offset	= 11;
			var->green.offset	= 5;
			var->red.offset		= 0;
		पूर्ण अन्यथा अणु
			var->red.offset		= 11;
			var->green.offset	= 5;
			var->blue.offset	= 0;
		पूर्ण
		var->transp.offset	= 0;

		var->red.length		= 5;
		var->green.length	= 6;
		var->blue.length	= 5;
		var->transp.length	= 0;
		अवरोध;

	हाल 32:
		अगर (sm->pdata->flags & SM501_FBPD_SWAP_FB_ENDIAN) अणु
			var->transp.offset	= 0;
			var->red.offset		= 8;
			var->green.offset	= 16;
			var->blue.offset	= 24;
		पूर्ण अन्यथा अणु
			var->transp.offset	= 24;
			var->red.offset		= 16;
			var->green.offset	= 8;
			var->blue.offset	= 0;
		पूर्ण

		var->red.length		= 8;
		var->green.length	= 8;
		var->blue.length	= 8;
		var->transp.length	= 0;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * sm501fb_check_var_crt():
 *
 * check the parameters क्रम the CRT head, and either bring them
 * back पूर्णांकo range, or वापस -EINVAL.
*/

अटल पूर्णांक sm501fb_check_var_crt(काष्ठा fb_var_screeninfo *var,
				 काष्ठा fb_info *info)
अणु
	वापस sm501fb_check_var(var, info);
पूर्ण

/* sm501fb_check_var_pnl():
 *
 * check the parameters क्रम the CRT head, and either bring them
 * back पूर्णांकo range, or वापस -EINVAL.
*/

अटल पूर्णांक sm501fb_check_var_pnl(काष्ठा fb_var_screeninfo *var,
				 काष्ठा fb_info *info)
अणु
	वापस sm501fb_check_var(var, info);
पूर्ण

/* sm501fb_set_par_common
 *
 * set common रेजिस्टरs क्रम framebuffers
*/

अटल पूर्णांक sm501fb_set_par_common(काष्ठा fb_info *info,
				  काष्ठा fb_var_screeninfo *var)
अणु
	काष्ठा sm501fb_par  *par = info->par;
	काष्ठा sm501fb_info *fbi = par->info;
	अचिन्हित दीर्घ pixघड़ी;      /* pixelघड़ी in Hz */
	अचिन्हित दीर्घ sm501pixघड़ी; /* pixelघड़ी the 501 can achieve in Hz */
	अचिन्हित पूर्णांक mem_type;
	अचिन्हित पूर्णांक घड़ी_प्रकारype;
	अचिन्हित पूर्णांक head_addr;
	अचिन्हित पूर्णांक smem_len;

	dev_dbg(fbi->dev, "%s: %dx%d, bpp = %d, virtual %dx%d\n",
		__func__, var->xres, var->yres, var->bits_per_pixel,
		var->xres_भव, var->yres_भव);

	चयन (par->head) अणु
	हाल HEAD_CRT:
		mem_type = SM501_MEMF_CRT;
		घड़ी_प्रकारype = SM501_CLOCK_V2XCLK;
		head_addr = SM501_DC_CRT_FB_ADDR;
		अवरोध;

	हाल HEAD_PANEL:
		mem_type = SM501_MEMF_PANEL;
		घड़ी_प्रकारype = SM501_CLOCK_P2XCLK;
		head_addr = SM501_DC_PANEL_FB_ADDR;
		अवरोध;

	शेष:
		mem_type = 0;		/* stop compiler warnings */
		head_addr = 0;
		घड़ी_प्रकारype = 0;
	पूर्ण

	चयन (var->bits_per_pixel) अणु
	हाल 8:
		info->fix.visual = FB_VISUAL_PSEUDOCOLOR;
		अवरोध;

	हाल 16:
		info->fix.visual = FB_VISUAL_TRUECOLOR;
		अवरोध;

	हाल 32:
		info->fix.visual = FB_VISUAL_TRUECOLOR;
		अवरोध;
	पूर्ण

	/* allocate fb memory within 501 */
	info->fix.line_length = (var->xres_भव * var->bits_per_pixel)/8;
	smem_len = info->fix.line_length * var->yres_भव;

	dev_dbg(fbi->dev, "%s: line length = %u\n", __func__,
		info->fix.line_length);

	अगर (sm501_alloc_mem(fbi, &par->screen, mem_type, smem_len, smem_len)) अणु
		dev_err(fbi->dev, "no memory available\n");
		वापस -ENOMEM;
	पूर्ण

	mutex_lock(&info->mm_lock);
	info->fix.smem_start = fbi->fbmem_res->start + par->screen.sm_addr;
	info->fix.smem_len   = smem_len;
	mutex_unlock(&info->mm_lock);

	info->screen_base = fbi->fbmem + par->screen.sm_addr;
	info->screen_size = info->fix.smem_len;

	/* set start of framebuffer to the screen */

	smc501_ग_लिखोl(par->screen.sm_addr | SM501_ADDR_FLIP,
			fbi->regs + head_addr);

	/* program CRT घड़ी  */

	pixघड़ी = sm501fb_ps_to_hz(var->pixघड़ी);

	sm501pixघड़ी = sm501_set_घड़ी(fbi->dev->parent, घड़ी_प्रकारype,
					pixघड़ी);

	/* update fb layer with actual घड़ी used */
	var->pixघड़ी = sm501fb_hz_to_ps(sm501pixघड़ी);

	dev_dbg(fbi->dev, "%s: pixclock(ps) = %u, pixclock(Hz)  = %lu, "
	       "sm501pixclock = %lu,  error = %ld%%\n",
	       __func__, var->pixघड़ी, pixघड़ी, sm501pixघड़ी,
	       ((pixघड़ी - sm501pixघड़ी)*100)/pixघड़ी);

	वापस 0;
पूर्ण

/* sm501fb_set_par_geometry
 *
 * set the geometry रेजिस्टरs क्रम specअगरied framebuffer.
*/

अटल व्योम sm501fb_set_par_geometry(काष्ठा fb_info *info,
				     काष्ठा fb_var_screeninfo *var)
अणु
	काष्ठा sm501fb_par  *par = info->par;
	काष्ठा sm501fb_info *fbi = par->info;
	व्योम __iomem *base = fbi->regs;
	अचिन्हित दीर्घ reg;

	अगर (par->head == HEAD_CRT)
		base += SM501_DC_CRT_H_TOT;
	अन्यथा
		base += SM501_DC_PANEL_H_TOT;

	/* set framebuffer width and display width */

	reg = info->fix.line_length;
	reg |= ((var->xres * var->bits_per_pixel)/8) << 16;

	smc501_ग_लिखोl(reg, fbi->regs + (par->head == HEAD_CRT ?
		    SM501_DC_CRT_FB_OFFSET :  SM501_DC_PANEL_FB_OFFSET));

	/* program horizontal total */

	reg  = (h_total(var) - 1) << 16;
	reg |= (var->xres - 1);

	smc501_ग_लिखोl(reg, base + SM501_OFF_DC_H_TOT);

	/* program horizontal sync */

	reg  = var->hsync_len << 16;
	reg |= var->xres + var->right_margin - 1;

	smc501_ग_लिखोl(reg, base + SM501_OFF_DC_H_SYNC);

	/* program vertical total */

	reg  = (v_total(var) - 1) << 16;
	reg |= (var->yres - 1);

	smc501_ग_लिखोl(reg, base + SM501_OFF_DC_V_TOT);

	/* program vertical sync */
	reg  = var->vsync_len << 16;
	reg |= var->yres + var->lower_margin - 1;

	smc501_ग_लिखोl(reg, base + SM501_OFF_DC_V_SYNC);
पूर्ण

/* sm501fb_pan_crt
 *
 * pan the CRT display output within an भव framebuffer
*/

अटल पूर्णांक sm501fb_pan_crt(काष्ठा fb_var_screeninfo *var,
			   काष्ठा fb_info *info)
अणु
	काष्ठा sm501fb_par  *par = info->par;
	काष्ठा sm501fb_info *fbi = par->info;
	अचिन्हित पूर्णांक bytes_pixel = info->var.bits_per_pixel / 8;
	अचिन्हित दीर्घ reg;
	अचिन्हित दीर्घ xoffs;

	xoffs = var->xoffset * bytes_pixel;

	reg = smc501_पढ़ोl(fbi->regs + SM501_DC_CRT_CONTROL);

	reg &= ~SM501_DC_CRT_CONTROL_PIXEL_MASK;
	reg |= ((xoffs & 15) / bytes_pixel) << 4;
	smc501_ग_लिखोl(reg, fbi->regs + SM501_DC_CRT_CONTROL);

	reg = (par->screen.sm_addr + xoffs +
	       var->yoffset * info->fix.line_length);
	smc501_ग_लिखोl(reg | SM501_ADDR_FLIP, fbi->regs + SM501_DC_CRT_FB_ADDR);

	sm501fb_sync_regs(fbi);
	वापस 0;
पूर्ण

/* sm501fb_pan_pnl
 *
 * pan the panel display output within an भव framebuffer
*/

अटल पूर्णांक sm501fb_pan_pnl(काष्ठा fb_var_screeninfo *var,
			   काष्ठा fb_info *info)
अणु
	काष्ठा sm501fb_par  *par = info->par;
	काष्ठा sm501fb_info *fbi = par->info;
	अचिन्हित दीर्घ reg;

	reg = var->xoffset | (info->var.xres_भव << 16);
	smc501_ग_लिखोl(reg, fbi->regs + SM501_DC_PANEL_FB_WIDTH);

	reg = var->yoffset | (info->var.yres_भव << 16);
	smc501_ग_लिखोl(reg, fbi->regs + SM501_DC_PANEL_FB_HEIGHT);

	sm501fb_sync_regs(fbi);
	वापस 0;
पूर्ण

/* sm501fb_set_par_crt
 *
 * Set the CRT video mode from the fb_info काष्ठाure
*/

अटल पूर्णांक sm501fb_set_par_crt(काष्ठा fb_info *info)
अणु
	काष्ठा sm501fb_par  *par = info->par;
	काष्ठा sm501fb_info *fbi = par->info;
	काष्ठा fb_var_screeninfo *var = &info->var;
	अचिन्हित दीर्घ control;       /* control रेजिस्टर */
	पूर्णांक ret;

	/* activate new configuration */

	dev_dbg(fbi->dev, "%s(%p)\n", __func__, info);

	/* enable CRT DAC - note 0 is on!*/
	sm501_misc_control(fbi->dev->parent, 0, SM501_MISC_DAC_POWER);

	control = smc501_पढ़ोl(fbi->regs + SM501_DC_CRT_CONTROL);

	control &= (SM501_DC_CRT_CONTROL_PIXEL_MASK |
		    SM501_DC_CRT_CONTROL_GAMMA |
		    SM501_DC_CRT_CONTROL_BLANK |
		    SM501_DC_CRT_CONTROL_SEL |
		    SM501_DC_CRT_CONTROL_CP |
		    SM501_DC_CRT_CONTROL_TVP);

	/* set the sync polarities beक्रमe we check data source  */

	अगर ((var->sync & FB_SYNC_HOR_HIGH_ACT) == 0)
		control |= SM501_DC_CRT_CONTROL_HSP;

	अगर ((var->sync & FB_SYNC_VERT_HIGH_ACT) == 0)
		control |= SM501_DC_CRT_CONTROL_VSP;

	अगर ((control & SM501_DC_CRT_CONTROL_SEL) == 0) अणु
		/* the head is displaying panel data... */

		sm501_alloc_mem(fbi, &par->screen, SM501_MEMF_CRT, 0,
				info->fix.smem_len);
		जाओ out_update;
	पूर्ण

	ret = sm501fb_set_par_common(info, var);
	अगर (ret) अणु
		dev_err(fbi->dev, "failed to set common parameters\n");
		वापस ret;
	पूर्ण

	sm501fb_pan_crt(var, info);
	sm501fb_set_par_geometry(info, var);

	control |= SM501_FIFO_3;	/* fill अगर >3 मुक्त slots */

	चयन(var->bits_per_pixel) अणु
	हाल 8:
		control |= SM501_DC_CRT_CONTROL_8BPP;
		अवरोध;

	हाल 16:
		control |= SM501_DC_CRT_CONTROL_16BPP;
		sm501fb_setup_gamma(fbi, SM501_DC_CRT_PALETTE);
		अवरोध;

	हाल 32:
		control |= SM501_DC_CRT_CONTROL_32BPP;
		sm501fb_setup_gamma(fbi, SM501_DC_CRT_PALETTE);
		अवरोध;

	शेष:
		BUG();
	पूर्ण

	control |= SM501_DC_CRT_CONTROL_SEL;	/* CRT displays CRT data */
	control |= SM501_DC_CRT_CONTROL_TE;	/* enable CRT timing */
	control |= SM501_DC_CRT_CONTROL_ENABLE;	/* enable CRT plane */

 out_update:
	dev_dbg(fbi->dev, "new control is %08lx\n", control);

	smc501_ग_लिखोl(control, fbi->regs + SM501_DC_CRT_CONTROL);
	sm501fb_sync_regs(fbi);

	वापस 0;
पूर्ण

अटल व्योम sm501fb_panel_घातer(काष्ठा sm501fb_info *fbi, पूर्णांक to)
अणु
	अचिन्हित दीर्घ control;
	व्योम __iomem *ctrl_reg = fbi->regs + SM501_DC_PANEL_CONTROL;
	काष्ठा sm501_platdata_fbsub *pd = fbi->pdata->fb_pnl;

	control = smc501_पढ़ोl(ctrl_reg);

	अगर (to && (control & SM501_DC_PANEL_CONTROL_VDD) == 0) अणु
		/* enable panel घातer */

		control |= SM501_DC_PANEL_CONTROL_VDD;	/* FPVDDEN */
		smc501_ग_लिखोl(control, ctrl_reg);
		sm501fb_sync_regs(fbi);
		mdelay(10);

		control |= SM501_DC_PANEL_CONTROL_DATA;	/* DATA */
		smc501_ग_लिखोl(control, ctrl_reg);
		sm501fb_sync_regs(fbi);
		mdelay(10);

		/* VBIASEN */

		अगर (!(pd->flags & SM501FB_FLAG_PANEL_NO_VBIASEN)) अणु
			अगर (pd->flags & SM501FB_FLAG_PANEL_INV_VBIASEN)
				control &= ~SM501_DC_PANEL_CONTROL_BIAS;
			अन्यथा
				control |= SM501_DC_PANEL_CONTROL_BIAS;

			smc501_ग_लिखोl(control, ctrl_reg);
			sm501fb_sync_regs(fbi);
			mdelay(10);
		पूर्ण

		अगर (!(pd->flags & SM501FB_FLAG_PANEL_NO_FPEN)) अणु
			अगर (pd->flags & SM501FB_FLAG_PANEL_INV_FPEN)
				control &= ~SM501_DC_PANEL_CONTROL_FPEN;
			अन्यथा
				control |= SM501_DC_PANEL_CONTROL_FPEN;

			smc501_ग_लिखोl(control, ctrl_reg);
			sm501fb_sync_regs(fbi);
			mdelay(10);
		पूर्ण
	पूर्ण अन्यथा अगर (!to && (control & SM501_DC_PANEL_CONTROL_VDD) != 0) अणु
		/* disable panel घातer */
		अगर (!(pd->flags & SM501FB_FLAG_PANEL_NO_FPEN)) अणु
			अगर (pd->flags & SM501FB_FLAG_PANEL_INV_FPEN)
				control |= SM501_DC_PANEL_CONTROL_FPEN;
			अन्यथा
				control &= ~SM501_DC_PANEL_CONTROL_FPEN;

			smc501_ग_लिखोl(control, ctrl_reg);
			sm501fb_sync_regs(fbi);
			mdelay(10);
		पूर्ण

		अगर (!(pd->flags & SM501FB_FLAG_PANEL_NO_VBIASEN)) अणु
			अगर (pd->flags & SM501FB_FLAG_PANEL_INV_VBIASEN)
				control |= SM501_DC_PANEL_CONTROL_BIAS;
			अन्यथा
				control &= ~SM501_DC_PANEL_CONTROL_BIAS;

			smc501_ग_लिखोl(control, ctrl_reg);
			sm501fb_sync_regs(fbi);
			mdelay(10);
		पूर्ण

		control &= ~SM501_DC_PANEL_CONTROL_DATA;
		smc501_ग_लिखोl(control, ctrl_reg);
		sm501fb_sync_regs(fbi);
		mdelay(10);

		control &= ~SM501_DC_PANEL_CONTROL_VDD;
		smc501_ग_लिखोl(control, ctrl_reg);
		sm501fb_sync_regs(fbi);
		mdelay(10);
	पूर्ण

	sm501fb_sync_regs(fbi);
पूर्ण

/* sm501fb_set_par_pnl
 *
 * Set the panel video mode from the fb_info काष्ठाure
*/

अटल पूर्णांक sm501fb_set_par_pnl(काष्ठा fb_info *info)
अणु
	काष्ठा sm501fb_par  *par = info->par;
	काष्ठा sm501fb_info *fbi = par->info;
	काष्ठा fb_var_screeninfo *var = &info->var;
	अचिन्हित दीर्घ control;
	अचिन्हित दीर्घ reg;
	पूर्णांक ret;

	dev_dbg(fbi->dev, "%s(%p)\n", __func__, info);

	/* activate this new configuration */

	ret = sm501fb_set_par_common(info, var);
	अगर (ret)
		वापस ret;

	sm501fb_pan_pnl(var, info);
	sm501fb_set_par_geometry(info, var);

	/* update control रेजिस्टर */

	control = smc501_पढ़ोl(fbi->regs + SM501_DC_PANEL_CONTROL);
	control &= (SM501_DC_PANEL_CONTROL_GAMMA |
		    SM501_DC_PANEL_CONTROL_VDD  |
		    SM501_DC_PANEL_CONTROL_DATA |
		    SM501_DC_PANEL_CONTROL_BIAS |
		    SM501_DC_PANEL_CONTROL_FPEN |
		    SM501_DC_PANEL_CONTROL_CP |
		    SM501_DC_PANEL_CONTROL_CK |
		    SM501_DC_PANEL_CONTROL_HP |
		    SM501_DC_PANEL_CONTROL_VP |
		    SM501_DC_PANEL_CONTROL_HPD |
		    SM501_DC_PANEL_CONTROL_VPD);

	control |= SM501_FIFO_3;	/* fill अगर >3 मुक्त slots */

	चयन(var->bits_per_pixel) अणु
	हाल 8:
		control |= SM501_DC_PANEL_CONTROL_8BPP;
		अवरोध;

	हाल 16:
		control |= SM501_DC_PANEL_CONTROL_16BPP;
		sm501fb_setup_gamma(fbi, SM501_DC_PANEL_PALETTE);
		अवरोध;

	हाल 32:
		control |= SM501_DC_PANEL_CONTROL_32BPP;
		sm501fb_setup_gamma(fbi, SM501_DC_PANEL_PALETTE);
		अवरोध;

	शेष:
		BUG();
	पूर्ण

	smc501_ग_लिखोl(0x0, fbi->regs + SM501_DC_PANEL_PANNING_CONTROL);

	/* panel plane top left and bottom right location */

	smc501_ग_लिखोl(0x00, fbi->regs + SM501_DC_PANEL_TL_LOC);

	reg  = var->xres - 1;
	reg |= (var->yres - 1) << 16;

	smc501_ग_लिखोl(reg, fbi->regs + SM501_DC_PANEL_BR_LOC);

	/* program panel control रेजिस्टर */

	control |= SM501_DC_PANEL_CONTROL_TE;	/* enable PANEL timing */
	control |= SM501_DC_PANEL_CONTROL_EN;	/* enable PANEL gfx plane */

	अगर ((var->sync & FB_SYNC_HOR_HIGH_ACT) == 0)
		control |= SM501_DC_PANEL_CONTROL_HSP;

	अगर ((var->sync & FB_SYNC_VERT_HIGH_ACT) == 0)
		control |= SM501_DC_PANEL_CONTROL_VSP;

	smc501_ग_लिखोl(control, fbi->regs + SM501_DC_PANEL_CONTROL);
	sm501fb_sync_regs(fbi);

	/* ensure the panel पूर्णांकerface is not tristated at this poपूर्णांक */

	sm501_modअगरy_reg(fbi->dev->parent, SM501_SYSTEM_CONTROL,
			 0, SM501_SYSCTRL_PANEL_TRISTATE);

	/* घातer the panel up */
	sm501fb_panel_घातer(fbi, 1);
	वापस 0;
पूर्ण


/* chan_to_field
 *
 * convert a colour value पूर्णांकo a field position
 *
 * from pxafb.c
*/

अटल अंतरभूत अचिन्हित पूर्णांक chan_to_field(अचिन्हित पूर्णांक chan,
					 काष्ठा fb_bitfield *bf)
अणु
	chan &= 0xffff;
	chan >>= 16 - bf->length;
	वापस chan << bf->offset;
पूर्ण

/* sm501fb_setcolreg
 *
 * set the colour mapping क्रम modes that support palettised data
*/

अटल पूर्णांक sm501fb_setcolreg(अचिन्हित regno,
			     अचिन्हित red, अचिन्हित green, अचिन्हित blue,
			     अचिन्हित transp, काष्ठा fb_info *info)
अणु
	काष्ठा sm501fb_par  *par = info->par;
	काष्ठा sm501fb_info *fbi = par->info;
	व्योम __iomem *base = fbi->regs;
	अचिन्हित पूर्णांक val;

	अगर (par->head == HEAD_CRT)
		base += SM501_DC_CRT_PALETTE;
	अन्यथा
		base += SM501_DC_PANEL_PALETTE;

	चयन (info->fix.visual) अणु
	हाल FB_VISUAL_TRUECOLOR:
		/* true-colour, use pseuo-palette */

		अगर (regno < 16) अणु
			u32 *pal = par->pseuकरो_palette;

			val  = chan_to_field(red,   &info->var.red);
			val |= chan_to_field(green, &info->var.green);
			val |= chan_to_field(blue,  &info->var.blue);

			pal[regno] = val;
		पूर्ण
		अवरोध;

	हाल FB_VISUAL_PSEUDOCOLOR:
		अगर (regno < 256) अणु
			val = (red >> 8) << 16;
			val |= (green >> 8) << 8;
			val |= blue >> 8;

			smc501_ग_लिखोl(val, base + (regno * 4));
		पूर्ण

		अवरोध;

	शेष:
		वापस 1;   /* unknown type */
	पूर्ण

	वापस 0;
पूर्ण

/* sm501fb_blank_pnl
 *
 * Blank or un-blank the panel पूर्णांकerface
*/

अटल पूर्णांक sm501fb_blank_pnl(पूर्णांक blank_mode, काष्ठा fb_info *info)
अणु
	काष्ठा sm501fb_par  *par = info->par;
	काष्ठा sm501fb_info *fbi = par->info;

	dev_dbg(fbi->dev, "%s(mode=%d, %p)\n", __func__, blank_mode, info);

	चयन (blank_mode) अणु
	हाल FB_BLANK_POWERDOWN:
		sm501fb_panel_घातer(fbi, 0);
		अवरोध;

	हाल FB_BLANK_UNBLANK:
		sm501fb_panel_घातer(fbi, 1);
		अवरोध;

	हाल FB_BLANK_NORMAL:
	हाल FB_BLANK_VSYNC_SUSPEND:
	हाल FB_BLANK_HSYNC_SUSPEND:
	शेष:
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

/* sm501fb_blank_crt
 *
 * Blank or un-blank the crt पूर्णांकerface
*/

अटल पूर्णांक sm501fb_blank_crt(पूर्णांक blank_mode, काष्ठा fb_info *info)
अणु
	काष्ठा sm501fb_par  *par = info->par;
	काष्ठा sm501fb_info *fbi = par->info;
	अचिन्हित दीर्घ ctrl;

	dev_dbg(fbi->dev, "%s(mode=%d, %p)\n", __func__, blank_mode, info);

	ctrl = smc501_पढ़ोl(fbi->regs + SM501_DC_CRT_CONTROL);

	चयन (blank_mode) अणु
	हाल FB_BLANK_POWERDOWN:
		ctrl &= ~SM501_DC_CRT_CONTROL_ENABLE;
		sm501_misc_control(fbi->dev->parent, SM501_MISC_DAC_POWER, 0);
		fallthrough;

	हाल FB_BLANK_NORMAL:
		ctrl |= SM501_DC_CRT_CONTROL_BLANK;
		अवरोध;

	हाल FB_BLANK_UNBLANK:
		ctrl &= ~SM501_DC_CRT_CONTROL_BLANK;
		ctrl |=  SM501_DC_CRT_CONTROL_ENABLE;
		sm501_misc_control(fbi->dev->parent, 0, SM501_MISC_DAC_POWER);
		अवरोध;

	हाल FB_BLANK_VSYNC_SUSPEND:
	हाल FB_BLANK_HSYNC_SUSPEND:
	शेष:
		वापस 1;

	पूर्ण

	smc501_ग_लिखोl(ctrl, fbi->regs + SM501_DC_CRT_CONTROL);
	sm501fb_sync_regs(fbi);

	वापस 0;
पूर्ण

/* sm501fb_cursor
 *
 * set or change the hardware cursor parameters
*/

अटल पूर्णांक sm501fb_cursor(काष्ठा fb_info *info, काष्ठा fb_cursor *cursor)
अणु
	काष्ठा sm501fb_par  *par = info->par;
	काष्ठा sm501fb_info *fbi = par->info;
	व्योम __iomem *base = fbi->regs;
	अचिन्हित दीर्घ hwc_addr;
	अचिन्हित दीर्घ fg, bg;

	dev_dbg(fbi->dev, "%s(%p,%p)\n", __func__, info, cursor);

	अगर (par->head == HEAD_CRT)
		base += SM501_DC_CRT_HWC_BASE;
	अन्यथा
		base += SM501_DC_PANEL_HWC_BASE;

	/* check not being asked to exceed capabilities */

	अगर (cursor->image.width > 64)
		वापस -EINVAL;

	अगर (cursor->image.height > 64)
		वापस -EINVAL;

	अगर (cursor->image.depth > 1)
		वापस -EINVAL;

	hwc_addr = smc501_पढ़ोl(base + SM501_OFF_HWC_ADDR);

	अगर (cursor->enable)
		smc501_ग_लिखोl(hwc_addr | SM501_HWC_EN,
				base + SM501_OFF_HWC_ADDR);
	अन्यथा
		smc501_ग_लिखोl(hwc_addr & ~SM501_HWC_EN,
				base + SM501_OFF_HWC_ADDR);

	/* set data */
	अगर (cursor->set & FB_CUR_SETPOS) अणु
		अचिन्हित पूर्णांक x = cursor->image.dx;
		अचिन्हित पूर्णांक y = cursor->image.dy;

		अगर (x >= 2048 || y >= 2048 )
			वापस -EINVAL;

		dev_dbg(fbi->dev, "set position %d,%d\n", x, y);

		//y += cursor->image.height;

		smc501_ग_लिखोl(x | (y << 16), base + SM501_OFF_HWC_LOC);
	पूर्ण

	अगर (cursor->set & FB_CUR_SETCMAP) अणु
		अचिन्हित पूर्णांक bg_col = cursor->image.bg_color;
		अचिन्हित पूर्णांक fg_col = cursor->image.fg_color;

		dev_dbg(fbi->dev, "%s: update cmap (%08x,%08x)\n",
			__func__, bg_col, fg_col);

		bg = ((info->cmap.red[bg_col] & 0xF8) << 8) |
			((info->cmap.green[bg_col] & 0xFC) << 3) |
			((info->cmap.blue[bg_col] & 0xF8) >> 3);

		fg = ((info->cmap.red[fg_col] & 0xF8) << 8) |
			((info->cmap.green[fg_col] & 0xFC) << 3) |
			((info->cmap.blue[fg_col] & 0xF8) >> 3);

		dev_dbg(fbi->dev, "fgcol %08lx, bgcol %08lx\n", fg, bg);

		smc501_ग_लिखोl(bg, base + SM501_OFF_HWC_COLOR_1_2);
		smc501_ग_लिखोl(fg, base + SM501_OFF_HWC_COLOR_3);
	पूर्ण

	अगर (cursor->set & FB_CUR_SETSIZE ||
	    cursor->set & (FB_CUR_SETIMAGE | FB_CUR_SETSHAPE)) अणु
		/* SM501 cursor is a two bpp 64x64 biपंचांगap this routine
		 * clears it to transparent then combines the cursor
		 * shape plane with the colour plane to set the
		 * cursor */
		पूर्णांक x, y;
		स्थिर अचिन्हित अक्षर *pcol = cursor->image.data;
		स्थिर अचिन्हित अक्षर *pmsk = cursor->mask;
		व्योम __iomem   *dst = par->cursor.k_addr;
		अचिन्हित अक्षर  dcol = 0;
		अचिन्हित अक्षर  dmsk = 0;
		अचिन्हित पूर्णांक   op;

		dev_dbg(fbi->dev, "%s: setting shape (%d,%d)\n",
			__func__, cursor->image.width, cursor->image.height);

		क्रम (op = 0; op < (64*64*2)/8; op+=4)
			smc501_ग_लिखोl(0x0, dst + op);

		क्रम (y = 0; y < cursor->image.height; y++) अणु
			क्रम (x = 0; x < cursor->image.width; x++) अणु
				अगर ((x % 8) == 0) अणु
					dcol = *pcol++;
					dmsk = *pmsk++;
				पूर्ण अन्यथा अणु
					dcol >>= 1;
					dmsk >>= 1;
				पूर्ण

				अगर (dmsk & 1) अणु
					op = (dcol & 1) ? 1 : 3;
					op <<= ((x % 4) * 2);

					op |= पढ़ोb(dst + (x / 4));
					ग_लिखोb(op, dst + (x / 4));
				पूर्ण
			पूर्ण
			dst += (64*2)/8;
		पूर्ण
	पूर्ण

	sm501fb_sync_regs(fbi);	/* ensure cursor data flushed */
	वापस 0;
पूर्ण

/* sm501fb_crtsrc_show
 *
 * device attribute code to show where the crt output is sourced from
*/

अटल sमाप_प्रकार sm501fb_crtsrc_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा sm501fb_info *info = dev_get_drvdata(dev);
	अचिन्हित दीर्घ ctrl;

	ctrl = smc501_पढ़ोl(info->regs + SM501_DC_CRT_CONTROL);
	ctrl &= SM501_DC_CRT_CONTROL_SEL;

	वापस snम_लिखो(buf, PAGE_SIZE, "%s\n", ctrl ? "crt" : "panel");
पूर्ण

/* sm501fb_crtsrc_show
 *
 * device attribute code to set where the crt output is sourced from
*/

अटल sमाप_प्रकार sm501fb_crtsrc_store(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा sm501fb_info *info = dev_get_drvdata(dev);
	क्रमागत sm501_controller head;
	अचिन्हित दीर्घ ctrl;

	अगर (len < 1)
		वापस -EINVAL;

	अगर (strnहालcmp(buf, "crt", 3) == 0)
		head = HEAD_CRT;
	अन्यथा अगर (strnहालcmp(buf, "panel", 5) == 0)
		head = HEAD_PANEL;
	अन्यथा
		वापस -EINVAL;

	dev_info(dev, "setting crt source to head %d\n", head);

	ctrl = smc501_पढ़ोl(info->regs + SM501_DC_CRT_CONTROL);

	अगर (head == HEAD_CRT) अणु
		ctrl |= SM501_DC_CRT_CONTROL_SEL;
		ctrl |= SM501_DC_CRT_CONTROL_ENABLE;
		ctrl |= SM501_DC_CRT_CONTROL_TE;
	पूर्ण अन्यथा अणु
		ctrl &= ~SM501_DC_CRT_CONTROL_SEL;
		ctrl &= ~SM501_DC_CRT_CONTROL_ENABLE;
		ctrl &= ~SM501_DC_CRT_CONTROL_TE;
	पूर्ण

	smc501_ग_लिखोl(ctrl, info->regs + SM501_DC_CRT_CONTROL);
	sm501fb_sync_regs(info);

	वापस len;
पूर्ण

/* Prepare the device_attr क्रम registration with sysfs later */
अटल DEVICE_ATTR(crt_src, 0664, sm501fb_crtsrc_show, sm501fb_crtsrc_store);

/* sm501fb_show_regs
 *
 * show the primary sm501 रेजिस्टरs
*/
अटल पूर्णांक sm501fb_show_regs(काष्ठा sm501fb_info *info, अक्षर *ptr,
			     अचिन्हित पूर्णांक start, अचिन्हित पूर्णांक len)
अणु
	व्योम __iomem *mem = info->regs;
	अक्षर *buf = ptr;
	अचिन्हित पूर्णांक reg;

	क्रम (reg = start; reg < (len + start); reg += 4)
		ptr += प्र_लिखो(ptr, "%08x = %08x\n", reg,
				smc501_पढ़ोl(mem + reg));

	वापस ptr - buf;
पूर्ण

/* sm501fb_debug_show_crt
 *
 * show the crt control and cursor रेजिस्टरs
*/

अटल sमाप_प्रकार sm501fb_debug_show_crt(काष्ठा device *dev,
				  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा sm501fb_info *info = dev_get_drvdata(dev);
	अक्षर *ptr = buf;

	ptr += sm501fb_show_regs(info, ptr, SM501_DC_CRT_CONTROL, 0x40);
	ptr += sm501fb_show_regs(info, ptr, SM501_DC_CRT_HWC_BASE, 0x10);

	वापस ptr - buf;
पूर्ण

अटल DEVICE_ATTR(fbregs_crt, 0444, sm501fb_debug_show_crt, शून्य);

/* sm501fb_debug_show_pnl
 *
 * show the panel control and cursor रेजिस्टरs
*/

अटल sमाप_प्रकार sm501fb_debug_show_pnl(काष्ठा device *dev,
				  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा sm501fb_info *info = dev_get_drvdata(dev);
	अक्षर *ptr = buf;

	ptr += sm501fb_show_regs(info, ptr, 0x0, 0x40);
	ptr += sm501fb_show_regs(info, ptr, SM501_DC_PANEL_HWC_BASE, 0x10);

	वापस ptr - buf;
पूर्ण

अटल DEVICE_ATTR(fbregs_pnl, 0444, sm501fb_debug_show_pnl, शून्य);

अटल काष्ठा attribute *sm501fb_attrs[] = अणु
	&dev_attr_crt_src.attr,
	&dev_attr_fbregs_pnl.attr,
	&dev_attr_fbregs_crt.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(sm501fb);

/* acceleration operations */
अटल पूर्णांक sm501fb_sync(काष्ठा fb_info *info)
अणु
	पूर्णांक count = 1000000;
	काष्ठा sm501fb_par  *par = info->par;
	काष्ठा sm501fb_info *fbi = par->info;

	/* रुको क्रम the 2d engine to be पढ़ोy */
	जबतक ((count > 0) &&
	       (smc501_पढ़ोl(fbi->regs + SM501_SYSTEM_CONTROL) &
		SM501_SYSCTRL_2D_ENGINE_STATUS) != 0)
		count--;

	अगर (count <= 0) अणु
		dev_err(info->dev, "Timeout waiting for 2d engine sync\n");
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम sm501fb_copyarea(काष्ठा fb_info *info, स्थिर काष्ठा fb_copyarea *area)
अणु
	काष्ठा sm501fb_par  *par = info->par;
	काष्ठा sm501fb_info *fbi = par->info;
	पूर्णांक width = area->width;
	पूर्णांक height = area->height;
	पूर्णांक sx = area->sx;
	पूर्णांक sy = area->sy;
	पूर्णांक dx = area->dx;
	पूर्णांक dy = area->dy;
	अचिन्हित दीर्घ rtl = 0;

	/* source clip */
	अगर ((sx >= info->var.xres_भव) ||
	    (sy >= info->var.yres_भव))
		/* source Area not within भव screen, skipping */
		वापस;
	अगर ((sx + width) >= info->var.xres_भव)
		width = info->var.xres_भव - sx - 1;
	अगर ((sy + height) >= info->var.yres_भव)
		height = info->var.yres_भव - sy - 1;

	/* dest clip */
	अगर ((dx >= info->var.xres_भव) ||
	    (dy >= info->var.yres_भव))
		/* Destination Area not within भव screen, skipping */
		वापस;
	अगर ((dx + width) >= info->var.xres_भव)
		width = info->var.xres_भव - dx - 1;
	अगर ((dy + height) >= info->var.yres_भव)
		height = info->var.yres_भव - dy - 1;

	अगर ((sx < dx) || (sy < dy)) अणु
		rtl = 1 << 27;
		sx += width - 1;
		dx += width - 1;
		sy += height - 1;
		dy += height - 1;
	पूर्ण

	अगर (sm501fb_sync(info))
		वापस;

	/* set the base addresses */
	smc501_ग_लिखोl(par->screen.sm_addr, fbi->regs2d + SM501_2D_SOURCE_BASE);
	smc501_ग_लिखोl(par->screen.sm_addr,
			fbi->regs2d + SM501_2D_DESTINATION_BASE);

	/* set the winकरोw width */
	smc501_ग_लिखोl((info->var.xres << 16) | info->var.xres,
	       fbi->regs2d + SM501_2D_WINDOW_WIDTH);

	/* set winकरोw stride */
	smc501_ग_लिखोl((info->var.xres_भव << 16) | info->var.xres_भव,
	       fbi->regs2d + SM501_2D_PITCH);

	/* set data क्रमmat */
	चयन (info->var.bits_per_pixel) अणु
	हाल 8:
		smc501_ग_लिखोl(0, fbi->regs2d + SM501_2D_STRETCH);
		अवरोध;
	हाल 16:
		smc501_ग_लिखोl(0x00100000, fbi->regs2d + SM501_2D_STRETCH);
		अवरोध;
	हाल 32:
		smc501_ग_लिखोl(0x00200000, fbi->regs2d + SM501_2D_STRETCH);
		अवरोध;
	पूर्ण

	/* 2d compare mask */
	smc501_ग_लिखोl(0xffffffff, fbi->regs2d + SM501_2D_COLOR_COMPARE_MASK);

	/* 2d mask */
	smc501_ग_लिखोl(0xffffffff, fbi->regs2d + SM501_2D_MASK);

	/* source and destination x y */
	smc501_ग_लिखोl((sx << 16) | sy, fbi->regs2d + SM501_2D_SOURCE);
	smc501_ग_लिखोl((dx << 16) | dy, fbi->regs2d + SM501_2D_DESTINATION);

	/* w/h */
	smc501_ग_लिखोl((width << 16) | height, fbi->regs2d + SM501_2D_DIMENSION);

	/* करो area move */
	smc501_ग_लिखोl(0x800000cc | rtl, fbi->regs2d + SM501_2D_CONTROL);
पूर्ण

अटल व्योम sm501fb_fillrect(काष्ठा fb_info *info, स्थिर काष्ठा fb_fillrect *rect)
अणु
	काष्ठा sm501fb_par  *par = info->par;
	काष्ठा sm501fb_info *fbi = par->info;
	पूर्णांक width = rect->width, height = rect->height;

	अगर ((rect->dx >= info->var.xres_भव) ||
	    (rect->dy >= info->var.yres_भव))
		/* Rectangle not within भव screen, skipping */
		वापस;
	अगर ((rect->dx + width) >= info->var.xres_भव)
		width = info->var.xres_भव - rect->dx - 1;
	अगर ((rect->dy + height) >= info->var.yres_भव)
		height = info->var.yres_भव - rect->dy - 1;

	अगर (sm501fb_sync(info))
		वापस;

	/* set the base addresses */
	smc501_ग_लिखोl(par->screen.sm_addr, fbi->regs2d + SM501_2D_SOURCE_BASE);
	smc501_ग_लिखोl(par->screen.sm_addr,
			fbi->regs2d + SM501_2D_DESTINATION_BASE);

	/* set the winकरोw width */
	smc501_ग_लिखोl((info->var.xres << 16) | info->var.xres,
	       fbi->regs2d + SM501_2D_WINDOW_WIDTH);

	/* set winकरोw stride */
	smc501_ग_लिखोl((info->var.xres_भव << 16) | info->var.xres_भव,
	       fbi->regs2d + SM501_2D_PITCH);

	/* set data क्रमmat */
	चयन (info->var.bits_per_pixel) अणु
	हाल 8:
		smc501_ग_लिखोl(0, fbi->regs2d + SM501_2D_STRETCH);
		अवरोध;
	हाल 16:
		smc501_ग_लिखोl(0x00100000, fbi->regs2d + SM501_2D_STRETCH);
		अवरोध;
	हाल 32:
		smc501_ग_लिखोl(0x00200000, fbi->regs2d + SM501_2D_STRETCH);
		अवरोध;
	पूर्ण

	/* 2d compare mask */
	smc501_ग_लिखोl(0xffffffff, fbi->regs2d + SM501_2D_COLOR_COMPARE_MASK);

	/* 2d mask */
	smc501_ग_लिखोl(0xffffffff, fbi->regs2d + SM501_2D_MASK);

	/* colour */
	smc501_ग_लिखोl(rect->color, fbi->regs2d + SM501_2D_FOREGROUND);

	/* x y */
	smc501_ग_लिखोl((rect->dx << 16) | rect->dy,
			fbi->regs2d + SM501_2D_DESTINATION);

	/* w/h */
	smc501_ग_लिखोl((width << 16) | height, fbi->regs2d + SM501_2D_DIMENSION);

	/* करो rectangle fill */
	smc501_ग_लिखोl(0x800100cc, fbi->regs2d + SM501_2D_CONTROL);
पूर्ण


अटल काष्ठा fb_ops sm501fb_ops_crt = अणु
	.owner		= THIS_MODULE,
	.fb_check_var	= sm501fb_check_var_crt,
	.fb_set_par	= sm501fb_set_par_crt,
	.fb_blank	= sm501fb_blank_crt,
	.fb_setcolreg	= sm501fb_setcolreg,
	.fb_pan_display	= sm501fb_pan_crt,
	.fb_cursor	= sm501fb_cursor,
	.fb_fillrect	= sm501fb_fillrect,
	.fb_copyarea	= sm501fb_copyarea,
	.fb_imageblit	= cfb_imageblit,
	.fb_sync	= sm501fb_sync,
पूर्ण;

अटल काष्ठा fb_ops sm501fb_ops_pnl = अणु
	.owner		= THIS_MODULE,
	.fb_check_var	= sm501fb_check_var_pnl,
	.fb_set_par	= sm501fb_set_par_pnl,
	.fb_pan_display	= sm501fb_pan_pnl,
	.fb_blank	= sm501fb_blank_pnl,
	.fb_setcolreg	= sm501fb_setcolreg,
	.fb_cursor	= sm501fb_cursor,
	.fb_fillrect	= sm501fb_fillrect,
	.fb_copyarea	= sm501fb_copyarea,
	.fb_imageblit	= cfb_imageblit,
	.fb_sync	= sm501fb_sync,
पूर्ण;

/* sm501_init_cursor
 *
 * initialise hw cursor parameters
*/

अटल पूर्णांक sm501_init_cursor(काष्ठा fb_info *fbi, अचिन्हित पूर्णांक reg_base)
अणु
	काष्ठा sm501fb_par *par;
	काष्ठा sm501fb_info *info;
	पूर्णांक ret;

	अगर (fbi == शून्य)
		वापस 0;

	par = fbi->par;
	info = par->info;

	par->cursor_regs = info->regs + reg_base;

	ret = sm501_alloc_mem(info, &par->cursor, SM501_MEMF_CURSOR, 1024,
			      fbi->fix.smem_len);
	अगर (ret < 0)
		वापस ret;

	/* initialise the colour रेजिस्टरs */

	smc501_ग_लिखोl(par->cursor.sm_addr,
			par->cursor_regs + SM501_OFF_HWC_ADDR);

	smc501_ग_लिखोl(0x00, par->cursor_regs + SM501_OFF_HWC_LOC);
	smc501_ग_लिखोl(0x00, par->cursor_regs + SM501_OFF_HWC_COLOR_1_2);
	smc501_ग_लिखोl(0x00, par->cursor_regs + SM501_OFF_HWC_COLOR_3);
	sm501fb_sync_regs(info);

	वापस 0;
पूर्ण

/* sm501fb_info_start
 *
 * fills the par काष्ठाure claiming resources and remapping etc.
*/

अटल पूर्णांक sm501fb_start(काष्ठा sm501fb_info *info,
			 काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource	*res;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक k;
	पूर्णांक ret;

	info->irq = ret = platक्रमm_get_irq(pdev, 0);
	अगर (ret < 0) अणु
		/* we currently करो not use the IRQ */
		dev_warn(dev, "no irq for device\n");
	पूर्ण

	/* allocate, reserve and remap resources क्रम display
	 * controller रेजिस्टरs */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (res == शून्य) अणु
		dev_err(dev, "no resource definition for registers\n");
		ret = -ENOENT;
		जाओ err_release;
	पूर्ण

	info->regs_res = request_mem_region(res->start,
					    resource_size(res),
					    pdev->name);

	अगर (info->regs_res == शून्य) अणु
		dev_err(dev, "cannot claim registers\n");
		ret = -ENXIO;
		जाओ err_release;
	पूर्ण

	info->regs = ioremap(res->start, resource_size(res));
	अगर (info->regs == शून्य) अणु
		dev_err(dev, "cannot remap registers\n");
		ret = -ENXIO;
		जाओ err_regs_res;
	पूर्ण

	/* allocate, reserve and remap resources क्रम 2d
	 * controller रेजिस्टरs */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
	अगर (res == शून्य) अणु
		dev_err(dev, "no resource definition for 2d registers\n");
		ret = -ENOENT;
		जाओ err_regs_map;
	पूर्ण

	info->regs2d_res = request_mem_region(res->start,
					      resource_size(res),
					      pdev->name);

	अगर (info->regs2d_res == शून्य) अणु
		dev_err(dev, "cannot claim registers\n");
		ret = -ENXIO;
		जाओ err_regs_map;
	पूर्ण

	info->regs2d = ioremap(res->start, resource_size(res));
	अगर (info->regs2d == शून्य) अणु
		dev_err(dev, "cannot remap registers\n");
		ret = -ENXIO;
		जाओ err_regs2d_res;
	पूर्ण

	/* allocate, reserve resources क्रम framebuffer */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 2);
	अगर (res == शून्य) अणु
		dev_err(dev, "no memory resource defined\n");
		ret = -ENXIO;
		जाओ err_regs2d_map;
	पूर्ण

	info->fbmem_res = request_mem_region(res->start,
					     resource_size(res),
					     pdev->name);
	अगर (info->fbmem_res == शून्य) अणु
		dev_err(dev, "cannot claim framebuffer\n");
		ret = -ENXIO;
		जाओ err_regs2d_map;
	पूर्ण

	info->fbmem = ioremap(res->start, resource_size(res));
	अगर (info->fbmem == शून्य) अणु
		dev_err(dev, "cannot remap framebuffer\n");
		ret = -ENXIO;
		जाओ err_mem_res;
	पूर्ण

	info->fbmem_len = resource_size(res);

	/* clear framebuffer memory - aव्योमs garbage data on unused fb */
	स_रखो_io(info->fbmem, 0, info->fbmem_len);

	/* clear palette ram - undefined at घातer on */
	क्रम (k = 0; k < (256 * 3); k++)
		smc501_ग_लिखोl(0, info->regs + SM501_DC_PANEL_PALETTE + (k * 4));

	/* enable display controller */
	sm501_unit_घातer(dev->parent, SM501_GATE_DISPLAY, 1);

	/* enable 2d controller */
	sm501_unit_घातer(dev->parent, SM501_GATE_2D_ENGINE, 1);

	/* setup cursors */
	sm501_init_cursor(info->fb[HEAD_CRT], SM501_DC_CRT_HWC_ADDR);
	sm501_init_cursor(info->fb[HEAD_PANEL], SM501_DC_PANEL_HWC_ADDR);

	वापस 0; /* everything is setup */

 err_mem_res:
	release_mem_region(info->fbmem_res->start,
			   resource_size(info->fbmem_res));

 err_regs2d_map:
	iounmap(info->regs2d);

 err_regs2d_res:
	release_mem_region(info->regs2d_res->start,
			   resource_size(info->regs2d_res));

 err_regs_map:
	iounmap(info->regs);

 err_regs_res:
	release_mem_region(info->regs_res->start,
			   resource_size(info->regs_res));

 err_release:
	वापस ret;
पूर्ण

अटल व्योम sm501fb_stop(काष्ठा sm501fb_info *info)
अणु
	/* disable display controller */
	sm501_unit_घातer(info->dev->parent, SM501_GATE_DISPLAY, 0);

	iounmap(info->fbmem);
	release_mem_region(info->fbmem_res->start,
			   resource_size(info->fbmem_res));

	iounmap(info->regs2d);
	release_mem_region(info->regs2d_res->start,
			   resource_size(info->regs2d_res));

	iounmap(info->regs);
	release_mem_region(info->regs_res->start,
			   resource_size(info->regs_res));
पूर्ण

अटल पूर्णांक sm501fb_init_fb(काष्ठा fb_info *fb, क्रमागत sm501_controller head,
			   स्थिर अक्षर *fbname)
अणु
	काष्ठा sm501_platdata_fbsub *pd;
	काष्ठा sm501fb_par *par = fb->par;
	काष्ठा sm501fb_info *info = par->info;
	अचिन्हित दीर्घ ctrl;
	अचिन्हित पूर्णांक enable;
	पूर्णांक ret;

	चयन (head) अणु
	हाल HEAD_CRT:
		pd = info->pdata->fb_crt;
		ctrl = smc501_पढ़ोl(info->regs + SM501_DC_CRT_CONTROL);
		enable = (ctrl & SM501_DC_CRT_CONTROL_ENABLE) ? 1 : 0;

		/* ensure we set the correct source रेजिस्टर */
		अगर (info->pdata->fb_route != SM501_FB_CRT_PANEL) अणु
			ctrl |= SM501_DC_CRT_CONTROL_SEL;
			smc501_ग_लिखोl(ctrl, info->regs + SM501_DC_CRT_CONTROL);
		पूर्ण

		अवरोध;

	हाल HEAD_PANEL:
		pd = info->pdata->fb_pnl;
		ctrl = smc501_पढ़ोl(info->regs + SM501_DC_PANEL_CONTROL);
		enable = (ctrl & SM501_DC_PANEL_CONTROL_EN) ? 1 : 0;
		अवरोध;

	शेष:
		pd = शून्य;		/* stop compiler warnings */
		ctrl = 0;
		enable = 0;
		BUG();
	पूर्ण

	dev_info(info->dev, "fb %s %sabled at start\n",
		 fbname, enable ? "en" : "dis");

	/* check to see अगर our routing allows this */

	अगर (head == HEAD_CRT && info->pdata->fb_route == SM501_FB_CRT_PANEL) अणु
		ctrl &= ~SM501_DC_CRT_CONTROL_SEL;
		smc501_ग_लिखोl(ctrl, info->regs + SM501_DC_CRT_CONTROL);
		enable = 0;
	पूर्ण

	strlcpy(fb->fix.id, fbname, माप(fb->fix.id));

	स_नकल(&par->ops,
	       (head == HEAD_CRT) ? &sm501fb_ops_crt : &sm501fb_ops_pnl,
	       माप(काष्ठा fb_ops));

	/* update ops dependent on what we've been passed */

	अगर ((pd->flags & SM501FB_FLAG_USE_HWCURSOR) == 0)
		par->ops.fb_cursor = शून्य;

	fb->fbops = &par->ops;
	fb->flags = FBINFO_FLAG_DEFAULT | FBINFO_READS_FAST |
		FBINFO_HWACCEL_COPYAREA | FBINFO_HWACCEL_FILLRECT |
		FBINFO_HWACCEL_XPAN | FBINFO_HWACCEL_YPAN;

#अगर defined(CONFIG_OF)
#अगर_घोषित __BIG_ENDIAN
	अगर (of_get_property(info->dev->parent->of_node, "little-endian", शून्य))
		fb->flags |= FBINFO_FOREIGN_ENDIAN;
#अन्यथा
	अगर (of_get_property(info->dev->parent->of_node, "big-endian", शून्य))
		fb->flags |= FBINFO_FOREIGN_ENDIAN;
#पूर्ण_अगर
#पूर्ण_अगर
	/* fixed data */

	fb->fix.type		= FB_TYPE_PACKED_PIXELS;
	fb->fix.type_aux	= 0;
	fb->fix.xpanstep	= 1;
	fb->fix.ypanstep	= 1;
	fb->fix.ywrapstep	= 0;
	fb->fix.accel		= FB_ACCEL_NONE;

	/* screenmode */

	fb->var.nonstd		= 0;
	fb->var.activate	= FB_ACTIVATE_NOW;
	fb->var.accel_flags	= 0;
	fb->var.vmode		= FB_VMODE_NONINTERLACED;
	fb->var.bits_per_pixel  = 16;

	अगर (info->edid_data) अणु
			/* Now build modedb from EDID */
			fb_edid_to_monspecs(info->edid_data, &fb->monspecs);
			fb_videomode_to_modelist(fb->monspecs.modedb,
						 fb->monspecs.modedb_len,
						 &fb->modelist);
	पूर्ण

	अगर (enable && (pd->flags & SM501FB_FLAG_USE_INIT_MODE) && 0) अणु
		/* TODO पढ़ो the mode from the current display */
	पूर्ण अन्यथा अणु
		अगर (pd->def_mode) अणु
			dev_info(info->dev, "using supplied mode\n");
			fb_videomode_to_var(&fb->var, pd->def_mode);

			fb->var.bits_per_pixel = pd->def_bpp ? pd->def_bpp : 8;
			fb->var.xres_भव = fb->var.xres;
			fb->var.yres_भव = fb->var.yres;
		पूर्ण अन्यथा अणु
			अगर (info->edid_data) अणु
				ret = fb_find_mode(&fb->var, fb, fb_mode,
					fb->monspecs.modedb,
					fb->monspecs.modedb_len,
					&sm501_शेष_mode, शेष_bpp);
				/* edid_data is no दीर्घer needed, मुक्त it */
				kमुक्त(info->edid_data);
			पूर्ण अन्यथा अणु
				ret = fb_find_mode(&fb->var, fb,
					   शून्य, शून्य, 0, शून्य, 8);
			पूर्ण

			चयन (ret) अणु
			हाल 1:
				dev_info(info->dev, "using mode specified in "
						"@mode\n");
				अवरोध;
			हाल 2:
				dev_info(info->dev, "using mode specified in "
					"@mode with ignored refresh rate\n");
				अवरोध;
			हाल 3:
				dev_info(info->dev, "using mode default "
					"mode\n");
				अवरोध;
			हाल 4:
				dev_info(info->dev, "using mode from list\n");
				अवरोध;
			शेष:
				dev_info(info->dev, "ret = %d\n", ret);
				dev_info(info->dev, "failed to find mode\n");
				वापस -EINVAL;
			पूर्ण
		पूर्ण
	पूर्ण

	/* initialise and set the palette */
	अगर (fb_alloc_cmap(&fb->cmap, NR_PALETTE, 0)) अणु
		dev_err(info->dev, "failed to allocate cmap memory\n");
		वापस -ENOMEM;
	पूर्ण
	fb_set_cmap(&fb->cmap, fb);

	ret = (fb->fbops->fb_check_var)(&fb->var, fb);
	अगर (ret)
		dev_err(info->dev, "check_var() failed on initial setup?\n");

	वापस 0;
पूर्ण

/* शेष platक्रमm data अगर none is supplied (ie, PCI device) */

अटल काष्ठा sm501_platdata_fbsub sm501fb_pdata_crt = अणु
	.flags		= (SM501FB_FLAG_USE_INIT_MODE |
			   SM501FB_FLAG_USE_HWCURSOR |
			   SM501FB_FLAG_USE_HWACCEL |
			   SM501FB_FLAG_DISABLE_AT_EXIT),

पूर्ण;

अटल काष्ठा sm501_platdata_fbsub sm501fb_pdata_pnl = अणु
	.flags		= (SM501FB_FLAG_USE_INIT_MODE |
			   SM501FB_FLAG_USE_HWCURSOR |
			   SM501FB_FLAG_USE_HWACCEL |
			   SM501FB_FLAG_DISABLE_AT_EXIT),
पूर्ण;

अटल काष्ठा sm501_platdata_fb sm501fb_def_pdata = अणु
	.fb_route		= SM501_FB_OWN,
	.fb_crt			= &sm501fb_pdata_crt,
	.fb_pnl			= &sm501fb_pdata_pnl,
पूर्ण;

अटल अक्षर driver_name_crt[] = "sm501fb-crt";
अटल अक्षर driver_name_pnl[] = "sm501fb-panel";

अटल पूर्णांक sm501fb_probe_one(काष्ठा sm501fb_info *info,
			     क्रमागत sm501_controller head)
अणु
	अचिन्हित अक्षर *name = (head == HEAD_CRT) ? "crt" : "panel";
	काष्ठा sm501_platdata_fbsub *pd;
	काष्ठा sm501fb_par *par;
	काष्ठा fb_info *fbi;

	pd = (head == HEAD_CRT) ? info->pdata->fb_crt : info->pdata->fb_pnl;

	/* Do not initialise अगर we've not been given any platक्रमm data */
	अगर (pd == शून्य) अणु
		dev_info(info->dev, "no data for fb %s (disabled)\n", name);
		वापस 0;
	पूर्ण

	fbi = framebuffer_alloc(माप(काष्ठा sm501fb_par), info->dev);
	अगर (!fbi)
		वापस -ENOMEM;

	par = fbi->par;
	par->info = info;
	par->head = head;
	fbi->pseuकरो_palette = &par->pseuकरो_palette;

	info->fb[head] = fbi;

	वापस 0;
पूर्ण

/* Free up anything allocated by sm501fb_init_fb */

अटल व्योम sm501_मुक्त_init_fb(काष्ठा sm501fb_info *info,
				क्रमागत sm501_controller head)
अणु
	काष्ठा fb_info *fbi = info->fb[head];

	अगर (!fbi)
		वापस;

	fb_dealloc_cmap(&fbi->cmap);
पूर्ण

अटल पूर्णांक sm501fb_start_one(काष्ठा sm501fb_info *info,
			     क्रमागत sm501_controller head, स्थिर अक्षर *drvname)
अणु
	काष्ठा fb_info *fbi = info->fb[head];
	पूर्णांक ret;

	अगर (!fbi)
		वापस 0;

	mutex_init(&info->fb[head]->mm_lock);

	ret = sm501fb_init_fb(info->fb[head], head, drvname);
	अगर (ret) अणु
		dev_err(info->dev, "cannot initialise fb %s\n", drvname);
		वापस ret;
	पूर्ण

	ret = रेजिस्टर_framebuffer(info->fb[head]);
	अगर (ret) अणु
		dev_err(info->dev, "failed to register fb %s\n", drvname);
		sm501_मुक्त_init_fb(info, head);
		वापस ret;
	पूर्ण

	dev_info(info->dev, "fb%d: %s frame buffer\n", fbi->node, fbi->fix.id);

	वापस 0;
पूर्ण

अटल पूर्णांक sm501fb_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sm501fb_info *info;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक ret;

	/* allocate our framebuffers */
	info = kzalloc(माप(*info), GFP_KERNEL);
	अगर (!info) अणु
		dev_err(dev, "failed to allocate state\n");
		वापस -ENOMEM;
	पूर्ण

	info->dev = dev = &pdev->dev;
	platक्रमm_set_drvdata(pdev, info);

	अगर (dev->parent->platक्रमm_data) अणु
		काष्ठा sm501_platdata *pd = dev->parent->platक्रमm_data;
		info->pdata = pd->fb;
	पूर्ण

	अगर (info->pdata == शून्य) अणु
		पूर्णांक found = 0;
#अगर defined(CONFIG_OF)
		काष्ठा device_node *np = pdev->dev.parent->of_node;
		स्थिर u8 *prop;
		स्थिर अक्षर *cp;
		पूर्णांक len;

		info->pdata = &sm501fb_def_pdata;
		अगर (np) अणु
			/* Get EDID */
			cp = of_get_property(np, "mode", &len);
			अगर (cp)
				म_नकल(fb_mode, cp);
			prop = of_get_property(np, "edid", &len);
			अगर (prop && len == EDID_LENGTH) अणु
				info->edid_data = kmemdup(prop, EDID_LENGTH,
							  GFP_KERNEL);
				अगर (info->edid_data)
					found = 1;
			पूर्ण
		पूर्ण
#पूर्ण_अगर
		अगर (!found) अणु
			dev_info(dev, "using default configuration data\n");
			info->pdata = &sm501fb_def_pdata;
		पूर्ण
	पूर्ण

	/* probe क्रम the presence of each panel */

	ret = sm501fb_probe_one(info, HEAD_CRT);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to probe CRT\n");
		जाओ err_alloc;
	पूर्ण

	ret = sm501fb_probe_one(info, HEAD_PANEL);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to probe PANEL\n");
		जाओ err_probed_crt;
	पूर्ण

	अगर (info->fb[HEAD_PANEL] == शून्य &&
	    info->fb[HEAD_CRT] == शून्य) अणु
		dev_err(dev, "no framebuffers found\n");
		ret = -ENODEV;
		जाओ err_alloc;
	पूर्ण

	/* get the resources क्रम both of the framebuffers */

	ret = sm501fb_start(info, pdev);
	अगर (ret) अणु
		dev_err(dev, "cannot initialise SM501\n");
		जाओ err_probed_panel;
	पूर्ण

	ret = sm501fb_start_one(info, HEAD_CRT, driver_name_crt);
	अगर (ret) अणु
		dev_err(dev, "failed to start CRT\n");
		जाओ err_started;
	पूर्ण

	ret = sm501fb_start_one(info, HEAD_PANEL, driver_name_pnl);
	अगर (ret) अणु
		dev_err(dev, "failed to start Panel\n");
		जाओ err_started_crt;
	पूर्ण

	/* we रेजिस्टरed, वापस ok */
	वापस 0;

err_started_crt:
	unरेजिस्टर_framebuffer(info->fb[HEAD_CRT]);
	sm501_मुक्त_init_fb(info, HEAD_CRT);

err_started:
	sm501fb_stop(info);

err_probed_panel:
	framebuffer_release(info->fb[HEAD_PANEL]);

err_probed_crt:
	framebuffer_release(info->fb[HEAD_CRT]);

err_alloc:
	kमुक्त(info);

	वापस ret;
पूर्ण


/*
 *  Cleanup
 */
अटल पूर्णांक sm501fb_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sm501fb_info *info = platक्रमm_get_drvdata(pdev);
	काष्ठा fb_info	   *fbinfo_crt = info->fb[0];
	काष्ठा fb_info	   *fbinfo_pnl = info->fb[1];

	sm501_मुक्त_init_fb(info, HEAD_CRT);
	sm501_मुक्त_init_fb(info, HEAD_PANEL);

	अगर (fbinfo_crt)
		unरेजिस्टर_framebuffer(fbinfo_crt);
	अगर (fbinfo_pnl)
		unरेजिस्टर_framebuffer(fbinfo_pnl);

	sm501fb_stop(info);
	kमुक्त(info);

	framebuffer_release(fbinfo_pnl);
	framebuffer_release(fbinfo_crt);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM

अटल पूर्णांक sm501fb_suspend_fb(काष्ठा sm501fb_info *info,
			      क्रमागत sm501_controller head)
अणु
	काष्ठा fb_info *fbi = info->fb[head];
	काष्ठा sm501fb_par *par;

	अगर (!fbi)
		वापस 0;

	par = fbi->par;
	अगर (par->screen.size == 0)
		वापस 0;

	/* blank the relevant पूर्णांकerface to ensure unit घातer minimised */
	(par->ops.fb_blank)(FB_BLANK_POWERDOWN, fbi);

	/* tell console/fb driver we are suspending */

	console_lock();
	fb_set_suspend(fbi, 1);
	console_unlock();

	/* backup copies in हाल chip is घातered करोwn over suspend */

	par->store_fb = vदो_स्मृति(par->screen.size);
	अगर (par->store_fb == शून्य) अणु
		dev_err(info->dev, "no memory to store screen\n");
		वापस -ENOMEM;
	पूर्ण

	par->store_cursor = vदो_स्मृति(par->cursor.size);
	अगर (par->store_cursor == शून्य) अणु
		dev_err(info->dev, "no memory to store cursor\n");
		जाओ err_nocursor;
	पूर्ण

	dev_dbg(info->dev, "suspending screen to %p\n", par->store_fb);
	dev_dbg(info->dev, "suspending cursor to %p\n", par->store_cursor);

	स_नकल_fromio(par->store_fb, par->screen.k_addr, par->screen.size);
	स_नकल_fromio(par->store_cursor, par->cursor.k_addr, par->cursor.size);

	वापस 0;

 err_nocursor:
	vमुक्त(par->store_fb);
	par->store_fb = शून्य;

	वापस -ENOMEM;
पूर्ण

अटल व्योम sm501fb_resume_fb(काष्ठा sm501fb_info *info,
			      क्रमागत sm501_controller head)
अणु
	काष्ठा fb_info *fbi = info->fb[head];
	काष्ठा sm501fb_par *par;

	अगर (!fbi)
		वापस;

	par = fbi->par;
	अगर (par->screen.size == 0)
		वापस;

	/* re-activate the configuration */

	(par->ops.fb_set_par)(fbi);

	/* restore the data */

	dev_dbg(info->dev, "restoring screen from %p\n", par->store_fb);
	dev_dbg(info->dev, "restoring cursor from %p\n", par->store_cursor);

	अगर (par->store_fb)
		स_नकल_toio(par->screen.k_addr, par->store_fb,
			    par->screen.size);

	अगर (par->store_cursor)
		स_नकल_toio(par->cursor.k_addr, par->store_cursor,
			    par->cursor.size);

	console_lock();
	fb_set_suspend(fbi, 0);
	console_unlock();

	vमुक्त(par->store_fb);
	vमुक्त(par->store_cursor);
पूर्ण


/* suspend and resume support */

अटल पूर्णांक sm501fb_suspend(काष्ठा platक्रमm_device *pdev, pm_message_t state)
अणु
	काष्ठा sm501fb_info *info = platक्रमm_get_drvdata(pdev);

	/* store crt control to resume with */
	info->pm_crt_ctrl = smc501_पढ़ोl(info->regs + SM501_DC_CRT_CONTROL);

	sm501fb_suspend_fb(info, HEAD_CRT);
	sm501fb_suspend_fb(info, HEAD_PANEL);

	/* turn off the घड़ीs, in हाल the device is not घातered करोwn */
	sm501_unit_घातer(info->dev->parent, SM501_GATE_DISPLAY, 0);

	वापस 0;
पूर्ण

#घोषणा SM501_CRT_CTRL_SAVE (SM501_DC_CRT_CONTROL_TVP |        \
			     SM501_DC_CRT_CONTROL_SEL)


अटल पूर्णांक sm501fb_resume(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sm501fb_info *info = platक्रमm_get_drvdata(pdev);
	अचिन्हित दीर्घ crt_ctrl;

	sm501_unit_घातer(info->dev->parent, SM501_GATE_DISPLAY, 1);

	/* restore the items we want to be saved क्रम crt control */

	crt_ctrl = smc501_पढ़ोl(info->regs + SM501_DC_CRT_CONTROL);
	crt_ctrl &= ~SM501_CRT_CTRL_SAVE;
	crt_ctrl |= info->pm_crt_ctrl & SM501_CRT_CTRL_SAVE;
	smc501_ग_लिखोl(crt_ctrl, info->regs + SM501_DC_CRT_CONTROL);

	sm501fb_resume_fb(info, HEAD_CRT);
	sm501fb_resume_fb(info, HEAD_PANEL);

	वापस 0;
पूर्ण

#अन्यथा
#घोषणा sm501fb_suspend शून्य
#घोषणा sm501fb_resume  शून्य
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver sm501fb_driver = अणु
	.probe		= sm501fb_probe,
	.हटाओ		= sm501fb_हटाओ,
	.suspend	= sm501fb_suspend,
	.resume		= sm501fb_resume,
	.driver		= अणु
		.name	= "sm501-fb",
		.dev_groups	= sm501fb_groups,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(sm501fb_driver);

module_param_named(mode, fb_mode, अक्षरp, 0);
MODULE_PARM_DESC(mode,
	"Specify resolution as \"<xres>x<yres>[-<bpp>][@<refresh>]\" ");
module_param_named(bpp, शेष_bpp, uदीर्घ, 0);
MODULE_PARM_DESC(bpp, "Specify bit-per-pixel if not specified mode");
MODULE_AUTHOR("Ben Dooks, Vincent Sanders");
MODULE_DESCRIPTION("SM501 Framebuffer driver");
MODULE_LICENSE("GPL v2");
