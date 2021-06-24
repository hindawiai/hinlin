<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_S390_PCI_CLP_H
#घोषणा _ASM_S390_PCI_CLP_H

#समावेश <यंत्र/clp.h>

/*
 * Call Logical Processor - Command Codes
 */
#घोषणा CLP_SLPC		0x0001
#घोषणा CLP_LIST_PCI		0x0002
#घोषणा CLP_QUERY_PCI_FN	0x0003
#घोषणा CLP_QUERY_PCI_FNGRP	0x0004
#घोषणा CLP_SET_PCI_FN		0x0005

/* PCI function handle list entry */
काष्ठा clp_fh_list_entry अणु
	u16 device_id;
	u16 venकरोr_id;
	u32 config_state :  1;
	u32		 : 31;
	u32 fid;		/* PCI function id */
	u32 fh;			/* PCI function handle */
पूर्ण __packed;

#घोषणा CLP_RC_SETPCIFN_FH	0x0101	/* Invalid PCI fn handle */
#घोषणा CLP_RC_SETPCIFN_FHOP	0x0102	/* Fn handle not valid क्रम op */
#घोषणा CLP_RC_SETPCIFN_DMAAS	0x0103	/* Invalid DMA addr space */
#घोषणा CLP_RC_SETPCIFN_RES	0x0104	/* Insufficient resources */
#घोषणा CLP_RC_SETPCIFN_ALRDY	0x0105	/* Fn alपढ़ोy in requested state */
#घोषणा CLP_RC_SETPCIFN_ERR	0x0106	/* Fn in permanent error state */
#घोषणा CLP_RC_SETPCIFN_RECPND	0x0107	/* Error recovery pending */
#घोषणा CLP_RC_SETPCIFN_BUSY	0x0108	/* Fn busy */
#घोषणा CLP_RC_LISTPCI_BADRT	0x010a	/* Resume token not recognized */
#घोषणा CLP_RC_QUERYPCIFG_PFGID	0x010b	/* Unrecognized PFGID */

/* request or response block header length */
#घोषणा LIST_PCI_HDR_LEN	32

/* Number of function handles fitting in response block */
#घोषणा CLP_FH_LIST_NR_ENTRIES				\
	((CLP_BLK_SIZE - 2 * LIST_PCI_HDR_LEN)		\
		/ माप(काष्ठा clp_fh_list_entry))

#घोषणा CLP_SET_ENABLE_PCI_FN	0	/* Yes, 0 enables it */
#घोषणा CLP_SET_DISABLE_PCI_FN	1	/* Yes, 1 disables it */
#घोषणा CLP_SET_ENABLE_MIO	2
#घोषणा CLP_SET_DISABLE_MIO	3

#घोषणा CLP_UTIL_STR_LEN	64
#घोषणा CLP_PFIP_NR_SEGMENTS	4

बाह्य bool zpci_unique_uid;

काष्ठा clp_rsp_slpc_pci अणु
	काष्ठा clp_rsp_hdr hdr;
	u32 reserved2[4];
	u32 lpअगर[8];
	u32 reserved3[4];
	u32 vwb		:  1;
	u32		:  1;
	u32 mio_wb	:  6;
	u32		: 24;
	u32 reserved5[3];
	u32 lpic[8];
पूर्ण __packed;

/* List PCI functions request */
काष्ठा clp_req_list_pci अणु
	काष्ठा clp_req_hdr hdr;
	u64 resume_token;
	u64 reserved2;
पूर्ण __packed;

/* List PCI functions response */
काष्ठा clp_rsp_list_pci अणु
	काष्ठा clp_rsp_hdr hdr;
	u64 resume_token;
	u32 reserved2;
	u16 max_fn;
	u8			: 7;
	u8 uid_checking		: 1;
	u8 entry_size;
	काष्ठा clp_fh_list_entry fh_list[CLP_FH_LIST_NR_ENTRIES];
पूर्ण __packed;

काष्ठा mio_info अणु
	u32 valid : 6;
	u32 : 26;
	u32 : 32;
	काष्ठा अणु
		u64 wb;
		u64 wt;
	पूर्ण addr[PCI_STD_NUM_BARS];
	u32 reserved[6];
पूर्ण __packed;

/* Query PCI function request */
काष्ठा clp_req_query_pci अणु
	काष्ठा clp_req_hdr hdr;
	u32 fh;				/* function handle */
	u32 reserved2;
	u64 reserved3;
पूर्ण __packed;

/* Query PCI function response */
काष्ठा clp_rsp_query_pci अणु
	काष्ठा clp_rsp_hdr hdr;
	u16 vfn;			/* भव fn number */
	u16			:  3;
	u16 rid_avail		:  1;
	u16 is_physfn		:  1;
	u16 reserved1		:  1;
	u16 mio_addr_avail	:  1;
	u16 util_str_avail	:  1;	/* utility string available? */
	u16 pfgid		:  8;	/* pci function group id */
	u32 fid;			/* pci function id */
	u8 bar_size[PCI_STD_NUM_BARS];
	u16 pchid;
	__le32 bar[PCI_STD_NUM_BARS];
	u8 pfip[CLP_PFIP_NR_SEGMENTS];	/* pci function पूर्णांकernal path */
	u16			: 12;
	u16 port		:  4;
	u8 fmb_len;
	u8 pft;				/* pci function type */
	u64 sdma;			/* start dma as */
	u64 edma;			/* end dma as */
#घोषणा ZPCI_RID_MASK_DEVFN 0x00ff
	u16 rid;			/* BUS/DEVFN PCI address */
	u16 reserved0;
	u32 reserved[10];
	u32 uid;			/* user defined id */
	u8 util_str[CLP_UTIL_STR_LEN];	/* utility string */
	u32 reserved2[16];
	काष्ठा mio_info mio;
पूर्ण __packed;

/* Query PCI function group request */
काष्ठा clp_req_query_pci_grp अणु
	काष्ठा clp_req_hdr hdr;
	u32 reserved2		: 24;
	u32 pfgid		:  8;	/* function group id */
	u32 reserved3;
	u64 reserved4;
पूर्ण __packed;

/* Query PCI function group response */
काष्ठा clp_rsp_query_pci_grp अणु
	काष्ठा clp_rsp_hdr hdr;
	u16			:  4;
	u16 noi			: 12;	/* number of पूर्णांकerrupts */
	u8 version;
	u8			:  6;
	u8 frame		:  1;
	u8 refresh		:  1;	/* TLB refresh mode */
	u16 reserved2;
	u16 mui;
	u16			: 16;
	u16 maxfaal;
	u16			:  4;
	u16 dnoi		: 12;
	u16 maxcpu;
	u64 dयंत्र;			/* dma address space mask */
	u64 msia;			/* MSI address */
	u64 reserved4;
	u64 reserved5;
पूर्ण __packed;

/* Set PCI function request */
काष्ठा clp_req_set_pci अणु
	काष्ठा clp_req_hdr hdr;
	u32 fh;				/* function handle */
	u16 reserved2;
	u8 oc;				/* operation controls */
	u8 ndas;			/* number of dma spaces */
	u64 reserved3;
पूर्ण __packed;

/* Set PCI function response */
काष्ठा clp_rsp_set_pci अणु
	काष्ठा clp_rsp_hdr hdr;
	u32 fh;				/* function handle */
	u32 reserved1;
	u64 reserved2;
	काष्ठा mio_info mio;
पूर्ण __packed;

/* Combined request/response block काष्ठाures used by clp insn */
काष्ठा clp_req_rsp_slpc_pci अणु
	काष्ठा clp_req_slpc request;
	काष्ठा clp_rsp_slpc_pci response;
पूर्ण __packed;

काष्ठा clp_req_rsp_list_pci अणु
	काष्ठा clp_req_list_pci request;
	काष्ठा clp_rsp_list_pci response;
पूर्ण __packed;

काष्ठा clp_req_rsp_set_pci अणु
	काष्ठा clp_req_set_pci request;
	काष्ठा clp_rsp_set_pci response;
पूर्ण __packed;

काष्ठा clp_req_rsp_query_pci अणु
	काष्ठा clp_req_query_pci request;
	काष्ठा clp_rsp_query_pci response;
पूर्ण __packed;

काष्ठा clp_req_rsp_query_pci_grp अणु
	काष्ठा clp_req_query_pci_grp request;
	काष्ठा clp_rsp_query_pci_grp response;
पूर्ण __packed;

#पूर्ण_अगर
