<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_EFI_H
#घोषणा _LINUX_EFI_H

/*
 * Extensible Firmware Interface
 * Based on 'Extensible Firmware Interface Specification' version 0.9, April 30, 1999
 *
 * Copyright (C) 1999 VA Linux Systems
 * Copyright (C) 1999 Walt Drummond <drummond@valinux.com>
 * Copyright (C) 1999, 2002-2003 Hewlett-Packard Co.
 *	David Mosberger-Tang <davidm@hpl.hp.com>
 *	Stephane Eranian <eranian@hpl.hp.com>
 */
#समावेश <linux/init.h>
#समावेश <linux/माला.स>
#समावेश <linux/समय.स>
#समावेश <linux/types.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/rtc.h>
#समावेश <linux/ioport.h>
#समावेश <linux/pfn.h>
#समावेश <linux/pstore.h>
#समावेश <linux/range.h>
#समावेश <linux/reboot.h>
#समावेश <linux/uuid.h>
#समावेश <linux/screen_info.h>

#समावेश <यंत्र/page.h>

#घोषणा EFI_SUCCESS		0
#घोषणा EFI_LOAD_ERROR		( 1 | (1UL << (BITS_PER_LONG-1)))
#घोषणा EFI_INVALID_PARAMETER	( 2 | (1UL << (BITS_PER_LONG-1)))
#घोषणा EFI_UNSUPPORTED		( 3 | (1UL << (BITS_PER_LONG-1)))
#घोषणा EFI_BAD_BUFFER_SIZE	( 4 | (1UL << (BITS_PER_LONG-1)))
#घोषणा EFI_BUFFER_TOO_SMALL	( 5 | (1UL << (BITS_PER_LONG-1)))
#घोषणा EFI_NOT_READY		( 6 | (1UL << (BITS_PER_LONG-1)))
#घोषणा EFI_DEVICE_ERROR	( 7 | (1UL << (BITS_PER_LONG-1)))
#घोषणा EFI_WRITE_PROTECTED	( 8 | (1UL << (BITS_PER_LONG-1)))
#घोषणा EFI_OUT_OF_RESOURCES	( 9 | (1UL << (BITS_PER_LONG-1)))
#घोषणा EFI_NOT_FOUND		(14 | (1UL << (BITS_PER_LONG-1)))
#घोषणा EFI_TIMEOUT		(18 | (1UL << (BITS_PER_LONG-1)))
#घोषणा EFI_ABORTED		(21 | (1UL << (BITS_PER_LONG-1)))
#घोषणा EFI_SECURITY_VIOLATION	(26 | (1UL << (BITS_PER_LONG-1)))

प्रकार अचिन्हित दीर्घ efi_status_t;
प्रकार u8 efi_bool_t;
प्रकार u16 efi_अक्षर16_t;		/* UNICODE अक्षरacter */
प्रकार u64 efi_physical_addr_t;
प्रकार व्योम *efi_handle_t;

#अगर defined(CONFIG_X86_64)
#घोषणा __efiapi __attribute__((ms_abi))
#या_अगर defined(CONFIG_X86_32)
#घोषणा __efiapi __attribute__((regparm(0)))
#अन्यथा
#घोषणा __efiapi
#पूर्ण_अगर

/*
 * The UEFI spec and EDK2 reference implementation both define EFI_GUID as
 * काष्ठा अणु u32 a; u16; b; u16 c; u8 d[8]; पूर्ण; and so the implied alignment
 * is 32 bits not 8 bits like our guid_t. In some हालs (i.e., on 32-bit ARM),
 * this means that firmware services invoked by the kernel may assume that
 * efi_guid_t* arguments are 32-bit aligned, and use memory accessors that
 * करो not tolerate misalignment. So let's set the minimum alignment to 32 bits.
 *
 * Note that the UEFI spec as well as some comments in the EDK2 code base
 * suggest that EFI_GUID should be 64-bit aligned, but this appears to be
 * a mistake, given that no code seems to exist that actually enक्रमces that
 * or relies on it.
 */
प्रकार guid_t efi_guid_t __aligned(__alignof__(u32));

#घोषणा EFI_GUID(a, b, c, d...) (efi_guid_t)अणु अणु					\
	(a) & 0xff, ((a) >> 8) & 0xff, ((a) >> 16) & 0xff, ((a) >> 24) & 0xff,	\
	(b) & 0xff, ((b) >> 8) & 0xff,						\
	(c) & 0xff, ((c) >> 8) & 0xff, d पूर्ण पूर्ण

/*
 * Generic EFI table header
 */
प्रकार	काष्ठा अणु
	u64 signature;
	u32 revision;
	u32 headersize;
	u32 crc32;
	u32 reserved;
पूर्ण efi_table_hdr_t;

/*
 * Memory map descriptor:
 */

/* Memory types: */
#घोषणा EFI_RESERVED_TYPE		 0
#घोषणा EFI_LOADER_CODE			 1
#घोषणा EFI_LOADER_DATA			 2
#घोषणा EFI_BOOT_SERVICES_CODE		 3
#घोषणा EFI_BOOT_SERVICES_DATA		 4
#घोषणा EFI_RUNTIME_SERVICES_CODE	 5
#घोषणा EFI_RUNTIME_SERVICES_DATA	 6
#घोषणा EFI_CONVENTIONAL_MEMORY		 7
#घोषणा EFI_UNUSABLE_MEMORY		 8
#घोषणा EFI_ACPI_RECLAIM_MEMORY		 9
#घोषणा EFI_ACPI_MEMORY_NVS		10
#घोषणा EFI_MEMORY_MAPPED_IO		11
#घोषणा EFI_MEMORY_MAPPED_IO_PORT_SPACE	12
#घोषणा EFI_PAL_CODE			13
#घोषणा EFI_PERSISTENT_MEMORY		14
#घोषणा EFI_MAX_MEMORY_TYPE		15

/* Attribute values: */
#घोषणा EFI_MEMORY_UC		((u64)0x0000000000000001ULL)	/* uncached */
#घोषणा EFI_MEMORY_WC		((u64)0x0000000000000002ULL)	/* ग_लिखो-coalescing */
#घोषणा EFI_MEMORY_WT		((u64)0x0000000000000004ULL)	/* ग_लिखो-through */
#घोषणा EFI_MEMORY_WB		((u64)0x0000000000000008ULL)	/* ग_लिखो-back */
#घोषणा EFI_MEMORY_UCE		((u64)0x0000000000000010ULL)	/* uncached, exported */
#घोषणा EFI_MEMORY_WP		((u64)0x0000000000001000ULL)	/* ग_लिखो-protect */
#घोषणा EFI_MEMORY_RP		((u64)0x0000000000002000ULL)	/* पढ़ो-protect */
#घोषणा EFI_MEMORY_XP		((u64)0x0000000000004000ULL)	/* execute-protect */
#घोषणा EFI_MEMORY_NV		((u64)0x0000000000008000ULL)	/* non-अस्थिर */
#घोषणा EFI_MEMORY_MORE_RELIABLE \
				((u64)0x0000000000010000ULL)	/* higher reliability */
#घोषणा EFI_MEMORY_RO		((u64)0x0000000000020000ULL)	/* पढ़ो-only */
#घोषणा EFI_MEMORY_SP		((u64)0x0000000000040000ULL)	/* soft reserved */
#घोषणा EFI_MEMORY_CPU_CRYPTO	((u64)0x0000000000080000ULL)	/* supports encryption */
#घोषणा EFI_MEMORY_RUNTIME	((u64)0x8000000000000000ULL)	/* range requires runसमय mapping */
#घोषणा EFI_MEMORY_DESCRIPTOR_VERSION	1

#घोषणा EFI_PAGE_SHIFT		12
#घोषणा EFI_PAGE_SIZE		(1UL << EFI_PAGE_SHIFT)
#घोषणा EFI_PAGES_MAX		(U64_MAX >> EFI_PAGE_SHIFT)

प्रकार काष्ठा अणु
	u32 type;
	u32 pad;
	u64 phys_addr;
	u64 virt_addr;
	u64 num_pages;
	u64 attribute;
पूर्ण efi_memory_desc_t;

प्रकार काष्ठा अणु
	efi_guid_t guid;
	u32 headersize;
	u32 flags;
	u32 imagesize;
पूर्ण efi_capsule_header_t;

/*
 * EFI capsule flags
 */
#घोषणा EFI_CAPSULE_PERSIST_ACROSS_RESET	0x00010000
#घोषणा EFI_CAPSULE_POPULATE_SYSTEM_TABLE	0x00020000
#घोषणा EFI_CAPSULE_INITIATE_RESET		0x00040000

