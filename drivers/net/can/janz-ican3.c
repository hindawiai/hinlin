<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Janz MODULbus VMOD-ICAN3 CAN Interface Driver
 *
 * Copyright (c) 2010 Ira W. Snyder <iws@ovro.caltech.edu>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <linux/netdevice.h>
#समावेश <linux/can.h>
#समावेश <linux/can/dev.h>
#समावेश <linux/can/skb.h>
#समावेश <linux/can/error.h>

#समावेश <linux/mfd/janz.h>
#समावेश <यंत्र/पन.स>

/* the DPM has 64k of memory, organized पूर्णांकo 256x 256 byte pages */
#घोषणा DPM_NUM_PAGES		256
#घोषणा DPM_PAGE_SIZE		256
#घोषणा DPM_PAGE_ADDR(p)	((p) * DPM_PAGE_SIZE)

/* JANZ ICAN3 "old-style" host पूर्णांकerface queue page numbers */
#घोषणा QUEUE_OLD_CONTROL	0
#घोषणा QUEUE_OLD_RB0		1
#घोषणा QUEUE_OLD_RB1		2
#घोषणा QUEUE_OLD_WB0		3
#घोषणा QUEUE_OLD_WB1		4

/* Janz ICAN3 "old-style" host पूर्णांकerface control रेजिस्टरs */
#घोषणा MSYNC_PEER		0x00		/* ICAN only */
#घोषणा MSYNC_LOCL		0x01		/* host only */
#घोषणा TARGET_RUNNING		0x02
#घोषणा FIRMWARE_STAMP		0x60		/* big endian firmware stamp */

#घोषणा MSYNC_RB0		0x01
#घोषणा MSYNC_RB1		0x02
#घोषणा MSYNC_RBLW		0x04
#घोषणा MSYNC_RB_MASK		(MSYNC_RB0 | MSYNC_RB1)

#घोषणा MSYNC_WB0		0x10
#घोषणा MSYNC_WB1		0x20
#घोषणा MSYNC_WBLW		0x40
#घोषणा MSYNC_WB_MASK		(MSYNC_WB0 | MSYNC_WB1)

/* Janz ICAN3 "new-style" host पूर्णांकerface queue page numbers */
#घोषणा QUEUE_TOHOST		5
#घोषणा QUEUE_FROMHOST_MID	6
#घोषणा QUEUE_FROMHOST_HIGH	7
#घोषणा QUEUE_FROMHOST_LOW	8

/* The first मुक्त page in the DPM is #9 */
#घोषणा DPM_FREE_START		9

/* Janz ICAN3 "new-style" and "fast" host पूर्णांकerface descriptor flags */
#घोषणा DESC_VALID		0x80
#घोषणा DESC_WRAP		0x40
#घोषणा DESC_INTERRUPT		0x20
#घोषणा DESC_IVALID		0x10
#घोषणा DESC_LEN(len)		(len)

/* Janz ICAN3 Firmware Messages */
#घोषणा MSG_CONNECTI		0x02
#घोषणा MSG_DISCONNECT		0x03
#घोषणा MSG_IDVERS		0x04
#घोषणा MSG_MSGLOST		0x05
#घोषणा MSG_NEWHOSTIF		0x08
#घोषणा MSG_INQUIRY		0x0a
#घोषणा MSG_SETAFILMASK		0x10
#घोषणा MSG_INITFDPMQUEUE	0x11
#घोषणा MSG_HWCONF		0x12
#घोषणा MSG_FMSGLOST		0x15
#घोषणा MSG_CEVTIND		0x37
#घोषणा MSG_CBTRREQ		0x41
#घोषणा MSG_COFFREQ		0x42
#घोषणा MSG_CONREQ		0x43
#घोषणा MSG_CCONFREQ		0x47
#घोषणा MSG_NMTS		0xb0
#घोषणा MSG_LMTS		0xb4

/*
 * Janz ICAN3 CAN Inquiry Message Types
 *
 * NOTE: there appears to be a firmware bug here. You must send
 * NOTE: INQUIRY_STATUS and expect to receive an INQUIRY_EXTENDED
 * NOTE: response. The controller never responds to a message with
 * NOTE: the INQUIRY_EXTENDED subspec :(
 */
#घोषणा INQUIRY_STATUS		0x00
#घोषणा INQUIRY_TERMINATION	0x01
#घोषणा INQUIRY_EXTENDED	0x04

/* Janz ICAN3 CAN Set Acceptance Filter Mask Message Types */
#घोषणा SETAFILMASK_REJECT	0x00
#घोषणा SETAFILMASK_FASTIF	0x02

/* Janz ICAN3 CAN Hardware Configuration Message Types */
#घोषणा HWCONF_TERMINATE_ON	0x01
#घोषणा HWCONF_TERMINATE_OFF	0x00

/* Janz ICAN3 CAN Event Indication Message Types */
#घोषणा CEVTIND_EI		0x01
#घोषणा CEVTIND_DOI		0x02
#घोषणा CEVTIND_LOST		0x04
#घोषणा CEVTIND_FULL		0x08
#घोषणा CEVTIND_BEI		0x10

#घोषणा CEVTIND_CHIP_SJA1000	0x02

#घोषणा ICAN3_BUSERR_QUOTA_MAX	255

/* Janz ICAN3 CAN Frame Conversion */
#घोषणा ICAN3_SNGL	0x02
#घोषणा ICAN3_ECHO	0x10
#घोषणा ICAN3_EFF_RTR	0x40
#घोषणा ICAN3_SFF_RTR	0x10
#घोषणा ICAN3_EFF	0x80

#घोषणा ICAN3_CAN_TYPE_MASK	0x0f
#घोषणा ICAN3_CAN_TYPE_SFF	0x00
#घोषणा ICAN3_CAN_TYPE_EFF	0x01

#घोषणा ICAN3_CAN_DLC_MASK	0x0f

/* Janz ICAN3 NMTS subtypes */
#घोषणा NMTS_CREATE_NODE_REQ	0x0
#घोषणा NMTS_SLAVE_STATE_IND	0x8
#घोषणा NMTS_SLAVE_EVENT_IND	0x9

/* Janz ICAN3 LMTS subtypes */
#घोषणा LMTS_BUSON_REQ		0x0
#घोषणा LMTS_BUSOFF_REQ		0x1
#घोषणा LMTS_CAN_CONF_REQ	0x2

/* Janz ICAN3 NMTS Event indications */
#घोषणा NE_LOCAL_OCCURRED	0x3
#घोषणा NE_LOCAL_RESOLVED	0x2
#घोषणा NE_REMOTE_OCCURRED	0xc
#घोषणा NE_REMOTE_RESOLVED	0x8

/*
 * SJA1000 Status and Error Register Definitions
 *
 * Copied from drivers/net/can/sja1000/sja1000.h
 */

/* status रेजिस्टर content */
#घोषणा SR_BS		0x80
#घोषणा SR_ES		0x40
#घोषणा SR_TS		0x20
#घोषणा SR_RS		0x10
#घोषणा SR_TCS		0x08
#घोषणा SR_TBS		0x04
#घोषणा SR_DOS		0x02
#घोषणा SR_RBS		0x01

#घोषणा SR_CRIT (SR_BS|SR_ES)

/* ECC रेजिस्टर */
#घोषणा ECC_SEG		0x1F
#घोषणा ECC_सूची		0x20
#घोषणा ECC_ERR		6
#घोषणा ECC_BIT		0x00
#घोषणा ECC_FORM	0x40
#घोषणा ECC_STUFF	0x80
#घोषणा ECC_MASK	0xc0

/* Number of buffers क्रम use in the "new-style" host पूर्णांकerface */
#घोषणा ICAN3_NEW_BUFFERS	16

/* Number of buffers क्रम use in the "fast" host पूर्णांकerface */
#घोषणा ICAN3_TX_BUFFERS	512
#घोषणा ICAN3_RX_BUFFERS	1024

/* SJA1000 Clock Input */
#घोषणा ICAN3_CAN_CLOCK		8000000

/* Janz ICAN3 firmware types */
क्रमागत ican3_fwtype अणु
	ICAN3_FWTYPE_ICANOS,
	ICAN3_FWTYPE_CAL_CANOPEN,
पूर्ण;

/* Driver Name */
#घोषणा DRV_NAME "janz-ican3"

/* DPM Control Registers -- starts at offset 0x100 in the MODULbus रेजिस्टरs */
काष्ठा ican3_dpm_control अणु
	/* winकरोw address रेजिस्टर */
	u8 winकरोw_address;
	u8 unused1;

	/*
	 * Read access: clear पूर्णांकerrupt from microcontroller
	 * Write access: send पूर्णांकerrupt to microcontroller
	 */
	u8 पूर्णांकerrupt;
	u8 unused2;

	/* ग_लिखो-only: reset all hardware on the module */
	u8 hwreset;
	u8 unused3;

	/* ग_लिखो-only: generate an पूर्णांकerrupt to the TPU */
	u8 tpuपूर्णांकerrupt;
पूर्ण;

