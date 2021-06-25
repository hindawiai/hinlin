<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * SPU core / file प्रणाली पूर्णांकerface and HW काष्ठाures
 *
 * (C) Copyright IBM Deutschland Entwicklung GmbH 2005
 *
 * Author: Arnd Bergmann <arndb@de.ibm.com>
 */

#अगर_अघोषित _SPU_H
#घोषणा _SPU_H
#अगर_घोषित __KERNEL__

#समावेश <linux/workqueue.h>
#समावेश <linux/device.h>
#समावेश <linux/mutex.h>
#समावेश <यंत्र/reg.h>
#समावेश <यंत्र/copro.h>

#घोषणा LS_SIZE (256 * 1024)
#घोषणा LS_ADDR_MASK (LS_SIZE - 1)

#घोषणा MFC_PUT_CMD             0x20
#घोषणा MFC_PUTS_CMD            0x28
#घोषणा MFC_PUTR_CMD            0x30
#घोषणा MFC_PUTF_CMD            0x22
#घोषणा MFC_PUTB_CMD            0x21
#घोषणा MFC_PUTFS_CMD           0x2A
#घोषणा MFC_PUTBS_CMD           0x29
#घोषणा MFC_PUTRF_CMD           0x32
#घोषणा MFC_PUTRB_CMD           0x31
#घोषणा MFC_PUTL_CMD            0x24
#घोषणा MFC_PUTRL_CMD           0x34
#घोषणा MFC_PUTLF_CMD           0x26
#घोषणा MFC_PUTLB_CMD           0x25
#घोषणा MFC_PUTRLF_CMD          0x36
#घोषणा MFC_PUTRLB_CMD          0x35

#घोषणा MFC_GET_CMD             0x40
#घोषणा MFC_GETS_CMD            0x48
#घोषणा MFC_GETF_CMD            0x42
#घोषणा MFC_GETB_CMD            0x41
#घोषणा MFC_GETFS_CMD           0x4A
#घोषणा MFC_GETBS_CMD           0x49
#घोषणा MFC_GETL_CMD            0x44
#घोषणा MFC_GETLF_CMD           0x46
#घोषणा MFC_GETLB_CMD           0x45

#घोषणा MFC_SDCRT_CMD           0x80
#घोषणा MFC_SDCRTST_CMD         0x81
#घोषणा MFC_SDCRZ_CMD           0x89
#घोषणा MFC_SDCRS_CMD           0x8D
#घोषणा MFC_SDCRF_CMD           0x8F

#घोषणा MFC_GETLLAR_CMD         0xD0
#घोषणा MFC_PUTLLC_CMD          0xB4
#घोषणा MFC_PUTLLUC_CMD         0xB0
#घोषणा MFC_PUTQLLUC_CMD        0xB8
#घोषणा MFC_SNDSIG_CMD          0xA0
#घोषणा MFC_SNDSIGB_CMD         0xA1
#घोषणा MFC_SNDSIGF_CMD         0xA2
#घोषणा MFC_BARRIER_CMD         0xC0
#घोषणा MFC_EIEIO_CMD           0xC8
#घोषणा MFC_SYNC_CMD            0xCC

#घोषणा MFC_MIN_DMA_SIZE_SHIFT  4       /* 16 bytes */
#घोषणा MFC_MAX_DMA_SIZE_SHIFT  14      /* 16384 bytes */
#घोषणा MFC_MIN_DMA_SIZE        (1 << MFC_MIN_DMA_SIZE_SHIFT)
#घोषणा MFC_MAX_DMA_SIZE        (1 << MFC_MAX_DMA_SIZE_SHIFT)
#घोषणा MFC_MIN_DMA_SIZE_MASK   (MFC_MIN_DMA_SIZE - 1)
#घोषणा MFC_MAX_DMA_SIZE_MASK   (MFC_MAX_DMA_SIZE - 1)
#घोषणा MFC_MIN_DMA_LIST_SIZE   0x0008  /*   8 bytes */
#घोषणा MFC_MAX_DMA_LIST_SIZE   0x4000  /* 16K bytes */

#घोषणा MFC_TAGID_TO_TAGMASK(tag_id)  (1 << (tag_id & 0x1F))

/* Events क्रम Channels 0-2 */
#घोषणा MFC_DMA_TAG_STATUS_UPDATE_EVENT     0x00000001
#घोषणा MFC_DMA_TAG_CMD_STALL_NOTIFY_EVENT  0x00000002
#घोषणा MFC_DMA_QUEUE_AVAILABLE_EVENT       0x00000008
#घोषणा MFC_SPU_MAILBOX_WRITTEN_EVENT       0x00000010
#घोषणा MFC_DECREMENTER_EVENT               0x00000020
#घोषणा MFC_PU_INT_MAILBOX_AVAILABLE_EVENT  0x00000040
#घोषणा MFC_PU_MAILBOX_AVAILABLE_EVENT      0x00000080
#घोषणा MFC_SIGNAL_2_EVENT                  0x00000100
#घोषणा MFC_SIGNAL_1_EVENT                  0x00000200
#घोषणा MFC_LLR_LOST_EVENT                  0x00000400
#घोषणा MFC_PRIV_ATTN_EVENT                 0x00000800
#घोषणा MFC_MULTI_SRC_EVENT                 0x00001000

/* Flag indicating progress during context चयन. */
#घोषणा SPU_CONTEXT_SWITCH_PENDING	0UL
#घोषणा SPU_CONTEXT_FAULT_PENDING	1UL

काष्ठा spu_context;
काष्ठा spu_runqueue;
काष्ठा spu_lscsa;
काष्ठा device_node;

क्रमागत spu_utilization_state अणु
	SPU_UTIL_USER,
	SPU_UTIL_SYSTEM,
	SPU_UTIL_IOWAIT,
	SPU_UTIL_IDLE_LOADED,
	SPU_UTIL_MAX
पूर्ण;

काष्ठा spu अणु
	स्थिर अक्षर *name;
	अचिन्हित दीर्घ local_store_phys;
	u8 *local_store;
	अचिन्हित दीर्घ problem_phys;
	काष्ठा spu_problem __iomem *problem;
	काष्ठा spu_priv2 __iomem *priv2;
	काष्ठा list_head cbe_list;
	काष्ठा list_head full_list;
	क्रमागत अणु SPU_FREE, SPU_USED पूर्ण alloc_state;
	पूर्णांक number;
	अचिन्हित पूर्णांक irqs[3];
	u32 node;
	अचिन्हित दीर्घ flags;
	u64 class_0_pending;
	u64 class_0_dar;
	u64 class_1_dar;
	u64 class_1_dsisr;
	माप_प्रकार ls_size;
	अचिन्हित पूर्णांक slb_replace;
	काष्ठा mm_काष्ठा *mm;
	काष्ठा spu_context *ctx;
	काष्ठा spu_runqueue *rq;
	अचिन्हित दीर्घ दीर्घ बारtamp;
	pid_t pid;
	pid_t tgid;
	spinlock_t रेजिस्टर_lock;

	व्योम (* wbox_callback)(काष्ठा spu *spu);
	व्योम (* ibox_callback)(काष्ठा spu *spu);
	व्योम (* stop_callback)(काष्ठा spu *spu, पूर्णांक irq);
	व्योम (* mfc_callback)(काष्ठा spu *spu);

	अक्षर irq_c0[8];
	अक्षर irq_c1[8];
	अक्षर irq_c2[8];

	u64 spe_id;

	व्योम* pdata; /* platक्रमm निजी data */

	/* of based platक्रमms only */
	काष्ठा device_node *devnode;

	/* native only */
	काष्ठा spu_priv1 __iomem *priv1;

	/* beat only */
	u64 shaकरोw_पूर्णांक_mask_RW[3];

	काष्ठा device dev;

	पूर्णांक has_mem_affinity;
	काष्ठा list_head aff_list;

	काष्ठा अणु
		/* रक्षित by पूर्णांकerrupt reentrancy */
		क्रमागत spu_utilization_state util_state;
		अचिन्हित दीर्घ दीर्घ tstamp;
		अचिन्हित दीर्घ दीर्घ बार[SPU_UTIL_MAX];
		अचिन्हित दीर्घ दीर्घ vol_ctx_चयन;
		अचिन्हित दीर्घ दीर्घ invol_ctx_चयन;
		अचिन्हित दीर्घ दीर्घ min_flt;
		अचिन्हित दीर्घ दीर्घ maj_flt;
		अचिन्हित दीर्घ दीर्घ hash_flt;
		अचिन्हित दीर्घ दीर्घ slb_flt;
		अचिन्हित दीर्घ दीर्घ class2_पूर्णांकr;
		अचिन्हित दीर्घ दीर्घ libassist;
	पूर्ण stats;
पूर्ण;

काष्ठा cbe_spu_info अणु
	काष्ठा mutex list_mutex;
	काष्ठा list_head spus;
	पूर्णांक n_spus;
	पूर्णांक nr_active;
	atomic_t busy_spus;
	atomic_t reserved_spus;
पूर्ण;

बाह्य काष्ठा cbe_spu_info cbe_spu_info[];

व्योम spu_init_channels(काष्ठा spu *spu);
व्योम spu_irq_setaffinity(काष्ठा spu *spu, पूर्णांक cpu);

व्योम spu_setup_kernel_slbs(काष्ठा spu *spu, काष्ठा spu_lscsa *lscsa,
		व्योम *code, पूर्णांक code_size);

बाह्य व्योम spu_invalidate_slbs(काष्ठा spu *spu);
बाह्य व्योम spu_associate_mm(काष्ठा spu *spu, काष्ठा mm_काष्ठा *mm);
पूर्णांक spu_64k_pages_available(व्योम);

/* Calls from the memory management to the SPU */
काष्ठा mm_काष्ठा;
बाह्य व्योम spu_flush_all_slbs(काष्ठा mm_काष्ठा *mm);

/* प्रणाली callbacks from the SPU */
काष्ठा spu_syscall_block अणु
	u64 nr_ret;
	u64 parm[6];
पूर्ण;
बाह्य दीर्घ spu_sys_callback(काष्ठा spu_syscall_block *s);

/* syscalls implemented in spufs */
काष्ठा file;
काष्ठा coredump_params;
काष्ठा spufs_calls अणु
	दीर्घ (*create_thपढ़ो)(स्थिर अक्षर __user *name,
					अचिन्हित पूर्णांक flags, umode_t mode,
					काष्ठा file *neighbor);
	दीर्घ (*spu_run)(काष्ठा file *filp, __u32 __user *unpc,
						__u32 __user *ustatus);
	पूर्णांक (*coredump_extra_notes_size)(व्योम);
	पूर्णांक (*coredump_extra_notes_ग_लिखो)(काष्ठा coredump_params *cprm);
	व्योम (*notअगरy_spus_active)(व्योम);
	काष्ठा module *owner;
