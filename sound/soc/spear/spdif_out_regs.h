<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * SPEAr SPDIF OUT controller header file
 *
 * Copyright (ST) 2011 Vipin Kumar (vipin.kumar@st.com)
 */

#अगर_अघोषित SPDIF_OUT_REGS_H
#घोषणा SPDIF_OUT_REGS_H

#घोषणा SPDIF_OUT_SOFT_RST	0x00
	#घोषणा SPDIF_OUT_RESET		(1 << 0)
#घोषणा SPDIF_OUT_FIFO_DATA	0x04
#घोषणा SPDIF_OUT_INT_STA	0x08
#घोषणा SPDIF_OUT_INT_STA_CLR	0x0C
	#घोषणा SPDIF_INT_UNDERFLOW	(1 << 0)
	#घोषणा SPDIF_INT_EODATA	(1 << 1)
	#घोषणा SPDIF_INT_EOBLOCK	(1 << 2)
	#घोषणा SPDIF_INT_EOLATENCY	(1 << 3)
	#घोषणा SPDIF_INT_EOPD_DATA	(1 << 4)
	#घोषणा SPDIF_INT_MEMFULLREAD	(1 << 5)
	#घोषणा SPDIF_INT_EOPD_PAUSE	(1 << 6)

#घोषणा SPDIF_OUT_INT_EN	0x10
#घोषणा SPDIF_OUT_INT_EN_SET	0x14
#घोषणा SPDIF_OUT_INT_EN_CLR	0x18
#घोषणा SPDIF_OUT_CTRL		0x1C
	#घोषणा SPDIF_OPMODE_MASK	(7 << 0)
	#घोषणा SPDIF_OPMODE_OFF	(0 << 0)
	#घोषणा SPDIF_OPMODE_MUTE_PCM	(1 << 0)
	#घोषणा SPDIF_OPMODE_MUTE_PAUSE	(2 << 0)
	#घोषणा SPDIF_OPMODE_AUD_DATA	(3 << 0)
	#घोषणा SPDIF_OPMODE_ENCODE	(4 << 0)
	#घोषणा SPDIF_STATE_NORMAL	(1 << 3)
	#घोषणा SPDIF_DIVIDER_MASK	(0xff << 5)
	#घोषणा SPDIF_DIVIDER_SHIFT	(5)
	#घोषणा SPDIF_SAMPLEREAD_MASK	(0x1ffff << 15)
	#घोषणा SPDIF_SAMPLEREAD_SHIFT	(15)
#घोषणा SPDIF_OUT_STA		0x20
#घोषणा SPDIF_OUT_PA_PB		0x24
#घोषणा SPDIF_OUT_PC_PD		0x28
#घोषणा SPDIF_OUT_CL1		0x2C
#घोषणा SPDIF_OUT_CR1		0x30
#घोषणा SPDIF_OUT_CL2_CR2_UV	0x34
#घोषणा SPDIF_OUT_PAUSE_LAT	0x38
#घोषणा SPDIF_OUT_FRMLEN_BRST	0x3C
#घोषणा SPDIF_OUT_CFG		0x40
	#घोषणा SPDIF_OUT_MEMFMT_16_0	(0 << 5)
	#घोषणा SPDIF_OUT_MEMFMT_16_16	(1 << 5)
	#घोषणा SPDIF_OUT_VALID_DMA	(0 << 3)
	#घोषणा SPDIF_OUT_VALID_HW	(1 << 3)
	#घोषणा SPDIF_OUT_USER_DMA	(0 << 2)
	#घोषणा SPDIF_OUT_USER_HW	(1 << 2)
	#घोषणा SPDIF_OUT_CHNLSTA_DMA	(0 << 1)
	#घोषणा SPDIF_OUT_CHNLSTA_HW	(1 << 1)
	#घोषणा SPDIF_OUT_PARITY_HW	(0 << 0)
	#घोषणा SPDIF_OUT_PARITY_DMA	(1 << 0)
	#घोषणा SPDIF_OUT_FDMA_TRIG_2	(2 << 8)
	#घोषणा SPDIF_OUT_FDMA_TRIG_6	(6 << 8)
	#घोषणा SPDIF_OUT_FDMA_TRIG_8	(8 << 8)
	#घोषणा SPDIF_OUT_FDMA_TRIG_10	(10 << 8)
	#घोषणा SPDIF_OUT_FDMA_TRIG_12	(12 << 8)
	#घोषणा SPDIF_OUT_FDMA_TRIG_16	(16 << 8)
	#घोषणा SPDIF_OUT_FDMA_TRIG_18	(18 << 8)

#पूर्ण_अगर /* SPDIF_OUT_REGS_H */
