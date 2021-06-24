<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम the Solomon SSD1307 OLED controller
 *
 * Copyright 2012 Free Electrons
 */

#समावेश <linux/backlight.h>
#समावेश <linux/delay.h>
#समावेश <linux/fb.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/property.h>
#समावेश <linux/pwm.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/regulator/consumer.h>

#घोषणा SSD1307FB_DATA			0x40
#घोषणा SSD1307FB_COMMAND		0x80

#घोषणा SSD1307FB_SET_ADDRESS_MODE	0x20
#घोषणा SSD1307FB_SET_ADDRESS_MODE_HORIZONTAL	(0x00)
#घोषणा SSD1307FB_SET_ADDRESS_MODE_VERTICAL	(0x01)
#घोषणा SSD1307FB_SET_ADDRESS_MODE_PAGE		(0x02)
#घोषणा SSD1307FB_SET_COL_RANGE		0x21
#घोषणा SSD1307FB_SET_PAGE_RANGE	0x22
#घोषणा SSD1307FB_CONTRAST		0x81
#घोषणा SSD1307FB_SET_LOOKUP_TABLE	0x91
#घोषणा	SSD1307FB_CHARGE_PUMP		0x8d
#घोषणा SSD1307FB_SEG_REMAP_ON		0xa1
#घोषणा SSD1307FB_DISPLAY_OFF		0xae
#घोषणा SSD1307FB_SET_MULTIPLEX_RATIO	0xa8
#घोषणा SSD1307FB_DISPLAY_ON		0xaf
#घोषणा SSD1307FB_START_PAGE_ADDRESS	0xb0
#घोषणा SSD1307FB_SET_DISPLAY_OFFSET	0xd3
#घोषणा	SSD1307FB_SET_CLOCK_FREQ	0xd5
#घोषणा	SSD1307FB_SET_AREA_COLOR_MODE	0xd8
#घोषणा	SSD1307FB_SET_PRECHARGE_PERIOD	0xd9
#घोषणा	SSD1307FB_SET_COM_PINS_CONFIG	0xda
#घोषणा	SSD1307FB_SET_VCOMH		0xdb

#घोषणा MAX_CONTRAST 255

#घोषणा REFRESHRATE 1

अटल u_पूर्णांक refreshrate = REFRESHRATE;
module_param(refreshrate, uपूर्णांक, 0);

काष्ठा ssd1307fb_deviceinfo अणु
	u32 शेष_vcomh;
	u32 शेष_dclk_भाग;
	u32 शेष_dclk_frq;
	पूर्णांक need_pwm;
	पूर्णांक need_अक्षरgepump;
पूर्ण;

काष्ठा ssd1307fb_par अणु
	अचिन्हित area_color_enable : 1;
	अचिन्हित com_invdir : 1;
	अचिन्हित com_lrremap : 1;
	अचिन्हित com_seq : 1;
	अचिन्हित lookup_table_set : 1;
	अचिन्हित low_घातer : 1;
	अचिन्हित seg_remap : 1;
	u32 com_offset;
	u32 contrast;
	u32 dclk_भाग;
	u32 dclk_frq;
	स्थिर काष्ठा ssd1307fb_deviceinfo *device_info;
	काष्ठा i2c_client *client;
	u32 height;
	काष्ठा fb_info *info;
	u8 lookup_table[4];
	u32 page_offset;
	u32 col_offset;
	u32 preअक्षरgep1;
	u32 preअक्षरgep2;
	काष्ठा pwm_device *pwm;
	काष्ठा gpio_desc *reset;
	काष्ठा regulator *vbat_reg;
	u32 vcomh;
	u32 width;
पूर्ण;

काष्ठा ssd1307fb_array अणु
	u8	type;
	u8	data[];
पूर्ण;

अटल स्थिर काष्ठा fb_fix_screeninfo ssd1307fb_fix = अणु
	.id		= "Solomon SSD1307",
	.type		= FB_TYPE_PACKED_PIXELS,
	.visual		= FB_VISUAL_MONO10,
	.xpanstep	= 0,
	.ypanstep	= 0,
	.ywrapstep	= 0,
	.accel		= FB_ACCEL_NONE,
