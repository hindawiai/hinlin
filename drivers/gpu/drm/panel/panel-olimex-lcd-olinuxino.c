<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * LCD-OLinuXino support क्रम panel driver
 *
 * Copyright (C) 2018 Olimex Ltd.
 *   Author: Stefan Mavrodiev <stefan@olimex.com>
 */

#समावेश <linux/crc32.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of.h>
#समावेश <linux/regulator/consumer.h>

#समावेश <video/videomode.h>
#समावेश <video/display_timing.h>

#समावेश <drm/drm_device.h>
#समावेश <drm/drm_modes.h>
#समावेश <drm/drm_panel.h>

#घोषणा LCD_OLINUXINO_HEADER_MAGIC	0x4F4CB727
#घोषणा LCD_OLINUXINO_DATA_LEN		256

काष्ठा lcd_olinuxino_mode अणु
	u32 pixelघड़ी;
	u32 hactive;
	u32 hfp;
	u32 hbp;
	u32 hpw;
	u32 vactive;
	u32 vfp;
	u32 vbp;
	u32 vpw;
	u32 refresh;
	u32 flags;
पूर्ण;

काष्ठा lcd_olinuxino_info अणु
	अक्षर name[32];
	u32 width_mm;
	u32 height_mm;
	u32 bpc;
	u32 bus_क्रमmat;
	u32 bus_flag;
पूर्ण __attribute__((__packed__));

काष्ठा lcd_olinuxino_eeprom अणु
	u32 header;
	u32 id;
	अक्षर revision[4];
	u32 serial;
	काष्ठा lcd_olinuxino_info info;
	u32 num_modes;
	u8 reserved[180];
	u32 checksum;
पूर्ण __attribute__((__packed__));

काष्ठा lcd_olinuxino अणु
	काष्ठा drm_panel panel;
	काष्ठा device *dev;
	काष्ठा i2c_client *client;
	काष्ठा mutex mutex;

	bool prepared;
	bool enabled;

	काष्ठा regulator *supply;
	काष्ठा gpio_desc *enable_gpio;

	काष्ठा lcd_olinuxino_eeprom eeprom;
पूर्ण;

अटल अंतरभूत काष्ठा lcd_olinuxino *to_lcd_olinuxino(काष्ठा drm_panel *panel)
अणु
	वापस container_of(panel, काष्ठा lcd_olinuxino, panel);
पूर्ण

अटल पूर्णांक lcd_olinuxino_disable(काष्ठा drm_panel *panel)
अणु
	काष्ठा lcd_olinuxino *lcd = to_lcd_olinuxino(panel);

	अगर (!lcd->enabled)
		वापस 0;

	lcd->enabled = false;

	वापस 0;
पूर्ण

अटल पूर्णांक lcd_olinuxino_unprepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा lcd_olinuxino *lcd = to_lcd_olinuxino(panel);

	अगर (!lcd->prepared)
		वापस 0;

	gpiod_set_value_cansleep(lcd->enable_gpio, 0);
	regulator_disable(lcd->supply);

	lcd->prepared = false;

	वापस 0;
पूर्ण

अटल पूर्णांक lcd_olinuxino_prepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा lcd_olinuxino *lcd = to_lcd_olinuxino(panel);
	पूर्णांक ret;

	अगर (lcd->prepared)
		वापस 0;

	ret = regulator_enable(lcd->supply);
	अगर (ret < 0)
		वापस ret;

	gpiod_set_value_cansleep(lcd->enable_gpio, 1);
	lcd->prepared = true;

	वापस 0;
पूर्ण

अटल पूर्णांक lcd_olinuxino_enable(काष्ठा drm_panel *panel)
अणु
	काष्ठा lcd_olinuxino *lcd = to_lcd_olinuxino(panel);

	अगर (lcd->enabled)
		वापस 0;

	lcd->enabled = true;

	वापस 0;
पूर्ण

अटल पूर्णांक lcd_olinuxino_get_modes(काष्ठा drm_panel *panel,
				   काष्ठा drm_connector *connector)
अणु
	काष्ठा lcd_olinuxino *lcd = to_lcd_olinuxino(panel);
	काष्ठा lcd_olinuxino_info *lcd_info = &lcd->eeprom.info;
	काष्ठा lcd_olinuxino_mode *lcd_mode;
	काष्ठा drm_display_mode *mode;
	u32 i, num = 0;

	क्रम (i = 0; i < lcd->eeprom.num_modes; i++) अणु
		lcd_mode = (काष्ठा lcd_olinuxino_mode *)
			   &lcd->eeprom.reserved[i * माप(*lcd_mode)];

		mode = drm_mode_create(connector->dev);
		अगर (!mode) अणु
			dev_err(panel->dev, "failed to add mode %ux%u@%u\n",
				lcd_mode->hactive,
				lcd_mode->vactive,
				lcd_mode->refresh);
			जारी;
		पूर्ण

		mode->घड़ी = lcd_mode->pixelघड़ी;
		mode->hdisplay = lcd_mode->hactive;
		mode->hsync_start = lcd_mode->hactive + lcd_mode->hfp;
		mode->hsync_end = lcd_mode->hactive + lcd_mode->hfp +
				  lcd_mode->hpw;
		mode->htotal = lcd_mode->hactive + lcd_mode->hfp +
			       lcd_mode->hpw + lcd_mode->hbp;
		mode->vdisplay = lcd_mode->vactive;
		mode->vsync_start = lcd_mode->vactive + lcd_mode->vfp;
		mode->vsync_end = lcd_mode->vactive + lcd_mode->vfp +
				  lcd_mode->vpw;
		mode->vtotal = lcd_mode->vactive + lcd_mode->vfp +
			       lcd_mode->vpw + lcd_mode->vbp;

		/* Always make the first mode preferred */
		अगर (i == 0)
			mode->type |= DRM_MODE_TYPE_PREFERRED;
		mode->type |= DRM_MODE_TYPE_DRIVER;

		drm_mode_set_name(mode);
		drm_mode_probed_add(connector, mode);

		num++;
	पूर्ण

	connector->display_info.width_mm = lcd_info->width_mm;
	connector->display_info.height_mm = lcd_info->height_mm;
	connector->display_info.bpc = lcd_info->bpc;

	अगर (lcd_info->bus_क्रमmat)
		drm_display_info_set_bus_क्रमmats(&connector->display_info,
						 &lcd_info->bus_क्रमmat, 1);
	connector->display_info.bus_flags = lcd_info->bus_flag;

	वापस num;
पूर्ण

अटल स्थिर काष्ठा drm_panel_funcs lcd_olinuxino_funcs = अणु
	.disable = lcd_olinuxino_disable,
	.unprepare = lcd_olinuxino_unprepare,
	.prepare = lcd_olinuxino_prepare,
	.enable = lcd_olinuxino_enable,
	.get_modes = lcd_olinuxino_get_modes,
पूर्ण;

अटल पूर्णांक lcd_olinuxino_probe(काष्ठा i2c_client *client,
			       स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा lcd_olinuxino *lcd;
	u32 checksum, i;
	पूर्णांक ret = 0;

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C |
				     I2C_FUNC_SMBUS_READ_I2C_BLOCK))
		वापस -ENODEV;

	lcd = devm_kzalloc(dev, माप(*lcd), GFP_KERNEL);
	अगर (!lcd)
		वापस -ENOMEM;

	i2c_set_clientdata(client, lcd);
	lcd->dev = dev;
	lcd->client = client;

	mutex_init(&lcd->mutex);

	/* Copy data पूर्णांकo buffer */
	क्रम (i = 0; i < LCD_OLINUXINO_DATA_LEN; i += I2C_SMBUS_BLOCK_MAX) अणु
		mutex_lock(&lcd->mutex);
		ret = i2c_smbus_पढ़ो_i2c_block_data(client,
						    i,
						    I2C_SMBUS_BLOCK_MAX,
						    (u8 *)&lcd->eeprom + i);
		mutex_unlock(&lcd->mutex);
		अगर (ret < 0) अणु
			dev_err(dev, "error reading from device at %02x\n", i);
			वापस ret;
		पूर्ण
	पूर्ण

	/* Check configuration checksum */
	checksum = ~crc32(~0, (u8 *)&lcd->eeprom, 252);
	अगर (checksum != lcd->eeprom.checksum) अणु
		dev_err(dev, "configuration checksum does not match!\n");
		वापस -EINVAL;
	पूर्ण

	/* Check magic header */
	अगर (lcd->eeprom.header != LCD_OLINUXINO_HEADER_MAGIC) अणु
		dev_err(dev, "magic header does not match\n");
		वापस -EINVAL;
	पूर्ण

	dev_info(dev, "Detected %s, Rev. %s, Serial: %08x\n",
		 lcd->eeprom.info.name,
		 lcd->eeprom.revision,
		 lcd->eeprom.serial);

	/*
	 * The eeprom can hold up to 4 modes.
	 * If the stored value is bigger, overग_लिखो it.
	 */
	अगर (lcd->eeprom.num_modes > 4) अणु
		dev_warn(dev, "invalid number of modes, falling back to 4\n");
		lcd->eeprom.num_modes = 4;
	पूर्ण

	lcd->enabled = false;
	lcd->prepared = false;

	lcd->supply = devm_regulator_get(dev, "power");
	अगर (IS_ERR(lcd->supply))
		वापस PTR_ERR(lcd->supply);

	lcd->enable_gpio = devm_gpiod_get(dev, "enable", GPIOD_OUT_LOW);
	अगर (IS_ERR(lcd->enable_gpio))
		वापस PTR_ERR(lcd->enable_gpio);

	drm_panel_init(&lcd->panel, dev, &lcd_olinuxino_funcs,
		       DRM_MODE_CONNECTOR_DPI);

	ret = drm_panel_of_backlight(&lcd->panel);
	अगर (ret)
		वापस ret;

	drm_panel_add(&lcd->panel);

	वापस 0;
पूर्ण

अटल पूर्णांक lcd_olinuxino_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा lcd_olinuxino *panel = i2c_get_clientdata(client);

	drm_panel_हटाओ(&panel->panel);

	drm_panel_disable(&panel->panel);
	drm_panel_unprepare(&panel->panel);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id lcd_olinuxino_of_ids[] = अणु
	अणु .compatible = "olimex,lcd-olinuxino" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, lcd_olinuxino_of_ids);

अटल काष्ठा i2c_driver lcd_olinuxino_driver = अणु
	.driver = अणु
		.name = "lcd_olinuxino",
		.of_match_table = lcd_olinuxino_of_ids,
	पूर्ण,
	.probe = lcd_olinuxino_probe,
	.हटाओ = lcd_olinuxino_हटाओ,
पूर्ण;

module_i2c_driver(lcd_olinuxino_driver);

MODULE_AUTHOR("Stefan Mavrodiev <stefan@olimex.com>");
MODULE_DESCRIPTION("LCD-OLinuXino driver");
MODULE_LICENSE("GPL");
