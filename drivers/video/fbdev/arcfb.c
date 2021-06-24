<शैली गुरु>
/*
 * linux/drivers/video/arcfb.c -- FB driver क्रम Arc monochrome LCD board
 *
 * Copyright (C) 2005, Jaya Kumar <jayalk@पूर्णांकworks.biz>
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License. See the file COPYING in the मुख्य directory of this archive क्रम
 * more details.
 *
 * Layout is based on skeletonfb.c by James Simmons and Geert Uytterhoeven.
 *
 * This driver was written to be used with the Arc LCD board. Arc uses a
 * set of KS108 chips that control inभागidual 64x64 LCD matrices. The board
 * can be paneled in a variety of setups such as 2x1=128x64, 4x4=256x256 and
 * so on. The पूर्णांकerface between the board and the host is TTL based GPIO. The
 * GPIO requirements are 8 writable data lines and 4+n lines क्रम control. On a
 * GPIO-less प्रणाली, the board can be tested by connecting the respective sigs
 * up to a parallel port connector. The driver requires the IO addresses क्रम
 * data and control GPIO at load समय. It is unable to probe क्रम the
 * existence of the LCD so it must be told at load समय whether it should
 * be enabled or not.
 *
 * Toकरो:
 * - testing with 4x4
 * - testing with पूर्णांकerrupt hw
 *
 * General notes:
 * - User must set tuhold. It's in microseconds. According to the 108 spec,
 *   the hold समय is supposed to be at least 1 microsecond.
 * - User must set num_cols=x num_rows=y, eg: x=2 means 128
 * - User must set arcfb_enable=1 to enable it
 * - User must set dio_addr=0xIOADDR cio_addr=0xIOADDR
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/fb.h>
#समावेश <linux/init.h>
#समावेश <linux/arcfb.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <linux/uaccess.h>

#घोषणा न्यूनमान8(a) (a&(~0x07))
#घोषणा न्यूनमानXres(a,xres) (a&(~(xres - 1)))
#घोषणा iउच्चमान8(a) (((पूर्णांक)((a+7)/8))*8)
#घोषणा उच्चमान64(a) (a|0x3F)
#घोषणा उच्चमानXres(a,xres) (a|(xres - 1))

/* ks108 chipset specअगरic defines and code */

#घोषणा KS_SET_DPY_START_LINE 	0xC0
#घोषणा KS_SET_PAGE_NUM 	0xB8
#घोषणा KS_SET_X 		0x40
#घोषणा KS_CEHI 		0x01
#घोषणा KS_CELO 		0x00
#घोषणा KS_SEL_CMD 		0x08
#घोषणा KS_SEL_DATA 		0x00
#घोषणा KS_DPY_ON 		0x3F
#घोषणा KS_DPY_OFF 		0x3E
#घोषणा KS_INTACK 		0x40
#घोषणा KS_CLRINT		0x02

काष्ठा arcfb_par अणु
	अचिन्हित दीर्घ dio_addr;
	अचिन्हित दीर्घ cio_addr;
	अचिन्हित दीर्घ c2io_addr;
	atomic_t ref_count;
	अचिन्हित अक्षर cslut[9];
	काष्ठा fb_info *info;
	अचिन्हित पूर्णांक irq;
	spinlock_t lock;
पूर्ण;

अटल स्थिर काष्ठा fb_fix_screeninfo arcfb_fix = अणु
	.id =		"arcfb",
	.type =		FB_TYPE_PACKED_PIXELS,
	.visual =	FB_VISUAL_MONO01,
	.xpanstep =	0,
	.ypanstep =	1,
	.ywrapstep =	0,
	.accel =	FB_ACCEL_NONE,
पूर्ण;

अटल स्थिर काष्ठा fb_var_screeninfo arcfb_var = अणु
	.xres		= 128,
	.yres		= 64,
	.xres_भव	= 128,
	.yres_भव	= 64,
	.bits_per_pixel	= 1,
	.nonstd		= 1,
पूर्ण;

अटल अचिन्हित दीर्घ num_cols;
अटल अचिन्हित दीर्घ num_rows;
अटल अचिन्हित दीर्घ dio_addr;
अटल अचिन्हित दीर्घ cio_addr;
अटल अचिन्हित दीर्घ c2io_addr;
अटल अचिन्हित दीर्घ splashval;
अटल अचिन्हित दीर्घ tuhold;
अटल अचिन्हित पूर्णांक nosplash;
अटल अचिन्हित पूर्णांक arcfb_enable;
अटल अचिन्हित पूर्णांक irq;

अटल DECLARE_WAIT_QUEUE_HEAD(arcfb_रुकोq);

अटल व्योम ks108_ग_लिखोb_ctl(काष्ठा arcfb_par *par,
				अचिन्हित पूर्णांक chipindex, अचिन्हित अक्षर value)
अणु
	अचिन्हित अक्षर chipselval = par->cslut[chipindex];

	outb(chipselval|KS_CEHI|KS_SEL_CMD, par->cio_addr);
	outb(value, par->dio_addr);
	udelay(tuhold);
	outb(chipselval|KS_CELO|KS_SEL_CMD, par->cio_addr);
पूर्ण

अटल व्योम ks108_ग_लिखोb_मुख्यctl(काष्ठा arcfb_par *par, अचिन्हित अक्षर value)
अणु

	outb(value, par->cio_addr);
	udelay(tuhold);
पूर्ण

अटल अचिन्हित अक्षर ks108_पढ़ोb_ctl2(काष्ठा arcfb_par *par)
अणु
	वापस inb(par->c2io_addr);
पूर्ण

अटल व्योम ks108_ग_लिखोb_data(काष्ठा arcfb_par *par,
				अचिन्हित पूर्णांक chipindex, अचिन्हित अक्षर value)
अणु
	अचिन्हित अक्षर chipselval = par->cslut[chipindex];

	outb(chipselval|KS_CEHI|KS_SEL_DATA, par->cio_addr);
	outb(value, par->dio_addr);
	udelay(tuhold);
	outb(chipselval|KS_CELO|KS_SEL_DATA, par->cio_addr);
पूर्ण

अटल व्योम ks108_set_start_line(काष्ठा arcfb_par *par,
				अचिन्हित पूर्णांक chipindex, अचिन्हित अक्षर y)
अणु
	ks108_ग_लिखोb_ctl(par, chipindex, KS_SET_DPY_START_LINE|y);
पूर्ण

अटल व्योम ks108_set_yaddr(काष्ठा arcfb_par *par,
				अचिन्हित पूर्णांक chipindex, अचिन्हित अक्षर y)
अणु
	ks108_ग_लिखोb_ctl(par, chipindex, KS_SET_PAGE_NUM|y);
पूर्ण

अटल व्योम ks108_set_xaddr(काष्ठा arcfb_par *par,
				अचिन्हित पूर्णांक chipindex, अचिन्हित अक्षर x)
अणु
	ks108_ग_लिखोb_ctl(par, chipindex, KS_SET_X|x);
पूर्ण

अटल व्योम ks108_clear_lcd(काष्ठा arcfb_par *par, अचिन्हित पूर्णांक chipindex)
अणु
	पूर्णांक i,j;

	क्रम (i = 0; i <= 8; i++) अणु
		ks108_set_yaddr(par, chipindex, i);
		ks108_set_xaddr(par, chipindex, 0);
		क्रम (j = 0; j < 64; j++) अणु
			ks108_ग_लिखोb_data(par, chipindex,
				(अचिन्हित अक्षर) splashval);
		पूर्ण
	पूर्ण
पूर्ण

/* मुख्य arcfb functions */

अटल पूर्णांक arcfb_खोलो(काष्ठा fb_info *info, पूर्णांक user)
अणु
	काष्ठा arcfb_par *par = info->par;

	atomic_inc(&par->ref_count);
	वापस 0;
पूर्ण

अटल पूर्णांक arcfb_release(काष्ठा fb_info *info, पूर्णांक user)
अणु
	काष्ठा arcfb_par *par = info->par;
	पूर्णांक count = atomic_पढ़ो(&par->ref_count);

	अगर (!count)
		वापस -EINVAL;
	atomic_dec(&par->ref_count);
	वापस 0;
पूर्ण

अटल पूर्णांक arcfb_pan_display(काष्ठा fb_var_screeninfo *var,
				काष्ठा fb_info *info)
