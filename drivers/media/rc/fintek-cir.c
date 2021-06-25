<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम Feature Integration Technology Inc. (aka Fपूर्णांकek) LPC CIR
 *
 * Copyright (C) 2011 Jarod Wilson <jarod@redhat.com>
 *
 * Special thanks to Fपूर्णांकek क्रम providing hardware and spec sheets.
 * This driver is based upon the nuvoton, ite and ene drivers क्रम
 * similar hardware.
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

#समावेश "fintek-cir.h"

/* ग_लिखो val to config reg */
अटल अंतरभूत व्योम fपूर्णांकek_cr_ग_लिखो(काष्ठा fपूर्णांकek_dev *fपूर्णांकek, u8 val, u8 reg)
अणु
	fit_dbg("%s: reg 0x%02x, val 0x%02x  (ip/dp: %02x/%02x)",
		__func__, reg, val, fपूर्णांकek->cr_ip, fपूर्णांकek->cr_dp);
	outb(reg, fपूर्णांकek->cr_ip);
	outb(val, fपूर्णांकek->cr_dp);
पूर्ण

/* पढ़ो val from config reg */
अटल अंतरभूत u8 fपूर्णांकek_cr_पढ़ो(काष्ठा fपूर्णांकek_dev *fपूर्णांकek, u8 reg)
अणु
	u8 val;

	outb(reg, fपूर्णांकek->cr_ip);
	val = inb(fपूर्णांकek->cr_dp);

	fit_dbg("%s: reg 0x%02x, val 0x%02x  (ip/dp: %02x/%02x)",
		__func__, reg, val, fपूर्णांकek->cr_ip, fपूर्णांकek->cr_dp);
	वापस val;
पूर्ण

/* update config रेजिस्टर bit without changing other bits */
अटल अंतरभूत व्योम fपूर्णांकek_set_reg_bit(काष्ठा fपूर्णांकek_dev *fपूर्णांकek, u8 val, u8 reg)
अणु
	u8 पंचांगp = fपूर्णांकek_cr_पढ़ो(fपूर्णांकek, reg) | val;
	fपूर्णांकek_cr_ग_लिखो(fपूर्णांकek, पंचांगp, reg);
पूर्ण

/* enter config mode */
अटल अंतरभूत व्योम fपूर्णांकek_config_mode_enable(काष्ठा fपूर्णांकek_dev *fपूर्णांकek)
अणु
	/* Enabling Config Mode explicitly requires writing 2x */
	outb(CONFIG_REG_ENABLE, fपूर्णांकek->cr_ip);
	outb(CONFIG_REG_ENABLE, fपूर्णांकek->cr_ip);
पूर्ण

/* निकास config mode */
अटल अंतरभूत व्योम fपूर्णांकek_config_mode_disable(काष्ठा fपूर्णांकek_dev *fपूर्णांकek)
अणु
	outb(CONFIG_REG_DISABLE, fपूर्णांकek->cr_ip);
पूर्ण

/*
 * When you want to address a specअगरic logical device, ग_लिखो its logical
 * device number to GCR_LOGICAL_DEV_NO
 */
अटल अंतरभूत व्योम fपूर्णांकek_select_logical_dev(काष्ठा fपूर्णांकek_dev *fपूर्णांकek, u8 ldev)
अणु
	fपूर्णांकek_cr_ग_लिखो(fपूर्णांकek, ldev, GCR_LOGICAL_DEV_NO);
पूर्ण

/* ग_लिखो val to cir config रेजिस्टर */
अटल अंतरभूत व्योम fपूर्णांकek_cir_reg_ग_लिखो(काष्ठा fपूर्णांकek_dev *fपूर्णांकek, u8 val, u8 offset)
अणु
	outb(val, fपूर्णांकek->cir_addr + offset);
पूर्ण

/* पढ़ो val from cir config रेजिस्टर */
अटल u8 fपूर्णांकek_cir_reg_पढ़ो(काष्ठा fपूर्णांकek_dev *fपूर्णांकek, u8 offset)
अणु
	वापस inb(fपूर्णांकek->cir_addr + offset);
पूर्ण

