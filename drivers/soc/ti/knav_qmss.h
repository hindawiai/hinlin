<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Keystone Navigator QMSS driver पूर्णांकernal header
 *
 * Copyright (C) 2014 Texas Instruments Incorporated - http://www.ti.com
 * Author:	Sandeep Nair <sandeep_n@ti.com>
 *		Cyril Chemparathy <cyril@ti.com>
 *		Santosh Shilimkar <santosh.shilimkar@ti.com>
 */

#अगर_अघोषित __KNAV_QMSS_H__
#घोषणा __KNAV_QMSS_H__

#समावेश <linux/percpu.h>

#घोषणा THRESH_GTE	BIT(7)
#घोषणा THRESH_LT	0

#घोषणा PDSP_CTRL_PC_MASK	0xffff0000
#घोषणा PDSP_CTRL_SOFT_RESET	BIT(0)
#घोषणा PDSP_CTRL_ENABLE	BIT(1)
#घोषणा PDSP_CTRL_RUNNING	BIT(15)

#घोषणा ACC_MAX_CHANNEL		48
#घोषणा ACC_DEFAULT_PERIOD	25 /* usecs */

#घोषणा ACC_CHANNEL_INT_BASE		2

#घोषणा ACC_LIST_ENTRY_TYPE		1
#घोषणा ACC_LIST_ENTRY_WORDS		(1 << ACC_LIST_ENTRY_TYPE)
#घोषणा ACC_LIST_ENTRY_QUEUE_IDX	0
#घोषणा ACC_LIST_ENTRY_DESC_IDX	(ACC_LIST_ENTRY_WORDS - 1)

#घोषणा ACC_CMD_DISABLE_CHANNEL	0x80
#घोषणा ACC_CMD_ENABLE_CHANNEL	0x81
#घोषणा ACC_CFG_MULTI_QUEUE		BIT(21)

#घोषणा ACC_INTD_OFFSET_EOI		(0x0010)
#घोषणा ACC_INTD_OFFSET_COUNT(ch)	(0x0300 + 4 * (ch))
#घोषणा ACC_INTD_OFFSET_STATUS(ch)	(0x0200 + 4 * ((ch) / 32))

#घोषणा RANGE_MAX_IRQS			64

#घोषणा ACC_DESCS_MAX		SZ_1K
#घोषणा ACC_DESCS_MASK		(ACC_DESCS_MAX - 1)
#घोषणा DESC_SIZE_MASK		0xful
#घोषणा DESC_PTR_MASK		(~DESC_SIZE_MASK)

#घोषणा KNAV_NAME_SIZE			32

क्रमागत knav_acc_result अणु
	ACC_RET_IDLE,
	ACC_RET_SUCCESS,
	ACC_RET_INVALID_COMMAND,
	ACC_RET_INVALID_CHANNEL,
	ACC_RET_INACTIVE_CHANNEL,
	ACC_RET_ACTIVE_CHANNEL,
	ACC_RET_INVALID_QUEUE,
	ACC_RET_INVALID_RET,
पूर्ण;

काष्ठा knav_reg_config अणु
	u32		revision;
	u32		__pad1;
	u32		भागert;
	u32		link_ram_base0;
	u32		link_ram_size0;
	u32		link_ram_base1;
	u32		__pad2[2];
	u32		starvation[];
पूर्ण;

काष्ठा knav_reg_region अणु
	u32		base;
	u32		start_index;
	u32		size_count;
	u32		__pad;
पूर्ण;

काष्ठा knav_reg_pdsp_regs अणु
	u32		control;
	u32		status;
	u32		cycle_count;
	u32		stall_count;
पूर्ण;

काष्ठा knav_reg_acc_command अणु
	u32		command;
	u32		queue_mask;
	u32		list_dma;
	u32		queue_num;
	u32		समयr_config;
पूर्ण;

काष्ठा knav_link_ram_block अणु
	dma_addr_t	 dma;
	व्योम		*virt;
	माप_प्रकार		 size;
पूर्ण;

काष्ठा knav_acc_info अणु
	u32			 pdsp_id;
	u32			 start_channel;
	u32			 list_entries;
	u32			 pacing_mode;
	u32			 समयr_count;
	पूर्णांक			 mem_size;
	पूर्णांक			 list_size;
	काष्ठा knav_pdsp_info	*pdsp;
पूर्ण;

काष्ठा knav_acc_channel अणु
	u32			channel;
	u32			list_index;
	u32			खोलो_mask;
	u32			*list_cpu[2];
	dma_addr_t		list_dma[2];
	अक्षर			name[KNAV_NAME_SIZE];
	atomic_t		retrigger_count;
पूर्ण;

काष्ठा knav_pdsp_info अणु
	स्थिर अक्षर					*name;
	काष्ठा knav_reg_pdsp_regs  __iomem		*regs;
	जोड़ अणु
		व्योम __iomem				*command;
		काष्ठा knav_reg_acc_command __iomem	*acc_command;
		u32 __iomem				*qos_command;
	पूर्ण;
	व्योम __iomem					*पूर्णांकd;
	u32 __iomem					*iram;
	u32						id;
	काष्ठा list_head				list;
	bool						loaded;
	bool						started;
पूर्ण;

काष्ठा knav_qmgr_info अणु
	अचिन्हित			start_queue;
	अचिन्हित			num_queues;
	काष्ठा knav_reg_config __iomem	*reg_config;
	काष्ठा knav_reg_region __iomem	*reg_region;
	काष्ठा knav_reg_queue __iomem	*reg_push, *reg_pop, *reg_peek;
	व्योम __iomem			*reg_status;
	काष्ठा list_head		list;
पूर्ण;

#घोषणा KNAV_NUM_LINKRAM	2

/**
 * काष्ठा knav_queue_stats:	queue statistics
 * pushes:			number of push operations
 * pops:			number of pop operations
 * push_errors:			number of push errors
 * pop_errors:			number of pop errors
 * notअगरies:			notअगरier counts
 */
काष्ठा knav_queue_stats अणु
	अचिन्हित पूर्णांक pushes;
	अचिन्हित पूर्णांक pops;
	अचिन्हित पूर्णांक push_errors;
	अचिन्हित पूर्णांक pop_errors;
	अचिन्हित पूर्णांक notअगरies;
पूर्ण;

/**
 * काष्ठा knav_reg_queue:	queue रेजिस्टरs
 * @entry_count:		valid entries in the queue
 * @byte_count:			total byte count in thhe queue
 * @packet_size:		packet size क्रम the queue
 * @ptr_माप_प्रकारhresh:		packet poपूर्णांकer size threshold
 */
काष्ठा knav_reg_queue अणु
	u32		entry_count;
	u32		byte_count;
	u32		packet_size;
	u32		ptr_माप_प्रकारhresh;
पूर्ण;

/**
 * काष्ठा knav_region:		qmss region info
 * @dma_start, dma_end:		start and end dma address
 * @virt_start, virt_end:	start and end भव address
 * @desc_size:			descriptor size
 * @used_desc:			consumed descriptors
 * @id:				region number
 * @num_desc:			total descriptors
 * @link_index:			index of the first descriptor
 * @name:			region name
 * @list:			instance in the device's region list
 * @pools:			list of descriptor pools in the region
 */
काष्ठा knav_region अणु
	dma_addr_t		dma_start, dma_end;
	व्योम			*virt_start, *virt_end;
	अचिन्हित		desc_size;
	अचिन्हित		used_desc;
	अचिन्हित		id;
	अचिन्हित		num_desc;
	अचिन्हित		link_index;
	स्थिर अक्षर		*name;
	काष्ठा list_head	list;
	काष्ठा list_head	pools;
पूर्ण;

/**
 * काष्ठा knav_pool:		qmss pools
 * @dev:			device poपूर्णांकer
 * @region:			qmss region info
 * @queue:			queue रेजिस्टरs
 * @kdev:			qmss device poपूर्णांकer
 * @region_offset:		offset from the base
 * @num_desc:			total descriptors
 * @desc_size:			descriptor size
 * @region_id:			region number
 * @name:			pool name
 * @list:			list head
 * @region_inst:		instance in the region's pool list
 */
काष्ठा knav_pool अणु
	काष्ठा device			*dev;
	काष्ठा knav_region		*region;
	काष्ठा knav_queue		*queue;
	काष्ठा knav_device		*kdev;
	पूर्णांक				region_offset;
	पूर्णांक				num_desc;
	पूर्णांक				desc_size;
	पूर्णांक				region_id;
	स्थिर अक्षर			*name;
	काष्ठा list_head		list;
	काष्ठा list_head		region_inst;
पूर्ण;

/**
 * काष्ठा knav_queue_inst:		qmss queue instance properties
 * @descs:				descriptor poपूर्णांकer
 * @desc_head, desc_tail, desc_count:	descriptor counters
 * @acc:				accumulator channel poपूर्णांकer
 * @kdev:				qmss device poपूर्णांकer
 * @range:				range info
 * @qmgr:				queue manager info
 * @id:					queue instance id
 * @irq_num:				irq line number
 * @notअगरy_needed:			notअगरier needed based on queue type
 * @num_notअगरiers:			total notअगरiers
 * @handles:				list head
 * @name:				queue instance name
 * @irq_name:				irq line name
 */
काष्ठा knav_queue_inst अणु
	u32				*descs;
	atomic_t			desc_head, desc_tail, desc_count;
	काष्ठा knav_acc_channel	*acc;
	काष्ठा knav_device		*kdev;
	काष्ठा knav_range_info		*range;
	काष्ठा knav_qmgr_info		*qmgr;
	u32				id;
	पूर्णांक				irq_num;
	पूर्णांक				notअगरy_needed;
	atomic_t			num_notअगरiers;
	काष्ठा list_head		handles;
	स्थिर अक्षर			*name;
	स्थिर अक्षर			*irq_name;
पूर्ण;

/**
 * काष्ठा knav_queue:			qmss queue properties
 * @reg_push, reg_pop, reg_peek:	push, pop queue रेजिस्टरs
 * @inst:				qmss queue instance properties
 * @notअगरier_fn:			notअगरier function
 * @notअगरier_fn_arg:			notअगरier function argument
 * @notअगरier_enabled:			notier enabled क्रम a give queue
 * @rcu:				rcu head
 * @flags:				queue flags
 * @list:				list head
 */
काष्ठा knav_queue अणु
	काष्ठा knav_reg_queue __iomem	*reg_push, *reg_pop, *reg_peek;
	काष्ठा knav_queue_inst		*inst;
	काष्ठा knav_queue_stats __percpu	*stats;
	knav_queue_notअगरy_fn		notअगरier_fn;
	व्योम				*notअगरier_fn_arg;
	atomic_t			notअगरier_enabled;
	काष्ठा rcu_head			rcu;
	अचिन्हित			flags;
	काष्ठा list_head		list;
पूर्ण;

क्रमागत qmss_version अणु
	QMSS,
	QMSS_66AK2G,
पूर्ण;

काष्ठा knav_device अणु
	काष्ठा device				*dev;
	अचिन्हित				base_id;
	अचिन्हित				num_queues;
	अचिन्हित				num_queues_in_use;
	अचिन्हित				inst_shअगरt;
	काष्ठा knav_link_ram_block		link_rams[KNAV_NUM_LINKRAM];
	व्योम					*instances;
	काष्ठा list_head			regions;
	काष्ठा list_head			queue_ranges;
	काष्ठा list_head			pools;
	काष्ठा list_head			pdsps;
	काष्ठा list_head			qmgrs;
	क्रमागत qmss_version			version;
पूर्ण;

काष्ठा knav_range_ops अणु
	पूर्णांक	(*init_range)(काष्ठा knav_range_info *range);
	पूर्णांक	(*मुक्त_range)(काष्ठा knav_range_info *range);
	पूर्णांक	(*init_queue)(काष्ठा knav_range_info *range,
			      काष्ठा knav_queue_inst *inst);
	पूर्णांक	(*खोलो_queue)(काष्ठा knav_range_info *range,
			      काष्ठा knav_queue_inst *inst, अचिन्हित flags);
	पूर्णांक	(*बंद_queue)(काष्ठा knav_range_info *range,
			       काष्ठा knav_queue_inst *inst);
	पूर्णांक	(*set_notअगरy)(काष्ठा knav_range_info *range,
			      काष्ठा knav_queue_inst *inst, bool enabled);
पूर्ण;

काष्ठा knav_irq_info अणु
	पूर्णांक		irq;
	काष्ठा cpumask	*cpu_mask;
पूर्ण;

काष्ठा knav_range_info अणु
	स्थिर अक्षर			*name;
	काष्ठा knav_device		*kdev;
	अचिन्हित			queue_base;
	अचिन्हित			num_queues;
	व्योम				*queue_base_inst;
	अचिन्हित			flags;
	काष्ठा list_head		list;
	काष्ठा knav_range_ops		*ops;
	काष्ठा knav_acc_info		acc_info;
	काष्ठा knav_acc_channel	*acc;
	अचिन्हित			num_irqs;
	काष्ठा knav_irq_info		irqs[RANGE_MAX_IRQS];
पूर्ण;

#घोषणा RANGE_RESERVED		BIT(0)
#घोषणा RANGE_HAS_IRQ		BIT(1)
#घोषणा RANGE_HAS_ACCUMULATOR	BIT(2)
#घोषणा RANGE_MULTI_QUEUE	BIT(3)

#घोषणा क्रम_each_region(kdev, region)				\
	list_क्रम_each_entry(region, &kdev->regions, list)

#घोषणा first_region(kdev)					\
	list_first_entry_or_null(&kdev->regions, \
				 काष्ठा knav_region, list)

#घोषणा क्रम_each_queue_range(kdev, range)			\
	list_क्रम_each_entry(range, &kdev->queue_ranges, list)

#घोषणा first_queue_range(kdev)					\
	list_first_entry_or_null(&kdev->queue_ranges, \
				 काष्ठा knav_range_info, list)

#घोषणा क्रम_each_pool(kdev, pool)				\
	list_क्रम_each_entry(pool, &kdev->pools, list)

#घोषणा क्रम_each_pdsp(kdev, pdsp)				\
	list_क्रम_each_entry(pdsp, &kdev->pdsps, list)

#घोषणा क्रम_each_qmgr(kdev, qmgr)				\
	list_क्रम_each_entry(qmgr, &kdev->qmgrs, list)

अटल अंतरभूत काष्ठा knav_pdsp_info *
knav_find_pdsp(काष्ठा knav_device *kdev, अचिन्हित pdsp_id)
अणु
	काष्ठा knav_pdsp_info *pdsp;

	क्रम_each_pdsp(kdev, pdsp)
		अगर (pdsp_id == pdsp->id)
			वापस pdsp;
	वापस शून्य;
पूर्ण

बाह्य पूर्णांक knav_init_acc_range(काष्ठा knav_device *kdev,
					काष्ठा device_node *node,
					काष्ठा knav_range_info *range);
बाह्य व्योम knav_queue_notअगरy(काष्ठा knav_queue_inst *inst);

#पूर्ण_अगर /* __KNAV_QMSS_H__ */
