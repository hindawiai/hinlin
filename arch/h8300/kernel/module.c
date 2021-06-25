<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/moduleloader.h>
#समावेश <linux/elf.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/fs.h>
#समावेश <linux/माला.स>
#समावेश <linux/kernel.h>

पूर्णांक apply_relocate_add(Elf32_Shdr *sechdrs,
		       स्थिर अक्षर *strtab,
		       अचिन्हित पूर्णांक symindex,
		       अचिन्हित पूर्णांक rअन्यथाc,
		       काष्ठा module *me)
अणु
	अचिन्हित पूर्णांक i;
	Elf32_Rela *rela = (व्योम *)sechdrs[rअन्यथाc].sh_addr;

	pr_debug("Applying relocate section %u to %u\n", rअन्यथाc,
	       sechdrs[rअन्यथाc].sh_info);
	क्रम (i = 0; i < sechdrs[rअन्यथाc].sh_size / माप(*rela); i++) अणु
		/* This is where to make the change */
		uपूर्णांक32_t *loc =
			(uपूर्णांक32_t *)(sechdrs[sechdrs[rअन्यथाc].sh_info].sh_addr
					     + rela[i].r_offset);
		/* This is the symbol it is referring to.  Note that all
		   undefined symbols have been resolved.  */
		Elf32_Sym *sym = (Elf32_Sym *)sechdrs[symindex].sh_addr
			+ ELF32_R_SYM(rela[i].r_info);
		uपूर्णांक32_t v = sym->st_value + rela[i].r_addend;

		चयन (ELF32_R_TYPE(rela[i].r_info)) अणु
		हाल R_H8_सूची24R8:
			loc = (uपूर्णांक32_t *)((uपूर्णांक32_t)loc - 1);
			*loc = (*loc & 0xff000000) | ((*loc & 0xffffff) + v);
			अवरोध;
		हाल R_H8_सूची24A8:
			अगर (ELF32_R_SYM(rela[i].r_info))
				*loc += v;
			अवरोध;
		हाल R_H8_सूची32:
		हाल R_H8_सूची32A16:
			*loc += v;
			अवरोध;
		हाल R_H8_PCREL16:
			v -= (अचिन्हित दीर्घ)loc + 2;
			अगर ((Elf32_Sword)v > 0x7fff ||
			    (Elf32_Sword)v < -(Elf32_Sword)0x8000)
				जाओ overflow;
			अन्यथा
				*(अचिन्हित लघु *)loc = v;
			अवरोध;
		हाल R_H8_PCREL8:
			v -= (अचिन्हित दीर्घ)loc + 1;
			अगर ((Elf32_Sword)v > 0x7f ||
			    (Elf32_Sword)v < -(Elf32_Sword)0x80)
				जाओ overflow;
			अन्यथा
				*(अचिन्हित अक्षर *)loc = v;
			अवरोध;
		शेष:
			pr_err("module %s: Unknown relocation: %u\n",
			       me->name, ELF32_R_TYPE(rela[i].r_info));
			वापस -ENOEXEC;
		पूर्ण
	पूर्ण
	वापस 0;
 overflow:
	pr_err("module %s: relocation offset overflow: %08x\n",
	       me->name, rela[i].r_offset);
	वापस -ENOEXEC;
पूर्ण
