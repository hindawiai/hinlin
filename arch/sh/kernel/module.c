<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*  Kernel module help क्रम SH.

    SHcompact version by Kaz Kojima and Paul Mundt.

    SHmedia bits:

	Copyright 2004 SuperH (UK) Ltd
	Author: Riअक्षरd Curnow

	Based on the sh version, and on code from the sh64-specअगरic parts of
	modutils, originally written by Riअक्षरd Curnow and Ben Gaster.
*/
#समावेश <linux/moduleloader.h>
#समावेश <linux/elf.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/bug.h>
#समावेश <linux/fs.h>
#समावेश <linux/माला.स>
#समावेश <linux/kernel.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <यंत्र/dwarf.h>

पूर्णांक apply_relocate_add(Elf32_Shdr *sechdrs,
		   स्थिर अक्षर *strtab,
		   अचिन्हित पूर्णांक symindex,
		   अचिन्हित पूर्णांक rअन्यथाc,
		   काष्ठा module *me)
अणु
	अचिन्हित पूर्णांक i;
	Elf32_Rela *rel = (व्योम *)sechdrs[rअन्यथाc].sh_addr;
	Elf32_Sym *sym;
	Elf32_Addr relocation;
	uपूर्णांक32_t *location;
	uपूर्णांक32_t value;

	pr_debug("Applying relocate section %u to %u\n", rअन्यथाc,
		 sechdrs[rअन्यथाc].sh_info);
	क्रम (i = 0; i < sechdrs[rअन्यथाc].sh_size / माप(*rel); i++) अणु
		/* This is where to make the change */
		location = (व्योम *)sechdrs[sechdrs[rअन्यथाc].sh_info].sh_addr
			+ rel[i].r_offset;
		/* This is the symbol it is referring to.  Note that all
		   undefined symbols have been resolved.  */
		sym = (Elf32_Sym *)sechdrs[symindex].sh_addr
			+ ELF32_R_SYM(rel[i].r_info);
		relocation = sym->st_value + rel[i].r_addend;

		चयन (ELF32_R_TYPE(rel[i].r_info)) अणु
		हाल R_SH_NONE:
			अवरोध;
		हाल R_SH_सूची32:
			value = get_unaligned(location);
			value += relocation;
			put_unaligned(value, location);
			अवरोध;
		हाल R_SH_REL32:
			relocation = (relocation - (Elf32_Addr) location);
			value = get_unaligned(location);
			value += relocation;
			put_unaligned(value, location);
			अवरोध;
		हाल R_SH_IMM_LOW16:
			*location = (*location & ~0x3fffc00) |
				((relocation & 0xffff) << 10);
			अवरोध;
		हाल R_SH_IMM_MEDLOW16:
			*location = (*location & ~0x3fffc00) |
				(((relocation >> 16) & 0xffff) << 10);
			अवरोध;
		हाल R_SH_IMM_LOW16_PCREL:
			relocation -= (Elf32_Addr) location;
			*location = (*location & ~0x3fffc00) |
				((relocation & 0xffff) << 10);
			अवरोध;
		हाल R_SH_IMM_MEDLOW16_PCREL:
			relocation -= (Elf32_Addr) location;
			*location = (*location & ~0x3fffc00) |
				(((relocation >> 16) & 0xffff) << 10);
			अवरोध;
		शेष:
			prपूर्णांकk(KERN_ERR "module %s: Unknown relocation: %u\n",
			       me->name, ELF32_R_TYPE(rel[i].r_info));
			वापस -ENOEXEC;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक module_finalize(स्थिर Elf_Ehdr *hdr,
		    स्थिर Elf_Shdr *sechdrs,
		    काष्ठा module *me)
अणु
	पूर्णांक ret = 0;

	ret |= module_dwarf_finalize(hdr, sechdrs, me);

	वापस ret;
पूर्ण

व्योम module_arch_cleanup(काष्ठा module *mod)
अणु
	module_dwarf_cleanup(mod);
पूर्ण
