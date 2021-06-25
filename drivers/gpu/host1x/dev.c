<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Tegra host1x driver
 *
 * Copyright (c) 2010-2013, NVIDIA Corporation.
 */

#समावेश <linux/clk.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पन.स>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of.h>
#समावेश <linux/slab.h>

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/host1x.h>
#अघोषित CREATE_TRACE_POINTS

#समावेश "bus.h"
#समावेश "channel.h"
#समावेश "debug.h"
#समावेश "dev.h"
#समावेश "intr.h"

#समावेश "hw/host1x01.h"
#समावेश "hw/host1x02.h"
#समावेश "hw/host1x04.h"
#समावेश "hw/host1x05.h"
#समावेश "hw/host1x06.h"
#समावेश "hw/host1x07.h"

व्योम host1x_hypervisor_ग_लिखोl(काष्ठा host1x *host1x, u32 v, u32 r)
अणु
	ग_लिखोl(v, host1x->hv_regs + r);
पूर्ण

u32 host1x_hypervisor_पढ़ोl(काष्ठा host1x *host1x, u32 r)
अणु
	वापस पढ़ोl(host1x->hv_regs + r);
पूर्ण

व्योम host1x_sync_ग_लिखोl(काष्ठा host1x *host1x, u32 v, u32 r)
अणु
	व्योम __iomem *sync_regs = host1x->regs + host1x->info->sync_offset;

	ग_लिखोl(v, sync_regs + r);
पूर्ण

u32 host1x_sync_पढ़ोl(काष्ठा host1x *host1x, u32 r)
अणु
	व्योम __iomem *sync_regs = host1x->regs + host1x->info->sync_offset;

	वापस पढ़ोl(sync_regs + r);
पूर्ण

व्योम host1x_ch_ग_लिखोl(काष्ठा host1x_channel *ch, u32 v, u32 r)
अणु
	ग_लिखोl(v, ch->regs + r);
पूर्ण

u32 host1x_ch_पढ़ोl(काष्ठा host1x_channel *ch, u32 r)
अणु
	वापस पढ़ोl(ch->regs + r);
पूर्ण

अटल स्थिर काष्ठा host1x_info host1x01_info = अणु
	.nb_channels = 8,
	.nb_pts = 32,
	.nb_mlocks = 16,
	.nb_bases = 8,
	.init = host1x01_init,
	.sync_offset = 0x3000,
	.dma_mask = DMA_BIT_MASK(32),
	.has_wide_gather = false,
	.has_hypervisor = false,
	.num_sid_entries = 0,
	.sid_table = शून्य,
	.reserve_vblank_syncpts = true,
पूर्ण;

अटल स्थिर काष्ठा host1x_info host1x02_info = अणु
	.nb_channels = 9,
	.nb_pts = 32,
	.nb_mlocks = 16,
	.nb_bases = 12,
	.init = host1x02_init,
	.sync_offset = 0x3000,
	.dma_mask = DMA_BIT_MASK(32),
	.has_wide_gather = false,
	.has_hypervisor = false,
	.num_sid_entries = 0,
	.sid_table = शून्य,
	.reserve_vblank_syncpts = true,
पूर्ण;

अटल स्थिर काष्ठा host1x_info host1x04_info = अणु
	.nb_channels = 12,
	.nb_pts = 192,
	.nb_mlocks = 16,
	.nb_bases = 64,
	.init = host1x04_init,
	.sync_offset = 0x2100,
	.dma_mask = DMA_BIT_MASK(34),
	.has_wide_gather = false,
	.has_hypervisor = false,
	.num_sid_entries = 0,
	.sid_table = शून्य,
	.reserve_vblank_syncpts = false,
पूर्ण;

अटल स्थिर काष्ठा host1x_info host1x05_info = अणु
	.nb_channels = 14,
	.nb_pts = 192,
	.nb_mlocks = 16,
	.nb_bases = 64,
	.init = host1x05_init,
	.sync_offset = 0x2100,
	.dma_mask = DMA_BIT_MASK(34),
	.has_wide_gather = false,
	.has_hypervisor = false,
	.num_sid_entries = 0,
	.sid_table = शून्य,
	.reserve_vblank_syncpts = false,
पूर्ण;

अटल स्थिर काष्ठा host1x_sid_entry tegra186_sid_table[] = अणु
	अणु
		/* VIC */
		.base = 0x1af0,
		.offset = 0x30,
		.limit = 0x34
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा host1x_info host1x06_info = अणु
	.nb_channels = 63,
	.nb_pts = 576,
	.nb_mlocks = 24,
	.nb_bases = 16,
	.init = host1x06_init,
	.sync_offset = 0x0,
	.dma_mask = DMA_BIT_MASK(40),
	.has_wide_gather = true,
	.has_hypervisor = true,
	.num_sid_entries = ARRAY_SIZE(tegra186_sid_table),
	.sid_table = tegra186_sid_table,
	.reserve_vblank_syncpts = false,
पूर्ण;

अटल स्थिर काष्ठा host1x_sid_entry tegra194_sid_table[] = अणु
	अणु
		/* VIC */
		.base = 0x1af0,
		.offset = 0x30,
		.limit = 0x34
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा host1x_info host1x07_info = अणु
	.nb_channels = 63,
	.nb_pts = 704,
	.nb_mlocks = 32,
	.nb_bases = 0,
	.init = host1x07_init,
	.sync_offset = 0x0,
	.dma_mask = DMA_BIT_MASK(40),
	.has_wide_gather = true,
	.has_hypervisor = true,
	.num_sid_entries = ARRAY_SIZE(tegra194_sid_table),
	.sid_table = tegra194_sid_table,
	.reserve_vblank_syncpts = false,
पूर्ण;

अटल स्थिर काष्ठा of_device_id host1x_of_match[] = अणु
	अणु .compatible = "nvidia,tegra194-host1x", .data = &host1x07_info, पूर्ण,
	अणु .compatible = "nvidia,tegra186-host1x", .data = &host1x06_info, पूर्ण,
	अणु .compatible = "nvidia,tegra210-host1x", .data = &host1x05_info, पूर्ण,
	अणु .compatible = "nvidia,tegra124-host1x", .data = &host1x04_info, पूर्ण,
	अणु .compatible = "nvidia,tegra114-host1x", .data = &host1x02_info, पूर्ण,
	अणु .compatible = "nvidia,tegra30-host1x", .data = &host1x01_info, पूर्ण,
	अणु .compatible = "nvidia,tegra20-host1x", .data = &host1x01_info, पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, host1x_of_match);

अटल व्योम host1x_setup_sid_table(काष्ठा host1x *host)
अणु
	स्थिर काष्ठा host1x_info *info = host->info;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < info->num_sid_entries; i++) अणु
		स्थिर काष्ठा host1x_sid_entry *entry = &info->sid_table[i];

		host1x_hypervisor_ग_लिखोl(host, entry->offset, entry->base);
		host1x_hypervisor_ग_लिखोl(host, entry->limit, entry->base + 4);
	पूर्ण
पूर्ण

अटल bool host1x_wants_iommu(काष्ठा host1x *host1x)
अणु
	/*
	 * If we support addressing a maximum of 32 bits of physical memory
	 * and अगर the host1x firewall is enabled, there's no need to enable
	 * IOMMU support. This can happen क्रम example on Tegra20, Tegra30
	 * and Tegra114.
	 *
	 * Tegra124 and later can address up to 34 bits of physical memory and
	 * many platक्रमms come equipped with more than 2 GiB of प्रणाली memory,
	 * which requires crossing the 4 GiB boundary. But there's a catch: on
	 * SoCs beक्रमe Tegra186 (i.e. Tegra124 and Tegra210), the host1x can
	 * only address up to 32 bits of memory in GATHER opcodes, which means
	 * that command buffers need to either be in the first 2 GiB of प्रणाली
	 * memory (which could quickly lead to memory exhaustion), or command
	 * buffers need to be treated dअगरferently from other buffers (which is
	 * not possible with the current ABI).
	 *
	 * A third option is to use the IOMMU in these हालs to make sure all
	 * buffers will be mapped पूर्णांकo a 32-bit IOVA space that host1x can
	 * address. This allows all of the प्रणाली memory to be used and works
	 * within the limitations of the host1x on these SoCs.
	 *
	 * In summary, शेष to enable IOMMU on Tegra124 and later. For any
	 * of the earlier SoCs, only use the IOMMU क्रम additional safety when
	 * the host1x firewall is disabled.
	 */
	अगर (host1x->info->dma_mask <= DMA_BIT_MASK(32)) अणु
		अगर (IS_ENABLED(CONFIG_TEGRA_HOST1X_FIREWALL))
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल काष्ठा iommu_करोमुख्य *host1x_iommu_attach(काष्ठा host1x *host)
अणु
	काष्ठा iommu_करोमुख्य *करोमुख्य = iommu_get_करोमुख्य_क्रम_dev(host->dev);
	पूर्णांक err;

	/*
	 * We may not always want to enable IOMMU support (क्रम example अगर the
	 * host1x firewall is alपढ़ोy enabled and we करोn't support addressing
	 * more than 32 bits of physical memory), so check क्रम that first.
	 *
	 * Similarly, अगर host1x is alपढ़ोy attached to an IOMMU (via the DMA
	 * API), करोn't try to attach again.
	 */
	अगर (!host1x_wants_iommu(host) || करोमुख्य)
		वापस करोमुख्य;

	host->group = iommu_group_get(host->dev);
	अगर (host->group) अणु
		काष्ठा iommu_करोमुख्य_geometry *geometry;
		dma_addr_t start, end;
		अचिन्हित दीर्घ order;

		err = iova_cache_get();
		अगर (err < 0)
			जाओ put_group;

		host->करोमुख्य = iommu_करोमुख्य_alloc(&platक्रमm_bus_type);
		अगर (!host->करोमुख्य) अणु
			err = -ENOMEM;
			जाओ put_cache;
		पूर्ण

		err = iommu_attach_group(host->करोमुख्य, host->group);
		अगर (err) अणु
			अगर (err == -ENODEV)
				err = 0;

			जाओ मुक्त_करोमुख्य;
		पूर्ण

		geometry = &host->करोमुख्य->geometry;
		start = geometry->aperture_start & host->info->dma_mask;
		end = geometry->aperture_end & host->info->dma_mask;

		order = __ffs(host->करोमुख्य->pgsize_biपंचांगap);
		init_iova_करोमुख्य(&host->iova, 1UL << order, start >> order);
		host->ioबहु_पूर्ण = end;

		करोमुख्य = host->करोमुख्य;
	पूर्ण

	वापस करोमुख्य;

मुक्त_करोमुख्य:
	iommu_करोमुख्य_मुक्त(host->करोमुख्य);
	host->करोमुख्य = शून्य;
put_cache:
	iova_cache_put();
put_group:
	iommu_group_put(host->group);
	host->group = शून्य;

	वापस ERR_PTR(err);
पूर्ण

अटल पूर्णांक host1x_iommu_init(काष्ठा host1x *host)
अणु
	u64 mask = host->info->dma_mask;
	काष्ठा iommu_करोमुख्य *करोमुख्य;
	पूर्णांक err;

	करोमुख्य = host1x_iommu_attach(host);
	अगर (IS_ERR(करोमुख्य)) अणु
		err = PTR_ERR(करोमुख्य);
		dev_err(host->dev, "failed to attach to IOMMU: %d\n", err);
		वापस err;
	पूर्ण

	/*
	 * If we're not behind an IOMMU make sure we don't get push buffers
	 * that are allocated outside of the range addressable by the GATHER
	 * opcode.
	 *
	 * Newer generations of Tegra (Tegra186 and later) support a wide
	 * variant of the GATHER opcode that allows addressing more bits.
	 */
	अगर (!करोमुख्य && !host->info->has_wide_gather)
		mask = DMA_BIT_MASK(32);

	err = dma_coerce_mask_and_coherent(host->dev, mask);
	अगर (err < 0) अणु
		dev_err(host->dev, "failed to set DMA mask: %d\n", err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम host1x_iommu_निकास(काष्ठा host1x *host)
अणु
	अगर (host->करोमुख्य) अणु
		put_iova_करोमुख्य(&host->iova);
		iommu_detach_group(host->करोमुख्य, host->group);

		iommu_करोमुख्य_मुक्त(host->करोमुख्य);
		host->करोमुख्य = शून्य;

		iova_cache_put();

		iommu_group_put(host->group);
		host->group = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक host1x_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा host1x *host;
	काष्ठा resource *regs, *hv_regs = शून्य;
	पूर्णांक syncpt_irq;
	पूर्णांक err;

	host = devm_kzalloc(&pdev->dev, माप(*host), GFP_KERNEL);
	अगर (!host)
		वापस -ENOMEM;

	host->info = of_device_get_match_data(&pdev->dev);

	अगर (host->info->has_hypervisor) अणु
		regs = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "vm");
		अगर (!regs) अणु
			dev_err(&pdev->dev, "failed to get vm registers\n");
			वापस -ENXIO;
		पूर्ण

		hv_regs = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM,
						       "hypervisor");
		अगर (!hv_regs) अणु
			dev_err(&pdev->dev,
				"failed to get hypervisor registers\n");
			वापस -ENXIO;
		पूर्ण
	पूर्ण अन्यथा अणु
		regs = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
		अगर (!regs) अणु
			dev_err(&pdev->dev, "failed to get registers\n");
			वापस -ENXIO;
		पूर्ण
	पूर्ण

	syncpt_irq = platक्रमm_get_irq(pdev, 0);
	अगर (syncpt_irq < 0)
		वापस syncpt_irq;

	mutex_init(&host->devices_lock);
	INIT_LIST_HEAD(&host->devices);
	INIT_LIST_HEAD(&host->list);
	host->dev = &pdev->dev;

	/* set common host1x device data */
	platक्रमm_set_drvdata(pdev, host);

	host->regs = devm_ioremap_resource(&pdev->dev, regs);
	अगर (IS_ERR(host->regs))
		वापस PTR_ERR(host->regs);

	अगर (host->info->has_hypervisor) अणु
		host->hv_regs = devm_ioremap_resource(&pdev->dev, hv_regs);
		अगर (IS_ERR(host->hv_regs))
			वापस PTR_ERR(host->hv_regs);
	पूर्ण

	host->dev->dma_parms = &host->dma_parms;
	dma_set_max_seg_size(host->dev, अच_पूर्णांक_उच्च);

	अगर (host->info->init) अणु
		err = host->info->init(host);
		अगर (err)
			वापस err;
	पूर्ण

	host->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(host->clk)) अणु
		err = PTR_ERR(host->clk);

		अगर (err != -EPROBE_DEFER)
			dev_err(&pdev->dev, "failed to get clock: %d\n", err);

		वापस err;
	पूर्ण

	host->rst = devm_reset_control_get(&pdev->dev, "host1x");
	अगर (IS_ERR(host->rst)) अणु
		err = PTR_ERR(host->rst);
		dev_err(&pdev->dev, "failed to get reset: %d\n", err);
		वापस err;
	पूर्ण

	err = host1x_iommu_init(host);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "failed to setup IOMMU: %d\n", err);
		वापस err;
	पूर्ण

	err = host1x_channel_list_init(&host->channel_list,
				       host->info->nb_channels);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to initialize channel list\n");
		जाओ iommu_निकास;
	पूर्ण

	err = clk_prepare_enable(host->clk);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "failed to enable clock\n");
		जाओ मुक्त_channels;
	पूर्ण

	err = reset_control_deनिश्चित(host->rst);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "failed to deassert reset: %d\n", err);
		जाओ unprepare_disable;
	पूर्ण

	err = host1x_syncpt_init(host);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to initialize syncpts\n");
		जाओ reset_निश्चित;
	पूर्ण

	err = host1x_पूर्णांकr_init(host, syncpt_irq);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to initialize interrupts\n");
		जाओ deinit_syncpt;
	पूर्ण

	host1x_debug_init(host);

	अगर (host->info->has_hypervisor)
		host1x_setup_sid_table(host);

	err = host1x_रेजिस्टर(host);
	अगर (err < 0)
		जाओ deinit_debugfs;

	err = devm_of_platक्रमm_populate(&pdev->dev);
	अगर (err < 0)
		जाओ unरेजिस्टर;

	वापस 0;

unरेजिस्टर:
	host1x_unरेजिस्टर(host);
deinit_debugfs:
	host1x_debug_deinit(host);
	host1x_पूर्णांकr_deinit(host);
deinit_syncpt:
	host1x_syncpt_deinit(host);
reset_निश्चित:
	reset_control_निश्चित(host->rst);
unprepare_disable:
	clk_disable_unprepare(host->clk);
मुक्त_channels:
	host1x_channel_list_मुक्त(&host->channel_list);
iommu_निकास:
	host1x_iommu_निकास(host);

	वापस err;
पूर्ण

अटल पूर्णांक host1x_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा host1x *host = platक्रमm_get_drvdata(pdev);

	host1x_unरेजिस्टर(host);
	host1x_debug_deinit(host);
	host1x_पूर्णांकr_deinit(host);
	host1x_syncpt_deinit(host);
	reset_control_निश्चित(host->rst);
	clk_disable_unprepare(host->clk);
	host1x_iommu_निकास(host);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver tegra_host1x_driver = अणु
	.driver = अणु
		.name = "tegra-host1x",
		.of_match_table = host1x_of_match,
	पूर्ण,
	.probe = host1x_probe,
	.हटाओ = host1x_हटाओ,
पूर्ण;

अटल काष्ठा platक्रमm_driver * स्थिर drivers[] = अणु
	&tegra_host1x_driver,
	&tegra_mipi_driver,
पूर्ण;

अटल पूर्णांक __init tegra_host1x_init(व्योम)
अणु
	पूर्णांक err;

	err = bus_रेजिस्टर(&host1x_bus_type);
	अगर (err < 0)
		वापस err;

	err = platक्रमm_रेजिस्टर_drivers(drivers, ARRAY_SIZE(drivers));
	अगर (err < 0)
		bus_unरेजिस्टर(&host1x_bus_type);

	वापस err;
पूर्ण
module_init(tegra_host1x_init);

अटल व्योम __निकास tegra_host1x_निकास(व्योम)
अणु
	platक्रमm_unरेजिस्टर_drivers(drivers, ARRAY_SIZE(drivers));
	bus_unरेजिस्टर(&host1x_bus_type);
पूर्ण
module_निकास(tegra_host1x_निकास);

/**
 * host1x_get_dma_mask() - query the supported DMA mask क्रम host1x
 * @host1x: host1x instance
 *
 * Note that this वापसs the supported DMA mask क्रम host1x, which can be
 * dअगरferent from the applicable DMA mask under certain circumstances.
 */
u64 host1x_get_dma_mask(काष्ठा host1x *host1x)
अणु
	वापस host1x->info->dma_mask;
पूर्ण
EXPORT_SYMBOL(host1x_get_dma_mask);

MODULE_AUTHOR("Thierry Reding <thierry.reding@avionic-design.de>");
MODULE_AUTHOR("Terje Bergstrom <tbergstrom@nvidia.com>");
MODULE_DESCRIPTION("Host1x driver for Tegra products");
MODULE_LICENSE("GPL");
