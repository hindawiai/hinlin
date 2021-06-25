<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_HTCPLD_H
#घोषणा __LINUX_HTCPLD_H

काष्ठा htcpld_chip_platक्रमm_data अणु
	अचिन्हित पूर्णांक addr;
	अचिन्हित पूर्णांक reset;
	अचिन्हित पूर्णांक num_gpios;
	अचिन्हित पूर्णांक gpio_out_base;
	अचिन्हित पूर्णांक gpio_in_base;
	अचिन्हित पूर्णांक irq_base;
	अचिन्हित पूर्णांक num_irqs;
पूर्ण;

काष्ठा htcpld_core_platक्रमm_data अणु
	अचिन्हित पूर्णांक                      पूर्णांक_reset_gpio_hi;
	अचिन्हित पूर्णांक                      पूर्णांक_reset_gpio_lo;
	अचिन्हित पूर्णांक                      i2c_adapter_id;

	काष्ठा htcpld_chip_platक्रमm_data  *chip;
	अचिन्हित पूर्णांक                      num_chip;
पूर्ण;

#पूर्ण_अगर /* __LINUX_HTCPLD_H */

