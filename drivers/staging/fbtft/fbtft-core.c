<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2013 Noralf Tronnes
 *
 * This driver is inspired by:
 *   st7735fb.c, Copyright (C) 2011, Matt Porter
 *   broadsheetfb.c, Copyright (C) 2008, Jaya Kumar
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/fb.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/delay.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/backlight.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/property.h>
#समावेश <linux/spinlock.h>

#समावेश <video/mipi_display.h>

#समावेश "fbtft.h"
#समावेश "internal.h"

अटल अचिन्हित दीर्घ debug;
module_param(debug, uदीर्घ, 0000);
MODULE_PARM_DESC(debug, "override device debug level");

पूर्णांक fbtft_ग_लिखो_buf_dc(काष्ठा fbtft_par *par, व्योम *buf, माप_प्रकार len, पूर्णांक dc)
अणु
	पूर्णांक ret;

	अगर (par->gpio.dc)
		gpiod_set_value(par->gpio.dc, dc);

	ret = par->fbtftops.ग_लिखो(par, buf, len);
	अगर (ret < 0)
		dev_err(par->info->device,
			"write() failed and returned %d\n", ret);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(fbtft_ग_लिखो_buf_dc);

व्योम fbtft_dbg_hex(स्थिर काष्ठा device *dev, पूर्णांक groupsize,
		   व्योम *buf, माप_प्रकार len, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;
	अटल अक्षर textbuf[512];
	अक्षर *text = textbuf;
	माप_प्रकार text_len;

	बहु_शुरू(args, fmt);
	text_len = vscnम_लिखो(text, माप(textbuf), fmt, args);
	बहु_पूर्ण(args);

	hex_dump_to_buffer(buf, len, 32, groupsize, text + text_len,
			   512 - text_len, false);

	अगर (len > 32)
		dev_info(dev, "%s ...\n", text);
	अन्यथा
		dev_info(dev, "%s\n", text);
पूर्ण
EXPORT_SYMBOL(fbtft_dbg_hex);

अटल पूर्णांक fbtft_request_one_gpio(काष्ठा fbtft_par *par,
				  स्थिर अक्षर *name, पूर्णांक index,
				  काष्ठा gpio_desc **gpiop)
अणु
	काष्ठा device *dev = par->info->device;
	पूर्णांक ret = 0;

	*gpiop = devm_gpiod_get_index_optional(dev, name, index,
					       GPIOD_OUT_HIGH);
	अगर (IS_ERR(*gpiop)) अणु
		ret = PTR_ERR(*gpiop);
		dev_err(dev,
			"Failed to request %s GPIO: %d\n", name, ret);
		वापस ret;
	पूर्ण
	fbtft_par_dbg(DEBUG_REQUEST_GPIOS, par, "%s: '%s' GPIO\n",
		      __func__, name);

	वापस ret;
पूर्ण

अटल पूर्णांक fbtft_request_gpios(काष्ठा fbtft_par *par)
अणु
	पूर्णांक i;
	पूर्णांक ret;

	ret = fbtft_request_one_gpio(par, "reset", 0, &par->gpio.reset);
	अगर (ret)
		वापस ret;
	ret = fbtft_request_one_gpio(par, "dc", 0, &par->gpio.dc);
	अगर (ret)
		वापस ret;
	ret = fbtft_request_one_gpio(par, "rd", 0, &par->gpio.rd);
	अगर (ret)
		वापस ret;
	ret = fbtft_request_one_gpio(par, "wr", 0, &par->gpio.wr);
	अगर (ret)
		वापस ret;
	ret = fbtft_request_one_gpio(par, "cs", 0, &par->gpio.cs);
	अगर (ret)
		वापस ret;
	ret = fbtft_request_one_gpio(par, "latch", 0, &par->gpio.latch);
	अगर (ret)
		वापस ret;
	क्रम (i = 0; i < 16; i++) अणु
		ret = fbtft_request_one_gpio(par, "db", i,
					     &par->gpio.db[i]);
		अगर (ret)
			वापस ret;
		ret = fbtft_request_one_gpio(par, "led", i,
					     &par->gpio.led[i]);
		अगर (ret)
			वापस ret;
		ret = fbtft_request_one_gpio(par, "aux", i,
					     &par->gpio.aux[i]);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_FB_BACKLIGHT
अटल पूर्णांक fbtft_backlight_update_status(काष्ठा backlight_device *bd)
अणु
	काष्ठा fbtft_par *par = bl_get_data(bd);
	bool polarity = par->polarity;

	fbtft_par_dbg(DEBUG_BACKLIGHT, par,
		      "%s: polarity=%d, power=%d, fb_blank=%d\n",
		      __func__, polarity, bd->props.घातer, bd->props.fb_blank);

	अगर ((bd->props.घातer == FB_BLANK_UNBLANK) &&
	    (bd->props.fb_blank == FB_BLANK_UNBLANK))
		gpiod_set_value(par->gpio.led[0], polarity);
	अन्यथा
		gpiod_set_value(par->gpio.led[0], !polarity);

	वापस 0;
पूर्ण

अटल पूर्णांक fbtft_backlight_get_brightness(काष्ठा backlight_device *bd)
अणु
	वापस bd->props.brightness;
पूर्ण

व्योम fbtft_unरेजिस्टर_backlight(काष्ठा fbtft_par *par)
अणु
	अगर (par->info->bl_dev) अणु
		par->info->bl_dev->props.घातer = FB_BLANK_POWERDOWN;
		backlight_update_status(par->info->bl_dev);
		backlight_device_unरेजिस्टर(par->info->bl_dev);
		par->info->bl_dev = शून्य;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा backlight_ops fbtft_bl_ops = अणु
	.get_brightness	= fbtft_backlight_get_brightness,
	.update_status	= fbtft_backlight_update_status,
पूर्ण;

व्योम fbtft_रेजिस्टर_backlight(काष्ठा fbtft_par *par)
अणु
	काष्ठा backlight_device *bd;
	काष्ठा backlight_properties bl_props = अणु 0, पूर्ण;

	अगर (!par->gpio.led[0]) अणु
		fbtft_par_dbg(DEBUG_BACKLIGHT, par,
			      "%s(): led pin not set, exiting.\n", __func__);
		वापस;
	पूर्ण

	bl_props.type = BACKLIGHT_RAW;
	/* Assume backlight is off, get polarity from current state of pin */
	bl_props.घातer = FB_BLANK_POWERDOWN;
	अगर (!gpiod_get_value(par->gpio.led[0]))
		par->polarity = true;

	bd = backlight_device_रेजिस्टर(dev_driver_string(par->info->device),
				       par->info->device, par,
				       &fbtft_bl_ops, &bl_props);
	अगर (IS_ERR(bd)) अणु
		dev_err(par->info->device,
			"cannot register backlight device (%ld)\n",
			PTR_ERR(bd));
		वापस;
	पूर्ण
	par->info->bl_dev = bd;

	अगर (!par->fbtftops.unरेजिस्टर_backlight)
		par->fbtftops.unरेजिस्टर_backlight = fbtft_unरेजिस्टर_backlight;
पूर्ण
#अन्यथा
व्योम fbtft_रेजिस्टर_backlight(काष्ठा fbtft_par *par) अणु पूर्ण;
व्योम fbtft_unरेजिस्टर_backlight(काष्ठा fbtft_par *par) अणु पूर्ण;
#पूर्ण_अगर
EXPORT_SYMBOL(fbtft_रेजिस्टर_backlight);
EXPORT_SYMBOL(fbtft_unरेजिस्टर_backlight);

अटल व्योम fbtft_set_addr_win(काष्ठा fbtft_par *par, पूर्णांक xs, पूर्णांक ys, पूर्णांक xe,
			       पूर्णांक ye)
अणु
	ग_लिखो_reg(par, MIPI_DCS_SET_COLUMN_ADDRESS,
		  (xs >> 8) & 0xFF, xs & 0xFF, (xe >> 8) & 0xFF, xe & 0xFF);

	ग_लिखो_reg(par, MIPI_DCS_SET_PAGE_ADDRESS,
		  (ys >> 8) & 0xFF, ys & 0xFF, (ye >> 8) & 0xFF, ye & 0xFF);

	ग_लिखो_reg(par, MIPI_DCS_WRITE_MEMORY_START);
पूर्ण

अटल व्योम fbtft_reset(काष्ठा fbtft_par *par)
अणु
	अगर (!par->gpio.reset)
		वापस;
	fbtft_par_dbg(DEBUG_RESET, par, "%s()\n", __func__);
	gpiod_set_value_cansleep(par->gpio.reset, 1);
	usleep_range(20, 40);
	gpiod_set_value_cansleep(par->gpio.reset, 0);
	msleep(120);
पूर्ण

अटल व्योम fbtft_update_display(काष्ठा fbtft_par *par, अचिन्हित पूर्णांक start_line,
				 अचिन्हित पूर्णांक end_line)
अणु
	माप_प्रकार offset, len;
	kसमय_प्रकार ts_start, ts_end;
	दीर्घ fps, throughput;
	bool समयit = false;
	पूर्णांक ret = 0;

	अगर (unlikely(par->debug & (DEBUG_TIME_FIRST_UPDATE |
			DEBUG_TIME_EACH_UPDATE))) अणु
		अगर ((par->debug & DEBUG_TIME_EACH_UPDATE) ||
		    ((par->debug & DEBUG_TIME_FIRST_UPDATE) &&
		    !par->first_update_करोne)) अणु
			ts_start = kसमय_get();
			समयit = true;
		पूर्ण
	पूर्ण

	/* Sanity checks */
	अगर (start_line > end_line) अणु
		dev_warn(par->info->device,
			 "%s: start_line=%u is larger than end_line=%u. Shouldn't happen, will do full display update\n",
			 __func__, start_line, end_line);
		start_line = 0;
		end_line = par->info->var.yres - 1;
	पूर्ण
	अगर (start_line > par->info->var.yres - 1 ||
	    end_line > par->info->var.yres - 1) अणु
		dev_warn(par->info->device,
			 "%s: start_line=%u or end_line=%u is larger than max=%d. Shouldn't happen, will do full display update\n",
			 __func__, start_line,
			 end_line, par->info->var.yres - 1);
		start_line = 0;
		end_line = par->info->var.yres - 1;
	पूर्ण

	fbtft_par_dbg(DEBUG_UPDATE_DISPLAY, par, "%s(start_line=%u, end_line=%u)\n",
		      __func__, start_line, end_line);

	अगर (par->fbtftops.set_addr_win)
		par->fbtftops.set_addr_win(par, 0, start_line,
				par->info->var.xres - 1, end_line);

	offset = start_line * par->info->fix.line_length;
	len = (end_line - start_line + 1) * par->info->fix.line_length;
	ret = par->fbtftops.ग_लिखो_vmem(par, offset, len);
	अगर (ret < 0)
		dev_err(par->info->device,
			"%s: write_vmem failed to update display buffer\n",
			__func__);

	अगर (unlikely(समयit)) अणु
		ts_end = kसमय_get();
		अगर (!kसमय_प्रकारo_ns(par->update_समय))
			par->update_समय = ts_start;

		fps = kसमय_us_delta(ts_start, par->update_समय);
		par->update_समय = ts_start;
		fps = fps ? 1000000 / fps : 0;

		throughput = kसमय_us_delta(ts_end, ts_start);
		throughput = throughput ? (len * 1000) / throughput : 0;
		throughput = throughput * 1000 / 1024;

		dev_info(par->info->device,
			 "Display update: %ld kB/s, fps=%ld\n",
			 throughput, fps);
		par->first_update_करोne = true;
	पूर्ण
पूर्ण

अटल व्योम fbtft_सूची_गढ़ोty(काष्ठा fb_info *info, पूर्णांक y, पूर्णांक height)
अणु
	काष्ठा fbtft_par *par = info->par;
	काष्ठा fb_deferred_io *fbdefio = info->fbdefio;

	/* special हाल, needed ? */
	अगर (y == -1) अणु
		y = 0;
		height = info->var.yres;
	पूर्ण

	/* Mark display lines/area as dirty */
	spin_lock(&par->dirty_lock);
	अगर (y < par->dirty_lines_start)
		par->dirty_lines_start = y;
	अगर (y + height - 1 > par->dirty_lines_end)
		par->dirty_lines_end = y + height - 1;
	spin_unlock(&par->dirty_lock);

	/* Schedule deferred_io to update display (no-op अगर alपढ़ोy on queue)*/
	schedule_delayed_work(&info->deferred_work, fbdefio->delay);
पूर्ण

अटल व्योम fbtft_deferred_io(काष्ठा fb_info *info, काष्ठा list_head *pagelist)
अणु
	काष्ठा fbtft_par *par = info->par;
	अचिन्हित पूर्णांक dirty_lines_start, dirty_lines_end;
	काष्ठा page *page;
	अचिन्हित दीर्घ index;
	अचिन्हित पूर्णांक y_low = 0, y_high = 0;
	पूर्णांक count = 0;

	spin_lock(&par->dirty_lock);
	dirty_lines_start = par->dirty_lines_start;
	dirty_lines_end = par->dirty_lines_end;
	/* set display line markers as clean */
	par->dirty_lines_start = par->info->var.yres - 1;
	par->dirty_lines_end = 0;
	spin_unlock(&par->dirty_lock);

	/* Mark display lines as dirty */
	list_क्रम_each_entry(page, pagelist, lru) अणु
		count++;
		index = page->index << PAGE_SHIFT;
		y_low = index / info->fix.line_length;
		y_high = (index + PAGE_SIZE - 1) / info->fix.line_length;
		dev_dbg(info->device,
			"page->index=%lu y_low=%d y_high=%d\n",
			page->index, y_low, y_high);
		अगर (y_high > info->var.yres - 1)
			y_high = info->var.yres - 1;
		अगर (y_low < dirty_lines_start)
			dirty_lines_start = y_low;
		अगर (y_high > dirty_lines_end)
			dirty_lines_end = y_high;
	पूर्ण

	par->fbtftops.update_display(info->par,
					dirty_lines_start, dirty_lines_end);
पूर्ण

अटल व्योम fbtft_fb_fillrect(काष्ठा fb_info *info,
			      स्थिर काष्ठा fb_fillrect *rect)
अणु
	काष्ठा fbtft_par *par = info->par;

	dev_dbg(info->dev,
		"%s: dx=%d, dy=%d, width=%d, height=%d\n",
		__func__, rect->dx, rect->dy, rect->width, rect->height);
	sys_fillrect(info, rect);

	par->fbtftops.सूची_गढ़ोty(info, rect->dy, rect->height);
पूर्ण

अटल व्योम fbtft_fb_copyarea(काष्ठा fb_info *info,
			      स्थिर काष्ठा fb_copyarea *area)
अणु
	काष्ठा fbtft_par *par = info->par;

	dev_dbg(info->dev,
		"%s: dx=%d, dy=%d, width=%d, height=%d\n",
		__func__,  area->dx, area->dy, area->width, area->height);
	sys_copyarea(info, area);

	par->fbtftops.सूची_गढ़ोty(info, area->dy, area->height);
पूर्ण

अटल व्योम fbtft_fb_imageblit(काष्ठा fb_info *info,
			       स्थिर काष्ठा fb_image *image)
अणु
	काष्ठा fbtft_par *par = info->par;

	dev_dbg(info->dev,
		"%s: dx=%d, dy=%d, width=%d, height=%d\n",
		__func__,  image->dx, image->dy, image->width, image->height);
	sys_imageblit(info, image);

	par->fbtftops.सूची_गढ़ोty(info, image->dy, image->height);
पूर्ण

अटल sमाप_प्रकार fbtft_fb_ग_लिखो(काष्ठा fb_info *info, स्थिर अक्षर __user *buf,
			      माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा fbtft_par *par = info->par;
	sमाप_प्रकार res;

	dev_dbg(info->dev,
		"%s: count=%zd, ppos=%llu\n", __func__,  count, *ppos);
	res = fb_sys_ग_लिखो(info, buf, count, ppos);

	/* TODO: only mark changed area update all क्रम now */
	par->fbtftops.सूची_गढ़ोty(info, -1, 0);

	वापस res;
पूर्ण

/* from pxafb.c */
अटल अचिन्हित पूर्णांक chan_to_field(अचिन्हित पूर्णांक chan, काष्ठा fb_bitfield *bf)
अणु
	chan &= 0xffff;
	chan >>= 16 - bf->length;
	वापस chan << bf->offset;
पूर्ण

अटल पूर्णांक fbtft_fb_setcolreg(अचिन्हित पूर्णांक regno, अचिन्हित पूर्णांक red,
			      अचिन्हित पूर्णांक green, अचिन्हित पूर्णांक blue,
			      अचिन्हित पूर्णांक transp, काष्ठा fb_info *info)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक ret = 1;

	dev_dbg(info->dev,
		"%s(regno=%u, red=0x%X, green=0x%X, blue=0x%X, trans=0x%X)\n",
		__func__, regno, red, green, blue, transp);

	चयन (info->fix.visual) अणु
	हाल FB_VISUAL_TRUECOLOR:
		अगर (regno < 16) अणु
			u32 *pal = info->pseuकरो_palette;

			val  = chan_to_field(red,   &info->var.red);
			val |= chan_to_field(green, &info->var.green);
			val |= chan_to_field(blue,  &info->var.blue);

			pal[regno] = val;
			ret = 0;
		पूर्ण
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक fbtft_fb_blank(पूर्णांक blank, काष्ठा fb_info *info)
अणु
	काष्ठा fbtft_par *par = info->par;
	पूर्णांक ret = -EINVAL;

	dev_dbg(info->dev, "%s(blank=%d)\n",
		__func__, blank);

	अगर (!par->fbtftops.blank)
		वापस ret;

	चयन (blank) अणु
	हाल FB_BLANK_POWERDOWN:
	हाल FB_BLANK_VSYNC_SUSPEND:
	हाल FB_BLANK_HSYNC_SUSPEND:
	हाल FB_BLANK_NORMAL:
		ret = par->fbtftops.blank(par, true);
		अवरोध;
	हाल FB_BLANK_UNBLANK:
		ret = par->fbtftops.blank(par, false);
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम fbtft_merge_fbtftops(काष्ठा fbtft_ops *dst, काष्ठा fbtft_ops *src)
अणु
	अगर (src->ग_लिखो)
		dst->ग_लिखो = src->ग_लिखो;
	अगर (src->पढ़ो)
		dst->पढ़ो = src->पढ़ो;
	अगर (src->ग_लिखो_vmem)
		dst->ग_लिखो_vmem = src->ग_लिखो_vmem;
	अगर (src->ग_लिखो_रेजिस्टर)
		dst->ग_लिखो_रेजिस्टर = src->ग_लिखो_रेजिस्टर;
	अगर (src->set_addr_win)
		dst->set_addr_win = src->set_addr_win;
	अगर (src->reset)
		dst->reset = src->reset;
	अगर (src->सूची_गढ़ोty)
		dst->सूची_गढ़ोty = src->सूची_गढ़ोty;
	अगर (src->update_display)
		dst->update_display = src->update_display;
	अगर (src->init_display)
		dst->init_display = src->init_display;
	अगर (src->blank)
		dst->blank = src->blank;
	अगर (src->request_gpios_match)
		dst->request_gpios_match = src->request_gpios_match;
	अगर (src->request_gpios)
		dst->request_gpios = src->request_gpios;
	अगर (src->verअगरy_gpios)
		dst->verअगरy_gpios = src->verअगरy_gpios;
	अगर (src->रेजिस्टर_backlight)
		dst->रेजिस्टर_backlight = src->रेजिस्टर_backlight;
	अगर (src->unरेजिस्टर_backlight)
		dst->unरेजिस्टर_backlight = src->unरेजिस्टर_backlight;
	अगर (src->set_var)
		dst->set_var = src->set_var;
	अगर (src->set_gamma)
		dst->set_gamma = src->set_gamma;
पूर्ण

/**
 * fbtft_framebuffer_alloc - creates a new frame buffer info काष्ठाure
 *
 * @display: poपूर्णांकer to काष्ठाure describing the display
 * @dev: poपूर्णांकer to the device क्रम this fb, this can be शून्य
 * @pdata: platक्रमm data क्रम the display in use
 *
 * Creates a new frame buffer info काष्ठाure.
 *
 * Also creates and populates the following काष्ठाures:
 *   info->fbops
 *   info->fbdefio
 *   info->pseuकरो_palette
 *   par->fbtftops
 *   par->txbuf
 *
 * Returns the new काष्ठाure, or शून्य अगर an error occurred.
 *
 */
काष्ठा fb_info *fbtft_framebuffer_alloc(काष्ठा fbtft_display *display,
					काष्ठा device *dev,
					काष्ठा fbtft_platक्रमm_data *pdata)
अणु
	काष्ठा fb_info *info;
	काष्ठा fbtft_par *par;
	काष्ठा fb_ops *fbops = शून्य;
	काष्ठा fb_deferred_io *fbdefio = शून्य;
	u8 *vmem = शून्य;
	व्योम *txbuf = शून्य;
	व्योम *buf = शून्य;
	अचिन्हित पूर्णांक width;
	अचिन्हित पूर्णांक height;
	पूर्णांक txbuflen = display->txbuflen;
	अचिन्हित पूर्णांक bpp = display->bpp;
	अचिन्हित पूर्णांक fps = display->fps;
	पूर्णांक vmem_size;
	स्थिर s16 *init_sequence = display->init_sequence;
	अक्षर *gamma = display->gamma;
	u32 *gamma_curves = शून्य;

	/* sanity check */
	अगर (display->gamma_num * display->gamma_len >
			FBTFT_GAMMA_MAX_VALUES_TOTAL) अणु
		dev_err(dev, "FBTFT_GAMMA_MAX_VALUES_TOTAL=%d is exceeded\n",
			FBTFT_GAMMA_MAX_VALUES_TOTAL);
		वापस शून्य;
	पूर्ण

	/* शेषs */
	अगर (!fps)
		fps = 20;
	अगर (!bpp)
		bpp = 16;

	अगर (!pdata) अणु
		dev_err(dev, "platform data is missing\n");
		वापस शून्य;
	पूर्ण

	/* override driver values? */
	अगर (pdata->fps)
		fps = pdata->fps;
	अगर (pdata->txbuflen)
		txbuflen = pdata->txbuflen;
	अगर (pdata->display.init_sequence)
		init_sequence = pdata->display.init_sequence;
	अगर (pdata->gamma)
		gamma = pdata->gamma;
	अगर (pdata->display.debug)
		display->debug = pdata->display.debug;
	अगर (pdata->display.backlight)
		display->backlight = pdata->display.backlight;
	अगर (pdata->display.width)
		display->width = pdata->display.width;
	अगर (pdata->display.height)
		display->height = pdata->display.height;
	अगर (pdata->display.buswidth)
		display->buswidth = pdata->display.buswidth;
	अगर (pdata->display.regwidth)
		display->regwidth = pdata->display.regwidth;

	display->debug |= debug;
	fbtft_expand_debug_value(&display->debug);

	चयन (pdata->rotate) अणु
	हाल 90:
	हाल 270:
		width =  display->height;
		height = display->width;
		अवरोध;
	शेष:
		width =  display->width;
		height = display->height;
	पूर्ण

	vmem_size = display->width * display->height * bpp / 8;
	vmem = vzalloc(vmem_size);
	अगर (!vmem)
		जाओ alloc_fail;

	fbops = devm_kzalloc(dev, माप(काष्ठा fb_ops), GFP_KERNEL);
	अगर (!fbops)
		जाओ alloc_fail;

	fbdefio = devm_kzalloc(dev, माप(काष्ठा fb_deferred_io), GFP_KERNEL);
	अगर (!fbdefio)
		जाओ alloc_fail;

	buf = devm_kzalloc(dev, 128, GFP_KERNEL);
	अगर (!buf)
		जाओ alloc_fail;

	अगर (display->gamma_num && display->gamma_len) अणु
		gamma_curves = devm_kसुस्मृति(dev,
					    display->gamma_num *
					    display->gamma_len,
					    माप(gamma_curves[0]),
					    GFP_KERNEL);
		अगर (!gamma_curves)
			जाओ alloc_fail;
	पूर्ण

	info = framebuffer_alloc(माप(काष्ठा fbtft_par), dev);
	अगर (!info)
		जाओ alloc_fail;

	info->screen_buffer = vmem;
	info->fbops = fbops;
	info->fbdefio = fbdefio;

	fbops->owner        =      dev->driver->owner;
	fbops->fb_पढ़ो      =      fb_sys_पढ़ो;
	fbops->fb_ग_लिखो     =      fbtft_fb_ग_लिखो;
	fbops->fb_fillrect  =      fbtft_fb_fillrect;
	fbops->fb_copyarea  =      fbtft_fb_copyarea;
	fbops->fb_imageblit =      fbtft_fb_imageblit;
	fbops->fb_setcolreg =      fbtft_fb_setcolreg;
	fbops->fb_blank     =      fbtft_fb_blank;

	fbdefio->delay =           HZ / fps;
	fbdefio->deferred_io =     fbtft_deferred_io;
	fb_deferred_io_init(info);

	snम_लिखो(info->fix.id, माप(info->fix.id), "%s", dev->driver->name);
	info->fix.type =           FB_TYPE_PACKED_PIXELS;
	info->fix.visual =         FB_VISUAL_TRUECOLOR;
	info->fix.xpanstep =	   0;
	info->fix.ypanstep =	   0;
	info->fix.ywrapstep =	   0;
	info->fix.line_length =    width * bpp / 8;
	info->fix.accel =          FB_ACCEL_NONE;
	info->fix.smem_len =       vmem_size;

	info->var.rotate =         pdata->rotate;
	info->var.xres =           width;
	info->var.yres =           height;
	info->var.xres_भव =   info->var.xres;
	info->var.yres_भव =   info->var.yres;
	info->var.bits_per_pixel = bpp;
	info->var.nonstd =         1;

	/* RGB565 */
	info->var.red.offset =     11;
	info->var.red.length =     5;
	info->var.green.offset =   5;
	info->var.green.length =   6;
	info->var.blue.offset =    0;
	info->var.blue.length =    5;
	info->var.transp.offset =  0;
	info->var.transp.length =  0;

	info->flags =              FBINFO_FLAG_DEFAULT | FBINFO_VIRTFB;

	par = info->par;
	par->info = info;
	par->pdata = pdata;
	par->debug = display->debug;
	par->buf = buf;
	spin_lock_init(&par->dirty_lock);
	par->bgr = pdata->bgr;
	par->startbyte = pdata->startbyte;
	par->init_sequence = init_sequence;
	par->gamma.curves = gamma_curves;
	par->gamma.num_curves = display->gamma_num;
	par->gamma.num_values = display->gamma_len;
	mutex_init(&par->gamma.lock);
	info->pseuकरो_palette = par->pseuकरो_palette;

	अगर (par->gamma.curves && gamma) अणु
		अगर (fbtft_gamma_parse_str(par, par->gamma.curves, gamma,
					  म_माप(gamma)))
			जाओ release_framebuf;
	पूर्ण

	/* Transmit buffer */
	अगर (txbuflen == -1)
		txbuflen = vmem_size + 2; /* add in हाल startbyte is used */
	अगर (txbuflen >= vmem_size + 2)
		txbuflen = 0;

#अगर_घोषित __LITTLE_ENDIAN
	अगर ((!txbuflen) && (bpp > 8))
		txbuflen = PAGE_SIZE; /* need buffer क्रम byteswapping */
#पूर्ण_अगर

	अगर (txbuflen > 0) अणु
		txbuf = devm_kzalloc(par->info->device, txbuflen, GFP_KERNEL);
		अगर (!txbuf)
			जाओ release_framebuf;
		par->txbuf.buf = txbuf;
		par->txbuf.len = txbuflen;
	पूर्ण

	/* शेष fbtft operations */
	par->fbtftops.ग_लिखो = fbtft_ग_लिखो_spi;
	par->fbtftops.पढ़ो = fbtft_पढ़ो_spi;
	par->fbtftops.ग_लिखो_vmem = fbtft_ग_लिखो_vmem16_bus8;
	par->fbtftops.ग_लिखो_रेजिस्टर = fbtft_ग_लिखो_reg8_bus8;
	par->fbtftops.set_addr_win = fbtft_set_addr_win;
	par->fbtftops.reset = fbtft_reset;
	par->fbtftops.सूची_गढ़ोty = fbtft_सूची_गढ़ोty;
	par->fbtftops.update_display = fbtft_update_display;
	अगर (display->backlight)
		par->fbtftops.रेजिस्टर_backlight = fbtft_रेजिस्टर_backlight;

	/* use driver provided functions */
	fbtft_merge_fbtftops(&par->fbtftops, &display->fbtftops);

	वापस info;

release_framebuf:
	framebuffer_release(info);

alloc_fail:
	vमुक्त(vmem);

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(fbtft_framebuffer_alloc);

/**
 * fbtft_framebuffer_release - मुक्तs up all memory used by the framebuffer
 *
 * @info: frame buffer info काष्ठाure
 *
 */
व्योम fbtft_framebuffer_release(काष्ठा fb_info *info)
अणु
	fb_deferred_io_cleanup(info);
	vमुक्त(info->screen_buffer);
	framebuffer_release(info);
पूर्ण
EXPORT_SYMBOL(fbtft_framebuffer_release);

/**
 *	fbtft_रेजिस्टर_framebuffer - रेजिस्टरs a tft frame buffer device
 *	@fb_info: frame buffer info काष्ठाure
 *
 *  Sets SPI driverdata अगर needed
 *  Requests needed gpios.
 *  Initializes display
 *  Updates display.
 *	Registers a frame buffer device @fb_info.
 *
 *	Returns negative त्रुटि_सं on error, or zero क्रम success.
 *
 */
पूर्णांक fbtft_रेजिस्टर_framebuffer(काष्ठा fb_info *fb_info)
अणु
	पूर्णांक ret;
	अक्षर text1[50] = "";
	अक्षर text2[50] = "";
	काष्ठा fbtft_par *par = fb_info->par;
	काष्ठा spi_device *spi = par->spi;

	/* sanity checks */
	अगर (!par->fbtftops.init_display) अणु
		dev_err(fb_info->device, "missing fbtftops.init_display()\n");
		वापस -EINVAL;
	पूर्ण

	अगर (spi)
		spi_set_drvdata(spi, fb_info);
	अगर (par->pdev)
		platक्रमm_set_drvdata(par->pdev, fb_info);

	ret = par->fbtftops.request_gpios(par);
	अगर (ret < 0)
		जाओ reg_fail;

	अगर (par->fbtftops.verअगरy_gpios) अणु
		ret = par->fbtftops.verअगरy_gpios(par);
		अगर (ret < 0)
			जाओ reg_fail;
	पूर्ण

	ret = par->fbtftops.init_display(par);
	अगर (ret < 0)
		जाओ reg_fail;
	अगर (par->fbtftops.set_var) अणु
		ret = par->fbtftops.set_var(par);
		अगर (ret < 0)
			जाओ reg_fail;
	पूर्ण

	/* update the entire display */
	par->fbtftops.update_display(par, 0, par->info->var.yres - 1);

	अगर (par->fbtftops.set_gamma && par->gamma.curves) अणु
		ret = par->fbtftops.set_gamma(par, par->gamma.curves);
		अगर (ret)
			जाओ reg_fail;
	पूर्ण

	अगर (par->fbtftops.रेजिस्टर_backlight)
		par->fbtftops.रेजिस्टर_backlight(par);

	ret = रेजिस्टर_framebuffer(fb_info);
	अगर (ret < 0)
		जाओ reg_fail;

	fbtft_sysfs_init(par);

	अगर (par->txbuf.buf && par->txbuf.len >= 1024)
		प्र_लिखो(text1, ", %zu KiB buffer memory", par->txbuf.len >> 10);
	अगर (spi)
		प्र_लिखो(text2, ", spi%d.%d at %d MHz", spi->master->bus_num,
			spi->chip_select, spi->max_speed_hz / 1000000);
	dev_info(fb_info->dev,
		 "%s frame buffer, %dx%d, %d KiB video memory%s, fps=%lu%s\n",
		 fb_info->fix.id, fb_info->var.xres, fb_info->var.yres,
		 fb_info->fix.smem_len >> 10, text1,
		 HZ / fb_info->fbdefio->delay, text2);

#अगर_घोषित CONFIG_FB_BACKLIGHT
	/* Turn on backlight अगर available */
	अगर (fb_info->bl_dev) अणु
		fb_info->bl_dev->props.घातer = FB_BLANK_UNBLANK;
		fb_info->bl_dev->ops->update_status(fb_info->bl_dev);
	पूर्ण
#पूर्ण_अगर

	वापस 0;

reg_fail:
	अगर (par->fbtftops.unरेजिस्टर_backlight)
		par->fbtftops.unरेजिस्टर_backlight(par);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(fbtft_रेजिस्टर_framebuffer);

/**
 *	fbtft_unरेजिस्टर_framebuffer - releases a tft frame buffer device
 *	@fb_info: frame buffer info काष्ठाure
 *
 *  Frees SPI driverdata अगर needed
 *  Frees gpios.
 *	Unरेजिस्टरs frame buffer device.
 *
 */
पूर्णांक fbtft_unरेजिस्टर_framebuffer(काष्ठा fb_info *fb_info)
अणु
	काष्ठा fbtft_par *par = fb_info->par;

	अगर (par->fbtftops.unरेजिस्टर_backlight)
		par->fbtftops.unरेजिस्टर_backlight(par);
	fbtft_sysfs_निकास(par);
	unरेजिस्टर_framebuffer(fb_info);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(fbtft_unरेजिस्टर_framebuffer);

/**
 * fbtft_init_display_from_property() - Device Tree init_display() function
 * @par: Driver data
 *
 * Return: 0 अगर successful, negative अगर error
 */
अटल पूर्णांक fbtft_init_display_from_property(काष्ठा fbtft_par *par)
अणु
	काष्ठा device *dev = par->info->device;
	पूर्णांक buf[64], count, index, i, j, ret;
	u32 *values;
	u32 val;

	count = device_property_count_u32(dev, "init");
	अगर (count < 0)
		वापस count;
	अगर (count == 0)
		वापस -EINVAL;

	values = kदो_स्मृति_array(count + 1, माप(*values), GFP_KERNEL);
	अगर (!values)
		वापस -ENOMEM;

	ret = device_property_पढ़ो_u32_array(dev, "init", values, count);
	अगर (ret)
		जाओ out_मुक्त;

	par->fbtftops.reset(par);
	अगर (par->gpio.cs)
		gpiod_set_value(par->gpio.cs, 0);  /* Activate chip */

	index = -1;
	val = values[++index];

	जबतक (index < count) अणु
		अगर (val & FBTFT_OF_INIT_CMD) अणु
			val &= 0xFFFF;
			i = 0;
			जबतक ((index < count) && !(val & 0xFFFF0000)) अणु
				अगर (i > 63) अणु
					dev_err(dev,
						"%s: Maximum register values exceeded\n",
						__func__);
					ret = -EINVAL;
					जाओ out_मुक्त;
				पूर्ण
				buf[i++] = val;
				val = values[++index];
			पूर्ण
			/* make debug message */
			fbtft_par_dbg(DEBUG_INIT_DISPLAY, par,
				      "init: write_register:\n");
			क्रम (j = 0; j < i; j++)
				fbtft_par_dbg(DEBUG_INIT_DISPLAY, par,
					      "buf[%d] = %02X\n", j, buf[j]);

			par->fbtftops.ग_लिखो_रेजिस्टर(par, i,
				buf[0], buf[1], buf[2], buf[3],
				buf[4], buf[5], buf[6], buf[7],
				buf[8], buf[9], buf[10], buf[11],
				buf[12], buf[13], buf[14], buf[15],
				buf[16], buf[17], buf[18], buf[19],
				buf[20], buf[21], buf[22], buf[23],
				buf[24], buf[25], buf[26], buf[27],
				buf[28], buf[29], buf[30], buf[31],
				buf[32], buf[33], buf[34], buf[35],
				buf[36], buf[37], buf[38], buf[39],
				buf[40], buf[41], buf[42], buf[43],
				buf[44], buf[45], buf[46], buf[47],
				buf[48], buf[49], buf[50], buf[51],
				buf[52], buf[53], buf[54], buf[55],
				buf[56], buf[57], buf[58], buf[59],
				buf[60], buf[61], buf[62], buf[63]);
		पूर्ण अन्यथा अगर (val & FBTFT_OF_INIT_DELAY) अणु
			fbtft_par_dbg(DEBUG_INIT_DISPLAY, par,
				      "init: msleep(%u)\n", val & 0xFFFF);
			msleep(val & 0xFFFF);
			val = values[++index];
		पूर्ण अन्यथा अणु
			dev_err(dev, "illegal init value 0x%X\n", val);
			ret = -EINVAL;
			जाओ out_मुक्त;
		पूर्ण
	पूर्ण

out_मुक्त:
	kमुक्त(values);
	वापस ret;
पूर्ण

/**
 * fbtft_init_display() - Generic init_display() function
 * @par: Driver data
 *
 * Uses par->init_sequence to करो the initialization
 *
 * Return: 0 अगर successful, negative अगर error
 */
पूर्णांक fbtft_init_display(काष्ठा fbtft_par *par)
अणु
	पूर्णांक buf[64];
	अक्षर msg[128];
	अक्षर str[16];
	पूर्णांक i = 0;
	पूर्णांक j;

	/* sanity check */
	अगर (!par->init_sequence) अणु
		dev_err(par->info->device,
			"error: init_sequence is not set\n");
		वापस -EINVAL;
	पूर्ण

	/* make sure stop marker exists */
	क्रम (i = 0; i < FBTFT_MAX_INIT_SEQUENCE; i++)
		अगर (par->init_sequence[i] == -3)
			अवरोध;
	अगर (i == FBTFT_MAX_INIT_SEQUENCE) अणु
		dev_err(par->info->device,
			"missing stop marker at end of init sequence\n");
		वापस -EINVAL;
	पूर्ण

	par->fbtftops.reset(par);
	अगर (par->gpio.cs)
		gpiod_set_value(par->gpio.cs, 0);  /* Activate chip */

	i = 0;
	जबतक (i < FBTFT_MAX_INIT_SEQUENCE) अणु
		अगर (par->init_sequence[i] == -3) अणु
			/* करोne */
			वापस 0;
		पूर्ण
		अगर (par->init_sequence[i] >= 0) अणु
			dev_err(par->info->device,
				"missing delimiter at position %d\n", i);
			वापस -EINVAL;
		पूर्ण
		अगर (par->init_sequence[i + 1] < 0) अणु
			dev_err(par->info->device,
				"missing value after delimiter %d at position %d\n",
				par->init_sequence[i], i);
			वापस -EINVAL;
		पूर्ण
		चयन (par->init_sequence[i]) अणु
		हाल -1:
			i++;
			/* make debug message */
			म_नकल(msg, "");
			j = i + 1;
			जबतक (par->init_sequence[j] >= 0) अणु
				प्र_लिखो(str, "0x%02X ", par->init_sequence[j]);
				म_जोड़ो(msg, str);
				j++;
			पूर्ण
			fbtft_par_dbg(DEBUG_INIT_DISPLAY, par,
				      "init: write(0x%02X) %s\n",
				      par->init_sequence[i], msg);

			/* Write */
			j = 0;
			जबतक (par->init_sequence[i] >= 0) अणु
				अगर (j > 63) अणु
					dev_err(par->info->device,
						"%s: Maximum register values exceeded\n",
						__func__);
					वापस -EINVAL;
				पूर्ण
				buf[j++] = par->init_sequence[i++];
			पूर्ण
			par->fbtftops.ग_लिखो_रेजिस्टर(par, j,
				buf[0], buf[1], buf[2], buf[3],
				buf[4], buf[5], buf[6], buf[7],
				buf[8], buf[9], buf[10], buf[11],
				buf[12], buf[13], buf[14], buf[15],
				buf[16], buf[17], buf[18], buf[19],
				buf[20], buf[21], buf[22], buf[23],
				buf[24], buf[25], buf[26], buf[27],
				buf[28], buf[29], buf[30], buf[31],
				buf[32], buf[33], buf[34], buf[35],
				buf[36], buf[37], buf[38], buf[39],
				buf[40], buf[41], buf[42], buf[43],
				buf[44], buf[45], buf[46], buf[47],
				buf[48], buf[49], buf[50], buf[51],
				buf[52], buf[53], buf[54], buf[55],
				buf[56], buf[57], buf[58], buf[59],
				buf[60], buf[61], buf[62], buf[63]);
			अवरोध;
		हाल -2:
			i++;
			fbtft_par_dbg(DEBUG_INIT_DISPLAY, par,
				      "init: mdelay(%d)\n",
				      par->init_sequence[i]);
			mdelay(par->init_sequence[i++]);
			अवरोध;
		शेष:
			dev_err(par->info->device,
				"unknown delimiter %d at position %d\n",
				par->init_sequence[i], i);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	dev_err(par->info->device,
		"%s: something is wrong. Shouldn't get here.\n", __func__);
	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL(fbtft_init_display);

/**
 * fbtft_verअगरy_gpios() - Generic verअगरy_gpios() function
 * @par: Driver data
 *
 * Uses @spi, @pdev and @buswidth to determine which GPIOs is needed
 *
 * Return: 0 अगर successful, negative अगर error
 */
अटल पूर्णांक fbtft_verअगरy_gpios(काष्ठा fbtft_par *par)
अणु
	काष्ठा fbtft_platक्रमm_data *pdata = par->pdata;
	पूर्णांक i;

	fbtft_par_dbg(DEBUG_VERIFY_GPIOS, par, "%s()\n", __func__);

	अगर (pdata->display.buswidth != 9 &&  par->startbyte == 0 &&
	    !par->gpio.dc) अणु
		dev_err(par->info->device,
			"Missing info about 'dc' gpio. Aborting.\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!par->pdev)
		वापस 0;

	अगर (!par->gpio.wr) अणु
		dev_err(par->info->device, "Missing 'wr' gpio. Aborting.\n");
		वापस -EINVAL;
	पूर्ण
	क्रम (i = 0; i < pdata->display.buswidth; i++) अणु
		अगर (!par->gpio.db[i]) अणु
			dev_err(par->info->device,
				"Missing 'db%02d' gpio. Aborting.\n", i);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* वापसs 0 अगर the property is not present */
अटल u32 fbtft_property_value(काष्ठा device *dev, स्थिर अक्षर *propname)
अणु
	पूर्णांक ret;
	u32 val = 0;

	ret = device_property_पढ़ो_u32(dev, propname, &val);
	अगर (ret == 0)
		dev_info(dev, "%s: %s = %u\n", __func__, propname, val);

	वापस val;
पूर्ण

अटल काष्ठा fbtft_platक्रमm_data *fbtft_properties_पढ़ो(काष्ठा device *dev)
अणु
	काष्ठा fbtft_platक्रमm_data *pdata;

	अगर (!dev_fwnode(dev)) अणु
		dev_err(dev, "Missing platform data or properties\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	pdata = devm_kzalloc(dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस ERR_PTR(-ENOMEM);

	pdata->display.width = fbtft_property_value(dev, "width");
	pdata->display.height = fbtft_property_value(dev, "height");
	pdata->display.regwidth = fbtft_property_value(dev, "regwidth");
	pdata->display.buswidth = fbtft_property_value(dev, "buswidth");
	pdata->display.backlight = fbtft_property_value(dev, "backlight");
	pdata->display.bpp = fbtft_property_value(dev, "bpp");
	pdata->display.debug = fbtft_property_value(dev, "debug");
	pdata->rotate = fbtft_property_value(dev, "rotate");
	pdata->bgr = device_property_पढ़ो_bool(dev, "bgr");
	pdata->fps = fbtft_property_value(dev, "fps");
	pdata->txbuflen = fbtft_property_value(dev, "txbuflen");
	pdata->startbyte = fbtft_property_value(dev, "startbyte");
	device_property_पढ़ो_string(dev, "gamma", (स्थिर अक्षर **)&pdata->gamma);

	अगर (device_property_present(dev, "led-gpios"))
		pdata->display.backlight = 1;
	अगर (device_property_present(dev, "init"))
		pdata->display.fbtftops.init_display =
			fbtft_init_display_from_property;

	pdata->display.fbtftops.request_gpios = fbtft_request_gpios;

	वापस pdata;
पूर्ण

/**
 * fbtft_probe_common() - Generic device probe() helper function
 * @display: Display properties
 * @sdev: SPI device
 * @pdev: Platक्रमm device
 *
 * Allocates, initializes and रेजिस्टरs a framebuffer
 *
 * Either @sdev or @pdev should be शून्य
 *
 * Return: 0 अगर successful, negative अगर error
 */
पूर्णांक fbtft_probe_common(काष्ठा fbtft_display *display,
		       काष्ठा spi_device *sdev,
		       काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev;
	काष्ठा fb_info *info;
	काष्ठा fbtft_par *par;
	काष्ठा fbtft_platक्रमm_data *pdata;
	पूर्णांक ret;

	अगर (sdev)
		dev = &sdev->dev;
	अन्यथा
		dev = &pdev->dev;

	अगर (unlikely(display->debug & DEBUG_DRIVER_INIT_FUNCTIONS))
		dev_info(dev, "%s()\n", __func__);

	pdata = dev->platक्रमm_data;
	अगर (!pdata) अणु
		pdata = fbtft_properties_पढ़ो(dev);
		अगर (IS_ERR(pdata))
			वापस PTR_ERR(pdata);
	पूर्ण

	info = fbtft_framebuffer_alloc(display, dev, pdata);
	अगर (!info)
		वापस -ENOMEM;

	par = info->par;
	par->spi = sdev;
	par->pdev = pdev;

	अगर (display->buswidth == 0) अणु
		dev_err(dev, "buswidth is not set\n");
		वापस -EINVAL;
	पूर्ण

	/* ग_लिखो रेजिस्टर functions */
	अगर (display->regwidth == 8 && display->buswidth == 8)
		par->fbtftops.ग_लिखो_रेजिस्टर = fbtft_ग_लिखो_reg8_bus8;
	अन्यथा अगर (display->regwidth == 8 && display->buswidth == 9 && par->spi)
		par->fbtftops.ग_लिखो_रेजिस्टर = fbtft_ग_लिखो_reg8_bus9;
	अन्यथा अगर (display->regwidth == 16 && display->buswidth == 8)
		par->fbtftops.ग_लिखो_रेजिस्टर = fbtft_ग_लिखो_reg16_bus8;
	अन्यथा अगर (display->regwidth == 16 && display->buswidth == 16)
		par->fbtftops.ग_लिखो_रेजिस्टर = fbtft_ग_लिखो_reg16_bus16;
	अन्यथा
		dev_warn(dev,
			 "no default functions for regwidth=%d and buswidth=%d\n",
			 display->regwidth, display->buswidth);

	/* ग_लिखो_vmem() functions */
	अगर (display->buswidth == 8)
		par->fbtftops.ग_लिखो_vmem = fbtft_ग_लिखो_vmem16_bus8;
	अन्यथा अगर (display->buswidth == 9)
		par->fbtftops.ग_लिखो_vmem = fbtft_ग_लिखो_vmem16_bus9;
	अन्यथा अगर (display->buswidth == 16)
		par->fbtftops.ग_लिखो_vmem = fbtft_ग_लिखो_vmem16_bus16;

	/* GPIO ग_लिखो() functions */
	अगर (par->pdev) अणु
		अगर (display->buswidth == 8)
			par->fbtftops.ग_लिखो = fbtft_ग_लिखो_gpio8_wr;
		अन्यथा अगर (display->buswidth == 16)
			par->fbtftops.ग_लिखो = fbtft_ग_लिखो_gpio16_wr;
	पूर्ण

	/* 9-bit SPI setup */
	अगर (par->spi && display->buswidth == 9) अणु
		अगर (par->spi->master->bits_per_word_mask & SPI_BPW_MASK(9)) अणु
			par->spi->bits_per_word = 9;
		पूर्ण अन्यथा अणु
			dev_warn(&par->spi->dev,
				 "9-bit SPI not available, emulating using 8-bit.\n");
			/* allocate buffer with room क्रम dc bits */
			par->extra = devm_kzalloc(par->info->device,
						  par->txbuf.len +
						  (par->txbuf.len / 8) + 8,
						  GFP_KERNEL);
			अगर (!par->extra) अणु
				ret = -ENOMEM;
				जाओ out_release;
			पूर्ण
			par->fbtftops.ग_लिखो = fbtft_ग_लिखो_spi_emulate_9;
		पूर्ण
	पूर्ण

	अगर (!par->fbtftops.verअगरy_gpios)
		par->fbtftops.verअगरy_gpios = fbtft_verअगरy_gpios;

	/* make sure we still use the driver provided functions */
	fbtft_merge_fbtftops(&par->fbtftops, &display->fbtftops);

	/* use init_sequence अगर provided */
	अगर (par->init_sequence)
		par->fbtftops.init_display = fbtft_init_display;

	/* use platक्रमm_data provided functions above all */
	fbtft_merge_fbtftops(&par->fbtftops, &pdata->display.fbtftops);

	ret = fbtft_रेजिस्टर_framebuffer(info);
	अगर (ret < 0)
		जाओ out_release;

	वापस 0;

out_release:
	fbtft_framebuffer_release(info);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(fbtft_probe_common);

/**
 * fbtft_हटाओ_common() - Generic device हटाओ() helper function
 * @dev: Device
 * @info: Framebuffer
 *
 * Unरेजिस्टरs and releases the framebuffer
 *
 * Return: 0 अगर successful, negative अगर error
 */
पूर्णांक fbtft_हटाओ_common(काष्ठा device *dev, काष्ठा fb_info *info)
अणु
	काष्ठा fbtft_par *par;

	अगर (!info)
		वापस -EINVAL;
	par = info->par;
	अगर (par)
		fbtft_par_dbg(DEBUG_DRIVER_INIT_FUNCTIONS, par,
			      "%s()\n", __func__);
	fbtft_unरेजिस्टर_framebuffer(info);
	fbtft_framebuffer_release(info);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(fbtft_हटाओ_common);

MODULE_LICENSE("GPL");
