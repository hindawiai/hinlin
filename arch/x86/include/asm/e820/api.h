<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_E820_API_H
#घोषणा _ASM_E820_API_H

#समावेश <यंत्र/e820/types.h>

बाह्य काष्ठा e820_table *e820_table;
बाह्य काष्ठा e820_table *e820_table_kexec;
बाह्य काष्ठा e820_table *e820_table_firmware;

बाह्य अचिन्हित दीर्घ pci_mem_start;

बाह्य bool e820__mapped_raw_any(u64 start, u64 end, क्रमागत e820_type type);
बाह्य bool e820__mapped_any(u64 start, u64 end, क्रमागत e820_type type);
बाह्य bool e820__mapped_all(u64 start, u64 end, क्रमागत e820_type type);

बाह्य व्योम e820__range_add   (u64 start, u64 size, क्रमागत e820_type type);
बाह्य u64  e820__range_update(u64 start, u64 size, क्रमागत e820_type old_type, क्रमागत e820_type new_type);
बाह्य u64  e820__range_हटाओ(u64 start, u64 size, क्रमागत e820_type old_type, bool check_type);

बाह्य व्योम e820__prपूर्णांक_table(अक्षर *who);
बाह्य पूर्णांक  e820__update_table(काष्ठा e820_table *table);
बाह्य व्योम e820__update_table_prपूर्णांक(व्योम);

बाह्य अचिन्हित दीर्घ e820__end_of_ram_pfn(व्योम);
बाह्य अचिन्हित दीर्घ e820__end_of_low_ram_pfn(व्योम);

बाह्य u64  e820__memblock_alloc_reserved(u64 size, u64 align);
बाह्य व्योम e820__memblock_setup(व्योम);

बाह्य व्योम e820__reserve_setup_data(व्योम);
बाह्य व्योम e820__finish_early_params(व्योम);
बाह्य व्योम e820__reserve_resources(व्योम);
बाह्य व्योम e820__reserve_resources_late(व्योम);

बाह्य व्योम e820__memory_setup(व्योम);
बाह्य व्योम e820__memory_setup_extended(u64 phys_addr, u32 data_len);
बाह्य अक्षर *e820__memory_setup_शेष(व्योम);
बाह्य व्योम e820__setup_pci_gap(व्योम);

बाह्य व्योम e820__पुनः_स्मृतिate_tables(व्योम);
बाह्य व्योम e820__रेजिस्टर_nosave_regions(अचिन्हित दीर्घ limit_pfn);

बाह्य पूर्णांक  e820__get_entry_type(u64 start, u64 end);

/*
 * Returns true अगरf the specअगरied range [start,end) is completely contained inside
 * the ISA region.
 */
अटल अंतरभूत bool is_ISA_range(u64 start, u64 end)
अणु
	वापस start >= ISA_START_ADDRESS && end <= ISA_END_ADDRESS;
पूर्ण

#पूर्ण_अगर /* _ASM_E820_API_H */
