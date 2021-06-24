<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Kernel module help क्रम sparc64.
 *
 * Copyright (C) 2001 Rusty Russell.
 * Copyright (C) 2002 David S. Miller.
 */

#समावेश <linux/moduleloader.h>
#समावेश <linux/kernel.h>
#समावेश <linux/elf.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/fs.h>
#समावेश <linux/gfp.h>
#समावेश <linux/माला.स>
#समावेश <linux/प्रकार.स>
#समावेश <linux/mm.h>

#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/spitfire.h>
#समावेश <यंत्र/cacheflush.h>

#समावेश "entry.h"

#अगर_घोषित CONFIG_SPARC64

#समावेश <linux/jump_label.h>

अटल व्योम *module_map(अचिन्हित दीर्घ size)
अणु
	अगर (PAGE_ALIGN(size) > MODULES_LEN)
		वापस शून्य;
	वापस __vदो_स्मृति_node_range(size, 1, MODULES_VADDR, MODULES_END,
				GFP_KERNEL, PAGE_KERNEL, 0, NUMA_NO_NODE,
				__builtin_वापस_address(0));
पूर्ण
#अन्यथा
अटल व्योम *module_map(अचिन्हित दीर्घ size)
अणु
	वापस vदो_स्मृति(size);
पूर्ण
#पूर्ण_अगर /* CONFIG_SPARC64 */

व्योम *module_alloc(अचिन्हित दीर्घ size)
अणु
	व्योम *ret;

	ret = module_map(size);
	अगर (ret)
		स_रखो(ret, 0, size);

	वापस ret;
पूर्ण

/* Make generic code ignore STT_REGISTER dummy undefined symbols.  */
पूर्णांक module_frob_arch_sections(Elf_Ehdr *hdr,
			      Elf_Shdr *sechdrs,
			      अक्षर *secstrings,
			      काष्ठा module *mod)
अणु
	अचिन्हित पूर्णांक symidx;
	Elf_Sym *sym;
	अक्षर *strtab;
	पूर्णांक i;

	क्रम (symidx = 0; sechdrs[symidx].sh_type != SHT_SYMTAB; symidx++) अणु
		अगर (symidx == hdr->e_shnum-1) अणु
			prपूर्णांकk("%s: no symtab found.\n", mod->name);
			वापस -ENOEXEC;
		पूर्ण
	पूर्ण
	sym = (Elf_Sym *)sechdrs[symidx].sh_addr;
	strtab = (अक्षर *)sechdrs[sechdrs[symidx].sh_link].sh_addr;

	क्रम (i = 1; i < sechdrs[symidx].sh_size / माप(Elf_Sym); i++) अणु
		अगर (sym[i].st_shndx == SHN_UNDEF) अणु
			अगर (ELF_ST_TYPE(sym[i].st_info) == STT_REGISTER)
				sym[i].st_shndx = SHN_ABS;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक apply_relocate_add(Elf_Shdr *sechdrs,
		       स्थिर अक्षर *strtab,
		       अचिन्हित पूर्णांक symindex,
		       अचिन्हित पूर्णांक rअन्यथाc,
		       काष्ठा module *me)
अणु
	अचिन्हित पूर्णांक i;
	Elf_Rela *rel = (व्योम *)sechdrs[rअन्यथाc].sh_addr;
	Elf_Sym *sym;
	u8 *location;
	u32 *loc32;

	क्रम (i = 0; i < sechdrs[rअन्यथाc].sh_size / माप(*rel); i++) अणु
		Elf_Addr v;

		/* This is where to make the change */
		location = (u8 *)sechdrs[sechdrs[rअन्यथाc].sh_info].sh_addr
			+ rel[i].r_offset;
		loc32 = (u32 *) location;

#अगर_घोषित CONFIG_SPARC64
		BUG_ON(((u64)location >> (u64)32) != (u64)0);
#पूर्ण_अगर /* CONFIG_SPARC64 */

		/* This is the symbol it is referring to.  Note that all
		   undefined symbols have been resolved.  */
		sym = (Elf_Sym *)sechdrs[symindex].sh_addr
			+ ELF_R_SYM(rel[i].r_info);
		v = sym->st_value + rel[i].r_addend;

		चयन (ELF_R_TYPE(rel[i].r_info) & 0xff) अणु
		हाल R_SPARC_DISP32:
			v -= (Elf_Addr) location;
			*loc32 = v;
			अवरोध;
#अगर_घोषित CONFIG_SPARC64
		हाल R_SPARC_64:
			location[0] = v >> 56;
			location[1] = v >> 48;
			location[2] = v >> 40;
			location[3] = v >> 32;
			location[4] = v >> 24;
			location[5] = v >> 16;
			location[6] = v >>  8;
			location[7] = v >>  0;
			अवरोध;

		हाल R_SPARC_WDISP19:
			v -= (Elf_Addr) location;
			*loc32 = (*loc32 & ~0x7ffff) |
				((v >> 2) & 0x7ffff);
			अवरोध;

		हाल R_SPARC_OLO10:
			*loc32 = (*loc32 & ~0x1fff) |
				(((v & 0x3ff) +
				  (ELF_R_TYPE(rel[i].r_info) >> 8))
				 & 0x1fff);
			अवरोध;
#पूर्ण_अगर /* CONFIG_SPARC64 */

		हाल R_SPARC_32:
		हाल R_SPARC_UA32:
			location[0] = v >> 24;
			location[1] = v >> 16;
			location[2] = v >>  8;
			location[3] = v >>  0;
			अवरोध;

		हाल R_SPARC_WDISP30:
			v -= (Elf_Addr) location;
			*loc32 = (*loc32 & ~0x3fffffff) |
				((v >> 2) & 0x3fffffff);
			अवरोध;

		हाल R_SPARC_WDISP22:
			v -= (Elf_Addr) location;
			*loc32 = (*loc32 & ~0x3fffff) |
				((v >> 2) & 0x3fffff);
			अवरोध;

		हाल R_SPARC_LO10:
			*loc32 = (*loc32 & ~0x3ff) | (v & 0x3ff);
			अवरोध;

		हाल R_SPARC_HI22:
			*loc32 = (*loc32 & ~0x3fffff) |
				((v >> 10) & 0x3fffff);
			अवरोध;

		शेष:
			prपूर्णांकk(KERN_ERR "module %s: Unknown relocation: %x\n",
			       me->name,
			       (पूर्णांक) (ELF_R_TYPE(rel[i].r_info) & 0xff));
			वापस -ENOEXEC;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_SPARC64
अटल व्योम करो_patch_sections(स्थिर Elf_Ehdr *hdr,
			      स्थिर Elf_Shdr *sechdrs)
अणु
	स्थिर Elf_Shdr *s, *sun4v_1insn = शून्य, *sun4v_2insn = शून्य;
	अक्षर *secstrings = (व्योम *)hdr + sechdrs[hdr->e_shstrndx].sh_offset;

	क्रम (s = sechdrs; s < sechdrs + hdr->e_shnum; s++) अणु
		अगर (!म_भेद(".sun4v_1insn_patch", secstrings + s->sh_name))
			sun4v_1insn = s;
		अगर (!म_भेद(".sun4v_2insn_patch", secstrings + s->sh_name))
			sun4v_2insn = s;
	पूर्ण

	अगर (sun4v_1insn && tlb_type == hypervisor) अणु
		व्योम *p = (व्योम *) sun4v_1insn->sh_addr;
		sun4v_patch_1insn_range(p, p + sun4v_1insn->sh_size);
	पूर्ण
	अगर (sun4v_2insn && tlb_type == hypervisor) अणु
		व्योम *p = (व्योम *) sun4v_2insn->sh_addr;
		sun4v_patch_2insn_range(p, p + sun4v_2insn->sh_size);
	पूर्ण
पूर्ण

पूर्णांक module_finalize(स्थिर Elf_Ehdr *hdr,
		    स्थिर Elf_Shdr *sechdrs,
		    काष्ठा module *me)
अणु
	/* make jump label nops */
	jump_label_apply_nops(me);

	करो_patch_sections(hdr, sechdrs);

	/* Cheetah's I-cache is fully coherent.  */
	अगर (tlb_type == spitfire) अणु
		अचिन्हित दीर्घ va;

		flushw_all();
		क्रम (va =  0; va < (PAGE_SIZE << 1); va += 32)
			spitfire_put_icache_tag(va, 0x0);
		__यंत्र__ __अस्थिर__("flush %g6");
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_SPARC64 */
