<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Header क्रम the new SH dmaengine driver
 *
 * Copyright (C) 2010 Guennadi Liakhovetski <g.liakhovetski@gmx.de>
 */
#अगर_अघोषित SH_DMA_H
#घोषणा SH_DMA_H

#समावेश <linux/dmaengine.h>
#समावेश <linux/list.h>
#समावेश <linux/shdma-base.h>
#समावेश <linux/types.h>

काष्ठा device;

/* Used by slave DMA clients to request DMA to/from a specअगरic peripheral */
काष्ठा sh_dmae_slave अणु
	काष्ठा shdma_slave		shdma_slave;	/* Set by the platक्रमm */
पूर्ण;

/*
 * Supplied by platक्रमms to specअगरy, how a DMA channel has to be configured क्रम
 * a certain peripheral
 */
काष्ठा sh_dmae_slave_config अणु
	पूर्णांक		slave_id;
	dma_addr_t	addr;
	u32		chcr;
	अक्षर		mid_rid;
पूर्ण;

/**
 * काष्ठा sh_dmae_channel - DMAC channel platक्रमm data
 * @offset:		रेजिस्टर offset within the मुख्य IOMEM resource
 * @dmars:		channel DMARS रेजिस्टर offset
 * @chclr_offset:	channel CHCLR रेजिस्टर offset
 * @dmars_bit:		channel DMARS field offset within the रेजिस्टर
 * @chclr_bit:		bit position, to be set to reset the channel
 */
काष्ठा sh_dmae_channel अणु
	अचिन्हित पूर्णांक	offset;
	अचिन्हित पूर्णांक	dmars;
	अचिन्हित पूर्णांक	chclr_offset;
	अचिन्हित अक्षर	dmars_bit;
	अचिन्हित अक्षर	chclr_bit;
पूर्ण;

/**
 * काष्ठा sh_dmae_pdata - DMAC platक्रमm data
 * @slave:		array of slaves
 * @slave_num:		number of slaves in the above array
 * @channel:		array of DMA channels
 * @channel_num:	number of channels in the above array
 * @ts_low_shअगरt:	shअगरt of the low part of the TS field
 * @ts_low_mask:	low TS field mask
 * @ts_high_shअगरt:	additional shअगरt of the high part of the TS field
 * @ts_high_mask:	high TS field mask
 * @ts_shअगरt:		array of Transfer Size shअगरts, indexed by TS value
 * @ts_shअगरt_num:	number of shअगरts in the above array
 * @dmaor_init:		DMAOR initialisation value
 * @chcr_offset:	CHCR address offset
 * @chcr_ie_bit:	CHCR Interrupt Enable bit
 * @dmaor_is_32bit:	DMAOR is a 32-bit रेजिस्टर
 * @needs_tend_set:	the TEND रेजिस्टर has to be set
 * @no_dmars:		DMAC has no DMARS रेजिस्टरs
 * @chclr_present:	DMAC has one or several CHCLR रेजिस्टरs
 * @chclr_bitwise:	channel CHCLR रेजिस्टरs are bitwise
 * @slave_only:		DMAC cannot be used क्रम MEMCPY
 */
काष्ठा sh_dmae_pdata अणु
	स्थिर काष्ठा sh_dmae_slave_config *slave;
	पूर्णांक slave_num;
	स्थिर काष्ठा sh_dmae_channel *channel;
	पूर्णांक channel_num;
	अचिन्हित पूर्णांक ts_low_shअगरt;
	अचिन्हित पूर्णांक ts_low_mask;
	अचिन्हित पूर्णांक ts_high_shअगरt;
	अचिन्हित पूर्णांक ts_high_mask;
	स्थिर अचिन्हित पूर्णांक *ts_shअगरt;
	पूर्णांक ts_shअगरt_num;
	u16 dmaor_init;
	अचिन्हित पूर्णांक chcr_offset;
	u32 chcr_ie_bit;

	अचिन्हित पूर्णांक dmaor_is_32bit:1;
	अचिन्हित पूर्णांक needs_tend_set:1;
	अचिन्हित पूर्णांक no_dmars:1;
	अचिन्हित पूर्णांक chclr_present:1;
	अचिन्हित पूर्णांक chclr_bitwise:1;
	अचिन्हित पूर्णांक slave_only:1;
पूर्ण;

/* DMAOR definitions */
#घोषणा DMAOR_AE	0x00000004	/* Address Error Flag */
#घोषणा DMAOR_NMIF	0x00000002
#घोषणा DMAOR_DME	0x00000001	/* DMA Master Enable */

/* Definitions क्रम the SuperH DMAC */
#घोषणा DM_INC	0x00004000	/* Destination addresses are incremented */
#घोषणा DM_DEC	0x00008000	/* Destination addresses are decremented */
#घोषणा DM_FIX	0x0000c000	/* Destination address is fixed */
#घोषणा SM_INC	0x00001000	/* Source addresses are incremented */
#घोषणा SM_DEC	0x00002000	/* Source addresses are decremented */
#घोषणा SM_FIX	0x00003000	/* Source address is fixed */
#घोषणा RS_AUTO	0x00000400	/* Auto Request */
#घोषणा RS_ERS	0x00000800	/* DMA extended resource selector */
#घोषणा CHCR_DE	0x00000001	/* DMA Enable */
#घोषणा CHCR_TE	0x00000002	/* Transfer End Flag */
#घोषणा CHCR_IE	0x00000004	/* Interrupt Enable */

#पूर्ण_अगर
