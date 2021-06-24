<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause) */
/* Copyright (C) 2017-2018 Netronome Systems, Inc. */

#अगर_अघोषित _NFP_PORT_H_
#घोषणा _NFP_PORT_H_

#समावेश <net/devlink.h>

काष्ठा net_device;
काष्ठा netdev_phys_item_id;
काष्ठा nfp_app;
काष्ठा nfp_pf;
काष्ठा nfp_port;

/**
 * क्रमागत nfp_port_type - type of port NFP can चयन traffic to
 * @NFP_PORT_INVALID:	port is invalid, %NFP_PORT_PHYS_PORT transitions to this
 *			state when port disappears because of FW fault or config
 *			change
 * @NFP_PORT_PHYS_PORT:	बाह्यal NIC port
 * @NFP_PORT_PF_PORT:	logical port of PCI PF
 * @NFP_PORT_VF_PORT:	logical port of PCI VF
 */
क्रमागत nfp_port_type अणु
	NFP_PORT_INVALID,
	NFP_PORT_PHYS_PORT,
	NFP_PORT_PF_PORT,
	NFP_PORT_VF_PORT,
पूर्ण;

/**
 * क्रमागत nfp_port_flags - port flags (can be type-specअगरic)
 * @NFP_PORT_CHANGED:	port state has changed since last eth table refresh;
 *			क्रम NFP_PORT_PHYS_PORT, never set otherwise; must hold
 *			rtnl_lock to clear
 */
क्रमागत nfp_port_flags अणु
	NFP_PORT_CHANGED = 0,
पूर्ण;

/**
 * काष्ठा nfp_port - काष्ठाure representing NFP port
 * @netdev:	backpoपूर्णांकer to associated netdev
 * @type:	what port type करोes the entity represent
 * @flags:	port flags
 * @tc_offload_cnt:	number of active TC offloads, how offloads are counted
 *			is not defined, use as a boolean
 * @app:	backpoपूर्णांकer to the app काष्ठाure
 * @dl_port:	devlink port काष्ठाure
 * @eth_id:	क्रम %NFP_PORT_PHYS_PORT port ID in NFP क्रमागतeration scheme
 * @eth_क्रमced:	क्रम %NFP_PORT_PHYS_PORT port is क्रमced UP or DOWN, करोn't change
 * @eth_port:	क्रम %NFP_PORT_PHYS_PORT translated ETH Table port entry
 * @eth_stats:	क्रम %NFP_PORT_PHYS_PORT MAC stats अगर available
 * @pf_id:	क्रम %NFP_PORT_PF_PORT, %NFP_PORT_VF_PORT ID of the PCI PF (0-3)
 * @vf_id:	क्रम %NFP_PORT_VF_PORT ID of the PCI VF within @pf_id
 * @pf_split:	क्रम %NFP_PORT_PF_PORT %true अगर PCI PF has more than one vNIC
 * @pf_split_id:क्रम %NFP_PORT_PF_PORT ID of PCI PF vNIC (valid अगर @pf_split)
 * @vnic:	क्रम %NFP_PORT_PF_PORT, %NFP_PORT_VF_PORT vNIC ctrl memory
 * @port_list:	entry on pf's list of ports
 */
काष्ठा nfp_port अणु
	काष्ठा net_device *netdev;
	क्रमागत nfp_port_type type;

	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ tc_offload_cnt;

	काष्ठा nfp_app *app;

	काष्ठा devlink_port dl_port;

	जोड़ अणु
		/* NFP_PORT_PHYS_PORT */
		काष्ठा अणु
			अचिन्हित पूर्णांक eth_id;
			bool eth_क्रमced;
			काष्ठा nfp_eth_table_port *eth_port;
			u8 __iomem *eth_stats;
		पूर्ण;
		/* NFP_PORT_PF_PORT, NFP_PORT_VF_PORT */
		काष्ठा अणु
			अचिन्हित पूर्णांक pf_id;
			अचिन्हित पूर्णांक vf_id;
			bool pf_split;
			अचिन्हित पूर्णांक pf_split_id;
			u8 __iomem *vnic;
		पूर्ण;
	पूर्ण;

	काष्ठा list_head port_list;
