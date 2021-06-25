<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2011-2015 Xilinx Inc.
 * Copyright (c) 2015, National Instruments Corp.
 *
 * FPGA Manager Driver क्रम Xilinx Zynq, heavily based on xdevcfg driver
 * in their venकरोr tree.
 */

#समावेश <linux/clk.h>
#समावेश <linux/completion.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/fpga/fpga-mgr.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/module.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/pm.h>
#समावेश <linux/regmap.h>
#समावेश <linux/माला.स>
#समावेश <linux/scatterlist.h>

/* Offsets पूर्णांकo SLCR regmap */

/* FPGA Software Reset Control */
#घोषणा SLCR_FPGA_RST_CTRL_OFFSET	0x240
/* Level Shअगरters Enable */
#घोषणा SLCR_LVL_SHFTR_EN_OFFSET	0x900

/* Constant Definitions */

/* Control Register */
#घोषणा CTRL_OFFSET			0x00
/* Lock Register */
#घोषणा LOCK_OFFSET			0x04
/* Interrupt Status Register */
#घोषणा INT_STS_OFFSET			0x0c
/* Interrupt Mask Register */
#घोषणा INT_MASK_OFFSET			0x10
/* Status Register */
#घोषणा STATUS_OFFSET			0x14
/* DMA Source Address Register */
#घोषणा DMA_SRC_ADDR_OFFSET		0x18
/* DMA Destination Address Reg */
#घोषणा DMA_DST_ADDR_OFFSET		0x1c
/* DMA Source Transfer Length */
#घोषणा DMA_SRC_LEN_OFFSET		0x20
/* DMA Destination Transfer */
#घोषणा DMA_DEST_LEN_OFFSET		0x24
/* Unlock Register */
#घोषणा UNLOCK_OFFSET			0x34
/* Misc. Control Register */
#घोषणा MCTRL_OFFSET			0x80

/* Control Register Bit definitions */

/* Signal to reset FPGA */
#घोषणा CTRL_PCFG_PROG_B_MASK		BIT(30)
/* Enable PCAP क्रम PR */
#घोषणा CTRL_PCAP_PR_MASK		BIT(27)
/* Enable PCAP */
#घोषणा CTRL_PCAP_MODE_MASK		BIT(26)
/* Lower rate to allow decrypt on the fly */
#घोषणा CTRL_PCAP_RATE_EN_MASK		BIT(25)
/* System booted in secure mode */
#घोषणा CTRL_SEC_EN_MASK		BIT(7)

/* Miscellaneous Control Register bit definitions */
/* Internal PCAP loopback */
#घोषणा MCTRL_PCAP_LPBK_MASK		BIT(4)

/* Status रेजिस्टर bit definitions */

/* FPGA init status */
#घोषणा STATUS_DMA_Q_F			BIT(31)
#घोषणा STATUS_DMA_Q_E			BIT(30)
#घोषणा STATUS_PCFG_INIT_MASK		BIT(4)

/* Interrupt Status/Mask Register Bit definitions */
/* DMA command करोne */
#घोषणा IXR_DMA_DONE_MASK		BIT(13)
/* DMA and PCAP cmd करोne */
#घोषणा IXR_D_P_DONE_MASK		BIT(12)
 /* FPGA programmed */
#घोषणा IXR_PCFG_DONE_MASK		BIT(2)
#घोषणा IXR_ERROR_FLAGS_MASK		0x00F0C860
#घोषणा IXR_ALL_MASK			0xF8F7F87F

/* Miscellaneous स्थिरant values */

/* Invalid DMA addr */
#घोषणा DMA_INVALID_ADDRESS		GENMASK(31, 0)
/* Used to unlock the dev */
#घोषणा UNLOCK_MASK			0x757bdf0d
/* Timeout क्रम polling reset bits */
#घोषणा INIT_POLL_TIMEOUT		2500000
/* Delay क्रम polling reset bits */
#घोषणा INIT_POLL_DELAY			20
/* Signal this is the last DMA transfer, रुको क्रम the AXI and PCAP beक्रमe
 * पूर्णांकerrupting
 */
#घोषणा DMA_SRC_LAST_TRANSFER		1
/* Timeout क्रम DMA completion */
#घोषणा DMA_TIMEOUT_MS			5000

/* Masks क्रम controlling stuff in SLCR */
/* Disable all Level shअगरters */
#घोषणा LVL_SHFTR_DISABLE_ALL_MASK	0x0
/* Enable Level shअगरters from PS to PL */
#घोषणा LVL_SHFTR_ENABLE_PS_TO_PL	0xa
/* Enable Level shअगरters from PL to PS */
#घोषणा LVL_SHFTR_ENABLE_PL_TO_PS	0xf
/* Enable global resets */
#घोषणा FPGA_RST_ALL_MASK		0xf
/* Disable global resets */
#घोषणा FPGA_RST_NONE_MASK		0x0

काष्ठा zynq_fpga_priv अणु
	पूर्णांक irq;
	काष्ठा clk *clk;

	व्योम __iomem *io_base;
	काष्ठा regmap *slcr;

	spinlock_t dma_lock;
	अचिन्हित पूर्णांक dma_elm;
	अचिन्हित पूर्णांक dma_nelms;
	काष्ठा scatterlist *cur_sg;

	काष्ठा completion dma_करोne;
पूर्ण;

अटल अंतरभूत व्योम zynq_fpga_ग_लिखो(काष्ठा zynq_fpga_priv *priv, u32 offset,
				   u32 val)
अणु
	ग_लिखोl(val, priv->io_base + offset);
पूर्ण

अटल अंतरभूत u32 zynq_fpga_पढ़ो(स्थिर काष्ठा zynq_fpga_priv *priv,
				 u32 offset)
अणु
	वापस पढ़ोl(priv->io_base + offset);
पूर्ण

#घोषणा zynq_fpga_poll_समयout(priv, addr, val, cond, sleep_us, समयout_us) \
	पढ़ोl_poll_समयout(priv->io_base + addr, val, cond, sleep_us, \
			   समयout_us)

/* Cause the specअगरied irq mask bits to generate IRQs */
अटल अंतरभूत व्योम zynq_fpga_set_irq(काष्ठा zynq_fpga_priv *priv, u32 enable)
अणु
	zynq_fpga_ग_लिखो(priv, INT_MASK_OFFSET, ~enable);
पूर्ण

/* Must be called with dma_lock held */
अटल व्योम zynq_step_dma(काष्ठा zynq_fpga_priv *priv)
अणु
	u32 addr;
	u32 len;
	bool first;

	first = priv->dma_elm == 0;
	जबतक (priv->cur_sg) अणु
		/* Feed the DMA queue until it is full. */
		अगर (zynq_fpga_पढ़ो(priv, STATUS_OFFSET) & STATUS_DMA_Q_F)
			अवरोध;

		addr = sg_dma_address(priv->cur_sg);
		len = sg_dma_len(priv->cur_sg);
		अगर (priv->dma_elm + 1 == priv->dma_nelms) अणु
			/* The last transfer रुकोs क्रम the PCAP to finish too,
			 * notice this also changes the irq_mask to ignore
			 * IXR_DMA_DONE_MASK which ensures we करो not trigger
			 * the completion too early.
			 */
			addr |= DMA_SRC_LAST_TRANSFER;
			priv->cur_sg = शून्य;
		पूर्ण अन्यथा अणु
			priv->cur_sg = sg_next(priv->cur_sg);
			priv->dma_elm++;
		पूर्ण

		zynq_fpga_ग_लिखो(priv, DMA_SRC_ADDR_OFFSET, addr);
		zynq_fpga_ग_लिखो(priv, DMA_DST_ADDR_OFFSET, DMA_INVALID_ADDRESS);
		zynq_fpga_ग_लिखो(priv, DMA_SRC_LEN_OFFSET, len / 4);
		zynq_fpga_ग_लिखो(priv, DMA_DEST_LEN_OFFSET, 0);
	पूर्ण

	/* Once the first transfer is queued we can turn on the ISR, future
	 * calls to zynq_step_dma will happen from the ISR context. The
	 * dma_lock spinlock guarentees this hanकरोver is करोne coherently, the
	 * ISR enable is put at the end to aव्योम another CPU spinning in the
	 * ISR on this lock.
	 */
	अगर (first && priv->cur_sg) अणु
		zynq_fpga_set_irq(priv,
				  IXR_DMA_DONE_MASK | IXR_ERROR_FLAGS_MASK);
	पूर्ण अन्यथा अगर (!priv->cur_sg) अणु
		/* The last transfer changes to DMA & PCAP mode since we करो
		 * not want to जारी until everything has been flushed पूर्णांकo
		 * the PCAP.
		 */
		zynq_fpga_set_irq(priv,
				  IXR_D_P_DONE_MASK | IXR_ERROR_FLAGS_MASK);
	पूर्ण
