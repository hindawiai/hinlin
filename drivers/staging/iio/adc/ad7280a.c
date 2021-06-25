<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * AD7280A Lithium Ion Battery Monitoring System
 *
 * Copyright 2011 Analog Devices Inc.
 */

#समावेश <linux/crc8.h>
#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/err.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/events.h>

#समावेश "ad7280a.h"

/* Registers */
#घोषणा AD7280A_CELL_VOLTAGE_1		0x0  /* D11 to D0, Read only */
#घोषणा AD7280A_CELL_VOLTAGE_2		0x1  /* D11 to D0, Read only */
#घोषणा AD7280A_CELL_VOLTAGE_3		0x2  /* D11 to D0, Read only */
#घोषणा AD7280A_CELL_VOLTAGE_4		0x3  /* D11 to D0, Read only */
#घोषणा AD7280A_CELL_VOLTAGE_5		0x4  /* D11 to D0, Read only */
#घोषणा AD7280A_CELL_VOLTAGE_6		0x5  /* D11 to D0, Read only */
#घोषणा AD7280A_AUX_ADC_1		0x6  /* D11 to D0, Read only */
#घोषणा AD7280A_AUX_ADC_2		0x7  /* D11 to D0, Read only */
#घोषणा AD7280A_AUX_ADC_3		0x8  /* D11 to D0, Read only */
#घोषणा AD7280A_AUX_ADC_4		0x9  /* D11 to D0, Read only */
#घोषणा AD7280A_AUX_ADC_5		0xA  /* D11 to D0, Read only */
#घोषणा AD7280A_AUX_ADC_6		0xB  /* D11 to D0, Read only */
#घोषणा AD7280A_SELF_TEST		0xC  /* D11 to D0, Read only */
#घोषणा AD7280A_CONTROL_HB		0xD  /* D15 to D8, Read/ग_लिखो */
#घोषणा AD7280A_CONTROL_LB		0xE  /* D7 to D0, Read/ग_लिखो */
#घोषणा AD7280A_CELL_OVERVOLTAGE	0xF  /* D7 to D0, Read/ग_लिखो */
#घोषणा AD7280A_CELL_UNDERVOLTAGE	0x10 /* D7 to D0, Read/ग_लिखो */
#घोषणा AD7280A_AUX_ADC_OVERVOLTAGE	0x11 /* D7 to D0, Read/ग_लिखो */
#घोषणा AD7280A_AUX_ADC_UNDERVOLTAGE	0x12 /* D7 to D0, Read/ग_लिखो */
#घोषणा AD7280A_ALERT			0x13 /* D7 to D0, Read/ग_लिखो */
#घोषणा AD7280A_CELL_BALANCE		0x14 /* D7 to D0, Read/ग_लिखो */
#घोषणा AD7280A_CB1_TIMER		0x15 /* D7 to D0, Read/ग_लिखो */
#घोषणा AD7280A_CB2_TIMER		0x16 /* D7 to D0, Read/ग_लिखो */
#घोषणा AD7280A_CB3_TIMER		0x17 /* D7 to D0, Read/ग_लिखो */
#घोषणा AD7280A_CB4_TIMER		0x18 /* D7 to D0, Read/ग_लिखो */
#घोषणा AD7280A_CB5_TIMER		0x19 /* D7 to D0, Read/ग_लिखो */
#घोषणा AD7280A_CB6_TIMER		0x1A /* D7 to D0, Read/ग_लिखो */
#घोषणा AD7280A_PD_TIMER		0x1B /* D7 to D0, Read/ग_लिखो */
#घोषणा AD7280A_READ			0x1C /* D7 to D0, Read/ग_लिखो */
#घोषणा AD7280A_CNVST_CONTROL		0x1D /* D7 to D0, Read/ग_लिखो */

/* Bits and Masks */
#घोषणा AD7280A_CTRL_HB_CONV_INPUT_ALL			0
#घोषणा AD7280A_CTRL_HB_CONV_INPUT_6CELL_AUX1_3_4	BIT(6)
#घोषणा AD7280A_CTRL_HB_CONV_INPUT_6CELL		BIT(7)
#घोषणा AD7280A_CTRL_HB_CONV_INPUT_SELF_TEST		(BIT(7) | BIT(6))
#घोषणा AD7280A_CTRL_HB_CONV_RES_READ_ALL		0
#घोषणा AD7280A_CTRL_HB_CONV_RES_READ_6CELL_AUX1_3_4	BIT(4)
#घोषणा AD7280A_CTRL_HB_CONV_RES_READ_6CELL		BIT(5)
#घोषणा AD7280A_CTRL_HB_CONV_RES_READ_NO		(BIT(5) | BIT(4))
#घोषणा AD7280A_CTRL_HB_CONV_START_CNVST		0
#घोषणा AD7280A_CTRL_HB_CONV_START_CS			BIT(3)
#घोषणा AD7280A_CTRL_HB_CONV_AVG_DIS			0
#घोषणा AD7280A_CTRL_HB_CONV_AVG_2			BIT(1)
#घोषणा AD7280A_CTRL_HB_CONV_AVG_4			BIT(2)
#घोषणा AD7280A_CTRL_HB_CONV_AVG_8			(BIT(2) | BIT(1))
#घोषणा AD7280A_CTRL_HB_CONV_AVG(x)			((x) << 1)
#घोषणा AD7280A_CTRL_HB_PWRDN_SW			BIT(0)

