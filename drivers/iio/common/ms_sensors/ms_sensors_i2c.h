<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Measurements Specialties common sensor driver
 *
 * Copyright (c) 2015 Measurement-Specialties
 */

#अगर_अघोषित _MS_SENSORS_I2C_H
#घोषणा _MS_SENSORS_I2C_H

#समावेश <linux/i2c.h>
#समावेश <linux/mutex.h>

#घोषणा MS_SENSORS_TP_PROM_WORDS_NB		8

/**
 * काष्ठा ms_ht_dev - Humidity/Temperature sensor device काष्ठाure
 * @client:	i2c client
 * @lock:	lock protecting the i2c conversion
 * @res_index:	index to selected sensor resolution
 */
काष्ठा ms_ht_dev अणु
	काष्ठा i2c_client *client;
	काष्ठा mutex lock;
	u8 res_index;
पूर्ण;

/**
 * काष्ठा ms_hw_data - Temperature/Pressure sensor hardware data
 * @prom_len:		number of words in the PROM
 * @max_res_index:	maximum sensor resolution index
 */
काष्ठा ms_tp_hw_data अणु
	u8 prom_len;
	u8 max_res_index;
पूर्ण;

/**
 * काष्ठा ms_tp_dev - Temperature/Pressure sensor device काष्ठाure
 * @client:	i2c client
 * @lock:	lock protecting the i2c conversion
 * @prom:	array of PROM coefficients used क्रम conversion. Added element
 *              क्रम CRC computation
 * @res_index:	index to selected sensor resolution
 */
काष्ठा ms_tp_dev अणु
	काष्ठा i2c_client *client;
	काष्ठा mutex lock;
	स्थिर काष्ठा ms_tp_hw_data *hw;
	u16 prom[MS_SENSORS_TP_PROM_WORDS_NB];
	u8 res_index;
पूर्ण;

पूर्णांक ms_sensors_reset(व्योम *cli, u8 cmd, अचिन्हित पूर्णांक delay);
पूर्णांक ms_sensors_पढ़ो_prom_word(व्योम *cli, पूर्णांक cmd, u16 *word);
पूर्णांक ms_sensors_convert_and_पढ़ो(व्योम *cli, u8 conv, u8 rd,
				अचिन्हित पूर्णांक delay, u32 *adc);
पूर्णांक ms_sensors_पढ़ो_serial(काष्ठा i2c_client *client, u64 *sn);
sमाप_प्रकार ms_sensors_show_serial(काष्ठा ms_ht_dev *dev_data, अक्षर *buf);
sमाप_प्रकार ms_sensors_ग_लिखो_resolution(काष्ठा ms_ht_dev *dev_data, u8 i);
sमाप_प्रकार ms_sensors_show_battery_low(काष्ठा ms_ht_dev *dev_data, अक्षर *buf);
sमाप_प्रकार ms_sensors_show_heater(काष्ठा ms_ht_dev *dev_data, अक्षर *buf);
sमाप_प्रकार ms_sensors_ग_लिखो_heater(काष्ठा ms_ht_dev *dev_data,
				स्थिर अक्षर *buf, माप_प्रकार len);
पूर्णांक ms_sensors_ht_पढ़ो_temperature(काष्ठा ms_ht_dev *dev_data,
				   s32 *temperature);
पूर्णांक ms_sensors_ht_पढ़ो_humidity(काष्ठा ms_ht_dev *dev_data,
				u32 *humidity);
पूर्णांक ms_sensors_tp_पढ़ो_prom(काष्ठा ms_tp_dev *dev_data);
पूर्णांक ms_sensors_पढ़ो_temp_and_pressure(काष्ठा ms_tp_dev *dev_data,
				      पूर्णांक *temperature,
				      अचिन्हित पूर्णांक *pressure);

#पूर्ण_अगर /* _MS_SENSORS_I2C_H */