पूर्ण

अटल irqवापस_t zynq_fpga_isr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा zynq_fpga_priv *priv = data;
	u32 पूर्णांकr_status;

	/* If anything other than DMA completion is reported stop and hand
	 * control back to zynq_fpga_ops_ग_लिखो, something went wrong,
	 * otherwise progress the DMA.
	 */
	spin_lock(&priv->dma_lock);
	पूर्णांकr_status = zynq_fpga_पढ़ो(priv, INT_STS_OFFSET);
	अगर (!(पूर्णांकr_status & IXR_ERROR_FLAGS_MASK) &&
	    (पूर्णांकr_status & IXR_DMA_DONE_MASK) && priv->cur_sg) अणु
		zynq_fpga_ग_लिखो(priv, INT_STS_OFFSET, IXR_DMA_DONE_MASK);
		zynq_step_dma(priv);
		spin_unlock(&priv->dma_lock);
		वापस IRQ_HANDLED;
	पूर्ण
	spin_unlock(&priv->dma_lock);

	zynq_fpga_set_irq(priv, 0);
	complete(&priv->dma_करोne);

	वापस IRQ_HANDLED;
पूर्ण

/* Sanity check the proposed bitstream. It must start with the sync word in
 * the correct byte order, and be dword aligned. The input is a Xilinx .bin
 * file with every 32 bit quantity swapped.
 */
अटल bool zynq_fpga_has_sync(स्थिर u8 *buf, माप_प्रकार count)
अणु
	क्रम (; count >= 4; buf += 4, count -= 4)
		अगर (buf[0] == 0x66 && buf[1] == 0x55 && buf[2] == 0x99 &&
		    buf[3] == 0xaa)
			वापस true;
	वापस false;
पूर्ण

अटल पूर्णांक zynq_fpga_ops_ग_लिखो_init(काष्ठा fpga_manager *mgr,
				    काष्ठा fpga_image_info *info,
				    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा zynq_fpga_priv *priv;
	u32 ctrl, status;
	पूर्णांक err;

	priv = mgr->priv;

	err = clk_enable(priv->clk);
	अगर (err)
		वापस err;

	/* check अगर bitstream is encrypted & and प्रणाली's still secure */
	अगर (info->flags & FPGA_MGR_ENCRYPTED_BITSTREAM) अणु
		ctrl = zynq_fpga_पढ़ो(priv, CTRL_OFFSET);
		अगर (!(ctrl & CTRL_SEC_EN_MASK)) अणु
			dev_err(&mgr->dev,
				"System not secure, can't use crypted bitstreams\n");
			err = -EINVAL;
			जाओ out_err;
		पूर्ण
	पूर्ण

	/* करोn't globally reset PL if we're करोing partial reconfig */
	अगर (!(info->flags & FPGA_MGR_PARTIAL_RECONFIG)) अणु
		अगर (!zynq_fpga_has_sync(buf, count)) अणु
			dev_err(&mgr->dev,
				"Invalid bitstream, could not find a sync word. Bitstream must be a byte swapped .bin file\n");
			err = -EINVAL;
			जाओ out_err;
		पूर्ण

		/* निश्चित AXI पूर्णांकerface resets */
		regmap_ग_लिखो(priv->slcr, SLCR_FPGA_RST_CTRL_OFFSET,
			     FPGA_RST_ALL_MASK);

		/* disable all level shअगरters */
		regmap_ग_लिखो(priv->slcr, SLCR_LVL_SHFTR_EN_OFFSET,
			     LVL_SHFTR_DISABLE_ALL_MASK);
		/* enable level shअगरters from PS to PL */
		regmap_ग_लिखो(priv->slcr, SLCR_LVL_SHFTR_EN_OFFSET,
			     LVL_SHFTR_ENABLE_PS_TO_PL);

		/* create a rising edge on PCFG_INIT. PCFG_INIT follows
		 * PCFG_PROG_B, so we need to poll it after setting PCFG_PROG_B
		 * to make sure the rising edge actually happens.
		 * Note: PCFG_PROG_B is low active, sequence as described in
		 * UG585 v1.10 page 211
		 */
		ctrl = zynq_fpga_पढ़ो(priv, CTRL_OFFSET);
		ctrl |= CTRL_PCFG_PROG_B_MASK;

		zynq_fpga_ग_लिखो(priv, CTRL_OFFSET, ctrl);

		err = zynq_fpga_poll_समयout(priv, STATUS_OFFSET, status,
					     status & STATUS_PCFG_INIT_MASK,
					     INIT_POLL_DELAY,
					     INIT_POLL_TIMEOUT);
		अगर (err) अणु
			dev_err(&mgr->dev, "Timeout waiting for PCFG_INIT\n");
			जाओ out_err;
		पूर्ण

		ctrl = zynq_fpga_पढ़ो(priv, CTRL_OFFSET);
		ctrl &= ~CTRL_PCFG_PROG_B_MASK;

		zynq_fpga_ग_लिखो(priv, CTRL_OFFSET, ctrl);

		err = zynq_fpga_poll_समयout(priv, STATUS_OFFSET, status,
					     !(status & STATUS_PCFG_INIT_MASK),
					     INIT_POLL_DELAY,
					     INIT_POLL_TIMEOUT);
		अगर (err) अणु
			dev_err(&mgr->dev, "Timeout waiting for !PCFG_INIT\n");
			जाओ out_err;
		पूर्ण

		ctrl = zynq_fpga_पढ़ो(priv, CTRL_OFFSET);
		ctrl |= CTRL_PCFG_PROG_B_MASK;

		zynq_fpga_ग_लिखो(priv, CTRL_OFFSET, ctrl);

		err = zynq_fpga_poll_समयout(priv, STATUS_OFFSET, status,
					     status & STATUS_PCFG_INIT_MASK,
					     INIT_POLL_DELAY,
					     INIT_POLL_TIMEOUT);
		अगर (err) अणु
			dev_err(&mgr->dev, "Timeout waiting for PCFG_INIT\n");
			जाओ out_err;
		पूर्ण
	पूर्ण

	/* set configuration रेजिस्टर with following options:
	 * - enable PCAP पूर्णांकerface
	 * - set throughput क्रम maximum speed (अगर bistream not crypted)
	 * - set CPU in user mode
	 */
	ctrl = zynq_fpga_पढ़ो(priv, CTRL_OFFSET);
	अगर (info->flags & FPGA_MGR_ENCRYPTED_BITSTREAM)
		zynq_fpga_ग_लिखो(priv, CTRL_OFFSET,
				(CTRL_PCAP_PR_MASK | CTRL_PCAP_MODE_MASK
				 | CTRL_PCAP_RATE_EN_MASK | ctrl));
	अन्यथा
		zynq_fpga_ग_लिखो(priv, CTRL_OFFSET,
				(CTRL_PCAP_PR_MASK | CTRL_PCAP_MODE_MASK
				 | ctrl));


	/* We expect that the command queue is empty right now. */
	status = zynq_fpga_पढ़ो(priv, STATUS_OFFSET);
	अगर ((status & STATUS_DMA_Q_F) ||
	    (status & STATUS_DMA_Q_E) != STATUS_DMA_Q_E) अणु
		dev_err(&mgr->dev, "DMA command queue not right\n");
		err = -EBUSY;
		जाओ out_err;
	पूर्ण

	/* ensure पूर्णांकernal PCAP loopback is disabled */
	ctrl = zynq_fpga_पढ़ो(priv, MCTRL_OFFSET);
	zynq_fpga_ग_लिखो(priv, MCTRL_OFFSET, (~MCTRL_PCAP_LPBK_MASK & ctrl));

	clk_disable(priv->clk);

	वापस 0;

out_err:
	clk_disable(priv->clk);

	वापस err;
पूर्ण

अटल पूर्णांक zynq_fpga_ops_ग_लिखो(काष्ठा fpga_manager *mgr, काष्ठा sg_table *sgt)
अणु
	काष्ठा zynq_fpga_priv *priv;
	स्थिर अक्षर *why;
	पूर्णांक err;
	u32 पूर्णांकr_status;
	अचिन्हित दीर्घ समयout;
	अचिन्हित दीर्घ flags;
	काष्ठा scatterlist *sg;
	पूर्णांक i;

	priv = mgr->priv;

	/* The hardware can only DMA multiples of 4 bytes, and it requires the
	 * starting addresses to be aligned to 64 bits (UG585 pg 212).
	 */
	क्रम_each_sg(sgt->sgl, sg, sgt->nents, i) अणु
		अगर ((sg->offset % 8) || (sg->length % 4)) अणु
			dev_err(&mgr->dev,
			    "Invalid bitstream, chunks must be aligned\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	priv->dma_nelms =
	    dma_map_sg(mgr->dev.parent, sgt->sgl, sgt->nents, DMA_TO_DEVICE);
	अगर (priv->dma_nelms == 0) अणु
		dev_err(&mgr->dev, "Unable to DMA map (TO_DEVICE)\n");
		वापस -ENOMEM;
	पूर्ण

	/* enable घड़ी */
	err = clk_enable(priv->clk);
	अगर (err)
		जाओ out_मुक्त;

	zynq_fpga_ग_लिखो(priv, INT_STS_OFFSET, IXR_ALL_MASK);
	reinit_completion(&priv->dma_करोne);

	/* zynq_step_dma will turn on पूर्णांकerrupts */
	spin_lock_irqsave(&priv->dma_lock, flags);
	priv->dma_elm = 0;
	priv->cur_sg = sgt->sgl;
	zynq_step_dma(priv);
	spin_unlock_irqrestore(&priv->dma_lock, flags);

	समयout = रुको_क्रम_completion_समयout(&priv->dma_करोne,
					      msecs_to_jअगरfies(DMA_TIMEOUT_MS));

	spin_lock_irqsave(&priv->dma_lock, flags);
	zynq_fpga_set_irq(priv, 0);
	priv->cur_sg = शून्य;
	spin_unlock_irqrestore(&priv->dma_lock, flags);

	पूर्णांकr_status = zynq_fpga_पढ़ो(priv, INT_STS_OFFSET);
	zynq_fpga_ग_लिखो(priv, INT_STS_OFFSET, IXR_ALL_MASK);

	/* There करोesn't seem to be a way to क्रमce cancel any DMA, so अगर
	 * something went wrong we are relying on the hardware to have halted
	 * the DMA beक्रमe we get here, अगर there was we could use
	 * रुको_क्रम_completion_पूर्णांकerruptible too.
	 */

	अगर (पूर्णांकr_status & IXR_ERROR_FLAGS_MASK) अणु
		why = "DMA reported error";
		err = -EIO;
		जाओ out_report;
	पूर्ण

	अगर (priv->cur_sg ||
	    !((पूर्णांकr_status & IXR_D_P_DONE_MASK) == IXR_D_P_DONE_MASK)) अणु
		अगर (समयout == 0)
			why = "DMA timed out";
		अन्यथा
			why = "DMA did not complete";
		err = -EIO;
		जाओ out_report;
	पूर्ण

	err = 0;
	जाओ out_clk;

out_report:
	dev_err(&mgr->dev,
		"%s: INT_STS:0x%x CTRL:0x%x LOCK:0x%x INT_MASK:0x%x STATUS:0x%x MCTRL:0x%x\n",
		why,
		पूर्णांकr_status,
		zynq_fpga_पढ़ो(priv, CTRL_OFFSET),
		zynq_fpga_पढ़ो(priv, LOCK_OFFSET),
		zynq_fpga_पढ़ो(priv, INT_MASK_OFFSET),
		zynq_fpga_पढ़ो(priv, STATUS_OFFSET),
		zynq_fpga_पढ़ो(priv, MCTRL_OFFSET));

out_clk:
	clk_disable(priv->clk);

out_मुक्त:
	dma_unmap_sg(mgr->dev.parent, sgt->sgl, sgt->nents, DMA_TO_DEVICE);
	वापस err;
पूर्ण

अटल पूर्णांक zynq_fpga_ops_ग_लिखो_complete(काष्ठा fpga_manager *mgr,
					काष्ठा fpga_image_info *info)
अणु
	काष्ठा zynq_fpga_priv *priv = mgr->priv;
	पूर्णांक err;
	u32 पूर्णांकr_status;

	err = clk_enable(priv->clk);
	अगर (err)
		वापस err;

	/* Release 'PR' control back to the ICAP */
	zynq_fpga_ग_लिखो(priv, CTRL_OFFSET,
		zynq_fpga_पढ़ो(priv, CTRL_OFFSET) & ~CTRL_PCAP_PR_MASK);

	err = zynq_fpga_poll_समयout(priv, INT_STS_OFFSET, पूर्णांकr_status,
				     पूर्णांकr_status & IXR_PCFG_DONE_MASK,
				     INIT_POLL_DELAY,
				     INIT_POLL_TIMEOUT);

	clk_disable(priv->clk);

	अगर (err)
		वापस err;

	/* क्रम the partial reconfig हाल we didn't touch the level shअगरters */
	अगर (!(info->flags & FPGA_MGR_PARTIAL_RECONFIG)) अणु
		/* enable level shअगरters from PL to PS */
		regmap_ग_लिखो(priv->slcr, SLCR_LVL_SHFTR_EN_OFFSET,
			     LVL_SHFTR_ENABLE_PL_TO_PS);

		/* deनिश्चित AXI पूर्णांकerface resets */
		regmap_ग_लिखो(priv->slcr, SLCR_FPGA_RST_CTRL_OFFSET,
			     FPGA_RST_NONE_MASK);
	पूर्ण

	वापस 0;
पूर्ण

अटल क्रमागत fpga_mgr_states zynq_fpga_ops_state(काष्ठा fpga_manager *mgr)
अणु
	पूर्णांक err;
	u32 पूर्णांकr_status;
	काष्ठा zynq_fpga_priv *priv;

	priv = mgr->priv;

	err = clk_enable(priv->clk);
	अगर (err)
		वापस FPGA_MGR_STATE_UNKNOWN;

	पूर्णांकr_status = zynq_fpga_पढ़ो(priv, INT_STS_OFFSET);
	clk_disable(priv->clk);

	अगर (पूर्णांकr_status & IXR_PCFG_DONE_MASK)
		वापस FPGA_MGR_STATE_OPERATING;

	वापस FPGA_MGR_STATE_UNKNOWN;
पूर्ण

अटल स्थिर काष्ठा fpga_manager_ops zynq_fpga_ops = अणु
	.initial_header_size = 128,
	.state = zynq_fpga_ops_state,
	.ग_लिखो_init = zynq_fpga_ops_ग_लिखो_init,
	.ग_लिखो_sg = zynq_fpga_ops_ग_लिखो,
	.ग_लिखो_complete = zynq_fpga_ops_ग_लिखो_complete,
पूर्ण;

अटल पूर्णांक zynq_fpga_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा zynq_fpga_priv *priv;
	काष्ठा fpga_manager *mgr;
	काष्ठा resource *res;
	पूर्णांक err;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;
	spin_lock_init(&priv->dma_lock);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	priv->io_base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(priv->io_base))
		वापस PTR_ERR(priv->io_base);

	priv->slcr = syscon_regmap_lookup_by_phandle(dev->of_node,
		"syscon");
	अगर (IS_ERR(priv->slcr)) अणु
		dev_err(dev, "unable to get zynq-slcr regmap\n");
		वापस PTR_ERR(priv->slcr);
	पूर्ण

	init_completion(&priv->dma_करोne);

	priv->irq = platक्रमm_get_irq(pdev, 0);
	अगर (priv->irq < 0)
		वापस priv->irq;

	priv->clk = devm_clk_get(dev, "ref_clk");
	अगर (IS_ERR(priv->clk)) अणु
		अगर (PTR_ERR(priv->clk) != -EPROBE_DEFER)
			dev_err(dev, "input clock not found\n");
		वापस PTR_ERR(priv->clk);
	पूर्ण

	err = clk_prepare_enable(priv->clk);
	अगर (err) अणु
		dev_err(dev, "unable to enable clock\n");
		वापस err;
	पूर्ण

	/* unlock the device */
	zynq_fpga_ग_लिखो(priv, UNLOCK_OFFSET, UNLOCK_MASK);

	zynq_fpga_set_irq(priv, 0);
	zynq_fpga_ग_लिखो(priv, INT_STS_OFFSET, IXR_ALL_MASK);
	err = devm_request_irq(dev, priv->irq, zynq_fpga_isr, 0, dev_name(dev),
			       priv);
	अगर (err) अणु
		dev_err(dev, "unable to request IRQ\n");
		clk_disable_unprepare(priv->clk);
		वापस err;
	पूर्ण

	clk_disable(priv->clk);

	mgr = devm_fpga_mgr_create(dev, "Xilinx Zynq FPGA Manager",
				   &zynq_fpga_ops, priv);
	अगर (!mgr)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, mgr);

	err = fpga_mgr_रेजिस्टर(mgr);
	अगर (err) अणु
		dev_err(dev, "unable to register FPGA manager\n");
		clk_unprepare(priv->clk);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक zynq_fpga_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा zynq_fpga_priv *priv;
	काष्ठा fpga_manager *mgr;

	mgr = platक्रमm_get_drvdata(pdev);
	priv = mgr->priv;

	fpga_mgr_unरेजिस्टर(mgr);

	clk_unprepare(priv->clk);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id zynq_fpga_of_match[] = अणु
	अणु .compatible = "xlnx,zynq-devcfg-1.0", पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, zynq_fpga_of_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver zynq_fpga_driver = अणु
	.probe = zynq_fpga_probe,
	.हटाओ = zynq_fpga_हटाओ,
	.driver = अणु
		.name = "zynq_fpga_manager",
		.of_match_table = of_match_ptr(zynq_fpga_of_match),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(zynq_fpga_driver);

MODULE_AUTHOR("Moritz Fischer <moritz.fischer@ettus.com>");
MODULE_AUTHOR("Michal Simek <michal.simek@xilinx.com>");
MODULE_DESCRIPTION("Xilinx Zynq FPGA Manager");
MODULE_LICENSE("GPL v2");