#घोषणा AD7280A_CTRL_LB_SWRST				BIT(7)
#घोषणा AD7280A_CTRL_LB_ACQ_TIME_400ns			0
#घोषणा AD7280A_CTRL_LB_ACQ_TIME_800ns			BIT(5)
#घोषणा AD7280A_CTRL_LB_ACQ_TIME_1200ns			BIT(6)
#घोषणा AD7280A_CTRL_LB_ACQ_TIME_1600ns			(BIT(6) | BIT(5))
#घोषणा AD7280A_CTRL_LB_ACQ_TIME(x)			((x) << 5)
#घोषणा AD7280A_CTRL_LB_MUST_SET			BIT(4)
#घोषणा AD7280A_CTRL_LB_THERMISTOR_EN			BIT(3)
#घोषणा AD7280A_CTRL_LB_LOCK_DEV_ADDR			BIT(2)
#घोषणा AD7280A_CTRL_LB_INC_DEV_ADDR			BIT(1)
#घोषणा AD7280A_CTRL_LB_DAISY_CHAIN_RB_EN		BIT(0)

#घोषणा AD7280A_ALERT_GEN_STATIC_HIGH			BIT(6)
#घोषणा AD7280A_ALERT_RELAY_SIG_CHAIN_DOWN		(BIT(7) | BIT(6))

#घोषणा AD7280A_ALL_CELLS				(0xAD << 16)

#घोषणा AD7280A_MAX_SPI_CLK_HZ		700000 /* < 1MHz */
#घोषणा AD7280A_MAX_CHAIN		8
#घोषणा AD7280A_CELLS_PER_DEV		6
#घोषणा AD7280A_BITS			12
#घोषणा AD7280A_NUM_CH			(AD7280A_AUX_ADC_6 - \
					AD7280A_CELL_VOLTAGE_1 + 1)

#घोषणा AD7280A_CALC_VOLTAGE_CHAN_NUM(d, c) (((d) * AD7280A_CELLS_PER_DEV) + \
					     (c))
#घोषणा AD7280A_CALC_TEMP_CHAN_NUM(d, c)    (((d) * AD7280A_CELLS_PER_DEV) + \
					     (c) - AD7280A_CELLS_PER_DEV)

#घोषणा AD7280A_DEVADDR_MASTER		0
#घोषणा AD7280A_DEVADDR_ALL		0x1F
/* 5-bit device address is sent LSB first */
अटल अचिन्हित पूर्णांक ad7280a_devaddr(अचिन्हित पूर्णांक addr)
अणु
	वापस ((addr & 0x1) << 4) |
	       ((addr & 0x2) << 3) |
	       (addr & 0x4) |
	       ((addr & 0x8) >> 3) |
	       ((addr & 0x10) >> 4);
पूर्ण

/* During a पढ़ो a valid ग_लिखो is mandatory.
 * So writing to the highest available address (Address 0x1F)
 * and setting the address all parts bit to 0 is recommended
 * So the TXVAL is AD7280A_DEVADDR_ALL + CRC
 */
#घोषणा AD7280A_READ_TXVAL	0xF800030A

/*
 * AD7280 CRC
 *
 * P(x) = x^8 + x^5 + x^3 + x^2 + x^1 + x^0 = 0b100101111 => 0x2F
 */
#घोषणा POLYNOM		0x2F

काष्ठा ad7280_state अणु
	काष्ठा spi_device		*spi;
	काष्ठा iio_chan_spec		*channels;
	काष्ठा iio_dev_attr		*iio_attr;
	पूर्णांक				slave_num;
	पूर्णांक				scan_cnt;
	पूर्णांक				पढ़ोback_delay_us;
	अचिन्हित अक्षर			crc_tab[CRC8_TABLE_SIZE];
	अचिन्हित अक्षर			ctrl_hb;
	अचिन्हित अक्षर			ctrl_lb;
	अचिन्हित अक्षर			cell_threshhigh;
	अचिन्हित अक्षर			cell_threshlow;
	अचिन्हित अक्षर			aux_threshhigh;
	अचिन्हित अक्षर			aux_threshlow;
	अचिन्हित अक्षर			cb_mask[AD7280A_MAX_CHAIN];
	काष्ठा mutex			lock; /* protect sensor state */

	__be32				buf[2] ____cacheline_aligned;
पूर्ण;

अटल अचिन्हित अक्षर ad7280_calc_crc8(अचिन्हित अक्षर *crc_tab, अचिन्हित पूर्णांक val)
अणु
	अचिन्हित अक्षर crc;

	crc = crc_tab[val >> 16 & 0xFF];
	crc = crc_tab[crc ^ (val >> 8 & 0xFF)];

	वापस  crc ^ (val & 0xFF);
पूर्ण

अटल पूर्णांक ad7280_check_crc(काष्ठा ad7280_state *st, अचिन्हित पूर्णांक val)
अणु
	अचिन्हित अक्षर crc = ad7280_calc_crc8(st->crc_tab, val >> 10);

	अगर (crc != ((val >> 2) & 0xFF))
		वापस -EIO;

	वापस 0;
पूर्ण

/* After initiating a conversion sequence we need to रुको until the
 * conversion is करोne. The delay is typically in the range of 15..30 us
 * however depending an the number of devices in the daisy chain and the
 * number of averages taken, conversion delays and acquisition समय options
 * it may take up to 250us, in this हाल we better sleep instead of busy
 * रुको.
 */

अटल व्योम ad7280_delay(काष्ठा ad7280_state *st)
अणु
	अगर (st->पढ़ोback_delay_us < 50)
		udelay(st->पढ़ोback_delay_us);
	अन्यथा
		usleep_range(250, 500);
पूर्ण

अटल पूर्णांक __ad7280_पढ़ो32(काष्ठा ad7280_state *st, अचिन्हित पूर्णांक *val)
अणु
	पूर्णांक ret;
	काष्ठा spi_transfer t = अणु
		.tx_buf	= &st->buf[0],
		.rx_buf = &st->buf[1],
		.len = 4,
	पूर्ण;

	st->buf[0] = cpu_to_be32(AD7280A_READ_TXVAL);

	ret = spi_sync_transfer(st->spi, &t, 1);
	अगर (ret)
		वापस ret;

	*val = be32_to_cpu(st->buf[1]);

	वापस 0;
पूर्ण

अटल पूर्णांक ad7280_ग_लिखो(काष्ठा ad7280_state *st, अचिन्हित पूर्णांक devaddr,
			अचिन्हित पूर्णांक addr, bool all, अचिन्हित पूर्णांक val)
अणु
	अचिन्हित पूर्णांक reg = devaddr << 27 | addr << 21 |
			(val & 0xFF) << 13 | all << 12;

	reg |= ad7280_calc_crc8(st->crc_tab, reg >> 11) << 3 | 0x2;
	st->buf[0] = cpu_to_be32(reg);

	वापस spi_ग_लिखो(st->spi, &st->buf[0], 4);
पूर्ण

अटल पूर्णांक ad7280_पढ़ो(काष्ठा ad7280_state *st, अचिन्हित पूर्णांक devaddr,
		       अचिन्हित पूर्णांक addr)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक पंचांगp;

	/* turns off the पढ़ो operation on all parts */
	ret = ad7280_ग_लिखो(st, AD7280A_DEVADDR_MASTER, AD7280A_CONTROL_HB, 1,
			   AD7280A_CTRL_HB_CONV_INPUT_ALL |
			   AD7280A_CTRL_HB_CONV_RES_READ_NO |
			   st->ctrl_hb);
	अगर (ret)
		वापस ret;

	/* turns on the पढ़ो operation on the addressed part */
	ret = ad7280_ग_लिखो(st, devaddr, AD7280A_CONTROL_HB, 0,
			   AD7280A_CTRL_HB_CONV_INPUT_ALL |
			   AD7280A_CTRL_HB_CONV_RES_READ_ALL |
			   st->ctrl_hb);
	अगर (ret)
		वापस ret;

	/* Set रेजिस्टर address on the part to be पढ़ो from */
	ret = ad7280_ग_लिखो(st, devaddr, AD7280A_READ, 0, addr << 2);
	अगर (ret)
		वापस ret;

	ret = __ad7280_पढ़ो32(st, &पंचांगp);
	अगर (ret)
		वापस ret;

	अगर (ad7280_check_crc(st, पंचांगp))
		वापस -EIO;

	अगर (((पंचांगp >> 27) != devaddr) || (((पंचांगp >> 21) & 0x3F) != addr))
		वापस -EFAULT;

	वापस (पंचांगp >> 13) & 0xFF;
पूर्ण

अटल पूर्णांक ad7280_पढ़ो_channel(काष्ठा ad7280_state *st, अचिन्हित पूर्णांक devaddr,
			       अचिन्हित पूर्णांक addr)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक पंचांगp;

	ret = ad7280_ग_लिखो(st, devaddr, AD7280A_READ, 0, addr << 2);
	अगर (ret)
		वापस ret;

	ret = ad7280_ग_लिखो(st, AD7280A_DEVADDR_MASTER, AD7280A_CONTROL_HB, 1,
			   AD7280A_CTRL_HB_CONV_INPUT_ALL |
			   AD7280A_CTRL_HB_CONV_RES_READ_NO |
			   st->ctrl_hb);
	अगर (ret)
		वापस ret;

	ret = ad7280_ग_लिखो(st, devaddr, AD7280A_CONTROL_HB, 0,
			   AD7280A_CTRL_HB_CONV_INPUT_ALL |
			   AD7280A_CTRL_HB_CONV_RES_READ_ALL |
			   AD7280A_CTRL_HB_CONV_START_CS |
			   st->ctrl_hb);
	अगर (ret)
		वापस ret;

	ad7280_delay(st);

	ret = __ad7280_पढ़ो32(st, &पंचांगp);
	अगर (ret)
		वापस ret;

	अगर (ad7280_check_crc(st, पंचांगp))
		वापस -EIO;

	अगर (((पंचांगp >> 27) != devaddr) || (((पंचांगp >> 23) & 0xF) != addr))
		वापस -EFAULT;

	वापस (पंचांगp >> 11) & 0xFFF;
पूर्ण

अटल पूर्णांक ad7280_पढ़ो_all_channels(काष्ठा ad7280_state *st, अचिन्हित पूर्णांक cnt,
				    अचिन्हित पूर्णांक *array)
अणु
	पूर्णांक i, ret;
	अचिन्हित पूर्णांक पंचांगp, sum = 0;

	ret = ad7280_ग_लिखो(st, AD7280A_DEVADDR_MASTER, AD7280A_READ, 1,
			   AD7280A_CELL_VOLTAGE_1 << 2);
	अगर (ret)
		वापस ret;

	ret = ad7280_ग_लिखो(st, AD7280A_DEVADDR_MASTER, AD7280A_CONTROL_HB, 1,
			   AD7280A_CTRL_HB_CONV_INPUT_ALL |
			   AD7280A_CTRL_HB_CONV_RES_READ_ALL |
			   AD7280A_CTRL_HB_CONV_START_CS |
			   st->ctrl_hb);
	अगर (ret)
		वापस ret;

	ad7280_delay(st);

	क्रम (i = 0; i < cnt; i++) अणु
		ret = __ad7280_पढ़ो32(st, &पंचांगp);
		अगर (ret)
			वापस ret;

		अगर (ad7280_check_crc(st, पंचांगp))
			वापस -EIO;

		अगर (array)
			array[i] = पंचांगp;
		/* only sum cell voltages */
		अगर (((पंचांगp >> 23) & 0xF) <= AD7280A_CELL_VOLTAGE_6)
			sum += ((पंचांगp >> 11) & 0xFFF);
	पूर्ण

	वापस sum;
पूर्ण

अटल व्योम ad7280_sw_घातer_करोwn(व्योम *data)
अणु
	काष्ठा ad7280_state *st = data;

	ad7280_ग_लिखो(st, AD7280A_DEVADDR_MASTER, AD7280A_CONTROL_HB, 1,
		     AD7280A_CTRL_HB_PWRDN_SW | st->ctrl_hb);
पूर्ण

अटल पूर्णांक ad7280_chain_setup(काष्ठा ad7280_state *st)
अणु
	अचिन्हित पूर्णांक val, n;
	पूर्णांक ret;

	ret = ad7280_ग_लिखो(st, AD7280A_DEVADDR_MASTER, AD7280A_CONTROL_LB, 1,
			   AD7280A_CTRL_LB_DAISY_CHAIN_RB_EN |
			   AD7280A_CTRL_LB_LOCK_DEV_ADDR |
			   AD7280A_CTRL_LB_MUST_SET |
			   AD7280A_CTRL_LB_SWRST |
			   st->ctrl_lb);
	अगर (ret)
		वापस ret;

	ret = ad7280_ग_लिखो(st, AD7280A_DEVADDR_MASTER, AD7280A_CONTROL_LB, 1,
			   AD7280A_CTRL_LB_DAISY_CHAIN_RB_EN |
			   AD7280A_CTRL_LB_LOCK_DEV_ADDR |
			   AD7280A_CTRL_LB_MUST_SET |
			   st->ctrl_lb);
	अगर (ret)
		जाओ error_घातer_करोwn;

	ret = ad7280_ग_लिखो(st, AD7280A_DEVADDR_MASTER, AD7280A_READ, 1,
			   AD7280A_CONTROL_LB << 2);
	अगर (ret)
		जाओ error_घातer_करोwn;

	क्रम (n = 0; n <= AD7280A_MAX_CHAIN; n++) अणु
		ret = __ad7280_पढ़ो32(st, &val);
		अगर (ret)
			जाओ error_घातer_करोwn;

		अगर (val == 0)
			वापस n - 1;

		अगर (ad7280_check_crc(st, val)) अणु
			ret = -EIO;
			जाओ error_घातer_करोwn;
		पूर्ण

		अगर (n != ad7280a_devaddr(val >> 27)) अणु
			ret = -EIO;
			जाओ error_घातer_करोwn;
		पूर्ण
	पूर्ण
	ret = -EFAULT;

error_घातer_करोwn:
	ad7280_ग_लिखो(st, AD7280A_DEVADDR_MASTER, AD7280A_CONTROL_HB, 1,
		     AD7280A_CTRL_HB_PWRDN_SW | st->ctrl_hb);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार ad7280_show_balance_sw(काष्ठा device *dev,
				      काष्ठा device_attribute *attr,
				      अक्षर *buf)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा ad7280_state *st = iio_priv(indio_dev);
	काष्ठा iio_dev_attr *this_attr = to_iio_dev_attr(attr);

	वापस प्र_लिखो(buf, "%d\n",
		       !!(st->cb_mask[this_attr->address >> 8] &
		       (1 << ((this_attr->address & 0xFF) + 2))));
पूर्ण

अटल sमाप_प्रकार ad7280_store_balance_sw(काष्ठा device *dev,
				       काष्ठा device_attribute *attr,
				       स्थिर अक्षर *buf,
				       माप_प्रकार len)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा ad7280_state *st = iio_priv(indio_dev);
	काष्ठा iio_dev_attr *this_attr = to_iio_dev_attr(attr);
	bool पढ़ोin;
	पूर्णांक ret;
	अचिन्हित पूर्णांक devaddr, ch;

	ret = strtobool(buf, &पढ़ोin);
	अगर (ret)
		वापस ret;

	devaddr = this_attr->address >> 8;
	ch = this_attr->address & 0xFF;

	mutex_lock(&st->lock);
	अगर (पढ़ोin)
		st->cb_mask[devaddr] |= 1 << (ch + 2);
	अन्यथा
		st->cb_mask[devaddr] &= ~(1 << (ch + 2));

	ret = ad7280_ग_लिखो(st, devaddr, AD7280A_CELL_BALANCE,
			   0, st->cb_mask[devaddr]);
	mutex_unlock(&st->lock);

	वापस ret ? ret : len;
पूर्ण

अटल sमाप_प्रकार ad7280_show_balance_समयr(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 अक्षर *buf)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा ad7280_state *st = iio_priv(indio_dev);
	काष्ठा iio_dev_attr *this_attr = to_iio_dev_attr(attr);
	पूर्णांक ret;
	अचिन्हित पूर्णांक msecs;

	mutex_lock(&st->lock);
	ret = ad7280_पढ़ो(st, this_attr->address >> 8,
			  this_attr->address & 0xFF);
	mutex_unlock(&st->lock);

	अगर (ret < 0)
		वापस ret;

	msecs = (ret >> 3) * 71500;

	वापस प्र_लिखो(buf, "%u\n", msecs);
पूर्ण

अटल sमाप_प्रकार ad7280_store_balance_समयr(काष्ठा device *dev,
					  काष्ठा device_attribute *attr,
					  स्थिर अक्षर *buf,
					  माप_प्रकार len)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा ad7280_state *st = iio_priv(indio_dev);
	काष्ठा iio_dev_attr *this_attr = to_iio_dev_attr(attr);
	अचिन्हित दीर्घ val;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(buf, 10, &val);
	अगर (ret)
		वापस ret;

	val /= 71500;

	अगर (val > 31)
		वापस -EINVAL;

	mutex_lock(&st->lock);
	ret = ad7280_ग_लिखो(st, this_attr->address >> 8,
			   this_attr->address & 0xFF,
			   0, (val & 0x1F) << 3);
	mutex_unlock(&st->lock);

	वापस ret ? ret : len;
पूर्ण

अटल काष्ठा attribute *ad7280_attributes[AD7280A_MAX_CHAIN *
					   AD7280A_CELLS_PER_DEV * 2 + 1];

अटल स्थिर काष्ठा attribute_group ad7280_attrs_group = अणु
	.attrs = ad7280_attributes,
पूर्ण;

अटल व्योम ad7280_voltage_channel_init(काष्ठा iio_chan_spec *chan, पूर्णांक i)
अणु
	chan->type = IIO_VOLTAGE;
	chan->dअगरferential = 1;
	chan->channel = i;
	chan->channel2 = chan->channel + 1;
पूर्ण

अटल व्योम ad7280_temp_channel_init(काष्ठा iio_chan_spec *chan, पूर्णांक i)
अणु
	chan->type = IIO_TEMP;
	chan->channel = i;
पूर्ण

अटल व्योम ad7280_common_fields_init(काष्ठा iio_chan_spec *chan, पूर्णांक addr,
				      पूर्णांक cnt)
अणु
	chan->indexed = 1;
	chan->info_mask_separate = BIT(IIO_CHAN_INFO_RAW);
	chan->info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE);
	chan->address = addr;
	chan->scan_index = cnt;
	chan->scan_type.sign = 'u';
	chan->scan_type.realbits = 12;
	chan->scan_type.storagebits = 32;
पूर्ण

अटल व्योम ad7280_total_voltage_channel_init(काष्ठा iio_chan_spec *chan,
					      पूर्णांक cnt, पूर्णांक dev)
अणु
	chan->type = IIO_VOLTAGE;
	chan->dअगरferential = 1;
	chan->channel = 0;
	chan->channel2 = dev * AD7280A_CELLS_PER_DEV;
	chan->address = AD7280A_ALL_CELLS;
	chan->indexed = 1;
	chan->info_mask_separate = BIT(IIO_CHAN_INFO_RAW);
	chan->info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE);
	chan->scan_index = cnt;
	chan->scan_type.sign = 'u';
	chan->scan_type.realbits = 32;
	chan->scan_type.storagebits = 32;
पूर्ण

अटल व्योम ad7280_बारtamp_channel_init(काष्ठा iio_chan_spec *chan, पूर्णांक cnt)
अणु
	chan->type = IIO_TIMESTAMP;
	chan->channel = -1;
	chan->scan_index = cnt;
	chan->scan_type.sign = 's';
	chan->scan_type.realbits = 64;
	chan->scan_type.storagebits = 64;
पूर्ण

अटल व्योम ad7280_init_dev_channels(काष्ठा ad7280_state *st, पूर्णांक dev, पूर्णांक *cnt)
अणु
	पूर्णांक addr, ch, i;
	काष्ठा iio_chan_spec *chan;

	क्रम (ch = AD7280A_CELL_VOLTAGE_1; ch <= AD7280A_AUX_ADC_6; ch++) अणु
		chan = &st->channels[*cnt];

		अगर (ch < AD7280A_AUX_ADC_1) अणु
			i = AD7280A_CALC_VOLTAGE_CHAN_NUM(dev, ch);
			ad7280_voltage_channel_init(chan, i);
		पूर्ण अन्यथा अणु
			i = AD7280A_CALC_TEMP_CHAN_NUM(dev, ch);
			ad7280_temp_channel_init(chan, i);
		पूर्ण

		addr = ad7280a_devaddr(dev) << 8 | ch;
		ad7280_common_fields_init(chan, addr, *cnt);

		(*cnt)++;
	पूर्ण
पूर्ण

अटल पूर्णांक ad7280_channel_init(काष्ठा ad7280_state *st)
अणु
	पूर्णांक dev, cnt = 0;

	st->channels = devm_kसुस्मृति(&st->spi->dev, (st->slave_num + 1) * 12 + 2,
				    माप(*st->channels), GFP_KERNEL);
	अगर (!st->channels)
		वापस -ENOMEM;

	क्रम (dev = 0; dev <= st->slave_num; dev++)
		ad7280_init_dev_channels(st, dev, &cnt);

	ad7280_total_voltage_channel_init(&st->channels[cnt], cnt, dev);
	cnt++;
	ad7280_बारtamp_channel_init(&st->channels[cnt], cnt);

	वापस cnt + 1;
पूर्ण

अटल पूर्णांक ad7280_balance_चयन_attr_init(काष्ठा iio_dev_attr *attr,
					   काष्ठा device *dev, पूर्णांक addr, पूर्णांक i)
अणु
	attr->address = addr;
	attr->dev_attr.attr.mode = 0644;
	attr->dev_attr.show = ad7280_show_balance_sw;
	attr->dev_attr.store = ad7280_store_balance_sw;
	attr->dev_attr.attr.name = devm_kaप्र_लिखो(dev, GFP_KERNEL,
						  "in%d-in%d_balance_switch_en",
						  i, i + 1);
	अगर (!attr->dev_attr.attr.name)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल पूर्णांक ad7280_balance_समयr_attr_init(काष्ठा iio_dev_attr *attr,
					  काष्ठा device *dev, पूर्णांक addr, पूर्णांक i)
