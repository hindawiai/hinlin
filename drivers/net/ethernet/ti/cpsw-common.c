<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/mfd/syscon.h>

#समावेश "cpsw.h"

#घोषणा CTRL_MAC_LO_REG(offset, id) ((offset) + 0x8 * (id))
#घोषणा CTRL_MAC_HI_REG(offset, id) ((offset) + 0x8 * (id) + 0x4)

अटल पूर्णांक davinci_emac_3517_get_macid(काष्ठा device *dev, u16 offset,
				       पूर्णांक slave, u8 *mac_addr)
अणु
	u32 macid_lsb;
	u32 macid_msb;
	काष्ठा regmap *syscon;

	syscon = syscon_regmap_lookup_by_phandle(dev->of_node, "syscon");
	अगर (IS_ERR(syscon)) अणु
		अगर (PTR_ERR(syscon) == -ENODEV)
			वापस 0;
		वापस PTR_ERR(syscon);
	पूर्ण

	regmap_पढ़ो(syscon, CTRL_MAC_LO_REG(offset, slave), &macid_lsb);
	regmap_पढ़ो(syscon, CTRL_MAC_HI_REG(offset, slave), &macid_msb);

	mac_addr[0] = (macid_msb >> 16) & 0xff;
	mac_addr[1] = (macid_msb >> 8)  & 0xff;
	mac_addr[2] = macid_msb & 0xff;
	mac_addr[3] = (macid_lsb >> 16) & 0xff;
	mac_addr[4] = (macid_lsb >> 8)  & 0xff;
	mac_addr[5] = macid_lsb & 0xff;

	वापस 0;
पूर्ण

अटल पूर्णांक cpsw_am33xx_cm_get_macid(काष्ठा device *dev, u16 offset, पूर्णांक slave,
				    u8 *mac_addr)
अणु
	u32 macid_lo;
	u32 macid_hi;
	काष्ठा regmap *syscon;

	syscon = syscon_regmap_lookup_by_phandle(dev->of_node, "syscon");
	अगर (IS_ERR(syscon)) अणु
		अगर (PTR_ERR(syscon) == -ENODEV)
			वापस 0;
		वापस PTR_ERR(syscon);
	पूर्ण

	regmap_पढ़ो(syscon, CTRL_MAC_LO_REG(offset, slave), &macid_lo);
	regmap_पढ़ो(syscon, CTRL_MAC_HI_REG(offset, slave), &macid_hi);

	mac_addr[5] = (macid_lo >> 8) & 0xff;
	mac_addr[4] = macid_lo & 0xff;
	mac_addr[3] = (macid_hi >> 24) & 0xff;
	mac_addr[2] = (macid_hi >> 16) & 0xff;
	mac_addr[1] = (macid_hi >> 8) & 0xff;
	mac_addr[0] = macid_hi & 0xff;

	वापस 0;
पूर्ण

पूर्णांक ti_cm_get_macid(काष्ठा device *dev, पूर्णांक slave, u8 *mac_addr)
अणु
	अगर (of_machine_is_compatible("ti,dm8148"))
		वापस cpsw_am33xx_cm_get_macid(dev, 0x630, slave, mac_addr);

	अगर (of_machine_is_compatible("ti,am33xx"))
		वापस cpsw_am33xx_cm_get_macid(dev, 0x630, slave, mac_addr);

	अगर (of_device_is_compatible(dev->of_node, "ti,am3517-emac"))
		वापस davinci_emac_3517_get_macid(dev, 0x110, slave, mac_addr);

	अगर (of_device_is_compatible(dev->of_node, "ti,dm816-emac"))
		वापस cpsw_am33xx_cm_get_macid(dev, 0x30, slave, mac_addr);

	अगर (of_machine_is_compatible("ti,am43"))
		वापस cpsw_am33xx_cm_get_macid(dev, 0x630, slave, mac_addr);

	अगर (of_machine_is_compatible("ti,dra7"))
		वापस davinci_emac_3517_get_macid(dev, 0x514, slave, mac_addr);

	dev_info(dev, "incompatible machine/device type for reading mac address\n");
	वापस -ENOENT;
पूर्ण
EXPORT_SYMBOL_GPL(ti_cm_get_macid);

MODULE_LICENSE("GPL");
