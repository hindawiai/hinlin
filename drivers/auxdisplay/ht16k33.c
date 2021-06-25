<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * HT16K33 driver
 *
 * Author: Robin van der Gracht <robin@protonic.nl>
 *
 * Copyright: (C) 2016 Protonic Holland.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/i2c.h>
#समावेश <linux/of.h>
#समावेश <linux/fb.h>
#समावेश <linux/slab.h>
#समावेश <linux/backlight.h>
#समावेश <linux/input.h>
#समावेश <linux/input/matrix_keypad.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/mm.h>

/* Registers */
#घोषणा REG_SYSTEM_SETUP		0x20
#घोषणा REG_SYSTEM_SETUP_OSC_ON		BIT(0)

#घोषणा REG_DISPLAY_SETUP		0x80
#घोषणा REG_DISPLAY_SETUP_ON		BIT(0)

#घोषणा REG_ROWINT_SET			0xA0
#घोषणा REG_ROWINT_SET_INT_EN		BIT(0)
#घोषणा REG_ROWINT_SET_INT_ACT_HIGH	BIT(1)

#घोषणा REG_BRIGHTNESS			0xE0

/* Defines */
#घोषणा DRIVER_NAME			"ht16k33"

#घोषणा MIN_BRIGHTNESS			0x1
#घोषणा MAX_BRIGHTNESS			0x10

#घोषणा HT16K33_MATRIX_LED_MAX_COLS	8
#घोषणा HT16K33_MATRIX_LED_MAX_ROWS	16
#घोषणा HT16K33_MATRIX_KEYPAD_MAX_COLS	3
#घोषणा HT16K33_MATRIX_KEYPAD_MAX_ROWS	12

#घोषणा BYTES_PER_ROW		(HT16K33_MATRIX_LED_MAX_ROWS / 8)
#घोषणा HT16K33_FB_SIZE		(HT16K33_MATRIX_LED_MAX_COLS * BYTES_PER_ROW)

काष्ठा ht16k33_keypad अणु
	काष्ठा i2c_client *client;
	काष्ठा input_dev *dev;
	uपूर्णांक32_t cols;
	uपूर्णांक32_t rows;
	uपूर्णांक32_t row_shअगरt;
	uपूर्णांक32_t debounce_ms;
	uपूर्णांक16_t last_key_state[HT16K33_MATRIX_KEYPAD_MAX_COLS];

	रुको_queue_head_t रुको;
	bool stopped;
पूर्ण;

काष्ठा ht16k33_fbdev अणु
	काष्ठा fb_info *info;
	uपूर्णांक32_t refresh_rate;
	uपूर्णांक8_t *buffer;
	uपूर्णांक8_t *cache;
	काष्ठा delayed_work work;
पूर्ण;

काष्ठा ht16k33_priv अणु
	काष्ठा i2c_client *client;
	काष्ठा ht16k33_keypad keypad;
	काष्ठा ht16k33_fbdev fbdev;
पूर्ण;

अटल स्थिर काष्ठा fb_fix_screeninfo ht16k33_fb_fix = अणु
	.id		= DRIVER_NAME,
	.type		= FB_TYPE_PACKED_PIXELS,
	.visual		= FB_VISUAL_MONO10,
	.xpanstep	= 0,
	.ypanstep	= 0,
	.ywrapstep	= 0,
	.line_length	= HT16K33_MATRIX_LED_MAX_ROWS,
	.accel		= FB_ACCEL_NONE,
पूर्ण;

अटल स्थिर काष्ठा fb_var_screeninfo ht16k33_fb_var = अणु
	.xres = HT16K33_MATRIX_LED_MAX_ROWS,
	.yres = HT16K33_MATRIX_LED_MAX_COLS,
	.xres_भव = HT16K33_MATRIX_LED_MAX_ROWS,
	.yres_भव = HT16K33_MATRIX_LED_MAX_COLS,
	.bits_per_pixel = 1,
	.red = अणु 0, 1, 0 पूर्ण,
	.green = अणु 0, 1, 0 पूर्ण,
	.blue = अणु 0, 1, 0 पूर्ण,
	.left_margin = 0,
	.right_margin = 0,
	.upper_margin = 0,
	.lower_margin = 0,
	.vmode = FB_VMODE_NONINTERLACED,
पूर्ण;

अटल पूर्णांक ht16k33_display_on(काष्ठा ht16k33_priv *priv)
अणु
	uपूर्णांक8_t data = REG_DISPLAY_SETUP | REG_DISPLAY_SETUP_ON;

	वापस i2c_smbus_ग_लिखो_byte(priv->client, data);
पूर्ण

अटल पूर्णांक ht16k33_display_off(काष्ठा ht16k33_priv *priv)
अणु
	वापस i2c_smbus_ग_लिखो_byte(priv->client, REG_DISPLAY_SETUP);
पूर्ण

अटल व्योम ht16k33_fb_queue(काष्ठा ht16k33_priv *priv)
अणु
	काष्ठा ht16k33_fbdev *fbdev = &priv->fbdev;

	schedule_delayed_work(&fbdev->work, HZ / fbdev->refresh_rate);
पूर्ण

/*
 * This माला_लो the fb data from cache and copies it to ht16k33 display RAM
 */
अटल व्योम ht16k33_fb_update(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ht16k33_fbdev *fbdev =
		container_of(work, काष्ठा ht16k33_fbdev, work.work);
	काष्ठा ht16k33_priv *priv =
		container_of(fbdev, काष्ठा ht16k33_priv, fbdev);

	uपूर्णांक8_t *p1, *p2;
	पूर्णांक len, pos = 0, first = -1;

	p1 = fbdev->cache;
	p2 = fbdev->buffer;

	/* Search क्रम the first byte with changes */
	जबतक (pos < HT16K33_FB_SIZE && first < 0) अणु
		अगर (*(p1++) - *(p2++))
			first = pos;
		pos++;
	पूर्ण

	/* No changes found */
	अगर (first < 0)
		जाओ requeue;

	len = HT16K33_FB_SIZE - first;
	p1 = fbdev->cache + HT16K33_FB_SIZE - 1;
	p2 = fbdev->buffer + HT16K33_FB_SIZE - 1;

	/* Determine i2c transfer length */
	जबतक (len > 1) अणु
		अगर (*(p1--) - *(p2--))
			अवरोध;
		len--;
	पूर्ण

	p1 = fbdev->cache + first;
	p2 = fbdev->buffer + first;
	अगर (!i2c_smbus_ग_लिखो_i2c_block_data(priv->client, first, len, p2))
		स_नकल(p1, p2, len);
requeue:
	ht16k33_fb_queue(priv);
पूर्ण

अटल पूर्णांक ht16k33_initialize(काष्ठा ht16k33_priv *priv)
अणु
	uपूर्णांक8_t byte;
	पूर्णांक err;
	uपूर्णांक8_t data[HT16K33_MATRIX_LED_MAX_COLS * 2];

	/* Clear RAM (8 * 16 bits) */
	स_रखो(data, 0, माप(data));
	err = i2c_smbus_ग_लिखो_block_data(priv->client, 0, माप(data), data);
	अगर (err)
		वापस err;

	/* Turn on पूर्णांकernal oscillator */
	byte = REG_SYSTEM_SETUP_OSC_ON | REG_SYSTEM_SETUP;
	err = i2c_smbus_ग_लिखो_byte(priv->client, byte);
	अगर (err)
		वापस err;

	/* Configure INT pin */
	byte = REG_ROWINT_SET | REG_ROWINT_SET_INT_ACT_HIGH;
	अगर (priv->client->irq > 0)
		byte |= REG_ROWINT_SET_INT_EN;
	वापस i2c_smbus_ग_लिखो_byte(priv->client, byte);
पूर्ण

अटल पूर्णांक ht16k33_bl_update_status(काष्ठा backlight_device *bl)
अणु
	पूर्णांक brightness = bl->props.brightness;
	काष्ठा ht16k33_priv *priv = bl_get_data(bl);

	अगर (bl->props.घातer != FB_BLANK_UNBLANK ||
	    bl->props.fb_blank != FB_BLANK_UNBLANK ||
	    bl->props.state & BL_CORE_FBBLANK || brightness == 0) अणु
		वापस ht16k33_display_off(priv);
	पूर्ण

	ht16k33_display_on(priv);
	वापस i2c_smbus_ग_लिखो_byte(priv->client,
				    REG_BRIGHTNESS | (brightness - 1));
पूर्ण

अटल पूर्णांक ht16k33_bl_check_fb(काष्ठा backlight_device *bl, काष्ठा fb_info *fi)
अणु
	काष्ठा ht16k33_priv *priv = bl_get_data(bl);

	वापस (fi == शून्य) || (fi->par == priv);
पूर्ण

अटल स्थिर काष्ठा backlight_ops ht16k33_bl_ops = अणु
	.update_status	= ht16k33_bl_update_status,
	.check_fb	= ht16k33_bl_check_fb,
पूर्ण;

अटल पूर्णांक ht16k33_mmap(काष्ठा fb_info *info, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा ht16k33_priv *priv = info->par;
	काष्ठा page *pages = virt_to_page(priv->fbdev.buffer);

	वापस vm_map_pages_zero(vma, &pages, 1);
पूर्ण

अटल स्थिर काष्ठा fb_ops ht16k33_fb_ops = अणु
	.owner = THIS_MODULE,
	.fb_पढ़ो = fb_sys_पढ़ो,
	.fb_ग_लिखो = fb_sys_ग_लिखो,
	.fb_fillrect = sys_fillrect,
	.fb_copyarea = sys_copyarea,
	.fb_imageblit = sys_imageblit,
	.fb_mmap = ht16k33_mmap,
पूर्ण;

/*
 * This माला_लो the keys from keypad and reports it to input subप्रणाली.
 * Returns true अगर a key is pressed.
 */
अटल bool ht16k33_keypad_scan(काष्ठा ht16k33_keypad *keypad)
अणु
	स्थिर अचिन्हित लघु *keycodes = keypad->dev->keycode;
	u16 new_state[HT16K33_MATRIX_KEYPAD_MAX_COLS];
	__le16 data[HT16K33_MATRIX_KEYPAD_MAX_COLS];
	अचिन्हित दीर्घ bits_changed;
	पूर्णांक row, col, code;
	पूर्णांक rc;
	bool pressed = false;

	rc = i2c_smbus_पढ़ो_i2c_block_data(keypad->client, 0x40,
					   माप(data), (u8 *)data);
	अगर (rc != माप(data)) अणु
		dev_err(&keypad->client->dev,
			"Failed to read key data, rc=%d\n", rc);
		वापस false;
	पूर्ण

	क्रम (col = 0; col < keypad->cols; col++) अणु
		new_state[col] = le16_to_cpu(data[col]);
		अगर (new_state[col])
			pressed = true;
		bits_changed = keypad->last_key_state[col] ^ new_state[col];

		क्रम_each_set_bit(row, &bits_changed, BITS_PER_LONG) अणु
			code = MATRIX_SCAN_CODE(row, col, keypad->row_shअगरt);
			input_event(keypad->dev, EV_MSC, MSC_SCAN, code);
			input_report_key(keypad->dev, keycodes[code],
					 new_state[col] & BIT(row));
		पूर्ण
	पूर्ण
	input_sync(keypad->dev);
	स_नकल(keypad->last_key_state, new_state, माप(u16) * keypad->cols);

	वापस pressed;
पूर्ण

अटल irqवापस_t ht16k33_keypad_irq_thपढ़ो(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा ht16k33_keypad *keypad = dev;

	करो अणु
		रुको_event_समयout(keypad->रुको, keypad->stopped,
				    msecs_to_jअगरfies(keypad->debounce_ms));
		अगर (keypad->stopped)
			अवरोध;
	पूर्ण जबतक (ht16k33_keypad_scan(keypad));

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक ht16k33_keypad_start(काष्ठा input_dev *dev)
अणु
	काष्ठा ht16k33_keypad *keypad = input_get_drvdata(dev);

	keypad->stopped = false;
	mb();
	enable_irq(keypad->client->irq);

	वापस 0;
पूर्ण

अटल व्योम ht16k33_keypad_stop(काष्ठा input_dev *dev)
अणु
	काष्ठा ht16k33_keypad *keypad = input_get_drvdata(dev);

	keypad->stopped = true;
	mb();
	wake_up(&keypad->रुको);
	disable_irq(keypad->client->irq);
पूर्ण

अटल पूर्णांक ht16k33_keypad_probe(काष्ठा i2c_client *client,
				काष्ठा ht16k33_keypad *keypad)
अणु
	काष्ठा device_node *node = client->dev.of_node;
	u32 rows = HT16K33_MATRIX_KEYPAD_MAX_ROWS;
	u32 cols = HT16K33_MATRIX_KEYPAD_MAX_COLS;
	पूर्णांक err;

	keypad->client = client;
	init_रुकोqueue_head(&keypad->रुको);

	keypad->dev = devm_input_allocate_device(&client->dev);
	अगर (!keypad->dev)
		वापस -ENOMEM;

	input_set_drvdata(keypad->dev, keypad);

	keypad->dev->name = DRIVER_NAME"-keypad";
	keypad->dev->id.bustype = BUS_I2C;
	keypad->dev->खोलो = ht16k33_keypad_start;
	keypad->dev->बंद = ht16k33_keypad_stop;

	अगर (!of_get_property(node, "linux,no-autorepeat", शून्य))
		__set_bit(EV_REP, keypad->dev->evbit);

	err = of_property_पढ़ो_u32(node, "debounce-delay-ms",
				   &keypad->debounce_ms);
	अगर (err) अणु
		dev_err(&client->dev, "key debounce delay not specified\n");
		वापस err;
	पूर्ण

	err = matrix_keypad_parse_of_params(&client->dev, &rows, &cols);
	अगर (err)
		वापस err;
	अगर (rows > HT16K33_MATRIX_KEYPAD_MAX_ROWS ||
	    cols > HT16K33_MATRIX_KEYPAD_MAX_COLS) अणु
		dev_err(&client->dev, "%u rows or %u cols out of range in DT\n",
			rows, cols);
		वापस -दुस्फल;
	पूर्ण

	keypad->rows = rows;
	keypad->cols = cols;
	keypad->row_shअगरt = get_count_order(cols);

	err = matrix_keypad_build_keymap(शून्य, शून्य, rows, cols, शून्य,
					 keypad->dev);
	अगर (err) अणु
		dev_err(&client->dev, "failed to build keymap\n");
		वापस err;
	पूर्ण

	err = devm_request_thपढ़ोed_irq(&client->dev, client->irq,
					शून्य, ht16k33_keypad_irq_thपढ़ो,
					IRQF_TRIGGER_HIGH | IRQF_ONESHOT,
					DRIVER_NAME, keypad);
	अगर (err) अणु
		dev_err(&client->dev, "irq request failed %d, error %d\n",
			client->irq, err);
		वापस err;
	पूर्ण

	ht16k33_keypad_stop(keypad->dev);

	err = input_रेजिस्टर_device(keypad->dev);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक ht16k33_probe(काष्ठा i2c_client *client,
				  स्थिर काष्ठा i2c_device_id *id)
अणु
	पूर्णांक err;
	uपूर्णांक32_t dft_brightness;
	काष्ठा backlight_device *bl;
	काष्ठा backlight_properties bl_props;
	काष्ठा ht16k33_priv *priv;
	काष्ठा ht16k33_fbdev *fbdev;
	काष्ठा device_node *node = client->dev.of_node;

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) अणु
		dev_err(&client->dev, "i2c_check_functionality error\n");
		वापस -EIO;
	पूर्ण

	priv = devm_kzalloc(&client->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->client = client;
	i2c_set_clientdata(client, priv);
	fbdev = &priv->fbdev;

	err = ht16k33_initialize(priv);
	अगर (err)
		वापस err;

	/* Framebuffer (2 bytes per column) */
	BUILD_BUG_ON(PAGE_SIZE < HT16K33_FB_SIZE);
	fbdev->buffer = (अचिन्हित अक्षर *) get_zeroed_page(GFP_KERNEL);
	अगर (!fbdev->buffer)
		वापस -ENOMEM;

	fbdev->cache = devm_kदो_स्मृति(&client->dev, HT16K33_FB_SIZE, GFP_KERNEL);
	अगर (!fbdev->cache) अणु
		err = -ENOMEM;
		जाओ err_fbdev_buffer;
	पूर्ण

	fbdev->info = framebuffer_alloc(0, &client->dev);
	अगर (!fbdev->info) अणु
		err = -ENOMEM;
		जाओ err_fbdev_buffer;
	पूर्ण

	err = of_property_पढ़ो_u32(node, "refresh-rate-hz",
		&fbdev->refresh_rate);
	अगर (err) अणु
		dev_err(&client->dev, "refresh rate not specified\n");
		जाओ err_fbdev_info;
	पूर्ण
	fb_bl_शेष_curve(fbdev->info, 0, MIN_BRIGHTNESS, MAX_BRIGHTNESS);

	INIT_DELAYED_WORK(&fbdev->work, ht16k33_fb_update);
	fbdev->info->fbops = &ht16k33_fb_ops;
	fbdev->info->screen_base = (अक्षर __iomem *) fbdev->buffer;
	fbdev->info->screen_size = HT16K33_FB_SIZE;
	fbdev->info->fix = ht16k33_fb_fix;
	fbdev->info->var = ht16k33_fb_var;
	fbdev->info->pseuकरो_palette = शून्य;
	fbdev->info->flags = FBINFO_FLAG_DEFAULT;
	fbdev->info->par = priv;

	err = रेजिस्टर_framebuffer(fbdev->info);
	अगर (err)
		जाओ err_fbdev_info;

	/* Keypad */
	अगर (client->irq > 0) अणु
		err = ht16k33_keypad_probe(client, &priv->keypad);
		अगर (err)
			जाओ err_fbdev_unरेजिस्टर;
	पूर्ण

	/* Backlight */
	स_रखो(&bl_props, 0, माप(काष्ठा backlight_properties));
	bl_props.type = BACKLIGHT_RAW;
	bl_props.max_brightness = MAX_BRIGHTNESS;

	bl = devm_backlight_device_रेजिस्टर(&client->dev, DRIVER_NAME"-bl",
					    &client->dev, priv,
					    &ht16k33_bl_ops, &bl_props);
	अगर (IS_ERR(bl)) अणु
		dev_err(&client->dev, "failed to register backlight\n");
		err = PTR_ERR(bl);
		जाओ err_fbdev_unरेजिस्टर;
	पूर्ण

	err = of_property_पढ़ो_u32(node, "default-brightness-level",
				   &dft_brightness);
	अगर (err) अणु
		dft_brightness = MAX_BRIGHTNESS;
	पूर्ण अन्यथा अगर (dft_brightness > MAX_BRIGHTNESS) अणु
		dev_warn(&client->dev,
			 "invalid default brightness level: %u, using %u\n",
			 dft_brightness, MAX_BRIGHTNESS);
		dft_brightness = MAX_BRIGHTNESS;
	पूर्ण

	bl->props.brightness = dft_brightness;
	ht16k33_bl_update_status(bl);

	ht16k33_fb_queue(priv);
	वापस 0;

err_fbdev_unरेजिस्टर:
	unरेजिस्टर_framebuffer(fbdev->info);
err_fbdev_info:
	framebuffer_release(fbdev->info);
err_fbdev_buffer:
	मुक्त_page((अचिन्हित दीर्घ) fbdev->buffer);

	वापस err;
पूर्ण

अटल पूर्णांक ht16k33_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा ht16k33_priv *priv = i2c_get_clientdata(client);
	काष्ठा ht16k33_fbdev *fbdev = &priv->fbdev;

	cancel_delayed_work_sync(&fbdev->work);
	unरेजिस्टर_framebuffer(fbdev->info);
	framebuffer_release(fbdev->info);
	मुक्त_page((अचिन्हित दीर्घ) fbdev->buffer);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ht16k33_i2c_match[] = अणु
	अणु "ht16k33", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ht16k33_i2c_match);

अटल स्थिर काष्ठा of_device_id ht16k33_of_match[] = अणु
	अणु .compatible = "holtek,ht16k33", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ht16k33_of_match);

अटल काष्ठा i2c_driver ht16k33_driver = अणु
	.probe		= ht16k33_probe,
	.हटाओ		= ht16k33_हटाओ,
	.driver		= अणु
		.name		= DRIVER_NAME,
		.of_match_table	= of_match_ptr(ht16k33_of_match),
	पूर्ण,
	.id_table = ht16k33_i2c_match,
पूर्ण;
module_i2c_driver(ht16k33_driver);

MODULE_DESCRIPTION("Holtek HT16K33 driver");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Robin van der Gracht <robin@protonic.nl>");
