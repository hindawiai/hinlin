<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम the NXP ISP1760 chip
 *
 * However, the code might contain some bugs. What करोesn't work क्रम sure is:
 * - ISO
 * - OTG
 e The पूर्णांकerrupt line is configured as active low, level.
 *
 * (c) 2007 Sebastian Siewior <bigeasy@linutronix.de>
 *
 * (c) 2011 Arvid Brodin <arvid.brodin@enea.com>
 *
 */
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/list.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/hcd.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/mm.h>
#समावेश <linux/समयr.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <यंत्र/cacheflush.h>

#समावेश "isp1760-core.h"
#समावेश "isp1760-hcd.h"
#समावेश "isp1760-regs.h"

अटल काष्ठा kmem_cache *qtd_cachep;
अटल काष्ठा kmem_cache *qh_cachep;
अटल काष्ठा kmem_cache *urb_listitem_cachep;

प्रकार व्योम (packet_enqueue)(काष्ठा usb_hcd *hcd, काष्ठा isp1760_qh *qh,
		काष्ठा isp1760_qtd *qtd);

अटल अंतरभूत काष्ठा isp1760_hcd *hcd_to_priv(काष्ठा usb_hcd *hcd)
अणु
	वापस *(काष्ठा isp1760_hcd **)hcd->hcd_priv;
पूर्ण

/* urb state*/
#घोषणा DELETE_URB		(0x0008)
#घोषणा NO_TRANSFER_ACTIVE	(0xffffffff)

/* Philips Proprietary Transfer Descriptor (PTD) */
प्रकार __u32 __bitwise __dw;
काष्ठा ptd अणु
	__dw dw0;
	__dw dw1;
	__dw dw2;
	__dw dw3;
	__dw dw4;
	__dw dw5;
	__dw dw6;
	__dw dw7;
पूर्ण;
#घोषणा PTD_OFFSET		0x0400
#घोषणा ISO_PTD_OFFSET		0x0400
#घोषणा INT_PTD_OFFSET		0x0800
#घोषणा ATL_PTD_OFFSET		0x0c00
#घोषणा PAYLOAD_OFFSET		0x1000


/* ATL */
/* DW0 */
#घोषणा DW0_VALID_BIT			1
#घोषणा FROM_DW0_VALID(x)		((x) & 0x01)
#घोषणा TO_DW0_LENGTH(x)		(((u32) x) << 3)
#घोषणा TO_DW0_MAXPACKET(x)		(((u32) x) << 18)
#घोषणा TO_DW0_MULTI(x)			(((u32) x) << 29)
#घोषणा TO_DW0_ENDPOINT(x)		(((u32)	x) << 31)
/* DW1 */
#घोषणा TO_DW1_DEVICE_ADDR(x)		(((u32) x) << 3)
#घोषणा TO_DW1_PID_TOKEN(x)		(((u32) x) << 10)
#घोषणा DW1_TRANS_BULK			((u32) 2 << 12)
#घोषणा DW1_TRANS_INT			((u32) 3 << 12)
#घोषणा DW1_TRANS_SPLIT			((u32) 1 << 14)
#घोषणा DW1_SE_USB_LOSPEED		((u32) 2 << 16)
#घोषणा TO_DW1_PORT_NUM(x)		(((u32) x) << 18)
#घोषणा TO_DW1_HUB_NUM(x)		(((u32) x) << 25)
/* DW2 */
#घोषणा TO_DW2_DATA_START_ADDR(x)	(((u32) x) << 8)
#घोषणा TO_DW2_RL(x)			((x) << 25)
#घोषणा FROM_DW2_RL(x)			(((x) >> 25) & 0xf)
/* DW3 */
#घोषणा FROM_DW3_NRBYTESTRANSFERRED(x)		((x) & 0x7fff)
#घोषणा FROM_DW3_SCS_NRBYTESTRANSFERRED(x)	((x) & 0x07ff)
#घोषणा TO_DW3_NAKCOUNT(x)		((x) << 19)
#घोषणा FROM_DW3_NAKCOUNT(x)		(((x) >> 19) & 0xf)
#घोषणा TO_DW3_CERR(x)			((x) << 23)
#घोषणा FROM_DW3_CERR(x)		(((x) >> 23) & 0x3)
#घोषणा TO_DW3_DATA_TOGGLE(x)		((x) << 25)
#घोषणा FROM_DW3_DATA_TOGGLE(x)		(((x) >> 25) & 0x1)
#घोषणा TO_DW3_PING(x)			((x) << 26)
#घोषणा FROM_DW3_PING(x)		(((x) >> 26) & 0x1)
#घोषणा DW3_ERROR_BIT			(1 << 28)
#घोषणा DW3_BABBLE_BIT			(1 << 29)
#घोषणा DW3_HALT_BIT			(1 << 30)
#घोषणा DW3_ACTIVE_BIT			(1 << 31)
#घोषणा FROM_DW3_ACTIVE(x)		(((x) >> 31) & 0x01)

#घोषणा INT_UNDERRUN			(1 << 2)
#घोषणा INT_BABBLE			(1 << 1)
#घोषणा INT_EXACT			(1 << 0)

#घोषणा SETUP_PID	(2)
#घोषणा IN_PID		(1)
#घोषणा OUT_PID		(0)

/* Errata 1 */
#घोषणा RL_COUNTER	(0)
#घोषणा NAK_COUNTER	(0)
#घोषणा ERR_COUNTER	(2)

काष्ठा isp1760_qtd अणु
	u8 packet_type;
	व्योम *data_buffer;
	u32 payload_addr;

	/* the rest is HCD-निजी */
	काष्ठा list_head qtd_list;
	काष्ठा urb *urb;
	माप_प्रकार length;
	माप_प्रकार actual_length;

	/* QTD_ENQUEUED:	रुकोing क्रम transfer (inactive) */
	/* QTD_PAYLOAD_ALLOC:	chip mem has been allocated क्रम payload */
	/* QTD_XFER_STARTED:	valid ptd has been written to isp176x - only
				पूर्णांकerrupt handler may touch this qtd! */
	/* QTD_XFER_COMPLETE:	payload has been transferred successfully */
	/* QTD_RETIRE:		transfer error/पात qtd */
#घोषणा QTD_ENQUEUED		0
#घोषणा QTD_PAYLOAD_ALLOC	1
#घोषणा QTD_XFER_STARTED	2
#घोषणा QTD_XFER_COMPLETE	3
#घोषणा QTD_RETIRE		4
	u32 status;
पूर्ण;

/* Queue head, one क्रम each active endpoपूर्णांक */
काष्ठा isp1760_qh अणु
	काष्ठा list_head qh_list;
	काष्ठा list_head qtd_list;
	u32 toggle;
	u32 ping;
	पूर्णांक slot;
	पूर्णांक tt_buffer_dirty;	/* See USB2.0 spec section 11.17.5 */
पूर्ण;

काष्ठा urb_listitem अणु
	काष्ठा list_head urb_list;
	काष्ठा urb *urb;
पूर्ण;

/*
 * Access functions क्रम isp176x रेजिस्टरs (addresses 0..0x03FF).
 */
अटल u32 reg_पढ़ो32(व्योम __iomem *base, u32 reg)
अणु
	वापस isp1760_पढ़ो32(base, reg);
पूर्ण

अटल व्योम reg_ग_लिखो32(व्योम __iomem *base, u32 reg, u32 val)
अणु
	isp1760_ग_लिखो32(base, reg, val);
पूर्ण

/*
 * Access functions क्रम isp176x memory (offset >= 0x0400).
 *
 * bank_पढ़ोs8() पढ़ोs memory locations prefetched by an earlier ग_लिखो to
 * HC_MEMORY_REG (see isp176x datasheet). Unless you want to करो fancy multi-
 * bank optimizations, you should use the more generic mem_पढ़ोs8() below.
 *
 * For access to ptd memory, use the specialized ptd_पढ़ो() and ptd_ग_लिखो()
 * below.
 *
 * These functions copy via MMIO data to/from the device. स_नकल_अणुto|fromपूर्णio()
 * करोesn't quite work because some people have to enक्रमce 32-bit access
 */
अटल व्योम bank_पढ़ोs8(व्योम __iomem *src_base, u32 src_offset, u32 bank_addr,
							__u32 *dst, u32 bytes)
अणु
	__u32 __iomem *src;
	u32 val;
	__u8 *src_byteptr;
	__u8 *dst_byteptr;

	src = src_base + (bank_addr | src_offset);

	अगर (src_offset < PAYLOAD_OFFSET) अणु
		जबतक (bytes >= 4) अणु
			*dst = le32_to_cpu(__raw_पढ़ोl(src));
			bytes -= 4;
			src++;
			dst++;
		पूर्ण
	पूर्ण अन्यथा अणु
		जबतक (bytes >= 4) अणु
			*dst = __raw_पढ़ोl(src);
			bytes -= 4;
			src++;
			dst++;
		पूर्ण
	पूर्ण

	अगर (!bytes)
		वापस;

	/* in हाल we have 3, 2 or 1 by left. The dst buffer may not be fully
	 * allocated.
	 */
	अगर (src_offset < PAYLOAD_OFFSET)
		val = le32_to_cpu(__raw_पढ़ोl(src));
	अन्यथा
		val = __raw_पढ़ोl(src);

	dst_byteptr = (व्योम *) dst;
	src_byteptr = (व्योम *) &val;
	जबतक (bytes > 0) अणु
		*dst_byteptr = *src_byteptr;
		dst_byteptr++;
		src_byteptr++;
		bytes--;
	पूर्ण
पूर्ण

अटल व्योम mem_पढ़ोs8(व्योम __iomem *src_base, u32 src_offset, व्योम *dst,
								u32 bytes)
अणु
	reg_ग_लिखो32(src_base, HC_MEMORY_REG, src_offset + ISP_BANK(0));
	ndelay(90);
	bank_पढ़ोs8(src_base, src_offset, ISP_BANK(0), dst, bytes);
पूर्ण

अटल व्योम mem_ग_लिखोs8(व्योम __iomem *dst_base, u32 dst_offset,
						__u32 स्थिर *src, u32 bytes)
अणु
	__u32 __iomem *dst;

	dst = dst_base + dst_offset;

	अगर (dst_offset < PAYLOAD_OFFSET) अणु
		जबतक (bytes >= 4) अणु
			__raw_ग_लिखोl(cpu_to_le32(*src), dst);
			bytes -= 4;
			src++;
			dst++;
		पूर्ण
	पूर्ण अन्यथा अणु
		जबतक (bytes >= 4) अणु
			__raw_ग_लिखोl(*src, dst);
			bytes -= 4;
			src++;
			dst++;
		पूर्ण
	पूर्ण

	अगर (!bytes)
		वापस;
	/* in हाल we have 3, 2 or 1 bytes left. The buffer is allocated and the
	 * extra bytes should not be पढ़ो by the HW.
	 */

	अगर (dst_offset < PAYLOAD_OFFSET)
		__raw_ग_लिखोl(cpu_to_le32(*src), dst);
	अन्यथा
		__raw_ग_लिखोl(*src, dst);
पूर्ण

/*
 * Read and ग_लिखो ptds. 'ptd_offset' should be one of ISO_PTD_OFFSET,
 * INT_PTD_OFFSET, and ATL_PTD_OFFSET. 'slot' should be less than 32.
 */
अटल व्योम ptd_पढ़ो(व्योम __iomem *base, u32 ptd_offset, u32 slot,
								काष्ठा ptd *ptd)
