<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright 2011 Red Hat, Inc.
 * All rights reserved.
 *
 * Author(s): Peter Jones <pjones@redhat.com>
 */
#अगर_अघोषित __LINUX_PE_H
#घोषणा __LINUX_PE_H

#समावेश <linux/types.h>

/*
 * Linux EFI stub v1.0 adds the following functionality:
 * - Loading initrd from the LINUX_EFI_INITRD_MEDIA_GUID device path,
 * - Loading/starting the kernel from firmware that tarमाला_लो a dअगरferent
 *   machine type, via the entrypoपूर्णांक exposed in the .compat PE/COFF section.
 *
 * The recommended way of loading and starting v1.0 or later kernels is to use
 * the LoadImage() and StartImage() EFI boot services, and expose the initrd
 * via the LINUX_EFI_INITRD_MEDIA_GUID device path.
 *
 * Versions older than v1.0 support initrd loading via the image load options
 * (using initrd=, limited to the volume from which the kernel itself was
 * loaded), or via arch specअगरic means (bootparams, DT, etc).
 *
 * On x86, LoadImage() and StartImage() can be omitted अगर the EFI hanकरोver
 * protocol is implemented, which can be inferred from the version,
 * hanकरोver_offset and xloadflags fields in the bootparams काष्ठाure.
 */
#घोषणा LINUX_EFISTUB_MAJOR_VERSION		0x1
#घोषणा LINUX_EFISTUB_MINOR_VERSION		0x0

#घोषणा MZ_MAGIC	0x5a4d	/* "MZ" */

#घोषणा PE_MAGIC		0x00004550	/* "PE\0\0" */
#घोषणा PE_OPT_MAGIC_PE32	0x010b
#घोषणा PE_OPT_MAGIC_PE32_ROM	0x0107
#घोषणा PE_OPT_MAGIC_PE32PLUS	0x020b

/* machine type */
#घोषणा	IMAGE_खाता_MACHINE_UNKNOWN	0x0000
#घोषणा	IMAGE_खाता_MACHINE_AM33		0x01d3
#घोषणा	IMAGE_खाता_MACHINE_AMD64	0x8664
#घोषणा	IMAGE_खाता_MACHINE_ARM		0x01c0
#घोषणा	IMAGE_खाता_MACHINE_ARMV7	0x01c4
#घोषणा	IMAGE_खाता_MACHINE_ARM64	0xaa64
#घोषणा	IMAGE_खाता_MACHINE_EBC		0x0ebc
#घोषणा	IMAGE_खाता_MACHINE_I386		0x014c
#घोषणा	IMAGE_खाता_MACHINE_IA64		0x0200
#घोषणा	IMAGE_खाता_MACHINE_M32R		0x9041
#घोषणा	IMAGE_खाता_MACHINE_MIPS16	0x0266
#घोषणा	IMAGE_खाता_MACHINE_MIPSFPU	0x0366
#घोषणा	IMAGE_खाता_MACHINE_MIPSFPU16	0x0466
#घोषणा	IMAGE_खाता_MACHINE_POWERPC	0x01f0
#घोषणा	IMAGE_खाता_MACHINE_POWERPCFP	0x01f1
#घोषणा	IMAGE_खाता_MACHINE_R4000	0x0166
#घोषणा	IMAGE_खाता_MACHINE_RISCV32	0x5032
#घोषणा	IMAGE_खाता_MACHINE_RISCV64	0x5064
#घोषणा	IMAGE_खाता_MACHINE_RISCV128	0x5128
#घोषणा	IMAGE_खाता_MACHINE_SH3		0x01a2
#घोषणा	IMAGE_खाता_MACHINE_SH3DSP	0x01a3
#घोषणा	IMAGE_खाता_MACHINE_SH3E		0x01a4
#घोषणा	IMAGE_खाता_MACHINE_SH4		0x01a6
#घोषणा	IMAGE_खाता_MACHINE_SH5		0x01a8
#घोषणा	IMAGE_खाता_MACHINE_THUMB	0x01c2
#घोषणा	IMAGE_खाता_MACHINE_WCEMIPSV2	0x0169

