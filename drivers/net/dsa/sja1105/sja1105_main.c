<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2018, Sensor-Technik Wiedemann GmbH
 * Copyright (c) 2018-2019, Vladimir Oltean <olteanv@gmail.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/phylink.h>
#समावेश <linux/of.h>
#समावेश <linux/of_net.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/of_device.h>
#समावेश <linux/netdev_features.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_bridge.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/dsa/8021q.h>
#समावेश "sja1105.h"
#समावेश "sja1105_sgmii.h"
#समावेश "sja1105_tas.h"

#घोषणा SJA1105_UNKNOWN_MULTICAST	0x010000000000ull
#घोषणा SJA1105_DEFAULT_VLAN		(VLAN_N_VID - 1)

अटल स्थिर काष्ठा dsa_चयन_ops sja1105_चयन_ops;

अटल व्योम sja1105_hw_reset(काष्ठा gpio_desc *gpio, अचिन्हित पूर्णांक pulse_len,
			     अचिन्हित पूर्णांक startup_delay)
अणु
	gpiod_set_value_cansleep(gpio, 1);
	/* Wait क्रम minimum reset pulse length */
	msleep(pulse_len);
	gpiod_set_value_cansleep(gpio, 0);
	/* Wait until chip is पढ़ोy after reset */
	msleep(startup_delay);
पूर्ण

अटल व्योम
sja1105_port_allow_traffic(काष्ठा sja1105_l2_क्रमwarding_entry *l2_fwd,
			   पूर्णांक from, पूर्णांक to, bool allow)
अणु
	अगर (allow)
		l2_fwd[from].reach_port |= BIT(to);
	अन्यथा
		l2_fwd[from].reach_port &= ~BIT(to);
पूर्ण

अटल bool sja1105_can_क्रमward(काष्ठा sja1105_l2_क्रमwarding_entry *l2_fwd,
				पूर्णांक from, पूर्णांक to)
अणु
	वापस !!(l2_fwd[from].reach_port & BIT(to));
पूर्ण

/* Structure used to temporarily transport device tree
 * settings पूर्णांकo sja1105_setup
 */
काष्ठा sja1105_dt_port अणु
	phy_पूर्णांकerface_t phy_mode;
	sja1105_mii_role_t role;
पूर्ण;

अटल पूर्णांक sja1105_init_mac_settings(काष्ठा sja1105_निजी *priv)
अणु
	काष्ठा sja1105_mac_config_entry शेष_mac = अणु
		/* Enable all 8 priority queues on egress.
		 * Every queue i holds top[i] - base[i] frames.
		 * Sum of top[i] - base[i] is 511 (max hardware limit).
		 */
		.top  = अणु0x3F, 0x7F, 0xBF, 0xFF, 0x13F, 0x17F, 0x1BF, 0x1FFपूर्ण,
		.base = अणु0x0, 0x40, 0x80, 0xC0, 0x100, 0x140, 0x180, 0x1C0पूर्ण,
		.enabled = अणुtrue, true, true, true, true, true, true, trueपूर्ण,
		/* Keep standard IFG of 12 bytes on egress. */
		.अगरg = 0,
		/* Always put the MAC speed in स्वतःmatic mode, where it can be
		 * adjusted at runसमय by PHYLINK.
		 */
		.speed = SJA1105_SPEED_AUTO,
		/* No अटल correction क्रम 1-step 1588 events */
		.tp_delin = 0,
		.tp_delout = 0,
		/* Disable aging क्रम critical TTEthernet traffic */
		.maxage = 0xFF,
		/* Internal VLAN (pvid) to apply to untagged ingress */
		.vlanprio = 0,
		.vlanid = 1,
		.ing_mirr = false,
		.egr_mirr = false,
		/* Don't drop traffic with other EtherType than ETH_P_IP */
		.drpnona664 = false,
		/* Don't drop द्विगुन-tagged traffic */
		.drpdtag = false,
		/* Don't drop untagged traffic */
		.drpuntag = false,
		/* Don't retag 802.1p (VID 0) traffic with the pvid */
		.retag = false,
		/* Disable learning and I/O on user ports by शेष -
		 * STP will enable it.
		 */
		.dyn_learn = false,
		.egress = false,
		.ingress = false,
	पूर्ण;
	काष्ठा sja1105_mac_config_entry *mac;
	काष्ठा sja1105_table *table;
	पूर्णांक i;

	table = &priv->अटल_config.tables[BLK_IDX_MAC_CONFIG];

	/* Discard previous MAC Configuration Table */
	अगर (table->entry_count) अणु
		kमुक्त(table->entries);
		table->entry_count = 0;
	पूर्ण

	table->entries = kसुस्मृति(SJA1105_NUM_PORTS,
				 table->ops->unpacked_entry_size, GFP_KERNEL);
	अगर (!table->entries)
		वापस -ENOMEM;

	table->entry_count = SJA1105_NUM_PORTS;

	mac = table->entries;

	क्रम (i = 0; i < SJA1105_NUM_PORTS; i++) अणु
		mac[i] = शेष_mac;
		अगर (i == dsa_upstream_port(priv->ds, i)) अणु
			/* STP करोesn't get called क्रम CPU port, so we need to
			 * set the I/O parameters अटलally.
			 */
			mac[i].dyn_learn = true;
			mac[i].ingress = true;
			mac[i].egress = true;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल bool sja1105_supports_sgmii(काष्ठा sja1105_निजी *priv, पूर्णांक port)
अणु
	अगर (priv->info->part_no != SJA1105R_PART_NO &&
	    priv->info->part_no != SJA1105S_PART_NO)
		वापस false;

	अगर (port != SJA1105_SGMII_PORT)
		वापस false;

	अगर (dsa_is_unused_port(priv->ds, port))
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक sja1105_init_mii_settings(काष्ठा sja1105_निजी *priv,
				     काष्ठा sja1105_dt_port *ports)
अणु
	काष्ठा device *dev = &priv->spidev->dev;
	काष्ठा sja1105_xmii_params_entry *mii;
	काष्ठा sja1105_table *table;
	पूर्णांक i;

	table = &priv->अटल_config.tables[BLK_IDX_XMII_PARAMS];

	/* Discard previous xMII Mode Parameters Table */
	अगर (table->entry_count) अणु
		kमुक्त(table->entries);
		table->entry_count = 0;
	पूर्ण

	table->entries = kसुस्मृति(SJA1105_MAX_XMII_PARAMS_COUNT,
				 table->ops->unpacked_entry_size, GFP_KERNEL);
	अगर (!table->entries)
		वापस -ENOMEM;

	/* Override table based on PHYLINK DT bindings */
	table->entry_count = SJA1105_MAX_XMII_PARAMS_COUNT;

	mii = table->entries;

	क्रम (i = 0; i < SJA1105_NUM_PORTS; i++) अणु
		अगर (dsa_is_unused_port(priv->ds, i))
			जारी;

		चयन (ports[i].phy_mode) अणु
		हाल PHY_INTERFACE_MODE_MII:
			mii->xmii_mode[i] = XMII_MODE_MII;
			अवरोध;
		हाल PHY_INTERFACE_MODE_RMII:
			mii->xmii_mode[i] = XMII_MODE_RMII;
			अवरोध;
		हाल PHY_INTERFACE_MODE_RGMII:
		हाल PHY_INTERFACE_MODE_RGMII_ID:
		हाल PHY_INTERFACE_MODE_RGMII_RXID:
		हाल PHY_INTERFACE_MODE_RGMII_TXID:
			mii->xmii_mode[i] = XMII_MODE_RGMII;
			अवरोध;
		हाल PHY_INTERFACE_MODE_SGMII:
			अगर (!sja1105_supports_sgmii(priv, i))
				वापस -EINVAL;
			mii->xmii_mode[i] = XMII_MODE_SGMII;
			अवरोध;
		शेष:
			dev_err(dev, "Unsupported PHY mode %s!\n",
				phy_modes(ports[i].phy_mode));
			वापस -EINVAL;
		पूर्ण

		/* Even though the SerDes port is able to drive SGMII स्वतःneg
		 * like a PHY would, from the perspective of the XMII tables,
		 * the SGMII port should always be put in MAC mode.
		 */
		अगर (ports[i].phy_mode == PHY_INTERFACE_MODE_SGMII)
			mii->phy_mac[i] = XMII_MAC;
		अन्यथा
			mii->phy_mac[i] = ports[i].role;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक sja1105_init_अटल_fdb(काष्ठा sja1105_निजी *priv)
अणु
	काष्ठा sja1105_l2_lookup_entry *l2_lookup;
	काष्ठा sja1105_table *table;
	पूर्णांक port;

	table = &priv->अटल_config.tables[BLK_IDX_L2_LOOKUP];

	/* We only populate the FDB table through dynamic L2 Address Lookup
	 * entries, except क्रम a special entry at the end which is a catch-all
	 * क्रम unknown multicast and will be used to control flooding करोमुख्य.
	 */
	अगर (table->entry_count) अणु
		kमुक्त(table->entries);
		table->entry_count = 0;
	पूर्ण

	अगर (!priv->info->can_limit_mcast_flood)
		वापस 0;

	table->entries = kसुस्मृति(1, table->ops->unpacked_entry_size,
				 GFP_KERNEL);
	अगर (!table->entries)
		वापस -ENOMEM;

	table->entry_count = 1;
	l2_lookup = table->entries;

	/* All L2 multicast addresses have an odd first octet */
	l2_lookup[0].macaddr = SJA1105_UNKNOWN_MULTICAST;
	l2_lookup[0].mask_macaddr = SJA1105_UNKNOWN_MULTICAST;
	l2_lookup[0].lockeds = true;
	l2_lookup[0].index = SJA1105_MAX_L2_LOOKUP_COUNT - 1;

	/* Flood multicast to every port by शेष */
	क्रम (port = 0; port < priv->ds->num_ports; port++)
		अगर (!dsa_is_unused_port(priv->ds, port))
			l2_lookup[0].destports |= BIT(port);

	वापस 0;
पूर्ण

अटल पूर्णांक sja1105_init_l2_lookup_params(काष्ठा sja1105_निजी *priv)
अणु
	काष्ठा sja1105_table *table;
	u64 max_fdb_entries = SJA1105_MAX_L2_LOOKUP_COUNT / SJA1105_NUM_PORTS;
	काष्ठा sja1105_l2_lookup_params_entry शेष_l2_lookup_params = अणु
		/* Learned FDB entries are क्रमgotten after 300 seconds */
		.maxage = SJA1105_AGEING_TIME_MS(300000),
		/* All entries within a FDB bin are available क्रम learning */
		.dyn_tbsz = SJA1105ET_FDB_BIN_SIZE,
		/* And the P/Q/R/S equivalent setting: */
		.start_dynspc = 0,
		.maxaddrp = अणुmax_fdb_entries, max_fdb_entries, max_fdb_entries,
			     max_fdb_entries, max_fdb_entries, पूर्ण,
		/* 2^8 + 2^5 + 2^3 + 2^2 + 2^1 + 1 in Koopman notation */
		.poly = 0x97,
		/* This selects between Independent VLAN Learning (IVL) and
		 * Shared VLAN Learning (SVL)
		 */
		.shared_learn = true,
		/* Don't discard management traffic based on ENFPORT -
		 * we करोn't perक्रमm SMAC port enक्रमcement anyway, so
		 * what we are setting here करोesn't matter.
		 */
		.no_enf_hostprt = false,
		/* Don't learn SMAC क्रम mac_fltres1 and mac_fltres0.
		 * Maybe correlate with no_linklocal_learn from bridge driver?
		 */
		.no_mgmt_learn = true,
		/* P/Q/R/S only */
		.use_अटल = true,
		/* Dynamically learned FDB entries can overग_लिखो other (older)
		 * dynamic FDB entries
		 */
		.owr_dyn = true,
		.drpnolearn = true,
	पूर्ण;

	table = &priv->अटल_config.tables[BLK_IDX_L2_LOOKUP_PARAMS];

	अगर (table->entry_count) अणु
		kमुक्त(table->entries);
		table->entry_count = 0;
	पूर्ण

	table->entries = kसुस्मृति(SJA1105_MAX_L2_LOOKUP_PARAMS_COUNT,
				 table->ops->unpacked_entry_size, GFP_KERNEL);
	अगर (!table->entries)
		वापस -ENOMEM;

	table->entry_count = SJA1105_MAX_L2_LOOKUP_PARAMS_COUNT;

	/* This table only has a single entry */
	((काष्ठा sja1105_l2_lookup_params_entry *)table->entries)[0] =
				शेष_l2_lookup_params;

	वापस 0;
पूर्ण

/* Set up a शेष VLAN क्रम untagged traffic injected from the CPU
 * using management routes (e.g. STP, PTP) as opposed to tag_8021q.
 * All DT-defined ports are members of this VLAN, and there are no
 * restrictions on क्रमwarding (since the CPU selects the destination).
 * Frames from this VLAN will always be transmitted as untagged, and
 * neither the bridge nor the 8021q module cannot create this VLAN ID.
 */
अटल पूर्णांक sja1105_init_अटल_vlan(काष्ठा sja1105_निजी *priv)
अणु
	काष्ठा sja1105_table *table;
	काष्ठा sja1105_vlan_lookup_entry pvid = अणु
		.ving_mirr = 0,
		.vegr_mirr = 0,
		.vmemb_port = 0,
		.vlan_bc = 0,
		.tag_port = 0,
		.vlanid = SJA1105_DEFAULT_VLAN,
	पूर्ण;
	काष्ठा dsa_चयन *ds = priv->ds;
	पूर्णांक port;

	table = &priv->अटल_config.tables[BLK_IDX_VLAN_LOOKUP];

	अगर (table->entry_count) अणु
		kमुक्त(table->entries);
		table->entry_count = 0;
	पूर्ण

	table->entries = kzalloc(table->ops->unpacked_entry_size,
				 GFP_KERNEL);
	अगर (!table->entries)
		वापस -ENOMEM;

	table->entry_count = 1;

	क्रम (port = 0; port < ds->num_ports; port++) अणु
		काष्ठा sja1105_bridge_vlan *v;

		अगर (dsa_is_unused_port(ds, port))
			जारी;

		pvid.vmemb_port |= BIT(port);
		pvid.vlan_bc |= BIT(port);
		pvid.tag_port &= ~BIT(port);

		v = kzalloc(माप(*v), GFP_KERNEL);
		अगर (!v)
			वापस -ENOMEM;

		v->port = port;
		v->vid = SJA1105_DEFAULT_VLAN;
		v->untagged = true;
		अगर (dsa_is_cpu_port(ds, port))
			v->pvid = true;
		list_add(&v->list, &priv->dsa_8021q_vlans);
	पूर्ण

	((काष्ठा sja1105_vlan_lookup_entry *)table->entries)[0] = pvid;
	वापस 0;
पूर्ण

अटल पूर्णांक sja1105_init_l2_क्रमwarding(काष्ठा sja1105_निजी *priv)
अणु
	काष्ठा sja1105_l2_क्रमwarding_entry *l2fwd;
	काष्ठा sja1105_table *table;
	पूर्णांक i, j;

	table = &priv->अटल_config.tables[BLK_IDX_L2_FORWARDING];

	अगर (table->entry_count) अणु
		kमुक्त(table->entries);
		table->entry_count = 0;
	पूर्ण

	table->entries = kसुस्मृति(SJA1105_MAX_L2_FORWARDING_COUNT,
				 table->ops->unpacked_entry_size, GFP_KERNEL);
	अगर (!table->entries)
		वापस -ENOMEM;

	table->entry_count = SJA1105_MAX_L2_FORWARDING_COUNT;

	l2fwd = table->entries;

	/* First 5 entries define the क्रमwarding rules */
	क्रम (i = 0; i < SJA1105_NUM_PORTS; i++) अणु
		अचिन्हित पूर्णांक upstream = dsa_upstream_port(priv->ds, i);

		क्रम (j = 0; j < SJA1105_NUM_TC; j++)
			l2fwd[i].vlan_pmap[j] = j;

		/* All ports start up with egress flooding enabled,
		 * including the CPU port.
		 */
		priv->ucast_egress_floods |= BIT(i);
		priv->bcast_egress_floods |= BIT(i);

		अगर (i == upstream)
			जारी;

		sja1105_port_allow_traffic(l2fwd, i, upstream, true);
		sja1105_port_allow_traffic(l2fwd, upstream, i, true);

		l2fwd[i].bc_करोमुख्य = BIT(upstream);
		l2fwd[i].fl_करोमुख्य = BIT(upstream);

		l2fwd[upstream].bc_करोमुख्य |= BIT(i);
		l2fwd[upstream].fl_करोमुख्य |= BIT(i);
	पूर्ण
	/* Next 8 entries define VLAN PCP mapping from ingress to egress.
	 * Create a one-to-one mapping.
	 */
	क्रम (i = 0; i < SJA1105_NUM_TC; i++)
		क्रम (j = 0; j < SJA1105_NUM_PORTS; j++)
			l2fwd[SJA1105_NUM_PORTS + i].vlan_pmap[j] = i;

	वापस 0;
पूर्ण

अटल पूर्णांक sja1105_init_l2_क्रमwarding_params(काष्ठा sja1105_निजी *priv)
अणु
	काष्ठा sja1105_l2_क्रमwarding_params_entry शेष_l2fwd_params = अणु
		/* Disallow dynamic reconfiguration of vlan_pmap */
		.max_dynp = 0,
		/* Use a single memory partition क्रम all ingress queues */
		.part_spc = अणु SJA1105_MAX_FRAME_MEMORY, 0, 0, 0, 0, 0, 0, 0 पूर्ण,
	पूर्ण;
	काष्ठा sja1105_table *table;

	table = &priv->अटल_config.tables[BLK_IDX_L2_FORWARDING_PARAMS];

	अगर (table->entry_count) अणु
		kमुक्त(table->entries);
		table->entry_count = 0;
	पूर्ण

	table->entries = kसुस्मृति(SJA1105_MAX_L2_FORWARDING_PARAMS_COUNT,
				 table->ops->unpacked_entry_size, GFP_KERNEL);
	अगर (!table->entries)
		वापस -ENOMEM;

	table->entry_count = SJA1105_MAX_L2_FORWARDING_PARAMS_COUNT;

	/* This table only has a single entry */
	((काष्ठा sja1105_l2_क्रमwarding_params_entry *)table->entries)[0] =
				शेष_l2fwd_params;

	वापस 0;
पूर्ण

