<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (c) 2018 MediaTek Inc.

#समावेश <linux/bitops.h>
#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mailbox_controller.h>
#समावेश <linux/mailbox/mtk-cmdq-mailbox.h>
#समावेश <linux/of_device.h>

#घोषणा CMDQ_OP_CODE_MASK		(0xff << CMDQ_OP_CODE_SHIFT)
#घोषणा CMDQ_NUM_CMD(t)			(t->cmd_buf_size / CMDQ_INST_SIZE)

#घोषणा CMDQ_CURR_IRQ_STATUS		0x10
#घोषणा CMDQ_SYNC_TOKEN_UPDATE		0x68
#घोषणा CMDQ_THR_SLOT_CYCLES		0x30
#घोषणा CMDQ_THR_BASE			0x100
#घोषणा CMDQ_THR_SIZE			0x80
#घोषणा CMDQ_THR_WARM_RESET		0x00
#घोषणा CMDQ_THR_ENABLE_TASK		0x04
#घोषणा CMDQ_THR_SUSPEND_TASK		0x08
#घोषणा CMDQ_THR_CURR_STATUS		0x0c
#घोषणा CMDQ_THR_IRQ_STATUS		0x10
#घोषणा CMDQ_THR_IRQ_ENABLE		0x14
#घोषणा CMDQ_THR_CURR_ADDR		0x20
#घोषणा CMDQ_THR_END_ADDR		0x24
#घोषणा CMDQ_THR_WAIT_TOKEN		0x30
#घोषणा CMDQ_THR_PRIORITY		0x40

#घोषणा CMDQ_THR_ACTIVE_SLOT_CYCLES	0x3200
#घोषणा CMDQ_THR_ENABLED		0x1
#घोषणा CMDQ_THR_DISABLED		0x0
#घोषणा CMDQ_THR_SUSPEND		0x1
#घोषणा CMDQ_THR_RESUME			0x0
#घोषणा CMDQ_THR_STATUS_SUSPENDED	BIT(1)
#घोषणा CMDQ_THR_DO_WARM_RESET		BIT(0)
#घोषणा CMDQ_THR_IRQ_DONE		0x1
#घोषणा CMDQ_THR_IRQ_ERROR		0x12
#घोषणा CMDQ_THR_IRQ_EN			(CMDQ_THR_IRQ_ERROR | CMDQ_THR_IRQ_DONE)
#घोषणा CMDQ_THR_IS_WAITING		BIT(31)

#घोषणा CMDQ_JUMP_BY_OFFSET		0x10000000
#घोषणा CMDQ_JUMP_BY_PA			0x10000001

काष्ठा cmdq_thपढ़ो अणु
	काष्ठा mbox_chan	*chan;
	व्योम __iomem		*base;
	काष्ठा list_head	task_busy_list;
	u32			priority;
पूर्ण;

काष्ठा cmdq_task अणु
	काष्ठा cmdq		*cmdq;
	काष्ठा list_head	list_entry;
	dma_addr_t		pa_base;
	काष्ठा cmdq_thपढ़ो	*thपढ़ो;
	काष्ठा cmdq_pkt		*pkt; /* the packet sent from mailbox client */
पूर्ण;

काष्ठा cmdq अणु
	काष्ठा mbox_controller	mbox;
	व्योम __iomem		*base;
	पूर्णांक			irq;
	u32			thपढ़ो_nr;
	u32			irq_mask;
	काष्ठा cmdq_thपढ़ो	*thपढ़ो;
	काष्ठा clk		*घड़ी;
	bool			suspended;
	u8			shअगरt_pa;
पूर्ण;

काष्ठा gce_plat अणु
	u32 thपढ़ो_nr;
	u8 shअगरt;
पूर्ण;

u8 cmdq_get_shअगरt_pa(काष्ठा mbox_chan *chan)
अणु
	काष्ठा cmdq *cmdq = container_of(chan->mbox, काष्ठा cmdq, mbox);

	वापस cmdq->shअगरt_pa;
पूर्ण
EXPORT_SYMBOL(cmdq_get_shअगरt_pa);

