<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Remote processor machine-specअगरic module क्रम DA8XX
 *
 * Copyright (C) 2013 Texas Instruments, Inc.
 */

#समावेश <linux/bitops.h>
#समावेश <linux/clk.h>
#समावेश <linux/reset.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_reserved_स्मृति.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/remoteproc.h>

#समावेश "remoteproc_internal.h"

अटल अक्षर *da8xx_fw_name;
module_param(da8xx_fw_name, अक्षरp, 0444);
MODULE_PARM_DESC(da8xx_fw_name,
		 "Name of DSP firmware file in /lib/firmware (if not specified defaults to 'rproc-dsp-fw')");

/*
 * OMAP-L138 Technical References:
 * http://www.ti.com/product/omap-l138
 */
#घोषणा SYSCFG_CHIPSIG0 BIT(0)
#घोषणा SYSCFG_CHIPSIG1 BIT(1)
#घोषणा SYSCFG_CHIPSIG2 BIT(2)
#घोषणा SYSCFG_CHIPSIG3 BIT(3)
#घोषणा SYSCFG_CHIPSIG4 BIT(4)

#घोषणा DA8XX_RPROC_LOCAL_ADDRESS_MASK	(SZ_16M - 1)

/**
 * काष्ठा da8xx_rproc_mem - पूर्णांकernal memory काष्ठाure
 * @cpu_addr: MPU भव address of the memory region
 * @bus_addr: Bus address used to access the memory region
 * @dev_addr: Device address of the memory region from DSP view
 * @size: Size of the memory region
 */
काष्ठा da8xx_rproc_mem अणु
	व्योम __iomem *cpu_addr;
	phys_addr_t bus_addr;
	u32 dev_addr;
	माप_प्रकार size;
पूर्ण;

/**
 * काष्ठा da8xx_rproc - da8xx remote processor instance state
 * @rproc: rproc handle
 * @mem: पूर्णांकernal memory regions data
 * @num_mems: number of पूर्णांकernal memory regions
 * @dsp_clk: placeholder क्रम platक्रमm's DSP clk
 * @ack_fxn: chip-specअगरic ack function क्रम ack'ing irq
 * @irq_data: ack_fxn function parameter
 * @chipsig: virt ptr to DSP पूर्णांकerrupt रेजिस्टरs (CHIPSIG & CHIPSIG_CLR)
 * @bootreg: virt ptr to DSP boot address रेजिस्टर (HOST1CFG)
 * @irq: irq # used by this instance
 */
काष्ठा da8xx_rproc अणु
	काष्ठा rproc *rproc;
	काष्ठा da8xx_rproc_mem *mem;
	पूर्णांक num_mems;
	काष्ठा clk *dsp_clk;
	काष्ठा reset_control *dsp_reset;
	व्योम (*ack_fxn)(काष्ठा irq_data *data);
	काष्ठा irq_data *irq_data;
	व्योम __iomem *chipsig;
	व्योम __iomem *bootreg;
	पूर्णांक irq;
पूर्ण;

/**
 * handle_event() - inbound virtqueue message workqueue function
 *
 * This function is रेजिस्टरed as a kernel thपढ़ो and is scheduled by the
 * kernel handler.
 */
अटल irqवापस_t handle_event(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा rproc *rproc = (काष्ठा rproc *)p;

	/* Process incoming buffers on all our vrings */
	rproc_vq_पूर्णांकerrupt(rproc, 0);
	rproc_vq_पूर्णांकerrupt(rproc, 1);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * da8xx_rproc_callback() - inbound virtqueue message handler
 *
 * This handler is invoked directly by the kernel whenever the remote
 * core (DSP) has modअगरied the state of a virtqueue.  There is no
 * "payload" message indicating the virtqueue index as is the हाल with
 * mailbox-based implementations on OMAP4.  As such, this handler "polls"
 * each known virtqueue index क्रम every invocation.
 */
अटल irqवापस_t da8xx_rproc_callback(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा rproc *rproc = (काष्ठा rproc *)p;
	काष्ठा da8xx_rproc *drproc = (काष्ठा da8xx_rproc *)rproc->priv;
	u32 chipsig;

	chipsig = पढ़ोl(drproc->chipsig);
	अगर (chipsig & SYSCFG_CHIPSIG0) अणु
		/* Clear पूर्णांकerrupt level source */
		ग_लिखोl(SYSCFG_CHIPSIG0, drproc->chipsig + 4);

		/*
		 * ACK पूर्णांकr to AINTC.
		 *
		 * It has alपढ़ोy been ack'ed by the kernel beक्रमe calling
		 * this function, but since the ARM<->DSP पूर्णांकerrupts in the
		 * CHIPSIG रेजिस्टर are "level" instead of "pulse" variety,
		 * we need to ack it after taking करोwn the level अन्यथा we'll
		 * be called again immediately after वापसing.
		 */
		drproc->ack_fxn(drproc->irq_data);

		वापस IRQ_WAKE_THREAD;
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक da8xx_rproc_start(काष्ठा rproc *rproc)
अणु
	काष्ठा device *dev = rproc->dev.parent;
	काष्ठा da8xx_rproc *drproc = (काष्ठा da8xx_rproc *)rproc->priv;
	काष्ठा clk *dsp_clk = drproc->dsp_clk;
	काष्ठा reset_control *dsp_reset = drproc->dsp_reset;
	पूर्णांक ret;

	/* hw requires the start (boot) address be on 1KB boundary */
	अगर (rproc->bootaddr & 0x3ff) अणु
		dev_err(dev, "invalid boot address: must be aligned to 1KB\n");

		वापस -EINVAL;
	पूर्ण

	ग_लिखोl(rproc->bootaddr, drproc->bootreg);

	ret = clk_prepare_enable(dsp_clk);
	अगर (ret) अणु
		dev_err(dev, "clk_prepare_enable() failed: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = reset_control_deनिश्चित(dsp_reset);
	अगर (ret) अणु
		dev_err(dev, "reset_control_deassert() failed: %d\n", ret);
		clk_disable_unprepare(dsp_clk);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक da8xx_rproc_stop(काष्ठा rproc *rproc)
अणु
	काष्ठा da8xx_rproc *drproc = rproc->priv;
	काष्ठा device *dev = rproc->dev.parent;
	पूर्णांक ret;

	ret = reset_control_निश्चित(drproc->dsp_reset);
	अगर (ret) अणु
		dev_err(dev, "reset_control_assert() failed: %d\n", ret);
		वापस ret;
	पूर्ण

	clk_disable_unprepare(drproc->dsp_clk);

	वापस 0;
पूर्ण

/* kick a virtqueue */
अटल व्योम da8xx_rproc_kick(काष्ठा rproc *rproc, पूर्णांक vqid)
अणु
	काष्ठा da8xx_rproc *drproc = (काष्ठा da8xx_rproc *)rproc->priv;

	/* Interrupt remote proc */
	ग_लिखोl(SYSCFG_CHIPSIG2, drproc->chipsig);
पूर्ण

अटल स्थिर काष्ठा rproc_ops da8xx_rproc_ops = अणु
	.start = da8xx_rproc_start,
	.stop = da8xx_rproc_stop,
	.kick = da8xx_rproc_kick,
पूर्ण;

अटल पूर्णांक da8xx_rproc_get_पूर्णांकernal_memories(काष्ठा platक्रमm_device *pdev,
					     काष्ठा da8xx_rproc *drproc)
अणु
	अटल स्थिर अक्षर * स्थिर mem_names[] = अणु"l2sram", "l1pram", "l1dram"पूर्ण;
	पूर्णांक num_mems = ARRAY_SIZE(mem_names);
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource *res;
	पूर्णांक i;

	drproc->mem = devm_kसुस्मृति(dev, num_mems, माप(*drproc->mem),
				   GFP_KERNEL);
	अगर (!drproc->mem)
		वापस -ENOMEM;

	क्रम (i = 0; i < num_mems; i++) अणु
		res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM,
						   mem_names[i]);
		drproc->mem[i].cpu_addr = devm_ioremap_resource(dev, res);
		अगर (IS_ERR(drproc->mem[i].cpu_addr)) अणु
			dev_err(dev, "failed to parse and map %s memory\n",
				mem_names[i]);
			वापस PTR_ERR(drproc->mem[i].cpu_addr);
		पूर्ण
		drproc->mem[i].bus_addr = res->start;
		drproc->mem[i].dev_addr =
				res->start & DA8XX_RPROC_LOCAL_ADDRESS_MASK;
		drproc->mem[i].size = resource_size(res);

		dev_dbg(dev, "memory %8s: bus addr %pa size 0x%zx va %p da 0x%x\n",
			mem_names[i], &drproc->mem[i].bus_addr,
			drproc->mem[i].size, drproc->mem[i].cpu_addr,
			drproc->mem[i].dev_addr);
	पूर्ण
	drproc->num_mems = num_mems;

	वापस 0;
पूर्ण

अटल पूर्णांक da8xx_rproc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा da8xx_rproc *drproc;
	काष्ठा rproc *rproc;
	काष्ठा irq_data *irq_data;
	काष्ठा resource *bootreg_res;
	काष्ठा resource *chipsig_res;
	काष्ठा clk *dsp_clk;
	काष्ठा reset_control *dsp_reset;
	व्योम __iomem *chipsig;
	व्योम __iomem *bootreg;
	पूर्णांक irq;
	पूर्णांक ret;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	irq_data = irq_get_irq_data(irq);
	अगर (!irq_data) अणु
		dev_err(dev, "irq_get_irq_data(%d): NULL\n", irq);
		वापस -EINVAL;
	पूर्ण

	bootreg_res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM,
						   "host1cfg");
	bootreg = devm_ioremap_resource(dev, bootreg_res);
	अगर (IS_ERR(bootreg))
		वापस PTR_ERR(bootreg);

	chipsig_res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM,
						   "chipsig");
	chipsig = devm_ioremap_resource(dev, chipsig_res);
	अगर (IS_ERR(chipsig))
		वापस PTR_ERR(chipsig);

	dsp_clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(dsp_clk)) अणु
		dev_err(dev, "clk_get error: %ld\n", PTR_ERR(dsp_clk));

		वापस PTR_ERR(dsp_clk);
	पूर्ण

	dsp_reset = devm_reset_control_get_exclusive(dev, शून्य);
	अगर (IS_ERR(dsp_reset)) अणु
		अगर (PTR_ERR(dsp_reset) != -EPROBE_DEFER)
			dev_err(dev, "unable to get reset control: %ld\n",
				PTR_ERR(dsp_reset));

		वापस PTR_ERR(dsp_reset);
	पूर्ण

	अगर (dev->of_node) अणु
		ret = of_reserved_mem_device_init(dev);
		अगर (ret) अणु
			dev_err(dev, "device does not have specific CMA pool: %d\n",
				ret);
			वापस ret;
		पूर्ण
	पूर्ण

	rproc = rproc_alloc(dev, "dsp", &da8xx_rproc_ops, da8xx_fw_name,
		माप(*drproc));
	अगर (!rproc) अणु
		ret = -ENOMEM;
		जाओ मुक्त_mem;
	पूर्ण

	/* error recovery is not supported at present */
	rproc->recovery_disabled = true;

	drproc = rproc->priv;
	drproc->rproc = rproc;
	drproc->dsp_clk = dsp_clk;
	drproc->dsp_reset = dsp_reset;
	rproc->has_iommu = false;

	ret = da8xx_rproc_get_पूर्णांकernal_memories(pdev, drproc);
	अगर (ret)
		जाओ मुक्त_rproc;

	platक्रमm_set_drvdata(pdev, rproc);

	/* everything the ISR needs is now setup, so hook it up */
	ret = devm_request_thपढ़ोed_irq(dev, irq, da8xx_rproc_callback,
					handle_event, 0, "da8xx-remoteproc",
					rproc);
	अगर (ret) अणु
		dev_err(dev, "devm_request_threaded_irq error: %d\n", ret);
		जाओ मुक्त_rproc;
	पूर्ण

	/*
	 * rproc_add() can end up enabling the DSP's clk with the DSP
	 * *not* in reset, but da8xx_rproc_start() needs the DSP to be
	 * held in reset at the समय it is called.
	 */
	ret = reset_control_निश्चित(dsp_reset);
	अगर (ret)
		जाओ मुक्त_rproc;

	drproc->chipsig = chipsig;
	drproc->bootreg = bootreg;
	drproc->ack_fxn = irq_data->chip->irq_ack;
	drproc->irq_data = irq_data;
	drproc->irq = irq;

	ret = rproc_add(rproc);
	अगर (ret) अणु
		dev_err(dev, "rproc_add failed: %d\n", ret);
		जाओ मुक्त_rproc;
	पूर्ण

	वापस 0;

