<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * VMware Balloon driver.
 *
 * Copyright (C) 2000-2018, VMware, Inc. All Rights Reserved.
 *
 * This is VMware physical memory management driver क्रम Linux. The driver
 * acts like a "balloon" that can be inflated to reclaim physical pages by
 * reserving them in the guest and invalidating them in the monitor,
 * मुक्तing up the underlying machine pages so they can be allocated to
 * other guests.  The balloon can also be deflated to allow the guest to
 * use more physical memory. Higher level policies can control the sizes
 * of balloons in VMs in order to manage physical memory resources.
 */

//#घोषणा DEBUG
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/types.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/sched.h>
#समावेश <linux/module.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/mount.h>
#समावेश <linux/pseuकरो_fs.h>
#समावेश <linux/balloon_compaction.h>
#समावेश <linux/vmw_vmci_defs.h>
#समावेश <linux/vmw_vmci_api.h>
#समावेश <यंत्र/hypervisor.h>

MODULE_AUTHOR("VMware, Inc.");
MODULE_DESCRIPTION("VMware Memory Control (Balloon) Driver");
MODULE_ALIAS("dmi:*:svnVMware*:*");
MODULE_ALIAS("vmware_vmmemctl");
MODULE_LICENSE("GPL");

अटल bool __पढ़ो_mostly vmwballoon_shrinker_enable;
module_param(vmwballoon_shrinker_enable, bool, 0444);
MODULE_PARM_DESC(vmwballoon_shrinker_enable,
	"Enable non-cooperative out-of-memory protection. Disabled by default as it may degrade performance.");

/* Delay in seconds after shrink beक्रमe inflation. */
#घोषणा VMBALLOON_SHRINK_DELAY		(5)

/* Maximum number of refused pages we accumulate during inflation cycle */
#घोषणा VMW_BALLOON_MAX_REFUSED		16

/* Magic number क्रम the balloon mount-poपूर्णांक */
#घोषणा BALLOON_VMW_MAGIC		0x0ba11007

/*
 * Hypervisor communication port definitions.
 */
#घोषणा VMW_BALLOON_HV_PORT		0x5670
#घोषणा VMW_BALLOON_HV_MAGIC		0x456c6d6f
#घोषणा VMW_BALLOON_GUEST_ID		1	/* Linux */

क्रमागत vmwballoon_capabilities अणु
	/*
	 * Bit 0 is reserved and not associated to any capability.
	 */
	VMW_BALLOON_BASIC_CMDS			= (1 << 1),
	VMW_BALLOON_BATCHED_CMDS		= (1 << 2),
	VMW_BALLOON_BATCHED_2M_CMDS		= (1 << 3),
	VMW_BALLOON_SIGNALLED_WAKEUP_CMD	= (1 << 4),
	VMW_BALLOON_64_BIT_TARGET		= (1 << 5)
पूर्ण;

#घोषणा VMW_BALLOON_CAPABILITIES_COMMON	(VMW_BALLOON_BASIC_CMDS \
					| VMW_BALLOON_BATCHED_CMDS \
					| VMW_BALLOON_BATCHED_2M_CMDS \
					| VMW_BALLOON_SIGNALLED_WAKEUP_CMD)

#घोषणा VMW_BALLOON_2M_ORDER		(PMD_SHIFT - PAGE_SHIFT)

/*
 * 64-bit tarमाला_लो are only supported in 64-bit
 */
#अगर_घोषित CONFIG_64BIT
#घोषणा VMW_BALLOON_CAPABILITIES	(VMW_BALLOON_CAPABILITIES_COMMON \
					| VMW_BALLOON_64_BIT_TARGET)
#अन्यथा
#घोषणा VMW_BALLOON_CAPABILITIES	VMW_BALLOON_CAPABILITIES_COMMON
#पूर्ण_अगर

क्रमागत vmballoon_page_माप_प्रकारype अणु
	VMW_BALLOON_4K_PAGE,
	VMW_BALLOON_2M_PAGE,
	VMW_BALLOON_LAST_SIZE = VMW_BALLOON_2M_PAGE
पूर्ण;

#घोषणा VMW_BALLOON_NUM_PAGE_SIZES	(VMW_BALLOON_LAST_SIZE + 1)

अटल स्थिर अक्षर * स्थिर vmballoon_page_size_names[] = अणु
	[VMW_BALLOON_4K_PAGE]			= "4k",
	[VMW_BALLOON_2M_PAGE]			= "2M"
पूर्ण;

क्रमागत vmballoon_op अणु
	VMW_BALLOON_INFLATE,
	VMW_BALLOON_DEFLATE
पूर्ण;

क्रमागत vmballoon_op_stat_type अणु
	VMW_BALLOON_OP_STAT,
	VMW_BALLOON_OP_FAIL_STAT
पूर्ण;

#घोषणा VMW_BALLOON_OP_STAT_TYPES	(VMW_BALLOON_OP_FAIL_STAT + 1)

/**
 * क्रमागत vmballoon_cmd_type - backकरोor commands.
 *
 * Availability of the commands is as followed:
 *
 * %VMW_BALLOON_CMD_START, %VMW_BALLOON_CMD_GET_TARGET and
 * %VMW_BALLOON_CMD_GUEST_ID are always available.
 *
 * If the host reports %VMW_BALLOON_BASIC_CMDS are supported then
 * %VMW_BALLOON_CMD_LOCK and %VMW_BALLOON_CMD_UNLOCK commands are available.
 *
 * If the host reports %VMW_BALLOON_BATCHED_CMDS are supported then
 * %VMW_BALLOON_CMD_BATCHED_LOCK and VMW_BALLOON_CMD_BATCHED_UNLOCK commands
 * are available.
 *
 * If the host reports %VMW_BALLOON_BATCHED_2M_CMDS are supported then
 * %VMW_BALLOON_CMD_BATCHED_2M_LOCK and %VMW_BALLOON_CMD_BATCHED_2M_UNLOCK
 * are supported.
 *
 * If the host reports  VMW_BALLOON_SIGNALLED_WAKEUP_CMD is supported then
 * VMW_BALLOON_CMD_VMCI_DOORBELL_SET command is supported.
 *
 * @VMW_BALLOON_CMD_START: Communicating supported version with the hypervisor.
 * @VMW_BALLOON_CMD_GET_TARGET: Gets the balloon target size.
 * @VMW_BALLOON_CMD_LOCK: Inक्रमms the hypervisor about a ballooned page.
 * @VMW_BALLOON_CMD_UNLOCK: Inक्रमms the hypervisor about a page that is about
 *			    to be deflated from the balloon.
 * @VMW_BALLOON_CMD_GUEST_ID: Inक्रमms the hypervisor about the type of OS that
 *			      runs in the VM.
 * @VMW_BALLOON_CMD_BATCHED_LOCK: Inक्रमm the hypervisor about a batch of
 *				  ballooned pages (up to 512).
 * @VMW_BALLOON_CMD_BATCHED_UNLOCK: Inक्रमm the hypervisor about a batch of
 *				  pages that are about to be deflated from the
 *				  balloon (up to 512).
 * @VMW_BALLOON_CMD_BATCHED_2M_LOCK: Similar to @VMW_BALLOON_CMD_BATCHED_LOCK
 *				     क्रम 2MB pages.
 * @VMW_BALLOON_CMD_BATCHED_2M_UNLOCK: Similar to
 *				       @VMW_BALLOON_CMD_BATCHED_UNLOCK क्रम 2MB
 *				       pages.
 * @VMW_BALLOON_CMD_VMCI_DOORBELL_SET: A command to set करोorbell notअगरication
 *				       that would be invoked when the balloon
 *				       size changes.
 * @VMW_BALLOON_CMD_LAST: Value of the last command.
 */
क्रमागत vmballoon_cmd_type अणु
	VMW_BALLOON_CMD_START,
	VMW_BALLOON_CMD_GET_TARGET,
	VMW_BALLOON_CMD_LOCK,
	VMW_BALLOON_CMD_UNLOCK,
	VMW_BALLOON_CMD_GUEST_ID,
	/* No command 5 */
	VMW_BALLOON_CMD_BATCHED_LOCK = 6,
	VMW_BALLOON_CMD_BATCHED_UNLOCK,
	VMW_BALLOON_CMD_BATCHED_2M_LOCK,
	VMW_BALLOON_CMD_BATCHED_2M_UNLOCK,
	VMW_BALLOON_CMD_VMCI_DOORBELL_SET,
	VMW_BALLOON_CMD_LAST = VMW_BALLOON_CMD_VMCI_DOORBELL_SET,
पूर्ण;

#घोषणा VMW_BALLOON_CMD_NUM	(VMW_BALLOON_CMD_LAST + 1)

क्रमागत vmballoon_error_codes अणु
	VMW_BALLOON_SUCCESS,
	VMW_BALLOON_ERROR_CMD_INVALID,
	VMW_BALLOON_ERROR_PPN_INVALID,
	VMW_BALLOON_ERROR_PPN_LOCKED,
	VMW_BALLOON_ERROR_PPN_UNLOCKED,
	VMW_BALLOON_ERROR_PPN_PINNED,
	VMW_BALLOON_ERROR_PPN_NOTNEEDED,
	VMW_BALLOON_ERROR_RESET,
	VMW_BALLOON_ERROR_BUSY
पूर्ण;

#घोषणा VMW_BALLOON_SUCCESS_WITH_CAPABILITIES	(0x03000000)

#घोषणा VMW_BALLOON_CMD_WITH_TARGET_MASK			\
	((1UL << VMW_BALLOON_CMD_GET_TARGET)		|	\
	 (1UL << VMW_BALLOON_CMD_LOCK)			|	\
	 (1UL << VMW_BALLOON_CMD_UNLOCK)		|	\
	 (1UL << VMW_BALLOON_CMD_BATCHED_LOCK)		|	\
	 (1UL << VMW_BALLOON_CMD_BATCHED_UNLOCK)	|	\
	 (1UL << VMW_BALLOON_CMD_BATCHED_2M_LOCK)	|	\
	 (1UL << VMW_BALLOON_CMD_BATCHED_2M_UNLOCK))

