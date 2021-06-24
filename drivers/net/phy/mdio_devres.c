<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later

#समावेश <linux/device.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/phy.h>
#समावेश <linux/मानकघोष.स>

काष्ठा mdiobus_devres अणु
	काष्ठा mii_bus *mii;
पूर्ण;

अटल व्योम devm_mdiobus_मुक्त(काष्ठा device *dev, व्योम *this)
अणु
	काष्ठा mdiobus_devres *dr = this;

	mdiobus_मुक्त(dr->mii);
पूर्ण

/**
 * devm_mdiobus_alloc_size - Resource-managed mdiobus_alloc_size()
 * @dev:		Device to allocate mii_bus क्रम
 * @माप_priv:	Space to allocate क्रम निजी काष्ठाure
 *
 * Managed mdiobus_alloc_size. mii_bus allocated with this function is
 * स्वतःmatically मुक्तd on driver detach.
 *
 * RETURNS:
 * Poपूर्णांकer to allocated mii_bus on success, शून्य on out-of-memory error.
 */
काष्ठा mii_bus *devm_mdiobus_alloc_size(काष्ठा device *dev, पूर्णांक माप_priv)
अणु
	काष्ठा mdiobus_devres *dr;

	dr = devres_alloc(devm_mdiobus_मुक्त, माप(*dr), GFP_KERNEL);
	अगर (!dr)
		वापस शून्य;

	dr->mii = mdiobus_alloc_size(माप_priv);
	अगर (!dr->mii) अणु
		devres_मुक्त(dr);
		वापस शून्य;
	पूर्ण

	devres_add(dev, dr);
	वापस dr->mii;
पूर्ण
EXPORT_SYMBOL(devm_mdiobus_alloc_size);

अटल व्योम devm_mdiobus_unरेजिस्टर(काष्ठा device *dev, व्योम *this)
अणु
	काष्ठा mdiobus_devres *dr = this;

	mdiobus_unरेजिस्टर(dr->mii);
पूर्ण

अटल पूर्णांक mdiobus_devres_match(काष्ठा device *dev,
				व्योम *this, व्योम *match_data)
अणु
	काष्ठा mdiobus_devres *res = this;
	काष्ठा mii_bus *mii = match_data;

	वापस mii == res->mii;
पूर्ण

/**
 * __devm_mdiobus_रेजिस्टर - Resource-managed variant of mdiobus_रेजिस्टर()
 * @dev:	Device to रेजिस्टर mii_bus क्रम
 * @bus:	MII bus काष्ठाure to रेजिस्टर
 * @owner:	Owning module
 *
 * Returns 0 on success, negative error number on failure.
 */
पूर्णांक __devm_mdiobus_रेजिस्टर(काष्ठा device *dev, काष्ठा mii_bus *bus,
			    काष्ठा module *owner)
अणु
	काष्ठा mdiobus_devres *dr;
	पूर्णांक ret;

	अगर (WARN_ON(!devres_find(dev, devm_mdiobus_मुक्त,
				 mdiobus_devres_match, bus)))
		वापस -EINVAL;

	dr = devres_alloc(devm_mdiobus_unरेजिस्टर, माप(*dr), GFP_KERNEL);
	अगर (!dr)
		वापस -ENOMEM;

	ret = __mdiobus_रेजिस्टर(bus, owner);
	अगर (ret) अणु
		devres_मुक्त(dr);
		वापस ret;
	पूर्ण

	dr->mii = bus;
	devres_add(dev, dr);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(__devm_mdiobus_रेजिस्टर);

#अगर IS_ENABLED(CONFIG_OF_MDIO)
/**
 * devm_of_mdiobus_रेजिस्टर - Resource managed variant of of_mdiobus_रेजिस्टर()
 * @dev:	Device to रेजिस्टर mii_bus क्रम
 * @mdio:	MII bus काष्ठाure to रेजिस्टर
 * @np:		Device node to parse
 */
पूर्णांक devm_of_mdiobus_रेजिस्टर(काष्ठा device *dev, काष्ठा mii_bus *mdio,
			     काष्ठा device_node *np)
अणु
	काष्ठा mdiobus_devres *dr;
	पूर्णांक ret;

	अगर (WARN_ON(!devres_find(dev, devm_mdiobus_मुक्त,
				 mdiobus_devres_match, mdio)))
		वापस -EINVAL;

	dr = devres_alloc(devm_mdiobus_unरेजिस्टर, माप(*dr), GFP_KERNEL);
	अगर (!dr)
		वापस -ENOMEM;

	ret = of_mdiobus_रेजिस्टर(mdio, np);
	अगर (ret) अणु
		devres_मुक्त(dr);
		वापस ret;
	पूर्ण

	dr->mii = mdio;
	devres_add(dev, dr);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(devm_of_mdiobus_रेजिस्टर);
#पूर्ण_अगर /* CONFIG_OF_MDIO */

MODULE_LICENSE("GPL");
