<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * timb_gpपन.स timberdale FPGA GPIO driver, platक्रमm data definition
 * Copyright (c) 2009 Intel Corporation
 */

#अगर_अघोषित _LINUX_TIMB_GPIO_H
#घोषणा _LINUX_TIMB_GPIO_H

/**
 * काष्ठा timbgpio_platक्रमm_data - Platक्रमm data of the Timberdale GPIO driver
 * @gpio_base		The number of the first GPIO pin, set to -1 क्रम
 *			dynamic number allocation.
 * @nr_pins		Number of pins that is supported by the hardware (1-32)
 * @irq_base		If IRQ is supported by the hardware, this is the base
 *			number of IRQ:s. One IRQ per pin will be used. Set to
 *			-1 अगर IRQ:s is not supported.
 */
काष्ठा timbgpio_platक्रमm_data अणु
	पूर्णांक gpio_base;
	पूर्णांक nr_pins;
	पूर्णांक irq_base;
पूर्ण;

#पूर्ण_अगर