काष्ठा ican3_dev अणु

	/* must be the first member */
	काष्ठा can_priv can;

	/* CAN network device */
	काष्ठा net_device *ndev;
	काष्ठा napi_काष्ठा napi;

	/* module number */
	अचिन्हित पूर्णांक num;

	/* base address of रेजिस्टरs and IRQ */
	काष्ठा janz_cmodio_onboard_regs __iomem *ctrl;
	काष्ठा ican3_dpm_control __iomem *dpmctrl;
	व्योम __iomem *dpm;
	पूर्णांक irq;

	/* CAN bus termination status */
	काष्ठा completion termination_comp;
	bool termination_enabled;

	/* CAN bus error status रेजिस्टरs */
	काष्ठा completion buserror_comp;
	काष्ठा can_berr_counter bec;

	/* firmware type */
	क्रमागत ican3_fwtype fwtype;
	अक्षर fwinfo[32];

	/* old and new style host पूर्णांकerface */
	अचिन्हित पूर्णांक अगरtype;

	/* queue क्रम echo packets */
	काष्ठा sk_buff_head echoq;

	/*
	 * Any function which changes the current DPM page must hold this
	 * lock जबतक it is perक्रमming data accesses. This ensures that the
	 * function will not be preempted and end up पढ़ोing data from a
	 * dअगरferent DPM page than it expects.
	 */
	spinlock_t lock;

	/* new host पूर्णांकerface */
	अचिन्हित पूर्णांक rx_पूर्णांक;
	अचिन्हित पूर्णांक rx_num;
	अचिन्हित पूर्णांक tx_num;

	/* fast host पूर्णांकerface */
	अचिन्हित पूर्णांक fastrx_start;
	अचिन्हित पूर्णांक fastrx_num;
	अचिन्हित पूर्णांक fasttx_start;
	अचिन्हित पूर्णांक fasttx_num;

	/* first मुक्त DPM page */
	अचिन्हित पूर्णांक मुक्त_page;
पूर्ण;

काष्ठा ican3_msg अणु
	u8 control;
	u8 spec;
	__le16 len;
	u8 data[252];
पूर्ण;

काष्ठा ican3_new_desc अणु
	u8 control;
	u8 poपूर्णांकer;
पूर्ण;

काष्ठा ican3_fast_desc अणु
	u8 control;
	u8 command;
	u8 data[14];
पूर्ण;

/* ग_लिखो to the winकरोw basic address रेजिस्टर */
अटल अंतरभूत व्योम ican3_set_page(काष्ठा ican3_dev *mod, अचिन्हित पूर्णांक page)
अणु
	BUG_ON(page >= DPM_NUM_PAGES);
	ioग_लिखो8(page, &mod->dpmctrl->winकरोw_address);
पूर्ण

/*
 * ICAN3 "old-style" host पूर्णांकerface
 */

/*
 * Receive a message from the ICAN3 "old-style" firmware पूर्णांकerface
 *
 * LOCKING: must hold mod->lock
 *
 * वापसs 0 on success, -ENOMEM when no message exists
 */
अटल पूर्णांक ican3_old_recv_msg(काष्ठा ican3_dev *mod, काष्ठा ican3_msg *msg)
अणु
	अचिन्हित पूर्णांक mbox, mbox_page;
	u8 locl, peer, xord;

	/* get the MSYNC रेजिस्टरs */
	ican3_set_page(mod, QUEUE_OLD_CONTROL);
	peer = ioपढ़ो8(mod->dpm + MSYNC_PEER);
	locl = ioपढ़ो8(mod->dpm + MSYNC_LOCL);
	xord = locl ^ peer;

	अगर ((xord & MSYNC_RB_MASK) == 0x00) अणु
		netdev_dbg(mod->ndev, "no mbox for reading\n");
		वापस -ENOMEM;
	पूर्ण

	/* find the first मुक्त mbox to पढ़ो */
	अगर ((xord & MSYNC_RB_MASK) == MSYNC_RB_MASK)
		mbox = (xord & MSYNC_RBLW) ? MSYNC_RB0 : MSYNC_RB1;
	अन्यथा
		mbox = (xord & MSYNC_RB0) ? MSYNC_RB0 : MSYNC_RB1;

	/* copy the message */
	mbox_page = (mbox == MSYNC_RB0) ? QUEUE_OLD_RB0 : QUEUE_OLD_RB1;
	ican3_set_page(mod, mbox_page);
	स_नकल_fromio(msg, mod->dpm, माप(*msg));

	/*
	 * notअगरy the firmware that the पढ़ो buffer is available
	 * क्रम it to fill again
	 */
	locl ^= mbox;

	ican3_set_page(mod, QUEUE_OLD_CONTROL);
	ioग_लिखो8(locl, mod->dpm + MSYNC_LOCL);
	वापस 0;
पूर्ण

/*
 * Send a message through the "old-style" firmware पूर्णांकerface
 *
 * LOCKING: must hold mod->lock
 *
 * वापसs 0 on success, -ENOMEM when no मुक्त space exists
 */
अटल पूर्णांक ican3_old_send_msg(काष्ठा ican3_dev *mod, काष्ठा ican3_msg *msg)
अणु
	अचिन्हित पूर्णांक mbox, mbox_page;
	u8 locl, peer, xord;

	/* get the MSYNC रेजिस्टरs */
	ican3_set_page(mod, QUEUE_OLD_CONTROL);
	peer = ioपढ़ो8(mod->dpm + MSYNC_PEER);
	locl = ioपढ़ो8(mod->dpm + MSYNC_LOCL);
	xord = locl ^ peer;

	अगर ((xord & MSYNC_WB_MASK) == MSYNC_WB_MASK) अणु
		netdev_err(mod->ndev, "no mbox for writing\n");
		वापस -ENOMEM;
	पूर्ण

	/* calculate a मुक्त mbox to use */
	mbox = (xord & MSYNC_WB0) ? MSYNC_WB1 : MSYNC_WB0;

	/* copy the message to the DPM */
	mbox_page = (mbox == MSYNC_WB0) ? QUEUE_OLD_WB0 : QUEUE_OLD_WB1;
	ican3_set_page(mod, mbox_page);
	स_नकल_toio(mod->dpm, msg, माप(*msg));

	locl ^= mbox;
	अगर (mbox == MSYNC_WB1)
		locl |= MSYNC_WBLW;

	ican3_set_page(mod, QUEUE_OLD_CONTROL);
	ioग_लिखो8(locl, mod->dpm + MSYNC_LOCL);
	वापस 0;
पूर्ण

/*
 * ICAN3 "new-style" Host Interface Setup
 */

अटल व्योम ican3_init_new_host_पूर्णांकerface(काष्ठा ican3_dev *mod)
अणु
	काष्ठा ican3_new_desc desc;
	अचिन्हित दीर्घ flags;
	व्योम __iomem *dst;
	पूर्णांक i;

	spin_lock_irqsave(&mod->lock, flags);

	/* setup the पूर्णांकernal dataकाष्ठाures क्रम RX */
	mod->rx_num = 0;
	mod->rx_पूर्णांक = 0;

	/* tohost queue descriptors are in page 5 */
	ican3_set_page(mod, QUEUE_TOHOST);
	dst = mod->dpm;

	/* initialize the tohost (rx) queue descriptors: pages 9-24 */
	क्रम (i = 0; i < ICAN3_NEW_BUFFERS; i++) अणु
		desc.control = DESC_INTERRUPT | DESC_LEN(1); /* I L=1 */
		desc.poपूर्णांकer = mod->मुक्त_page;

		/* set wrap flag on last buffer */
		अगर (i == ICAN3_NEW_BUFFERS - 1)
			desc.control |= DESC_WRAP;

		स_नकल_toio(dst, &desc, माप(desc));
		dst += माप(desc);
		mod->मुक्त_page++;
	पूर्ण

	/* fromhost (tx) mid queue descriptors are in page 6 */
	ican3_set_page(mod, QUEUE_FROMHOST_MID);
	dst = mod->dpm;

	/* setup the पूर्णांकernal dataकाष्ठाures क्रम TX */
	mod->tx_num = 0;

	/* initialize the fromhost mid queue descriptors: pages 25-40 */
	क्रम (i = 0; i < ICAN3_NEW_BUFFERS; i++) अणु
		desc.control = DESC_VALID | DESC_LEN(1); /* V L=1 */
		desc.poपूर्णांकer = mod->मुक्त_page;

		/* set wrap flag on last buffer */
		अगर (i == ICAN3_NEW_BUFFERS - 1)
			desc.control |= DESC_WRAP;

		स_नकल_toio(dst, &desc, माप(desc));
		dst += माप(desc);
		mod->मुक्त_page++;
	पूर्ण

	/* fromhost hi queue descriptors are in page 7 */
	ican3_set_page(mod, QUEUE_FROMHOST_HIGH);
	dst = mod->dpm;

	/* initialize only a single buffer in the fromhost hi queue (unused) */
	desc.control = DESC_VALID | DESC_WRAP | DESC_LEN(1); /* VW L=1 */
	desc.poपूर्णांकer = mod->मुक्त_page;
	स_नकल_toio(dst, &desc, माप(desc));
	mod->मुक्त_page++;

	/* fromhost low queue descriptors are in page 8 */
	ican3_set_page(mod, QUEUE_FROMHOST_LOW);
	dst = mod->dpm;

	/* initialize only a single buffer in the fromhost low queue (unused) */
	desc.control = DESC_VALID | DESC_WRAP | DESC_LEN(1); /* VW L=1 */
	desc.poपूर्णांकer = mod->मुक्त_page;
	स_नकल_toio(dst, &desc, माप(desc));
	mod->मुक्त_page++;

	spin_unlock_irqrestore(&mod->lock, flags);
पूर्ण

/*
 * ICAN3 Fast Host Interface Setup
 */

