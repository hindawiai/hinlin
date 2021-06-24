<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 * Common header क्रम the legacy SH DMA driver and the new dmaengine driver
 *
 * extracted from arch/sh/include/यंत्र/dma-sh.h:
 *
 * Copyright (C) 2000  Takashi YOSHII
 * Copyright (C) 2003  Paul Mundt
 */
#अगर_अघोषित DMA_REGISTER_H
#घोषणा DMA_REGISTER_H

/* DMA रेजिस्टरs */
#घोषणा SAR	0x00	/* Source Address Register */
#घोषणा DAR	0x04	/* Destination Address Register */
#घोषणा TCR	0x08	/* Transfer Count Register */
#घोषणा CHCR	0x0C	/* Channel Control Register */
#घोषणा DMAOR	0x40	/* DMA Operation Register */

/* DMAOR definitions */
#घोषणा DMAOR_AE	0x00000004	/* Address Error Flag */
#घोषणा DMAOR_NMIF	0x00000002
#घोषणा DMAOR_DME	0x00000001	/* DMA Master Enable */

/* Definitions क्रम the SuperH DMAC */
#घोषणा REQ_L	0x00000000
#घोषणा REQ_E	0x00080000
#घोषणा RACK_H	0x00000000
#घोषणा RACK_L	0x00040000
#घोषणा ACK_R	0x00000000
#घोषणा ACK_W	0x00020000
#घोषणा ACK_H	0x00000000
#घोषणा ACK_L	0x00010000
#घोषणा DM_INC	0x00004000	/* Destination addresses are incremented */
#घोषणा DM_DEC	0x00008000	/* Destination addresses are decremented */
#घोषणा DM_FIX	0x0000c000	/* Destination address is fixed */
#घोषणा SM_INC	0x00001000	/* Source addresses are incremented */
#घोषणा SM_DEC	0x00002000	/* Source addresses are decremented */
#घोषणा SM_FIX	0x00003000	/* Source address is fixed */
#घोषणा RS_IN	0x00000200
#घोषणा RS_OUT	0x00000300
#घोषणा RS_AUTO	0x00000400	/* Auto Request */
#घोषणा RS_ERS	0x00000800	/* DMA extended resource selector */
#घोषणा TS_BLK	0x00000040
#घोषणा TM_BUR	0x00000020
#घोषणा CHCR_DE	0x00000001	/* DMA Enable */
#घोषणा CHCR_TE	0x00000002	/* Transfer End Flag */
#घोषणा CHCR_IE	0x00000004	/* Interrupt Enable */

#पूर्ण_अगर
