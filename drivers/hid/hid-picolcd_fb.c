<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/***************************************************************************
 *   Copyright (C) 2010-2012 by Bruno Prथऊmont <bonbons@linux-vserver.org>  *
 *                                                                         *
 *   Based on Logitech G13 driver (v0.4)                                   *
 *     Copyright (C) 2009 by Rick L. Vinyard, Jr. <rvinyard@cs.nmsu.edu>   *
 *                                                                         *
 ***************************************************************************/

#समावेश <linux/hid.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश <linux/fb.h>
#समावेश <linux/module.h>

#समावेश "hid-picolcd.h"

/* Framebuffer
 *
 * The PicoLCD use a Topway LCD module of 256x64 pixel
 * This display area is tiled over 4 controllers with 8 tiles
 * each. Each tile has 8x64 pixel, each data byte representing
 * a 1-bit wide vertical line of the tile.
 *
 * The display can be updated at a tile granularity.
 *
 *       Chip 1           Chip 2           Chip 3           Chip 4
 * +----------------+----------------+----------------+----------------+
 * |     Tile 1     |     Tile 1     |     Tile 1     |     Tile 1     |
 * +----------------+----------------+----------------+----------------+
 * |     Tile 2     |     Tile 2     |     Tile 2     |     Tile 2     |
 * +----------------+----------------+----------------+----------------+
 *                                  ...
 * +----------------+----------------+----------------+----------------+
 * |     Tile 8     |     Tile 8     |     Tile 8     |     Tile 8     |
 * +----------------+----------------+----------------+----------------+
 */
#घोषणा PICOLCDFB_NAME "picolcdfb"
#घोषणा PICOLCDFB_WIDTH (256)
#घोषणा PICOLCDFB_HEIGHT (64)
#घोषणा PICOLCDFB_SIZE (PICOLCDFB_WIDTH * PICOLCDFB_HEIGHT / 8)

#घोषणा PICOLCDFB_UPDATE_RATE_LIMIT   10
#घोषणा PICOLCDFB_UPDATE_RATE_DEFAULT  2

/* Framebuffer visual काष्ठाures */
अटल स्थिर काष्ठा fb_fix_screeninfo picolcdfb_fix = अणु
	.id          = PICOLCDFB_NAME,
	.type        = FB_TYPE_PACKED_PIXELS,
	.visual      = FB_VISUAL_MONO01,
	.xpanstep    = 0,
	.ypanstep    = 0,
	.ywrapstep   = 0,
	.line_length = PICOLCDFB_WIDTH / 8,
	.accel       = FB_ACCEL_NONE,
पूर्ण;

अटल स्थिर काष्ठा fb_var_screeninfo picolcdfb_var = अणु
	.xres           = PICOLCDFB_WIDTH,
	.yres           = PICOLCDFB_HEIGHT,
	.xres_भव   = PICOLCDFB_WIDTH,
	.yres_भव   = PICOLCDFB_HEIGHT,
	.width          = 103,
	.height         = 26,
	.bits_per_pixel = 1,
	.grayscale      = 1,
	.red            = अणु
		.offset = 0,
		.length = 1,
		.msb_right = 0,
	पूर्ण,
	.green          = अणु
		.offset = 0,
		.length = 1,
		.msb_right = 0,
	पूर्ण,
	.blue           = अणु
		.offset = 0,
		.length = 1,
		.msb_right = 0,
	पूर्ण,
	.transp         = अणु
		.offset = 0,
		.length = 0,
		.msb_right = 0,
	पूर्ण,
पूर्ण;

/* Send a given tile to PicoLCD */
अटल पूर्णांक picolcd_fb_send_tile(काष्ठा picolcd_data *data, u8 *vbiपंचांगap,
		पूर्णांक chip, पूर्णांक tile)
अणु
	काष्ठा hid_report *report1, *report2;
	अचिन्हित दीर्घ flags;
	u8 *tdata;
	पूर्णांक i;

	report1 = picolcd_out_report(REPORT_LCD_CMD_DATA, data->hdev);
	अगर (!report1 || report1->maxfield != 1)
		वापस -ENODEV;
	report2 = picolcd_out_report(REPORT_LCD_DATA, data->hdev);
	अगर (!report2 || report2->maxfield != 1)
		वापस -ENODEV;

	spin_lock_irqsave(&data->lock, flags);
	अगर ((data->status & PICOLCD_FAILED)) अणु
		spin_unlock_irqrestore(&data->lock, flags);
		वापस -ENODEV;
	पूर्ण
	hid_set_field(report1->field[0],  0, chip << 2);
	hid_set_field(report1->field[0],  1, 0x02);
	hid_set_field(report1->field[0],  2, 0x00);
	hid_set_field(report1->field[0],  3, 0x00);
	hid_set_field(report1->field[0],  4, 0xb8 | tile);
	hid_set_field(report1->field[0],  5, 0x00);
	hid_set_field(report1->field[0],  6, 0x00);
	hid_set_field(report1->field[0],  7, 0x40);
	hid_set_field(report1->field[0],  8, 0x00);
	hid_set_field(report1->field[0],  9, 0x00);
	hid_set_field(report1->field[0], 10,   32);

	hid_set_field(report2->field[0],  0, (chip << 2) | 0x01);
	hid_set_field(report2->field[0],  1, 0x00);
	hid_set_field(report2->field[0],  2, 0x00);
	hid_set_field(report2->field[0],  3,   32);

	tdata = vbiपंचांगap + (tile * 4 + chip) * 64;
	क्रम (i = 0; i < 64; i++)
		अगर (i < 32)
			hid_set_field(report1->field[0], 11 + i, tdata[i]);
		अन्यथा
			hid_set_field(report2->field[0], 4 + i - 32, tdata[i]);

	hid_hw_request(data->hdev, report1, HID_REQ_SET_REPORT);
	hid_hw_request(data->hdev, report2, HID_REQ_SET_REPORT);
	spin_unlock_irqrestore(&data->lock, flags);
	वापस 0;
पूर्ण

/* Translate a single tile*/
अटल पूर्णांक picolcd_fb_update_tile(u8 *vbiपंचांगap, स्थिर u8 *biपंचांगap, पूर्णांक bpp,
		पूर्णांक chip, पूर्णांक tile)
अणु
	पूर्णांक i, b, changed = 0;
	u8 tdata[64];
	u8 *vdata = vbiपंचांगap + (tile * 4 + chip) * 64;

	अगर (bpp == 1) अणु
		क्रम (b = 7; b >= 0; b--) अणु
			स्थिर u8 *bdata = biपंचांगap + tile * 256 + chip * 8 + b * 32;
			क्रम (i = 0; i < 64; i++) अणु
				tdata[i] <<= 1;
				tdata[i] |= (bdata[i/8] >> (i % 8)) & 0x01;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (bpp == 8) अणु
		क्रम (b = 7; b >= 0; b--) अणु
			स्थिर u8 *bdata = biपंचांगap + (tile * 256 + chip * 8 + b * 32) * 8;
			क्रम (i = 0; i < 64; i++) अणु
				tdata[i] <<= 1;
				tdata[i] |= (bdata[i] & 0x80) ? 0x01 : 0x00;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Oops, we should never get here! */
		WARN_ON(1);
		वापस 0;
	पूर्ण

	क्रम (i = 0; i < 64; i++)
		अगर (tdata[i] != vdata[i]) अणु
			changed = 1;
			vdata[i] = tdata[i];
		पूर्ण
	वापस changed;
पूर्ण

व्योम picolcd_fb_refresh(काष्ठा picolcd_data *data)
अणु
	अगर (data->fb_info)
		schedule_delayed_work(&data->fb_info->deferred_work, 0);
पूर्ण

