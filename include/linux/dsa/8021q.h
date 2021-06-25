<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 * Copyright (c) 2019, Vladimir Oltean <olteanv@gmail.com>
 */

#अगर_अघोषित _NET_DSA_8021Q_H
#घोषणा _NET_DSA_8021Q_H

#समावेश <linux/refcount.h>
#समावेश <linux/types.h>

काष्ठा dsa_चयन;
काष्ठा sk_buff;
काष्ठा net_device;
काष्ठा packet_type;
काष्ठा dsa_8021q_context;

काष्ठा dsa_8021q_crosschip_link अणु
	काष्ठा list_head list;
	पूर्णांक port;
	काष्ठा dsa_8021q_context *other_ctx;
	पूर्णांक other_port;
	refcount_t refcount;
पूर्ण;

काष्ठा dsa_8021q_ops अणु
	पूर्णांक (*vlan_add)(काष्ठा dsa_चयन *ds, पूर्णांक port, u16 vid, u16 flags);
	पूर्णांक (*vlan_del)(काष्ठा dsa_चयन *ds, पूर्णांक port, u16 vid);
पूर्ण;

काष्ठा dsa_8021q_context अणु
	स्थिर काष्ठा dsa_8021q_ops *ops;
	काष्ठा dsa_चयन *ds;
	काष्ठा list_head crosschip_links;
	/* EtherType of RX VID, used क्रम filtering on master पूर्णांकerface */
	__be16 proto;
पूर्ण;

#घोषणा DSA_8021Q_N_SUBVLAN			8

#अगर IS_ENABLED(CONFIG_NET_DSA_TAG_8021Q)

पूर्णांक dsa_8021q_setup(काष्ठा dsa_8021q_context *ctx, bool enabled);

पूर्णांक dsa_8021q_crosschip_bridge_join(काष्ठा dsa_8021q_context *ctx, पूर्णांक port,
				    काष्ठा dsa_8021q_context *other_ctx,
				    पूर्णांक other_port);

पूर्णांक dsa_8021q_crosschip_bridge_leave(काष्ठा dsa_8021q_context *ctx, पूर्णांक port,
				     काष्ठा dsa_8021q_context *other_ctx,
				     पूर्णांक other_port);

काष्ठा sk_buff *dsa_8021q_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *netdev,
			       u16 tpid, u16 tci);

u16 dsa_8021q_tx_vid(काष्ठा dsa_चयन *ds, पूर्णांक port);

u16 dsa_8021q_rx_vid(काष्ठा dsa_चयन *ds, पूर्णांक port);

u16 dsa_8021q_rx_vid_subvlan(काष्ठा dsa_चयन *ds, पूर्णांक port, u16 subvlan);

पूर्णांक dsa_8021q_rx_चयन_id(u16 vid);

पूर्णांक dsa_8021q_rx_source_port(u16 vid);

u16 dsa_8021q_rx_subvlan(u16 vid);

bool vid_is_dsa_8021q_rxvlan(u16 vid);

bool vid_is_dsa_8021q_txvlan(u16 vid);

bool vid_is_dsa_8021q(u16 vid);

#अन्यथा

पूर्णांक dsa_8021q_setup(काष्ठा dsa_8021q_context *ctx, bool enabled)
अणु
	वापस 0;
पूर्ण

पूर्णांक dsa_8021q_crosschip_bridge_join(काष्ठा dsa_8021q_context *ctx, पूर्णांक port,
				    काष्ठा dsa_8021q_context *other_ctx,
				    पूर्णांक other_port)
अणु
	वापस 0;
पूर्ण

पूर्णांक dsa_8021q_crosschip_bridge_leave(काष्ठा dsa_8021q_context *ctx, पूर्णांक port,
				     काष्ठा dsa_8021q_context *other_ctx,
				     पूर्णांक other_port)
अणु
	वापस 0;
पूर्ण

काष्ठा sk_buff *dsa_8021q_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *netdev,
			       u16 tpid, u16 tci)
अणु
	वापस शून्य;
पूर्ण

u16 dsa_8021q_tx_vid(काष्ठा dsa_चयन *ds, पूर्णांक port)
अणु
	वापस 0;
पूर्ण

u16 dsa_8021q_rx_vid(काष्ठा dsa_चयन *ds, पूर्णांक port)
अणु
	वापस 0;
पूर्ण

u16 dsa_8021q_rx_vid_subvlan(काष्ठा dsa_चयन *ds, पूर्णांक port, u16 subvlan)
अणु
	वापस 0;
पूर्ण

पूर्णांक dsa_8021q_rx_चयन_id(u16 vid)
अणु
	वापस 0;
पूर्ण

पूर्णांक dsa_8021q_rx_source_port(u16 vid)
अणु
	वापस 0;
पूर्ण

u16 dsa_8021q_rx_subvlan(u16 vid)
अणु
	वापस 0;
पूर्ण

bool vid_is_dsa_8021q_rxvlan(u16 vid)
अणु
	वापस false;
पूर्ण

bool vid_is_dsa_8021q_txvlan(u16 vid)
अणु
	वापस false;
पूर्ण

bool vid_is_dsa_8021q(u16 vid)
अणु
	वापस false;
पूर्ण

#पूर्ण_अगर /* IS_ENABLED(CONFIG_NET_DSA_TAG_8021Q) */

#पूर्ण_अगर /* _NET_DSA_8021Q_H */
