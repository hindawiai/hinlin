<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * OF helpers क्रम network devices.
 *
 * Initially copied out of arch/घातerpc/kernel/prom_parse.c
 */
#समावेश <linux/etherdevice.h>
#समावेश <linux/kernel.h>
#समावेश <linux/of_net.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/phy.h>
#समावेश <linux/export.h>
#समावेश <linux/device.h>
#समावेश <linux/nvmem-consumer.h>

/**
 * of_get_phy_mode - Get phy mode क्रम given device_node
 * @np:	Poपूर्णांकer to the given device_node
 * @पूर्णांकerface: Poपूर्णांकer to the result
 *
 * The function माला_लो phy पूर्णांकerface string from property 'phy-mode' or
 * 'phy-connection-type'. The index in phy_modes table is set in
 * पूर्णांकerface and 0 वापसed. In हाल of error पूर्णांकerface is set to
 * PHY_INTERFACE_MODE_NA and an त्रुटि_सं is वापसed, e.g. -ENODEV.
 */
पूर्णांक of_get_phy_mode(काष्ठा device_node *np, phy_पूर्णांकerface_t *पूर्णांकerface)
अणु
	स्थिर अक्षर *pm;
	पूर्णांक err, i;

	*पूर्णांकerface = PHY_INTERFACE_MODE_NA;

	err = of_property_पढ़ो_string(np, "phy-mode", &pm);
	अगर (err < 0)
		err = of_property_पढ़ो_string(np, "phy-connection-type", &pm);
	अगर (err < 0)
		वापस err;

	क्रम (i = 0; i < PHY_INTERFACE_MODE_MAX; i++)
		अगर (!strहालcmp(pm, phy_modes(i))) अणु
			*पूर्णांकerface = i;
			वापस 0;
		पूर्ण

	वापस -ENODEV;
पूर्ण
EXPORT_SYMBOL_GPL(of_get_phy_mode);

अटल पूर्णांक of_get_mac_addr(काष्ठा device_node *np, स्थिर अक्षर *name, u8 *addr)
अणु
	काष्ठा property *pp = of_find_property(np, name, शून्य);

	अगर (pp && pp->length == ETH_ALEN && is_valid_ether_addr(pp->value)) अणु
		स_नकल(addr, pp->value, ETH_ALEN);
		वापस 0;
	पूर्ण
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक of_get_mac_addr_nvmem(काष्ठा device_node *np, u8 *addr)
अणु
	काष्ठा platक्रमm_device *pdev = of_find_device_by_node(np);
	काष्ठा nvmem_cell *cell;
	स्थिर व्योम *mac;
	माप_प्रकार len;
	पूर्णांक ret;

	/* Try lookup by device first, there might be a nvmem_cell_lookup
	 * associated with a given device.
	 */
	अगर (pdev) अणु
		ret = nvmem_get_mac_address(&pdev->dev, addr);
		put_device(&pdev->dev);
		वापस ret;
	पूर्ण

	cell = of_nvmem_cell_get(np, "mac-address");
	अगर (IS_ERR(cell))
		वापस PTR_ERR(cell);

	mac = nvmem_cell_पढ़ो(cell, &len);
	nvmem_cell_put(cell);

	अगर (IS_ERR(mac))
		वापस PTR_ERR(mac);

	अगर (len != ETH_ALEN || !is_valid_ether_addr(mac)) अणु
		kमुक्त(mac);
		वापस -EINVAL;
	पूर्ण

	स_नकल(addr, mac, ETH_ALEN);
	kमुक्त(mac);

	वापस 0;
पूर्ण

/**
 * of_get_mac_address()
 * @np:		Caller's Device Node
 * @addr:	Poपूर्णांकer to a six-byte array क्रम the result
 *
 * Search the device tree क्रम the best MAC address to use.  'mac-address' is
 * checked first, because that is supposed to contain to "most recent" MAC
 * address. If that isn't set, then 'local-mac-address' is checked next,
 * because that is the शेष address. If that isn't set, then the obsolete
 * 'address' is checked, just in case we're using an old device tree. If any
 * of the above isn't set, then try to get MAC address from nvmem cell named
 * 'mac-address'.
 *
 * Note that the 'address' property is supposed to contain a भव address of
 * the रेजिस्टर set, but some DTS files have redefined that property to be the
 * MAC address.
 *
 * All-zero MAC addresses are rejected, because those could be properties that
 * exist in the device tree, but were not set by U-Boot.  For example, the
 * DTS could define 'mac-address' and 'local-mac-address', with zero MAC
 * addresses.  Some older U-Boots only initialized 'local-mac-address'.  In
 * this हाल, the real MAC is in 'local-mac-address', and 'mac-address' exists
 * but is all zeros.
 *
 * Return: 0 on success and त्रुटि_सं in हाल of error.
*/
पूर्णांक of_get_mac_address(काष्ठा device_node *np, u8 *addr)
अणु
	पूर्णांक ret;

	अगर (!np)
		वापस -ENODEV;

	ret = of_get_mac_addr(np, "mac-address", addr);
	अगर (!ret)
		वापस 0;

	ret = of_get_mac_addr(np, "local-mac-address", addr);
	अगर (!ret)
		वापस 0;

	ret = of_get_mac_addr(np, "address", addr);
	अगर (!ret)
		वापस 0;

	वापस of_get_mac_addr_nvmem(np, addr);
पूर्ण
EXPORT_SYMBOL(of_get_mac_address);
