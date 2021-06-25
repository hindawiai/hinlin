<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright 2018 Marty E. Plummer <hanetzer@starपंचांगail.com> */
/* Copyright 2019 Linaro, Ltd, Rob Herring <robh@kernel.org> */
/*
 * Register definitions based on mali_midg_regmap.h
 * (C) COPYRIGHT 2010-2018 ARM Limited. All rights reserved.
 */
#अगर_अघोषित __PANFROST_REGS_H__
#घोषणा __PANFROST_REGS_H__

#घोषणा GPU_ID				0x00
#घोषणा GPU_L2_FEATURES			0x004	/* (RO) Level 2 cache features */
#घोषणा GPU_CORE_FEATURES		0x008	/* (RO) Shader Core Features */
#घोषणा GPU_TILER_FEATURES		0x00C	/* (RO) Tiler Features */
#घोषणा GPU_MEM_FEATURES		0x010	/* (RO) Memory प्रणाली features */
#घोषणा   GROUPS_L2_COHERENT		BIT(0)	/* Cores groups are l2 coherent */

#घोषणा GPU_MMU_FEATURES		0x014	/* (RO) MMU features */
#घोषणा GPU_AS_PRESENT			0x018	/* (RO) Address space slots present */
#घोषणा GPU_JS_PRESENT			0x01C	/* (RO) Job slots present */

#घोषणा GPU_INT_RAWSTAT			0x20
#घोषणा GPU_INT_CLEAR			0x24
#घोषणा GPU_INT_MASK			0x28
#घोषणा GPU_INT_STAT			0x2c
#घोषणा   GPU_IRQ_FAULT			BIT(0)
#घोषणा   GPU_IRQ_MULTIPLE_FAULT	BIT(7)
#घोषणा   GPU_IRQ_RESET_COMPLETED	BIT(8)
#घोषणा   GPU_IRQ_POWER_CHANGED		BIT(9)
#घोषणा   GPU_IRQ_POWER_CHANGED_ALL	BIT(10)
#घोषणा   GPU_IRQ_PERFCNT_SAMPLE_COMPLETED BIT(16)
#घोषणा   GPU_IRQ_CLEAN_CACHES_COMPLETED BIT(17)
#घोषणा   GPU_IRQ_MASK_ALL			 \
	  (GPU_IRQ_FAULT			|\
	   GPU_IRQ_MULTIPLE_FAULT		|\
	   GPU_IRQ_RESET_COMPLETED		|\
	   GPU_IRQ_POWER_CHANGED		|\
	   GPU_IRQ_POWER_CHANGED_ALL		|\
	   GPU_IRQ_PERFCNT_SAMPLE_COMPLETED	|\
	   GPU_IRQ_CLEAN_CACHES_COMPLETED)
#घोषणा GPU_IRQ_MASK_ERROR	   		\
	(					\
	 GPU_IRQ_FAULT				|\
	 GPU_IRQ_MULTIPLE_FAULT)
#घोषणा GPU_CMD				0x30
#घोषणा   GPU_CMD_SOFT_RESET		0x01
#घोषणा   GPU_CMD_PERFCNT_CLEAR		0x03
#घोषणा   GPU_CMD_PERFCNT_SAMPLE	0x04
#घोषणा   GPU_CMD_CLEAN_CACHES		0x07
#घोषणा   GPU_CMD_CLEAN_INV_CACHES	0x08
#घोषणा GPU_STATUS			0x34
#घोषणा   GPU_STATUS_PRFCNT_ACTIVE	BIT(2)
#घोषणा GPU_LATEST_FLUSH_ID		0x38
#घोषणा GPU_PWR_KEY			0x50	/* (WO) Power manager key रेजिस्टर */
#घोषणा  GPU_PWR_KEY_UNLOCK		0x2968A819
#घोषणा GPU_PWR_OVERRIDE0		0x54	/* (RW) Power manager override settings */
#घोषणा GPU_PWR_OVERRIDE1		0x58	/* (RW) Power manager override settings */
#घोषणा GPU_FAULT_STATUS		0x3C
#घोषणा GPU_FAULT_ADDRESS_LO		0x40
#घोषणा GPU_FAULT_ADDRESS_HI		0x44

