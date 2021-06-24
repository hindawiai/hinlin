<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Inकाष्ठाion-patching support.
 *
 * Copyright (C) 2003 Hewlett-Packard Co
 *	David Mosberger-Tang <davidm@hpl.hp.com>
 */
#समावेश <linux/init.h>
#समावेश <linux/माला.स>

#समावेश <यंत्र/patch.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/unistd.h>

/*
 * This was adapted from code written by Tony Luck:
 *
 * The 64-bit value in a "movl reg=value" is scattered between the two words of the bundle
 * like this:
 *
 * 6  6         5         4         3         2         1
 * 3210987654321098765432109876543210987654321098765432109876543210
 * ABBBBBBBBBBBBBBBBBBBBBBBCCCCCCCCCCCCCCCCCCDEEEEEFFFFFFFFFGGGGGGG
 *
 * CCCCCCCCCCCCCCCCCCxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
 * xxxxAFFFFFFFFFEEEEEDxGGGGGGGxxxxxxxxxxxxxBBBBBBBBBBBBBBBBBBBBBBB
 */
अटल u64
get_imm64 (u64 insn_addr)
अणु
	u64 *p = (u64 *) (insn_addr & -16);	/* mask out slot number */

	वापस ( (p[1] & 0x0800000000000000UL) << 4)  | /*A*/
		((p[1] & 0x00000000007fffffUL) << 40) | /*B*/
		((p[0] & 0xffffc00000000000UL) >> 24) | /*C*/
		((p[1] & 0x0000100000000000UL) >> 23) | /*D*/
		((p[1] & 0x0003e00000000000UL) >> 29) | /*E*/
		((p[1] & 0x07fc000000000000UL) >> 43) | /*F*/
		((p[1] & 0x000007f000000000UL) >> 36);  /*G*/
पूर्ण

/* Patch inकाष्ठाion with "val" where "mask" has 1 bits. */
व्योम
ia64_patch (u64 insn_addr, u64 mask, u64 val)
अणु
	u64 m0, m1, v0, v1, b0, b1, *b = (u64 *) (insn_addr & -16);
#	define insn_mask ((1UL << 41) - 1)
	अचिन्हित दीर्घ shअगरt;

	b0 = b[0]; b1 = b[1];
	shअगरt = 5 + 41 * (insn_addr % 16); /* 5 bits of ढाँचा, then 3 x 41-bit inकाष्ठाions */
	अगर (shअगरt >= 64) अणु
		m1 = mask << (shअगरt - 64);
		v1 = val << (shअगरt - 64);
	पूर्ण अन्यथा अणु
		m0 = mask << shअगरt; m1 = mask >> (64 - shअगरt);
		v0 = val  << shअगरt; v1 = val >> (64 - shअगरt);
		b[0] = (b0 & ~m0) | (v0 & m0);
	पूर्ण
	b[1] = (b1 & ~m1) | (v1 & m1);
पूर्ण

व्योम
ia64_patch_imm64 (u64 insn_addr, u64 val)
अणु
	/* The assembler may generate offset poपूर्णांकing to either slot 1
	   or slot 2 क्रम a दीर्घ (2-slot) inकाष्ठाion, occupying slots 1
	   and 2.  */
  	insn_addr &= -16UL;
	ia64_patch(insn_addr + 2,
		   0x01fffefe000UL, (  ((val & 0x8000000000000000UL) >> 27) /* bit 63 -> 36 */
				     | ((val & 0x0000000000200000UL) <<  0) /* bit 21 -> 21 */
				     | ((val & 0x00000000001f0000UL) <<  6) /* bit 16 -> 22 */
				     | ((val & 0x000000000000ff80UL) << 20) /* bit  7 -> 27 */
				     | ((val & 0x000000000000007fUL) << 13) /* bit  0 -> 13 */));
	ia64_patch(insn_addr + 1, 0x1ffffffffffUL, val >> 22);
पूर्ण

व्योम
ia64_patch_imm60 (u64 insn_addr, u64 val)
अणु
	/* The assembler may generate offset poपूर्णांकing to either slot 1
	   or slot 2 क्रम a दीर्घ (2-slot) inकाष्ठाion, occupying slots 1
	   and 2.  */
  	insn_addr &= -16UL;
	ia64_patch(insn_addr + 2,
		   0x011ffffe000UL, (  ((val & 0x0800000000000000UL) >> 23) /* bit 59 -> 36 */
				     | ((val & 0x00000000000fffffUL) << 13) /* bit  0 -> 13 */));
	ia64_patch(insn_addr + 1, 0x1fffffffffcUL, val >> 18);
पूर्ण

/*
 * We need someबार to load the physical address of a kernel
 * object.  Often we can convert the भव address to physical
 * at execution समय, but someबार (either क्रम perक्रमmance reasons
 * or during error recovery) we cannot to this.  Patch the marked
 * bundles to load the physical address.
 */
व्योम __init
ia64_patch_vtop (अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	s32 *offp = (s32 *) start;
	u64 ip;

	जबतक (offp < (s32 *) end) अणु
		ip = (u64) offp + *offp;

		/* replace भव address with corresponding physical address: */
		ia64_patch_imm64(ip, ia64_tpa(get_imm64(ip)));
		ia64_fc((व्योम *) ip);
		++offp;
	पूर्ण
	ia64_sync_i();
	ia64_srlz_i();
पूर्ण

/*
 * Disable the RSE workaround by turning the conditional branch
 * that we tagged in each place the workaround was used पूर्णांकo an
 * unconditional branch.
 */
व्योम __init
ia64_patch_rse (अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	s32 *offp = (s32 *) start;
	u64 ip, *b;

	जबतक (offp < (s32 *) end) अणु
		ip = (u64) offp + *offp;

		b = (u64 *)(ip & -16);
		b[1] &= ~0xf800000L;
		ia64_fc((व्योम *) ip);
		++offp;
	पूर्ण
	ia64_sync_i();
	ia64_srlz_i();
पूर्ण

व्योम __init
ia64_patch_mckinley_e9 (अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अटल पूर्णांक first_समय = 1;
	पूर्णांक need_workaround;
	s32 *offp = (s32 *) start;
	u64 *wp;

	need_workaround = (local_cpu_data->family == 0x1f && local_cpu_data->model == 0);

	अगर (first_समय) अणु
		first_समय = 0;
		अगर (need_workaround)
			prपूर्णांकk(KERN_INFO "Leaving McKinley Errata 9 workaround enabled\n");
	पूर्ण
	अगर (need_workaround)
		वापस;

	जबतक (offp < (s32 *) end) अणु
		wp = (u64 *) ia64_imva((अक्षर *) offp + *offp);
		wp[0] = 0x0000000100000011UL; /* nop.m 0; nop.i 0; br.ret.sptk.many b6 */
		wp[1] = 0x0084006880000200UL;
		wp[2] = 0x0000000100000000UL; /* nop.m 0; nop.i 0; nop.i 0 */
		wp[3] = 0x0004000000000200UL;
		ia64_fc(wp); ia64_fc(wp + 2);
		++offp;
	पूर्ण
	ia64_sync_i();
	ia64_srlz_i();
पूर्ण

अटल व्योम __init
patch_fsyscall_table (अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	बाह्य अचिन्हित दीर्घ fsyscall_table[NR_syscalls];
	s32 *offp = (s32 *) start;
	u64 ip;

	जबतक (offp < (s32 *) end) अणु
		ip = (u64) ia64_imva((अक्षर *) offp + *offp);
		ia64_patch_imm64(ip, (u64) fsyscall_table);
		ia64_fc((व्योम *) ip);
		++offp;
	पूर्ण
	ia64_sync_i();
	ia64_srlz_i();
पूर्ण

अटल व्योम __init
patch_brl_fsys_bubble_करोwn (अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	बाह्य अक्षर fsys_bubble_करोwn[];
	s32 *offp = (s32 *) start;
	u64 ip;

	जबतक (offp < (s32 *) end) अणु
		ip = (u64) offp + *offp;
		ia64_patch_imm60((u64) ia64_imva((व्योम *) ip),
				 (u64) (fsys_bubble_करोwn - (ip & -16)) / 16);
		ia64_fc((व्योम *) ip);
		++offp;
	पूर्ण
	ia64_sync_i();
	ia64_srlz_i();
पूर्ण

व्योम __init
ia64_patch_gate (व्योम)
अणु
#	define START(name)	((अचिन्हित दीर्घ) __start_gate_##name##_patchlist)
#	define END(name)	((अचिन्हित दीर्घ)__end_gate_##name##_patchlist)

	patch_fsyscall_table(START(fsyscall), END(fsyscall));
	patch_brl_fsys_bubble_करोwn(START(brl_fsys_bubble_करोwn), END(brl_fsys_bubble_करोwn));
	ia64_patch_vtop(START(vtop), END(vtop));
	ia64_patch_mckinley_e9(START(mckinley_e9), END(mckinley_e9));
पूर्ण

व्योम ia64_patch_phys_stack_reg(अचिन्हित दीर्घ val)
अणु
	s32 * offp = (s32 *) __start___phys_stack_reg_patchlist;
	s32 * end = (s32 *) __end___phys_stack_reg_patchlist;
	u64 ip, mask, imm;

	/* see inकाष्ठाion क्रमmat A4: adds r1 = imm13, r3 */
	mask = (0x3fUL << 27) | (0x7f << 13);
	imm = (((val >> 7) & 0x3f) << 27) | (val & 0x7f) << 13;

	जबतक (offp < end) अणु
		ip = (u64) offp + *offp;
		ia64_patch(ip, mask, imm);
		ia64_fc((व्योम *)ip);
		++offp;
	पूर्ण
	ia64_sync_i();
	ia64_srlz_i();
पूर्ण
