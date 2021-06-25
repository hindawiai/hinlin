<शैली गुरु>
/*
 * linux/drivers/video/hecubafb.c -- FB driver क्रम Hecuba/Apollo controller
 *
 * Copyright (C) 2006, Jaya Kumar
 * This work was sponsored by CIS(M) Sdn Bhd
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License. See the file COPYING in the मुख्य directory of this archive क्रम
 * more details.
 *
 * Layout is based on skeletonfb.c by James Simmons and Geert Uytterhoeven.
 * This work was possible because of apollo display code from E-Ink's website
 * http://support.eink.com/community
 * All inक्रमmation used to ग_लिखो this code is from खुला material made
 * available by E-Ink on its support site. Some commands such as 0xA4
 * were found by looping through cmd=0x00 thru 0xFF and supplying अक्रमom
 * values. There are other commands that the display is capable of,
 * beyond the 5 used here but they are more complex.
 *
 * This driver is written to be used with the Hecuba display architecture.
 * The actual display chip is called Apollo and the पूर्णांकerface electronics
 * it needs is called Hecuba.
 *
 * It is पूर्णांकended to be architecture independent. A board specअगरic driver
 * must be used to perक्रमm all the physical IO पूर्णांकeractions. An example
 * is provided as n411.c
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
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/list.h>
#समावेश <linux/uaccess.h>

#समावेश <video/hecubafb.h>

/* Display specअगरic inक्रमmation */
#घोषणा DPY_W 600
#घोषणा DPY_H 800

अटल स्थिर काष्ठा fb_fix_screeninfo hecubafb_fix = अणु
	.id =		"hecubafb",
	.type =		FB_TYPE_PACKED_PIXELS,
	.visual =	FB_VISUAL_MONO01,
	.xpanstep =	0,
	.ypanstep =	0,
	.ywrapstep =	0,
	.line_length =	DPY_W,
	.accel =	FB_ACCEL_NONE,
पूर्ण;

अटल स्थिर काष्ठा fb_var_screeninfo hecubafb_var = अणु
	.xres		= DPY_W,
	.yres		= DPY_H,
	.xres_भव	= DPY_W,
	.yres_भव	= DPY_H,
	.bits_per_pixel	= 1,
	.nonstd		= 1,
पूर्ण;

/* मुख्य hecubafb functions */

अटल व्योम apollo_send_data(काष्ठा hecubafb_par *par, अचिन्हित अक्षर data)
अणु
	/* set data */
	par->board->set_data(par, data);

	/* set DS low */
	par->board->set_ctl(par, HCB_DS_BIT, 0);

	/* रुको क्रम ack */
	par->board->रुको_क्रम_ack(par, 0);

	/* set DS hi */
	par->board->set_ctl(par, HCB_DS_BIT, 1);

	/* रुको क्रम ack to clear */
	par->board->रुको_क्रम_ack(par, 1);
पूर्ण

अटल व्योम apollo_send_command(काष्ठा hecubafb_par *par, अचिन्हित अक्षर data)
अणु
	/* command so set CD to high */
	par->board->set_ctl(par, HCB_CD_BIT, 1);

	/* actually strobe with command */
	apollo_send_data(par, data);

	/* clear CD back to low */
	par->board->set_ctl(par, HCB_CD_BIT, 0);
पूर्ण

अटल व्योम hecubafb_dpy_update(काष्ठा hecubafb_par *par)
अणु
	पूर्णांक i;
	अचिन्हित अक्षर *buf = (अचिन्हित अक्षर __क्रमce *)par->info->screen_base;

	apollo_send_command(par, APOLLO_START_NEW_IMG);

	क्रम (i=0; i < (DPY_W*DPY_H/8); i++) अणु
		apollo_send_data(par, *(buf++));
	पूर्ण

	apollo_send_command(par, APOLLO_STOP_IMG_DATA);
	apollo_send_command(par, APOLLO_DISPLAY_IMG);
पूर्ण

/* this is called back from the deferred io workqueue */
अटल व्योम hecubafb_dpy_deferred_io(काष्ठा fb_info *info,
				काष्ठा list_head *pagelist)
अणु
	hecubafb_dpy_update(info->par);
पूर्ण

अटल व्योम hecubafb_fillrect(काष्ठा fb_info *info,
				   स्थिर काष्ठा fb_fillrect *rect)
अणु
	काष्ठा hecubafb_par *par = info->par;

	sys_fillrect(info, rect);

	hecubafb_dpy_update(par);
पूर्ण

अटल व्योम hecubafb_copyarea(काष्ठा fb_info *info,
				   स्थिर काष्ठा fb_copyarea *area)
अणु
	काष्ठा hecubafb_par *par = info->par;

	sys_copyarea(info, area);

	hecubafb_dpy_update(par);
पूर्ण

अटल व्योम hecubafb_imageblit(काष्ठा fb_info *info,
				स्थिर काष्ठा fb_image *image)
अणु
	काष्ठा hecubafb_par *par = info->par;

	sys_imageblit(info, image);

	hecubafb_dpy_update(par);