मुक्त_rproc:
	rproc_मुक्त(rproc);
मुक्त_mem:
	अगर (dev->of_node)
		of_reserved_mem_device_release(dev);
	वापस ret;
पूर्ण

अटल पूर्णांक da8xx_rproc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rproc *rproc = platक्रमm_get_drvdata(pdev);
	काष्ठा da8xx_rproc *drproc = (काष्ठा da8xx_rproc *)rproc->priv;
	काष्ठा device *dev = &pdev->dev;

	/*
	 * The devm subप्रणाली might end up releasing things beक्रमe
	 * मुक्तing the irq, thus allowing an पूर्णांकerrupt to sneak in जबतक
	 * the device is being हटाओd.  This should prevent that.
	 */
	disable_irq(drproc->irq);

	rproc_del(rproc);
	rproc_मुक्त(rproc);
	अगर (dev->of_node)
		of_reserved_mem_device_release(dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id davinci_rproc_of_match[] __maybe_unused = अणु
	अणु .compatible = "ti,da850-dsp", पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, davinci_rproc_of_match);

अटल काष्ठा platक्रमm_driver da8xx_rproc_driver = अणु
	.probe = da8xx_rproc_probe,
	.हटाओ = da8xx_rproc_हटाओ,
	.driver = अणु
		.name = "davinci-rproc",
		.of_match_table = of_match_ptr(davinci_rproc_of_match),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(da8xx_rproc_driver);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("DA8XX Remote Processor control driver");
