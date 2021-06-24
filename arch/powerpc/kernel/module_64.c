<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*  Kernel module help क्रम PPC64.
    Copyright (C) 2001, 2003 Rusty Russell IBM Corporation.

*/

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/elf.h>
#समावेश <linux/moduleloader.h>
#समावेश <linux/err.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/ftrace.h>
#समावेश <linux/bug.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/module.h>
#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/code-patching.h>
#समावेश <linux/sort.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/inst.h>

/* FIXME: We करोn't do .init separately.  To do this, we'd need to have
   a separate r2 value in the init and core section, and stub between
   them, too.

   Using a magic allocator which places modules within 32MB solves
   this, and makes other things simpler.  Anton?
   --RR.  */

#अगर_घोषित PPC64_ELF_ABI_v2

/* An address is simply the address of the function. */
प्रकार अचिन्हित दीर्घ func_desc_t;

अटल func_desc_t func_desc(अचिन्हित दीर्घ addr)
अणु
	वापस addr;
पूर्ण
अटल अचिन्हित दीर्घ func_addr(अचिन्हित दीर्घ addr)
अणु
	वापस addr;
पूर्ण
अटल अचिन्हित दीर्घ stub_func_addr(func_desc_t func)
अणु
	वापस func;
पूर्ण

/* PowerPC64 specअगरic values क्रम the Elf64_Sym st_other field.  */
#घोषणा STO_PPC64_LOCAL_BIT	5
#घोषणा STO_PPC64_LOCAL_MASK	(7 << STO_PPC64_LOCAL_BIT)
#घोषणा PPC64_LOCAL_ENTRY_OFFSET(other)					\
 (((1 << (((other) & STO_PPC64_LOCAL_MASK) >> STO_PPC64_LOCAL_BIT)) >> 2) << 2)

अटल अचिन्हित पूर्णांक local_entry_offset(स्थिर Elf64_Sym *sym)
अणु
	/* sym->st_other indicates offset to local entry poपूर्णांक
	 * (otherwise it will assume r12 is the address of the start
	 * of function and try to derive r2 from it). */
	वापस PPC64_LOCAL_ENTRY_OFFSET(sym->st_other);
पूर्ण
#अन्यथा

/* An address is address of the OPD entry, which contains address of fn. */
प्रकार काष्ठा ppc64_opd_entry func_desc_t;

अटल func_desc_t func_desc(अचिन्हित दीर्घ addr)
अणु
	वापस *(काष्ठा ppc64_opd_entry *)addr;
पूर्ण
अटल अचिन्हित दीर्घ func_addr(अचिन्हित दीर्घ addr)
अणु
	वापस func_desc(addr).funcaddr;
पूर्ण
अटल अचिन्हित दीर्घ stub_func_addr(func_desc_t func)
अणु
	वापस func.funcaddr;
पूर्ण
अटल अचिन्हित पूर्णांक local_entry_offset(स्थिर Elf64_Sym *sym)
अणु
	वापस 0;
पूर्ण

व्योम *dereference_module_function_descriptor(काष्ठा module *mod, व्योम *ptr)
अणु
	अगर (ptr < (व्योम *)mod->arch.start_opd ||
			ptr >= (व्योम *)mod->arch.end_opd)
		वापस ptr;

	वापस dereference_function_descriptor(ptr);
पूर्ण
#पूर्ण_अगर

#घोषणा STUB_MAGIC 0x73747562 /* stub */

/* Like PPC32, we need little trampolines to करो > 24-bit jumps (पूर्णांकo
   the kernel itself).  But on PPC64, these need to be used क्रम every
   jump, actually, to reset r2 (TOC+0x8000). */
काष्ठा ppc64_stub_entry
अणु
	/* 28 byte jump inकाष्ठाion sequence (7 inकाष्ठाions). We only
	 * need 6 inकाष्ठाions on ABIv2 but we always allocate 7 so
	 * so we करोn't have to modअगरy the trampoline load inकाष्ठाion. */
	u32 jump[7];
	/* Used by ftrace to identअगरy stubs */
	u32 magic;
	/* Data क्रम the above code */
	func_desc_t funcdata;
पूर्ण;

