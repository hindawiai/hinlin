<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/**
 * xhci-dbgcap.h - xHCI debug capability support
 *
 * Copyright (C) 2017 Intel Corporation
 *
 * Author: Lu Baolu <baolu.lu@linux.पूर्णांकel.com>
 */
#अगर_अघोषित __LINUX_XHCI_DBGCAP_H
#घोषणा __LINUX_XHCI_DBGCAP_H

#समावेश <linux/tty.h>
#समावेश <linux/kfअगरo.h>

काष्ठा dbc_regs अणु
	__le32	capability;
	__le32	करोorbell;
	__le32	ersts;		/* Event Ring Segment Table Size*/
	__le32	__reserved_0;	/* 0c~0f reserved bits */
	__le64	erstba;		/* Event Ring Segment Table Base Address */
	__le64	erdp;		/* Event Ring Dequeue Poपूर्णांकer */
	__le32	control;
	__le32	status;
	__le32	portsc;		/* Port status and control */
	__le32	__reserved_1;	/* 2b~28 reserved bits */
	__le64	dccp;		/* Debug Capability Context Poपूर्णांकer */
	__le32	devinfo1;	/* Device Descriptor Info Register 1 */
	__le32	devinfo2;	/* Device Descriptor Info Register 2 */
पूर्ण;

काष्ठा dbc_info_context अणु
	__le64	string0;
	__le64	manufacturer;
	__le64	product;
	__le64	serial;
	__le32	length;
	__le32	__reserved_0[7];
पूर्ण;

#घोषणा DBC_CTRL_DBC_RUN		BIT(0)
#घोषणा DBC_CTRL_PORT_ENABLE		BIT(1)
#घोषणा DBC_CTRL_HALT_OUT_TR		BIT(2)
#घोषणा DBC_CTRL_HALT_IN_TR		BIT(3)
#घोषणा DBC_CTRL_DBC_RUN_CHANGE		BIT(4)
#घोषणा DBC_CTRL_DBC_ENABLE		BIT(31)
#घोषणा DBC_CTRL_MAXBURST(p)		(((p) >> 16) & 0xff)
#घोषणा DBC_DOOR_BELL_TARGET(p)		(((p) & 0xff) << 8)

#घोषणा DBC_MAX_PACKET			1024
#घोषणा DBC_MAX_STRING_LENGTH		64
#घोषणा DBC_STRING_MANUFACTURER		"Linux Foundation"
#घोषणा DBC_STRING_PRODUCT		"Linux USB Debug Target"
#घोषणा DBC_STRING_SERIAL		"0001"
#घोषणा	DBC_CONTEXT_SIZE		64

/*
 * Port status:
 */
#घोषणा DBC_PORTSC_CONN_STATUS		BIT(0)
#घोषणा DBC_PORTSC_PORT_ENABLED		BIT(1)
#घोषणा DBC_PORTSC_CONN_CHANGE		BIT(17)
#घोषणा DBC_PORTSC_RESET_CHANGE		BIT(21)
#घोषणा DBC_PORTSC_LINK_CHANGE		BIT(22)
#घोषणा DBC_PORTSC_CONFIG_CHANGE	BIT(23)

काष्ठा dbc_str_descs अणु
	अक्षर	string0[DBC_MAX_STRING_LENGTH];
	अक्षर	manufacturer[DBC_MAX_STRING_LENGTH];
	अक्षर	product[DBC_MAX_STRING_LENGTH];
	अक्षर	serial[DBC_MAX_STRING_LENGTH];
पूर्ण;

#घोषणा DBC_PROTOCOL			1	/* GNU Remote Debug Command */
#घोषणा DBC_VENDOR_ID			0x1d6b	/* Linux Foundation 0x1d6b */
#घोषणा DBC_PRODUCT_ID			0x0010	/* device 0010 */
#घोषणा DBC_DEVICE_REV			0x0010	/* 0.10 */

क्रमागत dbc_state अणु
	DS_DISABLED = 0,
	DS_INITIALIZED,
	DS_ENABLED,
	DS_CONNECTED,
	DS_CONFIGURED,
	DS_STALLED,
पूर्ण;

काष्ठा dbc_ep अणु
	काष्ठा xhci_dbc			*dbc;
	काष्ठा list_head		list_pending;
	काष्ठा xhci_ring		*ring;
	अचिन्हित पूर्णांक			direction:1;
पूर्ण;

#घोषणा DBC_QUEUE_SIZE			16
#घोषणा DBC_WRITE_BUF_SIZE		8192

/*
 * Private काष्ठाure क्रम DbC hardware state:
 */
काष्ठा dbc_port अणु
	काष्ठा tty_port			port;
	spinlock_t			port_lock;	/* port access */

	काष्ठा list_head		पढ़ो_pool;
	काष्ठा list_head		पढ़ो_queue;
	अचिन्हित पूर्णांक			n_पढ़ो;
	काष्ठा tasklet_काष्ठा		push;

	काष्ठा list_head		ग_लिखो_pool;
	काष्ठा kfअगरo			ग_लिखो_fअगरo;

	bool				रेजिस्टरed;
पूर्ण;

