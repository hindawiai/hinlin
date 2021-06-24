<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * SPEAr SPDIF IN controller header file
 *
 * Copyright (ST) 2011 Vipin Kumar (vipin.kumar@st.com)
 */

#अगर_अघोषित SPDIF_IN_REGS_H
#घोषणा SPDIF_IN_REGS_H

#घोषणा SPDIF_IN_CTRL		0x00
	#घोषणा SPDIF_IN_PRTYEN		(1 << 20)
	#घोषणा SPDIF_IN_STATEN		(1 << 19)
	#घोषणा SPDIF_IN_USREN		(1 << 18)
	#घोषणा SPDIF_IN_VALEN		(1 << 17)
	#घोषणा SPDIF_IN_BLKEN		(1 << 16)

	#घोषणा SPDIF_MODE_24BIT	(8 << 12)
	#घोषणा SPDIF_MODE_23BIT	(7 << 12)
	#घोषणा SPDIF_MODE_22BIT	(6 << 12)
	#घोषणा SPDIF_MODE_21BIT	(5 << 12)
	#घोषणा SPDIF_MODE_20BIT	(4 << 12)
	#घोषणा SPDIF_MODE_19BIT	(3 << 12)
	#घोषणा SPDIF_MODE_18BIT	(2 << 12)
	#घोषणा SPDIF_MODE_17BIT	(1 << 12)
	#घोषणा SPDIF_MODE_16BIT	(0 << 12)
	#घोषणा SPDIF_MODE_MASK		(0x0F << 12)

	#घोषणा SPDIF_IN_VALID		(1 << 11)
	#घोषणा SPDIF_IN_SAMPLE		(1 << 10)
	#घोषणा SPDIF_DATA_SWAP		(1 << 9)
	#घोषणा SPDIF_IN_ENB		(1 << 8)
	#घोषणा SPDIF_DATA_REVERT	(1 << 7)
	#घोषणा SPDIF_XTRACT_16BIT	(1 << 6)
	#घोषणा SPDIF_FIFO_THRES_16	(16 << 0)

#घोषणा SPDIF_IN_IRQ_MASK	0x04
#घोषणा SPDIF_IN_IRQ		0x08
	#घोषणा SPDIF_IRQ_FIFOWRITE	(1 << 0)
	#घोषणा SPDIF_IRQ_EMPTYFIFOREAD	(1 << 1)
	#घोषणा SPDIF_IRQ_FIFOFULL	(1 << 2)
	#घोषणा SPDIF_IRQ_OUTOFRANGE	(1 << 3)

#घोषणा SPDIF_IN_STA		0x0C
	#घोषणा SPDIF_IN_LOCK		(0x1 << 0)

#पूर्ण_अगर /* SPDIF_IN_REGS_H */
