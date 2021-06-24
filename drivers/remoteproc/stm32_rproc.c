<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) STMicroelectronics 2018 - All Rights Reserved
 * Authors: Luकरोvic Barre <luकरोvic.barre@st.com> क्रम STMicroelectronics.
 *          Fabien Dessenne <fabien.dessenne@st.com> क्रम STMicroelectronics.
 */

#समावेश <linux/arm-smccc.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/mailbox_client.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_reserved_स्मृति.स>
#समावेश <linux/pm_wakeirq.h>
#समावेश <linux/regmap.h>
#समावेश <linux/remoteproc.h>
#समावेश <linux/reset.h>
#समावेश <linux/slab.h>
#समावेश <linux/workqueue.h>

#समावेश "remoteproc_internal.h"

#घोषणा HOLD_BOOT		0
#घोषणा RELEASE_BOOT		1

#घोषणा MBOX_NB_VQ		2
#घोषणा MBOX_NB_MBX		4

#घोषणा STM32_SMC_RCC		0x82001000
#घोषणा STM32_SMC_REG_WRITE	0x1

#घोषणा STM32_MBX_VQ0		"vq0"
#घोषणा STM32_MBX_VQ0_ID	0
#घोषणा STM32_MBX_VQ1		"vq1"
#घोषणा STM32_MBX_VQ1_ID	1
#घोषणा STM32_MBX_SHUTDOWN	"shutdown"
#घोषणा STM32_MBX_DETACH	"detach"

#घोषणा RSC_TBL_SIZE		1024

#घोषणा M4_STATE_OFF		0
#घोषणा M4_STATE_INI		1
#घोषणा M4_STATE_CRUN		2
#घोषणा M4_STATE_CSTOP		3
#घोषणा M4_STATE_STANDBY	4
#घोषणा M4_STATE_CRASH		5

काष्ठा sपंचांग32_syscon अणु
	काष्ठा regmap *map;
	u32 reg;
	u32 mask;
पूर्ण;

काष्ठा sपंचांग32_rproc_mem अणु
	अक्षर name[20];
	व्योम __iomem *cpu_addr;
	phys_addr_t bus_addr;
	u32 dev_addr;
	माप_प्रकार size;
पूर्ण;

काष्ठा sपंचांग32_rproc_mem_ranges अणु
	u32 dev_addr;
	u32 bus_addr;
	u32 size;
पूर्ण;

काष्ठा sपंचांग32_mbox अणु
	स्थिर अचिन्हित अक्षर name[10];
	काष्ठा mbox_chan *chan;
	काष्ठा mbox_client client;
	काष्ठा work_काष्ठा vq_work;
	पूर्णांक vq_id;
पूर्ण;

काष्ठा sपंचांग32_rproc अणु
	काष्ठा reset_control *rst;
	काष्ठा sपंचांग32_syscon hold_boot;
	काष्ठा sपंचांग32_syscon pdds;
	काष्ठा sपंचांग32_syscon m4_state;
	काष्ठा sपंचांग32_syscon rsctbl;
	पूर्णांक wdg_irq;
	u32 nb_rmems;
	काष्ठा sपंचांग32_rproc_mem *rmems;
	काष्ठा sपंचांग32_mbox mb[MBOX_NB_MBX];
	काष्ठा workqueue_काष्ठा *workqueue;
	bool secured_soc;
	व्योम __iomem *rsc_va;
पूर्ण;

अटल पूर्णांक sपंचांग32_rproc_pa_to_da(काष्ठा rproc *rproc, phys_addr_t pa, u64 *da)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा sपंचांग32_rproc *ddata = rproc->priv;
	काष्ठा sपंचांग32_rproc_mem *p_mem;

	क्रम (i = 0; i < ddata->nb_rmems; i++) अणु
		p_mem = &ddata->rmems[i];

		अगर (pa < p_mem->bus_addr ||
		    pa >= p_mem->bus_addr + p_mem->size)
			जारी;
		*da = pa - p_mem->bus_addr + p_mem->dev_addr;
		dev_dbg(rproc->dev.parent, "pa %pa to da %llx\n", &pa, *da);
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक sपंचांग32_rproc_mem_alloc(काष्ठा rproc *rproc,
				 काष्ठा rproc_mem_entry *mem)
अणु
	काष्ठा device *dev = rproc->dev.parent;
	व्योम *va;

	dev_dbg(dev, "map memory: %pa+%x\n", &mem->dma, mem->len);
	va = ioremap_wc(mem->dma, mem->len);
	अगर (IS_ERR_OR_शून्य(va)) अणु
		dev_err(dev, "Unable to map memory region: %pa+%x\n",
			&mem->dma, mem->len);
		वापस -ENOMEM;
	पूर्ण

	/* Update memory entry va */
	mem->va = va;

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_rproc_mem_release(काष्ठा rproc *rproc,
				   काष्ठा rproc_mem_entry *mem)
अणु
	dev_dbg(rproc->dev.parent, "unmap memory: %pa\n", &mem->dma);
	iounmap(mem->va);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_rproc_of_memory_translations(काष्ठा platक्रमm_device *pdev,
					      काष्ठा sपंचांग32_rproc *ddata)
अणु
	काष्ठा device *parent, *dev = &pdev->dev;
	काष्ठा device_node *np;
	काष्ठा sपंचांग32_rproc_mem *p_mems;
	काष्ठा sपंचांग32_rproc_mem_ranges *mem_range;
	पूर्णांक cnt, array_size, i, ret = 0;

	parent = dev->parent;
	np = parent->of_node;

	cnt = of_property_count_elems_of_size(np, "dma-ranges",
					      माप(*mem_range));
	अगर (cnt <= 0) अणु
		dev_err(dev, "%s: dma-ranges property not defined\n", __func__);
		वापस -EINVAL;
	पूर्ण

	p_mems = devm_kसुस्मृति(dev, cnt, माप(*p_mems), GFP_KERNEL);
	अगर (!p_mems)
		वापस -ENOMEM;
	mem_range = kसुस्मृति(cnt, माप(*mem_range), GFP_KERNEL);
	अगर (!mem_range)
		वापस -ENOMEM;

	array_size = cnt * माप(काष्ठा sपंचांग32_rproc_mem_ranges) / माप(u32);

	ret = of_property_पढ़ो_u32_array(np, "dma-ranges",
					 (u32 *)mem_range, array_size);
	अगर (ret) अणु
		dev_err(dev, "error while get dma-ranges property: %x\n", ret);
		जाओ मुक्त_mem;
	पूर्ण

	क्रम (i = 0; i < cnt; i++) अणु
		p_mems[i].bus_addr = mem_range[i].bus_addr;
		p_mems[i].dev_addr = mem_range[i].dev_addr;
		p_mems[i].size     = mem_range[i].size;

		dev_dbg(dev, "memory range[%i]: da %#x, pa %pa, size %#zx:\n",
			i, p_mems[i].dev_addr, &p_mems[i].bus_addr,
			p_mems[i].size);
	पूर्ण

	ddata->rmems = p_mems;
	ddata->nb_rmems = cnt;

मुक्त_mem:
	kमुक्त(mem_range);
	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांग32_rproc_mbox_idx(काष्ठा rproc *rproc, स्थिर अचिन्हित अक्षर *name)
अणु
	काष्ठा sपंचांग32_rproc *ddata = rproc->priv;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(ddata->mb); i++) अणु
		अगर (!म_भेदन(ddata->mb[i].name, name, म_माप(name)))
			वापस i;
	पूर्ण
	dev_err(&rproc->dev, "mailbox %s not found\n", name);

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक sपंचांग32_rproc_prepare(काष्ठा rproc *rproc)
अणु
	काष्ठा device *dev = rproc->dev.parent;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा of_phandle_iterator it;
	काष्ठा rproc_mem_entry *mem;
	काष्ठा reserved_mem *rmem;
	u64 da;
	पूर्णांक index = 0;

	/* Register associated reserved memory regions */
	of_phandle_iterator_init(&it, np, "memory-region", शून्य, 0);
	जबतक (of_phandle_iterator_next(&it) == 0) अणु
		rmem = of_reserved_mem_lookup(it.node);
		अगर (!rmem) अणु
			dev_err(dev, "unable to acquire memory-region\n");
			वापस -EINVAL;
		पूर्ण

		अगर (sपंचांग32_rproc_pa_to_da(rproc, rmem->base, &da) < 0) अणु
			dev_err(dev, "memory region not valid %pa\n",
				&rmem->base);
			वापस -EINVAL;
		पूर्ण

		/*  No need to map vdev buffer */
		अगर (म_भेद(it.node->name, "vdev0buffer")) अणु
			/* Register memory region */
			mem = rproc_mem_entry_init(dev, शून्य,
						   (dma_addr_t)rmem->base,
						   rmem->size, da,
						   sपंचांग32_rproc_mem_alloc,
						   sपंचांग32_rproc_mem_release,
						   it.node->name);

			अगर (mem)
				rproc_coredump_add_segment(rproc, da,
							   rmem->size);
		पूर्ण अन्यथा अणु
			/* Register reserved memory क्रम vdev buffer alloc */
			mem = rproc_of_resm_mem_entry_init(dev, index,
							   rmem->size,
							   rmem->base,
							   it.node->name);
		पूर्ण

		अगर (!mem)
			वापस -ENOMEM;

		rproc_add_carveout(rproc, mem);
		index++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_rproc_parse_fw(काष्ठा rproc *rproc, स्थिर काष्ठा firmware *fw)
