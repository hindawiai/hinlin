<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR MIT)
/*
 * Microsemi Ocelot Switch driver
 *
 * Copyright (c) 2017 Microsemi Corporation
 */
#समावेश <linux/dsa/ocelot.h>
#समावेश <linux/अगर_bridge.h>
#समावेश <linux/ptp_classअगरy.h>
#समावेश <soc/mscc/ocelot_vcap.h>
#समावेश "ocelot.h"
#समावेश "ocelot_vcap.h"

#घोषणा TABLE_UPDATE_SLEEP_US 10
#घोषणा TABLE_UPDATE_TIMEOUT_US 100000

काष्ठा ocelot_mact_entry अणु
	u8 mac[ETH_ALEN];
	u16 vid;
	क्रमागत macaccess_entry_type type;
पूर्ण;

अटल अंतरभूत u32 ocelot_mact_पढ़ो_macaccess(काष्ठा ocelot *ocelot)
अणु
	वापस ocelot_पढ़ो(ocelot, ANA_TABLES_MACACCESS);
पूर्ण

अटल अंतरभूत पूर्णांक ocelot_mact_रुको_क्रम_completion(काष्ठा ocelot *ocelot)
अणु
	u32 val;

	वापस पढ़ोx_poll_समयout(ocelot_mact_पढ़ो_macaccess,
		ocelot, val,
		(val & ANA_TABLES_MACACCESS_MAC_TABLE_CMD_M) ==
		MACACCESS_CMD_IDLE,
		TABLE_UPDATE_SLEEP_US, TABLE_UPDATE_TIMEOUT_US);
पूर्ण

अटल व्योम ocelot_mact_select(काष्ठा ocelot *ocelot,
			       स्थिर अचिन्हित अक्षर mac[ETH_ALEN],
			       अचिन्हित पूर्णांक vid)
अणु
	u32 macl = 0, mach = 0;

	/* Set the MAC address to handle and the vlan associated in a क्रमmat
	 * understood by the hardware.
	 */
	mach |= vid    << 16;
	mach |= mac[0] << 8;
	mach |= mac[1] << 0;
	macl |= mac[2] << 24;
	macl |= mac[3] << 16;
	macl |= mac[4] << 8;
	macl |= mac[5] << 0;

	ocelot_ग_लिखो(ocelot, macl, ANA_TABLES_MACLDATA);
	ocelot_ग_लिखो(ocelot, mach, ANA_TABLES_MACHDATA);

पूर्ण

पूर्णांक ocelot_mact_learn(काष्ठा ocelot *ocelot, पूर्णांक port,
		      स्थिर अचिन्हित अक्षर mac[ETH_ALEN],
		      अचिन्हित पूर्णांक vid, क्रमागत macaccess_entry_type type)
अणु
	u32 cmd = ANA_TABLES_MACACCESS_VALID |
		ANA_TABLES_MACACCESS_DEST_IDX(port) |
		ANA_TABLES_MACACCESS_ENTRYTYPE(type) |
		ANA_TABLES_MACACCESS_MAC_TABLE_CMD(MACACCESS_CMD_LEARN);
	अचिन्हित पूर्णांक mc_ports;

	/* Set MAC_CPU_COPY अगर the CPU port is used by a multicast entry */
	अगर (type == ENTRYTYPE_MACv4)
		mc_ports = (mac[1] << 8) | mac[2];
	अन्यथा अगर (type == ENTRYTYPE_MACv6)
		mc_ports = (mac[0] << 8) | mac[1];
	अन्यथा
		mc_ports = 0;

	अगर (mc_ports & BIT(ocelot->num_phys_ports))
		cmd |= ANA_TABLES_MACACCESS_MAC_CPU_COPY;

	ocelot_mact_select(ocelot, mac, vid);

	/* Issue a ग_लिखो command */
	ocelot_ग_लिखो(ocelot, cmd, ANA_TABLES_MACACCESS);

	वापस ocelot_mact_रुको_क्रम_completion(ocelot);
पूर्ण
EXPORT_SYMBOL(ocelot_mact_learn);

पूर्णांक ocelot_mact_क्रमget(काष्ठा ocelot *ocelot,
		       स्थिर अचिन्हित अक्षर mac[ETH_ALEN], अचिन्हित पूर्णांक vid)
अणु
	ocelot_mact_select(ocelot, mac, vid);

	/* Issue a क्रमget command */
	ocelot_ग_लिखो(ocelot,
		     ANA_TABLES_MACACCESS_MAC_TABLE_CMD(MACACCESS_CMD_FORGET),
		     ANA_TABLES_MACACCESS);

	वापस ocelot_mact_रुको_क्रम_completion(ocelot);
पूर्ण
EXPORT_SYMBOL(ocelot_mact_क्रमget);

अटल व्योम ocelot_mact_init(काष्ठा ocelot *ocelot)
अणु
	/* Configure the learning mode entries attributes:
	 * - Do not copy the frame to the CPU extraction queues.
	 * - Use the vlan and mac_cpoy क्रम dmac lookup.
	 */
	ocelot_rmw(ocelot, 0,
		   ANA_AGENCTRL_LEARN_CPU_COPY | ANA_AGENCTRL_IGNORE_DMAC_FLAGS
		   | ANA_AGENCTRL_LEARN_FWD_KILL
		   | ANA_AGENCTRL_LEARN_IGNORE_VLAN,
		   ANA_AGENCTRL);

	/* Clear the MAC table */
	ocelot_ग_लिखो(ocelot, MACACCESS_CMD_INIT, ANA_TABLES_MACACCESS);
पूर्ण

अटल व्योम ocelot_vcap_enable(काष्ठा ocelot *ocelot, पूर्णांक port)
अणु
	ocelot_ग_लिखो_gix(ocelot, ANA_PORT_VCAP_S2_CFG_S2_ENA |
			 ANA_PORT_VCAP_S2_CFG_S2_IP6_CFG(0xa),
			 ANA_PORT_VCAP_S2_CFG, port);

	ocelot_ग_लिखो_gix(ocelot, ANA_PORT_VCAP_CFG_S1_ENA,
			 ANA_PORT_VCAP_CFG, port);

	ocelot_rmw_gix(ocelot, REW_PORT_CFG_ES0_EN,
		       REW_PORT_CFG_ES0_EN,
		       REW_PORT_CFG, port);
पूर्ण

अटल अंतरभूत u32 ocelot_vlant_पढ़ो_vlanaccess(काष्ठा ocelot *ocelot)
अणु
	वापस ocelot_पढ़ो(ocelot, ANA_TABLES_VLANACCESS);
पूर्ण

अटल अंतरभूत पूर्णांक ocelot_vlant_रुको_क्रम_completion(काष्ठा ocelot *ocelot)
अणु
	u32 val;

	वापस पढ़ोx_poll_समयout(ocelot_vlant_पढ़ो_vlanaccess,
		ocelot,
		val,
		(val & ANA_TABLES_VLANACCESS_VLAN_TBL_CMD_M) ==
		ANA_TABLES_VLANACCESS_CMD_IDLE,
		TABLE_UPDATE_SLEEP_US, TABLE_UPDATE_TIMEOUT_US);
पूर्ण

अटल पूर्णांक ocelot_vlant_set_mask(काष्ठा ocelot *ocelot, u16 vid, u32 mask)
अणु
	/* Select the VID to configure */
	ocelot_ग_लिखो(ocelot, ANA_TABLES_VLANTIDX_V_INDEX(vid),
		     ANA_TABLES_VLANTIDX);
	/* Set the vlan port members mask and issue a ग_लिखो command */
	ocelot_ग_लिखो(ocelot, ANA_TABLES_VLANACCESS_VLAN_PORT_MASK(mask) |
			     ANA_TABLES_VLANACCESS_CMD_WRITE,
		     ANA_TABLES_VLANACCESS);

	वापस ocelot_vlant_रुको_क्रम_completion(ocelot);
पूर्ण

अटल व्योम ocelot_port_set_native_vlan(काष्ठा ocelot *ocelot, पूर्णांक port,
					काष्ठा ocelot_vlan native_vlan)
अणु
	काष्ठा ocelot_port *ocelot_port = ocelot->ports[port];
	u32 val = 0;

	ocelot_port->native_vlan = native_vlan;

	ocelot_rmw_gix(ocelot, REW_PORT_VLAN_CFG_PORT_VID(native_vlan.vid),
		       REW_PORT_VLAN_CFG_PORT_VID_M,
		       REW_PORT_VLAN_CFG, port);

	अगर (ocelot_port->vlan_aware) अणु
		अगर (native_vlan.valid)
			/* Tag all frames except when VID == DEFAULT_VLAN */
			val = REW_TAG_CFG_TAG_CFG(1);
		अन्यथा
			/* Tag all frames */
			val = REW_TAG_CFG_TAG_CFG(3);
	पूर्ण अन्यथा अणु
		/* Port tagging disabled. */
		val = REW_TAG_CFG_TAG_CFG(0);
	पूर्ण
	ocelot_rmw_gix(ocelot, val,
		       REW_TAG_CFG_TAG_CFG_M,
		       REW_TAG_CFG, port);
पूर्ण

/* Default vlan to clasअगरy क्रम untagged frames (may be zero) */
अटल व्योम ocelot_port_set_pvid(काष्ठा ocelot *ocelot, पूर्णांक port,
				 काष्ठा ocelot_vlan pvid_vlan)
अणु
	काष्ठा ocelot_port *ocelot_port = ocelot->ports[port];
	u32 val = 0;

	ocelot_port->pvid_vlan = pvid_vlan;

	अगर (!ocelot_port->vlan_aware)
		pvid_vlan.vid = 0;

	ocelot_rmw_gix(ocelot,
		       ANA_PORT_VLAN_CFG_VLAN_VID(pvid_vlan.vid),
		       ANA_PORT_VLAN_CFG_VLAN_VID_M,
		       ANA_PORT_VLAN_CFG, port);

	/* If there's no pvid, we should drop not only untagged traffic (which
	 * happens स्वतःmatically), but also 802.1p traffic which माला_लो
	 * classअगरied to VLAN 0, but that is always in our RX filter, so it
	 * would get accepted were it not क्रम this setting.
	 */
	अगर (!pvid_vlan.valid && ocelot_port->vlan_aware)
		val = ANA_PORT_DROP_CFG_DROP_PRIO_S_TAGGED_ENA |
		      ANA_PORT_DROP_CFG_DROP_PRIO_C_TAGGED_ENA;

	ocelot_rmw_gix(ocelot, val,
		       ANA_PORT_DROP_CFG_DROP_PRIO_S_TAGGED_ENA |
		       ANA_PORT_DROP_CFG_DROP_PRIO_C_TAGGED_ENA,
		       ANA_PORT_DROP_CFG, port);
पूर्ण

पूर्णांक ocelot_port_vlan_filtering(काष्ठा ocelot *ocelot, पूर्णांक port,
			       bool vlan_aware)
अणु
	काष्ठा ocelot_vcap_block *block = &ocelot->block[VCAP_IS1];
	काष्ठा ocelot_port *ocelot_port = ocelot->ports[port];
	काष्ठा ocelot_vcap_filter *filter;
	u32 val;

	list_क्रम_each_entry(filter, &block->rules, list) अणु
		अगर (filter->ingress_port_mask & BIT(port) &&
		    filter->action.vid_replace_ena) अणु
			dev_err(ocelot->dev,
				"Cannot change VLAN state with vlan modify rules active\n");
			वापस -EBUSY;
		पूर्ण
	पूर्ण

	ocelot_port->vlan_aware = vlan_aware;

	अगर (vlan_aware)
		val = ANA_PORT_VLAN_CFG_VLAN_AWARE_ENA |
		      ANA_PORT_VLAN_CFG_VLAN_POP_CNT(1);
	अन्यथा
		val = 0;
	ocelot_rmw_gix(ocelot, val,
		       ANA_PORT_VLAN_CFG_VLAN_AWARE_ENA |
		       ANA_PORT_VLAN_CFG_VLAN_POP_CNT_M,
		       ANA_PORT_VLAN_CFG, port);

	ocelot_port_set_pvid(ocelot, port, ocelot_port->pvid_vlan);
	ocelot_port_set_native_vlan(ocelot, port, ocelot_port->native_vlan);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ocelot_port_vlan_filtering);

पूर्णांक ocelot_vlan_prepare(काष्ठा ocelot *ocelot, पूर्णांक port, u16 vid, bool pvid,
			bool untagged)
अणु
	काष्ठा ocelot_port *ocelot_port = ocelot->ports[port];

	/* Deny changing the native VLAN, but always permit deleting it */
	अगर (untagged && ocelot_port->native_vlan.vid != vid &&
	    ocelot_port->native_vlan.valid) अणु
		dev_err(ocelot->dev,
			"Port already has a native VLAN: %d\n",
			ocelot_port->native_vlan.vid);
		वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ocelot_vlan_prepare);

पूर्णांक ocelot_vlan_add(काष्ठा ocelot *ocelot, पूर्णांक port, u16 vid, bool pvid,
		    bool untagged)
अणु
	पूर्णांक ret;

	/* Make the port a member of the VLAN */
	ocelot->vlan_mask[vid] |= BIT(port);
	ret = ocelot_vlant_set_mask(ocelot, vid, ocelot->vlan_mask[vid]);
	अगर (ret)
		वापस ret;

	/* Default ingress vlan classअगरication */
	अगर (pvid) अणु
		काष्ठा ocelot_vlan pvid_vlan;

		pvid_vlan.vid = vid;
		pvid_vlan.valid = true;
		ocelot_port_set_pvid(ocelot, port, pvid_vlan);
	पूर्ण

	/* Untagged egress vlan clasअगरication */
	अगर (untagged) अणु
		काष्ठा ocelot_vlan native_vlan;

		native_vlan.vid = vid;
		native_vlan.valid = true;
		ocelot_port_set_native_vlan(ocelot, port, native_vlan);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ocelot_vlan_add);

पूर्णांक ocelot_vlan_del(काष्ठा ocelot *ocelot, पूर्णांक port, u16 vid)
अणु
	काष्ठा ocelot_port *ocelot_port = ocelot->ports[port];
	पूर्णांक ret;

	/* Stop the port from being a member of the vlan */
	ocelot->vlan_mask[vid] &= ~BIT(port);
	ret = ocelot_vlant_set_mask(ocelot, vid, ocelot->vlan_mask[vid]);
	अगर (ret)
		वापस ret;

	/* Ingress */
	अगर (ocelot_port->pvid_vlan.vid == vid) अणु
		काष्ठा ocelot_vlan pvid_vlan = अणु0पूर्ण;

		ocelot_port_set_pvid(ocelot, port, pvid_vlan);
	पूर्ण

	/* Egress */
	अगर (ocelot_port->native_vlan.vid == vid) अणु
		काष्ठा ocelot_vlan native_vlan = अणु0पूर्ण;

		ocelot_port_set_native_vlan(ocelot, port, native_vlan);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ocelot_vlan_del);

अटल व्योम ocelot_vlan_init(काष्ठा ocelot *ocelot)
अणु
	u16 port, vid;

	/* Clear VLAN table, by शेष all ports are members of all VLANs */
	ocelot_ग_लिखो(ocelot, ANA_TABLES_VLANACCESS_CMD_INIT,
		     ANA_TABLES_VLANACCESS);
	ocelot_vlant_रुको_क्रम_completion(ocelot);

	/* Configure the port VLAN memberships */
	क्रम (vid = 1; vid < VLAN_N_VID; vid++) अणु
		ocelot->vlan_mask[vid] = 0;
		ocelot_vlant_set_mask(ocelot, vid, ocelot->vlan_mask[vid]);
	पूर्ण

	/* Because VLAN filtering is enabled, we need VID 0 to get untagged
	 * traffic.  It is added स्वतःmatically अगर 8021q module is loaded, but
	 * we can't rely on it since module may be not loaded.
	 */
	ocelot->vlan_mask[0] = GENMASK(ocelot->num_phys_ports - 1, 0);
	ocelot_vlant_set_mask(ocelot, 0, ocelot->vlan_mask[0]);

	/* Set vlan ingress filter mask to all ports but the CPU port by
	 * शेष.
	 */
	ocelot_ग_लिखो(ocelot, GENMASK(ocelot->num_phys_ports - 1, 0),
		     ANA_VLANMASK);

	क्रम (port = 0; port < ocelot->num_phys_ports; port++) अणु
		ocelot_ग_लिखो_gix(ocelot, 0, REW_PORT_VLAN_CFG, port);
		ocelot_ग_लिखो_gix(ocelot, 0, REW_TAG_CFG, port);
	पूर्ण
पूर्ण

अटल u32 ocelot_पढ़ो_eq_avail(काष्ठा ocelot *ocelot, पूर्णांक port)
अणु
	वापस ocelot_पढ़ो_rix(ocelot, QSYS_SW_STATUS, port);
पूर्ण

पूर्णांक ocelot_port_flush(काष्ठा ocelot *ocelot, पूर्णांक port)
अणु
	अचिन्हित पूर्णांक छोड़ो_ena;
	पूर्णांक err, val;

	/* Disable dequeuing from the egress queues */
	ocelot_rmw_rix(ocelot, QSYS_PORT_MODE_DEQUEUE_DIS,
		       QSYS_PORT_MODE_DEQUEUE_DIS,
		       QSYS_PORT_MODE, port);

	/* Disable flow control */
	ocelot_fields_पढ़ो(ocelot, port, SYS_PAUSE_CFG_PAUSE_ENA, &छोड़ो_ena);
	ocelot_fields_ग_लिखो(ocelot, port, SYS_PAUSE_CFG_PAUSE_ENA, 0);

	/* Disable priority flow control */
	ocelot_fields_ग_लिखो(ocelot, port,
			    QSYS_SWITCH_PORT_MODE_TX_PFC_ENA, 0);

	/* Wait at least the समय it takes to receive a frame of maximum length
	 * at the port.
	 * Worst-हाल delays क्रम 10 kilobyte jumbo frames are:
	 * 8 ms on a 10M port
	 * 800 Nञs on a 100M port
	 * 80 Nञs on a 1G port
	 * 32 Nञs on a 2.5G port
	 */
	usleep_range(8000, 10000);

	/* Disable half duplex backpressure. */
	ocelot_rmw_rix(ocelot, 0, SYS_FRONT_PORT_MODE_HDX_MODE,
		       SYS_FRONT_PORT_MODE, port);

	/* Flush the queues associated with the port. */
	ocelot_rmw_gix(ocelot, REW_PORT_CFG_FLUSH_ENA, REW_PORT_CFG_FLUSH_ENA,
		       REW_PORT_CFG, port);

	/* Enable dequeuing from the egress queues. */
	ocelot_rmw_rix(ocelot, 0, QSYS_PORT_MODE_DEQUEUE_DIS, QSYS_PORT_MODE,
		       port);

	/* Wait until flushing is complete. */
	err = पढ़ो_poll_समयout(ocelot_पढ़ो_eq_avail, val, !val,
				100, 2000000, false, ocelot, port);

	/* Clear flushing again. */
	ocelot_rmw_gix(ocelot, 0, REW_PORT_CFG_FLUSH_ENA, REW_PORT_CFG, port);

	/* Re-enable flow control */
	ocelot_fields_ग_लिखो(ocelot, port, SYS_PAUSE_CFG_PAUSE_ENA, छोड़ो_ena);

	वापस err;
पूर्ण
EXPORT_SYMBOL(ocelot_port_flush);

व्योम ocelot_adjust_link(काष्ठा ocelot *ocelot, पूर्णांक port,
			काष्ठा phy_device *phydev)
अणु
	काष्ठा ocelot_port *ocelot_port = ocelot->ports[port];
	पूर्णांक speed, mode = 0;

	चयन (phydev->speed) अणु
	हाल SPEED_10:
		speed = OCELOT_SPEED_10;
		अवरोध;
	हाल SPEED_100:
		speed = OCELOT_SPEED_100;
		अवरोध;
	हाल SPEED_1000:
		speed = OCELOT_SPEED_1000;
		mode = DEV_MAC_MODE_CFG_GIGA_MODE_ENA;
		अवरोध;
	हाल SPEED_2500:
		speed = OCELOT_SPEED_2500;
		mode = DEV_MAC_MODE_CFG_GIGA_MODE_ENA;
		अवरोध;
	शेष:
		dev_err(ocelot->dev, "Unsupported PHY speed on port %d: %d\n",
			port, phydev->speed);
		वापस;
	पूर्ण

	phy_prपूर्णांक_status(phydev);

	अगर (!phydev->link)
		वापस;

	/* Only full duplex supported क्रम now */
	ocelot_port_ग_लिखोl(ocelot_port, DEV_MAC_MODE_CFG_FDX_ENA |
			   mode, DEV_MAC_MODE_CFG);

	/* Disable HDX fast control */
	ocelot_port_ग_लिखोl(ocelot_port, DEV_PORT_MISC_HDX_FAST_DIS,
			   DEV_PORT_MISC);

	/* SGMII only क्रम now */
	ocelot_port_ग_लिखोl(ocelot_port, PCS1G_MODE_CFG_SGMII_MODE_ENA,
			   PCS1G_MODE_CFG);
	ocelot_port_ग_लिखोl(ocelot_port, PCS1G_SD_CFG_SD_SEL, PCS1G_SD_CFG);

	/* Enable PCS */
	ocelot_port_ग_लिखोl(ocelot_port, PCS1G_CFG_PCS_ENA, PCS1G_CFG);

	/* No aneg on SGMII */
	ocelot_port_ग_लिखोl(ocelot_port, 0, PCS1G_ANEG_CFG);

	/* No loopback */
	ocelot_port_ग_लिखोl(ocelot_port, 0, PCS1G_LB_CFG);

	/* Enable MAC module */
	ocelot_port_ग_लिखोl(ocelot_port, DEV_MAC_ENA_CFG_RX_ENA |
			   DEV_MAC_ENA_CFG_TX_ENA, DEV_MAC_ENA_CFG);

	/* Take MAC, Port, Phy (पूर्णांकern) and PCS (SGMII/Serdes) घड़ी out of
	 * reset
	 */
	ocelot_port_ग_लिखोl(ocelot_port, DEV_CLOCK_CFG_LINK_SPEED(speed),
			   DEV_CLOCK_CFG);

	/* No PFC */
	ocelot_ग_लिखो_gix(ocelot, ANA_PFC_PFC_CFG_FC_LINK_SPEED(speed),
			 ANA_PFC_PFC_CFG, port);

	/* Core: Enable port क्रम frame transfer */
	ocelot_fields_ग_लिखो(ocelot, port,
			    QSYS_SWITCH_PORT_MODE_PORT_ENA, 1);

	/* Flow control */
	ocelot_ग_लिखो_rix(ocelot, SYS_MAC_FC_CFG_PAUSE_VAL_CFG(0xffff) |
			 SYS_MAC_FC_CFG_RX_FC_ENA | SYS_MAC_FC_CFG_TX_FC_ENA |
			 SYS_MAC_FC_CFG_ZERO_PAUSE_ENA |
			 SYS_MAC_FC_CFG_FC_LATENCY_CFG(0x7) |
			 SYS_MAC_FC_CFG_FC_LINK_SPEED(speed),
			 SYS_MAC_FC_CFG, port);
	ocelot_ग_लिखो_rix(ocelot, 0, ANA_POL_FLOWC, port);
पूर्ण
EXPORT_SYMBOL(ocelot_adjust_link);

व्योम ocelot_port_enable(काष्ठा ocelot *ocelot, पूर्णांक port,
			काष्ठा phy_device *phy)
अणु
	/* Enable receiving frames on the port, and activate स्वतः-learning of
	 * MAC addresses.
	 */
	ocelot_ग_लिखो_gix(ocelot, ANA_PORT_PORT_CFG_LEARNAUTO |
			 ANA_PORT_PORT_CFG_RECV_ENA |
			 ANA_PORT_PORT_CFG_PORTID_VAL(port),
			 ANA_PORT_PORT_CFG, port);
पूर्ण
EXPORT_SYMBOL(ocelot_port_enable);

व्योम ocelot_port_disable(काष्ठा ocelot *ocelot, पूर्णांक port)
अणु
	काष्ठा ocelot_port *ocelot_port = ocelot->ports[port];

	ocelot_port_ग_लिखोl(ocelot_port, 0, DEV_MAC_ENA_CFG);
	ocelot_fields_ग_लिखो(ocelot, port, QSYS_SWITCH_PORT_MODE_PORT_ENA, 0);
पूर्ण
EXPORT_SYMBOL(ocelot_port_disable);

अटल व्योम ocelot_port_add_txtstamp_skb(काष्ठा ocelot *ocelot, पूर्णांक port,
					 काष्ठा sk_buff *clone)
अणु
	काष्ठा ocelot_port *ocelot_port = ocelot->ports[port];

	spin_lock(&ocelot_port->ts_id_lock);

	skb_shinfo(clone)->tx_flags |= SKBTX_IN_PROGRESS;
	/* Store बारtamp ID in OCELOT_SKB_CB(clone)->ts_id */
	OCELOT_SKB_CB(clone)->ts_id = ocelot_port->ts_id;
	ocelot_port->ts_id = (ocelot_port->ts_id + 1) % 4;
	skb_queue_tail(&ocelot_port->tx_skbs, clone);

	spin_unlock(&ocelot_port->ts_id_lock);
पूर्ण

u32 ocelot_ptp_rew_op(काष्ठा sk_buff *skb)
अणु
	काष्ठा sk_buff *clone = OCELOT_SKB_CB(skb)->clone;
	u8 ptp_cmd = OCELOT_SKB_CB(skb)->ptp_cmd;
	u32 rew_op = 0;

	अगर (ptp_cmd == IFH_REW_OP_TWO_STEP_PTP && clone) अणु
		rew_op = ptp_cmd;
		rew_op |= OCELOT_SKB_CB(clone)->ts_id << 3;
	पूर्ण अन्यथा अगर (ptp_cmd == IFH_REW_OP_ORIGIN_PTP) अणु
		rew_op = ptp_cmd;
	पूर्ण

	वापस rew_op;
पूर्ण
EXPORT_SYMBOL(ocelot_ptp_rew_op);

अटल bool ocelot_ptp_is_onestep_sync(काष्ठा sk_buff *skb)
अणु
	काष्ठा ptp_header *hdr;
	अचिन्हित पूर्णांक ptp_class;
	u8 msgtype, twostep;

	ptp_class = ptp_classअगरy_raw(skb);
	अगर (ptp_class == PTP_CLASS_NONE)
		वापस false;

	hdr = ptp_parse_header(skb, ptp_class);
	अगर (!hdr)
		वापस false;

	msgtype = ptp_get_msgtype(hdr, ptp_class);
	twostep = hdr->flag_field[0] & 0x2;

	अगर (msgtype == PTP_MSGTYPE_SYNC && twostep == 0)
		वापस true;

	वापस false;
पूर्ण

पूर्णांक ocelot_port_txtstamp_request(काष्ठा ocelot *ocelot, पूर्णांक port,
				 काष्ठा sk_buff *skb,
				 काष्ठा sk_buff **clone)
अणु
	काष्ठा ocelot_port *ocelot_port = ocelot->ports[port];
	u8 ptp_cmd = ocelot_port->ptp_cmd;

	/* Store ptp_cmd in OCELOT_SKB_CB(skb)->ptp_cmd */
	अगर (ptp_cmd == IFH_REW_OP_ORIGIN_PTP) अणु
		अगर (ocelot_ptp_is_onestep_sync(skb)) अणु
			OCELOT_SKB_CB(skb)->ptp_cmd = ptp_cmd;
			वापस 0;
		पूर्ण

		/* Fall back to two-step बारtamping */
		ptp_cmd = IFH_REW_OP_TWO_STEP_PTP;
	पूर्ण

	अगर (ptp_cmd == IFH_REW_OP_TWO_STEP_PTP) अणु
		*clone = skb_clone_sk(skb);
		अगर (!(*clone))
			वापस -ENOMEM;

		ocelot_port_add_txtstamp_skb(ocelot, port, *clone);
		OCELOT_SKB_CB(skb)->ptp_cmd = ptp_cmd;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ocelot_port_txtstamp_request);

अटल व्योम ocelot_get_hwबारtamp(काष्ठा ocelot *ocelot,
				   काष्ठा बारpec64 *ts)
अणु
	अचिन्हित दीर्घ flags;
	u32 val;

	spin_lock_irqsave(&ocelot->ptp_घड़ी_lock, flags);

	/* Read current PTP समय to get seconds */
	val = ocelot_पढ़ो_rix(ocelot, PTP_PIN_CFG, TOD_ACC_PIN);

	val &= ~(PTP_PIN_CFG_SYNC | PTP_PIN_CFG_ACTION_MASK | PTP_PIN_CFG_DOM);
	val |= PTP_PIN_CFG_ACTION(PTP_PIN_ACTION_SAVE);
	ocelot_ग_लिखो_rix(ocelot, val, PTP_PIN_CFG, TOD_ACC_PIN);
	ts->tv_sec = ocelot_पढ़ो_rix(ocelot, PTP_PIN_TOD_SEC_LSB, TOD_ACC_PIN);

	/* Read packet HW बारtamp from FIFO */
	val = ocelot_पढ़ो(ocelot, SYS_PTP_TXSTAMP);
	ts->tv_nsec = SYS_PTP_TXSTAMP_PTP_TXSTAMP(val);

	/* Sec has incremented since the ts was रेजिस्टरed */
	अगर ((ts->tv_sec & 0x1) != !!(val & SYS_PTP_TXSTAMP_PTP_TXSTAMP_SEC))
		ts->tv_sec--;

	spin_unlock_irqrestore(&ocelot->ptp_घड़ी_lock, flags);
पूर्ण

व्योम ocelot_get_txtstamp(काष्ठा ocelot *ocelot)
अणु
	पूर्णांक budget = OCELOT_PTP_QUEUE_SZ;

	जबतक (budget--) अणु
		काष्ठा sk_buff *skb, *skb_पंचांगp, *skb_match = शून्य;
		काष्ठा skb_shared_hwtstamps shhwtstamps;
		काष्ठा ocelot_port *port;
		काष्ठा बारpec64 ts;
		अचिन्हित दीर्घ flags;
		u32 val, id, txport;

		val = ocelot_पढ़ो(ocelot, SYS_PTP_STATUS);

		/* Check अगर a बारtamp can be retrieved */
		अगर (!(val & SYS_PTP_STATUS_PTP_MESS_VLD))
			अवरोध;

		WARN_ON(val & SYS_PTP_STATUS_PTP_OVFL);

		/* Retrieve the ts ID and Tx port */
		id = SYS_PTP_STATUS_PTP_MESS_ID_X(val);
		txport = SYS_PTP_STATUS_PTP_MESS_TXPORT_X(val);

		/* Retrieve its associated skb */
		port = ocelot->ports[txport];

		spin_lock_irqsave(&port->tx_skbs.lock, flags);

		skb_queue_walk_safe(&port->tx_skbs, skb, skb_पंचांगp) अणु
			अगर (OCELOT_SKB_CB(skb)->ts_id != id)
				जारी;
			__skb_unlink(skb, &port->tx_skbs);
			skb_match = skb;
			अवरोध;
		पूर्ण

		spin_unlock_irqrestore(&port->tx_skbs.lock, flags);

		/* Get the h/w बारtamp */
		ocelot_get_hwबारtamp(ocelot, &ts);

		अगर (unlikely(!skb_match))
			जारी;

		/* Set the बारtamp पूर्णांकo the skb */
		स_रखो(&shhwtstamps, 0, माप(shhwtstamps));
		shhwtstamps.hwtstamp = kसमय_set(ts.tv_sec, ts.tv_nsec);
		skb_complete_tx_बारtamp(skb_match, &shhwtstamps);

		/* Next ts */
		ocelot_ग_लिखो(ocelot, SYS_PTP_NXT_PTP_NXT, SYS_PTP_NXT);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(ocelot_get_txtstamp);

अटल पूर्णांक ocelot_rx_frame_word(काष्ठा ocelot *ocelot, u8 grp, bool अगरh,
				u32 *rval)
अणु
	u32 bytes_valid, val;

	val = ocelot_पढ़ो_rix(ocelot, QS_XTR_RD, grp);
	अगर (val == XTR_NOT_READY) अणु
		अगर (अगरh)
			वापस -EIO;

		करो अणु
			val = ocelot_पढ़ो_rix(ocelot, QS_XTR_RD, grp);
		पूर्ण जबतक (val == XTR_NOT_READY);
	पूर्ण

	चयन (val) अणु
	हाल XTR_ABORT:
		वापस -EIO;
	हाल XTR_खातापूर्ण_0:
	हाल XTR_खातापूर्ण_1:
	हाल XTR_खातापूर्ण_2:
	हाल XTR_खातापूर्ण_3:
	हाल XTR_PRUNED:
		bytes_valid = XTR_VALID_BYTES(val);
		val = ocelot_पढ़ो_rix(ocelot, QS_XTR_RD, grp);
		अगर (val == XTR_ESCAPE)
			*rval = ocelot_पढ़ो_rix(ocelot, QS_XTR_RD, grp);
		अन्यथा
			*rval = val;

		वापस bytes_valid;
	हाल XTR_ESCAPE:
		*rval = ocelot_पढ़ो_rix(ocelot, QS_XTR_RD, grp);

		वापस 4;
	शेष:
		*rval = val;

		वापस 4;
	पूर्ण
पूर्ण

अटल पूर्णांक ocelot_xtr_poll_xfh(काष्ठा ocelot *ocelot, पूर्णांक grp, u32 *xfh)
अणु
	पूर्णांक i, err = 0;

	क्रम (i = 0; i < OCELOT_TAG_LEN / 4; i++) अणु
		err = ocelot_rx_frame_word(ocelot, grp, true, &xfh[i]);
		अगर (err != 4)
			वापस (err < 0) ? err : -EIO;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक ocelot_xtr_poll_frame(काष्ठा ocelot *ocelot, पूर्णांक grp, काष्ठा sk_buff **nskb)
अणु
	काष्ठा skb_shared_hwtstamps *shhwtstamps;
	u64 tod_in_ns, full_ts_in_ns;
	u64 बारtamp, src_port, len;
	u32 xfh[OCELOT_TAG_LEN / 4];
	काष्ठा net_device *dev;
	काष्ठा बारpec64 ts;
	काष्ठा sk_buff *skb;
	पूर्णांक sz, buf_len;
	u32 val, *buf;
	पूर्णांक err;

	err = ocelot_xtr_poll_xfh(ocelot, grp, xfh);
	अगर (err)
		वापस err;

	ocelot_xfh_get_src_port(xfh, &src_port);
	ocelot_xfh_get_len(xfh, &len);
	ocelot_xfh_get_rew_val(xfh, &बारtamp);

	अगर (WARN_ON(src_port >= ocelot->num_phys_ports))
		वापस -EINVAL;

	dev = ocelot->ops->port_to_netdev(ocelot, src_port);
	अगर (!dev)
		वापस -EINVAL;

	skb = netdev_alloc_skb(dev, len);
	अगर (unlikely(!skb)) अणु
		netdev_err(dev, "Unable to allocate sk_buff\n");
		वापस -ENOMEM;
	पूर्ण

	buf_len = len - ETH_FCS_LEN;
	buf = (u32 *)skb_put(skb, buf_len);

	len = 0;
	करो अणु
		sz = ocelot_rx_frame_word(ocelot, grp, false, &val);
		अगर (sz < 0) अणु
			err = sz;
			जाओ out_मुक्त_skb;
		पूर्ण
		*buf++ = val;
		len += sz;
	पूर्ण जबतक (len < buf_len);

	/* Read the FCS */
	sz = ocelot_rx_frame_word(ocelot, grp, false, &val);
	अगर (sz < 0) अणु
		err = sz;
		जाओ out_मुक्त_skb;
	पूर्ण

	/* Update the statistics अगर part of the FCS was पढ़ो beक्रमe */
	len -= ETH_FCS_LEN - sz;

	अगर (unlikely(dev->features & NETIF_F_RXFCS)) अणु
		buf = (u32 *)skb_put(skb, ETH_FCS_LEN);
		*buf = val;
	पूर्ण

	अगर (ocelot->ptp) अणु
		ocelot_ptp_समय_लो64(&ocelot->ptp_info, &ts);

		tod_in_ns = kसमय_set(ts.tv_sec, ts.tv_nsec);
		अगर ((tod_in_ns & 0xffffffff) < बारtamp)
			full_ts_in_ns = (((tod_in_ns >> 32) - 1) << 32) |
					बारtamp;
		अन्यथा
			full_ts_in_ns = (tod_in_ns & GENMASK_ULL(63, 32)) |
					बारtamp;

		shhwtstamps = skb_hwtstamps(skb);
		स_रखो(shhwtstamps, 0, माप(काष्ठा skb_shared_hwtstamps));
		shhwtstamps->hwtstamp = full_ts_in_ns;
	पूर्ण

	/* Everything we see on an पूर्णांकerface that is in the HW bridge
	 * has alपढ़ोy been क्रमwarded.
	 */
	अगर (ocelot->ports[src_port]->bridge)
		skb->offload_fwd_mark = 1;

	skb->protocol = eth_type_trans(skb, dev);

	*nskb = skb;

	वापस 0;

out_मुक्त_skb:
	kमुक्त_skb(skb);
	वापस err;
पूर्ण
EXPORT_SYMBOL(ocelot_xtr_poll_frame);

bool ocelot_can_inject(काष्ठा ocelot *ocelot, पूर्णांक grp)
अणु
	u32 val = ocelot_पढ़ो(ocelot, QS_INJ_STATUS);

	अगर (!(val & QS_INJ_STATUS_FIFO_RDY(BIT(grp))))
		वापस false;
	अगर (val & QS_INJ_STATUS_WMARK_REACHED(BIT(grp)))
		वापस false;

	वापस true;
पूर्ण
EXPORT_SYMBOL(ocelot_can_inject);

व्योम ocelot_port_inject_frame(काष्ठा ocelot *ocelot, पूर्णांक port, पूर्णांक grp,
			      u32 rew_op, काष्ठा sk_buff *skb)
अणु
	u32 अगरh[OCELOT_TAG_LEN / 4] = अणु0पूर्ण;
	अचिन्हित पूर्णांक i, count, last;

	ocelot_ग_लिखो_rix(ocelot, QS_INJ_CTRL_GAP_SIZE(1) |
			 QS_INJ_CTRL_SOF, QS_INJ_CTRL, grp);

	ocelot_अगरh_set_bypass(अगरh, 1);
	ocelot_अगरh_set_dest(अगरh, BIT_ULL(port));
	ocelot_अगरh_set_tag_type(अगरh, IFH_TAG_TYPE_C);
	ocelot_अगरh_set_vid(अगरh, skb_vlan_tag_get(skb));
	ocelot_अगरh_set_rew_op(अगरh, rew_op);

	क्रम (i = 0; i < OCELOT_TAG_LEN / 4; i++)
		ocelot_ग_लिखो_rix(ocelot, अगरh[i], QS_INJ_WR, grp);

	count = DIV_ROUND_UP(skb->len, 4);
	last = skb->len % 4;
	क्रम (i = 0; i < count; i++)
		ocelot_ग_लिखो_rix(ocelot, ((u32 *)skb->data)[i], QS_INJ_WR, grp);

	/* Add padding */
	जबतक (i < (OCELOT_BUFFER_CELL_SZ / 4)) अणु
		ocelot_ग_लिखो_rix(ocelot, 0, QS_INJ_WR, grp);
		i++;
	पूर्ण

	/* Indicate खातापूर्ण and valid bytes in last word */
	ocelot_ग_लिखो_rix(ocelot, QS_INJ_CTRL_GAP_SIZE(1) |
			 QS_INJ_CTRL_VLD_BYTES(skb->len < OCELOT_BUFFER_CELL_SZ ? 0 : last) |
			 QS_INJ_CTRL_खातापूर्ण,
			 QS_INJ_CTRL, grp);

	/* Add dummy CRC */
	ocelot_ग_लिखो_rix(ocelot, 0, QS_INJ_WR, grp);
	skb_tx_बारtamp(skb);

	skb->dev->stats.tx_packets++;
	skb->dev->stats.tx_bytes += skb->len;
पूर्ण
EXPORT_SYMBOL(ocelot_port_inject_frame);

व्योम ocelot_drain_cpu_queue(काष्ठा ocelot *ocelot, पूर्णांक grp)
अणु
	जबतक (ocelot_पढ़ो(ocelot, QS_XTR_DATA_PRESENT) & BIT(grp))
		ocelot_पढ़ो_rix(ocelot, QS_XTR_RD, grp);
पूर्ण
EXPORT_SYMBOL(ocelot_drain_cpu_queue);

पूर्णांक ocelot_fdb_add(काष्ठा ocelot *ocelot, पूर्णांक port,
		   स्थिर अचिन्हित अक्षर *addr, u16 vid)
अणु
	पूर्णांक pgid = port;

	अगर (port == ocelot->npi)
		pgid = PGID_CPU;

	वापस ocelot_mact_learn(ocelot, pgid, addr, vid, ENTRYTYPE_LOCKED);
पूर्ण
EXPORT_SYMBOL(ocelot_fdb_add);

पूर्णांक ocelot_fdb_del(काष्ठा ocelot *ocelot, पूर्णांक port,
		   स्थिर अचिन्हित अक्षर *addr, u16 vid)
अणु
	वापस ocelot_mact_क्रमget(ocelot, addr, vid);
पूर्ण
EXPORT_SYMBOL(ocelot_fdb_del);

पूर्णांक ocelot_port_fdb_करो_dump(स्थिर अचिन्हित अक्षर *addr, u16 vid,
			    bool is_अटल, व्योम *data)
अणु
	काष्ठा ocelot_dump_ctx *dump = data;
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
	ndm->ndm_state   = is_अटल ? NUD_NOARP : NUD_REACHABLE;

	अगर (nla_put(dump->skb, NDA_LLADDR, ETH_ALEN, addr))
		जाओ nla_put_failure;

	अगर (vid && nla_put_u16(dump->skb, NDA_VLAN, vid))
		जाओ nla_put_failure;

	nlmsg_end(dump->skb, nlh);

skip:
	dump->idx++;
	वापस 0;

nla_put_failure:
	nlmsg_cancel(dump->skb, nlh);
	वापस -EMSGSIZE;
पूर्ण
EXPORT_SYMBOL(ocelot_port_fdb_करो_dump);

अटल पूर्णांक ocelot_mact_पढ़ो(काष्ठा ocelot *ocelot, पूर्णांक port, पूर्णांक row, पूर्णांक col,
			    काष्ठा ocelot_mact_entry *entry)
अणु
	u32 val, dst, macl, mach;
	अक्षर mac[ETH_ALEN];

	/* Set row and column to पढ़ो from */
	ocelot_field_ग_लिखो(ocelot, ANA_TABLES_MACTINDX_M_INDEX, row);
	ocelot_field_ग_लिखो(ocelot, ANA_TABLES_MACTINDX_BUCKET, col);

	/* Issue a पढ़ो command */
	ocelot_ग_लिखो(ocelot,
		     ANA_TABLES_MACACCESS_MAC_TABLE_CMD(MACACCESS_CMD_READ),
		     ANA_TABLES_MACACCESS);

	अगर (ocelot_mact_रुको_क्रम_completion(ocelot))
		वापस -ETIMEDOUT;

	/* Read the entry flags */
	val = ocelot_पढ़ो(ocelot, ANA_TABLES_MACACCESS);
	अगर (!(val & ANA_TABLES_MACACCESS_VALID))
		वापस -EINVAL;

	/* If the entry पढ़ो has another port configured as its destination,
	 * करो not report it.
	 */
	dst = (val & ANA_TABLES_MACACCESS_DEST_IDX_M) >> 3;
	अगर (dst != port)
		वापस -EINVAL;

	/* Get the entry's MAC address and VLAN id */
	macl = ocelot_पढ़ो(ocelot, ANA_TABLES_MACLDATA);
	mach = ocelot_पढ़ो(ocelot, ANA_TABLES_MACHDATA);

	mac[0] = (mach >> 8)  & 0xff;
	mac[1] = (mach >> 0)  & 0xff;
	mac[2] = (macl >> 24) & 0xff;
	mac[3] = (macl >> 16) & 0xff;
	mac[4] = (macl >> 8)  & 0xff;
	mac[5] = (macl >> 0)  & 0xff;

	entry->vid = (mach >> 16) & 0xfff;
	ether_addr_copy(entry->mac, mac);

	वापस 0;
पूर्ण

पूर्णांक ocelot_fdb_dump(काष्ठा ocelot *ocelot, पूर्णांक port,
		    dsa_fdb_dump_cb_t *cb, व्योम *data)
अणु
	पूर्णांक i, j;

	/* Loop through all the mac tables entries. */
	क्रम (i = 0; i < ocelot->num_mact_rows; i++) अणु
		क्रम (j = 0; j < 4; j++) अणु
			काष्ठा ocelot_mact_entry entry;
			bool is_अटल;
			पूर्णांक ret;

			ret = ocelot_mact_पढ़ो(ocelot, port, i, j, &entry);
			/* If the entry is invalid (wrong port, invalid...),
			 * skip it.
			 */
			अगर (ret == -EINVAL)
				जारी;
			अन्यथा अगर (ret)
				वापस ret;

			is_अटल = (entry.type == ENTRYTYPE_LOCKED);

			ret = cb(entry.mac, entry.vid, is_अटल, data);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ocelot_fdb_dump);

पूर्णांक ocelot_hwstamp_get(काष्ठा ocelot *ocelot, पूर्णांक port, काष्ठा अगरreq *अगरr)
अणु
	वापस copy_to_user(अगरr->अगरr_data, &ocelot->hwtstamp_config,
			    माप(ocelot->hwtstamp_config)) ? -EFAULT : 0;
पूर्ण
EXPORT_SYMBOL(ocelot_hwstamp_get);

पूर्णांक ocelot_hwstamp_set(काष्ठा ocelot *ocelot, पूर्णांक port, काष्ठा अगरreq *अगरr)
अणु
	काष्ठा ocelot_port *ocelot_port = ocelot->ports[port];
	काष्ठा hwtstamp_config cfg;

	अगर (copy_from_user(&cfg, अगरr->अगरr_data, माप(cfg)))
		वापस -EFAULT;

	/* reserved क्रम future extensions */
	अगर (cfg.flags)
		वापस -EINVAL;

	/* Tx type sanity check */
	चयन (cfg.tx_type) अणु
	हाल HWTSTAMP_TX_ON:
		ocelot_port->ptp_cmd = IFH_REW_OP_TWO_STEP_PTP;
		अवरोध;
	हाल HWTSTAMP_TX_ONESTEP_SYNC:
		/* IFH_REW_OP_ONE_STEP_PTP updates the correctional field, we
		 * need to update the origin समय.
		 */
		ocelot_port->ptp_cmd = IFH_REW_OP_ORIGIN_PTP;
		अवरोध;
	हाल HWTSTAMP_TX_OFF:
		ocelot_port->ptp_cmd = 0;
		अवरोध;
	शेष:
		वापस -दुस्फल;
	पूर्ण

	mutex_lock(&ocelot->ptp_lock);

	चयन (cfg.rx_filter) अणु
	हाल HWTSTAMP_FILTER_NONE:
		अवरोध;
	हाल HWTSTAMP_FILTER_ALL:
	हाल HWTSTAMP_FILTER_SOME:
	हाल HWTSTAMP_FILTER_PTP_V1_L4_EVENT:
	हाल HWTSTAMP_FILTER_PTP_V1_L4_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ:
	हाल HWTSTAMP_FILTER_NTP_ALL:
	हाल HWTSTAMP_FILTER_PTP_V2_L4_EVENT:
	हाल HWTSTAMP_FILTER_PTP_V2_L4_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ:
	हाल HWTSTAMP_FILTER_PTP_V2_L2_EVENT:
	हाल HWTSTAMP_FILTER_PTP_V2_L2_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V2_L2_DELAY_REQ:
	हाल HWTSTAMP_FILTER_PTP_V2_EVENT:
	हाल HWTSTAMP_FILTER_PTP_V2_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V2_DELAY_REQ:
		cfg.rx_filter = HWTSTAMP_FILTER_PTP_V2_EVENT;
		अवरोध;
	शेष:
		mutex_unlock(&ocelot->ptp_lock);
		वापस -दुस्फल;
	पूर्ण

	/* Commit back the result & save it */
	स_नकल(&ocelot->hwtstamp_config, &cfg, माप(cfg));
	mutex_unlock(&ocelot->ptp_lock);

	वापस copy_to_user(अगरr->अगरr_data, &cfg, माप(cfg)) ? -EFAULT : 0;
पूर्ण
EXPORT_SYMBOL(ocelot_hwstamp_set);

व्योम ocelot_get_strings(काष्ठा ocelot *ocelot, पूर्णांक port, u32 sset, u8 *data)
अणु
	पूर्णांक i;

	अगर (sset != ETH_SS_STATS)
		वापस;

	क्रम (i = 0; i < ocelot->num_stats; i++)
		स_नकल(data + i * ETH_GSTRING_LEN, ocelot->stats_layout[i].name,
		       ETH_GSTRING_LEN);
पूर्ण
EXPORT_SYMBOL(ocelot_get_strings);

अटल व्योम ocelot_update_stats(काष्ठा ocelot *ocelot)
अणु
	पूर्णांक i, j;

	mutex_lock(&ocelot->stats_lock);

	क्रम (i = 0; i < ocelot->num_phys_ports; i++) अणु
		/* Configure the port to पढ़ो the stats from */
		ocelot_ग_लिखो(ocelot, SYS_STAT_CFG_STAT_VIEW(i), SYS_STAT_CFG);

		क्रम (j = 0; j < ocelot->num_stats; j++) अणु
			u32 val;
			अचिन्हित पूर्णांक idx = i * ocelot->num_stats + j;

			val = ocelot_पढ़ो_rix(ocelot, SYS_COUNT_RX_OCTETS,
					      ocelot->stats_layout[j].offset);

			अगर (val < (ocelot->stats[idx] & U32_MAX))
				ocelot->stats[idx] += (u64)1 << 32;

			ocelot->stats[idx] = (ocelot->stats[idx] &
					      ~(u64)U32_MAX) + val;
		पूर्ण
	पूर्ण

	mutex_unlock(&ocelot->stats_lock);
पूर्ण

अटल व्योम ocelot_check_stats_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *del_work = to_delayed_work(work);
	काष्ठा ocelot *ocelot = container_of(del_work, काष्ठा ocelot,
					     stats_work);

	ocelot_update_stats(ocelot);

	queue_delayed_work(ocelot->stats_queue, &ocelot->stats_work,
			   OCELOT_STATS_CHECK_DELAY);
पूर्ण

व्योम ocelot_get_ethtool_stats(काष्ठा ocelot *ocelot, पूर्णांक port, u64 *data)
अणु
	पूर्णांक i;

	/* check and update now */
	ocelot_update_stats(ocelot);

	/* Copy all counters */
	क्रम (i = 0; i < ocelot->num_stats; i++)
		*data++ = ocelot->stats[port * ocelot->num_stats + i];
पूर्ण
EXPORT_SYMBOL(ocelot_get_ethtool_stats);

पूर्णांक ocelot_get_sset_count(काष्ठा ocelot *ocelot, पूर्णांक port, पूर्णांक sset)
अणु
	अगर (sset != ETH_SS_STATS)
		वापस -EOPNOTSUPP;

	वापस ocelot->num_stats;
पूर्ण
EXPORT_SYMBOL(ocelot_get_sset_count);

पूर्णांक ocelot_get_ts_info(काष्ठा ocelot *ocelot, पूर्णांक port,
		       काष्ठा ethtool_ts_info *info)
अणु
	info->phc_index = ocelot->ptp_घड़ी ?
			  ptp_घड़ी_index(ocelot->ptp_घड़ी) : -1;
	अगर (info->phc_index == -1) अणु
		info->so_बारtamping |= SOF_TIMESTAMPING_TX_SOFTWARE |
					 SOF_TIMESTAMPING_RX_SOFTWARE |
					 SOF_TIMESTAMPING_SOFTWARE;
		वापस 0;
	पूर्ण
	info->so_बारtamping |= SOF_TIMESTAMPING_TX_SOFTWARE |
				 SOF_TIMESTAMPING_RX_SOFTWARE |
				 SOF_TIMESTAMPING_SOFTWARE |
				 SOF_TIMESTAMPING_TX_HARDWARE |
				 SOF_TIMESTAMPING_RX_HARDWARE |
				 SOF_TIMESTAMPING_RAW_HARDWARE;
	info->tx_types = BIT(HWTSTAMP_TX_OFF) | BIT(HWTSTAMP_TX_ON) |
			 BIT(HWTSTAMP_TX_ONESTEP_SYNC);
	info->rx_filters = BIT(HWTSTAMP_FILTER_NONE) | BIT(HWTSTAMP_FILTER_ALL);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ocelot_get_ts_info);

अटल u32 ocelot_get_bond_mask(काष्ठा ocelot *ocelot, काष्ठा net_device *bond,
				bool only_active_ports)
अणु
	u32 mask = 0;
	पूर्णांक port;

	क्रम (port = 0; port < ocelot->num_phys_ports; port++) अणु
		काष्ठा ocelot_port *ocelot_port = ocelot->ports[port];

		अगर (!ocelot_port)
			जारी;

		अगर (ocelot_port->bond == bond) अणु
			अगर (only_active_ports && !ocelot_port->lag_tx_active)
				जारी;

			mask |= BIT(port);
		पूर्ण
	पूर्ण

	वापस mask;
पूर्ण

अटल u32 ocelot_get_bridge_fwd_mask(काष्ठा ocelot *ocelot,
				      काष्ठा net_device *bridge)
अणु
	u32 mask = 0;
	पूर्णांक port;

	क्रम (port = 0; port < ocelot->num_phys_ports; port++) अणु
		काष्ठा ocelot_port *ocelot_port = ocelot->ports[port];

		अगर (!ocelot_port)
			जारी;

		अगर (ocelot_port->stp_state == BR_STATE_FORWARDING &&
		    ocelot_port->bridge == bridge)
			mask |= BIT(port);
	पूर्ण

	वापस mask;
पूर्ण

अटल u32 ocelot_get_dsa_8021q_cpu_mask(काष्ठा ocelot *ocelot)
अणु
	u32 mask = 0;
	पूर्णांक port;

	क्रम (port = 0; port < ocelot->num_phys_ports; port++) अणु
		काष्ठा ocelot_port *ocelot_port = ocelot->ports[port];

		अगर (!ocelot_port)
			जारी;

		अगर (ocelot_port->is_dsa_8021q_cpu)
			mask |= BIT(port);
	पूर्ण

	वापस mask;
पूर्ण

व्योम ocelot_apply_bridge_fwd_mask(काष्ठा ocelot *ocelot)
अणु
	अचिन्हित दीर्घ cpu_fwd_mask;
	पूर्णांक port;

	/* If a DSA tag_8021q CPU exists, it needs to be included in the
	 * regular क्रमwarding path of the front ports regardless of whether
	 * those are bridged or standalone.
	 * If DSA tag_8021q is not used, this वापसs 0, which is fine because
	 * the hardware-based CPU port module can be a destination क्रम packets
	 * even अगर it isn't part of PGID_SRC.
	 */
	cpu_fwd_mask = ocelot_get_dsa_8021q_cpu_mask(ocelot);

	/* Apply FWD mask. The loop is needed to add/हटाओ the current port as
	 * a source क्रम the other ports.
	 */
	क्रम (port = 0; port < ocelot->num_phys_ports; port++) अणु
		काष्ठा ocelot_port *ocelot_port = ocelot->ports[port];
		अचिन्हित दीर्घ mask;

		अगर (!ocelot_port) अणु
			/* Unused ports can't send anywhere */
			mask = 0;
		पूर्ण अन्यथा अगर (ocelot_port->is_dsa_8021q_cpu) अणु
			/* The DSA tag_8021q CPU ports need to be able to
			 * क्रमward packets to all other ports except क्रम
			 * themselves
			 */
			mask = GENMASK(ocelot->num_phys_ports - 1, 0);
			mask &= ~cpu_fwd_mask;
		पूर्ण अन्यथा अगर (ocelot_port->bridge) अणु
			काष्ठा net_device *bridge = ocelot_port->bridge;
			काष्ठा net_device *bond = ocelot_port->bond;

			mask = ocelot_get_bridge_fwd_mask(ocelot, bridge);
			mask &= ~BIT(port);
			अगर (bond) अणु
				mask &= ~ocelot_get_bond_mask(ocelot, bond,
							      false);
			पूर्ण
		पूर्ण अन्यथा अणु
			/* Standalone ports क्रमward only to DSA tag_8021q CPU
			 * ports (अगर those exist), or to the hardware CPU port
			 * module otherwise.
			 */
			mask = cpu_fwd_mask;
		पूर्ण

		ocelot_ग_लिखो_rix(ocelot, mask, ANA_PGID_PGID, PGID_SRC + port);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(ocelot_apply_bridge_fwd_mask);

व्योम ocelot_bridge_stp_state_set(काष्ठा ocelot *ocelot, पूर्णांक port, u8 state)
अणु
	काष्ठा ocelot_port *ocelot_port = ocelot->ports[port];
	u32 learn_ena = 0;

	ocelot_port->stp_state = state;

	अगर ((state == BR_STATE_LEARNING || state == BR_STATE_FORWARDING) &&
	    ocelot_port->learn_ena)
		learn_ena = ANA_PORT_PORT_CFG_LEARN_ENA;

	ocelot_rmw_gix(ocelot, learn_ena, ANA_PORT_PORT_CFG_LEARN_ENA,
		       ANA_PORT_PORT_CFG, port);

	ocelot_apply_bridge_fwd_mask(ocelot);
पूर्ण
EXPORT_SYMBOL(ocelot_bridge_stp_state_set);

व्योम ocelot_set_ageing_समय(काष्ठा ocelot *ocelot, अचिन्हित पूर्णांक msecs)
अणु
	अचिन्हित पूर्णांक age_period = ANA_AUTOAGE_AGE_PERIOD(msecs / 2000);

	/* Setting AGE_PERIOD to zero effectively disables स्वतःmatic aging,
	 * which is clearly not what our पूर्णांकention is. So aव्योम that.
	 */
	अगर (!age_period)
		age_period = 1;

	ocelot_rmw(ocelot, age_period, ANA_AUTOAGE_AGE_PERIOD_M, ANA_AUTOAGE);
पूर्ण
EXPORT_SYMBOL(ocelot_set_ageing_समय);

अटल काष्ठा ocelot_multicast *ocelot_multicast_get(काष्ठा ocelot *ocelot,
						     स्थिर अचिन्हित अक्षर *addr,
						     u16 vid)
अणु
	काष्ठा ocelot_multicast *mc;

	list_क्रम_each_entry(mc, &ocelot->multicast, list) अणु
		अगर (ether_addr_equal(mc->addr, addr) && mc->vid == vid)
			वापस mc;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल क्रमागत macaccess_entry_type ocelot_classअगरy_mdb(स्थिर अचिन्हित अक्षर *addr)
अणु
	अगर (addr[0] == 0x01 && addr[1] == 0x00 && addr[2] == 0x5e)
		वापस ENTRYTYPE_MACv4;
	अगर (addr[0] == 0x33 && addr[1] == 0x33)
		वापस ENTRYTYPE_MACv6;
	वापस ENTRYTYPE_LOCKED;
पूर्ण

अटल काष्ठा ocelot_pgid *ocelot_pgid_alloc(काष्ठा ocelot *ocelot, पूर्णांक index,
					     अचिन्हित दीर्घ ports)
अणु
	काष्ठा ocelot_pgid *pgid;

	pgid = kzalloc(माप(*pgid), GFP_KERNEL);
	अगर (!pgid)
		वापस ERR_PTR(-ENOMEM);

	pgid->ports = ports;
	pgid->index = index;
	refcount_set(&pgid->refcount, 1);
	list_add_tail(&pgid->list, &ocelot->pgids);

	वापस pgid;
पूर्ण

अटल व्योम ocelot_pgid_मुक्त(काष्ठा ocelot *ocelot, काष्ठा ocelot_pgid *pgid)
अणु
	अगर (!refcount_dec_and_test(&pgid->refcount))
		वापस;

	list_del(&pgid->list);
	kमुक्त(pgid);
पूर्ण

अटल काष्ठा ocelot_pgid *ocelot_mdb_get_pgid(काष्ठा ocelot *ocelot,
					       स्थिर काष्ठा ocelot_multicast *mc)
अणु
	काष्ठा ocelot_pgid *pgid;
	पूर्णांक index;

	/* According to VSC7514 datasheet 3.9.1.5 IPv4 Multicast Entries and
	 * 3.9.1.6 IPv6 Multicast Entries, "Instead of a lookup in the
	 * destination mask table (PGID), the destination set is programmed as
	 * part of the entry MAC address.", and the DEST_IDX is set to 0.
	 */
	अगर (mc->entry_type == ENTRYTYPE_MACv4 ||
	    mc->entry_type == ENTRYTYPE_MACv6)
		वापस ocelot_pgid_alloc(ocelot, 0, mc->ports);

	list_क्रम_each_entry(pgid, &ocelot->pgids, list) अणु
		/* When searching क्रम a nonreserved multicast PGID, ignore the
		 * dummy PGID of zero that we have क्रम MACv4/MACv6 entries
		 */
		अगर (pgid->index && pgid->ports == mc->ports) अणु
			refcount_inc(&pgid->refcount);
			वापस pgid;
		पूर्ण
	पूर्ण

	/* Search क्रम a मुक्त index in the nonreserved multicast PGID area */
	क्रम_each_nonreserved_multicast_dest_pgid(ocelot, index) अणु
		bool used = false;

		list_क्रम_each_entry(pgid, &ocelot->pgids, list) अणु
			अगर (pgid->index == index) अणु
				used = true;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (!used)
			वापस ocelot_pgid_alloc(ocelot, index, mc->ports);
	पूर्ण

	वापस ERR_PTR(-ENOSPC);
पूर्ण

अटल व्योम ocelot_encode_ports_to_mdb(अचिन्हित अक्षर *addr,
				       काष्ठा ocelot_multicast *mc)
अणु
	ether_addr_copy(addr, mc->addr);

	अगर (mc->entry_type == ENTRYTYPE_MACv4) अणु
		addr[0] = 0;
		addr[1] = mc->ports >> 8;
		addr[2] = mc->ports & 0xff;
	पूर्ण अन्यथा अगर (mc->entry_type == ENTRYTYPE_MACv6) अणु
		addr[0] = mc->ports >> 8;
		addr[1] = mc->ports & 0xff;
	पूर्ण
पूर्ण

पूर्णांक ocelot_port_mdb_add(काष्ठा ocelot *ocelot, पूर्णांक port,
			स्थिर काष्ठा चयनdev_obj_port_mdb *mdb)
अणु
	अचिन्हित अक्षर addr[ETH_ALEN];
	काष्ठा ocelot_multicast *mc;
	काष्ठा ocelot_pgid *pgid;
	u16 vid = mdb->vid;

	अगर (port == ocelot->npi)
		port = ocelot->num_phys_ports;

	mc = ocelot_multicast_get(ocelot, mdb->addr, vid);
	अगर (!mc) अणु
		/* New entry */
		mc = devm_kzalloc(ocelot->dev, माप(*mc), GFP_KERNEL);
		अगर (!mc)
			वापस -ENOMEM;

		mc->entry_type = ocelot_classअगरy_mdb(mdb->addr);
		ether_addr_copy(mc->addr, mdb->addr);
		mc->vid = vid;

		list_add_tail(&mc->list, &ocelot->multicast);
	पूर्ण अन्यथा अणु
		/* Existing entry. Clean up the current port mask from
		 * hardware now, because we'll be modअगरying it.
		 */
		ocelot_pgid_मुक्त(ocelot, mc->pgid);
		ocelot_encode_ports_to_mdb(addr, mc);
		ocelot_mact_क्रमget(ocelot, addr, vid);
	पूर्ण

	mc->ports |= BIT(port);

	pgid = ocelot_mdb_get_pgid(ocelot, mc);
	अगर (IS_ERR(pgid)) अणु
		dev_err(ocelot->dev,
			"Cannot allocate PGID for mdb %pM vid %d\n",
			mc->addr, mc->vid);
		devm_kमुक्त(ocelot->dev, mc);
		वापस PTR_ERR(pgid);
	पूर्ण
	mc->pgid = pgid;

	ocelot_encode_ports_to_mdb(addr, mc);

	अगर (mc->entry_type != ENTRYTYPE_MACv4 &&
	    mc->entry_type != ENTRYTYPE_MACv6)
		ocelot_ग_लिखो_rix(ocelot, pgid->ports, ANA_PGID_PGID,
				 pgid->index);

	वापस ocelot_mact_learn(ocelot, pgid->index, addr, vid,
				 mc->entry_type);
पूर्ण
EXPORT_SYMBOL(ocelot_port_mdb_add);

पूर्णांक ocelot_port_mdb_del(काष्ठा ocelot *ocelot, पूर्णांक port,
			स्थिर काष्ठा चयनdev_obj_port_mdb *mdb)
अणु
	अचिन्हित अक्षर addr[ETH_ALEN];
	काष्ठा ocelot_multicast *mc;
	काष्ठा ocelot_pgid *pgid;
	u16 vid = mdb->vid;

	अगर (port == ocelot->npi)
		port = ocelot->num_phys_ports;

	mc = ocelot_multicast_get(ocelot, mdb->addr, vid);
	अगर (!mc)
		वापस -ENOENT;

	ocelot_encode_ports_to_mdb(addr, mc);
	ocelot_mact_क्रमget(ocelot, addr, vid);

	ocelot_pgid_मुक्त(ocelot, mc->pgid);
	mc->ports &= ~BIT(port);
	अगर (!mc->ports) अणु
		list_del(&mc->list);
		devm_kमुक्त(ocelot->dev, mc);
		वापस 0;
	पूर्ण

	/* We have a PGID with fewer ports now */
	pgid = ocelot_mdb_get_pgid(ocelot, mc);
	अगर (IS_ERR(pgid))
		वापस PTR_ERR(pgid);
	mc->pgid = pgid;

	ocelot_encode_ports_to_mdb(addr, mc);

	अगर (mc->entry_type != ENTRYTYPE_MACv4 &&
	    mc->entry_type != ENTRYTYPE_MACv6)
		ocelot_ग_लिखो_rix(ocelot, pgid->ports, ANA_PGID_PGID,
				 pgid->index);

	वापस ocelot_mact_learn(ocelot, pgid->index, addr, vid,
				 mc->entry_type);
पूर्ण
EXPORT_SYMBOL(ocelot_port_mdb_del);

व्योम ocelot_port_bridge_join(काष्ठा ocelot *ocelot, पूर्णांक port,
			     काष्ठा net_device *bridge)
अणु
	काष्ठा ocelot_port *ocelot_port = ocelot->ports[port];

	ocelot_port->bridge = bridge;

	ocelot_apply_bridge_fwd_mask(ocelot);
पूर्ण
EXPORT_SYMBOL(ocelot_port_bridge_join);

व्योम ocelot_port_bridge_leave(काष्ठा ocelot *ocelot, पूर्णांक port,
			      काष्ठा net_device *bridge)
अणु
	काष्ठा ocelot_port *ocelot_port = ocelot->ports[port];
	काष्ठा ocelot_vlan pvid = अणु0पूर्ण, native_vlan = अणु0पूर्ण;

	ocelot_port->bridge = शून्य;

	ocelot_port_set_pvid(ocelot, port, pvid);
	ocelot_port_set_native_vlan(ocelot, port, native_vlan);
	ocelot_apply_bridge_fwd_mask(ocelot);
पूर्ण
EXPORT_SYMBOL(ocelot_port_bridge_leave);

अटल व्योम ocelot_set_aggr_pgids(काष्ठा ocelot *ocelot)
अणु
	अचिन्हित दीर्घ visited = GENMASK(ocelot->num_phys_ports - 1, 0);
	पूर्णांक i, port, lag;

	/* Reset destination and aggregation PGIDS */
	क्रम_each_unicast_dest_pgid(ocelot, port)
		ocelot_ग_लिखो_rix(ocelot, BIT(port), ANA_PGID_PGID, port);

	क्रम_each_aggr_pgid(ocelot, i)
		ocelot_ग_लिखो_rix(ocelot, GENMASK(ocelot->num_phys_ports - 1, 0),
				 ANA_PGID_PGID, i);

	/* The visited ports biपंचांगask holds the list of ports offloading any
	 * bonding पूर्णांकerface. Initially we mark all these ports as unvisited,
	 * then every समय we visit a port in this biपंचांगask, we know that it is
	 * the lowest numbered port, i.e. the one whose logical ID == physical
	 * port ID == LAG ID. So we mark as visited all further ports in the
	 * biपंचांगask that are offloading the same bonding पूर्णांकerface. This way,
	 * we set up the aggregation PGIDs only once per bonding पूर्णांकerface.
	 */
	क्रम (port = 0; port < ocelot->num_phys_ports; port++) अणु
		काष्ठा ocelot_port *ocelot_port = ocelot->ports[port];

		अगर (!ocelot_port || !ocelot_port->bond)
			जारी;

		visited &= ~BIT(port);
	पूर्ण

	/* Now, set PGIDs क्रम each active LAG */
	क्रम (lag = 0; lag < ocelot->num_phys_ports; lag++) अणु
		काष्ठा net_device *bond = ocelot->ports[lag]->bond;
		पूर्णांक num_active_ports = 0;
		अचिन्हित दीर्घ bond_mask;
		u8 aggr_idx[16];

		अगर (!bond || (visited & BIT(lag)))
			जारी;

		bond_mask = ocelot_get_bond_mask(ocelot, bond, true);

		क्रम_each_set_bit(port, &bond_mask, ocelot->num_phys_ports) अणु
			// Destination mask
			ocelot_ग_लिखो_rix(ocelot, bond_mask,
					 ANA_PGID_PGID, port);
			aggr_idx[num_active_ports++] = port;
		पूर्ण

		क्रम_each_aggr_pgid(ocelot, i) अणु
			u32 ac;

			ac = ocelot_पढ़ो_rix(ocelot, ANA_PGID_PGID, i);
			ac &= ~bond_mask;
			/* Don't करो भागision by zero अगर there was no active
			 * port. Just make all aggregation codes zero.
			 */
			अगर (num_active_ports)
				ac |= BIT(aggr_idx[i % num_active_ports]);
			ocelot_ग_लिखो_rix(ocelot, ac, ANA_PGID_PGID, i);
		पूर्ण

		/* Mark all ports in the same LAG as visited to aव्योम applying
		 * the same config again.
		 */
		क्रम (port = lag; port < ocelot->num_phys_ports; port++) अणु
			काष्ठा ocelot_port *ocelot_port = ocelot->ports[port];

			अगर (!ocelot_port)
				जारी;

			अगर (ocelot_port->bond == bond)
				visited |= BIT(port);
		पूर्ण
	पूर्ण
पूर्ण

/* When offloading a bonding पूर्णांकerface, the चयन ports configured under the
 * same bond must have the same logical port ID, equal to the physical port ID
 * of the lowest numbered physical port in that bond. Otherwise, in standalone/
 * bridged mode, each port has a logical port ID equal to its physical port ID.
 */
अटल व्योम ocelot_setup_logical_port_ids(काष्ठा ocelot *ocelot)
अणु
	पूर्णांक port;

	क्रम (port = 0; port < ocelot->num_phys_ports; port++) अणु
		काष्ठा ocelot_port *ocelot_port = ocelot->ports[port];
		काष्ठा net_device *bond;

		अगर (!ocelot_port)
			जारी;

		bond = ocelot_port->bond;
		अगर (bond) अणु
			पूर्णांक lag = __ffs(ocelot_get_bond_mask(ocelot, bond,
							     false));

			ocelot_rmw_gix(ocelot,
				       ANA_PORT_PORT_CFG_PORTID_VAL(lag),
				       ANA_PORT_PORT_CFG_PORTID_VAL_M,
				       ANA_PORT_PORT_CFG, port);
		पूर्ण अन्यथा अणु
			ocelot_rmw_gix(ocelot,
				       ANA_PORT_PORT_CFG_PORTID_VAL(port),
				       ANA_PORT_PORT_CFG_PORTID_VAL_M,
				       ANA_PORT_PORT_CFG, port);
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक ocelot_port_lag_join(काष्ठा ocelot *ocelot, पूर्णांक port,
			 काष्ठा net_device *bond,
			 काष्ठा netdev_lag_upper_info *info)
अणु
	अगर (info->tx_type != NETDEV_LAG_TX_TYPE_HASH)
		वापस -EOPNOTSUPP;

	ocelot->ports[port]->bond = bond;

	ocelot_setup_logical_port_ids(ocelot);
	ocelot_apply_bridge_fwd_mask(ocelot);
	ocelot_set_aggr_pgids(ocelot);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ocelot_port_lag_join);

व्योम ocelot_port_lag_leave(काष्ठा ocelot *ocelot, पूर्णांक port,
			   काष्ठा net_device *bond)
अणु
	ocelot->ports[port]->bond = शून्य;

	ocelot_setup_logical_port_ids(ocelot);
	ocelot_apply_bridge_fwd_mask(ocelot);
	ocelot_set_aggr_pgids(ocelot);
पूर्ण
EXPORT_SYMBOL(ocelot_port_lag_leave);

व्योम ocelot_port_lag_change(काष्ठा ocelot *ocelot, पूर्णांक port, bool lag_tx_active)
अणु
	काष्ठा ocelot_port *ocelot_port = ocelot->ports[port];

	ocelot_port->lag_tx_active = lag_tx_active;

	/* Rebalance the LAGs */
	ocelot_set_aggr_pgids(ocelot);
पूर्ण
EXPORT_SYMBOL(ocelot_port_lag_change);

/* Configure the maximum SDU (L2 payload) on RX to the value specअगरied in @sdu.
 * The length of VLAN tags is accounted क्रम स्वतःmatically via DEV_MAC_TAGS_CFG.
 * In the special हाल that it's the NPI port that we're configuring, the
 * length of the tag and optional prefix needs to be accounted क्रम निजीly,
 * in order to be able to sustain communication at the requested @sdu.
 */
व्योम ocelot_port_set_maxlen(काष्ठा ocelot *ocelot, पूर्णांक port, माप_प्रकार sdu)
अणु
	काष्ठा ocelot_port *ocelot_port = ocelot->ports[port];
	पूर्णांक maxlen = sdu + ETH_HLEN + ETH_FCS_LEN;
	पूर्णांक छोड़ो_start, छोड़ो_stop;
	पूर्णांक atop, atop_tot;

	अगर (port == ocelot->npi) अणु
		maxlen += OCELOT_TAG_LEN;

		अगर (ocelot->npi_inj_prefix == OCELOT_TAG_PREFIX_SHORT)
			maxlen += OCELOT_SHORT_PREFIX_LEN;
		अन्यथा अगर (ocelot->npi_inj_prefix == OCELOT_TAG_PREFIX_LONG)
			maxlen += OCELOT_LONG_PREFIX_LEN;
	पूर्ण

	ocelot_port_ग_लिखोl(ocelot_port, maxlen, DEV_MAC_MAXLEN_CFG);

	/* Set Pause watermark hysteresis */
	छोड़ो_start = 6 * maxlen / OCELOT_BUFFER_CELL_SZ;
	छोड़ो_stop = 4 * maxlen / OCELOT_BUFFER_CELL_SZ;
	ocelot_fields_ग_लिखो(ocelot, port, SYS_PAUSE_CFG_PAUSE_START,
			    छोड़ो_start);
	ocelot_fields_ग_लिखो(ocelot, port, SYS_PAUSE_CFG_PAUSE_STOP,
			    छोड़ो_stop);

	/* Tail dropping watermarks */
	atop_tot = (ocelot->packet_buffer_size - 9 * maxlen) /
		   OCELOT_BUFFER_CELL_SZ;
	atop = (9 * maxlen) / OCELOT_BUFFER_CELL_SZ;
	ocelot_ग_लिखो_rix(ocelot, ocelot->ops->wm_enc(atop), SYS_ATOP, port);
	ocelot_ग_लिखो(ocelot, ocelot->ops->wm_enc(atop_tot), SYS_ATOP_TOT_CFG);
पूर्ण
EXPORT_SYMBOL(ocelot_port_set_maxlen);

पूर्णांक ocelot_get_max_mtu(काष्ठा ocelot *ocelot, पूर्णांक port)
अणु
	पूर्णांक max_mtu = 65535 - ETH_HLEN - ETH_FCS_LEN;

	अगर (port == ocelot->npi) अणु
		max_mtu -= OCELOT_TAG_LEN;

		अगर (ocelot->npi_inj_prefix == OCELOT_TAG_PREFIX_SHORT)
			max_mtu -= OCELOT_SHORT_PREFIX_LEN;
		अन्यथा अगर (ocelot->npi_inj_prefix == OCELOT_TAG_PREFIX_LONG)
			max_mtu -= OCELOT_LONG_PREFIX_LEN;
	पूर्ण

	वापस max_mtu;
पूर्ण
EXPORT_SYMBOL(ocelot_get_max_mtu);

अटल व्योम ocelot_port_set_learning(काष्ठा ocelot *ocelot, पूर्णांक port,
				     bool enabled)
अणु
	काष्ठा ocelot_port *ocelot_port = ocelot->ports[port];
	u32 val = 0;

	अगर (enabled)
		val = ANA_PORT_PORT_CFG_LEARN_ENA;

	ocelot_rmw_gix(ocelot, val, ANA_PORT_PORT_CFG_LEARN_ENA,
		       ANA_PORT_PORT_CFG, port);

	ocelot_port->learn_ena = enabled;
पूर्ण

अटल व्योम ocelot_port_set_ucast_flood(काष्ठा ocelot *ocelot, पूर्णांक port,
					bool enabled)
अणु
	u32 val = 0;

	अगर (enabled)
		val = BIT(port);

	ocelot_rmw_rix(ocelot, val, BIT(port), ANA_PGID_PGID, PGID_UC);
पूर्ण

अटल व्योम ocelot_port_set_mcast_flood(काष्ठा ocelot *ocelot, पूर्णांक port,
					bool enabled)
अणु
	u32 val = 0;

	अगर (enabled)
		val = BIT(port);

	ocelot_rmw_rix(ocelot, val, BIT(port), ANA_PGID_PGID, PGID_MC);
पूर्ण

अटल व्योम ocelot_port_set_bcast_flood(काष्ठा ocelot *ocelot, पूर्णांक port,
					bool enabled)
अणु
	u32 val = 0;

	अगर (enabled)
		val = BIT(port);

	ocelot_rmw_rix(ocelot, val, BIT(port), ANA_PGID_PGID, PGID_BC);
पूर्ण

पूर्णांक ocelot_port_pre_bridge_flags(काष्ठा ocelot *ocelot, पूर्णांक port,
				 काष्ठा चयनdev_brport_flags flags)
अणु
	अगर (flags.mask & ~(BR_LEARNING | BR_FLOOD | BR_MCAST_FLOOD |
			   BR_BCAST_FLOOD))
		वापस -EINVAL;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ocelot_port_pre_bridge_flags);

व्योम ocelot_port_bridge_flags(काष्ठा ocelot *ocelot, पूर्णांक port,
			      काष्ठा चयनdev_brport_flags flags)
अणु
	अगर (flags.mask & BR_LEARNING)
		ocelot_port_set_learning(ocelot, port,
					 !!(flags.val & BR_LEARNING));

	अगर (flags.mask & BR_FLOOD)
		ocelot_port_set_ucast_flood(ocelot, port,
					    !!(flags.val & BR_FLOOD));

	अगर (flags.mask & BR_MCAST_FLOOD)
		ocelot_port_set_mcast_flood(ocelot, port,
					    !!(flags.val & BR_MCAST_FLOOD));

	अगर (flags.mask & BR_BCAST_FLOOD)
		ocelot_port_set_bcast_flood(ocelot, port,
					    !!(flags.val & BR_BCAST_FLOOD));
पूर्ण
EXPORT_SYMBOL(ocelot_port_bridge_flags);

व्योम ocelot_init_port(काष्ठा ocelot *ocelot, पूर्णांक port)
अणु
	काष्ठा ocelot_port *ocelot_port = ocelot->ports[port];

	skb_queue_head_init(&ocelot_port->tx_skbs);
	spin_lock_init(&ocelot_port->ts_id_lock);

	/* Basic L2 initialization */

	/* Set MAC IFG Gaps
	 * FDX: TX_IFG = 5, RX_IFG1 = RX_IFG2 = 0
	 * !FDX: TX_IFG = 5, RX_IFG1 = RX_IFG2 = 5
	 */
	ocelot_port_ग_लिखोl(ocelot_port, DEV_MAC_IFG_CFG_TX_IFG(5),
			   DEV_MAC_IFG_CFG);

	/* Load seed (0) and set MAC HDX late collision  */
	ocelot_port_ग_लिखोl(ocelot_port, DEV_MAC_HDX_CFG_LATE_COL_POS(67) |
			   DEV_MAC_HDX_CFG_SEED_LOAD,
			   DEV_MAC_HDX_CFG);
	mdelay(1);
	ocelot_port_ग_लिखोl(ocelot_port, DEV_MAC_HDX_CFG_LATE_COL_POS(67),
			   DEV_MAC_HDX_CFG);

	/* Set Max Length and maximum tags allowed */
	ocelot_port_set_maxlen(ocelot, port, ETH_DATA_LEN);
	ocelot_port_ग_लिखोl(ocelot_port, DEV_MAC_TAGS_CFG_TAG_ID(ETH_P_8021AD) |
			   DEV_MAC_TAGS_CFG_VLAN_AWR_ENA |
			   DEV_MAC_TAGS_CFG_VLAN_DBL_AWR_ENA |
			   DEV_MAC_TAGS_CFG_VLAN_LEN_AWR_ENA,
			   DEV_MAC_TAGS_CFG);

	/* Set SMAC of Pause frame (00:00:00:00:00:00) */
	ocelot_port_ग_लिखोl(ocelot_port, 0, DEV_MAC_FC_MAC_HIGH_CFG);
	ocelot_port_ग_लिखोl(ocelot_port, 0, DEV_MAC_FC_MAC_LOW_CFG);

	/* Enable transmission of छोड़ो frames */
	ocelot_fields_ग_लिखो(ocelot, port, SYS_PAUSE_CFG_PAUSE_ENA, 1);

	/* Drop frames with multicast source address */
	ocelot_rmw_gix(ocelot, ANA_PORT_DROP_CFG_DROP_MC_SMAC_ENA,
		       ANA_PORT_DROP_CFG_DROP_MC_SMAC_ENA,
		       ANA_PORT_DROP_CFG, port);

	/* Set शेष VLAN and tag type to 8021Q. */
	ocelot_rmw_gix(ocelot, REW_PORT_VLAN_CFG_PORT_TPID(ETH_P_8021Q),
		       REW_PORT_VLAN_CFG_PORT_TPID_M,
		       REW_PORT_VLAN_CFG, port);

	/* Disable source address learning क्रम standalone mode */
	ocelot_port_set_learning(ocelot, port, false);

	/* Enable vcap lookups */
	ocelot_vcap_enable(ocelot, port);
पूर्ण
EXPORT_SYMBOL(ocelot_init_port);

/* Configure and enable the CPU port module, which is a set of queues
 * accessible through रेजिस्टर MMIO, frame DMA or Ethernet (in हाल
 * NPI mode is used).
 */
अटल व्योम ocelot_cpu_port_init(काष्ठा ocelot *ocelot)
अणु
	पूर्णांक cpu = ocelot->num_phys_ports;

	/* The unicast destination PGID क्रम the CPU port module is unused */
	ocelot_ग_लिखो_rix(ocelot, 0, ANA_PGID_PGID, cpu);
	/* Instead set up a multicast destination PGID क्रम traffic copied to
	 * the CPU. Whitelisted MAC addresses like the port netdevice MAC
	 * addresses will be copied to the CPU via this PGID.
	 */
	ocelot_ग_लिखो_rix(ocelot, BIT(cpu), ANA_PGID_PGID, PGID_CPU);
	ocelot_ग_लिखो_gix(ocelot, ANA_PORT_PORT_CFG_RECV_ENA |
			 ANA_PORT_PORT_CFG_PORTID_VAL(cpu),
			 ANA_PORT_PORT_CFG, cpu);

	/* Enable CPU port module */
	ocelot_fields_ग_लिखो(ocelot, cpu, QSYS_SWITCH_PORT_MODE_PORT_ENA, 1);
	/* CPU port Injection/Extraction configuration */
	ocelot_fields_ग_लिखो(ocelot, cpu, SYS_PORT_MODE_INCL_XTR_HDR,
			    OCELOT_TAG_PREFIX_NONE);
	ocelot_fields_ग_लिखो(ocelot, cpu, SYS_PORT_MODE_INCL_INJ_HDR,
			    OCELOT_TAG_PREFIX_NONE);

	/* Configure the CPU port to be VLAN aware */
	ocelot_ग_लिखो_gix(ocelot, ANA_PORT_VLAN_CFG_VLAN_VID(0) |
				 ANA_PORT_VLAN_CFG_VLAN_AWARE_ENA |
				 ANA_PORT_VLAN_CFG_VLAN_POP_CNT(1),
			 ANA_PORT_VLAN_CFG, cpu);
पूर्ण

अटल व्योम ocelot_detect_features(काष्ठा ocelot *ocelot)
अणु
	पूर्णांक mmgt, eq_ctrl;

	/* For Ocelot, Felix, Seville, Serval etc, SYS:MMGT:MMGT:FREECNT holds
	 * the number of 240-byte मुक्त memory words (aka 4-cell chunks) and not
	 * 192 bytes as the करोcumentation incorrectly says.
	 */
	mmgt = ocelot_पढ़ो(ocelot, SYS_MMGT);
	ocelot->packet_buffer_size = 240 * SYS_MMGT_FREECNT(mmgt);

	eq_ctrl = ocelot_पढ़ो(ocelot, QSYS_EQ_CTRL);
	ocelot->num_frame_refs = QSYS_MMGT_EQ_CTRL_FP_FREE_CNT(eq_ctrl);
पूर्ण

पूर्णांक ocelot_init(काष्ठा ocelot *ocelot)
अणु
	अक्षर queue_name[32];
	पूर्णांक i, ret;
	u32 port;

	अगर (ocelot->ops->reset) अणु
		ret = ocelot->ops->reset(ocelot);
		अगर (ret) अणु
			dev_err(ocelot->dev, "Switch reset failed\n");
			वापस ret;
		पूर्ण
	पूर्ण

	ocelot->stats = devm_kसुस्मृति(ocelot->dev,
				     ocelot->num_phys_ports * ocelot->num_stats,
				     माप(u64), GFP_KERNEL);
	अगर (!ocelot->stats)
		वापस -ENOMEM;

	mutex_init(&ocelot->stats_lock);
	mutex_init(&ocelot->ptp_lock);
	spin_lock_init(&ocelot->ptp_घड़ी_lock);
	snम_लिखो(queue_name, माप(queue_name), "%s-stats",
		 dev_name(ocelot->dev));
	ocelot->stats_queue = create_singlethपढ़ो_workqueue(queue_name);
	अगर (!ocelot->stats_queue)
		वापस -ENOMEM;

	ocelot->owq = alloc_ordered_workqueue("ocelot-owq", 0);
	अगर (!ocelot->owq) अणु
		destroy_workqueue(ocelot->stats_queue);
		वापस -ENOMEM;
	पूर्ण

	INIT_LIST_HEAD(&ocelot->multicast);
	INIT_LIST_HEAD(&ocelot->pgids);
	ocelot_detect_features(ocelot);
	ocelot_mact_init(ocelot);
	ocelot_vlan_init(ocelot);
	ocelot_vcap_init(ocelot);
	ocelot_cpu_port_init(ocelot);

	क्रम (port = 0; port < ocelot->num_phys_ports; port++) अणु
		/* Clear all counters (5 groups) */
		ocelot_ग_लिखो(ocelot, SYS_STAT_CFG_STAT_VIEW(port) |
				     SYS_STAT_CFG_STAT_CLEAR_SHOT(0x7f),
			     SYS_STAT_CFG);
	पूर्ण

	/* Only use S-Tag */
	ocelot_ग_लिखो(ocelot, ETH_P_8021AD, SYS_VLAN_ETYPE_CFG);

	/* Aggregation mode */
	ocelot_ग_लिखो(ocelot, ANA_AGGR_CFG_AC_SMAC_ENA |
			     ANA_AGGR_CFG_AC_DMAC_ENA |
			     ANA_AGGR_CFG_AC_IP4_SIPDIP_ENA |
			     ANA_AGGR_CFG_AC_IP4_TCPUDP_ENA |
			     ANA_AGGR_CFG_AC_IP6_FLOW_LBL_ENA |
			     ANA_AGGR_CFG_AC_IP6_TCPUDP_ENA,
			     ANA_AGGR_CFG);

	/* Set MAC age समय to शेष value. The entry is aged after
	 * 2*AGE_PERIOD
	 */
	ocelot_ग_लिखो(ocelot,
		     ANA_AUTOAGE_AGE_PERIOD(BR_DEFAULT_AGEING_TIME / 2 / HZ),
		     ANA_AUTOAGE);

	/* Disable learning क्रम frames discarded by VLAN ingress filtering */
	regmap_field_ग_लिखो(ocelot->regfields[ANA_ADVLEARN_VLAN_CHK], 1);

	/* Setup frame ageing - fixed value "2 sec" - in 6.5 us units */
	ocelot_ग_लिखो(ocelot, SYS_FRM_AGING_AGE_TX_ENA |
		     SYS_FRM_AGING_MAX_AGE(307692), SYS_FRM_AGING);

	/* Setup flooding PGIDs */
	क्रम (i = 0; i < ocelot->num_flooding_pgids; i++)
		ocelot_ग_लिखो_rix(ocelot, ANA_FLOODING_FLD_MULTICAST(PGID_MC) |
				 ANA_FLOODING_FLD_BROADCAST(PGID_BC) |
				 ANA_FLOODING_FLD_UNICAST(PGID_UC),
				 ANA_FLOODING, i);
	ocelot_ग_लिखो(ocelot, ANA_FLOODING_IPMC_FLD_MC6_DATA(PGID_MCIPV6) |
		     ANA_FLOODING_IPMC_FLD_MC6_CTRL(PGID_MC) |
		     ANA_FLOODING_IPMC_FLD_MC4_DATA(PGID_MCIPV4) |
		     ANA_FLOODING_IPMC_FLD_MC4_CTRL(PGID_MC),
		     ANA_FLOODING_IPMC);

	क्रम (port = 0; port < ocelot->num_phys_ports; port++) अणु
		/* Transmit the frame to the local port. */
		ocelot_ग_लिखो_rix(ocelot, BIT(port), ANA_PGID_PGID, port);
		/* Do not क्रमward BPDU frames to the front ports. */
		ocelot_ग_लिखो_gix(ocelot,
				 ANA_PORT_CPU_FWD_BPDU_CFG_BPDU_REसूची_ENA(0xffff),
				 ANA_PORT_CPU_FWD_BPDU_CFG,
				 port);
		/* Ensure bridging is disabled */
		ocelot_ग_लिखो_rix(ocelot, 0, ANA_PGID_PGID, PGID_SRC + port);
	पूर्ण

	क्रम_each_nonreserved_multicast_dest_pgid(ocelot, i) अणु
		u32 val = ANA_PGID_PGID_PGID(GENMASK(ocelot->num_phys_ports - 1, 0));

		ocelot_ग_लिखो_rix(ocelot, val, ANA_PGID_PGID, i);
	पूर्ण

	ocelot_ग_लिखो_rix(ocelot, 0, ANA_PGID_PGID, PGID_BLACKHOLE);

	/* Allow broadcast and unknown L2 multicast to the CPU. */
	ocelot_rmw_rix(ocelot, ANA_PGID_PGID_PGID(BIT(ocelot->num_phys_ports)),
		       ANA_PGID_PGID_PGID(BIT(ocelot->num_phys_ports)),
		       ANA_PGID_PGID, PGID_MC);
	ocelot_rmw_rix(ocelot, ANA_PGID_PGID_PGID(BIT(ocelot->num_phys_ports)),
		       ANA_PGID_PGID_PGID(BIT(ocelot->num_phys_ports)),
		       ANA_PGID_PGID, PGID_BC);
	ocelot_ग_लिखो_rix(ocelot, 0, ANA_PGID_PGID, PGID_MCIPV4);
	ocelot_ग_लिखो_rix(ocelot, 0, ANA_PGID_PGID, PGID_MCIPV6);

	/* Allow manual injection via DEVCPU_QS रेजिस्टरs, and byte swap these
	 * रेजिस्टरs endianness.
	 */
	ocelot_ग_लिखो_rix(ocelot, QS_INJ_GRP_CFG_BYTE_SWAP |
			 QS_INJ_GRP_CFG_MODE(1), QS_INJ_GRP_CFG, 0);
	ocelot_ग_लिखो_rix(ocelot, QS_XTR_GRP_CFG_BYTE_SWAP |
			 QS_XTR_GRP_CFG_MODE(1), QS_XTR_GRP_CFG, 0);
	ocelot_ग_लिखो(ocelot, ANA_CPUQ_CFG_CPUQ_MIRROR(2) |
		     ANA_CPUQ_CFG_CPUQ_LRN(2) |
		     ANA_CPUQ_CFG_CPUQ_MAC_COPY(2) |
		     ANA_CPUQ_CFG_CPUQ_SRC_COPY(2) |
		     ANA_CPUQ_CFG_CPUQ_LOCKED_PORTMOVE(2) |
		     ANA_CPUQ_CFG_CPUQ_ALLBRIDGE(6) |
		     ANA_CPUQ_CFG_CPUQ_IPMC_CTRL(6) |
		     ANA_CPUQ_CFG_CPUQ_IGMP(6) |
		     ANA_CPUQ_CFG_CPUQ_MLD(6), ANA_CPUQ_CFG);
	क्रम (i = 0; i < 16; i++)
		ocelot_ग_लिखो_rix(ocelot, ANA_CPUQ_8021_CFG_CPUQ_GARP_VAL(6) |
				 ANA_CPUQ_8021_CFG_CPUQ_BPDU_VAL(6),
				 ANA_CPUQ_8021_CFG, i);

	INIT_DELAYED_WORK(&ocelot->stats_work, ocelot_check_stats_work);
	queue_delayed_work(ocelot->stats_queue, &ocelot->stats_work,
			   OCELOT_STATS_CHECK_DELAY);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ocelot_init);

व्योम ocelot_deinit(काष्ठा ocelot *ocelot)
अणु
	cancel_delayed_work(&ocelot->stats_work);
	destroy_workqueue(ocelot->stats_queue);
	destroy_workqueue(ocelot->owq);
	mutex_destroy(&ocelot->stats_lock);
पूर्ण
EXPORT_SYMBOL(ocelot_deinit);

व्योम ocelot_deinit_port(काष्ठा ocelot *ocelot, पूर्णांक port)
अणु
	काष्ठा ocelot_port *ocelot_port = ocelot->ports[port];

	skb_queue_purge(&ocelot_port->tx_skbs);
पूर्ण
EXPORT_SYMBOL(ocelot_deinit_port);

MODULE_LICENSE("Dual MIT/GPL");
