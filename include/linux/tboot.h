<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * tboot.h: shared data काष्ठाure with tboot and kernel and functions
 *          used by kernel क्रम runसमय support of Intel(R) Trusted
 *          Execution Technology
 *
 * Copyright (c) 2006-2009, Intel Corporation
 */

#अगर_अघोषित _LINUX_TBOOT_H
#घोषणा _LINUX_TBOOT_H

/* these must have the values from 0-5 in this order */
क्रमागत अणु
	TB_SHUTDOWN_REBOOT = 0,
	TB_SHUTDOWN_S5,
	TB_SHUTDOWN_S4,
	TB_SHUTDOWN_S3,
	TB_SHUTDOWN_HALT,
	TB_SHUTDOWN_WFS
पूर्ण;

#अगर_घोषित CONFIG_INTEL_TXT
#समावेश <linux/acpi.h>
/* used to communicate between tboot and the launched kernel */

#घोषणा TB_KEY_SIZE             64   /* 512 bits */

#घोषणा MAX_TB_MAC_REGIONS      32

काष्ठा tboot_mac_region अणु
	u64  start;         /* must be 64 byte -aligned */
	u32  size;          /* must be 64 byte -granular */
पूर्ण __packed;

/* GAS - Generic Address Structure (ACPI 2.0+) */
काष्ठा tboot_acpi_generic_address अणु
	u8  space_id;
	u8  bit_width;
	u8  bit_offset;
	u8  access_width;
	u64 address;
पूर्ण __packed;

/*
 * combines Sx info from FADT and FACS tables per ACPI 2.0+ spec
 * (https://uefi.org/specअगरications)
 */
काष्ठा tboot_acpi_sleep_info अणु
	काष्ठा tboot_acpi_generic_address pm1a_cnt_blk;
	काष्ठा tboot_acpi_generic_address pm1b_cnt_blk;
	काष्ठा tboot_acpi_generic_address pm1a_evt_blk;
	काष्ठा tboot_acpi_generic_address pm1b_evt_blk;
	u16 pm1a_cnt_val;
	u16 pm1b_cnt_val;
	u64 wakeup_vector;
	u32 vector_width;
	u64 kernel_s3_resume_vector;
पूर्ण __packed;

/*
 * shared memory page used क्रम communication between tboot and kernel
 */
काष्ठा tboot अणु
	/*
	 * version 3+ fields:
	 */

	/* TBOOT_UUID */
	u8 uuid[16];

	/* version number: 5 is current */
	u32 version;

	/* physical addr of tb_log_t log */
	u32 log_addr;

	/*
	 * physical addr of entry poपूर्णांक क्रम tboot shutकरोwn and
	 * type of shutकरोwn (TB_SHUTDOWN_*) being requested
	 */
	u32 shutकरोwn_entry;
	u32 shutकरोwn_type;

	/* kernel-specअगरied ACPI info क्रम Sx shutकरोwn */
	काष्ठा tboot_acpi_sleep_info acpi_sinfo;

	/* tboot location in memory (physical) */
	u32 tboot_base;
	u32 tboot_size;

	/* memory regions (phys addrs) क्रम tboot to MAC on S3 */
	u8 num_mac_regions;
	काष्ठा tboot_mac_region mac_regions[MAX_TB_MAC_REGIONS];


	/*
	 * version 4+ fields:
	 */

	/* symmetric key क्रम use by kernel; will be encrypted on S3 */
	u8 s3_key[TB_KEY_SIZE];


	/*
	 * version 5+ fields:
	 */

	/* used to 4byte-align num_in_wfs */
	u8 reserved_align[3];

	/* number of processors in रुको-क्रम-SIPI */
	u32 num_in_wfs;
पूर्ण __packed;

/*
 * UUID क्रम tboot data काष्ठा to facilitate matching
 * defined as अणु663C8DFF-E8B3-4b82-AABF-19EA4D057A08पूर्ण by tboot, which is
 * represented as अणुपूर्ण in the अक्षर array used here
 */
#घोषणा TBOOT_UUID	अणु0xff, 0x8d, 0x3c, 0x66, 0xb3, 0xe8, 0x82, 0x4b, 0xbf,\
			 0xaa, 0x19, 0xea, 0x4d, 0x5, 0x7a, 0x8पूर्ण

bool tboot_enabled(व्योम);
बाह्य व्योम tboot_probe(व्योम);
बाह्य व्योम tboot_shutकरोwn(u32 shutकरोwn_type);
बाह्य काष्ठा acpi_table_header *tboot_get_dmar_table(
				      काष्ठा acpi_table_header *dmar_tbl);
बाह्य पूर्णांक tboot_क्रमce_iommu(व्योम);

#अन्यथा

#घोषणा tboot_enabled()			0
#घोषणा tboot_probe()			करो अणु पूर्ण जबतक (0)
#घोषणा tboot_shutकरोwn(shutकरोwn_type)	करो अणु पूर्ण जबतक (0)
#घोषणा tboot_sleep(sleep_state, pm1a_control, pm1b_control)	\
					करो अणु पूर्ण जबतक (0)
#घोषणा tboot_get_dmar_table(dmar_tbl)	(dmar_tbl)
#घोषणा tboot_क्रमce_iommu()		0

#पूर्ण_अगर /* !CONFIG_INTEL_TXT */

#पूर्ण_अगर /* _LINUX_TBOOT_H */
