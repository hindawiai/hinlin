<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * driver क्रम ENE KB3926 B/C/D/E/F CIR (pnp id: ENE0XXX)
 *
 * Copyright (C) 2010 Maxim Levitsky <maximlevitsky@gmail.com>
 *
 * Special thanks to:
 *   Sami R. <maesesami@gmail.com> क्रम lot of help in debugging and thereक्रमe
 *    bringing to lअगरe support क्रम transmission & learning mode.
 *
 *   Charlie Andrews <अक्षरliethepilot@googlemail.com> क्रम lots of help in
 *   bringing up the support of new firmware buffer that is popular
 *   on latest notebooks
 *
 *   ENE क्रम partial device करोcumentation
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pnp.h>
#समावेश <linux/पन.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <media/rc-core.h>
#समावेश "ene_ir.h"

अटल पूर्णांक sample_period;
अटल bool learning_mode_क्रमce;
अटल पूर्णांक debug;
अटल bool txsim;

अटल व्योम ene_set_reg_addr(काष्ठा ene_device *dev, u16 reg)
अणु
	outb(reg >> 8, dev->hw_io + ENE_ADDR_HI);
	outb(reg & 0xFF, dev->hw_io + ENE_ADDR_LO);
पूर्ण

/* पढ़ो a hardware रेजिस्टर */
अटल u8 ene_पढ़ो_reg(काष्ठा ene_device *dev, u16 reg)
अणु
	u8 retval;
	ene_set_reg_addr(dev, reg);
	retval = inb(dev->hw_io + ENE_IO);
	dbg_regs("reg %04x == %02x", reg, retval);
	वापस retval;
पूर्ण

/* ग_लिखो a hardware रेजिस्टर */
अटल व्योम ene_ग_लिखो_reg(काष्ठा ene_device *dev, u16 reg, u8 value)
अणु
	dbg_regs("reg %04x <- %02x", reg, value);
	ene_set_reg_addr(dev, reg);
	outb(value, dev->hw_io + ENE_IO);
पूर्ण

/* Set bits in hardware रेजिस्टर */
अटल व्योम ene_set_reg_mask(काष्ठा ene_device *dev, u16 reg, u8 mask)
अणु
	dbg_regs("reg %04x |= %02x", reg, mask);
	ene_set_reg_addr(dev, reg);
	outb(inb(dev->hw_io + ENE_IO) | mask, dev->hw_io + ENE_IO);
पूर्ण

/* Clear bits in hardware रेजिस्टर */
अटल व्योम ene_clear_reg_mask(काष्ठा ene_device *dev, u16 reg, u8 mask)
अणु
	dbg_regs("reg %04x &= ~%02x ", reg, mask);
	ene_set_reg_addr(dev, reg);
	outb(inb(dev->hw_io + ENE_IO) & ~mask, dev->hw_io + ENE_IO);
पूर्ण

/* A helper to set/clear a bit in रेजिस्टर according to boolean variable */
अटल व्योम ene_set_clear_reg_mask(काष्ठा ene_device *dev, u16 reg, u8 mask,
								bool set)
अणु
	अगर (set)
		ene_set_reg_mask(dev, reg, mask);
	अन्यथा
		ene_clear_reg_mask(dev, reg, mask);
पूर्ण

/* detect hardware features */
अटल पूर्णांक ene_hw_detect(काष्ठा ene_device *dev)
अणु
	u8 chip_major, chip_minor;
	u8 hw_revision, old_ver;
	u8 fw_reg2, fw_reg1;

	ene_clear_reg_mask(dev, ENE_ECSTS, ENE_ECSTS_RSRVD);
	chip_major = ene_पढ़ो_reg(dev, ENE_ECVER_MAJOR);
	chip_minor = ene_पढ़ो_reg(dev, ENE_ECVER_MINOR);
	ene_set_reg_mask(dev, ENE_ECSTS, ENE_ECSTS_RSRVD);

	hw_revision = ene_पढ़ो_reg(dev, ENE_ECHV);
	old_ver = ene_पढ़ो_reg(dev, ENE_HW_VER_OLD);

	dev->pll_freq = (ene_पढ़ो_reg(dev, ENE_PLLFRH) << 4) +
		(ene_पढ़ो_reg(dev, ENE_PLLFRL) >> 4);

	अगर (sample_period != ENE_DEFAULT_SAMPLE_PERIOD)
		dev->rx_period_adjust =
			dev->pll_freq == ENE_DEFAULT_PLL_FREQ ? 2 : 4;

	अगर (hw_revision == 0xFF) अणु
		pr_warn("device seems to be disabled\n");
		pr_warn("send a mail to lirc-list@lists.sourceforge.net\n");
		pr_warn("please attach output of acpidump and dmidecode\n");
		वापस -ENODEV;
	पूर्ण

	pr_notice("chip is 0x%02x%02x - kbver = 0x%02x, rev = 0x%02x\n",
		  chip_major, chip_minor, old_ver, hw_revision);

	pr_notice("PLL freq = %d\n", dev->pll_freq);

	अगर (chip_major == 0x33) अणु
		pr_warn("chips 0x33xx aren't supported\n");
		वापस -ENODEV;
	पूर्ण

	अगर (chip_major == 0x39 && chip_minor == 0x26 && hw_revision == 0xC0) अणु
		dev->hw_revision = ENE_HW_C;
		pr_notice("KB3926C detected\n");
	पूर्ण अन्यथा अगर (old_ver == 0x24 && hw_revision == 0xC0) अणु
		dev->hw_revision = ENE_HW_B;
		pr_notice("KB3926B detected\n");
	पूर्ण अन्यथा अणु
		dev->hw_revision = ENE_HW_D;
		pr_notice("KB3926D or higher detected\n");
	पूर्ण

	/* detect features hardware supports */
	अगर (dev->hw_revision < ENE_HW_C)
		वापस 0;

	fw_reg1 = ene_पढ़ो_reg(dev, ENE_FW1);
	fw_reg2 = ene_पढ़ो_reg(dev, ENE_FW2);

	pr_notice("Firmware regs: %02x %02x\n", fw_reg1, fw_reg2);

	dev->hw_use_gpio_0a = !!(fw_reg2 & ENE_FW2_GP0A);
	dev->hw_learning_and_tx_capable = !!(fw_reg2 & ENE_FW2_LEARNING);
	dev->hw_extra_buffer = !!(fw_reg1 & ENE_FW1_HAS_EXTRA_BUF);

	अगर (dev->hw_learning_and_tx_capable)
		dev->hw_fan_input = !!(fw_reg2 & ENE_FW2_FAN_INPUT);

	pr_notice("Hardware features:\n");

	अगर (dev->hw_learning_and_tx_capable) अणु
		pr_notice("* Supports transmitting & learning mode\n");
		pr_notice("   This feature is rare and therefore,\n");
		pr_notice("   you are welcome to test it,\n");
		pr_notice("   and/or contact the author via:\n");
		pr_notice("   lirc-list@lists.sourceforge.net\n");
		pr_notice("   or maximlevitsky@gmail.com\n");

		pr_notice("* Uses GPIO %s for IR raw input\n",
			  dev->hw_use_gpio_0a ? "40" : "0A");

		अगर (dev->hw_fan_input)
			pr_notice("* Uses unused fan feedback input as source of demodulated IR data\n");
	पूर्ण

	अगर (!dev->hw_fan_input)
		pr_notice("* Uses GPIO %s for IR demodulated input\n",
			  dev->hw_use_gpio_0a ? "0A" : "40");

	अगर (dev->hw_extra_buffer)
		pr_notice("* Uses new style input buffer\n");
	वापस 0;
