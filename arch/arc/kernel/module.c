<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleloader.h>
#समावेश <linux/kernel.h>
#समावेश <linux/elf.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/slab.h>
#समावेश <linux/fs.h>
#समावेश <linux/माला.स>
#समावेश <यंत्र/unwind.h>

अटल अंतरभूत व्योम arc_ग_लिखो_me(अचिन्हित लघु *addr, अचिन्हित दीर्घ value)
अणु
	*addr = (value & 0xffff0000) >> 16;
	*(addr + 1) = (value & 0xffff);
पूर्ण

/*
 * This माला_लो called beक्रमe relocation loop in generic loader
 * Make a note of the section index of unwinding section
 */
पूर्णांक module_frob_arch_sections(Elf_Ehdr *hdr, Elf_Shdr *sechdrs,
			      अक्षर *secstr, काष्ठा module *mod)
अणु
#अगर_घोषित CONFIG_ARC_DW2_UNWIND
	mod->arch.unw_sec_idx = 0;
	mod->arch.unw_info = शून्य;
#पूर्ण_अगर
	mod->arch.secstr = secstr;
	वापस 0;
पूर्ण

व्योम module_arch_cleanup(काष्ठा module *mod)
अणु
#अगर_घोषित CONFIG_ARC_DW2_UNWIND
	अगर (mod->arch.unw_info)
		unwind_हटाओ_table(mod->arch.unw_info, 0);
#पूर्ण_अगर
पूर्ण

पूर्णांक apply_relocate_add(Elf32_Shdr *sechdrs,
		       स्थिर अक्षर *strtab,
		       अचिन्हित पूर्णांक symindex,	/* sec index क्रम sym tbl */
		       अचिन्हित पूर्णांक rअन्यथाc,	/* sec index क्रम relo sec */
		       काष्ठा module *module)
अणु
	पूर्णांक i, n, relo_type;
	Elf32_Rela *rel_entry = (व्योम *)sechdrs[rअन्यथाc].sh_addr;
	Elf32_Sym *sym_entry, *sym_sec;
	Elf32_Addr relocation, location, tgt_addr;
	अचिन्हित पूर्णांक tgtsec;

	/*
	 * @rअन्यथाc has relocations e.g. .rela.init.text
	 * @tgtsec is section to patch e.g. .init.text
	 */
	tgtsec = sechdrs[rअन्यथाc].sh_info;
	tgt_addr = sechdrs[tgtsec].sh_addr;
	sym_sec = (Elf32_Sym *) sechdrs[symindex].sh_addr;
	n = sechdrs[rअन्यथाc].sh_size / माप(*rel_entry);

	pr_debug("\nSection to fixup %s @%x\n",
		 module->arch.secstr + sechdrs[tgtsec].sh_name, tgt_addr);
	pr_debug("=========================================================\n");
	pr_debug("r_off\tr_add\tst_value ADDRESS  VALUE\n");
	pr_debug("=========================================================\n");

	/* Loop thru entries in relocation section */
	क्रम (i = 0; i < n; i++) अणु
		स्थिर अक्षर *s;

		/* This is where to make the change */
		location = tgt_addr + rel_entry[i].r_offset;

		/* This is the symbol it is referring to.  Note that all
		   undefined symbols have been resolved.  */
		sym_entry = sym_sec + ELF32_R_SYM(rel_entry[i].r_info);

		relocation = sym_entry->st_value + rel_entry[i].r_addend;

		अगर (sym_entry->st_name == 0 && ELF_ST_TYPE (sym_entry->st_info) == STT_SECTION) अणु
			s = module->arch.secstr + sechdrs[sym_entry->st_shndx].sh_name;
		पूर्ण अन्यथा अणु
			s = strtab + sym_entry->st_name;
		पूर्ण

		pr_debug("   %x\t%x\t%x %x %x [%s]\n",
			 rel_entry[i].r_offset, rel_entry[i].r_addend,
			 sym_entry->st_value, location, relocation, s);

		/* This assumes modules are built with -mदीर्घ-calls
		 * so any branches/jumps are असलolute 32 bit jmps
		 * global data access again is असल 32 bit.
		 * Both of these are handled by same relocation type
		 */
		relo_type = ELF32_R_TYPE(rel_entry[i].r_info);

		अगर (likely(R_ARC_32_ME == relo_type))	/* ME ( S + A ) */
			arc_ग_लिखो_me((अचिन्हित लघु *)location, relocation);
		अन्यथा अगर (R_ARC_32 == relo_type)		/* ( S + A ) */
			*((Elf32_Addr *) location) = relocation;
		अन्यथा अगर (R_ARC_32_PCREL == relo_type)	/* ( S + A ) - PDATA ) */
			*((Elf32_Addr *) location) = relocation - location;
		अन्यथा
			जाओ relo_err;

	पूर्ण

#अगर_घोषित CONFIG_ARC_DW2_UNWIND
	अगर (म_भेद(module->arch.secstr+sechdrs[tgtsec].sh_name, ".eh_frame") == 0)
		module->arch.unw_sec_idx = tgtsec;
#पूर्ण_अगर

	वापस 0;

relo_err:
	pr_err("%s: unknown relocation: %u\n",
		module->name, ELF32_R_TYPE(rel_entry[i].r_info));
	वापस -ENOEXEC;

पूर्ण

/* Just beक्रमe lअगरt off: After sections have been relocated, we add the
 * dwarf section to unwinder table pool
 * This couldn't be करोne in module_frob_arch_sections() because
 * relocations had not been applied by then
 */
पूर्णांक module_finalize(स्थिर Elf32_Ehdr *hdr, स्थिर Elf_Shdr *sechdrs,
		    काष्ठा module *mod)
अणु
#अगर_घोषित CONFIG_ARC_DW2_UNWIND
	व्योम *unw;
	पूर्णांक unwsec = mod->arch.unw_sec_idx;

	अगर (unwsec) अणु
		unw = unwind_add_table(mod, (व्योम *)sechdrs[unwsec].sh_addr,
				       sechdrs[unwsec].sh_size);
		mod->arch.unw_info = unw;
	पूर्ण
#पूर्ण_अगर
	वापस 0;
पूर्ण
