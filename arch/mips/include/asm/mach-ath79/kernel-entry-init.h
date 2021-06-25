<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  Atheros AR71XX/AR724X/AR913X specअगरic kernel entry setup
 *
 *  Copyright (C) 2009 Gabor Juhos <juhosg@खोलोwrt.org>
 */
#अगर_अघोषित __ASM_MACH_ATH79_KERNEL_ENTRY_H
#घोषणा __ASM_MACH_ATH79_KERNEL_ENTRY_H

	/*
	 * Some bootloaders set the 'Kseg0 coherency algorithm' to
	 * 'Cacheable, noncoherent, write-through, no write allocate'
	 * and this cause perक्रमmance issues. Let's go and change it to
	 * 'Cacheable, noncoherent, write-back, write allocate'
	 */
	.macro	kernel_entry_setup
	mfc0	t0, CP0_CONFIG
	li	t1, ~CONF_CM_CMASK
	and	t0, t1
	ori	t0, CONF_CM_CACHABLE_NONCOHERENT
	mtc0	t0, CP0_CONFIG
	nop
	.endm

	.macro	smp_slave_setup
	.endm

#पूर्ण_अगर /* __ASM_MACH_ATH79_KERNEL_ENTRY_H */