अटल पूर्णांक cmdq_thपढ़ो_suspend(काष्ठा cmdq *cmdq, काष्ठा cmdq_thपढ़ो *thपढ़ो)
अणु
	u32 status;

	ग_लिखोl(CMDQ_THR_SUSPEND, thपढ़ो->base + CMDQ_THR_SUSPEND_TASK);

	/* If alपढ़ोy disabled, treat as suspended successful. */
	अगर (!(पढ़ोl(thपढ़ो->base + CMDQ_THR_ENABLE_TASK) & CMDQ_THR_ENABLED))
		वापस 0;

	अगर (पढ़ोl_poll_समयout_atomic(thपढ़ो->base + CMDQ_THR_CURR_STATUS,
			status, status & CMDQ_THR_STATUS_SUSPENDED, 0, 10)) अणु
		dev_err(cmdq->mbox.dev, "suspend GCE thread 0x%x failed\n",
			(u32)(thपढ़ो->base - cmdq->base));
		वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम cmdq_thपढ़ो_resume(काष्ठा cmdq_thपढ़ो *thपढ़ो)
अणु
	ग_लिखोl(CMDQ_THR_RESUME, thपढ़ो->base + CMDQ_THR_SUSPEND_TASK);
पूर्ण

अटल व्योम cmdq_init(काष्ठा cmdq *cmdq)
अणु
	पूर्णांक i;

	WARN_ON(clk_enable(cmdq->घड़ी) < 0);
	ग_लिखोl(CMDQ_THR_ACTIVE_SLOT_CYCLES, cmdq->base + CMDQ_THR_SLOT_CYCLES);
	क्रम (i = 0; i <= CMDQ_MAX_EVENT; i++)
		ग_लिखोl(i, cmdq->base + CMDQ_SYNC_TOKEN_UPDATE);
	clk_disable(cmdq->घड़ी);
पूर्ण

अटल पूर्णांक cmdq_thपढ़ो_reset(काष्ठा cmdq *cmdq, काष्ठा cmdq_thपढ़ो *thपढ़ो)
अणु
	u32 warm_reset;

	ग_लिखोl(CMDQ_THR_DO_WARM_RESET, thपढ़ो->base + CMDQ_THR_WARM_RESET);
	अगर (पढ़ोl_poll_समयout_atomic(thपढ़ो->base + CMDQ_THR_WARM_RESET,
			warm_reset, !(warm_reset & CMDQ_THR_DO_WARM_RESET),
			0, 10)) अणु
		dev_err(cmdq->mbox.dev, "reset GCE thread 0x%x failed\n",
			(u32)(thपढ़ो->base - cmdq->base));
		वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम cmdq_thपढ़ो_disable(काष्ठा cmdq *cmdq, काष्ठा cmdq_thपढ़ो *thपढ़ो)
अणु
	cmdq_thपढ़ो_reset(cmdq, thपढ़ो);
	ग_लिखोl(CMDQ_THR_DISABLED, thपढ़ो->base + CMDQ_THR_ENABLE_TASK);
पूर्ण

/* notअगरy GCE to re-fetch commands by setting GCE thपढ़ो PC */
अटल व्योम cmdq_thपढ़ो_invalidate_fetched_data(काष्ठा cmdq_thपढ़ो *thपढ़ो)
अणु
	ग_लिखोl(पढ़ोl(thपढ़ो->base + CMDQ_THR_CURR_ADDR),
	       thपढ़ो->base + CMDQ_THR_CURR_ADDR);
पूर्ण

अटल व्योम cmdq_task_insert_पूर्णांकo_thपढ़ो(काष्ठा cmdq_task *task)
अणु
	काष्ठा device *dev = task->cmdq->mbox.dev;
	काष्ठा cmdq_thपढ़ो *thपढ़ो = task->thपढ़ो;
	काष्ठा cmdq_task *prev_task = list_last_entry(
			&thपढ़ो->task_busy_list, typeof(*task), list_entry);
	u64 *prev_task_base = prev_task->pkt->va_base;

	/* let previous task jump to this task */
	dma_sync_single_क्रम_cpu(dev, prev_task->pa_base,
				prev_task->pkt->cmd_buf_size, DMA_TO_DEVICE);
	prev_task_base[CMDQ_NUM_CMD(prev_task->pkt) - 1] =
		(u64)CMDQ_JUMP_BY_PA << 32 | task->pa_base;
	dma_sync_single_क्रम_device(dev, prev_task->pa_base,
				   prev_task->pkt->cmd_buf_size, DMA_TO_DEVICE);

	cmdq_thपढ़ो_invalidate_fetched_data(thपढ़ो);