पूर्ण;

बाह्य स्थिर काष्ठा ethtool_ops nfp_port_ethtool_ops;

पूर्णांक nfp_port_setup_tc(काष्ठा net_device *netdev, क्रमागत tc_setup_type type,
		      व्योम *type_data);

अटल अंतरभूत bool nfp_port_is_vnic(स्थिर काष्ठा nfp_port *port)
अणु
	वापस port->type == NFP_PORT_PF_PORT || port->type == NFP_PORT_VF_PORT;
पूर्ण

पूर्णांक
nfp_port_set_features(काष्ठा net_device *netdev, netdev_features_t features);

काष्ठा nfp_port *nfp_port_from_netdev(काष्ठा net_device *netdev);
पूर्णांक nfp_port_get_port_parent_id(काष्ठा net_device *netdev,
				काष्ठा netdev_phys_item_id *ppid);
काष्ठा nfp_port *
nfp_port_from_id(काष्ठा nfp_pf *pf, क्रमागत nfp_port_type type, अचिन्हित पूर्णांक id);
काष्ठा nfp_eth_table_port *__nfp_port_get_eth_port(काष्ठा nfp_port *port);
काष्ठा nfp_eth_table_port *nfp_port_get_eth_port(काष्ठा nfp_port *port);

पूर्णांक
nfp_port_get_phys_port_name(काष्ठा net_device *netdev, अक्षर *name, माप_प्रकार len);
पूर्णांक nfp_port_configure(काष्ठा net_device *netdev, bool configed);

काष्ठा nfp_port *
nfp_port_alloc(काष्ठा nfp_app *app, क्रमागत nfp_port_type type,
	       काष्ठा net_device *netdev);
व्योम nfp_port_मुक्त(काष्ठा nfp_port *port);

पूर्णांक nfp_port_init_phy_port(काष्ठा nfp_pf *pf, काष्ठा nfp_app *app,
			   काष्ठा nfp_port *port, अचिन्हित पूर्णांक id);

पूर्णांक nfp_net_refresh_eth_port(काष्ठा nfp_port *port);
व्योम nfp_net_refresh_port_table(काष्ठा nfp_port *port);
पूर्णांक nfp_net_refresh_port_table_sync(काष्ठा nfp_pf *pf);

पूर्णांक nfp_devlink_port_रेजिस्टर(काष्ठा nfp_app *app, काष्ठा nfp_port *port);
व्योम nfp_devlink_port_unरेजिस्टर(काष्ठा nfp_port *port);
व्योम nfp_devlink_port_type_eth_set(काष्ठा nfp_port *port);
व्योम nfp_devlink_port_type_clear(काष्ठा nfp_port *port);

/**
 * Mac stats (0x0000 - 0x0200)
 * all counters are 64bit.
 */
#घोषणा NFP_MAC_STATS_BASE                0x0000
#घोषणा NFP_MAC_STATS_SIZE                0x0200

#घोषणा NFP_MAC_STATS_RX_IN_OCTETS			(NFP_MAC_STATS_BASE + 0x000)
							/* unused 0x008 */
#घोषणा NFP_MAC_STATS_RX_FRAME_TOO_LONG_ERRORS		(NFP_MAC_STATS_BASE + 0x010)
#घोषणा NFP_MAC_STATS_RX_RANGE_LENGTH_ERRORS		(NFP_MAC_STATS_BASE + 0x018)
#घोषणा NFP_MAC_STATS_RX_VLAN_RECEIVED_OK		(NFP_MAC_STATS_BASE + 0x020)
#घोषणा NFP_MAC_STATS_RX_IN_ERRORS			(NFP_MAC_STATS_BASE + 0x028)
#घोषणा NFP_MAC_STATS_RX_IN_BROADCAST_PKTS		(NFP_MAC_STATS_BASE + 0x030)
#घोषणा NFP_MAC_STATS_RX_DROP_EVENTS			(NFP_MAC_STATS_BASE + 0x038)
#घोषणा NFP_MAC_STATS_RX_ALIGNMENT_ERRORS		(NFP_MAC_STATS_BASE + 0x040)
#घोषणा NFP_MAC_STATS_RX_PAUSE_MAC_CTRL_FRAMES		(NFP_MAC_STATS_BASE + 0x048)
#घोषणा NFP_MAC_STATS_RX_FRAMES_RECEIVED_OK		(NFP_MAC_STATS_BASE + 0x050)
#घोषणा NFP_MAC_STATS_RX_FRAME_CHECK_SEQUENCE_ERRORS	(NFP_MAC_STATS_BASE + 0x058)
#घोषणा NFP_MAC_STATS_RX_UNICAST_PKTS			(NFP_MAC_STATS_BASE + 0x060)
#घोषणा NFP_MAC_STATS_RX_MULTICAST_PKTS			(NFP_MAC_STATS_BASE + 0x068)
#घोषणा NFP_MAC_STATS_RX_PKTS				(NFP_MAC_STATS_BASE + 0x070)
#घोषणा NFP_MAC_STATS_RX_UNDERSIZE_PKTS			(NFP_MAC_STATS_BASE + 0x078)
#घोषणा NFP_MAC_STATS_RX_PKTS_64_OCTETS			(NFP_MAC_STATS_BASE + 0x080)
#घोषणा NFP_MAC_STATS_RX_PKTS_65_TO_127_OCTETS		(NFP_MAC_STATS_BASE + 0x088)
#घोषणा NFP_MAC_STATS_RX_PKTS_512_TO_1023_OCTETS	(NFP_MAC_STATS_BASE + 0x090)
#घोषणा NFP_MAC_STATS_RX_PKTS_1024_TO_1518_OCTETS	(NFP_MAC_STATS_BASE + 0x098)
#घोषणा NFP_MAC_STATS_RX_JABBERS			(NFP_MAC_STATS_BASE + 0x0a0)
#घोषणा NFP_MAC_STATS_RX_FRAGMENTS			(NFP_MAC_STATS_BASE + 0x0a8)
#घोषणा NFP_MAC_STATS_RX_PAUSE_FRAMES_CLASS2		(NFP_MAC_STATS_BASE + 0x0b0)
#घोषणा NFP_MAC_STATS_RX_PAUSE_FRAMES_CLASS3		(NFP_MAC_STATS_BASE + 0x0b8)
#घोषणा NFP_MAC_STATS_RX_PKTS_128_TO_255_OCTETS		(NFP_MAC_STATS_BASE + 0x0c0)
#घोषणा NFP_MAC_STATS_RX_PKTS_256_TO_511_OCTETS		(NFP_MAC_STATS_BASE + 0x0c8)
#घोषणा NFP_MAC_STATS_RX_PKTS_1519_TO_MAX_OCTETS	(NFP_MAC_STATS_BASE + 0x0d0)
#घोषणा NFP_MAC_STATS_RX_OVERSIZE_PKTS			(NFP_MAC_STATS_BASE + 0x0d8)
#घोषणा NFP_MAC_STATS_RX_PAUSE_FRAMES_CLASS0		(NFP_MAC_STATS_BASE + 0x0e0)
#घोषणा NFP_MAC_STATS_RX_PAUSE_FRAMES_CLASS1		(NFP_MAC_STATS_BASE + 0x0e8)
#घोषणा NFP_MAC_STATS_RX_PAUSE_FRAMES_CLASS4		(NFP_MAC_STATS_BASE + 0x0f0)
#घोषणा NFP_MAC_STATS_RX_PAUSE_FRAMES_CLASS5		(NFP_MAC_STATS_BASE + 0x0f8)
#घोषणा NFP_MAC_STATS_RX_PAUSE_FRAMES_CLASS6		(NFP_MAC_STATS_BASE + 0x100)
#घोषणा NFP_MAC_STATS_RX_PAUSE_FRAMES_CLASS7		(NFP_MAC_STATS_BASE + 0x108)
#घोषणा NFP_MAC_STATS_RX_MAC_CTRL_FRAMES_RECEIVED	(NFP_MAC_STATS_BASE + 0x110)
#घोषणा NFP_MAC_STATS_RX_MAC_HEAD_DROP			(NFP_MAC_STATS_BASE + 0x118)
							/* unused 0x120 */
							/* unused 0x128 */
							/* unused 0x130 */
#घोषणा NFP_MAC_STATS_TX_QUEUE_DROP			(NFP_MAC_STATS_BASE + 0x138)
#घोषणा NFP_MAC_STATS_TX_OUT_OCTETS			(NFP_MAC_STATS_BASE + 0x140)
							/* unused 0x148 */
#घोषणा NFP_MAC_STATS_TX_VLAN_TRANSMITTED_OK		(NFP_MAC_STATS_BASE + 0x150)
#घोषणा NFP_MAC_STATS_TX_OUT_ERRORS			(NFP_MAC_STATS_BASE + 0x158)
#घोषणा NFP_MAC_STATS_TX_BROADCAST_PKTS			(NFP_MAC_STATS_BASE + 0x160)
#घोषणा NFP_MAC_STATS_TX_PKTS_64_OCTETS			(NFP_MAC_STATS_BASE + 0x168)
#घोषणा NFP_MAC_STATS_TX_PKTS_256_TO_511_OCTETS		(NFP_MAC_STATS_BASE + 0x170)
#घोषणा NFP_MAC_STATS_TX_PKTS_512_TO_1023_OCTETS	(NFP_MAC_STATS_BASE + 0x178)
#घोषणा NFP_MAC_STATS_TX_PAUSE_MAC_CTRL_FRAMES		(NFP_MAC_STATS_BASE + 0x180)
#घोषणा NFP_MAC_STATS_TX_FRAMES_TRANSMITTED_OK		(NFP_MAC_STATS_BASE + 0x188)
#घोषणा NFP_MAC_STATS_TX_UNICAST_PKTS			(NFP_MAC_STATS_BASE + 0x190)
#घोषणा NFP_MAC_STATS_TX_MULTICAST_PKTS			(NFP_MAC_STATS_BASE + 0x198)
#घोषणा NFP_MAC_STATS_TX_PKTS_65_TO_127_OCTETS		(NFP_MAC_STATS_BASE + 0x1a0)
#घोषणा NFP_MAC_STATS_TX_PKTS_128_TO_255_OCTETS		(NFP_MAC_STATS_BASE + 0x1a8)
#घोषणा NFP_MAC_STATS_TX_PKTS_1024_TO_1518_OCTETS	(NFP_MAC_STATS_BASE + 0x1b0)
#घोषणा NFP_MAC_STATS_TX_PKTS_1519_TO_MAX_OCTETS	(NFP_MAC_STATS_BASE + 0x1b8)
#घोषणा NFP_MAC_STATS_TX_PAUSE_FRAMES_CLASS0		(NFP_MAC_STATS_BASE + 0x1c0)
#घोषणा NFP_MAC_STATS_TX_PAUSE_FRAMES_CLASS1		(NFP_MAC_STATS_BASE + 0x1c8)
#घोषणा NFP_MAC_STATS_TX_PAUSE_FRAMES_CLASS4		(NFP_MAC_STATS_BASE + 0x1d0)
#घोषणा NFP_MAC_STATS_TX_PAUSE_FRAMES_CLASS5		(NFP_MAC_STATS_BASE + 0x1d8)
#घोषणा NFP_MAC_STATS_TX_PAUSE_FRAMES_CLASS2		(NFP_MAC_STATS_BASE + 0x1e0)
#घोषणा NFP_MAC_STATS_TX_PAUSE_FRAMES_CLASS3		(NFP_MAC_STATS_BASE + 0x1e8)
#घोषणा NFP_MAC_STATS_TX_PAUSE_FRAMES_CLASS6		(NFP_MAC_STATS_BASE + 0x1f0)
#घोषणा NFP_MAC_STATS_TX_PAUSE_FRAMES_CLASS7		(NFP_MAC_STATS_BASE + 0x1f8)

#पूर्ण_अगर
