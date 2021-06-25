<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Definitions क्रम the NVM Express पूर्णांकerface
 * Copyright (c) 2011-2014, Intel Corporation.
 */

#अगर_अघोषित _LINUX_NVME_H
#घोषणा _LINUX_NVME_H

#समावेश <linux/types.h>
#समावेश <linux/uuid.h>

/* NQN names in commands fields specअगरied one size */
#घोषणा NVMF_NQN_FIELD_LEN	256

/* However the max length of a qualअगरied name is another size */
#घोषणा NVMF_NQN_SIZE		223

#घोषणा NVMF_TRSVCID_SIZE	32
#घोषणा NVMF_TRADDR_SIZE	256
#घोषणा NVMF_TSAS_SIZE		256

#घोषणा NVME_DISC_SUBSYS_NAME	"nqn.2014-08.org.nvmexpress.discovery"

#घोषणा NVME_RDMA_IP_PORT	4420

#घोषणा NVME_NSID_ALL		0xffffffff

क्रमागत nvme_subsys_type अणु
	NVME_NQN_DISC	= 1,		/* Discovery type target subप्रणाली */
	NVME_NQN_NVME	= 2,		/* NVME type target subप्रणाली */
पूर्ण;

/* Address Family codes क्रम Discovery Log Page entry ADRFAM field */
क्रमागत अणु
	NVMF_ADDR_FAMILY_PCI	= 0,	/* PCIe */
	NVMF_ADDR_FAMILY_IP4	= 1,	/* IP4 */
	NVMF_ADDR_FAMILY_IP6	= 2,	/* IP6 */
	NVMF_ADDR_FAMILY_IB	= 3,	/* InfiniBand */
	NVMF_ADDR_FAMILY_FC	= 4,	/* Fibre Channel */
	NVMF_ADDR_FAMILY_LOOP	= 254,	/* Reserved क्रम host usage */
	NVMF_ADDR_FAMILY_MAX,
पूर्ण;

/* Transport Type codes क्रम Discovery Log Page entry TRTYPE field */
क्रमागत अणु
	NVMF_TRTYPE_RDMA	= 1,	/* RDMA */
	NVMF_TRTYPE_FC		= 2,	/* Fibre Channel */
	NVMF_TRTYPE_TCP		= 3,	/* TCP/IP */
	NVMF_TRTYPE_LOOP	= 254,	/* Reserved क्रम host usage */
	NVMF_TRTYPE_MAX,
पूर्ण;

/* Transport Requirements codes क्रम Discovery Log Page entry TREQ field */
क्रमागत अणु
	NVMF_TREQ_NOT_SPECIFIED	= 0,		/* Not specअगरied */
	NVMF_TREQ_REQUIRED	= 1,		/* Required */
	NVMF_TREQ_NOT_REQUIRED	= 2,		/* Not Required */
#घोषणा NVME_TREQ_SECURE_CHANNEL_MASK \
	(NVMF_TREQ_REQUIRED | NVMF_TREQ_NOT_REQUIRED)

	NVMF_TREQ_DISABLE_SQFLOW = (1 << 2),	/* Supports SQ flow control disable */
पूर्ण;

/* RDMA QP Service Type codes क्रम Discovery Log Page entry TSAS
 * RDMA_QPTYPE field
 */
क्रमागत अणु
	NVMF_RDMA_QPTYPE_CONNECTED	= 1, /* Reliable Connected */
	NVMF_RDMA_QPTYPE_DATAGRAM	= 2, /* Reliable Datagram */
पूर्ण;

/* RDMA QP Service Type codes क्रम Discovery Log Page entry TSAS
 * RDMA_QPTYPE field
 */
क्रमागत अणु
	NVMF_RDMA_PRTYPE_NOT_SPECIFIED	= 1, /* No Provider Specअगरied */
	NVMF_RDMA_PRTYPE_IB		= 2, /* InfiniBand */
	NVMF_RDMA_PRTYPE_ROCE		= 3, /* InfiniBand RoCE */
	NVMF_RDMA_PRTYPE_ROCEV2		= 4, /* InfiniBand RoCEV2 */
	NVMF_RDMA_PRTYPE_IWARP		= 5, /* IWARP */
पूर्ण;

/* RDMA Connection Management Service Type codes क्रम Discovery Log Page
 * entry TSAS RDMA_CMS field
 */
क्रमागत अणु
	NVMF_RDMA_CMS_RDMA_CM	= 1, /* Sockets based endpoपूर्णांक addressing */
पूर्ण;

#घोषणा NVME_AQ_DEPTH		32
#घोषणा NVME_NR_AEN_COMMANDS	1
#घोषणा NVME_AQ_BLK_MQ_DEPTH	(NVME_AQ_DEPTH - NVME_NR_AEN_COMMANDS)

/*
 * Subtract one to leave an empty queue entry क्रम 'Full Queue' condition. See
 * NVM-Express 1.2 specअगरication, section 4.1.2.
 */
#घोषणा NVME_AQ_MQ_TAG_DEPTH	(NVME_AQ_BLK_MQ_DEPTH - 1)

क्रमागत अणु
	NVME_REG_CAP	= 0x0000,	/* Controller Capabilities */
	NVME_REG_VS	= 0x0008,	/* Version */
	NVME_REG_INTMS	= 0x000c,	/* Interrupt Mask Set */
	NVME_REG_INTMC	= 0x0010,	/* Interrupt Mask Clear */
	NVME_REG_CC	= 0x0014,	/* Controller Configuration */
	NVME_REG_CSTS	= 0x001c,	/* Controller Status */
	NVME_REG_NSSR	= 0x0020,	/* NVM Subप्रणाली Reset */
	NVME_REG_AQA	= 0x0024,	/* Admin Queue Attributes */
	NVME_REG_ASQ	= 0x0028,	/* Admin SQ Base Address */
	NVME_REG_ACQ	= 0x0030,	/* Admin CQ Base Address */
	NVME_REG_CMBLOC	= 0x0038,	/* Controller Memory Buffer Location */
	NVME_REG_CMBSZ	= 0x003c,	/* Controller Memory Buffer Size */
	NVME_REG_BPINFO	= 0x0040,	/* Boot Partition Inक्रमmation */
	NVME_REG_BPRSEL	= 0x0044,	/* Boot Partition Read Select */
	NVME_REG_BPMBL	= 0x0048,	/* Boot Partition Memory Buffer
					 * Location
					 */
	NVME_REG_CMBMSC = 0x0050,	/* Controller Memory Buffer Memory
					 * Space Control
					 */
	NVME_REG_PMRCAP	= 0x0e00,	/* Persistent Memory Capabilities */
	NVME_REG_PMRCTL	= 0x0e04,	/* Persistent Memory Region Control */
	NVME_REG_PMRSTS	= 0x0e08,	/* Persistent Memory Region Status */
	NVME_REG_PMREBS	= 0x0e0c,	/* Persistent Memory Region Elasticity
					 * Buffer Size
					 */
	NVME_REG_PMRSWTP = 0x0e10,	/* Persistent Memory Region Sustained
					 * Write Throughput
					 */
	NVME_REG_DBS	= 0x1000,	/* SQ 0 Tail Doorbell */
पूर्ण;

#घोषणा NVME_CAP_MQES(cap)	((cap) & 0xffff)
#घोषणा NVME_CAP_TIMEOUT(cap)	(((cap) >> 24) & 0xff)
#घोषणा NVME_CAP_STRIDE(cap)	(((cap) >> 32) & 0xf)
#घोषणा NVME_CAP_NSSRC(cap)	(((cap) >> 36) & 0x1)
#घोषणा NVME_CAP_CSS(cap)	(((cap) >> 37) & 0xff)
#घोषणा NVME_CAP_MPSMIN(cap)	(((cap) >> 48) & 0xf)
#घोषणा NVME_CAP_MPSMAX(cap)	(((cap) >> 52) & 0xf)
#घोषणा NVME_CAP_CMBS(cap)	(((cap) >> 57) & 0x1)

#घोषणा NVME_CMB_BIR(cmbloc)	((cmbloc) & 0x7)
#घोषणा NVME_CMB_OFST(cmbloc)	(((cmbloc) >> 12) & 0xfffff)

क्रमागत अणु
	NVME_CMBSZ_SQS		= 1 << 0,
	NVME_CMBSZ_CQS		= 1 << 1,
	NVME_CMBSZ_LISTS	= 1 << 2,
	NVME_CMBSZ_RDS		= 1 << 3,
	NVME_CMBSZ_WDS		= 1 << 4,

	NVME_CMBSZ_SZ_SHIFT	= 12,
	NVME_CMBSZ_SZ_MASK	= 0xfffff,

	NVME_CMBSZ_SZU_SHIFT	= 8,
	NVME_CMBSZ_SZU_MASK	= 0xf,
पूर्ण;

/*
 * Submission and Completion Queue Entry Sizes क्रम the NVM command set.
 * (In bytes and specअगरied as a घातer of two (2^n)).
 */
#घोषणा NVME_ADM_SQES       6
#घोषणा NVME_NVM_IOSQES		6
#घोषणा NVME_NVM_IOCQES		4

क्रमागत अणु
	NVME_CC_ENABLE		= 1 << 0,
	NVME_CC_EN_SHIFT	= 0,
	NVME_CC_CSS_SHIFT	= 4,
	NVME_CC_MPS_SHIFT	= 7,
	NVME_CC_AMS_SHIFT	= 11,
	NVME_CC_SHN_SHIFT	= 14,
	NVME_CC_IOSQES_SHIFT	= 16,
	NVME_CC_IOCQES_SHIFT	= 20,
	NVME_CC_CSS_NVM		= 0 << NVME_CC_CSS_SHIFT,
	NVME_CC_CSS_CSI		= 6 << NVME_CC_CSS_SHIFT,
	NVME_CC_CSS_MASK	= 7 << NVME_CC_CSS_SHIFT,
	NVME_CC_AMS_RR		= 0 << NVME_CC_AMS_SHIFT,
	NVME_CC_AMS_WRRU	= 1 << NVME_CC_AMS_SHIFT,
	NVME_CC_AMS_VS		= 7 << NVME_CC_AMS_SHIFT,
	NVME_CC_SHN_NONE	= 0 << NVME_CC_SHN_SHIFT,
	NVME_CC_SHN_NORMAL	= 1 << NVME_CC_SHN_SHIFT,
	NVME_CC_SHN_ABRUPT	= 2 << NVME_CC_SHN_SHIFT,
	NVME_CC_SHN_MASK	= 3 << NVME_CC_SHN_SHIFT,
	NVME_CC_IOSQES		= NVME_NVM_IOSQES << NVME_CC_IOSQES_SHIFT,
	NVME_CC_IOCQES		= NVME_NVM_IOCQES << NVME_CC_IOCQES_SHIFT,
	NVME_CAP_CSS_NVM	= 1 << 0,
	NVME_CAP_CSS_CSI	= 1 << 6,
	NVME_CSTS_RDY		= 1 << 0,
	NVME_CSTS_CFS		= 1 << 1,
	NVME_CSTS_NSSRO		= 1 << 4,
	NVME_CSTS_PP		= 1 << 5,
	NVME_CSTS_SHST_NORMAL	= 0 << 2,
	NVME_CSTS_SHST_OCCUR	= 1 << 2,
	NVME_CSTS_SHST_CMPLT	= 2 << 2,
	NVME_CSTS_SHST_MASK	= 3 << 2,
	NVME_CMBMSC_CRE		= 1 << 0,
	NVME_CMBMSC_CMSE	= 1 << 1,
पूर्ण;

काष्ठा nvme_id_घातer_state अणु
	__le16			max_घातer;	/* centiwatts */
	__u8			rsvd2;
	__u8			flags;
	__le32			entry_lat;	/* microseconds */
	__le32			निकास_lat;	/* microseconds */
	__u8			पढ़ो_tput;
	__u8			पढ़ो_lat;
	__u8			ग_लिखो_tput;
	__u8			ग_लिखो_lat;
	__le16			idle_घातer;
	__u8			idle_scale;
	__u8			rsvd19;
	__le16			active_घातer;
	__u8			active_work_scale;
	__u8			rsvd23[9];
पूर्ण;

क्रमागत अणु
	NVME_PS_FLAGS_MAX_POWER_SCALE	= 1 << 0,
	NVME_PS_FLAGS_NON_OP_STATE	= 1 << 1,
पूर्ण;

क्रमागत nvme_ctrl_attr अणु
	NVME_CTRL_ATTR_HID_128_BIT	= (1 << 0),
	NVME_CTRL_ATTR_TBKAS		= (1 << 6),
पूर्ण;

काष्ठा nvme_id_ctrl अणु
	__le16			vid;
	__le16			ssvid;
	अक्षर			sn[20];
	अक्षर			mn[40];
	अक्षर			fr[8];
	__u8			rab;
	__u8			ieee[3];
	__u8			cmic;
	__u8			mdts;
	__le16			cntlid;
	__le32			ver;
	__le32			rtd3r;
	__le32			rtd3e;
	__le32			oaes;
	__le32			ctratt;
	__u8			rsvd100[28];
	__le16			crdt1;
	__le16			crdt2;
	__le16			crdt3;
	__u8			rsvd134[122];
	__le16			oacs;
	__u8			acl;
	__u8			aerl;
	__u8			frmw;
	__u8			lpa;
	__u8			elpe;
	__u8			npss;
	__u8			avscc;
	__u8			apsta;
	__le16			wctemp;
	__le16			cctemp;
	__le16			mtfa;
	__le32			hmpre;
	__le32			hmmin;
	__u8			tnvmcap[16];
	__u8			unvmcap[16];
	__le32			rpmbs;
	__le16			edstt;
	__u8			dsto;
	__u8			fwug;
	__le16			kas;
	__le16			hcपंचांगa;
	__le16			mnपंचांगt;
	__le16			mxपंचांगt;
	__le32			sanicap;
	__le32			hmminds;
	__le16			hmmaxd;
	__u8			rsvd338[4];
	__u8			anatt;
	__u8			anacap;
	__le32			anagrpmax;
	__le32			nanagrpid;
	__u8			rsvd352[160];
	__u8			sqes;
	__u8			cqes;
	__le16			maxcmd;
	__le32			nn;
	__le16			oncs;
	__le16			fuses;
	__u8			fna;
	__u8			vwc;
	__le16			awun;
	__le16			awupf;
	__u8			nvscc;
	__u8			nwpc;
	__le16			acwu;
	__u8			rsvd534[2];
	__le32			sgls;
	__le32			mnan;
	__u8			rsvd544[224];
	अक्षर			subnqn[256];
	__u8			rsvd1024[768];
	__le32			ioccsz;
	__le32			iorcsz;
	__le16			icकरोff;
	__u8			ctrattr;
	__u8			msdbd;
	__u8			rsvd1804[244];
	काष्ठा nvme_id_घातer_state	psd[32];
	__u8			vs[1024];
पूर्ण;

क्रमागत अणु
	NVME_CTRL_CMIC_MULTI_CTRL		= 1 << 1,
	NVME_CTRL_CMIC_ANA			= 1 << 3,
	NVME_CTRL_ONCS_COMPARE			= 1 << 0,
	NVME_CTRL_ONCS_WRITE_UNCORRECTABLE	= 1 << 1,
	NVME_CTRL_ONCS_DSM			= 1 << 2,
	NVME_CTRL_ONCS_WRITE_ZEROES		= 1 << 3,
	NVME_CTRL_ONCS_RESERVATIONS		= 1 << 5,
	NVME_CTRL_ONCS_TIMESTAMP		= 1 << 6,
	NVME_CTRL_VWC_PRESENT			= 1 << 0,
	NVME_CTRL_OACS_SEC_SUPP                 = 1 << 0,
	NVME_CTRL_OACS_सूचीECTIVES		= 1 << 5,
	NVME_CTRL_OACS_DBBUF_SUPP		= 1 << 8,
	NVME_CTRL_LPA_CMD_EFFECTS_LOG		= 1 << 1,
	NVME_CTRL_CTRATT_128_ID			= 1 << 0,
	NVME_CTRL_CTRATT_NON_OP_PSP		= 1 << 1,
	NVME_CTRL_CTRATT_NVM_SETS		= 1 << 2,
	NVME_CTRL_CTRATT_READ_RECV_LVLS		= 1 << 3,
	NVME_CTRL_CTRATT_ENDURANCE_GROUPS	= 1 << 4,
	NVME_CTRL_CTRATT_PREDICTABLE_LAT	= 1 << 5,
	NVME_CTRL_CTRATT_NAMESPACE_GRANULARITY	= 1 << 7,
	NVME_CTRL_CTRATT_UUID_LIST		= 1 << 9,
पूर्ण;

काष्ठा nvme_lbaf अणु
	__le16			ms;
	__u8			ds;
	__u8			rp;
पूर्ण;

काष्ठा nvme_id_ns अणु
	__le64			nsze;
	__le64			ncap;
	__le64			nuse;
	__u8			nsfeat;
	__u8			nlbaf;
	__u8			flbas;
	__u8			mc;
	__u8			dpc;
	__u8			dps;
	__u8			nmic;
	__u8			rescap;
	__u8			fpi;
	__u8			dlfeat;
	__le16			nawun;
	__le16			nawupf;
	__le16			nacwu;
	__le16			nअसलn;
	__le16			nabo;
	__le16			nअसलpf;
	__le16			noiob;
	__u8			nvmcap[16];
	__le16			npwg;
	__le16			npwa;
	__le16			npdg;
	__le16			npda;
	__le16			nows;
	__u8			rsvd74[18];
	__le32			anagrpid;
	__u8			rsvd96[3];
	__u8			nsattr;
	__le16			nvmsetid;
	__le16			endgid;
	__u8			nguid[16];
	__u8			eui64[8];
	काष्ठा nvme_lbaf	lbaf[16];
	__u8			rsvd192[192];
	__u8			vs[3712];
