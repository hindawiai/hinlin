<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 * SH4 CPU-specअगरic DMA definitions, used by both DMA drivers
 *
 * Copyright (C) 2010 Guennadi Liakhovetski <g.liakhovetski@gmx.de>
 */
#अगर_अघोषित CPU_DMA_REGISTER_H
#घोषणा CPU_DMA_REGISTER_H

/* SH7751/7760/7780 DMA IRQ sources */

#अगर_घोषित CONFIG_CPU_SH4A

#घोषणा DMAOR_INIT	DMAOR_DME

#अगर defined(CONFIG_CPU_SUBTYPE_SH7343)
#घोषणा CHCR_TS_LOW_MASK	0x00000018
#घोषणा CHCR_TS_LOW_SHIFT	3
#घोषणा CHCR_TS_HIGH_MASK	0
#घोषणा CHCR_TS_HIGH_SHIFT	0
#या_अगर defined(CONFIG_CPU_SUBTYPE_SH7722) || \
	defined(CONFIG_CPU_SUBTYPE_SH7723) || \
	defined(CONFIG_CPU_SUBTYPE_SH7724) || \
	defined(CONFIG_CPU_SUBTYPE_SH7730) || \
	defined(CONFIG_CPU_SUBTYPE_SH7786)
#घोषणा CHCR_TS_LOW_MASK	0x00000018
#घोषणा CHCR_TS_LOW_SHIFT	3
#घोषणा CHCR_TS_HIGH_MASK	0x00300000
#घोषणा CHCR_TS_HIGH_SHIFT	(20 - 2)	/* 2 bits क्रम shअगरted low TS */
#या_अगर defined(CONFIG_CPU_SUBTYPE_SH7757) || \
	defined(CONFIG_CPU_SUBTYPE_SH7763) || \
	defined(CONFIG_CPU_SUBTYPE_SH7780) || \
	defined(CONFIG_CPU_SUBTYPE_SH7785)
#घोषणा CHCR_TS_LOW_MASK	0x00000018
#घोषणा CHCR_TS_LOW_SHIFT	3
#घोषणा CHCR_TS_HIGH_MASK	0x00100000
#घोषणा CHCR_TS_HIGH_SHIFT	(20 - 2)	/* 2 bits क्रम shअगरted low TS */
#पूर्ण_अगर

/* Transmit sizes and respective CHCR रेजिस्टर values */
क्रमागत अणु
	XMIT_SZ_8BIT		= 0,
	XMIT_SZ_16BIT		= 1,
	XMIT_SZ_32BIT		= 2,
	XMIT_SZ_64BIT		= 7,
	XMIT_SZ_128BIT		= 3,
	XMIT_SZ_256BIT		= 4,
	XMIT_SZ_128BIT_BLK	= 0xb,
	XMIT_SZ_256BIT_BLK	= 0xc,
पूर्ण;

/* log2(size / 8) - used to calculate number of transfers */
#घोषणा TS_SHIFT अणु			\
	[XMIT_SZ_8BIT]		= 0,	\
	[XMIT_SZ_16BIT]		= 1,	\
	[XMIT_SZ_32BIT]		= 2,	\
	[XMIT_SZ_64BIT]		= 3,	\
	[XMIT_SZ_128BIT]	= 4,	\
	[XMIT_SZ_256BIT]	= 5,	\
	[XMIT_SZ_128BIT_BLK]	= 4,	\
	[XMIT_SZ_256BIT_BLK]	= 5,	\
पूर्ण

#घोषणा TS_INDEX2VAL(i)	((((i) & 3) << CHCR_TS_LOW_SHIFT) | \
			 (((i) & 0xc) << CHCR_TS_HIGH_SHIFT))

#अन्यथा /* CONFIG_CPU_SH4A */

#घोषणा DMAOR_INIT	(0x8000 | DMAOR_DME)

#घोषणा CHCR_TS_LOW_MASK	0x70
#घोषणा CHCR_TS_LOW_SHIFT	4
#घोषणा CHCR_TS_HIGH_MASK	0
#घोषणा CHCR_TS_HIGH_SHIFT	0

/* Transmit sizes and respective CHCR रेजिस्टर values */
क्रमागत अणु
	XMIT_SZ_8BIT	= 1,
	XMIT_SZ_16BIT	= 2,
	XMIT_SZ_32BIT	= 3,
	XMIT_SZ_64BIT	= 0,
	XMIT_SZ_256BIT	= 4,
पूर्ण;

/* log2(size / 8) - used to calculate number of transfers */
#घोषणा TS_SHIFT अणु			\
	[XMIT_SZ_8BIT]		= 0,	\
	[XMIT_SZ_16BIT]		= 1,	\
	[XMIT_SZ_32BIT]		= 2,	\
	[XMIT_SZ_64BIT]		= 3,	\
	[XMIT_SZ_256BIT]	= 5,	\
पूर्ण

#घोषणा TS_INDEX2VAL(i)	(((i) & 7) << CHCR_TS_LOW_SHIFT)

#पूर्ण_अगर /* CONFIG_CPU_SH4A */

#पूर्ण_अगर