/*
 * PPC64 uses 24 bit jumps, but we need to jump पूर्णांकo other modules or
 * the kernel which may be further.  So we jump to a stub.
 *
 * For ELFv1 we need to use this to set up the new r2 value (aka TOC
 * poपूर्णांकer).  For ELFv2 it's the callee's responsibility to set up the
 * new r2, but क्रम both we need to save the old r2.
 *
 * We could simply patch the new r2 value and function poपूर्णांकer पूर्णांकo
 * the stub, but it's signअगरicantly लघुer to put these values at the
 * end of the stub code, and patch the stub address (32-bits relative
 * to the TOC ptr, r2) पूर्णांकo the stub.
 *
 * addis   r11,r2, <high>
 * addi    r11,r11, <low>
 * std     r2,R2_STACK_OFFSET(r1)
 * ld      r12,32(r11)
 * ld      r2,40(r11)
 * mtctr   r12
 * bctr
 */
अटल u32 ppc64_stub_insns[] = अणु
	PPC_INST_ADDIS | __PPC_RT(R11) | __PPC_RA(R2),
	PPC_INST_ADDI | __PPC_RT(R11) | __PPC_RA(R11),
	/* Save current r2 value in magic place on the stack. */
	PPC_INST_STD | __PPC_RS(R2) | __PPC_RA(R1) | R2_STACK_OFFSET,
	PPC_INST_LD | __PPC_RT(R12) | __PPC_RA(R11) | 32,
#अगर_घोषित PPC64_ELF_ABI_v1
	/* Set up new r2 from function descriptor */
	PPC_INST_LD | __PPC_RT(R2) | __PPC_RA(R11) | 40,
#पूर्ण_अगर
	PPC_INST_MTCTR | __PPC_RS(R12),
	PPC_INST_BCTR,
पूर्ण;

/* Count how many dअगरferent 24-bit relocations (dअगरferent symbol,
   dअगरferent addend) */
अटल अचिन्हित पूर्णांक count_relocs(स्थिर Elf64_Rela *rela, अचिन्हित पूर्णांक num)
अणु
	अचिन्हित पूर्णांक i, r_info, r_addend, _count_relocs;

	/* FIXME: Only count बाह्यal ones --RR */
	_count_relocs = 0;
	r_info = 0;
	r_addend = 0;
	क्रम (i = 0; i < num; i++)
		/* Only count 24-bit relocs, others करोn't need stubs */
		अगर (ELF64_R_TYPE(rela[i].r_info) == R_PPC_REL24 &&
		    (r_info != ELF64_R_SYM(rela[i].r_info) ||
		     r_addend != rela[i].r_addend)) अणु
			_count_relocs++;
			r_info = ELF64_R_SYM(rela[i].r_info);
			r_addend = rela[i].r_addend;
		पूर्ण

	वापस _count_relocs;
पूर्ण

अटल पूर्णांक relacmp(स्थिर व्योम *_x, स्थिर व्योम *_y)
अणु
	स्थिर Elf64_Rela *x, *y;

	y = (Elf64_Rela *)_x;
	x = (Elf64_Rela *)_y;

	/* Compare the entire r_info (as opposed to ELF64_R_SYM(r_info) only) to
	 * make the comparison cheaper/faster. It won't affect the sorting or
	 * the counting algorithms' perक्रमmance
	 */
	अगर (x->r_info < y->r_info)
		वापस -1;
	अन्यथा अगर (x->r_info > y->r_info)
		वापस 1;
	अन्यथा अगर (x->r_addend < y->r_addend)
		वापस -1;
	अन्यथा अगर (x->r_addend > y->r_addend)
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

/* Get size of potential trampolines required. */
अटल अचिन्हित दीर्घ get_stubs_size(स्थिर Elf64_Ehdr *hdr,
				    स्थिर Elf64_Shdr *sechdrs)
अणु
	/* One extra reloc so it's always 0-funcaddr terminated */
	अचिन्हित दीर्घ relocs = 1;
	अचिन्हित i;

	/* Every relocated section... */
	क्रम (i = 1; i < hdr->e_shnum; i++) अणु
		अगर (sechdrs[i].sh_type == SHT_RELA) अणु
			pr_debug("Found relocations in section %u\n", i);
			pr_debug("Ptr: %p.  Number: %Lu\n",
			       (व्योम *)sechdrs[i].sh_addr,
			       sechdrs[i].sh_size / माप(Elf64_Rela));

			/* Sort the relocation inक्रमmation based on a symbol and
			 * addend key. This is a stable O(n*log n) complनिकासy
			 * alogrithm but it will reduce the complनिकासy of
			 * count_relocs() to linear complनिकासy O(n)
			 */
			sort((व्योम *)sechdrs[i].sh_addr,
			     sechdrs[i].sh_size / माप(Elf64_Rela),
			     माप(Elf64_Rela), relacmp, शून्य);

			relocs += count_relocs((व्योम *)sechdrs[i].sh_addr,
					       sechdrs[i].sh_size
					       / माप(Elf64_Rela));
		पूर्ण
	पूर्ण

#अगर_घोषित CONFIG_DYNAMIC_FTRACE
	/* make the trampoline to the ftrace_caller */
	relocs++;
#अगर_घोषित CONFIG_DYNAMIC_FTRACE_WITH_REGS
	/* an additional one क्रम ftrace_regs_caller */
	relocs++;
#पूर्ण_अगर
#पूर्ण_अगर

	pr_debug("Looks like a total of %lu stubs, max\n", relocs);
	वापस relocs * माप(काष्ठा ppc64_stub_entry);
पूर्ण

/* Still needed क्रम ELFv2, क्रम .TOC. */
अटल व्योम deकरोtअगरy_versions(काष्ठा modversion_info *vers,
			      अचिन्हित दीर्घ size)
अणु
	काष्ठा modversion_info *end;

	क्रम (end = (व्योम *)vers + size; vers < end; vers++)
		अगर (vers->name[0] == '.') अणु
			स_हटाओ(vers->name, vers->name+1, म_माप(vers->name));
		पूर्ण
पूर्ण

/*
 * Undefined symbols which refer to .funcname, hack to funcname. Make .TOC.
 * seem to be defined (value set later).
 */
अटल व्योम deकरोtअगरy(Elf64_Sym *syms, अचिन्हित पूर्णांक numsyms, अक्षर *strtab)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 1; i < numsyms; i++) अणु
		अगर (syms[i].st_shndx == SHN_UNDEF) अणु
			अक्षर *name = strtab + syms[i].st_name;
			अगर (name[0] == '.') अणु
				अगर (म_भेद(name+1, "TOC.") == 0)
					syms[i].st_shndx = SHN_ABS;
				syms[i].st_name++;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल Elf64_Sym *find_करोt_toc(Elf64_Shdr *sechdrs,
			       स्थिर अक्षर *strtab,
			       अचिन्हित पूर्णांक symindex)
अणु
	अचिन्हित पूर्णांक i, numsyms;
	Elf64_Sym *syms;

	syms = (Elf64_Sym *)sechdrs[symindex].sh_addr;
	numsyms = sechdrs[symindex].sh_size / माप(Elf64_Sym);

	क्रम (i = 1; i < numsyms; i++) अणु
		अगर (syms[i].st_shndx == SHN_ABS
		    && म_भेद(strtab + syms[i].st_name, "TOC.") == 0)
			वापस &syms[i];
	पूर्ण
	वापस शून्य;
पूर्ण

पूर्णांक module_frob_arch_sections(Elf64_Ehdr *hdr,
			      Elf64_Shdr *sechdrs,
			      अक्षर *secstrings,
			      काष्ठा module *me)
