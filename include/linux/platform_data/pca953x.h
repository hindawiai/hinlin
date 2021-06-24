<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_PCA953X_H
#घोषणा _LINUX_PCA953X_H

#समावेश <linux/types.h>
#समावेश <linux/i2c.h>

/* platक्रमm data क्रम the PCA9539 16-bit I/O expander driver */

काष्ठा pca953x_platक्रमm_data अणु
	/* number of the first GPIO */
	अचिन्हित	gpio_base;

	/* initial polarity inversion setting */
	u32		invert;

	/* पूर्णांकerrupt base */
	पूर्णांक		irq_base;

	व्योम		*context;	/* param to setup/tearकरोwn */

	पूर्णांक		(*setup)(काष्ठा i2c_client *client,
				अचिन्हित gpio, अचिन्हित ngpio,
				व्योम *context);
	पूर्णांक		(*tearकरोwn)(काष्ठा i2c_client *client,
				अचिन्हित gpio, अचिन्हित ngpio,
				व्योम *context);
	स्थिर अक्षर	*स्थिर *names;
पूर्ण;

#पूर्ण_अगर /* _LINUX_PCA953X_H */