पूर्ण

/* Read properties of hw sample buffer */
अटल व्योम ene_rx_setup_hw_buffer(काष्ठा ene_device *dev)
अणु
	u16 पंचांगp;

	ene_rx_पढ़ो_hw_poपूर्णांकer(dev);
	dev->r_poपूर्णांकer = dev->w_poपूर्णांकer;

	अगर (!dev->hw_extra_buffer) अणु
		dev->buffer_len = ENE_FW_PACKET_SIZE * 2;
		वापस;
	पूर्ण

	पंचांगp = ene_पढ़ो_reg(dev, ENE_FW_SAMPLE_BUFFER);
	पंचांगp |= ene_पढ़ो_reg(dev, ENE_FW_SAMPLE_BUFFER+1) << 8;
	dev->extra_buf1_address = पंचांगp;

	dev->extra_buf1_len = ene_पढ़ो_reg(dev, ENE_FW_SAMPLE_BUFFER + 2);

	पंचांगp = ene_पढ़ो_reg(dev, ENE_FW_SAMPLE_BUFFER + 3);
	पंचांगp |= ene_पढ़ो_reg(dev, ENE_FW_SAMPLE_BUFFER + 4) << 8;
	dev->extra_buf2_address = पंचांगp;

	dev->extra_buf2_len = ene_पढ़ो_reg(dev, ENE_FW_SAMPLE_BUFFER + 5);

	dev->buffer_len = dev->extra_buf1_len + dev->extra_buf2_len + 8;

	pr_notice("Hardware uses 2 extended buffers:\n");
	pr_notice("  0x%04x - len : %d\n",
		  dev->extra_buf1_address, dev->extra_buf1_len);
	pr_notice("  0x%04x - len : %d\n",
		  dev->extra_buf2_address, dev->extra_buf2_len);

	pr_notice("Total buffer len = %d\n", dev->buffer_len);

	अगर (dev->buffer_len > 64 || dev->buffer_len < 16)
		जाओ error;

	अगर (dev->extra_buf1_address > 0xFBFC ||
					dev->extra_buf1_address < 0xEC00)
		जाओ error;

	अगर (dev->extra_buf2_address > 0xFBFC ||
					dev->extra_buf2_address < 0xEC00)
		जाओ error;

	अगर (dev->r_poपूर्णांकer > dev->buffer_len)
		जाओ error;

	ene_set_reg_mask(dev, ENE_FW1, ENE_FW1_EXTRA_BUF_HND);
	वापस;
error:
	pr_warn("Error validating extra buffers, device probably won't work\n");
	dev->hw_extra_buffer = false;
	ene_clear_reg_mask(dev, ENE_FW1, ENE_FW1_EXTRA_BUF_HND);
पूर्ण


/* Restore the poपूर्णांकers to extra buffers - to make module reload work*/
अटल व्योम ene_rx_restore_hw_buffer(काष्ठा ene_device *dev)
अणु
	अगर (!dev->hw_extra_buffer)
		वापस;

	ene_ग_लिखो_reg(dev, ENE_FW_SAMPLE_BUFFER + 0,
				dev->extra_buf1_address & 0xFF);
	ene_ग_लिखो_reg(dev, ENE_FW_SAMPLE_BUFFER + 1,
				dev->extra_buf1_address >> 8);
	ene_ग_लिखो_reg(dev, ENE_FW_SAMPLE_BUFFER + 2, dev->extra_buf1_len);

	ene_ग_लिखो_reg(dev, ENE_FW_SAMPLE_BUFFER + 3,
				dev->extra_buf2_address & 0xFF);
	ene_ग_लिखो_reg(dev, ENE_FW_SAMPLE_BUFFER + 4,
				dev->extra_buf2_address >> 8);
	ene_ग_लिखो_reg(dev, ENE_FW_SAMPLE_BUFFER + 5,
				dev->extra_buf2_len);
	ene_clear_reg_mask(dev, ENE_FW1, ENE_FW1_EXTRA_BUF_HND);
पूर्ण

/* Read hardware ग_लिखो poपूर्णांकer */
अटल व्योम ene_rx_पढ़ो_hw_poपूर्णांकer(काष्ठा ene_device *dev)
अणु
	अगर (dev->hw_extra_buffer)
		dev->w_poपूर्णांकer = ene_पढ़ो_reg(dev, ENE_FW_RX_POINTER);
	अन्यथा
		dev->w_poपूर्णांकer = ene_पढ़ो_reg(dev, ENE_FW2)
			& ENE_FW2_BUF_WPTR ? 0 : ENE_FW_PACKET_SIZE;

	dbg_verbose("RB: HW write pointer: %02x, driver read pointer: %02x",
		dev->w_poपूर्णांकer, dev->r_poपूर्णांकer);
पूर्ण

/* Gets address of next sample from HW ring buffer */
अटल पूर्णांक ene_rx_get_sample_reg(काष्ठा ene_device *dev)
अणु
	पूर्णांक r_poपूर्णांकer;

	अगर (dev->r_poपूर्णांकer == dev->w_poपूर्णांकer) अणु
		dbg_verbose("RB: hit end, try update w_pointer");
		ene_rx_पढ़ो_hw_poपूर्णांकer(dev);
	पूर्ण

	अगर (dev->r_poपूर्णांकer == dev->w_poपूर्णांकer) अणु
		dbg_verbose("RB: end of data at %d", dev->r_poपूर्णांकer);
		वापस 0;
	पूर्ण

	dbg_verbose("RB: reading at offset %d", dev->r_poपूर्णांकer);
	r_poपूर्णांकer = dev->r_poपूर्णांकer;

	dev->r_poपूर्णांकer++;
	अगर (dev->r_poपूर्णांकer == dev->buffer_len)
		dev->r_poपूर्णांकer = 0;

	dbg_verbose("RB: next read will be from offset %d", dev->r_poपूर्णांकer);

	अगर (r_poपूर्णांकer < 8) अणु
		dbg_verbose("RB: read at main buffer at %d", r_poपूर्णांकer);
		वापस ENE_FW_SAMPLE_BUFFER + r_poपूर्णांकer;
	पूर्ण

	r_poपूर्णांकer -= 8;

	अगर (r_poपूर्णांकer < dev->extra_buf1_len) अणु
		dbg_verbose("RB: read at 1st extra buffer at %d", r_poपूर्णांकer);
		वापस dev->extra_buf1_address + r_poपूर्णांकer;
	पूर्ण

	r_poपूर्णांकer -= dev->extra_buf1_len;

	अगर (r_poपूर्णांकer < dev->extra_buf2_len) अणु
		dbg_verbose("RB: read at 2nd extra buffer at %d", r_poपूर्णांकer);
		वापस dev->extra_buf2_address + r_poपूर्णांकer;
	पूर्ण

	dbg("attempt to read beyond ring buffer end");
	वापस 0;
पूर्ण

/* Sense current received carrier */
अटल व्योम ene_rx_sense_carrier(काष्ठा ene_device *dev)
अणु
	पूर्णांक carrier, duty_cycle;
	पूर्णांक period = ene_पढ़ो_reg(dev, ENE_CIRCAR_PRD);
	पूर्णांक hperiod = ene_पढ़ो_reg(dev, ENE_CIRCAR_HPRD);

	अगर (!(period & ENE_CIRCAR_PRD_VALID))
		वापस;

	period &= ~ENE_CIRCAR_PRD_VALID;

	अगर (!period)
		वापस;

	dbg("RX: hardware carrier period = %02x", period);
	dbg("RX: hardware carrier pulse period = %02x", hperiod);

	carrier = 2000000 / period;
	duty_cycle = (hperiod * 100) / period;
	dbg("RX: sensed carrier = %d Hz, duty cycle %d%%",
						carrier, duty_cycle);
	अगर (dev->carrier_detect_enabled) अणु
		काष्ठा ir_raw_event ev = अणु
			.carrier_report = true,
			.carrier = carrier,
			.duty_cycle = duty_cycle
		पूर्ण;
		ir_raw_event_store(dev->rdev, &ev);
	पूर्ण
पूर्ण

/* this enables/disables the CIR RX engine */
अटल व्योम ene_rx_enable_cir_engine(काष्ठा ene_device *dev, bool enable)
अणु
	ene_set_clear_reg_mask(dev, ENE_CIRCFG,
			ENE_CIRCFG_RX_EN | ENE_CIRCFG_RX_IRQ, enable);
पूर्ण

/* this selects input क्रम CIR engine. Ether GPIO 0A or GPIO40*/
अटल व्योम ene_rx_select_input(काष्ठा ene_device *dev, bool gpio_0a)
अणु
	ene_set_clear_reg_mask(dev, ENE_CIRCFG2, ENE_CIRCFG2_GPIO0A, gpio_0a);
पूर्ण

/*
 * this enables alternative input via fan tachometer sensor and bypasses
 * the hw CIR engine
 */
अटल व्योम ene_rx_enable_fan_input(काष्ठा ene_device *dev, bool enable)
अणु
	अगर (!dev->hw_fan_input)
		वापस;

	अगर (!enable)
		ene_ग_लिखो_reg(dev, ENE_FAN_AS_IN1, 0);
	अन्यथा अणु
		ene_ग_लिखो_reg(dev, ENE_FAN_AS_IN1, ENE_FAN_AS_IN1_EN);
		ene_ग_लिखो_reg(dev, ENE_FAN_AS_IN2, ENE_FAN_AS_IN2_EN);
	पूर्ण
पूर्ण

/* setup the receiver क्रम RX*/
अटल व्योम ene_rx_setup(काष्ठा ene_device *dev)
अणु
	bool learning_mode = dev->learning_mode_enabled ||
					dev->carrier_detect_enabled;
	पूर्णांक sample_period_adjust = 0;

	dbg("RX: setup receiver, learning mode = %d", learning_mode);


	/* This selects RLC input and clears CFG2 settings */
	ene_ग_लिखो_reg(dev, ENE_CIRCFG2, 0x00);

	/* set sample period*/
	अगर (sample_period == ENE_DEFAULT_SAMPLE_PERIOD)
		sample_period_adjust =
			dev->pll_freq == ENE_DEFAULT_PLL_FREQ ? 1 : 2;

	ene_ग_लिखो_reg(dev, ENE_CIRRLC_CFG,
			(sample_period + sample_period_adjust) |
						ENE_CIRRLC_CFG_OVERFLOW);
	/* revB करोesn't support inमाला_दो */
	अगर (dev->hw_revision < ENE_HW_C)
		जाओ select_समयout;

	अगर (learning_mode) अणु

		WARN_ON(!dev->hw_learning_and_tx_capable);

		/* Enable the opposite of the normal input
		That means that अगर GPIO40 is normally used, use GPIO0A
		and vice versa.
		This input will carry non demodulated
		संकेत, and we will tell the hw to demodulate it itself */
		ene_rx_select_input(dev, !dev->hw_use_gpio_0a);
		dev->rx_fan_input_inuse = false;

		/* Enable carrier demodulation */
		ene_set_reg_mask(dev, ENE_CIRCFG, ENE_CIRCFG_CARR_DEMOD);

		/* Enable carrier detection */
		ene_ग_लिखो_reg(dev, ENE_CIRCAR_PULS, 0x63);
		ene_set_clear_reg_mask(dev, ENE_CIRCFG2, ENE_CIRCFG2_CARR_DETECT,
			dev->carrier_detect_enabled || debug);
	पूर्ण अन्यथा अणु
		अगर (dev->hw_fan_input)
			dev->rx_fan_input_inuse = true;
		अन्यथा
			ene_rx_select_input(dev, dev->hw_use_gpio_0a);

		/* Disable carrier detection & demodulation */
		ene_clear_reg_mask(dev, ENE_CIRCFG, ENE_CIRCFG_CARR_DEMOD);
		ene_clear_reg_mask(dev, ENE_CIRCFG2, ENE_CIRCFG2_CARR_DETECT);
	पूर्ण

select_समयout:
	अगर (dev->rx_fan_input_inuse) अणु
		dev->rdev->rx_resolution = ENE_FW_SAMPLE_PERIOD_FAN;

		/* Fan input करोesn't support समयouts, it just ends the
			input with a maximum sample */
		dev->rdev->min_समयout = dev->rdev->max_समयout =
			ENE_FW_SMPL_BUF_FAN_MSK *
				ENE_FW_SAMPLE_PERIOD_FAN;
	पूर्ण अन्यथा अणु
		dev->rdev->rx_resolution = sample_period;

		/* Theoreticly समयout is unlimited, but we cap it
		 * because it was seen that on one device, it
		 * would stop sending spaces after around 250 msec.
		 * Besides, this is बंद to 2^32 anyway and समयout is u32.
		 */
		dev->rdev->min_समयout = 127 * sample_period;
		dev->rdev->max_समयout = 200000;
	पूर्ण

	अगर (dev->hw_learning_and_tx_capable)
		dev->rdev->tx_resolution = sample_period;

	अगर (dev->rdev->समयout > dev->rdev->max_समयout)
		dev->rdev->समयout = dev->rdev->max_समयout;
	अगर (dev->rdev->समयout < dev->rdev->min_समयout)
		dev->rdev->समयout = dev->rdev->min_समयout;
पूर्ण

/* Enable the device क्रम receive */
अटल व्योम ene_rx_enable_hw(काष्ठा ene_device *dev)
अणु
	u8 reg_value;

	/* Enable प्रणाली पूर्णांकerrupt */
	अगर (dev->hw_revision < ENE_HW_C) अणु
		ene_ग_लिखो_reg(dev, ENEB_IRQ, dev->irq << 1);
		ene_ग_लिखो_reg(dev, ENEB_IRQ_UNK1, 0x01);
	पूर्ण अन्यथा अणु
		reg_value = ene_पढ़ो_reg(dev, ENE_IRQ) & 0xF0;
		reg_value |= ENE_IRQ_UNK_EN;
		reg_value &= ~ENE_IRQ_STATUS;
		reg_value |= (dev->irq & ENE_IRQ_MASK);
		ene_ग_लिखो_reg(dev, ENE_IRQ, reg_value);
	पूर्ण

	/* Enable inमाला_दो */
	ene_rx_enable_fan_input(dev, dev->rx_fan_input_inuse);
	ene_rx_enable_cir_engine(dev, !dev->rx_fan_input_inuse);

	/* ack any pending irqs - just in हाल */
	ene_irq_status(dev);

	/* enable firmware bits */
	ene_set_reg_mask(dev, ENE_FW1, ENE_FW1_ENABLE | ENE_FW1_IRQ);

	/* enter idle mode */
	ir_raw_event_set_idle(dev->rdev, true);
पूर्ण

/* Enable the device क्रम receive - wrapper to track the state*/
अटल व्योम ene_rx_enable(काष्ठा ene_device *dev)
अणु
	ene_rx_enable_hw(dev);
	dev->rx_enabled = true;
पूर्ण

/* Disable the device receiver */
अटल व्योम ene_rx_disable_hw(काष्ठा ene_device *dev)
अणु
	/* disable inमाला_दो */
	ene_rx_enable_cir_engine(dev, false);
	ene_rx_enable_fan_input(dev, false);

	/* disable hardware IRQ and firmware flag */
	ene_clear_reg_mask(dev, ENE_FW1, ENE_FW1_ENABLE | ENE_FW1_IRQ);
	ir_raw_event_set_idle(dev->rdev, true);
पूर्ण

/* Disable the device receiver - wrapper to track the state */
अटल व्योम ene_rx_disable(काष्ठा ene_device *dev)
अणु
	ene_rx_disable_hw(dev);
	dev->rx_enabled = false;
पूर्ण

/* This resets the receiver. Useful to stop stream of spaces at end of
 * transmission
 */
अटल व्योम ene_rx_reset(काष्ठा ene_device *dev)
अणु
	ene_clear_reg_mask(dev, ENE_CIRCFG, ENE_CIRCFG_RX_EN);
	ene_set_reg_mask(dev, ENE_CIRCFG, ENE_CIRCFG_RX_EN);
पूर्ण

/* Set up the TX carrier frequency and duty cycle */
अटल व्योम ene_tx_set_carrier(काष्ठा ene_device *dev)
अणु
	u8 tx_puls_width;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->hw_lock, flags);

	ene_set_clear_reg_mask(dev, ENE_CIRCFG,
		ENE_CIRCFG_TX_CARR, dev->tx_period > 0);

	अगर (!dev->tx_period)
		जाओ unlock;

	BUG_ON(dev->tx_duty_cycle >= 100 || dev->tx_duty_cycle <= 0);

	tx_puls_width = dev->tx_period / (100 / dev->tx_duty_cycle);

	अगर (!tx_puls_width)
		tx_puls_width = 1;

	dbg("TX: pulse distance = %d * 500 ns", dev->tx_period);
	dbg("TX: pulse width = %d * 500 ns", tx_puls_width);

	ene_ग_लिखो_reg(dev, ENE_CIRMOD_PRD, dev->tx_period | ENE_CIRMOD_PRD_POL);
	ene_ग_लिखो_reg(dev, ENE_CIRMOD_HPRD, tx_puls_width);
unlock:
	spin_unlock_irqrestore(&dev->hw_lock, flags);
पूर्ण

/* Enable/disable transmitters */
अटल व्योम ene_tx_set_transmitters(काष्ठा ene_device *dev)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->hw_lock, flags);
	ene_set_clear_reg_mask(dev, ENE_GPIOFS8, ENE_GPIOFS8_GPIO41,
					!!(dev->transmitter_mask & 0x01));
	ene_set_clear_reg_mask(dev, ENE_GPIOFS1, ENE_GPIOFS1_GPIO0D,
					!!(dev->transmitter_mask & 0x02));
	spin_unlock_irqrestore(&dev->hw_lock, flags);
पूर्ण

/* prepare transmission */
अटल व्योम ene_tx_enable(काष्ठा ene_device *dev)
अणु
	u8 conf1 = ene_पढ़ो_reg(dev, ENE_CIRCFG);
	u8 fwreg2 = ene_पढ़ो_reg(dev, ENE_FW2);

	dev->saved_conf1 = conf1;

	/* Show inक्रमmation about currently connected transmitter jacks */
	अगर (fwreg2 & ENE_FW2_EMMITER1_CONN)
		dbg("TX: Transmitter #1 is connected");

	अगर (fwreg2 & ENE_FW2_EMMITER2_CONN)
		dbg("TX: Transmitter #2 is connected");

	अगर (!(fwreg2 & (ENE_FW2_EMMITER1_CONN | ENE_FW2_EMMITER2_CONN)))
		pr_warn("TX: transmitter cable isn't connected!\n");

	/* disable receive on revc */
	अगर (dev->hw_revision == ENE_HW_C)
		conf1 &= ~ENE_CIRCFG_RX_EN;

	/* Enable TX engine */
	conf1 |= ENE_CIRCFG_TX_EN | ENE_CIRCFG_TX_IRQ;
	ene_ग_लिखो_reg(dev, ENE_CIRCFG, conf1);
पूर्ण

/* end transmission */
अटल व्योम ene_tx_disable(काष्ठा ene_device *dev)
अणु
	ene_ग_लिखो_reg(dev, ENE_CIRCFG, dev->saved_conf1);
	dev->tx_buffer = शून्य;
पूर्ण


/* TX one sample - must be called with dev->hw_lock*/
अटल व्योम ene_tx_sample(काष्ठा ene_device *dev)
अणु
	u8 raw_tx;
	u32 sample;
	bool pulse = dev->tx_sample_pulse;

	अगर (!dev->tx_buffer) अणु
		pr_warn("TX: BUG: attempt to transmit NULL buffer\n");
		वापस;
	पूर्ण

	/* Grab next TX sample */
	अगर (!dev->tx_sample) अणु

		अगर (dev->tx_pos == dev->tx_len) अणु
			अगर (!dev->tx_करोne) अणु
				dbg("TX: no more data to send");
				dev->tx_करोne = true;
				जाओ निकास;
			पूर्ण अन्यथा अणु
				dbg("TX: last sample sent by hardware");
				ene_tx_disable(dev);
				complete(&dev->tx_complete);
				वापस;
			पूर्ण
		पूर्ण

		sample = dev->tx_buffer[dev->tx_pos++];
		dev->tx_sample_pulse = !dev->tx_sample_pulse;

		dev->tx_sample = DIV_ROUND_CLOSEST(sample, sample_period);

		अगर (!dev->tx_sample)
			dev->tx_sample = 1;
	पूर्ण

	raw_tx = min(dev->tx_sample , (अचिन्हित पूर्णांक)ENE_CIRRLC_OUT_MASK);
	dev->tx_sample -= raw_tx;

	dbg("TX: sample %8d (%s)", raw_tx * sample_period,
						pulse ? "pulse" : "space");
	अगर (pulse)
		raw_tx |= ENE_CIRRLC_OUT_PULSE;

	ene_ग_लिखो_reg(dev,
		dev->tx_reg ? ENE_CIRRLC_OUT1 : ENE_CIRRLC_OUT0, raw_tx);

	dev->tx_reg = !dev->tx_reg;
निकास:
	/* simulate TX करोne पूर्णांकerrupt */
	अगर (txsim)
		mod_समयr(&dev->tx_sim_समयr, jअगरfies + HZ / 500);
पूर्ण

/* समयr to simulate tx करोne पूर्णांकerrupt */
अटल व्योम ene_tx_irqsim(काष्ठा समयr_list *t)
अणु
	काष्ठा ene_device *dev = from_समयr(dev, t, tx_sim_समयr);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->hw_lock, flags);
	ene_tx_sample(dev);
	spin_unlock_irqrestore(&dev->hw_lock, flags);
पूर्ण


/* पढ़ो irq status and ack it */
अटल पूर्णांक ene_irq_status(काष्ठा ene_device *dev)
अणु
	u8 irq_status;
	u8 fw_flags1, fw_flags2;
	पूर्णांक retval = 0;

	fw_flags2 = ene_पढ़ो_reg(dev, ENE_FW2);

	अगर (dev->hw_revision < ENE_HW_C) अणु
		irq_status = ene_पढ़ो_reg(dev, ENEB_IRQ_STATUS);

		अगर (!(irq_status & ENEB_IRQ_STATUS_IR))
			वापस 0;

		ene_clear_reg_mask(dev, ENEB_IRQ_STATUS, ENEB_IRQ_STATUS_IR);
		वापस ENE_IRQ_RX;
	पूर्ण

	irq_status = ene_पढ़ो_reg(dev, ENE_IRQ);
	अगर (!(irq_status & ENE_IRQ_STATUS))
		वापस 0;

	/* original driver करोes that twice - a workaround ? */
	ene_ग_लिखो_reg(dev, ENE_IRQ, irq_status & ~ENE_IRQ_STATUS);
	ene_ग_लिखो_reg(dev, ENE_IRQ, irq_status & ~ENE_IRQ_STATUS);

	/* check RX पूर्णांकerrupt */
	अगर (fw_flags2 & ENE_FW2_RXIRQ) अणु
		retval |= ENE_IRQ_RX;
		ene_ग_लिखो_reg(dev, ENE_FW2, fw_flags2 & ~ENE_FW2_RXIRQ);
	पूर्ण

	/* check TX पूर्णांकerrupt */
	fw_flags1 = ene_पढ़ो_reg(dev, ENE_FW1);
	अगर (fw_flags1 & ENE_FW1_TXIRQ) अणु
		ene_ग_लिखो_reg(dev, ENE_FW1, fw_flags1 & ~ENE_FW1_TXIRQ);
		retval |= ENE_IRQ_TX;
	पूर्ण

	वापस retval;
