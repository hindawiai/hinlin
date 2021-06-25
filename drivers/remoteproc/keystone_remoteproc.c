<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * TI Keystone DSP remoteproc driver
 *
 * Copyright (C) 2015-2017 Texas Instruments Incorporated - http://www.ti.com/
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/workqueue.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_reserved_स्मृति.स>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/regmap.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/remoteproc.h>
#समावेश <linux/reset.h>

#समावेश "remoteproc_internal.h"

#घोषणा KEYSTONE_RPROC_LOCAL_ADDRESS_MASK	(SZ_16M - 1)

/**
 * काष्ठा keystone_rproc_mem - पूर्णांकernal memory काष्ठाure
 * @cpu_addr: MPU भव address of the memory region
 * @bus_addr: Bus address used to access the memory region
 * @dev_addr: Device address of the memory region from DSP view
 * @size: Size of the memory region
 */
काष्ठा keystone_rproc_mem अणु
	व्योम __iomem *cpu_addr;
	phys_addr_t bus_addr;
	u32 dev_addr;
	माप_प्रकार size;
पूर्ण;

/**
 * काष्ठा keystone_rproc - keystone remote processor driver काष्ठाure
 * @dev: cached device poपूर्णांकer
 * @rproc: remoteproc device handle
 * @mem: पूर्णांकernal memory regions data
 * @num_mems: number of पूर्णांकernal memory regions
 * @dev_ctrl: device control regmap handle
 * @reset: reset control handle
 * @boot_offset: boot रेजिस्टर offset in @dev_ctrl regmap
 * @irq_ring: irq entry क्रम vring
 * @irq_fault: irq entry क्रम exception
 * @kick_gpio: gpio used क्रम virtio kicks
 * @workqueue: workqueue क्रम processing virtio पूर्णांकerrupts
 */
काष्ठा keystone_rproc अणु
	काष्ठा device *dev;
	काष्ठा rproc *rproc;
	काष्ठा keystone_rproc_mem *mem;
	पूर्णांक num_mems;
	काष्ठा regmap *dev_ctrl;
	काष्ठा reset_control *reset;
	u32 boot_offset;
	पूर्णांक irq_ring;
	पूर्णांक irq_fault;
	पूर्णांक kick_gpio;
	काष्ठा work_काष्ठा workqueue;
पूर्ण;

/* Put the DSP processor पूर्णांकo reset */
अटल व्योम keystone_rproc_dsp_reset(काष्ठा keystone_rproc *ksproc)
अणु
	reset_control_निश्चित(ksproc->reset);
पूर्ण

/* Configure the boot address and boot the DSP processor */
अटल पूर्णांक keystone_rproc_dsp_boot(काष्ठा keystone_rproc *ksproc, u32 boot_addr)
अणु
	पूर्णांक ret;

	अगर (boot_addr & (SZ_1K - 1)) अणु
		dev_err(ksproc->dev, "invalid boot address 0x%x, must be aligned on a 1KB boundary\n",
			boot_addr);
		वापस -EINVAL;
	पूर्ण

	ret = regmap_ग_लिखो(ksproc->dev_ctrl, ksproc->boot_offset, boot_addr);
	अगर (ret) अणु
		dev_err(ksproc->dev, "regmap_write of boot address failed, status = %d\n",
			ret);
		वापस ret;
	पूर्ण

	reset_control_deनिश्चित(ksproc->reset);

	वापस 0;
पूर्ण

/*
 * Process the remoteproc exceptions
 *
 * The exception reporting on Keystone DSP remote processors is very simple
 * compared to the equivalent processors on the OMAP family, it is notअगरied
 * through a software-deचिन्हित specअगरic पूर्णांकerrupt source in the IPC पूर्णांकerrupt
 * generation रेजिस्टर.
 *
 * This function just invokes the rproc_report_crash to report the exception
 * to the remoteproc driver core, to trigger a recovery.
 */
अटल irqवापस_t keystone_rproc_exception_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा keystone_rproc *ksproc = dev_id;

	rproc_report_crash(ksproc->rproc, RPROC_FATAL_ERROR);

	वापस IRQ_HANDLED;
पूर्ण

/*
 * Main virtqueue message workqueue function
 *
 * This function is executed upon scheduling of the keystone remoteproc
 * driver's workqueue. The workqueue is scheduled by the vring ISR handler.
 *
 * There is no payload message indicating the virtqueue index as is the
 * हाल with mailbox-based implementations on OMAP family. As such, this
 * handler processes both the Tx and Rx virtqueue indices on every invocation.
 * The rproc_vq_पूर्णांकerrupt function can detect अगर there are new unprocessed
 * messages or not (वापसs IRQ_NONE vs IRQ_HANDLED), but there is no need
 * to check क्रम these वापस values. The index 0 triggering will process all
 * pending Rx buffers, and the index 1 triggering will process all newly
 * available Tx buffers and will wakeup any potentially blocked senders.
 *
 * NOTE:
 * 1. A payload could be added by using some of the source bits in the
 *    IPC पूर्णांकerrupt generation रेजिस्टरs, but this would need additional
 *    changes to the overall IPC stack, and currently there are no benefits
 *    of adapting that approach.
 * 2. The current logic is based on an inherent design assumption of supporting
 *    only 2 vrings, but this can be changed अगर needed.
 */
अटल व्योम handle_event(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा keystone_rproc *ksproc =
		container_of(work, काष्ठा keystone_rproc, workqueue);

	rproc_vq_पूर्णांकerrupt(ksproc->rproc, 0);
	rproc_vq_पूर्णांकerrupt(ksproc->rproc, 1);
पूर्ण

/*
 * Interrupt handler क्रम processing vring kicks from remote processor
 */
अटल irqवापस_t keystone_rproc_vring_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा keystone_rproc *ksproc = dev_id;

	schedule_work(&ksproc->workqueue);

	वापस IRQ_HANDLED;
पूर्ण

/*
 * Power up the DSP remote processor.
 *
 * This function will be invoked only after the firmware क्रम this rproc
 * was loaded, parsed successfully, and all of its resource requirements
 * were met.
 */
अटल पूर्णांक keystone_rproc_start(काष्ठा rproc *rproc)
अणु
	काष्ठा keystone_rproc *ksproc = rproc->priv;
	पूर्णांक ret;

	INIT_WORK(&ksproc->workqueue, handle_event);

	ret = request_irq(ksproc->irq_ring, keystone_rproc_vring_पूर्णांकerrupt, 0,
			  dev_name(ksproc->dev), ksproc);
	अगर (ret) अणु
		dev_err(ksproc->dev, "failed to enable vring interrupt, ret = %d\n",
			ret);
		जाओ out;
	पूर्ण

	ret = request_irq(ksproc->irq_fault, keystone_rproc_exception_पूर्णांकerrupt,
			  0, dev_name(ksproc->dev), ksproc);
	अगर (ret) अणु
		dev_err(ksproc->dev, "failed to enable exception interrupt, ret = %d\n",
			ret);
		जाओ मुक्त_vring_irq;
	पूर्ण

	ret = keystone_rproc_dsp_boot(ksproc, rproc->bootaddr);
	अगर (ret)
		जाओ मुक्त_exc_irq;

	वापस 0;

मुक्त_exc_irq:
	मुक्त_irq(ksproc->irq_fault, ksproc);
मुक्त_vring_irq:
	मुक्त_irq(ksproc->irq_ring, ksproc);
	flush_work(&ksproc->workqueue);
out:
	वापस ret;
पूर्ण

/*
 * Stop the DSP remote processor.
 *
 * This function माला_दो the DSP processor पूर्णांकo reset, and finishes processing
 * of any pending messages.
 */
अटल पूर्णांक keystone_rproc_stop(काष्ठा rproc *rproc)
अणु
	काष्ठा keystone_rproc *ksproc = rproc->priv;

	keystone_rproc_dsp_reset(ksproc);
	मुक्त_irq(ksproc->irq_fault, ksproc);
	मुक्त_irq(ksproc->irq_ring, ksproc);
	flush_work(&ksproc->workqueue);

	वापस 0;
पूर्ण

/*
 * Kick the remote processor to notअगरy about pending unprocessed messages.
 * The vqid usage is not used and is inconsequential, as the kick is perक्रमmed
 * through a simulated GPIO (a bit in an IPC पूर्णांकerrupt-triggering रेजिस्टर),
 * the remote processor is expected to process both its Tx and Rx virtqueues.
 */
अटल व्योम keystone_rproc_kick(काष्ठा rproc *rproc, पूर्णांक vqid)
अणु
	काष्ठा keystone_rproc *ksproc = rproc->priv;

	अगर (WARN_ON(ksproc->kick_gpio < 0))
		वापस;

	gpio_set_value(ksproc->kick_gpio, 1);
पूर्ण

/*
 * Custom function to translate a DSP device address (पूर्णांकernal RAMs only) to a
 * kernel भव address.  The DSPs can access their RAMs at either an पूर्णांकernal
 * address visible only from a DSP, or at the SoC-level bus address. Both these
 * addresses need to be looked through क्रम translation. The translated addresses
 * can be used either by the remoteproc core क्रम loading (when using kernel
 * remoteproc loader), or by any rpmsg bus drivers.
 */
अटल व्योम *keystone_rproc_da_to_va(काष्ठा rproc *rproc, u64 da, माप_प्रकार len, bool *is_iomem)
अणु
	काष्ठा keystone_rproc *ksproc = rproc->priv;
	व्योम __iomem *va = शून्य;
	phys_addr_t bus_addr;
	u32 dev_addr, offset;
	माप_प्रकार size;
	पूर्णांक i;

	अगर (len == 0)
		वापस शून्य;

	क्रम (i = 0; i < ksproc->num_mems; i++) अणु
		bus_addr = ksproc->mem[i].bus_addr;
		dev_addr = ksproc->mem[i].dev_addr;
		size = ksproc->mem[i].size;

		अगर (da < KEYSTONE_RPROC_LOCAL_ADDRESS_MASK) अणु
			/* handle DSP-view addresses */
			अगर ((da >= dev_addr) &&
			    ((da + len) <= (dev_addr + size))) अणु
				offset = da - dev_addr;
				va = ksproc->mem[i].cpu_addr + offset;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* handle SoC-view addresses */
			अगर ((da >= bus_addr) &&
			    (da + len) <= (bus_addr + size)) अणु
				offset = da - bus_addr;
				va = ksproc->mem[i].cpu_addr + offset;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस (__क्रमce व्योम *)va;
पूर्ण

अटल स्थिर काष्ठा rproc_ops keystone_rproc_ops = अणु
	.start		= keystone_rproc_start,
	.stop		= keystone_rproc_stop,
	.kick		= keystone_rproc_kick,
	.da_to_va	= keystone_rproc_da_to_va,
पूर्ण;

अटल पूर्णांक keystone_rproc_of_get_memories(काष्ठा platक्रमm_device *pdev,
					  काष्ठा keystone_rproc *ksproc)
अणु
	अटल स्थिर अक्षर * स्थिर mem_names[] = अणु"l2sram", "l1pram", "l1dram"पूर्ण;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource *res;
	पूर्णांक num_mems = 0;
	पूर्णांक i;

	num_mems = ARRAY_SIZE(mem_names);
	ksproc->mem = devm_kसुस्मृति(ksproc->dev, num_mems,
				   माप(*ksproc->mem), GFP_KERNEL);
	अगर (!ksproc->mem)
		वापस -ENOMEM;

	क्रम (i = 0; i < num_mems; i++) अणु
		res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM,
						   mem_names[i]);
		ksproc->mem[i].cpu_addr = devm_ioremap_resource(dev, res);
		अगर (IS_ERR(ksproc->mem[i].cpu_addr)) अणु
			dev_err(dev, "failed to parse and map %s memory\n",
				mem_names[i]);
			वापस PTR_ERR(ksproc->mem[i].cpu_addr);
		पूर्ण
		ksproc->mem[i].bus_addr = res->start;
		ksproc->mem[i].dev_addr =
				res->start & KEYSTONE_RPROC_LOCAL_ADDRESS_MASK;
		ksproc->mem[i].size = resource_size(res);

		/* zero out memories to start in a pristine state */
		स_रखो((__क्रमce व्योम *)ksproc->mem[i].cpu_addr, 0,
		       ksproc->mem[i].size);
	पूर्ण
	ksproc->num_mems = num_mems;

	वापस 0;
