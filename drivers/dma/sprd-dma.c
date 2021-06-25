<शैली गुरु>
/*
 * Copyright (C) 2017 Spपढ़ोtrum Communications Inc.
 *
 * SPDX-License-Identअगरier: GPL-2.0
 */

#समावेश <linux/clk.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dma/sprd-dma.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_dma.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/slab.h>

#समावेश "virt-dma.h"

#घोषणा SPRD_DMA_CHN_REG_OFFSET		0x1000
#घोषणा SPRD_DMA_CHN_REG_LENGTH		0x40
#घोषणा SPRD_DMA_MEMCPY_MIN_SIZE	64

/* DMA global रेजिस्टरs definition */
#घोषणा SPRD_DMA_GLB_PAUSE		0x0
#घोषणा SPRD_DMA_GLB_FRAG_WAIT		0x4
#घोषणा SPRD_DMA_GLB_REQ_PEND0_EN	0x8
#घोषणा SPRD_DMA_GLB_REQ_PEND1_EN	0xc
#घोषणा SPRD_DMA_GLB_INT_RAW_STS	0x10
#घोषणा SPRD_DMA_GLB_INT_MSK_STS	0x14
#घोषणा SPRD_DMA_GLB_REQ_STS		0x18
#घोषणा SPRD_DMA_GLB_CHN_EN_STS		0x1c
#घोषणा SPRD_DMA_GLB_DEBUG_STS		0x20
#घोषणा SPRD_DMA_GLB_ARB_SEL_STS	0x24
#घोषणा SPRD_DMA_GLB_2STAGE_GRP1	0x28
#घोषणा SPRD_DMA_GLB_2STAGE_GRP2	0x2c
#घोषणा SPRD_DMA_GLB_REQ_UID(uid)	(0x4 * ((uid) - 1))
#घोषणा SPRD_DMA_GLB_REQ_UID_OFFSET	0x2000

/* DMA channel रेजिस्टरs definition */
#घोषणा SPRD_DMA_CHN_PAUSE		0x0
#घोषणा SPRD_DMA_CHN_REQ		0x4
#घोषणा SPRD_DMA_CHN_CFG		0x8
#घोषणा SPRD_DMA_CHN_INTC		0xc
#घोषणा SPRD_DMA_CHN_SRC_ADDR		0x10
#घोषणा SPRD_DMA_CHN_DES_ADDR		0x14
#घोषणा SPRD_DMA_CHN_FRG_LEN		0x18
#घोषणा SPRD_DMA_CHN_BLK_LEN		0x1c
#घोषणा SPRD_DMA_CHN_TRSC_LEN		0x20
#घोषणा SPRD_DMA_CHN_TRSF_STEP		0x24
#घोषणा SPRD_DMA_CHN_WARP_PTR		0x28
#घोषणा SPRD_DMA_CHN_WARP_TO		0x2c
#घोषणा SPRD_DMA_CHN_LLIST_PTR		0x30
#घोषणा SPRD_DMA_CHN_FRAG_STEP		0x34
#घोषणा SPRD_DMA_CHN_SRC_BLK_STEP	0x38
#घोषणा SPRD_DMA_CHN_DES_BLK_STEP	0x3c

/* SPRD_DMA_GLB_2STAGE_GRP रेजिस्टर definition */
#घोषणा SPRD_DMA_GLB_2STAGE_EN		BIT(24)
#घोषणा SPRD_DMA_GLB_CHN_INT_MASK	GENMASK(23, 20)
#घोषणा SPRD_DMA_GLB_DEST_INT		BIT(22)
#घोषणा SPRD_DMA_GLB_SRC_INT		BIT(20)
#घोषणा SPRD_DMA_GLB_LIST_DONE_TRG	BIT(19)
#घोषणा SPRD_DMA_GLB_TRANS_DONE_TRG	BIT(18)
#घोषणा SPRD_DMA_GLB_BLOCK_DONE_TRG	BIT(17)
#घोषणा SPRD_DMA_GLB_FRAG_DONE_TRG	BIT(16)
#घोषणा SPRD_DMA_GLB_TRG_OFFSET		16
#घोषणा SPRD_DMA_GLB_DEST_CHN_MASK	GENMASK(13, 8)
#घोषणा SPRD_DMA_GLB_DEST_CHN_OFFSET	8
#घोषणा SPRD_DMA_GLB_SRC_CHN_MASK	GENMASK(5, 0)

/* SPRD_DMA_CHN_INTC रेजिस्टर definition */
#घोषणा SPRD_DMA_INT_MASK		GENMASK(4, 0)
#घोषणा SPRD_DMA_INT_CLR_OFFSET		24
#घोषणा SPRD_DMA_FRAG_INT_EN		BIT(0)
#घोषणा SPRD_DMA_BLK_INT_EN		BIT(1)
#घोषणा SPRD_DMA_TRANS_INT_EN		BIT(2)
#घोषणा SPRD_DMA_LIST_INT_EN		BIT(3)
#घोषणा SPRD_DMA_CFG_ERR_INT_EN		BIT(4)

/* SPRD_DMA_CHN_CFG रेजिस्टर definition */
#घोषणा SPRD_DMA_CHN_EN			BIT(0)
#घोषणा SPRD_DMA_LINKLIST_EN		BIT(4)
#घोषणा SPRD_DMA_WAIT_BDONE_OFFSET	24
#घोषणा SPRD_DMA_DONOT_WAIT_BDONE	1

/* SPRD_DMA_CHN_REQ रेजिस्टर definition */
#घोषणा SPRD_DMA_REQ_EN			BIT(0)

/* SPRD_DMA_CHN_PAUSE रेजिस्टर definition */
#घोषणा SPRD_DMA_PAUSE_EN		BIT(0)
#घोषणा SPRD_DMA_PAUSE_STS		BIT(2)
#घोषणा SPRD_DMA_PAUSE_CNT		0x2000

/* DMA_CHN_WARP_* रेजिस्टर definition */
#घोषणा SPRD_DMA_HIGH_ADDR_MASK		GENMASK(31, 28)
#घोषणा SPRD_DMA_LOW_ADDR_MASK		GENMASK(31, 0)
#घोषणा SPRD_DMA_WRAP_ADDR_MASK		GENMASK(27, 0)
#घोषणा SPRD_DMA_HIGH_ADDR_OFFSET	4

/* SPRD_DMA_CHN_INTC रेजिस्टर definition */
#घोषणा SPRD_DMA_FRAG_INT_STS		BIT(16)
#घोषणा SPRD_DMA_BLK_INT_STS		BIT(17)
#घोषणा SPRD_DMA_TRSC_INT_STS		BIT(18)
#घोषणा SPRD_DMA_LIST_INT_STS		BIT(19)
#घोषणा SPRD_DMA_CFGERR_INT_STS		BIT(20)
#घोषणा SPRD_DMA_CHN_INT_STS					\
	(SPRD_DMA_FRAG_INT_STS | SPRD_DMA_BLK_INT_STS |		\
	 SPRD_DMA_TRSC_INT_STS | SPRD_DMA_LIST_INT_STS |	\
	 SPRD_DMA_CFGERR_INT_STS)

