<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * sht15.c - support क्रम the SHT15 Temperature and Humidity Sensor
 *
 * Portions Copyright (c) 2010-2012 Savoir-faire Linux Inc.
 *          Jerome Oufella <jerome.oufella@savoirfairelinux.com>
 *          Vivien Didelot <vivien.didelot@savoirfairelinux.com>
 *
 * Copyright (c) 2009 Jonathan Cameron
 *
 * Copyright (c) 2007 Wouter Horre
 *
 * For further inक्रमmation, see the Documentation/hwmon/sht15.rst file.
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/mutex.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/sched.h>
#समावेश <linux/delay.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/err.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>
#समावेश <linux/atomic.h>
#समावेश <linux/bitrev.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/of.h>

/* Commands */
#घोषणा SHT15_MEASURE_TEMP		0x03
#घोषणा SHT15_MEASURE_RH		0x05
#घोषणा SHT15_WRITE_STATUS		0x06
#घोषणा SHT15_READ_STATUS		0x07
#घोषणा SHT15_SOFT_RESET		0x1E

/* Min timings */
#घोषणा SHT15_TSCKL			100	/* (nsecs) घड़ी low */
#घोषणा SHT15_TSCKH			100	/* (nsecs) घड़ी high */
#घोषणा SHT15_TSU			150	/* (nsecs) data setup समय */
#घोषणा SHT15_TSRST			11	/* (msecs) soft reset समय */

/* Status Register Bits */
#घोषणा SHT15_STATUS_LOW_RESOLUTION	0x01
#घोषणा SHT15_STATUS_NO_OTP_RELOAD	0x02
#घोषणा SHT15_STATUS_HEATER		0x04
#घोषणा SHT15_STATUS_LOW_BATTERY	0x40

/* List of supported chips */
क्रमागत sht15_chips अणु sht10, sht11, sht15, sht71, sht75 पूर्ण;

/* Actions the driver may be करोing */
क्रमागत sht15_state अणु
	SHT15_READING_NOTHING,
	SHT15_READING_TEMP,
	SHT15_READING_HUMID
पूर्ण;

/**
 * काष्ठा sht15_temppair - elements of voltage dependent temp calc
 * @vdd:	supply voltage in microvolts
 * @d1:		see data sheet
 */
काष्ठा sht15_temppair अणु
	पूर्णांक vdd; /* microvolts */
	पूर्णांक d1;
पूर्ण;

/* Table 9 from datasheet - relates temperature calculation to supply voltage */
अटल स्थिर काष्ठा sht15_temppair temppoपूर्णांकs[] = अणु
	अणु 2500000, -39400 पूर्ण,
	अणु 3000000, -39600 पूर्ण,
	अणु 3500000, -39700 पूर्ण,
	अणु 4000000, -39800 पूर्ण,
	अणु 5000000, -40100 पूर्ण,
पूर्ण;

/* Table from CRC datasheet, section 2.4 */
अटल स्थिर u8 sht15_crc8_table[] = अणु
	0,	49,	98,	83,	196,	245,	166,	151,
	185,	136,	219,	234,	125,	76,	31,	46,
	67,	114,	33,	16,	135,	182,	229,	212,
	250,	203,	152,	169,	62,	15,	92,	109,
	134,	183,	228,	213,	66,	115,	32,	17,
	63,	14,	93,	108,	251,	202,	153,	168,
	197,	244,	167,	150,	1,	48,	99,	82,
	124,	77,	30,	47,	184,	137,	218,	235,
	61,	12,	95,	110,	249,	200,	155,	170,
	132,	181,	230,	215,	64,	113,	34,	19,
	126,	79,	28,	45,	186,	139,	216,	233,
	199,	246,	165,	148,	3,	50,	97,	80,
	187,	138,	217,	232,	127,	78,	29,	44,
	2,	51,	96,	81,	198,	247,	164,	149,
	248,	201,	154,	171,	60,	13,	94,	111,
	65,	112,	35,	18,	133,	180,	231,	214,
	122,	75,	24,	41,	190,	143,	220,	237,
	195,	242,	161,	144,	7,	54,	101,	84,
	57,	8,	91,	106,	253,	204,	159,	174,
	128,	177,	226,	211,	68,	117,	38,	23,
	252,	205,	158,	175,	56,	9,	90,	107,
	69,	116,	39,	22,	129,	176,	227,	210,
	191,	142,	221,	236,	123,	74,	25,	40,
	6,	55,	100,	85,	194,	243,	160,	145,
	71,	118,	37,	20,	131,	178,	225,	208,
	254,	207,	156,	173,	58,	11,	88,	105,
	4,	53,	102,	87,	192,	241,	162,	147,
	189,	140,	223,	238,	121,	72,	27,	42,
	193,	240,	163,	146,	5,	52,	103,	86,
	120,	73,	26,	43,	188,	141,	222,	239,
	130,	179,	224,	209,	70,	119,	36,	21,
	59,	10,	89,	104,	255,	206,	157,	172
