<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 */

#अगर_अघोषित __BCM47XX_NVRAM_H
#घोषणा __BCM47XX_NVRAM_H

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/vदो_स्मृति.h>

#अगर_घोषित CONFIG_BCM47XX_NVRAM
पूर्णांक bcm47xx_nvram_init_from_mem(u32 base, u32 lim);
पूर्णांक bcm47xx_nvram_दो_पर्या(स्थिर अक्षर *name, अक्षर *val, माप_प्रकार val_len);
पूर्णांक bcm47xx_nvram_gpio_pin(स्थिर अक्षर *name);
अक्षर *bcm47xx_nvram_get_contents(माप_प्रकार *val_len);
अटल अंतरभूत व्योम bcm47xx_nvram_release_contents(अक्षर *nvram)
अणु
	vमुक्त(nvram);
पूर्ण;
#अन्यथा
अटल अंतरभूत पूर्णांक bcm47xx_nvram_init_from_mem(u32 base, u32 lim)
अणु
	वापस -ENOTSUPP;
पूर्ण;
अटल अंतरभूत पूर्णांक bcm47xx_nvram_दो_पर्या(स्थिर अक्षर *name, अक्षर *val,
				       माप_प्रकार val_len)
अणु
	वापस -ENOTSUPP;
पूर्ण;
अटल अंतरभूत पूर्णांक bcm47xx_nvram_gpio_pin(स्थिर अक्षर *name)
अणु
	वापस -ENOTSUPP;
पूर्ण;

अटल अंतरभूत अक्षर *bcm47xx_nvram_get_contents(माप_प्रकार *val_len)
अणु
	वापस शून्य;
पूर्ण;

अटल अंतरभूत व्योम bcm47xx_nvram_release_contents(अक्षर *nvram)
अणु
पूर्ण;
#पूर्ण_अगर

#पूर्ण_अगर /* __BCM47XX_NVRAM_H */
