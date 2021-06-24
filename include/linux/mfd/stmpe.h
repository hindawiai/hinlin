<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) ST-Ericsson SA 2010
 *
 * Author: Rabin Vincent <rabin.vincent@stericsson.com> क्रम ST-Ericsson
 */

#अगर_अघोषित __LINUX_MFD_STMPE_H
#घोषणा __LINUX_MFD_STMPE_H

#समावेश <linux/mutex.h>

#घोषणा STMPE_SAMPLE_TIME(x)	((x & 0xf) << 4)
#घोषणा STMPE_MOD_12B(x)	((x & 0x1) << 3)
#घोषणा STMPE_REF_SEL(x)	((x & 0x1) << 1)
#घोषणा STMPE_ADC_FREQ(x)	(x & 0x3)
#घोषणा STMPE_AVE_CTRL(x)	((x & 0x3) << 6)
#घोषणा STMPE_DET_DELAY(x)	((x & 0x7) << 3)
#घोषणा STMPE_SETTLING(x)	(x & 0x7)
#घोषणा STMPE_FRACTION_Z(x)	(x & 0x7)
#घोषणा STMPE_I_DRIVE(x)	(x & 0x1)
#घोषणा STMPE_OP_MODE(x)	((x & 0x7) << 1)

#घोषणा STMPE811_REG_ADC_CTRL1	0x20
#घोषणा STMPE811_REG_ADC_CTRL2	0x21

काष्ठा device;
काष्ठा regulator;

क्रमागत sपंचांगpe_block अणु
	STMPE_BLOCK_GPIO	= 1 << 0,
	STMPE_BLOCK_KEYPAD	= 1 << 1,
	STMPE_BLOCK_TOUCHSCREEN	= 1 << 2,
	STMPE_BLOCK_ADC		= 1 << 3,
	STMPE_BLOCK_PWM		= 1 << 4,
	STMPE_BLOCK_ROTATOR	= 1 << 5,
पूर्ण;

क्रमागत sपंचांगpe_partnum अणु
	STMPE610,
	STMPE801,
	STMPE811,
	STMPE1600,
	STMPE1601,
	STMPE1801,
	STMPE2401,
	STMPE2403,
	STMPE_NBR_PARTS
पूर्ण;

/*
 * For रेजिस्टरs whose locations dअगरfer on variants,  the correct address is
 * obtained by indexing sपंचांगpe->regs with one of the following.
 */
क्रमागत अणु
	STMPE_IDX_CHIP_ID,
	STMPE_IDX_SYS_CTRL,
	STMPE_IDX_SYS_CTRL2,
	STMPE_IDX_ICR_LSB,
	STMPE_IDX_IER_LSB,
	STMPE_IDX_IER_MSB,
	STMPE_IDX_ISR_LSB,
	STMPE_IDX_ISR_MSB,
	STMPE_IDX_GPMR_LSB,
	STMPE_IDX_GPMR_CSB,
	STMPE_IDX_GPMR_MSB,
	STMPE_IDX_GPSR_LSB,
	STMPE_IDX_GPSR_CSB,
	STMPE_IDX_GPSR_MSB,
	STMPE_IDX_GPCR_LSB,
	STMPE_IDX_GPCR_CSB,
	STMPE_IDX_GPCR_MSB,
	STMPE_IDX_GPDR_LSB,
	STMPE_IDX_GPDR_CSB,
	STMPE_IDX_GPDR_MSB,
	STMPE_IDX_GPEDR_LSB,
	STMPE_IDX_GPEDR_CSB,
	STMPE_IDX_GPEDR_MSB,
	STMPE_IDX_GPRER_LSB,
	STMPE_IDX_GPRER_CSB,
	STMPE_IDX_GPRER_MSB,
	STMPE_IDX_GPFER_LSB,
	STMPE_IDX_GPFER_CSB,
	STMPE_IDX_GPFER_MSB,
	STMPE_IDX_GPPUR_LSB,
	STMPE_IDX_GPPDR_LSB,
	STMPE_IDX_GPAFR_U_MSB,
	STMPE_IDX_IEGPIOR_LSB,
	STMPE_IDX_IEGPIOR_CSB,
	STMPE_IDX_IEGPIOR_MSB,
	STMPE_IDX_ISGPIOR_LSB,
	STMPE_IDX_ISGPIOR_CSB,
	STMPE_IDX_ISGPIOR_MSB,
	STMPE_IDX_MAX,
