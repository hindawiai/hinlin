<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Realtek SMI library helpers क्रम the RTL8366x variants
 * RTL8366RB and RTL8366S
 *
 * Copyright (C) 2017 Linus Walleij <linus.walleij@linaro.org>
 * Copyright (C) 2009-2010 Gabor Juhos <juhosg@खोलोwrt.org>
 * Copyright (C) 2010 Antti Seppथअlथअ <a.seppala@gmail.com>
 * Copyright (C) 2010 Roman Yeryomin <roman@advem.lv>
 * Copyright (C) 2011 Colin Leitner <colin.leitner@googlemail.com>
 */
#समावेश <linux/अगर_bridge.h>
#समावेश <net/dsa.h>

#समावेश "realtek-smi-core.h"

पूर्णांक rtl8366_mc_is_used(काष्ठा realtek_smi *smi, पूर्णांक mc_index, पूर्णांक *used)
अणु
	पूर्णांक ret;
	पूर्णांक i;

	*used = 0;
	क्रम (i = 0; i < smi->num_ports; i++) अणु
		पूर्णांक index = 0;

		ret = smi->ops->get_mc_index(smi, i, &index);
		अगर (ret)
			वापस ret;

		अगर (mc_index == index) अणु
			*used = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rtl8366_mc_is_used);

/**
 * rtl8366_obtain_mc() - retrieve or allocate a VLAN member configuration
 * @smi: the Realtek SMI device instance
 * @vid: the VLAN ID to look up or allocate
 * @vlanmc: the poपूर्णांकer will be asचिन्हित to a poपूर्णांकer to a valid member config
 * अगर successful
 * @वापस: index of a new member config or negative error number
 */
अटल पूर्णांक rtl8366_obtain_mc(काष्ठा realtek_smi *smi, पूर्णांक vid,
			     काष्ठा rtl8366_vlan_mc *vlanmc)
अणु
	काष्ठा rtl8366_vlan_4k vlan4k;
	पूर्णांक ret;
	पूर्णांक i;

	/* Try to find an existing member config entry क्रम this VID */
	क्रम (i = 0; i < smi->num_vlan_mc; i++) अणु
		ret = smi->ops->get_vlan_mc(smi, i, vlanmc);
		अगर (ret) अणु
			dev_err(smi->dev, "error searching for VLAN MC %d for VID %d\n",
				i, vid);
			वापस ret;
		पूर्ण

		अगर (vid == vlanmc->vid)
			वापस i;
	पूर्ण

	/* We have no MC entry क्रम this VID, try to find an empty one */
	क्रम (i = 0; i < smi->num_vlan_mc; i++) अणु
		ret = smi->ops->get_vlan_mc(smi, i, vlanmc);
		अगर (ret) अणु
			dev_err(smi->dev, "error searching for VLAN MC %d for VID %d\n",
				i, vid);
			वापस ret;
		पूर्ण

		अगर (vlanmc->vid == 0 && vlanmc->member == 0) अणु
			/* Update the entry from the 4K table */
			ret = smi->ops->get_vlan_4k(smi, vid, &vlan4k);
			अगर (ret) अणु
				dev_err(smi->dev, "error looking for 4K VLAN MC %d for VID %d\n",
					i, vid);
				वापस ret;
			पूर्ण

			vlanmc->vid = vid;
			vlanmc->member = vlan4k.member;
			vlanmc->untag = vlan4k.untag;
			vlanmc->fid = vlan4k.fid;
			ret = smi->ops->set_vlan_mc(smi, i, vlanmc);
			अगर (ret) अणु
				dev_err(smi->dev, "unable to set/update VLAN MC %d for VID %d\n",
					i, vid);
				वापस ret;
			पूर्ण

			dev_dbg(smi->dev, "created new MC at index %d for VID %d\n",
				i, vid);
			वापस i;
		पूर्ण
	पूर्ण

	/* MC table is full, try to find an unused entry and replace it */
	क्रम (i = 0; i < smi->num_vlan_mc; i++) अणु
		पूर्णांक used;

		ret = rtl8366_mc_is_used(smi, i, &used);
		अगर (ret)
			वापस ret;

		अगर (!used) अणु
			/* Update the entry from the 4K table */
			ret = smi->ops->get_vlan_4k(smi, vid, &vlan4k);
			अगर (ret)
				वापस ret;

			vlanmc->vid = vid;
			vlanmc->member = vlan4k.member;
			vlanmc->untag = vlan4k.untag;
			vlanmc->fid = vlan4k.fid;
			ret = smi->ops->set_vlan_mc(smi, i, vlanmc);
			अगर (ret) अणु
				dev_err(smi->dev, "unable to set/update VLAN MC %d for VID %d\n",
					i, vid);
				वापस ret;
			पूर्ण
			dev_dbg(smi->dev, "recycled MC at index %i for VID %d\n",
				i, vid);
			वापस i;
		पूर्ण
	पूर्ण

	dev_err(smi->dev, "all VLAN member configurations are in use\n");
	वापस -ENOSPC;
