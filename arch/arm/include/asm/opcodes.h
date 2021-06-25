<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  arch/arm/include/यंत्र/opcodes.h
 */

#अगर_अघोषित __ASM_ARM_OPCODES_H
#घोषणा __ASM_ARM_OPCODES_H

#अगर_अघोषित __ASSEMBLY__
#समावेश <linux/linkage.h>
बाह्य यंत्रlinkage अचिन्हित पूर्णांक arm_check_condition(u32 opcode, u32 psr);
#पूर्ण_अगर

#घोषणा ARM_OPCODE_CONDTEST_FAIL   0
#घोषणा ARM_OPCODE_CONDTEST_PASS   1
#घोषणा ARM_OPCODE_CONDTEST_UNCOND 2


/*
 * Assembler opcode byteswap helpers.
 * These are only पूर्णांकended क्रम use by this header: करोn't use them directly,
 * because they will be suboptimal in most हालs.
 */
#घोषणा ___यंत्र_opcode_swab32(x) (	\
	  (((x) << 24) & 0xFF000000)	\
	| (((x) <<  8) & 0x00FF0000)	\
	| (((x) >>  8) & 0x0000FF00)	\
	| (((x) >> 24) & 0x000000FF)	\
)
#घोषणा ___यंत्र_opcode_swab16(x) (	\
	  (((x) << 8) & 0xFF00)		\
	| (((x) >> 8) & 0x00FF)		\
)
#घोषणा ___यंत्र_opcode_swahb32(x) (	\
	  (((x) << 8) & 0xFF00FF00)	\
	| (((x) >> 8) & 0x00FF00FF)	\
)
#घोषणा ___यंत्र_opcode_swahw32(x) (	\
	  (((x) << 16) & 0xFFFF0000)	\
	| (((x) >> 16) & 0x0000FFFF)	\
)
#घोषणा ___यंत्र_opcode_identity32(x) ((x) & 0xFFFFFFFF)
#घोषणा ___यंत्र_opcode_identity16(x) ((x) & 0xFFFF)


/*
 * Opcode byteswap helpers
 *
 * These macros help with converting inकाष्ठाions between a canonical पूर्णांकeger
 * क्रमmat and in-memory representation, in an endianness-agnostic manner.
 *
 * __mem_to_opcode_*() convert from in-memory representation to canonical क्रमm.
 * __opcode_to_mem_*() convert from canonical क्रमm to in-memory representation.
 *
 *
 * Canonical inकाष्ठाion representation:
 *
 *	ARM:		0xKKLLMMNN
 *	Thumb 16-bit:	0x0000KKLL, where KK < 0xE8
 *	Thumb 32-bit:	0xKKLLMMNN, where KK >= 0xE8
 *
 * There is no way to distinguish an ARM inकाष्ठाion in canonical representation
 * from a Thumb inकाष्ठाion (just as these cannot be distinguished in memory).
 * Where this distinction is important, it needs to be tracked separately.
 *
 * Note that values in the range 0x0000E800..0xE7FFFFFF पूर्णांकentionally करो not
 * represent any valid Thumb-2 inकाष्ठाion.  For this range,
 * __opcode_is_thumb32() and __opcode_is_thumb16() will both be false.
 *
 * The ___यंत्र variants are पूर्णांकended only क्रम use by this header, in situations
 * involving अंतरभूत assembler.  For .S files, the normal __opcode_*() macros
 * should करो the right thing.
 */
#अगर_घोषित __ASSEMBLY__

#घोषणा ___opcode_swab32(x) ___यंत्र_opcode_swab32(x)
#घोषणा ___opcode_swab16(x) ___यंत्र_opcode_swab16(x)
#घोषणा ___opcode_swahb32(x) ___यंत्र_opcode_swahb32(x)
#घोषणा ___opcode_swahw32(x) ___यंत्र_opcode_swahw32(x)
#घोषणा ___opcode_identity32(x) ___यंत्र_opcode_identity32(x)
#घोषणा ___opcode_identity16(x) ___यंत्र_opcode_identity16(x)

#अन्यथा /* ! __ASSEMBLY__ */

