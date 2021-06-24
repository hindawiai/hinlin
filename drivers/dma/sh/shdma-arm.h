<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Renesas SuperH DMA Engine support
 *
 * Copyright (C) 2013 Renesas Electronics, Inc.
 */

#अगर_अघोषित SHDMA_ARM_H
#घोषणा SHDMA_ARM_H

#समावेश "shdma.h"

/* Transmit sizes and respective CHCR रेजिस्टर values */
क्रमागत अणु
	XMIT_SZ_8BIT		= 0,
	XMIT_SZ_16BIT		= 1,
	XMIT_SZ_32BIT		= 2,
	XMIT_SZ_64BIT		= 7,
	XMIT_SZ_128BIT		= 3,
	XMIT_SZ_256BIT		= 4,
	XMIT_SZ_512BIT		= 5,
पूर्ण;

/* log2(size / 8) - used to calculate number of transfers */
#घोषणा SH_DMAE_TS_SHIFT अणु		\
	[XMIT_SZ_8BIT]		= 0,	\
	[XMIT_SZ_16BIT]		= 1,	\
	[XMIT_SZ_32BIT]		= 2,	\
	[XMIT_SZ_64BIT]		= 3,	\
	[XMIT_SZ_128BIT]	= 4,	\
	[XMIT_SZ_256BIT]	= 5,	\
	[XMIT_SZ_512BIT]	= 6,	\
पूर्ण

#घोषणा TS_LOW_BIT	0x3 /* --xx */
#घोषणा TS_HI_BIT	0xc /* xx-- */

#घोषणा TS_LOW_SHIFT	(3)
#घोषणा TS_HI_SHIFT	(20 - 2)	/* 2 bits क्रम shअगरted low TS */

#घोषणा TS_INDEX2VAL(i) \
	((((i) & TS_LOW_BIT) << TS_LOW_SHIFT) |\
	 (((i) & TS_HI_BIT)  << TS_HI_SHIFT))

#घोषणा CHCR_TX(xmit_sz) (DM_FIX | SM_INC | RS_ERS | TS_INDEX2VAL((xmit_sz)))
#घोषणा CHCR_RX(xmit_sz) (DM_INC | SM_FIX | RS_ERS | TS_INDEX2VAL((xmit_sz)))

#पूर्ण_अगर
