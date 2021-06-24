<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright 2012 Pavel Machek <pavel@denx.de>
 * Copyright (C) 2012-2015 Altera Corporation
 */

#अगर_अघोषित __MACH_CORE_H
#घोषणा __MACH_CORE_H

#घोषणा SOCFPGA_RSTMGR_CTRL	0x04
#घोषणा SOCFPGA_RSTMGR_MODMPURST	0x10
#घोषणा SOCFPGA_RSTMGR_MODPERRST	0x14
#घोषणा SOCFPGA_RSTMGR_BRGMODRST	0x1c

#घोषणा SOCFPGA_A10_RSTMGR_CTRL		0xC
#घोषणा SOCFPGA_A10_RSTMGR_MODMPURST	0x20

/* System Manager bits */
#घोषणा RSTMGR_CTRL_SWCOLDRSTREQ	0x1	/* Cold Reset */
#घोषणा RSTMGR_CTRL_SWWARMRSTREQ	0x2	/* Warm Reset */

#घोषणा RSTMGR_MPUMODRST_CPU1		0x2     /* CPU1 Reset */

व्योम socfpga_init_l2_ecc(व्योम);
व्योम socfpga_init_ocram_ecc(व्योम);
व्योम socfpga_init_arria10_l2_ecc(व्योम);
व्योम socfpga_init_arria10_ocram_ecc(व्योम);

बाह्य व्योम __iomem *sys_manager_base_addr;
बाह्य व्योम __iomem *rst_manager_base_addr;
बाह्य व्योम __iomem *sdr_ctl_base_addr;

u32 socfpga_sdram_self_refresh(u32 sdr_base);
बाह्य अचिन्हित पूर्णांक socfpga_sdram_self_refresh_sz;

बाह्य अक्षर secondary_trampoline, secondary_trampoline_end;

बाह्य अचिन्हित दीर्घ socfpga_cpu1start_addr;

#घोषणा SOCFPGA_SCU_VIRT_BASE   0xfee00000

#पूर्ण_अगर
