<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright Gavin Shan, IBM Corporation 2016.
 */

#अगर_अघोषित __NCSI_PKT_H__
#घोषणा __NCSI_PKT_H__

काष्ठा ncsi_pkt_hdr अणु
	अचिन्हित अक्षर mc_id;        /* Management controller ID */
	अचिन्हित अक्षर revision;     /* NCSI version - 0x01      */
	अचिन्हित अक्षर reserved;     /* Reserved                 */
	अचिन्हित अक्षर id;           /* Packet sequence number   */
	अचिन्हित अक्षर type;         /* Packet type              */
	अचिन्हित अक्षर channel;      /* Network controller ID    */
	__be16        length;       /* Payload length           */
	__be32        reserved1[2]; /* Reserved                 */
पूर्ण;

काष्ठा ncsi_cmd_pkt_hdr अणु
	काष्ठा ncsi_pkt_hdr common; /* Common NCSI packet header */
पूर्ण;

काष्ठा ncsi_rsp_pkt_hdr अणु
	काष्ठा ncsi_pkt_hdr common; /* Common NCSI packet header */
	__be16              code;   /* Response code             */
	__be16              reason; /* Response reason           */
पूर्ण;

काष्ठा ncsi_aen_pkt_hdr अणु
	काष्ठा ncsi_pkt_hdr common;       /* Common NCSI packet header */
	अचिन्हित अक्षर       reserved2[3]; /* Reserved                  */
	अचिन्हित अक्षर       type;         /* AEN packet type           */
पूर्ण;

/* NCSI common command packet */
काष्ठा ncsi_cmd_pkt अणु
	काष्ठा ncsi_cmd_pkt_hdr cmd;      /* Command header */
	__be32                  checksum; /* Checksum       */
	अचिन्हित अक्षर           pad[26];
पूर्ण;

काष्ठा ncsi_rsp_pkt अणु
	काष्ठा ncsi_rsp_pkt_hdr rsp;      /* Response header */
	__be32                  checksum; /* Checksum        */
	अचिन्हित अक्षर           pad[22];
पूर्ण;

/* Select Package */
काष्ठा ncsi_cmd_sp_pkt अणु
	काष्ठा ncsi_cmd_pkt_hdr cmd;            /* Command header */
	अचिन्हित अक्षर           reserved[3];    /* Reserved       */
	अचिन्हित अक्षर           hw_arbitration; /* HW arbitration */
	__be32                  checksum;       /* Checksum       */
	अचिन्हित अक्षर           pad[22];
पूर्ण;

/* Disable Channel */
काष्ठा ncsi_cmd_dc_pkt अणु
	काष्ठा ncsi_cmd_pkt_hdr cmd;         /* Command header  */
	अचिन्हित अक्षर           reserved[3]; /* Reserved        */
	अचिन्हित अक्षर           ald;         /* Allow link करोwn */
	__be32                  checksum;    /* Checksum        */
	अचिन्हित अक्षर           pad[22];
पूर्ण;

/* Reset Channel */
काष्ठा ncsi_cmd_rc_pkt अणु
	काष्ठा ncsi_cmd_pkt_hdr cmd;      /* Command header */
	__be32                  reserved; /* Reserved       */
	__be32                  checksum; /* Checksum       */
	अचिन्हित अक्षर           pad[22];
पूर्ण;

/* AEN Enable */
काष्ठा ncsi_cmd_ae_pkt अणु
	काष्ठा ncsi_cmd_pkt_hdr cmd;         /* Command header   */
	अचिन्हित अक्षर           reserved[3]; /* Reserved         */
	अचिन्हित अक्षर           mc_id;       /* MC ID            */
	__be32                  mode;        /* AEN working mode */
	__be32                  checksum;    /* Checksum         */
	अचिन्हित अक्षर           pad[18];
पूर्ण;

