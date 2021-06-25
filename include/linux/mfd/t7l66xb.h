<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * This file contains the definitions क्रम the T7L66XB
 *
 * (C) Copyright 2005 Ian Molton <spyro@f2s.com>
 */
#अगर_अघोषित MFD_T7L66XB_H
#घोषणा MFD_T7L66XB_H

#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/पंचांगपन.स>

काष्ठा t7l66xb_platक्रमm_data अणु
	पूर्णांक (*enable)(काष्ठा platक्रमm_device *dev);
	पूर्णांक (*disable)(काष्ठा platक्रमm_device *dev);
	पूर्णांक (*suspend)(काष्ठा platक्रमm_device *dev);
	पूर्णांक (*resume)(काष्ठा platक्रमm_device *dev);

	पूर्णांक irq_base; /* The base क्रम subdevice irqs */

	काष्ठा पंचांगio_nand_data *nand_data;
पूर्ण;


#घोषणा IRQ_T7L66XB_MMC        (1)
#घोषणा IRQ_T7L66XB_न_अंकD       (3)

#घोषणा T7L66XB_NR_IRQS	8

#पूर्ण_अगर
