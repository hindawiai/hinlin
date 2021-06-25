<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _PPC_BOOT_ELF_H_
#घोषणा _PPC_BOOT_ELF_H_

/* 32-bit ELF base types. */
प्रकार अचिन्हित पूर्णांक Elf32_Addr;
प्रकार अचिन्हित लघु Elf32_Half;
प्रकार अचिन्हित पूर्णांक Elf32_Off;
प्रकार चिन्हित पूर्णांक Elf32_Sword;
प्रकार अचिन्हित पूर्णांक Elf32_Word;

/* 64-bit ELF base types. */
प्रकार अचिन्हित दीर्घ दीर्घ Elf64_Addr;
प्रकार अचिन्हित लघु Elf64_Half;
प्रकार चिन्हित लघु Elf64_SHalf;
प्रकार अचिन्हित दीर्घ दीर्घ Elf64_Off;
प्रकार चिन्हित पूर्णांक Elf64_Sword;
प्रकार अचिन्हित पूर्णांक Elf64_Word;
प्रकार अचिन्हित दीर्घ दीर्घ Elf64_Xword;
प्रकार चिन्हित दीर्घ दीर्घ Elf64_Sxword;

/* These स्थिरants are क्रम the segment types stored in the image headers */
#घोषणा PT_शून्य    0
#घोषणा PT_LOAD    1
#घोषणा PT_DYNAMIC 2
#घोषणा PT_INTERP  3
#घोषणा PT_NOTE    4
#घोषणा PT_SHLIB   5
#घोषणा PT_PHDR    6
#घोषणा PT_TLS     7		/* Thपढ़ो local storage segment */
#घोषणा PT_LOOS    0x60000000	/* OS-specअगरic */
#घोषणा PT_HIOS    0x6fffffff	/* OS-specअगरic */
#घोषणा PT_LOPROC  0x70000000
#घोषणा PT_HIPROC  0x7fffffff
#घोषणा PT_GNU_EH_FRAME		0x6474e550

#घोषणा PT_GNU_STACK	(PT_LOOS + 0x474e551)

/* These स्थिरants define the dअगरferent elf file types */
#घोषणा ET_NONE   0
#घोषणा ET_REL    1
#घोषणा ET_EXEC   2
#घोषणा ET_DYN    3
#घोषणा ET_CORE   4
#घोषणा ET_LOPROC 0xff00
#घोषणा ET_HIPROC 0xffff

/* These स्थिरants define the various ELF target machines */
#घोषणा EM_NONE  0
#घोषणा EM_PPC	       20	/* PowerPC */
#घोषणा EM_PPC64       21	/* PowerPC64 */

#घोषणा EI_NIDENT	16

प्रकार काष्ठा elf32_hdr अणु
	अचिन्हित अक्षर e_ident[EI_NIDENT];
	Elf32_Half e_type;
	Elf32_Half e_machine;
	Elf32_Word e_version;
	Elf32_Addr e_entry;	/* Entry poपूर्णांक */
	Elf32_Off e_phoff;
	Elf32_Off e_shoff;
	Elf32_Word e_flags;
	Elf32_Half e_ehsize;
	Elf32_Half e_phentsize;
	Elf32_Half e_phnum;
	Elf32_Half e_shentsize;
	Elf32_Half e_shnum;
	Elf32_Half e_shstrndx;
पूर्ण Elf32_Ehdr;

प्रकार काष्ठा elf64_hdr अणु
	अचिन्हित अक्षर e_ident[16];	/* ELF "magic number" */
	Elf64_Half e_type;
	Elf64_Half e_machine;
	Elf64_Word e_version;
	Elf64_Addr e_entry;	/* Entry poपूर्णांक भव address */
	Elf64_Off e_phoff;	/* Program header table file offset */
	Elf64_Off e_shoff;	/* Section header table file offset */
	Elf64_Word e_flags;
	Elf64_Half e_ehsize;
	Elf64_Half e_phentsize;
	Elf64_Half e_phnum;
	Elf64_Half e_shentsize;
	Elf64_Half e_shnum;
	Elf64_Half e_shstrndx;
पूर्ण Elf64_Ehdr;

/* These स्थिरants define the permissions on sections in the program
   header, p_flags. */
#घोषणा PF_R		0x4
#घोषणा PF_W		0x2
#घोषणा PF_X		0x1

प्रकार काष्ठा elf32_phdr अणु
	Elf32_Word p_type;
	Elf32_Off p_offset;
	Elf32_Addr p_vaddr;
	Elf32_Addr p_paddr;
	Elf32_Word p_filesz;
	Elf32_Word p_memsz;
	Elf32_Word p_flags;
	Elf32_Word p_align;
पूर्ण Elf32_Phdr;

प्रकार काष्ठा elf64_phdr अणु
	Elf64_Word p_type;
	Elf64_Word p_flags;
	Elf64_Off p_offset;	/* Segment file offset */
	Elf64_Addr p_vaddr;	/* Segment भव address */
	Elf64_Addr p_paddr;	/* Segment physical address */
	Elf64_Xword p_filesz;	/* Segment size in file */
	Elf64_Xword p_memsz;	/* Segment size in memory */
	Elf64_Xword p_align;	/* Segment alignment, file & memory */
पूर्ण Elf64_Phdr;

#घोषणा	EI_MAG0		0	/* e_ident[] indexes */
#घोषणा	EI_MAG1		1
#घोषणा	EI_MAG2		2
#घोषणा	EI_MAG3		3
#घोषणा	EI_CLASS	4
#घोषणा	EI_DATA		5
#घोषणा	EI_VERSION	6
#घोषणा	EI_OSABI	7
#घोषणा	EI_PAD		8

#घोषणा	ELFMAG0		0x7f	/* EI_MAG */
#घोषणा	ELFMAG1		'E'
#घोषणा	ELFMAG2		'L'
#घोषणा	ELFMAG3		'F'
#घोषणा	ELFMAG		"\177ELF"
#घोषणा	SELFMAG		4

#घोषणा	ELFCLASSNONE	0	/* EI_CLASS */
#घोषणा	ELFCLASS32	1
#घोषणा	ELFCLASS64	2
#घोषणा	ELFCLASSNUM	3

#घोषणा ELFDATANONE	0	/* e_ident[EI_DATA] */
#घोषणा ELFDATA2LSB	1
#घोषणा ELFDATA2MSB	2

#घोषणा EV_NONE		0	/* e_version, EI_VERSION */
#घोषणा EV_CURRENT	1
#घोषणा EV_NUM		2

#घोषणा ELFOSABI_NONE	0
#घोषणा ELFOSABI_LINUX	3

काष्ठा elf_info अणु
	अचिन्हित दीर्घ loadsize;
	अचिन्हित दीर्घ memsize;
	अचिन्हित दीर्घ elfoffset;
पूर्ण;
पूर्णांक parse_elf64(व्योम *hdr, काष्ठा elf_info *info);
पूर्णांक parse_elf32(व्योम *hdr, काष्ठा elf_info *info);

#पूर्ण_अगर				/* _PPC_BOOT_ELF_H_ */
