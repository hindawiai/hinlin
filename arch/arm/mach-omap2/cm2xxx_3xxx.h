<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * OMAP2/3 Clock Management (CM) रेजिस्टर definitions
 *
 * Copyright (C) 2007-2009 Texas Instruments, Inc.
 * Copyright (C) 2007-2010 Nokia Corporation
 * Paul Walmsley
 *
 * The CM hardware modules on the OMAP2/3 are quite similar to each
 * other.  The CM modules/instances on OMAP4 are quite dअगरferent, so
 * they are handled in a separate file.
 */
#अगर_अघोषित __ARCH_ASM_MACH_OMAP2_CM2XXX_3XXX_H
#घोषणा __ARCH_ASM_MACH_OMAP2_CM2XXX_3XXX_H

#समावेश "cm.h"

/*
 * Module specअगरic CM रेजिस्टर offsets from CM_BASE + करोमुख्य offset
 * Use cm_अणुपढ़ो,ग_लिखोपूर्ण_mod_reg() with these रेजिस्टरs.
 * These रेजिस्टर offsets generally appear in more than one PRCM submodule.
 */

/* Common between OMAP2 and OMAP3 */

#घोषणा CM_FCLKEN					0x0000
#घोषणा CM_FCLKEN1					CM_FCLKEN
#घोषणा CM_CLKEN					CM_FCLKEN
#घोषणा CM_ICLKEN					0x0010
#घोषणा CM_ICLKEN1					CM_ICLKEN
#घोषणा CM_ICLKEN2					0x0014
#घोषणा CM_ICLKEN3					0x0018
#घोषणा CM_IDLEST					0x0020
#घोषणा CM_IDLEST1					CM_IDLEST
#घोषणा CM_IDLEST2					0x0024
#घोषणा OMAP2430_CM_IDLEST3				0x0028
#घोषणा CM_AUTOIDLE					0x0030
#घोषणा CM_AUTOIDLE1					CM_AUTOIDLE
#घोषणा CM_AUTOIDLE2					0x0034
#घोषणा CM_AUTOIDLE3					0x0038
#घोषणा CM_CLKSEL					0x0040
#घोषणा CM_CLKSEL1					CM_CLKSEL
#घोषणा CM_CLKSEL2					0x0044
#घोषणा OMAP2_CM_CLKSTCTRL				0x0048

#अगर_अघोषित __ASSEMBLER__

#समावेश <linux/पन.स>

अटल अंतरभूत u32 omap2_cm_पढ़ो_mod_reg(s16 module, u16 idx)
अणु
	वापस पढ़ोl_relaxed(cm_base.va + module + idx);
पूर्ण

अटल अंतरभूत व्योम omap2_cm_ग_लिखो_mod_reg(u32 val, s16 module, u16 idx)
अणु
	ग_लिखोl_relaxed(val, cm_base.va + module + idx);
पूर्ण

/* Read-modअगरy-ग_लिखो a रेजिस्टर in a CM module. Caller must lock */
अटल अंतरभूत u32 omap2_cm_rmw_mod_reg_bits(u32 mask, u32 bits, s16 module,
					    s16 idx)
अणु
	u32 v;

	v = omap2_cm_पढ़ो_mod_reg(module, idx);
	v &= ~mask;
	v |= bits;
	omap2_cm_ग_लिखो_mod_reg(v, module, idx);

	वापस v;
पूर्ण

/* Read a CM रेजिस्टर, AND it, and shअगरt the result करोwn to bit 0 */
अटल अंतरभूत u32 omap2_cm_पढ़ो_mod_bits_shअगरt(s16 करोमुख्य, s16 idx, u32 mask)
अणु
	u32 v;

	v = omap2_cm_पढ़ो_mod_reg(करोमुख्य, idx);
	v &= mask;
	v >>= __ffs(mask);

	वापस v;
पूर्ण

अटल अंतरभूत u32 omap2_cm_set_mod_reg_bits(u32 bits, s16 module, s16 idx)
अणु
	वापस omap2_cm_rmw_mod_reg_bits(bits, bits, module, idx);
पूर्ण

अटल अंतरभूत u32 omap2_cm_clear_mod_reg_bits(u32 bits, s16 module, s16 idx)
अणु
	वापस omap2_cm_rmw_mod_reg_bits(bits, 0x0, module, idx);
पूर्ण

बाह्य पूर्णांक omap2xxx_cm_apll54_enable(व्योम);
बाह्य व्योम omap2xxx_cm_apll54_disable(व्योम);
बाह्य पूर्णांक omap2xxx_cm_apll96_enable(व्योम);
बाह्य व्योम omap2xxx_cm_apll96_disable(व्योम);

#पूर्ण_अगर

/* CM रेजिस्टर bits shared between 24XX and 3430 */

/* CM_CLKSEL_GFX */
#घोषणा OMAP_CLKSEL_GFX_SHIFT				0
#घोषणा OMAP_CLKSEL_GFX_MASK				(0x7 << 0)
#घोषणा OMAP_CLKSEL_GFX_WIDTH				3

/* CM_ICLKEN_GFX */
#घोषणा OMAP_EN_GFX_SHIFT				0
#घोषणा OMAP_EN_GFX_MASK				(1 << 0)

/* CM_IDLEST_GFX */
#घोषणा OMAP_ST_GFX_MASK				(1 << 0)

#पूर्ण_अगर
