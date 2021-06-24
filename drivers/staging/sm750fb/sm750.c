<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/fb.h>
#समावेश <linux/ioport.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/mm_types.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/screen_info.h>
#समावेश <linux/console.h>
#समावेश <यंत्र/fb.h>
#समावेश "sm750.h"
#समावेश "sm750_accel.h"
#समावेश "sm750_cursor.h"

/*
 * #अगर_घोषित __BIG_ENDIAN
 * sमाप_प्रकार lynxfb_ops_ग_लिखो(काष्ठा fb_info *info, स्थिर अक्षर __user *buf,
 * माप_प्रकार count, loff_t *ppos);
 * sमाप_प्रकार lynxfb_ops_पढ़ो(काष्ठा fb_info *info, अक्षर __user *buf,
 * माप_प्रकार count, loff_t *ppos);
 * #पूर्ण_अगर
 */

/* common var क्रम all device */
अटल पूर्णांक g_hwcursor = 1;
अटल पूर्णांक g_noaccel;
अटल पूर्णांक g_nomtrr;
अटल स्थिर अक्षर *g_fbmode[] = अणुशून्य, शून्यपूर्ण;
अटल स्थिर अक्षर *g_def_fbmode = "1024x768-32@60";
अटल अक्षर *g_settings;
अटल पूर्णांक g_dualview;
अटल अक्षर *g_option;

अटल स्थिर काष्ठा fb_videomode lynx750_ext[] = अणु
	/*	1024x600-60 VESA	[1.71:1] */
	अणुशून्य,  60, 1024, 600, 20423, 144,  40, 18, 1, 104, 3,
	 FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
	 FB_VMODE_NONINTERLACEDपूर्ण,

	/*	1024x600-70 VESA */
	अणुशून्य,  70, 1024, 600, 17211, 152,  48, 21, 1, 104, 3,
	 FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
	 FB_VMODE_NONINTERLACEDपूर्ण,

	/*	1024x600-75 VESA */
	अणुशून्य,  75, 1024, 600, 15822, 160,  56, 23, 1, 104, 3,
	 FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
	 FB_VMODE_NONINTERLACEDपूर्ण,

	/*	1024x600-85 VESA */
	अणुशून्य,  85, 1024, 600, 13730, 168,  56, 26, 1, 112, 3,
	 FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
	 FB_VMODE_NONINTERLACEDपूर्ण,

	/*	720x480	*/
	अणुशून्य, 60,  720,  480,  37427, 88,   16, 13, 1,   72,  3,
	 FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
	 FB_VMODE_NONINTERLACEDपूर्ण,

	/*	1280x720		[1.78:1]	*/
	अणुशून्य, 60,  1280,  720,  13426, 162, 86, 22, 1,  136, 3,
	 FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
	 FB_VMODE_NONINTERLACEDपूर्ण,

	/*	1280x768@60 */
	अणुशून्य, 60, 1280, 768, 12579, 192, 64, 20, 3, 128, 7,
	 FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
	 FB_VMODE_NONINTERLACEDपूर्ण,

	/*	1360 x 768	[1.77083:1]	*/
	अणुशून्य,  60, 1360, 768, 11804, 208,  64, 23, 1, 144, 3,
	 FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
	 FB_VMODE_NONINTERLACEDपूर्ण,

	/*	1368 x 768      [1.78:1]	*/
	अणुशून्य, 60,  1368,  768,  11647, 216, 72, 23, 1,  144, 3,
	 FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
	 FB_VMODE_NONINTERLACEDपूर्ण,

	/*	1440 x 900		[16:10]	*/
	अणुशून्य, 60, 1440, 900, 9392, 232, 80, 28, 1, 152, 3,
	 FB_SYNC_VERT_HIGH_ACT,
	 FB_VMODE_NONINTERLACEDपूर्ण,

	/*	1440x960		[15:10]	*/
	अणुशून्य, 60, 1440, 960, 8733, 240, 88, 30, 1, 152, 3,
	 FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
	 FB_VMODE_NONINTERLACEDपूर्ण,

	/*	1920x1080	[16:9]	*/
	अणुशून्य, 60, 1920, 1080, 6734, 148, 88, 41, 1, 44, 3,
	 FB_SYNC_VERT_HIGH_ACT,
	 FB_VMODE_NONINTERLACEDपूर्ण,
पूर्ण;

/* no hardware cursor supported under version 2.6.10, kernel bug */
अटल पूर्णांक lynxfb_ops_cursor(काष्ठा fb_info *info, काष्ठा fb_cursor *fbcursor)
अणु
	काष्ठा lynxfb_par *par;
	काष्ठा lynxfb_crtc *crtc;
	काष्ठा lynx_cursor *cursor;

	par = info->par;
	crtc = &par->crtc;
	cursor = &crtc->cursor;

	अगर (fbcursor->image.width > cursor->maxW ||
	    fbcursor->image.height > cursor->maxH ||
	    fbcursor->image.depth > 1) अणु
		वापस -ENXIO;
	पूर्ण

	sm750_hw_cursor_disable(cursor);
	अगर (fbcursor->set & FB_CUR_SETSIZE)
		sm750_hw_cursor_setSize(cursor,
					fbcursor->image.width,
					fbcursor->image.height);

	अगर (fbcursor->set & FB_CUR_SETPOS)
		sm750_hw_cursor_setPos(cursor,
				       fbcursor->image.dx - info->var.xoffset,
				       fbcursor->image.dy - info->var.yoffset);

	अगर (fbcursor->set & FB_CUR_SETCMAP) अणु
		/* get the 16bit color of kernel means */
		u16 fg, bg;

		fg = ((info->cmap.red[fbcursor->image.fg_color] & 0xf800)) |
		     ((info->cmap.green[fbcursor->image.fg_color] & 0xfc00) >> 5) |
		     ((info->cmap.blue[fbcursor->image.fg_color] & 0xf800) >> 11);

		bg = ((info->cmap.red[fbcursor->image.bg_color] & 0xf800)) |
		     ((info->cmap.green[fbcursor->image.bg_color] & 0xfc00) >> 5) |
		     ((info->cmap.blue[fbcursor->image.bg_color] & 0xf800) >> 11);

		sm750_hw_cursor_setColor(cursor, fg, bg);
	पूर्ण

	अगर (fbcursor->set & (FB_CUR_SETSHAPE | FB_CUR_SETIMAGE)) अणु
		sm750_hw_cursor_setData(cursor,
					fbcursor->rop,
					fbcursor->image.data,
					fbcursor->mask);
	पूर्ण

	अगर (fbcursor->enable)
		sm750_hw_cursor_enable(cursor);

	वापस 0;