अटल व्योम ican3_init_fast_host_पूर्णांकerface(काष्ठा ican3_dev *mod)
अणु
	काष्ठा ican3_fast_desc desc;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक addr;
	व्योम __iomem *dst;
	पूर्णांक i;

	spin_lock_irqsave(&mod->lock, flags);

	/* save the start recv page */
	mod->fastrx_start = mod->मुक्त_page;
	mod->fastrx_num = 0;

	/* build a single fast tohost queue descriptor */
	स_रखो(&desc, 0, माप(desc));
	desc.control = 0x00;
	desc.command = 1;

	/* build the tohost queue descriptor ring in memory */
	addr = 0;
	क्रम (i = 0; i < ICAN3_RX_BUFFERS; i++) अणु

		/* set the wrap bit on the last buffer */
		अगर (i == ICAN3_RX_BUFFERS - 1)
			desc.control |= DESC_WRAP;

		/* चयन to the correct page */
		ican3_set_page(mod, mod->मुक्त_page);

		/* copy the descriptor to the DPM */
		dst = mod->dpm + addr;
		स_नकल_toio(dst, &desc, माप(desc));
		addr += माप(desc);

		/* move to the next page अगर necessary */
		अगर (addr >= DPM_PAGE_SIZE) अणु
			addr = 0;
			mod->मुक्त_page++;
		पूर्ण
	पूर्ण

	/* make sure we page-align the next queue */
	अगर (addr != 0)
		mod->मुक्त_page++;

	/* save the start xmit page */
	mod->fasttx_start = mod->मुक्त_page;
	mod->fasttx_num = 0;

	/* build a single fast fromhost queue descriptor */
	स_रखो(&desc, 0, माप(desc));
	desc.control = DESC_VALID;
	desc.command = 1;

	/* build the fromhost queue descriptor ring in memory */
	addr = 0;
	क्रम (i = 0; i < ICAN3_TX_BUFFERS; i++) अणु

		/* set the wrap bit on the last buffer */
		अगर (i == ICAN3_TX_BUFFERS - 1)
			desc.control |= DESC_WRAP;

		/* चयन to the correct page */
		ican3_set_page(mod, mod->मुक्त_page);

		/* copy the descriptor to the DPM */
		dst = mod->dpm + addr;
		स_नकल_toio(dst, &desc, माप(desc));
		addr += माप(desc);

		/* move to the next page अगर necessary */
		अगर (addr >= DPM_PAGE_SIZE) अणु
			addr = 0;
			mod->मुक्त_page++;
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&mod->lock, flags);
पूर्ण

/*
 * ICAN3 "new-style" Host Interface Message Helpers
 */

/*
 * LOCKING: must hold mod->lock
 */
अटल पूर्णांक ican3_new_send_msg(काष्ठा ican3_dev *mod, काष्ठा ican3_msg *msg)
अणु
	काष्ठा ican3_new_desc desc;
	व्योम __iomem *desc_addr = mod->dpm + (mod->tx_num * माप(desc));

	/* चयन to the fromhost mid queue, and पढ़ो the buffer descriptor */
	ican3_set_page(mod, QUEUE_FROMHOST_MID);
	स_नकल_fromio(&desc, desc_addr, माप(desc));

	अगर (!(desc.control & DESC_VALID)) अणु
		netdev_dbg(mod->ndev, "%s: no free buffers\n", __func__);
		वापस -ENOMEM;
	पूर्ण

	/* चयन to the data page, copy the data */
	ican3_set_page(mod, desc.poपूर्णांकer);
	स_नकल_toio(mod->dpm, msg, माप(*msg));

	/* चयन back to the descriptor, set the valid bit, ग_लिखो it back */
	ican3_set_page(mod, QUEUE_FROMHOST_MID);
	desc.control ^= DESC_VALID;
	स_नकल_toio(desc_addr, &desc, माप(desc));

	/* update the tx number */
	mod->tx_num = (desc.control & DESC_WRAP) ? 0 : (mod->tx_num + 1);
	वापस 0;
पूर्ण

/*
 * LOCKING: must hold mod->lock
 */
अटल पूर्णांक ican3_new_recv_msg(काष्ठा ican3_dev *mod, काष्ठा ican3_msg *msg)
अणु
	काष्ठा ican3_new_desc desc;
	व्योम __iomem *desc_addr = mod->dpm + (mod->rx_num * माप(desc));

	/* चयन to the tohost queue, and पढ़ो the buffer descriptor */
	ican3_set_page(mod, QUEUE_TOHOST);
	स_नकल_fromio(&desc, desc_addr, माप(desc));

	अगर (!(desc.control & DESC_VALID)) अणु
		netdev_dbg(mod->ndev, "%s: no buffers to recv\n", __func__);
		वापस -ENOMEM;
	पूर्ण

	/* चयन to the data page, copy the data */
	ican3_set_page(mod, desc.poपूर्णांकer);
	स_नकल_fromio(msg, mod->dpm, माप(*msg));

	/* चयन back to the descriptor, toggle the valid bit, ग_लिखो it back */
	ican3_set_page(mod, QUEUE_TOHOST);
	desc.control ^= DESC_VALID;
	स_नकल_toio(desc_addr, &desc, माप(desc));

	/* update the rx number */
	mod->rx_num = (desc.control & DESC_WRAP) ? 0 : (mod->rx_num + 1);
	वापस 0;
पूर्ण

/*
 * Message Send / Recv Helpers
 */

अटल पूर्णांक ican3_send_msg(काष्ठा ican3_dev *mod, काष्ठा ican3_msg *msg)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&mod->lock, flags);

	अगर (mod->अगरtype == 0)
		ret = ican3_old_send_msg(mod, msg);
	अन्यथा
		ret = ican3_new_send_msg(mod, msg);

	spin_unlock_irqrestore(&mod->lock, flags);
	वापस ret;
पूर्ण

अटल पूर्णांक ican3_recv_msg(काष्ठा ican3_dev *mod, काष्ठा ican3_msg *msg)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&mod->lock, flags);

	अगर (mod->अगरtype == 0)
		ret = ican3_old_recv_msg(mod, msg);
	अन्यथा
		ret = ican3_new_recv_msg(mod, msg);

	spin_unlock_irqrestore(&mod->lock, flags);
	वापस ret;
पूर्ण

/*
 * Quick Pre-स्थिरructed Messages
 */

अटल पूर्णांक ican3_msg_connect(काष्ठा ican3_dev *mod)
अणु
	काष्ठा ican3_msg msg;

	स_रखो(&msg, 0, माप(msg));
	msg.spec = MSG_CONNECTI;
	msg.len = cpu_to_le16(0);

	वापस ican3_send_msg(mod, &msg);
पूर्ण

अटल पूर्णांक ican3_msg_disconnect(काष्ठा ican3_dev *mod)
अणु
	काष्ठा ican3_msg msg;

	स_रखो(&msg, 0, माप(msg));
	msg.spec = MSG_DISCONNECT;
	msg.len = cpu_to_le16(0);

	वापस ican3_send_msg(mod, &msg);
पूर्ण

अटल पूर्णांक ican3_msg_newhostअगर(काष्ठा ican3_dev *mod)
अणु
	काष्ठा ican3_msg msg;
	पूर्णांक ret;

	स_रखो(&msg, 0, माप(msg));
	msg.spec = MSG_NEWHOSTIF;
	msg.len = cpu_to_le16(0);

	/* If we're not using the old पूर्णांकerface, चयनing seems bogus */
	WARN_ON(mod->अगरtype != 0);

	ret = ican3_send_msg(mod, &msg);
	अगर (ret)
		वापस ret;

	/* mark the module as using the new host पूर्णांकerface */
	mod->अगरtype = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक ican3_msg_fasthostअगर(काष्ठा ican3_dev *mod)
अणु
	काष्ठा ican3_msg msg;
	अचिन्हित पूर्णांक addr;

	स_रखो(&msg, 0, माप(msg));
	msg.spec = MSG_INITFDPMQUEUE;
	msg.len = cpu_to_le16(8);

	/* ग_लिखो the tohost queue start address */
	addr = DPM_PAGE_ADDR(mod->fastrx_start);
	msg.data[0] = addr & 0xff;
	msg.data[1] = (addr >> 8) & 0xff;
	msg.data[2] = (addr >> 16) & 0xff;
	msg.data[3] = (addr >> 24) & 0xff;

	/* ग_लिखो the fromhost queue start address */
	addr = DPM_PAGE_ADDR(mod->fasttx_start);
	msg.data[4] = addr & 0xff;
	msg.data[5] = (addr >> 8) & 0xff;
	msg.data[6] = (addr >> 16) & 0xff;
	msg.data[7] = (addr >> 24) & 0xff;

	/* If we're not using the new पूर्णांकerface yet, we cannot करो this */
	WARN_ON(mod->अगरtype != 1);

	वापस ican3_send_msg(mod, &msg);
पूर्ण

/*
 * Setup the CAN filter to either accept or reject all
 * messages from the CAN bus.
 */
अटल पूर्णांक ican3_set_id_filter(काष्ठा ican3_dev *mod, bool accept)
अणु
	काष्ठा ican3_msg msg;
	पूर्णांक ret;

	/* Standard Frame Format */
	स_रखो(&msg, 0, माप(msg));
	msg.spec = MSG_SETAFILMASK;
	msg.len = cpu_to_le16(5);
	msg.data[0] = 0x00; /* IDLo LSB */
	msg.data[1] = 0x00; /* IDLo MSB */
	msg.data[2] = 0xff; /* IDHi LSB */
	msg.data[3] = 0x07; /* IDHi MSB */

	/* accept all frames क्रम fast host अगर, or reject all frames */
	msg.data[4] = accept ? SETAFILMASK_FASTIF : SETAFILMASK_REJECT;

	ret = ican3_send_msg(mod, &msg);
	अगर (ret)
		वापस ret;

	/* Extended Frame Format */
	स_रखो(&msg, 0, माप(msg));
	msg.spec = MSG_SETAFILMASK;
	msg.len = cpu_to_le16(13);
	msg.data[0] = 0;    /* MUX = 0 */
	msg.data[1] = 0x00; /* IDLo LSB */
	msg.data[2] = 0x00;
	msg.data[3] = 0x00;
	msg.data[4] = 0x20; /* IDLo MSB */
	msg.data[5] = 0xff; /* IDHi LSB */
	msg.data[6] = 0xff;
	msg.data[7] = 0xff;
	msg.data[8] = 0x3f; /* IDHi MSB */

	/* accept all frames क्रम fast host अगर, or reject all frames */
	msg.data[9] = accept ? SETAFILMASK_FASTIF : SETAFILMASK_REJECT;

	वापस ican3_send_msg(mod, &msg);
पूर्ण

/*
 * Bring the CAN bus online or offline
 */
अटल पूर्णांक ican3_set_bus_state(काष्ठा ican3_dev *mod, bool on)
अणु
	काष्ठा can_bittiming *bt = &mod->can.bittiming;
	काष्ठा ican3_msg msg;
	u8 btr0, btr1;
	पूर्णांक res;

	/* This algorithm was stolen from drivers/net/can/sja1000/sja1000.c      */
	/* The bittiming रेजिस्टर command क्रम the ICAN3 just sets the bit timing */
	/* रेजिस्टरs on the SJA1000 chip directly                                */
	btr0 = ((bt->brp - 1) & 0x3f) | (((bt->sjw - 1) & 0x3) << 6);
	btr1 = ((bt->prop_seg + bt->phase_seg1 - 1) & 0xf) |
		(((bt->phase_seg2 - 1) & 0x7) << 4);
	अगर (mod->can.ctrlmode & CAN_CTRLMODE_3_SAMPLES)
		btr1 |= 0x80;

	अगर (mod->fwtype == ICAN3_FWTYPE_ICANOS) अणु
		अगर (on) अणु
			/* set bittiming */
			स_रखो(&msg, 0, माप(msg));
			msg.spec = MSG_CBTRREQ;
			msg.len = cpu_to_le16(4);
			msg.data[0] = 0x00;
			msg.data[1] = 0x00;
			msg.data[2] = btr0;
			msg.data[3] = btr1;

			res = ican3_send_msg(mod, &msg);
			अगर (res)
				वापस res;
		पूर्ण

		/* can-on/off request */
		स_रखो(&msg, 0, माप(msg));
		msg.spec = on ? MSG_CONREQ : MSG_COFFREQ;
		msg.len = cpu_to_le16(0);

		वापस ican3_send_msg(mod, &msg);

	पूर्ण अन्यथा अगर (mod->fwtype == ICAN3_FWTYPE_CAL_CANOPEN) अणु
		/* bittiming + can-on/off request */
		स_रखो(&msg, 0, माप(msg));
		msg.spec = MSG_LMTS;
		अगर (on) अणु
			msg.len = cpu_to_le16(4);
			msg.data[0] = LMTS_BUSON_REQ;
			msg.data[1] = 0;
			msg.data[2] = btr0;
			msg.data[3] = btr1;
		पूर्ण अन्यथा अणु
			msg.len = cpu_to_le16(2);
			msg.data[0] = LMTS_BUSOFF_REQ;
			msg.data[1] = 0;
		पूर्ण
		res = ican3_send_msg(mod, &msg);
		अगर (res)
			वापस res;

		अगर (on) अणु
			/* create NMT Slave Node क्रम error processing
			 *   class 2 (with error capability, see CiA/DS203-1)
			 *   id    1
			 *   name  locnod1 (must be exactly 7 bytes)
			 */
			स_रखो(&msg, 0, माप(msg));
			msg.spec = MSG_NMTS;
			msg.len = cpu_to_le16(11);
			msg.data[0] = NMTS_CREATE_NODE_REQ;
			msg.data[1] = 0;
			msg.data[2] = 2;                 /* node class */
			msg.data[3] = 1;                 /* node id */
			म_नकल(msg.data + 4, "locnod1"); /* node name  */
			वापस ican3_send_msg(mod, &msg);
		पूर्ण
		वापस 0;
	पूर्ण
	वापस -ENOTSUPP;
पूर्ण

अटल पूर्णांक ican3_set_termination(काष्ठा ican3_dev *mod, bool on)
अणु
	काष्ठा ican3_msg msg;

	स_रखो(&msg, 0, माप(msg));
	msg.spec = MSG_HWCONF;
	msg.len = cpu_to_le16(2);
	msg.data[0] = 0x00;
	msg.data[1] = on ? HWCONF_TERMINATE_ON : HWCONF_TERMINATE_OFF;

	वापस ican3_send_msg(mod, &msg);
पूर्ण

अटल पूर्णांक ican3_send_inquiry(काष्ठा ican3_dev *mod, u8 subspec)
अणु
	काष्ठा ican3_msg msg;

	स_रखो(&msg, 0, माप(msg));
	msg.spec = MSG_INQUIRY;
	msg.len = cpu_to_le16(2);
	msg.data[0] = subspec;
	msg.data[1] = 0x00;

	वापस ican3_send_msg(mod, &msg);
पूर्ण

अटल पूर्णांक ican3_set_buserror(काष्ठा ican3_dev *mod, u8 quota)
अणु
	काष्ठा ican3_msg msg;

	अगर (mod->fwtype == ICAN3_FWTYPE_ICANOS) अणु
		स_रखो(&msg, 0, माप(msg));
		msg.spec = MSG_CCONFREQ;
		msg.len = cpu_to_le16(2);
		msg.data[0] = 0x00;
		msg.data[1] = quota;
	पूर्ण अन्यथा अगर (mod->fwtype == ICAN3_FWTYPE_CAL_CANOPEN) अणु
		स_रखो(&msg, 0, माप(msg));
		msg.spec = MSG_LMTS;
		msg.len = cpu_to_le16(4);
		msg.data[0] = LMTS_CAN_CONF_REQ;
		msg.data[1] = 0x00;
		msg.data[2] = 0x00;
		msg.data[3] = quota;
	पूर्ण अन्यथा अणु
		वापस -ENOTSUPP;
	पूर्ण
	वापस ican3_send_msg(mod, &msg);
पूर्ण

/*
 * ICAN3 to Linux CAN Frame Conversion
 */

अटल व्योम ican3_to_can_frame(काष्ठा ican3_dev *mod,
			       काष्ठा ican3_fast_desc *desc,
			       काष्ठा can_frame *cf)
अणु
	अगर ((desc->command & ICAN3_CAN_TYPE_MASK) == ICAN3_CAN_TYPE_SFF) अणु
		अगर (desc->data[1] & ICAN3_SFF_RTR)
			cf->can_id |= CAN_RTR_FLAG;

		cf->can_id |= desc->data[0] << 3;
		cf->can_id |= (desc->data[1] & 0xe0) >> 5;
		cf->len = can_cc_dlc2len(desc->data[1] & ICAN3_CAN_DLC_MASK);
		स_नकल(cf->data, &desc->data[2], cf->len);
	पूर्ण अन्यथा अणु
		cf->len = can_cc_dlc2len(desc->data[0] & ICAN3_CAN_DLC_MASK);
		अगर (desc->data[0] & ICAN3_EFF_RTR)
			cf->can_id |= CAN_RTR_FLAG;

		अगर (desc->data[0] & ICAN3_EFF) अणु
			cf->can_id |= CAN_EFF_FLAG;
			cf->can_id |= desc->data[2] << 21; /* 28-21 */
			cf->can_id |= desc->data[3] << 13; /* 20-13 */
			cf->can_id |= desc->data[4] << 5;  /* 12-5  */
			cf->can_id |= (desc->data[5] & 0xf8) >> 3;
		पूर्ण अन्यथा अणु
			cf->can_id |= desc->data[2] << 3;  /* 10-3  */
			cf->can_id |= desc->data[3] >> 5;  /* 2-0   */
		पूर्ण

		स_नकल(cf->data, &desc->data[6], cf->len);
	पूर्ण
पूर्ण

अटल व्योम can_frame_to_ican3(काष्ठा ican3_dev *mod,
			       काष्ठा can_frame *cf,
			       काष्ठा ican3_fast_desc *desc)
अणु
	/* clear out any stale data in the descriptor */
	स_रखो(desc->data, 0, माप(desc->data));

	/* we always use the extended क्रमmat, with the ECHO flag set */
	desc->command = ICAN3_CAN_TYPE_EFF;
	desc->data[0] |= cf->len;
	desc->data[1] |= ICAN3_ECHO;

	/* support single transmission (no retries) mode */
	अगर (mod->can.ctrlmode & CAN_CTRLMODE_ONE_SHOT)
		desc->data[1] |= ICAN3_SNGL;

	अगर (cf->can_id & CAN_RTR_FLAG)
		desc->data[0] |= ICAN3_EFF_RTR;

	/* pack the id पूर्णांकo the correct places */
	अगर (cf->can_id & CAN_EFF_FLAG) अणु
		desc->data[0] |= ICAN3_EFF;
		desc->data[2] = (cf->can_id & 0x1fe00000) >> 21; /* 28-21 */
		desc->data[3] = (cf->can_id & 0x001fe000) >> 13; /* 20-13 */
		desc->data[4] = (cf->can_id & 0x00001fe0) >> 5;  /* 12-5  */
		desc->data[5] = (cf->can_id & 0x0000001f) << 3;  /* 4-0   */
	पूर्ण अन्यथा अणु
		desc->data[2] = (cf->can_id & 0x7F8) >> 3; /* bits 10-3 */
		desc->data[3] = (cf->can_id & 0x007) << 5; /* bits 2-0  */
	पूर्ण

	/* copy the data bits पूर्णांकo the descriptor */
	स_नकल(&desc->data[6], cf->data, cf->len);
पूर्ण

/*
 * Interrupt Handling
 */

/*
 * Handle an ID + Version message response from the firmware. We never generate
 * this message in production code, but it is very useful when debugging to be
 * able to display this message.
 */