पूर्ण

/* पूर्णांकerrupt handler */
अटल irqवापस_t ene_isr(पूर्णांक irq, व्योम *data)
अणु
	u16 hw_value, reg;
	पूर्णांक hw_sample, irq_status;
	bool pulse;
	अचिन्हित दीर्घ flags;
	irqवापस_t retval = IRQ_NONE;
	काष्ठा ene_device *dev = (काष्ठा ene_device *)data;
	काष्ठा ir_raw_event ev = अणुपूर्ण;

	spin_lock_irqsave(&dev->hw_lock, flags);

	dbg_verbose("ISR called");
	ene_rx_पढ़ो_hw_poपूर्णांकer(dev);
	irq_status = ene_irq_status(dev);

	अगर (!irq_status)
		जाओ unlock;

	retval = IRQ_HANDLED;

	अगर (irq_status & ENE_IRQ_TX) अणु
		dbg_verbose("TX interrupt");
		अगर (!dev->hw_learning_and_tx_capable) अणु
			dbg("TX interrupt on unsupported device!");
			जाओ unlock;
		पूर्ण
		ene_tx_sample(dev);
	पूर्ण

	अगर (!(irq_status & ENE_IRQ_RX))
		जाओ unlock;

	dbg_verbose("RX interrupt");

	अगर (dev->hw_learning_and_tx_capable)
		ene_rx_sense_carrier(dev);

	/* On hardware that करोn't support extra buffer we need to trust
		the पूर्णांकerrupt and not track the पढ़ो poपूर्णांकer */
	अगर (!dev->hw_extra_buffer)
		dev->r_poपूर्णांकer = dev->w_poपूर्णांकer == 0 ? ENE_FW_PACKET_SIZE : 0;

	जबतक (1) अणु

		reg = ene_rx_get_sample_reg(dev);

		dbg_verbose("next sample to read at: %04x", reg);
		अगर (!reg)
			अवरोध;

		hw_value = ene_पढ़ो_reg(dev, reg);

		अगर (dev->rx_fan_input_inuse) अणु

			पूर्णांक offset = ENE_FW_SMPL_BUF_FAN - ENE_FW_SAMPLE_BUFFER;

			/* पढ़ो high part of the sample */
			hw_value |= ene_पढ़ो_reg(dev, reg + offset) << 8;
			pulse = hw_value & ENE_FW_SMPL_BUF_FAN_PLS;

			/* clear space bit, and other unused bits */
			hw_value &= ENE_FW_SMPL_BUF_FAN_MSK;
			hw_sample = hw_value * ENE_FW_SAMPLE_PERIOD_FAN;

		पूर्ण अन्यथा अणु
			pulse = !(hw_value & ENE_FW_SAMPLE_SPACE);
			hw_value &= ~ENE_FW_SAMPLE_SPACE;
			hw_sample = hw_value * sample_period;

			अगर (dev->rx_period_adjust) अणु
				hw_sample *= 100;
				hw_sample /= (100 + dev->rx_period_adjust);
			पूर्ण
		पूर्ण

		अगर (!dev->hw_extra_buffer && !hw_sample) अणु
			dev->r_poपूर्णांकer = dev->w_poपूर्णांकer;
			जारी;
		पूर्ण

		dbg("RX: %d (%s)", hw_sample, pulse ? "pulse" : "space");

		ev.duration = hw_sample;
		ev.pulse = pulse;
		ir_raw_event_store_with_filter(dev->rdev, &ev);
	पूर्ण

	ir_raw_event_handle(dev->rdev);
unlock:
	spin_unlock_irqrestore(&dev->hw_lock, flags);
	वापस retval;
पूर्ण

/* Initialize शेष settings */
अटल व्योम ene_setup_शेष_settings(काष्ठा ene_device *dev)
अणु
	dev->tx_period = 32;
	dev->tx_duty_cycle = 50; /*%*/
	dev->transmitter_mask = 0x03;
	dev->learning_mode_enabled = learning_mode_क्रमce;

	/* Set reasonable शेष समयout */
	dev->rdev->समयout = MS_TO_US(150);
पूर्ण

/* Upload all hardware settings at once. Used at load and resume समय */
अटल व्योम ene_setup_hw_settings(काष्ठा ene_device *dev)
अणु
	अगर (dev->hw_learning_and_tx_capable) अणु
		ene_tx_set_carrier(dev);
		ene_tx_set_transmitters(dev);
	पूर्ण

	ene_rx_setup(dev);
पूर्ण

/* outside पूर्णांकerface: called on first खोलो*/
अटल पूर्णांक ene_खोलो(काष्ठा rc_dev *rdev)
अणु
	काष्ठा ene_device *dev = rdev->priv;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->hw_lock, flags);
	ene_rx_enable(dev);
	spin_unlock_irqrestore(&dev->hw_lock, flags);
	वापस 0;
पूर्ण

/* outside पूर्णांकerface: called on device बंद*/
अटल व्योम ene_बंद(काष्ठा rc_dev *rdev)
अणु
	काष्ठा ene_device *dev = rdev->priv;
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&dev->hw_lock, flags);

	ene_rx_disable(dev);
	spin_unlock_irqrestore(&dev->hw_lock, flags);
पूर्ण

/* outside पूर्णांकerface: set transmitter mask */
अटल पूर्णांक ene_set_tx_mask(काष्ठा rc_dev *rdev, u32 tx_mask)
अणु
	काष्ठा ene_device *dev = rdev->priv;
	dbg("TX: attempt to set transmitter mask %02x", tx_mask);

	/* invalid txmask */
	अगर (!tx_mask || tx_mask & ~0x03) अणु
		dbg("TX: invalid mask");
		/* वापस count of transmitters */
		वापस 2;
	पूर्ण

	dev->transmitter_mask = tx_mask;
	ene_tx_set_transmitters(dev);
	वापस 0;
