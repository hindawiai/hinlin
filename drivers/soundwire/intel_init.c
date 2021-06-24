<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR BSD-3-Clause)
// Copyright(c) 2015-17 Intel Corporation.

/*
 * SDW Intel Init Routines
 *
 * Initializes and creates SDW devices based on ACPI and Hardware values
 */

#समावेश <linux/acpi.h>
#समावेश <linux/export.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/soundwire/sdw_पूर्णांकel.h>
#समावेश "cadence_master.h"
#समावेश "intel.h"

#घोषणा SDW_SHIM_LCAP		0x0
#घोषणा SDW_SHIM_BASE		0x2C000
#घोषणा SDW_ALH_BASE		0x2C800
#घोषणा SDW_LINK_BASE		0x30000
#घोषणा SDW_LINK_SIZE		0x10000

अटल पूर्णांक sdw_पूर्णांकel_cleanup(काष्ठा sdw_पूर्णांकel_ctx *ctx)
अणु
	काष्ठा sdw_पूर्णांकel_link_res *link = ctx->links;
	u32 link_mask;
	पूर्णांक i;

	अगर (!link)
		वापस 0;

	link_mask = ctx->link_mask;

	क्रम (i = 0; i < ctx->count; i++, link++) अणु
		अगर (!(link_mask & BIT(i)))
			जारी;

		अगर (link->pdev) अणु
			pm_runसमय_disable(&link->pdev->dev);
			platक्रमm_device_unरेजिस्टर(link->pdev);
		पूर्ण

		अगर (!link->घड़ी_stop_quirks)
			pm_runसमय_put_noidle(link->dev);
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा HDA_DSP_REG_ADSPIC2             (0x10)
#घोषणा HDA_DSP_REG_ADSPIS2             (0x14)
#घोषणा HDA_DSP_REG_ADSPIC2_SNDW        BIT(5)

/**
 * sdw_पूर्णांकel_enable_irq() - enable/disable Intel SoundWire IRQ
 * @mmio_base: The mmio base of the control रेजिस्टर
 * @enable: true अगर enable
 */
व्योम sdw_पूर्णांकel_enable_irq(व्योम __iomem *mmio_base, bool enable)
अणु
	u32 val;

	val = पढ़ोl(mmio_base + HDA_DSP_REG_ADSPIC2);

	अगर (enable)
		val |= HDA_DSP_REG_ADSPIC2_SNDW;
	अन्यथा
		val &= ~HDA_DSP_REG_ADSPIC2_SNDW;

	ग_लिखोl(val, mmio_base + HDA_DSP_REG_ADSPIC2);
पूर्ण
EXPORT_SYMBOL_NS(sdw_पूर्णांकel_enable_irq, SOUNDWIRE_INTEL_INIT);

irqवापस_t sdw_पूर्णांकel_thपढ़ो(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा sdw_पूर्णांकel_ctx *ctx = dev_id;
	काष्ठा sdw_पूर्णांकel_link_res *link;

	list_क्रम_each_entry(link, &ctx->link_list, list)
		sdw_cdns_irq(irq, link->cdns);

	sdw_पूर्णांकel_enable_irq(ctx->mmio_base, true);
	वापस IRQ_HANDLED;
पूर्ण
EXPORT_SYMBOL_NS(sdw_पूर्णांकel_thपढ़ो, SOUNDWIRE_INTEL_INIT);

अटल काष्ठा sdw_पूर्णांकel_ctx
*sdw_पूर्णांकel_probe_controller(काष्ठा sdw_पूर्णांकel_res *res)
अणु
	काष्ठा platक्रमm_device_info pdevinfo;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा sdw_पूर्णांकel_link_res *link;
	काष्ठा sdw_पूर्णांकel_ctx *ctx;
	काष्ठा acpi_device *adev;
	काष्ठा sdw_slave *slave;
	काष्ठा list_head *node;
	काष्ठा sdw_bus *bus;
	u32 link_mask;
	पूर्णांक num_slaves = 0;
	पूर्णांक count;
	पूर्णांक i;

	अगर (!res)
		वापस शून्य;

	अगर (acpi_bus_get_device(res->handle, &adev))
		वापस शून्य;

	अगर (!res->count)
		वापस शून्य;

	count = res->count;
	dev_dbg(&adev->dev, "Creating %d SDW Link devices\n", count);

	ctx = devm_kzalloc(&adev->dev, माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस शून्य;

	ctx->count = count;
	ctx->links = devm_kसुस्मृति(&adev->dev, ctx->count,
				  माप(*ctx->links), GFP_KERNEL);
	अगर (!ctx->links)
		वापस शून्य;

	ctx->count = count;
	ctx->mmio_base = res->mmio_base;
	ctx->link_mask = res->link_mask;
	ctx->handle = res->handle;
	mutex_init(&ctx->shim_lock);

	link = ctx->links;
	link_mask = ctx->link_mask;

	INIT_LIST_HEAD(&ctx->link_list);

	/* Create SDW Master devices */
	क्रम (i = 0; i < count; i++, link++) अणु
		अगर (!(link_mask & BIT(i))) अणु
			dev_dbg(&adev->dev,
				"Link %d masked, will not be enabled\n", i);
			जारी;
		पूर्ण

		link->mmio_base = res->mmio_base;
		link->रेजिस्टरs = res->mmio_base + SDW_LINK_BASE
			+ (SDW_LINK_SIZE * i);
		link->shim = res->mmio_base + SDW_SHIM_BASE;
		link->alh = res->mmio_base + SDW_ALH_BASE;

		link->ops = res->ops;
		link->dev = res->dev;

		link->घड़ी_stop_quirks = res->घड़ी_stop_quirks;
		link->shim_lock = &ctx->shim_lock;
		link->shim_mask = &ctx->shim_mask;
		link->link_mask = link_mask;

		स_रखो(&pdevinfo, 0, माप(pdevinfo));

		pdevinfo.parent = res->parent;
		pdevinfo.name = "intel-sdw";
		pdevinfo.id = i;
		pdevinfo.fwnode = acpi_fwnode_handle(adev);
		pdevinfo.data = link;
		pdevinfo.size_data = माप(*link);

		pdev = platक्रमm_device_रेजिस्टर_full(&pdevinfo);
		अगर (IS_ERR(pdev)) अणु
			dev_err(&adev->dev,
				"platform device creation failed: %ld\n",
				PTR_ERR(pdev));
			जाओ err;
		पूर्ण
		link->pdev = pdev;
		link->cdns = platक्रमm_get_drvdata(pdev);

		अगर (!link->cdns) अणु
			dev_err(&adev->dev, "failed to get link->cdns\n");
			/*
			 * 1 will be subtracted from i in the err label, but we need to call
			 * पूर्णांकel_link_dev_unरेजिस्टर क्रम this ldev, so plus 1 now
			 */
			i++;
			जाओ err;
		पूर्ण
		list_add_tail(&link->list, &ctx->link_list);
		bus = &link->cdns->bus;
		/* Calculate number of slaves */
		list_क्रम_each(node, &bus->slaves)
			num_slaves++;
	पूर्ण

	ctx->ids = devm_kसुस्मृति(&adev->dev, num_slaves,
				माप(*ctx->ids), GFP_KERNEL);
	अगर (!ctx->ids)
		जाओ err;

	ctx->num_slaves = num_slaves;
	i = 0;
	list_क्रम_each_entry(link, &ctx->link_list, list) अणु
		bus = &link->cdns->bus;
		list_क्रम_each_entry(slave, &bus->slaves, node) अणु
			ctx->ids[i].id = slave->id;
			ctx->ids[i].link_id = bus->link_id;
			i++;
		पूर्ण
	पूर्ण

	वापस ctx;

err:
	ctx->count = i;
	sdw_पूर्णांकel_cleanup(ctx);
	वापस शून्य;
पूर्ण

अटल पूर्णांक
sdw_पूर्णांकel_startup_controller(काष्ठा sdw_पूर्णांकel_ctx *ctx)
अणु
	काष्ठा acpi_device *adev;
	काष्ठा sdw_पूर्णांकel_link_res *link;
	u32 caps;
	u32 link_mask;
	पूर्णांक i;

	अगर (acpi_bus_get_device(ctx->handle, &adev))
		वापस -EINVAL;

	/* Check SNDWLCAP.LCOUNT */
	caps = ioपढ़ो32(ctx->mmio_base + SDW_SHIM_BASE + SDW_SHIM_LCAP);
	caps &= GENMASK(2, 0);

	/* Check HW supported vs property value */
	अगर (caps < ctx->count) अणु
		dev_err(&adev->dev,
			"BIOS master count is larger than hardware capabilities\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!ctx->links)
		वापस -EINVAL;

	link = ctx->links;
	link_mask = ctx->link_mask;

	/* Startup SDW Master devices */
	क्रम (i = 0; i < ctx->count; i++, link++) अणु
		अगर (!(link_mask & BIT(i)))
			जारी;

		पूर्णांकel_master_startup(link->pdev);

		अगर (!link->घड़ी_stop_quirks) अणु
			/*
			 * we need to prevent the parent PCI device
			 * from entering pm_runसमय suspend, so that
			 * घातer rails to the SoundWire IP are not
			 * turned off.
			 */
			pm_runसमय_get_noresume(link->dev);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * sdw_पूर्णांकel_probe() - SoundWire Intel probe routine
 * @res: resource data
 *
 * This रेजिस्टरs a platक्रमm device क्रम each Master handled by the controller,
 * and SoundWire Master and Slave devices will be created by the platक्रमm
 * device probe. All the inक्रमmation necessary is stored in the context, and
 * the res argument poपूर्णांकer can be मुक्तd after this step.
 * This function will be called after sdw_पूर्णांकel_acpi_scan() by SOF probe.
 */
काष्ठा sdw_पूर्णांकel_ctx
*sdw_पूर्णांकel_probe(काष्ठा sdw_पूर्णांकel_res *res)
अणु
	वापस sdw_पूर्णांकel_probe_controller(res);
पूर्ण
EXPORT_SYMBOL_NS(sdw_पूर्णांकel_probe, SOUNDWIRE_INTEL_INIT);

/**
 * sdw_पूर्णांकel_startup() - SoundWire Intel startup
 * @ctx: SoundWire context allocated in the probe
 *
 * Startup Intel SoundWire controller. This function will be called after
 * Intel Audio DSP is घातered up.
 */
पूर्णांक sdw_पूर्णांकel_startup(काष्ठा sdw_पूर्णांकel_ctx *ctx)
अणु
	वापस sdw_पूर्णांकel_startup_controller(ctx);
पूर्ण
EXPORT_SYMBOL_NS(sdw_पूर्णांकel_startup, SOUNDWIRE_INTEL_INIT);
/**
 * sdw_पूर्णांकel_निकास() - SoundWire Intel निकास
 * @ctx: SoundWire context allocated in the probe
 *
 * Delete the controller instances created and cleanup
 */
व्योम sdw_पूर्णांकel_निकास(काष्ठा sdw_पूर्णांकel_ctx *ctx)
अणु
	sdw_पूर्णांकel_cleanup(ctx);
पूर्ण
EXPORT_SYMBOL_NS(sdw_पूर्णांकel_निकास, SOUNDWIRE_INTEL_INIT);

व्योम sdw_पूर्णांकel_process_wakeen_event(काष्ठा sdw_पूर्णांकel_ctx *ctx)
अणु
	काष्ठा sdw_पूर्णांकel_link_res *link;
	u32 link_mask;
	पूर्णांक i;

	अगर (!ctx->links)
		वापस;

	link = ctx->links;
	link_mask = ctx->link_mask;

	/* Startup SDW Master devices */
	क्रम (i = 0; i < ctx->count; i++, link++) अणु
		अगर (!(link_mask & BIT(i)))
			जारी;

		पूर्णांकel_master_process_wakeen_event(link->pdev);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_NS(sdw_पूर्णांकel_process_wakeen_event, SOUNDWIRE_INTEL_INIT);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("Intel Soundwire Init Library");
