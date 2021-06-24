<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * OMAP DMAengine support
 */
#समावेश <linux/cpu_pm.h>
#समावेश <linux/delay.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/omap-dma.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/of_dma.h>
#समावेश <linux/of_device.h>

#समावेश "../virt-dma.h"

#घोषणा OMAP_SDMA_REQUESTS	127
#घोषणा OMAP_SDMA_CHANNELS	32

काष्ठा omap_dma_config अणु
	पूर्णांक lch_end;
	अचिन्हित पूर्णांक rw_priority:1;
	अचिन्हित पूर्णांक needs_busy_check:1;
	अचिन्हित पूर्णांक may_lose_context:1;
	अचिन्हित पूर्णांक needs_lch_clear:1;
पूर्ण;

काष्ठा omap_dma_context अणु
	u32 irqenable_l0;
	u32 irqenable_l1;
	u32 ocp_sysconfig;
	u32 gcr;
पूर्ण;

काष्ठा omap_dmadev अणु
	काष्ठा dma_device ddev;
	spinlock_t lock;
	व्योम __iomem *base;
	स्थिर काष्ठा omap_dma_reg *reg_map;
	काष्ठा omap_प्रणाली_dma_plat_info *plat;
	स्थिर काष्ठा omap_dma_config *cfg;
	काष्ठा notअगरier_block nb;
	काष्ठा omap_dma_context context;
	पूर्णांक lch_count;
	DECLARE_BITMAP(lch_biपंचांगap, OMAP_SDMA_CHANNELS);
	काष्ठा mutex lch_lock;		/* क्रम assigning logical channels */
	bool legacy;
	bool ll123_supported;
	काष्ठा dma_pool *desc_pool;
	अचिन्हित dma_requests;
	spinlock_t irq_lock;
	uपूर्णांक32_t irq_enable_mask;
	काष्ठा omap_chan **lch_map;
पूर्ण;

काष्ठा omap_chan अणु
	काष्ठा virt_dma_chan vc;
	व्योम __iomem *channel_base;
	स्थिर काष्ठा omap_dma_reg *reg_map;
	uपूर्णांक32_t ccr;

	काष्ठा dma_slave_config	cfg;
	अचिन्हित dma_sig;
	bool cyclic;
	bool छोड़ोd;
	bool running;

	पूर्णांक dma_ch;
	काष्ठा omap_desc *desc;
	अचिन्हित sgidx;
पूर्ण;

#घोषणा DESC_NXT_SV_REFRESH	(0x1 << 24)
#घोषणा DESC_NXT_SV_REUSE	(0x2 << 24)
#घोषणा DESC_NXT_DV_REFRESH	(0x1 << 26)
#घोषणा DESC_NXT_DV_REUSE	(0x2 << 26)
#घोषणा DESC_NTYPE_TYPE2	(0x2 << 29)

/* Type 2 descriptor with Source or Destination address update */
काष्ठा omap_type2_desc अणु
	uपूर्णांक32_t next_desc;
	uपूर्णांक32_t en;
	uपूर्णांक32_t addr; /* src or dst */
	uपूर्णांक16_t fn;
	uपूर्णांक16_t cicr;
	पूर्णांक16_t cdei;
	पूर्णांक16_t csei;
	पूर्णांक32_t cdfi;
	पूर्णांक32_t csfi;
पूर्ण __packed;

काष्ठा omap_sg अणु
	dma_addr_t addr;
	uपूर्णांक32_t en;		/* number of elements (24-bit) */
	uपूर्णांक32_t fn;		/* number of frames (16-bit) */
	पूर्णांक32_t fi;		/* क्रम द्विगुन indexing */
	पूर्णांक16_t ei;		/* क्रम द्विगुन indexing */

	/* Linked list */
	काष्ठा omap_type2_desc *t2_desc;
	dma_addr_t t2_desc_paddr;
पूर्ण;

काष्ठा omap_desc अणु
	काष्ठा virt_dma_desc vd;
	bool using_ll;
	क्रमागत dma_transfer_direction dir;
	dma_addr_t dev_addr;
	bool polled;

	पूर्णांक32_t fi;		/* क्रम OMAP_DMA_SYNC_PACKET / द्विगुन indexing */
	पूर्णांक16_t ei;		/* क्रम द्विगुन indexing */
	uपूर्णांक8_t es;		/* CSDP_DATA_TYPE_xxx */
	uपूर्णांक32_t ccr;		/* CCR value */
	uपूर्णांक16_t clnk_ctrl;	/* CLNK_CTRL value */
	uपूर्णांक16_t cicr;		/* CICR value */
	uपूर्णांक32_t csdp;		/* CSDP value */

	अचिन्हित sglen;
	काष्ठा omap_sg sg[];
पूर्ण;

क्रमागत अणु
	CAPS_0_SUPPORT_LL123	= BIT(20),	/* Linked List type1/2/3 */
	CAPS_0_SUPPORT_LL4	= BIT(21),	/* Linked List type4 */

	CCR_FS			= BIT(5),
	CCR_READ_PRIORITY	= BIT(6),
	CCR_ENABLE		= BIT(7),
	CCR_AUTO_INIT		= BIT(8),	/* OMAP1 only */
	CCR_REPEAT		= BIT(9),	/* OMAP1 only */
	CCR_OMAP31_DISABLE	= BIT(10),	/* OMAP1 only */
	CCR_SUSPEND_SENSITIVE	= BIT(8),	/* OMAP2+ only */
	CCR_RD_ACTIVE		= BIT(9),	/* OMAP2+ only */
	CCR_WR_ACTIVE		= BIT(10),	/* OMAP2+ only */
	CCR_SRC_AMODE_CONSTANT	= 0 << 12,
	CCR_SRC_AMODE_POSTINC	= 1 << 12,
	CCR_SRC_AMODE_SGLIDX	= 2 << 12,
	CCR_SRC_AMODE_DBLIDX	= 3 << 12,
	CCR_DST_AMODE_CONSTANT	= 0 << 14,
	CCR_DST_AMODE_POSTINC	= 1 << 14,
	CCR_DST_AMODE_SGLIDX	= 2 << 14,
	CCR_DST_AMODE_DBLIDX	= 3 << 14,
	CCR_CONSTANT_FILL	= BIT(16),
	CCR_TRANSPARENT_COPY	= BIT(17),
	CCR_BS			= BIT(18),
	CCR_SUPERVISOR		= BIT(22),
	CCR_PREFETCH		= BIT(23),
	CCR_TRIGGER_SRC		= BIT(24),
	CCR_BUFFERING_DISABLE	= BIT(25),
	CCR_WRITE_PRIORITY	= BIT(26),
	CCR_SYNC_ELEMENT	= 0,
	CCR_SYNC_FRAME		= CCR_FS,
	CCR_SYNC_BLOCK		= CCR_BS,
	CCR_SYNC_PACKET		= CCR_BS | CCR_FS,

	CSDP_DATA_TYPE_8	= 0,
	CSDP_DATA_TYPE_16	= 1,
	CSDP_DATA_TYPE_32	= 2,
	CSDP_SRC_PORT_EMIFF	= 0 << 2, /* OMAP1 only */
	CSDP_SRC_PORT_EMIFS	= 1 << 2, /* OMAP1 only */
	CSDP_SRC_PORT_OCP_T1	= 2 << 2, /* OMAP1 only */
	CSDP_SRC_PORT_TIPB	= 3 << 2, /* OMAP1 only */
	CSDP_SRC_PORT_OCP_T2	= 4 << 2, /* OMAP1 only */
	CSDP_SRC_PORT_MPUI	= 5 << 2, /* OMAP1 only */
	CSDP_SRC_PACKED		= BIT(6),
	CSDP_SRC_BURST_1	= 0 << 7,
	CSDP_SRC_BURST_16	= 1 << 7,
	CSDP_SRC_BURST_32	= 2 << 7,
	CSDP_SRC_BURST_64	= 3 << 7,
	CSDP_DST_PORT_EMIFF	= 0 << 9, /* OMAP1 only */
	CSDP_DST_PORT_EMIFS	= 1 << 9, /* OMAP1 only */
	CSDP_DST_PORT_OCP_T1	= 2 << 9, /* OMAP1 only */
	CSDP_DST_PORT_TIPB	= 3 << 9, /* OMAP1 only */
	CSDP_DST_PORT_OCP_T2	= 4 << 9, /* OMAP1 only */
	CSDP_DST_PORT_MPUI	= 5 << 9, /* OMAP1 only */
	CSDP_DST_PACKED		= BIT(13),
	CSDP_DST_BURST_1	= 0 << 14,
	CSDP_DST_BURST_16	= 1 << 14,
	CSDP_DST_BURST_32	= 2 << 14,
	CSDP_DST_BURST_64	= 3 << 14,
	CSDP_WRITE_NON_POSTED	= 0 << 16,
	CSDP_WRITE_POSTED	= 1 << 16,
	CSDP_WRITE_LAST_NON_POSTED = 2 << 16,

	CICR_TOUT_IE		= BIT(0),	/* OMAP1 only */
	CICR_DROP_IE		= BIT(1),
	CICR_HALF_IE		= BIT(2),
	CICR_FRAME_IE		= BIT(3),
	CICR_LAST_IE		= BIT(4),
	CICR_BLOCK_IE		= BIT(5),
	CICR_PKT_IE		= BIT(7),	/* OMAP2+ only */
	CICR_TRANS_ERR_IE	= BIT(8),	/* OMAP2+ only */
	CICR_SUPERVISOR_ERR_IE	= BIT(10),	/* OMAP2+ only */
	CICR_MISALIGNED_ERR_IE	= BIT(11),	/* OMAP2+ only */
	CICR_DRAIN_IE		= BIT(12),	/* OMAP2+ only */
	CICR_SUPER_BLOCK_IE	= BIT(14),	/* OMAP2+ only */

	CLNK_CTRL_ENABLE_LNK	= BIT(15),

	CDP_DST_VALID_INC	= 0 << 0,
	CDP_DST_VALID_RELOAD	= 1 << 0,
	CDP_DST_VALID_REUSE	= 2 << 0,
	CDP_SRC_VALID_INC	= 0 << 2,
	CDP_SRC_VALID_RELOAD	= 1 << 2,
	CDP_SRC_VALID_REUSE	= 2 << 2,
	CDP_NTYPE_TYPE1		= 1 << 4,
	CDP_NTYPE_TYPE2		= 2 << 4,
	CDP_NTYPE_TYPE3		= 3 << 4,
	CDP_TMODE_NORMAL	= 0 << 8,
	CDP_TMODE_LLIST		= 1 << 8,
	CDP_FAST		= BIT(10),
पूर्ण;

अटल स्थिर अचिन्हित es_bytes[] = अणु
	[CSDP_DATA_TYPE_8] = 1,
	[CSDP_DATA_TYPE_16] = 2,
	[CSDP_DATA_TYPE_32] = 4,
पूर्ण;

अटल bool omap_dma_filter_fn(काष्ठा dma_chan *chan, व्योम *param);
अटल काष्ठा of_dma_filter_info omap_dma_info = अणु
	.filter_fn = omap_dma_filter_fn,
पूर्ण;

अटल अंतरभूत काष्ठा omap_dmadev *to_omap_dma_dev(काष्ठा dma_device *d)
अणु
	वापस container_of(d, काष्ठा omap_dmadev, ddev);
पूर्ण

अटल अंतरभूत काष्ठा omap_chan *to_omap_dma_chan(काष्ठा dma_chan *c)
अणु
	वापस container_of(c, काष्ठा omap_chan, vc.chan);
पूर्ण

अटल अंतरभूत काष्ठा omap_desc *to_omap_dma_desc(काष्ठा dma_async_tx_descriptor *t)
अणु
	वापस container_of(t, काष्ठा omap_desc, vd.tx);
पूर्ण

अटल व्योम omap_dma_desc_मुक्त(काष्ठा virt_dma_desc *vd)
अणु
	काष्ठा omap_desc *d = to_omap_dma_desc(&vd->tx);

	अगर (d->using_ll) अणु
		काष्ठा omap_dmadev *od = to_omap_dma_dev(vd->tx.chan->device);
		पूर्णांक i;

		क्रम (i = 0; i < d->sglen; i++) अणु
			अगर (d->sg[i].t2_desc)
				dma_pool_मुक्त(od->desc_pool, d->sg[i].t2_desc,
					      d->sg[i].t2_desc_paddr);
		पूर्ण
	पूर्ण

	kमुक्त(d);
पूर्ण

अटल व्योम omap_dma_fill_type2_desc(काष्ठा omap_desc *d, पूर्णांक idx,
				     क्रमागत dma_transfer_direction dir, bool last)
अणु
	काष्ठा omap_sg *sg = &d->sg[idx];
	काष्ठा omap_type2_desc *t2_desc = sg->t2_desc;

	अगर (idx)
		d->sg[idx - 1].t2_desc->next_desc = sg->t2_desc_paddr;
	अगर (last)
		t2_desc->next_desc = 0xfffffffc;

	t2_desc->en = sg->en;
	t2_desc->addr = sg->addr;
	t2_desc->fn = sg->fn & 0xffff;
	t2_desc->cicr = d->cicr;
	अगर (!last)
		t2_desc->cicr &= ~CICR_BLOCK_IE;

	चयन (dir) अणु
	हाल DMA_DEV_TO_MEM:
		t2_desc->cdei = sg->ei;
		t2_desc->csei = d->ei;
		t2_desc->cdfi = sg->fi;
		t2_desc->csfi = d->fi;

		t2_desc->en |= DESC_NXT_DV_REFRESH;
		t2_desc->en |= DESC_NXT_SV_REUSE;
		अवरोध;
	हाल DMA_MEM_TO_DEV:
		t2_desc->cdei = d->ei;
		t2_desc->csei = sg->ei;
		t2_desc->cdfi = d->fi;
		t2_desc->csfi = sg->fi;

		t2_desc->en |= DESC_NXT_SV_REFRESH;
		t2_desc->en |= DESC_NXT_DV_REUSE;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	t2_desc->en |= DESC_NTYPE_TYPE2;
पूर्ण

अटल व्योम omap_dma_ग_लिखो(uपूर्णांक32_t val, अचिन्हित type, व्योम __iomem *addr)
अणु
	चयन (type) अणु
	हाल OMAP_DMA_REG_16BIT:
		ग_लिखोw_relaxed(val, addr);
		अवरोध;
	हाल OMAP_DMA_REG_2X16BIT:
		ग_लिखोw_relaxed(val, addr);
		ग_लिखोw_relaxed(val >> 16, addr + 2);
		अवरोध;
	हाल OMAP_DMA_REG_32BIT:
		ग_लिखोl_relaxed(val, addr);
		अवरोध;
	शेष:
		WARN_ON(1);
	पूर्ण
पूर्ण

अटल अचिन्हित omap_dma_पढ़ो(अचिन्हित type, व्योम __iomem *addr)
अणु
	अचिन्हित val;

	चयन (type) अणु
	हाल OMAP_DMA_REG_16BIT:
		val = पढ़ोw_relaxed(addr);
		अवरोध;
	हाल OMAP_DMA_REG_2X16BIT:
		val = पढ़ोw_relaxed(addr);
		val |= पढ़ोw_relaxed(addr + 2) << 16;
		अवरोध;
	हाल OMAP_DMA_REG_32BIT:
		val = पढ़ोl_relaxed(addr);
		अवरोध;
	शेष:
		WARN_ON(1);
		val = 0;
	पूर्ण

	वापस val;
पूर्ण

अटल व्योम omap_dma_glbl_ग_लिखो(काष्ठा omap_dmadev *od, अचिन्हित reg, अचिन्हित val)
अणु
	स्थिर काष्ठा omap_dma_reg *r = od->reg_map + reg;

	WARN_ON(r->stride);

	omap_dma_ग_लिखो(val, r->type, od->base + r->offset);
पूर्ण

अटल अचिन्हित omap_dma_glbl_पढ़ो(काष्ठा omap_dmadev *od, अचिन्हित reg)
अणु
	स्थिर काष्ठा omap_dma_reg *r = od->reg_map + reg;

	WARN_ON(r->stride);

	वापस omap_dma_पढ़ो(r->type, od->base + r->offset);
पूर्ण

अटल व्योम omap_dma_chan_ग_लिखो(काष्ठा omap_chan *c, अचिन्हित reg, अचिन्हित val)
अणु
	स्थिर काष्ठा omap_dma_reg *r = c->reg_map + reg;

	omap_dma_ग_लिखो(val, r->type, c->channel_base + r->offset);
पूर्ण

अटल अचिन्हित omap_dma_chan_पढ़ो(काष्ठा omap_chan *c, अचिन्हित reg)
अणु
	स्थिर काष्ठा omap_dma_reg *r = c->reg_map + reg;

	वापस omap_dma_पढ़ो(r->type, c->channel_base + r->offset);
पूर्ण

अटल व्योम omap_dma_clear_csr(काष्ठा omap_chan *c)
अणु
	अगर (dma_omap1())
		omap_dma_chan_पढ़ो(c, CSR);
	अन्यथा
		omap_dma_chan_ग_लिखो(c, CSR, ~0);
पूर्ण

अटल अचिन्हित omap_dma_get_csr(काष्ठा omap_chan *c)
अणु
	अचिन्हित val = omap_dma_chan_पढ़ो(c, CSR);

	अगर (!dma_omap1())
		omap_dma_chan_ग_लिखो(c, CSR, val);

	वापस val;
पूर्ण

अटल व्योम omap_dma_clear_lch(काष्ठा omap_dmadev *od, पूर्णांक lch)
अणु
	काष्ठा omap_chan *c;
	पूर्णांक i;

	c = od->lch_map[lch];
	अगर (!c)
		वापस;

	क्रम (i = CSDP; i <= od->cfg->lch_end; i++)
		omap_dma_chan_ग_लिखो(c, i, 0);
पूर्ण

अटल व्योम omap_dma_assign(काष्ठा omap_dmadev *od, काष्ठा omap_chan *c,
	अचिन्हित lch)
अणु
	c->channel_base = od->base + od->plat->channel_stride * lch;

	od->lch_map[lch] = c;
पूर्ण

अटल व्योम omap_dma_start(काष्ठा omap_chan *c, काष्ठा omap_desc *d)
अणु
	काष्ठा omap_dmadev *od = to_omap_dma_dev(c->vc.chan.device);
	uपूर्णांक16_t cicr = d->cicr;

	अगर (__dma_omap15xx(od->plat->dma_attr))
		omap_dma_chan_ग_लिखो(c, CPC, 0);
	अन्यथा
		omap_dma_chan_ग_लिखो(c, CDAC, 0);

	omap_dma_clear_csr(c);

	अगर (d->using_ll) अणु
		uपूर्णांक32_t cdp = CDP_TMODE_LLIST | CDP_NTYPE_TYPE2 | CDP_FAST;

		अगर (d->dir == DMA_DEV_TO_MEM)
			cdp |= (CDP_DST_VALID_RELOAD | CDP_SRC_VALID_REUSE);
		अन्यथा
			cdp |= (CDP_DST_VALID_REUSE | CDP_SRC_VALID_RELOAD);
		omap_dma_chan_ग_लिखो(c, CDP, cdp);

		omap_dma_chan_ग_लिखो(c, CNDP, d->sg[0].t2_desc_paddr);
		omap_dma_chan_ग_लिखो(c, CCDN, 0);
		omap_dma_chan_ग_लिखो(c, CCFN, 0xffff);
		omap_dma_chan_ग_लिखो(c, CCEN, 0xffffff);

		cicr &= ~CICR_BLOCK_IE;
	पूर्ण अन्यथा अगर (od->ll123_supported) अणु
		omap_dma_chan_ग_लिखो(c, CDP, 0);
	पूर्ण

	/* Enable पूर्णांकerrupts */
	omap_dma_chan_ग_लिखो(c, CICR, cicr);

	/* Enable channel */
	omap_dma_chan_ग_लिखो(c, CCR, d->ccr | CCR_ENABLE);

	c->running = true;
पूर्ण

अटल व्योम omap_dma_drain_chan(काष्ठा omap_chan *c)
अणु
	पूर्णांक i;
	u32 val;

	/* Wait क्रम sDMA FIFO to drain */
	क्रम (i = 0; ; i++) अणु
		val = omap_dma_chan_पढ़ो(c, CCR);
		अगर (!(val & (CCR_RD_ACTIVE | CCR_WR_ACTIVE)))
			अवरोध;

		अगर (i > 100)
			अवरोध;

		udelay(5);
	पूर्ण

	अगर (val & (CCR_RD_ACTIVE | CCR_WR_ACTIVE))
		dev_err(c->vc.chan.device->dev,
			"DMA drain did not complete on lch %d\n",
			c->dma_ch);
पूर्ण

अटल पूर्णांक omap_dma_stop(काष्ठा omap_chan *c)
अणु
	काष्ठा omap_dmadev *od = to_omap_dma_dev(c->vc.chan.device);
	uपूर्णांक32_t val;

	/* disable irq */
	omap_dma_chan_ग_लिखो(c, CICR, 0);

	omap_dma_clear_csr(c);

	val = omap_dma_chan_पढ़ो(c, CCR);
	अगर (od->plat->errata & DMA_ERRATA_i541 && val & CCR_TRIGGER_SRC) अणु
		uपूर्णांक32_t sysconfig;

		sysconfig = omap_dma_glbl_पढ़ो(od, OCP_SYSCONFIG);
		val = sysconfig & ~DMA_SYSCONFIG_MIDLEMODE_MASK;
		val |= DMA_SYSCONFIG_MIDLEMODE(DMA_IDLEMODE_NO_IDLE);
		omap_dma_glbl_ग_लिखो(od, OCP_SYSCONFIG, val);

		val = omap_dma_chan_पढ़ो(c, CCR);
		val &= ~CCR_ENABLE;
		omap_dma_chan_ग_लिखो(c, CCR, val);

		अगर (!(c->ccr & CCR_BUFFERING_DISABLE))
			omap_dma_drain_chan(c);

		omap_dma_glbl_ग_लिखो(od, OCP_SYSCONFIG, sysconfig);
	पूर्ण अन्यथा अणु
		अगर (!(val & CCR_ENABLE))
			वापस -EINVAL;

		val &= ~CCR_ENABLE;
		omap_dma_chan_ग_लिखो(c, CCR, val);

		अगर (!(c->ccr & CCR_BUFFERING_DISABLE))
			omap_dma_drain_chan(c);
	पूर्ण

	mb();

	अगर (!__dma_omap15xx(od->plat->dma_attr) && c->cyclic) अणु
		val = omap_dma_chan_पढ़ो(c, CLNK_CTRL);

		अगर (dma_omap1())
			val |= 1 << 14; /* set the STOP_LNK bit */
		अन्यथा
			val &= ~CLNK_CTRL_ENABLE_LNK;

		omap_dma_chan_ग_लिखो(c, CLNK_CTRL, val);
	पूर्ण
	c->running = false;
	वापस 0;
पूर्ण

अटल व्योम omap_dma_start_sg(काष्ठा omap_chan *c, काष्ठा omap_desc *d)
अणु
	काष्ठा omap_sg *sg = d->sg + c->sgidx;
	अचिन्हित cxsa, cxei, cxfi;

	अगर (d->dir == DMA_DEV_TO_MEM || d->dir == DMA_MEM_TO_MEM) अणु
		cxsa = CDSA;
		cxei = CDEI;
		cxfi = CDFI;
	पूर्ण अन्यथा अणु
		cxsa = CSSA;
		cxei = CSEI;
		cxfi = CSFI;
	पूर्ण

	omap_dma_chan_ग_लिखो(c, cxsa, sg->addr);
	omap_dma_chan_ग_लिखो(c, cxei, sg->ei);
	omap_dma_chan_ग_लिखो(c, cxfi, sg->fi);
	omap_dma_chan_ग_लिखो(c, CEN, sg->en);
	omap_dma_chan_ग_लिखो(c, CFN, sg->fn);

	omap_dma_start(c, d);
	c->sgidx++;
पूर्ण

अटल व्योम omap_dma_start_desc(काष्ठा omap_chan *c)
अणु
	काष्ठा virt_dma_desc *vd = vchan_next_desc(&c->vc);
	काष्ठा omap_desc *d;
	अचिन्हित cxsa, cxei, cxfi;

	अगर (!vd) अणु
		c->desc = शून्य;
		वापस;
	पूर्ण

	list_del(&vd->node);

	c->desc = d = to_omap_dma_desc(&vd->tx);
	c->sgidx = 0;

	/*
	 * This provides the necessary barrier to ensure data held in
	 * DMA coherent memory is visible to the DMA engine prior to
	 * the transfer starting.
	 */
	mb();

	omap_dma_chan_ग_लिखो(c, CCR, d->ccr);
	अगर (dma_omap1())
		omap_dma_chan_ग_लिखो(c, CCR2, d->ccr >> 16);

	अगर (d->dir == DMA_DEV_TO_MEM || d->dir == DMA_MEM_TO_MEM) अणु
		cxsa = CSSA;
		cxei = CSEI;
		cxfi = CSFI;
	पूर्ण अन्यथा अणु
		cxsa = CDSA;
		cxei = CDEI;
		cxfi = CDFI;
	पूर्ण

	omap_dma_chan_ग_लिखो(c, cxsa, d->dev_addr);
	omap_dma_chan_ग_लिखो(c, cxei, d->ei);
	omap_dma_chan_ग_लिखो(c, cxfi, d->fi);
	omap_dma_chan_ग_लिखो(c, CSDP, d->csdp);
	omap_dma_chan_ग_लिखो(c, CLNK_CTRL, d->clnk_ctrl);

	omap_dma_start_sg(c, d);
पूर्ण

अटल व्योम omap_dma_callback(पूर्णांक ch, u16 status, व्योम *data)
अणु
	काष्ठा omap_chan *c = data;
	काष्ठा omap_desc *d;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&c->vc.lock, flags);
	d = c->desc;
	अगर (d) अणु
		अगर (c->cyclic) अणु
			vchan_cyclic_callback(&d->vd);
		पूर्ण अन्यथा अगर (d->using_ll || c->sgidx == d->sglen) अणु
			omap_dma_start_desc(c);
			vchan_cookie_complete(&d->vd);
		पूर्ण अन्यथा अणु
			omap_dma_start_sg(c, d);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&c->vc.lock, flags);
पूर्ण

अटल irqवापस_t omap_dma_irq(पूर्णांक irq, व्योम *devid)
अणु
	काष्ठा omap_dmadev *od = devid;
	अचिन्हित status, channel;

	spin_lock(&od->irq_lock);

	status = omap_dma_glbl_पढ़ो(od, IRQSTATUS_L1);
	status &= od->irq_enable_mask;
	अगर (status == 0) अणु
		spin_unlock(&od->irq_lock);
		वापस IRQ_NONE;
	पूर्ण

	जबतक ((channel = ffs(status)) != 0) अणु
		अचिन्हित mask, csr;
		काष्ठा omap_chan *c;

		channel -= 1;
		mask = BIT(channel);
		status &= ~mask;

		c = od->lch_map[channel];
		अगर (c == शून्य) अणु
			/* This should never happen */
			dev_err(od->ddev.dev, "invalid channel %u\n", channel);
			जारी;
		पूर्ण

		csr = omap_dma_get_csr(c);
		omap_dma_glbl_ग_लिखो(od, IRQSTATUS_L1, mask);

		omap_dma_callback(channel, csr, c);
	पूर्ण

	spin_unlock(&od->irq_lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक omap_dma_get_lch(काष्ठा omap_dmadev *od, पूर्णांक *lch)
अणु
	पूर्णांक channel;

	mutex_lock(&od->lch_lock);
	channel = find_first_zero_bit(od->lch_biपंचांगap, od->lch_count);
	अगर (channel >= od->lch_count)
		जाओ out_busy;
	set_bit(channel, od->lch_biपंचांगap);
	mutex_unlock(&od->lch_lock);

	omap_dma_clear_lch(od, channel);
	*lch = channel;

	वापस 0;

out_busy:
	mutex_unlock(&od->lch_lock);
	*lch = -EINVAL;

	वापस -EBUSY;
पूर्ण

अटल व्योम omap_dma_put_lch(काष्ठा omap_dmadev *od, पूर्णांक lch)
अणु
	omap_dma_clear_lch(od, lch);
	mutex_lock(&od->lch_lock);
	clear_bit(lch, od->lch_biपंचांगap);
	mutex_unlock(&od->lch_lock);
पूर्ण

अटल पूर्णांक omap_dma_alloc_chan_resources(काष्ठा dma_chan *chan)
अणु
	काष्ठा omap_dmadev *od = to_omap_dma_dev(chan->device);
	काष्ठा omap_chan *c = to_omap_dma_chan(chan);
	काष्ठा device *dev = od->ddev.dev;
	पूर्णांक ret;

	अगर (od->legacy) अणु
		ret = omap_request_dma(c->dma_sig, "DMA engine",
				       omap_dma_callback, c, &c->dma_ch);
	पूर्ण अन्यथा अणु
		ret = omap_dma_get_lch(od, &c->dma_ch);
	पूर्ण

	dev_dbg(dev, "allocating channel %u for %u\n", c->dma_ch, c->dma_sig);

	अगर (ret >= 0) अणु
		omap_dma_assign(od, c, c->dma_ch);

		अगर (!od->legacy) अणु
			अचिन्हित val;

			spin_lock_irq(&od->irq_lock);
			val = BIT(c->dma_ch);
			omap_dma_glbl_ग_लिखो(od, IRQSTATUS_L1, val);
			od->irq_enable_mask |= val;
			omap_dma_glbl_ग_लिखो(od, IRQENABLE_L1, od->irq_enable_mask);

			val = omap_dma_glbl_पढ़ो(od, IRQENABLE_L0);
			val &= ~BIT(c->dma_ch);
			omap_dma_glbl_ग_लिखो(od, IRQENABLE_L0, val);
			spin_unlock_irq(&od->irq_lock);
		पूर्ण
	पूर्ण

	अगर (dma_omap1()) अणु
		अगर (__dma_omap16xx(od->plat->dma_attr)) अणु
			c->ccr = CCR_OMAP31_DISABLE;
			/* Duplicate what plat-omap/dma.c करोes */
			c->ccr |= c->dma_ch + 1;
		पूर्ण अन्यथा अणु
			c->ccr = c->dma_sig & 0x1f;
		पूर्ण
	पूर्ण अन्यथा अणु
		c->ccr = c->dma_sig & 0x1f;
		c->ccr |= (c->dma_sig & ~0x1f) << 14;
	पूर्ण
	अगर (od->plat->errata & DMA_ERRATA_IFRAME_BUFFERING)
		c->ccr |= CCR_BUFFERING_DISABLE;

	वापस ret;
पूर्ण

अटल व्योम omap_dma_मुक्त_chan_resources(काष्ठा dma_chan *chan)
अणु
	काष्ठा omap_dmadev *od = to_omap_dma_dev(chan->device);
	काष्ठा omap_chan *c = to_omap_dma_chan(chan);

	अगर (!od->legacy) अणु
		spin_lock_irq(&od->irq_lock);
		od->irq_enable_mask &= ~BIT(c->dma_ch);
		omap_dma_glbl_ग_लिखो(od, IRQENABLE_L1, od->irq_enable_mask);
		spin_unlock_irq(&od->irq_lock);
	पूर्ण

	c->channel_base = शून्य;
	od->lch_map[c->dma_ch] = शून्य;
	vchan_मुक्त_chan_resources(&c->vc);

	अगर (od->legacy)
		omap_मुक्त_dma(c->dma_ch);
	अन्यथा
		omap_dma_put_lch(od, c->dma_ch);

	dev_dbg(od->ddev.dev, "freeing channel %u used for %u\n", c->dma_ch,
		c->dma_sig);
	c->dma_sig = 0;
पूर्ण

अटल माप_प्रकार omap_dma_sg_size(काष्ठा omap_sg *sg)
अणु
	वापस sg->en * sg->fn;
पूर्ण

अटल माप_प्रकार omap_dma_desc_size(काष्ठा omap_desc *d)
अणु
	अचिन्हित i;
	माप_प्रकार size;

	क्रम (size = i = 0; i < d->sglen; i++)
		size += omap_dma_sg_size(&d->sg[i]);

	वापस size * es_bytes[d->es];
पूर्ण

अटल माप_प्रकार omap_dma_desc_size_pos(काष्ठा omap_desc *d, dma_addr_t addr)
अणु
	अचिन्हित i;
	माप_प्रकार size, es_size = es_bytes[d->es];

	क्रम (size = i = 0; i < d->sglen; i++) अणु
		माप_प्रकार this_size = omap_dma_sg_size(&d->sg[i]) * es_size;

		अगर (size)
			size += this_size;
		अन्यथा अगर (addr >= d->sg[i].addr &&
			 addr < d->sg[i].addr + this_size)
			size += d->sg[i].addr + this_size - addr;
	पूर्ण
	वापस size;
पूर्ण

/*
 * OMAP 3.2/3.3 erratum: someबार 0 is वापसed अगर CSAC/CDAC is
 * पढ़ो beक्रमe the DMA controller finished disabling the channel.
 */
अटल uपूर्णांक32_t omap_dma_chan_पढ़ो_3_3(काष्ठा omap_chan *c, अचिन्हित reg)
अणु
	काष्ठा omap_dmadev *od = to_omap_dma_dev(c->vc.chan.device);
	uपूर्णांक32_t val;

	val = omap_dma_chan_पढ़ो(c, reg);
	अगर (val == 0 && od->plat->errata & DMA_ERRATA_3_3)
		val = omap_dma_chan_पढ़ो(c, reg);

	वापस val;
पूर्ण

अटल dma_addr_t omap_dma_get_src_pos(काष्ठा omap_chan *c)
अणु
	काष्ठा omap_dmadev *od = to_omap_dma_dev(c->vc.chan.device);
	dma_addr_t addr, cdac;

	अगर (__dma_omap15xx(od->plat->dma_attr)) अणु
		addr = omap_dma_chan_पढ़ो(c, CPC);
	पूर्ण अन्यथा अणु
		addr = omap_dma_chan_पढ़ो_3_3(c, CSAC);
		cdac = omap_dma_chan_पढ़ो_3_3(c, CDAC);

		/*
		 * CDAC == 0 indicates that the DMA transfer on the channel has
		 * not been started (no data has been transferred so far).
		 * Return the programmed source start address in this हाल.
		 */
		अगर (cdac == 0)
			addr = omap_dma_chan_पढ़ो(c, CSSA);
	पूर्ण

	अगर (dma_omap1())
		addr |= omap_dma_chan_पढ़ो(c, CSSA) & 0xffff0000;

	वापस addr;
पूर्ण

अटल dma_addr_t omap_dma_get_dst_pos(काष्ठा omap_chan *c)
अणु
	काष्ठा omap_dmadev *od = to_omap_dma_dev(c->vc.chan.device);
	dma_addr_t addr;

	अगर (__dma_omap15xx(od->plat->dma_attr)) अणु
		addr = omap_dma_chan_पढ़ो(c, CPC);
	पूर्ण अन्यथा अणु
		addr = omap_dma_chan_पढ़ो_3_3(c, CDAC);

		/*
		 * CDAC == 0 indicates that the DMA transfer on the channel
		 * has not been started (no data has been transferred so
		 * far).  Return the programmed destination start address in
		 * this हाल.
		 */
		अगर (addr == 0)
			addr = omap_dma_chan_पढ़ो(c, CDSA);
	पूर्ण

	अगर (dma_omap1())
		addr |= omap_dma_chan_पढ़ो(c, CDSA) & 0xffff0000;

	वापस addr;
पूर्ण

अटल क्रमागत dma_status omap_dma_tx_status(काष्ठा dma_chan *chan,
	dma_cookie_t cookie, काष्ठा dma_tx_state *txstate)
अणु
	काष्ठा omap_chan *c = to_omap_dma_chan(chan);
	क्रमागत dma_status ret;
	अचिन्हित दीर्घ flags;
	काष्ठा omap_desc *d = शून्य;

	ret = dma_cookie_status(chan, cookie, txstate);
	अगर (ret == DMA_COMPLETE)
		वापस ret;

	spin_lock_irqsave(&c->vc.lock, flags);
	अगर (c->desc && c->desc->vd.tx.cookie == cookie)
		d = c->desc;

	अगर (!txstate)
		जाओ out;

	अगर (d) अणु
		dma_addr_t pos;

		अगर (d->dir == DMA_MEM_TO_DEV)
			pos = omap_dma_get_src_pos(c);
		अन्यथा अगर (d->dir == DMA_DEV_TO_MEM  || d->dir == DMA_MEM_TO_MEM)
			pos = omap_dma_get_dst_pos(c);
		अन्यथा
			pos = 0;

		txstate->residue = omap_dma_desc_size_pos(d, pos);
	पूर्ण अन्यथा अणु
		काष्ठा virt_dma_desc *vd = vchan_find_desc(&c->vc, cookie);

		अगर (vd)
			txstate->residue = omap_dma_desc_size(
						to_omap_dma_desc(&vd->tx));
		अन्यथा
			txstate->residue = 0;
	पूर्ण

out:
	अगर (ret == DMA_IN_PROGRESS && c->छोड़ोd) अणु
		ret = DMA_PAUSED;
	पूर्ण अन्यथा अगर (d && d->polled && c->running) अणु
		uपूर्णांक32_t ccr = omap_dma_chan_पढ़ो(c, CCR);
		/*
		 * The channel is no दीर्घer active, set the वापस value
		 * accordingly and mark it as completed
		 */
		अगर (!(ccr & CCR_ENABLE)) अणु
			ret = DMA_COMPLETE;
			omap_dma_start_desc(c);
			vchan_cookie_complete(&d->vd);
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&c->vc.lock, flags);

	वापस ret;
पूर्ण

अटल व्योम omap_dma_issue_pending(काष्ठा dma_chan *chan)
अणु
	काष्ठा omap_chan *c = to_omap_dma_chan(chan);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&c->vc.lock, flags);
	अगर (vchan_issue_pending(&c->vc) && !c->desc)
		omap_dma_start_desc(c);
	spin_unlock_irqrestore(&c->vc.lock, flags);
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *omap_dma_prep_slave_sg(
	काष्ठा dma_chan *chan, काष्ठा scatterlist *sgl, अचिन्हित sglen,
	क्रमागत dma_transfer_direction dir, अचिन्हित दीर्घ tx_flags, व्योम *context)
