<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_BOOT_H
#घोषणा _ASM_X86_BOOT_H


#समावेश <यंत्र/pgtable_types.h>
#समावेश <uapi/यंत्र/boot.h>

/* Physical address where kernel should be loaded. */
#घोषणा LOAD_PHYSICAL_ADDR ((CONFIG_PHYSICAL_START \
				+ (CONFIG_PHYSICAL_ALIGN - 1)) \
				& ~(CONFIG_PHYSICAL_ALIGN - 1))

/* Minimum kernel alignment, as a घातer of two */
#अगर_घोषित CONFIG_X86_64
# define MIN_KERNEL_ALIGN_LG2	PMD_SHIFT
#अन्यथा
# define MIN_KERNEL_ALIGN_LG2	(PAGE_SHIFT + THREAD_SIZE_ORDER)
#पूर्ण_अगर
#घोषणा MIN_KERNEL_ALIGN	(_AC(1, UL) << MIN_KERNEL_ALIGN_LG2)

#अगर (CONFIG_PHYSICAL_ALIGN & (CONFIG_PHYSICAL_ALIGN-1)) || \
	(CONFIG_PHYSICAL_ALIGN < MIN_KERNEL_ALIGN)
# error "Invalid value for CONFIG_PHYSICAL_ALIGN"
#पूर्ण_अगर

#अगर defined(CONFIG_KERNEL_BZIP2)
# define BOOT_HEAP_SIZE		0x400000
#या_अगर defined(CONFIG_KERNEL_ZSTD)
/*
 * Zstd needs to allocate the ZSTD_DCtx in order to decompress the kernel.
 * The ZSTD_DCtx is ~160KB, so set the heap size to 192KB because it is a
 * round number and to allow some slack.
 */
# define BOOT_HEAP_SIZE		 0x30000
#अन्यथा
# define BOOT_HEAP_SIZE		 0x10000
#पूर्ण_अगर

#अगर_घोषित CONFIG_X86_64
# define BOOT_STACK_SIZE	0x4000

# define BOOT_INIT_PGT_SIZE	(6*4096)
# अगरdef CONFIG_RANDOMIZE_BASE
/*
 * Assuming all cross the 512GB boundary:
 * 1 page क्रम level4
 * (2+2)*4 pages क्रम kernel, param, cmd_line, and अक्रमomized kernel
 * 2 pages क्रम first 2M (video RAM: CONFIG_X86_VERBOSE_BOOTUP).
 * Total is 19 pages.
 */
#  अगरdef CONFIG_X86_VERBOSE_BOOTUP
#   define BOOT_PGT_SIZE	(19*4096)
#  अन्यथा /* !CONFIG_X86_VERBOSE_BOOTUP */
#   define BOOT_PGT_SIZE	(17*4096)
#  endअगर
# अन्यथा /* !CONFIG_RANDOMIZE_BASE */
#  define BOOT_PGT_SIZE		BOOT_INIT_PGT_SIZE
# endअगर

#अन्यथा /* !CONFIG_X86_64 */
# define BOOT_STACK_SIZE	0x1000
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_X86_BOOT_H */