/* dump current cir रेजिस्टर contents */
अटल व्योम cir_dump_regs(काष्ठा fपूर्णांकek_dev *fपूर्णांकek)
अणु
	fपूर्णांकek_config_mode_enable(fपूर्णांकek);
	fपूर्णांकek_select_logical_dev(fपूर्णांकek, fपूर्णांकek->logical_dev_cir);

	pr_info("%s: Dump CIR logical device registers:\n", FINTEK_DRIVER_NAME);
	pr_info(" * CR CIR BASE ADDR: 0x%x\n",
		(fपूर्णांकek_cr_पढ़ो(fपूर्णांकek, CIR_CR_BASE_ADDR_HI) << 8) |
		fपूर्णांकek_cr_पढ़ो(fपूर्णांकek, CIR_CR_BASE_ADDR_LO));
	pr_info(" * CR CIR IRQ NUM:   0x%x\n",
		fपूर्णांकek_cr_पढ़ो(fपूर्णांकek, CIR_CR_IRQ_SEL));

	fपूर्णांकek_config_mode_disable(fपूर्णांकek);

	pr_info("%s: Dump CIR registers:\n", FINTEK_DRIVER_NAME);
	pr_info(" * STATUS:     0x%x\n",
		fपूर्णांकek_cir_reg_पढ़ो(fपूर्णांकek, CIR_STATUS));
	pr_info(" * CONTROL:    0x%x\n",
		fपूर्णांकek_cir_reg_पढ़ो(fपूर्णांकek, CIR_CONTROL));
	pr_info(" * RX_DATA:    0x%x\n",
		fपूर्णांकek_cir_reg_पढ़ो(fपूर्णांकek, CIR_RX_DATA));
	pr_info(" * TX_CONTROL: 0x%x\n",
		fपूर्णांकek_cir_reg_पढ़ो(fपूर्णांकek, CIR_TX_CONTROL));
	pr_info(" * TX_DATA:    0x%x\n",
		fपूर्णांकek_cir_reg_पढ़ो(fपूर्णांकek, CIR_TX_DATA));
पूर्ण

/* detect hardware features */
अटल पूर्णांक fपूर्णांकek_hw_detect(काष्ठा fपूर्णांकek_dev *fपूर्णांकek)
अणु
	अचिन्हित दीर्घ flags;
	u8 chip_major, chip_minor;
	u8 venकरोr_major, venकरोr_minor;
	u8 portsel, ir_class;
	u16 venकरोr, chip;

	fपूर्णांकek_config_mode_enable(fपूर्णांकek);

	/* Check अगर we're using config port 0x4e or 0x2e */
	portsel = fपूर्णांकek_cr_पढ़ो(fपूर्णांकek, GCR_CONFIG_PORT_SEL);
	अगर (portsel == 0xff) अणु
		fit_pr(KERN_INFO, "first portsel read was bunk, trying alt");
		fपूर्णांकek_config_mode_disable(fपूर्णांकek);
		fपूर्णांकek->cr_ip = CR_INDEX_PORT2;
		fपूर्णांकek->cr_dp = CR_DATA_PORT2;
		fपूर्णांकek_config_mode_enable(fपूर्णांकek);
		portsel = fपूर्णांकek_cr_पढ़ो(fपूर्णांकek, GCR_CONFIG_PORT_SEL);
	पूर्ण
	fit_dbg("portsel reg: 0x%02x", portsel);

	ir_class = fपूर्णांकek_cir_reg_पढ़ो(fपूर्णांकek, CIR_CR_CLASS);
	fit_dbg("ir_class reg: 0x%02x", ir_class);

	चयन (ir_class) अणु
	हाल CLASS_RX_2TX:
	हाल CLASS_RX_1TX:
		fपूर्णांकek->hw_tx_capable = true;
		अवरोध;
	हाल CLASS_RX_ONLY:
	शेष:
		fपूर्णांकek->hw_tx_capable = false;
		अवरोध;
	पूर्ण

	chip_major = fपूर्णांकek_cr_पढ़ो(fपूर्णांकek, GCR_CHIP_ID_HI);
	chip_minor = fपूर्णांकek_cr_पढ़ो(fपूर्णांकek, GCR_CHIP_ID_LO);
	chip  = chip_major << 8 | chip_minor;

	venकरोr_major = fपूर्णांकek_cr_पढ़ो(fपूर्णांकek, GCR_VENDOR_ID_HI);
	venकरोr_minor = fपूर्णांकek_cr_पढ़ो(fपूर्णांकek, GCR_VENDOR_ID_LO);
	venकरोr = venकरोr_major << 8 | venकरोr_minor;

	अगर (venकरोr != VENDOR_ID_FINTEK)
		fit_pr(KERN_WARNING, "Unknown vendor ID: 0x%04x", venकरोr);
	अन्यथा
		fit_dbg("Read Fintek vendor ID from chip");

	fपूर्णांकek_config_mode_disable(fपूर्णांकek);

	spin_lock_irqsave(&fपूर्णांकek->fपूर्णांकek_lock, flags);
	fपूर्णांकek->chip_major  = chip_major;
	fपूर्णांकek->chip_minor  = chip_minor;
	fपूर्णांकek->chip_venकरोr = venकरोr;

	/*
	 * Newer reviews of this chipset uses port 8 instead of 5
	 */
	अगर ((chip != 0x0408) && (chip != 0x0804))
		fपूर्णांकek->logical_dev_cir = LOGICAL_DEV_CIR_REV2;
	अन्यथा
		fपूर्णांकek->logical_dev_cir = LOGICAL_DEV_CIR_REV1;

	spin_unlock_irqrestore(&fपूर्णांकek->fपूर्णांकek_lock, flags);

	वापस 0;
