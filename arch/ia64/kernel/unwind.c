<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 1999-2004 Hewlett-Packard Co
 *	David Mosberger-Tang <davidm@hpl.hp.com>
 * Copyright (C) 2003 Fenghua Yu <fenghua.yu@पूर्णांकel.com>
 * 	- Change pt_regs_off() to make it less dependent on pt_regs काष्ठाure.
 */
/*
 * This file implements call frame unwind support क्रम the Linux
 * kernel.  Parsing and processing the unwind inक्रमmation is
 * समय-consuming, so this implementation translates the unwind
 * descriptors पूर्णांकo unwind scripts.  These scripts are very simple
 * (basically a sequence of assignments) and efficient to execute.
 * They are cached क्रम later re-use.  Each script is specअगरic क्रम a
 * given inकाष्ठाion poपूर्णांकer address and the set of predicate values
 * that the script depends on (most unwind descriptors are
 * unconditional and scripts often करो not depend on predicates at
 * all).  This code is based on the unwind conventions described in
 * the "IA-64 Software Conventions and Runtime Architecture" manual.
 *
 * SMP conventions:
 *	o updates to the global unwind data (in काष्ठाure "unw") are serialized
 *	  by the unw.lock spinlock
 *	o each unwind script has its own पढ़ो-ग_लिखो lock; a thपढ़ो must acquire
 *	  a पढ़ो lock beक्रमe executing a script and must acquire a ग_लिखो lock
 *	  beक्रमe modअगरying a script
 *	o अगर both the unw.lock spinlock and a script's पढ़ो-ग_लिखो lock must be
 *	  acquired, then the पढ़ो-ग_लिखो lock must be acquired first.
 */
#समावेश <linux/module.h>
#समावेश <linux/memblock.h>
#समावेश <linux/elf.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/unwind.h>

#समावेश <यंत्र/delay.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/ptrace_offsets.h>
#समावेश <यंत्र/rse.h>
#समावेश <यंत्र/sections.h>
#समावेश <linux/uaccess.h>

#समावेश "entry.h"
#समावेश "unwind_i.h"

#घोषणा UNW_LOG_CACHE_SIZE	7	/* each unw_script is ~256 bytes in size */
#घोषणा UNW_CACHE_SIZE		(1 << UNW_LOG_CACHE_SIZE)

#घोषणा UNW_LOG_HASH_SIZE	(UNW_LOG_CACHE_SIZE + 1)
#घोषणा UNW_HASH_SIZE		(1 << UNW_LOG_HASH_SIZE)

#घोषणा UNW_STATS	0	/* WARNING: this disabled पूर्णांकerrupts क्रम दीर्घ समय-spans!! */

#अगर_घोषित UNW_DEBUG
  अटल अचिन्हित पूर्णांक unw_debug_level = UNW_DEBUG;
#  define UNW_DEBUG_ON(n)	unw_debug_level >= n
   /* Do not code a prपूर्णांकk level, not all debug lines end in newline */
#  define UNW_DPRINT(n, ...)  अगर (UNW_DEBUG_ON(n)) prपूर्णांकk(__VA_ARGS__)
#  undef अंतरभूत
#  define अंतरभूत
#अन्यथा /* !UNW_DEBUG */
#  define UNW_DEBUG_ON(n)  0
#  define UNW_DPRINT(n, ...)
#पूर्ण_अगर /* UNW_DEBUG */

#अगर UNW_STATS
# define STAT(x...)	x
#अन्यथा
# define STAT(x...)
#पूर्ण_अगर

#घोषणा alloc_reg_state()	kदो_स्मृति(माप(काष्ठा unw_reg_state), GFP_ATOMIC)
#घोषणा मुक्त_reg_state(usr)	kमुक्त(usr)
#घोषणा alloc_labeled_state()	kदो_स्मृति(माप(काष्ठा unw_labeled_state), GFP_ATOMIC)
#घोषणा मुक्त_labeled_state(usr)	kमुक्त(usr)

प्रकार अचिन्हित दीर्घ unw_word;
प्रकार अचिन्हित अक्षर unw_hash_index_t;

अटल काष्ठा अणु
	spinlock_t lock;			/* spinlock क्रम unwind data */

	/* list of unwind tables (one per load-module) */
	काष्ठा unw_table *tables;

	अचिन्हित दीर्घ r0;			/* स्थिरant 0 क्रम r0 */

	/* table of रेजिस्टरs that prologues can save (and order in which they're saved): */
	स्थिर अचिन्हित अक्षर save_order[8];

	/* maps a preserved रेजिस्टर index (preg_index) to corresponding चयन_stack offset: */
	अचिन्हित लघु sw_off[माप(काष्ठा unw_frame_info) / 8];

	अचिन्हित लघु lru_head;		/* index of lead-recently used script */
	अचिन्हित लघु lru_tail;		/* index of most-recently used script */

	/* index पूर्णांकo unw_frame_info क्रम preserved रेजिस्टर i */
	अचिन्हित लघु preg_index[UNW_NUM_REGS];

	लघु pt_regs_offsets[32];

	/* unwind table क्रम the kernel: */
	काष्ठा unw_table kernel_table;

	/* unwind table describing the gate page (kernel code that is mapped पूर्णांकo user space): */
	माप_प्रकार gate_table_size;
	अचिन्हित दीर्घ *gate_table;

	/* hash table that maps inकाष्ठाion poपूर्णांकer to script index: */
	अचिन्हित लघु hash[UNW_HASH_SIZE];

	/* script cache: */
	काष्ठा unw_script cache[UNW_CACHE_SIZE];

# अगरdef UNW_DEBUG
	स्थिर अक्षर *preg_name[UNW_NUM_REGS];
# endअगर
# अगर UNW_STATS
	काष्ठा अणु
		काष्ठा अणु
			पूर्णांक lookups;
			पूर्णांक hपूर्णांकed_hits;
			पूर्णांक normal_hits;
			पूर्णांक collision_chain_traversals;
		पूर्ण cache;
		काष्ठा अणु
			अचिन्हित दीर्घ build_समय;
			अचिन्हित दीर्घ run_समय;
			अचिन्हित दीर्घ parse_समय;
			पूर्णांक builds;
			पूर्णांक news;
			पूर्णांक collisions;
			पूर्णांक runs;
		पूर्ण script;
		काष्ठा अणु
			अचिन्हित दीर्घ init_समय;
			अचिन्हित दीर्घ unwind_समय;
			पूर्णांक inits;
			पूर्णांक unwinds;
		पूर्ण api;
	पूर्ण stat;
# endअगर
पूर्ण unw = अणु
	.tables = &unw.kernel_table,
	.lock = __SPIN_LOCK_UNLOCKED(unw.lock),
	.save_order = अणु
		UNW_REG_RP, UNW_REG_PFS, UNW_REG_PSP, UNW_REG_PR,
		UNW_REG_UNAT, UNW_REG_LC, UNW_REG_FPSR, UNW_REG_PRI_UNAT_GR
	पूर्ण,
	.preg_index = अणु
		दुरत्व(काष्ठा unw_frame_info, pri_unat_loc)/8,	/* PRI_UNAT_GR */
		दुरत्व(काष्ठा unw_frame_info, pri_unat_loc)/8,	/* PRI_UNAT_MEM */
		दुरत्व(काष्ठा unw_frame_info, bsp_loc)/8,
		दुरत्व(काष्ठा unw_frame_info, bspstore_loc)/8,
		दुरत्व(काष्ठा unw_frame_info, pfs_loc)/8,
		दुरत्व(काष्ठा unw_frame_info, rnat_loc)/8,
		दुरत्व(काष्ठा unw_frame_info, psp)/8,
		दुरत्व(काष्ठा unw_frame_info, rp_loc)/8,
		दुरत्व(काष्ठा unw_frame_info, r4)/8,
		दुरत्व(काष्ठा unw_frame_info, r5)/8,
		दुरत्व(काष्ठा unw_frame_info, r6)/8,
		दुरत्व(काष्ठा unw_frame_info, r7)/8,
		दुरत्व(काष्ठा unw_frame_info, unat_loc)/8,
		दुरत्व(काष्ठा unw_frame_info, pr_loc)/8,
		दुरत्व(काष्ठा unw_frame_info, lc_loc)/8,
		दुरत्व(काष्ठा unw_frame_info, fpsr_loc)/8,
		दुरत्व(काष्ठा unw_frame_info, b1_loc)/8,
		दुरत्व(काष्ठा unw_frame_info, b2_loc)/8,
		दुरत्व(काष्ठा unw_frame_info, b3_loc)/8,
		दुरत्व(काष्ठा unw_frame_info, b4_loc)/8,
		दुरत्व(काष्ठा unw_frame_info, b5_loc)/8,
		दुरत्व(काष्ठा unw_frame_info, f2_loc)/8,
		दुरत्व(काष्ठा unw_frame_info, f3_loc)/8,
		दुरत्व(काष्ठा unw_frame_info, f4_loc)/8,
		दुरत्व(काष्ठा unw_frame_info, f5_loc)/8,
		दुरत्व(काष्ठा unw_frame_info, fr_loc[16 - 16])/8,
		दुरत्व(काष्ठा unw_frame_info, fr_loc[17 - 16])/8,
		दुरत्व(काष्ठा unw_frame_info, fr_loc[18 - 16])/8,
		दुरत्व(काष्ठा unw_frame_info, fr_loc[19 - 16])/8,
		दुरत्व(काष्ठा unw_frame_info, fr_loc[20 - 16])/8,
		दुरत्व(काष्ठा unw_frame_info, fr_loc[21 - 16])/8,
		दुरत्व(काष्ठा unw_frame_info, fr_loc[22 - 16])/8,
		दुरत्व(काष्ठा unw_frame_info, fr_loc[23 - 16])/8,
		दुरत्व(काष्ठा unw_frame_info, fr_loc[24 - 16])/8,
		दुरत्व(काष्ठा unw_frame_info, fr_loc[25 - 16])/8,
		दुरत्व(काष्ठा unw_frame_info, fr_loc[26 - 16])/8,
		दुरत्व(काष्ठा unw_frame_info, fr_loc[27 - 16])/8,
		दुरत्व(काष्ठा unw_frame_info, fr_loc[28 - 16])/8,
		दुरत्व(काष्ठा unw_frame_info, fr_loc[29 - 16])/8,
		दुरत्व(काष्ठा unw_frame_info, fr_loc[30 - 16])/8,
		दुरत्व(काष्ठा unw_frame_info, fr_loc[31 - 16])/8,
	पूर्ण,
	.pt_regs_offsets = अणु
		[0] = -1,
		दुरत्व(काष्ठा pt_regs,  r1),
		दुरत्व(काष्ठा pt_regs,  r2),
		दुरत्व(काष्ठा pt_regs,  r3),
		[4] = -1, [5] = -1, [6] = -1, [7] = -1,
		दुरत्व(काष्ठा pt_regs,  r8),
		दुरत्व(काष्ठा pt_regs,  r9),
		दुरत्व(काष्ठा pt_regs, r10),
		दुरत्व(काष्ठा pt_regs, r11),
		दुरत्व(काष्ठा pt_regs, r12),
		दुरत्व(काष्ठा pt_regs, r13),
		दुरत्व(काष्ठा pt_regs, r14),
		दुरत्व(काष्ठा pt_regs, r15),
		दुरत्व(काष्ठा pt_regs, r16),
		दुरत्व(काष्ठा pt_regs, r17),
		दुरत्व(काष्ठा pt_regs, r18),
		दुरत्व(काष्ठा pt_regs, r19),
		दुरत्व(काष्ठा pt_regs, r20),
		दुरत्व(काष्ठा pt_regs, r21),
		दुरत्व(काष्ठा pt_regs, r22),
		दुरत्व(काष्ठा pt_regs, r23),
		दुरत्व(काष्ठा pt_regs, r24),
		दुरत्व(काष्ठा pt_regs, r25),
		दुरत्व(काष्ठा pt_regs, r26),
		दुरत्व(काष्ठा pt_regs, r27),
		दुरत्व(काष्ठा pt_regs, r28),
		दुरत्व(काष्ठा pt_regs, r29),
		दुरत्व(काष्ठा pt_regs, r30),
		दुरत्व(काष्ठा pt_regs, r31),
	पूर्ण,
	.hash = अणु [0 ... UNW_HASH_SIZE - 1] = -1 पूर्ण,
