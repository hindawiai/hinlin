<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2019 Texas Instruments
 */

#अगर_अघोषित _LINUX_IRQ_DAVINCI_CP_INTC_
#घोषणा _LINUX_IRQ_DAVINCI_CP_INTC_

#समावेश <linux/ioport.h>

/**
 * काष्ठा davinci_cp_पूर्णांकc_config - configuration data क्रम davinci-cp-पूर्णांकc
 *                                 driver.
 *
 * @reg: रेजिस्टर range to map
 * @num_irqs: number of HW पूर्णांकerrupts supported by the controller
 */
काष्ठा davinci_cp_पूर्णांकc_config अणु
	काष्ठा resource reg;
	अचिन्हित पूर्णांक num_irqs;
पूर्ण;

पूर्णांक davinci_cp_पूर्णांकc_init(स्थिर काष्ठा davinci_cp_पूर्णांकc_config *config);

#पूर्ण_अगर /* _LINUX_IRQ_DAVINCI_CP_INTC_ */