अटल स्थिर अक्षर * स्थिर vmballoon_cmd_names[] = अणु
	[VMW_BALLOON_CMD_START]			= "start",
	[VMW_BALLOON_CMD_GET_TARGET]		= "target",
	[VMW_BALLOON_CMD_LOCK]			= "lock",
	[VMW_BALLOON_CMD_UNLOCK]		= "unlock",
	[VMW_BALLOON_CMD_GUEST_ID]		= "guestType",
	[VMW_BALLOON_CMD_BATCHED_LOCK]		= "batchLock",
	[VMW_BALLOON_CMD_BATCHED_UNLOCK]	= "batchUnlock",
	[VMW_BALLOON_CMD_BATCHED_2M_LOCK]	= "2m-lock",
	[VMW_BALLOON_CMD_BATCHED_2M_UNLOCK]	= "2m-unlock",
	[VMW_BALLOON_CMD_VMCI_DOORBELL_SET]	= "doorbellSet"
पूर्ण;

क्रमागत vmballoon_stat_page अणु
	VMW_BALLOON_PAGE_STAT_ALLOC,
	VMW_BALLOON_PAGE_STAT_ALLOC_FAIL,
	VMW_BALLOON_PAGE_STAT_REFUSED_ALLOC,
	VMW_BALLOON_PAGE_STAT_REFUSED_FREE,
	VMW_BALLOON_PAGE_STAT_FREE,
	VMW_BALLOON_PAGE_STAT_LAST = VMW_BALLOON_PAGE_STAT_FREE
पूर्ण;

#घोषणा VMW_BALLOON_PAGE_STAT_NUM	(VMW_BALLOON_PAGE_STAT_LAST + 1)

क्रमागत vmballoon_stat_general अणु
	VMW_BALLOON_STAT_TIMER,
	VMW_BALLOON_STAT_DOORBELL,
	VMW_BALLOON_STAT_RESET,
	VMW_BALLOON_STAT_SHRINK,
	VMW_BALLOON_STAT_SHRINK_FREE,
	VMW_BALLOON_STAT_LAST = VMW_BALLOON_STAT_SHRINK_FREE
पूर्ण;

#घोषणा VMW_BALLOON_STAT_NUM		(VMW_BALLOON_STAT_LAST + 1)

अटल DEFINE_STATIC_KEY_TRUE(vmw_balloon_batching);
अटल DEFINE_STATIC_KEY_FALSE(balloon_stat_enabled);

काष्ठा vmballoon_ctl अणु
	काष्ठा list_head pages;
	काष्ठा list_head refused_pages;
	काष्ठा list_head pपुनः_स्मृति_pages;
	अचिन्हित पूर्णांक n_refused_pages;
	अचिन्हित पूर्णांक n_pages;
	क्रमागत vmballoon_page_माप_प्रकारype page_size;
	क्रमागत vmballoon_op op;
पूर्ण;

/**
 * काष्ठा vmballoon_batch_entry - a batch entry क्रम lock or unlock.
 *
 * @status: the status of the operation, which is written by the hypervisor.
 * @reserved: reserved क्रम future use. Must be set to zero.
 * @pfn: the physical frame number of the page to be locked or unlocked.
 */
काष्ठा vmballoon_batch_entry अणु
	u64 status : 5;
	u64 reserved : PAGE_SHIFT - 5;
	u64 pfn : 52;
पूर्ण __packed;

काष्ठा vmballoon अणु
	/**
	 * @max_page_size: maximum supported page size क्रम ballooning.
	 *
	 * Protected by @conf_sem
	 */
	क्रमागत vmballoon_page_माप_प्रकारype max_page_size;

	/**
	 * @size: balloon actual size in basic page size (frames).
	 *
	 * While we currently करो not support size which is bigger than 32-bit,
	 * in preparation क्रम future support, use 64-bits.
	 */
	atomic64_t size;

	/**
	 * @target: balloon target size in basic page size (frames).
	 *
	 * We करो not protect the target under the assumption that setting the
	 * value is always करोne through a single ग_लिखो. If this assumption ever
	 * अवरोधs, we would have to use X_ONCE क्रम accesses, and suffer the less
	 * optimized code. Although we may पढ़ो stale target value अगर multiple
	 * accesses happen at once, the perक्रमmance impact should be minor.
	 */
	अचिन्हित दीर्घ target;

	/**
	 * @reset_required: reset flag
	 *
	 * Setting this flag may पूर्णांकroduce races, but the code is expected to
	 * handle them gracefully. In the worst हाल, another operation will
	 * fail as reset did not take place. Clearing the flag is करोne जबतक
	 * holding @conf_sem क्रम ग_लिखो.
	 */
	bool reset_required;

	/**
	 * @capabilities: hypervisor balloon capabilities.
	 *
	 * Protected by @conf_sem.
	 */
	अचिन्हित दीर्घ capabilities;

	/**
	 * @batch_page: poपूर्णांकer to communication batch page.
	 *
	 * When batching is used, batch_page poपूर्णांकs to a page, which holds up to
	 * %VMW_BALLOON_BATCH_MAX_PAGES entries क्रम locking or unlocking.
	 */
	काष्ठा vmballoon_batch_entry *batch_page;

	/**
	 * @batch_max_pages: maximum pages that can be locked/unlocked.
	 *
	 * Indicates the number of pages that the hypervisor can lock or unlock
	 * at once, according to whether batching is enabled. If batching is
	 * disabled, only a single page can be locked/unlock on each operation.
	 *
	 * Protected by @conf_sem.
	 */
	अचिन्हित पूर्णांक batch_max_pages;

	/**
	 * @page: page to be locked/unlocked by the hypervisor
	 *
	 * @page is only used when batching is disabled and a single page is
	 * reclaimed on each iteration.
	 *
	 * Protected by @comm_lock.
	 */
	काष्ठा page *page;

	/**
	 * @shrink_समयout: समयout until the next inflation.
	 *
	 * After an shrink event, indicates the समय in jअगरfies after which
	 * inflation is allowed again. Can be written concurrently with पढ़ोs,
	 * so must use READ_ONCE/WRITE_ONCE when accessing.
	 */
	अचिन्हित दीर्घ shrink_समयout;

	/* statistics */
	काष्ठा vmballoon_stats *stats;

	/**
	 * @b_dev_info: balloon device inक्रमmation descriptor.
	 */
	काष्ठा balloon_dev_info b_dev_info;

	काष्ठा delayed_work dwork;

	/**
	 * @huge_pages - list of the inflated 2MB pages.
	 *
	 * Protected by @b_dev_info.pages_lock .
	 */
	काष्ठा list_head huge_pages;

	/**
	 * @vmci_करोorbell.
	 *
	 * Protected by @conf_sem.
	 */
	काष्ठा vmci_handle vmci_करोorbell;

	/**
	 * @conf_sem: semaphore to protect the configuration and the statistics.
	 */
	काष्ठा rw_semaphore conf_sem;

	/**
	 * @comm_lock: lock to protect the communication with the host.
	 *
	 * Lock ordering: @conf_sem -> @comm_lock .
	 */
	spinlock_t comm_lock;

	/**
	 * @shrinker: shrinker पूर्णांकerface that is used to aव्योम over-inflation.
	 */
	काष्ठा shrinker shrinker;

	/**
	 * @shrinker_रेजिस्टरed: whether the shrinker was रेजिस्टरed.
	 *
	 * The shrinker पूर्णांकerface करोes not handle gracefully the removal of
	 * shrinker that was not रेजिस्टरed beक्रमe. This indication allows to
	 * simplअगरy the unregistration process.
	 */
	bool shrinker_रेजिस्टरed;
पूर्ण;

अटल काष्ठा vmballoon balloon;

काष्ठा vmballoon_stats अणु
	/* समयr / करोorbell operations */
	atomic64_t general_stat[VMW_BALLOON_STAT_NUM];

	/* allocation statistics क्रम huge and small pages */
	atomic64_t
	       page_stat[VMW_BALLOON_PAGE_STAT_NUM][VMW_BALLOON_NUM_PAGE_SIZES];

	/* Monitor operations: total operations, and failures */
	atomic64_t ops[VMW_BALLOON_CMD_NUM][VMW_BALLOON_OP_STAT_TYPES];
पूर्ण;

अटल अंतरभूत bool is_vmballoon_stats_on(व्योम)
अणु
	वापस IS_ENABLED(CONFIG_DEBUG_FS) &&
		अटल_branch_unlikely(&balloon_stat_enabled);
पूर्ण

अटल अंतरभूत व्योम vmballoon_stats_op_inc(काष्ठा vmballoon *b, अचिन्हित पूर्णांक op,
					  क्रमागत vmballoon_op_stat_type type)
अणु
	अगर (is_vmballoon_stats_on())
		atomic64_inc(&b->stats->ops[op][type]);
पूर्ण

अटल अंतरभूत व्योम vmballoon_stats_gen_inc(काष्ठा vmballoon *b,
					   क्रमागत vmballoon_stat_general stat)
अणु
	अगर (is_vmballoon_stats_on())
		atomic64_inc(&b->stats->general_stat[stat]);
पूर्ण

अटल अंतरभूत व्योम vmballoon_stats_gen_add(काष्ठा vmballoon *b,
					   क्रमागत vmballoon_stat_general stat,
					   अचिन्हित पूर्णांक val)
अणु
	अगर (is_vmballoon_stats_on())
		atomic64_add(val, &b->stats->general_stat[stat]);
पूर्ण

अटल अंतरभूत व्योम vmballoon_stats_page_inc(काष्ठा vmballoon *b,
					    क्रमागत vmballoon_stat_page stat,
					    क्रमागत vmballoon_page_माप_प्रकारype size)
अणु
	अगर (is_vmballoon_stats_on())
		atomic64_inc(&b->stats->page_stat[stat][size]);
पूर्ण

अटल अंतरभूत व्योम vmballoon_stats_page_add(काष्ठा vmballoon *b,
					    क्रमागत vmballoon_stat_page stat,
					    क्रमागत vmballoon_page_माप_प्रकारype size,
					    अचिन्हित पूर्णांक val)
अणु
	अगर (is_vmballoon_stats_on())
		atomic64_add(val, &b->stats->page_stat[stat][size]);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ
__vmballoon_cmd(काष्ठा vmballoon *b, अचिन्हित दीर्घ cmd, अचिन्हित दीर्घ arg1,
		अचिन्हित दीर्घ arg2, अचिन्हित दीर्घ *result)
अणु
	अचिन्हित दीर्घ status, dummy1, dummy2, dummy3, local_result;

	vmballoon_stats_op_inc(b, cmd, VMW_BALLOON_OP_STAT);

	यंत्र अस्थिर ("inl %%dx" :
		"=a"(status),
		"=c"(dummy1),
		"=d"(dummy2),
		"=b"(local_result),
		"=S"(dummy3) :
		"0"(VMW_BALLOON_HV_MAGIC),
		"1"(cmd),
		"2"(VMW_BALLOON_HV_PORT),
		"3"(arg1),
		"4"(arg2) :
		"memory");

	/* update the result अगर needed */
	अगर (result)
		*result = (cmd == VMW_BALLOON_CMD_START) ? dummy1 :
							   local_result;

	/* update target when applicable */
	अगर (status == VMW_BALLOON_SUCCESS &&
	    ((1ul << cmd) & VMW_BALLOON_CMD_WITH_TARGET_MASK))
		WRITE_ONCE(b->target, local_result);

	अगर (status != VMW_BALLOON_SUCCESS &&
	    status != VMW_BALLOON_SUCCESS_WITH_CAPABILITIES) अणु
		vmballoon_stats_op_inc(b, cmd, VMW_BALLOON_OP_FAIL_STAT);
		pr_debug("%s: %s [0x%lx,0x%lx) failed, returned %ld\n",
			 __func__, vmballoon_cmd_names[cmd], arg1, arg2,
			 status);
	पूर्ण

	/* mark reset required accordingly */
	अगर (status == VMW_BALLOON_ERROR_RESET)
		b->reset_required = true;

	वापस status;
पूर्ण

अटल __always_अंतरभूत अचिन्हित दीर्घ
vmballoon_cmd(काष्ठा vmballoon *b, अचिन्हित दीर्घ cmd, अचिन्हित दीर्घ arg1,
	      अचिन्हित दीर्घ arg2)
अणु
	अचिन्हित दीर्घ dummy;

	वापस __vmballoon_cmd(b, cmd, arg1, arg2, &dummy);
पूर्ण

/*
 * Send "start" command to the host, communicating supported version
 * of the protocol.
 */
अटल पूर्णांक vmballoon_send_start(काष्ठा vmballoon *b, अचिन्हित दीर्घ req_caps)
अणु
	अचिन्हित दीर्घ status, capabilities;

	status = __vmballoon_cmd(b, VMW_BALLOON_CMD_START, req_caps, 0,
				 &capabilities);

	चयन (status) अणु
	हाल VMW_BALLOON_SUCCESS_WITH_CAPABILITIES:
		b->capabilities = capabilities;
		अवरोध;
	हाल VMW_BALLOON_SUCCESS:
		b->capabilities = VMW_BALLOON_BASIC_CMDS;
		अवरोध;
	शेष:
		वापस -EIO;
	पूर्ण

	/*
	 * 2MB pages are only supported with batching. If batching is क्रम some
	 * reason disabled, करो not use 2MB pages, since otherwise the legacy
	 * mechanism is used with 2MB pages, causing a failure.
	 */
	b->max_page_size = VMW_BALLOON_4K_PAGE;
	अगर ((b->capabilities & VMW_BALLOON_BATCHED_2M_CMDS) &&
	    (b->capabilities & VMW_BALLOON_BATCHED_CMDS))
		b->max_page_size = VMW_BALLOON_2M_PAGE;


	वापस 0;
पूर्ण

/**
 * vmballoon_send_guest_id - communicate guest type to the host.
 *
 * @b: poपूर्णांकer to the balloon.
 *
 * Communicate guest type to the host so that it can adjust ballooning
 * algorithm to the one most appropriate क्रम the guest. This command
 * is normally issued after sending "start" command and is part of
 * standard reset sequence.
 *
 * Return: zero on success or appropriate error code.
 */
अटल पूर्णांक vmballoon_send_guest_id(काष्ठा vmballoon *b)
अणु
	अचिन्हित दीर्घ status;

	status = vmballoon_cmd(b, VMW_BALLOON_CMD_GUEST_ID,
			       VMW_BALLOON_GUEST_ID, 0);

	वापस status == VMW_BALLOON_SUCCESS ? 0 : -EIO;
पूर्ण

/**
 * vmballoon_page_order() - वापस the order of the page
 * @page_size: the size of the page.
 *
 * Return: the allocation order.
 */
अटल अंतरभूत
अचिन्हित पूर्णांक vmballoon_page_order(क्रमागत vmballoon_page_माप_प्रकारype page_size)
अणु
	वापस page_size == VMW_BALLOON_2M_PAGE ? VMW_BALLOON_2M_ORDER : 0;
पूर्ण

/**
 * vmballoon_page_in_frames() - वापसs the number of frames in a page.
 * @page_size: the size of the page.
 *
 * Return: the number of 4k frames.
 */
अटल अंतरभूत अचिन्हित पूर्णांक
vmballoon_page_in_frames(क्रमागत vmballoon_page_माप_प्रकारype page_size)
अणु
	वापस 1 << vmballoon_page_order(page_size);
पूर्ण

/**
 * vmballoon_mark_page_offline() - mark a page as offline
 * @page: poपूर्णांकer क्रम the page.
 * @page_size: the size of the page.
 */
अटल व्योम
vmballoon_mark_page_offline(काष्ठा page *page,
			    क्रमागत vmballoon_page_माप_प्रकारype page_size)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < vmballoon_page_in_frames(page_size); i++)
		__SetPageOffline(page + i);
पूर्ण

/**
 * vmballoon_mark_page_online() - mark a page as online
 * @page: poपूर्णांकer क्रम the page.
 * @page_size: the size of the page.
 */
अटल व्योम
vmballoon_mark_page_online(काष्ठा page *page,
			   क्रमागत vmballoon_page_माप_प्रकारype page_size)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < vmballoon_page_in_frames(page_size); i++)
		__ClearPageOffline(page + i);
पूर्ण

/**
 * vmballoon_send_get_target() - Retrieve desired balloon size from the host.
 *
 * @b: poपूर्णांकer to the balloon.
 *
 * Return: zero on success, EINVAL अगर limit करोes not fit in 32-bit, as required
 * by the host-guest protocol and EIO अगर an error occurred in communicating with
 * the host.
 */
अटल पूर्णांक vmballoon_send_get_target(काष्ठा vmballoon *b)
अणु
	अचिन्हित दीर्घ status;
	अचिन्हित दीर्घ limit;

	limit = totalram_pages();

	/* Ensure limit fits in 32-bits अगर 64-bit tarमाला_लो are not supported */
	अगर (!(b->capabilities & VMW_BALLOON_64_BIT_TARGET) &&
	    limit != (u32)limit)
		वापस -EINVAL;

	status = vmballoon_cmd(b, VMW_BALLOON_CMD_GET_TARGET, limit, 0);

	वापस status == VMW_BALLOON_SUCCESS ? 0 : -EIO;
पूर्ण

/**
 * vmballoon_alloc_page_list - allocates a list of pages.
 *
 * @b: poपूर्णांकer to the balloon.
 * @ctl: poपूर्णांकer क्रम the %काष्ठा vmballoon_ctl, which defines the operation.
 * @req_n_pages: the number of requested pages.
 *
 * Tries to allocate @req_n_pages. Add them to the list of balloon pages in
 * @ctl.pages and updates @ctl.n_pages to reflect the number of pages.
 *
 * Return: zero on success or error code otherwise.
 */
अटल पूर्णांक vmballoon_alloc_page_list(काष्ठा vmballoon *b,
				     काष्ठा vmballoon_ctl *ctl,
				     अचिन्हित पूर्णांक req_n_pages)
अणु
	काष्ठा page *page;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < req_n_pages; i++) अणु
		/*
		 * First check अगर we happen to have pages that were allocated
		 * beक्रमe. This happens when 2MB page rejected during inflation
		 * by the hypervisor, and then split पूर्णांकo 4KB pages.
		 */
		अगर (!list_empty(&ctl->pपुनः_स्मृति_pages)) अणु
			page = list_first_entry(&ctl->pपुनः_स्मृति_pages,
						काष्ठा page, lru);
			list_del(&page->lru);
		पूर्ण अन्यथा अणु
			अगर (ctl->page_size == VMW_BALLOON_2M_PAGE)
				page = alloc_pages(__GFP_HIGHMEM|__GFP_NOWARN|
					__GFP_NOMEMALLOC, VMW_BALLOON_2M_ORDER);
			अन्यथा
				page = balloon_page_alloc();

			vmballoon_stats_page_inc(b, VMW_BALLOON_PAGE_STAT_ALLOC,
						 ctl->page_size);
		पूर्ण

		अगर (page) अणु
			/* Success. Add the page to the list and जारी. */
			list_add(&page->lru, &ctl->pages);
			जारी;
		पूर्ण

		/* Allocation failed. Update statistics and stop. */
		vmballoon_stats_page_inc(b, VMW_BALLOON_PAGE_STAT_ALLOC_FAIL,
					 ctl->page_size);
		अवरोध;
	पूर्ण

	ctl->n_pages = i;

	वापस req_n_pages == ctl->n_pages ? 0 : -ENOMEM;
पूर्ण

/**
 * vmballoon_handle_one_result - Handle lock/unlock result क्रम a single page.
 *
 * @b: poपूर्णांकer क्रम %काष्ठा vmballoon.
 * @page: poपूर्णांकer क्रम the page whose result should be handled.
 * @page_size: size of the page.
 * @status: status of the operation as provided by the hypervisor.
 */
अटल पूर्णांक vmballoon_handle_one_result(काष्ठा vmballoon *b, काष्ठा page *page,
				       क्रमागत vmballoon_page_माप_प्रकारype page_size,
				       अचिन्हित दीर्घ status)
अणु
	/* On success करो nothing. The page is alपढ़ोy on the balloon list. */
	अगर (likely(status == VMW_BALLOON_SUCCESS))
		वापस 0;

	pr_debug("%s: failed comm pfn %lx status %lu page_size %s\n", __func__,
		 page_to_pfn(page), status,
		 vmballoon_page_size_names[page_size]);

	/* Error occurred */
	vmballoon_stats_page_inc(b, VMW_BALLOON_PAGE_STAT_REFUSED_ALLOC,
				 page_size);

	वापस -EIO;
पूर्ण

/**
 * vmballoon_status_page - वापसs the status of (un)lock operation
 *
 * @b: poपूर्णांकer to the balloon.
 * @idx: index क्रम the page क्रम which the operation is perक्रमmed.
 * @p: poपूर्णांकer to where the page काष्ठा is वापसed.
 *
 * Following a lock or unlock operation, वापसs the status of the operation क्रम
 * an inभागidual page. Provides the page that the operation was perक्रमmed on on
 * the @page argument.
 *
 * Returns: The status of a lock or unlock operation क्रम an inभागidual page.
 */
अटल अचिन्हित दीर्घ vmballoon_status_page(काष्ठा vmballoon *b, पूर्णांक idx,
					   काष्ठा page **p)
अणु
	अगर (अटल_branch_likely(&vmw_balloon_batching)) अणु
		/* batching mode */
		*p = pfn_to_page(b->batch_page[idx].pfn);
		वापस b->batch_page[idx].status;
	पूर्ण

	/* non-batching mode */
	*p = b->page;

	/*
	 * If a failure occurs, the indication will be provided in the status
	 * of the entire operation, which is considered beक्रमe the inभागidual
	 * page status. So क्रम non-batching mode, the indication is always of
	 * success.
	 */
	वापस VMW_BALLOON_SUCCESS;
पूर्ण

/**
 * vmballoon_lock_op - notअगरies the host about inflated/deflated pages.
 * @b: poपूर्णांकer to the balloon.
 * @num_pages: number of inflated/deflated pages.
 * @page_size: size of the page.
 * @op: the type of operation (lock or unlock).
 *
 * Notअगरy the host about page(s) that were ballooned (or हटाओd from the
 * balloon) so that host can use it without fear that guest will need it (or
 * stop using them since the VM करोes). Host may reject some pages, we need to
 * check the वापस value and maybe submit a dअगरferent page. The pages that are
 * inflated/deflated are poपूर्णांकed by @b->page.
 *
 * Return: result as provided by the hypervisor.
 */
अटल अचिन्हित दीर्घ vmballoon_lock_op(काष्ठा vmballoon *b,
				       अचिन्हित पूर्णांक num_pages,
				       क्रमागत vmballoon_page_माप_प्रकारype page_size,
				       क्रमागत vmballoon_op op)
अणु
	अचिन्हित दीर्घ cmd, pfn;

	lockdep_निश्चित_held(&b->comm_lock);

	अगर (अटल_branch_likely(&vmw_balloon_batching)) अणु
		अगर (op == VMW_BALLOON_INFLATE)
			cmd = page_size == VMW_BALLOON_2M_PAGE ?
				VMW_BALLOON_CMD_BATCHED_2M_LOCK :
				VMW_BALLOON_CMD_BATCHED_LOCK;
		अन्यथा
			cmd = page_size == VMW_BALLOON_2M_PAGE ?
				VMW_BALLOON_CMD_BATCHED_2M_UNLOCK :
				VMW_BALLOON_CMD_BATCHED_UNLOCK;

		pfn = PHYS_PFN(virt_to_phys(b->batch_page));
	पूर्ण अन्यथा अणु
		cmd = op == VMW_BALLOON_INFLATE ? VMW_BALLOON_CMD_LOCK :
						  VMW_BALLOON_CMD_UNLOCK;
		pfn = page_to_pfn(b->page);

		/* In non-batching mode, PFNs must fit in 32-bit */
		अगर (unlikely(pfn != (u32)pfn))
			वापस VMW_BALLOON_ERROR_PPN_INVALID;
	पूर्ण

	वापस vmballoon_cmd(b, cmd, pfn, num_pages);
पूर्ण

/**
 * vmballoon_add_page - adds a page towards lock/unlock operation.
 *
 * @b: poपूर्णांकer to the balloon.
 * @idx: index of the page to be ballooned in this batch.
 * @p: poपूर्णांकer to the page that is about to be ballooned.
 *
 * Adds the page to be ballooned. Must be called जबतक holding @comm_lock.
 */
अटल व्योम vmballoon_add_page(काष्ठा vmballoon *b, अचिन्हित पूर्णांक idx,
			       काष्ठा page *p)
अणु
	lockdep_निश्चित_held(&b->comm_lock);

	अगर (अटल_branch_likely(&vmw_balloon_batching))
		b->batch_page[idx] = (काष्ठा vmballoon_batch_entry)
					अणु .pfn = page_to_pfn(p) पूर्ण;
	अन्यथा
		b->page = p;
पूर्ण

/**
 * vmballoon_lock - lock or unlock a batch of pages.
 *
 * @b: poपूर्णांकer to the balloon.
 * @ctl: poपूर्णांकer क्रम the %काष्ठा vmballoon_ctl, which defines the operation.
 *
 * Notअगरies the host of about ballooned pages (after inflation or deflation,
 * according to @ctl). If the host rejects the page put it on the
 * @ctl refuse list. These refused page are then released when moving to the
 * next size of pages.
 *
 * Note that we neither मुक्त any @page here nor put them back on the ballooned
 * pages list. Instead we queue it क्रम later processing. We करो that क्रम several
 * reasons. First, we करो not want to मुक्त the page under the lock. Second, it
 * allows us to unअगरy the handling of lock and unlock. In the inflate हाल, the
 * caller will check अगर there are too many refused pages and release them.
 * Although it is not identical to the past behavior, it should not affect
 * perक्रमmance.
 */
अटल पूर्णांक vmballoon_lock(काष्ठा vmballoon *b, काष्ठा vmballoon_ctl *ctl)
अणु
	अचिन्हित दीर्घ batch_status;
	काष्ठा page *page;
	अचिन्हित पूर्णांक i, num_pages;

	num_pages = ctl->n_pages;
	अगर (num_pages == 0)
		वापस 0;

	/* communication with the host is करोne under the communication lock */
	spin_lock(&b->comm_lock);

	i = 0;
	list_क्रम_each_entry(page, &ctl->pages, lru)
		vmballoon_add_page(b, i++, page);

	batch_status = vmballoon_lock_op(b, ctl->n_pages, ctl->page_size,
					 ctl->op);

	/*
	 * Iterate over the pages in the provided list. Since we are changing
	 * @ctl->n_pages we are saving the original value in @num_pages and
	 * use this value to bound the loop.
	 */
	क्रम (i = 0; i < num_pages; i++) अणु
		अचिन्हित दीर्घ status;

		status = vmballoon_status_page(b, i, &page);

		/*
		 * Failure of the whole batch overrides a single operation
		 * results.
		 */
		अगर (batch_status != VMW_BALLOON_SUCCESS)
			status = batch_status;

		/* Continue अगर no error happened */
		अगर (!vmballoon_handle_one_result(b, page, ctl->page_size,
						 status))
			जारी;

		/*
		 * Error happened. Move the pages to the refused list and update
		 * the pages number.
		 */
		list_move(&page->lru, &ctl->refused_pages);
		ctl->n_pages--;
		ctl->n_refused_pages++;
	पूर्ण

	spin_unlock(&b->comm_lock);

	वापस batch_status == VMW_BALLOON_SUCCESS ? 0 : -EIO;
पूर्ण

/**
 * vmballoon_release_page_list() - Releases a page list
 *
 * @page_list: list of pages to release.
 * @n_pages: poपूर्णांकer to the number of pages.
 * @page_size: whether the pages in the list are 2MB (or अन्यथा 4KB).
 *
 * Releases the list of pages and zeros the number of pages.
 */
अटल व्योम vmballoon_release_page_list(काष्ठा list_head *page_list,
				       पूर्णांक *n_pages,
				       क्रमागत vmballoon_page_माप_प्रकारype page_size)
अणु
	काष्ठा page *page, *पंचांगp;

	list_क्रम_each_entry_safe(page, पंचांगp, page_list, lru) अणु
		list_del(&page->lru);
		__मुक्त_pages(page, vmballoon_page_order(page_size));
	पूर्ण

	अगर (n_pages)
		*n_pages = 0;
पूर्ण


/*
 * Release pages that were allocated जबतक attempting to inflate the
 * balloon but were refused by the host क्रम one reason or another.
 */
अटल व्योम vmballoon_release_refused_pages(काष्ठा vmballoon *b,
					    काष्ठा vmballoon_ctl *ctl)
अणु
	vmballoon_stats_page_inc(b, VMW_BALLOON_PAGE_STAT_REFUSED_FREE,
				 ctl->page_size);

	vmballoon_release_page_list(&ctl->refused_pages, &ctl->n_refused_pages,
				    ctl->page_size);
पूर्ण

/**
 * vmballoon_change - retrieve the required balloon change
 *
 * @b: poपूर्णांकer क्रम the balloon.
 *
 * Return: the required change क्रम the balloon size. A positive number
 * indicates inflation, a negative number indicates a deflation.
 */
अटल पूर्णांक64_t vmballoon_change(काष्ठा vmballoon *b)
अणु
	पूर्णांक64_t size, target;

	size = atomic64_पढ़ो(&b->size);
	target = READ_ONCE(b->target);

	/*
	 * We must cast first because of पूर्णांक sizes
	 * Otherwise we might get huge positives instead of negatives
	 */

	अगर (b->reset_required)
		वापस 0;

	/* consider a 2MB slack on deflate, unless the balloon is emptied */
	अगर (target < size && target != 0 &&
	    size - target < vmballoon_page_in_frames(VMW_BALLOON_2M_PAGE))
		वापस 0;

	/* If an out-of-memory recently occurred, inflation is disallowed. */
	अगर (target > size && समय_beक्रमe(jअगरfies, READ_ONCE(b->shrink_समयout)))
		वापस 0;

	वापस target - size;
पूर्ण

/**
 * vmballoon_enqueue_page_list() - Enqueues list of pages after inflation.
 *
 * @b: poपूर्णांकer to balloon.
 * @pages: list of pages to enqueue.
 * @n_pages: poपूर्णांकer to number of pages in list. The value is zeroed.
 * @page_size: whether the pages are 2MB or 4KB pages.
 *
 * Enqueues the provides list of pages in the ballooned page list, clears the
 * list and zeroes the number of pages that was provided.
 */
अटल व्योम vmballoon_enqueue_page_list(काष्ठा vmballoon *b,
					काष्ठा list_head *pages,
					अचिन्हित पूर्णांक *n_pages,
					क्रमागत vmballoon_page_माप_प्रकारype page_size)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा page *page;

	अगर (page_size == VMW_BALLOON_4K_PAGE) अणु
		balloon_page_list_enqueue(&b->b_dev_info, pages);
	पूर्ण अन्यथा अणु
		/*
		 * Keep the huge pages in a local list which is not available
		 * क्रम the balloon compaction mechanism.
		 */
		spin_lock_irqsave(&b->b_dev_info.pages_lock, flags);

		list_क्रम_each_entry(page, pages, lru) अणु
			vmballoon_mark_page_offline(page, VMW_BALLOON_2M_PAGE);
		पूर्ण

		list_splice_init(pages, &b->huge_pages);
		__count_vm_events(BALLOON_INFLATE, *n_pages *
				  vmballoon_page_in_frames(VMW_BALLOON_2M_PAGE));
		spin_unlock_irqrestore(&b->b_dev_info.pages_lock, flags);
	पूर्ण

	*n_pages = 0;
पूर्ण

/**
 * vmballoon_dequeue_page_list() - Dequeues page lists क्रम deflation.
 *
 * @b: poपूर्णांकer to balloon.
 * @pages: list of pages to enqueue.
 * @n_pages: poपूर्णांकer to number of pages in list. The value is zeroed.
 * @page_size: whether the pages are 2MB or 4KB pages.
 * @n_req_pages: the number of requested pages.
 *
 * Dequeues the number of requested pages from the balloon क्रम deflation. The
 * number of dequeued pages may be lower, अगर not enough pages in the requested
 * size are available.
 */
अटल व्योम vmballoon_dequeue_page_list(काष्ठा vmballoon *b,
					काष्ठा list_head *pages,
					अचिन्हित पूर्णांक *n_pages,
					क्रमागत vmballoon_page_माप_प्रकारype page_size,
					अचिन्हित पूर्णांक n_req_pages)
अणु
	काष्ठा page *page, *पंचांगp;
	अचिन्हित पूर्णांक i = 0;
	अचिन्हित दीर्घ flags;

	/* In the हाल of 4k pages, use the compaction infraकाष्ठाure */
	अगर (page_size == VMW_BALLOON_4K_PAGE) अणु
		*n_pages = balloon_page_list_dequeue(&b->b_dev_info, pages,
						     n_req_pages);
		वापस;
	पूर्ण

	/* 2MB pages */
	spin_lock_irqsave(&b->b_dev_info.pages_lock, flags);
	list_क्रम_each_entry_safe(page, पंचांगp, &b->huge_pages, lru) अणु
		vmballoon_mark_page_online(page, VMW_BALLOON_2M_PAGE);

		list_move(&page->lru, pages);
		अगर (++i == n_req_pages)
			अवरोध;
	पूर्ण

	__count_vm_events(BALLOON_DEFLATE,
			  i * vmballoon_page_in_frames(VMW_BALLOON_2M_PAGE));
	spin_unlock_irqrestore(&b->b_dev_info.pages_lock, flags);
	*n_pages = i;
पूर्ण

/**
 * vmballoon_split_refused_pages() - Split the 2MB refused pages to 4k.
 *
 * If inflation of 2MB pages was denied by the hypervisor, it is likely to be
 * due to one or few 4KB pages. These 2MB pages may keep being allocated and
 * then being refused. To prevent this हाल, this function splits the refused
 * pages पूर्णांकo 4KB pages and adds them पूर्णांकo @pपुनः_स्मृति_pages list.
 *
 * @ctl: poपूर्णांकer क्रम the %काष्ठा vmballoon_ctl, which defines the operation.
 */
अटल व्योम vmballoon_split_refused_pages(काष्ठा vmballoon_ctl *ctl)
अणु
	काष्ठा page *page, *पंचांगp;
	अचिन्हित पूर्णांक i, order;

	order = vmballoon_page_order(ctl->page_size);

	list_क्रम_each_entry_safe(page, पंचांगp, &ctl->refused_pages, lru) अणु
		list_del(&page->lru);
		split_page(page, order);
		क्रम (i = 0; i < (1 << order); i++)
			list_add(&page[i].lru, &ctl->pपुनः_स्मृति_pages);
	पूर्ण
	ctl->n_refused_pages = 0;
पूर्ण

/**
 * vmballoon_inflate() - Inflate the balloon towards its target size.
 *
 * @b: poपूर्णांकer to the balloon.
 */
अटल व्योम vmballoon_inflate(काष्ठा vmballoon *b)
अणु
	पूर्णांक64_t to_inflate_frames;
	काष्ठा vmballoon_ctl ctl = अणु
		.pages = LIST_HEAD_INIT(ctl.pages),
		.refused_pages = LIST_HEAD_INIT(ctl.refused_pages),
		.pपुनः_स्मृति_pages = LIST_HEAD_INIT(ctl.pपुनः_स्मृति_pages),
		.page_size = b->max_page_size,
		.op = VMW_BALLOON_INFLATE
	पूर्ण;

	जबतक ((to_inflate_frames = vmballoon_change(b)) > 0) अणु
		अचिन्हित पूर्णांक to_inflate_pages, page_in_frames;
		पूर्णांक alloc_error, lock_error = 0;

		VM_BUG_ON(!list_empty(&ctl.pages));
		VM_BUG_ON(ctl.n_pages != 0);

		page_in_frames = vmballoon_page_in_frames(ctl.page_size);

		to_inflate_pages = min_t(अचिन्हित दीर्घ, b->batch_max_pages,
					 DIV_ROUND_UP_ULL(to_inflate_frames,
							  page_in_frames));

		/* Start by allocating */
		alloc_error = vmballoon_alloc_page_list(b, &ctl,
							to_inflate_pages);

		/* Actually lock the pages by telling the hypervisor */
		lock_error = vmballoon_lock(b, &ctl);

		/*
		 * If an error indicates that something serious went wrong,
		 * stop the inflation.
		 */
		अगर (lock_error)
			अवरोध;

		/* Update the balloon size */
		atomic64_add(ctl.n_pages * page_in_frames, &b->size);

		vmballoon_enqueue_page_list(b, &ctl.pages, &ctl.n_pages,
					    ctl.page_size);

		/*
		 * If allocation failed or the number of refused pages exceeds
		 * the maximum allowed, move to the next page size.
		 */
		अगर (alloc_error ||
		    ctl.n_refused_pages >= VMW_BALLOON_MAX_REFUSED) अणु
			अगर (ctl.page_size == VMW_BALLOON_4K_PAGE)
				अवरोध;

			/*
			 * Split the refused pages to 4k. This will also empty
			 * the refused pages list.
			 */
			vmballoon_split_refused_pages(&ctl);
			ctl.page_size--;
		पूर्ण

		cond_resched();
	पूर्ण

	/*
	 * Release pages that were allocated जबतक attempting to inflate the
	 * balloon but were refused by the host क्रम one reason or another,
	 * and update the statistics.
	 */
	अगर (ctl.n_refused_pages != 0)
		vmballoon_release_refused_pages(b, &ctl);

	vmballoon_release_page_list(&ctl.pपुनः_स्मृति_pages, शून्य, ctl.page_size);
पूर्ण

/**
 * vmballoon_deflate() - Decrease the size of the balloon.
 *
 * @b: poपूर्णांकer to the balloon
 * @n_frames: the number of frames to deflate. If zero, स्वतःmatically
 * calculated according to the target size.
 * @coordinated: whether to coordinate with the host
 *
 * Decrease the size of the balloon allowing guest to use more memory.
 *
 * Return: The number of deflated frames (i.e., basic page size units)
 */
अटल अचिन्हित दीर्घ vmballoon_deflate(काष्ठा vmballoon *b, uपूर्णांक64_t n_frames,
				       bool coordinated)
अणु
	अचिन्हित दीर्घ deflated_frames = 0;
	अचिन्हित दीर्घ tried_frames = 0;
	काष्ठा vmballoon_ctl ctl = अणु
		.pages = LIST_HEAD_INIT(ctl.pages),
		.refused_pages = LIST_HEAD_INIT(ctl.refused_pages),
		.page_size = VMW_BALLOON_4K_PAGE,
		.op = VMW_BALLOON_DEFLATE
	पूर्ण;

	/* मुक्त pages to reach target */
	जबतक (true) अणु
		अचिन्हित पूर्णांक to_deflate_pages, n_unlocked_frames;
		अचिन्हित पूर्णांक page_in_frames;
		पूर्णांक64_t to_deflate_frames;
		bool deflated_all;

		page_in_frames = vmballoon_page_in_frames(ctl.page_size);

		VM_BUG_ON(!list_empty(&ctl.pages));
		VM_BUG_ON(ctl.n_pages);
		VM_BUG_ON(!list_empty(&ctl.refused_pages));
		VM_BUG_ON(ctl.n_refused_pages);

		/*
		 * If we were requested a specअगरic number of frames, we try to
		 * deflate this number of frames. Otherwise, deflation is
		 * perक्रमmed according to the target and balloon size.
		 */
		to_deflate_frames = n_frames ? n_frames - tried_frames :
					       -vmballoon_change(b);

		/* अवरोध अगर no work to करो */
		अगर (to_deflate_frames <= 0)
			अवरोध;

		/*
		 * Calculate the number of frames based on current page size,
		 * but limit the deflated frames to a single chunk
		 */
		to_deflate_pages = min_t(अचिन्हित दीर्घ, b->batch_max_pages,
					 DIV_ROUND_UP_ULL(to_deflate_frames,
							  page_in_frames));

		/* First take the pages from the balloon pages. */
		vmballoon_dequeue_page_list(b, &ctl.pages, &ctl.n_pages,
					    ctl.page_size, to_deflate_pages);

		/*
		 * Beक्रमe pages are moving to the refused list, count their
		 * frames as frames that we tried to deflate.
		 */
		tried_frames += ctl.n_pages * page_in_frames;

		/*
		 * Unlock the pages by communicating with the hypervisor अगर the
		 * communication is coordinated (i.e., not pop). We ignore the
		 * वापस code. Instead we check अगर all the pages we manage to
		 * unlock all the pages. If we failed, we will move to the next
		 * page size, and would eventually try again later.
		 */
		अगर (coordinated)
			vmballoon_lock(b, &ctl);

		/*
		 * Check अगर we deflated enough. We will move to the next page
		 * size अगर we did not manage to करो so. This calculation takes
		 * place now, as once the pages are released, the number of
		 * pages is zeroed.
		 */
		deflated_all = (ctl.n_pages == to_deflate_pages);

		/* Update local and global counters */
		n_unlocked_frames = ctl.n_pages * page_in_frames;
		atomic64_sub(n_unlocked_frames, &b->size);
		deflated_frames += n_unlocked_frames;

		vmballoon_stats_page_add(b, VMW_BALLOON_PAGE_STAT_FREE,
					 ctl.page_size, ctl.n_pages);

		/* मुक्त the ballooned pages */
		vmballoon_release_page_list(&ctl.pages, &ctl.n_pages,
					    ctl.page_size);

		/* Return the refused pages to the ballooned list. */
		vmballoon_enqueue_page_list(b, &ctl.refused_pages,
					    &ctl.n_refused_pages,
					    ctl.page_size);

		/* If we failed to unlock all the pages, move to next size. */
		अगर (!deflated_all) अणु
			अगर (ctl.page_size == b->max_page_size)
				अवरोध;
			ctl.page_size++;
		पूर्ण

		cond_resched();
	पूर्ण

	वापस deflated_frames;
पूर्ण

/**
 * vmballoon_deinit_batching - disables batching mode.
 *
 * @b: poपूर्णांकer to &काष्ठा vmballoon.
 *
 * Disables batching, by deallocating the page क्रम communication with the
 * hypervisor and disabling the अटल key to indicate that batching is off.
 */
अटल व्योम vmballoon_deinit_batching(काष्ठा vmballoon *b)
अणु
	मुक्त_page((अचिन्हित दीर्घ)b->batch_page);
	b->batch_page = शून्य;
	अटल_branch_disable(&vmw_balloon_batching);
	b->batch_max_pages = 1;
पूर्ण

/**
 * vmballoon_init_batching - enable batching mode.
 *
 * @b: poपूर्णांकer to &काष्ठा vmballoon.
 *
 * Enables batching, by allocating a page क्रम communication with the hypervisor
 * and enabling the अटल_key to use batching.
 *
 * Return: zero on success or an appropriate error-code.
 */
अटल पूर्णांक vmballoon_init_batching(काष्ठा vmballoon *b)
अणु
	काष्ठा page *page;

	page = alloc_page(GFP_KERNEL | __GFP_ZERO);
	अगर (!page)
		वापस -ENOMEM;

	b->batch_page = page_address(page);
	b->batch_max_pages = PAGE_SIZE / माप(काष्ठा vmballoon_batch_entry);

	अटल_branch_enable(&vmw_balloon_batching);

	वापस 0;
पूर्ण

/*
 * Receive notअगरication and resize balloon
 */
अटल व्योम vmballoon_करोorbell(व्योम *client_data)
अणु
	काष्ठा vmballoon *b = client_data;

	vmballoon_stats_gen_inc(b, VMW_BALLOON_STAT_DOORBELL);

	mod_delayed_work(प्रणाली_मुक्तzable_wq, &b->dwork, 0);
पूर्ण

/*
 * Clean up vmci करोorbell
 */
अटल व्योम vmballoon_vmci_cleanup(काष्ठा vmballoon *b)
अणु
	vmballoon_cmd(b, VMW_BALLOON_CMD_VMCI_DOORBELL_SET,
		      VMCI_INVALID_ID, VMCI_INVALID_ID);

	अगर (!vmci_handle_is_invalid(b->vmci_करोorbell)) अणु
		vmci_करोorbell_destroy(b->vmci_करोorbell);
		b->vmci_करोorbell = VMCI_INVALID_HANDLE;
	पूर्ण
पूर्ण

/**
 * vmballoon_vmci_init - Initialize vmci करोorbell.
 *
 * @b: poपूर्णांकer to the balloon.
 *
 * Return: zero on success or when wakeup command not supported. Error-code
 * otherwise.
 *
 * Initialize vmci करोorbell, to get notअगरied as soon as balloon changes.
 */
अटल पूर्णांक vmballoon_vmci_init(काष्ठा vmballoon *b)
अणु
	अचिन्हित दीर्घ error;

	अगर ((b->capabilities & VMW_BALLOON_SIGNALLED_WAKEUP_CMD) == 0)
		वापस 0;

	error = vmci_करोorbell_create(&b->vmci_करोorbell, VMCI_FLAG_DELAYED_CB,
				     VMCI_PRIVILEGE_FLAG_RESTRICTED,
				     vmballoon_करोorbell, b);

	अगर (error != VMCI_SUCCESS)
		जाओ fail;

	error =	__vmballoon_cmd(b, VMW_BALLOON_CMD_VMCI_DOORBELL_SET,
				b->vmci_करोorbell.context,
				b->vmci_करोorbell.resource, शून्य);

	अगर (error != VMW_BALLOON_SUCCESS)
		जाओ fail;

	वापस 0;
fail:
	vmballoon_vmci_cleanup(b);
	वापस -EIO;
पूर्ण

/**
 * vmballoon_pop - Quickly release all pages allocate क्रम the balloon.
 *
 * @b: poपूर्णांकer to the balloon.
 *
 * This function is called when host decides to "reset" balloon क्रम one reason
 * or another. Unlike normal "deflate" we करो not (shall not) notअगरy host of the
 * pages being released.
 */
अटल व्योम vmballoon_pop(काष्ठा vmballoon *b)
अणु
	अचिन्हित दीर्घ size;

	जबतक ((size = atomic64_पढ़ो(&b->size)))
		vmballoon_deflate(b, size, false);
पूर्ण

/*
 * Perक्रमm standard reset sequence by popping the balloon (in हाल it
 * is not  empty) and then restarting protocol. This operation normally
 * happens when host responds with VMW_BALLOON_ERROR_RESET to a command.
 */
अटल व्योम vmballoon_reset(काष्ठा vmballoon *b)
अणु
	पूर्णांक error;

	करोwn_ग_लिखो(&b->conf_sem);

	vmballoon_vmci_cleanup(b);

	/* मुक्त all pages, skipping monitor unlock */
	vmballoon_pop(b);

	अगर (vmballoon_send_start(b, VMW_BALLOON_CAPABILITIES))
		जाओ unlock;

	अगर ((b->capabilities & VMW_BALLOON_BATCHED_CMDS) != 0) अणु
		अगर (vmballoon_init_batching(b)) अणु
			/*
			 * We failed to initialize batching, inक्रमm the monitor
			 * about it by sending a null capability.
			 *
			 * The guest will retry in one second.
			 */
			vmballoon_send_start(b, 0);
			जाओ unlock;
		पूर्ण
	पूर्ण अन्यथा अगर ((b->capabilities & VMW_BALLOON_BASIC_CMDS) != 0) अणु
		vmballoon_deinit_batching(b);
	पूर्ण

	vmballoon_stats_gen_inc(b, VMW_BALLOON_STAT_RESET);
	b->reset_required = false;

	error = vmballoon_vmci_init(b);
	अगर (error)
		pr_err("failed to initialize vmci doorbell\n");

	अगर (vmballoon_send_guest_id(b))
		pr_err("failed to send guest ID to the host\n");

unlock:
	up_ग_लिखो(&b->conf_sem);
पूर्ण

/**
 * vmballoon_work - periodic balloon worker क्रम reset, inflation and deflation.
 *
 * @work: poपूर्णांकer to the &work_काष्ठा which is provided by the workqueue.
 *
 * Resets the protocol अगर needed, माला_लो the new size and adjusts balloon as
 * needed. Repeat in 1 sec.
 */
अटल व्योम vmballoon_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *dwork = to_delayed_work(work);
	काष्ठा vmballoon *b = container_of(dwork, काष्ठा vmballoon, dwork);
	पूर्णांक64_t change = 0;

	अगर (b->reset_required)
		vmballoon_reset(b);

	करोwn_पढ़ो(&b->conf_sem);

	/*
	 * Update the stats जबतक holding the semaphore to ensure that
	 * @stats_enabled is consistent with whether the stats are actually
	 * enabled
	 */
	vmballoon_stats_gen_inc(b, VMW_BALLOON_STAT_TIMER);

	अगर (!vmballoon_send_get_target(b))
		change = vmballoon_change(b);

	अगर (change != 0) अणु
		pr_debug("%s - size: %llu, target %lu\n", __func__,
			 atomic64_पढ़ो(&b->size), READ_ONCE(b->target));

		अगर (change > 0)
			vmballoon_inflate(b);
		अन्यथा  /* (change < 0) */
			vmballoon_deflate(b, 0, true);
	पूर्ण

	up_पढ़ो(&b->conf_sem);

	/*
	 * We are using a मुक्तzable workqueue so that balloon operations are
	 * stopped जबतक the प्रणाली transitions to/from sleep/hibernation.
	 */
	queue_delayed_work(प्रणाली_मुक्तzable_wq,
			   dwork, round_jअगरfies_relative(HZ));

पूर्ण

/**
 * vmballoon_shrinker_scan() - deflate the balloon due to memory pressure.
 * @shrinker: poपूर्णांकer to the balloon shrinker.
 * @sc: page reclaim inक्रमmation.
 *
 * Returns: number of pages that were मुक्तd during deflation.
 */
अटल अचिन्हित दीर्घ vmballoon_shrinker_scan(काष्ठा shrinker *shrinker,
					     काष्ठा shrink_control *sc)
अणु
	काष्ठा vmballoon *b = &balloon;
	अचिन्हित दीर्घ deflated_frames;

	pr_debug("%s - size: %llu", __func__, atomic64_पढ़ो(&b->size));

	vmballoon_stats_gen_inc(b, VMW_BALLOON_STAT_SHRINK);

	/*
	 * If the lock is also contended क्रम पढ़ो, we cannot easily reclaim and
	 * we bail out.
	 */
	अगर (!करोwn_पढ़ो_trylock(&b->conf_sem))
		वापस 0;

	deflated_frames = vmballoon_deflate(b, sc->nr_to_scan, true);

	vmballoon_stats_gen_add(b, VMW_BALLOON_STAT_SHRINK_FREE,
				deflated_frames);

	/*
	 * Delay future inflation क्रम some समय to mitigate the situations in
	 * which balloon continuously grows and shrinks. Use WRITE_ONCE() since
	 * the access is asynchronous.
	 */
	WRITE_ONCE(b->shrink_समयout, jअगरfies + HZ * VMBALLOON_SHRINK_DELAY);

	up_पढ़ो(&b->conf_sem);

	वापस deflated_frames;
पूर्ण

/**
 * vmballoon_shrinker_count() - वापस the number of ballooned pages.
 * @shrinker: poपूर्णांकer to the balloon shrinker.
 * @sc: page reclaim inक्रमmation.
 *
 * Returns: number of 4k pages that are allocated क्रम the balloon and can
 *	    thereक्रमe be reclaimed under pressure.
 */
अटल अचिन्हित दीर्घ vmballoon_shrinker_count(काष्ठा shrinker *shrinker,
					      काष्ठा shrink_control *sc)
अणु
	काष्ठा vmballoon *b = &balloon;

	वापस atomic64_पढ़ो(&b->size);
पूर्ण

अटल व्योम vmballoon_unरेजिस्टर_shrinker(काष्ठा vmballoon *b)
अणु
	अगर (b->shrinker_रेजिस्टरed)
		unरेजिस्टर_shrinker(&b->shrinker);
	b->shrinker_रेजिस्टरed = false;
पूर्ण

अटल पूर्णांक vmballoon_रेजिस्टर_shrinker(काष्ठा vmballoon *b)
अणु
	पूर्णांक r;

	/* Do nothing अगर the shrinker is not enabled */
	अगर (!vmwballoon_shrinker_enable)
		वापस 0;

	b->shrinker.scan_objects = vmballoon_shrinker_scan;
	b->shrinker.count_objects = vmballoon_shrinker_count;
	b->shrinker.seeks = DEFAULT_SEEKS;

	r = रेजिस्टर_shrinker(&b->shrinker);

	अगर (r == 0)
		b->shrinker_रेजिस्टरed = true;

	वापस r;
पूर्ण

/*
 * DEBUGFS Interface
 */
#अगर_घोषित CONFIG_DEBUG_FS

अटल स्थिर अक्षर * स्थिर vmballoon_stat_page_names[] = अणु
	[VMW_BALLOON_PAGE_STAT_ALLOC]		= "alloc",
	[VMW_BALLOON_PAGE_STAT_ALLOC_FAIL]	= "allocFail",
	[VMW_BALLOON_PAGE_STAT_REFUSED_ALLOC]	= "errAlloc",
	[VMW_BALLOON_PAGE_STAT_REFUSED_FREE]	= "errFree",
	[VMW_BALLOON_PAGE_STAT_FREE]		= "free"
पूर्ण;

अटल स्थिर अक्षर * स्थिर vmballoon_stat_names[] = अणु
	[VMW_BALLOON_STAT_TIMER]		= "timer",
	[VMW_BALLOON_STAT_DOORBELL]		= "doorbell",
	[VMW_BALLOON_STAT_RESET]		= "reset",
	[VMW_BALLOON_STAT_SHRINK]		= "shrink",
	[VMW_BALLOON_STAT_SHRINK_FREE]		= "shrinkFree"
पूर्ण;

अटल पूर्णांक vmballoon_enable_stats(काष्ठा vmballoon *b)
अणु
	पूर्णांक r = 0;

	करोwn_ग_लिखो(&b->conf_sem);

	/* did we somehow race with another पढ़ोer which enabled stats? */
	अगर (b->stats)
		जाओ out;

	b->stats = kzalloc(माप(*b->stats), GFP_KERNEL);

	अगर (!b->stats) अणु
		/* allocation failed */
		r = -ENOMEM;
		जाओ out;
	पूर्ण
	अटल_key_enable(&balloon_stat_enabled.key);
out:
	up_ग_लिखो(&b->conf_sem);
	वापस r;
पूर्ण

/**
 * vmballoon_debug_show - shows statistics of balloon operations.
 * @f: poपूर्णांकer to the &काष्ठा seq_file.
 * @offset: ignored.
 *
 * Provides the statistics that can be accessed in vmmemctl in the debugfs.
 * To aव्योम the overhead - मुख्यly that of memory - of collecting the statistics,
 * we only collect statistics after the first समय the counters are पढ़ो.
 *
 * Return: zero on success or an error code.
 */
अटल पूर्णांक vmballoon_debug_show(काष्ठा seq_file *f, व्योम *offset)
अणु
	काष्ठा vmballoon *b = f->निजी;
	पूर्णांक i, j;

	/* enables stats अगर they are disabled */
	अगर (!b->stats) अणु
		पूर्णांक r = vmballoon_enable_stats(b);

		अगर (r)
			वापस r;
	पूर्ण

	/* क्रमmat capabilities info */
	seq_म_लिखो(f, "%-22s: %#16x\n", "balloon capabilities",
		   VMW_BALLOON_CAPABILITIES);
	seq_म_लिखो(f, "%-22s: %#16lx\n", "used capabilities", b->capabilities);
	seq_म_लिखो(f, "%-22s: %16s\n", "is resetting",
		   b->reset_required ? "y" : "n");

	/* क्रमmat size info */
	seq_म_लिखो(f, "%-22s: %16lu\n", "target", READ_ONCE(b->target));
	seq_म_लिखो(f, "%-22s: %16llu\n", "current", atomic64_पढ़ो(&b->size));

	क्रम (i = 0; i < VMW_BALLOON_CMD_NUM; i++) अणु
		अगर (vmballoon_cmd_names[i] == शून्य)
			जारी;

		seq_म_लिखो(f, "%-22s: %16llu (%llu failed)\n",
			   vmballoon_cmd_names[i],
			   atomic64_पढ़ो(&b->stats->ops[i][VMW_BALLOON_OP_STAT]),
			   atomic64_पढ़ो(&b->stats->ops[i][VMW_BALLOON_OP_FAIL_STAT]));
	पूर्ण

	क्रम (i = 0; i < VMW_BALLOON_STAT_NUM; i++)
		seq_म_लिखो(f, "%-22s: %16llu\n",
			   vmballoon_stat_names[i],
			   atomic64_पढ़ो(&b->stats->general_stat[i]));

	क्रम (i = 0; i < VMW_BALLOON_PAGE_STAT_NUM; i++) अणु
		क्रम (j = 0; j < VMW_BALLOON_NUM_PAGE_SIZES; j++)
			seq_म_लिखो(f, "%-18s(%s): %16llu\n",
				   vmballoon_stat_page_names[i],
				   vmballoon_page_size_names[j],
				   atomic64_पढ़ो(&b->stats->page_stat[i][j]));
	पूर्ण

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(vmballoon_debug);

अटल व्योम __init vmballoon_debugfs_init(काष्ठा vmballoon *b)
अणु
	debugfs_create_file("vmmemctl", S_IRUGO, शून्य, b,
			    &vmballoon_debug_fops);
पूर्ण

अटल व्योम __निकास vmballoon_debugfs_निकास(काष्ठा vmballoon *b)
अणु
	अटल_key_disable(&balloon_stat_enabled.key);
	debugfs_हटाओ(debugfs_lookup("vmmemctl", शून्य));
	kमुक्त(b->stats);
	b->stats = शून्य;
पूर्ण

#अन्यथा

अटल अंतरभूत व्योम vmballoon_debugfs_init(काष्ठा vmballoon *b)
अणु
पूर्ण

अटल अंतरभूत व्योम vmballoon_debugfs_निकास(काष्ठा vmballoon *b)
अणु
पूर्ण

#पूर्ण_अगर	/* CONFIG_DEBUG_FS */


#अगर_घोषित CONFIG_BALLOON_COMPACTION

अटल पूर्णांक vmballoon_init_fs_context(काष्ठा fs_context *fc)
अणु
	वापस init_pseuकरो(fc, BALLOON_VMW_MAGIC) ? 0 : -ENOMEM;
पूर्ण

अटल काष्ठा file_प्रणाली_type vmballoon_fs = अणु
	.name           	= "balloon-vmware",
	.init_fs_context	= vmballoon_init_fs_context,
	.समाप्त_sb        	= समाप्त_anon_super,
पूर्ण;

अटल काष्ठा vfsmount *vmballoon_mnt;

/**
 * vmballoon_migratepage() - migrates a balloon page.
 * @b_dev_info: balloon device inक्रमmation descriptor.
 * @newpage: the page to which @page should be migrated.
 * @page: a ballooned page that should be migrated.
 * @mode: migration mode, ignored.
 *
 * This function is really खोलो-coded, but that is according to the पूर्णांकerface
 * that balloon_compaction provides.
 *
 * Return: zero on success, -EAGAIN when migration cannot be perक्रमmed
 *	   momentarily, and -EBUSY अगर migration failed and should be retried
 *	   with that specअगरic page.
 */
अटल पूर्णांक vmballoon_migratepage(काष्ठा balloon_dev_info *b_dev_info,
				 काष्ठा page *newpage, काष्ठा page *page,
				 क्रमागत migrate_mode mode)
अणु
	अचिन्हित दीर्घ status, flags;
	काष्ठा vmballoon *b;
	पूर्णांक ret;

	b = container_of(b_dev_info, काष्ठा vmballoon, b_dev_info);

	/*
	 * If the semaphore is taken, there is ongoing configuration change
	 * (i.e., balloon reset), so try again.
	 */
	अगर (!करोwn_पढ़ो_trylock(&b->conf_sem))
		वापस -EAGAIN;

	spin_lock(&b->comm_lock);
	/*
	 * We must start by deflating and not inflating, as otherwise the
	 * hypervisor may tell us that it has enough memory and the new page is
	 * not needed. Since the old page is isolated, we cannot use the list
	 * पूर्णांकerface to unlock it, as the LRU field is used क्रम isolation.
	 * Instead, we use the native पूर्णांकerface directly.
	 */
	vmballoon_add_page(b, 0, page);
	status = vmballoon_lock_op(b, 1, VMW_BALLOON_4K_PAGE,
				   VMW_BALLOON_DEFLATE);

	अगर (status == VMW_BALLOON_SUCCESS)
		status = vmballoon_status_page(b, 0, &page);

	/*
	 * If a failure happened, let the migration mechanism know that it
	 * should not retry.
	 */
	अगर (status != VMW_BALLOON_SUCCESS) अणु
		spin_unlock(&b->comm_lock);
		ret = -EBUSY;
		जाओ out_unlock;
	पूर्ण

	/*
	 * The page is isolated, so it is safe to delete it without holding
	 * @pages_lock . We keep holding @comm_lock since we will need it in a
	 * second.
	 */
	balloon_page_delete(page);

	put_page(page);

	/* Inflate */
	vmballoon_add_page(b, 0, newpage);
	status = vmballoon_lock_op(b, 1, VMW_BALLOON_4K_PAGE,
				   VMW_BALLOON_INFLATE);

	अगर (status == VMW_BALLOON_SUCCESS)
		status = vmballoon_status_page(b, 0, &newpage);

	spin_unlock(&b->comm_lock);

	अगर (status != VMW_BALLOON_SUCCESS) अणु
		/*
		 * A failure happened. While we can deflate the page we just
		 * inflated, this deflation can also encounter an error. Instead
		 * we will decrease the size of the balloon to reflect the
		 * change and report failure.
		 */
		atomic64_dec(&b->size);
		ret = -EBUSY;
	पूर्ण अन्यथा अणु
		/*
		 * Success. Take a reference क्रम the page, and we will add it to
		 * the list after acquiring the lock.
		 */
		get_page(newpage);
		ret = MIGRATEPAGE_SUCCESS;
	पूर्ण

	/* Update the balloon list under the @pages_lock */
	spin_lock_irqsave(&b->b_dev_info.pages_lock, flags);

	/*
	 * On inflation success, we alपढ़ोy took a reference क्रम the @newpage.
	 * If we succeed just insert it to the list and update the statistics
	 * under the lock.
	 */
	अगर (ret == MIGRATEPAGE_SUCCESS) अणु
		balloon_page_insert(&b->b_dev_info, newpage);
		__count_vm_event(BALLOON_MIGRATE);
	पूर्ण

	/*
	 * We deflated successfully, so regardless to the inflation success, we
	 * need to reduce the number of isolated_pages.
	 */
	b->b_dev_info.isolated_pages--;
	spin_unlock_irqrestore(&b->b_dev_info.pages_lock, flags);

out_unlock:
	up_पढ़ो(&b->conf_sem);
	वापस ret;
पूर्ण

/**
 * vmballoon_compaction_deinit() - हटाओs compaction related data.
 *
 * @b: poपूर्णांकer to the balloon.
 */
अटल व्योम vmballoon_compaction_deinit(काष्ठा vmballoon *b)
अणु
	अगर (!IS_ERR(b->b_dev_info.inode))
		iput(b->b_dev_info.inode);

	b->b_dev_info.inode = शून्य;
	kern_unmount(vmballoon_mnt);
	vmballoon_mnt = शून्य;
पूर्ण

/**
 * vmballoon_compaction_init() - initialized compaction क्रम the balloon.
 *
 * @b: poपूर्णांकer to the balloon.
 *
 * If during the initialization a failure occurred, this function करोes not
 * perक्रमm cleanup. The caller must call vmballoon_compaction_deinit() in this
 * हाल.
 *
 * Return: zero on success or error code on failure.
 */
अटल __init पूर्णांक vmballoon_compaction_init(काष्ठा vmballoon *b)
अणु
	vmballoon_mnt = kern_mount(&vmballoon_fs);
	अगर (IS_ERR(vmballoon_mnt))
		वापस PTR_ERR(vmballoon_mnt);

	b->b_dev_info.migratepage = vmballoon_migratepage;
	b->b_dev_info.inode = alloc_anon_inode(vmballoon_mnt->mnt_sb);

	अगर (IS_ERR(b->b_dev_info.inode))
		वापस PTR_ERR(b->b_dev_info.inode);

	b->b_dev_info.inode->i_mapping->a_ops = &balloon_aops;
	वापस 0;
पूर्ण

#अन्यथा /* CONFIG_BALLOON_COMPACTION */

अटल व्योम vmballoon_compaction_deinit(काष्ठा vmballoon *b)
अणु
पूर्ण

अटल पूर्णांक vmballoon_compaction_init(काष्ठा vmballoon *b)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_BALLOON_COMPACTION */

अटल पूर्णांक __init vmballoon_init(व्योम)
अणु
	पूर्णांक error;

	/*
	 * Check अगर we are running on VMware's hypervisor and bail out
	 * अगर we are not.
	 */
	अगर (x86_hyper_type != X86_HYPER_VMWARE)
		वापस -ENODEV;

	INIT_DELAYED_WORK(&balloon.dwork, vmballoon_work);

	error = vmballoon_रेजिस्टर_shrinker(&balloon);
	अगर (error)
		जाओ fail;

	/*
	 * Initialization of compaction must be करोne after the call to
	 * balloon_devinfo_init() .
	 */
	balloon_devinfo_init(&balloon.b_dev_info);
	error = vmballoon_compaction_init(&balloon);
	अगर (error)
		जाओ fail;

	INIT_LIST_HEAD(&balloon.huge_pages);
	spin_lock_init(&balloon.comm_lock);
	init_rwsem(&balloon.conf_sem);
	balloon.vmci_करोorbell = VMCI_INVALID_HANDLE;
	balloon.batch_page = शून्य;
	balloon.page = शून्य;
	balloon.reset_required = true;

	queue_delayed_work(प्रणाली_मुक्तzable_wq, &balloon.dwork, 0);

	vmballoon_debugfs_init(&balloon);

	वापस 0;
fail:
	vmballoon_unरेजिस्टर_shrinker(&balloon);
	vmballoon_compaction_deinit(&balloon);
	वापस error;
पूर्ण

/*
 * Using late_initcall() instead of module_init() allows the balloon to use the
 * VMCI करोorbell even when the balloon is built पूर्णांकo the kernel. Otherwise the
 * VMCI is probed only after the balloon is initialized. If the balloon is used
 * as a module, late_initcall() is equivalent to module_init().
 */
late_initcall(vmballoon_init);

अटल व्योम __निकास vmballoon_निकास(व्योम)
अणु
	vmballoon_unरेजिस्टर_shrinker(&balloon);
	vmballoon_vmci_cleanup(&balloon);
	cancel_delayed_work_sync(&balloon.dwork);

	vmballoon_debugfs_निकास(&balloon);

	/*
	 * Deallocate all reserved memory, and reset connection with monitor.
	 * Reset connection beक्रमe deallocating memory to aव्योम potential क्रम
	 * additional spurious resets from guest touching deallocated pages.
	 */
	vmballoon_send_start(&balloon, 0);
	vmballoon_pop(&balloon);

	/* Only once we popped the balloon, compaction can be deinit */
	vmballoon_compaction_deinit(&balloon);
पूर्ण
module_निकास(vmballoon_निकास);