/* Reconfigure LCD display */
पूर्णांक picolcd_fb_reset(काष्ठा picolcd_data *data, पूर्णांक clear)
अणु
	काष्ठा hid_report *report = picolcd_out_report(REPORT_LCD_CMD, data->hdev);
	काष्ठा picolcd_fb_data *fbdata = data->fb_info->par;
	पूर्णांक i, j;
	अचिन्हित दीर्घ flags;
	अटल स्थिर u8 mapcmd[8] = अणु 0x00, 0x02, 0x00, 0x64, 0x3f, 0x00, 0x64, 0xc0 पूर्ण;

	अगर (!report || report->maxfield != 1)
		वापस -ENODEV;

	spin_lock_irqsave(&data->lock, flags);
	क्रम (i = 0; i < 4; i++) अणु
		क्रम (j = 0; j < report->field[0]->maxusage; j++)
			अगर (j == 0)
				hid_set_field(report->field[0], j, i << 2);
			अन्यथा अगर (j < माप(mapcmd))
				hid_set_field(report->field[0], j, mapcmd[j]);
			अन्यथा
				hid_set_field(report->field[0], j, 0);
		hid_hw_request(data->hdev, report, HID_REQ_SET_REPORT);
	पूर्ण
	spin_unlock_irqrestore(&data->lock, flags);

	अगर (clear) अणु
		स_रखो(fbdata->vbiपंचांगap, 0, PICOLCDFB_SIZE);
		स_रखो(fbdata->biपंचांगap, 0, PICOLCDFB_SIZE*fbdata->bpp);
	पूर्ण
	fbdata->क्रमce = 1;

	/* schedule first output of framebuffer */
	अगर (fbdata->पढ़ोy)
		schedule_delayed_work(&data->fb_info->deferred_work, 0);
	अन्यथा
		fbdata->पढ़ोy = 1;

	वापस 0;
पूर्ण

/* Update fb_vbiपंचांगap from the screen_base and send changed tiles to device */
अटल व्योम picolcd_fb_update(काष्ठा fb_info *info)
अणु
	पूर्णांक chip, tile, n;
	अचिन्हित दीर्घ flags;
	काष्ठा picolcd_fb_data *fbdata = info->par;
	काष्ठा picolcd_data *data;

	mutex_lock(&info->lock);

	spin_lock_irqsave(&fbdata->lock, flags);
	अगर (!fbdata->पढ़ोy && fbdata->picolcd)
		picolcd_fb_reset(fbdata->picolcd, 0);
	spin_unlock_irqrestore(&fbdata->lock, flags);

	/*
	 * Translate the framebuffer पूर्णांकo the क्रमmat needed by the PicoLCD.
	 * See display layout above.
	 * Do this one tile after the other and push those tiles that changed.
	 *
	 * Wait क्रम our IO to complete as otherwise we might flood the queue!
	 */
	n = 0;
	क्रम (chip = 0; chip < 4; chip++)
		क्रम (tile = 0; tile < 8; tile++) अणु
			अगर (!fbdata->क्रमce && !picolcd_fb_update_tile(
					fbdata->vbiपंचांगap, fbdata->biपंचांगap,
					fbdata->bpp, chip, tile))
				जारी;
			n += 2;
			अगर (n >= HID_OUTPUT_FIFO_SIZE / 2) अणु
				spin_lock_irqsave(&fbdata->lock, flags);
				data = fbdata->picolcd;
				spin_unlock_irqrestore(&fbdata->lock, flags);
				mutex_unlock(&info->lock);
				अगर (!data)
					वापस;
				hid_hw_रुको(data->hdev);
				mutex_lock(&info->lock);
				n = 0;
			पूर्ण
			spin_lock_irqsave(&fbdata->lock, flags);
			data = fbdata->picolcd;
			spin_unlock_irqrestore(&fbdata->lock, flags);
			अगर (!data || picolcd_fb_send_tile(data,
					fbdata->vbiपंचांगap, chip, tile))
				जाओ out;
		पूर्ण
	fbdata->क्रमce = false;
	अगर (n) अणु
		spin_lock_irqsave(&fbdata->lock, flags);
		data = fbdata->picolcd;
		spin_unlock_irqrestore(&fbdata->lock, flags);
		mutex_unlock(&info->lock);
		अगर (data)
			hid_hw_रुको(data->hdev);
		वापस;
	पूर्ण
out:
	mutex_unlock(&info->lock);
पूर्ण

/* Stub to call the प्रणाली शेष and update the image on the picoLCD */
अटल व्योम picolcd_fb_fillrect(काष्ठा fb_info *info,
		स्थिर काष्ठा fb_fillrect *rect)
अणु
	अगर (!info->par)
		वापस;
	sys_fillrect(info, rect);

	schedule_delayed_work(&info->deferred_work, 0);
पूर्ण

