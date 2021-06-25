<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
 /*
  * iio/adc/max1363.c
  * Copyright (C) 2008-2010 Jonathan Cameron
  *
  * based on linux/drivers/i2c/chips/max123x
  * Copyright (C) 2002-2004 Stefan Eletzhofer
  *
  * based on linux/drivers/acron/अक्षर/pcf8583.c
  * Copyright (C) 2000 Russell King
  *
  * Driver क्रम max1363 and similar chips.
  */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/list.h>
#समावेश <linux/i2c.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/property.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/events.h>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/driver.h>
#समावेश <linux/iio/kfअगरo_buf.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/iio/triggered_buffer.h>

#घोषणा MAX1363_SETUP_BYTE(a) ((a) | 0x80)

/* There is a fair bit more defined here than currently
 * used, but the पूर्णांकention is to support everything these
 * chips करो in the दीर्घ run */

/* see data sheets */
/* max1363 and max1236, max1237, max1238, max1239 */
#घोषणा MAX1363_SETUP_AIN3_IS_AIN3_REF_IS_VDD	0x00
#घोषणा MAX1363_SETUP_AIN3_IS_REF_EXT_TO_REF	0x20
#घोषणा MAX1363_SETUP_AIN3_IS_AIN3_REF_IS_INT	0x40
#घोषणा MAX1363_SETUP_AIN3_IS_REF_REF_IS_INT	0x60
#घोषणा MAX1363_SETUP_POWER_UP_INT_REF		0x10
#घोषणा MAX1363_SETUP_POWER_DOWN_INT_REF	0x00

/* think about including max11600 etc - more settings */
#घोषणा MAX1363_SETUP_EXT_CLOCK			0x08
#घोषणा MAX1363_SETUP_INT_CLOCK			0x00
#घोषणा MAX1363_SETUP_UNIPOLAR			0x00
#घोषणा MAX1363_SETUP_BIPOLAR			0x04
#घोषणा MAX1363_SETUP_RESET			0x00
#घोषणा MAX1363_SETUP_NORESET			0x02
/* max1363 only - though करोn't care on others.
 * For now monitor modes are not implemented as the relevant
 * line is not connected on my test board.
 * The definitions are here as I पूर्णांकend to add this soon.
 */
#घोषणा MAX1363_SETUP_MONITOR_SETUP		0x01

/* Specअगरic to the max1363 */
#घोषणा MAX1363_MON_RESET_CHAN(a) (1 << ((a) + 4))
#घोषणा MAX1363_MON_INT_ENABLE			0x01

/* defined क्रम पढ़ोability reasons */
/* All chips */
#घोषणा MAX1363_CONFIG_BYTE(a) ((a))

#घोषणा MAX1363_CONFIG_SE			0x01
#घोषणा MAX1363_CONFIG_DE			0x00
#घोषणा MAX1363_CONFIG_SCAN_TO_CS		0x00
#घोषणा MAX1363_CONFIG_SCAN_SINGLE_8		0x20
#घोषणा MAX1363_CONFIG_SCAN_MONITOR_MODE	0x40
#घोषणा MAX1363_CONFIG_SCAN_SINGLE_1		0x60
/* max123अणु6-9पूर्ण only */
#घोषणा MAX1236_SCAN_MID_TO_CHANNEL		0x40

/* max1363 only - merely part of channel selects or करोn't care क्रम others */
#घोषणा MAX1363_CONFIG_EN_MON_MODE_READ 0x18

#घोषणा MAX1363_CHANNEL_SEL(a) ((a) << 1)

/* max1363 strictly 0x06 - but करोesn't matter */
#घोषणा MAX1363_CHANNEL_SEL_MASK		0x1E
#घोषणा MAX1363_SCAN_MASK			0x60
#घोषणा MAX1363_SE_DE_MASK			0x01

#घोषणा MAX1363_MAX_CHANNELS 25
/**
 * काष्ठा max1363_mode - scan mode inक्रमmation
 * @conf:	The corresponding value of the configuration रेजिस्टर
 * @modemask:	Bit mask corresponding to channels enabled in this mode
 */
काष्ठा max1363_mode अणु
	पूर्णांक8_t		conf;
	DECLARE_BITMAP(modemask, MAX1363_MAX_CHANNELS);
पूर्ण;

/* This must be मुख्यtained aदीर्घ side the max1363_mode_table in max1363_core */
क्रमागत max1363_modes अणु
	/* Single पढ़ो of a single channel */
	_s0, _s1, _s2, _s3, _s4, _s5, _s6, _s7, _s8, _s9, _s10, _s11,
	/* Dअगरferential single पढ़ो */
	d0m1, d2m3, d4m5, d6m7, d8m9, d10m11,
	d1m0, d3m2, d5m4, d7m6, d9m8, d11m10,
	/* Scan to channel and mid to channel where overlapping */
	s0to1, s0to2, s2to3, s0to3, s0to4, s0to5, s0to6,
	s6to7, s0to7, s6to8, s0to8, s6to9,
	s0to9, s6to10, s0to10, s6to11, s0to11,
	/* Dअगरferential scan to channel and mid to channel where overlapping */
	d0m1to2m3, d0m1to4m5, d0m1to6m7, d6m7to8m9,
	d0m1to8m9, d6m7to10m11, d0m1to10m11, d1m0to3m2,
	d1m0to5m4, d1m0to7m6, d7m6to9m8, d1m0to9m8,
	d7m6to11m10, d1m0to11m10,
पूर्ण;

/**
 * काष्ठा max1363_chip_info - chip specअगरc inक्रमmation
 * @info:		iio core function callbacks काष्ठाure
 * @channels:		channel specअगरication
 * @num_channels:       number of channels
 * @mode_list:		array of available scan modes
 * @शेष_mode:	the scan mode in which the chip starts up
 * @पूर्णांक_vref_mv:	the पूर्णांकernal reference voltage
 * @num_modes:		number of modes
 * @bits:		accuracy of the adc in bits
 */
काष्ठा max1363_chip_info अणु
	स्थिर काष्ठा iio_info		*info;
	स्थिर काष्ठा iio_chan_spec	*channels;
	पूर्णांक				num_channels;
	स्थिर क्रमागत max1363_modes	*mode_list;
	क्रमागत max1363_modes		शेष_mode;
	u16				पूर्णांक_vref_mv;
	u8				num_modes;
	u8				bits;
पूर्ण;

/**
 * काष्ठा max1363_state - driver instance specअगरic data
 * @client:		i2c_client
 * @setupbyte:		cache of current device setup byte
 * @configbyte:		cache of current device config byte
 * @chip_info:		chip model specअगरic स्थिरants, available modes, etc.
 * @current_mode:	the scan mode of this chip
 * @requestedmask:	a valid requested set of channels
 * @reg:		supply regulator
 * @lock:		lock to ensure state is consistent
 * @monitor_on:		whether monitor mode is enabled
 * @monitor_speed:	parameter corresponding to device monitor speed setting
 * @mask_high:		biपंचांगask क्रम enabled high thresholds
 * @mask_low:		biपंचांगask क्रम enabled low thresholds
 * @thresh_high:	high threshold values
 * @thresh_low:		low threshold values
 * @vref:		Reference voltage regulator
 * @vref_uv:		Actual (बाह्यal or पूर्णांकernal) reference voltage
 * @send:		function used to send data to the chip
 * @recv:		function used to receive data from the chip
 */
काष्ठा max1363_state अणु
	काष्ठा i2c_client		*client;
	u8				setupbyte;
	u8				configbyte;
	स्थिर काष्ठा max1363_chip_info	*chip_info;
	स्थिर काष्ठा max1363_mode	*current_mode;
	u32				requestedmask;
	काष्ठा regulator		*reg;
	काष्ठा mutex			lock;

	/* Using monitor modes and buffer at the same समय is
	   currently not supported */
	bool				monitor_on;
	अचिन्हित पूर्णांक			monitor_speed:3;
	u8				mask_high;
	u8				mask_low;
	/* 4x unipolar first then the fours bipolar ones */
	s16				thresh_high[8];
	s16				thresh_low[8];
	काष्ठा regulator		*vref;
	u32				vref_uv;
	पूर्णांक				(*send)(स्थिर काष्ठा i2c_client *client,
						स्थिर अक्षर *buf, पूर्णांक count);
	पूर्णांक				(*recv)(स्थिर काष्ठा i2c_client *client,
						अक्षर *buf, पूर्णांक count);
पूर्ण;

#घोषणा MAX1363_MODE_SINGLE(_num, _mask) अणु				\
		.conf = MAX1363_CHANNEL_SEL(_num)			\
			| MAX1363_CONFIG_SCAN_SINGLE_1			\
			| MAX1363_CONFIG_SE,				\
			.modemask[0] = _mask,				\
			पूर्ण

#घोषणा MAX1363_MODE_SCAN_TO_CHANNEL(_num, _mask) अणु			\
		.conf = MAX1363_CHANNEL_SEL(_num)			\
			| MAX1363_CONFIG_SCAN_TO_CS			\
			| MAX1363_CONFIG_SE,				\
			.modemask[0] = _mask,				\
			पूर्ण

/* note not available क्रम max1363 hence naming */
#घोषणा MAX1236_MODE_SCAN_MID_TO_CHANNEL(_mid, _num, _mask) अणु		\
		.conf = MAX1363_CHANNEL_SEL(_num)			\
			| MAX1236_SCAN_MID_TO_CHANNEL			\
			| MAX1363_CONFIG_SE,				\
			.modemask[0] = _mask				\
पूर्ण

