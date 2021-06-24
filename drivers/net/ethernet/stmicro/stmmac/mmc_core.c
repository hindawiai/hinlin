<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*******************************************************************************
  DWMAC Management Counters

  Copyright (C) 2011  STMicroelectronics Ltd


  Author: Giuseppe Cavallaro <peppe.cavallaro@st.com>
*******************************************************************************/

#समावेश <linux/kernel.h>
#समावेश <linux/पन.स>
#समावेश "hwif.h"
#समावेश "mmc.h"

/* MAC Management Counters रेजिस्टर offset */

#घोषणा MMC_CNTRL		0x00	/* MMC Control */
#घोषणा MMC_RX_INTR		0x04	/* MMC RX Interrupt */
#घोषणा MMC_TX_INTR		0x08	/* MMC TX Interrupt */
#घोषणा MMC_RX_INTR_MASK	0x0c	/* MMC Interrupt Mask */
#घोषणा MMC_TX_INTR_MASK	0x10	/* MMC Interrupt Mask */
#घोषणा MMC_DEFAULT_MASK	0xffffffff

/* MMC TX counter रेजिस्टरs */

/* Note:
 * _GB रेजिस्टर stands क्रम good and bad frames
 * _G is क्रम good only.
 */
#घोषणा MMC_TX_OCTETCOUNT_GB		0x14
#घोषणा MMC_TX_FRAMECOUNT_GB		0x18
#घोषणा MMC_TX_BROADCASTFRAME_G		0x1c
#घोषणा MMC_TX_MULTICASTFRAME_G		0x20
#घोषणा MMC_TX_64_OCTETS_GB		0x24
#घोषणा MMC_TX_65_TO_127_OCTETS_GB	0x28
#घोषणा MMC_TX_128_TO_255_OCTETS_GB	0x2c
#घोषणा MMC_TX_256_TO_511_OCTETS_GB	0x30
#घोषणा MMC_TX_512_TO_1023_OCTETS_GB	0x34
#घोषणा MMC_TX_1024_TO_MAX_OCTETS_GB	0x38
#घोषणा MMC_TX_UNICAST_GB		0x3c
#घोषणा MMC_TX_MULTICAST_GB		0x40
#घोषणा MMC_TX_BROADCAST_GB		0x44
#घोषणा MMC_TX_UNDERFLOW_ERROR		0x48
#घोषणा MMC_TX_SINGLECOL_G		0x4c
#घोषणा MMC_TX_MULTICOL_G		0x50
#घोषणा MMC_TX_DEFERRED			0x54
#घोषणा MMC_TX_LATECOL			0x58
#घोषणा MMC_TX_EXESSCOL			0x5c
#घोषणा MMC_TX_CARRIER_ERROR		0x60
#घोषणा MMC_TX_OCTETCOUNT_G		0x64
#घोषणा MMC_TX_FRAMECOUNT_G		0x68
#घोषणा MMC_TX_EXCESSDEF		0x6c
#घोषणा MMC_TX_PAUSE_FRAME		0x70
#घोषणा MMC_TX_VLAN_FRAME_G		0x74

/* MMC RX counter रेजिस्टरs */
#घोषणा MMC_RX_FRAMECOUNT_GB		0x80
#घोषणा MMC_RX_OCTETCOUNT_GB		0x84
#घोषणा MMC_RX_OCTETCOUNT_G		0x88
#घोषणा MMC_RX_BROADCASTFRAME_G		0x8c
#घोषणा MMC_RX_MULTICASTFRAME_G		0x90
#घोषणा MMC_RX_CRC_ERROR		0x94
#घोषणा MMC_RX_ALIGN_ERROR		0x98
#घोषणा MMC_RX_RUN_ERROR		0x9C
#घोषणा MMC_RX_JABBER_ERROR		0xA0
#घोषणा MMC_RX_UNDERSIZE_G		0xA4
#घोषणा MMC_RX_OVERSIZE_G		0xA8
#घोषणा MMC_RX_64_OCTETS_GB		0xAC
#घोषणा MMC_RX_65_TO_127_OCTETS_GB	0xb0
#घोषणा MMC_RX_128_TO_255_OCTETS_GB	0xb4
#घोषणा MMC_RX_256_TO_511_OCTETS_GB	0xb8
#घोषणा MMC_RX_512_TO_1023_OCTETS_GB	0xbc
#घोषणा MMC_RX_1024_TO_MAX_OCTETS_GB	0xc0
#घोषणा MMC_RX_UNICAST_G		0xc4
#घोषणा MMC_RX_LENGTH_ERROR		0xc8
#घोषणा MMC_RX_AUTOFRANGETYPE		0xcc
#घोषणा MMC_RX_PAUSE_FRAMES		0xd0
#घोषणा MMC_RX_FIFO_OVERFLOW		0xd4
#घोषणा MMC_RX_VLAN_FRAMES_GB		0xd8
#घोषणा MMC_RX_WATCHDOG_ERROR		0xdc
/* IPC*/
#घोषणा MMC_RX_IPC_INTR_MASK		0x100
#घोषणा MMC_RX_IPC_INTR			0x108
/* IPv4*/
#घोषणा MMC_RX_IPV4_GD			0x110
#घोषणा MMC_RX_IPV4_HDERR		0x114
#घोषणा MMC_RX_IPV4_NOPAY		0x118
#घोषणा MMC_RX_IPV4_FRAG		0x11C
#घोषणा MMC_RX_IPV4_UDSBL		0x120

#घोषणा MMC_RX_IPV4_GD_OCTETS		0x150
#घोषणा MMC_RX_IPV4_HDERR_OCTETS	0x154
#घोषणा MMC_RX_IPV4_NOPAY_OCTETS	0x158
#घोषणा MMC_RX_IPV4_FRAG_OCTETS		0x15c
#घोषणा MMC_RX_IPV4_UDSBL_OCTETS	0x160

/* IPV6*/
#घोषणा MMC_RX_IPV6_GD_OCTETS		0x164
#घोषणा MMC_RX_IPV6_HDERR_OCTETS	0x168
#घोषणा MMC_RX_IPV6_NOPAY_OCTETS	0x16c

#घोषणा MMC_RX_IPV6_GD			0x124
#घोषणा MMC_RX_IPV6_HDERR		0x128
#घोषणा MMC_RX_IPV6_NOPAY		0x12c

/* Protocols*/
#घोषणा MMC_RX_UDP_GD			0x130
#घोषणा MMC_RX_UDP_ERR			0x134
#घोषणा MMC_RX_TCP_GD			0x138
#घोषणा MMC_RX_TCP_ERR			0x13c
#घोषणा MMC_RX_ICMP_GD			0x140
#घोषणा MMC_RX_ICMP_ERR			0x144

#घोषणा MMC_RX_UDP_GD_OCTETS		0x170
#घोषणा MMC_RX_UDP_ERR_OCTETS		0x174
#घोषणा MMC_RX_TCP_GD_OCTETS		0x178
#घोषणा MMC_RX_TCP_ERR_OCTETS		0x17c
#घोषणा MMC_RX_ICMP_GD_OCTETS		0x180
#घोषणा MMC_RX_ICMP_ERR_OCTETS		0x184

#घोषणा MMC_TX_FPE_FRAG			0x1a8
#घोषणा MMC_TX_HOLD_REQ			0x1ac
#घोषणा MMC_RX_PKT_ASSEMBLY_ERR		0x1c8
#घोषणा MMC_RX_PKT_SMD_ERR		0x1cc
#घोषणा MMC_RX_PKT_ASSEMBLY_OK		0x1d0
#घोषणा MMC_RX_FPE_FRAG			0x1d4

/* XGMAC MMC Registers */
#घोषणा MMC_XGMAC_TX_OCTET_GB		0x14
#घोषणा MMC_XGMAC_TX_PKT_GB		0x1c
#घोषणा MMC_XGMAC_TX_BROAD_PKT_G	0x24
#घोषणा MMC_XGMAC_TX_MULTI_PKT_G	0x2c
#घोषणा MMC_XGMAC_TX_64OCT_GB		0x34
#घोषणा MMC_XGMAC_TX_65OCT_GB		0x3c
#घोषणा MMC_XGMAC_TX_128OCT_GB		0x44
#घोषणा MMC_XGMAC_TX_256OCT_GB		0x4c
#घोषणा MMC_XGMAC_TX_512OCT_GB		0x54
#घोषणा MMC_XGMAC_TX_1024OCT_GB		0x5c
#घोषणा MMC_XGMAC_TX_UNI_PKT_GB		0x64
#घोषणा MMC_XGMAC_TX_MULTI_PKT_GB	0x6c
#घोषणा MMC_XGMAC_TX_BROAD_PKT_GB	0x74
#घोषणा MMC_XGMAC_TX_UNDER		0x7c
#घोषणा MMC_XGMAC_TX_OCTET_G		0x84
#घोषणा MMC_XGMAC_TX_PKT_G		0x8c
#घोषणा MMC_XGMAC_TX_PAUSE		0x94
#घोषणा MMC_XGMAC_TX_VLAN_PKT_G		0x9c
#घोषणा MMC_XGMAC_TX_LPI_USEC		0xa4
#घोषणा MMC_XGMAC_TX_LPI_TRAN		0xa8

#घोषणा MMC_XGMAC_RX_PKT_GB		0x100
#घोषणा MMC_XGMAC_RX_OCTET_GB		0x108
#घोषणा MMC_XGMAC_RX_OCTET_G		0x110
#घोषणा MMC_XGMAC_RX_BROAD_PKT_G	0x118
#घोषणा MMC_XGMAC_RX_MULTI_PKT_G	0x120
#घोषणा MMC_XGMAC_RX_CRC_ERR		0x128
#घोषणा MMC_XGMAC_RX_RUNT_ERR		0x130
#घोषणा MMC_XGMAC_RX_JABBER_ERR		0x134
#घोषणा MMC_XGMAC_RX_UNDER		0x138
#घोषणा MMC_XGMAC_RX_OVER		0x13c
#घोषणा MMC_XGMAC_RX_64OCT_GB		0x140
#घोषणा MMC_XGMAC_RX_65OCT_GB		0x148
#घोषणा MMC_XGMAC_RX_128OCT_GB		0x150
#घोषणा MMC_XGMAC_RX_256OCT_GB		0x158
#घोषणा MMC_XGMAC_RX_512OCT_GB		0x160
#घोषणा MMC_XGMAC_RX_1024OCT_GB		0x168
#घोषणा MMC_XGMAC_RX_UNI_PKT_G		0x170
#घोषणा MMC_XGMAC_RX_LENGTH_ERR		0x178
#घोषणा MMC_XGMAC_RX_RANGE		0x180
#घोषणा MMC_XGMAC_RX_PAUSE		0x188
#घोषणा MMC_XGMAC_RX_FIFOOVER_PKT	0x190
#घोषणा MMC_XGMAC_RX_VLAN_PKT_GB	0x198
#घोषणा MMC_XGMAC_RX_WATCHDOG_ERR	0x1a0
#घोषणा MMC_XGMAC_RX_LPI_USEC		0x1a4
#घोषणा MMC_XGMAC_RX_LPI_TRAN		0x1a8
#घोषणा MMC_XGMAC_RX_DISCARD_PKT_GB	0x1ac
#घोषणा MMC_XGMAC_RX_DISCARD_OCT_GB	0x1b4
#घोषणा MMC_XGMAC_RX_ALIGN_ERR_PKT	0x1bc

#घोषणा MMC_XGMAC_TX_FPE_FRAG		0x208
#घोषणा MMC_XGMAC_TX_HOLD_REQ		0x20c
#घोषणा MMC_XGMAC_RX_PKT_ASSEMBLY_ERR	0x228
#घोषणा MMC_XGMAC_RX_PKT_SMD_ERR	0x22c
#घोषणा MMC_XGMAC_RX_PKT_ASSEMBLY_OK	0x230
#घोषणा MMC_XGMAC_RX_FPE_FRAG		0x234
#घोषणा MMC_XGMAC_RX_IPC_INTR_MASK	0x25c

अटल व्योम dwmac_mmc_ctrl(व्योम __iomem *mmcaddr, अचिन्हित पूर्णांक mode)
अणु
	u32 value = पढ़ोl(mmcaddr + MMC_CNTRL);

	value |= (mode & 0x3F);

	ग_लिखोl(value, mmcaddr + MMC_CNTRL);

	pr_debug("stmmac: MMC ctrl register (offset 0x%x): 0x%08x\n",
		 MMC_CNTRL, value);
पूर्ण

/* To mask all all पूर्णांकerrupts.*/
अटल व्योम dwmac_mmc_पूर्णांकr_all_mask(व्योम __iomem *mmcaddr)
अणु
	ग_लिखोl(MMC_DEFAULT_MASK, mmcaddr + MMC_RX_INTR_MASK);
	ग_लिखोl(MMC_DEFAULT_MASK, mmcaddr + MMC_TX_INTR_MASK);
	ग_लिखोl(MMC_DEFAULT_MASK, mmcaddr + MMC_RX_IPC_INTR_MASK);
पूर्ण

/* This पढ़ोs the MAC core counters (अगर actaully supported).
 * by शेष the MMC core is programmed to reset each
 * counter after a पढ़ो. So all the field of the mmc काष्ठा
 * have to be incremented.
 */
अटल व्योम dwmac_mmc_पढ़ो(व्योम __iomem *mmcaddr, काष्ठा sपंचांगmac_counters *mmc)
अणु
	mmc->mmc_tx_octetcount_gb += पढ़ोl(mmcaddr + MMC_TX_OCTETCOUNT_GB);
	mmc->mmc_tx_framecount_gb += पढ़ोl(mmcaddr + MMC_TX_FRAMECOUNT_GB);
	mmc->mmc_tx_broadcastframe_g += पढ़ोl(mmcaddr +
					      MMC_TX_BROADCASTFRAME_G);
	mmc->mmc_tx_multicastframe_g += पढ़ोl(mmcaddr +
					      MMC_TX_MULTICASTFRAME_G);
	mmc->mmc_tx_64_octets_gb += पढ़ोl(mmcaddr + MMC_TX_64_OCTETS_GB);
	mmc->mmc_tx_65_to_127_octets_gb +=
	    पढ़ोl(mmcaddr + MMC_TX_65_TO_127_OCTETS_GB);
	mmc->mmc_tx_128_to_255_octets_gb +=
	    पढ़ोl(mmcaddr + MMC_TX_128_TO_255_OCTETS_GB);
	mmc->mmc_tx_256_to_511_octets_gb +=
	    पढ़ोl(mmcaddr + MMC_TX_256_TO_511_OCTETS_GB);
	mmc->mmc_tx_512_to_1023_octets_gb +=
	    पढ़ोl(mmcaddr + MMC_TX_512_TO_1023_OCTETS_GB);
	mmc->mmc_tx_1024_to_max_octets_gb +=
	    पढ़ोl(mmcaddr + MMC_TX_1024_TO_MAX_OCTETS_GB);
	mmc->mmc_tx_unicast_gb += पढ़ोl(mmcaddr + MMC_TX_UNICAST_GB);
	mmc->mmc_tx_multicast_gb += पढ़ोl(mmcaddr + MMC_TX_MULTICAST_GB);
	mmc->mmc_tx_broadcast_gb += पढ़ोl(mmcaddr + MMC_TX_BROADCAST_GB);
	mmc->mmc_tx_underflow_error += पढ़ोl(mmcaddr + MMC_TX_UNDERFLOW_ERROR);
	mmc->mmc_tx_singlecol_g += पढ़ोl(mmcaddr + MMC_TX_SINGLECOL_G);
	mmc->mmc_tx_multicol_g += पढ़ोl(mmcaddr + MMC_TX_MULTICOL_G);
	mmc->mmc_tx_deferred += पढ़ोl(mmcaddr + MMC_TX_DEFERRED);
	mmc->mmc_tx_latecol += पढ़ोl(mmcaddr + MMC_TX_LATECOL);
	mmc->mmc_tx_exesscol += पढ़ोl(mmcaddr + MMC_TX_EXESSCOL);
	mmc->mmc_tx_carrier_error += पढ़ोl(mmcaddr + MMC_TX_CARRIER_ERROR);
	mmc->mmc_tx_octetcount_g += पढ़ोl(mmcaddr + MMC_TX_OCTETCOUNT_G);
	mmc->mmc_tx_framecount_g += पढ़ोl(mmcaddr + MMC_TX_FRAMECOUNT_G);
	mmc->mmc_tx_excessdef += पढ़ोl(mmcaddr + MMC_TX_EXCESSDEF);
	mmc->mmc_tx_छोड़ो_frame += पढ़ोl(mmcaddr + MMC_TX_PAUSE_FRAME);
	mmc->mmc_tx_vlan_frame_g += पढ़ोl(mmcaddr + MMC_TX_VLAN_FRAME_G);

	/* MMC RX counter रेजिस्टरs */
	mmc->mmc_rx_framecount_gb += पढ़ोl(mmcaddr + MMC_RX_FRAMECOUNT_GB);
	mmc->mmc_rx_octetcount_gb += पढ़ोl(mmcaddr + MMC_RX_OCTETCOUNT_GB);
	mmc->mmc_rx_octetcount_g += पढ़ोl(mmcaddr + MMC_RX_OCTETCOUNT_G);
	mmc->mmc_rx_broadcastframe_g += पढ़ोl(mmcaddr +
					      MMC_RX_BROADCASTFRAME_G);
	mmc->mmc_rx_multicastframe_g += पढ़ोl(mmcaddr +
					      MMC_RX_MULTICASTFRAME_G);
	mmc->mmc_rx_crc_error += पढ़ोl(mmcaddr + MMC_RX_CRC_ERROR);
	mmc->mmc_rx_align_error += पढ़ोl(mmcaddr + MMC_RX_ALIGN_ERROR);
	mmc->mmc_rx_run_error += पढ़ोl(mmcaddr + MMC_RX_RUN_ERROR);
	mmc->mmc_rx_jabber_error += पढ़ोl(mmcaddr + MMC_RX_JABBER_ERROR);
	mmc->mmc_rx_undersize_g += पढ़ोl(mmcaddr + MMC_RX_UNDERSIZE_G);
	mmc->mmc_rx_oversize_g += पढ़ोl(mmcaddr + MMC_RX_OVERSIZE_G);
	mmc->mmc_rx_64_octets_gb += पढ़ोl(mmcaddr + MMC_RX_64_OCTETS_GB);
	mmc->mmc_rx_65_to_127_octets_gb +=
	    पढ़ोl(mmcaddr + MMC_RX_65_TO_127_OCTETS_GB);
	mmc->mmc_rx_128_to_255_octets_gb +=
	    पढ़ोl(mmcaddr + MMC_RX_128_TO_255_OCTETS_GB);
	mmc->mmc_rx_256_to_511_octets_gb +=
	    पढ़ोl(mmcaddr + MMC_RX_256_TO_511_OCTETS_GB);
	mmc->mmc_rx_512_to_1023_octets_gb +=
	    पढ़ोl(mmcaddr + MMC_RX_512_TO_1023_OCTETS_GB);
	mmc->mmc_rx_1024_to_max_octets_gb +=
	    पढ़ोl(mmcaddr + MMC_RX_1024_TO_MAX_OCTETS_GB);
	mmc->mmc_rx_unicast_g += पढ़ोl(mmcaddr + MMC_RX_UNICAST_G);
	mmc->mmc_rx_length_error += पढ़ोl(mmcaddr + MMC_RX_LENGTH_ERROR);
	mmc->mmc_rx_स्वतःfrangetype += पढ़ोl(mmcaddr + MMC_RX_AUTOFRANGETYPE);
	mmc->mmc_rx_छोड़ो_frames += पढ़ोl(mmcaddr + MMC_RX_PAUSE_FRAMES);
	mmc->mmc_rx_fअगरo_overflow += पढ़ोl(mmcaddr + MMC_RX_FIFO_OVERFLOW);
	mmc->mmc_rx_vlan_frames_gb += पढ़ोl(mmcaddr + MMC_RX_VLAN_FRAMES_GB);
	mmc->mmc_rx_watchकरोg_error += पढ़ोl(mmcaddr + MMC_RX_WATCHDOG_ERROR);
	/* IPC */
	mmc->mmc_rx_ipc_पूर्णांकr_mask += पढ़ोl(mmcaddr + MMC_RX_IPC_INTR_MASK);
	mmc->mmc_rx_ipc_पूर्णांकr += पढ़ोl(mmcaddr + MMC_RX_IPC_INTR);
	/* IPv4 */
	mmc->mmc_rx_ipv4_gd += पढ़ोl(mmcaddr + MMC_RX_IPV4_GD);
	mmc->mmc_rx_ipv4_hderr += पढ़ोl(mmcaddr + MMC_RX_IPV4_HDERR);
	mmc->mmc_rx_ipv4_nopay += पढ़ोl(mmcaddr + MMC_RX_IPV4_NOPAY);
	mmc->mmc_rx_ipv4_frag += पढ़ोl(mmcaddr + MMC_RX_IPV4_FRAG);
	mmc->mmc_rx_ipv4_udsbl += पढ़ोl(mmcaddr + MMC_RX_IPV4_UDSBL);

	mmc->mmc_rx_ipv4_gd_octets += पढ़ोl(mmcaddr + MMC_RX_IPV4_GD_OCTETS);
	mmc->mmc_rx_ipv4_hderr_octets +=
	    पढ़ोl(mmcaddr + MMC_RX_IPV4_HDERR_OCTETS);
	mmc->mmc_rx_ipv4_nopay_octets +=
	    पढ़ोl(mmcaddr + MMC_RX_IPV4_NOPAY_OCTETS);
	mmc->mmc_rx_ipv4_frag_octets += पढ़ोl(mmcaddr +
					      MMC_RX_IPV4_FRAG_OCTETS);
	mmc->mmc_rx_ipv4_udsbl_octets +=
	    पढ़ोl(mmcaddr + MMC_RX_IPV4_UDSBL_OCTETS);

	/* IPV6 */
	mmc->mmc_rx_ipv6_gd_octets += पढ़ोl(mmcaddr + MMC_RX_IPV6_GD_OCTETS);
	mmc->mmc_rx_ipv6_hderr_octets +=
	    पढ़ोl(mmcaddr + MMC_RX_IPV6_HDERR_OCTETS);
	mmc->mmc_rx_ipv6_nopay_octets +=
	    पढ़ोl(mmcaddr + MMC_RX_IPV6_NOPAY_OCTETS);

	mmc->mmc_rx_ipv6_gd += पढ़ोl(mmcaddr + MMC_RX_IPV6_GD);
	mmc->mmc_rx_ipv6_hderr += पढ़ोl(mmcaddr + MMC_RX_IPV6_HDERR);
	mmc->mmc_rx_ipv6_nopay += पढ़ोl(mmcaddr + MMC_RX_IPV6_NOPAY);

	/* Protocols */
	mmc->mmc_rx_udp_gd += पढ़ोl(mmcaddr + MMC_RX_UDP_GD);
	mmc->mmc_rx_udp_err += पढ़ोl(mmcaddr + MMC_RX_UDP_ERR);
	mmc->mmc_rx_tcp_gd += पढ़ोl(mmcaddr + MMC_RX_TCP_GD);
	mmc->mmc_rx_tcp_err += पढ़ोl(mmcaddr + MMC_RX_TCP_ERR);
	mmc->mmc_rx_icmp_gd += पढ़ोl(mmcaddr + MMC_RX_ICMP_GD);
	mmc->mmc_rx_icmp_err += पढ़ोl(mmcaddr + MMC_RX_ICMP_ERR);

	mmc->mmc_rx_udp_gd_octets += पढ़ोl(mmcaddr + MMC_RX_UDP_GD_OCTETS);
	mmc->mmc_rx_udp_err_octets += पढ़ोl(mmcaddr + MMC_RX_UDP_ERR_OCTETS);
	mmc->mmc_rx_tcp_gd_octets += पढ़ोl(mmcaddr + MMC_RX_TCP_GD_OCTETS);
	mmc->mmc_rx_tcp_err_octets += पढ़ोl(mmcaddr + MMC_RX_TCP_ERR_OCTETS);
	mmc->mmc_rx_icmp_gd_octets += पढ़ोl(mmcaddr + MMC_RX_ICMP_GD_OCTETS);
	mmc->mmc_rx_icmp_err_octets += पढ़ोl(mmcaddr + MMC_RX_ICMP_ERR_OCTETS);

	mmc->mmc_tx_fpe_fragment_cntr += पढ़ोl(mmcaddr + MMC_TX_FPE_FRAG);
	mmc->mmc_tx_hold_req_cntr += पढ़ोl(mmcaddr + MMC_TX_HOLD_REQ);
	mmc->mmc_rx_packet_assembly_err_cntr +=
		पढ़ोl(mmcaddr + MMC_RX_PKT_ASSEMBLY_ERR);
	mmc->mmc_rx_packet_smd_err_cntr += पढ़ोl(mmcaddr + MMC_RX_PKT_SMD_ERR);
	mmc->mmc_rx_packet_assembly_ok_cntr +=
		पढ़ोl(mmcaddr + MMC_RX_PKT_ASSEMBLY_OK);
	mmc->mmc_rx_fpe_fragment_cntr += पढ़ोl(mmcaddr + MMC_RX_FPE_FRAG);
पूर्ण

स्थिर काष्ठा sपंचांगmac_mmc_ops dwmac_mmc_ops = अणु
	.ctrl = dwmac_mmc_ctrl,
	.पूर्णांकr_all_mask = dwmac_mmc_पूर्णांकr_all_mask,
	.पढ़ो = dwmac_mmc_पढ़ो,
पूर्ण;

अटल व्योम dwxgmac_mmc_ctrl(व्योम __iomem *mmcaddr, अचिन्हित पूर्णांक mode)
अणु
	u32 value = पढ़ोl(mmcaddr + MMC_CNTRL);

	value |= (mode & 0x3F);

	ग_लिखोl(value, mmcaddr + MMC_CNTRL);
पूर्ण

अटल व्योम dwxgmac_mmc_पूर्णांकr_all_mask(व्योम __iomem *mmcaddr)
अणु
	ग_लिखोl(0x0, mmcaddr + MMC_RX_INTR_MASK);
	ग_लिखोl(0x0, mmcaddr + MMC_TX_INTR_MASK);
	ग_लिखोl(MMC_DEFAULT_MASK, mmcaddr + MMC_XGMAC_RX_IPC_INTR_MASK);
पूर्ण

अटल व्योम dwxgmac_पढ़ो_mmc_reg(व्योम __iomem *addr, u32 reg, u32 *dest)
अणु
	u64 पंचांगp = 0;

	पंचांगp += पढ़ोl(addr + reg);
	पंचांगp += ((u64 )पढ़ोl(addr + reg + 0x4)) << 32;
	अगर (पंचांगp > GENMASK(31, 0))
		*dest = ~0x0;
	अन्यथा
		*dest = *dest + पंचांगp;
पूर्ण

/* This पढ़ोs the MAC core counters (अगर actaully supported).
 * by शेष the MMC core is programmed to reset each
 * counter after a पढ़ो. So all the field of the mmc काष्ठा
 * have to be incremented.
 */
अटल व्योम dwxgmac_mmc_पढ़ो(व्योम __iomem *mmcaddr, काष्ठा sपंचांगmac_counters *mmc)
अणु
	dwxgmac_पढ़ो_mmc_reg(mmcaddr, MMC_XGMAC_TX_OCTET_GB,
			     &mmc->mmc_tx_octetcount_gb);
	dwxgmac_पढ़ो_mmc_reg(mmcaddr, MMC_XGMAC_TX_PKT_GB,
			     &mmc->mmc_tx_framecount_gb);
	dwxgmac_पढ़ो_mmc_reg(mmcaddr, MMC_XGMAC_TX_BROAD_PKT_G,
			     &mmc->mmc_tx_broadcastframe_g);
	dwxgmac_पढ़ो_mmc_reg(mmcaddr, MMC_XGMAC_TX_MULTI_PKT_G,
			     &mmc->mmc_tx_multicastframe_g);
	dwxgmac_पढ़ो_mmc_reg(mmcaddr, MMC_XGMAC_TX_64OCT_GB,
			     &mmc->mmc_tx_64_octets_gb);
	dwxgmac_पढ़ो_mmc_reg(mmcaddr, MMC_XGMAC_TX_65OCT_GB,
			     &mmc->mmc_tx_65_to_127_octets_gb);
	dwxgmac_पढ़ो_mmc_reg(mmcaddr, MMC_XGMAC_TX_128OCT_GB,
			     &mmc->mmc_tx_128_to_255_octets_gb);
	dwxgmac_पढ़ो_mmc_reg(mmcaddr, MMC_XGMAC_TX_256OCT_GB,
			     &mmc->mmc_tx_256_to_511_octets_gb);
	dwxgmac_पढ़ो_mmc_reg(mmcaddr, MMC_XGMAC_TX_512OCT_GB,
			     &mmc->mmc_tx_512_to_1023_octets_gb);
	dwxgmac_पढ़ो_mmc_reg(mmcaddr, MMC_XGMAC_TX_1024OCT_GB,
			     &mmc->mmc_tx_1024_to_max_octets_gb);
	dwxgmac_पढ़ो_mmc_reg(mmcaddr, MMC_XGMAC_TX_UNI_PKT_GB,
			     &mmc->mmc_tx_unicast_gb);
	dwxgmac_पढ़ो_mmc_reg(mmcaddr, MMC_XGMAC_TX_MULTI_PKT_GB,
			     &mmc->mmc_tx_multicast_gb);
	dwxgmac_पढ़ो_mmc_reg(mmcaddr, MMC_XGMAC_TX_BROAD_PKT_GB,
			     &mmc->mmc_tx_broadcast_gb);
	dwxgmac_पढ़ो_mmc_reg(mmcaddr, MMC_XGMAC_TX_UNDER,
			     &mmc->mmc_tx_underflow_error);
	dwxgmac_पढ़ो_mmc_reg(mmcaddr, MMC_XGMAC_TX_OCTET_G,
			     &mmc->mmc_tx_octetcount_g);
	dwxgmac_पढ़ो_mmc_reg(mmcaddr, MMC_XGMAC_TX_PKT_G,
			     &mmc->mmc_tx_framecount_g);
	dwxgmac_पढ़ो_mmc_reg(mmcaddr, MMC_XGMAC_TX_PAUSE,
			     &mmc->mmc_tx_छोड़ो_frame);
	dwxgmac_पढ़ो_mmc_reg(mmcaddr, MMC_XGMAC_TX_VLAN_PKT_G,
			     &mmc->mmc_tx_vlan_frame_g);

	/* MMC RX counter रेजिस्टरs */
	dwxgmac_पढ़ो_mmc_reg(mmcaddr, MMC_XGMAC_RX_PKT_GB,
			     &mmc->mmc_rx_framecount_gb);
	dwxgmac_पढ़ो_mmc_reg(mmcaddr, MMC_XGMAC_RX_OCTET_GB,
			     &mmc->mmc_rx_octetcount_gb);
	dwxgmac_पढ़ो_mmc_reg(mmcaddr, MMC_XGMAC_RX_OCTET_G,
			     &mmc->mmc_rx_octetcount_g);
	dwxgmac_पढ़ो_mmc_reg(mmcaddr, MMC_XGMAC_RX_BROAD_PKT_G,
			     &mmc->mmc_rx_broadcastframe_g);
	dwxgmac_पढ़ो_mmc_reg(mmcaddr, MMC_XGMAC_RX_MULTI_PKT_G,
			     &mmc->mmc_rx_multicastframe_g);
	dwxgmac_पढ़ो_mmc_reg(mmcaddr, MMC_XGMAC_RX_CRC_ERR,
			     &mmc->mmc_rx_crc_error);
	dwxgmac_पढ़ो_mmc_reg(mmcaddr, MMC_XGMAC_RX_CRC_ERR,
			     &mmc->mmc_rx_crc_error);
	mmc->mmc_rx_run_error += पढ़ोl(mmcaddr + MMC_XGMAC_RX_RUNT_ERR);
	mmc->mmc_rx_jabber_error += पढ़ोl(mmcaddr + MMC_XGMAC_RX_JABBER_ERR);
	mmc->mmc_rx_undersize_g += पढ़ोl(mmcaddr + MMC_XGMAC_RX_UNDER);
	mmc->mmc_rx_oversize_g += पढ़ोl(mmcaddr + MMC_XGMAC_RX_OVER);
	dwxgmac_पढ़ो_mmc_reg(mmcaddr, MMC_XGMAC_RX_64OCT_GB,
			     &mmc->mmc_rx_64_octets_gb);
	dwxgmac_पढ़ो_mmc_reg(mmcaddr, MMC_XGMAC_RX_65OCT_GB,
			     &mmc->mmc_rx_65_to_127_octets_gb);
	dwxgmac_पढ़ो_mmc_reg(mmcaddr, MMC_XGMAC_RX_128OCT_GB,
			     &mmc->mmc_rx_128_to_255_octets_gb);
	dwxgmac_पढ़ो_mmc_reg(mmcaddr, MMC_XGMAC_RX_256OCT_GB,
			     &mmc->mmc_rx_256_to_511_octets_gb);
	dwxgmac_पढ़ो_mmc_reg(mmcaddr, MMC_XGMAC_RX_512OCT_GB,
			     &mmc->mmc_rx_512_to_1023_octets_gb);
	dwxgmac_पढ़ो_mmc_reg(mmcaddr, MMC_XGMAC_RX_1024OCT_GB,
			     &mmc->mmc_rx_1024_to_max_octets_gb);
	dwxgmac_पढ़ो_mmc_reg(mmcaddr, MMC_XGMAC_RX_UNI_PKT_G,
			     &mmc->mmc_rx_unicast_g);
	dwxgmac_पढ़ो_mmc_reg(mmcaddr, MMC_XGMAC_RX_LENGTH_ERR,
			     &mmc->mmc_rx_length_error);
	dwxgmac_पढ़ो_mmc_reg(mmcaddr, MMC_XGMAC_RX_RANGE,
			     &mmc->mmc_rx_स्वतःfrangetype);
	dwxgmac_पढ़ो_mmc_reg(mmcaddr, MMC_XGMAC_RX_PAUSE,
			     &mmc->mmc_rx_छोड़ो_frames);
	dwxgmac_पढ़ो_mmc_reg(mmcaddr, MMC_XGMAC_RX_FIFOOVER_PKT,
			     &mmc->mmc_rx_fअगरo_overflow);
	dwxgmac_पढ़ो_mmc_reg(mmcaddr, MMC_XGMAC_RX_VLAN_PKT_GB,
			     &mmc->mmc_rx_vlan_frames_gb);
	mmc->mmc_rx_watchकरोg_error += पढ़ोl(mmcaddr + MMC_XGMAC_RX_WATCHDOG_ERR);

	mmc->mmc_tx_fpe_fragment_cntr += पढ़ोl(mmcaddr + MMC_XGMAC_TX_FPE_FRAG);
	mmc->mmc_tx_hold_req_cntr += पढ़ोl(mmcaddr + MMC_XGMAC_TX_HOLD_REQ);
	mmc->mmc_rx_packet_assembly_err_cntr +=
		पढ़ोl(mmcaddr + MMC_XGMAC_RX_PKT_ASSEMBLY_ERR);
	mmc->mmc_rx_packet_smd_err_cntr +=
		पढ़ोl(mmcaddr + MMC_XGMAC_RX_PKT_SMD_ERR);
	mmc->mmc_rx_packet_assembly_ok_cntr +=
		पढ़ोl(mmcaddr + MMC_XGMAC_RX_PKT_ASSEMBLY_OK);
	mmc->mmc_rx_fpe_fragment_cntr +=
		पढ़ोl(mmcaddr + MMC_XGMAC_RX_FPE_FRAG);
पूर्ण

स्थिर काष्ठा sपंचांगmac_mmc_ops dwxgmac_mmc_ops = अणु
	.ctrl = dwxgmac_mmc_ctrl,
	.पूर्णांकr_all_mask = dwxgmac_mmc_पूर्णांकr_all_mask,
	.पढ़ो = dwxgmac_mmc_पढ़ो,
पूर्ण;