/* Set Link */
काष्ठा ncsi_cmd_sl_pkt अणु
	काष्ठा ncsi_cmd_pkt_hdr cmd;      /* Command header    */
	__be32                  mode;     /* Link working mode */
	__be32                  oem_mode; /* OEM link mode     */
	__be32                  checksum; /* Checksum          */
	अचिन्हित अक्षर           pad[18];
पूर्ण;

/* Set VLAN Filter */
काष्ठा ncsi_cmd_svf_pkt अणु
	काष्ठा ncsi_cmd_pkt_hdr cmd;       /* Command header    */
	__be16                  reserved;  /* Reserved          */
	__be16                  vlan;      /* VLAN ID           */
	__be16                  reserved1; /* Reserved          */
	अचिन्हित अक्षर           index;     /* VLAN table index  */
	अचिन्हित अक्षर           enable;    /* Enable or disable */
	__be32                  checksum;  /* Checksum          */
	अचिन्हित अक्षर           pad[18];
पूर्ण;

/* Enable VLAN */
काष्ठा ncsi_cmd_ev_pkt अणु
	काष्ठा ncsi_cmd_pkt_hdr cmd;         /* Command header   */
	अचिन्हित अक्षर           reserved[3]; /* Reserved         */
	अचिन्हित अक्षर           mode;        /* VLAN filter mode */
	__be32                  checksum;    /* Checksum         */
	अचिन्हित अक्षर           pad[22];
पूर्ण;

/* Set MAC Address */
काष्ठा ncsi_cmd_sma_pkt अणु
	काष्ठा ncsi_cmd_pkt_hdr cmd;      /* Command header          */
	अचिन्हित अक्षर           mac[6];   /* MAC address             */
	अचिन्हित अक्षर           index;    /* MAC table index         */
	अचिन्हित अक्षर           at_e;     /* Addr type and operation */
	__be32                  checksum; /* Checksum                */
	अचिन्हित अक्षर           pad[18];
पूर्ण;

/* Enable Broadcast Filter */
काष्ठा ncsi_cmd_ebf_pkt अणु
	काष्ठा ncsi_cmd_pkt_hdr cmd;      /* Command header */
	__be32                  mode;     /* Filter mode    */
	__be32                  checksum; /* Checksum       */
	अचिन्हित अक्षर           pad[22];
पूर्ण;

/* Enable Global Multicast Filter */
काष्ठा ncsi_cmd_egmf_pkt अणु
	काष्ठा ncsi_cmd_pkt_hdr cmd;      /* Command header */
	__be32                  mode;     /* Global MC mode */
	__be32                  checksum; /* Checksum       */
	अचिन्हित अक्षर           pad[22];
पूर्ण;

/* Set NCSI Flow Control */
काष्ठा ncsi_cmd_snfc_pkt अणु
	काष्ठा ncsi_cmd_pkt_hdr cmd;         /* Command header    */
	अचिन्हित अक्षर           reserved[3]; /* Reserved          */
	अचिन्हित अक्षर           mode;        /* Flow control mode */
	__be32                  checksum;    /* Checksum          */
	अचिन्हित अक्षर           pad[22];
पूर्ण;

/* OEM Request Command as per NCSI Specअगरication */
काष्ठा ncsi_cmd_oem_pkt अणु
	काष्ठा ncsi_cmd_pkt_hdr cmd;         /* Command header    */
	__be32                  mfr_id;      /* Manufacture ID    */
	अचिन्हित अक्षर           data[];      /* OEM Payload Data  */
पूर्ण;

/* OEM Response Packet as per NCSI Specअगरication */
काष्ठा ncsi_rsp_oem_pkt अणु
	काष्ठा ncsi_rsp_pkt_hdr rsp;         /* Command header    */
	__be32                  mfr_id;      /* Manufacture ID    */
	अचिन्हित अक्षर           data[];      /* Payload data      */
पूर्ण;

/* Mellanox Response Data */
काष्ठा ncsi_rsp_oem_mlx_pkt अणु
	अचिन्हित अक्षर           cmd_rev;     /* Command Revision  */
	अचिन्हित अक्षर           cmd;         /* Command ID        */
	अचिन्हित अक्षर           param;       /* Parameter         */
	अचिन्हित अक्षर           optional;    /* Optional data     */
	अचिन्हित अक्षर           data[];      /* Data              */