पूर्ण;

/**
 * काष्ठा sht15_data - device instance specअगरic data
 * @sck:		घड़ी GPIO line
 * @data:		data GPIO line
 * @पढ़ो_work:		bh of पूर्णांकerrupt handler.
 * @रुको_queue:		रुको queue क्रम getting values from device.
 * @val_temp:		last temperature value पढ़ो from device.
 * @val_humid:		last humidity value पढ़ो from device.
 * @val_status:		last status रेजिस्टर value पढ़ो from device.
 * @checksum_ok:	last value पढ़ो from the device passed CRC validation.
 * @checksumming:	flag used to enable the data validation with CRC.
 * @state:		state identअगरying the action the driver is करोing.
 * @measurements_valid:	are the current stored measures valid (start condition).
 * @status_valid:	is the current stored status valid (start condition).
 * @last_measurement:	समय of last measure.
 * @last_status:	समय of last status पढ़ोing.
 * @पढ़ो_lock:		mutex to ensure only one पढ़ो in progress at a समय.
 * @dev:		associate device काष्ठाure.
 * @hwmon_dev:		device associated with hwmon subप्रणाली.
 * @reg:		associated regulator (अगर specअगरied).
 * @nb:			notअगरier block to handle notअगरications of voltage
 *                      changes.
 * @supply_uv:		local copy of supply voltage used to allow use of
 *                      regulator consumer अगर available.
 * @supply_uv_valid:	indicates that an updated value has not yet been
 *			obtained from the regulator and so any calculations
 *			based upon it will be invalid.
 * @update_supply_work:	work काष्ठा that is used to update the supply_uv.
 * @पूर्णांकerrupt_handled:	flag used to indicate a handler has been scheduled.
 */
काष्ठा sht15_data अणु
	काष्ठा gpio_desc		*sck;
	काष्ठा gpio_desc		*data;
	काष्ठा work_काष्ठा		पढ़ो_work;
	रुको_queue_head_t		रुको_queue;
	uपूर्णांक16_t			val_temp;
	uपूर्णांक16_t			val_humid;
	u8				val_status;
	bool				checksum_ok;
	bool				checksumming;
	क्रमागत sht15_state		state;
	bool				measurements_valid;
	bool				status_valid;
	अचिन्हित दीर्घ			last_measurement;
	अचिन्हित दीर्घ			last_status;
	काष्ठा mutex			पढ़ो_lock;
	काष्ठा device			*dev;
	काष्ठा device			*hwmon_dev;
	काष्ठा regulator		*reg;
	काष्ठा notअगरier_block		nb;
	पूर्णांक				supply_uv;
	bool				supply_uv_valid;
	काष्ठा work_काष्ठा		update_supply_work;
	atomic_t			पूर्णांकerrupt_handled;
पूर्ण;

/**
 * sht15_crc8() - compute crc8
 * @data:	sht15 specअगरic data.
 * @value:	sht15 retrieved data.
 * @len:	Length of retrieved data
 *
 * This implements section 2 of the CRC datasheet.
 */
अटल u8 sht15_crc8(काष्ठा sht15_data *data,
		स्थिर u8 *value,
		पूर्णांक len)
अणु
	u8 crc = bitrev8(data->val_status & 0x0F);

	जबतक (len--) अणु
		crc = sht15_crc8_table[*value ^ crc];
		value++;
	पूर्ण

	वापस crc;
पूर्ण

/**
 * sht15_connection_reset() - reset the comms पूर्णांकerface
 * @data:	sht15 specअगरic data
 *
 * This implements section 3.4 of the data sheet
 */
अटल पूर्णांक sht15_connection_reset(काष्ठा sht15_data *data)
अणु
	पूर्णांक i, err;

	err = gpiod_direction_output(data->data, 1);
	अगर (err)
		वापस err;
	ndelay(SHT15_TSCKL);
	gpiod_set_value(data->sck, 0);
	ndelay(SHT15_TSCKL);
	क्रम (i = 0; i < 9; ++i) अणु
		gpiod_set_value(data->sck, 1);
		ndelay(SHT15_TSCKH);
		gpiod_set_value(data->sck, 0);
		ndelay(SHT15_TSCKL);
	पूर्ण
	वापस 0;
पूर्ण

/**
 * sht15_send_bit() - send an inभागidual bit to the device
 * @data:	device state data
 * @val:	value of bit to be sent
 */
अटल अंतरभूत व्योम sht15_send_bit(काष्ठा sht15_data *data, पूर्णांक val)
अणु
	gpiod_set_value(data->data, val);
	ndelay(SHT15_TSU);
	gpiod_set_value(data->sck, 1);
	ndelay(SHT15_TSCKH);
	gpiod_set_value(data->sck, 0);
	ndelay(SHT15_TSCKL); /* घड़ी low समय */