काष्ठा capsule_info अणु
	efi_capsule_header_t	header;
	efi_capsule_header_t	*capsule;
	पूर्णांक			reset_type;
	दीर्घ			index;
	माप_प्रकार			count;
	माप_प्रकार			total_size;
	काष्ठा page		**pages;
	phys_addr_t		*phys;
	माप_प्रकार			page_bytes_reमुख्य;
पूर्ण;

पूर्णांक __efi_capsule_setup_info(काष्ठा capsule_info *cap_info);

/*
 * Types and defines क्रम Time Services
 */
#घोषणा EFI_TIME_ADJUST_DAYLIGHT 0x1
#घोषणा EFI_TIME_IN_DAYLIGHT     0x2
#घोषणा EFI_UNSPECIFIED_TIMEZONE 0x07ff

प्रकार काष्ठा अणु
	u16 year;
	u8 month;
	u8 day;
	u8 hour;
	u8 minute;
	u8 second;
	u8 pad1;
	u32 nanosecond;
	s16 समयzone;
	u8 daylight;
	u8 pad2;
पूर्ण efi_समय_प्रकार;

प्रकार काष्ठा अणु
	u32 resolution;
	u32 accuracy;
	u8 sets_to_zero;
पूर्ण efi_समय_cap_t;

प्रकार जोड़ efi_boot_services efi_boot_services_t;

/*
 * Types and defines क्रम EFI ResetSystem
 */
#घोषणा EFI_RESET_COLD 0
#घोषणा EFI_RESET_WARM 1
#घोषणा EFI_RESET_SHUTDOWN 2

/*
 * EFI Runसमय Services table
 */
#घोषणा EFI_RUNTIME_SERVICES_SIGNATURE ((u64)0x5652453544e5552ULL)
#घोषणा EFI_RUNTIME_SERVICES_REVISION  0x00010000

प्रकार काष्ठा अणु
	efi_table_hdr_t hdr;
	u32 get_समय;
	u32 set_समय;
	u32 get_wakeup_समय;
	u32 set_wakeup_समय;
	u32 set_भव_address_map;
	u32 convert_poपूर्णांकer;
	u32 get_variable;
	u32 get_next_variable;
	u32 set_variable;
	u32 get_next_high_mono_count;
	u32 reset_प्रणाली;
	u32 update_capsule;
	u32 query_capsule_caps;
	u32 query_variable_info;
पूर्ण efi_runसमय_services_32_t;

प्रकार efi_status_t efi_get_समय_प्रकार (efi_समय_प्रकार *पंचांग, efi_समय_cap_t *tc);
प्रकार efi_status_t efi_set_समय_प्रकार (efi_समय_प्रकार *पंचांग);
प्रकार efi_status_t efi_get_wakeup_समय_प्रकार (efi_bool_t *enabled, efi_bool_t *pending,
					    efi_समय_प्रकार *पंचांग);
प्रकार efi_status_t efi_set_wakeup_समय_प्रकार (efi_bool_t enabled, efi_समय_प्रकार *पंचांग);
प्रकार efi_status_t efi_get_variable_t (efi_अक्षर16_t *name, efi_guid_t *venकरोr, u32 *attr,
					 अचिन्हित दीर्घ *data_size, व्योम *data);
प्रकार efi_status_t efi_get_next_variable_t (अचिन्हित दीर्घ *name_size, efi_अक्षर16_t *name,
					      efi_guid_t *venकरोr);
प्रकार efi_status_t efi_set_variable_t (efi_अक्षर16_t *name, efi_guid_t *venकरोr, 
					 u32 attr, अचिन्हित दीर्घ data_size,
					 व्योम *data);
प्रकार efi_status_t efi_get_next_high_mono_count_t (u32 *count);
प्रकार व्योम efi_reset_प्रणाली_t (पूर्णांक reset_type, efi_status_t status,
				 अचिन्हित दीर्घ data_size, efi_अक्षर16_t *data);
प्रकार efi_status_t efi_set_भव_address_map_t (अचिन्हित दीर्घ memory_map_size,
						अचिन्हित दीर्घ descriptor_size,
						u32 descriptor_version,
						efi_memory_desc_t *भव_map);
प्रकार efi_status_t efi_query_variable_info_t(u32 attr,
					       u64 *storage_space,
					       u64 *reमुख्यing_space,
					       u64 *max_variable_size);
प्रकार efi_status_t efi_update_capsule_t(efi_capsule_header_t **capsules,
					  अचिन्हित दीर्घ count,
					  अचिन्हित दीर्घ sg_list);
प्रकार efi_status_t efi_query_capsule_caps_t(efi_capsule_header_t **capsules,
					      अचिन्हित दीर्घ count,
					      u64 *max_size,
					      पूर्णांक *reset_type);
प्रकार efi_status_t efi_query_variable_store_t(u32 attributes,
						अचिन्हित दीर्घ size,
						bool nonblocking);

प्रकार जोड़ अणु
	काष्ठा अणु
		efi_table_hdr_t				hdr;
		efi_get_समय_प्रकार __efiapi			*get_समय;
		efi_set_समय_प्रकार __efiapi			*set_समय;
		efi_get_wakeup_समय_प्रकार __efiapi		*get_wakeup_समय;
		efi_set_wakeup_समय_प्रकार __efiapi		*set_wakeup_समय;
		efi_set_भव_address_map_t __efiapi	*set_भव_address_map;
		व्योम					*convert_poपूर्णांकer;
		efi_get_variable_t __efiapi		*get_variable;
		efi_get_next_variable_t __efiapi	*get_next_variable;
		efi_set_variable_t __efiapi		*set_variable;
		efi_get_next_high_mono_count_t __efiapi	*get_next_high_mono_count;
		efi_reset_प्रणाली_t __efiapi		*reset_प्रणाली;
		efi_update_capsule_t __efiapi		*update_capsule;
		efi_query_capsule_caps_t __efiapi	*query_capsule_caps;
		efi_query_variable_info_t __efiapi	*query_variable_info;
	पूर्ण;
	efi_runसमय_services_32_t mixed_mode;
पूर्ण efi_runसमय_services_t;

व्योम efi_native_runसमय_setup(व्योम);

/*
 * EFI Configuration Table and GUID definitions
 *
 * These are all defined in a single line to make them easier to
 * grep क्रम and to see them at a glance - जबतक still having a
 * similar काष्ठाure to the definitions in the spec.
 *
 * Here's how they are काष्ठाured:
 *
 * GUID: 12345678-1234-1234-1234-123456789012
 * Spec:
 *      #घोषणा EFI_SOME_PROTOCOL_GUID \
 *        अणु0x12345678,0x1234,0x1234,\
 *          अणु0x12,0x34,0x12,0x34,0x56,0x78,0x90,0x12पूर्णपूर्ण
 * Here:
 *	#घोषणा SOME_PROTOCOL_GUID		EFI_GUID(0x12345678, 0x1234, 0x1234,  0x12, 0x34, 0x12, 0x34, 0x56, 0x78, 0x90, 0x12)
 *					^ tअसल					    ^extra space
 *
 * Note that the 'extra space' separates the values at the same place
 * where the UEFI SPEC अवरोधs the line.
 */