अणु
	अचिन्हित पूर्णांक i;

	/* Find .toc and .stubs sections, symtab and strtab */
	क्रम (i = 1; i < hdr->e_shnum; i++) अणु
		अक्षर *p;
		अगर (म_भेद(secstrings + sechdrs[i].sh_name, ".stubs") == 0)
			me->arch.stubs_section = i;
		अन्यथा अगर (म_भेद(secstrings + sechdrs[i].sh_name, ".toc") == 0) अणु
			me->arch.toc_section = i;
			अगर (sechdrs[i].sh_addralign < 8)
				sechdrs[i].sh_addralign = 8;
		पूर्ण
		अन्यथा अगर (म_भेद(secstrings+sechdrs[i].sh_name,"__versions")==0)
			deकरोtअगरy_versions((व्योम *)hdr + sechdrs[i].sh_offset,
					  sechdrs[i].sh_size);

		/* We करोn't handle .init क्रम the moment: नाम to _init */
		जबतक ((p = म_माला(secstrings + sechdrs[i].sh_name, ".init")))
			p[0] = '_';

		अगर (sechdrs[i].sh_type == SHT_SYMTAB)
			deकरोtअगरy((व्योम *)hdr + sechdrs[i].sh_offset,
				 sechdrs[i].sh_size / माप(Elf64_Sym),
				 (व्योम *)hdr
				 + sechdrs[sechdrs[i].sh_link].sh_offset);
	पूर्ण

	अगर (!me->arch.stubs_section) अणु
		pr_err("%s: doesn't contain .stubs.\n", me->name);
		वापस -ENOEXEC;
	पूर्ण

	/* If we करोn't have a .toc, just use .stubs.  We need to set r2
	   to some reasonable value in हाल the module calls out to
	   other functions via a stub, or अगर a function poपूर्णांकer escapes
	   the module by some means.  */
	अगर (!me->arch.toc_section)
		me->arch.toc_section = me->arch.stubs_section;

	/* Override the stubs size */
	sechdrs[me->arch.stubs_section].sh_size = get_stubs_size(hdr, sechdrs);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_MPROखाता_KERNEL

#घोषणा PACATOC दुरत्व(काष्ठा paca_काष्ठा, kernel_toc)

/*
 * ld      r12,PACATOC(r13)
 * addis   r12,r12,<high>
 * addi    r12,r12,<low>
 * mtctr   r12
 * bctr
 */
अटल u32 stub_insns[] = अणु
	PPC_INST_LD | __PPC_RT(R12) | __PPC_RA(R13) | PACATOC,
	PPC_INST_ADDIS | __PPC_RT(R12) | __PPC_RA(R12),
	PPC_INST_ADDI | __PPC_RT(R12) | __PPC_RA(R12),
	PPC_INST_MTCTR | __PPC_RS(R12),
	PPC_INST_BCTR,
पूर्ण;

/*
 * For mprofile-kernel we use a special stub क्रम ftrace_caller() because we
 * can't rely on r2 containing this module's TOC when we enter the stub.
 *
 * That can happen अगर the function calling us didn't need to use the toc. In
 * that हाल it won't have setup r2, and the r2 value will be either the
 * kernel's toc, or possibly another modules toc.
 *
 * To deal with that this stub uses the kernel toc, which is always accessible
 * via the paca (in r13). The target (ftrace_caller()) is responsible क्रम
 * saving and restoring the toc beक्रमe वापसing.
 */
अटल अंतरभूत पूर्णांक create_ftrace_stub(काष्ठा ppc64_stub_entry *entry,
					अचिन्हित दीर्घ addr,
					काष्ठा module *me)
अणु
	दीर्घ reladdr;

	स_नकल(entry->jump, stub_insns, माप(stub_insns));

	/* Stub uses address relative to kernel toc (from the paca) */
	reladdr = addr - kernel_toc_addr();
	अगर (reladdr > 0x7FFFFFFF || reladdr < -(0x80000000L)) अणु
		pr_err("%s: Address of %ps out of range of kernel_toc.\n",
							me->name, (व्योम *)addr);
		वापस 0;
	पूर्ण

	entry->jump[1] |= PPC_HA(reladdr);
	entry->jump[2] |= PPC_LO(reladdr);

	/* Eventhough we करोn't use funcdata in the stub, it's needed अन्यथाwhere. */
	entry->funcdata = func_desc(addr);
	entry->magic = STUB_MAGIC;

	वापस 1;
पूर्ण

अटल bool is_mprofile_ftrace_call(स्थिर अक्षर *name)
अणु
	अगर (!म_भेद("_mcount", name))
		वापस true;
#अगर_घोषित CONFIG_DYNAMIC_FTRACE
	अगर (!म_भेद("ftrace_caller", name))
		वापस true;