अटल व्योम ican3_handle_idvers(काष्ठा ican3_dev *mod, काष्ठा ican3_msg *msg)
अणु
	netdev_dbg(mod->ndev, "IDVERS response: %s\n", msg->data);
पूर्ण

अटल व्योम ican3_handle_msglost(काष्ठा ican3_dev *mod, काष्ठा ican3_msg *msg)
अणु
	काष्ठा net_device *dev = mod->ndev;
	काष्ठा net_device_stats *stats = &dev->stats;
	काष्ठा can_frame *cf;
	काष्ठा sk_buff *skb;

	/*
	 * Report that communication messages with the microcontroller firmware
	 * are being lost. These are never CAN frames, so we करो not generate an
	 * error frame क्रम userspace
	 */
	अगर (msg->spec == MSG_MSGLOST) अणु
		netdev_err(mod->ndev, "lost %d control messages\n", msg->data[0]);
		वापस;
	पूर्ण

	/*
	 * Oops, this indicates that we have lost messages in the fast queue,
	 * which are exclusively CAN messages. Our driver isn't पढ़ोing CAN
	 * frames fast enough.
	 *
	 * We'll pretend that the SJA1000 told us that it ran out of buffer
	 * space, because there is not a better message क्रम this.
	 */
	skb = alloc_can_err_skb(dev, &cf);
	अगर (skb) अणु
		cf->can_id |= CAN_ERR_CRTL;
		cf->data[1] = CAN_ERR_CRTL_RX_OVERFLOW;
		stats->rx_over_errors++;
		stats->rx_errors++;
		netअगर_rx(skb);
	पूर्ण
पूर्ण

/*
 * Handle CAN Event Indication Messages from the firmware
 *
 * The ICAN3 firmware provides the values of some SJA1000 रेजिस्टरs when it
 * generates this message. The code below is largely copied from the
 * drivers/net/can/sja1000/sja1000.c file, and adapted as necessary
 */
अटल पूर्णांक ican3_handle_cevtind(काष्ठा ican3_dev *mod, काष्ठा ican3_msg *msg)
अणु
	काष्ठा net_device *dev = mod->ndev;
	काष्ठा net_device_stats *stats = &dev->stats;
	क्रमागत can_state state = mod->can.state;
	u8 isrc, ecc, status, rxerr, txerr;
	काष्ठा can_frame *cf;
	काष्ठा sk_buff *skb;

	/* we can only handle the SJA1000 part */
	अगर (msg->data[1] != CEVTIND_CHIP_SJA1000) अणु
		netdev_err(mod->ndev, "unable to handle errors on non-SJA1000\n");
		वापस -ENODEV;
	पूर्ण

	/* check the message length क्रम sanity */
	अगर (le16_to_cpu(msg->len) < 6) अणु
		netdev_err(mod->ndev, "error message too short\n");
		वापस -EINVAL;
	पूर्ण

	isrc = msg->data[0];
	ecc = msg->data[2];
	status = msg->data[3];
	rxerr = msg->data[4];
	txerr = msg->data[5];

	/*
	 * This hardware lacks any support other than bus error messages to
	 * determine अगर packet transmission has failed.
	 *
	 * When TX errors happen, one echo skb needs to be dropped from the
	 * front of the queue.
	 *
	 * A small bit of code is duplicated here and below, to aव्योम error
	 * skb allocation when it will just be मुक्तd immediately.
	 */
	अगर (isrc == CEVTIND_BEI) अणु
		पूर्णांक ret;
		netdev_dbg(mod->ndev, "bus error interrupt\n");

		/* TX error */
		अगर (!(ecc & ECC_सूची)) अणु
			kमुक्त_skb(skb_dequeue(&mod->echoq));
			stats->tx_errors++;
		पूर्ण अन्यथा अणु
			stats->rx_errors++;
		पूर्ण

		/*
		 * The controller स्वतःmatically disables bus-error पूर्णांकerrupts
		 * and thereक्रमe we must re-enable them.
		 */
		ret = ican3_set_buserror(mod, 1);
		अगर (ret) अणु
			netdev_err(mod->ndev, "unable to re-enable bus-error\n");
			वापस ret;
		पूर्ण

		/* bus error reporting is off, वापस immediately */
		अगर (!(mod->can.ctrlmode & CAN_CTRLMODE_BERR_REPORTING))
			वापस 0;
	पूर्ण

	skb = alloc_can_err_skb(dev, &cf);
	अगर (skb == शून्य)
		वापस -ENOMEM;

	/* data overrun पूर्णांकerrupt */
	अगर (isrc == CEVTIND_DOI || isrc == CEVTIND_LOST) अणु
		netdev_dbg(mod->ndev, "data overrun interrupt\n");
		cf->can_id |= CAN_ERR_CRTL;
		cf->data[1] = CAN_ERR_CRTL_RX_OVERFLOW;
		stats->rx_over_errors++;
		stats->rx_errors++;
	पूर्ण

	/* error warning + passive पूर्णांकerrupt */
	अगर (isrc == CEVTIND_EI) अणु
		netdev_dbg(mod->ndev, "error warning + passive interrupt\n");
		अगर (status & SR_BS) अणु
			state = CAN_STATE_BUS_OFF;
			cf->can_id |= CAN_ERR_BUSOFF;
			mod->can.can_stats.bus_off++;
			can_bus_off(dev);
		पूर्ण अन्यथा अगर (status & SR_ES) अणु
			अगर (rxerr >= 128 || txerr >= 128)
				state = CAN_STATE_ERROR_PASSIVE;
			अन्यथा
				state = CAN_STATE_ERROR_WARNING;
		पूर्ण अन्यथा अणु
			state = CAN_STATE_ERROR_ACTIVE;
		पूर्ण
	पूर्ण

	/* bus error पूर्णांकerrupt */
	अगर (isrc == CEVTIND_BEI) अणु
		mod->can.can_stats.bus_error++;
		cf->can_id |= CAN_ERR_PROT | CAN_ERR_BUSERROR;

		चयन (ecc & ECC_MASK) अणु
		हाल ECC_BIT:
			cf->data[2] |= CAN_ERR_PROT_BIT;
			अवरोध;
		हाल ECC_FORM:
			cf->data[2] |= CAN_ERR_PROT_FORM;
			अवरोध;
		हाल ECC_STUFF:
			cf->data[2] |= CAN_ERR_PROT_STUFF;
			अवरोध;
		शेष:
			cf->data[3] = ecc & ECC_SEG;
			अवरोध;
		पूर्ण

		अगर (!(ecc & ECC_सूची))
			cf->data[2] |= CAN_ERR_PROT_TX;

		cf->data[6] = txerr;
		cf->data[7] = rxerr;
	पूर्ण

	अगर (state != mod->can.state && (state == CAN_STATE_ERROR_WARNING ||
					state == CAN_STATE_ERROR_PASSIVE)) अणु
		cf->can_id |= CAN_ERR_CRTL;
		अगर (state == CAN_STATE_ERROR_WARNING) अणु
			mod->can.can_stats.error_warning++;
			cf->data[1] = (txerr > rxerr) ?
				CAN_ERR_CRTL_TX_WARNING :
				CAN_ERR_CRTL_RX_WARNING;
		पूर्ण अन्यथा अणु
			mod->can.can_stats.error_passive++;
			cf->data[1] = (txerr > rxerr) ?
				CAN_ERR_CRTL_TX_PASSIVE :
				CAN_ERR_CRTL_RX_PASSIVE;
		पूर्ण

		cf->data[6] = txerr;
		cf->data[7] = rxerr;
	पूर्ण

	mod->can.state = state;
	netअगर_rx(skb);
	वापस 0;
पूर्ण

अटल व्योम ican3_handle_inquiry(काष्ठा ican3_dev *mod, काष्ठा ican3_msg *msg)
अणु
	चयन (msg->data[0]) अणु
	हाल INQUIRY_STATUS:
	हाल INQUIRY_EXTENDED:
		mod->bec.rxerr = msg->data[5];
		mod->bec.txerr = msg->data[6];
		complete(&mod->buserror_comp);
		अवरोध;
	हाल INQUIRY_TERMINATION:
		mod->termination_enabled = msg->data[6] & HWCONF_TERMINATE_ON;
		complete(&mod->termination_comp);
		अवरोध;
	शेष:
		netdev_err(mod->ndev, "received an unknown inquiry response\n");
		अवरोध;
	पूर्ण
पूर्ण

/* Handle NMTS Slave Event Indication Messages from the firmware */
अटल व्योम ican3_handle_nmtsind(काष्ठा ican3_dev *mod, काष्ठा ican3_msg *msg)
अणु
	u16 subspec;

	subspec = msg->data[0] + msg->data[1] * 0x100;
	अगर (subspec == NMTS_SLAVE_EVENT_IND) अणु
		चयन (msg->data[2]) अणु
		हाल NE_LOCAL_OCCURRED:
		हाल NE_LOCAL_RESOLVED:
			/* now follows the same message as Raw ICANOS CEVTIND
			 * shअगरt the data at the same place and call this method
			 */
			le16_add_cpu(&msg->len, -3);
			स_हटाओ(msg->data, msg->data + 3, le16_to_cpu(msg->len));
			ican3_handle_cevtind(mod, msg);
			अवरोध;
		हाल NE_REMOTE_OCCURRED:
		हाल NE_REMOTE_RESOLVED:
			/* should not occurre, ignore */
			अवरोध;
		शेष:
			netdev_warn(mod->ndev, "unknown NMTS event indication %x\n",
				    msg->data[2]);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (subspec == NMTS_SLAVE_STATE_IND) अणु
		/* ignore state indications */
	पूर्ण अन्यथा अणु
		netdev_warn(mod->ndev, "unhandled NMTS indication %x\n",
			    subspec);
		वापस;
	पूर्ण
पूर्ण

