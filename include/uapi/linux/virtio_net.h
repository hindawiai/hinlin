<शैली गुरु>
#अगर_अघोषित _UAPI_LINUX_VIRTIO_NET_H
#घोषणा _UAPI_LINUX_VIRTIO_NET_H
/* This header is BSD licensed so anyone can use the definitions to implement
 * compatible drivers/servers.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    करोcumentation and/or other materials provided with the distribution.
 * 3. Neither the name of IBM nor the names of its contributors
 *    may be used to enकरोrse or promote products derived from this software
 *    without specअगरic prior written permission.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL IBM OR CONTRIBUTORS BE LIABLE
 * FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE. */
#समावेश <linux/types.h>
#समावेश <linux/virtio_ids.h>
#समावेश <linux/virtio_config.h>
#समावेश <linux/virtio_types.h>
#समावेश <linux/अगर_ether.h>

/* The feature biपंचांगap क्रम virtio net */
#घोषणा VIRTIO_NET_F_CSUM	0	/* Host handles pkts w/ partial csum */
#घोषणा VIRTIO_NET_F_GUEST_CSUM	1	/* Guest handles pkts w/ partial csum */
#घोषणा VIRTIO_NET_F_CTRL_GUEST_OFFLOADS 2 /* Dynamic offload configuration. */
#घोषणा VIRTIO_NET_F_MTU	3	/* Initial MTU advice */
#घोषणा VIRTIO_NET_F_MAC	5	/* Host has given MAC address. */
#घोषणा VIRTIO_NET_F_GUEST_TSO4	7	/* Guest can handle TSOv4 in. */
#घोषणा VIRTIO_NET_F_GUEST_TSO6	8	/* Guest can handle TSOv6 in. */
#घोषणा VIRTIO_NET_F_GUEST_ECN	9	/* Guest can handle TSO[6] w/ ECN in. */
#घोषणा VIRTIO_NET_F_GUEST_UFO	10	/* Guest can handle UFO in. */
#घोषणा VIRTIO_NET_F_HOST_TSO4	11	/* Host can handle TSOv4 in. */
#घोषणा VIRTIO_NET_F_HOST_TSO6	12	/* Host can handle TSOv6 in. */
#घोषणा VIRTIO_NET_F_HOST_ECN	13	/* Host can handle TSO[6] w/ ECN in. */
#घोषणा VIRTIO_NET_F_HOST_UFO	14	/* Host can handle UFO in. */
#घोषणा VIRTIO_NET_F_MRG_RXBUF	15	/* Host can merge receive buffers. */
#घोषणा VIRTIO_NET_F_STATUS	16	/* virtio_net_config.status available */
#घोषणा VIRTIO_NET_F_CTRL_VQ	17	/* Control channel available */
#घोषणा VIRTIO_NET_F_CTRL_RX	18	/* Control channel RX mode support */
#घोषणा VIRTIO_NET_F_CTRL_VLAN	19	/* Control channel VLAN filtering */
#घोषणा VIRTIO_NET_F_CTRL_RX_EXTRA 20	/* Extra RX mode control support */
#घोषणा VIRTIO_NET_F_GUEST_ANNOUNCE 21	/* Guest can announce device on the
					 * network */
#घोषणा VIRTIO_NET_F_MQ	22	/* Device supports Receive Flow
					 * Steering */
#घोषणा VIRTIO_NET_F_CTRL_MAC_ADDR 23	/* Set MAC address */

#घोषणा VIRTIO_NET_F_HASH_REPORT  57	/* Supports hash report */
#घोषणा VIRTIO_NET_F_RSS	  60	/* Supports RSS RX steering */
#घोषणा VIRTIO_NET_F_RSC_EXT	  61	/* extended coalescing info */
#घोषणा VIRTIO_NET_F_STANDBY	  62	/* Act as standby क्रम another device
					 * with the same MAC.
					 */
#घोषणा VIRTIO_NET_F_SPEED_DUPLEX 63	/* Device set linkspeed and duplex */

#अगर_अघोषित VIRTIO_NET_NO_LEGACY
#घोषणा VIRTIO_NET_F_GSO	6	/* Host handles pkts w/ any GSO type */
#पूर्ण_अगर /* VIRTIO_NET_NO_LEGACY */

#घोषणा VIRTIO_NET_S_LINK_UP	1	/* Link is up */
#घोषणा VIRTIO_NET_S_ANNOUNCE	2	/* Announcement is needed */

