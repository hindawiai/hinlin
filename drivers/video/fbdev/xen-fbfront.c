<शैली गुरु>
/*
 * Xen para-भव frame buffer device
 *
 * Copyright (C) 2005-2006 Anthony Liguori <aliguori@us.ibm.com>
 * Copyright (C) 2006-2008 Red Hat, Inc., Markus Armbruster <armbru@redhat.com>
 *
 *  Based on linux/drivers/video/q40fb.c
 *
 *  This file is subject to the terms and conditions of the GNU General Public
 *  License. See the file COPYING in the मुख्य directory of this archive क्रम
 *  more details.
 */

/*
 * TODO:
 *
 * Switch to grant tables when they become capable of dealing with the
 * frame buffer.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/console.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fb.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/mm.h>

#समावेश <यंत्र/xen/hypervisor.h>

#समावेश <xen/xen.h>
#समावेश <xen/events.h>
#समावेश <xen/page.h>
#समावेश <xen/पूर्णांकerface/io/fbअगर.h>
#समावेश <xen/पूर्णांकerface/io/protocols.h>
#समावेश <xen/xenbus.h>
#समावेश <xen/platक्रमm_pci.h>

काष्ठा xenfb_info अणु
	अचिन्हित अक्षर		*fb;
	काष्ठा fb_info		*fb_info;
	पूर्णांक			x1, y1, x2, y2;	/* dirty rectangle,
						   रक्षित by dirty_lock */
	spinlock_t		dirty_lock;
	पूर्णांक			nr_pages;
	पूर्णांक			irq;
	काष्ठा xenfb_page	*page;
	अचिन्हित दीर्घ 		*gfns;
	पूर्णांक			update_wanted; /* XENFB_TYPE_UPDATE wanted */
	पूर्णांक			feature_resize; /* XENFB_TYPE_RESIZE ok */
	काष्ठा xenfb_resize	resize;		/* रक्षित by resize_lock */
	पूर्णांक			resize_dpy;	/* ditto */
	spinlock_t		resize_lock;

	काष्ठा xenbus_device	*xbdev;
पूर्ण;

#घोषणा XENFB_DEFAULT_FB_LEN (XENFB_WIDTH * XENFB_HEIGHT * XENFB_DEPTH / 8)

क्रमागत अणु KPARAM_MEM, KPARAM_WIDTH, KPARAM_HEIGHT, KPARAM_CNT पूर्ण;
अटल पूर्णांक video[KPARAM_CNT] = अणु 2, XENFB_WIDTH, XENFB_HEIGHT पूर्ण;
module_param_array(video, पूर्णांक, शून्य, 0);
MODULE_PARM_DESC(video,
	"Video memory size in MB, width, height in pixels (default 2,800,600)");

अटल व्योम xenfb_make_preferred_console(व्योम);
अटल पूर्णांक xenfb_हटाओ(काष्ठा xenbus_device *);
अटल व्योम xenfb_init_shared_page(काष्ठा xenfb_info *, काष्ठा fb_info *);
अटल पूर्णांक xenfb_connect_backend(काष्ठा xenbus_device *, काष्ठा xenfb_info *);
अटल व्योम xenfb_disconnect_backend(काष्ठा xenfb_info *);

अटल व्योम xenfb_send_event(काष्ठा xenfb_info *info,
			     जोड़ xenfb_out_event *event)
अणु
	u32 prod;

	prod = info->page->out_prod;
	/* caller ensures !xenfb_queue_full() */
	mb();			/* ensure ring space available */
	XENFB_OUT_RING_REF(info->page, prod) = *event;
	wmb();			/* ensure ring contents visible */
	info->page->out_prod = prod + 1;

	notअगरy_remote_via_irq(info->irq);
पूर्ण

अटल व्योम xenfb_करो_update(काष्ठा xenfb_info *info,
			    पूर्णांक x, पूर्णांक y, पूर्णांक w, पूर्णांक h)