/* Stub to call the प्रणाली शेष and update the image on the picoLCD */
अटल व्योम picolcd_fb_copyarea(काष्ठा fb_info *info,
		स्थिर काष्ठा fb_copyarea *area)
अणु
	अगर (!info->par)
		वापस;
	sys_copyarea(info, area);

	schedule_delayed_work(&info->deferred_work, 0);
पूर्ण

/* Stub to call the प्रणाली शेष and update the image on the picoLCD */
अटल व्योम picolcd_fb_imageblit(काष्ठा fb_info *info, स्थिर काष्ठा fb_image *image)
अणु
	अगर (!info->par)
		वापस;
	sys_imageblit(info, image);

	schedule_delayed_work(&info->deferred_work, 0);
पूर्ण

/*
 * this is the slow path from userspace. they can seek and ग_लिखो to
 * the fb. it's inefficient to करो anything less than a full screen draw
 */
अटल sमाप_प्रकार picolcd_fb_ग_लिखो(काष्ठा fb_info *info, स्थिर अक्षर __user *buf,
		माप_प्रकार count, loff_t *ppos)
अणु
	sमाप_प्रकार ret;
	अगर (!info->par)
		वापस -ENODEV;
	ret = fb_sys_ग_लिखो(info, buf, count, ppos);
	अगर (ret >= 0)
		schedule_delayed_work(&info->deferred_work, 0);
	वापस ret;
पूर्ण

अटल पूर्णांक picolcd_fb_blank(पूर्णांक blank, काष्ठा fb_info *info)
अणु
	/* We let fb notअगरication करो this क्रम us via lcd/backlight device */
	वापस 0;
पूर्ण

अटल व्योम picolcd_fb_destroy(काष्ठा fb_info *info)
अणु
	काष्ठा picolcd_fb_data *fbdata = info->par;

	/* make sure no work is deferred */
	fb_deferred_io_cleanup(info);

	/* No thridparty should ever unरेजिस्टर our framebuffer! */
	WARN_ON(fbdata->picolcd != शून्य);

	vमुक्त((u8 *)info->fix.smem_start);
	framebuffer_release(info);
पूर्ण

अटल पूर्णांक picolcd_fb_check_var(काष्ठा fb_var_screeninfo *var, काष्ठा fb_info *info)
अणु
	__u32 bpp      = var->bits_per_pixel;
	__u32 activate = var->activate;

	/* only allow 1/8 bit depth (8-bit is grayscale) */
	*var = picolcdfb_var;
	var->activate = activate;
	अगर (bpp >= 8) अणु
		var->bits_per_pixel = 8;
		var->red.length     = 8;
		var->green.length   = 8;
		var->blue.length    = 8;
	पूर्ण अन्यथा अणु
		var->bits_per_pixel = 1;
		var->red.length     = 1;
		var->green.length   = 1;
		var->blue.length    = 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक picolcd_set_par(काष्ठा fb_info *info)
अणु
	काष्ठा picolcd_fb_data *fbdata = info->par;
	u8 *पंचांगp_fb, *o_fb;
	अगर (info->var.bits_per_pixel == fbdata->bpp)
		वापस 0;
	/* चयन between 1/8 bit depths */
	अगर (info->var.bits_per_pixel != 1 && info->var.bits_per_pixel != 8)
		वापस -EINVAL;

	o_fb   = fbdata->biपंचांगap;
	पंचांगp_fb = kदो_स्मृति_array(PICOLCDFB_SIZE, info->var.bits_per_pixel,
			       GFP_KERNEL);
	अगर (!पंचांगp_fb)
		वापस -ENOMEM;

	/* translate FB content to new bits-per-pixel */
	अगर (info->var.bits_per_pixel == 1) अणु
		पूर्णांक i, b;
		क्रम (i = 0; i < PICOLCDFB_SIZE; i++) अणु
			u8 p = 0;
			क्रम (b = 0; b < 8; b++) अणु
				p <<= 1;
				p |= o_fb[i*8+b] ? 0x01 : 0x00;
			पूर्ण
			पंचांगp_fb[i] = p;
		पूर्ण
		स_नकल(o_fb, पंचांगp_fb, PICOLCDFB_SIZE);
		info->fix.visual = FB_VISUAL_MONO01;
		info->fix.line_length = PICOLCDFB_WIDTH / 8;
	पूर्ण अन्यथा अणु
		पूर्णांक i;
		स_नकल(पंचांगp_fb, o_fb, PICOLCDFB_SIZE);
		क्रम (i = 0; i < PICOLCDFB_SIZE * 8; i++)
			o_fb[i] = पंचांगp_fb[i/8] & (0x01 << (7 - i % 8)) ? 0xff : 0x00;
		info->fix.visual = FB_VISUAL_सूचीECTCOLOR;
		info->fix.line_length = PICOLCDFB_WIDTH;
	पूर्ण

	kमुक्त(पंचांगp_fb);
	fbdata->bpp = info->var.bits_per_pixel;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा fb_ops picolcdfb_ops = अणु
	.owner        = THIS_MODULE,
	.fb_destroy   = picolcd_fb_destroy,
	.fb_पढ़ो      = fb_sys_पढ़ो,
	.fb_ग_लिखो     = picolcd_fb_ग_लिखो,
	.fb_blank     = picolcd_fb_blank,
	.fb_fillrect  = picolcd_fb_fillrect,
	.fb_copyarea  = picolcd_fb_copyarea,
	.fb_imageblit = picolcd_fb_imageblit,
	.fb_check_var = picolcd_fb_check_var,
	.fb_set_par   = picolcd_set_par,
पूर्ण;


/* Callback from deferred IO workqueue */
अटल व्योम picolcd_fb_deferred_io(काष्ठा fb_info *info, काष्ठा list_head *pagelist)
अणु
	picolcd_fb_update(info);
पूर्ण

अटल स्थिर काष्ठा fb_deferred_io picolcd_fb_defio = अणु
	.delay = HZ / PICOLCDFB_UPDATE_RATE_DEFAULT,
	.deferred_io = picolcd_fb_deferred_io,
पूर्ण;


/*
 * The "fb_update_rate" sysfs attribute
 */
अटल sमाप_प्रकार picolcd_fb_update_rate_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा picolcd_data *data = dev_get_drvdata(dev);
	काष्ठा picolcd_fb_data *fbdata = data->fb_info->par;
	अचिन्हित i, fb_update_rate = fbdata->update_rate;
	माप_प्रकार ret = 0;

	क्रम (i = 1; i <= PICOLCDFB_UPDATE_RATE_LIMIT; i++)
		अगर (ret >= PAGE_SIZE)
			अवरोध;
		अन्यथा अगर (i == fb_update_rate)
			ret += scnम_लिखो(buf+ret, PAGE_SIZE-ret, "[%u] ", i);
		अन्यथा
			ret += scnम_लिखो(buf+ret, PAGE_SIZE-ret, "%u ", i);
	अगर (ret > 0)
		buf[min(ret, (माप_प्रकार)PAGE_SIZE)-1] = '\n';
	वापस ret;
पूर्ण

अटल sमाप_प्रकार picolcd_fb_update_rate_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा picolcd_data *data = dev_get_drvdata(dev);
	काष्ठा picolcd_fb_data *fbdata = data->fb_info->par;
	पूर्णांक i;
	अचिन्हित u;

	अगर (count < 1 || count > 10)
		वापस -EINVAL;

	i = माला_पूछो(buf, "%u", &u);
	अगर (i != 1)
		वापस -EINVAL;

	अगर (u > PICOLCDFB_UPDATE_RATE_LIMIT)
		वापस -दुस्फल;
	अन्यथा अगर (u == 0)
		u = PICOLCDFB_UPDATE_RATE_DEFAULT;

	fbdata->update_rate = u;
	data->fb_info->fbdefio->delay = HZ / fbdata->update_rate;
	वापस count;
पूर्ण

अटल DEVICE_ATTR(fb_update_rate, 0664, picolcd_fb_update_rate_show,
		picolcd_fb_update_rate_store);

