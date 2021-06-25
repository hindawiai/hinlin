<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Linux network driver क्रम QLogic BR-series Converged Network Adapter.
 */
/*
 * Copyright (c) 2005-2014 Brocade Communications Systems, Inc.
 * Copyright (c) 2014-2015 QLogic Corporation
 * All rights reserved
 * www.qlogic.com
 */
#अगर_अघोषित __BFI_H__
#घोषणा __BFI_H__

#समावेश "bfa_defs.h"

/* BFI FW image type */
#घोषणा	BFI_FLASH_CHUNK_SZ			256	/*!< Flash chunk size */
#घोषणा	BFI_FLASH_CHUNK_SZ_WORDS	(BFI_FLASH_CHUNK_SZ/माप(u32))
#घोषणा BFI_FLASH_IMAGE_SZ		0x100000

/* Msg header common to all msgs */
काष्ठा bfi_mhdr अणु
	u8		msg_class;	/*!< @ref क्रमागत bfi_mclass	    */
	u8		msg_id;		/*!< msg opcode with in the class   */
	जोड़ अणु
		काष्ठा अणु
			u8	qid;
			u8	fn_lpu;	/*!< msg destination		    */
		पूर्ण __packed h2i;
		u16	i2htok;	/*!< token in msgs to host	    */
	पूर्ण __packed mtag;
पूर्ण __packed;

#घोषणा bfi_fn_lpu(__fn, __lpu)	((__fn) << 1 | (__lpu))
#घोषणा bfi_mhdr_2_fn(_mh)	((_mh)->mtag.h2i.fn_lpu >> 1)
#घोषणा bfi_mhdr_2_qid(_mh)	((_mh)->mtag.h2i.qid)

#घोषणा bfi_h2i_set(_mh, _mc, _op, _fn_lpu) करो अणु		\
	(_mh).msg_class			= (_mc);		\
	(_mh).msg_id			= (_op);		\
	(_mh).mtag.h2i.fn_lpu	= (_fn_lpu);			\
पूर्ण जबतक (0)

#घोषणा bfi_i2h_set(_mh, _mc, _op, _i2htok) करो अणु		\
	(_mh).msg_class			= (_mc);		\
	(_mh).msg_id			= (_op);		\
	(_mh).mtag.i2htok		= (_i2htok);		\
पूर्ण जबतक (0)

/*
 * Message opcodes: 0-127 to firmware, 128-255 to host
 */
#घोषणा BFI_I2H_OPCODE_BASE	128
#घोषणा BFA_I2HM(_x)			((_x) + BFI_I2H_OPCODE_BASE)

/****************************************************************************
 *
 * Scatter Gather Element and Page definition
 *
 ****************************************************************************
 */

/* DMA addresses */
जोड़ bfi_addr_u अणु
	काष्ठा अणु
		u32	addr_lo;
		u32	addr_hi;
	पूर्ण __packed a32;
पूर्ण __packed;

/* Generic DMA addr-len pair. */
काष्ठा bfi_alen अणु
	जोड़ bfi_addr_u	al_addr;	/* DMA addr of buffer	*/
	u32			al_len;		/* length of buffer */
पूर्ण __packed;

/*
 * Large Message काष्ठाure - 128 Bytes size Msgs
 */
#घोषणा BFI_LMSG_SZ		128
#घोषणा BFI_LMSG_PL_WSZ	\
			((BFI_LMSG_SZ - माप(काष्ठा bfi_mhdr)) / 4)

/* Mailbox message काष्ठाure */
#घोषणा BFI_MBMSG_SZ		7
काष्ठा bfi_mbmsg अणु
	काष्ठा bfi_mhdr mh;
	u32		pl[BFI_MBMSG_SZ];
पूर्ण __packed;

/* Supported PCI function class codes (personality) */
क्रमागत bfi_pcअगरn_class अणु
	BFI_PCIFN_CLASS_FC	= 0x0c04,
	BFI_PCIFN_CLASS_ETH	= 0x0200,
पूर्ण;

