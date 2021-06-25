<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2018-2019 Synopsys, Inc. and/or its affiliates.
 * Synopsys DesignWare eDMA core driver
 *
 * Author: Gustavo Pimentel <gustavo.pimentel@synopsys.com>
 */

#अगर_अघोषित _DW_EDMA_CORE_H
#घोषणा _DW_EDMA_CORE_H

#समावेश <linux/msi.h>
#समावेश <linux/dma/edma.h>

#समावेश "../virt-dma.h"

#घोषणा EDMA_LL_SZ					24
#घोषणा EDMA_MAX_WR_CH					8
#घोषणा EDMA_MAX_RD_CH					8

क्रमागत dw_edma_dir अणु
	EDMA_सूची_WRITE = 0,
	EDMA_सूची_READ
पूर्ण;

क्रमागत dw_edma_map_क्रमmat अणु
	EDMA_MF_EDMA_LEGACY = 0x0,
	EDMA_MF_EDMA_UNROLL = 0x1,
	EDMA_MF_HDMA_COMPAT = 0x5
पूर्ण;

क्रमागत dw_edma_request अणु
	EDMA_REQ_NONE = 0,
	EDMA_REQ_STOP,
	EDMA_REQ_PAUSE
पूर्ण;

क्रमागत dw_edma_status अणु
	EDMA_ST_IDLE = 0,
	EDMA_ST_PAUSE,
	EDMA_ST_BUSY
पूर्ण;

क्रमागत dw_edma_xfer_type अणु
	EDMA_XFER_SCATTER_GATHER = 0,
	EDMA_XFER_CYCLIC,
	EDMA_XFER_INTERLEAVED
पूर्ण;

काष्ठा dw_edma_chan;
काष्ठा dw_edma_chunk;

काष्ठा dw_edma_burst अणु
	काष्ठा list_head		list;
	u64				sar;
	u64				dar;
	u32				sz;
पूर्ण;

काष्ठा dw_edma_region अणु
	phys_addr_t			paddr;
	व्योम				__iomem *vaddr;
	माप_प्रकार				sz;
पूर्ण;

काष्ठा dw_edma_chunk अणु
	काष्ठा list_head		list;
	काष्ठा dw_edma_chan		*chan;
	काष्ठा dw_edma_burst		*burst;

	u32				bursts_alloc;

	u8				cb;
	काष्ठा dw_edma_region		ll_region;	/* Linked list */
पूर्ण;

काष्ठा dw_edma_desc अणु
	काष्ठा virt_dma_desc		vd;
	काष्ठा dw_edma_chan		*chan;
	काष्ठा dw_edma_chunk		*chunk;

	u32				chunks_alloc;

	u32				alloc_sz;
	u32				xfer_sz;
पूर्ण;

काष्ठा dw_edma_chan अणु
	काष्ठा virt_dma_chan		vc;
	काष्ठा dw_edma_chip		*chip;
	पूर्णांक				id;
	क्रमागत dw_edma_dir		dir;

	u32				ll_max;

	काष्ठा msi_msg			msi;

	क्रमागत dw_edma_request		request;
	क्रमागत dw_edma_status		status;
	u8				configured;

	काष्ठा dma_slave_config		config;
पूर्ण;

काष्ठा dw_edma_irq अणु
	काष्ठा msi_msg                  msi;
	u32				wr_mask;
	u32				rd_mask;
	काष्ठा dw_edma			*dw;
पूर्ण;

काष्ठा dw_edma_core_ops अणु
	पूर्णांक	(*irq_vector)(काष्ठा device *dev, अचिन्हित पूर्णांक nr);
पूर्ण;

काष्ठा dw_edma अणु
	अक्षर				name[20];

	काष्ठा dma_device		wr_edma;
	u16				wr_ch_cnt;

	काष्ठा dma_device		rd_edma;
	u16				rd_ch_cnt;

	काष्ठा dw_edma_region		rg_region;	/* Registers */
	काष्ठा dw_edma_region		ll_region_wr[EDMA_MAX_WR_CH];
	काष्ठा dw_edma_region		ll_region_rd[EDMA_MAX_RD_CH];
	काष्ठा dw_edma_region		dt_region_wr[EDMA_MAX_WR_CH];
	काष्ठा dw_edma_region		dt_region_rd[EDMA_MAX_RD_CH];

	काष्ठा dw_edma_irq		*irq;
	पूर्णांक				nr_irqs;

	क्रमागत dw_edma_map_क्रमmat		mf;

	काष्ठा dw_edma_chan		*chan;
	स्थिर काष्ठा dw_edma_core_ops	*ops;

	raw_spinlock_t			lock;		/* Only क्रम legacy */
#अगर_घोषित CONFIG_DEBUG_FS
	काष्ठा dentry			*debugfs;
#पूर्ण_अगर /* CONFIG_DEBUG_FS */
पूर्ण;

काष्ठा dw_edma_sg अणु
	काष्ठा scatterlist		*sgl;
	अचिन्हित पूर्णांक			len;
पूर्ण;

काष्ठा dw_edma_cyclic अणु
	dma_addr_t			paddr;
	माप_प्रकार				len;
	माप_प्रकार				cnt;
पूर्ण;

काष्ठा dw_edma_transfer अणु
	काष्ठा dma_chan			*dchan;
	जोड़ dw_edma_xfer अणु
		काष्ठा dw_edma_sg		sg;
		काष्ठा dw_edma_cyclic		cyclic;
		काष्ठा dma_पूर्णांकerleaved_ढाँचा *il;
	पूर्ण xfer;
	क्रमागत dma_transfer_direction	direction;
	अचिन्हित दीर्घ			flags;
	क्रमागत dw_edma_xfer_type		type;
पूर्ण;

अटल अंतरभूत
काष्ठा dw_edma_chan *vc2dw_edma_chan(काष्ठा virt_dma_chan *vc)
अणु
	वापस container_of(vc, काष्ठा dw_edma_chan, vc);
पूर्ण

अटल अंतरभूत
काष्ठा dw_edma_chan *dchan2dw_edma_chan(काष्ठा dma_chan *dchan)
अणु
	वापस vc2dw_edma_chan(to_virt_chan(dchan));
पूर्ण

#पूर्ण_अगर /* _DW_EDMA_CORE_H */