पूर्ण;

/* Broadcom Response Data */
काष्ठा ncsi_rsp_oem_bcm_pkt अणु
	अचिन्हित अक्षर           ver;         /* Payload Version   */
	अचिन्हित अक्षर           type;        /* OEM Command type  */
	__be16                  len;         /* Payload Length    */
	अचिन्हित अक्षर           data[];      /* Cmd specअगरic Data */
पूर्ण;

/* Get Link Status */
काष्ठा ncsi_rsp_gls_pkt अणु
	काष्ठा ncsi_rsp_pkt_hdr rsp;        /* Response header   */
	__be32                  status;     /* Link status       */
	__be32                  other;      /* Other indications */
	__be32                  oem_status; /* OEM link status   */
	__be32                  checksum;
	अचिन्हित अक्षर           pad[10];
पूर्ण;

/* Get Version ID */
काष्ठा ncsi_rsp_gvi_pkt अणु
	काष्ठा ncsi_rsp_pkt_hdr rsp;          /* Response header */
	__be32                  ncsi_version; /* NCSI version    */
	अचिन्हित अक्षर           reserved[3];  /* Reserved        */
	अचिन्हित अक्षर           alpha2;       /* NCSI version    */
	अचिन्हित अक्षर           fw_name[12];  /* f/w name string */
	__be32                  fw_version;   /* f/w version     */
	__be16                  pci_ids[4];   /* PCI IDs         */
	__be32                  mf_id;        /* Manufacture ID  */
	__be32                  checksum;
पूर्ण;

/* Get Capabilities */
काष्ठा ncsi_rsp_gc_pkt अणु
	काष्ठा ncsi_rsp_pkt_hdr rsp;         /* Response header   */
	__be32                  cap;         /* Capabilities      */
	__be32                  bc_cap;      /* Broadcast cap     */
	__be32                  mc_cap;      /* Multicast cap     */
	__be32                  buf_cap;     /* Buffering cap     */
	__be32                  aen_cap;     /* AEN cap           */
	अचिन्हित अक्षर           vlan_cnt;    /* VLAN filter count */
	अचिन्हित अक्षर           mixed_cnt;   /* Mix filter count  */
	अचिन्हित अक्षर           mc_cnt;      /* MC filter count   */
	अचिन्हित अक्षर           uc_cnt;      /* UC filter count   */
	अचिन्हित अक्षर           reserved[2]; /* Reserved          */
	अचिन्हित अक्षर           vlan_mode;   /* VLAN mode         */
	अचिन्हित अक्षर           channel_cnt; /* Channel count     */
	__be32                  checksum;    /* Checksum          */
पूर्ण;

/* Get Parameters */
काष्ठा ncsi_rsp_gp_pkt अणु
	काष्ठा ncsi_rsp_pkt_hdr rsp;          /* Response header       */
	अचिन्हित अक्षर           mac_cnt;      /* Number of MAC addr    */
	अचिन्हित अक्षर           reserved[2];  /* Reserved              */
	अचिन्हित अक्षर           mac_enable;   /* MAC addr enable flags */
	अचिन्हित अक्षर           vlan_cnt;     /* VLAN tag count        */
	अचिन्हित अक्षर           reserved1;    /* Reserved              */
	__be16                  vlan_enable;  /* VLAN tag enable flags */
	__be32                  link_mode;    /* Link setting          */
	__be32                  bc_mode;      /* BC filter mode        */
	__be32                  valid_modes;  /* Valid mode parameters */
	अचिन्हित अक्षर           vlan_mode;    /* VLAN mode             */
	अचिन्हित अक्षर           fc_mode;      /* Flow control mode     */
	अचिन्हित अक्षर           reserved2[2]; /* Reserved              */
	__be32                  aen_mode;     /* AEN mode              */
	अचिन्हित अक्षर           mac[6];       /* Supported MAC addr    */
	__be16                  vlan;         /* Supported VLAN tags   */
	__be32                  checksum;     /* Checksum              */
पूर्ण;

/* Get Controller Packet Statistics */
काष्ठा ncsi_rsp_gcps_pkt अणु
	काष्ठा ncsi_rsp_pkt_hdr rsp;            /* Response header            */
	__be32                  cnt_hi;         /* Counter cleared            */
	__be32                  cnt_lo;         /* Counter cleared            */
	__be32                  rx_bytes;       /* Rx bytes                   */
	__be32                  tx_bytes;       /* Tx bytes                   */
	__be32                  rx_uc_pkts;     /* Rx UC packets              */
	__be32                  rx_mc_pkts;     /* Rx MC packets              */
	__be32                  rx_bc_pkts;     /* Rx BC packets              */
	__be32                  tx_uc_pkts;     /* Tx UC packets              */
	__be32                  tx_mc_pkts;     /* Tx MC packets              */
	__be32                  tx_bc_pkts;     /* Tx BC packets              */
	__be32                  fcs_err;        /* FCS errors                 */
	__be32                  align_err;      /* Alignment errors           */
	__be32                  false_carrier;  /* False carrier detection    */
	__be32                  runt_pkts;      /* Rx runt packets            */
	__be32                  jabber_pkts;    /* Rx jabber packets          */
	__be32                  rx_छोड़ो_xon;   /* Rx छोड़ो XON frames        */
	__be32                  rx_छोड़ो_xoff;  /* Rx XOFF frames             */
	__be32                  tx_छोड़ो_xon;   /* Tx XON frames              */
	__be32                  tx_छोड़ो_xoff;  /* Tx XOFF frames             */
	__be32                  tx_s_collision; /* Single collision frames    */
	__be32                  tx_m_collision; /* Multiple collision frames  */
	__be32                  l_collision;    /* Late collision frames      */
	__be32                  e_collision;    /* Excessive collision frames */
	__be32                  rx_ctl_frames;  /* Rx control frames          */
	__be32                  rx_64_frames;   /* Rx 64-bytes frames         */
	__be32                  rx_127_frames;  /* Rx 65-127 bytes frames     */
	__be32                  rx_255_frames;  /* Rx 128-255 bytes frames    */
	__be32                  rx_511_frames;  /* Rx 256-511 bytes frames    */
	__be32                  rx_1023_frames; /* Rx 512-1023 bytes frames   */
	__be32                  rx_1522_frames; /* Rx 1024-1522 bytes frames  */
	__be32                  rx_9022_frames; /* Rx 1523-9022 bytes frames  */
	__be32                  tx_64_frames;   /* Tx 64-bytes frames         */
	__be32                  tx_127_frames;  /* Tx 65-127 bytes frames     */
	__be32                  tx_255_frames;  /* Tx 128-255 bytes frames    */
	__be32                  tx_511_frames;  /* Tx 256-511 bytes frames    */
	__be32                  tx_1023_frames; /* Tx 512-1023 bytes frames   */
	__be32                  tx_1522_frames; /* Tx 1024-1522 bytes frames  */
	__be32                  tx_9022_frames; /* Tx 1523-9022 bytes frames  */
	__be32                  rx_valid_bytes; /* Rx valid bytes             */
	__be32                  rx_runt_pkts;   /* Rx error runt packets      */
	__be32                  rx_jabber_pkts; /* Rx error jabber packets    */
	__be32                  checksum;       /* Checksum                   */
पूर्ण;

/* Get NCSI Statistics */
काष्ठा ncsi_rsp_gns_pkt अणु
	काष्ठा ncsi_rsp_pkt_hdr rsp;           /* Response header         */
	__be32                  rx_cmds;       /* Rx NCSI commands        */
	__be32                  dropped_cmds;  /* Dropped commands        */
	__be32                  cmd_type_errs; /* Command type errors     */
	__be32                  cmd_csum_errs; /* Command checksum errors */
	__be32                  rx_pkts;       /* Rx NCSI packets         */
	__be32                  tx_pkts;       /* Tx NCSI packets         */
	__be32                  tx_aen_pkts;   /* Tx AEN packets          */
	__be32                  checksum;      /* Checksum                */
पूर्ण;

/* Get NCSI Pass-through Statistics */
काष्ठा ncsi_rsp_gnpts_pkt अणु
	काष्ठा ncsi_rsp_pkt_hdr rsp;            /* Response header     */
	__be32                  tx_pkts;        /* Tx packets          */
	__be32                  tx_dropped;     /* Tx dropped packets  */
	__be32                  tx_channel_err; /* Tx channel errors   */
	__be32                  tx_us_err;      /* Tx undersize errors */
	__be32                  rx_pkts;        /* Rx packets          */
	__be32                  rx_dropped;     /* Rx dropped packets  */
	__be32                  rx_channel_err; /* Rx channel errors   */
	__be32                  rx_us_err;      /* Rx undersize errors */
	__be32                  rx_os_err;      /* Rx oversize errors  */
	__be32                  checksum;       /* Checksum            */
पूर्ण;

/* Get package status */
काष्ठा ncsi_rsp_gps_pkt अणु
	काष्ठा ncsi_rsp_pkt_hdr rsp;      /* Response header             */
	__be32                  status;   /* Hardware arbitration status */
	__be32                  checksum;
पूर्ण;

/* Get package UUID */
काष्ठा ncsi_rsp_gpuuid_pkt अणु
	काष्ठा ncsi_rsp_pkt_hdr rsp;      /* Response header */
	अचिन्हित अक्षर           uuid[16]; /* UUID            */
	__be32                  checksum;
पूर्ण;

/* AEN: Link State Change */
काष्ठा ncsi_aen_lsc_pkt अणु
	काष्ठा ncsi_aen_pkt_hdr aen;        /* AEN header      */
	__be32                  status;     /* Link status     */
	__be32                  oem_status; /* OEM link status */
	__be32                  checksum;   /* Checksum        */
	अचिन्हित अक्षर           pad[14];
पूर्ण;

/* AEN: Configuration Required */
काष्ठा ncsi_aen_cr_pkt अणु
	काष्ठा ncsi_aen_pkt_hdr aen;      /* AEN header */
	__be32                  checksum; /* Checksum   */
	अचिन्हित अक्षर           pad[22];
पूर्ण;

/* AEN: Host Network Controller Driver Status Change */
काष्ठा ncsi_aen_hncdsc_pkt अणु
	काष्ठा ncsi_aen_pkt_hdr aen;      /* AEN header */
	__be32                  status;   /* Status     */
	__be32                  checksum; /* Checksum   */
	अचिन्हित अक्षर           pad[18];
पूर्ण;

/* NCSI packet revision */
#घोषणा NCSI_PKT_REVISION	0x01

/* NCSI packet commands */
#घोषणा NCSI_PKT_CMD_CIS	0x00 /* Clear Initial State              */
#घोषणा NCSI_PKT_CMD_SP		0x01 /* Select Package                   */
#घोषणा NCSI_PKT_CMD_DP		0x02 /* Deselect Package                 */
#घोषणा NCSI_PKT_CMD_EC		0x03 /* Enable Channel                   */
#घोषणा NCSI_PKT_CMD_DC		0x04 /* Disable Channel                  */
#घोषणा NCSI_PKT_CMD_RC		0x05 /* Reset Channel                    */
#घोषणा NCSI_PKT_CMD_ECNT	0x06 /* Enable Channel Network Tx        */
#घोषणा NCSI_PKT_CMD_DCNT	0x07 /* Disable Channel Network Tx       */
#घोषणा NCSI_PKT_CMD_AE		0x08 /* AEN Enable                       */
#घोषणा NCSI_PKT_CMD_SL		0x09 /* Set Link                         */
#घोषणा NCSI_PKT_CMD_GLS	0x0a /* Get Link                         */
#घोषणा NCSI_PKT_CMD_SVF	0x0b /* Set VLAN Filter                  */
#घोषणा NCSI_PKT_CMD_EV		0x0c /* Enable VLAN                      */
#घोषणा NCSI_PKT_CMD_DV		0x0d /* Disable VLAN                     */
#घोषणा NCSI_PKT_CMD_SMA	0x0e /* Set MAC address                  */
#घोषणा NCSI_PKT_CMD_EBF	0x10 /* Enable Broadcast Filter          */
#घोषणा NCSI_PKT_CMD_DBF	0x11 /* Disable Broadcast Filter         */
#घोषणा NCSI_PKT_CMD_EGMF	0x12 /* Enable Global Multicast Filter   */
#घोषणा NCSI_PKT_CMD_DGMF	0x13 /* Disable Global Multicast Filter  */
#घोषणा NCSI_PKT_CMD_SNFC	0x14 /* Set NCSI Flow Control            */
#घोषणा NCSI_PKT_CMD_GVI	0x15 /* Get Version ID                   */
#घोषणा NCSI_PKT_CMD_GC		0x16 /* Get Capabilities                 */
#घोषणा NCSI_PKT_CMD_GP		0x17 /* Get Parameters                   */
#घोषणा NCSI_PKT_CMD_GCPS	0x18 /* Get Controller Packet Statistics */
#घोषणा NCSI_PKT_CMD_GNS	0x19 /* Get NCSI Statistics              */
#घोषणा NCSI_PKT_CMD_GNPTS	0x1a /* Get NCSI Pass-throu Statistics   */
#घोषणा NCSI_PKT_CMD_GPS	0x1b /* Get package status               */
#घोषणा NCSI_PKT_CMD_OEM	0x50 /* OEM                              */
#घोषणा NCSI_PKT_CMD_PLDM	0x51 /* PLDM request over NCSI over RBT  */
#घोषणा NCSI_PKT_CMD_GPUUID	0x52 /* Get package UUID                 */
#घोषणा NCSI_PKT_CMD_QPNPR	0x56 /* Query Pending NC PLDM request */
#घोषणा NCSI_PKT_CMD_SNPR	0x57 /* Send NC PLDM Reply  */


/* NCSI packet responses */
#घोषणा NCSI_PKT_RSP_CIS	(NCSI_PKT_CMD_CIS    + 0x80)
#घोषणा NCSI_PKT_RSP_SP		(NCSI_PKT_CMD_SP     + 0x80)
#घोषणा NCSI_PKT_RSP_DP		(NCSI_PKT_CMD_DP     + 0x80)
#घोषणा NCSI_PKT_RSP_EC		(NCSI_PKT_CMD_EC     + 0x80)
#घोषणा NCSI_PKT_RSP_DC		(NCSI_PKT_CMD_DC     + 0x80)
#घोषणा NCSI_PKT_RSP_RC		(NCSI_PKT_CMD_RC     + 0x80)
#घोषणा NCSI_PKT_RSP_ECNT	(NCSI_PKT_CMD_ECNT   + 0x80)
#घोषणा NCSI_PKT_RSP_DCNT	(NCSI_PKT_CMD_DCNT   + 0x80)
#घोषणा NCSI_PKT_RSP_AE		(NCSI_PKT_CMD_AE     + 0x80)
#घोषणा NCSI_PKT_RSP_SL		(NCSI_PKT_CMD_SL     + 0x80)
#घोषणा NCSI_PKT_RSP_GLS	(NCSI_PKT_CMD_GLS    + 0x80)
#घोषणा NCSI_PKT_RSP_SVF	(NCSI_PKT_CMD_SVF    + 0x80)
#घोषणा NCSI_PKT_RSP_EV		(NCSI_PKT_CMD_EV     + 0x80)
#घोषणा NCSI_PKT_RSP_DV		(NCSI_PKT_CMD_DV     + 0x80)
#घोषणा NCSI_PKT_RSP_SMA	(NCSI_PKT_CMD_SMA    + 0x80)
#घोषणा NCSI_PKT_RSP_EBF	(NCSI_PKT_CMD_EBF    + 0x80)
#घोषणा NCSI_PKT_RSP_DBF	(NCSI_PKT_CMD_DBF    + 0x80)
#घोषणा NCSI_PKT_RSP_EGMF	(NCSI_PKT_CMD_EGMF   + 0x80)
#घोषणा NCSI_PKT_RSP_DGMF	(NCSI_PKT_CMD_DGMF   + 0x80)
#घोषणा NCSI_PKT_RSP_SNFC	(NCSI_PKT_CMD_SNFC   + 0x80)
#घोषणा NCSI_PKT_RSP_GVI	(NCSI_PKT_CMD_GVI    + 0x80)
#घोषणा NCSI_PKT_RSP_GC		(NCSI_PKT_CMD_GC     + 0x80)
#घोषणा NCSI_PKT_RSP_GP		(NCSI_PKT_CMD_GP     + 0x80)
#घोषणा NCSI_PKT_RSP_GCPS	(NCSI_PKT_CMD_GCPS   + 0x80)
#घोषणा NCSI_PKT_RSP_GNS	(NCSI_PKT_CMD_GNS    + 0x80)
#घोषणा NCSI_PKT_RSP_GNPTS	(NCSI_PKT_CMD_GNPTS  + 0x80)
#घोषणा NCSI_PKT_RSP_GPS	(NCSI_PKT_CMD_GPS    + 0x80)
#घोषणा NCSI_PKT_RSP_OEM	(NCSI_PKT_CMD_OEM    + 0x80)
#घोषणा NCSI_PKT_RSP_PLDM	(NCSI_PKT_CMD_PLDM   + 0x80)
#घोषणा NCSI_PKT_RSP_GPUUID	(NCSI_PKT_CMD_GPUUID + 0x80)
#घोषणा NCSI_PKT_RSP_QPNPR	(NCSI_PKT_CMD_QPNPR   + 0x80)
#घोषणा NCSI_PKT_RSP_SNPR	(NCSI_PKT_CMD_SNPR   + 0x80)

/* NCSI response code/reason */
#घोषणा NCSI_PKT_RSP_C_COMPLETED	0x0000 /* Command Completed        */
#घोषणा NCSI_PKT_RSP_C_FAILED		0x0001 /* Command Failed           */
#घोषणा NCSI_PKT_RSP_C_UNAVAILABLE	0x0002 /* Command Unavailable      */
#घोषणा NCSI_PKT_RSP_C_UNSUPPORTED	0x0003 /* Command Unsupported      */
#घोषणा NCSI_PKT_RSP_R_NO_ERROR		0x0000 /* No Error                 */
#घोषणा NCSI_PKT_RSP_R_INTERFACE	0x0001 /* Interface not पढ़ोy      */
#घोषणा NCSI_PKT_RSP_R_PARAM		0x0002 /* Invalid Parameter        */
#घोषणा NCSI_PKT_RSP_R_CHANNEL		0x0003 /* Channel not Ready        */
#घोषणा NCSI_PKT_RSP_R_PACKAGE		0x0004 /* Package not Ready        */
#घोषणा NCSI_PKT_RSP_R_LENGTH		0x0005 /* Invalid payload length   */
#घोषणा NCSI_PKT_RSP_R_UNKNOWN		0x7fff /* Command type unsupported */

/* NCSI AEN packet type */
#घोषणा NCSI_PKT_AEN		0xFF /* AEN Packet               */
#घोषणा NCSI_PKT_AEN_LSC	0x00 /* Link status change       */
#घोषणा NCSI_PKT_AEN_CR		0x01 /* Configuration required   */
#घोषणा NCSI_PKT_AEN_HNCDSC	0x02 /* HNC driver status change */

#पूर्ण_अगर /* __NCSI_PKT_H__ */
