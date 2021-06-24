<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Driver क्रम the Synopsys DesignWare DMA Controller
 *
 * Copyright (C) 2007 Aपंचांगel Corporation
 * Copyright (C) 2010-2011 ST Microelectronics
 */
#अगर_अघोषित _PLATFORM_DATA_DMA_DW_H
#घोषणा _PLATFORM_DATA_DMA_DW_H

#समावेश <linux/bits.h>
#समावेश <linux/types.h>

#घोषणा DW_DMA_MAX_NR_MASTERS	4
#घोषणा DW_DMA_MAX_NR_CHANNELS	8
#घोषणा DW_DMA_MIN_BURST	1
#घोषणा DW_DMA_MAX_BURST	256

काष्ठा device;

/**
 * काष्ठा dw_dma_slave - Controller-specअगरic inक्रमmation about a slave
 *
 * @dma_dev:	required DMA master device
 * @src_id:	src request line
 * @dst_id:	dst request line
 * @m_master:	memory master क्रम transfers on allocated channel
 * @p_master:	peripheral master क्रम transfers on allocated channel
 * @channels:	mask of the channels permitted क्रम allocation (zero value means any)
 * @hs_polarity:set active low polarity of handshake पूर्णांकerface
 */
काष्ठा dw_dma_slave अणु
	काष्ठा device		*dma_dev;
	u8			src_id;
	u8			dst_id;
	u8			m_master;
	u8			p_master;
	u8			channels;
	bool			hs_polarity;
पूर्ण;

/**
 * काष्ठा dw_dma_platक्रमm_data - Controller configuration parameters
 * @nr_channels: Number of channels supported by hardware (max 8)
 * @chan_allocation_order: Allocate channels starting from 0 or 7
 * @chan_priority: Set channel priority increasing from 0 to 7 or 7 to 0.
 * @block_size: Maximum block size supported by the controller
 * @nr_masters: Number of AHB masters supported by the controller
 * @data_width: Maximum data width supported by hardware per AHB master
 *		(in bytes, घातer of 2)
 * @multi_block: Multi block transfers supported by hardware per channel.
 * @max_burst: Maximum value of burst transaction size supported by hardware
 *	       per channel (in units of CTL.SRC_TR_WIDTH/CTL.DST_TR_WIDTH).
 * @protctl: Protection control संकेतs setting per channel.
 */
काष्ठा dw_dma_platक्रमm_data अणु
	अचिन्हित पूर्णांक	nr_channels;
#घोषणा CHAN_ALLOCATION_ASCENDING	0	/* zero to seven */
#घोषणा CHAN_ALLOCATION_DESCENDING	1	/* seven to zero */
	अचिन्हित अक्षर	chan_allocation_order;
#घोषणा CHAN_PRIORITY_ASCENDING		0	/* chan0 highest */
#घोषणा CHAN_PRIORITY_DESCENDING	1	/* chan7 highest */
	अचिन्हित अक्षर	chan_priority;
	अचिन्हित पूर्णांक	block_size;
	अचिन्हित अक्षर	nr_masters;
	अचिन्हित अक्षर	data_width[DW_DMA_MAX_NR_MASTERS];
	अचिन्हित अक्षर	multi_block[DW_DMA_MAX_NR_CHANNELS];
	u32		max_burst[DW_DMA_MAX_NR_CHANNELS];
#घोषणा CHAN_PROTCTL_PRIVILEGED		BIT(0)
#घोषणा CHAN_PROTCTL_BUFFERABLE		BIT(1)
#घोषणा CHAN_PROTCTL_CACHEABLE		BIT(2)
#घोषणा CHAN_PROTCTL_MASK		GENMASK(2, 0)
	अचिन्हित अक्षर	protctl;
पूर्ण;

#पूर्ण_अगर /* _PLATFORM_DATA_DMA_DW_H */
