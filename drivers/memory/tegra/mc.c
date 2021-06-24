<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2014 NVIDIA CORPORATION.  All rights reserved.
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/export.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/sort.h>

#समावेश <soc/tegra/fuse.h>

#समावेश "mc.h"

अटल स्थिर काष्ठा of_device_id tegra_mc_of_match[] = अणु
#अगर_घोषित CONFIG_ARCH_TEGRA_2x_SOC
	अणु .compatible = "nvidia,tegra20-mc-gart", .data = &tegra20_mc_soc पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARCH_TEGRA_3x_SOC
	अणु .compatible = "nvidia,tegra30-mc", .data = &tegra30_mc_soc पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARCH_TEGRA_114_SOC
	अणु .compatible = "nvidia,tegra114-mc", .data = &tegra114_mc_soc पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARCH_TEGRA_124_SOC
	अणु .compatible = "nvidia,tegra124-mc", .data = &tegra124_mc_soc पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARCH_TEGRA_132_SOC
	अणु .compatible = "nvidia,tegra132-mc", .data = &tegra132_mc_soc पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARCH_TEGRA_210_SOC
	अणु .compatible = "nvidia,tegra210-mc", .data = &tegra210_mc_soc पूर्ण,
#पूर्ण_अगर
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, tegra_mc_of_match);

अटल व्योम tegra_mc_devm_action_put_device(व्योम *data)
अणु
	काष्ठा tegra_mc *mc = data;

	put_device(mc->dev);
पूर्ण

/**
 * devm_tegra_memory_controller_get() - get Tegra Memory Controller handle
 * @dev: device poपूर्णांकer क्रम the consumer device
 *
 * This function will search क्रम the Memory Controller node in a device-tree
 * and retrieve the Memory Controller handle.
 *
 * Return: ERR_PTR() on error or a valid poपूर्णांकer to a काष्ठा tegra_mc.
 */