/* SPRD_DMA_CHN_FRG_LEN रेजिस्टर definition */
#घोषणा SPRD_DMA_SRC_DATAWIDTH_OFFSET	30
#घोषणा SPRD_DMA_DES_DATAWIDTH_OFFSET	28
#घोषणा SPRD_DMA_SWT_MODE_OFFSET	26
#घोषणा SPRD_DMA_REQ_MODE_OFFSET	24
#घोषणा SPRD_DMA_REQ_MODE_MASK		GENMASK(1, 0)
#घोषणा SPRD_DMA_WRAP_SEL_DEST		BIT(23)
#घोषणा SPRD_DMA_WRAP_EN		BIT(22)
#घोषणा SPRD_DMA_FIX_SEL_OFFSET		21
#घोषणा SPRD_DMA_FIX_EN_OFFSET		20
#घोषणा SPRD_DMA_LLIST_END		BIT(19)
#घोषणा SPRD_DMA_FRG_LEN_MASK		GENMASK(16, 0)

/* SPRD_DMA_CHN_BLK_LEN रेजिस्टर definition */
#घोषणा SPRD_DMA_BLK_LEN_MASK		GENMASK(16, 0)

/* SPRD_DMA_CHN_TRSC_LEN रेजिस्टर definition */
#घोषणा SPRD_DMA_TRSC_LEN_MASK		GENMASK(27, 0)

/* SPRD_DMA_CHN_TRSF_STEP रेजिस्टर definition */
#घोषणा SPRD_DMA_DEST_TRSF_STEP_OFFSET	16
#घोषणा SPRD_DMA_SRC_TRSF_STEP_OFFSET	0
#घोषणा SPRD_DMA_TRSF_STEP_MASK		GENMASK(15, 0)

/* SPRD DMA_SRC_BLK_STEP रेजिस्टर definition */
#घोषणा SPRD_DMA_LLIST_HIGH_MASK	GENMASK(31, 28)
#घोषणा SPRD_DMA_LLIST_HIGH_SHIFT	28

/* define DMA channel mode & trigger mode mask */
#घोषणा SPRD_DMA_CHN_MODE_MASK		GENMASK(7, 0)
#घोषणा SPRD_DMA_TRG_MODE_MASK		GENMASK(7, 0)
#घोषणा SPRD_DMA_INT_TYPE_MASK		GENMASK(7, 0)

/* define the DMA transfer step type */
#घोषणा SPRD_DMA_NONE_STEP		0
#घोषणा SPRD_DMA_BYTE_STEP		1
#घोषणा SPRD_DMA_SHORT_STEP		2
#घोषणा SPRD_DMA_WORD_STEP		4
#घोषणा SPRD_DMA_DWORD_STEP		8

#घोषणा SPRD_DMA_SOFTWARE_UID		0

/* dma data width values */
क्रमागत sprd_dma_datawidth अणु
	SPRD_DMA_DATAWIDTH_1_BYTE,
	SPRD_DMA_DATAWIDTH_2_BYTES,
	SPRD_DMA_DATAWIDTH_4_BYTES,
	SPRD_DMA_DATAWIDTH_8_BYTES,
पूर्ण;

/* dma channel hardware configuration */
काष्ठा sprd_dma_chn_hw अणु
	u32 छोड़ो;
	u32 req;
	u32 cfg;
	u32 पूर्णांकc;
	u32 src_addr;
	u32 des_addr;
	u32 frg_len;
	u32 blk_len;
	u32 trsc_len;
	u32 trsf_step;
	u32 wrap_ptr;
	u32 wrap_to;
	u32 llist_ptr;
	u32 frg_step;
	u32 src_blk_step;
	u32 des_blk_step;
पूर्ण;

/* dma request description */
काष्ठा sprd_dma_desc अणु
	काष्ठा virt_dma_desc	vd;
	काष्ठा sprd_dma_chn_hw	chn_hw;
	क्रमागत dma_transfer_direction dir;
पूर्ण;

/* dma channel description */
काष्ठा sprd_dma_chn अणु
	काष्ठा virt_dma_chan	vc;
	व्योम __iomem		*chn_base;
	काष्ठा sprd_dma_linklist	linklist;
	काष्ठा dma_slave_config	slave_cfg;
	u32			chn_num;
	u32			dev_id;
	क्रमागत sprd_dma_chn_mode	chn_mode;
	क्रमागत sprd_dma_trg_mode	trg_mode;
	क्रमागत sprd_dma_पूर्णांक_type	पूर्णांक_type;
	काष्ठा sprd_dma_desc	*cur_desc;
पूर्ण;

/* SPRD dma device */
काष्ठा sprd_dma_dev अणु
	काष्ठा dma_device	dma_dev;
	व्योम __iomem		*glb_base;
	काष्ठा clk		*clk;
	काष्ठा clk		*ashb_clk;
	पूर्णांक			irq;
	u32			total_chns;
	काष्ठा sprd_dma_chn	channels[];
पूर्ण;

अटल व्योम sprd_dma_मुक्त_desc(काष्ठा virt_dma_desc *vd);
अटल bool sprd_dma_filter_fn(काष्ठा dma_chan *chan, व्योम *param);
अटल काष्ठा of_dma_filter_info sprd_dma_info = अणु
	.filter_fn = sprd_dma_filter_fn,
पूर्ण;

अटल अंतरभूत काष्ठा sprd_dma_chn *to_sprd_dma_chan(काष्ठा dma_chan *c)
अणु
	वापस container_of(c, काष्ठा sprd_dma_chn, vc.chan);
पूर्ण

अटल अंतरभूत काष्ठा sprd_dma_dev *to_sprd_dma_dev(काष्ठा dma_chan *c)
अणु
	काष्ठा sprd_dma_chn *schan = to_sprd_dma_chan(c);

	वापस container_of(schan, काष्ठा sprd_dma_dev, channels[c->chan_id]);
पूर्ण

अटल अंतरभूत काष्ठा sprd_dma_desc *to_sprd_dma_desc(काष्ठा virt_dma_desc *vd)
अणु
	वापस container_of(vd, काष्ठा sprd_dma_desc, vd);
पूर्ण

अटल व्योम sprd_dma_glb_update(काष्ठा sprd_dma_dev *sdev, u32 reg,
				u32 mask, u32 val)
अणु
	u32 orig = पढ़ोl(sdev->glb_base + reg);
	u32 पंचांगp;

	पंचांगp = (orig & ~mask) | val;
	ग_लिखोl(पंचांगp, sdev->glb_base + reg);
पूर्ण

अटल व्योम sprd_dma_chn_update(काष्ठा sprd_dma_chn *schan, u32 reg,
				u32 mask, u32 val)
अणु
	u32 orig = पढ़ोl(schan->chn_base + reg);
	u32 पंचांगp;

	पंचांगp = (orig & ~mask) | val;
	ग_लिखोl(पंचांगp, schan->chn_base + reg);
पूर्ण

अटल पूर्णांक sprd_dma_enable(काष्ठा sprd_dma_dev *sdev)
अणु
	पूर्णांक ret;

	ret = clk_prepare_enable(sdev->clk);
	अगर (ret)
		वापस ret;

	/*
	 * The ashb_clk is optional and only क्रम AGCP DMA controller, so we
	 * need add one condition to check अगर the ashb_clk need enable.
	 */
	अगर (!IS_ERR(sdev->ashb_clk))
		ret = clk_prepare_enable(sdev->ashb_clk);

	वापस ret;
पूर्ण

अटल व्योम sprd_dma_disable(काष्ठा sprd_dma_dev *sdev)
अणु
	clk_disable_unprepare(sdev->clk);

	/*
	 * Need to check अगर we need disable the optional ashb_clk क्रम AGCP DMA.
	 */
	अगर (!IS_ERR(sdev->ashb_clk))
		clk_disable_unprepare(sdev->ashb_clk);
पूर्ण