अणु
	जोड़ xenfb_out_event event;

	स_रखो(&event, 0, माप(event));
	event.type = XENFB_TYPE_UPDATE;
	event.update.x = x;
	event.update.y = y;
	event.update.width = w;
	event.update.height = h;

	/* caller ensures !xenfb_queue_full() */
	xenfb_send_event(info, &event);
पूर्ण

अटल व्योम xenfb_करो_resize(काष्ठा xenfb_info *info)
अणु
	जोड़ xenfb_out_event event;

	स_रखो(&event, 0, माप(event));
	event.resize = info->resize;

	/* caller ensures !xenfb_queue_full() */
	xenfb_send_event(info, &event);
पूर्ण

अटल पूर्णांक xenfb_queue_full(काष्ठा xenfb_info *info)
अणु
	u32 cons, prod;

	prod = info->page->out_prod;
	cons = info->page->out_cons;
	वापस prod - cons == XENFB_OUT_RING_LEN;
पूर्ण

अटल व्योम xenfb_handle_resize_dpy(काष्ठा xenfb_info *info)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&info->resize_lock, flags);
	अगर (info->resize_dpy) अणु
		अगर (!xenfb_queue_full(info)) अणु
			info->resize_dpy = 0;
			xenfb_करो_resize(info);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&info->resize_lock, flags);
पूर्ण

अटल व्योम xenfb_refresh(काष्ठा xenfb_info *info,
			  पूर्णांक x1, पूर्णांक y1, पूर्णांक w, पूर्णांक h)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक x2 = x1 + w - 1;
	पूर्णांक y2 = y1 + h - 1;

	xenfb_handle_resize_dpy(info);

	अगर (!info->update_wanted)
		वापस;

	spin_lock_irqsave(&info->dirty_lock, flags);

	/* Combine with dirty rectangle: */
	अगर (info->y1 < y1)
		y1 = info->y1;
	अगर (info->y2 > y2)
		y2 = info->y2;
	अगर (info->x1 < x1)
		x1 = info->x1;
	अगर (info->x2 > x2)
		x2 = info->x2;

	अगर (xenfb_queue_full(info)) अणु
		/* Can't send right now, stash it in the dirty rectangle */
		info->x1 = x1;
		info->x2 = x2;
		info->y1 = y1;
		info->y2 = y2;
		spin_unlock_irqrestore(&info->dirty_lock, flags);
		वापस;
	पूर्ण

	/* Clear dirty rectangle: */
	info->x1 = info->y1 = पूर्णांक_उच्च;
	info->x2 = info->y2 = 0;

	spin_unlock_irqrestore(&info->dirty_lock, flags);

	अगर (x1 <= x2 && y1 <= y2)
		xenfb_करो_update(info, x1, y1, x2 - x1 + 1, y2 - y1 + 1);
पूर्ण

अटल व्योम xenfb_deferred_io(काष्ठा fb_info *fb_info,
			      काष्ठा list_head *pagelist)
अणु
	काष्ठा xenfb_info *info = fb_info->par;
	काष्ठा page *page;
	अचिन्हित दीर्घ beg, end;
	पूर्णांक y1, y2, miny, maxy;

	miny = पूर्णांक_उच्च;
	maxy = 0;
	list_क्रम_each_entry(page, pagelist, lru) अणु
		beg = page->index << PAGE_SHIFT;
		end = beg + PAGE_SIZE - 1;
		y1 = beg / fb_info->fix.line_length;
		y2 = end / fb_info->fix.line_length;
		अगर (y2 >= fb_info->var.yres)
			y2 = fb_info->var.yres - 1;
		अगर (miny > y1)
			miny = y1;
		अगर (maxy < y2)
			maxy = y2;
	पूर्ण
	xenfb_refresh(info, 0, miny, fb_info->var.xres, maxy - miny + 1);
पूर्ण

अटल काष्ठा fb_deferred_io xenfb_defio = अणु
	.delay		= HZ / 20,
	.deferred_io	= xenfb_deferred_io,
पूर्ण;

अटल पूर्णांक xenfb_setcolreg(अचिन्हित regno, अचिन्हित red, अचिन्हित green,
			   अचिन्हित blue, अचिन्हित transp,
			   काष्ठा fb_info *info)
अणु
	u32 v;

	अगर (regno > info->cmap.len)
		वापस 1;

#घोषणा CNVT_TOHW(val, width) ((((val)<<(width))+0x7FFF-(val))>>16)
	red = CNVT_TOHW(red, info->var.red.length);
	green = CNVT_TOHW(green, info->var.green.length);
	blue = CNVT_TOHW(blue, info->var.blue.length);
	transp = CNVT_TOHW(transp, info->var.transp.length);
#अघोषित CNVT_TOHW

	v = (red << info->var.red.offset) |
	    (green << info->var.green.offset) |
	    (blue << info->var.blue.offset);

	चयन (info->var.bits_per_pixel) अणु
	हाल 16:
	हाल 24:
	हाल 32:
		((u32 *)info->pseuकरो_palette)[regno] = v;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम xenfb_fillrect(काष्ठा fb_info *p, स्थिर काष्ठा fb_fillrect *rect)
अणु
	काष्ठा xenfb_info *info = p->par;

	sys_fillrect(p, rect);
	xenfb_refresh(info, rect->dx, rect->dy, rect->width, rect->height);
पूर्ण

अटल व्योम xenfb_imageblit(काष्ठा fb_info *p, स्थिर काष्ठा fb_image *image)
अणु
	काष्ठा xenfb_info *info = p->par;

	sys_imageblit(p, image);
	xenfb_refresh(info, image->dx, image->dy, image->width, image->height);
पूर्ण

अटल व्योम xenfb_copyarea(काष्ठा fb_info *p, स्थिर काष्ठा fb_copyarea *area)
अणु
	काष्ठा xenfb_info *info = p->par;

	sys_copyarea(p, area);
	xenfb_refresh(info, area->dx, area->dy, area->width, area->height);
पूर्ण