काष्ठा tegra_mc *devm_tegra_memory_controller_get(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा device_node *np;
	काष्ठा tegra_mc *mc;
	पूर्णांक err;

	np = of_parse_phandle(dev->of_node, "nvidia,memory-controller", 0);
	अगर (!np)
		वापस ERR_PTR(-ENOENT);

	pdev = of_find_device_by_node(np);
	of_node_put(np);
	अगर (!pdev)
		वापस ERR_PTR(-ENODEV);

	mc = platक्रमm_get_drvdata(pdev);
	अगर (!mc) अणु
		put_device(&pdev->dev);
		वापस ERR_PTR(-EPROBE_DEFER);
	पूर्ण

	err = devm_add_action(dev, tegra_mc_devm_action_put_device, mc);
	अगर (err) अणु
		put_device(mc->dev);
		वापस ERR_PTR(err);
	पूर्ण

	वापस mc;
पूर्ण
EXPORT_SYMBOL_GPL(devm_tegra_memory_controller_get);

अटल पूर्णांक tegra_mc_block_dma_common(काष्ठा tegra_mc *mc,
				     स्थिर काष्ठा tegra_mc_reset *rst)
अणु
	अचिन्हित दीर्घ flags;
	u32 value;

	spin_lock_irqsave(&mc->lock, flags);

	value = mc_पढ़ोl(mc, rst->control) | BIT(rst->bit);
	mc_ग_लिखोl(mc, value, rst->control);

	spin_unlock_irqrestore(&mc->lock, flags);

	वापस 0;
पूर्ण

अटल bool tegra_mc_dma_idling_common(काष्ठा tegra_mc *mc,
				       स्थिर काष्ठा tegra_mc_reset *rst)
अणु
	वापस (mc_पढ़ोl(mc, rst->status) & BIT(rst->bit)) != 0;
पूर्ण

अटल पूर्णांक tegra_mc_unblock_dma_common(काष्ठा tegra_mc *mc,
				       स्थिर काष्ठा tegra_mc_reset *rst)
अणु
	अचिन्हित दीर्घ flags;
	u32 value;

	spin_lock_irqsave(&mc->lock, flags);

	value = mc_पढ़ोl(mc, rst->control) & ~BIT(rst->bit);
	mc_ग_लिखोl(mc, value, rst->control);

	spin_unlock_irqrestore(&mc->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_mc_reset_status_common(काष्ठा tegra_mc *mc,
					स्थिर काष्ठा tegra_mc_reset *rst)
अणु
	वापस (mc_पढ़ोl(mc, rst->control) & BIT(rst->bit)) != 0;
पूर्ण

स्थिर काष्ठा tegra_mc_reset_ops tegra_mc_reset_ops_common = अणु
	.block_dma = tegra_mc_block_dma_common,
	.dma_idling = tegra_mc_dma_idling_common,
	.unblock_dma = tegra_mc_unblock_dma_common,
	.reset_status = tegra_mc_reset_status_common,
पूर्ण;

अटल अंतरभूत काष्ठा tegra_mc *reset_to_mc(काष्ठा reset_controller_dev *rcdev)
अणु
	वापस container_of(rcdev, काष्ठा tegra_mc, reset);
पूर्ण

अटल स्थिर काष्ठा tegra_mc_reset *tegra_mc_reset_find(काष्ठा tegra_mc *mc,
							अचिन्हित दीर्घ id)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < mc->soc->num_resets; i++)
		अगर (mc->soc->resets[i].id == id)
			वापस &mc->soc->resets[i];

	वापस शून्य;
पूर्ण

अटल पूर्णांक tegra_mc_hotreset_निश्चित(काष्ठा reset_controller_dev *rcdev,
				    अचिन्हित दीर्घ id)
अणु
	काष्ठा tegra_mc *mc = reset_to_mc(rcdev);
	स्थिर काष्ठा tegra_mc_reset_ops *rst_ops;
	स्थिर काष्ठा tegra_mc_reset *rst;
	पूर्णांक retries = 500;
	पूर्णांक err;

	rst = tegra_mc_reset_find(mc, id);
	अगर (!rst)
		वापस -ENODEV;

	rst_ops = mc->soc->reset_ops;
	अगर (!rst_ops)
		वापस -ENODEV;

	/* DMA flushing will fail अगर reset is alपढ़ोy निश्चितed */
	अगर (rst_ops->reset_status) अणु
		/* check whether reset is निश्चितed */
		अगर (rst_ops->reset_status(mc, rst))
			वापस 0;
	पूर्ण

	अगर (rst_ops->block_dma) अणु
		/* block clients DMA requests */
		err = rst_ops->block_dma(mc, rst);
		अगर (err) अणु
			dev_err(mc->dev, "failed to block %s DMA: %d\n",
				rst->name, err);
			वापस err;
		पूर्ण
	पूर्ण

	अगर (rst_ops->dma_idling) अणु
		/* रुको क्रम completion of the outstanding DMA requests */
		जबतक (!rst_ops->dma_idling(mc, rst)) अणु
			अगर (!retries--) अणु
				dev_err(mc->dev, "failed to flush %s DMA\n",
					rst->name);
				वापस -EBUSY;
			पूर्ण

			usleep_range(10, 100);
		पूर्ण
	पूर्ण

	अगर (rst_ops->hotreset_निश्चित) अणु
		/* clear clients DMA requests sitting beक्रमe arbitration */
		err = rst_ops->hotreset_निश्चित(mc, rst);
		अगर (err) अणु
			dev_err(mc->dev, "failed to hot reset %s: %d\n",
				rst->name, err);
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_mc_hotreset_deनिश्चित(काष्ठा reset_controller_dev *rcdev,
				      अचिन्हित दीर्घ id)
अणु
	काष्ठा tegra_mc *mc = reset_to_mc(rcdev);
	स्थिर काष्ठा tegra_mc_reset_ops *rst_ops;
	स्थिर काष्ठा tegra_mc_reset *rst;
	पूर्णांक err;

	rst = tegra_mc_reset_find(mc, id);
	अगर (!rst)
		वापस -ENODEV;

	rst_ops = mc->soc->reset_ops;
	अगर (!rst_ops)
		वापस -ENODEV;

	अगर (rst_ops->hotreset_deनिश्चित) अणु
		/* take out client from hot reset */
		err = rst_ops->hotreset_deनिश्चित(mc, rst);
		अगर (err) अणु
			dev_err(mc->dev, "failed to deassert hot reset %s: %d\n",
				rst->name, err);
			वापस err;
		पूर्ण
	पूर्ण

	अगर (rst_ops->unblock_dma) अणु
		/* allow new DMA requests to proceed to arbitration */
		err = rst_ops->unblock_dma(mc, rst);
		अगर (err) अणु
			dev_err(mc->dev, "failed to unblock %s DMA : %d\n",
				rst->name, err);
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_mc_hotreset_status(काष्ठा reset_controller_dev *rcdev,
				    अचिन्हित दीर्घ id)
अणु
	काष्ठा tegra_mc *mc = reset_to_mc(rcdev);
	स्थिर काष्ठा tegra_mc_reset_ops *rst_ops;
	स्थिर काष्ठा tegra_mc_reset *rst;

	rst = tegra_mc_reset_find(mc, id);
	अगर (!rst)
		वापस -ENODEV;

	rst_ops = mc->soc->reset_ops;
	अगर (!rst_ops)
		वापस -ENODEV;

	वापस rst_ops->reset_status(mc, rst);
पूर्ण

अटल स्थिर काष्ठा reset_control_ops tegra_mc_reset_ops = अणु
	.निश्चित = tegra_mc_hotreset_निश्चित,
	.deनिश्चित = tegra_mc_hotreset_deनिश्चित,
	.status = tegra_mc_hotreset_status,
पूर्ण;

अटल पूर्णांक tegra_mc_reset_setup(काष्ठा tegra_mc *mc)
अणु
	पूर्णांक err;

	mc->reset.ops = &tegra_mc_reset_ops;
	mc->reset.owner = THIS_MODULE;
	mc->reset.of_node = mc->dev->of_node;
	mc->reset.of_reset_n_cells = 1;
	mc->reset.nr_resets = mc->soc->num_resets;

	err = reset_controller_रेजिस्टर(&mc->reset);
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_mc_setup_latency_allowance(काष्ठा tegra_mc *mc)
अणु
	अचिन्हित दीर्घ दीर्घ tick;
	अचिन्हित पूर्णांक i;
	u32 value;

	/* compute the number of MC घड़ी cycles per tick */
	tick = (अचिन्हित दीर्घ दीर्घ)mc->tick * clk_get_rate(mc->clk);
	करो_भाग(tick, NSEC_PER_SEC);

	value = mc_पढ़ोl(mc, MC_EMEM_ARB_CFG);
	value &= ~MC_EMEM_ARB_CFG_CYCLES_PER_UPDATE_MASK;
	value |= MC_EMEM_ARB_CFG_CYCLES_PER_UPDATE(tick);
	mc_ग_लिखोl(mc, value, MC_EMEM_ARB_CFG);

	/* ग_लिखो latency allowance शेषs */
	क्रम (i = 0; i < mc->soc->num_clients; i++) अणु
		स्थिर काष्ठा tegra_mc_la *la = &mc->soc->clients[i].la;
		u32 value;

		value = mc_पढ़ोl(mc, la->reg);
		value &= ~(la->mask << la->shअगरt);
		value |= (la->def & la->mask) << la->shअगरt;
		mc_ग_लिखोl(mc, value, la->reg);
	पूर्ण

	/* latch new values */
	mc_ग_लिखोl(mc, MC_TIMING_UPDATE, MC_TIMING_CONTROL);

	वापस 0;
पूर्ण

पूर्णांक tegra_mc_ग_लिखो_emem_configuration(काष्ठा tegra_mc *mc, अचिन्हित दीर्घ rate)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा tegra_mc_timing *timing = शून्य;

	क्रम (i = 0; i < mc->num_timings; i++) अणु
		अगर (mc->timings[i].rate == rate) अणु
			timing = &mc->timings[i];
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!timing) अणु
		dev_err(mc->dev, "no memory timing registered for rate %lu\n",
			rate);
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < mc->soc->num_emem_regs; ++i)
		mc_ग_लिखोl(mc, timing->emem_data[i], mc->soc->emem_regs[i]);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(tegra_mc_ग_लिखो_emem_configuration);

