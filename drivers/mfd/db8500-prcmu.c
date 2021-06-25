<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * DB8500 PRCM Unit driver
 *
 * Copyright (C) STMicroelectronics 2009
 * Copyright (C) ST-Ericsson SA 2010
 *
 * Author: Kumar Sanghvi <kumar.sanghvi@stericsson.com>
 * Author: Sundar Iyer <sundar.iyer@stericsson.com>
 * Author: Mattias Nilsson <mattias.i.nilsson@stericsson.com>
 *
 * U8500 PRCM Unit पूर्णांकerface driver
 */
#समावेश <linux/init.h>
#समावेश <linux/export.h>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/err.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/mutex.h>
#समावेश <linux/completion.h>
#समावेश <linux/irq.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/bitops.h>
#समावेश <linux/fs.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/dbx500-prcmu.h>
#समावेश <linux/mfd/abx500/ab8500.h>
#समावेश <linux/regulator/db8500-prcmu.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/platक्रमm_data/ux500_wdt.h>
#समावेश "dbx500-prcmu-regs.h"

/* Index of dअगरferent voltages to be used when accessing AVSData */
#घोषणा PRCM_AVS_BASE		0x2FC
#घोषणा PRCM_AVS_VBB_RET	(PRCM_AVS_BASE + 0x0)
#घोषणा PRCM_AVS_VBB_MAX_OPP	(PRCM_AVS_BASE + 0x1)
#घोषणा PRCM_AVS_VBB_100_OPP	(PRCM_AVS_BASE + 0x2)
#घोषणा PRCM_AVS_VBB_50_OPP	(PRCM_AVS_BASE + 0x3)
#घोषणा PRCM_AVS_VARM_MAX_OPP	(PRCM_AVS_BASE + 0x4)
#घोषणा PRCM_AVS_VARM_100_OPP	(PRCM_AVS_BASE + 0x5)
#घोषणा PRCM_AVS_VARM_50_OPP	(PRCM_AVS_BASE + 0x6)
#घोषणा PRCM_AVS_VARM_RET	(PRCM_AVS_BASE + 0x7)
#घोषणा PRCM_AVS_VAPE_100_OPP	(PRCM_AVS_BASE + 0x8)
#घोषणा PRCM_AVS_VAPE_50_OPP	(PRCM_AVS_BASE + 0x9)
#घोषणा PRCM_AVS_VMOD_100_OPP	(PRCM_AVS_BASE + 0xA)
#घोषणा PRCM_AVS_VMOD_50_OPP	(PRCM_AVS_BASE + 0xB)
#घोषणा PRCM_AVS_VSAFE		(PRCM_AVS_BASE + 0xC)

#घोषणा PRCM_AVS_VOLTAGE		0
#घोषणा PRCM_AVS_VOLTAGE_MASK		0x3f
#घोषणा PRCM_AVS_ISSLOWSTARTUP		6
#घोषणा PRCM_AVS_ISSLOWSTARTUP_MASK	(1 << PRCM_AVS_ISSLOWSTARTUP)
#घोषणा PRCM_AVS_ISMODEENABLE		7
#घोषणा PRCM_AVS_ISMODEENABLE_MASK	(1 << PRCM_AVS_ISMODEENABLE)

#घोषणा PRCM_BOOT_STATUS	0xFFF
#घोषणा PRCM_ROMCODE_A2P	0xFFE
#घोषणा PRCM_ROMCODE_P2A	0xFFD
#घोषणा PRCM_XP70_CUR_PWR_STATE 0xFFC      /* 4 BYTES */

#घोषणा PRCM_SW_RST_REASON 0xFF8 /* 2 bytes */

#घोषणा _PRCM_MBOX_HEADER		0xFE8 /* 16 bytes */
#घोषणा PRCM_MBOX_HEADER_REQ_MB0	(_PRCM_MBOX_HEADER + 0x0)
#घोषणा PRCM_MBOX_HEADER_REQ_MB1	(_PRCM_MBOX_HEADER + 0x1)
#घोषणा PRCM_MBOX_HEADER_REQ_MB2	(_PRCM_MBOX_HEADER + 0x2)
#घोषणा PRCM_MBOX_HEADER_REQ_MB3	(_PRCM_MBOX_HEADER + 0x3)
#घोषणा PRCM_MBOX_HEADER_REQ_MB4	(_PRCM_MBOX_HEADER + 0x4)
#घोषणा PRCM_MBOX_HEADER_REQ_MB5	(_PRCM_MBOX_HEADER + 0x5)
#घोषणा PRCM_MBOX_HEADER_ACK_MB0	(_PRCM_MBOX_HEADER + 0x8)

/* Req Mailboxes */
#घोषणा PRCM_REQ_MB0 0xFDC /* 12 bytes  */
#घोषणा PRCM_REQ_MB1 0xFD0 /* 12 bytes  */
#घोषणा PRCM_REQ_MB2 0xFC0 /* 16 bytes  */
#घोषणा PRCM_REQ_MB3 0xE4C /* 372 bytes  */
#घोषणा PRCM_REQ_MB4 0xE48 /* 4 bytes  */
#घोषणा PRCM_REQ_MB5 0xE44 /* 4 bytes  */

/* Ack Mailboxes */
#घोषणा PRCM_ACK_MB0 0xE08 /* 52 bytes  */
#घोषणा PRCM_ACK_MB1 0xE04 /* 4 bytes */
#घोषणा PRCM_ACK_MB2 0xE00 /* 4 bytes */
#घोषणा PRCM_ACK_MB3 0xDFC /* 4 bytes */
#घोषणा PRCM_ACK_MB4 0xDF8 /* 4 bytes */
#घोषणा PRCM_ACK_MB5 0xDF4 /* 4 bytes */

/* Mailbox 0 headers */
#घोषणा MB0H_POWER_STATE_TRANS		0
#घोषणा MB0H_CONFIG_WAKEUPS_EXE		1
#घोषणा MB0H_READ_WAKEUP_ACK		3
#घोषणा MB0H_CONFIG_WAKEUPS_SLEEP	4

#घोषणा MB0H_WAKEUP_EXE 2
#घोषणा MB0H_WAKEUP_SLEEP 5

/* Mailbox 0 REQs */
#घोषणा PRCM_REQ_MB0_AP_POWER_STATE	(PRCM_REQ_MB0 + 0x0)
#घोषणा PRCM_REQ_MB0_AP_PLL_STATE	(PRCM_REQ_MB0 + 0x1)
#घोषणा PRCM_REQ_MB0_ULP_CLOCK_STATE	(PRCM_REQ_MB0 + 0x2)
#घोषणा PRCM_REQ_MB0_DO_NOT_WFI		(PRCM_REQ_MB0 + 0x3)
#घोषणा PRCM_REQ_MB0_WAKEUP_8500	(PRCM_REQ_MB0 + 0x4)
#घोषणा PRCM_REQ_MB0_WAKEUP_4500	(PRCM_REQ_MB0 + 0x8)

/* Mailbox 0 ACKs */
#घोषणा PRCM_ACK_MB0_AP_PWRSTTR_STATUS	(PRCM_ACK_MB0 + 0x0)
#घोषणा PRCM_ACK_MB0_READ_POINTER	(PRCM_ACK_MB0 + 0x1)
#घोषणा PRCM_ACK_MB0_WAKEUP_0_8500	(PRCM_ACK_MB0 + 0x4)
#घोषणा PRCM_ACK_MB0_WAKEUP_0_4500	(PRCM_ACK_MB0 + 0x8)
#घोषणा PRCM_ACK_MB0_WAKEUP_1_8500	(PRCM_ACK_MB0 + 0x1C)
#घोषणा PRCM_ACK_MB0_WAKEUP_1_4500	(PRCM_ACK_MB0 + 0x20)
#घोषणा PRCM_ACK_MB0_EVENT_4500_NUMBERS	20

/* Mailbox 1 headers */
#घोषणा MB1H_ARM_APE_OPP 0x0
#घोषणा MB1H_RESET_MODEM 0x2
#घोषणा MB1H_REQUEST_APE_OPP_100_VOLT 0x3
#घोषणा MB1H_RELEASE_APE_OPP_100_VOLT 0x4
#घोषणा MB1H_RELEASE_USB_WAKEUP 0x5
#घोषणा MB1H_PLL_ON_OFF 0x6

/* Mailbox 1 Requests */
#घोषणा PRCM_REQ_MB1_ARM_OPP			(PRCM_REQ_MB1 + 0x0)
#घोषणा PRCM_REQ_MB1_APE_OPP			(PRCM_REQ_MB1 + 0x1)
#घोषणा PRCM_REQ_MB1_PLL_ON_OFF			(PRCM_REQ_MB1 + 0x4)
#घोषणा PLL_SOC0_OFF	0x1
#घोषणा PLL_SOC0_ON	0x2
#घोषणा PLL_SOC1_OFF	0x4
#घोषणा PLL_SOC1_ON	0x8

/* Mailbox 1 ACKs */
#घोषणा PRCM_ACK_MB1_CURRENT_ARM_OPP	(PRCM_ACK_MB1 + 0x0)
#घोषणा PRCM_ACK_MB1_CURRENT_APE_OPP	(PRCM_ACK_MB1 + 0x1)
#घोषणा PRCM_ACK_MB1_APE_VOLTAGE_STATUS	(PRCM_ACK_MB1 + 0x2)
#घोषणा PRCM_ACK_MB1_DVFS_STATUS	(PRCM_ACK_MB1 + 0x3)

/* Mailbox 2 headers */
#घोषणा MB2H_DPS	0x0
#घोषणा MB2H_AUTO_PWR	0x1

/* Mailbox 2 REQs */
#घोषणा PRCM_REQ_MB2_SVA_MMDSP		(PRCM_REQ_MB2 + 0x0)
#घोषणा PRCM_REQ_MB2_SVA_PIPE		(PRCM_REQ_MB2 + 0x1)
#घोषणा PRCM_REQ_MB2_SIA_MMDSP		(PRCM_REQ_MB2 + 0x2)
#घोषणा PRCM_REQ_MB2_SIA_PIPE		(PRCM_REQ_MB2 + 0x3)
#घोषणा PRCM_REQ_MB2_SGA		(PRCM_REQ_MB2 + 0x4)
#घोषणा PRCM_REQ_MB2_B2R2_MCDE		(PRCM_REQ_MB2 + 0x5)
#घोषणा PRCM_REQ_MB2_ESRAM12		(PRCM_REQ_MB2 + 0x6)
#घोषणा PRCM_REQ_MB2_ESRAM34		(PRCM_REQ_MB2 + 0x7)
#घोषणा PRCM_REQ_MB2_AUTO_PM_SLEEP	(PRCM_REQ_MB2 + 0x8)
#घोषणा PRCM_REQ_MB2_AUTO_PM_IDLE	(PRCM_REQ_MB2 + 0xC)

/* Mailbox 2 ACKs */
#घोषणा PRCM_ACK_MB2_DPS_STATUS (PRCM_ACK_MB2 + 0x0)
#घोषणा HWACC_PWR_ST_OK 0xFE

/* Mailbox 3 headers */
#घोषणा MB3H_ANC	0x0
#घोषणा MB3H_SIDETONE	0x1
#घोषणा MB3H_SYSCLK	0xE

/* Mailbox 3 Requests */
#घोषणा PRCM_REQ_MB3_ANC_FIR_COEFF	(PRCM_REQ_MB3 + 0x0)
#घोषणा PRCM_REQ_MB3_ANC_IIR_COEFF	(PRCM_REQ_MB3 + 0x20)
#घोषणा PRCM_REQ_MB3_ANC_SHIFTER	(PRCM_REQ_MB3 + 0x60)
#घोषणा PRCM_REQ_MB3_ANC_WARP		(PRCM_REQ_MB3 + 0x64)
#घोषणा PRCM_REQ_MB3_SIDETONE_FIR_GAIN	(PRCM_REQ_MB3 + 0x68)
#घोषणा PRCM_REQ_MB3_SIDETONE_FIR_COEFF	(PRCM_REQ_MB3 + 0x6C)
#घोषणा PRCM_REQ_MB3_SYSCLK_MGT		(PRCM_REQ_MB3 + 0x16C)

/* Mailbox 4 headers */
#घोषणा MB4H_DDR_INIT	0x0
#घोषणा MB4H_MEM_ST	0x1
#घोषणा MB4H_HOTDOG	0x12
#घोषणा MB4H_HOTMON	0x13
#घोषणा MB4H_HOT_PERIOD	0x14
#घोषणा MB4H_A9WDOG_CONF 0x16
#घोषणा MB4H_A9WDOG_EN   0x17
#घोषणा MB4H_A9WDOG_DIS  0x18
#घोषणा MB4H_A9WDOG_LOAD 0x19
#घोषणा MB4H_A9WDOG_KICK 0x20

/* Mailbox 4 Requests */
#घोषणा PRCM_REQ_MB4_DDR_ST_AP_SLEEP_IDLE	(PRCM_REQ_MB4 + 0x0)
#घोषणा PRCM_REQ_MB4_DDR_ST_AP_DEEP_IDLE	(PRCM_REQ_MB4 + 0x1)
#घोषणा PRCM_REQ_MB4_ESRAM0_ST			(PRCM_REQ_MB4 + 0x3)
#घोषणा PRCM_REQ_MB4_HOTDOG_THRESHOLD		(PRCM_REQ_MB4 + 0x0)
#घोषणा PRCM_REQ_MB4_HOTMON_LOW			(PRCM_REQ_MB4 + 0x0)
#घोषणा PRCM_REQ_MB4_HOTMON_HIGH		(PRCM_REQ_MB4 + 0x1)
#घोषणा PRCM_REQ_MB4_HOTMON_CONFIG		(PRCM_REQ_MB4 + 0x2)
#घोषणा PRCM_REQ_MB4_HOT_PERIOD			(PRCM_REQ_MB4 + 0x0)
#घोषणा HOTMON_CONFIG_LOW			BIT(0)
#घोषणा HOTMON_CONFIG_HIGH			BIT(1)
#घोषणा PRCM_REQ_MB4_A9WDOG_0			(PRCM_REQ_MB4 + 0x0)
#घोषणा PRCM_REQ_MB4_A9WDOG_1			(PRCM_REQ_MB4 + 0x1)
#घोषणा PRCM_REQ_MB4_A9WDOG_2			(PRCM_REQ_MB4 + 0x2)
#घोषणा PRCM_REQ_MB4_A9WDOG_3			(PRCM_REQ_MB4 + 0x3)
#घोषणा A9WDOG_AUTO_OFF_EN			BIT(7)
#घोषणा A9WDOG_AUTO_OFF_DIS			0
#घोषणा A9WDOG_ID_MASK				0xf

/* Mailbox 5 Requests */
#घोषणा PRCM_REQ_MB5_I2C_SLAVE_OP	(PRCM_REQ_MB5 + 0x0)
#घोषणा PRCM_REQ_MB5_I2C_HW_BITS	(PRCM_REQ_MB5 + 0x1)
#घोषणा PRCM_REQ_MB5_I2C_REG		(PRCM_REQ_MB5 + 0x2)
#घोषणा PRCM_REQ_MB5_I2C_VAL		(PRCM_REQ_MB5 + 0x3)
#घोषणा PRCMU_I2C_WRITE(slave) (((slave) << 1) | BIT(6))
#घोषणा PRCMU_I2C_READ(slave) (((slave) << 1) | BIT(0) | BIT(6))
#घोषणा PRCMU_I2C_STOP_EN		BIT(3)

/* Mailbox 5 ACKs */
#घोषणा PRCM_ACK_MB5_I2C_STATUS	(PRCM_ACK_MB5 + 0x1)
#घोषणा PRCM_ACK_MB5_I2C_VAL	(PRCM_ACK_MB5 + 0x3)
#घोषणा I2C_WR_OK 0x1
#घोषणा I2C_RD_OK 0x2

#घोषणा NUM_MB 8
#घोषणा MBOX_BIT BIT
#घोषणा ALL_MBOX_BITS (MBOX_BIT(NUM_MB) - 1)

/*
 * Wakeups/IRQs
 */

#घोषणा WAKEUP_BIT_RTC BIT(0)
#घोषणा WAKEUP_BIT_RTT0 BIT(1)
#घोषणा WAKEUP_BIT_RTT1 BIT(2)
#घोषणा WAKEUP_BIT_HSI0 BIT(3)
#घोषणा WAKEUP_BIT_HSI1 BIT(4)
#घोषणा WAKEUP_BIT_CA_WAKE BIT(5)
#घोषणा WAKEUP_BIT_USB BIT(6)
#घोषणा WAKEUP_BIT_ABB BIT(7)
#घोषणा WAKEUP_BIT_ABB_FIFO BIT(8)
#घोषणा WAKEUP_BIT_SYSCLK_OK BIT(9)
#घोषणा WAKEUP_BIT_CA_SLEEP BIT(10)
#घोषणा WAKEUP_BIT_AC_WAKE_ACK BIT(11)
#घोषणा WAKEUP_BIT_SIDE_TONE_OK BIT(12)
#घोषणा WAKEUP_BIT_ANC_OK BIT(13)
#घोषणा WAKEUP_BIT_SW_ERROR BIT(14)
#घोषणा WAKEUP_BIT_AC_SLEEP_ACK BIT(15)
#घोषणा WAKEUP_BIT_ARM BIT(17)
#घोषणा WAKEUP_BIT_HOTMON_LOW BIT(18)
#घोषणा WAKEUP_BIT_HOTMON_HIGH BIT(19)
#घोषणा WAKEUP_BIT_MODEM_SW_RESET_REQ BIT(20)
#घोषणा WAKEUP_BIT_GPIO0 BIT(23)
#घोषणा WAKEUP_BIT_GPIO1 BIT(24)
#घोषणा WAKEUP_BIT_GPIO2 BIT(25)
#घोषणा WAKEUP_BIT_GPIO3 BIT(26)
#घोषणा WAKEUP_BIT_GPIO4 BIT(27)
#घोषणा WAKEUP_BIT_GPIO5 BIT(28)
#घोषणा WAKEUP_BIT_GPIO6 BIT(29)
#घोषणा WAKEUP_BIT_GPIO7 BIT(30)
#घोषणा WAKEUP_BIT_GPIO8 BIT(31)