पूर्ण

/* outside पूर्णांकerface : set tx carrier */
अटल पूर्णांक ene_set_tx_carrier(काष्ठा rc_dev *rdev, u32 carrier)
अणु
	काष्ठा ene_device *dev = rdev->priv;
	u32 period;

	dbg("TX: attempt to set tx carrier to %d kHz", carrier);
	अगर (carrier == 0)
		वापस -EINVAL;

	period = 2000000 / carrier;
	अगर (period && (period > ENE_CIRMOD_PRD_MAX ||
			period < ENE_CIRMOD_PRD_MIN)) अणु

		dbg("TX: out of range %d-%d kHz carrier",
			2000 / ENE_CIRMOD_PRD_MIN, 2000 / ENE_CIRMOD_PRD_MAX);
		वापस -EINVAL;
	पूर्ण

	dev->tx_period = period;
	ene_tx_set_carrier(dev);
	वापस 0;
पूर्ण

/*outside पूर्णांकerface : set tx duty cycle */
अटल पूर्णांक ene_set_tx_duty_cycle(काष्ठा rc_dev *rdev, u32 duty_cycle)
अणु
	काष्ठा ene_device *dev = rdev->priv;
	dbg("TX: setting duty cycle to %d%%", duty_cycle);
	dev->tx_duty_cycle = duty_cycle;
	ene_tx_set_carrier(dev);
	वापस 0;
पूर्ण

/* outside पूर्णांकerface: enable learning mode */
अटल पूर्णांक ene_set_learning_mode(काष्ठा rc_dev *rdev, पूर्णांक enable)
अणु
	काष्ठा ene_device *dev = rdev->priv;
	अचिन्हित दीर्घ flags;
	अगर (enable == dev->learning_mode_enabled)
		वापस 0;

	spin_lock_irqsave(&dev->hw_lock, flags);
	dev->learning_mode_enabled = enable;
	ene_rx_disable(dev);
	ene_rx_setup(dev);
	ene_rx_enable(dev);
	spin_unlock_irqrestore(&dev->hw_lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक ene_set_carrier_report(काष्ठा rc_dev *rdev, पूर्णांक enable)
अणु
	काष्ठा ene_device *dev = rdev->priv;
	अचिन्हित दीर्घ flags;

	अगर (enable == dev->carrier_detect_enabled)
		वापस 0;

	spin_lock_irqsave(&dev->hw_lock, flags);
	dev->carrier_detect_enabled = enable;
	ene_rx_disable(dev);
	ene_rx_setup(dev);
	ene_rx_enable(dev);
	spin_unlock_irqrestore(&dev->hw_lock, flags);
	वापस 0;
पूर्ण

/* outside पूर्णांकerface: enable or disable idle mode */
अटल व्योम ene_set_idle(काष्ठा rc_dev *rdev, bool idle)
अणु
	काष्ठा ene_device *dev = rdev->priv;

	अगर (idle) अणु
		ene_rx_reset(dev);
		dbg("RX: end of data");
	पूर्ण
पूर्ण

/* outside पूर्णांकerface: transmit */
अटल पूर्णांक ene_transmit(काष्ठा rc_dev *rdev, अचिन्हित *buf, अचिन्हित n)
अणु
	काष्ठा ene_device *dev = rdev->priv;
	अचिन्हित दीर्घ flags;

	dev->tx_buffer = buf;
	dev->tx_len = n;
	dev->tx_pos = 0;
	dev->tx_reg = 0;
	dev->tx_करोne = 0;
	dev->tx_sample = 0;
	dev->tx_sample_pulse = false;

	dbg("TX: %d samples", dev->tx_len);

	spin_lock_irqsave(&dev->hw_lock, flags);

	ene_tx_enable(dev);

	/* Transmit first two samples */
	ene_tx_sample(dev);
	ene_tx_sample(dev);

	spin_unlock_irqrestore(&dev->hw_lock, flags);

	अगर (रुको_क्रम_completion_समयout(&dev->tx_complete, 2 * HZ) == 0) अणु
		dbg("TX: timeout");
		spin_lock_irqsave(&dev->hw_lock, flags);
		ene_tx_disable(dev);
		spin_unlock_irqrestore(&dev->hw_lock, flags);
	पूर्ण अन्यथा
		dbg("TX: done");
	वापस n;
पूर्ण

/* probe entry */
अटल पूर्णांक ene_probe(काष्ठा pnp_dev *pnp_dev, स्थिर काष्ठा pnp_device_id *id)
अणु
	पूर्णांक error = -ENOMEM;
	काष्ठा rc_dev *rdev;
	काष्ठा ene_device *dev;

	/* allocate memory */
	dev = kzalloc(माप(काष्ठा ene_device), GFP_KERNEL);
	rdev = rc_allocate_device(RC_DRIVER_IR_RAW);
	अगर (!dev || !rdev)
		जाओ निकास_मुक्त_dev_rdev;

	/* validate resources */
	error = -ENODEV;

	/* init these to -1, as 0 is valid क्रम both */
	dev->hw_io = -1;
	dev->irq = -1;

	अगर (!pnp_port_valid(pnp_dev, 0) ||
	    pnp_port_len(pnp_dev, 0) < ENE_IO_SIZE)
		जाओ निकास_मुक्त_dev_rdev;

	अगर (!pnp_irq_valid(pnp_dev, 0))
		जाओ निकास_मुक्त_dev_rdev;

	spin_lock_init(&dev->hw_lock);

	dev->hw_io = pnp_port_start(pnp_dev, 0);
	dev->irq = pnp_irq(pnp_dev, 0);


	pnp_set_drvdata(pnp_dev, dev);
	dev->pnp_dev = pnp_dev;

	/* करोn't allow too लघु/दीर्घ sample periods */
	अगर (sample_period < 5 || sample_period > 0x7F)
		sample_period = ENE_DEFAULT_SAMPLE_PERIOD;

	/* detect hardware version and features */
	error = ene_hw_detect(dev);
	अगर (error)
		जाओ निकास_मुक्त_dev_rdev;

	अगर (!dev->hw_learning_and_tx_capable && txsim) अणु
		dev->hw_learning_and_tx_capable = true;
		समयr_setup(&dev->tx_sim_समयr, ene_tx_irqsim, 0);
		pr_warn("Simulation of TX activated\n");
	पूर्ण

	अगर (!dev->hw_learning_and_tx_capable)
		learning_mode_क्रमce = false;

	rdev->allowed_protocols = RC_PROTO_BIT_ALL_IR_DECODER;
	rdev->priv = dev;
	rdev->खोलो = ene_खोलो;
	rdev->बंद = ene_बंद;
	rdev->s_idle = ene_set_idle;
	rdev->driver_name = ENE_DRIVER_NAME;
	rdev->map_name = RC_MAP_RC6_MCE;
	rdev->device_name = "ENE eHome Infrared Remote Receiver";

	अगर (dev->hw_learning_and_tx_capable) अणु
		rdev->s_learning_mode = ene_set_learning_mode;
		init_completion(&dev->tx_complete);
		rdev->tx_ir = ene_transmit;
		rdev->s_tx_mask = ene_set_tx_mask;
		rdev->s_tx_carrier = ene_set_tx_carrier;
		rdev->s_tx_duty_cycle = ene_set_tx_duty_cycle;
		rdev->s_carrier_report = ene_set_carrier_report;
		rdev->device_name = "ENE eHome Infrared Remote Transceiver";
	पूर्ण

	dev->rdev = rdev;

	ene_rx_setup_hw_buffer(dev);
	ene_setup_शेष_settings(dev);
	ene_setup_hw_settings(dev);

	device_set_wakeup_capable(&pnp_dev->dev, true);
	device_set_wakeup_enable(&pnp_dev->dev, true);

	error = rc_रेजिस्टर_device(rdev);
	अगर (error < 0)
		जाओ निकास_मुक्त_dev_rdev;

	/* claim the resources */
	error = -EBUSY;
	अगर (!request_region(dev->hw_io, ENE_IO_SIZE, ENE_DRIVER_NAME)) अणु
		जाओ निकास_unरेजिस्टर_device;
	पूर्ण

	अगर (request_irq(dev->irq, ene_isr,
			IRQF_SHARED, ENE_DRIVER_NAME, (व्योम *)dev)) अणु
		जाओ निकास_release_hw_io;
	पूर्ण

	pr_notice("driver has been successfully loaded\n");
	वापस 0;

निकास_release_hw_io:
	release_region(dev->hw_io, ENE_IO_SIZE);
निकास_unरेजिस्टर_device:
	rc_unरेजिस्टर_device(rdev);
	rdev = शून्य;
निकास_मुक्त_dev_rdev:
	rc_मुक्त_device(rdev);
	kमुक्त(dev);
	वापस error;
पूर्ण

/* मुख्य unload function */
अटल व्योम ene_हटाओ(काष्ठा pnp_dev *pnp_dev)
अणु
	काष्ठा ene_device *dev = pnp_get_drvdata(pnp_dev);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->hw_lock, flags);
	ene_rx_disable(dev);
	ene_rx_restore_hw_buffer(dev);
	spin_unlock_irqrestore(&dev->hw_lock, flags);

	मुक्त_irq(dev->irq, dev);
	release_region(dev->hw_io, ENE_IO_SIZE);
	rc_unरेजिस्टर_device(dev->rdev);
	kमुक्त(dev);
