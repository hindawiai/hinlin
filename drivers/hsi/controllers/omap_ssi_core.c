<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* OMAP SSI driver.
 *
 * Copyright (C) 2010 Nokia Corporation. All rights reserved.
 * Copyright (C) 2014 Sebastian Reichel <sre@kernel.org>
 *
 * Contact: Carlos Chinea <carlos.chinea@nokia.com>
 */

#समावेश <linux/compiler.h>
#समावेश <linux/err.h>
#समावेश <linux/ioport.h>
#समावेश <linux/पन.स>
#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/delay.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/hsi/hsi.h>
#समावेश <linux/idr.h>

#समावेश "omap_ssi_regs.h"
#समावेश "omap_ssi.h"

/* For स्वतःmatically allocated device IDs */
अटल DEFINE_IDA(platक्रमm_omap_ssi_ida);

#अगर_घोषित CONFIG_DEBUG_FS
अटल पूर्णांक ssi_regs_show(काष्ठा seq_file *m, व्योम *p __maybe_unused)
अणु
	काष्ठा hsi_controller *ssi = m->निजी;
	काष्ठा omap_ssi_controller *omap_ssi = hsi_controller_drvdata(ssi);
	व्योम __iomem *sys = omap_ssi->sys;

	pm_runसमय_get_sync(ssi->device.parent);
	seq_म_लिखो(m, "REVISION\t: 0x%08x\n",  पढ़ोl(sys + SSI_REVISION_REG));
	seq_म_लिखो(m, "SYSCONFIG\t: 0x%08x\n", पढ़ोl(sys + SSI_SYSCONFIG_REG));
	seq_म_लिखो(m, "SYSSTATUS\t: 0x%08x\n", पढ़ोl(sys + SSI_SYSSTATUS_REG));
	pm_runसमय_put(ssi->device.parent);

	वापस 0;
पूर्ण

अटल पूर्णांक ssi_gdd_regs_show(काष्ठा seq_file *m, व्योम *p __maybe_unused)
अणु
	काष्ठा hsi_controller *ssi = m->निजी;
	काष्ठा omap_ssi_controller *omap_ssi = hsi_controller_drvdata(ssi);
	व्योम __iomem *gdd = omap_ssi->gdd;
	व्योम __iomem *sys = omap_ssi->sys;
	पूर्णांक lch;

	pm_runसमय_get_sync(ssi->device.parent);

	seq_म_लिखो(m, "GDD_MPU_STATUS\t: 0x%08x\n",
		पढ़ोl(sys + SSI_GDD_MPU_IRQ_STATUS_REG));
	seq_म_लिखो(m, "GDD_MPU_ENABLE\t: 0x%08x\n\n",
		पढ़ोl(sys + SSI_GDD_MPU_IRQ_ENABLE_REG));
	seq_म_लिखो(m, "HW_ID\t\t: 0x%08x\n",
				पढ़ोl(gdd + SSI_GDD_HW_ID_REG));
	seq_म_लिखो(m, "PPORT_ID\t: 0x%08x\n",
				पढ़ोl(gdd + SSI_GDD_PPORT_ID_REG));
	seq_म_लिखो(m, "MPORT_ID\t: 0x%08x\n",
				पढ़ोl(gdd + SSI_GDD_MPORT_ID_REG));
	seq_म_लिखो(m, "TEST\t\t: 0x%08x\n",
				पढ़ोl(gdd + SSI_GDD_TEST_REG));
	seq_म_लिखो(m, "GCR\t\t: 0x%08x\n",
				पढ़ोl(gdd + SSI_GDD_GCR_REG));

	क्रम (lch = 0; lch < SSI_MAX_GDD_LCH; lch++) अणु
		seq_म_लिखो(m, "\nGDD LCH %d\n=========\n", lch);
		seq_म_लिखो(m, "CSDP\t\t: 0x%04x\n",
				पढ़ोw(gdd + SSI_GDD_CSDP_REG(lch)));
		seq_म_लिखो(m, "CCR\t\t: 0x%04x\n",
				पढ़ोw(gdd + SSI_GDD_CCR_REG(lch)));
		seq_म_लिखो(m, "CICR\t\t: 0x%04x\n",
				पढ़ोw(gdd + SSI_GDD_CICR_REG(lch)));
		seq_म_लिखो(m, "CSR\t\t: 0x%04x\n",
				पढ़ोw(gdd + SSI_GDD_CSR_REG(lch)));
		seq_म_लिखो(m, "CSSA\t\t: 0x%08x\n",
				पढ़ोl(gdd + SSI_GDD_CSSA_REG(lch)));
		seq_म_लिखो(m, "CDSA\t\t: 0x%08x\n",
				पढ़ोl(gdd + SSI_GDD_CDSA_REG(lch)));
		seq_म_लिखो(m, "CEN\t\t: 0x%04x\n",
				पढ़ोw(gdd + SSI_GDD_CEN_REG(lch)));
		seq_म_लिखो(m, "CSAC\t\t: 0x%04x\n",
				पढ़ोw(gdd + SSI_GDD_CSAC_REG(lch)));
		seq_म_लिखो(m, "CDAC\t\t: 0x%04x\n",
				पढ़ोw(gdd + SSI_GDD_CDAC_REG(lch)));
		seq_म_लिखो(m, "CLNK_CTRL\t: 0x%04x\n",
				पढ़ोw(gdd + SSI_GDD_CLNK_CTRL_REG(lch)));
	पूर्ण

	pm_runसमय_put(ssi->device.parent);

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(ssi_regs);
DEFINE_SHOW_ATTRIBUTE(ssi_gdd_regs);

