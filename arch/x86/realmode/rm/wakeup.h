<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Definitions क्रम the wakeup data काष्ठाure at the head of the
 * wakeup code.
 */

#अगर_अघोषित ARCH_X86_KERNEL_ACPI_RM_WAKEUP_H
#घोषणा ARCH_X86_KERNEL_ACPI_RM_WAKEUP_H

#अगर_अघोषित __ASSEMBLY__
#समावेश <linux/types.h>

/* This must match data at wakeup.S */
काष्ठा wakeup_header अणु
	u16 video_mode;		/* Video mode number */
	u32 pmode_entry;	/* Protected mode resume poपूर्णांक, 32-bit only */
	u16 pmode_cs;
	u32 pmode_cr0;		/* Protected mode cr0 */
	u32 pmode_cr3;		/* Protected mode cr3 */
	u32 pmode_cr4;		/* Protected mode cr4 */
	u32 pmode_efer_low;	/* Protected mode EFER */
	u32 pmode_efer_high;
	u64 pmode_gdt;
	u32 pmode_misc_en_low;	/* Protected mode MISC_ENABLE */
	u32 pmode_misc_en_high;
	u32 pmode_behavior;	/* Wakeup routine behavior flags */
	u32 realmode_flags;
	u32 real_magic;
	u32 signature;		/* To check we have correct काष्ठाure */
पूर्ण __attribute__((__packed__));

बाह्य काष्ठा wakeup_header wakeup_header;
#पूर्ण_अगर

#घोषणा WAKEUP_HEADER_OFFSET	8
#घोषणा WAKEUP_HEADER_SIGNATURE 0x51ee1111

/* Wakeup behavior bits */
#घोषणा WAKEUP_BEHAVIOR_RESTORE_MISC_ENABLE     0
#घोषणा WAKEUP_BEHAVIOR_RESTORE_CR4		1
#घोषणा WAKEUP_BEHAVIOR_RESTORE_EFER		2

#पूर्ण_अगर /* ARCH_X86_KERNEL_ACPI_RM_WAKEUP_H */
