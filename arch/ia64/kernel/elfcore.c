<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/elf.h>
#समावेश <linux/coredump.h>
#समावेश <linux/fs.h>
#समावेश <linux/mm.h>

#समावेश <यंत्र/elf.h>


Elf64_Half elf_core_extra_phdrs(व्योम)
अणु
	वापस GATE_EHDR->e_phnum;
पूर्ण

पूर्णांक elf_core_ग_लिखो_extra_phdrs(काष्ठा coredump_params *cprm, loff_t offset)
अणु
	स्थिर काष्ठा elf_phdr *स्थिर gate_phdrs =
		(स्थिर काष्ठा elf_phdr *) (GATE_ADDR + GATE_EHDR->e_phoff);
	पूर्णांक i;
	Elf64_Off ofs = 0;

	क्रम (i = 0; i < GATE_EHDR->e_phnum; ++i) अणु
		काष्ठा elf_phdr phdr = gate_phdrs[i];

		अगर (phdr.p_type == PT_LOAD) अणु
			phdr.p_memsz = PAGE_ALIGN(phdr.p_memsz);
			phdr.p_filesz = phdr.p_memsz;
			अगर (ofs == 0) अणु
				ofs = phdr.p_offset = offset;
				offset += phdr.p_filesz;
			पूर्ण अन्यथा अणु
				phdr.p_offset = ofs;
			पूर्ण
		पूर्ण अन्यथा अणु
			phdr.p_offset += ofs;
		पूर्ण
		phdr.p_paddr = 0; /* match other core phdrs */
		अगर (!dump_emit(cprm, &phdr, माप(phdr)))
			वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

पूर्णांक elf_core_ग_लिखो_extra_data(काष्ठा coredump_params *cprm)
अणु
	स्थिर काष्ठा elf_phdr *स्थिर gate_phdrs =
		(स्थिर काष्ठा elf_phdr *) (GATE_ADDR + GATE_EHDR->e_phoff);
	पूर्णांक i;

	क्रम (i = 0; i < GATE_EHDR->e_phnum; ++i) अणु
		अगर (gate_phdrs[i].p_type == PT_LOAD) अणु
			व्योम *addr = (व्योम *)gate_phdrs[i].p_vaddr;
			माप_प्रकार memsz = PAGE_ALIGN(gate_phdrs[i].p_memsz);

			अगर (!dump_emit(cprm, addr, memsz))
				वापस 0;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस 1;
पूर्ण

माप_प्रकार elf_core_extra_data_size(व्योम)
अणु
	स्थिर काष्ठा elf_phdr *स्थिर gate_phdrs =
		(स्थिर काष्ठा elf_phdr *) (GATE_ADDR + GATE_EHDR->e_phoff);
	पूर्णांक i;
	माप_प्रकार size = 0;

	क्रम (i = 0; i < GATE_EHDR->e_phnum; ++i) अणु
		अगर (gate_phdrs[i].p_type == PT_LOAD) अणु
			size += PAGE_ALIGN(gate_phdrs[i].p_memsz);
			अवरोध;
		पूर्ण
	पूर्ण
	वापस size;
पूर्ण