अटल काष्ठा अणु
	bool valid;
	काष्ठा prcmu_fw_version version;
पूर्ण fw_info;

अटल काष्ठा irq_करोमुख्य *db8500_irq_करोमुख्य;

/*
 * This vector maps irq numbers to the bits in the bit field used in
 * communication with the PRCMU firmware.
 *
 * The reason क्रम having this is to keep the irq numbers contiguous even though
 * the bits in the bit field are not. (The bits also have a tendency to move
 * around, to further complicate matters.)
 */
#घोषणा IRQ_INDEX(_name) ((IRQ_PRCMU_##_name))
#घोषणा IRQ_ENTRY(_name)[IRQ_INDEX(_name)] = (WAKEUP_BIT_##_name)

#घोषणा IRQ_PRCMU_RTC 0
#घोषणा IRQ_PRCMU_RTT0 1
#घोषणा IRQ_PRCMU_RTT1 2
#घोषणा IRQ_PRCMU_HSI0 3
#घोषणा IRQ_PRCMU_HSI1 4
#घोषणा IRQ_PRCMU_CA_WAKE 5
#घोषणा IRQ_PRCMU_USB 6
#घोषणा IRQ_PRCMU_ABB 7
#घोषणा IRQ_PRCMU_ABB_FIFO 8
#घोषणा IRQ_PRCMU_ARM 9
#घोषणा IRQ_PRCMU_MODEM_SW_RESET_REQ 10
#घोषणा IRQ_PRCMU_GPIO0 11
#घोषणा IRQ_PRCMU_GPIO1 12
#घोषणा IRQ_PRCMU_GPIO2 13
#घोषणा IRQ_PRCMU_GPIO3 14
#घोषणा IRQ_PRCMU_GPIO4 15
#घोषणा IRQ_PRCMU_GPIO5 16
#घोषणा IRQ_PRCMU_GPIO6 17
#घोषणा IRQ_PRCMU_GPIO7 18
#घोषणा IRQ_PRCMU_GPIO8 19
#घोषणा IRQ_PRCMU_CA_SLEEP 20
#घोषणा IRQ_PRCMU_HOTMON_LOW 21
#घोषणा IRQ_PRCMU_HOTMON_HIGH 22
#घोषणा NUM_PRCMU_WAKEUPS 23

अटल u32 prcmu_irq_bit[NUM_PRCMU_WAKEUPS] = अणु
	IRQ_ENTRY(RTC),
	IRQ_ENTRY(RTT0),
	IRQ_ENTRY(RTT1),
	IRQ_ENTRY(HSI0),
	IRQ_ENTRY(HSI1),
	IRQ_ENTRY(CA_WAKE),
	IRQ_ENTRY(USB),
	IRQ_ENTRY(ABB),
	IRQ_ENTRY(ABB_FIFO),
	IRQ_ENTRY(CA_SLEEP),
	IRQ_ENTRY(ARM),
	IRQ_ENTRY(HOTMON_LOW),
	IRQ_ENTRY(HOTMON_HIGH),
	IRQ_ENTRY(MODEM_SW_RESET_REQ),
	IRQ_ENTRY(GPIO0),
	IRQ_ENTRY(GPIO1),
	IRQ_ENTRY(GPIO2),
	IRQ_ENTRY(GPIO3),
	IRQ_ENTRY(GPIO4),
	IRQ_ENTRY(GPIO5),
	IRQ_ENTRY(GPIO6),
	IRQ_ENTRY(GPIO7),
	IRQ_ENTRY(GPIO8)
पूर्ण;

#घोषणा VALID_WAKEUPS (BIT(NUM_PRCMU_WAKEUP_INDICES) - 1)
#घोषणा WAKEUP_ENTRY(_name)[PRCMU_WAKEUP_INDEX_##_name] = (WAKEUP_BIT_##_name)
अटल u32 prcmu_wakeup_bit[NUM_PRCMU_WAKEUP_INDICES] = अणु
	WAKEUP_ENTRY(RTC),
	WAKEUP_ENTRY(RTT0),
	WAKEUP_ENTRY(RTT1),
	WAKEUP_ENTRY(HSI0),
	WAKEUP_ENTRY(HSI1),
	WAKEUP_ENTRY(USB),
	WAKEUP_ENTRY(ABB),
	WAKEUP_ENTRY(ABB_FIFO),
	WAKEUP_ENTRY(ARM)
पूर्ण;

/*
 * mb0_transfer - state needed क्रम mailbox 0 communication.
 * @lock:		The transaction lock.
 * @dbb_events_lock:	A lock used to handle concurrent access to (parts of)
 *			the request data.
 * @mask_work:		Work काष्ठाure used क्रम (un)masking wakeup पूर्णांकerrupts.
 * @req:		Request data that need to persist between requests.
 */
अटल काष्ठा अणु
	spinlock_t lock;
	spinlock_t dbb_irqs_lock;
	काष्ठा work_काष्ठा mask_work;
	काष्ठा mutex ac_wake_lock;
	काष्ठा completion ac_wake_work;
	काष्ठा अणु
		u32 dbb_irqs;
		u32 dbb_wakeups;
		u32 abb_events;
	पूर्ण req;
पूर्ण mb0_transfer;

/*
 * mb1_transfer - state needed क्रम mailbox 1 communication.
 * @lock:	The transaction lock.
 * @work:	The transaction completion काष्ठाure.
 * @ape_opp:	The current APE OPP.
 * @ack:	Reply ("acknowledge") data.
 */
अटल काष्ठा अणु
	काष्ठा mutex lock;
	काष्ठा completion work;
	u8 ape_opp;
	काष्ठा अणु
		u8 header;
		u8 arm_opp;
		u8 ape_opp;
		u8 ape_voltage_status;
	पूर्ण ack;
पूर्ण mb1_transfer;

/*
 * mb2_transfer - state needed क्रम mailbox 2 communication.
 * @lock:            The transaction lock.
 * @work:            The transaction completion काष्ठाure.
 * @स्वतः_pm_lock:    The स्वतःnomous घातer management configuration lock.
 * @स्वतः_pm_enabled: A flag indicating whether स्वतःnomous PM is enabled.
 * @req:             Request data that need to persist between requests.
 * @ack:             Reply ("acknowledge") data.
 */
अटल काष्ठा अणु
	काष्ठा mutex lock;
	काष्ठा completion work;
	spinlock_t स्वतः_pm_lock;
	bool स्वतः_pm_enabled;
	काष्ठा अणु
		u8 status;
	पूर्ण ack;
पूर्ण mb2_transfer;

/*
 * mb3_transfer - state needed क्रम mailbox 3 communication.
 * @lock:		The request lock.
 * @sysclk_lock:	A lock used to handle concurrent sysclk requests.
 * @sysclk_work:	Work काष्ठाure used क्रम sysclk requests.
 */
अटल काष्ठा अणु
	spinlock_t lock;
	काष्ठा mutex sysclk_lock;
	काष्ठा completion sysclk_work;
पूर्ण mb3_transfer;

/*
 * mb4_transfer - state needed क्रम mailbox 4 communication.
 * @lock:	The transaction lock.
 * @work:	The transaction completion काष्ठाure.
 */
अटल काष्ठा अणु
	काष्ठा mutex lock;
	काष्ठा completion work;
पूर्ण mb4_transfer;

/*
 * mb5_transfer - state needed क्रम mailbox 5 communication.
 * @lock:	The transaction lock.
 * @work:	The transaction completion काष्ठाure.
 * @ack:	Reply ("acknowledge") data.
 */
अटल काष्ठा अणु
	काष्ठा mutex lock;
	काष्ठा completion work;
	काष्ठा अणु
		u8 status;
		u8 value;
	पूर्ण ack;
पूर्ण mb5_transfer;

अटल atomic_t ac_wake_req_state = ATOMIC_INIT(0);

/* Spinlocks */
अटल DEFINE_SPINLOCK(prcmu_lock);
अटल DEFINE_SPINLOCK(clkout_lock);

/* Global var to runसमय determine TCDM base क्रम v2 or v1 */
अटल __iomem व्योम *tcdm_base;
अटल __iomem व्योम *prcmu_base;

काष्ठा clk_mgt अणु
	u32 offset;
	u32 pllsw;
	पूर्णांक branch;
	bool clk38भाग;
पूर्ण;

क्रमागत अणु
	PLL_RAW,
	PLL_FIX,
	PLL_DIV
पूर्ण;

अटल DEFINE_SPINLOCK(clk_mgt_lock);

#घोषणा CLK_MGT_ENTRY(_name, _branch, _clk38भाग)[PRCMU_##_name] = \
	अणु (PRCM_##_name##_MGT), 0 , _branch, _clk38भागपूर्ण
अटल काष्ठा clk_mgt clk_mgt[PRCMU_NUM_REG_CLOCKS] = अणु
	CLK_MGT_ENTRY(SGACLK, PLL_DIV, false),
	CLK_MGT_ENTRY(UARTCLK, PLL_FIX, true),
	CLK_MGT_ENTRY(MSP02CLK, PLL_FIX, true),
	CLK_MGT_ENTRY(MSP1CLK, PLL_FIX, true),
	CLK_MGT_ENTRY(I2CCLK, PLL_FIX, true),
	CLK_MGT_ENTRY(SDMMCCLK, PLL_DIV, true),
	CLK_MGT_ENTRY(SLIMCLK, PLL_FIX, true),
	CLK_MGT_ENTRY(PER1CLK, PLL_DIV, true),
	CLK_MGT_ENTRY(PER2CLK, PLL_DIV, true),
	CLK_MGT_ENTRY(PER3CLK, PLL_DIV, true),
	CLK_MGT_ENTRY(PER5CLK, PLL_DIV, true),
	CLK_MGT_ENTRY(PER6CLK, PLL_DIV, true),
	CLK_MGT_ENTRY(PER7CLK, PLL_DIV, true),
	CLK_MGT_ENTRY(LCDCLK, PLL_FIX, true),
	CLK_MGT_ENTRY(BMLCLK, PLL_DIV, true),
	CLK_MGT_ENTRY(HSITXCLK, PLL_DIV, true),
	CLK_MGT_ENTRY(HSIRXCLK, PLL_DIV, true),
	CLK_MGT_ENTRY(HDMICLK, PLL_FIX, false),
	CLK_MGT_ENTRY(APEATCLK, PLL_DIV, true),
	CLK_MGT_ENTRY(APETRACECLK, PLL_DIV, true),
	CLK_MGT_ENTRY(MCDECLK, PLL_DIV, true),
	CLK_MGT_ENTRY(IPI2CCLK, PLL_FIX, true),
	CLK_MGT_ENTRY(DSIALTCLK, PLL_FIX, false),
	CLK_MGT_ENTRY(DMACLK, PLL_DIV, true),
	CLK_MGT_ENTRY(B2R2CLK, PLL_DIV, true),
	CLK_MGT_ENTRY(TVCLK, PLL_FIX, true),
	CLK_MGT_ENTRY(SSPCLK, PLL_FIX, true),
	CLK_MGT_ENTRY(RNGCLK, PLL_FIX, true),
	CLK_MGT_ENTRY(UICCCLK, PLL_FIX, false),
पूर्ण;

काष्ठा dsiclk अणु
	u32 भागsel_mask;
	u32 भागsel_shअगरt;
	u32 भागsel;
पूर्ण;

अटल काष्ठा dsiclk dsiclk[2] = अणु
	अणु
		.भागsel_mask = PRCM_DSI_PLLOUT_SEL_DSI0_PLLOUT_DIVSEL_MASK,
		.भागsel_shअगरt = PRCM_DSI_PLLOUT_SEL_DSI0_PLLOUT_DIVSEL_SHIFT,
		.भागsel = PRCM_DSI_PLLOUT_SEL_PHI,
	पूर्ण,
	अणु
		.भागsel_mask = PRCM_DSI_PLLOUT_SEL_DSI1_PLLOUT_DIVSEL_MASK,
		.भागsel_shअगरt = PRCM_DSI_PLLOUT_SEL_DSI1_PLLOUT_DIVSEL_SHIFT,
		.भागsel = PRCM_DSI_PLLOUT_SEL_PHI,
	पूर्ण
पूर्ण;

काष्ठा dsiescclk अणु
	u32 en;
	u32 भाग_mask;
	u32 भाग_shअगरt;
पूर्ण;

अटल काष्ठा dsiescclk dsiescclk[3] = अणु
	अणु
		.en = PRCM_DSITVCLK_DIV_DSI0_ESC_CLK_EN,
		.भाग_mask = PRCM_DSITVCLK_DIV_DSI0_ESC_CLK_DIV_MASK,
		.भाग_shअगरt = PRCM_DSITVCLK_DIV_DSI0_ESC_CLK_DIV_SHIFT,
	पूर्ण,
	अणु
		.en = PRCM_DSITVCLK_DIV_DSI1_ESC_CLK_EN,
		.भाग_mask = PRCM_DSITVCLK_DIV_DSI1_ESC_CLK_DIV_MASK,
		.भाग_shअगरt = PRCM_DSITVCLK_DIV_DSI1_ESC_CLK_DIV_SHIFT,
	पूर्ण,
	अणु
		.en = PRCM_DSITVCLK_DIV_DSI2_ESC_CLK_EN,
		.भाग_mask = PRCM_DSITVCLK_DIV_DSI2_ESC_CLK_DIV_MASK,
		.भाग_shअगरt = PRCM_DSITVCLK_DIV_DSI2_ESC_CLK_DIV_SHIFT,
	पूर्ण
पूर्ण;

u32 db8500_prcmu_पढ़ो(अचिन्हित पूर्णांक reg)
अणु
	वापस पढ़ोl(prcmu_base + reg);
पूर्ण

व्योम db8500_prcmu_ग_लिखो(अचिन्हित पूर्णांक reg, u32 value)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&prcmu_lock, flags);
	ग_लिखोl(value, (prcmu_base + reg));
	spin_unlock_irqrestore(&prcmu_lock, flags);
पूर्ण

व्योम db8500_prcmu_ग_लिखो_masked(अचिन्हित पूर्णांक reg, u32 mask, u32 value)
अणु
	u32 val;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&prcmu_lock, flags);
	val = पढ़ोl(prcmu_base + reg);
	val = ((val & ~mask) | (value & mask));
	ग_लिखोl(val, (prcmu_base + reg));
	spin_unlock_irqrestore(&prcmu_lock, flags);
पूर्ण

काष्ठा prcmu_fw_version *prcmu_get_fw_version(व्योम)
अणु
	वापस fw_info.valid ? &fw_info.version : शून्य;
पूर्ण

अटल bool prcmu_is_ulppll_disabled(व्योम)
अणु
	काष्ठा prcmu_fw_version *ver;

	ver = prcmu_get_fw_version();
	वापस ver && ver->project == PRCMU_FW_PROJECT_U8420_SYSCLK;
पूर्ण

bool prcmu_has_arm_maxopp(व्योम)
अणु
	वापस (पढ़ोb(tcdm_base + PRCM_AVS_VARM_MAX_OPP) &
		PRCM_AVS_ISMODEENABLE_MASK) == PRCM_AVS_ISMODEENABLE_MASK;
पूर्ण

/**
 * prcmu_set_rc_a2p - This function is used to run few घातer state sequences
 * @val: Value to be set, i.e. transition requested
 * Returns: 0 on success, -EINVAL on invalid argument
 *
 * This function is used to run the following घातer state sequences -
 * any state to ApReset,  ApDeepSleep to ApExecute, ApExecute to ApDeepSleep
 */
पूर्णांक prcmu_set_rc_a2p(क्रमागत romcode_ग_लिखो val)
अणु
	अगर (val < RDY_2_DS || val > RDY_2_XP70_RST)
		वापस -EINVAL;
	ग_लिखोb(val, (tcdm_base + PRCM_ROMCODE_A2P));
	वापस 0;
पूर्ण

/**
 * prcmu_get_rc_p2a - This function is used to get घातer state sequences
 * Returns: the घातer transition that has last happened
 *
 * This function can वापस the following transitions-
 * any state to ApReset,  ApDeepSleep to ApExecute, ApExecute to ApDeepSleep
 */
क्रमागत romcode_पढ़ो prcmu_get_rc_p2a(व्योम)
अणु
	वापस पढ़ोb(tcdm_base + PRCM_ROMCODE_P2A);
पूर्ण

/**
 * prcmu_get_current_mode - Return the current XP70 घातer mode
 * Returns: Returns the current AP(ARM) घातer mode: init,
 * apBoot, apExecute, apDeepSleep, apSleep, apIdle, apReset
 */
क्रमागत ap_pwrst prcmu_get_xp70_current_state(व्योम)
अणु
	वापस पढ़ोb(tcdm_base + PRCM_XP70_CUR_PWR_STATE);
पूर्ण

/**
 * prcmu_config_clkout - Configure one of the programmable घड़ी outमाला_दो.
 * @clkout:	The CLKOUT number (0 or 1).
 * @source:	The घड़ी to be used (one of the PRCMU_CLKSRC_*).
 * @भाग:	The भागider to be applied.
 *
 * Configures one of the programmable घड़ी outमाला_दो (CLKOUTs).
 * @भाग should be in the range [1,63] to request a configuration, or 0 to
 * inक्रमm that the configuration is no दीर्घer requested.
 */
पूर्णांक prcmu_config_clkout(u8 clkout, u8 source, u8 भाग)
अणु
	अटल पूर्णांक requests[2];
	पूर्णांक r = 0;
	अचिन्हित दीर्घ flags;
	u32 val;
	u32 bits;
	u32 mask;
	u32 भाग_mask;

	BUG_ON(clkout > 1);
	BUG_ON(भाग > 63);
	BUG_ON((clkout == 0) && (source > PRCMU_CLKSRC_CLK009));

	अगर (!भाग && !requests[clkout])
		वापस -EINVAL;

	अगर (clkout == 0) अणु
		भाग_mask = PRCM_CLKOCR_CLKODIV0_MASK;
		mask = (PRCM_CLKOCR_CLKODIV0_MASK | PRCM_CLKOCR_CLKOSEL0_MASK);
		bits = ((source << PRCM_CLKOCR_CLKOSEL0_SHIFT) |
			(भाग << PRCM_CLKOCR_CLKODIV0_SHIFT));
	पूर्ण अन्यथा अणु
		भाग_mask = PRCM_CLKOCR_CLKODIV1_MASK;
		mask = (PRCM_CLKOCR_CLKODIV1_MASK | PRCM_CLKOCR_CLKOSEL1_MASK |
			PRCM_CLKOCR_CLK1TYPE);
		bits = ((source << PRCM_CLKOCR_CLKOSEL1_SHIFT) |
			(भाग << PRCM_CLKOCR_CLKODIV1_SHIFT));
	पूर्ण
	bits &= mask;

	spin_lock_irqsave(&clkout_lock, flags);

	val = पढ़ोl(PRCM_CLKOCR);
	अगर (val & भाग_mask) अणु
		अगर (भाग) अणु
			अगर ((val & mask) != bits) अणु
				r = -EBUSY;
				जाओ unlock_and_वापस;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर ((val & mask & ~भाग_mask) != bits) अणु
				r = -EINVAL;
				जाओ unlock_and_वापस;
			पूर्ण
		पूर्ण
	पूर्ण
	ग_लिखोl((bits | (val & ~mask)), PRCM_CLKOCR);
	requests[clkout] += (भाग ? 1 : -1);

unlock_and_वापस:
	spin_unlock_irqrestore(&clkout_lock, flags);

	वापस r;
पूर्ण

पूर्णांक db8500_prcmu_set_घातer_state(u8 state, bool keep_ulp_clk, bool keep_ap_pll)
अणु
	अचिन्हित दीर्घ flags;

	BUG_ON((state < PRCMU_AP_SLEEP) || (PRCMU_AP_DEEP_IDLE < state));

	spin_lock_irqsave(&mb0_transfer.lock, flags);

	जबतक (पढ़ोl(PRCM_MBOX_CPU_VAL) & MBOX_BIT(0))
		cpu_relax();

	ग_लिखोb(MB0H_POWER_STATE_TRANS, (tcdm_base + PRCM_MBOX_HEADER_REQ_MB0));
	ग_लिखोb(state, (tcdm_base + PRCM_REQ_MB0_AP_POWER_STATE));
	ग_लिखोb((keep_ap_pll ? 1 : 0), (tcdm_base + PRCM_REQ_MB0_AP_PLL_STATE));
	ग_लिखोb((keep_ulp_clk ? 1 : 0),
		(tcdm_base + PRCM_REQ_MB0_ULP_CLOCK_STATE));
	ग_लिखोb(0, (tcdm_base + PRCM_REQ_MB0_DO_NOT_WFI));
	ग_लिखोl(MBOX_BIT(0), PRCM_MBOX_CPU_SET);

	spin_unlock_irqrestore(&mb0_transfer.lock, flags);

	वापस 0;
पूर्ण

u8 db8500_prcmu_get_घातer_state_result(व्योम)
अणु
	वापस पढ़ोb(tcdm_base + PRCM_ACK_MB0_AP_PWRSTTR_STATUS);
पूर्ण

/* This function should only be called जबतक mb0_transfer.lock is held. */
अटल व्योम config_wakeups(व्योम)
अणु
	स्थिर u8 header[2] = अणु
		MB0H_CONFIG_WAKEUPS_EXE,
		MB0H_CONFIG_WAKEUPS_SLEEP
	पूर्ण;
	अटल u32 last_dbb_events;
	अटल u32 last_abb_events;
	u32 dbb_events;
	u32 abb_events;
	अचिन्हित पूर्णांक i;

	dbb_events = mb0_transfer.req.dbb_irqs | mb0_transfer.req.dbb_wakeups;
	dbb_events |= (WAKEUP_BIT_AC_WAKE_ACK | WAKEUP_BIT_AC_SLEEP_ACK);

	abb_events = mb0_transfer.req.abb_events;

	अगर ((dbb_events == last_dbb_events) && (abb_events == last_abb_events))
		वापस;

	क्रम (i = 0; i < 2; i++) अणु
		जबतक (पढ़ोl(PRCM_MBOX_CPU_VAL) & MBOX_BIT(0))
			cpu_relax();
		ग_लिखोl(dbb_events, (tcdm_base + PRCM_REQ_MB0_WAKEUP_8500));
		ग_लिखोl(abb_events, (tcdm_base + PRCM_REQ_MB0_WAKEUP_4500));
		ग_लिखोb(header[i], (tcdm_base + PRCM_MBOX_HEADER_REQ_MB0));
		ग_लिखोl(MBOX_BIT(0), PRCM_MBOX_CPU_SET);
	पूर्ण
	last_dbb_events = dbb_events;
	last_abb_events = abb_events;
पूर्ण

व्योम db8500_prcmu_enable_wakeups(u32 wakeups)
अणु
	अचिन्हित दीर्घ flags;
	u32 bits;
	पूर्णांक i;

	BUG_ON(wakeups != (wakeups & VALID_WAKEUPS));

	क्रम (i = 0, bits = 0; i < NUM_PRCMU_WAKEUP_INDICES; i++) अणु
		अगर (wakeups & BIT(i))
			bits |= prcmu_wakeup_bit[i];
	पूर्ण

	spin_lock_irqsave(&mb0_transfer.lock, flags);

	mb0_transfer.req.dbb_wakeups = bits;
	config_wakeups();

	spin_unlock_irqrestore(&mb0_transfer.lock, flags);
पूर्ण

व्योम db8500_prcmu_config_abb_event_पढ़ोout(u32 abb_events)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&mb0_transfer.lock, flags);

	mb0_transfer.req.abb_events = abb_events;
	config_wakeups();

	spin_unlock_irqrestore(&mb0_transfer.lock, flags);
पूर्ण

व्योम db8500_prcmu_get_abb_event_buffer(व्योम __iomem **buf)
अणु
	अगर (पढ़ोb(tcdm_base + PRCM_ACK_MB0_READ_POINTER) & 1)
		*buf = (tcdm_base + PRCM_ACK_MB0_WAKEUP_1_4500);
	अन्यथा
		*buf = (tcdm_base + PRCM_ACK_MB0_WAKEUP_0_4500);
पूर्ण

/**
 * db8500_prcmu_set_arm_opp - set the appropriate ARM OPP
 * @opp: The new ARM operating poपूर्णांक to which transition is to be made
 * Returns: 0 on success, non-zero on failure
 *
 * This function sets the the operating poपूर्णांक of the ARM.
 */
पूर्णांक db8500_prcmu_set_arm_opp(u8 opp)
अणु
	पूर्णांक r;

	अगर (opp < ARM_NO_CHANGE || opp > ARM_EXTCLK)
		वापस -EINVAL;

	r = 0;

	mutex_lock(&mb1_transfer.lock);

	जबतक (पढ़ोl(PRCM_MBOX_CPU_VAL) & MBOX_BIT(1))
		cpu_relax();

	ग_लिखोb(MB1H_ARM_APE_OPP, (tcdm_base + PRCM_MBOX_HEADER_REQ_MB1));
	ग_लिखोb(opp, (tcdm_base + PRCM_REQ_MB1_ARM_OPP));
	ग_लिखोb(APE_NO_CHANGE, (tcdm_base + PRCM_REQ_MB1_APE_OPP));

	ग_लिखोl(MBOX_BIT(1), PRCM_MBOX_CPU_SET);
	रुको_क्रम_completion(&mb1_transfer.work);

	अगर ((mb1_transfer.ack.header != MB1H_ARM_APE_OPP) ||
		(mb1_transfer.ack.arm_opp != opp))
		r = -EIO;

	mutex_unlock(&mb1_transfer.lock);

	वापस r;
पूर्ण

/**
 * db8500_prcmu_get_arm_opp - get the current ARM OPP
 *
 * Returns: the current ARM OPP
 */
पूर्णांक db8500_prcmu_get_arm_opp(व्योम)
अणु
	वापस पढ़ोb(tcdm_base + PRCM_ACK_MB1_CURRENT_ARM_OPP);
पूर्ण

/**
 * db8500_prcmu_get_ddr_opp - get the current DDR OPP
 *
 * Returns: the current DDR OPP
 */
पूर्णांक db8500_prcmu_get_ddr_opp(व्योम)
अणु
	वापस पढ़ोb(PRCM_DDR_SUBSYS_APE_MINBW);
पूर्ण

/* Divide the frequency of certain घड़ीs by 2 क्रम APE_50_PARTLY_25_OPP. */
अटल व्योम request_even_slower_घड़ीs(bool enable)
अणु
	u32 घड़ी_reg[] = अणु
		PRCM_ACLK_MGT,
		PRCM_DMACLK_MGT
	पूर्ण;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक i;

	spin_lock_irqsave(&clk_mgt_lock, flags);

	/* Grab the HW semaphore. */
	जबतक ((पढ़ोl(PRCM_SEM) & PRCM_SEM_PRCM_SEM) != 0)
		cpu_relax();

	क्रम (i = 0; i < ARRAY_SIZE(घड़ी_reg); i++) अणु
		u32 val;
		u32 भाग;

		val = पढ़ोl(prcmu_base + घड़ी_reg[i]);
		भाग = (val & PRCM_CLK_MGT_CLKPLLDIV_MASK);
		अगर (enable) अणु
			अगर ((भाग <= 1) || (भाग > 15)) अणु
				pr_err("prcmu: Bad clock divider %d in %s\n",
					भाग, __func__);
				जाओ unlock_and_वापस;
			पूर्ण
			भाग <<= 1;
		पूर्ण अन्यथा अणु
			अगर (भाग <= 2)
				जाओ unlock_and_वापस;
			भाग >>= 1;
		पूर्ण
		val = ((val & ~PRCM_CLK_MGT_CLKPLLDIV_MASK) |
			(भाग & PRCM_CLK_MGT_CLKPLLDIV_MASK));
		ग_लिखोl(val, prcmu_base + घड़ी_reg[i]);
	पूर्ण

unlock_and_वापस:
	/* Release the HW semaphore. */
	ग_लिखोl(0, PRCM_SEM);

	spin_unlock_irqrestore(&clk_mgt_lock, flags);
पूर्ण

/**
 * db8500_set_ape_opp - set the appropriate APE OPP
 * @opp: The new APE operating poपूर्णांक to which transition is to be made
 * Returns: 0 on success, non-zero on failure
 *
 * This function sets the operating poपूर्णांक of the APE.
 */
पूर्णांक db8500_prcmu_set_ape_opp(u8 opp)
अणु
	पूर्णांक r = 0;

	अगर (opp == mb1_transfer.ape_opp)
		वापस 0;

	mutex_lock(&mb1_transfer.lock);

	अगर (mb1_transfer.ape_opp == APE_50_PARTLY_25_OPP)
		request_even_slower_घड़ीs(false);

	अगर ((opp != APE_100_OPP) && (mb1_transfer.ape_opp != APE_100_OPP))
		जाओ skip_message;

	जबतक (पढ़ोl(PRCM_MBOX_CPU_VAL) & MBOX_BIT(1))
		cpu_relax();

	ग_लिखोb(MB1H_ARM_APE_OPP, (tcdm_base + PRCM_MBOX_HEADER_REQ_MB1));
	ग_लिखोb(ARM_NO_CHANGE, (tcdm_base + PRCM_REQ_MB1_ARM_OPP));
	ग_लिखोb(((opp == APE_50_PARTLY_25_OPP) ? APE_50_OPP : opp),
		(tcdm_base + PRCM_REQ_MB1_APE_OPP));

	ग_लिखोl(MBOX_BIT(1), PRCM_MBOX_CPU_SET);
	रुको_क्रम_completion(&mb1_transfer.work);

	अगर ((mb1_transfer.ack.header != MB1H_ARM_APE_OPP) ||
		(mb1_transfer.ack.ape_opp != opp))
		r = -EIO;

skip_message:
	अगर ((!r && (opp == APE_50_PARTLY_25_OPP)) ||
		(r && (mb1_transfer.ape_opp == APE_50_PARTLY_25_OPP)))
		request_even_slower_घड़ीs(true);
	अगर (!r)
		mb1_transfer.ape_opp = opp;

	mutex_unlock(&mb1_transfer.lock);

	वापस r;
पूर्ण

/**
 * db8500_prcmu_get_ape_opp - get the current APE OPP
 *
 * Returns: the current APE OPP
 */
पूर्णांक db8500_prcmu_get_ape_opp(व्योम)
अणु
	वापस पढ़ोb(tcdm_base + PRCM_ACK_MB1_CURRENT_APE_OPP);
पूर्ण

/**
 * db8500_prcmu_request_ape_opp_100_voltage - Request APE OPP 100% voltage
 * @enable: true to request the higher voltage, false to drop a request.
 *
 * Calls to this function to enable and disable requests must be balanced.
 */
पूर्णांक db8500_prcmu_request_ape_opp_100_voltage(bool enable)
अणु
	पूर्णांक r = 0;
	u8 header;
	अटल अचिन्हित पूर्णांक requests;

	mutex_lock(&mb1_transfer.lock);

	अगर (enable) अणु
		अगर (0 != requests++)
			जाओ unlock_and_वापस;
		header = MB1H_REQUEST_APE_OPP_100_VOLT;
	पूर्ण अन्यथा अणु
		अगर (requests == 0) अणु
			r = -EIO;
			जाओ unlock_and_वापस;
		पूर्ण अन्यथा अगर (1 != requests--) अणु
			जाओ unlock_and_वापस;
		पूर्ण
		header = MB1H_RELEASE_APE_OPP_100_VOLT;
	पूर्ण

	जबतक (पढ़ोl(PRCM_MBOX_CPU_VAL) & MBOX_BIT(1))
		cpu_relax();

	ग_लिखोb(header, (tcdm_base + PRCM_MBOX_HEADER_REQ_MB1));

	ग_लिखोl(MBOX_BIT(1), PRCM_MBOX_CPU_SET);
	रुको_क्रम_completion(&mb1_transfer.work);

	अगर ((mb1_transfer.ack.header != header) ||
		((mb1_transfer.ack.ape_voltage_status & BIT(0)) != 0))
		r = -EIO;

unlock_and_वापस:
	mutex_unlock(&mb1_transfer.lock);

	वापस r;
पूर्ण

/**
 * prcmu_release_usb_wakeup_state - release the state required by a USB wakeup
 *
 * This function releases the घातer state requirements of a USB wakeup.
 */
पूर्णांक prcmu_release_usb_wakeup_state(व्योम)
अणु
	पूर्णांक r = 0;

	mutex_lock(&mb1_transfer.lock);

	जबतक (पढ़ोl(PRCM_MBOX_CPU_VAL) & MBOX_BIT(1))
		cpu_relax();

	ग_लिखोb(MB1H_RELEASE_USB_WAKEUP,
		(tcdm_base + PRCM_MBOX_HEADER_REQ_MB1));

	ग_लिखोl(MBOX_BIT(1), PRCM_MBOX_CPU_SET);
	रुको_क्रम_completion(&mb1_transfer.work);

	अगर ((mb1_transfer.ack.header != MB1H_RELEASE_USB_WAKEUP) ||
		((mb1_transfer.ack.ape_voltage_status & BIT(0)) != 0))
		r = -EIO;

	mutex_unlock(&mb1_transfer.lock);

	वापस r;
पूर्ण

अटल पूर्णांक request_pll(u8 घड़ी, bool enable)
अणु
	पूर्णांक r = 0;

	अगर (घड़ी == PRCMU_PLLSOC0)
		घड़ी = (enable ? PLL_SOC0_ON : PLL_SOC0_OFF);
	अन्यथा अगर (घड़ी == PRCMU_PLLSOC1)
		घड़ी = (enable ? PLL_SOC1_ON : PLL_SOC1_OFF);
	अन्यथा
		वापस -EINVAL;

	mutex_lock(&mb1_transfer.lock);

	जबतक (पढ़ोl(PRCM_MBOX_CPU_VAL) & MBOX_BIT(1))
		cpu_relax();

	ग_लिखोb(MB1H_PLL_ON_OFF, (tcdm_base + PRCM_MBOX_HEADER_REQ_MB1));
	ग_लिखोb(घड़ी, (tcdm_base + PRCM_REQ_MB1_PLL_ON_OFF));

	ग_लिखोl(MBOX_BIT(1), PRCM_MBOX_CPU_SET);
	रुको_क्रम_completion(&mb1_transfer.work);

	अगर (mb1_transfer.ack.header != MB1H_PLL_ON_OFF)
		r = -EIO;

	mutex_unlock(&mb1_transfer.lock);

	वापस r;
पूर्ण