#समावेश <linux/types.h>
#समावेश <linux/swab.h>

#घोषणा ___opcode_swab32(x) swab32(x)
#घोषणा ___opcode_swab16(x) swab16(x)
#घोषणा ___opcode_swahb32(x) swahb32(x)
#घोषणा ___opcode_swahw32(x) swahw32(x)
#घोषणा ___opcode_identity32(x) ((u32)(x))
#घोषणा ___opcode_identity16(x) ((u16)(x))

#पूर्ण_अगर /* ! __ASSEMBLY__ */


#अगर_घोषित CONFIG_CPU_ENDIAN_BE8

#घोषणा __opcode_to_mem_arm(x) ___opcode_swab32(x)
#घोषणा __opcode_to_mem_thumb16(x) ___opcode_swab16(x)
#घोषणा __opcode_to_mem_thumb32(x) ___opcode_swahb32(x)
#घोषणा ___यंत्र_opcode_to_mem_arm(x) ___यंत्र_opcode_swab32(x)
#घोषणा ___यंत्र_opcode_to_mem_thumb16(x) ___यंत्र_opcode_swab16(x)
#घोषणा ___यंत्र_opcode_to_mem_thumb32(x) ___यंत्र_opcode_swahb32(x)

#अन्यथा /* ! CONFIG_CPU_ENDIAN_BE8 */

#घोषणा __opcode_to_mem_arm(x) ___opcode_identity32(x)
#घोषणा __opcode_to_mem_thumb16(x) ___opcode_identity16(x)
#घोषणा ___यंत्र_opcode_to_mem_arm(x) ___यंत्र_opcode_identity32(x)
#घोषणा ___यंत्र_opcode_to_mem_thumb16(x) ___यंत्र_opcode_identity16(x)
#अगर_अघोषित CONFIG_CPU_ENDIAN_BE32
/*
 * On BE32 प्रणालीs, using 32-bit accesses to store Thumb inकाष्ठाions will not
 * work in all हालs, due to alignment स्थिरraपूर्णांकs.  For now, a correct
 * version is not provided क्रम BE32.
 */
#घोषणा __opcode_to_mem_thumb32(x) ___opcode_swahw32(x)
#घोषणा ___यंत्र_opcode_to_mem_thumb32(x) ___यंत्र_opcode_swahw32(x)
#पूर्ण_अगर

#पूर्ण_अगर /* ! CONFIG_CPU_ENDIAN_BE8 */

#घोषणा __mem_to_opcode_arm(x) __opcode_to_mem_arm(x)
#घोषणा __mem_to_opcode_thumb16(x) __opcode_to_mem_thumb16(x)
#अगर_अघोषित CONFIG_CPU_ENDIAN_BE32
#घोषणा __mem_to_opcode_thumb32(x) __opcode_to_mem_thumb32(x)
#पूर्ण_अगर

/* Operations specअगरic to Thumb opcodes */

/* Inकाष्ठाion size checks: */
#घोषणा __opcode_is_thumb32(x) (		\
	   ((x) & 0xF8000000) == 0xE8000000	\
	|| ((x) & 0xF0000000) == 0xF0000000	\
)
#घोषणा __opcode_is_thumb16(x) (					\
	   ((x) & 0xFFFF0000) == 0					\
	&& !(((x) & 0xF800) == 0xE800 || ((x) & 0xF000) == 0xF000)	\
)

/* Operations to स्थिरruct or split 32-bit Thumb inकाष्ठाions: */
#घोषणा __opcode_thumb32_first(x) (___opcode_identity16((x) >> 16))
#घोषणा __opcode_thumb32_second(x) (___opcode_identity16(x))
#घोषणा __opcode_thumb32_compose(first, second) (			\
	  (___opcode_identity32(___opcode_identity16(first)) << 16)	\
	| ___opcode_identity32(___opcode_identity16(second))		\
)
#घोषणा ___यंत्र_opcode_thumb32_first(x) (___यंत्र_opcode_identity16((x) >> 16))
#घोषणा ___यंत्र_opcode_thumb32_second(x) (___यंत्र_opcode_identity16(x))
#घोषणा ___यंत्र_opcode_thumb32_compose(first, second) (			    \
	  (___यंत्र_opcode_identity32(___यंत्र_opcode_identity16(first)) << 16) \
	| ___यंत्र_opcode_identity32(___यंत्र_opcode_identity16(second))	    \
)