/* flags */
#घोषणा IMAGE_खाता_RELOCS_STRIPPED           0x0001
#घोषणा IMAGE_खाता_EXECUTABLE_IMAGE          0x0002
#घोषणा IMAGE_खाता_LINE_NUMS_STRIPPED        0x0004
#घोषणा IMAGE_खाता_LOCAL_SYMS_STRIPPED       0x0008
#घोषणा IMAGE_खाता_AGGRESSIVE_WS_TRIM        0x0010
#घोषणा IMAGE_खाता_LARGE_ADDRESS_AWARE       0x0020
#घोषणा IMAGE_खाता_16BIT_MACHINE             0x0040
#घोषणा IMAGE_खाता_BYTES_REVERSED_LO         0x0080
#घोषणा IMAGE_खाता_32BIT_MACHINE             0x0100
#घोषणा IMAGE_खाता_DEBUG_STRIPPED            0x0200
#घोषणा IMAGE_खाता_REMOVABLE_RUN_FROM_SWAP   0x0400
#घोषणा IMAGE_खाता_NET_RUN_FROM_SWAP         0x0800
#घोषणा IMAGE_खाता_SYSTEM                    0x1000
#घोषणा IMAGE_खाता_DLL                       0x2000
#घोषणा IMAGE_खाता_UP_SYSTEM_ONLY            0x4000
#घोषणा IMAGE_खाता_BYTES_REVERSED_HI         0x8000

#घोषणा IMAGE_खाता_OPT_ROM_MAGIC	0x107
#घोषणा IMAGE_खाता_OPT_PE32_MAGIC	0x10b
#घोषणा IMAGE_खाता_OPT_PE32_PLUS_MAGIC	0x20b

#घोषणा IMAGE_SUBSYSTEM_UNKNOWN			 0
#घोषणा IMAGE_SUBSYSTEM_NATIVE			 1
#घोषणा IMAGE_SUBSYSTEM_WINDOWS_GUI		 2
#घोषणा IMAGE_SUBSYSTEM_WINDOWS_CUI		 3
#घोषणा IMAGE_SUBSYSTEM_POSIX_CUI		 7
#घोषणा IMAGE_SUBSYSTEM_WINDOWS_CE_GUI		 9
#घोषणा IMAGE_SUBSYSTEM_EFI_APPLICATION		10
#घोषणा IMAGE_SUBSYSTEM_EFI_BOOT_SERVICE_DRIVER	11
#घोषणा IMAGE_SUBSYSTEM_EFI_RUNTIME_DRIVER	12
#घोषणा IMAGE_SUBSYSTEM_EFI_ROM_IMAGE		13
#घोषणा IMAGE_SUBSYSTEM_XBOX			14

#घोषणा IMAGE_DLL_CHARACTERISTICS_DYNAMIC_BASE          0x0040
#घोषणा IMAGE_DLL_CHARACTERISTICS_FORCE_INTEGRITY       0x0080
#घोषणा IMAGE_DLL_CHARACTERISTICS_NX_COMPAT             0x0100
#घोषणा IMAGE_DLLCHARACTERISTICS_NO_ISOLATION           0x0200
#घोषणा IMAGE_DLLCHARACTERISTICS_NO_SEH                 0x0400
#घोषणा IMAGE_DLLCHARACTERISTICS_NO_BIND                0x0800
#घोषणा IMAGE_DLLCHARACTERISTICS_WDM_DRIVER             0x2000
#घोषणा IMAGE_DLLCHARACTERISTICS_TERMINAL_SERVER_AWARE  0x8000

