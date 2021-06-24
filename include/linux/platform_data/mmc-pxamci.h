<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित ASMARM_ARCH_MMC_H
#घोषणा ASMARM_ARCH_MMC_H

#समावेश <linux/mmc/host.h>
#समावेश <linux/पूर्णांकerrupt.h>

काष्ठा device;
काष्ठा mmc_host;

काष्ठा pxamci_platक्रमm_data अणु
	अचिन्हित पूर्णांक ocr_mask;			/* available voltages */
	अचिन्हित दीर्घ detect_delay_ms;		/* delay in millisecond beक्रमe detecting cards after पूर्णांकerrupt */
	पूर्णांक (*init)(काष्ठा device *, irq_handler_t , व्योम *);
	पूर्णांक (*get_ro)(काष्ठा device *);
	पूर्णांक (*setघातer)(काष्ठा device *, अचिन्हित पूर्णांक);
	व्योम (*निकास)(काष्ठा device *, व्योम *);
	bool gpio_card_ro_invert;		/* gpio ro is inverted */
पूर्ण;

बाह्य व्योम pxa_set_mci_info(काष्ठा pxamci_platक्रमm_data *info);
बाह्य व्योम pxa3xx_set_mci2_info(काष्ठा pxamci_platक्रमm_data *info);
बाह्य व्योम pxa3xx_set_mci3_info(काष्ठा pxamci_platक्रमm_data *info);

#पूर्ण_अगर
