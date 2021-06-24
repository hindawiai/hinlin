<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_E820_TYPES_H
#घोषणा _ASM_E820_TYPES_H

#समावेश <uapi/यंत्र/bootparam.h>

/*
 * These are the E820 types known to the kernel:
 */
क्रमागत e820_type अणु
	E820_TYPE_RAM		= 1,
	E820_TYPE_RESERVED	= 2,
	E820_TYPE_ACPI		= 3,
	E820_TYPE_NVS		= 4,
	E820_TYPE_UNUSABLE	= 5,
	E820_TYPE_PMEM		= 7,

	/*
	 * This is a non-standardized way to represent ADR or
	 * NVDIMM regions that persist over a reboot.
	 *
	 * The kernel will ignore their special capabilities
	 * unless the CONFIG_X86_PMEM_LEGACY=y option is set.
	 *
	 * ( Note that older platक्रमms also used 6 क्रम the same
	 *   type of memory, but newer versions चयनed to 12 as
	 *   6 was asचिन्हित dअगरferently. Some समय they will learn... )
	 */
	E820_TYPE_PRAM		= 12,

	/*
	 * Special-purpose memory is indicated to the प्रणाली via the
	 * EFI_MEMORY_SP attribute. Define an e820 translation of this
	 * memory type क्रम the purpose of reserving this range and
	 * marking it with the IORES_DESC_SOFT_RESERVED designation.
	 */
	E820_TYPE_SOFT_RESERVED	= 0xefffffff,

	/*
	 * Reserved RAM used by the kernel itself अगर
	 * CONFIG_INTEL_TXT=y is enabled, memory of this type
	 * will be included in the S3 पूर्णांकegrity calculation
	 * and so should not include any memory that the BIOS
	 * might alter over the S3 transition:
	 */
	E820_TYPE_RESERVED_KERN	= 128,
पूर्ण;

/*
 * A single E820 map entry, describing a memory range of [addr...addr+size-1],
 * of 'type' memory type:
 *
 * (We pack it because there can be thousands of them on large प्रणालीs.)
 */
काष्ठा e820_entry अणु
	u64			addr;
	u64			size;
	क्रमागत e820_type		type;
पूर्ण __attribute__((packed));

/*
 * The legacy E820 BIOS limits us to 128 (E820_MAX_ENTRIES_ZEROPAGE) nodes
 * due to the स्थिरrained space in the zeropage.
 *
 * On large प्रणालीs we can easily have thousands of nodes with RAM,
 * which cannot be fit पूर्णांकo so few entries - so we have a mechanism
 * to extend the e820 table size at build-समय, via the E820_MAX_ENTRIES
 * define below.
 *
 * ( Those extra entries are क्रमागतerated via the EFI memory map, not
 *   via the legacy zeropage mechanism. )
 *
 * Size our पूर्णांकernal memory map tables to have room क्रम these additional
 * entries, based on a heuristic calculation: up to three entries per
 * NUMA node, plus E820_MAX_ENTRIES_ZEROPAGE क्रम some extra space.
 *
 * This allows क्रम bootstrap/firmware quirks such as possible duplicate
 * E820 entries that might need room in the same arrays, prior to the
 * call to e820__update_table() to हटाओ duplicates.  The allowance
 * of three memory map entries per node is "enough" entries क्रम
 * the initial hardware platक्रमm motivating this mechanism to make
 * use of additional EFI map entries.  Future platक्रमms may want
 * to allow more than three entries per node or otherwise refine
 * this size.
 */

#समावेश <linux/numa.h>

#घोषणा E820_MAX_ENTRIES	(E820_MAX_ENTRIES_ZEROPAGE + 3*MAX_NUMNODES)

/*
 * The whole array of E820 entries:
 */
काष्ठा e820_table अणु
	__u32 nr_entries;
	काष्ठा e820_entry entries[E820_MAX_ENTRIES];
पूर्ण;

/*
 * Various well-known legacy memory ranges in physical memory:
 */
#घोषणा ISA_START_ADDRESS	0x000a0000
#घोषणा ISA_END_ADDRESS		0x00100000

#घोषणा BIOS_BEGIN		0x000a0000
#घोषणा BIOS_END		0x00100000

#घोषणा HIGH_MEMORY		0x00100000

#घोषणा BIOS_ROM_BASE		0xffe00000
#घोषणा BIOS_ROM_END		0xffffffff

#पूर्ण_अगर /* _ASM_E820_TYPES_H */
