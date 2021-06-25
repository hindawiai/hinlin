<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/export.h>
#समावेश <linux/kref.h>
#समावेश <linux/list.h>
#समावेश <linux/mutex.h>
#समावेश <linux/phylink.h>
#समावेश <linux/property.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/slab.h>

#समावेश "sfp.h"

काष्ठा sfp_quirk अणु
	स्थिर अक्षर *venकरोr;
	स्थिर अक्षर *part;
	व्योम (*modes)(स्थिर काष्ठा sfp_eeprom_id *id, अचिन्हित दीर्घ *modes);
पूर्ण;

/**
 * काष्ठा sfp_bus - पूर्णांकernal representation of a sfp bus
 */
काष्ठा sfp_bus अणु
	/* निजी: */
	काष्ठा kref kref;
	काष्ठा list_head node;
	काष्ठा fwnode_handle *fwnode;

	स्थिर काष्ठा sfp_socket_ops *socket_ops;
	काष्ठा device *sfp_dev;
	काष्ठा sfp *sfp;
	स्थिर काष्ठा sfp_quirk *sfp_quirk;

	स्थिर काष्ठा sfp_upstream_ops *upstream_ops;
	व्योम *upstream;
	काष्ठा phy_device *phydev;

	bool रेजिस्टरed;
	bool started;
पूर्ण;

अटल व्योम sfp_quirk_2500basex(स्थिर काष्ठा sfp_eeprom_id *id,
				अचिन्हित दीर्घ *modes)
अणु
	phylink_set(modes, 2500baseX_Full);
पूर्ण

अटल व्योम sfp_quirk_ubnt_uf_instant(स्थिर काष्ठा sfp_eeprom_id *id,
				      अचिन्हित दीर्घ *modes)
अणु
	/* Ubiquiti U-Fiber Instant module claims that support all transceiver
	 * types including 10G Ethernet which is not truth. So clear all claimed
	 * modes and set only one mode which module supports: 1000baseX_Full.
	 */
	phylink_zero(modes);
	phylink_set(modes, 1000baseX_Full);
पूर्ण

अटल स्थिर काष्ठा sfp_quirk sfp_quirks[] = अणु
	अणु
		// Alcatel Lucent G-010S-P can operate at 2500base-X, but
		// incorrectly report 2500MBd NRZ in their EEPROM
		.venकरोr = "ALCATELLUCENT",
		.part = "G010SP",
		.modes = sfp_quirk_2500basex,
	पूर्ण, अणु
		// Alcatel Lucent G-010S-A can operate at 2500base-X, but
		// report 3.2GBd NRZ in their EEPROM
		.venकरोr = "ALCATELLUCENT",
		.part = "3FE46541AA",
		.modes = sfp_quirk_2500basex,
	पूर्ण, अणु
		// Huawei MA5671A can operate at 2500base-X, but report 1.2GBd
		// NRZ in their EEPROM
		.venकरोr = "HUAWEI",
		.part = "MA5671A",
		.modes = sfp_quirk_2500basex,
	पूर्ण, अणु
		.venकरोr = "UBNT",
		.part = "UF-INSTANT",
		.modes = sfp_quirk_ubnt_uf_instant,
	पूर्ण,
पूर्ण;

अटल माप_प्रकार sfp_म_माप(स्थिर अक्षर *str, माप_प्रकार maxlen)
अणु
	माप_प्रकार size, i;

	/* Trailing अक्षरacters should be filled with space अक्षरs */
	क्रम (i = 0, size = 0; i < maxlen; i++)
		अगर (str[i] != ' ')
			size = i + 1;

	वापस size;
पूर्ण

अटल bool sfp_match(स्थिर अक्षर *qs, स्थिर अक्षर *str, माप_प्रकार len)
अणु
	अगर (!qs)
		वापस true;
	अगर (म_माप(qs) != len)
		वापस false;
	वापस !म_भेदन(qs, str, len);
पूर्ण

अटल स्थिर काष्ठा sfp_quirk *sfp_lookup_quirk(स्थिर काष्ठा sfp_eeprom_id *id)
अणु
	स्थिर काष्ठा sfp_quirk *q;
	अचिन्हित पूर्णांक i;
	माप_प्रकार vs, ps;

	vs = sfp_म_माप(id->base.venकरोr_name, ARRAY_SIZE(id->base.venकरोr_name));
	ps = sfp_म_माप(id->base.venकरोr_pn, ARRAY_SIZE(id->base.venकरोr_pn));

	क्रम (i = 0, q = sfp_quirks; i < ARRAY_SIZE(sfp_quirks); i++, q++)
		अगर (sfp_match(q->venकरोr, id->base.venकरोr_name, vs) &&
		    sfp_match(q->part, id->base.venकरोr_pn, ps))
			वापस q;

	वापस शून्य;
पूर्ण

/**
 * sfp_parse_port() - Parse the EEPROM base ID, setting the port type
 * @bus: a poपूर्णांकer to the &काष्ठा sfp_bus काष्ठाure क्रम the sfp module
 * @id: a poपूर्णांकer to the module's &काष्ठा sfp_eeprom_id
 * @support: optional poपूर्णांकer to an array of अचिन्हित दीर्घ क्रम the
 *   ethtool support mask
 *
 * Parse the EEPROM identअगरication given in @id, and वापस one of
 * %PORT_TP, %PORT_FIBRE or %PORT_OTHER. If @support is non-%शून्य,
 * also set the ethtool %ETHTOOL_LINK_MODE_xxx_BIT corresponding with
 * the connector type.
 *
 * If the port type is not known, वापसs %PORT_OTHER.
 */
पूर्णांक sfp_parse_port(काष्ठा sfp_bus *bus, स्थिर काष्ठा sfp_eeprom_id *id,
		   अचिन्हित दीर्घ *support)
अणु
	पूर्णांक port;

	/* port is the physical connector, set this from the connector field. */
	चयन (id->base.connector) अणु
	हाल SFF8024_CONNECTOR_SC:
	हाल SFF8024_CONNECTOR_FIBERJACK:
	हाल SFF8024_CONNECTOR_LC:
	हाल SFF8024_CONNECTOR_MT_RJ:
	हाल SFF8024_CONNECTOR_MU:
	हाल SFF8024_CONNECTOR_OPTICAL_PIGTAIL:
	हाल SFF8024_CONNECTOR_MPO_1X12:
	हाल SFF8024_CONNECTOR_MPO_2X16:
		port = PORT_FIBRE;
		अवरोध;

	हाल SFF8024_CONNECTOR_RJ45:
		port = PORT_TP;
		अवरोध;

	हाल SFF8024_CONNECTOR_COPPER_PIGTAIL:
		port = PORT_DA;
		अवरोध;

	हाल SFF8024_CONNECTOR_UNSPEC:
		अगर (id->base.e1000_base_t) अणु
			port = PORT_TP;
			अवरोध;
		पूर्ण
		fallthrough;
	हाल SFF8024_CONNECTOR_SG: /* guess */
	हाल SFF8024_CONNECTOR_HSSDC_II:
	हाल SFF8024_CONNECTOR_NOSEPARATE:
	हाल SFF8024_CONNECTOR_MXC_2X16:
		port = PORT_OTHER;
		अवरोध;
	शेष:
		dev_warn(bus->sfp_dev, "SFP: unknown connector id 0x%02x\n",
			 id->base.connector);
		port = PORT_OTHER;
		अवरोध;
	पूर्ण

	अगर (support) अणु
		चयन (port) अणु
		हाल PORT_FIBRE:
			phylink_set(support, FIBRE);
			अवरोध;

		हाल PORT_TP:
			phylink_set(support, TP);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस port;
पूर्ण
EXPORT_SYMBOL_GPL(sfp_parse_port);

/**
 * sfp_may_have_phy() - indicate whether the module may have a PHY
 * @bus: a poपूर्णांकer to the &काष्ठा sfp_bus काष्ठाure क्रम the sfp module
 * @id: a poपूर्णांकer to the module's &काष्ठा sfp_eeprom_id
 *
 * Parse the EEPROM identअगरication given in @id, and वापस whether
 * this module may have a PHY.
 */
bool sfp_may_have_phy(काष्ठा sfp_bus *bus, स्थिर काष्ठा sfp_eeprom_id *id)
अणु
	अगर (id->base.e1000_base_t)
		वापस true;

	अगर (id->base.phys_id != SFF8024_ID_DWDM_SFP) अणु
		चयन (id->base.extended_cc) अणु
		हाल SFF8024_ECC_10GBASE_T_SFI:
		हाल SFF8024_ECC_10GBASE_T_SR:
		हाल SFF8024_ECC_5GBASE_T:
		हाल SFF8024_ECC_2_5GBASE_T:
			वापस true;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण
EXPORT_SYMBOL_GPL(sfp_may_have_phy);