पूर्ण;


काष्ठा sपंचांगpe_variant_info;
काष्ठा sपंचांगpe_client_info;
काष्ठा sपंचांगpe_platक्रमm_data;

/**
 * काष्ठा sपंचांगpe - STMPE MFD काष्ठाure
 * @vcc: optional VCC regulator
 * @vio: optional VIO regulator
 * @lock: lock protecting I/O operations
 * @irq_lock: IRQ bus lock
 * @dev: device, mostly क्रम dev_dbg()
 * @irq_करोमुख्य: IRQ करोमुख्य
 * @client: client - i2c or spi
 * @ci: client specअगरic inक्रमmation
 * @partnum: part number
 * @variant: the detected STMPE model number
 * @regs: list of addresses of रेजिस्टरs which are at dअगरferent addresses on
 *	  dअगरferent variants.  Indexed by one of STMPE_IDX_*.
 * @irq: irq number क्रम sपंचांगpe
 * @num_gpios: number of gpios, dअगरfers क्रम variants
 * @ier: cache of IER रेजिस्टरs क्रम bus_lock
 * @oldier: cache of IER रेजिस्टरs क्रम bus_lock
 * @pdata: platक्रमm data
 */
काष्ठा sपंचांगpe अणु
	काष्ठा regulator *vcc;
	काष्ठा regulator *vio;
	काष्ठा mutex lock;
	काष्ठा mutex irq_lock;
	काष्ठा device *dev;
	काष्ठा irq_करोमुख्य *करोमुख्य;
	व्योम *client;
	काष्ठा sपंचांगpe_client_info *ci;
	क्रमागत sपंचांगpe_partnum partnum;
	काष्ठा sपंचांगpe_variant_info *variant;
	स्थिर u8 *regs;

	पूर्णांक irq;
	पूर्णांक num_gpios;
	u8 ier[2];
	u8 oldier[2];
	काष्ठा sपंचांगpe_platक्रमm_data *pdata;

	/* For devices that use an ADC */
	u8 sample_समय;
	u8 mod_12b;
	u8 ref_sel;
	u8 adc_freq;
पूर्ण;

बाह्य पूर्णांक sपंचांगpe_reg_ग_लिखो(काष्ठा sपंचांगpe *sपंचांगpe, u8 reg, u8 data);
बाह्य पूर्णांक sपंचांगpe_reg_पढ़ो(काष्ठा sपंचांगpe *sपंचांगpe, u8 reg);
बाह्य पूर्णांक sपंचांगpe_block_पढ़ो(काष्ठा sपंचांगpe *sपंचांगpe, u8 reg, u8 length,
			    u8 *values);
बाह्य पूर्णांक sपंचांगpe_block_ग_लिखो(काष्ठा sपंचांगpe *sपंचांगpe, u8 reg, u8 length,
			     स्थिर u8 *values);
बाह्य पूर्णांक sपंचांगpe_set_bits(काष्ठा sपंचांगpe *sपंचांगpe, u8 reg, u8 mask, u8 val);
बाह्य पूर्णांक sपंचांगpe_set_altfunc(काष्ठा sपंचांगpe *sपंचांगpe, u32 pins,
			     क्रमागत sपंचांगpe_block block);
बाह्य पूर्णांक sपंचांगpe_enable(काष्ठा sपंचांगpe *sपंचांगpe, अचिन्हित पूर्णांक blocks);
बाह्य पूर्णांक sपंचांगpe_disable(काष्ठा sपंचांगpe *sपंचांगpe, अचिन्हित पूर्णांक blocks);
बाह्य पूर्णांक sपंचांगpe811_adc_common_init(काष्ठा sपंचांगpe *sपंचांगpe);

#घोषणा STMPE_GPIO_NOREQ_811_TOUCH	(0xf0)

#पूर्ण_अगर