पूर्ण

अटल bool cmdq_thपढ़ो_is_in_wfe(काष्ठा cmdq_thपढ़ो *thपढ़ो)
अणु
	वापस पढ़ोl(thपढ़ो->base + CMDQ_THR_WAIT_TOKEN) & CMDQ_THR_IS_WAITING;
पूर्ण

अटल व्योम cmdq_task_exec_करोne(काष्ठा cmdq_task *task, क्रमागत cmdq_cb_status sta)
अणु
	काष्ठा cmdq_task_cb *cb = &task->pkt->async_cb;
	काष्ठा cmdq_cb_data data;

	WARN_ON(cb->cb == (cmdq_async_flush_cb)शून्य);
	data.sta = sta;
	data.data = cb->data;
	cb->cb(data);

	list_del(&task->list_entry);
पूर्ण

अटल व्योम cmdq_task_handle_error(काष्ठा cmdq_task *task)
अणु
	काष्ठा cmdq_thपढ़ो *thपढ़ो = task->thपढ़ो;
	काष्ठा cmdq_task *next_task;
	काष्ठा cmdq *cmdq = task->cmdq;

	dev_err(cmdq->mbox.dev, "task 0x%p error\n", task);
	WARN_ON(cmdq_thपढ़ो_suspend(cmdq, thपढ़ो) < 0);
	next_task = list_first_entry_or_null(&thपढ़ो->task_busy_list,
			काष्ठा cmdq_task, list_entry);
	अगर (next_task)
		ग_लिखोl(next_task->pa_base >> cmdq->shअगरt_pa,
		       thपढ़ो->base + CMDQ_THR_CURR_ADDR);
	cmdq_thपढ़ो_resume(thपढ़ो);
पूर्ण

अटल व्योम cmdq_thपढ़ो_irq_handler(काष्ठा cmdq *cmdq,
				    काष्ठा cmdq_thपढ़ो *thपढ़ो)
अणु
	काष्ठा cmdq_task *task, *पंचांगp, *curr_task = शून्य;
	u32 curr_pa, irq_flag, task_end_pa;
	bool err;

	irq_flag = पढ़ोl(thपढ़ो->base + CMDQ_THR_IRQ_STATUS);
	ग_लिखोl(~irq_flag, thपढ़ो->base + CMDQ_THR_IRQ_STATUS);

	/*
	 * When ISR call this function, another CPU core could run
	 * "release task" right beक्रमe we acquire the spin lock, and thus
	 * reset / disable this GCE thपढ़ो, so we need to check the enable
	 * bit of this GCE thपढ़ो.
	 */
	अगर (!(पढ़ोl(thपढ़ो->base + CMDQ_THR_ENABLE_TASK) & CMDQ_THR_ENABLED))
		वापस;

	अगर (irq_flag & CMDQ_THR_IRQ_ERROR)
		err = true;
	अन्यथा अगर (irq_flag & CMDQ_THR_IRQ_DONE)
		err = false;
	अन्यथा
		वापस;

	curr_pa = पढ़ोl(thपढ़ो->base + CMDQ_THR_CURR_ADDR) << cmdq->shअगरt_pa;

	list_क्रम_each_entry_safe(task, पंचांगp, &thपढ़ो->task_busy_list,
				 list_entry) अणु
		task_end_pa = task->pa_base + task->pkt->cmd_buf_size;
		अगर (curr_pa >= task->pa_base && curr_pa < task_end_pa)
			curr_task = task;

		अगर (!curr_task || curr_pa == task_end_pa - CMDQ_INST_SIZE) अणु
			cmdq_task_exec_करोne(task, CMDQ_CB_NORMAL);
			kमुक्त(task);
		पूर्ण अन्यथा अगर (err) अणु
			cmdq_task_exec_करोne(task, CMDQ_CB_ERROR);
			cmdq_task_handle_error(curr_task);
			kमुक्त(task);
		पूर्ण

		अगर (curr_task)
			अवरोध;
	पूर्ण

	अगर (list_empty(&thपढ़ो->task_busy_list)) अणु
		cmdq_thपढ़ो_disable(cmdq, thपढ़ो);
		clk_disable(cmdq->घड़ी);
	पूर्ण
पूर्ण

अटल irqवापस_t cmdq_irq_handler(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा cmdq *cmdq = dev;
	अचिन्हित दीर्घ irq_status, flags = 0L;
	पूर्णांक bit;

	irq_status = पढ़ोl(cmdq->base + CMDQ_CURR_IRQ_STATUS) & cmdq->irq_mask;
	अगर (!(irq_status ^ cmdq->irq_mask))
		वापस IRQ_NONE;

	क्रम_each_clear_bit(bit, &irq_status, cmdq->thपढ़ो_nr) अणु
		काष्ठा cmdq_thपढ़ो *thपढ़ो = &cmdq->thपढ़ो[bit];

		spin_lock_irqsave(&thपढ़ो->chan->lock, flags);
		cmdq_thपढ़ो_irq_handler(cmdq, thपढ़ो);
		spin_unlock_irqrestore(&thपढ़ो->chan->lock, flags);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक cmdq_suspend(काष्ठा device *dev)
अणु
	काष्ठा cmdq *cmdq = dev_get_drvdata(dev);
	काष्ठा cmdq_thपढ़ो *thपढ़ो;
	पूर्णांक i;
	bool task_running = false;

	cmdq->suspended = true;

	क्रम (i = 0; i < cmdq->thपढ़ो_nr; i++) अणु
		thपढ़ो = &cmdq->thपढ़ो[i];
		अगर (!list_empty(&thपढ़ो->task_busy_list)) अणु
			task_running = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (task_running)
		dev_warn(dev, "exist running task(s) in suspend\n");

	clk_unprepare(cmdq->घड़ी);

	वापस 0;
पूर्ण

अटल पूर्णांक cmdq_resume(काष्ठा device *dev)
अणु
	काष्ठा cmdq *cmdq = dev_get_drvdata(dev);

	WARN_ON(clk_prepare(cmdq->घड़ी) < 0);
	cmdq->suspended = false;
	वापस 0;
पूर्ण

अटल पूर्णांक cmdq_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cmdq *cmdq = platक्रमm_get_drvdata(pdev);

	clk_unprepare(cmdq->घड़ी);

	वापस 0;
पूर्ण

अटल पूर्णांक cmdq_mbox_send_data(काष्ठा mbox_chan *chan, व्योम *data)
अणु
	काष्ठा cmdq_pkt *pkt = (काष्ठा cmdq_pkt *)data;
	काष्ठा cmdq_thपढ़ो *thपढ़ो = (काष्ठा cmdq_thपढ़ो *)chan->con_priv;
	काष्ठा cmdq *cmdq = dev_get_drvdata(chan->mbox->dev);
	काष्ठा cmdq_task *task;
	अचिन्हित दीर्घ curr_pa, end_pa;

	/* Client should not flush new tasks अगर suspended. */
	WARN_ON(cmdq->suspended);

	task = kzalloc(माप(*task), GFP_ATOMIC);
	अगर (!task)
		वापस -ENOMEM;

	task->cmdq = cmdq;
	INIT_LIST_HEAD(&task->list_entry);
	task->pa_base = pkt->pa_base;
	task->thपढ़ो = thपढ़ो;
	task->pkt = pkt;

	अगर (list_empty(&thपढ़ो->task_busy_list)) अणु
		WARN_ON(clk_enable(cmdq->घड़ी) < 0);
		/*
		 * The thपढ़ो reset will clear thपढ़ो related रेजिस्टर to 0,
		 * including pc, end, priority, irq, suspend and enable. Thus
		 * set CMDQ_THR_ENABLED to CMDQ_THR_ENABLE_TASK will enable
		 * thपढ़ो and make it running.
		 */
		WARN_ON(cmdq_thपढ़ो_reset(cmdq, thपढ़ो) < 0);

		ग_लिखोl(task->pa_base >> cmdq->shअगरt_pa,
		       thपढ़ो->base + CMDQ_THR_CURR_ADDR);
		ग_लिखोl((task->pa_base + pkt->cmd_buf_size) >> cmdq->shअगरt_pa,
		       thपढ़ो->base + CMDQ_THR_END_ADDR);

		ग_लिखोl(thपढ़ो->priority, thपढ़ो->base + CMDQ_THR_PRIORITY);
		ग_लिखोl(CMDQ_THR_IRQ_EN, thपढ़ो->base + CMDQ_THR_IRQ_ENABLE);
		ग_लिखोl(CMDQ_THR_ENABLED, thपढ़ो->base + CMDQ_THR_ENABLE_TASK);
	पूर्ण अन्यथा अणु
		WARN_ON(cmdq_thपढ़ो_suspend(cmdq, thपढ़ो) < 0);
		curr_pa = पढ़ोl(thपढ़ो->base + CMDQ_THR_CURR_ADDR) <<
			cmdq->shअगरt_pa;
		end_pa = पढ़ोl(thपढ़ो->base + CMDQ_THR_END_ADDR) <<
			cmdq->shअगरt_pa;
		/* check boundary */
		अगर (curr_pa == end_pa - CMDQ_INST_SIZE ||
		    curr_pa == end_pa) अणु
			/* set to this task directly */
			ग_लिखोl(task->pa_base >> cmdq->shअगरt_pa,
			       thपढ़ो->base + CMDQ_THR_CURR_ADDR);
		पूर्ण अन्यथा अणु
			cmdq_task_insert_पूर्णांकo_thपढ़ो(task);
			smp_mb(); /* modअगरy jump beक्रमe enable thपढ़ो */
		पूर्ण
		ग_लिखोl((task->pa_base + pkt->cmd_buf_size) >> cmdq->shअगरt_pa,
		       thपढ़ो->base + CMDQ_THR_END_ADDR);
		cmdq_thपढ़ो_resume(thपढ़ो);
	पूर्ण
	list_move_tail(&task->list_entry, &thपढ़ो->task_busy_list);

	वापस 0;
पूर्ण

अटल पूर्णांक cmdq_mbox_startup(काष्ठा mbox_chan *chan)
अणु
	वापस 0;
पूर्ण

अटल व्योम cmdq_mbox_shutकरोwn(काष्ठा mbox_chan *chan)
अणु
	काष्ठा cmdq_thपढ़ो *thपढ़ो = (काष्ठा cmdq_thपढ़ो *)chan->con_priv;
	काष्ठा cmdq *cmdq = dev_get_drvdata(chan->mbox->dev);
	काष्ठा cmdq_task *task, *पंचांगp;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&thपढ़ो->chan->lock, flags);
	अगर (list_empty(&thपढ़ो->task_busy_list))
		जाओ करोne;

	WARN_ON(cmdq_thपढ़ो_suspend(cmdq, thपढ़ो) < 0);

	/* make sure executed tasks have success callback */
	cmdq_thपढ़ो_irq_handler(cmdq, thपढ़ो);
	अगर (list_empty(&thपढ़ो->task_busy_list))
		जाओ करोne;

	list_क्रम_each_entry_safe(task, पंचांगp, &thपढ़ो->task_busy_list,
				 list_entry) अणु
		cmdq_task_exec_करोne(task, CMDQ_CB_ERROR);
		kमुक्त(task);
	पूर्ण

	cmdq_thपढ़ो_disable(cmdq, thपढ़ो);
	clk_disable(cmdq->घड़ी);
