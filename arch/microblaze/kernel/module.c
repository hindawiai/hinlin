<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2007-2009 Michal Simek <monstr@monstr.eu>
 * Copyright (C) 2007-2009 PetaLogix
 */

#समावेश <linux/export.h>
#समावेश <linux/moduleloader.h>
#समावेश <linux/kernel.h>
#समावेश <linux/elf.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/fs.h>
#समावेश <linux/माला.स>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/cacheflush.h>

पूर्णांक apply_relocate_add(Elf32_Shdr *sechdrs, स्थिर अक्षर *strtab,
	अचिन्हित पूर्णांक symindex, अचिन्हित पूर्णांक rअन्यथाc, काष्ठा module *module)
अणु

	अचिन्हित पूर्णांक i;
	Elf32_Rela *rela = (व्योम *)sechdrs[rअन्यथाc].sh_addr;
	Elf32_Sym *sym;
	अचिन्हित दीर्घ पूर्णांक *location;
	अचिन्हित दीर्घ पूर्णांक value;

	pr_debug("Applying add relocation section %u to %u\n",
		rअन्यथाc, sechdrs[rअन्यथाc].sh_info);

	क्रम (i = 0; i < sechdrs[rअन्यथाc].sh_size / माप(*rela); i++) अणु

		location = (व्योम *)sechdrs[sechdrs[rअन्यथाc].sh_info].sh_addr +
				rela[i].r_offset;
		sym = (Elf32_Sym *)sechdrs[symindex].sh_addr +
			ELF32_R_SYM(rela[i].r_info);
		value = sym->st_value + rela[i].r_addend;

		चयन (ELF32_R_TYPE(rela[i].r_info)) अणु

		/*
		 * Be careful! mb-gcc / mb-ld splits the relocs between the
		 * text and the reloc table. In general this means we must
		 * पढ़ो the current contents of (*location), add any offset
		 * then store the result back in
		 */

		हाल R_MICROBLAZE_32:
			*location = value;
			अवरोध;

		हाल R_MICROBLAZE_64:
			location[0] = (location[0] & 0xFFFF0000) |
					(value >> 16);
			location[1] = (location[1] & 0xFFFF0000) |
					(value & 0xFFFF);
			अवरोध;

		हाल R_MICROBLAZE_64_PCREL:
			value -= (अचिन्हित दीर्घ पूर्णांक)(location) + 4;
			location[0] = (location[0] & 0xFFFF0000) |
					(value >> 16);
			location[1] = (location[1] & 0xFFFF0000) |
					(value & 0xFFFF);
			pr_debug("R_MICROBLAZE_64_PCREL (%08lx)\n",
				value);
			अवरोध;

		हाल R_MICROBLAZE_32_PCREL_LO:
			pr_debug("R_MICROBLAZE_32_PCREL_LO\n");
			अवरोध;

		हाल R_MICROBLAZE_64_NONE:
			pr_debug("R_MICROBLAZE_64_NONE\n");
			अवरोध;

		हाल R_MICROBLAZE_NONE:
			pr_debug("R_MICROBLAZE_NONE\n");
			अवरोध;

		शेष:
			pr_err("module %s: Unknown relocation: %u\n",
				module->name,
				ELF32_R_TYPE(rela[i].r_info));
			वापस -ENOEXEC;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक module_finalize(स्थिर Elf32_Ehdr *hdr, स्थिर Elf_Shdr *sechdrs,
		काष्ठा module *module)
अणु
	flush_dcache();
	वापस 0;
पूर्ण
