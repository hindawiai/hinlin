<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * xhci-dbc.h - xHCI debug capability early driver
 *
 * Copyright (C) 2016 Intel Corporation
 *
 * Author: Lu Baolu <baolu.lu@linux.पूर्णांकel.com>
 */

#अगर_अघोषित __LINUX_XHCI_DBC_H
#घोषणा __LINUX_XHCI_DBC_H

#समावेश <linux/types.h>
#समावेश <linux/usb/ch9.h>

/*
 * xHCI Debug Capability Register पूर्णांकerfaces:
 */
काष्ठा xdbc_regs अणु
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

#घोषणा DEBUG_MAX_BURST(p)	(((p) >> 16) & 0xff)

#घोषणा CTRL_DBC_RUN		BIT(0)
#घोषणा CTRL_PORT_ENABLE	BIT(1)
#घोषणा CTRL_HALT_OUT_TR	BIT(2)
#घोषणा CTRL_HALT_IN_TR		BIT(3)
#घोषणा CTRL_DBC_RUN_CHANGE	BIT(4)
#घोषणा CTRL_DBC_ENABLE		BIT(31)

#घोषणा DCST_DEBUG_PORT(p)	(((p) >> 24) & 0xff)

#घोषणा PORTSC_CONN_STATUS	BIT(0)
#घोषणा PORTSC_CONN_CHANGE	BIT(17)
#घोषणा PORTSC_RESET_CHANGE	BIT(21)
#घोषणा PORTSC_LINK_CHANGE	BIT(22)
#घोषणा PORTSC_CONFIG_CHANGE	BIT(23)

/*
 * xHCI Debug Capability data काष्ठाures:
 */
काष्ठा xdbc_trb अणु
	__le32 field[4];
पूर्ण;

काष्ठा xdbc_erst_entry अणु
	__le64	seg_addr;
	__le32	seg_size;
	__le32	__reserved_0;
पूर्ण;

काष्ठा xdbc_info_context अणु
	__le64	string0;
	__le64	manufacturer;
	__le64	product;
	__le64	serial;
	__le32	length;
	__le32	__reserved_0[7];
पूर्ण;

काष्ठा xdbc_ep_context अणु
	__le32	ep_info1;
	__le32	ep_info2;
	__le64	deq;
	__le32	tx_info;
	__le32	__reserved_0[11];
पूर्ण;

काष्ठा xdbc_context अणु
	काष्ठा xdbc_info_context	info;
	काष्ठा xdbc_ep_context		out;
	काष्ठा xdbc_ep_context		in;
पूर्ण;

#घोषणा XDBC_INFO_CONTEXT_SIZE		48
#घोषणा XDBC_MAX_STRING_LENGTH		64
#घोषणा XDBC_STRING_MANUFACTURER	"Linux Foundation"
#घोषणा XDBC_STRING_PRODUCT		"Linux USB GDB Target"
#घोषणा XDBC_STRING_SERIAL		"0001"

काष्ठा xdbc_strings अणु
	अक्षर	string0[XDBC_MAX_STRING_LENGTH];
	अक्षर	manufacturer[XDBC_MAX_STRING_LENGTH];
	अक्षर	product[XDBC_MAX_STRING_LENGTH];
	अक्षर	serial[XDBC_MAX_STRING_LENGTH];
पूर्ण;

#घोषणा XDBC_PROTOCOL		1	/* GNU Remote Debug Command Set */
#घोषणा XDBC_VENDOR_ID		0x1d6b	/* Linux Foundation 0x1d6b */
#घोषणा XDBC_PRODUCT_ID		0x0011	/* __le16 idProduct; device 0011 */
#घोषणा XDBC_DEVICE_REV		0x0010	/* 0.10 */

/*
 * xHCI Debug Capability software state काष्ठाures:
 */
काष्ठा xdbc_segment अणु
	काष्ठा xdbc_trb		*trbs;
	dma_addr_t		dma;
पूर्ण;

#घोषणा XDBC_TRBS_PER_SEGMENT	256

काष्ठा xdbc_ring अणु
	काष्ठा xdbc_segment	*segment;
	काष्ठा xdbc_trb		*enqueue;
	काष्ठा xdbc_trb		*dequeue;
	u32			cycle_state;
पूर्ण;