/* they actually defined 0x00000000 as well, but I think we'll skip that one. */
#घोषणा IMAGE_SCN_RESERVED_0	0x00000001
#घोषणा IMAGE_SCN_RESERVED_1	0x00000002
#घोषणा IMAGE_SCN_RESERVED_2	0x00000004
#घोषणा IMAGE_SCN_TYPE_NO_PAD	0x00000008 /* करोn't pad - obsolete */
#घोषणा IMAGE_SCN_RESERVED_3	0x00000010
#घोषणा IMAGE_SCN_CNT_CODE	0x00000020 /* .text */
#घोषणा IMAGE_SCN_CNT_INITIALIZED_DATA 0x00000040 /* .data */
#घोषणा IMAGE_SCN_CNT_UNINITIALIZED_DATA 0x00000080 /* .bss */
#घोषणा IMAGE_SCN_LNK_OTHER	0x00000100 /* reserved */
#घोषणा IMAGE_SCN_LNK_INFO	0x00000200 /* .drectve comments */
#घोषणा IMAGE_SCN_RESERVED_4	0x00000400
#घोषणा IMAGE_SCN_LNK_REMOVE	0x00000800 /* .o only - scn to be rm'd*/
#घोषणा IMAGE_SCN_LNK_COMDAT	0x00001000 /* .o only - COMDAT data */
#घोषणा IMAGE_SCN_RESERVED_5	0x00002000 /* spec omits this */
#घोषणा IMAGE_SCN_RESERVED_6	0x00004000 /* spec omits this */
#घोषणा IMAGE_SCN_GPREL		0x00008000 /* global poपूर्णांकer referenced data */
/* spec lists 0x20000 twice, I suspect they meant 0x10000 क्रम one of them */
#घोषणा IMAGE_SCN_MEM_PURGEABLE	0x00010000 /* reserved क्रम "future" use */
#घोषणा IMAGE_SCN_16BIT		0x00020000 /* reserved क्रम "future" use */
#घोषणा IMAGE_SCN_LOCKED	0x00040000 /* reserved क्रम "future" use */
#घोषणा IMAGE_SCN_PRELOAD	0x00080000 /* reserved क्रम "future" use */
/* and here they just stuck a 1-byte पूर्णांकeger in the middle of a bitfield */
#घोषणा IMAGE_SCN_ALIGN_1BYTES	0x00100000 /* it करोes what it says on the box */
#घोषणा IMAGE_SCN_ALIGN_2BYTES	0x00200000
#घोषणा IMAGE_SCN_ALIGN_4BYTES	0x00300000
#घोषणा IMAGE_SCN_ALIGN_8BYTES	0x00400000
#घोषणा IMAGE_SCN_ALIGN_16BYTES	0x00500000
#घोषणा IMAGE_SCN_ALIGN_32BYTES	0x00600000
#घोषणा IMAGE_SCN_ALIGN_64BYTES	0x00700000
#घोषणा IMAGE_SCN_ALIGN_128BYTES 0x00800000
#घोषणा IMAGE_SCN_ALIGN_256BYTES 0x00900000
#घोषणा IMAGE_SCN_ALIGN_512BYTES 0x00a00000
#घोषणा IMAGE_SCN_ALIGN_1024BYTES 0x00b00000
#घोषणा IMAGE_SCN_ALIGN_2048BYTES 0x00c00000
#घोषणा IMAGE_SCN_ALIGN_4096BYTES 0x00d00000
#घोषणा IMAGE_SCN_ALIGN_8192BYTES 0x00e00000
#घोषणा IMAGE_SCN_LNK_NRELOC_OVFL 0x01000000 /* extended relocations */
#घोषणा IMAGE_SCN_MEM_DISCARDABLE 0x02000000 /* scn can be discarded */
#घोषणा IMAGE_SCN_MEM_NOT_CACHED 0x04000000 /* cannot be cached */
#घोषणा IMAGE_SCN_MEM_NOT_PAGED	0x08000000 /* not pageable */
#घोषणा IMAGE_SCN_MEM_SHARED	0x10000000 /* can be shared */
#घोषणा IMAGE_SCN_MEM_EXECUTE	0x20000000 /* can be executed as code */
#घोषणा IMAGE_SCN_MEM_READ	0x40000000 /* पढ़ोable */
#घोषणा IMAGE_SCN_MEM_WRITE	0x80000000 /* ग_लिखोable */

#घोषणा IMAGE_DEBUG_TYPE_CODEVIEW	2

#अगर_अघोषित __ASSEMBLY__

काष्ठा mz_hdr अणु
	uपूर्णांक16_t magic;		/* MZ_MAGIC */
	uपूर्णांक16_t lbsize;	/* size of last used block */
	uपूर्णांक16_t blocks;	/* pages in file, 0x3 */
	uपूर्णांक16_t relocs;	/* relocations */
	uपूर्णांक16_t hdrsize;	/* header size in "paragraphs" */
	uपूर्णांक16_t min_extra_pps;	/* .bss */
	uपूर्णांक16_t max_extra_pps;	/* runसमय limit क्रम the arena size */
	uपूर्णांक16_t ss;		/* relative stack segment */
	uपूर्णांक16_t sp;		/* initial %sp रेजिस्टर */
	uपूर्णांक16_t checksum;	/* word checksum */
	uपूर्णांक16_t ip;		/* initial %ip रेजिस्टर */
	uपूर्णांक16_t cs;		/* initial %cs relative to load segment */
	uपूर्णांक16_t reloc_table_offset;	/* offset of the first relocation */
	uपूर्णांक16_t overlay_num;	/* overlay number.  set to 0. */
	uपूर्णांक16_t reserved0[4];	/* reserved */
	uपूर्णांक16_t oem_id;	/* oem identअगरier */
	uपूर्णांक16_t oem_info;	/* oem specअगरic */
	uपूर्णांक16_t reserved1[10];	/* reserved */
	uपूर्णांक32_t peaddr;	/* address of pe header */
	अक्षर     message[];	/* message to prपूर्णांक */
पूर्ण;

काष्ठा mz_reloc अणु
	uपूर्णांक16_t offset;
	uपूर्णांक16_t segment;
पूर्ण;

काष्ठा pe_hdr अणु
	uपूर्णांक32_t magic;		/* PE magic */
	uपूर्णांक16_t machine;	/* machine type */
	uपूर्णांक16_t sections;	/* number of sections */
	uपूर्णांक32_t बारtamp;	/* समय_प्रकार */
	uपूर्णांक32_t symbol_table;	/* symbol table offset */
	uपूर्णांक32_t symbols;	/* number of symbols */
	uपूर्णांक16_t opt_hdr_size;	/* size of optional header */
	uपूर्णांक16_t flags;		/* flags */
पूर्ण;

/* the fact that pe32 isn't padded where pe32+ is 64-bit means union won't
 * work right.  vomit. */
काष्ठा pe32_opt_hdr अणु
	/* "standard" header */
	uपूर्णांक16_t magic;		/* file type */
	uपूर्णांक8_t  ld_major;	/* linker major version */
	uपूर्णांक8_t  ld_minor;	/* linker minor version */
	uपूर्णांक32_t text_size;	/* size of text section(s) */
	uपूर्णांक32_t data_size;	/* size of data section(s) */
	uपूर्णांक32_t bss_size;	/* size of bss section(s) */
	uपूर्णांक32_t entry_poपूर्णांक;	/* file offset of entry poपूर्णांक */
	uपूर्णांक32_t code_base;	/* relative code addr in ram */
	uपूर्णांक32_t data_base;	/* relative data addr in ram */
	/* "windows" header */
	uपूर्णांक32_t image_base;	/* preferred load address */
	uपूर्णांक32_t section_align;	/* alignment in bytes */
	uपूर्णांक32_t file_align;	/* file alignment in bytes */
	uपूर्णांक16_t os_major;	/* major OS version */
	uपूर्णांक16_t os_minor;	/* minor OS version */
	uपूर्णांक16_t image_major;	/* major image version */
	uपूर्णांक16_t image_minor;	/* minor image version */
	uपूर्णांक16_t subsys_major;	/* major subप्रणाली version */
	uपूर्णांक16_t subsys_minor;	/* minor subप्रणाली version */
	uपूर्णांक32_t win32_version;	/* reserved, must be 0 */
	uपूर्णांक32_t image_size;	/* image size */
	uपूर्णांक32_t header_size;	/* header size rounded up to
				   file_align */
	uपूर्णांक32_t csum;		/* checksum */
	uपूर्णांक16_t subsys;	/* subप्रणाली */
	uपूर्णांक16_t dll_flags;	/* more flags! */
	uपूर्णांक32_t stack_size_req;/* amt of stack requested */
	uपूर्णांक32_t stack_size;	/* amt of stack required */
	uपूर्णांक32_t heap_size_req;	/* amt of heap requested */
	uपूर्णांक32_t heap_size;	/* amt of heap required */
	uपूर्णांक32_t loader_flags;	/* reserved, must be 0 */
	uपूर्णांक32_t data_dirs;	/* number of data dir entries */
