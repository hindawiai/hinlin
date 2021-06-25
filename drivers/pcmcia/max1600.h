<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित MAX1600_H
#घोषणा MAX1600_H

काष्ठा gpio_desc;

क्रमागत अणु
	MAX1600_GPIO_0VCC = 0,
	MAX1600_GPIO_1VCC,
	MAX1600_GPIO_0VPP,
	MAX1600_GPIO_1VPP,
	MAX1600_GPIO_MAX,

	MAX1600_CHAN_A,
	MAX1600_CHAN_B,

	MAX1600_CODE_LOW,
	MAX1600_CODE_HIGH,
पूर्ण;

काष्ठा max1600 अणु
	काष्ठा gpio_desc *gpio[MAX1600_GPIO_MAX];
	काष्ठा device *dev;
	अचिन्हित पूर्णांक code;
पूर्ण;

पूर्णांक max1600_init(काष्ठा device *dev, काष्ठा max1600 **ptr,
	अचिन्हित पूर्णांक channel, अचिन्हित पूर्णांक code);

पूर्णांक max1600_configure(काष्ठा max1600 *, अचिन्हित पूर्णांक vcc, अचिन्हित पूर्णांक vpp);

#पूर्ण_अगर
