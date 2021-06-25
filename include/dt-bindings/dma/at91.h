<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * This header provides macros क्रम at91 dma bindings.
 *
 * Copyright (C) 2013 Luकरोvic Desroches <luकरोvic.desroches@aपंचांगel.com>
 */

#अगर_अघोषित __DT_BINDINGS_AT91_DMA_H__
#घोषणा __DT_BINDINGS_AT91_DMA_H__

/* ---------- HDMAC ---------- */

/*
 * Source and/or destination peripheral ID
 */
#घोषणा AT91_DMA_CFG_PER_ID_MASK	(0xff)
#घोषणा AT91_DMA_CFG_PER_ID(id)		(id & AT91_DMA_CFG_PER_ID_MASK)

/*
 * FIFO configuration: it defines when a request is serviced.
 */
#घोषणा AT91_DMA_CFG_FIFOCFG_OFFSET	(8)
#घोषणा AT91_DMA_CFG_FIFOCFG_MASK	(0xf << AT91_DMA_CFG_FIFOCFG_OFFSET)
#घोषणा AT91_DMA_CFG_FIFOCFG_HALF	(0x0 << AT91_DMA_CFG_FIFOCFG_OFFSET)	/* half FIFO (शेष behavior) */
#घोषणा AT91_DMA_CFG_FIFOCFG_ALAP	(0x1 << AT91_DMA_CFG_FIFOCFG_OFFSET)	/* largest defined AHB burst */
#घोषणा AT91_DMA_CFG_FIFOCFG_ASAP	(0x2 << AT91_DMA_CFG_FIFOCFG_OFFSET)	/* single AHB access */


/* ---------- XDMAC ---------- */
#घोषणा AT91_XDMAC_DT_MEM_IF_MASK	(0x1)
#घोषणा AT91_XDMAC_DT_MEM_IF_OFFSET	(13)
#घोषणा AT91_XDMAC_DT_MEM_IF(mem_अगर)	(((mem_अगर) & AT91_XDMAC_DT_MEM_IF_MASK) \
					<< AT91_XDMAC_DT_MEM_IF_OFFSET)
#घोषणा AT91_XDMAC_DT_GET_MEM_IF(cfg)	(((cfg) >> AT91_XDMAC_DT_MEM_IF_OFFSET) \
					& AT91_XDMAC_DT_MEM_IF_MASK)

#घोषणा AT91_XDMAC_DT_PER_IF_MASK	(0x1)
#घोषणा AT91_XDMAC_DT_PER_IF_OFFSET	(14)
#घोषणा AT91_XDMAC_DT_PER_IF(per_अगर)	(((per_अगर) & AT91_XDMAC_DT_PER_IF_MASK) \
					<< AT91_XDMAC_DT_PER_IF_OFFSET)
#घोषणा AT91_XDMAC_DT_GET_PER_IF(cfg)	(((cfg) >> AT91_XDMAC_DT_PER_IF_OFFSET) \
					& AT91_XDMAC_DT_PER_IF_MASK)

#घोषणा AT91_XDMAC_DT_PERID_MASK	(0x7f)
#घोषणा AT91_XDMAC_DT_PERID_OFFSET	(24)
#घोषणा AT91_XDMAC_DT_PERID(perid)	(((perid) & AT91_XDMAC_DT_PERID_MASK) \
					<< AT91_XDMAC_DT_PERID_OFFSET)
#घोषणा AT91_XDMAC_DT_GET_PERID(cfg)	(((cfg) >> AT91_XDMAC_DT_PERID_OFFSET) \
					& AT91_XDMAC_DT_PERID_MASK)

#पूर्ण_अगर /* __DT_BINDINGS_AT91_DMA_H__ */