#अगर_घोषित UNW_DEBUG
	.preg_name = अणु
		"pri_unat_gr", "pri_unat_mem", "bsp", "bspstore", "ar.pfs", "ar.rnat", "psp", "rp",
		"r4", "r5", "r6", "r7",
		"ar.unat", "pr", "ar.lc", "ar.fpsr",
		"b1", "b2", "b3", "b4", "b5",
		"f2", "f3", "f4", "f5",
		"f16", "f17", "f18", "f19", "f20", "f21", "f22", "f23",
		"f24", "f25", "f26", "f27", "f28", "f29", "f30", "f31"
	पूर्ण
#पूर्ण_अगर
पूर्ण;

अटल अंतरभूत पूर्णांक
पढ़ो_only (व्योम *addr)
अणु
	वापस (अचिन्हित दीर्घ) ((अक्षर *) addr - (अक्षर *) &unw.r0) < माप(unw.r0);
पूर्ण

/*
 * Returns offset of rREG in काष्ठा pt_regs.
 */
अटल अंतरभूत अचिन्हित दीर्घ
pt_regs_off (अचिन्हित दीर्घ reg)
अणु
	लघु off = -1;

	अगर (reg < ARRAY_SIZE(unw.pt_regs_offsets))
		off = unw.pt_regs_offsets[reg];

	अगर (off < 0) अणु
		UNW_DPRINT(0, "unwind.%s: bad scratch reg r%lu\n", __func__, reg);
		off = 0;
	पूर्ण
	वापस (अचिन्हित दीर्घ) off;
पूर्ण

अटल अंतरभूत काष्ठा pt_regs *
get_scratch_regs (काष्ठा unw_frame_info *info)
अणु
	अगर (!info->pt) अणु
		/* This should not happen with valid unwind info.  */
		UNW_DPRINT(0, "unwind.%s: bad unwind info: resetting info->pt\n", __func__);
		अगर (info->flags & UNW_FLAG_INTERRUPT_FRAME)
			info->pt = (अचिन्हित दीर्घ) ((काष्ठा pt_regs *) info->psp - 1);
		अन्यथा
			info->pt = info->sp - 16;
	पूर्ण
	UNW_DPRINT(3, "unwind.%s: sp 0x%lx pt 0x%lx\n", __func__, info->sp, info->pt);
	वापस (काष्ठा pt_regs *) info->pt;
पूर्ण

/* Unwind accessors.  */

पूर्णांक
unw_access_gr (काष्ठा unw_frame_info *info, पूर्णांक regnum, अचिन्हित दीर्घ *val, अक्षर *nat, पूर्णांक ग_लिखो)
अणु
	अचिन्हित दीर्घ *addr, *nat_addr, nat_mask = 0, dummy_nat;
	काष्ठा unw_ireg *ireg;
	काष्ठा pt_regs *pt;

	अगर ((अचिन्हित) regnum - 1 >= 127) अणु
		अगर (regnum == 0 && !ग_लिखो) अणु
			*val = 0;	/* पढ़ो r0 always वापसs 0 */
			*nat = 0;
			वापस 0;
		पूर्ण
		UNW_DPRINT(0, "unwind.%s: trying to access non-existent r%u\n",
			   __func__, regnum);
		वापस -1;
	पूर्ण

	अगर (regnum < 32) अणु
		अगर (regnum >= 4 && regnum <= 7) अणु
			/* access a preserved रेजिस्टर */
			ireg = &info->r4 + (regnum - 4);
			addr = ireg->loc;
			अगर (addr) अणु
				nat_addr = addr + ireg->nat.off;
				चयन (ireg->nat.type) अणु
				      हाल UNW_NAT_VAL:
					/* simulate getf.sig/setf.sig */
					अगर (ग_लिखो) अणु
						अगर (*nat) अणु
							/* ग_लिखो NaTVal and be करोne with it */
							addr[0] = 0;
							addr[1] = 0x1fffe;
							वापस 0;
						पूर्ण
						addr[1] = 0x1003e;
					पूर्ण अन्यथा अणु
						अगर (addr[0] == 0 && addr[1] == 0x1ffe) अणु
							/* वापस NaT and be करोne with it */
							*val = 0;
							*nat = 1;
							वापस 0;
						पूर्ण
					पूर्ण
					fallthrough;
				      हाल UNW_NAT_NONE:
					dummy_nat = 0;
					nat_addr = &dummy_nat;
					अवरोध;

				      हाल UNW_NAT_MEMSTK:
					nat_mask = (1UL << ((दीर्घ) addr & 0x1f8)/8);
					अवरोध;

				      हाल UNW_NAT_REGSTK:
					nat_addr = ia64_rse_rnat_addr(addr);
					अगर ((अचिन्हित दीर्घ) addr < info->regstk.limit
					    || (अचिन्हित दीर्घ) addr >= info->regstk.top)
					अणु
						UNW_DPRINT(0, "unwind.%s: %p outside of regstk "
							"[0x%lx-0x%lx)\n",
							__func__, (व्योम *) addr,
							info->regstk.limit,
							info->regstk.top);
						वापस -1;
					पूर्ण
					अगर ((अचिन्हित दीर्घ) nat_addr >= info->regstk.top)
						nat_addr = &info->sw->ar_rnat;
					nat_mask = (1UL << ia64_rse_slot_num(addr));
					अवरोध;
				पूर्ण
			पूर्ण अन्यथा अणु
				addr = &info->sw->r4 + (regnum - 4);
				nat_addr = &info->sw->ar_unat;
				nat_mask = (1UL << ((दीर्घ) addr & 0x1f8)/8);
			पूर्ण
		पूर्ण अन्यथा अणु
			/* access a scratch रेजिस्टर */
			pt = get_scratch_regs(info);
			addr = (अचिन्हित दीर्घ *) ((अचिन्हित दीर्घ)pt + pt_regs_off(regnum));
			अगर (info->pri_unat_loc)
				nat_addr = info->pri_unat_loc;
			अन्यथा
				nat_addr = &info->sw->caller_unat;
			nat_mask = (1UL << ((दीर्घ) addr & 0x1f8)/8);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* access a stacked रेजिस्टर */
		addr = ia64_rse_skip_regs((अचिन्हित दीर्घ *) info->bsp, regnum - 32);
		nat_addr = ia64_rse_rnat_addr(addr);
		अगर ((अचिन्हित दीर्घ) addr < info->regstk.limit
		    || (अचिन्हित दीर्घ) addr >= info->regstk.top)
		अणु
			UNW_DPRINT(0, "unwind.%s: ignoring attempt to access register outside "
				   "of rbs\n",  __func__);
			वापस -1;
		पूर्ण
		अगर ((अचिन्हित दीर्घ) nat_addr >= info->regstk.top)
			nat_addr = &info->sw->ar_rnat;
		nat_mask = (1UL << ia64_rse_slot_num(addr));
	पूर्ण

	अगर (ग_लिखो) अणु
		अगर (पढ़ो_only(addr)) अणु
			UNW_DPRINT(0, "unwind.%s: ignoring attempt to write read-only location\n",
				__func__);
		पूर्ण अन्यथा अणु
			*addr = *val;
			अगर (*nat)
				*nat_addr |= nat_mask;
			अन्यथा
				*nat_addr &= ~nat_mask;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर ((*nat_addr & nat_mask) == 0) अणु
			*val = *addr;
			*nat = 0;
		पूर्ण अन्यथा अणु
			*val = 0;	/* अगर रेजिस्टर is a NaT, *addr may contain kernel data! */
			*nat = 1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(unw_access_gr);

पूर्णांक
unw_access_br (काष्ठा unw_frame_info *info, पूर्णांक regnum, अचिन्हित दीर्घ *val, पूर्णांक ग_लिखो)
अणु
	अचिन्हित दीर्घ *addr;
	काष्ठा pt_regs *pt;

	चयन (regnum) अणु
		/* scratch: */
	      हाल 0: pt = get_scratch_regs(info); addr = &pt->b0; अवरोध;
	      हाल 6: pt = get_scratch_regs(info); addr = &pt->b6; अवरोध;
	      हाल 7: pt = get_scratch_regs(info); addr = &pt->b7; अवरोध;

		/* preserved: */
	      हाल 1: हाल 2: हाल 3: हाल 4: हाल 5:
		addr = *(&info->b1_loc + (regnum - 1));
		अगर (!addr)
			addr = &info->sw->b1 + (regnum - 1);
		अवरोध;

	      शेष:
		UNW_DPRINT(0, "unwind.%s: trying to access non-existent b%u\n",
			   __func__, regnum);
		वापस -1;
	पूर्ण
	अगर (ग_लिखो)
		अगर (पढ़ो_only(addr)) अणु
			UNW_DPRINT(0, "unwind.%s: ignoring attempt to write read-only location\n",
				__func__);
		पूर्ण अन्यथा
			*addr = *val;
	अन्यथा
		*val = *addr;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(unw_access_br);

पूर्णांक
unw_access_fr (काष्ठा unw_frame_info *info, पूर्णांक regnum, काष्ठा ia64_fpreg *val, पूर्णांक ग_लिखो)
अणु
	काष्ठा ia64_fpreg *addr = शून्य;
	काष्ठा pt_regs *pt;

	अगर ((अचिन्हित) (regnum - 2) >= 126) अणु
		UNW_DPRINT(0, "unwind.%s: trying to access non-existent f%u\n",
			   __func__, regnum);
		वापस -1;
	पूर्ण

	अगर (regnum <= 5) अणु
		addr = *(&info->f2_loc + (regnum - 2));
		अगर (!addr)
			addr = &info->sw->f2 + (regnum - 2);
	पूर्ण अन्यथा अगर (regnum <= 15) अणु
		अगर (regnum <= 11) अणु
			pt = get_scratch_regs(info);
			addr = &pt->f6  + (regnum - 6);
		पूर्ण
		अन्यथा
			addr = &info->sw->f12 + (regnum - 12);
	पूर्ण अन्यथा अगर (regnum <= 31) अणु
		addr = info->fr_loc[regnum - 16];
		अगर (!addr)
			addr = &info->sw->f16 + (regnum - 16);
	पूर्ण अन्यथा अणु
		काष्ठा task_काष्ठा *t = info->task;

		अगर (ग_लिखो)
			ia64_sync_fph(t);
		अन्यथा
			ia64_flush_fph(t);
		addr = t->thपढ़ो.fph + (regnum - 32);
	पूर्ण

	अगर (ग_लिखो)
		अगर (पढ़ो_only(addr)) अणु
			UNW_DPRINT(0, "unwind.%s: ignoring attempt to write read-only location\n",
				__func__);
		पूर्ण अन्यथा
			*addr = *val;
	अन्यथा
		*val = *addr;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(unw_access_fr);

पूर्णांक
unw_access_ar (काष्ठा unw_frame_info *info, पूर्णांक regnum, अचिन्हित दीर्घ *val, पूर्णांक ग_लिखो)
अणु
	अचिन्हित दीर्घ *addr;
	काष्ठा pt_regs *pt;

	चयन (regnum) अणु
	      हाल UNW_AR_BSP:
		addr = info->bsp_loc;
		अगर (!addr)
			addr = &info->sw->ar_bspstore;
		अवरोध;

	      हाल UNW_AR_BSPSTORE:
		addr = info->bspstore_loc;
		अगर (!addr)
			addr = &info->sw->ar_bspstore;
		अवरोध;

	      हाल UNW_AR_PFS:
		addr = info->pfs_loc;
		अगर (!addr)
			addr = &info->sw->ar_pfs;
		अवरोध;

	      हाल UNW_AR_RNAT:
		addr = info->rnat_loc;
		अगर (!addr)
			addr = &info->sw->ar_rnat;
		अवरोध;

	      हाल UNW_AR_UNAT:
		addr = info->unat_loc;
		अगर (!addr)
			addr = &info->sw->caller_unat;
		अवरोध;

	      हाल UNW_AR_LC:
		addr = info->lc_loc;
		अगर (!addr)
			addr = &info->sw->ar_lc;
		अवरोध;

	      हाल UNW_AR_EC:
		अगर (!info->cfm_loc)
			वापस -1;
		अगर (ग_लिखो)
			*info->cfm_loc =
				(*info->cfm_loc & ~(0x3fUL << 52)) | ((*val & 0x3f) << 52);
		अन्यथा
			*val = (*info->cfm_loc >> 52) & 0x3f;
		वापस 0;

	      हाल UNW_AR_FPSR:
		addr = info->fpsr_loc;
		अगर (!addr)
			addr = &info->sw->ar_fpsr;
		अवरोध;

	      हाल UNW_AR_RSC:
		pt = get_scratch_regs(info);
		addr = &pt->ar_rsc;
		अवरोध;

	      हाल UNW_AR_CCV:
		pt = get_scratch_regs(info);
		addr = &pt->ar_ccv;
		अवरोध;

	      हाल UNW_AR_CSD:
		pt = get_scratch_regs(info);
		addr = &pt->ar_csd;
		अवरोध;

	      हाल UNW_AR_SSD:
		pt = get_scratch_regs(info);
		addr = &pt->ar_ssd;
		अवरोध;

	      शेष:
		UNW_DPRINT(0, "unwind.%s: trying to access non-existent ar%u\n",
			   __func__, regnum);
		वापस -1;
	पूर्ण

	अगर (ग_लिखो) अणु
		अगर (पढ़ो_only(addr)) अणु
			UNW_DPRINT(0, "unwind.%s: ignoring attempt to write read-only location\n",
				__func__);
		पूर्ण अन्यथा
			*addr = *val;
	पूर्ण अन्यथा
		*val = *addr;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(unw_access_ar);

