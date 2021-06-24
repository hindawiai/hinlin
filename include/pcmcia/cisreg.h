<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * cisreg.h
 *
 * The initial developer of the original code is David A. Hinds
 * <dahinds@users.sourceक्रमge.net>.  Portions created by David A. Hinds
 * are Copyright (C) 1999 David A. Hinds.  All Rights Reserved.
 *
 * (C) 1999             David A. Hinds
 */

#अगर_अघोषित _LINUX_CISREG_H
#घोषणा _LINUX_CISREG_H

/*
 * Offsets from ConfigBase क्रम CIS रेजिस्टरs
 */
#घोषणा CISREG_COR		0x00
#घोषणा CISREG_CCSR		0x02
#घोषणा CISREG_PRR		0x04
#घोषणा CISREG_SCR		0x06
#घोषणा CISREG_ESR		0x08
#घोषणा CISREG_IOBASE_0		0x0a
#घोषणा CISREG_IOBASE_1		0x0c
#घोषणा CISREG_IOBASE_2		0x0e
#घोषणा CISREG_IOBASE_3		0x10
#घोषणा CISREG_IOSIZE		0x12

/*
 * Configuration Option Register
 */
#घोषणा COR_CONFIG_MASK		0x3f
#घोषणा COR_MFC_CONFIG_MASK	0x38
#घोषणा COR_FUNC_ENA		0x01
#घोषणा COR_ADDR_DECODE		0x02
#घोषणा COR_IREQ_ENA		0x04
#घोषणा COR_LEVEL_REQ		0x40
#घोषणा COR_SOFT_RESET		0x80

/*
 * Card Configuration and Status Register
 */
#घोषणा CCSR_INTR_ACK		0x01
#घोषणा CCSR_INTR_PENDING	0x02
#घोषणा CCSR_POWER_DOWN		0x04
#घोषणा CCSR_AUDIO_ENA		0x08
#घोषणा CCSR_IOIS8		0x20
#घोषणा CCSR_SIGCHG_ENA		0x40
#घोषणा CCSR_CHANGED		0x80

/*
 * Pin Replacement Register
 */
#घोषणा PRR_WP_STATUS		0x01
#घोषणा PRR_READY_STATUS	0x02
#घोषणा PRR_BVD2_STATUS		0x04
#घोषणा PRR_BVD1_STATUS		0x08
#घोषणा PRR_WP_EVENT		0x10
#घोषणा PRR_READY_EVENT		0x20
#घोषणा PRR_BVD2_EVENT		0x40
#घोषणा PRR_BVD1_EVENT		0x80

/*
 * Socket and Copy Register
 */
#घोषणा SCR_SOCKET_NUM		0x0f
#घोषणा SCR_COPY_NUM		0x70

/*
 * Extended Status Register
 */
#घोषणा ESR_REQ_ATTN_ENA	0x01
#घोषणा ESR_REQ_ATTN		0x10

/*
 * CardBus Function Status Registers
 */
#घोषणा CBFN_EVENT		0x00
#घोषणा CBFN_MASK		0x04
#घोषणा CBFN_STATE		0x08
#घोषणा CBFN_FORCE		0x0c

/*
 * These apply to all the CardBus function रेजिस्टरs
 */
#घोषणा CBFN_WP			0x0001
#घोषणा CBFN_READY		0x0002
#घोषणा CBFN_BVD2		0x0004
#घोषणा CBFN_BVD1		0x0008
#घोषणा CBFN_GWAKE		0x0010
#घोषणा CBFN_INTR		0x8000

/*
 * Extra bits in the Function Event Mask Register
 */
#घोषणा FEMR_BAM_ENA		0x0020
#घोषणा FEMR_PWM_ENA		0x0040
#घोषणा FEMR_WKUP_MASK		0x4000

/*
 * Indirect Addressing Registers क्रम Zoomed Video: these are addresses
 * in common memory space
 */
#घोषणा CISREG_ICTRL0		0x02	/* control रेजिस्टरs */
#घोषणा CISREG_ICTRL1		0x03
#घोषणा CISREG_IADDR0		0x04	/* address रेजिस्टरs */
#घोषणा CISREG_IADDR1		0x05
#घोषणा CISREG_IADDR2		0x06
#घोषणा CISREG_IADDR3		0x07
#घोषणा CISREG_IDATA0		0x08	/* data रेजिस्टरs */
#घोषणा CISREG_IDATA1		0x09

#घोषणा ICTRL0_COMMON		0x01
#घोषणा ICTRL0_AUTOINC		0x02
#घोषणा ICTRL0_BYTEGRAN		0x04

#पूर्ण_अगर /* _LINUX_CISREG_H */
