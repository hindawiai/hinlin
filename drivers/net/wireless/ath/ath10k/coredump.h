<शैली गुरु>
/* SPDX-License-Identअगरier: ISC */
/*
 * Copyright (c) 2011-2017 Qualcomm Atheros, Inc.
 */

#अगर_अघोषित _COREDUMP_H_
#घोषणा _COREDUMP_H_

#समावेश "core.h"

#घोषणा ATH10K_FW_CRASH_DUMP_VERSION 1

/**
 * क्रमागत ath10k_fw_crash_dump_type - types of data in the dump file
 * @ATH10K_FW_CRASH_DUMP_REGDUMP: Register crash dump in binary क्रमmat
 */
क्रमागत ath10k_fw_crash_dump_type अणु
	ATH10K_FW_CRASH_DUMP_REGISTERS = 0,
	ATH10K_FW_CRASH_DUMP_CE_DATA = 1,

	/* contains multiple काष्ठा ath10k_dump_ram_data_hdr */
	ATH10K_FW_CRASH_DUMP_RAM_DATA = 2,

	ATH10K_FW_CRASH_DUMP_MAX,
पूर्ण;

काष्ठा ath10k_tlv_dump_data अणु
	/* see ath10k_fw_crash_dump_type above */
	__le32 type;

	/* in bytes */
	__le32 tlv_len;

	/* pad to 32-bit boundaries as needed */
	u8 tlv_data[];
पूर्ण __packed;

काष्ठा ath10k_dump_file_data अणु
	/* dump file inक्रमmation */

	/* "ATH10K-FW-DUMP" */
	अक्षर df_magic[16];

	__le32 len;

	/* file dump version */
	__le32 version;

	/* some info we can get from ath10k काष्ठा that might help */

	guid_t guid;

	__le32 chip_id;

	/* 0 क्रम now, in place क्रम later hardware */
	__le32 bus_type;

	__le32 target_version;
	__le32 fw_version_major;
	__le32 fw_version_minor;
	__le32 fw_version_release;
	__le32 fw_version_build;
	__le32 phy_capability;
	__le32 hw_min_tx_घातer;
	__le32 hw_max_tx_घातer;
	__le32 ht_cap_info;
	__le32 vht_cap_info;
	__le32 num_rf_chains;

	/* firmware version string */
	अक्षर fw_ver[ETHTOOL_FWVERS_LEN];

	/* Kernel related inक्रमmation */

	/* समय-of-day stamp */
	__le64 tv_sec;

	/* समय-of-day stamp, nano-seconds */
	__le64 tv_nsec;

	/* LINUX_VERSION_CODE */
	__le32 kernel_ver_code;

	/* VERMAGIC_STRING */
	अक्षर kernel_ver[64];

	/* room क्रम growth w/out changing binary क्रमmat */
	u8 unused[128];

	/* काष्ठा ath10k_tlv_dump_data + more */
	u8 data[];
पूर्ण __packed;

काष्ठा ath10k_dump_ram_data_hdr अणु
	/* क्रमागत ath10k_mem_region_type */
	__le32 region_type;

	__le32 start;

	/* length of payload data, not including this header */
	__le32 length;

	u8 data[];
पूर्ण;

/* magic number to fill the holes not copied due to sections in regions */
#घोषणा ATH10K_MAGIC_NOT_COPIED		0xAA

/* part of user space ABI */
क्रमागत ath10k_mem_region_type अणु
	ATH10K_MEM_REGION_TYPE_REG	= 1,
	ATH10K_MEM_REGION_TYPE_DRAM	= 2,
	ATH10K_MEM_REGION_TYPE_AXI	= 3,
	ATH10K_MEM_REGION_TYPE_IRAM1	= 4,
	ATH10K_MEM_REGION_TYPE_IRAM2	= 5,
	ATH10K_MEM_REGION_TYPE_IOSRAM	= 6,
	ATH10K_MEM_REGION_TYPE_IOREG	= 7,
	ATH10K_MEM_REGION_TYPE_MSA	= 8,
पूर्ण;

/* Define a section of the region which should be copied. As not all parts
 * of the memory is possible to copy, क्रम example some of the रेजिस्टरs can
 * be like that, sections can be used to define what is safe to copy.
 *
 * To minimize the size of the array, the list must obey the क्रमmat:
 * '{start0,stop0},{start1,stop1},{start2,stop2}....' The values below must
 * also obey to 'start0 < stop0 < start1 < stop1 < start2 < ...', otherwise
 * we may encouter error in the dump processing.
 */
काष्ठा ath10k_mem_section अणु
	u32 start;
	u32 end;
पूर्ण;

/* One region of a memory layout. If the sections field is null entire
 * region is copied. If sections is non-null only the areas specअगरied in
 * sections are copied and rest of the areas are filled with
 * ATH10K_MAGIC_NOT_COPIED.
 */
काष्ठा ath10k_mem_region अणु
	क्रमागत ath10k_mem_region_type type;
	u32 start;
	u32 len;

	स्थिर अक्षर *name;

	काष्ठा अणु
		स्थिर काष्ठा ath10k_mem_section *sections;
		u32 size;
	पूर्ण section_table;
पूर्ण;

/* Contains the memory layout of a hardware version identअगरied with the
 * hardware id, split पूर्णांकo regions.
 */
काष्ठा ath10k_hw_mem_layout अणु
	u32 hw_id;
	u32 hw_rev;
	क्रमागत ath10k_bus bus;

	काष्ठा अणु
		स्थिर काष्ठा ath10k_mem_region *regions;
		पूर्णांक size;
	पूर्ण region_table;
पूर्ण;

/* FIXME: where to put this? */
बाह्य अचिन्हित दीर्घ ath10k_coredump_mask;

#अगर_घोषित CONFIG_DEV_COREDUMP

पूर्णांक ath10k_coredump_submit(काष्ठा ath10k *ar);
काष्ठा ath10k_fw_crash_data *ath10k_coredump_new(काष्ठा ath10k *ar);
पूर्णांक ath10k_coredump_create(काष्ठा ath10k *ar);
पूर्णांक ath10k_coredump_रेजिस्टर(काष्ठा ath10k *ar);
व्योम ath10k_coredump_unरेजिस्टर(काष्ठा ath10k *ar);
व्योम ath10k_coredump_destroy(काष्ठा ath10k *ar);

स्थिर काष्ठा ath10k_hw_mem_layout *ath10k_coredump_get_mem_layout(काष्ठा ath10k *ar);

#अन्यथा /* CONFIG_DEV_COREDUMP */

अटल अंतरभूत पूर्णांक ath10k_coredump_submit(काष्ठा ath10k *ar)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा ath10k_fw_crash_data *ath10k_coredump_new(काष्ठा ath10k *ar)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक ath10k_coredump_create(काष्ठा ath10k *ar)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक ath10k_coredump_रेजिस्टर(काष्ठा ath10k *ar)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम ath10k_coredump_unरेजिस्टर(काष्ठा ath10k *ar)
अणु
पूर्ण

अटल अंतरभूत व्योम ath10k_coredump_destroy(काष्ठा ath10k *ar)
अणु
पूर्ण

अटल अंतरभूत स्थिर काष्ठा ath10k_hw_mem_layout *
ath10k_coredump_get_mem_layout(काष्ठा ath10k *ar)
अणु
	वापस शून्य;
पूर्ण

#पूर्ण_अगर /* CONFIG_DEV_COREDUMP */

#पूर्ण_अगर /* _COREDUMP_H_ */
