<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * HTC simple EGPIO irq and gpio extender
 */

#अगर_अघोषित __HTC_EGPIO_H__
#घोषणा __HTC_EGPIO_H__

/* Descriptive values क्रम all-in or all-out htc_egpio_chip descriptors. */
#घोषणा HTC_EGPIO_OUTPUT (~0)
#घोषणा HTC_EGPIO_INPUT  0

/**
 * काष्ठा htc_egpio_chip - descriptor to create gpio_chip क्रम रेजिस्टर range
 * @reg_start: index of first रेजिस्टर
 * @gpio_base: gpio number of first pin in this रेजिस्टर range
 * @num_gpios: number of gpios in this रेजिस्टर range, max BITS_PER_LONG
 *    (number of रेजिस्टरs = DIV_ROUND_UP(num_gpios, reg_width))
 * @direction: bitfield, '0' = input, '1' = output,
 */
काष्ठा htc_egpio_chip अणु
	पूर्णांक           reg_start;
	पूर्णांक           gpio_base;
	पूर्णांक           num_gpios;
	अचिन्हित दीर्घ direction;
	अचिन्हित दीर्घ initial_values;
पूर्ण;

/**
 * काष्ठा htc_egpio_platक्रमm_data - description provided by the arch
 * @irq_base: beginning of available IRQs (eg, IRQ_BOARD_START)
 * @num_irqs: number of irqs
 * @reg_width: number of bits per रेजिस्टर, either 8 or 16 bit
 * @bus_width: alignment of the रेजिस्टरs, either 16 or 32 bit
 * @invert_acks: set अगर chip requires writing '0' to ack an irq, instead of '1'
 * @ack_रेजिस्टर: location of the irq/ack रेजिस्टर
 * @chip: poपूर्णांकer to array of htc_egpio_chip descriptors
 * @num_chips: number of egpio chip descriptors
 */
काष्ठा htc_egpio_platक्रमm_data अणु
	पूर्णांक                   bus_width;
	पूर्णांक                   reg_width;

	पूर्णांक                   irq_base;
	पूर्णांक                   num_irqs;
	पूर्णांक                   invert_acks;
	पूर्णांक                   ack_रेजिस्टर;

	काष्ठा htc_egpio_chip *chip;
	पूर्णांक                   num_chips;
पूर्ण;

#पूर्ण_अगर
