<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Header file क्रम the Ingenic JZ47xx TCU driver
 */
#अगर_अघोषित __LINUX_MFD_INGENIC_TCU_H_
#घोषणा __LINUX_MFD_INGENIC_TCU_H_

#समावेश <linux/bitops.h>

#घोषणा TCU_REG_WDT_TDR		0x00
#घोषणा TCU_REG_WDT_TCER	0x04
#घोषणा TCU_REG_WDT_TCNT	0x08
#घोषणा TCU_REG_WDT_TCSR	0x0c
#घोषणा TCU_REG_TER		0x10
#घोषणा TCU_REG_TESR		0x14
#घोषणा TCU_REG_TECR		0x18
#घोषणा TCU_REG_TSR		0x1c
#घोषणा TCU_REG_TFR		0x20
#घोषणा TCU_REG_TFSR		0x24
#घोषणा TCU_REG_TFCR		0x28
#घोषणा TCU_REG_TSSR		0x2c
#घोषणा TCU_REG_TMR		0x30
#घोषणा TCU_REG_TMSR		0x34
#घोषणा TCU_REG_TMCR		0x38
#घोषणा TCU_REG_TSCR		0x3c
#घोषणा TCU_REG_TDFR0		0x40
#घोषणा TCU_REG_TDHR0		0x44
#घोषणा TCU_REG_TCNT0		0x48
#घोषणा TCU_REG_TCSR0		0x4c
#घोषणा TCU_REG_OST_DR		0xe0
#घोषणा TCU_REG_OST_CNTL	0xe4
#घोषणा TCU_REG_OST_CNTH	0xe8
#घोषणा TCU_REG_OST_TCSR	0xec
#घोषणा TCU_REG_TSTR		0xf0
#घोषणा TCU_REG_TSTSR		0xf4
#घोषणा TCU_REG_TSTCR		0xf8
#घोषणा TCU_REG_OST_CNTHBUF	0xfc

#घोषणा TCU_TCSR_RESERVED_BITS		0x3f
#घोषणा TCU_TCSR_PARENT_CLOCK_MASK	0x07
#घोषणा TCU_TCSR_PRESCALE_LSB		3
#घोषणा TCU_TCSR_PRESCALE_MASK		0x38

#घोषणा TCU_TCSR_PWM_SD		BIT(9)	/* 0: Shutकरोwn gracefully 1: abruptly */
#घोषणा TCU_TCSR_PWM_INITL_HIGH	BIT(8)	/* Sets the initial output level */
#घोषणा TCU_TCSR_PWM_EN		BIT(7)	/* PWM pin output enable */

#घोषणा TCU_WDT_TCER_TCEN	BIT(0)	/* Watchकरोg समयr enable */

#घोषणा TCU_CHANNEL_STRIDE	0x10
#घोषणा TCU_REG_TDFRc(c)	(TCU_REG_TDFR0 + ((c) * TCU_CHANNEL_STRIDE))
#घोषणा TCU_REG_TDHRc(c)	(TCU_REG_TDHR0 + ((c) * TCU_CHANNEL_STRIDE))
#घोषणा TCU_REG_TCNTc(c)	(TCU_REG_TCNT0 + ((c) * TCU_CHANNEL_STRIDE))
#घोषणा TCU_REG_TCSRc(c)	(TCU_REG_TCSR0 + ((c) * TCU_CHANNEL_STRIDE))

#पूर्ण_अगर /* __LINUX_MFD_INGENIC_TCU_H_ */