अटल व्योम ican3_handle_unknown_message(काष्ठा ican3_dev *mod,
					काष्ठा ican3_msg *msg)
अणु
	netdev_warn(mod->ndev, "received unknown message: spec 0x%.2x length %d\n",
			   msg->spec, le16_to_cpu(msg->len));
पूर्ण

/*
 * Handle a control message from the firmware
 */
अटल व्योम ican3_handle_message(काष्ठा ican3_dev *mod, काष्ठा ican3_msg *msg)
अणु
	netdev_dbg(mod->ndev, "%s: modno %d spec 0x%.2x len %d bytes\n", __func__,
			   mod->num, msg->spec, le16_to_cpu(msg->len));

	चयन (msg->spec) अणु
	हाल MSG_IDVERS:
		ican3_handle_idvers(mod, msg);
		अवरोध;
	हाल MSG_MSGLOST:
	हाल MSG_FMSGLOST:
		ican3_handle_msglost(mod, msg);
		अवरोध;
	हाल MSG_CEVTIND:
		ican3_handle_cevtind(mod, msg);
		अवरोध;
	हाल MSG_INQUIRY:
		ican3_handle_inquiry(mod, msg);
		अवरोध;
	हाल MSG_NMTS:
		ican3_handle_nmtsind(mod, msg);
		अवरोध;
	शेष:
		ican3_handle_unknown_message(mod, msg);
		अवरोध;
	पूर्ण
पूर्ण

/*
 * The ican3 needs to store all echo skbs, and thereक्रमe cannot
 * use the generic infraकाष्ठाure क्रम this.
 */
अटल व्योम ican3_put_echo_skb(काष्ठा ican3_dev *mod, काष्ठा sk_buff *skb)
अणु
	skb = can_create_echo_skb(skb);
	अगर (!skb)
		वापस;

	/* save this skb क्रम tx पूर्णांकerrupt echo handling */
	skb_queue_tail(&mod->echoq, skb);
पूर्ण

अटल अचिन्हित पूर्णांक ican3_get_echo_skb(काष्ठा ican3_dev *mod)
अणु
	काष्ठा sk_buff *skb = skb_dequeue(&mod->echoq);
	काष्ठा can_frame *cf;
	u8 dlc;

	/* this should never trigger unless there is a driver bug */
	अगर (!skb) अणु
		netdev_err(mod->ndev, "BUG: echo skb not occupied\n");
		वापस 0;
	पूर्ण

	cf = (काष्ठा can_frame *)skb->data;
	dlc = cf->len;

	/* check flag whether this packet has to be looped back */
	अगर (skb->pkt_type != PACKET_LOOPBACK) अणु
		kमुक्त_skb(skb);
		वापस dlc;
	पूर्ण

	skb->protocol = htons(ETH_P_CAN);
	skb->pkt_type = PACKET_BROADCAST;
	skb->ip_summed = CHECKSUM_UNNECESSARY;
	skb->dev = mod->ndev;
	netअगर_receive_skb(skb);
	वापस dlc;
पूर्ण

/*
 * Compare an skb with an existing echo skb
 *
 * This function will be used on devices which have a hardware loopback.
 * On these devices, this function can be used to compare a received skb
 * with the saved echo skbs so that the hardware echo skb can be dropped.
 *
 * Returns true अगर the skb's are identical, false otherwise.
 */
अटल bool ican3_echo_skb_matches(काष्ठा ican3_dev *mod, काष्ठा sk_buff *skb)
अणु
	काष्ठा can_frame *cf = (काष्ठा can_frame *)skb->data;
	काष्ठा sk_buff *echo_skb = skb_peek(&mod->echoq);
	काष्ठा can_frame *echo_cf;

	अगर (!echo_skb)
		वापस false;

	echo_cf = (काष्ठा can_frame *)echo_skb->data;
	अगर (cf->can_id != echo_cf->can_id)
		वापस false;

	अगर (cf->len != echo_cf->len)
		वापस false;

	वापस स_भेद(cf->data, echo_cf->data, cf->len) == 0;
पूर्ण

/*
 * Check that there is room in the TX ring to transmit another skb
 *
 * LOCKING: must hold mod->lock
 */
अटल bool ican3_txok(काष्ठा ican3_dev *mod)
अणु
	काष्ठा ican3_fast_desc __iomem *desc;
	u8 control;

	/* check that we have echo queue space */
	अगर (skb_queue_len(&mod->echoq) >= ICAN3_TX_BUFFERS)
		वापस false;

	/* copy the control bits of the descriptor */
	ican3_set_page(mod, mod->fasttx_start + (mod->fasttx_num / 16));
	desc = mod->dpm + ((mod->fasttx_num % 16) * माप(*desc));
	control = ioपढ़ो8(&desc->control);

	/* अगर the control bits are not valid, then we have no more space */
	अगर (!(control & DESC_VALID))
		वापस false;

	वापस true;
पूर्ण

/*
 * Receive one CAN frame from the hardware
 *
 * CONTEXT: must be called from user context
 */
अटल पूर्णांक ican3_recv_skb(काष्ठा ican3_dev *mod)
अणु
	काष्ठा net_device *ndev = mod->ndev;
	काष्ठा net_device_stats *stats = &ndev->stats;
	काष्ठा ican3_fast_desc desc;
	व्योम __iomem *desc_addr;
	काष्ठा can_frame *cf;
	काष्ठा sk_buff *skb;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&mod->lock, flags);

	/* copy the whole descriptor */
	ican3_set_page(mod, mod->fastrx_start + (mod->fastrx_num / 16));
	desc_addr = mod->dpm + ((mod->fastrx_num % 16) * माप(desc));
	स_नकल_fromio(&desc, desc_addr, माप(desc));

	spin_unlock_irqrestore(&mod->lock, flags);

	/* check that we actually have a CAN frame */
	अगर (!(desc.control & DESC_VALID))
		वापस -ENOBUFS;

	/* allocate an skb */
	skb = alloc_can_skb(ndev, &cf);
	अगर (unlikely(skb == शून्य)) अणु
		stats->rx_dropped++;
		जाओ err_noalloc;
	पूर्ण

	/* convert the ICAN3 frame पूर्णांकo Linux CAN क्रमmat */
	ican3_to_can_frame(mod, &desc, cf);

	/*
	 * If this is an ECHO frame received from the hardware loopback
	 * feature, use the skb saved in the ECHO stack instead. This allows
	 * the Linux CAN core to support CAN_RAW_RECV_OWN_MSGS correctly.
	 *
	 * Since this is a confirmation of a successfully transmitted packet
	 * sent from this host, update the transmit statistics.
	 *
	 * Also, the netdevice queue needs to be allowed to send packets again.
	 */
	अगर (ican3_echo_skb_matches(mod, skb)) अणु
		stats->tx_packets++;
		stats->tx_bytes += ican3_get_echo_skb(mod);
		kमुक्त_skb(skb);
		जाओ err_noalloc;
	पूर्ण

	/* update statistics, receive the skb */
	stats->rx_packets++;
	stats->rx_bytes += cf->len;
	netअगर_receive_skb(skb);

err_noalloc:
	/* toggle the valid bit and वापस the descriptor to the ring */
	desc.control ^= DESC_VALID;

	spin_lock_irqsave(&mod->lock, flags);

	ican3_set_page(mod, mod->fastrx_start + (mod->fastrx_num / 16));
	स_नकल_toio(desc_addr, &desc, 1);

	/* update the next buffer poपूर्णांकer */
	mod->fastrx_num = (desc.control & DESC_WRAP) ? 0
						     : (mod->fastrx_num + 1);

	/* there are still more buffers to process */
	spin_unlock_irqrestore(&mod->lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक ican3_napi(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा ican3_dev *mod = container_of(napi, काष्ठा ican3_dev, napi);
	अचिन्हित दीर्घ flags;
	पूर्णांक received = 0;
	पूर्णांक ret;

	/* process all communication messages */
	जबतक (true) अणु
		काष्ठा ican3_msg msg;
		ret = ican3_recv_msg(mod, &msg);
		अगर (ret)
			अवरोध;

		ican3_handle_message(mod, &msg);
	पूर्ण

	/* process all CAN frames from the fast पूर्णांकerface */
	जबतक (received < budget) अणु
		ret = ican3_recv_skb(mod);
		अगर (ret)
			अवरोध;

		received++;
	पूर्ण

	/* We have processed all packets that the adapter had, but it
	 * was less than our budget, stop polling */
	अगर (received < budget)
		napi_complete_करोne(napi, received);

	spin_lock_irqsave(&mod->lock, flags);

	/* Wake up the transmit queue अगर necessary */
	अगर (netअगर_queue_stopped(mod->ndev) && ican3_txok(mod))
		netअगर_wake_queue(mod->ndev);

	spin_unlock_irqrestore(&mod->lock, flags);

	/* re-enable पूर्णांकerrupt generation */
	ioग_लिखो8(1 << mod->num, &mod->ctrl->पूर्णांक_enable);
	वापस received;
पूर्ण

अटल irqवापस_t ican3_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा ican3_dev *mod = dev_id;
	u8 stat;

	/*
	 * The पूर्णांकerrupt status रेजिस्टर on this device reports पूर्णांकerrupts
	 * as zeroes instead of using ones like most other devices
	 */
	stat = ioपढ़ो8(&mod->ctrl->पूर्णांक_disable) & (1 << mod->num);
	अगर (stat == (1 << mod->num))
		वापस IRQ_NONE;

	/* clear the MODULbus पूर्णांकerrupt from the microcontroller */
	ioपढ़ो8(&mod->dpmctrl->पूर्णांकerrupt);

	/* disable पूर्णांकerrupt generation, schedule the NAPI poller */
	ioग_लिखो8(1 << mod->num, &mod->ctrl->पूर्णांक_disable);
	napi_schedule(&mod->napi);
	वापस IRQ_HANDLED;
पूर्ण

/*
 * Firmware reset, startup, and shutकरोwn
 */

/*
 * Reset an ICAN module to its घातer-on state
 *
 * CONTEXT: no network device रेजिस्टरed
 */
अटल पूर्णांक ican3_reset_module(काष्ठा ican3_dev *mod)
अणु
	अचिन्हित दीर्घ start;
	u8 runold, runnew;

	/* disable पूर्णांकerrupts so no more work is scheduled */
	ioग_लिखो8(1 << mod->num, &mod->ctrl->पूर्णांक_disable);

	/* the first unallocated page in the DPM is #9 */
	mod->मुक्त_page = DPM_FREE_START;

	ican3_set_page(mod, QUEUE_OLD_CONTROL);
	runold = ioपढ़ो8(mod->dpm + TARGET_RUNNING);

	/* reset the module */
	ioग_लिखो8(0x00, &mod->dpmctrl->hwreset);

	/* रुको until the module has finished resetting and is running */
	start = jअगरfies;
	करो अणु
		ican3_set_page(mod, QUEUE_OLD_CONTROL);
		runnew = ioपढ़ो8(mod->dpm + TARGET_RUNNING);
		अगर (runnew == (runold ^ 0xff))
			वापस 0;

		msleep(10);
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, start + HZ / 2));

	netdev_err(mod->ndev, "failed to reset CAN module\n");
	वापस -ETIMEDOUT;