काष्ठा dbc_driver अणु
	पूर्णांक (*configure)(काष्ठा xhci_dbc *dbc);
	व्योम (*disconnect)(काष्ठा xhci_dbc *dbc);
पूर्ण;

काष्ठा xhci_dbc अणु
	spinlock_t			lock;		/* device access */
	काष्ठा device			*dev;
	काष्ठा xhci_hcd			*xhci;
	काष्ठा dbc_regs __iomem		*regs;
	काष्ठा xhci_ring		*ring_evt;
	काष्ठा xhci_ring		*ring_in;
	काष्ठा xhci_ring		*ring_out;
	काष्ठा xhci_erst		erst;
	काष्ठा xhci_container_ctx	*ctx;

	काष्ठा dbc_str_descs		*string;
	dma_addr_t			string_dma;
	माप_प्रकार				string_size;

	क्रमागत dbc_state			state;
	काष्ठा delayed_work		event_work;
	अचिन्हित			resume_required:1;
	काष्ठा dbc_ep			eps[2];

	स्थिर काष्ठा dbc_driver		*driver;
	व्योम				*priv;
पूर्ण;

काष्ठा dbc_request अणु
	व्योम				*buf;
	अचिन्हित पूर्णांक			length;
	dma_addr_t			dma;
	व्योम				(*complete)(काष्ठा xhci_dbc *dbc,
						    काष्ठा dbc_request *req);
	काष्ठा list_head		list_pool;
	पूर्णांक				status;
	अचिन्हित पूर्णांक			actual;

	काष्ठा xhci_dbc			*dbc;
	काष्ठा list_head		list_pending;
	dma_addr_t			trb_dma;
	जोड़ xhci_trb			*trb;
	अचिन्हित			direction:1;
पूर्ण;

#घोषणा dbc_bulkout_ctx(d)		\
	((काष्ठा xhci_ep_ctx *)((d)->ctx->bytes + DBC_CONTEXT_SIZE))
#घोषणा dbc_bulkin_ctx(d)		\
	((काष्ठा xhci_ep_ctx *)((d)->ctx->bytes + DBC_CONTEXT_SIZE * 2))
#घोषणा dbc_bulkout_enq(d)		\
	xhci_trb_virt_to_dma((d)->ring_out->enq_seg, (d)->ring_out->enqueue)
#घोषणा dbc_bulkin_enq(d)		\
	xhci_trb_virt_to_dma((d)->ring_in->enq_seg, (d)->ring_in->enqueue)
#घोषणा dbc_epctx_info2(t, p, b)	\
	cpu_to_le32(EP_TYPE(t) | MAX_PACKET(p) | MAX_BURST(b))
#घोषणा dbc_ep_dma_direction(d)		\
	((d)->direction ? DMA_FROM_DEVICE : DMA_TO_DEVICE)

#घोषणा BULK_OUT			0
#घोषणा BULK_IN				1
#घोषणा EPID_OUT			2
#घोषणा EPID_IN				3

क्रमागत evtवापस अणु
	EVT_ERR	= -1,
	EVT_DONE,
	EVT_GSER,
	EVT_DISC,
पूर्ण;

अटल अंतरभूत काष्ठा dbc_ep *get_in_ep(काष्ठा xhci_dbc *dbc)
अणु
	वापस &dbc->eps[BULK_IN];
पूर्ण

अटल अंतरभूत काष्ठा dbc_ep *get_out_ep(काष्ठा xhci_dbc *dbc)
अणु
	वापस &dbc->eps[BULK_OUT];
पूर्ण

#अगर_घोषित CONFIG_USB_XHCI_DBGCAP
पूर्णांक xhci_dbc_init(काष्ठा xhci_hcd *xhci);
व्योम xhci_dbc_निकास(काष्ठा xhci_hcd *xhci);
पूर्णांक xhci_dbc_tty_probe(काष्ठा xhci_hcd *xhci);
व्योम xhci_dbc_tty_हटाओ(काष्ठा xhci_dbc *dbc);
काष्ठा dbc_request *dbc_alloc_request(काष्ठा xhci_dbc *dbc,
				      अचिन्हित पूर्णांक direction,
				      gfp_t flags);
व्योम dbc_मुक्त_request(काष्ठा dbc_request *req);
पूर्णांक dbc_ep_queue(काष्ठा dbc_request *req);
#अगर_घोषित CONFIG_PM
पूर्णांक xhci_dbc_suspend(काष्ठा xhci_hcd *xhci);
पूर्णांक xhci_dbc_resume(काष्ठा xhci_hcd *xhci);
#पूर्ण_अगर /* CONFIG_PM */
#अन्यथा
अटल अंतरभूत पूर्णांक xhci_dbc_init(काष्ठा xhci_hcd *xhci)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम xhci_dbc_निकास(काष्ठा xhci_hcd *xhci)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक xhci_dbc_suspend(काष्ठा xhci_hcd *xhci)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक xhci_dbc_resume(काष्ठा xhci_hcd *xhci)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_USB_XHCI_DBGCAP */
#पूर्ण_अगर /* __LINUX_XHCI_DBGCAP_H */