अटल sमाप_प्रकार xenfb_ग_लिखो(काष्ठा fb_info *p, स्थिर अक्षर __user *buf,
			माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा xenfb_info *info = p->par;
	sमाप_प्रकार res;

	res = fb_sys_ग_लिखो(p, buf, count, ppos);
	xenfb_refresh(info, 0, 0, info->page->width, info->page->height);
	वापस res;
पूर्ण

अटल पूर्णांक
xenfb_check_var(काष्ठा fb_var_screeninfo *var, काष्ठा fb_info *info)
अणु
	काष्ठा xenfb_info *xenfb_info;
	पूर्णांक required_mem_len;

	xenfb_info = info->par;

	अगर (!xenfb_info->feature_resize) अणु
		अगर (var->xres == video[KPARAM_WIDTH] &&
		    var->yres == video[KPARAM_HEIGHT] &&
		    var->bits_per_pixel == xenfb_info->page->depth) अणु
			वापस 0;
		पूर्ण
		वापस -EINVAL;
	पूर्ण

	/* Can't resize past initial width and height */
	अगर (var->xres > video[KPARAM_WIDTH] || var->yres > video[KPARAM_HEIGHT])
		वापस -EINVAL;

	required_mem_len = var->xres * var->yres * xenfb_info->page->depth / 8;
	अगर (var->bits_per_pixel == xenfb_info->page->depth &&
	    var->xres <= info->fix.line_length / (XENFB_DEPTH / 8) &&
	    required_mem_len <= info->fix.smem_len) अणु
		var->xres_भव = var->xres;
		var->yres_भव = var->yres;
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक xenfb_set_par(काष्ठा fb_info *info)
अणु
	काष्ठा xenfb_info *xenfb_info;
	अचिन्हित दीर्घ flags;

	xenfb_info = info->par;

	spin_lock_irqsave(&xenfb_info->resize_lock, flags);
	xenfb_info->resize.type = XENFB_TYPE_RESIZE;
	xenfb_info->resize.width = info->var.xres;
	xenfb_info->resize.height = info->var.yres;
	xenfb_info->resize.stride = info->fix.line_length;
	xenfb_info->resize.depth = info->var.bits_per_pixel;
	xenfb_info->resize.offset = 0;
	xenfb_info->resize_dpy = 1;
	spin_unlock_irqrestore(&xenfb_info->resize_lock, flags);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा fb_ops xenfb_fb_ops = अणु
	.owner		= THIS_MODULE,
	.fb_पढ़ो	= fb_sys_पढ़ो,
	.fb_ग_लिखो	= xenfb_ग_लिखो,
	.fb_setcolreg	= xenfb_setcolreg,
	.fb_fillrect	= xenfb_fillrect,
	.fb_copyarea	= xenfb_copyarea,
	.fb_imageblit	= xenfb_imageblit,
	.fb_check_var	= xenfb_check_var,
	.fb_set_par     = xenfb_set_par,
पूर्ण;

अटल irqवापस_t xenfb_event_handler(पूर्णांक rq, व्योम *dev_id)
अणु
	/*
	 * No in events recognized, simply ignore them all.
	 * If you need to recognize some, see xen-kbdfront's
	 * input_handler() क्रम how to करो that.
	 */
	काष्ठा xenfb_info *info = dev_id;
	काष्ठा xenfb_page *page = info->page;

	अगर (page->in_cons != page->in_prod) अणु
		info->page->in_cons = info->page->in_prod;
		notअगरy_remote_via_irq(info->irq);
	पूर्ण

	/* Flush dirty rectangle: */
	xenfb_refresh(info, पूर्णांक_उच्च, पूर्णांक_उच्च, -पूर्णांक_उच्च, -पूर्णांक_उच्च);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक xenfb_probe(काष्ठा xenbus_device *dev,
		       स्थिर काष्ठा xenbus_device_id *id)
अणु
	काष्ठा xenfb_info *info;
	काष्ठा fb_info *fb_info;
	पूर्णांक fb_size;
	पूर्णांक val;
	पूर्णांक ret = 0;

	info = kzalloc(माप(*info), GFP_KERNEL);
	अगर (info == शून्य) अणु
		xenbus_dev_fatal(dev, -ENOMEM, "allocating info structure");
		वापस -ENOMEM;
	पूर्ण

	/* Limit kernel param videoram amount to what is in xenstore */
	अगर (xenbus_म_पूछो(XBT_NIL, dev->otherend, "videoram", "%d", &val) == 1) अणु
		अगर (val < video[KPARAM_MEM])
			video[KPARAM_MEM] = val;
	पूर्ण

	video[KPARAM_WIDTH] = xenbus_पढ़ो_अचिन्हित(dev->otherend, "width",
						   video[KPARAM_WIDTH]);
	video[KPARAM_HEIGHT] = xenbus_पढ़ो_अचिन्हित(dev->otherend, "height",
						    video[KPARAM_HEIGHT]);

	/* If requested res करोes not fit in available memory, use शेष */
	fb_size = video[KPARAM_MEM] * 1024 * 1024;
	अगर (video[KPARAM_WIDTH] * video[KPARAM_HEIGHT] * XENFB_DEPTH / 8
	    > fb_size) अणु
		pr_warn("display parameters %d,%d,%d invalid, use defaults\n",
			video[KPARAM_MEM], video[KPARAM_WIDTH],
			video[KPARAM_HEIGHT]);
		video[KPARAM_WIDTH] = XENFB_WIDTH;
		video[KPARAM_HEIGHT] = XENFB_HEIGHT;
		fb_size = XENFB_DEFAULT_FB_LEN;
	पूर्ण

	dev_set_drvdata(&dev->dev, info);
	info->xbdev = dev;
	info->irq = -1;
	info->x1 = info->y1 = पूर्णांक_उच्च;
	spin_lock_init(&info->dirty_lock);
	spin_lock_init(&info->resize_lock);

	info->fb = vzalloc(fb_size);
	अगर (info->fb == शून्य)
		जाओ error_nomem;

	info->nr_pages = (fb_size + PAGE_SIZE - 1) >> PAGE_SHIFT;

	info->gfns = vदो_स्मृति(array_size(माप(अचिन्हित दीर्घ), info->nr_pages));
	अगर (!info->gfns)
		जाओ error_nomem;

	/* set up shared page */
	info->page = (व्योम *)__get_मुक्त_page(GFP_KERNEL | __GFP_ZERO);
	अगर (!info->page)
		जाओ error_nomem;

	/* abusing framebuffer_alloc() to allocate pseuकरो_palette */
	fb_info = framebuffer_alloc(माप(u32) * 256, शून्य);
	अगर (fb_info == शून्य)
		जाओ error_nomem;

	/* complete the abuse: */
	fb_info->pseuकरो_palette = fb_info->par;
	fb_info->par = info;

	fb_info->screen_base = info->fb;

	fb_info->fbops = &xenfb_fb_ops;
	fb_info->var.xres_भव = fb_info->var.xres = video[KPARAM_WIDTH];
	fb_info->var.yres_भव = fb_info->var.yres = video[KPARAM_HEIGHT];
	fb_info->var.bits_per_pixel = XENFB_DEPTH;

	fb_info->var.red = (काष्ठा fb_bitfield)अणु16, 8, 0पूर्ण;
	fb_info->var.green = (काष्ठा fb_bitfield)अणु8, 8, 0पूर्ण;
	fb_info->var.blue = (काष्ठा fb_bitfield)अणु0, 8, 0पूर्ण;

	fb_info->var.activate = FB_ACTIVATE_NOW;
	fb_info->var.height = -1;
	fb_info->var.width = -1;
	fb_info->var.vmode = FB_VMODE_NONINTERLACED;

	fb_info->fix.visual = FB_VISUAL_TRUECOLOR;
	fb_info->fix.line_length = fb_info->var.xres * XENFB_DEPTH / 8;
	fb_info->fix.smem_start = 0;
	fb_info->fix.smem_len = fb_size;
	म_नकल(fb_info->fix.id, "xen");
	fb_info->fix.type = FB_TYPE_PACKED_PIXELS;
	fb_info->fix.accel = FB_ACCEL_NONE;

	fb_info->flags = FBINFO_FLAG_DEFAULT | FBINFO_VIRTFB;

	ret = fb_alloc_cmap(&fb_info->cmap, 256, 0);
	अगर (ret < 0) अणु
		framebuffer_release(fb_info);
		xenbus_dev_fatal(dev, ret, "fb_alloc_cmap");
		जाओ error;
	पूर्ण

	fb_info->fbdefio = &xenfb_defio;
	fb_deferred_io_init(fb_info);

	xenfb_init_shared_page(info, fb_info);

	ret = xenfb_connect_backend(dev, info);
	अगर (ret < 0) अणु
		xenbus_dev_fatal(dev, ret, "xenfb_connect_backend");
		जाओ error_fb;
	पूर्ण

	ret = रेजिस्टर_framebuffer(fb_info);
	अगर (ret) अणु
		xenbus_dev_fatal(dev, ret, "register_framebuffer");
		जाओ error_fb;
	पूर्ण
	info->fb_info = fb_info;

	xenfb_make_preferred_console();
	वापस 0;

error_fb:
	fb_deferred_io_cleanup(fb_info);
	fb_dealloc_cmap(&fb_info->cmap);
	framebuffer_release(fb_info);
error_nomem:
	अगर (!ret) अणु
		ret = -ENOMEM;
		xenbus_dev_fatal(dev, ret, "allocating device memory");
	पूर्ण
error:
	xenfb_हटाओ(dev);
	वापस ret;
पूर्ण

अटल व्योम xenfb_make_preferred_console(व्योम)
अणु
	काष्ठा console *c;

	अगर (console_set_on_cmdline)
		वापस;

	console_lock();
	क्रम_each_console(c) अणु
		अगर (!म_भेद(c->name, "tty") && c->index == 0)
			अवरोध;
	पूर्ण
	console_unlock();
	अगर (c) अणु
		unरेजिस्टर_console(c);
		c->flags |= CON_CONSDEV;
		c->flags &= ~CON_PRINTBUFFER; /* करोn't prपूर्णांक again */
		रेजिस्टर_console(c);
	पूर्ण
पूर्ण

अटल पूर्णांक xenfb_resume(काष्ठा xenbus_device *dev)
अणु
	काष्ठा xenfb_info *info = dev_get_drvdata(&dev->dev);

	xenfb_disconnect_backend(info);
	xenfb_init_shared_page(info, info->fb_info);
	वापस xenfb_connect_backend(dev, info);
पूर्ण

अटल पूर्णांक xenfb_हटाओ(काष्ठा xenbus_device *dev)
अणु
	काष्ठा xenfb_info *info = dev_get_drvdata(&dev->dev);

	xenfb_disconnect_backend(info);
	अगर (info->fb_info) अणु
		fb_deferred_io_cleanup(info->fb_info);
		unरेजिस्टर_framebuffer(info->fb_info);
		fb_dealloc_cmap(&info->fb_info->cmap);
		framebuffer_release(info->fb_info);
	पूर्ण
	मुक्त_page((अचिन्हित दीर्घ)info->page);
	vमुक्त(info->gfns);
	vमुक्त(info->fb);
	kमुक्त(info);

	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ vदो_स्मृति_to_gfn(व्योम *address)
अणु
	वापस xen_page_to_gfn(vदो_स्मृति_to_page(address));
पूर्ण

अटल व्योम xenfb_init_shared_page(काष्ठा xenfb_info *info,
				   काष्ठा fb_info *fb_info)
अणु
	पूर्णांक i;
	पूर्णांक epd = PAGE_SIZE / माप(info->gfns[0]);

	क्रम (i = 0; i < info->nr_pages; i++)
		info->gfns[i] = vदो_स्मृति_to_gfn(info->fb + i * PAGE_SIZE);

	क्रम (i = 0; i * epd < info->nr_pages; i++)
		info->page->pd[i] = vदो_स्मृति_to_gfn(&info->gfns[i * epd]);

	info->page->width = fb_info->var.xres;
	info->page->height = fb_info->var.yres;
	info->page->depth = fb_info->var.bits_per_pixel;
	info->page->line_length = fb_info->fix.line_length;
	info->page->mem_length = fb_info->fix.smem_len;
	info->page->in_cons = info->page->in_prod = 0;
	info->page->out_cons = info->page->out_prod = 0;
पूर्ण

अटल पूर्णांक xenfb_connect_backend(काष्ठा xenbus_device *dev,
				 काष्ठा xenfb_info *info)
अणु
	पूर्णांक ret, evtchn, irq;
	काष्ठा xenbus_transaction xbt;

	ret = xenbus_alloc_evtchn(dev, &evtchn);
	अगर (ret)
		वापस ret;
	irq = bind_evtchn_to_irqhandler(evtchn, xenfb_event_handler,
					0, dev->devicetype, info);
	अगर (irq < 0) अणु
		xenbus_मुक्त_evtchn(dev, evtchn);
		xenbus_dev_fatal(dev, ret, "bind_evtchn_to_irqhandler");
		वापस irq;
	पूर्ण
 again:
	ret = xenbus_transaction_start(&xbt);
	अगर (ret) अणु
		xenbus_dev_fatal(dev, ret, "starting transaction");
		जाओ unbind_irq;
	पूर्ण
	ret = xenbus_म_लिखो(xbt, dev->nodename, "page-ref", "%lu",
			    virt_to_gfn(info->page));
	अगर (ret)
		जाओ error_xenbus;
	ret = xenbus_म_लिखो(xbt, dev->nodename, "event-channel", "%u",
			    evtchn);
	अगर (ret)
		जाओ error_xenbus;
	ret = xenbus_म_लिखो(xbt, dev->nodename, "protocol", "%s",
			    XEN_IO_PROTO_ABI_NATIVE);
	अगर (ret)
		जाओ error_xenbus;
	ret = xenbus_म_लिखो(xbt, dev->nodename, "feature-update", "1");
	अगर (ret)
		जाओ error_xenbus;
	ret = xenbus_transaction_end(xbt, 0);
	अगर (ret) अणु
		अगर (ret == -EAGAIN)
			जाओ again;
		xenbus_dev_fatal(dev, ret, "completing transaction");
		जाओ unbind_irq;
	पूर्ण

	xenbus_चयन_state(dev, XenbusStateInitialised);
	info->irq = irq;
	वापस 0;

 error_xenbus:
	xenbus_transaction_end(xbt, 1);
	xenbus_dev_fatal(dev, ret, "writing xenstore");
 unbind_irq:
	unbind_from_irqhandler(irq, info);
	वापस ret;
पूर्ण

अटल व्योम xenfb_disconnect_backend(काष्ठा xenfb_info *info)
अणु
	/* Prevent xenfb refresh */
	info->update_wanted = 0;
	अगर (info->irq >= 0)
		unbind_from_irqhandler(info->irq, info);
	info->irq = -1;
पूर्ण

अटल व्योम xenfb_backend_changed(काष्ठा xenbus_device *dev,
				  क्रमागत xenbus_state backend_state)
अणु
	काष्ठा xenfb_info *info = dev_get_drvdata(&dev->dev);

	चयन (backend_state) अणु
	हाल XenbusStateInitialising:
	हाल XenbusStateInitialised:
	हाल XenbusStateReconfiguring:
	हाल XenbusStateReconfigured:
	हाल XenbusStateUnknown:
		अवरोध;

	हाल XenbusStateInitWait:
		xenbus_चयन_state(dev, XenbusStateConnected);
		अवरोध;

	हाल XenbusStateConnected:
		/*
		 * Work around xenbus race condition: If backend goes
		 * through InitWait to Connected fast enough, we can
		 * get Connected twice here.
		 */
		अगर (dev->state != XenbusStateConnected)
			/* no InitWait seen yet, fudge it */
			xenbus_चयन_state(dev, XenbusStateConnected);

		अगर (xenbus_पढ़ो_अचिन्हित(info->xbdev->otherend,
					 "request-update", 0))
			info->update_wanted = 1;

		info->feature_resize = xenbus_पढ़ो_अचिन्हित(dev->otherend,
							"feature-resize", 0);
		अवरोध;

	हाल XenbusStateClosed:
		अगर (dev->state == XenbusStateClosed)
			अवरोध;
		fallthrough;	/* Missed the backend's CLOSING state */
	हाल XenbusStateClosing:
		xenbus_frontend_बंदd(dev);
		अवरोध;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा xenbus_device_id xenfb_ids[] = अणु
	अणु "vfb" पूर्ण,
	अणु "" पूर्ण
पूर्ण;

अटल काष्ठा xenbus_driver xenfb_driver = अणु
	.ids = xenfb_ids,
	.probe = xenfb_probe,
	.हटाओ = xenfb_हटाओ,
	.resume = xenfb_resume,
	.otherend_changed = xenfb_backend_changed,
पूर्ण;

अटल पूर्णांक __init xenfb_init(व्योम)
अणु
	अगर (!xen_करोमुख्य())
		वापस -ENODEV;

	/* Nothing to करो अगर running in करोm0. */
	अगर (xen_initial_करोमुख्य())
		वापस -ENODEV;

	अगर (!xen_has_pv_devices())
		वापस -ENODEV;

	वापस xenbus_रेजिस्टर_frontend(&xenfb_driver);
पूर्ण

अटल व्योम __निकास xenfb_cleanup(व्योम)
अणु
	xenbus_unरेजिस्टर_driver(&xenfb_driver);
पूर्ण

module_init(xenfb_init);
module_निकास(xenfb_cleanup);

MODULE_DESCRIPTION("Xen virtual framebuffer device frontend");
MODULE_LICENSE("GPL");
MODULE_ALIAS("xen:vfb");
