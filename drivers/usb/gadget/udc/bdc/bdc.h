<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * bdc.h - header क्रम the BRCM BDC USB3.0 device controller
 *
 * Copyright (C) 2014 Broadcom Corporation
 *
 * Author: Ashwini Pahuja
 */

#अगर_अघोषित	__LINUX_BDC_H__
#घोषणा	__LINUX_BDC_H__

#समावेश <linux/kernel.h>
#समावेश <linux/usb.h>
#समावेश <linux/device.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/list.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/mm.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/usb/ch9.h>
#समावेश <linux/usb/gadget.h>
#समावेश <यंत्र/unaligned.h>

#घोषणा BRCM_BDC_NAME "bdc"
#घोषणा BRCM_BDC_DESC "Broadcom USB Device Controller driver"

#घोषणा DMA_ADDR_INVALID        (~(dma_addr_t)0)

/* BDC command operation समयout in usec*/
#घोषणा BDC_CMD_TIMEOUT	1000
/* BDC controller operation समयout in usec*/
#घोषणा BDC_COP_TIMEOUT	500

/*
 * Maximum size of ep0 response buffer क्रम ch9 requests,
 * the set_sel request uses 6 so far, the max.
 */
#घोषणा EP0_RESPONSE_BUFF  6
/* Start with SS as शेष */
#घोषणा EP0_MAX_PKT_SIZE 512

/* 64 entries in a SRR */
#घोषणा NUM_SR_ENTRIES	64

/* Num of bds per table */
#घोषणा NUM_BDS_PER_TABLE	64

/* Num of tables in bd list क्रम control,bulk and Int ep */
#घोषणा NUM_TABLES	2

/* Num of tables in bd list क्रम Isoch ep */
#घोषणा NUM_TABLES_ISOCH	6

/* U1 Timeout शेष: 248usec */
#घोषणा U1_TIMEOUT	0xf8

/* Interrupt coalescence in usec */
#घोषणा	INT_CLS	500

/* Register offsets */
/* Configuration and Capability रेजिस्टरs */
#घोषणा BDC_BDCCFG0	0x00
#घोषणा BDC_BDCCFG1	0x04
#घोषणा BDC_BDCCAP0	0x08
#घोषणा BDC_BDCCAP1	0x0c
#घोषणा BDC_CMDPAR0	0x10
#घोषणा BDC_CMDPAR1	0x14
#घोषणा BDC_CMDPAR2	0x18
#घोषणा BDC_CMDSC	0x1c
#घोषणा BDC_USPC	0x20
#घोषणा BDC_USPPMS	0x28
#घोषणा BDC_USPPM2	0x2c
#घोषणा BDC_SPBBAL	0x38
#घोषणा BDC_SPBBAH	0x3c
#घोषणा BDC_BDCSC	0x40
#घोषणा BDC_XSFNTF	0x4c

#घोषणा BDC_DVCSA	0x50
#घोषणा BDC_DVCSB	0x54
#घोषणा BDC_EPSTS0	0x60
#घोषणा BDC_EPSTS1	0x64
#घोषणा BDC_EPSTS2	0x68
#घोषणा BDC_EPSTS3	0x6c
#घोषणा BDC_EPSTS4	0x70
#घोषणा BDC_EPSTS5	0x74
#घोषणा BDC_EPSTS6	0x78
#घोषणा BDC_EPSTS7	0x7c
#घोषणा BDC_SRRBAL(n)	(0x200 + ((n) * 0x10))
#घोषणा BDC_SRRBAH(n)	(0x204 + ((n) * 0x10))
#घोषणा BDC_SRRINT(n)	(0x208 + ((n) * 0x10))
#घोषणा BDC_INTCTLS(n)	(0x20c + ((n) * 0x10))

/* Extended capability regs */
#घोषणा BDC_FSCNOC	0xcd4
#घोषणा BDC_FSCNIC	0xce4
#घोषणा NUM_NCS(p)	((p) >> 28)

/* Register bit fields and Masks */
/* BDC Configuration 0 */
#घोषणा BDC_PGS(p)	(((p) & (0x7 << 8)) >> 8)
#घोषणा BDC_SPB(p)	((p) & 0x7)

/* BDC Capability1 */
#घोषणा BDC_P64		BIT(0)