पूर्ण;

काष्ठा pe32plus_opt_hdr अणु
	uपूर्णांक16_t magic;		/* file type */
	uपूर्णांक8_t  ld_major;	/* linker major version */
	uपूर्णांक8_t  ld_minor;	/* linker minor version */
	uपूर्णांक32_t text_size;	/* size of text section(s) */
	uपूर्णांक32_t data_size;	/* size of data section(s) */
	uपूर्णांक32_t bss_size;	/* size of bss section(s) */
	uपूर्णांक32_t entry_poपूर्णांक;	/* file offset of entry poपूर्णांक */
	uपूर्णांक32_t code_base;	/* relative code addr in ram */
	/* "windows" header */
	uपूर्णांक64_t image_base;	/* preferred load address */
	uपूर्णांक32_t section_align;	/* alignment in bytes */
	uपूर्णांक32_t file_align;	/* file alignment in bytes */
	uपूर्णांक16_t os_major;	/* major OS version */
	uपूर्णांक16_t os_minor;	/* minor OS version */
	uपूर्णांक16_t image_major;	/* major image version */
	uपूर्णांक16_t image_minor;	/* minor image version */
	uपूर्णांक16_t subsys_major;	/* major subप्रणाली version */
	uपूर्णांक16_t subsys_minor;	/* minor subप्रणाली version */
	uपूर्णांक32_t win32_version;	/* reserved, must be 0 */
	uपूर्णांक32_t image_size;	/* image size */
	uपूर्णांक32_t header_size;	/* header size rounded up to
				   file_align */
	uपूर्णांक32_t csum;		/* checksum */
	uपूर्णांक16_t subsys;	/* subप्रणाली */
	uपूर्णांक16_t dll_flags;	/* more flags! */
	uपूर्णांक64_t stack_size_req;/* amt of stack requested */
	uपूर्णांक64_t stack_size;	/* amt of stack required */
	uपूर्णांक64_t heap_size_req;	/* amt of heap requested */
	uपूर्णांक64_t heap_size;	/* amt of heap required */
	uपूर्णांक32_t loader_flags;	/* reserved, must be 0 */
	uपूर्णांक32_t data_dirs;	/* number of data dir entries */
पूर्ण;

काष्ठा data_dirent अणु
	uपूर्णांक32_t भव_address;	/* relative to load address */
	uपूर्णांक32_t size;
पूर्ण;

काष्ठा data_directory अणु
	काष्ठा data_dirent exports;		/* .edata */
	काष्ठा data_dirent imports;		/* .idata */
	काष्ठा data_dirent resources;		/* .rsrc */
	काष्ठा data_dirent exceptions;		/* .pdata */
	काष्ठा data_dirent certs;		/* certs */
	काष्ठा data_dirent base_relocations;	/* .reloc */
	काष्ठा data_dirent debug;		/* .debug */
	काष्ठा data_dirent arch;		/* reservered */
	काष्ठा data_dirent global_ptr;		/* global poपूर्णांकer reg. Size=0 */
	काष्ठा data_dirent tls;			/* .tls */
	काष्ठा data_dirent load_config;		/* load configuration काष्ठाure */
	काष्ठा data_dirent bound_imports;	/* no idea */
	काष्ठा data_dirent import_addrs;	/* import address table */
	काष्ठा data_dirent delay_imports;	/* delay-load import table */
	काष्ठा data_dirent clr_runसमय_hdr;	/* .cor (object only) */
	काष्ठा data_dirent reserved;
पूर्ण;