पूर्ण

/* enable wake on IR (wakes on specअगरic button on original remote) */
अटल व्योम ene_enable_wake(काष्ठा ene_device *dev, bool enable)
अणु
	dbg("wake on IR %s", enable ? "enabled" : "disabled");
	ene_set_clear_reg_mask(dev, ENE_FW1, ENE_FW1_WAKE, enable);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक ene_suspend(काष्ठा pnp_dev *pnp_dev, pm_message_t state)
अणु
	काष्ठा ene_device *dev = pnp_get_drvdata(pnp_dev);
	bool wake = device_may_wakeup(&dev->pnp_dev->dev);

	अगर (!wake && dev->rx_enabled)
		ene_rx_disable_hw(dev);

	ene_enable_wake(dev, wake);
	वापस 0;
पूर्ण

अटल पूर्णांक ene_resume(काष्ठा pnp_dev *pnp_dev)
अणु
	काष्ठा ene_device *dev = pnp_get_drvdata(pnp_dev);
	ene_setup_hw_settings(dev);

	अगर (dev->rx_enabled)
		ene_rx_enable(dev);

	ene_enable_wake(dev, false);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल व्योम ene_shutकरोwn(काष्ठा pnp_dev *pnp_dev)
अणु
	काष्ठा ene_device *dev = pnp_get_drvdata(pnp_dev);
	ene_enable_wake(dev, true);
पूर्ण

अटल स्थिर काष्ठा pnp_device_id ene_ids[] = अणु
	अणु.id = "ENE0100",पूर्ण,
	अणु.id = "ENE0200",पूर्ण,
	अणु.id = "ENE0201",पूर्ण,
	अणु.id = "ENE0202",पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा pnp_driver ene_driver = अणु
	.name = ENE_DRIVER_NAME,
	.id_table = ene_ids,
	.flags = PNP_DRIVER_RES_DO_NOT_CHANGE,

	.probe = ene_probe,
	.हटाओ = ene_हटाओ,
#अगर_घोषित CONFIG_PM
	.suspend = ene_suspend,
	.resume = ene_resume,
#पूर्ण_अगर
	.shutकरोwn = ene_shutकरोwn,
पूर्ण;

module_param(sample_period, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(sample_period, "Hardware sample period (50 us default)");

module_param(learning_mode_क्रमce, bool, S_IRUGO);
MODULE_PARM_DESC(learning_mode_क्रमce, "Enable learning mode by default");

module_param(debug, पूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(debug, "Debug level");

module_param(txsim, bool, S_IRUGO);
MODULE_PARM_DESC(txsim,
	"Simulate TX features on unsupported hardware (dangerous)");

MODULE_DEVICE_TABLE(pnp, ene_ids);
MODULE_DESCRIPTION
	("Infrared input driver for KB3926B/C/D/E/F (aka ENE0100/ENE0200/ENE0201/ENE0202) CIR port");

MODULE_AUTHOR("Maxim Levitsky");
MODULE_LICENSE("GPL");

module_pnp_driver(ene_driver);