पूर्णांक
unw_access_pr (काष्ठा unw_frame_info *info, अचिन्हित दीर्घ *val, पूर्णांक ग_लिखो)
अणु
	अचिन्हित दीर्घ *addr;

	addr = info->pr_loc;
	अगर (!addr)
		addr = &info->sw->pr;

	अगर (ग_लिखो) अणु
		अगर (पढ़ो_only(addr)) अणु
			UNW_DPRINT(0, "unwind.%s: ignoring attempt to write read-only location\n",
				__func__);
		पूर्ण अन्यथा
			*addr = *val;
	पूर्ण अन्यथा
		*val = *addr;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(unw_access_pr);


/* Routines to manipulate the state stack.  */

अटल अंतरभूत व्योम
push (काष्ठा unw_state_record *sr)
अणु
	काष्ठा unw_reg_state *rs;

	rs = alloc_reg_state();
	अगर (!rs) अणु
		prपूर्णांकk(KERN_ERR "unwind: cannot stack reg state!\n");
		वापस;
	पूर्ण
	स_नकल(rs, &sr->curr, माप(*rs));
	sr->curr.next = rs;
पूर्ण

अटल व्योम
pop (काष्ठा unw_state_record *sr)
अणु
	काष्ठा unw_reg_state *rs = sr->curr.next;

	अगर (!rs) अणु
		prपूर्णांकk(KERN_ERR "unwind: stack underflow!\n");
		वापस;
	पूर्ण
	स_नकल(&sr->curr, rs, माप(*rs));
	मुक्त_reg_state(rs);
पूर्ण

/* Make a copy of the state stack.  Non-recursive to aव्योम stack overflows.  */
अटल काष्ठा unw_reg_state *
dup_state_stack (काष्ठा unw_reg_state *rs)
अणु
	काष्ठा unw_reg_state *copy, *prev = शून्य, *first = शून्य;

	जबतक (rs) अणु
		copy = alloc_reg_state();
		अगर (!copy) अणु
			prपूर्णांकk(KERN_ERR "unwind.dup_state_stack: out of memory\n");
			वापस शून्य;
		पूर्ण
		स_नकल(copy, rs, माप(*copy));
		अगर (first)
			prev->next = copy;
		अन्यथा
			first = copy;
		rs = rs->next;
		prev = copy;
	पूर्ण
	वापस first;
पूर्ण

/* Free all stacked रेजिस्टर states (but not RS itself).  */
अटल व्योम
मुक्त_state_stack (काष्ठा unw_reg_state *rs)
अणु
	काष्ठा unw_reg_state *p, *next;

	क्रम (p = rs->next; p != शून्य; p = next) अणु
		next = p->next;
		मुक्त_reg_state(p);
	पूर्ण
	rs->next = शून्य;
पूर्ण

/* Unwind decoder routines */

अटल क्रमागत unw_रेजिस्टर_index __attribute_स्थिर__
decode_abreg (अचिन्हित अक्षर abreg, पूर्णांक memory)
अणु
	चयन (abreg) अणु
	      हाल 0x04 ... 0x07: वापस UNW_REG_R4 + (abreg - 0x04);
	      हाल 0x22 ... 0x25: वापस UNW_REG_F2 + (abreg - 0x22);
	      हाल 0x30 ... 0x3f: वापस UNW_REG_F16 + (abreg - 0x30);
	      हाल 0x41 ... 0x45: वापस UNW_REG_B1 + (abreg - 0x41);
	      हाल 0x60: वापस UNW_REG_PR;
	      हाल 0x61: वापस UNW_REG_PSP;
	      हाल 0x62: वापस memory ? UNW_REG_PRI_UNAT_MEM : UNW_REG_PRI_UNAT_GR;
	      हाल 0x63: वापस UNW_REG_RP;
	      हाल 0x64: वापस UNW_REG_BSP;
	      हाल 0x65: वापस UNW_REG_BSPSTORE;
	      हाल 0x66: वापस UNW_REG_RNAT;
	      हाल 0x67: वापस UNW_REG_UNAT;
	      हाल 0x68: वापस UNW_REG_FPSR;
	      हाल 0x69: वापस UNW_REG_PFS;
	      हाल 0x6a: वापस UNW_REG_LC;
	      शेष:
		अवरोध;
	पूर्ण
	UNW_DPRINT(0, "unwind.%s: bad abreg=0x%x\n", __func__, abreg);
	वापस UNW_REG_LC;
पूर्ण

अटल व्योम
set_reg (काष्ठा unw_reg_info *reg, क्रमागत unw_where where, पूर्णांक when, अचिन्हित दीर्घ val)
अणु
	reg->val = val;
	reg->where = where;
	अगर (reg->when == UNW_WHEN_NEVER)
		reg->when = when;
पूर्ण

अटल व्योम
alloc_spill_area (अचिन्हित दीर्घ *offp, अचिन्हित दीर्घ regsize,
		  काष्ठा unw_reg_info *lo, काष्ठा unw_reg_info *hi)
अणु
	काष्ठा unw_reg_info *reg;

	क्रम (reg = hi; reg >= lo; --reg) अणु
		अगर (reg->where == UNW_WHERE_SPILL_HOME) अणु
			reg->where = UNW_WHERE_PSPREL;
			*offp -= regsize;
			reg->val = *offp;
		पूर्ण
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम
spill_next_when (काष्ठा unw_reg_info **regp, काष्ठा unw_reg_info *lim, unw_word t)
अणु
	काष्ठा unw_reg_info *reg;

	क्रम (reg = *regp; reg <= lim; ++reg) अणु
		अगर (reg->where == UNW_WHERE_SPILL_HOME) अणु
			reg->when = t;
			*regp = reg + 1;
			वापस;
		पूर्ण
	पूर्ण
	UNW_DPRINT(0, "unwind.%s: excess spill!\n",  __func__);
पूर्ण

अटल अंतरभूत व्योम
finish_prologue (काष्ठा unw_state_record *sr)
अणु
	काष्ठा unw_reg_info *reg;
	अचिन्हित दीर्घ off;
	पूर्णांक i;

	/*
	 * First, resolve implicit रेजिस्टर save locations (see Section "11.4.2.3 Rules
	 * क्रम Using Unwind Descriptors", rule 3):
	 */
	क्रम (i = 0; i < (पूर्णांक) ARRAY_SIZE(unw.save_order); ++i) अणु
		reg = sr->curr.reg + unw.save_order[i];
		अगर (reg->where == UNW_WHERE_GR_SAVE) अणु
			reg->where = UNW_WHERE_GR;
			reg->val = sr->gr_save_loc++;
		पूर्ण
	पूर्ण

	/*
	 * Next, compute when the fp, general, and branch रेजिस्टरs get
	 * saved.  This must come beक्रमe alloc_spill_area() because
	 * we need to know which रेजिस्टरs are spilled to their home
	 * locations.
	 */
	अगर (sr->imask) अणु
		अचिन्हित अक्षर kind, mask = 0, *cp = sr->imask;
		पूर्णांक t;
		अटल स्थिर अचिन्हित अक्षर limit[3] = अणु
			UNW_REG_F31, UNW_REG_R7, UNW_REG_B5
		पूर्ण;
		काष्ठा unw_reg_info *(regs[3]);

		regs[0] = sr->curr.reg + UNW_REG_F2;
		regs[1] = sr->curr.reg + UNW_REG_R4;
		regs[2] = sr->curr.reg + UNW_REG_B1;

		क्रम (t = 0; t < sr->region_len; ++t) अणु
			अगर ((t & 3) == 0)
				mask = *cp++;
			kind = (mask >> 2*(3-(t & 3))) & 3;
			अगर (kind > 0)
				spill_next_when(&regs[kind - 1], sr->curr.reg + limit[kind - 1],
						sr->region_start + t);
		पूर्ण
	पूर्ण
	/*
	 * Next, lay out the memory stack spill area:
	 */
	अगर (sr->any_spills) अणु
		off = sr->spill_offset;
		alloc_spill_area(&off, 16, sr->curr.reg + UNW_REG_F2, sr->curr.reg + UNW_REG_F31);
		alloc_spill_area(&off,  8, sr->curr.reg + UNW_REG_B1, sr->curr.reg + UNW_REG_B5);
		alloc_spill_area(&off,  8, sr->curr.reg + UNW_REG_R4, sr->curr.reg + UNW_REG_R7);
	पूर्ण
पूर्ण

/*
 * Region header descriptors.
 */

अटल व्योम
desc_prologue (पूर्णांक body, unw_word rlen, अचिन्हित अक्षर mask, अचिन्हित अक्षर grsave,
	       काष्ठा unw_state_record *sr)
अणु
	पूर्णांक i, region_start;

	अगर (!(sr->in_body || sr->first_region))
		finish_prologue(sr);
	sr->first_region = 0;

	/* check अगर we're करोne: */
	अगर (sr->when_target < sr->region_start + sr->region_len) अणु
		sr->करोne = 1;
		वापस;
	पूर्ण

	region_start = sr->region_start + sr->region_len;

	क्रम (i = 0; i < sr->epilogue_count; ++i)
		pop(sr);
	sr->epilogue_count = 0;
	sr->epilogue_start = UNW_WHEN_NEVER;

	sr->region_start = region_start;
	sr->region_len = rlen;
	sr->in_body = body;

	अगर (!body) अणु
		push(sr);

		क्रम (i = 0; i < 4; ++i) अणु
			अगर (mask & 0x8)
				set_reg(sr->curr.reg + unw.save_order[i], UNW_WHERE_GR,
					sr->region_start + sr->region_len - 1, grsave++);
			mask <<= 1;
		पूर्ण
		sr->gr_save_loc = grsave;
		sr->any_spills = 0;
		sr->imask = शून्य;
		sr->spill_offset = 0x10;	/* शेष to psp+16 */
	पूर्ण
पूर्ण

/*
 * Prologue descriptors.
 */

अटल अंतरभूत व्योम
desc_abi (अचिन्हित अक्षर abi, अचिन्हित अक्षर context, काष्ठा unw_state_record *sr)
अणु
	अगर (abi == 3 && context == 'i') अणु
		sr->flags |= UNW_FLAG_INTERRUPT_FRAME;
		UNW_DPRINT(3, "unwind.%s: interrupt frame\n",  __func__);
	पूर्ण
	अन्यथा
		UNW_DPRINT(0, "unwind%s: ignoring unwabi(abi=0x%x,context=0x%x)\n",
				__func__, abi, context);
पूर्ण

अटल अंतरभूत व्योम
desc_br_gr (अचिन्हित अक्षर brmask, अचिन्हित अक्षर gr, काष्ठा unw_state_record *sr)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 5; ++i) अणु
		अगर (brmask & 1)
			set_reg(sr->curr.reg + UNW_REG_B1 + i, UNW_WHERE_GR,
				sr->region_start + sr->region_len - 1, gr++);
		brmask >>= 1;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम
desc_br_mem (अचिन्हित अक्षर brmask, काष्ठा unw_state_record *sr)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 5; ++i) अणु
		अगर (brmask & 1) अणु
			set_reg(sr->curr.reg + UNW_REG_B1 + i, UNW_WHERE_SPILL_HOME,
				sr->region_start + sr->region_len - 1, 0);
			sr->any_spills = 1;
		पूर्ण
		brmask >>= 1;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम
desc_frgr_mem (अचिन्हित अक्षर grmask, unw_word frmask, काष्ठा unw_state_record *sr)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 4; ++i) अणु
		अगर ((grmask & 1) != 0) अणु
			set_reg(sr->curr.reg + UNW_REG_R4 + i, UNW_WHERE_SPILL_HOME,
				sr->region_start + sr->region_len - 1, 0);
			sr->any_spills = 1;
		पूर्ण
		grmask >>= 1;
	पूर्ण
	क्रम (i = 0; i < 20; ++i) अणु
		अगर ((frmask & 1) != 0) अणु
			पूर्णांक base = (i < 4) ? UNW_REG_F2 : UNW_REG_F16 - 4;
			set_reg(sr->curr.reg + base + i, UNW_WHERE_SPILL_HOME,
				sr->region_start + sr->region_len - 1, 0);
			sr->any_spills = 1;
		पूर्ण
		frmask >>= 1;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम
desc_fr_mem (अचिन्हित अक्षर frmask, काष्ठा unw_state_record *sr)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 4; ++i) अणु
		अगर ((frmask & 1) != 0) अणु
			set_reg(sr->curr.reg + UNW_REG_F2 + i, UNW_WHERE_SPILL_HOME,
				sr->region_start + sr->region_len - 1, 0);
			sr->any_spills = 1;
		पूर्ण
		frmask >>= 1;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम
desc_gr_gr (अचिन्हित अक्षर grmask, अचिन्हित अक्षर gr, काष्ठा unw_state_record *sr)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 4; ++i) अणु
		अगर ((grmask & 1) != 0)
			set_reg(sr->curr.reg + UNW_REG_R4 + i, UNW_WHERE_GR,
				sr->region_start + sr->region_len - 1, gr++);
		grmask >>= 1;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम
desc_gr_mem (अचिन्हित अक्षर grmask, काष्ठा unw_state_record *sr)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 4; ++i) अणु
		अगर ((grmask & 1) != 0) अणु
			set_reg(sr->curr.reg + UNW_REG_R4 + i, UNW_WHERE_SPILL_HOME,
				sr->region_start + sr->region_len - 1, 0);
			sr->any_spills = 1;
		पूर्ण
		grmask >>= 1;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम
desc_mem_stack_f (unw_word t, unw_word size, काष्ठा unw_state_record *sr)
अणु
	set_reg(sr->curr.reg + UNW_REG_PSP, UNW_WHERE_NONE,
		sr->region_start + min_t(पूर्णांक, t, sr->region_len - 1), 16*size);
पूर्ण

अटल अंतरभूत व्योम
desc_mem_stack_v (unw_word t, काष्ठा unw_state_record *sr)
अणु
	sr->curr.reg[UNW_REG_PSP].when = sr->region_start + min_t(पूर्णांक, t, sr->region_len - 1);
पूर्ण

अटल अंतरभूत व्योम
desc_reg_gr (अचिन्हित अक्षर reg, अचिन्हित अक्षर dst, काष्ठा unw_state_record *sr)
अणु
	set_reg(sr->curr.reg + reg, UNW_WHERE_GR, sr->region_start + sr->region_len - 1, dst);
पूर्ण

अटल अंतरभूत व्योम
desc_reg_psprel (अचिन्हित अक्षर reg, unw_word pspoff, काष्ठा unw_state_record *sr)
अणु
	set_reg(sr->curr.reg + reg, UNW_WHERE_PSPREL, sr->region_start + sr->region_len - 1,
		0x10 - 4*pspoff);
पूर्ण

अटल अंतरभूत व्योम
desc_reg_sprel (अचिन्हित अक्षर reg, unw_word spoff, काष्ठा unw_state_record *sr)
अणु
	set_reg(sr->curr.reg + reg, UNW_WHERE_SPREL, sr->region_start + sr->region_len - 1,
		4*spoff);
पूर्ण

अटल अंतरभूत व्योम
desc_rp_br (अचिन्हित अक्षर dst, काष्ठा unw_state_record *sr)
अणु
	sr->वापस_link_reg = dst;
पूर्ण

अटल अंतरभूत व्योम
desc_reg_when (अचिन्हित अक्षर regnum, unw_word t, काष्ठा unw_state_record *sr)
अणु
	काष्ठा unw_reg_info *reg = sr->curr.reg + regnum;

	अगर (reg->where == UNW_WHERE_NONE)
		reg->where = UNW_WHERE_GR_SAVE;
	reg->when = sr->region_start + min_t(पूर्णांक, t, sr->region_len - 1);
पूर्ण

अटल अंतरभूत व्योम
desc_spill_base (unw_word pspoff, काष्ठा unw_state_record *sr)
अणु
	sr->spill_offset = 0x10 - 4*pspoff;
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर *
desc_spill_mask (अचिन्हित अक्षर *imaskp, काष्ठा unw_state_record *sr)
अणु
	sr->imask = imaskp;
	वापस imaskp + (2*sr->region_len + 7)/8;
पूर्ण

/*
 * Body descriptors.
 */
अटल अंतरभूत व्योम
desc_epilogue (unw_word t, unw_word ecount, काष्ठा unw_state_record *sr)
अणु
	sr->epilogue_start = sr->region_start + sr->region_len - 1 - t;
	sr->epilogue_count = ecount + 1;
पूर्ण

अटल अंतरभूत व्योम
desc_copy_state (unw_word label, काष्ठा unw_state_record *sr)
अणु
	काष्ठा unw_labeled_state *ls;

	क्रम (ls = sr->labeled_states; ls; ls = ls->next) अणु
		अगर (ls->label == label) अणु
			मुक्त_state_stack(&sr->curr);
			स_नकल(&sr->curr, &ls->saved_state, माप(sr->curr));
			sr->curr.next = dup_state_stack(ls->saved_state.next);
			वापस;
		पूर्ण
	पूर्ण
	prपूर्णांकk(KERN_ERR "unwind: failed to find state labeled 0x%lx\n", label);
पूर्ण

अटल अंतरभूत व्योम
desc_label_state (unw_word label, काष्ठा unw_state_record *sr)
अणु
	काष्ठा unw_labeled_state *ls;

	ls = alloc_labeled_state();
	अगर (!ls) अणु
		prपूर्णांकk(KERN_ERR "unwind.desc_label_state(): out of memory\n");
		वापस;
	पूर्ण
	ls->label = label;
	स_नकल(&ls->saved_state, &sr->curr, माप(ls->saved_state));
	ls->saved_state.next = dup_state_stack(sr->curr.next);

	/* insert पूर्णांकo list of labeled states: */
	ls->next = sr->labeled_states;
	sr->labeled_states = ls;
पूर्ण

/*
 * General descriptors.
 */

अटल अंतरभूत पूर्णांक
desc_is_active (अचिन्हित अक्षर qp, unw_word t, काष्ठा unw_state_record *sr)
अणु
	अगर (sr->when_target <= sr->region_start + min_t(पूर्णांक, t, sr->region_len - 1))
		वापस 0;
	अगर (qp > 0) अणु
		अगर ((sr->pr_val & (1UL << qp)) == 0)
			वापस 0;
		sr->pr_mask |= (1UL << qp);
	पूर्ण
	वापस 1;
पूर्ण

अटल अंतरभूत व्योम
desc_restore_p (अचिन्हित अक्षर qp, unw_word t, अचिन्हित अक्षर abreg, काष्ठा unw_state_record *sr)
अणु
	काष्ठा unw_reg_info *r;

	अगर (!desc_is_active(qp, t, sr))
		वापस;

	r = sr->curr.reg + decode_abreg(abreg, 0);
	r->where = UNW_WHERE_NONE;
	r->when = UNW_WHEN_NEVER;
	r->val = 0;
पूर्ण

अटल अंतरभूत व्योम
desc_spill_reg_p (अचिन्हित अक्षर qp, unw_word t, अचिन्हित अक्षर abreg, अचिन्हित अक्षर x,
		     अचिन्हित अक्षर ytreg, काष्ठा unw_state_record *sr)
अणु
	क्रमागत unw_where where = UNW_WHERE_GR;
	काष्ठा unw_reg_info *r;

	अगर (!desc_is_active(qp, t, sr))
		वापस;

	अगर (x)
		where = UNW_WHERE_BR;
	अन्यथा अगर (ytreg & 0x80)
		where = UNW_WHERE_FR;

	r = sr->curr.reg + decode_abreg(abreg, 0);
	r->where = where;
	r->when = sr->region_start + min_t(पूर्णांक, t, sr->region_len - 1);
	r->val = (ytreg & 0x7f);
पूर्ण

अटल अंतरभूत व्योम
desc_spill_psprel_p (अचिन्हित अक्षर qp, unw_word t, अचिन्हित अक्षर abreg, unw_word pspoff,
		     काष्ठा unw_state_record *sr)
अणु
	काष्ठा unw_reg_info *r;

	अगर (!desc_is_active(qp, t, sr))
		वापस;

	r = sr->curr.reg + decode_abreg(abreg, 1);
	r->where = UNW_WHERE_PSPREL;
	r->when = sr->region_start + min_t(पूर्णांक, t, sr->region_len - 1);
	r->val = 0x10 - 4*pspoff;
पूर्ण

अटल अंतरभूत व्योम
desc_spill_sprel_p (अचिन्हित अक्षर qp, unw_word t, अचिन्हित अक्षर abreg, unw_word spoff,
		       काष्ठा unw_state_record *sr)
अणु
	काष्ठा unw_reg_info *r;

	अगर (!desc_is_active(qp, t, sr))
		वापस;

	r = sr->curr.reg + decode_abreg(abreg, 1);
	r->where = UNW_WHERE_SPREL;
	r->when = sr->region_start + min_t(पूर्णांक, t, sr->region_len - 1);
	r->val = 4*spoff;
पूर्ण

#घोषणा UNW_DEC_BAD_CODE(code)			prपूर्णांकk(KERN_ERR "unwind: unknown code 0x%02x\n", \
						       code);

/*
 * region headers:
 */
#घोषणा UNW_DEC_PROLOGUE_GR(fmt,r,m,gr,arg)	desc_prologue(0,r,m,gr,arg)
#घोषणा UNW_DEC_PROLOGUE(fmt,b,r,arg)		desc_prologue(b,r,0,32,arg)
/*
 * prologue descriptors:
 */
#घोषणा UNW_DEC_ABI(fmt,a,c,arg)		desc_abi(a,c,arg)
#घोषणा UNW_DEC_BR_GR(fmt,b,g,arg)		desc_br_gr(b,g,arg)
#घोषणा UNW_DEC_BR_MEM(fmt,b,arg)		desc_br_mem(b,arg)
#घोषणा UNW_DEC_FRGR_MEM(fmt,g,f,arg)		desc_frgr_mem(g,f,arg)
#घोषणा UNW_DEC_FR_MEM(fmt,f,arg)		desc_fr_mem(f,arg)
#घोषणा UNW_DEC_GR_GR(fmt,m,g,arg)		desc_gr_gr(m,g,arg)
#घोषणा UNW_DEC_GR_MEM(fmt,m,arg)		desc_gr_mem(m,arg)
#घोषणा UNW_DEC_MEM_STACK_F(fmt,t,s,arg)	desc_mem_stack_f(t,s,arg)
#घोषणा UNW_DEC_MEM_STACK_V(fmt,t,arg)		desc_mem_stack_v(t,arg)
#घोषणा UNW_DEC_REG_GR(fmt,r,d,arg)		desc_reg_gr(r,d,arg)
#घोषणा UNW_DEC_REG_PSPREL(fmt,r,o,arg)		desc_reg_psprel(r,o,arg)
#घोषणा UNW_DEC_REG_SPREL(fmt,r,o,arg)		desc_reg_sprel(r,o,arg)
#घोषणा UNW_DEC_REG_WHEN(fmt,r,t,arg)		desc_reg_when(r,t,arg)
#घोषणा UNW_DEC_PRIUNAT_WHEN_GR(fmt,t,arg)	desc_reg_when(UNW_REG_PRI_UNAT_GR,t,arg)
#घोषणा UNW_DEC_PRIUNAT_WHEN_MEM(fmt,t,arg)	desc_reg_when(UNW_REG_PRI_UNAT_MEM,t,arg)
#घोषणा UNW_DEC_PRIUNAT_GR(fmt,r,arg)		desc_reg_gr(UNW_REG_PRI_UNAT_GR,r,arg)
#घोषणा UNW_DEC_PRIUNAT_PSPREL(fmt,o,arg)	desc_reg_psprel(UNW_REG_PRI_UNAT_MEM,o,arg)
#घोषणा UNW_DEC_PRIUNAT_SPREL(fmt,o,arg)	desc_reg_sprel(UNW_REG_PRI_UNAT_MEM,o,arg)
#घोषणा UNW_DEC_RP_BR(fmt,d,arg)		desc_rp_br(d,arg)
#घोषणा UNW_DEC_SPILL_BASE(fmt,o,arg)		desc_spill_base(o,arg)
#घोषणा UNW_DEC_SPILL_MASK(fmt,m,arg)		(m = desc_spill_mask(m,arg))
/*
 * body descriptors:
 */
