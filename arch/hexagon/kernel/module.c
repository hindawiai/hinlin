<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Kernel module loader क्रम Hexagon
 *
 * Copyright (c) 2010-2011, The Linux Foundation. All rights reserved.
 */

#समावेश <यंत्र/module.h>
#समावेश <linux/elf.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleloader.h>
#समावेश <linux/vदो_स्मृति.h>

#अगर 0
#घोषणा DEBUGP prपूर्णांकk
#अन्यथा
#घोषणा DEBUGP(fmt , ...)
#पूर्ण_अगर

/*
 * module_frob_arch_sections - tweak got/plt sections.
 * @hdr - poपूर्णांकer to elf header
 * @sechdrs - poपूर्णांकer to elf load section headers
 * @secstrings - symbol names
 * @mod - poपूर्णांकer to module
 */
पूर्णांक module_frob_arch_sections(Elf_Ehdr *hdr, Elf_Shdr *sechdrs,
				अक्षर *secstrings,
				काष्ठा module *mod)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक found = 0;

	/* Look क्रम .plt and/or .got.plt and/or .init.plt sections */
	क्रम (i = 0; i < hdr->e_shnum; i++) अणु
		DEBUGP("Section %d is %s\n", i,
		       secstrings + sechdrs[i].sh_name);
		अगर (म_भेद(secstrings + sechdrs[i].sh_name, ".plt") == 0)
			found = i+1;
		अगर (म_भेद(secstrings + sechdrs[i].sh_name, ".got.plt") == 0)
			found = i+1;
		अगर (म_भेद(secstrings + sechdrs[i].sh_name, ".rela.plt") == 0)
			found = i+1;
	पूर्ण

	/* At this समय, we करोn't support modules comiled with -shared */
	अगर (found) अणु
		prपूर्णांकk(KERN_WARNING
			"Module '%s' contains unexpected .plt/.got sections.\n",
			mod->name);
		/*  वापस -ENOEXEC;  */
	पूर्ण

	वापस 0;
पूर्ण

/*
 * apply_relocate_add - perक्रमm rela relocations.
 * @sechdrs - poपूर्णांकer to section headers
 * @strtab - some sort of start address?
 * @symindex - symbol index offset or something?
 * @rअन्यथाc - address to relocate to?
 * @module - poपूर्णांकer to module
 *
 * Perक्रमm rela relocations.
 */
पूर्णांक apply_relocate_add(Elf_Shdr *sechdrs, स्थिर अक्षर *strtab,
			अचिन्हित पूर्णांक symindex, अचिन्हित पूर्णांक rअन्यथाc,
			काष्ठा module *module)
अणु
	अचिन्हित पूर्णांक i;
	Elf32_Sym *sym;
	uपूर्णांक32_t *location;
	uपूर्णांक32_t value;
	अचिन्हित पूर्णांक nrelocs = sechdrs[rअन्यथाc].sh_size / माप(Elf32_Rela);
	Elf32_Rela *rela = (व्योम *)sechdrs[rअन्यथाc].sh_addr;
	Elf32_Word sym_info = sechdrs[rअन्यथाc].sh_info;
	Elf32_Sym *sym_base = (Elf32_Sym *) sechdrs[symindex].sh_addr;
	व्योम *loc_base = (व्योम *) sechdrs[sym_info].sh_addr;

	DEBUGP("Applying relocations in section %u to section %u base=%p\n",
	       rअन्यथाc, sym_info, loc_base);

	क्रम (i = 0; i < nrelocs; i++) अणु

		/* Symbol to relocate */
		sym = sym_base + ELF32_R_SYM(rela[i].r_info);

		/* Where to make the change */
		location = loc_base + rela[i].r_offset;

		/* `Everything is relative'. */
		value = sym->st_value + rela[i].r_addend;

		DEBUGP("%d: value=%08x loc=%p reloc=%d symbol=%s\n",
		       i, value, location, ELF32_R_TYPE(rela[i].r_info),
		       sym->st_name ?
		       &strtab[sym->st_name] : "(anonymous)");

		चयन (ELF32_R_TYPE(rela[i].r_info)) अणु
		हाल R_HEXAGON_B22_PCREL: अणु
			पूर्णांक dist = (पूर्णांक)(value - (uपूर्णांक32_t)location);
			अगर ((dist < -0x00800000) ||
			    (dist >= 0x00800000)) अणु
				prपूर्णांकk(KERN_ERR
				       "%s: %s: %08x=%08x-%08x %s\n",
				       module->name,
				       "R_HEXAGON_B22_PCREL reloc out of range",
				       dist, value, (uपूर्णांक32_t)location,
				       sym->st_name ?
				       &strtab[sym->st_name] : "(anonymous)");
				वापस -ENOEXEC;
			पूर्ण
			DEBUGP("B22_PCREL contents: %08X.\n", *location);
			*location &= ~0x01ff3fff;
			*location |= 0x00003fff & dist;
			*location |= 0x01ff0000 & (dist<<2);
			DEBUGP("Contents after reloc: %08x\n", *location);
			अवरोध;
		पूर्ण
		हाल R_HEXAGON_HI16:
			value = (value>>16) & 0xffff;
			fallthrough;
		हाल R_HEXAGON_LO16:
			*location &= ~0x00c03fff;
			*location |= value & 0x3fff;
			*location |= (value & 0xc000) << 8;
			अवरोध;
		हाल R_HEXAGON_32:
			*location = value;
			अवरोध;
		हाल R_HEXAGON_32_PCREL:
			*location = value - (uपूर्णांक32_t)location;
			अवरोध;
		हाल R_HEXAGON_PLT_B22_PCREL:
		हाल R_HEXAGON_GOTOFF_LO16:
		हाल R_HEXAGON_GOTOFF_HI16:
			prपूर्णांकk(KERN_ERR "%s: GOT/PLT relocations unsupported\n",
			       module->name);
			वापस -ENOEXEC;
		शेष:
			prपूर्णांकk(KERN_ERR "%s: unknown relocation: %u\n",
			       module->name,
			       ELF32_R_TYPE(rela[i].r_info));
			वापस -ENOEXEC;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण
