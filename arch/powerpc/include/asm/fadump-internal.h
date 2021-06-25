<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Firmware-Assisted Dump पूर्णांकernal code.
 *
 * Copyright 2011, Mahesh Salgaonkar, IBM Corporation.
 * Copyright 2019, Hari Bathini, IBM Corporation.
 */

#अगर_अघोषित _ASM_POWERPC_FADUMP_INTERNAL_H
#घोषणा _ASM_POWERPC_FADUMP_INTERNAL_H

/* Maximum number of memory regions kernel supports */
#घोषणा FADUMP_MAX_MEM_REGS			128

#अगर_अघोषित CONFIG_PRESERVE_FA_DUMP

/* The upper limit percentage क्रम user specअगरied boot memory size (25%) */
#घोषणा MAX_BOOT_MEM_RATIO			4

#घोषणा memblock_num_regions(memblock_type)	(memblock.memblock_type.cnt)

/* Alignment per CMA requirement. */
#घोषणा FADUMP_CMA_ALIGNMENT	(PAGE_SIZE <<				\
				 max_t(अचिन्हित दीर्घ, MAX_ORDER - 1,	\
				 pageblock_order))

/* FAD commands */
#घोषणा FADUMP_REGISTER			1
#घोषणा FADUMP_UNREGISTER		2
#घोषणा FADUMP_INVALIDATE		3

/*
 * Copy the ascii values क्रम first 8 अक्षरacters from a string पूर्णांकo u64
 * variable at their respective indexes.
 * e.g.
 *  The string "FADMPINF" will be converted पूर्णांकo 0x4641444d50494e46
 */
अटल अंतरभूत u64 fadump_str_to_u64(स्थिर अक्षर *str)
अणु
	u64 val = 0;
	पूर्णांक i;

	क्रम (i = 0; i < माप(val); i++)
		val = (*str) ? (val << 8) | *str++ : val << 8;
	वापस val;
पूर्ण

#घोषणा FADUMP_CPU_UNKNOWN		(~((u32)0))

#घोषणा FADUMP_CRASH_INFO_MAGIC		fadump_str_to_u64("FADMPINF")

/* fadump crash info काष्ठाure */
काष्ठा fadump_crash_info_header अणु
	u64		magic_number;
	u64		elfcorehdr_addr;
	u32		crashing_cpu;
	काष्ठा pt_regs	regs;
	काष्ठा cpumask	online_mask;
पूर्ण;

काष्ठा fadump_memory_range अणु
	u64	base;
	u64	size;
पूर्ण;

/* fadump memory ranges info */
#घोषणा RNG_NAME_SZ			16
काष्ठा fadump_mrange_info अणु
	अक्षर				name[RNG_NAME_SZ];
	काष्ठा fadump_memory_range	*mem_ranges;
	u32				mem_ranges_sz;
	u32				mem_range_cnt;
	u32				max_mem_ranges;
	bool				is_अटल;
पूर्ण;

/* Platक्रमm specअगरic callback functions */
काष्ठा fadump_ops;

/* Firmware-assisted dump configuration details. */
काष्ठा fw_dump अणु
	अचिन्हित दीर्घ	reserve_dump_area_start;
	अचिन्हित दीर्घ	reserve_dump_area_size;
	/* cmd line option during boot */
	अचिन्हित दीर्घ	reserve_bootvar;

	अचिन्हित दीर्घ	cpu_state_data_size;
	u64		cpu_state_dest_vaddr;
	u32		cpu_state_data_version;
	u32		cpu_state_entry_size;

	अचिन्हित दीर्घ	hpte_region_size;

	अचिन्हित दीर्घ	boot_memory_size;
	u64		boot_mem_dest_addr;
	u64		boot_mem_addr[FADUMP_MAX_MEM_REGS];
	u64		boot_mem_sz[FADUMP_MAX_MEM_REGS];
	u64		boot_mem_top;
	u64		boot_mem_regs_cnt;

	अचिन्हित दीर्घ	fadumphdr_addr;
	अचिन्हित दीर्घ	cpu_notes_buf_vaddr;
	अचिन्हित दीर्घ	cpu_notes_buf_size;

	/*
	 * Maximum size supported by firmware to copy from source to
	 * destination address per entry.
	 */
	u64		max_copy_size;
	u64		kernel_metadata;

	पूर्णांक		ibm_configure_kernel_dump;

	अचिन्हित दीर्घ	fadump_enabled:1;
	अचिन्हित दीर्घ	fadump_supported:1;
	अचिन्हित दीर्घ	dump_active:1;
	अचिन्हित दीर्घ	dump_रेजिस्टरed:1;
	अचिन्हित दीर्घ	nocma:1;

	काष्ठा fadump_ops	*ops;
पूर्ण;

काष्ठा fadump_ops अणु
	u64	(*fadump_init_mem_काष्ठा)(काष्ठा fw_dump *fadump_conf);
	u64	(*fadump_get_metadata_size)(व्योम);
	पूर्णांक	(*fadump_setup_metadata)(काष्ठा fw_dump *fadump_conf);
	u64	(*fadump_get_booपंचांगem_min)(व्योम);
	पूर्णांक	(*fadump_रेजिस्टर)(काष्ठा fw_dump *fadump_conf);
	पूर्णांक	(*fadump_unरेजिस्टर)(काष्ठा fw_dump *fadump_conf);
	पूर्णांक	(*fadump_invalidate)(काष्ठा fw_dump *fadump_conf);
	व्योम	(*fadump_cleanup)(काष्ठा fw_dump *fadump_conf);
	पूर्णांक	(*fadump_process)(काष्ठा fw_dump *fadump_conf);
	व्योम	(*fadump_region_show)(काष्ठा fw_dump *fadump_conf,
				      काष्ठा seq_file *m);
	व्योम	(*fadump_trigger)(काष्ठा fadump_crash_info_header *fdh,
				  स्थिर अक्षर *msg);
पूर्ण;

/* Helper functions */
s32 fadump_setup_cpu_notes_buf(u32 num_cpus);
व्योम fadump_मुक्त_cpu_notes_buf(व्योम);
u32 *fadump_regs_to_elf_notes(u32 *buf, काष्ठा pt_regs *regs);
व्योम fadump_update_elfcore_header(अक्षर *bufp);
bool is_fadump_boot_mem_contiguous(व्योम);
bool is_fadump_reserved_mem_contiguous(व्योम);

#अन्यथा /* !CONFIG_PRESERVE_FA_DUMP */

/* Firmware-assisted dump configuration details. */
काष्ठा fw_dump अणु
	u64	boot_mem_top;
	u64	dump_active;
पूर्ण;

#पूर्ण_अगर /* CONFIG_PRESERVE_FA_DUMP */

#अगर_घोषित CONFIG_PPC_PSERIES
बाह्य व्योम rtas_fadump_dt_scan(काष्ठा fw_dump *fadump_conf, u64 node);
#अन्यथा
अटल अंतरभूत व्योम
rtas_fadump_dt_scan(काष्ठा fw_dump *fadump_conf, u64 node) अणु पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC_POWERNV
बाह्य व्योम opal_fadump_dt_scan(काष्ठा fw_dump *fadump_conf, u64 node);
#अन्यथा
अटल अंतरभूत व्योम
opal_fadump_dt_scan(काष्ठा fw_dump *fadump_conf, u64 node) अणु पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_POWERPC_FADUMP_INTERNAL_H */