#अगर_घोषित CONFIG_DYNAMIC_FTRACE_WITH_REGS
	अगर (!म_भेद("ftrace_regs_caller", name))
		वापस true;
#पूर्ण_अगर
#पूर्ण_अगर

	वापस false;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक create_ftrace_stub(काष्ठा ppc64_stub_entry *entry,
					अचिन्हित दीर्घ addr,
					काष्ठा module *me)
अणु
	वापस 0;
पूर्ण

अटल bool is_mprofile_ftrace_call(स्थिर अक्षर *name)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

/*
 * r2 is the TOC poपूर्णांकer: it actually poपूर्णांकs 0x8000 पूर्णांकo the TOC (this gives the
 * value maximum span in an inकाष्ठाion which uses a चिन्हित offset). Round करोwn
 * to a 256 byte boundary क्रम the odd हाल where we are setting up r2 without a
 * .toc section.
 */
अटल अंतरभूत अचिन्हित दीर्घ my_r2(स्थिर Elf64_Shdr *sechdrs, काष्ठा module *me)
अणु
	वापस (sechdrs[me->arch.toc_section].sh_addr & ~0xfful) + 0x8000;
पूर्ण

/* Patch stub to reference function and correct r2 value. */
अटल अंतरभूत पूर्णांक create_stub(स्थिर Elf64_Shdr *sechdrs,
			      काष्ठा ppc64_stub_entry *entry,
			      अचिन्हित दीर्घ addr,
			      काष्ठा module *me,
			      स्थिर अक्षर *name)
अणु
	दीर्घ reladdr;

	अगर (is_mprofile_ftrace_call(name))
		वापस create_ftrace_stub(entry, addr, me);

	स_नकल(entry->jump, ppc64_stub_insns, माप(ppc64_stub_insns));

	/* Stub uses address relative to r2. */
	reladdr = (अचिन्हित दीर्घ)entry - my_r2(sechdrs, me);
	अगर (reladdr > 0x7FFFFFFF || reladdr < -(0x80000000L)) अणु
		pr_err("%s: Address %p of stub out of range of %p.\n",
		       me->name, (व्योम *)reladdr, (व्योम *)my_r2);
		वापस 0;
	पूर्ण
	pr_debug("Stub %p get data from reladdr %li\n", entry, reladdr);

	entry->jump[0] |= PPC_HA(reladdr);
	entry->jump[1] |= PPC_LO(reladdr);
	entry->funcdata = func_desc(addr);
	entry->magic = STUB_MAGIC;

	वापस 1;
पूर्ण

/* Create stub to jump to function described in this OPD/ptr: we need the
   stub to set up the TOC ptr (r2) क्रम the function. */
अटल अचिन्हित दीर्घ stub_क्रम_addr(स्थिर Elf64_Shdr *sechdrs,
				   अचिन्हित दीर्घ addr,
				   काष्ठा module *me,
				   स्थिर अक्षर *name)
अणु
	काष्ठा ppc64_stub_entry *stubs;
	अचिन्हित पूर्णांक i, num_stubs;

	num_stubs = sechdrs[me->arch.stubs_section].sh_size / माप(*stubs);

	/* Find this stub, or अगर that fails, the next avail. entry */
	stubs = (व्योम *)sechdrs[me->arch.stubs_section].sh_addr;
	क्रम (i = 0; stub_func_addr(stubs[i].funcdata); i++) अणु
		अगर (WARN_ON(i >= num_stubs))
			वापस 0;

		अगर (stub_func_addr(stubs[i].funcdata) == func_addr(addr))
			वापस (अचिन्हित दीर्घ)&stubs[i];
	पूर्ण

	अगर (!create_stub(sechdrs, &stubs[i], addr, me, name))
		वापस 0;

	वापस (अचिन्हित दीर्घ)&stubs[i];
पूर्ण

/* We expect a noop next: अगर it is, replace it with inकाष्ठाion to
   restore r2. */
