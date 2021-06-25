<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2018 Hangzhou C-SKY Microप्रणालीs co.,ltd.

#समावेश <linux/moduleloader.h>
#समावेश <linux/elf.h>
#समावेश <linux/mm.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/slab.h>
#समावेश <linux/fs.h>
#समावेश <linux/माला.स>
#समावेश <linux/kernel.h>
#समावेश <linux/spinlock.h>

#अगर_घोषित CONFIG_CPU_CK810
#घोषणा IS_BSR32(hi16, lo16)		(((hi16) & 0xFC00) == 0xE000)
#घोषणा IS_JSRI32(hi16, lo16)		((hi16) == 0xEAE0)

#घोषणा CHANGE_JSRI_TO_LRW(addr) करो अणु					\
	*(uपूर्णांक16_t *)(addr) = (*(uपूर्णांक16_t *)(addr) & 0xFF9F) | 0x001a;	\
	*((uपूर्णांक16_t *)(addr) + 1) = *((uपूर्णांक16_t *)(addr) + 1) & 0xFFFF;	\
पूर्ण जबतक (0)

#घोषणा SET_JSR32_R26(addr) करो अणु		\
	*(uपूर्णांक16_t *)(addr) = 0xE8Fa;		\
	*((uपूर्णांक16_t *)(addr) + 1) = 0x0000;	\
पूर्ण जबतक (0)

अटल व्योम jsri_2_lrw_jsr(uपूर्णांक32_t *location)
अणु
	uपूर्णांक16_t *location_पंचांगp = (uपूर्णांक16_t *)location;

	अगर (IS_BSR32(*location_पंचांगp, *(location_पंचांगp + 1)))
		वापस;

	अगर (IS_JSRI32(*location_पंचांगp, *(location_पंचांगp + 1))) अणु
		/* jsri 0x...  --> lrw r26, 0x... */
		CHANGE_JSRI_TO_LRW(location);
		/* lsli r0, r0 --> jsr r26 */
		SET_JSR32_R26(location + 1);
	पूर्ण
पूर्ण
#अन्यथा
अटल व्योम अंतरभूत jsri_2_lrw_jsr(uपूर्णांक32_t *location)
अणु
	वापस;
पूर्ण
#पूर्ण_अगर

पूर्णांक apply_relocate_add(Elf32_Shdr *sechdrs, स्थिर अक्षर *strtab,
		अचिन्हित पूर्णांक symindex, अचिन्हित पूर्णांक rअन्यथाc, काष्ठा module *me)
अणु
	अचिन्हित पूर्णांक i;
	Elf32_Rela	*rel = (व्योम *) sechdrs[rअन्यथाc].sh_addr;
	Elf32_Sym	*sym;
	uपूर्णांक32_t	*location;
	लघु		*temp;

	क्रम (i = 0; i < sechdrs[rअन्यथाc].sh_size / माप(*rel); i++) अणु
		/* This is where to make the change */
		location = (व्योम *)sechdrs[sechdrs[rअन्यथाc].sh_info].sh_addr
							+ rel[i].r_offset;
		sym = (Elf32_Sym *)sechdrs[symindex].sh_addr
						+ ELF32_R_SYM(rel[i].r_info);

		चयन (ELF32_R_TYPE(rel[i].r_info)) अणु
		हाल R_CSKY_32:
			/* We add the value पूर्णांकo the location given */
			*location = rel[i].r_addend + sym->st_value;
			अवरोध;
		हाल R_CSKY_PC32:
			/* Add the value, subtract its postition */
			*location = rel[i].r_addend + sym->st_value
							- (uपूर्णांक32_t)location;
			अवरोध;
		हाल R_CSKY_PCRELJSR_IMM11BY2:
			अवरोध;
		हाल R_CSKY_PCRELJSR_IMM26BY2:
			jsri_2_lrw_jsr(location);
			अवरोध;
		हाल R_CSKY_ADDR_HI16:
			temp = ((लघु  *)location) + 1;
			*temp = (लघु)
				((rel[i].r_addend + sym->st_value) >> 16);
			अवरोध;
		हाल R_CSKY_ADDR_LO16:
			temp = ((लघु  *)location) + 1;
			*temp = (लघु)
				((rel[i].r_addend + sym->st_value) & 0xffff);
			अवरोध;
		शेष:
			pr_err("module %s: Unknown relocation: %u\n",
				me->name, ELF32_R_TYPE(rel[i].r_info));
			वापस -ENOEXEC;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण
