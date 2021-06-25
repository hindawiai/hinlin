<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * DPAA2 Ethernet Switch driver
 *
 * Copyright 2014-2016 Freescale Semiconductor Inc.
 * Copyright 2017-2021 NXP
 *
 */

#समावेश <linux/module.h>

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/msi.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/iommu.h>
#समावेश <net/pkt_cls.h>

#समावेश <linux/fsl/mc.h>

#समावेश "dpaa2-switch.h"

/* Minimal supported DPSW version */
#घोषणा DPSW_MIN_VER_MAJOR		8
#घोषणा DPSW_MIN_VER_MINOR		9

#घोषणा DEFAULT_VLAN_ID			1

अटल u16 dpaa2_चयन_port_get_fdb_id(काष्ठा ethsw_port_priv *port_priv)
अणु
	वापस port_priv->fdb->fdb_id;
पूर्ण

अटल काष्ठा dpaa2_चयन_fdb *dpaa2_चयन_fdb_get_unused(काष्ठा ethsw_core *ethsw)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ethsw->sw_attr.num_अगरs; i++)
		अगर (!ethsw->fdbs[i].in_use)
			वापस &ethsw->fdbs[i];
	वापस शून्य;
पूर्ण

अटल काष्ठा dpaa2_चयन_acl_tbl *
dpaa2_चयन_acl_tbl_get_unused(काष्ठा ethsw_core *ethsw)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ethsw->sw_attr.num_अगरs; i++)
		अगर (!ethsw->acls[i].in_use)
			वापस &ethsw->acls[i];
	वापस शून्य;
पूर्ण

अटल u16 dpaa2_चयन_port_set_fdb(काष्ठा ethsw_port_priv *port_priv,
				     काष्ठा net_device *bridge_dev)
अणु
	काष्ठा ethsw_port_priv *other_port_priv = शून्य;
	काष्ठा dpaa2_चयन_fdb *fdb;
	काष्ठा net_device *other_dev;
	काष्ठा list_head *iter;

	/* If we leave a bridge (bridge_dev is शून्य), find an unused
	 * FDB and use that.
	 */
	अगर (!bridge_dev) अणु
		fdb = dpaa2_चयन_fdb_get_unused(port_priv->ethsw_data);

		/* If there is no unused FDB, we must be the last port that
		 * leaves the last bridge, all the others are standalone. We
		 * can just keep the FDB that we alपढ़ोy have.
		 */

		अगर (!fdb) अणु
			port_priv->fdb->bridge_dev = शून्य;
			वापस 0;
		पूर्ण

		port_priv->fdb = fdb;
		port_priv->fdb->in_use = true;
		port_priv->fdb->bridge_dev = शून्य;
		वापस 0;
	पूर्ण

	/* The below call to netdev_क्रम_each_lower_dev() demands the RTNL lock
	 * being held. Assert on it so that it's easier to catch new code
	 * paths that reach this poपूर्णांक without the RTNL lock.
	 */
	ASSERT_RTNL();

	/* If part of a bridge, use the FDB of the first dpaa2 चयन पूर्णांकerface
	 * to be present in that bridge
	 */
	netdev_क्रम_each_lower_dev(bridge_dev, other_dev, iter) अणु
		अगर (!dpaa2_चयन_port_dev_check(other_dev))
			जारी;

		अगर (other_dev == port_priv->netdev)
			जारी;

		other_port_priv = netdev_priv(other_dev);
		अवरोध;
	पूर्ण

	/* The current port is about to change its FDB to the one used by the
	 * first port that joined the bridge.
	 */
	अगर (other_port_priv) अणु
		/* The previous FDB is about to become unused, since the
		 * पूर्णांकerface is no दीर्घer standalone.
		 */
		port_priv->fdb->in_use = false;
		port_priv->fdb->bridge_dev = शून्य;

		/* Get a reference to the new FDB */
		port_priv->fdb = other_port_priv->fdb;
	पूर्ण

	/* Keep track of the new upper bridge device */
	port_priv->fdb->bridge_dev = bridge_dev;

	वापस 0;
पूर्ण

अटल व्योम dpaa2_चयन_fdb_get_flood_cfg(काष्ठा ethsw_core *ethsw, u16 fdb_id,
					   क्रमागत dpsw_flood_type type,
					   काष्ठा dpsw_egress_flood_cfg *cfg)
अणु
	पूर्णांक i = 0, j;

	स_रखो(cfg, 0, माप(*cfg));

	/* Add all the DPAA2 चयन ports found in the same bridging करोमुख्य to
	 * the egress flooding करोमुख्य
	 */
	क्रम (j = 0; j < ethsw->sw_attr.num_अगरs; j++) अणु
		अगर (!ethsw->ports[j])
			जारी;
		अगर (ethsw->ports[j]->fdb->fdb_id != fdb_id)
			जारी;

		अगर (type == DPSW_BROADCAST && ethsw->ports[j]->bcast_flood)
			cfg->अगर_id[i++] = ethsw->ports[j]->idx;
		अन्यथा अगर (type == DPSW_FLOODING && ethsw->ports[j]->ucast_flood)
			cfg->अगर_id[i++] = ethsw->ports[j]->idx;
	पूर्ण

	/* Add the CTRL पूर्णांकerface to the egress flooding करोमुख्य */
	cfg->अगर_id[i++] = ethsw->sw_attr.num_अगरs;

	cfg->fdb_id = fdb_id;
	cfg->flood_type = type;
	cfg->num_अगरs = i;
पूर्ण

अटल पूर्णांक dpaa2_चयन_fdb_set_egress_flood(काष्ठा ethsw_core *ethsw, u16 fdb_id)
अणु
	काष्ठा dpsw_egress_flood_cfg flood_cfg;
	पूर्णांक err;

	/* Setup broadcast flooding करोमुख्य */
	dpaa2_चयन_fdb_get_flood_cfg(ethsw, fdb_id, DPSW_BROADCAST, &flood_cfg);
	err = dpsw_set_egress_flood(ethsw->mc_io, 0, ethsw->dpsw_handle,
				    &flood_cfg);
	अगर (err) अणु
		dev_err(ethsw->dev, "dpsw_set_egress_flood() = %d\n", err);
		वापस err;
	पूर्ण

	/* Setup unknown flooding करोमुख्य */
	dpaa2_चयन_fdb_get_flood_cfg(ethsw, fdb_id, DPSW_FLOODING, &flood_cfg);
	err = dpsw_set_egress_flood(ethsw->mc_io, 0, ethsw->dpsw_handle,
				    &flood_cfg);
	अगर (err) अणु
		dev_err(ethsw->dev, "dpsw_set_egress_flood() = %d\n", err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम *dpaa2_iova_to_virt(काष्ठा iommu_करोमुख्य *करोमुख्य,
				dma_addr_t iova_addr)
अणु
	phys_addr_t phys_addr;

	phys_addr = करोमुख्य ? iommu_iova_to_phys(करोमुख्य, iova_addr) : iova_addr;

	वापस phys_to_virt(phys_addr);
पूर्ण

अटल पूर्णांक dpaa2_चयन_add_vlan(काष्ठा ethsw_port_priv *port_priv, u16 vid)
अणु
	काष्ठा ethsw_core *ethsw = port_priv->ethsw_data;
	काष्ठा dpsw_vlan_cfg vcfg = अणु0पूर्ण;
	पूर्णांक err;

	vcfg.fdb_id = dpaa2_चयन_port_get_fdb_id(port_priv);
	err = dpsw_vlan_add(ethsw->mc_io, 0,
			    ethsw->dpsw_handle, vid, &vcfg);
	अगर (err) अणु
		dev_err(ethsw->dev, "dpsw_vlan_add err %d\n", err);
		वापस err;
	पूर्ण
	ethsw->vlans[vid] = ETHSW_VLAN_MEMBER;

	वापस 0;
पूर्ण

अटल bool dpaa2_चयन_port_is_up(काष्ठा ethsw_port_priv *port_priv)
अणु
	काष्ठा net_device *netdev = port_priv->netdev;
	काष्ठा dpsw_link_state state;
	पूर्णांक err;

	err = dpsw_अगर_get_link_state(port_priv->ethsw_data->mc_io, 0,
				     port_priv->ethsw_data->dpsw_handle,
				     port_priv->idx, &state);
	अगर (err) अणु
		netdev_err(netdev, "dpsw_if_get_link_state() err %d\n", err);
		वापस true;
	पूर्ण

	WARN_ONCE(state.up > 1, "Garbage read into link_state");

	वापस state.up ? true : false;
पूर्ण

अटल पूर्णांक dpaa2_चयन_port_set_pvid(काष्ठा ethsw_port_priv *port_priv, u16 pvid)
अणु
	काष्ठा ethsw_core *ethsw = port_priv->ethsw_data;
	काष्ठा net_device *netdev = port_priv->netdev;
	काष्ठा dpsw_tci_cfg tci_cfg = अणु 0 पूर्ण;
	bool up;
	पूर्णांक err, ret;

	err = dpsw_अगर_get_tci(ethsw->mc_io, 0, ethsw->dpsw_handle,
			      port_priv->idx, &tci_cfg);
	अगर (err) अणु
		netdev_err(netdev, "dpsw_if_get_tci err %d\n", err);
		वापस err;
	पूर्ण

	tci_cfg.vlan_id = pvid;

	/* Interface needs to be करोwn to change PVID */
	up = dpaa2_चयन_port_is_up(port_priv);
	अगर (up) अणु
		err = dpsw_अगर_disable(ethsw->mc_io, 0,
				      ethsw->dpsw_handle,
				      port_priv->idx);
		अगर (err) अणु
			netdev_err(netdev, "dpsw_if_disable err %d\n", err);
			वापस err;
		पूर्ण
	पूर्ण

	err = dpsw_अगर_set_tci(ethsw->mc_io, 0, ethsw->dpsw_handle,
			      port_priv->idx, &tci_cfg);
	अगर (err) अणु
		netdev_err(netdev, "dpsw_if_set_tci err %d\n", err);
		जाओ set_tci_error;
	पूर्ण

	/* Delete previous PVID info and mark the new one */
	port_priv->vlans[port_priv->pvid] &= ~ETHSW_VLAN_PVID;
	port_priv->vlans[pvid] |= ETHSW_VLAN_PVID;
	port_priv->pvid = pvid;

set_tci_error:
	अगर (up) अणु
		ret = dpsw_अगर_enable(ethsw->mc_io, 0,
				     ethsw->dpsw_handle,
				     port_priv->idx);
		अगर (ret) अणु
			netdev_err(netdev, "dpsw_if_enable err %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक dpaa2_चयन_port_add_vlan(काष्ठा ethsw_port_priv *port_priv,
				      u16 vid, u16 flags)
अणु
	काष्ठा ethsw_core *ethsw = port_priv->ethsw_data;
	काष्ठा net_device *netdev = port_priv->netdev;
	काष्ठा dpsw_vlan_अगर_cfg vcfg = अणु0पूर्ण;
	पूर्णांक err;

	अगर (port_priv->vlans[vid]) अणु
		netdev_warn(netdev, "VLAN %d already configured\n", vid);
		वापस -EEXIST;
	पूर्ण

	/* If hit, this VLAN rule will lead the packet पूर्णांकo the FDB table
	 * specअगरied in the vlan configuration below
	 */
	vcfg.num_अगरs = 1;
	vcfg.अगर_id[0] = port_priv->idx;
	vcfg.fdb_id = dpaa2_चयन_port_get_fdb_id(port_priv);
	vcfg.options |= DPSW_VLAN_ADD_IF_OPT_FDB_ID;
	err = dpsw_vlan_add_अगर(ethsw->mc_io, 0, ethsw->dpsw_handle, vid, &vcfg);
	अगर (err) अणु
		netdev_err(netdev, "dpsw_vlan_add_if err %d\n", err);
		वापस err;
	पूर्ण

	port_priv->vlans[vid] = ETHSW_VLAN_MEMBER;

	अगर (flags & BRIDGE_VLAN_INFO_UNTAGGED) अणु
		err = dpsw_vlan_add_अगर_untagged(ethsw->mc_io, 0,
						ethsw->dpsw_handle,
						vid, &vcfg);
		अगर (err) अणु
			netdev_err(netdev,
				   "dpsw_vlan_add_if_untagged err %d\n", err);
			वापस err;
		पूर्ण
		port_priv->vlans[vid] |= ETHSW_VLAN_UNTAGGED;
	पूर्ण

	अगर (flags & BRIDGE_VLAN_INFO_PVID) अणु
		err = dpaa2_चयन_port_set_pvid(port_priv, vid);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल क्रमागत dpsw_stp_state br_stp_state_to_dpsw(u8 state)
अणु
	चयन (state) अणु
	हाल BR_STATE_DISABLED:
		वापस DPSW_STP_STATE_DISABLED;
	हाल BR_STATE_LISTENING:
		वापस DPSW_STP_STATE_LISTENING;
	हाल BR_STATE_LEARNING:
		वापस DPSW_STP_STATE_LEARNING;
	हाल BR_STATE_FORWARDING:
		वापस DPSW_STP_STATE_FORWARDING;
	हाल BR_STATE_BLOCKING:
		वापस DPSW_STP_STATE_BLOCKING;
	शेष:
		वापस DPSW_STP_STATE_DISABLED;
	पूर्ण
पूर्ण

अटल पूर्णांक dpaa2_चयन_port_set_stp_state(काष्ठा ethsw_port_priv *port_priv, u8 state)
अणु
	काष्ठा dpsw_stp_cfg stp_cfg = अणु0पूर्ण;
	पूर्णांक err;
	u16 vid;

	अगर (!netअगर_running(port_priv->netdev) || state == port_priv->stp_state)
		वापस 0;	/* Nothing to करो */

	stp_cfg.state = br_stp_state_to_dpsw(state);
	क्रम (vid = 0; vid <= VLAN_VID_MASK; vid++) अणु
		अगर (port_priv->vlans[vid] & ETHSW_VLAN_MEMBER) अणु
			stp_cfg.vlan_id = vid;
			err = dpsw_अगर_set_stp(port_priv->ethsw_data->mc_io, 0,
					      port_priv->ethsw_data->dpsw_handle,
					      port_priv->idx, &stp_cfg);
			अगर (err) अणु
				netdev_err(port_priv->netdev,
					   "dpsw_if_set_stp err %d\n", err);
				वापस err;
			पूर्ण
		पूर्ण
	पूर्ण

	port_priv->stp_state = state;

	वापस 0;
पूर्ण

अटल पूर्णांक dpaa2_चयन_dellink(काष्ठा ethsw_core *ethsw, u16 vid)
अणु
	काष्ठा ethsw_port_priv *ppriv_local = शून्य;
	पूर्णांक i, err;

	अगर (!ethsw->vlans[vid])
		वापस -ENOENT;

	err = dpsw_vlan_हटाओ(ethsw->mc_io, 0, ethsw->dpsw_handle, vid);
	अगर (err) अणु
		dev_err(ethsw->dev, "dpsw_vlan_remove err %d\n", err);
		वापस err;
	पूर्ण
	ethsw->vlans[vid] = 0;

	क्रम (i = 0; i < ethsw->sw_attr.num_अगरs; i++) अणु
		ppriv_local = ethsw->ports[i];
		ppriv_local->vlans[vid] = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dpaa2_चयन_port_fdb_add_uc(काष्ठा ethsw_port_priv *port_priv,
					स्थिर अचिन्हित अक्षर *addr)
अणु
	काष्ठा dpsw_fdb_unicast_cfg entry = अणु0पूर्ण;
	u16 fdb_id;
	पूर्णांक err;

	entry.अगर_egress = port_priv->idx;
	entry.type = DPSW_FDB_ENTRY_STATIC;
	ether_addr_copy(entry.mac_addr, addr);

	fdb_id = dpaa2_चयन_port_get_fdb_id(port_priv);
	err = dpsw_fdb_add_unicast(port_priv->ethsw_data->mc_io, 0,
				   port_priv->ethsw_data->dpsw_handle,
				   fdb_id, &entry);
	अगर (err)
		netdev_err(port_priv->netdev,
			   "dpsw_fdb_add_unicast err %d\n", err);
	वापस err;
पूर्ण

अटल पूर्णांक dpaa2_चयन_port_fdb_del_uc(काष्ठा ethsw_port_priv *port_priv,
					स्थिर अचिन्हित अक्षर *addr)
अणु
	काष्ठा dpsw_fdb_unicast_cfg entry = अणु0पूर्ण;
	u16 fdb_id;
	पूर्णांक err;

	entry.अगर_egress = port_priv->idx;
	entry.type = DPSW_FDB_ENTRY_STATIC;
	ether_addr_copy(entry.mac_addr, addr);

	fdb_id = dpaa2_चयन_port_get_fdb_id(port_priv);
	err = dpsw_fdb_हटाओ_unicast(port_priv->ethsw_data->mc_io, 0,
				      port_priv->ethsw_data->dpsw_handle,
				      fdb_id, &entry);
	/* Silently discard error क्रम calling multiple बार the del command */
	अगर (err && err != -ENXIO)
		netdev_err(port_priv->netdev,
			   "dpsw_fdb_remove_unicast err %d\n", err);
	वापस err;
पूर्ण

अटल पूर्णांक dpaa2_चयन_port_fdb_add_mc(काष्ठा ethsw_port_priv *port_priv,
					स्थिर अचिन्हित अक्षर *addr)
अणु
	काष्ठा dpsw_fdb_multicast_cfg entry = अणु0पूर्ण;
	u16 fdb_id;
	पूर्णांक err;

	ether_addr_copy(entry.mac_addr, addr);
	entry.type = DPSW_FDB_ENTRY_STATIC;
	entry.num_अगरs = 1;
	entry.अगर_id[0] = port_priv->idx;

	fdb_id = dpaa2_चयन_port_get_fdb_id(port_priv);
	err = dpsw_fdb_add_multicast(port_priv->ethsw_data->mc_io, 0,
				     port_priv->ethsw_data->dpsw_handle,
				     fdb_id, &entry);
	/* Silently discard error क्रम calling multiple बार the add command */
	अगर (err && err != -ENXIO)
		netdev_err(port_priv->netdev, "dpsw_fdb_add_multicast err %d\n",
			   err);
	वापस err;
पूर्ण

अटल पूर्णांक dpaa2_चयन_port_fdb_del_mc(काष्ठा ethsw_port_priv *port_priv,
					स्थिर अचिन्हित अक्षर *addr)
अणु
	काष्ठा dpsw_fdb_multicast_cfg entry = अणु0पूर्ण;
	u16 fdb_id;
	पूर्णांक err;

	ether_addr_copy(entry.mac_addr, addr);
	entry.type = DPSW_FDB_ENTRY_STATIC;
	entry.num_अगरs = 1;
	entry.अगर_id[0] = port_priv->idx;

	fdb_id = dpaa2_चयन_port_get_fdb_id(port_priv);
	err = dpsw_fdb_हटाओ_multicast(port_priv->ethsw_data->mc_io, 0,
					port_priv->ethsw_data->dpsw_handle,
					fdb_id, &entry);
	/* Silently discard error क्रम calling multiple बार the del command */
	अगर (err && err != -ENAVAIL)
		netdev_err(port_priv->netdev,
			   "dpsw_fdb_remove_multicast err %d\n", err);
	वापस err;
पूर्ण

अटल व्योम dpaa2_चयन_port_get_stats(काष्ठा net_device *netdev,
					काष्ठा rtnl_link_stats64 *stats)
अणु
	काष्ठा ethsw_port_priv *port_priv = netdev_priv(netdev);
	u64 पंचांगp;
	पूर्णांक err;

	err = dpsw_अगर_get_counter(port_priv->ethsw_data->mc_io, 0,
				  port_priv->ethsw_data->dpsw_handle,
				  port_priv->idx,
				  DPSW_CNT_ING_FRAME, &stats->rx_packets);
	अगर (err)
		जाओ error;

	err = dpsw_अगर_get_counter(port_priv->ethsw_data->mc_io, 0,
				  port_priv->ethsw_data->dpsw_handle,
				  port_priv->idx,
				  DPSW_CNT_EGR_FRAME, &stats->tx_packets);
	अगर (err)
		जाओ error;

	err = dpsw_अगर_get_counter(port_priv->ethsw_data->mc_io, 0,
				  port_priv->ethsw_data->dpsw_handle,
				  port_priv->idx,
				  DPSW_CNT_ING_BYTE, &stats->rx_bytes);
	अगर (err)
		जाओ error;

	err = dpsw_अगर_get_counter(port_priv->ethsw_data->mc_io, 0,
				  port_priv->ethsw_data->dpsw_handle,
				  port_priv->idx,
				  DPSW_CNT_EGR_BYTE, &stats->tx_bytes);
	अगर (err)
		जाओ error;

	err = dpsw_अगर_get_counter(port_priv->ethsw_data->mc_io, 0,
				  port_priv->ethsw_data->dpsw_handle,
				  port_priv->idx,
				  DPSW_CNT_ING_FRAME_DISCARD,
				  &stats->rx_dropped);
	अगर (err)
		जाओ error;

	err = dpsw_अगर_get_counter(port_priv->ethsw_data->mc_io, 0,
				  port_priv->ethsw_data->dpsw_handle,
				  port_priv->idx,
				  DPSW_CNT_ING_FLTR_FRAME,
				  &पंचांगp);
	अगर (err)
		जाओ error;
	stats->rx_dropped += पंचांगp;

	err = dpsw_अगर_get_counter(port_priv->ethsw_data->mc_io, 0,
				  port_priv->ethsw_data->dpsw_handle,
				  port_priv->idx,
				  DPSW_CNT_EGR_FRAME_DISCARD,
				  &stats->tx_dropped);
	अगर (err)
		जाओ error;

	वापस;

error:
	netdev_err(netdev, "dpsw_if_get_counter err %d\n", err);
पूर्ण

अटल bool dpaa2_चयन_port_has_offload_stats(स्थिर काष्ठा net_device *netdev,
						पूर्णांक attr_id)
अणु
	वापस (attr_id == IFLA_OFFLOAD_XSTATS_CPU_HIT);
पूर्ण

अटल पूर्णांक dpaa2_चयन_port_get_offload_stats(पूर्णांक attr_id,
					       स्थिर काष्ठा net_device *netdev,
					       व्योम *sp)
अणु
	चयन (attr_id) अणु
	हाल IFLA_OFFLOAD_XSTATS_CPU_HIT:
		dpaa2_चयन_port_get_stats((काष्ठा net_device *)netdev, sp);
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक dpaa2_चयन_port_change_mtu(काष्ठा net_device *netdev, पूर्णांक mtu)
अणु
	काष्ठा ethsw_port_priv *port_priv = netdev_priv(netdev);
	पूर्णांक err;

	err = dpsw_अगर_set_max_frame_length(port_priv->ethsw_data->mc_io,
					   0,
					   port_priv->ethsw_data->dpsw_handle,
					   port_priv->idx,
					   (u16)ETHSW_L2_MAX_FRM(mtu));
	अगर (err) अणु
		netdev_err(netdev,
			   "dpsw_if_set_max_frame_length() err %d\n", err);
		वापस err;
	पूर्ण

	netdev->mtu = mtu;
	वापस 0;
पूर्ण

अटल पूर्णांक dpaa2_चयन_port_carrier_state_sync(काष्ठा net_device *netdev)
अणु
	काष्ठा ethsw_port_priv *port_priv = netdev_priv(netdev);
	काष्ठा dpsw_link_state state;
	पूर्णांक err;

	/* Interrupts are received even though no one issued an 'ifconfig up'
	 * on the चयन पूर्णांकerface. Ignore these link state update पूर्णांकerrupts
	 */
	अगर (!netअगर_running(netdev))
		वापस 0;

	err = dpsw_अगर_get_link_state(port_priv->ethsw_data->mc_io, 0,
				     port_priv->ethsw_data->dpsw_handle,
				     port_priv->idx, &state);
	अगर (err) अणु
		netdev_err(netdev, "dpsw_if_get_link_state() err %d\n", err);
		वापस err;
	पूर्ण

	WARN_ONCE(state.up > 1, "Garbage read into link_state");

	अगर (state.up != port_priv->link_state) अणु
		अगर (state.up) अणु
			netअगर_carrier_on(netdev);
			netअगर_tx_start_all_queues(netdev);
		पूर्ण अन्यथा अणु
			netअगर_carrier_off(netdev);
			netअगर_tx_stop_all_queues(netdev);
		पूर्ण
		port_priv->link_state = state.up;
	पूर्ण

	वापस 0;
पूर्ण

/* Manage all NAPI instances क्रम the control पूर्णांकerface.
 *
 * We only have one RX queue and one Tx Conf queue क्रम all
 * चयन ports. Thereक्रमe, we only need to enable the NAPI instance once, the
 * first समय one of the चयन ports runs .dev_खोलो().
 */

अटल व्योम dpaa2_चयन_enable_ctrl_अगर_napi(काष्ठा ethsw_core *ethsw)
अणु
	पूर्णांक i;

	/* Access to the ethsw->napi_users relies on the RTNL lock */
	ASSERT_RTNL();

	/* a new पूर्णांकerface is using the NAPI instance */
	ethsw->napi_users++;

	/* अगर there is alपढ़ोy a user of the instance, वापस */
	अगर (ethsw->napi_users > 1)
		वापस;

	क्रम (i = 0; i < DPAA2_SWITCH_RX_NUM_FQS; i++)
		napi_enable(&ethsw->fq[i].napi);
पूर्ण

अटल व्योम dpaa2_चयन_disable_ctrl_अगर_napi(काष्ठा ethsw_core *ethsw)
अणु
	पूर्णांक i;

	/* Access to the ethsw->napi_users relies on the RTNL lock */
	ASSERT_RTNL();

	/* If we are not the last पूर्णांकerface using the NAPI, वापस */
	ethsw->napi_users--;
	अगर (ethsw->napi_users)
		वापस;

	क्रम (i = 0; i < DPAA2_SWITCH_RX_NUM_FQS; i++)
		napi_disable(&ethsw->fq[i].napi);
पूर्ण

अटल पूर्णांक dpaa2_चयन_port_खोलो(काष्ठा net_device *netdev)
अणु
	काष्ठा ethsw_port_priv *port_priv = netdev_priv(netdev);
	काष्ठा ethsw_core *ethsw = port_priv->ethsw_data;
	पूर्णांक err;

	/* Explicitly set carrier off, otherwise
	 * netअगर_carrier_ok() will वापस true and cause 'ip link show'
	 * to report the LOWER_UP flag, even though the link
	 * notअगरication wasn't even received.
	 */
	netअगर_carrier_off(netdev);

	err = dpsw_अगर_enable(port_priv->ethsw_data->mc_io, 0,
			     port_priv->ethsw_data->dpsw_handle,
			     port_priv->idx);
	अगर (err) अणु
		netdev_err(netdev, "dpsw_if_enable err %d\n", err);
		वापस err;
	पूर्ण

	/* sync carrier state */
	err = dpaa2_चयन_port_carrier_state_sync(netdev);
	अगर (err) अणु
		netdev_err(netdev,
			   "dpaa2_switch_port_carrier_state_sync err %d\n", err);
		जाओ err_carrier_sync;
	पूर्ण

	dpaa2_चयन_enable_ctrl_अगर_napi(ethsw);

	वापस 0;

err_carrier_sync:
	dpsw_अगर_disable(port_priv->ethsw_data->mc_io, 0,
			port_priv->ethsw_data->dpsw_handle,
			port_priv->idx);
	वापस err;
पूर्ण

अटल पूर्णांक dpaa2_चयन_port_stop(काष्ठा net_device *netdev)
अणु
	काष्ठा ethsw_port_priv *port_priv = netdev_priv(netdev);
	काष्ठा ethsw_core *ethsw = port_priv->ethsw_data;
	पूर्णांक err;

	err = dpsw_अगर_disable(port_priv->ethsw_data->mc_io, 0,
			      port_priv->ethsw_data->dpsw_handle,
			      port_priv->idx);
	अगर (err) अणु
		netdev_err(netdev, "dpsw_if_disable err %d\n", err);
		वापस err;
	पूर्ण

	dpaa2_चयन_disable_ctrl_अगर_napi(ethsw);

	वापस 0;
पूर्ण

अटल पूर्णांक dpaa2_चयन_port_parent_id(काष्ठा net_device *dev,
				       काष्ठा netdev_phys_item_id *ppid)
अणु
	काष्ठा ethsw_port_priv *port_priv = netdev_priv(dev);

	ppid->id_len = 1;
	ppid->id[0] = port_priv->ethsw_data->dev_id;

	वापस 0;
पूर्ण

अटल पूर्णांक dpaa2_चयन_port_get_phys_name(काष्ठा net_device *netdev, अक्षर *name,
					   माप_प्रकार len)
अणु
	काष्ठा ethsw_port_priv *port_priv = netdev_priv(netdev);
	पूर्णांक err;

	err = snम_लिखो(name, len, "p%d", port_priv->idx);
	अगर (err >= len)
		वापस -EINVAL;

	वापस 0;
पूर्ण

काष्ठा ethsw_dump_ctx अणु
	काष्ठा net_device *dev;
	काष्ठा sk_buff *skb;
	काष्ठा netlink_callback *cb;
	पूर्णांक idx;
पूर्ण;

अटल पूर्णांक dpaa2_चयन_fdb_dump_nl(काष्ठा fdb_dump_entry *entry,
				    काष्ठा ethsw_dump_ctx *dump)
अणु
	पूर्णांक is_dynamic = entry->type & DPSW_FDB_ENTRY_DINAMIC;
	u32 portid = NETLINK_CB(dump->cb->skb).portid;
	u32 seq = dump->cb->nlh->nlmsg_seq;
	काष्ठा nlmsghdr *nlh;
	काष्ठा ndmsg *ndm;

	अगर (dump->idx < dump->cb->args[2])
		जाओ skip;

	nlh = nlmsg_put(dump->skb, portid, seq, RTM_NEWNEIGH,
			माप(*ndm), NLM_F_MULTI);
	अगर (!nlh)
		वापस -EMSGSIZE;

	ndm = nlmsg_data(nlh);
	ndm->ndm_family  = AF_BRIDGE;
	ndm->ndm_pad1    = 0;
	ndm->ndm_pad2    = 0;
	ndm->ndm_flags   = NTF_SELF;
	ndm->ndm_type    = 0;
	ndm->ndm_अगरindex = dump->dev->अगरindex;
	ndm->ndm_state   = is_dynamic ? NUD_REACHABLE : NUD_NOARP;

	अगर (nla_put(dump->skb, NDA_LLADDR, ETH_ALEN, entry->mac_addr))
		जाओ nla_put_failure;

	nlmsg_end(dump->skb, nlh);

skip:
	dump->idx++;
	वापस 0;

nla_put_failure:
	nlmsg_cancel(dump->skb, nlh);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक dpaa2_चयन_port_fdb_valid_entry(काष्ठा fdb_dump_entry *entry,
					     काष्ठा ethsw_port_priv *port_priv)
अणु
	पूर्णांक idx = port_priv->idx;
	पूर्णांक valid;

	अगर (entry->type & DPSW_FDB_ENTRY_TYPE_UNICAST)
		valid = entry->अगर_info == port_priv->idx;
	अन्यथा
		valid = entry->अगर_mask[idx / 8] & BIT(idx % 8);

	वापस valid;
पूर्ण

अटल पूर्णांक dpaa2_चयन_fdb_iterate(काष्ठा ethsw_port_priv *port_priv,
				    dpaa2_चयन_fdb_cb_t cb, व्योम *data)
अणु
	काष्ठा net_device *net_dev = port_priv->netdev;
	काष्ठा ethsw_core *ethsw = port_priv->ethsw_data;
	काष्ठा device *dev = net_dev->dev.parent;
	काष्ठा fdb_dump_entry *fdb_entries;
	काष्ठा fdb_dump_entry fdb_entry;
	dma_addr_t fdb_dump_iova;
	u16 num_fdb_entries;
	u32 fdb_dump_size;
	पूर्णांक err = 0, i;
	u8 *dma_mem;
	u16 fdb_id;

	fdb_dump_size = ethsw->sw_attr.max_fdb_entries * माप(fdb_entry);
	dma_mem = kzalloc(fdb_dump_size, GFP_KERNEL);
	अगर (!dma_mem)
		वापस -ENOMEM;

	fdb_dump_iova = dma_map_single(dev, dma_mem, fdb_dump_size,
				       DMA_FROM_DEVICE);
	अगर (dma_mapping_error(dev, fdb_dump_iova)) अणु
		netdev_err(net_dev, "dma_map_single() failed\n");
		err = -ENOMEM;
		जाओ err_map;
	पूर्ण

	fdb_id = dpaa2_चयन_port_get_fdb_id(port_priv);
	err = dpsw_fdb_dump(ethsw->mc_io, 0, ethsw->dpsw_handle, fdb_id,
			    fdb_dump_iova, fdb_dump_size, &num_fdb_entries);
	अगर (err) अणु
		netdev_err(net_dev, "dpsw_fdb_dump() = %d\n", err);
		जाओ err_dump;
	पूर्ण

	dma_unmap_single(dev, fdb_dump_iova, fdb_dump_size, DMA_FROM_DEVICE);

	fdb_entries = (काष्ठा fdb_dump_entry *)dma_mem;
	क्रम (i = 0; i < num_fdb_entries; i++) अणु
		fdb_entry = fdb_entries[i];

		err = cb(port_priv, &fdb_entry, data);
		अगर (err)
			जाओ end;
	पूर्ण

end:
	kमुक्त(dma_mem);

	वापस 0;

err_dump:
	dma_unmap_single(dev, fdb_dump_iova, fdb_dump_size, DMA_TO_DEVICE);
err_map:
	kमुक्त(dma_mem);
	वापस err;
पूर्ण

अटल पूर्णांक dpaa2_चयन_fdb_entry_dump(काष्ठा ethsw_port_priv *port_priv,
				       काष्ठा fdb_dump_entry *fdb_entry,
				       व्योम *data)
अणु
	अगर (!dpaa2_चयन_port_fdb_valid_entry(fdb_entry, port_priv))
		वापस 0;

	वापस dpaa2_चयन_fdb_dump_nl(fdb_entry, data);
पूर्ण

अटल पूर्णांक dpaa2_चयन_port_fdb_dump(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb,
				      काष्ठा net_device *net_dev,
				      काष्ठा net_device *filter_dev, पूर्णांक *idx)
अणु
	काष्ठा ethsw_port_priv *port_priv = netdev_priv(net_dev);
	काष्ठा ethsw_dump_ctx dump = अणु
		.dev = net_dev,
		.skb = skb,
		.cb = cb,
		.idx = *idx,
	पूर्ण;
	पूर्णांक err;

	err = dpaa2_चयन_fdb_iterate(port_priv, dpaa2_चयन_fdb_entry_dump, &dump);
	*idx = dump.idx;

	वापस err;
पूर्ण

अटल पूर्णांक dpaa2_चयन_fdb_entry_fast_age(काष्ठा ethsw_port_priv *port_priv,
					   काष्ठा fdb_dump_entry *fdb_entry,
					   व्योम *data __always_unused)
अणु
	अगर (!dpaa2_चयन_port_fdb_valid_entry(fdb_entry, port_priv))
		वापस 0;

	अगर (!(fdb_entry->type & DPSW_FDB_ENTRY_TYPE_DYNAMIC))
		वापस 0;

	अगर (fdb_entry->type & DPSW_FDB_ENTRY_TYPE_UNICAST)
		dpaa2_चयन_port_fdb_del_uc(port_priv, fdb_entry->mac_addr);
	अन्यथा
		dpaa2_चयन_port_fdb_del_mc(port_priv, fdb_entry->mac_addr);

	वापस 0;
पूर्ण

अटल व्योम dpaa2_चयन_port_fast_age(काष्ठा ethsw_port_priv *port_priv)
अणु
	dpaa2_चयन_fdb_iterate(port_priv,
				 dpaa2_चयन_fdb_entry_fast_age, शून्य);
पूर्ण

अटल पूर्णांक dpaa2_चयन_port_vlan_add(काष्ठा net_device *netdev, __be16 proto,
				      u16 vid)
अणु
	काष्ठा चयनdev_obj_port_vlan vlan = अणु
		.obj.id = SWITCHDEV_OBJ_ID_PORT_VLAN,
		.vid = vid,
		.obj.orig_dev = netdev,
		/* This API only allows programming tagged, non-PVID VIDs */
		.flags = 0,
	पूर्ण;

	वापस dpaa2_चयन_port_vlans_add(netdev, &vlan);
पूर्ण

अटल पूर्णांक dpaa2_चयन_port_vlan_समाप्त(काष्ठा net_device *netdev, __be16 proto,
				       u16 vid)
अणु
	काष्ठा चयनdev_obj_port_vlan vlan = अणु
		.obj.id = SWITCHDEV_OBJ_ID_PORT_VLAN,
		.vid = vid,
		.obj.orig_dev = netdev,
		/* This API only allows programming tagged, non-PVID VIDs */
		.flags = 0,
	पूर्ण;

	वापस dpaa2_चयन_port_vlans_del(netdev, &vlan);
पूर्ण

अटल पूर्णांक dpaa2_चयन_port_set_mac_addr(काष्ठा ethsw_port_priv *port_priv)
अणु
	काष्ठा ethsw_core *ethsw = port_priv->ethsw_data;
	काष्ठा net_device *net_dev = port_priv->netdev;
	काष्ठा device *dev = net_dev->dev.parent;
	u8 mac_addr[ETH_ALEN];
	पूर्णांक err;

	अगर (!(ethsw->features & ETHSW_FEATURE_MAC_ADDR))
		वापस 0;

	/* Get firmware address, अगर any */
	err = dpsw_अगर_get_port_mac_addr(ethsw->mc_io, 0, ethsw->dpsw_handle,
					port_priv->idx, mac_addr);
	अगर (err) अणु
		dev_err(dev, "dpsw_if_get_port_mac_addr() failed\n");
		वापस err;
	पूर्ण

	/* First check अगर firmware has any address configured by bootloader */
	अगर (!is_zero_ether_addr(mac_addr)) अणु
		स_नकल(net_dev->dev_addr, mac_addr, net_dev->addr_len);
	पूर्ण अन्यथा अणु
		/* No MAC address configured, fill in net_dev->dev_addr
		 * with a अक्रमom one
		 */
		eth_hw_addr_अक्रमom(net_dev);
		dev_dbg_once(dev, "device(s) have all-zero hwaddr, replaced with random\n");

		/* Override NET_ADDR_RANDOM set by eth_hw_addr_अक्रमom(); क्रम all
		 * practical purposes, this will be our "permanent" mac address,
		 * at least until the next reboot. This move will also permit
		 * रेजिस्टर_netdevice() to properly fill up net_dev->perm_addr.
		 */
		net_dev->addr_assign_type = NET_ADDR_PERM;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम dpaa2_चयन_मुक्त_fd(स्थिर काष्ठा ethsw_core *ethsw,
				 स्थिर काष्ठा dpaa2_fd *fd)
अणु
	काष्ठा device *dev = ethsw->dev;
	अचिन्हित अक्षर *buffer_start;
	काष्ठा sk_buff **skbh, *skb;
	dma_addr_t fd_addr;

	fd_addr = dpaa2_fd_get_addr(fd);
	skbh = dpaa2_iova_to_virt(ethsw->iommu_करोमुख्य, fd_addr);

	skb = *skbh;
	buffer_start = (अचिन्हित अक्षर *)skbh;

	dma_unmap_single(dev, fd_addr,
			 skb_tail_poपूर्णांकer(skb) - buffer_start,
			 DMA_TO_DEVICE);

	/* Move on with skb release */
	dev_kमुक्त_skb(skb);
पूर्ण

अटल पूर्णांक dpaa2_चयन_build_single_fd(काष्ठा ethsw_core *ethsw,
					काष्ठा sk_buff *skb,
					काष्ठा dpaa2_fd *fd)
अणु
	काष्ठा device *dev = ethsw->dev;
	काष्ठा sk_buff **skbh;
	dma_addr_t addr;
	u8 *buff_start;
	व्योम *hwa;

	buff_start = PTR_ALIGN(skb->data - DPAA2_SWITCH_TX_DATA_OFFSET -
			       DPAA2_SWITCH_TX_BUF_ALIGN,
			       DPAA2_SWITCH_TX_BUF_ALIGN);

	/* Clear FAS to have consistent values क्रम TX confirmation. It is
	 * located in the first 8 bytes of the buffer's hardware annotation
	 * area
	 */
	hwa = buff_start + DPAA2_SWITCH_SWA_SIZE;
	स_रखो(hwa, 0, 8);

	/* Store a backpoपूर्णांकer to the skb at the beginning of the buffer
	 * (in the निजी data area) such that we can release it
	 * on Tx confirm
	 */
	skbh = (काष्ठा sk_buff **)buff_start;
	*skbh = skb;

	addr = dma_map_single(dev, buff_start,
			      skb_tail_poपूर्णांकer(skb) - buff_start,
			      DMA_TO_DEVICE);
	अगर (unlikely(dma_mapping_error(dev, addr)))
		वापस -ENOMEM;

	/* Setup the FD fields */
	स_रखो(fd, 0, माप(*fd));

	dpaa2_fd_set_addr(fd, addr);
	dpaa2_fd_set_offset(fd, (u16)(skb->data - buff_start));
	dpaa2_fd_set_len(fd, skb->len);
	dpaa2_fd_set_क्रमmat(fd, dpaa2_fd_single);

	वापस 0;
पूर्ण

अटल netdev_tx_t dpaa2_चयन_port_tx(काष्ठा sk_buff *skb,
					काष्ठा net_device *net_dev)
अणु
	काष्ठा ethsw_port_priv *port_priv = netdev_priv(net_dev);
	काष्ठा ethsw_core *ethsw = port_priv->ethsw_data;
	पूर्णांक retries = DPAA2_SWITCH_SWP_BUSY_RETRIES;
	काष्ठा dpaa2_fd fd;
	पूर्णांक err;

	अगर (unlikely(skb_headroom(skb) < DPAA2_SWITCH_NEEDED_HEADROOM)) अणु
		काष्ठा sk_buff *ns;

		ns = skb_पुनः_स्मृति_headroom(skb, DPAA2_SWITCH_NEEDED_HEADROOM);
		अगर (unlikely(!ns)) अणु
			net_err_ratelimited("%s: Error reallocating skb headroom\n", net_dev->name);
			जाओ err_मुक्त_skb;
		पूर्ण
		dev_consume_skb_any(skb);
		skb = ns;
	पूर्ण

	/* We'll be holding a back-reference to the skb until Tx confirmation */
	skb = skb_unshare(skb, GFP_ATOMIC);
	अगर (unlikely(!skb)) अणु
		/* skb_unshare() has alपढ़ोy मुक्तd the skb */
		net_err_ratelimited("%s: Error copying the socket buffer\n", net_dev->name);
		जाओ err_निकास;
	पूर्ण

	/* At this stage, we करो not support non-linear skbs so just try to
	 * linearize the skb and अगर that's not working, just drop the packet.
	 */
	err = skb_linearize(skb);
	अगर (err) अणु
		net_err_ratelimited("%s: skb_linearize error (%d)!\n", net_dev->name, err);
		जाओ err_मुक्त_skb;
	पूर्ण

	err = dpaa2_चयन_build_single_fd(ethsw, skb, &fd);
	अगर (unlikely(err)) अणु
		net_err_ratelimited("%s: ethsw_build_*_fd() %d\n", net_dev->name, err);
		जाओ err_मुक्त_skb;
	पूर्ण

	करो अणु
		err = dpaa2_io_service_enqueue_qd(शून्य,
						  port_priv->tx_qdid,
						  8, 0, &fd);
		retries--;
	पूर्ण जबतक (err == -EBUSY && retries);

	अगर (unlikely(err < 0)) अणु
		dpaa2_चयन_मुक्त_fd(ethsw, &fd);
		जाओ err_निकास;
	पूर्ण

	वापस NETDEV_TX_OK;

err_मुक्त_skb:
	dev_kमुक्त_skb(skb);
err_निकास:
	वापस NETDEV_TX_OK;
पूर्ण

अटल पूर्णांक
dpaa2_चयन_setup_tc_cls_flower(काष्ठा dpaa2_चयन_acl_tbl *acl_tbl,
				 काष्ठा flow_cls_offload *f)
अणु
	चयन (f->command) अणु
	हाल FLOW_CLS_REPLACE:
		वापस dpaa2_चयन_cls_flower_replace(acl_tbl, f);
	हाल FLOW_CLS_DESTROY:
		वापस dpaa2_चयन_cls_flower_destroy(acl_tbl, f);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक
dpaa2_चयन_setup_tc_cls_matchall(काष्ठा dpaa2_चयन_acl_tbl *acl_tbl,
				   काष्ठा tc_cls_matchall_offload *f)
अणु
	चयन (f->command) अणु
	हाल TC_CLSMATCHALL_REPLACE:
		वापस dpaa2_चयन_cls_matchall_replace(acl_tbl, f);
	हाल TC_CLSMATCHALL_DESTROY:
		वापस dpaa2_चयन_cls_matchall_destroy(acl_tbl, f);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक dpaa2_चयन_port_setup_tc_block_cb_ig(क्रमागत tc_setup_type type,
						  व्योम *type_data,
						  व्योम *cb_priv)
अणु
	चयन (type) अणु
	हाल TC_SETUP_CLSFLOWER:
		वापस dpaa2_चयन_setup_tc_cls_flower(cb_priv, type_data);
	हाल TC_SETUP_CLSMATCHALL:
		वापस dpaa2_चयन_setup_tc_cls_matchall(cb_priv, type_data);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल LIST_HEAD(dpaa2_चयन_block_cb_list);

अटल पूर्णांक dpaa2_चयन_port_acl_tbl_bind(काष्ठा ethsw_port_priv *port_priv,
					  काष्ठा dpaa2_चयन_acl_tbl *acl_tbl)
अणु
	काष्ठा ethsw_core *ethsw = port_priv->ethsw_data;
	काष्ठा net_device *netdev = port_priv->netdev;
	काष्ठा dpsw_acl_अगर_cfg acl_अगर_cfg;
	पूर्णांक err;

	अगर (port_priv->acl_tbl)
		वापस -EINVAL;

	acl_अगर_cfg.अगर_id[0] = port_priv->idx;
	acl_अगर_cfg.num_अगरs = 1;
	err = dpsw_acl_add_अगर(ethsw->mc_io, 0, ethsw->dpsw_handle,
			      acl_tbl->id, &acl_अगर_cfg);
	अगर (err) अणु
		netdev_err(netdev, "dpsw_acl_add_if err %d\n", err);
		वापस err;
	पूर्ण

	acl_tbl->ports |= BIT(port_priv->idx);
	port_priv->acl_tbl = acl_tbl;

	वापस 0;
पूर्ण

अटल पूर्णांक
dpaa2_चयन_port_acl_tbl_unbind(काष्ठा ethsw_port_priv *port_priv,
				 काष्ठा dpaa2_चयन_acl_tbl *acl_tbl)
अणु
	काष्ठा ethsw_core *ethsw = port_priv->ethsw_data;
	काष्ठा net_device *netdev = port_priv->netdev;
	काष्ठा dpsw_acl_अगर_cfg acl_अगर_cfg;
	पूर्णांक err;

	अगर (port_priv->acl_tbl != acl_tbl)
		वापस -EINVAL;

	acl_अगर_cfg.अगर_id[0] = port_priv->idx;
	acl_अगर_cfg.num_अगरs = 1;
	err = dpsw_acl_हटाओ_अगर(ethsw->mc_io, 0, ethsw->dpsw_handle,
				 acl_tbl->id, &acl_अगर_cfg);
	अगर (err) अणु
		netdev_err(netdev, "dpsw_acl_add_if err %d\n", err);
		वापस err;
	पूर्ण

	acl_tbl->ports &= ~BIT(port_priv->idx);
	port_priv->acl_tbl = शून्य;
	वापस 0;
पूर्ण

अटल पूर्णांक dpaa2_चयन_port_block_bind(काष्ठा ethsw_port_priv *port_priv,
					काष्ठा dpaa2_चयन_acl_tbl *acl_tbl)
अणु
	काष्ठा dpaa2_चयन_acl_tbl *old_acl_tbl = port_priv->acl_tbl;
	पूर्णांक err;

	/* If the port is alपढ़ोy bound to this ACL table then करो nothing. This
	 * can happen when this port is the first one to join a tc block
	 */
	अगर (port_priv->acl_tbl == acl_tbl)
		वापस 0;

	err = dpaa2_चयन_port_acl_tbl_unbind(port_priv, old_acl_tbl);
	अगर (err)
		वापस err;

	/* Mark the previous ACL table as being unused अगर this was the last
	 * port that was using it.
	 */
	अगर (old_acl_tbl->ports == 0)
		old_acl_tbl->in_use = false;

	वापस dpaa2_चयन_port_acl_tbl_bind(port_priv, acl_tbl);
पूर्ण

अटल पूर्णांक dpaa2_चयन_port_block_unbind(काष्ठा ethsw_port_priv *port_priv,
					  काष्ठा dpaa2_चयन_acl_tbl *acl_tbl)
अणु
	काष्ठा ethsw_core *ethsw = port_priv->ethsw_data;
	काष्ठा dpaa2_चयन_acl_tbl *new_acl_tbl;
	पूर्णांक err;

	/* We are the last port that leaves a block (an ACL table).
	 * We'll जारी to use this table.
	 */
	अगर (acl_tbl->ports == BIT(port_priv->idx))
		वापस 0;

	err = dpaa2_चयन_port_acl_tbl_unbind(port_priv, acl_tbl);
	अगर (err)
		वापस err;

	अगर (acl_tbl->ports == 0)
		acl_tbl->in_use = false;

	new_acl_tbl = dpaa2_चयन_acl_tbl_get_unused(ethsw);
	new_acl_tbl->in_use = true;
	वापस dpaa2_चयन_port_acl_tbl_bind(port_priv, new_acl_tbl);
पूर्ण

अटल पूर्णांक dpaa2_चयन_setup_tc_block_bind(काष्ठा net_device *netdev,
					    काष्ठा flow_block_offload *f)
अणु
	काष्ठा ethsw_port_priv *port_priv = netdev_priv(netdev);
	काष्ठा ethsw_core *ethsw = port_priv->ethsw_data;
	काष्ठा dpaa2_चयन_acl_tbl *acl_tbl;
	काष्ठा flow_block_cb *block_cb;
	bool रेजिस्टर_block = false;
	पूर्णांक err;

	block_cb = flow_block_cb_lookup(f->block,
					dpaa2_चयन_port_setup_tc_block_cb_ig,
					ethsw);

	अगर (!block_cb) अणु
		/* If the ACL table is not alपढ़ोy known, then this port must
		 * be the first to join it. In this हाल, we can just जारी
		 * to use our निजी table
		 */
		acl_tbl = port_priv->acl_tbl;

		block_cb = flow_block_cb_alloc(dpaa2_चयन_port_setup_tc_block_cb_ig,
					       ethsw, acl_tbl, शून्य);
		अगर (IS_ERR(block_cb))
			वापस PTR_ERR(block_cb);

		रेजिस्टर_block = true;
	पूर्ण अन्यथा अणु
		acl_tbl = flow_block_cb_priv(block_cb);
	पूर्ण

	flow_block_cb_incref(block_cb);
	err = dpaa2_चयन_port_block_bind(port_priv, acl_tbl);
	अगर (err)
		जाओ err_block_bind;

	अगर (रेजिस्टर_block) अणु
		flow_block_cb_add(block_cb, f);
		list_add_tail(&block_cb->driver_list,
			      &dpaa2_चयन_block_cb_list);
	पूर्ण

	वापस 0;

err_block_bind:
	अगर (!flow_block_cb_decref(block_cb))
		flow_block_cb_मुक्त(block_cb);
	वापस err;
पूर्ण

अटल व्योम dpaa2_चयन_setup_tc_block_unbind(काष्ठा net_device *netdev,
					       काष्ठा flow_block_offload *f)
अणु
	काष्ठा ethsw_port_priv *port_priv = netdev_priv(netdev);
	काष्ठा ethsw_core *ethsw = port_priv->ethsw_data;
	काष्ठा dpaa2_चयन_acl_tbl *acl_tbl;
	काष्ठा flow_block_cb *block_cb;
	पूर्णांक err;

	block_cb = flow_block_cb_lookup(f->block,
					dpaa2_चयन_port_setup_tc_block_cb_ig,
					ethsw);
	अगर (!block_cb)
		वापस;

	acl_tbl = flow_block_cb_priv(block_cb);
	err = dpaa2_चयन_port_block_unbind(port_priv, acl_tbl);
	अगर (!err && !flow_block_cb_decref(block_cb)) अणु
		flow_block_cb_हटाओ(block_cb, f);
		list_del(&block_cb->driver_list);
	पूर्ण
पूर्ण

अटल पूर्णांक dpaa2_चयन_setup_tc_block(काष्ठा net_device *netdev,
				       काष्ठा flow_block_offload *f)
अणु
	अगर (f->binder_type != FLOW_BLOCK_BINDER_TYPE_CLSACT_INGRESS)
		वापस -EOPNOTSUPP;

	f->driver_block_list = &dpaa2_चयन_block_cb_list;

	चयन (f->command) अणु
	हाल FLOW_BLOCK_BIND:
		वापस dpaa2_चयन_setup_tc_block_bind(netdev, f);
	हाल FLOW_BLOCK_UNBIND:
		dpaa2_चयन_setup_tc_block_unbind(netdev, f);
		वापस 0;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक dpaa2_चयन_port_setup_tc(काष्ठा net_device *netdev,
				      क्रमागत tc_setup_type type,
				      व्योम *type_data)
अणु
	चयन (type) अणु
	हाल TC_SETUP_BLOCK: अणु
		वापस dpaa2_चयन_setup_tc_block(netdev, type_data);
	पूर्ण
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_device_ops dpaa2_चयन_port_ops = अणु
	.nकरो_खोलो		= dpaa2_चयन_port_खोलो,
	.nकरो_stop		= dpaa2_चयन_port_stop,

	.nकरो_set_mac_address	= eth_mac_addr,
	.nकरो_get_stats64	= dpaa2_चयन_port_get_stats,
	.nकरो_change_mtu		= dpaa2_चयन_port_change_mtu,
	.nकरो_has_offload_stats	= dpaa2_चयन_port_has_offload_stats,
	.nकरो_get_offload_stats	= dpaa2_चयन_port_get_offload_stats,
	.nकरो_fdb_dump		= dpaa2_चयन_port_fdb_dump,
	.nकरो_vlan_rx_add_vid	= dpaa2_चयन_port_vlan_add,
	.nकरो_vlan_rx_समाप्त_vid	= dpaa2_चयन_port_vlan_समाप्त,

	.nकरो_start_xmit		= dpaa2_चयन_port_tx,
	.nकरो_get_port_parent_id	= dpaa2_चयन_port_parent_id,
	.nकरो_get_phys_port_name = dpaa2_चयन_port_get_phys_name,
	.nकरो_setup_tc		= dpaa2_चयन_port_setup_tc,
पूर्ण;

bool dpaa2_चयन_port_dev_check(स्थिर काष्ठा net_device *netdev)
अणु
	वापस netdev->netdev_ops == &dpaa2_चयन_port_ops;
पूर्ण

अटल व्योम dpaa2_चयन_links_state_update(काष्ठा ethsw_core *ethsw)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ethsw->sw_attr.num_अगरs; i++) अणु
		dpaa2_चयन_port_carrier_state_sync(ethsw->ports[i]->netdev);
		dpaa2_चयन_port_set_mac_addr(ethsw->ports[i]);
	पूर्ण
पूर्ण

अटल irqवापस_t dpaa2_चयन_irq0_handler_thपढ़ो(पूर्णांक irq_num, व्योम *arg)
अणु
	काष्ठा device *dev = (काष्ठा device *)arg;
	काष्ठा ethsw_core *ethsw = dev_get_drvdata(dev);

	/* Mask the events and the अगर_id reserved bits to be cleared on पढ़ो */
	u32 status = DPSW_IRQ_EVENT_LINK_CHANGED | 0xFFFF0000;
	पूर्णांक err;

	err = dpsw_get_irq_status(ethsw->mc_io, 0, ethsw->dpsw_handle,
				  DPSW_IRQ_INDEX_IF, &status);
	अगर (err) अणु
		dev_err(dev, "Can't get irq status (err %d)\n", err);

		err = dpsw_clear_irq_status(ethsw->mc_io, 0, ethsw->dpsw_handle,
					    DPSW_IRQ_INDEX_IF, 0xFFFFFFFF);
		अगर (err)
			dev_err(dev, "Can't clear irq status (err %d)\n", err);
		जाओ out;
	पूर्ण

	अगर (status & DPSW_IRQ_EVENT_LINK_CHANGED)
		dpaa2_चयन_links_state_update(ethsw);

out:
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक dpaa2_चयन_setup_irqs(काष्ठा fsl_mc_device *sw_dev)
अणु
	काष्ठा device *dev = &sw_dev->dev;
	काष्ठा ethsw_core *ethsw = dev_get_drvdata(dev);
	u32 mask = DPSW_IRQ_EVENT_LINK_CHANGED;
	काष्ठा fsl_mc_device_irq *irq;
	पूर्णांक err;

	err = fsl_mc_allocate_irqs(sw_dev);
	अगर (err) अणु
		dev_err(dev, "MC irqs allocation failed\n");
		वापस err;
	पूर्ण

	अगर (WARN_ON(sw_dev->obj_desc.irq_count != DPSW_IRQ_NUM)) अणु
		err = -EINVAL;
		जाओ मुक्त_irq;
	पूर्ण

	err = dpsw_set_irq_enable(ethsw->mc_io, 0, ethsw->dpsw_handle,
				  DPSW_IRQ_INDEX_IF, 0);
	अगर (err) अणु
		dev_err(dev, "dpsw_set_irq_enable err %d\n", err);
		जाओ मुक्त_irq;
	पूर्ण

	irq = sw_dev->irqs[DPSW_IRQ_INDEX_IF];

	err = devm_request_thपढ़ोed_irq(dev, irq->msi_desc->irq,
					शून्य,
					dpaa2_चयन_irq0_handler_thपढ़ो,
					IRQF_NO_SUSPEND | IRQF_ONESHOT,
					dev_name(dev), dev);
	अगर (err) अणु
		dev_err(dev, "devm_request_threaded_irq(): %d\n", err);
		जाओ मुक्त_irq;
	पूर्ण

	err = dpsw_set_irq_mask(ethsw->mc_io, 0, ethsw->dpsw_handle,
				DPSW_IRQ_INDEX_IF, mask);
	अगर (err) अणु
		dev_err(dev, "dpsw_set_irq_mask(): %d\n", err);
		जाओ मुक्त_devm_irq;
	पूर्ण

	err = dpsw_set_irq_enable(ethsw->mc_io, 0, ethsw->dpsw_handle,
				  DPSW_IRQ_INDEX_IF, 1);
	अगर (err) अणु
		dev_err(dev, "dpsw_set_irq_enable(): %d\n", err);
		जाओ मुक्त_devm_irq;
	पूर्ण

	वापस 0;

मुक्त_devm_irq:
	devm_मुक्त_irq(dev, irq->msi_desc->irq, dev);
मुक्त_irq:
	fsl_mc_मुक्त_irqs(sw_dev);
	वापस err;
पूर्ण

अटल व्योम dpaa2_चयन_tearकरोwn_irqs(काष्ठा fsl_mc_device *sw_dev)
अणु
	काष्ठा device *dev = &sw_dev->dev;
	काष्ठा ethsw_core *ethsw = dev_get_drvdata(dev);
	पूर्णांक err;

	err = dpsw_set_irq_enable(ethsw->mc_io, 0, ethsw->dpsw_handle,
				  DPSW_IRQ_INDEX_IF, 0);
	अगर (err)
		dev_err(dev, "dpsw_set_irq_enable err %d\n", err);

	fsl_mc_मुक्त_irqs(sw_dev);
पूर्ण

अटल पूर्णांक dpaa2_चयन_port_set_learning(काष्ठा ethsw_port_priv *port_priv, bool enable)
अणु
	काष्ठा ethsw_core *ethsw = port_priv->ethsw_data;
	क्रमागत dpsw_learning_mode learn_mode;
	पूर्णांक err;

	अगर (enable)
		learn_mode = DPSW_LEARNING_MODE_HW;
	अन्यथा
		learn_mode = DPSW_LEARNING_MODE_DIS;

	err = dpsw_अगर_set_learning_mode(ethsw->mc_io, 0, ethsw->dpsw_handle,
					port_priv->idx, learn_mode);
	अगर (err)
		netdev_err(port_priv->netdev, "dpsw_if_set_learning_mode err %d\n", err);

	अगर (!enable)
		dpaa2_चयन_port_fast_age(port_priv);

	वापस err;
पूर्ण

अटल पूर्णांक dpaa2_चयन_port_attr_stp_state_set(काष्ठा net_device *netdev,
						u8 state)
अणु
	काष्ठा ethsw_port_priv *port_priv = netdev_priv(netdev);
	पूर्णांक err;

	err = dpaa2_चयन_port_set_stp_state(port_priv, state);
	अगर (err)
		वापस err;

	चयन (state) अणु
	हाल BR_STATE_DISABLED:
	हाल BR_STATE_BLOCKING:
	हाल BR_STATE_LISTENING:
		err = dpaa2_चयन_port_set_learning(port_priv, false);
		अवरोध;
	हाल BR_STATE_LEARNING:
	हाल BR_STATE_FORWARDING:
		err = dpaa2_चयन_port_set_learning(port_priv,
						     port_priv->learn_ena);
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक dpaa2_चयन_port_flood(काष्ठा ethsw_port_priv *port_priv,
				   काष्ठा चयनdev_brport_flags flags)
अणु
	काष्ठा ethsw_core *ethsw = port_priv->ethsw_data;

	अगर (flags.mask & BR_BCAST_FLOOD)
		port_priv->bcast_flood = !!(flags.val & BR_BCAST_FLOOD);

	अगर (flags.mask & BR_FLOOD)
		port_priv->ucast_flood = !!(flags.val & BR_FLOOD);

	वापस dpaa2_चयन_fdb_set_egress_flood(ethsw, port_priv->fdb->fdb_id);
पूर्ण

अटल पूर्णांक dpaa2_चयन_port_pre_bridge_flags(काष्ठा net_device *netdev,
					      काष्ठा चयनdev_brport_flags flags,
					      काष्ठा netlink_ext_ack *extack)
अणु
	अगर (flags.mask & ~(BR_LEARNING | BR_BCAST_FLOOD | BR_FLOOD |
			   BR_MCAST_FLOOD))
		वापस -EINVAL;

	अगर (flags.mask & (BR_FLOOD | BR_MCAST_FLOOD)) अणु
		bool multicast = !!(flags.val & BR_MCAST_FLOOD);
		bool unicast = !!(flags.val & BR_FLOOD);

		अगर (unicast != multicast) अणु
			NL_SET_ERR_MSG_MOD(extack,
					   "Cannot configure multicast flooding independently of unicast");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dpaa2_चयन_port_bridge_flags(काष्ठा net_device *netdev,
					  काष्ठा चयनdev_brport_flags flags,
					  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा ethsw_port_priv *port_priv = netdev_priv(netdev);
	पूर्णांक err;

	अगर (flags.mask & BR_LEARNING) अणु
		bool learn_ena = !!(flags.val & BR_LEARNING);

		err = dpaa2_चयन_port_set_learning(port_priv, learn_ena);
		अगर (err)
			वापस err;
		port_priv->learn_ena = learn_ena;
	पूर्ण

	अगर (flags.mask & (BR_BCAST_FLOOD | BR_FLOOD | BR_MCAST_FLOOD)) अणु
		err = dpaa2_चयन_port_flood(port_priv, flags);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dpaa2_चयन_port_attr_set(काष्ठा net_device *netdev,
				      स्थिर काष्ठा चयनdev_attr *attr,
				      काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक err = 0;

	चयन (attr->id) अणु
	हाल SWITCHDEV_ATTR_ID_PORT_STP_STATE:
		err = dpaa2_चयन_port_attr_stp_state_set(netdev,
							   attr->u.stp_state);
		अवरोध;
	हाल SWITCHDEV_ATTR_ID_BRIDGE_VLAN_FILTERING:
		अगर (!attr->u.vlan_filtering) अणु
			NL_SET_ERR_MSG_MOD(extack,
					   "The DPAA2 switch does not support VLAN-unaware operation");
			वापस -EOPNOTSUPP;
		पूर्ण
		अवरोध;
	हाल SWITCHDEV_ATTR_ID_PORT_PRE_BRIDGE_FLAGS:
		err = dpaa2_चयन_port_pre_bridge_flags(netdev, attr->u.brport_flags, extack);
		अवरोध;
	हाल SWITCHDEV_ATTR_ID_PORT_BRIDGE_FLAGS:
		err = dpaa2_चयन_port_bridge_flags(netdev, attr->u.brport_flags, extack);
		अवरोध;
	शेष:
		err = -EOPNOTSUPP;
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

पूर्णांक dpaa2_चयन_port_vlans_add(काष्ठा net_device *netdev,
				स्थिर काष्ठा चयनdev_obj_port_vlan *vlan)
अणु
	काष्ठा ethsw_port_priv *port_priv = netdev_priv(netdev);
	काष्ठा ethsw_core *ethsw = port_priv->ethsw_data;
	काष्ठा dpsw_attr *attr = &ethsw->sw_attr;
	पूर्णांक err = 0;

	/* Make sure that the VLAN is not alपढ़ोy configured
	 * on the चयन port
	 */
	अगर (port_priv->vlans[vlan->vid] & ETHSW_VLAN_MEMBER)
		वापस -EEXIST;

	/* Check अगर there is space क्रम a new VLAN */
	err = dpsw_get_attributes(ethsw->mc_io, 0, ethsw->dpsw_handle,
				  &ethsw->sw_attr);
	अगर (err) अणु
		netdev_err(netdev, "dpsw_get_attributes err %d\n", err);
		वापस err;
	पूर्ण
	अगर (attr->max_vlans - attr->num_vlans < 1)
		वापस -ENOSPC;

	/* Check अगर there is space क्रम a new VLAN */
	err = dpsw_get_attributes(ethsw->mc_io, 0, ethsw->dpsw_handle,
				  &ethsw->sw_attr);
	अगर (err) अणु
		netdev_err(netdev, "dpsw_get_attributes err %d\n", err);
		वापस err;
	पूर्ण
	अगर (attr->max_vlans - attr->num_vlans < 1)
		वापस -ENOSPC;

	अगर (!port_priv->ethsw_data->vlans[vlan->vid]) अणु
		/* this is a new VLAN */
		err = dpaa2_चयन_add_vlan(port_priv, vlan->vid);
		अगर (err)
			वापस err;

		port_priv->ethsw_data->vlans[vlan->vid] |= ETHSW_VLAN_GLOBAL;
	पूर्ण

	वापस dpaa2_चयन_port_add_vlan(port_priv, vlan->vid, vlan->flags);
पूर्ण

अटल पूर्णांक dpaa2_चयन_port_lookup_address(काष्ठा net_device *netdev, पूर्णांक is_uc,
					    स्थिर अचिन्हित अक्षर *addr)
अणु
	काष्ठा netdev_hw_addr_list *list = (is_uc) ? &netdev->uc : &netdev->mc;
	काष्ठा netdev_hw_addr *ha;

	netअगर_addr_lock_bh(netdev);
	list_क्रम_each_entry(ha, &list->list, list) अणु
		अगर (ether_addr_equal(ha->addr, addr)) अणु
			netअगर_addr_unlock_bh(netdev);
			वापस 1;
		पूर्ण
	पूर्ण
	netअगर_addr_unlock_bh(netdev);
	वापस 0;
पूर्ण

अटल पूर्णांक dpaa2_चयन_port_mdb_add(काष्ठा net_device *netdev,
				     स्थिर काष्ठा चयनdev_obj_port_mdb *mdb)
अणु
	काष्ठा ethsw_port_priv *port_priv = netdev_priv(netdev);
	पूर्णांक err;

	/* Check अगर address is alपढ़ोy set on this port */
	अगर (dpaa2_चयन_port_lookup_address(netdev, 0, mdb->addr))
		वापस -EEXIST;

	err = dpaa2_चयन_port_fdb_add_mc(port_priv, mdb->addr);
	अगर (err)
		वापस err;

	err = dev_mc_add(netdev, mdb->addr);
	अगर (err) अणु
		netdev_err(netdev, "dev_mc_add err %d\n", err);
		dpaa2_चयन_port_fdb_del_mc(port_priv, mdb->addr);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक dpaa2_चयन_port_obj_add(काष्ठा net_device *netdev,
				     स्थिर काष्ठा चयनdev_obj *obj)
अणु
	पूर्णांक err;

	चयन (obj->id) अणु
	हाल SWITCHDEV_OBJ_ID_PORT_VLAN:
		err = dpaa2_चयन_port_vlans_add(netdev,
						  SWITCHDEV_OBJ_PORT_VLAN(obj));
		अवरोध;
	हाल SWITCHDEV_OBJ_ID_PORT_MDB:
		err = dpaa2_चयन_port_mdb_add(netdev,
						SWITCHDEV_OBJ_PORT_MDB(obj));
		अवरोध;
	शेष:
		err = -EOPNOTSUPP;
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक dpaa2_चयन_port_del_vlan(काष्ठा ethsw_port_priv *port_priv, u16 vid)
अणु
	काष्ठा ethsw_core *ethsw = port_priv->ethsw_data;
	काष्ठा net_device *netdev = port_priv->netdev;
	काष्ठा dpsw_vlan_अगर_cfg vcfg;
	पूर्णांक i, err;

	अगर (!port_priv->vlans[vid])
		वापस -ENOENT;

	अगर (port_priv->vlans[vid] & ETHSW_VLAN_PVID) अणु
		/* If we are deleting the PVID of a port, use VLAN 4095 instead
		 * as we are sure that neither the bridge nor the 8021q module
		 * will use it
		 */
		err = dpaa2_चयन_port_set_pvid(port_priv, 4095);
		अगर (err)
			वापस err;
	पूर्ण

	vcfg.num_अगरs = 1;
	vcfg.अगर_id[0] = port_priv->idx;
	अगर (port_priv->vlans[vid] & ETHSW_VLAN_UNTAGGED) अणु
		err = dpsw_vlan_हटाओ_अगर_untagged(ethsw->mc_io, 0,
						   ethsw->dpsw_handle,
						   vid, &vcfg);
		अगर (err) अणु
			netdev_err(netdev,
				   "dpsw_vlan_remove_if_untagged err %d\n",
				   err);
		पूर्ण
		port_priv->vlans[vid] &= ~ETHSW_VLAN_UNTAGGED;
	पूर्ण

	अगर (port_priv->vlans[vid] & ETHSW_VLAN_MEMBER) अणु
		err = dpsw_vlan_हटाओ_अगर(ethsw->mc_io, 0, ethsw->dpsw_handle,
					  vid, &vcfg);
		अगर (err) अणु
			netdev_err(netdev,
				   "dpsw_vlan_remove_if err %d\n", err);
			वापस err;
		पूर्ण
		port_priv->vlans[vid] &= ~ETHSW_VLAN_MEMBER;

		/* Delete VLAN from चयन अगर it is no दीर्घer configured on
		 * any port
		 */
		क्रम (i = 0; i < ethsw->sw_attr.num_अगरs; i++)
			अगर (ethsw->ports[i]->vlans[vid] & ETHSW_VLAN_MEMBER)
				वापस 0; /* Found a port member in VID */

		ethsw->vlans[vid] &= ~ETHSW_VLAN_GLOBAL;

		err = dpaa2_चयन_dellink(ethsw, vid);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक dpaa2_चयन_port_vlans_del(काष्ठा net_device *netdev,
				स्थिर काष्ठा चयनdev_obj_port_vlan *vlan)
अणु
	काष्ठा ethsw_port_priv *port_priv = netdev_priv(netdev);

	अगर (netअगर_is_bridge_master(vlan->obj.orig_dev))
		वापस -EOPNOTSUPP;

	वापस dpaa2_चयन_port_del_vlan(port_priv, vlan->vid);
पूर्ण

अटल पूर्णांक dpaa2_चयन_port_mdb_del(काष्ठा net_device *netdev,
				     स्थिर काष्ठा चयनdev_obj_port_mdb *mdb)
अणु
	काष्ठा ethsw_port_priv *port_priv = netdev_priv(netdev);
	पूर्णांक err;

	अगर (!dpaa2_चयन_port_lookup_address(netdev, 0, mdb->addr))
		वापस -ENOENT;

	err = dpaa2_चयन_port_fdb_del_mc(port_priv, mdb->addr);
	अगर (err)
		वापस err;

	err = dev_mc_del(netdev, mdb->addr);
	अगर (err) अणु
		netdev_err(netdev, "dev_mc_del err %d\n", err);
		वापस err;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक dpaa2_चयन_port_obj_del(काष्ठा net_device *netdev,
				     स्थिर काष्ठा चयनdev_obj *obj)
अणु
	पूर्णांक err;

	चयन (obj->id) अणु
	हाल SWITCHDEV_OBJ_ID_PORT_VLAN:
		err = dpaa2_चयन_port_vlans_del(netdev, SWITCHDEV_OBJ_PORT_VLAN(obj));
		अवरोध;
	हाल SWITCHDEV_OBJ_ID_PORT_MDB:
		err = dpaa2_चयन_port_mdb_del(netdev, SWITCHDEV_OBJ_PORT_MDB(obj));
		अवरोध;
	शेष:
		err = -EOPNOTSUPP;
		अवरोध;
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक dpaa2_चयन_port_attr_set_event(काष्ठा net_device *netdev,
					    काष्ठा चयनdev_notअगरier_port_attr_info *ptr)
अणु
	पूर्णांक err;

	err = चयनdev_handle_port_attr_set(netdev, ptr,
					     dpaa2_चयन_port_dev_check,
					     dpaa2_चयन_port_attr_set);
	वापस notअगरier_from_त्रुटि_सं(err);
पूर्ण

अटल पूर्णांक dpaa2_चयन_port_bridge_join(काष्ठा net_device *netdev,
					 काष्ठा net_device *upper_dev)
अणु
	काष्ठा ethsw_port_priv *port_priv = netdev_priv(netdev);
	काष्ठा ethsw_core *ethsw = port_priv->ethsw_data;
	काष्ठा ethsw_port_priv *other_port_priv;
	काष्ठा net_device *other_dev;
	काष्ठा list_head *iter;
	bool learn_ena;
	पूर्णांक err;

	netdev_क्रम_each_lower_dev(upper_dev, other_dev, iter) अणु
		अगर (!dpaa2_चयन_port_dev_check(other_dev))
			जारी;

		other_port_priv = netdev_priv(other_dev);
		अगर (other_port_priv->ethsw_data != port_priv->ethsw_data) अणु
			netdev_err(netdev,
				   "Interface from a different DPSW is in the bridge already!\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* Delete the previously manually installed VLAN 1 */
	err = dpaa2_चयन_port_del_vlan(port_priv, 1);
	अगर (err)
		वापस err;

	dpaa2_चयन_port_set_fdb(port_priv, upper_dev);

	/* Inherit the initial bridge port learning state */
	learn_ena = br_port_flag_is_set(netdev, BR_LEARNING);
	err = dpaa2_चयन_port_set_learning(port_priv, learn_ena);
	port_priv->learn_ena = learn_ena;

	/* Setup the egress flood policy (broadcast, unknown unicast) */
	err = dpaa2_चयन_fdb_set_egress_flood(ethsw, port_priv->fdb->fdb_id);
	अगर (err)
		जाओ err_egress_flood;

	वापस 0;

err_egress_flood:
	dpaa2_चयन_port_set_fdb(port_priv, शून्य);
	वापस err;
पूर्ण

अटल पूर्णांक dpaa2_चयन_port_clear_rxvlan(काष्ठा net_device *vdev, पूर्णांक vid, व्योम *arg)
अणु
	__be16 vlan_proto = htons(ETH_P_8021Q);

	अगर (vdev)
		vlan_proto = vlan_dev_vlan_proto(vdev);

	वापस dpaa2_चयन_port_vlan_समाप्त(arg, vlan_proto, vid);
पूर्ण

अटल पूर्णांक dpaa2_चयन_port_restore_rxvlan(काष्ठा net_device *vdev, पूर्णांक vid, व्योम *arg)
अणु
	__be16 vlan_proto = htons(ETH_P_8021Q);

	अगर (vdev)
		vlan_proto = vlan_dev_vlan_proto(vdev);

	वापस dpaa2_चयन_port_vlan_add(arg, vlan_proto, vid);
पूर्ण

अटल पूर्णांक dpaa2_चयन_port_bridge_leave(काष्ठा net_device *netdev)
अणु
	काष्ठा ethsw_port_priv *port_priv = netdev_priv(netdev);
	काष्ठा dpaa2_चयन_fdb *old_fdb = port_priv->fdb;
	काष्ठा ethsw_core *ethsw = port_priv->ethsw_data;
	पूर्णांक err;

	/* First of all, fast age any learn FDB addresses on this चयन port */
	dpaa2_चयन_port_fast_age(port_priv);

	/* Clear all RX VLANs installed through vlan_vid_add() either as VLAN
	 * upper devices or otherwise from the FDB table that we are about to
	 * leave
	 */
	err = vlan_क्रम_each(netdev, dpaa2_चयन_port_clear_rxvlan, netdev);
	अगर (err)
		netdev_err(netdev, "Unable to clear RX VLANs from old FDB table, err (%d)\n", err);

	dpaa2_चयन_port_set_fdb(port_priv, शून्य);

	/* Restore all RX VLANs पूर्णांकo the new FDB table that we just joined */
	err = vlan_क्रम_each(netdev, dpaa2_चयन_port_restore_rxvlan, netdev);
	अगर (err)
		netdev_err(netdev, "Unable to restore RX VLANs to the new FDB, err (%d)\n", err);

	/* Reset the flooding state to denote that this port can send any
	 * packet in standalone mode. With this, we are also ensuring that any
	 * later bridge join will have the flooding flag on.
	 */
	port_priv->bcast_flood = true;
	port_priv->ucast_flood = true;

	/* Setup the egress flood policy (broadcast, unknown unicast).
	 * When the port is not under a bridge, only the CTRL पूर्णांकerface is part
	 * of the flooding करोमुख्य besides the actual port
	 */
	err = dpaa2_चयन_fdb_set_egress_flood(ethsw, port_priv->fdb->fdb_id);
	अगर (err)
		वापस err;

	/* Recreate the egress flood करोमुख्य of the FDB that we just left */
	err = dpaa2_चयन_fdb_set_egress_flood(ethsw, old_fdb->fdb_id);
	अगर (err)
		वापस err;

	/* No HW learning when not under a bridge */
	err = dpaa2_चयन_port_set_learning(port_priv, false);
	अगर (err)
		वापस err;
	port_priv->learn_ena = false;

	/* Add the VLAN 1 as PVID when not under a bridge. We need this since
	 * the dpaa2 चयन पूर्णांकerfaces are not capable to be VLAN unaware
	 */
	वापस dpaa2_चयन_port_add_vlan(port_priv, DEFAULT_VLAN_ID,
					  BRIDGE_VLAN_INFO_UNTAGGED | BRIDGE_VLAN_INFO_PVID);
पूर्ण

अटल पूर्णांक dpaa2_चयन_prevent_bridging_with_8021q_upper(काष्ठा net_device *netdev)
अणु
	काष्ठा net_device *upper_dev;
	काष्ठा list_head *iter;

	/* RCU पढ़ो lock not necessary because we have ग_लिखो-side protection
	 * (rtnl_mutex), however a non-rcu iterator करोes not exist.
	 */
	netdev_क्रम_each_upper_dev_rcu(netdev, upper_dev, iter)
		अगर (is_vlan_dev(upper_dev))
			वापस -EOPNOTSUPP;

	वापस 0;
पूर्ण

अटल पूर्णांक dpaa2_चयन_port_netdevice_event(काष्ठा notअगरier_block *nb,
					     अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *netdev = netdev_notअगरier_info_to_dev(ptr);
	काष्ठा netdev_notअगरier_changeupper_info *info = ptr;
	काष्ठा netlink_ext_ack *extack;
	काष्ठा net_device *upper_dev;
	पूर्णांक err = 0;

	अगर (!dpaa2_चयन_port_dev_check(netdev))
		वापस NOTIFY_DONE;

	extack = netdev_notअगरier_info_to_extack(&info->info);

	चयन (event) अणु
	हाल NETDEV_PRECHANGEUPPER:
		upper_dev = info->upper_dev;
		अगर (!netअगर_is_bridge_master(upper_dev))
			अवरोध;

		अगर (!br_vlan_enabled(upper_dev)) अणु
			NL_SET_ERR_MSG_MOD(extack, "Cannot join a VLAN-unaware bridge");
			err = -EOPNOTSUPP;
			जाओ out;
		पूर्ण

		err = dpaa2_चयन_prevent_bridging_with_8021q_upper(netdev);
		अगर (err) अणु
			NL_SET_ERR_MSG_MOD(extack,
					   "Cannot join a bridge while VLAN uppers are present");
			जाओ out;
		पूर्ण

		अवरोध;
	हाल NETDEV_CHANGEUPPER:
		upper_dev = info->upper_dev;
		अगर (netअगर_is_bridge_master(upper_dev)) अणु
			अगर (info->linking)
				err = dpaa2_चयन_port_bridge_join(netdev, upper_dev);
			अन्यथा
				err = dpaa2_चयन_port_bridge_leave(netdev);
		पूर्ण
		अवरोध;
	पूर्ण

out:
	वापस notअगरier_from_त्रुटि_सं(err);
पूर्ण

काष्ठा ethsw_चयनdev_event_work अणु
	काष्ठा work_काष्ठा work;
	काष्ठा चयनdev_notअगरier_fdb_info fdb_info;
	काष्ठा net_device *dev;
	अचिन्हित दीर्घ event;
पूर्ण;

अटल व्योम dpaa2_चयन_event_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ethsw_चयनdev_event_work *चयनdev_work =
		container_of(work, काष्ठा ethsw_चयनdev_event_work, work);
	काष्ठा net_device *dev = चयनdev_work->dev;
	काष्ठा चयनdev_notअगरier_fdb_info *fdb_info;
	पूर्णांक err;

	rtnl_lock();
	fdb_info = &चयनdev_work->fdb_info;

	चयन (चयनdev_work->event) अणु
	हाल SWITCHDEV_FDB_ADD_TO_DEVICE:
		अगर (!fdb_info->added_by_user || fdb_info->is_local)
			अवरोध;
		अगर (is_unicast_ether_addr(fdb_info->addr))
			err = dpaa2_चयन_port_fdb_add_uc(netdev_priv(dev),
							   fdb_info->addr);
		अन्यथा
			err = dpaa2_चयन_port_fdb_add_mc(netdev_priv(dev),
							   fdb_info->addr);
		अगर (err)
			अवरोध;
		fdb_info->offloaded = true;
		call_चयनdev_notअगरiers(SWITCHDEV_FDB_OFFLOADED, dev,
					 &fdb_info->info, शून्य);
		अवरोध;
	हाल SWITCHDEV_FDB_DEL_TO_DEVICE:
		अगर (!fdb_info->added_by_user || fdb_info->is_local)
			अवरोध;
		अगर (is_unicast_ether_addr(fdb_info->addr))
			dpaa2_चयन_port_fdb_del_uc(netdev_priv(dev), fdb_info->addr);
		अन्यथा
			dpaa2_चयन_port_fdb_del_mc(netdev_priv(dev), fdb_info->addr);
		अवरोध;
	पूर्ण

	rtnl_unlock();
	kमुक्त(चयनdev_work->fdb_info.addr);
	kमुक्त(चयनdev_work);
	dev_put(dev);
पूर्ण

/* Called under rcu_पढ़ो_lock() */
अटल पूर्णांक dpaa2_चयन_port_event(काष्ठा notअगरier_block *nb,
				   अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *dev = चयनdev_notअगरier_info_to_dev(ptr);
	काष्ठा ethsw_port_priv *port_priv = netdev_priv(dev);
	काष्ठा ethsw_चयनdev_event_work *चयनdev_work;
	काष्ठा चयनdev_notअगरier_fdb_info *fdb_info = ptr;
	काष्ठा ethsw_core *ethsw = port_priv->ethsw_data;

	अगर (event == SWITCHDEV_PORT_ATTR_SET)
		वापस dpaa2_चयन_port_attr_set_event(dev, ptr);

	अगर (!dpaa2_चयन_port_dev_check(dev))
		वापस NOTIFY_DONE;

	चयनdev_work = kzalloc(माप(*चयनdev_work), GFP_ATOMIC);
	अगर (!चयनdev_work)
		वापस NOTIFY_BAD;

	INIT_WORK(&चयनdev_work->work, dpaa2_चयन_event_work);
	चयनdev_work->dev = dev;
	चयनdev_work->event = event;

	चयन (event) अणु
	हाल SWITCHDEV_FDB_ADD_TO_DEVICE:
	हाल SWITCHDEV_FDB_DEL_TO_DEVICE:
		स_नकल(&चयनdev_work->fdb_info, ptr,
		       माप(चयनdev_work->fdb_info));
		चयनdev_work->fdb_info.addr = kzalloc(ETH_ALEN, GFP_ATOMIC);
		अगर (!चयनdev_work->fdb_info.addr)
			जाओ err_addr_alloc;

		ether_addr_copy((u8 *)चयनdev_work->fdb_info.addr,
				fdb_info->addr);

		/* Take a reference on the device to aव्योम being मुक्तd. */
		dev_hold(dev);
		अवरोध;
	शेष:
		kमुक्त(चयनdev_work);
		वापस NOTIFY_DONE;
	पूर्ण

	queue_work(ethsw->workqueue, &चयनdev_work->work);

	वापस NOTIFY_DONE;

err_addr_alloc:
	kमुक्त(चयनdev_work);
	वापस NOTIFY_BAD;
पूर्ण

अटल पूर्णांक dpaa2_चयन_port_obj_event(अचिन्हित दीर्घ event,
				       काष्ठा net_device *netdev,
				       काष्ठा चयनdev_notअगरier_port_obj_info *port_obj_info)
अणु
	पूर्णांक err = -EOPNOTSUPP;

	अगर (!dpaa2_चयन_port_dev_check(netdev))
		वापस NOTIFY_DONE;

	चयन (event) अणु
	हाल SWITCHDEV_PORT_OBJ_ADD:
		err = dpaa2_चयन_port_obj_add(netdev, port_obj_info->obj);
		अवरोध;
	हाल SWITCHDEV_PORT_OBJ_DEL:
		err = dpaa2_चयन_port_obj_del(netdev, port_obj_info->obj);
		अवरोध;
	पूर्ण

	port_obj_info->handled = true;
	वापस notअगरier_from_त्रुटि_सं(err);
पूर्ण

अटल पूर्णांक dpaa2_चयन_port_blocking_event(काष्ठा notअगरier_block *nb,
					    अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *dev = चयनdev_notअगरier_info_to_dev(ptr);

	चयन (event) अणु
	हाल SWITCHDEV_PORT_OBJ_ADD:
	हाल SWITCHDEV_PORT_OBJ_DEL:
		वापस dpaa2_चयन_port_obj_event(event, dev, ptr);
	हाल SWITCHDEV_PORT_ATTR_SET:
		वापस dpaa2_चयन_port_attr_set_event(dev, ptr);
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

/* Build a linear skb based on a single-buffer frame descriptor */
अटल काष्ठा sk_buff *dpaa2_चयन_build_linear_skb(काष्ठा ethsw_core *ethsw,
						     स्थिर काष्ठा dpaa2_fd *fd)
अणु
	u16 fd_offset = dpaa2_fd_get_offset(fd);
	dma_addr_t addr = dpaa2_fd_get_addr(fd);
	u32 fd_length = dpaa2_fd_get_len(fd);
	काष्ठा device *dev = ethsw->dev;
	काष्ठा sk_buff *skb = शून्य;
	व्योम *fd_vaddr;

	fd_vaddr = dpaa2_iova_to_virt(ethsw->iommu_करोमुख्य, addr);
	dma_unmap_page(dev, addr, DPAA2_SWITCH_RX_BUF_SIZE,
		       DMA_FROM_DEVICE);

	skb = build_skb(fd_vaddr, DPAA2_SWITCH_RX_BUF_SIZE +
			SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info)));
	अगर (unlikely(!skb)) अणु
		dev_err(dev, "build_skb() failed\n");
		वापस शून्य;
	पूर्ण

	skb_reserve(skb, fd_offset);
	skb_put(skb, fd_length);

	ethsw->buf_count--;

	वापस skb;
पूर्ण

अटल व्योम dpaa2_चयन_tx_conf(काष्ठा dpaa2_चयन_fq *fq,
				 स्थिर काष्ठा dpaa2_fd *fd)
अणु
	dpaa2_चयन_मुक्त_fd(fq->ethsw, fd);
पूर्ण

अटल व्योम dpaa2_चयन_rx(काष्ठा dpaa2_चयन_fq *fq,
			    स्थिर काष्ठा dpaa2_fd *fd)
अणु
	काष्ठा ethsw_core *ethsw = fq->ethsw;
	काष्ठा ethsw_port_priv *port_priv;
	काष्ठा net_device *netdev;
	काष्ठा vlan_ethhdr *hdr;
	काष्ठा sk_buff *skb;
	u16 vlan_tci, vid;
	पूर्णांक अगर_id, err;

	/* get चयन ingress पूर्णांकerface ID */
	अगर_id = upper_32_bits(dpaa2_fd_get_flc(fd)) & 0x0000FFFF;

	अगर (अगर_id >= ethsw->sw_attr.num_अगरs) अणु
		dev_err(ethsw->dev, "Frame received from unknown interface!\n");
		जाओ err_मुक्त_fd;
	पूर्ण
	port_priv = ethsw->ports[अगर_id];
	netdev = port_priv->netdev;

	/* build the SKB based on the FD received */
	अगर (dpaa2_fd_get_क्रमmat(fd) != dpaa2_fd_single) अणु
		अगर (net_ratelimit()) अणु
			netdev_err(netdev, "Received invalid frame format\n");
			जाओ err_मुक्त_fd;
		पूर्ण
	पूर्ण

	skb = dpaa2_चयन_build_linear_skb(ethsw, fd);
	अगर (unlikely(!skb))
		जाओ err_मुक्त_fd;

	skb_reset_mac_header(skb);

	/* Remove the VLAN header अगर the packet that we just received has a vid
	 * equal to the port PVIDs. Since the dpaa2-चयन can operate only in
	 * VLAN-aware mode and no alterations are made on the packet when it's
	 * redirected/mirrored to the control पूर्णांकerface, we are sure that there
	 * will always be a VLAN header present.
	 */
	hdr = vlan_eth_hdr(skb);
	vid = ntohs(hdr->h_vlan_TCI) & VLAN_VID_MASK;
	अगर (vid == port_priv->pvid) अणु
		err = __skb_vlan_pop(skb, &vlan_tci);
		अगर (err) अणु
			dev_info(ethsw->dev, "__skb_vlan_pop() returned %d", err);
			जाओ err_मुक्त_fd;
		पूर्ण
	पूर्ण

	skb->dev = netdev;
	skb->protocol = eth_type_trans(skb, skb->dev);

	/* Setup the offload_fwd_mark only अगर the port is under a bridge */
	skb->offload_fwd_mark = !!(port_priv->fdb->bridge_dev);

	netअगर_receive_skb(skb);

	वापस;

err_मुक्त_fd:
	dpaa2_चयन_मुक्त_fd(ethsw, fd);
पूर्ण

अटल व्योम dpaa2_चयन_detect_features(काष्ठा ethsw_core *ethsw)
अणु
	ethsw->features = 0;

	अगर (ethsw->major > 8 || (ethsw->major == 8 && ethsw->minor >= 6))
		ethsw->features |= ETHSW_FEATURE_MAC_ADDR;
पूर्ण

अटल पूर्णांक dpaa2_चयन_setup_fqs(काष्ठा ethsw_core *ethsw)
अणु
	काष्ठा dpsw_ctrl_अगर_attr ctrl_अगर_attr;
	काष्ठा device *dev = ethsw->dev;
	पूर्णांक i = 0;
	पूर्णांक err;

	err = dpsw_ctrl_अगर_get_attributes(ethsw->mc_io, 0, ethsw->dpsw_handle,
					  &ctrl_अगर_attr);
	अगर (err) अणु
		dev_err(dev, "dpsw_ctrl_if_get_attributes() = %d\n", err);
		वापस err;
	पूर्ण

	ethsw->fq[i].fqid = ctrl_अगर_attr.rx_fqid;
	ethsw->fq[i].ethsw = ethsw;
	ethsw->fq[i++].type = DPSW_QUEUE_RX;

	ethsw->fq[i].fqid = ctrl_अगर_attr.tx_err_conf_fqid;
	ethsw->fq[i].ethsw = ethsw;
	ethsw->fq[i++].type = DPSW_QUEUE_TX_ERR_CONF;

	वापस 0;
पूर्ण

/* Free buffers acquired from the buffer pool or which were meant to
 * be released in the pool
 */
अटल व्योम dpaa2_चयन_मुक्त_bufs(काष्ठा ethsw_core *ethsw, u64 *buf_array, पूर्णांक count)
अणु
	काष्ठा device *dev = ethsw->dev;
	व्योम *vaddr;
	पूर्णांक i;

	क्रम (i = 0; i < count; i++) अणु
		vaddr = dpaa2_iova_to_virt(ethsw->iommu_करोमुख्य, buf_array[i]);
		dma_unmap_page(dev, buf_array[i], DPAA2_SWITCH_RX_BUF_SIZE,
			       DMA_FROM_DEVICE);
		मुक्त_pages((अचिन्हित दीर्घ)vaddr, 0);
	पूर्ण
पूर्ण

/* Perक्रमm a single release command to add buffers
 * to the specअगरied buffer pool
 */
अटल पूर्णांक dpaa2_चयन_add_bufs(काष्ठा ethsw_core *ethsw, u16 bpid)
अणु
	काष्ठा device *dev = ethsw->dev;
	u64 buf_array[BUFS_PER_CMD];
	काष्ठा page *page;
	पूर्णांक retries = 0;
	dma_addr_t addr;
	पूर्णांक err;
	पूर्णांक i;

	क्रम (i = 0; i < BUFS_PER_CMD; i++) अणु
		/* Allocate one page क्रम each Rx buffer. WRIOP sees
		 * the entire page except क्रम a tailroom reserved क्रम
		 * skb shared info
		 */
		page = dev_alloc_pages(0);
		अगर (!page) अणु
			dev_err(dev, "buffer allocation failed\n");
			जाओ err_alloc;
		पूर्ण

		addr = dma_map_page(dev, page, 0, DPAA2_SWITCH_RX_BUF_SIZE,
				    DMA_FROM_DEVICE);
		अगर (dma_mapping_error(dev, addr)) अणु
			dev_err(dev, "dma_map_single() failed\n");
			जाओ err_map;
		पूर्ण
		buf_array[i] = addr;
	पूर्ण

release_bufs:
	/* In हाल the portal is busy, retry until successful or
	 * max retries hit.
	 */
	जबतक ((err = dpaa2_io_service_release(शून्य, bpid,
					       buf_array, i)) == -EBUSY) अणु
		अगर (retries++ >= DPAA2_SWITCH_SWP_BUSY_RETRIES)
			अवरोध;

		cpu_relax();
	पूर्ण

	/* If release command failed, clean up and bail out. */
	अगर (err) अणु
		dpaa2_चयन_मुक्त_bufs(ethsw, buf_array, i);
		वापस 0;
	पूर्ण

	वापस i;

err_map:
	__मुक्त_pages(page, 0);
err_alloc:
	/* If we managed to allocate at least some buffers,
	 * release them to hardware
	 */
	अगर (i)
		जाओ release_bufs;

	वापस 0;
पूर्ण

अटल पूर्णांक dpaa2_चयन_refill_bp(काष्ठा ethsw_core *ethsw)
अणु
	पूर्णांक *count = &ethsw->buf_count;
	पूर्णांक new_count;
	पूर्णांक err = 0;

	अगर (unlikely(*count < DPAA2_ETHSW_REFILL_THRESH)) अणु
		करो अणु
			new_count = dpaa2_चयन_add_bufs(ethsw, ethsw->bpid);
			अगर (unlikely(!new_count)) अणु
				/* Out of memory; पात क्रम now, we'll
				 * try later on
				 */
				अवरोध;
			पूर्ण
			*count += new_count;
		पूर्ण जबतक (*count < DPAA2_ETHSW_NUM_BUFS);

		अगर (unlikely(*count < DPAA2_ETHSW_NUM_BUFS))
			err = -ENOMEM;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक dpaa2_चयन_seed_bp(काष्ठा ethsw_core *ethsw)
अणु
	पूर्णांक *count, i;

	क्रम (i = 0; i < DPAA2_ETHSW_NUM_BUFS; i += BUFS_PER_CMD) अणु
		count = &ethsw->buf_count;
		*count += dpaa2_चयन_add_bufs(ethsw, ethsw->bpid);

		अगर (unlikely(*count < BUFS_PER_CMD))
			वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम dpaa2_चयन_drain_bp(काष्ठा ethsw_core *ethsw)
अणु
	u64 buf_array[BUFS_PER_CMD];
	पूर्णांक ret;

	करो अणु
		ret = dpaa2_io_service_acquire(शून्य, ethsw->bpid,
					       buf_array, BUFS_PER_CMD);
		अगर (ret < 0) अणु
			dev_err(ethsw->dev,
				"dpaa2_io_service_acquire() = %d\n", ret);
			वापस;
		पूर्ण
		dpaa2_चयन_मुक्त_bufs(ethsw, buf_array, ret);

	पूर्ण जबतक (ret);
पूर्ण

अटल पूर्णांक dpaa2_चयन_setup_dpbp(काष्ठा ethsw_core *ethsw)
अणु
	काष्ठा dpsw_ctrl_अगर_pools_cfg dpsw_ctrl_अगर_pools_cfg = अणु 0 पूर्ण;
	काष्ठा device *dev = ethsw->dev;
	काष्ठा fsl_mc_device *dpbp_dev;
	काष्ठा dpbp_attr dpbp_attrs;
	पूर्णांक err;

	err = fsl_mc_object_allocate(to_fsl_mc_device(dev), FSL_MC_POOL_DPBP,
				     &dpbp_dev);
	अगर (err) अणु
		अगर (err == -ENXIO)
			err = -EPROBE_DEFER;
		अन्यथा
			dev_err(dev, "DPBP device allocation failed\n");
		वापस err;
	पूर्ण
	ethsw->dpbp_dev = dpbp_dev;

	err = dpbp_खोलो(ethsw->mc_io, 0, dpbp_dev->obj_desc.id,
			&dpbp_dev->mc_handle);
	अगर (err) अणु
		dev_err(dev, "dpbp_open() failed\n");
		जाओ err_खोलो;
	पूर्ण

	err = dpbp_reset(ethsw->mc_io, 0, dpbp_dev->mc_handle);
	अगर (err) अणु
		dev_err(dev, "dpbp_reset() failed\n");
		जाओ err_reset;
	पूर्ण

	err = dpbp_enable(ethsw->mc_io, 0, dpbp_dev->mc_handle);
	अगर (err) अणु
		dev_err(dev, "dpbp_enable() failed\n");
		जाओ err_enable;
	पूर्ण

	err = dpbp_get_attributes(ethsw->mc_io, 0, dpbp_dev->mc_handle,
				  &dpbp_attrs);
	अगर (err) अणु
		dev_err(dev, "dpbp_get_attributes() failed\n");
		जाओ err_get_attr;
	पूर्ण

	dpsw_ctrl_अगर_pools_cfg.num_dpbp = 1;
	dpsw_ctrl_अगर_pools_cfg.pools[0].dpbp_id = dpbp_attrs.id;
	dpsw_ctrl_अगर_pools_cfg.pools[0].buffer_size = DPAA2_SWITCH_RX_BUF_SIZE;
	dpsw_ctrl_अगर_pools_cfg.pools[0].backup_pool = 0;

	err = dpsw_ctrl_अगर_set_pools(ethsw->mc_io, 0, ethsw->dpsw_handle,
				     &dpsw_ctrl_अगर_pools_cfg);
	अगर (err) अणु
		dev_err(dev, "dpsw_ctrl_if_set_pools() failed\n");
		जाओ err_get_attr;
	पूर्ण
	ethsw->bpid = dpbp_attrs.id;

	वापस 0;

err_get_attr:
	dpbp_disable(ethsw->mc_io, 0, dpbp_dev->mc_handle);
err_enable:
err_reset:
	dpbp_बंद(ethsw->mc_io, 0, dpbp_dev->mc_handle);
err_खोलो:
	fsl_mc_object_मुक्त(dpbp_dev);
	वापस err;
पूर्ण

अटल व्योम dpaa2_चयन_मुक्त_dpbp(काष्ठा ethsw_core *ethsw)
अणु
	dpbp_disable(ethsw->mc_io, 0, ethsw->dpbp_dev->mc_handle);
	dpbp_बंद(ethsw->mc_io, 0, ethsw->dpbp_dev->mc_handle);
	fsl_mc_object_मुक्त(ethsw->dpbp_dev);
पूर्ण

अटल पूर्णांक dpaa2_चयन_alloc_rings(काष्ठा ethsw_core *ethsw)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < DPAA2_SWITCH_RX_NUM_FQS; i++) अणु
		ethsw->fq[i].store =
			dpaa2_io_store_create(DPAA2_SWITCH_STORE_SIZE,
					      ethsw->dev);
		अगर (!ethsw->fq[i].store) अणु
			dev_err(ethsw->dev, "dpaa2_io_store_create failed\n");
			जबतक (--i >= 0)
				dpaa2_io_store_destroy(ethsw->fq[i].store);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम dpaa2_चयन_destroy_rings(काष्ठा ethsw_core *ethsw)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < DPAA2_SWITCH_RX_NUM_FQS; i++)
		dpaa2_io_store_destroy(ethsw->fq[i].store);
पूर्ण

अटल पूर्णांक dpaa2_चयन_pull_fq(काष्ठा dpaa2_चयन_fq *fq)
अणु
	पूर्णांक err, retries = 0;

	/* Try to pull from the FQ जबतक the portal is busy and we didn't hit
	 * the maximum number fo retries
	 */
	करो अणु
		err = dpaa2_io_service_pull_fq(शून्य, fq->fqid, fq->store);
		cpu_relax();
	पूर्ण जबतक (err == -EBUSY && retries++ < DPAA2_SWITCH_SWP_BUSY_RETRIES);

	अगर (unlikely(err))
		dev_err(fq->ethsw->dev, "dpaa2_io_service_pull err %d", err);

	वापस err;
पूर्ण

/* Consume all frames pull-dequeued पूर्णांकo the store */
अटल पूर्णांक dpaa2_चयन_store_consume(काष्ठा dpaa2_चयन_fq *fq)
अणु
	काष्ठा ethsw_core *ethsw = fq->ethsw;
	पूर्णांक cleaned = 0, is_last;
	काष्ठा dpaa2_dq *dq;
	पूर्णांक retries = 0;

	करो अणु
		/* Get the next available FD from the store */
		dq = dpaa2_io_store_next(fq->store, &is_last);
		अगर (unlikely(!dq)) अणु
			अगर (retries++ >= DPAA2_SWITCH_SWP_BUSY_RETRIES) अणु
				dev_err_once(ethsw->dev,
					     "No valid dequeue response\n");
				वापस -ETIMEDOUT;
			पूर्ण
			जारी;
		पूर्ण

		अगर (fq->type == DPSW_QUEUE_RX)
			dpaa2_चयन_rx(fq, dpaa2_dq_fd(dq));
		अन्यथा
			dpaa2_चयन_tx_conf(fq, dpaa2_dq_fd(dq));
		cleaned++;

	पूर्ण जबतक (!is_last);

	वापस cleaned;
पूर्ण

/* NAPI poll routine */
अटल पूर्णांक dpaa2_चयन_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	पूर्णांक err, cleaned = 0, store_cleaned, work_करोne;
	काष्ठा dpaa2_चयन_fq *fq;
	पूर्णांक retries = 0;

	fq = container_of(napi, काष्ठा dpaa2_चयन_fq, napi);

	करो अणु
		err = dpaa2_चयन_pull_fq(fq);
		अगर (unlikely(err))
			अवरोध;

		/* Refill pool अगर appropriate */
		dpaa2_चयन_refill_bp(fq->ethsw);

		store_cleaned = dpaa2_चयन_store_consume(fq);
		cleaned += store_cleaned;

		अगर (cleaned >= budget) अणु
			work_करोne = budget;
			जाओ out;
		पूर्ण

	पूर्ण जबतक (store_cleaned);

	/* We didn't consume the entire budget, so finish napi and re-enable
	 * data availability notअगरications
	 */
	napi_complete_करोne(napi, cleaned);
	करो अणु
		err = dpaa2_io_service_rearm(शून्य, &fq->nctx);
		cpu_relax();
	पूर्ण जबतक (err == -EBUSY && retries++ < DPAA2_SWITCH_SWP_BUSY_RETRIES);

	work_करोne = max(cleaned, 1);
out:

	वापस work_करोne;
पूर्ण

अटल व्योम dpaa2_चयन_fqdan_cb(काष्ठा dpaa2_io_notअगरication_ctx *nctx)
अणु
	काष्ठा dpaa2_चयन_fq *fq;

	fq = container_of(nctx, काष्ठा dpaa2_चयन_fq, nctx);

	napi_schedule(&fq->napi);
पूर्ण

अटल पूर्णांक dpaa2_चयन_setup_dpio(काष्ठा ethsw_core *ethsw)
अणु
	काष्ठा dpsw_ctrl_अगर_queue_cfg queue_cfg;
	काष्ठा dpaa2_io_notअगरication_ctx *nctx;
	पूर्णांक err, i, j;

	क्रम (i = 0; i < DPAA2_SWITCH_RX_NUM_FQS; i++) अणु
		nctx = &ethsw->fq[i].nctx;

		/* Register a new software context क्रम the FQID.
		 * By using शून्य as the first parameter, we specअगरy that we करो
		 * not care on which cpu are पूर्णांकerrupts received क्रम this queue
		 */
		nctx->is_cdan = 0;
		nctx->id = ethsw->fq[i].fqid;
		nctx->desired_cpu = DPAA2_IO_ANY_CPU;
		nctx->cb = dpaa2_चयन_fqdan_cb;
		err = dpaa2_io_service_रेजिस्टर(शून्य, nctx, ethsw->dev);
		अगर (err) अणु
			err = -EPROBE_DEFER;
			जाओ err_रेजिस्टर;
		पूर्ण

		queue_cfg.options = DPSW_CTRL_IF_QUEUE_OPT_DEST |
				    DPSW_CTRL_IF_QUEUE_OPT_USER_CTX;
		queue_cfg.dest_cfg.dest_type = DPSW_CTRL_IF_DEST_DPIO;
		queue_cfg.dest_cfg.dest_id = nctx->dpio_id;
		queue_cfg.dest_cfg.priority = 0;
		queue_cfg.user_ctx = nctx->qman64;

		err = dpsw_ctrl_अगर_set_queue(ethsw->mc_io, 0,
					     ethsw->dpsw_handle,
					     ethsw->fq[i].type,
					     &queue_cfg);
		अगर (err)
			जाओ err_set_queue;
	पूर्ण

	वापस 0;

err_set_queue:
	dpaa2_io_service_deरेजिस्टर(शून्य, nctx, ethsw->dev);
err_रेजिस्टर:
	क्रम (j = 0; j < i; j++)
		dpaa2_io_service_deरेजिस्टर(शून्य, &ethsw->fq[j].nctx,
					    ethsw->dev);

	वापस err;
पूर्ण

अटल व्योम dpaa2_चयन_मुक्त_dpio(काष्ठा ethsw_core *ethsw)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < DPAA2_SWITCH_RX_NUM_FQS; i++)
		dpaa2_io_service_deरेजिस्टर(शून्य, &ethsw->fq[i].nctx,
					    ethsw->dev);
पूर्ण

अटल पूर्णांक dpaa2_चयन_ctrl_अगर_setup(काष्ठा ethsw_core *ethsw)
अणु
	पूर्णांक err;

	/* setup FQs क्रम Rx and Tx Conf */
	err = dpaa2_चयन_setup_fqs(ethsw);
	अगर (err)
		वापस err;

	/* setup the buffer pool needed on the Rx path */
	err = dpaa2_चयन_setup_dpbp(ethsw);
	अगर (err)
		वापस err;

	err = dpaa2_चयन_seed_bp(ethsw);
	अगर (err)
		जाओ err_मुक्त_dpbp;

	err = dpaa2_चयन_alloc_rings(ethsw);
	अगर (err)
		जाओ err_drain_dpbp;

	err = dpaa2_चयन_setup_dpio(ethsw);
	अगर (err)
		जाओ err_destroy_rings;

	err = dpsw_ctrl_अगर_enable(ethsw->mc_io, 0, ethsw->dpsw_handle);
	अगर (err) अणु
		dev_err(ethsw->dev, "dpsw_ctrl_if_enable err %d\n", err);
		जाओ err_deरेजिस्टर_dpio;
	पूर्ण

	वापस 0;

err_deरेजिस्टर_dpio:
	dpaa2_चयन_मुक्त_dpio(ethsw);
err_destroy_rings:
	dpaa2_चयन_destroy_rings(ethsw);
err_drain_dpbp:
	dpaa2_चयन_drain_bp(ethsw);
err_मुक्त_dpbp:
	dpaa2_चयन_मुक्त_dpbp(ethsw);

	वापस err;
पूर्ण

अटल पूर्णांक dpaa2_चयन_init(काष्ठा fsl_mc_device *sw_dev)
अणु
	काष्ठा device *dev = &sw_dev->dev;
	काष्ठा ethsw_core *ethsw = dev_get_drvdata(dev);
	काष्ठा dpsw_vlan_अगर_cfg vcfg = अणु0पूर्ण;
	काष्ठा dpsw_tci_cfg tci_cfg = अणु0पूर्ण;
	काष्ठा dpsw_stp_cfg stp_cfg;
	पूर्णांक err;
	u16 i;

	ethsw->dev_id = sw_dev->obj_desc.id;

	err = dpsw_खोलो(ethsw->mc_io, 0, ethsw->dev_id, &ethsw->dpsw_handle);
	अगर (err) अणु
		dev_err(dev, "dpsw_open err %d\n", err);
		वापस err;
	पूर्ण

	err = dpsw_get_attributes(ethsw->mc_io, 0, ethsw->dpsw_handle,
				  &ethsw->sw_attr);
	अगर (err) अणु
		dev_err(dev, "dpsw_get_attributes err %d\n", err);
		जाओ err_बंद;
	पूर्ण

	err = dpsw_get_api_version(ethsw->mc_io, 0,
				   &ethsw->major,
				   &ethsw->minor);
	अगर (err) अणु
		dev_err(dev, "dpsw_get_api_version err %d\n", err);
		जाओ err_बंद;
	पूर्ण

	/* Minimum supported DPSW version check */
	अगर (ethsw->major < DPSW_MIN_VER_MAJOR ||
	    (ethsw->major == DPSW_MIN_VER_MAJOR &&
	     ethsw->minor < DPSW_MIN_VER_MINOR)) अणु
		dev_err(dev, "DPSW version %d:%d not supported. Use firmware 10.28.0 or greater.\n",
			ethsw->major, ethsw->minor);
		err = -EOPNOTSUPP;
		जाओ err_बंद;
	पूर्ण

	अगर (!dpaa2_चयन_supports_cpu_traffic(ethsw)) अणु
		err = -EOPNOTSUPP;
		जाओ err_बंद;
	पूर्ण

	dpaa2_चयन_detect_features(ethsw);

	err = dpsw_reset(ethsw->mc_io, 0, ethsw->dpsw_handle);
	अगर (err) अणु
		dev_err(dev, "dpsw_reset err %d\n", err);
		जाओ err_बंद;
	पूर्ण

	stp_cfg.vlan_id = DEFAULT_VLAN_ID;
	stp_cfg.state = DPSW_STP_STATE_FORWARDING;

	क्रम (i = 0; i < ethsw->sw_attr.num_अगरs; i++) अणु
		err = dpsw_अगर_disable(ethsw->mc_io, 0, ethsw->dpsw_handle, i);
		अगर (err) अणु
			dev_err(dev, "dpsw_if_disable err %d\n", err);
			जाओ err_बंद;
		पूर्ण

		err = dpsw_अगर_set_stp(ethsw->mc_io, 0, ethsw->dpsw_handle, i,
				      &stp_cfg);
		अगर (err) अणु
			dev_err(dev, "dpsw_if_set_stp err %d for port %d\n",
				err, i);
			जाओ err_बंद;
		पूर्ण

		/* Switch starts with all ports configured to VLAN 1. Need to
		 * हटाओ this setting to allow configuration at bridge join
		 */
		vcfg.num_अगरs = 1;
		vcfg.अगर_id[0] = i;
		err = dpsw_vlan_हटाओ_अगर_untagged(ethsw->mc_io, 0, ethsw->dpsw_handle,
						   DEFAULT_VLAN_ID, &vcfg);
		अगर (err) अणु
			dev_err(dev, "dpsw_vlan_remove_if_untagged err %d\n",
				err);
			जाओ err_बंद;
		पूर्ण

		tci_cfg.vlan_id = 4095;
		err = dpsw_अगर_set_tci(ethsw->mc_io, 0, ethsw->dpsw_handle, i, &tci_cfg);
		अगर (err) अणु
			dev_err(dev, "dpsw_if_set_tci err %d\n", err);
			जाओ err_बंद;
		पूर्ण

		err = dpsw_vlan_हटाओ_अगर(ethsw->mc_io, 0, ethsw->dpsw_handle,
					  DEFAULT_VLAN_ID, &vcfg);
		अगर (err) अणु
			dev_err(dev, "dpsw_vlan_remove_if err %d\n", err);
			जाओ err_बंद;
		पूर्ण
	पूर्ण

	err = dpsw_vlan_हटाओ(ethsw->mc_io, 0, ethsw->dpsw_handle, DEFAULT_VLAN_ID);
	अगर (err) अणु
		dev_err(dev, "dpsw_vlan_remove err %d\n", err);
		जाओ err_बंद;
	पूर्ण

	ethsw->workqueue = alloc_ordered_workqueue("%s_%d_ordered",
						   WQ_MEM_RECLAIM, "ethsw",
						   ethsw->sw_attr.id);
	अगर (!ethsw->workqueue) अणु
		err = -ENOMEM;
		जाओ err_बंद;
	पूर्ण

	err = dpsw_fdb_हटाओ(ethsw->mc_io, 0, ethsw->dpsw_handle, 0);
	अगर (err)
		जाओ err_destroy_ordered_workqueue;

	err = dpaa2_चयन_ctrl_अगर_setup(ethsw);
	अगर (err)
		जाओ err_destroy_ordered_workqueue;

	वापस 0;

err_destroy_ordered_workqueue:
	destroy_workqueue(ethsw->workqueue);

err_बंद:
	dpsw_बंद(ethsw->mc_io, 0, ethsw->dpsw_handle);
	वापस err;
पूर्ण

/* Add an ACL to redirect frames with specअगरic destination MAC address to
 * control पूर्णांकerface
 */
अटल पूर्णांक dpaa2_चयन_port_trap_mac_addr(काष्ठा ethsw_port_priv *port_priv,
					   स्थिर अक्षर *mac)
अणु
	काष्ठा dpaa2_चयन_acl_entry acl_entry = अणु0पूर्ण;

	/* Match on the destination MAC address */
	ether_addr_copy(acl_entry.key.match.l2_dest_mac, mac);
	eth_broadcast_addr(acl_entry.key.mask.l2_dest_mac);

	/* Trap to CPU */
	acl_entry.cfg.precedence = 0;
	acl_entry.cfg.result.action = DPSW_ACL_ACTION_REसूचीECT_TO_CTRL_IF;

	वापस dpaa2_चयन_acl_entry_add(port_priv->acl_tbl, &acl_entry);
पूर्ण

अटल पूर्णांक dpaa2_चयन_port_init(काष्ठा ethsw_port_priv *port_priv, u16 port)
अणु
	स्थिर अक्षर stpa[ETH_ALEN] = अणु0x01, 0x80, 0xc2, 0x00, 0x00, 0x00पूर्ण;
	काष्ठा चयनdev_obj_port_vlan vlan = अणु
		.obj.id = SWITCHDEV_OBJ_ID_PORT_VLAN,
		.vid = DEFAULT_VLAN_ID,
		.flags = BRIDGE_VLAN_INFO_UNTAGGED | BRIDGE_VLAN_INFO_PVID,
	पूर्ण;
	काष्ठा net_device *netdev = port_priv->netdev;
	काष्ठा ethsw_core *ethsw = port_priv->ethsw_data;
	काष्ठा dpaa2_चयन_acl_tbl *acl_tbl;
	काष्ठा dpsw_fdb_cfg fdb_cfg = अणु0पूर्ण;
	काष्ठा dpsw_अगर_attr dpsw_अगर_attr;
	काष्ठा dpaa2_चयन_fdb *fdb;
	काष्ठा dpsw_acl_cfg acl_cfg;
	u16 fdb_id, acl_tbl_id;
	पूर्णांक err;

	/* Get the Tx queue क्रम this specअगरic port */
	err = dpsw_अगर_get_attributes(ethsw->mc_io, 0, ethsw->dpsw_handle,
				     port_priv->idx, &dpsw_अगर_attr);
	अगर (err) अणु
		netdev_err(netdev, "dpsw_if_get_attributes err %d\n", err);
		वापस err;
	पूर्ण
	port_priv->tx_qdid = dpsw_अगर_attr.qdid;

	/* Create a FDB table क्रम this particular चयन port */
	fdb_cfg.num_fdb_entries = ethsw->sw_attr.max_fdb_entries / ethsw->sw_attr.num_अगरs;
	err = dpsw_fdb_add(ethsw->mc_io, 0, ethsw->dpsw_handle,
			   &fdb_id, &fdb_cfg);
	अगर (err) अणु
		netdev_err(netdev, "dpsw_fdb_add err %d\n", err);
		वापस err;
	पूर्ण

	/* Find an unused dpaa2_चयन_fdb काष्ठाure and use it */
	fdb = dpaa2_चयन_fdb_get_unused(ethsw);
	fdb->fdb_id = fdb_id;
	fdb->in_use = true;
	fdb->bridge_dev = शून्य;
	port_priv->fdb = fdb;

	/* We need to add VLAN 1 as the PVID on this port until it is under a
	 * bridge since the DPAA2 चयन is not able to handle the traffic in a
	 * VLAN unaware fashion
	 */
	err = dpaa2_चयन_port_vlans_add(netdev, &vlan);
	अगर (err)
		वापस err;

	/* Setup the egress flooding करोमुख्यs (broadcast, unknown unicast */
	err = dpaa2_चयन_fdb_set_egress_flood(ethsw, port_priv->fdb->fdb_id);
	अगर (err)
		वापस err;

	/* Create an ACL table to be used by this चयन port */
	acl_cfg.max_entries = DPAA2_ETHSW_PORT_MAX_ACL_ENTRIES;
	err = dpsw_acl_add(ethsw->mc_io, 0, ethsw->dpsw_handle,
			   &acl_tbl_id, &acl_cfg);
	अगर (err) अणु
		netdev_err(netdev, "dpsw_acl_add err %d\n", err);
		वापस err;
	पूर्ण

	acl_tbl = dpaa2_चयन_acl_tbl_get_unused(ethsw);
	acl_tbl->ethsw = ethsw;
	acl_tbl->id = acl_tbl_id;
	acl_tbl->in_use = true;
	acl_tbl->num_rules = 0;
	INIT_LIST_HEAD(&acl_tbl->entries);

	err = dpaa2_चयन_port_acl_tbl_bind(port_priv, acl_tbl);
	अगर (err)
		वापस err;

	err = dpaa2_चयन_port_trap_mac_addr(port_priv, stpa);
	अगर (err)
		वापस err;

	वापस err;
पूर्ण

अटल व्योम dpaa2_चयन_takeकरोwn(काष्ठा fsl_mc_device *sw_dev)
अणु
	काष्ठा device *dev = &sw_dev->dev;
	काष्ठा ethsw_core *ethsw = dev_get_drvdata(dev);
	पूर्णांक err;

	err = dpsw_बंद(ethsw->mc_io, 0, ethsw->dpsw_handle);
	अगर (err)
		dev_warn(dev, "dpsw_close err %d\n", err);
पूर्ण

अटल व्योम dpaa2_चयन_ctrl_अगर_tearकरोwn(काष्ठा ethsw_core *ethsw)
अणु
	dpsw_ctrl_अगर_disable(ethsw->mc_io, 0, ethsw->dpsw_handle);
	dpaa2_चयन_मुक्त_dpio(ethsw);
	dpaa2_चयन_destroy_rings(ethsw);
	dpaa2_चयन_drain_bp(ethsw);
	dpaa2_चयन_मुक्त_dpbp(ethsw);
पूर्ण

अटल पूर्णांक dpaa2_चयन_हटाओ(काष्ठा fsl_mc_device *sw_dev)
अणु
	काष्ठा ethsw_port_priv *port_priv;
	काष्ठा ethsw_core *ethsw;
	काष्ठा device *dev;
	पूर्णांक i;

	dev = &sw_dev->dev;
	ethsw = dev_get_drvdata(dev);

	dpaa2_चयन_ctrl_अगर_tearकरोwn(ethsw);

	dpaa2_चयन_tearकरोwn_irqs(sw_dev);

	dpsw_disable(ethsw->mc_io, 0, ethsw->dpsw_handle);

	क्रम (i = 0; i < ethsw->sw_attr.num_अगरs; i++) अणु
		port_priv = ethsw->ports[i];
		unरेजिस्टर_netdev(port_priv->netdev);
		मुक्त_netdev(port_priv->netdev);
	पूर्ण

	kमुक्त(ethsw->fdbs);
	kमुक्त(ethsw->acls);
	kमुक्त(ethsw->ports);

	dpaa2_चयन_takeकरोwn(sw_dev);

	destroy_workqueue(ethsw->workqueue);

	fsl_mc_portal_मुक्त(ethsw->mc_io);

	kमुक्त(ethsw);

	dev_set_drvdata(dev, शून्य);

	वापस 0;
पूर्ण

अटल पूर्णांक dpaa2_चयन_probe_port(काष्ठा ethsw_core *ethsw,
				   u16 port_idx)
अणु
	काष्ठा ethsw_port_priv *port_priv;
	काष्ठा device *dev = ethsw->dev;
	काष्ठा net_device *port_netdev;
	पूर्णांक err;

	port_netdev = alloc_etherdev(माप(काष्ठा ethsw_port_priv));
	अगर (!port_netdev) अणु
		dev_err(dev, "alloc_etherdev error\n");
		वापस -ENOMEM;
	पूर्ण

	port_priv = netdev_priv(port_netdev);
	port_priv->netdev = port_netdev;
	port_priv->ethsw_data = ethsw;

	port_priv->idx = port_idx;
	port_priv->stp_state = BR_STATE_FORWARDING;

	SET_NETDEV_DEV(port_netdev, dev);
	port_netdev->netdev_ops = &dpaa2_चयन_port_ops;
	port_netdev->ethtool_ops = &dpaa2_चयन_port_ethtool_ops;

	port_netdev->needed_headroom = DPAA2_SWITCH_NEEDED_HEADROOM;

	port_priv->bcast_flood = true;
	port_priv->ucast_flood = true;

	/* Set MTU limits */
	port_netdev->min_mtu = ETH_MIN_MTU;
	port_netdev->max_mtu = ETHSW_MAX_FRAME_LENGTH;

	/* Populate the निजी port काष्ठाure so that later calls to
	 * dpaa2_चयन_port_init() can use it.
	 */
	ethsw->ports[port_idx] = port_priv;

	/* The DPAA2 चयन's ingress path depends on the VLAN table,
	 * thus we are not able to disable VLAN filtering.
	 */
	port_netdev->features = NETIF_F_HW_VLAN_CTAG_FILTER |
				NETIF_F_HW_VLAN_STAG_FILTER |
				NETIF_F_HW_TC;

	err = dpaa2_चयन_port_init(port_priv, port_idx);
	अगर (err)
		जाओ err_port_probe;

	err = dpaa2_चयन_port_set_mac_addr(port_priv);
	अगर (err)
		जाओ err_port_probe;

	err = dpaa2_चयन_port_set_learning(port_priv, false);
	अगर (err)
		जाओ err_port_probe;
	port_priv->learn_ena = false;

	वापस 0;

err_port_probe:
	मुक्त_netdev(port_netdev);
	ethsw->ports[port_idx] = शून्य;

	वापस err;
पूर्ण

अटल पूर्णांक dpaa2_चयन_probe(काष्ठा fsl_mc_device *sw_dev)
अणु
	काष्ठा device *dev = &sw_dev->dev;
	काष्ठा ethsw_core *ethsw;
	पूर्णांक i, err;

	/* Allocate चयन core*/
	ethsw = kzalloc(माप(*ethsw), GFP_KERNEL);

	अगर (!ethsw)
		वापस -ENOMEM;

	ethsw->dev = dev;
	ethsw->iommu_करोमुख्य = iommu_get_करोमुख्य_क्रम_dev(dev);
	dev_set_drvdata(dev, ethsw);

	err = fsl_mc_portal_allocate(sw_dev, FSL_MC_IO_ATOMIC_CONTEXT_PORTAL,
				     &ethsw->mc_io);
	अगर (err) अणु
		अगर (err == -ENXIO)
			err = -EPROBE_DEFER;
		अन्यथा
			dev_err(dev, "fsl_mc_portal_allocate err %d\n", err);
		जाओ err_मुक्त_drvdata;
	पूर्ण

	err = dpaa2_चयन_init(sw_dev);
	अगर (err)
		जाओ err_मुक्त_cmdport;

	ethsw->ports = kसुस्मृति(ethsw->sw_attr.num_अगरs, माप(*ethsw->ports),
			       GFP_KERNEL);
	अगर (!(ethsw->ports)) अणु
		err = -ENOMEM;
		जाओ err_takeकरोwn;
	पूर्ण

	ethsw->fdbs = kसुस्मृति(ethsw->sw_attr.num_अगरs, माप(*ethsw->fdbs),
			      GFP_KERNEL);
	अगर (!ethsw->fdbs) अणु
		err = -ENOMEM;
		जाओ err_मुक्त_ports;
	पूर्ण

	ethsw->acls = kसुस्मृति(ethsw->sw_attr.num_अगरs, माप(*ethsw->acls),
			      GFP_KERNEL);
	अगर (!ethsw->acls) अणु
		err = -ENOMEM;
		जाओ err_मुक्त_fdbs;
	पूर्ण

	क्रम (i = 0; i < ethsw->sw_attr.num_अगरs; i++) अणु
		err = dpaa2_चयन_probe_port(ethsw, i);
		अगर (err)
			जाओ err_मुक्त_netdev;
	पूर्ण

	/* Add a NAPI instance क्रम each of the Rx queues. The first port's
	 * net_device will be associated with the instances since we करो not have
	 * dअगरferent queues क्रम each चयन ports.
	 */
	क्रम (i = 0; i < DPAA2_SWITCH_RX_NUM_FQS; i++)
		netअगर_napi_add(ethsw->ports[0]->netdev,
			       &ethsw->fq[i].napi, dpaa2_चयन_poll,
			       NAPI_POLL_WEIGHT);

	err = dpsw_enable(ethsw->mc_io, 0, ethsw->dpsw_handle);
	अगर (err) अणु
		dev_err(ethsw->dev, "dpsw_enable err %d\n", err);
		जाओ err_मुक्त_netdev;
	पूर्ण

	/* Setup IRQs */
	err = dpaa2_चयन_setup_irqs(sw_dev);
	अगर (err)
		जाओ err_stop;

	/* Register the netdev only when the entire setup is करोne and the
	 * चयन port पूर्णांकerfaces are पढ़ोy to receive traffic
	 */
	क्रम (i = 0; i < ethsw->sw_attr.num_अगरs; i++) अणु
		err = रेजिस्टर_netdev(ethsw->ports[i]->netdev);
		अगर (err < 0) अणु
			dev_err(dev, "register_netdev error %d\n", err);
			जाओ err_unरेजिस्टर_ports;
		पूर्ण
	पूर्ण

	वापस 0;

err_unरेजिस्टर_ports:
	क्रम (i--; i >= 0; i--)
		unरेजिस्टर_netdev(ethsw->ports[i]->netdev);
	dpaa2_चयन_tearकरोwn_irqs(sw_dev);
err_stop:
	dpsw_disable(ethsw->mc_io, 0, ethsw->dpsw_handle);
err_मुक्त_netdev:
	क्रम (i--; i >= 0; i--)
		मुक्त_netdev(ethsw->ports[i]->netdev);
	kमुक्त(ethsw->acls);
err_मुक्त_fdbs:
	kमुक्त(ethsw->fdbs);
err_मुक्त_ports:
	kमुक्त(ethsw->ports);

err_takeकरोwn:
	dpaa2_चयन_takeकरोwn(sw_dev);

err_मुक्त_cmdport:
	fsl_mc_portal_मुक्त(ethsw->mc_io);

err_मुक्त_drvdata:
	kमुक्त(ethsw);
	dev_set_drvdata(dev, शून्य);

	वापस err;
पूर्ण

अटल स्थिर काष्ठा fsl_mc_device_id dpaa2_चयन_match_id_table[] = अणु
	अणु
		.venकरोr = FSL_MC_VENDOR_FREESCALE,
		.obj_type = "dpsw",
	पूर्ण,
	अणु .venकरोr = 0x0 पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(fslmc, dpaa2_चयन_match_id_table);

अटल काष्ठा fsl_mc_driver dpaa2_चयन_drv = अणु
	.driver = अणु
		.name = KBUILD_MODNAME,
		.owner = THIS_MODULE,
	पूर्ण,
	.probe = dpaa2_चयन_probe,
	.हटाओ = dpaa2_चयन_हटाओ,
	.match_id_table = dpaa2_चयन_match_id_table
पूर्ण;

अटल काष्ठा notअगरier_block dpaa2_चयन_port_nb __पढ़ो_mostly = अणु
	.notअगरier_call = dpaa2_चयन_port_netdevice_event,
पूर्ण;

अटल काष्ठा notअगरier_block dpaa2_चयन_port_चयनdev_nb = अणु
	.notअगरier_call = dpaa2_चयन_port_event,
पूर्ण;

अटल काष्ठा notअगरier_block dpaa2_चयन_port_चयनdev_blocking_nb = अणु
	.notअगरier_call = dpaa2_चयन_port_blocking_event,
पूर्ण;

अटल पूर्णांक dpaa2_चयन_रेजिस्टर_notअगरiers(व्योम)
अणु
	पूर्णांक err;

	err = रेजिस्टर_netdevice_notअगरier(&dpaa2_चयन_port_nb);
	अगर (err) अणु
		pr_err("dpaa2-switch: failed to register net_device notifier (%d)\n", err);
		वापस err;
	पूर्ण

	err = रेजिस्टर_चयनdev_notअगरier(&dpaa2_चयन_port_चयनdev_nb);
	अगर (err) अणु
		pr_err("dpaa2-switch: failed to register switchdev notifier (%d)\n", err);
		जाओ err_चयनdev_nb;
	पूर्ण

	err = रेजिस्टर_चयनdev_blocking_notअगरier(&dpaa2_चयन_port_चयनdev_blocking_nb);
	अगर (err) अणु
		pr_err("dpaa2-switch: failed to register switchdev blocking notifier (%d)\n", err);
		जाओ err_चयनdev_blocking_nb;
	पूर्ण

	वापस 0;

err_चयनdev_blocking_nb:
	unरेजिस्टर_चयनdev_notअगरier(&dpaa2_चयन_port_चयनdev_nb);
err_चयनdev_nb:
	unरेजिस्टर_netdevice_notअगरier(&dpaa2_चयन_port_nb);

	वापस err;
पूर्ण

अटल व्योम dpaa2_चयन_unरेजिस्टर_notअगरiers(व्योम)
अणु
	पूर्णांक err;

	err = unरेजिस्टर_चयनdev_blocking_notअगरier(&dpaa2_चयन_port_चयनdev_blocking_nb);
	अगर (err)
		pr_err("dpaa2-switch: failed to unregister switchdev blocking notifier (%d)\n",
		       err);

	err = unरेजिस्टर_चयनdev_notअगरier(&dpaa2_चयन_port_चयनdev_nb);
	अगर (err)
		pr_err("dpaa2-switch: failed to unregister switchdev notifier (%d)\n", err);

	err = unरेजिस्टर_netdevice_notअगरier(&dpaa2_चयन_port_nb);
	अगर (err)
		pr_err("dpaa2-switch: failed to unregister net_device notifier (%d)\n", err);
पूर्ण

अटल पूर्णांक __init dpaa2_चयन_driver_init(व्योम)
अणु
	पूर्णांक err;

	err = fsl_mc_driver_रेजिस्टर(&dpaa2_चयन_drv);
	अगर (err)
		वापस err;

	err = dpaa2_चयन_रेजिस्टर_notअगरiers();
	अगर (err) अणु
		fsl_mc_driver_unरेजिस्टर(&dpaa2_चयन_drv);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास dpaa2_चयन_driver_निकास(व्योम)
अणु
	dpaa2_चयन_unरेजिस्टर_notअगरiers();
	fsl_mc_driver_unरेजिस्टर(&dpaa2_चयन_drv);
पूर्ण

module_init(dpaa2_चयन_driver_init);
module_निकास(dpaa2_चयन_driver_निकास);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("DPAA2 Ethernet Switch Driver");
