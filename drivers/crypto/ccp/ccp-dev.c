<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AMD Cryptographic Coprocessor (CCP) driver
 *
 * Copyright (C) 2013,2019 Advanced Micro Devices, Inc.
 *
 * Author: Tom Lendacky <thomas.lendacky@amd.com>
 * Author: Gary R Hook <gary.hook@amd.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/sched.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/spinlock_types.h>
#समावेश <linux/types.h>
#समावेश <linux/mutex.h>
#समावेश <linux/delay.h>
#समावेश <linux/hw_अक्रमom.h>
#समावेश <linux/cpu.h>
#समावेश <linux/atomic.h>
#अगर_घोषित CONFIG_X86
#समावेश <यंत्र/cpu_device_id.h>
#पूर्ण_अगर
#समावेश <linux/ccp.h>

#समावेश "ccp-dev.h"

#घोषणा MAX_CCPS 32

/* Limit CCP use to a specअगरed number of queues per device */
अटल अचिन्हित पूर्णांक nqueues = 0;
module_param(nqueues, uपूर्णांक, 0444);
MODULE_PARM_DESC(nqueues, "Number of queues per CCP (minimum 1; default: all available)");

/* Limit the maximum number of configured CCPs */
अटल atomic_t dev_count = ATOMIC_INIT(0);
अटल अचिन्हित पूर्णांक max_devs = MAX_CCPS;
module_param(max_devs, uपूर्णांक, 0444);
MODULE_PARM_DESC(max_devs, "Maximum number of CCPs to enable (default: all; 0 disables all CCPs)");

काष्ठा ccp_tasklet_data अणु
	काष्ठा completion completion;
	काष्ठा ccp_cmd *cmd;
पूर्ण;

/* Human-पढ़ोable error strings */
#घोषणा CCP_MAX_ERROR_CODE	64
अटल अक्षर *ccp_error_codes[] = अणु
	"",
	"ILLEGAL_ENGINE",
	"ILLEGAL_KEY_ID",
	"ILLEGAL_FUNCTION_TYPE",
	"ILLEGAL_FUNCTION_MODE",
	"ILLEGAL_FUNCTION_ENCRYPT",
	"ILLEGAL_FUNCTION_SIZE",
	"Zlib_MISSING_INIT_EOM",
	"ILLEGAL_FUNCTION_RSVD",
	"ILLEGAL_BUFFER_LENGTH",
	"VLSB_FAULT",
	"ILLEGAL_MEM_ADDR",
	"ILLEGAL_MEM_SEL",
	"ILLEGAL_CONTEXT_ID",
	"ILLEGAL_KEY_ADDR",
	"0xF Reserved",
	"Zlib_ILLEGAL_MULTI_QUEUE",
	"Zlib_ILLEGAL_JOBID_CHANGE",
	"CMD_TIMEOUT",
	"IDMA0_AXI_SLVERR",
	"IDMA0_AXI_DECERR",
	"0x15 Reserved",
	"IDMA1_AXI_SLAVE_FAULT",
	"IDMA1_AIXI_DECERR",
	"0x18 Reserved",
	"ZLIBVHB_AXI_SLVERR",
	"ZLIBVHB_AXI_DECERR",
	"0x1B Reserved",
	"ZLIB_UNEXPECTED_EOM",
	"ZLIB_EXTRA_DATA",
	"ZLIB_BTYPE",
	"ZLIB_UNDEFINED_SYMBOL",
	"ZLIB_UNDEFINED_DISTANCE_S",
	"ZLIB_CODE_LENGTH_SYMBOL",
	"ZLIB _VHB_ILLEGAL_FETCH",
	"ZLIB_UNCOMPRESSED_LEN",
	"ZLIB_LIMIT_REACHED",
	"ZLIB_CHECKSUM_MISMATCH0",
	"ODMA0_AXI_SLVERR",
	"ODMA0_AXI_DECERR",
	"0x28 Reserved",
	"ODMA1_AXI_SLVERR",
	"ODMA1_AXI_DECERR",
