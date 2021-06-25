<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2010-2013 Bluecherry, LLC <https://www.bluecherrydvr.com>
 *
 * Original author:
 * Ben Collins <bcollins@ubuntu.com>
 *
 * Additional work by:
 * John Brooks <john.brooks@bluecherry.net>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>

#समावेश "solo6x10.h"

अटल पूर्णांक multi_p2m;
module_param(multi_p2m, uपूर्णांक, 0644);
MODULE_PARM_DESC(multi_p2m,
		 "Use multiple P2M DMA channels (default: no, 6010-only)");

अटल पूर्णांक desc_mode;
module_param(desc_mode, uपूर्णांक, 0644);
MODULE_PARM_DESC(desc_mode,
		 "Allow use of descriptor mode DMA (default: no, 6010-only)");

पूर्णांक solo_p2m_dma(काष्ठा solo_dev *solo_dev, पूर्णांक wr,
		 व्योम *sys_addr, u32 ext_addr, u32 size,
		 पूर्णांक repeat, u32 ext_size)
अणु
	dma_addr_t dma_addr;
	पूर्णांक ret;

	अगर (WARN_ON_ONCE((अचिन्हित दीर्घ)sys_addr & 0x03))
		वापस -EINVAL;
	अगर (WARN_ON_ONCE(!size))
		वापस -EINVAL;

	dma_addr = dma_map_single(&solo_dev->pdev->dev, sys_addr, size,
				  wr ? DMA_TO_DEVICE : DMA_FROM_DEVICE);
	अगर (dma_mapping_error(&solo_dev->pdev->dev, dma_addr))
		वापस -ENOMEM;

	ret = solo_p2m_dma_t(solo_dev, wr, dma_addr, ext_addr, size,
			     repeat, ext_size);

	dma_unmap_single(&solo_dev->pdev->dev, dma_addr, size,
			 wr ? DMA_TO_DEVICE : DMA_FROM_DEVICE);

	वापस ret;
पूर्ण

/* Mutex must be held क्रम p2m_id beक्रमe calling this!! */
पूर्णांक solo_p2m_dma_desc(काष्ठा solo_dev *solo_dev,
		      काष्ठा solo_p2m_desc *desc, dma_addr_t desc_dma,
		      पूर्णांक desc_cnt)
अणु
	काष्ठा solo_p2m_dev *p2m_dev;
	अचिन्हित पूर्णांक समयout;
	अचिन्हित पूर्णांक config = 0;
	पूर्णांक ret = 0;
	अचिन्हित पूर्णांक p2m_id = 0;

	/* Get next ID. According to Softlogic, 6110 has problems on !=0 P2M */
	अगर (solo_dev->type != SOLO_DEV_6110 && multi_p2m)
		p2m_id = atomic_inc_वापस(&solo_dev->p2m_count) % SOLO_NR_P2M;

	p2m_dev = &solo_dev->p2m_dev[p2m_id];

	अगर (mutex_lock_पूर्णांकerruptible(&p2m_dev->mutex))
		वापस -EINTR;

	reinit_completion(&p2m_dev->completion);
	p2m_dev->error = 0;

	अगर (desc_cnt > 1 && solo_dev->type != SOLO_DEV_6110 && desc_mode) अणु
		/* For 6010 with more than one desc, we can करो a one-shot */
		p2m_dev->desc_count = p2m_dev->desc_idx = 0;
		config = solo_reg_पढ़ो(solo_dev, SOLO_P2M_CONFIG(p2m_id));

		solo_reg_ग_लिखो(solo_dev, SOLO_P2M_DES_ADR(p2m_id), desc_dma);
		solo_reg_ग_लिखो(solo_dev, SOLO_P2M_DESC_ID(p2m_id), desc_cnt);
		solo_reg_ग_लिखो(solo_dev, SOLO_P2M_CONFIG(p2m_id), config |
			       SOLO_P2M_DESC_MODE);
	पूर्ण अन्यथा अणु
		/* For single descriptors and 6110, we need to run each desc */
		p2m_dev->desc_count = desc_cnt;
		p2m_dev->desc_idx = 1;
		p2m_dev->descs = desc;

		solo_reg_ग_लिखो(solo_dev, SOLO_P2M_TAR_ADR(p2m_id),
			       desc[1].dma_addr);
		solo_reg_ग_लिखो(solo_dev, SOLO_P2M_EXT_ADR(p2m_id),
			       desc[1].ext_addr);
		solo_reg_ग_लिखो(solo_dev, SOLO_P2M_EXT_CFG(p2m_id),
			       desc[1].cfg);
		solo_reg_ग_लिखो(solo_dev, SOLO_P2M_CONTROL(p2m_id),
			       desc[1].ctrl);
	पूर्ण

	समयout = रुको_क्रम_completion_समयout(&p2m_dev->completion,
					      solo_dev->p2m_jअगरfies);

	अगर (WARN_ON_ONCE(p2m_dev->error))
		ret = -EIO;
	अन्यथा अगर (समयout == 0) अणु
		solo_dev->p2m_समयouts++;
		ret = -EAGAIN;
	पूर्ण

	solo_reg_ग_लिखो(solo_dev, SOLO_P2M_CONTROL(p2m_id), 0);

	/* Don't ग_लिखो here क्रम the no_desc_mode हाल, because config is 0.
	 * We can't test no_desc_mode again, it might race. */
	अगर (desc_cnt > 1 && solo_dev->type != SOLO_DEV_6110 && config)
		solo_reg_ग_लिखो(solo_dev, SOLO_P2M_CONFIG(p2m_id), config);

	mutex_unlock(&p2m_dev->mutex);

	वापस ret;