पूर्ण;

अटल स्थिर काष्ठा fb_var_screeninfo ssd1307fb_var = अणु
	.bits_per_pixel	= 1,
	.red = अणु .length = 1 पूर्ण,
	.green = अणु .length = 1 पूर्ण,
	.blue = अणु .length = 1 पूर्ण,
पूर्ण;

अटल काष्ठा ssd1307fb_array *ssd1307fb_alloc_array(u32 len, u8 type)
अणु
	काष्ठा ssd1307fb_array *array;

	array = kzalloc(माप(काष्ठा ssd1307fb_array) + len, GFP_KERNEL);
	अगर (!array)
		वापस शून्य;

	array->type = type;

	वापस array;
पूर्ण

अटल पूर्णांक ssd1307fb_ग_लिखो_array(काष्ठा i2c_client *client,
				 काष्ठा ssd1307fb_array *array, u32 len)
अणु
	पूर्णांक ret;

	len += माप(काष्ठा ssd1307fb_array);

	ret = i2c_master_send(client, (u8 *)array, len);
	अगर (ret != len) अणु
		dev_err(&client->dev, "Couldn't send I2C command.\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक ssd1307fb_ग_लिखो_cmd(काष्ठा i2c_client *client, u8 cmd)
अणु
	काष्ठा ssd1307fb_array *array;
	पूर्णांक ret;

	array = ssd1307fb_alloc_array(1, SSD1307FB_COMMAND);
	अगर (!array)
		वापस -ENOMEM;

	array->data[0] = cmd;

	ret = ssd1307fb_ग_लिखो_array(client, array, 1);
	kमुक्त(array);

	वापस ret;
पूर्ण

अटल व्योम ssd1307fb_update_display(काष्ठा ssd1307fb_par *par)
अणु
	काष्ठा ssd1307fb_array *array;
	u8 *vmem = par->info->screen_buffer;
	अचिन्हित पूर्णांक line_length = par->info->fix.line_length;
	अचिन्हित पूर्णांक pages = DIV_ROUND_UP(par->height, 8);
	पूर्णांक i, j, k;

	array = ssd1307fb_alloc_array(par->width * pages, SSD1307FB_DATA);
	अगर (!array)
		वापस;

	/*
	 * The screen is भागided in pages, each having a height of 8
	 * pixels, and the width of the screen. When sending a byte of
	 * data to the controller, it gives the 8 bits क्रम the current
	 * column. I.e, the first byte are the 8 bits of the first
	 * column, then the 8 bits क्रम the second column, etc.
	 *
	 *
	 * Representation of the screen, assuming it is 5 bits
	 * wide. Each letter-number combination is a bit that controls
	 * one pixel.
	 *
	 * A0 A1 A2 A3 A4
	 * B0 B1 B2 B3 B4
	 * C0 C1 C2 C3 C4
	 * D0 D1 D2 D3 D4
	 * E0 E1 E2 E3 E4
	 * F0 F1 F2 F3 F4
	 * G0 G1 G2 G3 G4
	 * H0 H1 H2 H3 H4
	 *
	 * If you want to update this screen, you need to send 5 bytes:
	 *  (1) A0 B0 C0 D0 E0 F0 G0 H0
	 *  (2) A1 B1 C1 D1 E1 F1 G1 H1
	 *  (3) A2 B2 C2 D2 E2 F2 G2 H2
	 *  (4) A3 B3 C3 D3 E3 F3 G3 H3
	 *  (5) A4 B4 C4 D4 E4 F4 G4 H4
	 */

	क्रम (i = 0; i < pages; i++) अणु
		क्रम (j = 0; j < par->width; j++) अणु
			पूर्णांक m = 8;
			u32 array_idx = i * par->width + j;
			array->data[array_idx] = 0;
			/* Last page may be partial */
			अगर (i + 1 == pages && par->height % 8)
				m = par->height % 8;
			क्रम (k = 0; k < m; k++) अणु
				u8 byte = vmem[(8 * i + k) * line_length +
					       j / 8];
				u8 bit = (byte >> (j % 8)) & 1;
				array->data[array_idx] |= bit << k;
			पूर्ण
		पूर्ण
	पूर्ण

	ssd1307fb_ग_लिखो_array(par->client, array, par->width * pages);
	kमुक्त(array);
पूर्ण


अटल sमाप_प्रकार ssd1307fb_ग_लिखो(काष्ठा fb_info *info, स्थिर अक्षर __user *buf,
		माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ssd1307fb_par *par = info->par;
	अचिन्हित दीर्घ total_size;
	अचिन्हित दीर्घ p = *ppos;
	व्योम *dst;

	total_size = info->fix.smem_len;

	अगर (p > total_size)
		वापस -EINVAL;

	अगर (count + p > total_size)
		count = total_size - p;

	अगर (!count)
		वापस -EINVAL;

	dst = info->screen_buffer + p;

	अगर (copy_from_user(dst, buf, count))
		वापस -EFAULT;

	ssd1307fb_update_display(par);

	*ppos += count;

	वापस count;
पूर्ण

अटल पूर्णांक ssd1307fb_blank(पूर्णांक blank_mode, काष्ठा fb_info *info)
अणु
	काष्ठा ssd1307fb_par *par = info->par;

	अगर (blank_mode != FB_BLANK_UNBLANK)
		वापस ssd1307fb_ग_लिखो_cmd(par->client, SSD1307FB_DISPLAY_OFF);
	अन्यथा
		वापस ssd1307fb_ग_लिखो_cmd(par->client, SSD1307FB_DISPLAY_ON);
पूर्ण

अटल व्योम ssd1307fb_fillrect(काष्ठा fb_info *info, स्थिर काष्ठा fb_fillrect *rect)
अणु
	काष्ठा ssd1307fb_par *par = info->par;
	sys_fillrect(info, rect);
	ssd1307fb_update_display(par);
पूर्ण

अटल व्योम ssd1307fb_copyarea(काष्ठा fb_info *info, स्थिर काष्ठा fb_copyarea *area)
अणु
	काष्ठा ssd1307fb_par *par = info->par;
	sys_copyarea(info, area);
	ssd1307fb_update_display(par);
पूर्ण

अटल व्योम ssd1307fb_imageblit(काष्ठा fb_info *info, स्थिर काष्ठा fb_image *image)
अणु
	काष्ठा ssd1307fb_par *par = info->par;
	sys_imageblit(info, image);
	ssd1307fb_update_display(par);
पूर्ण

अटल स्थिर काष्ठा fb_ops ssd1307fb_ops = अणु
	.owner		= THIS_MODULE,
	.fb_पढ़ो	= fb_sys_पढ़ो,
	.fb_ग_लिखो	= ssd1307fb_ग_लिखो,
	.fb_blank	= ssd1307fb_blank,
	.fb_fillrect	= ssd1307fb_fillrect,
	.fb_copyarea	= ssd1307fb_copyarea,
	.fb_imageblit	= ssd1307fb_imageblit,
पूर्ण;

अटल व्योम ssd1307fb_deferred_io(काष्ठा fb_info *info,
				काष्ठा list_head *pagelist)
अणु
	ssd1307fb_update_display(info->par);
पूर्ण

अटल पूर्णांक ssd1307fb_init(काष्ठा ssd1307fb_par *par)
अणु
	काष्ठा pwm_state pwmstate;
	पूर्णांक ret;
	u32 preअक्षरge, dclk, com_invdir, compins;

	अगर (par->device_info->need_pwm) अणु
		par->pwm = pwm_get(&par->client->dev, शून्य);
		अगर (IS_ERR(par->pwm)) अणु
			dev_err(&par->client->dev, "Could not get PWM from device tree!\n");
			वापस PTR_ERR(par->pwm);
		पूर्ण

		pwm_init_state(par->pwm, &pwmstate);
		pwm_set_relative_duty_cycle(&pwmstate, 50, 100);
		pwm_apply_state(par->pwm, &pwmstate);

		/* Enable the PWM */
		pwm_enable(par->pwm);

		dev_dbg(&par->client->dev, "Using PWM%d with a %lluns period.\n",
			par->pwm->pwm, pwm_get_period(par->pwm));
	पूर्ण

	/* Set initial contrast */
	ret = ssd1307fb_ग_लिखो_cmd(par->client, SSD1307FB_CONTRAST);
	अगर (ret < 0)
		वापस ret;

	ret = ssd1307fb_ग_लिखो_cmd(par->client, par->contrast);
	अगर (ret < 0)
		वापस ret;

	/* Set segment re-map */
	अगर (par->seg_remap) अणु
		ret = ssd1307fb_ग_लिखो_cmd(par->client, SSD1307FB_SEG_REMAP_ON);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	/* Set COM direction */
	com_invdir = 0xc0 | par->com_invdir << 3;
	ret = ssd1307fb_ग_लिखो_cmd(par->client,  com_invdir);
	अगर (ret < 0)
		वापस ret;

	/* Set multiplex ratio value */
	ret = ssd1307fb_ग_लिखो_cmd(par->client, SSD1307FB_SET_MULTIPLEX_RATIO);
	अगर (ret < 0)
		वापस ret;

	ret = ssd1307fb_ग_लिखो_cmd(par->client, par->height - 1);
	अगर (ret < 0)
		वापस ret;

	/* set display offset value */
	ret = ssd1307fb_ग_लिखो_cmd(par->client, SSD1307FB_SET_DISPLAY_OFFSET);
	अगर (ret < 0)
		वापस ret;

	ret = ssd1307fb_ग_लिखो_cmd(par->client, par->com_offset);
	अगर (ret < 0)
		वापस ret;

	/* Set घड़ी frequency */
	ret = ssd1307fb_ग_लिखो_cmd(par->client, SSD1307FB_SET_CLOCK_FREQ);
	अगर (ret < 0)
		वापस ret;

	dclk = ((par->dclk_भाग - 1) & 0xf) | (par->dclk_frq & 0xf) << 4;
	ret = ssd1307fb_ग_लिखो_cmd(par->client, dclk);
	अगर (ret < 0)
		वापस ret;

	/* Set Set Area Color Mode ON/OFF & Low Power Display Mode */
	अगर (par->area_color_enable || par->low_घातer) अणु
		u32 mode;

		ret = ssd1307fb_ग_लिखो_cmd(par->client,
					  SSD1307FB_SET_AREA_COLOR_MODE);
		अगर (ret < 0)
			वापस ret;

		mode = (par->area_color_enable ? 0x30 : 0) |
			(par->low_घातer ? 5 : 0);
		ret = ssd1307fb_ग_लिखो_cmd(par->client, mode);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	/* Set preअक्षरge period in number of ticks from the पूर्णांकernal घड़ी */
	ret = ssd1307fb_ग_लिखो_cmd(par->client, SSD1307FB_SET_PRECHARGE_PERIOD);
	अगर (ret < 0)
		वापस ret;

	preअक्षरge = (par->preअक्षरgep1 & 0xf) | (par->preअक्षरgep2 & 0xf) << 4;
	ret = ssd1307fb_ग_लिखो_cmd(par->client, preअक्षरge);
	अगर (ret < 0)
		वापस ret;

	/* Set COM pins configuration */
	ret = ssd1307fb_ग_लिखो_cmd(par->client, SSD1307FB_SET_COM_PINS_CONFIG);
	अगर (ret < 0)
		वापस ret;

	compins = 0x02 | !par->com_seq << 4 | par->com_lrremap << 5;
	ret = ssd1307fb_ग_लिखो_cmd(par->client, compins);
	अगर (ret < 0)
		वापस ret;

	/* Set VCOMH */
	ret = ssd1307fb_ग_लिखो_cmd(par->client, SSD1307FB_SET_VCOMH);
	अगर (ret < 0)
		वापस ret;

	ret = ssd1307fb_ग_लिखो_cmd(par->client, par->vcomh);
	अगर (ret < 0)
		वापस ret;

	/* Turn on the DC-DC Charge Pump */
	ret = ssd1307fb_ग_लिखो_cmd(par->client, SSD1307FB_CHARGE_PUMP);
	अगर (ret < 0)
		वापस ret;

	ret = ssd1307fb_ग_लिखो_cmd(par->client,
		BIT(4) | (par->device_info->need_अक्षरgepump ? BIT(2) : 0));
	अगर (ret < 0)
		वापस ret;

	/* Set lookup table */
	अगर (par->lookup_table_set) अणु
		पूर्णांक i;

		ret = ssd1307fb_ग_लिखो_cmd(par->client,
					  SSD1307FB_SET_LOOKUP_TABLE);
		अगर (ret < 0)
			वापस ret;

		क्रम (i = 0; i < ARRAY_SIZE(par->lookup_table); ++i) अणु
			u8 val = par->lookup_table[i];

			अगर (val < 31 || val > 63)
				dev_warn(&par->client->dev,
					 "lookup table index %d value out of range 31 <= %d <= 63\n",
					 i, val);
			ret = ssd1307fb_ग_लिखो_cmd(par->client, val);
			अगर (ret < 0)
				वापस ret;
		पूर्ण
	पूर्ण

	/* Switch to horizontal addressing mode */
	ret = ssd1307fb_ग_लिखो_cmd(par->client, SSD1307FB_SET_ADDRESS_MODE);
	अगर (ret < 0)
		वापस ret;

	ret = ssd1307fb_ग_लिखो_cmd(par->client,
				  SSD1307FB_SET_ADDRESS_MODE_HORIZONTAL);
	अगर (ret < 0)
		वापस ret;

	/* Set column range */
	ret = ssd1307fb_ग_लिखो_cmd(par->client, SSD1307FB_SET_COL_RANGE);
	अगर (ret < 0)
		वापस ret;

	ret = ssd1307fb_ग_लिखो_cmd(par->client, par->col_offset);
	अगर (ret < 0)
		वापस ret;

	ret = ssd1307fb_ग_लिखो_cmd(par->client, par->col_offset + par->width - 1);
	अगर (ret < 0)
		वापस ret;

	/* Set page range */
	ret = ssd1307fb_ग_लिखो_cmd(par->client, SSD1307FB_SET_PAGE_RANGE);
	अगर (ret < 0)
		वापस ret;

	ret = ssd1307fb_ग_लिखो_cmd(par->client, par->page_offset);
	अगर (ret < 0)
		वापस ret;

	ret = ssd1307fb_ग_लिखो_cmd(par->client,
				  par->page_offset +
				  DIV_ROUND_UP(par->height, 8) - 1);
	अगर (ret < 0)
		वापस ret;

	/* Clear the screen */
	ssd1307fb_update_display(par);

	/* Turn on the display */
	ret = ssd1307fb_ग_लिखो_cmd(par->client, SSD1307FB_DISPLAY_ON);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक ssd1307fb_update_bl(काष्ठा backlight_device *bdev)
अणु
	काष्ठा ssd1307fb_par *par = bl_get_data(bdev);
	पूर्णांक ret;
	पूर्णांक brightness = bdev->props.brightness;

	par->contrast = brightness;

	ret = ssd1307fb_ग_लिखो_cmd(par->client, SSD1307FB_CONTRAST);
	अगर (ret < 0)
		वापस ret;
	ret = ssd1307fb_ग_लिखो_cmd(par->client, par->contrast);
	अगर (ret < 0)
		वापस ret;
	वापस 0;
पूर्ण

अटल पूर्णांक ssd1307fb_get_brightness(काष्ठा backlight_device *bdev)
अणु
	काष्ठा ssd1307fb_par *par = bl_get_data(bdev);

	वापस par->contrast;
पूर्ण

अटल पूर्णांक ssd1307fb_check_fb(काष्ठा backlight_device *bdev,
				   काष्ठा fb_info *info)
अणु
	वापस (info->bl_dev == bdev);
पूर्ण

अटल स्थिर काष्ठा backlight_ops ssd1307fb_bl_ops = अणु
	.options	= BL_CORE_SUSPENDRESUME,
	.update_status	= ssd1307fb_update_bl,
	.get_brightness	= ssd1307fb_get_brightness,
	.check_fb	= ssd1307fb_check_fb,
पूर्ण;

अटल काष्ठा ssd1307fb_deviceinfo ssd1307fb_ssd1305_deviceinfo = अणु
	.शेष_vcomh = 0x34,
	.शेष_dclk_भाग = 1,
	.शेष_dclk_frq = 7,
पूर्ण;

अटल काष्ठा ssd1307fb_deviceinfo ssd1307fb_ssd1306_deviceinfo = अणु
	.शेष_vcomh = 0x20,
	.शेष_dclk_भाग = 1,
	.शेष_dclk_frq = 8,
	.need_अक्षरgepump = 1,
पूर्ण;

अटल काष्ठा ssd1307fb_deviceinfo ssd1307fb_ssd1307_deviceinfo = अणु
	.शेष_vcomh = 0x20,
	.शेष_dclk_भाग = 2,
	.शेष_dclk_frq = 12,
	.need_pwm = 1,
पूर्ण;

अटल काष्ठा ssd1307fb_deviceinfo ssd1307fb_ssd1309_deviceinfo = अणु
	.शेष_vcomh = 0x34,
	.शेष_dclk_भाग = 1,
	.शेष_dclk_frq = 10,
पूर्ण;

अटल स्थिर काष्ठा of_device_id ssd1307fb_of_match[] = अणु
	अणु
		.compatible = "solomon,ssd1305fb-i2c",
		.data = (व्योम *)&ssd1307fb_ssd1305_deviceinfo,
	पूर्ण,
	अणु
		.compatible = "solomon,ssd1306fb-i2c",
		.data = (व्योम *)&ssd1307fb_ssd1306_deviceinfo,
	पूर्ण,
	अणु
		.compatible = "solomon,ssd1307fb-i2c",
		.data = (व्योम *)&ssd1307fb_ssd1307_deviceinfo,
	पूर्ण,
	अणु
		.compatible = "solomon,ssd1309fb-i2c",
		.data = (व्योम *)&ssd1307fb_ssd1309_deviceinfo,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ssd1307fb_of_match);

अटल पूर्णांक ssd1307fb_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा backlight_device *bl;
	अक्षर bl_name[12];
	काष्ठा fb_info *info;
	काष्ठा fb_deferred_io *ssd1307fb_defio;
	u32 vmem_size;
	काष्ठा ssd1307fb_par *par;
	व्योम *vmem;
	पूर्णांक ret;

	info = framebuffer_alloc(माप(काष्ठा ssd1307fb_par), dev);
	अगर (!info)
		वापस -ENOMEM;

	par = info->par;
	par->info = info;
	par->client = client;

	par->device_info = device_get_match_data(dev);

	par->reset = devm_gpiod_get_optional(dev, "reset", GPIOD_OUT_LOW);
	अगर (IS_ERR(par->reset)) अणु
		dev_err(dev, "failed to get reset gpio: %ld\n",
			PTR_ERR(par->reset));
		ret = PTR_ERR(par->reset);
		जाओ fb_alloc_error;
	पूर्ण

	par->vbat_reg = devm_regulator_get_optional(dev, "vbat");
	अगर (IS_ERR(par->vbat_reg)) अणु
		ret = PTR_ERR(par->vbat_reg);
		अगर (ret == -ENODEV) अणु
			par->vbat_reg = शून्य;
		पूर्ण अन्यथा अणु
			dev_err(dev, "failed to get VBAT regulator: %d\n", ret);
			जाओ fb_alloc_error;
		पूर्ण
	पूर्ण

	अगर (device_property_पढ़ो_u32(dev, "solomon,width", &par->width))
		par->width = 96;

	अगर (device_property_पढ़ो_u32(dev, "solomon,height", &par->height))
		par->height = 16;

	अगर (device_property_पढ़ो_u32(dev, "solomon,page-offset", &par->page_offset))
		par->page_offset = 1;

	अगर (device_property_पढ़ो_u32(dev, "solomon,col-offset", &par->col_offset))
		par->col_offset = 0;

	अगर (device_property_पढ़ो_u32(dev, "solomon,com-offset", &par->com_offset))
		par->com_offset = 0;

	अगर (device_property_पढ़ो_u32(dev, "solomon,prechargep1", &par->preअक्षरgep1))
		par->preअक्षरgep1 = 2;

	अगर (device_property_पढ़ो_u32(dev, "solomon,prechargep2", &par->preअक्षरgep2))
		par->preअक्षरgep2 = 2;

	अगर (!device_property_पढ़ो_u8_array(dev, "solomon,lookup-table",
					   par->lookup_table,
					   ARRAY_SIZE(par->lookup_table)))
		par->lookup_table_set = 1;

	par->seg_remap = !device_property_पढ़ो_bool(dev, "solomon,segment-no-remap");
	par->com_seq = device_property_पढ़ो_bool(dev, "solomon,com-seq");
	par->com_lrremap = device_property_पढ़ो_bool(dev, "solomon,com-lrremap");
	par->com_invdir = device_property_पढ़ो_bool(dev, "solomon,com-invdir");
	par->area_color_enable =
		device_property_पढ़ो_bool(dev, "solomon,area-color-enable");
	par->low_घातer = device_property_पढ़ो_bool(dev, "solomon,low-power");

	par->contrast = 127;
	par->vcomh = par->device_info->शेष_vcomh;

	/* Setup display timing */
	अगर (device_property_पढ़ो_u32(dev, "solomon,dclk-div", &par->dclk_भाग))
		par->dclk_भाग = par->device_info->शेष_dclk_भाग;
	अगर (device_property_पढ़ो_u32(dev, "solomon,dclk-frq", &par->dclk_frq))
		par->dclk_frq = par->device_info->शेष_dclk_frq;

	vmem_size = DIV_ROUND_UP(par->width, 8) * par->height;

	vmem = (व्योम *)__get_मुक्त_pages(GFP_KERNEL | __GFP_ZERO,
					get_order(vmem_size));
	अगर (!vmem) अणु
		dev_err(dev, "Couldn't allocate graphical memory.\n");
		ret = -ENOMEM;
		जाओ fb_alloc_error;
	पूर्ण

	ssd1307fb_defio = devm_kzalloc(dev, माप(*ssd1307fb_defio),
				       GFP_KERNEL);
	अगर (!ssd1307fb_defio) अणु
		dev_err(dev, "Couldn't allocate deferred io.\n");
		ret = -ENOMEM;
		जाओ fb_alloc_error;
	पूर्ण

	ssd1307fb_defio->delay = HZ / refreshrate;
	ssd1307fb_defio->deferred_io = ssd1307fb_deferred_io;

	info->fbops = &ssd1307fb_ops;
	info->fix = ssd1307fb_fix;
	info->fix.line_length = DIV_ROUND_UP(par->width, 8);
	info->fbdefio = ssd1307fb_defio;

	info->var = ssd1307fb_var;
	info->var.xres = par->width;
	info->var.xres_भव = par->width;
	info->var.yres = par->height;
	info->var.yres_भव = par->height;

	info->screen_buffer = vmem;
	info->fix.smem_start = __pa(vmem);
	info->fix.smem_len = vmem_size;

	fb_deferred_io_init(info);

	i2c_set_clientdata(client, info);

	अगर (par->reset) अणु
		/* Reset the screen */
		gpiod_set_value_cansleep(par->reset, 1);
		udelay(4);
		gpiod_set_value_cansleep(par->reset, 0);
		udelay(4);
	पूर्ण

	अगर (par->vbat_reg) अणु
		ret = regulator_enable(par->vbat_reg);
		अगर (ret) अणु
			dev_err(dev, "failed to enable VBAT: %d\n", ret);
			जाओ reset_oled_error;
		पूर्ण
	पूर्ण

	ret = ssd1307fb_init(par);
	अगर (ret)
		जाओ regulator_enable_error;

	ret = रेजिस्टर_framebuffer(info);
	अगर (ret) अणु
		dev_err(dev, "Couldn't register the framebuffer\n");
		जाओ panel_init_error;
	पूर्ण

	snम_लिखो(bl_name, माप(bl_name), "ssd1307fb%d", info->node);
	bl = backlight_device_रेजिस्टर(bl_name, dev, par, &ssd1307fb_bl_ops,
				       शून्य);
	अगर (IS_ERR(bl)) अणु
		ret = PTR_ERR(bl);
		dev_err(dev, "unable to register backlight device: %d\n", ret);
		जाओ bl_init_error;
	पूर्ण

	bl->props.brightness = par->contrast;
	bl->props.max_brightness = MAX_CONTRAST;
	info->bl_dev = bl;

	dev_info(dev, "fb%d: %s framebuffer device registered, using %d bytes of video memory\n", info->node, info->fix.id, vmem_size);

	वापस 0;

bl_init_error:
	unरेजिस्टर_framebuffer(info);
panel_init_error:
	अगर (par->device_info->need_pwm) अणु
		pwm_disable(par->pwm);
		pwm_put(par->pwm);
	पूर्ण
regulator_enable_error:
	अगर (par->vbat_reg)
		regulator_disable(par->vbat_reg);
reset_oled_error:
	fb_deferred_io_cleanup(info);
fb_alloc_error:
	framebuffer_release(info);
	वापस ret;
पूर्ण

अटल पूर्णांक ssd1307fb_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा fb_info *info = i2c_get_clientdata(client);
	काष्ठा ssd1307fb_par *par = info->par;

	ssd1307fb_ग_लिखो_cmd(par->client, SSD1307FB_DISPLAY_OFF);

	backlight_device_unरेजिस्टर(info->bl_dev);

	unरेजिस्टर_framebuffer(info);
	अगर (par->device_info->need_pwm) अणु
		pwm_disable(par->pwm);
		pwm_put(par->pwm);
	पूर्ण
	अगर (par->vbat_reg)
		regulator_disable(par->vbat_reg);
	fb_deferred_io_cleanup(info);
	__मुक्त_pages(__va(info->fix.smem_start), get_order(info->fix.smem_len));
	framebuffer_release(info);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ssd1307fb_i2c_id[] = अणु
	अणु "ssd1305fb", 0 पूर्ण,
	अणु "ssd1306fb", 0 पूर्ण,
	अणु "ssd1307fb", 0 पूर्ण,
	अणु "ssd1309fb", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ssd1307fb_i2c_id);

अटल काष्ठा i2c_driver ssd1307fb_driver = अणु
	.probe_new = ssd1307fb_probe,
	.हटाओ = ssd1307fb_हटाओ,
	.id_table = ssd1307fb_i2c_id,
	.driver = अणु
		.name = "ssd1307fb",
		.of_match_table = ssd1307fb_of_match,
	पूर्ण,
पूर्ण;

module_i2c_driver(ssd1307fb_driver);

MODULE_DESCRIPTION("FB driver for the Solomon SSD1307 OLED controller");
MODULE_AUTHOR("Maxime Ripard <maxime.ripard@free-electrons.com>");
MODULE_LICENSE("GPL");