पूर्ण

पूर्णांक rtl8366_set_vlan(काष्ठा realtek_smi *smi, पूर्णांक vid, u32 member,
		     u32 untag, u32 fid)
अणु
	काष्ठा rtl8366_vlan_mc vlanmc;
	काष्ठा rtl8366_vlan_4k vlan4k;
	पूर्णांक mc;
	पूर्णांक ret;

	अगर (!smi->ops->is_vlan_valid(smi, vid))
		वापस -EINVAL;

	dev_dbg(smi->dev,
		"setting VLAN%d 4k members: 0x%02x, untagged: 0x%02x\n",
		vid, member, untag);

	/* Update the 4K table */
	ret = smi->ops->get_vlan_4k(smi, vid, &vlan4k);
	अगर (ret)
		वापस ret;

	vlan4k.member |= member;
	vlan4k.untag |= untag;
	vlan4k.fid = fid;
	ret = smi->ops->set_vlan_4k(smi, &vlan4k);
	अगर (ret)
		वापस ret;

	dev_dbg(smi->dev,
		"resulting VLAN%d 4k members: 0x%02x, untagged: 0x%02x\n",
		vid, vlan4k.member, vlan4k.untag);

	/* Find or allocate a member config क्रम this VID */
	ret = rtl8366_obtain_mc(smi, vid, &vlanmc);
	अगर (ret < 0)
		वापस ret;
	mc = ret;

	/* Update the MC entry */
	vlanmc.member |= member;
	vlanmc.untag |= untag;
	vlanmc.fid = fid;

	/* Commit updates to the MC entry */
	ret = smi->ops->set_vlan_mc(smi, mc, &vlanmc);
	अगर (ret)
		dev_err(smi->dev, "failed to commit changes to VLAN MC index %d for VID %d\n",
			mc, vid);
	अन्यथा
		dev_dbg(smi->dev,
			"resulting VLAN%d MC members: 0x%02x, untagged: 0x%02x\n",
			vid, vlanmc.member, vlanmc.untag);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(rtl8366_set_vlan);

पूर्णांक rtl8366_set_pvid(काष्ठा realtek_smi *smi, अचिन्हित पूर्णांक port,
		     अचिन्हित पूर्णांक vid)
अणु
	काष्ठा rtl8366_vlan_mc vlanmc;
	पूर्णांक mc;
	पूर्णांक ret;

	अगर (!smi->ops->is_vlan_valid(smi, vid))
		वापस -EINVAL;

	/* Find or allocate a member config क्रम this VID */
	ret = rtl8366_obtain_mc(smi, vid, &vlanmc);
	अगर (ret < 0)
		वापस ret;
	mc = ret;

	ret = smi->ops->set_mc_index(smi, port, mc);
	अगर (ret) अणु
		dev_err(smi->dev, "set PVID: failed to set MC index %d for port %d\n",
			mc, port);
		वापस ret;
	पूर्ण

	dev_dbg(smi->dev, "set PVID: the PVID for port %d set to %d using existing MC index %d\n",
		port, vid, mc);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rtl8366_set_pvid);

पूर्णांक rtl8366_enable_vlan4k(काष्ठा realtek_smi *smi, bool enable)
अणु
	पूर्णांक ret;

	/* To enable 4k VLAN, ordinary VLAN must be enabled first,
	 * but अगर we disable 4k VLAN it is fine to leave ordinary
	 * VLAN enabled.
	 */
	अगर (enable) अणु
		/* Make sure VLAN is ON */
		ret = smi->ops->enable_vlan(smi, true);
		अगर (ret)
			वापस ret;

		smi->vlan_enabled = true;
	पूर्ण

	ret = smi->ops->enable_vlan4k(smi, enable);
	अगर (ret)
		वापस ret;

	smi->vlan4k_enabled = enable;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rtl8366_enable_vlan4k);

पूर्णांक rtl8366_enable_vlan(काष्ठा realtek_smi *smi, bool enable)
अणु
	पूर्णांक ret;

	ret = smi->ops->enable_vlan(smi, enable);
	अगर (ret)
		वापस ret;

	smi->vlan_enabled = enable;

	/* If we turn VLAN off, make sure that we turn off
	 * 4k VLAN as well, अगर that happened to be on.
	 */
	अगर (!enable) अणु
		smi->vlan4k_enabled = false;
		ret = smi->ops->enable_vlan4k(smi, false);
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(rtl8366_enable_vlan);

