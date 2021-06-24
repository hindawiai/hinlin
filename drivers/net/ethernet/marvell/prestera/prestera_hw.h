<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0 */
/* Copyright (c) 2019-2020 Marvell International Ltd. All rights reserved. */

#अगर_अघोषित _PRESTERA_HW_H_
#घोषणा _PRESTERA_HW_H_

#समावेश <linux/types.h>

क्रमागत prestera_accept_frm_type अणु
	PRESTERA_ACCEPT_FRAME_TYPE_TAGGED,
	PRESTERA_ACCEPT_FRAME_TYPE_UNTAGGED,
	PRESTERA_ACCEPT_FRAME_TYPE_ALL,
पूर्ण;

क्रमागत prestera_fdb_flush_mode अणु
	PRESTERA_FDB_FLUSH_MODE_DYNAMIC = BIT(0),
	PRESTERA_FDB_FLUSH_MODE_STATIC = BIT(1),
	PRESTERA_FDB_FLUSH_MODE_ALL = PRESTERA_FDB_FLUSH_MODE_DYNAMIC
					| PRESTERA_FDB_FLUSH_MODE_STATIC,
पूर्ण;

क्रमागत अणु
	PRESTERA_LINK_MODE_10baseT_Half,
	PRESTERA_LINK_MODE_10baseT_Full,
	PRESTERA_LINK_MODE_100baseT_Half,
	PRESTERA_LINK_MODE_100baseT_Full,
	PRESTERA_LINK_MODE_1000baseT_Half,
	PRESTERA_LINK_MODE_1000baseT_Full,
	PRESTERA_LINK_MODE_1000baseX_Full,
	PRESTERA_LINK_MODE_1000baseKX_Full,
	PRESTERA_LINK_MODE_2500baseX_Full,
	PRESTERA_LINK_MODE_10GbaseKR_Full,
	PRESTERA_LINK_MODE_10GbaseSR_Full,
	PRESTERA_LINK_MODE_10GbaseLR_Full,
	PRESTERA_LINK_MODE_20GbaseKR2_Full,
	PRESTERA_LINK_MODE_25GbaseCR_Full,
	PRESTERA_LINK_MODE_25GbaseKR_Full,
	PRESTERA_LINK_MODE_25GbaseSR_Full,
	PRESTERA_LINK_MODE_40GbaseKR4_Full,
	PRESTERA_LINK_MODE_40GbaseCR4_Full,
	PRESTERA_LINK_MODE_40GbaseSR4_Full,
	PRESTERA_LINK_MODE_50GbaseCR2_Full,
	PRESTERA_LINK_MODE_50GbaseKR2_Full,
	PRESTERA_LINK_MODE_50GbaseSR2_Full,
	PRESTERA_LINK_MODE_100GbaseKR4_Full,
	PRESTERA_LINK_MODE_100GbaseSR4_Full,
	PRESTERA_LINK_MODE_100GbaseCR4_Full,

	PRESTERA_LINK_MODE_MAX
पूर्ण;

क्रमागत अणु
	PRESTERA_PORT_TYPE_NONE,
	PRESTERA_PORT_TYPE_TP,
	PRESTERA_PORT_TYPE_AUI,
	PRESTERA_PORT_TYPE_MII,
	PRESTERA_PORT_TYPE_FIBRE,
	PRESTERA_PORT_TYPE_BNC,
	PRESTERA_PORT_TYPE_DA,
	PRESTERA_PORT_TYPE_OTHER,

	PRESTERA_PORT_TYPE_MAX
पूर्ण;

क्रमागत अणु
	PRESTERA_PORT_TCVR_COPPER,
	PRESTERA_PORT_TCVR_SFP,

	PRESTERA_PORT_TCVR_MAX
पूर्ण;

क्रमागत अणु
	PRESTERA_PORT_FEC_OFF,
	PRESTERA_PORT_FEC_BASER,
	PRESTERA_PORT_FEC_RS,

	PRESTERA_PORT_FEC_MAX
पूर्ण;

क्रमागत अणु
	PRESTERA_PORT_DUPLEX_HALF,
	PRESTERA_PORT_DUPLEX_FULL,
पूर्ण;

क्रमागत अणु
	PRESTERA_STP_DISABLED,
	PRESTERA_STP_BLOCK_LISTEN,
	PRESTERA_STP_LEARN,
	PRESTERA_STP_FORWARD,
पूर्ण;

काष्ठा prestera_चयन;
काष्ठा prestera_port;
काष्ठा prestera_port_stats;
काष्ठा prestera_port_caps;
क्रमागत prestera_event_type;
काष्ठा prestera_event;

प्रकार व्योम (*prestera_event_cb_t)
	(काष्ठा prestera_चयन *sw, काष्ठा prestera_event *evt, व्योम *arg);

काष्ठा prestera_rxtx_params;

/* Switch API */
पूर्णांक prestera_hw_चयन_init(काष्ठा prestera_चयन *sw);
व्योम prestera_hw_चयन_fini(काष्ठा prestera_चयन *sw);
पूर्णांक prestera_hw_चयन_ageing_set(काष्ठा prestera_चयन *sw, u32 ageing_ms);
पूर्णांक prestera_hw_चयन_mac_set(काष्ठा prestera_चयन *sw, स्थिर अक्षर *mac);

/* Port API */
पूर्णांक prestera_hw_port_info_get(स्थिर काष्ठा prestera_port *port,
			      u32 *dev_id, u32 *hw_id, u16 *fp_id);
पूर्णांक prestera_hw_port_state_set(स्थिर काष्ठा prestera_port *port,
			       bool admin_state);
पूर्णांक prestera_hw_port_mtu_set(स्थिर काष्ठा prestera_port *port, u32 mtu);
पूर्णांक prestera_hw_port_mtu_get(स्थिर काष्ठा prestera_port *port, u32 *mtu);
पूर्णांक prestera_hw_port_mac_set(स्थिर काष्ठा prestera_port *port, स्थिर अक्षर *mac);
पूर्णांक prestera_hw_port_mac_get(स्थिर काष्ठा prestera_port *port, अक्षर *mac);
पूर्णांक prestera_hw_port_cap_get(स्थिर काष्ठा prestera_port *port,
			     काष्ठा prestera_port_caps *caps);
पूर्णांक prestera_hw_port_remote_cap_get(स्थिर काष्ठा prestera_port *port,
				    u64 *link_mode_biपंचांगap);
पूर्णांक prestera_hw_port_remote_fc_get(स्थिर काष्ठा prestera_port *port,
				   bool *छोड़ो, bool *asym_छोड़ो);
पूर्णांक prestera_hw_port_type_get(स्थिर काष्ठा prestera_port *port, u8 *type);
पूर्णांक prestera_hw_port_fec_get(स्थिर काष्ठा prestera_port *port, u8 *fec);
पूर्णांक prestera_hw_port_fec_set(स्थिर काष्ठा prestera_port *port, u8 fec);
पूर्णांक prestera_hw_port_स्वतःneg_set(स्थिर काष्ठा prestera_port *port,
				 bool स्वतःneg, u64 link_modes, u8 fec);
पूर्णांक prestera_hw_port_स्वतःneg_restart(काष्ठा prestera_port *port);
पूर्णांक prestera_hw_port_duplex_get(स्थिर काष्ठा prestera_port *port, u8 *duplex);
पूर्णांक prestera_hw_port_stats_get(स्थिर काष्ठा prestera_port *port,
			       काष्ठा prestera_port_stats *stats);
पूर्णांक prestera_hw_port_link_mode_set(स्थिर काष्ठा prestera_port *port, u32 mode);
पूर्णांक prestera_hw_port_link_mode_get(स्थिर काष्ठा prestera_port *port, u32 *mode);
पूर्णांक prestera_hw_port_mdix_get(स्थिर काष्ठा prestera_port *port, u8 *status,
			      u8 *admin_mode);
पूर्णांक prestera_hw_port_mdix_set(स्थिर काष्ठा prestera_port *port, u8 mode);
पूर्णांक prestera_hw_port_speed_get(स्थिर काष्ठा prestera_port *port, u32 *speed);
पूर्णांक prestera_hw_port_learning_set(काष्ठा prestera_port *port, bool enable);
पूर्णांक prestera_hw_port_flood_set(काष्ठा prestera_port *port, bool flood);
पूर्णांक prestera_hw_port_accept_frm_type(काष्ठा prestera_port *port,
				     क्रमागत prestera_accept_frm_type type);
/* Vlan API */
पूर्णांक prestera_hw_vlan_create(काष्ठा prestera_चयन *sw, u16 vid);
पूर्णांक prestera_hw_vlan_delete(काष्ठा prestera_चयन *sw, u16 vid);
पूर्णांक prestera_hw_vlan_port_set(काष्ठा prestera_port *port, u16 vid,
			      bool is_member, bool untagged);
पूर्णांक prestera_hw_vlan_port_vid_set(काष्ठा prestera_port *port, u16 vid);
पूर्णांक prestera_hw_vlan_port_stp_set(काष्ठा prestera_port *port, u16 vid, u8 state);

/* FDB API */
पूर्णांक prestera_hw_fdb_add(काष्ठा prestera_port *port, स्थिर अचिन्हित अक्षर *mac,
			u16 vid, bool dynamic);
पूर्णांक prestera_hw_fdb_del(काष्ठा prestera_port *port, स्थिर अचिन्हित अक्षर *mac,
			u16 vid);
पूर्णांक prestera_hw_fdb_flush_port(काष्ठा prestera_port *port, u32 mode);
पूर्णांक prestera_hw_fdb_flush_vlan(काष्ठा prestera_चयन *sw, u16 vid, u32 mode);
पूर्णांक prestera_hw_fdb_flush_port_vlan(काष्ठा prestera_port *port, u16 vid,
				    u32 mode);

/* Bridge API */
पूर्णांक prestera_hw_bridge_create(काष्ठा prestera_चयन *sw, u16 *bridge_id);
पूर्णांक prestera_hw_bridge_delete(काष्ठा prestera_चयन *sw, u16 bridge_id);
पूर्णांक prestera_hw_bridge_port_add(काष्ठा prestera_port *port, u16 bridge_id);
पूर्णांक prestera_hw_bridge_port_delete(काष्ठा prestera_port *port, u16 bridge_id);

/* Event handlers */
पूर्णांक prestera_hw_event_handler_रेजिस्टर(काष्ठा prestera_चयन *sw,
				       क्रमागत prestera_event_type type,
				       prestera_event_cb_t fn,
				       व्योम *arg);
व्योम prestera_hw_event_handler_unरेजिस्टर(काष्ठा prestera_चयन *sw,
					  क्रमागत prestera_event_type type,
					  prestera_event_cb_t fn);

/* RX/TX */
पूर्णांक prestera_hw_rxtx_init(काष्ठा prestera_चयन *sw,
			  काष्ठा prestera_rxtx_params *params);
पूर्णांक prestera_hw_rxtx_port_init(काष्ठा prestera_port *port);

#पूर्ण_अगर /* _PRESTERA_HW_H_ */