पूर्ण

अटल व्योम ican3_shutकरोwn_module(काष्ठा ican3_dev *mod)
अणु
	ican3_msg_disconnect(mod);
	ican3_reset_module(mod);
पूर्ण

/*
 * Startup an ICAN module, bringing it पूर्णांकo fast mode
 */
अटल पूर्णांक ican3_startup_module(काष्ठा ican3_dev *mod)
अणु
	पूर्णांक ret;

	ret = ican3_reset_module(mod);
	अगर (ret) अणु
		netdev_err(mod->ndev, "unable to reset module\n");
		वापस ret;
	पूर्ण

	/* detect firmware */
	स_नकल_fromio(mod->fwinfo, mod->dpm + FIRMWARE_STAMP, माप(mod->fwinfo) - 1);
	अगर (म_भेदन(mod->fwinfo, "JANZ-ICAN3", 10)) अणु
		netdev_err(mod->ndev, "ICAN3 not detected (found %s)\n", mod->fwinfo);
		वापस -ENODEV;
	पूर्ण
	अगर (म_माला(mod->fwinfo, "CAL/CANopen"))
		mod->fwtype = ICAN3_FWTYPE_CAL_CANOPEN;
	अन्यथा
		mod->fwtype = ICAN3_FWTYPE_ICANOS;

	/* re-enable पूर्णांकerrupts so we can send messages */
	ioग_लिखो8(1 << mod->num, &mod->ctrl->पूर्णांक_enable);

	ret = ican3_msg_connect(mod);
	अगर (ret) अणु
		netdev_err(mod->ndev, "unable to connect to module\n");
		वापस ret;
	पूर्ण

	ican3_init_new_host_पूर्णांकerface(mod);
	ret = ican3_msg_newhostअगर(mod);
	अगर (ret) अणु
		netdev_err(mod->ndev, "unable to switch to new-style interface\n");
		वापस ret;
	पूर्ण

	/* शेष to "termination on" */
	ret = ican3_set_termination(mod, true);
	अगर (ret) अणु
		netdev_err(mod->ndev, "unable to enable termination\n");
		वापस ret;
	पूर्ण

	/* शेष to "bus errors enabled" */
	ret = ican3_set_buserror(mod, 1);
	अगर (ret) अणु
		netdev_err(mod->ndev, "unable to set bus-error\n");
		वापस ret;
	पूर्ण

	ican3_init_fast_host_पूर्णांकerface(mod);
	ret = ican3_msg_fasthostअगर(mod);
	अगर (ret) अणु
		netdev_err(mod->ndev, "unable to switch to fast host interface\n");
		वापस ret;
	पूर्ण

	ret = ican3_set_id_filter(mod, true);
	अगर (ret) अणु
		netdev_err(mod->ndev, "unable to set acceptance filter\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * CAN Network Device
 */

अटल पूर्णांक ican3_खोलो(काष्ठा net_device *ndev)
अणु
	काष्ठा ican3_dev *mod = netdev_priv(ndev);
	पूर्णांक ret;

	/* खोलो the CAN layer */
	ret = खोलो_candev(ndev);
	अगर (ret) अणु
		netdev_err(mod->ndev, "unable to start CAN layer\n");
		वापस ret;
	पूर्ण

	/* bring the bus online */
	ret = ican3_set_bus_state(mod, true);
	अगर (ret) अणु
		netdev_err(mod->ndev, "unable to set bus-on\n");
		बंद_candev(ndev);
		वापस ret;
	पूर्ण

	/* start up the network device */
	mod->can.state = CAN_STATE_ERROR_ACTIVE;
	netअगर_start_queue(ndev);

	वापस 0;
पूर्ण

अटल पूर्णांक ican3_stop(काष्ठा net_device *ndev)
अणु
	काष्ठा ican3_dev *mod = netdev_priv(ndev);
	पूर्णांक ret;

	/* stop the network device xmit routine */
	netअगर_stop_queue(ndev);
	mod->can.state = CAN_STATE_STOPPED;

	/* bring the bus offline, stop receiving packets */
	ret = ican3_set_bus_state(mod, false);
	अगर (ret) अणु
		netdev_err(mod->ndev, "unable to set bus-off\n");
		वापस ret;
	पूर्ण

	/* drop all outstanding echo skbs */
	skb_queue_purge(&mod->echoq);

	/* बंद the CAN layer */
	बंद_candev(ndev);
	वापस 0;
पूर्ण

अटल netdev_tx_t ican3_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *ndev)
अणु
	काष्ठा ican3_dev *mod = netdev_priv(ndev);
	काष्ठा can_frame *cf = (काष्ठा can_frame *)skb->data;
	काष्ठा ican3_fast_desc desc;
	व्योम __iomem *desc_addr;
	अचिन्हित दीर्घ flags;

	अगर (can_dropped_invalid_skb(ndev, skb))
		वापस NETDEV_TX_OK;

	spin_lock_irqsave(&mod->lock, flags);

	/* check that we can actually transmit */
	अगर (!ican3_txok(mod)) अणु
		netdev_err(mod->ndev, "BUG: no free descriptors\n");
		spin_unlock_irqrestore(&mod->lock, flags);
		वापस NETDEV_TX_BUSY;
	पूर्ण

	/* copy the control bits of the descriptor */
	ican3_set_page(mod, mod->fasttx_start + (mod->fasttx_num / 16));
	desc_addr = mod->dpm + ((mod->fasttx_num % 16) * माप(desc));
	स_रखो(&desc, 0, माप(desc));
	स_नकल_fromio(&desc, desc_addr, 1);

	/* convert the Linux CAN frame पूर्णांकo ICAN3 क्रमmat */
	can_frame_to_ican3(mod, cf, &desc);

	/*
	 * This hardware करोesn't have TX-done notifications, so we'll try and
	 * emulate it the best we can using ECHO skbs. Add the skb to the ECHO
	 * stack. Upon packet reception, check अगर the ECHO skb and received
	 * skb match, and use that to wake the queue.
	 */
	ican3_put_echo_skb(mod, skb);

	/*
	 * the programming manual says that you must set the IVALID bit, then
	 * पूर्णांकerrupt, then set the valid bit. Quite weird, but it seems to be
	 * required क्रम this to work
	 */
	desc.control |= DESC_IVALID;
	स_नकल_toio(desc_addr, &desc, माप(desc));

	/* generate a MODULbus पूर्णांकerrupt to the microcontroller */
	ioग_लिखो8(0x01, &mod->dpmctrl->पूर्णांकerrupt);

	desc.control ^= DESC_VALID;
	स_नकल_toio(desc_addr, &desc, माप(desc));

	/* update the next buffer poपूर्णांकer */
	mod->fasttx_num = (desc.control & DESC_WRAP) ? 0
						     : (mod->fasttx_num + 1);

	/* अगर there is no मुक्त descriptor space, stop the transmit queue */
	अगर (!ican3_txok(mod))
		netअगर_stop_queue(ndev);

	spin_unlock_irqrestore(&mod->lock, flags);
	वापस NETDEV_TX_OK;
पूर्ण

अटल स्थिर काष्ठा net_device_ops ican3_netdev_ops = अणु
	.nकरो_खोलो	= ican3_खोलो,
	.nकरो_stop	= ican3_stop,
	.nकरो_start_xmit	= ican3_xmit,
	.nकरो_change_mtu = can_change_mtu,
पूर्ण;

/*
 * Low-level CAN Device
 */

/* This काष्ठाure was stolen from drivers/net/can/sja1000/sja1000.c */
अटल स्थिर काष्ठा can_bittiming_स्थिर ican3_bittiming_स्थिर = अणु
	.name = DRV_NAME,
	.tseg1_min = 1,
	.tseg1_max = 16,
	.tseg2_min = 1,
	.tseg2_max = 8,
	.sjw_max = 4,
	.brp_min = 1,
	.brp_max = 64,
	.brp_inc = 1,
पूर्ण;

अटल पूर्णांक ican3_set_mode(काष्ठा net_device *ndev, क्रमागत can_mode mode)
अणु
	काष्ठा ican3_dev *mod = netdev_priv(ndev);
	पूर्णांक ret;

	अगर (mode != CAN_MODE_START)
		वापस -ENOTSUPP;

	/* bring the bus online */
	ret = ican3_set_bus_state(mod, true);
	अगर (ret) अणु
		netdev_err(ndev, "unable to set bus-on\n");
		वापस ret;
	पूर्ण

	/* start up the network device */
	mod->can.state = CAN_STATE_ERROR_ACTIVE;

	अगर (netअगर_queue_stopped(ndev))
		netअगर_wake_queue(ndev);

	वापस 0;
पूर्ण

अटल पूर्णांक ican3_get_berr_counter(स्थिर काष्ठा net_device *ndev,
				  काष्ठा can_berr_counter *bec)
अणु
	काष्ठा ican3_dev *mod = netdev_priv(ndev);
	पूर्णांक ret;

	ret = ican3_send_inquiry(mod, INQUIRY_STATUS);
	अगर (ret)
		वापस ret;

	अगर (!रुको_क्रम_completion_समयout(&mod->buserror_comp, HZ)) अणु
		netdev_info(mod->ndev, "%s timed out\n", __func__);
		वापस -ETIMEDOUT;
	पूर्ण

	bec->rxerr = mod->bec.rxerr;
	bec->txerr = mod->bec.txerr;
	वापस 0;
पूर्ण

/*
 * Sysfs Attributes
 */

अटल sमाप_प्रकार ican3_sysfs_show_term(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     अक्षर *buf)
अणु
	काष्ठा ican3_dev *mod = netdev_priv(to_net_dev(dev));
	पूर्णांक ret;

	ret = ican3_send_inquiry(mod, INQUIRY_TERMINATION);
	अगर (ret)
		वापस ret;

	अगर (!रुको_क्रम_completion_समयout(&mod->termination_comp, HZ)) अणु
		netdev_info(mod->ndev, "%s timed out\n", __func__);
		वापस -ETIMEDOUT;
	पूर्ण

	वापस snम_लिखो(buf, PAGE_SIZE, "%u\n", mod->termination_enabled);
पूर्ण

अटल sमाप_प्रकार ican3_sysfs_set_term(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा ican3_dev *mod = netdev_priv(to_net_dev(dev));
	अचिन्हित दीर्घ enable;
	पूर्णांक ret;

	अगर (kम_से_अदीर्घ(buf, 0, &enable))
		वापस -EINVAL;

	ret = ican3_set_termination(mod, enable);
	अगर (ret)
		वापस ret;

	वापस count;
पूर्ण

अटल sमाप_प्रकार ican3_sysfs_show_fwinfo(काष्ठा device *dev,
				       काष्ठा device_attribute *attr,
				       अक्षर *buf)
अणु
	काष्ठा ican3_dev *mod = netdev_priv(to_net_dev(dev));

	वापस scnम_लिखो(buf, PAGE_SIZE, "%s\n", mod->fwinfo);
पूर्ण

अटल DEVICE_ATTR(termination, 0644, ican3_sysfs_show_term,
		   ican3_sysfs_set_term);
अटल DEVICE_ATTR(fwinfo, 0444, ican3_sysfs_show_fwinfo, शून्य);

अटल काष्ठा attribute *ican3_sysfs_attrs[] = अणु
	&dev_attr_termination.attr,
	&dev_attr_fwinfo.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group ican3_sysfs_attr_group = अणु
	.attrs = ican3_sysfs_attrs,
पूर्ण;

/*
 * PCI Subप्रणाली
 */

अटल पूर्णांक ican3_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा janz_platक्रमm_data *pdata;
	काष्ठा net_device *ndev;
	काष्ठा ican3_dev *mod;
	काष्ठा resource *res;
	काष्ठा device *dev;
	पूर्णांक ret;

	pdata = dev_get_platdata(&pdev->dev);
	अगर (!pdata)
		वापस -ENXIO;

	dev_dbg(&pdev->dev, "probe: module number %d\n", pdata->modno);

	/* save the काष्ठा device क्रम prपूर्णांकing */
	dev = &pdev->dev;

	/* allocate the CAN device and निजी data */
	ndev = alloc_candev(माप(*mod), 0);
	अगर (!ndev) अणु
		dev_err(dev, "unable to allocate CANdev\n");
		ret = -ENOMEM;
		जाओ out_वापस;
	पूर्ण

	platक्रमm_set_drvdata(pdev, ndev);
	mod = netdev_priv(ndev);
	mod->ndev = ndev;
	mod->num = pdata->modno;
	netअगर_napi_add(ndev, &mod->napi, ican3_napi, ICAN3_RX_BUFFERS);
	skb_queue_head_init(&mod->echoq);
	spin_lock_init(&mod->lock);
	init_completion(&mod->termination_comp);
	init_completion(&mod->buserror_comp);

	/* setup device-specअगरic sysfs attributes */
	ndev->sysfs_groups[0] = &ican3_sysfs_attr_group;

	/* the first unallocated page in the DPM is 9 */
	mod->मुक्त_page = DPM_FREE_START;

	ndev->netdev_ops = &ican3_netdev_ops;
	ndev->flags |= IFF_ECHO;
	SET_NETDEV_DEV(ndev, &pdev->dev);

	mod->can.घड़ी.freq = ICAN3_CAN_CLOCK;
	mod->can.bittiming_स्थिर = &ican3_bittiming_स्थिर;
	mod->can.करो_set_mode = ican3_set_mode;
	mod->can.करो_get_berr_counter = ican3_get_berr_counter;
	mod->can.ctrlmode_supported = CAN_CTRLMODE_3_SAMPLES
				    | CAN_CTRLMODE_BERR_REPORTING
				    | CAN_CTRLMODE_ONE_SHOT;

	/* find our IRQ number */
	mod->irq = platक्रमm_get_irq(pdev, 0);
	अगर (mod->irq < 0) अणु
		ret = -ENODEV;
		जाओ out_मुक्त_ndev;
	पूर्ण

	ndev->irq = mod->irq;

	/* get access to the MODULbus रेजिस्टरs क्रम this module */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res) अणु
		dev_err(dev, "MODULbus registers not found\n");
		ret = -ENODEV;
		जाओ out_मुक्त_ndev;
	पूर्ण

	mod->dpm = ioremap(res->start, resource_size(res));
	अगर (!mod->dpm) अणु
		dev_err(dev, "MODULbus registers not ioremap\n");
		ret = -ENOMEM;
		जाओ out_मुक्त_ndev;
	पूर्ण

	mod->dpmctrl = mod->dpm + DPM_PAGE_SIZE;

	/* get access to the control रेजिस्टरs क्रम this module */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
	अगर (!res) अणु
		dev_err(dev, "CONTROL registers not found\n");
		ret = -ENODEV;
		जाओ out_iounmap_dpm;
	पूर्ण

	mod->ctrl = ioremap(res->start, resource_size(res));
	अगर (!mod->ctrl) अणु
		dev_err(dev, "CONTROL registers not ioremap\n");
		ret = -ENOMEM;
		जाओ out_iounmap_dpm;
	पूर्ण

	/* disable our IRQ, then hookup the IRQ handler */
	ioग_लिखो8(1 << mod->num, &mod->ctrl->पूर्णांक_disable);
	ret = request_irq(mod->irq, ican3_irq, IRQF_SHARED, DRV_NAME, mod);
	अगर (ret) अणु
		dev_err(dev, "unable to request IRQ\n");
		जाओ out_iounmap_ctrl;
	पूर्ण

	/* reset and initialize the CAN controller पूर्णांकo fast mode */
	napi_enable(&mod->napi);
	ret = ican3_startup_module(mod);
	अगर (ret) अणु
		dev_err(dev, "%s: unable to start CANdev\n", __func__);
		जाओ out_मुक्त_irq;
	पूर्ण

	/* रेजिस्टर with the Linux CAN layer */
	ret = रेजिस्टर_candev(ndev);
	अगर (ret) अणु
		dev_err(dev, "%s: unable to register CANdev\n", __func__);
		जाओ out_मुक्त_irq;
	पूर्ण

	netdev_info(mod->ndev, "module %d: registered CAN device\n", pdata->modno);
	वापस 0;

out_मुक्त_irq:
	napi_disable(&mod->napi);
	ioग_लिखो8(1 << mod->num, &mod->ctrl->पूर्णांक_disable);
	मुक्त_irq(mod->irq, mod);
out_iounmap_ctrl:
	iounmap(mod->ctrl);
out_iounmap_dpm:
	iounmap(mod->dpm);
out_मुक्त_ndev:
	मुक्त_candev(ndev);
out_वापस:
	वापस ret;
पूर्ण

अटल पूर्णांक ican3_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *ndev = platक्रमm_get_drvdata(pdev);
	काष्ठा ican3_dev *mod = netdev_priv(ndev);

	/* unरेजिस्टर the netdevice, stop पूर्णांकerrupts */
	unरेजिस्टर_netdev(ndev);
	napi_disable(&mod->napi);
	ioग_लिखो8(1 << mod->num, &mod->ctrl->पूर्णांक_disable);
	मुक्त_irq(mod->irq, mod);

	/* put the module पूर्णांकo reset */
	ican3_shutकरोwn_module(mod);

	/* unmap all रेजिस्टरs */
	iounmap(mod->ctrl);
	iounmap(mod->dpm);

	मुक्त_candev(ndev);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver ican3_driver = अणु
	.driver		= अणु
		.name	= DRV_NAME,
	पूर्ण,
	.probe		= ican3_probe,
	.हटाओ		= ican3_हटाओ,
पूर्ण;

module_platक्रमm_driver(ican3_driver);

MODULE_AUTHOR("Ira W. Snyder <iws@ovro.caltech.edu>");
MODULE_DESCRIPTION("Janz MODULbus VMOD-ICAN3 Driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:janz-ican3");
