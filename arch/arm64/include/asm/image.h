<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित __ASM_IMAGE_H
#घोषणा __ASM_IMAGE_H

#घोषणा ARM64_IMAGE_MAGIC	"ARM\x64"

#घोषणा ARM64_IMAGE_FLAG_BE_SHIFT		0
#घोषणा ARM64_IMAGE_FLAG_PAGE_SIZE_SHIFT	(ARM64_IMAGE_FLAG_BE_SHIFT + 1)
#घोषणा ARM64_IMAGE_FLAG_PHYS_BASE_SHIFT \
					(ARM64_IMAGE_FLAG_PAGE_SIZE_SHIFT + 2)
#घोषणा ARM64_IMAGE_FLAG_BE_MASK		0x1
#घोषणा ARM64_IMAGE_FLAG_PAGE_SIZE_MASK		0x3
#घोषणा ARM64_IMAGE_FLAG_PHYS_BASE_MASK		0x1

#घोषणा ARM64_IMAGE_FLAG_LE			0
#घोषणा ARM64_IMAGE_FLAG_BE			1
#घोषणा ARM64_IMAGE_FLAG_PAGE_SIZE_4K		1
#घोषणा ARM64_IMAGE_FLAG_PAGE_SIZE_16K		2
#घोषणा ARM64_IMAGE_FLAG_PAGE_SIZE_64K		3
#घोषणा ARM64_IMAGE_FLAG_PHYS_BASE		1

#अगर_अघोषित __ASSEMBLY__

#घोषणा arm64_image_flag_field(flags, field) \
				(((flags) >> field##_SHIFT) & field##_MASK)

/*
 * काष्ठा arm64_image_header - arm64 kernel image header
 * See Documentation/arm64/booting.rst क्रम details
 *
 * @code0:		Executable code, or
 *   @mz_header		  alternatively used क्रम part of MZ header
 * @code1:		Executable code
 * @text_offset:	Image load offset
 * @image_size:		Effective Image size
 * @flags:		kernel flags
 * @reserved:		reserved
 * @magic:		Magic number
 * @reserved5:		reserved, or
 *   @pe_header:	  alternatively used क्रम PE COFF offset
 */

काष्ठा arm64_image_header अणु
	__le32 code0;
	__le32 code1;
	__le64 text_offset;
	__le64 image_size;
	__le64 flags;
	__le64 res2;
	__le64 res3;
	__le64 res4;
	__le32 magic;
	__le32 res5;
पूर्ण;

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* __ASM_IMAGE_H */
