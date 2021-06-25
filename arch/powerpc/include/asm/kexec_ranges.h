<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
#अगर_अघोषित _ASM_POWERPC_KEXEC_RANGES_H
#घोषणा _ASM_POWERPC_KEXEC_RANGES_H

#घोषणा MEM_RANGE_CHUNK_SZ		2048	/* Memory ranges size chunk */

व्योम sort_memory_ranges(काष्ठा crash_mem *mrngs, bool merge);
काष्ठा crash_mem *पुनः_स्मृति_mem_ranges(काष्ठा crash_mem **mem_ranges);
पूर्णांक add_mem_range(काष्ठा crash_mem **mem_ranges, u64 base, u64 size);
पूर्णांक add_tce_mem_ranges(काष्ठा crash_mem **mem_ranges);
पूर्णांक add_initrd_mem_range(काष्ठा crash_mem **mem_ranges);
#अगर_घोषित CONFIG_PPC_BOOK3S_64
पूर्णांक add_htab_mem_range(काष्ठा crash_mem **mem_ranges);
#अन्यथा
अटल अंतरभूत पूर्णांक add_htab_mem_range(काष्ठा crash_mem **mem_ranges)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर
पूर्णांक add_kernel_mem_range(काष्ठा crash_mem **mem_ranges);
पूर्णांक add_rtas_mem_range(काष्ठा crash_mem **mem_ranges);
पूर्णांक add_opal_mem_range(काष्ठा crash_mem **mem_ranges);
पूर्णांक add_reserved_mem_ranges(काष्ठा crash_mem **mem_ranges);

#पूर्ण_अगर /* _ASM_POWERPC_KEXEC_RANGES_H */