अचिन्हित पूर्णांक tegra_mc_get_emem_device_count(काष्ठा tegra_mc *mc)
अणु
	u8 dram_count;

	dram_count = mc_पढ़ोl(mc, MC_EMEM_ADR_CFG);
	dram_count &= MC_EMEM_ADR_CFG_EMEM_NUMDEV;
	dram_count++;

	वापस dram_count;
पूर्ण
EXPORT_SYMBOL_GPL(tegra_mc_get_emem_device_count);

अटल पूर्णांक load_one_timing(काष्ठा tegra_mc *mc,
			   काष्ठा tegra_mc_timing *timing,
			   काष्ठा device_node *node)
अणु
	पूर्णांक err;
	u32 पंचांगp;

	err = of_property_पढ़ो_u32(node, "clock-frequency", &पंचांगp);
	अगर (err) अणु
		dev_err(mc->dev,
			"timing %pOFn: failed to read rate\n", node);
		वापस err;
	पूर्ण

	timing->rate = पंचांगp;
	timing->emem_data = devm_kसुस्मृति(mc->dev, mc->soc->num_emem_regs,
					 माप(u32), GFP_KERNEL);
	अगर (!timing->emem_data)
		वापस -ENOMEM;

	err = of_property_पढ़ो_u32_array(node, "nvidia,emem-configuration",
					 timing->emem_data,
					 mc->soc->num_emem_regs);
	अगर (err) अणु
		dev_err(mc->dev,
			"timing %pOFn: failed to read EMEM configuration\n",
			node);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक load_timings(काष्ठा tegra_mc *mc, काष्ठा device_node *node)
