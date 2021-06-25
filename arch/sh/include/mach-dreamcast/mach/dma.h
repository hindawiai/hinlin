<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 * include/यंत्र-sh/dreamcast/dma.h
 *
 * Copyright (C) 2003 Paul Mundt
 */
#अगर_अघोषित __ASM_SH_DREAMCAST_DMA_H
#घोषणा __ASM_SH_DREAMCAST_DMA_H

/* Number of DMA channels */
#घोषणा G2_NR_DMA_CHANNELS	4

/* Channels क्रम cascading */
#घोषणा PVR2_CASCADE_CHAN	2
#घोषणा G2_CASCADE_CHAN		3

/* PVR2 DMA Registers */
#घोषणा PVR2_DMA_BASE		0xa05f6800
#घोषणा PVR2_DMA_ADDR		(PVR2_DMA_BASE + 0)
#घोषणा PVR2_DMA_COUNT		(PVR2_DMA_BASE + 4)
#घोषणा PVR2_DMA_MODE		(PVR2_DMA_BASE + 8)
#घोषणा PVR2_DMA_LMMODE0	(PVR2_DMA_BASE + 132)
#घोषणा PVR2_DMA_LMMODE1	(PVR2_DMA_BASE + 136)

/* G2 DMA Register */
#घोषणा G2_DMA_BASE		0xa05f7800

#पूर्ण_अगर /* __ASM_SH_DREAMCAST_DMA_H */

