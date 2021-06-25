<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Virtual EISA root driver.
 * Acts as a placeholder अगर we करोn't have a proper EISA bridge.
 *
 * (C) 2003 Marc Zyngier <maz@wild-wind.fr.eu.org>
 * modअगरied क्रम SNI usage by Thomas Bogenकरोerfer
 */

#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/eisa.h>
#समावेश <linux/init.h>

/* The शेष EISA device parent (भव root device).
 * Now use a platक्रमm device, since that's the obvious choice. */

अटल काष्ठा platक्रमm_device eisa_root_dev = अणु
	.name = "eisa",
	.id   = 0,
पूर्ण;

अटल काष्ठा eisa_root_device eisa_bus_root = अणु
	.dev	       = &eisa_root_dev.dev,
	.bus_base_addr = 0,
	.res	       = &ioport_resource,
	.slots	       = EISA_MAX_SLOTS,
	.dma_mask      = 0xffffffff,
	.क्रमce_probe   = 1,
पूर्ण;

पूर्णांक __init sni_eisa_root_init(व्योम)
अणु
	पूर्णांक r;

	r = platक्रमm_device_रेजिस्टर(&eisa_root_dev);
	अगर (!r)
		वापस r;

	dev_set_drvdata(&eisa_root_dev.dev, &eisa_bus_root);

	अगर (eisa_root_रेजिस्टर(&eisa_bus_root)) अणु
		/* A real bridge may have been रेजिस्टरed beक्रमe
		 * us. So quietly unरेजिस्टर. */
		platक्रमm_device_unरेजिस्टर(&eisa_root_dev);
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण
