<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम STMicroelectronics STM32F7 I2C controller
 *
 * This I2C controller is described in the STM32F75xxx and STM32F74xxx Soc
 * reference manual.
 * Please see below a link to the करोcumentation:
 * http://www.st.com/resource/en/reference_manual/dm00124865.pdf
 *
 * Copyright (C) M'boumba Cedric Madianga 2017
 * Copyright (C) STMicroelectronics 2017
 * Author: M'boumba Cedric Madianga <cedric.madianga@gmail.com>
 *
 * This driver is based on i2c-sपंचांग32f4.c
 *
 */
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/i2c-smbus.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/pm_wakeirq.h>
#समावेश <linux/regmap.h>
#समावेश <linux/reset.h>
#समावेश <linux/slab.h>

#समावेश "i2c-stm32.h"

/* STM32F7 I2C रेजिस्टरs */
#घोषणा STM32F7_I2C_CR1				0x00
#घोषणा STM32F7_I2C_CR2				0x04
#घोषणा STM32F7_I2C_OAR1			0x08
#घोषणा STM32F7_I2C_OAR2			0x0C
#घोषणा STM32F7_I2C_PECR			0x20
#घोषणा STM32F7_I2C_TIMINGR			0x10
#घोषणा STM32F7_I2C_ISR				0x18
#घोषणा STM32F7_I2C_ICR				0x1C
#घोषणा STM32F7_I2C_RXDR			0x24
#घोषणा STM32F7_I2C_TXDR			0x28

/* STM32F7 I2C control 1 */
#घोषणा STM32F7_I2C_CR1_PECEN			BIT(23)
#घोषणा STM32F7_I2C_CR1_SMBHEN			BIT(20)
#घोषणा STM32F7_I2C_CR1_WUPEN			BIT(18)
#घोषणा STM32F7_I2C_CR1_SBC			BIT(16)
#घोषणा STM32F7_I2C_CR1_RXDMAEN			BIT(15)
#घोषणा STM32F7_I2C_CR1_TXDMAEN			BIT(14)
#घोषणा STM32F7_I2C_CR1_ANFOFF			BIT(12)
#घोषणा STM32F7_I2C_CR1_DNF_MASK		GENMASK(11, 8)
#घोषणा STM32F7_I2C_CR1_DNF(n)			(((n) & 0xf) << 8)
#घोषणा STM32F7_I2C_CR1_ERRIE			BIT(7)
#घोषणा STM32F7_I2C_CR1_TCIE			BIT(6)
#घोषणा STM32F7_I2C_CR1_STOPIE			BIT(5)
#घोषणा STM32F7_I2C_CR1_NACKIE			BIT(4)
#घोषणा STM32F7_I2C_CR1_ADDRIE			BIT(3)
#घोषणा STM32F7_I2C_CR1_RXIE			BIT(2)
#घोषणा STM32F7_I2C_CR1_TXIE			BIT(1)
#घोषणा STM32F7_I2C_CR1_PE			BIT(0)
#घोषणा STM32F7_I2C_ALL_IRQ_MASK		(STM32F7_I2C_CR1_ERRIE \
						| STM32F7_I2C_CR1_TCIE \
						| STM32F7_I2C_CR1_STOPIE \
						| STM32F7_I2C_CR1_NACKIE \
						| STM32F7_I2C_CR1_RXIE \
						| STM32F7_I2C_CR1_TXIE)
#घोषणा STM32F7_I2C_XFER_IRQ_MASK		(STM32F7_I2C_CR1_TCIE \
						| STM32F7_I2C_CR1_STOPIE \
						| STM32F7_I2C_CR1_NACKIE \
						| STM32F7_I2C_CR1_RXIE \
						| STM32F7_I2C_CR1_TXIE)

/* STM32F7 I2C control 2 */
#घोषणा STM32F7_I2C_CR2_PECBYTE			BIT(26)
#घोषणा STM32F7_I2C_CR2_RELOAD			BIT(24)
#घोषणा STM32F7_I2C_CR2_NBYTES_MASK		GENMASK(23, 16)
#घोषणा STM32F7_I2C_CR2_NBYTES(n)		(((n) & 0xff) << 16)
#घोषणा STM32F7_I2C_CR2_NACK			BIT(15)
#घोषणा STM32F7_I2C_CR2_STOP			BIT(14)
#घोषणा STM32F7_I2C_CR2_START			BIT(13)
#घोषणा STM32F7_I2C_CR2_HEAD10R			BIT(12)
#घोषणा STM32F7_I2C_CR2_ADD10			BIT(11)
#घोषणा STM32F7_I2C_CR2_RD_WRN			BIT(10)
#घोषणा STM32F7_I2C_CR2_SADD10_MASK		GENMASK(9, 0)
#घोषणा STM32F7_I2C_CR2_SADD10(n)		(((n) & \
						STM32F7_I2C_CR2_SADD10_MASK))
#घोषणा STM32F7_I2C_CR2_SADD7_MASK		GENMASK(7, 1)
#घोषणा STM32F7_I2C_CR2_SADD7(n)		(((n) & 0x7f) << 1)

/* STM32F7 I2C Own Address 1 */
#घोषणा STM32F7_I2C_OAR1_OA1EN			BIT(15)
#घोषणा STM32F7_I2C_OAR1_OA1MODE		BIT(10)
#घोषणा STM32F7_I2C_OAR1_OA1_10_MASK		GENMASK(9, 0)
#घोषणा STM32F7_I2C_OAR1_OA1_10(n)		(((n) & \
						STM32F7_I2C_OAR1_OA1_10_MASK))
#घोषणा STM32F7_I2C_OAR1_OA1_7_MASK		GENMASK(7, 1)
#घोषणा STM32F7_I2C_OAR1_OA1_7(n)		(((n) & 0x7f) << 1)
#घोषणा STM32F7_I2C_OAR1_MASK			(STM32F7_I2C_OAR1_OA1_7_MASK \
						| STM32F7_I2C_OAR1_OA1_10_MASK \
						| STM32F7_I2C_OAR1_OA1EN \
						| STM32F7_I2C_OAR1_OA1MODE)

/* STM32F7 I2C Own Address 2 */
#घोषणा STM32F7_I2C_OAR2_OA2EN			BIT(15)
#घोषणा STM32F7_I2C_OAR2_OA2MSK_MASK		GENMASK(10, 8)
#घोषणा STM32F7_I2C_OAR2_OA2MSK(n)		(((n) & 0x7) << 8)
#घोषणा STM32F7_I2C_OAR2_OA2_7_MASK		GENMASK(7, 1)
#घोषणा STM32F7_I2C_OAR2_OA2_7(n)		(((n) & 0x7f) << 1)
#घोषणा STM32F7_I2C_OAR2_MASK			(STM32F7_I2C_OAR2_OA2MSK_MASK \
						| STM32F7_I2C_OAR2_OA2_7_MASK \
						| STM32F7_I2C_OAR2_OA2EN)

/* STM32F7 I2C Interrupt Status */
#घोषणा STM32F7_I2C_ISR_ADDCODE_MASK		GENMASK(23, 17)
#घोषणा STM32F7_I2C_ISR_ADDCODE_GET(n) \
				(((n) & STM32F7_I2C_ISR_ADDCODE_MASK) >> 17)
#घोषणा STM32F7_I2C_ISR_सूची			BIT(16)
#घोषणा STM32F7_I2C_ISR_BUSY			BIT(15)
#घोषणा STM32F7_I2C_ISR_PECERR			BIT(11)
#घोषणा STM32F7_I2C_ISR_ARLO			BIT(9)
#घोषणा STM32F7_I2C_ISR_BERR			BIT(8)
#घोषणा STM32F7_I2C_ISR_TCR			BIT(7)
#घोषणा STM32F7_I2C_ISR_TC			BIT(6)
#घोषणा STM32F7_I2C_ISR_STOPF			BIT(5)
#घोषणा STM32F7_I2C_ISR_NACKF			BIT(4)
#घोषणा STM32F7_I2C_ISR_ADDR			BIT(3)
#घोषणा STM32F7_I2C_ISR_RXNE			BIT(2)
#घोषणा STM32F7_I2C_ISR_TXIS			BIT(1)
#घोषणा STM32F7_I2C_ISR_TXE			BIT(0)

/* STM32F7 I2C Interrupt Clear */
#घोषणा STM32F7_I2C_ICR_PECCF			BIT(11)
#घोषणा STM32F7_I2C_ICR_ARLOCF			BIT(9)
#घोषणा STM32F7_I2C_ICR_BERRCF			BIT(8)
#घोषणा STM32F7_I2C_ICR_STOPCF			BIT(5)
#घोषणा STM32F7_I2C_ICR_NACKCF			BIT(4)
#घोषणा STM32F7_I2C_ICR_ADDRCF			BIT(3)

/* STM32F7 I2C Timing */
#घोषणा STM32F7_I2C_TIMINGR_PRESC(n)		(((n) & 0xf) << 28)
#घोषणा STM32F7_I2C_TIMINGR_SCLDEL(n)		(((n) & 0xf) << 20)
#घोषणा STM32F7_I2C_TIMINGR_SDADEL(n)		(((n) & 0xf) << 16)
#घोषणा STM32F7_I2C_TIMINGR_SCLH(n)		(((n) & 0xff) << 8)
#घोषणा STM32F7_I2C_TIMINGR_SCLL(n)		((n) & 0xff)

#घोषणा STM32F7_I2C_MAX_LEN			0xff
#घोषणा STM32F7_I2C_DMA_LEN_MIN			0x16
क्रमागत अणु
	STM32F7_SLAVE_HOSTNOTIFY,
	STM32F7_SLAVE_7_10_BITS_ADDR,
	STM32F7_SLAVE_7_BITS_ADDR,
	STM32F7_I2C_MAX_SLAVE
पूर्ण;

#घोषणा STM32F7_I2C_DNF_DEFAULT			0
#घोषणा STM32F7_I2C_DNF_MAX			15

#घोषणा STM32F7_I2C_ANALOG_FILTER_DELAY_MIN	50	/* ns */
#घोषणा STM32F7_I2C_ANALOG_FILTER_DELAY_MAX	260	/* ns */

#घोषणा STM32F7_I2C_RISE_TIME_DEFAULT		25	/* ns */
#घोषणा STM32F7_I2C_FALL_TIME_DEFAULT		10	/* ns */

#घोषणा STM32F7_PRESC_MAX			BIT(4)
#घोषणा STM32F7_SCLDEL_MAX			BIT(4)
#घोषणा STM32F7_SDADEL_MAX			BIT(4)
#घोषणा STM32F7_SCLH_MAX			BIT(8)
#घोषणा STM32F7_SCLL_MAX			BIT(8)

#घोषणा STM32F7_AUTOSUSPEND_DELAY		(HZ / 100)

/**
 * काष्ठा sपंचांग32f7_i2c_regs - i2c f7 रेजिस्टरs backup
 * @cr1: Control रेजिस्टर 1
 * @cr2: Control रेजिस्टर 2
 * @oar1: Own address 1 रेजिस्टर
 * @oar2: Own address 2 रेजिस्टर
 * @पंचांगgr: Timing रेजिस्टर
 */
काष्ठा sपंचांग32f7_i2c_regs अणु
	u32 cr1;
	u32 cr2;
	u32 oar1;
	u32 oar2;
	u32 पंचांगgr;
पूर्ण;

/**
 * काष्ठा sपंचांग32f7_i2c_spec - निजी i2c specअगरication timing
 * @rate: I2C bus speed (Hz)
 * @fall_max: Max fall समय of both SDA and SCL संकेतs (ns)
 * @rise_max: Max rise समय of both SDA and SCL संकेतs (ns)
 * @hddat_min: Min data hold समय (ns)
 * @vddat_max: Max data valid समय (ns)
 * @sudat_min: Min data setup समय (ns)
 * @l_min: Min low period of the SCL घड़ी (ns)
 * @h_min: Min high period of the SCL घड़ी (ns)
 */
काष्ठा sपंचांग32f7_i2c_spec अणु
	u32 rate;
	u32 fall_max;
	u32 rise_max;
	u32 hddat_min;
	u32 vddat_max;
	u32 sudat_min;
	u32 l_min;
	u32 h_min;
पूर्ण;

/**
 * काष्ठा sपंचांग32f7_i2c_setup - निजी I2C timing setup parameters
 * @speed_freq: I2C speed frequency  (Hz)
 * @घड़ी_src: I2C घड़ी source frequency (Hz)
 * @rise_समय: Rise समय (ns)
 * @fall_समय: Fall समय (ns)
 * @fmp_clr_offset: Fast Mode Plus clear रेजिस्टर offset from set रेजिस्टर
 */
काष्ठा sपंचांग32f7_i2c_setup अणु
	u32 speed_freq;
	u32 घड़ी_src;
	u32 rise_समय;
	u32 fall_समय;
	u32 fmp_clr_offset;
पूर्ण;

/**
 * काष्ठा sपंचांग32f7_i2c_timings - निजी I2C output parameters
 * @node: List entry
 * @presc: Prescaler value
 * @scldel: Data setup समय
 * @sdadel: Data hold समय
 * @sclh: SCL high period (master mode)
 * @scll: SCL low period (master mode)
 */
काष्ठा sपंचांग32f7_i2c_timings अणु
	काष्ठा list_head node;
	u8 presc;
	u8 scldel;
	u8 sdadel;
	u8 sclh;
	u8 scll;
पूर्ण;

/**
 * काष्ठा sपंचांग32f7_i2c_msg - client specअगरic data
 * @addr: 8-bit or 10-bit slave addr, including r/w bit
 * @count: number of bytes to be transferred
 * @buf: data buffer
 * @result: result of the transfer
 * @stop: last I2C msg to be sent, i.e. STOP to be generated
 * @smbus: boolean to know अगर the I2C IP is used in SMBus mode
 * @size: type of SMBus protocol
 * @पढ़ो_ग_लिखो: direction of SMBus protocol
 * SMBus block पढ़ो and SMBus block ग_लिखो - block पढ़ो process call protocols
 * @smbus_buf: buffer to be used क्रम SMBus protocol transfer. It will
 * contain a maximum of 32 bytes of data + byte command + byte count + PEC
 * This buffer has to be 32-bit aligned to be compliant with memory address
 * रेजिस्टर in DMA mode.
 */
काष्ठा sपंचांग32f7_i2c_msg अणु
	u16 addr;
	u32 count;
	u8 *buf;
	पूर्णांक result;
	bool stop;
	bool smbus;
	पूर्णांक size;
	अक्षर पढ़ो_ग_लिखो;
	u8 smbus_buf[I2C_SMBUS_BLOCK_MAX + 3] __aligned(4);
पूर्ण;

/**
 * काष्ठा sपंचांग32f7_i2c_dev - निजी data of the controller
 * @adap: I2C adapter क्रम this controller
 * @dev: device क्रम this controller
 * @base: भव memory area
 * @complete: completion of I2C message
 * @clk: hw i2c घड़ी
 * @bus_rate: I2C घड़ी frequency of the controller
 * @msg: Poपूर्णांकer to data to be written
 * @msg_num: number of I2C messages to be executed
 * @msg_id: message identअगरiant
 * @f7_msg: customized i2c msg क्रम driver usage
 * @setup: I2C timing input setup
 * @timing: I2C computed timings
 * @slave: list of slave devices रेजिस्टरed on the I2C bus
 * @slave_running: slave device currently used
 * @backup_regs: backup of i2c controller रेजिस्टरs (क्रम suspend/resume)
 * @slave_dir: transfer direction क्रम the current slave device
 * @master_mode: boolean to know in which mode the I2C is running (master or
 * slave)
 * @dma: dma data
 * @use_dma: boolean to know अगर dma is used in the current transfer
 * @regmap: holds SYSCFG phandle क्रम Fast Mode Plus bits
 * @fmp_sreg: रेजिस्टर address क्रम setting Fast Mode Plus bits
 * @fmp_creg: रेजिस्टर address क्रम clearing Fast Mode Plus bits
 * @fmp_mask: mask क्रम Fast Mode Plus bits in set रेजिस्टर
 * @wakeup_src: boolean to know अगर the device is a wakeup source
 * @smbus_mode: states that the controller is configured in SMBus mode
 * @host_notअगरy_client: SMBus host-notअगरy client
 * @analog_filter: boolean to indicate enabling of the analog filter
 * @dnf_dt: value of digital filter requested via dt
 * @dnf: value of digital filter to apply
 */
काष्ठा sपंचांग32f7_i2c_dev अणु
	काष्ठा i2c_adapter adap;
	काष्ठा device *dev;
	व्योम __iomem *base;
	काष्ठा completion complete;
	काष्ठा clk *clk;
	अचिन्हित पूर्णांक bus_rate;
	काष्ठा i2c_msg *msg;
	अचिन्हित पूर्णांक msg_num;
	अचिन्हित पूर्णांक msg_id;
	काष्ठा sपंचांग32f7_i2c_msg f7_msg;
	काष्ठा sपंचांग32f7_i2c_setup setup;
	काष्ठा sपंचांग32f7_i2c_timings timing;
	काष्ठा i2c_client *slave[STM32F7_I2C_MAX_SLAVE];
	काष्ठा i2c_client *slave_running;
	काष्ठा sपंचांग32f7_i2c_regs backup_regs;
	u32 slave_dir;
	bool master_mode;
	काष्ठा sपंचांग32_i2c_dma *dma;
	bool use_dma;
	काष्ठा regmap *regmap;
	u32 fmp_sreg;
	u32 fmp_creg;
	u32 fmp_mask;
	bool wakeup_src;
	bool smbus_mode;
	काष्ठा i2c_client *host_notअगरy_client;
	bool analog_filter;
	u32 dnf_dt;
	u32 dnf;
पूर्ण;

/*
 * All these values are coming from I2C Specअगरication, Version 6.0, 4th of
 * April 2014.
 *
 * Table10. Characteristics of the SDA and SCL bus lines क्रम Standard, Fast,
 * and Fast-mode Plus I2C-bus devices
 */
अटल काष्ठा sपंचांग32f7_i2c_spec sपंचांग32f7_i2c_specs[] = अणु
	अणु
		.rate = I2C_MAX_STANDARD_MODE_FREQ,
		.fall_max = 300,
		.rise_max = 1000,
		.hddat_min = 0,
		.vddat_max = 3450,
		.sudat_min = 250,
		.l_min = 4700,
		.h_min = 4000,
	पूर्ण,
	अणु
		.rate = I2C_MAX_FAST_MODE_FREQ,
		.fall_max = 300,
		.rise_max = 300,
		.hddat_min = 0,
		.vddat_max = 900,
		.sudat_min = 100,
		.l_min = 1300,
		.h_min = 600,
	पूर्ण,
	अणु
		.rate = I2C_MAX_FAST_MODE_PLUS_FREQ,
		.fall_max = 100,
		.rise_max = 120,
		.hddat_min = 0,
		.vddat_max = 450,
		.sudat_min = 50,
		.l_min = 500,
		.h_min = 260,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा sपंचांग32f7_i2c_setup sपंचांग32f7_setup = अणु
	.rise_समय = STM32F7_I2C_RISE_TIME_DEFAULT,
	.fall_समय = STM32F7_I2C_FALL_TIME_DEFAULT,
पूर्ण;

अटल स्थिर काष्ठा sपंचांग32f7_i2c_setup sपंचांग32mp15_setup = अणु
	.rise_समय = STM32F7_I2C_RISE_TIME_DEFAULT,
	.fall_समय = STM32F7_I2C_FALL_TIME_DEFAULT,
	.fmp_clr_offset = 0x40,
पूर्ण;

अटल अंतरभूत व्योम sपंचांग32f7_i2c_set_bits(व्योम __iomem *reg, u32 mask)
अणु
	ग_लिखोl_relaxed(पढ़ोl_relaxed(reg) | mask, reg);
पूर्ण

अटल अंतरभूत व्योम sपंचांग32f7_i2c_clr_bits(व्योम __iomem *reg, u32 mask)
अणु
	ग_लिखोl_relaxed(पढ़ोl_relaxed(reg) & ~mask, reg);
पूर्ण

अटल व्योम sपंचांग32f7_i2c_disable_irq(काष्ठा sपंचांग32f7_i2c_dev *i2c_dev, u32 mask)
अणु
	sपंचांग32f7_i2c_clr_bits(i2c_dev->base + STM32F7_I2C_CR1, mask);
पूर्ण

अटल काष्ठा sपंचांग32f7_i2c_spec *sपंचांग32f7_get_specs(u32 rate)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(sपंचांग32f7_i2c_specs); i++)
		अगर (rate <= sपंचांग32f7_i2c_specs[i].rate)
			वापस &sपंचांग32f7_i2c_specs[i];

	वापस ERR_PTR(-EINVAL);
पूर्ण

#घोषणा	RATE_MIN(rate)	((rate) * 8 / 10)
अटल पूर्णांक sपंचांग32f7_i2c_compute_timing(काष्ठा sपंचांग32f7_i2c_dev *i2c_dev,
				      काष्ठा sपंचांग32f7_i2c_setup *setup,
				      काष्ठा sपंचांग32f7_i2c_timings *output)
अणु
	काष्ठा sपंचांग32f7_i2c_spec *specs;
	u32 p_prev = STM32F7_PRESC_MAX;
	u32 i2cclk = DIV_ROUND_CLOSEST(NSEC_PER_SEC,
				       setup->घड़ी_src);
	u32 i2cbus = DIV_ROUND_CLOSEST(NSEC_PER_SEC,
				       setup->speed_freq);
	u32 clk_error_prev = i2cbus;
	u32 tsync;
	u32 af_delay_min, af_delay_max;
	u32 dnf_delay;
	u32 clk_min, clk_max;
	पूर्णांक sdadel_min, sdadel_max;
	पूर्णांक scldel_min;
	काष्ठा sपंचांग32f7_i2c_timings *v, *_v, *s;
	काष्ठा list_head solutions;
	u16 p, l, a, h;
	पूर्णांक ret = 0;

	specs = sपंचांग32f7_get_specs(setup->speed_freq);
	अगर (specs == ERR_PTR(-EINVAL)) अणु
		dev_err(i2c_dev->dev, "speed out of bound {%d}\n",
			setup->speed_freq);
		वापस -EINVAL;
	पूर्ण

	अगर ((setup->rise_समय > specs->rise_max) ||
	    (setup->fall_समय > specs->fall_max)) अणु
		dev_err(i2c_dev->dev,
			"timings out of bound Rise{%d>%d}/Fall{%d>%d}\n",
			setup->rise_समय, specs->rise_max,
			setup->fall_समय, specs->fall_max);
		वापस -EINVAL;
	पूर्ण

	i2c_dev->dnf = DIV_ROUND_CLOSEST(i2c_dev->dnf_dt, i2cclk);
	अगर (i2c_dev->dnf > STM32F7_I2C_DNF_MAX) अणु
		dev_err(i2c_dev->dev,
			"DNF out of bound %d/%d\n",
			i2c_dev->dnf * i2cclk, STM32F7_I2C_DNF_MAX * i2cclk);
		वापस -EINVAL;
	पूर्ण

	/*  Analog and Digital Filters */
	af_delay_min =
		(i2c_dev->analog_filter ?
		 STM32F7_I2C_ANALOG_FILTER_DELAY_MIN : 0);
	af_delay_max =
		(i2c_dev->analog_filter ?
		 STM32F7_I2C_ANALOG_FILTER_DELAY_MAX : 0);
	dnf_delay = i2c_dev->dnf * i2cclk;

	sdadel_min = specs->hddat_min + setup->fall_समय -
		af_delay_min - (i2c_dev->dnf + 3) * i2cclk;

	sdadel_max = specs->vddat_max - setup->rise_समय -
		af_delay_max - (i2c_dev->dnf + 4) * i2cclk;

	scldel_min = setup->rise_समय + specs->sudat_min;

	अगर (sdadel_min < 0)
		sdadel_min = 0;
	अगर (sdadel_max < 0)
		sdadel_max = 0;

	dev_dbg(i2c_dev->dev, "SDADEL(min/max): %i/%i, SCLDEL(Min): %i\n",
		sdadel_min, sdadel_max, scldel_min);

	INIT_LIST_HEAD(&solutions);
	/* Compute possible values क्रम PRESC, SCLDEL and SDADEL */
	क्रम (p = 0; p < STM32F7_PRESC_MAX; p++) अणु
		क्रम (l = 0; l < STM32F7_SCLDEL_MAX; l++) अणु
			u32 scldel = (l + 1) * (p + 1) * i2cclk;

			अगर (scldel < scldel_min)
				जारी;

			क्रम (a = 0; a < STM32F7_SDADEL_MAX; a++) अणु
				u32 sdadel = (a * (p + 1) + 1) * i2cclk;

				अगर (((sdadel >= sdadel_min) &&
				     (sdadel <= sdadel_max)) &&
				    (p != p_prev)) अणु
					v = kदो_स्मृति(माप(*v), GFP_KERNEL);
					अगर (!v) अणु
						ret = -ENOMEM;
						जाओ निकास;
					पूर्ण

					v->presc = p;
					v->scldel = l;
					v->sdadel = a;
					p_prev = p;

					list_add_tail(&v->node,
						      &solutions);
					अवरोध;
				पूर्ण
			पूर्ण

			अगर (p_prev == p)
				अवरोध;
		पूर्ण
	पूर्ण

	अगर (list_empty(&solutions)) अणु
		dev_err(i2c_dev->dev, "no Prescaler solution\n");
		ret = -EPERM;
		जाओ निकास;
	पूर्ण

	tsync = af_delay_min + dnf_delay + (2 * i2cclk);
	s = शून्य;
	clk_max = NSEC_PER_SEC / RATE_MIN(setup->speed_freq);
	clk_min = NSEC_PER_SEC / setup->speed_freq;

	/*
	 * Among Prescaler possibilities discovered above figures out SCL Low
	 * and High Period. Provided:
	 * - SCL Low Period has to be higher than SCL Clock Low Period
	 *   defined by I2C Specअगरication. I2C Clock has to be lower than
	 *   (SCL Low Period - Analog/Digital filters) / 4.
	 * - SCL High Period has to be lower than SCL Clock High Period
	 *   defined by I2C Specअगरication
	 * - I2C Clock has to be lower than SCL High Period
	 */
	list_क्रम_each_entry(v, &solutions, node) अणु
		u32 prescaler = (v->presc + 1) * i2cclk;

		क्रम (l = 0; l < STM32F7_SCLL_MAX; l++) अणु
			u32 tscl_l = (l + 1) * prescaler + tsync;

			अगर ((tscl_l < specs->l_min) ||
			    (i2cclk >=
			     ((tscl_l - af_delay_min - dnf_delay) / 4))) अणु
				जारी;
			पूर्ण

			क्रम (h = 0; h < STM32F7_SCLH_MAX; h++) अणु
				u32 tscl_h = (h + 1) * prescaler + tsync;
				u32 tscl = tscl_l + tscl_h +
					setup->rise_समय + setup->fall_समय;

				अगर ((tscl >= clk_min) && (tscl <= clk_max) &&
				    (tscl_h >= specs->h_min) &&
				    (i2cclk < tscl_h)) अणु
					पूर्णांक clk_error = tscl - i2cbus;

					अगर (clk_error < 0)
						clk_error = -clk_error;

					अगर (clk_error < clk_error_prev) अणु
						clk_error_prev = clk_error;
						v->scll = l;
						v->sclh = h;
						s = v;
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!s) अणु
		dev_err(i2c_dev->dev, "no solution at all\n");
		ret = -EPERM;
		जाओ निकास;
	पूर्ण

	output->presc = s->presc;
	output->scldel = s->scldel;
	output->sdadel = s->sdadel;
	output->scll = s->scll;
	output->sclh = s->sclh;

	dev_dbg(i2c_dev->dev,
		"Presc: %i, scldel: %i, sdadel: %i, scll: %i, sclh: %i\n",
		output->presc,
		output->scldel, output->sdadel,
		output->scll, output->sclh);

निकास:
	/* Release list and memory */
	list_क्रम_each_entry_safe(v, _v, &solutions, node) अणु
		list_del(&v->node);
		kमुक्त(v);
	पूर्ण

	वापस ret;
पूर्ण

अटल u32 sपंचांग32f7_get_lower_rate(u32 rate)
अणु
	पूर्णांक i = ARRAY_SIZE(sपंचांग32f7_i2c_specs);

	जबतक (--i)
		अगर (sपंचांग32f7_i2c_specs[i].rate < rate)
			अवरोध;

	वापस sपंचांग32f7_i2c_specs[i].rate;
पूर्ण

अटल पूर्णांक sपंचांग32f7_i2c_setup_timing(काष्ठा sपंचांग32f7_i2c_dev *i2c_dev,
				    काष्ठा sपंचांग32f7_i2c_setup *setup)
अणु
	काष्ठा i2c_timings timings, *t = &timings;
	पूर्णांक ret = 0;

	t->bus_freq_hz = I2C_MAX_STANDARD_MODE_FREQ;
	t->scl_rise_ns = i2c_dev->setup.rise_समय;
	t->scl_fall_ns = i2c_dev->setup.fall_समय;

	i2c_parse_fw_timings(i2c_dev->dev, t, false);

	अगर (t->bus_freq_hz > I2C_MAX_FAST_MODE_PLUS_FREQ) अणु
		dev_err(i2c_dev->dev, "Invalid bus speed (%i>%i)\n",
			t->bus_freq_hz, I2C_MAX_FAST_MODE_PLUS_FREQ);
		वापस -EINVAL;
	पूर्ण

	setup->speed_freq = t->bus_freq_hz;
	i2c_dev->setup.rise_समय = t->scl_rise_ns;
	i2c_dev->setup.fall_समय = t->scl_fall_ns;
	i2c_dev->dnf_dt = t->digital_filter_width_ns;
	setup->घड़ी_src = clk_get_rate(i2c_dev->clk);

	अगर (!setup->घड़ी_src) अणु
		dev_err(i2c_dev->dev, "clock rate is 0\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!of_property_पढ़ो_bool(i2c_dev->dev->of_node, "i2c-digital-filter"))
		i2c_dev->dnf_dt = STM32F7_I2C_DNF_DEFAULT;

	करो अणु
		ret = sपंचांग32f7_i2c_compute_timing(i2c_dev, setup,
						 &i2c_dev->timing);
		अगर (ret) अणु
			dev_err(i2c_dev->dev,
				"failed to compute I2C timings.\n");
			अगर (setup->speed_freq <= I2C_MAX_STANDARD_MODE_FREQ)
				अवरोध;
			setup->speed_freq =
				sपंचांग32f7_get_lower_rate(setup->speed_freq);
			dev_warn(i2c_dev->dev,
				 "downgrade I2C Speed Freq to (%i)\n",
				 setup->speed_freq);
		पूर्ण
	पूर्ण जबतक (ret);

	अगर (ret) अणु
		dev_err(i2c_dev->dev, "Impossible to compute I2C timings.\n");
		वापस ret;
	पूर्ण

	i2c_dev->analog_filter = of_property_पढ़ो_bool(i2c_dev->dev->of_node,
						       "i2c-analog-filter");

	dev_dbg(i2c_dev->dev, "I2C Speed(%i), Clk Source(%i)\n",
		setup->speed_freq, setup->घड़ी_src);
	dev_dbg(i2c_dev->dev, "I2C Rise(%i) and Fall(%i) Time\n",
		setup->rise_समय, setup->fall_समय);
	dev_dbg(i2c_dev->dev, "I2C Analog Filter(%s), DNF(%i)\n",
		(i2c_dev->analog_filter ? "On" : "Off"), i2c_dev->dnf);

	i2c_dev->bus_rate = setup->speed_freq;

	वापस 0;
पूर्ण

अटल व्योम sपंचांग32f7_i2c_disable_dma_req(काष्ठा sपंचांग32f7_i2c_dev *i2c_dev)
अणु
	व्योम __iomem *base = i2c_dev->base;
	u32 mask = STM32F7_I2C_CR1_RXDMAEN | STM32F7_I2C_CR1_TXDMAEN;

	sपंचांग32f7_i2c_clr_bits(base + STM32F7_I2C_CR1, mask);
पूर्ण

अटल व्योम sपंचांग32f7_i2c_dma_callback(व्योम *arg)
अणु
	काष्ठा sपंचांग32f7_i2c_dev *i2c_dev = (काष्ठा sपंचांग32f7_i2c_dev *)arg;
	काष्ठा sपंचांग32_i2c_dma *dma = i2c_dev->dma;
	काष्ठा device *dev = dma->chan_using->device->dev;

	sपंचांग32f7_i2c_disable_dma_req(i2c_dev);
	dma_unmap_single(dev, dma->dma_buf, dma->dma_len, dma->dma_data_dir);
	complete(&dma->dma_complete);
पूर्ण

अटल व्योम sपंचांग32f7_i2c_hw_config(काष्ठा sपंचांग32f7_i2c_dev *i2c_dev)
अणु
	काष्ठा sपंचांग32f7_i2c_timings *t = &i2c_dev->timing;
	u32 timing = 0;

	/* Timing settings */
	timing |= STM32F7_I2C_TIMINGR_PRESC(t->presc);
	timing |= STM32F7_I2C_TIMINGR_SCLDEL(t->scldel);
	timing |= STM32F7_I2C_TIMINGR_SDADEL(t->sdadel);
	timing |= STM32F7_I2C_TIMINGR_SCLH(t->sclh);
	timing |= STM32F7_I2C_TIMINGR_SCLL(t->scll);
	ग_लिखोl_relaxed(timing, i2c_dev->base + STM32F7_I2C_TIMINGR);

	/* Configure the Analog Filter */
	अगर (i2c_dev->analog_filter)
		sपंचांग32f7_i2c_clr_bits(i2c_dev->base + STM32F7_I2C_CR1,
				     STM32F7_I2C_CR1_ANFOFF);
	अन्यथा
		sपंचांग32f7_i2c_set_bits(i2c_dev->base + STM32F7_I2C_CR1,
				     STM32F7_I2C_CR1_ANFOFF);

	/* Program the Digital Filter */
	sपंचांग32f7_i2c_clr_bits(i2c_dev->base + STM32F7_I2C_CR1,
			     STM32F7_I2C_CR1_DNF_MASK);
	sपंचांग32f7_i2c_set_bits(i2c_dev->base + STM32F7_I2C_CR1,
			     STM32F7_I2C_CR1_DNF(i2c_dev->dnf));

	sपंचांग32f7_i2c_set_bits(i2c_dev->base + STM32F7_I2C_CR1,
			     STM32F7_I2C_CR1_PE);
पूर्ण

अटल व्योम sपंचांग32f7_i2c_ग_लिखो_tx_data(काष्ठा sपंचांग32f7_i2c_dev *i2c_dev)
अणु
	काष्ठा sपंचांग32f7_i2c_msg *f7_msg = &i2c_dev->f7_msg;
	व्योम __iomem *base = i2c_dev->base;

	अगर (f7_msg->count) अणु
		ग_लिखोb_relaxed(*f7_msg->buf++, base + STM32F7_I2C_TXDR);
		f7_msg->count--;
	पूर्ण
पूर्ण

अटल व्योम sपंचांग32f7_i2c_पढ़ो_rx_data(काष्ठा sपंचांग32f7_i2c_dev *i2c_dev)
अणु
	काष्ठा sपंचांग32f7_i2c_msg *f7_msg = &i2c_dev->f7_msg;
	व्योम __iomem *base = i2c_dev->base;

	अगर (f7_msg->count) अणु
		*f7_msg->buf++ = पढ़ोb_relaxed(base + STM32F7_I2C_RXDR);
		f7_msg->count--;
	पूर्ण अन्यथा अणु
		/* Flush RX buffer has no data is expected */
		पढ़ोb_relaxed(base + STM32F7_I2C_RXDR);
	पूर्ण
पूर्ण

अटल व्योम sपंचांग32f7_i2c_reload(काष्ठा sपंचांग32f7_i2c_dev *i2c_dev)
अणु
	काष्ठा sपंचांग32f7_i2c_msg *f7_msg = &i2c_dev->f7_msg;
	u32 cr2;

	अगर (i2c_dev->use_dma)
		f7_msg->count -= STM32F7_I2C_MAX_LEN;

	cr2 = पढ़ोl_relaxed(i2c_dev->base + STM32F7_I2C_CR2);

	cr2 &= ~STM32F7_I2C_CR2_NBYTES_MASK;
	अगर (f7_msg->count > STM32F7_I2C_MAX_LEN) अणु
		cr2 |= STM32F7_I2C_CR2_NBYTES(STM32F7_I2C_MAX_LEN);
	पूर्ण अन्यथा अणु
		cr2 &= ~STM32F7_I2C_CR2_RELOAD;
		cr2 |= STM32F7_I2C_CR2_NBYTES(f7_msg->count);
	पूर्ण

	ग_लिखोl_relaxed(cr2, i2c_dev->base + STM32F7_I2C_CR2);
पूर्ण

अटल व्योम sपंचांग32f7_i2c_smbus_reload(काष्ठा sपंचांग32f7_i2c_dev *i2c_dev)
अणु
	काष्ठा sपंचांग32f7_i2c_msg *f7_msg = &i2c_dev->f7_msg;
	u32 cr2;
	u8 *val;

	/*
	 * For I2C_SMBUS_BLOCK_DATA && I2C_SMBUS_BLOCK_PROC_CALL, the first
	 * data received inक्रमm us how many data will follow.
	 */
	sपंचांग32f7_i2c_पढ़ो_rx_data(i2c_dev);

	/*
	 * Update NBYTES with the value पढ़ो to जारी the transfer
	 */
	val = f7_msg->buf - माप(u8);
	f7_msg->count = *val;
	cr2 = पढ़ोl_relaxed(i2c_dev->base + STM32F7_I2C_CR2);
	cr2 &= ~(STM32F7_I2C_CR2_NBYTES_MASK | STM32F7_I2C_CR2_RELOAD);
	cr2 |= STM32F7_I2C_CR2_NBYTES(f7_msg->count);
	ग_लिखोl_relaxed(cr2, i2c_dev->base + STM32F7_I2C_CR2);
पूर्ण

अटल पूर्णांक sपंचांग32f7_i2c_release_bus(काष्ठा i2c_adapter *i2c_adap)
अणु
	काष्ठा sपंचांग32f7_i2c_dev *i2c_dev = i2c_get_adapdata(i2c_adap);

	dev_info(i2c_dev->dev, "Trying to recover bus\n");

	sपंचांग32f7_i2c_clr_bits(i2c_dev->base + STM32F7_I2C_CR1,
			     STM32F7_I2C_CR1_PE);

	sपंचांग32f7_i2c_hw_config(i2c_dev);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32f7_i2c_रुको_मुक्त_bus(काष्ठा sपंचांग32f7_i2c_dev *i2c_dev)
अणु
	u32 status;
	पूर्णांक ret;

	ret = पढ़ोl_relaxed_poll_समयout(i2c_dev->base + STM32F7_I2C_ISR,
					 status,
					 !(status & STM32F7_I2C_ISR_BUSY),
					 10, 1000);
	अगर (!ret)
		वापस 0;

	dev_info(i2c_dev->dev, "bus busy\n");

	ret = sपंचांग32f7_i2c_release_bus(&i2c_dev->adap);
	अगर (ret) अणु
		dev_err(i2c_dev->dev, "Failed to recover the bus (%d)\n", ret);
		वापस ret;
	पूर्ण

	वापस -EBUSY;
पूर्ण

अटल व्योम sपंचांग32f7_i2c_xfer_msg(काष्ठा sपंचांग32f7_i2c_dev *i2c_dev,
				 काष्ठा i2c_msg *msg)
अणु
	काष्ठा sपंचांग32f7_i2c_msg *f7_msg = &i2c_dev->f7_msg;
	व्योम __iomem *base = i2c_dev->base;
	u32 cr1, cr2;
	पूर्णांक ret;

	f7_msg->addr = msg->addr;
	f7_msg->buf = msg->buf;
	f7_msg->count = msg->len;
	f7_msg->result = 0;
	f7_msg->stop = (i2c_dev->msg_id >= i2c_dev->msg_num - 1);

	reinit_completion(&i2c_dev->complete);

	cr1 = पढ़ोl_relaxed(base + STM32F7_I2C_CR1);
	cr2 = पढ़ोl_relaxed(base + STM32F7_I2C_CR2);

	/* Set transfer direction */
	cr2 &= ~STM32F7_I2C_CR2_RD_WRN;
	अगर (msg->flags & I2C_M_RD)
		cr2 |= STM32F7_I2C_CR2_RD_WRN;

	/* Set slave address */
	cr2 &= ~(STM32F7_I2C_CR2_HEAD10R | STM32F7_I2C_CR2_ADD10);
	अगर (msg->flags & I2C_M_TEN) अणु
		cr2 &= ~STM32F7_I2C_CR2_SADD10_MASK;
		cr2 |= STM32F7_I2C_CR2_SADD10(f7_msg->addr);
		cr2 |= STM32F7_I2C_CR2_ADD10;
	पूर्ण अन्यथा अणु
		cr2 &= ~STM32F7_I2C_CR2_SADD7_MASK;
		cr2 |= STM32F7_I2C_CR2_SADD7(f7_msg->addr);
	पूर्ण

	/* Set nb bytes to transfer and reload अगर needed */
	cr2 &= ~(STM32F7_I2C_CR2_NBYTES_MASK | STM32F7_I2C_CR2_RELOAD);
	अगर (f7_msg->count > STM32F7_I2C_MAX_LEN) अणु
		cr2 |= STM32F7_I2C_CR2_NBYTES(STM32F7_I2C_MAX_LEN);
		cr2 |= STM32F7_I2C_CR2_RELOAD;
	पूर्ण अन्यथा अणु
		cr2 |= STM32F7_I2C_CR2_NBYTES(f7_msg->count);
	पूर्ण

	/* Enable NACK, STOP, error and transfer complete पूर्णांकerrupts */
	cr1 |= STM32F7_I2C_CR1_ERRIE | STM32F7_I2C_CR1_TCIE |
		STM32F7_I2C_CR1_STOPIE | STM32F7_I2C_CR1_NACKIE;

	/* Clear DMA req and TX/RX पूर्णांकerrupt */
	cr1 &= ~(STM32F7_I2C_CR1_RXIE | STM32F7_I2C_CR1_TXIE |
			STM32F7_I2C_CR1_RXDMAEN | STM32F7_I2C_CR1_TXDMAEN);

	/* Configure DMA or enable RX/TX पूर्णांकerrupt */
	i2c_dev->use_dma = false;
	अगर (i2c_dev->dma && f7_msg->count >= STM32F7_I2C_DMA_LEN_MIN) अणु
		ret = sपंचांग32_i2c_prep_dma_xfer(i2c_dev->dev, i2c_dev->dma,
					      msg->flags & I2C_M_RD,
					      f7_msg->count, f7_msg->buf,
					      sपंचांग32f7_i2c_dma_callback,
					      i2c_dev);
		अगर (!ret)
			i2c_dev->use_dma = true;
		अन्यथा
			dev_warn(i2c_dev->dev, "can't use DMA\n");
	पूर्ण

	अगर (!i2c_dev->use_dma) अणु
		अगर (msg->flags & I2C_M_RD)
			cr1 |= STM32F7_I2C_CR1_RXIE;
		अन्यथा
			cr1 |= STM32F7_I2C_CR1_TXIE;
	पूर्ण अन्यथा अणु
		अगर (msg->flags & I2C_M_RD)
			cr1 |= STM32F7_I2C_CR1_RXDMAEN;
		अन्यथा
			cr1 |= STM32F7_I2C_CR1_TXDMAEN;
	पूर्ण

	/* Configure Start/Repeated Start */
	cr2 |= STM32F7_I2C_CR2_START;

	i2c_dev->master_mode = true;

	/* Write configurations रेजिस्टरs */
	ग_लिखोl_relaxed(cr1, base + STM32F7_I2C_CR1);
	ग_लिखोl_relaxed(cr2, base + STM32F7_I2C_CR2);
पूर्ण

अटल पूर्णांक sपंचांग32f7_i2c_smbus_xfer_msg(काष्ठा sपंचांग32f7_i2c_dev *i2c_dev,
				      अचिन्हित लघु flags, u8 command,
				      जोड़ i2c_smbus_data *data)
अणु
	काष्ठा sपंचांग32f7_i2c_msg *f7_msg = &i2c_dev->f7_msg;
	काष्ठा device *dev = i2c_dev->dev;
	व्योम __iomem *base = i2c_dev->base;
	u32 cr1, cr2;
	पूर्णांक i, ret;

	f7_msg->result = 0;
	reinit_completion(&i2c_dev->complete);

	cr2 = पढ़ोl_relaxed(base + STM32F7_I2C_CR2);
	cr1 = पढ़ोl_relaxed(base + STM32F7_I2C_CR1);

	/* Set transfer direction */
	cr2 &= ~STM32F7_I2C_CR2_RD_WRN;
	अगर (f7_msg->पढ़ो_ग_लिखो)
		cr2 |= STM32F7_I2C_CR2_RD_WRN;

	/* Set slave address */
	cr2 &= ~(STM32F7_I2C_CR2_ADD10 | STM32F7_I2C_CR2_SADD7_MASK);
	cr2 |= STM32F7_I2C_CR2_SADD7(f7_msg->addr);

	f7_msg->smbus_buf[0] = command;
	चयन (f7_msg->size) अणु
	हाल I2C_SMBUS_QUICK:
		f7_msg->stop = true;
		f7_msg->count = 0;
		अवरोध;
	हाल I2C_SMBUS_BYTE:
		f7_msg->stop = true;
		f7_msg->count = 1;
		अवरोध;
	हाल I2C_SMBUS_BYTE_DATA:
		अगर (f7_msg->पढ़ो_ग_लिखो) अणु
			f7_msg->stop = false;
			f7_msg->count = 1;
			cr2 &= ~STM32F7_I2C_CR2_RD_WRN;
		पूर्ण अन्यथा अणु
			f7_msg->stop = true;
			f7_msg->count = 2;
			f7_msg->smbus_buf[1] = data->byte;
		पूर्ण
		अवरोध;
	हाल I2C_SMBUS_WORD_DATA:
		अगर (f7_msg->पढ़ो_ग_लिखो) अणु
			f7_msg->stop = false;
			f7_msg->count = 1;
			cr2 &= ~STM32F7_I2C_CR2_RD_WRN;
		पूर्ण अन्यथा अणु
			f7_msg->stop = true;
			f7_msg->count = 3;
			f7_msg->smbus_buf[1] = data->word & 0xff;
			f7_msg->smbus_buf[2] = data->word >> 8;
		पूर्ण
		अवरोध;
	हाल I2C_SMBUS_BLOCK_DATA:
		अगर (f7_msg->पढ़ो_ग_लिखो) अणु
			f7_msg->stop = false;
			f7_msg->count = 1;
			cr2 &= ~STM32F7_I2C_CR2_RD_WRN;
		पूर्ण अन्यथा अणु
			f7_msg->stop = true;
			अगर (data->block[0] > I2C_SMBUS_BLOCK_MAX ||
			    !data->block[0]) अणु
				dev_err(dev, "Invalid block write size %d\n",
					data->block[0]);
				वापस -EINVAL;
			पूर्ण
			f7_msg->count = data->block[0] + 2;
			क्रम (i = 1; i < f7_msg->count; i++)
				f7_msg->smbus_buf[i] = data->block[i - 1];
		पूर्ण
		अवरोध;
	हाल I2C_SMBUS_PROC_CALL:
		f7_msg->stop = false;
		f7_msg->count = 3;
		f7_msg->smbus_buf[1] = data->word & 0xff;
		f7_msg->smbus_buf[2] = data->word >> 8;
		cr2 &= ~STM32F7_I2C_CR2_RD_WRN;
		f7_msg->पढ़ो_ग_लिखो = I2C_SMBUS_READ;
		अवरोध;
	हाल I2C_SMBUS_BLOCK_PROC_CALL:
		f7_msg->stop = false;
		अगर (data->block[0] > I2C_SMBUS_BLOCK_MAX - 1) अणु
			dev_err(dev, "Invalid block write size %d\n",
				data->block[0]);
			वापस -EINVAL;
		पूर्ण
		f7_msg->count = data->block[0] + 2;
		क्रम (i = 1; i < f7_msg->count; i++)
			f7_msg->smbus_buf[i] = data->block[i - 1];
		cr2 &= ~STM32F7_I2C_CR2_RD_WRN;
		f7_msg->पढ़ो_ग_लिखो = I2C_SMBUS_READ;
		अवरोध;
	हाल I2C_SMBUS_I2C_BLOCK_DATA:
		/* Rely on emulated i2c transfer (through master_xfer) */
		वापस -EOPNOTSUPP;
	शेष:
		dev_err(dev, "Unsupported smbus protocol %d\n", f7_msg->size);
		वापस -EOPNOTSUPP;
	पूर्ण

	f7_msg->buf = f7_msg->smbus_buf;

	/* Configure PEC */
	अगर ((flags & I2C_CLIENT_PEC) && f7_msg->size != I2C_SMBUS_QUICK) अणु
		cr1 |= STM32F7_I2C_CR1_PECEN;
		cr2 |= STM32F7_I2C_CR2_PECBYTE;
		अगर (!f7_msg->पढ़ो_ग_लिखो)
			f7_msg->count++;
	पूर्ण अन्यथा अणु
		cr1 &= ~STM32F7_I2C_CR1_PECEN;
		cr2 &= ~STM32F7_I2C_CR2_PECBYTE;
	पूर्ण

	/* Set number of bytes to be transferred */
	cr2 &= ~(STM32F7_I2C_CR2_NBYTES_MASK | STM32F7_I2C_CR2_RELOAD);
	cr2 |= STM32F7_I2C_CR2_NBYTES(f7_msg->count);

	/* Enable NACK, STOP, error and transfer complete पूर्णांकerrupts */
	cr1 |= STM32F7_I2C_CR1_ERRIE | STM32F7_I2C_CR1_TCIE |
		STM32F7_I2C_CR1_STOPIE | STM32F7_I2C_CR1_NACKIE;

	/* Clear DMA req and TX/RX पूर्णांकerrupt */
	cr1 &= ~(STM32F7_I2C_CR1_RXIE | STM32F7_I2C_CR1_TXIE |
			STM32F7_I2C_CR1_RXDMAEN | STM32F7_I2C_CR1_TXDMAEN);

	/* Configure DMA or enable RX/TX पूर्णांकerrupt */
	i2c_dev->use_dma = false;
	अगर (i2c_dev->dma && f7_msg->count >= STM32F7_I2C_DMA_LEN_MIN) अणु
		ret = sपंचांग32_i2c_prep_dma_xfer(i2c_dev->dev, i2c_dev->dma,
					      cr2 & STM32F7_I2C_CR2_RD_WRN,
					      f7_msg->count, f7_msg->buf,
					      sपंचांग32f7_i2c_dma_callback,
					      i2c_dev);
		अगर (!ret)
			i2c_dev->use_dma = true;
		अन्यथा
			dev_warn(i2c_dev->dev, "can't use DMA\n");
	पूर्ण

	अगर (!i2c_dev->use_dma) अणु
		अगर (cr2 & STM32F7_I2C_CR2_RD_WRN)
			cr1 |= STM32F7_I2C_CR1_RXIE;
		अन्यथा
			cr1 |= STM32F7_I2C_CR1_TXIE;
	पूर्ण अन्यथा अणु
		अगर (cr2 & STM32F7_I2C_CR2_RD_WRN)
			cr1 |= STM32F7_I2C_CR1_RXDMAEN;
		अन्यथा
			cr1 |= STM32F7_I2C_CR1_TXDMAEN;
	पूर्ण

	/* Set Start bit */
	cr2 |= STM32F7_I2C_CR2_START;

	i2c_dev->master_mode = true;

	/* Write configurations रेजिस्टरs */
	ग_लिखोl_relaxed(cr1, base + STM32F7_I2C_CR1);
	ग_लिखोl_relaxed(cr2, base + STM32F7_I2C_CR2);

	वापस 0;
पूर्ण

अटल व्योम sपंचांग32f7_i2c_smbus_rep_start(काष्ठा sपंचांग32f7_i2c_dev *i2c_dev)
अणु
	काष्ठा sपंचांग32f7_i2c_msg *f7_msg = &i2c_dev->f7_msg;
	व्योम __iomem *base = i2c_dev->base;
	u32 cr1, cr2;
	पूर्णांक ret;

	cr2 = पढ़ोl_relaxed(base + STM32F7_I2C_CR2);
	cr1 = पढ़ोl_relaxed(base + STM32F7_I2C_CR1);

	/* Set transfer direction */
	cr2 |= STM32F7_I2C_CR2_RD_WRN;

	चयन (f7_msg->size) अणु
	हाल I2C_SMBUS_BYTE_DATA:
		f7_msg->count = 1;
		अवरोध;
	हाल I2C_SMBUS_WORD_DATA:
	हाल I2C_SMBUS_PROC_CALL:
		f7_msg->count = 2;
		अवरोध;
	हाल I2C_SMBUS_BLOCK_DATA:
	हाल I2C_SMBUS_BLOCK_PROC_CALL:
		f7_msg->count = 1;
		cr2 |= STM32F7_I2C_CR2_RELOAD;
		अवरोध;
	पूर्ण

	f7_msg->buf = f7_msg->smbus_buf;
	f7_msg->stop = true;

	/* Add one byte क्रम PEC अगर needed */
	अगर (cr1 & STM32F7_I2C_CR1_PECEN)
		f7_msg->count++;

	/* Set number of bytes to be transferred */
	cr2 &= ~(STM32F7_I2C_CR2_NBYTES_MASK);
	cr2 |= STM32F7_I2C_CR2_NBYTES(f7_msg->count);

	/*
	 * Configure RX/TX पूर्णांकerrupt:
	 */
	cr1 &= ~(STM32F7_I2C_CR1_RXIE | STM32F7_I2C_CR1_TXIE);
	cr1 |= STM32F7_I2C_CR1_RXIE;

	/*
	 * Configure DMA or enable RX/TX पूर्णांकerrupt:
	 * For I2C_SMBUS_BLOCK_DATA and I2C_SMBUS_BLOCK_PROC_CALL we करोn't use
	 * dma as we करोn't know in advance how many data will be received
	 */
	cr1 &= ~(STM32F7_I2C_CR1_RXIE | STM32F7_I2C_CR1_TXIE |
		 STM32F7_I2C_CR1_RXDMAEN | STM32F7_I2C_CR1_TXDMAEN);

	i2c_dev->use_dma = false;
	अगर (i2c_dev->dma && f7_msg->count >= STM32F7_I2C_DMA_LEN_MIN &&
	    f7_msg->size != I2C_SMBUS_BLOCK_DATA &&
	    f7_msg->size != I2C_SMBUS_BLOCK_PROC_CALL) अणु
		ret = sपंचांग32_i2c_prep_dma_xfer(i2c_dev->dev, i2c_dev->dma,
					      cr2 & STM32F7_I2C_CR2_RD_WRN,
					      f7_msg->count, f7_msg->buf,
					      sपंचांग32f7_i2c_dma_callback,
					      i2c_dev);

		अगर (!ret)
			i2c_dev->use_dma = true;
		अन्यथा
			dev_warn(i2c_dev->dev, "can't use DMA\n");
	पूर्ण

	अगर (!i2c_dev->use_dma)
		cr1 |= STM32F7_I2C_CR1_RXIE;
	अन्यथा
		cr1 |= STM32F7_I2C_CR1_RXDMAEN;

	/* Configure Repeated Start */
	cr2 |= STM32F7_I2C_CR2_START;

	/* Write configurations रेजिस्टरs */
	ग_लिखोl_relaxed(cr1, base + STM32F7_I2C_CR1);
	ग_लिखोl_relaxed(cr2, base + STM32F7_I2C_CR2);
पूर्ण

अटल पूर्णांक sपंचांग32f7_i2c_smbus_check_pec(काष्ठा sपंचांग32f7_i2c_dev *i2c_dev)
अणु
	काष्ठा sपंचांग32f7_i2c_msg *f7_msg = &i2c_dev->f7_msg;
	u8 count, पूर्णांकernal_pec, received_pec;

	पूर्णांकernal_pec = पढ़ोl_relaxed(i2c_dev->base + STM32F7_I2C_PECR);

	चयन (f7_msg->size) अणु
	हाल I2C_SMBUS_BYTE:
	हाल I2C_SMBUS_BYTE_DATA:
		received_pec = f7_msg->smbus_buf[1];
		अवरोध;
	हाल I2C_SMBUS_WORD_DATA:
	हाल I2C_SMBUS_PROC_CALL:
		received_pec = f7_msg->smbus_buf[2];
		अवरोध;
	हाल I2C_SMBUS_BLOCK_DATA:
	हाल I2C_SMBUS_BLOCK_PROC_CALL:
		count = f7_msg->smbus_buf[0];
		received_pec = f7_msg->smbus_buf[count];
		अवरोध;
	शेष:
		dev_err(i2c_dev->dev, "Unsupported smbus protocol for PEC\n");
		वापस -EINVAL;
	पूर्ण

	अगर (पूर्णांकernal_pec != received_pec) अणु
		dev_err(i2c_dev->dev, "Bad PEC 0x%02x vs. 0x%02x\n",
			पूर्णांकernal_pec, received_pec);
		वापस -EBADMSG;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool sपंचांग32f7_i2c_is_addr_match(काष्ठा i2c_client *slave, u32 addcode)
अणु
	u32 addr;

	अगर (!slave)
		वापस false;

	अगर (slave->flags & I2C_CLIENT_TEN) अणु
		/*
		 * For 10-bit addr, addcode = 11110XY with
		 * X = Bit 9 of slave address
		 * Y = Bit 8 of slave address
		 */
		addr = slave->addr >> 8;
		addr |= 0x78;
		अगर (addr == addcode)
			वापस true;
	पूर्ण अन्यथा अणु
		addr = slave->addr & 0x7f;
		अगर (addr == addcode)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम sपंचांग32f7_i2c_slave_start(काष्ठा sपंचांग32f7_i2c_dev *i2c_dev)
अणु
	काष्ठा i2c_client *slave = i2c_dev->slave_running;
	व्योम __iomem *base = i2c_dev->base;
	u32 mask;
	u8 value = 0;

	अगर (i2c_dev->slave_dir) अणु
		/* Notअगरy i2c slave that new पढ़ो transfer is starting */
		i2c_slave_event(slave, I2C_SLAVE_READ_REQUESTED, &value);

		/*
		 * Disable slave TX config in हाल of I2C combined message
		 * (I2C Write followed by I2C Read)
		 */
		mask = STM32F7_I2C_CR2_RELOAD;
		sपंचांग32f7_i2c_clr_bits(base + STM32F7_I2C_CR2, mask);
		mask = STM32F7_I2C_CR1_SBC | STM32F7_I2C_CR1_RXIE |
		       STM32F7_I2C_CR1_TCIE;
		sपंचांग32f7_i2c_clr_bits(base + STM32F7_I2C_CR1, mask);

		/* Enable TX empty, STOP, NACK पूर्णांकerrupts */
		mask =  STM32F7_I2C_CR1_STOPIE | STM32F7_I2C_CR1_NACKIE |
			STM32F7_I2C_CR1_TXIE;
		sपंचांग32f7_i2c_set_bits(base + STM32F7_I2C_CR1, mask);

		/* Write 1st data byte */
		ग_लिखोl_relaxed(value, base + STM32F7_I2C_TXDR);
	पूर्ण अन्यथा अणु
		/* Notअगरy i2c slave that new ग_लिखो transfer is starting */
		i2c_slave_event(slave, I2C_SLAVE_WRITE_REQUESTED, &value);

		/* Set reload mode to be able to ACK/NACK each received byte */
		mask = STM32F7_I2C_CR2_RELOAD;
		sपंचांग32f7_i2c_set_bits(base + STM32F7_I2C_CR2, mask);

		/*
		 * Set STOP, NACK, RX empty and transfer complete पूर्णांकerrupts.*
		 * Set Slave Byte Control to be able to ACK/NACK each data
		 * byte received
		 */
		mask =  STM32F7_I2C_CR1_STOPIE | STM32F7_I2C_CR1_NACKIE |
			STM32F7_I2C_CR1_SBC | STM32F7_I2C_CR1_RXIE |
			STM32F7_I2C_CR1_TCIE;
		sपंचांग32f7_i2c_set_bits(base + STM32F7_I2C_CR1, mask);
	पूर्ण
पूर्ण

अटल व्योम sपंचांग32f7_i2c_slave_addr(काष्ठा sपंचांग32f7_i2c_dev *i2c_dev)
अणु
	व्योम __iomem *base = i2c_dev->base;
	u32 isr, addcode, dir, mask;
	पूर्णांक i;

	isr = पढ़ोl_relaxed(i2c_dev->base + STM32F7_I2C_ISR);
	addcode = STM32F7_I2C_ISR_ADDCODE_GET(isr);
	dir = isr & STM32F7_I2C_ISR_सूची;

	क्रम (i = 0; i < STM32F7_I2C_MAX_SLAVE; i++) अणु
		अगर (sपंचांग32f7_i2c_is_addr_match(i2c_dev->slave[i], addcode)) अणु
			i2c_dev->slave_running = i2c_dev->slave[i];
			i2c_dev->slave_dir = dir;

			/* Start I2C slave processing */
			sपंचांग32f7_i2c_slave_start(i2c_dev);

			/* Clear ADDR flag */
			mask = STM32F7_I2C_ICR_ADDRCF;
			ग_लिखोl_relaxed(mask, base + STM32F7_I2C_ICR);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक sपंचांग32f7_i2c_get_slave_id(काष्ठा sपंचांग32f7_i2c_dev *i2c_dev,
				    काष्ठा i2c_client *slave, पूर्णांक *id)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < STM32F7_I2C_MAX_SLAVE; i++) अणु
		अगर (i2c_dev->slave[i] == slave) अणु
			*id = i;
			वापस 0;
		पूर्ण
	पूर्ण

	dev_err(i2c_dev->dev, "Slave 0x%x not registered\n", slave->addr);

	वापस -ENODEV;