अणु
	attr->address = addr;
	attr->dev_attr.attr.mode = 0644;
	attr->dev_attr.show = ad7280_show_balance_समयr;
	attr->dev_attr.store = ad7280_store_balance_समयr;
	attr->dev_attr.attr.name = devm_kaप्र_लिखो(dev, GFP_KERNEL,
						  "in%d-in%d_balance_timer",
						  i, i + 1);
	अगर (!attr->dev_attr.attr.name)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल पूर्णांक ad7280_init_dev_attrs(काष्ठा ad7280_state *st, पूर्णांक dev, पूर्णांक *cnt)
अणु
	पूर्णांक addr, ch, i, ret;
	काष्ठा iio_dev_attr *iio_attr;
	काष्ठा device *sdev = &st->spi->dev;

	क्रम (ch = AD7280A_CELL_VOLTAGE_1; ch <= AD7280A_CELL_VOLTAGE_6; ch++) अणु
		iio_attr = &st->iio_attr[*cnt];
		addr = ad7280a_devaddr(dev) << 8 | ch;
		i = dev * AD7280A_CELLS_PER_DEV + ch;

		ret = ad7280_balance_चयन_attr_init(iio_attr, sdev, addr, i);
		अगर (ret < 0)
			वापस ret;

		ad7280_attributes[*cnt] = &iio_attr->dev_attr.attr;

		(*cnt)++;
		iio_attr = &st->iio_attr[*cnt];
		addr = ad7280a_devaddr(dev) << 8 | (AD7280A_CB1_TIMER + ch);

		ret = ad7280_balance_समयr_attr_init(iio_attr, sdev, addr, i);
		अगर (ret < 0)
			वापस ret;

		ad7280_attributes[*cnt] = &iio_attr->dev_attr.attr;
		(*cnt)++;
	पूर्ण

	ad7280_attributes[*cnt] = शून्य;

	वापस 0;
पूर्ण

अटल पूर्णांक ad7280_attr_init(काष्ठा ad7280_state *st)
अणु
	पूर्णांक dev, cnt = 0, ret;

	st->iio_attr = devm_kसुस्मृति(&st->spi->dev, 2, माप(*st->iio_attr) *
				    (st->slave_num + 1) * AD7280A_CELLS_PER_DEV,
				    GFP_KERNEL);
	अगर (!st->iio_attr)
		वापस -ENOMEM;

	क्रम (dev = 0; dev <= st->slave_num; dev++) अणु
		ret = ad7280_init_dev_attrs(st, dev, &cnt);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल sमाप_प्रकार ad7280_पढ़ो_channel_config(काष्ठा device *dev,
					  काष्ठा device_attribute *attr,
					  अक्षर *buf)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा ad7280_state *st = iio_priv(indio_dev);
	काष्ठा iio_dev_attr *this_attr = to_iio_dev_attr(attr);
	अचिन्हित पूर्णांक val;

	चयन (this_attr->address) अणु
	हाल AD7280A_CELL_OVERVOLTAGE:
		val = 1000 + (st->cell_threshhigh * 1568) / 100;
		अवरोध;
	हाल AD7280A_CELL_UNDERVOLTAGE:
		val = 1000 + (st->cell_threshlow * 1568) / 100;
		अवरोध;
	हाल AD7280A_AUX_ADC_OVERVOLTAGE:
		val = (st->aux_threshhigh * 196) / 10;
		अवरोध;
	हाल AD7280A_AUX_ADC_UNDERVOLTAGE:
		val = (st->aux_threshlow * 196) / 10;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस प्र_लिखो(buf, "%u\n", val);
पूर्ण

अटल sमाप_प्रकार ad7280_ग_लिखो_channel_config(काष्ठा device *dev,
					   काष्ठा device_attribute *attr,
					   स्थिर अक्षर *buf,
					   माप_प्रकार len)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा ad7280_state *st = iio_priv(indio_dev);
	काष्ठा iio_dev_attr *this_attr = to_iio_dev_attr(attr);

	दीर्घ val;
	पूर्णांक ret;

	ret = kम_से_दीर्घ(buf, 10, &val);
	अगर (ret)
		वापस ret;

	चयन (this_attr->address) अणु
	हाल AD7280A_CELL_OVERVOLTAGE:
	हाल AD7280A_CELL_UNDERVOLTAGE:
		val = ((val - 1000) * 100) / 1568; /* LSB 15.68mV */
		अवरोध;
	हाल AD7280A_AUX_ADC_OVERVOLTAGE:
	हाल AD7280A_AUX_ADC_UNDERVOLTAGE:
		val = (val * 10) / 196; /* LSB 19.6mV */
		अवरोध;
	शेष:
		वापस -EFAULT;
	पूर्ण

	val = clamp(val, 0L, 0xFFL);

	mutex_lock(&st->lock);
	चयन (this_attr->address) अणु
	हाल AD7280A_CELL_OVERVOLTAGE:
		st->cell_threshhigh = val;
		अवरोध;
	हाल AD7280A_CELL_UNDERVOLTAGE:
		st->cell_threshlow = val;
		अवरोध;
	हाल AD7280A_AUX_ADC_OVERVOLTAGE:
		st->aux_threshhigh = val;
		अवरोध;
	हाल AD7280A_AUX_ADC_UNDERVOLTAGE:
		st->aux_threshlow = val;
		अवरोध;
	पूर्ण

	ret = ad7280_ग_लिखो(st, AD7280A_DEVADDR_MASTER,
			   this_attr->address, 1, val);

	mutex_unlock(&st->lock);

	वापस ret ? ret : len;