पूर्ण;

काष्ठा nvme_zns_lbafe अणु
	__le64			zsze;
	__u8			zdes;
	__u8			rsvd9[7];
पूर्ण;

काष्ठा nvme_id_ns_zns अणु
	__le16			zoc;
	__le16			ozcs;
	__le32			mar;
	__le32			mor;
	__le32			rrl;
	__le32			frl;
	__u8			rsvd20[2796];
	काष्ठा nvme_zns_lbafe	lbafe[16];
	__u8			rsvd3072[768];
	__u8			vs[256];
पूर्ण;

काष्ठा nvme_id_ctrl_zns अणु
	__u8	zasl;
	__u8	rsvd1[4095];
पूर्ण;

काष्ठा nvme_id_ctrl_nvm अणु
	__u8	vsl;
	__u8	wzsl;
	__u8	wusl;
	__u8	dmrl;
	__le32	dmrsl;
	__le64	dmsl;
	__u8	rsvd16[4080];
पूर्ण;

क्रमागत अणु
	NVME_ID_CNS_NS			= 0x00,
	NVME_ID_CNS_CTRL		= 0x01,
	NVME_ID_CNS_NS_ACTIVE_LIST	= 0x02,
	NVME_ID_CNS_NS_DESC_LIST	= 0x03,
	NVME_ID_CNS_CS_NS		= 0x05,
	NVME_ID_CNS_CS_CTRL		= 0x06,
	NVME_ID_CNS_NS_PRESENT_LIST	= 0x10,
	NVME_ID_CNS_NS_PRESENT		= 0x11,
	NVME_ID_CNS_CTRL_NS_LIST	= 0x12,
	NVME_ID_CNS_CTRL_LIST		= 0x13,
	NVME_ID_CNS_SCNDRY_CTRL_LIST	= 0x15,
	NVME_ID_CNS_NS_GRANULARITY	= 0x16,
	NVME_ID_CNS_UUID_LIST		= 0x17,
पूर्ण;

क्रमागत अणु
	NVME_CSI_NVM			= 0,
	NVME_CSI_ZNS			= 2,
पूर्ण;

क्रमागत अणु
	NVME_सूची_IDENTIFY		= 0x00,
	NVME_सूची_STREAMS		= 0x01,
	NVME_सूची_SND_ID_OP_ENABLE	= 0x01,
	NVME_सूची_SND_ST_OP_REL_ID	= 0x01,
	NVME_सूची_SND_ST_OP_REL_RSC	= 0x02,
	NVME_सूची_RCV_ID_OP_PARAM	= 0x01,
	NVME_सूची_RCV_ST_OP_PARAM	= 0x01,
	NVME_सूची_RCV_ST_OP_STATUS	= 0x02,
	NVME_सूची_RCV_ST_OP_RESOURCE	= 0x03,
	NVME_सूची_ENसूची			= 0x01,
पूर्ण;

क्रमागत अणु
	NVME_NS_FEAT_THIN	= 1 << 0,
	NVME_NS_FEAT_ATOMICS	= 1 << 1,
	NVME_NS_FEAT_IO_OPT	= 1 << 4,
	NVME_NS_ATTR_RO		= 1 << 0,
	NVME_NS_FLBAS_LBA_MASK	= 0xf,
	NVME_NS_FLBAS_META_EXT	= 0x10,
	NVME_NS_NMIC_SHARED	= 1 << 0,
	NVME_LBAF_RP_BEST	= 0,
	NVME_LBAF_RP_BETTER	= 1,
	NVME_LBAF_RP_GOOD	= 2,
	NVME_LBAF_RP_DEGRADED	= 3,
	NVME_NS_DPC_PI_LAST	= 1 << 4,
	NVME_NS_DPC_PI_FIRST	= 1 << 3,
	NVME_NS_DPC_PI_TYPE3	= 1 << 2,
	NVME_NS_DPC_PI_TYPE2	= 1 << 1,
	NVME_NS_DPC_PI_TYPE1	= 1 << 0,
	NVME_NS_DPS_PI_FIRST	= 1 << 3,
	NVME_NS_DPS_PI_MASK	= 0x7,
	NVME_NS_DPS_PI_TYPE1	= 1,
	NVME_NS_DPS_PI_TYPE2	= 2,
	NVME_NS_DPS_PI_TYPE3	= 3,
पूर्ण;

/* Identअगरy Namespace Metadata Capabilities (MC): */
क्रमागत अणु
	NVME_MC_EXTENDED_LBA	= (1 << 0),
	NVME_MC_METADATA_PTR	= (1 << 1),
पूर्ण;

काष्ठा nvme_ns_id_desc अणु
	__u8 nidt;
	__u8 nidl;
	__le16 reserved;
पूर्ण;

#घोषणा NVME_NIDT_EUI64_LEN	8
#घोषणा NVME_NIDT_NGUID_LEN	16
#घोषणा NVME_NIDT_UUID_LEN	16
#घोषणा NVME_NIDT_CSI_LEN	1

क्रमागत अणु
	NVME_NIDT_EUI64		= 0x01,
	NVME_NIDT_NGUID		= 0x02,
	NVME_NIDT_UUID		= 0x03,
	NVME_NIDT_CSI		= 0x04,
पूर्ण;

काष्ठा nvme_smart_log अणु
	__u8			critical_warning;
	__u8			temperature[2];
	__u8			avail_spare;
	__u8			spare_thresh;
	__u8			percent_used;
	__u8			endu_grp_crit_warn_sumry;
	__u8			rsvd7[25];
	__u8			data_units_पढ़ो[16];
	__u8			data_units_written[16];
	__u8			host_पढ़ोs[16];
	__u8			host_ग_लिखोs[16];
	__u8			ctrl_busy_समय[16];
	__u8			घातer_cycles[16];
	__u8			घातer_on_hours[16];
	__u8			unsafe_shutकरोwns[16];
	__u8			media_errors[16];
	__u8			num_err_log_entries[16];
	__le32			warning_temp_समय;
	__le32			critical_comp_समय;
	__le16			temp_sensor[8];
	__le32			thm_temp1_trans_count;
	__le32			thm_temp2_trans_count;
	__le32			thm_temp1_total_समय;
	__le32			thm_temp2_total_समय;
	__u8			rsvd232[280];
पूर्ण;

काष्ठा nvme_fw_slot_info_log अणु
	__u8			afi;
	__u8			rsvd1[7];
	__le64			frs[7];
	__u8			rsvd64[448];
पूर्ण;

क्रमागत अणु
	NVME_CMD_EFFECTS_CSUPP		= 1 << 0,
	NVME_CMD_EFFECTS_LBCC		= 1 << 1,
	NVME_CMD_EFFECTS_NCC		= 1 << 2,
	NVME_CMD_EFFECTS_NIC		= 1 << 3,
	NVME_CMD_EFFECTS_CCC		= 1 << 4,
	NVME_CMD_EFFECTS_CSE_MASK	= 3 << 16,
	NVME_CMD_EFFECTS_UUID_SEL	= 1 << 19,
पूर्ण;

काष्ठा nvme_effects_log अणु
	__le32 acs[256];
	__le32 iocs[256];
	__u8   resv[2048];
पूर्ण;

क्रमागत nvme_ana_state अणु
	NVME_ANA_OPTIMIZED		= 0x01,
	NVME_ANA_NONOPTIMIZED		= 0x02,
	NVME_ANA_INACCESSIBLE		= 0x03,
	NVME_ANA_PERSISTENT_LOSS	= 0x04,
	NVME_ANA_CHANGE			= 0x0f,
पूर्ण;

काष्ठा nvme_ana_group_desc अणु
	__le32	grpid;
	__le32	nnsids;
	__le64	chgcnt;
	__u8	state;
	__u8	rsvd17[15];
	__le32	nsids[];
पूर्ण;

/* flag क्रम the log specअगरic field of the ANA log */
#घोषणा NVME_ANA_LOG_RGO	(1 << 0)

काष्ठा nvme_ana_rsp_hdr अणु
	__le64	chgcnt;
	__le16	ngrps;
	__le16	rsvd10[3];
पूर्ण;

काष्ठा nvme_zone_descriptor अणु
	__u8		zt;
	__u8		zs;
	__u8		za;
	__u8		rsvd3[5];
	__le64		zcap;
	__le64		zslba;
	__le64		wp;
	__u8		rsvd32[32];