अणु
	काष्ठा omap_dmadev *od = to_omap_dma_dev(chan->device);
	काष्ठा omap_chan *c = to_omap_dma_chan(chan);
	क्रमागत dma_slave_buswidth dev_width;
	काष्ठा scatterlist *sgent;
	काष्ठा omap_desc *d;
	dma_addr_t dev_addr;
	अचिन्हित i, es, en, frame_bytes;
	bool ll_failed = false;
	u32 burst;
	u32 port_winकरोw, port_winकरोw_bytes;

	अगर (dir == DMA_DEV_TO_MEM) अणु
		dev_addr = c->cfg.src_addr;
		dev_width = c->cfg.src_addr_width;
		burst = c->cfg.src_maxburst;
		port_winकरोw = c->cfg.src_port_winकरोw_size;
	पूर्ण अन्यथा अगर (dir == DMA_MEM_TO_DEV) अणु
		dev_addr = c->cfg.dst_addr;
		dev_width = c->cfg.dst_addr_width;
		burst = c->cfg.dst_maxburst;
		port_winकरोw = c->cfg.dst_port_winकरोw_size;
	पूर्ण अन्यथा अणु
		dev_err(chan->device->dev, "%s: bad direction?\n", __func__);
		वापस शून्य;
	पूर्ण

	/* Bus width translates to the element size (ES) */
	चयन (dev_width) अणु
	हाल DMA_SLAVE_BUSWIDTH_1_BYTE:
		es = CSDP_DATA_TYPE_8;
		अवरोध;
	हाल DMA_SLAVE_BUSWIDTH_2_BYTES:
		es = CSDP_DATA_TYPE_16;
		अवरोध;
	हाल DMA_SLAVE_BUSWIDTH_4_BYTES:
		es = CSDP_DATA_TYPE_32;
		अवरोध;
	शेष: /* not reached */
		वापस शून्य;
	पूर्ण

	/* Now allocate and setup the descriptor. */
	d = kzalloc(काष्ठा_size(d, sg, sglen), GFP_ATOMIC);
	अगर (!d)
		वापस शून्य;

	d->dir = dir;
	d->dev_addr = dev_addr;
	d->es = es;

	/* When the port_winकरोw is used, one frame must cover the winकरोw */
	अगर (port_winकरोw) अणु
		burst = port_winकरोw;
		port_winकरोw_bytes = port_winकरोw * es_bytes[es];

		d->ei = 1;
		/*
		 * One frame covers the port_winकरोw and by  configure
		 * the source frame index to be -1 * (port_winकरोw - 1)
		 * we inकाष्ठा the sDMA that after a frame is processed
		 * it should move back to the start of the winकरोw.
		 */
		d->fi = -(port_winकरोw_bytes - 1);
	पूर्ण

	d->ccr = c->ccr | CCR_SYNC_FRAME;
	अगर (dir == DMA_DEV_TO_MEM) अणु
		d->csdp = CSDP_DST_BURST_64 | CSDP_DST_PACKED;

		d->ccr |= CCR_DST_AMODE_POSTINC;
		अगर (port_winकरोw) अणु
			d->ccr |= CCR_SRC_AMODE_DBLIDX;

			अगर (port_winकरोw_bytes >= 64)
				d->csdp |= CSDP_SRC_BURST_64;
			अन्यथा अगर (port_winकरोw_bytes >= 32)
				d->csdp |= CSDP_SRC_BURST_32;
			अन्यथा अगर (port_winकरोw_bytes >= 16)
				d->csdp |= CSDP_SRC_BURST_16;

		पूर्ण अन्यथा अणु
			d->ccr |= CCR_SRC_AMODE_CONSTANT;
		पूर्ण
	पूर्ण अन्यथा अणु
		d->csdp = CSDP_SRC_BURST_64 | CSDP_SRC_PACKED;

		d->ccr |= CCR_SRC_AMODE_POSTINC;
		अगर (port_winकरोw) अणु
			d->ccr |= CCR_DST_AMODE_DBLIDX;

			अगर (port_winकरोw_bytes >= 64)
				d->csdp |= CSDP_DST_BURST_64;
			अन्यथा अगर (port_winकरोw_bytes >= 32)
				d->csdp |= CSDP_DST_BURST_32;
			अन्यथा अगर (port_winकरोw_bytes >= 16)
				d->csdp |= CSDP_DST_BURST_16;
		पूर्ण अन्यथा अणु
			d->ccr |= CCR_DST_AMODE_CONSTANT;
		पूर्ण
	पूर्ण

	d->cicr = CICR_DROP_IE | CICR_BLOCK_IE;
	d->csdp |= es;

	अगर (dma_omap1()) अणु
		d->cicr |= CICR_TOUT_IE;

		अगर (dir == DMA_DEV_TO_MEM)
			d->csdp |= CSDP_DST_PORT_EMIFF | CSDP_SRC_PORT_TIPB;
		अन्यथा
			d->csdp |= CSDP_DST_PORT_TIPB | CSDP_SRC_PORT_EMIFF;
	पूर्ण अन्यथा अणु
		अगर (dir == DMA_DEV_TO_MEM)
			d->ccr |= CCR_TRIGGER_SRC;

		d->cicr |= CICR_MISALIGNED_ERR_IE | CICR_TRANS_ERR_IE;

		अगर (port_winकरोw)
			d->csdp |= CSDP_WRITE_LAST_NON_POSTED;
	पूर्ण
	अगर (od->plat->errata & DMA_ERRATA_PARALLEL_CHANNELS)
		d->clnk_ctrl = c->dma_ch;

	/*
	 * Build our scatterlist entries: each contains the address,
	 * the number of elements (EN) in each frame, and the number of
	 * frames (FN).  Number of bytes क्रम this entry = ES * EN * FN.
	 *
	 * Burst size translates to number of elements with frame sync.
	 * Note: DMA engine defines burst to be the number of dev-width
	 * transfers.
	 */
	en = burst;
	frame_bytes = es_bytes[es] * en;

	अगर (sglen >= 2)
		d->using_ll = od->ll123_supported;

	क्रम_each_sg(sgl, sgent, sglen, i) अणु
		काष्ठा omap_sg *osg = &d->sg[i];

		osg->addr = sg_dma_address(sgent);
		osg->en = en;
		osg->fn = sg_dma_len(sgent) / frame_bytes;

		अगर (d->using_ll) अणु
			osg->t2_desc = dma_pool_alloc(od->desc_pool, GFP_ATOMIC,
						      &osg->t2_desc_paddr);
			अगर (!osg->t2_desc) अणु
				dev_err(chan->device->dev,
					"t2_desc[%d] allocation failed\n", i);
				ll_failed = true;
				d->using_ll = false;
				जारी;
			पूर्ण

			omap_dma_fill_type2_desc(d, i, dir, (i == sglen - 1));
		पूर्ण
	पूर्ण

	d->sglen = sglen;

	/* Release the dma_pool entries अगर one allocation failed */
	अगर (ll_failed) अणु
		क्रम (i = 0; i < d->sglen; i++) अणु
			काष्ठा omap_sg *osg = &d->sg[i];

			अगर (osg->t2_desc) अणु
				dma_pool_मुक्त(od->desc_pool, osg->t2_desc,
					      osg->t2_desc_paddr);
				osg->t2_desc = शून्य;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस vchan_tx_prep(&c->vc, &d->vd, tx_flags);
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *omap_dma_prep_dma_cyclic(
	काष्ठा dma_chan *chan, dma_addr_t buf_addr, माप_प्रकार buf_len,
	माप_प्रकार period_len, क्रमागत dma_transfer_direction dir, अचिन्हित दीर्घ flags)
अणु
	काष्ठा omap_dmadev *od = to_omap_dma_dev(chan->device);
	काष्ठा omap_chan *c = to_omap_dma_chan(chan);
	क्रमागत dma_slave_buswidth dev_width;
	काष्ठा omap_desc *d;
	dma_addr_t dev_addr;
	अचिन्हित es;
	u32 burst;

	अगर (dir == DMA_DEV_TO_MEM) अणु
		dev_addr = c->cfg.src_addr;
		dev_width = c->cfg.src_addr_width;
		burst = c->cfg.src_maxburst;
	पूर्ण अन्यथा अगर (dir == DMA_MEM_TO_DEV) अणु
		dev_addr = c->cfg.dst_addr;
		dev_width = c->cfg.dst_addr_width;
		burst = c->cfg.dst_maxburst;
	पूर्ण अन्यथा अणु
		dev_err(chan->device->dev, "%s: bad direction?\n", __func__);
		वापस शून्य;
	पूर्ण

	/* Bus width translates to the element size (ES) */
	चयन (dev_width) अणु
	हाल DMA_SLAVE_BUSWIDTH_1_BYTE:
		es = CSDP_DATA_TYPE_8;
		अवरोध;
	हाल DMA_SLAVE_BUSWIDTH_2_BYTES:
		es = CSDP_DATA_TYPE_16;
		अवरोध;
	हाल DMA_SLAVE_BUSWIDTH_4_BYTES:
		es = CSDP_DATA_TYPE_32;
		अवरोध;
	शेष: /* not reached */
		वापस शून्य;
	पूर्ण

	/* Now allocate and setup the descriptor. */
	d = kzalloc(माप(*d) + माप(d->sg[0]), GFP_ATOMIC);
	अगर (!d)
		वापस शून्य;

	d->dir = dir;
	d->dev_addr = dev_addr;
	d->fi = burst;
	d->es = es;
	d->sg[0].addr = buf_addr;
	d->sg[0].en = period_len / es_bytes[es];
	d->sg[0].fn = buf_len / period_len;
	d->sglen = 1;

	d->ccr = c->ccr;
	अगर (dir == DMA_DEV_TO_MEM)
		d->ccr |= CCR_DST_AMODE_POSTINC | CCR_SRC_AMODE_CONSTANT;
	अन्यथा
		d->ccr |= CCR_DST_AMODE_CONSTANT | CCR_SRC_AMODE_POSTINC;

	d->cicr = CICR_DROP_IE;
	अगर (flags & DMA_PREP_INTERRUPT)
		d->cicr |= CICR_FRAME_IE;

	d->csdp = es;

	अगर (dma_omap1()) अणु
		d->cicr |= CICR_TOUT_IE;

		अगर (dir == DMA_DEV_TO_MEM)
			d->csdp |= CSDP_DST_PORT_EMIFF | CSDP_SRC_PORT_MPUI;
		अन्यथा
			d->csdp |= CSDP_DST_PORT_MPUI | CSDP_SRC_PORT_EMIFF;
	पूर्ण अन्यथा अणु
		अगर (burst)
			d->ccr |= CCR_SYNC_PACKET;
		अन्यथा
			d->ccr |= CCR_SYNC_ELEMENT;

		अगर (dir == DMA_DEV_TO_MEM) अणु
			d->ccr |= CCR_TRIGGER_SRC;
			d->csdp |= CSDP_DST_PACKED;
		पूर्ण अन्यथा अणु
			d->csdp |= CSDP_SRC_PACKED;
		पूर्ण

		d->cicr |= CICR_MISALIGNED_ERR_IE | CICR_TRANS_ERR_IE;

		d->csdp |= CSDP_DST_BURST_64 | CSDP_SRC_BURST_64;
	पूर्ण

	अगर (__dma_omap15xx(od->plat->dma_attr))
		d->ccr |= CCR_AUTO_INIT | CCR_REPEAT;
	अन्यथा
		d->clnk_ctrl = c->dma_ch | CLNK_CTRL_ENABLE_LNK;

	c->cyclic = true;

	वापस vchan_tx_prep(&c->vc, &d->vd, flags);
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *omap_dma_prep_dma_स_नकल(
	काष्ठा dma_chan *chan, dma_addr_t dest, dma_addr_t src,
	माप_प्रकार len, अचिन्हित दीर्घ tx_flags)