पूर्ण

अटल irqवापस_t ad7280_event_handler(पूर्णांक irq, व्योम *निजी)
अणु
	काष्ठा iio_dev *indio_dev = निजी;
	काष्ठा ad7280_state *st = iio_priv(indio_dev);
	अचिन्हित पूर्णांक *channels;
	पूर्णांक i, ret;

	channels = kसुस्मृति(st->scan_cnt, माप(*channels), GFP_KERNEL);
	अगर (!channels)
		वापस IRQ_HANDLED;

	ret = ad7280_पढ़ो_all_channels(st, st->scan_cnt, channels);
	अगर (ret < 0)
		जाओ out;

	क्रम (i = 0; i < st->scan_cnt; i++) अणु
		अगर (((channels[i] >> 23) & 0xF) <= AD7280A_CELL_VOLTAGE_6) अणु
			अगर (((channels[i] >> 11) & 0xFFF) >=
			    st->cell_threshhigh) अणु
				u64 पंचांगp = IIO_EVENT_CODE(IIO_VOLTAGE, 1, 0,
							 IIO_EV_सूची_RISING,
							 IIO_EV_TYPE_THRESH,
							 0, 0, 0);
				iio_push_event(indio_dev, पंचांगp,
					       iio_get_समय_ns(indio_dev));
			पूर्ण अन्यथा अगर (((channels[i] >> 11) & 0xFFF) <=
				   st->cell_threshlow) अणु
				u64 पंचांगp = IIO_EVENT_CODE(IIO_VOLTAGE, 1, 0,
							 IIO_EV_सूची_FALLING,
							 IIO_EV_TYPE_THRESH,
							 0, 0, 0);
				iio_push_event(indio_dev, पंचांगp,
					       iio_get_समय_ns(indio_dev));
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (((channels[i] >> 11) & 0xFFF) >=
			    st->aux_threshhigh) अणु
				u64 पंचांगp = IIO_UNMOD_EVENT_CODE(IIO_TEMP, 0,
							IIO_EV_TYPE_THRESH,
							IIO_EV_सूची_RISING);
				iio_push_event(indio_dev, पंचांगp,
					       iio_get_समय_ns(indio_dev));
			पूर्ण अन्यथा अगर (((channels[i] >> 11) & 0xFFF) <=
				st->aux_threshlow) अणु
				u64 पंचांगp = IIO_UNMOD_EVENT_CODE(IIO_TEMP, 0,
							IIO_EV_TYPE_THRESH,
							IIO_EV_सूची_FALLING);
				iio_push_event(indio_dev, पंचांगp,
					       iio_get_समय_ns(indio_dev));
			पूर्ण
		पूर्ण
	पूर्ण

out:
	kमुक्त(channels);

	वापस IRQ_HANDLED;
पूर्ण

/* Note: No need to fix checkpatch warning that पढ़ोs:
 *	CHECK: spaces preferred around that '-' (ctx:VxV)
 * The function argument is stringअगरied and करोesn't need a fix
 */
अटल IIO_DEVICE_ATTR_NAMED(in_thresh_low_value,
			     in_voltage-voltage_thresh_low_value,
			     0644,
			     ad7280_पढ़ो_channel_config,
			     ad7280_ग_लिखो_channel_config,
			     AD7280A_CELL_UNDERVOLTAGE);

अटल IIO_DEVICE_ATTR_NAMED(in_thresh_high_value,
			     in_voltage-voltage_thresh_high_value,
			     0644,
			     ad7280_पढ़ो_channel_config,
			     ad7280_ग_लिखो_channel_config,
			     AD7280A_CELL_OVERVOLTAGE);

अटल IIO_DEVICE_ATTR(in_temp_thresh_low_value,
		       0644,
		       ad7280_पढ़ो_channel_config,
		       ad7280_ग_लिखो_channel_config,
		       AD7280A_AUX_ADC_UNDERVOLTAGE);

अटल IIO_DEVICE_ATTR(in_temp_thresh_high_value,
		       0644,
		       ad7280_पढ़ो_channel_config,
		       ad7280_ग_लिखो_channel_config,
		       AD7280A_AUX_ADC_OVERVOLTAGE);

अटल काष्ठा attribute *ad7280_event_attributes[] = अणु
	&iio_dev_attr_in_thresh_low_value.dev_attr.attr,
	&iio_dev_attr_in_thresh_high_value.dev_attr.attr,
	&iio_dev_attr_in_temp_thresh_low_value.dev_attr.attr,
	&iio_dev_attr_in_temp_thresh_high_value.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group ad7280_event_attrs_group = अणु
	.attrs = ad7280_event_attributes,
पूर्ण;

अटल पूर्णांक ad7280_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			   काष्ठा iio_chan_spec स्थिर *chan,
			   पूर्णांक *val,
			   पूर्णांक *val2,
			   दीर्घ m)
अणु
	काष्ठा ad7280_state *st = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (m) अणु
	हाल IIO_CHAN_INFO_RAW:
		mutex_lock(&st->lock);
		अगर (chan->address == AD7280A_ALL_CELLS)
			ret = ad7280_पढ़ो_all_channels(st, st->scan_cnt, शून्य);
		अन्यथा
			ret = ad7280_पढ़ो_channel(st, chan->address >> 8,
						  chan->address & 0xFF);
		mutex_unlock(&st->lock);

		अगर (ret < 0)
			वापस ret;

		*val = ret;

		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		अगर ((chan->address & 0xFF) <= AD7280A_CELL_VOLTAGE_6)
			*val = 4000;
		अन्यथा
			*val = 5000;

		*val2 = AD7280A_BITS;
		वापस IIO_VAL_FRACTIONAL_LOG2;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा iio_info ad7280_info = अणु
	.पढ़ो_raw = ad7280_पढ़ो_raw,
	.event_attrs = &ad7280_event_attrs_group,
	.attrs = &ad7280_attrs_group,
