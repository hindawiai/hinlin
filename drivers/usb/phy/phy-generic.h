<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _PHY_GENERIC_H_
#घोषणा _PHY_GENERIC_H_

#समावेश <linux/usb/usb_phy_generic.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/regulator/consumer.h>

काष्ठा usb_phy_generic अणु
	काष्ठा usb_phy phy;
	काष्ठा device *dev;
	काष्ठा clk *clk;
	काष्ठा regulator *vcc;
	काष्ठा gpio_desc *gpiod_reset;
	काष्ठा gpio_desc *gpiod_vbus;
	काष्ठा regulator *vbus_draw;
	bool vbus_draw_enabled;
	अचिन्हित दीर्घ mA;
	अचिन्हित पूर्णांक vbus;
पूर्ण;

पूर्णांक usb_gen_phy_init(काष्ठा usb_phy *phy);
व्योम usb_gen_phy_shutकरोwn(काष्ठा usb_phy *phy);

पूर्णांक usb_phy_gen_create_phy(काष्ठा device *dev, काष्ठा usb_phy_generic *nop);

#पूर्ण_अगर