अटल व्योम sprd_dma_set_uid(काष्ठा sprd_dma_chn *schan)
अणु
	काष्ठा sprd_dma_dev *sdev = to_sprd_dma_dev(&schan->vc.chan);
	u32 dev_id = schan->dev_id;

	अगर (dev_id != SPRD_DMA_SOFTWARE_UID) अणु
		u32 uid_offset = SPRD_DMA_GLB_REQ_UID_OFFSET +
				 SPRD_DMA_GLB_REQ_UID(dev_id);

		ग_लिखोl(schan->chn_num + 1, sdev->glb_base + uid_offset);
	पूर्ण
पूर्ण

अटल व्योम sprd_dma_unset_uid(काष्ठा sprd_dma_chn *schan)
अणु
	काष्ठा sprd_dma_dev *sdev = to_sprd_dma_dev(&schan->vc.chan);
	u32 dev_id = schan->dev_id;

	अगर (dev_id != SPRD_DMA_SOFTWARE_UID) अणु
		u32 uid_offset = SPRD_DMA_GLB_REQ_UID_OFFSET +
				 SPRD_DMA_GLB_REQ_UID(dev_id);

		ग_लिखोl(0, sdev->glb_base + uid_offset);
	पूर्ण
पूर्ण

अटल व्योम sprd_dma_clear_पूर्णांक(काष्ठा sprd_dma_chn *schan)
अणु
	sprd_dma_chn_update(schan, SPRD_DMA_CHN_INTC,
			    SPRD_DMA_INT_MASK << SPRD_DMA_INT_CLR_OFFSET,
			    SPRD_DMA_INT_MASK << SPRD_DMA_INT_CLR_OFFSET);
पूर्ण

अटल व्योम sprd_dma_enable_chn(काष्ठा sprd_dma_chn *schan)
अणु
	sprd_dma_chn_update(schan, SPRD_DMA_CHN_CFG, SPRD_DMA_CHN_EN,
			    SPRD_DMA_CHN_EN);
पूर्ण

अटल व्योम sprd_dma_disable_chn(काष्ठा sprd_dma_chn *schan)
अणु
	sprd_dma_chn_update(schan, SPRD_DMA_CHN_CFG, SPRD_DMA_CHN_EN, 0);
पूर्ण

अटल व्योम sprd_dma_soft_request(काष्ठा sprd_dma_chn *schan)
अणु
	sprd_dma_chn_update(schan, SPRD_DMA_CHN_REQ, SPRD_DMA_REQ_EN,
			    SPRD_DMA_REQ_EN);
पूर्ण

अटल व्योम sprd_dma_छोड़ो_resume(काष्ठा sprd_dma_chn *schan, bool enable)
अणु
	काष्ठा sprd_dma_dev *sdev = to_sprd_dma_dev(&schan->vc.chan);
	u32 छोड़ो, समयout = SPRD_DMA_PAUSE_CNT;

	अगर (enable) अणु
		sprd_dma_chn_update(schan, SPRD_DMA_CHN_PAUSE,
				    SPRD_DMA_PAUSE_EN, SPRD_DMA_PAUSE_EN);

		करो अणु
			छोड़ो = पढ़ोl(schan->chn_base + SPRD_DMA_CHN_PAUSE);
			अगर (छोड़ो & SPRD_DMA_PAUSE_STS)
				अवरोध;

			cpu_relax();
		पूर्ण जबतक (--समयout > 0);

		अगर (!समयout)
			dev_warn(sdev->dma_dev.dev,
				 "pause dma controller timeout\n");
	पूर्ण अन्यथा अणु
		sprd_dma_chn_update(schan, SPRD_DMA_CHN_PAUSE,
				    SPRD_DMA_PAUSE_EN, 0);
	पूर्ण
पूर्ण

अटल व्योम sprd_dma_stop_and_disable(काष्ठा sprd_dma_chn *schan)
अणु
	u32 cfg = पढ़ोl(schan->chn_base + SPRD_DMA_CHN_CFG);

	अगर (!(cfg & SPRD_DMA_CHN_EN))
		वापस;

	sprd_dma_छोड़ो_resume(schan, true);
	sprd_dma_disable_chn(schan);
पूर्ण

अटल अचिन्हित दीर्घ sprd_dma_get_src_addr(काष्ठा sprd_dma_chn *schan)
अणु
	अचिन्हित दीर्घ addr, addr_high;

	addr = पढ़ोl(schan->chn_base + SPRD_DMA_CHN_SRC_ADDR);
	addr_high = पढ़ोl(schan->chn_base + SPRD_DMA_CHN_WARP_PTR) &
		    SPRD_DMA_HIGH_ADDR_MASK;

	वापस addr | (addr_high << SPRD_DMA_HIGH_ADDR_OFFSET);
पूर्ण

अटल अचिन्हित दीर्घ sprd_dma_get_dst_addr(काष्ठा sprd_dma_chn *schan)
अणु
	अचिन्हित दीर्घ addr, addr_high;

	addr = पढ़ोl(schan->chn_base + SPRD_DMA_CHN_DES_ADDR);
	addr_high = पढ़ोl(schan->chn_base + SPRD_DMA_CHN_WARP_TO) &
		    SPRD_DMA_HIGH_ADDR_MASK;

	वापस addr | (addr_high << SPRD_DMA_HIGH_ADDR_OFFSET);
पूर्ण

अटल क्रमागत sprd_dma_पूर्णांक_type sprd_dma_get_पूर्णांक_type(काष्ठा sprd_dma_chn *schan)
अणु
	काष्ठा sprd_dma_dev *sdev = to_sprd_dma_dev(&schan->vc.chan);
	u32 पूर्णांकc_sts = पढ़ोl(schan->chn_base + SPRD_DMA_CHN_INTC) &
		       SPRD_DMA_CHN_INT_STS;

	चयन (पूर्णांकc_sts) अणु
	हाल SPRD_DMA_CFGERR_INT_STS:
		वापस SPRD_DMA_CFGERR_INT;

	हाल SPRD_DMA_LIST_INT_STS:
		वापस SPRD_DMA_LIST_INT;

	हाल SPRD_DMA_TRSC_INT_STS:
		वापस SPRD_DMA_TRANS_INT;

	हाल SPRD_DMA_BLK_INT_STS:
		वापस SPRD_DMA_BLK_INT;

	हाल SPRD_DMA_FRAG_INT_STS:
		वापस SPRD_DMA_FRAG_INT;

	शेष:
		dev_warn(sdev->dma_dev.dev, "incorrect dma interrupt type\n");
		वापस SPRD_DMA_NO_INT;
	पूर्ण
पूर्ण

अटल क्रमागत sprd_dma_req_mode sprd_dma_get_req_type(काष्ठा sprd_dma_chn *schan)
अणु
	u32 frag_reg = पढ़ोl(schan->chn_base + SPRD_DMA_CHN_FRG_LEN);

	वापस (frag_reg >> SPRD_DMA_REQ_MODE_OFFSET) & SPRD_DMA_REQ_MODE_MASK;
पूर्ण

अटल पूर्णांक sprd_dma_set_2stage_config(काष्ठा sprd_dma_chn *schan)
अणु
	काष्ठा sprd_dma_dev *sdev = to_sprd_dma_dev(&schan->vc.chan);
	u32 val, chn = schan->chn_num + 1;

	चयन (schan->chn_mode) अणु
	हाल SPRD_DMA_SRC_CHN0:
		val = chn & SPRD_DMA_GLB_SRC_CHN_MASK;
		val |= BIT(schan->trg_mode - 1) << SPRD_DMA_GLB_TRG_OFFSET;
		val |= SPRD_DMA_GLB_2STAGE_EN;
		अगर (schan->पूर्णांक_type != SPRD_DMA_NO_INT)
			val |= SPRD_DMA_GLB_SRC_INT;

		sprd_dma_glb_update(sdev, SPRD_DMA_GLB_2STAGE_GRP1, val, val);
		अवरोध;

	हाल SPRD_DMA_SRC_CHN1:
		val = chn & SPRD_DMA_GLB_SRC_CHN_MASK;
		val |= BIT(schan->trg_mode - 1) << SPRD_DMA_GLB_TRG_OFFSET;
		val |= SPRD_DMA_GLB_2STAGE_EN;
		अगर (schan->पूर्णांक_type != SPRD_DMA_NO_INT)
			val |= SPRD_DMA_GLB_SRC_INT;

		sprd_dma_glb_update(sdev, SPRD_DMA_GLB_2STAGE_GRP2, val, val);
		अवरोध;

	हाल SPRD_DMA_DST_CHN0:
		val = (chn << SPRD_DMA_GLB_DEST_CHN_OFFSET) &
			SPRD_DMA_GLB_DEST_CHN_MASK;
		val |= SPRD_DMA_GLB_2STAGE_EN;
		अगर (schan->पूर्णांक_type != SPRD_DMA_NO_INT)
			val |= SPRD_DMA_GLB_DEST_INT;

		sprd_dma_glb_update(sdev, SPRD_DMA_GLB_2STAGE_GRP1, val, val);
		अवरोध;

	हाल SPRD_DMA_DST_CHN1:
		val = (chn << SPRD_DMA_GLB_DEST_CHN_OFFSET) &
			SPRD_DMA_GLB_DEST_CHN_MASK;
		val |= SPRD_DMA_GLB_2STAGE_EN;
		अगर (schan->पूर्णांक_type != SPRD_DMA_NO_INT)
			val |= SPRD_DMA_GLB_DEST_INT;

		sprd_dma_glb_update(sdev, SPRD_DMA_GLB_2STAGE_GRP2, val, val);
		अवरोध;

	शेष:
		dev_err(sdev->dma_dev.dev, "invalid channel mode setting %d\n",
			schan->chn_mode);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम sprd_dma_set_pending(काष्ठा sprd_dma_chn *schan, bool enable)
अणु
	काष्ठा sprd_dma_dev *sdev = to_sprd_dma_dev(&schan->vc.chan);
	u32 reg, val, req_id;

	अगर (schan->dev_id == SPRD_DMA_SOFTWARE_UID)
		वापस;

	/* The DMA request id always starts from 0. */
	req_id = schan->dev_id - 1;

	अगर (req_id < 32) अणु
		reg = SPRD_DMA_GLB_REQ_PEND0_EN;
		val = BIT(req_id);
	पूर्ण अन्यथा अणु
		reg = SPRD_DMA_GLB_REQ_PEND1_EN;
		val = BIT(req_id - 32);
	पूर्ण

	sprd_dma_glb_update(sdev, reg, val, enable ? val : 0);
पूर्ण

अटल व्योम sprd_dma_set_chn_config(काष्ठा sprd_dma_chn *schan,
				    काष्ठा sprd_dma_desc *sdesc)
अणु
	काष्ठा sprd_dma_chn_hw *cfg = &sdesc->chn_hw;

	ग_लिखोl(cfg->छोड़ो, schan->chn_base + SPRD_DMA_CHN_PAUSE);
	ग_लिखोl(cfg->cfg, schan->chn_base + SPRD_DMA_CHN_CFG);
	ग_लिखोl(cfg->पूर्णांकc, schan->chn_base + SPRD_DMA_CHN_INTC);
	ग_लिखोl(cfg->src_addr, schan->chn_base + SPRD_DMA_CHN_SRC_ADDR);
	ग_लिखोl(cfg->des_addr, schan->chn_base + SPRD_DMA_CHN_DES_ADDR);
	ग_लिखोl(cfg->frg_len, schan->chn_base + SPRD_DMA_CHN_FRG_LEN);
	ग_लिखोl(cfg->blk_len, schan->chn_base + SPRD_DMA_CHN_BLK_LEN);
	ग_लिखोl(cfg->trsc_len, schan->chn_base + SPRD_DMA_CHN_TRSC_LEN);
	ग_लिखोl(cfg->trsf_step, schan->chn_base + SPRD_DMA_CHN_TRSF_STEP);
	ग_लिखोl(cfg->wrap_ptr, schan->chn_base + SPRD_DMA_CHN_WARP_PTR);
	ग_लिखोl(cfg->wrap_to, schan->chn_base + SPRD_DMA_CHN_WARP_TO);
	ग_लिखोl(cfg->llist_ptr, schan->chn_base + SPRD_DMA_CHN_LLIST_PTR);
	ग_लिखोl(cfg->frg_step, schan->chn_base + SPRD_DMA_CHN_FRAG_STEP);
	ग_लिखोl(cfg->src_blk_step, schan->chn_base + SPRD_DMA_CHN_SRC_BLK_STEP);
	ग_लिखोl(cfg->des_blk_step, schan->chn_base + SPRD_DMA_CHN_DES_BLK_STEP);
	ग_लिखोl(cfg->req, schan->chn_base + SPRD_DMA_CHN_REQ);
पूर्ण

अटल व्योम sprd_dma_start(काष्ठा sprd_dma_chn *schan)
अणु
	काष्ठा virt_dma_desc *vd = vchan_next_desc(&schan->vc);

	अगर (!vd)
		वापस;

	list_del(&vd->node);
	schan->cur_desc = to_sprd_dma_desc(vd);

	/*
	 * Set 2-stage configuration अगर the channel starts one 2-stage
	 * transfer.
	 */
	अगर (schan->chn_mode && sprd_dma_set_2stage_config(schan))
		वापस;

	/*
	 * Copy the DMA configuration from DMA descriptor to this hardware
	 * channel.
	 */
	sprd_dma_set_chn_config(schan, schan->cur_desc);
	sprd_dma_set_uid(schan);
	sprd_dma_set_pending(schan, true);
	sprd_dma_enable_chn(schan);

	अगर (schan->dev_id == SPRD_DMA_SOFTWARE_UID &&
	    schan->chn_mode != SPRD_DMA_DST_CHN0 &&
	    schan->chn_mode != SPRD_DMA_DST_CHN1)
		sprd_dma_soft_request(schan);
पूर्ण

अटल व्योम sprd_dma_stop(काष्ठा sprd_dma_chn *schan)
अणु
	sprd_dma_stop_and_disable(schan);
	sprd_dma_set_pending(schan, false);
	sprd_dma_unset_uid(schan);
	sprd_dma_clear_पूर्णांक(schan);
	schan->cur_desc = शून्य;
पूर्ण

अटल bool sprd_dma_check_trans_करोne(काष्ठा sprd_dma_desc *sdesc,
				      क्रमागत sprd_dma_पूर्णांक_type पूर्णांक_type,
				      क्रमागत sprd_dma_req_mode req_mode)
अणु
	अगर (पूर्णांक_type == SPRD_DMA_NO_INT)
		वापस false;

	अगर (पूर्णांक_type >= req_mode + 1)
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

अटल irqवापस_t dma_irq_handle(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा sprd_dma_dev *sdev = (काष्ठा sprd_dma_dev *)dev_id;
	u32 irq_status = पढ़ोl(sdev->glb_base + SPRD_DMA_GLB_INT_MSK_STS);
	काष्ठा sprd_dma_chn *schan;
	काष्ठा sprd_dma_desc *sdesc;
	क्रमागत sprd_dma_req_mode req_type;
	क्रमागत sprd_dma_पूर्णांक_type पूर्णांक_type;
	bool trans_करोne = false, cyclic = false;
	u32 i;

	जबतक (irq_status) अणु
		i = __ffs(irq_status);
		irq_status &= (irq_status - 1);
		schan = &sdev->channels[i];

		spin_lock(&schan->vc.lock);

		sdesc = schan->cur_desc;
		अगर (!sdesc) अणु
			spin_unlock(&schan->vc.lock);
			वापस IRQ_HANDLED;
		पूर्ण

		पूर्णांक_type = sprd_dma_get_पूर्णांक_type(schan);
		req_type = sprd_dma_get_req_type(schan);
		sprd_dma_clear_पूर्णांक(schan);

		/* cyclic mode schedule callback */
		cyclic = schan->linklist.phy_addr ? true : false;
		अगर (cyclic == true) अणु
			vchan_cyclic_callback(&sdesc->vd);
		पूर्ण अन्यथा अणु
			/* Check अगर the dma request descriptor is करोne. */
			trans_करोne = sprd_dma_check_trans_करोne(sdesc, पूर्णांक_type,
							       req_type);
			अगर (trans_करोne == true) अणु
				vchan_cookie_complete(&sdesc->vd);
				schan->cur_desc = शून्य;
				sprd_dma_start(schan);
			पूर्ण
		पूर्ण
		spin_unlock(&schan->vc.lock);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक sprd_dma_alloc_chan_resources(काष्ठा dma_chan *chan)
अणु
	वापस pm_runसमय_get_sync(chan->device->dev);
पूर्ण

अटल व्योम sprd_dma_मुक्त_chan_resources(काष्ठा dma_chan *chan)
अणु
	काष्ठा sprd_dma_chn *schan = to_sprd_dma_chan(chan);
	काष्ठा virt_dma_desc *cur_vd = शून्य;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&schan->vc.lock, flags);
	अगर (schan->cur_desc)
		cur_vd = &schan->cur_desc->vd;

	sprd_dma_stop(schan);
	spin_unlock_irqrestore(&schan->vc.lock, flags);

	अगर (cur_vd)
		sprd_dma_मुक्त_desc(cur_vd);

	vchan_मुक्त_chan_resources(&schan->vc);
	pm_runसमय_put(chan->device->dev);
पूर्ण

अटल क्रमागत dma_status sprd_dma_tx_status(काष्ठा dma_chan *chan,
					  dma_cookie_t cookie,
					  काष्ठा dma_tx_state *txstate)
अणु
	काष्ठा sprd_dma_chn *schan = to_sprd_dma_chan(chan);
	काष्ठा virt_dma_desc *vd;
	अचिन्हित दीर्घ flags;
	क्रमागत dma_status ret;
	u32 pos;

	ret = dma_cookie_status(chan, cookie, txstate);
	अगर (ret == DMA_COMPLETE || !txstate)
		वापस ret;

	spin_lock_irqsave(&schan->vc.lock, flags);
	vd = vchan_find_desc(&schan->vc, cookie);
	अगर (vd) अणु
		काष्ठा sprd_dma_desc *sdesc = to_sprd_dma_desc(vd);
		काष्ठा sprd_dma_chn_hw *hw = &sdesc->chn_hw;

		अगर (hw->trsc_len > 0)
			pos = hw->trsc_len;
		अन्यथा अगर (hw->blk_len > 0)
			pos = hw->blk_len;
		अन्यथा अगर (hw->frg_len > 0)
			pos = hw->frg_len;
		अन्यथा
			pos = 0;
	पूर्ण अन्यथा अगर (schan->cur_desc && schan->cur_desc->vd.tx.cookie == cookie) अणु
		काष्ठा sprd_dma_desc *sdesc = schan->cur_desc;

		अगर (sdesc->dir == DMA_DEV_TO_MEM)
			pos = sprd_dma_get_dst_addr(schan);
		अन्यथा
			pos = sprd_dma_get_src_addr(schan);
	पूर्ण अन्यथा अणु
		pos = 0;
	पूर्ण
	spin_unlock_irqrestore(&schan->vc.lock, flags);

	dma_set_residue(txstate, pos);
	वापस ret;
पूर्ण

अटल व्योम sprd_dma_issue_pending(काष्ठा dma_chan *chan)
अणु
	काष्ठा sprd_dma_chn *schan = to_sprd_dma_chan(chan);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&schan->vc.lock, flags);
	अगर (vchan_issue_pending(&schan->vc) && !schan->cur_desc)
		sprd_dma_start(schan);
	spin_unlock_irqrestore(&schan->vc.lock, flags);
पूर्ण

अटल पूर्णांक sprd_dma_get_datawidth(क्रमागत dma_slave_buswidth buswidth)
अणु
	चयन (buswidth) अणु
	हाल DMA_SLAVE_BUSWIDTH_1_BYTE:
	हाल DMA_SLAVE_BUSWIDTH_2_BYTES:
	हाल DMA_SLAVE_BUSWIDTH_4_BYTES:
	हाल DMA_SLAVE_BUSWIDTH_8_BYTES:
		वापस ffs(buswidth) - 1;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक sprd_dma_get_step(क्रमागत dma_slave_buswidth buswidth)
अणु
	चयन (buswidth) अणु
	हाल DMA_SLAVE_BUSWIDTH_1_BYTE:
	हाल DMA_SLAVE_BUSWIDTH_2_BYTES:
	हाल DMA_SLAVE_BUSWIDTH_4_BYTES:
	हाल DMA_SLAVE_BUSWIDTH_8_BYTES:
		वापस buswidth;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक sprd_dma_fill_desc(काष्ठा dma_chan *chan,
			      काष्ठा sprd_dma_chn_hw *hw,
			      अचिन्हित पूर्णांक sglen, पूर्णांक sg_index,
			      dma_addr_t src, dma_addr_t dst, u32 len,
			      क्रमागत dma_transfer_direction dir,
			      अचिन्हित दीर्घ flags,
			      काष्ठा dma_slave_config *slave_cfg)
अणु
	काष्ठा sprd_dma_dev *sdev = to_sprd_dma_dev(chan);
	काष्ठा sprd_dma_chn *schan = to_sprd_dma_chan(chan);
	क्रमागत sprd_dma_chn_mode chn_mode = schan->chn_mode;
	u32 req_mode = (flags >> SPRD_DMA_REQ_SHIFT) & SPRD_DMA_REQ_MODE_MASK;
	u32 पूर्णांक_mode = flags & SPRD_DMA_INT_MASK;
	पूर्णांक src_datawidth, dst_datawidth, src_step, dst_step;
	u32 temp, fix_mode = 0, fix_en = 0;
	phys_addr_t llist_ptr;

	अगर (dir == DMA_MEM_TO_DEV) अणु
		src_step = sprd_dma_get_step(slave_cfg->src_addr_width);
		अगर (src_step < 0) अणु
			dev_err(sdev->dma_dev.dev, "invalid source step\n");
			वापस src_step;
		पूर्ण

		/*
		 * For 2-stage transfer, destination channel step can not be 0,
		 * since destination device is AON IRAM.
		 */
		अगर (chn_mode == SPRD_DMA_DST_CHN0 ||
		    chn_mode == SPRD_DMA_DST_CHN1)
			dst_step = src_step;
		अन्यथा
			dst_step = SPRD_DMA_NONE_STEP;
	पूर्ण अन्यथा अणु
		dst_step = sprd_dma_get_step(slave_cfg->dst_addr_width);
		अगर (dst_step < 0) अणु
			dev_err(sdev->dma_dev.dev, "invalid destination step\n");
			वापस dst_step;
		पूर्ण
		src_step = SPRD_DMA_NONE_STEP;
	पूर्ण

	src_datawidth = sprd_dma_get_datawidth(slave_cfg->src_addr_width);
	अगर (src_datawidth < 0) अणु
		dev_err(sdev->dma_dev.dev, "invalid source datawidth\n");
		वापस src_datawidth;
	पूर्ण

	dst_datawidth = sprd_dma_get_datawidth(slave_cfg->dst_addr_width);
	अगर (dst_datawidth < 0) अणु
		dev_err(sdev->dma_dev.dev, "invalid destination datawidth\n");
		वापस dst_datawidth;
	पूर्ण

	अगर (slave_cfg->slave_id)
		schan->dev_id = slave_cfg->slave_id;

	hw->cfg = SPRD_DMA_DONOT_WAIT_BDONE << SPRD_DMA_WAIT_BDONE_OFFSET;

	/*
	 * wrap_ptr and wrap_to will save the high 4 bits source address and
	 * destination address.
	 */
	hw->wrap_ptr = (src >> SPRD_DMA_HIGH_ADDR_OFFSET) & SPRD_DMA_HIGH_ADDR_MASK;
	hw->wrap_to = (dst >> SPRD_DMA_HIGH_ADDR_OFFSET) & SPRD_DMA_HIGH_ADDR_MASK;
	hw->src_addr = src & SPRD_DMA_LOW_ADDR_MASK;
	hw->des_addr = dst & SPRD_DMA_LOW_ADDR_MASK;

	/*
	 * If the src step and dst step both are 0 or both are not 0, that means
	 * we can not enable the fix mode. If one is 0 and another one is not,
	 * we can enable the fix mode.
	 */
	अगर ((src_step != 0 && dst_step != 0) || (src_step | dst_step) == 0) अणु
		fix_en = 0;
	पूर्ण अन्यथा अणु
		fix_en = 1;
		अगर (src_step)
			fix_mode = 1;
		अन्यथा
			fix_mode = 0;
	पूर्ण

	hw->पूर्णांकc = पूर्णांक_mode | SPRD_DMA_CFG_ERR_INT_EN;

	temp = src_datawidth << SPRD_DMA_SRC_DATAWIDTH_OFFSET;
	temp |= dst_datawidth << SPRD_DMA_DES_DATAWIDTH_OFFSET;
	temp |= req_mode << SPRD_DMA_REQ_MODE_OFFSET;
	temp |= fix_mode << SPRD_DMA_FIX_SEL_OFFSET;
	temp |= fix_en << SPRD_DMA_FIX_EN_OFFSET;
	temp |= schan->linklist.wrap_addr ?
		SPRD_DMA_WRAP_EN | SPRD_DMA_WRAP_SEL_DEST : 0;
	temp |= slave_cfg->src_maxburst & SPRD_DMA_FRG_LEN_MASK;
	hw->frg_len = temp;

	hw->blk_len = slave_cfg->src_maxburst & SPRD_DMA_BLK_LEN_MASK;
	hw->trsc_len = len & SPRD_DMA_TRSC_LEN_MASK;

	temp = (dst_step & SPRD_DMA_TRSF_STEP_MASK) << SPRD_DMA_DEST_TRSF_STEP_OFFSET;
	temp |= (src_step & SPRD_DMA_TRSF_STEP_MASK) << SPRD_DMA_SRC_TRSF_STEP_OFFSET;
	hw->trsf_step = temp;

	/* link-list configuration */
	अगर (schan->linklist.phy_addr) अणु
		hw->cfg |= SPRD_DMA_LINKLIST_EN;

		/* link-list index */
		temp = sglen ? (sg_index + 1) % sglen : 0;

		/* Next link-list configuration's physical address offset */
		temp = temp * माप(*hw) + SPRD_DMA_CHN_SRC_ADDR;
		/*
		 * Set the link-list poपूर्णांकer poपूर्णांक to next link-list
		 * configuration's physical address.
		 */
		llist_ptr = schan->linklist.phy_addr + temp;
		hw->llist_ptr = lower_32_bits(llist_ptr);
		hw->src_blk_step = (upper_32_bits(llist_ptr) << SPRD_DMA_LLIST_HIGH_SHIFT) &
			SPRD_DMA_LLIST_HIGH_MASK;

		अगर (schan->linklist.wrap_addr) अणु
			hw->wrap_ptr |= schan->linklist.wrap_addr &
				SPRD_DMA_WRAP_ADDR_MASK;
			hw->wrap_to |= dst & SPRD_DMA_WRAP_ADDR_MASK;
		पूर्ण
	पूर्ण अन्यथा अणु
		hw->llist_ptr = 0;
		hw->src_blk_step = 0;
	पूर्ण

	hw->frg_step = 0;
	hw->des_blk_step = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक sprd_dma_fill_linklist_desc(काष्ठा dma_chan *chan,
				       अचिन्हित पूर्णांक sglen, पूर्णांक sg_index,
				       dma_addr_t src, dma_addr_t dst, u32 len,
				       क्रमागत dma_transfer_direction dir,
				       अचिन्हित दीर्घ flags,
				       काष्ठा dma_slave_config *slave_cfg)
अणु
	काष्ठा sprd_dma_chn *schan = to_sprd_dma_chan(chan);
	काष्ठा sprd_dma_chn_hw *hw;

	अगर (!schan->linklist.virt_addr)
		वापस -EINVAL;

	hw = (काष्ठा sprd_dma_chn_hw *)(schan->linklist.virt_addr +
					sg_index * माप(*hw));

	वापस sprd_dma_fill_desc(chan, hw, sglen, sg_index, src, dst, len,
				  dir, flags, slave_cfg);
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
sprd_dma_prep_dma_स_नकल(काष्ठा dma_chan *chan, dma_addr_t dest, dma_addr_t src,
			 माप_प्रकार len, अचिन्हित दीर्घ flags)
अणु
	काष्ठा sprd_dma_chn *schan = to_sprd_dma_chan(chan);
	काष्ठा sprd_dma_desc *sdesc;
	काष्ठा sprd_dma_chn_hw *hw;
	क्रमागत sprd_dma_datawidth datawidth;
	u32 step, temp;

	sdesc = kzalloc(माप(*sdesc), GFP_NOWAIT);
	अगर (!sdesc)
		वापस शून्य;

	hw = &sdesc->chn_hw;

	hw->cfg = SPRD_DMA_DONOT_WAIT_BDONE << SPRD_DMA_WAIT_BDONE_OFFSET;
	hw->पूर्णांकc = SPRD_DMA_TRANS_INT | SPRD_DMA_CFG_ERR_INT_EN;
	hw->src_addr = src & SPRD_DMA_LOW_ADDR_MASK;
	hw->des_addr = dest & SPRD_DMA_LOW_ADDR_MASK;
	hw->wrap_ptr = (src >> SPRD_DMA_HIGH_ADDR_OFFSET) &
		SPRD_DMA_HIGH_ADDR_MASK;
	hw->wrap_to = (dest >> SPRD_DMA_HIGH_ADDR_OFFSET) &
		SPRD_DMA_HIGH_ADDR_MASK;

	अगर (IS_ALIGNED(len, 8)) अणु
		datawidth = SPRD_DMA_DATAWIDTH_8_BYTES;
		step = SPRD_DMA_DWORD_STEP;
	पूर्ण अन्यथा अगर (IS_ALIGNED(len, 4)) अणु
		datawidth = SPRD_DMA_DATAWIDTH_4_BYTES;
		step = SPRD_DMA_WORD_STEP;
	पूर्ण अन्यथा अगर (IS_ALIGNED(len, 2)) अणु
		datawidth = SPRD_DMA_DATAWIDTH_2_BYTES;
		step = SPRD_DMA_SHORT_STEP;
	पूर्ण अन्यथा अणु
		datawidth = SPRD_DMA_DATAWIDTH_1_BYTE;
		step = SPRD_DMA_BYTE_STEP;
	पूर्ण

	temp = datawidth << SPRD_DMA_SRC_DATAWIDTH_OFFSET;
	temp |= datawidth << SPRD_DMA_DES_DATAWIDTH_OFFSET;
	temp |= SPRD_DMA_TRANS_REQ << SPRD_DMA_REQ_MODE_OFFSET;
	temp |= len & SPRD_DMA_FRG_LEN_MASK;
	hw->frg_len = temp;

	hw->blk_len = len & SPRD_DMA_BLK_LEN_MASK;
	hw->trsc_len = len & SPRD_DMA_TRSC_LEN_MASK;

	temp = (step & SPRD_DMA_TRSF_STEP_MASK) << SPRD_DMA_DEST_TRSF_STEP_OFFSET;
	temp |= (step & SPRD_DMA_TRSF_STEP_MASK) << SPRD_DMA_SRC_TRSF_STEP_OFFSET;
	hw->trsf_step = temp;

	वापस vchan_tx_prep(&schan->vc, &sdesc->vd, flags);
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
sprd_dma_prep_slave_sg(काष्ठा dma_chan *chan, काष्ठा scatterlist *sgl,
		       अचिन्हित पूर्णांक sglen, क्रमागत dma_transfer_direction dir,
		       अचिन्हित दीर्घ flags, व्योम *context)
अणु
	काष्ठा sprd_dma_chn *schan = to_sprd_dma_chan(chan);
	काष्ठा dma_slave_config *slave_cfg = &schan->slave_cfg;
	dma_addr_t src = 0, dst = 0;
	dma_addr_t start_src = 0, start_dst = 0;
	काष्ठा sprd_dma_desc *sdesc;
	काष्ठा scatterlist *sg;
	u32 len = 0;
	पूर्णांक ret, i;

	अगर (!is_slave_direction(dir))
		वापस शून्य;

	अगर (context) अणु
		काष्ठा sprd_dma_linklist *ll_cfg =
			(काष्ठा sprd_dma_linklist *)context;

		schan->linklist.phy_addr = ll_cfg->phy_addr;
		schan->linklist.virt_addr = ll_cfg->virt_addr;
		schan->linklist.wrap_addr = ll_cfg->wrap_addr;
	पूर्ण अन्यथा अणु
		schan->linklist.phy_addr = 0;
		schan->linklist.virt_addr = 0;
		schan->linklist.wrap_addr = 0;
	पूर्ण

	/*
	 * Set channel mode, पूर्णांकerrupt mode and trigger mode क्रम 2-stage
	 * transfer.
	 */
	schan->chn_mode =
		(flags >> SPRD_DMA_CHN_MODE_SHIFT) & SPRD_DMA_CHN_MODE_MASK;
	schan->trg_mode =
		(flags >> SPRD_DMA_TRG_MODE_SHIFT) & SPRD_DMA_TRG_MODE_MASK;
	schan->पूर्णांक_type = flags & SPRD_DMA_INT_TYPE_MASK;

	sdesc = kzalloc(माप(*sdesc), GFP_NOWAIT);
	अगर (!sdesc)
		वापस शून्य;

	sdesc->dir = dir;

	क्रम_each_sg(sgl, sg, sglen, i) अणु
		len = sg_dma_len(sg);

		अगर (dir == DMA_MEM_TO_DEV) अणु
			src = sg_dma_address(sg);
			dst = slave_cfg->dst_addr;
		पूर्ण अन्यथा अणु
			src = slave_cfg->src_addr;
			dst = sg_dma_address(sg);
		पूर्ण

		अगर (!i) अणु
			start_src = src;
			start_dst = dst;
		पूर्ण

		/*
		 * The link-list mode needs at least 2 link-list
		 * configurations. If there is only one sg, it करोesn't
		 * need to fill the link-list configuration.
		 */
		अगर (sglen < 2)
			अवरोध;

		ret = sprd_dma_fill_linklist_desc(chan, sglen, i, src, dst, len,
						  dir, flags, slave_cfg);
		अगर (ret) अणु
			kमुक्त(sdesc);
			वापस शून्य;
		पूर्ण
	पूर्ण

	ret = sprd_dma_fill_desc(chan, &sdesc->chn_hw, 0, 0, start_src,
				 start_dst, len, dir, flags, slave_cfg);
	अगर (ret) अणु
		kमुक्त(sdesc);
		वापस शून्य;
	पूर्ण

	वापस vchan_tx_prep(&schan->vc, &sdesc->vd, flags);
पूर्ण

अटल पूर्णांक sprd_dma_slave_config(काष्ठा dma_chan *chan,
				 काष्ठा dma_slave_config *config)
अणु
	काष्ठा sprd_dma_chn *schan = to_sprd_dma_chan(chan);
	काष्ठा dma_slave_config *slave_cfg = &schan->slave_cfg;

	स_नकल(slave_cfg, config, माप(*config));
	वापस 0;
पूर्ण

अटल पूर्णांक sprd_dma_छोड़ो(काष्ठा dma_chan *chan)
अणु
	काष्ठा sprd_dma_chn *schan = to_sprd_dma_chan(chan);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&schan->vc.lock, flags);
	sprd_dma_छोड़ो_resume(schan, true);
	spin_unlock_irqrestore(&schan->vc.lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक sprd_dma_resume(काष्ठा dma_chan *chan)
अणु
	काष्ठा sprd_dma_chn *schan = to_sprd_dma_chan(chan);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&schan->vc.lock, flags);
	sprd_dma_छोड़ो_resume(schan, false);
	spin_unlock_irqrestore(&schan->vc.lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक sprd_dma_terminate_all(काष्ठा dma_chan *chan)
अणु
	काष्ठा sprd_dma_chn *schan = to_sprd_dma_chan(chan);
	काष्ठा virt_dma_desc *cur_vd = शून्य;
	अचिन्हित दीर्घ flags;
	LIST_HEAD(head);

	spin_lock_irqsave(&schan->vc.lock, flags);
	अगर (schan->cur_desc)
		cur_vd = &schan->cur_desc->vd;

	sprd_dma_stop(schan);

	vchan_get_all_descriptors(&schan->vc, &head);
	spin_unlock_irqrestore(&schan->vc.lock, flags);

	अगर (cur_vd)
		sprd_dma_मुक्त_desc(cur_vd);

	vchan_dma_desc_मुक्त_list(&schan->vc, &head);
	वापस 0;
पूर्ण

अटल व्योम sprd_dma_मुक्त_desc(काष्ठा virt_dma_desc *vd)
अणु
	काष्ठा sprd_dma_desc *sdesc = to_sprd_dma_desc(vd);

	kमुक्त(sdesc);
पूर्ण

अटल bool sprd_dma_filter_fn(काष्ठा dma_chan *chan, व्योम *param)
अणु
	काष्ठा sprd_dma_chn *schan = to_sprd_dma_chan(chan);
	u32 slave_id = *(u32 *)param;

	schan->dev_id = slave_id;
	वापस true;
पूर्ण

अटल पूर्णांक sprd_dma_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा sprd_dma_dev *sdev;
	काष्ठा sprd_dma_chn *dma_chn;
	u32 chn_count;
	पूर्णांक ret, i;

	ret = device_property_पढ़ो_u32(&pdev->dev, "#dma-channels", &chn_count);
	अगर (ret) अणु
		dev_err(&pdev->dev, "get dma channels count failed\n");
		वापस ret;
	पूर्ण

	sdev = devm_kzalloc(&pdev->dev,
			    काष्ठा_size(sdev, channels, chn_count),
			    GFP_KERNEL);
	अगर (!sdev)
		वापस -ENOMEM;

	sdev->clk = devm_clk_get(&pdev->dev, "enable");
	अगर (IS_ERR(sdev->clk)) अणु
		dev_err(&pdev->dev, "get enable clock failed\n");
		वापस PTR_ERR(sdev->clk);
	पूर्ण

	/* ashb घड़ी is optional क्रम AGCP DMA */
	sdev->ashb_clk = devm_clk_get(&pdev->dev, "ashb_eb");
	अगर (IS_ERR(sdev->ashb_clk))
		dev_warn(&pdev->dev, "no optional ashb eb clock\n");

	/*
	 * We have three DMA controllers: AP DMA, AON DMA and AGCP DMA. For AGCP
	 * DMA controller, it can or करो not request the irq, which will save
	 * प्रणाली घातer without resuming प्रणाली by DMA पूर्णांकerrupts अगर AGCP DMA
	 * करोes not request the irq. Thus the DMA पूर्णांकerrupts property should
	 * be optional.
	 */
	sdev->irq = platक्रमm_get_irq(pdev, 0);
	अगर (sdev->irq > 0) अणु
		ret = devm_request_irq(&pdev->dev, sdev->irq, dma_irq_handle,
				       0, "sprd_dma", (व्योम *)sdev);
		अगर (ret < 0) अणु
			dev_err(&pdev->dev, "request dma irq failed\n");
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_warn(&pdev->dev, "no interrupts for the dma controller\n");
	पूर्ण

	sdev->glb_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(sdev->glb_base))
		वापस PTR_ERR(sdev->glb_base);

	dma_cap_set(DMA_MEMCPY, sdev->dma_dev.cap_mask);
	sdev->total_chns = chn_count;
	sdev->dma_dev.chancnt = chn_count;
	INIT_LIST_HEAD(&sdev->dma_dev.channels);
	INIT_LIST_HEAD(&sdev->dma_dev.global_node);
	sdev->dma_dev.dev = &pdev->dev;
	sdev->dma_dev.device_alloc_chan_resources = sprd_dma_alloc_chan_resources;
	sdev->dma_dev.device_मुक्त_chan_resources = sprd_dma_मुक्त_chan_resources;
	sdev->dma_dev.device_tx_status = sprd_dma_tx_status;
	sdev->dma_dev.device_issue_pending = sprd_dma_issue_pending;
	sdev->dma_dev.device_prep_dma_स_नकल = sprd_dma_prep_dma_स_नकल;
	sdev->dma_dev.device_prep_slave_sg = sprd_dma_prep_slave_sg;
	sdev->dma_dev.device_config = sprd_dma_slave_config;
	sdev->dma_dev.device_छोड़ो = sprd_dma_छोड़ो;
	sdev->dma_dev.device_resume = sprd_dma_resume;
	sdev->dma_dev.device_terminate_all = sprd_dma_terminate_all;

	क्रम (i = 0; i < chn_count; i++) अणु
		dma_chn = &sdev->channels[i];
		dma_chn->chn_num = i;
		dma_chn->cur_desc = शून्य;
		/* get each channel's रेजिस्टरs base address. */
		dma_chn->chn_base = sdev->glb_base + SPRD_DMA_CHN_REG_OFFSET +
				    SPRD_DMA_CHN_REG_LENGTH * i;

		dma_chn->vc.desc_मुक्त = sprd_dma_मुक्त_desc;
		vchan_init(&dma_chn->vc, &sdev->dma_dev);
	पूर्ण

	platक्रमm_set_drvdata(pdev, sdev);
	ret = sprd_dma_enable(sdev);
	अगर (ret)
		वापस ret;

	pm_runसमय_set_active(&pdev->dev);
	pm_runसमय_enable(&pdev->dev);

	ret = pm_runसमय_get_sync(&pdev->dev);
	अगर (ret < 0)
		जाओ err_rpm;

	ret = dma_async_device_रेजिस्टर(&sdev->dma_dev);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "register dma device failed:%d\n", ret);
		जाओ err_रेजिस्टर;
	पूर्ण

	sprd_dma_info.dma_cap = sdev->dma_dev.cap_mask;
	ret = of_dma_controller_रेजिस्टर(np, of_dma_simple_xlate,
					 &sprd_dma_info);
	अगर (ret)
		जाओ err_of_रेजिस्टर;

	pm_runसमय_put(&pdev->dev);
	वापस 0;

err_of_रेजिस्टर:
	dma_async_device_unरेजिस्टर(&sdev->dma_dev);
err_रेजिस्टर:
	pm_runसमय_put_noidle(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);
err_rpm:
	sprd_dma_disable(sdev);
	वापस ret;
पूर्ण

अटल पूर्णांक sprd_dma_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sprd_dma_dev *sdev = platक्रमm_get_drvdata(pdev);
	काष्ठा sprd_dma_chn *c, *cn;
	पूर्णांक ret;

	ret = pm_runसमय_get_sync(&pdev->dev);
	अगर (ret < 0)
		वापस ret;

	/* explicitly मुक्त the irq */
	अगर (sdev->irq > 0)
		devm_मुक्त_irq(&pdev->dev, sdev->irq, sdev);

	list_क्रम_each_entry_safe(c, cn, &sdev->dma_dev.channels,
				 vc.chan.device_node) अणु
		list_del(&c->vc.chan.device_node);
		tasklet_समाप्त(&c->vc.task);
	पूर्ण

	of_dma_controller_मुक्त(pdev->dev.of_node);
	dma_async_device_unरेजिस्टर(&sdev->dma_dev);
	sprd_dma_disable(sdev);

	pm_runसमय_put_noidle(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id sprd_dma_match[] = अणु
	अणु .compatible = "sprd,sc9860-dma", पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक __maybe_unused sprd_dma_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा sprd_dma_dev *sdev = dev_get_drvdata(dev);

	sprd_dma_disable(sdev);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused sprd_dma_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा sprd_dma_dev *sdev = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = sprd_dma_enable(sdev);
	अगर (ret)
		dev_err(sdev->dma_dev.dev, "enable dma failed\n");

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops sprd_dma_pm_ops = अणु
	SET_RUNTIME_PM_OPS(sprd_dma_runसमय_suspend,
			   sprd_dma_runसमय_resume,
			   शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver sprd_dma_driver = अणु
	.probe = sprd_dma_probe,
	.हटाओ = sprd_dma_हटाओ,
	.driver = अणु
		.name = "sprd-dma",
		.of_match_table = sprd_dma_match,
		.pm = &sprd_dma_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(sprd_dma_driver);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("DMA driver for Spreadtrum");
MODULE_AUTHOR("Baolin Wang <baolin.wang@spreadtrum.com>");
MODULE_AUTHOR("Eric Long <eric.long@spreadtrum.com>");
MODULE_ALIAS("platform:sprd-dma");
