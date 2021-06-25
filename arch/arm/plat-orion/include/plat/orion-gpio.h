<शैली गुरु>
/*
 * arch/arm/plat-orion/include/plat/orion-gpपन.स
 *
 * Marvell Orion SoC GPIO handling.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#अगर_अघोषित __PLAT_GPIO_H
#घोषणा __PLAT_GPIO_H

#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/irqकरोमुख्य.h>

काष्ठा gpio_desc;

/*
 * Orion-specअगरic GPIO API extensions.
 */
व्योम orion_gpio_set_unused(अचिन्हित pin);
व्योम orion_gpio_set_blink(अचिन्हित pin, पूर्णांक blink);
पूर्णांक orion_gpio_led_blink_set(काष्ठा gpio_desc *desc, पूर्णांक state,
	अचिन्हित दीर्घ *delay_on, अचिन्हित दीर्घ *delay_off);

#घोषणा GPIO_INPUT_OK		(1 << 0)
#घोषणा GPIO_OUTPUT_OK		(1 << 1)
व्योम orion_gpio_set_valid(अचिन्हित pin, पूर्णांक mode);

/* Initialize gpiolib. */
व्योम __init orion_gpio_init(काष्ठा device_node *np,
			    पूर्णांक gpio_base, पूर्णांक ngpio,
			    व्योम __iomem *base, पूर्णांक mask_offset,
			    पूर्णांक secondary_irq_base,
			    पूर्णांक irq[4]);

#पूर्ण_अगर