#घोषणा UNW_DEC_EPILOGUE(fmt,t,c,arg)		desc_epilogue(t,c,arg)
#घोषणा UNW_DEC_COPY_STATE(fmt,l,arg)		desc_copy_state(l,arg)
#घोषणा UNW_DEC_LABEL_STATE(fmt,l,arg)		desc_label_state(l,arg)
/*
 * general unwind descriptors:
 */
#घोषणा UNW_DEC_SPILL_REG_P(f,p,t,a,x,y,arg)	desc_spill_reg_p(p,t,a,x,y,arg)
#घोषणा UNW_DEC_SPILL_REG(f,t,a,x,y,arg)	desc_spill_reg_p(0,t,a,x,y,arg)
#घोषणा UNW_DEC_SPILL_PSPREL_P(f,p,t,a,o,arg)	desc_spill_psprel_p(p,t,a,o,arg)
#घोषणा UNW_DEC_SPILL_PSPREL(f,t,a,o,arg)	desc_spill_psprel_p(0,t,a,o,arg)
#घोषणा UNW_DEC_SPILL_SPREL_P(f,p,t,a,o,arg)	desc_spill_sprel_p(p,t,a,o,arg)
#घोषणा UNW_DEC_SPILL_SPREL(f,t,a,o,arg)	desc_spill_sprel_p(0,t,a,o,arg)
#घोषणा UNW_DEC_RESTORE_P(f,p,t,a,arg)		desc_restore_p(p,t,a,arg)
#घोषणा UNW_DEC_RESTORE(f,t,a,arg)		desc_restore_p(0,t,a,arg)

#समावेश "unwind_decoder.c"


/* Unwind scripts. */

अटल अंतरभूत unw_hash_index_t
hash (अचिन्हित दीर्घ ip)
अणु
	/* magic number = ((वर्ग_मूल(5)-1)/2)*2^64 */
	अटल स्थिर अचिन्हित दीर्घ hashmagic = 0x9e3779b97f4a7c16UL;

	वापस (ip >> 4) * hashmagic >> (64 - UNW_LOG_HASH_SIZE);
पूर्ण

अटल अंतरभूत दीर्घ
cache_match (काष्ठा unw_script *script, अचिन्हित दीर्घ ip, अचिन्हित दीर्घ pr)
अणु
	पढ़ो_lock(&script->lock);
	अगर (ip == script->ip && ((pr ^ script->pr_val) & script->pr_mask) == 0)
		/* keep the पढ़ो lock... */
		वापस 1;
	पढ़ो_unlock(&script->lock);
	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा unw_script *
script_lookup (काष्ठा unw_frame_info *info)
अणु
	काष्ठा unw_script *script = unw.cache + info->hपूर्णांक;
	अचिन्हित लघु index;
	अचिन्हित दीर्घ ip, pr;

	अगर (UNW_DEBUG_ON(0))
		वापस शून्य;	/* Always regenerate scripts in debug mode */

	STAT(++unw.stat.cache.lookups);

	ip = info->ip;
	pr = info->pr;

	अगर (cache_match(script, ip, pr)) अणु
		STAT(++unw.stat.cache.hपूर्णांकed_hits);
		वापस script;
	पूर्ण

	index = unw.hash[hash(ip)];
	अगर (index >= UNW_CACHE_SIZE)
		वापस शून्य;

	script = unw.cache + index;
	जबतक (1) अणु
		अगर (cache_match(script, ip, pr)) अणु
			/* update hपूर्णांक; no locking required as single-word ग_लिखोs are atomic */
			STAT(++unw.stat.cache.normal_hits);
			unw.cache[info->prev_script].hपूर्णांक = script - unw.cache;
			वापस script;
		पूर्ण
		अगर (script->coll_chain >= UNW_HASH_SIZE)
			वापस शून्य;
		script = unw.cache + script->coll_chain;
		STAT(++unw.stat.cache.collision_chain_traversals);
	पूर्ण
पूर्ण

/*
 * On वापसing, a ग_लिखो lock क्रम the SCRIPT is still being held.
 */
अटल अंतरभूत काष्ठा unw_script *
script_new (अचिन्हित दीर्घ ip)
अणु
	काष्ठा unw_script *script, *prev, *पंचांगp;
	unw_hash_index_t index;
	अचिन्हित लघु head;

	STAT(++unw.stat.script.news);

	/*
	 * Can't (easily) use cmpxchg() here because of ABA problem
	 * that is पूर्णांकrinsic in cmpxchg()...
	 */
	head = unw.lru_head;
	script = unw.cache + head;
	unw.lru_head = script->lru_chain;

	/*
	 * We'd deadlock here अगर we पूर्णांकerrupted a thपढ़ो that is holding a पढ़ो lock on
	 * script->lock.  Thus, अगर the ग_लिखो_trylock() fails, we simply bail out.  The
	 * alternative would be to disable पूर्णांकerrupts whenever we hold a पढ़ो-lock, but
	 * that seems silly.
	 */
	अगर (!ग_लिखो_trylock(&script->lock))
		वापस शून्य;

	/* re-insert script at the tail of the LRU chain: */
	unw.cache[unw.lru_tail].lru_chain = head;
	unw.lru_tail = head;

	/* हटाओ the old script from the hash table (अगर it's there): */
	अगर (script->ip) अणु
		index = hash(script->ip);
		पंचांगp = unw.cache + unw.hash[index];
		prev = शून्य;
		जबतक (1) अणु
			अगर (पंचांगp == script) अणु
				अगर (prev)
					prev->coll_chain = पंचांगp->coll_chain;
				अन्यथा
					unw.hash[index] = पंचांगp->coll_chain;
				अवरोध;
			पूर्ण अन्यथा
				prev = पंचांगp;
			अगर (पंचांगp->coll_chain >= UNW_CACHE_SIZE)
			/* old script wasn't in the hash-table */
				अवरोध;
			पंचांगp = unw.cache + पंचांगp->coll_chain;
		पूर्ण
	पूर्ण

	/* enter new script in the hash table */
	index = hash(ip);
	script->coll_chain = unw.hash[index];
	unw.hash[index] = script - unw.cache;

	script->ip = ip;	/* set new IP जबतक we're holding the locks */

	STAT(अगर (script->coll_chain < UNW_CACHE_SIZE) ++unw.stat.script.collisions);

	script->flags = 0;
	script->hपूर्णांक = 0;
	script->count = 0;
	वापस script;
पूर्ण

अटल व्योम
script_finalize (काष्ठा unw_script *script, काष्ठा unw_state_record *sr)
अणु
	script->pr_mask = sr->pr_mask;
	script->pr_val = sr->pr_val;
	/*
	 * We could करोwn-grade our ग_लिखो-lock on script->lock here but
	 * the rwlock API करोesn't offer atomic lock करोwngrading, so
	 * we'll just keep the ग_लिखो-lock and release it later when
	 * we're करोne using the script.
	 */
पूर्ण

अटल अंतरभूत व्योम
script_emit (काष्ठा unw_script *script, काष्ठा unw_insn insn)
अणु
	अगर (script->count >= UNW_MAX_SCRIPT_LEN) अणु
		UNW_DPRINT(0, "unwind.%s: script exceeds maximum size of %u instructions!\n",
			__func__, UNW_MAX_SCRIPT_LEN);
		वापस;
	पूर्ण
	script->insn[script->count++] = insn;
पूर्ण

अटल अंतरभूत व्योम
emit_nat_info (काष्ठा unw_state_record *sr, पूर्णांक i, काष्ठा unw_script *script)
अणु
	काष्ठा unw_reg_info *r = sr->curr.reg + i;
	क्रमागत unw_insn_opcode opc;
	काष्ठा unw_insn insn;
	अचिन्हित दीर्घ val = 0;

	चयन (r->where) अणु
	      हाल UNW_WHERE_GR:
		अगर (r->val >= 32) अणु
			/* रेजिस्टर got spilled to a stacked रेजिस्टर */
			opc = UNW_INSN_SETNAT_TYPE;
			val = UNW_NAT_REGSTK;
		पूर्ण अन्यथा
			/* रेजिस्टर got spilled to a scratch रेजिस्टर */
			opc = UNW_INSN_SETNAT_MEMSTK;
		अवरोध;

	      हाल UNW_WHERE_FR:
		opc = UNW_INSN_SETNAT_TYPE;
		val = UNW_NAT_VAL;
		अवरोध;

	      हाल UNW_WHERE_BR:
		opc = UNW_INSN_SETNAT_TYPE;
		val = UNW_NAT_NONE;
		अवरोध;

	      हाल UNW_WHERE_PSPREL:
	      हाल UNW_WHERE_SPREL:
		opc = UNW_INSN_SETNAT_MEMSTK;
		अवरोध;

	      शेष:
		UNW_DPRINT(0, "unwind.%s: don't know how to emit nat info for where = %u\n",
			   __func__, r->where);
		वापस;
	पूर्ण
	insn.opc = opc;
	insn.dst = unw.preg_index[i];
	insn.val = val;
	script_emit(script, insn);
पूर्ण

अटल व्योम
compile_reg (काष्ठा unw_state_record *sr, पूर्णांक i, काष्ठा unw_script *script)
अणु
	काष्ठा unw_reg_info *r = sr->curr.reg + i;
	क्रमागत unw_insn_opcode opc;
	अचिन्हित दीर्घ val, rval;
	काष्ठा unw_insn insn;
	दीर्घ need_nat_info;

	अगर (r->where == UNW_WHERE_NONE || r->when >= sr->when_target)
		वापस;

	opc = UNW_INSN_MOVE;
	val = rval = r->val;
	need_nat_info = (i >= UNW_REG_R4 && i <= UNW_REG_R7);

	चयन (r->where) अणु
	      हाल UNW_WHERE_GR:
		अगर (rval >= 32) अणु
			opc = UNW_INSN_MOVE_STACKED;
			val = rval - 32;
		पूर्ण अन्यथा अगर (rval >= 4 && rval <= 7) अणु
			अगर (need_nat_info) अणु
				opc = UNW_INSN_MOVE2;
				need_nat_info = 0;
			पूर्ण
			val = unw.preg_index[UNW_REG_R4 + (rval - 4)];
		पूर्ण अन्यथा अगर (rval == 0) अणु
			opc = UNW_INSN_MOVE_CONST;
			val = 0;
		पूर्ण अन्यथा अणु
			/* रेजिस्टर got spilled to a scratch रेजिस्टर */
			opc = UNW_INSN_MOVE_SCRATCH;
			val = pt_regs_off(rval);
		पूर्ण
		अवरोध;

	      हाल UNW_WHERE_FR:
		अगर (rval <= 5)
			val = unw.preg_index[UNW_REG_F2  + (rval -  2)];
		अन्यथा अगर (rval >= 16 && rval <= 31)
			val = unw.preg_index[UNW_REG_F16 + (rval - 16)];
		अन्यथा अणु
			opc = UNW_INSN_MOVE_SCRATCH;
			अगर (rval <= 11)
				val = दुरत्व(काष्ठा pt_regs, f6) + 16*(rval - 6);
			अन्यथा
				UNW_DPRINT(0, "unwind.%s: kernel may not touch f%lu\n",
					   __func__, rval);
		पूर्ण
		अवरोध;

	      हाल UNW_WHERE_BR:
		अगर (rval >= 1 && rval <= 5)
			val = unw.preg_index[UNW_REG_B1 + (rval - 1)];
		अन्यथा अणु
			opc = UNW_INSN_MOVE_SCRATCH;
			अगर (rval == 0)
				val = दुरत्व(काष्ठा pt_regs, b0);
			अन्यथा अगर (rval == 6)
				val = दुरत्व(काष्ठा pt_regs, b6);
			अन्यथा
				val = दुरत्व(काष्ठा pt_regs, b7);
		पूर्ण
		अवरोध;

	      हाल UNW_WHERE_SPREL:
		opc = UNW_INSN_ADD_SP;
		अवरोध;

	      हाल UNW_WHERE_PSPREL:
		opc = UNW_INSN_ADD_PSP;
		अवरोध;

	      शेष:
		UNW_DPRINT(0, "unwind%s: register %u has unexpected `where' value of %u\n",
			   __func__, i, r->where);
		अवरोध;
	पूर्ण
	insn.opc = opc;
	insn.dst = unw.preg_index[i];
	insn.val = val;
	script_emit(script, insn);
	अगर (need_nat_info)
		emit_nat_info(sr, i, script);

	अगर (i == UNW_REG_PSP) अणु
		/*
		 * info->psp must contain the _value_ of the previous
		 * sp, not it's save location.  We get this by
		 * dereferencing the value we just stored in
		 * info->psp:
		 */
		insn.opc = UNW_INSN_LOAD;
		insn.dst = insn.val = unw.preg_index[UNW_REG_PSP];
		script_emit(script, insn);
	पूर्ण