अणु
	काष्ठा omap_chan *c = to_omap_dma_chan(chan);
	काष्ठा omap_desc *d;
	uपूर्णांक8_t data_type;

	d = kzalloc(माप(*d) + माप(d->sg[0]), GFP_ATOMIC);
	अगर (!d)
		वापस शून्य;

	data_type = __ffs((src | dest | len));
	अगर (data_type > CSDP_DATA_TYPE_32)
		data_type = CSDP_DATA_TYPE_32;

	d->dir = DMA_MEM_TO_MEM;
	d->dev_addr = src;
	d->fi = 0;
	d->es = data_type;
	d->sg[0].en = len / BIT(data_type);
	d->sg[0].fn = 1;
	d->sg[0].addr = dest;
	d->sglen = 1;
	d->ccr = c->ccr;
	d->ccr |= CCR_DST_AMODE_POSTINC | CCR_SRC_AMODE_POSTINC;

	अगर (tx_flags & DMA_PREP_INTERRUPT)
		d->cicr |= CICR_FRAME_IE;
	अन्यथा
		d->polled = true;

	d->csdp = data_type;

	अगर (dma_omap1()) अणु
		d->cicr |= CICR_TOUT_IE;
		d->csdp |= CSDP_DST_PORT_EMIFF | CSDP_SRC_PORT_EMIFF;
	पूर्ण अन्यथा अणु
		d->csdp |= CSDP_DST_PACKED | CSDP_SRC_PACKED;
		d->cicr |= CICR_MISALIGNED_ERR_IE | CICR_TRANS_ERR_IE;
		d->csdp |= CSDP_DST_BURST_64 | CSDP_SRC_BURST_64;
	पूर्ण

	वापस vchan_tx_prep(&c->vc, &d->vd, tx_flags);
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *omap_dma_prep_dma_पूर्णांकerleaved(
	काष्ठा dma_chan *chan, काष्ठा dma_पूर्णांकerleaved_ढाँचा *xt,
	अचिन्हित दीर्घ flags)
अणु
	काष्ठा omap_chan *c = to_omap_dma_chan(chan);
	काष्ठा omap_desc *d;
	काष्ठा omap_sg *sg;
	uपूर्णांक8_t data_type;
	माप_प्रकार src_icg, dst_icg;

	/* Slave mode is not supported */
	अगर (is_slave_direction(xt->dir))
		वापस शून्य;

	अगर (xt->frame_size != 1 || xt->numf == 0)
		वापस शून्य;

	d = kzalloc(माप(*d) + माप(d->sg[0]), GFP_ATOMIC);
	अगर (!d)
		वापस शून्य;

	data_type = __ffs((xt->src_start | xt->dst_start | xt->sgl[0].size));
	अगर (data_type > CSDP_DATA_TYPE_32)
		data_type = CSDP_DATA_TYPE_32;

	sg = &d->sg[0];
	d->dir = DMA_MEM_TO_MEM;
	d->dev_addr = xt->src_start;
	d->es = data_type;
	sg->en = xt->sgl[0].size / BIT(data_type);
	sg->fn = xt->numf;
	sg->addr = xt->dst_start;
	d->sglen = 1;
	d->ccr = c->ccr;

	src_icg = dmaengine_get_src_icg(xt, &xt->sgl[0]);
	dst_icg = dmaengine_get_dst_icg(xt, &xt->sgl[0]);
	अगर (src_icg) अणु
		d->ccr |= CCR_SRC_AMODE_DBLIDX;
		d->ei = 1;
		d->fi = src_icg + 1;
	पूर्ण अन्यथा अगर (xt->src_inc) अणु
		d->ccr |= CCR_SRC_AMODE_POSTINC;
		d->fi = 0;
	पूर्ण अन्यथा अणु
		dev_err(chan->device->dev,
			"%s: SRC constant addressing is not supported\n",
			__func__);
		kमुक्त(d);
		वापस शून्य;
	पूर्ण

	अगर (dst_icg) अणु
		d->ccr |= CCR_DST_AMODE_DBLIDX;
		sg->ei = 1;
		sg->fi = dst_icg + 1;
	पूर्ण अन्यथा अगर (xt->dst_inc) अणु
		d->ccr |= CCR_DST_AMODE_POSTINC;
		sg->fi = 0;
	पूर्ण अन्यथा अणु
		dev_err(chan->device->dev,
			"%s: DST constant addressing is not supported\n",
			__func__);
		kमुक्त(d);
		वापस शून्य;
	पूर्ण

	d->cicr = CICR_DROP_IE | CICR_FRAME_IE;

	d->csdp = data_type;

	अगर (dma_omap1()) अणु
		d->cicr |= CICR_TOUT_IE;
		d->csdp |= CSDP_DST_PORT_EMIFF | CSDP_SRC_PORT_EMIFF;
	पूर्ण अन्यथा अणु
		d->csdp |= CSDP_DST_PACKED | CSDP_SRC_PACKED;
		d->cicr |= CICR_MISALIGNED_ERR_IE | CICR_TRANS_ERR_IE;
		d->csdp |= CSDP_DST_BURST_64 | CSDP_SRC_BURST_64;
	पूर्ण

	वापस vchan_tx_prep(&c->vc, &d->vd, flags);
पूर्ण

अटल पूर्णांक omap_dma_slave_config(काष्ठा dma_chan *chan, काष्ठा dma_slave_config *cfg)
अणु
	काष्ठा omap_chan *c = to_omap_dma_chan(chan);

	अगर (cfg->src_addr_width == DMA_SLAVE_BUSWIDTH_8_BYTES ||
	    cfg->dst_addr_width == DMA_SLAVE_BUSWIDTH_8_BYTES)
		वापस -EINVAL;

	अगर (cfg->src_maxburst > chan->device->max_burst ||
	    cfg->dst_maxburst > chan->device->max_burst)
		वापस -EINVAL;

	स_नकल(&c->cfg, cfg, माप(c->cfg));

	वापस 0;
पूर्ण

अटल पूर्णांक omap_dma_terminate_all(काष्ठा dma_chan *chan)
अणु
	काष्ठा omap_chan *c = to_omap_dma_chan(chan);
	अचिन्हित दीर्घ flags;
	LIST_HEAD(head);

	spin_lock_irqsave(&c->vc.lock, flags);

	/*
	 * Stop DMA activity: we assume the callback will not be called
	 * after omap_dma_stop() वापसs (even अगर it करोes, it will see
	 * c->desc is शून्य and निकास.)
	 */
	अगर (c->desc) अणु
		vchan_terminate_vdesc(&c->desc->vd);
		c->desc = शून्य;
		/* Aव्योम stopping the dma twice */
		अगर (!c->छोड़ोd)
			omap_dma_stop(c);
	पूर्ण

	c->cyclic = false;
	c->छोड़ोd = false;

	vchan_get_all_descriptors(&c->vc, &head);
	spin_unlock_irqrestore(&c->vc.lock, flags);
	vchan_dma_desc_मुक्त_list(&c->vc, &head);

	वापस 0;
पूर्ण

अटल व्योम omap_dma_synchronize(काष्ठा dma_chan *chan)
अणु
	काष्ठा omap_chan *c = to_omap_dma_chan(chan);

	vchan_synchronize(&c->vc);
पूर्ण

अटल पूर्णांक omap_dma_छोड़ो(काष्ठा dma_chan *chan)
अणु
	काष्ठा omap_chan *c = to_omap_dma_chan(chan);
	काष्ठा omap_dmadev *od = to_omap_dma_dev(chan->device);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = -EINVAL;
	bool can_छोड़ो = false;

	spin_lock_irqsave(&od->irq_lock, flags);

	अगर (!c->desc)
		जाओ out;

	अगर (c->cyclic)
		can_छोड़ो = true;

	/*
	 * We करो not allow DMA_MEM_TO_DEV transfers to be छोड़ोd.
	 * From the AM572x TRM, 16.1.4.18 Disabling a Channel During Transfer:
	 * "When a channel is disabled during a transfer, the channel undergoes
	 * an पात, unless it is hardware-source-synchronized ै इ".
	 * A source-synchronised channel is one where the fetching of data is
	 * under control of the device. In other words, a device-to-memory
	 * transfer. So, a destination-synchronised channel (which would be a
	 * memory-to-device transfer) undergoes an पात अगर the the CCR_ENABLE
	 * bit is cleared.
	 * From 16.1.4.20.4.6.2 Abort: "If an पात trigger occurs, the channel
	 * पातs immediately after completion of current पढ़ो/ग_लिखो
	 * transactions and then the FIFO is cleaned up." The term "cleaned up"
	 * is not defined. TI recommends to check that RD_ACTIVE and WR_ACTIVE
	 * are both clear _beक्रमe_ disabling the channel, otherwise data loss
	 * will occur.
	 * The problem is that अगर the channel is active, then device activity
	 * can result in DMA activity starting between पढ़ोing those as both
	 * clear and the ग_लिखो to DMA_CCR to clear the enable bit hitting the
	 * hardware. If the DMA hardware can't drain the data in its FIFO to the
	 * destination, then data loss "might" occur (say अगर we ग_लिखो to an UART
	 * and the UART is not accepting any further data).
	 */
	अन्यथा अगर (c->desc->dir == DMA_DEV_TO_MEM)
		can_छोड़ो = true;

	अगर (can_छोड़ो && !c->छोड़ोd) अणु
		ret = omap_dma_stop(c);
		अगर (!ret)
			c->छोड़ोd = true;
	पूर्ण