/* BDC Command रेजिस्टर */
#घोषणा BDC_CMD_FH	0xe
#घोषणा BDC_CMD_DNC	0x6
#घोषणा BDC_CMD_EPO	0x4
#घोषणा BDC_CMD_BLA	0x3
#घोषणा BDC_CMD_EPC	0x2
#घोषणा BDC_CMD_DVC	0x1
#घोषणा BDC_CMD_CWS		BIT(5)
#घोषणा BDC_CMD_CST(p)		(((p) & (0xf << 6))>>6)
#घोषणा BDC_CMD_EPN(p)		(((p) & 0x1f) << 10)
#घोषणा BDC_SUB_CMD_ADD		(0x1 << 17)
#घोषणा BDC_SUB_CMD_FWK		(0x4 << 17)
/* Reset sequence number */
#घोषणा BDC_CMD_EPO_RST_SN	(0x1 << 16)
#घोषणा BDC_CMD_EP0_XSD		(0x1 << 16)
#घोषणा BDC_SUB_CMD_ADD_EP	(0x1 << 17)
#घोषणा BDC_SUB_CMD_DRP_EP	(0x2 << 17)
#घोषणा BDC_SUB_CMD_EP_STP	(0x2 << 17)
#घोषणा BDC_SUB_CMD_EP_STL	(0x4 << 17)
#घोषणा BDC_SUB_CMD_EP_RST	(0x1 << 17)
#घोषणा BDC_CMD_SRD		BIT(27)

/* CMD completion status */
#घोषणा BDC_CMDS_SUCC	0x1
#घोषणा BDC_CMDS_PARA	0x3
#घोषणा BDC_CMDS_STAT	0x4
#घोषणा BDC_CMDS_FAIL	0x5
#घोषणा BDC_CMDS_INTL	0x6
#घोषणा BDC_CMDS_BUSY	0xf

/* CMDSC Param 2 shअगरts */
#घोषणा EPT_SHIFT	22
#घोषणा MP_SHIFT	10
#घोषणा MB_SHIFT	6
#घोषणा EPM_SHIFT	4

/* BDC USPSC */
#घोषणा BDC_VBC		BIT(31)
#घोषणा BDC_PRC		BIT(30)
#घोषणा BDC_PCE		BIT(29)
#घोषणा BDC_CFC		BIT(28)
#घोषणा BDC_PCC		BIT(27)
#घोषणा BDC_PSC		BIT(26)
#घोषणा BDC_VBS		BIT(25)
#घोषणा BDC_PRS		BIT(24)
#घोषणा BDC_PCS		BIT(23)
#घोषणा BDC_PSP(p)	(((p) & (0x7 << 20))>>20)
#घोषणा BDC_SCN		BIT(8)
#घोषणा BDC_SDC		BIT(7)
#घोषणा BDC_SWS		BIT(4)

#घोषणा BDC_USPSC_RW	(BDC_SCN|BDC_SDC|BDC_SWS|0xf)
#घोषणा BDC_PSP(p)	(((p) & (0x7 << 20))>>20)

#घोषणा BDC_SPEED_FS	0x1
#घोषणा BDC_SPEED_LS	0x2
#घोषणा BDC_SPEED_HS	0x3
#घोषणा BDC_SPEED_SS	0x4

#घोषणा BDC_PST(p)	((p) & 0xf)
#घोषणा BDC_PST_MASK	0xf

/* USPPMS */
#घोषणा BDC_U2E		BIT(31)
#घोषणा BDC_U1E		BIT(30)
#घोषणा BDC_U2A		BIT(29)
#घोषणा BDC_PORT_W1S	BIT(17)
#घोषणा BDC_U1T(p)	((p) & 0xff)
#घोषणा BDC_U2T(p)	(((p) & 0xff) << 8)
#घोषणा BDC_U1T_MASK	0xff

/* USBPM2 */
/* Hardware LPM Enable */
#घोषणा BDC_HLE		BIT(16)

/* BDC Status and Control */
#घोषणा BDC_COP_RST	(1 << 29)
#घोषणा BDC_COP_RUN	(2 << 29)
#घोषणा BDC_COP_STP	(4 << 29)

#घोषणा BDC_COP_MASK (BDC_COP_RST|BDC_COP_RUN|BDC_COP_STP)

#घोषणा BDC_COS		BIT(28)
#घोषणा BDC_CSTS(p)	(((p) & (0x7 << 20)) >> 20)
#घोषणा BDC_MASK_MCW	BIT(7)
#घोषणा BDC_GIE		BIT(1)
#घोषणा BDC_GIP		BIT(0)

