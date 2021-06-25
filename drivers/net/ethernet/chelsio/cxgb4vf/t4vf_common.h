<शैली गुरु>
/*
 * This file is part of the Chelsio T4 PCI-E SR-IOV Virtual Function Ethernet
 * driver क्रम Linux.
 *
 * Copyright (c) 2009-2010 Chelsio Communications, Inc. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#अगर_अघोषित __T4VF_COMMON_H__
#घोषणा __T4VF_COMMON_H__

#समावेश "../cxgb4/t4_hw.h"
#समावेश "../cxgb4/t4fw_api.h"

#घोषणा CHELSIO_CHIP_CODE(version, revision) (((version) << 4) | (revision))
#घोषणा CHELSIO_CHIP_VERSION(code) (((code) >> 4) & 0xf)
#घोषणा CHELSIO_CHIP_RELEASE(code) ((code) & 0xf)

/* All T4 and later chips have their PCI-E Device IDs encoded as 0xVFPP where:
 *
 *   V  = "4" क्रम T4; "5" क्रम T5, etc. or
 *      = "a" क्रम T4 FPGA; "b" क्रम T4 FPGA, etc.
 *   F  = "0" क्रम PF 0..3; "4".."7" क्रम PF4..7; and "8" क्रम VFs
 *   PP = adapter product designation
 */
#घोषणा CHELSIO_T4		0x4
#घोषणा CHELSIO_T5		0x5
#घोषणा CHELSIO_T6		0x6

क्रमागत chip_type अणु
	T4_A1 = CHELSIO_CHIP_CODE(CHELSIO_T4, 1),
	T4_A2 = CHELSIO_CHIP_CODE(CHELSIO_T4, 2),
	T4_FIRST_REV	= T4_A1,
	T4_LAST_REV	= T4_A2,

	T5_A0 = CHELSIO_CHIP_CODE(CHELSIO_T5, 0),
	T5_A1 = CHELSIO_CHIP_CODE(CHELSIO_T5, 1),
	T5_FIRST_REV	= T5_A0,
	T5_LAST_REV	= T5_A1,
पूर्ण;

/*
 * The "len16" field of a Firmware Command Structure ...
 */
#घोषणा FW_LEN16(fw_काष्ठा) FW_CMD_LEN16_V(माप(fw_काष्ठा) / 16)

/*
 * Per-VF statistics.
 */
काष्ठा t4vf_port_stats अणु
	/*
	 * TX statistics.
	 */
	u64 tx_bcast_bytes;		/* broadcast */
	u64 tx_bcast_frames;
	u64 tx_mcast_bytes;		/* multicast */
	u64 tx_mcast_frames;
	u64 tx_ucast_bytes;		/* unicast */
	u64 tx_ucast_frames;
	u64 tx_drop_frames;		/* TX dropped frames */
	u64 tx_offload_bytes;		/* offload */
	u64 tx_offload_frames;

	/*
	 * RX statistics.
	 */
	u64 rx_bcast_bytes;		/* broadcast */
	u64 rx_bcast_frames;
	u64 rx_mcast_bytes;		/* multicast */
	u64 rx_mcast_frames;
	u64 rx_ucast_bytes;
	u64 rx_ucast_frames;		/* unicast */

	u64 rx_err_frames;		/* RX error frames */
पूर्ण;

/*
 * Per-"port" (Virtual Interface) link configuration ...
 */
प्रकार u16 fw_port_cap16_t;    /* 16-bit Port Capabilities पूर्णांकegral value */
प्रकार u32 fw_port_cap32_t;    /* 32-bit Port Capabilities पूर्णांकegral value */

क्रमागत fw_caps अणु
	FW_CAPS_UNKNOWN	= 0,	/* 0'ed out initial state */
	FW_CAPS16	= 1,	/* old Firmware: 16-bit Port Capabilities */
	FW_CAPS32	= 2,	/* new Firmware: 32-bit Port Capabilities */
पूर्ण;

क्रमागत cc_छोड़ो अणु
	PAUSE_RX	= 1 << 0,
	PAUSE_TX	= 1 << 1,
	PAUSE_AUTONEG	= 1 << 2
पूर्ण;

क्रमागत cc_fec अणु
	FEC_AUTO	= 1 << 0,	/* IEEE 802.3 "automatic" */
	FEC_RS		= 1 << 1,	/* Reed-Solomon */
	FEC_BASER_RS	= 1 << 2,	/* BaseR/Reed-Solomon */
पूर्ण;

काष्ठा link_config अणु
	fw_port_cap32_t pcaps;		/* link capabilities */
	fw_port_cap32_t	acaps;		/* advertised capabilities */
	fw_port_cap32_t	lpacaps;	/* peer advertised capabilities */

	fw_port_cap32_t	speed_caps;	/* speed(s) user has requested */
	u32		speed;		/* actual link speed */

	क्रमागत cc_छोड़ो	requested_fc;	/* flow control user has requested */
	क्रमागत cc_छोड़ो	fc;		/* actual link flow control */
	क्रमागत cc_छोड़ो   advertised_fc;  /* actual advertised flow control */

	क्रमागत cc_fec	स्वतः_fec;	/* Forward Error Correction: */
	क्रमागत cc_fec	requested_fec;	/*   "automatic" (IEEE 802.3), */
	क्रमागत cc_fec	fec;		/*   requested, and actual in use */

	अचिन्हित अक्षर	स्वतःneg;	/* स्वतःnegotiating? */

	अचिन्हित अक्षर	link_ok;	/* link up? */
	अचिन्हित अक्षर	link_करोwn_rc;	/* link करोwn reason */
पूर्ण;

/* Return true अगर the Link Configuration supports "High Speeds" (those greater
 * than 1Gb/s).
 */
अटल अंतरभूत bool is_x_10g_port(स्थिर काष्ठा link_config *lc)
अणु
	fw_port_cap32_t speeds, high_speeds;

	speeds = FW_PORT_CAP32_SPEED_V(FW_PORT_CAP32_SPEED_G(lc->pcaps));
	high_speeds =
		speeds & ~(FW_PORT_CAP32_SPEED_100M | FW_PORT_CAP32_SPEED_1G);

	वापस high_speeds != 0;
पूर्ण

/*
 * General device parameters ...
 */
काष्ठा dev_params अणु
	u32 fwrev;			/* firmware version */
	u32 tprev;			/* TP Microcode Version */
पूर्ण;

/*
 * Scatter Gather Engine parameters.  These are almost all determined by the
 * Physical Function Driver.  We just need to grab them to see within which
 * environment we're playing ...
 */
काष्ठा sge_params अणु
	u32 sge_control;		/* padding, boundaries, lengths, etc. */
	u32 sge_control2;		/* T5: more of the same */
	u32 sge_host_page_size;		/* PF0-7 page sizes */
	u32 sge_egress_queues_per_page;	/* PF0-7 egress queues/page */
	u32 sge_ingress_queues_per_page;/* PF0-7 ingress queues/page */
	u32 sge_vf_hps;                 /* host page size क्रम our vf */
	u32 sge_vf_eq_qpp;		/* egress queues/page क्रम our VF */
	u32 sge_vf_iq_qpp;		/* ingress queues/page क्रम our VF */
	u32 sge_fl_buffer_size[16];	/* मुक्त list buffer sizes */
	u32 sge_ingress_rx_threshold;	/* RX counter पूर्णांकerrupt threshold[4] */
	u32 sge_congestion_control;     /* congestion thresholds, etc. */
	u32 sge_समयr_value_0_and_1;	/* पूर्णांकerrupt coalescing समयr values */
	u32 sge_समयr_value_2_and_3;
	u32 sge_समयr_value_4_and_5;
पूर्ण;

/*
 * Vital Product Data parameters.
 */
काष्ठा vpd_params अणु
	u32 cclk;			/* Core Clock (KHz) */
पूर्ण;

/* Stores chip specअगरic parameters */
काष्ठा arch_specअगरic_params अणु
	u32 sge_fl_db;
	u16 mps_tcam_size;
पूर्ण;

/*
 * Global Receive Side Scaling (RSS) parameters in host-native क्रमmat.
 */
काष्ठा rss_params अणु
	अचिन्हित पूर्णांक mode;		/* RSS mode */
	जोड़ अणु
	    काष्ठा अणु
		अचिन्हित पूर्णांक synmapen:1;	/* SYN Map Enable */
		अचिन्हित पूर्णांक syn4tupenipv6:1;	/* enable hashing 4-tuple IPv6 SYNs */
		अचिन्हित पूर्णांक syn2tupenipv6:1;	/* enable hashing 2-tuple IPv6 SYNs */
		अचिन्हित पूर्णांक syn4tupenipv4:1;	/* enable hashing 4-tuple IPv4 SYNs */
		अचिन्हित पूर्णांक syn2tupenipv4:1;	/* enable hashing 2-tuple IPv4 SYNs */
		अचिन्हित पूर्णांक ofdmapen:1;	/* Offload Map Enable */
		अचिन्हित पूर्णांक tnlmapen:1;	/* Tunnel Map Enable */
		अचिन्हित पूर्णांक tnlalllookup:1;	/* Tunnel All Lookup */
		अचिन्हित पूर्णांक hashtoeplitz:1;	/* use Toeplitz hash */
	    पूर्ण basicभव;
	पूर्ण u;
पूर्ण;

/*
 * Virtual Interface RSS Configuration in host-native क्रमmat.
 */
जोड़ rss_vi_config अणु
    काष्ठा अणु
	u16 शेषq;			/* Ingress Queue ID क्रम !tnlalllookup */
	अचिन्हित पूर्णांक ip6fourtupen:1;	/* hash 4-tuple IPv6 ingress packets */
	अचिन्हित पूर्णांक ip6twotupen:1;	/* hash 2-tuple IPv6 ingress packets */
	अचिन्हित पूर्णांक ip4fourtupen:1;	/* hash 4-tuple IPv4 ingress packets */
	अचिन्हित पूर्णांक ip4twotupen:1;	/* hash 2-tuple IPv4 ingress packets */
	पूर्णांक udpen;			/* hash 4-tuple UDP ingress packets */
    पूर्ण basicभव;
पूर्ण;

/*
 * Maximum resources provisioned क्रम a PCI VF.
 */
काष्ठा vf_resources अणु
	अचिन्हित पूर्णांक nvi;		/* N भव पूर्णांकerfaces */
	अचिन्हित पूर्णांक neq;		/* N egress Qs */
	अचिन्हित पूर्णांक nethctrl;		/* N egress ETH or CTRL Qs */
	अचिन्हित पूर्णांक niqflपूर्णांक;		/* N ingress Qs/w मुक्त list(s) & पूर्णांकr */
	अचिन्हित पूर्णांक niq;		/* N ingress Qs */
	अचिन्हित पूर्णांक tc;		/* PCI-E traffic class */
	अचिन्हित पूर्णांक pmask;		/* port access rights mask */
	अचिन्हित पूर्णांक nexactf;		/* N exact MPS filters */
	अचिन्हित पूर्णांक r_caps;		/* पढ़ो capabilities */
	अचिन्हित पूर्णांक wx_caps;		/* ग_लिखो/execute capabilities */
पूर्ण;

/*
 * Per-"adapter" (Virtual Function) parameters.
 */
काष्ठा adapter_params अणु
	काष्ठा dev_params dev;		/* general device parameters */
	काष्ठा sge_params sge;		/* Scatter Gather Engine */
	काष्ठा vpd_params vpd;		/* Vital Product Data */
	काष्ठा rss_params rss;		/* Receive Side Scaling */
	काष्ठा vf_resources vfres;	/* Virtual Function Resource limits */
	काष्ठा arch_specअगरic_params arch; /* chip specअगरic params */
	क्रमागत chip_type chip;		/* chip code */
	u8 nports;			/* # of Ethernet "ports" */
	u8 fw_caps_support;		/* 32-bit Port Capabilities */
पूर्ण;

/* Firmware Mailbox Command/Reply log.  All values are in Host-Endian क्रमmat.
 * The access and execute बार are चिन्हित in order to accommodate negative
 * error वापसs.
 */
काष्ठा mbox_cmd अणु
	u64 cmd[MBOX_LEN / 8];		/* a Firmware Mailbox Command/Reply */
	u64 बारtamp;			/* OS-dependent बारtamp */
	u32 seqno;			/* sequence number */
	s16 access;			/* समय (ms) to access mailbox */
	s16 execute;			/* समय (ms) to execute */
पूर्ण;

काष्ठा mbox_cmd_log अणु
	अचिन्हित पूर्णांक size;		/* number of entries in the log */
	अचिन्हित पूर्णांक cursor;		/* next position in the log to ग_लिखो */
	u32 seqno;			/* next sequence number */
	/* variable length mailbox command log starts here */
पूर्ण;

/* Given a poपूर्णांकer to a Firmware Mailbox Command Log and a log entry index,
 * वापस a poपूर्णांकer to the specअगरied entry.
 */
अटल अंतरभूत काष्ठा mbox_cmd *mbox_cmd_log_entry(काष्ठा mbox_cmd_log *log,
						  अचिन्हित पूर्णांक entry_idx)
अणु
	वापस &((काष्ठा mbox_cmd *)&(log)[1])[entry_idx];
पूर्ण

#समावेश "adapter.h"

#अगर_अघोषित PCI_VENDOR_ID_CHELSIO
# define PCI_VENDOR_ID_CHELSIO 0x1425
#पूर्ण_अगर

#घोषणा क्रम_each_port(adapter, iter) \
	क्रम (iter = 0; iter < (adapter)->params.nports; iter++)

अटल अंतरभूत अचिन्हित पूर्णांक core_ticks_per_usec(स्थिर काष्ठा adapter *adapter)
अणु
	वापस adapter->params.vpd.cclk / 1000;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक us_to_core_ticks(स्थिर काष्ठा adapter *adapter,
					    अचिन्हित पूर्णांक us)
अणु
	वापस (us * adapter->params.vpd.cclk) / 1000;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक core_ticks_to_us(स्थिर काष्ठा adapter *adapter,
					    अचिन्हित पूर्णांक ticks)
अणु
	वापस (ticks * 1000) / adapter->params.vpd.cclk;
पूर्ण

पूर्णांक t4vf_wr_mbox_core(काष्ठा adapter *, स्थिर व्योम *, पूर्णांक, व्योम *, bool);

अटल अंतरभूत पूर्णांक t4vf_wr_mbox(काष्ठा adapter *adapter, स्थिर व्योम *cmd,
			       पूर्णांक size, व्योम *rpl)
अणु
	वापस t4vf_wr_mbox_core(adapter, cmd, size, rpl, true);
पूर्ण

अटल अंतरभूत पूर्णांक t4vf_wr_mbox_ns(काष्ठा adapter *adapter, स्थिर व्योम *cmd,
				  पूर्णांक size, व्योम *rpl)
अणु
	वापस t4vf_wr_mbox_core(adapter, cmd, size, rpl, false);
पूर्ण

#घोषणा CHELSIO_PCI_ID_VER(dev_id)  ((dev_id) >> 12)

अटल अंतरभूत पूर्णांक is_t4(क्रमागत chip_type chip)
अणु
	वापस CHELSIO_CHIP_VERSION(chip) == CHELSIO_T4;
पूर्ण

/**
 *	hash_mac_addr - वापस the hash value of a MAC address
 *	@addr: the 48-bit Ethernet MAC address
 *
 *	Hashes a MAC address according to the hash function used by hardware
 *	inexact (hash) address matching.
 */
अटल अंतरभूत पूर्णांक hash_mac_addr(स्थिर u8 *addr)
अणु
	u32 a = ((u32)addr[0] << 16) | ((u32)addr[1] << 8) | addr[2];
	u32 b = ((u32)addr[3] << 16) | ((u32)addr[4] << 8) | addr[5];

	a ^= b;
	a ^= (a >> 12);
	a ^= (a >> 6);
	वापस a & 0x3f;
पूर्ण

पूर्णांक t4vf_रुको_dev_पढ़ोy(काष्ठा adapter *);
पूर्णांक t4vf_port_init(काष्ठा adapter *, पूर्णांक);

पूर्णांक t4vf_fw_reset(काष्ठा adapter *);
पूर्णांक t4vf_set_params(काष्ठा adapter *, अचिन्हित पूर्णांक, स्थिर u32 *, स्थिर u32 *);

पूर्णांक t4vf_fl_pkt_align(काष्ठा adapter *adapter);
क्रमागत t4_bar2_qtype अणु T4_BAR2_QTYPE_EGRESS, T4_BAR2_QTYPE_INGRESS पूर्ण;
पूर्णांक t4vf_bar2_sge_qregs(काष्ठा adapter *adapter,
			अचिन्हित पूर्णांक qid,
			क्रमागत t4_bar2_qtype qtype,
			u64 *pbar2_qoffset,
			अचिन्हित पूर्णांक *pbar2_qid);

अचिन्हित पूर्णांक t4vf_get_pf_from_vf(काष्ठा adapter *);
पूर्णांक t4vf_get_sge_params(काष्ठा adapter *);
पूर्णांक t4vf_get_vpd_params(काष्ठा adapter *);
पूर्णांक t4vf_get_dev_params(काष्ठा adapter *);
पूर्णांक t4vf_get_rss_glb_config(काष्ठा adapter *);
पूर्णांक t4vf_get_vfres(काष्ठा adapter *);

पूर्णांक t4vf_पढ़ो_rss_vi_config(काष्ठा adapter *, अचिन्हित पूर्णांक,
			    जोड़ rss_vi_config *);
पूर्णांक t4vf_ग_लिखो_rss_vi_config(काष्ठा adapter *, अचिन्हित पूर्णांक,
			     जोड़ rss_vi_config *);
पूर्णांक t4vf_config_rss_range(काष्ठा adapter *, अचिन्हित पूर्णांक, पूर्णांक, पूर्णांक,
			  स्थिर u16 *, पूर्णांक);

पूर्णांक t4vf_alloc_vi(काष्ठा adapter *, पूर्णांक);
पूर्णांक t4vf_मुक्त_vi(काष्ठा adapter *, पूर्णांक);
पूर्णांक t4vf_enable_vi(काष्ठा adapter *adapter, अचिन्हित पूर्णांक viid, bool rx_en,
		   bool tx_en);
पूर्णांक t4vf_enable_pi(काष्ठा adapter *adapter, काष्ठा port_info *pi, bool rx_en,
		   bool tx_en);
पूर्णांक t4vf_identअगरy_port(काष्ठा adapter *, अचिन्हित पूर्णांक, अचिन्हित पूर्णांक);

पूर्णांक t4vf_set_rxmode(काष्ठा adapter *, अचिन्हित पूर्णांक, पूर्णांक, पूर्णांक, पूर्णांक, पूर्णांक, पूर्णांक,
		    bool);
पूर्णांक t4vf_alloc_mac_filt(काष्ठा adapter *, अचिन्हित पूर्णांक, bool, अचिन्हित पूर्णांक,
			स्थिर u8 **, u16 *, u64 *, bool);
पूर्णांक t4vf_मुक्त_mac_filt(काष्ठा adapter *, अचिन्हित पूर्णांक, अचिन्हित पूर्णांक naddr,
		       स्थिर u8 **, bool);
पूर्णांक t4vf_change_mac(काष्ठा adapter *, अचिन्हित पूर्णांक, पूर्णांक, स्थिर u8 *, bool);
पूर्णांक t4vf_set_addr_hash(काष्ठा adapter *, अचिन्हित पूर्णांक, bool, u64, bool);
पूर्णांक t4vf_get_port_stats(काष्ठा adapter *, पूर्णांक, काष्ठा t4vf_port_stats *);

पूर्णांक t4vf_iq_मुक्त(काष्ठा adapter *, अचिन्हित पूर्णांक, अचिन्हित पूर्णांक, अचिन्हित पूर्णांक,
		 अचिन्हित पूर्णांक);
पूर्णांक t4vf_eth_eq_मुक्त(काष्ठा adapter *, अचिन्हित पूर्णांक);

पूर्णांक t4vf_update_port_info(काष्ठा port_info *pi);
पूर्णांक t4vf_handle_fw_rpl(काष्ठा adapter *, स्थिर __be64 *);
पूर्णांक t4vf_prep_adapter(काष्ठा adapter *);
पूर्णांक t4vf_get_vf_mac_acl(काष्ठा adapter *adapter, अचिन्हित पूर्णांक port,
			अचिन्हित पूर्णांक *naddr, u8 *addr);
पूर्णांक t4vf_get_vf_vlan_acl(काष्ठा adapter *adapter);

#पूर्ण_अगर /* __T4VF_COMMON_H__ */