#घोषणा MAX1363_MODE_DIFF_SINGLE(_nump, _numm, _mask) अणु			\
		.conf = MAX1363_CHANNEL_SEL(_nump)			\
			| MAX1363_CONFIG_SCAN_SINGLE_1			\
			| MAX1363_CONFIG_DE,				\
			.modemask[0] = _mask				\
			पूर्ण

/* Can't think how to स्वतःmate naming so specअगरy क्रम now */
#घोषणा MAX1363_MODE_DIFF_SCAN_TO_CHANNEL(_num, _numvals, _mask) अणु	\
		.conf = MAX1363_CHANNEL_SEL(_num)			\
			| MAX1363_CONFIG_SCAN_TO_CS			\
			| MAX1363_CONFIG_DE,				\
			.modemask[0] = _mask				\
			पूर्ण

/* note only available क्रम max1363 hence naming */
#घोषणा MAX1236_MODE_DIFF_SCAN_MID_TO_CHANNEL(_num, _numvals, _mask) अणु	\
		.conf = MAX1363_CHANNEL_SEL(_num)			\
			| MAX1236_SCAN_MID_TO_CHANNEL			\
			| MAX1363_CONFIG_SE,				\
			.modemask[0] = _mask				\
पूर्ण

अटल स्थिर काष्ठा max1363_mode max1363_mode_table[] = अणु
	/* All of the single channel options first */
	MAX1363_MODE_SINGLE(0, 1 << 0),
	MAX1363_MODE_SINGLE(1, 1 << 1),
	MAX1363_MODE_SINGLE(2, 1 << 2),
	MAX1363_MODE_SINGLE(3, 1 << 3),
	MAX1363_MODE_SINGLE(4, 1 << 4),
	MAX1363_MODE_SINGLE(5, 1 << 5),
	MAX1363_MODE_SINGLE(6, 1 << 6),
	MAX1363_MODE_SINGLE(7, 1 << 7),
	MAX1363_MODE_SINGLE(8, 1 << 8),
	MAX1363_MODE_SINGLE(9, 1 << 9),
	MAX1363_MODE_SINGLE(10, 1 << 10),
	MAX1363_MODE_SINGLE(11, 1 << 11),

	MAX1363_MODE_DIFF_SINGLE(0, 1, 1 << 12),
	MAX1363_MODE_DIFF_SINGLE(2, 3, 1 << 13),
	MAX1363_MODE_DIFF_SINGLE(4, 5, 1 << 14),
	MAX1363_MODE_DIFF_SINGLE(6, 7, 1 << 15),
	MAX1363_MODE_DIFF_SINGLE(8, 9, 1 << 16),
	MAX1363_MODE_DIFF_SINGLE(10, 11, 1 << 17),
	MAX1363_MODE_DIFF_SINGLE(1, 0, 1 << 18),
	MAX1363_MODE_DIFF_SINGLE(3, 2, 1 << 19),
	MAX1363_MODE_DIFF_SINGLE(5, 4, 1 << 20),
	MAX1363_MODE_DIFF_SINGLE(7, 6, 1 << 21),
	MAX1363_MODE_DIFF_SINGLE(9, 8, 1 << 22),
	MAX1363_MODE_DIFF_SINGLE(11, 10, 1 << 23),

	/* The multichannel scans next */
	MAX1363_MODE_SCAN_TO_CHANNEL(1, 0x003),
	MAX1363_MODE_SCAN_TO_CHANNEL(2, 0x007),
	MAX1236_MODE_SCAN_MID_TO_CHANNEL(2, 3, 0x00C),
	MAX1363_MODE_SCAN_TO_CHANNEL(3, 0x00F),
	MAX1363_MODE_SCAN_TO_CHANNEL(4, 0x01F),
	MAX1363_MODE_SCAN_TO_CHANNEL(5, 0x03F),
	MAX1363_MODE_SCAN_TO_CHANNEL(6, 0x07F),
	MAX1236_MODE_SCAN_MID_TO_CHANNEL(6, 7, 0x0C0),
	MAX1363_MODE_SCAN_TO_CHANNEL(7, 0x0FF),
	MAX1236_MODE_SCAN_MID_TO_CHANNEL(6, 8, 0x1C0),
	MAX1363_MODE_SCAN_TO_CHANNEL(8, 0x1FF),
	MAX1236_MODE_SCAN_MID_TO_CHANNEL(6, 9, 0x3C0),
	MAX1363_MODE_SCAN_TO_CHANNEL(9, 0x3FF),
	MAX1236_MODE_SCAN_MID_TO_CHANNEL(6, 10, 0x7C0),
	MAX1363_MODE_SCAN_TO_CHANNEL(10, 0x7FF),
	MAX1236_MODE_SCAN_MID_TO_CHANNEL(6, 11, 0xFC0),
	MAX1363_MODE_SCAN_TO_CHANNEL(11, 0xFFF),

	MAX1363_MODE_DIFF_SCAN_TO_CHANNEL(2, 2, 0x003000),
	MAX1363_MODE_DIFF_SCAN_TO_CHANNEL(4, 3, 0x007000),
	MAX1363_MODE_DIFF_SCAN_TO_CHANNEL(6, 4, 0x00F000),
	MAX1236_MODE_DIFF_SCAN_MID_TO_CHANNEL(8, 2, 0x018000),
	MAX1363_MODE_DIFF_SCAN_TO_CHANNEL(8, 5, 0x01F000),
	MAX1236_MODE_DIFF_SCAN_MID_TO_CHANNEL(10, 3, 0x038000),
	MAX1363_MODE_DIFF_SCAN_TO_CHANNEL(10, 6, 0x3F000),
	MAX1363_MODE_DIFF_SCAN_TO_CHANNEL(3, 2, 0x0C0000),
	MAX1363_MODE_DIFF_SCAN_TO_CHANNEL(5, 3, 0x1C0000),
	MAX1363_MODE_DIFF_SCAN_TO_CHANNEL(7, 4, 0x3C0000),
	MAX1236_MODE_DIFF_SCAN_MID_TO_CHANNEL(9, 2, 0x600000),
	MAX1363_MODE_DIFF_SCAN_TO_CHANNEL(9, 5, 0x7C0000),
	MAX1236_MODE_DIFF_SCAN_MID_TO_CHANNEL(11, 3, 0xE00000),
	MAX1363_MODE_DIFF_SCAN_TO_CHANNEL(11, 6, 0xFC0000),
पूर्ण;

अटल स्थिर काष्ठा max1363_mode
*max1363_match_mode(स्थिर अचिन्हित दीर्घ *mask,
	स्थिर काष्ठा max1363_chip_info *ci)
अणु
	पूर्णांक i;
	अगर (mask)
		क्रम (i = 0; i < ci->num_modes; i++)
			अगर (biपंचांगap_subset(mask,
					  max1363_mode_table[ci->mode_list[i]].
					  modemask,
					  MAX1363_MAX_CHANNELS))
				वापस &max1363_mode_table[ci->mode_list[i]];
	वापस शून्य;
पूर्ण

अटल पूर्णांक max1363_smbus_send(स्थिर काष्ठा i2c_client *client, स्थिर अक्षर *buf,
		पूर्णांक count)
अणु
	पूर्णांक i, err;

	क्रम (i = err = 0; err == 0 && i < count; ++i)
		err = i2c_smbus_ग_लिखो_byte(client, buf[i]);

	वापस err ? err : count;
पूर्ण

अटल पूर्णांक max1363_smbus_recv(स्थिर काष्ठा i2c_client *client, अक्षर *buf,
		पूर्णांक count)
अणु
	पूर्णांक i, ret;

	क्रम (i = 0; i < count; ++i) अणु
		ret = i2c_smbus_पढ़ो_byte(client);
		अगर (ret < 0)
			वापस ret;
		buf[i] = ret;
	पूर्ण

	वापस count;
पूर्ण

अटल पूर्णांक max1363_ग_लिखो_basic_config(काष्ठा max1363_state *st)
अणु
	u8 tx_buf[2] = अणु st->setupbyte, st->configbyte पूर्ण;

	वापस st->send(st->client, tx_buf, 2);
पूर्ण

अटल पूर्णांक max1363_set_scan_mode(काष्ठा max1363_state *st)
अणु
	st->configbyte &= ~(MAX1363_CHANNEL_SEL_MASK
			    | MAX1363_SCAN_MASK
			    | MAX1363_SE_DE_MASK);
	st->configbyte |= st->current_mode->conf;

	वापस max1363_ग_लिखो_basic_config(st);
पूर्ण

अटल पूर्णांक max1363_पढ़ो_single_chan(काष्ठा iio_dev *indio_dev,
				    काष्ठा iio_chan_spec स्थिर *chan,
				    पूर्णांक *val,
				    दीर्घ m)
अणु
	पूर्णांक ret = 0;
	s32 data;
	u8 rxbuf[2];
	काष्ठा max1363_state *st = iio_priv(indio_dev);
	काष्ठा i2c_client *client = st->client;

	ret = iio_device_claim_direct_mode(indio_dev);
	अगर (ret)
		वापस ret;
	mutex_lock(&st->lock);

	/*
	 * If monitor mode is enabled, the method क्रम पढ़ोing a single
	 * channel will have to be rather dअगरferent and has not yet
	 * been implemented.
	 *
	 * Also, cannot पढ़ो directly अगर buffered capture enabled.
	 */
	अगर (st->monitor_on) अणु
		ret = -EBUSY;
		जाओ error_ret;
	पूर्ण

	/* Check to see अगर current scan mode is correct */
	अगर (st->current_mode != &max1363_mode_table[chan->address]) अणु
		/* Update scan mode अगर needed */
		st->current_mode = &max1363_mode_table[chan->address];
		ret = max1363_set_scan_mode(st);
		अगर (ret < 0)
			जाओ error_ret;
	पूर्ण
	अगर (st->chip_info->bits != 8) अणु
		/* Get पढ़ोing */
		data = st->recv(client, rxbuf, 2);
		अगर (data < 0) अणु
			ret = data;
			जाओ error_ret;
		पूर्ण
		data = (rxbuf[1] | rxbuf[0] << 8) &
		  ((1 << st->chip_info->bits) - 1);
	पूर्ण अन्यथा अणु
		/* Get पढ़ोing */
		data = st->recv(client, rxbuf, 1);
		अगर (data < 0) अणु
			ret = data;
			जाओ error_ret;
		पूर्ण
		data = rxbuf[0];
	पूर्ण
	*val = data;

