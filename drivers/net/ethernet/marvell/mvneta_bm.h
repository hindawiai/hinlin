<शैली गुरु>
/*
 * Driver क्रम Marvell NETA network controller Buffer Manager.
 *
 * Copyright (C) 2015 Marvell
 *
 * Marcin Wojtas <mw@semihalf.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#अगर_अघोषित _MVNETA_BM_H_
#घोषणा _MVNETA_BM_H_

/* BM Configuration Register */
#घोषणा MVNETA_BM_CONFIG_REG			0x0
#घोषणा    MVNETA_BM_STATUS_MASK		0x30
#घोषणा    MVNETA_BM_ACTIVE_MASK		BIT(4)
#घोषणा    MVNETA_BM_MAX_IN_BURST_SIZE_MASK	0x60000
#घोषणा    MVNETA_BM_MAX_IN_BURST_SIZE_16BP	BIT(18)
#घोषणा    MVNETA_BM_EMPTY_LIMIT_MASK		BIT(19)

/* BM Activation Register */
#घोषणा MVNETA_BM_COMMAND_REG			0x4
#घोषणा    MVNETA_BM_START_MASK			BIT(0)
#घोषणा    MVNETA_BM_STOP_MASK			BIT(1)
#घोषणा    MVNETA_BM_PAUSE_MASK			BIT(2)

/* BM Xbar पूर्णांकerface Register */
#घोषणा MVNETA_BM_XBAR_01_REG			0x8
#घोषणा MVNETA_BM_XBAR_23_REG			0xc
#घोषणा MVNETA_BM_XBAR_POOL_REG(pool)		\
		(((pool) < 2) ? MVNETA_BM_XBAR_01_REG : MVNETA_BM_XBAR_23_REG)
#घोषणा     MVNETA_BM_TARGET_ID_OFFS(pool)	(((pool) & 1) ? 16 : 0)
#घोषणा     MVNETA_BM_TARGET_ID_MASK(pool)	\
		(0xf << MVNETA_BM_TARGET_ID_OFFS(pool))
#घोषणा     MVNETA_BM_TARGET_ID_VAL(pool, id)	\
		((id) << MVNETA_BM_TARGET_ID_OFFS(pool))
#घोषणा     MVNETA_BM_XBAR_ATTR_OFFS(pool)	(((pool) & 1) ? 20 : 4)
#घोषणा     MVNETA_BM_XBAR_ATTR_MASK(pool)	\
		(0xff << MVNETA_BM_XBAR_ATTR_OFFS(pool))
#घोषणा     MVNETA_BM_XBAR_ATTR_VAL(pool, attr)	\
		((attr) << MVNETA_BM_XBAR_ATTR_OFFS(pool))

/* Address of External Buffer Poपूर्णांकers Pool Register */
#घोषणा MVNETA_BM_POOL_BASE_REG(pool)		(0x10 + ((pool) << 4))
#घोषणा     MVNETA_BM_POOL_ENABLE_MASK		BIT(0)

/* External Buffer Poपूर्णांकers Pool RD poपूर्णांकer Register */
#घोषणा MVNETA_BM_POOL_READ_PTR_REG(pool)	(0x14 + ((pool) << 4))
#घोषणा     MVNETA_BM_POOL_SET_READ_PTR_MASK	0xfffc
#घोषणा     MVNETA_BM_POOL_GET_READ_PTR_OFFS	16
#घोषणा     MVNETA_BM_POOL_GET_READ_PTR_MASK	0xfffc0000

/* External Buffer Poपूर्णांकers Pool WR poपूर्णांकer */
#घोषणा MVNETA_BM_POOL_WRITE_PTR_REG(pool)	(0x18 + ((pool) << 4))
#घोषणा     MVNETA_BM_POOL_SET_WRITE_PTR_OFFS	0
#घोषणा     MVNETA_BM_POOL_SET_WRITE_PTR_MASK	0xfffc
#घोषणा     MVNETA_BM_POOL_GET_WRITE_PTR_OFFS	16
#घोषणा     MVNETA_BM_POOL_GET_WRITE_PTR_MASK	0xfffc0000

/* External Buffer Poपूर्णांकers Pool Size Register */
#घोषणा MVNETA_BM_POOL_SIZE_REG(pool)		(0x1c + ((pool) << 4))
#घोषणा     MVNETA_BM_POOL_SIZE_MASK		0x3fff

/* BM Interrupt Cause Register */
#घोषणा MVNETA_BM_INTR_CAUSE_REG		(0x50)

/* BM पूर्णांकerrupt Mask Register */
#घोषणा MVNETA_BM_INTR_MASK_REG			(0x54)

/* Other definitions */
#घोषणा MVNETA_BM_SHORT_PKT_SIZE		256
#घोषणा MVNETA_BM_POOLS_NUM			4
#घोषणा MVNETA_BM_POOL_CAP_MIN			128
#घोषणा MVNETA_BM_POOL_CAP_DEF			2048
#घोषणा MVNETA_BM_POOL_CAP_MAX			\
		(16 * 1024 - MVNETA_BM_POOL_CAP_ALIGN)
#घोषणा MVNETA_BM_POOL_CAP_ALIGN		32
#घोषणा MVNETA_BM_POOL_PTR_ALIGN		32

#घोषणा MVNETA_BM_POOL_ACCESS_OFFS		8

#घोषणा MVNETA_BM_BPPI_SIZE			0x100000

#घोषणा MVNETA_RX_BUF_SIZE(pkt_size)   ((pkt_size) + NET_SKB_PAD)

क्रमागत mvneta_bm_type अणु
	MVNETA_BM_FREE,
	MVNETA_BM_LONG,
	MVNETA_BM_SHORT
पूर्ण;

काष्ठा mvneta_bm अणु
	व्योम __iomem *reg_base;
	काष्ठा clk *clk;
	काष्ठा platक्रमm_device *pdev;

	काष्ठा gen_pool *bppi_pool;
	/* BPPI भव base address */
	व्योम __iomem *bppi_virt_addr;
	/* BPPI physical base address */
	dma_addr_t bppi_phys_addr;

	/* BM pools */
	काष्ठा mvneta_bm_pool *bm_pools;
पूर्ण;

काष्ठा mvneta_bm_pool अणु
	काष्ठा hwbm_pool hwbm_pool;
	/* Pool number in the range 0-3 */
	u8 id;
	क्रमागत mvneta_bm_type type;

	/* Packet size */
	पूर्णांक pkt_size;
	/* Size of the buffer acces through DMA*/
	u32 buf_size;

	/* BPPE भव base address */
	u32 *virt_addr;
	/* BPPE physical base address */
	dma_addr_t phys_addr;

	/* Ports using BM pool */
	u8 port_map;

	काष्ठा mvneta_bm *priv;
पूर्ण;

/* Declarations and definitions */
#अगर IS_ENABLED(CONFIG_MVNETA_BM)
काष्ठा mvneta_bm *mvneta_bm_get(काष्ठा device_node *node);
व्योम mvneta_bm_put(काष्ठा mvneta_bm *priv);

व्योम mvneta_bm_pool_destroy(काष्ठा mvneta_bm *priv,
			    काष्ठा mvneta_bm_pool *bm_pool, u8 port_map);
व्योम mvneta_bm_bufs_मुक्त(काष्ठा mvneta_bm *priv, काष्ठा mvneta_bm_pool *bm_pool,
			 u8 port_map);
पूर्णांक mvneta_bm_स्थिरruct(काष्ठा hwbm_pool *hwbm_pool, व्योम *buf);
पूर्णांक mvneta_bm_pool_refill(काष्ठा mvneta_bm *priv,
			  काष्ठा mvneta_bm_pool *bm_pool);
काष्ठा mvneta_bm_pool *mvneta_bm_pool_use(काष्ठा mvneta_bm *priv, u8 pool_id,
					  क्रमागत mvneta_bm_type type, u8 port_id,
					  पूर्णांक pkt_size);

अटल अंतरभूत व्योम mvneta_bm_pool_put_bp(काष्ठा mvneta_bm *priv,
					 काष्ठा mvneta_bm_pool *bm_pool,
					 dma_addr_t buf_phys_addr)
अणु
	ग_लिखोl_relaxed(buf_phys_addr, priv->bppi_virt_addr +
		       (bm_pool->id << MVNETA_BM_POOL_ACCESS_OFFS));
पूर्ण

अटल अंतरभूत u32 mvneta_bm_pool_get_bp(काष्ठा mvneta_bm *priv,
					काष्ठा mvneta_bm_pool *bm_pool)
अणु
	वापस पढ़ोl_relaxed(priv->bppi_virt_addr +
			     (bm_pool->id << MVNETA_BM_POOL_ACCESS_OFFS));
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम mvneta_bm_pool_destroy(काष्ठा mvneta_bm *priv,
					  काष्ठा mvneta_bm_pool *bm_pool,
					  u8 port_map) अणुपूर्ण
अटल अंतरभूत व्योम mvneta_bm_bufs_मुक्त(काष्ठा mvneta_bm *priv,
				       काष्ठा mvneta_bm_pool *bm_pool,
				       u8 port_map) अणुपूर्ण
अटल अंतरभूत पूर्णांक mvneta_bm_स्थिरruct(काष्ठा hwbm_pool *hwbm_pool, व्योम *buf)
अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक mvneta_bm_pool_refill(काष्ठा mvneta_bm *priv,
					काष्ठा mvneta_bm_pool *bm_pool)
अणु वापस 0; पूर्ण
अटल अंतरभूत काष्ठा mvneta_bm_pool *mvneta_bm_pool_use(काष्ठा mvneta_bm *priv,
							u8 pool_id,
							क्रमागत mvneta_bm_type type,
							u8 port_id,
							पूर्णांक pkt_size)
अणु वापस शून्य; पूर्ण

अटल अंतरभूत व्योम mvneta_bm_pool_put_bp(काष्ठा mvneta_bm *priv,
					 काष्ठा mvneta_bm_pool *bm_pool,
					 dma_addr_t buf_phys_addr) अणुपूर्ण

अटल अंतरभूत u32 mvneta_bm_pool_get_bp(काष्ठा mvneta_bm *priv,
					काष्ठा mvneta_bm_pool *bm_pool)
अणु वापस 0; पूर्ण
अटल अंतरभूत काष्ठा mvneta_bm *mvneta_bm_get(काष्ठा device_node *node)
अणु वापस शून्य; पूर्ण
अटल अंतरभूत व्योम mvneta_bm_put(काष्ठा mvneta_bm *priv) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_MVNETA_BM */
#पूर्ण_अगर
