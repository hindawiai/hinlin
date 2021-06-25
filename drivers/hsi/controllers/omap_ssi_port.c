<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* OMAP SSI port driver.
 *
 * Copyright (C) 2010 Nokia Corporation. All rights reserved.
 * Copyright (C) 2014 Sebastian Reichel <sre@kernel.org>
 *
 * Contact: Carlos Chinea <carlos.chinea@nokia.com>
 */

#समावेश <linux/mod_devicetable.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/delay.h>

#समावेश <linux/gpio/consumer.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/debugfs.h>

#समावेश "omap_ssi_regs.h"
#समावेश "omap_ssi.h"

अटल अंतरभूत पूर्णांक hsi_dummy_msg(काष्ठा hsi_msg *msg __maybe_unused)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक hsi_dummy_cl(काष्ठा hsi_client *cl __maybe_unused)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक ssi_wakein(काष्ठा hsi_port *port)
अणु
	काष्ठा omap_ssi_port *omap_port = hsi_port_drvdata(port);
	वापस gpiod_get_value(omap_port->wake_gpio);
पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
अटल व्योम ssi_debug_हटाओ_port(काष्ठा hsi_port *port)
अणु
	काष्ठा omap_ssi_port *omap_port = hsi_port_drvdata(port);

	debugfs_हटाओ_recursive(omap_port->dir);
पूर्ण

अटल पूर्णांक ssi_port_regs_show(काष्ठा seq_file *m, व्योम *p __maybe_unused)
अणु
	काष्ठा hsi_port *port = m->निजी;
	काष्ठा omap_ssi_port *omap_port = hsi_port_drvdata(port);
	काष्ठा hsi_controller *ssi = to_hsi_controller(port->device.parent);
	काष्ठा omap_ssi_controller *omap_ssi = hsi_controller_drvdata(ssi);
	व्योम __iomem	*base = omap_ssi->sys;
	अचिन्हित पूर्णांक ch;

	pm_runसमय_get_sync(omap_port->pdev);
	अगर (omap_port->wake_irq > 0)
		seq_म_लिखो(m, "CAWAKE\t\t: %d\n", ssi_wakein(port));
	seq_म_लिखो(m, "WAKE\t\t: 0x%08x\n",
				पढ़ोl(base + SSI_WAKE_REG(port->num)));
	seq_म_लिखो(m, "MPU_ENABLE_IRQ%d\t: 0x%08x\n", 0,
			पढ़ोl(base + SSI_MPU_ENABLE_REG(port->num, 0)));
	seq_म_लिखो(m, "MPU_STATUS_IRQ%d\t: 0x%08x\n", 0,
			पढ़ोl(base + SSI_MPU_STATUS_REG(port->num, 0)));
	/* SST */
	base = omap_port->sst_base;
	seq_माला_दो(m, "\nSST\n===\n");
	seq_म_लिखो(m, "ID SST\t\t: 0x%08x\n",
				पढ़ोl(base + SSI_SST_ID_REG));
	seq_म_लिखो(m, "MODE\t\t: 0x%08x\n",
				पढ़ोl(base + SSI_SST_MODE_REG));
	seq_म_लिखो(m, "FRAMESIZE\t: 0x%08x\n",
				पढ़ोl(base + SSI_SST_FRAMESIZE_REG));
	seq_म_लिखो(m, "DIVISOR\t\t: 0x%08x\n",
				पढ़ोl(base + SSI_SST_DIVISOR_REG));
	seq_म_लिखो(m, "CHANNELS\t: 0x%08x\n",
				पढ़ोl(base + SSI_SST_CHANNELS_REG));
	seq_म_लिखो(m, "ARBMODE\t\t: 0x%08x\n",
				पढ़ोl(base + SSI_SST_ARBMODE_REG));
	seq_म_लिखो(m, "TXSTATE\t\t: 0x%08x\n",
				पढ़ोl(base + SSI_SST_TXSTATE_REG));
	seq_म_लिखो(m, "BUFSTATE\t: 0x%08x\n",
				पढ़ोl(base + SSI_SST_BUFSTATE_REG));
	seq_म_लिखो(m, "BREAK\t\t: 0x%08x\n",
				पढ़ोl(base + SSI_SST_BREAK_REG));
	क्रम (ch = 0; ch < omap_port->channels; ch++) अणु
		seq_म_लिखो(m, "BUFFER_CH%d\t: 0x%08x\n", ch,
				पढ़ोl(base + SSI_SST_BUFFER_CH_REG(ch)));
	पूर्ण
	/* SSR */
	base = omap_port->ssr_base;
	seq_माला_दो(m, "\nSSR\n===\n");
	seq_म_लिखो(m, "ID SSR\t\t: 0x%08x\n",
				पढ़ोl(base + SSI_SSR_ID_REG));
	seq_म_लिखो(m, "MODE\t\t: 0x%08x\n",
				पढ़ोl(base + SSI_SSR_MODE_REG));
	seq_म_लिखो(m, "FRAMESIZE\t: 0x%08x\n",
				पढ़ोl(base + SSI_SSR_FRAMESIZE_REG));
	seq_म_लिखो(m, "CHANNELS\t: 0x%08x\n",
				पढ़ोl(base + SSI_SSR_CHANNELS_REG));
	seq_म_लिखो(m, "TIMEOUT\t\t: 0x%08x\n",
				पढ़ोl(base + SSI_SSR_TIMEOUT_REG));
	seq_म_लिखो(m, "RXSTATE\t\t: 0x%08x\n",
				पढ़ोl(base + SSI_SSR_RXSTATE_REG));
	seq_म_लिखो(m, "BUFSTATE\t: 0x%08x\n",
				पढ़ोl(base + SSI_SSR_BUFSTATE_REG));
	seq_म_लिखो(m, "BREAK\t\t: 0x%08x\n",
				पढ़ोl(base + SSI_SSR_BREAK_REG));
	seq_म_लिखो(m, "ERROR\t\t: 0x%08x\n",
				पढ़ोl(base + SSI_SSR_ERROR_REG));
	seq_म_लिखो(m, "ERRORACK\t: 0x%08x\n",
				पढ़ोl(base + SSI_SSR_ERRORACK_REG));
	क्रम (ch = 0; ch < omap_port->channels; ch++) अणु
		seq_म_लिखो(m, "BUFFER_CH%d\t: 0x%08x\n", ch,
				पढ़ोl(base + SSI_SSR_BUFFER_CH_REG(ch)));
	पूर्ण
	pm_runसमय_put_स्वतःsuspend(omap_port->pdev);

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(ssi_port_regs);

अटल पूर्णांक ssi_भाग_get(व्योम *data, u64 *val)
अणु
	काष्ठा hsi_port *port = data;
	काष्ठा omap_ssi_port *omap_port = hsi_port_drvdata(port);

	pm_runसमय_get_sync(omap_port->pdev);
	*val = पढ़ोl(omap_port->sst_base + SSI_SST_DIVISOR_REG);
	pm_runसमय_put_स्वतःsuspend(omap_port->pdev);

	वापस 0;
पूर्ण

अटल पूर्णांक ssi_भाग_set(व्योम *data, u64 val)
अणु
	काष्ठा hsi_port *port = data;
	काष्ठा omap_ssi_port *omap_port = hsi_port_drvdata(port);

	अगर (val > 127)
		वापस -EINVAL;

	pm_runसमय_get_sync(omap_port->pdev);
	ग_लिखोl(val, omap_port->sst_base + SSI_SST_DIVISOR_REG);
	omap_port->sst.भागisor = val;
	pm_runसमय_put_स्वतःsuspend(omap_port->pdev);

	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(ssi_sst_भाग_fops, ssi_भाग_get, ssi_भाग_set, "%llu\n");

अटल पूर्णांक ssi_debug_add_port(काष्ठा omap_ssi_port *omap_port,
				     काष्ठा dentry *dir)