out:
	spin_unlock_irqrestore(&od->irq_lock, flags);

	वापस ret;
पूर्ण

अटल पूर्णांक omap_dma_resume(काष्ठा dma_chan *chan)
अणु
	काष्ठा omap_chan *c = to_omap_dma_chan(chan);
	काष्ठा omap_dmadev *od = to_omap_dma_dev(chan->device);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = -EINVAL;

	spin_lock_irqsave(&od->irq_lock, flags);

	अगर (c->छोड़ोd && c->desc) अणु
		mb();

		/* Restore channel link रेजिस्टर */
		omap_dma_chan_ग_लिखो(c, CLNK_CTRL, c->desc->clnk_ctrl);

		omap_dma_start(c, c->desc);
		c->छोड़ोd = false;
		ret = 0;
	पूर्ण
	spin_unlock_irqrestore(&od->irq_lock, flags);

	वापस ret;
पूर्ण

अटल पूर्णांक omap_dma_chan_init(काष्ठा omap_dmadev *od)
अणु
	काष्ठा omap_chan *c;

	c = kzalloc(माप(*c), GFP_KERNEL);
	अगर (!c)
		वापस -ENOMEM;

	c->reg_map = od->reg_map;
	c->vc.desc_मुक्त = omap_dma_desc_मुक्त;
	vchan_init(&c->vc, &od->ddev);

	वापस 0;
पूर्ण

अटल व्योम omap_dma_मुक्त(काष्ठा omap_dmadev *od)
अणु
	जबतक (!list_empty(&od->ddev.channels)) अणु
		काष्ठा omap_chan *c = list_first_entry(&od->ddev.channels,
			काष्ठा omap_chan, vc.chan.device_node);

		list_del(&c->vc.chan.device_node);
		tasklet_समाप्त(&c->vc.task);
		kमुक्त(c);
	पूर्ण
पूर्ण

/* Currently used by omap2 & 3 to block deeper SoC idle states */
अटल bool omap_dma_busy(काष्ठा omap_dmadev *od)
अणु
	काष्ठा omap_chan *c;
	पूर्णांक lch = -1;

	जबतक (1) अणु
		lch = find_next_bit(od->lch_biपंचांगap, od->lch_count, lch + 1);
		अगर (lch >= od->lch_count)
			अवरोध;
		c = od->lch_map[lch];
		अगर (!c)
			जारी;
		अगर (omap_dma_chan_पढ़ो(c, CCR) & CCR_ENABLE)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

/* Currently only used क्रम omap2. For omap1, also a check क्रम lcd_dma is needed */
अटल पूर्णांक omap_dma_busy_notअगरier(काष्ठा notअगरier_block *nb,
				  अचिन्हित दीर्घ cmd, व्योम *v)
अणु
	काष्ठा omap_dmadev *od;

	od = container_of(nb, काष्ठा omap_dmadev, nb);

	चयन (cmd) अणु
	हाल CPU_CLUSTER_PM_ENTER:
		अगर (omap_dma_busy(od))
			वापस NOTIFY_BAD;
		अवरोध;
	हाल CPU_CLUSTER_PM_ENTER_FAILED:
	हाल CPU_CLUSTER_PM_EXIT:
		अवरोध;
	पूर्ण

	वापस NOTIFY_OK;
पूर्ण

/*
 * We are using IRQENABLE_L1, and legacy DMA code was using IRQENABLE_L0.
 * As the DSP may be using IRQENABLE_L2 and L3, let's not touch those क्रम
 * now. Context save seems to be only currently needed on omap3.
 */
अटल व्योम omap_dma_context_save(काष्ठा omap_dmadev *od)
अणु
	od->context.irqenable_l0 = omap_dma_glbl_पढ़ो(od, IRQENABLE_L0);
	od->context.irqenable_l1 = omap_dma_glbl_पढ़ो(od, IRQENABLE_L1);
	od->context.ocp_sysconfig = omap_dma_glbl_पढ़ो(od, OCP_SYSCONFIG);
	od->context.gcr = omap_dma_glbl_पढ़ो(od, GCR);
पूर्ण

अटल व्योम omap_dma_context_restore(काष्ठा omap_dmadev *od)
अणु
	पूर्णांक i;

	omap_dma_glbl_ग_लिखो(od, GCR, od->context.gcr);
	omap_dma_glbl_ग_लिखो(od, OCP_SYSCONFIG, od->context.ocp_sysconfig);
	omap_dma_glbl_ग_लिखो(od, IRQENABLE_L0, od->context.irqenable_l0);
	omap_dma_glbl_ग_लिखो(od, IRQENABLE_L1, od->context.irqenable_l1);

	/* Clear IRQSTATUS_L0 as legacy DMA code is no दीर्घer करोing it */
	अगर (od->plat->errata & DMA_ROMCODE_BUG)
		omap_dma_glbl_ग_लिखो(od, IRQSTATUS_L0, 0);

	/* Clear dma channels */
	क्रम (i = 0; i < od->lch_count; i++)
		omap_dma_clear_lch(od, i);
पूर्ण

/* Currently only used क्रम omap3 */
अटल पूर्णांक omap_dma_context_notअगरier(काष्ठा notअगरier_block *nb,
				     अचिन्हित दीर्घ cmd, व्योम *v)
अणु
	काष्ठा omap_dmadev *od;

	od = container_of(nb, काष्ठा omap_dmadev, nb);

	चयन (cmd) अणु
	हाल CPU_CLUSTER_PM_ENTER:
		अगर (omap_dma_busy(od))
			वापस NOTIFY_BAD;
		omap_dma_context_save(od);
		अवरोध;
	हाल CPU_CLUSTER_PM_ENTER_FAILED:
	हाल CPU_CLUSTER_PM_EXIT:
		omap_dma_context_restore(od);
		अवरोध;
	पूर्ण

	वापस NOTIFY_OK;
पूर्ण

अटल व्योम omap_dma_init_gcr(काष्ठा omap_dmadev *od, पूर्णांक arb_rate,
			      पूर्णांक max_fअगरo_depth, पूर्णांक tparams)
अणु
	u32 val;

	/* Set only क्रम omap2430 and later */
	अगर (!od->cfg->rw_priority)
		वापस;

	अगर (max_fअगरo_depth == 0)
		max_fअगरo_depth = 1;
	अगर (arb_rate == 0)
		arb_rate = 1;

	val = 0xff & max_fअगरo_depth;
	val |= (0x3 & tparams) << 12;
	val |= (arb_rate & 0xff) << 16;

	omap_dma_glbl_ग_लिखो(od, GCR, val);
पूर्ण

#घोषणा OMAP_DMA_BUSWIDTHS	(BIT(DMA_SLAVE_BUSWIDTH_1_BYTE) | \
				 BIT(DMA_SLAVE_BUSWIDTH_2_BYTES) | \
				 BIT(DMA_SLAVE_BUSWIDTH_4_BYTES))

/*
 * No flags currently set क्रम शेष configuration as omap1 is still
 * using platक्रमm data.
 */
अटल स्थिर काष्ठा omap_dma_config शेष_cfg;