error_ret:
	mutex_unlock(&st->lock);
	iio_device_release_direct_mode(indio_dev);
	वापस ret;

पूर्ण

अटल पूर्णांक max1363_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan,
			    पूर्णांक *val,
			    पूर्णांक *val2,
			    दीर्घ m)
अणु
	काष्ठा max1363_state *st = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (m) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = max1363_पढ़ो_single_chan(indio_dev, chan, val, m);
		अगर (ret < 0)
			वापस ret;
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		*val = st->vref_uv / 1000;
		*val2 = st->chip_info->bits;
		वापस IIO_VAL_FRACTIONAL_LOG2;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/* Applies to max1363 */
अटल स्थिर क्रमागत max1363_modes max1363_mode_list[] = अणु
	_s0, _s1, _s2, _s3,
	s0to1, s0to2, s0to3,
	d0m1, d2m3, d1m0, d3m2,
	d0m1to2m3, d1m0to3m2,
पूर्ण;

अटल स्थिर काष्ठा iio_event_spec max1363_events[] = अणु
	अणु
		.type = IIO_EV_TYPE_THRESH,
		.dir = IIO_EV_सूची_RISING,
		.mask_separate = BIT(IIO_EV_INFO_VALUE) |
			BIT(IIO_EV_INFO_ENABLE),
	पूर्ण, अणु
		.type = IIO_EV_TYPE_THRESH,
		.dir = IIO_EV_सूची_FALLING,
		.mask_separate = BIT(IIO_EV_INFO_VALUE) |
			BIT(IIO_EV_INFO_ENABLE),
	पूर्ण,
पूर्ण;

#घोषणा MAX1363_CHAN_U(num, addr, si, bits, ev_spec, num_ev_spec)	\
	अणु								\
		.type = IIO_VOLTAGE,					\
		.indexed = 1,						\
		.channel = num,						\
		.address = addr,					\
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),		\
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE),	\
		.datasheet_name = "AIN"#num,				\
		.scan_type = अणु						\
			.sign = 'u',					\
			.realbits = bits,				\
			.storagebits = (bits > 8) ? 16 : 8,		\
			.endianness = IIO_BE,				\
		पूर्ण,							\
		.scan_index = si,					\
		.event_spec = ev_spec,					\
		.num_event_specs = num_ev_spec,				\
	पूर्ण

/* bipolar channel */
#घोषणा MAX1363_CHAN_B(num, num2, addr, si, bits, ev_spec, num_ev_spec)	\
	अणु								\
		.type = IIO_VOLTAGE,					\
		.dअगरferential = 1,					\
		.indexed = 1,						\
		.channel = num,						\
		.channel2 = num2,					\
		.address = addr,					\
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),		\
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE),	\
		.datasheet_name = "AIN"#num"-AIN"#num2,			\
		.scan_type = अणु						\
			.sign = 's',					\
			.realbits = bits,				\
			.storagebits = (bits > 8) ? 16 : 8,		\
			.endianness = IIO_BE,				\
		पूर्ण,							\
		.scan_index = si,					\
		.event_spec = ev_spec,					\
		.num_event_specs = num_ev_spec,				\
	पूर्ण

#घोषणा MAX1363_4X_CHANS(bits, ev_spec, num_ev_spec) अणु			\
	MAX1363_CHAN_U(0, _s0, 0, bits, ev_spec, num_ev_spec),		\
	MAX1363_CHAN_U(1, _s1, 1, bits, ev_spec, num_ev_spec),		\
	MAX1363_CHAN_U(2, _s2, 2, bits, ev_spec, num_ev_spec),		\
	MAX1363_CHAN_U(3, _s3, 3, bits, ev_spec, num_ev_spec),		\
	MAX1363_CHAN_B(0, 1, d0m1, 4, bits, ev_spec, num_ev_spec),	\
	MAX1363_CHAN_B(2, 3, d2m3, 5, bits, ev_spec, num_ev_spec),	\
	MAX1363_CHAN_B(1, 0, d1m0, 6, bits, ev_spec, num_ev_spec),	\
	MAX1363_CHAN_B(3, 2, d3m2, 7, bits, ev_spec, num_ev_spec),	\
	IIO_CHAN_SOFT_TIMESTAMP(8)					\
	पूर्ण

अटल स्थिर काष्ठा iio_chan_spec max1036_channels[] =
	MAX1363_4X_CHANS(8, शून्य, 0);
अटल स्थिर काष्ठा iio_chan_spec max1136_channels[] =
	MAX1363_4X_CHANS(10, शून्य, 0);
अटल स्थिर काष्ठा iio_chan_spec max1236_channels[] =
	MAX1363_4X_CHANS(12, शून्य, 0);
अटल स्थिर काष्ठा iio_chan_spec max1361_channels[] =
	MAX1363_4X_CHANS(10, max1363_events, ARRAY_SIZE(max1363_events));
अटल स्थिर काष्ठा iio_chan_spec max1363_channels[] =
	MAX1363_4X_CHANS(12, max1363_events, ARRAY_SIZE(max1363_events));

/* Applies to max1236, max1237 */
अटल स्थिर क्रमागत max1363_modes max1236_mode_list[] = अणु
	_s0, _s1, _s2, _s3,
	s0to1, s0to2, s0to3,
	d0m1, d2m3, d1m0, d3m2,
	d0m1to2m3, d1m0to3m2,
	s2to3,
पूर्ण;

/* Applies to max1238, max1239 */
अटल स्थिर क्रमागत max1363_modes max1238_mode_list[] = अणु
	_s0, _s1, _s2, _s3, _s4, _s5, _s6, _s7, _s8, _s9, _s10, _s11,
	s0to1, s0to2, s0to3, s0to4, s0to5, s0to6,
	s0to7, s0to8, s0to9, s0to10, s0to11,
	d0m1, d2m3, d4m5, d6m7, d8m9, d10m11,
	d1m0, d3m2, d5m4, d7m6, d9m8, d11m10,
	d0m1to2m3, d0m1to4m5, d0m1to6m7, d0m1to8m9, d0m1to10m11,
	d1m0to3m2, d1m0to5m4, d1m0to7m6, d1m0to9m8, d1m0to11m10,
	s6to7, s6to8, s6to9, s6to10, s6to11,
	d6m7to8m9, d6m7to10m11, d7m6to9m8, d7m6to11m10,
पूर्ण;

#घोषणा MAX1363_12X_CHANS(bits) अणु				\
	MAX1363_CHAN_U(0, _s0, 0, bits, शून्य, 0),		\
	MAX1363_CHAN_U(1, _s1, 1, bits, शून्य, 0),		\
	MAX1363_CHAN_U(2, _s2, 2, bits, शून्य, 0),		\
	MAX1363_CHAN_U(3, _s3, 3, bits, शून्य, 0),		\
	MAX1363_CHAN_U(4, _s4, 4, bits, शून्य, 0),		\
	MAX1363_CHAN_U(5, _s5, 5, bits, शून्य, 0),		\
	MAX1363_CHAN_U(6, _s6, 6, bits, शून्य, 0),		\
	MAX1363_CHAN_U(7, _s7, 7, bits, शून्य, 0),		\
	MAX1363_CHAN_U(8, _s8, 8, bits, शून्य, 0),		\
	MAX1363_CHAN_U(9, _s9, 9, bits, शून्य, 0),		\
	MAX1363_CHAN_U(10, _s10, 10, bits, शून्य, 0),		\
	MAX1363_CHAN_U(11, _s11, 11, bits, शून्य, 0),		\
	MAX1363_CHAN_B(0, 1, d0m1, 12, bits, शून्य, 0),		\
	MAX1363_CHAN_B(2, 3, d2m3, 13, bits, शून्य, 0),		\
	MAX1363_CHAN_B(4, 5, d4m5, 14, bits, शून्य, 0),		\
	MAX1363_CHAN_B(6, 7, d6m7, 15, bits, शून्य, 0),		\
	MAX1363_CHAN_B(8, 9, d8m9, 16, bits, शून्य, 0),		\
	MAX1363_CHAN_B(10, 11, d10m11, 17, bits, शून्य, 0),	\
	MAX1363_CHAN_B(1, 0, d1m0, 18, bits, शून्य, 0),		\
	MAX1363_CHAN_B(3, 2, d3m2, 19, bits, शून्य, 0),		\
	MAX1363_CHAN_B(5, 4, d5m4, 20, bits, शून्य, 0),		\
	MAX1363_CHAN_B(7, 6, d7m6, 21, bits, शून्य, 0),		\
	MAX1363_CHAN_B(9, 8, d9m8, 22, bits, शून्य, 0),		\
	MAX1363_CHAN_B(11, 10, d11m10, 23, bits, शून्य, 0),	\
	IIO_CHAN_SOFT_TIMESTAMP(24)				\
	पूर्ण
अटल स्थिर काष्ठा iio_chan_spec max1038_channels[] = MAX1363_12X_CHANS(8);
अटल स्थिर काष्ठा iio_chan_spec max1138_channels[] = MAX1363_12X_CHANS(10);
अटल स्थिर काष्ठा iio_chan_spec max1238_channels[] = MAX1363_12X_CHANS(12);

अटल स्थिर क्रमागत max1363_modes max11607_mode_list[] = अणु
	_s0, _s1, _s2, _s3,
	s0to1, s0to2, s0to3,
	s2to3,
	d0m1, d2m3, d1m0, d3m2,
	d0m1to2m3, d1m0to3m2,
पूर्ण;

अटल स्थिर क्रमागत max1363_modes max11608_mode_list[] = अणु
	_s0, _s1, _s2, _s3, _s4, _s5, _s6, _s7,
	s0to1, s0to2, s0to3, s0to4, s0to5, s0to6, s0to7,
	s6to7,
	d0m1, d2m3, d4m5, d6m7,
	d1m0, d3m2, d5m4, d7m6,
	d0m1to2m3, d0m1to4m5, d0m1to6m7,
	d1m0to3m2, d1m0to5m4, d1m0to7m6,
पूर्ण;

#घोषणा MAX1363_8X_CHANS(bits) अणु			\
	MAX1363_CHAN_U(0, _s0, 0, bits, शून्य, 0),	\
	MAX1363_CHAN_U(1, _s1, 1, bits, शून्य, 0),	\
	MAX1363_CHAN_U(2, _s2, 2, bits, शून्य, 0),	\
	MAX1363_CHAN_U(3, _s3, 3, bits, शून्य, 0),	\
	MAX1363_CHAN_U(4, _s4, 4, bits, शून्य, 0),	\
	MAX1363_CHAN_U(5, _s5, 5, bits, शून्य, 0),	\
	MAX1363_CHAN_U(6, _s6, 6, bits, शून्य, 0),	\
	MAX1363_CHAN_U(7, _s7, 7, bits, शून्य, 0),	\
	MAX1363_CHAN_B(0, 1, d0m1, 8, bits, शून्य, 0),	\
	MAX1363_CHAN_B(2, 3, d2m3, 9, bits, शून्य, 0),	\
	MAX1363_CHAN_B(4, 5, d4m5, 10, bits, शून्य, 0),	\
	MAX1363_CHAN_B(6, 7, d6m7, 11, bits, शून्य, 0),	\
	MAX1363_CHAN_B(1, 0, d1m0, 12, bits, शून्य, 0),	\
	MAX1363_CHAN_B(3, 2, d3m2, 13, bits, शून्य, 0),	\
	MAX1363_CHAN_B(5, 4, d5m4, 14, bits, शून्य, 0),	\
	MAX1363_CHAN_B(7, 6, d7m6, 15, bits, शून्य, 0),	\
	IIO_CHAN_SOFT_TIMESTAMP(16)			\
पूर्ण
अटल स्थिर काष्ठा iio_chan_spec max11602_channels[] = MAX1363_8X_CHANS(8);
अटल स्थिर काष्ठा iio_chan_spec max11608_channels[] = MAX1363_8X_CHANS(10);
अटल स्थिर काष्ठा iio_chan_spec max11614_channels[] = MAX1363_8X_CHANS(12);

अटल स्थिर क्रमागत max1363_modes max11644_mode_list[] = अणु
	_s0, _s1, s0to1, d0m1, d1m0,
पूर्ण;

#घोषणा MAX1363_2X_CHANS(bits) अणु			\
	MAX1363_CHAN_U(0, _s0, 0, bits, शून्य, 0),	\
	MAX1363_CHAN_U(1, _s1, 1, bits, शून्य, 0),	\
	MAX1363_CHAN_B(0, 1, d0m1, 2, bits, शून्य, 0),	\
	MAX1363_CHAN_B(1, 0, d1m0, 3, bits, शून्य, 0),	\
	IIO_CHAN_SOFT_TIMESTAMP(4)			\
	पूर्ण

अटल स्थिर काष्ठा iio_chan_spec max11646_channels[] = MAX1363_2X_CHANS(10);
अटल स्थिर काष्ठा iio_chan_spec max11644_channels[] = MAX1363_2X_CHANS(12);

क्रमागत अणु max1361,
       max1362,
       max1363,
       max1364,
       max1036,
       max1037,
       max1038,
       max1039,
       max1136,
       max1137,
       max1138,
       max1139,
       max1236,
       max1237,
       max1238,
       max1239,
       max11600,
       max11601,
       max11602,
       max11603,
       max11604,
       max11605,
       max11606,
       max11607,
       max11608,
       max11609,
       max11610,
       max11611,
       max11612,
       max11613,
       max11614,
       max11615,
       max11616,
       max11617,
       max11644,
       max11645,
       max11646,
       max11647
पूर्ण;

अटल स्थिर पूर्णांक max1363_monitor_speeds[] = अणु 133000, 665000, 33300, 16600,
					      8300, 4200, 2000, 1000 पूर्ण;

