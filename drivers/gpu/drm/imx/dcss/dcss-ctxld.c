<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright 2019 NXP.
 */

#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#समावेश "dcss-dev.h"

#घोषणा DCSS_CTXLD_CONTROL_STATUS	0x0
#घोषणा   CTXLD_ENABLE			BIT(0)
#घोषणा   ARB_SEL			BIT(1)
#घोषणा   RD_ERR_EN			BIT(2)
#घोषणा   DB_COMP_EN			BIT(3)
#घोषणा   SB_HP_COMP_EN			BIT(4)
#घोषणा   SB_LP_COMP_EN			BIT(5)
#घोषणा   DB_PEND_SB_REC_EN		BIT(6)
#घोषणा   SB_PEND_DISP_ACTIVE_EN	BIT(7)
#घोषणा   AHB_ERR_EN			BIT(8)
#घोषणा   RD_ERR			BIT(16)
#घोषणा   DB_COMP			BIT(17)
#घोषणा   SB_HP_COMP			BIT(18)
#घोषणा   SB_LP_COMP			BIT(19)
#घोषणा   DB_PEND_SB_REC		BIT(20)
#घोषणा   SB_PEND_DISP_ACTIVE		BIT(21)
#घोषणा   AHB_ERR			BIT(22)
#घोषणा DCSS_CTXLD_DB_BASE_ADDR		0x10
#घोषणा DCSS_CTXLD_DB_COUNT		0x14
#घोषणा DCSS_CTXLD_SB_BASE_ADDR		0x18
#घोषणा DCSS_CTXLD_SB_COUNT		0x1C
#घोषणा   SB_HP_COUNT_POS		0
#घोषणा   SB_HP_COUNT_MASK		0xffff
#घोषणा   SB_LP_COUNT_POS		16
#घोषणा   SB_LP_COUNT_MASK		0xffff0000
#घोषणा DCSS_AHB_ERR_ADDR		0x20

#घोषणा CTXLD_IRQ_COMPLETION		(DB_COMP | SB_HP_COMP | SB_LP_COMP)
#घोषणा CTXLD_IRQ_ERROR			(RD_ERR | DB_PEND_SB_REC | AHB_ERR)

/* The following sizes are in context loader entries, 8 bytes each. */
#घोषणा CTXLD_DB_CTX_ENTRIES		1024	/* max 65536 */
#घोषणा CTXLD_SB_LP_CTX_ENTRIES		10240	/* max 65536 */
#घोषणा CTXLD_SB_HP_CTX_ENTRIES		20000	/* max 65536 */
#घोषणा CTXLD_SB_CTX_ENTRIES		(CTXLD_SB_LP_CTX_ENTRIES + \
					 CTXLD_SB_HP_CTX_ENTRIES)

/* Sizes, in entries, of the DB, SB_HP and SB_LP context regions. */
अटल u16 dcss_ctxld_ctx_size[3] = अणु
	CTXLD_DB_CTX_ENTRIES,
	CTXLD_SB_HP_CTX_ENTRIES,
	CTXLD_SB_LP_CTX_ENTRIES
पूर्ण;

/* this represents an entry in the context loader map */
काष्ठा dcss_ctxld_item अणु
	u32 val;
	u32 ofs;
पूर्ण;

#घोषणा CTX_ITEM_SIZE			माप(काष्ठा dcss_ctxld_item)

काष्ठा dcss_ctxld अणु
	काष्ठा device *dev;
	व्योम __iomem *ctxld_reg;
	पूर्णांक irq;
	bool irq_en;

	काष्ठा dcss_ctxld_item *db[2];
	काष्ठा dcss_ctxld_item *sb_hp[2];
	काष्ठा dcss_ctxld_item *sb_lp[2];

	dma_addr_t db_paddr[2];
	dma_addr_t sb_paddr[2];

	u16 ctx_size[2][3]; /* holds the sizes of DB, SB_HP and SB_LP ctx */
	u8 current_ctx;

	bool in_use;
	bool armed;

	spinlock_t lock; /* protects concurent access to निजी data */
पूर्ण;

