<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 * SH3 CPU-specअगरic DMA definitions, used by both DMA drivers
 *
 * Copyright (C) 2010 Guennadi Liakhovetski <g.liakhovetski@gmx.de>
 */
#अगर_अघोषित CPU_DMA_REGISTER_H
#घोषणा CPU_DMA_REGISTER_H

#घोषणा CHCR_TS_LOW_MASK	0x18
#घोषणा CHCR_TS_LOW_SHIFT	3
#घोषणा CHCR_TS_HIGH_MASK	0
#घोषणा CHCR_TS_HIGH_SHIFT	0

#घोषणा DMAOR_INIT	DMAOR_DME

/*
 * The SuperH DMAC supports a number of transmit sizes, we list them here,
 * with their respective values as they appear in the CHCR रेजिस्टरs.
 */
क्रमागत अणु
	XMIT_SZ_8BIT,
	XMIT_SZ_16BIT,
	XMIT_SZ_32BIT,
	XMIT_SZ_128BIT,
पूर्ण;

/* log2(size / 8) - used to calculate number of transfers */
#घोषणा TS_SHIFT अणु			\
	[XMIT_SZ_8BIT]		= 0,	\
	[XMIT_SZ_16BIT]		= 1,	\
	[XMIT_SZ_32BIT]		= 2,	\
	[XMIT_SZ_128BIT]	= 4,	\
पूर्ण

#घोषणा TS_INDEX2VAL(i)	(((i) & 3) << CHCR_TS_LOW_SHIFT)

#पूर्ण_अगर