पूर्ण

अटल व्योम fपूर्णांकek_cir_ldev_init(काष्ठा fपूर्णांकek_dev *fपूर्णांकek)
अणु
	/* Select CIR logical device and enable */
	fपूर्णांकek_select_logical_dev(fपूर्णांकek, fपूर्णांकek->logical_dev_cir);
	fपूर्णांकek_cr_ग_लिखो(fपूर्णांकek, LOGICAL_DEV_ENABLE, CIR_CR_DEV_EN);

	/* Write allocated CIR address and IRQ inक्रमmation to hardware */
	fपूर्णांकek_cr_ग_लिखो(fपूर्णांकek, fपूर्णांकek->cir_addr >> 8, CIR_CR_BASE_ADDR_HI);
	fपूर्णांकek_cr_ग_लिखो(fपूर्णांकek, fपूर्णांकek->cir_addr & 0xff, CIR_CR_BASE_ADDR_LO);

	fपूर्णांकek_cr_ग_लिखो(fपूर्णांकek, fपूर्णांकek->cir_irq, CIR_CR_IRQ_SEL);

	fit_dbg("CIR initialized, base io address: 0x%lx, irq: %d (len: %d)",
		fपूर्णांकek->cir_addr, fपूर्णांकek->cir_irq, fपूर्णांकek->cir_port_len);
पूर्ण

/* enable CIR पूर्णांकerrupts */
अटल व्योम fपूर्णांकek_enable_cir_irq(काष्ठा fपूर्णांकek_dev *fपूर्णांकek)
अणु
	fपूर्णांकek_cir_reg_ग_लिखो(fपूर्णांकek, CIR_STATUS_IRQ_EN, CIR_STATUS);
पूर्ण

अटल व्योम fपूर्णांकek_cir_regs_init(काष्ठा fपूर्णांकek_dev *fपूर्णांकek)
अणु
	/* clear any and all stray पूर्णांकerrupts */
	fपूर्णांकek_cir_reg_ग_लिखो(fपूर्णांकek, CIR_STATUS_IRQ_MASK, CIR_STATUS);

	/* and finally, enable पूर्णांकerrupts */
	fपूर्णांकek_enable_cir_irq(fपूर्णांकek);
पूर्ण

अटल व्योम fपूर्णांकek_enable_wake(काष्ठा fपूर्णांकek_dev *fपूर्णांकek)
अणु
	fपूर्णांकek_config_mode_enable(fपूर्णांकek);
	fपूर्णांकek_select_logical_dev(fपूर्णांकek, LOGICAL_DEV_ACPI);

	/* Allow CIR PME's to wake प्रणाली */
	fपूर्णांकek_set_reg_bit(fपूर्णांकek, ACPI_WAKE_EN_CIR_BIT, LDEV_ACPI_WAKE_EN_REG);
	/* Enable CIR PME's */
	fपूर्णांकek_set_reg_bit(fपूर्णांकek, ACPI_PME_CIR_BIT, LDEV_ACPI_PME_EN_REG);
	/* Clear CIR PME status रेजिस्टर */
	fपूर्णांकek_set_reg_bit(fपूर्णांकek, ACPI_PME_CIR_BIT, LDEV_ACPI_PME_CLR_REG);
	/* Save state */
	fपूर्णांकek_set_reg_bit(fपूर्णांकek, ACPI_STATE_CIR_BIT, LDEV_ACPI_STATE_REG);

	fपूर्णांकek_config_mode_disable(fपूर्णांकek);