पूर्ण

/**
 * sht15_transmission_start() - specअगरic sequence क्रम new transmission
 * @data:	device state data
 *
 * Timings क्रम this are not करोcumented on the data sheet, so very
 * conservative ones used in implementation. This implements
 * figure 12 on the data sheet.
 */
अटल पूर्णांक sht15_transmission_start(काष्ठा sht15_data *data)
अणु
	पूर्णांक err;

	/* ensure data is high and output */
	err = gpiod_direction_output(data->data, 1);
	अगर (err)
		वापस err;
	ndelay(SHT15_TSU);
	gpiod_set_value(data->sck, 0);
	ndelay(SHT15_TSCKL);
	gpiod_set_value(data->sck, 1);
	ndelay(SHT15_TSCKH);
	gpiod_set_value(data->data, 0);
	ndelay(SHT15_TSU);
	gpiod_set_value(data->sck, 0);
	ndelay(SHT15_TSCKL);
	gpiod_set_value(data->sck, 1);
	ndelay(SHT15_TSCKH);
	gpiod_set_value(data->data, 1);
	ndelay(SHT15_TSU);
	gpiod_set_value(data->sck, 0);
	ndelay(SHT15_TSCKL);
	वापस 0;
पूर्ण

/**
 * sht15_send_byte() - send a single byte to the device
 * @data:	device state
 * @byte:	value to be sent
 */
अटल व्योम sht15_send_byte(काष्ठा sht15_data *data, u8 byte)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 8; i++) अणु
		sht15_send_bit(data, !!(byte & 0x80));
		byte <<= 1;
	पूर्ण
पूर्ण

/**
 * sht15_रुको_क्रम_response() - checks क्रम ack from device
 * @data:	device state
 */
अटल पूर्णांक sht15_रुको_क्रम_response(काष्ठा sht15_data *data)
अणु
	पूर्णांक err;

	err = gpiod_direction_input(data->data);
	अगर (err)
		वापस err;
	gpiod_set_value(data->sck, 1);
	ndelay(SHT15_TSCKH);
	अगर (gpiod_get_value(data->data)) अणु
		gpiod_set_value(data->sck, 0);
		dev_err(data->dev, "Command not acknowledged\n");
		err = sht15_connection_reset(data);
		अगर (err)
			वापस err;
		वापस -EIO;
	पूर्ण
	gpiod_set_value(data->sck, 0);
	ndelay(SHT15_TSCKL);
	वापस 0;
पूर्ण

/**
 * sht15_send_cmd() - Sends a command to the device.
 * @data:	device state
 * @cmd:	command byte to be sent
 *
 * On entry, sck is output low, data is output pull high
 * and the पूर्णांकerrupt disabled.
 */
अटल पूर्णांक sht15_send_cmd(काष्ठा sht15_data *data, u8 cmd)
अणु
	पूर्णांक err;

	err = sht15_transmission_start(data);
	अगर (err)
		वापस err;
	sht15_send_byte(data, cmd);
	वापस sht15_रुको_क्रम_response(data);
पूर्ण

/**
 * sht15_soft_reset() - send a soft reset command
 * @data:	sht15 specअगरic data.
 *
 * As described in section 3.2 of the datasheet.
 */
अटल पूर्णांक sht15_soft_reset(काष्ठा sht15_data *data)
अणु
	पूर्णांक ret;

	ret = sht15_send_cmd(data, SHT15_SOFT_RESET);
	अगर (ret)
		वापस ret;
	msleep(SHT15_TSRST);
	/* device resets शेष hardware status रेजिस्टर value */
	data->val_status = 0;

	वापस ret;
पूर्ण

/**
 * sht15_ack() - send a ack
 * @data:	sht15 specअगरic data.
 *
 * Each byte of data is acknowledged by pulling the data line
 * low क्रम one घड़ी pulse.
 */
अटल पूर्णांक sht15_ack(काष्ठा sht15_data *data)
अणु
	पूर्णांक err;

	err = gpiod_direction_output(data->data, 0);
	अगर (err)
		वापस err;
	ndelay(SHT15_TSU);
	gpiod_set_value(data->sck, 1);
	ndelay(SHT15_TSU);
	gpiod_set_value(data->sck, 0);
	ndelay(SHT15_TSU);
	gpiod_set_value(data->data, 1);

	वापस gpiod_direction_input(data->data);
पूर्ण

/**
 * sht15_end_transmission() - notअगरy device of end of transmission
 * @data:	device state.
 *
 * This is basically a NAK (single घड़ी pulse, data high).
 */
