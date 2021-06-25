<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause) */
/* Copyright (C) 2017-2018 Netronome Systems, Inc. */

#अगर_अघोषित NFP_NET_REPR_H
#घोषणा NFP_NET_REPR_H

काष्ठा metadata_dst;
काष्ठा nfp_app;
काष्ठा nfp_net;
काष्ठा nfp_port;

#समावेश <net/dst_metadata.h>

/**
 * काष्ठा nfp_reprs - container क्रम representor netdevs
 * @num_reprs:	Number of elements in reprs array
 * @reprs:	Array of representor netdevs
 */
काष्ठा nfp_reprs अणु
	अचिन्हित पूर्णांक num_reprs;
	काष्ठा net_device __rcu *reprs[];
पूर्ण;

/**
 * काष्ठा nfp_repr_pcpu_stats
 * @rx_packets:	Received packets
 * @rx_bytes:	Received bytes
 * @tx_packets:	Transmitted packets
 * @tx_bytes:	Transmitted dropped
 * @tx_drops:	Packets dropped on transmit
 * @syncp:	Reference count
 */
काष्ठा nfp_repr_pcpu_stats अणु
	u64 rx_packets;
	u64 rx_bytes;
	u64 tx_packets;
	u64 tx_bytes;
	u64 tx_drops;
	काष्ठा u64_stats_sync syncp;
पूर्ण;

/**
 * काष्ठा nfp_repr - priv data क्रम representor netdevs
 * @netdev:	Back poपूर्णांकer to netdev
 * @dst:	Destination क्रम packet TX
 * @port:	Port of representor
 * @app:	APP handle
 * @stats:	Statistic of packets hitting CPU
 * @app_priv:	Poपूर्णांकer क्रम APP data
 */
काष्ठा nfp_repr अणु
	काष्ठा net_device *netdev;
	काष्ठा metadata_dst *dst;
	काष्ठा nfp_port *port;
	काष्ठा nfp_app *app;
	काष्ठा nfp_repr_pcpu_stats __percpu *stats;
	व्योम *app_priv;
पूर्ण;

/**
 * क्रमागत nfp_repr_type - type of representor
 * @NFP_REPR_TYPE_PHYS_PORT:	बाह्यal NIC port
 * @NFP_REPR_TYPE_PF:		physical function
 * @NFP_REPR_TYPE_VF:		भव function
 * @__NFP_REPR_TYPE_MAX:	number of representor types
 */
क्रमागत nfp_repr_type अणु
	NFP_REPR_TYPE_PHYS_PORT,
	NFP_REPR_TYPE_PF,
	NFP_REPR_TYPE_VF,

	__NFP_REPR_TYPE_MAX,
पूर्ण;
#घोषणा NFP_REPR_TYPE_MAX (__NFP_REPR_TYPE_MAX - 1)

बाह्य स्थिर काष्ठा net_device_ops nfp_repr_netdev_ops;

अटल अंतरभूत bool nfp_netdev_is_nfp_repr(काष्ठा net_device *netdev)
अणु
	वापस netdev->netdev_ops == &nfp_repr_netdev_ops;
पूर्ण

अटल अंतरभूत पूर्णांक nfp_repr_get_port_id(काष्ठा net_device *netdev)
अणु
	काष्ठा nfp_repr *priv = netdev_priv(netdev);

	वापस priv->dst->u.port_info.port_id;
पूर्ण

काष्ठा net_device *
nfp_repr_get_locked(काष्ठा nfp_app *app, काष्ठा nfp_reprs *set,
		    अचिन्हित पूर्णांक id);

व्योम nfp_repr_inc_rx_stats(काष्ठा net_device *netdev, अचिन्हित पूर्णांक len);
व्योम
nfp_repr_transfer_features(काष्ठा net_device *netdev, काष्ठा net_device *lower);
पूर्णांक nfp_repr_init(काष्ठा nfp_app *app, काष्ठा net_device *netdev,
		  u32 cmsg_port_id, काष्ठा nfp_port *port,
		  काष्ठा net_device *pf_netdev);
व्योम nfp_repr_मुक्त(काष्ठा net_device *netdev);
काष्ठा net_device *
nfp_repr_alloc_mqs(काष्ठा nfp_app *app, अचिन्हित पूर्णांक txqs, अचिन्हित पूर्णांक rxqs);
व्योम nfp_repr_clean_and_मुक्त(काष्ठा nfp_repr *repr);
व्योम nfp_reprs_clean_and_मुक्त(काष्ठा nfp_app *app, काष्ठा nfp_reprs *reprs);
व्योम nfp_reprs_clean_and_मुक्त_by_type(काष्ठा nfp_app *app,
				      क्रमागत nfp_repr_type type);
काष्ठा nfp_reprs *nfp_reprs_alloc(अचिन्हित पूर्णांक num_reprs);
पूर्णांक nfp_reprs_resync_phys_ports(काष्ठा nfp_app *app);

अटल अंतरभूत काष्ठा net_device *nfp_repr_alloc(काष्ठा nfp_app *app)
अणु
	वापस nfp_repr_alloc_mqs(app, 1, 1);
पूर्ण
#पूर्ण_अगर /* NFP_NET_REPR_H */