/* Message Classes */
क्रमागत bfi_mclass अणु
	BFI_MC_IOC		= 1,	/*!< IO Controller (IOC)	    */
	BFI_MC_DIAG		= 2,	/*!< Diagnostic Msgs		    */
	BFI_MC_FLASH		= 3,	/*!< Flash message class	    */
	BFI_MC_CEE		= 4,	/*!< CEE			    */
	BFI_MC_FCPORT		= 5,	/*!< FC port			    */
	BFI_MC_IOCFC		= 6,	/*!< FC - IO Controller (IOC)	    */
	BFI_MC_LL		= 7,	/*!< Link Layer			    */
	BFI_MC_UF		= 8,	/*!< Unsolicited frame receive	    */
	BFI_MC_FCXP		= 9,	/*!< FC Transport		    */
	BFI_MC_LPS		= 10,	/*!< lport fc login services	    */
	BFI_MC_RPORT		= 11,	/*!< Remote port		    */
	BFI_MC_ITNIM		= 12,	/*!< I-T nexus (Initiator mode)	    */
	BFI_MC_IOIM_READ	= 13,	/*!< पढ़ो IO (Initiator mode)	    */
	BFI_MC_IOIM_WRITE	= 14,	/*!< ग_लिखो IO (Initiator mode)	    */
	BFI_MC_IOIM_IO		= 15,	/*!< IO (Initiator mode)	    */
	BFI_MC_IOIM		= 16,	/*!< IO (Initiator mode)	    */
	BFI_MC_IOIM_IOCOM	= 17,	/*!< good IO completion		    */
	BFI_MC_TSKIM		= 18,	/*!< Initiator Task management	    */
	BFI_MC_SBOOT		= 19,	/*!< SAN boot services		    */
	BFI_MC_IPFC		= 20,	/*!< IP over FC Msgs		    */
	BFI_MC_PORT		= 21,	/*!< Physical port		    */
	BFI_MC_SFP		= 22,	/*!< SFP module			    */
	BFI_MC_MSGQ		= 23,	/*!< MSGQ			    */
	BFI_MC_ENET		= 24,	/*!< ENET commands/responses	    */
	BFI_MC_PHY		= 25,	/*!< External PHY message class	    */
	BFI_MC_NBOOT		= 26,	/*!< Network Boot		    */
	BFI_MC_TIO_READ		= 27,	/*!< पढ़ो IO (Target mode)	    */
	BFI_MC_TIO_WRITE	= 28,	/*!< ग_लिखो IO (Target mode)	    */
	BFI_MC_TIO_DATA_XFERED	= 29,	/*!< ds transferred (target mode)   */
	BFI_MC_TIO_IO		= 30,	/*!< IO (Target mode)		    */
	BFI_MC_TIO		= 31,	/*!< IO (target mode)		    */
	BFI_MC_MFG		= 32,	/*!< MFG/ASIC block commands	    */
	BFI_MC_EDMA		= 33,	/*!< EDMA copy commands		    */
	BFI_MC_MAX		= 34
पूर्ण;

#घोषणा BFI_IOC_MSGLEN_MAX	32	/* 32 bytes */

#घोषणा BFI_FWBOOT_ENV_OS		0

/*----------------------------------------------------------------------
 *				IOC
 *----------------------------------------------------------------------
 */

/* Dअगरferent asic generations */
क्रमागत bfi_asic_gen अणु
	BFI_ASIC_GEN_CB		= 1,
	BFI_ASIC_GEN_CT		= 2,
	BFI_ASIC_GEN_CT2	= 3,
पूर्ण;

क्रमागत bfi_asic_mode अणु
	BFI_ASIC_MODE_FC	= 1,	/* FC up to 8G speed		*/
	BFI_ASIC_MODE_FC16	= 2,	/* FC up to 16G speed		*/
	BFI_ASIC_MODE_ETH	= 3,	/* Ethernet ports		*/
	BFI_ASIC_MODE_COMBO	= 4,	/* FC 16G and Ethernet 10G port	*/
पूर्ण;

क्रमागत bfi_ioc_h2i_msgs अणु
	BFI_IOC_H2I_ENABLE_REQ		= 1,
	BFI_IOC_H2I_DISABLE_REQ		= 2,
	BFI_IOC_H2I_GETATTR_REQ		= 3,
	BFI_IOC_H2I_DBG_SYNC		= 4,
	BFI_IOC_H2I_DBG_DUMP		= 5,
पूर्ण;

क्रमागत bfi_ioc_i2h_msgs अणु
	BFI_IOC_I2H_ENABLE_REPLY	= BFA_I2HM(1),
	BFI_IOC_I2H_DISABLE_REPLY	= BFA_I2HM(2),
	BFI_IOC_I2H_GETATTR_REPLY	= BFA_I2HM(3),
	BFI_IOC_I2H_HBEAT		= BFA_I2HM(4),
