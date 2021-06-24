<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2011 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * Copyright 2008 Openmoko, Inc.
 * Copyright 2008 Simtec Electronics
 *	http://armlinux.simtec.co.uk/
 *	Ben Dooks <ben@simtec.co.uk>
 *
 * S3C Platक्रमm - SDHCI (HSMMC) platक्रमm data definitions
 */

#अगर_अघोषित __PLAT_S3C_SDHCI_H
#घोषणा __PLAT_S3C_SDHCI_H __खाता__

#समावेश <linux/platक्रमm_data/mmc-sdhci-s3c.h>
#समावेश "devs.h"

/* s3c_sdhci_set_platdata() - common helper क्रम setting SDHCI platक्रमm data
 * @pd: The शेष platक्रमm data क्रम this device.
 * @set: Poपूर्णांकer to the platक्रमm data to fill in.
 */
बाह्य व्योम s3c_sdhci_set_platdata(काष्ठा s3c_sdhci_platdata *pd,
				    काष्ठा s3c_sdhci_platdata *set);

/**
 * s3c_sdhci0_set_platdata - Set platक्रमm data क्रम S3C SDHCI device.
 * @pd: Platक्रमm data to रेजिस्टर to device.
 *
 * Register the given platक्रमm data क्रम use withe S3C SDHCI device.
 * The call will copy the platक्रमm data, so the board definitions can
 * make the काष्ठाure itself __initdata.
 */
बाह्य व्योम s3c_sdhci0_set_platdata(काष्ठा s3c_sdhci_platdata *pd);
बाह्य व्योम s3c_sdhci1_set_platdata(काष्ठा s3c_sdhci_platdata *pd);
बाह्य व्योम s3c_sdhci2_set_platdata(काष्ठा s3c_sdhci_platdata *pd);
बाह्य व्योम s3c_sdhci3_set_platdata(काष्ठा s3c_sdhci_platdata *pd);

/* Default platक्रमm data, exported so that per-cpu initialisation can
 * set the correct one when there are more than one cpu type selected.
*/

बाह्य काष्ठा s3c_sdhci_platdata s3c_hsmmc0_def_platdata;
बाह्य काष्ठा s3c_sdhci_platdata s3c_hsmmc1_def_platdata;
बाह्य काष्ठा s3c_sdhci_platdata s3c_hsmmc2_def_platdata;
बाह्य काष्ठा s3c_sdhci_platdata s3c_hsmmc3_def_platdata;

/* Helper function availability */

बाह्य व्योम s3c2416_setup_sdhci0_cfg_gpio(काष्ठा platक्रमm_device *, पूर्णांक w);
बाह्य व्योम s3c2416_setup_sdhci1_cfg_gpio(काष्ठा platक्रमm_device *, पूर्णांक w);
बाह्य व्योम s3c64xx_setup_sdhci0_cfg_gpio(काष्ठा platक्रमm_device *, पूर्णांक w);
बाह्य व्योम s3c64xx_setup_sdhci1_cfg_gpio(काष्ठा platक्रमm_device *, पूर्णांक w);
बाह्य व्योम s3c64xx_setup_sdhci2_cfg_gpio(काष्ठा platक्रमm_device *, पूर्णांक w);

/* S3C2416 SDHCI setup */

#अगर_घोषित CONFIG_S3C2416_SETUP_SDHCI
अटल अंतरभूत व्योम s3c2416_शेष_sdhci0(व्योम)
अणु
#अगर_घोषित CONFIG_S3C_DEV_HSMMC
	s3c_hsmmc0_def_platdata.cfg_gpio = s3c2416_setup_sdhci0_cfg_gpio;
#पूर्ण_अगर /* CONFIG_S3C_DEV_HSMMC */
पूर्ण

अटल अंतरभूत व्योम s3c2416_शेष_sdhci1(व्योम)
अणु
#अगर_घोषित CONFIG_S3C_DEV_HSMMC1
	s3c_hsmmc1_def_platdata.cfg_gpio = s3c2416_setup_sdhci1_cfg_gpio;
#पूर्ण_अगर /* CONFIG_S3C_DEV_HSMMC1 */
पूर्ण

#अन्यथा
अटल अंतरभूत व्योम s3c2416_शेष_sdhci0(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम s3c2416_शेष_sdhci1(व्योम) अणु पूर्ण

#पूर्ण_अगर /* CONFIG_S3C2416_SETUP_SDHCI */

/* S3C64XX SDHCI setup */

#अगर_घोषित CONFIG_S3C64XX_SETUP_SDHCI
अटल अंतरभूत व्योम s3c6400_शेष_sdhci0(व्योम)
अणु
#अगर_घोषित CONFIG_S3C_DEV_HSMMC
	s3c_hsmmc0_def_platdata.cfg_gpio = s3c64xx_setup_sdhci0_cfg_gpio;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम s3c6400_शेष_sdhci1(व्योम)
अणु
#अगर_घोषित CONFIG_S3C_DEV_HSMMC1
	s3c_hsmmc1_def_platdata.cfg_gpio = s3c64xx_setup_sdhci1_cfg_gpio;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम s3c6400_शेष_sdhci2(व्योम)
अणु
#अगर_घोषित CONFIG_S3C_DEV_HSMMC2
	s3c_hsmmc2_def_platdata.cfg_gpio = s3c64xx_setup_sdhci2_cfg_gpio;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम s3c6410_शेष_sdhci0(व्योम)
अणु
#अगर_घोषित CONFIG_S3C_DEV_HSMMC
	s3c_hsmmc0_def_platdata.cfg_gpio = s3c64xx_setup_sdhci0_cfg_gpio;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम s3c6410_शेष_sdhci1(व्योम)
अणु
#अगर_घोषित CONFIG_S3C_DEV_HSMMC1
	s3c_hsmmc1_def_platdata.cfg_gpio = s3c64xx_setup_sdhci1_cfg_gpio;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम s3c6410_शेष_sdhci2(व्योम)
अणु
#अगर_घोषित CONFIG_S3C_DEV_HSMMC2
	s3c_hsmmc2_def_platdata.cfg_gpio = s3c64xx_setup_sdhci2_cfg_gpio;
#पूर्ण_अगर
पूर्ण

#अन्यथा
अटल अंतरभूत व्योम s3c6410_शेष_sdhci0(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम s3c6410_शेष_sdhci1(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम s3c6410_शेष_sdhci2(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम s3c6400_शेष_sdhci0(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम s3c6400_शेष_sdhci1(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम s3c6400_शेष_sdhci2(व्योम) अणु पूर्ण

#पूर्ण_अगर /* CONFIG_S3C64XX_SETUP_SDHCI */

अटल अंतरभूत व्योम s3c_sdhci_setname(पूर्णांक id, अक्षर *name)
अणु
	चयन (id) अणु
#अगर_घोषित CONFIG_S3C_DEV_HSMMC
	हाल 0:
		s3c_device_hsmmc0.name = name;
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_S3C_DEV_HSMMC1
	हाल 1:
		s3c_device_hsmmc1.name = name;
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_S3C_DEV_HSMMC2
	हाल 2:
		s3c_device_hsmmc2.name = name;
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_S3C_DEV_HSMMC3
	हाल 3:
		s3c_device_hsmmc3.name = name;
		अवरोध;
#पूर्ण_अगर
	शेष:
		अवरोध;
	पूर्ण
पूर्ण
#पूर्ण_अगर /* __PLAT_S3C_SDHCI_H */
