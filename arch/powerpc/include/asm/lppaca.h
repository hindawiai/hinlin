<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * lppaca.h
 * Copyright (C) 2001  Mike Corrigan IBM Corporation
 */
#अगर_अघोषित _ASM_POWERPC_LPPACA_H
#घोषणा _ASM_POWERPC_LPPACA_H

/*
 * The below VPHN macros are outside the __KERNEL__ check since these are
 * used क्रम compiling the vphn selftest in userspace
 */

/* The H_HOME_NODE_ASSOCIATIVITY h_call वापसs 6 64-bit रेजिस्टरs. */
#घोषणा VPHN_REGISTER_COUNT 6

/*
 * 6 64-bit रेजिस्टरs unpacked पूर्णांकo up to 24 be32 associativity values. To
 * क्रमm the complete property we have to add the length in the first cell.
 */
#घोषणा VPHN_ASSOC_बफ_मानE (VPHN_REGISTER_COUNT*माप(u64)/माप(u16) + 1)

/*
 * The H_HOME_NODE_ASSOCIATIVITY hcall takes two values क्रम flags:
 * 1 क्रम retrieving associativity inक्रमmation क्रम a guest cpu
 * 2 क्रम retrieving associativity inक्रमmation क्रम a host/hypervisor cpu
 */
#घोषणा VPHN_FLAG_VCPU	1
#घोषणा VPHN_FLAG_PCPU	2

#अगर_घोषित __KERNEL__

/*
 * These definitions relate to hypervisors that only exist when using
 * a server type processor
 */
#अगर_घोषित CONFIG_PPC_BOOK3S

/*
 * This control block contains the data that is shared between the
 * hypervisor and the OS.
 */
#समावेश <linux/cache.h>
#समावेश <linux/thपढ़ोs.h>
#समावेश <यंत्र/types.h>
#समावेश <यंत्र/mmu.h>
#समावेश <यंत्र/firmware.h>

/*
 * The lppaca is the "virtual processor area" रेजिस्टरed with the hypervisor,
 * H_REGISTER_VPA etc.
 *
 * According to PAPR, the काष्ठाure is 640 bytes दीर्घ, must be L1 cache line
 * aligned, and must not cross a 4kB boundary. Its size field must be at
 * least 640 bytes (but may be more).
 *
 * Pre-v4.14 KVM hypervisors reject the VPA अगर its size field is smaller than
 * 1kB, so we dynamically allocate 1kB and advertise size as 1kB, but keep
 * this काष्ठाure as the canonical 640 byte size.
 */
काष्ठा lppaca अणु
	/* cacheline 1 contains पढ़ो-only data */

	__be32	desc;			/* Eye catcher 0xD397D781 */
	__be16	size;			/* Size of this काष्ठा */
	u8	reserved1[3];
	u8	__old_status;		/* Old status, including shared proc */
	u8	reserved3[14];
	अस्थिर __be32 dyn_hw_node_id;	/* Dynamic hardware node id */
	अस्थिर __be32 dyn_hw_proc_id;	/* Dynamic hardware proc id */
	u8	reserved4[56];
	अस्थिर u8 vphn_assoc_counts[8]; /* Virtual processor home node */
					  /* associativity change counters */
	u8	reserved5[32];

	/* cacheline 2 contains local पढ़ो-ग_लिखो data */

	u8	reserved6[48];
	u8	cede_latency_hपूर्णांक;
	u8	ebb_regs_in_use;
	u8	reserved7[6];
	u8	dtl_enable_mask;	/* Dispatch Trace Log mask */
	u8	करोnate_dedicated_cpu;	/* Donate dedicated CPU cycles */
	u8	fpregs_in_use;
	u8	pmcregs_in_use;
	u8	reserved8[28];
	__be64	रुको_state_cycles;	/* Wait cycles क्रम this proc */
	u8	reserved9[28];
	__be16	slb_count;		/* # of SLBs to मुख्यtain */
	u8	idle;			/* Indicate OS is idle */
	u8	vmxregs_in_use;

	/* cacheline 3 is shared with other processors */

	/*
	 * This is the yield_count.  An "odd" value (low bit on) means that
	 * the processor is yielded (either because of an OS yield or a
	 * hypervisor preempt).  An even value implies that the processor is
	 * currently executing.
	 * NOTE: Even dedicated processor partitions can yield so this
	 * field cannot be used to determine अगर we are shared or dedicated.
	 */
	अस्थिर __be32 yield_count;
	अस्थिर __be32 dispersion_count; /* dispatch changed physical cpu */
	अस्थिर __be64 cmo_faults;	/* CMO page fault count */
	अस्थिर __be64 cmo_fault_समय;	/* CMO page fault समय */
	u8	reserved10[104];

	/* cacheline 4-5 */

	__be32	page_ins;		/* CMO Hपूर्णांक - # page ins by OS */
	u8	reserved11[148];
	अस्थिर __be64 dtl_idx;	/* Dispatch Trace Log head index */
	u8	reserved12[96];
पूर्ण ____cacheline_aligned;

#घोषणा lppaca_of(cpu)	(*paca_ptrs[cpu]->lppaca_ptr)

/*
 * We are using a non architected field to determine अगर a partition is
 * shared or dedicated. This currently works on both KVM and PHYP, but
 * we will have to transition to something better.
 */
#घोषणा LPPACA_OLD_SHARED_PROC		2

अटल अंतरभूत bool lppaca_shared_proc(काष्ठा lppaca *l)
अणु
	अगर (!firmware_has_feature(FW_FEATURE_SPLPAR))
		वापस false;
	वापस !!(l->__old_status & LPPACA_OLD_SHARED_PROC);
पूर्ण

/*
 * SLB shaकरोw buffer काष्ठाure as defined in the PAPR.  The save_area
 * contains adjacent ESID and VSID pairs क्रम each shaकरोwed SLB.  The
 * ESID is stored in the lower 64bits, then the VSID.
 */
काष्ठा slb_shaकरोw अणु
	__be32	persistent;		/* Number of persistent SLBs */
	__be32	buffer_length;		/* Total shaकरोw buffer length */
	__be64	reserved;
	काष्ठा	अणु
		__be64     esid;
		__be64	vsid;
	पूर्ण save_area[SLB_NUM_BOLTED];
पूर्ण ____cacheline_aligned;

बाह्य दीर्घ hcall_vphn(अचिन्हित दीर्घ cpu, u64 flags, __be32 *associativity);

#पूर्ण_अगर /* CONFIG_PPC_BOOK3S */
#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /* _ASM_POWERPC_LPPACA_H */