/* supported/enabled hash types */
#घोषणा VIRTIO_NET_RSS_HASH_TYPE_IPv4          (1 << 0)
#घोषणा VIRTIO_NET_RSS_HASH_TYPE_TCPv4         (1 << 1)
#घोषणा VIRTIO_NET_RSS_HASH_TYPE_UDPv4         (1 << 2)
#घोषणा VIRTIO_NET_RSS_HASH_TYPE_IPv6          (1 << 3)
#घोषणा VIRTIO_NET_RSS_HASH_TYPE_TCPv6         (1 << 4)
#घोषणा VIRTIO_NET_RSS_HASH_TYPE_UDPv6         (1 << 5)
#घोषणा VIRTIO_NET_RSS_HASH_TYPE_IP_EX         (1 << 6)
#घोषणा VIRTIO_NET_RSS_HASH_TYPE_TCP_EX        (1 << 7)
#घोषणा VIRTIO_NET_RSS_HASH_TYPE_UDP_EX        (1 << 8)

काष्ठा virtio_net_config अणु
	/* The config defining mac address (अगर VIRTIO_NET_F_MAC) */
	__u8 mac[ETH_ALEN];
	/* See VIRTIO_NET_F_STATUS and VIRTIO_NET_S_* above */
	__virtio16 status;
	/* Maximum number of each of transmit and receive queues;
	 * see VIRTIO_NET_F_MQ and VIRTIO_NET_CTRL_MQ.
	 * Legal values are between 1 and 0x8000
	 */
	__virtio16 max_virtqueue_pairs;
	/* Default maximum transmit unit advice */
	__virtio16 mtu;
	/*
	 * speed, in units of 1Mb. All values 0 to पूर्णांक_उच्च are legal.
	 * Any other value stands क्रम unknown.
	 */
	__le32 speed;
	/*
	 * 0x00 - half duplex
	 * 0x01 - full duplex
	 * Any other value stands क्रम unknown.
	 */
	__u8 duplex;
	/* maximum size of RSS key */
	__u8 rss_max_key_size;
	/* maximum number of indirection table entries */
	__le16 rss_max_indirection_table_length;
	/* biपंचांगask of supported VIRTIO_NET_RSS_HASH_ types */
	__le32 supported_hash_types;
पूर्ण __attribute__((packed));

/*
 * This header comes first in the scatter-gather list.  If you करोn't
 * specअगरy GSO or CSUM features, you can simply ignore the header.
 *
 * This is bitwise-equivalent to the legacy काष्ठा virtio_net_hdr_mrg_rxbuf,
 * only flattened.
 */
काष्ठा virtio_net_hdr_v1 अणु
#घोषणा VIRTIO_NET_HDR_F_NEEDS_CSUM	1	/* Use csum_start, csum_offset */
#घोषणा VIRTIO_NET_HDR_F_DATA_VALID	2	/* Csum is valid */
#घोषणा VIRTIO_NET_HDR_F_RSC_INFO	4	/* rsc info in csum_ fields */
	__u8 flags;
#घोषणा VIRTIO_NET_HDR_GSO_NONE		0	/* Not a GSO frame */
#घोषणा VIRTIO_NET_HDR_GSO_TCPV4	1	/* GSO frame, IPv4 TCP (TSO) */
#घोषणा VIRTIO_NET_HDR_GSO_UDP		3	/* GSO frame, IPv4 UDP (UFO) */
#घोषणा VIRTIO_NET_HDR_GSO_TCPV6	4	/* GSO frame, IPv6 TCP */
#घोषणा VIRTIO_NET_HDR_GSO_ECN		0x80	/* TCP has ECN set */
	__u8 gso_type;
	__virtio16 hdr_len;	/* Ethernet + IP + tcp/udp hdrs */
	__virtio16 gso_size;	/* Bytes to append to hdr_len per frame */
	जोड़ अणु
		काष्ठा अणु
			__virtio16 csum_start;
			__virtio16 csum_offset;
		पूर्ण;
		/* Checksum calculation */
		काष्ठा अणु
			/* Position to start checksumming from */
			__virtio16 start;
			/* Offset after that to place checksum */
			__virtio16 offset;
		पूर्ण csum;
		/* Receive Segment Coalescing */
		काष्ठा अणु
			/* Number of coalesced segments */
			__le16 segments;
			/* Number of duplicated acks */
			__le16 dup_acks;
		पूर्ण rsc;
	पूर्ण;
	__virtio16 num_buffers;	/* Number of merged rx buffers */
पूर्ण;

काष्ठा virtio_net_hdr_v1_hash अणु
	काष्ठा virtio_net_hdr_v1 hdr;
	__le32 hash_value;
#घोषणा VIRTIO_NET_HASH_REPORT_NONE            0
#घोषणा VIRTIO_NET_HASH_REPORT_IPv4            1
#घोषणा VIRTIO_NET_HASH_REPORT_TCPv4           2
#घोषणा VIRTIO_NET_HASH_REPORT_UDPv4           3
#घोषणा VIRTIO_NET_HASH_REPORT_IPv6            4
#घोषणा VIRTIO_NET_HASH_REPORT_TCPv6           5
#घोषणा VIRTIO_NET_HASH_REPORT_UDPv6           6
#घोषणा VIRTIO_NET_HASH_REPORT_IPv6_EX         7
#घोषणा VIRTIO_NET_HASH_REPORT_TCPv6_EX        8
#घोषणा VIRTIO_NET_HASH_REPORT_UDPv6_EX        9
	__le16 hash_report;
	__le16 padding;
पूर्ण;

#अगर_अघोषित VIRTIO_NET_NO_LEGACY
/* This header comes first in the scatter-gather list.
 * For legacy virtio, अगर VIRTIO_F_ANY_LAYOUT is not negotiated, it must
 * be the first element of the scatter-gather list.  If you करोn't
 * specअगरy GSO or CSUM features, you can simply ignore the header. */
काष्ठा virtio_net_hdr अणु
	/* See VIRTIO_NET_HDR_F_* */
	__u8 flags;
	/* See VIRTIO_NET_HDR_GSO_* */
	__u8 gso_type;
	__virtio16 hdr_len;		/* Ethernet + IP + tcp/udp hdrs */
	__virtio16 gso_size;		/* Bytes to append to hdr_len per frame */
	__virtio16 csum_start;	/* Position to start checksumming from */
	__virtio16 csum_offset;	/* Offset after that to place checksum */
पूर्ण;

/* This is the version of the header to use when the MRG_RXBUF
 * feature has been negotiated. */
काष्ठा virtio_net_hdr_mrg_rxbuf अणु
	काष्ठा virtio_net_hdr hdr;
	__virtio16 num_buffers;	/* Number of merged rx buffers */
पूर्ण;
#पूर्ण_अगर /* ...VIRTIO_NET_NO_LEGACY */

/*
 * Control virtqueue data काष्ठाures
 *
 * The control virtqueue expects a header in the first sg entry
 * and an ack/status response in the last entry.  Data क्रम the
 * command goes in between.
 */
काष्ठा virtio_net_ctrl_hdr अणु
	__u8 class;
	__u8 cmd;
पूर्ण __attribute__((packed));

प्रकार __u8 virtio_net_ctrl_ack;

#घोषणा VIRTIO_NET_OK     0
#घोषणा VIRTIO_NET_ERR    1

/*
 * Control the RX mode, ie. promisucous, allmulti, etc...
 * All commands require an "out" sg entry containing a 1 byte
 * state value, zero = disable, non-zero = enable.  Commands
 * 0 and 1 are supported with the VIRTIO_NET_F_CTRL_RX feature.
 * Commands 2-5 are added with VIRTIO_NET_F_CTRL_RX_EXTRA.
 */
#घोषणा VIRTIO_NET_CTRL_RX    0
 #घोषणा VIRTIO_NET_CTRL_RX_PROMISC      0
 #घोषणा VIRTIO_NET_CTRL_RX_ALLMULTI     1
 #घोषणा VIRTIO_NET_CTRL_RX_ALLUNI       2
 #घोषणा VIRTIO_NET_CTRL_RX_NOMULTI      3
 #घोषणा VIRTIO_NET_CTRL_RX_NOUNI        4
 #घोषणा VIRTIO_NET_CTRL_RX_NOBCAST      5

/*
 * Control the MAC
 *
 * The MAC filter table is managed by the hypervisor, the guest should
 * assume the size is infinite.  Filtering should be considered
 * non-perfect, ie. based on hypervisor resources, the guest may
 * received packets from sources not specअगरied in the filter list.
 *
 * In addition to the class/cmd header, the TABLE_SET command requires
 * two out scatterlists.  Each contains a 4 byte count of entries followed
 * by a concatenated byte stream of the ETH_ALEN MAC addresses.  The
 * first sg list contains unicast addresses, the second is क्रम multicast.
 * This functionality is present अगर the VIRTIO_NET_F_CTRL_RX feature
 * is available.
 *
 * The ADDR_SET command requests one out scatterlist, it contains a
 * 6 bytes MAC address. This functionality is present अगर the
 * VIRTIO_NET_F_CTRL_MAC_ADDR feature is available.
 */
काष्ठा virtio_net_ctrl_mac अणु
	__virtio32 entries;
	__u8 macs[][ETH_ALEN];
पूर्ण __attribute__((packed));

#घोषणा VIRTIO_NET_CTRL_MAC    1
 #घोषणा VIRTIO_NET_CTRL_MAC_TABLE_SET        0
 #घोषणा VIRTIO_NET_CTRL_MAC_ADDR_SET         1

/*
 * Control VLAN filtering
 *
 * The VLAN filter table is controlled via a simple ADD/DEL पूर्णांकerface.
 * VLAN IDs not added may be filterd by the hypervisor.  Del is the
 * opposite of add.  Both commands expect an out entry containing a 2
 * byte VLAN ID.  VLAN filterting is available with the
 * VIRTIO_NET_F_CTRL_VLAN feature bit.
 */
#घोषणा VIRTIO_NET_CTRL_VLAN       2
 #घोषणा VIRTIO_NET_CTRL_VLAN_ADD             0
 #घोषणा VIRTIO_NET_CTRL_VLAN_DEL             1

/*
 * Control link announce acknowledgement
 *
 * The command VIRTIO_NET_CTRL_ANNOUNCE_ACK is used to indicate that
 * driver has recevied the notअगरication; device would clear the
 * VIRTIO_NET_S_ANNOUNCE bit in the status field after it receives
 * this command.
 */
#घोषणा VIRTIO_NET_CTRL_ANNOUNCE       3
 #घोषणा VIRTIO_NET_CTRL_ANNOUNCE_ACK         0

/*
 * Control Receive Flow Steering
 */
#घोषणा VIRTIO_NET_CTRL_MQ   4
/*
 * The command VIRTIO_NET_CTRL_MQ_VQ_PAIRS_SET
 * enables Receive Flow Steering, specअगरying the number of the transmit and
 * receive queues that will be used. After the command is consumed and acked by
 * the device, the device will not steer new packets on receive virtqueues
 * other than specअगरied nor पढ़ो from transmit virtqueues other than specअगरied.
 * Accordingly, driver should not transmit new packets  on virtqueues other than
 * specअगरied.
 */
काष्ठा virtio_net_ctrl_mq अणु
	__virtio16 virtqueue_pairs;
पूर्ण;

 #घोषणा VIRTIO_NET_CTRL_MQ_VQ_PAIRS_SET        0
 #घोषणा VIRTIO_NET_CTRL_MQ_VQ_PAIRS_MIN        1
 #घोषणा VIRTIO_NET_CTRL_MQ_VQ_PAIRS_MAX        0x8000

/*
 * The command VIRTIO_NET_CTRL_MQ_RSS_CONFIG has the same effect as
 * VIRTIO_NET_CTRL_MQ_VQ_PAIRS_SET करोes and additionally configures
 * the receive steering to use a hash calculated क्रम incoming packet
 * to decide on receive virtqueue to place the packet. The command
 * also provides parameters to calculate a hash and receive virtqueue.
 */
काष्ठा virtio_net_rss_config अणु
	__le32 hash_types;
	__le16 indirection_table_mask;
	__le16 unclassअगरied_queue;
	__le16 indirection_table[1/* + indirection_table_mask */];
	__le16 max_tx_vq;
	__u8 hash_key_length;
	__u8 hash_key_data[/* hash_key_length */];
पूर्ण;

 #घोषणा VIRTIO_NET_CTRL_MQ_RSS_CONFIG          1

/*
 * The command VIRTIO_NET_CTRL_MQ_HASH_CONFIG requests the device
 * to include in the virtio header of the packet the value of the
 * calculated hash and the report type of hash. It also provides
 * parameters क्रम hash calculation. The command requires feature
 * VIRTIO_NET_F_HASH_REPORT to be negotiated to extend the
 * layout of virtio header as defined in virtio_net_hdr_v1_hash.
 */
काष्ठा virtio_net_hash_config अणु
	__le32 hash_types;
	/* क्रम compatibility with virtio_net_rss_config */
	__le16 reserved[4];
	__u8 hash_key_length;
	__u8 hash_key_data[/* hash_key_length */];
पूर्ण;

 #घोषणा VIRTIO_NET_CTRL_MQ_HASH_CONFIG         2

/*
 * Control network offloads
 *
 * Reconfigures the network offloads that Guest can handle.
 *
 * Available with the VIRTIO_NET_F_CTRL_GUEST_OFFLOADS feature bit.
 *
 * Command data क्रमmat matches the feature bit mask exactly.
 *
 * See VIRTIO_NET_F_GUEST_* क्रम the list of offloads
 * that can be enabled/disabled.
 */
#घोषणा VIRTIO_NET_CTRL_GUEST_OFFLOADS   5
#घोषणा VIRTIO_NET_CTRL_GUEST_OFFLOADS_SET        0

#पूर्ण_अगर /* _UAPI_LINUX_VIRTIO_NET_H */
