<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*

    bttv-अगर.c  --  old gpio पूर्णांकerface to other kernel modules
		   करोn't use in new code, will go away in 2.7
		   have a look at bttv-gpio.c instead.

    bttv - Bt848 frame grabber driver

    Copyright (C) 1996,97,98 Ralph  Metzler (rjkm@thp.uni-koeln.de)
			   & Marcus Metzler (mocm@thp.uni-koeln.de)
    (c) 1999-2003 Gerd Knorr <kraxel@bytesex.org>


*/

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <यंत्र/पन.स>

#समावेश "bttvp.h"

EXPORT_SYMBOL(bttv_get_pcidev);
EXPORT_SYMBOL(bttv_gpio_enable);
EXPORT_SYMBOL(bttv_पढ़ो_gpio);
EXPORT_SYMBOL(bttv_ग_लिखो_gpio);

/* ----------------------------------------------------------------------- */
/* Exported functions - क्रम other modules which want to access the         */
/*                      gpio ports (IR क्रम example)                        */
/*                      see bttv.h क्रम comments                            */

काष्ठा pci_dev* bttv_get_pcidev(अचिन्हित पूर्णांक card)
अणु
	अगर (card >= bttv_num)
		वापस शून्य;
	अगर (!bttvs[card])
		वापस शून्य;

	वापस bttvs[card]->c.pci;
पूर्ण


पूर्णांक bttv_gpio_enable(अचिन्हित पूर्णांक card, अचिन्हित दीर्घ mask, अचिन्हित दीर्घ data)
अणु
	काष्ठा bttv *btv;

	अगर (card >= bttv_num) अणु
		वापस -EINVAL;
	पूर्ण

	btv = bttvs[card];
	अगर (!btv)
		वापस -ENODEV;

	gpio_inout(mask,data);
	अगर (bttv_gpio)
		bttv_gpio_tracking(btv,"extern enable");
	वापस 0;
पूर्ण

पूर्णांक bttv_पढ़ो_gpio(अचिन्हित पूर्णांक card, अचिन्हित दीर्घ *data)
अणु
	काष्ठा bttv *btv;

	अगर (card >= bttv_num) अणु
		वापस -EINVAL;
	पूर्ण

	btv = bttvs[card];
	अगर (!btv)
		वापस -ENODEV;

	अगर(btv->shutकरोwn) अणु
		वापस -ENODEV;
	पूर्ण

/* prior setting BT848_GPIO_REG_INP is (probably) not needed
   because we set direct input on init */
	*data = gpio_पढ़ो();
	वापस 0;
पूर्ण

पूर्णांक bttv_ग_लिखो_gpio(अचिन्हित पूर्णांक card, अचिन्हित दीर्घ mask, अचिन्हित दीर्घ data)
अणु
	काष्ठा bttv *btv;

	अगर (card >= bttv_num) अणु
		वापस -EINVAL;
	पूर्ण

	btv = bttvs[card];
	अगर (!btv)
		वापस -ENODEV;

/* prior setting BT848_GPIO_REG_INP is (probably) not needed
   because direct input is set on init */
	gpio_bits(mask,data);
	अगर (bttv_gpio)
		bttv_gpio_tracking(btv,"extern write");
	वापस 0;
पूर्ण