अणु
	reg_ग_लिखो32(base, HC_MEMORY_REG,
				ISP_BANK(0) + ptd_offset + slot*माप(*ptd));
	ndelay(90);
	bank_पढ़ोs8(base, ptd_offset + slot*माप(*ptd), ISP_BANK(0),
						(व्योम *) ptd, माप(*ptd));
पूर्ण

अटल व्योम ptd_ग_लिखो(व्योम __iomem *base, u32 ptd_offset, u32 slot,
								काष्ठा ptd *ptd)
अणु
	mem_ग_लिखोs8(base, ptd_offset + slot*माप(*ptd) + माप(ptd->dw0),
						&ptd->dw1, 7*माप(ptd->dw1));
	/* Make sure dw0 माला_लो written last (after other dw's and after payload)
	   since it contains the enable bit */
	wmb();
	mem_ग_लिखोs8(base, ptd_offset + slot*माप(*ptd), &ptd->dw0,
							माप(ptd->dw0));
पूर्ण


/* memory management of the 60kb on the chip from 0x1000 to 0xffff */
अटल व्योम init_memory(काष्ठा isp1760_hcd *priv)
अणु
	पूर्णांक i, curr;
	u32 payload_addr;

	payload_addr = PAYLOAD_OFFSET;
	क्रम (i = 0; i < BLOCK_1_NUM; i++) अणु
		priv->memory_pool[i].start = payload_addr;
		priv->memory_pool[i].size = BLOCK_1_SIZE;
		priv->memory_pool[i].मुक्त = 1;
		payload_addr += priv->memory_pool[i].size;
	पूर्ण

	curr = i;
	क्रम (i = 0; i < BLOCK_2_NUM; i++) अणु
		priv->memory_pool[curr + i].start = payload_addr;
		priv->memory_pool[curr + i].size = BLOCK_2_SIZE;
		priv->memory_pool[curr + i].मुक्त = 1;
		payload_addr += priv->memory_pool[curr + i].size;
	पूर्ण

	curr = i;
	क्रम (i = 0; i < BLOCK_3_NUM; i++) अणु
		priv->memory_pool[curr + i].start = payload_addr;
		priv->memory_pool[curr + i].size = BLOCK_3_SIZE;
		priv->memory_pool[curr + i].मुक्त = 1;
		payload_addr += priv->memory_pool[curr + i].size;
	पूर्ण

	WARN_ON(payload_addr - priv->memory_pool[0].start > PAYLOAD_AREA_SIZE);
पूर्ण

अटल व्योम alloc_mem(काष्ठा usb_hcd *hcd, काष्ठा isp1760_qtd *qtd)
अणु
	काष्ठा isp1760_hcd *priv = hcd_to_priv(hcd);
	पूर्णांक i;

	WARN_ON(qtd->payload_addr);

	अगर (!qtd->length)
		वापस;

	क्रम (i = 0; i < BLOCKS; i++) अणु
		अगर (priv->memory_pool[i].size >= qtd->length &&
				priv->memory_pool[i].मुक्त) अणु
			priv->memory_pool[i].मुक्त = 0;
			qtd->payload_addr = priv->memory_pool[i].start;
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम मुक्त_mem(काष्ठा usb_hcd *hcd, काष्ठा isp1760_qtd *qtd)
अणु
	काष्ठा isp1760_hcd *priv = hcd_to_priv(hcd);
	पूर्णांक i;

	अगर (!qtd->payload_addr)
		वापस;

	क्रम (i = 0; i < BLOCKS; i++) अणु
		अगर (priv->memory_pool[i].start == qtd->payload_addr) अणु
			WARN_ON(priv->memory_pool[i].मुक्त);
			priv->memory_pool[i].मुक्त = 1;
			qtd->payload_addr = 0;
			वापस;
		पूर्ण
	पूर्ण

	dev_err(hcd->self.controller, "%s: Invalid pointer: %08x\n",
						__func__, qtd->payload_addr);
	WARN_ON(1);
	qtd->payload_addr = 0;
पूर्ण

अटल पूर्णांक handshake(काष्ठा usb_hcd *hcd, u32 reg,
		      u32 mask, u32 करोne, पूर्णांक usec)
अणु
	u32 result;
	पूर्णांक ret;

	ret = पढ़ोl_poll_समयout_atomic(hcd->regs + reg, result,
					((result & mask) == करोne ||
					 result == U32_MAX), 1, usec);
	अगर (result == U32_MAX)
		वापस -ENODEV;

	वापस ret;
पूर्ण

