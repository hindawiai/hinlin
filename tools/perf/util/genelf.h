<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __GENELF_H__
#घोषणा __GENELF_H__

/* genelf.c */
पूर्णांक jit_ग_लिखो_elf(पूर्णांक fd, uपूर्णांक64_t code_addr, स्थिर अक्षर *sym,
		  स्थिर व्योम *code, पूर्णांक csize, व्योम *debug, पूर्णांक nr_debug_entries,
		  व्योम *unwinding, uपूर्णांक64_t unwinding_header_size, uपूर्णांक64_t unwinding_size);
#अगर_घोषित HAVE_DWARF_SUPPORT
/* genelf_debug.c */
पूर्णांक jit_add_debug_info(Elf *e, uपूर्णांक64_t code_addr, व्योम *debug, पूर्णांक nr_debug_entries);
#पूर्ण_अगर

#अगर   defined(__arm__)
#घोषणा GEN_ELF_ARCH	EM_ARM
#घोषणा GEN_ELF_CLASS	ELFCLASS32
#या_अगर defined(__aarch64__)
#घोषणा GEN_ELF_ARCH	EM_AARCH64
#घोषणा GEN_ELF_CLASS	ELFCLASS64
#या_अगर defined(__x86_64__)
#घोषणा GEN_ELF_ARCH	EM_X86_64
#घोषणा GEN_ELF_CLASS	ELFCLASS64
#या_अगर defined(__i386__)
#घोषणा GEN_ELF_ARCH	EM_386
#घोषणा GEN_ELF_CLASS	ELFCLASS32
#या_अगर defined(__घातerpc64__)
#घोषणा GEN_ELF_ARCH	EM_PPC64
#घोषणा GEN_ELF_CLASS	ELFCLASS64
#या_अगर defined(__घातerpc__)
#घोषणा GEN_ELF_ARCH	EM_PPC
#घोषणा GEN_ELF_CLASS	ELFCLASS32
#या_अगर defined(__sparc__) && defined(__arch64__)
#घोषणा GEN_ELF_ARCH	EM_SPARCV9
#घोषणा GEN_ELF_CLASS	ELFCLASS64
#या_अगर defined(__sparc__)
#घोषणा GEN_ELF_ARCH	EM_SPARC
#घोषणा GEN_ELF_CLASS	ELFCLASS32
#या_अगर defined(__s390x__)
#घोषणा GEN_ELF_ARCH	EM_S390
#घोषणा GEN_ELF_CLASS	ELFCLASS64
#अन्यथा
#त्रुटि "unsupported architecture"
#पूर्ण_अगर

#अगर __BYTE_ORDER == __BIG_ENDIAN
#घोषणा GEN_ELF_ENDIAN	ELFDATA2MSB
#अन्यथा
#घोषणा GEN_ELF_ENDIAN	ELFDATA2LSB
#पूर्ण_अगर

#अगर GEN_ELF_CLASS == ELFCLASS64
#घोषणा elf_newehdr	elf64_newehdr
#घोषणा elf_माला_लोhdr	elf64_माला_लोhdr
#घोषणा Elf_Ehdr	Elf64_Ehdr
#घोषणा Elf_Shdr	Elf64_Shdr
#घोषणा Elf_Sym		Elf64_Sym
#घोषणा ELF_ST_TYPE(a)	ELF64_ST_TYPE(a)
#घोषणा ELF_ST_BIND(a)	ELF64_ST_BIND(a)
#घोषणा ELF_ST_VIS(a)	ELF64_ST_VISIBILITY(a)
#अन्यथा
#घोषणा elf_newehdr	elf32_newehdr
#घोषणा elf_माला_लोhdr	elf32_माला_लोhdr
#घोषणा Elf_Ehdr	Elf32_Ehdr
#घोषणा Elf_Shdr	Elf32_Shdr
#घोषणा Elf_Sym		Elf32_Sym
#घोषणा ELF_ST_TYPE(a)	ELF32_ST_TYPE(a)
#घोषणा ELF_ST_BIND(a)	ELF32_ST_BIND(a)
#घोषणा ELF_ST_VIS(a)	ELF32_ST_VISIBILITY(a)
#पूर्ण_अगर

/* The .text section is directly after the ELF header */
#घोषणा GEN_ELF_TEXT_OFFSET माप(Elf_Ehdr)

#पूर्ण_अगर
