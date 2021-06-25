<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 */

#अगर_अघोषित __BCM47XX_SPROM_H
#घोषणा __BCM47XX_SPROM_H

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/vदो_स्मृति.h>

काष्ठा ssb_sprom;

#अगर_घोषित CONFIG_BCM47XX_SPROM
व्योम bcm47xx_fill_sprom(काष्ठा ssb_sprom *sprom, स्थिर अक्षर *prefix,
			bool fallback);
पूर्णांक bcm47xx_sprom_रेजिस्टर_fallbacks(व्योम);
#अन्यथा
अटल अंतरभूत व्योम bcm47xx_fill_sprom(काष्ठा ssb_sprom *sprom,
				      स्थिर अक्षर *prefix,
				      bool fallback)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक bcm47xx_sprom_रेजिस्टर_fallbacks(व्योम)
अणु
	वापस -ENOTSUPP;
पूर्ण;
#पूर्ण_अगर

#पूर्ण_अगर /* __BCM47XX_SPROM_H */
