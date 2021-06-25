<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Author: Kevin Wells <kevin.wells@nxp.com>
 *
 * Copyright (C) 2010 NXP Semiconductors
 */

#अगर_अघोषित __SOC_LPC32XX_MISC_H
#घोषणा __SOC_LPC32XX_MISC_H

#समावेश <linux/types.h>
#समावेश <linux/phy.h>

#अगर_घोषित CONFIG_ARCH_LPC32XX
बाह्य u32 lpc32xx_वापस_iram(व्योम __iomem **mapbase, dma_addr_t *dmaaddr);
बाह्य व्योम lpc32xx_set_phy_पूर्णांकerface_mode(phy_पूर्णांकerface_t mode);
बाह्य व्योम lpc32xx_loopback_set(resource_माप_प्रकार mapbase, पूर्णांक state);
#अन्यथा
अटल अंतरभूत u32 lpc32xx_वापस_iram(व्योम __iomem **mapbase, dma_addr_t *dmaaddr)
अणु
	*mapbase = शून्य;
	*dmaaddr = 0;
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम lpc32xx_set_phy_पूर्णांकerface_mode(phy_पूर्णांकerface_t mode)
अणु
पूर्ण
अटल अंतरभूत व्योम lpc32xx_loopback_set(resource_माप_प्रकार mapbase, पूर्णांक state)
अणु
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर  /* __SOC_LPC32XX_MISC_H */