/*
 * These are the "Endpoint ID" (also known as "Context Index") values क्रम the
 * OUT Transfer Ring and the IN Transfer Ring of a Debug Capability Context data
 * काष्ठाure.
 * According to the "eXtensible Host Controller Interface क्रम Universal Serial
 * Bus (xHCI)" specification, section "7.6.3.2 Endpoपूर्णांक Contexts and Transfer
 * Rings", these should be 0 and 1, and those are the values AMD machines give
 * you; but Intel machines seem to use the क्रमmula from section "4.5.1 Device
 * Context Index", which is supposed to be used क्रम the Device Context only.
 * Luckily the values from Intel करोn't overlap with those from AMD, so we can
 * just test क्रम both.
 */
#घोषणा XDBC_EPID_OUT		0
#घोषणा XDBC_EPID_IN		1
#घोषणा XDBC_EPID_OUT_INTEL	2
#घोषणा XDBC_EPID_IN_INTEL	3

काष्ठा xdbc_state अणु
	u16			venकरोr;
	u16			device;
	u32			bus;
	u32			dev;
	u32			func;
	व्योम __iomem		*xhci_base;
	u64			xhci_start;
	माप_प्रकार			xhci_length;
	पूर्णांक			port_number;

	/* DbC रेजिस्टर base */
	काष्ठा xdbc_regs __iomem *xdbc_reg;

	/* DbC table page */
	dma_addr_t		table_dma;
	व्योम			*table_base;

	/* event ring segment table */
	dma_addr_t		erst_dma;
	माप_प्रकार			erst_size;
	व्योम			*erst_base;

	/* event ring segments */
	काष्ठा xdbc_ring	evt_ring;
	काष्ठा xdbc_segment	evt_seg;

	/* debug capability contexts */
	dma_addr_t		dbcc_dma;
	माप_प्रकार			dbcc_size;
	व्योम			*dbcc_base;

	/* descriptor strings */
	dma_addr_t		string_dma;
	माप_प्रकार			string_size;
	व्योम			*string_base;

	/* bulk OUT endpoपूर्णांक */
	काष्ठा xdbc_ring	out_ring;
	काष्ठा xdbc_segment	out_seg;
	व्योम			*out_buf;
	dma_addr_t		out_dma;

	/* bulk IN endpoपूर्णांक */
	काष्ठा xdbc_ring	in_ring;
	काष्ठा xdbc_segment	in_seg;
	व्योम			*in_buf;
	dma_addr_t		in_dma;

	u32			flags;

	/* spinlock क्रम early_xdbc_ग_लिखो() reentrancy */
	raw_spinlock_t		lock;
पूर्ण;

#घोषणा XDBC_PCI_MAX_BUSES	256
#घोषणा XDBC_PCI_MAX_DEVICES	32
#घोषणा XDBC_PCI_MAX_FUNCTION	8

#घोषणा XDBC_TABLE_ENTRY_SIZE	64
#घोषणा XDBC_ERST_ENTRY_NUM	1
#घोषणा XDBC_DBCC_ENTRY_NUM	3
#घोषणा XDBC_STRING_ENTRY_NUM	4

/* Bits definitions क्रम xdbc_state.flags: */
#घोषणा XDBC_FLAGS_INITIALIZED	BIT(0)
#घोषणा XDBC_FLAGS_IN_STALL	BIT(1)
#घोषणा XDBC_FLAGS_OUT_STALL	BIT(2)
#घोषणा XDBC_FLAGS_IN_PROCESS	BIT(3)
#घोषणा XDBC_FLAGS_OUT_PROCESS	BIT(4)
#घोषणा XDBC_FLAGS_CONFIGURED	BIT(5)

#घोषणा XDBC_MAX_PACKET		1024

/* Door bell target: */
#घोषणा OUT_EP_DOORBELL		0
#घोषणा IN_EP_DOORBELL		1
#घोषणा DOOR_BELL_TARGET(p)	(((p) & 0xff) << 8)

#घोषणा xdbc_पढ़ो64(regs)	xhci_पढ़ो_64(शून्य, (regs))
#घोषणा xdbc_ग_लिखो64(val, regs)	xhci_ग_लिखो_64(शून्य, (val), (regs))

#पूर्ण_अगर /* __LINUX_XHCI_DBC_H */