पूर्ण;

क्रमागत अणु
	NVME_ZONE_TYPE_SEQWRITE_REQ	= 0x2,
पूर्ण;

काष्ठा nvme_zone_report अणु
	__le64		nr_zones;
	__u8		resv8[56];
	काष्ठा nvme_zone_descriptor entries[];
पूर्ण;

क्रमागत अणु
	NVME_SMART_CRIT_SPARE		= 1 << 0,
	NVME_SMART_CRIT_TEMPERATURE	= 1 << 1,
	NVME_SMART_CRIT_RELIABILITY	= 1 << 2,
	NVME_SMART_CRIT_MEDIA		= 1 << 3,
	NVME_SMART_CRIT_VOLATILE_MEMORY	= 1 << 4,
पूर्ण;

क्रमागत अणु
	NVME_AER_ERROR			= 0,
	NVME_AER_SMART			= 1,
	NVME_AER_NOTICE			= 2,
	NVME_AER_CSS			= 6,
	NVME_AER_VS			= 7,
पूर्ण;

क्रमागत अणु
	NVME_AER_NOTICE_NS_CHANGED	= 0x00,
	NVME_AER_NOTICE_FW_ACT_STARTING = 0x01,
	NVME_AER_NOTICE_ANA		= 0x03,
	NVME_AER_NOTICE_DISC_CHANGED	= 0xf0,
पूर्ण;

क्रमागत अणु
	NVME_AEN_BIT_NS_ATTR		= 8,
	NVME_AEN_BIT_FW_ACT		= 9,
	NVME_AEN_BIT_ANA_CHANGE		= 11,
	NVME_AEN_BIT_DISC_CHANGE	= 31,
पूर्ण;

क्रमागत अणु
	NVME_AEN_CFG_NS_ATTR		= 1 << NVME_AEN_BIT_NS_ATTR,
	NVME_AEN_CFG_FW_ACT		= 1 << NVME_AEN_BIT_FW_ACT,
	NVME_AEN_CFG_ANA_CHANGE		= 1 << NVME_AEN_BIT_ANA_CHANGE,
	NVME_AEN_CFG_DISC_CHANGE	= 1 << NVME_AEN_BIT_DISC_CHANGE,
पूर्ण;

काष्ठा nvme_lba_range_type अणु
	__u8			type;
	__u8			attributes;
	__u8			rsvd2[14];
	__u64			slba;
	__u64			nlb;
	__u8			guid[16];
	__u8			rsvd48[16];
पूर्ण;

क्रमागत अणु
	NVME_LBART_TYPE_FS	= 0x01,
	NVME_LBART_TYPE_RAID	= 0x02,
	NVME_LBART_TYPE_CACHE	= 0x03,
	NVME_LBART_TYPE_SWAP	= 0x04,

	NVME_LBART_ATTRIB_TEMP	= 1 << 0,
	NVME_LBART_ATTRIB_HIDE	= 1 << 1,
पूर्ण;

काष्ठा nvme_reservation_status अणु
	__le32	gen;
	__u8	rtype;
	__u8	regctl[2];
	__u8	resv5[2];
	__u8	ptpls;
	__u8	resv10[13];
	काष्ठा अणु
		__le16	cntlid;
		__u8	rcsts;
		__u8	resv3[5];
		__le64	hostid;
		__le64	rkey;
	पूर्ण regctl_ds[];
पूर्ण;

क्रमागत nvme_async_event_type अणु
	NVME_AER_TYPE_ERROR	= 0,
	NVME_AER_TYPE_SMART	= 1,
	NVME_AER_TYPE_NOTICE	= 2,
पूर्ण;

/* I/O commands */

क्रमागत nvme_opcode अणु
	nvme_cmd_flush		= 0x00,
	nvme_cmd_ग_लिखो		= 0x01,
	nvme_cmd_पढ़ो		= 0x02,
	nvme_cmd_ग_लिखो_uncor	= 0x04,
	nvme_cmd_compare	= 0x05,
	nvme_cmd_ग_लिखो_zeroes	= 0x08,
	nvme_cmd_dsm		= 0x09,
	nvme_cmd_verअगरy		= 0x0c,
	nvme_cmd_resv_रेजिस्टर	= 0x0d,
	nvme_cmd_resv_report	= 0x0e,
	nvme_cmd_resv_acquire	= 0x11,
	nvme_cmd_resv_release	= 0x15,
	nvme_cmd_zone_mgmt_send	= 0x79,
	nvme_cmd_zone_mgmt_recv	= 0x7a,
	nvme_cmd_zone_append	= 0x7d,
पूर्ण;

#घोषणा nvme_opcode_name(opcode)	अणु opcode, #opcode पूर्ण
#घोषणा show_nvm_opcode_name(val)				\
	__prपूर्णांक_symbolic(val,					\
		nvme_opcode_name(nvme_cmd_flush),		\
		nvme_opcode_name(nvme_cmd_ग_लिखो),		\
		nvme_opcode_name(nvme_cmd_पढ़ो),		\
		nvme_opcode_name(nvme_cmd_ग_लिखो_uncor),		\
		nvme_opcode_name(nvme_cmd_compare),		\
		nvme_opcode_name(nvme_cmd_ग_लिखो_zeroes),	\
		nvme_opcode_name(nvme_cmd_dsm),			\
		nvme_opcode_name(nvme_cmd_resv_रेजिस्टर),	\
		nvme_opcode_name(nvme_cmd_resv_report),		\
		nvme_opcode_name(nvme_cmd_resv_acquire),	\
		nvme_opcode_name(nvme_cmd_resv_release),	\
		nvme_opcode_name(nvme_cmd_zone_mgmt_send),	\
		nvme_opcode_name(nvme_cmd_zone_mgmt_recv),	\
		nvme_opcode_name(nvme_cmd_zone_append))



/*
 * Descriptor subtype - lower 4 bits of nvme_(keyed_)sgl_desc identअगरier
 *
 * @NVME_SGL_FMT_ADDRESS:     असलolute address of the data block
 * @NVME_SGL_FMT_OFFSET:      relative offset of the in-capsule data block
 * @NVME_SGL_FMT_TRANSPORT_A: transport defined क्रमmat, value 0xA
 * @NVME_SGL_FMT_INVALIDATE:  RDMA transport specअगरic remote invalidation
 *                            request subtype
 */
क्रमागत अणु
	NVME_SGL_FMT_ADDRESS		= 0x00,
	NVME_SGL_FMT_OFFSET		= 0x01,
	NVME_SGL_FMT_TRANSPORT_A	= 0x0A,
	NVME_SGL_FMT_INVALIDATE		= 0x0f,
पूर्ण;

/*
 * Descriptor type - upper 4 bits of nvme_(keyed_)sgl_desc identअगरier
 *
 * For काष्ठा nvme_sgl_desc:
 *   @NVME_SGL_FMT_DATA_DESC:		data block descriptor
 *   @NVME_SGL_FMT_SEG_DESC:		sgl segment descriptor
 *   @NVME_SGL_FMT_LAST_SEG_DESC:	last sgl segment descriptor
 *
 * For काष्ठा nvme_keyed_sgl_desc:
 *   @NVME_KEY_SGL_FMT_DATA_DESC:	keyed data block descriptor
 *
 * Transport-specअगरic SGL types:
 *   @NVME_TRANSPORT_SGL_DATA_DESC:	Transport SGL data dlock descriptor
 */
क्रमागत अणु
	NVME_SGL_FMT_DATA_DESC		= 0x00,
	NVME_SGL_FMT_SEG_DESC		= 0x02,
	NVME_SGL_FMT_LAST_SEG_DESC	= 0x03,
	NVME_KEY_SGL_FMT_DATA_DESC	= 0x04,
	NVME_TRANSPORT_SGL_DATA_DESC	= 0x05,
पूर्ण;

काष्ठा nvme_sgl_desc अणु
	__le64	addr;
	__le32	length;
	__u8	rsvd[3];
	__u8	type;
पूर्ण;

काष्ठा nvme_keyed_sgl_desc अणु
	__le64	addr;
	__u8	length[3];
	__u8	key[4];
	__u8	type;
पूर्ण;

जोड़ nvme_data_ptr अणु
	काष्ठा अणु
		__le64	prp1;
		__le64	prp2;
	पूर्ण;
	काष्ठा nvme_sgl_desc	sgl;
	काष्ठा nvme_keyed_sgl_desc ksgl;
पूर्ण;

