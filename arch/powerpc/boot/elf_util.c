<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) Paul Mackerras 1997.
 *
 * Updates क्रम PPC64 by Todd Inglett, Dave Engebretsen & Peter Bergner.
 */
#समावेश <मानकतर्क.स>
#समावेश <मानकघोष.स>
#समावेश "elf.h"
#समावेश "page.h"
#समावेश "string.h"
#समावेश "stdio.h"

पूर्णांक parse_elf64(व्योम *hdr, काष्ठा elf_info *info)
अणु
	Elf64_Ehdr *elf64 = hdr;
	Elf64_Phdr *elf64ph;
	अचिन्हित पूर्णांक i;

	अगर (!(elf64->e_ident[EI_MAG0]  == ELFMAG0	&&
	      elf64->e_ident[EI_MAG1]  == ELFMAG1	&&
	      elf64->e_ident[EI_MAG2]  == ELFMAG2	&&
	      elf64->e_ident[EI_MAG3]  == ELFMAG3	&&
	      elf64->e_ident[EI_CLASS] == ELFCLASS64	&&
#अगर_घोषित __LITTLE_ENDIAN__
	      elf64->e_ident[EI_DATA]  == ELFDATA2LSB	&&
#अन्यथा
	      elf64->e_ident[EI_DATA]  == ELFDATA2MSB	&&
#पूर्ण_अगर
	      (elf64->e_type            == ET_EXEC ||
	       elf64->e_type            == ET_DYN)	&&
	      elf64->e_machine         == EM_PPC64))
		वापस 0;

	elf64ph = (Elf64_Phdr *)((अचिन्हित दीर्घ)elf64 +
				 (अचिन्हित दीर्घ)elf64->e_phoff);
	क्रम (i = 0; i < (अचिन्हित पूर्णांक)elf64->e_phnum; i++, elf64ph++)
		अगर (elf64ph->p_type == PT_LOAD)
			अवरोध;
	अगर (i >= (अचिन्हित पूर्णांक)elf64->e_phnum)
		वापस 0;

	info->loadsize = (अचिन्हित दीर्घ)elf64ph->p_filesz;
	info->memsize = (अचिन्हित दीर्घ)elf64ph->p_memsz;
	info->elfoffset = (अचिन्हित दीर्घ)elf64ph->p_offset;

	वापस 1;
पूर्ण

पूर्णांक parse_elf32(व्योम *hdr, काष्ठा elf_info *info)
अणु
	Elf32_Ehdr *elf32 = hdr;
	Elf32_Phdr *elf32ph;
	अचिन्हित पूर्णांक i;

	अगर (!(elf32->e_ident[EI_MAG0]  == ELFMAG0	&&
	      elf32->e_ident[EI_MAG1]  == ELFMAG1	&&
	      elf32->e_ident[EI_MAG2]  == ELFMAG2	&&
	      elf32->e_ident[EI_MAG3]  == ELFMAG3	&&
	      elf32->e_ident[EI_CLASS] == ELFCLASS32	&&
	      elf32->e_ident[EI_DATA]  == ELFDATA2MSB	&&
	      (elf32->e_type            == ET_EXEC ||
	       elf32->e_type            == ET_DYN)      &&
	      elf32->e_machine         == EM_PPC))
		वापस 0;

	elf32ph = (Elf32_Phdr *) ((अचिन्हित दीर्घ)elf32 + elf32->e_phoff);
	क्रम (i = 0; i < elf32->e_phnum; i++, elf32ph++)
		अगर (elf32ph->p_type == PT_LOAD)
			अवरोध;
	अगर (i >= elf32->e_phnum)
		वापस 0;

	info->loadsize = elf32ph->p_filesz;
	info->memsize = elf32ph->p_memsz;
	info->elfoffset = elf32ph->p_offset;
	वापस 1;
पूर्ण
