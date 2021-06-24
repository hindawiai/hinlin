<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Cobalt/SEAD3 LCD frame buffer driver.
 *
 *  Copyright (C) 2008  Yoichi Yuasa <yuasa@linux-mips.org>
 *  Copyright (C) 2012  MIPS Technologies, Inc.
 */
#समावेश <linux/delay.h>
#समावेश <linux/fb.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/ioport.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/module.h>
#समावेश <linux/sched/संकेत.स>

/*
 * Cursor position address
 * \X  0    1    2  ...  14   15
 * Y+----+----+----+---+----+----+
 * 0|0x00|0x01|0x02|...|0x0e|0x0f|
 *  +----+----+----+---+----+----+
 * 1|0x40|0x41|0x42|...|0x4e|0x4f|
 *  +----+----+----+---+----+----+
 */
#घोषणा LCD_DATA_REG_OFFSET	0x10
#घोषणा LCD_XRES_MAX		16
#घोषणा LCD_YRES_MAX		2
#घोषणा LCD_CHARS_MAX		32

#घोषणा LCD_CLEAR		0x01
#घोषणा LCD_CURSOR_MOVE_HOME	0x02
#घोषणा LCD_RESET		0x06
#घोषणा LCD_OFF			0x08
#घोषणा LCD_CURSOR_OFF		0x0c
#घोषणा LCD_CURSOR_BLINK_OFF	0x0e
#घोषणा LCD_CURSOR_ON		0x0f
#घोषणा LCD_ON			LCD_CURSOR_ON
#घोषणा LCD_CURSOR_MOVE_LEFT	0x10
#घोषणा LCD_CURSOR_MOVE_RIGHT	0x14
#घोषणा LCD_DISPLAY_LEFT	0x18
#घोषणा LCD_DISPLAY_RIGHT	0x1c
#घोषणा LCD_PRERESET		0x3f	/* execute 4 बार continuously */
#घोषणा LCD_BUSY		0x80

#घोषणा LCD_GRAPHIC_MODE	0x40
#घोषणा LCD_TEXT_MODE		0x80
#घोषणा LCD_CUR_POS_MASK	0x7f

#घोषणा LCD_CUR_POS(x)		((x) & LCD_CUR_POS_MASK)
#घोषणा LCD_TEXT_POS(x)		((x) | LCD_TEXT_MODE)

अटल अंतरभूत व्योम lcd_ग_लिखो_control(काष्ठा fb_info *info, u8 control)
अणु
	ग_लिखोl((u32)control << 24, info->screen_base);
पूर्ण

अटल अंतरभूत u8 lcd_पढ़ो_control(काष्ठा fb_info *info)
अणु
	वापस पढ़ोl(info->screen_base) >> 24;
पूर्ण

अटल अंतरभूत व्योम lcd_ग_लिखो_data(काष्ठा fb_info *info, u8 data)
अणु
	ग_लिखोl((u32)data << 24, info->screen_base + LCD_DATA_REG_OFFSET);
पूर्ण

अटल अंतरभूत u8 lcd_पढ़ो_data(काष्ठा fb_info *info)
अणु
	वापस पढ़ोl(info->screen_base + LCD_DATA_REG_OFFSET) >> 24;
पूर्ण

अटल पूर्णांक lcd_busy_रुको(काष्ठा fb_info *info)
अणु
	u8 val = 0;
	पूर्णांक समयout = 10, retval = 0;

	करो अणु
		val = lcd_पढ़ो_control(info);
		val &= LCD_BUSY;
		अगर (val != LCD_BUSY)
			अवरोध;

		अगर (msleep_पूर्णांकerruptible(1))
			वापस -EINTR;

		समयout--;
	पूर्ण जबतक (समयout);

	अगर (val == LCD_BUSY)
		retval = -EBUSY;

	वापस retval;
पूर्ण

अटल व्योम lcd_clear(काष्ठा fb_info *info)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 4; i++) अणु
		udelay(150);

		lcd_ग_लिखो_control(info, LCD_PRERESET);
	पूर्ण

	udelay(150);

	lcd_ग_लिखो_control(info, LCD_CLEAR);

	udelay(150);

	lcd_ग_लिखो_control(info, LCD_RESET);
पूर्ण

अटल स्थिर काष्ठा fb_fix_screeninfo cobalt_lcdfb_fix = अणु
	.id		= "cobalt-lcd",
	.type		= FB_TYPE_TEXT,
	.type_aux	= FB_AUX_TEXT_MDA,
	.visual		= FB_VISUAL_MONO01,
	.line_length	= LCD_XRES_MAX,
	.accel		= FB_ACCEL_NONE,
पूर्ण;

अटल sमाप_प्रकार cobalt_lcdfb_पढ़ो(काष्ठा fb_info *info, अक्षर __user *buf,
				 माप_प्रकार count, loff_t *ppos)
अणु
	अक्षर src[LCD_CHARS_MAX];
	अचिन्हित दीर्घ pos;
	पूर्णांक len, retval = 0;

	pos = *ppos;
	अगर (pos >= LCD_CHARS_MAX || count == 0)
		वापस 0;

	अगर (count > LCD_CHARS_MAX)
		count = LCD_CHARS_MAX;

	अगर (pos + count > LCD_CHARS_MAX)
		count = LCD_CHARS_MAX - pos;

	क्रम (len = 0; len < count; len++) अणु
		retval = lcd_busy_रुको(info);
		अगर (retval < 0)
			अवरोध;

		lcd_ग_लिखो_control(info, LCD_TEXT_POS(pos));

		retval = lcd_busy_रुको(info);
		अगर (retval < 0)
			अवरोध;

		src[len] = lcd_पढ़ो_data(info);
		अगर (pos == 0x0f)
			pos = 0x40;
		अन्यथा
			pos++;
	पूर्ण

	अगर (retval < 0 && संकेत_pending(current))
		वापस -ERESTARTSYS;

	अगर (copy_to_user(buf, src, len))
		वापस -EFAULT;

	*ppos += len;

	वापस len;
पूर्ण

अटल sमाप_प्रकार cobalt_lcdfb_ग_लिखो(काष्ठा fb_info *info, स्थिर अक्षर __user *buf,
				  माप_प्रकार count, loff_t *ppos)
अणु
	अक्षर dst[LCD_CHARS_MAX];
	अचिन्हित दीर्घ pos;
	पूर्णांक len, retval = 0;

	pos = *ppos;
	अगर (pos >= LCD_CHARS_MAX || count == 0)
		वापस 0;

	अगर (count > LCD_CHARS_MAX)
		count = LCD_CHARS_MAX;

	अगर (pos + count > LCD_CHARS_MAX)
		count = LCD_CHARS_MAX - pos;

	अगर (copy_from_user(dst, buf, count))
		वापस -EFAULT;

	क्रम (len = 0; len < count; len++) अणु
		retval = lcd_busy_रुको(info);
		अगर (retval < 0)
			अवरोध;

		lcd_ग_लिखो_control(info, LCD_TEXT_POS(pos));

		retval = lcd_busy_रुको(info);
		अगर (retval < 0)
			अवरोध;

		lcd_ग_लिखो_data(info, dst[len]);
		अगर (pos == 0x0f)
			pos = 0x40;
		अन्यथा
			pos++;
	पूर्ण

	अगर (retval < 0 && संकेत_pending(current))
		वापस -ERESTARTSYS;

	*ppos += len;

	वापस len;
पूर्ण

अटल पूर्णांक cobalt_lcdfb_blank(पूर्णांक blank_mode, काष्ठा fb_info *info)
अणु
	पूर्णांक retval;

	retval = lcd_busy_रुको(info);
	अगर (retval < 0)
		वापस retval;

	चयन (blank_mode) अणु
	हाल FB_BLANK_UNBLANK:
		lcd_ग_लिखो_control(info, LCD_ON);
		अवरोध;
	शेष:
		lcd_ग_लिखो_control(info, LCD_OFF);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cobalt_lcdfb_cursor(काष्ठा fb_info *info, काष्ठा fb_cursor *cursor)
अणु
	u32 x, y;
	पूर्णांक retval;

	चयन (cursor->set) अणु
	हाल FB_CUR_SETPOS:
		x = cursor->image.dx;
		y = cursor->image.dy;
		अगर (x >= LCD_XRES_MAX || y >= LCD_YRES_MAX)
			वापस -EINVAL;

		retval = lcd_busy_रुको(info);
		अगर (retval < 0)
			वापस retval;

		lcd_ग_लिखो_control(info,
				  LCD_TEXT_POS(info->fix.line_length * y + x));
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	retval = lcd_busy_रुको(info);
	अगर (retval < 0)
		वापस retval;

	अगर (cursor->enable)
		lcd_ग_लिखो_control(info, LCD_CURSOR_ON);
	अन्यथा
		lcd_ग_लिखो_control(info, LCD_CURSOR_OFF);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा fb_ops cobalt_lcd_fbops = अणु
	.owner		= THIS_MODULE,
	.fb_पढ़ो	= cobalt_lcdfb_पढ़ो,
	.fb_ग_लिखो	= cobalt_lcdfb_ग_लिखो,
	.fb_blank	= cobalt_lcdfb_blank,
	.fb_cursor	= cobalt_lcdfb_cursor,
पूर्ण;

अटल पूर्णांक cobalt_lcdfb_probe(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा fb_info *info;
	काष्ठा resource *res;
	पूर्णांक retval;

	info = framebuffer_alloc(0, &dev->dev);
	अगर (!info)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(dev, IORESOURCE_MEM, 0);
	अगर (!res) अणु
		framebuffer_release(info);
		वापस -EBUSY;
	पूर्ण

	info->screen_size = resource_size(res);
	info->screen_base = devm_ioremap(&dev->dev, res->start,
					 info->screen_size);
	अगर (!info->screen_base) अणु
		framebuffer_release(info);
		वापस -ENOMEM;
	पूर्ण

	info->fbops = &cobalt_lcd_fbops;
	info->fix = cobalt_lcdfb_fix;
	info->fix.smem_start = res->start;
	info->fix.smem_len = info->screen_size;
	info->pseuकरो_palette = शून्य;
	info->par = शून्य;
	info->flags = FBINFO_DEFAULT;

	retval = रेजिस्टर_framebuffer(info);
	अगर (retval < 0) अणु
		framebuffer_release(info);
		वापस retval;
	पूर्ण

	platक्रमm_set_drvdata(dev, info);

	lcd_clear(info);

	fb_info(info, "Cobalt server LCD frame buffer device\n");

	वापस 0;
पूर्ण

अटल पूर्णांक cobalt_lcdfb_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा fb_info *info;

	info = platक्रमm_get_drvdata(dev);
	अगर (info) अणु
		unरेजिस्टर_framebuffer(info);
		framebuffer_release(info);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver cobalt_lcdfb_driver = अणु
	.probe	= cobalt_lcdfb_probe,
	.हटाओ	= cobalt_lcdfb_हटाओ,
	.driver	= अणु
		.name	= "cobalt-lcd",
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(cobalt_lcdfb_driver);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Yoichi Yuasa");
MODULE_DESCRIPTION("Cobalt server LCD frame buffer driver");