पूर्ण;

अटल स्थिर काष्ठा ad7280_platक्रमm_data ad7793_शेष_pdata = अणु
	.acquisition_समय = AD7280A_ACQ_TIME_400ns,
	.conversion_averaging = AD7280A_CONV_AVG_DIS,
	.thermistor_term_en = true,
पूर्ण;

अटल पूर्णांक ad7280_probe(काष्ठा spi_device *spi)
अणु
	स्थिर काष्ठा ad7280_platक्रमm_data *pdata = dev_get_platdata(&spi->dev);
	काष्ठा ad7280_state *st;
	पूर्णांक ret;
	स्थिर अचिन्हित लघु t_acq_ns[4] = अणु465, 1010, 1460, 1890पूर्ण;
	स्थिर अचिन्हित लघु n_avg[4] = अणु1, 2, 4, 8पूर्ण;
	काष्ठा iio_dev *indio_dev;

	indio_dev = devm_iio_device_alloc(&spi->dev, माप(*st));
	अगर (!indio_dev)
		वापस -ENOMEM;

	st = iio_priv(indio_dev);
	spi_set_drvdata(spi, indio_dev);
	st->spi = spi;
	mutex_init(&st->lock);

	अगर (!pdata)
		pdata = &ad7793_शेष_pdata;

	crc8_populate_msb(st->crc_tab, POLYNOM);

	st->spi->max_speed_hz = AD7280A_MAX_SPI_CLK_HZ;
	st->spi->mode = SPI_MODE_1;
	spi_setup(st->spi);

	st->ctrl_lb = AD7280A_CTRL_LB_ACQ_TIME(pdata->acquisition_समय & 0x3);
	st->ctrl_hb = AD7280A_CTRL_HB_CONV_AVG(pdata->conversion_averaging
			& 0x3) | (pdata->thermistor_term_en ?
			AD7280A_CTRL_LB_THERMISTOR_EN : 0);

	ret = ad7280_chain_setup(st);
	अगर (ret < 0)
		वापस ret;

	st->slave_num = ret;
	st->scan_cnt = (st->slave_num + 1) * AD7280A_NUM_CH;
	st->cell_threshhigh = 0xFF;
	st->aux_threshhigh = 0xFF;

	ret = devm_add_action_or_reset(&spi->dev, ad7280_sw_घातer_करोwn, st);
	अगर (ret)
		वापस ret;

	/*
	 * Total Conversion Time = ((tACQ + tCONV) *
	 *			   (Number of Conversions per Part)) ै
	 *			   tACQ + ((N - 1) * tDELAY)
	 *
	 * Readback Delay = Total Conversion Time + tWAIT
	 */

	st->पढ़ोback_delay_us =
		((t_acq_ns[pdata->acquisition_समय & 0x3] + 695) *
		 (AD7280A_NUM_CH * n_avg[pdata->conversion_averaging & 0x3])) -
		t_acq_ns[pdata->acquisition_समय & 0x3] + st->slave_num * 250;

	/* Convert to usecs */
	st->पढ़ोback_delay_us = DIV_ROUND_UP(st->पढ़ोback_delay_us, 1000);
	st->पढ़ोback_delay_us += 5; /* Add tWAIT */

	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->modes = INDIO_सूचीECT_MODE;

	ret = ad7280_channel_init(st);
	अगर (ret < 0)
		वापस ret;

	indio_dev->num_channels = ret;
	indio_dev->channels = st->channels;
	indio_dev->info = &ad7280_info;

	ret = ad7280_attr_init(st);
	अगर (ret < 0)
		वापस ret;

	ret = devm_iio_device_रेजिस्टर(&spi->dev, indio_dev);
	अगर (ret)
		वापस ret;

	अगर (spi->irq > 0) अणु
		ret = ad7280_ग_लिखो(st, AD7280A_DEVADDR_MASTER,
				   AD7280A_ALERT, 1,
				   AD7280A_ALERT_RELAY_SIG_CHAIN_DOWN);
		अगर (ret)
			वापस ret;

		ret = ad7280_ग_लिखो(st, ad7280a_devaddr(st->slave_num),
				   AD7280A_ALERT, 0,
				   AD7280A_ALERT_GEN_STATIC_HIGH |
				   (pdata->chain_last_alert_ignore & 0xF));
		अगर (ret)
			वापस ret;

		ret = devm_request_thपढ़ोed_irq(&spi->dev, spi->irq,
						शून्य,
						ad7280_event_handler,
						IRQF_TRIGGER_FALLING |
						IRQF_ONESHOT,
						indio_dev->name,
						indio_dev);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा spi_device_id ad7280_id[] = अणु
	अणु"ad7280a", 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, ad7280_id);

अटल काष्ठा spi_driver ad7280_driver = अणु
	.driver = अणु
		.name	= "ad7280",
	पूर्ण,
	.probe		= ad7280_probe,
	.id_table	= ad7280_id,
पूर्ण;
module_spi_driver(ad7280_driver);

MODULE_AUTHOR("Michael Hennerich <michael.hennerich@analog.com>");
MODULE_DESCRIPTION("Analog Devices AD7280A");
MODULE_LICENSE("GPL v2");
