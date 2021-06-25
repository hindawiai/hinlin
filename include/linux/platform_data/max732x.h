<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_I2C_MAX732X_H
#घोषणा __LINUX_I2C_MAX732X_H

/* platक्रमm data क्रम the MAX732x 8/16-bit I/O expander driver */

काष्ठा max732x_platक्रमm_data अणु
	/* number of the first GPIO */
	अचिन्हित	gpio_base;

	/* पूर्णांकerrupt base */
	पूर्णांक		irq_base;

	व्योम		*context;	/* param to setup/tearकरोwn */

	पूर्णांक		(*setup)(काष्ठा i2c_client *client,
				अचिन्हित gpio, अचिन्हित ngpio,
				व्योम *context);
	पूर्णांक		(*tearकरोwn)(काष्ठा i2c_client *client,
				अचिन्हित gpio, अचिन्हित ngpio,
				व्योम *context);
पूर्ण;
#पूर्ण_अगर /* __LINUX_I2C_MAX732X_H */