पूर्ण

अटल अंतरभूत स्थिर काष्ठा unw_table_entry *
lookup (काष्ठा unw_table *table, अचिन्हित दीर्घ rel_ip)
अणु
	स्थिर काष्ठा unw_table_entry *e = शून्य;
	अचिन्हित दीर्घ lo, hi, mid;

	/* करो a binary search क्रम right entry: */
	क्रम (lo = 0, hi = table->length; lo < hi; ) अणु
		mid = (lo + hi) / 2;
		e = &table->array[mid];
		अगर (rel_ip < e->start_offset)
			hi = mid;
		अन्यथा अगर (rel_ip >= e->end_offset)
			lo = mid + 1;
		अन्यथा
			अवरोध;
	पूर्ण
	अगर (rel_ip < e->start_offset || rel_ip >= e->end_offset)
		वापस शून्य;
	वापस e;
पूर्ण

/*
 * Build an unwind script that unwinds from state OLD_STATE to the
 * entrypoपूर्णांक of the function that called OLD_STATE.
 */
अटल अंतरभूत काष्ठा unw_script *
build_script (काष्ठा unw_frame_info *info)
अणु
	स्थिर काष्ठा unw_table_entry *e = शून्य;
	काष्ठा unw_script *script = शून्य;
	काष्ठा unw_labeled_state *ls, *next;
	अचिन्हित दीर्घ ip = info->ip;
	काष्ठा unw_state_record sr;
	काष्ठा unw_table *table, *prev;
	काष्ठा unw_reg_info *r;
	काष्ठा unw_insn insn;
	u8 *dp, *desc_end;
	u64 hdr;
	पूर्णांक i;
	STAT(अचिन्हित दीर्घ start, parse_start;)

	STAT(++unw.stat.script.builds; start = ia64_get_itc());

	/* build state record */
	स_रखो(&sr, 0, माप(sr));
	क्रम (r = sr.curr.reg; r < sr.curr.reg + UNW_NUM_REGS; ++r)
		r->when = UNW_WHEN_NEVER;
	sr.pr_val = info->pr;

	UNW_DPRINT(3, "unwind.%s: ip 0x%lx\n", __func__, ip);
	script = script_new(ip);
	अगर (!script) अणु
		UNW_DPRINT(0, "unwind.%s: failed to create unwind script\n",  __func__);
		STAT(unw.stat.script.build_समय += ia64_get_itc() - start);
		वापस शून्य;
	पूर्ण
	unw.cache[info->prev_script].hपूर्णांक = script - unw.cache;

	/* search the kernels and the modules' unwind tables क्रम IP: */

	STAT(parse_start = ia64_get_itc());

	prev = शून्य;
	क्रम (table = unw.tables; table; table = table->next) अणु
		अगर (ip >= table->start && ip < table->end) अणु
			/*
			 * Leave the kernel unwind table at the very front,
			 * lest moving it अवरोधs some assumption अन्यथाwhere.
			 * Otherwise, move the matching table to the second
			 * position in the list so that traversals can benefit
			 * from commonality in backtrace paths.
			 */
			अगर (prev && prev != unw.tables) अणु
				/* unw is safe - we're alपढ़ोy spinlocked */
				prev->next = table->next;
				table->next = unw.tables->next;
				unw.tables->next = table;
			पूर्ण
			e = lookup(table, ip - table->segment_base);
			अवरोध;
		पूर्ण
		prev = table;
	पूर्ण
	अगर (!e) अणु
		/* no info, वापस शेष unwinder (leaf proc, no mem stack, no saved regs)  */
		UNW_DPRINT(1, "unwind.%s: no unwind info for ip=0x%lx (prev ip=0x%lx)\n",
			__func__, ip, unw.cache[info->prev_script].ip);
		sr.curr.reg[UNW_REG_RP].where = UNW_WHERE_BR;
		sr.curr.reg[UNW_REG_RP].when = -1;
		sr.curr.reg[UNW_REG_RP].val = 0;
		compile_reg(&sr, UNW_REG_RP, script);
		script_finalize(script, &sr);
		STAT(unw.stat.script.parse_समय += ia64_get_itc() - parse_start);
		STAT(unw.stat.script.build_समय += ia64_get_itc() - start);
		वापस script;
	पूर्ण

	sr.when_target = (3*((ip & ~0xfUL) - (table->segment_base + e->start_offset))/16
			  + (ip & 0xfUL));
	hdr = *(u64 *) (table->segment_base + e->info_offset);
	dp =   (u8 *)  (table->segment_base + e->info_offset + 8);
	desc_end = dp + 8*UNW_LENGTH(hdr);

	जबतक (!sr.करोne && dp < desc_end)
		dp = unw_decode(dp, sr.in_body, &sr);

	अगर (sr.when_target > sr.epilogue_start) अणु
		/*
		 * sp has been restored and all values on the memory stack below
		 * psp also have been restored.
		 */
		sr.curr.reg[UNW_REG_PSP].val = 0;
		sr.curr.reg[UNW_REG_PSP].where = UNW_WHERE_NONE;
		sr.curr.reg[UNW_REG_PSP].when = UNW_WHEN_NEVER;
		क्रम (r = sr.curr.reg; r < sr.curr.reg + UNW_NUM_REGS; ++r)
			अगर ((r->where == UNW_WHERE_PSPREL && r->val <= 0x10)
			    || r->where == UNW_WHERE_SPREL)
			अणु
				r->val = 0;
				r->where = UNW_WHERE_NONE;
				r->when = UNW_WHEN_NEVER;
			पूर्ण
	पूर्ण

	script->flags = sr.flags;

	/*
	 * If RP did't get saved, generate entry क्रम the वापस link
	 * रेजिस्टर.
	 */
	अगर (sr.curr.reg[UNW_REG_RP].when >= sr.when_target) अणु
		sr.curr.reg[UNW_REG_RP].where = UNW_WHERE_BR;
		sr.curr.reg[UNW_REG_RP].when = -1;
		sr.curr.reg[UNW_REG_RP].val = sr.वापस_link_reg;
		UNW_DPRINT(1, "unwind.%s: using default for rp at ip=0x%lx where=%d val=0x%lx\n",
			   __func__, ip, sr.curr.reg[UNW_REG_RP].where,
			   sr.curr.reg[UNW_REG_RP].val);
	पूर्ण

#अगर_घोषित UNW_DEBUG
	UNW_DPRINT(1, "unwind.%s: state record for func 0x%lx, t=%u:\n",
		__func__, table->segment_base + e->start_offset, sr.when_target);
	क्रम (r = sr.curr.reg; r < sr.curr.reg + UNW_NUM_REGS; ++r) अणु
		अगर (r->where != UNW_WHERE_NONE || r->when != UNW_WHEN_NEVER) अणु
			UNW_DPRINT(1, "  %s <- ", unw.preg_name[r - sr.curr.reg]);
			चयन (r->where) अणु
			      हाल UNW_WHERE_GR:     UNW_DPRINT(1, "r%lu", r->val); अवरोध;
			      हाल UNW_WHERE_FR:     UNW_DPRINT(1, "f%lu", r->val); अवरोध;
			      हाल UNW_WHERE_BR:     UNW_DPRINT(1, "b%lu", r->val); अवरोध;
			      हाल UNW_WHERE_SPREL:  UNW_DPRINT(1, "[sp+0x%lx]", r->val); अवरोध;
			      हाल UNW_WHERE_PSPREL: UNW_DPRINT(1, "[psp+0x%lx]", r->val); अवरोध;
			      हाल UNW_WHERE_NONE:
				UNW_DPRINT(1, "%s+0x%lx", unw.preg_name[r - sr.curr.reg], r->val);
				अवरोध;

			      शेष:
				UNW_DPRINT(1, "BADWHERE(%d)", r->where);
				अवरोध;
			पूर्ण
			UNW_DPRINT(1, "\t\t%d\n", r->when);
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	STAT(unw.stat.script.parse_समय += ia64_get_itc() - parse_start);

	/* translate state record पूर्णांकo unwinder inकाष्ठाions: */

	/*
	 * First, set psp अगर we're dealing with a fixed-size frame;
	 * subsequent inकाष्ठाions may depend on this value.
	 */
	अगर (sr.when_target > sr.curr.reg[UNW_REG_PSP].when
	    && (sr.curr.reg[UNW_REG_PSP].where == UNW_WHERE_NONE)
	    && sr.curr.reg[UNW_REG_PSP].val != 0) अणु
		/* new psp is sp plus frame size */
		insn.opc = UNW_INSN_ADD;
		insn.dst = दुरत्व(काष्ठा unw_frame_info, psp)/8;
		insn.val = sr.curr.reg[UNW_REG_PSP].val;	/* frame size */
		script_emit(script, insn);
	पूर्ण

	/* determine where the primary UNaT is: */
	अगर (sr.when_target < sr.curr.reg[UNW_REG_PRI_UNAT_GR].when)
		i = UNW_REG_PRI_UNAT_MEM;
	अन्यथा अगर (sr.when_target < sr.curr.reg[UNW_REG_PRI_UNAT_MEM].when)
		i = UNW_REG_PRI_UNAT_GR;
	अन्यथा अगर (sr.curr.reg[UNW_REG_PRI_UNAT_MEM].when > sr.curr.reg[UNW_REG_PRI_UNAT_GR].when)
		i = UNW_REG_PRI_UNAT_MEM;
	अन्यथा
		i = UNW_REG_PRI_UNAT_GR;

	compile_reg(&sr, i, script);

	क्रम (i = UNW_REG_BSP; i < UNW_NUM_REGS; ++i)
		compile_reg(&sr, i, script);

	/* मुक्त labeled रेजिस्टर states & stack: */

	STAT(parse_start = ia64_get_itc());
	क्रम (ls = sr.labeled_states; ls; ls = next) अणु
		next = ls->next;
		मुक्त_state_stack(&ls->saved_state);
		मुक्त_labeled_state(ls);
	पूर्ण
	मुक्त_state_stack(&sr.curr);
	STAT(unw.stat.script.parse_समय += ia64_get_itc() - parse_start);

	script_finalize(script, &sr);
	STAT(unw.stat.script.build_समय += ia64_get_itc() - start);
	वापस script;
पूर्ण

/*
 * Apply the unwinding actions represented by OPS and update SR to
 * reflect the state that existed upon entry to the function that this
 * unwinder represents.
 */
अटल अंतरभूत व्योम
run_script (काष्ठा unw_script *script, काष्ठा unw_frame_info *state)
अणु
	काष्ठा unw_insn *ip, *limit, next_insn;
	अचिन्हित दीर्घ opc, dst, val, off;
	अचिन्हित दीर्घ *s = (अचिन्हित दीर्घ *) state;
	STAT(अचिन्हित दीर्घ start;)

	STAT(++unw.stat.script.runs; start = ia64_get_itc());
	state->flags = script->flags;
	ip = script->insn;
	limit = script->insn + script->count;
	next_insn = *ip;

	जबतक (ip++ < limit) अणु
		opc = next_insn.opc;
		dst = next_insn.dst;
		val = next_insn.val;
		next_insn = *ip;

	  reकरो:
		चयन (opc) अणु
		      हाल UNW_INSN_ADD:
			s[dst] += val;
			अवरोध;

		      हाल UNW_INSN_MOVE2:
			अगर (!s[val])
				जाओ lazy_init;
			s[dst+1] = s[val+1];
			s[dst] = s[val];
			अवरोध;

		      हाल UNW_INSN_MOVE:
			अगर (!s[val])
				जाओ lazy_init;
			s[dst] = s[val];
			अवरोध;

		      हाल UNW_INSN_MOVE_SCRATCH:
			अगर (state->pt) अणु
				s[dst] = (अचिन्हित दीर्घ) get_scratch_regs(state) + val;
			पूर्ण अन्यथा अणु
				s[dst] = 0;
				UNW_DPRINT(0, "unwind.%s: no state->pt, dst=%ld, val=%ld\n",
					   __func__, dst, val);
			पूर्ण
			अवरोध;

		      हाल UNW_INSN_MOVE_CONST:
			अगर (val == 0)
				s[dst] = (अचिन्हित दीर्घ) &unw.r0;
			अन्यथा अणु
				s[dst] = 0;
				UNW_DPRINT(0, "unwind.%s: UNW_INSN_MOVE_CONST bad val=%ld\n",
					   __func__, val);
			पूर्ण
			अवरोध;


		      हाल UNW_INSN_MOVE_STACKED:
			s[dst] = (अचिन्हित दीर्घ) ia64_rse_skip_regs((अचिन्हित दीर्घ *)state->bsp,
								    val);
			अवरोध;

		      हाल UNW_INSN_ADD_PSP:
			s[dst] = state->psp + val;
			अवरोध;

		      हाल UNW_INSN_ADD_SP:
			s[dst] = state->sp + val;
			अवरोध;

		      हाल UNW_INSN_SETNAT_MEMSTK:
			अगर (!state->pri_unat_loc)
				state->pri_unat_loc = &state->sw->caller_unat;
			/* रेजिस्टर off. is a multiple of 8, so the least 3 bits (type) are 0 */
			s[dst+1] = ((अचिन्हित दीर्घ) state->pri_unat_loc - s[dst]) | UNW_NAT_MEMSTK;
			अवरोध;

		      हाल UNW_INSN_SETNAT_TYPE:
			s[dst+1] = val;
			अवरोध;

		      हाल UNW_INSN_LOAD:
#अगर_घोषित UNW_DEBUG
			अगर ((s[val] & (local_cpu_data->unimpl_va_mask | 0x7)) != 0
			    || s[val] < TASK_SIZE)
			अणु
				UNW_DPRINT(0, "unwind.%s: rejecting bad psp=0x%lx\n",
					   __func__, s[val]);
				अवरोध;
			पूर्ण
#पूर्ण_अगर
			s[dst] = *(अचिन्हित दीर्घ *) s[val];
			अवरोध;
		पूर्ण
	पूर्ण
	STAT(unw.stat.script.run_समय += ia64_get_itc() - start);
	वापस;

  lazy_init:
	off = unw.sw_off[val];
	s[val] = (अचिन्हित दीर्घ) state->sw + off;
	अगर (off >= दुरत्व(काष्ठा चयन_stack, r4) && off <= दुरत्व(काष्ठा चयन_stack, r7))
		/*
		 * We're initializing a general रेजिस्टर: init NaT info, too.  Note that
		 * the offset is a multiple of 8 which gives us the 3 bits needed क्रम
		 * the type field.
		 */
		s[val+1] = (दुरत्व(काष्ठा चयन_stack, ar_unat) - off) | UNW_NAT_MEMSTK;
	जाओ reकरो;
पूर्ण

अटल पूर्णांक
find_save_locs (काष्ठा unw_frame_info *info)
अणु
	पूर्णांक have_ग_लिखो_lock = 0;
	काष्ठा unw_script *scr;
	अचिन्हित दीर्घ flags = 0;

	अगर ((info->ip & (local_cpu_data->unimpl_va_mask | 0xf)) || info->ip < TASK_SIZE) अणु
		/* करोn't let obviously bad addresses pollute the cache */
		/* FIXME: should really be level 0 but it occurs too often. KAO */
		UNW_DPRINT(1, "unwind.%s: rejecting bad ip=0x%lx\n", __func__, info->ip);
		info->rp_loc = शून्य;
		वापस -1;
	पूर्ण

	scr = script_lookup(info);
	अगर (!scr) अणु
		spin_lock_irqsave(&unw.lock, flags);
		scr = build_script(info);
		अगर (!scr) अणु
			spin_unlock_irqrestore(&unw.lock, flags);
			UNW_DPRINT(0,
				   "unwind.%s: failed to locate/build unwind script for ip %lx\n",
				   __func__, info->ip);
			वापस -1;
		पूर्ण
		have_ग_लिखो_lock = 1;
	पूर्ण
	info->hपूर्णांक = scr->hपूर्णांक;
	info->prev_script = scr - unw.cache;

	run_script(scr, info);

	अगर (have_ग_लिखो_lock) अणु
		ग_लिखो_unlock(&scr->lock);
		spin_unlock_irqrestore(&unw.lock, flags);
	पूर्ण अन्यथा
		पढ़ो_unlock(&scr->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक
unw_valid(स्थिर काष्ठा unw_frame_info *info, अचिन्हित दीर्घ* p)
अणु
	अचिन्हित दीर्घ loc = (अचिन्हित दीर्घ)p;
	वापस (loc >= info->regstk.limit && loc < info->regstk.top) ||
	       (loc >= info->memstk.top && loc < info->memstk.limit);
पूर्ण

पूर्णांक
unw_unwind (काष्ठा unw_frame_info *info)
अणु
	अचिन्हित दीर्घ prev_ip, prev_sp, prev_bsp;
	अचिन्हित दीर्घ ip, pr, num_regs;
	STAT(अचिन्हित दीर्घ start, flags;)
	पूर्णांक retval;

	STAT(local_irq_save(flags); ++unw.stat.api.unwinds; start = ia64_get_itc());

	prev_ip = info->ip;
	prev_sp = info->sp;
	prev_bsp = info->bsp;

	/* validate the वापस IP poपूर्णांकer */
	अगर (!unw_valid(info, info->rp_loc)) अणु
		/* FIXME: should really be level 0 but it occurs too often. KAO */
		UNW_DPRINT(1, "unwind.%s: failed to locate return link (ip=0x%lx)!\n",
			   __func__, info->ip);
		STAT(unw.stat.api.unwind_समय += ia64_get_itc() - start; local_irq_restore(flags));
		वापस -1;
	पूर्ण
	/* restore the ip */
	ip = info->ip = *info->rp_loc;
	अगर (ip < GATE_ADDR) अणु
		UNW_DPRINT(2, "unwind.%s: reached user-space (ip=0x%lx)\n", __func__, ip);
		STAT(unw.stat.api.unwind_समय += ia64_get_itc() - start; local_irq_restore(flags));
		वापस -1;
	पूर्ण

	/* validate the previous stack frame poपूर्णांकer */
	अगर (!unw_valid(info, info->pfs_loc)) अणु
		UNW_DPRINT(0, "unwind.%s: failed to locate ar.pfs!\n", __func__);
		STAT(unw.stat.api.unwind_समय += ia64_get_itc() - start; local_irq_restore(flags));
		वापस -1;
	पूर्ण
	/* restore the cfm: */
	info->cfm_loc = info->pfs_loc;

	/* restore the bsp: */
	pr = info->pr;
	num_regs = 0;
	अगर ((info->flags & UNW_FLAG_INTERRUPT_FRAME)) अणु
		info->pt = info->sp + 16;
		अगर ((pr & (1UL << PRED_NON_SYSCALL)) != 0)
			num_regs = *info->cfm_loc & 0x7f;		/* size of frame */
		info->pfs_loc =
			(अचिन्हित दीर्घ *) (info->pt + दुरत्व(काष्ठा pt_regs, ar_pfs));
		UNW_DPRINT(3, "unwind.%s: interrupt_frame pt 0x%lx\n", __func__, info->pt);
	पूर्ण अन्यथा
		num_regs = (*info->cfm_loc >> 7) & 0x7f;	/* size of locals */
	info->bsp = (अचिन्हित दीर्घ) ia64_rse_skip_regs((अचिन्हित दीर्घ *) info->bsp, -num_regs);
	अगर (info->bsp < info->regstk.limit || info->bsp > info->regstk.top) अणु
		UNW_DPRINT(0, "unwind.%s: bsp (0x%lx) out of range [0x%lx-0x%lx]\n",
			__func__, info->bsp, info->regstk.limit, info->regstk.top);
		STAT(unw.stat.api.unwind_समय += ia64_get_itc() - start; local_irq_restore(flags));
		वापस -1;
	पूर्ण

	/* restore the sp: */
	info->sp = info->psp;
	अगर (info->sp < info->memstk.top || info->sp > info->memstk.limit) अणु
		UNW_DPRINT(0, "unwind.%s: sp (0x%lx) out of range [0x%lx-0x%lx]\n",
			__func__, info->sp, info->memstk.top, info->memstk.limit);
		STAT(unw.stat.api.unwind_समय += ia64_get_itc() - start; local_irq_restore(flags));
		वापस -1;
	पूर्ण

	अगर (info->ip == prev_ip && info->sp == prev_sp && info->bsp == prev_bsp) अणु
		UNW_DPRINT(0, "unwind.%s: ip, sp, bsp unchanged; stopping here (ip=0x%lx)\n",
			   __func__, ip);
		STAT(unw.stat.api.unwind_समय += ia64_get_itc() - start; local_irq_restore(flags));
		वापस -1;
	पूर्ण

	/* as we unwind, the saved ar.unat becomes the primary unat: */
	info->pri_unat_loc = info->unat_loc;

	/* finally, restore the predicates: */
	unw_get_pr(info, &info->pr);

	retval = find_save_locs(info);
	STAT(unw.stat.api.unwind_समय += ia64_get_itc() - start; local_irq_restore(flags));
	वापस retval;
पूर्ण
EXPORT_SYMBOL(unw_unwind);

पूर्णांक
unw_unwind_to_user (काष्ठा unw_frame_info *info)
अणु
	अचिन्हित दीर्घ ip, sp, pr = info->pr;

	करो अणु
		unw_get_sp(info, &sp);
		अगर ((दीर्घ)((अचिन्हित दीर्घ)info->task + IA64_STK_OFFSET - sp)
		    < IA64_PT_REGS_SIZE) अणु
			UNW_DPRINT(0, "unwind.%s: ran off the top of the kernel stack\n",
				   __func__);
			अवरोध;
		पूर्ण
		अगर (unw_is_पूर्णांकr_frame(info) &&
		    (pr & (1UL << PRED_USER_STACK)))
			वापस 0;
		अगर (unw_get_pr (info, &pr) < 0) अणु
			unw_get_rp(info, &ip);
			UNW_DPRINT(0, "unwind.%s: failed to read "
				   "predicate register (ip=0x%lx)\n",
				__func__, ip);
			वापस -1;
		पूर्ण
	पूर्ण जबतक (unw_unwind(info) >= 0);
	unw_get_ip(info, &ip);
	UNW_DPRINT(0, "unwind.%s: failed to unwind to user-level (ip=0x%lx)\n",
		   __func__, ip);
	वापस -1;
पूर्ण
EXPORT_SYMBOL(unw_unwind_to_user);

अटल व्योम
init_frame_info (काष्ठा unw_frame_info *info, काष्ठा task_काष्ठा *t,
		 काष्ठा चयन_stack *sw, अचिन्हित दीर्घ stktop)
अणु
	अचिन्हित दीर्घ rbslimit, rbstop, stklimit;
	STAT(अचिन्हित दीर्घ start, flags;)

	STAT(local_irq_save(flags); ++unw.stat.api.inits; start = ia64_get_itc());

	/*
	 * Subtle stuff here: we _could_ unwind through the चयन_stack frame but we
	 * करोn't want to करो that because it would be slow as each preserved रेजिस्टर would
	 * have to be processed.  Instead, what we करो here is zero out the frame info and
	 * start the unwind process at the function that created the चयन_stack frame.
	 * When a preserved value in चयन_stack needs to be accessed, run_script() will
	 * initialize the appropriate poपूर्णांकer on demand.
	 */
	स_रखो(info, 0, माप(*info));

	rbslimit = (अचिन्हित दीर्घ) t + IA64_RBS_OFFSET;
	stklimit = (अचिन्हित दीर्घ) t + IA64_STK_OFFSET;

	rbstop   = sw->ar_bspstore;
	अगर (rbstop > stklimit || rbstop < rbslimit)
		rbstop = rbslimit;

	अगर (stktop <= rbstop)
		stktop = rbstop;
	अगर (stktop > stklimit)
		stktop = stklimit;

	info->regstk.limit = rbslimit;
	info->regstk.top   = rbstop;
	info->memstk.limit = stklimit;
	info->memstk.top   = stktop;
	info->task = t;
	info->sw  = sw;
	info->sp = info->psp = stktop;
	info->pr = sw->pr;
	UNW_DPRINT(3, "unwind.%s:\n"
		   "  task   0x%lx\n"
		   "  rbs = [0x%lx-0x%lx)\n"
		   "  stk = [0x%lx-0x%lx)\n"
		   "  pr     0x%lx\n"
		   "  sw     0x%lx\n"
		   "  sp     0x%lx\n",
		   __func__, (अचिन्हित दीर्घ) t, rbslimit, rbstop, stktop, stklimit,
		   info->pr, (अचिन्हित दीर्घ) info->sw, info->sp);
	STAT(unw.stat.api.init_समय += ia64_get_itc() - start; local_irq_restore(flags));
पूर्ण

व्योम
unw_init_frame_info (काष्ठा unw_frame_info *info, काष्ठा task_काष्ठा *t, काष्ठा चयन_stack *sw)
अणु
	अचिन्हित दीर्घ sol;

	init_frame_info(info, t, sw, (अचिन्हित दीर्घ) (sw + 1) - 16);
	info->cfm_loc = &sw->ar_pfs;
	sol = (*info->cfm_loc >> 7) & 0x7f;
	info->bsp = (अचिन्हित दीर्घ) ia64_rse_skip_regs((अचिन्हित दीर्घ *) info->regstk.top, -sol);
	info->ip = sw->b0;
	UNW_DPRINT(3, "unwind.%s:\n"
		   "  bsp    0x%lx\n"
		   "  sol    0x%lx\n"
		   "  ip     0x%lx\n",
		   __func__, info->bsp, sol, info->ip);
	find_save_locs(info);
पूर्ण

EXPORT_SYMBOL(unw_init_frame_info);

व्योम
unw_init_from_blocked_task (काष्ठा unw_frame_info *info, काष्ठा task_काष्ठा *t)
अणु
	काष्ठा चयन_stack *sw = (काष्ठा चयन_stack *) (t->thपढ़ो.ksp + 16);

	UNW_DPRINT(1, "unwind.%s\n", __func__);
	unw_init_frame_info(info, t, sw);
पूर्ण
EXPORT_SYMBOL(unw_init_from_blocked_task);

अटल व्योम
init_unwind_table (काष्ठा unw_table *table, स्थिर अक्षर *name, अचिन्हित दीर्घ segment_base,
		   अचिन्हित दीर्घ gp, स्थिर व्योम *table_start, स्थिर व्योम *table_end)
अणु
	स्थिर काष्ठा unw_table_entry *start = table_start, *end = table_end;

	table->name = name;
	table->segment_base = segment_base;
	table->gp = gp;
	table->start = segment_base + start[0].start_offset;
	table->end = segment_base + end[-1].end_offset;
	table->array = start;
	table->length = end - start;
पूर्ण

व्योम *
unw_add_unwind_table (स्थिर अक्षर *name, अचिन्हित दीर्घ segment_base, अचिन्हित दीर्घ gp,
		      स्थिर व्योम *table_start, स्थिर व्योम *table_end)
अणु
	स्थिर काष्ठा unw_table_entry *start = table_start, *end = table_end;
	काष्ठा unw_table *table;
	अचिन्हित दीर्घ flags;

	अगर (end - start <= 0) अणु
		UNW_DPRINT(0, "unwind.%s: ignoring attempt to insert empty unwind table\n",
			   __func__);
		वापस शून्य;
	पूर्ण

	table = kदो_स्मृति(माप(*table), GFP_USER);
	अगर (!table)
		वापस शून्य;

	init_unwind_table(table, name, segment_base, gp, table_start, table_end);

	spin_lock_irqsave(&unw.lock, flags);
	अणु
		/* keep kernel unwind table at the front (it's searched most commonly): */
		table->next = unw.tables->next;
		unw.tables->next = table;
	पूर्ण
	spin_unlock_irqrestore(&unw.lock, flags);

	वापस table;
पूर्ण

व्योम
unw_हटाओ_unwind_table (व्योम *handle)
अणु
	काष्ठा unw_table *table, *prev;
	काष्ठा unw_script *पंचांगp;
	अचिन्हित दीर्घ flags;
	दीर्घ index;

	अगर (!handle) अणु
		UNW_DPRINT(0, "unwind.%s: ignoring attempt to remove non-existent unwind table\n",
			   __func__);
		वापस;
	पूर्ण

	table = handle;
	अगर (table == &unw.kernel_table) अणु
		UNW_DPRINT(0, "unwind.%s: sorry, freeing the kernel's unwind table is a "
			   "no-can-do!\n", __func__);
		वापस;
	पूर्ण

	spin_lock_irqsave(&unw.lock, flags);
	अणु
		/* first, delete the table: */

		क्रम (prev = (काष्ठा unw_table *) &unw.tables; prev; prev = prev->next)
			अगर (prev->next == table)
				अवरोध;
		अगर (!prev) अणु
			UNW_DPRINT(0, "unwind.%s: failed to find unwind table %p\n",
				   __func__, (व्योम *) table);
			spin_unlock_irqrestore(&unw.lock, flags);
			वापस;
		पूर्ण
		prev->next = table->next;
	पूर्ण
	spin_unlock_irqrestore(&unw.lock, flags);

	/* next, हटाओ hash table entries क्रम this table */

	क्रम (index = 0; index < UNW_HASH_SIZE; ++index) अणु
		पंचांगp = unw.cache + unw.hash[index];
		अगर (unw.hash[index] >= UNW_CACHE_SIZE
		    || पंचांगp->ip < table->start || पंचांगp->ip >= table->end)
			जारी;

		ग_लिखो_lock(&पंचांगp->lock);
		अणु
			अगर (पंचांगp->ip >= table->start && पंचांगp->ip < table->end) अणु
				unw.hash[index] = पंचांगp->coll_chain;
				पंचांगp->ip = 0;
			पूर्ण
		पूर्ण
		ग_लिखो_unlock(&पंचांगp->lock);
	पूर्ण

	kमुक्त(table);
पूर्ण

अटल पूर्णांक __init
create_gate_table (व्योम)
अणु
	स्थिर काष्ठा unw_table_entry *entry, *start, *end;
	अचिन्हित दीर्घ *lp, segbase = GATE_ADDR;
	माप_प्रकार info_size, size;
	अक्षर *info;
	Elf64_Phdr *punw = शून्य, *phdr = (Elf64_Phdr *) (GATE_ADDR + GATE_EHDR->e_phoff);
	पूर्णांक i;

	क्रम (i = 0; i < GATE_EHDR->e_phnum; ++i, ++phdr)
		अगर (phdr->p_type == PT_IA_64_UNWIND) अणु
			punw = phdr;
			अवरोध;
		पूर्ण

	अगर (!punw) अणु
		prपूर्णांकk("%s: failed to find gate DSO's unwind table!\n", __func__);
		वापस 0;
	पूर्ण

	start = (स्थिर काष्ठा unw_table_entry *) punw->p_vaddr;
	end = (काष्ठा unw_table_entry *) ((अक्षर *) start + punw->p_memsz);
	size  = 0;

	unw_add_unwind_table("linux-gate.so", segbase, 0, start, end);

	क्रम (entry = start; entry < end; ++entry)
		size += 3*8 + 8 + 8*UNW_LENGTH(*(u64 *) (segbase + entry->info_offset));
	size += 8;	/* reserve space क्रम "end of table" marker */

	unw.gate_table = kदो_स्मृति(size, GFP_KERNEL);
	अगर (!unw.gate_table) अणु
		unw.gate_table_size = 0;
		prपूर्णांकk(KERN_ERR "%s: unable to create unwind data for gate page!\n", __func__);
		वापस 0;
	पूर्ण
	unw.gate_table_size = size;

	lp = unw.gate_table;
	info = (अक्षर *) unw.gate_table + size;

	क्रम (entry = start; entry < end; ++entry, lp += 3) अणु
		info_size = 8 + 8*UNW_LENGTH(*(u64 *) (segbase + entry->info_offset));
		info -= info_size;
		स_नकल(info, (अक्षर *) segbase + entry->info_offset, info_size);

		lp[0] = segbase + entry->start_offset;		/* start */
		lp[1] = segbase + entry->end_offset;		/* end */
		lp[2] = info - (अक्षर *) unw.gate_table;		/* info */
	पूर्ण
	*lp = 0;	/* end-of-table marker */
	वापस 0;
पूर्ण

__initcall(create_gate_table);

व्योम __init
unw_init (व्योम)
अणु
	बाह्य अक्षर __gp[];
	बाह्य व्योम unw_hash_index_t_is_too_narrow (व्योम);
	दीर्घ i, off;

	अगर (8*माप(unw_hash_index_t) < UNW_LOG_HASH_SIZE)
		unw_hash_index_t_is_too_narrow();

	unw.sw_off[unw.preg_index[UNW_REG_PRI_UNAT_GR]] = SW(CALLER_UNAT);
	unw.sw_off[unw.preg_index[UNW_REG_BSPSTORE]] = SW(AR_BSPSTORE);
	unw.sw_off[unw.preg_index[UNW_REG_PFS]] = SW(AR_PFS);
	unw.sw_off[unw.preg_index[UNW_REG_RP]] = SW(B0);
	unw.sw_off[unw.preg_index[UNW_REG_UNAT]] = SW(CALLER_UNAT);
	unw.sw_off[unw.preg_index[UNW_REG_PR]] = SW(PR);
	unw.sw_off[unw.preg_index[UNW_REG_LC]] = SW(AR_LC);
	unw.sw_off[unw.preg_index[UNW_REG_FPSR]] = SW(AR_FPSR);
	क्रम (i = UNW_REG_R4, off = SW(R4); i <= UNW_REG_R7; ++i, off += 8)
		unw.sw_off[unw.preg_index[i]] = off;
	क्रम (i = UNW_REG_B1, off = SW(B1); i <= UNW_REG_B5; ++i, off += 8)
		unw.sw_off[unw.preg_index[i]] = off;
	क्रम (i = UNW_REG_F2, off = SW(F2); i <= UNW_REG_F5; ++i, off += 16)
		unw.sw_off[unw.preg_index[i]] = off;
	क्रम (i = UNW_REG_F16, off = SW(F16); i <= UNW_REG_F31; ++i, off += 16)
		unw.sw_off[unw.preg_index[i]] = off;

	क्रम (i = 0; i < UNW_CACHE_SIZE; ++i) अणु
		अगर (i > 0)
			unw.cache[i].lru_chain = (i - 1);
		unw.cache[i].coll_chain = -1;
		rwlock_init(&unw.cache[i].lock);
	पूर्ण
	unw.lru_head = UNW_CACHE_SIZE - 1;
	unw.lru_tail = 0;

	init_unwind_table(&unw.kernel_table, "kernel", KERNEL_START, (अचिन्हित दीर्घ) __gp,
			  __start_unwind, __end_unwind);
पूर्ण

/*
 * DEPRECATED DEPRECATED DEPRECATED DEPRECATED DEPRECATED DEPRECATED DEPRECATED
 *
 *	This प्रणाली call has been deprecated.  The new and improved way to get
 *	at the kernel's unwind info is via the gate DSO.  The address of the
 *	ELF header क्रम this DSO is passed to user-level via AT_SYSINFO_EHDR.
 *
 * DEPRECATED DEPRECATED DEPRECATED DEPRECATED DEPRECATED DEPRECATED DEPRECATED
 *
 * This प्रणाली call copies the unwind data पूर्णांकo the buffer poपूर्णांकed to by BUF and वापसs
 * the size of the unwind data.  If BUF_SIZE is smaller than the size of the unwind data
 * or अगर BUF is शून्य, nothing is copied, but the प्रणाली call still वापसs the size of the
 * unwind data.
 *
 * The first portion of the unwind data contains an unwind table and rest contains the
 * associated unwind info (in no particular order).  The unwind table consists of a table
 * of entries of the क्रमm:
 *
 *	u64 start;	(64-bit address of start of function)
 *	u64 end;	(64-bit address of start of function)
 *	u64 info;	(BUF-relative offset to unwind info)
 *
 * The end of the unwind table is indicated by an entry with a START address of zero.
 *
 * Please see the IA-64 Software Conventions and Runसमय Architecture manual क्रम details
 * on the क्रमmat of the unwind info.
 *
 * ERRORS
 *	EFAULT	BUF poपूर्णांकs outside your accessible address space.
 */
यंत्रlinkage दीर्घ
sys_getunwind (व्योम __user *buf, माप_प्रकार buf_size)
अणु
	अगर (buf && buf_size >= unw.gate_table_size)
		अगर (copy_to_user(buf, unw.gate_table, unw.gate_table_size) != 0)
			वापस -EFAULT;
	वापस unw.gate_table_size;
पूर्ण