#घोषणा GPU_PERFCNT_BASE_LO		0x60
#घोषणा GPU_PERFCNT_BASE_HI		0x64
#घोषणा GPU_PERFCNT_CFG			0x68
#घोषणा   GPU_PERFCNT_CFG_MODE(x)	(x)
#घोषणा   GPU_PERFCNT_CFG_MODE_OFF	0
#घोषणा   GPU_PERFCNT_CFG_MODE_MANUAL	1
#घोषणा   GPU_PERFCNT_CFG_MODE_TILE	2
#घोषणा   GPU_PERFCNT_CFG_AS(x)		((x) << 4)
#घोषणा   GPU_PERFCNT_CFG_SETSEL(x)	((x) << 8)
#घोषणा GPU_PRFCNT_JM_EN		0x6c
#घोषणा GPU_PRFCNT_SHADER_EN		0x70
#घोषणा GPU_PRFCNT_TILER_EN		0x74
#घोषणा GPU_PRFCNT_MMU_L2_EN		0x7c

#घोषणा GPU_THREAD_MAX_THREADS		0x0A0	/* (RO) Maximum number of thपढ़ोs per core */
#घोषणा GPU_THREAD_MAX_WORKGROUP_SIZE	0x0A4	/* (RO) Maximum workgroup size */
#घोषणा GPU_THREAD_MAX_BARRIER_SIZE	0x0A8	/* (RO) Maximum thपढ़ोs रुकोing at a barrier */
#घोषणा GPU_THREAD_FEATURES		0x0AC	/* (RO) Thपढ़ो features */
#घोषणा GPU_THREAD_TLS_ALLOC		0x310   /* (RO) Number of thपढ़ोs per core that
						 * TLS must be allocated क्रम */

#घोषणा GPU_TEXTURE_FEATURES(n)		(0x0B0 + ((n) * 4))
#घोषणा GPU_JS_FEATURES(n)		(0x0C0 + ((n) * 4))

#घोषणा GPU_SHADER_PRESENT_LO		0x100	/* (RO) Shader core present biपंचांगap, low word */
#घोषणा GPU_SHADER_PRESENT_HI		0x104	/* (RO) Shader core present biपंचांगap, high word */
#घोषणा GPU_TILER_PRESENT_LO		0x110	/* (RO) Tiler core present biपंचांगap, low word */
#घोषणा GPU_TILER_PRESENT_HI		0x114	/* (RO) Tiler core present biपंचांगap, high word */

#घोषणा GPU_L2_PRESENT_LO		0x120	/* (RO) Level 2 cache present biपंचांगap, low word */
#घोषणा GPU_L2_PRESENT_HI		0x124	/* (RO) Level 2 cache present biपंचांगap, high word */

#घोषणा GPU_COHERENCY_FEATURES		0x300	/* (RO) Coherency features present */
#घोषणा   COHERENCY_ACE_LITE		BIT(0)
#घोषणा   COHERENCY_ACE			BIT(1)

#घोषणा GPU_STACK_PRESENT_LO		0xE00   /* (RO) Core stack present biपंचांगap, low word */
#घोषणा GPU_STACK_PRESENT_HI		0xE04   /* (RO) Core stack present biपंचांगap, high word */

#घोषणा SHADER_READY_LO			0x140	/* (RO) Shader core पढ़ोy biपंचांगap, low word */
#घोषणा SHADER_READY_HI			0x144	/* (RO) Shader core पढ़ोy biपंचांगap, high word */

#घोषणा TILER_READY_LO			0x150	/* (RO) Tiler core पढ़ोy biपंचांगap, low word */
#घोषणा TILER_READY_HI			0x154	/* (RO) Tiler core पढ़ोy biपंचांगap, high word */

#घोषणा L2_READY_LO			0x160	/* (RO) Level 2 cache पढ़ोy biपंचांगap, low word */
#घोषणा L2_READY_HI			0x164	/* (RO) Level 2 cache पढ़ोy biपंचांगap, high word */

#घोषणा STACK_READY_LO			0xE10   /* (RO) Core stack पढ़ोy biपंचांगap, low word */
#घोषणा STACK_READY_HI			0xE14   /* (RO) Core stack पढ़ोy biपंचांगap, high word */


#घोषणा SHADER_PWRON_LO			0x180	/* (WO) Shader core घातer on biपंचांगap, low word */
#घोषणा SHADER_PWRON_HI			0x184	/* (WO) Shader core घातer on biपंचांगap, high word */

#घोषणा TILER_PWRON_LO			0x190	/* (WO) Tiler core घातer on biपंचांगap, low word */
#घोषणा TILER_PWRON_HI			0x194	/* (WO) Tiler core घातer on biपंचांगap, high word */

#घोषणा L2_PWRON_LO			0x1A0	/* (WO) Level 2 cache घातer on biपंचांगap, low word */
#घोषणा L2_PWRON_HI			0x1A4	/* (WO) Level 2 cache घातer on biपंचांगap, high word */

#घोषणा STACK_PWRON_LO			0xE20   /* (RO) Core stack घातer on biपंचांगap, low word */
#घोषणा STACK_PWRON_HI			0xE24   /* (RO) Core stack घातer on biपंचांगap, high word */


#घोषणा SHADER_PWROFF_LO		0x1C0	/* (WO) Shader core घातer off biपंचांगap, low word */
#घोषणा SHADER_PWROFF_HI		0x1C4	/* (WO) Shader core घातer off biपंचांगap, high word */

#घोषणा TILER_PWROFF_LO			0x1D0	/* (WO) Tiler core घातer off biपंचांगap, low word */
#घोषणा TILER_PWROFF_HI			0x1D4	/* (WO) Tiler core घातer off biपंचांगap, high word */

#घोषणा L2_PWROFF_LO			0x1E0	/* (WO) Level 2 cache घातer off biपंचांगap, low word */
#घोषणा L2_PWROFF_HI			0x1E4	/* (WO) Level 2 cache घातer off biपंचांगap, high word */

#घोषणा STACK_PWROFF_LO			0xE30   /* (RO) Core stack घातer off biपंचांगap, low word */
#घोषणा STACK_PWROFF_HI			0xE34   /* (RO) Core stack घातer off biपंचांगap, high word */


#घोषणा SHADER_PWRTRANS_LO		0x200	/* (RO) Shader core घातer transition biपंचांगap, low word */
#घोषणा SHADER_PWRTRANS_HI		0x204	/* (RO) Shader core घातer transition biपंचांगap, high word */

#घोषणा TILER_PWRTRANS_LO		0x210	/* (RO) Tiler core घातer transition biपंचांगap, low word */
#घोषणा TILER_PWRTRANS_HI		0x214	/* (RO) Tiler core घातer transition biपंचांगap, high word */

#घोषणा L2_PWRTRANS_LO			0x220	/* (RO) Level 2 cache घातer transition biपंचांगap, low word */
#घोषणा L2_PWRTRANS_HI			0x224	/* (RO) Level 2 cache घातer transition biपंचांगap, high word */

#घोषणा STACK_PWRTRANS_LO		0xE40   /* (RO) Core stack घातer transition biपंचांगap, low word */
#घोषणा STACK_PWRTRANS_HI		0xE44   /* (RO) Core stack घातer transition biपंचांगap, high word */


#घोषणा SHADER_PWRACTIVE_LO		0x240	/* (RO) Shader core active biपंचांगap, low word */
#घोषणा SHADER_PWRACTIVE_HI		0x244	/* (RO) Shader core active biपंचांगap, high word */

#घोषणा TILER_PWRACTIVE_LO		0x250	/* (RO) Tiler core active biपंचांगap, low word */
#घोषणा TILER_PWRACTIVE_HI		0x254	/* (RO) Tiler core active biपंचांगap, high word */

#घोषणा L2_PWRACTIVE_LO			0x260	/* (RO) Level 2 cache active biपंचांगap, low word */
#घोषणा L2_PWRACTIVE_HI			0x264	/* (RO) Level 2 cache active biपंचांगap, high word */

#घोषणा GPU_JM_CONFIG			0xF00   /* (RW) Job Manager configuration रेजिस्टर (Implementation specअगरic रेजिस्टर) */
#घोषणा GPU_SHADER_CONFIG		0xF04	/* (RW) Shader core configuration settings (Implementation specअगरic रेजिस्टर) */
#घोषणा GPU_TILER_CONFIG		0xF08   /* (RW) Tiler core configuration settings (Implementation specअगरic रेजिस्टर) */
#घोषणा GPU_L2_MMU_CONFIG		0xF0C	/* (RW) Configuration of the L2 cache and MMU (Implementation specअगरic रेजिस्टर) */

/* L2_MMU_CONFIG रेजिस्टर */
#घोषणा L2_MMU_CONFIG_ALLOW_SNOOP_DISPARITY_SHIFT	23
#घोषणा L2_MMU_CONFIG_ALLOW_SNOOP_DISPARITY		(0x1 << L2_MMU_CONFIG_ALLOW_SNOOP_DISPARITY_SHIFT)
#घोषणा L2_MMU_CONFIG_LIMIT_EXTERNAL_READS_SHIFT	24
#घोषणा L2_MMU_CONFIG_LIMIT_EXTERNAL_READS		(0x3 << L2_MMU_CONFIG_LIMIT_EXTERNAL_READS_SHIFT)
#घोषणा L2_MMU_CONFIG_LIMIT_EXTERNAL_READS_OCTANT	(0x1 << L2_MMU_CONFIG_LIMIT_EXTERNAL_READS_SHIFT)
#घोषणा L2_MMU_CONFIG_LIMIT_EXTERNAL_READS_QUARTER	(0x2 << L2_MMU_CONFIG_LIMIT_EXTERNAL_READS_SHIFT)
#घोषणा L2_MMU_CONFIG_LIMIT_EXTERNAL_READS_HALF		(0x3 << L2_MMU_CONFIG_LIMIT_EXTERNAL_READS_SHIFT)

#घोषणा L2_MMU_CONFIG_LIMIT_EXTERNAL_WRITES_SHIFT	26
#घोषणा L2_MMU_CONFIG_LIMIT_EXTERNAL_WRITES		(0x3 << L2_MMU_CONFIG_LIMIT_EXTERNAL_WRITES_SHIFT)
#घोषणा L2_MMU_CONFIG_LIMIT_EXTERNAL_WRITES_OCTANT	(0x1 << L2_MMU_CONFIG_LIMIT_EXTERNAL_WRITES_SHIFT)
#घोषणा L2_MMU_CONFIG_LIMIT_EXTERNAL_WRITES_QUARTER	(0x2 << L2_MMU_CONFIG_LIMIT_EXTERNAL_WRITES_SHIFT)
#घोषणा L2_MMU_CONFIG_LIMIT_EXTERNAL_WRITES_HALF	(0x3 << L2_MMU_CONFIG_LIMIT_EXTERNAL_WRITES_SHIFT)

#घोषणा L2_MMU_CONFIG_3BIT_LIMIT_EXTERNAL_READS_SHIFT	12
#घोषणा L2_MMU_CONFIG_3BIT_LIMIT_EXTERNAL_READS		(0x7 << L2_MMU_CONFIG_LIMIT_EXTERNAL_READS_SHIFT)

#घोषणा L2_MMU_CONFIG_3BIT_LIMIT_EXTERNAL_WRITES_SHIFT	15
#घोषणा L2_MMU_CONFIG_3BIT_LIMIT_EXTERNAL_WRITES	(0x7 << L2_MMU_CONFIG_LIMIT_EXTERNAL_WRITES_SHIFT)

