<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*  Kernel module help क्रम PPC.
    Copyright (C) 2001 Rusty Russell.

*/

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/moduleloader.h>
#समावेश <linux/elf.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/fs.h>
#समावेश <linux/माला.स>
#समावेश <linux/kernel.h>
#समावेश <linux/ftrace.h>
#समावेश <linux/cache.h>
#समावेश <linux/bug.h>
#समावेश <linux/sort.h>
#समावेश <यंत्र/setup.h>

/* Count how many dअगरferent relocations (dअगरferent symbol, dअगरferent
   addend) */
अटल अचिन्हित पूर्णांक count_relocs(स्थिर Elf32_Rela *rela, अचिन्हित पूर्णांक num)
अणु
	अचिन्हित पूर्णांक i, r_info, r_addend, _count_relocs;

	_count_relocs = 0;
	r_info = 0;
	r_addend = 0;
	क्रम (i = 0; i < num; i++)
		/* Only count 24-bit relocs, others करोn't need stubs */
		अगर (ELF32_R_TYPE(rela[i].r_info) == R_PPC_REL24 &&
		    (r_info != ELF32_R_SYM(rela[i].r_info) ||
		     r_addend != rela[i].r_addend)) अणु
			_count_relocs++;
			r_info = ELF32_R_SYM(rela[i].r_info);
			r_addend = rela[i].r_addend;
		पूर्ण

#अगर_घोषित CONFIG_DYNAMIC_FTRACE
	_count_relocs++;	/* add one क्रम ftrace_caller */
#पूर्ण_अगर
	वापस _count_relocs;
पूर्ण

अटल पूर्णांक relacmp(स्थिर व्योम *_x, स्थिर व्योम *_y)
अणु
	स्थिर Elf32_Rela *x, *y;

	y = (Elf32_Rela *)_x;
	x = (Elf32_Rela *)_y;

	/* Compare the entire r_info (as opposed to ELF32_R_SYM(r_info) only) to
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

/* Get the potential trampolines size required of the init and
   non-init sections */
अटल अचिन्हित दीर्घ get_plt_size(स्थिर Elf32_Ehdr *hdr,
				  स्थिर Elf32_Shdr *sechdrs,
				  स्थिर अक्षर *secstrings,
				  पूर्णांक is_init)
अणु
	अचिन्हित दीर्घ ret = 0;
	अचिन्हित i;

	/* Everything marked ALLOC (this includes the exported
           symbols) */
	क्रम (i = 1; i < hdr->e_shnum; i++) अणु
		/* If it's called *.init*, and we're not init, we're
                   not पूर्णांकerested */
		अगर ((म_माला(secstrings + sechdrs[i].sh_name, ".init") != शून्य)
		    != is_init)
			जारी;

		/* We करोn't want to look at debug sections. */
		अगर (म_माला(secstrings + sechdrs[i].sh_name, ".debug"))
			जारी;

		अगर (sechdrs[i].sh_type == SHT_RELA) अणु
			pr_debug("Found relocations in section %u\n", i);
			pr_debug("Ptr: %p.  Number: %u\n",
			       (व्योम *)hdr + sechdrs[i].sh_offset,
			       sechdrs[i].sh_size / माप(Elf32_Rela));

			/* Sort the relocation inक्रमmation based on a symbol and
			 * addend key. This is a stable O(n*log n) complनिकासy
			 * alogrithm but it will reduce the complनिकासy of
			 * count_relocs() to linear complनिकासy O(n)
			 */
			sort((व्योम *)hdr + sechdrs[i].sh_offset,
			     sechdrs[i].sh_size / माप(Elf32_Rela),
			     माप(Elf32_Rela), relacmp, शून्य);

			ret += count_relocs((व्योम *)hdr
					     + sechdrs[i].sh_offset,
					     sechdrs[i].sh_size
					     / माप(Elf32_Rela))
				* माप(काष्ठा ppc_plt_entry);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक module_frob_arch_sections(Elf32_Ehdr *hdr,
			      Elf32_Shdr *sechdrs,
			      अक्षर *secstrings,
			      काष्ठा module *me)
अणु
	अचिन्हित पूर्णांक i;

	/* Find .plt and .init.plt sections */
	क्रम (i = 0; i < hdr->e_shnum; i++) अणु
		अगर (म_भेद(secstrings + sechdrs[i].sh_name, ".init.plt") == 0)
			me->arch.init_plt_section = i;
		अन्यथा अगर (म_भेद(secstrings + sechdrs[i].sh_name, ".plt") == 0)
			me->arch.core_plt_section = i;
	पूर्ण
	अगर (!me->arch.core_plt_section || !me->arch.init_plt_section) अणु
		pr_err("Module doesn't contain .plt or .init.plt sections.\n");
		वापस -ENOEXEC;
	पूर्ण

	/* Override their sizes */
	sechdrs[me->arch.core_plt_section].sh_size
		= get_plt_size(hdr, sechdrs, secstrings, 0);
	sechdrs[me->arch.init_plt_section].sh_size
		= get_plt_size(hdr, sechdrs, secstrings, 1);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक entry_matches(काष्ठा ppc_plt_entry *entry, Elf32_Addr val)
अणु
	अगर (entry->jump[0] != (PPC_INST_ADDIS | __PPC_RT(R12) | PPC_HA(val)))
		वापस 0;
	अगर (entry->jump[1] != (PPC_INST_ADDI | __PPC_RT(R12) | __PPC_RA(R12) |
			       PPC_LO(val)))
		वापस 0;
	वापस 1;
पूर्ण

/* Set up a trampoline in the PLT to bounce us to the distant function */
अटल uपूर्णांक32_t करो_plt_call(व्योम *location,
			    Elf32_Addr val,
			    स्थिर Elf32_Shdr *sechdrs,
			    काष्ठा module *mod)
अणु
	काष्ठा ppc_plt_entry *entry;

	pr_debug("Doing plt for call to 0x%x at 0x%x\n", val, (अचिन्हित पूर्णांक)location);
	/* Init, or core PLT? */
	अगर (location >= mod->core_layout.base
	    && location < mod->core_layout.base + mod->core_layout.size)
		entry = (व्योम *)sechdrs[mod->arch.core_plt_section].sh_addr;
	अन्यथा
		entry = (व्योम *)sechdrs[mod->arch.init_plt_section].sh_addr;

	/* Find this entry, or अगर that fails, the next avail. entry */
	जबतक (entry->jump[0]) अणु
		अगर (entry_matches(entry, val)) वापस (uपूर्णांक32_t)entry;
		entry++;
	पूर्ण

	/*
	 * lis r12, sym@ha
	 * addi r12, r12, sym@l
	 * mtctr r12
	 * bctr
	 */
	entry->jump[0] = PPC_INST_ADDIS | __PPC_RT(R12) | PPC_HA(val);
	entry->jump[1] = PPC_INST_ADDI | __PPC_RT(R12) | __PPC_RA(R12) | PPC_LO(val);
	entry->jump[2] = PPC_INST_MTCTR | __PPC_RS(R12);
	entry->jump[3] = PPC_INST_BCTR;

	pr_debug("Initialized plt for 0x%x at %p\n", val, entry);
	वापस (uपूर्णांक32_t)entry;
पूर्ण

पूर्णांक apply_relocate_add(Elf32_Shdr *sechdrs,
		       स्थिर अक्षर *strtab,
		       अचिन्हित पूर्णांक symindex,
		       अचिन्हित पूर्णांक rअन्यथाc,
		       काष्ठा module *module)
अणु
	अचिन्हित पूर्णांक i;
	Elf32_Rela *rela = (व्योम *)sechdrs[rअन्यथाc].sh_addr;
	Elf32_Sym *sym;
	uपूर्णांक32_t *location;
	uपूर्णांक32_t value;

	pr_debug("Applying ADD relocate section %u to %u\n", rअन्यथाc,
	       sechdrs[rअन्यथाc].sh_info);
	क्रम (i = 0; i < sechdrs[rअन्यथाc].sh_size / माप(*rela); i++) अणु
		/* This is where to make the change */
		location = (व्योम *)sechdrs[sechdrs[rअन्यथाc].sh_info].sh_addr
			+ rela[i].r_offset;
		/* This is the symbol it is referring to.  Note that all
		   undefined symbols have been resolved.  */
		sym = (Elf32_Sym *)sechdrs[symindex].sh_addr
			+ ELF32_R_SYM(rela[i].r_info);
		/* `Everything is relative'. */
		value = sym->st_value + rela[i].r_addend;

		चयन (ELF32_R_TYPE(rela[i].r_info)) अणु
		हाल R_PPC_ADDR32:
			/* Simply set it */
			*(uपूर्णांक32_t *)location = value;
			अवरोध;

		हाल R_PPC_ADDR16_LO:
			/* Low half of the symbol */
			*(uपूर्णांक16_t *)location = value;
			अवरोध;

		हाल R_PPC_ADDR16_HI:
			/* Higher half of the symbol */
			*(uपूर्णांक16_t *)location = (value >> 16);
			अवरोध;

		हाल R_PPC_ADDR16_HA:
			/* Sign-adjusted lower 16 bits: PPC ELF ABI says:
			   (((x >> 16) + ((x & 0x8000) ? 1 : 0))) & 0xFFFF.
			   This is the same, only sane.
			 */
			*(uपूर्णांक16_t *)location = (value + 0x8000) >> 16;
			अवरोध;

		हाल R_PPC_REL24:
			अगर ((पूर्णांक)(value - (uपूर्णांक32_t)location) < -0x02000000
			    || (पूर्णांक)(value - (uपूर्णांक32_t)location) >= 0x02000000)
				value = करो_plt_call(location, value,
						    sechdrs, module);

			/* Only replace bits 2 through 26 */
			pr_debug("REL24 value = %08X. location = %08X\n",
			       value, (uपूर्णांक32_t)location);
			pr_debug("Location before: %08X.\n",
			       *(uपूर्णांक32_t *)location);
			*(uपूर्णांक32_t *)location
				= (*(uपूर्णांक32_t *)location & ~0x03fffffc)
				| ((value - (uपूर्णांक32_t)location)
				   & 0x03fffffc);
			pr_debug("Location after: %08X.\n",
			       *(uपूर्णांक32_t *)location);
			pr_debug("ie. jump to %08X+%08X = %08X\n",
			       *(uपूर्णांक32_t *)location & 0x03fffffc,
			       (uपूर्णांक32_t)location,
			       (*(uपूर्णांक32_t *)location & 0x03fffffc)
			       + (uपूर्णांक32_t)location);
			अवरोध;

		हाल R_PPC_REL32:
			/* 32-bit relative jump. */
			*(uपूर्णांक32_t *)location = value - (uपूर्णांक32_t)location;
			अवरोध;

		शेष:
			pr_err("%s: unknown ADD relocation: %u\n",
			       module->name,
			       ELF32_R_TYPE(rela[i].r_info));
			वापस -ENOEXEC;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_DYNAMIC_FTRACE
पूर्णांक module_finalize_ftrace(काष्ठा module *module, स्थिर Elf_Shdr *sechdrs)
अणु
	module->arch.tramp = करो_plt_call(module->core_layout.base,
					 (अचिन्हित दीर्घ)ftrace_caller,
					 sechdrs, module);
	अगर (!module->arch.tramp)
		वापस -ENOENT;

	वापस 0;
पूर्ण
#पूर्ण_अगर
