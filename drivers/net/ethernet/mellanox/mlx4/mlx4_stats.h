<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _MLX4_STATS_
#घोषणा _MLX4_STATS_

#घोषणा NUM_PRIORITIES	9
#घोषणा NUM_PRIORITY_STATS 2

काष्ठा mlx4_en_pkt_stats अणु
	अचिन्हित दीर्घ rx_multicast_packets;
	अचिन्हित दीर्घ rx_broadcast_packets;
	अचिन्हित दीर्घ rx_jabbers;
	अचिन्हित दीर्घ rx_in_range_length_error;
	अचिन्हित दीर्घ rx_out_range_length_error;
	अचिन्हित दीर्घ tx_multicast_packets;
	अचिन्हित दीर्घ tx_broadcast_packets;
	अचिन्हित दीर्घ rx_prio[NUM_PRIORITIES][NUM_PRIORITY_STATS];
	अचिन्हित दीर्घ tx_prio[NUM_PRIORITIES][NUM_PRIORITY_STATS];
#घोषणा NUM_PKT_STATS		43
पूर्ण;

काष्ठा mlx4_en_counter_stats अणु
	अचिन्हित दीर्घ rx_packets;
	अचिन्हित दीर्घ rx_bytes;
	अचिन्हित दीर्घ tx_packets;
	अचिन्हित दीर्घ tx_bytes;
#घोषणा NUM_PF_STATS      4
पूर्ण;

काष्ठा mlx4_en_port_stats अणु
	अचिन्हित दीर्घ tso_packets;
	अचिन्हित दीर्घ xmit_more;
	अचिन्हित दीर्घ queue_stopped;
	अचिन्हित दीर्घ wake_queue;
	अचिन्हित दीर्घ tx_समयout;
	अचिन्हित दीर्घ rx_alloc_pages;
	अचिन्हित दीर्घ rx_chksum_good;
	अचिन्हित दीर्घ rx_chksum_none;
	अचिन्हित दीर्घ rx_chksum_complete;
	अचिन्हित दीर्घ tx_chksum_offload;
#घोषणा NUM_PORT_STATS		10
पूर्ण;

काष्ठा mlx4_en_xdp_stats अणु
	अचिन्हित दीर्घ rx_xdp_drop;
	अचिन्हित दीर्घ rx_xdp_tx;
	अचिन्हित दीर्घ rx_xdp_tx_full;
#घोषणा NUM_XDP_STATS		3
पूर्ण;

काष्ठा mlx4_en_phy_stats अणु
	अचिन्हित दीर्घ rx_packets_phy;
	अचिन्हित दीर्घ rx_bytes_phy;
	अचिन्हित दीर्घ tx_packets_phy;
	अचिन्हित दीर्घ tx_bytes_phy;
#घोषणा NUM_PHY_STATS		4
पूर्ण;

#घोषणा NUM_MAIN_STATS	21

#घोषणा MLX4_NUM_PRIORITIES	8

काष्ठा mlx4_en_flow_stats_rx अणु
	u64 rx_छोड़ो;
	u64 rx_छोड़ो_duration;
	u64 rx_छोड़ो_transition;
#घोषणा NUM_FLOW_STATS_RX	3
#घोषणा NUM_FLOW_PRIORITY_STATS_RX	(NUM_FLOW_STATS_RX * \
					 MLX4_NUM_PRIORITIES)
पूर्ण;

#घोषणा FLOW_PRIORITY_STATS_IDX_RX_FRAMES	(NUM_MAIN_STATS +	\
						 NUM_PORT_STATS +	\
						 NUM_PF_STATS +		\
						 NUM_FLOW_PRIORITY_STATS_RX)

काष्ठा mlx4_en_flow_stats_tx अणु
	u64 tx_छोड़ो;
	u64 tx_छोड़ो_duration;
	u64 tx_छोड़ो_transition;
#घोषणा NUM_FLOW_STATS_TX	3
#घोषणा NUM_FLOW_PRIORITY_STATS_TX	(NUM_FLOW_STATS_TX * \
					 MLX4_NUM_PRIORITIES)
पूर्ण;

#घोषणा FLOW_PRIORITY_STATS_IDX_TX_FRAMES	(NUM_MAIN_STATS +	\
						 NUM_PORT_STATS +	\
						 NUM_PF_STATS +		\
						 NUM_FLOW_PRIORITY_STATS_RX + \
						 NUM_FLOW_STATS_RX +	\
						 NUM_FLOW_PRIORITY_STATS_TX)

#घोषणा NUM_FLOW_STATS (NUM_FLOW_STATS_RX + NUM_FLOW_STATS_TX + \
			NUM_FLOW_PRIORITY_STATS_TX + \
			NUM_FLOW_PRIORITY_STATS_RX)

काष्ठा mlx4_en_stat_out_flow_control_mbox अणु
	/* Total number of PAUSE frames received from the far-end port */
	__be64 rx_छोड़ो;
	/* Total number of microseconds that far-end port requested to छोड़ो
	* transmission of packets
	*/
	__be64 rx_छोड़ो_duration;
	/* Number of received transmission from XOFF state to XON state */
	__be64 rx_छोड़ो_transition;
	/* Total number of PAUSE frames sent from the far-end port */
	__be64 tx_छोड़ो;
	/* Total समय in microseconds that transmission of packets has been
	* छोड़ोd
	*/
	__be64 tx_छोड़ो_duration;
	/* Number of transmitter transitions from XOFF state to XON state */
	__be64 tx_छोड़ो_transition;
	/* Reserverd */
	__be64 reserved[2];
पूर्ण;

क्रमागत अणु
	MLX4_DUMP_ETH_STATS_FLOW_CONTROL = 1 << 12
पूर्ण;

#घोषणा NUM_ALL_STATS	(NUM_MAIN_STATS + NUM_PORT_STATS + NUM_PKT_STATS + \
			 NUM_FLOW_STATS + NUM_PF_STATS + \
			 NUM_XDP_STATS + NUM_PHY_STATS)

#घोषणा MLX4_FIND_NETDEV_STAT(n) (दुरत्व(काष्ठा net_device_stats, n) / \
				  माप(((काष्ठा net_device_stats *)0)->n))

#पूर्ण_अगर
