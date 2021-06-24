<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Driver क्रम Feature Integration Technology Inc. (aka Fपूर्णांकek) LPC CIR
 *
 * Copyright (C) 2011 Jarod Wilson <jarod@redhat.com>
 *
 * Special thanks to Fपूर्णांकek क्रम providing hardware and spec sheets.
 * This driver is based upon the nuvoton, ite and ene drivers क्रम
 * similar hardware.
 */

#समावेश <linux/spinlock.h>
#समावेश <linux/ioctl.h>

/* platक्रमm driver name to रेजिस्टर */
#घोषणा FINTEK_DRIVER_NAME	"fintek-cir"
#घोषणा FINTEK_DESCRIPTION	"Fintek LPC SuperIO Consumer IR Transceiver"
#घोषणा VENDOR_ID_FINTEK	0x1934


/* debugging module parameter */
अटल पूर्णांक debug;

#घोषणा fit_pr(level, text, ...) \
	prपूर्णांकk(level KBUILD_MODNAME ": " text, ## __VA_ARGS__)

#घोषणा fit_dbg(text, ...) \
	अगर (debug) \
		prपूर्णांकk(KERN_DEBUG \
			KBUILD_MODNAME ": " text "\n" , ## __VA_ARGS__)

#घोषणा fit_dbg_verbose(text, ...) \
	अगर (debug > 1) \
		prपूर्णांकk(KERN_DEBUG \
			KBUILD_MODNAME ": " text "\n" , ## __VA_ARGS__)

#घोषणा fit_dbg_wake(text, ...) \
	अगर (debug > 2) \
		prपूर्णांकk(KERN_DEBUG \
			KBUILD_MODNAME ": " text "\n" , ## __VA_ARGS__)


#घोषणा TX_BUF_LEN 256
#घोषणा RX_BUF_LEN 32

काष्ठा fपूर्णांकek_dev अणु
	काष्ठा pnp_dev *pdev;
	काष्ठा rc_dev *rdev;

	spinlock_t fपूर्णांकek_lock;

	/* क्रम rx */
	u8 buf[RX_BUF_LEN];
	अचिन्हित पूर्णांक pkts;

	काष्ठा अणु
		spinlock_t lock;
		u8 buf[TX_BUF_LEN];
		अचिन्हित पूर्णांक buf_count;
		अचिन्हित पूर्णांक cur_buf_num;
		रुको_queue_head_t queue;
	पूर्ण tx;

	/* Config रेजिस्टर index/data port pair */
	u32 cr_ip;
	u32 cr_dp;

	/* hardware I/O settings */
	अचिन्हित दीर्घ cir_addr;
	पूर्णांक cir_irq;
	पूर्णांक cir_port_len;

	/* hardware id */
	u8 chip_major;
	u8 chip_minor;
	u16 chip_venकरोr;
	u8 logical_dev_cir;

	/* hardware features */
	bool hw_learning_capable;
	bool hw_tx_capable;

	/* rx settings */
	bool learning_enabled;
	bool carrier_detect_enabled;

	क्रमागत अणु
		CMD_HEADER = 0,
		SUBCMD,
		CMD_DATA,
		PARSE_IRDATA,
	पूर्ण parser_state;

	u8 cmd, rem;

	/* carrier period = 1 / frequency */
	u32 carrier;
पूर्ण;

/* buffer packet स्थिरants, largely identical to mceusb.c */
#घोषणा BUF_PULSE_BIT		0x80
#घोषणा BUF_LEN_MASK		0x1f
#घोषणा BUF_SAMPLE_MASK		0x7f

#घोषणा BUF_COMMAND_HEADER	0x9f
#घोषणा BUF_COMMAND_MASK	0xe0
#घोषणा BUF_COMMAND_शून्य	0x00
#घोषणा BUF_HW_CMD_HEADER	0xff
#घोषणा BUF_CMD_G_REVISION	0x0b
#घोषणा BUF_CMD_S_CARRIER	0x06
#घोषणा BUF_CMD_S_TIMEOUT	0x0c
#घोषणा BUF_CMD_SIG_END		0x01
#घोषणा BUF_CMD_S_TXMASK	0x08
#घोषणा BUF_CMD_S_RXSENSOR	0x14
#घोषणा BUF_RSP_PULSE_COUNT	0x15

#घोषणा CIR_SAMPLE_PERIOD	50

/*
 * Configuration Register:
 *  Index Port
 *  Data Port
 */
#घोषणा CR_INDEX_PORT		0x2e
#घोषणा CR_DATA_PORT		0x2f

/* Possible alternate values, depends on how the chip is wired */
#घोषणा CR_INDEX_PORT2		0x4e
#घोषणा CR_DATA_PORT2		0x4f

/*
 * GCR_CONFIG_PORT_SEL bit 4 specअगरies which Index Port value is
 * active. 1 = 0x4e, 0 = 0x2e
 */
#घोषणा PORT_SEL_PORT_4E_EN	0x10

/* Extended Function Mode enable/disable magic values */
#घोषणा CONFIG_REG_ENABLE	0x87
#घोषणा CONFIG_REG_DISABLE	0xaa

/* Chip IDs found in CR_CHIP_ID_अणुHI,LOपूर्ण */
#घोषणा CHIP_ID_HIGH_F71809U	0x04
#घोषणा CHIP_ID_LOW_F71809U	0x08

/*
 * Global control regs we need to care about:
 *      Global Control                  def.
 *      Register name           addr    val. */
#घोषणा GCR_SOFTWARE_RESET	0x02 /* 0x00 */
#घोषणा GCR_LOGICAL_DEV_NO	0x07 /* 0x00 */
#घोषणा GCR_CHIP_ID_HI		0x20 /* 0x04 */
#घोषणा GCR_CHIP_ID_LO		0x21 /* 0x08 */
#घोषणा GCR_VENDOR_ID_HI	0x23 /* 0x19 */
#घोषणा GCR_VENDOR_ID_LO	0x24 /* 0x34 */
#घोषणा GCR_CONFIG_PORT_SEL	0x25 /* 0x01 */
#घोषणा GCR_KBMOUSE_WAKEUP	0x27

#घोषणा LOGICAL_DEV_DISABLE	0x00
#घोषणा LOGICAL_DEV_ENABLE	0x01

/* Logical device number of the CIR function */
#घोषणा LOGICAL_DEV_CIR_REV1	0x05
#घोषणा LOGICAL_DEV_CIR_REV2	0x08

/* CIR Logical Device (LDN 0x08) config रेजिस्टरs */
#घोषणा CIR_CR_COMMAND_INDEX	0x04
#घोषणा CIR_CR_IRCS		0x05 /* Beक्रमe host ग_लिखोs command to IR, host
					must set to 1. When host finshes ग_लिखो
					command to IR, host must clear to 0. */
#घोषणा CIR_CR_COMMAND_DATA	0x06 /* Host पढ़ो or ग_लिखो command data */
#घोषणा CIR_CR_CLASS		0x07 /* 0xff = rx-only, 0x66 = rx + 2 tx,
					0x33 = rx + 1 tx */
#घोषणा CIR_CR_DEV_EN		0x30 /* bit0 = 1 enables CIR */
#घोषणा CIR_CR_BASE_ADDR_HI	0x60 /* MSB of CIR IO base addr */
#घोषणा CIR_CR_BASE_ADDR_LO	0x61 /* LSB of CIR IO base addr */
#घोषणा CIR_CR_IRQ_SEL		0x70 /* bits3-0 store CIR IRQ */
#घोषणा CIR_CR_PSOUT_STATUS	0xf1
#घोषणा CIR_CR_WAKE_KEY3_ADDR	0xf8
#घोषणा CIR_CR_WAKE_KEY3_CODE	0xf9
#घोषणा CIR_CR_WAKE_KEY3_DC	0xfa
#घोषणा CIR_CR_WAKE_CONTROL	0xfb
#घोषणा CIR_CR_WAKE_KEY12_ADDR	0xfc
#घोषणा CIR_CR_WAKE_KEY4_ADDR	0xfd
#घोषणा CIR_CR_WAKE_KEY5_ADDR	0xfe

#घोषणा CLASS_RX_ONLY		0xff
#घोषणा CLASS_RX_2TX		0x66
#घोषणा CLASS_RX_1TX		0x33

/* CIR device रेजिस्टरs */
#घोषणा CIR_STATUS		0x00
#घोषणा CIR_RX_DATA		0x01
#घोषणा CIR_TX_CONTROL		0x02
#घोषणा CIR_TX_DATA		0x03
#घोषणा CIR_CONTROL		0x04

/* Bits to enable CIR wake */
#घोषणा LOGICAL_DEV_ACPI	0x01
#घोषणा LDEV_ACPI_WAKE_EN_REG	0xe8
#घोषणा ACPI_WAKE_EN_CIR_BIT	0x04

#घोषणा LDEV_ACPI_PME_EN_REG	0xf0
#घोषणा LDEV_ACPI_PME_CLR_REG	0xf1
#घोषणा ACPI_PME_CIR_BIT	0x02

#घोषणा LDEV_ACPI_STATE_REG	0xf4
#घोषणा ACPI_STATE_CIR_BIT	0x20

/*
 * CIR status रेजिस्टर (0x00):
 *   7 - CIR_IRQ_EN (1 = enable CIR IRQ, 0 = disable)
 *   3 - TX_FINISH (1 when TX finished, ग_लिखो 1 to clear)
 *   2 - TX_UNDERRUN (1 on TX underrun, ग_लिखो 1 to clear)
 *   1 - RX_TIMEOUT (1 on RX समयout, ग_लिखो 1 to clear)
 *   0 - RX_RECEIVE (1 on RX receive, ग_लिखो 1 to clear)
 */
#घोषणा CIR_STATUS_IRQ_EN	0x80
#घोषणा CIR_STATUS_TX_FINISH	0x08
#घोषणा CIR_STATUS_TX_UNDERRUN	0x04
#घोषणा CIR_STATUS_RX_TIMEOUT	0x02
#घोषणा CIR_STATUS_RX_RECEIVE	0x01
#घोषणा CIR_STATUS_IRQ_MASK	0x0f

/*
 * CIR TX control रेजिस्टर (0x02):
 *   7 - TX_START (1 to indicate TX start, स्वतः-cleared when करोne)
 *   6 - TX_END (1 to indicate TX data written to TX fअगरo)
 */
#घोषणा CIR_TX_CONTROL_TX_START	0x80
#घोषणा CIR_TX_CONTROL_TX_END	0x40