अटल पूर्णांक ssi_debug_add_ctrl(काष्ठा hsi_controller *ssi)
अणु
	काष्ठा omap_ssi_controller *omap_ssi = hsi_controller_drvdata(ssi);
	काष्ठा dentry *dir;

	/* SSI controller */
	omap_ssi->dir = debugfs_create_dir(dev_name(&ssi->device), शून्य);
	अगर (!omap_ssi->dir)
		वापस -ENOMEM;

	debugfs_create_file("regs", S_IRUGO, omap_ssi->dir, ssi,
								&ssi_regs_fops);
	/* SSI GDD (DMA) */
	dir = debugfs_create_dir("gdd", omap_ssi->dir);
	अगर (!dir)
		जाओ rback;
	debugfs_create_file("regs", S_IRUGO, dir, ssi, &ssi_gdd_regs_fops);

	वापस 0;
rback:
	debugfs_हटाओ_recursive(omap_ssi->dir);

	वापस -ENOMEM;
पूर्ण

अटल व्योम ssi_debug_हटाओ_ctrl(काष्ठा hsi_controller *ssi)
अणु
	काष्ठा omap_ssi_controller *omap_ssi = hsi_controller_drvdata(ssi);

	debugfs_हटाओ_recursive(omap_ssi->dir);
पूर्ण
#पूर्ण_अगर /* CONFIG_DEBUG_FS */

/*
 * FIXME: Horrible HACK needed until we हटाओ the useless wakeline test
 * in the CMT. To be हटाओd !!!!
 */
व्योम ssi_waketest(काष्ठा hsi_client *cl, अचिन्हित पूर्णांक enable)
अणु
	काष्ठा hsi_port *port = hsi_get_port(cl);
	काष्ठा omap_ssi_port *omap_port = hsi_port_drvdata(port);
	काष्ठा hsi_controller *ssi = to_hsi_controller(port->device.parent);
	काष्ठा omap_ssi_controller *omap_ssi = hsi_controller_drvdata(ssi);

	omap_port->wktest = !!enable;
	अगर (omap_port->wktest) अणु
		pm_runसमय_get_sync(ssi->device.parent);
		ग_लिखोl_relaxed(SSI_WAKE(0),
				omap_ssi->sys + SSI_SET_WAKE_REG(port->num));
	पूर्ण अन्यथा अणु
		ग_लिखोl_relaxed(SSI_WAKE(0),
				omap_ssi->sys +	SSI_CLEAR_WAKE_REG(port->num));
		pm_runसमय_put(ssi->device.parent);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(ssi_waketest);