काष्ठा section_header अणु
	अक्षर name[8];			/* name or "/12\0" string tbl offset */
	uपूर्णांक32_t भव_size;		/* size of loaded section in ram */
	uपूर्णांक32_t भव_address;	/* relative भव address */
	uपूर्णांक32_t raw_data_size;		/* size of the section */
	uपूर्णांक32_t data_addr;		/* file poपूर्णांकer to first page of sec */
	uपूर्णांक32_t relocs;		/* file poपूर्णांकer to relocation entries */
	uपूर्णांक32_t line_numbers;		/* line numbers! */
	uपूर्णांक16_t num_relocs;		/* number of relocations */
	uपूर्णांक16_t num_lin_numbers;	/* srsly. */
	uपूर्णांक32_t flags;
पूर्ण;

क्रमागत x64_coff_reloc_type अणु
	IMAGE_REL_AMD64_ABSOLUTE = 0,
	IMAGE_REL_AMD64_ADDR64,
	IMAGE_REL_AMD64_ADDR32,
	IMAGE_REL_AMD64_ADDR32N,
	IMAGE_REL_AMD64_REL32,
	IMAGE_REL_AMD64_REL32_1,
	IMAGE_REL_AMD64_REL32_2,
	IMAGE_REL_AMD64_REL32_3,
	IMAGE_REL_AMD64_REL32_4,
	IMAGE_REL_AMD64_REL32_5,
	IMAGE_REL_AMD64_SECTION,
	IMAGE_REL_AMD64_SECREL,
	IMAGE_REL_AMD64_SECREL7,
	IMAGE_REL_AMD64_TOKEN,
	IMAGE_REL_AMD64_SREL32,
	IMAGE_REL_AMD64_PAIR,
	IMAGE_REL_AMD64_SSPAN32,
पूर्ण;

क्रमागत arm_coff_reloc_type अणु
	IMAGE_REL_ARM_ABSOLUTE,
	IMAGE_REL_ARM_ADDR32,
	IMAGE_REL_ARM_ADDR32N,
	IMAGE_REL_ARM_BRANCH2,
	IMAGE_REL_ARM_BRANCH1,
	IMAGE_REL_ARM_SECTION,
	IMAGE_REL_ARM_SECREL,
पूर्ण;

क्रमागत sh_coff_reloc_type अणु
	IMAGE_REL_SH3_ABSOLUTE,
	IMAGE_REL_SH3_सूचीECT16,
	IMAGE_REL_SH3_सूचीECT32,
	IMAGE_REL_SH3_सूचीECT8,
	IMAGE_REL_SH3_सूचीECT8_WORD,
	IMAGE_REL_SH3_सूचीECT8_LONG,
	IMAGE_REL_SH3_सूचीECT4,
	IMAGE_REL_SH3_सूचीECT4_WORD,
	IMAGE_REL_SH3_सूचीECT4_LONG,
	IMAGE_REL_SH3_PCREL8_WORD,
	IMAGE_REL_SH3_PCREL8_LONG,
	IMAGE_REL_SH3_PCREL12_WORD,
	IMAGE_REL_SH3_STARTOF_SECTION,
	IMAGE_REL_SH3_SIZखातापूर्ण_SECTION,
	IMAGE_REL_SH3_SECTION,
	IMAGE_REL_SH3_SECREL,
	IMAGE_REL_SH3_सूचीECT32_NB,
	IMAGE_REL_SH3_GPREL4_LONG,
	IMAGE_REL_SH3_TOKEN,
	IMAGE_REL_SHM_PCRELPT,
	IMAGE_REL_SHM_REFLO,
	IMAGE_REL_SHM_REFHALF,
	IMAGE_REL_SHM_RELLO,
	IMAGE_REL_SHM_RELHALF,
	IMAGE_REL_SHM_PAIR,
	IMAGE_REL_SHM_NOMODE,
पूर्ण;

क्रमागत ppc_coff_reloc_type अणु
	IMAGE_REL_PPC_ABSOLUTE,
	IMAGE_REL_PPC_ADDR64,
	IMAGE_REL_PPC_ADDR32,
	IMAGE_REL_PPC_ADDR24,
	IMAGE_REL_PPC_ADDR16,
	IMAGE_REL_PPC_ADDR14,
	IMAGE_REL_PPC_REL24,
	IMAGE_REL_PPC_REL14,
	IMAGE_REL_PPC_ADDR32N,
	IMAGE_REL_PPC_SECREL,
	IMAGE_REL_PPC_SECTION,
	IMAGE_REL_PPC_SECREL16,
	IMAGE_REL_PPC_REFHI,
	IMAGE_REL_PPC_REFLO,
	IMAGE_REL_PPC_PAIR,
	IMAGE_REL_PPC_SECRELLO,
	IMAGE_REL_PPC_GPREL,
	IMAGE_REL_PPC_TOKEN,
