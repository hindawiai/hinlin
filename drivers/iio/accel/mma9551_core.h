<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Common code क्रम Freescale MMA955x Intelligent Sensor Platक्रमm drivers
 * Copyright (c) 2014, Intel Corporation.
 */

#अगर_अघोषित _MMA9551_CORE_H_
#घोषणा _MMA9551_CORE_H_

/* Applications IDs */
#घोषणा MMA9551_APPID_VERSION		0x00
#घोषणा MMA9551_APPID_GPIO		0x03
#घोषणा MMA9551_APPID_AFE		0x06
#घोषणा MMA9551_APPID_TILT		0x0B
#घोषणा MMA9551_APPID_SLEEP_WAKE	0x12
#घोषणा MMA9551_APPID_Pगलत_तर्कETER	        0x15
#घोषणा MMA9551_APPID_RSC		0x17
#घोषणा MMA9551_APPID_NONE		0xff

/* Reset/Suspend/Clear application app masks */
#घोषणा MMA9551_RSC_PED			BIT(21)

#घोषणा MMA9551_AUTO_SUSPEND_DELAY_MS	2000

क्रमागत mma9551_gpio_pin अणु
	mma9551_gpio6 = 0,
	mma9551_gpio7,
	mma9551_gpio8,
	mma9551_gpio9,
	mma9551_gpio_max = mma9551_gpio9,
पूर्ण;

#घोषणा MMA9551_ACCEL_CHANNEL(axis) अणु				\
	.type = IIO_ACCEL,					\
	.modअगरied = 1,						\
	.channel2 = axis,					\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),		\
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE),	\
पूर्ण

पूर्णांक mma9551_पढ़ो_config_byte(काष्ठा i2c_client *client, u8 app_id,
			     u16 reg, u8 *val);
पूर्णांक mma9551_ग_लिखो_config_byte(काष्ठा i2c_client *client, u8 app_id,
			      u16 reg, u8 val);
पूर्णांक mma9551_पढ़ो_status_byte(काष्ठा i2c_client *client, u8 app_id,
			     u16 reg, u8 *val);
पूर्णांक mma9551_पढ़ो_config_word(काष्ठा i2c_client *client, u8 app_id,
			     u16 reg, u16 *val);
पूर्णांक mma9551_ग_लिखो_config_word(काष्ठा i2c_client *client, u8 app_id,
			      u16 reg, u16 val);
पूर्णांक mma9551_पढ़ो_status_word(काष्ठा i2c_client *client, u8 app_id,
			     u16 reg, u16 *val);
पूर्णांक mma9551_पढ़ो_config_words(काष्ठा i2c_client *client, u8 app_id,
			      u16 reg, u8 len, u16 *buf);
पूर्णांक mma9551_पढ़ो_status_words(काष्ठा i2c_client *client, u8 app_id,
			      u16 reg, u8 len, u16 *buf);
पूर्णांक mma9551_ग_लिखो_config_words(काष्ठा i2c_client *client, u8 app_id,
			       u16 reg, u8 len, u16 *buf);
पूर्णांक mma9551_update_config_bits(काष्ठा i2c_client *client, u8 app_id,
			       u16 reg, u8 mask, u8 val);
पूर्णांक mma9551_gpio_config(काष्ठा i2c_client *client, क्रमागत mma9551_gpio_pin pin,
			u8 app_id, u8 bitnum, पूर्णांक polarity);
पूर्णांक mma9551_पढ़ो_version(काष्ठा i2c_client *client);
पूर्णांक mma9551_set_device_state(काष्ठा i2c_client *client, bool enable);
पूर्णांक mma9551_set_घातer_state(काष्ठा i2c_client *client, bool on);
व्योम mma9551_sleep(पूर्णांक freq);
पूर्णांक mma9551_पढ़ो_accel_chan(काष्ठा i2c_client *client,
			    स्थिर काष्ठा iio_chan_spec *chan,
			    पूर्णांक *val, पूर्णांक *val2);
पूर्णांक mma9551_पढ़ो_accel_scale(पूर्णांक *val, पूर्णांक *val2);
पूर्णांक mma9551_app_reset(काष्ठा i2c_client *client, u32 app_mask);

#पूर्ण_अगर /* _MMA9551_CORE_H_ */
