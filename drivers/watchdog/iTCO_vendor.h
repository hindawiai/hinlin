<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* iTCO Venकरोr Specअगरic Support hooks */
#अगर_घोषित CONFIG_ITCO_VENDOR_SUPPORT
बाह्य पूर्णांक iTCO_venकरोrsupport;
बाह्य व्योम iTCO_venकरोr_pre_start(काष्ठा resource *, अचिन्हित पूर्णांक);
बाह्य व्योम iTCO_venकरोr_pre_stop(काष्ठा resource *);
बाह्य पूर्णांक iTCO_venकरोr_check_noreboot_on(व्योम);
#अन्यथा
#घोषणा iTCO_venकरोrsupport				0
#घोषणा iTCO_venकरोr_pre_start(acpibase, heartbeat)	अणुपूर्ण
#घोषणा iTCO_venकरोr_pre_stop(acpibase)			अणुपूर्ण
#घोषणा iTCO_venकरोr_check_noreboot_on()			1
				/* 1=check noreboot; 0=करोn't check */
#पूर्ण_अगर