पूर्ण

/*
 * this is the slow path from userspace. they can seek and ग_लिखो to
 * the fb. it's inefficient to करो anything less than a full screen draw
 */
अटल sमाप_प्रकार hecubafb_ग_लिखो(काष्ठा fb_info *info, स्थिर अक्षर __user *buf,
				माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा hecubafb_par *par = info->par;
	अचिन्हित दीर्घ p = *ppos;
	व्योम *dst;
	पूर्णांक err = 0;
	अचिन्हित दीर्घ total_size;

	अगर (info->state != FBINFO_STATE_RUNNING)
		वापस -EPERM;

	total_size = info->fix.smem_len;

	अगर (p > total_size)
		वापस -EFBIG;

	अगर (count > total_size) अणु
		err = -EFBIG;
		count = total_size;
	पूर्ण

	अगर (count + p > total_size) अणु
		अगर (!err)
			err = -ENOSPC;

		count = total_size - p;
	पूर्ण

	dst = (व्योम __क्रमce *) (info->screen_base + p);

	अगर (copy_from_user(dst, buf, count))
		err = -EFAULT;

	अगर  (!err)
		*ppos += count;

	hecubafb_dpy_update(par);

	वापस (err) ? err : count;
पूर्ण

अटल स्थिर काष्ठा fb_ops hecubafb_ops = अणु
	.owner		= THIS_MODULE,
	.fb_पढ़ो        = fb_sys_पढ़ो,
	.fb_ग_लिखो	= hecubafb_ग_लिखो,
	.fb_fillrect	= hecubafb_fillrect,
	.fb_copyarea	= hecubafb_copyarea,
	.fb_imageblit	= hecubafb_imageblit,
पूर्ण;

अटल काष्ठा fb_deferred_io hecubafb_defio = अणु
	.delay		= HZ,
	.deferred_io	= hecubafb_dpy_deferred_io,
पूर्ण;

अटल पूर्णांक hecubafb_probe(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा fb_info *info;
	काष्ठा hecuba_board *board;
	पूर्णांक retval = -ENOMEM;
	पूर्णांक videomemorysize;
	अचिन्हित अक्षर *videomemory;
	काष्ठा hecubafb_par *par;

	/* pick up board specअगरic routines */
	board = dev->dev.platक्रमm_data;
	अगर (!board)
		वापस -EINVAL;

	/* try to count device specअगरic driver, अगर can't, platक्रमm recalls */
	अगर (!try_module_get(board->owner))
		वापस -ENODEV;

	videomemorysize = (DPY_W*DPY_H)/8;

	videomemory = vzalloc(videomemorysize);
	अगर (!videomemory)
		जाओ err_videomem_alloc;

	info = framebuffer_alloc(माप(काष्ठा hecubafb_par), &dev->dev);
	अगर (!info)
		जाओ err_fballoc;

	info->screen_base = (अक्षर __क्रमce __iomem *)videomemory;
	info->fbops = &hecubafb_ops;

	info->var = hecubafb_var;
	info->fix = hecubafb_fix;
	info->fix.smem_len = videomemorysize;
	par = info->par;
	par->info = info;
	par->board = board;
	par->send_command = apollo_send_command;
	par->send_data = apollo_send_data;

	info->flags = FBINFO_FLAG_DEFAULT | FBINFO_VIRTFB;

	info->fbdefio = &hecubafb_defio;
	fb_deferred_io_init(info);

	retval = रेजिस्टर_framebuffer(info);
	अगर (retval < 0)
		जाओ err_fbreg;
	platक्रमm_set_drvdata(dev, info);

	fb_info(info, "Hecuba frame buffer device, using %dK of video memory\n",
		videomemorysize >> 10);

	/* this inits the dpy */
	retval = par->board->init(par);
	अगर (retval < 0)
		जाओ err_fbreg;

	वापस 0;
err_fbreg:
	framebuffer_release(info);
err_fballoc:
	vमुक्त(videomemory);
err_videomem_alloc:
	module_put(board->owner);
	वापस retval;
पूर्ण

अटल पूर्णांक hecubafb_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा fb_info *info = platक्रमm_get_drvdata(dev);

	अगर (info) अणु
		काष्ठा hecubafb_par *par = info->par;
		fb_deferred_io_cleanup(info);
		unरेजिस्टर_framebuffer(info);
		vमुक्त((व्योम __क्रमce *)info->screen_base);
		अगर (par->board->हटाओ)
			par->board->हटाओ(par);
		module_put(par->board->owner);
		framebuffer_release(info);
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver hecubafb_driver = अणु
	.probe	= hecubafb_probe,
	.हटाओ = hecubafb_हटाओ,
	.driver	= अणु
		.name	= "hecubafb",
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(hecubafb_driver);

MODULE_DESCRIPTION("fbdev driver for Hecuba/Apollo controller");
MODULE_AUTHOR("Jaya Kumar");
MODULE_LICENSE("GPL");