अटल irqवापस_t dcss_ctxld_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा dcss_ctxld *ctxld = data;
	काष्ठा dcss_dev *dcss = dcss_drv_dev_to_dcss(ctxld->dev);
	u32 irq_status;

	irq_status = dcss_पढ़ोl(ctxld->ctxld_reg + DCSS_CTXLD_CONTROL_STATUS);

	अगर (irq_status & CTXLD_IRQ_COMPLETION &&
	    !(irq_status & CTXLD_ENABLE) && ctxld->in_use) अणु
		ctxld->in_use = false;

		अगर (dcss && dcss->disable_callback)
			dcss->disable_callback(dcss);
	पूर्ण अन्यथा अगर (irq_status & CTXLD_IRQ_ERROR) अणु
		/*
		 * Except क्रम throwing an error message and clearing the status
		 * रेजिस्टर, there's not much we can करो here.
		 */
		dev_err(ctxld->dev, "ctxld: error encountered: %08x\n",
			irq_status);
		dev_err(ctxld->dev, "ctxld: db=%d, sb_hp=%d, sb_lp=%d\n",
			ctxld->ctx_size[ctxld->current_ctx ^ 1][CTX_DB],
			ctxld->ctx_size[ctxld->current_ctx ^ 1][CTX_SB_HP],
			ctxld->ctx_size[ctxld->current_ctx ^ 1][CTX_SB_LP]);
	पूर्ण

	dcss_clr(irq_status & (CTXLD_IRQ_ERROR | CTXLD_IRQ_COMPLETION),
		 ctxld->ctxld_reg + DCSS_CTXLD_CONTROL_STATUS);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक dcss_ctxld_irq_config(काष्ठा dcss_ctxld *ctxld,
				 काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;

	ctxld->irq = platक्रमm_get_irq_byname(pdev, "ctxld");
	अगर (ctxld->irq < 0)
		वापस ctxld->irq;

	ret = request_irq(ctxld->irq, dcss_ctxld_irq_handler,
			  0, "dcss_ctxld", ctxld);
	अगर (ret) अणु
		dev_err(ctxld->dev, "ctxld: irq request failed.\n");
		वापस ret;
	पूर्ण

	ctxld->irq_en = true;

	वापस 0;
पूर्ण

अटल व्योम dcss_ctxld_hw_cfg(काष्ठा dcss_ctxld *ctxld)
अणु
	dcss_ग_लिखोl(RD_ERR_EN | SB_HP_COMP_EN |
		    DB_PEND_SB_REC_EN | AHB_ERR_EN | RD_ERR | AHB_ERR,
		    ctxld->ctxld_reg + DCSS_CTXLD_CONTROL_STATUS);
पूर्ण

अटल व्योम dcss_ctxld_मुक्त_ctx(काष्ठा dcss_ctxld *ctxld)
अणु
	काष्ठा dcss_ctxld_item *ctx;
	पूर्णांक i;

	क्रम (i = 0; i < 2; i++) अणु
		अगर (ctxld->db[i]) अणु
			dma_मुक्त_coherent(ctxld->dev,
					  CTXLD_DB_CTX_ENTRIES * माप(*ctx),
					  ctxld->db[i], ctxld->db_paddr[i]);
			ctxld->db[i] = शून्य;
			ctxld->db_paddr[i] = 0;
		पूर्ण

		अगर (ctxld->sb_hp[i]) अणु
			dma_मुक्त_coherent(ctxld->dev,
					  CTXLD_SB_CTX_ENTRIES * माप(*ctx),
					  ctxld->sb_hp[i], ctxld->sb_paddr[i]);
			ctxld->sb_hp[i] = शून्य;
			ctxld->sb_paddr[i] = 0;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक dcss_ctxld_alloc_ctx(काष्ठा dcss_ctxld *ctxld)
अणु
	काष्ठा dcss_ctxld_item *ctx;
	पूर्णांक i;

	क्रम (i = 0; i < 2; i++) अणु
		ctx = dma_alloc_coherent(ctxld->dev,
					 CTXLD_DB_CTX_ENTRIES * माप(*ctx),
					 &ctxld->db_paddr[i], GFP_KERNEL);
		अगर (!ctx)
			वापस -ENOMEM;

		ctxld->db[i] = ctx;

		ctx = dma_alloc_coherent(ctxld->dev,
					 CTXLD_SB_CTX_ENTRIES * माप(*ctx),
					 &ctxld->sb_paddr[i], GFP_KERNEL);
		अगर (!ctx)
			वापस -ENOMEM;

		ctxld->sb_hp[i] = ctx;
		ctxld->sb_lp[i] = ctx + CTXLD_SB_HP_CTX_ENTRIES;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक dcss_ctxld_init(काष्ठा dcss_dev *dcss, अचिन्हित दीर्घ ctxld_base)
अणु
	काष्ठा dcss_ctxld *ctxld;
	पूर्णांक ret;

	ctxld = kzalloc(माप(*ctxld), GFP_KERNEL);
	अगर (!ctxld)
		वापस -ENOMEM;

	dcss->ctxld = ctxld;
	ctxld->dev = dcss->dev;

	spin_lock_init(&ctxld->lock);

	ret = dcss_ctxld_alloc_ctx(ctxld);
	अगर (ret) अणु
		dev_err(dcss->dev, "ctxld: cannot allocate context memory.\n");
		जाओ err;
	पूर्ण

	ctxld->ctxld_reg = ioremap(ctxld_base, SZ_4K);
	अगर (!ctxld->ctxld_reg) अणु
		dev_err(dcss->dev, "ctxld: unable to remap ctxld base\n");
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	ret = dcss_ctxld_irq_config(ctxld, to_platक्रमm_device(dcss->dev));
	अगर (ret)
		जाओ err_irq;

	dcss_ctxld_hw_cfg(ctxld);

	वापस 0;

err_irq:
	iounmap(ctxld->ctxld_reg);

err:
	dcss_ctxld_मुक्त_ctx(ctxld);
	kमुक्त(ctxld);

	वापस ret;
पूर्ण

व्योम dcss_ctxld_निकास(काष्ठा dcss_ctxld *ctxld)
अणु
	मुक्त_irq(ctxld->irq, ctxld);

	अगर (ctxld->ctxld_reg)
		iounmap(ctxld->ctxld_reg);

	dcss_ctxld_मुक्त_ctx(ctxld);
	kमुक्त(ctxld);
पूर्ण

अटल पूर्णांक dcss_ctxld_enable_locked(काष्ठा dcss_ctxld *ctxld)
अणु
	पूर्णांक curr_ctx = ctxld->current_ctx;
	u32 db_base, sb_base, sb_count;
	u32 sb_hp_cnt, sb_lp_cnt, db_cnt;
	काष्ठा dcss_dev *dcss = dcss_drv_dev_to_dcss(ctxld->dev);

	अगर (!dcss)
		वापस 0;

	dcss_dpr_ग_लिखो_sysctrl(dcss->dpr);

	dcss_scaler_ग_लिखो_sclctrl(dcss->scaler);

	sb_hp_cnt = ctxld->ctx_size[curr_ctx][CTX_SB_HP];
	sb_lp_cnt = ctxld->ctx_size[curr_ctx][CTX_SB_LP];
	db_cnt = ctxld->ctx_size[curr_ctx][CTX_DB];

	/* make sure SB_LP context area comes after SB_HP */
	अगर (sb_lp_cnt &&
	    ctxld->sb_lp[curr_ctx] != ctxld->sb_hp[curr_ctx] + sb_hp_cnt) अणु
		काष्ठा dcss_ctxld_item *sb_lp_adjusted;

		sb_lp_adjusted = ctxld->sb_hp[curr_ctx] + sb_hp_cnt;

		स_नकल(sb_lp_adjusted, ctxld->sb_lp[curr_ctx],
		       sb_lp_cnt * CTX_ITEM_SIZE);
	पूर्ण

	db_base = db_cnt ? ctxld->db_paddr[curr_ctx] : 0;

	dcss_ग_लिखोl(db_base, ctxld->ctxld_reg + DCSS_CTXLD_DB_BASE_ADDR);
	dcss_ग_लिखोl(db_cnt, ctxld->ctxld_reg + DCSS_CTXLD_DB_COUNT);

	अगर (sb_hp_cnt)
		sb_count = ((sb_hp_cnt << SB_HP_COUNT_POS) & SB_HP_COUNT_MASK) |
			   ((sb_lp_cnt << SB_LP_COUNT_POS) & SB_LP_COUNT_MASK);
	अन्यथा
		sb_count = (sb_lp_cnt << SB_HP_COUNT_POS) & SB_HP_COUNT_MASK;

	sb_base = sb_count ? ctxld->sb_paddr[curr_ctx] : 0;

	dcss_ग_लिखोl(sb_base, ctxld->ctxld_reg + DCSS_CTXLD_SB_BASE_ADDR);
	dcss_ग_लिखोl(sb_count, ctxld->ctxld_reg + DCSS_CTXLD_SB_COUNT);

	/* enable the context loader */
	dcss_set(CTXLD_ENABLE, ctxld->ctxld_reg + DCSS_CTXLD_CONTROL_STATUS);

	ctxld->in_use = true;

	/*
	 * Toggle the current context to the alternate one so that any updates
	 * in the modules' settings take place there.
	 */
	ctxld->current_ctx ^= 1;

	ctxld->ctx_size[ctxld->current_ctx][CTX_DB] = 0;
	ctxld->ctx_size[ctxld->current_ctx][CTX_SB_HP] = 0;
	ctxld->ctx_size[ctxld->current_ctx][CTX_SB_LP] = 0;

	वापस 0;
पूर्ण

पूर्णांक dcss_ctxld_enable(काष्ठा dcss_ctxld *ctxld)
अणु
	spin_lock_irq(&ctxld->lock);
	ctxld->armed = true;
	spin_unlock_irq(&ctxld->lock);

	वापस 0;
पूर्ण

व्योम dcss_ctxld_kick(काष्ठा dcss_ctxld *ctxld)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ctxld->lock, flags);
	अगर (ctxld->armed && !ctxld->in_use) अणु
		ctxld->armed = false;
		dcss_ctxld_enable_locked(ctxld);
	पूर्ण
	spin_unlock_irqrestore(&ctxld->lock, flags);
