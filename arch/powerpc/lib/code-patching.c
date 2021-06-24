<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright 2008 Michael Ellerman, IBM Corporation.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/kprobes.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/init.h>
#समावेश <linux/mm.h>
#समावेश <linux/cpuhotplug.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>

#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/code-patching.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/inst.h>

अटल पूर्णांक __patch_inकाष्ठाion(काष्ठा ppc_inst *exec_addr, काष्ठा ppc_inst instr,
			       काष्ठा ppc_inst *patch_addr)
अणु
	अगर (!ppc_inst_prefixed(instr)) अणु
		u32 val = ppc_inst_val(instr);

		__put_kernel_nofault(patch_addr, &val, u32, failed);
	पूर्ण अन्यथा अणु
		u64 val = ppc_inst_as_uदीर्घ(instr);

		__put_kernel_nofault(patch_addr, &val, u64, failed);
	पूर्ण

	यंत्र ("dcbst 0, %0; sync; icbi 0,%1; sync; isync" :: "r" (patch_addr),
							    "r" (exec_addr));

	वापस 0;

failed:
	वापस -EFAULT;
पूर्ण

पूर्णांक raw_patch_inकाष्ठाion(काष्ठा ppc_inst *addr, काष्ठा ppc_inst instr)
अणु
	वापस __patch_inकाष्ठाion(addr, instr, addr);
पूर्ण

#अगर_घोषित CONFIG_STRICT_KERNEL_RWX
अटल DEFINE_PER_CPU(काष्ठा vm_काष्ठा *, text_poke_area);

अटल पूर्णांक text_area_cpu_up(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा vm_काष्ठा *area;

	area = get_vm_area(PAGE_SIZE, VM_ALLOC);
	अगर (!area) अणु
		WARN_ONCE(1, "Failed to create text area for cpu %d\n",
			cpu);
		वापस -1;
	पूर्ण
	this_cpu_ग_लिखो(text_poke_area, area);

	वापस 0;
पूर्ण

अटल पूर्णांक text_area_cpu_करोwn(अचिन्हित पूर्णांक cpu)
अणु
	मुक्त_vm_area(this_cpu_पढ़ो(text_poke_area));
	वापस 0;
पूर्ण

/*
 * Run as a late init call. This allows all the boot समय patching to be करोne
 * simply by patching the code, and then we're called here prior to
 * mark_rodata_ro(), which happens after all init calls are run. Although
 * BUG_ON() is rude, in this हाल it should only happen अगर ENOMEM, and we judge
 * it as being preferable to a kernel that will crash later when someone tries
 * to use patch_inकाष्ठाion().
 */
अटल पूर्णांक __init setup_text_poke_area(व्योम)
अणु
	BUG_ON(!cpuhp_setup_state(CPUHP_AP_ONLINE_DYN,
		"powerpc/text_poke:online", text_area_cpu_up,
		text_area_cpu_करोwn));

	वापस 0;
पूर्ण
late_initcall(setup_text_poke_area);

/*
 * This can be called क्रम kernel text or a module.
 */
अटल पूर्णांक map_patch_area(व्योम *addr, अचिन्हित दीर्घ text_poke_addr)
अणु
	अचिन्हित दीर्घ pfn;
	पूर्णांक err;

	अगर (is_vदो_स्मृति_or_module_addr(addr))
		pfn = vदो_स्मृति_to_pfn(addr);
	अन्यथा
		pfn = __pa_symbol(addr) >> PAGE_SHIFT;

	err = map_kernel_page(text_poke_addr, (pfn << PAGE_SHIFT), PAGE_KERNEL);

	pr_devel("Mapped addr %lx with pfn %lx:%d\n", text_poke_addr, pfn, err);
	अगर (err)
		वापस -1;

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक unmap_patch_area(अचिन्हित दीर्घ addr)
अणु
	pte_t *ptep;
	pmd_t *pmdp;
	pud_t *pudp;
	p4d_t *p4dp;
	pgd_t *pgdp;

	pgdp = pgd_offset_k(addr);
	अगर (unlikely(!pgdp))
		वापस -EINVAL;

	p4dp = p4d_offset(pgdp, addr);
	अगर (unlikely(!p4dp))
		वापस -EINVAL;

	pudp = pud_offset(p4dp, addr);
	अगर (unlikely(!pudp))
		वापस -EINVAL;

	pmdp = pmd_offset(pudp, addr);
	अगर (unlikely(!pmdp))
		वापस -EINVAL;

	ptep = pte_offset_kernel(pmdp, addr);
	अगर (unlikely(!ptep))
		वापस -EINVAL;

	pr_devel("clearing mm %p, pte %p, addr %lx\n", &init_mm, ptep, addr);

	/*
	 * In hash, pte_clear flushes the tlb, in radix, we have to
	 */
	pte_clear(&init_mm, addr, ptep);
	flush_tlb_kernel_range(addr, addr + PAGE_SIZE);

	वापस 0;
पूर्ण

अटल पूर्णांक करो_patch_inकाष्ठाion(काष्ठा ppc_inst *addr, काष्ठा ppc_inst instr)
अणु
	पूर्णांक err;
	काष्ठा ppc_inst *patch_addr = शून्य;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ text_poke_addr;
	अचिन्हित दीर्घ kaddr = (अचिन्हित दीर्घ)addr;

	/*
	 * During early early boot patch_inकाष्ठाion is called
	 * when text_poke_area is not पढ़ोy, but we still need
	 * to allow patching. We just करो the plain old patching
	 */
	अगर (!this_cpu_पढ़ो(text_poke_area))
		वापस raw_patch_inकाष्ठाion(addr, instr);

	local_irq_save(flags);

	text_poke_addr = (अचिन्हित दीर्घ)__this_cpu_पढ़ो(text_poke_area)->addr;
	अगर (map_patch_area(addr, text_poke_addr)) अणु
		err = -1;
		जाओ out;
	पूर्ण

	patch_addr = (काष्ठा ppc_inst *)(text_poke_addr + (kaddr & ~PAGE_MASK));

	__patch_inकाष्ठाion(addr, instr, patch_addr);

	err = unmap_patch_area(text_poke_addr);
	अगर (err)
		pr_warn("failed to unmap %lx\n", text_poke_addr);

out:
	local_irq_restore(flags);

	वापस err;
पूर्ण
#अन्यथा /* !CONFIG_STRICT_KERNEL_RWX */

अटल पूर्णांक करो_patch_inकाष्ठाion(काष्ठा ppc_inst *addr, काष्ठा ppc_inst instr)
अणु
	वापस raw_patch_inकाष्ठाion(addr, instr);
पूर्ण

#पूर्ण_अगर /* CONFIG_STRICT_KERNEL_RWX */

पूर्णांक patch_inकाष्ठाion(काष्ठा ppc_inst *addr, काष्ठा ppc_inst instr)
अणु
	/* Make sure we aren't patching a मुक्तd init section */
	अगर (init_mem_is_मुक्त && init_section_contains(addr, 4)) अणु
		pr_debug("Skipping init section patching addr: 0x%px\n", addr);
		वापस 0;
	पूर्ण
	वापस करो_patch_inकाष्ठाion(addr, instr);
पूर्ण
NOKPROBE_SYMBOL(patch_inकाष्ठाion);

पूर्णांक patch_branch(काष्ठा ppc_inst *addr, अचिन्हित दीर्घ target, पूर्णांक flags)
अणु
	काष्ठा ppc_inst instr;

	create_branch(&instr, addr, target, flags);
	वापस patch_inकाष्ठाion(addr, instr);
पूर्ण

bool is_offset_in_branch_range(दीर्घ offset)
अणु
	/*
	 * Powerpc branch inकाष्ठाion is :
	 *
	 *  0         6                 30   31
	 *  +---------+----------------+---+---+
	 *  | opcode  |     LI         |AA |LK |
	 *  +---------+----------------+---+---+
	 *  Where AA = 0 and LK = 0
	 *
	 * LI is a चिन्हित 24 bits पूर्णांकeger. The real branch offset is computed
	 * by: imm32 = SignExtend(LI:'0b00', 32);
	 *
	 * So the maximum क्रमward branch should be:
	 *   (0x007fffff << 2) = 0x01fffffc =  0x1fffffc
	 * The maximum backward branch should be:
	 *   (0xff800000 << 2) = 0xfe000000 = -0x2000000
	 */
	वापस (offset >= -0x2000000 && offset <= 0x1fffffc && !(offset & 0x3));
पूर्ण

/*
 * Helper to check अगर a given inकाष्ठाion is a conditional branch
 * Derived from the conditional checks in analyse_instr()
 */
bool is_conditional_branch(काष्ठा ppc_inst instr)
अणु
	अचिन्हित पूर्णांक opcode = ppc_inst_primary_opcode(instr);

	अगर (opcode == 16)       /* bc, bca, bcl, bcla */
		वापस true;
	अगर (opcode == 19) अणु
		चयन ((ppc_inst_val(instr) >> 1) & 0x3ff) अणु
		हाल 16:        /* bclr, bclrl */
		हाल 528:       /* bcctr, bcctrl */
		हाल 560:       /* bctar, bctarl */
			वापस true;
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण
NOKPROBE_SYMBOL(is_conditional_branch);

पूर्णांक create_branch(काष्ठा ppc_inst *instr,
		  स्थिर काष्ठा ppc_inst *addr,
		  अचिन्हित दीर्घ target, पूर्णांक flags)
अणु
	दीर्घ offset;

	*instr = ppc_inst(0);
	offset = target;
	अगर (! (flags & BRANCH_ABSOLUTE))
		offset = offset - (अचिन्हित दीर्घ)addr;

	/* Check we can represent the target in the inकाष्ठाion क्रमmat */
	अगर (!is_offset_in_branch_range(offset))
		वापस 1;

	/* Mask out the flags and target, so they करोn't step on each other. */
	*instr = ppc_inst(0x48000000 | (flags & 0x3) | (offset & 0x03FFFFFC));

	वापस 0;
पूर्ण

पूर्णांक create_cond_branch(काष्ठा ppc_inst *instr, स्थिर काष्ठा ppc_inst *addr,
		       अचिन्हित दीर्घ target, पूर्णांक flags)
अणु
	दीर्घ offset;

	offset = target;
	अगर (! (flags & BRANCH_ABSOLUTE))
		offset = offset - (अचिन्हित दीर्घ)addr;

	/* Check we can represent the target in the inकाष्ठाion क्रमmat */
	अगर (offset < -0x8000 || offset > 0x7FFF || offset & 0x3)
		वापस 1;

	/* Mask out the flags and target, so they करोn't step on each other. */
	*instr = ppc_inst(0x40000000 | (flags & 0x3FF0003) | (offset & 0xFFFC));

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक branch_opcode(काष्ठा ppc_inst instr)
अणु
	वापस ppc_inst_primary_opcode(instr) & 0x3F;
पूर्ण

अटल पूर्णांक instr_is_branch_अगरorm(काष्ठा ppc_inst instr)
अणु
	वापस branch_opcode(instr) == 18;
पूर्ण

अटल पूर्णांक instr_is_branch_bक्रमm(काष्ठा ppc_inst instr)
अणु
	वापस branch_opcode(instr) == 16;
पूर्ण

पूर्णांक instr_is_relative_branch(काष्ठा ppc_inst instr)
अणु
	अगर (ppc_inst_val(instr) & BRANCH_ABSOLUTE)
		वापस 0;

	वापस instr_is_branch_अगरorm(instr) || instr_is_branch_bक्रमm(instr);
पूर्ण

पूर्णांक instr_is_relative_link_branch(काष्ठा ppc_inst instr)
अणु
	वापस instr_is_relative_branch(instr) && (ppc_inst_val(instr) & BRANCH_SET_LINK);
पूर्ण

अटल अचिन्हित दीर्घ branch_अगरorm_target(स्थिर काष्ठा ppc_inst *instr)
अणु
	चिन्हित दीर्घ imm;

	imm = ppc_inst_val(*instr) & 0x3FFFFFC;

	/* If the top bit of the immediate value is set this is negative */
	अगर (imm & 0x2000000)
		imm -= 0x4000000;

	अगर ((ppc_inst_val(*instr) & BRANCH_ABSOLUTE) == 0)
		imm += (अचिन्हित दीर्घ)instr;

	वापस (अचिन्हित दीर्घ)imm;
पूर्ण

अटल अचिन्हित दीर्घ branch_bक्रमm_target(स्थिर काष्ठा ppc_inst *instr)
अणु
	चिन्हित दीर्घ imm;

	imm = ppc_inst_val(*instr) & 0xFFFC;

	/* If the top bit of the immediate value is set this is negative */
	अगर (imm & 0x8000)
		imm -= 0x10000;

	अगर ((ppc_inst_val(*instr) & BRANCH_ABSOLUTE) == 0)
		imm += (अचिन्हित दीर्घ)instr;

	वापस (अचिन्हित दीर्घ)imm;
पूर्ण

अचिन्हित दीर्घ branch_target(स्थिर काष्ठा ppc_inst *instr)
अणु
	अगर (instr_is_branch_अगरorm(ppc_inst_पढ़ो(instr)))
		वापस branch_अगरorm_target(instr);
	अन्यथा अगर (instr_is_branch_bक्रमm(ppc_inst_पढ़ो(instr)))
		वापस branch_bक्रमm_target(instr);

	वापस 0;
पूर्ण

पूर्णांक instr_is_branch_to_addr(स्थिर काष्ठा ppc_inst *instr, अचिन्हित दीर्घ addr)
अणु
	अगर (instr_is_branch_अगरorm(ppc_inst_पढ़ो(instr)) ||
	    instr_is_branch_bक्रमm(ppc_inst_पढ़ो(instr)))
		वापस branch_target(instr) == addr;

	वापस 0;
पूर्ण

पूर्णांक translate_branch(काष्ठा ppc_inst *instr, स्थिर काष्ठा ppc_inst *dest,
		     स्थिर काष्ठा ppc_inst *src)
अणु
	अचिन्हित दीर्घ target;
	target = branch_target(src);

	अगर (instr_is_branch_अगरorm(ppc_inst_पढ़ो(src)))
		वापस create_branch(instr, dest, target,
				     ppc_inst_val(ppc_inst_पढ़ो(src)));
	अन्यथा अगर (instr_is_branch_bक्रमm(ppc_inst_पढ़ो(src)))
		वापस create_cond_branch(instr, dest, target,
					  ppc_inst_val(ppc_inst_पढ़ो(src)));

	वापस 1;
पूर्ण

#अगर_घोषित CONFIG_PPC_BOOK3E_64
व्योम __patch_exception(पूर्णांक exc, अचिन्हित दीर्घ addr)
अणु
	बाह्य अचिन्हित पूर्णांक पूर्णांकerrupt_base_book3e;
	अचिन्हित पूर्णांक *ibase = &पूर्णांकerrupt_base_book3e;

	/* Our exceptions vectors start with a NOP and -then- a branch
	 * to deal with single stepping from userspace which stops on
	 * the second inकाष्ठाion. Thus we need to patch the second
	 * inकाष्ठाion of the exception, not the first one
	 */

	patch_branch((काष्ठा ppc_inst *)(ibase + (exc / 4) + 1), addr, 0);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_CODE_PATCHING_SELFTEST

अटल व्योम __init test_trampoline(व्योम)
अणु
	यंत्र ("nop;\n");
पूर्ण

#घोषणा check(x)	\
	अगर (!(x)) prपूर्णांकk("code-patching: test failed at line %d\n", __LINE__);

अटल व्योम __init test_branch_अगरorm(व्योम)
अणु
	पूर्णांक err;
	काष्ठा ppc_inst instr;
	अचिन्हित दीर्घ addr;

	addr = (अचिन्हित दीर्घ)&instr;

	/* The simplest हाल, branch to self, no flags */
	check(instr_is_branch_अगरorm(ppc_inst(0x48000000)));
	/* All bits of target set, and flags */
	check(instr_is_branch_अगरorm(ppc_inst(0x4bffffff)));
	/* High bit of opcode set, which is wrong */
	check(!instr_is_branch_अगरorm(ppc_inst(0xcbffffff)));
	/* Middle bits of opcode set, which is wrong */
	check(!instr_is_branch_अगरorm(ppc_inst(0x7bffffff)));

	/* Simplest हाल, branch to self with link */
	check(instr_is_branch_अगरorm(ppc_inst(0x48000001)));
	/* All bits of tarमाला_लो set */
	check(instr_is_branch_अगरorm(ppc_inst(0x4bfffffd)));
	/* Some bits of tarमाला_लो set */
	check(instr_is_branch_अगरorm(ppc_inst(0x4bff00fd)));
	/* Must be a valid branch to start with */
	check(!instr_is_branch_अगरorm(ppc_inst(0x7bfffffd)));

	/* Absolute branch to 0x100 */
	instr = ppc_inst(0x48000103);
	check(instr_is_branch_to_addr(&instr, 0x100));
	/* Absolute branch to 0x420fc */
	instr = ppc_inst(0x480420ff);
	check(instr_is_branch_to_addr(&instr, 0x420fc));
	/* Maximum positive relative branch, + 20MB - 4B */
	instr = ppc_inst(0x49fffffc);
	check(instr_is_branch_to_addr(&instr, addr + 0x1FFFFFC));
	/* Smallest negative relative branch, - 4B */
	instr = ppc_inst(0x4bfffffc);
	check(instr_is_branch_to_addr(&instr, addr - 4));
	/* Largest negative relative branch, - 32 MB */
	instr = ppc_inst(0x4a000000);
	check(instr_is_branch_to_addr(&instr, addr - 0x2000000));

	/* Branch to self, with link */
	err = create_branch(&instr, &instr, addr, BRANCH_SET_LINK);
	check(instr_is_branch_to_addr(&instr, addr));

	/* Branch to self - 0x100, with link */
	err = create_branch(&instr, &instr, addr - 0x100, BRANCH_SET_LINK);
	check(instr_is_branch_to_addr(&instr, addr - 0x100));

	/* Branch to self + 0x100, no link */
	err = create_branch(&instr, &instr, addr + 0x100, 0);
	check(instr_is_branch_to_addr(&instr, addr + 0x100));

	/* Maximum relative negative offset, - 32 MB */
	err = create_branch(&instr, &instr, addr - 0x2000000, BRANCH_SET_LINK);
	check(instr_is_branch_to_addr(&instr, addr - 0x2000000));

	/* Out of range relative negative offset, - 32 MB + 4*/
	err = create_branch(&instr, &instr, addr - 0x2000004, BRANCH_SET_LINK);
	check(err);

	/* Out of range relative positive offset, + 32 MB */
	err = create_branch(&instr, &instr, addr + 0x2000000, BRANCH_SET_LINK);
	check(err);

	/* Unaligned target */
	err = create_branch(&instr, &instr, addr + 3, BRANCH_SET_LINK);
	check(err);

	/* Check flags are masked correctly */
	err = create_branch(&instr, &instr, addr, 0xFFFFFFFC);
	check(instr_is_branch_to_addr(&instr, addr));
	check(ppc_inst_equal(instr, ppc_inst(0x48000000)));
पूर्ण

अटल व्योम __init test_create_function_call(व्योम)
अणु
	काष्ठा ppc_inst *iptr;
	अचिन्हित दीर्घ dest;
	काष्ठा ppc_inst instr;

	/* Check we can create a function call */
	iptr = (काष्ठा ppc_inst *)ppc_function_entry(test_trampoline);
	dest = ppc_function_entry(test_create_function_call);
	create_branch(&instr, iptr, dest, BRANCH_SET_LINK);
	patch_inकाष्ठाion(iptr, instr);
	check(instr_is_branch_to_addr(iptr, dest));
पूर्ण

अटल व्योम __init test_branch_bक्रमm(व्योम)
अणु
	पूर्णांक err;
	अचिन्हित दीर्घ addr;
	काष्ठा ppc_inst *iptr, instr;
	अचिन्हित पूर्णांक flags;

	iptr = &instr;
	addr = (अचिन्हित दीर्घ)iptr;

	/* The simplest हाल, branch to self, no flags */
	check(instr_is_branch_bक्रमm(ppc_inst(0x40000000)));
	/* All bits of target set, and flags */
	check(instr_is_branch_bक्रमm(ppc_inst(0x43ffffff)));
	/* High bit of opcode set, which is wrong */
	check(!instr_is_branch_bक्रमm(ppc_inst(0xc3ffffff)));
	/* Middle bits of opcode set, which is wrong */
	check(!instr_is_branch_bक्रमm(ppc_inst(0x7bffffff)));

	/* Absolute conditional branch to 0x100 */
	instr = ppc_inst(0x43ff0103);
	check(instr_is_branch_to_addr(&instr, 0x100));
	/* Absolute conditional branch to 0x20fc */
	instr = ppc_inst(0x43ff20ff);
	check(instr_is_branch_to_addr(&instr, 0x20fc));
	/* Maximum positive relative conditional branch, + 32 KB - 4B */
	instr = ppc_inst(0x43ff7ffc);
	check(instr_is_branch_to_addr(&instr, addr + 0x7FFC));
	/* Smallest negative relative conditional branch, - 4B */
	instr = ppc_inst(0x43fffffc);
	check(instr_is_branch_to_addr(&instr, addr - 4));
	/* Largest negative relative conditional branch, - 32 KB */
	instr = ppc_inst(0x43ff8000);
	check(instr_is_branch_to_addr(&instr, addr - 0x8000));

	/* All condition code bits set & link */
	flags = 0x3ff000 | BRANCH_SET_LINK;

	/* Branch to self */
	err = create_cond_branch(&instr, iptr, addr, flags);
	check(instr_is_branch_to_addr(&instr, addr));

	/* Branch to self - 0x100 */
	err = create_cond_branch(&instr, iptr, addr - 0x100, flags);
	check(instr_is_branch_to_addr(&instr, addr - 0x100));

	/* Branch to self + 0x100 */
	err = create_cond_branch(&instr, iptr, addr + 0x100, flags);
	check(instr_is_branch_to_addr(&instr, addr + 0x100));

	/* Maximum relative negative offset, - 32 KB */
	err = create_cond_branch(&instr, iptr, addr - 0x8000, flags);
	check(instr_is_branch_to_addr(&instr, addr - 0x8000));

	/* Out of range relative negative offset, - 32 KB + 4*/
	err = create_cond_branch(&instr, iptr, addr - 0x8004, flags);
	check(err);

	/* Out of range relative positive offset, + 32 KB */
	err = create_cond_branch(&instr, iptr, addr + 0x8000, flags);
	check(err);

	/* Unaligned target */
	err = create_cond_branch(&instr, iptr, addr + 3, flags);
	check(err);

	/* Check flags are masked correctly */
	err = create_cond_branch(&instr, iptr, addr, 0xFFFFFFFC);
	check(instr_is_branch_to_addr(&instr, addr));
	check(ppc_inst_equal(instr, ppc_inst(0x43FF0000)));
पूर्ण

अटल व्योम __init test_translate_branch(व्योम)
अणु
	अचिन्हित दीर्घ addr;
	व्योम *p, *q;
	काष्ठा ppc_inst instr;
	व्योम *buf;

	buf = vदो_स्मृति(PAGE_ALIGN(0x2000000 + 1));
	check(buf);
	अगर (!buf)
		वापस;

	/* Simple हाल, branch to self moved a little */
	p = buf;
	addr = (अचिन्हित दीर्घ)p;
	patch_branch(p, addr, 0);
	check(instr_is_branch_to_addr(p, addr));
	q = p + 4;
	translate_branch(&instr, q, p);
	patch_inकाष्ठाion(q, instr);
	check(instr_is_branch_to_addr(q, addr));

	/* Maximum negative हाल, move b . to addr + 32 MB */
	p = buf;
	addr = (अचिन्हित दीर्घ)p;
	patch_branch(p, addr, 0);
	q = buf + 0x2000000;
	translate_branch(&instr, q, p);
	patch_inकाष्ठाion(q, instr);
	check(instr_is_branch_to_addr(p, addr));
	check(instr_is_branch_to_addr(q, addr));
	check(ppc_inst_equal(ppc_inst_पढ़ो(q), ppc_inst(0x4a000000)));

	/* Maximum positive हाल, move x to x - 32 MB + 4 */
	p = buf + 0x2000000;
	addr = (अचिन्हित दीर्घ)p;
	patch_branch(p, addr, 0);
	q = buf + 4;
	translate_branch(&instr, q, p);
	patch_inकाष्ठाion(q, instr);
	check(instr_is_branch_to_addr(p, addr));
	check(instr_is_branch_to_addr(q, addr));
	check(ppc_inst_equal(ppc_inst_पढ़ो(q), ppc_inst(0x49fffffc)));

	/* Jump to x + 16 MB moved to x + 20 MB */
	p = buf;
	addr = 0x1000000 + (अचिन्हित दीर्घ)buf;
	patch_branch(p, addr, BRANCH_SET_LINK);
	q = buf + 0x1400000;
	translate_branch(&instr, q, p);
	patch_inकाष्ठाion(q, instr);
	check(instr_is_branch_to_addr(p, addr));
	check(instr_is_branch_to_addr(q, addr));

	/* Jump to x + 16 MB moved to x - 16 MB + 4 */
	p = buf + 0x1000000;
	addr = 0x2000000 + (अचिन्हित दीर्घ)buf;
	patch_branch(p, addr, 0);
	q = buf + 4;
	translate_branch(&instr, q, p);
	patch_inकाष्ठाion(q, instr);
	check(instr_is_branch_to_addr(p, addr));
	check(instr_is_branch_to_addr(q, addr));


	/* Conditional branch tests */

	/* Simple हाल, branch to self moved a little */
	p = buf;
	addr = (अचिन्हित दीर्घ)p;
	create_cond_branch(&instr, p, addr, 0);
	patch_inकाष्ठाion(p, instr);
	check(instr_is_branch_to_addr(p, addr));
	q = buf + 4;
	translate_branch(&instr, q, p);
	patch_inकाष्ठाion(q, instr);
	check(instr_is_branch_to_addr(q, addr));

	/* Maximum negative हाल, move b . to addr + 32 KB */
	p = buf;
	addr = (अचिन्हित दीर्घ)p;
	create_cond_branch(&instr, p, addr, 0xFFFFFFFC);
	patch_inकाष्ठाion(p, instr);
	q = buf + 0x8000;
	translate_branch(&instr, q, p);
	patch_inकाष्ठाion(q, instr);
	check(instr_is_branch_to_addr(p, addr));
	check(instr_is_branch_to_addr(q, addr));
	check(ppc_inst_equal(ppc_inst_पढ़ो(q), ppc_inst(0x43ff8000)));

	/* Maximum positive हाल, move x to x - 32 KB + 4 */
	p = buf + 0x8000;
	addr = (अचिन्हित दीर्घ)p;
	create_cond_branch(&instr, p, addr, 0xFFFFFFFC);
	patch_inकाष्ठाion(p, instr);
	q = buf + 4;
	translate_branch(&instr, q, p);
	patch_inकाष्ठाion(q, instr);
	check(instr_is_branch_to_addr(p, addr));
	check(instr_is_branch_to_addr(q, addr));
	check(ppc_inst_equal(ppc_inst_पढ़ो(q), ppc_inst(0x43ff7ffc)));

	/* Jump to x + 12 KB moved to x + 20 KB */
	p = buf;
	addr = 0x3000 + (अचिन्हित दीर्घ)buf;
	create_cond_branch(&instr, p, addr, BRANCH_SET_LINK);
	patch_inकाष्ठाion(p, instr);
	q = buf + 0x5000;
	translate_branch(&instr, q, p);
	patch_inकाष्ठाion(q, instr);
	check(instr_is_branch_to_addr(p, addr));
	check(instr_is_branch_to_addr(q, addr));

	/* Jump to x + 8 KB moved to x - 8 KB + 4 */
	p = buf + 0x2000;
	addr = 0x4000 + (अचिन्हित दीर्घ)buf;
	create_cond_branch(&instr, p, addr, 0);
	patch_inकाष्ठाion(p, instr);
	q = buf + 4;
	translate_branch(&instr, q, p);
	patch_inकाष्ठाion(q, instr);
	check(instr_is_branch_to_addr(p, addr));
	check(instr_is_branch_to_addr(q, addr));

	/* Free the buffer we were using */
	vमुक्त(buf);
पूर्ण

#अगर_घोषित CONFIG_PPC64
अटल व्योम __init test_prefixed_patching(व्योम)
अणु
	बाह्य अचिन्हित पूर्णांक code_patching_test1[];
	बाह्य अचिन्हित पूर्णांक code_patching_test1_expected[];
	बाह्य अचिन्हित पूर्णांक end_code_patching_test1[];

	__patch_inकाष्ठाion((काष्ठा ppc_inst *)code_patching_test1,
			    ppc_inst_prefix(OP_PREFIX << 26, 0x00000000),
			    (काष्ठा ppc_inst *)code_patching_test1);

	check(!स_भेद(code_patching_test1,
		      code_patching_test1_expected,
		      माप(अचिन्हित पूर्णांक) *
		      (end_code_patching_test1 - code_patching_test1)));
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम test_prefixed_patching(व्योम) अणुपूर्ण
#पूर्ण_अगर

अटल पूर्णांक __init test_code_patching(व्योम)
अणु
	prपूर्णांकk(KERN_DEBUG "Running code patching self-tests ...\n");

	test_branch_अगरorm();
	test_branch_bक्रमm();
	test_create_function_call();
	test_translate_branch();
	test_prefixed_patching();

	वापस 0;
पूर्ण
late_initcall(test_code_patching);

#पूर्ण_अगर /* CONFIG_CODE_PATCHING_SELFTEST */