अणु
	अगर (rproc_elf_load_rsc_table(rproc, fw))
		dev_warn(&rproc->dev, "no resource table found for this firmware\n");

	वापस 0;
पूर्ण

अटल irqवापस_t sपंचांग32_rproc_wdg(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा platक्रमm_device *pdev = data;
	काष्ठा rproc *rproc = platक्रमm_get_drvdata(pdev);

	rproc_report_crash(rproc, RPROC_WATCHDOG);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम sपंचांग32_rproc_mb_vq_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा sपंचांग32_mbox *mb = container_of(work, काष्ठा sपंचांग32_mbox, vq_work);
	काष्ठा rproc *rproc = dev_get_drvdata(mb->client.dev);

	अगर (rproc_vq_पूर्णांकerrupt(rproc, mb->vq_id) == IRQ_NONE)
		dev_dbg(&rproc->dev, "no message found in vq%d\n", mb->vq_id);
पूर्ण

अटल व्योम sपंचांग32_rproc_mb_callback(काष्ठा mbox_client *cl, व्योम *data)
अणु
	काष्ठा rproc *rproc = dev_get_drvdata(cl->dev);
	काष्ठा sपंचांग32_mbox *mb = container_of(cl, काष्ठा sपंचांग32_mbox, client);
	काष्ठा sपंचांग32_rproc *ddata = rproc->priv;

	queue_work(ddata->workqueue, &mb->vq_work);
पूर्ण

अटल व्योम sपंचांग32_rproc_मुक्त_mbox(काष्ठा rproc *rproc)
अणु
	काष्ठा sपंचांग32_rproc *ddata = rproc->priv;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(ddata->mb); i++) अणु
		अगर (ddata->mb[i].chan)
			mbox_मुक्त_channel(ddata->mb[i].chan);
		ddata->mb[i].chan = शून्य;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा sपंचांग32_mbox sपंचांग32_rproc_mbox[MBOX_NB_MBX] = अणु
	अणु
		.name = STM32_MBX_VQ0,
		.vq_id = STM32_MBX_VQ0_ID,
		.client = अणु
			.rx_callback = sपंचांग32_rproc_mb_callback,
			.tx_block = false,
		पूर्ण,
	पूर्ण,
	अणु
		.name = STM32_MBX_VQ1,
		.vq_id = STM32_MBX_VQ1_ID,
		.client = अणु
			.rx_callback = sपंचांग32_rproc_mb_callback,
			.tx_block = false,
		पूर्ण,
	पूर्ण,
	अणु
		.name = STM32_MBX_SHUTDOWN,
		.vq_id = -1,
		.client = अणु
			.tx_block = true,
			.tx_करोne = शून्य,
			.tx_tout = 500, /* 500 ms समय out */
		पूर्ण,
	पूर्ण,
	अणु
		.name = STM32_MBX_DETACH,
		.vq_id = -1,
		.client = अणु
			.tx_block = true,
			.tx_करोne = शून्य,
			.tx_tout = 200, /* 200 ms समय out to detach should be fair enough */
		पूर्ण,
	पूर्ण
पूर्ण;

अटल पूर्णांक sपंचांग32_rproc_request_mbox(काष्ठा rproc *rproc)
अणु
	काष्ठा sपंचांग32_rproc *ddata = rproc->priv;
	काष्ठा device *dev = &rproc->dev;
	अचिन्हित पूर्णांक i;
	पूर्णांक j;
	स्थिर अचिन्हित अक्षर *name;
	काष्ठा mbox_client *cl;

	/* Initialise mailbox काष्ठाure table */
	स_नकल(ddata->mb, sपंचांग32_rproc_mbox, माप(sपंचांग32_rproc_mbox));

	क्रम (i = 0; i < MBOX_NB_MBX; i++) अणु
		name = ddata->mb[i].name;

		cl = &ddata->mb[i].client;
		cl->dev = dev->parent;

		ddata->mb[i].chan = mbox_request_channel_byname(cl, name);
		अगर (IS_ERR(ddata->mb[i].chan)) अणु
			अगर (PTR_ERR(ddata->mb[i].chan) == -EPROBE_DEFER) अणु
				dev_err_probe(dev->parent,
					      PTR_ERR(ddata->mb[i].chan),
					      "failed to request mailbox %s\n",
					      name);
				जाओ err_probe;
			पूर्ण
			dev_warn(dev, "cannot get %s mbox\n", name);
			ddata->mb[i].chan = शून्य;
		पूर्ण
		अगर (ddata->mb[i].vq_id >= 0) अणु
			INIT_WORK(&ddata->mb[i].vq_work,
				  sपंचांग32_rproc_mb_vq_work);
		पूर्ण
	पूर्ण

	वापस 0;

err_probe:
	क्रम (j = i - 1; j >= 0; j--)
		अगर (ddata->mb[j].chan)
			mbox_मुक्त_channel(ddata->mb[j].chan);
	वापस -EPROBE_DEFER;
पूर्ण

अटल पूर्णांक sपंचांग32_rproc_set_hold_boot(काष्ठा rproc *rproc, bool hold)
अणु
	काष्ठा sपंचांग32_rproc *ddata = rproc->priv;
	काष्ठा sपंचांग32_syscon hold_boot = ddata->hold_boot;
	काष्ठा arm_smccc_res smc_res;
	पूर्णांक val, err;

	val = hold ? HOLD_BOOT : RELEASE_BOOT;

	अगर (IS_ENABLED(CONFIG_HAVE_ARM_SMCCC) && ddata->secured_soc) अणु
		arm_smccc_smc(STM32_SMC_RCC, STM32_SMC_REG_WRITE,
			      hold_boot.reg, val, 0, 0, 0, 0, &smc_res);
		err = smc_res.a0;
	पूर्ण अन्यथा अणु
		err = regmap_update_bits(hold_boot.map, hold_boot.reg,
					 hold_boot.mask, val);
	पूर्ण

	अगर (err)
		dev_err(&rproc->dev, "failed to set hold boot\n");

	वापस err;
पूर्ण

अटल व्योम sपंचांग32_rproc_add_coredump_trace(काष्ठा rproc *rproc)
अणु
	काष्ठा rproc_debug_trace *trace;
	काष्ठा rproc_dump_segment *segment;
	bool alपढ़ोy_added;

	list_क्रम_each_entry(trace, &rproc->traces, node) अणु
		alपढ़ोy_added = false;

		list_क्रम_each_entry(segment, &rproc->dump_segments, node) अणु
			अगर (segment->da == trace->trace_mem.da) अणु
				alपढ़ोy_added = true;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (!alपढ़ोy_added)
			rproc_coredump_add_segment(rproc, trace->trace_mem.da,
						   trace->trace_mem.len);
	पूर्ण
पूर्ण

अटल पूर्णांक sपंचांग32_rproc_start(काष्ठा rproc *rproc)
अणु
	काष्ठा sपंचांग32_rproc *ddata = rproc->priv;
	पूर्णांक err;

	sपंचांग32_rproc_add_coredump_trace(rproc);

	/* clear remote proc Deep Sleep */
	अगर (ddata->pdds.map) अणु
		err = regmap_update_bits(ddata->pdds.map, ddata->pdds.reg,
					 ddata->pdds.mask, 0);
		अगर (err) अणु
			dev_err(&rproc->dev, "failed to clear pdds\n");
			वापस err;
		पूर्ण
	पूर्ण

	err = sपंचांग32_rproc_set_hold_boot(rproc, false);
	अगर (err)
		वापस err;

	वापस sपंचांग32_rproc_set_hold_boot(rproc, true);
पूर्ण

अटल पूर्णांक sपंचांग32_rproc_attach(काष्ठा rproc *rproc)
अणु
	sपंचांग32_rproc_add_coredump_trace(rproc);

	वापस sपंचांग32_rproc_set_hold_boot(rproc, true);
पूर्ण

अटल पूर्णांक sपंचांग32_rproc_detach(काष्ठा rproc *rproc)
अणु
	काष्ठा sपंचांग32_rproc *ddata = rproc->priv;
	पूर्णांक err, dummy_data, idx;

	/* Inक्रमm the remote processor of the detach */
	idx = sपंचांग32_rproc_mbox_idx(rproc, STM32_MBX_DETACH);
	अगर (idx >= 0 && ddata->mb[idx].chan) अणु
		/* A dummy data is sent to allow to block on transmit */
		err = mbox_send_message(ddata->mb[idx].chan,
					&dummy_data);
		अगर (err < 0)
			dev_warn(&rproc->dev, "warning: remote FW detach without ack\n");
	पूर्ण

	/* Allow remote processor to स्वतः-reboot */
	वापस sपंचांग32_rproc_set_hold_boot(rproc, false);
पूर्ण

अटल पूर्णांक sपंचांग32_rproc_stop(काष्ठा rproc *rproc)
अणु
	काष्ठा sपंचांग32_rproc *ddata = rproc->priv;
	पूर्णांक err, dummy_data, idx;

	/* request shutकरोwn of the remote processor */
	अगर (rproc->state != RPROC_OFFLINE) अणु
		idx = sपंचांग32_rproc_mbox_idx(rproc, STM32_MBX_SHUTDOWN);
		अगर (idx >= 0 && ddata->mb[idx].chan) अणु
			/* a dummy data is sent to allow to block on transmit */
			err = mbox_send_message(ddata->mb[idx].chan,
						&dummy_data);
			अगर (err < 0)
				dev_warn(&rproc->dev, "warning: remote FW shutdown without ack\n");
		पूर्ण
	पूर्ण

	err = sपंचांग32_rproc_set_hold_boot(rproc, true);
	अगर (err)
		वापस err;

	err = reset_control_निश्चित(ddata->rst);
	अगर (err) अणु
		dev_err(&rproc->dev, "failed to assert the reset\n");
		वापस err;
	पूर्ण

	/* to allow platक्रमm Standby घातer mode, set remote proc Deep Sleep */
	अगर (ddata->pdds.map) अणु
		err = regmap_update_bits(ddata->pdds.map, ddata->pdds.reg,
					 ddata->pdds.mask, 1);
		अगर (err) अणु
			dev_err(&rproc->dev, "failed to set pdds\n");
			वापस err;
		पूर्ण
	पूर्ण

	/* update coprocessor state to OFF अगर available */
	अगर (ddata->m4_state.map) अणु
		err = regmap_update_bits(ddata->m4_state.map,
					 ddata->m4_state.reg,
					 ddata->m4_state.mask,
					 M4_STATE_OFF);
		अगर (err) अणु
			dev_err(&rproc->dev, "failed to set copro state\n");
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम sपंचांग32_rproc_kick(काष्ठा rproc *rproc, पूर्णांक vqid)
अणु
	काष्ठा sपंचांग32_rproc *ddata = rproc->priv;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	अगर (WARN_ON(vqid >= MBOX_NB_VQ))
		वापस;

	क्रम (i = 0; i < MBOX_NB_MBX; i++) अणु
		अगर (vqid != ddata->mb[i].vq_id)
			जारी;
		अगर (!ddata->mb[i].chan)
			वापस;
		err = mbox_send_message(ddata->mb[i].chan, (व्योम *)(दीर्घ)vqid);
		अगर (err < 0)
			dev_err(&rproc->dev, "%s: failed (%s, err:%d)\n",
				__func__, ddata->mb[i].name, err);
		वापस;
	पूर्ण
पूर्ण

अटल पूर्णांक sपंचांग32_rproc_da_to_pa(काष्ठा rproc *rproc,
				u64 da, phys_addr_t *pa)
