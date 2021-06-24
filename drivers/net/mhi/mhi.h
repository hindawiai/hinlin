<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* MHI Network driver - Network over MHI bus
 *
 * Copyright (C) 2021 Linaro Ltd <loic.poulain@linaro.org>
 */

काष्ठा mhi_net_stats अणु
	u64_stats_t rx_packets;
	u64_stats_t rx_bytes;
	u64_stats_t rx_errors;
	u64_stats_t rx_dropped;
	u64_stats_t rx_length_errors;
	u64_stats_t tx_packets;
	u64_stats_t tx_bytes;
	u64_stats_t tx_errors;
	u64_stats_t tx_dropped;
	काष्ठा u64_stats_sync tx_syncp;
	काष्ठा u64_stats_sync rx_syncp;
पूर्ण;

काष्ठा mhi_net_dev अणु
	काष्ठा mhi_device *mdev;
	काष्ठा net_device *ndev;
	काष्ठा sk_buff *skbagg_head;
	काष्ठा sk_buff *skbagg_tail;
	स्थिर काष्ठा mhi_net_proto *proto;
	व्योम *proto_data;
	काष्ठा delayed_work rx_refill;
	काष्ठा mhi_net_stats stats;
	u32 rx_queue_sz;
	पूर्णांक msg_enable;
	अचिन्हित पूर्णांक mru;
पूर्ण;

काष्ठा mhi_net_proto अणु
	पूर्णांक (*init)(काष्ठा mhi_net_dev *mhi_netdev);
	काष्ठा sk_buff * (*tx_fixup)(काष्ठा mhi_net_dev *mhi_netdev, काष्ठा sk_buff *skb);
	व्योम (*rx)(काष्ठा mhi_net_dev *mhi_netdev, काष्ठा sk_buff *skb);
पूर्ण;

बाह्य स्थिर काष्ठा mhi_net_proto proto_mbim;