अटल sमाप_प्रकार max1363_monitor_show_freq(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	काष्ठा max1363_state *st = iio_priv(dev_to_iio_dev(dev));
	वापस प्र_लिखो(buf, "%d\n", max1363_monitor_speeds[st->monitor_speed]);
पूर्ण

अटल sमाप_प्रकार max1363_monitor_store_freq(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					स्थिर अक्षर *buf,
					माप_प्रकार len)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा max1363_state *st = iio_priv(indio_dev);
	पूर्णांक i, ret;
	अचिन्हित दीर्घ val;
	bool found = false;

	ret = kम_से_अदीर्घ(buf, 10, &val);
	अगर (ret)
		वापस -EINVAL;
	क्रम (i = 0; i < ARRAY_SIZE(max1363_monitor_speeds); i++)
		अगर (val == max1363_monitor_speeds[i]) अणु
			found = true;
			अवरोध;
		पूर्ण
	अगर (!found)
		वापस -EINVAL;

	mutex_lock(&st->lock);
	st->monitor_speed = i;
	mutex_unlock(&st->lock);

	वापस 0;
पूर्ण

अटल IIO_DEV_ATTR_SAMP_FREQ(S_IRUGO | S_IWUSR,
			max1363_monitor_show_freq,
			max1363_monitor_store_freq);

अटल IIO_CONST_ATTR(sampling_frequency_available,
		"133000 665000 33300 16600 8300 4200 2000 1000");

अटल पूर्णांक max1363_पढ़ो_thresh(काष्ठा iio_dev *indio_dev,
	स्थिर काष्ठा iio_chan_spec *chan, क्रमागत iio_event_type type,
	क्रमागत iio_event_direction dir, क्रमागत iio_event_info info, पूर्णांक *val,
	पूर्णांक *val2)
अणु
	काष्ठा max1363_state *st = iio_priv(indio_dev);
	अगर (dir == IIO_EV_सूची_FALLING)
		*val = st->thresh_low[chan->channel];
	अन्यथा
		*val = st->thresh_high[chan->channel];
	वापस IIO_VAL_INT;
पूर्ण

अटल पूर्णांक max1363_ग_लिखो_thresh(काष्ठा iio_dev *indio_dev,
	स्थिर काष्ठा iio_chan_spec *chan, क्रमागत iio_event_type type,
	क्रमागत iio_event_direction dir, क्रमागत iio_event_info info, पूर्णांक val,
	पूर्णांक val2)
अणु
	काष्ठा max1363_state *st = iio_priv(indio_dev);
	/* make it handle चिन्हित correctly as well */
	चयन (st->chip_info->bits) अणु
	हाल 10:
		अगर (val > 0x3FF)
			वापस -EINVAL;
		अवरोध;
	हाल 12:
		अगर (val > 0xFFF)
			वापस -EINVAL;
		अवरोध;
	पूर्ण

	चयन (dir) अणु
	हाल IIO_EV_सूची_FALLING:
		st->thresh_low[chan->channel] = val;
		अवरोध;
	हाल IIO_EV_सूची_RISING:
		st->thresh_high[chan->channel] = val;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर u64 max1363_event_codes[] = अणु
	IIO_UNMOD_EVENT_CODE(IIO_VOLTAGE, 0,
			     IIO_EV_TYPE_THRESH, IIO_EV_सूची_FALLING),
	IIO_UNMOD_EVENT_CODE(IIO_VOLTAGE, 1,
			     IIO_EV_TYPE_THRESH, IIO_EV_सूची_FALLING),
	IIO_UNMOD_EVENT_CODE(IIO_VOLTAGE, 2,
			     IIO_EV_TYPE_THRESH, IIO_EV_सूची_FALLING),
	IIO_UNMOD_EVENT_CODE(IIO_VOLTAGE, 3,
			     IIO_EV_TYPE_THRESH, IIO_EV_सूची_FALLING),
	IIO_UNMOD_EVENT_CODE(IIO_VOLTAGE, 0,
			     IIO_EV_TYPE_THRESH, IIO_EV_सूची_RISING),
	IIO_UNMOD_EVENT_CODE(IIO_VOLTAGE, 1,
			     IIO_EV_TYPE_THRESH, IIO_EV_सूची_RISING),
	IIO_UNMOD_EVENT_CODE(IIO_VOLTAGE, 2,
			     IIO_EV_TYPE_THRESH, IIO_EV_सूची_RISING),
	IIO_UNMOD_EVENT_CODE(IIO_VOLTAGE, 3,
			     IIO_EV_TYPE_THRESH, IIO_EV_सूची_RISING),
पूर्ण;

अटल irqवापस_t max1363_event_handler(पूर्णांक irq, व्योम *निजी)
अणु
	काष्ठा iio_dev *indio_dev = निजी;
	काष्ठा max1363_state *st = iio_priv(indio_dev);
	s64 बारtamp = iio_get_समय_ns(indio_dev);
	अचिन्हित दीर्घ mask, loc;
	u8 rx;
	u8 tx[2] = अणु st->setupbyte,
		     MAX1363_MON_INT_ENABLE | (st->monitor_speed << 1) | 0xF0 पूर्ण;

	st->recv(st->client, &rx, 1);
	mask = rx;
	क्रम_each_set_bit(loc, &mask, 8)
		iio_push_event(indio_dev, max1363_event_codes[loc], बारtamp);
	st->send(st->client, tx, 2);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक max1363_पढ़ो_event_config(काष्ठा iio_dev *indio_dev,
	स्थिर काष्ठा iio_chan_spec *chan, क्रमागत iio_event_type type,
	क्रमागत iio_event_direction dir)
अणु
	काष्ठा max1363_state *st = iio_priv(indio_dev);
	पूर्णांक val;
	पूर्णांक number = chan->channel;

	mutex_lock(&st->lock);
	अगर (dir == IIO_EV_सूची_FALLING)
		val = (1 << number) & st->mask_low;
	अन्यथा
		val = (1 << number) & st->mask_high;
	mutex_unlock(&st->lock);

	वापस val;
पूर्ण

अटल पूर्णांक max1363_monitor_mode_update(काष्ठा max1363_state *st, पूर्णांक enabled)
अणु
	u8 *tx_buf;
	पूर्णांक ret, i = 3, j;
	अचिन्हित दीर्घ numelements;
	पूर्णांक len;
	स्थिर दीर्घ *modemask;

	अगर (!enabled) अणु
		/* transition to buffered capture is not currently supported */
		st->setupbyte &= ~MAX1363_SETUP_MONITOR_SETUP;
		st->configbyte &= ~MAX1363_SCAN_MASK;
		st->monitor_on = false;
		वापस max1363_ग_लिखो_basic_config(st);
	पूर्ण

	/* Ensure we are in the relevant mode */
	st->setupbyte |= MAX1363_SETUP_MONITOR_SETUP;
	st->configbyte &= ~(MAX1363_CHANNEL_SEL_MASK
			    | MAX1363_SCAN_MASK
			| MAX1363_SE_DE_MASK);
	st->configbyte |= MAX1363_CONFIG_SCAN_MONITOR_MODE;
	अगर ((st->mask_low | st->mask_high) & 0x0F) अणु
		st->configbyte |= max1363_mode_table[s0to3].conf;
		modemask = max1363_mode_table[s0to3].modemask;
	पूर्ण अन्यथा अगर ((st->mask_low | st->mask_high) & 0x30) अणु
		st->configbyte |= max1363_mode_table[d0m1to2m3].conf;
		modemask = max1363_mode_table[d0m1to2m3].modemask;
	पूर्ण अन्यथा अणु
		st->configbyte |= max1363_mode_table[d1m0to3m2].conf;
		modemask = max1363_mode_table[d1m0to3m2].modemask;
	पूर्ण
	numelements = biपंचांगap_weight(modemask, MAX1363_MAX_CHANNELS);
	len = 3 * numelements + 3;
	tx_buf = kदो_स्मृति(len, GFP_KERNEL);
	अगर (!tx_buf) अणु
		ret = -ENOMEM;
		जाओ error_ret;
	पूर्ण
	tx_buf[0] = st->configbyte;
	tx_buf[1] = st->setupbyte;
	tx_buf[2] = (st->monitor_speed << 1);

	/*
	 * So we need to करो yet another bit of nefarious scan mode
	 * setup to match what we need.
	 */
	क्रम (j = 0; j < 8; j++)
		अगर (test_bit(j, modemask)) अणु
			/* Establish the mode is in the scan */
			अगर (st->mask_low & (1 << j)) अणु
				tx_buf[i] = (st->thresh_low[j] >> 4) & 0xFF;
				tx_buf[i + 1] = (st->thresh_low[j] << 4) & 0xF0;
			पूर्ण अन्यथा अगर (j < 4) अणु
				tx_buf[i] = 0;
				tx_buf[i + 1] = 0;
			पूर्ण अन्यथा अणु
				tx_buf[i] = 0x80;
				tx_buf[i + 1] = 0;
			पूर्ण
			अगर (st->mask_high & (1 << j)) अणु
				tx_buf[i + 1] |=
					(st->thresh_high[j] >> 8) & 0x0F;
				tx_buf[i + 2] = st->thresh_high[j] & 0xFF;
			पूर्ण अन्यथा अगर (j < 4) अणु
				tx_buf[i + 1] |= 0x0F;
				tx_buf[i + 2] = 0xFF;
			पूर्ण अन्यथा अणु
				tx_buf[i + 1] |= 0x07;
				tx_buf[i + 2] = 0xFF;
			पूर्ण
			i += 3;
		पूर्ण


	ret = st->send(st->client, tx_buf, len);
	अगर (ret < 0)
		जाओ error_ret;
	अगर (ret != len) अणु
		ret = -EIO;
		जाओ error_ret;
	पूर्ण

	/*
	 * Now that we hopefully have sensible thresholds in place it is
	 * समय to turn the पूर्णांकerrupts on.
	 * It is unclear from the data sheet अगर this should be necessary
	 * (i.e. whether monitor mode setup is atomic) but it appears to
	 * be in practice.
	 */
	tx_buf[0] = st->setupbyte;
	tx_buf[1] = MAX1363_MON_INT_ENABLE | (st->monitor_speed << 1) | 0xF0;
	ret = st->send(st->client, tx_buf, 2);
	अगर (ret < 0)
		जाओ error_ret;
	अगर (ret != 2) अणु
		ret = -EIO;
		जाओ error_ret;
	पूर्ण
	ret = 0;
	st->monitor_on = true;
error_ret:

	kमुक्त(tx_buf);

	वापस ret;
पूर्ण

/*
 * To keep this manageable we always use one of 3 scan modes.
 * Scan 0...3, 0-1,2-3 and 1-0,3-2
 */

अटल अंतरभूत पूर्णांक __max1363_check_event_mask(पूर्णांक thismask, पूर्णांक checkmask)
अणु
	पूर्णांक ret = 0;
	/* Is it unipolar */
	अगर (thismask < 4) अणु
		अगर (checkmask & ~0x0F) अणु
			ret = -EBUSY;
			जाओ error_ret;
		पूर्ण
	पूर्ण अन्यथा अगर (thismask < 6) अणु
		अगर (checkmask & ~0x30) अणु
			ret = -EBUSY;
			जाओ error_ret;
		पूर्ण
	पूर्ण अन्यथा अगर (checkmask & ~0xC0)
		ret = -EBUSY;
error_ret:
	वापस ret;
पूर्ण

अटल पूर्णांक max1363_ग_लिखो_event_config(काष्ठा iio_dev *indio_dev,
	स्थिर काष्ठा iio_chan_spec *chan, क्रमागत iio_event_type type,
	क्रमागत iio_event_direction dir, पूर्णांक state)
अणु
	पूर्णांक ret = 0;
	काष्ठा max1363_state *st = iio_priv(indio_dev);
	u16 unअगरiedmask;
	पूर्णांक number = chan->channel;

	ret = iio_device_claim_direct_mode(indio_dev);
	अगर (ret)
		वापस ret;
	mutex_lock(&st->lock);

	unअगरiedmask = st->mask_low | st->mask_high;
	अगर (dir == IIO_EV_सूची_FALLING) अणु

		अगर (state == 0)
			st->mask_low &= ~(1 << number);
		अन्यथा अणु
			ret = __max1363_check_event_mask((1 << number),
							 unअगरiedmask);
			अगर (ret)
				जाओ error_ret;
			st->mask_low |= (1 << number);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (state == 0)
			st->mask_high &= ~(1 << number);
		अन्यथा अणु
			ret = __max1363_check_event_mask((1 << number),
							 unअगरiedmask);
			अगर (ret)
				जाओ error_ret;
			st->mask_high |= (1 << number);
		पूर्ण
	पूर्ण

	max1363_monitor_mode_update(st, !!(st->mask_high | st->mask_low));
error_ret:
	mutex_unlock(&st->lock);
	iio_device_release_direct_mode(indio_dev);

	वापस ret;
पूर्ण

/*
 * As with scan_elements, only certain sets of these can
 * be combined.
 */
अटल काष्ठा attribute *max1363_event_attributes[] = अणु
	&iio_dev_attr_sampling_frequency.dev_attr.attr,
	&iio_स्थिर_attr_sampling_frequency_available.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group max1363_event_attribute_group = अणु
	.attrs = max1363_event_attributes,
पूर्ण;

अटल पूर्णांक max1363_update_scan_mode(काष्ठा iio_dev *indio_dev,
				    स्थिर अचिन्हित दीर्घ *scan_mask)
अणु
	काष्ठा max1363_state *st = iio_priv(indio_dev);

	/*
	 * Need to figure out the current mode based upon the requested
	 * scan mask in iio_dev
	 */
	st->current_mode = max1363_match_mode(scan_mask, st->chip_info);
	अगर (!st->current_mode)
		वापस -EINVAL;
	max1363_set_scan_mode(st);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा iio_info max1238_info = अणु
	.पढ़ो_raw = &max1363_पढ़ो_raw,
	.update_scan_mode = &max1363_update_scan_mode,
पूर्ण;

अटल स्थिर काष्ठा iio_info max1363_info = अणु
	.पढ़ो_event_value = &max1363_पढ़ो_thresh,
	.ग_लिखो_event_value = &max1363_ग_लिखो_thresh,
	.पढ़ो_event_config = &max1363_पढ़ो_event_config,
	.ग_लिखो_event_config = &max1363_ग_लिखो_event_config,
	.पढ़ो_raw = &max1363_पढ़ो_raw,
	.update_scan_mode = &max1363_update_scan_mode,
	.event_attrs = &max1363_event_attribute_group,
पूर्ण;

/* max1363 and max1368 tested - rest from data sheet */
अटल स्थिर काष्ठा max1363_chip_info max1363_chip_info_tbl[] = अणु
	[max1361] = अणु
		.bits = 10,
		.पूर्णांक_vref_mv = 2048,
		.mode_list = max1363_mode_list,
		.num_modes = ARRAY_SIZE(max1363_mode_list),
		.शेष_mode = s0to3,
		.channels = max1361_channels,
		.num_channels = ARRAY_SIZE(max1361_channels),
		.info = &max1363_info,
	पूर्ण,
	[max1362] = अणु
		.bits = 10,
		.पूर्णांक_vref_mv = 4096,
		.mode_list = max1363_mode_list,
		.num_modes = ARRAY_SIZE(max1363_mode_list),
		.शेष_mode = s0to3,
		.channels = max1361_channels,
		.num_channels = ARRAY_SIZE(max1361_channels),
		.info = &max1363_info,
	पूर्ण,
	[max1363] = अणु
		.bits = 12,
		.पूर्णांक_vref_mv = 2048,
		.mode_list = max1363_mode_list,
		.num_modes = ARRAY_SIZE(max1363_mode_list),
		.शेष_mode = s0to3,
		.channels = max1363_channels,
		.num_channels = ARRAY_SIZE(max1363_channels),
		.info = &max1363_info,
	पूर्ण,
	[max1364] = अणु
		.bits = 12,
		.पूर्णांक_vref_mv = 4096,
		.mode_list = max1363_mode_list,
		.num_modes = ARRAY_SIZE(max1363_mode_list),
		.शेष_mode = s0to3,
		.channels = max1363_channels,
		.num_channels = ARRAY_SIZE(max1363_channels),
		.info = &max1363_info,
	पूर्ण,
	[max1036] = अणु
		.bits = 8,
		.पूर्णांक_vref_mv = 4096,
		.mode_list = max1236_mode_list,
		.num_modes = ARRAY_SIZE(max1236_mode_list),
		.शेष_mode = s0to3,
		.info = &max1238_info,
		.channels = max1036_channels,
		.num_channels = ARRAY_SIZE(max1036_channels),
	पूर्ण,
	[max1037] = अणु
		.bits = 8,
		.पूर्णांक_vref_mv = 2048,
		.mode_list = max1236_mode_list,
		.num_modes = ARRAY_SIZE(max1236_mode_list),
		.शेष_mode = s0to3,
		.info = &max1238_info,
		.channels = max1036_channels,
		.num_channels = ARRAY_SIZE(max1036_channels),
	पूर्ण,
	[max1038] = अणु
		.bits = 8,
		.पूर्णांक_vref_mv = 4096,
		.mode_list = max1238_mode_list,
		.num_modes = ARRAY_SIZE(max1238_mode_list),
		.शेष_mode = s0to11,
		.info = &max1238_info,
		.channels = max1038_channels,
		.num_channels = ARRAY_SIZE(max1038_channels),
	पूर्ण,
	[max1039] = अणु
		.bits = 8,
		.पूर्णांक_vref_mv = 2048,
		.mode_list = max1238_mode_list,
		.num_modes = ARRAY_SIZE(max1238_mode_list),
		.शेष_mode = s0to11,
		.info = &max1238_info,
		.channels = max1038_channels,
		.num_channels = ARRAY_SIZE(max1038_channels),
	पूर्ण,
	[max1136] = अणु
		.bits = 10,
		.पूर्णांक_vref_mv = 4096,
		.mode_list = max1236_mode_list,
		.num_modes = ARRAY_SIZE(max1236_mode_list),
		.शेष_mode = s0to3,
		.info = &max1238_info,
		.channels = max1136_channels,
		.num_channels = ARRAY_SIZE(max1136_channels),
	पूर्ण,
	[max1137] = अणु
		.bits = 10,
		.पूर्णांक_vref_mv = 2048,
		.mode_list = max1236_mode_list,
		.num_modes = ARRAY_SIZE(max1236_mode_list),
		.शेष_mode = s0to3,
		.info = &max1238_info,
		.channels = max1136_channels,
		.num_channels = ARRAY_SIZE(max1136_channels),
	पूर्ण,
	[max1138] = अणु
		.bits = 10,
		.पूर्णांक_vref_mv = 4096,
		.mode_list = max1238_mode_list,
		.num_modes = ARRAY_SIZE(max1238_mode_list),
		.शेष_mode = s0to11,
		.info = &max1238_info,
		.channels = max1138_channels,
		.num_channels = ARRAY_SIZE(max1138_channels),
	पूर्ण,
	[max1139] = अणु
		.bits = 10,
		.पूर्णांक_vref_mv = 2048,
		.mode_list = max1238_mode_list,
		.num_modes = ARRAY_SIZE(max1238_mode_list),
		.शेष_mode = s0to11,
		.info = &max1238_info,
		.channels = max1138_channels,
		.num_channels = ARRAY_SIZE(max1138_channels),
	पूर्ण,
	[max1236] = अणु
		.bits = 12,
		.पूर्णांक_vref_mv = 4096,
		.mode_list = max1236_mode_list,
		.num_modes = ARRAY_SIZE(max1236_mode_list),
		.शेष_mode = s0to3,
		.info = &max1238_info,
		.channels = max1236_channels,
		.num_channels = ARRAY_SIZE(max1236_channels),
	पूर्ण,
	[max1237] = अणु
		.bits = 12,
		.पूर्णांक_vref_mv = 2048,
		.mode_list = max1236_mode_list,
		.num_modes = ARRAY_SIZE(max1236_mode_list),
		.शेष_mode = s0to3,
		.info = &max1238_info,
		.channels = max1236_channels,
		.num_channels = ARRAY_SIZE(max1236_channels),
	पूर्ण,
	[max1238] = अणु
		.bits = 12,
		.पूर्णांक_vref_mv = 4096,
		.mode_list = max1238_mode_list,
		.num_modes = ARRAY_SIZE(max1238_mode_list),
		.शेष_mode = s0to11,
		.info = &max1238_info,
		.channels = max1238_channels,
		.num_channels = ARRAY_SIZE(max1238_channels),
	पूर्ण,
	[max1239] = अणु
		.bits = 12,
		.पूर्णांक_vref_mv = 2048,
		.mode_list = max1238_mode_list,
		.num_modes = ARRAY_SIZE(max1238_mode_list),
		.शेष_mode = s0to11,
		.info = &max1238_info,
		.channels = max1238_channels,
		.num_channels = ARRAY_SIZE(max1238_channels),
	पूर्ण,
	[max11600] = अणु
		.bits = 8,
		.पूर्णांक_vref_mv = 4096,
		.mode_list = max11607_mode_list,
		.num_modes = ARRAY_SIZE(max11607_mode_list),
		.शेष_mode = s0to3,
		.info = &max1238_info,
		.channels = max1036_channels,
		.num_channels = ARRAY_SIZE(max1036_channels),
	पूर्ण,
	[max11601] = अणु
		.bits = 8,
		.पूर्णांक_vref_mv = 2048,
		.mode_list = max11607_mode_list,
		.num_modes = ARRAY_SIZE(max11607_mode_list),
		.शेष_mode = s0to3,
		.info = &max1238_info,
		.channels = max1036_channels,
		.num_channels = ARRAY_SIZE(max1036_channels),
	पूर्ण,
	[max11602] = अणु
		.bits = 8,
		.पूर्णांक_vref_mv = 4096,
		.mode_list = max11608_mode_list,
		.num_modes = ARRAY_SIZE(max11608_mode_list),
		.शेष_mode = s0to7,
		.info = &max1238_info,
		.channels = max11602_channels,
		.num_channels = ARRAY_SIZE(max11602_channels),
	पूर्ण,
	[max11603] = अणु
		.bits = 8,
		.पूर्णांक_vref_mv = 2048,
		.mode_list = max11608_mode_list,
		.num_modes = ARRAY_SIZE(max11608_mode_list),
		.शेष_mode = s0to7,
		.info = &max1238_info,
		.channels = max11602_channels,
		.num_channels = ARRAY_SIZE(max11602_channels),
	पूर्ण,
	[max11604] = अणु
		.bits = 8,
		.पूर्णांक_vref_mv = 4096,
		.mode_list = max1238_mode_list,
		.num_modes = ARRAY_SIZE(max1238_mode_list),
		.शेष_mode = s0to11,
		.info = &max1238_info,
		.channels = max1038_channels,
		.num_channels = ARRAY_SIZE(max1038_channels),
	पूर्ण,
	[max11605] = अणु
		.bits = 8,
		.पूर्णांक_vref_mv = 2048,
		.mode_list = max1238_mode_list,
		.num_modes = ARRAY_SIZE(max1238_mode_list),
		.शेष_mode = s0to11,
		.info = &max1238_info,
		.channels = max1038_channels,
		.num_channels = ARRAY_SIZE(max1038_channels),
	पूर्ण,
	[max11606] = अणु
		.bits = 10,
		.पूर्णांक_vref_mv = 4096,
		.mode_list = max11607_mode_list,
		.num_modes = ARRAY_SIZE(max11607_mode_list),
		.शेष_mode = s0to3,
		.info = &max1238_info,
		.channels = max1136_channels,
		.num_channels = ARRAY_SIZE(max1136_channels),
	पूर्ण,
	[max11607] = अणु
		.bits = 10,
		.पूर्णांक_vref_mv = 2048,
		.mode_list = max11607_mode_list,
		.num_modes = ARRAY_SIZE(max11607_mode_list),
		.शेष_mode = s0to3,
		.info = &max1238_info,
		.channels = max1136_channels,
		.num_channels = ARRAY_SIZE(max1136_channels),
	पूर्ण,
	[max11608] = अणु
		.bits = 10,
		.पूर्णांक_vref_mv = 4096,
		.mode_list = max11608_mode_list,
		.num_modes = ARRAY_SIZE(max11608_mode_list),
		.शेष_mode = s0to7,
		.info = &max1238_info,
		.channels = max11608_channels,
		.num_channels = ARRAY_SIZE(max11608_channels),
	पूर्ण,
	[max11609] = अणु
		.bits = 10,
		.पूर्णांक_vref_mv = 2048,
		.mode_list = max11608_mode_list,
		.num_modes = ARRAY_SIZE(max11608_mode_list),
		.शेष_mode = s0to7,
		.info = &max1238_info,
		.channels = max11608_channels,
		.num_channels = ARRAY_SIZE(max11608_channels),
	पूर्ण,
	[max11610] = अणु
		.bits = 10,
		.पूर्णांक_vref_mv = 4096,
		.mode_list = max1238_mode_list,
		.num_modes = ARRAY_SIZE(max1238_mode_list),
		.शेष_mode = s0to11,
		.info = &max1238_info,
		.channels = max1138_channels,
		.num_channels = ARRAY_SIZE(max1138_channels),
	पूर्ण,
	[max11611] = अणु
		.bits = 10,
		.पूर्णांक_vref_mv = 2048,
		.mode_list = max1238_mode_list,
		.num_modes = ARRAY_SIZE(max1238_mode_list),
		.शेष_mode = s0to11,
		.info = &max1238_info,
		.channels = max1138_channels,
		.num_channels = ARRAY_SIZE(max1138_channels),
	पूर्ण,
	[max11612] = अणु
		.bits = 12,
		.पूर्णांक_vref_mv = 4096,
		.mode_list = max11607_mode_list,
		.num_modes = ARRAY_SIZE(max11607_mode_list),
		.शेष_mode = s0to3,
		.info = &max1238_info,
		.channels = max1363_channels,
		.num_channels = ARRAY_SIZE(max1363_channels),
	पूर्ण,
	[max11613] = अणु
		.bits = 12,
		.पूर्णांक_vref_mv = 2048,
		.mode_list = max11607_mode_list,
		.num_modes = ARRAY_SIZE(max11607_mode_list),
		.शेष_mode = s0to3,
		.info = &max1238_info,
		.channels = max1363_channels,
		.num_channels = ARRAY_SIZE(max1363_channels),
	पूर्ण,
	[max11614] = अणु
		.bits = 12,
		.पूर्णांक_vref_mv = 4096,
		.mode_list = max11608_mode_list,
		.num_modes = ARRAY_SIZE(max11608_mode_list),
		.शेष_mode = s0to7,
		.info = &max1238_info,
		.channels = max11614_channels,
		.num_channels = ARRAY_SIZE(max11614_channels),
	पूर्ण,
	[max11615] = अणु
		.bits = 12,
		.पूर्णांक_vref_mv = 2048,
		.mode_list = max11608_mode_list,
		.num_modes = ARRAY_SIZE(max11608_mode_list),
		.शेष_mode = s0to7,
		.info = &max1238_info,
		.channels = max11614_channels,
		.num_channels = ARRAY_SIZE(max11614_channels),
	पूर्ण,
	[max11616] = अणु
		.bits = 12,
		.पूर्णांक_vref_mv = 4096,
		.mode_list = max1238_mode_list,
		.num_modes = ARRAY_SIZE(max1238_mode_list),
		.शेष_mode = s0to11,
		.info = &max1238_info,
		.channels = max1238_channels,
		.num_channels = ARRAY_SIZE(max1238_channels),
	पूर्ण,
	[max11617] = अणु
		.bits = 12,
		.पूर्णांक_vref_mv = 2048,
		.mode_list = max1238_mode_list,
		.num_modes = ARRAY_SIZE(max1238_mode_list),
		.शेष_mode = s0to11,
		.info = &max1238_info,
		.channels = max1238_channels,
		.num_channels = ARRAY_SIZE(max1238_channels),
	पूर्ण,
	[max11644] = अणु
		.bits = 12,
		.पूर्णांक_vref_mv = 4096,
		.mode_list = max11644_mode_list,
		.num_modes = ARRAY_SIZE(max11644_mode_list),
		.शेष_mode = s0to1,
		.info = &max1238_info,
		.channels = max11644_channels,
		.num_channels = ARRAY_SIZE(max11644_channels),
	पूर्ण,
	[max11645] = अणु
		.bits = 12,
		.पूर्णांक_vref_mv = 2048,
		.mode_list = max11644_mode_list,
		.num_modes = ARRAY_SIZE(max11644_mode_list),
		.शेष_mode = s0to1,
		.info = &max1238_info,
		.channels = max11644_channels,
		.num_channels = ARRAY_SIZE(max11644_channels),
	पूर्ण,
	[max11646] = अणु
		.bits = 10,
		.पूर्णांक_vref_mv = 4096,
		.mode_list = max11644_mode_list,
		.num_modes = ARRAY_SIZE(max11644_mode_list),
		.शेष_mode = s0to1,
		.info = &max1238_info,
		.channels = max11646_channels,
		.num_channels = ARRAY_SIZE(max11646_channels),
	पूर्ण,
	[max11647] = अणु
		.bits = 10,
		.पूर्णांक_vref_mv = 2048,
		.mode_list = max11644_mode_list,
		.num_modes = ARRAY_SIZE(max11644_mode_list),
		.शेष_mode = s0to1,
		.info = &max1238_info,
		.channels = max11646_channels,
		.num_channels = ARRAY_SIZE(max11646_channels),
	पूर्ण,
पूर्ण;

अटल पूर्णांक max1363_initial_setup(काष्ठा max1363_state *st)
अणु
	st->setupbyte = MAX1363_SETUP_INT_CLOCK
		| MAX1363_SETUP_UNIPOLAR
		| MAX1363_SETUP_NORESET;

	अगर (st->vref)
		st->setupbyte |= MAX1363_SETUP_AIN3_IS_REF_EXT_TO_REF;
	अन्यथा
		st->setupbyte |= MAX1363_SETUP_POWER_UP_INT_REF
		  | MAX1363_SETUP_AIN3_IS_AIN3_REF_IS_INT;

	/* Set scan mode ग_लिखोs the config anyway so रुको until then */
	st->setupbyte = MAX1363_SETUP_BYTE(st->setupbyte);
	st->current_mode = &max1363_mode_table[st->chip_info->शेष_mode];
	st->configbyte = MAX1363_CONFIG_BYTE(st->configbyte);

	वापस max1363_set_scan_mode(st);
पूर्ण

अटल पूर्णांक max1363_alloc_scan_masks(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा max1363_state *st = iio_priv(indio_dev);
	अचिन्हित दीर्घ *masks;
	पूर्णांक i;

	masks = devm_kzalloc(&indio_dev->dev,
			array3_size(BITS_TO_LONGS(MAX1363_MAX_CHANNELS),
				    माप(दीर्घ),
				    st->chip_info->num_modes + 1),
			GFP_KERNEL);
	अगर (!masks)
		वापस -ENOMEM;

	क्रम (i = 0; i < st->chip_info->num_modes; i++)
		biपंचांगap_copy(masks + BITS_TO_LONGS(MAX1363_MAX_CHANNELS)*i,
			    max1363_mode_table[st->chip_info->mode_list[i]]
			    .modemask, MAX1363_MAX_CHANNELS);

	indio_dev->available_scan_masks = masks;

	वापस 0;
पूर्ण

अटल irqवापस_t max1363_trigger_handler(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा iio_poll_func *pf = p;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा max1363_state *st = iio_priv(indio_dev);
	__u8 *rxbuf;
	पूर्णांक b_sent;
	माप_प्रकार d_size;
	अचिन्हित दीर्घ numvals = biपंचांगap_weight(st->current_mode->modemask,
					      MAX1363_MAX_CHANNELS);

	/* Ensure the बारtamp is 8 byte aligned */
	अगर (st->chip_info->bits != 8)
		d_size = numvals*2;
	अन्यथा
		d_size = numvals;
	अगर (indio_dev->scan_बारtamp) अणु
		d_size += माप(s64);
		अगर (d_size % माप(s64))
			d_size += माप(s64) - (d_size % माप(s64));
	पूर्ण
	/* Monitor mode prevents पढ़ोing. Whilst not currently implemented
	 * might as well have this test in here in the meanसमय as it करोes
	 * no harm.
	 */
	अगर (numvals == 0)
		जाओ करोne;

	rxbuf = kदो_स्मृति(d_size,	GFP_KERNEL);
	अगर (rxbuf == शून्य)
		जाओ करोne;
	अगर (st->chip_info->bits != 8)
		b_sent = st->recv(st->client, rxbuf, numvals * 2);
	अन्यथा
		b_sent = st->recv(st->client, rxbuf, numvals);
	अगर (b_sent < 0)
		जाओ करोne_मुक्त;

	iio_push_to_buffers_with_बारtamp(indio_dev, rxbuf,
					   iio_get_समय_ns(indio_dev));

करोne_मुक्त:
	kमुक्त(rxbuf);
करोne:
	iio_trigger_notअगरy_करोne(indio_dev->trig);

	वापस IRQ_HANDLED;
पूर्ण

#घोषणा MAX1363_COMPATIBLE(of_compatible, cfg) अणु		\
			.compatible = of_compatible,		\
			.data = &max1363_chip_info_tbl[cfg],	\
पूर्ण

अटल स्थिर काष्ठा of_device_id max1363_of_match[] = अणु
	MAX1363_COMPATIBLE("maxim,max1361", max1361),
	MAX1363_COMPATIBLE("maxim,max1362", max1362),
	MAX1363_COMPATIBLE("maxim,max1363", max1363),
	MAX1363_COMPATIBLE("maxim,max1364", max1364),
	MAX1363_COMPATIBLE("maxim,max1036", max1036),
	MAX1363_COMPATIBLE("maxim,max1037", max1037),
	MAX1363_COMPATIBLE("maxim,max1038", max1038),
	MAX1363_COMPATIBLE("maxim,max1039", max1039),
	MAX1363_COMPATIBLE("maxim,max1136", max1136),
	MAX1363_COMPATIBLE("maxim,max1137", max1137),
	MAX1363_COMPATIBLE("maxim,max1138", max1138),
	MAX1363_COMPATIBLE("maxim,max1139", max1139),
	MAX1363_COMPATIBLE("maxim,max1236", max1236),
	MAX1363_COMPATIBLE("maxim,max1237", max1237),
	MAX1363_COMPATIBLE("maxim,max1238", max1238),
	MAX1363_COMPATIBLE("maxim,max1239", max1239),
	MAX1363_COMPATIBLE("maxim,max11600", max11600),
	MAX1363_COMPATIBLE("maxim,max11601", max11601),
	MAX1363_COMPATIBLE("maxim,max11602", max11602),
	MAX1363_COMPATIBLE("maxim,max11603", max11603),
	MAX1363_COMPATIBLE("maxim,max11604", max11604),
	MAX1363_COMPATIBLE("maxim,max11605", max11605),
	MAX1363_COMPATIBLE("maxim,max11606", max11606),
	MAX1363_COMPATIBLE("maxim,max11607", max11607),
	MAX1363_COMPATIBLE("maxim,max11608", max11608),
	MAX1363_COMPATIBLE("maxim,max11609", max11609),
	MAX1363_COMPATIBLE("maxim,max11610", max11610),
	MAX1363_COMPATIBLE("maxim,max11611", max11611),
	MAX1363_COMPATIBLE("maxim,max11612", max11612),
	MAX1363_COMPATIBLE("maxim,max11613", max11613),
	MAX1363_COMPATIBLE("maxim,max11614", max11614),
	MAX1363_COMPATIBLE("maxim,max11615", max11615),
	MAX1363_COMPATIBLE("maxim,max11616", max11616),
	MAX1363_COMPATIBLE("maxim,max11617", max11617),
	MAX1363_COMPATIBLE("maxim,max11644", max11644),
	MAX1363_COMPATIBLE("maxim,max11645", max11645),
	MAX1363_COMPATIBLE("maxim,max11646", max11646),
	MAX1363_COMPATIBLE("maxim,max11647", max11647),
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, max1363_of_match);

अटल पूर्णांक max1363_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	पूर्णांक ret;
	काष्ठा max1363_state *st;
	काष्ठा iio_dev *indio_dev;
	काष्ठा regulator *vref;

	indio_dev = devm_iio_device_alloc(&client->dev,
					  माप(काष्ठा max1363_state));
	अगर (!indio_dev)
		वापस -ENOMEM;

	ret = iio_map_array_रेजिस्टर(indio_dev, client->dev.platक्रमm_data);
	अगर (ret < 0)
		वापस ret;

	st = iio_priv(indio_dev);

	mutex_init(&st->lock);
	st->reg = devm_regulator_get(&client->dev, "vcc");
	अगर (IS_ERR(st->reg)) अणु
		ret = PTR_ERR(st->reg);
		जाओ error_unरेजिस्टर_map;
	पूर्ण

	ret = regulator_enable(st->reg);
	अगर (ret)
		जाओ error_unरेजिस्टर_map;

	/* this is only used क्रम device removal purposes */
	i2c_set_clientdata(client, indio_dev);

	st->chip_info = device_get_match_data(&client->dev);
	अगर (!st->chip_info)
		st->chip_info = &max1363_chip_info_tbl[id->driver_data];
	st->client = client;

	st->vref_uv = st->chip_info->पूर्णांक_vref_mv * 1000;
	vref = devm_regulator_get_optional(&client->dev, "vref");
	अगर (!IS_ERR(vref)) अणु
		पूर्णांक vref_uv;

		ret = regulator_enable(vref);
		अगर (ret)
			जाओ error_disable_reg;
		st->vref = vref;
		vref_uv = regulator_get_voltage(vref);
		अगर (vref_uv <= 0) अणु
			ret = -EINVAL;
			जाओ error_disable_reg;
		पूर्ण
		st->vref_uv = vref_uv;
	पूर्ण

	अगर (i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) अणु
		st->send = i2c_master_send;
		st->recv = i2c_master_recv;
	पूर्ण अन्यथा अगर (i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_BYTE)
			&& st->chip_info->bits == 8) अणु
		st->send = max1363_smbus_send;
		st->recv = max1363_smbus_recv;
	पूर्ण अन्यथा अणु
		ret = -EOPNOTSUPP;
		जाओ error_disable_reg;
	पूर्ण

	ret = max1363_alloc_scan_masks(indio_dev);
	अगर (ret)
		जाओ error_disable_reg;

	indio_dev->name = id->name;
	indio_dev->channels = st->chip_info->channels;
	indio_dev->num_channels = st->chip_info->num_channels;
	indio_dev->info = st->chip_info->info;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	ret = max1363_initial_setup(st);
	अगर (ret < 0)
		जाओ error_disable_reg;

	ret = iio_triggered_buffer_setup(indio_dev, शून्य,
		&max1363_trigger_handler, शून्य);
	अगर (ret)
		जाओ error_disable_reg;

	अगर (client->irq) अणु
		ret = devm_request_thपढ़ोed_irq(&client->dev, st->client->irq,
					   शून्य,
					   &max1363_event_handler,
					   IRQF_TRIGGER_RISING | IRQF_ONESHOT,
					   "max1363_event",
					   indio_dev);

		अगर (ret)
			जाओ error_uninit_buffer;
	पूर्ण

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret < 0)
		जाओ error_uninit_buffer;

	वापस 0;