अणु
	काष्ठा device_node *child;
	काष्ठा tegra_mc_timing *timing;
	पूर्णांक child_count = of_get_child_count(node);
	पूर्णांक i = 0, err;

	mc->timings = devm_kसुस्मृति(mc->dev, child_count, माप(*timing),
				   GFP_KERNEL);
	अगर (!mc->timings)
		वापस -ENOMEM;

	mc->num_timings = child_count;

	क्रम_each_child_of_node(node, child) अणु
		timing = &mc->timings[i++];

		err = load_one_timing(mc, timing, child);
		अगर (err) अणु
			of_node_put(child);
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_mc_setup_timings(काष्ठा tegra_mc *mc)
अणु
	काष्ठा device_node *node;
	u32 ram_code, node_ram_code;
	पूर्णांक err;

	ram_code = tegra_पढ़ो_ram_code();

	mc->num_timings = 0;

	क्रम_each_child_of_node(mc->dev->of_node, node) अणु
		err = of_property_पढ़ो_u32(node, "nvidia,ram-code",
					   &node_ram_code);
		अगर (err || (node_ram_code != ram_code))
			जारी;

		err = load_timings(mc, node);
		of_node_put(node);
		अगर (err)
			वापस err;
		अवरोध;
	पूर्ण

	अगर (mc->num_timings == 0)
		dev_warn(mc->dev,
			 "no memory timings for RAM code %u registered\n",
			 ram_code);

	वापस 0;
पूर्ण

अटल स्थिर अक्षर *स्थिर status_names[32] = अणु
	[ 1] = "External interrupt",
	[ 6] = "EMEM address decode error",
	[ 7] = "GART page fault",
	[ 8] = "Security violation",
	[ 9] = "EMEM arbitration error",
	[10] = "Page fault",
	[11] = "Invalid APB ASID update",
	[12] = "VPR violation",
	[13] = "Secure carveout violation",
	[16] = "MTS carveout violation",
पूर्ण;

अटल स्थिर अक्षर *स्थिर error_names[8] = अणु
	[2] = "EMEM decode error",
	[3] = "TrustZone violation",
	[4] = "Carveout violation",
	[6] = "SMMU translation error",
पूर्ण;

अटल irqवापस_t tegra_mc_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा tegra_mc *mc = data;
	अचिन्हित दीर्घ status;
	अचिन्हित पूर्णांक bit;

	/* mask all पूर्णांकerrupts to aव्योम flooding */
	status = mc_पढ़ोl(mc, MC_INTSTATUS) & mc->soc->पूर्णांकmask;
	अगर (!status)
		वापस IRQ_NONE;

	क्रम_each_set_bit(bit, &status, 32) अणु
		स्थिर अक्षर *error = status_names[bit] ?: "unknown";
		स्थिर अक्षर *client = "unknown", *desc;
		स्थिर अक्षर *direction, *secure;
		phys_addr_t addr = 0;
		अचिन्हित पूर्णांक i;
		अक्षर perm[7];
		u8 id, type;
		u32 value;

		value = mc_पढ़ोl(mc, MC_ERR_STATUS);

#अगर_घोषित CONFIG_PHYS_ADDR_T_64BIT
		अगर (mc->soc->num_address_bits > 32) अणु
			addr = ((value >> MC_ERR_STATUS_ADR_HI_SHIFT) &
				MC_ERR_STATUS_ADR_HI_MASK);
			addr <<= 32;
		पूर्ण
#पूर्ण_अगर

		अगर (value & MC_ERR_STATUS_RW)
			direction = "write";
		अन्यथा
			direction = "read";

		अगर (value & MC_ERR_STATUS_SECURITY)
			secure = "secure ";
		अन्यथा
			secure = "";

		id = value & mc->soc->client_id_mask;

		क्रम (i = 0; i < mc->soc->num_clients; i++) अणु
			अगर (mc->soc->clients[i].id == id) अणु
				client = mc->soc->clients[i].name;
				अवरोध;
			पूर्ण
		पूर्ण

		type = (value & MC_ERR_STATUS_TYPE_MASK) >>
		       MC_ERR_STATUS_TYPE_SHIFT;
		desc = error_names[type];

		चयन (value & MC_ERR_STATUS_TYPE_MASK) अणु
		हाल MC_ERR_STATUS_TYPE_INVALID_SMMU_PAGE:
			perm[0] = ' ';
			perm[1] = '[';

			अगर (value & MC_ERR_STATUS_READABLE)
				perm[2] = 'R';
			अन्यथा
				perm[2] = '-';

			अगर (value & MC_ERR_STATUS_WRITABLE)
				perm[3] = 'W';
			अन्यथा
				perm[3] = '-';

			अगर (value & MC_ERR_STATUS_NONSECURE)
				perm[4] = '-';
			अन्यथा
				perm[4] = 'S';

			perm[5] = ']';
			perm[6] = '\0';
			अवरोध;

		शेष:
			perm[0] = '\0';
			अवरोध;
		पूर्ण

		value = mc_पढ़ोl(mc, MC_ERR_ADR);
		addr |= value;

		dev_err_ratelimited(mc->dev, "%s: %s%s @%pa: %s (%s%s)\n",
				    client, secure, direction, &addr, error,
				    desc, perm);
	पूर्ण

	/* clear पूर्णांकerrupts */
	mc_ग_लिखोl(mc, status, MC_INTSTATUS);

	वापस IRQ_HANDLED;