अटल पूर्णांक restore_r2(स्थिर अक्षर *name, u32 *inकाष्ठाion, काष्ठा module *me)
अणु
	u32 *prev_insn = inकाष्ठाion - 1;

	अगर (is_mprofile_ftrace_call(name))
		वापस 1;

	/*
	 * Make sure the branch isn't a sibling call.  Sibling calls aren't
	 * "link" branches and they करोn't return, so they don't need the r2
	 * restore afterwards.
	 */
	अगर (!instr_is_relative_link_branch(ppc_inst(*prev_insn)))
		वापस 1;

	अगर (*inकाष्ठाion != PPC_INST_NOP) अणु
		pr_err("%s: Expected nop after call, got %08x at %pS\n",
			me->name, *inकाष्ठाion, inकाष्ठाion);
		वापस 0;
	पूर्ण
	/* ld r2,R2_STACK_OFFSET(r1) */
	*inकाष्ठाion = PPC_INST_LD_TOC;
	वापस 1;
पूर्ण

पूर्णांक apply_relocate_add(Elf64_Shdr *sechdrs,
		       स्थिर अक्षर *strtab,
		       अचिन्हित पूर्णांक symindex,
		       अचिन्हित पूर्णांक rअन्यथाc,
		       काष्ठा module *me)
अणु
	अचिन्हित पूर्णांक i;
	Elf64_Rela *rela = (व्योम *)sechdrs[rअन्यथाc].sh_addr;
	Elf64_Sym *sym;
	अचिन्हित दीर्घ *location;
	अचिन्हित दीर्घ value;

	pr_debug("Applying ADD relocate section %u to %u\n", rअन्यथाc,
	       sechdrs[rअन्यथाc].sh_info);

	/* First समय we're called, we can fix up .TOC. */
	अगर (!me->arch.toc_fixed) अणु
		sym = find_करोt_toc(sechdrs, strtab, symindex);
		/* It's theoretically possible that a module doesn't want a
		 * .TOC. so करोn't fail it just क्रम that. */
		अगर (sym)
			sym->st_value = my_r2(sechdrs, me);
		me->arch.toc_fixed = true;
	पूर्ण

	क्रम (i = 0; i < sechdrs[rअन्यथाc].sh_size / माप(*rela); i++) अणु
		/* This is where to make the change */
		location = (व्योम *)sechdrs[sechdrs[rअन्यथाc].sh_info].sh_addr
			+ rela[i].r_offset;
		/* This is the symbol it is referring to */
		sym = (Elf64_Sym *)sechdrs[symindex].sh_addr
			+ ELF64_R_SYM(rela[i].r_info);

		pr_debug("RELOC at %p: %li-type as %s (0x%lx) + %li\n",
		       location, (दीर्घ)ELF64_R_TYPE(rela[i].r_info),
		       strtab + sym->st_name, (अचिन्हित दीर्घ)sym->st_value,
		       (दीर्घ)rela[i].r_addend);

		/* `Everything is relative'. */
		value = sym->st_value + rela[i].r_addend;

		चयन (ELF64_R_TYPE(rela[i].r_info)) अणु
		हाल R_PPC64_ADDR32:
			/* Simply set it */
			*(u32 *)location = value;
			अवरोध;

		हाल R_PPC64_ADDR64:
			/* Simply set it */
			*(अचिन्हित दीर्घ *)location = value;
			अवरोध;

		हाल R_PPC64_TOC:
			*(अचिन्हित दीर्घ *)location = my_r2(sechdrs, me);
			अवरोध;

		हाल R_PPC64_TOC16:
			/* Subtract TOC poपूर्णांकer */
			value -= my_r2(sechdrs, me);
			अगर (value + 0x8000 > 0xffff) अणु
				pr_err("%s: bad TOC16 relocation (0x%lx)\n",
				       me->name, value);
				वापस -ENOEXEC;
			पूर्ण
			*((uपूर्णांक16_t *) location)
				= (*((uपूर्णांक16_t *) location) & ~0xffff)
				| (value & 0xffff);
			अवरोध;

		हाल R_PPC64_TOC16_LO:
			/* Subtract TOC poपूर्णांकer */
			value -= my_r2(sechdrs, me);
			*((uपूर्णांक16_t *) location)
				= (*((uपूर्णांक16_t *) location) & ~0xffff)
				| (value & 0xffff);
			अवरोध;

		हाल R_PPC64_TOC16_DS:
			/* Subtract TOC poपूर्णांकer */
			value -= my_r2(sechdrs, me);
			अगर ((value & 3) != 0 || value + 0x8000 > 0xffff) अणु
				pr_err("%s: bad TOC16_DS relocation (0x%lx)\n",
				       me->name, value);
				वापस -ENOEXEC;
			पूर्ण
			*((uपूर्णांक16_t *) location)
				= (*((uपूर्णांक16_t *) location) & ~0xfffc)
				| (value & 0xfffc);
			अवरोध;

		हाल R_PPC64_TOC16_LO_DS:
			/* Subtract TOC poपूर्णांकer */
			value -= my_r2(sechdrs, me);
			अगर ((value & 3) != 0) अणु
				pr_err("%s: bad TOC16_LO_DS relocation (0x%lx)\n",
				       me->name, value);
				वापस -ENOEXEC;
			पूर्ण
			*((uपूर्णांक16_t *) location)
				= (*((uपूर्णांक16_t *) location) & ~0xfffc)
				| (value & 0xfffc);
			अवरोध;

		हाल R_PPC64_TOC16_HA:
			/* Subtract TOC poपूर्णांकer */
			value -= my_r2(sechdrs, me);
			value = ((value + 0x8000) >> 16);
			*((uपूर्णांक16_t *) location)
				= (*((uपूर्णांक16_t *) location) & ~0xffff)
				| (value & 0xffff);
			अवरोध;

		हाल R_PPC_REL24:
			/* FIXME: Handle weak symbols here --RR */
			अगर (sym->st_shndx == SHN_UNDEF ||
			    sym->st_shndx == SHN_LIVEPATCH) अणु
				/* External: go via stub */
				value = stub_क्रम_addr(sechdrs, value, me,
						strtab + sym->st_name);
				अगर (!value)
					वापस -ENOENT;
				अगर (!restore_r2(strtab + sym->st_name,
							(u32 *)location + 1, me))
					वापस -ENOEXEC;
			पूर्ण अन्यथा
				value += local_entry_offset(sym);

			/* Convert value to relative */
			value -= (अचिन्हित दीर्घ)location;
			अगर (value + 0x2000000 > 0x3ffffff || (value & 3) != 0)अणु
				pr_err("%s: REL24 %li out of range!\n",
				       me->name, (दीर्घ पूर्णांक)value);
				वापस -ENOEXEC;
			पूर्ण

			/* Only replace bits 2 through 26 */
			*(uपूर्णांक32_t *)location
				= (*(uपूर्णांक32_t *)location & ~0x03fffffc)
				| (value & 0x03fffffc);
			अवरोध;

		हाल R_PPC64_REL64:
			/* 64 bits relative (used by features fixups) */
			*location = value - (अचिन्हित दीर्घ)location;
			अवरोध;

		हाल R_PPC64_REL32:
			/* 32 bits relative (used by relative exception tables) */
			/* Convert value to relative */
			value -= (अचिन्हित दीर्घ)location;
			अगर (value + 0x80000000 > 0xffffffff) अणु
				pr_err("%s: REL32 %li out of range!\n",
				       me->name, (दीर्घ पूर्णांक)value);
				वापस -ENOEXEC;
			पूर्ण
			*(u32 *)location = value;
			अवरोध;

		हाल R_PPC64_TOCSAVE:
			/*
			 * Marker reloc indicates we करोn't have to save r2.
			 * That would only save us one inकाष्ठाion, so ignore
			 * it.
			 */
			अवरोध;

		हाल R_PPC64_ENTRY:
			/*
			 * Optimize ELFv2 large code model entry poपूर्णांक अगर
			 * the TOC is within 2GB range of current location.
			 */
			value = my_r2(sechdrs, me) - (अचिन्हित दीर्घ)location;
			अगर (value + 0x80008000 > 0xffffffff)
				अवरोध;
			/*
			 * Check क्रम the large code model prolog sequence:
		         *	ld r2, ...(r12)
			 *	add r2, r2, r12
			 */
			अगर ((((uपूर्णांक32_t *)location)[0] & ~0xfffc) !=
			    (PPC_INST_LD | __PPC_RT(R2) | __PPC_RA(R12)))
				अवरोध;
			अगर (((uपूर्णांक32_t *)location)[1] !=
			    (PPC_INST_ADD | __PPC_RT(R2) | __PPC_RA(R2) | __PPC_RB(R12)))
				अवरोध;
			/*
			 * If found, replace it with:
			 *	addis r2, r12, (.TOC.-func)@ha
			 *	addi  r2,  r2, (.TOC.-func)@l
			 */
			((uपूर्णांक32_t *)location)[0] = PPC_INST_ADDIS | __PPC_RT(R2) |
						    __PPC_RA(R12) | PPC_HA(value);
			((uपूर्णांक32_t *)location)[1] = PPC_INST_ADDI | __PPC_RT(R2) |
						    __PPC_RA(R2) | PPC_LO(value);
			अवरोध;

		हाल R_PPC64_REL16_HA:
			/* Subtract location poपूर्णांकer */
			value -= (अचिन्हित दीर्घ)location;
			value = ((value + 0x8000) >> 16);
			*((uपूर्णांक16_t *) location)
				= (*((uपूर्णांक16_t *) location) & ~0xffff)
				| (value & 0xffff);
			अवरोध;

		हाल R_PPC64_REL16_LO:
			/* Subtract location poपूर्णांकer */
			value -= (अचिन्हित दीर्घ)location;
			*((uपूर्णांक16_t *) location)
				= (*((uपूर्णांक16_t *) location) & ~0xffff)
				| (value & 0xffff);
			अवरोध;

		शेष:
			pr_err("%s: Unknown ADD relocation: %lu\n",
			       me->name,
			       (अचिन्हित दीर्घ)ELF64_R_TYPE(rela[i].r_info));
			वापस -ENOEXEC;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_DYNAMIC_FTRACE