/* initialize Framebuffer device */
पूर्णांक picolcd_init_framebuffer(काष्ठा picolcd_data *data)
अणु
	काष्ठा device *dev = &data->hdev->dev;
	काष्ठा fb_info *info = शून्य;
	काष्ठा picolcd_fb_data *fbdata = शून्य;
	पूर्णांक i, error = -ENOMEM;
	u32 *palette;

	/* The extra memory is:
	 * - 256*u32 क्रम pseuकरो_palette
	 * - काष्ठा fb_deferred_io
	 */
	info = framebuffer_alloc(256 * माप(u32) +
			माप(काष्ठा fb_deferred_io) +
			माप(काष्ठा picolcd_fb_data) +
			PICOLCDFB_SIZE, dev);
	अगर (!info)
		जाओ err_nomem;

	info->fbdefio = info->par;
	*info->fbdefio = picolcd_fb_defio;
	info->par += माप(काष्ठा fb_deferred_io);
	palette = info->par;
	info->par += 256 * माप(u32);
	क्रम (i = 0; i < 256; i++)
		palette[i] = i > 0 && i < 16 ? 0xff : 0;
	info->pseuकरो_palette = palette;
	info->fbops = &picolcdfb_ops;
	info->var = picolcdfb_var;
	info->fix = picolcdfb_fix;
	info->fix.smem_len   = PICOLCDFB_SIZE*8;
	info->flags = FBINFO_FLAG_DEFAULT;

	fbdata = info->par;
	spin_lock_init(&fbdata->lock);
	fbdata->picolcd = data;
	fbdata->update_rate = PICOLCDFB_UPDATE_RATE_DEFAULT;
	fbdata->bpp     = picolcdfb_var.bits_per_pixel;
	fbdata->क्रमce   = 1;
	fbdata->vbiपंचांगap = info->par + माप(काष्ठा picolcd_fb_data);
	fbdata->biपंचांगap  = vदो_स्मृति(PICOLCDFB_SIZE*8);
	अगर (fbdata->biपंचांगap == शून्य) अणु
		dev_err(dev, "can't get a free page for framebuffer\n");
		जाओ err_nomem;
	पूर्ण
	info->screen_base = (अक्षर __क्रमce __iomem *)fbdata->biपंचांगap;
	info->fix.smem_start = (अचिन्हित दीर्घ)fbdata->biपंचांगap;
	स_रखो(fbdata->vbiपंचांगap, 0xff, PICOLCDFB_SIZE);
	data->fb_info = info;

	error = picolcd_fb_reset(data, 1);
	अगर (error) अणु
		dev_err(dev, "failed to configure display\n");
		जाओ err_cleanup;
	पूर्ण

	error = device_create_file(dev, &dev_attr_fb_update_rate);
	अगर (error) अणु
		dev_err(dev, "failed to create sysfs attributes\n");
		जाओ err_cleanup;
	पूर्ण

	fb_deferred_io_init(info);
	error = रेजिस्टर_framebuffer(info);
	अगर (error) अणु
		dev_err(dev, "failed to register framebuffer\n");
		जाओ err_sysfs;
	पूर्ण
	वापस 0;

err_sysfs:
	device_हटाओ_file(dev, &dev_attr_fb_update_rate);
	fb_deferred_io_cleanup(info);
err_cleanup:
	data->fb_info    = शून्य;

err_nomem:
	अगर (fbdata)
		vमुक्त(fbdata->biपंचांगap);
	framebuffer_release(info);
	वापस error;
पूर्ण

व्योम picolcd_निकास_framebuffer(काष्ठा picolcd_data *data)
अणु
	काष्ठा fb_info *info = data->fb_info;
	काष्ठा picolcd_fb_data *fbdata;
	अचिन्हित दीर्घ flags;

	अगर (!info)
		वापस;

	device_हटाओ_file(&data->hdev->dev, &dev_attr_fb_update_rate);
	fbdata = info->par;

	/* disconnect framebuffer from HID dev */
	spin_lock_irqsave(&fbdata->lock, flags);
	fbdata->picolcd = शून्य;
	spin_unlock_irqrestore(&fbdata->lock, flags);

	/* make sure there is no running update - thus that fbdata->picolcd
	 * once obtained under lock is guaranteed not to get मुक्त() under
	 * the feet of the deferred work */
	flush_delayed_work(&info->deferred_work);

	data->fb_info = शून्य;
	unरेजिस्टर_framebuffer(info);
पूर्ण