पूर्ण

अटल __maybe_unused irqवापस_t tegra20_mc_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा tegra_mc *mc = data;
	अचिन्हित दीर्घ status;
	अचिन्हित पूर्णांक bit;

	/* mask all पूर्णांकerrupts to aव्योम flooding */
	status = mc_पढ़ोl(mc, MC_INTSTATUS) & mc->soc->पूर्णांकmask;
	अगर (!status)
		वापस IRQ_NONE;

	क्रम_each_set_bit(bit, &status, 32) अणु
		स्थिर अक्षर *direction = "read", *secure = "";
		स्थिर अक्षर *error = status_names[bit];
		स्थिर अक्षर *client, *desc;
		phys_addr_t addr;
		u32 value, reg;
		u8 id, type;

		चयन (BIT(bit)) अणु
		हाल MC_INT_DECERR_EMEM:
			reg = MC_DECERR_EMEM_OTHERS_STATUS;
			value = mc_पढ़ोl(mc, reg);

			id = value & mc->soc->client_id_mask;
			desc = error_names[2];

			अगर (value & BIT(31))
				direction = "write";
			अवरोध;

		हाल MC_INT_INVALID_GART_PAGE:
			reg = MC_GART_ERROR_REQ;
			value = mc_पढ़ोl(mc, reg);

			id = (value >> 1) & mc->soc->client_id_mask;
			desc = error_names[2];

			अगर (value & BIT(0))
				direction = "write";
			अवरोध;

		हाल MC_INT_SECURITY_VIOLATION:
			reg = MC_SECURITY_VIOLATION_STATUS;
			value = mc_पढ़ोl(mc, reg);

			id = value & mc->soc->client_id_mask;
			type = (value & BIT(30)) ? 4 : 3;
			desc = error_names[type];
			secure = "secure ";

			अगर (value & BIT(31))
				direction = "write";
			अवरोध;

		शेष:
			जारी;
		पूर्ण

		client = mc->soc->clients[id].name;
		addr = mc_पढ़ोl(mc, reg + माप(u32));

		dev_err_ratelimited(mc->dev, "%s: %s%s @%pa: %s (%s)\n",
				    client, secure, direction, &addr, error,
				    desc);
	पूर्ण

	/* clear पूर्णांकerrupts */
	mc_ग_लिखोl(mc, status, MC_INTSTATUS);

	वापस IRQ_HANDLED;
पूर्ण

/*
 * Memory Controller (MC) has few Memory Clients that are issuing memory
 * bandwidth allocation requests to the MC पूर्णांकerconnect provider. The MC
 * provider aggregates the requests and then sends the aggregated request
 * up to the External Memory Controller (EMC) पूर्णांकerconnect provider which
 * re-configures hardware पूर्णांकerface to External Memory (EMEM) in accordance
 * to the required bandwidth. Each MC पूर्णांकerconnect node represents an
 * inभागidual Memory Client.
 *
 * Memory पूर्णांकerconnect topology:
 *
 *               +----+
 * +--------+    |    |
 * | TEXSRD +--->+    |
 * +--------+    |    |
 *               |    |    +-----+    +------+
 *    ...        | MC +--->+ EMC +--->+ EMEM |
 *               |    |    +-----+    +------+
 * +--------+    |    |
 * | DISP.. +--->+    |
 * +--------+    |    |
 *               +----+
 */
अटल पूर्णांक tegra_mc_पूर्णांकerconnect_setup(काष्ठा tegra_mc *mc)
अणु
	काष्ठा icc_node *node;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	/* older device-trees करोn't have पूर्णांकerconnect properties */
	अगर (!device_property_present(mc->dev, "#interconnect-cells") ||
	    !mc->soc->icc_ops)
		वापस 0;

	mc->provider.dev = mc->dev;
	mc->provider.data = &mc->provider;
	mc->provider.set = mc->soc->icc_ops->set;
	mc->provider.aggregate = mc->soc->icc_ops->aggregate;
	mc->provider.xlate_extended = mc->soc->icc_ops->xlate_extended;

	err = icc_provider_add(&mc->provider);
	अगर (err)
		वापस err;

	/* create Memory Controller node */
	node = icc_node_create(TEGRA_ICC_MC);
	अगर (IS_ERR(node)) अणु
		err = PTR_ERR(node);
		जाओ del_provider;
	पूर्ण

	node->name = "Memory Controller";
	icc_node_add(node, &mc->provider);

	/* link Memory Controller to External Memory Controller */
	err = icc_link_create(node, TEGRA_ICC_EMC);
	अगर (err)
		जाओ हटाओ_nodes;

	क्रम (i = 0; i < mc->soc->num_clients; i++) अणु
		/* create MC client node */
		node = icc_node_create(mc->soc->clients[i].id);
		अगर (IS_ERR(node)) अणु
			err = PTR_ERR(node);
			जाओ हटाओ_nodes;
		पूर्ण

		node->name = mc->soc->clients[i].name;
		icc_node_add(node, &mc->provider);

		/* link Memory Client to Memory Controller */
		err = icc_link_create(node, TEGRA_ICC_MC);
		अगर (err)
			जाओ हटाओ_nodes;
	पूर्ण

	/*
	 * MC driver is रेजिस्टरed too early, so early that generic driver
	 * syncing करोesn't work for the MC. But it doesn't really matter
	 * since syncing works क्रम the EMC drivers, hence we can sync the
	 * MC driver by ourselves and then EMC will complete syncing of
	 * the whole ICC state.
	 */
	icc_sync_state(mc->dev);

	वापस 0;

हटाओ_nodes:
	icc_nodes_हटाओ(&mc->provider);
del_provider:
	icc_provider_del(&mc->provider);

	वापस err;
पूर्ण

अटल पूर्णांक tegra_mc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res;
	काष्ठा tegra_mc *mc;
	व्योम *isr;
	u64 mask;
	पूर्णांक err;

	mc = devm_kzalloc(&pdev->dev, माप(*mc), GFP_KERNEL);
	अगर (!mc)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, mc);
	spin_lock_init(&mc->lock);
	mc->soc = of_device_get_match_data(&pdev->dev);
	mc->dev = &pdev->dev;

	mask = DMA_BIT_MASK(mc->soc->num_address_bits);

	err = dma_coerce_mask_and_coherent(&pdev->dev, mask);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "failed to set DMA mask: %d\n", err);
		वापस err;
	पूर्ण

	/* length of MC tick in nanoseconds */
	mc->tick = 30;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	mc->regs = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(mc->regs))
		वापस PTR_ERR(mc->regs);

	mc->clk = devm_clk_get(&pdev->dev, "mc");
	अगर (IS_ERR(mc->clk)) अणु
		dev_err(&pdev->dev, "failed to get MC clock: %ld\n",
			PTR_ERR(mc->clk));
		वापस PTR_ERR(mc->clk);
	पूर्ण

#अगर_घोषित CONFIG_ARCH_TEGRA_2x_SOC
	अगर (mc->soc == &tegra20_mc_soc) अणु
		isr = tegra20_mc_irq;
	पूर्ण अन्यथा
#पूर्ण_अगर
	अणु
		/* ensure that debug features are disabled */
		mc_ग_लिखोl(mc, 0x00000000, MC_TIMING_CONTROL_DBG);

		err = tegra_mc_setup_latency_allowance(mc);
		अगर (err < 0) अणु
			dev_err(&pdev->dev,
				"failed to setup latency allowance: %d\n",
				err);
			वापस err;
		पूर्ण

		isr = tegra_mc_irq;

		err = tegra_mc_setup_timings(mc);
		अगर (err < 0) अणु
			dev_err(&pdev->dev, "failed to setup timings: %d\n",
				err);
			वापस err;
		पूर्ण
	पूर्ण

	mc->irq = platक्रमm_get_irq(pdev, 0);
	अगर (mc->irq < 0)
		वापस mc->irq;

	WARN(!mc->soc->client_id_mask, "missing client ID mask for this SoC\n");

	mc_ग_लिखोl(mc, mc->soc->पूर्णांकmask, MC_INTMASK);

	err = devm_request_irq(&pdev->dev, mc->irq, isr, 0,
			       dev_name(&pdev->dev), mc);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "failed to request IRQ#%u: %d\n", mc->irq,
			err);
		वापस err;
	पूर्ण

	mc->debugfs.root = debugfs_create_dir("mc", शून्य);

	अगर (mc->soc->init) अणु
		err = mc->soc->init(mc);
		अगर (err < 0)
			dev_err(&pdev->dev, "failed to initialize SoC driver: %d\n",
				err);
	पूर्ण

	err = tegra_mc_reset_setup(mc);
	अगर (err < 0)
		dev_err(&pdev->dev, "failed to register reset controller: %d\n",
			err);

	err = tegra_mc_पूर्णांकerconnect_setup(mc);
	अगर (err < 0)
		dev_err(&pdev->dev, "failed to initialize interconnect: %d\n",
			err);

	अगर (IS_ENABLED(CONFIG_TEGRA_IOMMU_SMMU) && mc->soc->smmu) अणु
		mc->smmu = tegra_smmu_probe(&pdev->dev, mc->soc->smmu, mc);
		अगर (IS_ERR(mc->smmu)) अणु
			dev_err(&pdev->dev, "failed to probe SMMU: %ld\n",
				PTR_ERR(mc->smmu));
			mc->smmu = शून्य;
		पूर्ण
	पूर्ण

	अगर (IS_ENABLED(CONFIG_TEGRA_IOMMU_GART) && !mc->soc->smmu) अणु
		mc->gart = tegra_gart_probe(&pdev->dev, mc);
		अगर (IS_ERR(mc->gart)) अणु
			dev_err(&pdev->dev, "failed to probe GART: %ld\n",
				PTR_ERR(mc->gart));
			mc->gart = शून्य;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_mc_suspend(काष्ठा device *dev)
अणु
	काष्ठा tegra_mc *mc = dev_get_drvdata(dev);
	पूर्णांक err;

	अगर (IS_ENABLED(CONFIG_TEGRA_IOMMU_GART) && mc->gart) अणु
		err = tegra_gart_suspend(mc->gart);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_mc_resume(काष्ठा device *dev)
अणु
	काष्ठा tegra_mc *mc = dev_get_drvdata(dev);
	पूर्णांक err;

	अगर (IS_ENABLED(CONFIG_TEGRA_IOMMU_GART) && mc->gart) अणु
		err = tegra_gart_resume(mc->gart);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops tegra_mc_pm_ops = अणु
	.suspend = tegra_mc_suspend,
	.resume = tegra_mc_resume,
पूर्ण;

अटल काष्ठा platक्रमm_driver tegra_mc_driver = अणु
	.driver = अणु
		.name = "tegra-mc",
		.of_match_table = tegra_mc_of_match,
		.pm = &tegra_mc_pm_ops,
		.suppress_bind_attrs = true,
	पूर्ण,
	.prevent_deferred_probe = true,
	.probe = tegra_mc_probe,
पूर्ण;

अटल पूर्णांक tegra_mc_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&tegra_mc_driver);
पूर्ण
arch_initcall(tegra_mc_init);

MODULE_AUTHOR("Thierry Reding <treding@nvidia.com>");
MODULE_DESCRIPTION("NVIDIA Tegra Memory Controller driver");
MODULE_LICENSE("GPL v2");
