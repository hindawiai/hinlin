<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2013-2014, NVIDIA CORPORATION.  All rights reserved.
 *
 * Based on drivers/misc/eeprom/sunxi_sid.c
 */

#समावेश <linux/device.h>
#समावेश <linux/clk.h>
#समावेश <linux/completion.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/kobject.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/अक्रमom.h>

#समावेश <soc/tegra/fuse.h>

#समावेश "fuse.h"

#घोषणा FUSE_BEGIN	0x100
#घोषणा FUSE_UID_LOW	0x08
#घोषणा FUSE_UID_HIGH	0x0c

अटल u32 tegra20_fuse_पढ़ो_early(काष्ठा tegra_fuse *fuse, अचिन्हित पूर्णांक offset)
अणु
	वापस पढ़ोl_relaxed(fuse->base + FUSE_BEGIN + offset);
पूर्ण

अटल व्योम apb_dma_complete(व्योम *args)
अणु
	काष्ठा tegra_fuse *fuse = args;

	complete(&fuse->apbdma.रुको);
पूर्ण

अटल u32 tegra20_fuse_पढ़ो(काष्ठा tegra_fuse *fuse, अचिन्हित पूर्णांक offset)
अणु
	अचिन्हित दीर्घ flags = DMA_PREP_INTERRUPT | DMA_CTRL_ACK;
	काष्ठा dma_async_tx_descriptor *dma_desc;
	अचिन्हित दीर्घ समय_left;
	u32 value = 0;
	पूर्णांक err;

	mutex_lock(&fuse->apbdma.lock);

	fuse->apbdma.config.src_addr = fuse->phys + FUSE_BEGIN + offset;

	err = dmaengine_slave_config(fuse->apbdma.chan, &fuse->apbdma.config);
	अगर (err)
		जाओ out;

	dma_desc = dmaengine_prep_slave_single(fuse->apbdma.chan,
					       fuse->apbdma.phys,
					       माप(u32), DMA_DEV_TO_MEM,
					       flags);
	अगर (!dma_desc)
		जाओ out;

	dma_desc->callback = apb_dma_complete;
	dma_desc->callback_param = fuse;

	reinit_completion(&fuse->apbdma.रुको);

	clk_prepare_enable(fuse->clk);

	dmaengine_submit(dma_desc);
	dma_async_issue_pending(fuse->apbdma.chan);
	समय_left = रुको_क्रम_completion_समयout(&fuse->apbdma.रुको,
						msecs_to_jअगरfies(50));

	अगर (WARN(समय_left == 0, "apb read dma timed out"))
		dmaengine_terminate_all(fuse->apbdma.chan);
	अन्यथा
		value = *fuse->apbdma.virt;

	clk_disable_unprepare(fuse->clk);

out:
	mutex_unlock(&fuse->apbdma.lock);
	वापस value;
पूर्ण

अटल bool dma_filter(काष्ठा dma_chan *chan, व्योम *filter_param)
अणु
	काष्ठा device_node *np = chan->device->dev->of_node;

	वापस of_device_is_compatible(np, "nvidia,tegra20-apbdma");
पूर्ण

अटल पूर्णांक tegra20_fuse_probe(काष्ठा tegra_fuse *fuse)
अणु
	dma_cap_mask_t mask;

	dma_cap_zero(mask);
	dma_cap_set(DMA_SLAVE, mask);

	fuse->apbdma.chan = dma_request_channel(mask, dma_filter, शून्य);
	अगर (!fuse->apbdma.chan)
		वापस -EPROBE_DEFER;

	fuse->apbdma.virt = dma_alloc_coherent(fuse->dev, माप(u32),
					       &fuse->apbdma.phys,
					       GFP_KERNEL);
	अगर (!fuse->apbdma.virt) अणु
		dma_release_channel(fuse->apbdma.chan);
		वापस -ENOMEM;
	पूर्ण

	fuse->apbdma.config.src_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
	fuse->apbdma.config.dst_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
	fuse->apbdma.config.src_maxburst = 1;
	fuse->apbdma.config.dst_maxburst = 1;
	fuse->apbdma.config.direction = DMA_DEV_TO_MEM;
	fuse->apbdma.config.device_fc = false;

	init_completion(&fuse->apbdma.रुको);
	mutex_init(&fuse->apbdma.lock);
	fuse->पढ़ो = tegra20_fuse_पढ़ो;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा tegra_fuse_info tegra20_fuse_info = अणु
	.पढ़ो = tegra20_fuse_पढ़ो,
	.size = 0x1f8,
	.spare = 0x100,
पूर्ण;

/* Early boot code. This code is called beक्रमe the devices are created */

अटल व्योम __init tegra20_fuse_add_अक्रमomness(व्योम)
अणु
	u32 अक्रमomness[7];

	अक्रमomness[0] = tegra_sku_info.sku_id;
	अक्रमomness[1] = tegra_पढ़ो_straps();
	अक्रमomness[2] = tegra_पढ़ो_chipid();
	अक्रमomness[3] = tegra_sku_info.cpu_process_id << 16;
	अक्रमomness[3] |= tegra_sku_info.soc_process_id;
	अक्रमomness[4] = tegra_sku_info.cpu_speeकरो_id << 16;
	अक्रमomness[4] |= tegra_sku_info.soc_speeकरो_id;
	अक्रमomness[5] = tegra_fuse_पढ़ो_early(FUSE_UID_LOW);
	अक्रमomness[6] = tegra_fuse_पढ़ो_early(FUSE_UID_HIGH);

	add_device_अक्रमomness(अक्रमomness, माप(अक्रमomness));
पूर्ण

अटल व्योम __init tegra20_fuse_init(काष्ठा tegra_fuse *fuse)
अणु
	fuse->पढ़ो_early = tegra20_fuse_पढ़ो_early;

	tegra_init_revision();
	fuse->soc->speeकरो_init(&tegra_sku_info);
	tegra20_fuse_add_अक्रमomness();
पूर्ण

स्थिर काष्ठा tegra_fuse_soc tegra20_fuse_soc = अणु
	.init = tegra20_fuse_init,
	.speeकरो_init = tegra20_init_speeकरो_data,
	.probe = tegra20_fuse_probe,
	.info = &tegra20_fuse_info,
	.soc_attr_group = &tegra_soc_attr_group,
पूर्ण;