पूर्ण

अटल व्योम lynxfb_ops_fillrect(काष्ठा fb_info *info,
				स्थिर काष्ठा fb_fillrect *region)
अणु
	काष्ठा lynxfb_par *par;
	काष्ठा sm750_dev *sm750_dev;
	अचिन्हित पूर्णांक base, pitch, Bpp, rop;
	u32 color;

	अगर (info->state != FBINFO_STATE_RUNNING)
		वापस;

	par = info->par;
	sm750_dev = par->dev;

	/*
	 * each समय 2d function begin to work,below three variable always need
	 * be set, seems we can put them together in some place
	 */
	base = par->crtc.oScreen;
	pitch = info->fix.line_length;
	Bpp = info->var.bits_per_pixel >> 3;

	color = (Bpp == 1) ? region->color :
		((u32 *)info->pseuकरो_palette)[region->color];
	rop = (region->rop != ROP_COPY) ? HW_ROP2_XOR : HW_ROP2_COPY;

	/*
	 * If not use spin_lock, प्रणाली will die अगर user load driver
	 * and immediately unload driver frequently (dual)
	 * since they fb_count could change during the lअगरeसमय of
	 * this lock, we are holding it क्रम all हालs.
	 */
	spin_lock(&sm750_dev->slock);

	sm750_dev->accel.de_fillrect(&sm750_dev->accel,
				     base, pitch, Bpp,
				     region->dx, region->dy,
				     region->width, region->height,
				     color, rop);
	spin_unlock(&sm750_dev->slock);
पूर्ण

अटल व्योम lynxfb_ops_copyarea(काष्ठा fb_info *info,
				स्थिर काष्ठा fb_copyarea *region)
अणु
	काष्ठा lynxfb_par *par;
	काष्ठा sm750_dev *sm750_dev;
	अचिन्हित पूर्णांक base, pitch, Bpp;

	par = info->par;
	sm750_dev = par->dev;

	/*
	 * each समय 2d function begin to work,below three variable always need
	 * be set, seems we can put them together in some place
	 */
	base = par->crtc.oScreen;
	pitch = info->fix.line_length;
	Bpp = info->var.bits_per_pixel >> 3;

	/*
	 * If not use spin_lock, प्रणाली will die अगर user load driver
	 * and immediately unload driver frequently (dual)
	 * since they fb_count could change during the lअगरeसमय of
	 * this lock, we are holding it क्रम all हालs.
	 */
	spin_lock(&sm750_dev->slock);

	sm750_dev->accel.de_copyarea(&sm750_dev->accel,
				     base, pitch, region->sx, region->sy,
				     base, pitch, Bpp, region->dx, region->dy,
				     region->width, region->height,
				     HW_ROP2_COPY);
	spin_unlock(&sm750_dev->slock);
पूर्ण

अटल व्योम lynxfb_ops_imageblit(काष्ठा fb_info *info,
				 स्थिर काष्ठा fb_image *image)
अणु
	अचिन्हित पूर्णांक base, pitch, Bpp;
	अचिन्हित पूर्णांक fgcol, bgcol;
	काष्ठा lynxfb_par *par;
	काष्ठा sm750_dev *sm750_dev;

	par = info->par;
	sm750_dev = par->dev;
	/*
	 * each समय 2d function begin to work,below three variable always need
	 * be set, seems we can put them together in some place
	 */
	base = par->crtc.oScreen;
	pitch = info->fix.line_length;
	Bpp = info->var.bits_per_pixel >> 3;

	/* TODO: Implement hardware acceleration क्रम image->depth > 1 */
	अगर (image->depth != 1) अणु
		cfb_imageblit(info, image);
		वापस;
	पूर्ण

	अगर (info->fix.visual == FB_VISUAL_TRUECOLOR ||
	    info->fix.visual == FB_VISUAL_सूचीECTCOLOR) अणु
		fgcol = ((u32 *)info->pseuकरो_palette)[image->fg_color];
		bgcol = ((u32 *)info->pseuकरो_palette)[image->bg_color];
	पूर्ण अन्यथा अणु
		fgcol = image->fg_color;
		bgcol = image->bg_color;
	पूर्ण

	/*
	 * If not use spin_lock, प्रणाली will die अगर user load driver
	 * and immediately unload driver frequently (dual)
	 * since they fb_count could change during the lअगरeसमय of
	 * this lock, we are holding it क्रम all हालs.
	 */
	spin_lock(&sm750_dev->slock);

	sm750_dev->accel.de_imageblit(&sm750_dev->accel,
				      image->data, image->width >> 3, 0,
				      base, pitch, Bpp,
				      image->dx, image->dy,
				      image->width, image->height,
				      fgcol, bgcol, HW_ROP2_COPY);
	spin_unlock(&sm750_dev->slock);
