<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Keystone accumulator queue manager
 *
 * Copyright (C) 2014 Texas Instruments Incorporated - http://www.ti.com
 * Author:	Sandeep Nair <sandeep_n@ti.com>
 *		Cyril Chemparathy <cyril@ti.com>
 *		Santosh Shilimkar <santosh.shilimkar@ti.com>
 */

#समावेश <linux/dma-mapping.h>
#समावेश <linux/पन.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/soc/ti/knav_qmss.h>

#समावेश "knav_qmss.h"

#घोषणा knav_range_offset_to_inst(kdev, range, q)	\
	(range->queue_base_inst + (q << kdev->inst_shअगरt))

अटल व्योम __knav_acc_notअगरy(काष्ठा knav_range_info *range,
				काष्ठा knav_acc_channel *acc)
अणु
	काष्ठा knav_device *kdev = range->kdev;
	काष्ठा knav_queue_inst *inst;
	पूर्णांक range_base, queue;

	range_base = kdev->base_id + range->queue_base;

	अगर (range->flags & RANGE_MULTI_QUEUE) अणु
		क्रम (queue = 0; queue < range->num_queues; queue++) अणु
			inst = knav_range_offset_to_inst(kdev, range,
								queue);
			अगर (inst->notअगरy_needed) अणु
				inst->notअगरy_needed = 0;
				dev_dbg(kdev->dev, "acc-irq: notifying %d\n",
					range_base + queue);
				knav_queue_notअगरy(inst);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		queue = acc->channel - range->acc_info.start_channel;
		inst = knav_range_offset_to_inst(kdev, range, queue);
		dev_dbg(kdev->dev, "acc-irq: notifying %d\n",
			range_base + queue);
		knav_queue_notअगरy(inst);
	पूर्ण
पूर्ण

अटल पूर्णांक knav_acc_set_notअगरy(काष्ठा knav_range_info *range,
				काष्ठा knav_queue_inst *kq,
				bool enabled)
अणु
	काष्ठा knav_pdsp_info *pdsp = range->acc_info.pdsp;
	काष्ठा knav_device *kdev = range->kdev;
	u32 mask, offset;

	/*
	 * when enabling, we need to re-trigger an पूर्णांकerrupt अगर we
	 * have descriptors pending
	 */
	अगर (!enabled || atomic_पढ़ो(&kq->desc_count) <= 0)
		वापस 0;

	kq->notअगरy_needed = 1;
	atomic_inc(&kq->acc->retrigger_count);
	mask = BIT(kq->acc->channel % 32);
	offset = ACC_INTD_OFFSET_STATUS(kq->acc->channel);
	dev_dbg(kdev->dev, "setup-notify: re-triggering irq for %s\n",
		kq->acc->name);
	ग_लिखोl_relaxed(mask, pdsp->पूर्णांकd + offset);
	वापस 0;
पूर्ण

अटल irqवापस_t knav_acc_पूर्णांक_handler(पूर्णांक irq, व्योम *_instdata)
अणु
	काष्ठा knav_acc_channel *acc;
	काष्ठा knav_queue_inst *kq = शून्य;
	काष्ठा knav_range_info *range;
	काष्ठा knav_pdsp_info *pdsp;
	काष्ठा knav_acc_info *info;
	काष्ठा knav_device *kdev;

	u32 *list, *list_cpu, val, idx, notअगरies;
	पूर्णांक range_base, channel, queue = 0;
	dma_addr_t list_dma;

	range = _instdata;
	info  = &range->acc_info;
	kdev  = range->kdev;
	pdsp  = range->acc_info.pdsp;
	acc   = range->acc;

	range_base = kdev->base_id + range->queue_base;
	अगर ((range->flags & RANGE_MULTI_QUEUE) == 0) अणु
		क्रम (queue = 0; queue < range->num_irqs; queue++)
			अगर (range->irqs[queue].irq == irq)
				अवरोध;
		kq = knav_range_offset_to_inst(kdev, range, queue);
		acc += queue;
	पूर्ण

	channel = acc->channel;
	list_dma = acc->list_dma[acc->list_index];
	list_cpu = acc->list_cpu[acc->list_index];
	dev_dbg(kdev->dev, "acc-irq: channel %d, list %d, virt %p, dma %pad\n",
		channel, acc->list_index, list_cpu, &list_dma);
	अगर (atomic_पढ़ो(&acc->retrigger_count)) अणु
		atomic_dec(&acc->retrigger_count);
		__knav_acc_notअगरy(range, acc);
		ग_लिखोl_relaxed(1, pdsp->पूर्णांकd + ACC_INTD_OFFSET_COUNT(channel));
		/* ack the पूर्णांकerrupt */
		ग_लिखोl_relaxed(ACC_CHANNEL_INT_BASE + channel,
			       pdsp->पूर्णांकd + ACC_INTD_OFFSET_EOI);

		वापस IRQ_HANDLED;
	पूर्ण

	notअगरies = पढ़ोl_relaxed(pdsp->पूर्णांकd + ACC_INTD_OFFSET_COUNT(channel));
	WARN_ON(!notअगरies);
	dma_sync_single_क्रम_cpu(kdev->dev, list_dma, info->list_size,
				DMA_FROM_DEVICE);

	क्रम (list = list_cpu; list < list_cpu + (info->list_size / माप(u32));
	     list += ACC_LIST_ENTRY_WORDS) अणु
		अगर (ACC_LIST_ENTRY_WORDS == 1) अणु
			dev_dbg(kdev->dev,
				"acc-irq: list %d, entry @%p, %08x\n",
				acc->list_index, list, list[0]);
		पूर्ण अन्यथा अगर (ACC_LIST_ENTRY_WORDS == 2) अणु
			dev_dbg(kdev->dev,
				"acc-irq: list %d, entry @%p, %08x %08x\n",
				acc->list_index, list, list[0], list[1]);
		पूर्ण अन्यथा अगर (ACC_LIST_ENTRY_WORDS == 4) अणु
			dev_dbg(kdev->dev,
				"acc-irq: list %d, entry @%p, %08x %08x %08x %08x\n",
				acc->list_index, list, list[0], list[1],
				list[2], list[3]);
		पूर्ण

		val = list[ACC_LIST_ENTRY_DESC_IDX];
		अगर (!val)
			अवरोध;

		अगर (range->flags & RANGE_MULTI_QUEUE) अणु
			queue = list[ACC_LIST_ENTRY_QUEUE_IDX] >> 16;
			अगर (queue < range_base ||
			    queue >= range_base + range->num_queues) अणु
				dev_err(kdev->dev,
					"bad queue %d, expecting %d-%d\n",
					queue, range_base,
					range_base + range->num_queues);
				अवरोध;
			पूर्ण
			queue -= range_base;
			kq = knav_range_offset_to_inst(kdev, range,
								queue);
		पूर्ण

		अगर (atomic_inc_वापस(&kq->desc_count) >= ACC_DESCS_MAX) अणु
			atomic_dec(&kq->desc_count);
			dev_err(kdev->dev,
				"acc-irq: queue %d full, entry dropped\n",
				queue + range_base);
			जारी;
		पूर्ण

		idx = atomic_inc_वापस(&kq->desc_tail) & ACC_DESCS_MASK;
		kq->descs[idx] = val;
		kq->notअगरy_needed = 1;
		dev_dbg(kdev->dev, "acc-irq: enqueue %08x at %d, queue %d\n",
			val, idx, queue + range_base);
	पूर्ण

	__knav_acc_notअगरy(range, acc);
	स_रखो(list_cpu, 0, info->list_size);
	dma_sync_single_क्रम_device(kdev->dev, list_dma, info->list_size,
				   DMA_TO_DEVICE);

	/* flip to the other list */
	acc->list_index ^= 1;

	/* reset the पूर्णांकerrupt counter */
	ग_लिखोl_relaxed(1, pdsp->पूर्णांकd + ACC_INTD_OFFSET_COUNT(channel));

	/* ack the पूर्णांकerrupt */
	ग_लिखोl_relaxed(ACC_CHANNEL_INT_BASE + channel,
		       pdsp->पूर्णांकd + ACC_INTD_OFFSET_EOI);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक knav_range_setup_acc_irq(काष्ठा knav_range_info *range,
				पूर्णांक queue, bool enabled)