#घोषणा BDC_HLT	1
#घोषणा BDC_NOR	2
#घोषणा BDC_OIP	7

/* Buffer descriptor and Status report bit fields and masks */
#घोषणा BD_TYPE_BITMASK	(0xf)
#घोषणा BD_CHAIN	0xf

#घोषणा BD_TFS_SHIFT	4
#घोषणा BD_SOT		BIT(26)
#घोषणा BD_EOT		BIT(27)
#घोषणा BD_ISP		BIT(29)
#घोषणा BD_IOC		BIT(30)
#घोषणा BD_SBF		BIT(31)

#घोषणा BD_INTR_TARGET(p)	(((p) & 0x1f) << 27)

#घोषणा BDC_SRR_RWS		BIT(4)
#घोषणा BDC_SRR_RST		BIT(3)
#घोषणा BDC_SRR_ISR		BIT(2)
#घोषणा BDC_SRR_IE		BIT(1)
#घोषणा BDC_SRR_IP		BIT(0)
#घोषणा BDC_SRR_EPI(p)	(((p) & (0xff << 24)) >> 24)
#घोषणा BDC_SRR_DPI(p) (((p) & (0xff << 16)) >> 16)
#घोषणा BDC_SRR_DPI_MASK	0x00ff0000

#घोषणा MARK_CHAIN_BD	(BD_CHAIN|BD_EOT|BD_SOT)

/* Control transfer BD specअगरic fields */
#घोषणा BD_सूची_IN		BIT(25)

#घोषणा BDC_PTC_MASK	0xf0000000

/* status report defines */
#घोषणा SR_XSF		0
#घोषणा SR_USPC		4
#घोषणा SR_BD_LEN(p)    ((p) & 0xffffff)

#घोषणा XSF_SUCC	0x1
#घोषणा XSF_SHORT	0x3
#घोषणा XSF_BABB	0x4
#घोषणा XSF_SETUP_RECV	0x6
#घोषणा XSF_DATA_START	0x7
#घोषणा XSF_STATUS_START 0x8

#घोषणा XSF_STS(p) (((p) >> 28) & 0xf)

/* Transfer BD fields */
#घोषणा BD_LEN(p) ((p) & 0x1ffff)
#घोषणा BD_LTF		BIT(25)
#घोषणा BD_TYPE_DS	0x1
#घोषणा BD_TYPE_SS	0x2

#घोषणा BDC_EP_ENABLED     BIT(0)
#घोषणा BDC_EP_STALL       BIT(1)
#घोषणा BDC_EP_STOP        BIT(2)

/* One BD can transfer max 65536 bytes */
#घोषणा BD_MAX_BUFF_SIZE	(1 << 16)
/* Maximum bytes in one XFR, Refer to BDC spec */
#घोषणा MAX_XFR_LEN		16777215

/* defines क्रम Force Header command */
#घोषणा DEV_NOTF_TYPE 6
#घोषणा FWK_SUBTYPE  1
#घोषणा TRA_PACKET   4

#घोषणा to_bdc_ep(e)		container_of(e, काष्ठा bdc_ep, usb_ep)
#घोषणा to_bdc_req(r)		container_of(r, काष्ठा bdc_req, usb_req)
#घोषणा gadget_to_bdc(g)	container_of(g, काष्ठा bdc, gadget)

/* FUNCTION WAKE DEV NOTIFICATION पूर्णांकerval, USB3 spec table 8.13 */
#घोषणा BDC_TNOTIFY 2500 /*in ms*/
/* Devstatus bitfields */
#घोषणा REMOTE_WAKEUP_ISSUED	BIT(16)
#घोषणा DEVICE_SUSPENDED	BIT(17)
#घोषणा FUNC_WAKE_ISSUED	BIT(18)
#घोषणा REMOTE_WAKE_ENABLE	(1 << USB_DEVICE_REMOTE_WAKEUP)

/* On disconnect, preserve these bits and clear rest */
#घोषणा DEVSTATUS_CLEAR		(1 << USB_DEVICE_SELF_POWERED)
/* Hardware and software Data काष्ठाures */

/* Endpoपूर्णांक bd: buffer descriptor */
काष्ठा bdc_bd अणु
	__le32 offset[4];
