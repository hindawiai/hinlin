<शैली गुरु>
/*
 * AMD 10Gb Ethernet driver
 *
 * This file is available to you under your choice of the following two
 * licenses:
 *
 * License 1: GPLv2
 *
 * Copyright (c) 2014-2016 Advanced Micro Devices, Inc.
 *
 * This file is मुक्त software; you may copy, redistribute and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or (at
 * your option) any later version.
 *
 * This file is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * This file incorporates work covered by the following copyright and
 * permission notice:
 *     The Synopsys DWC ETHER XGMAC Software Driver and करोcumentation
 *     (hereinafter "Software") is an unsupported proprietary work of Synopsys,
 *     Inc. unless otherwise expressly agreed to in writing between Synopsys
 *     and you.
 *
 *     The Software IS NOT an item of Licensed Software or Licensed Product
 *     under any End User Software License Agreement or Agreement क्रम Licensed
 *     Product with Synopsys or any supplement thereto.  Permission is hereby
 *     granted, मुक्त of अक्षरge, to any person obtaining a copy of this software
 *     annotated with this license and the Software, to deal in the Software
 *     without restriction, including without limitation the rights to use,
 *     copy, modअगरy, merge, publish, distribute, sublicense, and/or sell copies
 *     of the Software, and to permit persons to whom the Software is furnished
 *     to करो so, subject to the following conditions:
 *
 *     The above copyright notice and this permission notice shall be included
 *     in all copies or substantial portions of the Software.
 *
 *     THIS SOFTWARE IS BEING DISTRIBUTED BY SYNOPSYS SOLELY ON AN "AS IS"
 *     BASIS AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 *     TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 *     PARTICULAR PURPOSE ARE HEREBY DISCLAIMED. IN NO EVENT SHALL SYNOPSYS
 *     BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *     CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *     SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *     INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *     CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *     ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 *     THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 * License 2: Modअगरied BSD
 *
 * Copyright (c) 2014-2016 Advanced Micro Devices, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary क्रमm must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       करोcumentation and/or other materials provided with the distribution.
 *     * Neither the name of Advanced Micro Devices, Inc. nor the
 *       names of its contributors may be used to enकरोrse or promote products
 *       derived from this software without specअगरic prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
 * सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * This file incorporates work covered by the following copyright and
 * permission notice:
 *     The Synopsys DWC ETHER XGMAC Software Driver and करोcumentation
 *     (hereinafter "Software") is an unsupported proprietary work of Synopsys,
 *     Inc. unless otherwise expressly agreed to in writing between Synopsys
 *     and you.
 *
 *     The Software IS NOT an item of Licensed Software or Licensed Product
 *     under any End User Software License Agreement or Agreement क्रम Licensed
 *     Product with Synopsys or any supplement thereto.  Permission is hereby
 *     granted, मुक्त of अक्षरge, to any person obtaining a copy of this software
 *     annotated with this license and the Software, to deal in the Software
 *     without restriction, including without limitation the rights to use,
 *     copy, modअगरy, merge, publish, distribute, sublicense, and/or sell copies
 *     of the Software, and to permit persons to whom the Software is furnished
 *     to करो so, subject to the following conditions:
 *
 *     The above copyright notice and this permission notice shall be included
 *     in all copies or substantial portions of the Software.
 *
 *     THIS SOFTWARE IS BEING DISTRIBUTED BY SYNOPSYS SOLELY ON AN "AS IS"
 *     BASIS AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 *     TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 *     PARTICULAR PURPOSE ARE HEREBY DISCLAIMED. IN NO EVENT SHALL SYNOPSYS
 *     BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *     CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *     SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *     INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *     CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *     ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 *     THE POSSIBILITY OF SUCH DAMAGE.
 */

#अगर_अघोषित __XGBE_H__
#घोषणा __XGBE_H__

#समावेश <linux/dma-mapping.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/phy.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/bitops.h>
#समावेश <linux/ptp_घड़ी_kernel.h>
#समावेश <linux/समयcounter.h>
#समावेश <linux/net_tstamp.h>
#समावेश <net/dcbnl.h>
#समावेश <linux/completion.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/dcache.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/list.h>

#घोषणा XGBE_DRV_NAME		"amd-xgbe"
#घोषणा XGBE_DRV_DESC		"AMD 10 Gigabit Ethernet Driver"

/* Descriptor related defines */
#घोषणा XGBE_TX_DESC_CNT	512
#घोषणा XGBE_TX_DESC_MIN_FREE	(XGBE_TX_DESC_CNT >> 3)
#घोषणा XGBE_TX_DESC_MAX_PROC	(XGBE_TX_DESC_CNT >> 1)
#घोषणा XGBE_RX_DESC_CNT	512

#घोषणा XGBE_TX_DESC_CNT_MIN	64
#घोषणा XGBE_TX_DESC_CNT_MAX	4096
#घोषणा XGBE_RX_DESC_CNT_MIN	64
#घोषणा XGBE_RX_DESC_CNT_MAX	4096

#घोषणा XGBE_TX_MAX_BUF_SIZE	(0x3fff & ~(64 - 1))

/* Descriptors required क्रम maximum contiguous TSO/GSO packet */
#घोषणा XGBE_TX_MAX_SPLIT	((GSO_MAX_SIZE / XGBE_TX_MAX_BUF_SIZE) + 1)

/* Maximum possible descriptors needed क्रम an SKB:
 * - Maximum number of SKB frags
 * - Maximum descriptors क्रम contiguous TSO/GSO packet
 * - Possible context descriptor
 * - Possible TSO header descriptor
 */
#घोषणा XGBE_TX_MAX_DESCS	(MAX_SKB_FRAGS + XGBE_TX_MAX_SPLIT + 2)

#घोषणा XGBE_RX_MIN_BUF_SIZE	(ETH_FRAME_LEN + ETH_FCS_LEN + VLAN_HLEN)
#घोषणा XGBE_RX_BUF_ALIGN	64
#घोषणा XGBE_SKB_ALLOC_SIZE	256
#घोषणा XGBE_SPH_HDSMS_SIZE	2	/* Keep in sync with SKB_ALLOC_SIZE */

#घोषणा XGBE_MAX_DMA_CHANNELS	16
#घोषणा XGBE_MAX_QUEUES		16
#घोषणा XGBE_PRIORITY_QUEUES	8
#घोषणा XGBE_DMA_STOP_TIMEOUT	1

/* DMA cache settings - Outer sharable, ग_लिखो-back, ग_लिखो-allocate */
#घोषणा XGBE_DMA_OS_ARCR	0x002b2b2b
#घोषणा XGBE_DMA_OS_AWCR	0x2f2f2f2f

/* DMA cache settings - System, no caches used */
#घोषणा XGBE_DMA_SYS_ARCR	0x00303030
#घोषणा XGBE_DMA_SYS_AWCR	0x30303030

/* DMA cache settings - PCI device */
#घोषणा XGBE_DMA_PCI_ARCR	0x000f0f0f
#घोषणा XGBE_DMA_PCI_AWCR	0x0f0f0f0f
#घोषणा XGBE_DMA_PCI_AWARCR	0x00000f0f

/* DMA channel पूर्णांकerrupt modes */
#घोषणा XGBE_IRQ_MODE_EDGE	0
#घोषणा XGBE_IRQ_MODE_LEVEL	1

#घोषणा XGMAC_MIN_PACKET	60
#घोषणा XGMAC_STD_PACKET_MTU	1500
#घोषणा XGMAC_MAX_STD_PACKET	1518
#घोषणा XGMAC_JUMBO_PACKET_MTU	9000
#घोषणा XGMAC_MAX_JUMBO_PACKET	9018
#घोषणा XGMAC_ETH_PREAMBLE	(12 + 8)	/* Inter-frame gap + preamble */

#घोषणा XGMAC_PFC_DATA_LEN	46
#घोषणा XGMAC_PFC_DELAYS	14000

#घोषणा XGMAC_PRIO_QUEUES(_cnt)					\
	min_t(अचिन्हित पूर्णांक, IEEE_8021QAZ_MAX_TCS, (_cnt))

/* Common property names */
#घोषणा XGBE_MAC_ADDR_PROPERTY	"mac-address"
#घोषणा XGBE_PHY_MODE_PROPERTY	"phy-mode"
#घोषणा XGBE_DMA_IRQS_PROPERTY	"amd,per-channel-interrupt"
#घोषणा XGBE_SPEEDSET_PROPERTY	"amd,speed-set"

/* Device-tree घड़ी names */
#घोषणा XGBE_DMA_CLOCK		"dma_clk"
#घोषणा XGBE_PTP_CLOCK		"ptp_clk"

/* ACPI property names */
#घोषणा XGBE_ACPI_DMA_FREQ	"amd,dma-freq"
#घोषणा XGBE_ACPI_PTP_FREQ	"amd,ptp-freq"

/* PCI BAR mapping */
#घोषणा XGBE_XGMAC_BAR		0
#घोषणा XGBE_XPCS_BAR		1
#घोषणा XGBE_MAC_PROP_OFFSET	0x1d000
#घोषणा XGBE_I2C_CTRL_OFFSET	0x1e000

/* PCI MSI/MSIx support */
#घोषणा XGBE_MSI_BASE_COUNT	4
#घोषणा XGBE_MSI_MIN_COUNT	(XGBE_MSI_BASE_COUNT + 1)

/* PCI घड़ी frequencies */
#घोषणा XGBE_V2_DMA_CLOCK_FREQ	500000000	/* 500 MHz */
#घोषणा XGBE_V2_PTP_CLOCK_FREQ	125000000	/* 125 MHz */

/* Timestamp support - values based on 50MHz PTP घड़ी
 *   50MHz => 20 nsec
 */
#घोषणा XGBE_TSTAMP_SSINC	20
#घोषणा XGBE_TSTAMP_SNSINC	0

/* Driver PMT macros */
#घोषणा XGMAC_DRIVER_CONTEXT	1
#घोषणा XGMAC_IOCTL_CONTEXT	2

#घोषणा XGMAC_FIFO_MIN_ALLOC	2048
#घोषणा XGMAC_FIFO_UNIT		256
#घोषणा XGMAC_FIFO_ALIGN(_x)				\
	(((_x) + XGMAC_FIFO_UNIT - 1) & ~(XGMAC_FIFO_UNIT - 1))
#घोषणा XGMAC_FIFO_FC_OFF	2048
#घोषणा XGMAC_FIFO_FC_MIN	4096

#घोषणा XGBE_TC_MIN_QUANTUM	10

/* Helper macro क्रम descriptor handling
 *  Always use XGBE_GET_DESC_DATA to access the descriptor data
 *  since the index is मुक्त-running and needs to be and-ed
 *  with the descriptor count value of the ring to index to
 *  the proper descriptor data.
 */
#घोषणा XGBE_GET_DESC_DATA(_ring, _idx)				\
	((_ring)->rdata +					\
	 ((_idx) & ((_ring)->rdesc_count - 1)))

/* Default coalescing parameters */
#घोषणा XGMAC_INIT_DMA_TX_USECS		1000
#घोषणा XGMAC_INIT_DMA_TX_FRAMES	25

#घोषणा XGMAC_MAX_DMA_RIWT		0xff
#घोषणा XGMAC_INIT_DMA_RX_USECS		30
#घोषणा XGMAC_INIT_DMA_RX_FRAMES	25

/* Flow control queue count */
#घोषणा XGMAC_MAX_FLOW_CONTROL_QUEUES	8

/* Flow control threshold units */
#घोषणा XGMAC_FLOW_CONTROL_UNIT		512
#घोषणा XGMAC_FLOW_CONTROL_ALIGN(_x)				\
	(((_x) + XGMAC_FLOW_CONTROL_UNIT - 1) & ~(XGMAC_FLOW_CONTROL_UNIT - 1))
#घोषणा XGMAC_FLOW_CONTROL_VALUE(_x)				\
	(((_x) < 1024) ? 0 : ((_x) / XGMAC_FLOW_CONTROL_UNIT) - 2)
#घोषणा XGMAC_FLOW_CONTROL_MAX		33280

/* Maximum MAC address hash table size (256 bits = 8 bytes) */
#घोषणा XGBE_MAC_HASH_TABLE_SIZE	8

/* Receive Side Scaling */
#घोषणा XGBE_RSS_HASH_KEY_SIZE		40
#घोषणा XGBE_RSS_MAX_TABLE_SIZE		256
#घोषणा XGBE_RSS_LOOKUP_TABLE_TYPE	0
#घोषणा XGBE_RSS_HASH_KEY_TYPE		1

/* Auto-negotiation */
#घोषणा XGBE_AN_MS_TIMEOUT		500
#घोषणा XGBE_LINK_TIMEOUT		5

#घोषणा XGBE_SGMII_AN_LINK_STATUS	BIT(1)
#घोषणा XGBE_SGMII_AN_LINK_SPEED	(BIT(2) | BIT(3))
#घोषणा XGBE_SGMII_AN_LINK_SPEED_100	0x04
#घोषणा XGBE_SGMII_AN_LINK_SPEED_1000	0x08
#घोषणा XGBE_SGMII_AN_LINK_DUPLEX	BIT(4)

/* ECC correctable error notअगरication winकरोw (seconds) */
#घोषणा XGBE_ECC_LIMIT			60

/* MDIO port types */
#घोषणा XGMAC_MAX_C22_PORT		3

/* Link mode bit operations */
#घोषणा XGBE_ZERO_SUP(_ls)		\
	ethtool_link_ksettings_zero_link_mode((_ls), supported)

#घोषणा XGBE_SET_SUP(_ls, _mode)	\
	ethtool_link_ksettings_add_link_mode((_ls), supported, _mode)

#घोषणा XGBE_CLR_SUP(_ls, _mode)	\
	ethtool_link_ksettings_del_link_mode((_ls), supported, _mode)

#घोषणा XGBE_IS_SUP(_ls, _mode)	\
	ethtool_link_ksettings_test_link_mode((_ls), supported, _mode)

#घोषणा XGBE_ZERO_ADV(_ls)		\
	ethtool_link_ksettings_zero_link_mode((_ls), advertising)

#घोषणा XGBE_SET_ADV(_ls, _mode)	\
	ethtool_link_ksettings_add_link_mode((_ls), advertising, _mode)

#घोषणा XGBE_CLR_ADV(_ls, _mode)	\
	ethtool_link_ksettings_del_link_mode((_ls), advertising, _mode)

#घोषणा XGBE_ADV(_ls, _mode)		\
	ethtool_link_ksettings_test_link_mode((_ls), advertising, _mode)

#घोषणा XGBE_ZERO_LP_ADV(_ls)		\
	ethtool_link_ksettings_zero_link_mode((_ls), lp_advertising)

#घोषणा XGBE_SET_LP_ADV(_ls, _mode)	\
	ethtool_link_ksettings_add_link_mode((_ls), lp_advertising, _mode)

#घोषणा XGBE_CLR_LP_ADV(_ls, _mode)	\
	ethtool_link_ksettings_del_link_mode((_ls), lp_advertising, _mode)

#घोषणा XGBE_LP_ADV(_ls, _mode)		\
	ethtool_link_ksettings_test_link_mode((_ls), lp_advertising, _mode)

#घोषणा XGBE_LM_COPY(_dst, _dname, _src, _sname)	\
	biपंचांगap_copy((_dst)->link_modes._dname,		\
		    (_src)->link_modes._sname,		\
		    __ETHTOOL_LINK_MODE_MASK_NBITS)

काष्ठा xgbe_prv_data;

काष्ठा xgbe_packet_data अणु
	काष्ठा sk_buff *skb;

	अचिन्हित पूर्णांक attributes;

	अचिन्हित पूर्णांक errors;

	अचिन्हित पूर्णांक rdesc_count;
	अचिन्हित पूर्णांक length;

	अचिन्हित पूर्णांक header_len;
	अचिन्हित पूर्णांक tcp_header_len;
	अचिन्हित पूर्णांक tcp_payload_len;
	अचिन्हित लघु mss;

	अचिन्हित लघु vlan_ctag;

	u64 rx_tstamp;

	u32 rss_hash;
	क्रमागत pkt_hash_types rss_hash_type;

	अचिन्हित पूर्णांक tx_packets;
	अचिन्हित पूर्णांक tx_bytes;
पूर्ण;

/* Common Rx and Tx descriptor mapping */
काष्ठा xgbe_ring_desc अणु
	__le32 desc0;
	__le32 desc1;
	__le32 desc2;
	__le32 desc3;
पूर्ण;

/* Page allocation related values */
काष्ठा xgbe_page_alloc अणु
	काष्ठा page *pages;
	अचिन्हित पूर्णांक pages_len;
	अचिन्हित पूर्णांक pages_offset;

	dma_addr_t pages_dma;
पूर्ण;

/* Ring entry buffer data */
काष्ठा xgbe_buffer_data अणु
	काष्ठा xgbe_page_alloc pa;
	काष्ठा xgbe_page_alloc pa_unmap;

	dma_addr_t dma_base;
	अचिन्हित दीर्घ dma_off;
	अचिन्हित पूर्णांक dma_len;
पूर्ण;

/* Tx-related ring data */
काष्ठा xgbe_tx_ring_data अणु
	अचिन्हित पूर्णांक packets;		/* BQL packet count */
	अचिन्हित पूर्णांक bytes;		/* BQL byte count */
पूर्ण;

/* Rx-related ring data */
काष्ठा xgbe_rx_ring_data अणु
	काष्ठा xgbe_buffer_data hdr;	/* Header locations */
	काष्ठा xgbe_buffer_data buf;	/* Payload locations */

	अचिन्हित लघु hdr_len;		/* Length of received header */
	अचिन्हित लघु len;		/* Length of received packet */
पूर्ण;

/* Structure used to hold inक्रमmation related to the descriptor
 * and the packet associated with the descriptor (always use
 * use the XGBE_GET_DESC_DATA macro to access this data from the ring)
 */
काष्ठा xgbe_ring_data अणु
	काष्ठा xgbe_ring_desc *rdesc;	/* Virtual address of descriptor */
	dma_addr_t rdesc_dma;		/* DMA address of descriptor */

	काष्ठा sk_buff *skb;		/* Virtual address of SKB */
	dma_addr_t skb_dma;		/* DMA address of SKB data */
	अचिन्हित पूर्णांक skb_dma_len;	/* Length of SKB DMA area */

	काष्ठा xgbe_tx_ring_data tx;	/* Tx-related data */
	काष्ठा xgbe_rx_ring_data rx;	/* Rx-related data */

	अचिन्हित पूर्णांक mapped_as_page;

	/* Incomplete receive save location.  If the budget is exhausted
	 * or the last descriptor (last normal descriptor or a following
	 * context descriptor) has not been DMA'd yet the current state
	 * of the receive processing needs to be saved.
	 */
	अचिन्हित पूर्णांक state_saved;
	काष्ठा अणु
		काष्ठा sk_buff *skb;
		अचिन्हित पूर्णांक len;
		अचिन्हित पूर्णांक error;
	पूर्ण state;
पूर्ण;

काष्ठा xgbe_ring अणु
	/* Ring lock - used just क्रम TX rings at the moment */
	spinlock_t lock;

	/* Per packet related inक्रमmation */
	काष्ठा xgbe_packet_data packet_data;

	/* Virtual/DMA addresses and count of allocated descriptor memory */
	काष्ठा xgbe_ring_desc *rdesc;
	dma_addr_t rdesc_dma;
	अचिन्हित पूर्णांक rdesc_count;

	/* Array of descriptor data corresponding the descriptor memory
	 * (always use the XGBE_GET_DESC_DATA macro to access this data)
	 */
	काष्ठा xgbe_ring_data *rdata;

	/* Page allocation क्रम RX buffers */
	काष्ठा xgbe_page_alloc rx_hdr_pa;
	काष्ठा xgbe_page_alloc rx_buf_pa;
	पूर्णांक node;

	/* Ring index values
	 *  cur   - Tx: index of descriptor to be used क्रम current transfer
	 *          Rx: index of descriptor to check क्रम packet availability
	 *  dirty - Tx: index of descriptor to check क्रम transfer complete
	 *          Rx: index of descriptor to check क्रम buffer पुनः_स्मृतिation
	 */
	अचिन्हित पूर्णांक cur;
	अचिन्हित पूर्णांक dirty;

	/* Coalesce frame count used क्रम पूर्णांकerrupt bit setting */
	अचिन्हित पूर्णांक coalesce_count;

	जोड़ अणु
		काष्ठा अणु
			अचिन्हित पूर्णांक queue_stopped;
			अचिन्हित पूर्णांक xmit_more;
			अचिन्हित लघु cur_mss;
			अचिन्हित लघु cur_vlan_ctag;
		पूर्ण tx;
	पूर्ण;
पूर्ण ____cacheline_aligned;

/* Structure used to describe the descriptor rings associated with
 * a DMA channel.
 */
काष्ठा xgbe_channel अणु
	अक्षर name[16];

	/* Address of निजी data area क्रम device */
	काष्ठा xgbe_prv_data *pdata;

	/* Queue index and base address of queue's DMA रेजिस्टरs */
	अचिन्हित पूर्णांक queue_index;
	व्योम __iomem *dma_regs;

	/* Per channel पूर्णांकerrupt irq number */
	पूर्णांक dma_irq;
	अक्षर dma_irq_name[IFNAMSIZ + 32];

	/* Netdev related settings */
	काष्ठा napi_काष्ठा napi;

	/* Per channel पूर्णांकerrupt enablement tracker */
	अचिन्हित पूर्णांक curr_ier;
	अचिन्हित पूर्णांक saved_ier;

	अचिन्हित पूर्णांक tx_समयr_active;
	काष्ठा समयr_list tx_समयr;

	काष्ठा xgbe_ring *tx_ring;
	काष्ठा xgbe_ring *rx_ring;

	पूर्णांक node;
	cpumask_t affinity_mask;
पूर्ण ____cacheline_aligned;

क्रमागत xgbe_state अणु
	XGBE_DOWN,
	XGBE_LINK_INIT,
	XGBE_LINK_ERR,
	XGBE_STOPPED,
पूर्ण;

क्रमागत xgbe_पूर्णांक अणु
	XGMAC_INT_DMA_CH_SR_TI,
	XGMAC_INT_DMA_CH_SR_TPS,
	XGMAC_INT_DMA_CH_SR_TBU,
	XGMAC_INT_DMA_CH_SR_RI,
	XGMAC_INT_DMA_CH_SR_RBU,
	XGMAC_INT_DMA_CH_SR_RPS,
	XGMAC_INT_DMA_CH_SR_TI_RI,
	XGMAC_INT_DMA_CH_SR_FBE,
	XGMAC_INT_DMA_ALL,
पूर्ण;

क्रमागत xgbe_पूर्णांक_state अणु
	XGMAC_INT_STATE_SAVE,
	XGMAC_INT_STATE_RESTORE,
पूर्ण;

क्रमागत xgbe_ecc_sec अणु
	XGBE_ECC_SEC_TX,
	XGBE_ECC_SEC_RX,
	XGBE_ECC_SEC_DESC,
पूर्ण;

क्रमागत xgbe_speed अणु
	XGBE_SPEED_1000 = 0,
	XGBE_SPEED_2500,
	XGBE_SPEED_10000,
	XGBE_SPEEDS,
पूर्ण;

क्रमागत xgbe_xpcs_access अणु
	XGBE_XPCS_ACCESS_V1 = 0,
	XGBE_XPCS_ACCESS_V2,
पूर्ण;

क्रमागत xgbe_an_mode अणु
	XGBE_AN_MODE_CL73 = 0,
	XGBE_AN_MODE_CL73_REDRV,
	XGBE_AN_MODE_CL37,
	XGBE_AN_MODE_CL37_SGMII,
	XGBE_AN_MODE_NONE,
पूर्ण;

क्रमागत xgbe_an अणु
	XGBE_AN_READY = 0,
	XGBE_AN_PAGE_RECEIVED,
	XGBE_AN_INCOMPAT_LINK,
	XGBE_AN_COMPLETE,
	XGBE_AN_NO_LINK,
	XGBE_AN_ERROR,
पूर्ण;

क्रमागत xgbe_rx अणु
	XGBE_RX_BPA = 0,
	XGBE_RX_XNP,
	XGBE_RX_COMPLETE,
	XGBE_RX_ERROR,
पूर्ण;

क्रमागत xgbe_mode अणु
	XGBE_MODE_KX_1000 = 0,
	XGBE_MODE_KX_2500,
	XGBE_MODE_KR,
	XGBE_MODE_X,
	XGBE_MODE_SGMII_100,
	XGBE_MODE_SGMII_1000,
	XGBE_MODE_SFI,
	XGBE_MODE_UNKNOWN,
पूर्ण;

क्रमागत xgbe_speedset अणु
	XGBE_SPEEDSET_1000_10000 = 0,
	XGBE_SPEEDSET_2500_10000,
पूर्ण;

क्रमागत xgbe_mdio_mode अणु
	XGBE_MDIO_MODE_NONE = 0,
	XGBE_MDIO_MODE_CL22,
	XGBE_MDIO_MODE_CL45,
पूर्ण;

काष्ठा xgbe_phy अणु
	काष्ठा ethtool_link_ksettings lks;

	पूर्णांक address;

	पूर्णांक स्वतःneg;
	पूर्णांक speed;
	पूर्णांक duplex;

	पूर्णांक link;

	पूर्णांक छोड़ो_स्वतःneg;
	पूर्णांक tx_छोड़ो;
	पूर्णांक rx_छोड़ो;
पूर्ण;

क्रमागत xgbe_i2c_cmd अणु
	XGBE_I2C_CMD_READ = 0,
	XGBE_I2C_CMD_WRITE,
पूर्ण;

काष्ठा xgbe_i2c_op अणु
	क्रमागत xgbe_i2c_cmd cmd;

	अचिन्हित पूर्णांक target;

	व्योम *buf;
	अचिन्हित पूर्णांक len;
पूर्ण;

काष्ठा xgbe_i2c_op_state अणु
	काष्ठा xgbe_i2c_op *op;

	अचिन्हित पूर्णांक tx_len;
	अचिन्हित अक्षर *tx_buf;

	अचिन्हित पूर्णांक rx_len;
	अचिन्हित अक्षर *rx_buf;

	अचिन्हित पूर्णांक tx_पात_source;

	पूर्णांक ret;
पूर्ण;

काष्ठा xgbe_i2c अणु
	अचिन्हित पूर्णांक started;
	अचिन्हित पूर्णांक max_speed_mode;
	अचिन्हित पूर्णांक rx_fअगरo_size;
	अचिन्हित पूर्णांक tx_fअगरo_size;

	काष्ठा xgbe_i2c_op_state op_state;
पूर्ण;

काष्ठा xgbe_mmc_stats अणु
	/* Tx Stats */
	u64 txoctetcount_gb;
	u64 txframecount_gb;
	u64 txbroadcastframes_g;
	u64 txmulticastframes_g;
	u64 tx64octets_gb;
	u64 tx65to127octets_gb;
	u64 tx128to255octets_gb;
	u64 tx256to511octets_gb;
	u64 tx512to1023octets_gb;
	u64 tx1024tomaxoctets_gb;
	u64 txunicastframes_gb;
	u64 txmulticastframes_gb;
	u64 txbroadcastframes_gb;
	u64 txunderflowerror;
	u64 txoctetcount_g;
	u64 txframecount_g;
	u64 txछोड़ोframes;
	u64 txvlanframes_g;

	/* Rx Stats */
	u64 rxframecount_gb;
	u64 rxoctetcount_gb;
	u64 rxoctetcount_g;
	u64 rxbroadcastframes_g;
	u64 rxmulticastframes_g;
	u64 rxcrcerror;
	u64 rxrunterror;
	u64 rxjabbererror;
	u64 rxundersize_g;
	u64 rxoversize_g;
	u64 rx64octets_gb;
	u64 rx65to127octets_gb;
	u64 rx128to255octets_gb;
	u64 rx256to511octets_gb;
	u64 rx512to1023octets_gb;
	u64 rx1024tomaxoctets_gb;
	u64 rxunicastframes_g;
	u64 rxlengtherror;
	u64 rxoutofrangetype;
	u64 rxछोड़ोframes;
	u64 rxfअगरooverflow;
	u64 rxvlanframes_gb;
	u64 rxwatchकरोgerror;
पूर्ण;

काष्ठा xgbe_ext_stats अणु
	u64 tx_tso_packets;
	u64 rx_split_header_packets;
	u64 rx_buffer_unavailable;

	u64 txq_packets[XGBE_MAX_DMA_CHANNELS];
	u64 txq_bytes[XGBE_MAX_DMA_CHANNELS];
	u64 rxq_packets[XGBE_MAX_DMA_CHANNELS];
	u64 rxq_bytes[XGBE_MAX_DMA_CHANNELS];

	u64 tx_vxlan_packets;
	u64 rx_vxlan_packets;
	u64 rx_csum_errors;
	u64 rx_vxlan_csum_errors;
पूर्ण;

काष्ठा xgbe_hw_अगर अणु
	पूर्णांक (*tx_complete)(काष्ठा xgbe_ring_desc *);

	पूर्णांक (*set_mac_address)(काष्ठा xgbe_prv_data *, u8 *addr);
	पूर्णांक (*config_rx_mode)(काष्ठा xgbe_prv_data *);

	पूर्णांक (*enable_rx_csum)(काष्ठा xgbe_prv_data *);
	पूर्णांक (*disable_rx_csum)(काष्ठा xgbe_prv_data *);

	पूर्णांक (*enable_rx_vlan_stripping)(काष्ठा xgbe_prv_data *);
	पूर्णांक (*disable_rx_vlan_stripping)(काष्ठा xgbe_prv_data *);
	पूर्णांक (*enable_rx_vlan_filtering)(काष्ठा xgbe_prv_data *);
	पूर्णांक (*disable_rx_vlan_filtering)(काष्ठा xgbe_prv_data *);
	पूर्णांक (*update_vlan_hash_table)(काष्ठा xgbe_prv_data *);

	पूर्णांक (*पढ़ो_mmd_regs)(काष्ठा xgbe_prv_data *, पूर्णांक, पूर्णांक);
	व्योम (*ग_लिखो_mmd_regs)(काष्ठा xgbe_prv_data *, पूर्णांक, पूर्णांक, पूर्णांक);
	पूर्णांक (*set_speed)(काष्ठा xgbe_prv_data *, पूर्णांक);

	पूर्णांक (*set_ext_mii_mode)(काष्ठा xgbe_prv_data *, अचिन्हित पूर्णांक,
				क्रमागत xgbe_mdio_mode);
	पूर्णांक (*पढ़ो_ext_mii_regs)(काष्ठा xgbe_prv_data *, पूर्णांक, पूर्णांक);
	पूर्णांक (*ग_लिखो_ext_mii_regs)(काष्ठा xgbe_prv_data *, पूर्णांक, पूर्णांक, u16);

	पूर्णांक (*set_gpio)(काष्ठा xgbe_prv_data *, अचिन्हित पूर्णांक);
	पूर्णांक (*clr_gpio)(काष्ठा xgbe_prv_data *, अचिन्हित पूर्णांक);

	व्योम (*enable_tx)(काष्ठा xgbe_prv_data *);
	व्योम (*disable_tx)(काष्ठा xgbe_prv_data *);
	व्योम (*enable_rx)(काष्ठा xgbe_prv_data *);
	व्योम (*disable_rx)(काष्ठा xgbe_prv_data *);

	व्योम (*घातerup_tx)(काष्ठा xgbe_prv_data *);
	व्योम (*घातerकरोwn_tx)(काष्ठा xgbe_prv_data *);
	व्योम (*घातerup_rx)(काष्ठा xgbe_prv_data *);
	व्योम (*घातerकरोwn_rx)(काष्ठा xgbe_prv_data *);

	पूर्णांक (*init)(काष्ठा xgbe_prv_data *);
	पूर्णांक (*निकास)(काष्ठा xgbe_prv_data *);

	पूर्णांक (*enable_पूर्णांक)(काष्ठा xgbe_channel *, क्रमागत xgbe_पूर्णांक);
	पूर्णांक (*disable_पूर्णांक)(काष्ठा xgbe_channel *, क्रमागत xgbe_पूर्णांक);
	व्योम (*dev_xmit)(काष्ठा xgbe_channel *);
	पूर्णांक (*dev_पढ़ो)(काष्ठा xgbe_channel *);
	व्योम (*tx_desc_init)(काष्ठा xgbe_channel *);
	व्योम (*rx_desc_init)(काष्ठा xgbe_channel *);
	व्योम (*tx_desc_reset)(काष्ठा xgbe_ring_data *);
	व्योम (*rx_desc_reset)(काष्ठा xgbe_prv_data *, काष्ठा xgbe_ring_data *,
			      अचिन्हित पूर्णांक);
	पूर्णांक (*is_last_desc)(काष्ठा xgbe_ring_desc *);
	पूर्णांक (*is_context_desc)(काष्ठा xgbe_ring_desc *);
	व्योम (*tx_start_xmit)(काष्ठा xgbe_channel *, काष्ठा xgbe_ring *);

	/* For FLOW ctrl */
	पूर्णांक (*config_tx_flow_control)(काष्ठा xgbe_prv_data *);
	पूर्णांक (*config_rx_flow_control)(काष्ठा xgbe_prv_data *);

	/* For RX coalescing */
	पूर्णांक (*config_rx_coalesce)(काष्ठा xgbe_prv_data *);
	पूर्णांक (*config_tx_coalesce)(काष्ठा xgbe_prv_data *);
	अचिन्हित पूर्णांक (*usec_to_riwt)(काष्ठा xgbe_prv_data *, अचिन्हित पूर्णांक);
	अचिन्हित पूर्णांक (*riwt_to_usec)(काष्ठा xgbe_prv_data *, अचिन्हित पूर्णांक);

	/* For RX and TX threshold config */
	पूर्णांक (*config_rx_threshold)(काष्ठा xgbe_prv_data *, अचिन्हित पूर्णांक);
	पूर्णांक (*config_tx_threshold)(काष्ठा xgbe_prv_data *, अचिन्हित पूर्णांक);

	/* For RX and TX Store and Forward Mode config */
	पूर्णांक (*config_rsf_mode)(काष्ठा xgbe_prv_data *, अचिन्हित पूर्णांक);
	पूर्णांक (*config_tsf_mode)(काष्ठा xgbe_prv_data *, अचिन्हित पूर्णांक);

	/* For TX DMA Operate on Second Frame config */
	पूर्णांक (*config_osp_mode)(काष्ठा xgbe_prv_data *);

	/* For MMC statistics */
	व्योम (*rx_mmc_पूर्णांक)(काष्ठा xgbe_prv_data *);
	व्योम (*tx_mmc_पूर्णांक)(काष्ठा xgbe_prv_data *);
	व्योम (*पढ़ो_mmc_stats)(काष्ठा xgbe_prv_data *);

	/* For Timestamp config */
	पूर्णांक (*config_tstamp)(काष्ठा xgbe_prv_data *, अचिन्हित पूर्णांक);
	व्योम (*update_tstamp_addend)(काष्ठा xgbe_prv_data *, अचिन्हित पूर्णांक);
	व्योम (*set_tstamp_समय)(काष्ठा xgbe_prv_data *, अचिन्हित पूर्णांक sec,
				अचिन्हित पूर्णांक nsec);
	u64 (*get_tstamp_समय)(काष्ठा xgbe_prv_data *);
	u64 (*get_tx_tstamp)(काष्ठा xgbe_prv_data *);

	/* For Data Center Bridging config */
	व्योम (*config_tc)(काष्ठा xgbe_prv_data *);
	व्योम (*config_dcb_tc)(काष्ठा xgbe_prv_data *);
	व्योम (*config_dcb_pfc)(काष्ठा xgbe_prv_data *);

	/* For Receive Side Scaling */
	पूर्णांक (*enable_rss)(काष्ठा xgbe_prv_data *);
	पूर्णांक (*disable_rss)(काष्ठा xgbe_prv_data *);
	पूर्णांक (*set_rss_hash_key)(काष्ठा xgbe_prv_data *, स्थिर u8 *);
	पूर्णांक (*set_rss_lookup_table)(काष्ठा xgbe_prv_data *, स्थिर u32 *);

	/* For ECC */
	व्योम (*disable_ecc_ded)(काष्ठा xgbe_prv_data *);
	व्योम (*disable_ecc_sec)(काष्ठा xgbe_prv_data *, क्रमागत xgbe_ecc_sec);

	/* For VXLAN */
	व्योम (*enable_vxlan)(काष्ठा xgbe_prv_data *);
	व्योम (*disable_vxlan)(काष्ठा xgbe_prv_data *);
	व्योम (*set_vxlan_id)(काष्ठा xgbe_prv_data *);
पूर्ण;

/* This काष्ठाure represents implementation specअगरic routines क्रम an
 * implementation of a PHY. All routines are required unless noted below.
 *   Optional routines:
 *     an_pre, an_post
 *     kr_training_pre, kr_training_post
 *     module_info, module_eeprom
 */
काष्ठा xgbe_phy_impl_अगर अणु
	/* Perक्रमm Setup/tearकरोwn actions */
	पूर्णांक (*init)(काष्ठा xgbe_prv_data *);
	व्योम (*निकास)(काष्ठा xgbe_prv_data *);

	/* Perक्रमm start/stop specअगरic actions */
	पूर्णांक (*reset)(काष्ठा xgbe_prv_data *);
	पूर्णांक (*start)(काष्ठा xgbe_prv_data *);
	व्योम (*stop)(काष्ठा xgbe_prv_data *);

	/* Return the link status */
	पूर्णांक (*link_status)(काष्ठा xgbe_prv_data *, पूर्णांक *);

	/* Indicate अगर a particular speed is valid */
	bool (*valid_speed)(काष्ठा xgbe_prv_data *, पूर्णांक);

	/* Check अगर the specअगरied mode can/should be used */
	bool (*use_mode)(काष्ठा xgbe_prv_data *, क्रमागत xgbe_mode);
	/* Switch the PHY पूर्णांकo various modes */
	व्योम (*set_mode)(काष्ठा xgbe_prv_data *, क्रमागत xgbe_mode);
	/* Retrieve mode needed क्रम a specअगरic speed */
	क्रमागत xgbe_mode (*get_mode)(काष्ठा xgbe_prv_data *, पूर्णांक);
	/* Retrieve new/next mode when trying to स्वतः-negotiate */
	क्रमागत xgbe_mode (*चयन_mode)(काष्ठा xgbe_prv_data *);
	/* Retrieve current mode */
	क्रमागत xgbe_mode (*cur_mode)(काष्ठा xgbe_prv_data *);

	/* Retrieve current स्वतः-negotiation mode */
	क्रमागत xgbe_an_mode (*an_mode)(काष्ठा xgbe_prv_data *);

	/* Configure स्वतः-negotiation settings */
	पूर्णांक (*an_config)(काष्ठा xgbe_prv_data *);

	/* Set/override स्वतः-negotiation advertisement settings */
	व्योम (*an_advertising)(काष्ठा xgbe_prv_data *,
			       काष्ठा ethtool_link_ksettings *);

	/* Process results of स्वतः-negotiation */
	क्रमागत xgbe_mode (*an_outcome)(काष्ठा xgbe_prv_data *);

	/* Pre/Post स्वतः-negotiation support */
	व्योम (*an_pre)(काष्ठा xgbe_prv_data *);
	व्योम (*an_post)(काष्ठा xgbe_prv_data *);

	/* Pre/Post KR training enablement support */
	व्योम (*kr_training_pre)(काष्ठा xgbe_prv_data *);
	व्योम (*kr_training_post)(काष्ठा xgbe_prv_data *);

	/* SFP module related info */
	पूर्णांक (*module_info)(काष्ठा xgbe_prv_data *pdata,
			   काष्ठा ethtool_modinfo *modinfo);
	पूर्णांक (*module_eeprom)(काष्ठा xgbe_prv_data *pdata,
			     काष्ठा ethtool_eeprom *eeprom, u8 *data);
पूर्ण;

काष्ठा xgbe_phy_अगर अणु
	/* For PHY setup/tearकरोwn */
	पूर्णांक (*phy_init)(काष्ठा xgbe_prv_data *);
	व्योम (*phy_निकास)(काष्ठा xgbe_prv_data *);

	/* For PHY support when setting device up/करोwn */
	पूर्णांक (*phy_reset)(काष्ठा xgbe_prv_data *);
	पूर्णांक (*phy_start)(काष्ठा xgbe_prv_data *);
	व्योम (*phy_stop)(काष्ठा xgbe_prv_data *);

	/* For PHY support जबतक device is up */
	व्योम (*phy_status)(काष्ठा xgbe_prv_data *);
	पूर्णांक (*phy_config_aneg)(काष्ठा xgbe_prv_data *);

	/* For PHY settings validation */
	bool (*phy_valid_speed)(काष्ठा xgbe_prv_data *, पूर्णांक);

	/* For single पूर्णांकerrupt support */
	irqवापस_t (*an_isr)(काष्ठा xgbe_prv_data *);

	/* For ethtool PHY support */
	पूर्णांक (*module_info)(काष्ठा xgbe_prv_data *pdata,
			   काष्ठा ethtool_modinfo *modinfo);
	पूर्णांक (*module_eeprom)(काष्ठा xgbe_prv_data *pdata,
			     काष्ठा ethtool_eeprom *eeprom, u8 *data);

	/* PHY implementation specअगरic services */
	काष्ठा xgbe_phy_impl_अगर phy_impl;
पूर्ण;

काष्ठा xgbe_i2c_अगर अणु
	/* For initial I2C setup */
	पूर्णांक (*i2c_init)(काष्ठा xgbe_prv_data *);

	/* For I2C support when setting device up/करोwn */
	पूर्णांक (*i2c_start)(काष्ठा xgbe_prv_data *);
	व्योम (*i2c_stop)(काष्ठा xgbe_prv_data *);

	/* For perक्रमming I2C operations */
	पूर्णांक (*i2c_xfer)(काष्ठा xgbe_prv_data *, काष्ठा xgbe_i2c_op *);

	/* For single पूर्णांकerrupt support */
	irqवापस_t (*i2c_isr)(काष्ठा xgbe_prv_data *);
पूर्ण;

काष्ठा xgbe_desc_अगर अणु
	पूर्णांक (*alloc_ring_resources)(काष्ठा xgbe_prv_data *);
	व्योम (*मुक्त_ring_resources)(काष्ठा xgbe_prv_data *);
	पूर्णांक (*map_tx_skb)(काष्ठा xgbe_channel *, काष्ठा sk_buff *);
	पूर्णांक (*map_rx_buffer)(काष्ठा xgbe_prv_data *, काष्ठा xgbe_ring *,
			     काष्ठा xgbe_ring_data *);
	व्योम (*unmap_rdata)(काष्ठा xgbe_prv_data *, काष्ठा xgbe_ring_data *);
	व्योम (*wrapper_tx_desc_init)(काष्ठा xgbe_prv_data *);
	व्योम (*wrapper_rx_desc_init)(काष्ठा xgbe_prv_data *);
पूर्ण;

/* This काष्ठाure contains flags that indicate what hardware features
 * or configurations are present in the device.
 */
काष्ठा xgbe_hw_features अणु
	/* HW Version */
	अचिन्हित पूर्णांक version;

	/* HW Feature Register0 */
	अचिन्हित पूर्णांक gmii;		/* 1000 Mbps support */
	अचिन्हित पूर्णांक vlhash;		/* VLAN Hash Filter */
	अचिन्हित पूर्णांक sma;		/* SMA(MDIO) Interface */
	अचिन्हित पूर्णांक rwk;		/* PMT remote wake-up packet */
	अचिन्हित पूर्णांक mgk;		/* PMT magic packet */
	अचिन्हित पूर्णांक mmc;		/* RMON module */
	अचिन्हित पूर्णांक aoe;		/* ARP Offload */
	अचिन्हित पूर्णांक ts;		/* IEEE 1588-2008 Advanced Timestamp */
	अचिन्हित पूर्णांक eee;		/* Energy Efficient Ethernet */
	अचिन्हित पूर्णांक tx_coe;		/* Tx Checksum Offload */
	अचिन्हित पूर्णांक rx_coe;		/* Rx Checksum Offload */
	अचिन्हित पूर्णांक addn_mac;		/* Additional MAC Addresses */
	अचिन्हित पूर्णांक ts_src;		/* Timestamp Source */
	अचिन्हित पूर्णांक sa_vlan_ins;	/* Source Address or VLAN Insertion */
	अचिन्हित पूर्णांक vxn;		/* VXLAN/NVGRE */

	/* HW Feature Register1 */
	अचिन्हित पूर्णांक rx_fअगरo_size;	/* MTL Receive FIFO Size */
	अचिन्हित पूर्णांक tx_fअगरo_size;	/* MTL Transmit FIFO Size */
	अचिन्हित पूर्णांक adv_ts_hi;		/* Advance Timestamping High Word */
	अचिन्हित पूर्णांक dma_width;		/* DMA width */
	अचिन्हित पूर्णांक dcb;		/* DCB Feature */
	अचिन्हित पूर्णांक sph;		/* Split Header Feature */
	अचिन्हित पूर्णांक tso;		/* TCP Segmentation Offload */
	अचिन्हित पूर्णांक dma_debug;		/* DMA Debug Registers */
	अचिन्हित पूर्णांक rss;		/* Receive Side Scaling */
	अचिन्हित पूर्णांक tc_cnt;		/* Number of Traffic Classes */
	अचिन्हित पूर्णांक hash_table_size;	/* Hash Table Size */
	अचिन्हित पूर्णांक l3l4_filter_num;	/* Number of L3-L4 Filters */

	/* HW Feature Register2 */
	अचिन्हित पूर्णांक rx_q_cnt;		/* Number of MTL Receive Queues */
	अचिन्हित पूर्णांक tx_q_cnt;		/* Number of MTL Transmit Queues */
	अचिन्हित पूर्णांक rx_ch_cnt;		/* Number of DMA Receive Channels */
	अचिन्हित पूर्णांक tx_ch_cnt;		/* Number of DMA Transmit Channels */
	अचिन्हित पूर्णांक pps_out_num;	/* Number of PPS outमाला_दो */
	अचिन्हित पूर्णांक aux_snap_num;	/* Number of Aux snapshot inमाला_दो */
पूर्ण;

काष्ठा xgbe_version_data अणु
	व्योम (*init_function_ptrs_phy_impl)(काष्ठा xgbe_phy_अगर *);
	क्रमागत xgbe_xpcs_access xpcs_access;
	अचिन्हित पूर्णांक mmc_64bit;
	अचिन्हित पूर्णांक tx_max_fअगरo_size;
	अचिन्हित पूर्णांक rx_max_fअगरo_size;
	अचिन्हित पूर्णांक tx_tstamp_workaround;
	अचिन्हित पूर्णांक ecc_support;
	अचिन्हित पूर्णांक i2c_support;
	अचिन्हित पूर्णांक irq_reissue_support;
	अचिन्हित पूर्णांक tx_desc_prefetch;
	अचिन्हित पूर्णांक rx_desc_prefetch;
	अचिन्हित पूर्णांक an_cdr_workaround;
पूर्ण;

काष्ठा xgbe_prv_data अणु
	काष्ठा net_device *netdev;
	काष्ठा pci_dev *pcidev;
	काष्ठा platक्रमm_device *platdev;
	काष्ठा acpi_device *adev;
	काष्ठा device *dev;
	काष्ठा platक्रमm_device *phy_platdev;
	काष्ठा device *phy_dev;

	/* Version related data */
	काष्ठा xgbe_version_data *vdata;

	/* ACPI or DT flag */
	अचिन्हित पूर्णांक use_acpi;

	/* XGMAC/XPCS related mmio रेजिस्टरs */
	व्योम __iomem *xgmac_regs;	/* XGMAC CSRs */
	व्योम __iomem *xpcs_regs;	/* XPCS MMD रेजिस्टरs */
	व्योम __iomem *rxtx_regs;	/* SerDes Rx/Tx CSRs */
	व्योम __iomem *sir0_regs;	/* SerDes पूर्णांकegration रेजिस्टरs (1/2) */
	व्योम __iomem *sir1_regs;	/* SerDes पूर्णांकegration रेजिस्टरs (2/2) */
	व्योम __iomem *xprop_regs;	/* XGBE property रेजिस्टरs */
	व्योम __iomem *xi2c_regs;	/* XGBE I2C CSRs */

	/* Port property रेजिस्टरs */
	अचिन्हित पूर्णांक pp0;
	अचिन्हित पूर्णांक pp1;
	अचिन्हित पूर्णांक pp2;
	अचिन्हित पूर्णांक pp3;
	अचिन्हित पूर्णांक pp4;

	/* Overall device lock */
	spinlock_t lock;

	/* XPCS indirect addressing lock */
	spinlock_t xpcs_lock;
	अचिन्हित पूर्णांक xpcs_winकरोw_def_reg;
	अचिन्हित पूर्णांक xpcs_winकरोw_sel_reg;
	अचिन्हित पूर्णांक xpcs_winकरोw;
	अचिन्हित पूर्णांक xpcs_winकरोw_size;
	अचिन्हित पूर्णांक xpcs_winकरोw_mask;

	/* RSS addressing mutex */
	काष्ठा mutex rss_mutex;

	/* Flags representing xgbe_state */
	अचिन्हित दीर्घ dev_state;

	/* ECC support */
	अचिन्हित दीर्घ tx_sec_period;
	अचिन्हित दीर्घ tx_ded_period;
	अचिन्हित दीर्घ rx_sec_period;
	अचिन्हित दीर्घ rx_ded_period;
	अचिन्हित दीर्घ desc_sec_period;
	अचिन्हित दीर्घ desc_ded_period;

	अचिन्हित पूर्णांक tx_sec_count;
	अचिन्हित पूर्णांक tx_ded_count;
	अचिन्हित पूर्णांक rx_sec_count;
	अचिन्हित पूर्णांक rx_ded_count;
	अचिन्हित पूर्णांक desc_ded_count;
	अचिन्हित पूर्णांक desc_sec_count;

	पूर्णांक dev_irq;
	पूर्णांक ecc_irq;
	पूर्णांक i2c_irq;
	पूर्णांक channel_irq[XGBE_MAX_DMA_CHANNELS];

	अचिन्हित पूर्णांक per_channel_irq;
	अचिन्हित पूर्णांक irq_count;
	अचिन्हित पूर्णांक channel_irq_count;
	अचिन्हित पूर्णांक channel_irq_mode;

	अक्षर ecc_name[IFNAMSIZ + 32];

	काष्ठा xgbe_hw_अगर hw_अगर;
	काष्ठा xgbe_phy_अगर phy_अगर;
	काष्ठा xgbe_desc_अगर desc_अगर;
	काष्ठा xgbe_i2c_अगर i2c_अगर;

	/* AXI DMA settings */
	अचिन्हित पूर्णांक coherent;
	अचिन्हित पूर्णांक arcr;
	अचिन्हित पूर्णांक awcr;
	अचिन्हित पूर्णांक awarcr;

	/* Service routine support */
	काष्ठा workqueue_काष्ठा *dev_workqueue;
	काष्ठा work_काष्ठा service_work;
	काष्ठा समयr_list service_समयr;

	/* Rings क्रम Tx/Rx on a DMA channel */
	काष्ठा xgbe_channel *channel[XGBE_MAX_DMA_CHANNELS];
	अचिन्हित पूर्णांक tx_max_channel_count;
	अचिन्हित पूर्णांक rx_max_channel_count;
	अचिन्हित पूर्णांक channel_count;
	अचिन्हित पूर्णांक tx_ring_count;
	अचिन्हित पूर्णांक tx_desc_count;
	अचिन्हित पूर्णांक rx_ring_count;
	अचिन्हित पूर्णांक rx_desc_count;

	अचिन्हित पूर्णांक new_tx_ring_count;
	अचिन्हित पूर्णांक new_rx_ring_count;

	अचिन्हित पूर्णांक tx_max_q_count;
	अचिन्हित पूर्णांक rx_max_q_count;
	अचिन्हित पूर्णांक tx_q_count;
	अचिन्हित पूर्णांक rx_q_count;

	/* Tx/Rx common settings */
	अचिन्हित पूर्णांक blen;
	अचिन्हित पूर्णांक pbl;
	अचिन्हित पूर्णांक aal;
	अचिन्हित पूर्णांक rd_osr_limit;
	अचिन्हित पूर्णांक wr_osr_limit;

	/* Tx settings */
	अचिन्हित पूर्णांक tx_sf_mode;
	अचिन्हित पूर्णांक tx_threshold;
	अचिन्हित पूर्णांक tx_osp_mode;
	अचिन्हित पूर्णांक tx_max_fअगरo_size;

	/* Rx settings */
	अचिन्हित पूर्णांक rx_sf_mode;
	अचिन्हित पूर्णांक rx_threshold;
	अचिन्हित पूर्णांक rx_max_fअगरo_size;

	/* Tx coalescing settings */
	अचिन्हित पूर्णांक tx_usecs;
	अचिन्हित पूर्णांक tx_frames;

	/* Rx coalescing settings */
	अचिन्हित पूर्णांक rx_riwt;
	अचिन्हित पूर्णांक rx_usecs;
	अचिन्हित पूर्णांक rx_frames;

	/* Current Rx buffer size */
	अचिन्हित पूर्णांक rx_buf_size;

	/* Flow control settings */
	अचिन्हित पूर्णांक छोड़ो_स्वतःneg;
	अचिन्हित पूर्णांक tx_छोड़ो;
	अचिन्हित पूर्णांक rx_छोड़ो;
	अचिन्हित पूर्णांक rx_rfa[XGBE_MAX_QUEUES];
	अचिन्हित पूर्णांक rx_rfd[XGBE_MAX_QUEUES];

	/* Receive Side Scaling settings */
	u8 rss_key[XGBE_RSS_HASH_KEY_SIZE];
	u32 rss_table[XGBE_RSS_MAX_TABLE_SIZE];
	u32 rss_options;

	/* VXLAN settings */
	u16 vxlan_port;

	/* Netdev related settings */
	अचिन्हित अक्षर mac_addr[ETH_ALEN];
	netdev_features_t netdev_features;
	काष्ठा napi_काष्ठा napi;
	काष्ठा xgbe_mmc_stats mmc_stats;
	काष्ठा xgbe_ext_stats ext_stats;

	/* Filtering support */
	अचिन्हित दीर्घ active_vlans[BITS_TO_LONGS(VLAN_N_VID)];

	/* Device घड़ीs */
	काष्ठा clk *sysclk;
	अचिन्हित दीर्घ sysclk_rate;
	काष्ठा clk *ptpclk;
	अचिन्हित दीर्घ ptpclk_rate;

	/* Timestamp support */
	spinlock_t tstamp_lock;
	काष्ठा ptp_घड़ी_info ptp_घड़ी_info;
	काष्ठा ptp_घड़ी *ptp_घड़ी;
	काष्ठा hwtstamp_config tstamp_config;
	काष्ठा cyclecounter tstamp_cc;
	काष्ठा समयcounter tstamp_tc;
	अचिन्हित पूर्णांक tstamp_addend;
	काष्ठा work_काष्ठा tx_tstamp_work;
	काष्ठा sk_buff *tx_tstamp_skb;
	u64 tx_tstamp;

	/* DCB support */
	काष्ठा ieee_ets *ets;
	काष्ठा ieee_pfc *pfc;
	अचिन्हित पूर्णांक q2tc_map[XGBE_MAX_QUEUES];
	अचिन्हित पूर्णांक prio2q_map[IEEE_8021QAZ_MAX_TCS];
	अचिन्हित पूर्णांक pfcq[XGBE_MAX_QUEUES];
	अचिन्हित पूर्णांक pfc_rfa;
	u8 num_tcs;

	/* Hardware features of the device */
	काष्ठा xgbe_hw_features hw_feat;

	/* Device work काष्ठाures */
	काष्ठा work_काष्ठा restart_work;
	काष्ठा work_काष्ठा stopdev_work;

	/* Keeps track of घातer mode */
	अचिन्हित पूर्णांक घातer_करोwn;

	/* Network पूर्णांकerface message level setting */
	u32 msg_enable;

	/* Current PHY settings */
	phy_पूर्णांकerface_t phy_mode;
	पूर्णांक phy_link;
	पूर्णांक phy_speed;

	/* MDIO/PHY related settings */
	अचिन्हित पूर्णांक phy_started;
	व्योम *phy_data;
	काष्ठा xgbe_phy phy;
	पूर्णांक mdio_mmd;
	अचिन्हित दीर्घ link_check;
	काष्ठा completion mdio_complete;

	अचिन्हित पूर्णांक kr_redrv;

	अक्षर an_name[IFNAMSIZ + 32];
	काष्ठा workqueue_काष्ठा *an_workqueue;

	पूर्णांक an_irq;
	काष्ठा work_काष्ठा an_irq_work;

	/* Auto-negotiation state machine support */
	अचिन्हित पूर्णांक an_पूर्णांक;
	अचिन्हित पूर्णांक an_status;
	काष्ठा mutex an_mutex;
	क्रमागत xgbe_an an_result;
	क्रमागत xgbe_an an_state;
	क्रमागत xgbe_rx kr_state;
	क्रमागत xgbe_rx kx_state;
	काष्ठा work_काष्ठा an_work;
	अचिन्हित पूर्णांक an_again;
	अचिन्हित पूर्णांक an_supported;
	अचिन्हित पूर्णांक parallel_detect;
	अचिन्हित पूर्णांक fec_ability;
	अचिन्हित दीर्घ an_start;
	क्रमागत xgbe_an_mode an_mode;

	/* I2C support */
	काष्ठा xgbe_i2c i2c;
	काष्ठा mutex i2c_mutex;
	काष्ठा completion i2c_complete;
	अक्षर i2c_name[IFNAMSIZ + 32];

	अचिन्हित पूर्णांक lpm_ctrl;		/* CTRL1 क्रम resume */

	अचिन्हित पूर्णांक isr_as_tasklet;
	काष्ठा tasklet_काष्ठा tasklet_dev;
	काष्ठा tasklet_काष्ठा tasklet_ecc;
	काष्ठा tasklet_काष्ठा tasklet_i2c;
	काष्ठा tasklet_काष्ठा tasklet_an;

	काष्ठा dentry *xgbe_debugfs;

	अचिन्हित पूर्णांक debugfs_xgmac_reg;

	अचिन्हित पूर्णांक debugfs_xpcs_mmd;
	अचिन्हित पूर्णांक debugfs_xpcs_reg;

	अचिन्हित पूर्णांक debugfs_xprop_reg;

	अचिन्हित पूर्णांक debugfs_xi2c_reg;

	bool debugfs_an_cdr_workaround;
	bool debugfs_an_cdr_track_early;
पूर्ण;

/* Function prototypes*/
काष्ठा xgbe_prv_data *xgbe_alloc_pdata(काष्ठा device *);
व्योम xgbe_मुक्त_pdata(काष्ठा xgbe_prv_data *);
व्योम xgbe_set_counts(काष्ठा xgbe_prv_data *);
पूर्णांक xgbe_config_netdev(काष्ठा xgbe_prv_data *);
व्योम xgbe_deconfig_netdev(काष्ठा xgbe_prv_data *);

पूर्णांक xgbe_platक्रमm_init(व्योम);
व्योम xgbe_platक्रमm_निकास(व्योम);
#अगर_घोषित CONFIG_PCI
पूर्णांक xgbe_pci_init(व्योम);
व्योम xgbe_pci_निकास(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक xgbe_pci_init(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम xgbe_pci_निकास(व्योम) अणु पूर्ण
#पूर्ण_अगर

व्योम xgbe_init_function_ptrs_dev(काष्ठा xgbe_hw_अगर *);
व्योम xgbe_init_function_ptrs_phy(काष्ठा xgbe_phy_अगर *);
व्योम xgbe_init_function_ptrs_phy_v1(काष्ठा xgbe_phy_अगर *);
व्योम xgbe_init_function_ptrs_phy_v2(काष्ठा xgbe_phy_अगर *);
व्योम xgbe_init_function_ptrs_desc(काष्ठा xgbe_desc_अगर *);
व्योम xgbe_init_function_ptrs_i2c(काष्ठा xgbe_i2c_अगर *);
स्थिर काष्ठा net_device_ops *xgbe_get_netdev_ops(व्योम);
स्थिर काष्ठा ethtool_ops *xgbe_get_ethtool_ops(व्योम);
स्थिर काष्ठा udp_tunnel_nic_info *xgbe_get_udp_tunnel_info(व्योम);

#अगर_घोषित CONFIG_AMD_XGBE_DCB
स्थिर काष्ठा dcbnl_rtnl_ops *xgbe_get_dcbnl_ops(व्योम);
#पूर्ण_अगर

व्योम xgbe_ptp_रेजिस्टर(काष्ठा xgbe_prv_data *);
व्योम xgbe_ptp_unरेजिस्टर(काष्ठा xgbe_prv_data *);
व्योम xgbe_dump_tx_desc(काष्ठा xgbe_prv_data *, काष्ठा xgbe_ring *,
		       अचिन्हित पूर्णांक, अचिन्हित पूर्णांक, अचिन्हित पूर्णांक);
व्योम xgbe_dump_rx_desc(काष्ठा xgbe_prv_data *, काष्ठा xgbe_ring *,
		       अचिन्हित पूर्णांक);
व्योम xgbe_prपूर्णांक_pkt(काष्ठा net_device *, काष्ठा sk_buff *, bool);
व्योम xgbe_get_all_hw_features(काष्ठा xgbe_prv_data *);
पूर्णांक xgbe_घातerup(काष्ठा net_device *, अचिन्हित पूर्णांक);
पूर्णांक xgbe_घातerकरोwn(काष्ठा net_device *, अचिन्हित पूर्णांक);
व्योम xgbe_init_rx_coalesce(काष्ठा xgbe_prv_data *);
व्योम xgbe_init_tx_coalesce(काष्ठा xgbe_prv_data *);
व्योम xgbe_restart_dev(काष्ठा xgbe_prv_data *pdata);
व्योम xgbe_full_restart_dev(काष्ठा xgbe_prv_data *pdata);

#अगर_घोषित CONFIG_DEBUG_FS
व्योम xgbe_debugfs_init(काष्ठा xgbe_prv_data *);
व्योम xgbe_debugfs_निकास(काष्ठा xgbe_prv_data *);
व्योम xgbe_debugfs_नाम(काष्ठा xgbe_prv_data *pdata);
#अन्यथा
अटल अंतरभूत व्योम xgbe_debugfs_init(काष्ठा xgbe_prv_data *pdata) अणुपूर्ण
अटल अंतरभूत व्योम xgbe_debugfs_निकास(काष्ठा xgbe_prv_data *pdata) अणुपूर्ण
अटल अंतरभूत व्योम xgbe_debugfs_नाम(काष्ठा xgbe_prv_data *pdata) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_DEBUG_FS */

/* NOTE: Uncomment क्रम function trace log messages in KERNEL LOG */
#अगर 0
#घोषणा YDEBUG
#घोषणा YDEBUG_MDIO
#पूर्ण_अगर

/* For debug prपूर्णांकs */
#अगर_घोषित YDEBUG
#घोषणा DBGPR(x...) pr_alert(x)
#अन्यथा
#घोषणा DBGPR(x...) करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

#अगर_घोषित YDEBUG_MDIO
#घोषणा DBGPR_MDIO(x...) pr_alert(x)
#अन्यथा
#घोषणा DBGPR_MDIO(x...) करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

#पूर्ण_अगर