अटल पूर्णांक sht15_end_transmission(काष्ठा sht15_data *data)
अणु
	पूर्णांक err;

	err = gpiod_direction_output(data->data, 1);
	अगर (err)
		वापस err;
	ndelay(SHT15_TSU);
	gpiod_set_value(data->sck, 1);
	ndelay(SHT15_TSCKH);
	gpiod_set_value(data->sck, 0);
	ndelay(SHT15_TSCKL);
	वापस 0;
पूर्ण

/**
 * sht15_पढ़ो_byte() - Read a byte back from the device
 * @data:	device state.
 */
अटल u8 sht15_पढ़ो_byte(काष्ठा sht15_data *data)
अणु
	पूर्णांक i;
	u8 byte = 0;

	क्रम (i = 0; i < 8; ++i) अणु
		byte <<= 1;
		gpiod_set_value(data->sck, 1);
		ndelay(SHT15_TSCKH);
		byte |= !!gpiod_get_value(data->data);
		gpiod_set_value(data->sck, 0);
		ndelay(SHT15_TSCKL);
	पूर्ण
	वापस byte;
पूर्ण

/**
 * sht15_send_status() - ग_लिखो the status रेजिस्टर byte
 * @data:	sht15 specअगरic data.
 * @status:	the byte to set the status रेजिस्टर with.
 *
 * As described in figure 14 and table 5 of the datasheet.
 */
अटल पूर्णांक sht15_send_status(काष्ठा sht15_data *data, u8 status)
अणु
	पूर्णांक err;

	err = sht15_send_cmd(data, SHT15_WRITE_STATUS);
	अगर (err)
		वापस err;
	err = gpiod_direction_output(data->data, 1);
	अगर (err)
		वापस err;
	ndelay(SHT15_TSU);
	sht15_send_byte(data, status);
	err = sht15_रुको_क्रम_response(data);
	अगर (err)
		वापस err;

	data->val_status = status;
	वापस 0;
पूर्ण

/**
 * sht15_update_status() - get updated status रेजिस्टर from device अगर too old
 * @data:	device instance specअगरic data.
 *
 * As described in figure 15 and table 5 of the datasheet.
 */
अटल पूर्णांक sht15_update_status(काष्ठा sht15_data *data)
अणु
	पूर्णांक ret = 0;
	u8 status;
	u8 previous_config;
	u8 dev_checksum = 0;
	u8 checksum_vals[2];
	पूर्णांक समयout = HZ;

	mutex_lock(&data->पढ़ो_lock);
	अगर (समय_after(jअगरfies, data->last_status + समयout)
			|| !data->status_valid) अणु
		ret = sht15_send_cmd(data, SHT15_READ_STATUS);
		अगर (ret)
			जाओ unlock;
		status = sht15_पढ़ो_byte(data);

		अगर (data->checksumming) अणु
			sht15_ack(data);
			dev_checksum = bitrev8(sht15_पढ़ो_byte(data));
			checksum_vals[0] = SHT15_READ_STATUS;
			checksum_vals[1] = status;
			data->checksum_ok = (sht15_crc8(data, checksum_vals, 2)
					== dev_checksum);
		पूर्ण

		ret = sht15_end_transmission(data);
		अगर (ret)
			जाओ unlock;

		/*
		 * Perक्रमm checksum validation on the received data.
		 * Specअगरication mentions that in हाल a checksum verअगरication
		 * fails, a soft reset command must be sent to the device.
		 */
		अगर (data->checksumming && !data->checksum_ok) अणु
			previous_config = data->val_status & 0x07;
			ret = sht15_soft_reset(data);
			अगर (ret)
				जाओ unlock;
			अगर (previous_config) अणु
				ret = sht15_send_status(data, previous_config);
				अगर (ret) अणु
					dev_err(data->dev,
						"CRC validation failed, unable "
						"to restore device settings\n");
					जाओ unlock;
				पूर्ण
			पूर्ण
			ret = -EAGAIN;
			जाओ unlock;
		पूर्ण

		data->val_status = status;
		data->status_valid = true;
		data->last_status = jअगरfies;
	पूर्ण

unlock:
	mutex_unlock(&data->पढ़ो_lock);
	वापस ret;
पूर्ण

/**
 * sht15_measurement() - get a new value from device
 * @data:		device instance specअगरic data
 * @command:		command sent to request value
 * @समयout_msecs:	समयout after which comms are assumed
 *			to have failed are reset.
 */
अटल पूर्णांक sht15_measurement(काष्ठा sht15_data *data,
			     पूर्णांक command,
			     पूर्णांक समयout_msecs)
