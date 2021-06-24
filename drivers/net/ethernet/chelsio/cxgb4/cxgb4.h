<शैली गुरु>
/*
 * This file is part of the Chelsio T4 Ethernet driver क्रम Linux.
 *
 * Copyright (c) 2003-2016 Chelsio Communications, Inc. All rights reserved.
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

#अगर_अघोषित __CXGB4_H__
#घोषणा __CXGB4_H__

#समावेश "t4_hw.h"

#समावेश <linux/bitops.h>
#समावेश <linux/cache.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/list.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/pci.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/समयr.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/rhashtable.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/net_tstamp.h>
#समावेश <linux/ptp_घड़ी_kernel.h>
#समावेश <linux/ptp_classअगरy.h>
#समावेश <linux/crash_dump.h>
#समावेश <linux/thermal.h>
#समावेश <यंत्र/पन.स>
#समावेश "t4_chip_type.h"
#समावेश "cxgb4_uld.h"
#समावेश "t4fw_api.h"

#घोषणा CH_WARN(adap, fmt, ...) dev_warn(adap->pdev_dev, fmt, ## __VA_ARGS__)
बाह्य काष्ठा list_head adapter_list;
बाह्य काष्ठा list_head uld_list;
बाह्य काष्ठा mutex uld_mutex;

/* Suspend an Ethernet Tx queue with fewer available descriptors than this.
 * This is the same as calc_tx_descs() क्रम a TSO packet with
 * nr_frags == MAX_SKB_FRAGS.
 */
#घोषणा ETHTXQ_STOP_THRES \
	(1 + DIV_ROUND_UP((3 * MAX_SKB_FRAGS) / 2 + (MAX_SKB_FRAGS & 1), 8))

#घोषणा FW_PARAM_DEV(param) \
	(FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_DEV) | \
	 FW_PARAMS_PARAM_X_V(FW_PARAMS_PARAM_DEV_##param))

#घोषणा FW_PARAM_PFVF(param) \
	(FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_PFVF) | \
	 FW_PARAMS_PARAM_X_V(FW_PARAMS_PARAM_PFVF_##param) |  \
	 FW_PARAMS_PARAM_Y_V(0) | \
	 FW_PARAMS_PARAM_Z_V(0))

क्रमागत अणु
	MAX_NPORTS	= 4,     /* max # of ports */
	SERNUM_LEN	= 24,    /* Serial # length */
	EC_LEN		= 16,    /* E/C length */
	ID_LEN		= 16,    /* ID length */
	PN_LEN		= 16,    /* Part Number length */
	MACADDR_LEN	= 12,    /* MAC Address length */
पूर्ण;

क्रमागत अणु
	T4_REGMAP_SIZE = (160 * 1024),
	T5_REGMAP_SIZE = (332 * 1024),
पूर्ण;

क्रमागत अणु
	MEM_EDC0,
	MEM_EDC1,
	MEM_MC,
	MEM_MC0 = MEM_MC,
	MEM_MC1,
	MEM_HMA,
पूर्ण;

क्रमागत अणु
	MEMWIN0_APERTURE = 2048,
	MEMWIN0_BASE     = 0x1b800,
	MEMWIN1_APERTURE = 32768,
	MEMWIN1_BASE     = 0x28000,
	MEMWIN1_BASE_T5  = 0x52000,
	MEMWIN2_APERTURE = 65536,
	MEMWIN2_BASE     = 0x30000,
	MEMWIN2_APERTURE_T5 = 131072,
	MEMWIN2_BASE_T5  = 0x60000,
पूर्ण;

क्रमागत dev_master अणु
	MASTER_CANT,
	MASTER_MAY,
	MASTER_MUST
पूर्ण;

क्रमागत dev_state अणु
	DEV_STATE_UNINIT,
	DEV_STATE_INIT,
	DEV_STATE_ERR
पूर्ण;

क्रमागत cc_छोड़ो अणु
	PAUSE_RX      = 1 << 0,
	PAUSE_TX      = 1 << 1,
	PAUSE_AUTONEG = 1 << 2
पूर्ण;

क्रमागत cc_fec अणु
	FEC_AUTO      = 1 << 0,	 /* IEEE 802.3 "automatic" */
	FEC_RS        = 1 << 1,  /* Reed-Solomon */
	FEC_BASER_RS  = 1 << 2   /* BaseR/Reed-Solomon */
पूर्ण;

क्रमागत अणु
	CXGB4_ETHTOOL_FLASH_FW = 1,
	CXGB4_ETHTOOL_FLASH_PHY = 2,
	CXGB4_ETHTOOL_FLASH_BOOT = 3,
	CXGB4_ETHTOOL_FLASH_BOOTCFG = 4
पूर्ण;

क्रमागत cxgb4_netdev_tls_ops अणु
	CXGB4_TLSDEV_OPS  = 1,
	CXGB4_XFRMDEV_OPS
पूर्ण;

काष्ठा cxgb4_bootcfg_data अणु
	__le16 signature;
	__u8 reserved[2];
पूर्ण;

काष्ठा cxgb4_pcir_data अणु
	__le32 signature;	/* Signature. The string "PCIR" */
	__le16 venकरोr_id;	/* Venकरोr Identअगरication */
	__le16 device_id;	/* Device Identअगरication */
	__u8 vital_product[2];	/* Poपूर्णांकer to Vital Product Data */
	__u8 length[2];		/* PCIR Data Structure Length */
	__u8 revision;		/* PCIR Data Structure Revision */
	__u8 class_code[3];	/* Class Code */
	__u8 image_length[2];	/* Image Length. Multiple of 512B */
	__u8 code_revision[2];	/* Revision Level of Code/Data */
	__u8 code_type;
	__u8 indicator;
	__u8 reserved[2];
पूर्ण;

/* BIOS boot headers */
काष्ठा cxgb4_pci_exp_rom_header अणु
	__le16 signature;	/* ROM Signature. Should be 0xaa55 */
	__u8 reserved[22];	/* Reserved per processor Architecture data */
	__le16 pcir_offset;	/* Offset to PCI Data Structure */
पूर्ण;

/* Legacy PCI Expansion ROM Header */
काष्ठा legacy_pci_rom_hdr अणु
	__u8 signature[2];	/* ROM Signature. Should be 0xaa55 */
	__u8 size512;		/* Current Image Size in units of 512 bytes */
	__u8 initentry_poपूर्णांक[4];
	__u8 cksum;		/* Checksum computed on the entire Image */
	__u8 reserved[16];	/* Reserved */
	__le16 pcir_offset;	/* Offset to PCI Data Struture */
पूर्ण;

#घोषणा CXGB4_HDR_CODE1 0x00
#घोषणा CXGB4_HDR_CODE2 0x03
#घोषणा CXGB4_HDR_INDI 0x80

/* BOOT स्थिरants */
क्रमागत अणु
	BOOT_CFG_SIG = 0x4243,
	BOOT_SIZE_INC = 512,
	BOOT_SIGNATURE = 0xaa55,
	BOOT_MIN_SIZE = माप(काष्ठा cxgb4_pci_exp_rom_header),
	BOOT_MAX_SIZE = 1024 * BOOT_SIZE_INC,
	PCIR_SIGNATURE = 0x52494350
पूर्ण;

काष्ठा port_stats अणु
	u64 tx_octets;            /* total # of octets in good frames */
	u64 tx_frames;            /* all good frames */
	u64 tx_bcast_frames;      /* all broadcast frames */
	u64 tx_mcast_frames;      /* all multicast frames */
	u64 tx_ucast_frames;      /* all unicast frames */
	u64 tx_error_frames;      /* all error frames */

	u64 tx_frames_64;         /* # of Tx frames in a particular range */
	u64 tx_frames_65_127;
	u64 tx_frames_128_255;
	u64 tx_frames_256_511;
	u64 tx_frames_512_1023;
	u64 tx_frames_1024_1518;
	u64 tx_frames_1519_max;

	u64 tx_drop;              /* # of dropped Tx frames */
	u64 tx_छोड़ो;             /* # of transmitted छोड़ो frames */
	u64 tx_ppp0;              /* # of transmitted PPP prio 0 frames */
	u64 tx_ppp1;              /* # of transmitted PPP prio 1 frames */
	u64 tx_ppp2;              /* # of transmitted PPP prio 2 frames */
	u64 tx_ppp3;              /* # of transmitted PPP prio 3 frames */
	u64 tx_ppp4;              /* # of transmitted PPP prio 4 frames */
	u64 tx_ppp5;              /* # of transmitted PPP prio 5 frames */
	u64 tx_ppp6;              /* # of transmitted PPP prio 6 frames */
	u64 tx_ppp7;              /* # of transmitted PPP prio 7 frames */

	u64 rx_octets;            /* total # of octets in good frames */
	u64 rx_frames;            /* all good frames */
	u64 rx_bcast_frames;      /* all broadcast frames */
	u64 rx_mcast_frames;      /* all multicast frames */
	u64 rx_ucast_frames;      /* all unicast frames */
	u64 rx_too_दीर्घ;          /* # of frames exceeding MTU */
	u64 rx_jabber;            /* # of jabber frames */
	u64 rx_fcs_err;           /* # of received frames with bad FCS */
	u64 rx_len_err;           /* # of received frames with length error */
	u64 rx_symbol_err;        /* symbol errors */
	u64 rx_runt;              /* # of लघु frames */

	u64 rx_frames_64;         /* # of Rx frames in a particular range */
	u64 rx_frames_65_127;
	u64 rx_frames_128_255;
	u64 rx_frames_256_511;
	u64 rx_frames_512_1023;
	u64 rx_frames_1024_1518;
	u64 rx_frames_1519_max;

	u64 rx_छोड़ो;             /* # of received छोड़ो frames */
	u64 rx_ppp0;              /* # of received PPP prio 0 frames */
	u64 rx_ppp1;              /* # of received PPP prio 1 frames */
	u64 rx_ppp2;              /* # of received PPP prio 2 frames */
	u64 rx_ppp3;              /* # of received PPP prio 3 frames */
	u64 rx_ppp4;              /* # of received PPP prio 4 frames */
	u64 rx_ppp5;              /* # of received PPP prio 5 frames */
	u64 rx_ppp6;              /* # of received PPP prio 6 frames */
	u64 rx_ppp7;              /* # of received PPP prio 7 frames */

	u64 rx_ovflow0;           /* drops due to buffer-group 0 overflows */
	u64 rx_ovflow1;           /* drops due to buffer-group 1 overflows */
	u64 rx_ovflow2;           /* drops due to buffer-group 2 overflows */
	u64 rx_ovflow3;           /* drops due to buffer-group 3 overflows */
	u64 rx_trunc0;            /* buffer-group 0 truncated packets */
	u64 rx_trunc1;            /* buffer-group 1 truncated packets */
	u64 rx_trunc2;            /* buffer-group 2 truncated packets */
	u64 rx_trunc3;            /* buffer-group 3 truncated packets */
पूर्ण;

काष्ठा lb_port_stats अणु
	u64 octets;
	u64 frames;
	u64 bcast_frames;
	u64 mcast_frames;
	u64 ucast_frames;
	u64 error_frames;

	u64 frames_64;
	u64 frames_65_127;
	u64 frames_128_255;
	u64 frames_256_511;
	u64 frames_512_1023;
	u64 frames_1024_1518;
	u64 frames_1519_max;

	u64 drop;

	u64 ovflow0;
	u64 ovflow1;
	u64 ovflow2;
	u64 ovflow3;
	u64 trunc0;
	u64 trunc1;
	u64 trunc2;
	u64 trunc3;
पूर्ण;

काष्ठा tp_tcp_stats अणु
	u32 tcp_out_rsts;
	u64 tcp_in_segs;
	u64 tcp_out_segs;
	u64 tcp_retrans_segs;
पूर्ण;

काष्ठा tp_usm_stats अणु
	u32 frames;
	u32 drops;
	u64 octets;
पूर्ण;

काष्ठा tp_fcoe_stats अणु
	u32 frames_ddp;
	u32 frames_drop;
	u64 octets_ddp;
पूर्ण;

काष्ठा tp_err_stats अणु
	u32 mac_in_errs[4];
	u32 hdr_in_errs[4];
	u32 tcp_in_errs[4];
	u32 tnl_cong_drops[4];
	u32 ofld_chan_drops[4];
	u32 tnl_tx_drops[4];
	u32 ofld_vlan_drops[4];
	u32 tcp6_in_errs[4];
	u32 ofld_no_neigh;
	u32 ofld_cong_defer;
पूर्ण;

काष्ठा tp_cpl_stats अणु
	u32 req[4];
	u32 rsp[4];
पूर्ण;

काष्ठा tp_rdma_stats अणु
	u32 rqe_dfr_pkt;
	u32 rqe_dfr_mod;
पूर्ण;

काष्ठा sge_params अणु
	u32 hps;			/* host page size क्रम our PF/VF */
	u32 eq_qpp;			/* egress queues/page क्रम our PF/VF */
	u32 iq_qpp;			/* egress queues/page क्रम our PF/VF */
पूर्ण;

काष्ठा tp_params अणु
	अचिन्हित पूर्णांक tre;            /* log2 of core घड़ीs per TP tick */
	अचिन्हित पूर्णांक la_mask;        /* what events are recorded by TP LA */
	अचिन्हित लघु tx_modq_map;  /* TX modulation scheduler queue to */
				     /* channel map */

	uपूर्णांक32_t dack_re;            /* DACK समयr resolution */
	अचिन्हित लघु tx_modq[NCHAN];	/* channel to modulation queue map */

	u32 vlan_pri_map;               /* cached TP_VLAN_PRI_MAP */
	u32 filter_mask;
	u32 ingress_config;             /* cached TP_INGRESS_CONFIG */

	/* cached TP_OUT_CONFIG compressed error vector
	 * and passing outer header info क्रम encapsulated packets.
	 */
	पूर्णांक rx_pkt_encap;

	/* TP_VLAN_PRI_MAP Compressed Filter Tuple field offsets.  This is a
	 * subset of the set of fields which may be present in the Compressed
	 * Filter Tuple portion of filters and TCP TCB connections.  The
	 * fields which are present are controlled by the TP_VLAN_PRI_MAP.
	 * Since a variable number of fields may or may not be present, their
	 * shअगरted field positions within the Compressed Filter Tuple may
	 * vary, or not even be present अगर the field isn't selected in
	 * TP_VLAN_PRI_MAP.  Since some of these fields are needed in various
	 * places we store their offsets here, or a -1 अगर the field isn't
	 * present.
	 */
	पूर्णांक fcoe_shअगरt;
	पूर्णांक port_shअगरt;
	पूर्णांक vnic_shअगरt;
	पूर्णांक vlan_shअगरt;
	पूर्णांक tos_shअगरt;
	पूर्णांक protocol_shअगरt;
	पूर्णांक ethertype_shअगरt;
	पूर्णांक macmatch_shअगरt;
	पूर्णांक matchtype_shअगरt;
	पूर्णांक frag_shअगरt;

	u64 hash_filter_mask;
पूर्ण;

काष्ठा vpd_params अणु
	अचिन्हित पूर्णांक cclk;
	u8 ec[EC_LEN + 1];
	u8 sn[SERNUM_LEN + 1];
	u8 id[ID_LEN + 1];
	u8 pn[PN_LEN + 1];
	u8 na[MACADDR_LEN + 1];
पूर्ण;

/* Maximum resources provisioned क्रम a PCI PF.
 */
काष्ठा pf_resources अणु
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

काष्ठा pci_params अणु
	अचिन्हित अक्षर speed;
	अचिन्हित अक्षर width;
पूर्ण;

काष्ठा devlog_params अणु
	u32 memtype;                    /* which memory (EDC0, EDC1, MC) */
	u32 start;                      /* start of log in firmware memory */
	u32 size;                       /* size of log */
पूर्ण;

/* Stores chip specअगरic parameters */
काष्ठा arch_specअगरic_params अणु
	u8 nchan;
	u8 pm_stats_cnt;
	u8 cng_ch_bits_log;		/* congestion channel map bits width */
	u16 mps_rplc_size;
	u16 vfcount;
	u32 sge_fl_db;
	u16 mps_tcam_size;
पूर्ण;

काष्ठा adapter_params अणु
	काष्ठा sge_params sge;
	काष्ठा tp_params  tp;
	काष्ठा vpd_params vpd;
	काष्ठा pf_resources pfres;
	काष्ठा pci_params pci;
	काष्ठा devlog_params devlog;
	क्रमागत pcie_memwin drv_memwin;

	अचिन्हित पूर्णांक cim_la_size;

	अचिन्हित पूर्णांक sf_size;             /* serial flash size in bytes */
	अचिन्हित पूर्णांक sf_nsec;             /* # of flash sectors */

	अचिन्हित पूर्णांक fw_vers;		  /* firmware version */
	अचिन्हित पूर्णांक bs_vers;		  /* bootstrap version */
	अचिन्हित पूर्णांक tp_vers;		  /* TP microcode version */
	अचिन्हित पूर्णांक er_vers;		  /* expansion ROM version */
	अचिन्हित पूर्णांक scfg_vers;		  /* Serial Configuration version */
	अचिन्हित पूर्णांक vpd_vers;		  /* VPD Version */
	u8 api_vers[7];

	अचिन्हित लघु mtus[NMTUS];
	अचिन्हित लघु a_wnd[NCCTRL_WIN];
	अचिन्हित लघु b_wnd[NCCTRL_WIN];

	अचिन्हित अक्षर nports;             /* # of ethernet ports */
	अचिन्हित अक्षर portvec;
	क्रमागत chip_type chip;               /* chip code */
	काष्ठा arch_specअगरic_params arch;  /* chip specअगरic params */
	अचिन्हित अक्षर offload;
	अचिन्हित अक्षर crypto;		/* HW capability क्रम crypto */
	अचिन्हित अक्षर ethofld;		/* QoS support */

	अचिन्हित अक्षर bypass;
	अचिन्हित अक्षर hash_filter;

	अचिन्हित पूर्णांक ofldq_wr_cred;
	bool ulptx_memग_लिखो_dsgl;          /* use of T5 DSGL allowed */

	अचिन्हित पूर्णांक nsched_cls;          /* number of traffic classes */
	अचिन्हित पूर्णांक max_ordird_qp;       /* Max पढ़ो depth per RDMA QP */
	अचिन्हित पूर्णांक max_ird_adapter;     /* Max पढ़ो depth per adapter */
	bool fr_nsmr_tpte_wr_support;	  /* FW support क्रम FR_NSMR_TPTE_WR */
	u8 fw_caps_support;		/* 32-bit Port Capabilities */
	bool filter2_wr_support;	/* FW support क्रम FILTER2_WR */
	अचिन्हित पूर्णांक viid_smt_extn_support:1; /* FW वापसs vin and smt index */

	/* MPS Buffer Group Map[per Port].  Bit i is set अगर buffer group i is
	 * used by the Port
	 */
	u8 mps_bg_map[MAX_NPORTS];	/* MPS Buffer Group Map */
	bool ग_लिखो_w_imm_support;       /* FW supports WRITE_WITH_IMMEDIATE */
	bool ग_लिखो_cmpl_support;        /* FW supports WRITE_CMPL */
पूर्ण;

/* State needed to monitor the क्रमward progress of SGE Ingress DMA activities
 * and possible hangs.
 */
काष्ठा sge_idma_monitor_state अणु
	अचिन्हित पूर्णांक idma_1s_thresh;	/* 1s threshold in Core Clock ticks */
	अचिन्हित पूर्णांक idma_stalled[2];	/* synthesized stalled समयrs in HZ */
	अचिन्हित पूर्णांक idma_state[2];	/* IDMA Hang detect state */
	अचिन्हित पूर्णांक idma_qid[2];	/* IDMA Hung Ingress Queue ID */
	अचिन्हित पूर्णांक idma_warn[2];	/* समय to warning in HZ */
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

#घोषणा FW_VERSION(chip) ( \
		FW_HDR_FW_VER_MAJOR_G(chip##FW_VERSION_MAJOR) | \
		FW_HDR_FW_VER_MINOR_G(chip##FW_VERSION_MINOR) | \
		FW_HDR_FW_VER_MICRO_G(chip##FW_VERSION_MICRO) | \
		FW_HDR_FW_VER_BUILD_G(chip##FW_VERSION_BUILD))
#घोषणा FW_INTFVER(chip, पूर्णांकf) (FW_HDR_INTFVER_##पूर्णांकf)

काष्ठा cxgb4_ethtool_lb_test अणु
	काष्ठा completion completion;
	पूर्णांक result;
	पूर्णांक loopback;
पूर्ण;

काष्ठा fw_info अणु
	u8 chip;
	अक्षर *fs_name;
	अक्षर *fw_mod_name;
	काष्ठा fw_hdr fw_hdr;
पूर्ण;

काष्ठा trace_params अणु
	u32 data[TRACE_LEN / 4];
	u32 mask[TRACE_LEN / 4];
	अचिन्हित लघु snap_len;
	अचिन्हित लघु min_len;
	अचिन्हित अक्षर skip_ofst;
	अचिन्हित अक्षर skip_len;
	अचिन्हित अक्षर invert;
	अचिन्हित अक्षर port;
पूर्ण;

काष्ठा cxgb4_fw_data अणु
	__be32 signature;
	__u8 reserved[4];
पूर्ण;

/* Firmware Port Capabilities types. */

प्रकार u16 fw_port_cap16_t;	/* 16-bit Port Capabilities पूर्णांकegral value */
प्रकार u32 fw_port_cap32_t;	/* 32-bit Port Capabilities पूर्णांकegral value */

क्रमागत fw_caps अणु
	FW_CAPS_UNKNOWN	= 0,	/* 0'ed out initial state */
	FW_CAPS16	= 1,	/* old Firmware: 16-bit Port Capabilities */
	FW_CAPS32	= 2,	/* new Firmware: 32-bit Port Capabilities */
पूर्ण;

काष्ठा link_config अणु
	fw_port_cap32_t pcaps;           /* link capabilities */
	fw_port_cap32_t def_acaps;       /* शेष advertised capabilities */
	fw_port_cap32_t acaps;           /* advertised capabilities */
	fw_port_cap32_t lpacaps;         /* peer advertised capabilities */

	fw_port_cap32_t speed_caps;      /* speed(s) user has requested */
	अचिन्हित पूर्णांक   speed;            /* actual link speed (Mb/s) */

	क्रमागत cc_छोड़ो  requested_fc;     /* flow control user has requested */
	क्रमागत cc_छोड़ो  fc;               /* actual link flow control */
	क्रमागत cc_छोड़ो  advertised_fc;    /* actual advertised flow control */

	क्रमागत cc_fec    requested_fec;	 /* Forward Error Correction: */
	क्रमागत cc_fec    fec;		 /* requested and actual in use */

	अचिन्हित अक्षर  स्वतःneg;          /* स्वतःnegotiating? */

	अचिन्हित अक्षर  link_ok;          /* link up? */
	अचिन्हित अक्षर  link_करोwn_rc;     /* link करोwn reason */

	bool new_module;		 /* ->OS Transceiver Module inserted */
	bool reकरो_l1cfg;		 /* ->CC reकरो current "sticky" L1 CFG */
पूर्ण;

#घोषणा FW_LEN16(fw_काष्ठा) FW_CMD_LEN16_V(माप(fw_काष्ठा) / 16)

क्रमागत अणु
	MAX_ETH_QSETS = 32,           /* # of Ethernet Tx/Rx queue sets */
	MAX_OFLD_QSETS = 16,          /* # of offload Tx, iscsi Rx queue sets */
	MAX_CTRL_QUEUES = NCHAN,      /* # of control Tx queues */
पूर्ण;

क्रमागत अणु
	MAX_TXQ_ENTRIES      = 16384,
	MAX_CTRL_TXQ_ENTRIES = 1024,
	MAX_RSPQ_ENTRIES     = 16384,
	MAX_RX_BUFFERS       = 16384,
	MIN_TXQ_ENTRIES      = 32,
	MIN_CTRL_TXQ_ENTRIES = 32,
	MIN_RSPQ_ENTRIES     = 128,
	MIN_FL_ENTRIES       = 16
पूर्ण;

क्रमागत अणु
	MAX_TXQ_DESC_SIZE      = 64,
	MAX_RXQ_DESC_SIZE      = 128,
	MAX_FL_DESC_SIZE       = 8,
	MAX_CTRL_TXQ_DESC_SIZE = 64,
पूर्ण;

क्रमागत अणु
	INGQ_EXTRAS = 2,        /* firmware event queue and */
				/*   क्रमwarded पूर्णांकerrupts */
	MAX_INGQ = MAX_ETH_QSETS + INGQ_EXTRAS,
पूर्ण;

क्रमागत अणु
	PRIV_FLAG_PORT_TX_VM_BIT,
पूर्ण;

#घोषणा PRIV_FLAG_PORT_TX_VM		BIT(PRIV_FLAG_PORT_TX_VM_BIT)

#घोषणा PRIV_FLAGS_ADAP			0
#घोषणा PRIV_FLAGS_PORT			PRIV_FLAG_PORT_TX_VM

काष्ठा adapter;
काष्ठा sge_rspq;

#समावेश "cxgb4_dcb.h"

#अगर_घोषित CONFIG_CHELSIO_T4_FCOE
#समावेश "cxgb4_fcoe.h"
#पूर्ण_अगर /* CONFIG_CHELSIO_T4_FCOE */

काष्ठा port_info अणु
	काष्ठा adapter *adapter;
	u16    viid;
	पूर्णांक    xact_addr_filt;        /* index of exact MAC address filter */
	u16    rss_size;              /* size of VI's RSS table slice */
	s8     mdio_addr;
	क्रमागत fw_port_type port_type;
	u8     mod_type;
	u8     port_id;
	u8     tx_chan;
	u8     lport;                 /* associated offload logical port */
	u8     nqsets;                /* # of qsets */
	u8     first_qset;            /* index of first qset */
	u8     rss_mode;
	काष्ठा link_config link_cfg;
	u16   *rss;
	काष्ठा port_stats stats_base;
#अगर_घोषित CONFIG_CHELSIO_T4_DCB
	काष्ठा port_dcb_info dcb;     /* Data Center Bridging support */
#पूर्ण_अगर
#अगर_घोषित CONFIG_CHELSIO_T4_FCOE
	काष्ठा cxgb_fcoe fcoe;
#पूर्ण_अगर /* CONFIG_CHELSIO_T4_FCOE */
	bool rxtstamp;  /* Enable TS */
	काष्ठा hwtstamp_config tstamp_config;
	bool ptp_enable;
	काष्ठा sched_table *sched_tbl;
	u32 eth_flags;

	/* viid and smt fields either वापसed by fw
	 * or decoded by parsing viid by driver.
	 */
	u8 vin;
	u8 vivld;
	u8 smt_idx;
	u8 rx_cchan;

	bool tc_block_shared;

	/* Mirror VI inक्रमmation */
	u16 viid_mirror;
	u16 nmirrorqsets;
	u32 vi_mirror_count;
	काष्ठा mutex vi_mirror_mutex; /* Sync access to Mirror VI info */
	काष्ठा cxgb4_ethtool_lb_test ethtool_lb;
पूर्ण;

काष्ठा dentry;
काष्ठा work_काष्ठा;

क्रमागत अणु                                 /* adapter flags */
	CXGB4_FULL_INIT_DONE		= (1 << 0),
	CXGB4_DEV_ENABLED		= (1 << 1),
	CXGB4_USING_MSI			= (1 << 2),
	CXGB4_USING_MSIX		= (1 << 3),
	CXGB4_FW_OK			= (1 << 4),
	CXGB4_RSS_TNLALLLOOKUP		= (1 << 5),
	CXGB4_USING_SOFT_PARAMS		= (1 << 6),
	CXGB4_MASTER_PF			= (1 << 7),
	CXGB4_FW_OFLD_CONN		= (1 << 9),
	CXGB4_ROOT_NO_RELAXED_ORDERING	= (1 << 10),
	CXGB4_SHUTTING_DOWN		= (1 << 11),
	CXGB4_SGE_DBQ_TIMER		= (1 << 12),
पूर्ण;

क्रमागत अणु
	ULP_CRYPTO_LOOKASIDE = 1 << 0,
	ULP_CRYPTO_IPSEC_INLINE = 1 << 1,
	ULP_CRYPTO_KTLS_INLINE  = 1 << 3,
पूर्ण;

#घोषणा CXGB4_MIRROR_RXQ_DEFAULT_DESC_NUM 1024
#घोषणा CXGB4_MIRROR_RXQ_DEFAULT_DESC_SIZE 64
#घोषणा CXGB4_MIRROR_RXQ_DEFAULT_INTR_USEC 5
#घोषणा CXGB4_MIRROR_RXQ_DEFAULT_PKT_CNT 8

#घोषणा CXGB4_MIRROR_FLQ_DEFAULT_DESC_NUM 72

काष्ठा rx_sw_desc;

काष्ठा sge_fl अणु                     /* SGE मुक्त-buffer queue state */
	अचिन्हित पूर्णांक avail;         /* # of available Rx buffers */
	अचिन्हित पूर्णांक pend_cred;     /* new buffers since last FL DB ring */
	अचिन्हित पूर्णांक cidx;          /* consumer index */
	अचिन्हित पूर्णांक pidx;          /* producer index */
	अचिन्हित दीर्घ alloc_failed; /* # of बार buffer allocation failed */
	अचिन्हित दीर्घ large_alloc_failed;
	अचिन्हित दीर्घ mapping_err;  /* # of RX Buffer DMA Mapping failures */
	अचिन्हित दीर्घ low;          /* # of बार momentarily starving */
	अचिन्हित दीर्घ starving;
	/* RO fields */
	अचिन्हित पूर्णांक cntxt_id;      /* SGE context id क्रम the मुक्त list */
	अचिन्हित पूर्णांक size;          /* capacity of मुक्त list */
	काष्ठा rx_sw_desc *sdesc;   /* address of SW Rx descriptor ring */
	__be64 *desc;               /* address of HW Rx descriptor ring */
	dma_addr_t addr;            /* bus address of HW ring start */
	व्योम __iomem *bar2_addr;    /* address of BAR2 Queue रेजिस्टरs */
	अचिन्हित पूर्णांक bar2_qid;      /* Queue ID क्रम BAR2 Queue रेजिस्टरs */
पूर्ण;

/* A packet gather list */
काष्ठा pkt_gl अणु
	u64 sमाला_लोtamp;		    /* SGE Time Stamp क्रम Ingress Packet */
	काष्ठा page_frag frags[MAX_SKB_FRAGS];
	व्योम *va;                         /* भव address of first byte */
	अचिन्हित पूर्णांक nfrags;              /* # of fragments */
	अचिन्हित पूर्णांक tot_len;             /* total length of fragments */
पूर्ण;

प्रकार पूर्णांक (*rspq_handler_t)(काष्ठा sge_rspq *q, स्थिर __be64 *rsp,
			      स्थिर काष्ठा pkt_gl *gl);
प्रकार व्योम (*rspq_flush_handler_t)(काष्ठा sge_rspq *q);
/* LRO related declarations क्रम ULD */
काष्ठा t4_lro_mgr अणु
#घोषणा MAX_LRO_SESSIONS		64
	u8 lro_session_cnt;         /* # of sessions to aggregate */
	अचिन्हित दीर्घ lro_pkts;     /* # of LRO super packets */
	अचिन्हित दीर्घ lro_merged;   /* # of wire packets merged by LRO */
	काष्ठा sk_buff_head lroq;   /* list of aggregated sessions */
पूर्ण;

काष्ठा sge_rspq अणु                   /* state क्रम an SGE response queue */
	काष्ठा napi_काष्ठा napi;
	स्थिर __be64 *cur_desc;     /* current descriptor in queue */
	अचिन्हित पूर्णांक cidx;          /* consumer index */
	u8 gen;                     /* current generation bit */
	u8 पूर्णांकr_params;             /* पूर्णांकerrupt holकरोff parameters */
	u8 next_पूर्णांकr_params;        /* holकरोff params क्रम next पूर्णांकerrupt */
	u8 adaptive_rx;
	u8 pktcnt_idx;              /* पूर्णांकerrupt packet threshold */
	u8 uld;                     /* ULD handling this queue */
	u8 idx;                     /* queue index within its group */
	पूर्णांक offset;                 /* offset पूर्णांकo current Rx buffer */
	u16 cntxt_id;               /* SGE context id क्रम the response q */
	u16 असल_id;                 /* असलolute SGE id क्रम the response q */
	__be64 *desc;               /* address of HW response ring */
	dma_addr_t phys_addr;       /* physical address of the ring */
	व्योम __iomem *bar2_addr;    /* address of BAR2 Queue रेजिस्टरs */
	अचिन्हित पूर्णांक bar2_qid;      /* Queue ID क्रम BAR2 Queue रेजिस्टरs */
	अचिन्हित पूर्णांक iqe_len;       /* entry size */
	अचिन्हित पूर्णांक size;          /* capacity of response queue */
	काष्ठा adapter *adap;
	काष्ठा net_device *netdev;  /* associated net device */
	rspq_handler_t handler;
	rspq_flush_handler_t flush_handler;
	काष्ठा t4_lro_mgr lro_mgr;
पूर्ण;

काष्ठा sge_eth_stats अणु              /* Ethernet queue statistics */
	अचिन्हित दीर्घ pkts;         /* # of ethernet packets */
	अचिन्हित दीर्घ lro_pkts;     /* # of LRO super packets */
	अचिन्हित दीर्घ lro_merged;   /* # of wire packets merged by LRO */
	अचिन्हित दीर्घ rx_cso;       /* # of Rx checksum offloads */
	अचिन्हित दीर्घ vlan_ex;      /* # of Rx VLAN extractions */
	अचिन्हित दीर्घ rx_drops;     /* # of packets dropped due to no mem */
	अचिन्हित दीर्घ bad_rx_pkts;  /* # of packets with err_vec!=0 */
पूर्ण;

काष्ठा sge_eth_rxq अणु                /* SW Ethernet Rx queue */
	काष्ठा sge_rspq rspq;
	काष्ठा sge_fl fl;
	काष्ठा sge_eth_stats stats;
	काष्ठा msix_info *msix;
पूर्ण ____cacheline_aligned_in_smp;

काष्ठा sge_ofld_stats अणु             /* offload queue statistics */
	अचिन्हित दीर्घ pkts;         /* # of packets */
	अचिन्हित दीर्घ imm;          /* # of immediate-data packets */
	अचिन्हित दीर्घ an;           /* # of asynchronous notअगरications */
	अचिन्हित दीर्घ nomem;        /* # of responses deferred due to no mem */
पूर्ण;

काष्ठा sge_ofld_rxq अणु               /* SW offload Rx queue */
	काष्ठा sge_rspq rspq;
	काष्ठा sge_fl fl;
	काष्ठा sge_ofld_stats stats;
	काष्ठा msix_info *msix;
पूर्ण ____cacheline_aligned_in_smp;

काष्ठा tx_desc अणु
	__be64 flit[8];
पूर्ण;

काष्ठा ulptx_sgl;

काष्ठा tx_sw_desc अणु
	काष्ठा sk_buff *skb; /* SKB to मुक्त after getting completion */
	dma_addr_t addr[MAX_SKB_FRAGS + 1]; /* DMA mapped addresses */
पूर्ण;

काष्ठा sge_txq अणु
	अचिन्हित पूर्णांक  in_use;       /* # of in-use Tx descriptors */
	अचिन्हित पूर्णांक  q_type;	    /* Q type Eth/Ctrl/Ofld */
	अचिन्हित पूर्णांक  size;         /* # of descriptors */
	अचिन्हित पूर्णांक  cidx;         /* SW consumer index */
	अचिन्हित पूर्णांक  pidx;         /* producer index */
	अचिन्हित दीर्घ stops;        /* # of बार q has been stopped */
	अचिन्हित दीर्घ restarts;     /* # of queue restarts */
	अचिन्हित पूर्णांक  cntxt_id;     /* SGE context id क्रम the Tx q */
	काष्ठा tx_desc *desc;       /* address of HW Tx descriptor ring */
	काष्ठा tx_sw_desc *sdesc;   /* address of SW Tx descriptor ring */
	काष्ठा sge_qstat *stat;     /* queue status entry */
	dma_addr_t    phys_addr;    /* physical address of the ring */
	spinlock_t db_lock;
	पूर्णांक db_disabled;
	अचिन्हित लघु db_pidx;
	अचिन्हित लघु db_pidx_inc;
	व्योम __iomem *bar2_addr;    /* address of BAR2 Queue रेजिस्टरs */
	अचिन्हित पूर्णांक bar2_qid;      /* Queue ID क्रम BAR2 Queue रेजिस्टरs */
पूर्ण;

काष्ठा sge_eth_txq अणु                /* state क्रम an SGE Ethernet Tx queue */
	काष्ठा sge_txq q;
	काष्ठा netdev_queue *txq;   /* associated netdev TX queue */
#अगर_घोषित CONFIG_CHELSIO_T4_DCB
	u8 dcb_prio;		    /* DCB Priority bound to queue */
#पूर्ण_अगर
	u8 dbqt;                    /* SGE Doorbell Queue Timer in use */
	अचिन्हित पूर्णांक dbqसमयrix;    /* SGE Doorbell Queue Timer Index */
	अचिन्हित दीर्घ tso;          /* # of TSO requests */
	अचिन्हित दीर्घ uso;          /* # of USO requests */
	अचिन्हित दीर्घ tx_cso;       /* # of Tx checksum offloads */
	अचिन्हित दीर्घ vlan_ins;     /* # of Tx VLAN insertions */
	अचिन्हित दीर्घ mapping_err;  /* # of I/O MMU packet mapping errors */
पूर्ण ____cacheline_aligned_in_smp;

काष्ठा sge_uld_txq अणु               /* state क्रम an SGE offload Tx queue */
	काष्ठा sge_txq q;
	काष्ठा adapter *adap;
	काष्ठा sk_buff_head sendq;  /* list of backpressured packets */
	काष्ठा tasklet_काष्ठा qresume_tsk; /* restarts the queue */
	bool service_ofldq_running; /* service_ofldq() is processing sendq */
	u8 full;                    /* the Tx ring is full */
	अचिन्हित दीर्घ mapping_err;  /* # of I/O MMU packet mapping errors */
पूर्ण ____cacheline_aligned_in_smp;

काष्ठा sge_ctrl_txq अणु               /* state क्रम an SGE control Tx queue */
	काष्ठा sge_txq q;
	काष्ठा adapter *adap;
	काष्ठा sk_buff_head sendq;  /* list of backpressured packets */
	काष्ठा tasklet_काष्ठा qresume_tsk; /* restarts the queue */
	u8 full;                    /* the Tx ring is full */
पूर्ण ____cacheline_aligned_in_smp;

काष्ठा sge_uld_rxq_info अणु
	अक्षर name[IFNAMSIZ];	/* name of ULD driver */
	काष्ठा sge_ofld_rxq *uldrxq; /* Rxq's क्रम ULD */
	u16 *rspq_id;		/* response queue id's of rxq */
	u16 nrxq;		/* # of ingress uld queues */
	u16 nciq;		/* # of completion queues */
	u8 uld;			/* uld type */
पूर्ण;

काष्ठा sge_uld_txq_info अणु
	काष्ठा sge_uld_txq *uldtxq; /* Txq's क्रम ULD */
	atomic_t users;		/* num users */
	u16 ntxq;		/* # of egress uld queues */
पूर्ण;

/* काष्ठा to मुख्यtain ULD list to पुनः_स्मृतिate ULD resources on hotplug */
काष्ठा cxgb4_uld_list अणु
	काष्ठा cxgb4_uld_info uld_info;
	काष्ठा list_head list_node;
	क्रमागत cxgb4_uld uld_type;
पूर्ण;

क्रमागत sge_eosw_state अणु
	CXGB4_EO_STATE_CLOSED = 0, /* Not पढ़ोy to accept traffic */
	CXGB4_EO_STATE_FLOWC_OPEN_SEND, /* Send FLOWC खोलो request */
	CXGB4_EO_STATE_FLOWC_OPEN_REPLY, /* Waiting क्रम FLOWC खोलो reply */
	CXGB4_EO_STATE_ACTIVE, /* Ready to accept traffic */
	CXGB4_EO_STATE_FLOWC_CLOSE_SEND, /* Send FLOWC बंद request */
	CXGB4_EO_STATE_FLOWC_CLOSE_REPLY, /* Waiting क्रम FLOWC बंद reply */
पूर्ण;

काष्ठा sge_eosw_txq अणु
	spinlock_t lock; /* Per queue lock to synchronize completions */
	क्रमागत sge_eosw_state state; /* Current ETHOFLD State */
	काष्ठा tx_sw_desc *desc; /* Descriptor ring to hold packets */
	u32 ndesc; /* Number of descriptors */
	u32 pidx; /* Current Producer Index */
	u32 last_pidx; /* Last successfully transmitted Producer Index */
	u32 cidx; /* Current Consumer Index */
	u32 last_cidx; /* Last successfully reclaimed Consumer Index */
	u32 flowc_idx; /* Descriptor containing a FLOWC request */
	u32 inuse; /* Number of packets held in ring */

	u32 cred; /* Current available credits */
	u32 ncompl; /* # of completions posted */
	u32 last_compl; /* # of credits consumed since last completion req */

	u32 eotid; /* Index पूर्णांकo EOTID table in software */
	u32 hwtid; /* Hardware EOTID index */

	u32 hwqid; /* Underlying hardware queue index */
	काष्ठा net_device *netdev; /* Poपूर्णांकer to netdevice */
	काष्ठा tasklet_काष्ठा qresume_tsk; /* Restarts the queue */
	काष्ठा completion completion; /* completion क्रम FLOWC rendezvous */
पूर्ण;

काष्ठा sge_eohw_txq अणु
	spinlock_t lock; /* Per queue lock */
	काष्ठा sge_txq q; /* HW Txq */
	काष्ठा adapter *adap; /* Backpoपूर्णांकer to adapter */
	अचिन्हित दीर्घ tso; /* # of TSO requests */
	अचिन्हित दीर्घ uso; /* # of USO requests */
	अचिन्हित दीर्घ tx_cso; /* # of Tx checksum offloads */
	अचिन्हित दीर्घ vlan_ins; /* # of Tx VLAN insertions */
	अचिन्हित दीर्घ mapping_err; /* # of I/O MMU packet mapping errors */
पूर्ण;

काष्ठा sge अणु
	काष्ठा sge_eth_txq ethtxq[MAX_ETH_QSETS];
	काष्ठा sge_eth_txq ptptxq;
	काष्ठा sge_ctrl_txq ctrlq[MAX_CTRL_QUEUES];

	काष्ठा sge_eth_rxq ethrxq[MAX_ETH_QSETS];
	काष्ठा sge_rspq fw_evtq ____cacheline_aligned_in_smp;
	काष्ठा sge_uld_rxq_info **uld_rxq_info;
	काष्ठा sge_uld_txq_info **uld_txq_info;

	काष्ठा sge_rspq पूर्णांकrq ____cacheline_aligned_in_smp;
	spinlock_t पूर्णांकrq_lock;

	काष्ठा sge_eohw_txq *eohw_txq;
	काष्ठा sge_ofld_rxq *eohw_rxq;

	काष्ठा sge_eth_rxq *mirror_rxq[NCHAN];

	u16 max_ethqsets;           /* # of available Ethernet queue sets */
	u16 ethqsets;               /* # of active Ethernet queue sets */
	u16 ethtxq_rover;           /* Tx queue to clean up next */
	u16 ofldqsets;              /* # of active ofld queue sets */
	u16 nqs_per_uld;	    /* # of Rx queues per ULD */
	u16 eoqsets;                /* # of ETHOFLD queues */
	u16 mirrorqsets;            /* # of Mirror queues */

	u16 समयr_val[SGE_NTIMERS];
	u8 counter_val[SGE_NCOUNTERS];
	u16 dbqसमयr_tick;
	u16 dbqसमयr_val[SGE_NDBQTIMERS];
	u32 fl_pg_order;            /* large page allocation size */
	u32 stat_len;               /* length of status page at ring end */
	u32 pktshअगरt;               /* padding between CPL & packet data */
	u32 fl_align;               /* response queue message alignment */
	u32 fl_starve_thres;        /* Free List starvation threshold */

	काष्ठा sge_idma_monitor_state idma_monitor;
	अचिन्हित पूर्णांक egr_start;
	अचिन्हित पूर्णांक egr_sz;
	अचिन्हित पूर्णांक ingr_start;
	अचिन्हित पूर्णांक ingr_sz;
	व्योम **egr_map;    /* qid->queue egress queue map */
	काष्ठा sge_rspq **ingr_map; /* qid->queue ingress queue map */
	अचिन्हित दीर्घ *starving_fl;
	अचिन्हित दीर्घ *txq_maperr;
	अचिन्हित दीर्घ *blocked_fl;
	काष्ठा समयr_list rx_समयr; /* refills starving FLs */
	काष्ठा समयr_list tx_समयr; /* checks Tx queues */

	पूर्णांक fwevtq_msix_idx; /* Index to firmware event queue MSI-X info */
	पूर्णांक nd_msix_idx; /* Index to non-data पूर्णांकerrupts MSI-X info */
पूर्ण;

#घोषणा क्रम_each_ethrxq(sge, i) क्रम (i = 0; i < (sge)->ethqsets; i++)
#घोषणा क्रम_each_ofldtxq(sge, i) क्रम (i = 0; i < (sge)->ofldqsets; i++)

काष्ठा l2t_data;

#अगर_घोषित CONFIG_PCI_IOV

/* T4 supports SRIOV on PF0-3 and T5 on PF0-7.  However, the Serial
 * Configuration initialization क्रम T5 only has SR-IOV functionality enabled
 * on PF0-3 in order to simplअगरy everything.
 */
#घोषणा NUM_OF_PF_WITH_SRIOV 4

#पूर्ण_अगर

काष्ठा करोorbell_stats अणु
	u32 db_drop;
	u32 db_empty;
	u32 db_full;
पूर्ण;

काष्ठा hash_mac_addr अणु
	काष्ठा list_head list;
	u8 addr[ETH_ALEN];
	अचिन्हित पूर्णांक अगरace_mac;
पूर्ण;

काष्ठा msix_bmap अणु
	अचिन्हित दीर्घ *msix_bmap;
	अचिन्हित पूर्णांक mapsize;
	spinlock_t lock; /* lock क्रम acquiring biपंचांगap */
पूर्ण;

काष्ठा msix_info अणु
	अचिन्हित लघु vec;
	अक्षर desc[IFNAMSIZ + 10];
	अचिन्हित पूर्णांक idx;
	cpumask_var_t aff_mask;
पूर्ण;

काष्ठा vf_info अणु
	अचिन्हित अक्षर vf_mac_addr[ETH_ALEN];
	अचिन्हित पूर्णांक tx_rate;
	bool pf_set_mac;
	u16 vlan;
	पूर्णांक link_state;
पूर्ण;

क्रमागत अणु
	HMA_DMA_MAPPED_FLAG = 1
पूर्ण;

काष्ठा hma_data अणु
	अचिन्हित अक्षर flags;
	काष्ठा sg_table *sgt;
	dma_addr_t *phy_addr;	/* physical address of the page */
पूर्ण;

काष्ठा mbox_list अणु
	काष्ठा list_head list;
पूर्ण;

#अगर IS_ENABLED(CONFIG_THERMAL)
काष्ठा ch_thermal अणु
	काष्ठा thermal_zone_device *tzdev;
	पूर्णांक trip_temp;
	पूर्णांक trip_type;
पूर्ण;
#पूर्ण_अगर

काष्ठा mps_entries_ref अणु
	काष्ठा list_head list;
	u8 addr[ETH_ALEN];
	u8 mask[ETH_ALEN];
	u16 idx;
	refcount_t refcnt;
पूर्ण;

काष्ठा cxgb4_ethtool_filter_info अणु
	u32 *loc_array; /* Array holding the actual TIDs set to filters */
	अचिन्हित दीर्घ *bmap; /* Biपंचांगap क्रम managing filters in use */
	u32 in_use; /* # of filters in use */
पूर्ण;

काष्ठा cxgb4_ethtool_filter अणु
	u32 nentries; /* Adapter wide number of supported filters */
	काष्ठा cxgb4_ethtool_filter_info *port; /* Per port entry */
पूर्ण;

काष्ठा adapter अणु
	व्योम __iomem *regs;
	व्योम __iomem *bar2;
	u32 t4_bar0;
	काष्ठा pci_dev *pdev;
	काष्ठा device *pdev_dev;
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक mbox;
	अचिन्हित पूर्णांक pf;
	अचिन्हित पूर्णांक flags;
	अचिन्हित पूर्णांक adap_idx;
	क्रमागत chip_type chip;
	u32 eth_flags;

	पूर्णांक msg_enable;
	__be16 vxlan_port;
	__be16 geneve_port;

	काष्ठा adapter_params params;
	काष्ठा cxgb4_virt_res vres;
	अचिन्हित पूर्णांक swपूर्णांकr;

	/* MSI-X Info क्रम NIC and OFLD queues */
	काष्ठा msix_info *msix_info;
	काष्ठा msix_bmap msix_bmap;

	काष्ठा करोorbell_stats db_stats;
	काष्ठा sge sge;

	काष्ठा net_device *port[MAX_NPORTS];
	u8 chan_map[NCHAN];                   /* channel -> port map */

	काष्ठा vf_info *vfinfo;
	u8 num_vfs;

	u32 filter_mode;
	अचिन्हित पूर्णांक l2t_start;
	अचिन्हित पूर्णांक l2t_end;
	काष्ठा l2t_data *l2t;
	अचिन्हित पूर्णांक clipt_start;
	अचिन्हित पूर्णांक clipt_end;
	काष्ठा clip_tbl *clipt;
	अचिन्हित पूर्णांक rawf_start;
	अचिन्हित पूर्णांक rawf_cnt;
	काष्ठा smt_data *smt;
	काष्ठा cxgb4_uld_info *uld;
	व्योम *uld_handle[CXGB4_ULD_MAX];
	अचिन्हित पूर्णांक num_uld;
	अचिन्हित पूर्णांक num_ofld_uld;
	काष्ठा list_head list_node;
	काष्ठा list_head rcu_node;
	काष्ठा list_head mac_hlist; /* list of MAC addresses in MPS Hash */
	काष्ठा list_head mps_ref;
	spinlock_t mps_ref_lock; /* lock क्रम syncing mps ref/def activities */

	व्योम *iscsi_ppm;

	काष्ठा tid_info tids;
	व्योम **tid_release_head;
	spinlock_t tid_release_lock;
	काष्ठा workqueue_काष्ठा *workq;
	काष्ठा work_काष्ठा tid_release_task;
	काष्ठा work_काष्ठा db_full_task;
	काष्ठा work_काष्ठा db_drop_task;
	काष्ठा work_काष्ठा fatal_err_notअगरy_task;
	bool tid_release_task_busy;

	/* lock क्रम mailbox cmd list */
	spinlock_t mbox_lock;
	काष्ठा mbox_list mlist;

	/* support क्रम mailbox command/reply logging */
#घोषणा T4_OS_LOG_MBOX_CMDS 256
	काष्ठा mbox_cmd_log *mbox_log;

	काष्ठा mutex uld_mutex;

	काष्ठा dentry *debugfs_root;
	bool use_bd;     /* Use SGE Back Door पूर्णांकfc क्रम पढ़ोing SGE Contexts */
	bool trace_rss;	/* 1 implies that dअगरferent RSS flit per filter is
			 * used per filter अन्यथा अगर 0 शेष RSS flit is
			 * used क्रम all 4 filters.
			 */

	काष्ठा ptp_घड़ी *ptp_घड़ी;
	काष्ठा ptp_घड़ी_info ptp_घड़ी_info;
	काष्ठा sk_buff *ptp_tx_skb;
	/* ptp lock */
	spinlock_t ptp_lock;
	spinlock_t stats_lock;
	spinlock_t win0_lock ____cacheline_aligned_in_smp;

	/* TC u32 offload */
	काष्ठा cxgb4_tc_u32_table *tc_u32;
	काष्ठा chcr_ktls chcr_ktls;
	काष्ठा chcr_stats_debug chcr_stats;
#अगर IS_ENABLED(CONFIG_CHELSIO_TLS_DEVICE)
	काष्ठा ch_ktls_stats_debug ch_ktls_stats;
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_CHELSIO_IPSEC_INLINE)
	काष्ठा ch_ipsec_stats_debug ch_ipsec_stats;
#पूर्ण_अगर

	/* TC flower offload */
	bool tc_flower_initialized;
	काष्ठा rhashtable flower_tbl;
	काष्ठा rhashtable_params flower_ht_params;
	काष्ठा समयr_list flower_stats_समयr;
	काष्ठा work_काष्ठा flower_stats_work;

	/* Ethtool Dump */
	काष्ठा ethtool_dump eth_dump;

	/* HMA */
	काष्ठा hma_data hma;

	काष्ठा srq_data *srq;

	/* Dump buffer क्रम collecting logs in kdump kernel */
	काष्ठा vmcoredd_data vmcoredd;
#अगर IS_ENABLED(CONFIG_THERMAL)
	काष्ठा ch_thermal ch_thermal;
#पूर्ण_अगर

	/* TC MQPRIO offload */
	काष्ठा cxgb4_tc_mqprio *tc_mqprio;

	/* TC MATCHALL classअगरier offload */
	काष्ठा cxgb4_tc_matchall *tc_matchall;

	/* Ethtool n-tuple */
	काष्ठा cxgb4_ethtool_filter *ethtool_filters;
पूर्ण;

/* Support क्रम "sched-class" command to allow a TX Scheduling Class to be
 * programmed with various parameters.
 */
काष्ठा ch_sched_params अणु
	u8   type;                     /* packet or flow */
	जोड़ अणु
		काष्ठा अणु
			u8   level;    /* scheduler hierarchy level */
			u8   mode;     /* per-class or per-flow */
			u8   rateunit; /* bit or packet rate */
			u8   ratemode; /* %port relative or kbps असलolute */
			u8   channel;  /* scheduler channel [0..N] */
			u8   class;    /* scheduler class [0..N] */
			u32  minrate;  /* minimum rate */
			u32  maxrate;  /* maximum rate */
			u16  weight;   /* percent weight */
			u16  pktsize;  /* average packet size */
			u16  burstsize;  /* burst buffer size */
		पूर्ण params;
	पूर्ण u;
पूर्ण;

क्रमागत अणु
	SCHED_CLASS_TYPE_PACKET = 0,    /* class type */
पूर्ण;

क्रमागत अणु
	SCHED_CLASS_LEVEL_CL_RL = 0,    /* class rate limiter */
	SCHED_CLASS_LEVEL_CH_RL = 2,    /* channel rate limiter */
पूर्ण;

क्रमागत अणु
	SCHED_CLASS_MODE_CLASS = 0,     /* per-class scheduling */
	SCHED_CLASS_MODE_FLOW,          /* per-flow scheduling */
पूर्ण;

क्रमागत अणु
	SCHED_CLASS_RATEUNIT_BITS = 0,  /* bit rate scheduling */
पूर्ण;

क्रमागत अणु
	SCHED_CLASS_RATEMODE_ABS = 1,   /* Kb/s */
पूर्ण;

/* Support क्रम "sched_queue" command to allow one or more NIC TX Queues
 * to be bound to a TX Scheduling Class.
 */
काष्ठा ch_sched_queue अणु
	s8   queue;    /* queue index */
	s8   class;    /* class index */
पूर्ण;

/* Support क्रम "sched_flowc" command to allow one or more FLOWC
 * to be bound to a TX Scheduling Class.
 */
काष्ठा ch_sched_flowc अणु
	s32 tid;   /* TID to bind */
	s8  class; /* class index */
पूर्ण;

/* Defined bit width of user definable filter tuples
 */
#घोषणा ETHTYPE_BITWIDTH 16
#घोषणा FRAG_BITWIDTH 1
#घोषणा MACIDX_BITWIDTH 9
#घोषणा FCOE_BITWIDTH 1
#घोषणा IPORT_BITWIDTH 3
#घोषणा MATCHTYPE_BITWIDTH 3
#घोषणा PROTO_BITWIDTH 8
#घोषणा TOS_BITWIDTH 8
#घोषणा PF_BITWIDTH 8
#घोषणा VF_BITWIDTH 8
#घोषणा IVLAN_BITWIDTH 16
#घोषणा OVLAN_BITWIDTH 16
#घोषणा ENCAP_VNI_BITWIDTH 24

/* Filter matching rules.  These consist of a set of ingress packet field
 * (value, mask) tuples.  The associated ingress packet field matches the
 * tuple when ((field & mask) == value).  (Thus a wildcard "don't care" field
 * rule can be स्थिरructed by specअगरying a tuple of (0, 0).)  A filter rule
 * matches an ingress packet when all of the inभागidual inभागidual field
 * matching rules are true.
 *
 * Partial field masks are always valid, however, जबतक it may be easy to
 * understand their meanings क्रम some fields (e.g. IP address to match a
 * subnet), क्रम others making sensible partial masks is less पूर्णांकuitive (e.g.
 * MPS match type) ...
 *
 * Most of the following data काष्ठाures are modeled on T4 capabilities.
 * Drivers क्रम earlier chips use the subsets which make sense क्रम those chips.
 * We really need to come up with a hardware-independent mechanism to
 * represent hardware filter capabilities ...
 */
काष्ठा ch_filter_tuple अणु
	/* Compressed header matching field rules.  The TP_VLAN_PRI_MAP
	 * रेजिस्टर selects which of these fields will participate in the
	 * filter match rules -- up to a maximum of 36 bits.  Because
	 * TP_VLAN_PRI_MAP is a global रेजिस्टर, all filters must use the same
	 * set of fields.
	 */
	uपूर्णांक32_t ethtype:ETHTYPE_BITWIDTH;      /* Ethernet type */
	uपूर्णांक32_t frag:FRAG_BITWIDTH;            /* IP fragmentation header */
	uपूर्णांक32_t ivlan_vld:1;                   /* inner VLAN valid */
	uपूर्णांक32_t ovlan_vld:1;                   /* outer VLAN valid */
	uपूर्णांक32_t pfvf_vld:1;                    /* PF/VF valid */
	uपूर्णांक32_t encap_vld:1;			/* Encapsulation valid */
	uपूर्णांक32_t macidx:MACIDX_BITWIDTH;        /* exact match MAC index */
	uपूर्णांक32_t fcoe:FCOE_BITWIDTH;            /* FCoE packet */
	uपूर्णांक32_t iport:IPORT_BITWIDTH;          /* ingress port */
	uपूर्णांक32_t matchtype:MATCHTYPE_BITWIDTH;  /* MPS match type */
	uपूर्णांक32_t proto:PROTO_BITWIDTH;          /* protocol type */
	uपूर्णांक32_t tos:TOS_BITWIDTH;              /* TOS/Traffic Type */
	uपूर्णांक32_t pf:PF_BITWIDTH;                /* PCI-E PF ID */
	uपूर्णांक32_t vf:VF_BITWIDTH;                /* PCI-E VF ID */
	uपूर्णांक32_t ivlan:IVLAN_BITWIDTH;          /* inner VLAN */
	uपूर्णांक32_t ovlan:OVLAN_BITWIDTH;          /* outer VLAN */
	uपूर्णांक32_t vni:ENCAP_VNI_BITWIDTH;	/* VNI of tunnel */

	/* Uncompressed header matching field rules.  These are always
	 * available क्रम field rules.
	 */
	uपूर्णांक8_t lip[16];        /* local IP address (IPv4 in [3:0]) */
	uपूर्णांक8_t fip[16];        /* क्रमeign IP address (IPv4 in [3:0]) */
	uपूर्णांक16_t lport;         /* local port */
	uपूर्णांक16_t fport;         /* क्रमeign port */
पूर्ण;

/* A filter ioctl command.
 */
काष्ठा ch_filter_specअगरication अणु
	/* Administrative fields क्रम filter.
	 */
	uपूर्णांक32_t hitcnts:1;     /* count filter hits in TCB */
	uपूर्णांक32_t prio:1;        /* filter has priority over active/server */

	/* Fundamental filter typing.  This is the one element of filter
	 * matching that करोesn't exist as a (value, mask) tuple.
	 */
	uपूर्णांक32_t type:1;        /* 0 => IPv4, 1 => IPv6 */
	u32 hash:1;		/* 0 => wild-card, 1 => exact-match */

	/* Packet dispatch inक्रमmation.  Ingress packets which match the
	 * filter rules will be dropped, passed to the host or चयनed back
	 * out as egress packets.
	 */
	uपूर्णांक32_t action:2;      /* drop, pass, चयन */

	uपूर्णांक32_t rpttid:1;      /* report TID in RSS hash field */

	uपूर्णांक32_t dirsteer:1;    /* 0 => RSS, 1 => steer to iq */
	uपूर्णांक32_t iq:10;         /* ingress queue */

	uपूर्णांक32_t maskhash:1;    /* dirsteer=0: store RSS hash in TCB */
	uपूर्णांक32_t dirsteerhash:1;/* dirsteer=1: 0 => TCB contains RSS hash */
				/*             1 => TCB contains IQ ID */

	/* Switch proxy/reग_लिखो fields.  An ingress packet which matches a
	 * filter with "switch" set will be looped back out as an egress
	 * packet -- potentially with some Ethernet header rewriting.
	 */
	uपूर्णांक32_t eport:2;       /* egress port to चयन packet out */
	uपूर्णांक32_t newdmac:1;     /* reग_लिखो destination MAC address */
	uपूर्णांक32_t newsmac:1;     /* reग_लिखो source MAC address */
	uपूर्णांक32_t newvlan:2;     /* reग_लिखो VLAN Tag */
	uपूर्णांक32_t nat_mode:3;    /* specअगरy NAT operation mode */
	uपूर्णांक8_t dmac[ETH_ALEN]; /* new destination MAC address */
	uपूर्णांक8_t smac[ETH_ALEN]; /* new source MAC address */
	uपूर्णांक16_t vlan;          /* VLAN Tag to insert */

	u8 nat_lip[16];		/* local IP to use after NAT'ing */
	u8 nat_fip[16];		/* क्रमeign IP to use after NAT'ing */
	u16 nat_lport;		/* local port to use after NAT'ing */
	u16 nat_fport;		/* क्रमeign port to use after NAT'ing */

	u32 tc_prio;		/* TC's filter priority index */
	u64 tc_cookie;		/* Unique cookie identअगरying TC rules */

	/* reservation क्रम future additions */
	u8 rsvd[12];

	/* Filter rule value/mask pairs.
	 */
	काष्ठा ch_filter_tuple val;
	काष्ठा ch_filter_tuple mask;
पूर्ण;

क्रमागत अणु
	FILTER_PASS = 0,        /* शेष */
	FILTER_DROP,
	FILTER_SWITCH
पूर्ण;

क्रमागत अणु
	VLAN_NOCHANGE = 0,      /* शेष */
	VLAN_REMOVE,
	VLAN_INSERT,
	VLAN_REWRITE
पूर्ण;

क्रमागत अणु
	NAT_MODE_NONE = 0,	/* No NAT perक्रमmed */
	NAT_MODE_DIP,		/* NAT on Dst IP */
	NAT_MODE_DIP_DP,	/* NAT on Dst IP, Dst Port */
	NAT_MODE_DIP_DP_SIP,	/* NAT on Dst IP, Dst Port and Src IP */
	NAT_MODE_DIP_DP_SP,	/* NAT on Dst IP, Dst Port and Src Port */
	NAT_MODE_SIP_SP,	/* NAT on Src IP and Src Port */
	NAT_MODE_DIP_SIP_SP,	/* NAT on Dst IP, Src IP and Src Port */
	NAT_MODE_ALL		/* NAT on entire 4-tuple */
पूर्ण;

#घोषणा CXGB4_FILTER_TYPE_MAX 2

/* Host shaकरोw copy of ingress filter entry.  This is in host native क्रमmat
 * and करोesn't match the ordering or bit order, etc. of the hardware of the
 * firmware command.  The use of bit-field काष्ठाure elements is purely to
 * remind ourselves of the field size limitations and save memory in the हाल
 * where the filter table is large.
 */
काष्ठा filter_entry अणु
	/* Administrative fields क्रम filter. */
	u32 valid:1;            /* filter allocated and valid */
	u32 locked:1;           /* filter is administratively locked */

	u32 pending:1;          /* filter action is pending firmware reply */
	काष्ठा filter_ctx *ctx; /* Caller's completion hook */
	काष्ठा l2t_entry *l2t;  /* Layer Two Table entry क्रम dmac */
	काष्ठा smt_entry *smt;  /* Source Mac Table entry क्रम smac */
	काष्ठा net_device *dev; /* Associated net device */
	u32 tid;                /* This will store the actual tid */

	/* The filter itself.  Most of this is a straight copy of inक्रमmation
	 * provided by the extended ioctl().  Some fields are translated to
	 * पूर्णांकernal क्रमms -- क्रम instance the Ingress Queue ID passed in from
	 * the ioctl() is translated पूर्णांकo the Absolute Ingress Queue ID.
	 */
	काष्ठा ch_filter_specअगरication fs;
पूर्ण;

अटल अंतरभूत पूर्णांक is_offload(स्थिर काष्ठा adapter *adap)
अणु
	वापस adap->params.offload;
पूर्ण

अटल अंतरभूत पूर्णांक is_hashfilter(स्थिर काष्ठा adapter *adap)
अणु
	वापस adap->params.hash_filter;
पूर्ण

अटल अंतरभूत पूर्णांक is_pci_uld(स्थिर काष्ठा adapter *adap)
अणु
	वापस adap->params.crypto;
पूर्ण

अटल अंतरभूत पूर्णांक is_uld(स्थिर काष्ठा adapter *adap)
अणु
	वापस (adap->params.offload || adap->params.crypto);
पूर्ण

अटल अंतरभूत पूर्णांक is_ethofld(स्थिर काष्ठा adapter *adap)
अणु
	वापस adap->params.ethofld;
पूर्ण

अटल अंतरभूत u32 t4_पढ़ो_reg(काष्ठा adapter *adap, u32 reg_addr)
अणु
	वापस पढ़ोl(adap->regs + reg_addr);
पूर्ण

अटल अंतरभूत व्योम t4_ग_लिखो_reg(काष्ठा adapter *adap, u32 reg_addr, u32 val)
अणु
	ग_लिखोl(val, adap->regs + reg_addr);
पूर्ण

#अगर_अघोषित पढ़ोq
अटल अंतरभूत u64 पढ़ोq(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	वापस पढ़ोl(addr) + ((u64)पढ़ोl(addr + 4) << 32);
पूर्ण

अटल अंतरभूत व्योम ग_लिखोq(u64 val, अस्थिर व्योम __iomem *addr)
अणु
	ग_लिखोl(val, addr);
	ग_लिखोl(val >> 32, addr + 4);
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत u64 t4_पढ़ो_reg64(काष्ठा adapter *adap, u32 reg_addr)
अणु
	वापस पढ़ोq(adap->regs + reg_addr);
पूर्ण

अटल अंतरभूत व्योम t4_ग_लिखो_reg64(काष्ठा adapter *adap, u32 reg_addr, u64 val)
अणु
	ग_लिखोq(val, adap->regs + reg_addr);
पूर्ण

/**
 * t4_set_hw_addr - store a port's MAC address in SW
 * @adapter: the adapter
 * @port_idx: the port index
 * @hw_addr: the Ethernet address
 *
 * Store the Ethernet address of the given port in SW.  Called by the common
 * code when it retrieves a port's Ethernet address from EEPROM.
 */
अटल अंतरभूत व्योम t4_set_hw_addr(काष्ठा adapter *adapter, पूर्णांक port_idx,
				  u8 hw_addr[])
अणु
	ether_addr_copy(adapter->port[port_idx]->dev_addr, hw_addr);
	ether_addr_copy(adapter->port[port_idx]->perm_addr, hw_addr);
पूर्ण

/**
 * netdev2pinfo - वापस the port_info काष्ठाure associated with a net_device
 * @dev: the netdev
 *
 * Return the काष्ठा port_info associated with a net_device
 */
अटल अंतरभूत काष्ठा port_info *netdev2pinfo(स्थिर काष्ठा net_device *dev)
अणु
	वापस netdev_priv(dev);
पूर्ण

/**
 * adap2pinfo - वापस the port_info of a port
 * @adap: the adapter
 * @idx: the port index
 *
 * Return the port_info काष्ठाure क्रम the port of the given index.
 */
अटल अंतरभूत काष्ठा port_info *adap2pinfo(काष्ठा adapter *adap, पूर्णांक idx)
अणु
	वापस netdev_priv(adap->port[idx]);
पूर्ण

/**
 * netdev2adap - वापस the adapter काष्ठाure associated with a net_device
 * @dev: the netdev
 *
 * Return the काष्ठा adapter associated with a net_device
 */
अटल अंतरभूत काष्ठा adapter *netdev2adap(स्थिर काष्ठा net_device *dev)
अणु
	वापस netdev2pinfo(dev)->adapter;
पूर्ण

/* Return a version number to identअगरy the type of adapter.  The scheme is:
 * - bits 0..9: chip version
 * - bits 10..15: chip revision
 * - bits 16..23: रेजिस्टर dump version
 */
अटल अंतरभूत अचिन्हित पूर्णांक mk_adap_vers(काष्ठा adapter *ap)
अणु
	वापस CHELSIO_CHIP_VERSION(ap->params.chip) |
		(CHELSIO_CHIP_RELEASE(ap->params.chip) << 10) | (1 << 16);
पूर्ण

/* Return a queue's पूर्णांकerrupt hold-off समय in us.  0 means no समयr. */
अटल अंतरभूत अचिन्हित पूर्णांक qसमयr_val(स्थिर काष्ठा adapter *adap,
				      स्थिर काष्ठा sge_rspq *q)
अणु
	अचिन्हित पूर्णांक idx = q->पूर्णांकr_params >> 1;

	वापस idx < SGE_NTIMERS ? adap->sge.समयr_val[idx] : 0;
पूर्ण

/* driver name used क्रम ethtool_drvinfo */
बाह्य अक्षर cxgb4_driver_name[];

व्योम t4_os_porपंचांगod_changed(काष्ठा adapter *adap, पूर्णांक port_id);
व्योम t4_os_link_changed(काष्ठा adapter *adap, पूर्णांक port_id, पूर्णांक link_stat);

व्योम t4_मुक्त_sge_resources(काष्ठा adapter *adap);
व्योम t4_मुक्त_ofld_rxqs(काष्ठा adapter *adap, पूर्णांक n, काष्ठा sge_ofld_rxq *q);
irq_handler_t t4_पूर्णांकr_handler(काष्ठा adapter *adap);
netdev_tx_t t4_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev);
पूर्णांक cxgb4_selftest_lb_pkt(काष्ठा net_device *netdev);
पूर्णांक t4_ethrx_handler(काष्ठा sge_rspq *q, स्थिर __be64 *rsp,
		     स्थिर काष्ठा pkt_gl *gl);
पूर्णांक t4_mgmt_tx(काष्ठा adapter *adap, काष्ठा sk_buff *skb);
पूर्णांक t4_ofld_send(काष्ठा adapter *adap, काष्ठा sk_buff *skb);
पूर्णांक t4_sge_alloc_rxq(काष्ठा adapter *adap, काष्ठा sge_rspq *iq, bool fwevtq,
		     काष्ठा net_device *dev, पूर्णांक पूर्णांकr_idx,
		     काष्ठा sge_fl *fl, rspq_handler_t hnd,
		     rspq_flush_handler_t flush_handler, पूर्णांक cong);
पूर्णांक t4_sge_alloc_eth_txq(काष्ठा adapter *adap, काष्ठा sge_eth_txq *txq,
			 काष्ठा net_device *dev, काष्ठा netdev_queue *netdevq,
			 अचिन्हित पूर्णांक iqid, u8 dbqt);
पूर्णांक t4_sge_alloc_ctrl_txq(काष्ठा adapter *adap, काष्ठा sge_ctrl_txq *txq,
			  काष्ठा net_device *dev, अचिन्हित पूर्णांक iqid,
			  अचिन्हित पूर्णांक cmplqid);
पूर्णांक t4_sge_mod_ctrl_txq(काष्ठा adapter *adap, अचिन्हित पूर्णांक eqid,
			अचिन्हित पूर्णांक cmplqid);
पूर्णांक t4_sge_alloc_uld_txq(काष्ठा adapter *adap, काष्ठा sge_uld_txq *txq,
			 काष्ठा net_device *dev, अचिन्हित पूर्णांक iqid,
			 अचिन्हित पूर्णांक uld_type);
पूर्णांक t4_sge_alloc_ethofld_txq(काष्ठा adapter *adap, काष्ठा sge_eohw_txq *txq,
			     काष्ठा net_device *dev, u32 iqid);
व्योम t4_sge_मुक्त_ethofld_txq(काष्ठा adapter *adap, काष्ठा sge_eohw_txq *txq);
irqवापस_t t4_sge_पूर्णांकr_msix(पूर्णांक irq, व्योम *cookie);
पूर्णांक t4_sge_init(काष्ठा adapter *adap);
व्योम t4_sge_start(काष्ठा adapter *adap);
व्योम t4_sge_stop(काष्ठा adapter *adap);
पूर्णांक t4_sge_eth_txq_egress_update(काष्ठा adapter *adap, काष्ठा sge_eth_txq *q,
				 पूर्णांक maxreclaim);
व्योम cxgb4_set_ethtool_ops(काष्ठा net_device *netdev);
पूर्णांक cxgb4_ग_लिखो_rss(स्थिर काष्ठा port_info *pi, स्थिर u16 *queues);
क्रमागत cpl_tx_tnl_lso_type cxgb_encap_offload_supported(काष्ठा sk_buff *skb);
बाह्य पूर्णांक dbfअगरo_पूर्णांक_thresh;

#घोषणा क्रम_each_port(adapter, iter) \
	क्रम (iter = 0; iter < (adapter)->params.nports; ++iter)

अटल अंतरभूत पूर्णांक is_bypass(काष्ठा adapter *adap)
अणु
	वापस adap->params.bypass;
पूर्ण

अटल अंतरभूत पूर्णांक is_bypass_device(पूर्णांक device)
अणु
	/* this should be set based upon device capabilities */
	चयन (device) अणु
	हाल 0x440b:
	हाल 0x440c:
		वापस 1;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक is_10gbt_device(पूर्णांक device)
अणु
	/* this should be set based upon device capabilities */
	चयन (device) अणु
	हाल 0x4409:
	हाल 0x4486:
		वापस 1;

	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक core_ticks_per_usec(स्थिर काष्ठा adapter *adap)
अणु
	वापस adap->params.vpd.cclk / 1000;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक us_to_core_ticks(स्थिर काष्ठा adapter *adap,
					    अचिन्हित पूर्णांक us)
अणु
	वापस (us * adap->params.vpd.cclk) / 1000;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक core_ticks_to_us(स्थिर काष्ठा adapter *adapter,
					    अचिन्हित पूर्णांक ticks)
अणु
	/* add Core Clock / 2 to round ticks to nearest uS */
	वापस ((ticks * 1000 + adapter->params.vpd.cclk/2) /
		adapter->params.vpd.cclk);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक dack_ticks_to_usec(स्थिर काष्ठा adapter *adap,
					      अचिन्हित पूर्णांक ticks)
अणु
	वापस (ticks << adap->params.tp.dack_re) / core_ticks_per_usec(adap);
पूर्ण

व्योम t4_set_reg_field(काष्ठा adapter *adap, अचिन्हित पूर्णांक addr, u32 mask,
		      u32 val);

पूर्णांक t4_wr_mbox_meat_समयout(काष्ठा adapter *adap, पूर्णांक mbox, स्थिर व्योम *cmd,
			    पूर्णांक size, व्योम *rpl, bool sleep_ok, पूर्णांक समयout);
पूर्णांक t4_wr_mbox_meat(काष्ठा adapter *adap, पूर्णांक mbox, स्थिर व्योम *cmd, पूर्णांक size,
		    व्योम *rpl, bool sleep_ok);

अटल अंतरभूत पूर्णांक t4_wr_mbox_समयout(काष्ठा adapter *adap, पूर्णांक mbox,
				     स्थिर व्योम *cmd, पूर्णांक size, व्योम *rpl,
				     पूर्णांक समयout)
अणु
	वापस t4_wr_mbox_meat_समयout(adap, mbox, cmd, size, rpl, true,
				       समयout);
पूर्ण

अटल अंतरभूत पूर्णांक t4_wr_mbox(काष्ठा adapter *adap, पूर्णांक mbox, स्थिर व्योम *cmd,
			     पूर्णांक size, व्योम *rpl)
अणु
	वापस t4_wr_mbox_meat(adap, mbox, cmd, size, rpl, true);
पूर्ण

अटल अंतरभूत पूर्णांक t4_wr_mbox_ns(काष्ठा adapter *adap, पूर्णांक mbox, स्थिर व्योम *cmd,
				पूर्णांक size, व्योम *rpl)
अणु
	वापस t4_wr_mbox_meat(adap, mbox, cmd, size, rpl, false);
पूर्ण

/**
 *	hash_mac_addr - वापस the hash value of a MAC address
 *	@addr: the 48-bit Ethernet MAC address
 *
 *	Hashes a MAC address according to the hash function used by HW inexact
 *	(hash) address matching.
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

पूर्णांक cxgb4_set_rspq_पूर्णांकr_params(काष्ठा sge_rspq *q, अचिन्हित पूर्णांक us,
			       अचिन्हित पूर्णांक cnt);
अटल अंतरभूत व्योम init_rspq(काष्ठा adapter *adap, काष्ठा sge_rspq *q,
			     अचिन्हित पूर्णांक us, अचिन्हित पूर्णांक cnt,
			     अचिन्हित पूर्णांक size, अचिन्हित पूर्णांक iqe_size)
अणु
	q->adap = adap;
	cxgb4_set_rspq_पूर्णांकr_params(q, us, cnt);
	q->iqe_len = iqe_size;
	q->size = size;
पूर्ण

/**
 *     t4_is_inserted_mod_type - is a plugged in Firmware Module Type
 *     @fw_mod_type: the Firmware Mofule Type
 *
 *     Return whether the Firmware Module Type represents a real Transceiver
 *     Module/Cable Module Type which has been inserted.
 */
अटल अंतरभूत bool t4_is_inserted_mod_type(अचिन्हित पूर्णांक fw_mod_type)
अणु
	वापस (fw_mod_type != FW_PORT_MOD_TYPE_NONE &&
		fw_mod_type != FW_PORT_MOD_TYPE_NOTSUPPORTED &&
		fw_mod_type != FW_PORT_MOD_TYPE_UNKNOWN &&
		fw_mod_type != FW_PORT_MOD_TYPE_ERROR);
पूर्ण

व्योम t4_ग_लिखो_indirect(काष्ठा adapter *adap, अचिन्हित पूर्णांक addr_reg,
		       अचिन्हित पूर्णांक data_reg, स्थिर u32 *vals,
		       अचिन्हित पूर्णांक nregs, अचिन्हित पूर्णांक start_idx);
व्योम t4_पढ़ो_indirect(काष्ठा adapter *adap, अचिन्हित पूर्णांक addr_reg,
		      अचिन्हित पूर्णांक data_reg, u32 *vals, अचिन्हित पूर्णांक nregs,
		      अचिन्हित पूर्णांक start_idx);
व्योम t4_hw_pci_पढ़ो_cfg4(काष्ठा adapter *adapter, पूर्णांक reg, u32 *val);

काष्ठा fw_filter_wr;

व्योम t4_पूर्णांकr_enable(काष्ठा adapter *adapter);
व्योम t4_पूर्णांकr_disable(काष्ठा adapter *adapter);
पूर्णांक t4_slow_पूर्णांकr_handler(काष्ठा adapter *adapter);

पूर्णांक t4_रुको_dev_पढ़ोy(व्योम __iomem *regs);

fw_port_cap32_t t4_link_acaps(काष्ठा adapter *adapter, अचिन्हित पूर्णांक port,
			      काष्ठा link_config *lc);
पूर्णांक t4_link_l1cfg_core(काष्ठा adapter *adap, अचिन्हित पूर्णांक mbox,
		       अचिन्हित पूर्णांक port, काष्ठा link_config *lc,
		       u8 sleep_ok, पूर्णांक समयout);

अटल अंतरभूत पूर्णांक t4_link_l1cfg(काष्ठा adapter *adapter, अचिन्हित पूर्णांक mbox,
				अचिन्हित पूर्णांक port, काष्ठा link_config *lc)
अणु
	वापस t4_link_l1cfg_core(adapter, mbox, port, lc,
				  true, FW_CMD_MAX_TIMEOUT);
पूर्ण

अटल अंतरभूत पूर्णांक t4_link_l1cfg_ns(काष्ठा adapter *adapter, अचिन्हित पूर्णांक mbox,
				   अचिन्हित पूर्णांक port, काष्ठा link_config *lc)
अणु
	वापस t4_link_l1cfg_core(adapter, mbox, port, lc,
				  false, FW_CMD_MAX_TIMEOUT);
पूर्ण

पूर्णांक t4_restart_aneg(काष्ठा adapter *adap, अचिन्हित पूर्णांक mbox, अचिन्हित पूर्णांक port);

u32 t4_पढ़ो_pcie_cfg4(काष्ठा adapter *adap, पूर्णांक reg);
u32 t4_get_util_winकरोw(काष्ठा adapter *adap);
व्योम t4_setup_memwin(काष्ठा adapter *adap, u32 memwin_base, u32 winकरोw);

पूर्णांक t4_memory_rw_init(काष्ठा adapter *adap, पूर्णांक win, पूर्णांक mtype, u32 *mem_off,
		      u32 *mem_base, u32 *mem_aperture);
व्योम t4_memory_update_win(काष्ठा adapter *adap, पूर्णांक win, u32 addr);
व्योम t4_memory_rw_residual(काष्ठा adapter *adap, u32 off, u32 addr, u8 *buf,
			   पूर्णांक dir);
#घोषणा T4_MEMORY_WRITE	0
#घोषणा T4_MEMORY_READ	1
पूर्णांक t4_memory_rw(काष्ठा adapter *adap, पूर्णांक win, पूर्णांक mtype, u32 addr, u32 len,
		 व्योम *buf, पूर्णांक dir);
अटल अंतरभूत पूर्णांक t4_memory_ग_लिखो(काष्ठा adapter *adap, पूर्णांक mtype, u32 addr,
				  u32 len, __be32 *buf)
अणु
	वापस t4_memory_rw(adap, 0, mtype, addr, len, buf, 0);
पूर्ण

अचिन्हित पूर्णांक t4_get_regs_len(काष्ठा adapter *adapter);
व्योम t4_get_regs(काष्ठा adapter *adap, व्योम *buf, माप_प्रकार buf_size);

पूर्णांक t4_eeprom_ptov(अचिन्हित पूर्णांक phys_addr, अचिन्हित पूर्णांक fn, अचिन्हित पूर्णांक sz);
पूर्णांक t4_seeprom_wp(काष्ठा adapter *adapter, bool enable);
पूर्णांक t4_get_raw_vpd_params(काष्ठा adapter *adapter, काष्ठा vpd_params *p);
पूर्णांक t4_get_vpd_params(काष्ठा adapter *adapter, काष्ठा vpd_params *p);
पूर्णांक t4_get_pfres(काष्ठा adapter *adapter);
पूर्णांक t4_पढ़ो_flash(काष्ठा adapter *adapter, अचिन्हित पूर्णांक addr,
		  अचिन्हित पूर्णांक nwords, u32 *data, पूर्णांक byte_oriented);
पूर्णांक t4_load_fw(काष्ठा adapter *adapter, स्थिर u8 *fw_data, अचिन्हित पूर्णांक size);
पूर्णांक t4_load_phy_fw(काष्ठा adapter *adap, पूर्णांक win,
		   पूर्णांक (*phy_fw_version)(स्थिर u8 *, माप_प्रकार),
		   स्थिर u8 *phy_fw_data, माप_प्रकार phy_fw_size);
पूर्णांक t4_phy_fw_ver(काष्ठा adapter *adap, पूर्णांक *phy_fw_ver);
पूर्णांक t4_fwcache(काष्ठा adapter *adap, क्रमागत fw_params_param_dev_fwcache op);
पूर्णांक t4_fw_upgrade(काष्ठा adapter *adap, अचिन्हित पूर्णांक mbox,
		  स्थिर u8 *fw_data, अचिन्हित पूर्णांक size, पूर्णांक क्रमce);
पूर्णांक t4_fl_pkt_align(काष्ठा adapter *adap);
अचिन्हित पूर्णांक t4_flash_cfg_addr(काष्ठा adapter *adapter);
पूर्णांक t4_check_fw_version(काष्ठा adapter *adap);
पूर्णांक t4_load_cfg(काष्ठा adapter *adapter, स्थिर u8 *cfg_data, अचिन्हित पूर्णांक size);
पूर्णांक t4_get_fw_version(काष्ठा adapter *adapter, u32 *vers);
पूर्णांक t4_get_bs_version(काष्ठा adapter *adapter, u32 *vers);
पूर्णांक t4_get_tp_version(काष्ठा adapter *adapter, u32 *vers);
पूर्णांक t4_get_exprom_version(काष्ठा adapter *adapter, u32 *vers);
पूर्णांक t4_get_scfg_version(काष्ठा adapter *adapter, u32 *vers);
पूर्णांक t4_get_vpd_version(काष्ठा adapter *adapter, u32 *vers);
पूर्णांक t4_get_version_info(काष्ठा adapter *adapter);
व्योम t4_dump_version_info(काष्ठा adapter *adapter);
पूर्णांक t4_prep_fw(काष्ठा adapter *adap, काष्ठा fw_info *fw_info,
	       स्थिर u8 *fw_data, अचिन्हित पूर्णांक fw_size,
	       काष्ठा fw_hdr *card_fw, क्रमागत dev_state state, पूर्णांक *reset);
पूर्णांक t4_prep_adapter(काष्ठा adapter *adapter);
पूर्णांक t4_shutकरोwn_adapter(काष्ठा adapter *adapter);

क्रमागत t4_bar2_qtype अणु T4_BAR2_QTYPE_EGRESS, T4_BAR2_QTYPE_INGRESS पूर्ण;
पूर्णांक t4_bar2_sge_qregs(काष्ठा adapter *adapter,
		      अचिन्हित पूर्णांक qid,
		      क्रमागत t4_bar2_qtype qtype,
		      पूर्णांक user,
		      u64 *pbar2_qoffset,
		      अचिन्हित पूर्णांक *pbar2_qid);

अचिन्हित पूर्णांक qसमयr_val(स्थिर काष्ठा adapter *adap,
			स्थिर काष्ठा sge_rspq *q);

पूर्णांक t4_init_devlog_params(काष्ठा adapter *adapter);
पूर्णांक t4_init_sge_params(काष्ठा adapter *adapter);
पूर्णांक t4_init_tp_params(काष्ठा adapter *adap, bool sleep_ok);
पूर्णांक t4_filter_field_shअगरt(स्थिर काष्ठा adapter *adap, पूर्णांक filter_sel);
पूर्णांक t4_init_rss_mode(काष्ठा adapter *adap, पूर्णांक mbox);
पूर्णांक t4_init_portinfo(काष्ठा port_info *pi, पूर्णांक mbox,
		     पूर्णांक port, पूर्णांक pf, पूर्णांक vf, u8 mac[]);
पूर्णांक t4_port_init(काष्ठा adapter *adap, पूर्णांक mbox, पूर्णांक pf, पूर्णांक vf);
पूर्णांक t4_init_port_mirror(काष्ठा port_info *pi, u8 mbox, u8 port, u8 pf, u8 vf,
			u16 *mirror_viid);
व्योम t4_fatal_err(काष्ठा adapter *adapter);
अचिन्हित पूर्णांक t4_chip_rss_size(काष्ठा adapter *adapter);
पूर्णांक t4_config_rss_range(काष्ठा adapter *adapter, पूर्णांक mbox, अचिन्हित पूर्णांक viid,
			पूर्णांक start, पूर्णांक n, स्थिर u16 *rspq, अचिन्हित पूर्णांक nrspq);
पूर्णांक t4_config_glbl_rss(काष्ठा adapter *adapter, पूर्णांक mbox, अचिन्हित पूर्णांक mode,
		       अचिन्हित पूर्णांक flags);
पूर्णांक t4_config_vi_rss(काष्ठा adapter *adapter, पूर्णांक mbox, अचिन्हित पूर्णांक viid,
		     अचिन्हित पूर्णांक flags, अचिन्हित पूर्णांक defq);
पूर्णांक t4_पढ़ो_rss(काष्ठा adapter *adapter, u16 *entries);
व्योम t4_पढ़ो_rss_key(काष्ठा adapter *adapter, u32 *key, bool sleep_ok);
व्योम t4_ग_लिखो_rss_key(काष्ठा adapter *adap, स्थिर u32 *key, पूर्णांक idx,
		      bool sleep_ok);
व्योम t4_पढ़ो_rss_pf_config(काष्ठा adapter *adapter, अचिन्हित पूर्णांक index,
			   u32 *valp, bool sleep_ok);
व्योम t4_पढ़ो_rss_vf_config(काष्ठा adapter *adapter, अचिन्हित पूर्णांक index,
			   u32 *vfl, u32 *vfh, bool sleep_ok);
u32 t4_पढ़ो_rss_pf_map(काष्ठा adapter *adapter, bool sleep_ok);
u32 t4_पढ़ो_rss_pf_mask(काष्ठा adapter *adapter, bool sleep_ok);

अचिन्हित पूर्णांक t4_get_mps_bg_map(काष्ठा adapter *adapter, पूर्णांक pidx);
अचिन्हित पूर्णांक t4_get_tp_ch_map(काष्ठा adapter *adapter, पूर्णांक pidx);
व्योम t4_pmtx_get_stats(काष्ठा adapter *adap, u32 cnt[], u64 cycles[]);
व्योम t4_pmrx_get_stats(काष्ठा adapter *adap, u32 cnt[], u64 cycles[]);
पूर्णांक t4_पढ़ो_cim_ibq(काष्ठा adapter *adap, अचिन्हित पूर्णांक qid, u32 *data,
		    माप_प्रकार n);
पूर्णांक t4_पढ़ो_cim_obq(काष्ठा adapter *adap, अचिन्हित पूर्णांक qid, u32 *data,
		    माप_प्रकार n);
पूर्णांक t4_cim_पढ़ो(काष्ठा adapter *adap, अचिन्हित पूर्णांक addr, अचिन्हित पूर्णांक n,
		अचिन्हित पूर्णांक *valp);
पूर्णांक t4_cim_ग_लिखो(काष्ठा adapter *adap, अचिन्हित पूर्णांक addr, अचिन्हित पूर्णांक n,
		 स्थिर अचिन्हित पूर्णांक *valp);
पूर्णांक t4_cim_पढ़ो_la(काष्ठा adapter *adap, u32 *la_buf, अचिन्हित पूर्णांक *wrptr);
व्योम t4_cim_पढ़ो_pअगर_la(काष्ठा adapter *adap, u32 *pअगर_req, u32 *pअगर_rsp,
			अचिन्हित पूर्णांक *pअगर_req_wrptr,
			अचिन्हित पूर्णांक *pअगर_rsp_wrptr);
व्योम t4_cim_पढ़ो_ma_la(काष्ठा adapter *adap, u32 *ma_req, u32 *ma_rsp);
व्योम t4_पढ़ो_cimq_cfg(काष्ठा adapter *adap, u16 *base, u16 *size, u16 *thres);
स्थिर अक्षर *t4_get_port_type_description(क्रमागत fw_port_type port_type);
व्योम t4_get_port_stats(काष्ठा adapter *adap, पूर्णांक idx, काष्ठा port_stats *p);
व्योम t4_get_port_stats_offset(काष्ठा adapter *adap, पूर्णांक idx,
			      काष्ठा port_stats *stats,
			      काष्ठा port_stats *offset);
व्योम t4_get_lb_stats(काष्ठा adapter *adap, पूर्णांक idx, काष्ठा lb_port_stats *p);
व्योम t4_पढ़ो_mtu_tbl(काष्ठा adapter *adap, u16 *mtus, u8 *mtu_log);
व्योम t4_पढ़ो_cong_tbl(काष्ठा adapter *adap, u16 incr[NMTUS][NCCTRL_WIN]);
व्योम t4_tp_wr_bits_indirect(काष्ठा adapter *adap, अचिन्हित पूर्णांक addr,
			    अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक val);
व्योम t4_tp_पढ़ो_la(काष्ठा adapter *adap, u64 *la_buf, अचिन्हित पूर्णांक *wrptr);
व्योम t4_tp_get_err_stats(काष्ठा adapter *adap, काष्ठा tp_err_stats *st,
			 bool sleep_ok);
व्योम t4_tp_get_cpl_stats(काष्ठा adapter *adap, काष्ठा tp_cpl_stats *st,
			 bool sleep_ok);
व्योम t4_tp_get_rdma_stats(काष्ठा adapter *adap, काष्ठा tp_rdma_stats *st,
			  bool sleep_ok);
व्योम t4_get_usm_stats(काष्ठा adapter *adap, काष्ठा tp_usm_stats *st,
		      bool sleep_ok);
व्योम t4_tp_get_tcp_stats(काष्ठा adapter *adap, काष्ठा tp_tcp_stats *v4,
			 काष्ठा tp_tcp_stats *v6, bool sleep_ok);
व्योम t4_get_fcoe_stats(काष्ठा adapter *adap, अचिन्हित पूर्णांक idx,
		       काष्ठा tp_fcoe_stats *st, bool sleep_ok);
व्योम t4_load_mtus(काष्ठा adapter *adap, स्थिर अचिन्हित लघु *mtus,
		  स्थिर अचिन्हित लघु *alpha, स्थिर अचिन्हित लघु *beta);

व्योम t4_ulprx_पढ़ो_la(काष्ठा adapter *adap, u32 *la_buf);

व्योम t4_get_chan_txrate(काष्ठा adapter *adap, u64 *nic_rate, u64 *ofld_rate);
व्योम t4_mk_filtdelwr(अचिन्हित पूर्णांक ftid, काष्ठा fw_filter_wr *wr, पूर्णांक qid);

व्योम t4_wol_magic_enable(काष्ठा adapter *adap, अचिन्हित पूर्णांक port,
			 स्थिर u8 *addr);
पूर्णांक t4_wol_pat_enable(काष्ठा adapter *adap, अचिन्हित पूर्णांक port, अचिन्हित पूर्णांक map,
		      u64 mask0, u64 mask1, अचिन्हित पूर्णांक crc, bool enable);

पूर्णांक t4_fw_hello(काष्ठा adapter *adap, अचिन्हित पूर्णांक mbox, अचिन्हित पूर्णांक evt_mbox,
		क्रमागत dev_master master, क्रमागत dev_state *state);
पूर्णांक t4_fw_bye(काष्ठा adapter *adap, अचिन्हित पूर्णांक mbox);
पूर्णांक t4_early_init(काष्ठा adapter *adap, अचिन्हित पूर्णांक mbox);
पूर्णांक t4_fw_reset(काष्ठा adapter *adap, अचिन्हित पूर्णांक mbox, पूर्णांक reset);
पूर्णांक t4_fixup_host_params(काष्ठा adapter *adap, अचिन्हित पूर्णांक page_size,
			  अचिन्हित पूर्णांक cache_line_size);
पूर्णांक t4_fw_initialize(काष्ठा adapter *adap, अचिन्हित पूर्णांक mbox);
पूर्णांक t4_query_params(काष्ठा adapter *adap, अचिन्हित पूर्णांक mbox, अचिन्हित पूर्णांक pf,
		    अचिन्हित पूर्णांक vf, अचिन्हित पूर्णांक nparams, स्थिर u32 *params,
		    u32 *val);
पूर्णांक t4_query_params_ns(काष्ठा adapter *adap, अचिन्हित पूर्णांक mbox, अचिन्हित पूर्णांक pf,
		       अचिन्हित पूर्णांक vf, अचिन्हित पूर्णांक nparams, स्थिर u32 *params,
		       u32 *val);
पूर्णांक t4_query_params_rw(काष्ठा adapter *adap, अचिन्हित पूर्णांक mbox, अचिन्हित पूर्णांक pf,
		       अचिन्हित पूर्णांक vf, अचिन्हित पूर्णांक nparams, स्थिर u32 *params,
		       u32 *val, पूर्णांक rw, bool sleep_ok);
पूर्णांक t4_set_params_समयout(काष्ठा adapter *adap, अचिन्हित पूर्णांक mbox,
			  अचिन्हित पूर्णांक pf, अचिन्हित पूर्णांक vf,
			  अचिन्हित पूर्णांक nparams, स्थिर u32 *params,
			  स्थिर u32 *val, पूर्णांक समयout);
पूर्णांक t4_set_params(काष्ठा adapter *adap, अचिन्हित पूर्णांक mbox, अचिन्हित पूर्णांक pf,
		  अचिन्हित पूर्णांक vf, अचिन्हित पूर्णांक nparams, स्थिर u32 *params,
		  स्थिर u32 *val);
पूर्णांक t4_cfg_pfvf(काष्ठा adapter *adap, अचिन्हित पूर्णांक mbox, अचिन्हित पूर्णांक pf,
		अचिन्हित पूर्णांक vf, अचिन्हित पूर्णांक txq, अचिन्हित पूर्णांक txq_eth_ctrl,
		अचिन्हित पूर्णांक rxqi, अचिन्हित पूर्णांक rxq, अचिन्हित पूर्णांक tc,
		अचिन्हित पूर्णांक vi, अचिन्हित पूर्णांक cmask, अचिन्हित पूर्णांक pmask,
		अचिन्हित पूर्णांक nexact, अचिन्हित पूर्णांक rcaps, अचिन्हित पूर्णांक wxcaps);
पूर्णांक t4_alloc_vi(काष्ठा adapter *adap, अचिन्हित पूर्णांक mbox, अचिन्हित पूर्णांक port,
		अचिन्हित पूर्णांक pf, अचिन्हित पूर्णांक vf, अचिन्हित पूर्णांक nmac, u8 *mac,
		अचिन्हित पूर्णांक *rss_size, u8 *vivld, u8 *vin);
पूर्णांक t4_मुक्त_vi(काष्ठा adapter *adap, अचिन्हित पूर्णांक mbox,
	       अचिन्हित पूर्णांक pf, अचिन्हित पूर्णांक vf,
	       अचिन्हित पूर्णांक viid);
पूर्णांक t4_set_rxmode(काष्ठा adapter *adap, अचिन्हित पूर्णांक mbox, अचिन्हित पूर्णांक viid,
		  अचिन्हित पूर्णांक viid_mirror, पूर्णांक mtu, पूर्णांक promisc, पूर्णांक all_multi,
		  पूर्णांक bcast, पूर्णांक vlanex, bool sleep_ok);
पूर्णांक t4_मुक्त_raw_mac_filt(काष्ठा adapter *adap, अचिन्हित पूर्णांक viid,
			 स्थिर u8 *addr, स्थिर u8 *mask, अचिन्हित पूर्णांक idx,
			 u8 lookup_type, u8 port_id, bool sleep_ok);
पूर्णांक t4_मुक्त_encap_mac_filt(काष्ठा adapter *adap, अचिन्हित पूर्णांक viid, पूर्णांक idx,
			   bool sleep_ok);
पूर्णांक t4_alloc_encap_mac_filt(काष्ठा adapter *adap, अचिन्हित पूर्णांक viid,
			    स्थिर u8 *addr, स्थिर u8 *mask, अचिन्हित पूर्णांक vni,
			    अचिन्हित पूर्णांक vni_mask, u8 dip_hit, u8 lookup_type,
			    bool sleep_ok);
पूर्णांक t4_alloc_raw_mac_filt(काष्ठा adapter *adap, अचिन्हित पूर्णांक viid,
			  स्थिर u8 *addr, स्थिर u8 *mask, अचिन्हित पूर्णांक idx,
			  u8 lookup_type, u8 port_id, bool sleep_ok);
पूर्णांक t4_alloc_mac_filt(काष्ठा adapter *adap, अचिन्हित पूर्णांक mbox,
		      अचिन्हित पूर्णांक viid, bool मुक्त, अचिन्हित पूर्णांक naddr,
		      स्थिर u8 **addr, u16 *idx, u64 *hash, bool sleep_ok);
पूर्णांक t4_मुक्त_mac_filt(काष्ठा adapter *adap, अचिन्हित पूर्णांक mbox,
		     अचिन्हित पूर्णांक viid, अचिन्हित पूर्णांक naddr,
		     स्थिर u8 **addr, bool sleep_ok);
पूर्णांक t4_change_mac(काष्ठा adapter *adap, अचिन्हित पूर्णांक mbox, अचिन्हित पूर्णांक viid,
		  पूर्णांक idx, स्थिर u8 *addr, bool persist, u8 *smt_idx);
पूर्णांक t4_set_addr_hash(काष्ठा adapter *adap, अचिन्हित पूर्णांक mbox, अचिन्हित पूर्णांक viid,
		     bool ucast, u64 vec, bool sleep_ok);
पूर्णांक t4_enable_vi_params(काष्ठा adapter *adap, अचिन्हित पूर्णांक mbox,
			अचिन्हित पूर्णांक viid, bool rx_en, bool tx_en, bool dcb_en);
पूर्णांक t4_enable_pi_params(काष्ठा adapter *adap, अचिन्हित पूर्णांक mbox,
			काष्ठा port_info *pi,
			bool rx_en, bool tx_en, bool dcb_en);
पूर्णांक t4_enable_vi(काष्ठा adapter *adap, अचिन्हित पूर्णांक mbox, अचिन्हित पूर्णांक viid,
		 bool rx_en, bool tx_en);
पूर्णांक t4_identअगरy_port(काष्ठा adapter *adap, अचिन्हित पूर्णांक mbox, अचिन्हित पूर्णांक viid,
		     अचिन्हित पूर्णांक nblinks);
पूर्णांक t4_mdio_rd(काष्ठा adapter *adap, अचिन्हित पूर्णांक mbox, अचिन्हित पूर्णांक phy_addr,
	       अचिन्हित पूर्णांक mmd, अचिन्हित पूर्णांक reg, u16 *valp);
पूर्णांक t4_mdio_wr(काष्ठा adapter *adap, अचिन्हित पूर्णांक mbox, अचिन्हित पूर्णांक phy_addr,
	       अचिन्हित पूर्णांक mmd, अचिन्हित पूर्णांक reg, u16 val);
पूर्णांक t4_iq_stop(काष्ठा adapter *adap, अचिन्हित पूर्णांक mbox, अचिन्हित पूर्णांक pf,
	       अचिन्हित पूर्णांक vf, अचिन्हित पूर्णांक iqtype, अचिन्हित पूर्णांक iqid,
	       अचिन्हित पूर्णांक fl0id, अचिन्हित पूर्णांक fl1id);
पूर्णांक t4_iq_मुक्त(काष्ठा adapter *adap, अचिन्हित पूर्णांक mbox, अचिन्हित पूर्णांक pf,
	       अचिन्हित पूर्णांक vf, अचिन्हित पूर्णांक iqtype, अचिन्हित पूर्णांक iqid,
	       अचिन्हित पूर्णांक fl0id, अचिन्हित पूर्णांक fl1id);
पूर्णांक t4_eth_eq_मुक्त(काष्ठा adapter *adap, अचिन्हित पूर्णांक mbox, अचिन्हित पूर्णांक pf,
		   अचिन्हित पूर्णांक vf, अचिन्हित पूर्णांक eqid);
पूर्णांक t4_ctrl_eq_मुक्त(काष्ठा adapter *adap, अचिन्हित पूर्णांक mbox, अचिन्हित पूर्णांक pf,
		    अचिन्हित पूर्णांक vf, अचिन्हित पूर्णांक eqid);
पूर्णांक t4_ofld_eq_मुक्त(काष्ठा adapter *adap, अचिन्हित पूर्णांक mbox, अचिन्हित पूर्णांक pf,
		    अचिन्हित पूर्णांक vf, अचिन्हित पूर्णांक eqid);
पूर्णांक t4_sge_ctxt_flush(काष्ठा adapter *adap, अचिन्हित पूर्णांक mbox, पूर्णांक ctxt_type);
पूर्णांक t4_पढ़ो_sge_dbqसमयrs(काष्ठा adapter *adap, अचिन्हित पूर्णांक ndbqसमयrs,
			  u16 *dbqसमयrs);
व्योम t4_handle_get_port_info(काष्ठा port_info *pi, स्थिर __be64 *rpl);
पूर्णांक t4_update_port_info(काष्ठा port_info *pi);
पूर्णांक t4_get_link_params(काष्ठा port_info *pi, अचिन्हित पूर्णांक *link_okp,
		       अचिन्हित पूर्णांक *speedp, अचिन्हित पूर्णांक *mtup);
पूर्णांक t4_handle_fw_rpl(काष्ठा adapter *adap, स्थिर __be64 *rpl);
व्योम t4_db_full(काष्ठा adapter *adapter);
व्योम t4_db_dropped(काष्ठा adapter *adapter);
पूर्णांक t4_set_trace_filter(काष्ठा adapter *adapter, स्थिर काष्ठा trace_params *tp,
			पूर्णांक filter_index, पूर्णांक enable);
व्योम t4_get_trace_filter(काष्ठा adapter *adapter, काष्ठा trace_params *tp,
			 पूर्णांक filter_index, पूर्णांक *enabled);
पूर्णांक t4_fwaddrspace_ग_लिखो(काष्ठा adapter *adap, अचिन्हित पूर्णांक mbox,
			 u32 addr, u32 val);
व्योम t4_पढ़ो_pace_tbl(काष्ठा adapter *adap, अचिन्हित पूर्णांक pace_vals[NTX_SCHED]);
व्योम t4_get_tx_sched(काष्ठा adapter *adap, अचिन्हित पूर्णांक sched,
		     अचिन्हित पूर्णांक *kbps, अचिन्हित पूर्णांक *ipg, bool sleep_ok);
पूर्णांक t4_sge_ctxt_rd(काष्ठा adapter *adap, अचिन्हित पूर्णांक mbox, अचिन्हित पूर्णांक cid,
		   क्रमागत ctxt_type ctype, u32 *data);
पूर्णांक t4_sge_ctxt_rd_bd(काष्ठा adapter *adap, अचिन्हित पूर्णांक cid,
		      क्रमागत ctxt_type ctype, u32 *data);
पूर्णांक t4_sched_params(काष्ठा adapter *adapter, u8 type, u8 level, u8 mode,
		    u8 rateunit, u8 ratemode, u8 channel, u8 class,
		    u32 minrate, u32 maxrate, u16 weight, u16 pktsize,
		    u16 burstsize);
व्योम t4_sge_decode_idma_state(काष्ठा adapter *adapter, पूर्णांक state);
व्योम t4_idma_monitor_init(काष्ठा adapter *adapter,
			  काष्ठा sge_idma_monitor_state *idma);
व्योम t4_idma_monitor(काष्ठा adapter *adapter,
		     काष्ठा sge_idma_monitor_state *idma,
		     पूर्णांक hz, पूर्णांक ticks);
पूर्णांक t4_set_vf_mac_acl(काष्ठा adapter *adapter, अचिन्हित पूर्णांक vf,
		      अचिन्हित पूर्णांक naddr, u8 *addr);
व्योम t4_tp_pio_पढ़ो(काष्ठा adapter *adap, u32 *buff, u32 nregs,
		    u32 start_index, bool sleep_ok);
व्योम t4_tp_पंचांग_pio_पढ़ो(काष्ठा adapter *adap, u32 *buff, u32 nregs,
		       u32 start_index, bool sleep_ok);
व्योम t4_tp_mib_पढ़ो(काष्ठा adapter *adap, u32 *buff, u32 nregs,
		    u32 start_index, bool sleep_ok);

व्योम t4_uld_mem_मुक्त(काष्ठा adapter *adap);
पूर्णांक t4_uld_mem_alloc(काष्ठा adapter *adap);
व्योम t4_uld_clean_up(काष्ठा adapter *adap);
व्योम t4_रेजिस्टर_netevent_notअगरier(व्योम);
पूर्णांक t4_i2c_rd(काष्ठा adapter *adap, अचिन्हित पूर्णांक mbox, पूर्णांक port,
	      अचिन्हित पूर्णांक devid, अचिन्हित पूर्णांक offset,
	      अचिन्हित पूर्णांक len, u8 *buf);
पूर्णांक t4_load_boot(काष्ठा adapter *adap, u8 *boot_data,
		 अचिन्हित पूर्णांक boot_addr, अचिन्हित पूर्णांक size);
पूर्णांक t4_load_bootcfg(काष्ठा adapter *adap,
		    स्थिर u8 *cfg_data, अचिन्हित पूर्णांक size);
व्योम मुक्त_rspq_fl(काष्ठा adapter *adap, काष्ठा sge_rspq *rq, काष्ठा sge_fl *fl);
व्योम मुक्त_tx_desc(काष्ठा adapter *adap, काष्ठा sge_txq *q,
		  अचिन्हित पूर्णांक n, bool unmap);
व्योम cxgb4_eosw_txq_मुक्त_desc(काष्ठा adapter *adap, काष्ठा sge_eosw_txq *txq,
			      u32 ndesc);
पूर्णांक cxgb4_ethofld_send_flowc(काष्ठा net_device *dev, u32 eotid, u32 tc);
व्योम cxgb4_ethofld_restart(काष्ठा tasklet_काष्ठा *t);
पूर्णांक cxgb4_ethofld_rx_handler(काष्ठा sge_rspq *q, स्थिर __be64 *rsp,
			     स्थिर काष्ठा pkt_gl *si);
व्योम मुक्त_txq(काष्ठा adapter *adap, काष्ठा sge_txq *q);
व्योम cxgb4_reclaim_completed_tx(काष्ठा adapter *adap,
				काष्ठा sge_txq *q, bool unmap);
पूर्णांक cxgb4_map_skb(काष्ठा device *dev, स्थिर काष्ठा sk_buff *skb,
		  dma_addr_t *addr);
व्योम cxgb4_अंतरभूत_tx_skb(स्थिर काष्ठा sk_buff *skb, स्थिर काष्ठा sge_txq *q,
			 व्योम *pos);
व्योम cxgb4_ग_लिखो_sgl(स्थिर काष्ठा sk_buff *skb, काष्ठा sge_txq *q,
		     काष्ठा ulptx_sgl *sgl, u64 *end, अचिन्हित पूर्णांक start,
		     स्थिर dma_addr_t *addr);
व्योम cxgb4_ग_लिखो_partial_sgl(स्थिर काष्ठा sk_buff *skb, काष्ठा sge_txq *q,
			     काष्ठा ulptx_sgl *sgl, u64 *end,
			     स्थिर dma_addr_t *addr, u32 start, u32 send_len);
व्योम cxgb4_ring_tx_db(काष्ठा adapter *adap, काष्ठा sge_txq *q, पूर्णांक n);
पूर्णांक t4_set_vlan_acl(काष्ठा adapter *adap, अचिन्हित पूर्णांक mbox, अचिन्हित पूर्णांक vf,
		    u16 vlan);
पूर्णांक cxgb4_dcb_enabled(स्थिर काष्ठा net_device *dev);

पूर्णांक cxgb4_thermal_init(काष्ठा adapter *adap);
पूर्णांक cxgb4_thermal_हटाओ(काष्ठा adapter *adap);
पूर्णांक cxgb4_set_msix_aff(काष्ठा adapter *adap, अचिन्हित लघु vec,
		       cpumask_var_t *aff_mask, पूर्णांक idx);
व्योम cxgb4_clear_msix_aff(अचिन्हित लघु vec, cpumask_var_t aff_mask);

पूर्णांक cxgb4_change_mac(काष्ठा port_info *pi, अचिन्हित पूर्णांक viid,
		     पूर्णांक *tcam_idx, स्थिर u8 *addr,
		     bool persistent, u8 *smt_idx);

पूर्णांक cxgb4_alloc_mac_filt(काष्ठा adapter *adap, अचिन्हित पूर्णांक viid,
			 bool मुक्त, अचिन्हित पूर्णांक naddr,
			 स्थिर u8 **addr, u16 *idx,
			 u64 *hash, bool sleep_ok);
पूर्णांक cxgb4_मुक्त_mac_filt(काष्ठा adapter *adap, अचिन्हित पूर्णांक viid,
			अचिन्हित पूर्णांक naddr, स्थिर u8 **addr, bool sleep_ok);
पूर्णांक cxgb4_init_mps_ref_entries(काष्ठा adapter *adap);
व्योम cxgb4_मुक्त_mps_ref_entries(काष्ठा adapter *adap);
पूर्णांक cxgb4_alloc_encap_mac_filt(काष्ठा adapter *adap, अचिन्हित पूर्णांक viid,
			       स्थिर u8 *addr, स्थिर u8 *mask,
			       अचिन्हित पूर्णांक vni, अचिन्हित पूर्णांक vni_mask,
			       u8 dip_hit, u8 lookup_type, bool sleep_ok);
पूर्णांक cxgb4_मुक्त_encap_mac_filt(काष्ठा adapter *adap, अचिन्हित पूर्णांक viid,
			      पूर्णांक idx, bool sleep_ok);
पूर्णांक cxgb4_मुक्त_raw_mac_filt(काष्ठा adapter *adap,
			    अचिन्हित पूर्णांक viid,
			    स्थिर u8 *addr,
			    स्थिर u8 *mask,
			    अचिन्हित पूर्णांक idx,
			    u8 lookup_type,
			    u8 port_id,
			    bool sleep_ok);
पूर्णांक cxgb4_alloc_raw_mac_filt(काष्ठा adapter *adap,
			     अचिन्हित पूर्णांक viid,
			     स्थिर u8 *addr,
			     स्थिर u8 *mask,
			     अचिन्हित पूर्णांक idx,
			     u8 lookup_type,
			     u8 port_id,
			     bool sleep_ok);
पूर्णांक cxgb4_update_mac_filt(काष्ठा port_info *pi, अचिन्हित पूर्णांक viid,
			  पूर्णांक *tcam_idx, स्थिर u8 *addr,
			  bool persistent, u8 *smt_idx);
पूर्णांक cxgb4_get_msix_idx_from_bmap(काष्ठा adapter *adap);
व्योम cxgb4_मुक्त_msix_idx_in_bmap(काष्ठा adapter *adap, u32 msix_idx);
व्योम cxgb4_enable_rx(काष्ठा adapter *adap, काष्ठा sge_rspq *q);
व्योम cxgb4_quiesce_rx(काष्ठा sge_rspq *q);
पूर्णांक cxgb4_port_mirror_alloc(काष्ठा net_device *dev);
व्योम cxgb4_port_mirror_मुक्त(काष्ठा net_device *dev);
#अगर IS_ENABLED(CONFIG_CHELSIO_TLS_DEVICE)
पूर्णांक cxgb4_set_ktls_feature(काष्ठा adapter *adap, bool enable);
#पूर्ण_अगर
#पूर्ण_अगर /* __CXGB4_H__ */
