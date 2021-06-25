<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>

अटल __init पूर्णांक add_pcspkr(व्योम)
अणु
	काष्ठा platक्रमm_device *pd;

	pd = platक्रमm_device_रेजिस्टर_simple("pcspkr", -1, शून्य, 0);

	वापस PTR_ERR_OR_ZERO(pd);
पूर्ण
device_initcall(add_pcspkr);
