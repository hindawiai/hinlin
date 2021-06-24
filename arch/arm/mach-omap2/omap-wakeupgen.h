<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * OMAP WakeupGen header file
 *
 * Copyright (C) 2011 Texas Instruments, Inc.
 *	Santosh Shilimkar <santosh.shilimkar@ti.com>
 */
#अगर_अघोषित OMAP_ARCH_WAKEUPGEN_H
#घोषणा OMAP_ARCH_WAKEUPGEN_H

/* OMAP4 and OMAP5 has same base address */
#घोषणा OMAP_WKUPGEN_BASE			0x48281000

#घोषणा OMAP_WKG_CONTROL_0			0x00
#घोषणा OMAP_WKG_ENB_A_0			0x10
#घोषणा OMAP_WKG_ENB_B_0			0x14
#घोषणा OMAP_WKG_ENB_C_0			0x18
#घोषणा OMAP_WKG_ENB_D_0			0x1c
#घोषणा OMAP_WKG_ENB_E_0			0x20
#घोषणा OMAP_WKG_ENB_A_1			0x410
#घोषणा OMAP_WKG_ENB_B_1			0x414
#घोषणा OMAP_WKG_ENB_C_1			0x418
#घोषणा OMAP_WKG_ENB_D_1			0x41c
#घोषणा OMAP_WKG_ENB_E_1			0x420
#घोषणा OMAP_AUX_CORE_BOOT_0			0x800
#घोषणा OMAP_AUX_CORE_BOOT_1			0x804
#घोषणा OMAP_AMBA_IF_MODE			0x80c
#घोषणा OMAP_PTMSYNCREQ_MASK			0xc00
#घोषणा OMAP_PTMSYNCREQ_EN			0xc04
#घोषणा OMAP_TIMESTAMPCYCLELO			0xc08
#घोषणा OMAP_TIMESTAMPCYCLEHI			0xc0c

बाह्य व्योम __iomem *omap_get_wakeupgen_base(व्योम);
बाह्य पूर्णांक omap_secure_apis_support(व्योम);
#पूर्ण_अगर