अणु
	काष्ठा knav_device *kdev = range->kdev;
	काष्ठा knav_acc_channel *acc;
	काष्ठा cpumask *cpu_mask;
	पूर्णांक ret = 0, irq;
	u32 old, new;

	अगर (range->flags & RANGE_MULTI_QUEUE) अणु
		acc = range->acc;
		irq = range->irqs[0].irq;
		cpu_mask = range->irqs[0].cpu_mask;
	पूर्ण अन्यथा अणु
		acc = range->acc + queue;
		irq = range->irqs[queue].irq;
		cpu_mask = range->irqs[queue].cpu_mask;
	पूर्ण

	old = acc->खोलो_mask;
	अगर (enabled)
		new = old | BIT(queue);
	अन्यथा
		new = old & ~BIT(queue);
	acc->खोलो_mask = new;

	dev_dbg(kdev->dev,
		"setup-acc-irq: open mask old %08x, new %08x, channel %s\n",
		old, new, acc->name);

	अगर (likely(new == old))
		वापस 0;

	अगर (new && !old) अणु
		dev_dbg(kdev->dev,
			"setup-acc-irq: requesting %s for channel %s\n",
			acc->name, acc->name);
		ret = request_irq(irq, knav_acc_पूर्णांक_handler, 0, acc->name,
				  range);
		अगर (!ret && cpu_mask) अणु
			ret = irq_set_affinity_hपूर्णांक(irq, cpu_mask);
			अगर (ret) अणु
				dev_warn(range->kdev->dev,
					 "Failed to set IRQ affinity\n");
				वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (old && !new) अणु
		dev_dbg(kdev->dev, "setup-acc-irq: freeing %s for channel %s\n",
			acc->name, acc->name);
		ret = irq_set_affinity_hपूर्णांक(irq, शून्य);
		अगर (ret)
			dev_warn(range->kdev->dev,
				 "Failed to set IRQ affinity\n");
		मुक्त_irq(irq, range);
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर अक्षर *knav_acc_result_str(क्रमागत knav_acc_result result)
अणु
	अटल स्थिर अक्षर * स्थिर result_str[] = अणु
		[ACC_RET_IDLE]			= "idle",
		[ACC_RET_SUCCESS]		= "success",
		[ACC_RET_INVALID_COMMAND]	= "invalid command",
		[ACC_RET_INVALID_CHANNEL]	= "invalid channel",
		[ACC_RET_INACTIVE_CHANNEL]	= "inactive channel",
		[ACC_RET_ACTIVE_CHANNEL]	= "active channel",
		[ACC_RET_INVALID_QUEUE]		= "invalid queue",
		[ACC_RET_INVALID_RET]		= "invalid return code",
	पूर्ण;

	अगर (result >= ARRAY_SIZE(result_str))
		वापस result_str[ACC_RET_INVALID_RET];
	अन्यथा
		वापस result_str[result];
पूर्ण

अटल क्रमागत knav_acc_result
knav_acc_ग_लिखो(काष्ठा knav_device *kdev, काष्ठा knav_pdsp_info *pdsp,
		काष्ठा knav_reg_acc_command *cmd)
अणु
	u32 result;

	dev_dbg(kdev->dev, "acc command %08x %08x %08x %08x %08x\n",
		cmd->command, cmd->queue_mask, cmd->list_dma,
		cmd->queue_num, cmd->समयr_config);

	ग_लिखोl_relaxed(cmd->समयr_config, &pdsp->acc_command->समयr_config);
	ग_लिखोl_relaxed(cmd->queue_num, &pdsp->acc_command->queue_num);
	ग_लिखोl_relaxed(cmd->list_dma, &pdsp->acc_command->list_dma);
	ग_लिखोl_relaxed(cmd->queue_mask, &pdsp->acc_command->queue_mask);
	ग_लिखोl_relaxed(cmd->command, &pdsp->acc_command->command);

	/* रुको क्रम the command to clear */
	करो अणु
		result = पढ़ोl_relaxed(&pdsp->acc_command->command);
	पूर्ण जबतक ((result >> 8) & 0xff);

	वापस (result >> 24) & 0xff;
पूर्ण

अटल व्योम knav_acc_setup_cmd(काष्ठा knav_device *kdev,
				काष्ठा knav_range_info *range,
				काष्ठा knav_reg_acc_command *cmd,
				पूर्णांक queue)
अणु
	काष्ठा knav_acc_info *info = &range->acc_info;
	काष्ठा knav_acc_channel *acc;
	पूर्णांक queue_base;
	u32 queue_mask;

	अगर (range->flags & RANGE_MULTI_QUEUE) अणु
		acc = range->acc;
		queue_base = range->queue_base;
		queue_mask = BIT(range->num_queues) - 1;
	पूर्ण अन्यथा अणु
		acc = range->acc + queue;
		queue_base = range->queue_base + queue;
		queue_mask = 0;
	पूर्ण

	स_रखो(cmd, 0, माप(*cmd));
	cmd->command    = acc->channel;
	cmd->queue_mask = queue_mask;
	cmd->list_dma   = (u32)acc->list_dma[0];
	cmd->queue_num  = info->list_entries << 16;
	cmd->queue_num |= queue_base;

	cmd->समयr_config = ACC_LIST_ENTRY_TYPE << 18;
	अगर (range->flags & RANGE_MULTI_QUEUE)
		cmd->समयr_config |= ACC_CFG_MULTI_QUEUE;
	cmd->समयr_config |= info->pacing_mode << 16;
	cmd->समयr_config |= info->समयr_count;
पूर्ण

अटल व्योम knav_acc_stop(काष्ठा knav_device *kdev,
				काष्ठा knav_range_info *range,
				पूर्णांक queue)
अणु
	काष्ठा knav_reg_acc_command cmd;
	काष्ठा knav_acc_channel *acc;
	क्रमागत knav_acc_result result;

	acc = range->acc + queue;

	knav_acc_setup_cmd(kdev, range, &cmd, queue);
	cmd.command |= ACC_CMD_DISABLE_CHANNEL << 8;
	result = knav_acc_ग_लिखो(kdev, range->acc_info.pdsp, &cmd);

	dev_dbg(kdev->dev, "stopped acc channel %s, result %s\n",
		acc->name, knav_acc_result_str(result));
पूर्ण

अटल क्रमागत knav_acc_result knav_acc_start(काष्ठा knav_device *kdev,
						काष्ठा knav_range_info *range,
						पूर्णांक queue)
अणु
	काष्ठा knav_reg_acc_command cmd;
	काष्ठा knav_acc_channel *acc;
	क्रमागत knav_acc_result result;

	acc = range->acc + queue;

	knav_acc_setup_cmd(kdev, range, &cmd, queue);
	cmd.command |= ACC_CMD_ENABLE_CHANNEL << 8;
	result = knav_acc_ग_लिखो(kdev, range->acc_info.pdsp, &cmd);

	dev_dbg(kdev->dev, "started acc channel %s, result %s\n",
		acc->name, knav_acc_result_str(result));

	वापस result;
पूर्ण

अटल पूर्णांक knav_acc_init_range(काष्ठा knav_range_info *range)
अणु
	काष्ठा knav_device *kdev = range->kdev;
	काष्ठा knav_acc_channel *acc;
	क्रमागत knav_acc_result result;
	पूर्णांक queue;

	क्रम (queue = 0; queue < range->num_queues; queue++) अणु
		acc = range->acc + queue;

		knav_acc_stop(kdev, range, queue);
		acc->list_index = 0;
		result = knav_acc_start(kdev, range, queue);

		अगर (result != ACC_RET_SUCCESS)
			वापस -EIO;

		अगर (range->flags & RANGE_MULTI_QUEUE)
			वापस 0;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक knav_acc_init_queue(काष्ठा knav_range_info *range,
				काष्ठा knav_queue_inst *kq)
अणु
	अचिन्हित id = kq->id - range->queue_base;

	kq->descs = devm_kसुस्मृति(range->kdev->dev,
				 ACC_DESCS_MAX, माप(u32), GFP_KERNEL);
	अगर (!kq->descs)
		वापस -ENOMEM;

	kq->acc = range->acc;
	अगर ((range->flags & RANGE_MULTI_QUEUE) == 0)
		kq->acc += id;
	वापस 0;
पूर्ण

अटल पूर्णांक knav_acc_खोलो_queue(काष्ठा knav_range_info *range,
				काष्ठा knav_queue_inst *inst, अचिन्हित flags)
अणु
	अचिन्हित id = inst->id - range->queue_base;

	वापस knav_range_setup_acc_irq(range, id, true);
पूर्ण

अटल पूर्णांक knav_acc_बंद_queue(काष्ठा knav_range_info *range,
					काष्ठा knav_queue_inst *inst)
अणु
	अचिन्हित id = inst->id - range->queue_base;

	वापस knav_range_setup_acc_irq(range, id, false);
पूर्ण

अटल पूर्णांक knav_acc_मुक्त_range(काष्ठा knav_range_info *range)
अणु
	काष्ठा knav_device *kdev = range->kdev;
	काष्ठा knav_acc_channel *acc;
	काष्ठा knav_acc_info *info;
	पूर्णांक channel, channels;

	info = &range->acc_info;

	अगर (range->flags & RANGE_MULTI_QUEUE)
		channels = 1;
	अन्यथा
		channels = range->num_queues;

	क्रम (channel = 0; channel < channels; channel++) अणु
		acc = range->acc + channel;
		अगर (!acc->list_cpu[0])
			जारी;
		dma_unmap_single(kdev->dev, acc->list_dma[0],
				 info->mem_size, DMA_BIसूचीECTIONAL);
		मुक्त_pages_exact(acc->list_cpu[0], info->mem_size);
	पूर्ण
	devm_kमुक्त(range->kdev->dev, range->acc);
	वापस 0;
पूर्ण

अटल काष्ठा knav_range_ops knav_acc_range_ops = अणु
	.set_notअगरy	= knav_acc_set_notअगरy,
	.init_queue	= knav_acc_init_queue,
	.खोलो_queue	= knav_acc_खोलो_queue,
	.बंद_queue	= knav_acc_बंद_queue,
	.init_range	= knav_acc_init_range,
	.मुक्त_range	= knav_acc_मुक्त_range,
पूर्ण;

/**
 * knav_init_acc_range: Initialise accumulator ranges
 *
 * @kdev:		qmss device
 * @node:		device node
 * @range:		qmms range inक्रमmation
 *
 * Return 0 on success or error
 */
पूर्णांक knav_init_acc_range(काष्ठा knav_device *kdev,
			काष्ठा device_node *node,
			काष्ठा knav_range_info *range)