पूर्ण;

/* वापस status from spu_run, same as in libspe */
#घोषणा SPE_EVENT_DMA_ALIGNMENT		0x0008	/*A DMA alignment error */
#घोषणा SPE_EVENT_SPE_ERROR		0x0010	/*An illegal inकाष्ठाion error*/
#घोषणा SPE_EVENT_SPE_DATA_SEGMENT	0x0020	/*A DMA segmentation error    */
#घोषणा SPE_EVENT_SPE_DATA_STORAGE	0x0040	/*A DMA storage error */
#घोषणा SPE_EVENT_INVALID_DMA		0x0800	/* Invalid MFC DMA */

/*
 * Flags क्रम sys_spu_create.
 */
#घोषणा SPU_CREATE_EVENTS_ENABLED	0x0001
#घोषणा SPU_CREATE_GANG			0x0002
#घोषणा SPU_CREATE_NOSCHED		0x0004
#घोषणा SPU_CREATE_ISOLATE		0x0008
#घोषणा SPU_CREATE_AFFINITY_SPU		0x0010
#घोषणा SPU_CREATE_AFFINITY_MEM		0x0020

#घोषणा SPU_CREATE_FLAG_ALL		0x003f /* mask of all valid flags */


पूर्णांक रेजिस्टर_spu_syscalls(काष्ठा spufs_calls *calls);
व्योम unरेजिस्टर_spu_syscalls(काष्ठा spufs_calls *calls);

पूर्णांक spu_add_dev_attr(काष्ठा device_attribute *attr);
व्योम spu_हटाओ_dev_attr(काष्ठा device_attribute *attr);

पूर्णांक spu_add_dev_attr_group(काष्ठा attribute_group *attrs);
व्योम spu_हटाओ_dev_attr_group(काष्ठा attribute_group *attrs);

बाह्य व्योम notअगरy_spus_active(व्योम);
बाह्य व्योम करो_notअगरy_spus_active(व्योम);

/*
 * This defines the Local Store, Problem Area and Privilege Area of an SPU.
 */

जोड़ mfc_tag_size_class_cmd अणु
	काष्ठा अणु
		u16 mfc_size;
		u16 mfc_tag;
		u8  pad;
		u8  mfc_rclassid;
		u16 mfc_cmd;
	पूर्ण u;
	काष्ठा अणु
		u32 mfc_माप_प्रकारag32;
		u32 mfc_class_cmd32;
	पूर्ण by32;
	u64 all64;
पूर्ण;

काष्ठा mfc_cq_sr अणु
	u64 mfc_cq_data0_RW;
	u64 mfc_cq_data1_RW;
	u64 mfc_cq_data2_RW;
	u64 mfc_cq_data3_RW;
पूर्ण;

काष्ठा spu_problem अणु
#घोषणा MS_SYNC_PENDING         1L
	u64 spc_mssync_RW;					/* 0x0000 */
	u8  pad_0x0008_0x3000[0x3000 - 0x0008];

	/* DMA Area */
	u8  pad_0x3000_0x3004[0x4];				/* 0x3000 */
	u32 mfc_lsa_W;						/* 0x3004 */
	u64 mfc_ea_W;						/* 0x3008 */
	जोड़ mfc_tag_size_class_cmd mfc_जोड़_W;			/* 0x3010 */
	u8  pad_0x3018_0x3104[0xec];				/* 0x3018 */
	u32 dma_qstatus_R;					/* 0x3104 */
	u8  pad_0x3108_0x3204[0xfc];				/* 0x3108 */
	u32 dma_querytype_RW;					/* 0x3204 */
	u8  pad_0x3208_0x321c[0x14];				/* 0x3208 */
	u32 dma_querymask_RW;					/* 0x321c */
	u8  pad_0x3220_0x322c[0xc];				/* 0x3220 */
	u32 dma_tagstatus_R;					/* 0x322c */
#घोषणा DMA_TAGSTATUS_INTR_ANY	1u
#घोषणा DMA_TAGSTATUS_INTR_ALL	2u
	u8  pad_0x3230_0x4000[0x4000 - 0x3230]; 		/* 0x3230 */

	/* SPU Control Area */
	u8  pad_0x4000_0x4004[0x4];				/* 0x4000 */
	u32 pu_mb_R;						/* 0x4004 */
	u8  pad_0x4008_0x400c[0x4];				/* 0x4008 */
	u32 spu_mb_W;						/* 0x400c */
	u8  pad_0x4010_0x4014[0x4];				/* 0x4010 */
	u32 mb_stat_R;						/* 0x4014 */
	u8  pad_0x4018_0x401c[0x4];				/* 0x4018 */
	u32 spu_runcntl_RW;					/* 0x401c */
#घोषणा SPU_RUNCNTL_STOP	0L
#घोषणा SPU_RUNCNTL_RUNNABLE	1L
#घोषणा SPU_RUNCNTL_ISOLATE	2L
	u8  pad_0x4020_0x4024[0x4];				/* 0x4020 */
	u32 spu_status_R;					/* 0x4024 */
#घोषणा SPU_STOP_STATUS_SHIFT           16
#घोषणा SPU_STATUS_STOPPED		0x0
#घोषणा SPU_STATUS_RUNNING		0x1
#घोषणा SPU_STATUS_STOPPED_BY_STOP	0x2
#घोषणा SPU_STATUS_STOPPED_BY_HALT	0x4
#घोषणा SPU_STATUS_WAITING_FOR_CHANNEL	0x8
#घोषणा SPU_STATUS_SINGLE_STEP		0x10
#घोषणा SPU_STATUS_INVALID_INSTR        0x20
#घोषणा SPU_STATUS_INVALID_CH           0x40
#घोषणा SPU_STATUS_ISOLATED_STATE       0x80
#घोषणा SPU_STATUS_ISOLATED_LOAD_STATUS 0x200
#घोषणा SPU_STATUS_ISOLATED_EXIT_STATUS 0x400
	u8  pad_0x4028_0x402c[0x4];				/* 0x4028 */
	u32 spu_spe_R;						/* 0x402c */
	u8  pad_0x4030_0x4034[0x4];				/* 0x4030 */
	u32 spu_npc_RW;						/* 0x4034 */
	u8  pad_0x4038_0x14000[0x14000 - 0x4038];		/* 0x4038 */

	/* Signal Notअगरication Area */
	u8  pad_0x14000_0x1400c[0xc];				/* 0x14000 */
	u32 संकेत_notअगरy1;					/* 0x1400c */
	u8  pad_0x14010_0x1c00c[0x7ffc];			/* 0x14010 */
	u32 संकेत_notअगरy2;					/* 0x1c00c */
पूर्ण __attribute__ ((aligned(0x20000)));

/* SPU Privilege 2 State Area */
काष्ठा spu_priv2 अणु
	/* MFC Registers */
	u8  pad_0x0000_0x1100[0x1100 - 0x0000]; 		/* 0x0000 */

	/* SLB Management Registers */
	u8  pad_0x1100_0x1108[0x8];				/* 0x1100 */
	u64 slb_index_W;					/* 0x1108 */
#घोषणा SLB_INDEX_MASK				0x7L
	u64 slb_esid_RW;					/* 0x1110 */
	u64 slb_vsid_RW;					/* 0x1118 */
#घोषणा SLB_VSID_SUPERVISOR_STATE	(0x1ull << 11)
#घोषणा SLB_VSID_SUPERVISOR_STATE_MASK	(0x1ull << 11)
#घोषणा SLB_VSID_PROBLEM_STATE		(0x1ull << 10)
#घोषणा SLB_VSID_PROBLEM_STATE_MASK	(0x1ull << 10)
#घोषणा SLB_VSID_EXECUTE_SEGMENT	(0x1ull << 9)
#घोषणा SLB_VSID_NO_EXECUTE_SEGMENT	(0x1ull << 9)
#घोषणा SLB_VSID_EXECUTE_SEGMENT_MASK	(0x1ull << 9)
#घोषणा SLB_VSID_4K_PAGE		(0x0 << 8)
#घोषणा SLB_VSID_LARGE_PAGE		(0x1ull << 8)
#घोषणा SLB_VSID_PAGE_SIZE_MASK		(0x1ull << 8)
#घोषणा SLB_VSID_CLASS_MASK		(0x1ull << 7)
#घोषणा SLB_VSID_VIRTUAL_PAGE_SIZE_MASK	(0x1ull << 6)
	u64 slb_invalidate_entry_W;				/* 0x1120 */
	u64 slb_invalidate_all_W;				/* 0x1128 */
	u8  pad_0x1130_0x2000[0x2000 - 0x1130]; 		/* 0x1130 */

	/* Context Save / Restore Area */
	काष्ठा mfc_cq_sr spuq[16];				/* 0x2000 */
	काष्ठा mfc_cq_sr puq[8];				/* 0x2200 */
	u8  pad_0x2300_0x3000[0x3000 - 0x2300]; 		/* 0x2300 */

	/* MFC Control */
	u64 mfc_control_RW;					/* 0x3000 */
#घोषणा MFC_CNTL_RESUME_DMA_QUEUE		(0ull << 0)
#घोषणा MFC_CNTL_SUSPEND_DMA_QUEUE		(1ull << 0)
#घोषणा MFC_CNTL_SUSPEND_DMA_QUEUE_MASK		(1ull << 0)
#घोषणा MFC_CNTL_SUSPEND_MASK			(1ull << 4)
#घोषणा MFC_CNTL_NORMAL_DMA_QUEUE_OPERATION	(0ull << 8)
#घोषणा MFC_CNTL_SUSPEND_IN_PROGRESS		(1ull << 8)
#घोषणा MFC_CNTL_SUSPEND_COMPLETE		(3ull << 8)
#घोषणा MFC_CNTL_SUSPEND_DMA_STATUS_MASK	(3ull << 8)
#घोषणा MFC_CNTL_DMA_QUEUES_EMPTY		(1ull << 14)
#घोषणा MFC_CNTL_DMA_QUEUES_EMPTY_MASK		(1ull << 14)
#घोषणा MFC_CNTL_PURGE_DMA_REQUEST		(1ull << 15)
#घोषणा MFC_CNTL_PURGE_DMA_IN_PROGRESS		(1ull << 24)
#घोषणा MFC_CNTL_PURGE_DMA_COMPLETE		(3ull << 24)
#घोषणा MFC_CNTL_PURGE_DMA_STATUS_MASK		(3ull << 24)
#घोषणा MFC_CNTL_RESTART_DMA_COMMAND		(1ull << 32)
#घोषणा MFC_CNTL_DMA_COMMAND_REISSUE_PENDING	(1ull << 32)
#घोषणा MFC_CNTL_DMA_COMMAND_REISSUE_STATUS_MASK (1ull << 32)
#घोषणा MFC_CNTL_MFC_PRIVILEGE_STATE		(2ull << 33)
#घोषणा MFC_CNTL_MFC_PROBLEM_STATE		(3ull << 33)
#घोषणा MFC_CNTL_MFC_KEY_PROTECTION_STATE_MASK	(3ull << 33)
#घोषणा MFC_CNTL_DECREMENTER_HALTED		(1ull << 35)
#घोषणा MFC_CNTL_DECREMENTER_RUNNING		(1ull << 40)
#घोषणा MFC_CNTL_DECREMENTER_STATUS_MASK	(1ull << 40)
	u8  pad_0x3008_0x4000[0x4000 - 0x3008]; 		/* 0x3008 */

	/* Interrupt Mailbox */
	u64 puपूर्णांक_mb_R;						/* 0x4000 */
	u8  pad_0x4008_0x4040[0x4040 - 0x4008]; 		/* 0x4008 */

	/* SPU Control */
	u64 spu_privcntl_RW;					/* 0x4040 */
#घोषणा SPU_PRIVCNTL_MODE_NORMAL		(0x0ull << 0)
#घोषणा SPU_PRIVCNTL_MODE_SINGLE_STEP		(0x1ull << 0)
#घोषणा SPU_PRIVCNTL_MODE_MASK			(0x1ull << 0)
#घोषणा SPU_PRIVCNTL_NO_ATTENTION_EVENT		(0x0ull << 1)
#घोषणा SPU_PRIVCNTL_ATTENTION_EVENT		(0x1ull << 1)
#घोषणा SPU_PRIVCNTL_ATTENTION_EVENT_MASK	(0x1ull << 1)
#घोषणा SPU_PRIVCNT_LOAD_REQUEST_NORMAL		(0x0ull << 2)
#घोषणा SPU_PRIVCNT_LOAD_REQUEST_ENABLE_MASK	(0x1ull << 2)
	u8  pad_0x4048_0x4058[0x10];				/* 0x4048 */
	u64 spu_lslr_RW;					/* 0x4058 */
	u64 spu_chnlcntptr_RW;					/* 0x4060 */
	u64 spu_chnlcnt_RW;					/* 0x4068 */
	u64 spu_chnldata_RW;					/* 0x4070 */
	u64 spu_cfg_RW;						/* 0x4078 */
	u8  pad_0x4080_0x5000[0x5000 - 0x4080]; 		/* 0x4080 */

	/* PV2_ImplRegs: Implementation-specअगरic privileged-state 2 regs */
	u64 spu_pm_trace_tag_status_RW;				/* 0x5000 */
	u64 spu_tag_status_query_RW;				/* 0x5008 */
#घोषणा TAG_STATUS_QUERY_CONDITION_BITS (0x3ull << 32)
#घोषणा TAG_STATUS_QUERY_MASK_BITS (0xffffffffull)
	u64 spu_cmd_buf1_RW;					/* 0x5010 */
#घोषणा SPU_COMMAND_BUFFER_1_LSA_BITS (0x7ffffull << 32)
#घोषणा SPU_COMMAND_BUFFER_1_EAH_BITS (0xffffffffull)
	u64 spu_cmd_buf2_RW;					/* 0x5018 */
#घोषणा SPU_COMMAND_BUFFER_2_EAL_BITS ((0xffffffffull) << 32)
#घोषणा SPU_COMMAND_BUFFER_2_TS_BITS (0xffffull << 16)
#घोषणा SPU_COMMAND_BUFFER_2_TAG_BITS (0x3full)
	u64 spu_atomic_status_RW;				/* 0x5020 */
पूर्ण __attribute__ ((aligned(0x20000)));

/* SPU Privilege 1 State Area */
काष्ठा spu_priv1 अणु
	/* Control and Configuration Area */
	u64 mfc_sr1_RW;						/* 0x000 */
#घोषणा MFC_STATE1_LOCAL_STORAGE_DECODE_MASK	0x01ull
#घोषणा MFC_STATE1_BUS_TLBIE_MASK		0x02ull
#घोषणा MFC_STATE1_REAL_MODE_OFFSET_ENABLE_MASK	0x04ull
#घोषणा MFC_STATE1_PROBLEM_STATE_MASK		0x08ull
#घोषणा MFC_STATE1_RELOCATE_MASK		0x10ull
#घोषणा MFC_STATE1_MASTER_RUN_CONTROL_MASK	0x20ull
#घोषणा MFC_STATE1_TABLE_SEARCH_MASK		0x40ull
	u64 mfc_lpid_RW;					/* 0x008 */
	u64 spu_idr_RW;						/* 0x010 */
	u64 mfc_vr_RO;						/* 0x018 */
#घोषणा MFC_VERSION_BITS		(0xffff << 16)
#घोषणा MFC_REVISION_BITS		(0xffff)
#घोषणा MFC_GET_VERSION_BITS(vr)	(((vr) & MFC_VERSION_BITS) >> 16)
#घोषणा MFC_GET_REVISION_BITS(vr)	((vr) & MFC_REVISION_BITS)
	u64 spu_vr_RO;						/* 0x020 */
#घोषणा SPU_VERSION_BITS		(0xffff << 16)
#घोषणा SPU_REVISION_BITS		(0xffff)
#घोषणा SPU_GET_VERSION_BITS(vr)	(vr & SPU_VERSION_BITS) >> 16
#घोषणा SPU_GET_REVISION_BITS(vr)	(vr & SPU_REVISION_BITS)
	u8  pad_0x28_0x100[0x100 - 0x28];			/* 0x28 */

	/* Interrupt Area */
	u64 पूर्णांक_mask_RW[3];					/* 0x100 */