error_uninit_buffer:
	iio_triggered_buffer_cleanup(indio_dev);
error_disable_reg:
	अगर (st->vref)
		regulator_disable(st->vref);
	regulator_disable(st->reg);
error_unरेजिस्टर_map:
	iio_map_array_unरेजिस्टर(indio_dev);
	वापस ret;
पूर्ण

अटल पूर्णांक max1363_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(client);
	काष्ठा max1363_state *st = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);
	iio_triggered_buffer_cleanup(indio_dev);
	अगर (st->vref)
		regulator_disable(st->vref);
	regulator_disable(st->reg);
	iio_map_array_unरेजिस्टर(indio_dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id max1363_id[] = अणु
	अणु "max1361", max1361 पूर्ण,
	अणु "max1362", max1362 पूर्ण,
	अणु "max1363", max1363 पूर्ण,
	अणु "max1364", max1364 पूर्ण,
	अणु "max1036", max1036 पूर्ण,
	अणु "max1037", max1037 पूर्ण,
	अणु "max1038", max1038 पूर्ण,
	अणु "max1039", max1039 पूर्ण,
	अणु "max1136", max1136 पूर्ण,
	अणु "max1137", max1137 पूर्ण,
	अणु "max1138", max1138 पूर्ण,
	अणु "max1139", max1139 पूर्ण,
	अणु "max1236", max1236 पूर्ण,
	अणु "max1237", max1237 पूर्ण,
	अणु "max1238", max1238 पूर्ण,
	अणु "max1239", max1239 पूर्ण,
	अणु "max11600", max11600 पूर्ण,
	अणु "max11601", max11601 पूर्ण,
	अणु "max11602", max11602 पूर्ण,
	अणु "max11603", max11603 पूर्ण,
	अणु "max11604", max11604 पूर्ण,
	अणु "max11605", max11605 पूर्ण,
	अणु "max11606", max11606 पूर्ण,
	अणु "max11607", max11607 पूर्ण,
	अणु "max11608", max11608 पूर्ण,
	अणु "max11609", max11609 पूर्ण,
	अणु "max11610", max11610 पूर्ण,
	अणु "max11611", max11611 पूर्ण,
	अणु "max11612", max11612 पूर्ण,
	अणु "max11613", max11613 पूर्ण,
	अणु "max11614", max11614 पूर्ण,
	अणु "max11615", max11615 पूर्ण,
	अणु "max11616", max11616 पूर्ण,
	अणु "max11617", max11617 पूर्ण,
	अणु "max11644", max11644 पूर्ण,
	अणु "max11645", max11645 पूर्ण,
	अणु "max11646", max11646 पूर्ण,
	अणु "max11647", max11647 पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, max1363_id);

अटल काष्ठा i2c_driver max1363_driver = अणु
	.driver = अणु
		.name = "max1363",
		.of_match_table = max1363_of_match,
	पूर्ण,
	.probe = max1363_probe,
	.हटाओ = max1363_हटाओ,
	.id_table = max1363_id,
पूर्ण;
module_i2c_driver(max1363_driver);

MODULE_AUTHOR("Jonathan Cameron <jic23@kernel.org>");
MODULE_DESCRIPTION("Maxim 1363 ADC");
MODULE_LICENSE("GPL v2");
