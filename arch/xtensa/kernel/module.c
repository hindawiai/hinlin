<शैली गुरु>
/*
 * arch/xtensa/kernel/module.c
 *
 * Module support.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2001 - 2006 Tensilica Inc.
 *
 * Chris Zankel <chris@zankel.net>
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleloader.h>
#समावेश <linux/elf.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/fs.h>
#समावेश <linux/माला.स>
#समावेश <linux/kernel.h>
#समावेश <linux/cache.h>

अटल पूर्णांक
decode_calln_opcode (अचिन्हित अक्षर *location)
अणु
#अगर_घोषित __XTENSA_EB__
	वापस (location[0] & 0xf0) == 0x50;
#पूर्ण_अगर
#अगर_घोषित __XTENSA_EL__
	वापस (location[0] & 0xf) == 0x5;
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक
decode_l32r_opcode (अचिन्हित अक्षर *location)
अणु
#अगर_घोषित __XTENSA_EB__
	वापस (location[0] & 0xf0) == 0x10;
#पूर्ण_अगर
#अगर_घोषित __XTENSA_EL__
	वापस (location[0] & 0xf) == 0x1;
#पूर्ण_अगर
पूर्ण

पूर्णांक apply_relocate_add(Elf32_Shdr *sechdrs,
		       स्थिर अक्षर *strtab,
		       अचिन्हित पूर्णांक symindex,
		       अचिन्हित पूर्णांक rअन्यथाc,
		       काष्ठा module *mod)
अणु
	अचिन्हित पूर्णांक i;
	Elf32_Rela *rela = (व्योम *)sechdrs[rअन्यथाc].sh_addr;
	Elf32_Sym *sym;
	अचिन्हित अक्षर *location;
	uपूर्णांक32_t value;

	pr_debug("Applying relocate section %u to %u\n", rअन्यथाc,
		 sechdrs[rअन्यथाc].sh_info);

	क्रम (i = 0; i < sechdrs[rअन्यथाc].sh_size / माप(*rela); i++) अणु
		location = (अक्षर *)sechdrs[sechdrs[rअन्यथाc].sh_info].sh_addr
			+ rela[i].r_offset;
		sym = (Elf32_Sym *)sechdrs[symindex].sh_addr
			+ ELF32_R_SYM(rela[i].r_info);
		value = sym->st_value + rela[i].r_addend;

		चयन (ELF32_R_TYPE(rela[i].r_info)) अणु
		हाल R_XTENSA_NONE:
		हाल R_XTENSA_DIFF8:
		हाल R_XTENSA_DIFF16:
		हाल R_XTENSA_DIFF32:
		हाल R_XTENSA_ASM_EXPAND:
			अवरोध;

		हाल R_XTENSA_32:
		हाल R_XTENSA_PLT:
			*(uपूर्णांक32_t *)location += value;
			अवरोध;

		हाल R_XTENSA_SLOT0_OP:
			अगर (decode_calln_opcode(location)) अणु
				value -= ((अचिन्हित दीर्घ)location & -4) + 4;
				अगर ((value & 3) != 0 ||
				    ((value + (1 << 19)) >> 20) != 0) अणु
					pr_err("%s: relocation out of range, "
					       "section %d reloc %d "
					       "sym '%s'\n",
					       mod->name, rअन्यथाc, i,
					       strtab + sym->st_name);
					वापस -ENOEXEC;
				पूर्ण
				value = (चिन्हित पूर्णांक)value >> 2;
#अगर_घोषित __XTENSA_EB__
				location[0] = ((location[0] & ~0x3) |
					    ((value >> 16) & 0x3));
				location[1] = (value >> 8) & 0xff;
				location[2] = value & 0xff;
#पूर्ण_अगर
#अगर_घोषित __XTENSA_EL__
				location[0] = ((location[0] & ~0xc0) |
					    ((value << 6) & 0xc0));
				location[1] = (value >> 2) & 0xff;
				location[2] = (value >> 10) & 0xff;
#पूर्ण_अगर
			पूर्ण अन्यथा अगर (decode_l32r_opcode(location)) अणु
				value -= (((अचिन्हित दीर्घ)location + 3) & -4);
				अगर ((value & 3) != 0 ||
				    (चिन्हित पूर्णांक)value >> 18 != -1) अणु
					pr_err("%s: relocation out of range, "
					       "section %d reloc %d "
					       "sym '%s'\n",
					       mod->name, rअन्यथाc, i,
					       strtab + sym->st_name);
					वापस -ENOEXEC;
				पूर्ण
				value = (चिन्हित पूर्णांक)value >> 2;

#अगर_घोषित __XTENSA_EB__
				location[1] = (value >> 8) & 0xff;
				location[2] = value & 0xff;
#पूर्ण_अगर
#अगर_घोषित __XTENSA_EL__
				location[1] = value & 0xff;
				location[2] = (value >> 8) & 0xff;
#पूर्ण_अगर
			पूर्ण
			/* FIXME: Ignore any other opcodes.  The Xtensa
			   assembler currently assumes that the linker will
			   always करो relaxation and so all PC-relative
			   opeअक्रमs need relocations.  (The assembler also
			   ग_लिखोs out the tentative PC-relative values,
			   assuming no link-समय relaxation, so it is usually
			   safe to ignore the relocations.)  If the
			   assembler's "--no-link-relax" flag can be made to
			   work, and अगर all kernel modules can be assembled
			   with that flag, then unexpected relocations could
			   be detected here.  */
			अवरोध;

		हाल R_XTENSA_SLOT1_OP:
		हाल R_XTENSA_SLOT2_OP:
		हाल R_XTENSA_SLOT3_OP:
		हाल R_XTENSA_SLOT4_OP:
		हाल R_XTENSA_SLOT5_OP:
		हाल R_XTENSA_SLOT6_OP:
		हाल R_XTENSA_SLOT7_OP:
		हाल R_XTENSA_SLOT8_OP:
		हाल R_XTENSA_SLOT9_OP:
		हाल R_XTENSA_SLOT10_OP:
		हाल R_XTENSA_SLOT11_OP:
		हाल R_XTENSA_SLOT12_OP:
		हाल R_XTENSA_SLOT13_OP:
		हाल R_XTENSA_SLOT14_OP:
			pr_err("%s: unexpected FLIX relocation: %u\n",
			       mod->name,
			       ELF32_R_TYPE(rela[i].r_info));
			वापस -ENOEXEC;

		हाल R_XTENSA_SLOT0_ALT:
		हाल R_XTENSA_SLOT1_ALT:
		हाल R_XTENSA_SLOT2_ALT:
		हाल R_XTENSA_SLOT3_ALT:
		हाल R_XTENSA_SLOT4_ALT:
		हाल R_XTENSA_SLOT5_ALT:
		हाल R_XTENSA_SLOT6_ALT:
		हाल R_XTENSA_SLOT7_ALT:
		हाल R_XTENSA_SLOT8_ALT:
		हाल R_XTENSA_SLOT9_ALT:
		हाल R_XTENSA_SLOT10_ALT:
		हाल R_XTENSA_SLOT11_ALT:
		हाल R_XTENSA_SLOT12_ALT:
		हाल R_XTENSA_SLOT13_ALT:
		हाल R_XTENSA_SLOT14_ALT:
			pr_err("%s: unexpected ALT relocation: %u\n",
			       mod->name,
			       ELF32_R_TYPE(rela[i].r_info));
			वापस -ENOEXEC;

		शेष:
			pr_err("%s: unexpected relocation: %u\n",
			       mod->name,
			       ELF32_R_TYPE(rela[i].r_info));
			वापस -ENOEXEC;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण
