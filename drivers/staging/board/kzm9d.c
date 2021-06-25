<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Staging board support क्रम KZM9D. Enable not-yet-DT-capable devices here. */

#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश "board.h"

अटल काष्ठा resource usbs1_res[] __initdata = अणु
	DEFINE_RES_MEM(0xe2800000, 0x2000),
	DEFINE_RES_IRQ(159),
पूर्ण;

अटल व्योम __init kzm9d_init(व्योम)
अणु
	board_staging_gic_setup_xlate("arm,pl390", 32);

	अगर (!board_staging_dt_node_available(usbs1_res,
					     ARRAY_SIZE(usbs1_res))) अणु
		board_staging_gic_fixup_resources(usbs1_res,
						  ARRAY_SIZE(usbs1_res));
		platक्रमm_device_रेजिस्टर_simple("emxx_udc", -1, usbs1_res,
						ARRAY_SIZE(usbs1_res));
	पूर्ण
पूर्ण

board_staging("renesas,kzm9d", kzm9d_init);