पूर्ण

अटल पूर्णांक lynxfb_ops_pan_display(काष्ठा fb_var_screeninfo *var,
				  काष्ठा fb_info *info)
अणु
	काष्ठा lynxfb_par *par;
	काष्ठा lynxfb_crtc *crtc;

	अगर (!info)
		वापस -EINVAL;

	par = info->par;
	crtc = &par->crtc;
	वापस hw_sm750_pan_display(crtc, var, info);
पूर्ण

अटल अंतरभूत व्योम lynxfb_set_visual_mode(काष्ठा fb_info *info)
अणु
	चयन (info->var.bits_per_pixel) अणु
	हाल 8:
		info->fix.visual = FB_VISUAL_PSEUDOCOLOR;
		अवरोध;
	हाल 16:
	हाल 24:
	हाल 32:
		info->fix.visual = FB_VISUAL_TRUECOLOR;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक lynxfb_set_color_offsets(काष्ठा fb_info *info)
अणु
	lynxfb_set_visual_mode(info);

	चयन (info->var.bits_per_pixel) अणु
	हाल 8:
		info->var.red.offset = 0;
		info->var.red.length = 8;
		info->var.green.offset = 0;
		info->var.green.length = 8;
		info->var.blue.offset = 0;
		info->var.blue.length = 8;
		info->var.transp.length = 0;
		info->var.transp.offset = 0;
		अवरोध;
	हाल 16:
		info->var.red.offset = 11;
		info->var.red.length = 5;
		info->var.green.offset = 5;
		info->var.green.length = 6;
		info->var.blue.offset = 0;
		info->var.blue.length = 5;
		info->var.transp.length = 0;
		info->var.transp.offset = 0;
		अवरोध;
	हाल 24:
	हाल 32:
		info->var.red.offset = 16;
		info->var.red.length = 8;
		info->var.green.offset = 8;
		info->var.green.length = 8;
		info->var.blue.offset = 0;
		info->var.blue.length = 8;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक lynxfb_ops_set_par(काष्ठा fb_info *info)
अणु
	काष्ठा lynxfb_par *par;
	काष्ठा lynxfb_crtc *crtc;
	काष्ठा lynxfb_output *output;
	काष्ठा fb_var_screeninfo *var;
	काष्ठा fb_fix_screeninfo *fix;
	पूर्णांक ret;
	अचिन्हित पूर्णांक line_length;

	अगर (!info)
		वापस -EINVAL;

	ret = 0;
	par = info->par;
	crtc = &par->crtc;
	output = &par->output;
	var = &info->var;
	fix = &info->fix;

	/* fix काष्ठाure is not so FIX ... */
	line_length = var->xres_भव * var->bits_per_pixel / 8;
	line_length = ALIGN(line_length, crtc->line_pad);
	fix->line_length = line_length;
	pr_info("fix->line_length = %d\n", fix->line_length);

	/*
	 * var->red,green,blue,transp are need to be set by driver
	 * and these data should be set beक्रमe setcolreg routine
	 */

	ret = lynxfb_set_color_offsets(info);

	var->height = var->width = -1;
	var->accel_flags = 0;/*FB_ACCELF_TEXT;*/

	अगर (ret) अणु
		pr_err("bpp %d not supported\n", var->bits_per_pixel);
		वापस ret;
	पूर्ण
	ret = hw_sm750_crtc_setMode(crtc, var, fix);
	अगर (!ret)
		ret = hw_sm750_output_setMode(output, var, fix);
	वापस ret;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक chan_to_field(अचिन्हित पूर्णांक chan,
					 काष्ठा fb_bitfield *bf)
अणु
	chan &= 0xffff;
	chan >>= 16 - bf->length;
	वापस chan << bf->offset;
पूर्ण

अटल पूर्णांक __maybe_unused lynxfb_suspend(काष्ठा device *dev)
अणु
	काष्ठा fb_info *info;
	काष्ठा sm750_dev *sm750_dev;

	sm750_dev = dev_get_drvdata(dev);

	console_lock();
	info = sm750_dev->fbinfo[0];
	अगर (info)
		/* 1 means करो suspend */
		fb_set_suspend(info, 1);
	info = sm750_dev->fbinfo[1];
	अगर (info)
		/* 1 means करो suspend */
		fb_set_suspend(info, 1);

	console_unlock();
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused lynxfb_resume(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा fb_info *info;
	काष्ठा sm750_dev *sm750_dev;

	काष्ठा lynxfb_par *par;
	काष्ठा lynxfb_crtc *crtc;
	काष्ठा lynx_cursor *cursor;

	sm750_dev = pci_get_drvdata(pdev);

	console_lock();

	hw_sm750_inithw(sm750_dev, pdev);

	info = sm750_dev->fbinfo[0];

	अगर (info) अणु
		par = info->par;
		crtc = &par->crtc;
		cursor = &crtc->cursor;
		स_रखो_io(cursor->vstart, 0x0, cursor->size);
		स_रखो_io(crtc->vScreen, 0x0, crtc->vidmem_size);
		lynxfb_ops_set_par(info);
		fb_set_suspend(info, 0);
	पूर्ण

	info = sm750_dev->fbinfo[1];

	अगर (info) अणु
		par = info->par;
		crtc = &par->crtc;
		cursor = &crtc->cursor;
		स_रखो_io(cursor->vstart, 0x0, cursor->size);
		स_रखो_io(crtc->vScreen, 0x0, crtc->vidmem_size);
		lynxfb_ops_set_par(info);
		fb_set_suspend(info, 0);
	पूर्ण

	pdev->dev.घातer.घातer_state.event = PM_EVENT_RESUME;

	console_unlock();
	वापस 0;
पूर्ण

अटल पूर्णांक lynxfb_ops_check_var(काष्ठा fb_var_screeninfo *var,
				काष्ठा fb_info *info)
अणु
	पूर्णांक ret;
	काष्ठा lynxfb_par *par;
	काष्ठा lynxfb_crtc *crtc;
	resource_माप_प्रकार request;

	ret = 0;
	par = info->par;
	crtc = &par->crtc;

	pr_debug("check var:%dx%d-%d\n",
		 var->xres,
		 var->yres,
		 var->bits_per_pixel);

	ret = lynxfb_set_color_offsets(info);

	अगर (ret) अणु
		pr_err("bpp %d not supported\n", var->bits_per_pixel);
		वापस ret;
	पूर्ण

	var->height = var->width = -1;
	var->accel_flags = 0;/* FB_ACCELF_TEXT; */

	/* check अगर current fb's video memory big enough to hold the onscreen*/
	request = var->xres_भव * (var->bits_per_pixel >> 3);
	/* शेषy crtc->channel go with par->index */

	request = ALIGN(request, crtc->line_pad);
	request = request * var->yres_भव;
	अगर (crtc->vidmem_size < request) अणु
		pr_err("not enough video memory for mode\n");
		वापस -ENOMEM;
	पूर्ण

	वापस hw_sm750_crtc_checkMode(crtc, var);
पूर्ण

अटल पूर्णांक lynxfb_ops_setcolreg(अचिन्हित पूर्णांक regno,
				अचिन्हित पूर्णांक red,
				अचिन्हित पूर्णांक green,
				अचिन्हित पूर्णांक blue,
				अचिन्हित पूर्णांक transp,
				काष्ठा fb_info *info)
अणु
	काष्ठा lynxfb_par *par;
	काष्ठा lynxfb_crtc *crtc;
	काष्ठा fb_var_screeninfo *var;
	पूर्णांक ret;

	par = info->par;
	crtc = &par->crtc;
	var = &info->var;
	ret = 0;

	अगर (regno > 256) अणु
		pr_err("regno = %d\n", regno);
		वापस -EINVAL;
	पूर्ण

	अगर (info->var.grayscale)
		red = green = blue = (red * 77 + green * 151 + blue * 28) >> 8;

	अगर (var->bits_per_pixel == 8 &&
	    info->fix.visual == FB_VISUAL_PSEUDOCOLOR) अणु
		red >>= 8;
		green >>= 8;
		blue >>= 8;
		ret = hw_sm750_setColReg(crtc, regno, red, green, blue);
		जाओ निकास;
	पूर्ण

	अगर (info->fix.visual == FB_VISUAL_TRUECOLOR && regno < 256) अणु
		u32 val;

		अगर (var->bits_per_pixel == 16 ||
		    var->bits_per_pixel == 32 ||
		    var->bits_per_pixel == 24) अणु
			val = chan_to_field(red, &var->red);
			val |= chan_to_field(green, &var->green);
			val |= chan_to_field(blue, &var->blue);
			par->pseuकरो_palette[regno] = val;
			जाओ निकास;
		पूर्ण
	पूर्ण

	ret = -EINVAL;

निकास:
	वापस ret;
पूर्ण

अटल पूर्णांक lynxfb_ops_blank(पूर्णांक blank, काष्ठा fb_info *info)
अणु
	काष्ठा lynxfb_par *par;
	काष्ठा lynxfb_output *output;

	pr_debug("blank = %d.\n", blank);
	par = info->par;
	output = &par->output;
	वापस output->proc_setBLANK(output, blank);
पूर्ण

अटल पूर्णांक sm750fb_set_drv(काष्ठा lynxfb_par *par)
अणु
	पूर्णांक ret;
	काष्ठा sm750_dev *sm750_dev;
	काष्ठा lynxfb_output *output;
	काष्ठा lynxfb_crtc *crtc;

	ret = 0;

	sm750_dev = par->dev;
	output = &par->output;
	crtc = &par->crtc;

	crtc->vidmem_size = sm750_dev->vidmem_size;
	अगर (sm750_dev->fb_count > 1)
		crtc->vidmem_size >>= 1;

	/* setup crtc and output member */
	sm750_dev->hwCursor = g_hwcursor;

	crtc->line_pad = 16;
	crtc->xpanstep = 8;
	crtc->ypanstep = 1;
	crtc->ywrapstep = 0;

	output->proc_setBLANK = (sm750_dev->revid == SM750LE_REVISION_ID) ?
				 hw_sm750le_setBLANK : hw_sm750_setBLANK;
	/* chip specअगरic phase */
	sm750_dev->accel.de_रुको = (sm750_dev->revid == SM750LE_REVISION_ID) ?
				    hw_sm750le_deWait : hw_sm750_deWait;
	चयन (sm750_dev->dataflow) अणु
	हाल sm750_simul_pri:
		output->paths = sm750_pnc;
		crtc->channel = sm750_primary;
		crtc->oScreen = 0;
		crtc->vScreen = sm750_dev->pvMem;
		pr_info("use simul primary mode\n");
		अवरोध;
	हाल sm750_simul_sec:
		output->paths = sm750_pnc;
		crtc->channel = sm750_secondary;
		crtc->oScreen = 0;
		crtc->vScreen = sm750_dev->pvMem;
		अवरोध;
	हाल sm750_dual_normal:
		अगर (par->index == 0) अणु
			output->paths = sm750_panel;
			crtc->channel = sm750_primary;
			crtc->oScreen = 0;
			crtc->vScreen = sm750_dev->pvMem;
		पूर्ण अन्यथा अणु
			output->paths = sm750_crt;
			crtc->channel = sm750_secondary;
			/* not consider of padding stuffs क्रम oScreen,need fix */
			crtc->oScreen = sm750_dev->vidmem_size >> 1;
			crtc->vScreen = sm750_dev->pvMem + crtc->oScreen;
		पूर्ण
		अवरोध;
	हाल sm750_dual_swap:
		अगर (par->index == 0) अणु
			output->paths = sm750_panel;
			crtc->channel = sm750_secondary;
			crtc->oScreen = 0;
			crtc->vScreen = sm750_dev->pvMem;
		पूर्ण अन्यथा अणु
			output->paths = sm750_crt;
			crtc->channel = sm750_primary;
			/* not consider of padding stuffs क्रम oScreen,
			 * need fix
			 */
			crtc->oScreen = sm750_dev->vidmem_size >> 1;
			crtc->vScreen = sm750_dev->pvMem + crtc->oScreen;
		पूर्ण
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल काष्ठा fb_ops lynxfb_ops = अणु
	.owner = THIS_MODULE,
	.fb_check_var =  lynxfb_ops_check_var,
	.fb_set_par = lynxfb_ops_set_par,
	.fb_setcolreg = lynxfb_ops_setcolreg,
	.fb_blank = lynxfb_ops_blank,
	.fb_fillrect = cfb_fillrect,
	.fb_imageblit = cfb_imageblit,
	.fb_copyarea = cfb_copyarea,
	/* cursor */
	.fb_cursor = lynxfb_ops_cursor,
पूर्ण;

अटल पूर्णांक lynxfb_set_fbinfo(काष्ठा fb_info *info, पूर्णांक index)
अणु
	पूर्णांक i;
	काष्ठा lynxfb_par *par;
	काष्ठा sm750_dev *sm750_dev;
	काष्ठा lynxfb_crtc *crtc;
	काष्ठा lynxfb_output *output;
	काष्ठा fb_var_screeninfo *var;
	काष्ठा fb_fix_screeninfo *fix;

	स्थिर काष्ठा fb_videomode *pdb[] = अणु
		lynx750_ext, शून्य, vesa_modes,
	पूर्ण;
	पूर्णांक cdb[] = अणुARRAY_SIZE(lynx750_ext), 0, VESA_MODEDB_SIZEपूर्ण;
	अटल स्थिर अक्षर * स्थिर mdb_desc[] = अणु
		"driver prepared modes",
		"kernel prepared default modedb",
		"kernel HELPERS prepared vesa_modes",
	पूर्ण;

	अटल स्थिर अक्षर *fixId[2] = अणु
		"sm750_fb1", "sm750_fb2",
	पूर्ण;

	पूर्णांक ret, line_length;

	ret = 0;
	par = (काष्ठा lynxfb_par *)info->par;
	sm750_dev = par->dev;
	crtc = &par->crtc;
	output = &par->output;
	var = &info->var;
	fix = &info->fix;

	/* set index */
	par->index = index;
	output->channel = &crtc->channel;
	sm750fb_set_drv(par);
	lynxfb_ops.fb_pan_display = lynxfb_ops_pan_display;

	/*
	 * set current cursor variable and proc poपूर्णांकer,
	 * must be set after crtc member initialized
	 */
	crtc->cursor.offset = crtc->oScreen + crtc->vidmem_size - 1024;
	crtc->cursor.mmio = sm750_dev->pvReg +
		0x800f0 + (पूर्णांक)crtc->channel * 0x140;

	pr_info("crtc->cursor.mmio = %p\n", crtc->cursor.mmio);
	crtc->cursor.maxH = crtc->cursor.maxW = 64;
	crtc->cursor.size = crtc->cursor.maxH * crtc->cursor.maxW * 2 / 8;
	crtc->cursor.vstart = sm750_dev->pvMem + crtc->cursor.offset;

	स_रखो_io(crtc->cursor.vstart, 0, crtc->cursor.size);
	अगर (!g_hwcursor) अणु
		lynxfb_ops.fb_cursor = शून्य;
		sm750_hw_cursor_disable(&crtc->cursor);
	पूर्ण

	/* set info->fbops, must be set beक्रमe fb_find_mode */
	अगर (!sm750_dev->accel_off) अणु
		/* use 2d acceleration */
		lynxfb_ops.fb_fillrect = lynxfb_ops_fillrect;
		lynxfb_ops.fb_copyarea = lynxfb_ops_copyarea;
		lynxfb_ops.fb_imageblit = lynxfb_ops_imageblit;
	पूर्ण
	info->fbops = &lynxfb_ops;

	अगर (!g_fbmode[index]) अणु
		g_fbmode[index] = g_def_fbmode;
		अगर (index)
			g_fbmode[index] = g_fbmode[0];
	पूर्ण

	क्रम (i = 0; i < 3; i++) अणु
		ret = fb_find_mode(var, info, g_fbmode[index],
				   pdb[i], cdb[i], शून्य, 8);

		अगर (ret == 1) अणु
			pr_info("success! use specified mode:%s in %s\n",
				g_fbmode[index],
				mdb_desc[i]);
			अवरोध;
		पूर्ण अन्यथा अगर (ret == 2) अणु
			pr_warn("use specified mode:%s in %s,with an ignored refresh rate\n",
				g_fbmode[index],
				mdb_desc[i]);
			अवरोध;
		पूर्ण अन्यथा अगर (ret == 3) अणु
			pr_warn("wanna use default mode\n");
			/*अवरोध;*/
		पूर्ण अन्यथा अगर (ret == 4) अणु
			pr_warn("fall back to any valid mode\n");
		पूर्ण अन्यथा अणु
			pr_warn("ret = %d,fb_find_mode failed,with %s\n",
				ret,
				mdb_desc[i]);
		पूर्ण
	पूर्ण

	/* some member of info->var had been set by fb_find_mode */

	pr_info("Member of info->var is :\n"
		"xres=%d\n"
		"yres=%d\n"
		"xres_virtual=%d\n"
		"yres_virtual=%d\n"
		"xoffset=%d\n"
		"yoffset=%d\n"
		"bits_per_pixel=%d\n"
		" ...\n",
		var->xres,
		var->yres,
		var->xres_भव,
		var->yres_भव,
		var->xoffset,
		var->yoffset,
		var->bits_per_pixel);

	/* set par */
	par->info = info;

	/* set info */
	line_length = ALIGN((var->xres_भव * var->bits_per_pixel / 8),
			    crtc->line_pad);

	info->pseuकरो_palette = &par->pseuकरो_palette[0];
	info->screen_base = crtc->vScreen;
	pr_debug("screen_base vaddr = %p\n", info->screen_base);
	info->screen_size = line_length * var->yres_भव;
	info->flags = FBINFO_FLAG_DEFAULT | 0;

	/* set info->fix */
	fix->type = FB_TYPE_PACKED_PIXELS;
	fix->type_aux = 0;
	fix->xpanstep = crtc->xpanstep;
	fix->ypanstep = crtc->ypanstep;
	fix->ywrapstep = crtc->ywrapstep;
	fix->accel = FB_ACCEL_SMI;

	strscpy(fix->id, fixId[index], माप(fix->id));

	fix->smem_start = crtc->oScreen + sm750_dev->vidmem_start;
	pr_info("fix->smem_start = %lx\n", fix->smem_start);
	/*
	 * according to mmap experiment from user space application,
	 * fix->mmio_len should not larger than भव size
	 * (xres_भव x yres_भव x ByPP)
	 * Below line maybe buggy when user mmap fb dev node and ग_लिखो
	 * data पूर्णांकo the bound over भव size
	 */
	fix->smem_len = crtc->vidmem_size;
	pr_info("fix->smem_len = %x\n", fix->smem_len);
	info->screen_size = fix->smem_len;
	fix->line_length = line_length;
	fix->mmio_start = sm750_dev->vidreg_start;
	pr_info("fix->mmio_start = %lx\n", fix->mmio_start);
	fix->mmio_len = sm750_dev->vidreg_size;
	pr_info("fix->mmio_len = %x\n", fix->mmio_len);

	lynxfb_set_visual_mode(info);

	/* set var */
	var->activate = FB_ACTIVATE_NOW;
	var->accel_flags = 0;
	var->vmode = FB_VMODE_NONINTERLACED;

	pr_debug("#1 show info->cmap :\nstart=%d,len=%d,red=%p,green=%p,blue=%p,transp=%p\n",
		 info->cmap.start, info->cmap.len,
		 info->cmap.red, info->cmap.green, info->cmap.blue,
		 info->cmap.transp);

	ret = fb_alloc_cmap(&info->cmap, 256, 0);
	अगर (ret < 0) अणु
		pr_err("Could not allocate memory for cmap.\n");
		जाओ निकास;
	पूर्ण

	pr_debug("#2 show info->cmap :\nstart=%d,len=%d,red=%p,green=%p,blue=%p,transp=%p\n",
		 info->cmap.start, info->cmap.len,
		 info->cmap.red, info->cmap.green, info->cmap.blue,
		 info->cmap.transp);

निकास:
	lynxfb_ops_check_var(var, info);
	वापस ret;
पूर्ण

/*	chip specअगरic g_option configuration routine */
अटल व्योम sm750fb_setup(काष्ठा sm750_dev *sm750_dev, अक्षर *src)
अणु
	अक्षर *opt;
	पूर्णांक swap;

	swap = 0;

	sm750_dev->initParm.chip_clk = 0;
	sm750_dev->initParm.mem_clk = 0;
	sm750_dev->initParm.master_clk = 0;
	sm750_dev->initParm.घातerMode = 0;
	sm750_dev->initParm.setAllEngOff = 0;
	sm750_dev->initParm.resetMemory = 1;

	/* शेषly turn g_hwcursor on क्रम both view */
	g_hwcursor = 3;

	अगर (!src || !*src) अणु
		dev_warn(&sm750_dev->pdev->dev, "no specific g_option.\n");
		जाओ NO_PARAM;
	पूर्ण

	जबतक ((opt = strsep(&src, ":")) != शून्य && *opt != 0) अणु
		dev_info(&sm750_dev->pdev->dev, "opt=%s\n", opt);
		dev_info(&sm750_dev->pdev->dev, "src=%s\n", src);

		अगर (!म_भेदन(opt, "swap", म_माप("swap"))) अणु
			swap = 1;
		पूर्ण अन्यथा अगर (!म_भेदन(opt, "nocrt", म_माप("nocrt"))) अणु
			sm750_dev->nocrt = 1;
		पूर्ण अन्यथा अगर (!म_भेदन(opt, "36bit", म_माप("36bit"))) अणु
			sm750_dev->pnltype = sm750_द्विगुनTFT;
		पूर्ण अन्यथा अगर (!म_भेदन(opt, "18bit", म_माप("18bit"))) अणु
			sm750_dev->pnltype = sm750_dualTFT;
		पूर्ण अन्यथा अगर (!म_भेदन(opt, "24bit", म_माप("24bit"))) अणु
			sm750_dev->pnltype = sm750_24TFT;
		पूर्ण अन्यथा अगर (!म_भेदन(opt, "nohwc0", म_माप("nohwc0"))) अणु
			g_hwcursor &= ~0x1;
		पूर्ण अन्यथा अगर (!म_भेदन(opt, "nohwc1", म_माप("nohwc1"))) अणु
			g_hwcursor &= ~0x2;
		पूर्ण अन्यथा अगर (!म_भेदन(opt, "nohwc", म_माप("nohwc"))) अणु
			g_hwcursor = 0;
		पूर्ण अन्यथा अणु
			अगर (!g_fbmode[0]) अणु
				g_fbmode[0] = opt;
				dev_info(&sm750_dev->pdev->dev,
					 "find fbmode0 : %s\n", g_fbmode[0]);
			पूर्ण अन्यथा अगर (!g_fbmode[1]) अणु
				g_fbmode[1] = opt;
				dev_info(&sm750_dev->pdev->dev,
					 "find fbmode1 : %s\n", g_fbmode[1]);
			पूर्ण अन्यथा अणु
				dev_warn(&sm750_dev->pdev->dev, "How many view you wann set?\n");
			पूर्ण
		पूर्ण
	पूर्ण

NO_PARAM:
	अगर (sm750_dev->revid != SM750LE_REVISION_ID) अणु
		अगर (sm750_dev->fb_count > 1) अणु
			अगर (swap)
				sm750_dev->dataflow = sm750_dual_swap;
			अन्यथा
				sm750_dev->dataflow = sm750_dual_normal;
		पूर्ण अन्यथा अणु
			अगर (swap)
				sm750_dev->dataflow = sm750_simul_sec;
			अन्यथा
				sm750_dev->dataflow = sm750_simul_pri;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* SM750LE only have one crt channel */
		sm750_dev->dataflow = sm750_simul_sec;
		/* sm750le करो not have complex attributes */
		sm750_dev->nocrt = 0;
	पूर्ण
पूर्ण

अटल व्योम sm750fb_framebuffer_release(काष्ठा sm750_dev *sm750_dev)
अणु
	काष्ठा fb_info *fb_info;

	जबतक (sm750_dev->fb_count) अणु
		fb_info = sm750_dev->fbinfo[sm750_dev->fb_count - 1];
		unरेजिस्टर_framebuffer(fb_info);
		framebuffer_release(fb_info);
		sm750_dev->fb_count--;
	पूर्ण
पूर्ण

अटल पूर्णांक sm750fb_framebuffer_alloc(काष्ठा sm750_dev *sm750_dev, पूर्णांक fbidx)
अणु
	काष्ठा fb_info *fb_info;
	काष्ठा lynxfb_par *par;
	पूर्णांक err;

	fb_info = framebuffer_alloc(माप(काष्ठा lynxfb_par),
				    &sm750_dev->pdev->dev);
	अगर (!fb_info)
		वापस -ENOMEM;

	sm750_dev->fbinfo[fbidx] = fb_info;
	par = fb_info->par;
	par->dev = sm750_dev;

	err = lynxfb_set_fbinfo(fb_info, fbidx);
	अगर (err)
		जाओ release_fb;

	err = रेजिस्टर_framebuffer(fb_info);
	अगर (err < 0)
		जाओ release_fb;

	sm750_dev->fb_count++;

	वापस 0;

release_fb:
	framebuffer_release(fb_info);
	वापस err;
पूर्ण

अटल पूर्णांक lynxfb_kick_out_firmware_fb(काष्ठा pci_dev *pdev)
अणु
	काष्ठा apertures_काष्ठा *ap;
	bool primary = false;

	ap = alloc_apertures(1);
	अगर (!ap)
		वापस -ENOMEM;

	ap->ranges[0].base = pci_resource_start(pdev, 0);
	ap->ranges[0].size = pci_resource_len(pdev, 0);
#अगर_घोषित CONFIG_X86
	primary = pdev->resource[PCI_ROM_RESOURCE].flags &
					IORESOURCE_ROM_SHADOW;
#पूर्ण_अगर
	हटाओ_conflicting_framebuffers(ap, "sm750_fb1", primary);
	kमुक्त(ap);
	वापस 0;
पूर्ण

अटल पूर्णांक lynxfb_pci_probe(काष्ठा pci_dev *pdev,
			    स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा sm750_dev *sm750_dev = शून्य;
	पूर्णांक max_fb;
	पूर्णांक fbidx;
	पूर्णांक err;

	err = lynxfb_kick_out_firmware_fb(pdev);
	अगर (err)
		वापस err;

	/* enable device */
	err = pcim_enable_device(pdev);
	अगर (err)
		वापस err;

	err = -ENOMEM;
	sm750_dev = devm_kzalloc(&pdev->dev, माप(*sm750_dev), GFP_KERNEL);
	अगर (!sm750_dev)
		वापस err;

	sm750_dev->fbinfo[0] = sm750_dev->fbinfo[1] = शून्य;
	sm750_dev->devid = pdev->device;
	sm750_dev->revid = pdev->revision;
	sm750_dev->pdev = pdev;
	sm750_dev->mtrr_off = g_nomtrr;
	sm750_dev->mtrr.vram = 0;
	sm750_dev->accel_off = g_noaccel;
	spin_lock_init(&sm750_dev->slock);

	अगर (!sm750_dev->accel_off) अणु
		/*
		 * hook deInit and 2d routines, notes that below hw_xxx
		 * routine can work on most of lynx chips
		 * अगर some chip need specअगरic function,
		 * please hook it in smXXX_set_drv routine
		 */
		sm750_dev->accel.de_init = sm750_hw_de_init;
		sm750_dev->accel.de_fillrect = sm750_hw_fillrect;
		sm750_dev->accel.de_copyarea = sm750_hw_copyarea;
		sm750_dev->accel.de_imageblit = sm750_hw_imageblit;
	पूर्ण

	/* call chip specअगरic setup routine  */
	sm750fb_setup(sm750_dev, g_settings);

	/* call chip specअगरic mmap routine */
	err = hw_sm750_map(sm750_dev, pdev);
	अगर (err)
		वापस err;

	अगर (!sm750_dev->mtrr_off)
		sm750_dev->mtrr.vram = arch_phys_wc_add(sm750_dev->vidmem_start,
							sm750_dev->vidmem_size);

	स_रखो_io(sm750_dev->pvMem, 0, sm750_dev->vidmem_size);

	pci_set_drvdata(pdev, sm750_dev);

	/* call chipInit routine */
	hw_sm750_inithw(sm750_dev, pdev);

	/* allocate frame buffer info काष्ठाures according to g_dualview */
	max_fb = g_dualview ? 2 : 1;
	क्रम (fbidx = 0; fbidx < max_fb; fbidx++) अणु
		err = sm750fb_framebuffer_alloc(sm750_dev, fbidx);
		अगर (err)
			जाओ release_fb;
	पूर्ण

	वापस 0;

release_fb:
	sm750fb_framebuffer_release(sm750_dev);
	वापस err;
पूर्ण

अटल व्योम lynxfb_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा sm750_dev *sm750_dev;

	sm750_dev = pci_get_drvdata(pdev);

	sm750fb_framebuffer_release(sm750_dev);
	arch_phys_wc_del(sm750_dev->mtrr.vram);

	iounmap(sm750_dev->pvReg);
	iounmap(sm750_dev->pvMem);
	kमुक्त(g_settings);
पूर्ण

अटल पूर्णांक __init lynxfb_setup(अक्षर *options)
अणु
	पूर्णांक len;
	अक्षर *opt, *पंचांगp;

	अगर (!options || !*options) अणु
		pr_warn("no options.\n");
		वापस 0;
	पूर्ण

	pr_info("options:%s\n", options);

	len = म_माप(options) + 1;
	g_settings = kzalloc(len, GFP_KERNEL);
	अगर (!g_settings)
		वापस -ENOMEM;

	पंचांगp = g_settings;

	/*
	 * Notes:
	 * अक्षर * strsep(अक्षर **s,स्थिर अक्षर * ct);
	 * @s: the string to be searched
	 * @ct :the अक्षरacters to search क्रम
	 *
	 * strsep() updates @options to poपूर्णांकer after the first found token
	 * it also वापसs the poपूर्णांकer ahead the token.
	 */
	जबतक ((opt = strsep(&options, ":")) != शून्य) अणु
		/* options that mean क्रम any lynx chips are configured here */
		अगर (!म_भेदन(opt, "noaccel", म_माप("noaccel"))) अणु
			g_noaccel = 1;
		पूर्ण अन्यथा अगर (!म_भेदन(opt, "nomtrr", म_माप("nomtrr"))) अणु
			g_nomtrr = 1;
		पूर्ण अन्यथा अगर (!म_भेदन(opt, "dual", म_माप("dual"))) अणु
			g_dualview = 1;
		पूर्ण अन्यथा अणु
			म_जोड़ो(पंचांगp, opt);
			पंचांगp += म_माप(opt);
			अगर (options)
				*पंचांगp++ = ':';
			अन्यथा
				*पंचांगp++ = 0;
		पूर्ण
	पूर्ण

	/* misc g_settings are transport to chip specअगरic routines */
	pr_info("parameter left for chip specific analysis:%s\n", g_settings);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pci_device_id smi_pci_table[] = अणु
	अणु PCI_DEVICE(0x126f, 0x0750), पूर्ण,
	अणु0,पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, smi_pci_table);

अटल SIMPLE_DEV_PM_OPS(lynxfb_pm_ops, lynxfb_suspend, lynxfb_resume);

अटल काष्ठा pci_driver lynxfb_driver = अणु
	.name =		"sm750fb",
	.id_table =	smi_pci_table,
	.probe =	lynxfb_pci_probe,
	.हटाओ =	lynxfb_pci_हटाओ,
	.driver.pm =	&lynxfb_pm_ops,
पूर्ण;

अटल पूर्णांक __init lynxfb_init(व्योम)
अणु
	अक्षर *option;

#अगर_घोषित MODULE
	option = g_option;
#अन्यथा
	अगर (fb_get_options("sm750fb", &option))
		वापस -ENODEV;
#पूर्ण_अगर

	lynxfb_setup(option);
	वापस pci_रेजिस्टर_driver(&lynxfb_driver);
पूर्ण
module_init(lynxfb_init);

अटल व्योम __निकास lynxfb_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&lynxfb_driver);
पूर्ण
module_निकास(lynxfb_निकास);

module_param(g_option, अक्षरp, 0444);

MODULE_PARM_DESC(g_option,
		 "\n\t\tCommon options:\n"
		 "\t\tnoaccel:disable 2d capabilities\n"
		 "\t\tnomtrr:disable MTRR attribute for video memory\n"
		 "\t\tdualview:dual frame buffer feature enabled\n"
		 "\t\tnohwc:disable hardware cursor\n"
		 "\t\tUsual example:\n"
		 "\t\tinsmod ./sm750fb.ko g_option=\"noaccel,nohwc,1280x1024-8@60\"\n"
		 );

MODULE_AUTHOR("monk liu <monk.liu@siliconmotion.com>");
MODULE_AUTHOR("Sudip Mukherjee <sudip@vectorindia.org>");
MODULE_DESCRIPTION("Frame buffer driver for SM750 chipset");
MODULE_LICENSE("Dual BSD/GPL");
