<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम STMicroelectronics STM32 I2C controller
 *
 * This I2C controller is described in the STM32F429/439 Soc reference manual.
 * Please see below a link to the करोcumentation:
 * http://www.st.com/resource/en/reference_manual/DM00031020.pdf
 *
 * Copyright (C) M'boumba Cedric Madianga 2016
 * Copyright (C) STMicroelectronics 2017
 * Author: M'boumba Cedric Madianga <cedric.madianga@gmail.com>
 *
 * This driver is based on i2c-st.c
 *
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reset.h>

#समावेश "i2c-stm32.h"

/* STM32F4 I2C offset रेजिस्टरs */
#घोषणा STM32F4_I2C_CR1			0x00
#घोषणा STM32F4_I2C_CR2			0x04
#घोषणा STM32F4_I2C_DR			0x10
#घोषणा STM32F4_I2C_SR1			0x14
#घोषणा STM32F4_I2C_SR2			0x18
#घोषणा STM32F4_I2C_CCR			0x1C
#घोषणा STM32F4_I2C_TRISE		0x20
#घोषणा STM32F4_I2C_FLTR		0x24

/* STM32F4 I2C control 1*/
#घोषणा STM32F4_I2C_CR1_POS		BIT(11)
#घोषणा STM32F4_I2C_CR1_ACK		BIT(10)
#घोषणा STM32F4_I2C_CR1_STOP		BIT(9)
#घोषणा STM32F4_I2C_CR1_START		BIT(8)
#घोषणा STM32F4_I2C_CR1_PE		BIT(0)

/* STM32F4 I2C control 2 */
#घोषणा STM32F4_I2C_CR2_FREQ_MASK	GENMASK(5, 0)
#घोषणा STM32F4_I2C_CR2_FREQ(n)		((n) & STM32F4_I2C_CR2_FREQ_MASK)
#घोषणा STM32F4_I2C_CR2_ITBUFEN		BIT(10)
#घोषणा STM32F4_I2C_CR2_ITEVTEN		BIT(9)
#घोषणा STM32F4_I2C_CR2_ITERREN		BIT(8)
#घोषणा STM32F4_I2C_CR2_IRQ_MASK	(STM32F4_I2C_CR2_ITBUFEN | \
					 STM32F4_I2C_CR2_ITEVTEN | \
					 STM32F4_I2C_CR2_ITERREN)

/* STM32F4 I2C Status 1 */
#घोषणा STM32F4_I2C_SR1_AF		BIT(10)
#घोषणा STM32F4_I2C_SR1_ARLO		BIT(9)
#घोषणा STM32F4_I2C_SR1_BERR		BIT(8)
#घोषणा STM32F4_I2C_SR1_TXE		BIT(7)
#घोषणा STM32F4_I2C_SR1_RXNE		BIT(6)
#घोषणा STM32F4_I2C_SR1_BTF		BIT(2)
#घोषणा STM32F4_I2C_SR1_ADDR		BIT(1)
#घोषणा STM32F4_I2C_SR1_SB		BIT(0)
#घोषणा STM32F4_I2C_SR1_ITEVTEN_MASK	(STM32F4_I2C_SR1_BTF | \
					 STM32F4_I2C_SR1_ADDR | \
					 STM32F4_I2C_SR1_SB)
#घोषणा STM32F4_I2C_SR1_ITBUFEN_MASK	(STM32F4_I2C_SR1_TXE | \
					 STM32F4_I2C_SR1_RXNE)
#घोषणा STM32F4_I2C_SR1_ITERREN_MASK	(STM32F4_I2C_SR1_AF | \
					 STM32F4_I2C_SR1_ARLO | \
					 STM32F4_I2C_SR1_BERR)

/* STM32F4 I2C Status 2 */
#घोषणा STM32F4_I2C_SR2_BUSY		BIT(1)

/* STM32F4 I2C Control Clock */
#घोषणा STM32F4_I2C_CCR_CCR_MASK	GENMASK(11, 0)
#घोषणा STM32F4_I2C_CCR_CCR(n)		((n) & STM32F4_I2C_CCR_CCR_MASK)
#घोषणा STM32F4_I2C_CCR_FS		BIT(15)
#घोषणा STM32F4_I2C_CCR_DUTY		BIT(14)

/* STM32F4 I2C Trise */
#घोषणा STM32F4_I2C_TRISE_VALUE_MASK	GENMASK(5, 0)
#घोषणा STM32F4_I2C_TRISE_VALUE(n)	((n) & STM32F4_I2C_TRISE_VALUE_MASK)

#घोषणा STM32F4_I2C_MIN_STANDARD_FREQ	2U
#घोषणा STM32F4_I2C_MIN_FAST_FREQ	6U
#घोषणा STM32F4_I2C_MAX_FREQ		46U
#घोषणा HZ_TO_MHZ			1000000

