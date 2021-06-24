<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2007 Aurelien Jarno <aurelien@aurel32.net>
 */

#अगर_अघोषित __ASM_BCM47XX_H
#घोषणा __ASM_BCM47XX_H

#समावेश <linux/ssb/ssb.h>
#समावेश <linux/bcma/bcma.h>
#समावेश <linux/bcma/bcma_soc.h>
#समावेश <linux/bcm47xx_nvram.h>
#समावेश <linux/bcm47xx_sprom.h>

क्रमागत bcm47xx_bus_type अणु
#अगर_घोषित CONFIG_BCM47XX_SSB
	BCM47XX_BUS_TYPE_SSB,
#पूर्ण_अगर
#अगर_घोषित CONFIG_BCM47XX_BCMA
	BCM47XX_BUS_TYPE_BCMA,
#पूर्ण_अगर
पूर्ण;

जोड़ bcm47xx_bus अणु
#अगर_घोषित CONFIG_BCM47XX_SSB
	काष्ठा ssb_bus ssb;
#पूर्ण_अगर
#अगर_घोषित CONFIG_BCM47XX_BCMA
	काष्ठा bcma_soc bcma;
#पूर्ण_अगर
पूर्ण;

बाह्य जोड़ bcm47xx_bus bcm47xx_bus;
बाह्य क्रमागत bcm47xx_bus_type bcm47xx_bus_type;

व्योम bcm47xx_set_प्रणाली_type(u16 chip_id);

#पूर्ण_अगर /* __ASM_BCM47XX_H */