पूर्ण;

/* Status report in Status report ring(srr) */
काष्ठा bdc_sr अणु
	__le32 offset[4];
पूर्ण;

/* bd_table: contiguous bd's in a table */
काष्ठा bd_table अणु
	काष्ठा bdc_bd *start_bd;
	/* dma address of start bd of table*/
	dma_addr_t dma;
पूर्ण;

/*
 * Each endpoपूर्णांक has a bdl(buffer descriptor list), bdl consists of 1 or more bd
 * table's chained to each other through a chain bd, every table has equal
 * number of bds. the software uses bdi(bd index) to refer to particular bd in
 * the list.
 */
काष्ठा bd_list अणु
	/* Array of bd table poपूर्णांकers*/
	काष्ठा bd_table **bd_table_array;
	/* How many tables chained to each other */
	पूर्णांक num_tअसल;
	/* Max_bdi = num_tअसल * num_bds_table - 1 */
	पूर्णांक max_bdi;
	/* current enq bdi from sw poपूर्णांक of view */
	पूर्णांक eqp_bdi;
	/* current deq bdi from sw poपूर्णांक of view */
	पूर्णांक hwd_bdi;
	/* numbers of bds per table */
	पूर्णांक num_bds_table;
पूर्ण;

काष्ठा bdc_req;

/* Representation of a transfer, one transfer can have multiple bd's */
काष्ठा bd_transfer अणु
	काष्ठा bdc_req *req;
	/* start bd index */
	पूर्णांक start_bdi;
	/* this will be the next hw dqp when this transfer completes */
	पूर्णांक next_hwd_bdi;
	/* number of bds in this transfer */
	पूर्णांक num_bds;
पूर्ण;

/*
 * Representation of a gadget request, every gadget request is contained
 * by 1 bd_transfer.
 */
काष्ठा bdc_req अणु
	काष्ठा usb_request	usb_req;
	काष्ठा list_head	queue;
	काष्ठा bdc_ep		*ep;
	/* only one Transfer per request */
	काष्ठा bd_transfer bd_xfr;
	पूर्णांक	epnum;
पूर्ण;

/* scratchpad buffer needed by bdc hardware */
काष्ठा bdc_scratchpad अणु
	dma_addr_t sp_dma;
	व्योम *buff;
	u32 size;
पूर्ण;

/* endpoपूर्णांक representation */
काष्ठा bdc_ep अणु
	काष्ठा usb_ep	usb_ep;
	काष्ठा list_head queue;
	काष्ठा bdc *bdc;
	u8  ep_type;
	u8  dir;
	u8  ep_num;
	स्थिर काष्ठा usb_ss_ep_comp_descriptor	*comp_desc;
	स्थिर काष्ठा usb_endpoपूर्णांक_descriptor	*desc;
	अचिन्हित पूर्णांक flags;
	अक्षर name[20];
	/* endpoपूर्णांक bd list*/
	काष्ठा bd_list bd_list;
	/*
	 * HW generates extra event क्रम multi bd tranfers, this flag helps in
	 * ignoring the extra event
	 */
	bool ignore_next_sr;
पूर्ण;

/* bdc cmmand parameter काष्ठाure */
काष्ठा bdc_cmd_params अणु
	u32	param2;
	u32	param1;
	u32	param0;
पूर्ण;

/* status report ring(srr), currently one srr is supported क्रम entire प्रणाली */
काष्ठा srr अणु
	काष्ठा bdc_sr *sr_bds;
	u16	eqp_index;
	u16	dqp_index;
	dma_addr_t	dma_addr;
पूर्ण;

/* EP0 states */
क्रमागत bdc_ep0_state अणु
	WAIT_FOR_SETUP = 0,
	WAIT_FOR_DATA_START,
	WAIT_FOR_DATA_XMIT,
	WAIT_FOR_STATUS_START,
	WAIT_FOR_STATUS_XMIT,
	STATUS_PENDING
पूर्ण;

/* Link states */
क्रमागत bdc_link_state अणु
	BDC_LINK_STATE_U0	= 0x00,
	BDC_LINK_STATE_U3	= 0x03,
	BDC_LINK_STATE_RX_DET	= 0x05,
	BDC_LINK_STATE_RESUME	= 0x0f
पूर्ण;

