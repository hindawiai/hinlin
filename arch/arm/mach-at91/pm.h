<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * AT91 Power Management
 *
 * Copyright (C) 2005 David Brownell
 */
#अगर_अघोषित __ARCH_ARM_MACH_AT91_PM
#घोषणा __ARCH_ARM_MACH_AT91_PM

#समावेश <यंत्र/proc-fns.h>

#समावेश <linux/mfd/syscon/aपंचांगel-mc.h>
#समावेश <soc/at91/at91sam9_ddrsdr.h>
#समावेश <soc/at91/at91sam9_sdramc.h>

#घोषणा AT91_MEMCTRL_MC		0
#घोषणा AT91_MEMCTRL_SDRAMC	1
#घोषणा AT91_MEMCTRL_DDRSDR	2

#घोषणा	AT91_PM_STANDBY		0x00
#घोषणा AT91_PM_ULP0		0x01
#घोषणा AT91_PM_ULP0_FAST	0x02
#घोषणा AT91_PM_ULP1		0x03
#घोषणा	AT91_PM_BACKUP		0x04

#अगर_अघोषित __ASSEMBLY__
काष्ठा at91_pm_data अणु
	व्योम __iomem *pmc;
	व्योम __iomem *ramc[2];
	अचिन्हित दीर्घ uhp_udp_mask;
	अचिन्हित पूर्णांक memctrl;
	अचिन्हित पूर्णांक mode;
	व्योम __iomem *shdwc;
	व्योम __iomem *sfrbu;
	अचिन्हित पूर्णांक standby_mode;
	अचिन्हित पूर्णांक suspend_mode;
	अचिन्हित पूर्णांक pmc_mckr_offset;
	अचिन्हित पूर्णांक pmc_version;
पूर्ण;
#पूर्ण_अगर

#पूर्ण_अगर