#घोषणा CLASS0_ENABLE_DMA_ALIGNMENT_INTR		0x1L
#घोषणा CLASS0_ENABLE_INVALID_DMA_COMMAND_INTR		0x2L
#घोषणा CLASS0_ENABLE_SPU_ERROR_INTR			0x4L
#घोषणा CLASS0_ENABLE_MFC_FIR_INTR			0x8L
#घोषणा CLASS1_ENABLE_SEGMENT_FAULT_INTR		0x1L
#घोषणा CLASS1_ENABLE_STORAGE_FAULT_INTR		0x2L
#घोषणा CLASS1_ENABLE_LS_COMPARE_SUSPEND_ON_GET_INTR	0x4L
#घोषणा CLASS1_ENABLE_LS_COMPARE_SUSPEND_ON_PUT_INTR	0x8L
#घोषणा CLASS2_ENABLE_MAILBOX_INTR			0x1L
#घोषणा CLASS2_ENABLE_SPU_STOP_INTR			0x2L
#घोषणा CLASS2_ENABLE_SPU_HALT_INTR			0x4L
#घोषणा CLASS2_ENABLE_SPU_DMA_TAG_GROUP_COMPLETE_INTR	0x8L
#घोषणा CLASS2_ENABLE_MAILBOX_THRESHOLD_INTR		0x10L
	u8  pad_0x118_0x140[0x28];				/* 0x118 */
	u64 पूर्णांक_stat_RW[3];					/* 0x140 */
#घोषणा CLASS0_DMA_ALIGNMENT_INTR			0x1L
#घोषणा CLASS0_INVALID_DMA_COMMAND_INTR			0x2L
#घोषणा CLASS0_SPU_ERROR_INTR				0x4L
#घोषणा CLASS0_INTR_MASK				0x7L
#घोषणा CLASS1_SEGMENT_FAULT_INTR			0x1L
#घोषणा CLASS1_STORAGE_FAULT_INTR			0x2L
#घोषणा CLASS1_LS_COMPARE_SUSPEND_ON_GET_INTR		0x4L
#घोषणा CLASS1_LS_COMPARE_SUSPEND_ON_PUT_INTR		0x8L
#घोषणा CLASS1_INTR_MASK				0xfL
#घोषणा CLASS2_MAILBOX_INTR				0x1L
#घोषणा CLASS2_SPU_STOP_INTR				0x2L
#घोषणा CLASS2_SPU_HALT_INTR				0x4L
#घोषणा CLASS2_SPU_DMA_TAG_GROUP_COMPLETE_INTR		0x8L
#घोषणा CLASS2_MAILBOX_THRESHOLD_INTR			0x10L
#घोषणा CLASS2_INTR_MASK				0x1fL
	u8  pad_0x158_0x180[0x28];				/* 0x158 */
	u64 पूर्णांक_route_RW;					/* 0x180 */

	/* Interrupt Routing */
	u8  pad_0x188_0x200[0x200 - 0x188];			/* 0x188 */

	/* Atomic Unit Control Area */
	u64 mfc_atomic_flush_RW;				/* 0x200 */
#घोषणा mfc_atomic_flush_enable			0x1L
	u8  pad_0x208_0x280[0x78];				/* 0x208 */
	u64 resource_allocation_groupID_RW;			/* 0x280 */
	u64 resource_allocation_enable_RW; 			/* 0x288 */
	u8  pad_0x290_0x3c8[0x3c8 - 0x290];			/* 0x290 */

	/* SPU_Cache_ImplRegs: Implementation-dependent cache रेजिस्टरs */

	u64 smf_sbi_संकेत_sel;					/* 0x3c8 */
#घोषणा smf_sbi_mask_lsb	56
#घोषणा smf_sbi_shअगरt		(63 - smf_sbi_mask_lsb)
#घोषणा smf_sbi_mask		(0x301LL << smf_sbi_shअगरt)
#घोषणा smf_sbi_bus0_bits	(0x001LL << smf_sbi_shअगरt)
#घोषणा smf_sbi_bus2_bits	(0x100LL << smf_sbi_shअगरt)
#घोषणा smf_sbi2_bus0_bits	(0x201LL << smf_sbi_shअगरt)
#घोषणा smf_sbi2_bus2_bits	(0x300LL << smf_sbi_shअगरt)
	u64 smf_ato_संकेत_sel;					/* 0x3d0 */
#घोषणा smf_ato_mask_lsb	35
#घोषणा smf_ato_shअगरt		(63 - smf_ato_mask_lsb)
#घोषणा smf_ato_mask		(0x3LL << smf_ato_shअगरt)
#घोषणा smf_ato_bus0_bits	(0x2LL << smf_ato_shअगरt)
#घोषणा smf_ato_bus2_bits	(0x1LL << smf_ato_shअगरt)
	u8  pad_0x3d8_0x400[0x400 - 0x3d8];			/* 0x3d8 */

	/* TLB Management Registers */
	u64 mfc_sdr_RW;						/* 0x400 */
	u8  pad_0x408_0x500[0xf8];				/* 0x408 */
	u64 tlb_index_hपूर्णांक_RO;					/* 0x500 */
	u64 tlb_index_W;					/* 0x508 */
	u64 tlb_vpn_RW;						/* 0x510 */
	u64 tlb_rpn_RW;						/* 0x518 */
	u8  pad_0x520_0x540[0x20];				/* 0x520 */
	u64 tlb_invalidate_entry_W;				/* 0x540 */
	u64 tlb_invalidate_all_W;				/* 0x548 */
	u8  pad_0x550_0x580[0x580 - 0x550];			/* 0x550 */

	/* SPU_MMU_ImplRegs: Implementation-dependent MMU रेजिस्टरs */
	u64 smm_hid;						/* 0x580 */