/* representation of bdc */
काष्ठा bdc अणु
	काष्ठा usb_gadget	gadget;
	काष्ठा usb_gadget_driver	*gadget_driver;
	काष्ठा device	*dev;
	/* device lock */
	spinlock_t	lock;

	/* generic phy */
	काष्ठा phy      **phys;
	पूर्णांक num_phys;
	/* num of endpoपूर्णांकs क्रम a particular instantiation of IP */
	अचिन्हित पूर्णांक num_eps;
	/*
	 * Array of ep's, it uses the same index covention as bdc hw i.e.
	 * 1 क्रम ep0, 2 क्रम 1out,3 क्रम 1in ....
	 */
	काष्ठा bdc_ep		**bdc_ep_array;
	व्योम __iomem		*regs;
	काष्ठा bdc_scratchpad	scratchpad;
	u32	sp_buff_size;
	/* current driver supports 1 status ring */
	काष्ठा srr	srr;
	/* Last received setup packet */
	काष्ठा	usb_ctrlrequest setup_pkt;
	काष्ठा	bdc_req ep0_req;
	काष्ठा	bdc_req status_req;
	क्रमागत	bdc_ep0_state ep0_state;
	bool	delayed_status;
	bool	zlp_needed;
	bool	reinit;
	bool	pullup;
	/* Bits 0-15 are standard and 16-31 क्रम proprietary inक्रमmation */
	u32	devstatus;
	पूर्णांक	irq;
	व्योम	*mem;
	u32	dev_addr;
	/* DMA pools */
	काष्ठा dma_pool	*bd_table_pool;
	u8		test_mode;
	/* array of callbacks क्रम various status report handlers */
	व्योम (*sr_handler[2])(काष्ठा bdc *, काष्ठा bdc_sr *);
	/* ep0 callback handlers */
	व्योम (*sr_xsf_ep0[3])(काष्ठा bdc *, काष्ठा bdc_sr *);
	/* ep0 response buffer क्रम ch9 requests like GET_STATUS and SET_SEL */
	अचिन्हित अक्षर		ep0_response_buff[EP0_RESPONSE_BUFF];
	/*
	 * Timer to check अगर host resumed transfer after bdc sent Func wake
	 * notअगरication  packet after a remote wakeup. अगर not, then resend the
	 * Func Wake packet every 2.5 secs. Refer to USB3 spec section 8.5.6.4
	 */
	काष्ठा delayed_work	func_wake_notअगरy;
	काष्ठा clk		*clk;
पूर्ण;

अटल अंतरभूत u32 bdc_पढ़ोl(व्योम __iomem *base, u32 offset)
अणु
	वापस पढ़ोl(base + offset);
पूर्ण

अटल अंतरभूत व्योम bdc_ग_लिखोl(व्योम __iomem *base, u32 offset, u32 value)
अणु
	ग_लिखोl(value, base + offset);
पूर्ण

/* Buffer descriptor list operations */
व्योम bdc_notअगरy_xfr(काष्ठा bdc *bdc, u32 epnum);
व्योम bdc_softconn(काष्ठा bdc *bdc);
व्योम bdc_softdisconn(काष्ठा bdc *bdc);
पूर्णांक bdc_run(काष्ठा bdc *bdc);
पूर्णांक bdc_stop(काष्ठा bdc *bdc);
पूर्णांक bdc_reset(काष्ठा bdc *bdc);
पूर्णांक bdc_udc_init(काष्ठा bdc *bdc);
व्योम bdc_udc_निकास(काष्ठा bdc *bdc);
पूर्णांक bdc_reinit(काष्ठा bdc *bdc);

/* Status report handlers */
/* Upstream port status change sr */
व्योम bdc_sr_uspc(काष्ठा bdc *bdc, काष्ठा bdc_sr *sreport);
/* transfer sr */
व्योम bdc_sr_xsf(काष्ठा bdc *bdc, काष्ठा bdc_sr *sreport);
/* EP0 XSF handlers */
व्योम bdc_xsf_ep0_setup_recv(काष्ठा bdc *bdc, काष्ठा bdc_sr *sreport);
व्योम bdc_xsf_ep0_data_start(काष्ठा bdc *bdc, काष्ठा bdc_sr *sreport);
व्योम bdc_xsf_ep0_status_start(काष्ठा bdc *bdc, काष्ठा bdc_sr *sreport);

#पूर्ण_अगर /* __LINUX_BDC_H__ */
