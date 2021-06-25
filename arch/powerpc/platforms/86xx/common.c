<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Routines common to most mpc86xx-based boards.
 */

#समावेश <linux/of_platक्रमm.h>
#समावेश <यंत्र/synch.h>

#समावेश "mpc86xx.h"

अटल स्थिर काष्ठा of_device_id mpc86xx_common_ids[] __initस्थिर = अणु
	अणु .type = "soc", पूर्ण,
	अणु .compatible = "soc", पूर्ण,
	अणु .compatible = "simple-bus", पूर्ण,
	अणु .name = "localbus", पूर्ण,
	अणु .compatible = "gianfar", पूर्ण,
	अणु .compatible = "fsl,mpc8641-pcie", पूर्ण,
	अणुपूर्ण,
पूर्ण;

पूर्णांक __init mpc86xx_common_publish_devices(व्योम)
अणु
	वापस of_platक्रमm_bus_probe(शून्य, mpc86xx_common_ids, शून्य);
पूर्ण

दीर्घ __init mpc86xx_समय_init(व्योम)
अणु
	अचिन्हित पूर्णांक temp;

	/* Set the समय base to zero */
	mtspr(SPRN_TBWL, 0);
	mtspr(SPRN_TBWU, 0);

	temp = mfspr(SPRN_HID0);
	temp |= HID0_TBEN;
	mtspr(SPRN_HID0, temp);
	isync();

	वापस 0;
पूर्ण
