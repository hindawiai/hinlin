<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 * Copyright(c) 2020 Intel Corporation.
 */

#अगर_अघोषित XDPXCEIVER_H_
#घोषणा XDPXCEIVER_H_

#अगर_अघोषित SOL_XDP
#घोषणा SOL_XDP 283
#पूर्ण_अगर

#अगर_अघोषित AF_XDP
#घोषणा AF_XDP 44
#पूर्ण_अगर

#अगर_अघोषित PF_XDP
#घोषणा PF_XDP AF_XDP
#पूर्ण_अगर

#घोषणा MAX_INTERFACES 2
#घोषणा MAX_INTERFACE_NAME_CHARS 7
#घोषणा MAX_INTERFACES_NAMESPACE_CHARS 10
#घोषणा MAX_SOCKS 1
#घोषणा MAX_TEARDOWN_ITER 10
#घोषणा MAX_BIDI_ITER 2
#घोषणा MAX_BPF_ITER 2
#घोषणा PKT_HDR_SIZE (माप(काष्ठा ethhdr) + माप(काष्ठा iphdr) + \
			माप(काष्ठा udphdr))
#घोषणा MIN_PKT_SIZE 64
#घोषणा ETH_FCS_SIZE 4
#घोषणा PKT_SIZE (MIN_PKT_SIZE - ETH_FCS_SIZE)
#घोषणा IP_PKT_SIZE (PKT_SIZE - माप(काष्ठा ethhdr))
#घोषणा IP_PKT_VER 0x4
#घोषणा IP_PKT_TOS 0x9
#घोषणा UDP_PKT_SIZE (IP_PKT_SIZE - माप(काष्ठा iphdr))
#घोषणा UDP_PKT_DATA_SIZE (UDP_PKT_SIZE - माप(काष्ठा udphdr))
#घोषणा EOT (-1)
#घोषणा USLEEP_MAX 200000
#घोषणा SOCK_RECONF_CTR 10
#घोषणा BATCH_SIZE 64
#घोषणा POLL_TMOUT 1000
#घोषणा DEFAULT_PKT_CNT 10000
#घोषणा RX_FULL_RXQSIZE 32

#घोषणा prपूर्णांक_verbose(x...) करो अणु अगर (opt_verbose) ksft_prपूर्णांक_msg(x); पूर्ण जबतक (0)

प्रकार __u32 u32;
प्रकार __u16 u16;
प्रकार __u8 u8;

क्रमागत TEST_MODES अणु
	TEST_MODE_UNCONFIGURED = -1,
	TEST_MODE_SKB,
	TEST_MODE_DRV,
	TEST_MODE_MAX
पूर्ण;

क्रमागत TEST_TYPES अणु
	TEST_TYPE_NOPOLL,
	TEST_TYPE_POLL,
	TEST_TYPE_TEARDOWN,
	TEST_TYPE_BIDI,
	TEST_TYPE_STATS,
	TEST_TYPE_BPF_RES,
	TEST_TYPE_MAX
पूर्ण;

क्रमागत STAT_TEST_TYPES अणु
	STAT_TEST_RX_DROPPED,
	STAT_TEST_TX_INVALID,
	STAT_TEST_RX_FULL,
	STAT_TEST_RX_FILL_EMPTY,
	STAT_TEST_TYPE_MAX
पूर्ण;

अटल पूर्णांक configured_mode = TEST_MODE_UNCONFIGURED;
अटल u8 debug_pkt_dump;
अटल u32 num_frames;
अटल bool second_step;
अटल पूर्णांक test_type;

अटल पूर्णांक opt_pkt_count;
अटल u8 opt_verbose;

अटल u32 xdp_flags = XDP_FLAGS_UPDATE_IF_NOEXIST;
अटल u32 xdp_bind_flags = XDP_USE_NEED_WAKEUP | XDP_COPY;
अटल u8 pkt_data[XSK_UMEM__DEFAULT_FRAME_SIZE];
अटल u32 pkt_counter;
अटल दीर्घ prev_pkt = -1;
अटल पूर्णांक sigvar;
अटल पूर्णांक stat_test_type;
अटल u32 rxqsize;
अटल u32 frame_headroom;

काष्ठा xsk_umem_info अणु
	काष्ठा xsk_ring_prod fq;
	काष्ठा xsk_ring_cons cq;
	काष्ठा xsk_umem *umem;
	व्योम *buffer;
पूर्ण;

काष्ठा xsk_socket_info अणु
	काष्ठा xsk_ring_cons rx;
	काष्ठा xsk_ring_prod tx;
	काष्ठा xsk_umem_info *umem;
	काष्ठा xsk_socket *xsk;
	अचिन्हित दीर्घ rx_npkts;
	अचिन्हित दीर्घ tx_npkts;
	अचिन्हित दीर्घ prev_rx_npkts;
	अचिन्हित दीर्घ prev_tx_npkts;
	u32 outstanding_tx;
पूर्ण;

काष्ठा flow_vector अणु
	क्रमागत fvector अणु
		tx,
		rx,
	पूर्ण vector;
पूर्ण;

काष्ठा generic_data अणु
	u32 seqnum;
पूर्ण;

काष्ठा अगरobject अणु
	अक्षर अगरname[MAX_INTERFACE_NAME_CHARS];
	अक्षर nsname[MAX_INTERFACES_NAMESPACE_CHARS];
	काष्ठा xsk_socket_info *xsk;
	काष्ठा xsk_socket_info **xsk_arr;
	काष्ठा xsk_umem_info **umem_arr;
	काष्ठा xsk_umem_info *umem;
	व्योम *(*func_ptr)(व्योम *arg);
	काष्ठा flow_vector fv;
	पूर्णांक ns_fd;
	पूर्णांक अगरdict_index;
	u32 dst_ip;
	u32 src_ip;
	u16 src_port;
	u16 dst_port;
	u8 dst_mac[ETH_ALEN];
	u8 src_mac[ETH_ALEN];
पूर्ण;

अटल काष्ठा अगरobject *अगरdict[MAX_INTERFACES];
अटल काष्ठा अगरobject *अगरdict_rx;
अटल काष्ठा अगरobject *अगरdict_tx;

/*thपढ़ोs*/
pthपढ़ो_barrier_t barr;
pthपढ़ो_t t0, t1;

TAILQ_HEAD(head_s, pkt) head = TAILQ_HEAD_INITIALIZER(head);
काष्ठा head_s *head_p;
काष्ठा pkt अणु
	अक्षर *pkt_frame;

	TAILQ_ENTRY(pkt) pkt_nodes;
पूर्ण *pkt_node_rx, *pkt_node_rx_q;

काष्ठा pkt_frame अणु
	अक्षर *payload;
पूर्ण *pkt_obj;

काष्ठा pkt_frame **pkt_buf;

#पूर्ण_अगर				/* XDPXCEIVER_H */
