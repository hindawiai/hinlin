<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Copyright (c) 2013-2014, 2016-2018 The Linux Foundation. All rights reserved.
 *
 * RMNET Data configuration engine
 */

#समावेश <linux/skbuff.h>
#समावेश <net/gro_cells.h>

#अगर_अघोषित _RMNET_CONFIG_H_
#घोषणा _RMNET_CONFIG_H_

#घोषणा RMNET_MAX_LOGICAL_EP 255

काष्ठा rmnet_endpoपूर्णांक अणु
	u8 mux_id;
	काष्ठा net_device *egress_dev;
	काष्ठा hlist_node hlnode;
पूर्ण;

/* One instance of this काष्ठाure is instantiated क्रम each real_dev associated
 * with rmnet.
 */
काष्ठा rmnet_port अणु
	काष्ठा net_device *dev;
	u32 data_क्रमmat;
	u8 nr_rmnet_devs;
	u8 rmnet_mode;
	काष्ठा hlist_head muxed_ep[RMNET_MAX_LOGICAL_EP];
	काष्ठा net_device *bridge_ep;
	काष्ठा net_device *rmnet_dev;
पूर्ण;

बाह्य काष्ठा rtnl_link_ops rmnet_link_ops;

काष्ठा rmnet_vnd_stats अणु
	u64 rx_pkts;
	u64 rx_bytes;
	u64 tx_pkts;
	u64 tx_bytes;
	u32 tx_drops;
पूर्ण;

काष्ठा rmnet_pcpu_stats अणु
	काष्ठा rmnet_vnd_stats stats;
	काष्ठा u64_stats_sync syncp;
पूर्ण;

काष्ठा rmnet_priv_stats अणु
	u64 csum_ok;
	u64 csum_valid_unset;
	u64 csum_validation_failed;
	u64 csum_err_bad_buffer;
	u64 csum_err_invalid_ip_version;
	u64 csum_err_invalid_transport;
	u64 csum_fragmented_pkt;
	u64 csum_skipped;
	u64 csum_sw;
पूर्ण;

काष्ठा rmnet_priv अणु
	u8 mux_id;
	काष्ठा net_device *real_dev;
	काष्ठा rmnet_pcpu_stats __percpu *pcpu_stats;
	काष्ठा gro_cells gro_cells;
	काष्ठा rmnet_priv_stats stats;
पूर्ण;

काष्ठा rmnet_port *rmnet_get_port_rcu(काष्ठा net_device *real_dev);
काष्ठा rmnet_endpoपूर्णांक *rmnet_get_endpoपूर्णांक(काष्ठा rmnet_port *port, u8 mux_id);
पूर्णांक rmnet_add_bridge(काष्ठा net_device *rmnet_dev,
		     काष्ठा net_device *slave_dev,
		     काष्ठा netlink_ext_ack *extack);
पूर्णांक rmnet_del_bridge(काष्ठा net_device *rmnet_dev,
		     काष्ठा net_device *slave_dev);
काष्ठा rmnet_port*
rmnet_get_port_rtnl(स्थिर काष्ठा net_device *real_dev);
#पूर्ण_अगर /* _RMNET_CONFIG_H_ */