/**
 * sfp_parse_support() - Parse the eeprom id क्रम supported link modes
 * @bus: a poपूर्णांकer to the &काष्ठा sfp_bus काष्ठाure क्रम the sfp module
 * @id: a poपूर्णांकer to the module's &काष्ठा sfp_eeprom_id
 * @support: poपूर्णांकer to an array of अचिन्हित दीर्घ क्रम the ethtool support mask
 *
 * Parse the EEPROM identअगरication inक्रमmation and derive the supported
 * ethtool link modes क्रम the module.
 */
व्योम sfp_parse_support(काष्ठा sfp_bus *bus, स्थिर काष्ठा sfp_eeprom_id *id,
		       अचिन्हित दीर्घ *support)
अणु
	अचिन्हित पूर्णांक br_min, br_nom, br_max;
	__ETHTOOL_DECLARE_LINK_MODE_MASK(modes) = अणु 0, पूर्ण;

	/* Decode the bitrate inक्रमmation to MBd */
	br_min = br_nom = br_max = 0;
	अगर (id->base.br_nominal) अणु
		अगर (id->base.br_nominal != 255) अणु
			br_nom = id->base.br_nominal * 100;
			br_min = br_nom - id->base.br_nominal * id->ext.br_min;
			br_max = br_nom + id->base.br_nominal * id->ext.br_max;
		पूर्ण अन्यथा अगर (id->ext.br_max) अणु
			br_nom = 250 * id->ext.br_max;
			br_max = br_nom + br_nom * id->ext.br_min / 100;
			br_min = br_nom - br_nom * id->ext.br_min / 100;
		पूर्ण

		/* When using passive cables, in हाल neither BR,min nor BR,max
		 * are specअगरied, set br_min to 0 as the nominal value is then
		 * used as the maximum.
		 */
		अगर (br_min == br_max && id->base.sfp_ct_passive)
			br_min = 0;
	पूर्ण

	/* Set ethtool support from the compliance fields. */
	अगर (id->base.e10g_base_sr)
		phylink_set(modes, 10000baseSR_Full);
	अगर (id->base.e10g_base_lr)
		phylink_set(modes, 10000baseLR_Full);
	अगर (id->base.e10g_base_lrm)
		phylink_set(modes, 10000baseLRM_Full);
	अगर (id->base.e10g_base_er)
		phylink_set(modes, 10000baseER_Full);
	अगर (id->base.e1000_base_sx ||
	    id->base.e1000_base_lx ||
	    id->base.e1000_base_cx)
		phylink_set(modes, 1000baseX_Full);
	अगर (id->base.e1000_base_t) अणु
		phylink_set(modes, 1000baseT_Half);
		phylink_set(modes, 1000baseT_Full);
	पूर्ण

	/* 1000Base-PX or 1000Base-BX10 */
	अगर ((id->base.e_base_px || id->base.e_base_bx10) &&
	    br_min <= 1300 && br_max >= 1200)
		phylink_set(modes, 1000baseX_Full);

	/* 100Base-FX, 100Base-LX, 100Base-PX, 100Base-BX10 */
	अगर (id->base.e100_base_fx || id->base.e100_base_lx)
		phylink_set(modes, 100baseFX_Full);
	अगर ((id->base.e_base_px || id->base.e_base_bx10) && br_nom == 100)
		phylink_set(modes, 100baseFX_Full);

	/* For active or passive cables, select the link modes
	 * based on the bit rates and the cable compliance bytes.
	 */
	अगर ((id->base.sfp_ct_passive || id->base.sfp_ct_active) && br_nom) अणु
		/* This may look odd, but some manufacturers use 12000MBd */
		अगर (br_min <= 12000 && br_max >= 10300)
			phylink_set(modes, 10000baseCR_Full);
		अगर (br_min <= 3200 && br_max >= 3100)
			phylink_set(modes, 2500baseX_Full);
		अगर (br_min <= 1300 && br_max >= 1200)
			phylink_set(modes, 1000baseX_Full);
	पूर्ण
	अगर (id->base.sfp_ct_passive) अणु
		अगर (id->base.passive.sff8431_app_e)
			phylink_set(modes, 10000baseCR_Full);
	पूर्ण
	अगर (id->base.sfp_ct_active) अणु
		अगर (id->base.active.sff8431_app_e ||
		    id->base.active.sff8431_lim) अणु
			phylink_set(modes, 10000baseCR_Full);
		पूर्ण
	पूर्ण

	चयन (id->base.extended_cc) अणु
	हाल SFF8024_ECC_UNSPEC:
		अवरोध;
	हाल SFF8024_ECC_100GBASE_SR4_25GBASE_SR:
		phylink_set(modes, 100000baseSR4_Full);
		phylink_set(modes, 25000baseSR_Full);
		अवरोध;
	हाल SFF8024_ECC_100GBASE_LR4_25GBASE_LR:
	हाल SFF8024_ECC_100GBASE_ER4_25GBASE_ER:
		phylink_set(modes, 100000baseLR4_ER4_Full);
		अवरोध;
	हाल SFF8024_ECC_100GBASE_CR4:
		phylink_set(modes, 100000baseCR4_Full);
		fallthrough;
	हाल SFF8024_ECC_25GBASE_CR_S:
	हाल SFF8024_ECC_25GBASE_CR_N:
		phylink_set(modes, 25000baseCR_Full);
		अवरोध;
	हाल SFF8024_ECC_10GBASE_T_SFI:
	हाल SFF8024_ECC_10GBASE_T_SR:
		phylink_set(modes, 10000baseT_Full);
		अवरोध;
	हाल SFF8024_ECC_5GBASE_T:
		phylink_set(modes, 5000baseT_Full);
		अवरोध;
	हाल SFF8024_ECC_2_5GBASE_T:
		phylink_set(modes, 2500baseT_Full);
		अवरोध;
	शेष:
		dev_warn(bus->sfp_dev,
			 "Unknown/unsupported extended compliance code: 0x%02x\n",
			 id->base.extended_cc);
		अवरोध;
	पूर्ण

	/* For fibre channel SFP, derive possible BaseX modes */
	अगर (id->base.fc_speed_100 ||
	    id->base.fc_speed_200 ||
	    id->base.fc_speed_400) अणु
		अगर (id->base.br_nominal >= 31)
			phylink_set(modes, 2500baseX_Full);
		अगर (id->base.br_nominal >= 12)
			phylink_set(modes, 1000baseX_Full);
	पूर्ण

	/* If we haven't discovered any modes that this module supports, try
	 * the bitrate to determine supported modes. Some BiDi modules (eg,
	 * 1310nm/1550nm) are not 1000BASE-BX compliant due to the dअगरfering
	 * wavelengths, so करो not set any transceiver bits.
	 *
	 * Do the same क्रम modules supporting 2500BASE-X. Note that some
	 * modules use 2500Mbaud rather than 3100 or 3200Mbaud क्रम
	 * 2500BASE-X, so we allow some slack here.
	 */
	अगर (biपंचांगap_empty(modes, __ETHTOOL_LINK_MODE_MASK_NBITS) && br_nom) अणु
		अगर (br_min <= 1300 && br_max >= 1200)
			phylink_set(modes, 1000baseX_Full);
		अगर (br_min <= 3200 && br_max >= 2500)
			phylink_set(modes, 2500baseX_Full);
	पूर्ण

	अगर (bus->sfp_quirk)
		bus->sfp_quirk->modes(id, modes);

	biपंचांगap_or(support, support, modes, __ETHTOOL_LINK_MODE_MASK_NBITS);

	phylink_set(support, Autoneg);
	phylink_set(support, Pause);
	phylink_set(support, Asym_Pause);