अणु
	पूर्णांक ret;
	u8 previous_config;

	ret = sht15_send_cmd(data, command);
	अगर (ret)
		वापस ret;

	ret = gpiod_direction_input(data->data);
	अगर (ret)
		वापस ret;
	atomic_set(&data->पूर्णांकerrupt_handled, 0);

	enable_irq(gpiod_to_irq(data->data));
	अगर (gpiod_get_value(data->data) == 0) अणु
		disable_irq_nosync(gpiod_to_irq(data->data));
		/* Only relevant अगर the पूर्णांकerrupt hasn't occurred. */
		अगर (!atomic_पढ़ो(&data->पूर्णांकerrupt_handled))
			schedule_work(&data->पढ़ो_work);
	पूर्ण
	ret = रुको_event_समयout(data->रुको_queue,
				 (data->state == SHT15_READING_NOTHING),
				 msecs_to_jअगरfies(समयout_msecs));
	अगर (data->state != SHT15_READING_NOTHING) अणु /* I/O error occurred */
		data->state = SHT15_READING_NOTHING;
		वापस -EIO;
	पूर्ण अन्यथा अगर (ret == 0) अणु /* समयout occurred */
		disable_irq_nosync(gpiod_to_irq(data->data));
		ret = sht15_connection_reset(data);
		अगर (ret)
			वापस ret;
		वापस -ETIME;
	पूर्ण

	/*
	 *  Perक्रमm checksum validation on the received data.
	 *  Specअगरication mentions that in हाल a checksum verअगरication fails,
	 *  a soft reset command must be sent to the device.
	 */
	अगर (data->checksumming && !data->checksum_ok) अणु
		previous_config = data->val_status & 0x07;
		ret = sht15_soft_reset(data);
		अगर (ret)
			वापस ret;
		अगर (previous_config) अणु
			ret = sht15_send_status(data, previous_config);
			अगर (ret) अणु
				dev_err(data->dev,
					"CRC validation failed, unable "
					"to restore device settings\n");
				वापस ret;
			पूर्ण
		पूर्ण
		वापस -EAGAIN;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * sht15_update_measurements() - get updated measures from device अगर too old
 * @data:	device state
 */
अटल पूर्णांक sht15_update_measurements(काष्ठा sht15_data *data)
अणु
	पूर्णांक ret = 0;
	पूर्णांक समयout = HZ;

	mutex_lock(&data->पढ़ो_lock);
	अगर (समय_after(jअगरfies, data->last_measurement + समयout)
	    || !data->measurements_valid) अणु
		data->state = SHT15_READING_HUMID;
		ret = sht15_measurement(data, SHT15_MEASURE_RH, 160);
		अगर (ret)
			जाओ unlock;
		data->state = SHT15_READING_TEMP;
		ret = sht15_measurement(data, SHT15_MEASURE_TEMP, 400);
		अगर (ret)
			जाओ unlock;
		data->measurements_valid = true;
		data->last_measurement = jअगरfies;
	पूर्ण

unlock:
	mutex_unlock(&data->पढ़ो_lock);
	वापस ret;
पूर्ण

/**
 * sht15_calc_temp() - convert the raw पढ़ोing to a temperature
 * @data:	device state
 *
 * As per section 4.3 of the data sheet.
 */
अटल अंतरभूत पूर्णांक sht15_calc_temp(काष्ठा sht15_data *data)
अणु
	पूर्णांक d1 = temppoपूर्णांकs[0].d1;
	पूर्णांक d2 = (data->val_status & SHT15_STATUS_LOW_RESOLUTION) ? 40 : 10;
	पूर्णांक i;

	क्रम (i = ARRAY_SIZE(temppoपूर्णांकs) - 1; i > 0; i--)
		/* Find poपूर्णांकer to पूर्णांकerpolate */
		अगर (data->supply_uv > temppoपूर्णांकs[i - 1].vdd) अणु
			d1 = (data->supply_uv - temppoपूर्णांकs[i - 1].vdd)
				* (temppoपूर्णांकs[i].d1 - temppoपूर्णांकs[i - 1].d1)
				/ (temppoपूर्णांकs[i].vdd - temppoपूर्णांकs[i - 1].vdd)
				+ temppoपूर्णांकs[i - 1].d1;
			अवरोध;
		पूर्ण

	वापस data->val_temp * d2 + d1;
पूर्ण

/**
 * sht15_calc_humid() - using last temperature convert raw to humid
 * @data:	device state
 *
 * This is the temperature compensated version as per section 4.2 of
 * the data sheet.
 *
 * The sensor is assumed to be V3, which is compatible with V4.
 * Humidity conversion coefficients are shown in table 7 of the datasheet.
 */
अटल अंतरभूत पूर्णांक sht15_calc_humid(काष्ठा sht15_data *data)
अणु
	पूर्णांक rh_linear; /* milli percent */
	पूर्णांक temp = sht15_calc_temp(data);
	पूर्णांक c2, c3;
	पूर्णांक t2;
	स्थिर पूर्णांक c1 = -4;

	अगर (data->val_status & SHT15_STATUS_LOW_RESOLUTION) अणु
		c2 = 648000; /* x 10 ^ -6 */
		c3 = -7200;  /* x 10 ^ -7 */
		t2 = 1280;
	पूर्ण अन्यथा अणु
		c2 = 40500;  /* x 10 ^ -6 */
		c3 = -28;    /* x 10 ^ -7 */
		t2 = 80;
	पूर्ण

	rh_linear = c1 * 1000
		+ c2 * data->val_humid / 1000
		+ (data->val_humid * data->val_humid * c3) / 10000;
	वापस (temp - 25000) * (10000 + t2 * data->val_humid)
		/ 1000000 + rh_linear;