#घोषणा शून्य_GUID				EFI_GUID(0x00000000, 0x0000, 0x0000,  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)
#घोषणा MPS_TABLE_GUID				EFI_GUID(0xeb9d2d2f, 0x2d88, 0x11d3,  0x9a, 0x16, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d)
#घोषणा ACPI_TABLE_GUID				EFI_GUID(0xeb9d2d30, 0x2d88, 0x11d3,  0x9a, 0x16, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d)
#घोषणा ACPI_20_TABLE_GUID			EFI_GUID(0x8868e871, 0xe4f1, 0x11d3,  0xbc, 0x22, 0x00, 0x80, 0xc7, 0x3c, 0x88, 0x81)
#घोषणा SMBIOS_TABLE_GUID			EFI_GUID(0xeb9d2d31, 0x2d88, 0x11d3,  0x9a, 0x16, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d)
#घोषणा SMBIOS3_TABLE_GUID			EFI_GUID(0xf2fd1544, 0x9794, 0x4a2c,  0x99, 0x2e, 0xe5, 0xbb, 0xcf, 0x20, 0xe3, 0x94)
#घोषणा SAL_SYSTEM_TABLE_GUID			EFI_GUID(0xeb9d2d32, 0x2d88, 0x11d3,  0x9a, 0x16, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d)
#घोषणा HCDP_TABLE_GUID				EFI_GUID(0xf951938d, 0x620b, 0x42ef,  0x82, 0x79, 0xa8, 0x4b, 0x79, 0x61, 0x78, 0x98)
#घोषणा UGA_IO_PROTOCOL_GUID			EFI_GUID(0x61a4d49e, 0x6f68, 0x4f1b,  0xb9, 0x22, 0xa8, 0x6e, 0xed, 0x0b, 0x07, 0xa2)
#घोषणा EFI_GLOBAL_VARIABLE_GUID		EFI_GUID(0x8be4df61, 0x93ca, 0x11d2,  0xaa, 0x0d, 0x00, 0xe0, 0x98, 0x03, 0x2b, 0x8c)
#घोषणा UV_SYSTEM_TABLE_GUID			EFI_GUID(0x3b13a7d4, 0x633e, 0x11dd,  0x93, 0xec, 0xda, 0x25, 0x56, 0xd8, 0x95, 0x93)
#घोषणा LINUX_EFI_CRASH_GUID			EFI_GUID(0xcfc8fc79, 0xbe2e, 0x4ddc,  0x97, 0xf0, 0x9f, 0x98, 0xbf, 0xe2, 0x98, 0xa0)
#घोषणा LOADED_IMAGE_PROTOCOL_GUID		EFI_GUID(0x5b1b31a1, 0x9562, 0x11d2,  0x8e, 0x3f, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b)
#घोषणा EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID	EFI_GUID(0x9042a9de, 0x23dc, 0x4a38,  0x96, 0xfb, 0x7a, 0xde, 0xd0, 0x80, 0x51, 0x6a)
#घोषणा EFI_UGA_PROTOCOL_GUID			EFI_GUID(0x982c298b, 0xf4fa, 0x41cb,  0xb8, 0x38, 0x77, 0xaa, 0x68, 0x8f, 0xb8, 0x39)
#घोषणा EFI_PCI_IO_PROTOCOL_GUID		EFI_GUID(0x4cf5b200, 0x68b8, 0x4ca5,  0x9e, 0xec, 0xb2, 0x3e, 0x3f, 0x50, 0x02, 0x9a)
#घोषणा EFI_खाता_INFO_ID			EFI_GUID(0x09576e92, 0x6d3f, 0x11d2,  0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b)
#घोषणा EFI_SYSTEM_RESOURCE_TABLE_GUID		EFI_GUID(0xb122a263, 0x3661, 0x4f68,  0x99, 0x29, 0x78, 0xf8, 0xb0, 0xd6, 0x21, 0x80)
#घोषणा EFI_खाता_SYSTEM_GUID			EFI_GUID(0x964e5b22, 0x6459, 0x11d2,  0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b)
#घोषणा DEVICE_TREE_GUID			EFI_GUID(0xb1b621d5, 0xf19c, 0x41a5,  0x83, 0x0b, 0xd9, 0x15, 0x2c, 0x69, 0xaa, 0xe0)
#घोषणा EFI_PROPERTIES_TABLE_GUID		EFI_GUID(0x880aaca3, 0x4adc, 0x4a04,  0x90, 0x79, 0xb7, 0x47, 0x34, 0x08, 0x25, 0xe5)
#घोषणा EFI_RNG_PROTOCOL_GUID			EFI_GUID(0x3152bca5, 0xeade, 0x433d,  0x86, 0x2e, 0xc0, 0x1c, 0xdc, 0x29, 0x1f, 0x44)
#घोषणा EFI_RNG_ALGORITHM_RAW			EFI_GUID(0xe43176d7, 0xb6e8, 0x4827,  0xb7, 0x84, 0x7f, 0xfd, 0xc4, 0xb6, 0x85, 0x61)
#घोषणा EFI_MEMORY_ATTRIBUTES_TABLE_GUID	EFI_GUID(0xdcfa911d, 0x26eb, 0x469f,  0xa2, 0x20, 0x38, 0xb7, 0xdc, 0x46, 0x12, 0x20)
#घोषणा EFI_CONSOLE_OUT_DEVICE_GUID		EFI_GUID(0xd3b36f2c, 0xd551, 0x11d4,  0x9a, 0x46, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d)
#घोषणा APPLE_PROPERTIES_PROTOCOL_GUID		EFI_GUID(0x91bd12fe, 0xf6c3, 0x44fb,  0xa5, 0xb7, 0x51, 0x22, 0xab, 0x30, 0x3a, 0xe0)
#घोषणा EFI_TCG2_PROTOCOL_GUID			EFI_GUID(0x607f766c, 0x7455, 0x42be,  0x93, 0x0b, 0xe4, 0xd7, 0x6d, 0xb2, 0x72, 0x0f)
#घोषणा EFI_LOAD_खाता_PROTOCOL_GUID		EFI_GUID(0x56ec3091, 0x954c, 0x11d2,  0x8e, 0x3f, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b)
#घोषणा EFI_LOAD_खाता2_PROTOCOL_GUID		EFI_GUID(0x4006c0c1, 0xfcb3, 0x403e,  0x99, 0x6d, 0x4a, 0x6c, 0x87, 0x24, 0xe0, 0x6d)
#घोषणा EFI_RT_PROPERTIES_TABLE_GUID		EFI_GUID(0xeb66918a, 0x7eef, 0x402a,  0x84, 0x2e, 0x93, 0x1d, 0x21, 0xc3, 0x8a, 0xe9)

#घोषणा EFI_IMAGE_SECURITY_DATABASE_GUID	EFI_GUID(0xd719b2cb, 0x3d3a, 0x4596,  0xa3, 0xbc, 0xda, 0xd0, 0x0e, 0x67, 0x65, 0x6f)
#घोषणा EFI_SHIM_LOCK_GUID			EFI_GUID(0x605dab50, 0xe046, 0x4300,  0xab, 0xb6, 0x3d, 0xd8, 0x10, 0xdd, 0x8b, 0x23)

#घोषणा EFI_CERT_SHA256_GUID			EFI_GUID(0xc1c41626, 0x504c, 0x4092, 0xac, 0xa9, 0x41, 0xf9, 0x36, 0x93, 0x43, 0x28)
#घोषणा EFI_CERT_X509_GUID			EFI_GUID(0xa5c059a1, 0x94e4, 0x4aa7, 0x87, 0xb5, 0xab, 0x15, 0x5c, 0x2b, 0xf0, 0x72)
#घोषणा EFI_CERT_X509_SHA256_GUID		EFI_GUID(0x3bd2a492, 0x96c0, 0x4079, 0xb4, 0x20, 0xfc, 0xf9, 0x8e, 0xf1, 0x03, 0xed)

/*
 * This GUID is used to pass to the kernel proper the काष्ठा screen_info
 * काष्ठाure that was populated by the stub based on the GOP protocol instance
 * associated with ConOut
 */
#घोषणा LINUX_EFI_ARM_SCREEN_INFO_TABLE_GUID	EFI_GUID(0xe03fc20a, 0x85dc, 0x406e,  0xb9, 0x0e, 0x4a, 0xb5, 0x02, 0x37, 0x1d, 0x95)
#घोषणा LINUX_EFI_ARM_CPU_STATE_TABLE_GUID	EFI_GUID(0xef79e4aa, 0x3c3d, 0x4989,  0xb9, 0x02, 0x07, 0xa9, 0x43, 0xe5, 0x50, 0xd2)
#घोषणा LINUX_EFI_LOADER_ENTRY_GUID		EFI_GUID(0x4a67b082, 0x0a4c, 0x41cf,  0xb6, 0xc7, 0x44, 0x0b, 0x29, 0xbb, 0x8c, 0x4f)
#घोषणा LINUX_EFI_RANDOM_SEED_TABLE_GUID	EFI_GUID(0x1ce1e5bc, 0x7ceb, 0x42f2,  0x81, 0xe5, 0x8a, 0xad, 0xf1, 0x80, 0xf5, 0x7b)
#घोषणा LINUX_EFI_TPM_EVENT_LOG_GUID		EFI_GUID(0xb7799cb0, 0xeca2, 0x4943,  0x96, 0x67, 0x1f, 0xae, 0x07, 0xb7, 0x47, 0xfa)
#घोषणा LINUX_EFI_TPM_FINAL_LOG_GUID		EFI_GUID(0x1e2ed096, 0x30e2, 0x4254,  0xbd, 0x89, 0x86, 0x3b, 0xbe, 0xf8, 0x23, 0x25)
#घोषणा LINUX_EFI_MEMRESERVE_TABLE_GUID		EFI_GUID(0x888eb0c6, 0x8ede, 0x4ff5,  0xa8, 0xf0, 0x9a, 0xee, 0x5c, 0xb9, 0x77, 0xc2)
#घोषणा LINUX_EFI_INITRD_MEDIA_GUID		EFI_GUID(0x5568e427, 0x68fc, 0x4f3d,  0xac, 0x74, 0xca, 0x55, 0x52, 0x31, 0xcc, 0x68)
#घोषणा LINUX_EFI_MOK_VARIABLE_TABLE_GUID	EFI_GUID(0xc451ed2b, 0x9694, 0x45d3,  0xba, 0xba, 0xed, 0x9f, 0x89, 0x88, 0xa3, 0x89)

/* OEM GUIDs */
#घोषणा DELLEMC_EFI_RCI2_TABLE_GUID		EFI_GUID(0x2d9f28a2, 0xa886, 0x456a,  0x97, 0xa8, 0xf1, 0x1e, 0xf2, 0x4f, 0xf4, 0x55)

प्रकार काष्ठा अणु
	efi_guid_t guid;
	u64 table;
पूर्ण efi_config_table_64_t;

प्रकार काष्ठा अणु
	efi_guid_t guid;
	u32 table;
पूर्ण efi_config_table_32_t;

प्रकार जोड़ अणु
	काष्ठा अणु
		efi_guid_t guid;
		व्योम *table;
	पूर्ण;
	efi_config_table_32_t mixed_mode;
पूर्ण efi_config_table_t;

प्रकार काष्ठा अणु
	efi_guid_t guid;
	अचिन्हित दीर्घ *ptr;
	स्थिर अक्षर name[16];
पूर्ण efi_config_table_type_t;

#घोषणा EFI_SYSTEM_TABLE_SIGNATURE ((u64)0x5453595320494249ULL)

#घोषणा EFI_2_30_SYSTEM_TABLE_REVISION  ((2 << 16) | (30))
#घोषणा EFI_2_20_SYSTEM_TABLE_REVISION  ((2 << 16) | (20))
#घोषणा EFI_2_10_SYSTEM_TABLE_REVISION  ((2 << 16) | (10))
#घोषणा EFI_2_00_SYSTEM_TABLE_REVISION  ((2 << 16) | (00))
#घोषणा EFI_1_10_SYSTEM_TABLE_REVISION  ((1 << 16) | (10))
#घोषणा EFI_1_02_SYSTEM_TABLE_REVISION  ((1 << 16) | (02))

प्रकार काष्ठा अणु
	efi_table_hdr_t hdr;
	u64 fw_venकरोr;	/* physical addr of CHAR16 venकरोr string */
	u32 fw_revision;
	u32 __pad1;
	u64 con_in_handle;
	u64 con_in;
	u64 con_out_handle;
	u64 con_out;
	u64 मानक_त्रुटि_handle;
	u64 मानक_त्रुटि;
	u64 runसमय;
	u64 bootसमय;
	u32 nr_tables;
	u32 __pad2;
	u64 tables;
पूर्ण efi_प्रणाली_table_64_t;

प्रकार काष्ठा अणु
	efi_table_hdr_t hdr;
	u32 fw_venकरोr;	/* physical addr of CHAR16 venकरोr string */
	u32 fw_revision;
	u32 con_in_handle;
	u32 con_in;
	u32 con_out_handle;
	u32 con_out;
	u32 मानक_त्रुटि_handle;
	u32 मानक_त्रुटि;
	u32 runसमय;
	u32 bootसमय;
	u32 nr_tables;
	u32 tables;
पूर्ण efi_प्रणाली_table_32_t;

प्रकार जोड़ efi_simple_text_input_protocol efi_simple_text_input_protocol_t;
प्रकार जोड़ efi_simple_text_output_protocol efi_simple_text_output_protocol_t;

प्रकार जोड़ अणु
	काष्ठा अणु
		efi_table_hdr_t hdr;
		अचिन्हित दीर्घ fw_venकरोr;	/* physical addr of CHAR16 venकरोr string */
		u32 fw_revision;
		अचिन्हित दीर्घ con_in_handle;
		efi_simple_text_input_protocol_t *con_in;
		अचिन्हित दीर्घ con_out_handle;
		efi_simple_text_output_protocol_t *con_out;
		अचिन्हित दीर्घ मानक_त्रुटि_handle;
		अचिन्हित दीर्घ मानक_त्रुटि;
		efi_runसमय_services_t *runसमय;
		efi_boot_services_t *bootसमय;
		अचिन्हित दीर्घ nr_tables;
		अचिन्हित दीर्घ tables;
	पूर्ण;
	efi_प्रणाली_table_32_t mixed_mode;
पूर्ण efi_प्रणाली_table_t;

/*
 * Architecture independent काष्ठाure क्रम describing a memory map क्रम the
 * benefit of efi_memmap_init_early(), and क्रम passing context between
 * efi_memmap_alloc() and efi_memmap_install().
 */
काष्ठा efi_memory_map_data अणु
	phys_addr_t phys_map;
	अचिन्हित दीर्घ size;
	अचिन्हित दीर्घ desc_version;
	अचिन्हित दीर्घ desc_size;
	अचिन्हित दीर्घ flags;
पूर्ण;

काष्ठा efi_memory_map अणु
	phys_addr_t phys_map;
	व्योम *map;
	व्योम *map_end;
	पूर्णांक nr_map;
	अचिन्हित दीर्घ desc_version;
	अचिन्हित दीर्घ desc_size;
#घोषणा EFI_MEMMAP_LATE (1UL << 0)
#घोषणा EFI_MEMMAP_MEMBLOCK (1UL << 1)
#घोषणा EFI_MEMMAP_SLAB (1UL << 2)
	अचिन्हित दीर्घ flags;
पूर्ण;

काष्ठा efi_mem_range अणु
	काष्ठा range range;
	u64 attribute;
पूर्ण;

प्रकार काष्ठा अणु
	u32 version;
	u32 length;
	u64 memory_protection_attribute;
पूर्ण efi_properties_table_t;

#घोषणा EFI_PROPERTIES_TABLE_VERSION	0x00010000
#घोषणा EFI_PROPERTIES_RUNTIME_MEMORY_PROTECTION_NON_EXECUTABLE_PE_DATA	0x1

प्रकार काष्ठा अणु
	u16 version;
	u16 length;
	u32 runसमय_services_supported;
पूर्ण efi_rt_properties_table_t;

#घोषणा EFI_RT_PROPERTIES_TABLE_VERSION	0x1

#घोषणा EFI_INVALID_TABLE_ADDR		(~0UL)

प्रकार काष्ठा अणु
	u32 version;
	u32 num_entries;
	u32 desc_size;
	u32 reserved;
	efi_memory_desc_t entry[0];
पूर्ण efi_memory_attributes_table_t;

प्रकार काष्ठा अणु
	efi_guid_t signature_owner;
	u8 signature_data[];
पूर्ण efi_signature_data_t;

प्रकार काष्ठा अणु
	efi_guid_t signature_type;
	u32 signature_list_size;
	u32 signature_header_size;
	u32 signature_size;
	u8 signature_header[];
	/* efi_signature_data_t signatures[][] */
पूर्ण efi_signature_list_t;

प्रकार u8 efi_sha256_hash_t[32];

प्रकार काष्ठा अणु
	efi_sha256_hash_t to_be_चिन्हित_hash;
	efi_समय_प्रकार समय_of_revocation;
पूर्ण efi_cert_x509_sha256_t;

बाह्य अचिन्हित दीर्घ __ro_after_init efi_rng_seed;		/* RNG Seed table */

/*
 * All runसमय access to EFI goes through this काष्ठाure:
 */
बाह्य काष्ठा efi अणु
	स्थिर efi_runसमय_services_t	*runसमय;		/* EFI runसमय services table */
	अचिन्हित पूर्णांक			runसमय_version;	/* Runसमय services version */
	अचिन्हित पूर्णांक			runसमय_supported_mask;

	अचिन्हित दीर्घ			acpi;			/* ACPI table  (IA64 ext 0.71) */
	अचिन्हित दीर्घ			acpi20;			/* ACPI table  (ACPI 2.0) */
	अचिन्हित दीर्घ			smbios;			/* SMBIOS table (32 bit entry poपूर्णांक) */
	अचिन्हित दीर्घ			smbios3;		/* SMBIOS table (64 bit entry poपूर्णांक) */
	अचिन्हित दीर्घ			esrt;			/* ESRT table */
	अचिन्हित दीर्घ			tpm_log;		/* TPM2 Event Log table */
	अचिन्हित दीर्घ			tpm_final_log;		/* TPM2 Final Events Log table */
	अचिन्हित दीर्घ			mokvar_table;		/* MOK variable config table */

	efi_get_समय_प्रकार			*get_समय;
	efi_set_समय_प्रकार			*set_समय;
	efi_get_wakeup_समय_प्रकार		*get_wakeup_समय;
	efi_set_wakeup_समय_प्रकार		*set_wakeup_समय;
	efi_get_variable_t		*get_variable;
	efi_get_next_variable_t		*get_next_variable;
	efi_set_variable_t		*set_variable;
	efi_set_variable_t		*set_variable_nonblocking;
	efi_query_variable_info_t	*query_variable_info;
	efi_query_variable_info_t	*query_variable_info_nonblocking;
	efi_update_capsule_t		*update_capsule;
	efi_query_capsule_caps_t	*query_capsule_caps;
	efi_get_next_high_mono_count_t	*get_next_high_mono_count;
	efi_reset_प्रणाली_t		*reset_प्रणाली;

	काष्ठा efi_memory_map		memmap;
	अचिन्हित दीर्घ			flags;
पूर्ण efi;

#घोषणा EFI_RT_SUPPORTED_GET_TIME 				0x0001
#घोषणा EFI_RT_SUPPORTED_SET_TIME 				0x0002
#घोषणा EFI_RT_SUPPORTED_GET_WAKEUP_TIME			0x0004
#घोषणा EFI_RT_SUPPORTED_SET_WAKEUP_TIME			0x0008
#घोषणा EFI_RT_SUPPORTED_GET_VARIABLE				0x0010
#घोषणा EFI_RT_SUPPORTED_GET_NEXT_VARIABLE_NAME			0x0020
#घोषणा EFI_RT_SUPPORTED_SET_VARIABLE				0x0040
#घोषणा EFI_RT_SUPPORTED_SET_VIRTUAL_ADDRESS_MAP		0x0080
#घोषणा EFI_RT_SUPPORTED_CONVERT_POINTER			0x0100
#घोषणा EFI_RT_SUPPORTED_GET_NEXT_HIGH_MONOTONIC_COUNT		0x0200
#घोषणा EFI_RT_SUPPORTED_RESET_SYSTEM				0x0400
#घोषणा EFI_RT_SUPPORTED_UPDATE_CAPSULE				0x0800
#घोषणा EFI_RT_SUPPORTED_QUERY_CAPSULE_CAPABILITIES		0x1000
#घोषणा EFI_RT_SUPPORTED_QUERY_VARIABLE_INFO			0x2000

#घोषणा EFI_RT_SUPPORTED_ALL					0x3fff

#घोषणा EFI_RT_SUPPORTED_TIME_SERVICES				0x000f
#घोषणा EFI_RT_SUPPORTED_VARIABLE_SERVICES			0x0070

बाह्य काष्ठा mm_काष्ठा efi_mm;

अटल अंतरभूत पूर्णांक
efi_guidcmp (efi_guid_t left, efi_guid_t right)
अणु
	वापस स_भेद(&left, &right, माप (efi_guid_t));
पूर्ण

अटल अंतरभूत अक्षर *
efi_guid_to_str(efi_guid_t *guid, अक्षर *out)
अणु
	प्र_लिखो(out, "%pUl", guid->b);
        वापस out;
पूर्ण

बाह्य व्योम efi_init (व्योम);
#अगर_घोषित CONFIG_EFI
बाह्य व्योम efi_enter_भव_mode (व्योम);	/* चयन EFI to भव mode, अगर possible */
#अन्यथा
अटल अंतरभूत व्योम efi_enter_भव_mode (व्योम) अणुपूर्ण
#पूर्ण_अगर
#अगर_घोषित CONFIG_X86
बाह्य efi_status_t efi_query_variable_store(u32 attributes,
					     अचिन्हित दीर्घ size,
					     bool nonblocking);
#अन्यथा

अटल अंतरभूत efi_status_t efi_query_variable_store(u32 attributes,
						    अचिन्हित दीर्घ size,
						    bool nonblocking)
अणु
	वापस EFI_SUCCESS;
पूर्ण
#पूर्ण_अगर
बाह्य व्योम __iomem *efi_lookup_mapped_addr(u64 phys_addr);

बाह्य पूर्णांक __init efi_memmap_alloc(अचिन्हित पूर्णांक num_entries,
				   काष्ठा efi_memory_map_data *data);
बाह्य व्योम __efi_memmap_मुक्त(u64 phys, अचिन्हित दीर्घ size,
			      अचिन्हित दीर्घ flags);
बाह्य पूर्णांक __init efi_memmap_init_early(काष्ठा efi_memory_map_data *data);
बाह्य पूर्णांक __init efi_memmap_init_late(phys_addr_t addr, अचिन्हित दीर्घ size);
बाह्य व्योम __init efi_memmap_unmap(व्योम);
बाह्य पूर्णांक __init efi_memmap_install(काष्ठा efi_memory_map_data *data);
बाह्य पूर्णांक __init efi_memmap_split_count(efi_memory_desc_t *md,
					 काष्ठा range *range);
बाह्य व्योम __init efi_memmap_insert(काष्ठा efi_memory_map *old_memmap,
				     व्योम *buf, काष्ठा efi_mem_range *mem);

#अगर_घोषित CONFIG_EFI_ESRT
बाह्य व्योम __init efi_esrt_init(व्योम);
#अन्यथा
अटल अंतरभूत व्योम efi_esrt_init(व्योम) अणु पूर्ण
#पूर्ण_अगर
बाह्य पूर्णांक efi_config_parse_tables(स्थिर efi_config_table_t *config_tables,
				   पूर्णांक count,
				   स्थिर efi_config_table_type_t *arch_tables);
बाह्य पूर्णांक efi_systab_check_header(स्थिर efi_table_hdr_t *systab_hdr,
				   पूर्णांक min_major_version);
बाह्य व्योम efi_systab_report_header(स्थिर efi_table_hdr_t *systab_hdr,
				     अचिन्हित दीर्घ fw_venकरोr);
बाह्य u64 efi_get_iobase (व्योम);
बाह्य पूर्णांक efi_mem_type(अचिन्हित दीर्घ phys_addr);
बाह्य u64 efi_mem_attributes (अचिन्हित दीर्घ phys_addr);
बाह्य u64 efi_mem_attribute (अचिन्हित दीर्घ phys_addr, अचिन्हित दीर्घ size);
बाह्य पूर्णांक __init efi_uart_console_only (व्योम);
बाह्य u64 efi_mem_desc_end(efi_memory_desc_t *md);
बाह्य पूर्णांक efi_mem_desc_lookup(u64 phys_addr, efi_memory_desc_t *out_md);
बाह्य व्योम efi_mem_reserve(phys_addr_t addr, u64 size);
बाह्य पूर्णांक efi_mem_reserve_persistent(phys_addr_t addr, u64 size);
बाह्य व्योम efi_initialize_iomem_resources(काष्ठा resource *code_resource,
		काष्ठा resource *data_resource, काष्ठा resource *bss_resource);
बाह्य u64 efi_get_fdt_params(काष्ठा efi_memory_map_data *data);
बाह्य काष्ठा kobject *efi_kobj;

बाह्य पूर्णांक efi_reboot_quirk_mode;
बाह्य bool efi_घातeroff_required(व्योम);

#अगर_घोषित CONFIG_EFI_FAKE_MEMMAP
बाह्य व्योम __init efi_fake_memmap(व्योम);
#अन्यथा
अटल अंतरभूत व्योम efi_fake_memmap(व्योम) अणु पूर्ण
#पूर्ण_अगर

बाह्य अचिन्हित दीर्घ efi_mem_attr_table;

/*
 * efi_memattr_perm_setter - arch specअगरic callback function passed पूर्णांकo
 *                           efi_memattr_apply_permissions() that updates the
 *                           mapping permissions described by the second
 *                           argument in the page tables referred to by the
 *                           first argument.
 */
प्रकार पूर्णांक (*efi_memattr_perm_setter)(काष्ठा mm_काष्ठा *, efi_memory_desc_t *);

बाह्य पूर्णांक efi_memattr_init(व्योम);
बाह्य पूर्णांक efi_memattr_apply_permissions(काष्ठा mm_काष्ठा *mm,
					 efi_memattr_perm_setter fn);