/**
 * काष्ठा sपंचांग32f4_i2c_msg - client specअगरic data
 * @addr: 8-bit slave addr, including r/w bit
 * @count: number of bytes to be transferred
 * @buf: data buffer
 * @result: result of the transfer
 * @stop: last I2C msg to be sent, i.e. STOP to be generated
 */
काष्ठा sपंचांग32f4_i2c_msg अणु
	u8 addr;
	u32 count;
	u8 *buf;
	पूर्णांक result;
	bool stop;
पूर्ण;

/**
 * काष्ठा sपंचांग32f4_i2c_dev - निजी data of the controller
 * @adap: I2C adapter क्रम this controller
 * @dev: device क्रम this controller
 * @base: भव memory area
 * @complete: completion of I2C message
 * @clk: hw i2c घड़ी
 * @speed: I2C घड़ी frequency of the controller. Standard or Fast are supported
 * @parent_rate: I2C घड़ी parent rate in MHz
 * @msg: I2C transfer inक्रमmation
 */
काष्ठा sपंचांग32f4_i2c_dev अणु
	काष्ठा i2c_adapter adap;
	काष्ठा device *dev;
	व्योम __iomem *base;
	काष्ठा completion complete;
	काष्ठा clk *clk;
	पूर्णांक speed;
	पूर्णांक parent_rate;
	काष्ठा sपंचांग32f4_i2c_msg msg;
पूर्ण;

अटल अंतरभूत व्योम sपंचांग32f4_i2c_set_bits(व्योम __iomem *reg, u32 mask)
अणु
	ग_लिखोl_relaxed(पढ़ोl_relaxed(reg) | mask, reg);
पूर्ण

अटल अंतरभूत व्योम sपंचांग32f4_i2c_clr_bits(व्योम __iomem *reg, u32 mask)
अणु
	ग_लिखोl_relaxed(पढ़ोl_relaxed(reg) & ~mask, reg);
पूर्ण

अटल व्योम sपंचांग32f4_i2c_disable_irq(काष्ठा sपंचांग32f4_i2c_dev *i2c_dev)
अणु
	व्योम __iomem *reg = i2c_dev->base + STM32F4_I2C_CR2;

	sपंचांग32f4_i2c_clr_bits(reg, STM32F4_I2C_CR2_IRQ_MASK);
पूर्ण

अटल पूर्णांक sपंचांग32f4_i2c_set_periph_clk_freq(काष्ठा sपंचांग32f4_i2c_dev *i2c_dev)
अणु
	u32 freq;
	u32 cr2 = 0;

	i2c_dev->parent_rate = clk_get_rate(i2c_dev->clk);
	freq = DIV_ROUND_UP(i2c_dev->parent_rate, HZ_TO_MHZ);

	अगर (i2c_dev->speed == STM32_I2C_SPEED_STANDARD) अणु
		/*
		 * To reach 100 kHz, the parent clk frequency should be between
		 * a minimum value of 2 MHz and a maximum value of 46 MHz due
		 * to hardware limitation
		 */
		अगर (freq < STM32F4_I2C_MIN_STANDARD_FREQ ||
		    freq > STM32F4_I2C_MAX_FREQ) अणु
			dev_err(i2c_dev->dev,
				"bad parent clk freq for standard mode\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * To be as बंद as possible to 400 kHz, the parent clk
		 * frequency should be between a minimum value of 6 MHz and a
		 * maximum value of 46 MHz due to hardware limitation
		 */
		अगर (freq < STM32F4_I2C_MIN_FAST_FREQ ||
		    freq > STM32F4_I2C_MAX_FREQ) अणु
			dev_err(i2c_dev->dev,
				"bad parent clk freq for fast mode\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	cr2 |= STM32F4_I2C_CR2_FREQ(freq);
	ग_लिखोl_relaxed(cr2, i2c_dev->base + STM32F4_I2C_CR2);

	वापस 0;
पूर्ण

अटल व्योम sपंचांग32f4_i2c_set_rise_समय(काष्ठा sपंचांग32f4_i2c_dev *i2c_dev)
अणु
	u32 freq = DIV_ROUND_UP(i2c_dev->parent_rate, HZ_TO_MHZ);
	u32 trise;

	/*
	 * These bits must be programmed with the maximum SCL rise समय given in
	 * the I2C bus specअगरication, incremented by 1.
	 *
	 * In standard mode, the maximum allowed SCL rise समय is 1000 ns.
	 * If, in the I2C_CR2 रेजिस्टर, the value of FREQ[5:0] bits is equal to
	 * 0x08 so period = 125 ns thereक्रमe the TRISE[5:0] bits must be
	 * programmed with 0x9. (1000 ns / 125 ns + 1)
	 * So, क्रम I2C standard mode TRISE = FREQ[5:0] + 1
	 *
	 * In fast mode, the maximum allowed SCL rise समय is 300 ns.
	 * If, in the I2C_CR2 रेजिस्टर, the value of FREQ[5:0] bits is equal to
	 * 0x08 so period = 125 ns thereक्रमe the TRISE[5:0] bits must be
	 * programmed with 0x3. (300 ns / 125 ns + 1)
	 * So, क्रम I2C fast mode TRISE = FREQ[5:0] * 300 / 1000 + 1
	 *
	 * Function sपंचांग32f4_i2c_set_periph_clk_freq made sure that parent rate
	 * is not higher than 46 MHz . As a result trise is at most 4 bits wide
	 * and so fits पूर्णांकo the TRISE bits [5:0].
	 */
	अगर (i2c_dev->speed == STM32_I2C_SPEED_STANDARD)
		trise = freq + 1;
	अन्यथा
		trise = freq * 3 / 10 + 1;

	ग_लिखोl_relaxed(STM32F4_I2C_TRISE_VALUE(trise),
		       i2c_dev->base + STM32F4_I2C_TRISE);
पूर्ण

अटल व्योम sपंचांग32f4_i2c_set_speed_mode(काष्ठा sपंचांग32f4_i2c_dev *i2c_dev)
अणु
	u32 val;
	u32 ccr = 0;

	अगर (i2c_dev->speed == STM32_I2C_SPEED_STANDARD) अणु
		/*
		 * In standard mode:
		 * t_scl_high = t_scl_low = CCR * I2C parent clk period
		 * So to reach 100 kHz, we have:
		 * CCR = I2C parent rate / (100 kHz * 2)
		 *
		 * For example with parent rate = 2 MHz:
		 * CCR = 2000000 / (100000 * 2) = 10
		 * t_scl_high = t_scl_low = 10 * (1 / 2000000) = 5000 ns
		 * t_scl_high + t_scl_low = 10000 ns so 100 kHz is reached
		 *
		 * Function sपंचांग32f4_i2c_set_periph_clk_freq made sure that
		 * parent rate is not higher than 46 MHz . As a result val
		 * is at most 8 bits wide and so fits पूर्णांकo the CCR bits [11:0].
		 */
		val = i2c_dev->parent_rate / (I2C_MAX_STANDARD_MODE_FREQ * 2);
	पूर्ण अन्यथा अणु
		/*
		 * In fast mode, we compute CCR with duty = 0 as with low
		 * frequencies we are not able to reach 400 kHz.
		 * In that हाल:
		 * t_scl_high = CCR * I2C parent clk period
		 * t_scl_low = 2 * CCR * I2C parent clk period
		 * So, CCR = I2C parent rate / (400 kHz * 3)
		 *
		 * For example with parent rate = 6 MHz:
		 * CCR = 6000000 / (400000 * 3) = 5
		 * t_scl_high = 5 * (1 / 6000000) = 833 ns > 600 ns
		 * t_scl_low = 2 * 5 * (1 / 6000000) = 1667 ns > 1300 ns
		 * t_scl_high + t_scl_low = 2500 ns so 400 kHz is reached
		 *
		 * Function sपंचांग32f4_i2c_set_periph_clk_freq made sure that
		 * parent rate is not higher than 46 MHz . As a result val
		 * is at most 6 bits wide and so fits पूर्णांकo the CCR bits [11:0].
		 */
		val = DIV_ROUND_UP(i2c_dev->parent_rate, I2C_MAX_FAST_MODE_FREQ * 3);

		/* Select Fast mode */
		ccr |= STM32F4_I2C_CCR_FS;
	पूर्ण

	ccr |= STM32F4_I2C_CCR_CCR(val);
	ग_लिखोl_relaxed(ccr, i2c_dev->base + STM32F4_I2C_CCR);
पूर्ण

/**
 * sपंचांग32f4_i2c_hw_config() - Prepare I2C block
 * @i2c_dev: Controller's निजी data
 */
अटल पूर्णांक sपंचांग32f4_i2c_hw_config(काष्ठा sपंचांग32f4_i2c_dev *i2c_dev)
अणु
	पूर्णांक ret;

	ret = sपंचांग32f4_i2c_set_periph_clk_freq(i2c_dev);
	अगर (ret)
		वापस ret;

	sपंचांग32f4_i2c_set_rise_समय(i2c_dev);

	sपंचांग32f4_i2c_set_speed_mode(i2c_dev);

	/* Enable I2C */
	ग_लिखोl_relaxed(STM32F4_I2C_CR1_PE, i2c_dev->base + STM32F4_I2C_CR1);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32f4_i2c_रुको_मुक्त_bus(काष्ठा sपंचांग32f4_i2c_dev *i2c_dev)
अणु
	u32 status;
	पूर्णांक ret;

	ret = पढ़ोl_relaxed_poll_समयout(i2c_dev->base + STM32F4_I2C_SR2,
					 status,
					 !(status & STM32F4_I2C_SR2_BUSY),
					 10, 1000);
	अगर (ret) अणु
		dev_dbg(i2c_dev->dev, "bus not free\n");
		ret = -EBUSY;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * sपंचांग32f4_i2c_ग_लिखो_byte() - Write a byte in the data रेजिस्टर
 * @i2c_dev: Controller's निजी data
 * @byte: Data to ग_लिखो in the रेजिस्टर
 */
अटल व्योम sपंचांग32f4_i2c_ग_लिखो_byte(काष्ठा sपंचांग32f4_i2c_dev *i2c_dev, u8 byte)
अणु
	ग_लिखोl_relaxed(byte, i2c_dev->base + STM32F4_I2C_DR);
पूर्ण

/**
 * sपंचांग32f4_i2c_ग_लिखो_msg() - Fill the data रेजिस्टर in ग_लिखो mode
 * @i2c_dev: Controller's निजी data
 *
 * This function fills the data रेजिस्टर with I2C transfer buffer
 */
अटल व्योम sपंचांग32f4_i2c_ग_लिखो_msg(काष्ठा sपंचांग32f4_i2c_dev *i2c_dev)
अणु
	काष्ठा sपंचांग32f4_i2c_msg *msg = &i2c_dev->msg;

	sपंचांग32f4_i2c_ग_लिखो_byte(i2c_dev, *msg->buf++);
	msg->count--;
पूर्ण

अटल व्योम sपंचांग32f4_i2c_पढ़ो_msg(काष्ठा sपंचांग32f4_i2c_dev *i2c_dev)
अणु
	काष्ठा sपंचांग32f4_i2c_msg *msg = &i2c_dev->msg;
	u32 rbuf;

	rbuf = पढ़ोl_relaxed(i2c_dev->base + STM32F4_I2C_DR);
	*msg->buf++ = rbuf;
	msg->count--;
पूर्ण

अटल व्योम sपंचांग32f4_i2c_terminate_xfer(काष्ठा sपंचांग32f4_i2c_dev *i2c_dev)
अणु
	काष्ठा sपंचांग32f4_i2c_msg *msg = &i2c_dev->msg;
	व्योम __iomem *reg;

	sपंचांग32f4_i2c_disable_irq(i2c_dev);

	reg = i2c_dev->base + STM32F4_I2C_CR1;
	अगर (msg->stop)
		sपंचांग32f4_i2c_set_bits(reg, STM32F4_I2C_CR1_STOP);
	अन्यथा
		sपंचांग32f4_i2c_set_bits(reg, STM32F4_I2C_CR1_START);

	complete(&i2c_dev->complete);
पूर्ण

/**
 * sपंचांग32f4_i2c_handle_ग_लिखो() - Handle FIFO empty पूर्णांकerrupt in हाल of ग_लिखो
 * @i2c_dev: Controller's निजी data
 */
अटल व्योम sपंचांग32f4_i2c_handle_ग_लिखो(काष्ठा sपंचांग32f4_i2c_dev *i2c_dev)
अणु
	काष्ठा sपंचांग32f4_i2c_msg *msg = &i2c_dev->msg;
	व्योम __iomem *reg = i2c_dev->base + STM32F4_I2C_CR2;

	अगर (msg->count) अणु
		sपंचांग32f4_i2c_ग_लिखो_msg(i2c_dev);
		अगर (!msg->count) अणु
			/*
			 * Disable buffer पूर्णांकerrupts क्रम RX not empty and TX
			 * empty events
			 */
			sपंचांग32f4_i2c_clr_bits(reg, STM32F4_I2C_CR2_ITBUFEN);
		पूर्ण
	पूर्ण अन्यथा अणु
		sपंचांग32f4_i2c_terminate_xfer(i2c_dev);
	पूर्ण
पूर्ण

/**
 * sपंचांग32f4_i2c_handle_पढ़ो() - Handle FIFO empty पूर्णांकerrupt in हाल of पढ़ो
 * @i2c_dev: Controller's निजी data
 *
 * This function is called when a new data is received in data रेजिस्टर
 */
अटल व्योम sपंचांग32f4_i2c_handle_पढ़ो(काष्ठा sपंचांग32f4_i2c_dev *i2c_dev)
अणु
	काष्ठा sपंचांग32f4_i2c_msg *msg = &i2c_dev->msg;
	व्योम __iomem *reg = i2c_dev->base + STM32F4_I2C_CR2;

	चयन (msg->count) अणु
	हाल 1:
		sपंचांग32f4_i2c_disable_irq(i2c_dev);
		sपंचांग32f4_i2c_पढ़ो_msg(i2c_dev);
		complete(&i2c_dev->complete);
		अवरोध;
	/*
	 * For 2-byte reception, 3-byte reception and क्रम Data N-2, N-1 and N
	 * क्रम N-byte reception with N > 3, we करो not have to पढ़ो the data
	 * रेजिस्टर when RX not empty event occurs as we have to रुको क्रम byte
	 * transferred finished event beक्रमe पढ़ोing data.
	 * So, here we just disable buffer पूर्णांकerrupt in order to aव्योम another
	 * प्रणाली preemption due to RX not empty event.
	 */
	हाल 2:
	हाल 3:
		sपंचांग32f4_i2c_clr_bits(reg, STM32F4_I2C_CR2_ITBUFEN);
		अवरोध;
	/*
	 * For N byte reception with N > 3 we directly पढ़ो data रेजिस्टर
	 * until N-2 data.
	 */
	शेष:
		sपंचांग32f4_i2c_पढ़ो_msg(i2c_dev);
	पूर्ण
पूर्ण

/**
 * sपंचांग32f4_i2c_handle_rx_करोne() - Handle byte transfer finished पूर्णांकerrupt
 * in हाल of पढ़ो
 * @i2c_dev: Controller's निजी data
 *
 * This function is called when a new data is received in the shअगरt रेजिस्टर
 * but data रेजिस्टर has not been पढ़ो yet.
 */
अटल व्योम sपंचांग32f4_i2c_handle_rx_करोne(काष्ठा sपंचांग32f4_i2c_dev *i2c_dev)
अणु
	काष्ठा sपंचांग32f4_i2c_msg *msg = &i2c_dev->msg;
	व्योम __iomem *reg;
	u32 mask;
	पूर्णांक i;

	चयन (msg->count) अणु
	हाल 2:
		/*
		 * In order to correctly send the Stop or Repeated Start
		 * condition on the I2C bus, the STOP/START bit has to be set
		 * beक्रमe पढ़ोing the last two bytes (data N-1 and N).
		 * After that, we could पढ़ो the last two bytes, disable
		 * reमुख्यing पूर्णांकerrupts and notअगरy the end of xfer to the
		 * client
		 */
		reg = i2c_dev->base + STM32F4_I2C_CR1;
		अगर (msg->stop)
			sपंचांग32f4_i2c_set_bits(reg, STM32F4_I2C_CR1_STOP);
		अन्यथा
			sपंचांग32f4_i2c_set_bits(reg, STM32F4_I2C_CR1_START);

		क्रम (i = 2; i > 0; i--)
			sपंचांग32f4_i2c_पढ़ो_msg(i2c_dev);

		reg = i2c_dev->base + STM32F4_I2C_CR2;
		mask = STM32F4_I2C_CR2_ITEVTEN | STM32F4_I2C_CR2_ITERREN;
		sपंचांग32f4_i2c_clr_bits(reg, mask);

		complete(&i2c_dev->complete);
		अवरोध;
	हाल 3:
		/*
		 * In order to correctly generate the NACK pulse after the last
		 * received data byte, we have to enable NACK beक्रमe पढ़ोing N-2
		 * data
		 */
		reg = i2c_dev->base + STM32F4_I2C_CR1;
		sपंचांग32f4_i2c_clr_bits(reg, STM32F4_I2C_CR1_ACK);
		sपंचांग32f4_i2c_पढ़ो_msg(i2c_dev);
		अवरोध;
	शेष:
		sपंचांग32f4_i2c_पढ़ो_msg(i2c_dev);
	पूर्ण
पूर्ण

/**
 * sपंचांग32f4_i2c_handle_rx_addr() - Handle address matched पूर्णांकerrupt in हाल of
 * master receiver
 * @i2c_dev: Controller's निजी data
 */
अटल व्योम sपंचांग32f4_i2c_handle_rx_addr(काष्ठा sपंचांग32f4_i2c_dev *i2c_dev)
अणु
	काष्ठा sपंचांग32f4_i2c_msg *msg = &i2c_dev->msg;
	u32 cr1;

	चयन (msg->count) अणु
	हाल 0:
		sपंचांग32f4_i2c_terminate_xfer(i2c_dev);

		/* Clear ADDR flag */
		पढ़ोl_relaxed(i2c_dev->base + STM32F4_I2C_SR2);
		अवरोध;
	हाल 1:
		/*
		 * Single byte reception:
		 * Enable NACK and reset POS (Acknowledge position).
		 * Then, clear ADDR flag and set STOP or RepSTART.
		 * In that way, the NACK and STOP or RepStart pulses will be
		 * sent as soon as the byte will be received in shअगरt रेजिस्टर
		 */
		cr1 = पढ़ोl_relaxed(i2c_dev->base + STM32F4_I2C_CR1);
		cr1 &= ~(STM32F4_I2C_CR1_ACK | STM32F4_I2C_CR1_POS);
		ग_लिखोl_relaxed(cr1, i2c_dev->base + STM32F4_I2C_CR1);

		पढ़ोl_relaxed(i2c_dev->base + STM32F4_I2C_SR2);

		अगर (msg->stop)
			cr1 |= STM32F4_I2C_CR1_STOP;
		अन्यथा
			cr1 |= STM32F4_I2C_CR1_START;
		ग_लिखोl_relaxed(cr1, i2c_dev->base + STM32F4_I2C_CR1);
		अवरोध;
	हाल 2:
		/*
		 * 2-byte reception:
		 * Enable NACK, set POS (NACK position) and clear ADDR flag.
		 * In that way, NACK will be sent क्रम the next byte which will
		 * be received in the shअगरt रेजिस्टर instead of the current
		 * one.
		 */
		cr1 = पढ़ोl_relaxed(i2c_dev->base + STM32F4_I2C_CR1);
		cr1 &= ~STM32F4_I2C_CR1_ACK;
		cr1 |= STM32F4_I2C_CR1_POS;
		ग_लिखोl_relaxed(cr1, i2c_dev->base + STM32F4_I2C_CR1);

		पढ़ोl_relaxed(i2c_dev->base + STM32F4_I2C_SR2);
		अवरोध;

	शेष:
		/*
		 * N-byte reception:
		 * Enable ACK, reset POS (ACK position) and clear ADDR flag.
		 * In that way, ACK will be sent as soon as the current byte
		 * will be received in the shअगरt रेजिस्टर
		 */
		cr1 = पढ़ोl_relaxed(i2c_dev->base + STM32F4_I2C_CR1);
		cr1 |= STM32F4_I2C_CR1_ACK;
		cr1 &= ~STM32F4_I2C_CR1_POS;
		ग_लिखोl_relaxed(cr1, i2c_dev->base + STM32F4_I2C_CR1);

		पढ़ोl_relaxed(i2c_dev->base + STM32F4_I2C_SR2);
		अवरोध;
	पूर्ण
पूर्ण

/**
 * sपंचांग32f4_i2c_isr_event() - Interrupt routine क्रम I2C bus event
 * @irq: पूर्णांकerrupt number
 * @data: Controller's निजी data
 */
अटल irqवापस_t sपंचांग32f4_i2c_isr_event(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा sपंचांग32f4_i2c_dev *i2c_dev = data;
	काष्ठा sपंचांग32f4_i2c_msg *msg = &i2c_dev->msg;
	u32 possible_status = STM32F4_I2C_SR1_ITEVTEN_MASK;
	u32 status, ien, event, cr2;

	cr2 = पढ़ोl_relaxed(i2c_dev->base + STM32F4_I2C_CR2);
	ien = cr2 & STM32F4_I2C_CR2_IRQ_MASK;

	/* Update possible_status अगर buffer पूर्णांकerrupt is enabled */
	अगर (ien & STM32F4_I2C_CR2_ITBUFEN)
		possible_status |= STM32F4_I2C_SR1_ITBUFEN_MASK;

	status = पढ़ोl_relaxed(i2c_dev->base + STM32F4_I2C_SR1);
	event = status & possible_status;
	अगर (!event) अणु
		dev_dbg(i2c_dev->dev,
			"spurious evt irq (status=0x%08x, ien=0x%08x)\n",
			status, ien);
		वापस IRQ_NONE;
	पूर्ण

	/* Start condition generated */
	अगर (event & STM32F4_I2C_SR1_SB)
		sपंचांग32f4_i2c_ग_लिखो_byte(i2c_dev, msg->addr);

	/* I2C Address sent */
	अगर (event & STM32F4_I2C_SR1_ADDR) अणु
		अगर (msg->addr & I2C_M_RD)
			sपंचांग32f4_i2c_handle_rx_addr(i2c_dev);
		अन्यथा
			पढ़ोl_relaxed(i2c_dev->base + STM32F4_I2C_SR2);

		/*
		 * Enable buffer पूर्णांकerrupts क्रम RX not empty and TX empty
		 * events
		 */
		cr2 |= STM32F4_I2C_CR2_ITBUFEN;
		ग_लिखोl_relaxed(cr2, i2c_dev->base + STM32F4_I2C_CR2);
	पूर्ण

	/* TX empty */
	अगर ((event & STM32F4_I2C_SR1_TXE) && !(msg->addr & I2C_M_RD))
		sपंचांग32f4_i2c_handle_ग_लिखो(i2c_dev);

	/* RX not empty */
	अगर ((event & STM32F4_I2C_SR1_RXNE) && (msg->addr & I2C_M_RD))
		sपंचांग32f4_i2c_handle_पढ़ो(i2c_dev);

	/*
	 * The BTF (Byte Transfer finished) event occurs when:
	 * - in reception : a new byte is received in the shअगरt रेजिस्टर
	 * but the previous byte has not been पढ़ो yet from data रेजिस्टर
	 * - in transmission: a new byte should be sent but the data रेजिस्टर
	 * has not been written yet
	 */
	अगर (event & STM32F4_I2C_SR1_BTF) अणु
		अगर (msg->addr & I2C_M_RD)
			sपंचांग32f4_i2c_handle_rx_करोne(i2c_dev);
		अन्यथा
			sपंचांग32f4_i2c_handle_ग_लिखो(i2c_dev);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/**
 * sपंचांग32f4_i2c_isr_error() - Interrupt routine क्रम I2C bus error
 * @irq: पूर्णांकerrupt number
 * @data: Controller's निजी data
 */
अटल irqवापस_t sपंचांग32f4_i2c_isr_error(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा sपंचांग32f4_i2c_dev *i2c_dev = data;
	काष्ठा sपंचांग32f4_i2c_msg *msg = &i2c_dev->msg;
	व्योम __iomem *reg;
	u32 status;

	status = पढ़ोl_relaxed(i2c_dev->base + STM32F4_I2C_SR1);

	/* Arbitration lost */
	अगर (status & STM32F4_I2C_SR1_ARLO) अणु
		status &= ~STM32F4_I2C_SR1_ARLO;
		ग_लिखोl_relaxed(status, i2c_dev->base + STM32F4_I2C_SR1);
		msg->result = -EAGAIN;
	पूर्ण

	/*
	 * Acknowledge failure:
	 * In master transmitter mode a Stop must be generated by software
	 */
	अगर (status & STM32F4_I2C_SR1_AF) अणु
		अगर (!(msg->addr & I2C_M_RD)) अणु
			reg = i2c_dev->base + STM32F4_I2C_CR1;
			sपंचांग32f4_i2c_set_bits(reg, STM32F4_I2C_CR1_STOP);
		पूर्ण
		status &= ~STM32F4_I2C_SR1_AF;
		ग_लिखोl_relaxed(status, i2c_dev->base + STM32F4_I2C_SR1);
		msg->result = -EIO;
	पूर्ण

	/* Bus error */
	अगर (status & STM32F4_I2C_SR1_BERR) अणु
		status &= ~STM32F4_I2C_SR1_BERR;
		ग_लिखोl_relaxed(status, i2c_dev->base + STM32F4_I2C_SR1);
		msg->result = -EIO;
	पूर्ण

	sपंचांग32f4_i2c_disable_irq(i2c_dev);
	complete(&i2c_dev->complete);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * sपंचांग32f4_i2c_xfer_msg() - Transfer a single I2C message
 * @i2c_dev: Controller's निजी data
 * @msg: I2C message to transfer
 * @is_first: first message of the sequence
 * @is_last: last message of the sequence
 */
अटल पूर्णांक sपंचांग32f4_i2c_xfer_msg(काष्ठा sपंचांग32f4_i2c_dev *i2c_dev,
				काष्ठा i2c_msg *msg, bool is_first,
				bool is_last)
अणु
	काष्ठा sपंचांग32f4_i2c_msg *f4_msg = &i2c_dev->msg;
	व्योम __iomem *reg = i2c_dev->base + STM32F4_I2C_CR1;
	अचिन्हित दीर्घ समयout;
	u32 mask;
	पूर्णांक ret;

	f4_msg->addr = i2c_8bit_addr_from_msg(msg);
	f4_msg->buf = msg->buf;
	f4_msg->count = msg->len;
	f4_msg->result = 0;
	f4_msg->stop = is_last;

	reinit_completion(&i2c_dev->complete);

	/* Enable events and errors पूर्णांकerrupts */
	mask = STM32F4_I2C_CR2_ITEVTEN | STM32F4_I2C_CR2_ITERREN;
	sपंचांग32f4_i2c_set_bits(i2c_dev->base + STM32F4_I2C_CR2, mask);

	अगर (is_first) अणु
		ret = sपंचांग32f4_i2c_रुको_मुक्त_bus(i2c_dev);
		अगर (ret)
			वापस ret;

		/* START generation */
		sपंचांग32f4_i2c_set_bits(reg, STM32F4_I2C_CR1_START);
	पूर्ण

	समयout = रुको_क्रम_completion_समयout(&i2c_dev->complete,
					      i2c_dev->adap.समयout);
	ret = f4_msg->result;

	अगर (!समयout)
		ret = -ETIMEDOUT;

	वापस ret;
पूर्ण

/**
 * sपंचांग32f4_i2c_xfer() - Transfer combined I2C message
 * @i2c_adap: Adapter poपूर्णांकer to the controller
 * @msgs: Poपूर्णांकer to data to be written.
 * @num: Number of messages to be executed
 */
अटल पूर्णांक sपंचांग32f4_i2c_xfer(काष्ठा i2c_adapter *i2c_adap, काष्ठा i2c_msg msgs[],
			    पूर्णांक num)
अणु
	काष्ठा sपंचांग32f4_i2c_dev *i2c_dev = i2c_get_adapdata(i2c_adap);
	पूर्णांक ret, i;

	ret = clk_enable(i2c_dev->clk);
	अगर (ret) अणु
		dev_err(i2c_dev->dev, "Failed to enable clock\n");
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < num && !ret; i++)
		ret = sपंचांग32f4_i2c_xfer_msg(i2c_dev, &msgs[i], i == 0,
					   i == num - 1);

	clk_disable(i2c_dev->clk);

	वापस (ret < 0) ? ret : num;
पूर्ण

अटल u32 sपंचांग32f4_i2c_func(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm sपंचांग32f4_i2c_algo = अणु
	.master_xfer = sपंचांग32f4_i2c_xfer,
	.functionality = sपंचांग32f4_i2c_func,
पूर्ण;

अटल पूर्णांक sपंचांग32f4_i2c_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा sपंचांग32f4_i2c_dev *i2c_dev;
	काष्ठा resource *res;
	u32 irq_event, irq_error, clk_rate;
	काष्ठा i2c_adapter *adap;
	काष्ठा reset_control *rst;
	पूर्णांक ret;

	i2c_dev = devm_kzalloc(&pdev->dev, माप(*i2c_dev), GFP_KERNEL);
	अगर (!i2c_dev)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	i2c_dev->base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(i2c_dev->base))
		वापस PTR_ERR(i2c_dev->base);

	irq_event = irq_of_parse_and_map(np, 0);
	अगर (!irq_event) अणु
		dev_err(&pdev->dev, "IRQ event missing or invalid\n");
		वापस -EINVAL;
	पूर्ण

	irq_error = irq_of_parse_and_map(np, 1);
	अगर (!irq_error) अणु
		dev_err(&pdev->dev, "IRQ error missing or invalid\n");
		वापस -EINVAL;
	पूर्ण

	i2c_dev->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(i2c_dev->clk)) अणु
		dev_err(&pdev->dev, "Error: Missing controller clock\n");
		वापस PTR_ERR(i2c_dev->clk);
	पूर्ण
	ret = clk_prepare_enable(i2c_dev->clk);
	अगर (ret) अणु
		dev_err(i2c_dev->dev, "Failed to prepare_enable clock\n");
		वापस ret;
	पूर्ण

	rst = devm_reset_control_get_exclusive(&pdev->dev, शून्य);
	अगर (IS_ERR(rst)) अणु
		ret = dev_err_probe(&pdev->dev, PTR_ERR(rst),
				    "Error: Missing reset ctrl\n");
		जाओ clk_मुक्त;
	पूर्ण
	reset_control_निश्चित(rst);
	udelay(2);
	reset_control_deनिश्चित(rst);

	i2c_dev->speed = STM32_I2C_SPEED_STANDARD;
	ret = of_property_पढ़ो_u32(np, "clock-frequency", &clk_rate);
	अगर (!ret && clk_rate >= I2C_MAX_FAST_MODE_FREQ)
		i2c_dev->speed = STM32_I2C_SPEED_FAST;

	i2c_dev->dev = &pdev->dev;

	ret = devm_request_irq(&pdev->dev, irq_event, sपंचांग32f4_i2c_isr_event, 0,
			       pdev->name, i2c_dev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to request irq event %i\n",
			irq_event);
		जाओ clk_मुक्त;
	पूर्ण

	ret = devm_request_irq(&pdev->dev, irq_error, sपंचांग32f4_i2c_isr_error, 0,
			       pdev->name, i2c_dev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to request irq error %i\n",
			irq_error);
		जाओ clk_मुक्त;
	पूर्ण

	ret = sपंचांग32f4_i2c_hw_config(i2c_dev);
	अगर (ret)
		जाओ clk_मुक्त;

	adap = &i2c_dev->adap;
	i2c_set_adapdata(adap, i2c_dev);
	snम_लिखो(adap->name, माप(adap->name), "STM32 I2C(%pa)", &res->start);
	adap->owner = THIS_MODULE;
	adap->समयout = 2 * HZ;
	adap->retries = 0;
	adap->algo = &sपंचांग32f4_i2c_algo;
	adap->dev.parent = &pdev->dev;
	adap->dev.of_node = pdev->dev.of_node;

	init_completion(&i2c_dev->complete);

	ret = i2c_add_adapter(adap);
	अगर (ret)
		जाओ clk_मुक्त;

	platक्रमm_set_drvdata(pdev, i2c_dev);

	clk_disable(i2c_dev->clk);

	dev_info(i2c_dev->dev, "STM32F4 I2C driver registered\n");

	वापस 0;

clk_मुक्त:
	clk_disable_unprepare(i2c_dev->clk);
	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांग32f4_i2c_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sपंचांग32f4_i2c_dev *i2c_dev = platक्रमm_get_drvdata(pdev);

	i2c_del_adapter(&i2c_dev->adap);

	clk_unprepare(i2c_dev->clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id sपंचांग32f4_i2c_match[] = अणु
	अणु .compatible = "st,stm32f4-i2c", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sपंचांग32f4_i2c_match);

अटल काष्ठा platक्रमm_driver sपंचांग32f4_i2c_driver = अणु
	.driver = अणु
		.name = "stm32f4-i2c",
		.of_match_table = sपंचांग32f4_i2c_match,
	पूर्ण,
	.probe = sपंचांग32f4_i2c_probe,
	.हटाओ = sपंचांग32f4_i2c_हटाओ,
पूर्ण;

module_platक्रमm_driver(sपंचांग32f4_i2c_driver);

MODULE_AUTHOR("M'boumba Cedric Madianga <cedric.madianga@gmail.com>");
MODULE_DESCRIPTION("STMicroelectronics STM32F4 I2C driver");
MODULE_LICENSE("GPL v2");
