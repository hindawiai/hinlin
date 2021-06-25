<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित _ASM_RISCV_IMAGE_H
#घोषणा _ASM_RISCV_IMAGE_H

#घोषणा RISCV_IMAGE_MAGIC	"RISCV\0\0\0"
#घोषणा RISCV_IMAGE_MAGIC2	"RSC\x05"

#घोषणा RISCV_IMAGE_FLAG_BE_SHIFT	0
#घोषणा RISCV_IMAGE_FLAG_BE_MASK	0x1

#घोषणा RISCV_IMAGE_FLAG_LE		0
#घोषणा RISCV_IMAGE_FLAG_BE		1

#अगर_घोषित CONFIG_CPU_BIG_ENDIAN
#त्रुटि conversion of header fields to LE not yet implemented
#अन्यथा
#घोषणा __HEAD_FLAG_BE		RISCV_IMAGE_FLAG_LE
#पूर्ण_अगर

#घोषणा __HEAD_FLAG(field)	(__HEAD_FLAG_##field << \
				RISCV_IMAGE_FLAG_##field##_SHIFT)

#घोषणा __HEAD_FLAGS		(__HEAD_FLAG(BE))

#घोषणा RISCV_HEADER_VERSION_MAJOR 0
#घोषणा RISCV_HEADER_VERSION_MINOR 2

#घोषणा RISCV_HEADER_VERSION (RISCV_HEADER_VERSION_MAJOR << 16 | \
			      RISCV_HEADER_VERSION_MINOR)

#अगर_अघोषित __ASSEMBLY__
/**
 * काष्ठा riscv_image_header - riscv kernel image header
 * @code0:		Executable code
 * @code1:		Executable code
 * @text_offset:	Image load offset (little endian)
 * @image_size:		Effective Image size (little endian)
 * @flags:		kernel flags (little endian)
 * @version:		version
 * @res1:		reserved
 * @res2:		reserved
 * @magic:		Magic number (RISC-V specअगरic; deprecated)
 * @magic2:		Magic number 2 (to match the ARM64 'magic' field pos)
 * @res3:		reserved (will be used क्रम PE COFF offset)
 *
 * The पूर्णांकention is क्रम this header क्रमmat to be shared between multiple
 * architectures to aव्योम a prolअगरeration of image header क्रमmats.
 */

काष्ठा riscv_image_header अणु
	u32 code0;
	u32 code1;
	u64 text_offset;
	u64 image_size;
	u64 flags;
	u32 version;
	u32 res1;
	u64 res2;
	u64 magic;
	u32 magic2;
	u32 res3;
पूर्ण;
#पूर्ण_अगर /* __ASSEMBLY__ */
#पूर्ण_अगर /* _ASM_RISCV_IMAGE_H */