/* SHADER_CONFIG रेजिस्टर */
#घोषणा SC_ALT_COUNTERS			BIT(3)
#घोषणा SC_OVERRIDE_FWD_PIXEL_KILL	BIT(4)
#घोषणा SC_SDC_DISABLE_OQ_DISCARD	BIT(6)
#घोषणा SC_LS_ALLOW_ATTR_TYPES		BIT(16)
#घोषणा SC_LS_PAUSEBUFFER_DISABLE	BIT(16)
#घोषणा SC_TLS_HASH_ENABLE		BIT(17)
#घोषणा SC_LS_ATTR_CHECK_DISABLE	BIT(18)
#घोषणा SC_ENABLE_TEXGRD_FLAGS		BIT(25)
/* End SHADER_CONFIG रेजिस्टर */

/* TILER_CONFIG रेजिस्टर */
#घोषणा TC_CLOCK_GATE_OVERRIDE		BIT(0)

/* JM_CONFIG रेजिस्टर */
#घोषणा JM_TIMESTAMP_OVERRIDE		BIT(0)
#घोषणा JM_CLOCK_GATE_OVERRIDE		BIT(1)
#घोषणा JM_JOB_THROTTLE_ENABLE		BIT(2)
#घोषणा JM_JOB_THROTTLE_LIMIT_SHIFT	3
#घोषणा JM_MAX_JOB_THROTTLE_LIMIT	0x3F
#घोषणा JM_FORCE_COHERENCY_FEATURES_SHIFT 2
#घोषणा JM_IDVS_GROUP_SIZE_SHIFT	16
#घोषणा JM_MAX_IDVS_GROUP_SIZE		0x3F


/* Job Control regs */
#घोषणा JOB_INT_RAWSTAT			0x1000
#घोषणा JOB_INT_CLEAR			0x1004
#घोषणा JOB_INT_MASK			0x1008
#घोषणा JOB_INT_STAT			0x100c
#घोषणा JOB_INT_JS_STATE		0x1010
#घोषणा JOB_INT_THROTTLE		0x1014

#घोषणा MK_JS_MASK(j)			(0x10001 << (j))
#घोषणा JOB_INT_MASK_ERR(j)		BIT((j) + 16)
#घोषणा JOB_INT_MASK_DONE(j)		BIT(j)

#घोषणा JS_BASE				0x1800
#घोषणा JS_HEAD_LO(n)			(JS_BASE + ((n) * 0x80) + 0x00)
#घोषणा JS_HEAD_HI(n)			(JS_BASE + ((n) * 0x80) + 0x04)
#घोषणा JS_TAIL_LO(n)			(JS_BASE + ((n) * 0x80) + 0x08)
#घोषणा JS_TAIL_HI(n)			(JS_BASE + ((n) * 0x80) + 0x0c)
#घोषणा JS_AFFINITY_LO(n)		(JS_BASE + ((n) * 0x80) + 0x10)
#घोषणा JS_AFFINITY_HI(n)		(JS_BASE + ((n) * 0x80) + 0x14)
#घोषणा JS_CONFIG(n)			(JS_BASE + ((n) * 0x80) + 0x18)
#घोषणा JS_XAFFINITY(n)			(JS_BASE + ((n) * 0x80) + 0x1c)
#घोषणा JS_COMMAND(n)			(JS_BASE + ((n) * 0x80) + 0x20)
#घोषणा JS_STATUS(n)			(JS_BASE + ((n) * 0x80) + 0x24)
#घोषणा JS_HEAD_NEXT_LO(n)		(JS_BASE + ((n) * 0x80) + 0x40)
#घोषणा JS_HEAD_NEXT_HI(n)		(JS_BASE + ((n) * 0x80) + 0x44)
#घोषणा JS_AFFINITY_NEXT_LO(n)		(JS_BASE + ((n) * 0x80) + 0x50)
#घोषणा JS_AFFINITY_NEXT_HI(n)		(JS_BASE + ((n) * 0x80) + 0x54)
#घोषणा JS_CONFIG_NEXT(n)		(JS_BASE + ((n) * 0x80) + 0x58)
#घोषणा JS_COMMAND_NEXT(n)		(JS_BASE + ((n) * 0x80) + 0x60)
#घोषणा JS_FLUSH_ID_NEXT(n)		(JS_BASE + ((n) * 0x80) + 0x70)