#घोषणा PAGE_SIZE_MASK		0xf000000000000000ull
#घोषणा PAGE_SIZE_16MB_64KB	0x2000000000000000ull
	u8  pad_0x588_0x600[0x600 - 0x588];			/* 0x588 */

	/* MFC Status/Control Area */
	u64 mfc_accr_RW;					/* 0x600 */
#घोषणा MFC_ACCR_EA_ACCESS_GET		(1 << 0)
#घोषणा MFC_ACCR_EA_ACCESS_PUT		(1 << 1)
#घोषणा MFC_ACCR_LS_ACCESS_GET		(1 << 3)
#घोषणा MFC_ACCR_LS_ACCESS_PUT		(1 << 4)
	u8  pad_0x608_0x610[0x8];				/* 0x608 */
	u64 mfc_dsisr_RW;					/* 0x610 */
#घोषणा MFC_DSISR_PTE_NOT_FOUND		(1 << 30)
#घोषणा MFC_DSISR_ACCESS_DENIED		(1 << 27)
#घोषणा MFC_DSISR_ATOMIC		(1 << 26)
#घोषणा MFC_DSISR_ACCESS_PUT		(1 << 25)
#घोषणा MFC_DSISR_ADDR_MATCH		(1 << 22)
#घोषणा MFC_DSISR_LS			(1 << 17)
#घोषणा MFC_DSISR_L			(1 << 16)
#घोषणा MFC_DSISR_ADDRESS_OVERFLOW	(1 << 0)
	u8  pad_0x618_0x620[0x8];				/* 0x618 */
	u64 mfc_dar_RW;						/* 0x620 */
	u8  pad_0x628_0x700[0x700 - 0x628];			/* 0x628 */

	/* Replacement Management Table (RMT) Area */
	u64 rmt_index_RW;					/* 0x700 */
	u8  pad_0x708_0x710[0x8];				/* 0x708 */
	u64 rmt_data1_RW;					/* 0x710 */
	u8  pad_0x718_0x800[0x800 - 0x718];			/* 0x718 */

	/* Control/Configuration Registers */
	u64 mfc_dsir_R;						/* 0x800 */
#घोषणा MFC_DSIR_Q			(1 << 31)
#घोषणा MFC_DSIR_SPU_QUEUE		MFC_DSIR_Q
	u64 mfc_lsacr_RW;					/* 0x808 */
#घोषणा MFC_LSACR_COMPARE_MASK		((~0ull) << 32)
#घोषणा MFC_LSACR_COMPARE_ADDR		((~0ull) >> 32)
	u64 mfc_lscrr_R;					/* 0x810 */
#घोषणा MFC_LSCRR_Q			(1 << 31)
#घोषणा MFC_LSCRR_SPU_QUEUE		MFC_LSCRR_Q
#घोषणा MFC_LSCRR_QI_SHIFT		32
#घोषणा MFC_LSCRR_QI_MASK		((~0ull) << MFC_LSCRR_QI_SHIFT)
	u8  pad_0x818_0x820[0x8];				/* 0x818 */
	u64 mfc_tclass_id_RW;					/* 0x820 */
#घोषणा MFC_TCLASS_ID_ENABLE		(1L << 0L)
#घोषणा MFC_TCLASS_SLOT2_ENABLE		(1L << 5L)
#घोषणा MFC_TCLASS_SLOT1_ENABLE		(1L << 6L)
#घोषणा MFC_TCLASS_SLOT0_ENABLE		(1L << 7L)
#घोषणा MFC_TCLASS_QUOTA_2_SHIFT	8L
#घोषणा MFC_TCLASS_QUOTA_1_SHIFT	16L
#घोषणा MFC_TCLASS_QUOTA_0_SHIFT	24L
#घोषणा MFC_TCLASS_QUOTA_2_MASK		(0x1FL << MFC_TCLASS_QUOTA_2_SHIFT)
#घोषणा MFC_TCLASS_QUOTA_1_MASK		(0x1FL << MFC_TCLASS_QUOTA_1_SHIFT)
#घोषणा MFC_TCLASS_QUOTA_0_MASK		(0x1FL << MFC_TCLASS_QUOTA_0_SHIFT)
	u8  pad_0x828_0x900[0x900 - 0x828];			/* 0x828 */

	/* Real Mode Support Registers */
	u64 mfc_rm_boundary;					/* 0x900 */
	u8  pad_0x908_0x938[0x30];				/* 0x908 */
	u64 smf_dma_संकेत_sel;					/* 0x938 */
#घोषणा mfc_dma1_mask_lsb	41
#घोषणा mfc_dma1_shअगरt		(63 - mfc_dma1_mask_lsb)
#घोषणा mfc_dma1_mask		(0x3LL << mfc_dma1_shअगरt)
#घोषणा mfc_dma1_bits		(0x1LL << mfc_dma1_shअगरt)
#घोषणा mfc_dma2_mask_lsb	43
#घोषणा mfc_dma2_shअगरt		(63 - mfc_dma2_mask_lsb)
#घोषणा mfc_dma2_mask		(0x3LL << mfc_dma2_shअगरt)
#घोषणा mfc_dma2_bits		(0x1LL << mfc_dma2_shअगरt)
	u8  pad_0x940_0xa38[0xf8];				/* 0x940 */
	u64 smm_संकेत_sel;					/* 0xa38 */