पूर्ण

/**
 * sht15_show_status() - show status inक्रमmation in sysfs
 * @dev:	device.
 * @attr:	device attribute.
 * @buf:	sysfs buffer where inक्रमmation is written to.
 *
 * Will be called on पढ़ो access to temp1_fault, humidity1_fault
 * and heater_enable sysfs attributes.
 * Returns number of bytes written पूर्णांकo buffer, negative त्रुटि_सं on error.
 */
अटल sमाप_प्रकार sht15_status_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक ret;
	काष्ठा sht15_data *data = dev_get_drvdata(dev);
	u8 bit = to_sensor_dev_attr(attr)->index;

	ret = sht15_update_status(data);

	वापस ret ? ret : प्र_लिखो(buf, "%d\n", !!(data->val_status & bit));
पूर्ण

/**
 * sht15_store_heater() - change heater state via sysfs
 * @dev:	device.
 * @attr:	device attribute.
 * @buf:	sysfs buffer to पढ़ो the new heater state from.
 * @count:	length of the data.
 *
 * Will be called on ग_लिखो access to heater_enable sysfs attribute.
 * Returns number of bytes actually decoded, negative त्रुटि_सं on error.
 */
अटल sमाप_प्रकार sht15_status_store(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक ret;
	काष्ठा sht15_data *data = dev_get_drvdata(dev);
	दीर्घ value;
	u8 status;

	अगर (kम_से_दीर्घ(buf, 10, &value))
		वापस -EINVAL;

	mutex_lock(&data->पढ़ो_lock);
	status = data->val_status & 0x07;
	अगर (!!value)
		status |= SHT15_STATUS_HEATER;
	अन्यथा
		status &= ~SHT15_STATUS_HEATER;

	ret = sht15_send_status(data, status);
	mutex_unlock(&data->पढ़ो_lock);

	वापस ret ? ret : count;
पूर्ण

/**
 * sht15_show_temp() - show temperature measurement value in sysfs
 * @dev:	device.
 * @attr:	device attribute.
 * @buf:	sysfs buffer where measurement values are written to.
 *
 * Will be called on पढ़ो access to temp1_input sysfs attribute.
 * Returns number of bytes written पूर्णांकo buffer, negative त्रुटि_सं on error.
 */
अटल sमाप_प्रकार sht15_temp_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक ret;
	काष्ठा sht15_data *data = dev_get_drvdata(dev);

	/* Technically no need to पढ़ो humidity as well */
	ret = sht15_update_measurements(data);

	वापस ret ? ret : प्र_लिखो(buf, "%d\n",
				   sht15_calc_temp(data));
पूर्ण

/**
 * sht15_show_humidity() - show humidity measurement value in sysfs
 * @dev:	device.
 * @attr:	device attribute.
 * @buf:	sysfs buffer where measurement values are written to.
 *
 * Will be called on पढ़ो access to humidity1_input sysfs attribute.
 * Returns number of bytes written पूर्णांकo buffer, negative त्रुटि_सं on error.
 */
अटल sमाप_प्रकार sht15_humidity_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक ret;
	काष्ठा sht15_data *data = dev_get_drvdata(dev);

	ret = sht15_update_measurements(data);

	वापस ret ? ret : प्र_लिखो(buf, "%d\n", sht15_calc_humid(data));
पूर्ण

अटल sमाप_प्रकार name_show(काष्ठा device *dev,
			 काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	वापस प्र_लिखो(buf, "%s\n", pdev->name);
पूर्ण

अटल SENSOR_DEVICE_ATTR_RO(temp1_input, sht15_temp, 0);
अटल SENSOR_DEVICE_ATTR_RO(humidity1_input, sht15_humidity, 0);
अटल SENSOR_DEVICE_ATTR_RO(temp1_fault, sht15_status,
			     SHT15_STATUS_LOW_BATTERY);
अटल SENSOR_DEVICE_ATTR_RO(humidity1_fault, sht15_status,
			     SHT15_STATUS_LOW_BATTERY);
अटल SENSOR_DEVICE_ATTR_RW(heater_enable, sht15_status, SHT15_STATUS_HEATER);
अटल DEVICE_ATTR_RO(name);
अटल काष्ठा attribute *sht15_attrs[] = अणु
	&sensor_dev_attr_temp1_input.dev_attr.attr,
	&sensor_dev_attr_humidity1_input.dev_attr.attr,
	&sensor_dev_attr_temp1_fault.dev_attr.attr,
	&sensor_dev_attr_humidity1_fault.dev_attr.attr,
	&sensor_dev_attr_heater_enable.dev_attr.attr,
	&dev_attr_name.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group sht15_attr_group = अणु
	.attrs = sht15_attrs,
पूर्ण;

अटल irqवापस_t sht15_पूर्णांकerrupt_fired(पूर्णांक irq, व्योम *d)
अणु
	काष्ठा sht15_data *data = d;

	/* First disable the पूर्णांकerrupt */
	disable_irq_nosync(irq);
	atomic_inc(&data->पूर्णांकerrupt_handled);
	/* Then schedule a पढ़ोing work काष्ठा */
	अगर (data->state != SHT15_READING_NOTHING)
		schedule_work(&data->पढ़ो_work);
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम sht15_bh_पढ़ो_data(काष्ठा work_काष्ठा *work_s)
अणु
	uपूर्णांक16_t val = 0;
	u8 dev_checksum = 0;
	u8 checksum_vals[3];
	काष्ठा sht15_data *data
		= container_of(work_s, काष्ठा sht15_data,
			       पढ़ो_work);

	/* Firstly, verअगरy the line is low */
	अगर (gpiod_get_value(data->data)) अणु
		/*
		 * If not, then start the पूर्णांकerrupt again - care here as could
		 * have gone low in meanसमय so verअगरy it hasn't!
		 */
		atomic_set(&data->पूर्णांकerrupt_handled, 0);
		enable_irq(gpiod_to_irq(data->data));
		/* If still not occurred or another handler was scheduled */
		अगर (gpiod_get_value(data->data)
		    || atomic_पढ़ो(&data->पूर्णांकerrupt_handled))
			वापस;
	पूर्ण

	/* Read the data back from the device */
	val = sht15_पढ़ो_byte(data);
	val <<= 8;
	अगर (sht15_ack(data))
		जाओ wakeup;
	val |= sht15_पढ़ो_byte(data);

	अगर (data->checksumming) अणु
		/*
		 * Ask the device क्रम a checksum and पढ़ो it back.
		 * Note: the device sends the checksum byte reversed.
		 */
		अगर (sht15_ack(data))
			जाओ wakeup;
		dev_checksum = bitrev8(sht15_पढ़ो_byte(data));
		checksum_vals[0] = (data->state == SHT15_READING_TEMP) ?
			SHT15_MEASURE_TEMP : SHT15_MEASURE_RH;
		checksum_vals[1] = (u8) (val >> 8);
		checksum_vals[2] = (u8) val;
		data->checksum_ok
			= (sht15_crc8(data, checksum_vals, 3) == dev_checksum);
	पूर्ण

	/* Tell the device we are करोne */
	अगर (sht15_end_transmission(data))
		जाओ wakeup;

	चयन (data->state) अणु
	हाल SHT15_READING_TEMP:
		data->val_temp = val;
		अवरोध;
	हाल SHT15_READING_HUMID:
		data->val_humid = val;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	data->state = SHT15_READING_NOTHING;
wakeup:
	wake_up(&data->रुको_queue);
पूर्ण

अटल व्योम sht15_update_voltage(काष्ठा work_काष्ठा *work_s)
अणु
	काष्ठा sht15_data *data
		= container_of(work_s, काष्ठा sht15_data,
			       update_supply_work);
	data->supply_uv = regulator_get_voltage(data->reg);
पूर्ण

/**
 * sht15_invalidate_voltage() - mark supply voltage invalid when notअगरied by reg
 * @nb:		associated notअगरication काष्ठाure
 * @event:	voltage regulator state change event code
 * @ignored:	function parameter - ignored here
 *
 * Note that as the notअगरication code holds the regulator lock, we have
 * to schedule an update of the supply voltage rather than getting it directly.
 */
अटल पूर्णांक sht15_invalidate_voltage(काष्ठा notअगरier_block *nb,
				    अचिन्हित दीर्घ event,
				    व्योम *ignored)
अणु
	काष्ठा sht15_data *data = container_of(nb, काष्ठा sht15_data, nb);

	अगर (event == REGULATOR_EVENT_VOLTAGE_CHANGE)
		data->supply_uv_valid = false;
	schedule_work(&data->update_supply_work);

	वापस NOTIFY_OK;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id sht15_dt_match[] = अणु
	अणु .compatible = "sensirion,sht15" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sht15_dt_match);
#पूर्ण_अगर

अटल पूर्णांक sht15_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;
	काष्ठा sht15_data *data;

	data = devm_kzalloc(&pdev->dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	INIT_WORK(&data->पढ़ो_work, sht15_bh_पढ़ो_data);
	INIT_WORK(&data->update_supply_work, sht15_update_voltage);
	platक्रमm_set_drvdata(pdev, data);
	mutex_init(&data->पढ़ो_lock);
	data->dev = &pdev->dev;
	init_रुकोqueue_head(&data->रुको_queue);

	/*
	 * If a regulator is available,
	 * query what the supply voltage actually is!
	 */
	data->reg = devm_regulator_get_optional(data->dev, "vcc");
	अगर (!IS_ERR(data->reg)) अणु
		पूर्णांक voltage;

		voltage = regulator_get_voltage(data->reg);
		अगर (voltage)
			data->supply_uv = voltage;

		ret = regulator_enable(data->reg);
		अगर (ret != 0) अणु
			dev_err(&pdev->dev,
				"failed to enable regulator: %d\n", ret);
			वापस ret;
		पूर्ण

		/*
		 * Setup a notअगरier block to update this अगर another device
		 * causes the voltage to change
		 */
		data->nb.notअगरier_call = &sht15_invalidate_voltage;
		ret = regulator_रेजिस्टर_notअगरier(data->reg, &data->nb);
		अगर (ret) अणु
			dev_err(&pdev->dev,
				"regulator notifier request failed\n");
			regulator_disable(data->reg);
			वापस ret;
		पूर्ण
	पूर्ण

	/* Try requesting the GPIOs */
	data->sck = devm_gpiod_get(&pdev->dev, "clk", GPIOD_OUT_LOW);
	अगर (IS_ERR(data->sck)) अणु
		ret = PTR_ERR(data->sck);
		dev_err(&pdev->dev, "clock line GPIO request failed\n");
		जाओ err_release_reg;
	पूर्ण
	data->data = devm_gpiod_get(&pdev->dev, "data", GPIOD_IN);
	अगर (IS_ERR(data->data)) अणु
		ret = PTR_ERR(data->data);
		dev_err(&pdev->dev, "data line GPIO request failed\n");
		जाओ err_release_reg;
	पूर्ण

	ret = devm_request_irq(&pdev->dev, gpiod_to_irq(data->data),
			       sht15_पूर्णांकerrupt_fired,
			       IRQF_TRIGGER_FALLING,
			       "sht15 data",
			       data);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to get irq for data line\n");
		जाओ err_release_reg;
	पूर्ण
	disable_irq_nosync(gpiod_to_irq(data->data));
	ret = sht15_connection_reset(data);
	अगर (ret)
		जाओ err_release_reg;
	ret = sht15_soft_reset(data);
	अगर (ret)
		जाओ err_release_reg;

	ret = sysfs_create_group(&pdev->dev.kobj, &sht15_attr_group);
	अगर (ret) अणु
		dev_err(&pdev->dev, "sysfs create failed\n");
		जाओ err_release_reg;
	पूर्ण

	data->hwmon_dev = hwmon_device_रेजिस्टर(data->dev);
	अगर (IS_ERR(data->hwmon_dev)) अणु
		ret = PTR_ERR(data->hwmon_dev);
		जाओ err_release_sysfs_group;
	पूर्ण

	वापस 0;

err_release_sysfs_group:
	sysfs_हटाओ_group(&pdev->dev.kobj, &sht15_attr_group);
err_release_reg:
	अगर (!IS_ERR(data->reg)) अणु
		regulator_unरेजिस्टर_notअगरier(data->reg, &data->nb);
		regulator_disable(data->reg);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक sht15_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sht15_data *data = platक्रमm_get_drvdata(pdev);

	/*
	 * Make sure any पढ़ोs from the device are करोne and
	 * prevent new ones beginning
	 */
	mutex_lock(&data->पढ़ो_lock);
	अगर (sht15_soft_reset(data)) अणु
		mutex_unlock(&data->पढ़ो_lock);
		वापस -EFAULT;
	पूर्ण
	hwmon_device_unरेजिस्टर(data->hwmon_dev);
	sysfs_हटाओ_group(&pdev->dev.kobj, &sht15_attr_group);
	अगर (!IS_ERR(data->reg)) अणु
		regulator_unरेजिस्टर_notअगरier(data->reg, &data->nb);
		regulator_disable(data->reg);
	पूर्ण

	mutex_unlock(&data->पढ़ो_lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id sht15_device_ids[] = अणु
	अणु "sht10", sht10 पूर्ण,
	अणु "sht11", sht11 पूर्ण,
	अणु "sht15", sht15 पूर्ण,
	अणु "sht71", sht71 पूर्ण,
	अणु "sht75", sht75 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, sht15_device_ids);

अटल काष्ठा platक्रमm_driver sht15_driver = अणु
	.driver = अणु
		.name = "sht15",
		.of_match_table = of_match_ptr(sht15_dt_match),
	पूर्ण,
	.probe = sht15_probe,
	.हटाओ = sht15_हटाओ,
	.id_table = sht15_device_ids,
पूर्ण;
module_platक्रमm_driver(sht15_driver);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Sensirion SHT15 temperature and humidity sensor driver");