पूर्ण

अटल पूर्णांक fपूर्णांकek_cmdsize(u8 cmd, u8 subcmd)
अणु
	पूर्णांक datasize = 0;

	चयन (cmd) अणु
	हाल BUF_COMMAND_शून्य:
		अगर (subcmd == BUF_HW_CMD_HEADER)
			datasize = 1;
		अवरोध;
	हाल BUF_HW_CMD_HEADER:
		अगर (subcmd == BUF_CMD_G_REVISION)
			datasize = 2;
		अवरोध;
	हाल BUF_COMMAND_HEADER:
		चयन (subcmd) अणु
		हाल BUF_CMD_S_CARRIER:
		हाल BUF_CMD_S_TIMEOUT:
		हाल BUF_RSP_PULSE_COUNT:
			datasize = 2;
			अवरोध;
		हाल BUF_CMD_SIG_END:
		हाल BUF_CMD_S_TXMASK:
		हाल BUF_CMD_S_RXSENSOR:
			datasize = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस datasize;
पूर्ण

/* process ir data stored in driver buffer */
अटल व्योम fपूर्णांकek_process_rx_ir_data(काष्ठा fपूर्णांकek_dev *fपूर्णांकek)
अणु
	काष्ठा ir_raw_event rawir = अणुपूर्ण;
	u8 sample;
	bool event = false;
	पूर्णांक i;

	क्रम (i = 0; i < fपूर्णांकek->pkts; i++) अणु
		sample = fपूर्णांकek->buf[i];
		चयन (fपूर्णांकek->parser_state) अणु
		हाल CMD_HEADER:
			fपूर्णांकek->cmd = sample;
			अगर ((fपूर्णांकek->cmd == BUF_COMMAND_HEADER) ||
			    ((fपूर्णांकek->cmd & BUF_COMMAND_MASK) !=
			     BUF_PULSE_BIT)) अणु
				fपूर्णांकek->parser_state = SUBCMD;
				जारी;
			पूर्ण
			fपूर्णांकek->rem = (fपूर्णांकek->cmd & BUF_LEN_MASK);
			fit_dbg("%s: rem: 0x%02x", __func__, fपूर्णांकek->rem);
			अगर (fपूर्णांकek->rem)
				fपूर्णांकek->parser_state = PARSE_IRDATA;
			अन्यथा
				ir_raw_event_reset(fपूर्णांकek->rdev);
			अवरोध;
		हाल SUBCMD:
			fपूर्णांकek->rem = fपूर्णांकek_cmdsize(fपूर्णांकek->cmd, sample);
			fपूर्णांकek->parser_state = CMD_DATA;
			अवरोध;
		हाल CMD_DATA:
			fपूर्णांकek->rem--;
			अवरोध;
		हाल PARSE_IRDATA:
			fपूर्णांकek->rem--;
			rawir.pulse = ((sample & BUF_PULSE_BIT) != 0);
			rawir.duration = (sample & BUF_SAMPLE_MASK)
					  * CIR_SAMPLE_PERIOD;

			fit_dbg("Storing %s with duration %d",
				rawir.pulse ? "pulse" : "space",
				rawir.duration);
			अगर (ir_raw_event_store_with_filter(fपूर्णांकek->rdev,
									&rawir))
				event = true;
			अवरोध;
		पूर्ण

		अगर ((fपूर्णांकek->parser_state != CMD_HEADER) && !fपूर्णांकek->rem)
			fपूर्णांकek->parser_state = CMD_HEADER;
	पूर्ण

	fपूर्णांकek->pkts = 0;

	अगर (event) अणु
		fit_dbg("Calling ir_raw_event_handle");
		ir_raw_event_handle(fपूर्णांकek->rdev);
	पूर्ण
पूर्ण

/* copy data from hardware rx रेजिस्टर पूर्णांकo driver buffer */
अटल व्योम fपूर्णांकek_get_rx_ir_data(काष्ठा fपूर्णांकek_dev *fपूर्णांकek, u8 rx_irqs)
अणु
	अचिन्हित दीर्घ flags;
	u8 sample, status;

	spin_lock_irqsave(&fपूर्णांकek->fपूर्णांकek_lock, flags);

	/*
	 * We must पढ़ो data from CIR_RX_DATA until the hardware IR buffer
	 * is empty and clears the RX_TIMEOUT and/or RX_RECEIVE flags in
	 * the CIR_STATUS रेजिस्टर
	 */
	करो अणु
		sample = fपूर्णांकek_cir_reg_पढ़ो(fपूर्णांकek, CIR_RX_DATA);
		fit_dbg("%s: sample: 0x%02x", __func__, sample);

		fपूर्णांकek->buf[fपूर्णांकek->pkts] = sample;
		fपूर्णांकek->pkts++;

		status = fपूर्णांकek_cir_reg_पढ़ो(fपूर्णांकek, CIR_STATUS);
		अगर (!(status & CIR_STATUS_IRQ_EN))
			अवरोध;
	पूर्ण जबतक (status & rx_irqs);

	fपूर्णांकek_process_rx_ir_data(fपूर्णांकek);

	spin_unlock_irqrestore(&fपूर्णांकek->fपूर्णांकek_lock, flags);
पूर्ण

अटल व्योम fपूर्णांकek_cir_log_irqs(u8 status)
अणु
	fit_pr(KERN_INFO, "IRQ 0x%02x:%s%s%s%s%s", status,
		status & CIR_STATUS_IRQ_EN	? " IRQEN"	: "",
		status & CIR_STATUS_TX_FINISH	? " TXF"	: "",
		status & CIR_STATUS_TX_UNDERRUN	? " TXU"	: "",
		status & CIR_STATUS_RX_TIMEOUT	? " RXTO"	: "",
		status & CIR_STATUS_RX_RECEIVE	? " RXOK"	: "");
पूर्ण

/* पूर्णांकerrupt service routine क्रम incoming and outgoing CIR data */
अटल irqवापस_t fपूर्णांकek_cir_isr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा fपूर्णांकek_dev *fपूर्णांकek = data;
	u8 status, rx_irqs;

	fit_dbg_verbose("%s firing", __func__);

	fपूर्णांकek_config_mode_enable(fपूर्णांकek);
	fपूर्णांकek_select_logical_dev(fपूर्णांकek, fपूर्णांकek->logical_dev_cir);
	fपूर्णांकek_config_mode_disable(fपूर्णांकek);

	/*
	 * Get IR Status रेजिस्टर contents. Write 1 to ack/clear
	 *
	 * bit: reg name    - description
	 *   3: TX_FINISH   - TX is finished
	 *   2: TX_UNDERRUN - TX underrun
	 *   1: RX_TIMEOUT  - RX data समयout
	 *   0: RX_RECEIVE  - RX data received
	 */
	status = fपूर्णांकek_cir_reg_पढ़ो(fपूर्णांकek, CIR_STATUS);
	अगर (!(status & CIR_STATUS_IRQ_MASK) || status == 0xff) अणु
		fit_dbg_verbose("%s exiting, IRSTS 0x%02x", __func__, status);
		fपूर्णांकek_cir_reg_ग_लिखो(fपूर्णांकek, CIR_STATUS_IRQ_MASK, CIR_STATUS);
		वापस IRQ_RETVAL(IRQ_NONE);
	पूर्ण

	अगर (debug)
		fपूर्णांकek_cir_log_irqs(status);

	rx_irqs = status & (CIR_STATUS_RX_RECEIVE | CIR_STATUS_RX_TIMEOUT);
	अगर (rx_irqs)
		fपूर्णांकek_get_rx_ir_data(fपूर्णांकek, rx_irqs);

	/* ack/clear all irq flags we've got */
	fपूर्णांकek_cir_reg_ग_लिखो(fपूर्णांकek, status, CIR_STATUS);

	fit_dbg_verbose("%s done", __func__);
	वापस IRQ_RETVAL(IRQ_HANDLED);