करोne:
	/*
	 * The thपढ़ो->task_busy_list empty means thपढ़ो alपढ़ोy disable. The
	 * cmdq_mbox_send_data() always reset thपढ़ो which clear disable and
	 * suspend statue when first pkt send to channel, so there is no need
	 * to करो any operation here, only unlock and leave.
	 */
	spin_unlock_irqrestore(&thपढ़ो->chan->lock, flags);
पूर्ण

अटल पूर्णांक cmdq_mbox_flush(काष्ठा mbox_chan *chan, अचिन्हित दीर्घ समयout)
अणु
	काष्ठा cmdq_thपढ़ो *thपढ़ो = (काष्ठा cmdq_thपढ़ो *)chan->con_priv;
	काष्ठा cmdq_task_cb *cb;
	काष्ठा cmdq_cb_data data;
	काष्ठा cmdq *cmdq = dev_get_drvdata(chan->mbox->dev);
	काष्ठा cmdq_task *task, *पंचांगp;
	अचिन्हित दीर्घ flags;
	u32 enable;

	spin_lock_irqsave(&thपढ़ो->chan->lock, flags);
	अगर (list_empty(&thपढ़ो->task_busy_list))
		जाओ out;

	WARN_ON(cmdq_thपढ़ो_suspend(cmdq, thपढ़ो) < 0);
	अगर (!cmdq_thपढ़ो_is_in_wfe(thपढ़ो))
		जाओ रुको;

	list_क्रम_each_entry_safe(task, पंचांगp, &thपढ़ो->task_busy_list,
				 list_entry) अणु
		cb = &task->pkt->async_cb;
		अगर (cb->cb) अणु
			data.sta = CMDQ_CB_ERROR;
			data.data = cb->data;
			cb->cb(data);
		पूर्ण
		list_del(&task->list_entry);
		kमुक्त(task);
	पूर्ण

	cmdq_thपढ़ो_resume(thपढ़ो);
	cmdq_thपढ़ो_disable(cmdq, thपढ़ो);
	clk_disable(cmdq->घड़ी);

out:
	spin_unlock_irqrestore(&thपढ़ो->chan->lock, flags);
	वापस 0;

रुको:
	cmdq_thपढ़ो_resume(thपढ़ो);
	spin_unlock_irqrestore(&thपढ़ो->chan->lock, flags);
	अगर (पढ़ोl_poll_समयout_atomic(thपढ़ो->base + CMDQ_THR_ENABLE_TASK,
				      enable, enable == 0, 1, समयout)) अणु
		dev_err(cmdq->mbox.dev, "Fail to wait GCE thread 0x%x done\n",
			(u32)(thपढ़ो->base - cmdq->base));

		वापस -EFAULT;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mbox_chan_ops cmdq_mbox_chan_ops = अणु
	.send_data = cmdq_mbox_send_data,
	.startup = cmdq_mbox_startup,
	.shutकरोwn = cmdq_mbox_shutकरोwn,
	.flush = cmdq_mbox_flush,
पूर्ण;

अटल काष्ठा mbox_chan *cmdq_xlate(काष्ठा mbox_controller *mbox,
		स्थिर काष्ठा of_phandle_args *sp)
अणु
	पूर्णांक ind = sp->args[0];
	काष्ठा cmdq_thपढ़ो *thपढ़ो;

	अगर (ind >= mbox->num_chans)
		वापस ERR_PTR(-EINVAL);

	thपढ़ो = (काष्ठा cmdq_thपढ़ो *)mbox->chans[ind].con_priv;
	thपढ़ो->priority = sp->args[1];
	thपढ़ो->chan = &mbox->chans[ind];

	वापस &mbox->chans[ind];
पूर्ण

