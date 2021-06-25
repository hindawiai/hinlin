<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित __ASM_BOOT_H
#घोषणा __ASM_BOOT_H

#समावेश <linux/sizes.h>

/*
 * arm64 requires the DTB to be 8 byte aligned and
 * not exceed 2MB in size.
 */
#घोषणा MIN_FDT_ALIGN		8
#घोषणा MAX_FDT_SIZE		SZ_2M

/*
 * arm64 requires the kernel image to placed at a 2 MB aligned base address
 */
#घोषणा MIN_KIMG_ALIGN		SZ_2M

#पूर्ण_अगर