/**
 * db8500_prcmu_set_epod - set the state of a EPOD (घातer करोमुख्य)
 * @epod_id: The EPOD to set
 * @epod_state: The new EPOD state
 *
 * This function sets the state of a EPOD (घातer करोमुख्य). It may not be called
 * from पूर्णांकerrupt context.
 */
पूर्णांक db8500_prcmu_set_epod(u16 epod_id, u8 epod_state)
अणु
	पूर्णांक r = 0;
	bool ram_retention = false;
	पूर्णांक i;

	/* check argument */
	BUG_ON(epod_id >= NUM_EPOD_ID);

	/* set flag अगर retention is possible */
	चयन (epod_id) अणु
	हाल EPOD_ID_SVAMMDSP:
	हाल EPOD_ID_SIAMMDSP:
	हाल EPOD_ID_ESRAM12:
	हाल EPOD_ID_ESRAM34:
		ram_retention = true;
		अवरोध;
	पूर्ण

	/* check argument */
	BUG_ON(epod_state > EPOD_STATE_ON);
	BUG_ON(epod_state == EPOD_STATE_RAMRET && !ram_retention);

	/* get lock */
	mutex_lock(&mb2_transfer.lock);

	/* रुको क्रम mailbox */
	जबतक (पढ़ोl(PRCM_MBOX_CPU_VAL) & MBOX_BIT(2))
		cpu_relax();

	/* fill in mailbox */
	क्रम (i = 0; i < NUM_EPOD_ID; i++)
		ग_लिखोb(EPOD_STATE_NO_CHANGE, (tcdm_base + PRCM_REQ_MB2 + i));
	ग_लिखोb(epod_state, (tcdm_base + PRCM_REQ_MB2 + epod_id));

	ग_लिखोb(MB2H_DPS, (tcdm_base + PRCM_MBOX_HEADER_REQ_MB2));

	ग_लिखोl(MBOX_BIT(2), PRCM_MBOX_CPU_SET);

	/*
	 * The current firmware version करोes not handle errors correctly,
	 * and we cannot recover अगर there is an error.
	 * This is expected to change when the firmware is updated.
	 */
	अगर (!रुको_क्रम_completion_समयout(&mb2_transfer.work,
			msecs_to_jअगरfies(20000))) अणु
		pr_err("prcmu: %s timed out (20 s) waiting for a reply.\n",
			__func__);
		r = -EIO;
		जाओ unlock_and_वापस;
	पूर्ण

	अगर (mb2_transfer.ack.status != HWACC_PWR_ST_OK)
		r = -EIO;

unlock_and_वापस:
	mutex_unlock(&mb2_transfer.lock);
	वापस r;
पूर्ण

/**
 * prcmu_configure_स्वतः_pm - Configure स्वतःnomous घातer management.
 * @sleep: Configuration क्रम ApSleep.
 * @idle:  Configuration क्रम ApIdle.
 */
व्योम prcmu_configure_स्वतः_pm(काष्ठा prcmu_स्वतः_pm_config *sleep,
	काष्ठा prcmu_स्वतः_pm_config *idle)
अणु
	u32 sleep_cfg;
	u32 idle_cfg;
	अचिन्हित दीर्घ flags;

	BUG_ON((sleep == शून्य) || (idle == शून्य));

	sleep_cfg = (sleep->sva_स्वतः_pm_enable & 0xF);
	sleep_cfg = ((sleep_cfg << 4) | (sleep->sia_स्वतः_pm_enable & 0xF));
	sleep_cfg = ((sleep_cfg << 8) | (sleep->sva_घातer_on & 0xFF));
	sleep_cfg = ((sleep_cfg << 8) | (sleep->sia_घातer_on & 0xFF));
	sleep_cfg = ((sleep_cfg << 4) | (sleep->sva_policy & 0xF));
	sleep_cfg = ((sleep_cfg << 4) | (sleep->sia_policy & 0xF));

	idle_cfg = (idle->sva_स्वतः_pm_enable & 0xF);
	idle_cfg = ((idle_cfg << 4) | (idle->sia_स्वतः_pm_enable & 0xF));
	idle_cfg = ((idle_cfg << 8) | (idle->sva_घातer_on & 0xFF));
	idle_cfg = ((idle_cfg << 8) | (idle->sia_घातer_on & 0xFF));
	idle_cfg = ((idle_cfg << 4) | (idle->sva_policy & 0xF));
	idle_cfg = ((idle_cfg << 4) | (idle->sia_policy & 0xF));

	spin_lock_irqsave(&mb2_transfer.स्वतः_pm_lock, flags);

	/*
	 * The स्वतःnomous घातer management configuration is करोne through
	 * fields in mailbox 2, but these fields are only used as shared
	 * variables - i.e. there is no need to send a message.
	 */
	ग_लिखोl(sleep_cfg, (tcdm_base + PRCM_REQ_MB2_AUTO_PM_SLEEP));
	ग_लिखोl(idle_cfg, (tcdm_base + PRCM_REQ_MB2_AUTO_PM_IDLE));

	mb2_transfer.स्वतः_pm_enabled =
		((sleep->sva_स्वतः_pm_enable == PRCMU_AUTO_PM_ON) ||
		 (sleep->sia_स्वतः_pm_enable == PRCMU_AUTO_PM_ON) ||
		 (idle->sva_स्वतः_pm_enable == PRCMU_AUTO_PM_ON) ||
		 (idle->sia_स्वतः_pm_enable == PRCMU_AUTO_PM_ON));

	spin_unlock_irqrestore(&mb2_transfer.स्वतः_pm_lock, flags);
पूर्ण
EXPORT_SYMBOL(prcmu_configure_स्वतः_pm);

bool prcmu_is_स्वतः_pm_enabled(व्योम)
अणु
	वापस mb2_transfer.स्वतः_pm_enabled;
पूर्ण

अटल पूर्णांक request_sysclk(bool enable)
अणु
	पूर्णांक r;
	अचिन्हित दीर्घ flags;

	r = 0;

	mutex_lock(&mb3_transfer.sysclk_lock);

	spin_lock_irqsave(&mb3_transfer.lock, flags);

	जबतक (पढ़ोl(PRCM_MBOX_CPU_VAL) & MBOX_BIT(3))
		cpu_relax();

	ग_लिखोb((enable ? ON : OFF), (tcdm_base + PRCM_REQ_MB3_SYSCLK_MGT));

	ग_लिखोb(MB3H_SYSCLK, (tcdm_base + PRCM_MBOX_HEADER_REQ_MB3));
	ग_लिखोl(MBOX_BIT(3), PRCM_MBOX_CPU_SET);

	spin_unlock_irqrestore(&mb3_transfer.lock, flags);

	/*
	 * The firmware only sends an ACK अगर we want to enable the
	 * SysClk, and it succeeds.
	 */
	अगर (enable && !रुको_क्रम_completion_समयout(&mb3_transfer.sysclk_work,
			msecs_to_jअगरfies(20000))) अणु
		pr_err("prcmu: %s timed out (20 s) waiting for a reply.\n",
			__func__);
		r = -EIO;
	पूर्ण

	mutex_unlock(&mb3_transfer.sysclk_lock);

	वापस r;
पूर्ण

अटल पूर्णांक request_timclk(bool enable)
अणु
	u32 val;

	/*
	 * On the U8420_CLKSEL firmware, the ULP (Ultra Low Power)
	 * PLL is disabled so we cannot use करोze mode, this will
	 * stop the घड़ी on this firmware.
	 */
	अगर (prcmu_is_ulppll_disabled())
		val = 0;
	अन्यथा
		val = (PRCM_TCR_DOZE_MODE | PRCM_TCR_TENSEL_MASK);

	अगर (!enable)
		val |= PRCM_TCR_STOP_TIMERS |
			PRCM_TCR_DOZE_MODE |
			PRCM_TCR_TENSEL_MASK;

	ग_लिखोl(val, PRCM_TCR);

	वापस 0;
पूर्ण