अणु
	काष्ठा knav_acc_channel *acc;
	काष्ठा knav_pdsp_info *pdsp;
	काष्ठा knav_acc_info *info;
	पूर्णांक ret, channel, channels;
	पूर्णांक list_size, mem_size;
	dma_addr_t list_dma;
	व्योम *list_mem;
	u32 config[5];

	range->flags |= RANGE_HAS_ACCUMULATOR;
	info = &range->acc_info;

	ret = of_property_पढ़ो_u32_array(node, "accumulator", config, 5);
	अगर (ret)
		वापस ret;

	info->pdsp_id		= config[0];
	info->start_channel	= config[1];
	info->list_entries	= config[2];
	info->pacing_mode	= config[3];
	info->समयr_count	= config[4] / ACC_DEFAULT_PERIOD;

	अगर (info->start_channel > ACC_MAX_CHANNEL) अणु
		dev_err(kdev->dev, "channel %d invalid for range %s\n",
			info->start_channel, range->name);
		वापस -EINVAL;
	पूर्ण

	अगर (info->pacing_mode > 3) अणु
		dev_err(kdev->dev, "pacing mode %d invalid for range %s\n",
			info->pacing_mode, range->name);
		वापस -EINVAL;
	पूर्ण

	pdsp = knav_find_pdsp(kdev, info->pdsp_id);
	अगर (!pdsp) अणु
		dev_err(kdev->dev, "pdsp id %d not found for range %s\n",
			info->pdsp_id, range->name);
		वापस -EINVAL;
	पूर्ण

	अगर (!pdsp->started) अणु
		dev_err(kdev->dev, "pdsp id %d not started for range %s\n",
			info->pdsp_id, range->name);
		वापस -ENODEV;
	पूर्ण

	info->pdsp = pdsp;
	channels = range->num_queues;
	अगर (of_get_property(node, "multi-queue", शून्य)) अणु
		range->flags |= RANGE_MULTI_QUEUE;
		channels = 1;
		अगर (range->queue_base & (32 - 1)) अणु
			dev_err(kdev->dev,
				"misaligned multi-queue accumulator range %s\n",
				range->name);
			वापस -EINVAL;
		पूर्ण
		अगर (range->num_queues > 32) अणु
			dev_err(kdev->dev,
				"too many queues in accumulator range %s\n",
				range->name);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* figure out list size */
	list_size  = info->list_entries;
	list_size *= ACC_LIST_ENTRY_WORDS * माप(u32);
	info->list_size = list_size;
	mem_size   = PAGE_ALIGN(list_size * 2);
	info->mem_size  = mem_size;
	range->acc = devm_kसुस्मृति(kdev->dev, channels, माप(*range->acc),
				  GFP_KERNEL);
	अगर (!range->acc)
		वापस -ENOMEM;

	क्रम (channel = 0; channel < channels; channel++) अणु
		acc = range->acc + channel;
		acc->channel = info->start_channel + channel;

		/* allocate memory क्रम the two lists */
		list_mem = alloc_pages_exact(mem_size, GFP_KERNEL | GFP_DMA);
		अगर (!list_mem)
			वापस -ENOMEM;

		list_dma = dma_map_single(kdev->dev, list_mem, mem_size,
					  DMA_BIसूचीECTIONAL);
		अगर (dma_mapping_error(kdev->dev, list_dma)) अणु
			मुक्त_pages_exact(list_mem, mem_size);
			वापस -ENOMEM;
		पूर्ण

		स_रखो(list_mem, 0, mem_size);
		dma_sync_single_क्रम_device(kdev->dev, list_dma, mem_size,
					   DMA_TO_DEVICE);
		scnम_लिखो(acc->name, माप(acc->name), "hwqueue-acc-%d",
			  acc->channel);
		acc->list_cpu[0] = list_mem;
		acc->list_cpu[1] = list_mem + list_size;
		acc->list_dma[0] = list_dma;
		acc->list_dma[1] = list_dma + list_size;
		dev_dbg(kdev->dev, "%s: channel %d, dma %pad, virt %8p\n",
			acc->name, acc->channel, &list_dma, list_mem);
	पूर्ण

	range->ops = &knav_acc_range_ops;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(knav_init_acc_range);
