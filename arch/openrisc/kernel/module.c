<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * OpenRISC module.c
 *
 * Linux architectural port borrowing liberally from similar works of
 * others.  All original copyrights apply as per the original source
 * declaration.
 *
 * Modअगरications क्रम the OpenRISC architecture:
 * Copyright (C) 2010-2011 Jonas Bonn <jonas@southpole.se>
 */

#समावेश <linux/moduleloader.h>
#समावेश <linux/elf.h>

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
		value = sym->st_value + rel[i].r_addend;

		चयन (ELF32_R_TYPE(rel[i].r_info)) अणु
		हाल R_OR32_32:
			*location = value;
			अवरोध;
		हाल R_OR32_CONST:
			*((uपूर्णांक16_t *)location + 1) = value;
			अवरोध;
		हाल R_OR32_CONSTH:
			*((uपूर्णांक16_t *)location + 1) = value >> 16;
			अवरोध;
		हाल R_OR32_JUMPTARG:
			value -= (uपूर्णांक32_t)location;
			value >>= 2;
			value &= 0x03ffffff;
			value |= *location & 0xfc000000;
			*location = value;
			अवरोध;
		शेष:
			pr_err("module %s: Unknown relocation: %u\n",
			       me->name, ELF32_R_TYPE(rel[i].r_info));
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