अटल पूर्णांक request_घड़ी(u8 घड़ी, bool enable)
अणु
	u32 val;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&clk_mgt_lock, flags);

	/* Grab the HW semaphore. */
	जबतक ((पढ़ोl(PRCM_SEM) & PRCM_SEM_PRCM_SEM) != 0)
		cpu_relax();

	val = पढ़ोl(prcmu_base + clk_mgt[घड़ी].offset);
	अगर (enable) अणु
		val |= (PRCM_CLK_MGT_CLKEN | clk_mgt[घड़ी].pllsw);
	पूर्ण अन्यथा अणु
		clk_mgt[घड़ी].pllsw = (val & PRCM_CLK_MGT_CLKPLLSW_MASK);
		val &= ~(PRCM_CLK_MGT_CLKEN | PRCM_CLK_MGT_CLKPLLSW_MASK);
	पूर्ण
	ग_लिखोl(val, prcmu_base + clk_mgt[घड़ी].offset);

	/* Release the HW semaphore. */
	ग_लिखोl(0, PRCM_SEM);

	spin_unlock_irqrestore(&clk_mgt_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक request_sga_घड़ी(u8 घड़ी, bool enable)
अणु
	u32 val;
	पूर्णांक ret;

	अगर (enable) अणु
		val = पढ़ोl(PRCM_CGATING_BYPASS);
		ग_लिखोl(val | PRCM_CGATING_BYPASS_ICN2, PRCM_CGATING_BYPASS);
	पूर्ण

	ret = request_घड़ी(घड़ी, enable);

	अगर (!ret && !enable) अणु
		val = पढ़ोl(PRCM_CGATING_BYPASS);
		ग_लिखोl(val & ~PRCM_CGATING_BYPASS_ICN2, PRCM_CGATING_BYPASS);
	पूर्ण

	वापस ret;
पूर्ण

अटल अंतरभूत bool plldsi_locked(व्योम)
अणु
	वापस (पढ़ोl(PRCM_PLLDSI_LOCKP) &
		(PRCM_PLLDSI_LOCKP_PRCM_PLLDSI_LOCKP10 |
		 PRCM_PLLDSI_LOCKP_PRCM_PLLDSI_LOCKP3)) ==
		(PRCM_PLLDSI_LOCKP_PRCM_PLLDSI_LOCKP10 |
		 PRCM_PLLDSI_LOCKP_PRCM_PLLDSI_LOCKP3);
पूर्ण

अटल पूर्णांक request_plldsi(bool enable)
अणु
	पूर्णांक r = 0;
	u32 val;

	ग_लिखोl((PRCM_MMIP_LS_CLAMP_DSIPLL_CLAMP |
		PRCM_MMIP_LS_CLAMP_DSIPLL_CLAMPI), (enable ?
		PRCM_MMIP_LS_CLAMP_CLR : PRCM_MMIP_LS_CLAMP_SET));

	val = पढ़ोl(PRCM_PLLDSI_ENABLE);
	अगर (enable)
		val |= PRCM_PLLDSI_ENABLE_PRCM_PLLDSI_ENABLE;
	अन्यथा
		val &= ~PRCM_PLLDSI_ENABLE_PRCM_PLLDSI_ENABLE;
	ग_लिखोl(val, PRCM_PLLDSI_ENABLE);

	अगर (enable) अणु
		अचिन्हित पूर्णांक i;
		bool locked = plldsi_locked();

		क्रम (i = 10; !locked && (i > 0); --i) अणु
			udelay(100);
			locked = plldsi_locked();
		पूर्ण
		अगर (locked) अणु
			ग_लिखोl(PRCM_APE_RESETN_DSIPLL_RESETN,
				PRCM_APE_RESETN_SET);
		पूर्ण अन्यथा अणु
			ग_लिखोl((PRCM_MMIP_LS_CLAMP_DSIPLL_CLAMP |
				PRCM_MMIP_LS_CLAMP_DSIPLL_CLAMPI),
				PRCM_MMIP_LS_CLAMP_SET);
			val &= ~PRCM_PLLDSI_ENABLE_PRCM_PLLDSI_ENABLE;
			ग_लिखोl(val, PRCM_PLLDSI_ENABLE);
			r = -EAGAIN;
		पूर्ण
	पूर्ण अन्यथा अणु
		ग_लिखोl(PRCM_APE_RESETN_DSIPLL_RESETN, PRCM_APE_RESETN_CLR);
	पूर्ण
	वापस r;
पूर्ण

अटल पूर्णांक request_dsiclk(u8 n, bool enable)
अणु
	u32 val;

	val = पढ़ोl(PRCM_DSI_PLLOUT_SEL);
	val &= ~dsiclk[n].भागsel_mask;
	val |= ((enable ? dsiclk[n].भागsel : PRCM_DSI_PLLOUT_SEL_OFF) <<
		dsiclk[n].भागsel_shअगरt);
	ग_लिखोl(val, PRCM_DSI_PLLOUT_SEL);
	वापस 0;
पूर्ण

अटल पूर्णांक request_dsiescclk(u8 n, bool enable)
अणु
	u32 val;

	val = पढ़ोl(PRCM_DSITVCLK_DIV);
	enable ? (val |= dsiescclk[n].en) : (val &= ~dsiescclk[n].en);
	ग_लिखोl(val, PRCM_DSITVCLK_DIV);
	वापस 0;
पूर्ण

/**
 * db8500_prcmu_request_घड़ी() - Request क्रम a घड़ी to be enabled or disabled.
 * @घड़ी:      The घड़ी क्रम which the request is made.
 * @enable:     Whether the घड़ी should be enabled (true) or disabled (false).
 *
 * This function should only be used by the घड़ी implementation.
 * Do not use it from any other place!
 */
पूर्णांक db8500_prcmu_request_घड़ी(u8 घड़ी, bool enable)
अणु
	अगर (घड़ी == PRCMU_SGACLK)
		वापस request_sga_घड़ी(घड़ी, enable);
	अन्यथा अगर (घड़ी < PRCMU_NUM_REG_CLOCKS)
		वापस request_घड़ी(घड़ी, enable);
	अन्यथा अगर (घड़ी == PRCMU_TIMCLK)
		वापस request_timclk(enable);
	अन्यथा अगर ((घड़ी == PRCMU_DSI0CLK) || (घड़ी == PRCMU_DSI1CLK))
		वापस request_dsiclk((घड़ी - PRCMU_DSI0CLK), enable);
	अन्यथा अगर ((PRCMU_DSI0ESCCLK <= घड़ी) && (घड़ी <= PRCMU_DSI2ESCCLK))
		वापस request_dsiescclk((घड़ी - PRCMU_DSI0ESCCLK), enable);
	अन्यथा अगर (घड़ी == PRCMU_PLLDSI)
		वापस request_plldsi(enable);
	अन्यथा अगर (घड़ी == PRCMU_SYSCLK)
		वापस request_sysclk(enable);
	अन्यथा अगर ((घड़ी == PRCMU_PLLSOC0) || (घड़ी == PRCMU_PLLSOC1))
		वापस request_pll(घड़ी, enable);
	अन्यथा
		वापस -EINVAL;
पूर्ण

अटल अचिन्हित दीर्घ pll_rate(व्योम __iomem *reg, अचिन्हित दीर्घ src_rate,
	पूर्णांक branch)
अणु
	u64 rate;
	u32 val;
	u32 d;
	u32 भाग = 1;

	val = पढ़ोl(reg);

	rate = src_rate;
	rate *= ((val & PRCM_PLL_FREQ_D_MASK) >> PRCM_PLL_FREQ_D_SHIFT);

	d = ((val & PRCM_PLL_FREQ_N_MASK) >> PRCM_PLL_FREQ_N_SHIFT);
	अगर (d > 1)
		भाग *= d;

	d = ((val & PRCM_PLL_FREQ_R_MASK) >> PRCM_PLL_FREQ_R_SHIFT);
	अगर (d > 1)
		भाग *= d;

	अगर (val & PRCM_PLL_FREQ_SELDIV2)
		भाग *= 2;

	अगर ((branch == PLL_FIX) || ((branch == PLL_DIV) &&
		(val & PRCM_PLL_FREQ_DIV2EN) &&
		((reg == PRCM_PLLSOC0_FREQ) ||
		 (reg == PRCM_PLLARM_FREQ) ||
		 (reg == PRCM_PLLDDR_FREQ))))
		भाग *= 2;

	(व्योम)करो_भाग(rate, भाग);

	वापस (अचिन्हित दीर्घ)rate;
पूर्ण

#घोषणा ROOT_CLOCK_RATE 38400000

अटल अचिन्हित दीर्घ घड़ी_rate(u8 घड़ी)
अणु
	u32 val;
	u32 pllsw;
	अचिन्हित दीर्घ rate = ROOT_CLOCK_RATE;

	val = पढ़ोl(prcmu_base + clk_mgt[घड़ी].offset);

	अगर (val & PRCM_CLK_MGT_CLK38) अणु
		अगर (clk_mgt[घड़ी].clk38भाग && (val & PRCM_CLK_MGT_CLK38DIV))
			rate /= 2;
		वापस rate;
	पूर्ण

	val |= clk_mgt[घड़ी].pllsw;
	pllsw = (val & PRCM_CLK_MGT_CLKPLLSW_MASK);

	अगर (pllsw == PRCM_CLK_MGT_CLKPLLSW_SOC0)
		rate = pll_rate(PRCM_PLLSOC0_FREQ, rate, clk_mgt[घड़ी].branch);
	अन्यथा अगर (pllsw == PRCM_CLK_MGT_CLKPLLSW_SOC1)
		rate = pll_rate(PRCM_PLLSOC1_FREQ, rate, clk_mgt[घड़ी].branch);
	अन्यथा अगर (pllsw == PRCM_CLK_MGT_CLKPLLSW_DDR)
		rate = pll_rate(PRCM_PLLDDR_FREQ, rate, clk_mgt[घड़ी].branch);
	अन्यथा
		वापस 0;

	अगर ((घड़ी == PRCMU_SGACLK) &&
		(val & PRCM_SGACLK_MGT_SGACLKDIV_BY_2_5_EN)) अणु
		u64 r = (rate * 10);

		(व्योम)करो_भाग(r, 25);
		वापस (अचिन्हित दीर्घ)r;
	पूर्ण
	val &= PRCM_CLK_MGT_CLKPLLDIV_MASK;
	अगर (val)
		वापस rate / val;
	अन्यथा
		वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ armss_rate(व्योम)
अणु
	u32 r;
	अचिन्हित दीर्घ rate;

	r = पढ़ोl(PRCM_ARM_CHGCLKREQ);

	अगर (r & PRCM_ARM_CHGCLKREQ_PRCM_ARM_CHGCLKREQ) अणु
		/* External ARMCLKFIX घड़ी */

		rate = pll_rate(PRCM_PLLDDR_FREQ, ROOT_CLOCK_RATE, PLL_FIX);

		/* Check PRCM_ARM_CHGCLKREQ भागider */
		अगर (!(r & PRCM_ARM_CHGCLKREQ_PRCM_ARM_DIVSEL))
			rate /= 2;

		/* Check PRCM_ARMCLKFIX_MGT भागider */
		r = पढ़ोl(PRCM_ARMCLKFIX_MGT);
		r &= PRCM_CLK_MGT_CLKPLLDIV_MASK;
		rate /= r;

	पूर्ण अन्यथा अणु/* ARM PLL */
		rate = pll_rate(PRCM_PLLARM_FREQ, ROOT_CLOCK_RATE, PLL_DIV);
	पूर्ण

	वापस rate;
पूर्ण

अटल अचिन्हित दीर्घ dsiclk_rate(u8 n)
अणु
	u32 भागsel;
	u32 भाग = 1;

	भागsel = पढ़ोl(PRCM_DSI_PLLOUT_SEL);
	भागsel = ((भागsel & dsiclk[n].भागsel_mask) >> dsiclk[n].भागsel_shअगरt);

	अगर (भागsel == PRCM_DSI_PLLOUT_SEL_OFF)
		भागsel = dsiclk[n].भागsel;
	अन्यथा
		dsiclk[n].भागsel = भागsel;

	चयन (भागsel) अणु
	हाल PRCM_DSI_PLLOUT_SEL_PHI_4:
		भाग *= 2;
		fallthrough;
	हाल PRCM_DSI_PLLOUT_SEL_PHI_2:
		भाग *= 2;
		fallthrough;
	हाल PRCM_DSI_PLLOUT_SEL_PHI:
		वापस pll_rate(PRCM_PLLDSI_FREQ, घड़ी_rate(PRCMU_HDMICLK),
			PLL_RAW) / भाग;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल अचिन्हित दीर्घ dsiescclk_rate(u8 n)
अणु
	u32 भाग;

	भाग = पढ़ोl(PRCM_DSITVCLK_DIV);
	भाग = ((भाग & dsiescclk[n].भाग_mask) >> (dsiescclk[n].भाग_shअगरt));
	वापस घड़ी_rate(PRCMU_TVCLK) / max((u32)1, भाग);
पूर्ण

अचिन्हित दीर्घ prcmu_घड़ी_rate(u8 घड़ी)
अणु
	अगर (घड़ी < PRCMU_NUM_REG_CLOCKS)
		वापस घड़ी_rate(घड़ी);
	अन्यथा अगर (घड़ी == PRCMU_TIMCLK)
		वापस prcmu_is_ulppll_disabled() ?
			32768 : ROOT_CLOCK_RATE / 16;
	अन्यथा अगर (घड़ी == PRCMU_SYSCLK)
		वापस ROOT_CLOCK_RATE;
	अन्यथा अगर (घड़ी == PRCMU_PLLSOC0)
		वापस pll_rate(PRCM_PLLSOC0_FREQ, ROOT_CLOCK_RATE, PLL_RAW);
	अन्यथा अगर (घड़ी == PRCMU_PLLSOC1)
		वापस pll_rate(PRCM_PLLSOC1_FREQ, ROOT_CLOCK_RATE, PLL_RAW);
	अन्यथा अगर (घड़ी == PRCMU_ARMSS)
		वापस armss_rate();
	अन्यथा अगर (घड़ी == PRCMU_PLLDDR)
		वापस pll_rate(PRCM_PLLDDR_FREQ, ROOT_CLOCK_RATE, PLL_RAW);
	अन्यथा अगर (घड़ी == PRCMU_PLLDSI)
		वापस pll_rate(PRCM_PLLDSI_FREQ, घड़ी_rate(PRCMU_HDMICLK),
			PLL_RAW);
	अन्यथा अगर ((घड़ी == PRCMU_DSI0CLK) || (घड़ी == PRCMU_DSI1CLK))
		वापस dsiclk_rate(घड़ी - PRCMU_DSI0CLK);
	अन्यथा अगर ((PRCMU_DSI0ESCCLK <= घड़ी) && (घड़ी <= PRCMU_DSI2ESCCLK))
		वापस dsiescclk_rate(घड़ी - PRCMU_DSI0ESCCLK);
	अन्यथा
		वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ घड़ी_source_rate(u32 clk_mgt_val, पूर्णांक branch)
अणु
	अगर (clk_mgt_val & PRCM_CLK_MGT_CLK38)
		वापस ROOT_CLOCK_RATE;
	clk_mgt_val &= PRCM_CLK_MGT_CLKPLLSW_MASK;
	अगर (clk_mgt_val == PRCM_CLK_MGT_CLKPLLSW_SOC0)
		वापस pll_rate(PRCM_PLLSOC0_FREQ, ROOT_CLOCK_RATE, branch);
	अन्यथा अगर (clk_mgt_val == PRCM_CLK_MGT_CLKPLLSW_SOC1)
		वापस pll_rate(PRCM_PLLSOC1_FREQ, ROOT_CLOCK_RATE, branch);
	अन्यथा अगर (clk_mgt_val == PRCM_CLK_MGT_CLKPLLSW_DDR)
		वापस pll_rate(PRCM_PLLDDR_FREQ, ROOT_CLOCK_RATE, branch);
	अन्यथा
		वापस 0;
पूर्ण

अटल u32 घड़ी_भागider(अचिन्हित दीर्घ src_rate, अचिन्हित दीर्घ rate)
अणु
	u32 भाग;

	भाग = (src_rate / rate);
	अगर (भाग == 0)
		वापस 1;
	अगर (rate < (src_rate / भाग))
		भाग++;
	वापस भाग;
पूर्ण

अटल दीर्घ round_घड़ी_rate(u8 घड़ी, अचिन्हित दीर्घ rate)
अणु
	u32 val;
	u32 भाग;
	अचिन्हित दीर्घ src_rate;
	दीर्घ rounded_rate;

	val = पढ़ोl(prcmu_base + clk_mgt[घड़ी].offset);
	src_rate = घड़ी_source_rate((val | clk_mgt[घड़ी].pllsw),
		clk_mgt[घड़ी].branch);
	भाग = घड़ी_भागider(src_rate, rate);
	अगर (val & PRCM_CLK_MGT_CLK38) अणु
		अगर (clk_mgt[घड़ी].clk38भाग) अणु
			अगर (भाग > 2)
				भाग = 2;
		पूर्ण अन्यथा अणु
			भाग = 1;
		पूर्ण
	पूर्ण अन्यथा अगर ((घड़ी == PRCMU_SGACLK) && (भाग == 3)) अणु
		u64 r = (src_rate * 10);

		(व्योम)करो_भाग(r, 25);
		अगर (r <= rate)
			वापस (अचिन्हित दीर्घ)r;
	पूर्ण
	rounded_rate = (src_rate / min(भाग, (u32)31));

	वापस rounded_rate;
पूर्ण

अटल स्थिर अचिन्हित दीर्घ db8500_armss_freqs[] = अणु
	200000000,
	400000000,
	800000000,
	998400000
पूर्ण;

/* The DB8520 has slightly higher ARMSS max frequency */
अटल स्थिर अचिन्हित दीर्घ db8520_armss_freqs[] = अणु
	200000000,
	400000000,
	800000000,
	1152000000
पूर्ण;



अटल दीर्घ round_armss_rate(अचिन्हित दीर्घ rate)
अणु
	अचिन्हित दीर्घ freq = 0;
	स्थिर अचिन्हित दीर्घ *freqs;
	पूर्णांक nfreqs;
	पूर्णांक i;

	अगर (fw_info.version.project == PRCMU_FW_PROJECT_U8520) अणु
		freqs = db8520_armss_freqs;
		nfreqs = ARRAY_SIZE(db8520_armss_freqs);
	पूर्ण अन्यथा अणु
		freqs = db8500_armss_freqs;
		nfreqs = ARRAY_SIZE(db8500_armss_freqs);
	पूर्ण

	/* Find the corresponding arm opp from the cpufreq table. */
	क्रम (i = 0; i < nfreqs; i++) अणु
		freq = freqs[i];
		अगर (rate <= freq)
			अवरोध;
	पूर्ण

	/* Return the last valid value, even अगर a match was not found. */
	वापस freq;
पूर्ण

#घोषणा MIN_PLL_VCO_RATE 600000000ULL
#घोषणा MAX_PLL_VCO_RATE 1680640000ULL

अटल दीर्घ round_plldsi_rate(अचिन्हित दीर्घ rate)
अणु
	दीर्घ rounded_rate = 0;
	अचिन्हित दीर्घ src_rate;
	अचिन्हित दीर्घ rem;
	u32 r;

	src_rate = घड़ी_rate(PRCMU_HDMICLK);
	rem = rate;

	क्रम (r = 7; (rem > 0) && (r > 0); r--) अणु
		u64 d;

		d = (r * rate);
		(व्योम)करो_भाग(d, src_rate);
		अगर (d < 6)
			d = 6;
		अन्यथा अगर (d > 255)
			d = 255;
		d *= src_rate;
		अगर (((2 * d) < (r * MIN_PLL_VCO_RATE)) ||
			((r * MAX_PLL_VCO_RATE) < (2 * d)))
			जारी;
		(व्योम)करो_भाग(d, r);
		अगर (rate < d) अणु
			अगर (rounded_rate == 0)
				rounded_rate = (दीर्घ)d;
			अवरोध;
		पूर्ण
		अगर ((rate - d) < rem) अणु
			rem = (rate - d);
			rounded_rate = (दीर्घ)d;
		पूर्ण
	पूर्ण
	वापस rounded_rate;
पूर्ण

अटल दीर्घ round_dsiclk_rate(अचिन्हित दीर्घ rate)
अणु
	u32 भाग;
	अचिन्हित दीर्घ src_rate;
	दीर्घ rounded_rate;

	src_rate = pll_rate(PRCM_PLLDSI_FREQ, घड़ी_rate(PRCMU_HDMICLK),
		PLL_RAW);
	भाग = घड़ी_भागider(src_rate, rate);
	rounded_rate = (src_rate / ((भाग > 2) ? 4 : भाग));

	वापस rounded_rate;
पूर्ण

अटल दीर्घ round_dsiescclk_rate(अचिन्हित दीर्घ rate)
अणु
	u32 भाग;
	अचिन्हित दीर्घ src_rate;
	दीर्घ rounded_rate;

	src_rate = घड़ी_rate(PRCMU_TVCLK);
	भाग = घड़ी_भागider(src_rate, rate);
	rounded_rate = (src_rate / min(भाग, (u32)255));

	वापस rounded_rate;
पूर्ण

दीर्घ prcmu_round_घड़ी_rate(u8 घड़ी, अचिन्हित दीर्घ rate)
अणु
	अगर (घड़ी < PRCMU_NUM_REG_CLOCKS)
		वापस round_घड़ी_rate(घड़ी, rate);
	अन्यथा अगर (घड़ी == PRCMU_ARMSS)
		वापस round_armss_rate(rate);
	अन्यथा अगर (घड़ी == PRCMU_PLLDSI)
		वापस round_plldsi_rate(rate);
	अन्यथा अगर ((घड़ी == PRCMU_DSI0CLK) || (घड़ी == PRCMU_DSI1CLK))
		वापस round_dsiclk_rate(rate);
	अन्यथा अगर ((PRCMU_DSI0ESCCLK <= घड़ी) && (घड़ी <= PRCMU_DSI2ESCCLK))
		वापस round_dsiescclk_rate(rate);
	अन्यथा
		वापस (दीर्घ)prcmu_घड़ी_rate(घड़ी);
पूर्ण

अटल व्योम set_घड़ी_rate(u8 घड़ी, अचिन्हित दीर्घ rate)
अणु
	u32 val;
	u32 भाग;
	अचिन्हित दीर्घ src_rate;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&clk_mgt_lock, flags);

	/* Grab the HW semaphore. */
	जबतक ((पढ़ोl(PRCM_SEM) & PRCM_SEM_PRCM_SEM) != 0)
		cpu_relax();

	val = पढ़ोl(prcmu_base + clk_mgt[घड़ी].offset);
	src_rate = घड़ी_source_rate((val | clk_mgt[घड़ी].pllsw),
		clk_mgt[घड़ी].branch);
	भाग = घड़ी_भागider(src_rate, rate);
	अगर (val & PRCM_CLK_MGT_CLK38) अणु
		अगर (clk_mgt[घड़ी].clk38भाग) अणु
			अगर (भाग > 1)
				val |= PRCM_CLK_MGT_CLK38DIV;
			अन्यथा
				val &= ~PRCM_CLK_MGT_CLK38DIV;
		पूर्ण
	पूर्ण अन्यथा अगर (घड़ी == PRCMU_SGACLK) अणु
		val &= ~(PRCM_CLK_MGT_CLKPLLDIV_MASK |
			PRCM_SGACLK_MGT_SGACLKDIV_BY_2_5_EN);
		अगर (भाग == 3) अणु
			u64 r = (src_rate * 10);

			(व्योम)करो_भाग(r, 25);
			अगर (r <= rate) अणु
				val |= PRCM_SGACLK_MGT_SGACLKDIV_BY_2_5_EN;
				भाग = 0;
			पूर्ण
		पूर्ण
		val |= min(भाग, (u32)31);
	पूर्ण अन्यथा अणु
		val &= ~PRCM_CLK_MGT_CLKPLLDIV_MASK;
		val |= min(भाग, (u32)31);
	पूर्ण
	ग_लिखोl(val, prcmu_base + clk_mgt[घड़ी].offset);

	/* Release the HW semaphore. */
	ग_लिखोl(0, PRCM_SEM);

	spin_unlock_irqrestore(&clk_mgt_lock, flags);
पूर्ण

अटल पूर्णांक set_armss_rate(अचिन्हित दीर्घ rate)
अणु
	अचिन्हित दीर्घ freq;
	u8 opps[] = अणु ARM_EXTCLK, ARM_50_OPP, ARM_100_OPP, ARM_MAX_OPP पूर्ण;
	स्थिर अचिन्हित दीर्घ *freqs;
	पूर्णांक nfreqs;
	पूर्णांक i;

	अगर (fw_info.version.project == PRCMU_FW_PROJECT_U8520) अणु
		freqs = db8520_armss_freqs;
		nfreqs = ARRAY_SIZE(db8520_armss_freqs);
	पूर्ण अन्यथा अणु
		freqs = db8500_armss_freqs;
		nfreqs = ARRAY_SIZE(db8500_armss_freqs);
	पूर्ण

	/* Find the corresponding arm opp from the cpufreq table. */
	क्रम (i = 0; i < nfreqs; i++) अणु
		freq = freqs[i];
		अगर (rate == freq)
			अवरोध;
	पूर्ण

	अगर (rate != freq)
		वापस -EINVAL;

	/* Set the new arm opp. */
	pr_debug("SET ARM OPP 0x%02x\n", opps[i]);
	वापस db8500_prcmu_set_arm_opp(opps[i]);
पूर्ण

अटल पूर्णांक set_plldsi_rate(अचिन्हित दीर्घ rate)
अणु
	अचिन्हित दीर्घ src_rate;
	अचिन्हित दीर्घ rem;
	u32 pll_freq = 0;
	u32 r;

	src_rate = घड़ी_rate(PRCMU_HDMICLK);
	rem = rate;

	क्रम (r = 7; (rem > 0) && (r > 0); r--) अणु
		u64 d;
		u64 hwrate;

		d = (r * rate);
		(व्योम)करो_भाग(d, src_rate);
		अगर (d < 6)
			d = 6;
		अन्यथा अगर (d > 255)
			d = 255;
		hwrate = (d * src_rate);
		अगर (((2 * hwrate) < (r * MIN_PLL_VCO_RATE)) ||
			((r * MAX_PLL_VCO_RATE) < (2 * hwrate)))
			जारी;
		(व्योम)करो_भाग(hwrate, r);
		अगर (rate < hwrate) अणु
			अगर (pll_freq == 0)
				pll_freq = (((u32)d << PRCM_PLL_FREQ_D_SHIFT) |
					(r << PRCM_PLL_FREQ_R_SHIFT));
			अवरोध;
		पूर्ण
		अगर ((rate - hwrate) < rem) अणु
			rem = (rate - hwrate);
			pll_freq = (((u32)d << PRCM_PLL_FREQ_D_SHIFT) |
				(r << PRCM_PLL_FREQ_R_SHIFT));
		पूर्ण
	पूर्ण
	अगर (pll_freq == 0)
		वापस -EINVAL;

	pll_freq |= (1 << PRCM_PLL_FREQ_N_SHIFT);
	ग_लिखोl(pll_freq, PRCM_PLLDSI_FREQ);

	वापस 0;
पूर्ण

