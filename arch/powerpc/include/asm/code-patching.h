<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित _ASM_POWERPC_CODE_PATCHING_H
#घोषणा _ASM_POWERPC_CODE_PATCHING_H

/*
 * Copyright 2008, Michael Ellerman, IBM Corporation.
 */

#समावेश <यंत्र/types.h>
#समावेश <यंत्र/ppc-opcode.h>
#समावेश <linux/माला.स>
#समावेश <linux/kallsyms.h>
#समावेश <यंत्र/यंत्र-compat.h>
#समावेश <यंत्र/inst.h>

/* Flags क्रम create_branch:
 * "b"   == create_branch(addr, target, 0);
 * "ba"  == create_branch(addr, target, BRANCH_ABSOLUTE);
 * "bl"  == create_branch(addr, target, BRANCH_SET_LINK);
 * "bla" == create_branch(addr, target, BRANCH_ABSOLUTE | BRANCH_SET_LINK);
 */
#घोषणा BRANCH_SET_LINK	0x1
#घोषणा BRANCH_ABSOLUTE	0x2

bool is_offset_in_branch_range(दीर्घ offset);
पूर्णांक create_branch(काष्ठा ppc_inst *instr, स्थिर काष्ठा ppc_inst *addr,
		  अचिन्हित दीर्घ target, पूर्णांक flags);
पूर्णांक create_cond_branch(काष्ठा ppc_inst *instr, स्थिर काष्ठा ppc_inst *addr,
		       अचिन्हित दीर्घ target, पूर्णांक flags);
पूर्णांक patch_branch(काष्ठा ppc_inst *addr, अचिन्हित दीर्घ target, पूर्णांक flags);
पूर्णांक patch_inकाष्ठाion(काष्ठा ppc_inst *addr, काष्ठा ppc_inst instr);
पूर्णांक raw_patch_inकाष्ठाion(काष्ठा ppc_inst *addr, काष्ठा ppc_inst instr);

अटल अंतरभूत अचिन्हित दीर्घ patch_site_addr(s32 *site)
अणु
	वापस (अचिन्हित दीर्घ)site + *site;
पूर्ण

अटल अंतरभूत पूर्णांक patch_inकाष्ठाion_site(s32 *site, काष्ठा ppc_inst instr)
अणु
	वापस patch_inकाष्ठाion((काष्ठा ppc_inst *)patch_site_addr(site), instr);
पूर्ण

अटल अंतरभूत पूर्णांक patch_branch_site(s32 *site, अचिन्हित दीर्घ target, पूर्णांक flags)
अणु
	वापस patch_branch((काष्ठा ppc_inst *)patch_site_addr(site), target, flags);
पूर्ण

अटल अंतरभूत पूर्णांक modअगरy_inकाष्ठाion(अचिन्हित पूर्णांक *addr, अचिन्हित पूर्णांक clr,
				     अचिन्हित पूर्णांक set)
अणु
	वापस patch_inकाष्ठाion((काष्ठा ppc_inst *)addr, ppc_inst((*addr & ~clr) | set));
पूर्ण

अटल अंतरभूत पूर्णांक modअगरy_inकाष्ठाion_site(s32 *site, अचिन्हित पूर्णांक clr, अचिन्हित पूर्णांक set)
अणु
	वापस modअगरy_inकाष्ठाion((अचिन्हित पूर्णांक *)patch_site_addr(site), clr, set);
पूर्ण

पूर्णांक instr_is_relative_branch(काष्ठा ppc_inst instr);
पूर्णांक instr_is_relative_link_branch(काष्ठा ppc_inst instr);
पूर्णांक instr_is_branch_to_addr(स्थिर काष्ठा ppc_inst *instr, अचिन्हित दीर्घ addr);
अचिन्हित दीर्घ branch_target(स्थिर काष्ठा ppc_inst *instr);
पूर्णांक translate_branch(काष्ठा ppc_inst *instr, स्थिर काष्ठा ppc_inst *dest,
		     स्थिर काष्ठा ppc_inst *src);
बाह्य bool is_conditional_branch(काष्ठा ppc_inst instr);
#अगर_घोषित CONFIG_PPC_BOOK3E_64
व्योम __patch_exception(पूर्णांक exc, अचिन्हित दीर्घ addr);
#घोषणा patch_exception(exc, name) करो अणु \
	बाह्य अचिन्हित पूर्णांक name; \
	__patch_exception((exc), (अचिन्हित दीर्घ)&name); \
पूर्ण जबतक (0)
#पूर्ण_अगर

#घोषणा OP_RT_RA_MASK	0xffff0000UL
#घोषणा LIS_R2		(PPC_INST_ADDIS | __PPC_RT(R2))
#घोषणा ADDIS_R2_R12	(PPC_INST_ADDIS | __PPC_RT(R2) | __PPC_RA(R12))
#घोषणा ADDI_R2_R2	(PPC_INST_ADDI  | __PPC_RT(R2) | __PPC_RA(R2))


अटल अंतरभूत अचिन्हित दीर्घ ppc_function_entry(व्योम *func)
अणु
#अगर_घोषित PPC64_ELF_ABI_v2
	u32 *insn = func;

	/*
	 * A PPC64 ABIv2 function may have a local and a global entry
	 * poपूर्णांक. We need to use the local entry poपूर्णांक when patching
	 * functions, so identअगरy and step over the global entry poपूर्णांक
	 * sequence.
	 *
	 * The global entry poपूर्णांक sequence is always of the क्रमm:
	 *
	 * addis r2,r12,XXXX
	 * addi  r2,r2,XXXX
	 *
	 * A linker optimisation may convert the addis to lis:
	 *
	 * lis   r2,XXXX
	 * addi  r2,r2,XXXX
	 */
	अगर ((((*insn & OP_RT_RA_MASK) == ADDIS_R2_R12) ||
	     ((*insn & OP_RT_RA_MASK) == LIS_R2)) &&
	    ((*(insn+1) & OP_RT_RA_MASK) == ADDI_R2_R2))
		वापस (अचिन्हित दीर्घ)(insn + 2);
	अन्यथा
		वापस (अचिन्हित दीर्घ)func;
#या_अगर defined(PPC64_ELF_ABI_v1)
	/*
	 * On PPC64 ABIv1 the function poपूर्णांकer actually poपूर्णांकs to the
	 * function's descriptor. The first entry in the descriptor is the
	 * address of the function text.
	 */
	वापस ((func_descr_t *)func)->entry;
#अन्यथा
	वापस (अचिन्हित दीर्घ)func;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ ppc_global_function_entry(व्योम *func)
अणु
#अगर_घोषित PPC64_ELF_ABI_v2
	/* PPC64 ABIv2 the global entry poपूर्णांक is at the address */
	वापस (अचिन्हित दीर्घ)func;
#अन्यथा
	/* All other हालs there is no change vs ppc_function_entry() */
	वापस ppc_function_entry(func);
#पूर्ण_अगर
पूर्ण

/*
 * Wrapper around kallsyms_lookup() to वापस function entry address:
 * - For ABIv1, we lookup the करोt variant.
 * - For ABIv2, we वापस the local entry poपूर्णांक.
 */
अटल अंतरभूत अचिन्हित दीर्घ ppc_kallsyms_lookup_name(स्थिर अक्षर *name)
अणु
	अचिन्हित दीर्घ addr;
#अगर_घोषित PPC64_ELF_ABI_v1
	/* check क्रम करोt variant */
	अक्षर करोt_name[1 + KSYM_NAME_LEN];
	bool करोt_appended = false;

	अगर (strnlen(name, KSYM_NAME_LEN) >= KSYM_NAME_LEN)
		वापस 0;

	अगर (name[0] != '.') अणु
		करोt_name[0] = '.';
		करोt_name[1] = '\0';
		strlcat(करोt_name, name, माप(करोt_name));
		करोt_appended = true;
	पूर्ण अन्यथा अणु
		करोt_name[0] = '\0';
		strlcat(करोt_name, name, माप(करोt_name));
	पूर्ण
	addr = kallsyms_lookup_name(करोt_name);
	अगर (!addr && करोt_appended)
		/* Let's try the original non-करोt symbol lookup	*/
		addr = kallsyms_lookup_name(name);
#या_अगर defined(PPC64_ELF_ABI_v2)
	addr = kallsyms_lookup_name(name);
	अगर (addr)
		addr = ppc_function_entry((व्योम *)addr);
#अन्यथा
	addr = kallsyms_lookup_name(name);
#पूर्ण_अगर
	वापस addr;
पूर्ण

#अगर_घोषित CONFIG_PPC64
/*
 * Some inकाष्ठाion encodings commonly used in dynamic ftracing
 * and function live patching.
 */

/* This must match the definition of STK_GOT in <यंत्र/ppc_यंत्र.h> */
#अगर_घोषित PPC64_ELF_ABI_v2
#घोषणा R2_STACK_OFFSET         24
#अन्यथा
#घोषणा R2_STACK_OFFSET         40
#पूर्ण_अगर

#घोषणा PPC_INST_LD_TOC		(PPC_INST_LD  | ___PPC_RT(__REG_R2) | \
				 ___PPC_RA(__REG_R1) | R2_STACK_OFFSET)

/* usually preceded by a mflr r0 */
#घोषणा PPC_INST_STD_LR		(PPC_INST_STD | ___PPC_RS(__REG_R0) | \
				 ___PPC_RA(__REG_R1) | PPC_LR_STKOFF)
#पूर्ण_अगर /* CONFIG_PPC64 */

#पूर्ण_अगर /* _ASM_POWERPC_CODE_PATCHING_H */