/* Possible values of JS_CONFIG and JS_CONFIG_NEXT रेजिस्टरs */
#घोषणा JS_CONFIG_START_FLUSH_CLEAN		BIT(8)
#घोषणा JS_CONFIG_START_FLUSH_CLEAN_INVALIDATE	(3u << 8)
#घोषणा JS_CONFIG_START_MMU			BIT(10)
#घोषणा JS_CONFIG_JOB_CHAIN_FLAG		BIT(11)
#घोषणा JS_CONFIG_END_FLUSH_CLEAN		BIT(12)
#घोषणा JS_CONFIG_END_FLUSH_CLEAN_INVALIDATE	(3u << 12)
#घोषणा JS_CONFIG_ENABLE_FLUSH_REDUCTION	BIT(14)
#घोषणा JS_CONFIG_DISABLE_DESCRIPTOR_WR_BK	BIT(15)
#घोषणा JS_CONFIG_THREAD_PRI(n)			((n) << 16)

#घोषणा JS_COMMAND_NOP			0x00
#घोषणा JS_COMMAND_START		0x01
#घोषणा JS_COMMAND_SOFT_STOP		0x02	/* Gently stop processing a job chain */
#घोषणा JS_COMMAND_HARD_STOP		0x03	/* Rudely stop processing a job chain */
#घोषणा JS_COMMAND_SOFT_STOP_0		0x04	/* Execute SOFT_STOP अगर JOB_CHAIN_FLAG is 0 */
#घोषणा JS_COMMAND_HARD_STOP_0		0x05	/* Execute HARD_STOP अगर JOB_CHAIN_FLAG is 0 */
#घोषणा JS_COMMAND_SOFT_STOP_1		0x06	/* Execute SOFT_STOP अगर JOB_CHAIN_FLAG is 1 */
#घोषणा JS_COMMAND_HARD_STOP_1		0x07	/* Execute HARD_STOP अगर JOB_CHAIN_FLAG is 1 */

#घोषणा JS_STATUS_EVENT_ACTIVE		0x08


/* MMU regs */
#घोषणा MMU_INT_RAWSTAT			0x2000
#घोषणा MMU_INT_CLEAR			0x2004
#घोषणा MMU_INT_MASK			0x2008
#घोषणा MMU_INT_STAT			0x200c

/* AS_COMMAND रेजिस्टर commands */
#घोषणा AS_COMMAND_NOP			0x00	/* NOP Operation */
#घोषणा AS_COMMAND_UPDATE		0x01	/* Broadcasts the values in AS_TRANSTAB and ASn_MEMATTR to all MMUs */
#घोषणा AS_COMMAND_LOCK			0x02	/* Issue a lock region command to all MMUs */
#घोषणा AS_COMMAND_UNLOCK		0x03	/* Issue a flush region command to all MMUs */
#घोषणा AS_COMMAND_FLUSH		0x04	/* Flush all L2 caches then issue a flush region command to all MMUs
						   (deprecated - only क्रम use with T60x) */
#घोषणा AS_COMMAND_FLUSH_PT		0x04	/* Flush all L2 caches then issue a flush region command to all MMUs */
#घोषणा AS_COMMAND_FLUSH_MEM		0x05	/* Wait क्रम memory accesses to complete, flush all the L1s cache then
						   flush all L2 caches then issue a flush region command to all MMUs */

#घोषणा MMU_AS(as)			(0x2400 + ((as) << 6))