पूर्ण

व्योम dcss_ctxld_ग_लिखो_irqsafe(काष्ठा dcss_ctxld *ctxld, u32 ctx_id, u32 val,
			      u32 reg_ofs)
अणु
	पूर्णांक curr_ctx = ctxld->current_ctx;
	काष्ठा dcss_ctxld_item *ctx[] = अणु
		[CTX_DB] = ctxld->db[curr_ctx],
		[CTX_SB_HP] = ctxld->sb_hp[curr_ctx],
		[CTX_SB_LP] = ctxld->sb_lp[curr_ctx]
	पूर्ण;
	पूर्णांक item_idx = ctxld->ctx_size[curr_ctx][ctx_id];

	अगर (item_idx + 1 > dcss_ctxld_ctx_size[ctx_id]) अणु
		WARN_ON(1);
		वापस;
	पूर्ण

	ctx[ctx_id][item_idx].val = val;
	ctx[ctx_id][item_idx].ofs = reg_ofs;
	ctxld->ctx_size[curr_ctx][ctx_id] += 1;
पूर्ण

व्योम dcss_ctxld_ग_लिखो(काष्ठा dcss_ctxld *ctxld, u32 ctx_id,
		      u32 val, u32 reg_ofs)
अणु
	spin_lock_irq(&ctxld->lock);
	dcss_ctxld_ग_लिखो_irqsafe(ctxld, ctx_id, val, reg_ofs);
	spin_unlock_irq(&ctxld->lock);
पूर्ण

bool dcss_ctxld_is_flushed(काष्ठा dcss_ctxld *ctxld)
अणु
	वापस ctxld->ctx_size[ctxld->current_ctx][CTX_DB] == 0 &&
		ctxld->ctx_size[ctxld->current_ctx][CTX_SB_HP] == 0 &&
		ctxld->ctx_size[ctxld->current_ctx][CTX_SB_LP] == 0;
पूर्ण

पूर्णांक dcss_ctxld_resume(काष्ठा dcss_ctxld *ctxld)
अणु
	dcss_ctxld_hw_cfg(ctxld);

	अगर (!ctxld->irq_en) अणु
		enable_irq(ctxld->irq);
		ctxld->irq_en = true;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक dcss_ctxld_suspend(काष्ठा dcss_ctxld *ctxld)
अणु
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ समयout = jअगरfies + msecs_to_jअगरfies(500);

	अगर (!dcss_ctxld_is_flushed(ctxld)) अणु
		dcss_ctxld_kick(ctxld);

		जबतक (!समय_after(jअगरfies, समयout) && ctxld->in_use)
			msleep(20);

		अगर (समय_after(jअगरfies, समयout))
			वापस -ETIMEDOUT;
	पूर्ण

	spin_lock_irq(&ctxld->lock);

	अगर (ctxld->irq_en) अणु
		disable_irq_nosync(ctxld->irq);
		ctxld->irq_en = false;
	पूर्ण

	/* reset context region and sizes */
	ctxld->current_ctx = 0;
	ctxld->ctx_size[0][CTX_DB] = 0;
	ctxld->ctx_size[0][CTX_SB_HP] = 0;
	ctxld->ctx_size[0][CTX_SB_LP] = 0;

	spin_unlock_irq(&ctxld->lock);

	वापस ret;
पूर्ण

व्योम dcss_ctxld_निश्चित_locked(काष्ठा dcss_ctxld *ctxld)
अणु
	lockdep_निश्चित_held(&ctxld->lock);
पूर्ण