पूर्ण

अटल पूर्णांक keystone_rproc_of_get_dev_syscon(काष्ठा platक्रमm_device *pdev,
					    काष्ठा keystone_rproc *ksproc)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक ret;

	अगर (!of_property_पढ़ो_bool(np, "ti,syscon-dev")) अणु
		dev_err(dev, "ti,syscon-dev property is absent\n");
		वापस -EINVAL;
	पूर्ण

	ksproc->dev_ctrl =
		syscon_regmap_lookup_by_phandle(np, "ti,syscon-dev");
	अगर (IS_ERR(ksproc->dev_ctrl)) अणु
		ret = PTR_ERR(ksproc->dev_ctrl);
		वापस ret;
	पूर्ण

	अगर (of_property_पढ़ो_u32_index(np, "ti,syscon-dev", 1,
				       &ksproc->boot_offset)) अणु
		dev_err(dev, "couldn't read the boot register offset\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक keystone_rproc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा keystone_rproc *ksproc;
	काष्ठा rproc *rproc;
	पूर्णांक dsp_id;
	अक्षर *fw_name = शून्य;
	अक्षर *ढाँचा = "keystone-dsp%d-fw";
	पूर्णांक name_len = 0;
	पूर्णांक ret = 0;

	अगर (!np) अणु
		dev_err(dev, "only DT-based devices are supported\n");
		वापस -ENODEV;
	पूर्ण

	dsp_id = of_alias_get_id(np, "rproc");
	अगर (dsp_id < 0) अणु
		dev_warn(dev, "device does not have an alias id\n");
		वापस dsp_id;
	पूर्ण

	/* स्थिरruct a custom शेष fw name - subject to change in future */
	name_len = म_माप(ढाँचा); /* assuming a single digit alias */
	fw_name = devm_kzalloc(dev, name_len, GFP_KERNEL);
	अगर (!fw_name)
		वापस -ENOMEM;
	snम_लिखो(fw_name, name_len, ढाँचा, dsp_id);

	rproc = rproc_alloc(dev, dev_name(dev), &keystone_rproc_ops, fw_name,
			    माप(*ksproc));
	अगर (!rproc)
		वापस -ENOMEM;

	rproc->has_iommu = false;
	ksproc = rproc->priv;
	ksproc->rproc = rproc;
	ksproc->dev = dev;

	ret = keystone_rproc_of_get_dev_syscon(pdev, ksproc);
	अगर (ret)
		जाओ मुक्त_rproc;

	ksproc->reset = devm_reset_control_get_exclusive(dev, शून्य);
	अगर (IS_ERR(ksproc->reset)) अणु
		ret = PTR_ERR(ksproc->reset);
		जाओ मुक्त_rproc;
	पूर्ण

	/* enable घड़ी क्रम accessing DSP पूर्णांकernal memories */
	pm_runसमय_enable(dev);
	ret = pm_runसमय_get_sync(dev);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to enable clock, status = %d\n", ret);
		pm_runसमय_put_noidle(dev);
		जाओ disable_rpm;
	पूर्ण

	ret = keystone_rproc_of_get_memories(pdev, ksproc);
	अगर (ret)
		जाओ disable_clk;

	ksproc->irq_ring = platक्रमm_get_irq_byname(pdev, "vring");
	अगर (ksproc->irq_ring < 0) अणु
		ret = ksproc->irq_ring;
		जाओ disable_clk;
	पूर्ण

	ksproc->irq_fault = platक्रमm_get_irq_byname(pdev, "exception");
	अगर (ksproc->irq_fault < 0) अणु
		ret = ksproc->irq_fault;
		जाओ disable_clk;
	पूर्ण

	ksproc->kick_gpio = of_get_named_gpio_flags(np, "kick-gpios", 0, शून्य);
	अगर (ksproc->kick_gpio < 0) अणु
		ret = ksproc->kick_gpio;
		dev_err(dev, "failed to get gpio for virtio kicks, status = %d\n",
			ret);
		जाओ disable_clk;
	पूर्ण

	अगर (of_reserved_mem_device_init(dev))
		dev_warn(dev, "device does not have specific CMA pool\n");

	/* ensure the DSP is in reset beक्रमe loading firmware */
	ret = reset_control_status(ksproc->reset);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to get reset status, status = %d\n", ret);
		जाओ release_mem;
	पूर्ण अन्यथा अगर (ret == 0) अणु
		WARN(1, "device is not in reset\n");
		keystone_rproc_dsp_reset(ksproc);
	पूर्ण

	ret = rproc_add(rproc);
	अगर (ret) अणु
		dev_err(dev, "failed to add register device with remoteproc core, status = %d\n",
			ret);
		जाओ release_mem;
	पूर्ण

	platक्रमm_set_drvdata(pdev, ksproc);

	वापस 0;

release_mem:
	of_reserved_mem_device_release(dev);
disable_clk:
	pm_runसमय_put_sync(dev);
disable_rpm:
	pm_runसमय_disable(dev);
मुक्त_rproc:
	rproc_मुक्त(rproc);
	वापस ret;
पूर्ण

अटल पूर्णांक keystone_rproc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा keystone_rproc *ksproc = platक्रमm_get_drvdata(pdev);

	rproc_del(ksproc->rproc);
	pm_runसमय_put_sync(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);
	rproc_मुक्त(ksproc->rproc);
	of_reserved_mem_device_release(&pdev->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id keystone_rproc_of_match[] = अणु
	अणु .compatible = "ti,k2hk-dsp", पूर्ण,
	अणु .compatible = "ti,k2l-dsp", पूर्ण,
	अणु .compatible = "ti,k2e-dsp", पूर्ण,
	अणु .compatible = "ti,k2g-dsp", पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, keystone_rproc_of_match);

अटल काष्ठा platक्रमm_driver keystone_rproc_driver = अणु
	.probe	= keystone_rproc_probe,
	.हटाओ	= keystone_rproc_हटाओ,
	.driver	= अणु
		.name = "keystone-rproc",
		.of_match_table = keystone_rproc_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(keystone_rproc_driver);

MODULE_AUTHOR("Suman Anna <s-anna@ti.com>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("TI Keystone DSP Remoteproc driver");
