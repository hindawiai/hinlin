<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (c) 2014-2015 Hisilicon Limited.
 */

#अगर_अघोषित __HNS_ENET_H
#घोषणा __HNS_ENET_H

#समावेश <linux/netdevice.h>
#समावेश <linux/of_net.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/समयr.h>
#समावेश <linux/workqueue.h>

#समावेश "hnae.h"

#घोषणा HNS_DEBUG_OFFSET	6
#घोषणा HNS_SRV_OFFSET		2

क्रमागत hns_nic_state अणु
	NIC_STATE_TESTING = 0,
	NIC_STATE_RESETTING,
	NIC_STATE_REINITING,
	NIC_STATE_DOWN,
	NIC_STATE_DISABLED,
	NIC_STATE_REMOVING,
	NIC_STATE_SERVICE_INITED,
	NIC_STATE_SERVICE_SCHED,
	NIC_STATE2_RESET_REQUESTED,
	NIC_STATE_MAX
पूर्ण;

काष्ठा hns_nic_ring_data अणु
	काष्ठा hnae_ring *ring;
	काष्ठा napi_काष्ठा napi;
	cpumask_t mask; /* affinity mask */
	u32 queue_index;
	पूर्णांक (*poll_one)(काष्ठा hns_nic_ring_data *, पूर्णांक, व्योम *);
	व्योम (*ex_process)(काष्ठा hns_nic_ring_data *, काष्ठा sk_buff *);
	bool (*fini_process)(काष्ठा hns_nic_ring_data *);
पूर्ण;

/* compatible the dअगरference between two versions */
काष्ठा hns_nic_ops अणु
	व्योम (*fill_desc)(काष्ठा hnae_ring *ring, व्योम *priv,
			  पूर्णांक size, dma_addr_t dma, पूर्णांक frag_end,
			  पूर्णांक buf_num, क्रमागत hns_desc_type type, पूर्णांक mtu);
	पूर्णांक (*maybe_stop_tx)(काष्ठा sk_buff **out_skb,
			     पूर्णांक *bnum, काष्ठा hnae_ring *ring);
	व्योम (*get_rxd_bnum)(u32 bnum_flag, पूर्णांक *out_bnum);
पूर्ण;

काष्ठा hns_nic_priv अणु
	स्थिर काष्ठा fwnode_handle      *fwnode;
	u32 enet_ver;
	u32 port_id;
	पूर्णांक phy_mode;
	पूर्णांक phy_led_val;
	काष्ठा net_device *netdev;
	काष्ठा device *dev;
	काष्ठा hnae_handle *ae_handle;

	काष्ठा hns_nic_ops ops;

	/* the cb क्रम nic to manage the ring buffer, the first half of the
	 * array is क्रम tx_ring and vice versa क्रम the second half
	 */
	काष्ठा hns_nic_ring_data *ring_data;

	/* The most recently पढ़ो link state */
	पूर्णांक link;
	u64 tx_समयout_count;

	अचिन्हित दीर्घ state;

	काष्ठा समयr_list service_समयr;

	काष्ठा work_काष्ठा service_task;

	काष्ठा notअगरier_block notअगरier_block;
पूर्ण;

#घोषणा tx_ring_data(priv, idx) ((priv)->ring_data[idx])
#घोषणा rx_ring_data(priv, idx) \
	((priv)->ring_data[(priv)->ae_handle->q_num + (idx)])

व्योम hns_ethtool_set_ops(काष्ठा net_device *ndev);
व्योम hns_nic_net_reset(काष्ठा net_device *ndev);
व्योम hns_nic_net_reinit(काष्ठा net_device *netdev);
पूर्णांक hns_nic_init_phy(काष्ठा net_device *ndev, काष्ठा hnae_handle *h);
netdev_tx_t hns_nic_net_xmit_hw(काष्ठा net_device *ndev,
				काष्ठा sk_buff *skb,
				काष्ठा hns_nic_ring_data *ring_data);

#पूर्ण_अगर	/**__HNS_ENET_H */
