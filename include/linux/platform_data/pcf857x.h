<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_PCF857X_H
#घोषणा __LINUX_PCF857X_H

/**
 * काष्ठा pcf857x_platक्रमm_data - data to set up pcf857x driver
 * @gpio_base: number of the chip's first GPIO
 * @n_latch: optional bit-inverse of initial रेजिस्टर value; अगर
 *	you leave this initialized to zero the driver will act
 *	like the chip was just reset
 * @setup: optional callback issued once the GPIOs are valid
 * @tearकरोwn: optional callback issued beक्रमe the GPIOs are invalidated
 * @context: optional parameter passed to setup() and tearकरोwn()
 *
 * In addition to the I2C_BOARD_INFO() state appropriate to each chip,
 * the i2c_board_info used with the pcf875x driver must provide its
 * platक्रमm_data (poपूर्णांकer to one of these काष्ठाures) with at least
 * the gpio_base value initialized.
 *
 * The @setup callback may be used with the kind of board-specअगरic glue
 * which hands the (now-valid) GPIOs to other drivers, or which माला_दो
 * devices in their initial states using these GPIOs.
 *
 * These GPIO chips are only "quasi-bidirectional"; पढ़ो the chip specs
 * to understand the behavior.  They करोn't have separate रेजिस्टरs to
 * record which pins are used क्रम input or output, record which output
 * values are driven, or provide access to input values.  That must be
 * inferred by पढ़ोing the chip's value and knowing the last value written
 * to it.  If you leave n_latch initialized to zero, that last written
 * value is presumed to be all ones (as अगर the chip were just reset).
 */
काष्ठा pcf857x_platक्रमm_data अणु
	अचिन्हित	gpio_base;
	अचिन्हित	n_latch;

	पूर्णांक		(*setup)(काष्ठा i2c_client *client,
					पूर्णांक gpio, अचिन्हित ngpio,
					व्योम *context);
	पूर्णांक		(*tearकरोwn)(काष्ठा i2c_client *client,
					पूर्णांक gpio, अचिन्हित ngpio,
					व्योम *context);
	व्योम		*context;
पूर्ण;

#पूर्ण_अगर /* __LINUX_PCF857X_H */
