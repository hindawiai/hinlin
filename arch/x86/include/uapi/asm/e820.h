<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_ASM_X86_E820_H
#घोषणा _UAPI_ASM_X86_E820_H
#घोषणा E820MAP	0x2d0		/* our map */
#घोषणा E820MAX	128		/* number of entries in E820MAP */

/*
 * Legacy E820 BIOS limits us to 128 (E820MAX) nodes due to the
 * स्थिरrained space in the zeropage.  If we have more nodes than
 * that, and अगर we've booted off EFI firmware, then the EFI tables
 * passed us from the EFI firmware can list more nodes.  Size our
 * पूर्णांकernal memory map tables to have room क्रम these additional
 * nodes, based on up to three entries per node क्रम which the
 * kernel was built: MAX_NUMNODES == (1 << CONFIG_NODES_SHIFT),
 * plus E820MAX, allowing space क्रम the possible duplicate E820
 * entries that might need room in the same arrays, prior to the
 * call to sanitize_e820_map() to हटाओ duplicates.  The allowance
 * of three memory map entries per node is "enough" entries क्रम
 * the initial hardware platक्रमm motivating this mechanism to make
 * use of additional EFI map entries.  Future platक्रमms may want
 * to allow more than three entries per node or otherwise refine
 * this size.
 */

#अगर_अघोषित __KERNEL__
#घोषणा E820_X_MAX E820MAX
#पूर्ण_अगर

#घोषणा E820NR	0x1e8		/* # entries in E820MAP */

#घोषणा E820_RAM	1
#घोषणा E820_RESERVED	2
#घोषणा E820_ACPI	3
#घोषणा E820_NVS	4
#घोषणा E820_UNUSABLE	5
#घोषणा E820_PMEM	7

/*
 * This is a non-standardized way to represent ADR or NVDIMM regions that
 * persist over a reboot.  The kernel will ignore their special capabilities
 * unless the CONFIG_X86_PMEM_LEGACY option is set.
 *
 * ( Note that older platक्रमms also used 6 क्रम the same type of memory,
 *   but newer versions चयनed to 12 as 6 was asचिन्हित dअगरferently.  Some
 *   समय they will learn... )
 */
#घोषणा E820_PRAM	12

/*
 * reserved RAM used by kernel itself
 * अगर CONFIG_INTEL_TXT is enabled, memory of this type will be
 * included in the S3 पूर्णांकegrity calculation and so should not include
 * any memory that BIOS might alter over the S3 transition
 */
#घोषणा E820_RESERVED_KERN        128

#अगर_अघोषित __ASSEMBLY__
#समावेश <linux/types.h>
काष्ठा e820entry अणु
	__u64 addr;	/* start of memory segment */
	__u64 size;	/* size of memory segment */
	__u32 type;	/* type of memory segment */
पूर्ण __attribute__((packed));

काष्ठा e820map अणु
	__u32 nr_map;
	काष्ठा e820entry map[E820_X_MAX];
पूर्ण;

#घोषणा ISA_START_ADDRESS	0xa0000
#घोषणा ISA_END_ADDRESS		0x100000

#घोषणा BIOS_BEGIN		0x000a0000
#घोषणा BIOS_END		0x00100000

#घोषणा BIOS_ROM_BASE		0xffe00000
#घोषणा BIOS_ROM_END		0xffffffff

#पूर्ण_अगर /* __ASSEMBLY__ */


#पूर्ण_अगर /* _UAPI_ASM_X86_E820_H */
