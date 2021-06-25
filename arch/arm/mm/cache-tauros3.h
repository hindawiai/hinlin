<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Marvell Tauros3 cache controller includes
 *
 * Sebastian Hesselbarth <sebastian.hesselbarth@gmail.com>
 *
 * based on GPL'ed 2.6 kernel sources
 *  (c) Marvell International Ltd.
 */

#अगर_अघोषित __ASM_ARM_HARDWARE_TAUROS3_H
#घोषणा __ASM_ARM_HARDWARE_TAUROS3_H

/*
 * Marvell Tauros3 L2CC is compatible with PL310 r0p0
 * but with PREFETCH_CTRL (r2p0) and an additional event counter.
 * Also, there is AUX2_CTRL क्रम some Marvell specअगरic control.
 */

#घोषणा TAUROS3_EVENT_CNT2_CFG		0x224
#घोषणा TAUROS3_EVENT_CNT2_VAL		0x228
#घोषणा TAUROS3_INV_ALL			0x780
#घोषणा TAUROS3_CLEAN_ALL		0x784
#घोषणा TAUROS3_AUX2_CTRL		0x820

/* Registers shअगरts and masks */
#घोषणा TAUROS3_AUX2_CTRL_LINEFILL_BURST8_EN	(1 << 2)

#पूर्ण_अगर