/*
 * efi_early_memdesc_ptr - get the n-th EFI memmap descriptor
 * @map: the start of efi memmap
 * @desc_size: the size of space क्रम each EFI memmap descriptor
 * @n: the index of efi memmap descriptor
 *
 * EFI boot service provides the GetMemoryMap() function to get a copy of the
 * current memory map which is an array of memory descriptors, each of
 * which describes a contiguous block of memory. It also माला_लो the size of the
 * map, and the size of each descriptor, etc.
 *
 * Note that per section 6.2 of UEFI Spec 2.6 Errata A, the वापसed size of
 * each descriptor might not be equal to माप(efi_memory_memdesc_t),
 * since efi_memory_memdesc_t may be extended in the future. Thus the OS
 * MUST use the वापसed size of the descriptor to find the start of each
 * efi_memory_memdesc_t in the memory map array. This should only be used
 * during bootup since क्रम_each_efi_memory_desc_xxx() is available after the
 * kernel initializes the EFI subप्रणाली to set up काष्ठा efi_memory_map.
 */
#घोषणा efi_early_memdesc_ptr(map, desc_size, n)			\
	(efi_memory_desc_t *)((व्योम *)(map) + ((n) * (desc_size)))

/* Iterate through an efi_memory_map */
#घोषणा क्रम_each_efi_memory_desc_in_map(m, md)				   \
	क्रम ((md) = (m)->map;						   \
	     (md) && ((व्योम *)(md) + (m)->desc_size) <= (m)->map_end;	   \
	     (md) = (व्योम *)(md) + (m)->desc_size)

/**
 * क्रम_each_efi_memory_desc - iterate over descriptors in efi.memmap
 * @md: the efi_memory_desc_t * iterator
 *
 * Once the loop finishes @md must not be accessed.
 */
#घोषणा क्रम_each_efi_memory_desc(md) \
	क्रम_each_efi_memory_desc_in_map(&efi.memmap, md)

/*
 * Format an EFI memory descriptor's type and attributes to a user-provided
 * अक्षरacter buffer, as per snम_लिखो(), and वापस the buffer.
 */
अक्षर * __init efi_md_typeattr_क्रमmat(अक्षर *buf, माप_प्रकार size,
				     स्थिर efi_memory_desc_t *md);


प्रकार व्योम (*efi_element_handler_t)(स्थिर अक्षर *source,
				      स्थिर व्योम *element_data,
				      माप_प्रकार element_size);
बाह्य पूर्णांक __init parse_efi_signature_list(
	स्थिर अक्षर *source,
	स्थिर व्योम *data, माप_प्रकार size,
	efi_element_handler_t (*get_handler_क्रम_guid)(स्थिर efi_guid_t *));

/**
 * efi_range_is_wc - check the WC bit on an address range
 * @start: starting kvirt address
 * @len: length of range
 *
 * Consult the EFI memory map and make sure it's ok to set this range WC.
 * Returns true or false.
 */
अटल अंतरभूत पूर्णांक efi_range_is_wc(अचिन्हित दीर्घ start, अचिन्हित दीर्घ len)
अणु
	अचिन्हित दीर्घ i;

	क्रम (i = 0; i < len; i += (1UL << EFI_PAGE_SHIFT)) अणु
		अचिन्हित दीर्घ paddr = __pa(start + i);
		अगर (!(efi_mem_attributes(paddr) & EFI_MEMORY_WC))
			वापस 0;
	पूर्ण
	/* The range checked out */
	वापस 1;
पूर्ण

#अगर_घोषित CONFIG_EFI_PCDP
बाह्य पूर्णांक __init efi_setup_pcdp_console(अक्षर *);
#पूर्ण_अगर

/*
 * We play games with efi_enabled so that the compiler will, अगर
 * possible, हटाओ EFI-related code altogether.
 */
#घोषणा EFI_BOOT		0	/* Were we booted from EFI? */
#घोषणा EFI_CONFIG_TABLES	2	/* Can we use EFI config tables? */
#घोषणा EFI_RUNTIME_SERVICES	3	/* Can we use runसमय services? */
#घोषणा EFI_MEMMAP		4	/* Can we use EFI memory map? */
#घोषणा EFI_64BIT		5	/* Is the firmware 64-bit? */
#घोषणा EFI_PARAVIRT		6	/* Access is via a paravirt पूर्णांकerface */
#घोषणा EFI_ARCH_1		7	/* First arch-specअगरic bit */
#घोषणा EFI_DBG			8	/* Prपूर्णांक additional debug info at runसमय */
#घोषणा EFI_NX_PE_DATA		9	/* Can runसमय data regions be mapped non-executable? */
#घोषणा EFI_MEM_ATTR		10	/* Did firmware publish an EFI_MEMORY_ATTRIBUTES table? */
#घोषणा EFI_MEM_NO_SOFT_RESERVE	11	/* Is the kernel configured to ignore soft reservations? */
#घोषणा EFI_PRESERVE_BS_REGIONS	12	/* Are EFI boot-services memory segments available? */

#अगर_घोषित CONFIG_EFI
/*
 * Test whether the above EFI_* bits are enabled.
 */
अटल अंतरभूत bool efi_enabled(पूर्णांक feature)
अणु
	वापस test_bit(feature, &efi.flags) != 0;
पूर्ण
बाह्य व्योम efi_reboot(क्रमागत reboot_mode reboot_mode, स्थिर अक्षर *__unused);

bool __pure __efi_soft_reserve_enabled(व्योम);

अटल अंतरभूत bool __pure efi_soft_reserve_enabled(व्योम)
अणु
	वापस IS_ENABLED(CONFIG_EFI_SOFT_RESERVE)
		&& __efi_soft_reserve_enabled();
पूर्ण

अटल अंतरभूत bool efi_rt_services_supported(अचिन्हित पूर्णांक mask)
अणु
	वापस (efi.runसमय_supported_mask & mask) == mask;
पूर्ण
#अन्यथा
अटल अंतरभूत bool efi_enabled(पूर्णांक feature)
अणु
	वापस false;
पूर्ण
अटल अंतरभूत व्योम
efi_reboot(क्रमागत reboot_mode reboot_mode, स्थिर अक्षर *__unused) अणुपूर्ण

अटल अंतरभूत bool efi_soft_reserve_enabled(व्योम)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool efi_rt_services_supported(अचिन्हित पूर्णांक mask)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

बाह्य पूर्णांक efi_status_to_err(efi_status_t status);

/*
 * Variable Attributes
 */
#घोषणा EFI_VARIABLE_NON_VOLATILE       0x0000000000000001
#घोषणा EFI_VARIABLE_BOOTSERVICE_ACCESS 0x0000000000000002
#घोषणा EFI_VARIABLE_RUNTIME_ACCESS     0x0000000000000004
#घोषणा EFI_VARIABLE_HARDWARE_ERROR_RECORD 0x0000000000000008
#घोषणा EFI_VARIABLE_AUTHENTICATED_WRITE_ACCESS 0x0000000000000010
#घोषणा EFI_VARIABLE_TIME_BASED_AUTHENTICATED_WRITE_ACCESS 0x0000000000000020
#घोषणा EFI_VARIABLE_APPEND_WRITE	0x0000000000000040

#घोषणा EFI_VARIABLE_MASK 	(EFI_VARIABLE_NON_VOLATILE | \
				EFI_VARIABLE_BOOTSERVICE_ACCESS | \
				EFI_VARIABLE_RUNTIME_ACCESS | \
				EFI_VARIABLE_HARDWARE_ERROR_RECORD | \
				EFI_VARIABLE_AUTHENTICATED_WRITE_ACCESS | \
				EFI_VARIABLE_TIME_BASED_AUTHENTICATED_WRITE_ACCESS | \
				EFI_VARIABLE_APPEND_WRITE)
/*
 * Length of a GUID string (म_माप("aaaaaaaa-bbbb-cccc-dddd-eeeeeeeeeeee"))
 * not including trailing NUL
 */
#घोषणा EFI_VARIABLE_GUID_LEN	UUID_STRING_LEN

/*
 * EFI Device Path inक्रमmation
 */
#घोषणा EFI_DEV_HW			0x01
#घोषणा  EFI_DEV_PCI				 1
#घोषणा  EFI_DEV_PCCARD				 2
#घोषणा  EFI_DEV_MEM_MAPPED			 3
#घोषणा  EFI_DEV_VENDOR				 4
#घोषणा  EFI_DEV_CONTROLLER			 5
#घोषणा EFI_DEV_ACPI			0x02
#घोषणा   EFI_DEV_BASIC_ACPI			 1
#घोषणा   EFI_DEV_EXPANDED_ACPI			 2
#घोषणा EFI_DEV_MSG			0x03
#घोषणा   EFI_DEV_MSG_ATAPI			 1
#घोषणा   EFI_DEV_MSG_SCSI			 2
#घोषणा   EFI_DEV_MSG_FC			 3
#घोषणा   EFI_DEV_MSG_1394			 4
#घोषणा   EFI_DEV_MSG_USB			 5
#घोषणा   EFI_DEV_MSG_USB_CLASS			15
#घोषणा   EFI_DEV_MSG_I20			 6
#घोषणा   EFI_DEV_MSG_MAC			11
#घोषणा   EFI_DEV_MSG_IPV4			12
#घोषणा   EFI_DEV_MSG_IPV6			13
#घोषणा   EFI_DEV_MSG_INFINIBAND		 9
#घोषणा   EFI_DEV_MSG_UART			14
#घोषणा   EFI_DEV_MSG_VENDOR			10
#घोषणा EFI_DEV_MEDIA			0x04
#घोषणा   EFI_DEV_MEDIA_HARD_DRIVE		 1
#घोषणा   EFI_DEV_MEDIA_CDROM			 2
#घोषणा   EFI_DEV_MEDIA_VENDOR			 3
#घोषणा   EFI_DEV_MEDIA_खाता			 4
#घोषणा   EFI_DEV_MEDIA_PROTOCOL		 5
#घोषणा EFI_DEV_BIOS_BOOT		0x05
#घोषणा EFI_DEV_END_PATH		0x7F
#घोषणा EFI_DEV_END_PATH2		0xFF
#घोषणा   EFI_DEV_END_INSTANCE			0x01
#घोषणा   EFI_DEV_END_ENTIRE			0xFF

काष्ठा efi_generic_dev_path अणु
	u8				type;
	u8				sub_type;
	u16				length;
पूर्ण __packed;

काष्ठा efi_acpi_dev_path अणु
	काष्ठा efi_generic_dev_path	header;
	u32				hid;
	u32				uid;
पूर्ण __packed;

काष्ठा efi_pci_dev_path अणु
	काष्ठा efi_generic_dev_path	header;
	u8				fn;
	u8				dev;
पूर्ण __packed;

काष्ठा efi_venकरोr_dev_path अणु
	काष्ठा efi_generic_dev_path	header;
	efi_guid_t			venकरोrguid;
	u8				venकरोrdata[];
पूर्ण __packed;

काष्ठा efi_dev_path अणु
	जोड़ अणु
		काष्ठा efi_generic_dev_path	header;
		काष्ठा efi_acpi_dev_path	acpi;
		काष्ठा efi_pci_dev_path		pci;
		काष्ठा efi_venकरोr_dev_path	venकरोr;
	पूर्ण;
पूर्ण __packed;

काष्ठा device *efi_get_device_by_path(स्थिर काष्ठा efi_dev_path **node,
				      माप_प्रकार *len);

अटल अंतरभूत व्योम memrange_efi_to_native(u64 *addr, u64 *npages)
अणु
	*npages = PFN_UP(*addr + (*npages<<EFI_PAGE_SHIFT)) - PFN_DOWN(*addr);
	*addr &= PAGE_MASK;
पूर्ण

/*
 * EFI Variable support.
 *
 * Dअगरferent firmware drivers can expose their EFI-like variables using
 * the following.
 */

काष्ठा efivar_operations अणु
	efi_get_variable_t *get_variable;
	efi_get_next_variable_t *get_next_variable;
	efi_set_variable_t *set_variable;
	efi_set_variable_t *set_variable_nonblocking;
	efi_query_variable_store_t *query_variable_store;
पूर्ण;

काष्ठा efivars अणु
	काष्ठा kset *kset;
	काष्ठा kobject *kobject;
	स्थिर काष्ठा efivar_operations *ops;
पूर्ण;

/*
 * The maximum size of VariableName + Data = 1024
 * Thereक्रमe, it's reasonable to save that much
 * space in each part of the काष्ठाure,
 * and we use a page क्रम पढ़ोing/writing.
 */

#घोषणा EFI_VAR_NAME_LEN	1024

काष्ठा efi_variable अणु
	efi_अक्षर16_t  VariableName[EFI_VAR_NAME_LEN/माप(efi_अक्षर16_t)];
	efi_guid_t    VenकरोrGuid;
	अचिन्हित दीर्घ DataSize;
	__u8          Data[1024];
	efi_status_t  Status;
	__u32         Attributes;
पूर्ण __attribute__((packed));

काष्ठा efivar_entry अणु
	काष्ठा efi_variable var;
	काष्ठा list_head list;
	काष्ठा kobject kobj;
	bool scanning;
	bool deleting;
पूर्ण;

अटल अंतरभूत व्योम
efivar_unरेजिस्टर(काष्ठा efivar_entry *var)
अणु
	kobject_put(&var->kobj);
पूर्ण

पूर्णांक efivars_रेजिस्टर(काष्ठा efivars *efivars,
		     स्थिर काष्ठा efivar_operations *ops,
		     काष्ठा kobject *kobject);
पूर्णांक efivars_unरेजिस्टर(काष्ठा efivars *efivars);
काष्ठा kobject *efivars_kobject(व्योम);

पूर्णांक efivar_supports_ग_लिखोs(व्योम);
पूर्णांक efivar_init(पूर्णांक (*func)(efi_अक्षर16_t *, efi_guid_t, अचिन्हित दीर्घ, व्योम *),
		व्योम *data, bool duplicates, काष्ठा list_head *head);

पूर्णांक efivar_entry_add(काष्ठा efivar_entry *entry, काष्ठा list_head *head);
पूर्णांक efivar_entry_हटाओ(काष्ठा efivar_entry *entry);

पूर्णांक __efivar_entry_delete(काष्ठा efivar_entry *entry);
पूर्णांक efivar_entry_delete(काष्ठा efivar_entry *entry);

पूर्णांक efivar_entry_size(काष्ठा efivar_entry *entry, अचिन्हित दीर्घ *size);
पूर्णांक __efivar_entry_get(काष्ठा efivar_entry *entry, u32 *attributes,
		       अचिन्हित दीर्घ *size, व्योम *data);
पूर्णांक efivar_entry_get(काष्ठा efivar_entry *entry, u32 *attributes,
		     अचिन्हित दीर्घ *size, व्योम *data);
पूर्णांक efivar_entry_set(काष्ठा efivar_entry *entry, u32 attributes,
		     अचिन्हित दीर्घ size, व्योम *data, काष्ठा list_head *head);
पूर्णांक efivar_entry_set_get_size(काष्ठा efivar_entry *entry, u32 attributes,
			      अचिन्हित दीर्घ *size, व्योम *data, bool *set);
पूर्णांक efivar_entry_set_safe(efi_अक्षर16_t *name, efi_guid_t venकरोr, u32 attributes,
			  bool block, अचिन्हित दीर्घ size, व्योम *data);

पूर्णांक efivar_entry_iter_begin(व्योम);
व्योम efivar_entry_iter_end(व्योम);

पूर्णांक __efivar_entry_iter(पूर्णांक (*func)(काष्ठा efivar_entry *, व्योम *),
			काष्ठा list_head *head, व्योम *data,
			काष्ठा efivar_entry **prev);
पूर्णांक efivar_entry_iter(पूर्णांक (*func)(काष्ठा efivar_entry *, व्योम *),
		      काष्ठा list_head *head, व्योम *data);

काष्ठा efivar_entry *efivar_entry_find(efi_अक्षर16_t *name, efi_guid_t guid,
				       काष्ठा list_head *head, bool हटाओ);

bool efivar_validate(efi_guid_t venकरोr, efi_अक्षर16_t *var_name, u8 *data,
		     अचिन्हित दीर्घ data_size);
bool efivar_variable_is_removable(efi_guid_t venकरोr, स्थिर अक्षर *name,
				  माप_प्रकार len);

#अगर IS_ENABLED(CONFIG_EFI_CAPSULE_LOADER)
बाह्य bool efi_capsule_pending(पूर्णांक *reset_type);

बाह्य पूर्णांक efi_capsule_supported(efi_guid_t guid, u32 flags,
				 माप_प्रकार size, पूर्णांक *reset);

बाह्य पूर्णांक efi_capsule_update(efi_capsule_header_t *capsule,
			      phys_addr_t *pages);
#अन्यथा
अटल अंतरभूत bool efi_capsule_pending(पूर्णांक *reset_type) अणु वापस false; पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_EFI_RUNTIME_MAP
पूर्णांक efi_runसमय_map_init(काष्ठा kobject *);
पूर्णांक efi_get_runसमय_map_size(व्योम);
पूर्णांक efi_get_runसमय_map_desc_size(व्योम);
पूर्णांक efi_runसमय_map_copy(व्योम *buf, माप_प्रकार bufsz);
#अन्यथा
अटल अंतरभूत पूर्णांक efi_runसमय_map_init(काष्ठा kobject *kobj)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक efi_get_runसमय_map_size(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक efi_get_runसमय_map_desc_size(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक efi_runसमय_map_copy(व्योम *buf, माप_प्रकार bufsz)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर

#अगर_घोषित CONFIG_EFI
बाह्य bool efi_runसमय_disabled(व्योम);
#अन्यथा
अटल अंतरभूत bool efi_runसमय_disabled(व्योम) अणु वापस true; पूर्ण
#पूर्ण_अगर

बाह्य व्योम efi_call_virt_check_flags(अचिन्हित दीर्घ flags, स्थिर अक्षर *call);
बाह्य अचिन्हित दीर्घ efi_call_virt_save_flags(व्योम);

क्रमागत efi_secureboot_mode अणु
	efi_secureboot_mode_unset,
	efi_secureboot_mode_unknown,
	efi_secureboot_mode_disabled,
	efi_secureboot_mode_enabled,
पूर्ण;

अटल अंतरभूत
क्रमागत efi_secureboot_mode efi_get_secureboot_mode(efi_get_variable_t *get_var)
अणु
	u8 secboot, setupmode = 0;
	efi_status_t status;
	अचिन्हित दीर्घ size;

	size = माप(secboot);
	status = get_var(L"SecureBoot", &EFI_GLOBAL_VARIABLE_GUID, शून्य, &size,
			 &secboot);
	अगर (status == EFI_NOT_FOUND)
		वापस efi_secureboot_mode_disabled;
	अगर (status != EFI_SUCCESS)
		वापस efi_secureboot_mode_unknown;

	size = माप(setupmode);
	get_var(L"SetupMode", &EFI_GLOBAL_VARIABLE_GUID, शून्य, &size, &setupmode);
	अगर (secboot == 0 || setupmode == 1)
		वापस efi_secureboot_mode_disabled;
	वापस efi_secureboot_mode_enabled;
पूर्ण

#अगर_घोषित CONFIG_EFI_EMBEDDED_FIRMWARE
व्योम efi_check_क्रम_embedded_firmwares(व्योम);
#अन्यथा
अटल अंतरभूत व्योम efi_check_क्रम_embedded_firmwares(व्योम) अणु पूर्ण
#पूर्ण_अगर

efi_status_t efi_अक्रमom_get_seed(व्योम);

/*
 * Arch code can implement the following three ढाँचा macros, aव्योमing
 * reptition क्रम the व्योम/non-व्योम वापस हालs of अणु__,पूर्णefi_call_virt():
 *
 *  * arch_efi_call_virt_setup()
 *
 *    Sets up the environment क्रम the call (e.g. चयनing page tables,
 *    allowing kernel-mode use of भग्नing poपूर्णांक, अगर required).
 *
 *  * arch_efi_call_virt()
 *
 *    Perक्रमms the call. The last expression in the macro must be the call
 *    itself, allowing the logic to be shared by the व्योम and non-व्योम
 *    हालs.
 *
 *  * arch_efi_call_virt_tearकरोwn()
 *
 *    Restores the usual kernel environment once the call has वापसed.
 */

#घोषणा efi_call_virt_poपूर्णांकer(p, f, args...)				\
(अणु									\
	efi_status_t __s;						\
	अचिन्हित दीर्घ __flags;						\
									\
	arch_efi_call_virt_setup();					\
									\
	__flags = efi_call_virt_save_flags();				\
	__s = arch_efi_call_virt(p, f, args);				\
	efi_call_virt_check_flags(__flags, __stringअगरy(f));		\
									\
	arch_efi_call_virt_tearकरोwn();					\
									\
	__s;								\
पूर्ण)

#घोषणा __efi_call_virt_poपूर्णांकer(p, f, args...)				\
(अणु									\
	अचिन्हित दीर्घ __flags;						\
									\
	arch_efi_call_virt_setup();					\
									\
	__flags = efi_call_virt_save_flags();				\
	arch_efi_call_virt(p, f, args);					\
	efi_call_virt_check_flags(__flags, __stringअगरy(f));		\
									\
	arch_efi_call_virt_tearकरोwn();					\
पूर्ण)

#घोषणा EFI_RANDOM_SEED_SIZE		64U

काष्ठा linux_efi_अक्रमom_seed अणु
	u32	size;
	u8	bits[];
पूर्ण;

काष्ठा linux_efi_tpm_eventlog अणु
	u32	size;
	u32	final_events_preboot_size;
	u8	version;
	u8	log[];
पूर्ण;

बाह्य पूर्णांक efi_tpm_eventlog_init(व्योम);

काष्ठा efi_tcg2_final_events_table अणु
	u64 version;
	u64 nr_events;
	u8 events[];
पूर्ण;
बाह्य पूर्णांक efi_tpm_final_log_size;

बाह्य अचिन्हित दीर्घ rci2_table_phys;

/*
 * efi_runसमय_service() function identअगरiers.
 * "NONE" is used by efi_recover_from_page_fault() to check अगर the page
 * fault happened जबतक executing an efi runसमय service.
 */
क्रमागत efi_rts_ids अणु
	EFI_NONE,
	EFI_GET_TIME,
	EFI_SET_TIME,
	EFI_GET_WAKEUP_TIME,
	EFI_SET_WAKEUP_TIME,
	EFI_GET_VARIABLE,
	EFI_GET_NEXT_VARIABLE,
	EFI_SET_VARIABLE,
	EFI_QUERY_VARIABLE_INFO,
	EFI_GET_NEXT_HIGH_MONO_COUNT,
	EFI_RESET_SYSTEM,
	EFI_UPDATE_CAPSULE,
	EFI_QUERY_CAPSULE_CAPS,
पूर्ण;

/*
 * efi_runसमय_work:	Details of EFI Runसमय Service work
 * @arg<1-5>:		EFI Runसमय Service function arguments
 * @status:		Status of executing EFI Runसमय Service
 * @efi_rts_id:		EFI Runसमय Service function identअगरier
 * @efi_rts_comp:	Struct used क्रम handling completions
 */
काष्ठा efi_runसमय_work अणु
	व्योम *arg1;
	व्योम *arg2;
	व्योम *arg3;
	व्योम *arg4;
	व्योम *arg5;
	efi_status_t status;
	काष्ठा work_काष्ठा work;
	क्रमागत efi_rts_ids efi_rts_id;
	काष्ठा completion efi_rts_comp;
पूर्ण;

बाह्य काष्ठा efi_runसमय_work efi_rts_work;

/* Workqueue to queue EFI Runसमय Services */
बाह्य काष्ठा workqueue_काष्ठा *efi_rts_wq;

काष्ठा linux_efi_memreserve अणु
	पूर्णांक		size;			// allocated size of the array
	atomic_t	count;			// number of entries used
	phys_addr_t	next;			// pa of next काष्ठा instance
	काष्ठा अणु
		phys_addr_t	base;
		phys_addr_t	size;
	पूर्ण entry[];
पूर्ण;

#घोषणा EFI_MEMRESERVE_COUNT(size) (((size) - माप(काष्ठा linux_efi_memreserve)) \
	/ माप_field(काष्ठा linux_efi_memreserve, entry[0]))

व्योम __init efi_arch_mem_reserve(phys_addr_t addr, u64 size);

अक्षर *efi_systab_show_arch(अक्षर *str);

/*
 * The LINUX_EFI_MOK_VARIABLE_TABLE_GUID config table can be provided
 * to the kernel by an EFI boot loader. The table contains a packed
 * sequence of these entries, one क्रम each named MOK variable.
 * The sequence is terminated by an entry with a completely शून्य
 * name and 0 data size.
 */
काष्ठा efi_mokvar_table_entry अणु
	अक्षर name[256];
	u64 data_size;
	u8 data[];
पूर्ण __attribute((packed));

#अगर_घोषित CONFIG_LOAD_UEFI_KEYS
बाह्य व्योम __init efi_mokvar_table_init(व्योम);
बाह्य काष्ठा efi_mokvar_table_entry *efi_mokvar_entry_next(
			काष्ठा efi_mokvar_table_entry **mokvar_entry);
बाह्य काष्ठा efi_mokvar_table_entry *efi_mokvar_entry_find(स्थिर अक्षर *name);
#अन्यथा
अटल अंतरभूत व्योम efi_mokvar_table_init(व्योम) अणु पूर्ण
अटल अंतरभूत काष्ठा efi_mokvar_table_entry *efi_mokvar_entry_next(
			काष्ठा efi_mokvar_table_entry **mokvar_entry)
अणु
	वापस शून्य;
पूर्ण
अटल अंतरभूत काष्ठा efi_mokvar_table_entry *efi_mokvar_entry_find(
			स्थिर अक्षर *name)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _LINUX_EFI_H */