अटल व्योम ssi_gdd_complete(काष्ठा hsi_controller *ssi, अचिन्हित पूर्णांक lch)
अणु
	काष्ठा omap_ssi_controller *omap_ssi = hsi_controller_drvdata(ssi);
	काष्ठा hsi_msg *msg = omap_ssi->gdd_trn[lch].msg;
	काष्ठा hsi_port *port = to_hsi_port(msg->cl->device.parent);
	काष्ठा omap_ssi_port *omap_port = hsi_port_drvdata(port);
	अचिन्हित पूर्णांक dir;
	u32 csr;
	u32 val;

	spin_lock(&omap_ssi->lock);

	val = पढ़ोl(omap_ssi->sys + SSI_GDD_MPU_IRQ_ENABLE_REG);
	val &= ~SSI_GDD_LCH(lch);
	ग_लिखोl_relaxed(val, omap_ssi->sys + SSI_GDD_MPU_IRQ_ENABLE_REG);

	अगर (msg->ttype == HSI_MSG_READ) अणु
		dir = DMA_FROM_DEVICE;
		val = SSI_DATAAVAILABLE(msg->channel);
		pm_runसमय_put(omap_port->pdev);
	पूर्ण अन्यथा अणु
		dir = DMA_TO_DEVICE;
		val = SSI_DATAACCEPT(msg->channel);
		/* Keep घड़ीs reference क्रम ग_लिखो pio event */
	पूर्ण
	dma_unmap_sg(&ssi->device, msg->sgt.sgl, msg->sgt.nents, dir);
	csr = पढ़ोw(omap_ssi->gdd + SSI_GDD_CSR_REG(lch));
	omap_ssi->gdd_trn[lch].msg = शून्य; /* release GDD lch */
	dev_dbg(&port->device, "DMA completed ch %d ttype %d\n",
				msg->channel, msg->ttype);
	spin_unlock(&omap_ssi->lock);
	अगर (csr & SSI_CSR_TOUR) अणु /* Timeout error */
		msg->status = HSI_STATUS_ERROR;
		msg->actual_len = 0;
		spin_lock(&omap_port->lock);
		list_del(&msg->link); /* Dequeue msg */
		spin_unlock(&omap_port->lock);

		list_add_tail(&msg->link, &omap_port->errqueue);
		schedule_delayed_work(&omap_port->errqueue_work, 0);
		वापस;
	पूर्ण
	spin_lock(&omap_port->lock);
	val |= पढ़ोl(omap_ssi->sys + SSI_MPU_ENABLE_REG(port->num, 0));
	ग_लिखोl_relaxed(val, omap_ssi->sys + SSI_MPU_ENABLE_REG(port->num, 0));
	spin_unlock(&omap_port->lock);

	msg->status = HSI_STATUS_COMPLETED;
	msg->actual_len = sg_dma_len(msg->sgt.sgl);
पूर्ण

अटल व्योम ssi_gdd_tasklet(अचिन्हित दीर्घ dev)
अणु
	काष्ठा hsi_controller *ssi = (काष्ठा hsi_controller *)dev;
	काष्ठा omap_ssi_controller *omap_ssi = hsi_controller_drvdata(ssi);
	व्योम __iomem *sys = omap_ssi->sys;
	अचिन्हित पूर्णांक lch;
	u32 status_reg;

	pm_runसमय_get(ssi->device.parent);

	अगर (!pm_runसमय_active(ssi->device.parent)) अणु
		dev_warn(ssi->device.parent, "ssi_gdd_tasklet called without runtime PM!\n");
		pm_runसमय_put(ssi->device.parent);
		वापस;
	पूर्ण

	status_reg = पढ़ोl(sys + SSI_GDD_MPU_IRQ_STATUS_REG);
	क्रम (lch = 0; lch < SSI_MAX_GDD_LCH; lch++) अणु
		अगर (status_reg & SSI_GDD_LCH(lch))
			ssi_gdd_complete(ssi, lch);
	पूर्ण
	ग_लिखोl_relaxed(status_reg, sys + SSI_GDD_MPU_IRQ_STATUS_REG);
	status_reg = पढ़ोl(sys + SSI_GDD_MPU_IRQ_STATUS_REG);

	pm_runसमय_put(ssi->device.parent);

	अगर (status_reg)
		tasklet_hi_schedule(&omap_ssi->gdd_tasklet);
	अन्यथा
		enable_irq(omap_ssi->gdd_irq);

पूर्ण

अटल irqवापस_t ssi_gdd_isr(पूर्णांक irq, व्योम *ssi)
अणु
	काष्ठा omap_ssi_controller *omap_ssi = hsi_controller_drvdata(ssi);

	tasklet_hi_schedule(&omap_ssi->gdd_tasklet);
	disable_irq_nosync(irq);

	वापस IRQ_HANDLED;
पूर्ण

अटल अचिन्हित दीर्घ ssi_get_clk_rate(काष्ठा hsi_controller *ssi)
अणु
	काष्ठा omap_ssi_controller *omap_ssi = hsi_controller_drvdata(ssi);
	अचिन्हित दीर्घ rate = clk_get_rate(omap_ssi->fck);
	वापस rate;
पूर्ण

अटल पूर्णांक ssi_clk_event(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ event,
								व्योम *data)
अणु
	काष्ठा omap_ssi_controller *omap_ssi = container_of(nb,
					काष्ठा omap_ssi_controller, fck_nb);
	काष्ठा hsi_controller *ssi = to_hsi_controller(omap_ssi->dev);
	काष्ठा clk_notअगरier_data *clk_data = data;
	काष्ठा omap_ssi_port *omap_port;
	पूर्णांक i;

	चयन (event) अणु
	हाल PRE_RATE_CHANGE:
		dev_dbg(&ssi->device, "pre rate change\n");

		क्रम (i = 0; i < ssi->num_ports; i++) अणु
			omap_port = omap_ssi->port[i];

			अगर (!omap_port)
				जारी;

			/* Workaround क्रम SWBREAK + CAwake करोwn race in CMT */
			disable_irq(omap_port->wake_irq);

			/* stop all ssi communication */
			pinctrl_pm_select_idle_state(omap_port->pdev);
			udelay(1); /* रुको क्रम racing frames */
		पूर्ण

		अवरोध;
	हाल ABORT_RATE_CHANGE:
		dev_dbg(&ssi->device, "abort rate change\n");
		fallthrough;
	हाल POST_RATE_CHANGE:
		dev_dbg(&ssi->device, "post rate change (%lu -> %lu)\n",
			clk_data->old_rate, clk_data->new_rate);
		omap_ssi->fck_rate = DIV_ROUND_CLOSEST(clk_data->new_rate, 1000); /* kHz */

		क्रम (i = 0; i < ssi->num_ports; i++) अणु
			omap_port = omap_ssi->port[i];

			अगर (!omap_port)
				जारी;

			omap_ssi_port_update_fclk(ssi, omap_port);

			/* resume ssi communication */
			pinctrl_pm_select_शेष_state(omap_port->pdev);
			enable_irq(omap_port->wake_irq);
		पूर्ण

		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक ssi_get_iomem(काष्ठा platक्रमm_device *pd,
		स्थिर अक्षर *name, व्योम __iomem **pbase, dma_addr_t *phy)
अणु
	काष्ठा resource *mem;
	व्योम __iomem *base;
	काष्ठा hsi_controller *ssi = platक्रमm_get_drvdata(pd);

	mem = platक्रमm_get_resource_byname(pd, IORESOURCE_MEM, name);
	base = devm_ioremap_resource(&ssi->device, mem);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	*pbase = base;

	अगर (phy)
		*phy = mem->start;

	वापस 0;
पूर्ण

अटल पूर्णांक ssi_add_controller(काष्ठा hsi_controller *ssi,
						काष्ठा platक्रमm_device *pd)
अणु
	काष्ठा omap_ssi_controller *omap_ssi;
	पूर्णांक err;

	omap_ssi = devm_kzalloc(&ssi->device, माप(*omap_ssi), GFP_KERNEL);
	अगर (!omap_ssi)
		वापस -ENOMEM;

	err = ida_simple_get(&platक्रमm_omap_ssi_ida, 0, 0, GFP_KERNEL);
	अगर (err < 0)
		वापस err;
	ssi->id = err;

	ssi->owner = THIS_MODULE;
	ssi->device.parent = &pd->dev;
	dev_set_name(&ssi->device, "ssi%d", ssi->id);
	hsi_controller_set_drvdata(ssi, omap_ssi);
	omap_ssi->dev = &ssi->device;
	err = ssi_get_iomem(pd, "sys", &omap_ssi->sys, शून्य);
	अगर (err < 0)
		जाओ out_err;
	err = ssi_get_iomem(pd, "gdd", &omap_ssi->gdd, शून्य);
	अगर (err < 0)
		जाओ out_err;
	err = platक्रमm_get_irq_byname(pd, "gdd_mpu");
	अगर (err < 0)
		जाओ out_err;
	omap_ssi->gdd_irq = err;
	tasklet_init(&omap_ssi->gdd_tasklet, ssi_gdd_tasklet,
							(अचिन्हित दीर्घ)ssi);
	err = devm_request_irq(&ssi->device, omap_ssi->gdd_irq, ssi_gdd_isr,
						0, "gdd_mpu", ssi);
	अगर (err < 0) अणु
		dev_err(&ssi->device, "Request GDD IRQ %d failed (%d)",
							omap_ssi->gdd_irq, err);
		जाओ out_err;
	पूर्ण

	omap_ssi->port = devm_kसुस्मृति(&ssi->device, ssi->num_ports,
				      माप(*omap_ssi->port), GFP_KERNEL);
	अगर (!omap_ssi->port) अणु
		err = -ENOMEM;
		जाओ out_err;
	पूर्ण

	omap_ssi->fck = devm_clk_get(&ssi->device, "ssi_ssr_fck");
	अगर (IS_ERR(omap_ssi->fck)) अणु
		dev_err(&pd->dev, "Could not acquire clock \"ssi_ssr_fck\": %li\n",
			PTR_ERR(omap_ssi->fck));
		err = -ENODEV;
		जाओ out_err;
	पूर्ण

	omap_ssi->fck_nb.notअगरier_call = ssi_clk_event;
	omap_ssi->fck_nb.priority = पूर्णांक_उच्च;
	clk_notअगरier_रेजिस्टर(omap_ssi->fck, &omap_ssi->fck_nb);

	/* TODO: find रेजिस्टर, which can be used to detect context loss */
	omap_ssi->get_loss = शून्य;

	omap_ssi->max_speed = अच_पूर्णांक_उच्च;
	spin_lock_init(&omap_ssi->lock);
	err = hsi_रेजिस्टर_controller(ssi);

	अगर (err < 0)
		जाओ out_err;

	वापस 0;

out_err:
	ida_simple_हटाओ(&platक्रमm_omap_ssi_ida, ssi->id);
	वापस err;
पूर्ण