अटल पूर्णांक cmdq_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource *res;
	काष्ठा cmdq *cmdq;
	पूर्णांक err, i;
	काष्ठा gce_plat *plat_data;

	cmdq = devm_kzalloc(dev, माप(*cmdq), GFP_KERNEL);
	अगर (!cmdq)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	cmdq->base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(cmdq->base)) अणु
		dev_err(dev, "failed to ioremap gce\n");
		वापस PTR_ERR(cmdq->base);
	पूर्ण

	cmdq->irq = platक्रमm_get_irq(pdev, 0);
	अगर (cmdq->irq < 0)
		वापस cmdq->irq;

	plat_data = (काष्ठा gce_plat *)of_device_get_match_data(dev);
	अगर (!plat_data) अणु
		dev_err(dev, "failed to get match data\n");
		वापस -EINVAL;
	पूर्ण

	cmdq->thपढ़ो_nr = plat_data->thपढ़ो_nr;
	cmdq->shअगरt_pa = plat_data->shअगरt;
	cmdq->irq_mask = GENMASK(cmdq->thपढ़ो_nr - 1, 0);
	err = devm_request_irq(dev, cmdq->irq, cmdq_irq_handler, IRQF_SHARED,
			       "mtk_cmdq", cmdq);
	अगर (err < 0) अणु
		dev_err(dev, "failed to register ISR (%d)\n", err);
		वापस err;
	पूर्ण

	dev_dbg(dev, "cmdq device: addr:0x%p, va:0x%p, irq:%d\n",
		dev, cmdq->base, cmdq->irq);

	cmdq->घड़ी = devm_clk_get(dev, "gce");
	अगर (IS_ERR(cmdq->घड़ी)) अणु
		dev_err(dev, "failed to get gce clk\n");
		वापस PTR_ERR(cmdq->घड़ी);
	पूर्ण

	cmdq->mbox.dev = dev;
	cmdq->mbox.chans = devm_kसुस्मृति(dev, cmdq->thपढ़ो_nr,
					माप(*cmdq->mbox.chans), GFP_KERNEL);
	अगर (!cmdq->mbox.chans)
		वापस -ENOMEM;

	cmdq->mbox.num_chans = cmdq->thपढ़ो_nr;
	cmdq->mbox.ops = &cmdq_mbox_chan_ops;
	cmdq->mbox.of_xlate = cmdq_xlate;

	/* make use of TXDONE_BY_ACK */
	cmdq->mbox.txकरोne_irq = false;
	cmdq->mbox.txकरोne_poll = false;

	cmdq->thपढ़ो = devm_kसुस्मृति(dev, cmdq->thपढ़ो_nr,
					माप(*cmdq->thपढ़ो), GFP_KERNEL);
	अगर (!cmdq->thपढ़ो)
		वापस -ENOMEM;

	क्रम (i = 0; i < cmdq->thपढ़ो_nr; i++) अणु
		cmdq->thपढ़ो[i].base = cmdq->base + CMDQ_THR_BASE +
				CMDQ_THR_SIZE * i;
		INIT_LIST_HEAD(&cmdq->thपढ़ो[i].task_busy_list);
		cmdq->mbox.chans[i].con_priv = (व्योम *)&cmdq->thपढ़ो[i];
	पूर्ण

	err = devm_mbox_controller_रेजिस्टर(dev, &cmdq->mbox);
	अगर (err < 0) अणु
		dev_err(dev, "failed to register mailbox: %d\n", err);
		वापस err;
	पूर्ण

	platक्रमm_set_drvdata(pdev, cmdq);
	WARN_ON(clk_prepare(cmdq->घड़ी) < 0);

	cmdq_init(cmdq);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops cmdq_pm_ops = अणु
	.suspend = cmdq_suspend,
	.resume = cmdq_resume,
पूर्ण;

अटल स्थिर काष्ठा gce_plat gce_plat_v2 = अणु.thपढ़ो_nr = 16पूर्ण;
अटल स्थिर काष्ठा gce_plat gce_plat_v3 = अणु.thपढ़ो_nr = 24पूर्ण;
अटल स्थिर काष्ठा gce_plat gce_plat_v4 = अणु.thपढ़ो_nr = 24, .shअगरt = 3पूर्ण;

अटल स्थिर काष्ठा of_device_id cmdq_of_ids[] = अणु
	अणु.compatible = "mediatek,mt8173-gce", .data = (व्योम *)&gce_plat_v2पूर्ण,
	अणु.compatible = "mediatek,mt8183-gce", .data = (व्योम *)&gce_plat_v3पूर्ण,
	अणु.compatible = "mediatek,mt6779-gce", .data = (व्योम *)&gce_plat_v4पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver cmdq_drv = अणु
	.probe = cmdq_probe,
	.हटाओ = cmdq_हटाओ,
	.driver = अणु
		.name = "mtk_cmdq",
		.pm = &cmdq_pm_ops,
		.of_match_table = cmdq_of_ids,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init cmdq_drv_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&cmdq_drv);
पूर्ण

अटल व्योम __निकास cmdq_drv_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&cmdq_drv);
पूर्ण

subsys_initcall(cmdq_drv_init);
module_निकास(cmdq_drv_निकास);

MODULE_LICENSE("GPL v2");