#घोषणा AS_TRANSTAB_LO(as)		(MMU_AS(as) + 0x00) /* (RW) Translation Table Base Address क्रम address space n, low word */
#घोषणा AS_TRANSTAB_HI(as)		(MMU_AS(as) + 0x04) /* (RW) Translation Table Base Address क्रम address space n, high word */
#घोषणा AS_MEMATTR_LO(as)		(MMU_AS(as) + 0x08) /* (RW) Memory attributes क्रम address space n, low word. */
#घोषणा AS_MEMATTR_HI(as)		(MMU_AS(as) + 0x0C) /* (RW) Memory attributes क्रम address space n, high word. */
#घोषणा AS_LOCKADDR_LO(as)		(MMU_AS(as) + 0x10) /* (RW) Lock region address क्रम address space n, low word */
#घोषणा AS_LOCKADDR_HI(as)		(MMU_AS(as) + 0x14) /* (RW) Lock region address क्रम address space n, high word */
#घोषणा AS_COMMAND(as)			(MMU_AS(as) + 0x18) /* (WO) MMU command रेजिस्टर क्रम address space n */
#घोषणा AS_FAULTSTATUS(as)		(MMU_AS(as) + 0x1C) /* (RO) MMU fault status रेजिस्टर क्रम address space n */
#घोषणा AS_FAULTADDRESS_LO(as)		(MMU_AS(as) + 0x20) /* (RO) Fault Address क्रम address space n, low word */
#घोषणा AS_FAULTADDRESS_HI(as)		(MMU_AS(as) + 0x24) /* (RO) Fault Address क्रम address space n, high word */
#घोषणा AS_STATUS(as)			(MMU_AS(as) + 0x28) /* (RO) Status flags क्रम address space n */
/* Additional Bअगरrost AS regsiters */
#घोषणा AS_TRANSCFG_LO(as)		(MMU_AS(as) + 0x30) /* (RW) Translation table configuration क्रम address space n, low word */
#घोषणा AS_TRANSCFG_HI(as)		(MMU_AS(as) + 0x34) /* (RW) Translation table configuration क्रम address space n, high word */
#घोषणा AS_FAULTEXTRA_LO(as)		(MMU_AS(as) + 0x38) /* (RO) Secondary fault address क्रम address space n, low word */
#घोषणा AS_FAULTEXTRA_HI(as)		(MMU_AS(as) + 0x3C) /* (RO) Secondary fault address क्रम address space n, high word */

/*
 * Begin LPAE MMU TRANSTAB रेजिस्टर values
 */
#घोषणा AS_TRANSTAB_LPAE_ADDR_SPACE_MASK	0xfffffffffffff000
#घोषणा AS_TRANSTAB_LPAE_ADRMODE_IDENTITY	0x2
#घोषणा AS_TRANSTAB_LPAE_ADRMODE_TABLE		0x3
#घोषणा AS_TRANSTAB_LPAE_ADRMODE_MASK		0x3
#घोषणा AS_TRANSTAB_LPAE_READ_INNER		BIT(2)
#घोषणा AS_TRANSTAB_LPAE_SHARE_OUTER		BIT(4)

#घोषणा AS_STATUS_AS_ACTIVE			0x01

#घोषणा AS_FAULTSTATUS_ACCESS_TYPE_MASK		(0x3 << 8)
#घोषणा AS_FAULTSTATUS_ACCESS_TYPE_ATOMIC	(0x0 << 8)
#घोषणा AS_FAULTSTATUS_ACCESS_TYPE_EX		(0x1 << 8)
#घोषणा AS_FAULTSTATUS_ACCESS_TYPE_READ		(0x2 << 8)
#घोषणा AS_FAULTSTATUS_ACCESS_TYPE_WRITE	(0x3 << 8)

#घोषणा gpu_ग_लिखो(dev, reg, data) ग_लिखोl(data, dev->iomem + reg)
#घोषणा gpu_पढ़ो(dev, reg) पढ़ोl(dev->iomem + reg)

#पूर्ण_अगर
