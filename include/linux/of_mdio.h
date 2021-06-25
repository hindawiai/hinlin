<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * OF helpers क्रम the MDIO (Ethernet PHY) API
 *
 * Copyright (c) 2009 Secret Lab Technologies, Ltd.
 */

#अगर_अघोषित __LINUX_OF_MDIO_H
#घोषणा __LINUX_OF_MDIO_H

#समावेश <linux/device.h>
#समावेश <linux/phy.h>
#समावेश <linux/of.h>

#अगर IS_ENABLED(CONFIG_OF_MDIO)
bool of_mdiobus_child_is_phy(काष्ठा device_node *child);
पूर्णांक of_mdiobus_रेजिस्टर(काष्ठा mii_bus *mdio, काष्ठा device_node *np);
पूर्णांक devm_of_mdiobus_रेजिस्टर(काष्ठा device *dev, काष्ठा mii_bus *mdio,
			     काष्ठा device_node *np);
काष्ठा mdio_device *of_mdio_find_device(काष्ठा device_node *np);
काष्ठा phy_device *of_phy_find_device(काष्ठा device_node *phy_np);
काष्ठा phy_device *
of_phy_connect(काष्ठा net_device *dev, काष्ठा device_node *phy_np,
	       व्योम (*hndlr)(काष्ठा net_device *), u32 flags,
	       phy_पूर्णांकerface_t अगरace);
काष्ठा phy_device *
of_phy_get_and_connect(काष्ठा net_device *dev, काष्ठा device_node *np,
		       व्योम (*hndlr)(काष्ठा net_device *));

काष्ठा mii_bus *of_mdio_find_bus(काष्ठा device_node *mdio_np);
पूर्णांक of_phy_रेजिस्टर_fixed_link(काष्ठा device_node *np);
व्योम of_phy_deरेजिस्टर_fixed_link(काष्ठा device_node *np);
bool of_phy_is_fixed_link(काष्ठा device_node *np);
पूर्णांक of_mdiobus_phy_device_रेजिस्टर(काष्ठा mii_bus *mdio, काष्ठा phy_device *phy,
				   काष्ठा device_node *child, u32 addr);

अटल अंतरभूत पूर्णांक of_mdio_parse_addr(काष्ठा device *dev,
				     स्थिर काष्ठा device_node *np)
अणु
	u32 addr;
	पूर्णांक ret;

	ret = of_property_पढ़ो_u32(np, "reg", &addr);
	अगर (ret < 0) अणु
		dev_err(dev, "%s has invalid PHY address\n", np->full_name);
		वापस ret;
	पूर्ण

	/* A PHY must have a reg property in the range [0-31] */
	अगर (addr >= PHY_MAX_ADDR) अणु
		dev_err(dev, "%s PHY address %i is too large\n",
			np->full_name, addr);
		वापस -EINVAL;
	पूर्ण

	वापस addr;
पूर्ण

#अन्यथा /* CONFIG_OF_MDIO */
अटल अंतरभूत bool of_mdiobus_child_is_phy(काष्ठा device_node *child)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत पूर्णांक of_mdiobus_रेजिस्टर(काष्ठा mii_bus *mdio, काष्ठा device_node *np)
अणु
	/*
	 * Fall back to the non-DT function to रेजिस्टर a bus.
	 * This way, we करोn't have to keep compat bits around in drivers.
	 */

	वापस mdiobus_रेजिस्टर(mdio);
पूर्ण

अटल अंतरभूत काष्ठा mdio_device *of_mdio_find_device(काष्ठा device_node *np)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा phy_device *of_phy_find_device(काष्ठा device_node *phy_np)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा phy_device *of_phy_connect(काष्ठा net_device *dev,
						काष्ठा device_node *phy_np,
						व्योम (*hndlr)(काष्ठा net_device *),
						u32 flags, phy_पूर्णांकerface_t अगरace)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा phy_device *
of_phy_get_and_connect(काष्ठा net_device *dev, काष्ठा device_node *np,
		       व्योम (*hndlr)(काष्ठा net_device *))
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा mii_bus *of_mdio_find_bus(काष्ठा device_node *mdio_np)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक of_mdio_parse_addr(काष्ठा device *dev,
				     स्थिर काष्ठा device_node *np)
अणु
	वापस -ENOSYS;
पूर्ण
अटल अंतरभूत पूर्णांक of_phy_रेजिस्टर_fixed_link(काष्ठा device_node *np)
अणु
	वापस -ENOSYS;
पूर्ण
अटल अंतरभूत व्योम of_phy_deरेजिस्टर_fixed_link(काष्ठा device_node *np)
अणु
पूर्ण
अटल अंतरभूत bool of_phy_is_fixed_link(काष्ठा device_node *np)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत पूर्णांक of_mdiobus_phy_device_रेजिस्टर(काष्ठा mii_bus *mdio,
					    काष्ठा phy_device *phy,
					    काष्ठा device_node *child, u32 addr)
अणु
	वापस -ENOSYS;
पूर्ण
#पूर्ण_अगर


#पूर्ण_अगर /* __LINUX_OF_MDIO_H */
