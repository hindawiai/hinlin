<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * This file is part of AD5686 DAC driver
 *
 * Copyright 2018 Analog Devices Inc.
 */

#अगर_अघोषित __DRIVERS_IIO_DAC_AD5686_H__
#घोषणा __DRIVERS_IIO_DAC_AD5686_H__

#समावेश <linux/types.h>
#समावेश <linux/cache.h>
#समावेश <linux/mutex.h>
#समावेश <linux/kernel.h>

#घोषणा AD5310_CMD(x)				((x) << 12)

#घोषणा AD5683_DATA(x)				((x) << 4)

#घोषणा AD5686_ADDR(x)				((x) << 16)
#घोषणा AD5686_CMD(x)				((x) << 20)

#घोषणा AD5686_ADDR_DAC(chan)			(0x1 << (chan))
#घोषणा AD5686_ADDR_ALL_DAC			0xF

#घोषणा AD5686_CMD_NOOP				0x0
#घोषणा AD5686_CMD_WRITE_INPUT_N		0x1
#घोषणा AD5686_CMD_UPDATE_DAC_N			0x2
#घोषणा AD5686_CMD_WRITE_INPUT_N_UPDATE_N	0x3
#घोषणा AD5686_CMD_POWERDOWN_DAC		0x4
#घोषणा AD5686_CMD_LDAC_MASK			0x5
#घोषणा AD5686_CMD_RESET			0x6
#घोषणा AD5686_CMD_INTERNAL_REFER_SETUP		0x7
#घोषणा AD5686_CMD_DAISY_CHAIN_ENABLE		0x8
#घोषणा AD5686_CMD_READBACK_ENABLE		0x9

#घोषणा AD5686_LDAC_PWRDN_NONE			0x0
#घोषणा AD5686_LDAC_PWRDN_1K			0x1
#घोषणा AD5686_LDAC_PWRDN_100K			0x2
#घोषणा AD5686_LDAC_PWRDN_3STATE		0x3

#घोषणा AD5686_CMD_CONTROL_REG			0x4
#घोषणा AD5686_CMD_READBACK_ENABLE_V2		0x5

#घोषणा AD5310_REF_BIT_MSK			BIT(8)
#घोषणा AD5683_REF_BIT_MSK			BIT(12)
#घोषणा AD5693_REF_BIT_MSK			BIT(12)

/**
 * ad5686_supported_device_ids:
 */
क्रमागत ad5686_supported_device_ids अणु
	ID_AD5310R,
	ID_AD5311R,
	ID_AD5338R,
	ID_AD5671R,
	ID_AD5672R,
	ID_AD5673R,
	ID_AD5674R,
	ID_AD5675R,
	ID_AD5676,
	ID_AD5676R,
	ID_AD5677R,
	ID_AD5679R,
	ID_AD5681R,
	ID_AD5682R,
	ID_AD5683,
	ID_AD5683R,
	ID_AD5684,
	ID_AD5684R,
	ID_AD5685R,
	ID_AD5686,
	ID_AD5686R,
	ID_AD5691R,
	ID_AD5692R,
	ID_AD5693,
	ID_AD5693R,
	ID_AD5694,
	ID_AD5694R,
	ID_AD5695R,
	ID_AD5696,
	ID_AD5696R,
पूर्ण;

क्रमागत ad5686_regmap_type अणु
	AD5310_REGMAP,
	AD5683_REGMAP,
	AD5686_REGMAP,
	AD5693_REGMAP
पूर्ण;

काष्ठा ad5686_state;

प्रकार पूर्णांक (*ad5686_ग_लिखो_func)(काष्ठा ad5686_state *st,
				 u8 cmd, u8 addr, u16 val);

प्रकार पूर्णांक (*ad5686_पढ़ो_func)(काष्ठा ad5686_state *st, u8 addr);

/**
 * काष्ठा ad5686_chip_info - chip specअगरic inक्रमmation
 * @पूर्णांक_vref_mv:	AD5620/40/60: the पूर्णांकernal reference voltage
 * @num_channels:	number of channels
 * @channel:		channel specअगरication
 * @regmap_type:	रेजिस्टर map layout variant
 */

काष्ठा ad5686_chip_info अणु
	u16				पूर्णांक_vref_mv;
	अचिन्हित पूर्णांक			num_channels;
	स्थिर काष्ठा iio_chan_spec	*channels;
	क्रमागत ad5686_regmap_type		regmap_type;
पूर्ण;

/**
 * काष्ठा ad5446_state - driver instance specअगरic data
 * @spi:		spi_device
 * @chip_info:		chip model specअगरic स्थिरants, available modes etc
 * @reg:		supply regulator
 * @vref_mv:		actual reference voltage used
 * @pwr_करोwn_mask:	घातer करोwn mask
 * @pwr_करोwn_mode:	current घातer करोwn mode
 * @use_पूर्णांकernal_vref:	set to true अगर the पूर्णांकernal reference voltage is used
 * @lock		lock to protect the data buffer during regmap ops
 * @data:		spi transfer buffers
 */

काष्ठा ad5686_state अणु
	काष्ठा device			*dev;
	स्थिर काष्ठा ad5686_chip_info	*chip_info;
	काष्ठा regulator		*reg;
	अचिन्हित लघु			vref_mv;
	अचिन्हित पूर्णांक			pwr_करोwn_mask;
	अचिन्हित पूर्णांक			pwr_करोwn_mode;
	ad5686_ग_लिखो_func		ग_लिखो;
	ad5686_पढ़ो_func		पढ़ो;
	bool				use_पूर्णांकernal_vref;
	काष्ठा mutex			lock;

	/*
	 * DMA (thus cache coherency मुख्यtenance) requires the
	 * transfer buffers to live in their own cache lines.
	 */

	जोड़ अणु
		__be32 d32;
		__be16 d16;
		u8 d8[4];
	पूर्ण data[3] ____cacheline_aligned;
पूर्ण;


पूर्णांक ad5686_probe(काष्ठा device *dev,
		 क्रमागत ad5686_supported_device_ids chip_type,
		 स्थिर अक्षर *name, ad5686_ग_लिखो_func ग_लिखो,
		 ad5686_पढ़ो_func पढ़ो);

पूर्णांक ad5686_हटाओ(काष्ठा device *dev);


#पूर्ण_अगर /* __DRIVERS_IIO_DAC_AD5686_H__ */