पूर्ण

व्योम solo_p2m_fill_desc(काष्ठा solo_p2m_desc *desc, पूर्णांक wr,
			dma_addr_t dma_addr, u32 ext_addr, u32 size,
			पूर्णांक repeat, u32 ext_size)
अणु
	WARN_ON_ONCE(dma_addr & 0x03);
	WARN_ON_ONCE(!size);

	desc->cfg = SOLO_P2M_COPY_SIZE(size >> 2);
	desc->ctrl = SOLO_P2M_BURST_SIZE(SOLO_P2M_BURST_256) |
		(wr ? SOLO_P2M_WRITE : 0) | SOLO_P2M_TRANS_ON;

	अगर (repeat) अणु
		desc->cfg |= SOLO_P2M_EXT_INC(ext_size >> 2);
		desc->ctrl |=  SOLO_P2M_PCI_INC(size >> 2) |
			 SOLO_P2M_REPEAT(repeat);
	पूर्ण

	desc->dma_addr = dma_addr;
	desc->ext_addr = ext_addr;
पूर्ण

पूर्णांक solo_p2m_dma_t(काष्ठा solo_dev *solo_dev, पूर्णांक wr,
		   dma_addr_t dma_addr, u32 ext_addr, u32 size,
		   पूर्णांक repeat, u32 ext_size)
अणु
	काष्ठा solo_p2m_desc desc[2];

	solo_p2m_fill_desc(&desc[1], wr, dma_addr, ext_addr, size, repeat,
			   ext_size);

	/* No need क्रम desc_dma since we know it is a single-shot */
	वापस solo_p2m_dma_desc(solo_dev, desc, 0, 1);
पूर्ण

व्योम solo_p2m_isr(काष्ठा solo_dev *solo_dev, पूर्णांक id)
अणु
	काष्ठा solo_p2m_dev *p2m_dev = &solo_dev->p2m_dev[id];
	काष्ठा solo_p2m_desc *desc;

	अगर (p2m_dev->desc_count <= p2m_dev->desc_idx) अणु
		complete(&p2m_dev->completion);
		वापस;
	पूर्ण

	/* Setup next descriptor */
	p2m_dev->desc_idx++;
	desc = &p2m_dev->descs[p2m_dev->desc_idx];

	solo_reg_ग_लिखो(solo_dev, SOLO_P2M_CONTROL(id), 0);
	solo_reg_ग_लिखो(solo_dev, SOLO_P2M_TAR_ADR(id), desc->dma_addr);
	solo_reg_ग_लिखो(solo_dev, SOLO_P2M_EXT_ADR(id), desc->ext_addr);
	solo_reg_ग_लिखो(solo_dev, SOLO_P2M_EXT_CFG(id), desc->cfg);
	solo_reg_ग_लिखो(solo_dev, SOLO_P2M_CONTROL(id), desc->ctrl);
पूर्ण

व्योम solo_p2m_error_isr(काष्ठा solo_dev *solo_dev)
अणु
	अचिन्हित पूर्णांक err = solo_reg_पढ़ो(solo_dev, SOLO_PCI_ERR);
	काष्ठा solo_p2m_dev *p2m_dev;
	पूर्णांक i;

	अगर (!(err & (SOLO_PCI_ERR_P2M | SOLO_PCI_ERR_P2M_DESC)))
		वापस;

	क्रम (i = 0; i < SOLO_NR_P2M; i++) अणु
		p2m_dev = &solo_dev->p2m_dev[i];
		p2m_dev->error = 1;
		solo_reg_ग_लिखो(solo_dev, SOLO_P2M_CONTROL(i), 0);
		complete(&p2m_dev->completion);
	पूर्ण
पूर्ण

व्योम solo_p2m_निकास(काष्ठा solo_dev *solo_dev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < SOLO_NR_P2M; i++)
		solo_irq_off(solo_dev, SOLO_IRQ_P2M(i));