पूर्ण

अटल व्योम fपूर्णांकek_enable_cir(काष्ठा fपूर्णांकek_dev *fपूर्णांकek)
अणु
	/* set IRQ enabled */
	fपूर्णांकek_cir_reg_ग_लिखो(fपूर्णांकek, CIR_STATUS_IRQ_EN, CIR_STATUS);

	fपूर्णांकek_config_mode_enable(fपूर्णांकek);

	/* enable the CIR logical device */
	fपूर्णांकek_select_logical_dev(fपूर्णांकek, fपूर्णांकek->logical_dev_cir);
	fपूर्णांकek_cr_ग_लिखो(fपूर्णांकek, LOGICAL_DEV_ENABLE, CIR_CR_DEV_EN);

	fपूर्णांकek_config_mode_disable(fपूर्णांकek);

	/* clear all pending पूर्णांकerrupts */
	fपूर्णांकek_cir_reg_ग_लिखो(fपूर्णांकek, CIR_STATUS_IRQ_MASK, CIR_STATUS);

	/* enable पूर्णांकerrupts */
	fपूर्णांकek_enable_cir_irq(fपूर्णांकek);
पूर्ण

अटल व्योम fपूर्णांकek_disable_cir(काष्ठा fपूर्णांकek_dev *fपूर्णांकek)
अणु
	fपूर्णांकek_config_mode_enable(fपूर्णांकek);

	/* disable the CIR logical device */
	fपूर्णांकek_select_logical_dev(fपूर्णांकek, fपूर्णांकek->logical_dev_cir);
	fपूर्णांकek_cr_ग_लिखो(fपूर्णांकek, LOGICAL_DEV_DISABLE, CIR_CR_DEV_EN);

	fपूर्णांकek_config_mode_disable(fपूर्णांकek);
पूर्ण

अटल पूर्णांक fपूर्णांकek_खोलो(काष्ठा rc_dev *dev)
अणु
	काष्ठा fपूर्णांकek_dev *fपूर्णांकek = dev->priv;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&fपूर्णांकek->fपूर्णांकek_lock, flags);
	fपूर्णांकek_enable_cir(fपूर्णांकek);
	spin_unlock_irqrestore(&fपूर्णांकek->fपूर्णांकek_lock, flags);

	वापस 0;
पूर्ण

अटल व्योम fपूर्णांकek_बंद(काष्ठा rc_dev *dev)
अणु
	काष्ठा fपूर्णांकek_dev *fपूर्णांकek = dev->priv;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&fपूर्णांकek->fपूर्णांकek_lock, flags);
	fपूर्णांकek_disable_cir(fपूर्णांकek);
	spin_unlock_irqrestore(&fपूर्णांकek->fपूर्णांकek_lock, flags);
पूर्ण