पूर्ण

अटल पूर्णांक sपंचांग32f7_i2c_get_मुक्त_slave_id(काष्ठा sपंचांग32f7_i2c_dev *i2c_dev,
					 काष्ठा i2c_client *slave, पूर्णांक *id)
अणु
	काष्ठा device *dev = i2c_dev->dev;
	पूर्णांक i;

	/*
	 * slave[STM32F7_SLAVE_HOSTNOTIFY] support only SMBus Host address (0x8)
	 * slave[STM32F7_SLAVE_7_10_BITS_ADDR] supports 7-bit and 10-bit slave address
	 * slave[STM32F7_SLAVE_7_BITS_ADDR] supports 7-bit slave address only
	 */
	अगर (i2c_dev->smbus_mode && (slave->addr == 0x08)) अणु
		अगर (i2c_dev->slave[STM32F7_SLAVE_HOSTNOTIFY])
			जाओ fail;
		*id = STM32F7_SLAVE_HOSTNOTIFY;
		वापस 0;
	पूर्ण

	क्रम (i = STM32F7_I2C_MAX_SLAVE - 1; i > STM32F7_SLAVE_HOSTNOTIFY; i--) अणु
		अगर ((i == STM32F7_SLAVE_7_BITS_ADDR) &&
		    (slave->flags & I2C_CLIENT_TEN))
			जारी;
		अगर (!i2c_dev->slave[i]) अणु
			*id = i;
			वापस 0;
		पूर्ण
	पूर्ण

fail:
	dev_err(dev, "Slave 0x%x could not be registered\n", slave->addr);

	वापस -EINVAL;
पूर्ण

अटल bool sपंचांग32f7_i2c_is_slave_रेजिस्टरed(काष्ठा sपंचांग32f7_i2c_dev *i2c_dev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < STM32F7_I2C_MAX_SLAVE; i++) अणु
		अगर (i2c_dev->slave[i])
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल bool sपंचांग32f7_i2c_is_slave_busy(काष्ठा sपंचांग32f7_i2c_dev *i2c_dev)
अणु
	पूर्णांक i, busy;

	busy = 0;
	क्रम (i = 0; i < STM32F7_I2C_MAX_SLAVE; i++) अणु
		अगर (i2c_dev->slave[i])
			busy++;
	पूर्ण

	वापस i == busy;
पूर्ण

अटल irqवापस_t sपंचांग32f7_i2c_slave_isr_event(काष्ठा sपंचांग32f7_i2c_dev *i2c_dev)
अणु
	व्योम __iomem *base = i2c_dev->base;
	u32 cr2, status, mask;
	u8 val;
	पूर्णांक ret;

	status = पढ़ोl_relaxed(i2c_dev->base + STM32F7_I2C_ISR);

	/* Slave transmitter mode */
	अगर (status & STM32F7_I2C_ISR_TXIS) अणु
		i2c_slave_event(i2c_dev->slave_running,
				I2C_SLAVE_READ_PROCESSED,
				&val);

		/* Write data byte */
		ग_लिखोl_relaxed(val, base + STM32F7_I2C_TXDR);
	पूर्ण

	/* Transfer Complete Reload क्रम Slave receiver mode */
	अगर (status & STM32F7_I2C_ISR_TCR || status & STM32F7_I2C_ISR_RXNE) अणु
		/*
		 * Read data byte then set NBYTES to receive next byte or NACK
		 * the current received byte
		 */
		val = पढ़ोb_relaxed(i2c_dev->base + STM32F7_I2C_RXDR);
		ret = i2c_slave_event(i2c_dev->slave_running,
				      I2C_SLAVE_WRITE_RECEIVED,
				      &val);
		अगर (!ret) अणु
			cr2 = पढ़ोl_relaxed(i2c_dev->base + STM32F7_I2C_CR2);
			cr2 |= STM32F7_I2C_CR2_NBYTES(1);
			ग_लिखोl_relaxed(cr2, i2c_dev->base + STM32F7_I2C_CR2);
		पूर्ण अन्यथा अणु
			mask = STM32F7_I2C_CR2_NACK;
			sपंचांग32f7_i2c_set_bits(base + STM32F7_I2C_CR2, mask);
		पूर्ण
	पूर्ण

	/* NACK received */
	अगर (status & STM32F7_I2C_ISR_NACKF) अणु
		dev_dbg(i2c_dev->dev, "<%s>: Receive NACK\n", __func__);
		ग_लिखोl_relaxed(STM32F7_I2C_ICR_NACKCF, base + STM32F7_I2C_ICR);
	पूर्ण

	/* STOP received */
	अगर (status & STM32F7_I2C_ISR_STOPF) अणु
		/* Disable पूर्णांकerrupts */
		sपंचांग32f7_i2c_disable_irq(i2c_dev, STM32F7_I2C_XFER_IRQ_MASK);

		अगर (i2c_dev->slave_dir) अणु
			/*
			 * Flush TX buffer in order to not used the byte in
			 * TXDR क्रम the next transfer
			 */
			mask = STM32F7_I2C_ISR_TXE;
			sपंचांग32f7_i2c_set_bits(base + STM32F7_I2C_ISR, mask);
		पूर्ण

		/* Clear STOP flag */
		ग_लिखोl_relaxed(STM32F7_I2C_ICR_STOPCF, base + STM32F7_I2C_ICR);

		/* Notअगरy i2c slave that a STOP flag has been detected */
		i2c_slave_event(i2c_dev->slave_running, I2C_SLAVE_STOP, &val);

		i2c_dev->slave_running = शून्य;
	पूर्ण

	/* Address match received */
	अगर (status & STM32F7_I2C_ISR_ADDR)
		sपंचांग32f7_i2c_slave_addr(i2c_dev);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t sपंचांग32f7_i2c_isr_event(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा sपंचांग32f7_i2c_dev *i2c_dev = data;
	काष्ठा sपंचांग32f7_i2c_msg *f7_msg = &i2c_dev->f7_msg;
	व्योम __iomem *base = i2c_dev->base;
	u32 status, mask;
	पूर्णांक ret = IRQ_HANDLED;

	/* Check अगर the पूर्णांकerrupt अगर क्रम a slave device */
	अगर (!i2c_dev->master_mode) अणु
		ret = sपंचांग32f7_i2c_slave_isr_event(i2c_dev);
		वापस ret;
	पूर्ण

	status = पढ़ोl_relaxed(i2c_dev->base + STM32F7_I2C_ISR);

	/* Tx empty */
	अगर (status & STM32F7_I2C_ISR_TXIS)
		sपंचांग32f7_i2c_ग_लिखो_tx_data(i2c_dev);

	/* RX not empty */
	अगर (status & STM32F7_I2C_ISR_RXNE)
		sपंचांग32f7_i2c_पढ़ो_rx_data(i2c_dev);

	/* NACK received */
	अगर (status & STM32F7_I2C_ISR_NACKF) अणु
		dev_dbg(i2c_dev->dev, "<%s>: Receive NACK (addr %x)\n",
			__func__, f7_msg->addr);
		ग_लिखोl_relaxed(STM32F7_I2C_ICR_NACKCF, base + STM32F7_I2C_ICR);
		f7_msg->result = -ENXIO;
	पूर्ण

	/* STOP detection flag */
	अगर (status & STM32F7_I2C_ISR_STOPF) अणु
		/* Disable पूर्णांकerrupts */
		अगर (sपंचांग32f7_i2c_is_slave_रेजिस्टरed(i2c_dev))
			mask = STM32F7_I2C_XFER_IRQ_MASK;
		अन्यथा
			mask = STM32F7_I2C_ALL_IRQ_MASK;
		sपंचांग32f7_i2c_disable_irq(i2c_dev, mask);

		/* Clear STOP flag */
		ग_लिखोl_relaxed(STM32F7_I2C_ICR_STOPCF, base + STM32F7_I2C_ICR);

		अगर (i2c_dev->use_dma) अणु
			ret = IRQ_WAKE_THREAD;
		पूर्ण अन्यथा अणु
			i2c_dev->master_mode = false;
			complete(&i2c_dev->complete);
		पूर्ण
	पूर्ण

	/* Transfer complete */
	अगर (status & STM32F7_I2C_ISR_TC) अणु
		अगर (f7_msg->stop) अणु
			mask = STM32F7_I2C_CR2_STOP;
			sपंचांग32f7_i2c_set_bits(base + STM32F7_I2C_CR2, mask);
		पूर्ण अन्यथा अगर (i2c_dev->use_dma) अणु
			ret = IRQ_WAKE_THREAD;
		पूर्ण अन्यथा अगर (f7_msg->smbus) अणु
			sपंचांग32f7_i2c_smbus_rep_start(i2c_dev);
		पूर्ण अन्यथा अणु
			i2c_dev->msg_id++;
			i2c_dev->msg++;
			sपंचांग32f7_i2c_xfer_msg(i2c_dev, i2c_dev->msg);
		पूर्ण
	पूर्ण

	अगर (status & STM32F7_I2C_ISR_TCR) अणु
		अगर (f7_msg->smbus)
			sपंचांग32f7_i2c_smbus_reload(i2c_dev);
		अन्यथा
			sपंचांग32f7_i2c_reload(i2c_dev);
	पूर्ण

	वापस ret;
पूर्ण

अटल irqवापस_t sपंचांग32f7_i2c_isr_event_thपढ़ो(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा sपंचांग32f7_i2c_dev *i2c_dev = data;
	काष्ठा sपंचांग32f7_i2c_msg *f7_msg = &i2c_dev->f7_msg;
	काष्ठा sपंचांग32_i2c_dma *dma = i2c_dev->dma;
	u32 status;
	पूर्णांक ret;

	/*
	 * Wait क्रम dma transfer completion beक्रमe sending next message or
	 * notity the end of xfer to the client
	 */
	ret = रुको_क्रम_completion_समयout(&i2c_dev->dma->dma_complete, HZ);
	अगर (!ret) अणु
		dev_dbg(i2c_dev->dev, "<%s>: Timed out\n", __func__);
		sपंचांग32f7_i2c_disable_dma_req(i2c_dev);
		dmaengine_terminate_all(dma->chan_using);
		f7_msg->result = -ETIMEDOUT;
	पूर्ण

	status = पढ़ोl_relaxed(i2c_dev->base + STM32F7_I2C_ISR);

	अगर (status & STM32F7_I2C_ISR_TC) अणु
		अगर (f7_msg->smbus) अणु
			sपंचांग32f7_i2c_smbus_rep_start(i2c_dev);
		पूर्ण अन्यथा अणु
			i2c_dev->msg_id++;
			i2c_dev->msg++;
			sपंचांग32f7_i2c_xfer_msg(i2c_dev, i2c_dev->msg);
		पूर्ण
	पूर्ण अन्यथा अणु
		i2c_dev->master_mode = false;
		complete(&i2c_dev->complete);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t sपंचांग32f7_i2c_isr_error(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा sपंचांग32f7_i2c_dev *i2c_dev = data;
	काष्ठा sपंचांग32f7_i2c_msg *f7_msg = &i2c_dev->f7_msg;
	व्योम __iomem *base = i2c_dev->base;
	काष्ठा device *dev = i2c_dev->dev;
	काष्ठा sपंचांग32_i2c_dma *dma = i2c_dev->dma;
	u32 status;

	status = पढ़ोl_relaxed(i2c_dev->base + STM32F7_I2C_ISR);

	/* Bus error */
	अगर (status & STM32F7_I2C_ISR_BERR) अणु
		dev_err(dev, "<%s>: Bus error accessing addr 0x%x\n",
			__func__, f7_msg->addr);
		ग_लिखोl_relaxed(STM32F7_I2C_ICR_BERRCF, base + STM32F7_I2C_ICR);
		sपंचांग32f7_i2c_release_bus(&i2c_dev->adap);
		f7_msg->result = -EIO;
	पूर्ण

	/* Arbitration loss */
	अगर (status & STM32F7_I2C_ISR_ARLO) अणु
		dev_dbg(dev, "<%s>: Arbitration loss accessing addr 0x%x\n",
			__func__, f7_msg->addr);
		ग_लिखोl_relaxed(STM32F7_I2C_ICR_ARLOCF, base + STM32F7_I2C_ICR);
		f7_msg->result = -EAGAIN;
	पूर्ण

	अगर (status & STM32F7_I2C_ISR_PECERR) अणु
		dev_err(dev, "<%s>: PEC error in reception accessing addr 0x%x\n",
			__func__, f7_msg->addr);
		ग_लिखोl_relaxed(STM32F7_I2C_ICR_PECCF, base + STM32F7_I2C_ICR);
		f7_msg->result = -EINVAL;
	पूर्ण

	अगर (!i2c_dev->slave_running) अणु
		u32 mask;
		/* Disable पूर्णांकerrupts */
		अगर (sपंचांग32f7_i2c_is_slave_रेजिस्टरed(i2c_dev))
			mask = STM32F7_I2C_XFER_IRQ_MASK;
		अन्यथा
			mask = STM32F7_I2C_ALL_IRQ_MASK;
		sपंचांग32f7_i2c_disable_irq(i2c_dev, mask);
	पूर्ण

	/* Disable dma */
	अगर (i2c_dev->use_dma) अणु
		sपंचांग32f7_i2c_disable_dma_req(i2c_dev);
		dmaengine_terminate_all(dma->chan_using);
	पूर्ण

	i2c_dev->master_mode = false;
	complete(&i2c_dev->complete);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक sपंचांग32f7_i2c_xfer(काष्ठा i2c_adapter *i2c_adap,
			    काष्ठा i2c_msg msgs[], पूर्णांक num)
अणु
	काष्ठा sपंचांग32f7_i2c_dev *i2c_dev = i2c_get_adapdata(i2c_adap);
	काष्ठा sपंचांग32f7_i2c_msg *f7_msg = &i2c_dev->f7_msg;
	काष्ठा sपंचांग32_i2c_dma *dma = i2c_dev->dma;
	अचिन्हित दीर्घ समय_left;
	पूर्णांक ret;

	i2c_dev->msg = msgs;
	i2c_dev->msg_num = num;
	i2c_dev->msg_id = 0;
	f7_msg->smbus = false;

	ret = pm_runसमय_resume_and_get(i2c_dev->dev);
	अगर (ret < 0)
		वापस ret;

	ret = sपंचांग32f7_i2c_रुको_मुक्त_bus(i2c_dev);
	अगर (ret)
		जाओ pm_मुक्त;

	sपंचांग32f7_i2c_xfer_msg(i2c_dev, msgs);

	समय_left = रुको_क्रम_completion_समयout(&i2c_dev->complete,
						i2c_dev->adap.समयout);
	ret = f7_msg->result;

	अगर (!समय_left) अणु
		dev_dbg(i2c_dev->dev, "Access to slave 0x%x timed out\n",
			i2c_dev->msg->addr);
		अगर (i2c_dev->use_dma)
			dmaengine_terminate_all(dma->chan_using);
		ret = -ETIMEDOUT;
	पूर्ण

pm_मुक्त:
	pm_runसमय_mark_last_busy(i2c_dev->dev);
	pm_runसमय_put_स्वतःsuspend(i2c_dev->dev);

	वापस (ret < 0) ? ret : num;
पूर्ण

अटल पूर्णांक sपंचांग32f7_i2c_smbus_xfer(काष्ठा i2c_adapter *adapter, u16 addr,
				  अचिन्हित लघु flags, अक्षर पढ़ो_ग_लिखो,
				  u8 command, पूर्णांक size,
				  जोड़ i2c_smbus_data *data)
अणु
	काष्ठा sपंचांग32f7_i2c_dev *i2c_dev = i2c_get_adapdata(adapter);
	काष्ठा sपंचांग32f7_i2c_msg *f7_msg = &i2c_dev->f7_msg;
	काष्ठा sपंचांग32_i2c_dma *dma = i2c_dev->dma;
	काष्ठा device *dev = i2c_dev->dev;
	अचिन्हित दीर्घ समयout;
	पूर्णांक i, ret;

	f7_msg->addr = addr;
	f7_msg->size = size;
	f7_msg->पढ़ो_ग_लिखो = पढ़ो_ग_लिखो;
	f7_msg->smbus = true;

	ret = pm_runसमय_resume_and_get(dev);
	अगर (ret < 0)
		वापस ret;

	ret = sपंचांग32f7_i2c_रुको_मुक्त_bus(i2c_dev);
	अगर (ret)
		जाओ pm_मुक्त;

	ret = sपंचांग32f7_i2c_smbus_xfer_msg(i2c_dev, flags, command, data);
	अगर (ret)
		जाओ pm_मुक्त;

	समयout = रुको_क्रम_completion_समयout(&i2c_dev->complete,
					      i2c_dev->adap.समयout);
	ret = f7_msg->result;
	अगर (ret)
		जाओ pm_मुक्त;

	अगर (!समयout) अणु
		dev_dbg(dev, "Access to slave 0x%x timed out\n", f7_msg->addr);
		अगर (i2c_dev->use_dma)
			dmaengine_terminate_all(dma->chan_using);
		ret = -ETIMEDOUT;
		जाओ pm_मुक्त;
	पूर्ण

	/* Check PEC */
	अगर ((flags & I2C_CLIENT_PEC) && size != I2C_SMBUS_QUICK && पढ़ो_ग_लिखो) अणु
		ret = sपंचांग32f7_i2c_smbus_check_pec(i2c_dev);
		अगर (ret)
			जाओ pm_मुक्त;
	पूर्ण

	अगर (पढ़ो_ग_लिखो && size != I2C_SMBUS_QUICK) अणु
		चयन (size) अणु
		हाल I2C_SMBUS_BYTE:
		हाल I2C_SMBUS_BYTE_DATA:
			data->byte = f7_msg->smbus_buf[0];
		अवरोध;
		हाल I2C_SMBUS_WORD_DATA:
		हाल I2C_SMBUS_PROC_CALL:
			data->word = f7_msg->smbus_buf[0] |
				(f7_msg->smbus_buf[1] << 8);
		अवरोध;
		हाल I2C_SMBUS_BLOCK_DATA:
		हाल I2C_SMBUS_BLOCK_PROC_CALL:
		क्रम (i = 0; i <= f7_msg->smbus_buf[0]; i++)
			data->block[i] = f7_msg->smbus_buf[i];
		अवरोध;
		शेष:
			dev_err(dev, "Unsupported smbus transaction\n");
			ret = -EINVAL;
		पूर्ण
	पूर्ण

pm_मुक्त:
	pm_runसमय_mark_last_busy(dev);
	pm_runसमय_put_स्वतःsuspend(dev);
	वापस ret;
पूर्ण

अटल व्योम sपंचांग32f7_i2c_enable_wakeup(काष्ठा sपंचांग32f7_i2c_dev *i2c_dev,
				      bool enable)
अणु
	व्योम __iomem *base = i2c_dev->base;
	u32 mask = STM32F7_I2C_CR1_WUPEN;

	अगर (!i2c_dev->wakeup_src)
		वापस;

	अगर (enable) अणु
		device_set_wakeup_enable(i2c_dev->dev, true);
		sपंचांग32f7_i2c_set_bits(base + STM32F7_I2C_CR1, mask);
	पूर्ण अन्यथा अणु
		device_set_wakeup_enable(i2c_dev->dev, false);
		sपंचांग32f7_i2c_clr_bits(base + STM32F7_I2C_CR1, mask);
	पूर्ण
पूर्ण

अटल पूर्णांक sपंचांग32f7_i2c_reg_slave(काष्ठा i2c_client *slave)
अणु
	काष्ठा sपंचांग32f7_i2c_dev *i2c_dev = i2c_get_adapdata(slave->adapter);
	व्योम __iomem *base = i2c_dev->base;
	काष्ठा device *dev = i2c_dev->dev;
	u32 oar1, oar2, mask;
	पूर्णांक id, ret;

	अगर (slave->flags & I2C_CLIENT_PEC) अणु
		dev_err(dev, "SMBus PEC not supported in slave mode\n");
		वापस -EINVAL;
	पूर्ण

	अगर (sपंचांग32f7_i2c_is_slave_busy(i2c_dev)) अणु
		dev_err(dev, "Too much slave registered\n");
		वापस -EBUSY;
	पूर्ण

	ret = sपंचांग32f7_i2c_get_मुक्त_slave_id(i2c_dev, slave, &id);
	अगर (ret)
		वापस ret;

	ret = pm_runसमय_resume_and_get(dev);
	अगर (ret < 0)
		वापस ret;

	अगर (!sपंचांग32f7_i2c_is_slave_रेजिस्टरed(i2c_dev))
		sपंचांग32f7_i2c_enable_wakeup(i2c_dev, true);

	चयन (id) अणु
	हाल 0:
		/* Slave SMBus Host */
		i2c_dev->slave[id] = slave;
		अवरोध;

	हाल 1:
		/* Configure Own Address 1 */
		oar1 = पढ़ोl_relaxed(i2c_dev->base + STM32F7_I2C_OAR1);
		oar1 &= ~STM32F7_I2C_OAR1_MASK;
		अगर (slave->flags & I2C_CLIENT_TEN) अणु
			oar1 |= STM32F7_I2C_OAR1_OA1_10(slave->addr);
			oar1 |= STM32F7_I2C_OAR1_OA1MODE;
		पूर्ण अन्यथा अणु
			oar1 |= STM32F7_I2C_OAR1_OA1_7(slave->addr);
		पूर्ण
		oar1 |= STM32F7_I2C_OAR1_OA1EN;
		i2c_dev->slave[id] = slave;
		ग_लिखोl_relaxed(oar1, i2c_dev->base + STM32F7_I2C_OAR1);
		अवरोध;

	हाल 2:
		/* Configure Own Address 2 */
		oar2 = पढ़ोl_relaxed(i2c_dev->base + STM32F7_I2C_OAR2);
		oar2 &= ~STM32F7_I2C_OAR2_MASK;
		अगर (slave->flags & I2C_CLIENT_TEN) अणु
			ret = -EOPNOTSUPP;
			जाओ pm_मुक्त;
		पूर्ण

		oar2 |= STM32F7_I2C_OAR2_OA2_7(slave->addr);
		oar2 |= STM32F7_I2C_OAR2_OA2EN;
		i2c_dev->slave[id] = slave;
		ग_लिखोl_relaxed(oar2, i2c_dev->base + STM32F7_I2C_OAR2);
		अवरोध;

	शेष:
		dev_err(dev, "I2C slave id not supported\n");
		ret = -ENODEV;
		जाओ pm_मुक्त;
	पूर्ण

	/* Enable ACK */
	sपंचांग32f7_i2c_clr_bits(base + STM32F7_I2C_CR2, STM32F7_I2C_CR2_NACK);

	/* Enable Address match पूर्णांकerrupt, error पूर्णांकerrupt and enable I2C  */
	mask = STM32F7_I2C_CR1_ADDRIE | STM32F7_I2C_CR1_ERRIE |
		STM32F7_I2C_CR1_PE;
	sपंचांग32f7_i2c_set_bits(base + STM32F7_I2C_CR1, mask);

	ret = 0;
pm_मुक्त:
	अगर (!sपंचांग32f7_i2c_is_slave_रेजिस्टरed(i2c_dev))
		sपंचांग32f7_i2c_enable_wakeup(i2c_dev, false);

	pm_runसमय_mark_last_busy(dev);
	pm_runसमय_put_स्वतःsuspend(dev);

	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांग32f7_i2c_unreg_slave(काष्ठा i2c_client *slave)
अणु
	काष्ठा sपंचांग32f7_i2c_dev *i2c_dev = i2c_get_adapdata(slave->adapter);
	व्योम __iomem *base = i2c_dev->base;
	u32 mask;
	पूर्णांक id, ret;

	ret = sपंचांग32f7_i2c_get_slave_id(i2c_dev, slave, &id);
	अगर (ret)
		वापस ret;

	WARN_ON(!i2c_dev->slave[id]);

	ret = pm_runसमय_resume_and_get(i2c_dev->dev);
	अगर (ret < 0)
		वापस ret;

	अगर (id == 1) अणु
		mask = STM32F7_I2C_OAR1_OA1EN;
		sपंचांग32f7_i2c_clr_bits(base + STM32F7_I2C_OAR1, mask);
	पूर्ण अन्यथा अगर (id == 2) अणु
		mask = STM32F7_I2C_OAR2_OA2EN;
		sपंचांग32f7_i2c_clr_bits(base + STM32F7_I2C_OAR2, mask);
	पूर्ण

	i2c_dev->slave[id] = शून्य;

	अगर (!sपंचांग32f7_i2c_is_slave_रेजिस्टरed(i2c_dev)) अणु
		sपंचांग32f7_i2c_disable_irq(i2c_dev, STM32F7_I2C_ALL_IRQ_MASK);
		sपंचांग32f7_i2c_enable_wakeup(i2c_dev, false);
	पूर्ण

	pm_runसमय_mark_last_busy(i2c_dev->dev);
	pm_runसमय_put_स्वतःsuspend(i2c_dev->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32f7_i2c_ग_लिखो_fm_plus_bits(काष्ठा sपंचांग32f7_i2c_dev *i2c_dev,
					  bool enable)
अणु
	पूर्णांक ret;

	अगर (i2c_dev->bus_rate <= I2C_MAX_FAST_MODE_FREQ ||
	    IS_ERR_OR_शून्य(i2c_dev->regmap))
		/* Optional */
		वापस 0;

	अगर (i2c_dev->fmp_sreg == i2c_dev->fmp_creg)
		ret = regmap_update_bits(i2c_dev->regmap,
					 i2c_dev->fmp_sreg,
					 i2c_dev->fmp_mask,
					 enable ? i2c_dev->fmp_mask : 0);
	अन्यथा
		ret = regmap_ग_लिखो(i2c_dev->regmap,
				   enable ? i2c_dev->fmp_sreg :
					    i2c_dev->fmp_creg,
				   i2c_dev->fmp_mask);

	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांग32f7_i2c_setup_fm_plus_bits(काष्ठा platक्रमm_device *pdev,
					  काष्ठा sपंचांग32f7_i2c_dev *i2c_dev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	पूर्णांक ret;

	i2c_dev->regmap = syscon_regmap_lookup_by_phandle(np, "st,syscfg-fmp");
	अगर (IS_ERR(i2c_dev->regmap))
		/* Optional */
		वापस 0;

	ret = of_property_पढ़ो_u32_index(np, "st,syscfg-fmp", 1,
					 &i2c_dev->fmp_sreg);
	अगर (ret)
		वापस ret;

	i2c_dev->fmp_creg = i2c_dev->fmp_sreg +
			       i2c_dev->setup.fmp_clr_offset;

	वापस of_property_पढ़ो_u32_index(np, "st,syscfg-fmp", 2,
					  &i2c_dev->fmp_mask);
पूर्ण

अटल पूर्णांक sपंचांग32f7_i2c_enable_smbus_host(काष्ठा sपंचांग32f7_i2c_dev *i2c_dev)
अणु
	काष्ठा i2c_adapter *adap = &i2c_dev->adap;
	व्योम __iomem *base = i2c_dev->base;
	काष्ठा i2c_client *client;

	client = i2c_new_slave_host_notअगरy_device(adap);
	अगर (IS_ERR(client))
		वापस PTR_ERR(client);

	i2c_dev->host_notअगरy_client = client;

	/* Enable SMBus Host address */
	sपंचांग32f7_i2c_set_bits(base + STM32F7_I2C_CR1, STM32F7_I2C_CR1_SMBHEN);

	वापस 0;
पूर्ण

अटल व्योम sपंचांग32f7_i2c_disable_smbus_host(काष्ठा sपंचांग32f7_i2c_dev *i2c_dev)
अणु
	व्योम __iomem *base = i2c_dev->base;

	अगर (i2c_dev->host_notअगरy_client) अणु
		/* Disable SMBus Host address */
		sपंचांग32f7_i2c_clr_bits(base + STM32F7_I2C_CR1,
				     STM32F7_I2C_CR1_SMBHEN);
		i2c_मुक्त_slave_host_notअगरy_device(i2c_dev->host_notअगरy_client);
	पूर्ण
पूर्ण

अटल u32 sपंचांग32f7_i2c_func(काष्ठा i2c_adapter *adap)
अणु
	काष्ठा sपंचांग32f7_i2c_dev *i2c_dev = i2c_get_adapdata(adap);

	u32 func = I2C_FUNC_I2C | I2C_FUNC_10BIT_ADDR | I2C_FUNC_SLAVE |
		   I2C_FUNC_SMBUS_QUICK | I2C_FUNC_SMBUS_BYTE |
		   I2C_FUNC_SMBUS_BYTE_DATA | I2C_FUNC_SMBUS_WORD_DATA |
		   I2C_FUNC_SMBUS_BLOCK_DATA | I2C_FUNC_SMBUS_BLOCK_PROC_CALL |
		   I2C_FUNC_SMBUS_PROC_CALL | I2C_FUNC_SMBUS_PEC |
		   I2C_FUNC_SMBUS_I2C_BLOCK;

	अगर (i2c_dev->smbus_mode)
		func |= I2C_FUNC_SMBUS_HOST_NOTIFY;

	वापस func;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm sपंचांग32f7_i2c_algo = अणु
	.master_xfer = sपंचांग32f7_i2c_xfer,
	.smbus_xfer = sपंचांग32f7_i2c_smbus_xfer,
	.functionality = sपंचांग32f7_i2c_func,
	.reg_slave = sपंचांग32f7_i2c_reg_slave,
	.unreg_slave = sपंचांग32f7_i2c_unreg_slave,
पूर्ण;

अटल पूर्णांक sपंचांग32f7_i2c_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sपंचांग32f7_i2c_dev *i2c_dev;
	स्थिर काष्ठा sपंचांग32f7_i2c_setup *setup;
	काष्ठा resource *res;
	काष्ठा i2c_adapter *adap;
	काष्ठा reset_control *rst;
	dma_addr_t phy_addr;
	पूर्णांक irq_error, irq_event, ret;

	i2c_dev = devm_kzalloc(&pdev->dev, माप(*i2c_dev), GFP_KERNEL);
	अगर (!i2c_dev)
		वापस -ENOMEM;

	i2c_dev->base = devm_platक्रमm_get_and_ioremap_resource(pdev, 0, &res);
	अगर (IS_ERR(i2c_dev->base))
		वापस PTR_ERR(i2c_dev->base);
	phy_addr = (dma_addr_t)res->start;

	irq_event = platक्रमm_get_irq(pdev, 0);
	अगर (irq_event <= 0)
		वापस irq_event ? : -ENOENT;

	irq_error = platक्रमm_get_irq(pdev, 1);
	अगर (irq_error <= 0)
		वापस irq_error ? : -ENOENT;

	i2c_dev->wakeup_src = of_property_पढ़ो_bool(pdev->dev.of_node,
						    "wakeup-source");

	i2c_dev->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(i2c_dev->clk))
		वापस dev_err_probe(&pdev->dev, PTR_ERR(i2c_dev->clk),
				     "Failed to get controller clock\n");

	ret = clk_prepare_enable(i2c_dev->clk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to prepare_enable clock\n");
		वापस ret;
	पूर्ण

	rst = devm_reset_control_get(&pdev->dev, शून्य);
	अगर (IS_ERR(rst)) अणु
		ret = dev_err_probe(&pdev->dev, PTR_ERR(rst),
				    "Error: Missing reset ctrl\n");
		जाओ clk_मुक्त;
	पूर्ण
	reset_control_निश्चित(rst);
	udelay(2);
	reset_control_deनिश्चित(rst);

	i2c_dev->dev = &pdev->dev;

	ret = devm_request_thपढ़ोed_irq(&pdev->dev, irq_event,
					sपंचांग32f7_i2c_isr_event,
					sपंचांग32f7_i2c_isr_event_thपढ़ो,
					IRQF_ONESHOT,
					pdev->name, i2c_dev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to request irq event %i\n",
			irq_event);
		जाओ clk_मुक्त;
	पूर्ण

	ret = devm_request_irq(&pdev->dev, irq_error, sपंचांग32f7_i2c_isr_error, 0,
			       pdev->name, i2c_dev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to request irq error %i\n",
			irq_error);
		जाओ clk_मुक्त;
	पूर्ण

	setup = of_device_get_match_data(&pdev->dev);
	अगर (!setup) अणु
		dev_err(&pdev->dev, "Can't get device data\n");
		ret = -ENODEV;
		जाओ clk_मुक्त;
	पूर्ण
	i2c_dev->setup = *setup;

	ret = sपंचांग32f7_i2c_setup_timing(i2c_dev, &i2c_dev->setup);
	अगर (ret)
		जाओ clk_मुक्त;

	/* Setup Fast mode plus अगर necessary */
	अगर (i2c_dev->bus_rate > I2C_MAX_FAST_MODE_FREQ) अणु
		ret = sपंचांग32f7_i2c_setup_fm_plus_bits(pdev, i2c_dev);
		अगर (ret)
			जाओ clk_मुक्त;
		ret = sपंचांग32f7_i2c_ग_लिखो_fm_plus_bits(i2c_dev, true);
		अगर (ret)
			जाओ clk_मुक्त;
	पूर्ण

	adap = &i2c_dev->adap;
	i2c_set_adapdata(adap, i2c_dev);
	snम_लिखो(adap->name, माप(adap->name), "STM32F7 I2C(%pa)",
		 &res->start);
	adap->owner = THIS_MODULE;
	adap->समयout = 2 * HZ;
	adap->retries = 3;
	adap->algo = &sपंचांग32f7_i2c_algo;
	adap->dev.parent = &pdev->dev;
	adap->dev.of_node = pdev->dev.of_node;

	init_completion(&i2c_dev->complete);

	/* Init DMA config अगर supported */
	i2c_dev->dma = sपंचांग32_i2c_dma_request(i2c_dev->dev, phy_addr,
					     STM32F7_I2C_TXDR,
					     STM32F7_I2C_RXDR);
	अगर (IS_ERR(i2c_dev->dma)) अणु
		ret = PTR_ERR(i2c_dev->dma);
		/* DMA support is optional, only report other errors */
		अगर (ret != -ENODEV)
			जाओ fmp_clear;
		dev_dbg(i2c_dev->dev, "No DMA option: fallback using interrupts\n");
		i2c_dev->dma = शून्य;
	पूर्ण

	अगर (i2c_dev->wakeup_src) अणु
		device_set_wakeup_capable(i2c_dev->dev, true);

		ret = dev_pm_set_wake_irq(i2c_dev->dev, irq_event);
		अगर (ret) अणु
			dev_err(i2c_dev->dev, "Failed to set wake up irq\n");
			जाओ clr_wakeup_capable;
		पूर्ण
	पूर्ण

	platक्रमm_set_drvdata(pdev, i2c_dev);

	pm_runसमय_set_स्वतःsuspend_delay(i2c_dev->dev,
					 STM32F7_AUTOSUSPEND_DELAY);
	pm_runसमय_use_स्वतःsuspend(i2c_dev->dev);
	pm_runसमय_set_active(i2c_dev->dev);
	pm_runसमय_enable(i2c_dev->dev);

	pm_runसमय_get_noresume(&pdev->dev);

	sपंचांग32f7_i2c_hw_config(i2c_dev);

	i2c_dev->smbus_mode = of_property_पढ़ो_bool(pdev->dev.of_node, "smbus");

	ret = i2c_add_adapter(adap);
	अगर (ret)
		जाओ pm_disable;

	अगर (i2c_dev->smbus_mode) अणु
		ret = sपंचांग32f7_i2c_enable_smbus_host(i2c_dev);
		अगर (ret) अणु
			dev_err(i2c_dev->dev,
				"failed to enable SMBus Host-Notify protocol (%d)\n",
				ret);
			जाओ i2c_adapter_हटाओ;
		पूर्ण
	पूर्ण

	dev_info(i2c_dev->dev, "STM32F7 I2C-%d bus adapter\n", adap->nr);

	pm_runसमय_mark_last_busy(i2c_dev->dev);
	pm_runसमय_put_स्वतःsuspend(i2c_dev->dev);

	वापस 0;

i2c_adapter_हटाओ:
	i2c_del_adapter(adap);

pm_disable:
	pm_runसमय_put_noidle(i2c_dev->dev);
	pm_runसमय_disable(i2c_dev->dev);
	pm_runसमय_set_suspended(i2c_dev->dev);
	pm_runसमय_करोnt_use_स्वतःsuspend(i2c_dev->dev);

	अगर (i2c_dev->wakeup_src)
		dev_pm_clear_wake_irq(i2c_dev->dev);

clr_wakeup_capable:
	अगर (i2c_dev->wakeup_src)
		device_set_wakeup_capable(i2c_dev->dev, false);

	अगर (i2c_dev->dma) अणु
		sपंचांग32_i2c_dma_मुक्त(i2c_dev->dma);
		i2c_dev->dma = शून्य;
	पूर्ण

fmp_clear:
	sपंचांग32f7_i2c_ग_लिखो_fm_plus_bits(i2c_dev, false);

clk_मुक्त:
	clk_disable_unprepare(i2c_dev->clk);

	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांग32f7_i2c_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sपंचांग32f7_i2c_dev *i2c_dev = platक्रमm_get_drvdata(pdev);

	sपंचांग32f7_i2c_disable_smbus_host(i2c_dev);

	i2c_del_adapter(&i2c_dev->adap);
	pm_runसमय_get_sync(i2c_dev->dev);

	अगर (i2c_dev->wakeup_src) अणु
		dev_pm_clear_wake_irq(i2c_dev->dev);
		/*
		 * enक्रमce that wakeup is disabled and that the device
		 * is marked as non wakeup capable
		 */
		device_init_wakeup(i2c_dev->dev, false);
	पूर्ण

	pm_runसमय_put_noidle(i2c_dev->dev);
	pm_runसमय_disable(i2c_dev->dev);
	pm_runसमय_set_suspended(i2c_dev->dev);
	pm_runसमय_करोnt_use_स्वतःsuspend(i2c_dev->dev);

	अगर (i2c_dev->dma) अणु
		sपंचांग32_i2c_dma_मुक्त(i2c_dev->dma);
		i2c_dev->dma = शून्य;
	पूर्ण

	sपंचांग32f7_i2c_ग_लिखो_fm_plus_bits(i2c_dev, false);

	clk_disable_unprepare(i2c_dev->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused sपंचांग32f7_i2c_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा sपंचांग32f7_i2c_dev *i2c_dev = dev_get_drvdata(dev);

	अगर (!sपंचांग32f7_i2c_is_slave_रेजिस्टरed(i2c_dev))
		clk_disable_unprepare(i2c_dev->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused sपंचांग32f7_i2c_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा sपंचांग32f7_i2c_dev *i2c_dev = dev_get_drvdata(dev);
	पूर्णांक ret;

	अगर (!sपंचांग32f7_i2c_is_slave_रेजिस्टरed(i2c_dev)) अणु
		ret = clk_prepare_enable(i2c_dev->clk);
		अगर (ret) अणु
			dev_err(dev, "failed to prepare_enable clock\n");
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused sपंचांग32f7_i2c_regs_backup(काष्ठा sपंचांग32f7_i2c_dev *i2c_dev)
अणु
	पूर्णांक ret;
	काष्ठा sपंचांग32f7_i2c_regs *backup_regs = &i2c_dev->backup_regs;

	ret = pm_runसमय_resume_and_get(i2c_dev->dev);
	अगर (ret < 0)
		वापस ret;

	backup_regs->cr1 = पढ़ोl_relaxed(i2c_dev->base + STM32F7_I2C_CR1);
	backup_regs->cr2 = पढ़ोl_relaxed(i2c_dev->base + STM32F7_I2C_CR2);
	backup_regs->oar1 = पढ़ोl_relaxed(i2c_dev->base + STM32F7_I2C_OAR1);
	backup_regs->oar2 = पढ़ोl_relaxed(i2c_dev->base + STM32F7_I2C_OAR2);
	backup_regs->पंचांगgr = पढ़ोl_relaxed(i2c_dev->base + STM32F7_I2C_TIMINGR);
	sपंचांग32f7_i2c_ग_लिखो_fm_plus_bits(i2c_dev, false);

	pm_runसमय_put_sync(i2c_dev->dev);

	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused sपंचांग32f7_i2c_regs_restore(काष्ठा sपंचांग32f7_i2c_dev *i2c_dev)
अणु
	u32 cr1;
	पूर्णांक ret;
	काष्ठा sपंचांग32f7_i2c_regs *backup_regs = &i2c_dev->backup_regs;

	ret = pm_runसमय_resume_and_get(i2c_dev->dev);
	अगर (ret < 0)
		वापस ret;

	cr1 = पढ़ोl_relaxed(i2c_dev->base + STM32F7_I2C_CR1);
	अगर (cr1 & STM32F7_I2C_CR1_PE)
		sपंचांग32f7_i2c_clr_bits(i2c_dev->base + STM32F7_I2C_CR1,
				     STM32F7_I2C_CR1_PE);

	ग_लिखोl_relaxed(backup_regs->पंचांगgr, i2c_dev->base + STM32F7_I2C_TIMINGR);
	ग_लिखोl_relaxed(backup_regs->cr1 & ~STM32F7_I2C_CR1_PE,
		       i2c_dev->base + STM32F7_I2C_CR1);
	अगर (backup_regs->cr1 & STM32F7_I2C_CR1_PE)
		sपंचांग32f7_i2c_set_bits(i2c_dev->base + STM32F7_I2C_CR1,
				     STM32F7_I2C_CR1_PE);
	ग_लिखोl_relaxed(backup_regs->cr2, i2c_dev->base + STM32F7_I2C_CR2);
	ग_लिखोl_relaxed(backup_regs->oar1, i2c_dev->base + STM32F7_I2C_OAR1);
	ग_लिखोl_relaxed(backup_regs->oar2, i2c_dev->base + STM32F7_I2C_OAR2);
	sपंचांग32f7_i2c_ग_लिखो_fm_plus_bits(i2c_dev, true);

	pm_runसमय_put_sync(i2c_dev->dev);

	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused sपंचांग32f7_i2c_suspend(काष्ठा device *dev)
अणु
	काष्ठा sपंचांग32f7_i2c_dev *i2c_dev = dev_get_drvdata(dev);
	पूर्णांक ret;

	i2c_mark_adapter_suspended(&i2c_dev->adap);

	अगर (!device_may_wakeup(dev) && !device_wakeup_path(dev)) अणु
		ret = sपंचांग32f7_i2c_regs_backup(i2c_dev);
		अगर (ret < 0) अणु
			i2c_mark_adapter_resumed(&i2c_dev->adap);
			वापस ret;
		पूर्ण

		pinctrl_pm_select_sleep_state(dev);
		pm_runसमय_क्रमce_suspend(dev);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused sपंचांग32f7_i2c_resume(काष्ठा device *dev)
अणु
	काष्ठा sपंचांग32f7_i2c_dev *i2c_dev = dev_get_drvdata(dev);
	पूर्णांक ret;

	अगर (!device_may_wakeup(dev) && !device_wakeup_path(dev)) अणु
		ret = pm_runसमय_क्रमce_resume(dev);
		अगर (ret < 0)
			वापस ret;
		pinctrl_pm_select_शेष_state(dev);

		ret = sपंचांग32f7_i2c_regs_restore(i2c_dev);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	i2c_mark_adapter_resumed(&i2c_dev->adap);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops sपंचांग32f7_i2c_pm_ops = अणु
	SET_RUNTIME_PM_OPS(sपंचांग32f7_i2c_runसमय_suspend,
			   sपंचांग32f7_i2c_runसमय_resume, शून्य)
	SET_SYSTEM_SLEEP_PM_OPS(sपंचांग32f7_i2c_suspend, sपंचांग32f7_i2c_resume)
पूर्ण;

अटल स्थिर काष्ठा of_device_id sपंचांग32f7_i2c_match[] = अणु
	अणु .compatible = "st,stm32f7-i2c", .data = &sपंचांग32f7_setupपूर्ण,
	अणु .compatible = "st,stm32mp15-i2c", .data = &sपंचांग32mp15_setupपूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sपंचांग32f7_i2c_match);

अटल काष्ठा platक्रमm_driver sपंचांग32f7_i2c_driver = अणु
	.driver = अणु
		.name = "stm32f7-i2c",
		.of_match_table = sपंचांग32f7_i2c_match,
		.pm = &sपंचांग32f7_i2c_pm_ops,
	पूर्ण,
	.probe = sपंचांग32f7_i2c_probe,
	.हटाओ = sपंचांग32f7_i2c_हटाओ,
पूर्ण;

module_platक्रमm_driver(sपंचांग32f7_i2c_driver);

MODULE_AUTHOR("M'boumba Cedric Madianga <cedric.madianga@gmail.com>");
MODULE_DESCRIPTION("STMicroelectronics STM32F7 I2C driver");
MODULE_LICENSE("GPL v2");
