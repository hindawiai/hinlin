<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LMC_H_
#घोषणा _LMC_H_

#समावेश "lmc_var.h"

/*
 * prototypes क्रम everyone
 */
पूर्णांक lmc_probe(काष्ठा net_device * dev);
अचिन्हित lmc_mii_पढ़ोreg(lmc_softc_t * स्थिर sc, अचिन्हित
      			  devaddr, अचिन्हित regno);
व्योम lmc_mii_ग_लिखोreg(lmc_softc_t * स्थिर sc, अचिन्हित devaddr,
			       अचिन्हित regno, अचिन्हित data);
व्योम lmc_led_on(lmc_softc_t * स्थिर, u32);
व्योम lmc_led_off(lmc_softc_t * स्थिर, u32);
अचिन्हित lmc_mii_पढ़ोreg(lmc_softc_t * स्थिर, अचिन्हित, अचिन्हित);
व्योम lmc_mii_ग_लिखोreg(lmc_softc_t * स्थिर, अचिन्हित, अचिन्हित, अचिन्हित);
व्योम lmc_gpio_mkinput(lmc_softc_t * स्थिर sc, u32 bits);
व्योम lmc_gpio_mkoutput(lmc_softc_t * स्थिर sc, u32 bits);

पूर्णांक lmc_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd);

बाह्य lmc_media_t lmc_ds3_media;
बाह्य lmc_media_t lmc_ssi_media;
बाह्य lmc_media_t lmc_t1_media;
बाह्य lmc_media_t lmc_hssi_media;

#अगर_घोषित _DBG_EVENTLOG
अटल व्योम lmcEventLog(u32 EventNum, u32 arg2, u32 arg3);
#पूर्ण_अगर

#पूर्ण_अगर