/* Allocate memory, probe hardware, and initialize everything */
अटल पूर्णांक fपूर्णांकek_probe(काष्ठा pnp_dev *pdev, स्थिर काष्ठा pnp_device_id *dev_id)
अणु
	काष्ठा fपूर्णांकek_dev *fपूर्णांकek;
	काष्ठा rc_dev *rdev;
	पूर्णांक ret = -ENOMEM;

	fपूर्णांकek = kzalloc(माप(काष्ठा fपूर्णांकek_dev), GFP_KERNEL);
	अगर (!fपूर्णांकek)
		वापस ret;

	/* input device क्रम IR remote (and tx) */
	rdev = rc_allocate_device(RC_DRIVER_IR_RAW);
	अगर (!rdev)
		जाओ निकास_मुक्त_dev_rdev;

	ret = -ENODEV;
	/* validate pnp resources */
	अगर (!pnp_port_valid(pdev, 0)) अणु
		dev_err(&pdev->dev, "IR PNP Port not valid!\n");
		जाओ निकास_मुक्त_dev_rdev;
	पूर्ण

	अगर (!pnp_irq_valid(pdev, 0)) अणु
		dev_err(&pdev->dev, "IR PNP IRQ not valid!\n");
		जाओ निकास_मुक्त_dev_rdev;
	पूर्ण

	fपूर्णांकek->cir_addr = pnp_port_start(pdev, 0);
	fपूर्णांकek->cir_irq  = pnp_irq(pdev, 0);
	fपूर्णांकek->cir_port_len = pnp_port_len(pdev, 0);

	fपूर्णांकek->cr_ip = CR_INDEX_PORT;
	fपूर्णांकek->cr_dp = CR_DATA_PORT;

	spin_lock_init(&fपूर्णांकek->fपूर्णांकek_lock);

	pnp_set_drvdata(pdev, fपूर्णांकek);
	fपूर्णांकek->pdev = pdev;

	ret = fपूर्णांकek_hw_detect(fपूर्णांकek);
	अगर (ret)
		जाओ निकास_मुक्त_dev_rdev;

	/* Initialize CIR & CIR Wake Logical Devices */
	fपूर्णांकek_config_mode_enable(fपूर्णांकek);
	fपूर्णांकek_cir_ldev_init(fपूर्णांकek);
	fपूर्णांकek_config_mode_disable(fपूर्णांकek);

	/* Initialize CIR & CIR Wake Config Registers */
	fपूर्णांकek_cir_regs_init(fपूर्णांकek);

	/* Set up the rc device */
	rdev->priv = fपूर्णांकek;
	rdev->allowed_protocols = RC_PROTO_BIT_ALL_IR_DECODER;
	rdev->खोलो = fपूर्णांकek_खोलो;
	rdev->बंद = fपूर्णांकek_बंद;
	rdev->device_name = FINTEK_DESCRIPTION;
	rdev->input_phys = "fintek/cir0";
	rdev->input_id.bustype = BUS_HOST;
	rdev->input_id.venकरोr = VENDOR_ID_FINTEK;
	rdev->input_id.product = fपूर्णांकek->chip_major;
	rdev->input_id.version = fपूर्णांकek->chip_minor;
	rdev->dev.parent = &pdev->dev;
	rdev->driver_name = FINTEK_DRIVER_NAME;
	rdev->map_name = RC_MAP_RC6_MCE;
	rdev->समयout = 1000;
	/* rx resolution is hardwired to 50us aपंचांग, 1, 25, 100 also possible */
	rdev->rx_resolution = CIR_SAMPLE_PERIOD;

	fपूर्णांकek->rdev = rdev;

	ret = -EBUSY;
	/* now claim resources */
	अगर (!request_region(fपूर्णांकek->cir_addr,
			    fपूर्णांकek->cir_port_len, FINTEK_DRIVER_NAME))
		जाओ निकास_मुक्त_dev_rdev;

	अगर (request_irq(fपूर्णांकek->cir_irq, fपूर्णांकek_cir_isr, IRQF_SHARED,
			FINTEK_DRIVER_NAME, (व्योम *)fपूर्णांकek))
		जाओ निकास_मुक्त_cir_addr;

	ret = rc_रेजिस्टर_device(rdev);
	अगर (ret)
		जाओ निकास_मुक्त_irq;

	device_init_wakeup(&pdev->dev, true);

	fit_pr(KERN_NOTICE, "driver has been successfully loaded\n");
	अगर (debug)
		cir_dump_regs(fपूर्णांकek);

	वापस 0;

निकास_मुक्त_irq:
	मुक्त_irq(fपूर्णांकek->cir_irq, fपूर्णांकek);
निकास_मुक्त_cir_addr:
	release_region(fपूर्णांकek->cir_addr, fपूर्णांकek->cir_port_len);
निकास_मुक्त_dev_rdev:
	rc_मुक्त_device(rdev);
	kमुक्त(fपूर्णांकek);

	वापस ret;
पूर्ण

अटल व्योम fपूर्णांकek_हटाओ(काष्ठा pnp_dev *pdev)
अणु
	काष्ठा fपूर्णांकek_dev *fपूर्णांकek = pnp_get_drvdata(pdev);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&fपूर्णांकek->fपूर्णांकek_lock, flags);
	/* disable CIR */
	fपूर्णांकek_disable_cir(fपूर्णांकek);
	fपूर्णांकek_cir_reg_ग_लिखो(fपूर्णांकek, CIR_STATUS_IRQ_MASK, CIR_STATUS);
	/* enable CIR Wake (क्रम IR घातer-on) */
	fपूर्णांकek_enable_wake(fपूर्णांकek);
	spin_unlock_irqrestore(&fपूर्णांकek->fपूर्णांकek_lock, flags);

	/* मुक्त resources */
	मुक्त_irq(fपूर्णांकek->cir_irq, fपूर्णांकek);
	release_region(fपूर्णांकek->cir_addr, fपूर्णांकek->cir_port_len);

	rc_unरेजिस्टर_device(fपूर्णांकek->rdev);

	kमुक्त(fपूर्णांकek);
पूर्ण

अटल पूर्णांक fपूर्णांकek_suspend(काष्ठा pnp_dev *pdev, pm_message_t state)
अणु
	काष्ठा fपूर्णांकek_dev *fपूर्णांकek = pnp_get_drvdata(pdev);
	अचिन्हित दीर्घ flags;

	fit_dbg("%s called", __func__);

	spin_lock_irqsave(&fपूर्णांकek->fपूर्णांकek_lock, flags);

	/* disable all CIR पूर्णांकerrupts */
	fपूर्णांकek_cir_reg_ग_लिखो(fपूर्णांकek, CIR_STATUS_IRQ_MASK, CIR_STATUS);

	spin_unlock_irqrestore(&fपूर्णांकek->fपूर्णांकek_lock, flags);

	fपूर्णांकek_config_mode_enable(fपूर्णांकek);

	/* disable cir logical dev */
	fपूर्णांकek_select_logical_dev(fपूर्णांकek, fपूर्णांकek->logical_dev_cir);
	fपूर्णांकek_cr_ग_लिखो(fपूर्णांकek, LOGICAL_DEV_DISABLE, CIR_CR_DEV_EN);

	fपूर्णांकek_config_mode_disable(fपूर्णांकek);

	/* make sure wake is enabled */
	fपूर्णांकek_enable_wake(fपूर्णांकek);

	वापस 0;
पूर्ण

अटल पूर्णांक fपूर्णांकek_resume(काष्ठा pnp_dev *pdev)
अणु
	काष्ठा fपूर्णांकek_dev *fपूर्णांकek = pnp_get_drvdata(pdev);

	fit_dbg("%s called", __func__);

	/* खोलो पूर्णांकerrupt */
	fपूर्णांकek_enable_cir_irq(fपूर्णांकek);

	/* Enable CIR logical device */
	fपूर्णांकek_config_mode_enable(fपूर्णांकek);
	fपूर्णांकek_select_logical_dev(fपूर्णांकek, fपूर्णांकek->logical_dev_cir);
	fपूर्णांकek_cr_ग_लिखो(fपूर्णांकek, LOGICAL_DEV_ENABLE, CIR_CR_DEV_EN);

	fपूर्णांकek_config_mode_disable(fपूर्णांकek);

	fपूर्णांकek_cir_regs_init(fपूर्णांकek);

	वापस 0;
पूर्ण

अटल व्योम fपूर्णांकek_shutकरोwn(काष्ठा pnp_dev *pdev)
अणु
	काष्ठा fपूर्णांकek_dev *fपूर्णांकek = pnp_get_drvdata(pdev);
	fपूर्णांकek_enable_wake(fपूर्णांकek);
पूर्ण

अटल स्थिर काष्ठा pnp_device_id fपूर्णांकek_ids[] = अणु
	अणु "FIT0002", 0 पूर्ण,   /* CIR */
	अणु "", 0 पूर्ण,
पूर्ण;

अटल काष्ठा pnp_driver fपूर्णांकek_driver = अणु
	.name		= FINTEK_DRIVER_NAME,
	.id_table	= fपूर्णांकek_ids,
	.flags		= PNP_DRIVER_RES_DO_NOT_CHANGE,
	.probe		= fपूर्णांकek_probe,
	.हटाओ		= fपूर्णांकek_हटाओ,
	.suspend	= fपूर्णांकek_suspend,
	.resume		= fपूर्णांकek_resume,
	.shutकरोwn	= fपूर्णांकek_shutकरोwn,
पूर्ण;

module_param(debug, पूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(debug, "Enable debugging output");

MODULE_DEVICE_TABLE(pnp, fपूर्णांकek_ids);
MODULE_DESCRIPTION(FINTEK_DESCRIPTION " driver");

MODULE_AUTHOR("Jarod Wilson <jarod@redhat.com>");
MODULE_LICENSE("GPL");

module_pnp_driver(fपूर्णांकek_driver);
