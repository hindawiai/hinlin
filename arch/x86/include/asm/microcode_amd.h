<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_MICROCODE_AMD_H
#घोषणा _ASM_X86_MICROCODE_AMD_H

#समावेश <यंत्र/microcode.h>

#घोषणा UCODE_MAGIC			0x00414d44
#घोषणा UCODE_EQUIV_CPU_TABLE_TYPE	0x00000000
#घोषणा UCODE_UCODE_TYPE		0x00000001

#घोषणा SECTION_HDR_SIZE		8
#घोषणा CONTAINER_HDR_SZ		12

काष्ठा equiv_cpu_entry अणु
	u32	installed_cpu;
	u32	fixed_errata_mask;
	u32	fixed_errata_compare;
	u16	equiv_cpu;
	u16	res;
पूर्ण __attribute__((packed));

काष्ठा microcode_header_amd अणु
	u32	data_code;
	u32	patch_id;
	u16	mc_patch_data_id;
	u8	mc_patch_data_len;
	u8	init_flag;
	u32	mc_patch_data_checksum;
	u32	nb_dev_id;
	u32	sb_dev_id;
	u16	processor_rev_id;
	u8	nb_rev_id;
	u8	sb_rev_id;
	u8	bios_api_rev;
	u8	reserved1[3];
	u32	match_reg[8];
पूर्ण __attribute__((packed));

काष्ठा microcode_amd अणु
	काष्ठा microcode_header_amd	hdr;
	अचिन्हित पूर्णांक			mpb[0];
पूर्ण;

#घोषणा PATCH_MAX_SIZE (3 * PAGE_SIZE)

#अगर_घोषित CONFIG_MICROCODE_AMD
बाह्य व्योम __init load_ucode_amd_bsp(अचिन्हित पूर्णांक family);
बाह्य व्योम load_ucode_amd_ap(अचिन्हित पूर्णांक family);
बाह्य पूर्णांक __init save_microcode_in_initrd_amd(अचिन्हित पूर्णांक family);
व्योम reload_ucode_amd(व्योम);
#अन्यथा
अटल अंतरभूत व्योम __init load_ucode_amd_bsp(अचिन्हित पूर्णांक family) अणुपूर्ण
अटल अंतरभूत व्योम load_ucode_amd_ap(अचिन्हित पूर्णांक family) अणुपूर्ण
अटल अंतरभूत पूर्णांक __init
save_microcode_in_initrd_amd(अचिन्हित पूर्णांक family) अणु वापस -EINVAL; पूर्ण
अटल अंतरभूत व्योम reload_ucode_amd(व्योम) अणुपूर्ण
#पूर्ण_अगर
#पूर्ण_अगर /* _ASM_X86_MICROCODE_AMD_H */
