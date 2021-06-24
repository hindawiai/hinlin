<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2010-2013, NVIDIA Corporation. All rights reserved.
 */

#अगर_अघोषित __MACH_TEGRA_SLEEP_H
#घोषणा __MACH_TEGRA_SLEEP_H

#समावेश "iomap.h"
#समावेश "irammap.h"

#घोषणा TEGRA_ARM_PERIF_VIRT (TEGRA_ARM_PERIF_BASE - IO_CPU_PHYS \
					+ IO_CPU_VIRT)
#घोषणा TEGRA_FLOW_CTRL_VIRT (TEGRA_FLOW_CTRL_BASE - IO_PPSB_PHYS \
					+ IO_PPSB_VIRT)
#घोषणा TEGRA_CLK_RESET_VIRT (TEGRA_CLK_RESET_BASE - IO_PPSB_PHYS \
					+ IO_PPSB_VIRT)
#घोषणा TEGRA_APB_MISC_VIRT (TEGRA_APB_MISC_BASE - IO_APB_PHYS \
					+ IO_APB_VIRT)
#घोषणा TEGRA_PMC_VIRT	(TEGRA_PMC_BASE - IO_APB_PHYS + IO_APB_VIRT)

#घोषणा TEGRA_IRAM_RESET_BASE_VIRT (IO_IRAM_VIRT + \
				TEGRA_IRAM_RESET_HANDLER_OFFSET)

/* PMC_SCRATCH37-39 and 41 are used क्रम tegra_pen_lock and idle */
#घोषणा PMC_SCRATCH37	0x130
#घोषणा PMC_SCRATCH38	0x134
#घोषणा PMC_SCRATCH39	0x138
#घोषणा PMC_SCRATCH41	0x140

#अगर_घोषित CONFIG_ARCH_TEGRA_2x_SOC
#घोषणा CPU_RESETTABLE		2
#घोषणा CPU_RESETTABLE_SOON	1
#घोषणा CPU_NOT_RESETTABLE	0
#पूर्ण_अगर

/* flag of tegra_disable_clean_inv_dcache to करो LoUIS or all */
#घोषणा TEGRA_FLUSH_CACHE_LOUIS	0
#घोषणा TEGRA_FLUSH_CACHE_ALL	1

#अगर_घोषित __ASSEMBLY__
/* रुकोs until the microsecond counter (base) is > rn */
.macro रुको_until, rn, base, पंचांगp
	add	\लn, \लn, #1
1001:	ldr	\टmp, [\मase]
	cmp	\टmp, \लn
	bmi	1001b
.endm

/* वापसs the offset of the flow controller halt रेजिस्टर क्रम a cpu */
.macro cpu_to_halt_reg rd, rcpu
	cmp	\लcpu, #0
	subne	\लd, \लcpu, #1
	movne	\लd, \लd, lsl #3
	addne	\लd, \लd, #0x14
	moveq	\लd, #0
.endm

/* वापसs the offset of the flow controller csr रेजिस्टर क्रम a cpu */
.macro cpu_to_csr_reg rd, rcpu
	cmp	\लcpu, #0
	subne	\लd, \लcpu, #1
	movne	\लd, \लd, lsl #3
	addne	\लd, \लd, #0x18
	moveq	\लd, #8
.endm

/* वापसs the ID of the current processor */
.macro cpu_id, rd
	mrc	p15, 0, \लd, c0, c0, 5
	and	\लd, \लd, #0xF
.endm

/* loads a 32-bit value पूर्णांकo a रेजिस्टर without a data access */
.macro mov32, reg, val
	movw	\लeg, #:lower16:\खal
	movt	\लeg, #:upper16:\खal
.endm

/* Marco to check CPU part num */
.macro check_cpu_part_num part_num, पंचांगp1, पंचांगp2
	mrc	p15, 0, \टmp1, c0, c0, 0
	ubfx	\टmp1, \टmp1, #4, #12
	mov32	\टmp2, \part_num
	cmp	\टmp1, \टmp2
.endm

/* Macro to निकास SMP coherency. */
.macro निकास_smp, पंचांगp1, पंचांगp2
	mrc	p15, 0, \टmp1, c1, c0, 1	@ ACTLR
	bic	\टmp1, \टmp1, #(1<<6) | (1<<0)	@ clear ACTLR.SMP | ACTLR.FW
	mcr	p15, 0, \टmp1, c1, c0, 1	@ ACTLR
	isb
#अगर_घोषित CONFIG_HAVE_ARM_SCU
	check_cpu_part_num 0xc09, \टmp1, \टmp2
	mrceq	p15, 0, \टmp1, c0, c0, 5
	andeq	\टmp1, \टmp1, #0xF
	moveq	\टmp1, \टmp1, lsl #2
	moveq	\टmp2, #0xf
	moveq	\टmp2, \टmp2, lsl \टmp1
	ldreq	\टmp1, =(TEGRA_ARM_PERIF_VIRT + 0xC)
	streq	\टmp2, [\टmp1]			@ invalidate SCU tags क्रम CPU
	dsb
#पूर्ण_अगर
.endm

/* Macro to check Tegra revision */
#घोषणा APB_MISC_GP_HIDREV	0x804
.macro tegra_get_soc_id base, पंचांगp1
	mov32	\टmp1, \मase
	ldr	\टmp1, [\टmp1, #APB_MISC_GP_HIDREV]
	and	\टmp1, \टmp1, #0xff00
	mov	\टmp1, \टmp1, lsr #8
.endm

#अन्यथा
व्योम tegra_resume(व्योम);
पूर्णांक tegra_sleep_cpu_finish(अचिन्हित दीर्घ);
व्योम tegra_disable_clean_inv_dcache(u32 flag);

व्योम tegra20_hotplug_shutकरोwn(व्योम);
व्योम tegra30_hotplug_shutकरोwn(व्योम);

व्योम tegra20_tear_करोwn_cpu(व्योम);
व्योम tegra30_tear_करोwn_cpu(व्योम);

#पूर्ण_अगर
#पूर्ण_अगर