पूर्ण;

व्योम ccp_log_error(काष्ठा ccp_device *d, अचिन्हित पूर्णांक e)
अणु
	अगर (WARN_ON(e >= CCP_MAX_ERROR_CODE))
		वापस;

	अगर (e < ARRAY_SIZE(ccp_error_codes))
		dev_err(d->dev, "CCP error %d: %s\n", e, ccp_error_codes[e]);
	अन्यथा
		dev_err(d->dev, "CCP error %d: Unknown Error\n", e);
पूर्ण

/* List of CCPs, CCP count, पढ़ो-ग_लिखो access lock, and access functions
 *
 * Lock काष्ठाure: get ccp_unit_lock क्रम पढ़ोing whenever we need to
 * examine the CCP list. While holding it क्रम पढ़ोing we can acquire
 * the RR lock to update the round-robin next-CCP poपूर्णांकer. The unit lock
 * must be acquired beक्रमe the RR lock.
 *
 * If the unit-lock is acquired क्रम writing, we have total control over
 * the list, so there's no value in getting the RR lock.
 */
अटल DEFINE_RWLOCK(ccp_unit_lock);
अटल LIST_HEAD(ccp_units);

/* Round-robin counter */
अटल DEFINE_SPINLOCK(ccp_rr_lock);
अटल काष्ठा ccp_device *ccp_rr;

/**
 * ccp_add_device - add a CCP device to the list
 *
 * @ccp: ccp_device काष्ठा poपूर्णांकer
 *
 * Put this CCP on the unit list, which makes it available
 * क्रम use.
 *
 * Returns zero अगर a CCP device is present, -ENODEV otherwise.
 */
व्योम ccp_add_device(काष्ठा ccp_device *ccp)
अणु
	अचिन्हित दीर्घ flags;

	ग_लिखो_lock_irqsave(&ccp_unit_lock, flags);
	list_add_tail(&ccp->entry, &ccp_units);
	अगर (!ccp_rr)
		/* We alपढ़ोy have the list lock (we're first) so this
		 * poपूर्णांकer can't change on us. Set its initial value.
		 */
		ccp_rr = ccp;
	ग_लिखो_unlock_irqrestore(&ccp_unit_lock, flags);
पूर्ण

/**
 * ccp_del_device - हटाओ a CCP device from the list
 *
 * @ccp: ccp_device काष्ठा poपूर्णांकer
 *
 * Remove this unit from the list of devices. If the next device
 * up क्रम use is this one, adjust the poपूर्णांकer. If this is the last
 * device, शून्य the poपूर्णांकer.
 */
व्योम ccp_del_device(काष्ठा ccp_device *ccp)
अणु
	अचिन्हित दीर्घ flags;

	ग_लिखो_lock_irqsave(&ccp_unit_lock, flags);
	अगर (ccp_rr == ccp) अणु
		/* ccp_unit_lock is पढ़ो/ग_लिखो; any पढ़ो access
		 * will be suspended जबतक we make changes to the
		 * list and RR poपूर्णांकer.
		 */
		अगर (list_is_last(&ccp_rr->entry, &ccp_units))
			ccp_rr = list_first_entry(&ccp_units, काष्ठा ccp_device,
						  entry);
		अन्यथा
			ccp_rr = list_next_entry(ccp_rr, entry);
	पूर्ण
	list_del(&ccp->entry);
	अगर (list_empty(&ccp_units))
		ccp_rr = शून्य;
	ग_लिखो_unlock_irqrestore(&ccp_unit_lock, flags);
पूर्ण



पूर्णांक ccp_रेजिस्टर_rng(काष्ठा ccp_device *ccp)
अणु
	पूर्णांक ret = 0;

	dev_dbg(ccp->dev, "Registering RNG...\n");
	/* Register an RNG */
	ccp->hwrng.name = ccp->rngname;
	ccp->hwrng.पढ़ो = ccp_trng_पढ़ो;
	ret = hwrng_रेजिस्टर(&ccp->hwrng);
	अगर (ret)
		dev_err(ccp->dev, "error registering hwrng (%d)\n", ret);

	वापस ret;
पूर्ण

व्योम ccp_unरेजिस्टर_rng(काष्ठा ccp_device *ccp)
अणु
	अगर (ccp->hwrng.name)
		hwrng_unरेजिस्टर(&ccp->hwrng);
पूर्ण

अटल काष्ठा ccp_device *ccp_get_device(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा ccp_device *dp = शून्य;

	/* We round-robin through the unit list.
	 * The (ccp_rr) poपूर्णांकer refers to the next unit to use.
	 */
	पढ़ो_lock_irqsave(&ccp_unit_lock, flags);
	अगर (!list_empty(&ccp_units)) अणु
		spin_lock(&ccp_rr_lock);
		dp = ccp_rr;
		अगर (list_is_last(&ccp_rr->entry, &ccp_units))
			ccp_rr = list_first_entry(&ccp_units, काष्ठा ccp_device,
						  entry);
		अन्यथा
			ccp_rr = list_next_entry(ccp_rr, entry);
		spin_unlock(&ccp_rr_lock);
	पूर्ण
	पढ़ो_unlock_irqrestore(&ccp_unit_lock, flags);

	वापस dp;
पूर्ण

/**
 * ccp_present - check अगर a CCP device is present
 *
 * Returns zero अगर a CCP device is present, -ENODEV otherwise.
 */
पूर्णांक ccp_present(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	पढ़ो_lock_irqsave(&ccp_unit_lock, flags);
	ret = list_empty(&ccp_units);
	पढ़ो_unlock_irqrestore(&ccp_unit_lock, flags);

	वापस ret ? -ENODEV : 0;
पूर्ण
EXPORT_SYMBOL_GPL(ccp_present);

/**
 * ccp_version - get the version of the CCP device
 *
 * Returns the version from the first unit on the list;
 * otherwise a zero अगर no CCP device is present
 */
अचिन्हित पूर्णांक ccp_version(व्योम)
अणु
	काष्ठा ccp_device *dp;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	पढ़ो_lock_irqsave(&ccp_unit_lock, flags);
	अगर (!list_empty(&ccp_units)) अणु
		dp = list_first_entry(&ccp_units, काष्ठा ccp_device, entry);
		ret = dp->vdata->version;
	पूर्ण
	पढ़ो_unlock_irqrestore(&ccp_unit_lock, flags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(ccp_version);

/**
 * ccp_enqueue_cmd - queue an operation क्रम processing by the CCP
 *
 * @cmd: ccp_cmd काष्ठा to be processed
 *
 * Queue a cmd to be processed by the CCP. If queueing the cmd
 * would exceed the defined length of the cmd queue the cmd will
 * only be queued अगर the CCP_CMD_MAY_BACKLOG flag is set and will
 * result in a वापस code of -EBUSY.
 *
 * The callback routine specअगरied in the ccp_cmd काष्ठा will be
 * called to notअगरy the caller of completion (अगर the cmd was not
 * backlogged) or advancement out of the backlog. If the cmd has
 * advanced out of the backlog the "err" value of the callback
 * will be -EINPROGRESS. Any other "err" value during callback is
 * the result of the operation.
 *
 * The cmd has been successfully queued अगर:
 *   the वापस code is -EINPROGRESS or
 *   the वापस code is -EBUSY and CCP_CMD_MAY_BACKLOG flag is set
 */
पूर्णांक ccp_enqueue_cmd(काष्ठा ccp_cmd *cmd)
अणु
	काष्ठा ccp_device *ccp;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	/* Some commands might need to be sent to a specअगरic device */
	ccp = cmd->ccp ? cmd->ccp : ccp_get_device();

	अगर (!ccp)
		वापस -ENODEV;

	/* Caller must supply a callback routine */
	अगर (!cmd->callback)
		वापस -EINVAL;

	cmd->ccp = ccp;

	spin_lock_irqsave(&ccp->cmd_lock, flags);

	i = ccp->cmd_q_count;

	अगर (ccp->cmd_count >= MAX_CMD_QLEN) अणु
		अगर (cmd->flags & CCP_CMD_MAY_BACKLOG) अणु
			ret = -EBUSY;
			list_add_tail(&cmd->entry, &ccp->backlog);
		पूर्ण अन्यथा अणु
			ret = -ENOSPC;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = -EINPROGRESS;
		ccp->cmd_count++;
		list_add_tail(&cmd->entry, &ccp->cmd);

		/* Find an idle queue */
		अगर (!ccp->suspending) अणु
			क्रम (i = 0; i < ccp->cmd_q_count; i++) अणु
				अगर (ccp->cmd_q[i].active)
					जारी;

				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&ccp->cmd_lock, flags);

	/* If we found an idle queue, wake it up */
	अगर (i < ccp->cmd_q_count)
		wake_up_process(ccp->cmd_q[i].kthपढ़ो);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(ccp_enqueue_cmd);

अटल व्योम ccp_करो_cmd_backlog(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ccp_cmd *cmd = container_of(work, काष्ठा ccp_cmd, work);
	काष्ठा ccp_device *ccp = cmd->ccp;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक i;

	cmd->callback(cmd->data, -EINPROGRESS);

	spin_lock_irqsave(&ccp->cmd_lock, flags);

	ccp->cmd_count++;
	list_add_tail(&cmd->entry, &ccp->cmd);

	/* Find an idle queue */
	क्रम (i = 0; i < ccp->cmd_q_count; i++) अणु
		अगर (ccp->cmd_q[i].active)
			जारी;

		अवरोध;
	पूर्ण

	spin_unlock_irqrestore(&ccp->cmd_lock, flags);

	/* If we found an idle queue, wake it up */
	अगर (i < ccp->cmd_q_count)
		wake_up_process(ccp->cmd_q[i].kthपढ़ो);
पूर्ण

अटल काष्ठा ccp_cmd *ccp_dequeue_cmd(काष्ठा ccp_cmd_queue *cmd_q)
अणु
	काष्ठा ccp_device *ccp = cmd_q->ccp;
	काष्ठा ccp_cmd *cmd = शून्य;
	काष्ठा ccp_cmd *backlog = शून्य;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ccp->cmd_lock, flags);

	cmd_q->active = 0;

	अगर (ccp->suspending) अणु
		cmd_q->suspended = 1;

		spin_unlock_irqrestore(&ccp->cmd_lock, flags);
		wake_up_पूर्णांकerruptible(&ccp->suspend_queue);

		वापस शून्य;
	पूर्ण

	अगर (ccp->cmd_count) अणु
		cmd_q->active = 1;

		cmd = list_first_entry(&ccp->cmd, काष्ठा ccp_cmd, entry);
		list_del(&cmd->entry);

		ccp->cmd_count--;
	पूर्ण

	अगर (!list_empty(&ccp->backlog)) अणु
		backlog = list_first_entry(&ccp->backlog, काष्ठा ccp_cmd,
					   entry);
		list_del(&backlog->entry);
	पूर्ण

	spin_unlock_irqrestore(&ccp->cmd_lock, flags);

	अगर (backlog) अणु
		INIT_WORK(&backlog->work, ccp_करो_cmd_backlog);
		schedule_work(&backlog->work);
	पूर्ण

	वापस cmd;
पूर्ण

अटल व्योम ccp_करो_cmd_complete(अचिन्हित दीर्घ data)
अणु
	काष्ठा ccp_tasklet_data *tdata = (काष्ठा ccp_tasklet_data *)data;
	काष्ठा ccp_cmd *cmd = tdata->cmd;

	cmd->callback(cmd->data, cmd->ret);

	complete(&tdata->completion);
पूर्ण

/**
 * ccp_cmd_queue_thपढ़ो - create a kernel thपढ़ो to manage a CCP queue
 *
 * @data: thपढ़ो-specअगरic data
 */
पूर्णांक ccp_cmd_queue_thपढ़ो(व्योम *data)
अणु
	काष्ठा ccp_cmd_queue *cmd_q = (काष्ठा ccp_cmd_queue *)data;
	काष्ठा ccp_cmd *cmd;
	काष्ठा ccp_tasklet_data tdata;
	काष्ठा tasklet_काष्ठा tasklet;

	tasklet_init(&tasklet, ccp_करो_cmd_complete, (अचिन्हित दीर्घ)&tdata);

	set_current_state(TASK_INTERRUPTIBLE);
	जबतक (!kthपढ़ो_should_stop()) अणु
		schedule();

		set_current_state(TASK_INTERRUPTIBLE);

		cmd = ccp_dequeue_cmd(cmd_q);
		अगर (!cmd)
			जारी;

		__set_current_state(TASK_RUNNING);

		/* Execute the command */
		cmd->ret = ccp_run_cmd(cmd_q, cmd);

		/* Schedule the completion callback */
		tdata.cmd = cmd;
		init_completion(&tdata.completion);
		tasklet_schedule(&tasklet);
		रुको_क्रम_completion(&tdata.completion);
	पूर्ण

	__set_current_state(TASK_RUNNING);

	वापस 0;
पूर्ण

/**
 * ccp_alloc_काष्ठा - allocate and initialize the ccp_device काष्ठा
 *
 * @dev: device काष्ठा of the CCP
 */
काष्ठा ccp_device *ccp_alloc_काष्ठा(काष्ठा sp_device *sp)
अणु
	काष्ठा device *dev = sp->dev;
	काष्ठा ccp_device *ccp;

	ccp = devm_kzalloc(dev, माप(*ccp), GFP_KERNEL);
	अगर (!ccp)
		वापस शून्य;
	ccp->dev = dev;
	ccp->sp = sp;
	ccp->axcache = sp->axcache;

	INIT_LIST_HEAD(&ccp->cmd);
	INIT_LIST_HEAD(&ccp->backlog);

	spin_lock_init(&ccp->cmd_lock);
	mutex_init(&ccp->req_mutex);
	mutex_init(&ccp->sb_mutex);
	ccp->sb_count = KSB_COUNT;
	ccp->sb_start = 0;

	/* Initialize the रुको queues */
	init_रुकोqueue_head(&ccp->sb_queue);
	init_रुकोqueue_head(&ccp->suspend_queue);

	snम_लिखो(ccp->name, MAX_CCP_NAME_LEN, "ccp-%u", sp->ord);
	snम_लिखो(ccp->rngname, MAX_CCP_NAME_LEN, "ccp-%u-rng", sp->ord);

	वापस ccp;
पूर्ण

पूर्णांक ccp_trng_पढ़ो(काष्ठा hwrng *rng, व्योम *data, माप_प्रकार max, bool रुको)
अणु
	काष्ठा ccp_device *ccp = container_of(rng, काष्ठा ccp_device, hwrng);
	u32 trng_value;
	पूर्णांक len = min_t(पूर्णांक, माप(trng_value), max);

	/* Locking is provided by the caller so we can update device
	 * hwrng-related fields safely
	 */
	trng_value = ioपढ़ो32(ccp->io_regs + TRNG_OUT_REG);
	अगर (!trng_value) अणु
		/* Zero is वापसed अगर not data is available or अगर a
		 * bad-entropy error is present. Assume an error अगर
		 * we exceed TRNG_RETRIES पढ़ोs of zero.
		 */
		अगर (ccp->hwrng_retries++ > TRNG_RETRIES)
			वापस -EIO;

		वापस 0;
	पूर्ण

	/* Reset the counter and save the rng value */
	ccp->hwrng_retries = 0;
	स_नकल(data, &trng_value, len);

	वापस len;
पूर्ण

bool ccp_queues_suspended(काष्ठा ccp_device *ccp)
अणु
	अचिन्हित पूर्णांक suspended = 0;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक i;

	spin_lock_irqsave(&ccp->cmd_lock, flags);

	क्रम (i = 0; i < ccp->cmd_q_count; i++)
		अगर (ccp->cmd_q[i].suspended)
			suspended++;

	spin_unlock_irqrestore(&ccp->cmd_lock, flags);

	वापस ccp->cmd_q_count == suspended;
पूर्ण

व्योम ccp_dev_suspend(काष्ठा sp_device *sp)
अणु
	काष्ठा ccp_device *ccp = sp->ccp_data;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक i;

	/* If there's no device there's nothing to करो */
	अगर (!ccp)
		वापस;

	spin_lock_irqsave(&ccp->cmd_lock, flags);

	ccp->suspending = 1;

	/* Wake all the queue kthपढ़ोs to prepare क्रम suspend */
	क्रम (i = 0; i < ccp->cmd_q_count; i++)
		wake_up_process(ccp->cmd_q[i].kthपढ़ो);

	spin_unlock_irqrestore(&ccp->cmd_lock, flags);

	/* Wait क्रम all queue kthपढ़ोs to say they're करोne */
	जबतक (!ccp_queues_suspended(ccp))
		रुको_event_पूर्णांकerruptible(ccp->suspend_queue,
					 ccp_queues_suspended(ccp));
पूर्ण

व्योम ccp_dev_resume(काष्ठा sp_device *sp)
अणु
	काष्ठा ccp_device *ccp = sp->ccp_data;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक i;

	/* If there's no device there's nothing to करो */
	अगर (!ccp)
		वापस;

	spin_lock_irqsave(&ccp->cmd_lock, flags);

	ccp->suspending = 0;

	/* Wake up all the kthपढ़ोs */
	क्रम (i = 0; i < ccp->cmd_q_count; i++) अणु
		ccp->cmd_q[i].suspended = 0;
		wake_up_process(ccp->cmd_q[i].kthपढ़ो);
	पूर्ण

	spin_unlock_irqrestore(&ccp->cmd_lock, flags);
पूर्ण

पूर्णांक ccp_dev_init(काष्ठा sp_device *sp)
अणु
	काष्ठा device *dev = sp->dev;
	काष्ठा ccp_device *ccp;
	पूर्णांक ret;

	/*
	 * Check how many we have so far, and stop after reaching
	 * that number
	 */
	अगर (atomic_inc_वापस(&dev_count) > max_devs)
		वापस 0; /* करोn't fail the load */

	ret = -ENOMEM;
	ccp = ccp_alloc_काष्ठा(sp);
	अगर (!ccp)
		जाओ e_err;
	sp->ccp_data = ccp;

	अगर (!nqueues || (nqueues > MAX_HW_QUEUES))
		ccp->max_q_count = MAX_HW_QUEUES;
	अन्यथा
		ccp->max_q_count = nqueues;

	ccp->vdata = (काष्ठा ccp_vdata *)sp->dev_vdata->ccp_vdata;
	अगर (!ccp->vdata || !ccp->vdata->version) अणु
		ret = -ENODEV;
		dev_err(dev, "missing driver data\n");
		जाओ e_err;
	पूर्ण

	ccp->use_tasklet = sp->use_tasklet;

	ccp->io_regs = sp->io_map + ccp->vdata->offset;
	अगर (ccp->vdata->setup)
		ccp->vdata->setup(ccp);

	ret = ccp->vdata->perक्रमm->init(ccp);
	अगर (ret) अणु
		/* A positive number means that the device cannot be initialized,
		 * but no additional message is required.
		 */
		अगर (ret > 0)
			जाओ e_quiet;

		/* An unexpected problem occurred, and should be reported in the log */
		जाओ e_err;
	पूर्ण

	dev_notice(dev, "ccp enabled\n");

	वापस 0;

e_err:
	dev_notice(dev, "ccp initialization failed\n");

e_quiet:
	sp->ccp_data = शून्य;

	वापस ret;
पूर्ण

व्योम ccp_dev_destroy(काष्ठा sp_device *sp)
अणु
	काष्ठा ccp_device *ccp = sp->ccp_data;

	अगर (!ccp)
		वापस;

	ccp->vdata->perक्रमm->destroy(ccp);
पूर्ण
