<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __BRCMSTB_SOC_H
#घोषणा __BRCMSTB_SOC_H

#समावेश <linux/kconfig.h>

अटल अंतरभूत u32 BRCM_ID(u32 reg)
अणु
	वापस reg >> 28 ? reg >> 16 : reg >> 8;
पूर्ण

अटल अंतरभूत u32 BRCM_REV(u32 reg)
अणु
	वापस reg & 0xff;
पूर्ण

#अगर IS_ENABLED(CONFIG_SOC_BRCMSTB)

/*
 * Helper functions क्रम getting family or product id from the
 * SoC driver.
 */
u32 brcmstb_get_family_id(व्योम);
u32 brcmstb_get_product_id(व्योम);

#अन्यथा
अटल अंतरभूत u32 brcmstb_get_family_id(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत u32 brcmstb_get_product_id(व्योम)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __BRCMSTB_SOC_H */