अटल पूर्णांक omap_dma_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा omap_dma_config *conf;
	काष्ठा omap_dmadev *od;
	काष्ठा resource *res;
	पूर्णांक rc, i, irq;
	u32 val;

	od = devm_kzalloc(&pdev->dev, माप(*od), GFP_KERNEL);
	अगर (!od)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	od->base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(od->base))
		वापस PTR_ERR(od->base);

	conf = of_device_get_match_data(&pdev->dev);
	अगर (conf) अणु
		od->cfg = conf;
		od->plat = dev_get_platdata(&pdev->dev);
		अगर (!od->plat) अणु
			dev_err(&pdev->dev, "omap_system_dma_plat_info is missing");
			वापस -ENODEV;
		पूर्ण
	पूर्ण अन्यथा अणु
		od->cfg = &शेष_cfg;

		od->plat = omap_get_plat_info();
		अगर (!od->plat)
			वापस -EPROBE_DEFER;
	पूर्ण

	od->reg_map = od->plat->reg_map;

	dma_cap_set(DMA_SLAVE, od->ddev.cap_mask);
	dma_cap_set(DMA_CYCLIC, od->ddev.cap_mask);
	dma_cap_set(DMA_MEMCPY, od->ddev.cap_mask);
	dma_cap_set(DMA_INTERLEAVE, od->ddev.cap_mask);
	od->ddev.device_alloc_chan_resources = omap_dma_alloc_chan_resources;
	od->ddev.device_मुक्त_chan_resources = omap_dma_मुक्त_chan_resources;
	od->ddev.device_tx_status = omap_dma_tx_status;
	od->ddev.device_issue_pending = omap_dma_issue_pending;
	od->ddev.device_prep_slave_sg = omap_dma_prep_slave_sg;
	od->ddev.device_prep_dma_cyclic = omap_dma_prep_dma_cyclic;
	od->ddev.device_prep_dma_स_नकल = omap_dma_prep_dma_स_नकल;
	od->ddev.device_prep_पूर्णांकerleaved_dma = omap_dma_prep_dma_पूर्णांकerleaved;
	od->ddev.device_config = omap_dma_slave_config;
	od->ddev.device_छोड़ो = omap_dma_छोड़ो;
	od->ddev.device_resume = omap_dma_resume;
	od->ddev.device_terminate_all = omap_dma_terminate_all;
	od->ddev.device_synchronize = omap_dma_synchronize;
	od->ddev.src_addr_widths = OMAP_DMA_BUSWIDTHS;
	od->ddev.dst_addr_widths = OMAP_DMA_BUSWIDTHS;
	od->ddev.directions = BIT(DMA_DEV_TO_MEM) | BIT(DMA_MEM_TO_DEV);
	अगर (__dma_omap15xx(od->plat->dma_attr))
		od->ddev.residue_granularity =
				DMA_RESIDUE_GRANULARITY_DESCRIPTOR;
	अन्यथा
		od->ddev.residue_granularity = DMA_RESIDUE_GRANULARITY_BURST;
	od->ddev.max_burst = SZ_16M - 1; /* CCEN: 24bit अचिन्हित */
	od->ddev.dev = &pdev->dev;
	INIT_LIST_HEAD(&od->ddev.channels);
	mutex_init(&od->lch_lock);
	spin_lock_init(&od->lock);
	spin_lock_init(&od->irq_lock);

	/* Number of DMA requests */
	od->dma_requests = OMAP_SDMA_REQUESTS;
	अगर (pdev->dev.of_node && of_property_पढ़ो_u32(pdev->dev.of_node,
						      "dma-requests",
						      &od->dma_requests)) अणु
		dev_info(&pdev->dev,
			 "Missing dma-requests property, using %u.\n",
			 OMAP_SDMA_REQUESTS);
	पूर्ण

	/* Number of available logical channels */
	अगर (!pdev->dev.of_node) अणु
		od->lch_count = od->plat->dma_attr->lch_count;
		अगर (unlikely(!od->lch_count))
			od->lch_count = OMAP_SDMA_CHANNELS;
	पूर्ण अन्यथा अगर (of_property_पढ़ो_u32(pdev->dev.of_node, "dma-channels",
					&od->lch_count)) अणु
		dev_info(&pdev->dev,
			 "Missing dma-channels property, using %u.\n",
			 OMAP_SDMA_CHANNELS);
		od->lch_count = OMAP_SDMA_CHANNELS;
	पूर्ण

	/* Mask of allowed logical channels */
	अगर (pdev->dev.of_node && !of_property_पढ़ो_u32(pdev->dev.of_node,
						       "dma-channel-mask",
						       &val)) अणु
		/* Tag channels not in mask as reserved */
		val = ~val;
		biपंचांगap_from_arr32(od->lch_biपंचांगap, &val, od->lch_count);
	पूर्ण
	अगर (od->plat->dma_attr->dev_caps & HS_CHANNELS_RESERVED)
		biपंचांगap_set(od->lch_biपंचांगap, 0, 2);

	od->lch_map = devm_kसुस्मृति(&pdev->dev, od->lch_count,
				   माप(*od->lch_map),
				   GFP_KERNEL);
	अगर (!od->lch_map)
		वापस -ENOMEM;

	क्रम (i = 0; i < od->dma_requests; i++) अणु
		rc = omap_dma_chan_init(od);
		अगर (rc) अणु
			omap_dma_मुक्त(od);
			वापस rc;
		पूर्ण
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 1);
	अगर (irq <= 0) अणु
		dev_info(&pdev->dev, "failed to get L1 IRQ: %d\n", irq);
		od->legacy = true;
	पूर्ण अन्यथा अणु
		/* Disable all पूर्णांकerrupts */
		od->irq_enable_mask = 0;
		omap_dma_glbl_ग_लिखो(od, IRQENABLE_L1, 0);

		rc = devm_request_irq(&pdev->dev, irq, omap_dma_irq,
				      IRQF_SHARED, "omap-dma-engine", od);
		अगर (rc) अणु
			omap_dma_मुक्त(od);
			वापस rc;
		पूर्ण
	पूर्ण

	अगर (omap_dma_glbl_पढ़ो(od, CAPS_0) & CAPS_0_SUPPORT_LL123)
		od->ll123_supported = true;

	od->ddev.filter.map = od->plat->slave_map;
	od->ddev.filter.mapcnt = od->plat->slavecnt;
	od->ddev.filter.fn = omap_dma_filter_fn;

	अगर (od->ll123_supported) अणु
		od->desc_pool = dma_pool_create(dev_name(&pdev->dev),
						&pdev->dev,
						माप(काष्ठा omap_type2_desc),
						4, 0);
		अगर (!od->desc_pool) अणु
			dev_err(&pdev->dev,
				"unable to allocate descriptor pool\n");
			od->ll123_supported = false;
		पूर्ण
	पूर्ण

	rc = dma_async_device_रेजिस्टर(&od->ddev);
	अगर (rc) अणु
		pr_warn("OMAP-DMA: failed to register slave DMA engine device: %d\n",
			rc);
		omap_dma_मुक्त(od);
		वापस rc;
	पूर्ण

	platक्रमm_set_drvdata(pdev, od);

	अगर (pdev->dev.of_node) अणु
		omap_dma_info.dma_cap = od->ddev.cap_mask;

		/* Device-tree DMA controller registration */
		rc = of_dma_controller_रेजिस्टर(pdev->dev.of_node,
				of_dma_simple_xlate, &omap_dma_info);
		अगर (rc) अणु
			pr_warn("OMAP-DMA: failed to register DMA controller\n");
			dma_async_device_unरेजिस्टर(&od->ddev);
			omap_dma_मुक्त(od);
		पूर्ण
	पूर्ण

	omap_dma_init_gcr(od, DMA_DEFAULT_ARB_RATE, DMA_DEFAULT_FIFO_DEPTH, 0);

	अगर (od->cfg->needs_busy_check) अणु
		od->nb.notअगरier_call = omap_dma_busy_notअगरier;
		cpu_pm_रेजिस्टर_notअगरier(&od->nb);
	पूर्ण अन्यथा अगर (od->cfg->may_lose_context) अणु
		od->nb.notअगरier_call = omap_dma_context_notअगरier;
		cpu_pm_रेजिस्टर_notअगरier(&od->nb);
	पूर्ण

	dev_info(&pdev->dev, "OMAP DMA engine driver%s\n",
		 od->ll123_supported ? " (LinkedList1/2/3 supported)" : "");

	वापस rc;
पूर्ण

अटल पूर्णांक omap_dma_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा omap_dmadev *od = platक्रमm_get_drvdata(pdev);
	पूर्णांक irq;

	अगर (od->cfg->may_lose_context)
		cpu_pm_unरेजिस्टर_notअगरier(&od->nb);

	अगर (pdev->dev.of_node)
		of_dma_controller_मुक्त(pdev->dev.of_node);

	irq = platक्रमm_get_irq(pdev, 1);
	devm_मुक्त_irq(&pdev->dev, irq, od);

	dma_async_device_unरेजिस्टर(&od->ddev);

	अगर (!od->legacy) अणु
		/* Disable all पूर्णांकerrupts */
		omap_dma_glbl_ग_लिखो(od, IRQENABLE_L0, 0);
	पूर्ण

	अगर (od->ll123_supported)
		dma_pool_destroy(od->desc_pool);

	omap_dma_मुक्त(od);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा omap_dma_config omap2420_data = अणु
	.lch_end = CCFN,
	.rw_priority = true,
	.needs_lch_clear = true,
	.needs_busy_check = true,
पूर्ण;

अटल स्थिर काष्ठा omap_dma_config omap2430_data = अणु
	.lch_end = CCFN,
	.rw_priority = true,
	.needs_lch_clear = true,
पूर्ण;

अटल स्थिर काष्ठा omap_dma_config omap3430_data = अणु
	.lch_end = CCFN,
	.rw_priority = true,
	.needs_lch_clear = true,
	.may_lose_context = true,
पूर्ण;

अटल स्थिर काष्ठा omap_dma_config omap3630_data = अणु
	.lch_end = CCDN,
	.rw_priority = true,
	.needs_lch_clear = true,
	.may_lose_context = true,
पूर्ण;

अटल स्थिर काष्ठा omap_dma_config omap4_data = अणु
	.lch_end = CCDN,
	.rw_priority = true,
	.needs_lch_clear = true,
पूर्ण;

अटल स्थिर काष्ठा of_device_id omap_dma_match[] = अणु
	अणु .compatible = "ti,omap2420-sdma", .data = &omap2420_data, पूर्ण,
	अणु .compatible = "ti,omap2430-sdma", .data = &omap2430_data, पूर्ण,
	अणु .compatible = "ti,omap3430-sdma", .data = &omap3430_data, पूर्ण,
	अणु .compatible = "ti,omap3630-sdma", .data = &omap3630_data, पूर्ण,
	अणु .compatible = "ti,omap4430-sdma", .data = &omap4_data, पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, omap_dma_match);

अटल काष्ठा platक्रमm_driver omap_dma_driver = अणु
	.probe	= omap_dma_probe,
	.हटाओ	= omap_dma_हटाओ,
	.driver = अणु
		.name = "omap-dma-engine",
		.of_match_table = omap_dma_match,
	पूर्ण,
पूर्ण;

अटल bool omap_dma_filter_fn(काष्ठा dma_chan *chan, व्योम *param)
अणु
	अगर (chan->device->dev->driver == &omap_dma_driver.driver) अणु
		काष्ठा omap_dmadev *od = to_omap_dma_dev(chan->device);
		काष्ठा omap_chan *c = to_omap_dma_chan(chan);
		अचिन्हित req = *(अचिन्हित *)param;

		अगर (req <= od->dma_requests) अणु
			c->dma_sig = req;
			वापस true;
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण

अटल पूर्णांक omap_dma_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&omap_dma_driver);
पूर्ण
subsys_initcall(omap_dma_init);

अटल व्योम __निकास omap_dma_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&omap_dma_driver);
पूर्ण
module_निकास(omap_dma_निकास);

MODULE_AUTHOR("Russell King");
MODULE_LICENSE("GPL");
