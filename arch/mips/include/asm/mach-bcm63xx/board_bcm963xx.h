<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित BOARD_BCM963XX_H_
#घोषणा BOARD_BCM963XX_H_

#समावेश <linux/types.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/leds.h>
#समावेश <bcm63xx_dev_enet.h>
#समावेश <bcm63xx_dev_usb_usbd.h>

/*
 * flash mapping
 */
#घोषणा BCM963XX_CFE_VERSION_OFFSET	0x570
#घोषणा BCM963XX_NVRAM_OFFSET		0x580

/*
 * board definition
 */
काष्ठा board_info अणु
	u8		name[16];
	अचिन्हित पूर्णांक	expected_cpu_id;

	/* enabled feature/device */
	अचिन्हित पूर्णांक	has_enet0:1;
	अचिन्हित पूर्णांक	has_enet1:1;
	अचिन्हित पूर्णांक	has_enetsw:1;
	अचिन्हित पूर्णांक	has_pci:1;
	अचिन्हित पूर्णांक	has_pccard:1;
	अचिन्हित पूर्णांक	has_ohci0:1;
	अचिन्हित पूर्णांक	has_ehci0:1;
	अचिन्हित पूर्णांक	has_usbd:1;
	अचिन्हित पूर्णांक	has_uart0:1;
	अचिन्हित पूर्णांक	has_uart1:1;

	/* ethernet config */
	काष्ठा bcm63xx_enet_platक्रमm_data enet0;
	काष्ठा bcm63xx_enet_platक्रमm_data enet1;
	काष्ठा bcm63xx_enetsw_platक्रमm_data enetsw;

	/* USB config */
	काष्ठा bcm63xx_usbd_platक्रमm_data usbd;

	/* GPIO LEDs */
	काष्ठा gpio_led leds[5];

	/* External PHY reset GPIO */
	अचिन्हित पूर्णांक ephy_reset_gpio;

	/* External PHY reset GPIO flags from gpपन.स */
	अचिन्हित दीर्घ ephy_reset_gpio_flags;
पूर्ण;

#पूर्ण_अगर /* ! BOARD_BCM963XX_H_ */