/*
 * Lowest two bits of our flags field (FUSE field in the spec):
 *
 * @NVME_CMD_FUSE_FIRST:   Fused Operation, first command
 * @NVME_CMD_FUSE_SECOND:  Fused Operation, second command
 *
 * Highest two bits in our flags field (PSDT field in the spec):
 *
 * @NVME_CMD_PSDT_SGL_METABUF:	Use SGLS क्रम this transfer,
 *	If used, MPTR contains addr of single physical buffer (byte aligned).
 * @NVME_CMD_PSDT_SGL_METASEG:	Use SGLS क्रम this transfer,
 *	If used, MPTR contains an address of an SGL segment containing
 *	exactly 1 SGL descriptor (qword aligned).
 */
क्रमागत अणु
	NVME_CMD_FUSE_FIRST	= (1 << 0),
	NVME_CMD_FUSE_SECOND	= (1 << 1),

	NVME_CMD_SGL_METABUF	= (1 << 6),
	NVME_CMD_SGL_METASEG	= (1 << 7),
	NVME_CMD_SGL_ALL	= NVME_CMD_SGL_METABUF | NVME_CMD_SGL_METASEG,
पूर्ण;

काष्ठा nvme_common_command अणु
	__u8			opcode;
	__u8			flags;
	__u16			command_id;
	__le32			nsid;
	__le32			cdw2[2];
	__le64			metadata;
	जोड़ nvme_data_ptr	dptr;
	__le32			cdw10;
	__le32			cdw11;
	__le32			cdw12;
	__le32			cdw13;
	__le32			cdw14;
	__le32			cdw15;
पूर्ण;

काष्ठा nvme_rw_command अणु
	__u8			opcode;
	__u8			flags;
	__u16			command_id;
	__le32			nsid;
	__u64			rsvd2;
	__le64			metadata;
	जोड़ nvme_data_ptr	dptr;
	__le64			slba;
	__le16			length;
	__le16			control;
	__le32			dsmgmt;
	__le32			reftag;
	__le16			apptag;
	__le16			appmask;
पूर्ण;

क्रमागत अणु
	NVME_RW_LR			= 1 << 15,
	NVME_RW_FUA			= 1 << 14,
	NVME_RW_APPEND_PIREMAP		= 1 << 9,
	NVME_RW_DSM_FREQ_UNSPEC		= 0,
	NVME_RW_DSM_FREQ_TYPICAL	= 1,
	NVME_RW_DSM_FREQ_RARE		= 2,
	NVME_RW_DSM_FREQ_READS		= 3,
	NVME_RW_DSM_FREQ_WRITES		= 4,
	NVME_RW_DSM_FREQ_RW		= 5,
	NVME_RW_DSM_FREQ_ONCE		= 6,
	NVME_RW_DSM_FREQ_PREFETCH	= 7,
	NVME_RW_DSM_FREQ_TEMP		= 8,
	NVME_RW_DSM_LATENCY_NONE	= 0 << 4,
	NVME_RW_DSM_LATENCY_IDLE	= 1 << 4,
	NVME_RW_DSM_LATENCY_NORM	= 2 << 4,
	NVME_RW_DSM_LATENCY_LOW		= 3 << 4,
	NVME_RW_DSM_SEQ_REQ		= 1 << 6,
	NVME_RW_DSM_COMPRESSED		= 1 << 7,
	NVME_RW_PRINFO_PRCHK_REF	= 1 << 10,
	NVME_RW_PRINFO_PRCHK_APP	= 1 << 11,
	NVME_RW_PRINFO_PRCHK_GUARD	= 1 << 12,
	NVME_RW_PRINFO_PRACT		= 1 << 13,
	NVME_RW_DTYPE_STREAMS		= 1 << 4,
पूर्ण;

काष्ठा nvme_dsm_cmd अणु
	__u8			opcode;
	__u8			flags;
	__u16			command_id;
	__le32			nsid;
	__u64			rsvd2[2];
	जोड़ nvme_data_ptr	dptr;
	__le32			nr;
	__le32			attributes;
	__u32			rsvd12[4];
पूर्ण;

क्रमागत अणु
	NVME_DSMGMT_IDR		= 1 << 0,
	NVME_DSMGMT_IDW		= 1 << 1,
	NVME_DSMGMT_AD		= 1 << 2,
पूर्ण;

#घोषणा NVME_DSM_MAX_RANGES	256

काष्ठा nvme_dsm_range अणु
	__le32			cattr;
	__le32			nlb;
	__le64			slba;
पूर्ण;

काष्ठा nvme_ग_लिखो_zeroes_cmd अणु
	__u8			opcode;
	__u8			flags;
	__u16			command_id;
	__le32			nsid;
	__u64			rsvd2;
	__le64			metadata;
	जोड़ nvme_data_ptr	dptr;
	__le64			slba;
	__le16			length;
	__le16			control;
	__le32			dsmgmt;
	__le32			reftag;
	__le16			apptag;
	__le16			appmask;
पूर्ण;

क्रमागत nvme_zone_mgmt_action अणु
	NVME_ZONE_CLOSE		= 0x1,
	NVME_ZONE_FINISH	= 0x2,
	NVME_ZONE_OPEN		= 0x3,
	NVME_ZONE_RESET		= 0x4,
	NVME_ZONE_OFFLINE	= 0x5,
	NVME_ZONE_SET_DESC_EXT	= 0x10,
पूर्ण;

काष्ठा nvme_zone_mgmt_send_cmd अणु
	__u8			opcode;
	__u8			flags;
	__u16			command_id;
	__le32			nsid;
	__le32			cdw2[2];
	__le64			metadata;
	जोड़ nvme_data_ptr	dptr;
	__le64			slba;
	__le32			cdw12;
	__u8			zsa;
	__u8			select_all;
	__u8			rsvd13[2];
	__le32			cdw14[2];
पूर्ण;

काष्ठा nvme_zone_mgmt_recv_cmd अणु
	__u8			opcode;
	__u8			flags;
	__u16			command_id;
	__le32			nsid;
	__le64			rsvd2[2];
	जोड़ nvme_data_ptr	dptr;
	__le64			slba;
	__le32			numd;
	__u8			zra;
	__u8			zrasf;
	__u8			pr;
	__u8			rsvd13;
	__le32			cdw14[2];
पूर्ण;

क्रमागत अणु
	NVME_ZRA_ZONE_REPORT		= 0,
	NVME_ZRASF_ZONE_REPORT_ALL	= 0,
	NVME_REPORT_ZONE_PARTIAL	= 1,
पूर्ण;

/* Features */

क्रमागत अणु
	NVME_TEMP_THRESH_MASK		= 0xffff,
	NVME_TEMP_THRESH_SELECT_SHIFT	= 16,
	NVME_TEMP_THRESH_TYPE_UNDER	= 0x100000,
पूर्ण;

काष्ठा nvme_feat_स्वतः_pst अणु
	__le64 entries[32];
पूर्ण;

क्रमागत अणु
	NVME_HOST_MEM_ENABLE	= (1 << 0),
	NVME_HOST_MEM_RETURN	= (1 << 1),
पूर्ण;

काष्ठा nvme_feat_host_behavior अणु
	__u8 acre;
	__u8 resv1[511];
पूर्ण;

क्रमागत अणु
	NVME_ENABLE_ACRE	= 1,
पूर्ण;

/* Admin commands */

क्रमागत nvme_admin_opcode अणु
	nvme_admin_delete_sq		= 0x00,
	nvme_admin_create_sq		= 0x01,
	nvme_admin_get_log_page		= 0x02,
	nvme_admin_delete_cq		= 0x04,
	nvme_admin_create_cq		= 0x05,
	nvme_admin_identअगरy		= 0x06,
	nvme_admin_पात_cmd		= 0x08,
	nvme_admin_set_features		= 0x09,
	nvme_admin_get_features		= 0x0a,
	nvme_admin_async_event		= 0x0c,
	nvme_admin_ns_mgmt		= 0x0d,
	nvme_admin_activate_fw		= 0x10,
	nvme_admin_करोwnload_fw		= 0x11,
	nvme_admin_dev_self_test	= 0x14,
	nvme_admin_ns_attach		= 0x15,
	nvme_admin_keep_alive		= 0x18,
	nvme_admin_directive_send	= 0x19,
	nvme_admin_directive_recv	= 0x1a,
	nvme_admin_भव_mgmt		= 0x1c,
	nvme_admin_nvme_mi_send		= 0x1d,
	nvme_admin_nvme_mi_recv		= 0x1e,
	nvme_admin_dbbuf		= 0x7C,
	nvme_admin_क्रमmat_nvm		= 0x80,
	nvme_admin_security_send	= 0x81,
	nvme_admin_security_recv	= 0x82,
	nvme_admin_sanitize_nvm		= 0x84,
	nvme_admin_get_lba_status	= 0x86,
	nvme_admin_venकरोr_start		= 0xC0,
पूर्ण;

#घोषणा nvme_admin_opcode_name(opcode)	अणु opcode, #opcode पूर्ण
#घोषणा show_admin_opcode_name(val)					\
	__prपूर्णांक_symbolic(val,						\
		nvme_admin_opcode_name(nvme_admin_delete_sq),		\
		nvme_admin_opcode_name(nvme_admin_create_sq),		\
		nvme_admin_opcode_name(nvme_admin_get_log_page),	\
		nvme_admin_opcode_name(nvme_admin_delete_cq),		\
		nvme_admin_opcode_name(nvme_admin_create_cq),		\
		nvme_admin_opcode_name(nvme_admin_identअगरy),		\
		nvme_admin_opcode_name(nvme_admin_पात_cmd),		\
		nvme_admin_opcode_name(nvme_admin_set_features),	\
		nvme_admin_opcode_name(nvme_admin_get_features),	\
		nvme_admin_opcode_name(nvme_admin_async_event),		\
		nvme_admin_opcode_name(nvme_admin_ns_mgmt),		\
		nvme_admin_opcode_name(nvme_admin_activate_fw),		\
		nvme_admin_opcode_name(nvme_admin_करोwnload_fw),		\
		nvme_admin_opcode_name(nvme_admin_ns_attach),		\
		nvme_admin_opcode_name(nvme_admin_keep_alive),		\
		nvme_admin_opcode_name(nvme_admin_directive_send),	\
		nvme_admin_opcode_name(nvme_admin_directive_recv),	\
		nvme_admin_opcode_name(nvme_admin_dbbuf),		\
		nvme_admin_opcode_name(nvme_admin_क्रमmat_nvm),		\
		nvme_admin_opcode_name(nvme_admin_security_send),	\
		nvme_admin_opcode_name(nvme_admin_security_recv),	\
		nvme_admin_opcode_name(nvme_admin_sanitize_nvm),	\
		nvme_admin_opcode_name(nvme_admin_get_lba_status))

क्रमागत अणु
	NVME_QUEUE_PHYS_CONTIG	= (1 << 0),
	NVME_CQ_IRQ_ENABLED	= (1 << 1),
	NVME_SQ_PRIO_URGENT	= (0 << 1),
	NVME_SQ_PRIO_HIGH	= (1 << 1),
	NVME_SQ_PRIO_MEDIUM	= (2 << 1),
	NVME_SQ_PRIO_LOW	= (3 << 1),
	NVME_FEAT_ARBITRATION	= 0x01,
	NVME_FEAT_POWER_MGMT	= 0x02,
	NVME_FEAT_LBA_RANGE	= 0x03,
	NVME_FEAT_TEMP_THRESH	= 0x04,
	NVME_FEAT_ERR_RECOVERY	= 0x05,
	NVME_FEAT_VOLATILE_WC	= 0x06,
	NVME_FEAT_NUM_QUEUES	= 0x07,
	NVME_FEAT_IRQ_COALESCE	= 0x08,
	NVME_FEAT_IRQ_CONFIG	= 0x09,
	NVME_FEAT_WRITE_ATOMIC	= 0x0a,
	NVME_FEAT_ASYNC_EVENT	= 0x0b,
	NVME_FEAT_AUTO_PST	= 0x0c,
	NVME_FEAT_HOST_MEM_BUF	= 0x0d,
	NVME_FEAT_TIMESTAMP	= 0x0e,
	NVME_FEAT_KATO		= 0x0f,
	NVME_FEAT_HCTM		= 0x10,
	NVME_FEAT_NOPSC		= 0x11,
	NVME_FEAT_RRL		= 0x12,
	NVME_FEAT_PLM_CONFIG	= 0x13,
	NVME_FEAT_PLM_WINDOW	= 0x14,
	NVME_FEAT_HOST_BEHAVIOR	= 0x16,
	NVME_FEAT_SANITIZE	= 0x17,
	NVME_FEAT_SW_PROGRESS	= 0x80,
	NVME_FEAT_HOST_ID	= 0x81,
	NVME_FEAT_RESV_MASK	= 0x82,
	NVME_FEAT_RESV_PERSIST	= 0x83,
	NVME_FEAT_WRITE_PROTECT	= 0x84,
	NVME_FEAT_VENDOR_START	= 0xC0,
	NVME_FEAT_VENDOR_END	= 0xFF,
	NVME_LOG_ERROR		= 0x01,
	NVME_LOG_SMART		= 0x02,
	NVME_LOG_FW_SLOT	= 0x03,
	NVME_LOG_CHANGED_NS	= 0x04,
	NVME_LOG_CMD_EFFECTS	= 0x05,
	NVME_LOG_DEVICE_SELF_TEST = 0x06,
	NVME_LOG_TELEMETRY_HOST = 0x07,
	NVME_LOG_TELEMETRY_CTRL = 0x08,
	NVME_LOG_ENDURANCE_GROUP = 0x09,
	NVME_LOG_ANA		= 0x0c,
	NVME_LOG_DISC		= 0x70,
	NVME_LOG_RESERVATION	= 0x80,
	NVME_FWACT_REPL		= (0 << 3),
	NVME_FWACT_REPL_ACTV	= (1 << 3),
	NVME_FWACT_ACTV		= (2 << 3),
पूर्ण;

/* NVMe Namespace Write Protect State */
क्रमागत अणु
	NVME_NS_NO_WRITE_PROTECT = 0,
	NVME_NS_WRITE_PROTECT,
	NVME_NS_WRITE_PROTECT_POWER_CYCLE,
	NVME_NS_WRITE_PROTECT_PERMANENT,
पूर्ण;

#घोषणा NVME_MAX_CHANGED_NAMESPACES	1024

काष्ठा nvme_identअगरy अणु
	__u8			opcode;
	__u8			flags;
	__u16			command_id;
	__le32			nsid;
	__u64			rsvd2[2];
	जोड़ nvme_data_ptr	dptr;
	__u8			cns;
	__u8			rsvd3;
	__le16			ctrlid;
	__u8			rsvd11[3];
	__u8			csi;
	__u32			rsvd12[4];
पूर्ण;

#घोषणा NVME_IDENTIFY_DATA_SIZE 4096

काष्ठा nvme_features अणु
	__u8			opcode;
	__u8			flags;
	__u16			command_id;
	__le32			nsid;
	__u64			rsvd2[2];
	जोड़ nvme_data_ptr	dptr;
	__le32			fid;
	__le32			dword11;
	__le32                  dword12;
	__le32                  dword13;
	__le32                  dword14;
	__le32                  dword15;
पूर्ण;

काष्ठा nvme_host_mem_buf_desc अणु
	__le64			addr;
	__le32			size;
	__u32			rsvd;
पूर्ण;

काष्ठा nvme_create_cq अणु
	__u8			opcode;
	__u8			flags;
	__u16			command_id;
	__u32			rsvd1[5];
	__le64			prp1;
	__u64			rsvd8;
	__le16			cqid;
	__le16			qsize;
	__le16			cq_flags;
	__le16			irq_vector;
	__u32			rsvd12[4];
पूर्ण;

काष्ठा nvme_create_sq अणु
	__u8			opcode;
	__u8			flags;
	__u16			command_id;
	__u32			rsvd1[5];
	__le64			prp1;
	__u64			rsvd8;
	__le16			sqid;
	__le16			qsize;
	__le16			sq_flags;
	__le16			cqid;
	__u32			rsvd12[4];
पूर्ण;

काष्ठा nvme_delete_queue अणु
	__u8			opcode;
	__u8			flags;
	__u16			command_id;
	__u32			rsvd1[9];
	__le16			qid;
	__u16			rsvd10;
	__u32			rsvd11[5];
पूर्ण;

काष्ठा nvme_पात_cmd अणु
	__u8			opcode;
	__u8			flags;
	__u16			command_id;
	__u32			rsvd1[9];
	__le16			sqid;
	__u16			cid;
	__u32			rsvd11[5];
पूर्ण;

काष्ठा nvme_करोwnload_firmware अणु
	__u8			opcode;
	__u8			flags;
	__u16			command_id;
	__u32			rsvd1[5];
	जोड़ nvme_data_ptr	dptr;
	__le32			numd;
	__le32			offset;
	__u32			rsvd12[4];
पूर्ण;

काष्ठा nvme_क्रमmat_cmd अणु
	__u8			opcode;
	__u8			flags;
	__u16			command_id;
	__le32			nsid;
	__u64			rsvd2[4];
	__le32			cdw10;
	__u32			rsvd11[5];
पूर्ण;

काष्ठा nvme_get_log_page_command अणु
	__u8			opcode;
	__u8			flags;
	__u16			command_id;
	__le32			nsid;
	__u64			rsvd2[2];
	जोड़ nvme_data_ptr	dptr;
	__u8			lid;
	__u8			lsp; /* upper 4 bits reserved */
	__le16			numdl;
	__le16			numdu;
	__u16			rsvd11;
	जोड़ अणु
		काष्ठा अणु
			__le32 lpol;
			__le32 lpou;
		पूर्ण;
		__le64 lpo;
	पूर्ण;
	__u8			rsvd14[3];
	__u8			csi;
	__u32			rsvd15;
पूर्ण;

काष्ठा nvme_directive_cmd अणु
	__u8			opcode;
	__u8			flags;
	__u16			command_id;
	__le32			nsid;
	__u64			rsvd2[2];
	जोड़ nvme_data_ptr	dptr;
	__le32			numd;
	__u8			करोper;
	__u8			dtype;
	__le16			dspec;
	__u8			endir;
	__u8			tdtype;
	__u16			rsvd15;

	__u32			rsvd16[3];
पूर्ण;

/*
 * Fabrics subcommands.
 */
क्रमागत nvmf_fabrics_opcode अणु
	nvme_fabrics_command		= 0x7f,
पूर्ण;

क्रमागत nvmf_capsule_command अणु
	nvme_fabrics_type_property_set	= 0x00,
	nvme_fabrics_type_connect	= 0x01,
	nvme_fabrics_type_property_get	= 0x04,
पूर्ण;

#घोषणा nvme_fabrics_type_name(type)   अणु type, #type पूर्ण
#घोषणा show_fabrics_type_name(type)					\
	__prपूर्णांक_symbolic(type,						\
		nvme_fabrics_type_name(nvme_fabrics_type_property_set),	\
		nvme_fabrics_type_name(nvme_fabrics_type_connect),	\
		nvme_fabrics_type_name(nvme_fabrics_type_property_get))

/*
 * If not fabrics command, fctype will be ignored.
 */
#घोषणा show_opcode_name(qid, opcode, fctype)			\
	((opcode) == nvme_fabrics_command ?			\
	 show_fabrics_type_name(fctype) :			\
	((qid) ?						\
	 show_nvm_opcode_name(opcode) :				\
	 show_admin_opcode_name(opcode)))

काष्ठा nvmf_common_command अणु
	__u8	opcode;
	__u8	resv1;
	__u16	command_id;
	__u8	fctype;
	__u8	resv2[35];
	__u8	ts[24];
पूर्ण;

/*
 * The legal cntlid range a NVMe Target will provide.
 * Note that cntlid of value 0 is considered illegal in the fabrics world.
 * Devices based on earlier specs did not have the subप्रणाली concept;
 * thereक्रमe, those devices had their cntlid value set to 0 as a result.
 */
#घोषणा NVME_CNTLID_MIN		1
#घोषणा NVME_CNTLID_MAX		0xffef
#घोषणा NVME_CNTLID_DYNAMIC	0xffff

#घोषणा MAX_DISC_LOGS	255

/* Discovery log page entry */
काष्ठा nvmf_disc_rsp_page_entry अणु
	__u8		trtype;
	__u8		adrfam;
	__u8		subtype;
	__u8		treq;
	__le16		portid;
	__le16		cntlid;
	__le16		asqsz;
	__u8		resv8[22];
	अक्षर		trsvcid[NVMF_TRSVCID_SIZE];
	__u8		resv64[192];
	अक्षर		subnqn[NVMF_NQN_FIELD_LEN];
	अक्षर		traddr[NVMF_TRADDR_SIZE];
	जोड़ tsas अणु
		अक्षर		common[NVMF_TSAS_SIZE];
		काष्ठा rdma अणु
			__u8	qptype;
			__u8	prtype;
			__u8	cms;
			__u8	resv3[5];
			__u16	pkey;
			__u8	resv10[246];
		पूर्ण rdma;
	पूर्ण tsas;
पूर्ण;

/* Discovery log page header */
काष्ठा nvmf_disc_rsp_page_hdr अणु
	__le64		genctr;
	__le64		numrec;
	__le16		recfmt;
	__u8		resv14[1006];
	काष्ठा nvmf_disc_rsp_page_entry entries[];
पूर्ण;

क्रमागत अणु
	NVME_CONNECT_DISABLE_SQFLOW	= (1 << 2),
पूर्ण;

काष्ठा nvmf_connect_command अणु
	__u8		opcode;
	__u8		resv1;
	__u16		command_id;
	__u8		fctype;
	__u8		resv2[19];
	जोड़ nvme_data_ptr dptr;
	__le16		recfmt;
	__le16		qid;
	__le16		sqsize;
	__u8		cattr;
	__u8		resv3;
	__le32		kato;
	__u8		resv4[12];
पूर्ण;

काष्ठा nvmf_connect_data अणु
	uuid_t		hostid;
	__le16		cntlid;
	अक्षर		resv4[238];
	अक्षर		subsysnqn[NVMF_NQN_FIELD_LEN];
	अक्षर		hostnqn[NVMF_NQN_FIELD_LEN];
	अक्षर		resv5[256];
पूर्ण;

काष्ठा nvmf_property_set_command अणु
	__u8		opcode;
	__u8		resv1;
	__u16		command_id;
	__u8		fctype;
	__u8		resv2[35];
	__u8		attrib;
	__u8		resv3[3];
	__le32		offset;
	__le64		value;
	__u8		resv4[8];
पूर्ण;

काष्ठा nvmf_property_get_command अणु
	__u8		opcode;
	__u8		resv1;
	__u16		command_id;
	__u8		fctype;
	__u8		resv2[35];
	__u8		attrib;
	__u8		resv3[3];
	__le32		offset;
	__u8		resv4[16];
पूर्ण;

काष्ठा nvme_dbbuf अणु
	__u8			opcode;
	__u8			flags;
	__u16			command_id;
	__u32			rsvd1[5];
	__le64			prp1;
	__le64			prp2;
	__u32			rsvd12[6];
पूर्ण;

काष्ठा streams_directive_params अणु
	__le16	msl;
	__le16	nssa;
	__le16	nsso;
	__u8	rsvd[10];
	__le32	sws;
	__le16	sgs;
	__le16	nsa;
	__le16	nso;
	__u8	rsvd2[6];
पूर्ण;

काष्ठा nvme_command अणु
	जोड़ अणु
		काष्ठा nvme_common_command common;
		काष्ठा nvme_rw_command rw;
		काष्ठा nvme_identअगरy identअगरy;
		काष्ठा nvme_features features;
		काष्ठा nvme_create_cq create_cq;
		काष्ठा nvme_create_sq create_sq;
		काष्ठा nvme_delete_queue delete_queue;
		काष्ठा nvme_करोwnload_firmware dlfw;
		काष्ठा nvme_क्रमmat_cmd क्रमmat;
		काष्ठा nvme_dsm_cmd dsm;
		काष्ठा nvme_ग_लिखो_zeroes_cmd ग_लिखो_zeroes;
		काष्ठा nvme_zone_mgmt_send_cmd zms;
		काष्ठा nvme_zone_mgmt_recv_cmd zmr;
		काष्ठा nvme_पात_cmd पात;
		काष्ठा nvme_get_log_page_command get_log_page;
		काष्ठा nvmf_common_command fabrics;
		काष्ठा nvmf_connect_command connect;
		काष्ठा nvmf_property_set_command prop_set;
		काष्ठा nvmf_property_get_command prop_get;
		काष्ठा nvme_dbbuf dbbuf;
		काष्ठा nvme_directive_cmd directive;
	पूर्ण;
पूर्ण;

अटल अंतरभूत bool nvme_is_fabrics(काष्ठा nvme_command *cmd)
अणु
	वापस cmd->common.opcode == nvme_fabrics_command;
पूर्ण

काष्ठा nvme_error_slot अणु
	__le64		error_count;
	__le16		sqid;
	__le16		cmdid;
	__le16		status_field;
	__le16		param_error_location;
	__le64		lba;
	__le32		nsid;
	__u8		vs;
	__u8		resv[3];
	__le64		cs;
	__u8		resv2[24];
पूर्ण;

अटल अंतरभूत bool nvme_is_ग_लिखो(काष्ठा nvme_command *cmd)
अणु
	/*
	 * What a mess...
	 *
	 * Why can't we simply have a Fabrics In and Fabrics out command?
	 */
	अगर (unlikely(nvme_is_fabrics(cmd)))
		वापस cmd->fabrics.fctype & 1;
	वापस cmd->common.opcode & 1;
पूर्ण

क्रमागत अणु
	/*
	 * Generic Command Status:
	 */
	NVME_SC_SUCCESS			= 0x0,
	NVME_SC_INVALID_OPCODE		= 0x1,
	NVME_SC_INVALID_FIELD		= 0x2,
	NVME_SC_CMDID_CONFLICT		= 0x3,
	NVME_SC_DATA_XFER_ERROR		= 0x4,
	NVME_SC_POWER_LOSS		= 0x5,
	NVME_SC_INTERNAL		= 0x6,
	NVME_SC_ABORT_REQ		= 0x7,
	NVME_SC_ABORT_QUEUE		= 0x8,
	NVME_SC_FUSED_FAIL		= 0x9,
	NVME_SC_FUSED_MISSING		= 0xa,
	NVME_SC_INVALID_NS		= 0xb,
	NVME_SC_CMD_SEQ_ERROR		= 0xc,
	NVME_SC_SGL_INVALID_LAST	= 0xd,
	NVME_SC_SGL_INVALID_COUNT	= 0xe,
	NVME_SC_SGL_INVALID_DATA	= 0xf,
	NVME_SC_SGL_INVALID_METADATA	= 0x10,
	NVME_SC_SGL_INVALID_TYPE	= 0x11,
	NVME_SC_CMB_INVALID_USE		= 0x12,
	NVME_SC_PRP_INVALID_OFFSET	= 0x13,
	NVME_SC_ATOMIC_WU_EXCEEDED	= 0x14,
	NVME_SC_OP_DENIED		= 0x15,
	NVME_SC_SGL_INVALID_OFFSET	= 0x16,
	NVME_SC_RESERVED		= 0x17,
	NVME_SC_HOST_ID_INCONSIST	= 0x18,
	NVME_SC_KA_TIMEOUT_EXPIRED	= 0x19,
	NVME_SC_KA_TIMEOUT_INVALID	= 0x1A,
	NVME_SC_ABORTED_PREEMPT_ABORT	= 0x1B,
	NVME_SC_SANITIZE_FAILED		= 0x1C,
	NVME_SC_SANITIZE_IN_PROGRESS	= 0x1D,
	NVME_SC_SGL_INVALID_GRANULARITY	= 0x1E,
	NVME_SC_CMD_NOT_SUP_CMB_QUEUE	= 0x1F,
	NVME_SC_NS_WRITE_PROTECTED	= 0x20,
	NVME_SC_CMD_INTERRUPTED		= 0x21,
	NVME_SC_TRANSIENT_TR_ERR	= 0x22,

	NVME_SC_LBA_RANGE		= 0x80,
	NVME_SC_CAP_EXCEEDED		= 0x81,
	NVME_SC_NS_NOT_READY		= 0x82,
	NVME_SC_RESERVATION_CONFLICT	= 0x83,
	NVME_SC_FORMAT_IN_PROGRESS	= 0x84,

	/*
	 * Command Specअगरic Status:
	 */
	NVME_SC_CQ_INVALID		= 0x100,
	NVME_SC_QID_INVALID		= 0x101,
	NVME_SC_QUEUE_SIZE		= 0x102,
	NVME_SC_ABORT_LIMIT		= 0x103,
	NVME_SC_ABORT_MISSING		= 0x104,
	NVME_SC_ASYNC_LIMIT		= 0x105,
	NVME_SC_FIRMWARE_SLOT		= 0x106,
	NVME_SC_FIRMWARE_IMAGE		= 0x107,
	NVME_SC_INVALID_VECTOR		= 0x108,
	NVME_SC_INVALID_LOG_PAGE	= 0x109,
	NVME_SC_INVALID_FORMAT		= 0x10a,
	NVME_SC_FW_NEEDS_CONV_RESET	= 0x10b,
	NVME_SC_INVALID_QUEUE		= 0x10c,
	NVME_SC_FEATURE_NOT_SAVEABLE	= 0x10d,
	NVME_SC_FEATURE_NOT_CHANGEABLE	= 0x10e,
	NVME_SC_FEATURE_NOT_PER_NS	= 0x10f,
	NVME_SC_FW_NEEDS_SUBSYS_RESET	= 0x110,
	NVME_SC_FW_NEEDS_RESET		= 0x111,
	NVME_SC_FW_NEEDS_MAX_TIME	= 0x112,
	NVME_SC_FW_ACTIVATE_PROHIBITED	= 0x113,
	NVME_SC_OVERLAPPING_RANGE	= 0x114,
	NVME_SC_NS_INSUFFICIENT_CAP	= 0x115,
	NVME_SC_NS_ID_UNAVAILABLE	= 0x116,
	NVME_SC_NS_ALREADY_ATTACHED	= 0x118,
	NVME_SC_NS_IS_PRIVATE		= 0x119,
	NVME_SC_NS_NOT_ATTACHED		= 0x11a,
	NVME_SC_THIN_PROV_NOT_SUPP	= 0x11b,
	NVME_SC_CTRL_LIST_INVALID	= 0x11c,
	NVME_SC_SELT_TEST_IN_PROGRESS	= 0x11d,
	NVME_SC_BP_WRITE_PROHIBITED	= 0x11e,
	NVME_SC_CTRL_ID_INVALID		= 0x11f,
	NVME_SC_SEC_CTRL_STATE_INVALID	= 0x120,
	NVME_SC_CTRL_RES_NUM_INVALID	= 0x121,
	NVME_SC_RES_ID_INVALID		= 0x122,
	NVME_SC_PMR_SAN_PROHIBITED	= 0x123,
	NVME_SC_ANA_GROUP_ID_INVALID	= 0x124,
	NVME_SC_ANA_ATTACH_FAILED	= 0x125,

	/*
	 * I/O Command Set Specअगरic - NVM commands:
	 */
	NVME_SC_BAD_ATTRIBUTES		= 0x180,
	NVME_SC_INVALID_PI		= 0x181,
	NVME_SC_READ_ONLY		= 0x182,
	NVME_SC_ONCS_NOT_SUPPORTED	= 0x183,

	/*
	 * I/O Command Set Specअगरic - Fabrics commands:
	 */
	NVME_SC_CONNECT_FORMAT		= 0x180,
	NVME_SC_CONNECT_CTRL_BUSY	= 0x181,
	NVME_SC_CONNECT_INVALID_PARAM	= 0x182,
	NVME_SC_CONNECT_RESTART_DISC	= 0x183,
	NVME_SC_CONNECT_INVALID_HOST	= 0x184,

	NVME_SC_DISCOVERY_RESTART	= 0x190,
	NVME_SC_AUTH_REQUIRED		= 0x191,

	/*
	 * I/O Command Set Specअगरic - Zoned commands:
	 */
	NVME_SC_ZONE_BOUNDARY_ERROR	= 0x1b8,
	NVME_SC_ZONE_FULL		= 0x1b9,
	NVME_SC_ZONE_READ_ONLY		= 0x1ba,
	NVME_SC_ZONE_OFFLINE		= 0x1bb,
	NVME_SC_ZONE_INVALID_WRITE	= 0x1bc,
	NVME_SC_ZONE_TOO_MANY_ACTIVE	= 0x1bd,
	NVME_SC_ZONE_TOO_MANY_OPEN	= 0x1be,
	NVME_SC_ZONE_INVALID_TRANSITION	= 0x1bf,

	/*
	 * Media and Data Integrity Errors:
	 */
	NVME_SC_WRITE_FAULT		= 0x280,
	NVME_SC_READ_ERROR		= 0x281,
	NVME_SC_GUARD_CHECK		= 0x282,
	NVME_SC_APPTAG_CHECK		= 0x283,
	NVME_SC_REFTAG_CHECK		= 0x284,
	NVME_SC_COMPARE_FAILED		= 0x285,
	NVME_SC_ACCESS_DENIED		= 0x286,
	NVME_SC_UNWRITTEN_BLOCK		= 0x287,

	/*
	 * Path-related Errors:
	 */
	NVME_SC_ANA_PERSISTENT_LOSS	= 0x301,
	NVME_SC_ANA_INACCESSIBLE	= 0x302,
	NVME_SC_ANA_TRANSITION		= 0x303,
	NVME_SC_HOST_PATH_ERROR		= 0x370,
	NVME_SC_HOST_ABORTED_CMD	= 0x371,

	NVME_SC_CRD			= 0x1800,
	NVME_SC_DNR			= 0x4000,
पूर्ण;

काष्ठा nvme_completion अणु
	/*
	 * Used by Admin and Fabrics commands to वापस data:
	 */
	जोड़ nvme_result अणु
		__le16	u16;
		__le32	u32;
		__le64	u64;
	पूर्ण result;
	__le16	sq_head;	/* how much of this queue may be reclaimed */
	__le16	sq_id;		/* submission queue that generated this entry */
	__u16	command_id;	/* of the command which completed */
	__le16	status;		/* did the command fail, and अगर so, why? */
पूर्ण;

#घोषणा NVME_VS(major, minor, tertiary) \
	(((major) << 16) | ((minor) << 8) | (tertiary))

#घोषणा NVME_MAJOR(ver)		((ver) >> 16)
#घोषणा NVME_MINOR(ver)		(((ver) >> 8) & 0xff)
#घोषणा NVME_TERTIARY(ver)	((ver) & 0xff)

#पूर्ण_अगर /* _LINUX_NVME_H */
