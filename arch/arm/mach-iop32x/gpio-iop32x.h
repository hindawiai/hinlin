<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
अटल काष्ठा resource iop32x_gpio_res[] = अणु
	DEFINE_RES_MEM((IOP3XX_PERIPHERAL_PHYS_BASE + 0x07c4), 0x10),
पूर्ण;

अटल अंतरभूत व्योम रेजिस्टर_iop32x_gpio(व्योम)
अणु
	platक्रमm_device_रेजिस्टर_simple("gpio-iop", 0,
					iop32x_gpio_res,
					ARRAY_SIZE(iop32x_gpio_res));
पूर्ण
