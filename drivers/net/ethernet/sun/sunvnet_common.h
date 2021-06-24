<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _SUNVNETCOMMON_H
#घोषणा _SUNVNETCOMMON_H

#समावेश <linux/पूर्णांकerrupt.h>

/* length of समय (or less) we expect pending descriptors to be marked
 * as VIO_DESC_DONE and skbs पढ़ोy to be मुक्तd
 */
#घोषणा	VNET_CLEAN_TIMEOUT		((HZ / 100) + 1)

#घोषणा VNET_MAXPACKET			(65535ULL + ETH_HLEN + VLAN_HLEN)
#घोषणा VNET_TX_RING_SIZE		512
#घोषणा VNET_TX_WAKEUP_THRESH(dr)	((dr)->pending / 4)

#घोषणा	VNET_MINTSO	 2048	/* VIO protocol's minimum TSO len */
#घोषणा	VNET_MAXTSO	65535	/* VIO protocol's maximum TSO len */

#घोषणा VNET_MAX_MTU	65535

/* VNET packets are sent in buffers with the first 6 bytes skipped
 * so that after the ethernet header the IPv4/IPv6 headers are aligned
 * properly.
 */
#घोषणा VNET_PACKET_SKIP		6

#घोषणा	VNET_MAXCOOKIES			(VNET_MAXPACKET / PAGE_SIZE + 1)

#घोषणा	VNET_MAX_TXQS		16

काष्ठा vnet_tx_entry अणु
	काष्ठा sk_buff		*skb;
	अचिन्हित पूर्णांक		ncookies;
	काष्ठा ldc_trans_cookie	cookies[VNET_MAXCOOKIES];
पूर्ण;

काष्ठा vnet;

काष्ठा vnet_port_stats अणु
	/* keep them all the same size */
	u32 rx_bytes;
	u32 tx_bytes;
	u32 rx_packets;
	u32 tx_packets;
	u32 event_up;
	u32 event_reset;
	u32 q_placeholder;
पूर्ण;

#घोषणा NUM_VNET_PORT_STATS  (माप(काष्ठा vnet_port_stats) / माप(u32))

/* Structure to describe a vnet-port or vsw-port in the MD.
 * If the vsw bit is set, this काष्ठाure represents a vचयन
 * port, and the net_device can be found from ->dev. If the
 * vsw bit is not set, the net_device is available from ->vp->dev.
 * See the VNET_PORT_TO_NET_DEVICE macro below.
 */
काष्ठा vnet_port अणु
	काष्ठा vio_driver_state	vio;

	काष्ठा vnet_port_stats stats;

	काष्ठा hlist_node	hash;
	u8			raddr[ETH_ALEN];
	अचिन्हित		चयन_port:1;
	अचिन्हित		tso:1;
	अचिन्हित		vsw:1;
	अचिन्हित		__pad:13;

	काष्ठा vnet		*vp;
	काष्ठा net_device	*dev;

	काष्ठा vnet_tx_entry	tx_bufs[VNET_TX_RING_SIZE];

	काष्ठा list_head	list;

	u32			stop_rx_idx;
	bool			stop_rx;
	bool			start_cons;

	काष्ठा समयr_list	clean_समयr;

	u64			rmtu;
	u16			tsolen;

	काष्ठा napi_काष्ठा	napi;
	u32			napi_stop_idx;
	bool			napi_resume;
	पूर्णांक			rx_event;
	u16			q_index;
पूर्ण;

अटल अंतरभूत काष्ठा vnet_port *to_vnet_port(काष्ठा vio_driver_state *vio)
अणु
	वापस container_of(vio, काष्ठा vnet_port, vio);
पूर्ण

#घोषणा VNET_PORT_HASH_SIZE	16
#घोषणा VNET_PORT_HASH_MASK	(VNET_PORT_HASH_SIZE - 1)

अटल अंतरभूत अचिन्हित पूर्णांक vnet_hashfn(u8 *mac)
अणु
	अचिन्हित पूर्णांक val = mac[4] ^ mac[5];

	वापस val & (VNET_PORT_HASH_MASK);
पूर्ण

काष्ठा vnet_mcast_entry अणु
	u8			addr[ETH_ALEN];
	u8			sent;
	u8			hit;
	काष्ठा vnet_mcast_entry	*next;
पूर्ण;

काष्ठा vnet अणु
	spinlock_t		lock; /* Protects port_list and port_hash.  */
	काष्ठा net_device	*dev;
	u32			msg_enable;
	u8			q_used[VNET_MAX_TXQS];
	काष्ठा list_head	port_list;
	काष्ठा hlist_head	port_hash[VNET_PORT_HASH_SIZE];
	काष्ठा vnet_mcast_entry	*mcast_list;
	काष्ठा list_head	list;
	u64			local_mac;
	पूर्णांक			nports;
पूर्ण;

/* Def used by common code to get the net_device from the proper location */
#घोषणा VNET_PORT_TO_NET_DEVICE(__port) \
	((__port)->vsw ? (__port)->dev : (__port)->vp->dev)

/* Common funcs */
व्योम sunvnet_clean_समयr_expire_common(काष्ठा समयr_list *t);
पूर्णांक sunvnet_खोलो_common(काष्ठा net_device *dev);
पूर्णांक sunvnet_बंद_common(काष्ठा net_device *dev);
व्योम sunvnet_set_rx_mode_common(काष्ठा net_device *dev, काष्ठा vnet *vp);
पूर्णांक sunvnet_set_mac_addr_common(काष्ठा net_device *dev, व्योम *p);
व्योम sunvnet_tx_समयout_common(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue);
netdev_tx_t
sunvnet_start_xmit_common(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
			  काष्ठा vnet_port *(*vnet_tx_port)
			  (काष्ठा sk_buff *, काष्ठा net_device *));
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
व्योम sunvnet_poll_controller_common(काष्ठा net_device *dev, काष्ठा vnet *vp);
#पूर्ण_अगर
व्योम sunvnet_event_common(व्योम *arg, पूर्णांक event);
पूर्णांक sunvnet_send_attr_common(काष्ठा vio_driver_state *vio);
पूर्णांक sunvnet_handle_attr_common(काष्ठा vio_driver_state *vio, व्योम *arg);
व्योम sunvnet_handshake_complete_common(काष्ठा vio_driver_state *vio);
पूर्णांक sunvnet_poll_common(काष्ठा napi_काष्ठा *napi, पूर्णांक budget);
व्योम sunvnet_port_मुक्त_tx_bufs_common(काष्ठा vnet_port *port);
व्योम vnet_port_reset(काष्ठा vnet_port *port);
bool sunvnet_port_is_up_common(काष्ठा vnet_port *vnet);
व्योम sunvnet_port_add_txq_common(काष्ठा vnet_port *port);
व्योम sunvnet_port_rm_txq_common(काष्ठा vnet_port *port);

#पूर्ण_अगर /* _SUNVNETCOMMON_H */