पूर्णांक rtl8366_reset_vlan(काष्ठा realtek_smi *smi)
अणु
	काष्ठा rtl8366_vlan_mc vlanmc;
	पूर्णांक ret;
	पूर्णांक i;

	rtl8366_enable_vlan(smi, false);
	rtl8366_enable_vlan4k(smi, false);

	/* Clear the 16 VLAN member configurations */
	vlanmc.vid = 0;
	vlanmc.priority = 0;
	vlanmc.member = 0;
	vlanmc.untag = 0;
	vlanmc.fid = 0;
	क्रम (i = 0; i < smi->num_vlan_mc; i++) अणु
		ret = smi->ops->set_vlan_mc(smi, i, &vlanmc);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rtl8366_reset_vlan);

पूर्णांक rtl8366_init_vlan(काष्ठा realtek_smi *smi)
अणु
	पूर्णांक port;
	पूर्णांक ret;

	ret = rtl8366_reset_vlan(smi);
	अगर (ret)
		वापस ret;

	/* Loop over the available ports, क्रम each port, associate
	 * it with the VLAN (port+1)
	 */
	क्रम (port = 0; port < smi->num_ports; port++) अणु
		u32 mask;

		अगर (port == smi->cpu_port)
			/* For the CPU port, make all ports members of this
			 * VLAN.
			 */
			mask = GENMASK((पूर्णांक)smi->num_ports - 1, 0);
		अन्यथा
			/* For all other ports, enable itself plus the
			 * CPU port.
			 */
			mask = BIT(port) | BIT(smi->cpu_port);

		/* For each port, set the port as member of VLAN (port+1)
		 * and untagged, except क्रम the CPU port: the CPU port (5) is
		 * member of VLAN 6 and so are ALL the other ports as well.
		 * Use filter 0 (no filter).
		 */
		dev_info(smi->dev, "VLAN%d port mask for port %d, %08x\n",
			 (port + 1), port, mask);
		ret = rtl8366_set_vlan(smi, (port + 1), mask, mask, 0);
		अगर (ret)
			वापस ret;

		dev_info(smi->dev, "VLAN%d port %d, PVID set to %d\n",
			 (port + 1), port, (port + 1));
		ret = rtl8366_set_pvid(smi, port, (port + 1));
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस rtl8366_enable_vlan(smi, true);
पूर्ण
EXPORT_SYMBOL_GPL(rtl8366_init_vlan);

पूर्णांक rtl8366_vlan_filtering(काष्ठा dsa_चयन *ds, पूर्णांक port, bool vlan_filtering,
			   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा realtek_smi *smi = ds->priv;
	काष्ठा rtl8366_vlan_4k vlan4k;
	पूर्णांक ret;

	/* Use VLAN nr port + 1 since VLAN0 is not valid */
	अगर (!smi->ops->is_vlan_valid(smi, port + 1))
		वापस -EINVAL;

	dev_info(smi->dev, "%s filtering on port %d\n",
		 vlan_filtering ? "enable" : "disable",
		 port);

	/* TODO:
	 * The hardware support filter ID (FID) 0..7, I have no clue how to
	 * support this in the driver when the callback only says on/off.
	 */
	ret = smi->ops->get_vlan_4k(smi, port + 1, &vlan4k);
	अगर (ret)
		वापस ret;

	/* Just set the filter to FID 1 क्रम now then */
	ret = rtl8366_set_vlan(smi, port + 1,
			       vlan4k.member,
			       vlan4k.untag,
			       1);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rtl8366_vlan_filtering);

पूर्णांक rtl8366_vlan_add(काष्ठा dsa_चयन *ds, पूर्णांक port,
		     स्थिर काष्ठा चयनdev_obj_port_vlan *vlan,
		     काष्ठा netlink_ext_ack *extack)
अणु
	bool untagged = !!(vlan->flags & BRIDGE_VLAN_INFO_UNTAGGED);
	bool pvid = !!(vlan->flags & BRIDGE_VLAN_INFO_PVID);
	काष्ठा realtek_smi *smi = ds->priv;
	u32 member = 0;
	u32 untag = 0;
	पूर्णांक ret;

	अगर (!smi->ops->is_vlan_valid(smi, vlan->vid)) अणु
		NL_SET_ERR_MSG_MOD(extack, "VLAN ID not valid");
		वापस -EINVAL;
	पूर्ण

	/* Enable VLAN in the hardware
	 * FIXME: what's with this 4k business?
	 * Just rtl8366_enable_vlan() seems inconclusive.
	 */
	ret = rtl8366_enable_vlan4k(smi, true);
	अगर (ret) अणु
		NL_SET_ERR_MSG_MOD(extack, "Failed to enable VLAN 4K");
		वापस ret;
	पूर्ण

	dev_info(smi->dev, "add VLAN %d on port %d, %s, %s\n",
		 vlan->vid, port, untagged ? "untagged" : "tagged",
		 pvid ? " PVID" : "no PVID");

	अगर (dsa_is_dsa_port(ds, port) || dsa_is_cpu_port(ds, port))
		dev_err(smi->dev, "port is DSA or CPU port\n");

	member |= BIT(port);

	अगर (untagged)
		untag |= BIT(port);

	ret = rtl8366_set_vlan(smi, vlan->vid, member, untag, 0);
	अगर (ret) अणु
		dev_err(smi->dev, "failed to set up VLAN %04x", vlan->vid);
		वापस ret;
	पूर्ण

	अगर (!pvid)
		वापस 0;

	ret = rtl8366_set_pvid(smi, port, vlan->vid);
	अगर (ret) अणु
		dev_err(smi->dev, "failed to set PVID on port %d to VLAN %04x",
			port, vlan->vid);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rtl8366_vlan_add);

पूर्णांक rtl8366_vlan_del(काष्ठा dsa_चयन *ds, पूर्णांक port,
		     स्थिर काष्ठा चयनdev_obj_port_vlan *vlan)
अणु
	काष्ठा realtek_smi *smi = ds->priv;
	पूर्णांक ret, i;

	dev_info(smi->dev, "del VLAN %04x on port %d\n", vlan->vid, port);

	क्रम (i = 0; i < smi->num_vlan_mc; i++) अणु
		काष्ठा rtl8366_vlan_mc vlanmc;

		ret = smi->ops->get_vlan_mc(smi, i, &vlanmc);
		अगर (ret)
			वापस ret;

		अगर (vlan->vid == vlanmc.vid) अणु
			/* Remove this port from the VLAN */
			vlanmc.member &= ~BIT(port);
			vlanmc.untag &= ~BIT(port);
			/*
			 * If no ports are members of this VLAN
			 * anymore then clear the whole member
			 * config so it can be reused.
			 */
			अगर (!vlanmc.member && vlanmc.untag) अणु
				vlanmc.vid = 0;
				vlanmc.priority = 0;
				vlanmc.fid = 0;
			पूर्ण
			ret = smi->ops->set_vlan_mc(smi, i, &vlanmc);
			अगर (ret) अणु
				dev_err(smi->dev,
					"failed to remove VLAN %04x\n",
					vlan->vid);
				वापस ret;
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rtl8366_vlan_del);

व्योम rtl8366_get_strings(काष्ठा dsa_चयन *ds, पूर्णांक port, u32 stringset,
			 uपूर्णांक8_t *data)
अणु
	काष्ठा realtek_smi *smi = ds->priv;
	काष्ठा rtl8366_mib_counter *mib;
	पूर्णांक i;

	अगर (port >= smi->num_ports)
		वापस;

	क्रम (i = 0; i < smi->num_mib_counters; i++) अणु
		mib = &smi->mib_counters[i];
		म_नकलन(data + i * ETH_GSTRING_LEN,
			mib->name, ETH_GSTRING_LEN);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(rtl8366_get_strings);

पूर्णांक rtl8366_get_sset_count(काष्ठा dsa_चयन *ds, पूर्णांक port, पूर्णांक sset)
अणु
	काष्ठा realtek_smi *smi = ds->priv;

	/* We only support SS_STATS */
	अगर (sset != ETH_SS_STATS)
		वापस 0;
	अगर (port >= smi->num_ports)
		वापस -EINVAL;

	वापस smi->num_mib_counters;
पूर्ण
EXPORT_SYMBOL_GPL(rtl8366_get_sset_count);

व्योम rtl8366_get_ethtool_stats(काष्ठा dsa_चयन *ds, पूर्णांक port, uपूर्णांक64_t *data)
अणु
	काष्ठा realtek_smi *smi = ds->priv;
	पूर्णांक i;
	पूर्णांक ret;

	अगर (port >= smi->num_ports)
		वापस;

	क्रम (i = 0; i < smi->num_mib_counters; i++) अणु
		काष्ठा rtl8366_mib_counter *mib;
		u64 mibvalue = 0;

		mib = &smi->mib_counters[i];
		ret = smi->ops->get_mib_counter(smi, port, mib, &mibvalue);
		अगर (ret) अणु
			dev_err(smi->dev, "error reading MIB counter %s\n",
				mib->name);
		पूर्ण
		data[i] = mibvalue;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(rtl8366_get_ethtool_stats);