अणु
	पूर्णांक i;
	काष्ठा arcfb_par *par = info->par;

	अगर ((var->vmode & FB_VMODE_YWRAP) && (var->yoffset < 64)
		&& (info->var.yres <= 64)) अणु
		क्रम (i = 0; i < num_cols; i++) अणु
			ks108_set_start_line(par, i, var->yoffset);
		पूर्ण
		info->var.yoffset = var->yoffset;
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल irqवापस_t arcfb_पूर्णांकerrupt(पूर्णांक vec, व्योम *dev_instance)
अणु
	काष्ठा fb_info *info = dev_instance;
	अचिन्हित अक्षर ctl2status;
	काष्ठा arcfb_par *par = info->par;

	ctl2status = ks108_पढ़ोb_ctl2(par);

	अगर (!(ctl2status & KS_INTACK)) /* not arc generated पूर्णांकerrupt */
		वापस IRQ_NONE;

	ks108_ग_लिखोb_मुख्यctl(par, KS_CLRINT);

	spin_lock(&par->lock);
        अगर (रुकोqueue_active(&arcfb_रुकोq)) अणु
                wake_up(&arcfb_रुकोq);
        पूर्ण
	spin_unlock(&par->lock);

	वापस IRQ_HANDLED;
पूर्ण

/*
 * here we handle a specअगरic page on the lcd. the complनिकासy comes from
 * the fact that the fb is laiकरोut in 8xX vertical columns. we extract
 * each ग_लिखो of 8 vertical pixels. then we shअगरt out as we move aदीर्घ
 * X. That's what rightshअगरt करोes. biपंचांगask selects the desired input bit.
 */
अटल व्योम arcfb_lcd_update_page(काष्ठा arcfb_par *par, अचिन्हित पूर्णांक upper,
		अचिन्हित पूर्णांक left, अचिन्हित पूर्णांक right, अचिन्हित पूर्णांक distance)
अणु
	अचिन्हित अक्षर *src;
	अचिन्हित पूर्णांक xindex, yindex, chipindex, linesize;
	पूर्णांक i;
	अचिन्हित अक्षर val;
	अचिन्हित अक्षर biपंचांगask, rightshअगरt;

	xindex = left >> 6;
	yindex = upper >> 6;
	chipindex = (xindex + (yindex*num_cols));

	ks108_set_yaddr(par, chipindex, upper/8);

	linesize = par->info->var.xres/8;
	src = (अचिन्हित अक्षर __क्रमce *) par->info->screen_base + (left/8) +
		(upper * linesize);
	ks108_set_xaddr(par, chipindex, left);

	biपंचांगask=1;
	rightshअगरt=0;
	जबतक (left <= right) अणु
		val = 0;
		क्रम (i = 0; i < 8; i++) अणु
			अगर ( i > rightshअगरt) अणु
				val |= (*(src + (i*linesize)) & biपंचांगask)
						<< (i - rightshअगरt);
			पूर्ण अन्यथा अणु
				val |= (*(src + (i*linesize)) & biपंचांगask)
						 >> (rightshअगरt - i);
			पूर्ण
		पूर्ण
		ks108_ग_लिखोb_data(par, chipindex, val);
		left++;
		अगर (biपंचांगask == 0x80) अणु
			biपंचांगask = 1;
			src++;
			rightshअगरt=0;
		पूर्ण अन्यथा अणु
			biपंचांगask <<= 1;
			rightshअगरt++;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * here we handle the entire vertical page of the update. we ग_लिखो across
 * lcd chips. update_page uses the upper/left values to decide which
 * chip to select क्रम the right. upper is needed क्रम setting the page
 * desired क्रम the ग_लिखो.
 */
अटल व्योम arcfb_lcd_update_vert(काष्ठा arcfb_par *par, अचिन्हित पूर्णांक top,
		अचिन्हित पूर्णांक bottom, अचिन्हित पूर्णांक left, अचिन्हित पूर्णांक right)
अणु
	अचिन्हित पूर्णांक distance, upper, lower;

	distance = (bottom - top) + 1;
	upper = top;
	lower = top + 7;

	जबतक (distance > 0) अणु
		distance -= 8;
		arcfb_lcd_update_page(par, upper, left, right, 8);
		upper = lower + 1;
		lower = upper + 7;
	पूर्ण
पूर्ण

/*
 * here we handle horizontal blocks क्रम the update. update_vert will
 * handle spaning multiple pages. we अवरोध out each horizontal
 * block in to inभागidual blocks no taller than 64 pixels.
 */
अटल व्योम arcfb_lcd_update_horiz(काष्ठा arcfb_par *par, अचिन्हित पूर्णांक left,
			अचिन्हित पूर्णांक right, अचिन्हित पूर्णांक top, अचिन्हित पूर्णांक h)
अणु
	अचिन्हित पूर्णांक distance, upper, lower;

	distance = h;
	upper = न्यूनमान8(top);
	lower = min(upper + distance - 1, उच्चमान64(upper));

	जबतक (distance > 0) अणु
		distance -= ((lower - upper) + 1 );
		arcfb_lcd_update_vert(par, upper, lower, left, right);
		upper = lower + 1;
		lower = min(upper + distance - 1, उच्चमान64(upper));
	पूर्ण
पूर्ण

/*
 * here we start the process of splitting out the fb update पूर्णांकo
 * inभागidual blocks of pixels. we end up splitting पूर्णांकo 64x64 blocks
 * and finally करोwn to 64x8 pages.
 */
अटल व्योम arcfb_lcd_update(काष्ठा arcfb_par *par, अचिन्हित पूर्णांक dx,
			अचिन्हित पूर्णांक dy, अचिन्हित पूर्णांक w, अचिन्हित पूर्णांक h)
अणु
	अचिन्हित पूर्णांक left, right, distance, y;

	/* align the request first */
	y = न्यूनमान8(dy);
	h += dy - y;
	h = iउच्चमान8(h);

	distance = w;
	left = dx;
	right = min(left + w - 1, उच्चमान64(left));

	जबतक (distance > 0) अणु
		arcfb_lcd_update_horiz(par, left, right, y, h);
		distance -= ((right - left) + 1);
		left = right + 1;
		right = min(left + distance - 1, उच्चमान64(left));
	पूर्ण
पूर्ण

अटल व्योम arcfb_fillrect(काष्ठा fb_info *info,
			   स्थिर काष्ठा fb_fillrect *rect)
अणु
	काष्ठा arcfb_par *par = info->par;

	sys_fillrect(info, rect);

	/* update the physical lcd */
	arcfb_lcd_update(par, rect->dx, rect->dy, rect->width, rect->height);
पूर्ण

अटल व्योम arcfb_copyarea(काष्ठा fb_info *info,
			   स्थिर काष्ठा fb_copyarea *area)
अणु
	काष्ठा arcfb_par *par = info->par;

	sys_copyarea(info, area);

	/* update the physical lcd */
	arcfb_lcd_update(par, area->dx, area->dy, area->width, area->height);
पूर्ण

अटल व्योम arcfb_imageblit(काष्ठा fb_info *info, स्थिर काष्ठा fb_image *image)
अणु
	काष्ठा arcfb_par *par = info->par;

	sys_imageblit(info, image);

	/* update the physical lcd */
	arcfb_lcd_update(par, image->dx, image->dy, image->width,
				image->height);
पूर्ण

अटल पूर्णांक arcfb_ioctl(काष्ठा fb_info *info,
			  अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	व्योम __user *argp = (व्योम __user *)arg;
	काष्ठा arcfb_par *par = info->par;
	अचिन्हित दीर्घ flags;

	चयन (cmd) अणु
		हाल FBIO_WAITEVENT:
		अणु
			DEFINE_WAIT(रुको);
			/* illegal to रुको on arc अगर no irq will occur */
			अगर (!par->irq)
				वापस -EINVAL;

			/* रुको until the Arc has generated an पूर्णांकerrupt
			 * which will wake us up */
			spin_lock_irqsave(&par->lock, flags);
			prepare_to_रुको(&arcfb_रुकोq, &रुको,
					TASK_INTERRUPTIBLE);
			spin_unlock_irqrestore(&par->lock, flags);
			schedule();
			finish_रुको(&arcfb_रुकोq, &रुको);
		पूर्ण
		fallthrough;

		हाल FBIO_GETCONTROL2:
		अणु
			अचिन्हित अक्षर ctl2;

			ctl2 = ks108_पढ़ोb_ctl2(info->par);
			अगर (copy_to_user(argp, &ctl2, माप(ctl2)))
				वापस -EFAULT;
			वापस 0;
		पूर्ण
		शेष:
			वापस -EINVAL;
	पूर्ण
पूर्ण

/*
 * this is the access path from userspace. they can seek and ग_लिखो to
 * the fb. it's inefficient क्रम them to करो anything less than 64*8
 * ग_लिखोs since we update the lcd in each ग_लिखो() anyway.
 */
अटल sमाप_प्रकार arcfb_ग_लिखो(काष्ठा fb_info *info, स्थिर अक्षर __user *buf,
			   माप_प्रकार count, loff_t *ppos)
अणु
	/* modded from epson 1355 */

	अचिन्हित दीर्घ p;
	पूर्णांक err=-EINVAL;
	अचिन्हित पूर्णांक fbmemlength,x,y,w,h, bitppos, startpos, endpos, bitcount;
	काष्ठा arcfb_par *par;
	अचिन्हित पूर्णांक xres;

	p = *ppos;
	par = info->par;
	xres = info->var.xres;
	fbmemlength = (xres * info->var.yres)/8;

	अगर (p > fbmemlength)
		वापस -ENOSPC;

	err = 0;
	अगर ((count + p) > fbmemlength) अणु
		count = fbmemlength - p;
		err = -ENOSPC;
	पूर्ण

	अगर (count) अणु
		अक्षर *base_addr;

		base_addr = (अक्षर __क्रमce *)info->screen_base;
		count -= copy_from_user(base_addr + p, buf, count);
		*ppos += count;
		err = -EFAULT;
	पूर्ण


	bitppos = p*8;
	startpos = न्यूनमानXres(bitppos, xres);
	endpos = उच्चमानXres((bitppos + (count*8)), xres);
	bitcount = endpos - startpos;

	x = startpos % xres;
	y = startpos / xres;
	w = xres;
	h = bitcount / xres;
	arcfb_lcd_update(par, x, y, w, h);

	अगर (count)
		वापस count;
	वापस err;
पूर्ण

अटल स्थिर काष्ठा fb_ops arcfb_ops = अणु
	.owner		= THIS_MODULE,
	.fb_खोलो	= arcfb_खोलो,
	.fb_पढ़ो        = fb_sys_पढ़ो,
	.fb_ग_लिखो	= arcfb_ग_लिखो,
	.fb_release	= arcfb_release,
	.fb_pan_display	= arcfb_pan_display,
	.fb_fillrect	= arcfb_fillrect,
	.fb_copyarea	= arcfb_copyarea,
	.fb_imageblit	= arcfb_imageblit,
	.fb_ioctl 	= arcfb_ioctl,
पूर्ण;

अटल पूर्णांक arcfb_probe(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा fb_info *info;
	पूर्णांक retval = -ENOMEM;
	पूर्णांक videomemorysize;
	अचिन्हित अक्षर *videomemory;
	काष्ठा arcfb_par *par;
	पूर्णांक i;

	videomemorysize = (((64*64)*num_cols)*num_rows)/8;

	/* We need a flat backing store क्रम the Arc's
	   less-flat actual paged framebuffer */
	videomemory = vzalloc(videomemorysize);
	अगर (!videomemory)
		वापस retval;

	info = framebuffer_alloc(माप(काष्ठा arcfb_par), &dev->dev);
	अगर (!info)
		जाओ err;

	info->screen_base = (अक्षर __iomem *)videomemory;
	info->fbops = &arcfb_ops;

	info->var = arcfb_var;
	info->fix = arcfb_fix;
	par = info->par;
	par->info = info;

	अगर (!dio_addr || !cio_addr || !c2io_addr) अणु
		prपूर्णांकk(KERN_WARNING "no IO addresses supplied\n");
		जाओ err1;
	पूर्ण
	par->dio_addr = dio_addr;
	par->cio_addr = cio_addr;
	par->c2io_addr = c2io_addr;
	par->cslut[0] = 0x00;
	par->cslut[1] = 0x06;
	info->flags = FBINFO_FLAG_DEFAULT;
	spin_lock_init(&par->lock);
	अगर (irq) अणु
		par->irq = irq;
		अगर (request_irq(par->irq, &arcfb_पूर्णांकerrupt, IRQF_SHARED,
				"arcfb", info)) अणु
			prपूर्णांकk(KERN_INFO
				"arcfb: Failed req IRQ %d\n", par->irq);
			retval = -EBUSY;
			जाओ err1;
		पूर्ण
	पूर्ण
	retval = रेजिस्टर_framebuffer(info);
	अगर (retval < 0)
		जाओ err1;
	platक्रमm_set_drvdata(dev, info);
	fb_info(info, "Arc frame buffer device, using %dK of video memory\n",
		videomemorysize >> 10);

	/* this inits the lcd but करोesn't clear dirty pixels */
	क्रम (i = 0; i < num_cols * num_rows; i++) अणु
		ks108_ग_लिखोb_ctl(par, i, KS_DPY_OFF);
		ks108_set_start_line(par, i, 0);
		ks108_set_yaddr(par, i, 0);
		ks108_set_xaddr(par, i, 0);
		ks108_ग_लिखोb_ctl(par, i, KS_DPY_ON);
	पूर्ण

	/* अगर we were told to splash the screen, we just clear it */
	अगर (!nosplash) अणु
		क्रम (i = 0; i < num_cols * num_rows; i++) अणु
			fb_info(info, "splashing lcd %d\n", i);
			ks108_set_start_line(par, i, 0);
			ks108_clear_lcd(par, i);
		पूर्ण
	पूर्ण

	वापस 0;
err1:
	framebuffer_release(info);
err:
	vमुक्त(videomemory);
	वापस retval;
पूर्ण

अटल पूर्णांक arcfb_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा fb_info *info = platक्रमm_get_drvdata(dev);

	अगर (info) अणु
		unरेजिस्टर_framebuffer(info);
		अगर (irq)
			मुक्त_irq(((काष्ठा arcfb_par *)(info->par))->irq, info);
		vमुक्त((व्योम __क्रमce *)info->screen_base);
		framebuffer_release(info);
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver arcfb_driver = अणु
	.probe	= arcfb_probe,
	.हटाओ = arcfb_हटाओ,
	.driver	= अणु
		.name	= "arcfb",
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device *arcfb_device;

अटल पूर्णांक __init arcfb_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (!arcfb_enable)
		वापस -ENXIO;

	ret = platक्रमm_driver_रेजिस्टर(&arcfb_driver);
	अगर (!ret) अणु
		arcfb_device = platक्रमm_device_alloc("arcfb", 0);
		अगर (arcfb_device) अणु
			ret = platक्रमm_device_add(arcfb_device);
		पूर्ण अन्यथा अणु
			ret = -ENOMEM;
		पूर्ण
		अगर (ret) अणु
			platक्रमm_device_put(arcfb_device);
			platक्रमm_driver_unरेजिस्टर(&arcfb_driver);
		पूर्ण
	पूर्ण
	वापस ret;

पूर्ण

अटल व्योम __निकास arcfb_निकास(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(arcfb_device);
	platक्रमm_driver_unरेजिस्टर(&arcfb_driver);
पूर्ण

module_param(num_cols, uदीर्घ, 0);
MODULE_PARM_DESC(num_cols, "Num horiz panels, eg: 2 = 128 bit wide");
module_param(num_rows, uदीर्घ, 0);
MODULE_PARM_DESC(num_rows, "Num vert panels, eg: 1 = 64 bit high");
module_param(nosplash, uपूर्णांक, 0);
MODULE_PARM_DESC(nosplash, "Disable doing the splash screen");
module_param(arcfb_enable, uपूर्णांक, 0);
MODULE_PARM_DESC(arcfb_enable, "Enable communication with Arc board");
module_param_hw(dio_addr, uदीर्घ, ioport, 0);
MODULE_PARM_DESC(dio_addr, "IO address for data, eg: 0x480");
module_param_hw(cio_addr, uदीर्घ, ioport, 0);
MODULE_PARM_DESC(cio_addr, "IO address for control, eg: 0x400");
module_param_hw(c2io_addr, uदीर्घ, ioport, 0);
MODULE_PARM_DESC(c2io_addr, "IO address for secondary control, eg: 0x408");
module_param(splashval, uदीर्घ, 0);
MODULE_PARM_DESC(splashval, "Splash pattern: 0xFF is black, 0x00 is green");
module_param(tuhold, uदीर्घ, 0);
MODULE_PARM_DESC(tuhold, "Time to hold between strobing data to Arc board");
module_param_hw(irq, uपूर्णांक, irq, 0);
MODULE_PARM_DESC(irq, "IRQ for the Arc board");

module_init(arcfb_init);
module_निकास(arcfb_निकास);

MODULE_DESCRIPTION("fbdev driver for Arc monochrome LCD board");
MODULE_AUTHOR("Jaya Kumar");
MODULE_LICENSE("GPL");