पूर्णांक module_trampoline_target(काष्ठा module *mod, अचिन्हित दीर्घ addr,
			     अचिन्हित दीर्घ *target)
अणु
	काष्ठा ppc64_stub_entry *stub;
	func_desc_t funcdata;
	u32 magic;

	अगर (!within_module_core(addr, mod)) अणु
		pr_err("%s: stub %lx not in module %s\n", __func__, addr, mod->name);
		वापस -EFAULT;
	पूर्ण

	stub = (काष्ठा ppc64_stub_entry *)addr;

	अगर (copy_from_kernel_nofault(&magic, &stub->magic,
			माप(magic))) अणु
		pr_err("%s: fault reading magic for stub %lx for %s\n", __func__, addr, mod->name);
		वापस -EFAULT;
	पूर्ण

	अगर (magic != STUB_MAGIC) अणु
		pr_err("%s: bad magic for stub %lx for %s\n", __func__, addr, mod->name);
		वापस -EFAULT;
	पूर्ण

	अगर (copy_from_kernel_nofault(&funcdata, &stub->funcdata,
			माप(funcdata))) अणु
		pr_err("%s: fault reading funcdata for stub %lx for %s\n", __func__, addr, mod->name);
                वापस -EFAULT;
	पूर्ण

	*target = stub_func_addr(funcdata);

	वापस 0;
पूर्ण

पूर्णांक module_finalize_ftrace(काष्ठा module *mod, स्थिर Elf_Shdr *sechdrs)
अणु
	mod->arch.tramp = stub_क्रम_addr(sechdrs,
					(अचिन्हित दीर्घ)ftrace_caller,
					mod,
					"ftrace_caller");
#अगर_घोषित CONFIG_DYNAMIC_FTRACE_WITH_REGS
	mod->arch.tramp_regs = stub_क्रम_addr(sechdrs,
					(अचिन्हित दीर्घ)ftrace_regs_caller,
					mod,
					"ftrace_regs_caller");
	अगर (!mod->arch.tramp_regs)
		वापस -ENOENT;
#पूर्ण_अगर

	अगर (!mod->arch.tramp)
		वापस -ENOENT;

	वापस 0;
पूर्ण
#पूर्ण_अगर