अटल पूर्णांक ssi_hw_init(काष्ठा hsi_controller *ssi)
अणु
	काष्ठा omap_ssi_controller *omap_ssi = hsi_controller_drvdata(ssi);
	पूर्णांक err;

	err = pm_runसमय_resume_and_get(ssi->device.parent);
	अगर (err < 0) अणु
		dev_err(&ssi->device, "runtime PM failed %d\n", err);
		वापस err;
	पूर्ण
	/* Resetting GDD */
	ग_लिखोl_relaxed(SSI_SWRESET, omap_ssi->gdd + SSI_GDD_GRST_REG);
	/* Get FCK rate in kHz */
	omap_ssi->fck_rate = DIV_ROUND_CLOSEST(ssi_get_clk_rate(ssi), 1000);
	dev_dbg(&ssi->device, "SSI fck rate %lu kHz\n", omap_ssi->fck_rate);

	ग_लिखोl_relaxed(SSI_CLK_AUTOGATING_ON, omap_ssi->sys + SSI_GDD_GCR_REG);
	omap_ssi->gdd_gcr = SSI_CLK_AUTOGATING_ON;
	pm_runसमय_put_sync(ssi->device.parent);

	वापस 0;
पूर्ण

अटल व्योम ssi_हटाओ_controller(काष्ठा hsi_controller *ssi)
अणु
	काष्ठा omap_ssi_controller *omap_ssi = hsi_controller_drvdata(ssi);
	पूर्णांक id = ssi->id;
	tasklet_समाप्त(&omap_ssi->gdd_tasklet);
	hsi_unरेजिस्टर_controller(ssi);
	clk_notअगरier_unरेजिस्टर(omap_ssi->fck, &omap_ssi->fck_nb);
	ida_simple_हटाओ(&platक्रमm_omap_ssi_ida, id);
पूर्ण

अटल अंतरभूत पूर्णांक ssi_of_get_available_ports_count(स्थिर काष्ठा device_node *np)
अणु
	काष्ठा device_node *child;
	पूर्णांक num = 0;

	क्रम_each_available_child_of_node(np, child)
		अगर (of_device_is_compatible(child, "ti,omap3-ssi-port"))
			num++;

	वापस num;
पूर्ण

अटल पूर्णांक ssi_हटाओ_ports(काष्ठा device *dev, व्योम *c)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);

	अगर (!dev->of_node)
		वापस 0;

	of_node_clear_flag(dev->of_node, OF_POPULATED);
	of_device_unरेजिस्टर(pdev);

	वापस 0;
पूर्ण

अटल पूर्णांक ssi_probe(काष्ठा platक्रमm_device *pd)
अणु
	काष्ठा platक्रमm_device *childpdev;
	काष्ठा device_node *np = pd->dev.of_node;
	काष्ठा device_node *child;
	काष्ठा hsi_controller *ssi;
	पूर्णांक err;
	पूर्णांक num_ports;

	अगर (!np) अणु
		dev_err(&pd->dev, "missing device tree data\n");
		वापस -EINVAL;
	पूर्ण

	num_ports = ssi_of_get_available_ports_count(np);

	ssi = hsi_alloc_controller(num_ports, GFP_KERNEL);
	अगर (!ssi) अणु
		dev_err(&pd->dev, "No memory for controller\n");
		वापस -ENOMEM;
	पूर्ण

	platक्रमm_set_drvdata(pd, ssi);

	err = ssi_add_controller(ssi, pd);
	अगर (err < 0)
		जाओ out1;

	pm_runसमय_enable(&pd->dev);

	err = ssi_hw_init(ssi);
	अगर (err < 0)
		जाओ out2;
#अगर_घोषित CONFIG_DEBUG_FS
	err = ssi_debug_add_ctrl(ssi);
	अगर (err < 0)
		जाओ out2;
#पूर्ण_अगर

	क्रम_each_available_child_of_node(np, child) अणु
		अगर (!of_device_is_compatible(child, "ti,omap3-ssi-port"))
			जारी;

		childpdev = of_platक्रमm_device_create(child, शून्य, &pd->dev);
		अगर (!childpdev) अणु
			err = -ENODEV;
			dev_err(&pd->dev, "failed to create ssi controller port\n");
			जाओ out3;
		पूर्ण
	पूर्ण

	dev_info(&pd->dev, "ssi controller %d initialized (%d ports)!\n",
		ssi->id, num_ports);
	वापस err;
out3:
	device_क्रम_each_child(&pd->dev, शून्य, ssi_हटाओ_ports);
out2:
	ssi_हटाओ_controller(ssi);
out1:
	platक्रमm_set_drvdata(pd, शून्य);
	pm_runसमय_disable(&pd->dev);

	वापस err;
पूर्ण

अटल पूर्णांक ssi_हटाओ(काष्ठा platक्रमm_device *pd)
अणु
	काष्ठा hsi_controller *ssi = platक्रमm_get_drvdata(pd);

	/* cleanup of of_platक्रमm_populate() call */
	device_क्रम_each_child(&pd->dev, शून्य, ssi_हटाओ_ports);

#अगर_घोषित CONFIG_DEBUG_FS
	ssi_debug_हटाओ_ctrl(ssi);
#पूर्ण_अगर
	ssi_हटाओ_controller(ssi);
	platक्रमm_set_drvdata(pd, शून्य);

	pm_runसमय_disable(&pd->dev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक omap_ssi_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा hsi_controller *ssi = dev_get_drvdata(dev);
	काष्ठा omap_ssi_controller *omap_ssi = hsi_controller_drvdata(ssi);

	dev_dbg(dev, "runtime suspend!\n");

	अगर (omap_ssi->get_loss)
		omap_ssi->loss_count =
				omap_ssi->get_loss(ssi->device.parent);

	वापस 0;
पूर्ण

अटल पूर्णांक omap_ssi_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा hsi_controller *ssi = dev_get_drvdata(dev);
	काष्ठा omap_ssi_controller *omap_ssi = hsi_controller_drvdata(ssi);

	dev_dbg(dev, "runtime resume!\n");

	अगर ((omap_ssi->get_loss) && (omap_ssi->loss_count ==
				omap_ssi->get_loss(ssi->device.parent)))
		वापस 0;

	ग_लिखोl_relaxed(omap_ssi->gdd_gcr, omap_ssi->gdd + SSI_GDD_GCR_REG);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops omap_ssi_pm_ops = अणु
	SET_RUNTIME_PM_OPS(omap_ssi_runसमय_suspend, omap_ssi_runसमय_resume,
		शून्य)
पूर्ण;

#घोषणा DEV_PM_OPS     (&omap_ssi_pm_ops)
#अन्यथा
#घोषणा DEV_PM_OPS     शून्य
#पूर्ण_अगर

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id omap_ssi_of_match[] = अणु
	अणु .compatible = "ti,omap3-ssi", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, omap_ssi_of_match);
#अन्यथा
#घोषणा omap_ssi_of_match शून्य
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver ssi_pdriver = अणु
	.probe = ssi_probe,
	.हटाओ	= ssi_हटाओ,
	.driver	= अणु
		.name	= "omap_ssi",
		.pm     = DEV_PM_OPS,
		.of_match_table = omap_ssi_of_match,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init ssi_init(व्योम) अणु
	पूर्णांक ret;

	ret = platक्रमm_driver_रेजिस्टर(&ssi_pdriver);
	अगर (ret)
		वापस ret;

	वापस platक्रमm_driver_रेजिस्टर(&ssi_port_pdriver);
पूर्ण
module_init(ssi_init);

अटल व्योम __निकास ssi_निकास(व्योम) अणु
	platक्रमm_driver_unरेजिस्टर(&ssi_port_pdriver);
	platक्रमm_driver_unरेजिस्टर(&ssi_pdriver);
पूर्ण
module_निकास(ssi_निकास);

MODULE_ALIAS("platform:omap_ssi");
MODULE_AUTHOR("Carlos Chinea <carlos.chinea@nokia.com>");
MODULE_AUTHOR("Sebastian Reichel <sre@kernel.org>");
MODULE_DESCRIPTION("Synchronous Serial Interface Driver");
MODULE_LICENSE("GPL v2");
