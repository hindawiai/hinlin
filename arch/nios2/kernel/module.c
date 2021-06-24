<शैली गुरु>
/*
 * Kernel module support क्रम Nios II.
 *
 * Copyright (C) 2004 Microtronix Datacom Ltd.
 *   Written by Wentao Xu <xuwentao@microtronix.com>
 * Copyright (C) 2001, 2003 Rusty Russell
 *
 * This file is subject to the terms and conditions of the GNU General
 * Public License.  See the file COPYING in the मुख्य directory of this
 * archive क्रम more details.
 */

#समावेश <linux/moduleloader.h>
#समावेश <linux/elf.h>
#समावेश <linux/mm.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/slab.h>
#समावेश <linux/fs.h>
#समावेश <linux/माला.स>
#समावेश <linux/kernel.h>

#समावेश <यंत्र/cacheflush.h>

/*
 * Modules should NOT be allocated with kदो_स्मृति क्रम (obvious) reasons.
 * But we करो it क्रम now to aव्योम relocation issues. CALL26/PCREL26 cannot reach
 * from 0x80000000 (vदो_स्मृति area) to 0xc00000000 (kernel) (kदो_स्मृति वापसs
 * addresses in 0xc0000000)
 */
व्योम *module_alloc(अचिन्हित दीर्घ size)
अणु
	अगर (size == 0)
		वापस शून्य;
	वापस kदो_स्मृति(size, GFP_KERNEL);
पूर्ण

/* Free memory वापसed from module_alloc */
व्योम module_memमुक्त(व्योम *module_region)
अणु
	kमुक्त(module_region);
पूर्ण

पूर्णांक apply_relocate_add(Elf32_Shdr *sechdrs, स्थिर अक्षर *strtab,
			अचिन्हित पूर्णांक symindex, अचिन्हित पूर्णांक rअन्यथाc,
			काष्ठा module *mod)
अणु
	अचिन्हित पूर्णांक i;
	Elf32_Rela *rela = (व्योम *)sechdrs[rअन्यथाc].sh_addr;

	pr_debug("Applying relocate section %u to %u\n", rअन्यथाc,
		 sechdrs[rअन्यथाc].sh_info);

	क्रम (i = 0; i < sechdrs[rअन्यथाc].sh_size / माप(*rela); i++) अणु
		/* This is where to make the change */
		uपूर्णांक32_t word;
		uपूर्णांक32_t *loc
			= ((व्योम *)sechdrs[sechdrs[rअन्यथाc].sh_info].sh_addr
			   + rela[i].r_offset);
		/* This is the symbol it is referring to.  Note that all
		   undefined symbols have been resolved.  */
		Elf32_Sym *sym
			= ((Elf32_Sym *)sechdrs[symindex].sh_addr
				+ ELF32_R_SYM(rela[i].r_info));
		uपूर्णांक32_t v = sym->st_value + rela[i].r_addend;

		pr_debug("reltype %d 0x%x name:<%s>\n",
			ELF32_R_TYPE(rela[i].r_info),
			rela[i].r_offset, strtab + sym->st_name);

		चयन (ELF32_R_TYPE(rela[i].r_info)) अणु
		हाल R_NIOS2_NONE:
			अवरोध;
		हाल R_NIOS2_BFD_RELOC_32:
			*loc += v;
			अवरोध;
		हाल R_NIOS2_PCREL16:
			v -= (uपूर्णांक32_t)loc + 4;
			अगर ((पूर्णांक32_t)v > 0x7fff ||
				(पूर्णांक32_t)v < -(पूर्णांक32_t)0x8000) अणु
				pr_err("module %s: relocation overflow\n",
					mod->name);
				वापस -ENOEXEC;
			पूर्ण
			word = *loc;
			*loc = ((((word >> 22) << 16) | (v & 0xffff)) << 6) |
				(word & 0x3f);
			अवरोध;
		हाल R_NIOS2_CALL26:
			अगर (v & 3) अणु
				pr_err("module %s: dangerous relocation\n",
					mod->name);
				वापस -ENOEXEC;
			पूर्ण
			अगर ((v >> 28) != ((uपूर्णांक32_t)loc >> 28)) अणु
				pr_err("module %s: relocation overflow\n",
					mod->name);
				वापस -ENOEXEC;
			पूर्ण
			*loc = (*loc & 0x3f) | ((v >> 2) << 6);
			अवरोध;
		हाल R_NIOS2_HI16:
			word = *loc;
			*loc = ((((word >> 22) << 16) |
				((v >> 16) & 0xffff)) << 6) | (word & 0x3f);
			अवरोध;
		हाल R_NIOS2_LO16:
			word = *loc;
			*loc = ((((word >> 22) << 16) | (v & 0xffff)) << 6) |
					(word & 0x3f);
			अवरोध;
		हाल R_NIOS2_HIADJ16:
			अणु
				Elf32_Addr word2;

				word = *loc;
				word2 = ((v >> 16) + ((v >> 15) & 1)) & 0xffff;
				*loc = ((((word >> 22) << 16) | word2) << 6) |
						(word & 0x3f);
			पूर्ण
			अवरोध;

		शेष:
			pr_err("module %s: Unknown reloc: %u\n",
				mod->name, ELF32_R_TYPE(rela[i].r_info));
			वापस -ENOEXEC;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक module_finalize(स्थिर Elf_Ehdr *hdr, स्थिर Elf_Shdr *sechdrs,
			काष्ठा module *me)
अणु
	flush_cache_all();
	वापस 0;
पूर्ण