अटल व्योम set_dsiclk_rate(u8 n, अचिन्हित दीर्घ rate)
अणु
	u32 val;
	u32 भाग;

	भाग = घड़ी_भागider(pll_rate(PRCM_PLLDSI_FREQ,
			घड़ी_rate(PRCMU_HDMICLK), PLL_RAW), rate);

	dsiclk[n].भागsel = (भाग == 1) ? PRCM_DSI_PLLOUT_SEL_PHI :
			   (भाग == 2) ? PRCM_DSI_PLLOUT_SEL_PHI_2 :
			   /* अन्यथा */	PRCM_DSI_PLLOUT_SEL_PHI_4;

	val = पढ़ोl(PRCM_DSI_PLLOUT_SEL);
	val &= ~dsiclk[n].भागsel_mask;
	val |= (dsiclk[n].भागsel << dsiclk[n].भागsel_shअगरt);
	ग_लिखोl(val, PRCM_DSI_PLLOUT_SEL);
पूर्ण

अटल व्योम set_dsiescclk_rate(u8 n, अचिन्हित दीर्घ rate)
अणु
	u32 val;
	u32 भाग;

	भाग = घड़ी_भागider(घड़ी_rate(PRCMU_TVCLK), rate);
	val = पढ़ोl(PRCM_DSITVCLK_DIV);
	val &= ~dsiescclk[n].भाग_mask;
	val |= (min(भाग, (u32)255) << dsiescclk[n].भाग_shअगरt);
	ग_लिखोl(val, PRCM_DSITVCLK_DIV);
पूर्ण

पूर्णांक prcmu_set_घड़ी_rate(u8 घड़ी, अचिन्हित दीर्घ rate)
अणु
	अगर (घड़ी < PRCMU_NUM_REG_CLOCKS)
		set_घड़ी_rate(घड़ी, rate);
	अन्यथा अगर (घड़ी == PRCMU_ARMSS)
		वापस set_armss_rate(rate);
	अन्यथा अगर (घड़ी == PRCMU_PLLDSI)
		वापस set_plldsi_rate(rate);
	अन्यथा अगर ((घड़ी == PRCMU_DSI0CLK) || (घड़ी == PRCMU_DSI1CLK))
		set_dsiclk_rate((घड़ी - PRCMU_DSI0CLK), rate);
	अन्यथा अगर ((PRCMU_DSI0ESCCLK <= घड़ी) && (घड़ी <= PRCMU_DSI2ESCCLK))
		set_dsiescclk_rate((घड़ी - PRCMU_DSI0ESCCLK), rate);
	वापस 0;
पूर्ण

पूर्णांक db8500_prcmu_config_esram0_deep_sleep(u8 state)
अणु
	अगर ((state > ESRAM0_DEEP_SLEEP_STATE_RET) ||
	    (state < ESRAM0_DEEP_SLEEP_STATE_OFF))
		वापस -EINVAL;

	mutex_lock(&mb4_transfer.lock);

	जबतक (पढ़ोl(PRCM_MBOX_CPU_VAL) & MBOX_BIT(4))
		cpu_relax();

	ग_लिखोb(MB4H_MEM_ST, (tcdm_base + PRCM_MBOX_HEADER_REQ_MB4));
	ग_लिखोb(((DDR_PWR_STATE_OFFHIGHLAT << 4) | DDR_PWR_STATE_ON),
	       (tcdm_base + PRCM_REQ_MB4_DDR_ST_AP_SLEEP_IDLE));
	ग_लिखोb(DDR_PWR_STATE_ON,
	       (tcdm_base + PRCM_REQ_MB4_DDR_ST_AP_DEEP_IDLE));
	ग_लिखोb(state, (tcdm_base + PRCM_REQ_MB4_ESRAM0_ST));

	ग_लिखोl(MBOX_BIT(4), PRCM_MBOX_CPU_SET);
	रुको_क्रम_completion(&mb4_transfer.work);

	mutex_unlock(&mb4_transfer.lock);

	वापस 0;
पूर्ण

पूर्णांक db8500_prcmu_config_hotकरोg(u8 threshold)
अणु
	mutex_lock(&mb4_transfer.lock);

	जबतक (पढ़ोl(PRCM_MBOX_CPU_VAL) & MBOX_BIT(4))
		cpu_relax();

	ग_लिखोb(threshold, (tcdm_base + PRCM_REQ_MB4_HOTDOG_THRESHOLD));
	ग_लिखोb(MB4H_HOTDOG, (tcdm_base + PRCM_MBOX_HEADER_REQ_MB4));

	ग_लिखोl(MBOX_BIT(4), PRCM_MBOX_CPU_SET);
	रुको_क्रम_completion(&mb4_transfer.work);

	mutex_unlock(&mb4_transfer.lock);

	वापस 0;
पूर्ण

पूर्णांक db8500_prcmu_config_hoपंचांगon(u8 low, u8 high)
अणु
	mutex_lock(&mb4_transfer.lock);

	जबतक (पढ़ोl(PRCM_MBOX_CPU_VAL) & MBOX_BIT(4))
		cpu_relax();

	ग_लिखोb(low, (tcdm_base + PRCM_REQ_MB4_HOTMON_LOW));
	ग_लिखोb(high, (tcdm_base + PRCM_REQ_MB4_HOTMON_HIGH));
	ग_लिखोb((HOTMON_CONFIG_LOW | HOTMON_CONFIG_HIGH),
		(tcdm_base + PRCM_REQ_MB4_HOTMON_CONFIG));
	ग_लिखोb(MB4H_HOTMON, (tcdm_base + PRCM_MBOX_HEADER_REQ_MB4));

	ग_लिखोl(MBOX_BIT(4), PRCM_MBOX_CPU_SET);
	रुको_क्रम_completion(&mb4_transfer.work);

	mutex_unlock(&mb4_transfer.lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(db8500_prcmu_config_hoपंचांगon);

अटल पूर्णांक config_hot_period(u16 val)
अणु
	mutex_lock(&mb4_transfer.lock);

	जबतक (पढ़ोl(PRCM_MBOX_CPU_VAL) & MBOX_BIT(4))
		cpu_relax();

	ग_लिखोw(val, (tcdm_base + PRCM_REQ_MB4_HOT_PERIOD));
	ग_लिखोb(MB4H_HOT_PERIOD, (tcdm_base + PRCM_MBOX_HEADER_REQ_MB4));

	ग_लिखोl(MBOX_BIT(4), PRCM_MBOX_CPU_SET);
	रुको_क्रम_completion(&mb4_transfer.work);

	mutex_unlock(&mb4_transfer.lock);

	वापस 0;
पूर्ण

पूर्णांक db8500_prcmu_start_temp_sense(u16 cycles32k)
अणु
	अगर (cycles32k == 0xFFFF)
		वापस -EINVAL;

	वापस config_hot_period(cycles32k);
पूर्ण
EXPORT_SYMBOL_GPL(db8500_prcmu_start_temp_sense);

पूर्णांक db8500_prcmu_stop_temp_sense(व्योम)
अणु
	वापस config_hot_period(0xFFFF);
पूर्ण
EXPORT_SYMBOL_GPL(db8500_prcmu_stop_temp_sense);

अटल पूर्णांक prcmu_a9wकरोg(u8 cmd, u8 d0, u8 d1, u8 d2, u8 d3)
अणु

	mutex_lock(&mb4_transfer.lock);

	जबतक (पढ़ोl(PRCM_MBOX_CPU_VAL) & MBOX_BIT(4))
		cpu_relax();

	ग_लिखोb(d0, (tcdm_base + PRCM_REQ_MB4_A9WDOG_0));
	ग_लिखोb(d1, (tcdm_base + PRCM_REQ_MB4_A9WDOG_1));
	ग_लिखोb(d2, (tcdm_base + PRCM_REQ_MB4_A9WDOG_2));
	ग_लिखोb(d3, (tcdm_base + PRCM_REQ_MB4_A9WDOG_3));

	ग_लिखोb(cmd, (tcdm_base + PRCM_MBOX_HEADER_REQ_MB4));

	ग_लिखोl(MBOX_BIT(4), PRCM_MBOX_CPU_SET);
	रुको_क्रम_completion(&mb4_transfer.work);

	mutex_unlock(&mb4_transfer.lock);

	वापस 0;

पूर्ण

पूर्णांक db8500_prcmu_config_a9wकरोg(u8 num, bool sleep_स्वतः_off)
अणु
	BUG_ON(num == 0 || num > 0xf);
	वापस prcmu_a9wकरोg(MB4H_A9WDOG_CONF, num, 0, 0,
			    sleep_स्वतः_off ? A9WDOG_AUTO_OFF_EN :
			    A9WDOG_AUTO_OFF_DIS);
पूर्ण
EXPORT_SYMBOL(db8500_prcmu_config_a9wकरोg);

पूर्णांक db8500_prcmu_enable_a9wकरोg(u8 id)
अणु
	वापस prcmu_a9wकरोg(MB4H_A9WDOG_EN, id, 0, 0, 0);
पूर्ण
EXPORT_SYMBOL(db8500_prcmu_enable_a9wकरोg);

पूर्णांक db8500_prcmu_disable_a9wकरोg(u8 id)
अणु
	वापस prcmu_a9wकरोg(MB4H_A9WDOG_DIS, id, 0, 0, 0);
पूर्ण
EXPORT_SYMBOL(db8500_prcmu_disable_a9wकरोg);

पूर्णांक db8500_prcmu_kick_a9wकरोg(u8 id)
अणु
	वापस prcmu_a9wकरोg(MB4H_A9WDOG_KICK, id, 0, 0, 0);
पूर्ण
EXPORT_SYMBOL(db8500_prcmu_kick_a9wकरोg);

/*
 * समयout is 28 bit, in ms.
 */
पूर्णांक db8500_prcmu_load_a9wकरोg(u8 id, u32 समयout)
अणु
	वापस prcmu_a9wकरोg(MB4H_A9WDOG_LOAD,
			    (id & A9WDOG_ID_MASK) |
			    /*
			     * Put the lowest 28 bits of समयout at
			     * offset 4. Four first bits are used क्रम id.
			     */
			    (u8)((समयout << 4) & 0xf0),
			    (u8)((समयout >> 4) & 0xff),
			    (u8)((समयout >> 12) & 0xff),
			    (u8)((समयout >> 20) & 0xff));
पूर्ण
EXPORT_SYMBOL(db8500_prcmu_load_a9wकरोg);

/**
 * prcmu_abb_पढ़ो() - Read रेजिस्टर value(s) from the ABB.
 * @slave:	The I2C slave address.
 * @reg:	The (start) रेजिस्टर address.
 * @value:	The पढ़ो out value(s).
 * @size:	The number of रेजिस्टरs to पढ़ो.
 *
 * Reads रेजिस्टर value(s) from the ABB.
 * @size has to be 1 क्रम the current firmware version.
 */
पूर्णांक prcmu_abb_पढ़ो(u8 slave, u8 reg, u8 *value, u8 size)
अणु
	पूर्णांक r;

	अगर (size != 1)
		वापस -EINVAL;

	mutex_lock(&mb5_transfer.lock);

	जबतक (पढ़ोl(PRCM_MBOX_CPU_VAL) & MBOX_BIT(5))
		cpu_relax();

	ग_लिखोb(0, (tcdm_base + PRCM_MBOX_HEADER_REQ_MB5));
	ग_लिखोb(PRCMU_I2C_READ(slave), (tcdm_base + PRCM_REQ_MB5_I2C_SLAVE_OP));
	ग_लिखोb(PRCMU_I2C_STOP_EN, (tcdm_base + PRCM_REQ_MB5_I2C_HW_BITS));
	ग_लिखोb(reg, (tcdm_base + PRCM_REQ_MB5_I2C_REG));
	ग_लिखोb(0, (tcdm_base + PRCM_REQ_MB5_I2C_VAL));

	ग_लिखोl(MBOX_BIT(5), PRCM_MBOX_CPU_SET);

	अगर (!रुको_क्रम_completion_समयout(&mb5_transfer.work,
				msecs_to_jअगरfies(20000))) अणु
		pr_err("prcmu: %s timed out (20 s) waiting for a reply.\n",
			__func__);
		r = -EIO;
	पूर्ण अन्यथा अणु
		r = ((mb5_transfer.ack.status == I2C_RD_OK) ? 0 : -EIO);
	पूर्ण

	अगर (!r)
		*value = mb5_transfer.ack.value;

	mutex_unlock(&mb5_transfer.lock);

	वापस r;
पूर्ण

/**
 * prcmu_abb_ग_लिखो_masked() - Write masked रेजिस्टर value(s) to the ABB.
 * @slave:	The I2C slave address.
 * @reg:	The (start) रेजिस्टर address.
 * @value:	The value(s) to ग_लिखो.
 * @mask:	The mask(s) to use.
 * @size:	The number of रेजिस्टरs to ग_लिखो.
 *
 * Writes masked रेजिस्टर value(s) to the ABB.
 * For each @value, only the bits set to 1 in the corresponding @mask
 * will be written. The other bits are not changed.
 * @size has to be 1 क्रम the current firmware version.
 */
पूर्णांक prcmu_abb_ग_लिखो_masked(u8 slave, u8 reg, u8 *value, u8 *mask, u8 size)
अणु
	पूर्णांक r;

	अगर (size != 1)
		वापस -EINVAL;

	mutex_lock(&mb5_transfer.lock);

	जबतक (पढ़ोl(PRCM_MBOX_CPU_VAL) & MBOX_BIT(5))
		cpu_relax();

	ग_लिखोb(~*mask, (tcdm_base + PRCM_MBOX_HEADER_REQ_MB5));
	ग_लिखोb(PRCMU_I2C_WRITE(slave), (tcdm_base + PRCM_REQ_MB5_I2C_SLAVE_OP));
	ग_लिखोb(PRCMU_I2C_STOP_EN, (tcdm_base + PRCM_REQ_MB5_I2C_HW_BITS));
	ग_लिखोb(reg, (tcdm_base + PRCM_REQ_MB5_I2C_REG));
	ग_लिखोb(*value, (tcdm_base + PRCM_REQ_MB5_I2C_VAL));

	ग_लिखोl(MBOX_BIT(5), PRCM_MBOX_CPU_SET);

	अगर (!रुको_क्रम_completion_समयout(&mb5_transfer.work,
				msecs_to_jअगरfies(20000))) अणु
		pr_err("prcmu: %s timed out (20 s) waiting for a reply.\n",
			__func__);
		r = -EIO;
	पूर्ण अन्यथा अणु
		r = ((mb5_transfer.ack.status == I2C_WR_OK) ? 0 : -EIO);
	पूर्ण

	mutex_unlock(&mb5_transfer.lock);

	वापस r;
पूर्ण

/**
 * prcmu_abb_ग_लिखो() - Write रेजिस्टर value(s) to the ABB.
 * @slave:	The I2C slave address.
 * @reg:	The (start) रेजिस्टर address.
 * @value:	The value(s) to ग_लिखो.
 * @size:	The number of रेजिस्टरs to ग_लिखो.
 *
 * Writes रेजिस्टर value(s) to the ABB.
 * @size has to be 1 क्रम the current firmware version.
 */
पूर्णांक prcmu_abb_ग_लिखो(u8 slave, u8 reg, u8 *value, u8 size)
अणु
	u8 mask = ~0;

	वापस prcmu_abb_ग_लिखो_masked(slave, reg, value, &mask, size);
पूर्ण

/**
 * prcmu_ac_wake_req - should be called whenever ARM wants to wakeup Modem
 */
पूर्णांक prcmu_ac_wake_req(व्योम)
अणु
	u32 val;
	पूर्णांक ret = 0;

	mutex_lock(&mb0_transfer.ac_wake_lock);

	val = पढ़ोl(PRCM_HOSTACCESS_REQ);
	अगर (val & PRCM_HOSTACCESS_REQ_HOSTACCESS_REQ)
		जाओ unlock_and_वापस;

	atomic_set(&ac_wake_req_state, 1);

	/*
	 * Force Modem Wake-up beक्रमe hostaccess_req ping-pong.
	 * It prevents Modem to enter in Sleep जबतक acking the hostaccess
	 * request. The 31us delay has been calculated by HWI.
	 */
	val |= PRCM_HOSTACCESS_REQ_WAKE_REQ;
	ग_लिखोl(val, PRCM_HOSTACCESS_REQ);

	udelay(31);

	val |= PRCM_HOSTACCESS_REQ_HOSTACCESS_REQ;
	ग_लिखोl(val, PRCM_HOSTACCESS_REQ);

	अगर (!रुको_क्रम_completion_समयout(&mb0_transfer.ac_wake_work,
			msecs_to_jअगरfies(5000))) अणु
		pr_crit("prcmu: %s timed out (5 s) waiting for a reply.\n",
			__func__);
		ret = -EFAULT;
	पूर्ण

unlock_and_वापस:
	mutex_unlock(&mb0_transfer.ac_wake_lock);
	वापस ret;
पूर्ण

/**
 * prcmu_ac_sleep_req - called when ARM no दीर्घer needs to talk to modem
 */
व्योम prcmu_ac_sleep_req(व्योम)
अणु
	u32 val;

	mutex_lock(&mb0_transfer.ac_wake_lock);

	val = पढ़ोl(PRCM_HOSTACCESS_REQ);
	अगर (!(val & PRCM_HOSTACCESS_REQ_HOSTACCESS_REQ))
		जाओ unlock_and_वापस;

	ग_लिखोl((val & ~PRCM_HOSTACCESS_REQ_HOSTACCESS_REQ),
		PRCM_HOSTACCESS_REQ);

	अगर (!रुको_क्रम_completion_समयout(&mb0_transfer.ac_wake_work,
			msecs_to_jअगरfies(5000))) अणु
		pr_crit("prcmu: %s timed out (5 s) waiting for a reply.\n",
			__func__);
	पूर्ण

	atomic_set(&ac_wake_req_state, 0);

unlock_and_वापस:
	mutex_unlock(&mb0_transfer.ac_wake_lock);
पूर्ण

bool db8500_prcmu_is_ac_wake_requested(व्योम)
अणु
	वापस (atomic_पढ़ो(&ac_wake_req_state) != 0);
पूर्ण

/**
 * db8500_prcmu_प्रणाली_reset - System reset
 *
 * Saves the reset reason code and then sets the APE_SOFTRST रेजिस्टर which
 * fires पूर्णांकerrupt to fw
 *
 * @reset_code: The reason क्रम प्रणाली reset
 */
व्योम db8500_prcmu_प्रणाली_reset(u16 reset_code)
अणु
	ग_लिखोw(reset_code, (tcdm_base + PRCM_SW_RST_REASON));
	ग_लिखोl(1, PRCM_APE_SOFTRST);
पूर्ण

/**
 * db8500_prcmu_get_reset_code - Retrieve SW reset reason code
 *
 * Retrieves the reset reason code stored by prcmu_प्रणाली_reset() beक्रमe
 * last restart.
 */
u16 db8500_prcmu_get_reset_code(व्योम)
अणु
	वापस पढ़ोw(tcdm_base + PRCM_SW_RST_REASON);
पूर्ण

/**
 * db8500_prcmu_reset_modem - ask the PRCMU to reset modem
 */
व्योम db8500_prcmu_modem_reset(व्योम)
अणु
	mutex_lock(&mb1_transfer.lock);

	जबतक (पढ़ोl(PRCM_MBOX_CPU_VAL) & MBOX_BIT(1))
		cpu_relax();

	ग_लिखोb(MB1H_RESET_MODEM, (tcdm_base + PRCM_MBOX_HEADER_REQ_MB1));
	ग_लिखोl(MBOX_BIT(1), PRCM_MBOX_CPU_SET);
	रुको_क्रम_completion(&mb1_transfer.work);

	/*
	 * No need to check वापस from PRCMU as modem should go in reset state
	 * This state is alपढ़ोy managed by upper layer
	 */

	mutex_unlock(&mb1_transfer.lock);
पूर्ण

अटल व्योम ack_dbb_wakeup(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&mb0_transfer.lock, flags);

	जबतक (पढ़ोl(PRCM_MBOX_CPU_VAL) & MBOX_BIT(0))
		cpu_relax();

	ग_लिखोb(MB0H_READ_WAKEUP_ACK, (tcdm_base + PRCM_MBOX_HEADER_REQ_MB0));
	ग_लिखोl(MBOX_BIT(0), PRCM_MBOX_CPU_SET);

	spin_unlock_irqrestore(&mb0_transfer.lock, flags);
पूर्ण

अटल अंतरभूत व्योम prपूर्णांक_unknown_header_warning(u8 n, u8 header)
अणु
	pr_warn("prcmu: Unknown message header (%d) in mailbox %d\n",
		header, n);
पूर्ण

अटल bool पढ़ो_mailbox_0(व्योम)
अणु
	bool r;
	u32 ev;
	अचिन्हित पूर्णांक n;
	u8 header;

	header = पढ़ोb(tcdm_base + PRCM_MBOX_HEADER_ACK_MB0);
	चयन (header) अणु
	हाल MB0H_WAKEUP_EXE:
	हाल MB0H_WAKEUP_SLEEP:
		अगर (पढ़ोb(tcdm_base + PRCM_ACK_MB0_READ_POINTER) & 1)
			ev = पढ़ोl(tcdm_base + PRCM_ACK_MB0_WAKEUP_1_8500);
		अन्यथा
			ev = पढ़ोl(tcdm_base + PRCM_ACK_MB0_WAKEUP_0_8500);

		अगर (ev & (WAKEUP_BIT_AC_WAKE_ACK | WAKEUP_BIT_AC_SLEEP_ACK))
			complete(&mb0_transfer.ac_wake_work);
		अगर (ev & WAKEUP_BIT_SYSCLK_OK)
			complete(&mb3_transfer.sysclk_work);

		ev &= mb0_transfer.req.dbb_irqs;

		क्रम (n = 0; n < NUM_PRCMU_WAKEUPS; n++) अणु
			अगर (ev & prcmu_irq_bit[n])
				generic_handle_irq(irq_find_mapping(db8500_irq_करोमुख्य, n));
		पूर्ण
		r = true;
		अवरोध;
	शेष:
		prपूर्णांक_unknown_header_warning(0, header);
		r = false;
		अवरोध;
	पूर्ण
	ग_लिखोl(MBOX_BIT(0), PRCM_ARM_IT1_CLR);
	वापस r;
पूर्ण

अटल bool पढ़ो_mailbox_1(व्योम)
अणु
	mb1_transfer.ack.header = पढ़ोb(tcdm_base + PRCM_MBOX_HEADER_REQ_MB1);
	mb1_transfer.ack.arm_opp = पढ़ोb(tcdm_base +
		PRCM_ACK_MB1_CURRENT_ARM_OPP);
	mb1_transfer.ack.ape_opp = पढ़ोb(tcdm_base +
		PRCM_ACK_MB1_CURRENT_APE_OPP);
	mb1_transfer.ack.ape_voltage_status = पढ़ोb(tcdm_base +
		PRCM_ACK_MB1_APE_VOLTAGE_STATUS);
	ग_लिखोl(MBOX_BIT(1), PRCM_ARM_IT1_CLR);
	complete(&mb1_transfer.work);
	वापस false;
पूर्ण

अटल bool पढ़ो_mailbox_2(व्योम)
अणु
	mb2_transfer.ack.status = पढ़ोb(tcdm_base + PRCM_ACK_MB2_DPS_STATUS);
	ग_लिखोl(MBOX_BIT(2), PRCM_ARM_IT1_CLR);
	complete(&mb2_transfer.work);
	वापस false;
पूर्ण

अटल bool पढ़ो_mailbox_3(व्योम)
अणु
	ग_लिखोl(MBOX_BIT(3), PRCM_ARM_IT1_CLR);
	वापस false;
पूर्ण

अटल bool पढ़ो_mailbox_4(व्योम)
अणु
	u8 header;
	bool करो_complete = true;

	header = पढ़ोb(tcdm_base + PRCM_MBOX_HEADER_REQ_MB4);
	चयन (header) अणु
	हाल MB4H_MEM_ST:
	हाल MB4H_HOTDOG:
	हाल MB4H_HOTMON:
	हाल MB4H_HOT_PERIOD:
	हाल MB4H_A9WDOG_CONF:
	हाल MB4H_A9WDOG_EN:
	हाल MB4H_A9WDOG_DIS:
	हाल MB4H_A9WDOG_LOAD:
	हाल MB4H_A9WDOG_KICK:
		अवरोध;
	शेष:
		prपूर्णांक_unknown_header_warning(4, header);
		करो_complete = false;
		अवरोध;
	पूर्ण

	ग_लिखोl(MBOX_BIT(4), PRCM_ARM_IT1_CLR);

	अगर (करो_complete)
		complete(&mb4_transfer.work);

	वापस false;
पूर्ण

अटल bool पढ़ो_mailbox_5(व्योम)
अणु
	mb5_transfer.ack.status = पढ़ोb(tcdm_base + PRCM_ACK_MB5_I2C_STATUS);
	mb5_transfer.ack.value = पढ़ोb(tcdm_base + PRCM_ACK_MB5_I2C_VAL);
	ग_लिखोl(MBOX_BIT(5), PRCM_ARM_IT1_CLR);
	complete(&mb5_transfer.work);
	वापस false;
पूर्ण

अटल bool पढ़ो_mailbox_6(व्योम)
अणु
	ग_लिखोl(MBOX_BIT(6), PRCM_ARM_IT1_CLR);
	वापस false;
पूर्ण

अटल bool पढ़ो_mailbox_7(व्योम)
अणु
	ग_लिखोl(MBOX_BIT(7), PRCM_ARM_IT1_CLR);
	वापस false;
पूर्ण

अटल bool (* स्थिर पढ़ो_mailbox[NUM_MB])(व्योम) = अणु
	पढ़ो_mailbox_0,
	पढ़ो_mailbox_1,
	पढ़ो_mailbox_2,
	पढ़ो_mailbox_3,
	पढ़ो_mailbox_4,
	पढ़ो_mailbox_5,
	पढ़ो_mailbox_6,
	पढ़ो_mailbox_7
पूर्ण;

अटल irqवापस_t prcmu_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	u32 bits;
	u8 n;
	irqवापस_t r;

	bits = (पढ़ोl(PRCM_ARM_IT1_VAL) & ALL_MBOX_BITS);
	अगर (unlikely(!bits))
		वापस IRQ_NONE;

	r = IRQ_HANDLED;
	क्रम (n = 0; bits; n++) अणु
		अगर (bits & MBOX_BIT(n)) अणु
			bits -= MBOX_BIT(n);
			अगर (पढ़ो_mailbox[n]())
				r = IRQ_WAKE_THREAD;
		पूर्ण
	पूर्ण
	वापस r;
पूर्ण

अटल irqवापस_t prcmu_irq_thपढ़ो_fn(पूर्णांक irq, व्योम *data)
अणु
	ack_dbb_wakeup();
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम prcmu_mask_work(काष्ठा work_काष्ठा *work)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&mb0_transfer.lock, flags);

	config_wakeups();

	spin_unlock_irqrestore(&mb0_transfer.lock, flags);
