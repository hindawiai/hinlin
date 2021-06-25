<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * OMAP4 Power/Reset Management (PRM) function prototypes
 *
 * Copyright (C) 2010 Nokia Corporation
 * Copyright (C) 2011 Texas Instruments, Inc.
 * Paul Walmsley
 */
#अगर_अघोषित __ARCH_ASM_MACH_OMAP2_PRMINST44XX_H
#घोषणा __ARCH_ASM_MACH_OMAP2_PRMINST44XX_H

#घोषणा PRM_INSTANCE_UNKNOWN	-1
बाह्य s32 omap4_prmst_get_prm_dev_inst(व्योम);
व्योम omap4_prminst_set_prm_dev_inst(s32 dev_inst);

/*
 * In an ideal world, we would not export these low-level functions,
 * but this will probably take some समय to fix properly
 */
बाह्य u32 omap4_prminst_पढ़ो_inst_reg(u8 part, s16 inst, u16 idx);
बाह्य व्योम omap4_prminst_ग_लिखो_inst_reg(u32 val, u8 part, s16 inst, u16 idx);
बाह्य u32 omap4_prminst_rmw_inst_reg_bits(u32 mask, u32 bits, u8 part,
					   s16 inst, u16 idx);

बाह्य व्योम omap4_prminst_global_warm_sw_reset(व्योम);

बाह्य पूर्णांक omap4_prminst_is_hardreset_निश्चितed(u8 shअगरt, u8 part, s16 inst,
					       u16 rstctrl_offs);
बाह्य पूर्णांक omap4_prminst_निश्चित_hardreset(u8 shअगरt, u8 part, s16 inst,
					  u16 rstctrl_offs);
पूर्णांक omap4_prminst_deनिश्चित_hardreset(u8 shअगरt, u8 st_shअगरt, u8 part,
				     s16 inst, u16 rstctrl_offs,
				     u16 rstst_offs);

बाह्य व्योम omap_prm_base_init(व्योम);

#पूर्ण_अगर