/*
 * Opcode injection helpers
 *
 * In rare हालs it is necessary to assemble an opcode which the
 * assembler करोes not support directly, or which would normally be
 * rejected because of the CFLAGS or AFLAGS used to build the affected
 * file.
 *
 * Beक्रमe using these macros, consider carefully whether it is feasible
 * instead to change the build flags क्रम your file, or whether it really
 * makes sense to support old assembler versions when building that
 * particular kernel feature.
 *
 * The macros defined here should only be used where there is no viable
 * alternative.
 *
 *
 * __inst_arm(x): emit the specअगरied ARM opcode
 * __inst_thumb16(x): emit the specअगरied 16-bit Thumb opcode
 * __inst_thumb32(x): emit the specअगरied 32-bit Thumb opcode
 *
 * __inst_arm_thumb16(arm, thumb): emit either the specअगरied arm or
 *	16-bit Thumb opcode, depending on whether an ARM or Thumb-2
 *	kernel is being built
 *
 * __inst_arm_thumb32(arm, thumb): emit either the specअगरied arm or
 *	32-bit Thumb opcode, depending on whether an ARM or Thumb-2
 *	kernel is being built
 *
 *
 * Note that using these macros directly is poor practice.  Instead, you
 * should use them to define human-पढ़ोable wrapper macros to encode the
 * inकाष्ठाions that you care about.  In code which might run on ARMv7 or
 * above, you can usually use the __inst_arm_thumbअणु16,32पूर्ण macros to
 * specअगरy the ARM and Thumb alternatives at the same समय.  This ensures
 * that the correct opcode माला_लो emitted depending on the inकाष्ठाion set
 * used क्रम the kernel build.
 *
 * Look at opcodes-virt.h क्रम an example of how to use these macros.
 */
#समावेश <linux/stringअगरy.h>

#घोषणा __inst_arm(x) ___inst_arm(___यंत्र_opcode_to_mem_arm(x))
#घोषणा __inst_thumb32(x) ___inst_thumb32(				\
	___यंत्र_opcode_to_mem_thumb16(___यंत्र_opcode_thumb32_first(x)),	\
	___यंत्र_opcode_to_mem_thumb16(___यंत्र_opcode_thumb32_second(x))	\
)
#घोषणा __inst_thumb16(x) ___inst_thumb16(___यंत्र_opcode_to_mem_thumb16(x))

#अगर_घोषित CONFIG_THUMB2_KERNEL
#घोषणा __inst_arm_thumb16(arm_opcode, thumb_opcode) \
	__inst_thumb16(thumb_opcode)
#घोषणा __inst_arm_thumb32(arm_opcode, thumb_opcode) \
	__inst_thumb32(thumb_opcode)
#अन्यथा
#घोषणा __inst_arm_thumb16(arm_opcode, thumb_opcode) __inst_arm(arm_opcode)
#घोषणा __inst_arm_thumb32(arm_opcode, thumb_opcode) __inst_arm(arm_opcode)
#पूर्ण_अगर

/* Helpers क्रम the helpers.  Don't use these directly. */
#अगर_घोषित __ASSEMBLY__
#घोषणा ___inst_arm(x) .दीर्घ x
#घोषणा ___inst_thumb16(x) .लघु x
#घोषणा ___inst_thumb32(first, second) .लघु first, second
#अन्यथा
#घोषणा ___inst_arm(x) ".long " __stringअगरy(x) "\n\t"
#घोषणा ___inst_thumb16(x) ".short " __stringअगरy(x) "\n\t"
#घोषणा ___inst_thumb32(first, second) \
	".short " __stringअगरy(first) ", " __stringअगरy(second) "\n\t"
#पूर्ण_अगर

#पूर्ण_अगर /* __ASM_ARM_OPCODES_H */
