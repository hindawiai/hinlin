<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित ASMARM_ARCH_IRDA_H
#घोषणा ASMARM_ARCH_IRDA_H

/* board specअगरic transceiver capabilities */

#घोषणा IR_OFF		1
#घोषणा IR_SIRMODE	2
#घोषणा IR_FIRMODE	4

काष्ठा pxaficp_platक्रमm_data अणु
	पूर्णांक transceiver_cap;
	व्योम (*transceiver_mode)(काष्ठा device *dev, पूर्णांक mode);
	पूर्णांक (*startup)(काष्ठा device *dev);
	व्योम (*shutकरोwn)(काष्ठा device *dev);
	पूर्णांक gpio_pwकरोwn;		/* घातerकरोwn GPIO क्रम the IrDA chip */
	bool gpio_pwकरोwn_inverted;	/* gpio_pwकरोwn is inverted */
पूर्ण;

बाह्य व्योम pxa_set_ficp_info(काष्ठा pxaficp_platक्रमm_data *info);

#अगर defined(CONFIG_PXA25x) || defined(CONFIG_PXA27x)
व्योम pxa2xx_transceiver_mode(काष्ठा device *dev, पूर्णांक mode);
#पूर्ण_अगर

#पूर्ण_अगर
