<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "bcm47xx_private.h"

#समावेश <linux/gpपन.स>
#समावेश <bcm47xx_board.h>
#समावेश <bcm47xx.h>

अटल व्योम __init bcm47xx_workarounds_enable_usb_घातer(पूर्णांक usb_घातer)
अणु
	पूर्णांक err;

	err = gpio_request_one(usb_घातer, GPIOF_OUT_INIT_HIGH, "usb_power");
	अगर (err)
		pr_err("Failed to request USB power gpio: %d\n", err);
	अन्यथा
		gpio_मुक्त(usb_घातer);
पूर्ण

व्योम __init bcm47xx_workarounds(व्योम)
अणु
	क्रमागत bcm47xx_board board = bcm47xx_board_get();

	चयन (board) अणु
	हाल BCM47XX_BOARD_NETGEAR_WNR3500L:
		bcm47xx_workarounds_enable_usb_घातer(12);
		अवरोध;
	हाल BCM47XX_BOARD_NETGEAR_WNDR3400V2:
	हाल BCM47XX_BOARD_NETGEAR_WNDR3400_V3:
		bcm47xx_workarounds_enable_usb_घातer(21);
		अवरोध;
	शेष:
		/* No workaround(s) needed */
		अवरोध;
	पूर्ण
पूर्ण