अणु
	काष्ठा sपंचांग32_rproc *ddata = rproc->priv;
	काष्ठा device *dev = rproc->dev.parent;
	काष्ठा sपंचांग32_rproc_mem *p_mem;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ddata->nb_rmems; i++) अणु
		p_mem = &ddata->rmems[i];

		अगर (da < p_mem->dev_addr ||
		    da >= p_mem->dev_addr + p_mem->size)
			जारी;

		*pa = da - p_mem->dev_addr + p_mem->bus_addr;
		dev_dbg(dev, "da %llx to pa %#x\n", da, *pa);

		वापस 0;
	पूर्ण

	dev_err(dev, "can't translate da %llx\n", da);

	वापस -EINVAL;
पूर्ण

अटल काष्ठा resource_table *
sपंचांग32_rproc_get_loaded_rsc_table(काष्ठा rproc *rproc, माप_प्रकार *table_sz)
अणु
	काष्ठा sपंचांग32_rproc *ddata = rproc->priv;
	काष्ठा device *dev = rproc->dev.parent;
	phys_addr_t rsc_pa;
	u32 rsc_da;
	पूर्णांक err;

	/* The resource table has alपढ़ोy been mapped, nothing to करो */
	अगर (ddata->rsc_va)
		जाओ करोne;

	err = regmap_पढ़ो(ddata->rsctbl.map, ddata->rsctbl.reg, &rsc_da);
	अगर (err) अणु
		dev_err(dev, "failed to read rsc tbl addr\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (!rsc_da)
		/* no rsc table */
		वापस ERR_PTR(-ENOENT);

	err = sपंचांग32_rproc_da_to_pa(rproc, rsc_da, &rsc_pa);
	अगर (err)
		वापस ERR_PTR(err);

	ddata->rsc_va = devm_ioremap_wc(dev, rsc_pa, RSC_TBL_SIZE);
	अगर (IS_ERR_OR_शून्य(ddata->rsc_va)) अणु
		dev_err(dev, "Unable to map memory region: %pa+%zx\n",
			&rsc_pa, RSC_TBL_SIZE);
		ddata->rsc_va = शून्य;
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

करोne:
	/*
	 * Assuming the resource table fits in 1kB is fair.
	 * Notice क्रम the detach, that this 1 kB memory area has to be reserved in the coprocessor
	 * firmware क्रम the resource table. On detach, the remoteproc core re-initializes this
	 * entire area by overwriting it with the initial values stored in rproc->clean_table.
	 */
	*table_sz = RSC_TBL_SIZE;
	वापस (काष्ठा resource_table *)ddata->rsc_va;
पूर्ण

अटल स्थिर काष्ठा rproc_ops st_rproc_ops = अणु
	.prepare	= sपंचांग32_rproc_prepare,
	.start		= sपंचांग32_rproc_start,
	.stop		= sपंचांग32_rproc_stop,
	.attach		= sपंचांग32_rproc_attach,
	.detach		= sपंचांग32_rproc_detach,
	.kick		= sपंचांग32_rproc_kick,
	.load		= rproc_elf_load_segments,
	.parse_fw	= sपंचांग32_rproc_parse_fw,
	.find_loaded_rsc_table = rproc_elf_find_loaded_rsc_table,
	.get_loaded_rsc_table = sपंचांग32_rproc_get_loaded_rsc_table,
	.sanity_check	= rproc_elf_sanity_check,
	.get_boot_addr	= rproc_elf_get_boot_addr,
पूर्ण;

अटल स्थिर काष्ठा of_device_id sपंचांग32_rproc_match[] = अणु
	अणु .compatible = "st,stm32mp1-m4" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sपंचांग32_rproc_match);

अटल पूर्णांक sपंचांग32_rproc_get_syscon(काष्ठा device_node *np, स्थिर अक्षर *prop,
				  काष्ठा sपंचांग32_syscon *syscon)
अणु
	पूर्णांक err = 0;

	syscon->map = syscon_regmap_lookup_by_phandle(np, prop);
	अगर (IS_ERR(syscon->map)) अणु
		err = PTR_ERR(syscon->map);
		syscon->map = शून्य;
		जाओ out;
	पूर्ण

	err = of_property_पढ़ो_u32_index(np, prop, 1, &syscon->reg);
	अगर (err)
		जाओ out;

	err = of_property_पढ़ो_u32_index(np, prop, 2, &syscon->mask);

out:
	वापस err;
पूर्ण

अटल पूर्णांक sपंचांग32_rproc_parse_dt(काष्ठा platक्रमm_device *pdev,
				काष्ठा sपंचांग32_rproc *ddata, bool *स्वतः_boot)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा sपंचांग32_syscon tz;
	अचिन्हित पूर्णांक tzen;
	पूर्णांक err, irq;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq == -EPROBE_DEFER)
		वापस dev_err_probe(dev, irq, "failed to get interrupt\n");

	अगर (irq > 0) अणु
		err = devm_request_irq(dev, irq, sपंचांग32_rproc_wdg, 0,
				       dev_name(dev), pdev);
		अगर (err)
			वापस dev_err_probe(dev, err,
					     "failed to request wdg irq\n");

		ddata->wdg_irq = irq;

		अगर (of_property_पढ़ो_bool(np, "wakeup-source")) अणु
			device_init_wakeup(dev, true);
			dev_pm_set_wake_irq(dev, irq);
		पूर्ण

		dev_info(dev, "wdg irq registered\n");
	पूर्ण

	ddata->rst = devm_reset_control_get_by_index(dev, 0);
	अगर (IS_ERR(ddata->rst))
		वापस dev_err_probe(dev, PTR_ERR(ddata->rst),
				     "failed to get mcu_reset\n");

	/*
	 * अगर platक्रमm is secured the hold boot bit must be written by
	 * smc call and पढ़ो normally.
	 * अगर not secure the hold boot bit could be पढ़ो/ग_लिखो normally
	 */
	err = sपंचांग32_rproc_get_syscon(np, "st,syscfg-tz", &tz);
	अगर (err) अणु
		dev_err(dev, "failed to get tz syscfg\n");
		वापस err;
	पूर्ण

	err = regmap_पढ़ो(tz.map, tz.reg, &tzen);
	अगर (err) अणु
		dev_err(dev, "failed to read tzen\n");
		वापस err;
	पूर्ण
	ddata->secured_soc = tzen & tz.mask;

	err = sपंचांग32_rproc_get_syscon(np, "st,syscfg-holdboot",
				     &ddata->hold_boot);
	अगर (err) अणु
		dev_err(dev, "failed to get hold boot\n");
		वापस err;
	पूर्ण

	err = sपंचांग32_rproc_get_syscon(np, "st,syscfg-pdds", &ddata->pdds);
	अगर (err)
		dev_info(dev, "failed to get pdds\n");

	*स्वतः_boot = of_property_पढ़ो_bool(np, "st,auto-boot");

	/*
	 * See अगर we can check the M4 status, i.e अगर it was started
	 * from the boot loader or not.
	 */
	err = sपंचांग32_rproc_get_syscon(np, "st,syscfg-m4-state",
				     &ddata->m4_state);
	अगर (err) अणु
		/* remember this */
		ddata->m4_state.map = शून्य;
		/* no coprocessor state syscon (optional) */
		dev_warn(dev, "m4 state not supported\n");

		/* no need to go further */
		वापस 0;
	पूर्ण

	/* See अगर we can get the resource table */
	err = sपंचांग32_rproc_get_syscon(np, "st,syscfg-rsc-tbl",
				     &ddata->rsctbl);
	अगर (err) अणु
		/* no rsc table syscon (optional) */
		dev_warn(dev, "rsc tbl syscon not supported\n");
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_rproc_get_m4_status(काष्ठा sपंचांग32_rproc *ddata,
				     अचिन्हित पूर्णांक *state)
अणु
	/* See sपंचांग32_rproc_parse_dt() */
	अगर (!ddata->m4_state.map) अणु
		/*
		 * We couldn't get the coprocessor's state, assume
		 * it is not running.
		 */
		*state = M4_STATE_OFF;
		वापस 0;
	पूर्ण

	वापस regmap_पढ़ो(ddata->m4_state.map, ddata->m4_state.reg, state);
पूर्ण

अटल पूर्णांक sपंचांग32_rproc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा sपंचांग32_rproc *ddata;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा rproc *rproc;
	अचिन्हित पूर्णांक state;
	पूर्णांक ret;

	ret = dma_coerce_mask_and_coherent(dev, DMA_BIT_MASK(32));
	अगर (ret)
		वापस ret;

	rproc = rproc_alloc(dev, np->name, &st_rproc_ops, शून्य, माप(*ddata));
	अगर (!rproc)
		वापस -ENOMEM;

	ddata = rproc->priv;

	rproc_coredump_set_elf_info(rproc, ELFCLASS32, EM_NONE);

	ret = sपंचांग32_rproc_parse_dt(pdev, ddata, &rproc->स्वतः_boot);
	अगर (ret)
		जाओ मुक्त_rproc;

	ret = sपंचांग32_rproc_of_memory_translations(pdev, ddata);
	अगर (ret)
		जाओ मुक्त_rproc;

	ret = sपंचांग32_rproc_get_m4_status(ddata, &state);
	अगर (ret)
		जाओ मुक्त_rproc;

	अगर (state == M4_STATE_CRUN)
		rproc->state = RPROC_DETACHED;

	rproc->has_iommu = false;
	ddata->workqueue = create_workqueue(dev_name(dev));
	अगर (!ddata->workqueue) अणु
		dev_err(dev, "cannot create workqueue\n");
		ret = -ENOMEM;
		जाओ मुक्त_resources;
	पूर्ण

	platक्रमm_set_drvdata(pdev, rproc);

	ret = sपंचांग32_rproc_request_mbox(rproc);
	अगर (ret)
		जाओ मुक्त_wkq;

	ret = rproc_add(rproc);
	अगर (ret)
		जाओ मुक्त_mb;

	वापस 0;

मुक्त_mb:
	sपंचांग32_rproc_मुक्त_mbox(rproc);
मुक्त_wkq:
	destroy_workqueue(ddata->workqueue);
मुक्त_resources:
	rproc_resource_cleanup(rproc);
मुक्त_rproc:
	अगर (device_may_wakeup(dev)) अणु
		dev_pm_clear_wake_irq(dev);
		device_init_wakeup(dev, false);
	पूर्ण
	rproc_मुक्त(rproc);
	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांग32_rproc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rproc *rproc = platक्रमm_get_drvdata(pdev);
	काष्ठा sपंचांग32_rproc *ddata = rproc->priv;
	काष्ठा device *dev = &pdev->dev;

	अगर (atomic_पढ़ो(&rproc->घातer) > 0)
		rproc_shutकरोwn(rproc);

	rproc_del(rproc);
	sपंचांग32_rproc_मुक्त_mbox(rproc);
	destroy_workqueue(ddata->workqueue);

	अगर (device_may_wakeup(dev)) अणु
		dev_pm_clear_wake_irq(dev);
		device_init_wakeup(dev, false);
	पूर्ण
	rproc_मुक्त(rproc);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused sपंचांग32_rproc_suspend(काष्ठा device *dev)
अणु
	काष्ठा rproc *rproc = dev_get_drvdata(dev);
	काष्ठा sपंचांग32_rproc *ddata = rproc->priv;

	अगर (device_may_wakeup(dev))
		वापस enable_irq_wake(ddata->wdg_irq);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused sपंचांग32_rproc_resume(काष्ठा device *dev)
अणु
	काष्ठा rproc *rproc = dev_get_drvdata(dev);
	काष्ठा sपंचांग32_rproc *ddata = rproc->priv;

	अगर (device_may_wakeup(dev))
		वापस disable_irq_wake(ddata->wdg_irq);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(sपंचांग32_rproc_pm_ops,
			 sपंचांग32_rproc_suspend, sपंचांग32_rproc_resume);

अटल काष्ठा platक्रमm_driver sपंचांग32_rproc_driver = अणु
	.probe = sपंचांग32_rproc_probe,
	.हटाओ = sपंचांग32_rproc_हटाओ,
	.driver = अणु
		.name = "stm32-rproc",
		.pm = &sपंचांग32_rproc_pm_ops,
		.of_match_table = of_match_ptr(sपंचांग32_rproc_match),
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(sपंचांग32_rproc_driver);

MODULE_DESCRIPTION("STM32 Remote Processor Control Driver");
MODULE_AUTHOR("Ludovic Barre <ludovic.barre@st.com>");
MODULE_AUTHOR("Fabien Dessenne <fabien.dessenne@st.com>");
MODULE_LICENSE("GPL v2");