पूर्ण
EXPORT_SYMBOL_GPL(sfp_parse_support);

/**
 * sfp_select_पूर्णांकerface() - Select appropriate phy_पूर्णांकerface_t mode
 * @bus: a poपूर्णांकer to the &काष्ठा sfp_bus काष्ठाure क्रम the sfp module
 * @link_modes: ethtool link modes mask
 *
 * Derive the phy_पूर्णांकerface_t mode क्रम the SFP module from the link
 * modes mask.
 */
phy_पूर्णांकerface_t sfp_select_पूर्णांकerface(काष्ठा sfp_bus *bus,
				     अचिन्हित दीर्घ *link_modes)
अणु
	अगर (phylink_test(link_modes, 10000baseCR_Full) ||
	    phylink_test(link_modes, 10000baseSR_Full) ||
	    phylink_test(link_modes, 10000baseLR_Full) ||
	    phylink_test(link_modes, 10000baseLRM_Full) ||
	    phylink_test(link_modes, 10000baseER_Full) ||
	    phylink_test(link_modes, 10000baseT_Full))
		वापस PHY_INTERFACE_MODE_10GBASER;

	अगर (phylink_test(link_modes, 5000baseT_Full))
		वापस PHY_INTERFACE_MODE_5GBASER;

	अगर (phylink_test(link_modes, 2500baseX_Full))
		वापस PHY_INTERFACE_MODE_2500BASEX;

	अगर (phylink_test(link_modes, 1000baseT_Half) ||
	    phylink_test(link_modes, 1000baseT_Full))
		वापस PHY_INTERFACE_MODE_SGMII;

	अगर (phylink_test(link_modes, 1000baseX_Full))
		वापस PHY_INTERFACE_MODE_1000BASEX;

	अगर (phylink_test(link_modes, 100baseFX_Full))
		वापस PHY_INTERFACE_MODE_100BASEX;

	dev_warn(bus->sfp_dev, "Unable to ascertain link mode\n");

	वापस PHY_INTERFACE_MODE_NA;
पूर्ण
EXPORT_SYMBOL_GPL(sfp_select_पूर्णांकerface);

अटल LIST_HEAD(sfp_buses);
अटल DEFINE_MUTEX(sfp_mutex);

अटल स्थिर काष्ठा sfp_upstream_ops *sfp_get_upstream_ops(काष्ठा sfp_bus *bus)
अणु
	वापस bus->रेजिस्टरed ? bus->upstream_ops : शून्य;
पूर्ण

अटल काष्ठा sfp_bus *sfp_bus_get(काष्ठा fwnode_handle *fwnode)
अणु
	काष्ठा sfp_bus *sfp, *new, *found = शून्य;

	new = kzalloc(माप(*new), GFP_KERNEL);

	mutex_lock(&sfp_mutex);

	list_क्रम_each_entry(sfp, &sfp_buses, node) अणु
		अगर (sfp->fwnode == fwnode) अणु
			kref_get(&sfp->kref);
			found = sfp;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!found && new) अणु
		kref_init(&new->kref);
		new->fwnode = fwnode;
		list_add(&new->node, &sfp_buses);
		found = new;
		new = शून्य;
	पूर्ण

	mutex_unlock(&sfp_mutex);

	kमुक्त(new);

	वापस found;
पूर्ण

अटल व्योम sfp_bus_release(काष्ठा kref *kref)
अणु
	काष्ठा sfp_bus *bus = container_of(kref, काष्ठा sfp_bus, kref);

	list_del(&bus->node);
	mutex_unlock(&sfp_mutex);
	kमुक्त(bus);
पूर्ण

/**
 * sfp_bus_put() - put a reference on the &काष्ठा sfp_bus
 * @bus: the &काष्ठा sfp_bus found via sfp_bus_find_fwnode()
 *
 * Put a reference on the &काष्ठा sfp_bus and मुक्त the underlying काष्ठाure
 * अगर this was the last reference.
 */
व्योम sfp_bus_put(काष्ठा sfp_bus *bus)
अणु
	अगर (bus)
		kref_put_mutex(&bus->kref, sfp_bus_release, &sfp_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(sfp_bus_put);

अटल पूर्णांक sfp_रेजिस्टर_bus(काष्ठा sfp_bus *bus)
अणु
	स्थिर काष्ठा sfp_upstream_ops *ops = bus->upstream_ops;
	पूर्णांक ret;

	अगर (ops) अणु
		अगर (ops->link_करोwn)
			ops->link_करोwn(bus->upstream);
		अगर (ops->connect_phy && bus->phydev) अणु
			ret = ops->connect_phy(bus->upstream, bus->phydev);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण
	bus->रेजिस्टरed = true;
	bus->socket_ops->attach(bus->sfp);
	अगर (bus->started)
		bus->socket_ops->start(bus->sfp);
	bus->upstream_ops->attach(bus->upstream, bus);
	वापस 0;
पूर्ण

अटल व्योम sfp_unरेजिस्टर_bus(काष्ठा sfp_bus *bus)
अणु
	स्थिर काष्ठा sfp_upstream_ops *ops = bus->upstream_ops;

	अगर (bus->रेजिस्टरed) अणु
		bus->upstream_ops->detach(bus->upstream, bus);
		अगर (bus->started)
			bus->socket_ops->stop(bus->sfp);
		bus->socket_ops->detach(bus->sfp);
		अगर (bus->phydev && ops && ops->disconnect_phy)
			ops->disconnect_phy(bus->upstream);
	पूर्ण
	bus->रेजिस्टरed = false;
पूर्ण

/**
 * sfp_get_module_info() - Get the ethtool_modinfo क्रम a SFP module
 * @bus: a poपूर्णांकer to the &काष्ठा sfp_bus काष्ठाure क्रम the sfp module
 * @modinfo: a &काष्ठा ethtool_modinfo
 *
 * Fill in the type and eeprom_len parameters in @modinfo क्रम a module on
 * the sfp bus specअगरied by @bus.
 *
 * Returns 0 on success or a negative त्रुटि_सं number.
 */
पूर्णांक sfp_get_module_info(काष्ठा sfp_bus *bus, काष्ठा ethtool_modinfo *modinfo)
अणु
	वापस bus->socket_ops->module_info(bus->sfp, modinfo);
पूर्ण
EXPORT_SYMBOL_GPL(sfp_get_module_info);

/**
 * sfp_get_module_eeprom() - Read the SFP module EEPROM
 * @bus: a poपूर्णांकer to the &काष्ठा sfp_bus काष्ठाure क्रम the sfp module
 * @ee: a &काष्ठा ethtool_eeprom
 * @data: buffer to contain the EEPROM data (must be at least @ee->len bytes)
 *
 * Read the EEPROM as specअगरied by the supplied @ee. See the करोcumentation
 * क्रम &काष्ठा ethtool_eeprom क्रम the region to be पढ़ो.
 *
 * Returns 0 on success or a negative त्रुटि_सं number.
 */
पूर्णांक sfp_get_module_eeprom(काष्ठा sfp_bus *bus, काष्ठा ethtool_eeprom *ee,
			  u8 *data)
अणु
	वापस bus->socket_ops->module_eeprom(bus->sfp, ee, data);
पूर्ण
EXPORT_SYMBOL_GPL(sfp_get_module_eeprom);

/**
 * sfp_get_module_eeprom_by_page() - Read a page from the SFP module EEPROM
 * @bus: a poपूर्णांकer to the &काष्ठा sfp_bus काष्ठाure क्रम the sfp module
 * @page: a &काष्ठा ethtool_module_eeprom
 * @extack: extack क्रम reporting problems
 *
 * Read an EEPROM page as specअगरied by the supplied @page. See the
 * करोcumentation क्रम &काष्ठा ethtool_module_eeprom क्रम the page to be पढ़ो.
 *
 * Returns 0 on success or a negative त्रुटि_सं number. More error
 * inक्रमmation might be provided via extack
 */
पूर्णांक sfp_get_module_eeprom_by_page(काष्ठा sfp_bus *bus,
				  स्थिर काष्ठा ethtool_module_eeprom *page,
				  काष्ठा netlink_ext_ack *extack)
अणु
	वापस bus->socket_ops->module_eeprom_by_page(bus->sfp, page, extack);
पूर्ण
EXPORT_SYMBOL_GPL(sfp_get_module_eeprom_by_page);

/**
 * sfp_upstream_start() - Inक्रमm the SFP that the network device is up
 * @bus: a poपूर्णांकer to the &काष्ठा sfp_bus काष्ठाure क्रम the sfp module
 *
 * Inक्रमm the SFP socket that the network device is now up, so that the
 * module can be enabled by allowing TX_DISABLE to be deनिश्चितed. This
 * should be called from the network device driver's &काष्ठा net_device_ops
 * nकरो_खोलो() method.
 */
व्योम sfp_upstream_start(काष्ठा sfp_bus *bus)
अणु
	अगर (bus->रेजिस्टरed)
		bus->socket_ops->start(bus->sfp);
	bus->started = true;
पूर्ण
EXPORT_SYMBOL_GPL(sfp_upstream_start);

/**
 * sfp_upstream_stop() - Inक्रमm the SFP that the network device is करोwn
 * @bus: a poपूर्णांकer to the &काष्ठा sfp_bus काष्ठाure क्रम the sfp module
 *
 * Inक्रमm the SFP socket that the network device is now up, so that the
 * module can be disabled by निश्चितing TX_DISABLE, disabling the laser
 * in optical modules. This should be called from the network device
 * driver's &काष्ठा net_device_ops nकरो_stop() method.
 */
व्योम sfp_upstream_stop(काष्ठा sfp_bus *bus)
अणु
	अगर (bus->रेजिस्टरed)
		bus->socket_ops->stop(bus->sfp);
	bus->started = false;
पूर्ण
EXPORT_SYMBOL_GPL(sfp_upstream_stop);

अटल व्योम sfp_upstream_clear(काष्ठा sfp_bus *bus)
अणु
	bus->upstream_ops = शून्य;
	bus->upstream = शून्य;
पूर्ण

/**
 * sfp_bus_find_fwnode() - parse and locate the SFP bus from fwnode
 * @fwnode: firmware node क्रम the parent device (MAC or PHY)
 *
 * Parse the parent device's firmware node क्रम a SFP bus, and locate
 * the sfp_bus काष्ठाure, incrementing its reference count.  This must
 * be put via sfp_bus_put() when करोne.
 *
 * Returns:
 * 	    - on success, a poपूर्णांकer to the sfp_bus काष्ठाure,
 *	    - %शून्य अगर no SFP is specअगरied,
 * 	    - on failure, an error poपूर्णांकer value:
 *
 * 	      - corresponding to the errors detailed क्रम
 * 	        fwnode_property_get_reference_args().
 * 	      - %-ENOMEM अगर we failed to allocate the bus.
 *	      - an error from the upstream's connect_phy() method.
 */
काष्ठा sfp_bus *sfp_bus_find_fwnode(काष्ठा fwnode_handle *fwnode)
अणु
	काष्ठा fwnode_reference_args ref;
	काष्ठा sfp_bus *bus;
	पूर्णांक ret;

	ret = fwnode_property_get_reference_args(fwnode, "sfp", शून्य,
						 0, 0, &ref);
	अगर (ret == -ENOENT)
		वापस शून्य;
	अन्यथा अगर (ret < 0)
		वापस ERR_PTR(ret);

	bus = sfp_bus_get(ref.fwnode);
	fwnode_handle_put(ref.fwnode);
	अगर (!bus)
		वापस ERR_PTR(-ENOMEM);

	वापस bus;
पूर्ण
EXPORT_SYMBOL_GPL(sfp_bus_find_fwnode);

/**
 * sfp_bus_add_upstream() - parse and रेजिस्टर the neighbouring device
 * @bus: the &काष्ठा sfp_bus found via sfp_bus_find_fwnode()
 * @upstream: the upstream निजी data
 * @ops: the upstream's &काष्ठा sfp_upstream_ops
 *
 * Add upstream driver क्रम the SFP bus, and अगर the bus is complete, रेजिस्टर
 * the SFP bus using sfp_रेजिस्टर_upstream().  This takes a reference on the
 * bus, so it is safe to put the bus after this call.
 *
 * Returns:
 * 	    - on success, a poपूर्णांकer to the sfp_bus काष्ठाure,
 *	    - %शून्य अगर no SFP is specअगरied,
 * 	    - on failure, an error poपूर्णांकer value:
 *
 * 	      - corresponding to the errors detailed क्रम
 * 	        fwnode_property_get_reference_args().
 * 	      - %-ENOMEM अगर we failed to allocate the bus.
 *	      - an error from the upstream's connect_phy() method.
 */
पूर्णांक sfp_bus_add_upstream(काष्ठा sfp_bus *bus, व्योम *upstream,
			 स्थिर काष्ठा sfp_upstream_ops *ops)
अणु
	पूर्णांक ret;

	/* If no bus, वापस success */
	अगर (!bus)
		वापस 0;

	rtnl_lock();
	kref_get(&bus->kref);
	bus->upstream_ops = ops;
	bus->upstream = upstream;

	अगर (bus->sfp) अणु
		ret = sfp_रेजिस्टर_bus(bus);
		अगर (ret)
			sfp_upstream_clear(bus);
	पूर्ण अन्यथा अणु
		ret = 0;
	पूर्ण
	rtnl_unlock();

	अगर (ret)
		sfp_bus_put(bus);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(sfp_bus_add_upstream);

/**
 * sfp_bus_del_upstream() - Delete a sfp bus
 * @bus: a poपूर्णांकer to the &काष्ठा sfp_bus काष्ठाure क्रम the sfp module
 *
 * Delete a previously रेजिस्टरed upstream connection क्रम the SFP
 * module. @bus should have been added by sfp_bus_add_upstream().
 */
व्योम sfp_bus_del_upstream(काष्ठा sfp_bus *bus)
अणु
	अगर (bus) अणु
		rtnl_lock();
		अगर (bus->sfp)
			sfp_unरेजिस्टर_bus(bus);
		sfp_upstream_clear(bus);
		rtnl_unlock();

		sfp_bus_put(bus);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(sfp_bus_del_upstream);

/* Socket driver entry poपूर्णांकs */
पूर्णांक sfp_add_phy(काष्ठा sfp_bus *bus, काष्ठा phy_device *phydev)
अणु
	स्थिर काष्ठा sfp_upstream_ops *ops = sfp_get_upstream_ops(bus);
	पूर्णांक ret = 0;

	अगर (ops && ops->connect_phy)
		ret = ops->connect_phy(bus->upstream, phydev);

	अगर (ret == 0)
		bus->phydev = phydev;

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(sfp_add_phy);

व्योम sfp_हटाओ_phy(काष्ठा sfp_bus *bus)
अणु
	स्थिर काष्ठा sfp_upstream_ops *ops = sfp_get_upstream_ops(bus);

	अगर (ops && ops->disconnect_phy)
		ops->disconnect_phy(bus->upstream);
	bus->phydev = शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(sfp_हटाओ_phy);

व्योम sfp_link_up(काष्ठा sfp_bus *bus)
अणु
	स्थिर काष्ठा sfp_upstream_ops *ops = sfp_get_upstream_ops(bus);

	अगर (ops && ops->link_up)
		ops->link_up(bus->upstream);
पूर्ण
EXPORT_SYMBOL_GPL(sfp_link_up);

व्योम sfp_link_करोwn(काष्ठा sfp_bus *bus)
अणु
	स्थिर काष्ठा sfp_upstream_ops *ops = sfp_get_upstream_ops(bus);

	अगर (ops && ops->link_करोwn)
		ops->link_करोwn(bus->upstream);
पूर्ण
EXPORT_SYMBOL_GPL(sfp_link_करोwn);

पूर्णांक sfp_module_insert(काष्ठा sfp_bus *bus, स्थिर काष्ठा sfp_eeprom_id *id)
अणु
	स्थिर काष्ठा sfp_upstream_ops *ops = sfp_get_upstream_ops(bus);
	पूर्णांक ret = 0;

	bus->sfp_quirk = sfp_lookup_quirk(id);

	अगर (ops && ops->module_insert)
		ret = ops->module_insert(bus->upstream, id);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(sfp_module_insert);

व्योम sfp_module_हटाओ(काष्ठा sfp_bus *bus)
अणु
	स्थिर काष्ठा sfp_upstream_ops *ops = sfp_get_upstream_ops(bus);

	अगर (ops && ops->module_हटाओ)
		ops->module_हटाओ(bus->upstream);

	bus->sfp_quirk = शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(sfp_module_हटाओ);

पूर्णांक sfp_module_start(काष्ठा sfp_bus *bus)
अणु
	स्थिर काष्ठा sfp_upstream_ops *ops = sfp_get_upstream_ops(bus);
	पूर्णांक ret = 0;

	अगर (ops && ops->module_start)
		ret = ops->module_start(bus->upstream);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(sfp_module_start);

व्योम sfp_module_stop(काष्ठा sfp_bus *bus)
अणु
	स्थिर काष्ठा sfp_upstream_ops *ops = sfp_get_upstream_ops(bus);

	अगर (ops && ops->module_stop)
		ops->module_stop(bus->upstream);
पूर्ण
EXPORT_SYMBOL_GPL(sfp_module_stop);

अटल व्योम sfp_socket_clear(काष्ठा sfp_bus *bus)
अणु
	bus->sfp_dev = शून्य;
	bus->sfp = शून्य;
	bus->socket_ops = शून्य;
पूर्ण

काष्ठा sfp_bus *sfp_रेजिस्टर_socket(काष्ठा device *dev, काष्ठा sfp *sfp,
				    स्थिर काष्ठा sfp_socket_ops *ops)
अणु
	काष्ठा sfp_bus *bus = sfp_bus_get(dev->fwnode);
	पूर्णांक ret = 0;

	अगर (bus) अणु
		rtnl_lock();
		bus->sfp_dev = dev;
		bus->sfp = sfp;
		bus->socket_ops = ops;

		अगर (bus->upstream_ops) अणु
			ret = sfp_रेजिस्टर_bus(bus);
			अगर (ret)
				sfp_socket_clear(bus);
		पूर्ण
		rtnl_unlock();
	पूर्ण

	अगर (ret) अणु
		sfp_bus_put(bus);
		bus = शून्य;
	पूर्ण

	वापस bus;
पूर्ण
EXPORT_SYMBOL_GPL(sfp_रेजिस्टर_socket);

व्योम sfp_unरेजिस्टर_socket(काष्ठा sfp_bus *bus)
अणु
	rtnl_lock();
	अगर (bus->upstream_ops)
		sfp_unरेजिस्टर_bus(bus);
	sfp_socket_clear(bus);
	rtnl_unlock();

	sfp_bus_put(bus);
पूर्ण
EXPORT_SYMBOL_GPL(sfp_unरेजिस्टर_socket);