पूर्ण

अटल व्योम prcmu_irq_mask(काष्ठा irq_data *d)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&mb0_transfer.dbb_irqs_lock, flags);

	mb0_transfer.req.dbb_irqs &= ~prcmu_irq_bit[d->hwirq];

	spin_unlock_irqrestore(&mb0_transfer.dbb_irqs_lock, flags);

	अगर (d->irq != IRQ_PRCMU_CA_SLEEP)
		schedule_work(&mb0_transfer.mask_work);
पूर्ण

अटल व्योम prcmu_irq_unmask(काष्ठा irq_data *d)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&mb0_transfer.dbb_irqs_lock, flags);

	mb0_transfer.req.dbb_irqs |= prcmu_irq_bit[d->hwirq];

	spin_unlock_irqrestore(&mb0_transfer.dbb_irqs_lock, flags);

	अगर (d->irq != IRQ_PRCMU_CA_SLEEP)
		schedule_work(&mb0_transfer.mask_work);
पूर्ण

अटल व्योम noop(काष्ठा irq_data *d)
अणु
पूर्ण

अटल काष्ठा irq_chip prcmu_irq_chip = अणु
	.name		= "prcmu",
	.irq_disable	= prcmu_irq_mask,
	.irq_ack	= noop,
	.irq_mask	= prcmu_irq_mask,
	.irq_unmask	= prcmu_irq_unmask,
पूर्ण;

अटल अक्षर *fw_project_name(u32 project)
अणु
	चयन (project) अणु
	हाल PRCMU_FW_PROJECT_U8500:
		वापस "U8500";
	हाल PRCMU_FW_PROJECT_U8400:
		वापस "U8400";
	हाल PRCMU_FW_PROJECT_U9500:
		वापस "U9500";
	हाल PRCMU_FW_PROJECT_U8500_MBB:
		वापस "U8500 MBB";
	हाल PRCMU_FW_PROJECT_U8500_C1:
		वापस "U8500 C1";
	हाल PRCMU_FW_PROJECT_U8500_C2:
		वापस "U8500 C2";
	हाल PRCMU_FW_PROJECT_U8500_C3:
		वापस "U8500 C3";
	हाल PRCMU_FW_PROJECT_U8500_C4:
		वापस "U8500 C4";
	हाल PRCMU_FW_PROJECT_U9500_MBL:
		वापस "U9500 MBL";
	हाल PRCMU_FW_PROJECT_U8500_MBL:
		वापस "U8500 MBL";
	हाल PRCMU_FW_PROJECT_U8500_MBL2:
		वापस "U8500 MBL2";
	हाल PRCMU_FW_PROJECT_U8520:
		वापस "U8520 MBL";
	हाल PRCMU_FW_PROJECT_U8420:
		वापस "U8420";
	हाल PRCMU_FW_PROJECT_U8420_SYSCLK:
		वापस "U8420-sysclk";
	हाल PRCMU_FW_PROJECT_U9540:
		वापस "U9540";
	हाल PRCMU_FW_PROJECT_A9420:
		वापस "A9420";
	हाल PRCMU_FW_PROJECT_L8540:
		वापस "L8540";
	हाल PRCMU_FW_PROJECT_L8580:
		वापस "L8580";
	शेष:
		वापस "Unknown";
	पूर्ण
पूर्ण

अटल पूर्णांक db8500_irq_map(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक virq,
				irq_hw_number_t hwirq)
अणु
	irq_set_chip_and_handler(virq, &prcmu_irq_chip,
				handle_simple_irq);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops db8500_irq_ops = अणु
	.map    = db8500_irq_map,
	.xlate  = irq_करोमुख्य_xlate_twocell,
पूर्ण;

अटल पूर्णांक db8500_irq_init(काष्ठा device_node *np)
अणु
	पूर्णांक i;

	db8500_irq_करोमुख्य = irq_करोमुख्य_add_simple(
		np, NUM_PRCMU_WAKEUPS, 0,
		&db8500_irq_ops, शून्य);

	अगर (!db8500_irq_करोमुख्य) अणु
		pr_err("Failed to create irqdomain\n");
		वापस -ENOSYS;
	पूर्ण

	/* All wakeups will be used, so create mappings क्रम all */
	क्रम (i = 0; i < NUM_PRCMU_WAKEUPS; i++)
		irq_create_mapping(db8500_irq_करोमुख्य, i);

	वापस 0;
पूर्ण

अटल व्योम dbx500_fw_version_init(काष्ठा device_node *np)
अणु
	व्योम __iomem *tcpm_base;
	u32 version;

	tcpm_base = of_iomap(np, 1);
	अगर (!tcpm_base) अणु
		pr_err("no prcmu tcpm mem region provided\n");
		वापस;
	पूर्ण

	version = पढ़ोl(tcpm_base + DB8500_PRCMU_FW_VERSION_OFFSET);
	fw_info.version.project = (version & 0xFF);
	fw_info.version.api_version = (version >> 8) & 0xFF;
	fw_info.version.func_version = (version >> 16) & 0xFF;
	fw_info.version.errata = (version >> 24) & 0xFF;
	म_नकलन(fw_info.version.project_name,
		fw_project_name(fw_info.version.project),
		PRCMU_FW_PROJECT_NAME_LEN);
	fw_info.valid = true;
	pr_info("PRCMU firmware: %s(%d), version %d.%d.%d\n",
		fw_info.version.project_name,
		fw_info.version.project,
		fw_info.version.api_version,
		fw_info.version.func_version,
		fw_info.version.errata);
	iounmap(tcpm_base);
पूर्ण

व्योम __init db8500_prcmu_early_init(व्योम)
अणु
	/*
	 * This is a temporary remap to bring up the घड़ीs. It is
	 * subsequently replaces with a real remap. After the merge of
	 * the mailbox subप्रणाली all of this early code goes away, and the
	 * घड़ी driver can probe independently. An early initcall will
	 * still be needed, but it can be भागerted पूर्णांकo drivers/clk/ux500.
	 */
	काष्ठा device_node *np;

	np = of_find_compatible_node(शून्य, शून्य, "stericsson,db8500-prcmu");
	prcmu_base = of_iomap(np, 0);
	अगर (!prcmu_base) अणु
		of_node_put(np);
		pr_err("%s: ioremap() of prcmu registers failed!\n", __func__);
		वापस;
	पूर्ण
	dbx500_fw_version_init(np);
	of_node_put(np);

	spin_lock_init(&mb0_transfer.lock);
	spin_lock_init(&mb0_transfer.dbb_irqs_lock);
	mutex_init(&mb0_transfer.ac_wake_lock);
	init_completion(&mb0_transfer.ac_wake_work);
	mutex_init(&mb1_transfer.lock);
	init_completion(&mb1_transfer.work);
	mb1_transfer.ape_opp = APE_NO_CHANGE;
	mutex_init(&mb2_transfer.lock);
	init_completion(&mb2_transfer.work);
	spin_lock_init(&mb2_transfer.स्वतः_pm_lock);
	spin_lock_init(&mb3_transfer.lock);
	mutex_init(&mb3_transfer.sysclk_lock);
	init_completion(&mb3_transfer.sysclk_work);
	mutex_init(&mb4_transfer.lock);
	init_completion(&mb4_transfer.work);
	mutex_init(&mb5_transfer.lock);
	init_completion(&mb5_transfer.work);

	INIT_WORK(&mb0_transfer.mask_work, prcmu_mask_work);
पूर्ण

अटल व्योम init_prcm_रेजिस्टरs(व्योम)
अणु
	u32 val;

	val = पढ़ोl(PRCM_A9PL_FORCE_CLKEN);
	val &= ~(PRCM_A9PL_FORCE_CLKEN_PRCM_A9PL_FORCE_CLKEN |
		PRCM_A9PL_FORCE_CLKEN_PRCM_A9AXI_FORCE_CLKEN);
	ग_लिखोl(val, (PRCM_A9PL_FORCE_CLKEN));
पूर्ण

/*
 * Power करोमुख्य चयनes (ePODs) modeled as regulators क्रम the DB8500 SoC
 */