/* reset a non-running (STS_HALT == 1) controller */
अटल पूर्णांक ehci_reset(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा isp1760_hcd *priv = hcd_to_priv(hcd);

	u32 command = reg_पढ़ो32(hcd->regs, HC_USBCMD);

	command |= CMD_RESET;
	reg_ग_लिखो32(hcd->regs, HC_USBCMD, command);
	hcd->state = HC_STATE_HALT;
	priv->next_statechange = jअगरfies;

	वापस handshake(hcd, HC_USBCMD, CMD_RESET, 0, 250 * 1000);
पूर्ण

अटल काष्ठा isp1760_qh *qh_alloc(gfp_t flags)
अणु
	काष्ठा isp1760_qh *qh;

	qh = kmem_cache_zalloc(qh_cachep, flags);
	अगर (!qh)
		वापस शून्य;

	INIT_LIST_HEAD(&qh->qh_list);
	INIT_LIST_HEAD(&qh->qtd_list);
	qh->slot = -1;

	वापस qh;
पूर्ण

अटल व्योम qh_मुक्त(काष्ठा isp1760_qh *qh)
अणु
	WARN_ON(!list_empty(&qh->qtd_list));
	WARN_ON(qh->slot > -1);
	kmem_cache_मुक्त(qh_cachep, qh);
पूर्ण

/* one-समय init, only क्रम memory state */
अटल पूर्णांक priv_init(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा isp1760_hcd		*priv = hcd_to_priv(hcd);
	u32			hcc_params;
	पूर्णांक i;

	spin_lock_init(&priv->lock);

	क्रम (i = 0; i < QH_END; i++)
		INIT_LIST_HEAD(&priv->qh_list[i]);

	/*
	 * hw शेष: 1K periodic list heads, one per frame.
	 * periodic_size can shrink by USBCMD update अगर hcc_params allows.
	 */
	priv->periodic_size = DEFAULT_I_TDPS;

	/* controllers may cache some of the periodic schedule ... */
	hcc_params = reg_पढ़ो32(hcd->regs, HC_HCCPARAMS);
	/* full frame cache */
	अगर (HCC_ISOC_CACHE(hcc_params))
		priv->i_thresh = 8;
	अन्यथा /* N microframes cached */
		priv->i_thresh = 2 + HCC_ISOC_THRES(hcc_params);

	वापस 0;
पूर्ण

अटल पूर्णांक isp1760_hc_setup(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा isp1760_hcd *priv = hcd_to_priv(hcd);
	पूर्णांक result;
	u32 scratch, hwmode;

	reg_ग_लिखो32(hcd->regs, HC_SCRATCH_REG, 0xdeadbabe);
	/* Change bus pattern */
	scratch = reg_पढ़ो32(hcd->regs, HC_CHIP_ID_REG);
	scratch = reg_पढ़ो32(hcd->regs, HC_SCRATCH_REG);
	अगर (scratch != 0xdeadbabe) अणु
		dev_err(hcd->self.controller, "Scratch test failed.\n");
		वापस -ENODEV;
	पूर्ण

	/*
	 * The RESET_HC bit in the SW_RESET रेजिस्टर is supposed to reset the
	 * host controller without touching the CPU पूर्णांकerface रेजिस्टरs, but at
	 * least on the ISP1761 it seems to behave as the RESET_ALL bit and
	 * reset the whole device. We thus can't use it here, so let's reset
	 * the host controller through the EHCI USB Command रेजिस्टर. The device
	 * has been reset in core code anyway, so this shouldn't matter.
	 */
	reg_ग_लिखो32(hcd->regs, HC_BUFFER_STATUS_REG, 0);
	reg_ग_लिखो32(hcd->regs, HC_ATL_PTD_SKIPMAP_REG, NO_TRANSFER_ACTIVE);
	reg_ग_लिखो32(hcd->regs, HC_INT_PTD_SKIPMAP_REG, NO_TRANSFER_ACTIVE);
	reg_ग_लिखो32(hcd->regs, HC_ISO_PTD_SKIPMAP_REG, NO_TRANSFER_ACTIVE);

	result = ehci_reset(hcd);
	अगर (result)
		वापस result;

	/* Step 11 passed */

	/* ATL reset */
	hwmode = reg_पढ़ो32(hcd->regs, HC_HW_MODE_CTRL) & ~ALL_ATX_RESET;
	reg_ग_लिखो32(hcd->regs, HC_HW_MODE_CTRL, hwmode | ALL_ATX_RESET);
	mdelay(10);
	reg_ग_लिखो32(hcd->regs, HC_HW_MODE_CTRL, hwmode);

	reg_ग_लिखो32(hcd->regs, HC_INTERRUPT_ENABLE, INTERRUPT_ENABLE_MASK);

	priv->hcs_params = reg_पढ़ो32(hcd->regs, HC_HCSPARAMS);

	वापस priv_init(hcd);
पूर्ण

अटल u32 base_to_chip(u32 base)
अणु
	वापस ((base - 0x400) >> 3);
पूर्ण

अटल पूर्णांक last_qtd_of_urb(काष्ठा isp1760_qtd *qtd, काष्ठा isp1760_qh *qh)
अणु
	काष्ठा urb *urb;

	अगर (list_is_last(&qtd->qtd_list, &qh->qtd_list))
		वापस 1;

	urb = qtd->urb;
	qtd = list_entry(qtd->qtd_list.next, typeof(*qtd), qtd_list);
	वापस (qtd->urb != urb);
पूर्ण

/* magic numbers that can affect प्रणाली perक्रमmance */
#घोषणा	EHCI_TUNE_CERR		3	/* 0-3 qtd retries; 0 == करोn't stop */
#घोषणा	EHCI_TUNE_RL_HS		4	/* nak throttle; see 4.9 */
#घोषणा	EHCI_TUNE_RL_TT		0
#घोषणा	EHCI_TUNE_MULT_HS	1	/* 1-3 transactions/uframe; 4.10.3 */
#घोषणा	EHCI_TUNE_MULT_TT	1
#घोषणा	EHCI_TUNE_FLS		2	/* (small) 256 frame schedule */

अटल व्योम create_ptd_atl(काष्ठा isp1760_qh *qh,
			काष्ठा isp1760_qtd *qtd, काष्ठा ptd *ptd)
अणु
	u32 maxpacket;
	u32 multi;
	u32 rl = RL_COUNTER;
	u32 nak = NAK_COUNTER;

	स_रखो(ptd, 0, माप(*ptd));

	/* according to 3.6.2, max packet len can not be > 0x400 */
	maxpacket = usb_maxpacket(qtd->urb->dev, qtd->urb->pipe,
						usb_pipeout(qtd->urb->pipe));
	multi =  1 + ((maxpacket >> 11) & 0x3);
	maxpacket &= 0x7ff;

	/* DW0 */
	ptd->dw0 = DW0_VALID_BIT;
	ptd->dw0 |= TO_DW0_LENGTH(qtd->length);
	ptd->dw0 |= TO_DW0_MAXPACKET(maxpacket);
	ptd->dw0 |= TO_DW0_ENDPOINT(usb_pipeendpoपूर्णांक(qtd->urb->pipe));

	/* DW1 */
	ptd->dw1 = usb_pipeendpoपूर्णांक(qtd->urb->pipe) >> 1;
	ptd->dw1 |= TO_DW1_DEVICE_ADDR(usb_pipedevice(qtd->urb->pipe));
	ptd->dw1 |= TO_DW1_PID_TOKEN(qtd->packet_type);

	अगर (usb_pipebulk(qtd->urb->pipe))
		ptd->dw1 |= DW1_TRANS_BULK;
	अन्यथा अगर  (usb_pipeपूर्णांक(qtd->urb->pipe))
		ptd->dw1 |= DW1_TRANS_INT;

	अगर (qtd->urb->dev->speed != USB_SPEED_HIGH) अणु
		/* split transaction */

		ptd->dw1 |= DW1_TRANS_SPLIT;
		अगर (qtd->urb->dev->speed == USB_SPEED_LOW)
			ptd->dw1 |= DW1_SE_USB_LOSPEED;

		ptd->dw1 |= TO_DW1_PORT_NUM(qtd->urb->dev->ttport);
		ptd->dw1 |= TO_DW1_HUB_NUM(qtd->urb->dev->tt->hub->devnum);

		/* SE bit क्रम Split INT transfers */
		अगर (usb_pipeपूर्णांक(qtd->urb->pipe) &&
				(qtd->urb->dev->speed == USB_SPEED_LOW))
			ptd->dw1 |= 2 << 16;

		rl = 0;
		nak = 0;
	पूर्ण अन्यथा अणु
		ptd->dw0 |= TO_DW0_MULTI(multi);
		अगर (usb_pipecontrol(qtd->urb->pipe) ||
						usb_pipebulk(qtd->urb->pipe))
			ptd->dw3 |= TO_DW3_PING(qh->ping);
	पूर्ण
	/* DW2 */
	ptd->dw2 = 0;
	ptd->dw2 |= TO_DW2_DATA_START_ADDR(base_to_chip(qtd->payload_addr));
	ptd->dw2 |= TO_DW2_RL(rl);

	/* DW3 */
	ptd->dw3 |= TO_DW3_NAKCOUNT(nak);
	ptd->dw3 |= TO_DW3_DATA_TOGGLE(qh->toggle);
	अगर (usb_pipecontrol(qtd->urb->pipe)) अणु
		अगर (qtd->data_buffer == qtd->urb->setup_packet)
			ptd->dw3 &= ~TO_DW3_DATA_TOGGLE(1);
		अन्यथा अगर (last_qtd_of_urb(qtd, qh))
			ptd->dw3 |= TO_DW3_DATA_TOGGLE(1);
	पूर्ण

	ptd->dw3 |= DW3_ACTIVE_BIT;
	/* Cerr */
	ptd->dw3 |= TO_DW3_CERR(ERR_COUNTER);
पूर्ण

अटल व्योम transक्रमm_add_पूर्णांक(काष्ठा isp1760_qh *qh,
			काष्ठा isp1760_qtd *qtd, काष्ठा ptd *ptd)
अणु
	u32 usof;
	u32 period;

	/*
	 * Most of this is guessing. ISP1761 datasheet is quite unclear, and
	 * the algorithm from the original Philips driver code, which was
	 * pretty much used in this driver beक्रमe as well, is quite horrenकरोus
	 * and, i believe, incorrect. The code below follows the datasheet and
	 * USB2.0 spec as far as I can tell, and plug/unplug seems to be much
	 * more reliable this way (fingers crossed...).
	 */

	अगर (qtd->urb->dev->speed == USB_SPEED_HIGH) अणु
		/* urb->पूर्णांकerval is in units of microframes (1/8 ms) */
		period = qtd->urb->पूर्णांकerval >> 3;

		अगर (qtd->urb->पूर्णांकerval > 4)
			usof = 0x01; /* One bit set =>
						पूर्णांकerval 1 ms * uFrame-match */
		अन्यथा अगर (qtd->urb->पूर्णांकerval > 2)
			usof = 0x22; /* Two bits set => पूर्णांकerval 1/2 ms */
		अन्यथा अगर (qtd->urb->पूर्णांकerval > 1)
			usof = 0x55; /* Four bits set => पूर्णांकerval 1/4 ms */
		अन्यथा
			usof = 0xff; /* All bits set => पूर्णांकerval 1/8 ms */
	पूर्ण अन्यथा अणु
		/* urb->पूर्णांकerval is in units of frames (1 ms) */
		period = qtd->urb->पूर्णांकerval;
		usof = 0x0f;		/* Execute Start Split on any of the
					   four first uFrames */

		/*
		 * First 8 bits in dw5 is uSCS and "specअगरies which uSOF the
		 * complete split needs to be sent. Valid only क्रम IN." Also,
		 * "All bits can be set to one for every transfer." (p 82,
		 * ISP1761 data sheet.) 0x1c is from Philips driver. Where did
		 * that number come from? 0xff seems to work fine...
		 */
		/* ptd->dw5 = 0x1c; */
		ptd->dw5 = 0xff; /* Execute Complete Split on any uFrame */
	पूर्ण

	period = period >> 1;/* Ensure equal or लघुer period than requested */
	period &= 0xf8; /* Mask off too large values and lowest unused 3 bits */

	ptd->dw2 |= period;
	ptd->dw4 = usof;
पूर्ण

अटल व्योम create_ptd_पूर्णांक(काष्ठा isp1760_qh *qh,
			काष्ठा isp1760_qtd *qtd, काष्ठा ptd *ptd)
अणु
	create_ptd_atl(qh, qtd, ptd);
	transक्रमm_add_पूर्णांक(qh, qtd, ptd);
पूर्ण

अटल व्योम isp1760_urb_करोne(काष्ठा usb_hcd *hcd, काष्ठा urb *urb)
__releases(priv->lock)
__acquires(priv->lock)
अणु
	काष्ठा isp1760_hcd *priv = hcd_to_priv(hcd);

	अगर (!urb->unlinked) अणु
		अगर (urb->status == -EINPROGRESS)
			urb->status = 0;
	पूर्ण

	अगर (usb_pipein(urb->pipe) && usb_pipetype(urb->pipe) != PIPE_CONTROL) अणु
		व्योम *ptr;
		क्रम (ptr = urb->transfer_buffer;
		     ptr < urb->transfer_buffer + urb->transfer_buffer_length;
		     ptr += PAGE_SIZE)
			flush_dcache_page(virt_to_page(ptr));
	पूर्ण

	/* complete() can reenter this HCD */
	usb_hcd_unlink_urb_from_ep(hcd, urb);
	spin_unlock(&priv->lock);
	usb_hcd_giveback_urb(hcd, urb, urb->status);
	spin_lock(&priv->lock);
पूर्ण

अटल काष्ठा isp1760_qtd *qtd_alloc(gfp_t flags, काष्ठा urb *urb,
								u8 packet_type)
अणु
	काष्ठा isp1760_qtd *qtd;

	qtd = kmem_cache_zalloc(qtd_cachep, flags);
	अगर (!qtd)
		वापस शून्य;

	INIT_LIST_HEAD(&qtd->qtd_list);
	qtd->urb = urb;
	qtd->packet_type = packet_type;
	qtd->status = QTD_ENQUEUED;
	qtd->actual_length = 0;

	वापस qtd;
पूर्ण

अटल व्योम qtd_मुक्त(काष्ठा isp1760_qtd *qtd)
अणु
	WARN_ON(qtd->payload_addr);
	kmem_cache_मुक्त(qtd_cachep, qtd);
पूर्ण

अटल व्योम start_bus_transfer(काष्ठा usb_hcd *hcd, u32 ptd_offset, पूर्णांक slot,
				काष्ठा isp1760_slotinfo *slots,
				काष्ठा isp1760_qtd *qtd, काष्ठा isp1760_qh *qh,
				काष्ठा ptd *ptd)
अणु
	काष्ठा isp1760_hcd *priv = hcd_to_priv(hcd);
	पूर्णांक skip_map;

	WARN_ON((slot < 0) || (slot > 31));
	WARN_ON(qtd->length && !qtd->payload_addr);
	WARN_ON(slots[slot].qtd);
	WARN_ON(slots[slot].qh);
	WARN_ON(qtd->status != QTD_PAYLOAD_ALLOC);

	/* Make sure करोne map has not triggered from some unlinked transfer */
	अगर (ptd_offset == ATL_PTD_OFFSET) अणु
		priv->atl_करोne_map |= reg_पढ़ो32(hcd->regs,
						HC_ATL_PTD_DONEMAP_REG);
		priv->atl_करोne_map &= ~(1 << slot);
	पूर्ण अन्यथा अणु
		priv->पूर्णांक_करोne_map |= reg_पढ़ो32(hcd->regs,
						HC_INT_PTD_DONEMAP_REG);
		priv->पूर्णांक_करोne_map &= ~(1 << slot);
	पूर्ण

	qh->slot = slot;
	qtd->status = QTD_XFER_STARTED;
	slots[slot].बारtamp = jअगरfies;
	slots[slot].qtd = qtd;
	slots[slot].qh = qh;
	ptd_ग_लिखो(hcd->regs, ptd_offset, slot, ptd);

	अगर (ptd_offset == ATL_PTD_OFFSET) अणु
		skip_map = reg_पढ़ो32(hcd->regs, HC_ATL_PTD_SKIPMAP_REG);
		skip_map &= ~(1 << qh->slot);
		reg_ग_लिखो32(hcd->regs, HC_ATL_PTD_SKIPMAP_REG, skip_map);
	पूर्ण अन्यथा अणु
		skip_map = reg_पढ़ो32(hcd->regs, HC_INT_PTD_SKIPMAP_REG);
		skip_map &= ~(1 << qh->slot);
		reg_ग_लिखो32(hcd->regs, HC_INT_PTD_SKIPMAP_REG, skip_map);
	पूर्ण
पूर्ण

अटल पूर्णांक is_लघु_bulk(काष्ठा isp1760_qtd *qtd)
अणु
	वापस (usb_pipebulk(qtd->urb->pipe) &&
					(qtd->actual_length < qtd->length));
पूर्ण

अटल व्योम collect_qtds(काष्ठा usb_hcd *hcd, काष्ठा isp1760_qh *qh,
						काष्ठा list_head *urb_list)
अणु
	पूर्णांक last_qtd;
	काष्ठा isp1760_qtd *qtd, *qtd_next;
	काष्ठा urb_listitem *urb_listitem;

	list_क्रम_each_entry_safe(qtd, qtd_next, &qh->qtd_list, qtd_list) अणु
		अगर (qtd->status < QTD_XFER_COMPLETE)
			अवरोध;

		last_qtd = last_qtd_of_urb(qtd, qh);

		अगर ((!last_qtd) && (qtd->status == QTD_RETIRE))
			qtd_next->status = QTD_RETIRE;

		अगर (qtd->status == QTD_XFER_COMPLETE) अणु
			अगर (qtd->actual_length) अणु
				चयन (qtd->packet_type) अणु
				हाल IN_PID:
					mem_पढ़ोs8(hcd->regs, qtd->payload_addr,
							qtd->data_buffer,
							qtd->actual_length);
					fallthrough;
				हाल OUT_PID:
					qtd->urb->actual_length +=
							qtd->actual_length;
					fallthrough;
				हाल SETUP_PID:
					अवरोध;
				पूर्ण
			पूर्ण

			अगर (is_लघु_bulk(qtd)) अणु
				अगर (qtd->urb->transfer_flags & URB_SHORT_NOT_OK)
					qtd->urb->status = -EREMOTEIO;
				अगर (!last_qtd)
					qtd_next->status = QTD_RETIRE;
			पूर्ण
		पूर्ण

		अगर (qtd->payload_addr)
			मुक्त_mem(hcd, qtd);

		अगर (last_qtd) अणु
			अगर ((qtd->status == QTD_RETIRE) &&
					(qtd->urb->status == -EINPROGRESS))
				qtd->urb->status = -EPIPE;
			/* Defer calling of urb_करोne() since it releases lock */
			urb_listitem = kmem_cache_zalloc(urb_listitem_cachep,
								GFP_ATOMIC);
			अगर (unlikely(!urb_listitem))
				अवरोध; /* Try again on next call */
			urb_listitem->urb = qtd->urb;
			list_add_tail(&urb_listitem->urb_list, urb_list);
		पूर्ण

		list_del(&qtd->qtd_list);
		qtd_मुक्त(qtd);
	पूर्ण
पूर्ण

#घोषणा ENQUEUE_DEPTH	2
अटल व्योम enqueue_qtds(काष्ठा usb_hcd *hcd, काष्ठा isp1760_qh *qh)
अणु
	काष्ठा isp1760_hcd *priv = hcd_to_priv(hcd);
	पूर्णांक ptd_offset;
	काष्ठा isp1760_slotinfo *slots;
	पूर्णांक curr_slot, मुक्त_slot;
	पूर्णांक n;
	काष्ठा ptd ptd;
	काष्ठा isp1760_qtd *qtd;

	अगर (unlikely(list_empty(&qh->qtd_list))) अणु
		WARN_ON(1);
		वापस;
	पूर्ण

	/* Make sure this endpoपूर्णांक's TT buffer is clean beक्रमe queueing ptds */
	अगर (qh->tt_buffer_dirty)
		वापस;

	अगर (usb_pipeपूर्णांक(list_entry(qh->qtd_list.next, काष्ठा isp1760_qtd,
							qtd_list)->urb->pipe)) अणु
		ptd_offset = INT_PTD_OFFSET;
		slots = priv->पूर्णांक_slots;
	पूर्ण अन्यथा अणु
		ptd_offset = ATL_PTD_OFFSET;
		slots = priv->atl_slots;
	पूर्ण

	मुक्त_slot = -1;
	क्रम (curr_slot = 0; curr_slot < 32; curr_slot++) अणु
		अगर ((मुक्त_slot == -1) && (slots[curr_slot].qtd == शून्य))
			मुक्त_slot = curr_slot;
		अगर (slots[curr_slot].qh == qh)
			अवरोध;
	पूर्ण

	n = 0;
	list_क्रम_each_entry(qtd, &qh->qtd_list, qtd_list) अणु
		अगर (qtd->status == QTD_ENQUEUED) अणु
			WARN_ON(qtd->payload_addr);
			alloc_mem(hcd, qtd);
			अगर ((qtd->length) && (!qtd->payload_addr))
				अवरोध;

			अगर ((qtd->length) &&
			    ((qtd->packet_type == SETUP_PID) ||
			     (qtd->packet_type == OUT_PID))) अणु
				mem_ग_लिखोs8(hcd->regs, qtd->payload_addr,
						qtd->data_buffer, qtd->length);
			पूर्ण

			qtd->status = QTD_PAYLOAD_ALLOC;
		पूर्ण

		अगर (qtd->status == QTD_PAYLOAD_ALLOC) अणु
/*
			अगर ((curr_slot > 31) && (मुक्त_slot == -1))
				dev_dbg(hcd->self.controller, "%s: No slot "
					"available for transfer\n", __func__);
*/
			/* Start xfer क्रम this endpoपूर्णांक अगर not alपढ़ोy करोne */
			अगर ((curr_slot > 31) && (मुक्त_slot > -1)) अणु
				अगर (usb_pipeपूर्णांक(qtd->urb->pipe))
					create_ptd_पूर्णांक(qh, qtd, &ptd);
				अन्यथा
					create_ptd_atl(qh, qtd, &ptd);

				start_bus_transfer(hcd, ptd_offset, मुक्त_slot,
							slots, qtd, qh, &ptd);
				curr_slot = मुक्त_slot;
			पूर्ण

			n++;
			अगर (n >= ENQUEUE_DEPTH)
				अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम schedule_ptds(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा isp1760_hcd *priv;
	काष्ठा isp1760_qh *qh, *qh_next;
	काष्ठा list_head *ep_queue;
	LIST_HEAD(urb_list);
	काष्ठा urb_listitem *urb_listitem, *urb_listitem_next;
	पूर्णांक i;

	अगर (!hcd) अणु
		WARN_ON(1);
		वापस;
	पूर्ण

	priv = hcd_to_priv(hcd);

	/*
	 * check finished/retired xfers, transfer payloads, call urb_करोne()
	 */
	क्रम (i = 0; i < QH_END; i++) अणु
		ep_queue = &priv->qh_list[i];
		list_क्रम_each_entry_safe(qh, qh_next, ep_queue, qh_list) अणु
			collect_qtds(hcd, qh, &urb_list);
			अगर (list_empty(&qh->qtd_list))
				list_del(&qh->qh_list);
		पूर्ण
	पूर्ण

	list_क्रम_each_entry_safe(urb_listitem, urb_listitem_next, &urb_list,
								urb_list) अणु
		isp1760_urb_करोne(hcd, urb_listitem->urb);
		kmem_cache_मुक्त(urb_listitem_cachep, urb_listitem);
	पूर्ण

	/*
	 * Schedule packets क्रम transfer.
	 *
	 * According to USB2.0 specअगरication:
	 *
	 * 1st prio: पूर्णांकerrupt xfers, up to 80 % of bandwidth
	 * 2nd prio: control xfers
	 * 3rd prio: bulk xfers
	 *
	 * ... but let's use a simpler scheme here (mostly because ISP1761 करोc
	 * is very unclear on how to prioritize traffic):
	 *
	 * 1) Enqueue any queued control transfers, as दीर्घ as payload chip mem
	 *    and PTD ATL slots are available.
	 * 2) Enqueue any queued INT transfers, as दीर्घ as payload chip mem
	 *    and PTD INT slots are available.
	 * 3) Enqueue any queued bulk transfers, as दीर्घ as payload chip mem
	 *    and PTD ATL slots are available.
	 *
	 * Use द्विगुन buffering (ENQUEUE_DEPTH==2) as a compromise between
	 * conservation of chip mem and perक्रमmance.
	 *
	 * I'm sure this scheme could be improved upon!
	 */
	क्रम (i = 0; i < QH_END; i++) अणु
		ep_queue = &priv->qh_list[i];
		list_क्रम_each_entry_safe(qh, qh_next, ep_queue, qh_list)
			enqueue_qtds(hcd, qh);
	पूर्ण
पूर्ण

#घोषणा PTD_STATE_QTD_DONE	1
#घोषणा PTD_STATE_QTD_RELOAD	2
#घोषणा PTD_STATE_URB_RETIRE	3

अटल पूर्णांक check_पूर्णांक_transfer(काष्ठा usb_hcd *hcd, काष्ठा ptd *ptd,
								काष्ठा urb *urb)
अणु
	__dw dw4;
	पूर्णांक i;

	dw4 = ptd->dw4;
	dw4 >>= 8;

	/* FIXME: ISP1761 datasheet करोes not say what to करो with these. Do we
	   need to handle these errors? Is it करोne in hardware? */

	अगर (ptd->dw3 & DW3_HALT_BIT) अणु

		urb->status = -EPROTO; /* Default unknown error */

		क्रम (i = 0; i < 8; i++) अणु
			चयन (dw4 & 0x7) अणु
			हाल INT_UNDERRUN:
				dev_dbg(hcd->self.controller, "%s: underrun "
						"during uFrame %d\n",
						__func__, i);
				urb->status = -ECOMM; /* Could not ग_लिखो data */
				अवरोध;
			हाल INT_EXACT:
				dev_dbg(hcd->self.controller, "%s: transaction "
						"error during uFrame %d\n",
						__func__, i);
				urb->status = -EPROTO; /* समयout, bad CRC, PID
							  error etc. */
				अवरोध;
			हाल INT_BABBLE:
				dev_dbg(hcd->self.controller, "%s: babble "
						"error during uFrame %d\n",
						__func__, i);
				urb->status = -EOVERFLOW;
				अवरोध;
			पूर्ण
			dw4 >>= 3;
		पूर्ण

		वापस PTD_STATE_URB_RETIRE;
	पूर्ण

	वापस PTD_STATE_QTD_DONE;
पूर्ण

अटल पूर्णांक check_atl_transfer(काष्ठा usb_hcd *hcd, काष्ठा ptd *ptd,
								काष्ठा urb *urb)
अणु
	WARN_ON(!ptd);
	अगर (ptd->dw3 & DW3_HALT_BIT) अणु
		अगर (ptd->dw3 & DW3_BABBLE_BIT)
			urb->status = -EOVERFLOW;
		अन्यथा अगर (FROM_DW3_CERR(ptd->dw3))
			urb->status = -EPIPE;  /* Stall */
		अन्यथा
			urb->status = -EPROTO; /* Unknown */
/*
		dev_dbg(hcd->self.controller, "%s: ptd error:\n"
			"        dw0: %08x dw1: %08x dw2: %08x dw3: %08x\n"
			"        dw4: %08x dw5: %08x dw6: %08x dw7: %08x\n",
			__func__,
			ptd->dw0, ptd->dw1, ptd->dw2, ptd->dw3,
			ptd->dw4, ptd->dw5, ptd->dw6, ptd->dw7);
*/
		वापस PTD_STATE_URB_RETIRE;
	पूर्ण

	अगर ((ptd->dw3 & DW3_ERROR_BIT) && (ptd->dw3 & DW3_ACTIVE_BIT)) अणु
		/* Transfer Error, *but* active and no HALT -> reload */
		dev_dbg(hcd->self.controller, "PID error; reloading ptd\n");
		वापस PTD_STATE_QTD_RELOAD;
	पूर्ण

	अगर (!FROM_DW3_NAKCOUNT(ptd->dw3) && (ptd->dw3 & DW3_ACTIVE_BIT)) अणु
		/*
		 * NAKs are handled in HW by the chip. Usually अगर the
		 * device is not able to send data fast enough.
		 * This happens mostly on slower hardware.
		 */
		वापस PTD_STATE_QTD_RELOAD;
	पूर्ण

	वापस PTD_STATE_QTD_DONE;
पूर्ण

अटल व्योम handle_करोne_ptds(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा isp1760_hcd *priv = hcd_to_priv(hcd);
	काष्ठा ptd ptd;
	काष्ठा isp1760_qh *qh;
	पूर्णांक slot;
	पूर्णांक state;
	काष्ठा isp1760_slotinfo *slots;
	u32 ptd_offset;
	काष्ठा isp1760_qtd *qtd;
	पूर्णांक modअगरied;
	पूर्णांक skip_map;

	skip_map = reg_पढ़ो32(hcd->regs, HC_INT_PTD_SKIPMAP_REG);
	priv->पूर्णांक_करोne_map &= ~skip_map;
	skip_map = reg_पढ़ो32(hcd->regs, HC_ATL_PTD_SKIPMAP_REG);
	priv->atl_करोne_map &= ~skip_map;

	modअगरied = priv->पूर्णांक_करोne_map || priv->atl_करोne_map;

	जबतक (priv->पूर्णांक_करोne_map || priv->atl_करोne_map) अणु
		अगर (priv->पूर्णांक_करोne_map) अणु
			/* INT ptd */
			slot = __ffs(priv->पूर्णांक_करोne_map);
			priv->पूर्णांक_करोne_map &= ~(1 << slot);
			slots = priv->पूर्णांक_slots;
			/* This should not trigger, and could be हटाओd अगर
			   noone have any problems with it triggering: */
			अगर (!slots[slot].qh) अणु
				WARN_ON(1);
				जारी;
			पूर्ण
			ptd_offset = INT_PTD_OFFSET;
			ptd_पढ़ो(hcd->regs, INT_PTD_OFFSET, slot, &ptd);
			state = check_पूर्णांक_transfer(hcd, &ptd,
							slots[slot].qtd->urb);
		पूर्ण अन्यथा अणु
			/* ATL ptd */
			slot = __ffs(priv->atl_करोne_map);
			priv->atl_करोne_map &= ~(1 << slot);
			slots = priv->atl_slots;
			/* This should not trigger, and could be हटाओd अगर
			   noone have any problems with it triggering: */
			अगर (!slots[slot].qh) अणु
				WARN_ON(1);
				जारी;
			पूर्ण
			ptd_offset = ATL_PTD_OFFSET;
			ptd_पढ़ो(hcd->regs, ATL_PTD_OFFSET, slot, &ptd);
			state = check_atl_transfer(hcd, &ptd,
							slots[slot].qtd->urb);
		पूर्ण

		qtd = slots[slot].qtd;
		slots[slot].qtd = शून्य;
		qh = slots[slot].qh;
		slots[slot].qh = शून्य;
		qh->slot = -1;

		WARN_ON(qtd->status != QTD_XFER_STARTED);

		चयन (state) अणु
		हाल PTD_STATE_QTD_DONE:
			अगर ((usb_pipeपूर्णांक(qtd->urb->pipe)) &&
				       (qtd->urb->dev->speed != USB_SPEED_HIGH))
				qtd->actual_length =
				       FROM_DW3_SCS_NRBYTESTRANSFERRED(ptd.dw3);
			अन्यथा
				qtd->actual_length =
					FROM_DW3_NRBYTESTRANSFERRED(ptd.dw3);

			qtd->status = QTD_XFER_COMPLETE;
			अगर (list_is_last(&qtd->qtd_list, &qh->qtd_list) ||
							is_लघु_bulk(qtd))
				qtd = शून्य;
			अन्यथा
				qtd = list_entry(qtd->qtd_list.next,
							typeof(*qtd), qtd_list);

			qh->toggle = FROM_DW3_DATA_TOGGLE(ptd.dw3);
			qh->ping = FROM_DW3_PING(ptd.dw3);
			अवरोध;

		हाल PTD_STATE_QTD_RELOAD: /* QTD_RETRY, क्रम atls only */
			qtd->status = QTD_PAYLOAD_ALLOC;
			ptd.dw0 |= DW0_VALID_BIT;
			/* RL counter = ERR counter */
			ptd.dw3 &= ~TO_DW3_NAKCOUNT(0xf);
			ptd.dw3 |= TO_DW3_NAKCOUNT(FROM_DW2_RL(ptd.dw2));
			ptd.dw3 &= ~TO_DW3_CERR(3);
			ptd.dw3 |= TO_DW3_CERR(ERR_COUNTER);
			qh->toggle = FROM_DW3_DATA_TOGGLE(ptd.dw3);
			qh->ping = FROM_DW3_PING(ptd.dw3);
			अवरोध;

		हाल PTD_STATE_URB_RETIRE:
			qtd->status = QTD_RETIRE;
			अगर ((qtd->urb->dev->speed != USB_SPEED_HIGH) &&
					(qtd->urb->status != -EPIPE) &&
					(qtd->urb->status != -EREMOTEIO)) अणु
				qh->tt_buffer_dirty = 1;
				अगर (usb_hub_clear_tt_buffer(qtd->urb))
					/* Clear failed; let's hope things work
					   anyway */
					qh->tt_buffer_dirty = 0;
			पूर्ण
			qtd = शून्य;
			qh->toggle = 0;
			qh->ping = 0;
			अवरोध;

		शेष:
			WARN_ON(1);
			जारी;
		पूर्ण

		अगर (qtd && (qtd->status == QTD_PAYLOAD_ALLOC)) अणु
			अगर (slots == priv->पूर्णांक_slots) अणु
				अगर (state == PTD_STATE_QTD_RELOAD)
					dev_err(hcd->self.controller,
						"%s: PTD_STATE_QTD_RELOAD on "
						"interrupt packet\n", __func__);
				अगर (state != PTD_STATE_QTD_RELOAD)
					create_ptd_पूर्णांक(qh, qtd, &ptd);
			पूर्ण अन्यथा अणु
				अगर (state != PTD_STATE_QTD_RELOAD)
					create_ptd_atl(qh, qtd, &ptd);
			पूर्ण

			start_bus_transfer(hcd, ptd_offset, slot, slots, qtd,
				qh, &ptd);
		पूर्ण
	पूर्ण

	अगर (modअगरied)
		schedule_ptds(hcd);
पूर्ण

अटल irqवापस_t isp1760_irq(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा isp1760_hcd *priv = hcd_to_priv(hcd);
	u32 imask;
	irqवापस_t irqret = IRQ_NONE;

	spin_lock(&priv->lock);

	अगर (!(hcd->state & HC_STATE_RUNNING))
		जाओ leave;

	imask = reg_पढ़ो32(hcd->regs, HC_INTERRUPT_REG);
	अगर (unlikely(!imask))
		जाओ leave;
	reg_ग_लिखो32(hcd->regs, HC_INTERRUPT_REG, imask); /* Clear */

	priv->पूर्णांक_करोne_map |= reg_पढ़ो32(hcd->regs, HC_INT_PTD_DONEMAP_REG);
	priv->atl_करोne_map |= reg_पढ़ो32(hcd->regs, HC_ATL_PTD_DONEMAP_REG);

	handle_करोne_ptds(hcd);

	irqret = IRQ_HANDLED;
leave:
	spin_unlock(&priv->lock);

	वापस irqret;
पूर्ण

/*
 * Workaround क्रम problem described in chip errata 2:
 *
 * Someबार पूर्णांकerrupts are not generated when ATL (not INT?) completion occurs.
 * One solution suggested in the errata is to use SOF पूर्णांकerrupts _instead_of_
 * ATL करोne पूर्णांकerrupts (the "instead of" might be important since it seems
 * enabling ATL पूर्णांकerrupts also causes the chip to someबार - rarely - "forget"
 * to set the PTD's करोne bit in addition to not generating an पूर्णांकerrupt!).
 *
 * So अगर we use SOF + ATL पूर्णांकerrupts, we someबार get stale PTDs since their
 * करोne bit is not being set. This is bad - it blocks the endpoपूर्णांक until reboot.
 *
 * If we use SOF पूर्णांकerrupts only, we get latency between ptd completion and the
 * actual handling. This is very noticeable in testusb runs which takes several
 * minutes दीर्घer without ATL पूर्णांकerrupts.
 *
 * A better solution is to run the code below every SLOT_CHECK_PERIOD ms. If it
 * finds active ATL slots which are older than SLOT_TIMEOUT ms, it checks the
 * slot's ACTIVE and VALID bits. If these are not set, the ptd is considered
 * completed and its करोne map bit is set.
 *
 * The values of SLOT_TIMEOUT and SLOT_CHECK_PERIOD have been arbitrarily chosen
 * not to cause too much lag when this HW bug occurs, जबतक still hopefully
 * ensuring that the check करोes not falsely trigger.
 */
#घोषणा SLOT_TIMEOUT 300
#घोषणा SLOT_CHECK_PERIOD 200
अटल काष्ठा समयr_list errata2_समयr;
अटल काष्ठा usb_hcd *errata2_समयr_hcd;

अटल व्योम errata2_function(काष्ठा समयr_list *unused)
अणु
	काष्ठा usb_hcd *hcd = errata2_समयr_hcd;
	काष्ठा isp1760_hcd *priv = hcd_to_priv(hcd);
	पूर्णांक slot;
	काष्ठा ptd ptd;
	अचिन्हित दीर्घ spinflags;

	spin_lock_irqsave(&priv->lock, spinflags);

	क्रम (slot = 0; slot < 32; slot++)
		अगर (priv->atl_slots[slot].qh && समय_after(jअगरfies,
					priv->atl_slots[slot].बारtamp +
					msecs_to_jअगरfies(SLOT_TIMEOUT))) अणु
			ptd_पढ़ो(hcd->regs, ATL_PTD_OFFSET, slot, &ptd);
			अगर (!FROM_DW0_VALID(ptd.dw0) &&
					!FROM_DW3_ACTIVE(ptd.dw3))
				priv->atl_करोne_map |= 1 << slot;
		पूर्ण

	अगर (priv->atl_करोne_map)
		handle_करोne_ptds(hcd);

	spin_unlock_irqrestore(&priv->lock, spinflags);

	errata2_समयr.expires = jअगरfies + msecs_to_jअगरfies(SLOT_CHECK_PERIOD);
	add_समयr(&errata2_समयr);
पूर्ण

अटल पूर्णांक isp1760_run(काष्ठा usb_hcd *hcd)
अणु
	पूर्णांक retval;
	u32 temp;
	u32 command;
	u32 chipid;

	hcd->uses_new_polling = 1;

	hcd->state = HC_STATE_RUNNING;

	/* Set PTD पूर्णांकerrupt AND & OR maps */
	reg_ग_लिखो32(hcd->regs, HC_ATL_IRQ_MASK_AND_REG, 0);
	reg_ग_लिखो32(hcd->regs, HC_ATL_IRQ_MASK_OR_REG, 0xffffffff);
	reg_ग_लिखो32(hcd->regs, HC_INT_IRQ_MASK_AND_REG, 0);
	reg_ग_लिखो32(hcd->regs, HC_INT_IRQ_MASK_OR_REG, 0xffffffff);
	reg_ग_लिखो32(hcd->regs, HC_ISO_IRQ_MASK_AND_REG, 0);
	reg_ग_लिखो32(hcd->regs, HC_ISO_IRQ_MASK_OR_REG, 0xffffffff);
	/* step 23 passed */

	temp = reg_पढ़ो32(hcd->regs, HC_HW_MODE_CTRL);
	reg_ग_लिखो32(hcd->regs, HC_HW_MODE_CTRL, temp | HW_GLOBAL_INTR_EN);

	command = reg_पढ़ो32(hcd->regs, HC_USBCMD);
	command &= ~(CMD_LRESET|CMD_RESET);
	command |= CMD_RUN;
	reg_ग_लिखो32(hcd->regs, HC_USBCMD, command);

	retval = handshake(hcd, HC_USBCMD, CMD_RUN, CMD_RUN, 250 * 1000);
	अगर (retval)
		वापस retval;

	/*
	 * XXX
	 * Spec says to ग_लिखो FLAG_CF as last config action, priv code grअसल
	 * the semaphore जबतक करोing so.
	 */
	करोwn_ग_लिखो(&ehci_cf_port_reset_rwsem);
	reg_ग_लिखो32(hcd->regs, HC_CONFIGFLAG, FLAG_CF);

	retval = handshake(hcd, HC_CONFIGFLAG, FLAG_CF, FLAG_CF, 250 * 1000);
	up_ग_लिखो(&ehci_cf_port_reset_rwsem);
	अगर (retval)
		वापस retval;

	errata2_समयr_hcd = hcd;
	समयr_setup(&errata2_समयr, errata2_function, 0);
	errata2_समयr.expires = jअगरfies + msecs_to_jअगरfies(SLOT_CHECK_PERIOD);
	add_समयr(&errata2_समयr);

	chipid = reg_पढ़ो32(hcd->regs, HC_CHIP_ID_REG);
	dev_info(hcd->self.controller, "USB ISP %04x HW rev. %d started\n",
					chipid & 0xffff, chipid >> 16);

	/* PTD Register Init Part 2, Step 28 */

	/* Setup रेजिस्टरs controlling PTD checking */
	reg_ग_लिखो32(hcd->regs, HC_ATL_PTD_LASTPTD_REG, 0x80000000);
	reg_ग_लिखो32(hcd->regs, HC_INT_PTD_LASTPTD_REG, 0x80000000);
	reg_ग_लिखो32(hcd->regs, HC_ISO_PTD_LASTPTD_REG, 0x00000001);
	reg_ग_लिखो32(hcd->regs, HC_ATL_PTD_SKIPMAP_REG, 0xffffffff);
	reg_ग_लिखो32(hcd->regs, HC_INT_PTD_SKIPMAP_REG, 0xffffffff);
	reg_ग_लिखो32(hcd->regs, HC_ISO_PTD_SKIPMAP_REG, 0xffffffff);
	reg_ग_लिखो32(hcd->regs, HC_BUFFER_STATUS_REG,
						ATL_BUF_FILL | INT_BUF_FILL);

	/* GRR this is run-once init(), being करोne every समय the HC starts.
	 * So दीर्घ as they're part of class devices, we can't करो it init()
	 * since the class device isn't created that early.
	 */
	वापस 0;
पूर्ण

अटल पूर्णांक qtd_fill(काष्ठा isp1760_qtd *qtd, व्योम *databuffer, माप_प्रकार len)
अणु
	qtd->data_buffer = databuffer;

	अगर (len > MAX_PAYLOAD_SIZE)
		len = MAX_PAYLOAD_SIZE;
	qtd->length = len;

	वापस qtd->length;
पूर्ण

अटल व्योम qtd_list_मुक्त(काष्ठा list_head *qtd_list)
अणु
	काष्ठा isp1760_qtd *qtd, *qtd_next;

	list_क्रम_each_entry_safe(qtd, qtd_next, qtd_list, qtd_list) अणु
		list_del(&qtd->qtd_list);
		qtd_मुक्त(qtd);
	पूर्ण
पूर्ण

/*
 * Packetize urb->transfer_buffer पूर्णांकo list of packets of size wMaxPacketSize.
 * Also calculate the PID type (SETUP/IN/OUT) क्रम each packet.
 */
#घोषणा max_packet(wMaxPacketSize) ((wMaxPacketSize) & 0x07ff)
अटल व्योम packetize_urb(काष्ठा usb_hcd *hcd,
		काष्ठा urb *urb, काष्ठा list_head *head, gfp_t flags)
अणु
	काष्ठा isp1760_qtd *qtd;
	व्योम *buf;
	पूर्णांक len, maxpacketsize;
	u8 packet_type;

	/*
	 * URBs map to sequences of QTDs:  one logical transaction
	 */

	अगर (!urb->transfer_buffer && urb->transfer_buffer_length) अणु
		/* XXX This looks like usb storage / SCSI bug */
		dev_err(hcd->self.controller,
				"buf is null, dma is %08lx len is %d\n",
				(दीर्घ अचिन्हित)urb->transfer_dma,
				urb->transfer_buffer_length);
		WARN_ON(1);
	पूर्ण

	अगर (usb_pipein(urb->pipe))
		packet_type = IN_PID;
	अन्यथा
		packet_type = OUT_PID;

	अगर (usb_pipecontrol(urb->pipe)) अणु
		qtd = qtd_alloc(flags, urb, SETUP_PID);
		अगर (!qtd)
			जाओ cleanup;
		qtd_fill(qtd, urb->setup_packet, माप(काष्ठा usb_ctrlrequest));
		list_add_tail(&qtd->qtd_list, head);

		/* क्रम zero length DATA stages, STATUS is always IN */
		अगर (urb->transfer_buffer_length == 0)
			packet_type = IN_PID;
	पूर्ण

	maxpacketsize = max_packet(usb_maxpacket(urb->dev, urb->pipe,
						usb_pipeout(urb->pipe)));

	/*
	 * buffer माला_लो wrapped in one or more qtds;
	 * last one may be "short" (including zero len)
	 * and may serve as a control status ack
	 */
	buf = urb->transfer_buffer;
	len = urb->transfer_buffer_length;

	क्रम (;;) अणु
		पूर्णांक this_qtd_len;

		qtd = qtd_alloc(flags, urb, packet_type);
		अगर (!qtd)
			जाओ cleanup;
		this_qtd_len = qtd_fill(qtd, buf, len);
		list_add_tail(&qtd->qtd_list, head);

		len -= this_qtd_len;
		buf += this_qtd_len;

		अगर (len <= 0)
			अवरोध;
	पूर्ण

	/*
	 * control requests may need a terminating data "status" ack;
	 * bulk ones may need a terminating लघु packet (zero length).
	 */
	अगर (urb->transfer_buffer_length != 0) अणु
		पूर्णांक one_more = 0;

		अगर (usb_pipecontrol(urb->pipe)) अणु
			one_more = 1;
			अगर (packet_type == IN_PID)
				packet_type = OUT_PID;
			अन्यथा
				packet_type = IN_PID;
		पूर्ण अन्यथा अगर (usb_pipebulk(urb->pipe)
				&& (urb->transfer_flags & URB_ZERO_PACKET)
				&& !(urb->transfer_buffer_length %
							maxpacketsize)) अणु
			one_more = 1;
		पूर्ण
		अगर (one_more) अणु
			qtd = qtd_alloc(flags, urb, packet_type);
			अगर (!qtd)
				जाओ cleanup;

			/* never any data in such packets */
			qtd_fill(qtd, शून्य, 0);
			list_add_tail(&qtd->qtd_list, head);
		पूर्ण
	पूर्ण

	वापस;

cleanup:
	qtd_list_मुक्त(head);
पूर्ण

अटल पूर्णांक isp1760_urb_enqueue(काष्ठा usb_hcd *hcd, काष्ठा urb *urb,
		gfp_t mem_flags)
अणु
	काष्ठा isp1760_hcd *priv = hcd_to_priv(hcd);
	काष्ठा list_head *ep_queue;
	काष्ठा isp1760_qh *qh, *qhit;
	अचिन्हित दीर्घ spinflags;
	LIST_HEAD(new_qtds);
	पूर्णांक retval;
	पूर्णांक qh_in_queue;

	चयन (usb_pipetype(urb->pipe)) अणु
	हाल PIPE_CONTROL:
		ep_queue = &priv->qh_list[QH_CONTROL];
		अवरोध;
	हाल PIPE_BULK:
		ep_queue = &priv->qh_list[QH_BULK];
		अवरोध;
	हाल PIPE_INTERRUPT:
		अगर (urb->पूर्णांकerval < 0)
			वापस -EINVAL;
		/* FIXME: Check bandwidth  */
		ep_queue = &priv->qh_list[QH_INTERRUPT];
		अवरोध;
	हाल PIPE_ISOCHRONOUS:
		dev_err(hcd->self.controller, "%s: isochronous USB packets "
							"not yet supported\n",
							__func__);
		वापस -EPIPE;
	शेष:
		dev_err(hcd->self.controller, "%s: unknown pipe type\n",
							__func__);
		वापस -EPIPE;
	पूर्ण

	अगर (usb_pipein(urb->pipe))
		urb->actual_length = 0;

	packetize_urb(hcd, urb, &new_qtds, mem_flags);
	अगर (list_empty(&new_qtds))
		वापस -ENOMEM;

	retval = 0;
	spin_lock_irqsave(&priv->lock, spinflags);

	अगर (!test_bit(HCD_FLAG_HW_ACCESSIBLE, &hcd->flags)) अणु
		retval = -ESHUTDOWN;
		qtd_list_मुक्त(&new_qtds);
		जाओ out;
	पूर्ण
	retval = usb_hcd_link_urb_to_ep(hcd, urb);
	अगर (retval) अणु
		qtd_list_मुक्त(&new_qtds);
		जाओ out;
	पूर्ण

	qh = urb->ep->hcpriv;
	अगर (qh) अणु
		qh_in_queue = 0;
		list_क्रम_each_entry(qhit, ep_queue, qh_list) अणु
			अगर (qhit == qh) अणु
				qh_in_queue = 1;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (!qh_in_queue)
			list_add_tail(&qh->qh_list, ep_queue);
	पूर्ण अन्यथा अणु
		qh = qh_alloc(GFP_ATOMIC);
		अगर (!qh) अणु
			retval = -ENOMEM;
			usb_hcd_unlink_urb_from_ep(hcd, urb);
			qtd_list_मुक्त(&new_qtds);
			जाओ out;
		पूर्ण
		list_add_tail(&qh->qh_list, ep_queue);
		urb->ep->hcpriv = qh;
	पूर्ण

	list_splice_tail(&new_qtds, &qh->qtd_list);
	schedule_ptds(hcd);

out:
	spin_unlock_irqrestore(&priv->lock, spinflags);
	वापस retval;
पूर्ण

अटल व्योम समाप्त_transfer(काष्ठा usb_hcd *hcd, काष्ठा urb *urb,
		काष्ठा isp1760_qh *qh)
अणु
	काष्ठा isp1760_hcd *priv = hcd_to_priv(hcd);
	पूर्णांक skip_map;

	WARN_ON(qh->slot == -1);

	/* We need to क्रमcefully reclaim the slot since some transfers never
	   वापस, e.g. पूर्णांकerrupt transfers and NAKed bulk transfers. */
	अगर (usb_pipecontrol(urb->pipe) || usb_pipebulk(urb->pipe)) अणु
		skip_map = reg_पढ़ो32(hcd->regs, HC_ATL_PTD_SKIPMAP_REG);
		skip_map |= (1 << qh->slot);
		reg_ग_लिखो32(hcd->regs, HC_ATL_PTD_SKIPMAP_REG, skip_map);
		priv->atl_slots[qh->slot].qh = शून्य;
		priv->atl_slots[qh->slot].qtd = शून्य;
	पूर्ण अन्यथा अणु
		skip_map = reg_पढ़ो32(hcd->regs, HC_INT_PTD_SKIPMAP_REG);
		skip_map |= (1 << qh->slot);
		reg_ग_लिखो32(hcd->regs, HC_INT_PTD_SKIPMAP_REG, skip_map);
		priv->पूर्णांक_slots[qh->slot].qh = शून्य;
		priv->पूर्णांक_slots[qh->slot].qtd = शून्य;
	पूर्ण

	qh->slot = -1;
पूर्ण

/*
 * Retire the qtds beginning at 'qtd' and beदीर्घing all to the same urb, समाप्तing
 * any active transfer beदीर्घing to the urb in the process.
 */
अटल व्योम dequeue_urb_from_qtd(काष्ठा usb_hcd *hcd, काष्ठा isp1760_qh *qh,
						काष्ठा isp1760_qtd *qtd)
अणु
	काष्ठा urb *urb;
	पूर्णांक urb_was_running;

	urb = qtd->urb;
	urb_was_running = 0;
	list_क्रम_each_entry_from(qtd, &qh->qtd_list, qtd_list) अणु
		अगर (qtd->urb != urb)
			अवरोध;

		अगर (qtd->status >= QTD_XFER_STARTED)
			urb_was_running = 1;
		अगर (last_qtd_of_urb(qtd, qh) &&
					(qtd->status >= QTD_XFER_COMPLETE))
			urb_was_running = 0;

		अगर (qtd->status == QTD_XFER_STARTED)
			समाप्त_transfer(hcd, urb, qh);
		qtd->status = QTD_RETIRE;
	पूर्ण

	अगर ((urb->dev->speed != USB_SPEED_HIGH) && urb_was_running) अणु
		qh->tt_buffer_dirty = 1;
		अगर (usb_hub_clear_tt_buffer(urb))
			/* Clear failed; let's hope things work anyway */
			qh->tt_buffer_dirty = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक isp1760_urb_dequeue(काष्ठा usb_hcd *hcd, काष्ठा urb *urb,
		पूर्णांक status)
अणु
	काष्ठा isp1760_hcd *priv = hcd_to_priv(hcd);
	अचिन्हित दीर्घ spinflags;
	काष्ठा isp1760_qh *qh;
	काष्ठा isp1760_qtd *qtd;
	पूर्णांक retval = 0;

	spin_lock_irqsave(&priv->lock, spinflags);
	retval = usb_hcd_check_unlink_urb(hcd, urb, status);
	अगर (retval)
		जाओ out;

	qh = urb->ep->hcpriv;
	अगर (!qh) अणु
		retval = -EINVAL;
		जाओ out;
	पूर्ण

	list_क्रम_each_entry(qtd, &qh->qtd_list, qtd_list)
		अगर (qtd->urb == urb) अणु
			dequeue_urb_from_qtd(hcd, qh, qtd);
			list_move(&qtd->qtd_list, &qh->qtd_list);
			अवरोध;
		पूर्ण

	urb->status = status;
	schedule_ptds(hcd);

out:
	spin_unlock_irqrestore(&priv->lock, spinflags);
	वापस retval;
पूर्ण

अटल व्योम isp1760_endpoपूर्णांक_disable(काष्ठा usb_hcd *hcd,
		काष्ठा usb_host_endpoपूर्णांक *ep)
अणु
	काष्ठा isp1760_hcd *priv = hcd_to_priv(hcd);
	अचिन्हित दीर्घ spinflags;
	काष्ठा isp1760_qh *qh, *qh_iter;
	पूर्णांक i;

	spin_lock_irqsave(&priv->lock, spinflags);

	qh = ep->hcpriv;
	अगर (!qh)
		जाओ out;

	WARN_ON(!list_empty(&qh->qtd_list));

	क्रम (i = 0; i < QH_END; i++)
		list_क्रम_each_entry(qh_iter, &priv->qh_list[i], qh_list)
			अगर (qh_iter == qh) अणु
				list_del(&qh_iter->qh_list);
				i = QH_END;
				अवरोध;
			पूर्ण
	qh_मुक्त(qh);
	ep->hcpriv = शून्य;

	schedule_ptds(hcd);

out:
	spin_unlock_irqrestore(&priv->lock, spinflags);
पूर्ण

अटल पूर्णांक isp1760_hub_status_data(काष्ठा usb_hcd *hcd, अक्षर *buf)
अणु
	काष्ठा isp1760_hcd *priv = hcd_to_priv(hcd);
	u32 temp, status = 0;
	u32 mask;
	पूर्णांक retval = 1;
	अचिन्हित दीर्घ flags;

	/* अगर !PM, root hub समयrs won't get shut करोwn ... */
	अगर (!HC_IS_RUNNING(hcd->state))
		वापस 0;

	/* init status to no-changes */
	buf[0] = 0;
	mask = PORT_CSC;

	spin_lock_irqsave(&priv->lock, flags);
	temp = reg_पढ़ो32(hcd->regs, HC_PORTSC1);

	अगर (temp & PORT_OWNER) अणु
		अगर (temp & PORT_CSC) अणु
			temp &= ~PORT_CSC;
			reg_ग_लिखो32(hcd->regs, HC_PORTSC1, temp);
			जाओ करोne;
		पूर्ण
	पूर्ण

	/*
	 * Return status inक्रमmation even क्रम ports with OWNER set.
	 * Otherwise hub_wq wouldn't see the disconnect event when a
	 * high-speed device is चयनed over to the companion
	 * controller by the user.
	 */

	अगर ((temp & mask) != 0
			|| ((temp & PORT_RESUME) != 0
				&& समय_after_eq(jअगरfies,
					priv->reset_करोne))) अणु
		buf [0] |= 1 << (0 + 1);
		status = STS_PCD;
	पूर्ण
	/* FIXME स्वतःsuspend idle root hubs */
करोne:
	spin_unlock_irqrestore(&priv->lock, flags);
	वापस status ? retval : 0;
पूर्ण

अटल व्योम isp1760_hub_descriptor(काष्ठा isp1760_hcd *priv,
		काष्ठा usb_hub_descriptor *desc)
अणु
	पूर्णांक ports = HCS_N_PORTS(priv->hcs_params);
	u16 temp;

	desc->bDescriptorType = USB_DT_HUB;
	/* priv 1.0, 2.3.9 says 20ms max */
	desc->bPwrOn2PwrGood = 10;
	desc->bHubContrCurrent = 0;

	desc->bNbrPorts = ports;
	temp = 1 + (ports / 8);
	desc->bDescLength = 7 + 2 * temp;

	/* ports removable, and usb 1.0 legacy PortPwrCtrlMask */
	स_रखो(&desc->u.hs.DeviceRemovable[0], 0, temp);
	स_रखो(&desc->u.hs.DeviceRemovable[temp], 0xff, temp);

	/* per-port overcurrent reporting */
	temp = HUB_CHAR_INDV_PORT_OCPM;
	अगर (HCS_PPC(priv->hcs_params))
		/* per-port घातer control */
		temp |= HUB_CHAR_INDV_PORT_LPSM;
	अन्यथा
		/* no घातer चयनing */
		temp |= HUB_CHAR_NO_LPSM;
	desc->wHubCharacteristics = cpu_to_le16(temp);
पूर्ण

#घोषणा	PORT_WAKE_BITS	(PORT_WKOC_E|PORT_WKDISC_E|PORT_WKCONN_E)

अटल पूर्णांक check_reset_complete(काष्ठा usb_hcd *hcd, पूर्णांक index,
		पूर्णांक port_status)
अणु
	अगर (!(port_status & PORT_CONNECT))
		वापस port_status;

	/* अगर reset finished and it's still not enabled -- hanकरोff */
	अगर (!(port_status & PORT_PE)) अणु

		dev_info(hcd->self.controller,
					"port %d full speed --> companion\n",
					index + 1);

		port_status |= PORT_OWNER;
		port_status &= ~PORT_RWC_BITS;
		reg_ग_लिखो32(hcd->regs, HC_PORTSC1, port_status);

	पूर्ण अन्यथा
		dev_info(hcd->self.controller, "port %d high speed\n",
								index + 1);

	वापस port_status;
पूर्ण

अटल पूर्णांक isp1760_hub_control(काष्ठा usb_hcd *hcd, u16 typeReq,
		u16 wValue, u16 wIndex, अक्षर *buf, u16 wLength)
अणु
	काष्ठा isp1760_hcd *priv = hcd_to_priv(hcd);
	पूर्णांक ports = HCS_N_PORTS(priv->hcs_params);
	u32 temp, status;
	अचिन्हित दीर्घ flags;
	पूर्णांक retval = 0;

	/*
	 * FIXME:  support SetPortFeatures USB_PORT_FEAT_INDICATOR.
	 * HCS_INDICATOR may say we can change LEDs to off/amber/green.
	 * (track current state ourselves) ... blink क्रम diagnostics,
	 * घातer, "this is the one", etc.  EHCI spec supports this.
	 */

	spin_lock_irqsave(&priv->lock, flags);
	चयन (typeReq) अणु
	हाल ClearHubFeature:
		चयन (wValue) अणु
		हाल C_HUB_LOCAL_POWER:
		हाल C_HUB_OVER_CURRENT:
			/* no hub-wide feature/status flags */
			अवरोध;
		शेष:
			जाओ error;
		पूर्ण
		अवरोध;
	हाल ClearPortFeature:
		अगर (!wIndex || wIndex > ports)
			जाओ error;
		wIndex--;
		temp = reg_पढ़ो32(hcd->regs, HC_PORTSC1);

		/*
		 * Even अगर OWNER is set, so the port is owned by the
		 * companion controller, hub_wq needs to be able to clear
		 * the port-change status bits (especially
		 * USB_PORT_STAT_C_CONNECTION).
		 */

		चयन (wValue) अणु
		हाल USB_PORT_FEAT_ENABLE:
			reg_ग_लिखो32(hcd->regs, HC_PORTSC1, temp & ~PORT_PE);
			अवरोध;
		हाल USB_PORT_FEAT_C_ENABLE:
			/* XXX error? */
			अवरोध;
		हाल USB_PORT_FEAT_SUSPEND:
			अगर (temp & PORT_RESET)
				जाओ error;

			अगर (temp & PORT_SUSPEND) अणु
				अगर ((temp & PORT_PE) == 0)
					जाओ error;
				/* resume संकेतing क्रम 20 msec */
				temp &= ~(PORT_RWC_BITS);
				reg_ग_लिखो32(hcd->regs, HC_PORTSC1,
							temp | PORT_RESUME);
				priv->reset_करोne = jअगरfies +
					msecs_to_jअगरfies(USB_RESUME_TIMEOUT);
			पूर्ण
			अवरोध;
		हाल USB_PORT_FEAT_C_SUSPEND:
			/* we स्वतः-clear this feature */
			अवरोध;
		हाल USB_PORT_FEAT_POWER:
			अगर (HCS_PPC(priv->hcs_params))
				reg_ग_लिखो32(hcd->regs, HC_PORTSC1,
							temp & ~PORT_POWER);
			अवरोध;
		हाल USB_PORT_FEAT_C_CONNECTION:
			reg_ग_लिखो32(hcd->regs, HC_PORTSC1, temp | PORT_CSC);
			अवरोध;
		हाल USB_PORT_FEAT_C_OVER_CURRENT:
			/* XXX error ?*/
			अवरोध;
		हाल USB_PORT_FEAT_C_RESET:
			/* GetPortStatus clears reset */
			अवरोध;
		शेष:
			जाओ error;
		पूर्ण
		reg_पढ़ो32(hcd->regs, HC_USBCMD);
		अवरोध;
	हाल GetHubDescriptor:
		isp1760_hub_descriptor(priv, (काष्ठा usb_hub_descriptor *)
			buf);
		अवरोध;
	हाल GetHubStatus:
		/* no hub-wide feature/status flags */
		स_रखो(buf, 0, 4);
		अवरोध;
	हाल GetPortStatus:
		अगर (!wIndex || wIndex > ports)
			जाओ error;
		wIndex--;
		status = 0;
		temp = reg_पढ़ो32(hcd->regs, HC_PORTSC1);

		/* wPortChange bits */
		अगर (temp & PORT_CSC)
			status |= USB_PORT_STAT_C_CONNECTION << 16;


		/* whoever resumes must GetPortStatus to complete it!! */
		अगर (temp & PORT_RESUME) अणु
			dev_err(hcd->self.controller, "Port resume should be skipped.\n");

			/* Remote Wakeup received? */
			अगर (!priv->reset_करोne) अणु
				/* resume संकेतing क्रम 20 msec */
				priv->reset_करोne = jअगरfies
						+ msecs_to_jअगरfies(20);
				/* check the port again */
				mod_समयr(&hcd->rh_समयr, priv->reset_करोne);
			पूर्ण

			/* resume completed? */
			अन्यथा अगर (समय_after_eq(jअगरfies,
					priv->reset_करोne)) अणु
				status |= USB_PORT_STAT_C_SUSPEND << 16;
				priv->reset_करोne = 0;

				/* stop resume संकेतing */
				temp = reg_पढ़ो32(hcd->regs, HC_PORTSC1);
				reg_ग_लिखो32(hcd->regs, HC_PORTSC1,
					temp & ~(PORT_RWC_BITS | PORT_RESUME));
				retval = handshake(hcd, HC_PORTSC1,
					   PORT_RESUME, 0, 2000 /* 2msec */);
				अगर (retval != 0) अणु
					dev_err(hcd->self.controller,
						"port %d resume error %d\n",
						wIndex + 1, retval);
					जाओ error;
				पूर्ण
				temp &= ~(PORT_SUSPEND|PORT_RESUME|(3<<10));
			पूर्ण
		पूर्ण

		/* whoever resets must GetPortStatus to complete it!! */
		अगर ((temp & PORT_RESET)
				&& समय_after_eq(jअगरfies,
					priv->reset_करोne)) अणु
			status |= USB_PORT_STAT_C_RESET << 16;
			priv->reset_करोne = 0;

			/* क्रमce reset to complete */
			reg_ग_लिखो32(hcd->regs, HC_PORTSC1, temp & ~PORT_RESET);
			/* REVISIT:  some hardware needs 550+ usec to clear
			 * this bit; seems too दीर्घ to spin routinely...
			 */
			retval = handshake(hcd, HC_PORTSC1,
					PORT_RESET, 0, 750);
			अगर (retval != 0) अणु
				dev_err(hcd->self.controller, "port %d reset error %d\n",
						wIndex + 1, retval);
				जाओ error;
			पूर्ण

			/* see what we found out */
			temp = check_reset_complete(hcd, wIndex,
					reg_पढ़ो32(hcd->regs, HC_PORTSC1));
		पूर्ण
		/*
		 * Even अगर OWNER is set, there's no harm letting hub_wq
		 * see the wPortStatus values (they should all be 0 except
		 * क्रम PORT_POWER anyway).
		 */

		अगर (temp & PORT_OWNER)
			dev_err(hcd->self.controller, "PORT_OWNER is set\n");

		अगर (temp & PORT_CONNECT) अणु
			status |= USB_PORT_STAT_CONNECTION;
			/* status may be from पूर्णांकegrated TT */
			status |= USB_PORT_STAT_HIGH_SPEED;
		पूर्ण
		अगर (temp & PORT_PE)
			status |= USB_PORT_STAT_ENABLE;
		अगर (temp & (PORT_SUSPEND|PORT_RESUME))
			status |= USB_PORT_STAT_SUSPEND;
		अगर (temp & PORT_RESET)
			status |= USB_PORT_STAT_RESET;
		अगर (temp & PORT_POWER)
			status |= USB_PORT_STAT_POWER;

		put_unaligned(cpu_to_le32(status), (__le32 *) buf);
		अवरोध;
	हाल SetHubFeature:
		चयन (wValue) अणु
		हाल C_HUB_LOCAL_POWER:
		हाल C_HUB_OVER_CURRENT:
			/* no hub-wide feature/status flags */
			अवरोध;
		शेष:
			जाओ error;
		पूर्ण
		अवरोध;
	हाल SetPortFeature:
		wIndex &= 0xff;
		अगर (!wIndex || wIndex > ports)
			जाओ error;
		wIndex--;
		temp = reg_पढ़ो32(hcd->regs, HC_PORTSC1);
		अगर (temp & PORT_OWNER)
			अवरोध;

/*		temp &= ~PORT_RWC_BITS; */
		चयन (wValue) अणु
		हाल USB_PORT_FEAT_ENABLE:
			reg_ग_लिखो32(hcd->regs, HC_PORTSC1, temp | PORT_PE);
			अवरोध;

		हाल USB_PORT_FEAT_SUSPEND:
			अगर ((temp & PORT_PE) == 0
					|| (temp & PORT_RESET) != 0)
				जाओ error;

			reg_ग_लिखो32(hcd->regs, HC_PORTSC1, temp | PORT_SUSPEND);
			अवरोध;
		हाल USB_PORT_FEAT_POWER:
			अगर (HCS_PPC(priv->hcs_params))
				reg_ग_लिखो32(hcd->regs, HC_PORTSC1,
							temp | PORT_POWER);
			अवरोध;
		हाल USB_PORT_FEAT_RESET:
			अगर (temp & PORT_RESUME)
				जाओ error;
			/* line status bits may report this as low speed,
			 * which can be fine अगर this root hub has a
			 * transaction translator built in.
			 */
			अगर ((temp & (PORT_PE|PORT_CONNECT)) == PORT_CONNECT
					&& PORT_USB11(temp)) अणु
				temp |= PORT_OWNER;
			पूर्ण अन्यथा अणु
				temp |= PORT_RESET;
				temp &= ~PORT_PE;

				/*
				 * caller must रुको, then call GetPortStatus
				 * usb 2.0 spec says 50 ms resets on root
				 */
				priv->reset_करोne = jअगरfies +
					msecs_to_jअगरfies(50);
			पूर्ण
			reg_ग_लिखो32(hcd->regs, HC_PORTSC1, temp);
			अवरोध;
		शेष:
			जाओ error;
		पूर्ण
		reg_पढ़ो32(hcd->regs, HC_USBCMD);
		अवरोध;

	शेष:
error:
		/* "stall" on error */
		retval = -EPIPE;
	पूर्ण
	spin_unlock_irqrestore(&priv->lock, flags);
	वापस retval;
पूर्ण

अटल पूर्णांक isp1760_get_frame(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा isp1760_hcd *priv = hcd_to_priv(hcd);
	u32 fr;

	fr = reg_पढ़ो32(hcd->regs, HC_FRINDEX);
	वापस (fr >> 3) % priv->periodic_size;
पूर्ण

अटल व्योम isp1760_stop(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा isp1760_hcd *priv = hcd_to_priv(hcd);
	u32 temp;

	del_समयr(&errata2_समयr);

	isp1760_hub_control(hcd, ClearPortFeature, USB_PORT_FEAT_POWER,	1,
			शून्य, 0);
	msleep(20);

	spin_lock_irq(&priv->lock);
	ehci_reset(hcd);
	/* Disable IRQ */
	temp = reg_पढ़ो32(hcd->regs, HC_HW_MODE_CTRL);
	reg_ग_लिखो32(hcd->regs, HC_HW_MODE_CTRL, temp &= ~HW_GLOBAL_INTR_EN);
	spin_unlock_irq(&priv->lock);

	reg_ग_लिखो32(hcd->regs, HC_CONFIGFLAG, 0);
पूर्ण

अटल व्योम isp1760_shutकरोwn(काष्ठा usb_hcd *hcd)
अणु
	u32 command, temp;

	isp1760_stop(hcd);
	temp = reg_पढ़ो32(hcd->regs, HC_HW_MODE_CTRL);
	reg_ग_लिखो32(hcd->regs, HC_HW_MODE_CTRL, temp &= ~HW_GLOBAL_INTR_EN);

	command = reg_पढ़ो32(hcd->regs, HC_USBCMD);
	command &= ~CMD_RUN;
	reg_ग_लिखो32(hcd->regs, HC_USBCMD, command);
पूर्ण

अटल व्योम isp1760_clear_tt_buffer_complete(काष्ठा usb_hcd *hcd,
						काष्ठा usb_host_endpoपूर्णांक *ep)
अणु
	काष्ठा isp1760_hcd *priv = hcd_to_priv(hcd);
	काष्ठा isp1760_qh *qh = ep->hcpriv;
	अचिन्हित दीर्घ spinflags;

	अगर (!qh)
		वापस;

	spin_lock_irqsave(&priv->lock, spinflags);
	qh->tt_buffer_dirty = 0;
	schedule_ptds(hcd);
	spin_unlock_irqrestore(&priv->lock, spinflags);
पूर्ण


अटल स्थिर काष्ठा hc_driver isp1760_hc_driver = अणु
	.description		= "isp1760-hcd",
	.product_desc		= "NXP ISP1760 USB Host Controller",
	.hcd_priv_size		= माप(काष्ठा isp1760_hcd *),
	.irq			= isp1760_irq,
	.flags			= HCD_MEMORY | HCD_USB2,
	.reset			= isp1760_hc_setup,
	.start			= isp1760_run,
	.stop			= isp1760_stop,
	.shutकरोwn		= isp1760_shutकरोwn,
	.urb_enqueue		= isp1760_urb_enqueue,
	.urb_dequeue		= isp1760_urb_dequeue,
	.endpoपूर्णांक_disable	= isp1760_endpoपूर्णांक_disable,
	.get_frame_number	= isp1760_get_frame,
	.hub_status_data	= isp1760_hub_status_data,
	.hub_control		= isp1760_hub_control,
	.clear_tt_buffer_complete	= isp1760_clear_tt_buffer_complete,
पूर्ण;

पूर्णांक __init isp1760_init_kmem_once(व्योम)
अणु
	urb_listitem_cachep = kmem_cache_create("isp1760_urb_listitem",
			माप(काष्ठा urb_listitem), 0, SLAB_TEMPORARY |
			SLAB_MEM_SPREAD, शून्य);

	अगर (!urb_listitem_cachep)
		वापस -ENOMEM;

	qtd_cachep = kmem_cache_create("isp1760_qtd",
			माप(काष्ठा isp1760_qtd), 0, SLAB_TEMPORARY |
			SLAB_MEM_SPREAD, शून्य);

	अगर (!qtd_cachep)
		वापस -ENOMEM;

	qh_cachep = kmem_cache_create("isp1760_qh", माप(काष्ठा isp1760_qh),
			0, SLAB_TEMPORARY | SLAB_MEM_SPREAD, शून्य);

	अगर (!qh_cachep) अणु
		kmem_cache_destroy(qtd_cachep);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

व्योम isp1760_deinit_kmem_cache(व्योम)
अणु
	kmem_cache_destroy(qtd_cachep);
	kmem_cache_destroy(qh_cachep);
	kmem_cache_destroy(urb_listitem_cachep);
पूर्ण

पूर्णांक isp1760_hcd_रेजिस्टर(काष्ठा isp1760_hcd *priv, व्योम __iomem *regs,
			 काष्ठा resource *mem, पूर्णांक irq, अचिन्हित दीर्घ irqflags,
			 काष्ठा device *dev)
अणु
	काष्ठा usb_hcd *hcd;
	पूर्णांक ret;

	hcd = usb_create_hcd(&isp1760_hc_driver, dev, dev_name(dev));
	अगर (!hcd)
		वापस -ENOMEM;

	*(काष्ठा isp1760_hcd **)hcd->hcd_priv = priv;

	priv->hcd = hcd;

	init_memory(priv);

	hcd->irq = irq;
	hcd->regs = regs;
	hcd->rsrc_start = mem->start;
	hcd->rsrc_len = resource_size(mem);

	/* This driver करोesn't support wakeup requests */
	hcd->cant_recv_wakeups = 1;

	ret = usb_add_hcd(hcd, irq, irqflags);
	अगर (ret)
		जाओ error;

	device_wakeup_enable(hcd->self.controller);

	वापस 0;

error:
	usb_put_hcd(hcd);
	वापस ret;
पूर्ण

व्योम isp1760_hcd_unरेजिस्टर(काष्ठा isp1760_hcd *priv)
अणु
	अगर (!priv->hcd)
		वापस;

	usb_हटाओ_hcd(priv->hcd);
	usb_put_hcd(priv->hcd);
पूर्ण
