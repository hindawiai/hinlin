<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/moduleloader.h>
#समावेश <linux/elf.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/fs.h>
#समावेश <linux/माला.स>
#समावेश <linux/kernel.h>

#अगर 0
#घोषणा DEBUGP(fmt, ...) prपूर्णांकk(KERN_DEBUG pr_fmt(fmt), ##__VA_ARGS__)
#अन्यथा
#घोषणा DEBUGP(fmt, ...) no_prपूर्णांकk(KERN_DEBUG pr_fmt(fmt), ##__VA_ARGS__)
#पूर्ण_अगर

#अगर_घोषित CONFIG_MODULES

पूर्णांक apply_relocate(Elf32_Shdr *sechdrs,
		   स्थिर अक्षर *strtab,
		   अचिन्हित पूर्णांक symindex,
		   अचिन्हित पूर्णांक rअन्यथाc,
		   काष्ठा module *me)
अणु
	अचिन्हित पूर्णांक i;
	Elf32_Rel *rel = (व्योम *)sechdrs[rअन्यथाc].sh_addr;
	Elf32_Sym *sym;
	uपूर्णांक32_t *location;

	DEBUGP("Applying relocate section %u to %u\n", rअन्यथाc,
	       sechdrs[rअन्यथाc].sh_info);
	क्रम (i = 0; i < sechdrs[rअन्यथाc].sh_size / माप(*rel); i++) अणु
		/* This is where to make the change */
		location = (व्योम *)sechdrs[sechdrs[rअन्यथाc].sh_info].sh_addr
			+ rel[i].r_offset;
		/* This is the symbol it is referring to.  Note that all
		   undefined symbols have been resolved.  */
		sym = (Elf32_Sym *)sechdrs[symindex].sh_addr
			+ ELF32_R_SYM(rel[i].r_info);

		चयन (ELF32_R_TYPE(rel[i].r_info)) अणु
		हाल R_68K_32:
			/* We add the value पूर्णांकo the location given */
			*location += sym->st_value;
			अवरोध;
		हाल R_68K_PC32:
			/* Add the value, subtract its position */
			*location += sym->st_value - (uपूर्णांक32_t)location;
			अवरोध;
		शेष:
			pr_err("module %s: Unknown relocation: %u\n", me->name,
			       ELF32_R_TYPE(rel[i].r_info));
			वापस -ENOEXEC;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक apply_relocate_add(Elf32_Shdr *sechdrs,
		       स्थिर अक्षर *strtab,
		       अचिन्हित पूर्णांक symindex,
		       अचिन्हित पूर्णांक rअन्यथाc,
		       काष्ठा module *me)
अणु
	अचिन्हित पूर्णांक i;
	Elf32_Rela *rel = (व्योम *)sechdrs[rअन्यथाc].sh_addr;
	Elf32_Sym *sym;
	uपूर्णांक32_t *location;

	DEBUGP("Applying relocate_add section %u to %u\n", rअन्यथाc,
	       sechdrs[rअन्यथाc].sh_info);
	क्रम (i = 0; i < sechdrs[rअन्यथाc].sh_size / माप(*rel); i++) अणु
		/* This is where to make the change */
		location = (व्योम *)sechdrs[sechdrs[rअन्यथाc].sh_info].sh_addr
			+ rel[i].r_offset;
		/* This is the symbol it is referring to.  Note that all
		   undefined symbols have been resolved.  */
		sym = (Elf32_Sym *)sechdrs[symindex].sh_addr
			+ ELF32_R_SYM(rel[i].r_info);

		चयन (ELF32_R_TYPE(rel[i].r_info)) अणु
		हाल R_68K_32:
			/* We add the value पूर्णांकo the location given */
			*location = rel[i].r_addend + sym->st_value;
			अवरोध;
		हाल R_68K_PC32:
			/* Add the value, subtract its position */
			*location = rel[i].r_addend + sym->st_value - (uपूर्णांक32_t)location;
			अवरोध;
		शेष:
			pr_err("module %s: Unknown relocation: %u\n", me->name,
			       ELF32_R_TYPE(rel[i].r_info));
			वापस -ENOEXEC;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक module_finalize(स्थिर Elf_Ehdr *hdr,
		    स्थिर Elf_Shdr *sechdrs,
		    काष्ठा module *mod)
अणु
	module_fixup(mod, mod->arch.fixup_start, mod->arch.fixup_end);
	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_MODULES */

व्योम module_fixup(काष्ठा module *mod, काष्ठा m68k_fixup_info *start,
		  काष्ठा m68k_fixup_info *end)
अणु
#अगर_घोषित CONFIG_MMU
	काष्ठा m68k_fixup_info *fixup;

	क्रम (fixup = start; fixup < end; fixup++) अणु
		चयन (fixup->type) अणु
		हाल m68k_fixup_memoffset:
			*(u32 *)fixup->addr = m68k_memoffset;
			अवरोध;
		हाल m68k_fixup_vnode_shअगरt:
			*(u16 *)fixup->addr += m68k_virt_to_node_shअगरt;
			अवरोध;
		पूर्ण
	पूर्ण
#पूर्ण_अगर
पूर्ण