व्योम sja1105_frame_memory_partitioning(काष्ठा sja1105_निजी *priv)
अणु
	काष्ठा sja1105_l2_क्रमwarding_params_entry *l2_fwd_params;
	काष्ठा sja1105_vl_क्रमwarding_params_entry *vl_fwd_params;
	काष्ठा sja1105_table *table;
	पूर्णांक max_mem;

	/* VLAN retagging is implemented using a loopback port that consumes
	 * frame buffers. That leaves less क्रम us.
	 */
	अगर (priv->vlan_state == SJA1105_VLAN_BEST_EFFORT)
		max_mem = SJA1105_MAX_FRAME_MEMORY_RETAGGING;
	अन्यथा
		max_mem = SJA1105_MAX_FRAME_MEMORY;

	table = &priv->अटल_config.tables[BLK_IDX_L2_FORWARDING_PARAMS];
	l2_fwd_params = table->entries;
	l2_fwd_params->part_spc[0] = max_mem;

	/* If we have any critical-traffic भव links, we need to reserve
	 * some frame buffer memory क्रम them. At the moment, hardcode the value
	 * at 100 blocks of 128 bytes of memory each. This leaves 829 blocks
	 * reमुख्यing क्रम best-efक्रमt traffic. TODO: figure out a more flexible
	 * way to perक्रमm the frame buffer partitioning.
	 */
	अगर (!priv->अटल_config.tables[BLK_IDX_VL_FORWARDING].entry_count)
		वापस;

	table = &priv->अटल_config.tables[BLK_IDX_VL_FORWARDING_PARAMS];
	vl_fwd_params = table->entries;

	l2_fwd_params->part_spc[0] -= SJA1105_VL_FRAME_MEMORY;
	vl_fwd_params->partspc[0] = SJA1105_VL_FRAME_MEMORY;
पूर्ण

अटल पूर्णांक sja1105_init_general_params(काष्ठा sja1105_निजी *priv)
अणु
	काष्ठा sja1105_general_params_entry शेष_general_params = अणु
		/* Allow dynamic changing of the mirror port */
		.mirr_ptacu = true,
		.चयनid = priv->ds->index,
		/* Priority queue क्रम link-local management frames
		 * (both ingress to and egress from CPU - PTP, STP etc)
		 */
		.hostprio = 7,
		.mac_fltres1 = SJA1105_LINKLOCAL_FILTER_A,
		.mac_flt1    = SJA1105_LINKLOCAL_FILTER_A_MASK,
		.incl_srcpt1 = false,
		.send_meta1  = false,
		.mac_fltres0 = SJA1105_LINKLOCAL_FILTER_B,
		.mac_flt0    = SJA1105_LINKLOCAL_FILTER_B_MASK,
		.incl_srcpt0 = false,
		.send_meta0  = false,
		/* The destination क्रम traffic matching mac_fltres1 and
		 * mac_fltres0 on all ports except host_port. Such traffic
		 * receieved on host_port itself would be dropped, except
		 * by installing a temporary 'management route'
		 */
		.host_port = dsa_upstream_port(priv->ds, 0),
		/* Default to an invalid value */
		.mirr_port = SJA1105_NUM_PORTS,
		/* Link-local traffic received on casc_port will be क्रमwarded
		 * to host_port without embedding the source port and device ID
		 * info in the destination MAC address (presumably because it
		 * is a cascaded port and a करोwnstream SJA चयन alपढ़ोy did
		 * that). Default to an invalid port (to disable the feature)
		 * and overग_लिखो this अगर we find any DSA (cascaded) ports.
		 */
		.casc_port = SJA1105_NUM_PORTS,
		/* No TTEthernet */
		.vllupक्रमmat = SJA1105_VL_FORMAT_PSFP,
		.vlmarker = 0,
		.vlmask = 0,
		/* Only update correctionField क्रम 1-step PTP (L2 transport) */
		.ignore2stf = 0,
		/* Forcefully disable VLAN filtering by telling
		 * the चयन that VLAN has a dअगरferent EtherType.
		 */
		.tpid = ETH_P_SJA1105,
		.tpid2 = ETH_P_SJA1105,
	पूर्ण;
	काष्ठा sja1105_table *table;

	table = &priv->अटल_config.tables[BLK_IDX_GENERAL_PARAMS];

	अगर (table->entry_count) अणु
		kमुक्त(table->entries);
		table->entry_count = 0;
	पूर्ण

	table->entries = kसुस्मृति(SJA1105_MAX_GENERAL_PARAMS_COUNT,
				 table->ops->unpacked_entry_size, GFP_KERNEL);
	अगर (!table->entries)
		वापस -ENOMEM;

	table->entry_count = SJA1105_MAX_GENERAL_PARAMS_COUNT;

	/* This table only has a single entry */
	((काष्ठा sja1105_general_params_entry *)table->entries)[0] =
				शेष_general_params;

	वापस 0;
पूर्ण

अटल पूर्णांक sja1105_init_avb_params(काष्ठा sja1105_निजी *priv)
अणु
	काष्ठा sja1105_avb_params_entry *avb;
	काष्ठा sja1105_table *table;

	table = &priv->अटल_config.tables[BLK_IDX_AVB_PARAMS];

	/* Discard previous AVB Parameters Table */
	अगर (table->entry_count) अणु
		kमुक्त(table->entries);
		table->entry_count = 0;
	पूर्ण

	table->entries = kसुस्मृति(SJA1105_MAX_AVB_PARAMS_COUNT,
				 table->ops->unpacked_entry_size, GFP_KERNEL);
	अगर (!table->entries)
		वापस -ENOMEM;

	table->entry_count = SJA1105_MAX_AVB_PARAMS_COUNT;

	avb = table->entries;

	/* Configure the MAC addresses क्रम meta frames */
	avb->desपंचांगeta = SJA1105_META_DMAC;
	avb->srcmeta  = SJA1105_META_SMAC;
	/* On P/Q/R/S, configure the direction of the PTP_CLK pin as input by
	 * शेष. This is because there might be boards with a hardware
	 * layout where enabling the pin as output might cause an electrical
	 * clash. On E/T the pin is always an output, which the board designers
	 * probably alपढ़ोy knew, so even अगर there are going to be electrical
	 * issues, there's nothing we can करो.
	 */
	avb->cas_master = false;

	वापस 0;
पूर्ण

/* The L2 policing table is 2-stage. The table is looked up क्रम each frame
 * according to the ingress port, whether it was broadcast or not, and the
 * classअगरied traffic class (given by VLAN PCP). This portion of the lookup is
 * fixed, and gives access to the SHARINDX, an indirection रेजिस्टर poपूर्णांकing
 * within the policing table itself, which is used to resolve the policer that
 * will be used क्रम this frame.
 *
 *  Stage 1                              Stage 2
 * +------------+--------+              +---------------------------------+
 * |Port 0 TC 0 |SHARINDX|              | Policer 0: Rate, Burst, MTU     |
 * +------------+--------+              +---------------------------------+
 * |Port 0 TC 1 |SHARINDX|              | Policer 1: Rate, Burst, MTU     |
 * +------------+--------+              +---------------------------------+
 *    ...                               | Policer 2: Rate, Burst, MTU     |
 * +------------+--------+              +---------------------------------+
 * |Port 0 TC 7 |SHARINDX|              | Policer 3: Rate, Burst, MTU     |
 * +------------+--------+              +---------------------------------+
 * |Port 1 TC 0 |SHARINDX|              | Policer 4: Rate, Burst, MTU     |
 * +------------+--------+              +---------------------------------+
 *    ...                               | Policer 5: Rate, Burst, MTU     |
 * +------------+--------+              +---------------------------------+
 * |Port 1 TC 7 |SHARINDX|              | Policer 6: Rate, Burst, MTU     |
 * +------------+--------+              +---------------------------------+
 *    ...                               | Policer 7: Rate, Burst, MTU     |
 * +------------+--------+              +---------------------------------+
 * |Port 4 TC 7 |SHARINDX|                 ...
 * +------------+--------+
 * |Port 0 BCAST|SHARINDX|                 ...
 * +------------+--------+
 * |Port 1 BCAST|SHARINDX|                 ...
 * +------------+--------+
 *    ...                                  ...
 * +------------+--------+              +---------------------------------+
 * |Port 4 BCAST|SHARINDX|              | Policer 44: Rate, Burst, MTU    |
 * +------------+--------+              +---------------------------------+
 *
 * In this driver, we shall use policers 0-4 as अटलally alocated port
 * (matchall) policers. So we need to make the SHARINDX क्रम all lookups
 * corresponding to this ingress port (8 VLAN PCP lookups and 1 broadcast
 * lookup) equal.
 * The reमुख्यing policers (40) shall be dynamically allocated क्रम flower
 * policers, where the key is either vlan_prio or dst_mac ff:ff:ff:ff:ff:ff.
 */
#घोषणा SJA1105_RATE_MBPS(speed) (((speed) * 64000) / 1000)

अटल पूर्णांक sja1105_init_l2_policing(काष्ठा sja1105_निजी *priv)
अणु
	काष्ठा sja1105_l2_policing_entry *policing;
	काष्ठा sja1105_table *table;
	पूर्णांक port, tc;

	table = &priv->अटल_config.tables[BLK_IDX_L2_POLICING];

	/* Discard previous L2 Policing Table */
	अगर (table->entry_count) अणु
		kमुक्त(table->entries);
		table->entry_count = 0;
	पूर्ण

	table->entries = kसुस्मृति(SJA1105_MAX_L2_POLICING_COUNT,
				 table->ops->unpacked_entry_size, GFP_KERNEL);
	अगर (!table->entries)
		वापस -ENOMEM;

	table->entry_count = SJA1105_MAX_L2_POLICING_COUNT;

	policing = table->entries;

	/* Setup shared indices क्रम the matchall policers */
	क्रम (port = 0; port < SJA1105_NUM_PORTS; port++) अणु
		पूर्णांक bcast = (SJA1105_NUM_PORTS * SJA1105_NUM_TC) + port;

		क्रम (tc = 0; tc < SJA1105_NUM_TC; tc++)
			policing[port * SJA1105_NUM_TC + tc].sharindx = port;

		policing[bcast].sharindx = port;
	पूर्ण

	/* Setup the matchall policer parameters */
	क्रम (port = 0; port < SJA1105_NUM_PORTS; port++) अणु
		पूर्णांक mtu = VLAN_ETH_FRAME_LEN + ETH_FCS_LEN;

		अगर (dsa_is_cpu_port(priv->ds, port))
			mtu += VLAN_HLEN;

		policing[port].smax = 65535; /* Burst size in bytes */
		policing[port].rate = SJA1105_RATE_MBPS(1000);
		policing[port].maxlen = mtu;
		policing[port].partition = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sja1105_अटल_config_load(काष्ठा sja1105_निजी *priv,
				      काष्ठा sja1105_dt_port *ports)
अणु
	पूर्णांक rc;

	sja1105_अटल_config_मुक्त(&priv->अटल_config);
	rc = sja1105_अटल_config_init(&priv->अटल_config,
					priv->info->अटल_ops,
					priv->info->device_id);
	अगर (rc)
		वापस rc;

	/* Build अटल configuration */
	rc = sja1105_init_mac_settings(priv);
	अगर (rc < 0)
		वापस rc;
	rc = sja1105_init_mii_settings(priv, ports);
	अगर (rc < 0)
		वापस rc;
	rc = sja1105_init_अटल_fdb(priv);
	अगर (rc < 0)
		वापस rc;
	rc = sja1105_init_अटल_vlan(priv);
	अगर (rc < 0)
		वापस rc;
	rc = sja1105_init_l2_lookup_params(priv);
	अगर (rc < 0)
		वापस rc;
	rc = sja1105_init_l2_क्रमwarding(priv);
	अगर (rc < 0)
		वापस rc;
	rc = sja1105_init_l2_क्रमwarding_params(priv);
	अगर (rc < 0)
		वापस rc;
	rc = sja1105_init_l2_policing(priv);
	अगर (rc < 0)
		वापस rc;
	rc = sja1105_init_general_params(priv);
	अगर (rc < 0)
		वापस rc;
	rc = sja1105_init_avb_params(priv);
	अगर (rc < 0)
		वापस rc;

	/* Send initial configuration to hardware via SPI */
	वापस sja1105_अटल_config_upload(priv);
पूर्ण

अटल पूर्णांक sja1105_parse_rgmii_delays(काष्ठा sja1105_निजी *priv,
				      स्थिर काष्ठा sja1105_dt_port *ports)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < SJA1105_NUM_PORTS; i++) अणु
		अगर (ports[i].role == XMII_MAC)
			जारी;

		अगर (ports[i].phy_mode == PHY_INTERFACE_MODE_RGMII_RXID ||
		    ports[i].phy_mode == PHY_INTERFACE_MODE_RGMII_ID)
			priv->rgmii_rx_delay[i] = true;

		अगर (ports[i].phy_mode == PHY_INTERFACE_MODE_RGMII_TXID ||
		    ports[i].phy_mode == PHY_INTERFACE_MODE_RGMII_ID)
			priv->rgmii_tx_delay[i] = true;

		अगर ((priv->rgmii_rx_delay[i] || priv->rgmii_tx_delay[i]) &&
		     !priv->info->setup_rgmii_delay)
			वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक sja1105_parse_ports_node(काष्ठा sja1105_निजी *priv,
				    काष्ठा sja1105_dt_port *ports,
				    काष्ठा device_node *ports_node)
अणु
	काष्ठा device *dev = &priv->spidev->dev;
	काष्ठा device_node *child;

	क्रम_each_available_child_of_node(ports_node, child) अणु
		काष्ठा device_node *phy_node;
		phy_पूर्णांकerface_t phy_mode;
		u32 index;
		पूर्णांक err;

		/* Get चयन port number from DT */
		अगर (of_property_पढ़ो_u32(child, "reg", &index) < 0) अणु
			dev_err(dev, "Port number not defined in device tree "
				"(property \"reg\")\n");
			of_node_put(child);
			वापस -ENODEV;
		पूर्ण

		/* Get PHY mode from DT */
		err = of_get_phy_mode(child, &phy_mode);
		अगर (err) अणु
			dev_err(dev, "Failed to read phy-mode or "
				"phy-interface-type property for port %d\n",
				index);
			of_node_put(child);
			वापस -ENODEV;
		पूर्ण
		ports[index].phy_mode = phy_mode;

		phy_node = of_parse_phandle(child, "phy-handle", 0);
		अगर (!phy_node) अणु
			अगर (!of_phy_is_fixed_link(child)) अणु
				dev_err(dev, "phy-handle or fixed-link "
					"properties missing!\n");
				of_node_put(child);
				वापस -ENODEV;
			पूर्ण
			/* phy-handle is missing, but fixed-link isn't.
			 * So it's a fixed link. Default to PHY role.
			 */
			ports[index].role = XMII_PHY;
		पूर्ण अन्यथा अणु
			/* phy-handle present => put port in MAC role */
			ports[index].role = XMII_MAC;
			of_node_put(phy_node);
		पूर्ण

		/* The MAC/PHY role can be overridden with explicit bindings */
		अगर (of_property_पढ़ो_bool(child, "sja1105,role-mac"))
			ports[index].role = XMII_MAC;
		अन्यथा अगर (of_property_पढ़ो_bool(child, "sja1105,role-phy"))
			ports[index].role = XMII_PHY;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sja1105_parse_dt(काष्ठा sja1105_निजी *priv,
			    काष्ठा sja1105_dt_port *ports)
अणु
	काष्ठा device *dev = &priv->spidev->dev;
	काष्ठा device_node *चयन_node = dev->of_node;
	काष्ठा device_node *ports_node;
	पूर्णांक rc;

	ports_node = of_get_child_by_name(चयन_node, "ports");
	अगर (!ports_node) अणु
		dev_err(dev, "Incorrect bindings: absent \"ports\" node\n");
		वापस -ENODEV;
	पूर्ण

	rc = sja1105_parse_ports_node(priv, ports, ports_node);
	of_node_put(ports_node);

	वापस rc;
पूर्ण

अटल पूर्णांक sja1105_sgmii_पढ़ो(काष्ठा sja1105_निजी *priv, पूर्णांक pcs_reg)
अणु
	स्थिर काष्ठा sja1105_regs *regs = priv->info->regs;
	u32 val;
	पूर्णांक rc;

	rc = sja1105_xfer_u32(priv, SPI_READ, regs->sgmii + pcs_reg, &val,
			      शून्य);
	अगर (rc < 0)
		वापस rc;

	वापस val;
पूर्ण

अटल पूर्णांक sja1105_sgmii_ग_लिखो(काष्ठा sja1105_निजी *priv, पूर्णांक pcs_reg,
			       u16 pcs_val)
अणु
	स्थिर काष्ठा sja1105_regs *regs = priv->info->regs;
	u32 val = pcs_val;
	पूर्णांक rc;

	rc = sja1105_xfer_u32(priv, SPI_WRITE, regs->sgmii + pcs_reg, &val,
			      शून्य);
	अगर (rc < 0)
		वापस rc;

	वापस val;
पूर्ण

अटल व्योम sja1105_sgmii_pcs_config(काष्ठा sja1105_निजी *priv,
				     bool an_enabled, bool an_master)
अणु
	u16 ac = SJA1105_AC_AUTONEG_MODE_SGMII;

	/* DIGITAL_CONTROL_1: Enable venकरोr-specअगरic MMD1, allow the PHY to
	 * stop the घड़ी during LPI mode, make the MAC reconfigure
	 * स्वतःnomously after PCS स्वतःneg is करोne, flush the पूर्णांकernal FIFOs.
	 */
	sja1105_sgmii_ग_लिखो(priv, SJA1105_DC1, SJA1105_DC1_EN_VSMMD1 |
					       SJA1105_DC1_CLOCK_STOP_EN |
					       SJA1105_DC1_MAC_AUTO_SW |
					       SJA1105_DC1_INIT);
	/* DIGITAL_CONTROL_2: No polarity inversion क्रम TX and RX lanes */
	sja1105_sgmii_ग_लिखो(priv, SJA1105_DC2, SJA1105_DC2_TX_POL_INV_DISABLE);
	/* AUTONEG_CONTROL: Use SGMII स्वतःneg */
	अगर (an_master)
		ac |= SJA1105_AC_PHY_MODE | SJA1105_AC_SGMII_LINK;
	sja1105_sgmii_ग_लिखो(priv, SJA1105_AC, ac);
	/* BASIC_CONTROL: enable in-band AN now, अगर requested. Otherwise,
	 * sja1105_sgmii_pcs_क्रमce_speed must be called later क्रम the link
	 * to become operational.
	 */
	अगर (an_enabled)
		sja1105_sgmii_ग_लिखो(priv, MII_BMCR,
				    BMCR_ANENABLE | BMCR_ANRESTART);
पूर्ण

अटल व्योम sja1105_sgmii_pcs_क्रमce_speed(काष्ठा sja1105_निजी *priv,
					  पूर्णांक speed)
अणु
	पूर्णांक pcs_speed;

	चयन (speed) अणु
	हाल SPEED_1000:
		pcs_speed = BMCR_SPEED1000;
		अवरोध;
	हाल SPEED_100:
		pcs_speed = BMCR_SPEED100;
		अवरोध;
	हाल SPEED_10:
		pcs_speed = BMCR_SPEED10;
		अवरोध;
	शेष:
		dev_err(priv->ds->dev, "Invalid speed %d\n", speed);
		वापस;
	पूर्ण
	sja1105_sgmii_ग_लिखो(priv, MII_BMCR, pcs_speed | BMCR_FULLDPLX);
पूर्ण

/* Convert link speed from SJA1105 to ethtool encoding */
अटल पूर्णांक sja1105_speed[] = अणु
	[SJA1105_SPEED_AUTO]		= SPEED_UNKNOWN,
	[SJA1105_SPEED_10MBPS]		= SPEED_10,
	[SJA1105_SPEED_100MBPS]		= SPEED_100,
	[SJA1105_SPEED_1000MBPS]	= SPEED_1000,
पूर्ण;

/* Set link speed in the MAC configuration क्रम a specअगरic port. */
अटल पूर्णांक sja1105_adjust_port_config(काष्ठा sja1105_निजी *priv, पूर्णांक port,
				      पूर्णांक speed_mbps)
अणु
	काष्ठा sja1105_xmii_params_entry *mii;
	काष्ठा sja1105_mac_config_entry *mac;
	काष्ठा device *dev = priv->ds->dev;
	sja1105_phy_पूर्णांकerface_t phy_mode;
	sja1105_speed_t speed;
	पूर्णांक rc;

	/* On P/Q/R/S, one can पढ़ो from the device via the MAC reconfiguration
	 * tables. On E/T, MAC reconfig tables are not पढ़ोable, only writable.
	 * We have to *know* what the MAC looks like.  For the sake of keeping
	 * the code common, we'll use the अटल configuration tables as a
	 * reasonable approximation क्रम both E/T and P/Q/R/S.
	 */
	mac = priv->अटल_config.tables[BLK_IDX_MAC_CONFIG].entries;
	mii = priv->अटल_config.tables[BLK_IDX_XMII_PARAMS].entries;

	चयन (speed_mbps) अणु
	हाल SPEED_UNKNOWN:
		/* PHYLINK called sja1105_mac_config() to inक्रमm us about
		 * the state->पूर्णांकerface, but AN has not completed and the
		 * speed is not yet valid. UM10944.pdf says that setting
		 * SJA1105_SPEED_AUTO at runसमय disables the port, so that is
		 * ok क्रम घातer consumption in हाल AN will never complete -
		 * otherwise PHYLINK should come back with a new update.
		 */
		speed = SJA1105_SPEED_AUTO;
		अवरोध;
	हाल SPEED_10:
		speed = SJA1105_SPEED_10MBPS;
		अवरोध;
	हाल SPEED_100:
		speed = SJA1105_SPEED_100MBPS;
		अवरोध;
	हाल SPEED_1000:
		speed = SJA1105_SPEED_1000MBPS;
		अवरोध;
	शेष:
		dev_err(dev, "Invalid speed %iMbps\n", speed_mbps);
		वापस -EINVAL;
	पूर्ण

	/* Overग_लिखो SJA1105_SPEED_AUTO from the अटल MAC configuration
	 * table, since this will be used क्रम the घड़ीing setup, and we no
	 * दीर्घer need to store it in the अटल config (alपढ़ोy told hardware
	 * we want स्वतः during upload phase).
	 * Actually क्रम the SGMII port, the MAC is fixed at 1 Gbps and
	 * we need to configure the PCS only (अगर even that).
	 */
	अगर (sja1105_supports_sgmii(priv, port))
		mac[port].speed = SJA1105_SPEED_1000MBPS;
	अन्यथा
		mac[port].speed = speed;

	/* Write to the dynamic reconfiguration tables */
	rc = sja1105_dynamic_config_ग_लिखो(priv, BLK_IDX_MAC_CONFIG, port,
					  &mac[port], true);
	अगर (rc < 0) अणु
		dev_err(dev, "Failed to write MAC config: %d\n", rc);
		वापस rc;
	पूर्ण

	/* Reconfigure the PLLs क्रम the RGMII पूर्णांकerfaces (required 125 MHz at
	 * gigabit, 25 MHz at 100 Mbps and 2.5 MHz at 10 Mbps). For MII and
	 * RMII no change of the घड़ी setup is required. Actually, changing
	 * the घड़ी setup करोes पूर्णांकerrupt the घड़ी संकेत क्रम a certain समय
	 * which causes trouble क्रम all PHYs relying on this संकेत.
	 */
	phy_mode = mii->xmii_mode[port];
	अगर (phy_mode != XMII_MODE_RGMII)
		वापस 0;

	वापस sja1105_घड़ीing_setup_port(priv, port);
पूर्ण

/* The SJA1105 MAC programming model is through the अटल config (the xMII
 * Mode table cannot be dynamically reconfigured), and we have to program
 * that early (earlier than PHYLINK calls us, anyway).
 * So just error out in हाल the connected PHY attempts to change the initial
 * प्रणाली पूर्णांकerface MII protocol from what is defined in the DT, at least क्रम
 * now.
 */
अटल bool sja1105_phy_mode_mismatch(काष्ठा sja1105_निजी *priv, पूर्णांक port,
				      phy_पूर्णांकerface_t पूर्णांकerface)
अणु
	काष्ठा sja1105_xmii_params_entry *mii;
	sja1105_phy_पूर्णांकerface_t phy_mode;

	mii = priv->अटल_config.tables[BLK_IDX_XMII_PARAMS].entries;
	phy_mode = mii->xmii_mode[port];

	चयन (पूर्णांकerface) अणु
	हाल PHY_INTERFACE_MODE_MII:
		वापस (phy_mode != XMII_MODE_MII);
	हाल PHY_INTERFACE_MODE_RMII:
		वापस (phy_mode != XMII_MODE_RMII);
	हाल PHY_INTERFACE_MODE_RGMII:
	हाल PHY_INTERFACE_MODE_RGMII_ID:
	हाल PHY_INTERFACE_MODE_RGMII_RXID:
	हाल PHY_INTERFACE_MODE_RGMII_TXID:
		वापस (phy_mode != XMII_MODE_RGMII);
	हाल PHY_INTERFACE_MODE_SGMII:
		वापस (phy_mode != XMII_MODE_SGMII);
	शेष:
		वापस true;
	पूर्ण
पूर्ण

अटल व्योम sja1105_mac_config(काष्ठा dsa_चयन *ds, पूर्णांक port,
			       अचिन्हित पूर्णांक mode,
			       स्थिर काष्ठा phylink_link_state *state)
अणु
	काष्ठा sja1105_निजी *priv = ds->priv;
	bool is_sgmii = sja1105_supports_sgmii(priv, port);

	अगर (sja1105_phy_mode_mismatch(priv, port, state->पूर्णांकerface)) अणु
		dev_err(ds->dev, "Changing PHY mode to %s not supported!\n",
			phy_modes(state->पूर्णांकerface));
		वापस;
	पूर्ण

	अगर (phylink_स्वतःneg_inband(mode) && !is_sgmii) अणु
		dev_err(ds->dev, "In-band AN not supported!\n");
		वापस;
	पूर्ण

	अगर (is_sgmii)
		sja1105_sgmii_pcs_config(priv, phylink_स्वतःneg_inband(mode),
					 false);
पूर्ण

अटल व्योम sja1105_mac_link_करोwn(काष्ठा dsa_चयन *ds, पूर्णांक port,
				  अचिन्हित पूर्णांक mode,
				  phy_पूर्णांकerface_t पूर्णांकerface)
अणु
	sja1105_inhibit_tx(ds->priv, BIT(port), true);
पूर्ण

अटल व्योम sja1105_mac_link_up(काष्ठा dsa_चयन *ds, पूर्णांक port,
				अचिन्हित पूर्णांक mode,
				phy_पूर्णांकerface_t पूर्णांकerface,
				काष्ठा phy_device *phydev,
				पूर्णांक speed, पूर्णांक duplex,
				bool tx_छोड़ो, bool rx_छोड़ो)
अणु
	काष्ठा sja1105_निजी *priv = ds->priv;

	sja1105_adjust_port_config(priv, port, speed);

	अगर (sja1105_supports_sgmii(priv, port) && !phylink_स्वतःneg_inband(mode))
		sja1105_sgmii_pcs_क्रमce_speed(priv, speed);

	sja1105_inhibit_tx(priv, BIT(port), false);
पूर्ण

अटल व्योम sja1105_phylink_validate(काष्ठा dsa_चयन *ds, पूर्णांक port,
				     अचिन्हित दीर्घ *supported,
				     काष्ठा phylink_link_state *state)
अणु
	/* Conकाष्ठा a new mask which exhaustively contains all link features
	 * supported by the MAC, and then apply that (logical AND) to what will
	 * be sent to the PHY क्रम "marketing".
	 */
	__ETHTOOL_DECLARE_LINK_MODE_MASK(mask) = अणु 0, पूर्ण;
	काष्ठा sja1105_निजी *priv = ds->priv;
	काष्ठा sja1105_xmii_params_entry *mii;

	mii = priv->अटल_config.tables[BLK_IDX_XMII_PARAMS].entries;

	/* include/linux/phylink.h says:
	 *     When @state->पूर्णांकerface is %PHY_INTERFACE_MODE_NA, phylink
	 *     expects the MAC driver to वापस all supported link modes.
	 */
	अगर (state->पूर्णांकerface != PHY_INTERFACE_MODE_NA &&
	    sja1105_phy_mode_mismatch(priv, port, state->पूर्णांकerface)) अणु
		biपंचांगap_zero(supported, __ETHTOOL_LINK_MODE_MASK_NBITS);
		वापस;
	पूर्ण

	/* The MAC करोes not support छोड़ो frames, and also करोesn't
	 * support half-duplex traffic modes.
	 */
	phylink_set(mask, Autoneg);
	phylink_set(mask, MII);
	phylink_set(mask, 10baseT_Full);
	phylink_set(mask, 100baseT_Full);
	phylink_set(mask, 100baseT1_Full);
	अगर (mii->xmii_mode[port] == XMII_MODE_RGMII ||
	    mii->xmii_mode[port] == XMII_MODE_SGMII)
		phylink_set(mask, 1000baseT_Full);

	biपंचांगap_and(supported, supported, mask, __ETHTOOL_LINK_MODE_MASK_NBITS);
	biपंचांगap_and(state->advertising, state->advertising, mask,
		   __ETHTOOL_LINK_MODE_MASK_NBITS);
पूर्ण

अटल पूर्णांक sja1105_mac_pcs_get_state(काष्ठा dsa_चयन *ds, पूर्णांक port,
				     काष्ठा phylink_link_state *state)
अणु
	काष्ठा sja1105_निजी *priv = ds->priv;
	पूर्णांक ais;

	/* Read the venकरोr-specअगरic AUTONEG_INTR_STATUS रेजिस्टर */
	ais = sja1105_sgmii_पढ़ो(priv, SJA1105_AIS);
	अगर (ais < 0)
		वापस ais;

	चयन (SJA1105_AIS_SPEED(ais)) अणु
	हाल 0:
		state->speed = SPEED_10;
		अवरोध;
	हाल 1:
		state->speed = SPEED_100;
		अवरोध;
	हाल 2:
		state->speed = SPEED_1000;
		अवरोध;
	शेष:
		dev_err(ds->dev, "Invalid SGMII PCS speed %lu\n",
			SJA1105_AIS_SPEED(ais));
	पूर्ण
	state->duplex = SJA1105_AIS_DUPLEX_MODE(ais);
	state->an_complete = SJA1105_AIS_COMPLETE(ais);
	state->link = SJA1105_AIS_LINK_STATUS(ais);

	वापस 0;
पूर्ण

अटल पूर्णांक
sja1105_find_अटल_fdb_entry(काष्ठा sja1105_निजी *priv, पूर्णांक port,
			      स्थिर काष्ठा sja1105_l2_lookup_entry *requested)
अणु
	काष्ठा sja1105_l2_lookup_entry *l2_lookup;
	काष्ठा sja1105_table *table;
	पूर्णांक i;

	table = &priv->अटल_config.tables[BLK_IDX_L2_LOOKUP];
	l2_lookup = table->entries;

	क्रम (i = 0; i < table->entry_count; i++)
		अगर (l2_lookup[i].macaddr == requested->macaddr &&
		    l2_lookup[i].vlanid == requested->vlanid &&
		    l2_lookup[i].destports & BIT(port))
			वापस i;

	वापस -1;
पूर्ण

/* We want FDB entries added अटलally through the bridge command to persist
 * across चयन resets, which are a common thing during normal SJA1105
 * operation. So we have to back them up in the अटल configuration tables
 * and hence apply them on next अटल config upload... yay!
 */
अटल पूर्णांक
sja1105_अटल_fdb_change(काष्ठा sja1105_निजी *priv, पूर्णांक port,
			  स्थिर काष्ठा sja1105_l2_lookup_entry *requested,
			  bool keep)
अणु
	काष्ठा sja1105_l2_lookup_entry *l2_lookup;
	काष्ठा sja1105_table *table;
	पूर्णांक rc, match;

	table = &priv->अटल_config.tables[BLK_IDX_L2_LOOKUP];

	match = sja1105_find_अटल_fdb_entry(priv, port, requested);
	अगर (match < 0) अणु
		/* Can't delete a missing entry. */
		अगर (!keep)
			वापस 0;

		/* No match => new entry */
		rc = sja1105_table_resize(table, table->entry_count + 1);
		अगर (rc)
			वापस rc;

		match = table->entry_count - 1;
	पूर्ण

	/* Assign poपूर्णांकer after the resize (it may be new memory) */
	l2_lookup = table->entries;

	/* We have a match.
	 * If the job was to add this FDB entry, it's alपढ़ोy करोne (mostly
	 * anyway, since the port क्रमwarding mask may have changed, हाल in
	 * which we update it).
	 * Otherwise we have to delete it.
	 */
	अगर (keep) अणु
		l2_lookup[match] = *requested;
		वापस 0;
	पूर्ण

	/* To हटाओ, the strategy is to overग_लिखो the element with
	 * the last one, and then reduce the array size by 1
	 */
	l2_lookup[match] = l2_lookup[table->entry_count - 1];
	वापस sja1105_table_resize(table, table->entry_count - 1);
पूर्ण

/* First-generation चयनes have a 4-way set associative TCAM that
 * holds the FDB entries. An FDB index spans from 0 to 1023 and is comprised of
 * a "bin" (grouping of 4 entries) and a "way" (an entry within a bin).
 * For the placement of a newly learnt FDB entry, the चयन selects the bin
 * based on a hash function, and the way within that bin incrementally.
 */
अटल पूर्णांक sja1105et_fdb_index(पूर्णांक bin, पूर्णांक way)
अणु
	वापस bin * SJA1105ET_FDB_BIN_SIZE + way;
पूर्ण

अटल पूर्णांक sja1105et_is_fdb_entry_in_bin(काष्ठा sja1105_निजी *priv, पूर्णांक bin,
					 स्थिर u8 *addr, u16 vid,
					 काष्ठा sja1105_l2_lookup_entry *match,
					 पूर्णांक *last_unused)
अणु
	पूर्णांक way;

	क्रम (way = 0; way < SJA1105ET_FDB_BIN_SIZE; way++) अणु
		काष्ठा sja1105_l2_lookup_entry l2_lookup = अणु0पूर्ण;
		पूर्णांक index = sja1105et_fdb_index(bin, way);

		/* Skip unused entries, optionally marking them
		 * पूर्णांकo the वापस value
		 */
		अगर (sja1105_dynamic_config_पढ़ो(priv, BLK_IDX_L2_LOOKUP,
						index, &l2_lookup)) अणु
			अगर (last_unused)
				*last_unused = way;
			जारी;
		पूर्ण

		अगर (l2_lookup.macaddr == ether_addr_to_u64(addr) &&
		    l2_lookup.vlanid == vid) अणु
			अगर (match)
				*match = l2_lookup;
			वापस way;
		पूर्ण
	पूर्ण
	/* Return an invalid entry index अगर not found */
	वापस -1;
पूर्ण

पूर्णांक sja1105et_fdb_add(काष्ठा dsa_चयन *ds, पूर्णांक port,
		      स्थिर अचिन्हित अक्षर *addr, u16 vid)
अणु
	काष्ठा sja1105_l2_lookup_entry l2_lookup = अणु0पूर्ण;
	काष्ठा sja1105_निजी *priv = ds->priv;
	काष्ठा device *dev = ds->dev;
	पूर्णांक last_unused = -1;
	पूर्णांक bin, way, rc;

	bin = sja1105et_fdb_hash(priv, addr, vid);

	way = sja1105et_is_fdb_entry_in_bin(priv, bin, addr, vid,
					    &l2_lookup, &last_unused);
	अगर (way >= 0) अणु
		/* We have an FDB entry. Is our port in the destination
		 * mask? If yes, we need to करो nothing. If not, we need
		 * to reग_लिखो the entry by adding this port to it.
		 */
		अगर (l2_lookup.destports & BIT(port))
			वापस 0;
		l2_lookup.destports |= BIT(port);
	पूर्ण अन्यथा अणु
		पूर्णांक index = sja1105et_fdb_index(bin, way);

		/* We करोn't have an FDB entry. We स्थिरruct a new one and
		 * try to find a place क्रम it within the FDB table.
		 */
		l2_lookup.macaddr = ether_addr_to_u64(addr);
		l2_lookup.destports = BIT(port);
		l2_lookup.vlanid = vid;

		अगर (last_unused >= 0) अणु
			way = last_unused;
		पूर्ण अन्यथा अणु
			/* Bin is full, need to evict somebody.
			 * Choose victim at अक्रमom. If you get these messages
			 * often, you may need to consider changing the
			 * distribution function:
			 * अटल_config[BLK_IDX_L2_LOOKUP_PARAMS].entries->poly
			 */
			get_अक्रमom_bytes(&way, माप(u8));
			way %= SJA1105ET_FDB_BIN_SIZE;
			dev_warn(dev, "Warning, FDB bin %d full while adding entry for %pM. Evicting entry %u.\n",
				 bin, addr, way);
			/* Evict entry */
			sja1105_dynamic_config_ग_लिखो(priv, BLK_IDX_L2_LOOKUP,
						     index, शून्य, false);
		पूर्ण
	पूर्ण
	l2_lookup.index = sja1105et_fdb_index(bin, way);

	rc = sja1105_dynamic_config_ग_लिखो(priv, BLK_IDX_L2_LOOKUP,
					  l2_lookup.index, &l2_lookup,
					  true);
	अगर (rc < 0)
		वापस rc;

	वापस sja1105_अटल_fdb_change(priv, port, &l2_lookup, true);
पूर्ण

पूर्णांक sja1105et_fdb_del(काष्ठा dsa_चयन *ds, पूर्णांक port,
		      स्थिर अचिन्हित अक्षर *addr, u16 vid)
अणु
	काष्ठा sja1105_l2_lookup_entry l2_lookup = अणु0पूर्ण;
	काष्ठा sja1105_निजी *priv = ds->priv;
	पूर्णांक index, bin, way, rc;
	bool keep;

	bin = sja1105et_fdb_hash(priv, addr, vid);
	way = sja1105et_is_fdb_entry_in_bin(priv, bin, addr, vid,
					    &l2_lookup, शून्य);
	अगर (way < 0)
		वापस 0;
	index = sja1105et_fdb_index(bin, way);

	/* We have an FDB entry. Is our port in the destination mask? If yes,
	 * we need to हटाओ it. If the resulting port mask becomes empty, we
	 * need to completely evict the FDB entry.
	 * Otherwise we just ग_लिखो it back.
	 */
	l2_lookup.destports &= ~BIT(port);

	अगर (l2_lookup.destports)
		keep = true;
	अन्यथा
		keep = false;

	rc = sja1105_dynamic_config_ग_लिखो(priv, BLK_IDX_L2_LOOKUP,
					  index, &l2_lookup, keep);
	अगर (rc < 0)
		वापस rc;

	वापस sja1105_अटल_fdb_change(priv, port, &l2_lookup, keep);
पूर्ण

पूर्णांक sja1105pqrs_fdb_add(काष्ठा dsa_चयन *ds, पूर्णांक port,
			स्थिर अचिन्हित अक्षर *addr, u16 vid)
अणु
	काष्ठा sja1105_l2_lookup_entry l2_lookup = अणु0पूर्ण;
	काष्ठा sja1105_निजी *priv = ds->priv;
	पूर्णांक rc, i;

	/* Search क्रम an existing entry in the FDB table */
	l2_lookup.macaddr = ether_addr_to_u64(addr);
	l2_lookup.vlanid = vid;
	l2_lookup.iotag = SJA1105_S_TAG;
	l2_lookup.mask_macaddr = GENMASK_ULL(ETH_ALEN * 8 - 1, 0);
	अगर (priv->vlan_state != SJA1105_VLAN_UNAWARE) अणु
		l2_lookup.mask_vlanid = VLAN_VID_MASK;
		l2_lookup.mask_iotag = BIT(0);
	पूर्ण अन्यथा अणु
		l2_lookup.mask_vlanid = 0;
		l2_lookup.mask_iotag = 0;
	पूर्ण
	l2_lookup.destports = BIT(port);

	rc = sja1105_dynamic_config_पढ़ो(priv, BLK_IDX_L2_LOOKUP,
					 SJA1105_SEARCH, &l2_lookup);
	अगर (rc == 0) अणु
		/* Found and this port is alपढ़ोy in the entry's
		 * port mask => job करोne
		 */
		अगर (l2_lookup.destports & BIT(port))
			वापस 0;
		/* l2_lookup.index is populated by the चयन in हाल it
		 * found something.
		 */
		l2_lookup.destports |= BIT(port);
		जाओ skip_finding_an_index;
	पूर्ण

	/* Not found, so try to find an unused spot in the FDB.
	 * This is slightly inefficient because the strategy is knock-knock at
	 * every possible position from 0 to 1023.
	 */
	क्रम (i = 0; i < SJA1105_MAX_L2_LOOKUP_COUNT; i++) अणु
		rc = sja1105_dynamic_config_पढ़ो(priv, BLK_IDX_L2_LOOKUP,
						 i, शून्य);
		अगर (rc < 0)
			अवरोध;
	पूर्ण
	अगर (i == SJA1105_MAX_L2_LOOKUP_COUNT) अणु
		dev_err(ds->dev, "FDB is full, cannot add entry.\n");
		वापस -EINVAL;
	पूर्ण
	l2_lookup.lockeds = true;
	l2_lookup.index = i;

skip_finding_an_index:
	rc = sja1105_dynamic_config_ग_लिखो(priv, BLK_IDX_L2_LOOKUP,
					  l2_lookup.index, &l2_lookup,
					  true);
	अगर (rc < 0)
		वापस rc;

	वापस sja1105_अटल_fdb_change(priv, port, &l2_lookup, true);
पूर्ण

पूर्णांक sja1105pqrs_fdb_del(काष्ठा dsa_चयन *ds, पूर्णांक port,
			स्थिर अचिन्हित अक्षर *addr, u16 vid)
अणु
	काष्ठा sja1105_l2_lookup_entry l2_lookup = अणु0पूर्ण;
	काष्ठा sja1105_निजी *priv = ds->priv;
	bool keep;
	पूर्णांक rc;

	l2_lookup.macaddr = ether_addr_to_u64(addr);
	l2_lookup.vlanid = vid;
	l2_lookup.iotag = SJA1105_S_TAG;
	l2_lookup.mask_macaddr = GENMASK_ULL(ETH_ALEN * 8 - 1, 0);
	अगर (priv->vlan_state != SJA1105_VLAN_UNAWARE) अणु
		l2_lookup.mask_vlanid = VLAN_VID_MASK;
		l2_lookup.mask_iotag = BIT(0);
	पूर्ण अन्यथा अणु
		l2_lookup.mask_vlanid = 0;
		l2_lookup.mask_iotag = 0;
	पूर्ण
	l2_lookup.destports = BIT(port);

	rc = sja1105_dynamic_config_पढ़ो(priv, BLK_IDX_L2_LOOKUP,
					 SJA1105_SEARCH, &l2_lookup);
	अगर (rc < 0)
		वापस 0;

	l2_lookup.destports &= ~BIT(port);

	/* Decide whether we हटाओ just this port from the FDB entry,
	 * or अगर we हटाओ it completely.
	 */
	अगर (l2_lookup.destports)
		keep = true;
	अन्यथा
		keep = false;

	rc = sja1105_dynamic_config_ग_लिखो(priv, BLK_IDX_L2_LOOKUP,
					  l2_lookup.index, &l2_lookup, keep);
	अगर (rc < 0)
		वापस rc;

	वापस sja1105_अटल_fdb_change(priv, port, &l2_lookup, keep);
पूर्ण

अटल पूर्णांक sja1105_fdb_add(काष्ठा dsa_चयन *ds, पूर्णांक port,
			   स्थिर अचिन्हित अक्षर *addr, u16 vid)
अणु
	काष्ठा sja1105_निजी *priv = ds->priv;

	/* dsa_8021q is in effect when the bridge's vlan_filtering isn't,
	 * so the चयन still करोes some VLAN processing पूर्णांकernally.
	 * But Shared VLAN Learning (SVL) is also active, and it will take
	 * care of स्वतःnomous क्रमwarding between the unique pvid's of each
	 * port.  Here we just make sure that users can't add duplicate FDB
	 * entries when in this mode - the actual VID करोesn't matter except
	 * क्रम what माला_लो prपूर्णांकed in 'bridge fdb show'.  In the हाल of zero,
	 * no VID माला_लो prपूर्णांकed at all.
	 */
	अगर (priv->vlan_state != SJA1105_VLAN_FILTERING_FULL)
		vid = 0;

	वापस priv->info->fdb_add_cmd(ds, port, addr, vid);
पूर्ण

अटल पूर्णांक sja1105_fdb_del(काष्ठा dsa_चयन *ds, पूर्णांक port,
			   स्थिर अचिन्हित अक्षर *addr, u16 vid)
अणु
	काष्ठा sja1105_निजी *priv = ds->priv;

	अगर (priv->vlan_state != SJA1105_VLAN_FILTERING_FULL)
		vid = 0;

	वापस priv->info->fdb_del_cmd(ds, port, addr, vid);
पूर्ण

अटल पूर्णांक sja1105_fdb_dump(काष्ठा dsa_चयन *ds, पूर्णांक port,
			    dsa_fdb_dump_cb_t *cb, व्योम *data)
अणु
	काष्ठा sja1105_निजी *priv = ds->priv;
	काष्ठा device *dev = ds->dev;
	पूर्णांक i;

	क्रम (i = 0; i < SJA1105_MAX_L2_LOOKUP_COUNT; i++) अणु
		काष्ठा sja1105_l2_lookup_entry l2_lookup = अणु0पूर्ण;
		u8 macaddr[ETH_ALEN];
		पूर्णांक rc;

		rc = sja1105_dynamic_config_पढ़ो(priv, BLK_IDX_L2_LOOKUP,
						 i, &l2_lookup);
		/* No fdb entry at i, not an issue */
		अगर (rc == -ENOENT)
			जारी;
		अगर (rc) अणु
			dev_err(dev, "Failed to dump FDB: %d\n", rc);
			वापस rc;
		पूर्ण

		/* FDB dump callback is per port. This means we have to
		 * disregard a valid entry अगर it's not क्रम this port, even अगर
		 * only to revisit it later. This is inefficient because the
		 * 1024-sized FDB table needs to be traversed 4 बार through
		 * SPI during a 'bridge fdb show' command.
		 */
		अगर (!(l2_lookup.destports & BIT(port)))
			जारी;

		/* We need to hide the FDB entry क्रम unknown multicast */
		अगर (l2_lookup.macaddr == SJA1105_UNKNOWN_MULTICAST &&
		    l2_lookup.mask_macaddr == SJA1105_UNKNOWN_MULTICAST)
			जारी;

		u64_to_ether_addr(l2_lookup.macaddr, macaddr);

		/* We need to hide the dsa_8021q VLANs from the user. */
		अगर (priv->vlan_state == SJA1105_VLAN_UNAWARE)
			l2_lookup.vlanid = 0;
		cb(macaddr, l2_lookup.vlanid, l2_lookup.lockeds, data);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक sja1105_mdb_add(काष्ठा dsa_चयन *ds, पूर्णांक port,
			   स्थिर काष्ठा चयनdev_obj_port_mdb *mdb)
अणु
	वापस sja1105_fdb_add(ds, port, mdb->addr, mdb->vid);
पूर्ण

अटल पूर्णांक sja1105_mdb_del(काष्ठा dsa_चयन *ds, पूर्णांक port,
			   स्थिर काष्ठा चयनdev_obj_port_mdb *mdb)
अणु
	वापस sja1105_fdb_del(ds, port, mdb->addr, mdb->vid);
पूर्ण

/* Common function क्रम unicast and broadcast flood configuration.
 * Flooding is configured between each अणुingress, egressपूर्ण port pair, and since
 * the bridge's semantics are those of "egress flooding", it means we must
 * enable flooding towards this port from all ingress ports that are in the
 * same क्रमwarding करोमुख्य.
 */
अटल पूर्णांक sja1105_manage_flood_करोमुख्यs(काष्ठा sja1105_निजी *priv)
अणु
	काष्ठा sja1105_l2_क्रमwarding_entry *l2_fwd;
	काष्ठा dsa_चयन *ds = priv->ds;
	पूर्णांक from, to, rc;

	l2_fwd = priv->अटल_config.tables[BLK_IDX_L2_FORWARDING].entries;

	क्रम (from = 0; from < ds->num_ports; from++) अणु
		u64 fl_करोमुख्य = 0, bc_करोमुख्य = 0;

		क्रम (to = 0; to < priv->ds->num_ports; to++) अणु
			अगर (!sja1105_can_क्रमward(l2_fwd, from, to))
				जारी;

			अगर (priv->ucast_egress_floods & BIT(to))
				fl_करोमुख्य |= BIT(to);
			अगर (priv->bcast_egress_floods & BIT(to))
				bc_करोमुख्य |= BIT(to);
		पूर्ण

		/* Nothing changed, nothing to करो */
		अगर (l2_fwd[from].fl_करोमुख्य == fl_करोमुख्य &&
		    l2_fwd[from].bc_करोमुख्य == bc_करोमुख्य)
			जारी;

		l2_fwd[from].fl_करोमुख्य = fl_करोमुख्य;
		l2_fwd[from].bc_करोमुख्य = bc_करोमुख्य;

		rc = sja1105_dynamic_config_ग_लिखो(priv, BLK_IDX_L2_FORWARDING,
						  from, &l2_fwd[from], true);
		अगर (rc < 0)
			वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sja1105_bridge_member(काष्ठा dsa_चयन *ds, पूर्णांक port,
				 काष्ठा net_device *br, bool member)
अणु
	काष्ठा sja1105_l2_क्रमwarding_entry *l2_fwd;
	काष्ठा sja1105_निजी *priv = ds->priv;
	पूर्णांक i, rc;

	l2_fwd = priv->अटल_config.tables[BLK_IDX_L2_FORWARDING].entries;

	क्रम (i = 0; i < SJA1105_NUM_PORTS; i++) अणु
		/* Add this port to the क्रमwarding matrix of the
		 * other ports in the same bridge, and viceversa.
		 */
		अगर (!dsa_is_user_port(ds, i))
			जारी;
		/* For the ports alपढ़ोy under the bridge, only one thing needs
		 * to be करोne, and that is to add this port to their
		 * reachability करोमुख्य. So we can perक्रमm the SPI ग_लिखो क्रम
		 * them immediately. However, क्रम this port itself (the one
		 * that is new to the bridge), we need to add all other ports
		 * to its reachability करोमुख्य. So we करो that incrementally in
		 * this loop, and perक्रमm the SPI ग_लिखो only at the end, once
		 * the करोमुख्य contains all other bridge ports.
		 */
		अगर (i == port)
			जारी;
		अगर (dsa_to_port(ds, i)->bridge_dev != br)
			जारी;
		sja1105_port_allow_traffic(l2_fwd, i, port, member);
		sja1105_port_allow_traffic(l2_fwd, port, i, member);

		rc = sja1105_dynamic_config_ग_लिखो(priv, BLK_IDX_L2_FORWARDING,
						  i, &l2_fwd[i], true);
		अगर (rc < 0)
			वापस rc;
	पूर्ण

	rc = sja1105_dynamic_config_ग_लिखो(priv, BLK_IDX_L2_FORWARDING,
					  port, &l2_fwd[port], true);
	अगर (rc)
		वापस rc;

	वापस sja1105_manage_flood_करोमुख्यs(priv);
पूर्ण

अटल व्योम sja1105_bridge_stp_state_set(काष्ठा dsa_चयन *ds, पूर्णांक port,
					 u8 state)
अणु
	काष्ठा sja1105_निजी *priv = ds->priv;
	काष्ठा sja1105_mac_config_entry *mac;

	mac = priv->अटल_config.tables[BLK_IDX_MAC_CONFIG].entries;

	चयन (state) अणु
	हाल BR_STATE_DISABLED:
	हाल BR_STATE_BLOCKING:
		/* From UM10944 description of DRPDTAG (why put this there?):
		 * "Management traffic flows to the port regardless of the state
		 * of the INGRESS flag". So BPDUs are still be allowed to pass.
		 * At the moment no dअगरference between DISABLED and BLOCKING.
		 */
		mac[port].ingress   = false;
		mac[port].egress    = false;
		mac[port].dyn_learn = false;
		अवरोध;
	हाल BR_STATE_LISTENING:
		mac[port].ingress   = true;
		mac[port].egress    = false;
		mac[port].dyn_learn = false;
		अवरोध;
	हाल BR_STATE_LEARNING:
		mac[port].ingress   = true;
		mac[port].egress    = false;
		mac[port].dyn_learn = !!(priv->learn_ena & BIT(port));
		अवरोध;
	हाल BR_STATE_FORWARDING:
		mac[port].ingress   = true;
		mac[port].egress    = true;
		mac[port].dyn_learn = !!(priv->learn_ena & BIT(port));
		अवरोध;
	शेष:
		dev_err(ds->dev, "invalid STP state: %d\n", state);
		वापस;
	पूर्ण

	sja1105_dynamic_config_ग_लिखो(priv, BLK_IDX_MAC_CONFIG, port,
				     &mac[port], true);
पूर्ण

अटल पूर्णांक sja1105_bridge_join(काष्ठा dsa_चयन *ds, पूर्णांक port,
			       काष्ठा net_device *br)
अणु
	वापस sja1105_bridge_member(ds, port, br, true);
पूर्ण

अटल व्योम sja1105_bridge_leave(काष्ठा dsa_चयन *ds, पूर्णांक port,
				 काष्ठा net_device *br)
अणु
	sja1105_bridge_member(ds, port, br, false);
पूर्ण

#घोषणा BYTES_PER_KBIT (1000LL / 8)

अटल पूर्णांक sja1105_find_unused_cbs_shaper(काष्ठा sja1105_निजी *priv)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < priv->info->num_cbs_shapers; i++)
		अगर (!priv->cbs[i].idle_slope && !priv->cbs[i].send_slope)
			वापस i;

	वापस -1;
पूर्ण

अटल पूर्णांक sja1105_delete_cbs_shaper(काष्ठा sja1105_निजी *priv, पूर्णांक port,
				     पूर्णांक prio)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < priv->info->num_cbs_shapers; i++) अणु
		काष्ठा sja1105_cbs_entry *cbs = &priv->cbs[i];

		अगर (cbs->port == port && cbs->prio == prio) अणु
			स_रखो(cbs, 0, माप(*cbs));
			वापस sja1105_dynamic_config_ग_लिखो(priv, BLK_IDX_CBS,
							    i, cbs, true);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sja1105_setup_tc_cbs(काष्ठा dsa_चयन *ds, पूर्णांक port,
				काष्ठा tc_cbs_qopt_offload *offload)
अणु
	काष्ठा sja1105_निजी *priv = ds->priv;
	काष्ठा sja1105_cbs_entry *cbs;
	पूर्णांक index;

	अगर (!offload->enable)
		वापस sja1105_delete_cbs_shaper(priv, port, offload->queue);

	index = sja1105_find_unused_cbs_shaper(priv);
	अगर (index < 0)
		वापस -ENOSPC;

	cbs = &priv->cbs[index];
	cbs->port = port;
	cbs->prio = offload->queue;
	/* locredit and sendslope are negative by definition. In hardware,
	 * positive values must be provided, and the negative sign is implicit.
	 */
	cbs->credit_hi = offload->hicredit;
	cbs->credit_lo = असल(offload->locredit);
	/* User space is in kbits/sec, hardware in bytes/sec */
	cbs->idle_slope = offload->idleslope * BYTES_PER_KBIT;
	cbs->send_slope = असल(offload->sendslope * BYTES_PER_KBIT);
	/* Convert the negative values from 64-bit 2's complement
	 * to 32-bit 2's complement (क्रम the हाल of 0x80000000 whose
	 * negative is still negative).
	 */
	cbs->credit_lo &= GENMASK_ULL(31, 0);
	cbs->send_slope &= GENMASK_ULL(31, 0);

	वापस sja1105_dynamic_config_ग_लिखो(priv, BLK_IDX_CBS, index, cbs,
					    true);
पूर्ण

अटल पूर्णांक sja1105_reload_cbs(काष्ठा sja1105_निजी *priv)
अणु
	पूर्णांक rc = 0, i;

	क्रम (i = 0; i < priv->info->num_cbs_shapers; i++) अणु
		काष्ठा sja1105_cbs_entry *cbs = &priv->cbs[i];

		अगर (!cbs->idle_slope && !cbs->send_slope)
			जारी;

		rc = sja1105_dynamic_config_ग_लिखो(priv, BLK_IDX_CBS, i, cbs,
						  true);
		अगर (rc)
			अवरोध;
	पूर्ण

	वापस rc;
पूर्ण

अटल स्थिर अक्षर * स्थिर sja1105_reset_reasons[] = अणु
	[SJA1105_VLAN_FILTERING] = "VLAN filtering",
	[SJA1105_RX_HWTSTAMPING] = "RX timestamping",
	[SJA1105_AGEING_TIME] = "Ageing time",
	[SJA1105_SCHEDULING] = "Time-aware scheduling",
	[SJA1105_BEST_EFFORT_POLICING] = "Best-effort policing",
	[SJA1105_VIRTUAL_LINKS] = "Virtual links",
पूर्ण;

/* For situations where we need to change a setting at runसमय that is only
 * available through the अटल configuration, resetting the चयन in order
 * to upload the new अटल config is unaव्योमable. Back up the settings we
 * modअगरy at runसमय (currently only MAC) and restore them after uploading,
 * such that this operation is relatively seamless.
 */
पूर्णांक sja1105_अटल_config_reload(काष्ठा sja1105_निजी *priv,
				 क्रमागत sja1105_reset_reason reason)
अणु
	काष्ठा ptp_प्रणाली_बारtamp ptp_sts_beक्रमe;
	काष्ठा ptp_प्रणाली_बारtamp ptp_sts_after;
	काष्ठा sja1105_mac_config_entry *mac;
	पूर्णांक speed_mbps[SJA1105_NUM_PORTS];
	काष्ठा dsa_चयन *ds = priv->ds;
	s64 t1, t2, t3, t4;
	s64 t12, t34;
	u16 bmcr = 0;
	पूर्णांक rc, i;
	s64 now;

	mutex_lock(&priv->mgmt_lock);

	mac = priv->अटल_config.tables[BLK_IDX_MAC_CONFIG].entries;

	/* Back up the dynamic link speed changed by sja1105_adjust_port_config
	 * in order to temporarily restore it to SJA1105_SPEED_AUTO - which the
	 * चयन wants to see in the अटल config in order to allow us to
	 * change it through the dynamic पूर्णांकerface later.
	 */
	क्रम (i = 0; i < SJA1105_NUM_PORTS; i++) अणु
		speed_mbps[i] = sja1105_speed[mac[i].speed];
		mac[i].speed = SJA1105_SPEED_AUTO;
	पूर्ण

	अगर (sja1105_supports_sgmii(priv, SJA1105_SGMII_PORT))
		bmcr = sja1105_sgmii_पढ़ो(priv, MII_BMCR);

	/* No PTP operations can run right now */
	mutex_lock(&priv->ptp_data.lock);

	rc = __sja1105_ptp_समय_लोx(ds, &now, &ptp_sts_beक्रमe);
	अगर (rc < 0)
		जाओ out_unlock_ptp;

	/* Reset चयन and send updated अटल configuration */
	rc = sja1105_अटल_config_upload(priv);
	अगर (rc < 0)
		जाओ out_unlock_ptp;

	rc = __sja1105_ptp_समय_रखो(ds, 0, &ptp_sts_after);
	अगर (rc < 0)
		जाओ out_unlock_ptp;

	t1 = बारpec64_to_ns(&ptp_sts_beक्रमe.pre_ts);
	t2 = बारpec64_to_ns(&ptp_sts_beक्रमe.post_ts);
	t3 = बारpec64_to_ns(&ptp_sts_after.pre_ts);
	t4 = बारpec64_to_ns(&ptp_sts_after.post_ts);
	/* Mid poपूर्णांक, corresponds to pre-reset PTPCLKVAL */
	t12 = t1 + (t2 - t1) / 2;
	/* Mid poपूर्णांक, corresponds to post-reset PTPCLKVAL, aka 0 */
	t34 = t3 + (t4 - t3) / 2;
	/* Advance PTPCLKVAL by the समय it took since its पढ़ोout */
	now += (t34 - t12);

	__sja1105_ptp_adjसमय(ds, now);

out_unlock_ptp:
	mutex_unlock(&priv->ptp_data.lock);

	dev_info(priv->ds->dev,
		 "Reset switch and programmed static config. Reason: %s\n",
		 sja1105_reset_reasons[reason]);

	/* Configure the CGU (PLLs) क्रम MII and RMII PHYs.
	 * For these पूर्णांकerfaces there is no dynamic configuration
	 * needed, since PLLs have same settings at all speeds.
	 */
	rc = sja1105_घड़ीing_setup(priv);
	अगर (rc < 0)
		जाओ out;

	क्रम (i = 0; i < SJA1105_NUM_PORTS; i++) अणु
		rc = sja1105_adjust_port_config(priv, i, speed_mbps[i]);
		अगर (rc < 0)
			जाओ out;
	पूर्ण

	अगर (sja1105_supports_sgmii(priv, SJA1105_SGMII_PORT)) अणु
		bool an_enabled = !!(bmcr & BMCR_ANENABLE);

		sja1105_sgmii_pcs_config(priv, an_enabled, false);

		अगर (!an_enabled) अणु
			पूर्णांक speed = SPEED_UNKNOWN;

			अगर (bmcr & BMCR_SPEED1000)
				speed = SPEED_1000;
			अन्यथा अगर (bmcr & BMCR_SPEED100)
				speed = SPEED_100;
			अन्यथा
				speed = SPEED_10;

			sja1105_sgmii_pcs_क्रमce_speed(priv, speed);
		पूर्ण
	पूर्ण

	rc = sja1105_reload_cbs(priv);
	अगर (rc < 0)
		जाओ out;
out:
	mutex_unlock(&priv->mgmt_lock);

	वापस rc;
पूर्ण

अटल पूर्णांक sja1105_pvid_apply(काष्ठा sja1105_निजी *priv, पूर्णांक port, u16 pvid)
अणु
	काष्ठा sja1105_mac_config_entry *mac;

	mac = priv->अटल_config.tables[BLK_IDX_MAC_CONFIG].entries;

	mac[port].vlanid = pvid;

	वापस sja1105_dynamic_config_ग_लिखो(priv, BLK_IDX_MAC_CONFIG, port,
					   &mac[port], true);
पूर्ण

अटल पूर्णांक sja1105_crosschip_bridge_join(काष्ठा dsa_चयन *ds,
					 पूर्णांक tree_index, पूर्णांक sw_index,
					 पूर्णांक other_port, काष्ठा net_device *br)
अणु
	काष्ठा dsa_चयन *other_ds = dsa_चयन_find(tree_index, sw_index);
	काष्ठा sja1105_निजी *other_priv = other_ds->priv;
	काष्ठा sja1105_निजी *priv = ds->priv;
	पूर्णांक port, rc;

	अगर (other_ds->ops != &sja1105_चयन_ops)
		वापस 0;

	क्रम (port = 0; port < ds->num_ports; port++) अणु
		अगर (!dsa_is_user_port(ds, port))
			जारी;
		अगर (dsa_to_port(ds, port)->bridge_dev != br)
			जारी;

		rc = dsa_8021q_crosschip_bridge_join(priv->dsa_8021q_ctx,
						     port,
						     other_priv->dsa_8021q_ctx,
						     other_port);
		अगर (rc)
			वापस rc;

		rc = dsa_8021q_crosschip_bridge_join(other_priv->dsa_8021q_ctx,
						     other_port,
						     priv->dsa_8021q_ctx,
						     port);
		अगर (rc)
			वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम sja1105_crosschip_bridge_leave(काष्ठा dsa_चयन *ds,
					   पूर्णांक tree_index, पूर्णांक sw_index,
					   पूर्णांक other_port,
					   काष्ठा net_device *br)
अणु
	काष्ठा dsa_चयन *other_ds = dsa_चयन_find(tree_index, sw_index);
	काष्ठा sja1105_निजी *other_priv = other_ds->priv;
	काष्ठा sja1105_निजी *priv = ds->priv;
	पूर्णांक port;

	अगर (other_ds->ops != &sja1105_चयन_ops)
		वापस;

	क्रम (port = 0; port < ds->num_ports; port++) अणु
		अगर (!dsa_is_user_port(ds, port))
			जारी;
		अगर (dsa_to_port(ds, port)->bridge_dev != br)
			जारी;

		dsa_8021q_crosschip_bridge_leave(priv->dsa_8021q_ctx, port,
						 other_priv->dsa_8021q_ctx,
						 other_port);

		dsa_8021q_crosschip_bridge_leave(other_priv->dsa_8021q_ctx,
						 other_port,
						 priv->dsa_8021q_ctx, port);
	पूर्ण
पूर्ण

अटल पूर्णांक sja1105_setup_8021q_tagging(काष्ठा dsa_चयन *ds, bool enabled)
अणु
	काष्ठा sja1105_निजी *priv = ds->priv;
	पूर्णांक rc;

	rc = dsa_8021q_setup(priv->dsa_8021q_ctx, enabled);
	अगर (rc)
		वापस rc;

	dev_info(ds->dev, "%s switch tagging\n",
		 enabled ? "Enabled" : "Disabled");
	वापस 0;
पूर्ण

अटल क्रमागत dsa_tag_protocol
sja1105_get_tag_protocol(काष्ठा dsa_चयन *ds, पूर्णांक port,
			 क्रमागत dsa_tag_protocol mp)
अणु
	वापस DSA_TAG_PROTO_SJA1105;
पूर्ण

अटल पूर्णांक sja1105_find_मुक्त_subvlan(u16 *subvlan_map, bool pvid)
अणु
	पूर्णांक subvlan;

	अगर (pvid)
		वापस 0;

	क्रम (subvlan = 1; subvlan < DSA_8021Q_N_SUBVLAN; subvlan++)
		अगर (subvlan_map[subvlan] == VLAN_N_VID)
			वापस subvlan;

	वापस -1;
पूर्ण

अटल पूर्णांक sja1105_find_subvlan(u16 *subvlan_map, u16 vid)
अणु
	पूर्णांक subvlan;

	क्रम (subvlan = 0; subvlan < DSA_8021Q_N_SUBVLAN; subvlan++)
		अगर (subvlan_map[subvlan] == vid)
			वापस subvlan;

	वापस -1;
पूर्ण

अटल पूर्णांक sja1105_find_committed_subvlan(काष्ठा sja1105_निजी *priv,
					  पूर्णांक port, u16 vid)
अणु
	काष्ठा sja1105_port *sp = &priv->ports[port];

	वापस sja1105_find_subvlan(sp->subvlan_map, vid);
पूर्ण

अटल व्योम sja1105_init_subvlan_map(u16 *subvlan_map)
अणु
	पूर्णांक subvlan;

	क्रम (subvlan = 0; subvlan < DSA_8021Q_N_SUBVLAN; subvlan++)
		subvlan_map[subvlan] = VLAN_N_VID;
पूर्ण

अटल व्योम sja1105_commit_subvlan_map(काष्ठा sja1105_निजी *priv, पूर्णांक port,
				       u16 *subvlan_map)
अणु
	काष्ठा sja1105_port *sp = &priv->ports[port];
	पूर्णांक subvlan;

	क्रम (subvlan = 0; subvlan < DSA_8021Q_N_SUBVLAN; subvlan++)
		sp->subvlan_map[subvlan] = subvlan_map[subvlan];
पूर्ण

अटल पूर्णांक sja1105_is_vlan_configured(काष्ठा sja1105_निजी *priv, u16 vid)
अणु
	काष्ठा sja1105_vlan_lookup_entry *vlan;
	पूर्णांक count, i;

	vlan = priv->अटल_config.tables[BLK_IDX_VLAN_LOOKUP].entries;
	count = priv->अटल_config.tables[BLK_IDX_VLAN_LOOKUP].entry_count;

	क्रम (i = 0; i < count; i++)
		अगर (vlan[i].vlanid == vid)
			वापस i;

	/* Return an invalid entry index अगर not found */
	वापस -1;
पूर्ण

अटल पूर्णांक
sja1105_find_retagging_entry(काष्ठा sja1105_retagging_entry *retagging,
			     पूर्णांक count, पूर्णांक from_port, u16 from_vid,
			     u16 to_vid)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < count; i++)
		अगर (retagging[i].ing_port == BIT(from_port) &&
		    retagging[i].vlan_ing == from_vid &&
		    retagging[i].vlan_egr == to_vid)
			वापस i;

	/* Return an invalid entry index अगर not found */
	वापस -1;
पूर्ण

अटल पूर्णांक sja1105_commit_vlans(काष्ठा sja1105_निजी *priv,
				काष्ठा sja1105_vlan_lookup_entry *new_vlan,
				काष्ठा sja1105_retagging_entry *new_retagging,
				पूर्णांक num_retagging)
अणु
	काष्ठा sja1105_retagging_entry *retagging;
	काष्ठा sja1105_vlan_lookup_entry *vlan;
	काष्ठा sja1105_table *table;
	पूर्णांक num_vlans = 0;
	पूर्णांक rc, i, k = 0;

	/* VLAN table */
	table = &priv->अटल_config.tables[BLK_IDX_VLAN_LOOKUP];
	vlan = table->entries;

	क्रम (i = 0; i < VLAN_N_VID; i++) अणु
		पूर्णांक match = sja1105_is_vlan_configured(priv, i);

		अगर (new_vlan[i].vlanid != VLAN_N_VID)
			num_vlans++;

		अगर (new_vlan[i].vlanid == VLAN_N_VID && match >= 0) अणु
			/* Was there beक्रमe, no दीर्घer is. Delete */
			dev_dbg(priv->ds->dev, "Deleting VLAN %d\n", i);
			rc = sja1105_dynamic_config_ग_लिखो(priv,
							  BLK_IDX_VLAN_LOOKUP,
							  i, &vlan[match], false);
			अगर (rc < 0)
				वापस rc;
		पूर्ण अन्यथा अगर (new_vlan[i].vlanid != VLAN_N_VID) अणु
			/* Nothing changed, करोn't करो anything */
			अगर (match >= 0 &&
			    vlan[match].vlanid == new_vlan[i].vlanid &&
			    vlan[match].tag_port == new_vlan[i].tag_port &&
			    vlan[match].vlan_bc == new_vlan[i].vlan_bc &&
			    vlan[match].vmemb_port == new_vlan[i].vmemb_port)
				जारी;
			/* Update entry */
			dev_dbg(priv->ds->dev, "Updating VLAN %d\n", i);
			rc = sja1105_dynamic_config_ग_लिखो(priv,
							  BLK_IDX_VLAN_LOOKUP,
							  i, &new_vlan[i],
							  true);
			अगर (rc < 0)
				वापस rc;
		पूर्ण
	पूर्ण

	अगर (table->entry_count)
		kमुक्त(table->entries);

	table->entries = kसुस्मृति(num_vlans, table->ops->unpacked_entry_size,
				 GFP_KERNEL);
	अगर (!table->entries)
		वापस -ENOMEM;

	table->entry_count = num_vlans;
	vlan = table->entries;

	क्रम (i = 0; i < VLAN_N_VID; i++) अणु
		अगर (new_vlan[i].vlanid == VLAN_N_VID)
			जारी;
		vlan[k++] = new_vlan[i];
	पूर्ण

	/* VLAN Retagging Table */
	table = &priv->अटल_config.tables[BLK_IDX_RETAGGING];
	retagging = table->entries;

	क्रम (i = 0; i < table->entry_count; i++) अणु
		rc = sja1105_dynamic_config_ग_लिखो(priv, BLK_IDX_RETAGGING,
						  i, &retagging[i], false);
		अगर (rc)
			वापस rc;
	पूर्ण

	अगर (table->entry_count)
		kमुक्त(table->entries);

	table->entries = kसुस्मृति(num_retagging, table->ops->unpacked_entry_size,
				 GFP_KERNEL);
	अगर (!table->entries)
		वापस -ENOMEM;

	table->entry_count = num_retagging;
	retagging = table->entries;

	क्रम (i = 0; i < num_retagging; i++) अणु
		retagging[i] = new_retagging[i];

		/* Update entry */
		rc = sja1105_dynamic_config_ग_लिखो(priv, BLK_IDX_RETAGGING,
						  i, &retagging[i], true);
		अगर (rc < 0)
			वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा sja1105_crosschip_vlan अणु
	काष्ठा list_head list;
	u16 vid;
	bool untagged;
	पूर्णांक port;
	पूर्णांक other_port;
	काष्ठा dsa_8021q_context *other_ctx;
पूर्ण;

काष्ठा sja1105_crosschip_चयन अणु
	काष्ठा list_head list;
	काष्ठा dsa_8021q_context *other_ctx;
पूर्ण;

अटल पूर्णांक sja1105_commit_pvid(काष्ठा sja1105_निजी *priv)
अणु
	काष्ठा sja1105_bridge_vlan *v;
	काष्ठा list_head *vlan_list;
	पूर्णांक rc = 0;

	अगर (priv->vlan_state == SJA1105_VLAN_FILTERING_FULL)
		vlan_list = &priv->bridge_vlans;
	अन्यथा
		vlan_list = &priv->dsa_8021q_vlans;

	list_क्रम_each_entry(v, vlan_list, list) अणु
		अगर (v->pvid) अणु
			rc = sja1105_pvid_apply(priv, v->port, v->vid);
			अगर (rc)
				अवरोध;
		पूर्ण
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक
sja1105_build_bridge_vlans(काष्ठा sja1105_निजी *priv,
			   काष्ठा sja1105_vlan_lookup_entry *new_vlan)
अणु
	काष्ठा sja1105_bridge_vlan *v;

	अगर (priv->vlan_state == SJA1105_VLAN_UNAWARE)
		वापस 0;

	list_क्रम_each_entry(v, &priv->bridge_vlans, list) अणु
		पूर्णांक match = v->vid;

		new_vlan[match].vlanid = v->vid;
		new_vlan[match].vmemb_port |= BIT(v->port);
		new_vlan[match].vlan_bc |= BIT(v->port);
		अगर (!v->untagged)
			new_vlan[match].tag_port |= BIT(v->port);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
sja1105_build_dsa_8021q_vlans(काष्ठा sja1105_निजी *priv,
			      काष्ठा sja1105_vlan_lookup_entry *new_vlan)
अणु
	काष्ठा sja1105_bridge_vlan *v;

	अगर (priv->vlan_state == SJA1105_VLAN_FILTERING_FULL)
		वापस 0;

	list_क्रम_each_entry(v, &priv->dsa_8021q_vlans, list) अणु
		पूर्णांक match = v->vid;

		new_vlan[match].vlanid = v->vid;
		new_vlan[match].vmemb_port |= BIT(v->port);
		new_vlan[match].vlan_bc |= BIT(v->port);
		अगर (!v->untagged)
			new_vlan[match].tag_port |= BIT(v->port);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sja1105_build_subvlans(काष्ठा sja1105_निजी *priv,
				  u16 subvlan_map[][DSA_8021Q_N_SUBVLAN],
				  काष्ठा sja1105_vlan_lookup_entry *new_vlan,
				  काष्ठा sja1105_retagging_entry *new_retagging,
				  पूर्णांक *num_retagging)
अणु
	काष्ठा sja1105_bridge_vlan *v;
	पूर्णांक k = *num_retagging;

	अगर (priv->vlan_state != SJA1105_VLAN_BEST_EFFORT)
		वापस 0;

	list_क्रम_each_entry(v, &priv->bridge_vlans, list) अणु
		पूर्णांक upstream = dsa_upstream_port(priv->ds, v->port);
		पूर्णांक match, subvlan;
		u16 rx_vid;

		/* Only sub-VLANs on user ports need to be applied.
		 * Bridge VLANs also include VLANs added स्वतःmatically
		 * by DSA on the CPU port.
		 */
		अगर (!dsa_is_user_port(priv->ds, v->port))
			जारी;

		subvlan = sja1105_find_subvlan(subvlan_map[v->port],
					       v->vid);
		अगर (subvlan < 0) अणु
			subvlan = sja1105_find_मुक्त_subvlan(subvlan_map[v->port],
							    v->pvid);
			अगर (subvlan < 0) अणु
				dev_err(priv->ds->dev, "No more free subvlans\n");
				वापस -ENOSPC;
			पूर्ण
		पूर्ण

		rx_vid = dsa_8021q_rx_vid_subvlan(priv->ds, v->port, subvlan);

		/* @v->vid on @v->port needs to be retagged to @rx_vid
		 * on @upstream. Assume @v->vid on @v->port and on
		 * @upstream was alपढ़ोy configured by the previous
		 * iteration over bridge_vlans.
		 */
		match = rx_vid;
		new_vlan[match].vlanid = rx_vid;
		new_vlan[match].vmemb_port |= BIT(v->port);
		new_vlan[match].vmemb_port |= BIT(upstream);
		new_vlan[match].vlan_bc |= BIT(v->port);
		new_vlan[match].vlan_bc |= BIT(upstream);
		/* The "untagged" flag is set the same as क्रम the
		 * original VLAN
		 */
		अगर (!v->untagged)
			new_vlan[match].tag_port |= BIT(v->port);
		/* But it's always tagged towards the CPU */
		new_vlan[match].tag_port |= BIT(upstream);

		/* The Retagging Table generates packet *clones* with
		 * the new VLAN. This is a very odd hardware quirk
		 * which we need to suppress by dropping the original
		 * packet.
		 * Deny egress of the original VLAN towards the CPU
		 * port. This will क्रमce the चयन to drop it, and
		 * we'll see only the retagged packets.
		 */
		match = v->vid;
		new_vlan[match].vlan_bc &= ~BIT(upstream);

		/* And the retagging itself */
		new_retagging[k].vlan_ing = v->vid;
		new_retagging[k].vlan_egr = rx_vid;
		new_retagging[k].ing_port = BIT(v->port);
		new_retagging[k].egr_port = BIT(upstream);
		अगर (k++ == SJA1105_MAX_RETAGGING_COUNT) अणु
			dev_err(priv->ds->dev, "No more retagging rules\n");
			वापस -ENOSPC;
		पूर्ण

		subvlan_map[v->port][subvlan] = v->vid;
	पूर्ण

	*num_retagging = k;

	वापस 0;
पूर्ण

/* Sadly, in crosschip scenarios where the CPU port is also the link to another
 * चयन, we should retag backwards (the dsa_8021q vid to the original vid) on
 * the CPU port of neighbour चयनes.
 */
अटल पूर्णांक
sja1105_build_crosschip_subvlans(काष्ठा sja1105_निजी *priv,
				 काष्ठा sja1105_vlan_lookup_entry *new_vlan,
				 काष्ठा sja1105_retagging_entry *new_retagging,
				 पूर्णांक *num_retagging)
अणु
	काष्ठा sja1105_crosschip_vlan *पंचांगp, *pos;
	काष्ठा dsa_8021q_crosschip_link *c;
	काष्ठा sja1105_bridge_vlan *v, *w;
	काष्ठा list_head crosschip_vlans;
	पूर्णांक k = *num_retagging;
	पूर्णांक rc = 0;

	अगर (priv->vlan_state != SJA1105_VLAN_BEST_EFFORT)
		वापस 0;

	INIT_LIST_HEAD(&crosschip_vlans);

	list_क्रम_each_entry(c, &priv->dsa_8021q_ctx->crosschip_links, list) अणु
		काष्ठा sja1105_निजी *other_priv = c->other_ctx->ds->priv;

		अगर (other_priv->vlan_state == SJA1105_VLAN_FILTERING_FULL)
			जारी;

		/* Crosschip links are also added to the CPU ports.
		 * Ignore those.
		 */
		अगर (!dsa_is_user_port(priv->ds, c->port))
			जारी;
		अगर (!dsa_is_user_port(c->other_ctx->ds, c->other_port))
			जारी;

		/* Search क्रम VLANs on the remote port */
		list_क्रम_each_entry(v, &other_priv->bridge_vlans, list) अणु
			bool alपढ़ोy_added = false;
			bool we_have_it = false;

			अगर (v->port != c->other_port)
				जारी;

			/* If @v is a pvid on @other_ds, it करोes not need
			 * re-retagging, because its SVL field is 0 and we
			 * alपढ़ोy allow that, via the dsa_8021q crosschip
			 * links.
			 */
			अगर (v->pvid)
				जारी;

			/* Search क्रम the VLAN on our local port */
			list_क्रम_each_entry(w, &priv->bridge_vlans, list) अणु
				अगर (w->port == c->port && w->vid == v->vid) अणु
					we_have_it = true;
					अवरोध;
				पूर्ण
			पूर्ण

			अगर (!we_have_it)
				जारी;

			list_क्रम_each_entry(पंचांगp, &crosschip_vlans, list) अणु
				अगर (पंचांगp->vid == v->vid &&
				    पंचांगp->untagged == v->untagged &&
				    पंचांगp->port == c->port &&
				    पंचांगp->other_port == v->port &&
				    पंचांगp->other_ctx == c->other_ctx) अणु
					alपढ़ोy_added = true;
					अवरोध;
				पूर्ण
			पूर्ण

			अगर (alपढ़ोy_added)
				जारी;

			पंचांगp = kzalloc(माप(*पंचांगp), GFP_KERNEL);
			अगर (!पंचांगp) अणु
				dev_err(priv->ds->dev, "Failed to allocate memory\n");
				rc = -ENOMEM;
				जाओ out;
			पूर्ण
			पंचांगp->vid = v->vid;
			पंचांगp->port = c->port;
			पंचांगp->other_port = v->port;
			पंचांगp->other_ctx = c->other_ctx;
			पंचांगp->untagged = v->untagged;
			list_add(&पंचांगp->list, &crosschip_vlans);
		पूर्ण
	पूर्ण

	list_क्रम_each_entry(पंचांगp, &crosschip_vlans, list) अणु
		काष्ठा sja1105_निजी *other_priv = पंचांगp->other_ctx->ds->priv;
		पूर्णांक upstream = dsa_upstream_port(priv->ds, पंचांगp->port);
		पूर्णांक match, subvlan;
		u16 rx_vid;

		subvlan = sja1105_find_committed_subvlan(other_priv,
							 पंचांगp->other_port,
							 पंचांगp->vid);
		/* If this happens, it's a bug. The neighbour चयन करोes not
		 * have a subvlan क्रम पंचांगp->vid on पंचांगp->other_port, but it
		 * should, since we alपढ़ोy checked क्रम its vlan_state.
		 */
		अगर (WARN_ON(subvlan < 0)) अणु
			rc = -EINVAL;
			जाओ out;
		पूर्ण

		rx_vid = dsa_8021q_rx_vid_subvlan(पंचांगp->other_ctx->ds,
						  पंचांगp->other_port,
						  subvlan);

		/* The @rx_vid retagged from @पंचांगp->vid on
		 * अणु@पंचांगp->other_ds, @पंचांगp->other_portपूर्ण needs to be
		 * re-retagged to @पंचांगp->vid on the way back to us.
		 *
		 * Assume the original @पंचांगp->vid is alपढ़ोy configured
		 * on this local चयन, otherwise we wouldn't be
		 * retagging its subvlan on the other चयन in the
		 * first place. We just need to add a reverse retagging
		 * rule क्रम @rx_vid and install @rx_vid on our ports.
		 */
		match = rx_vid;
		new_vlan[match].vlanid = rx_vid;
		new_vlan[match].vmemb_port |= BIT(पंचांगp->port);
		new_vlan[match].vmemb_port |= BIT(upstream);
		/* The "untagged" flag is set the same as क्रम the
		 * original VLAN. And towards the CPU, it करोesn't
		 * really matter, because @rx_vid will only receive
		 * traffic on that port. For consistency with other dsa_8021q
		 * VLANs, we'll keep the CPU port tagged.
		 */
		अगर (!पंचांगp->untagged)
			new_vlan[match].tag_port |= BIT(पंचांगp->port);
		new_vlan[match].tag_port |= BIT(upstream);
		/* Deny egress of @rx_vid towards our front-panel port.
		 * This will क्रमce the चयन to drop it, and we'll see
		 * only the re-retagged packets (having the original,
		 * pre-initial-retagging, VLAN @पंचांगp->vid).
		 */
		new_vlan[match].vlan_bc &= ~BIT(पंचांगp->port);

		/* On reverse retagging, the same ingress VLAN goes to multiple
		 * ports. So we have an opportunity to create composite rules
		 * to not waste the limited space in the retagging table.
		 */
		k = sja1105_find_retagging_entry(new_retagging, *num_retagging,
						 upstream, rx_vid, पंचांगp->vid);
		अगर (k < 0) अणु
			अगर (*num_retagging == SJA1105_MAX_RETAGGING_COUNT) अणु
				dev_err(priv->ds->dev, "No more retagging rules\n");
				rc = -ENOSPC;
				जाओ out;
			पूर्ण
			k = (*num_retagging)++;
		पूर्ण
		/* And the retagging itself */
		new_retagging[k].vlan_ing = rx_vid;
		new_retagging[k].vlan_egr = पंचांगp->vid;
		new_retagging[k].ing_port = BIT(upstream);
		new_retagging[k].egr_port |= BIT(पंचांगp->port);
	पूर्ण

out:
	list_क्रम_each_entry_safe(पंचांगp, pos, &crosschip_vlans, list) अणु
		list_del(&पंचांगp->list);
		kमुक्त(पंचांगp);
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक sja1105_build_vlan_table(काष्ठा sja1105_निजी *priv, bool notअगरy);

अटल पूर्णांक sja1105_notअगरy_crosschip_चयनes(काष्ठा sja1105_निजी *priv)
अणु
	काष्ठा sja1105_crosschip_चयन *s, *pos;
	काष्ठा list_head crosschip_चयनes;
	काष्ठा dsa_8021q_crosschip_link *c;
	पूर्णांक rc = 0;

	INIT_LIST_HEAD(&crosschip_चयनes);

	list_क्रम_each_entry(c, &priv->dsa_8021q_ctx->crosschip_links, list) अणु
		bool alपढ़ोy_added = false;

		list_क्रम_each_entry(s, &crosschip_चयनes, list) अणु
			अगर (s->other_ctx == c->other_ctx) अणु
				alपढ़ोy_added = true;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (alपढ़ोy_added)
			जारी;

		s = kzalloc(माप(*s), GFP_KERNEL);
		अगर (!s) अणु
			dev_err(priv->ds->dev, "Failed to allocate memory\n");
			rc = -ENOMEM;
			जाओ out;
		पूर्ण
		s->other_ctx = c->other_ctx;
		list_add(&s->list, &crosschip_चयनes);
	पूर्ण

	list_क्रम_each_entry(s, &crosschip_चयनes, list) अणु
		काष्ठा sja1105_निजी *other_priv = s->other_ctx->ds->priv;

		rc = sja1105_build_vlan_table(other_priv, false);
		अगर (rc)
			जाओ out;
	पूर्ण

out:
	list_क्रम_each_entry_safe(s, pos, &crosschip_चयनes, list) अणु
		list_del(&s->list);
		kमुक्त(s);
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक sja1105_build_vlan_table(काष्ठा sja1105_निजी *priv, bool notअगरy)
अणु
	u16 subvlan_map[SJA1105_NUM_PORTS][DSA_8021Q_N_SUBVLAN];
	काष्ठा sja1105_retagging_entry *new_retagging;
	काष्ठा sja1105_vlan_lookup_entry *new_vlan;
	काष्ठा sja1105_table *table;
	पूर्णांक i, num_retagging = 0;
	पूर्णांक rc;

	table = &priv->अटल_config.tables[BLK_IDX_VLAN_LOOKUP];
	new_vlan = kसुस्मृति(VLAN_N_VID,
			   table->ops->unpacked_entry_size, GFP_KERNEL);
	अगर (!new_vlan)
		वापस -ENOMEM;

	table = &priv->अटल_config.tables[BLK_IDX_VLAN_LOOKUP];
	new_retagging = kसुस्मृति(SJA1105_MAX_RETAGGING_COUNT,
				table->ops->unpacked_entry_size, GFP_KERNEL);
	अगर (!new_retagging) अणु
		kमुक्त(new_vlan);
		वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0; i < VLAN_N_VID; i++)
		new_vlan[i].vlanid = VLAN_N_VID;

	क्रम (i = 0; i < SJA1105_MAX_RETAGGING_COUNT; i++)
		new_retagging[i].vlan_ing = VLAN_N_VID;

	क्रम (i = 0; i < priv->ds->num_ports; i++)
		sja1105_init_subvlan_map(subvlan_map[i]);

	/* Bridge VLANs */
	rc = sja1105_build_bridge_vlans(priv, new_vlan);
	अगर (rc)
		जाओ out;

	/* VLANs necessary क्रम dsa_8021q operation, given to us by tag_8021q.c:
	 * - RX VLANs
	 * - TX VLANs
	 * - Crosschip links
	 */
	rc = sja1105_build_dsa_8021q_vlans(priv, new_vlan);
	अगर (rc)
		जाओ out;

	/* Private VLANs necessary क्रम dsa_8021q operation, which we need to
	 * determine on our own:
	 * - Sub-VLANs
	 * - Sub-VLANs of crosschip चयनes
	 */
	rc = sja1105_build_subvlans(priv, subvlan_map, new_vlan, new_retagging,
				    &num_retagging);
	अगर (rc)
		जाओ out;

	rc = sja1105_build_crosschip_subvlans(priv, new_vlan, new_retagging,
					      &num_retagging);
	अगर (rc)
		जाओ out;

	rc = sja1105_commit_vlans(priv, new_vlan, new_retagging, num_retagging);
	अगर (rc)
		जाओ out;

	rc = sja1105_commit_pvid(priv);
	अगर (rc)
		जाओ out;

	क्रम (i = 0; i < priv->ds->num_ports; i++)
		sja1105_commit_subvlan_map(priv, i, subvlan_map[i]);

	अगर (notअगरy) अणु
		rc = sja1105_notअगरy_crosschip_चयनes(priv);
		अगर (rc)
			जाओ out;
	पूर्ण

out:
	kमुक्त(new_vlan);
	kमुक्त(new_retagging);

	वापस rc;
पूर्ण

/* The TPID setting beदीर्घs to the General Parameters table,
 * which can only be partially reconfigured at runसमय (and not the TPID).
 * So a चयन reset is required.
 */