अटल काष्ठा regulator_consumer_supply db8500_vape_consumers[] = अणु
	REGULATOR_SUPPLY("v-ape", शून्य),
	REGULATOR_SUPPLY("v-i2c", "nmk-i2c.0"),
	REGULATOR_SUPPLY("v-i2c", "nmk-i2c.1"),
	REGULATOR_SUPPLY("v-i2c", "nmk-i2c.2"),
	REGULATOR_SUPPLY("v-i2c", "nmk-i2c.3"),
	REGULATOR_SUPPLY("v-i2c", "nmk-i2c.4"),
	/* "v-mmc" changed to "vcore" in the मुख्यline kernel */
	REGULATOR_SUPPLY("vcore", "sdi0"),
	REGULATOR_SUPPLY("vcore", "sdi1"),
	REGULATOR_SUPPLY("vcore", "sdi2"),
	REGULATOR_SUPPLY("vcore", "sdi3"),
	REGULATOR_SUPPLY("vcore", "sdi4"),
	REGULATOR_SUPPLY("v-dma", "dma40.0"),
	REGULATOR_SUPPLY("v-ape", "ab8500-usb.0"),
	/* "v-uart" changed to "vcore" in the मुख्यline kernel */
	REGULATOR_SUPPLY("vcore", "uart0"),
	REGULATOR_SUPPLY("vcore", "uart1"),
	REGULATOR_SUPPLY("vcore", "uart2"),
	REGULATOR_SUPPLY("v-ape", "nmk-ske-keypad.0"),
	REGULATOR_SUPPLY("v-hsi", "ste_hsi.0"),
	REGULATOR_SUPPLY("vddvario", "smsc911x.0"),
पूर्ण;

अटल काष्ठा regulator_consumer_supply db8500_vsmps2_consumers[] = अणु
	REGULATOR_SUPPLY("musb_1v8", "ab8500-usb.0"),
	/* AV8100 regulator */
	REGULATOR_SUPPLY("hdmi_1v8", "0-0070"),
पूर्ण;

अटल काष्ठा regulator_consumer_supply db8500_b2r2_mcde_consumers[] = अणु
	REGULATOR_SUPPLY("vsupply", "b2r2_bus"),
	REGULATOR_SUPPLY("vsupply", "mcde"),
पूर्ण;

/* SVA MMDSP regulator चयन */
अटल काष्ठा regulator_consumer_supply db8500_svammdsp_consumers[] = अणु
	REGULATOR_SUPPLY("sva-mmdsp", "cm_control"),
पूर्ण;

/* SVA pipe regulator चयन */
अटल काष्ठा regulator_consumer_supply db8500_svapipe_consumers[] = अणु
	REGULATOR_SUPPLY("sva-pipe", "cm_control"),
पूर्ण;

/* SIA MMDSP regulator चयन */
अटल काष्ठा regulator_consumer_supply db8500_siammdsp_consumers[] = अणु
	REGULATOR_SUPPLY("sia-mmdsp", "cm_control"),
पूर्ण;

/* SIA pipe regulator चयन */
अटल काष्ठा regulator_consumer_supply db8500_siapipe_consumers[] = अणु
	REGULATOR_SUPPLY("sia-pipe", "cm_control"),
पूर्ण;

अटल काष्ठा regulator_consumer_supply db8500_sga_consumers[] = अणु
	REGULATOR_SUPPLY("v-mali", शून्य),
पूर्ण;

/* ESRAM1 and 2 regulator चयन */
अटल काष्ठा regulator_consumer_supply db8500_esram12_consumers[] = अणु
	REGULATOR_SUPPLY("esram12", "cm_control"),
पूर्ण;

/* ESRAM3 and 4 regulator चयन */
अटल काष्ठा regulator_consumer_supply db8500_esram34_consumers[] = अणु
	REGULATOR_SUPPLY("v-esram34", "mcde"),
	REGULATOR_SUPPLY("esram34", "cm_control"),
	REGULATOR_SUPPLY("lcla_esram", "dma40.0"),
पूर्ण;

अटल काष्ठा regulator_init_data db8500_regulators[DB8500_NUM_REGULATORS] = अणु
	[DB8500_REGULATOR_VAPE] = अणु
		.स्थिरraपूर्णांकs = अणु
			.name = "db8500-vape",
			.valid_ops_mask = REGULATOR_CHANGE_STATUS,
			.always_on = true,
		पूर्ण,
		.consumer_supplies = db8500_vape_consumers,
		.num_consumer_supplies = ARRAY_SIZE(db8500_vape_consumers),
	पूर्ण,
	[DB8500_REGULATOR_VARM] = अणु
		.स्थिरraपूर्णांकs = अणु
			.name = "db8500-varm",
			.valid_ops_mask = REGULATOR_CHANGE_STATUS,
		पूर्ण,
	पूर्ण,
	[DB8500_REGULATOR_VMODEM] = अणु
		.स्थिरraपूर्णांकs = अणु
			.name = "db8500-vmodem",
			.valid_ops_mask = REGULATOR_CHANGE_STATUS,
		पूर्ण,
	पूर्ण,
	[DB8500_REGULATOR_VPLL] = अणु
		.स्थिरraपूर्णांकs = अणु
			.name = "db8500-vpll",
			.valid_ops_mask = REGULATOR_CHANGE_STATUS,
		पूर्ण,
	पूर्ण,
	[DB8500_REGULATOR_VSMPS1] = अणु
		.स्थिरraपूर्णांकs = अणु
			.name = "db8500-vsmps1",
			.valid_ops_mask = REGULATOR_CHANGE_STATUS,
		पूर्ण,
	पूर्ण,
	[DB8500_REGULATOR_VSMPS2] = अणु
		.स्थिरraपूर्णांकs = अणु
			.name = "db8500-vsmps2",
			.valid_ops_mask = REGULATOR_CHANGE_STATUS,
		पूर्ण,
		.consumer_supplies = db8500_vsmps2_consumers,
		.num_consumer_supplies = ARRAY_SIZE(db8500_vsmps2_consumers),
	पूर्ण,
	[DB8500_REGULATOR_VSMPS3] = अणु
		.स्थिरraपूर्णांकs = अणु
			.name = "db8500-vsmps3",
			.valid_ops_mask = REGULATOR_CHANGE_STATUS,
		पूर्ण,
	पूर्ण,
	[DB8500_REGULATOR_VRF1] = अणु
		.स्थिरraपूर्णांकs = अणु
			.name = "db8500-vrf1",
			.valid_ops_mask = REGULATOR_CHANGE_STATUS,
		पूर्ण,
	पूर्ण,
	[DB8500_REGULATOR_SWITCH_SVAMMDSP] = अणु
		/* dependency to u8500-vape is handled outside regulator framework */
		.स्थिरraपूर्णांकs = अणु
			.name = "db8500-sva-mmdsp",
			.valid_ops_mask = REGULATOR_CHANGE_STATUS,
		पूर्ण,
		.consumer_supplies = db8500_svammdsp_consumers,
		.num_consumer_supplies = ARRAY_SIZE(db8500_svammdsp_consumers),
	पूर्ण,
	[DB8500_REGULATOR_SWITCH_SVAMMDSPRET] = अणु
		.स्थिरraपूर्णांकs = अणु
			/* "ret" means "retention" */
			.name = "db8500-sva-mmdsp-ret",
			.valid_ops_mask = REGULATOR_CHANGE_STATUS,
		पूर्ण,
	पूर्ण,
	[DB8500_REGULATOR_SWITCH_SVAPIPE] = अणु
		/* dependency to u8500-vape is handled outside regulator framework */
		.स्थिरraपूर्णांकs = अणु
			.name = "db8500-sva-pipe",
			.valid_ops_mask = REGULATOR_CHANGE_STATUS,
		पूर्ण,
		.consumer_supplies = db8500_svapipe_consumers,
		.num_consumer_supplies = ARRAY_SIZE(db8500_svapipe_consumers),
	पूर्ण,
	[DB8500_REGULATOR_SWITCH_SIAMMDSP] = अणु
		/* dependency to u8500-vape is handled outside regulator framework */
		.स्थिरraपूर्णांकs = अणु
			.name = "db8500-sia-mmdsp",
			.valid_ops_mask = REGULATOR_CHANGE_STATUS,
		पूर्ण,
		.consumer_supplies = db8500_siammdsp_consumers,
		.num_consumer_supplies = ARRAY_SIZE(db8500_siammdsp_consumers),
	पूर्ण,
	[DB8500_REGULATOR_SWITCH_SIAMMDSPRET] = अणु
		.स्थिरraपूर्णांकs = अणु
			.name = "db8500-sia-mmdsp-ret",
			.valid_ops_mask = REGULATOR_CHANGE_STATUS,
		पूर्ण,
	पूर्ण,
	[DB8500_REGULATOR_SWITCH_SIAPIPE] = अणु
		/* dependency to u8500-vape is handled outside regulator framework */
		.स्थिरraपूर्णांकs = अणु
			.name = "db8500-sia-pipe",
			.valid_ops_mask = REGULATOR_CHANGE_STATUS,
		पूर्ण,
		.consumer_supplies = db8500_siapipe_consumers,
		.num_consumer_supplies = ARRAY_SIZE(db8500_siapipe_consumers),
	पूर्ण,
	[DB8500_REGULATOR_SWITCH_SGA] = अणु
		.supply_regulator = "db8500-vape",
		.स्थिरraपूर्णांकs = अणु
			.name = "db8500-sga",
			.valid_ops_mask = REGULATOR_CHANGE_STATUS,
		पूर्ण,
		.consumer_supplies = db8500_sga_consumers,
		.num_consumer_supplies = ARRAY_SIZE(db8500_sga_consumers),

	पूर्ण,
	[DB8500_REGULATOR_SWITCH_B2R2_MCDE] = अणु
		.supply_regulator = "db8500-vape",
		.स्थिरraपूर्णांकs = अणु
			.name = "db8500-b2r2-mcde",
			.valid_ops_mask = REGULATOR_CHANGE_STATUS,
		पूर्ण,
		.consumer_supplies = db8500_b2r2_mcde_consumers,
		.num_consumer_supplies = ARRAY_SIZE(db8500_b2r2_mcde_consumers),
	पूर्ण,
	[DB8500_REGULATOR_SWITCH_ESRAM12] = अणु
		/*
		 * esram12 is set in retention and supplied by Vsafe when Vape is off,
		 * no need to hold Vape
		 */
		.स्थिरraपूर्णांकs = अणु
			.name = "db8500-esram12",
			.valid_ops_mask = REGULATOR_CHANGE_STATUS,
		पूर्ण,
		.consumer_supplies = db8500_esram12_consumers,
		.num_consumer_supplies = ARRAY_SIZE(db8500_esram12_consumers),
	पूर्ण,
	[DB8500_REGULATOR_SWITCH_ESRAM12RET] = अणु
		.स्थिरraपूर्णांकs = अणु
			.name = "db8500-esram12-ret",
			.valid_ops_mask = REGULATOR_CHANGE_STATUS,
		पूर्ण,
	पूर्ण,
	[DB8500_REGULATOR_SWITCH_ESRAM34] = अणु
		/*
		 * esram34 is set in retention and supplied by Vsafe when Vape is off,
		 * no need to hold Vape
		 */
		.स्थिरraपूर्णांकs = अणु
			.name = "db8500-esram34",
			.valid_ops_mask = REGULATOR_CHANGE_STATUS,
		पूर्ण,
		.consumer_supplies = db8500_esram34_consumers,
		.num_consumer_supplies = ARRAY_SIZE(db8500_esram34_consumers),
	पूर्ण,
	[DB8500_REGULATOR_SWITCH_ESRAM34RET] = अणु
		.स्थिरraपूर्णांकs = अणु
			.name = "db8500-esram34-ret",
			.valid_ops_mask = REGULATOR_CHANGE_STATUS,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा ux500_wdt_data db8500_wdt_pdata = अणु
	.समयout = 600, /* 10 minutes */
	.has_28_bits_resolution = true,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell common_prcmu_devs[] = अणु
	अणु
		.name = "ux500_wdt",
		.platक्रमm_data = &db8500_wdt_pdata,
		.pdata_size = माप(db8500_wdt_pdata),
		.id = -1,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell db8500_prcmu_devs[] = अणु
	MFD_CELL_OF("db8500-prcmu-regulators", शून्य,
		    &db8500_regulators, माप(db8500_regulators), 0,
		    "stericsson,db8500-prcmu-regulator"),
	MFD_CELL_OF("cpuidle-dbx500",
		    शून्य, शून्य, 0, 0, "stericsson,cpuidle-dbx500"),
	MFD_CELL_OF("db8500-thermal",
		    शून्य, शून्य, 0, 0, "stericsson,db8500-thermal"),
पूर्ण;

अटल पूर्णांक db8500_prcmu_रेजिस्टर_ab8500(काष्ठा device *parent)
अणु
	काष्ठा device_node *np;
	काष्ठा resource ab850x_resource;
	स्थिर काष्ठा mfd_cell ab8500_cell = अणु
		.name = "ab8500-core",
		.of_compatible = "stericsson,ab8500",
		.id = AB8500_VERSION_AB8500,
		.resources = &ab850x_resource,
		.num_resources = 1,
	पूर्ण;
	स्थिर काष्ठा mfd_cell ab8505_cell = अणु
		.name = "ab8505-core",
		.of_compatible = "stericsson,ab8505",
		.id = AB8500_VERSION_AB8505,
		.resources = &ab850x_resource,
		.num_resources = 1,
	पूर्ण;
	स्थिर काष्ठा mfd_cell *ab850x_cell;

	अगर (!parent->of_node)
		वापस -ENODEV;

	/* Look up the device node, sneak the IRQ out of it */
	क्रम_each_child_of_node(parent->of_node, np) अणु
		अगर (of_device_is_compatible(np, ab8500_cell.of_compatible)) अणु
			ab850x_cell = &ab8500_cell;
			अवरोध;
		पूर्ण
		अगर (of_device_is_compatible(np, ab8505_cell.of_compatible)) अणु
			ab850x_cell = &ab8505_cell;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!np) अणु
		dev_info(parent, "could not find AB850X node in the device tree\n");
		वापस -ENODEV;
	पूर्ण
	of_irq_to_resource_table(np, &ab850x_resource, 1);

	वापस mfd_add_devices(parent, 0, ab850x_cell, 1, शून्य, 0, शून्य);
पूर्ण

अटल पूर्णांक db8500_prcmu_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	पूर्णांक irq = 0, err = 0;
	काष्ठा resource *res;

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "prcmu");
	अगर (!res) अणु
		dev_err(&pdev->dev, "no prcmu memory region provided\n");
		वापस -EINVAL;
	पूर्ण
	prcmu_base = devm_ioremap(&pdev->dev, res->start, resource_size(res));
	अगर (!prcmu_base) अणु
		dev_err(&pdev->dev,
			"failed to ioremap prcmu register memory\n");
		वापस -ENOMEM;
	पूर्ण
	init_prcm_रेजिस्टरs();
	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "prcmu-tcdm");
	अगर (!res) अणु
		dev_err(&pdev->dev, "no prcmu tcdm region provided\n");
		वापस -EINVAL;
	पूर्ण
	tcdm_base = devm_ioremap(&pdev->dev, res->start,
			resource_size(res));
	अगर (!tcdm_base) अणु
		dev_err(&pdev->dev,
			"failed to ioremap prcmu-tcdm register memory\n");
		वापस -ENOMEM;
	पूर्ण

	/* Clean up the mailbox पूर्णांकerrupts after pre-kernel code. */
	ग_लिखोl(ALL_MBOX_BITS, PRCM_ARM_IT1_CLR);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq <= 0)
		वापस irq;

	err = request_thपढ़ोed_irq(irq, prcmu_irq_handler,
	        prcmu_irq_thपढ़ो_fn, IRQF_NO_SUSPEND, "prcmu", शून्य);
	अगर (err < 0) अणु
		pr_err("prcmu: Failed to allocate IRQ_DB8500_PRCMU1.\n");
		वापस err;
	पूर्ण

	db8500_irq_init(np);

	prcmu_config_esram0_deep_sleep(ESRAM0_DEEP_SLEEP_STATE_RET);

	err = mfd_add_devices(&pdev->dev, 0, common_prcmu_devs,
			      ARRAY_SIZE(common_prcmu_devs), शून्य, 0, db8500_irq_करोमुख्य);
	अगर (err) अणु
		pr_err("prcmu: Failed to add subdevices\n");
		वापस err;
	पूर्ण

	/* TODO: Remove restriction when clk definitions are available. */
	अगर (!of_machine_is_compatible("st-ericsson,u8540")) अणु
		err = mfd_add_devices(&pdev->dev, 0, db8500_prcmu_devs,
				      ARRAY_SIZE(db8500_prcmu_devs), शून्य, 0,
				      db8500_irq_करोमुख्य);
		अगर (err) अणु
			mfd_हटाओ_devices(&pdev->dev);
			pr_err("prcmu: Failed to add subdevices\n");
			वापस err;
		पूर्ण
	पूर्ण

	err = db8500_prcmu_रेजिस्टर_ab8500(&pdev->dev);
	अगर (err) अणु
		mfd_हटाओ_devices(&pdev->dev);
		pr_err("prcmu: Failed to add ab8500 subdevice\n");
		वापस err;
	पूर्ण

	pr_info("DB8500 PRCMU initialized\n");
	वापस err;
पूर्ण
अटल स्थिर काष्ठा of_device_id db8500_prcmu_match[] = अणु
	अणु .compatible = "stericsson,db8500-prcmu"पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver db8500_prcmu_driver = अणु
	.driver = अणु
		.name = "db8500-prcmu",
		.of_match_table = db8500_prcmu_match,
	पूर्ण,
	.probe = db8500_prcmu_probe,
पूर्ण;

अटल पूर्णांक __init db8500_prcmu_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&db8500_prcmu_driver);
पूर्ण
core_initcall(db8500_prcmu_init);