#घोषणा smm_sig_mask_lsb	12
#घोषणा smm_sig_shअगरt		(63 - smm_sig_mask_lsb)
#घोषणा smm_sig_mask		(0x3LL << smm_sig_shअगरt)
#घोषणा smm_sig_bus0_bits	(0x2LL << smm_sig_shअगरt)
#घोषणा smm_sig_bus2_bits	(0x1LL << smm_sig_shअगरt)
	u8  pad_0xa40_0xc00[0xc00 - 0xa40];			/* 0xa40 */

	/* DMA Command Error Area */
	u64 mfc_cer_R;						/* 0xc00 */
#घोषणा MFC_CER_Q		(1 << 31)
#घोषणा MFC_CER_SPU_QUEUE	MFC_CER_Q
	u8  pad_0xc08_0x1000[0x1000 - 0xc08];			/* 0xc08 */

	/* PV1_ImplRegs: Implementation-dependent privileged-state 1 regs */
	/* DMA Command Error Area */
	u64 spu_ecc_cntl_RW;					/* 0x1000 */
#घोषणा SPU_ECC_CNTL_E			(1ull << 0ull)
#घोषणा SPU_ECC_CNTL_ENABLE		SPU_ECC_CNTL_E
#घोषणा SPU_ECC_CNTL_DISABLE		(~SPU_ECC_CNTL_E & 1L)
#घोषणा SPU_ECC_CNTL_S			(1ull << 1ull)
#घोषणा SPU_ECC_STOP_AFTER_ERROR	SPU_ECC_CNTL_S
#घोषणा SPU_ECC_CONTINUE_AFTER_ERROR	(~SPU_ECC_CNTL_S & 2L)
#घोषणा SPU_ECC_CNTL_B			(1ull << 2ull)
#घोषणा SPU_ECC_BACKGROUND_ENABLE	SPU_ECC_CNTL_B
#घोषणा SPU_ECC_BACKGROUND_DISABLE	(~SPU_ECC_CNTL_B & 4L)
#घोषणा SPU_ECC_CNTL_I_SHIFT		3ull
#घोषणा SPU_ECC_CNTL_I_MASK		(3ull << SPU_ECC_CNTL_I_SHIFT)
#घोषणा SPU_ECC_WRITE_ALWAYS		(~SPU_ECC_CNTL_I & 12L)
#घोषणा SPU_ECC_WRITE_CORRECTABLE	(1ull << SPU_ECC_CNTL_I_SHIFT)
#घोषणा SPU_ECC_WRITE_UNCORRECTABLE	(3ull << SPU_ECC_CNTL_I_SHIFT)
#घोषणा SPU_ECC_CNTL_D			(1ull << 5ull)
#घोषणा SPU_ECC_DETECTION_ENABLE	SPU_ECC_CNTL_D
#घोषणा SPU_ECC_DETECTION_DISABLE	(~SPU_ECC_CNTL_D & 32L)
	u64 spu_ecc_stat_RW;					/* 0x1008 */
#घोषणा SPU_ECC_CORRECTED_ERROR		(1ull << 0ul)
#घोषणा SPU_ECC_UNCORRECTED_ERROR	(1ull << 1ul)
#घोषणा SPU_ECC_SCRUB_COMPLETE		(1ull << 2ul)
#घोषणा SPU_ECC_SCRUB_IN_PROGRESS	(1ull << 3ul)
#घोषणा SPU_ECC_INSTRUCTION_ERROR	(1ull << 4ul)
#घोषणा SPU_ECC_DATA_ERROR		(1ull << 5ul)
#घोषणा SPU_ECC_DMA_ERROR		(1ull << 6ul)
#घोषणा SPU_ECC_STATUS_CNT_MASK		(256ull << 8)
	u64 spu_ecc_addr_RW;					/* 0x1010 */
	u64 spu_err_mask_RW;					/* 0x1018 */
#घोषणा SPU_ERR_ILLEGAL_INSTR		(1ull << 0ul)
#घोषणा SPU_ERR_ILLEGAL_CHANNEL		(1ull << 1ul)
	u8  pad_0x1020_0x1028[0x1028 - 0x1020];			/* 0x1020 */

	/* SPU Debug-Trace Bus (DTB) Selection Registers */
	u64 spu_trig0_sel;					/* 0x1028 */
	u64 spu_trig1_sel;					/* 0x1030 */
	u64 spu_trig2_sel;					/* 0x1038 */
	u64 spu_trig3_sel;					/* 0x1040 */
	u64 spu_trace_sel;					/* 0x1048 */
#घोषणा spu_trace_sel_mask		0x1f1fLL
#घोषणा spu_trace_sel_bus0_bits		0x1000LL
#घोषणा spu_trace_sel_bus2_bits		0x0010LL
	u64 spu_event0_sel;					/* 0x1050 */
	u64 spu_event1_sel;					/* 0x1058 */
	u64 spu_event2_sel;					/* 0x1060 */
	u64 spu_event3_sel;					/* 0x1068 */
	u64 spu_trace_cntl;					/* 0x1070 */
पूर्ण __attribute__ ((aligned(0x2000)));

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर
