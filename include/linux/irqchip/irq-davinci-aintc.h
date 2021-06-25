<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2019 Texas Instruments
 */

#अगर_अघोषित _LINUX_IRQ_DAVINCI_AINTC_
#घोषणा _LINUX_IRQ_DAVINCI_AINTC_

#समावेश <linux/ioport.h>

/**
 * काष्ठा davinci_aपूर्णांकc_config - configuration data क्रम davinci-aपूर्णांकc driver.
 *
 * @reg: रेजिस्टर range to map
 * @num_irqs: number of HW पूर्णांकerrupts supported by the controller
 * @prios: an array of size num_irqs containing priority settings क्रम
 *         each पूर्णांकerrupt
 */
काष्ठा davinci_aपूर्णांकc_config अणु
	काष्ठा resource reg;
	अचिन्हित पूर्णांक num_irqs;
	u8 *prios;
पूर्ण;

व्योम davinci_aपूर्णांकc_init(स्थिर काष्ठा davinci_aपूर्णांकc_config *config);

#पूर्ण_अगर /* _LINUX_IRQ_DAVINCI_AINTC_ */
