<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/elf.h>
#समावेश <linux/coredump.h>
#समावेश <linux/fs.h>
#समावेश <linux/mm.h>

#समावेश <यंत्र/elf.h>


Elf32_Half elf_core_extra_phdrs(व्योम)
अणु
	वापस vsyscall_ehdr ? (((काष्ठा elfhdr *)vsyscall_ehdr)->e_phnum) : 0;
पूर्ण

पूर्णांक elf_core_ग_लिखो_extra_phdrs(काष्ठा coredump_params *cprm, loff_t offset)
अणु
	अगर ( vsyscall_ehdr ) अणु
		स्थिर काष्ठा elfhdr *स्थिर ehdrp =
			(काष्ठा elfhdr *) vsyscall_ehdr;
		स्थिर काष्ठा elf_phdr *स्थिर phdrp =
			(स्थिर काष्ठा elf_phdr *) (vsyscall_ehdr + ehdrp->e_phoff);
		पूर्णांक i;
		Elf32_Off ofs = 0;

		क्रम (i = 0; i < ehdrp->e_phnum; ++i) अणु
			काष्ठा elf_phdr phdr = phdrp[i];

			अगर (phdr.p_type == PT_LOAD) अणु
				ofs = phdr.p_offset = offset;
				offset += phdr.p_filesz;
			पूर्ण अन्यथा अणु
				phdr.p_offset += ofs;
			पूर्ण
			phdr.p_paddr = 0; /* match other core phdrs */
			अगर (!dump_emit(cprm, &phdr, माप(phdr)))
				वापस 0;
		पूर्ण
	पूर्ण
	वापस 1;
पूर्ण

पूर्णांक elf_core_ग_लिखो_extra_data(काष्ठा coredump_params *cprm)
अणु
	अगर ( vsyscall_ehdr ) अणु
		स्थिर काष्ठा elfhdr *स्थिर ehdrp =
			(काष्ठा elfhdr *) vsyscall_ehdr;
		स्थिर काष्ठा elf_phdr *स्थिर phdrp =
			(स्थिर काष्ठा elf_phdr *) (vsyscall_ehdr + ehdrp->e_phoff);
		पूर्णांक i;

		क्रम (i = 0; i < ehdrp->e_phnum; ++i) अणु
			अगर (phdrp[i].p_type == PT_LOAD) अणु
				व्योम *addr = (व्योम *) phdrp[i].p_vaddr;
				माप_प्रकार filesz = phdrp[i].p_filesz;
				अगर (!dump_emit(cprm, addr, filesz))
					वापस 0;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 1;
पूर्ण

माप_प्रकार elf_core_extra_data_size(व्योम)
अणु
	अगर ( vsyscall_ehdr ) अणु
		स्थिर काष्ठा elfhdr *स्थिर ehdrp =
			(काष्ठा elfhdr *)vsyscall_ehdr;
		स्थिर काष्ठा elf_phdr *स्थिर phdrp =
			(स्थिर काष्ठा elf_phdr *) (vsyscall_ehdr + ehdrp->e_phoff);
		पूर्णांक i;

		क्रम (i = 0; i < ehdrp->e_phnum; ++i)
			अगर (phdrp[i].p_type == PT_LOAD)
				वापस (माप_प्रकार) phdrp[i].p_filesz;
	पूर्ण
	वापस 0;
पूर्ण
