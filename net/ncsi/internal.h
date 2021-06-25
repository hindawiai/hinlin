<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright Gavin Shan, IBM Corporation 2016.
 */

#अगर_अघोषित __NCSI_INTERNAL_H__
#घोषणा __NCSI_INTERNAL_H__

क्रमागत अणु
	NCSI_CAP_BASE		= 0,
	NCSI_CAP_GENERIC	= 0,
	NCSI_CAP_BC,
	NCSI_CAP_MC,
	NCSI_CAP_BUFFER,
	NCSI_CAP_AEN,
	NCSI_CAP_VLAN,
	NCSI_CAP_MAX
पूर्ण;

क्रमागत अणु
	NCSI_CAP_GENERIC_HWA             = 0x01, /* HW arbitration           */
	NCSI_CAP_GENERIC_HDS             = 0x02, /* HNC driver status change */
	NCSI_CAP_GENERIC_FC              = 0x04, /* HNC to MC flow control   */
	NCSI_CAP_GENERIC_FC1             = 0x08, /* MC to HNC flow control   */
	NCSI_CAP_GENERIC_MC              = 0x10, /* Global MC filtering      */
	NCSI_CAP_GENERIC_HWA_UNKNOWN     = 0x00, /* Unknown HW arbitration   */
	NCSI_CAP_GENERIC_HWA_SUPPORT     = 0x20, /* Supported HW arbitration */
	NCSI_CAP_GENERIC_HWA_NOT_SUPPORT = 0x40, /* No HW arbitration        */
	NCSI_CAP_GENERIC_HWA_RESERVED    = 0x60, /* Reserved HW arbitration  */
	NCSI_CAP_GENERIC_HWA_MASK        = 0x60, /* Mask क्रम HW arbitration  */
	NCSI_CAP_GENERIC_MASK            = 0x7f,
	NCSI_CAP_BC_ARP                  = 0x01, /* ARP packet filtering     */
	NCSI_CAP_BC_DHCPC                = 0x02, /* DHCP client filtering    */
	NCSI_CAP_BC_DHCPS                = 0x04, /* DHCP server filtering    */
	NCSI_CAP_BC_NETBIOS              = 0x08, /* NetBIOS packet filtering */
	NCSI_CAP_BC_MASK                 = 0x0f,
	NCSI_CAP_MC_IPV6_NEIGHBOR        = 0x01, /* IPv6 neighbor filtering  */
	NCSI_CAP_MC_IPV6_ROUTER          = 0x02, /* IPv6 router filering     */
	NCSI_CAP_MC_DHCPV6_RELAY         = 0x04, /* DHCPv6 relay / server MC */
	NCSI_CAP_MC_DHCPV6_WELL_KNOWN    = 0x08, /* DHCPv6 well-known MC     */
	NCSI_CAP_MC_IPV6_MLD             = 0x10, /* IPv6 MLD filtering       */
	NCSI_CAP_MC_IPV6_NEIGHBOR_S      = 0x20, /* IPv6 neighbour filtering */
	NCSI_CAP_MC_MASK                 = 0x3f,
	NCSI_CAP_AEN_LSC                 = 0x01, /* Link status change       */
	NCSI_CAP_AEN_CR                  = 0x02, /* Configuration required   */
	NCSI_CAP_AEN_HDS                 = 0x04, /* HNC driver status        */
	NCSI_CAP_AEN_MASK                = 0x07,
	NCSI_CAP_VLAN_ONLY               = 0x01, /* Filter VLAN packet only  */
	NCSI_CAP_VLAN_NO                 = 0x02, /* Filter VLAN and non-VLAN */
	NCSI_CAP_VLAN_ANY                = 0x04, /* Filter Any-and-non-VLAN  */
	NCSI_CAP_VLAN_MASK               = 0x07
पूर्ण;

क्रमागत अणु
	NCSI_MODE_BASE		= 0,
	NCSI_MODE_ENABLE	= 0,
	NCSI_MODE_TX_ENABLE,
	NCSI_MODE_LINK,
	NCSI_MODE_VLAN,
	NCSI_MODE_BC,
	NCSI_MODE_MC,
	NCSI_MODE_AEN,
	NCSI_MODE_FC,
	NCSI_MODE_MAX
पूर्ण;

/* Supported media status bits क्रम Mellanox Mac affinity command.
 * Bit (0-2) क्रम dअगरferent protocol support; Bit 1 क्रम RBT support,
 * bit 1 क्रम SMBUS support and bit 2 क्रम PCIE support. Bit (3-5)
 * क्रम dअगरferent protocol availability. Bit 4 क्रम RBT, bit 4 क्रम
 * SMBUS and bit 5 क्रम PCIE.
 */
क्रमागत अणु
	MLX_MC_RBT_SUPPORT  = 0x01, /* MC supports RBT         */
	MLX_MC_RBT_AVL      = 0x08, /* RBT medium is available */
पूर्ण;

/* OEM Venकरोr Manufacture ID */
#घोषणा NCSI_OEM_MFR_MLX_ID             0x8119
#घोषणा NCSI_OEM_MFR_BCM_ID             0x113d
/* Broadcom specअगरic OEM Command */
#घोषणा NCSI_OEM_BCM_CMD_GMA            0x01   /* CMD ID क्रम Get MAC */
/* Mellanox specअगरic OEM Command */
#घोषणा NCSI_OEM_MLX_CMD_GMA            0x00   /* CMD ID क्रम Get MAC */
#घोषणा NCSI_OEM_MLX_CMD_GMA_PARAM      0x1b   /* Parameter क्रम GMA  */
#घोषणा NCSI_OEM_MLX_CMD_SMAF           0x01   /* CMD ID क्रम Set MC Affinity */
#घोषणा NCSI_OEM_MLX_CMD_SMAF_PARAM     0x07   /* Parameter क्रम SMAF         */
/* OEM Command payload lengths*/
#घोषणा NCSI_OEM_BCM_CMD_GMA_LEN        12
#घोषणा NCSI_OEM_MLX_CMD_GMA_LEN        8
#घोषणा NCSI_OEM_MLX_CMD_SMAF_LEN        60
/* Offset in OEM request */
#घोषणा MLX_SMAF_MAC_ADDR_OFFSET         8     /* Offset क्रम MAC in SMAF    */
#घोषणा MLX_SMAF_MED_SUPPORT_OFFSET      14    /* Offset क्रम medium in SMAF */
/* Mac address offset in OEM response */
#घोषणा BCM_MAC_ADDR_OFFSET             28
#घोषणा MLX_MAC_ADDR_OFFSET             8


काष्ठा ncsi_channel_version अणु
	u32 version;		/* Supported BCD encoded NCSI version */
	u32 alpha2;		/* Supported BCD encoded NCSI version */
	u8  fw_name[12];	/* Firmware name string                */
	u32 fw_version;		/* Firmware version                   */
	u16 pci_ids[4];		/* PCI identअगरication                 */
	u32 mf_id;		/* Manufacture ID                     */
पूर्ण;

काष्ठा ncsi_channel_cap अणु
	u32 index;	/* Index of channel capabilities */
	u32 cap;	/* NCSI channel capability       */
पूर्ण;

काष्ठा ncsi_channel_mode अणु
	u32 index;	/* Index of channel modes      */
	u32 enable;	/* Enabled or disabled         */
	u32 size;	/* Valid entries in ncm_data[] */
	u32 data[8];	/* Data entries                */
पूर्ण;

काष्ठा ncsi_channel_mac_filter अणु
	u8	n_uc;
	u8	n_mc;
	u8	n_mixed;
	u64	biपंचांगap;
	अचिन्हित अक्षर	*addrs;
पूर्ण;

काष्ठा ncsi_channel_vlan_filter अणु
	u8	n_vids;
	u64	biपंचांगap;
	u16	*vids;
पूर्ण;

काष्ठा ncsi_channel_stats अणु
	u32 hnc_cnt_hi;		/* Counter cleared            */
	u32 hnc_cnt_lo;		/* Counter cleared            */
	u32 hnc_rx_bytes;	/* Rx bytes                   */
	u32 hnc_tx_bytes;	/* Tx bytes                   */
	u32 hnc_rx_uc_pkts;	/* Rx UC packets              */
	u32 hnc_rx_mc_pkts;     /* Rx MC packets              */
	u32 hnc_rx_bc_pkts;	/* Rx BC packets              */
	u32 hnc_tx_uc_pkts;	/* Tx UC packets              */
	u32 hnc_tx_mc_pkts;	/* Tx MC packets              */
	u32 hnc_tx_bc_pkts;	/* Tx BC packets              */
	u32 hnc_fcs_err;	/* FCS errors                 */
	u32 hnc_align_err;	/* Alignment errors           */
	u32 hnc_false_carrier;	/* False carrier detection    */
	u32 hnc_runt_pkts;	/* Rx runt packets            */
	u32 hnc_jabber_pkts;	/* Rx jabber packets          */
	u32 hnc_rx_छोड़ो_xon;	/* Rx छोड़ो XON frames        */
	u32 hnc_rx_छोड़ो_xoff;	/* Rx XOFF frames             */
	u32 hnc_tx_छोड़ो_xon;	/* Tx XON frames              */
	u32 hnc_tx_छोड़ो_xoff;	/* Tx XOFF frames             */
	u32 hnc_tx_s_collision;	/* Single collision frames    */
	u32 hnc_tx_m_collision;	/* Multiple collision frames  */
	u32 hnc_l_collision;	/* Late collision frames      */
	u32 hnc_e_collision;	/* Excessive collision frames */
	u32 hnc_rx_ctl_frames;	/* Rx control frames          */
	u32 hnc_rx_64_frames;	/* Rx 64-bytes frames         */
	u32 hnc_rx_127_frames;	/* Rx 65-127 bytes frames     */
	u32 hnc_rx_255_frames;	/* Rx 128-255 bytes frames    */
	u32 hnc_rx_511_frames;	/* Rx 256-511 bytes frames    */
	u32 hnc_rx_1023_frames;	/* Rx 512-1023 bytes frames   */
	u32 hnc_rx_1522_frames;	/* Rx 1024-1522 bytes frames  */
	u32 hnc_rx_9022_frames;	/* Rx 1523-9022 bytes frames  */
	u32 hnc_tx_64_frames;	/* Tx 64-bytes frames         */
	u32 hnc_tx_127_frames;	/* Tx 65-127 bytes frames     */
	u32 hnc_tx_255_frames;	/* Tx 128-255 bytes frames    */
	u32 hnc_tx_511_frames;	/* Tx 256-511 bytes frames    */
	u32 hnc_tx_1023_frames;	/* Tx 512-1023 bytes frames   */
	u32 hnc_tx_1522_frames;	/* Tx 1024-1522 bytes frames  */
	u32 hnc_tx_9022_frames;	/* Tx 1523-9022 bytes frames  */
	u32 hnc_rx_valid_bytes;	/* Rx valid bytes             */
	u32 hnc_rx_runt_pkts;	/* Rx error runt packets      */
	u32 hnc_rx_jabber_pkts;	/* Rx error jabber packets    */
	u32 ncsi_rx_cmds;	/* Rx NCSI commands           */
	u32 ncsi_dropped_cmds;	/* Dropped commands           */
	u32 ncsi_cmd_type_errs;	/* Command type errors        */
	u32 ncsi_cmd_csum_errs;	/* Command checksum errors    */
	u32 ncsi_rx_pkts;	/* Rx NCSI packets            */
	u32 ncsi_tx_pkts;	/* Tx NCSI packets            */
	u32 ncsi_tx_aen_pkts;	/* Tx AEN packets             */
	u32 pt_tx_pkts;		/* Tx packets                 */
	u32 pt_tx_dropped;	/* Tx dropped packets         */
	u32 pt_tx_channel_err;	/* Tx channel errors          */
	u32 pt_tx_us_err;	/* Tx undersize errors        */
	u32 pt_rx_pkts;		/* Rx packets                 */
	u32 pt_rx_dropped;	/* Rx dropped packets         */
	u32 pt_rx_channel_err;	/* Rx channel errors          */
	u32 pt_rx_us_err;	/* Rx undersize errors        */
	u32 pt_rx_os_err;	/* Rx oversize errors         */
पूर्ण;

काष्ठा ncsi_dev_priv;
काष्ठा ncsi_package;

#घोषणा NCSI_PACKAGE_SHIFT	5
#घोषणा NCSI_PACKAGE_INDEX(c)	(((c) >> NCSI_PACKAGE_SHIFT) & 0x7)
#घोषणा NCSI_RESERVED_CHANNEL	0x1f
#घोषणा NCSI_CHANNEL_INDEX(c)	((c) & ((1 << NCSI_PACKAGE_SHIFT) - 1))
#घोषणा NCSI_TO_CHANNEL(p, c)	(((p) << NCSI_PACKAGE_SHIFT) | (c))
#घोषणा NCSI_MAX_PACKAGE	8
#घोषणा NCSI_MAX_CHANNEL	32

काष्ठा ncsi_channel अणु
	अचिन्हित अक्षर               id;
	पूर्णांक                         state;
#घोषणा NCSI_CHANNEL_INACTIVE		1
#घोषणा NCSI_CHANNEL_ACTIVE		2
#घोषणा NCSI_CHANNEL_INVISIBLE		3
	bool                        reconfigure_needed;
	spinlock_t                  lock;	/* Protect filters etc */
	काष्ठा ncsi_package         *package;
	काष्ठा ncsi_channel_version version;
	काष्ठा ncsi_channel_cap	    caps[NCSI_CAP_MAX];
	काष्ठा ncsi_channel_mode    modes[NCSI_MODE_MAX];
	/* Filtering Settings */
	काष्ठा ncsi_channel_mac_filter	mac_filter;
	काष्ठा ncsi_channel_vlan_filter	vlan_filter;
	काष्ठा ncsi_channel_stats   stats;
	काष्ठा अणु
		काष्ठा समयr_list   समयr;
		bool                enabled;
		अचिन्हित पूर्णांक        state;
#घोषणा NCSI_CHANNEL_MONITOR_START	0
#घोषणा NCSI_CHANNEL_MONITOR_RETRY	1
#घोषणा NCSI_CHANNEL_MONITOR_WAIT	2
#घोषणा NCSI_CHANNEL_MONITOR_WAIT_MAX	5
	पूर्ण monitor;
	काष्ठा list_head            node;
	काष्ठा list_head            link;
पूर्ण;

काष्ठा ncsi_package अणु
	अचिन्हित अक्षर        id;          /* NCSI 3-bits package ID */
	अचिन्हित अक्षर        uuid[16];    /* UUID                   */
	काष्ठा ncsi_dev_priv *ndp;        /* NCSI device            */
	spinlock_t           lock;        /* Protect the package    */
	अचिन्हित पूर्णांक         channel_num; /* Number of channels     */
	काष्ठा list_head     channels;    /* List of chanels        */
	काष्ठा list_head     node;        /* Form list of packages  */

	bool                 multi_channel; /* Enable multiple channels  */
	u32                  channel_whitelist; /* Channels to configure */
	काष्ठा ncsi_channel  *preferred_channel; /* Primary channel      */
पूर्ण;

काष्ठा ncsi_request अणु
	अचिन्हित अक्षर        id;      /* Request ID - 0 to 255           */
	bool                 used;    /* Request that has been asचिन्हित  */
	अचिन्हित पूर्णांक         flags;   /* NCSI request property           */
#घोषणा NCSI_REQ_FLAG_EVENT_DRIVEN	1
#घोषणा NCSI_REQ_FLAG_NETLINK_DRIVEN	2
	काष्ठा ncsi_dev_priv *ndp;    /* Associated NCSI device          */
	काष्ठा sk_buff       *cmd;    /* Associated NCSI command packet  */
	काष्ठा sk_buff       *rsp;    /* Associated NCSI response packet */
	काष्ठा समयr_list    समयr;   /* Timer on रुकोing क्रम response   */
	bool                 enabled; /* Time has been enabled or not    */
	u32                  snd_seq;     /* netlink sending sequence number */
	u32                  snd_portid;  /* netlink portid of sender        */
	काष्ठा nlmsghdr      nlhdr;       /* netlink message header          */
पूर्ण;

क्रमागत अणु
	ncsi_dev_state_major		= 0xff00,
	ncsi_dev_state_minor		= 0x00ff,
	ncsi_dev_state_probe_deselect	= 0x0201,
	ncsi_dev_state_probe_package,
	ncsi_dev_state_probe_channel,
	ncsi_dev_state_probe_mlx_gma,
	ncsi_dev_state_probe_mlx_smaf,
	ncsi_dev_state_probe_cis,
	ncsi_dev_state_probe_gvi,
	ncsi_dev_state_probe_gc,
	ncsi_dev_state_probe_gls,
	ncsi_dev_state_probe_dp,
	ncsi_dev_state_config_sp	= 0x0301,
	ncsi_dev_state_config_cis,
	ncsi_dev_state_config_oem_gma,
	ncsi_dev_state_config_clear_vids,
	ncsi_dev_state_config_svf,
	ncsi_dev_state_config_ev,
	ncsi_dev_state_config_sma,
	ncsi_dev_state_config_ebf,
	ncsi_dev_state_config_dgmf,
	ncsi_dev_state_config_ecnt,
	ncsi_dev_state_config_ec,
	ncsi_dev_state_config_ae,
	ncsi_dev_state_config_gls,
	ncsi_dev_state_config_करोne,
	ncsi_dev_state_suspend_select	= 0x0401,
	ncsi_dev_state_suspend_gls,
	ncsi_dev_state_suspend_dcnt,
	ncsi_dev_state_suspend_dc,
	ncsi_dev_state_suspend_deselect,
	ncsi_dev_state_suspend_करोne
पूर्ण;

काष्ठा vlan_vid अणु
	काष्ठा list_head list;
	__be16 proto;
	u16 vid;
पूर्ण;

काष्ठा ncsi_dev_priv अणु
	काष्ठा ncsi_dev     ndev;            /* Associated NCSI device     */
	अचिन्हित पूर्णांक        flags;           /* NCSI device flags          */
#घोषणा NCSI_DEV_PROBED		1            /* Finalized NCSI topology    */
#घोषणा NCSI_DEV_HWA		2            /* Enabled HW arbitration     */
#घोषणा NCSI_DEV_RESHUFFLE	4
#घोषणा NCSI_DEV_RESET		8            /* Reset state of NC          */
	अचिन्हित पूर्णांक        gma_flag;        /* OEM GMA flag               */
	spinlock_t          lock;            /* Protect the NCSI device    */
	अचिन्हित पूर्णांक        package_probe_id;/* Current ID during probe    */
	अचिन्हित पूर्णांक        package_num;     /* Number of packages         */
	काष्ठा list_head    packages;        /* List of packages           */
	काष्ठा ncsi_channel *hot_channel;    /* Channel was ever active    */
	काष्ठा ncsi_request requests[256];   /* Request table              */
	अचिन्हित पूर्णांक        request_id;      /* Last used request ID       */
#घोषणा NCSI_REQ_START_IDX	1
	अचिन्हित पूर्णांक        pending_req_num; /* Number of pending requests */
	काष्ठा ncsi_package *active_package; /* Currently handled package  */
	काष्ठा ncsi_channel *active_channel; /* Currently handled channel  */
	काष्ठा list_head    channel_queue;   /* Config queue of channels   */
	काष्ठा work_काष्ठा  work;            /* For channel management     */
	काष्ठा packet_type  ptype;           /* NCSI packet Rx handler     */
	काष्ठा list_head    node;            /* Form NCSI device list      */
#घोषणा NCSI_MAX_VLAN_VIDS	15
	काष्ठा list_head    vlan_vids;       /* List of active VLAN IDs */

	bool                multi_package;   /* Enable multiple packages   */
	bool                mlx_multi_host;  /* Enable multi host Mellanox */
	u32                 package_whitelist; /* Packages to configure    */
पूर्ण;

काष्ठा ncsi_cmd_arg अणु
	काष्ठा ncsi_dev_priv *ndp;        /* Associated NCSI device        */
	अचिन्हित अक्षर        type;        /* Command in the NCSI packet    */
	अचिन्हित अक्षर        id;          /* Request ID (sequence number)  */
	अचिन्हित अक्षर        package;     /* Destination package ID        */
	अचिन्हित अक्षर        channel;     /* Detination channel ID or 0x1f */
	अचिन्हित लघु       payload;     /* Command packet payload length */
	अचिन्हित पूर्णांक         req_flags;   /* NCSI request properties       */
	जोड़ अणु
		अचिन्हित अक्षर  bytes[16]; /* Command packet specअगरic data  */
		अचिन्हित लघु words[8];
		अचिन्हित पूर्णांक   dwords[4];
	पूर्ण;
	अचिन्हित अक्षर        *data;       /* NCSI OEM data                 */
	काष्ठा genl_info     *info;       /* Netlink inक्रमmation           */
पूर्ण;

बाह्य काष्ठा list_head ncsi_dev_list;
बाह्य spinlock_t ncsi_dev_lock;

#घोषणा TO_NCSI_DEV_PRIV(nd) \
	container_of(nd, काष्ठा ncsi_dev_priv, ndev)
#घोषणा NCSI_FOR_EACH_DEV(ndp) \
	list_क्रम_each_entry_rcu(ndp, &ncsi_dev_list, node)
#घोषणा NCSI_FOR_EACH_PACKAGE(ndp, np) \
	list_क्रम_each_entry_rcu(np, &ndp->packages, node)
#घोषणा NCSI_FOR_EACH_CHANNEL(np, nc) \
	list_क्रम_each_entry_rcu(nc, &np->channels, node)

/* Resources */
पूर्णांक ncsi_reset_dev(काष्ठा ncsi_dev *nd);
व्योम ncsi_start_channel_monitor(काष्ठा ncsi_channel *nc);
व्योम ncsi_stop_channel_monitor(काष्ठा ncsi_channel *nc);
काष्ठा ncsi_channel *ncsi_find_channel(काष्ठा ncsi_package *np,
				       अचिन्हित अक्षर id);
काष्ठा ncsi_channel *ncsi_add_channel(काष्ठा ncsi_package *np,
				      अचिन्हित अक्षर id);
काष्ठा ncsi_package *ncsi_find_package(काष्ठा ncsi_dev_priv *ndp,
				       अचिन्हित अक्षर id);
काष्ठा ncsi_package *ncsi_add_package(काष्ठा ncsi_dev_priv *ndp,
				      अचिन्हित अक्षर id);
व्योम ncsi_हटाओ_package(काष्ठा ncsi_package *np);
व्योम ncsi_find_package_and_channel(काष्ठा ncsi_dev_priv *ndp,
				   अचिन्हित अक्षर id,
				   काष्ठा ncsi_package **np,
				   काष्ठा ncsi_channel **nc);
काष्ठा ncsi_request *ncsi_alloc_request(काष्ठा ncsi_dev_priv *ndp,
					अचिन्हित पूर्णांक req_flags);
व्योम ncsi_मुक्त_request(काष्ठा ncsi_request *nr);
काष्ठा ncsi_dev *ncsi_find_dev(काष्ठा net_device *dev);
पूर्णांक ncsi_process_next_channel(काष्ठा ncsi_dev_priv *ndp);
bool ncsi_channel_has_link(काष्ठा ncsi_channel *channel);
bool ncsi_channel_is_last(काष्ठा ncsi_dev_priv *ndp,
			  काष्ठा ncsi_channel *channel);
पूर्णांक ncsi_update_tx_channel(काष्ठा ncsi_dev_priv *ndp,
			   काष्ठा ncsi_package *np,
			   काष्ठा ncsi_channel *disable,
			   काष्ठा ncsi_channel *enable);

/* Packet handlers */
u32 ncsi_calculate_checksum(अचिन्हित अक्षर *data, पूर्णांक len);
पूर्णांक ncsi_xmit_cmd(काष्ठा ncsi_cmd_arg *nca);
पूर्णांक ncsi_rcv_rsp(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
		 काष्ठा packet_type *pt, काष्ठा net_device *orig_dev);
पूर्णांक ncsi_aen_handler(काष्ठा ncsi_dev_priv *ndp, काष्ठा sk_buff *skb);

#पूर्ण_अगर /* __NCSI_INTERNAL_H__ */