पूर्ण;

क्रमागत x86_coff_reloc_type अणु
	IMAGE_REL_I386_ABSOLUTE,
	IMAGE_REL_I386_सूची16,
	IMAGE_REL_I386_REL16,
	IMAGE_REL_I386_सूची32,
	IMAGE_REL_I386_सूची32NB,
	IMAGE_REL_I386_SEG12,
	IMAGE_REL_I386_SECTION,
	IMAGE_REL_I386_SECREL,
	IMAGE_REL_I386_TOKEN,
	IMAGE_REL_I386_SECREL7,
	IMAGE_REL_I386_REL32,
पूर्ण;

क्रमागत ia64_coff_reloc_type अणु
	IMAGE_REL_IA64_ABSOLUTE,
	IMAGE_REL_IA64_IMM14,
	IMAGE_REL_IA64_IMM22,
	IMAGE_REL_IA64_IMM64,
	IMAGE_REL_IA64_सूची32,
	IMAGE_REL_IA64_सूची64,
	IMAGE_REL_IA64_PCREL21B,
	IMAGE_REL_IA64_PCREL21M,
	IMAGE_REL_IA64_PCREL21F,
	IMAGE_REL_IA64_GPREL22,
	IMAGE_REL_IA64_LTOFF22,
	IMAGE_REL_IA64_SECTION,
	IMAGE_REL_IA64_SECREL22,
	IMAGE_REL_IA64_SECREL64I,
	IMAGE_REL_IA64_SECREL32,
	IMAGE_REL_IA64_सूची32NB,
	IMAGE_REL_IA64_SREL14,
	IMAGE_REL_IA64_SREL22,
	IMAGE_REL_IA64_SREL32,
	IMAGE_REL_IA64_UREL32,
	IMAGE_REL_IA64_PCREL60X,
	IMAGE_REL_IA64_PCREL60B,
	IMAGE_REL_IA64_PCREL60F,
	IMAGE_REL_IA64_PCREL60I,
	IMAGE_REL_IA64_PCREL60M,
	IMAGE_REL_IA64_IMMGPREL6,
	IMAGE_REL_IA64_TOKEN,
	IMAGE_REL_IA64_GPREL32,
	IMAGE_REL_IA64_ADDEND,
पूर्ण;

काष्ठा coff_reloc अणु
	uपूर्णांक32_t भव_address;
	uपूर्णांक32_t symbol_table_index;
	जोड़ अणु
		क्रमागत x64_coff_reloc_type  x64_type;
		क्रमागत arm_coff_reloc_type  arm_type;
		क्रमागत sh_coff_reloc_type   sh_type;
		क्रमागत ppc_coff_reloc_type  ppc_type;
		क्रमागत x86_coff_reloc_type  x86_type;
		क्रमागत ia64_coff_reloc_type ia64_type;
		uपूर्णांक16_t data;
	पूर्ण;
पूर्ण;

/*
 * Definitions क्रम the contents of the certs data block
 */
#घोषणा WIN_CERT_TYPE_PKCS_SIGNED_DATA	0x0002
#घोषणा WIN_CERT_TYPE_EFI_OKCS115	0x0EF0
#घोषणा WIN_CERT_TYPE_EFI_GUID		0x0EF1

#घोषणा WIN_CERT_REVISION_1_0	0x0100
#घोषणा WIN_CERT_REVISION_2_0	0x0200

काष्ठा win_certअगरicate अणु
	uपूर्णांक32_t length;
	uपूर्णांक16_t revision;
	uपूर्णांक16_t cert_type;
पूर्ण;

#पूर्ण_अगर /* !__ASSEMBLY__ */

#पूर्ण_अगर /* __LINUX_PE_H */