पूर्णांक sja1105_vlan_filtering(काष्ठा dsa_चयन *ds, पूर्णांक port, bool enabled,
			   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा sja1105_l2_lookup_params_entry *l2_lookup_params;
	काष्ठा sja1105_general_params_entry *general_params;
	काष्ठा sja1105_निजी *priv = ds->priv;
	क्रमागत sja1105_vlan_state state;
	काष्ठा sja1105_table *table;
	काष्ठा sja1105_rule *rule;
	bool want_tagging;
	u16 tpid, tpid2;
	पूर्णांक rc;

	list_क्रम_each_entry(rule, &priv->flow_block.rules, list) अणु
		अगर (rule->type == SJA1105_RULE_VL) अणु
			NL_SET_ERR_MSG_MOD(extack,
					   "Cannot change VLAN filtering with active VL rules");
			वापस -EBUSY;
		पूर्ण
	पूर्ण

	अगर (enabled) अणु
		/* Enable VLAN filtering. */
		tpid  = ETH_P_8021Q;
		tpid2 = ETH_P_8021AD;
	पूर्ण अन्यथा अणु
		/* Disable VLAN filtering. */
		tpid  = ETH_P_SJA1105;
		tpid2 = ETH_P_SJA1105;
	पूर्ण

	क्रम (port = 0; port < ds->num_ports; port++) अणु
		काष्ठा sja1105_port *sp = &priv->ports[port];

		अगर (enabled)
			sp->xmit_tpid = priv->info->qinq_tpid;
		अन्यथा
			sp->xmit_tpid = ETH_P_SJA1105;
	पूर्ण

	अगर (!enabled)
		state = SJA1105_VLAN_UNAWARE;
	अन्यथा अगर (priv->best_efक्रमt_vlan_filtering)
		state = SJA1105_VLAN_BEST_EFFORT;
	अन्यथा
		state = SJA1105_VLAN_FILTERING_FULL;

	अगर (priv->vlan_state == state)
		वापस 0;

	priv->vlan_state = state;
	want_tagging = (state == SJA1105_VLAN_UNAWARE ||
			state == SJA1105_VLAN_BEST_EFFORT);

	table = &priv->अटल_config.tables[BLK_IDX_GENERAL_PARAMS];
	general_params = table->entries;
	/* EtherType used to identअगरy inner tagged (C-tag) VLAN traffic */
	general_params->tpid = tpid;
	/* EtherType used to identअगरy outer tagged (S-tag) VLAN traffic */
	general_params->tpid2 = tpid2;
	/* When VLAN filtering is on, we need to at least be able to
	 * decode management traffic through the "backup plan".
	 */
	general_params->incl_srcpt1 = enabled;
	general_params->incl_srcpt0 = enabled;

	want_tagging = priv->best_efक्रमt_vlan_filtering || !enabled;

	/* VLAN filtering => independent VLAN learning.
	 * No VLAN filtering (or best efक्रमt) => shared VLAN learning.
	 *
	 * In shared VLAN learning mode, untagged traffic still माला_लो
	 * pvid-tagged, and the FDB table माला_लो populated with entries
	 * containing the "real" (pvid or from VLAN tag) VLAN ID.
	 * However the चयन perक्रमms a masked L2 lookup in the FDB,
	 * effectively only looking up a frame's DMAC (and not VID) क्रम the
	 * क्रमwarding decision.
	 *
	 * This is extremely convenient क्रम us, because in modes with
	 * vlan_filtering=0, dsa_8021q actually installs unique pvid's पूर्णांकo
	 * each front panel port. This is good क्रम identअगरication but अवरोधs
	 * learning badly - the VID of the learnt FDB entry is unique, aka
	 * no frames coming from any other port are going to have it. So
	 * क्रम क्रमwarding purposes, this is as though learning was broken
	 * (all frames get flooded).
	 */
	table = &priv->अटल_config.tables[BLK_IDX_L2_LOOKUP_PARAMS];
	l2_lookup_params = table->entries;
	l2_lookup_params->shared_learn = want_tagging;

	sja1105_frame_memory_partitioning(priv);

	rc = sja1105_build_vlan_table(priv, false);
	अगर (rc)
		वापस rc;

	rc = sja1105_अटल_config_reload(priv, SJA1105_VLAN_FILTERING);
	अगर (rc)
		NL_SET_ERR_MSG_MOD(extack, "Failed to change VLAN Ethertype");

	/* Switch port identअगरication based on 802.1Q is only passable
	 * अगर we are not under a vlan_filtering bridge. So make sure
	 * the two configurations are mutually exclusive (of course, the
	 * user may know better, i.e. best_efक्रमt_vlan_filtering).
	 */
	वापस sja1105_setup_8021q_tagging(ds, want_tagging);
पूर्ण

/* Returns number of VLANs added (0 or 1) on success,
 * or a negative error code.
 */
अटल पूर्णांक sja1105_vlan_add_one(काष्ठा dsa_चयन *ds, पूर्णांक port, u16 vid,
				u16 flags, काष्ठा list_head *vlan_list)
अणु
	bool untagged = flags & BRIDGE_VLAN_INFO_UNTAGGED;
	bool pvid = flags & BRIDGE_VLAN_INFO_PVID;
	काष्ठा sja1105_bridge_vlan *v;

	list_क्रम_each_entry(v, vlan_list, list) अणु
		अगर (v->port == port && v->vid == vid) अणु
			/* Alपढ़ोy added */
			अगर (v->untagged == untagged && v->pvid == pvid)
				/* Nothing changed */
				वापस 0;

			/* It's the same VLAN, but some of the flags changed
			 * and the user did not bother to delete it first.
			 * Update it and trigger sja1105_build_vlan_table.
			 */
			v->untagged = untagged;
			v->pvid = pvid;
			वापस 1;
		पूर्ण
	पूर्ण

	v = kzalloc(माप(*v), GFP_KERNEL);
	अगर (!v) अणु
		dev_err(ds->dev, "Out of memory while storing VLAN\n");
		वापस -ENOMEM;
	पूर्ण

	v->port = port;
	v->vid = vid;
	v->untagged = untagged;
	v->pvid = pvid;
	list_add(&v->list, vlan_list);

	वापस 1;
पूर्ण

/* Returns number of VLANs deleted (0 or 1) */
अटल पूर्णांक sja1105_vlan_del_one(काष्ठा dsa_चयन *ds, पूर्णांक port, u16 vid,
				काष्ठा list_head *vlan_list)
अणु
	काष्ठा sja1105_bridge_vlan *v, *n;

	list_क्रम_each_entry_safe(v, n, vlan_list, list) अणु
		अगर (v->port == port && v->vid == vid) अणु
			list_del(&v->list);
			kमुक्त(v);
			वापस 1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sja1105_vlan_add(काष्ठा dsa_चयन *ds, पूर्णांक port,
			    स्थिर काष्ठा चयनdev_obj_port_vlan *vlan,
			    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा sja1105_निजी *priv = ds->priv;
	bool vlan_table_changed = false;
	पूर्णांक rc;

	/* If the user wants best-efक्रमt VLAN filtering (aka vlan_filtering
	 * bridge plus tagging), be sure to at least deny alterations to the
	 * configuration करोne by dsa_8021q.
	 */
	अगर (priv->vlan_state != SJA1105_VLAN_FILTERING_FULL &&
	    vid_is_dsa_8021q(vlan->vid)) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Range 1024-3071 reserved for dsa_8021q operation");
		वापस -EBUSY;
	पूर्ण

	rc = sja1105_vlan_add_one(ds, port, vlan->vid, vlan->flags,
				  &priv->bridge_vlans);
	अगर (rc < 0)
		वापस rc;
	अगर (rc > 0)
		vlan_table_changed = true;

	अगर (!vlan_table_changed)
		वापस 0;

	वापस sja1105_build_vlan_table(priv, true);
पूर्ण

अटल पूर्णांक sja1105_vlan_del(काष्ठा dsa_चयन *ds, पूर्णांक port,
			    स्थिर काष्ठा चयनdev_obj_port_vlan *vlan)
अणु
	काष्ठा sja1105_निजी *priv = ds->priv;
	bool vlan_table_changed = false;
	पूर्णांक rc;

	rc = sja1105_vlan_del_one(ds, port, vlan->vid, &priv->bridge_vlans);
	अगर (rc > 0)
		vlan_table_changed = true;

	अगर (!vlan_table_changed)
		वापस 0;

	वापस sja1105_build_vlan_table(priv, true);
पूर्ण

अटल पूर्णांक sja1105_dsa_8021q_vlan_add(काष्ठा dsa_चयन *ds, पूर्णांक port, u16 vid,
				      u16 flags)
अणु
	काष्ठा sja1105_निजी *priv = ds->priv;
	पूर्णांक rc;

	rc = sja1105_vlan_add_one(ds, port, vid, flags, &priv->dsa_8021q_vlans);
	अगर (rc <= 0)
		वापस rc;

	वापस sja1105_build_vlan_table(priv, true);
पूर्ण

अटल पूर्णांक sja1105_dsa_8021q_vlan_del(काष्ठा dsa_चयन *ds, पूर्णांक port, u16 vid)
अणु
	काष्ठा sja1105_निजी *priv = ds->priv;
	पूर्णांक rc;

	rc = sja1105_vlan_del_one(ds, port, vid, &priv->dsa_8021q_vlans);
	अगर (!rc)
		वापस 0;

	वापस sja1105_build_vlan_table(priv, true);
पूर्ण

अटल स्थिर काष्ठा dsa_8021q_ops sja1105_dsa_8021q_ops = अणु
	.vlan_add	= sja1105_dsa_8021q_vlan_add,
	.vlan_del	= sja1105_dsa_8021q_vlan_del,
पूर्ण;

/* The programming model क्रम the SJA1105 चयन is "all-at-once" via अटल
 * configuration tables. Some of these can be dynamically modअगरied at runसमय,
 * but not the xMII mode parameters table.
 * Furthermode, some PHYs may not have crystals क्रम generating their घड़ीs
 * (e.g. RMII). Instead, their 50MHz घड़ी is supplied via the SJA1105 port's
 * ref_clk pin. So port घड़ीing needs to be initialized early, beक्रमe
 * connecting to PHYs is attempted, otherwise they won't respond through MDIO.
 * Setting correct PHY link speed करोes not matter now.
 * But dsa_slave_phy_setup is called later than sja1105_setup, so the PHY
 * bindings are not yet parsed by DSA core. We need to parse early so that we
 * can populate the xMII mode parameters table.
 */
अटल पूर्णांक sja1105_setup(काष्ठा dsa_चयन *ds)
अणु
	काष्ठा sja1105_dt_port ports[SJA1105_NUM_PORTS];
	काष्ठा sja1105_निजी *priv = ds->priv;
	पूर्णांक rc;

	rc = sja1105_parse_dt(priv, ports);
	अगर (rc < 0) अणु
		dev_err(ds->dev, "Failed to parse DT: %d\n", rc);
		वापस rc;
	पूर्ण

	/* Error out early अगर पूर्णांकernal delays are required through DT
	 * and we can't apply them.
	 */
	rc = sja1105_parse_rgmii_delays(priv, ports);
	अगर (rc < 0) अणु
		dev_err(ds->dev, "RGMII delay not supported\n");
		वापस rc;
	पूर्ण

	rc = sja1105_ptp_घड़ी_रेजिस्टर(ds);
	अगर (rc < 0) अणु
		dev_err(ds->dev, "Failed to register PTP clock: %d\n", rc);
		वापस rc;
	पूर्ण
	/* Create and send configuration करोwn to device */
	rc = sja1105_अटल_config_load(priv, ports);
	अगर (rc < 0) अणु
		dev_err(ds->dev, "Failed to load static config: %d\n", rc);
		जाओ out_ptp_घड़ी_unरेजिस्टर;
	पूर्ण
	/* Configure the CGU (PHY link modes and speeds) */
	rc = sja1105_घड़ीing_setup(priv);
	अगर (rc < 0) अणु
		dev_err(ds->dev, "Failed to configure MII clocking: %d\n", rc);
		जाओ out_अटल_config_मुक्त;
	पूर्ण
	/* On SJA1105, VLAN filtering per se is always enabled in hardware.
	 * The only thing we can करो to disable it is lie about what the 802.1Q
	 * EtherType is.
	 * So it will still try to apply VLAN filtering, but all ingress
	 * traffic (except frames received with EtherType of ETH_P_SJA1105)
	 * will be पूर्णांकernally tagged with a distorted VLAN header where the
	 * TPID is ETH_P_SJA1105, and the VLAN ID is the port pvid.
	 */
	ds->vlan_filtering_is_global = true;

	/* Advertise the 8 egress queues */
	ds->num_tx_queues = SJA1105_NUM_TC;

	ds->mtu_enक्रमcement_ingress = true;

	priv->best_efक्रमt_vlan_filtering = true;

	rc = sja1105_devlink_setup(ds);
	अगर (rc < 0)
		जाओ out_अटल_config_मुक्त;

	/* The DSA/चयनdev model brings up चयन ports in standalone mode by
	 * शेष, and that means vlan_filtering is 0 since they're not under
	 * a bridge, so it's safe to set up चयन tagging at this समय.
	 */
	rtnl_lock();
	rc = sja1105_setup_8021q_tagging(ds, true);
	rtnl_unlock();
	अगर (rc)
		जाओ out_devlink_tearकरोwn;

	वापस 0;

out_devlink_tearकरोwn:
	sja1105_devlink_tearकरोwn(ds);
out_ptp_घड़ी_unरेजिस्टर:
	sja1105_ptp_घड़ी_unरेजिस्टर(ds);
out_अटल_config_मुक्त:
	sja1105_अटल_config_मुक्त(&priv->अटल_config);

	वापस rc;
पूर्ण

अटल व्योम sja1105_tearकरोwn(काष्ठा dsa_चयन *ds)
अणु
	काष्ठा sja1105_निजी *priv = ds->priv;
	काष्ठा sja1105_bridge_vlan *v, *n;
	पूर्णांक port;

	क्रम (port = 0; port < SJA1105_NUM_PORTS; port++) अणु
		काष्ठा sja1105_port *sp = &priv->ports[port];

		अगर (!dsa_is_user_port(ds, port))
			जारी;

		अगर (sp->xmit_worker)
			kthपढ़ो_destroy_worker(sp->xmit_worker);
	पूर्ण

	sja1105_devlink_tearकरोwn(ds);
	sja1105_flower_tearकरोwn(ds);
	sja1105_tas_tearकरोwn(ds);
	sja1105_ptp_घड़ी_unरेजिस्टर(ds);
	sja1105_अटल_config_मुक्त(&priv->अटल_config);

	list_क्रम_each_entry_safe(v, n, &priv->dsa_8021q_vlans, list) अणु
		list_del(&v->list);
		kमुक्त(v);
	पूर्ण

	list_क्रम_each_entry_safe(v, n, &priv->bridge_vlans, list) अणु
		list_del(&v->list);
		kमुक्त(v);
	पूर्ण
पूर्ण

अटल व्योम sja1105_port_disable(काष्ठा dsa_चयन *ds, पूर्णांक port)
अणु
	काष्ठा sja1105_निजी *priv = ds->priv;
	काष्ठा sja1105_port *sp = &priv->ports[port];

	अगर (!dsa_is_user_port(ds, port))
		वापस;

	kthपढ़ो_cancel_work_sync(&sp->xmit_work);
	skb_queue_purge(&sp->xmit_queue);
पूर्ण

अटल पूर्णांक sja1105_mgmt_xmit(काष्ठा dsa_चयन *ds, पूर्णांक port, पूर्णांक slot,
			     काष्ठा sk_buff *skb, bool takets)
अणु
	काष्ठा sja1105_mgmt_entry mgmt_route = अणु0पूर्ण;
	काष्ठा sja1105_निजी *priv = ds->priv;
	काष्ठा ethhdr *hdr;
	पूर्णांक समयout = 10;
	पूर्णांक rc;

	hdr = eth_hdr(skb);

	mgmt_route.macaddr = ether_addr_to_u64(hdr->h_dest);
	mgmt_route.destports = BIT(port);
	mgmt_route.enfport = 1;
	mgmt_route.tsreg = 0;
	mgmt_route.takets = takets;

	rc = sja1105_dynamic_config_ग_लिखो(priv, BLK_IDX_MGMT_ROUTE,
					  slot, &mgmt_route, true);
	अगर (rc < 0) अणु
		kमुक्त_skb(skb);
		वापस rc;
	पूर्ण

	/* Transfer skb to the host port. */
	dsa_enqueue_skb(skb, dsa_to_port(ds, port)->slave);

	/* Wait until the चयन has processed the frame */
	करो अणु
		rc = sja1105_dynamic_config_पढ़ो(priv, BLK_IDX_MGMT_ROUTE,
						 slot, &mgmt_route);
		अगर (rc < 0) अणु
			dev_err_ratelimited(priv->ds->dev,
					    "failed to poll for mgmt route\n");
			जारी;
		पूर्ण

		/* UM10944: The ENFPORT flag of the respective entry is
		 * cleared when a match is found. The host can use this
		 * flag as an acknowledgment.
		 */
		cpu_relax();
	पूर्ण जबतक (mgmt_route.enfport && --समयout);

	अगर (!समयout) अणु
		/* Clean up the management route so that a follow-up
		 * frame may not match on it by mistake.
		 * This is only hardware supported on P/Q/R/S - on E/T it is
		 * a no-op and we are silently discarding the -EOPNOTSUPP.
		 */
		sja1105_dynamic_config_ग_लिखो(priv, BLK_IDX_MGMT_ROUTE,
					     slot, &mgmt_route, false);
		dev_err_ratelimited(priv->ds->dev, "xmit timed out\n");
	पूर्ण

	वापस NETDEV_TX_OK;
पूर्ण

#घोषणा work_to_port(work) \
		container_of((work), काष्ठा sja1105_port, xmit_work)
#घोषणा tagger_to_sja1105(t) \
		container_of((t), काष्ठा sja1105_निजी, tagger_data)

/* Deferred work is unक्रमtunately necessary because setting up the management
 * route cannot be करोne from atomit context (SPI transfer takes a sleepable
 * lock on the bus)
 */
अटल व्योम sja1105_port_deferred_xmit(काष्ठा kthपढ़ो_work *work)
अणु
	काष्ठा sja1105_port *sp = work_to_port(work);
	काष्ठा sja1105_tagger_data *tagger_data = sp->data;
	काष्ठा sja1105_निजी *priv = tagger_to_sja1105(tagger_data);
	पूर्णांक port = sp - priv->ports;
	काष्ठा sk_buff *skb;

	जबतक ((skb = skb_dequeue(&sp->xmit_queue)) != शून्य) अणु
		काष्ठा sk_buff *clone = SJA1105_SKB_CB(skb)->clone;

		mutex_lock(&priv->mgmt_lock);

		sja1105_mgmt_xmit(priv->ds, port, 0, skb, !!clone);

		/* The clone, अगर there, was made by dsa_skb_tx_बारtamp */
		अगर (clone)
			sja1105_ptp_txtstamp_skb(priv->ds, port, clone);

		mutex_unlock(&priv->mgmt_lock);
	पूर्ण
पूर्ण

/* The MAXAGE setting beदीर्घs to the L2 Forwarding Parameters table,
 * which cannot be reconfigured at runसमय. So a चयन reset is required.
 */
अटल पूर्णांक sja1105_set_ageing_समय(काष्ठा dsa_चयन *ds,
				   अचिन्हित पूर्णांक ageing_समय)
अणु
	काष्ठा sja1105_l2_lookup_params_entry *l2_lookup_params;
	काष्ठा sja1105_निजी *priv = ds->priv;
	काष्ठा sja1105_table *table;
	अचिन्हित पूर्णांक maxage;

	table = &priv->अटल_config.tables[BLK_IDX_L2_LOOKUP_PARAMS];
	l2_lookup_params = table->entries;

	maxage = SJA1105_AGEING_TIME_MS(ageing_समय);

	अगर (l2_lookup_params->maxage == maxage)
		वापस 0;

	l2_lookup_params->maxage = maxage;

	वापस sja1105_अटल_config_reload(priv, SJA1105_AGEING_TIME);
पूर्ण

अटल पूर्णांक sja1105_change_mtu(काष्ठा dsa_चयन *ds, पूर्णांक port, पूर्णांक new_mtu)
अणु
	काष्ठा sja1105_l2_policing_entry *policing;
	काष्ठा sja1105_निजी *priv = ds->priv;

	new_mtu += VLAN_ETH_HLEN + ETH_FCS_LEN;

	अगर (dsa_is_cpu_port(ds, port))
		new_mtu += VLAN_HLEN;

	policing = priv->अटल_config.tables[BLK_IDX_L2_POLICING].entries;

	अगर (policing[port].maxlen == new_mtu)
		वापस 0;

	policing[port].maxlen = new_mtu;

	वापस sja1105_अटल_config_reload(priv, SJA1105_BEST_EFFORT_POLICING);
पूर्ण

अटल पूर्णांक sja1105_get_max_mtu(काष्ठा dsa_चयन *ds, पूर्णांक port)
अणु
	वापस 2043 - VLAN_ETH_HLEN - ETH_FCS_LEN;
पूर्ण

अटल पूर्णांक sja1105_port_setup_tc(काष्ठा dsa_चयन *ds, पूर्णांक port,
				 क्रमागत tc_setup_type type,
				 व्योम *type_data)
अणु
	चयन (type) अणु
	हाल TC_SETUP_QDISC_TAPRIO:
		वापस sja1105_setup_tc_taprio(ds, port, type_data);
	हाल TC_SETUP_QDISC_CBS:
		वापस sja1105_setup_tc_cbs(ds, port, type_data);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

/* We have a single mirror (@to) port, but can configure ingress and egress
 * mirroring on all other (@from) ports.
 * We need to allow mirroring rules only as दीर्घ as the @to port is always the
 * same, and we need to unset the @to port from mirr_port only when there is no
 * mirroring rule that references it.
 */
अटल पूर्णांक sja1105_mirror_apply(काष्ठा sja1105_निजी *priv, पूर्णांक from, पूर्णांक to,
				bool ingress, bool enabled)
अणु
	काष्ठा sja1105_general_params_entry *general_params;
	काष्ठा sja1105_mac_config_entry *mac;
	काष्ठा sja1105_table *table;
	bool alपढ़ोy_enabled;
	u64 new_mirr_port;
	पूर्णांक rc;

	table = &priv->अटल_config.tables[BLK_IDX_GENERAL_PARAMS];
	general_params = table->entries;

	mac = priv->अटल_config.tables[BLK_IDX_MAC_CONFIG].entries;

	alपढ़ोy_enabled = (general_params->mirr_port != SJA1105_NUM_PORTS);
	अगर (alपढ़ोy_enabled && enabled && general_params->mirr_port != to) अणु
		dev_err(priv->ds->dev,
			"Delete mirroring rules towards port %llu first\n",
			general_params->mirr_port);
		वापस -EBUSY;
	पूर्ण

	new_mirr_port = to;
	अगर (!enabled) अणु
		bool keep = false;
		पूर्णांक port;

		/* Anybody still referencing mirr_port? */
		क्रम (port = 0; port < SJA1105_NUM_PORTS; port++) अणु
			अगर (mac[port].ing_mirr || mac[port].egr_mirr) अणु
				keep = true;
				अवरोध;
			पूर्ण
		पूर्ण
		/* Unset alपढ़ोy_enabled क्रम next समय */
		अगर (!keep)
			new_mirr_port = SJA1105_NUM_PORTS;
	पूर्ण
	अगर (new_mirr_port != general_params->mirr_port) अणु
		general_params->mirr_port = new_mirr_port;

		rc = sja1105_dynamic_config_ग_लिखो(priv, BLK_IDX_GENERAL_PARAMS,
						  0, general_params, true);
		अगर (rc < 0)
			वापस rc;
	पूर्ण

	अगर (ingress)
		mac[from].ing_mirr = enabled;
	अन्यथा
		mac[from].egr_mirr = enabled;

	वापस sja1105_dynamic_config_ग_लिखो(priv, BLK_IDX_MAC_CONFIG, from,
					    &mac[from], true);
पूर्ण

अटल पूर्णांक sja1105_mirror_add(काष्ठा dsa_चयन *ds, पूर्णांक port,
			      काष्ठा dsa_mall_mirror_tc_entry *mirror,
			      bool ingress)
अणु
	वापस sja1105_mirror_apply(ds->priv, port, mirror->to_local_port,
				    ingress, true);
पूर्ण

अटल व्योम sja1105_mirror_del(काष्ठा dsa_चयन *ds, पूर्णांक port,
			       काष्ठा dsa_mall_mirror_tc_entry *mirror)
अणु
	sja1105_mirror_apply(ds->priv, port, mirror->to_local_port,
			     mirror->ingress, false);
पूर्ण

अटल पूर्णांक sja1105_port_policer_add(काष्ठा dsa_चयन *ds, पूर्णांक port,
				    काष्ठा dsa_mall_policer_tc_entry *policer)
अणु
	काष्ठा sja1105_l2_policing_entry *policing;
	काष्ठा sja1105_निजी *priv = ds->priv;

	policing = priv->अटल_config.tables[BLK_IDX_L2_POLICING].entries;

	/* In hardware, every 8 microseconds the credit level is incremented by
	 * the value of RATE bytes भागided by 64, up to a maximum of SMAX
	 * bytes.
	 */
	policing[port].rate = भाग_u64(512 * policer->rate_bytes_per_sec,
				      1000000);
	policing[port].smax = policer->burst;

	वापस sja1105_अटल_config_reload(priv, SJA1105_BEST_EFFORT_POLICING);
पूर्ण

अटल व्योम sja1105_port_policer_del(काष्ठा dsa_चयन *ds, पूर्णांक port)
अणु
	काष्ठा sja1105_l2_policing_entry *policing;
	काष्ठा sja1105_निजी *priv = ds->priv;

	policing = priv->अटल_config.tables[BLK_IDX_L2_POLICING].entries;

	policing[port].rate = SJA1105_RATE_MBPS(1000);
	policing[port].smax = 65535;

	sja1105_अटल_config_reload(priv, SJA1105_BEST_EFFORT_POLICING);
पूर्ण

अटल पूर्णांक sja1105_port_set_learning(काष्ठा sja1105_निजी *priv, पूर्णांक port,
				     bool enabled)
अणु
	काष्ठा sja1105_mac_config_entry *mac;
	पूर्णांक rc;

	mac = priv->अटल_config.tables[BLK_IDX_MAC_CONFIG].entries;

	mac[port].dyn_learn = enabled;

	rc = sja1105_dynamic_config_ग_लिखो(priv, BLK_IDX_MAC_CONFIG, port,
					  &mac[port], true);
	अगर (rc)
		वापस rc;

	अगर (enabled)
		priv->learn_ena |= BIT(port);
	अन्यथा
		priv->learn_ena &= ~BIT(port);

	वापस 0;
पूर्ण

अटल पूर्णांक sja1105_port_ucast_bcast_flood(काष्ठा sja1105_निजी *priv, पूर्णांक to,
					  काष्ठा चयनdev_brport_flags flags)
अणु
	अगर (flags.mask & BR_FLOOD) अणु
		अगर (flags.val & BR_FLOOD)
			priv->ucast_egress_floods |= BIT(to);
		अन्यथा
			priv->ucast_egress_floods &= ~BIT(to);
	पूर्ण

	अगर (flags.mask & BR_BCAST_FLOOD) अणु
		अगर (flags.val & BR_BCAST_FLOOD)
			priv->bcast_egress_floods |= BIT(to);
		अन्यथा
			priv->bcast_egress_floods &= ~BIT(to);
	पूर्ण

	वापस sja1105_manage_flood_करोमुख्यs(priv);
पूर्ण

अटल पूर्णांक sja1105_port_mcast_flood(काष्ठा sja1105_निजी *priv, पूर्णांक to,
				    काष्ठा चयनdev_brport_flags flags,
				    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा sja1105_l2_lookup_entry *l2_lookup;
	काष्ठा sja1105_table *table;
	पूर्णांक match;

	table = &priv->अटल_config.tables[BLK_IDX_L2_LOOKUP];
	l2_lookup = table->entries;

	क्रम (match = 0; match < table->entry_count; match++)
		अगर (l2_lookup[match].macaddr == SJA1105_UNKNOWN_MULTICAST &&
		    l2_lookup[match].mask_macaddr == SJA1105_UNKNOWN_MULTICAST)
			अवरोध;

	अगर (match == table->entry_count) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Could not find FDB entry for unknown multicast");
		वापस -ENOSPC;
	पूर्ण

	अगर (flags.val & BR_MCAST_FLOOD)
		l2_lookup[match].destports |= BIT(to);
	अन्यथा
		l2_lookup[match].destports &= ~BIT(to);

	वापस sja1105_dynamic_config_ग_लिखो(priv, BLK_IDX_L2_LOOKUP,
					    l2_lookup[match].index,
					    &l2_lookup[match],
					    true);
पूर्ण

अटल पूर्णांक sja1105_port_pre_bridge_flags(काष्ठा dsa_चयन *ds, पूर्णांक port,
					 काष्ठा चयनdev_brport_flags flags,
					 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा sja1105_निजी *priv = ds->priv;

	अगर (flags.mask & ~(BR_LEARNING | BR_FLOOD | BR_MCAST_FLOOD |
			   BR_BCAST_FLOOD))
		वापस -EINVAL;

	अगर (flags.mask & (BR_FLOOD | BR_MCAST_FLOOD) &&
	    !priv->info->can_limit_mcast_flood) अणु
		bool multicast = !!(flags.val & BR_MCAST_FLOOD);
		bool unicast = !!(flags.val & BR_FLOOD);

		अगर (unicast != multicast) अणु
			NL_SET_ERR_MSG_MOD(extack,
					   "This chip cannot configure multicast flooding independently of unicast");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sja1105_port_bridge_flags(काष्ठा dsa_चयन *ds, पूर्णांक port,
				     काष्ठा चयनdev_brport_flags flags,
				     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा sja1105_निजी *priv = ds->priv;
	पूर्णांक rc;

	अगर (flags.mask & BR_LEARNING) अणु
		bool learn_ena = !!(flags.val & BR_LEARNING);

		rc = sja1105_port_set_learning(priv, port, learn_ena);
		अगर (rc)
			वापस rc;
	पूर्ण

	अगर (flags.mask & (BR_FLOOD | BR_BCAST_FLOOD)) अणु
		rc = sja1105_port_ucast_bcast_flood(priv, port, flags);
		अगर (rc)
			वापस rc;
	पूर्ण

	/* For chips that can't offload BR_MCAST_FLOOD independently, there
	 * is nothing to करो here, we ensured the configuration is in sync by
	 * offloading BR_FLOOD.
	 */
	अगर (flags.mask & BR_MCAST_FLOOD && priv->info->can_limit_mcast_flood) अणु
		rc = sja1105_port_mcast_flood(priv, port, flags,
					      extack);
		अगर (rc)
			वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dsa_चयन_ops sja1105_चयन_ops = अणु
	.get_tag_protocol	= sja1105_get_tag_protocol,
	.setup			= sja1105_setup,
	.tearकरोwn		= sja1105_tearकरोwn,
	.set_ageing_समय	= sja1105_set_ageing_समय,
	.port_change_mtu	= sja1105_change_mtu,
	.port_max_mtu		= sja1105_get_max_mtu,
	.phylink_validate	= sja1105_phylink_validate,
	.phylink_mac_link_state	= sja1105_mac_pcs_get_state,
	.phylink_mac_config	= sja1105_mac_config,
	.phylink_mac_link_up	= sja1105_mac_link_up,
	.phylink_mac_link_करोwn	= sja1105_mac_link_करोwn,
	.get_strings		= sja1105_get_strings,
	.get_ethtool_stats	= sja1105_get_ethtool_stats,
	.get_sset_count		= sja1105_get_sset_count,
	.get_ts_info		= sja1105_get_ts_info,
	.port_disable		= sja1105_port_disable,
	.port_fdb_dump		= sja1105_fdb_dump,
	.port_fdb_add		= sja1105_fdb_add,
	.port_fdb_del		= sja1105_fdb_del,
	.port_bridge_join	= sja1105_bridge_join,
	.port_bridge_leave	= sja1105_bridge_leave,
	.port_pre_bridge_flags	= sja1105_port_pre_bridge_flags,
	.port_bridge_flags	= sja1105_port_bridge_flags,
	.port_stp_state_set	= sja1105_bridge_stp_state_set,
	.port_vlan_filtering	= sja1105_vlan_filtering,
	.port_vlan_add		= sja1105_vlan_add,
	.port_vlan_del		= sja1105_vlan_del,
	.port_mdb_add		= sja1105_mdb_add,
	.port_mdb_del		= sja1105_mdb_del,
	.port_hwtstamp_get	= sja1105_hwtstamp_get,
	.port_hwtstamp_set	= sja1105_hwtstamp_set,
	.port_rxtstamp		= sja1105_port_rxtstamp,
	.port_txtstamp		= sja1105_port_txtstamp,
	.port_setup_tc		= sja1105_port_setup_tc,
	.port_mirror_add	= sja1105_mirror_add,
	.port_mirror_del	= sja1105_mirror_del,
	.port_policer_add	= sja1105_port_policer_add,
	.port_policer_del	= sja1105_port_policer_del,
	.cls_flower_add		= sja1105_cls_flower_add,
	.cls_flower_del		= sja1105_cls_flower_del,
	.cls_flower_stats	= sja1105_cls_flower_stats,
	.crosschip_bridge_join	= sja1105_crosschip_bridge_join,
	.crosschip_bridge_leave	= sja1105_crosschip_bridge_leave,
	.devlink_param_get	= sja1105_devlink_param_get,
	.devlink_param_set	= sja1105_devlink_param_set,
	.devlink_info_get	= sja1105_devlink_info_get,
पूर्ण;

अटल स्थिर काष्ठा of_device_id sja1105_dt_ids[];

अटल पूर्णांक sja1105_check_device_id(काष्ठा sja1105_निजी *priv)
अणु
	स्थिर काष्ठा sja1105_regs *regs = priv->info->regs;
	u8 prod_id[SJA1105_SIZE_DEVICE_ID] = अणु0पूर्ण;
	काष्ठा device *dev = &priv->spidev->dev;
	स्थिर काष्ठा of_device_id *match;
	u32 device_id;
	u64 part_no;
	पूर्णांक rc;

	rc = sja1105_xfer_u32(priv, SPI_READ, regs->device_id, &device_id,
			      शून्य);
	अगर (rc < 0)
		वापस rc;

	rc = sja1105_xfer_buf(priv, SPI_READ, regs->prod_id, prod_id,
			      SJA1105_SIZE_DEVICE_ID);
	अगर (rc < 0)
		वापस rc;

	sja1105_unpack(prod_id, &part_no, 19, 4, SJA1105_SIZE_DEVICE_ID);

	क्रम (match = sja1105_dt_ids; match->compatible[0]; match++) अणु
		स्थिर काष्ठा sja1105_info *info = match->data;

		/* Is what's been probed in our match table at all? */
		अगर (info->device_id != device_id || info->part_no != part_no)
			जारी;

		/* But is it what's in the device tree? */
		अगर (priv->info->device_id != device_id ||
		    priv->info->part_no != part_no) अणु
			dev_warn(dev, "Device tree specifies chip %s but found %s, please fix it!\n",
				 priv->info->name, info->name);
			/* It isn't. No problem, pick that up. */
			priv->info = info;
		पूर्ण

		वापस 0;
	पूर्ण

	dev_err(dev, "Unexpected {device ID, part number}: 0x%x 0x%llx\n",
		device_id, part_no);

	वापस -ENODEV;
पूर्ण

अटल पूर्णांक sja1105_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा sja1105_tagger_data *tagger_data;
	काष्ठा device *dev = &spi->dev;
	काष्ठा sja1105_निजी *priv;
	काष्ठा dsa_चयन *ds;
	पूर्णांक rc, port;

	अगर (!dev->of_node) अणु
		dev_err(dev, "No DTS bindings for SJA1105 driver\n");
		वापस -EINVAL;
	पूर्ण

	priv = devm_kzalloc(dev, माप(काष्ठा sja1105_निजी), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	/* Configure the optional reset pin and bring up चयन */
	priv->reset_gpio = devm_gpiod_get(dev, "reset", GPIOD_OUT_HIGH);
	अगर (IS_ERR(priv->reset_gpio))
		dev_dbg(dev, "reset-gpios not defined, ignoring\n");
	अन्यथा
		sja1105_hw_reset(priv->reset_gpio, 1, 1);

	/* Populate our driver निजी काष्ठाure (priv) based on
	 * the device tree node that was probed (spi)
	 */
	priv->spidev = spi;
	spi_set_drvdata(spi, priv);

	/* Configure the SPI bus */
	spi->bits_per_word = 8;
	rc = spi_setup(spi);
	अगर (rc < 0) अणु
		dev_err(dev, "Could not init SPI\n");
		वापस rc;
	पूर्ण

	priv->info = of_device_get_match_data(dev);

	/* Detect hardware device */
	rc = sja1105_check_device_id(priv);
	अगर (rc < 0) अणु
		dev_err(dev, "Device ID check failed: %d\n", rc);
		वापस rc;
	पूर्ण

	dev_info(dev, "Probed switch chip: %s\n", priv->info->name);

	ds = devm_kzalloc(dev, माप(*ds), GFP_KERNEL);
	अगर (!ds)
		वापस -ENOMEM;

	ds->dev = dev;
	ds->num_ports = SJA1105_NUM_PORTS;
	ds->ops = &sja1105_चयन_ops;
	ds->priv = priv;
	priv->ds = ds;

	tagger_data = &priv->tagger_data;

	mutex_init(&priv->ptp_data.lock);
	mutex_init(&priv->mgmt_lock);

	priv->dsa_8021q_ctx = devm_kzalloc(dev, माप(*priv->dsa_8021q_ctx),
					   GFP_KERNEL);
	अगर (!priv->dsa_8021q_ctx)
		वापस -ENOMEM;

	priv->dsa_8021q_ctx->ops = &sja1105_dsa_8021q_ops;
	priv->dsa_8021q_ctx->proto = htons(ETH_P_8021Q);
	priv->dsa_8021q_ctx->ds = ds;

	INIT_LIST_HEAD(&priv->dsa_8021q_ctx->crosschip_links);
	INIT_LIST_HEAD(&priv->bridge_vlans);
	INIT_LIST_HEAD(&priv->dsa_8021q_vlans);

	sja1105_tas_setup(ds);
	sja1105_flower_setup(ds);

	rc = dsa_रेजिस्टर_चयन(priv->ds);
	अगर (rc)
		वापस rc;

	अगर (IS_ENABLED(CONFIG_NET_SCH_CBS)) अणु
		priv->cbs = devm_kसुस्मृति(dev, priv->info->num_cbs_shapers,
					 माप(काष्ठा sja1105_cbs_entry),
					 GFP_KERNEL);
		अगर (!priv->cbs) अणु
			rc = -ENOMEM;
			जाओ out_unरेजिस्टर_चयन;
		पूर्ण
	पूर्ण

	/* Connections between dsa_port and sja1105_port */
	क्रम (port = 0; port < SJA1105_NUM_PORTS; port++) अणु
		काष्ठा sja1105_port *sp = &priv->ports[port];
		काष्ठा dsa_port *dp = dsa_to_port(ds, port);
		काष्ठा net_device *slave;
		पूर्णांक subvlan;

		अगर (!dsa_is_user_port(ds, port))
			जारी;

		dp->priv = sp;
		sp->dp = dp;
		sp->data = tagger_data;
		slave = dp->slave;
		kthपढ़ो_init_work(&sp->xmit_work, sja1105_port_deferred_xmit);
		sp->xmit_worker = kthपढ़ो_create_worker(0, "%s_xmit",
							slave->name);
		अगर (IS_ERR(sp->xmit_worker)) अणु
			rc = PTR_ERR(sp->xmit_worker);
			dev_err(ds->dev,
				"failed to create deferred xmit thread: %d\n",
				rc);
			जाओ out_destroy_workers;
		पूर्ण
		skb_queue_head_init(&sp->xmit_queue);
		sp->xmit_tpid = ETH_P_SJA1105;

		क्रम (subvlan = 0; subvlan < DSA_8021Q_N_SUBVLAN; subvlan++)
			sp->subvlan_map[subvlan] = VLAN_N_VID;
	पूर्ण

	वापस 0;

out_destroy_workers:
	जबतक (port-- > 0) अणु
		काष्ठा sja1105_port *sp = &priv->ports[port];

		अगर (!dsa_is_user_port(ds, port))
			जारी;

		kthपढ़ो_destroy_worker(sp->xmit_worker);
	पूर्ण

out_unरेजिस्टर_चयन:
	dsa_unरेजिस्टर_चयन(ds);

	वापस rc;
पूर्ण

अटल पूर्णांक sja1105_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा sja1105_निजी *priv = spi_get_drvdata(spi);

	dsa_unरेजिस्टर_चयन(priv->ds);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id sja1105_dt_ids[] = अणु
	अणु .compatible = "nxp,sja1105e", .data = &sja1105e_info पूर्ण,
	अणु .compatible = "nxp,sja1105t", .data = &sja1105t_info पूर्ण,
	अणु .compatible = "nxp,sja1105p", .data = &sja1105p_info पूर्ण,
	अणु .compatible = "nxp,sja1105q", .data = &sja1105q_info पूर्ण,
	अणु .compatible = "nxp,sja1105r", .data = &sja1105r_info पूर्ण,
	अणु .compatible = "nxp,sja1105s", .data = &sja1105s_info पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sja1105_dt_ids);

अटल काष्ठा spi_driver sja1105_driver = अणु
	.driver = अणु
		.name  = "sja1105",
		.owner = THIS_MODULE,
		.of_match_table = of_match_ptr(sja1105_dt_ids),
	पूर्ण,
	.probe  = sja1105_probe,
	.हटाओ = sja1105_हटाओ,
पूर्ण;

module_spi_driver(sja1105_driver);

MODULE_AUTHOR("Vladimir Oltean <olteanv@gmail.com>");
MODULE_AUTHOR("Georg Waibel <georg.waibel@sensor-technik.de>");
MODULE_DESCRIPTION("SJA1105 Driver");
MODULE_LICENSE("GPL v2");