अणु
	काष्ठा hsi_port *port = to_hsi_port(omap_port->dev);

	dir = debugfs_create_dir(dev_name(omap_port->dev), dir);
	अगर (!dir)
		वापस -ENOMEM;
	omap_port->dir = dir;
	debugfs_create_file("regs", S_IRUGO, dir, port, &ssi_port_regs_fops);
	dir = debugfs_create_dir("sst", dir);
	अगर (!dir)
		वापस -ENOMEM;
	debugfs_create_file_unsafe("divisor", 0644, dir, port,
				   &ssi_sst_भाग_fops);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल व्योम ssi_process_errqueue(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा omap_ssi_port *omap_port;
	काष्ठा list_head *head, *पंचांगp;
	काष्ठा hsi_msg *msg;

	omap_port = container_of(work, काष्ठा omap_ssi_port, errqueue_work.work);

	list_क्रम_each_safe(head, पंचांगp, &omap_port->errqueue) अणु
		msg = list_entry(head, काष्ठा hsi_msg, link);
		msg->complete(msg);
		list_del(head);
	पूर्ण
पूर्ण

अटल पूर्णांक ssi_claim_lch(काष्ठा hsi_msg *msg)
अणु

	काष्ठा hsi_port *port = hsi_get_port(msg->cl);
	काष्ठा hsi_controller *ssi = to_hsi_controller(port->device.parent);
	काष्ठा omap_ssi_controller *omap_ssi = hsi_controller_drvdata(ssi);
	पूर्णांक lch;

	क्रम (lch = 0; lch < SSI_MAX_GDD_LCH; lch++)
		अगर (!omap_ssi->gdd_trn[lch].msg) अणु
			omap_ssi->gdd_trn[lch].msg = msg;
			omap_ssi->gdd_trn[lch].sg = msg->sgt.sgl;
			वापस lch;
		पूर्ण

	वापस -EBUSY;
पूर्ण

अटल पूर्णांक ssi_start_dma(काष्ठा hsi_msg *msg, पूर्णांक lch)
अणु
	काष्ठा hsi_port *port = hsi_get_port(msg->cl);
	काष्ठा omap_ssi_port *omap_port = hsi_port_drvdata(port);
	काष्ठा hsi_controller *ssi = to_hsi_controller(port->device.parent);
	काष्ठा omap_ssi_controller *omap_ssi = hsi_controller_drvdata(ssi);
	व्योम __iomem *gdd = omap_ssi->gdd;
	पूर्णांक err;
	u16 csdp;
	u16 ccr;
	u32 s_addr;
	u32 d_addr;
	u32 पंचांगp;

	/* Hold घड़ीs during the transfer */
	pm_runसमय_get(omap_port->pdev);

	अगर (!pm_runसमय_active(omap_port->pdev)) अणु
		dev_warn(&port->device, "ssi_start_dma called without runtime PM!\n");
		pm_runसमय_put_स्वतःsuspend(omap_port->pdev);
		वापस -EREMOTEIO;
	पूर्ण

	अगर (msg->ttype == HSI_MSG_READ) अणु
		err = dma_map_sg(&ssi->device, msg->sgt.sgl, msg->sgt.nents,
							DMA_FROM_DEVICE);
		अगर (err < 0) अणु
			dev_dbg(&ssi->device, "DMA map SG failed !\n");
			pm_runसमय_put_स्वतःsuspend(omap_port->pdev);
			वापस err;
		पूर्ण
		csdp = SSI_DST_BURST_4x32_BIT | SSI_DST_MEMORY_PORT |
			SSI_SRC_SINGLE_ACCESS0 | SSI_SRC_PERIPHERAL_PORT |
			SSI_DATA_TYPE_S32;
		ccr = msg->channel + 0x10 + (port->num * 8); /* Sync */
		ccr |= SSI_DST_AMODE_POSTINC | SSI_SRC_AMODE_CONST |
			SSI_CCR_ENABLE;
		s_addr = omap_port->ssr_dma +
					SSI_SSR_BUFFER_CH_REG(msg->channel);
		d_addr = sg_dma_address(msg->sgt.sgl);
	पूर्ण अन्यथा अणु
		err = dma_map_sg(&ssi->device, msg->sgt.sgl, msg->sgt.nents,
							DMA_TO_DEVICE);
		अगर (err < 0) अणु
			dev_dbg(&ssi->device, "DMA map SG failed !\n");
			pm_runसमय_put_स्वतःsuspend(omap_port->pdev);
			वापस err;
		पूर्ण
		csdp = SSI_SRC_BURST_4x32_BIT | SSI_SRC_MEMORY_PORT |
			SSI_DST_SINGLE_ACCESS0 | SSI_DST_PERIPHERAL_PORT |
			SSI_DATA_TYPE_S32;
		ccr = (msg->channel + 1 + (port->num * 8)) & 0xf; /* Sync */
		ccr |= SSI_SRC_AMODE_POSTINC | SSI_DST_AMODE_CONST |
			SSI_CCR_ENABLE;
		s_addr = sg_dma_address(msg->sgt.sgl);
		d_addr = omap_port->sst_dma +
					SSI_SST_BUFFER_CH_REG(msg->channel);
	पूर्ण
	dev_dbg(&ssi->device, "lch %d cdsp %08x ccr %04x s_addr %08x d_addr %08x\n",
		lch, csdp, ccr, s_addr, d_addr);

	ग_लिखोw_relaxed(csdp, gdd + SSI_GDD_CSDP_REG(lch));
	ग_लिखोw_relaxed(SSI_BLOCK_IE | SSI_TOUT_IE, gdd + SSI_GDD_CICR_REG(lch));
	ग_लिखोl_relaxed(d_addr, gdd + SSI_GDD_CDSA_REG(lch));
	ग_लिखोl_relaxed(s_addr, gdd + SSI_GDD_CSSA_REG(lch));
	ग_लिखोw_relaxed(SSI_BYTES_TO_FRAMES(msg->sgt.sgl->length),
						gdd + SSI_GDD_CEN_REG(lch));

	spin_lock_bh(&omap_ssi->lock);
	पंचांगp = पढ़ोl(omap_ssi->sys + SSI_GDD_MPU_IRQ_ENABLE_REG);
	पंचांगp |= SSI_GDD_LCH(lch);
	ग_लिखोl_relaxed(पंचांगp, omap_ssi->sys + SSI_GDD_MPU_IRQ_ENABLE_REG);
	spin_unlock_bh(&omap_ssi->lock);
	ग_लिखोw(ccr, gdd + SSI_GDD_CCR_REG(lch));
	msg->status = HSI_STATUS_PROCEEDING;

	वापस 0;
पूर्ण

अटल पूर्णांक ssi_start_pio(काष्ठा hsi_msg *msg)
अणु
	काष्ठा hsi_port *port = hsi_get_port(msg->cl);
	काष्ठा omap_ssi_port *omap_port = hsi_port_drvdata(port);
	काष्ठा hsi_controller *ssi = to_hsi_controller(port->device.parent);
	काष्ठा omap_ssi_controller *omap_ssi = hsi_controller_drvdata(ssi);
	u32 val;

	pm_runसमय_get(omap_port->pdev);

	अगर (!pm_runसमय_active(omap_port->pdev)) अणु
		dev_warn(&port->device, "ssi_start_pio called without runtime PM!\n");
		pm_runसमय_put_स्वतःsuspend(omap_port->pdev);
		वापस -EREMOTEIO;
	पूर्ण

	अगर (msg->ttype == HSI_MSG_WRITE) अणु
		val = SSI_DATAACCEPT(msg->channel);
		/* Hold घड़ीs क्रम pio ग_लिखोs */
		pm_runसमय_get(omap_port->pdev);
	पूर्ण अन्यथा अणु
		val = SSI_DATAAVAILABLE(msg->channel) | SSI_ERROROCCURED;
	पूर्ण
	dev_dbg(&port->device, "Single %s transfer\n",
						msg->ttype ? "write" : "read");
	val |= पढ़ोl(omap_ssi->sys + SSI_MPU_ENABLE_REG(port->num, 0));
	ग_लिखोl(val, omap_ssi->sys + SSI_MPU_ENABLE_REG(port->num, 0));
	pm_runसमय_put_स्वतःsuspend(omap_port->pdev);
	msg->actual_len = 0;
	msg->status = HSI_STATUS_PROCEEDING;

	वापस 0;
पूर्ण

अटल पूर्णांक ssi_start_transfer(काष्ठा list_head *queue)
अणु
	काष्ठा hsi_msg *msg;
	पूर्णांक lch = -1;

	अगर (list_empty(queue))
		वापस 0;
	msg = list_first_entry(queue, काष्ठा hsi_msg, link);
	अगर (msg->status != HSI_STATUS_QUEUED)
		वापस 0;
	अगर ((msg->sgt.nents) && (msg->sgt.sgl->length > माप(u32)))
		lch = ssi_claim_lch(msg);
	अगर (lch >= 0)
		वापस ssi_start_dma(msg, lch);
	अन्यथा
		वापस ssi_start_pio(msg);
पूर्ण

अटल पूर्णांक ssi_async_अवरोध(काष्ठा hsi_msg *msg)
अणु
	काष्ठा hsi_port *port = hsi_get_port(msg->cl);
	काष्ठा omap_ssi_port *omap_port = hsi_port_drvdata(port);
	काष्ठा hsi_controller *ssi = to_hsi_controller(port->device.parent);
	काष्ठा omap_ssi_controller *omap_ssi = hsi_controller_drvdata(ssi);
	पूर्णांक err = 0;
	u32 पंचांगp;

	pm_runसमय_get_sync(omap_port->pdev);
	अगर (msg->ttype == HSI_MSG_WRITE) अणु
		अगर (omap_port->sst.mode != SSI_MODE_FRAME) अणु
			err = -EINVAL;
			जाओ out;
		पूर्ण
		ग_लिखोl(1, omap_port->sst_base + SSI_SST_BREAK_REG);
		msg->status = HSI_STATUS_COMPLETED;
		msg->complete(msg);
	पूर्ण अन्यथा अणु
		अगर (omap_port->ssr.mode != SSI_MODE_FRAME) अणु
			err = -EINVAL;
			जाओ out;
		पूर्ण
		spin_lock_bh(&omap_port->lock);
		पंचांगp = पढ़ोl(omap_ssi->sys +
					SSI_MPU_ENABLE_REG(port->num, 0));
		ग_लिखोl(पंचांगp | SSI_BREAKDETECTED,
			omap_ssi->sys + SSI_MPU_ENABLE_REG(port->num, 0));
		msg->status = HSI_STATUS_PROCEEDING;
		list_add_tail(&msg->link, &omap_port->brkqueue);
		spin_unlock_bh(&omap_port->lock);
	पूर्ण
out:
	pm_runसमय_mark_last_busy(omap_port->pdev);
	pm_runसमय_put_स्वतःsuspend(omap_port->pdev);

	वापस err;
पूर्ण

अटल पूर्णांक ssi_async(काष्ठा hsi_msg *msg)
अणु
	काष्ठा hsi_port *port = hsi_get_port(msg->cl);
	काष्ठा omap_ssi_port *omap_port = hsi_port_drvdata(port);
	काष्ठा list_head *queue;
	पूर्णांक err = 0;

	BUG_ON(!msg);

	अगर (msg->sgt.nents > 1)
		वापस -ENOSYS; /* TODO: Add sg support */

	अगर (msg->अवरोध_frame)
		वापस ssi_async_अवरोध(msg);

	अगर (msg->ttype) अणु
		BUG_ON(msg->channel >= omap_port->sst.channels);
		queue = &omap_port->txqueue[msg->channel];
	पूर्ण अन्यथा अणु
		BUG_ON(msg->channel >= omap_port->ssr.channels);
		queue = &omap_port->rxqueue[msg->channel];
	पूर्ण
	msg->status = HSI_STATUS_QUEUED;

	pm_runसमय_get_sync(omap_port->pdev);
	spin_lock_bh(&omap_port->lock);
	list_add_tail(&msg->link, queue);
	err = ssi_start_transfer(queue);
	अगर (err < 0) अणु
		list_del(&msg->link);
		msg->status = HSI_STATUS_ERROR;
	पूर्ण
	spin_unlock_bh(&omap_port->lock);
	pm_runसमय_mark_last_busy(omap_port->pdev);
	pm_runसमय_put_स्वतःsuspend(omap_port->pdev);
	dev_dbg(&port->device, "msg status %d ttype %d ch %d\n",
				msg->status, msg->ttype, msg->channel);

	वापस err;
पूर्ण

अटल u32 ssi_calculate_भाग(काष्ठा hsi_controller *ssi)
अणु
	काष्ठा omap_ssi_controller *omap_ssi = hsi_controller_drvdata(ssi);
	u32 tx_fckrate = (u32) omap_ssi->fck_rate;

	/* / 2 : SSI TX घड़ी is always half of the SSI functional घड़ी */
	tx_fckrate >>= 1;
	/* Round करोwn when tx_fckrate % omap_ssi->max_speed == 0 */
	tx_fckrate--;
	dev_dbg(&ssi->device, "TX div %d for fck_rate %lu Khz speed %d Kb/s\n",
		tx_fckrate / omap_ssi->max_speed, omap_ssi->fck_rate,
		omap_ssi->max_speed);

	वापस tx_fckrate / omap_ssi->max_speed;
पूर्ण

अटल व्योम ssi_flush_queue(काष्ठा list_head *queue, काष्ठा hsi_client *cl)
अणु
	काष्ठा list_head *node, *पंचांगp;
	काष्ठा hsi_msg *msg;

	list_क्रम_each_safe(node, पंचांगp, queue) अणु
		msg = list_entry(node, काष्ठा hsi_msg, link);
		अगर ((cl) && (cl != msg->cl))
			जारी;
		list_del(node);
		pr_debug("flush queue: ch %d, msg %p len %d type %d ctxt %p\n",
			msg->channel, msg, msg->sgt.sgl->length,
					msg->ttype, msg->context);
		अगर (msg->deकाष्ठाor)
			msg->deकाष्ठाor(msg);
		अन्यथा
			hsi_मुक्त_msg(msg);
	पूर्ण
पूर्ण

अटल पूर्णांक ssi_setup(काष्ठा hsi_client *cl)
अणु
	काष्ठा hsi_port *port = to_hsi_port(cl->device.parent);
	काष्ठा omap_ssi_port *omap_port = hsi_port_drvdata(port);
	काष्ठा hsi_controller *ssi = to_hsi_controller(port->device.parent);
	काष्ठा omap_ssi_controller *omap_ssi = hsi_controller_drvdata(ssi);
	व्योम __iomem *sst = omap_port->sst_base;
	व्योम __iomem *ssr = omap_port->ssr_base;
	u32 भाग;
	u32 val;
	पूर्णांक err = 0;

	pm_runसमय_get_sync(omap_port->pdev);
	spin_lock_bh(&omap_port->lock);
	अगर (cl->tx_cfg.speed)
		omap_ssi->max_speed = cl->tx_cfg.speed;
	भाग = ssi_calculate_भाग(ssi);
	अगर (भाग > SSI_MAX_DIVISOR) अणु
		dev_err(&cl->device, "Invalid TX speed %d Mb/s (div %d)\n",
						cl->tx_cfg.speed, भाग);
		err = -EINVAL;
		जाओ out;
	पूर्ण
	/* Set TX/RX module to sleep to stop TX/RX during cfg update */
	ग_लिखोl_relaxed(SSI_MODE_SLEEP, sst + SSI_SST_MODE_REG);
	ग_लिखोl_relaxed(SSI_MODE_SLEEP, ssr + SSI_SSR_MODE_REG);
	/* Flush posted ग_लिखो */
	val = पढ़ोl(ssr + SSI_SSR_MODE_REG);
	/* TX */
	ग_लिखोl_relaxed(31, sst + SSI_SST_FRAMESIZE_REG);
	ग_लिखोl_relaxed(भाग, sst + SSI_SST_DIVISOR_REG);
	ग_लिखोl_relaxed(cl->tx_cfg.num_hw_channels, sst + SSI_SST_CHANNELS_REG);
	ग_लिखोl_relaxed(cl->tx_cfg.arb_mode, sst + SSI_SST_ARBMODE_REG);
	ग_लिखोl_relaxed(cl->tx_cfg.mode, sst + SSI_SST_MODE_REG);
	/* RX */
	ग_लिखोl_relaxed(31, ssr + SSI_SSR_FRAMESIZE_REG);
	ग_लिखोl_relaxed(cl->rx_cfg.num_hw_channels, ssr + SSI_SSR_CHANNELS_REG);
	ग_लिखोl_relaxed(0, ssr + SSI_SSR_TIMEOUT_REG);
	/* Cleanup the अवरोध queue अगर we leave FRAME mode */
	अगर ((omap_port->ssr.mode == SSI_MODE_FRAME) &&
		(cl->rx_cfg.mode != SSI_MODE_FRAME))
		ssi_flush_queue(&omap_port->brkqueue, cl);
	ग_लिखोl_relaxed(cl->rx_cfg.mode, ssr + SSI_SSR_MODE_REG);
	omap_port->channels = max(cl->rx_cfg.num_hw_channels,
				  cl->tx_cfg.num_hw_channels);
	/* Shaकरोw रेजिस्टरing क्रम OFF mode */
	/* SST */
	omap_port->sst.भागisor = भाग;
	omap_port->sst.frame_size = 31;
	omap_port->sst.channels = cl->tx_cfg.num_hw_channels;
	omap_port->sst.arb_mode = cl->tx_cfg.arb_mode;
	omap_port->sst.mode = cl->tx_cfg.mode;
	/* SSR */
	omap_port->ssr.frame_size = 31;
	omap_port->ssr.समयout = 0;
	omap_port->ssr.channels = cl->rx_cfg.num_hw_channels;
	omap_port->ssr.mode = cl->rx_cfg.mode;
out:
	spin_unlock_bh(&omap_port->lock);
	pm_runसमय_mark_last_busy(omap_port->pdev);
	pm_runसमय_put_स्वतःsuspend(omap_port->pdev);

	वापस err;
पूर्ण

अटल पूर्णांक ssi_flush(काष्ठा hsi_client *cl)
अणु
	काष्ठा hsi_port *port = hsi_get_port(cl);
	काष्ठा omap_ssi_port *omap_port = hsi_port_drvdata(port);
	काष्ठा hsi_controller *ssi = to_hsi_controller(port->device.parent);
	काष्ठा omap_ssi_controller *omap_ssi = hsi_controller_drvdata(ssi);
	काष्ठा hsi_msg *msg;
	व्योम __iomem *sst = omap_port->sst_base;
	व्योम __iomem *ssr = omap_port->ssr_base;
	अचिन्हित पूर्णांक i;
	u32 err;

	pm_runसमय_get_sync(omap_port->pdev);
	spin_lock_bh(&omap_port->lock);

	/* stop all ssi communication */
	pinctrl_pm_select_idle_state(omap_port->pdev);
	udelay(1); /* रुको क्रम racing frames */

	/* Stop all DMA transfers */
	क्रम (i = 0; i < SSI_MAX_GDD_LCH; i++) अणु
		msg = omap_ssi->gdd_trn[i].msg;
		अगर (!msg || (port != hsi_get_port(msg->cl)))
			जारी;
		ग_लिखोw_relaxed(0, omap_ssi->gdd + SSI_GDD_CCR_REG(i));
		अगर (msg->ttype == HSI_MSG_READ)
			pm_runसमय_put_स्वतःsuspend(omap_port->pdev);
		omap_ssi->gdd_trn[i].msg = शून्य;
	पूर्ण
	/* Flush all SST buffers */
	ग_लिखोl_relaxed(0, sst + SSI_SST_BUFSTATE_REG);
	ग_लिखोl_relaxed(0, sst + SSI_SST_TXSTATE_REG);
	/* Flush all SSR buffers */
	ग_लिखोl_relaxed(0, ssr + SSI_SSR_RXSTATE_REG);
	ग_लिखोl_relaxed(0, ssr + SSI_SSR_BUFSTATE_REG);
	/* Flush all errors */
	err = पढ़ोl(ssr + SSI_SSR_ERROR_REG);
	ग_लिखोl_relaxed(err, ssr + SSI_SSR_ERRORACK_REG);
	/* Flush अवरोध */
	ग_लिखोl_relaxed(0, ssr + SSI_SSR_BREAK_REG);
	/* Clear पूर्णांकerrupts */
	ग_लिखोl_relaxed(0, omap_ssi->sys + SSI_MPU_ENABLE_REG(port->num, 0));
	ग_लिखोl_relaxed(0xffffff00,
			omap_ssi->sys + SSI_MPU_STATUS_REG(port->num, 0));
	ग_लिखोl_relaxed(0, omap_ssi->sys + SSI_GDD_MPU_IRQ_ENABLE_REG);
	ग_लिखोl(0xff, omap_ssi->sys + SSI_GDD_MPU_IRQ_STATUS_REG);
	/* Dequeue all pending requests */
	क्रम (i = 0; i < omap_port->channels; i++) अणु
		/* Release ग_लिखो घड़ीs */
		अगर (!list_empty(&omap_port->txqueue[i]))
			pm_runसमय_put_स्वतःsuspend(omap_port->pdev);
		ssi_flush_queue(&omap_port->txqueue[i], शून्य);
		ssi_flush_queue(&omap_port->rxqueue[i], शून्य);
	पूर्ण
	ssi_flush_queue(&omap_port->brkqueue, शून्य);

	/* Resume SSI communication */
	pinctrl_pm_select_शेष_state(omap_port->pdev);

	spin_unlock_bh(&omap_port->lock);
	pm_runसमय_mark_last_busy(omap_port->pdev);
	pm_runसमय_put_स्वतःsuspend(omap_port->pdev);

	वापस 0;
पूर्ण

अटल व्योम start_tx_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा omap_ssi_port *omap_port =
				container_of(work, काष्ठा omap_ssi_port, work);
	काष्ठा hsi_port *port = to_hsi_port(omap_port->dev);
	काष्ठा hsi_controller *ssi = to_hsi_controller(port->device.parent);
	काष्ठा omap_ssi_controller *omap_ssi = hsi_controller_drvdata(ssi);

	pm_runसमय_get_sync(omap_port->pdev); /* Grab घड़ीs */
	ग_लिखोl(SSI_WAKE(0), omap_ssi->sys + SSI_SET_WAKE_REG(port->num));
पूर्ण

अटल पूर्णांक ssi_start_tx(काष्ठा hsi_client *cl)
अणु
	काष्ठा hsi_port *port = hsi_get_port(cl);
	काष्ठा omap_ssi_port *omap_port = hsi_port_drvdata(port);

	dev_dbg(&port->device, "Wake out high %d\n", omap_port->wk_refcount);

	spin_lock_bh(&omap_port->wk_lock);
	अगर (omap_port->wk_refcount++) अणु
		spin_unlock_bh(&omap_port->wk_lock);
		वापस 0;
	पूर्ण
	spin_unlock_bh(&omap_port->wk_lock);

	schedule_work(&omap_port->work);

	वापस 0;
पूर्ण

अटल पूर्णांक ssi_stop_tx(काष्ठा hsi_client *cl)
अणु
	काष्ठा hsi_port *port = hsi_get_port(cl);
	काष्ठा omap_ssi_port *omap_port = hsi_port_drvdata(port);
	काष्ठा hsi_controller *ssi = to_hsi_controller(port->device.parent);
	काष्ठा omap_ssi_controller *omap_ssi = hsi_controller_drvdata(ssi);

	dev_dbg(&port->device, "Wake out low %d\n", omap_port->wk_refcount);

	spin_lock_bh(&omap_port->wk_lock);
	BUG_ON(!omap_port->wk_refcount);
	अगर (--omap_port->wk_refcount) अणु
		spin_unlock_bh(&omap_port->wk_lock);
		वापस 0;
	पूर्ण
	ग_लिखोl(SSI_WAKE(0), omap_ssi->sys + SSI_CLEAR_WAKE_REG(port->num));
	spin_unlock_bh(&omap_port->wk_lock);

	pm_runसमय_mark_last_busy(omap_port->pdev);
	pm_runसमय_put_स्वतःsuspend(omap_port->pdev); /* Release घड़ीs */


	वापस 0;
पूर्ण

अटल व्योम ssi_transfer(काष्ठा omap_ssi_port *omap_port,
							काष्ठा list_head *queue)
अणु
	काष्ठा hsi_msg *msg;
	पूर्णांक err = -1;

	pm_runसमय_get(omap_port->pdev);
	spin_lock_bh(&omap_port->lock);
	जबतक (err < 0) अणु
		err = ssi_start_transfer(queue);
		अगर (err < 0) अणु
			msg = list_first_entry(queue, काष्ठा hsi_msg, link);
			msg->status = HSI_STATUS_ERROR;
			msg->actual_len = 0;
			list_del(&msg->link);
			spin_unlock_bh(&omap_port->lock);
			msg->complete(msg);
			spin_lock_bh(&omap_port->lock);
		पूर्ण
	पूर्ण
	spin_unlock_bh(&omap_port->lock);
	pm_runसमय_mark_last_busy(omap_port->pdev);
	pm_runसमय_put_स्वतःsuspend(omap_port->pdev);
पूर्ण

अटल व्योम ssi_cleanup_queues(काष्ठा hsi_client *cl)
अणु
	काष्ठा hsi_port *port = hsi_get_port(cl);
	काष्ठा omap_ssi_port *omap_port = hsi_port_drvdata(port);
	काष्ठा hsi_controller *ssi = to_hsi_controller(port->device.parent);
	काष्ठा omap_ssi_controller *omap_ssi = hsi_controller_drvdata(ssi);
	काष्ठा hsi_msg *msg;
	अचिन्हित पूर्णांक i;
	u32 rxbuख_स्थितिe = 0;
	u32 txbuख_स्थितिe = 0;
	u32 status = SSI_ERROROCCURED;
	u32 पंचांगp;

	ssi_flush_queue(&omap_port->brkqueue, cl);
	अगर (list_empty(&omap_port->brkqueue))
		status |= SSI_BREAKDETECTED;

	क्रम (i = 0; i < omap_port->channels; i++) अणु
		अगर (list_empty(&omap_port->txqueue[i]))
			जारी;
		msg = list_first_entry(&omap_port->txqueue[i], काष्ठा hsi_msg,
									link);
		अगर ((msg->cl == cl) && (msg->status == HSI_STATUS_PROCEEDING)) अणु
			txbuख_स्थितिe |= (1 << i);
			status |= SSI_DATAACCEPT(i);
			/* Release the घड़ीs ग_लिखोs, also GDD ones */
			pm_runसमय_mark_last_busy(omap_port->pdev);
			pm_runसमय_put_स्वतःsuspend(omap_port->pdev);
		पूर्ण
		ssi_flush_queue(&omap_port->txqueue[i], cl);
	पूर्ण
	क्रम (i = 0; i < omap_port->channels; i++) अणु
		अगर (list_empty(&omap_port->rxqueue[i]))
			जारी;
		msg = list_first_entry(&omap_port->rxqueue[i], काष्ठा hsi_msg,
									link);
		अगर ((msg->cl == cl) && (msg->status == HSI_STATUS_PROCEEDING)) अणु
			rxbuख_स्थितिe |= (1 << i);
			status |= SSI_DATAAVAILABLE(i);
		पूर्ण
		ssi_flush_queue(&omap_port->rxqueue[i], cl);
		/* Check अगर we keep the error detection पूर्णांकerrupt armed */
		अगर (!list_empty(&omap_port->rxqueue[i]))
			status &= ~SSI_ERROROCCURED;
	पूर्ण
	/* Cleanup ग_लिखो buffers */
	पंचांगp = पढ़ोl(omap_port->sst_base + SSI_SST_BUFSTATE_REG);
	पंचांगp &= ~txbuख_स्थितिe;
	ग_लिखोl_relaxed(पंचांगp, omap_port->sst_base + SSI_SST_BUFSTATE_REG);
	/* Cleanup पढ़ो buffers */
	पंचांगp = पढ़ोl(omap_port->ssr_base + SSI_SSR_BUFSTATE_REG);
	पंचांगp &= ~rxbuख_स्थितिe;
	ग_लिखोl_relaxed(पंचांगp, omap_port->ssr_base + SSI_SSR_BUFSTATE_REG);
	/* Disarm and ack pending पूर्णांकerrupts */
	पंचांगp = पढ़ोl(omap_ssi->sys + SSI_MPU_ENABLE_REG(port->num, 0));
	पंचांगp &= ~status;
	ग_लिखोl_relaxed(पंचांगp, omap_ssi->sys + SSI_MPU_ENABLE_REG(port->num, 0));
	ग_लिखोl_relaxed(status, omap_ssi->sys +
		SSI_MPU_STATUS_REG(port->num, 0));
पूर्ण

अटल व्योम ssi_cleanup_gdd(काष्ठा hsi_controller *ssi, काष्ठा hsi_client *cl)
अणु
	काष्ठा omap_ssi_controller *omap_ssi = hsi_controller_drvdata(ssi);
	काष्ठा hsi_port *port = hsi_get_port(cl);
	काष्ठा omap_ssi_port *omap_port = hsi_port_drvdata(port);
	काष्ठा hsi_msg *msg;
	अचिन्हित पूर्णांक i;
	u32 val = 0;
	u32 पंचांगp;

	क्रम (i = 0; i < SSI_MAX_GDD_LCH; i++) अणु
		msg = omap_ssi->gdd_trn[i].msg;
		अगर ((!msg) || (msg->cl != cl))
			जारी;
		ग_लिखोw_relaxed(0, omap_ssi->gdd + SSI_GDD_CCR_REG(i));
		val |= (1 << i);
		/*
		 * Clock references क्रम ग_लिखो will be handled in
		 * ssi_cleanup_queues
		 */
		अगर (msg->ttype == HSI_MSG_READ) अणु
			pm_runसमय_mark_last_busy(omap_port->pdev);
			pm_runसमय_put_स्वतःsuspend(omap_port->pdev);
		पूर्ण
		omap_ssi->gdd_trn[i].msg = शून्य;
	पूर्ण
	पंचांगp = पढ़ोl_relaxed(omap_ssi->sys + SSI_GDD_MPU_IRQ_ENABLE_REG);
	पंचांगp &= ~val;
	ग_लिखोl_relaxed(पंचांगp, omap_ssi->sys + SSI_GDD_MPU_IRQ_ENABLE_REG);
	ग_लिखोl(val, omap_ssi->sys + SSI_GDD_MPU_IRQ_STATUS_REG);
पूर्ण

अटल पूर्णांक ssi_set_port_mode(काष्ठा omap_ssi_port *omap_port, u32 mode)
अणु
	ग_लिखोl(mode, omap_port->sst_base + SSI_SST_MODE_REG);
	ग_लिखोl(mode, omap_port->ssr_base + SSI_SSR_MODE_REG);
	/* OCP barrier */
	mode = पढ़ोl(omap_port->ssr_base + SSI_SSR_MODE_REG);

	वापस 0;
पूर्ण

अटल पूर्णांक ssi_release(काष्ठा hsi_client *cl)
अणु
	काष्ठा hsi_port *port = hsi_get_port(cl);
	काष्ठा omap_ssi_port *omap_port = hsi_port_drvdata(port);
	काष्ठा hsi_controller *ssi = to_hsi_controller(port->device.parent);

	pm_runसमय_get_sync(omap_port->pdev);
	spin_lock_bh(&omap_port->lock);
	/* Stop all the pending DMA requests क्रम that client */
	ssi_cleanup_gdd(ssi, cl);
	/* Now cleanup all the queues */
	ssi_cleanup_queues(cl);
	/* If it is the last client of the port, करो extra checks and cleanup */
	अगर (port->claimed <= 1) अणु
		/*
		 * Drop the घड़ी reference क्रम the incoming wake line
		 * अगर it is still kept high by the other side.
		 */
		अगर (test_and_clear_bit(SSI_WAKE_EN, &omap_port->flags))
			pm_runसमय_put_sync(omap_port->pdev);
		pm_runसमय_get(omap_port->pdev);
		/* Stop any SSI TX/RX without a client */
		ssi_set_port_mode(omap_port, SSI_MODE_SLEEP);
		omap_port->sst.mode = SSI_MODE_SLEEP;
		omap_port->ssr.mode = SSI_MODE_SLEEP;
		pm_runसमय_put(omap_port->pdev);
		WARN_ON(omap_port->wk_refcount != 0);
	पूर्ण
	spin_unlock_bh(&omap_port->lock);
	pm_runसमय_put_sync(omap_port->pdev);

	वापस 0;
पूर्ण



अटल व्योम ssi_error(काष्ठा hsi_port *port)
अणु
	काष्ठा omap_ssi_port *omap_port = hsi_port_drvdata(port);
	काष्ठा hsi_controller *ssi = to_hsi_controller(port->device.parent);
	काष्ठा omap_ssi_controller *omap_ssi = hsi_controller_drvdata(ssi);
	काष्ठा hsi_msg *msg;
	अचिन्हित पूर्णांक i;
	u32 err;
	u32 val;
	u32 पंचांगp;

	/* ACK error */
	err = पढ़ोl(omap_port->ssr_base + SSI_SSR_ERROR_REG);
	dev_err(&port->device, "SSI error: 0x%02x\n", err);
	अगर (!err) अणु
		dev_dbg(&port->device, "spurious SSI error ignored!\n");
		वापस;
	पूर्ण
	spin_lock(&omap_ssi->lock);
	/* Cancel all GDD पढ़ो transfers */
	क्रम (i = 0, val = 0; i < SSI_MAX_GDD_LCH; i++) अणु
		msg = omap_ssi->gdd_trn[i].msg;
		अगर ((msg) && (msg->ttype == HSI_MSG_READ)) अणु
			ग_लिखोw_relaxed(0, omap_ssi->gdd + SSI_GDD_CCR_REG(i));
			val |= (1 << i);
			omap_ssi->gdd_trn[i].msg = शून्य;
		पूर्ण
	पूर्ण
	पंचांगp = पढ़ोl(omap_ssi->sys + SSI_GDD_MPU_IRQ_ENABLE_REG);
	पंचांगp &= ~val;
	ग_लिखोl_relaxed(पंचांगp, omap_ssi->sys + SSI_GDD_MPU_IRQ_ENABLE_REG);
	spin_unlock(&omap_ssi->lock);
	/* Cancel all PIO पढ़ो transfers */
	spin_lock(&omap_port->lock);
	पंचांगp = पढ़ोl(omap_ssi->sys + SSI_MPU_ENABLE_REG(port->num, 0));
	पंचांगp &= 0xfeff00ff; /* Disable error & all dataavailable पूर्णांकerrupts */
	ग_लिखोl_relaxed(पंचांगp, omap_ssi->sys + SSI_MPU_ENABLE_REG(port->num, 0));
	/* ACK error */
	ग_लिखोl_relaxed(err, omap_port->ssr_base + SSI_SSR_ERRORACK_REG);
	ग_लिखोl_relaxed(SSI_ERROROCCURED,
			omap_ssi->sys + SSI_MPU_STATUS_REG(port->num, 0));
	/* Signal the error all current pending पढ़ो requests */
	क्रम (i = 0; i < omap_port->channels; i++) अणु
		अगर (list_empty(&omap_port->rxqueue[i]))
			जारी;
		msg = list_first_entry(&omap_port->rxqueue[i], काष्ठा hsi_msg,
									link);
		list_del(&msg->link);
		msg->status = HSI_STATUS_ERROR;
		spin_unlock(&omap_port->lock);
		msg->complete(msg);
		/* Now restart queued पढ़ोs अगर any */
		ssi_transfer(omap_port, &omap_port->rxqueue[i]);
		spin_lock(&omap_port->lock);
	पूर्ण
	spin_unlock(&omap_port->lock);
पूर्ण

अटल व्योम ssi_अवरोध_complete(काष्ठा hsi_port *port)
अणु
	काष्ठा omap_ssi_port *omap_port = hsi_port_drvdata(port);
	काष्ठा hsi_controller *ssi = to_hsi_controller(port->device.parent);
	काष्ठा omap_ssi_controller *omap_ssi = hsi_controller_drvdata(ssi);
	काष्ठा hsi_msg *msg;
	काष्ठा hsi_msg *पंचांगp;
	u32 val;

	dev_dbg(&port->device, "HWBREAK received\n");

	spin_lock(&omap_port->lock);
	val = पढ़ोl(omap_ssi->sys + SSI_MPU_ENABLE_REG(port->num, 0));
	val &= ~SSI_BREAKDETECTED;
	ग_लिखोl_relaxed(val, omap_ssi->sys + SSI_MPU_ENABLE_REG(port->num, 0));
	ग_लिखोl_relaxed(0, omap_port->ssr_base + SSI_SSR_BREAK_REG);
	ग_लिखोl(SSI_BREAKDETECTED,
			omap_ssi->sys + SSI_MPU_STATUS_REG(port->num, 0));
	spin_unlock(&omap_port->lock);

	list_क्रम_each_entry_safe(msg, पंचांगp, &omap_port->brkqueue, link) अणु
		msg->status = HSI_STATUS_COMPLETED;
		spin_lock(&omap_port->lock);
		list_del(&msg->link);
		spin_unlock(&omap_port->lock);
		msg->complete(msg);
	पूर्ण

पूर्ण

अटल व्योम ssi_pio_complete(काष्ठा hsi_port *port, काष्ठा list_head *queue)
अणु
	काष्ठा hsi_controller *ssi = to_hsi_controller(port->device.parent);
	काष्ठा omap_ssi_controller *omap_ssi = hsi_controller_drvdata(ssi);
	काष्ठा omap_ssi_port *omap_port = hsi_port_drvdata(port);
	काष्ठा hsi_msg *msg;
	u32 *buf;
	u32 reg;
	u32 val;

	spin_lock_bh(&omap_port->lock);
	msg = list_first_entry(queue, काष्ठा hsi_msg, link);
	अगर ((!msg->sgt.nents) || (!msg->sgt.sgl->length)) अणु
		msg->actual_len = 0;
		msg->status = HSI_STATUS_PENDING;
	पूर्ण
	अगर (msg->ttype == HSI_MSG_WRITE)
		val = SSI_DATAACCEPT(msg->channel);
	अन्यथा
		val = SSI_DATAAVAILABLE(msg->channel);
	अगर (msg->status == HSI_STATUS_PROCEEDING) अणु
		buf = sg_virt(msg->sgt.sgl) + msg->actual_len;
		अगर (msg->ttype == HSI_MSG_WRITE)
			ग_लिखोl(*buf, omap_port->sst_base +
					SSI_SST_BUFFER_CH_REG(msg->channel));
		 अन्यथा
			*buf = पढ़ोl(omap_port->ssr_base +
					SSI_SSR_BUFFER_CH_REG(msg->channel));
		dev_dbg(&port->device, "ch %d ttype %d 0x%08x\n", msg->channel,
							msg->ttype, *buf);
		msg->actual_len += माप(*buf);
		अगर (msg->actual_len >= msg->sgt.sgl->length)
			msg->status = HSI_STATUS_COMPLETED;
		/*
		 * Wait क्रम the last written frame to be really sent beक्रमe
		 * we call the complete callback
		 */
		अगर ((msg->status == HSI_STATUS_PROCEEDING) ||
				((msg->status == HSI_STATUS_COMPLETED) &&
					(msg->ttype == HSI_MSG_WRITE))) अणु
			ग_लिखोl(val, omap_ssi->sys +
					SSI_MPU_STATUS_REG(port->num, 0));
			spin_unlock_bh(&omap_port->lock);

			वापस;
		पूर्ण

	पूर्ण
	/* Transfer completed at this poपूर्णांक */
	reg = पढ़ोl(omap_ssi->sys + SSI_MPU_ENABLE_REG(port->num, 0));
	अगर (msg->ttype == HSI_MSG_WRITE) अणु
		/* Release घड़ीs क्रम ग_लिखो transfer */
		pm_runसमय_mark_last_busy(omap_port->pdev);
		pm_runसमय_put_स्वतःsuspend(omap_port->pdev);
	पूर्ण
	reg &= ~val;
	ग_लिखोl_relaxed(reg, omap_ssi->sys + SSI_MPU_ENABLE_REG(port->num, 0));
	ग_लिखोl_relaxed(val, omap_ssi->sys + SSI_MPU_STATUS_REG(port->num, 0));
	list_del(&msg->link);
	spin_unlock_bh(&omap_port->lock);
	msg->complete(msg);
	ssi_transfer(omap_port, queue);
पूर्ण

अटल irqवापस_t ssi_pio_thपढ़ो(पूर्णांक irq, व्योम *ssi_port)
अणु
	काष्ठा hsi_port *port = (काष्ठा hsi_port *)ssi_port;
	काष्ठा hsi_controller *ssi = to_hsi_controller(port->device.parent);
	काष्ठा omap_ssi_port *omap_port = hsi_port_drvdata(port);
	काष्ठा omap_ssi_controller *omap_ssi = hsi_controller_drvdata(ssi);
	व्योम __iomem *sys = omap_ssi->sys;
	अचिन्हित पूर्णांक ch;
	u32 status_reg;

	pm_runसमय_get_sync(omap_port->pdev);

	करो अणु
		status_reg = पढ़ोl(sys + SSI_MPU_STATUS_REG(port->num, 0));
		status_reg &= पढ़ोl(sys + SSI_MPU_ENABLE_REG(port->num, 0));

		क्रम (ch = 0; ch < omap_port->channels; ch++) अणु
			अगर (status_reg & SSI_DATAACCEPT(ch))
				ssi_pio_complete(port, &omap_port->txqueue[ch]);
			अगर (status_reg & SSI_DATAAVAILABLE(ch))
				ssi_pio_complete(port, &omap_port->rxqueue[ch]);
		पूर्ण
		अगर (status_reg & SSI_BREAKDETECTED)
			ssi_अवरोध_complete(port);
		अगर (status_reg & SSI_ERROROCCURED)
			ssi_error(port);

		status_reg = पढ़ोl(sys + SSI_MPU_STATUS_REG(port->num, 0));
		status_reg &= पढ़ोl(sys + SSI_MPU_ENABLE_REG(port->num, 0));

		/* TODO: sleep अगर we retry? */
	पूर्ण जबतक (status_reg);

	pm_runसमय_mark_last_busy(omap_port->pdev);
	pm_runसमय_put_स्वतःsuspend(omap_port->pdev);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t ssi_wake_thपढ़ो(पूर्णांक irq __maybe_unused, व्योम *ssi_port)
अणु
	काष्ठा hsi_port *port = (काष्ठा hsi_port *)ssi_port;
	काष्ठा hsi_controller *ssi = to_hsi_controller(port->device.parent);
	काष्ठा omap_ssi_port *omap_port = hsi_port_drvdata(port);
	काष्ठा omap_ssi_controller *omap_ssi = hsi_controller_drvdata(ssi);

	अगर (ssi_wakein(port)) अणु
		/**
		 * We can have a quick High-Low-High transition in the line.
		 * In such a हाल अगर we have दीर्घ पूर्णांकerrupt latencies,
		 * we can miss the low event or get twice a high event.
		 * This workaround will aव्योम अवरोधing the घड़ी reference
		 * count when such a situation ocurrs.
		 */
		अगर (!test_and_set_bit(SSI_WAKE_EN, &omap_port->flags))
			pm_runसमय_get_sync(omap_port->pdev);
		dev_dbg(&ssi->device, "Wake in high\n");
		अगर (omap_port->wktest) अणु /* FIXME: HACK ! To be हटाओd */
			ग_लिखोl(SSI_WAKE(0),
				omap_ssi->sys + SSI_SET_WAKE_REG(port->num));
		पूर्ण
		hsi_event(port, HSI_EVENT_START_RX);
	पूर्ण अन्यथा अणु
		dev_dbg(&ssi->device, "Wake in low\n");
		अगर (omap_port->wktest) अणु /* FIXME: HACK ! To be हटाओd */
			ग_लिखोl(SSI_WAKE(0),
				omap_ssi->sys + SSI_CLEAR_WAKE_REG(port->num));
		पूर्ण
		hsi_event(port, HSI_EVENT_STOP_RX);
		अगर (test_and_clear_bit(SSI_WAKE_EN, &omap_port->flags)) अणु
			pm_runसमय_mark_last_busy(omap_port->pdev);
			pm_runसमय_put_स्वतःsuspend(omap_port->pdev);
		पूर्ण
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक ssi_port_irq(काष्ठा hsi_port *port, काष्ठा platक्रमm_device *pd)
अणु
	काष्ठा omap_ssi_port *omap_port = hsi_port_drvdata(port);
	पूर्णांक err;

	err = platक्रमm_get_irq(pd, 0);
	अगर (err < 0)
		वापस err;
	omap_port->irq = err;
	err = devm_request_thपढ़ोed_irq(&port->device, omap_port->irq, शून्य,
				ssi_pio_thपढ़ो, IRQF_ONESHOT, "SSI PORT", port);
	अगर (err < 0)
		dev_err(&port->device, "Request IRQ %d failed (%d)\n",
							omap_port->irq, err);
	वापस err;
पूर्ण

अटल पूर्णांक ssi_wake_irq(काष्ठा hsi_port *port, काष्ठा platक्रमm_device *pd)
अणु
	काष्ठा omap_ssi_port *omap_port = hsi_port_drvdata(port);
	पूर्णांक cawake_irq;
	पूर्णांक err;

	अगर (!omap_port->wake_gpio) अणु
		omap_port->wake_irq = -1;
		वापस 0;
	पूर्ण

	cawake_irq = gpiod_to_irq(omap_port->wake_gpio);
	omap_port->wake_irq = cawake_irq;

	err = devm_request_thपढ़ोed_irq(&port->device, cawake_irq, शून्य,
		ssi_wake_thपढ़ो,
		IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
		"SSI cawake", port);
	अगर (err < 0)
		dev_err(&port->device, "Request Wake in IRQ %d failed %d\n",
						cawake_irq, err);
	err = enable_irq_wake(cawake_irq);
	अगर (err < 0)
		dev_err(&port->device, "Enable wake on the wakeline in irq %d failed %d\n",
			cawake_irq, err);

	वापस err;
पूर्ण

अटल व्योम ssi_queues_init(काष्ठा omap_ssi_port *omap_port)
अणु
	अचिन्हित पूर्णांक ch;

	क्रम (ch = 0; ch < SSI_MAX_CHANNELS; ch++) अणु
		INIT_LIST_HEAD(&omap_port->txqueue[ch]);
		INIT_LIST_HEAD(&omap_port->rxqueue[ch]);
	पूर्ण
	INIT_LIST_HEAD(&omap_port->brkqueue);
पूर्ण

अटल पूर्णांक ssi_port_get_iomem(काष्ठा platक्रमm_device *pd,
		स्थिर अक्षर *name, व्योम __iomem **pbase, dma_addr_t *phy)
अणु
	काष्ठा hsi_port *port = platक्रमm_get_drvdata(pd);
	काष्ठा resource *mem;
	काष्ठा resource *ioarea;
	व्योम __iomem *base;

	mem = platक्रमm_get_resource_byname(pd, IORESOURCE_MEM, name);
	अगर (!mem) अणु
		dev_err(&pd->dev, "IO memory region missing (%s)\n", name);
		वापस -ENXIO;
	पूर्ण
	ioarea = devm_request_mem_region(&port->device, mem->start,
					resource_size(mem), dev_name(&pd->dev));
	अगर (!ioarea) अणु
		dev_err(&pd->dev, "%s IO memory region request failed\n",
								mem->name);
		वापस -ENXIO;
	पूर्ण
	base = devm_ioremap(&port->device, mem->start, resource_size(mem));
	अगर (!base) अणु
		dev_err(&pd->dev, "%s IO remap failed\n", mem->name);
		वापस -ENXIO;
	पूर्ण
	*pbase = base;

	अगर (phy)
		*phy = mem->start;

	वापस 0;
पूर्ण

अटल पूर्णांक ssi_port_probe(काष्ठा platक्रमm_device *pd)
अणु
	काष्ठा device_node *np = pd->dev.of_node;
	काष्ठा hsi_port *port;
	काष्ठा omap_ssi_port *omap_port;
	काष्ठा hsi_controller *ssi = dev_get_drvdata(pd->dev.parent);
	काष्ठा omap_ssi_controller *omap_ssi = hsi_controller_drvdata(ssi);
	काष्ठा gpio_desc *cawake_gpio = शून्य;
	u32 port_id;
	पूर्णांक err;

	dev_dbg(&pd->dev, "init ssi port...\n");

	अगर (!ssi->port || !omap_ssi->port) अणु
		dev_err(&pd->dev, "ssi controller not initialized!\n");
		err = -ENODEV;
		जाओ error;
	पूर्ण

	/* get id of first uninitialized port in controller */
	क्रम (port_id = 0; port_id < ssi->num_ports && omap_ssi->port[port_id];
		port_id++)
		;

	अगर (port_id >= ssi->num_ports) अणु
		dev_err(&pd->dev, "port id out of range!\n");
		err = -ENODEV;
		जाओ error;
	पूर्ण

	port = ssi->port[port_id];

	अगर (!np) अणु
		dev_err(&pd->dev, "missing device tree data\n");
		err = -EINVAL;
		जाओ error;
	पूर्ण

	cawake_gpio = devm_gpiod_get(&pd->dev, "ti,ssi-cawake", GPIOD_IN);
	अगर (IS_ERR(cawake_gpio)) अणु
		err = PTR_ERR(cawake_gpio);
		dev_err(&pd->dev, "couldn't get cawake gpio (err=%d)!\n", err);
		जाओ error;
	पूर्ण

	omap_port = devm_kzalloc(&port->device, माप(*omap_port), GFP_KERNEL);
	अगर (!omap_port) अणु
		err = -ENOMEM;
		जाओ error;
	पूर्ण
	omap_port->wake_gpio = cawake_gpio;
	omap_port->pdev = &pd->dev;
	omap_port->port_id = port_id;

	INIT_DEFERRABLE_WORK(&omap_port->errqueue_work, ssi_process_errqueue);
	INIT_WORK(&omap_port->work, start_tx_work);

	/* initialize HSI port */
	port->async	= ssi_async;
	port->setup	= ssi_setup;
	port->flush	= ssi_flush;
	port->start_tx	= ssi_start_tx;
	port->stop_tx	= ssi_stop_tx;
	port->release	= ssi_release;
	hsi_port_set_drvdata(port, omap_port);
	omap_ssi->port[port_id] = omap_port;

	platक्रमm_set_drvdata(pd, port);

	err = ssi_port_get_iomem(pd, "tx", &omap_port->sst_base,
		&omap_port->sst_dma);
	अगर (err < 0)
		जाओ error;
	err = ssi_port_get_iomem(pd, "rx", &omap_port->ssr_base,
		&omap_port->ssr_dma);
	अगर (err < 0)
		जाओ error;

	err = ssi_port_irq(port, pd);
	अगर (err < 0)
		जाओ error;
	err = ssi_wake_irq(port, pd);
	अगर (err < 0)
		जाओ error;

	ssi_queues_init(omap_port);
	spin_lock_init(&omap_port->lock);
	spin_lock_init(&omap_port->wk_lock);
	omap_port->dev = &port->device;

	pm_runसमय_use_स्वतःsuspend(omap_port->pdev);
	pm_runसमय_set_स्वतःsuspend_delay(omap_port->pdev, 250);
	pm_runसमय_enable(omap_port->pdev);

#अगर_घोषित CONFIG_DEBUG_FS
	err = ssi_debug_add_port(omap_port, omap_ssi->dir);
	अगर (err < 0) अणु
		pm_runसमय_disable(omap_port->pdev);
		जाओ error;
	पूर्ण
#पूर्ण_अगर

	hsi_add_clients_from_dt(port, np);

	dev_info(&pd->dev, "ssi port %u successfully initialized\n", port_id);

	वापस 0;

error:
	वापस err;
पूर्ण

अटल पूर्णांक ssi_port_हटाओ(काष्ठा platक्रमm_device *pd)
अणु
	काष्ठा hsi_port *port = platक्रमm_get_drvdata(pd);
	काष्ठा omap_ssi_port *omap_port = hsi_port_drvdata(port);
	काष्ठा hsi_controller *ssi = to_hsi_controller(port->device.parent);
	काष्ठा omap_ssi_controller *omap_ssi = hsi_controller_drvdata(ssi);

#अगर_घोषित CONFIG_DEBUG_FS
	ssi_debug_हटाओ_port(port);
#पूर्ण_अगर

	cancel_delayed_work_sync(&omap_port->errqueue_work);

	hsi_port_unरेजिस्टर_clients(port);

	port->async	= hsi_dummy_msg;
	port->setup	= hsi_dummy_cl;
	port->flush	= hsi_dummy_cl;
	port->start_tx	= hsi_dummy_cl;
	port->stop_tx	= hsi_dummy_cl;
	port->release	= hsi_dummy_cl;

	omap_ssi->port[omap_port->port_id] = शून्य;
	platक्रमm_set_drvdata(pd, शून्य);

	pm_runसमय_करोnt_use_स्वतःsuspend(&pd->dev);
	pm_runसमय_disable(&pd->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक ssi_restore_भागisor(काष्ठा omap_ssi_port *omap_port)
अणु
	ग_लिखोl_relaxed(omap_port->sst.भागisor,
				omap_port->sst_base + SSI_SST_DIVISOR_REG);

	वापस 0;
पूर्ण

व्योम omap_ssi_port_update_fclk(काष्ठा hsi_controller *ssi,
			       काष्ठा omap_ssi_port *omap_port)
अणु
	/* update भागisor */
	u32 भाग = ssi_calculate_भाग(ssi);
	omap_port->sst.भागisor = भाग;
	ssi_restore_भागisor(omap_port);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक ssi_save_port_ctx(काष्ठा omap_ssi_port *omap_port)
अणु
	काष्ठा hsi_port *port = to_hsi_port(omap_port->dev);
	काष्ठा hsi_controller *ssi = to_hsi_controller(port->device.parent);
	काष्ठा omap_ssi_controller *omap_ssi = hsi_controller_drvdata(ssi);

	omap_port->sys_mpu_enable = पढ़ोl(omap_ssi->sys +
					SSI_MPU_ENABLE_REG(port->num, 0));

	वापस 0;
पूर्ण

अटल पूर्णांक ssi_restore_port_ctx(काष्ठा omap_ssi_port *omap_port)
अणु
	काष्ठा hsi_port *port = to_hsi_port(omap_port->dev);
	काष्ठा hsi_controller *ssi = to_hsi_controller(port->device.parent);
	काष्ठा omap_ssi_controller *omap_ssi = hsi_controller_drvdata(ssi);
	व्योम __iomem	*base;

	ग_लिखोl_relaxed(omap_port->sys_mpu_enable,
			omap_ssi->sys + SSI_MPU_ENABLE_REG(port->num, 0));

	/* SST context */
	base = omap_port->sst_base;
	ग_लिखोl_relaxed(omap_port->sst.frame_size, base + SSI_SST_FRAMESIZE_REG);
	ग_लिखोl_relaxed(omap_port->sst.channels, base + SSI_SST_CHANNELS_REG);
	ग_लिखोl_relaxed(omap_port->sst.arb_mode, base + SSI_SST_ARBMODE_REG);

	/* SSR context */
	base = omap_port->ssr_base;
	ग_लिखोl_relaxed(omap_port->ssr.frame_size, base + SSI_SSR_FRAMESIZE_REG);
	ग_लिखोl_relaxed(omap_port->ssr.channels, base + SSI_SSR_CHANNELS_REG);
	ग_लिखोl_relaxed(omap_port->ssr.समयout, base + SSI_SSR_TIMEOUT_REG);

	वापस 0;
पूर्ण

अटल पूर्णांक ssi_restore_port_mode(काष्ठा omap_ssi_port *omap_port)
अणु
	u32 mode;

	ग_लिखोl_relaxed(omap_port->sst.mode,
				omap_port->sst_base + SSI_SST_MODE_REG);
	ग_लिखोl_relaxed(omap_port->ssr.mode,
				omap_port->ssr_base + SSI_SSR_MODE_REG);
	/* OCP barrier */
	mode = पढ़ोl(omap_port->ssr_base + SSI_SSR_MODE_REG);

	वापस 0;
पूर्ण

अटल पूर्णांक omap_ssi_port_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा hsi_port *port = dev_get_drvdata(dev);
	काष्ठा omap_ssi_port *omap_port = hsi_port_drvdata(port);
	काष्ठा hsi_controller *ssi = to_hsi_controller(port->device.parent);
	काष्ठा omap_ssi_controller *omap_ssi = hsi_controller_drvdata(ssi);

	dev_dbg(dev, "port runtime suspend!\n");

	ssi_set_port_mode(omap_port, SSI_MODE_SLEEP);
	अगर (omap_ssi->get_loss)
		omap_port->loss_count =
				omap_ssi->get_loss(ssi->device.parent);
	ssi_save_port_ctx(omap_port);

	वापस 0;
पूर्ण

अटल पूर्णांक omap_ssi_port_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा hsi_port *port = dev_get_drvdata(dev);
	काष्ठा omap_ssi_port *omap_port = hsi_port_drvdata(port);
	काष्ठा hsi_controller *ssi = to_hsi_controller(port->device.parent);
	काष्ठा omap_ssi_controller *omap_ssi = hsi_controller_drvdata(ssi);

	dev_dbg(dev, "port runtime resume!\n");

	अगर ((omap_ssi->get_loss) && (omap_port->loss_count ==
				omap_ssi->get_loss(ssi->device.parent)))
		जाओ mode; /* We always need to restore the mode & TX भागisor */

	ssi_restore_port_ctx(omap_port);

mode:
	ssi_restore_भागisor(omap_port);
	ssi_restore_port_mode(omap_port);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops omap_ssi_port_pm_ops = अणु
	SET_RUNTIME_PM_OPS(omap_ssi_port_runसमय_suspend,
		omap_ssi_port_runसमय_resume, शून्य)
पूर्ण;

#घोषणा DEV_PM_OPS     (&omap_ssi_port_pm_ops)
#अन्यथा
#घोषणा DEV_PM_OPS     शून्य
#पूर्ण_अगर


#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id omap_ssi_port_of_match[] = अणु
	अणु .compatible = "ti,omap3-ssi-port", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, omap_ssi_port_of_match);
#अन्यथा
#घोषणा omap_ssi_port_of_match शून्य
#पूर्ण_अगर

काष्ठा platक्रमm_driver ssi_port_pdriver = अणु
	.probe = ssi_port_probe,
	.हटाओ	= ssi_port_हटाओ,
	.driver	= अणु
		.name	= "omap_ssi_port",
		.of_match_table = omap_ssi_port_of_match,
		.pm	= DEV_PM_OPS,
	पूर्ण,
पूर्ण;