पूर्ण;

/* BFI_IOC_H2I_GETATTR_REQ message */
काष्ठा bfi_ioc_getattr_req अणु
	काष्ठा bfi_mhdr mh;
	जोड़ bfi_addr_u	attr_addr;
पूर्ण __packed;

काष्ठा bfi_ioc_attr अणु
	u64		mfg_pwwn;	/*!< Mfg port wwn	   */
	u64		mfg_nwwn;	/*!< Mfg node wwn	   */
	u8		mfg_mac[ETH_ALEN]; /*!< Mfg mac		   */
	u8		port_mode;	/* क्रमागत bfi_port_mode	   */
	u8		rsvd_a;
	u64		pwwn;
	u64		nwwn;
	u8		mac[ETH_ALEN];	/*!< PBC or Mfg mac	   */
	u16	rsvd_b;
	u8		fcoe_mac[ETH_ALEN];
	u16	rsvd_c;
	अक्षर		brcd_serialnum[STRSZ(BFA_MFG_SERIALNUM_SIZE)];
	u8		pcie_gen;
	u8		pcie_lanes_orig;
	u8		pcie_lanes;
	u8		rx_bbcredit;	/*!< receive buffer credits */
	u32	adapter_prop;	/*!< adapter properties     */
	u16	maxfrsize;	/*!< max receive frame size */
	अक्षर		asic_rev;
	u8		rsvd_d;
	अक्षर		fw_version[BFA_VERSION_LEN];
	अक्षर		optrom_version[BFA_VERSION_LEN];
	काष्ठा bfa_mfg_vpd vpd;
	u32	card_type;	/*!< card type			*/
पूर्ण __packed;

/* BFI_IOC_I2H_GETATTR_REPLY message */
काष्ठा bfi_ioc_getattr_reply अणु
	काष्ठा bfi_mhdr mh;	/*!< Common msg header		*/
	u8			status;	/*!< cfg reply status		*/
	u8			rsvd[3];
पूर्ण __packed;

/* Firmware memory page offsets */
#घोषणा BFI_IOC_SMEM_PG0_CB	(0x40)
#घोषणा BFI_IOC_SMEM_PG0_CT	(0x180)

/* Firmware statistic offset */
#घोषणा BFI_IOC_FWSTATS_OFF	(0x6B40)
#घोषणा BFI_IOC_FWSTATS_SZ	(4096)

/* Firmware trace offset */
#घोषणा BFI_IOC_TRC_OFF		(0x4b00)
#घोषणा BFI_IOC_TRC_ENTS	256
#घोषणा BFI_IOC_TRC_ENT_SZ	16
#घोषणा BFI_IOC_TRC_HDR_SZ	32

#घोषणा BFI_IOC_FW_SIGNATURE	(0xbfadbfad)
#घोषणा BFI_IOC_FW_INV_SIGN	(0xdeaddead)
#घोषणा BFI_IOC_MD5SUM_SZ	4

काष्ठा bfi_ioc_fwver अणु
#अगर_घोषित __BIG_ENDIAN
	u8 patch;
	u8 मुख्यt;
	u8 minor;
	u8 major;
	u8 rsvd[2];
	u8 build;
	u8 phase;
#अन्यथा
	u8 major;
	u8 minor;
	u8 मुख्यt;
	u8 patch;
	u8 phase;
	u8 build;
	u8 rsvd[2];
#पूर्ण_अगर
पूर्ण __packed;

काष्ठा bfi_ioc_image_hdr अणु
	u32	signature;	/*!< स्थिरant signature */
	u8	asic_gen;	/*!< asic generation */
	u8	asic_mode;
	u8	port0_mode;	/*!< device mode क्रम port 0 */
	u8	port1_mode;	/*!< device mode क्रम port 1 */
	u32	exec;		/*!< exec vector	*/
	u32	bootenv;	/*!< firmware boot env */
	u32	rsvd_b[2];
	काष्ठा bfi_ioc_fwver fwver;
	u32	md5sum[BFI_IOC_MD5SUM_SZ];
पूर्ण __packed;

क्रमागत bfi_ioc_img_ver_cmp अणु
	BFI_IOC_IMG_VER_INCOMP,
	BFI_IOC_IMG_VER_OLD,
	BFI_IOC_IMG_VER_SAME,
	BFI_IOC_IMG_VER_BETTER
पूर्ण;

#घोषणा BFI_FWBOOT_DEVMODE_OFF		4
#घोषणा BFI_FWBOOT_TYPE_OFF		8
#घोषणा BFI_FWBOOT_ENV_OFF		12
#घोषणा BFI_FWBOOT_DEVMODE(__asic_gen, __asic_mode, __p0_mode, __p1_mode) \
	(((u32)(__asic_gen)) << 24 |	\
	 ((u32)(__asic_mode)) << 16 |	\
	 ((u32)(__p0_mode)) << 8 |	\
	 ((u32)(__p1_mode)))

क्रमागत bfi_fwboot_type अणु
	BFI_FWBOOT_TYPE_NORMAL	= 0,
	BFI_FWBOOT_TYPE_FLASH	= 1,
	BFI_FWBOOT_TYPE_MEMTEST	= 2,
पूर्ण;

क्रमागत bfi_port_mode अणु
	BFI_PORT_MODE_FC	= 1,
	BFI_PORT_MODE_ETH	= 2,
पूर्ण;

काष्ठा bfi_ioc_hbeat अणु
	काष्ठा bfi_mhdr mh;		/*!< common msg header		*/
	u32	   hb_count;	/*!< current heart beat count	*/
पूर्ण __packed;

/* IOC hardware/firmware state */
क्रमागत bfi_ioc_state अणु
	BFI_IOC_UNINIT		= 0,	/*!< not initialized		     */
	BFI_IOC_INITING		= 1,	/*!< h/w is being initialized	     */
	BFI_IOC_HWINIT		= 2,	/*!< h/w is initialized		     */
	BFI_IOC_CFG		= 3,	/*!< IOC configuration in progress   */
	BFI_IOC_OP		= 4,	/*!< IOC is operational		     */
	BFI_IOC_DISABLING	= 5,	/*!< IOC is being disabled	     */
	BFI_IOC_DISABLED	= 6,	/*!< IOC is disabled		     */
	BFI_IOC_CFG_DISABLED	= 7,	/*!< IOC is being disabled;transient */
	BFI_IOC_FAIL		= 8,	/*!< IOC heart-beat failure	     */
	BFI_IOC_MEMTEST		= 9,	/*!< IOC is करोing memtest	     */
पूर्ण;

क्रमागत अणु
	BFI_ADAPTER_TYPE_FC	= 0x01,		/*!< FC adapters	   */
	BFI_ADAPTER_TYPE_MK	= 0x0f0000,	/*!< adapter type mask     */
	BFI_ADAPTER_TYPE_SH	= 16,	        /*!< adapter type shअगरt    */
	BFI_ADAPTER_NPORTS_MK	= 0xff00,	/*!< number of ports mask  */
	BFI_ADAPTER_NPORTS_SH	= 8,	        /*!< number of ports shअगरt */
	BFI_ADAPTER_SPEED_MK	= 0xff,		/*!< adapter speed mask    */
	BFI_ADAPTER_SPEED_SH	= 0,	        /*!< adapter speed shअगरt   */
	BFI_ADAPTER_PROTO	= 0x100000,	/*!< prototype adapaters   */
	BFI_ADAPTER_TTV		= 0x200000,	/*!< TTV debug capable     */
	BFI_ADAPTER_UNSUPP	= 0x400000,	/*!< unknown adapter type  */
पूर्ण;

#घोषणा BFI_ADAPTER_GETP(__prop, __adap_prop)			\
	(((__adap_prop) & BFI_ADAPTER_ ## __prop ## _MK) >>	\
		BFI_ADAPTER_ ## __prop ## _SH)
#घोषणा BFI_ADAPTER_SETP(__prop, __val)				\
	((__val) << BFI_ADAPTER_ ## __prop ## _SH)
#घोषणा BFI_ADAPTER_IS_SPECIAL(__adap_type)			\
	((__adap_type) & (BFI_ADAPTER_TTV | BFI_ADAPTER_PROTO |	\
			BFI_ADAPTER_UNSUPP))

/* BFI_IOC_H2I_ENABLE_REQ & BFI_IOC_H2I_DISABLE_REQ messages */
काष्ठा bfi_ioc_ctrl_req अणु
	काष्ठा bfi_mhdr mh;
	u16			clscode;
	u16			rsvd;
	u32		tv_sec;
पूर्ण __packed;

/* BFI_IOC_I2H_ENABLE_REPLY & BFI_IOC_I2H_DISABLE_REPLY messages */
काष्ठा bfi_ioc_ctrl_reply अणु
	काष्ठा bfi_mhdr mh;			/*!< Common msg header     */
	u8			status;		/*!< enable/disable status */
	u8			port_mode;	/*!< क्रमागत bfa_mode */
	u8			cap_bm;		/*!< capability bit mask */
	u8			rsvd;
पूर्ण __packed;

#घोषणा BFI_IOC_MSGSZ   8
/* H2I Messages */
जोड़ bfi_ioc_h2i_msg_u अणु
	काष्ठा bfi_mhdr mh;
	काष्ठा bfi_ioc_ctrl_req enable_req;
	काष्ठा bfi_ioc_ctrl_req disable_req;
	काष्ठा bfi_ioc_getattr_req getattr_req;
	u32			mboxmsg[BFI_IOC_MSGSZ];
पूर्ण __packed;

/* I2H Messages */
जोड़ bfi_ioc_i2h_msg_u अणु
	काष्ठा bfi_mhdr mh;
	काष्ठा bfi_ioc_ctrl_reply fw_event;
	u32			mboxmsg[BFI_IOC_MSGSZ];
पूर्ण __packed;

/*----------------------------------------------------------------------
 *				MSGQ
 *----------------------------------------------------------------------
 */

क्रमागत bfi_msgq_h2i_msgs अणु
	BFI_MSGQ_H2I_INIT_REQ	   = 1,
	BFI_MSGQ_H2I_DOORBELL_PI	= 2,
	BFI_MSGQ_H2I_DOORBELL_CI	= 3,
	BFI_MSGQ_H2I_CMDQ_COPY_RSP      = 4,
पूर्ण;

क्रमागत bfi_msgq_i2h_msgs अणु
	BFI_MSGQ_I2H_INIT_RSP	   = BFA_I2HM(BFI_MSGQ_H2I_INIT_REQ),
	BFI_MSGQ_I2H_DOORBELL_PI	= BFA_I2HM(BFI_MSGQ_H2I_DOORBELL_PI),
	BFI_MSGQ_I2H_DOORBELL_CI	= BFA_I2HM(BFI_MSGQ_H2I_DOORBELL_CI),
	BFI_MSGQ_I2H_CMDQ_COPY_REQ      = BFA_I2HM(BFI_MSGQ_H2I_CMDQ_COPY_RSP),
पूर्ण;

/* Messages(commands/responsed/AENS will have the following header */
काष्ठा bfi_msgq_mhdr अणु
	u8	msg_class;
	u8	msg_id;
	u16	msg_token;
	u16	num_entries;
	u8	enet_id;
	u8	rsvd;
पूर्ण __packed;

#घोषणा bfi_msgq_mhdr_set(_mh, _mc, _mid, _tok, _enet_id) करो अणु	\
	(_mh).msg_class	 = (_mc);	\
	(_mh).msg_id	    = (_mid);       \
	(_mh).msg_token	 = (_tok);       \
	(_mh).enet_id	   = (_enet_id);   \
पूर्ण जबतक (0)

/*
 * Mailbox  क्रम messaging पूर्णांकerface
 */
#घोषणा BFI_MSGQ_CMD_ENTRY_SIZE	 (64)    /* TBD */
#घोषणा BFI_MSGQ_RSP_ENTRY_SIZE	 (64)    /* TBD */

#घोषणा bfi_msgq_num_cmd_entries(_size)				 \
	(((_size) + BFI_MSGQ_CMD_ENTRY_SIZE - 1) / BFI_MSGQ_CMD_ENTRY_SIZE)

काष्ठा bfi_msgq अणु
	जोड़ bfi_addr_u addr;
	u16 q_depth;     /* Total num of entries in the queue */
	u8 rsvd[2];
पूर्ण __packed;

/* BFI_ENET_MSGQ_CFG_REQ TBD init or cfg? */
काष्ठा bfi_msgq_cfg_req अणु
	काष्ठा bfi_mhdr mh;
	काष्ठा bfi_msgq cmdq;
	काष्ठा bfi_msgq rspq;
पूर्ण __packed;

/* BFI_ENET_MSGQ_CFG_RSP */
काष्ठा bfi_msgq_cfg_rsp अणु
	काष्ठा bfi_mhdr mh;
	u8 cmd_status;
	u8 rsvd[3];
पूर्ण __packed;

/* BFI_MSGQ_H2I_DOORBELL */
काष्ठा bfi_msgq_h2i_db अणु
	काष्ठा bfi_mhdr mh;
	जोड़ अणु
		u16 cmdq_pi;
		u16 rspq_ci;
	पूर्ण __packed idx;
पूर्ण __packed;

/* BFI_MSGQ_I2H_DOORBELL */
काष्ठा bfi_msgq_i2h_db अणु
	काष्ठा bfi_mhdr mh;
	जोड़ अणु
		u16 rspq_pi;
		u16 cmdq_ci;
	पूर्ण __packed idx;
पूर्ण __packed;

#घोषणा BFI_CMD_COPY_SZ 28

/* BFI_MSGQ_H2I_CMD_COPY_RSP */
काष्ठा bfi_msgq_h2i_cmdq_copy_rsp अणु
	काष्ठा bfi_mhdr mh;
	u8	      data[BFI_CMD_COPY_SZ];
पूर्ण __packed;

/* BFI_MSGQ_I2H_CMD_COPY_REQ */
काष्ठा bfi_msgq_i2h_cmdq_copy_req अणु
	काष्ठा bfi_mhdr mh;
	u16     offset;
	u16     len;
पूर्ण __packed;

/*
 *      FLASH module specअगरic
 */
क्रमागत bfi_flash_h2i_msgs अणु
	BFI_FLASH_H2I_QUERY_REQ = 1,
	BFI_FLASH_H2I_ERASE_REQ = 2,
	BFI_FLASH_H2I_WRITE_REQ = 3,
	BFI_FLASH_H2I_READ_REQ = 4,
	BFI_FLASH_H2I_BOOT_VER_REQ = 5,
पूर्ण;

क्रमागत bfi_flash_i2h_msgs अणु
	BFI_FLASH_I2H_QUERY_RSP = BFA_I2HM(1),
	BFI_FLASH_I2H_ERASE_RSP = BFA_I2HM(2),
	BFI_FLASH_I2H_WRITE_RSP = BFA_I2HM(3),
	BFI_FLASH_I2H_READ_RSP = BFA_I2HM(4),
	BFI_FLASH_I2H_BOOT_VER_RSP = BFA_I2HM(5),
	BFI_FLASH_I2H_EVENT = BFA_I2HM(127),
पूर्ण;

/*
 * Flash query request
 */
काष्ठा bfi_flash_query_req अणु
	काष्ठा bfi_mhdr mh;   /* Common msg header */
	काष्ठा bfi_alen alen;
पूर्ण __packed;

/*
 * Flash ग_लिखो request
 */
काष्ठा bfi_flash_ग_लिखो_req अणु
	काष्ठा bfi_mhdr mh;	/* Common msg header */
	काष्ठा bfi_alen alen;
	u32	type;   /* partition type */
	u8	instance; /* partition instance */
	u8	last;
	u8	rsv[2];
	u32	offset;
	u32	length;
पूर्ण __packed;

/*
 * Flash पढ़ो request
 */
काष्ठा bfi_flash_पढ़ो_req अणु
	काष्ठा bfi_mhdr mh;	/* Common msg header */
	u32	type;		/* partition type */
	u8	instance;	/* partition instance */
	u8	rsv[3];
	u32	offset;
	u32	length;
	काष्ठा bfi_alen alen;
पूर्ण __packed;

/*
 * Flash query response
 */
काष्ठा bfi_flash_query_rsp अणु
	काष्ठा bfi_mhdr mh;	/* Common msg header */
	u32	status;
पूर्ण __packed;

/*
 * Flash पढ़ो response
 */
काष्ठा bfi_flash_पढ़ो_rsp अणु
	काष्ठा bfi_mhdr mh;	/* Common msg header */
	u32	type;		/* partition type */
	u8	instance;	/* partition instance */
	u8	rsv[3];
	u32	status;
	u32	length;
पूर्ण __packed;

/*
 * Flash ग_लिखो response
 */
काष्ठा bfi_flash_ग_लिखो_rsp अणु
	काष्ठा bfi_mhdr mh;	/* Common msg header */
	u32	type;		/* partition type */
	u8	instance;	/* partition instance */
	u8	rsv[3];
	u32	status;
	u32	length;
पूर्ण __packed;

#पूर्ण_अगर /* __BFI_H__ */