पूर्ण

अटल पूर्णांक solo_p2m_test(काष्ठा solo_dev *solo_dev, पूर्णांक base, पूर्णांक size)
अणु
	u32 *wr_buf;
	u32 *rd_buf;
	पूर्णांक i;
	पूर्णांक ret = -EIO;
	पूर्णांक order = get_order(size);

	wr_buf = (u32 *)__get_मुक्त_pages(GFP_KERNEL, order);
	अगर (wr_buf == शून्य)
		वापस -1;

	rd_buf = (u32 *)__get_मुक्त_pages(GFP_KERNEL, order);
	अगर (rd_buf == शून्य) अणु
		मुक्त_pages((अचिन्हित दीर्घ)wr_buf, order);
		वापस -1;
	पूर्ण

	क्रम (i = 0; i < (size >> 3); i++)
		*(wr_buf + i) = (i << 16) | (i + 1);

	क्रम (i = (size >> 3); i < (size >> 2); i++)
		*(wr_buf + i) = ~((i << 16) | (i + 1));

	स_रखो(rd_buf, 0x55, size);

	अगर (solo_p2m_dma(solo_dev, 1, wr_buf, base, size, 0, 0))
		जाओ test_fail;

	अगर (solo_p2m_dma(solo_dev, 0, rd_buf, base, size, 0, 0))
		जाओ test_fail;

	क्रम (i = 0; i < (size >> 2); i++) अणु
		अगर (*(wr_buf + i) != *(rd_buf + i))
			जाओ test_fail;
	पूर्ण

	ret = 0;

test_fail:
	मुक्त_pages((अचिन्हित दीर्घ)wr_buf, order);
	मुक्त_pages((अचिन्हित दीर्घ)rd_buf, order);

	वापस ret;
पूर्ण

पूर्णांक solo_p2m_init(काष्ठा solo_dev *solo_dev)
अणु
	काष्ठा solo_p2m_dev *p2m_dev;
	पूर्णांक i;

	क्रम (i = 0; i < SOLO_NR_P2M; i++) अणु
		p2m_dev = &solo_dev->p2m_dev[i];

		mutex_init(&p2m_dev->mutex);
		init_completion(&p2m_dev->completion);

		solo_reg_ग_लिखो(solo_dev, SOLO_P2M_CONTROL(i), 0);
		solo_reg_ग_लिखो(solo_dev, SOLO_P2M_CONFIG(i),
			       SOLO_P2M_CSC_16BIT_565 |
			       SOLO_P2M_DESC_INTR_OPT |
			       SOLO_P2M_DMA_INTERVAL(0) |
			       SOLO_P2M_PCI_MASTER_MODE);
		solo_irq_on(solo_dev, SOLO_IRQ_P2M(i));
	पूर्ण

	/* Find correct SDRAM size */
	क्रम (solo_dev->sdram_size = 0, i = 2; i >= 0; i--) अणु
		solo_reg_ग_लिखो(solo_dev, SOLO_DMA_CTRL,
			       SOLO_DMA_CTRL_REFRESH_CYCLE(1) |
			       SOLO_DMA_CTRL_SDRAM_SIZE(i) |
			       SOLO_DMA_CTRL_SDRAM_CLK_INVERT |
			       SOLO_DMA_CTRL_READ_CLK_SELECT |
			       SOLO_DMA_CTRL_LATENCY(1));

		solo_reg_ग_लिखो(solo_dev, SOLO_SYS_CFG, solo_dev->sys_config |
			       SOLO_SYS_CFG_RESET);
		solo_reg_ग_लिखो(solo_dev, SOLO_SYS_CFG, solo_dev->sys_config);

		चयन (i) अणु
		हाल 2:
			अगर (solo_p2m_test(solo_dev, 0x07ff0000, 0x00010000) ||
			    solo_p2m_test(solo_dev, 0x05ff0000, 0x00010000))
				जारी;
			अवरोध;

		हाल 1:
			अगर (solo_p2m_test(solo_dev, 0x03ff0000, 0x00010000))
				जारी;
			अवरोध;

		शेष:
			अगर (solo_p2m_test(solo_dev, 0x01ff0000, 0x00010000))
				जारी;
		पूर्ण

		solo_dev->sdram_size = (32 << 20) << i;
		अवरोध;
	पूर्ण

	अगर (!solo_dev->sdram_size) अणु
		dev_err(&solo_dev->pdev->dev, "Error detecting SDRAM size\n");
		वापस -EIO;
	पूर्ण

	अगर (SOLO_SDRAM_END(solo_dev) > solo_dev->sdram_size) अणु
		dev_err(&solo_dev->pdev->dev,
			"SDRAM is not large enough (%u < %u)\n",
			solo_dev->sdram_size, SOLO_SDRAM_END(solo_dev));
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण
