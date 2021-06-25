<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Driver क्रम the Conexant CX23885 PCIe bridge
 *
 *  Copyright (c) 2006 Steven Toth <stoth@linuxtv.org>
 */

#समावेश "cx23885.h"

#समावेश <linux/init.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/kmod.h>
#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <यंत्र/भाग64.h>
#समावेश <linux/firmware.h>

#समावेश "cimax2.h"
#समावेश "altera-ci.h"
#समावेश "cx23888-ir.h"
#समावेश "cx23885-ir.h"
#समावेश "cx23885-av.h"
#समावेश "cx23885-input.h"

MODULE_DESCRIPTION("Driver for cx23885 based TV cards");
MODULE_AUTHOR("Steven Toth <stoth@linuxtv.org>");
MODULE_LICENSE("GPL");
MODULE_VERSION(CX23885_VERSION);

/*
 * Some platक्रमms have been found to require periodic resetting of the DMA
 * engine. Ryzen and XEON platक्रमms are known to be affected. The symptom
 * encountered is "mpeg risc op code error". Only Ryzen platक्रमms employ
 * this workaround अगर the option equals 1. The workaround can be explicitly
 * disabled क्रम all platक्रमms by setting to 0, the workaround can be क्रमced
 * on क्रम any platक्रमm by setting to 2.
 */
अटल अचिन्हित पूर्णांक dma_reset_workaround = 1;
module_param(dma_reset_workaround, पूर्णांक, 0644);
MODULE_PARM_DESC(dma_reset_workaround, "periodic RiSC dma engine reset; 0-force disable, 1-driver detect (default), 2-force enable");

अटल अचिन्हित पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "enable debug messages");

अटल अचिन्हित पूर्णांक card[]  = अणु[0 ... (CX23885_MAXBOARDS - 1)] = UNSET पूर्ण;
module_param_array(card,  पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(card, "card type");

#घोषणा dprपूर्णांकk(level, fmt, arg...)\
	करो अणु अगर (debug >= level)\
		prपूर्णांकk(KERN_DEBUG pr_fmt("%s: " fmt), \
		       __func__, ##arg); \
	पूर्ण जबतक (0)

अटल अचिन्हित पूर्णांक cx23885_devcount;

#घोषणा NO_SYNC_LINE (-1U)

/* FIXME, these allocations will change when
 * analog arrives. The be reviewed.
 * CX23887 Assumptions
 * 1 line = 16 bytes of CDT
 * cmds size = 80
 * cdt size = 16 * linesize
 * iqsize = 64
 * maxlines = 6
 *
 * Address Space:
 * 0x00000000 0x00008fff FIFO clusters
 * 0x00010000 0x000104af Channel Management Data Structures
 * 0x000104b0 0x000104ff Free
 * 0x00010500 0x000108bf 15 channels * iqsize
 * 0x000108c0 0x000108ff Free
 * 0x00010900 0x00010e9f IQ's + Cluster Descriptor Tables
 *                       15 channels * (iqsize + (maxlines * linesize))
 * 0x00010ea0 0x00010xxx Free
 */

अटल काष्ठा sram_channel cx23885_sram_channels[] = अणु
	[SRAM_CH01] = अणु
		.name		= "VID A",
		.cmds_start	= 0x10000,
		.ctrl_start	= 0x10380,
		.cdt		= 0x104c0,
		.fअगरo_start	= 0x40,
		.fअगरo_size	= 0x2800,
		.ptr1_reg	= DMA1_PTR1,
		.ptr2_reg	= DMA1_PTR2,
		.cnt1_reg	= DMA1_CNT1,
		.cnt2_reg	= DMA1_CNT2,
	पूर्ण,
	[SRAM_CH02] = अणु
		.name		= "ch2",
		.cmds_start	= 0x0,
		.ctrl_start	= 0x0,
		.cdt		= 0x0,
		.fअगरo_start	= 0x0,
		.fअगरo_size	= 0x0,
		.ptr1_reg	= DMA2_PTR1,
		.ptr2_reg	= DMA2_PTR2,
		.cnt1_reg	= DMA2_CNT1,
		.cnt2_reg	= DMA2_CNT2,
	पूर्ण,
	[SRAM_CH03] = अणु
		.name		= "TS1 B",
		.cmds_start	= 0x100A0,
		.ctrl_start	= 0x10400,
		.cdt		= 0x10580,
		.fअगरo_start	= 0x5000,
		.fअगरo_size	= 0x1000,
		.ptr1_reg	= DMA3_PTR1,
		.ptr2_reg	= DMA3_PTR2,
		.cnt1_reg	= DMA3_CNT1,
		.cnt2_reg	= DMA3_CNT2,
	पूर्ण,
	[SRAM_CH04] = अणु
		.name		= "ch4",
		.cmds_start	= 0x0,
		.ctrl_start	= 0x0,
		.cdt		= 0x0,
		.fअगरo_start	= 0x0,
		.fअगरo_size	= 0x0,
		.ptr1_reg	= DMA4_PTR1,
		.ptr2_reg	= DMA4_PTR2,
		.cnt1_reg	= DMA4_CNT1,
		.cnt2_reg	= DMA4_CNT2,
	पूर्ण,
	[SRAM_CH05] = अणु
		.name		= "ch5",
		.cmds_start	= 0x0,
		.ctrl_start	= 0x0,
		.cdt		= 0x0,
		.fअगरo_start	= 0x0,
		.fअगरo_size	= 0x0,
		.ptr1_reg	= DMA5_PTR1,
		.ptr2_reg	= DMA5_PTR2,
		.cnt1_reg	= DMA5_CNT1,
		.cnt2_reg	= DMA5_CNT2,
	पूर्ण,
	[SRAM_CH06] = अणु
		.name		= "TS2 C",
		.cmds_start	= 0x10140,
		.ctrl_start	= 0x10440,
		.cdt		= 0x105e0,
		.fअगरo_start	= 0x6000,
		.fअगरo_size	= 0x1000,
		.ptr1_reg	= DMA5_PTR1,
		.ptr2_reg	= DMA5_PTR2,
		.cnt1_reg	= DMA5_CNT1,
		.cnt2_reg	= DMA5_CNT2,
	पूर्ण,
	[SRAM_CH07] = अणु
		.name		= "TV Audio",
		.cmds_start	= 0x10190,
		.ctrl_start	= 0x10480,
		.cdt		= 0x10a00,
		.fअगरo_start	= 0x7000,
		.fअगरo_size	= 0x1000,
		.ptr1_reg	= DMA6_PTR1,
		.ptr2_reg	= DMA6_PTR2,
		.cnt1_reg	= DMA6_CNT1,
		.cnt2_reg	= DMA6_CNT2,
	पूर्ण,
	[SRAM_CH08] = अणु
		.name		= "ch8",
		.cmds_start	= 0x0,
		.ctrl_start	= 0x0,
		.cdt		= 0x0,
		.fअगरo_start	= 0x0,
		.fअगरo_size	= 0x0,
		.ptr1_reg	= DMA7_PTR1,
		.ptr2_reg	= DMA7_PTR2,
		.cnt1_reg	= DMA7_CNT1,
		.cnt2_reg	= DMA7_CNT2,
	पूर्ण,
	[SRAM_CH09] = अणु
		.name		= "ch9",
		.cmds_start	= 0x0,
		.ctrl_start	= 0x0,
		.cdt		= 0x0,
		.fअगरo_start	= 0x0,
		.fअगरo_size	= 0x0,
		.ptr1_reg	= DMA8_PTR1,
		.ptr2_reg	= DMA8_PTR2,
		.cnt1_reg	= DMA8_CNT1,
		.cnt2_reg	= DMA8_CNT2,
	पूर्ण,
पूर्ण;

अटल काष्ठा sram_channel cx23887_sram_channels[] = अणु
	[SRAM_CH01] = अणु
		.name		= "VID A",
		.cmds_start	= 0x10000,
		.ctrl_start	= 0x105b0,
		.cdt		= 0x107b0,
		.fअगरo_start	= 0x40,
		.fअगरo_size	= 0x2800,
		.ptr1_reg	= DMA1_PTR1,
		.ptr2_reg	= DMA1_PTR2,
		.cnt1_reg	= DMA1_CNT1,
		.cnt2_reg	= DMA1_CNT2,
	पूर्ण,
	[SRAM_CH02] = अणु
		.name		= "VID A (VBI)",
		.cmds_start	= 0x10050,
		.ctrl_start	= 0x105F0,
		.cdt		= 0x10810,
		.fअगरo_start	= 0x3000,
		.fअगरo_size	= 0x1000,
		.ptr1_reg	= DMA2_PTR1,
		.ptr2_reg	= DMA2_PTR2,
		.cnt1_reg	= DMA2_CNT1,
		.cnt2_reg	= DMA2_CNT2,
	पूर्ण,
	[SRAM_CH03] = अणु
		.name		= "TS1 B",
		.cmds_start	= 0x100A0,
		.ctrl_start	= 0x10630,
		.cdt		= 0x10870,
		.fअगरo_start	= 0x5000,
		.fअगरo_size	= 0x1000,
		.ptr1_reg	= DMA3_PTR1,
		.ptr2_reg	= DMA3_PTR2,
		.cnt1_reg	= DMA3_CNT1,
		.cnt2_reg	= DMA3_CNT2,
	पूर्ण,
	[SRAM_CH04] = अणु
		.name		= "ch4",
		.cmds_start	= 0x0,
		.ctrl_start	= 0x0,
		.cdt		= 0x0,
		.fअगरo_start	= 0x0,
		.fअगरo_size	= 0x0,
		.ptr1_reg	= DMA4_PTR1,
		.ptr2_reg	= DMA4_PTR2,
		.cnt1_reg	= DMA4_CNT1,
		.cnt2_reg	= DMA4_CNT2,
	पूर्ण,
	[SRAM_CH05] = अणु
		.name		= "ch5",
		.cmds_start	= 0x0,
		.ctrl_start	= 0x0,
		.cdt		= 0x0,
		.fअगरo_start	= 0x0,
		.fअगरo_size	= 0x0,
		.ptr1_reg	= DMA5_PTR1,
		.ptr2_reg	= DMA5_PTR2,
		.cnt1_reg	= DMA5_CNT1,
		.cnt2_reg	= DMA5_CNT2,
	पूर्ण,
	[SRAM_CH06] = अणु
		.name		= "TS2 C",
		.cmds_start	= 0x10140,
		.ctrl_start	= 0x10670,
		.cdt		= 0x108d0,
		.fअगरo_start	= 0x6000,
		.fअगरo_size	= 0x1000,
		.ptr1_reg	= DMA5_PTR1,
		.ptr2_reg	= DMA5_PTR2,
		.cnt1_reg	= DMA5_CNT1,
		.cnt2_reg	= DMA5_CNT2,
	पूर्ण,
	[SRAM_CH07] = अणु
		.name		= "TV Audio",
		.cmds_start	= 0x10190,
		.ctrl_start	= 0x106B0,
		.cdt		= 0x10930,
		.fअगरo_start	= 0x7000,
		.fअगरo_size	= 0x1000,
		.ptr1_reg	= DMA6_PTR1,
		.ptr2_reg	= DMA6_PTR2,
		.cnt1_reg	= DMA6_CNT1,
		.cnt2_reg	= DMA6_CNT2,
	पूर्ण,
	[SRAM_CH08] = अणु
		.name		= "ch8",
		.cmds_start	= 0x0,
		.ctrl_start	= 0x0,
		.cdt		= 0x0,
		.fअगरo_start	= 0x0,
		.fअगरo_size	= 0x0,
		.ptr1_reg	= DMA7_PTR1,
		.ptr2_reg	= DMA7_PTR2,
		.cnt1_reg	= DMA7_CNT1,
		.cnt2_reg	= DMA7_CNT2,
	पूर्ण,
	[SRAM_CH09] = अणु
		.name		= "ch9",
		.cmds_start	= 0x0,
		.ctrl_start	= 0x0,
		.cdt		= 0x0,
		.fअगरo_start	= 0x0,
		.fअगरo_size	= 0x0,
		.ptr1_reg	= DMA8_PTR1,
		.ptr2_reg	= DMA8_PTR2,
		.cnt1_reg	= DMA8_CNT1,
		.cnt2_reg	= DMA8_CNT2,
	पूर्ण,
पूर्ण;

अटल व्योम cx23885_irq_add(काष्ठा cx23885_dev *dev, u32 mask)
अणु
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&dev->pci_irqmask_lock, flags);

	dev->pci_irqmask |= mask;

	spin_unlock_irqrestore(&dev->pci_irqmask_lock, flags);
पूर्ण

व्योम cx23885_irq_add_enable(काष्ठा cx23885_dev *dev, u32 mask)
अणु
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&dev->pci_irqmask_lock, flags);

	dev->pci_irqmask |= mask;
	cx_set(PCI_INT_MSK, mask);

	spin_unlock_irqrestore(&dev->pci_irqmask_lock, flags);
पूर्ण

व्योम cx23885_irq_enable(काष्ठा cx23885_dev *dev, u32 mask)
अणु
	u32 v;
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&dev->pci_irqmask_lock, flags);

	v = mask & dev->pci_irqmask;
	अगर (v)
		cx_set(PCI_INT_MSK, v);

	spin_unlock_irqrestore(&dev->pci_irqmask_lock, flags);
पूर्ण

अटल अंतरभूत व्योम cx23885_irq_enable_all(काष्ठा cx23885_dev *dev)
अणु
	cx23885_irq_enable(dev, 0xffffffff);
पूर्ण

व्योम cx23885_irq_disable(काष्ठा cx23885_dev *dev, u32 mask)
अणु
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&dev->pci_irqmask_lock, flags);

	cx_clear(PCI_INT_MSK, mask);

	spin_unlock_irqrestore(&dev->pci_irqmask_lock, flags);
पूर्ण

अटल अंतरभूत व्योम cx23885_irq_disable_all(काष्ठा cx23885_dev *dev)
अणु
	cx23885_irq_disable(dev, 0xffffffff);
पूर्ण

व्योम cx23885_irq_हटाओ(काष्ठा cx23885_dev *dev, u32 mask)
अणु
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&dev->pci_irqmask_lock, flags);

	dev->pci_irqmask &= ~mask;
	cx_clear(PCI_INT_MSK, mask);

	spin_unlock_irqrestore(&dev->pci_irqmask_lock, flags);
पूर्ण

अटल u32 cx23885_irq_get_mask(काष्ठा cx23885_dev *dev)
अणु
	u32 v;
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&dev->pci_irqmask_lock, flags);

	v = cx_पढ़ो(PCI_INT_MSK);

	spin_unlock_irqrestore(&dev->pci_irqmask_lock, flags);
	वापस v;
पूर्ण

अटल पूर्णांक cx23885_risc_decode(u32 risc)
अणु
	अटल अक्षर *instr[16] = अणु
		[RISC_SYNC    >> 28] = "sync",
		[RISC_WRITE   >> 28] = "write",
		[RISC_WRITEC  >> 28] = "writec",
		[RISC_READ    >> 28] = "read",
		[RISC_READC   >> 28] = "readc",
		[RISC_JUMP    >> 28] = "jump",
		[RISC_SKIP    >> 28] = "skip",
		[RISC_WRITERM >> 28] = "writerm",
		[RISC_WRITECM >> 28] = "writecm",
		[RISC_WRITECR >> 28] = "writecr",
	पूर्ण;
	अटल पूर्णांक incr[16] = अणु
		[RISC_WRITE   >> 28] = 3,
		[RISC_JUMP    >> 28] = 3,
		[RISC_SKIP    >> 28] = 1,
		[RISC_SYNC    >> 28] = 1,
		[RISC_WRITERM >> 28] = 3,
		[RISC_WRITECM >> 28] = 3,
		[RISC_WRITECR >> 28] = 4,
	पूर्ण;
	अटल अक्षर *bits[] = अणु
		"12",   "13",   "14",   "resync",
		"cnt0", "cnt1", "18",   "19",
		"20",   "21",   "22",   "23",
		"irq1", "irq2", "eol",  "sol",
	पूर्ण;
	पूर्णांक i;

	prपूर्णांकk(KERN_DEBUG "0x%08x [ %s", risc,
	       instr[risc >> 28] ? instr[risc >> 28] : "INVALID");
	क्रम (i = ARRAY_SIZE(bits) - 1; i >= 0; i--)
		अगर (risc & (1 << (i + 12)))
			pr_cont(" %s", bits[i]);
	pr_cont(" count=%d ]\n", risc & 0xfff);
	वापस incr[risc >> 28] ? incr[risc >> 28] : 1;
पूर्ण

अटल व्योम cx23885_wakeup(काष्ठा cx23885_tsport *port,
			   काष्ठा cx23885_dmaqueue *q, u32 count)
अणु
	काष्ठा cx23885_buffer *buf;
	पूर्णांक count_delta;
	पूर्णांक max_buf_करोne = 5; /* service maximum five buffers */

	करो अणु
		अगर (list_empty(&q->active))
			वापस;
		buf = list_entry(q->active.next,
				 काष्ठा cx23885_buffer, queue);

		buf->vb.vb2_buf.बारtamp = kसमय_get_ns();
		buf->vb.sequence = q->count++;
		अगर (count != (q->count % 65536)) अणु
			dprपूर्णांकk(1, "[%p/%d] wakeup reg=%d buf=%d\n", buf,
				buf->vb.vb2_buf.index, count, q->count);
		पूर्ण अन्यथा अणु
			dprपूर्णांकk(7, "[%p/%d] wakeup reg=%d buf=%d\n", buf,
				buf->vb.vb2_buf.index, count, q->count);
		पूर्ण
		list_del(&buf->queue);
		vb2_buffer_करोne(&buf->vb.vb2_buf, VB2_BUF_STATE_DONE);
		max_buf_करोne--;
		/* count रेजिस्टर is 16 bits so apply modulo appropriately */
		count_delta = ((पूर्णांक)count - (पूर्णांक)(q->count % 65536));
	पूर्ण जबतक ((count_delta > 0) && (max_buf_करोne > 0));
पूर्ण

पूर्णांक cx23885_sram_channel_setup(काष्ठा cx23885_dev *dev,
				      काष्ठा sram_channel *ch,
				      अचिन्हित पूर्णांक bpl, u32 risc)
अणु
	अचिन्हित पूर्णांक i, lines;
	u32 cdt;

	अगर (ch->cmds_start == 0) अणु
		dprपूर्णांकk(1, "%s() Erasing channel [%s]\n", __func__,
			ch->name);
		cx_ग_लिखो(ch->ptr1_reg, 0);
		cx_ग_लिखो(ch->ptr2_reg, 0);
		cx_ग_लिखो(ch->cnt2_reg, 0);
		cx_ग_लिखो(ch->cnt1_reg, 0);
		वापस 0;
	पूर्ण अन्यथा अणु
		dprपूर्णांकk(1, "%s() Configuring channel [%s]\n", __func__,
			ch->name);
	पूर्ण

	bpl   = (bpl + 7) & ~7; /* alignment */
	cdt   = ch->cdt;
	lines = ch->fअगरo_size / bpl;
	अगर (lines > 6)
		lines = 6;
	BUG_ON(lines < 2);

	cx_ग_लिखो(8 + 0, RISC_JUMP | RISC_CNT_RESET);
	cx_ग_लिखो(8 + 4, 12);
	cx_ग_लिखो(8 + 8, 0);

	/* ग_लिखो CDT */
	क्रम (i = 0; i < lines; i++) अणु
		dprपूर्णांकk(2, "%s() 0x%08x <- 0x%08x\n", __func__, cdt + 16*i,
			ch->fअगरo_start + bpl*i);
		cx_ग_लिखो(cdt + 16*i, ch->fअगरo_start + bpl*i);
		cx_ग_लिखो(cdt + 16*i +  4, 0);
		cx_ग_लिखो(cdt + 16*i +  8, 0);
		cx_ग_लिखो(cdt + 16*i + 12, 0);
	पूर्ण

	/* ग_लिखो CMDS */
	अगर (ch->jumponly)
		cx_ग_लिखो(ch->cmds_start + 0, 8);
	अन्यथा
		cx_ग_लिखो(ch->cmds_start + 0, risc);
	cx_ग_लिखो(ch->cmds_start +  4, 0); /* 64 bits 63-32 */
	cx_ग_लिखो(ch->cmds_start +  8, cdt);
	cx_ग_लिखो(ch->cmds_start + 12, (lines*16) >> 3);
	cx_ग_लिखो(ch->cmds_start + 16, ch->ctrl_start);
	अगर (ch->jumponly)
		cx_ग_लिखो(ch->cmds_start + 20, 0x80000000 | (64 >> 2));
	अन्यथा
		cx_ग_लिखो(ch->cmds_start + 20, 64 >> 2);
	क्रम (i = 24; i < 80; i += 4)
		cx_ग_लिखो(ch->cmds_start + i, 0);

	/* fill रेजिस्टरs */
	cx_ग_लिखो(ch->ptr1_reg, ch->fअगरo_start);
	cx_ग_लिखो(ch->ptr2_reg, cdt);
	cx_ग_लिखो(ch->cnt2_reg, (lines*16) >> 3);
	cx_ग_लिखो(ch->cnt1_reg, (bpl >> 3) - 1);

	dprपूर्णांकk(2, "[bridge %d] sram setup %s: bpl=%d lines=%d\n",
		dev->bridge,
		ch->name,
		bpl,
		lines);

	वापस 0;
पूर्ण

व्योम cx23885_sram_channel_dump(काष्ठा cx23885_dev *dev,
				      काष्ठा sram_channel *ch)
अणु
	अटल अक्षर *name[] = अणु
		"init risc lo",
		"init risc hi",
		"cdt base",
		"cdt size",
		"iq base",
		"iq size",
		"risc pc lo",
		"risc pc hi",
		"iq wr ptr",
		"iq rd ptr",
		"cdt current",
		"pci target lo",
		"pci target hi",
		"line / byte",
	पूर्ण;
	u32 risc;
	अचिन्हित पूर्णांक i, j, n;

	pr_warn("%s: %s - dma channel status dump\n",
		dev->name, ch->name);
	क्रम (i = 0; i < ARRAY_SIZE(name); i++)
		pr_warn("%s:   cmds: %-15s: 0x%08x\n",
			dev->name, name[i],
			cx_पढ़ो(ch->cmds_start + 4*i));

	क्रम (i = 0; i < 4; i++) अणु
		risc = cx_पढ़ो(ch->cmds_start + 4 * (i + 14));
		pr_warn("%s:   risc%d: ", dev->name, i);
		cx23885_risc_decode(risc);
	पूर्ण
	क्रम (i = 0; i < (64 >> 2); i += n) अणु
		risc = cx_पढ़ो(ch->ctrl_start + 4 * i);
		/* No consideration क्रम bits 63-32 */

		pr_warn("%s:   (0x%08x) iq %x: ", dev->name,
			ch->ctrl_start + 4 * i, i);
		n = cx23885_risc_decode(risc);
		क्रम (j = 1; j < n; j++) अणु
			risc = cx_पढ़ो(ch->ctrl_start + 4 * (i + j));
			pr_warn("%s:   iq %x: 0x%08x [ arg #%d ]\n",
				dev->name, i+j, risc, j);
		पूर्ण
	पूर्ण

	pr_warn("%s: fifo: 0x%08x -> 0x%x\n",
		dev->name, ch->fअगरo_start, ch->fअगरo_start+ch->fअगरo_size);
	pr_warn("%s: ctrl: 0x%08x -> 0x%x\n",
		dev->name, ch->ctrl_start, ch->ctrl_start + 6*16);
	pr_warn("%s:   ptr1_reg: 0x%08x\n",
		dev->name, cx_पढ़ो(ch->ptr1_reg));
	pr_warn("%s:   ptr2_reg: 0x%08x\n",
		dev->name, cx_पढ़ो(ch->ptr2_reg));
	pr_warn("%s:   cnt1_reg: 0x%08x\n",
		dev->name, cx_पढ़ो(ch->cnt1_reg));
	pr_warn("%s:   cnt2_reg: 0x%08x\n",
		dev->name, cx_पढ़ो(ch->cnt2_reg));
पूर्ण

अटल व्योम cx23885_risc_disयंत्र(काष्ठा cx23885_tsport *port,
				काष्ठा cx23885_riscmem *risc)
अणु
	काष्ठा cx23885_dev *dev = port->dev;
	अचिन्हित पूर्णांक i, j, n;

	pr_info("%s: risc disasm: %p [dma=0x%08lx]\n",
	       dev->name, risc->cpu, (अचिन्हित दीर्घ)risc->dma);
	क्रम (i = 0; i < (risc->size >> 2); i += n) अणु
		pr_info("%s:   %04d: ", dev->name, i);
		n = cx23885_risc_decode(le32_to_cpu(risc->cpu[i]));
		क्रम (j = 1; j < n; j++)
			pr_info("%s:   %04d: 0x%08x [ arg #%d ]\n",
				dev->name, i + j, risc->cpu[i + j], j);
		अगर (risc->cpu[i] == cpu_to_le32(RISC_JUMP))
			अवरोध;
	पूर्ण
पूर्ण

अटल व्योम cx23885_clear_bridge_error(काष्ठा cx23885_dev *dev)
अणु
	uपूर्णांक32_t reg1_val, reg2_val;

	अगर (!dev->need_dma_reset)
		वापस;

	reg1_val = cx_पढ़ो(TC_REQ); /* पढ़ो-only */
	reg2_val = cx_पढ़ो(TC_REQ_SET);

	अगर (reg1_val && reg2_val) अणु
		cx_ग_लिखो(TC_REQ, reg1_val);
		cx_ग_लिखो(TC_REQ_SET, reg2_val);
		cx_पढ़ो(VID_B_DMA);
		cx_पढ़ो(VBI_B_DMA);
		cx_पढ़ो(VID_C_DMA);
		cx_पढ़ो(VBI_C_DMA);

		dev_info(&dev->pci->dev,
			"dma in progress detected 0x%08x 0x%08x, clearing\n",
			reg1_val, reg2_val);
	पूर्ण
पूर्ण

अटल व्योम cx23885_shutकरोwn(काष्ठा cx23885_dev *dev)
अणु
	/* disable RISC controller */
	cx_ग_लिखो(DEV_CNTRL2, 0);

	/* Disable all IR activity */
	cx_ग_लिखो(IR_CNTRL_REG, 0);

	/* Disable Video A/B activity */
	cx_ग_लिखो(VID_A_DMA_CTL, 0);
	cx_ग_लिखो(VID_B_DMA_CTL, 0);
	cx_ग_लिखो(VID_C_DMA_CTL, 0);

	/* Disable Audio activity */
	cx_ग_लिखो(AUD_INT_DMA_CTL, 0);
	cx_ग_लिखो(AUD_EXT_DMA_CTL, 0);

	/* Disable Serial port */
	cx_ग_लिखो(UART_CTL, 0);

	/* Disable Interrupts */
	cx23885_irq_disable_all(dev);
	cx_ग_लिखो(VID_A_INT_MSK, 0);
	cx_ग_लिखो(VID_B_INT_MSK, 0);
	cx_ग_लिखो(VID_C_INT_MSK, 0);
	cx_ग_लिखो(AUDIO_INT_INT_MSK, 0);
	cx_ग_लिखो(AUDIO_EXT_INT_MSK, 0);

पूर्ण

अटल व्योम cx23885_reset(काष्ठा cx23885_dev *dev)
अणु
	dprपूर्णांकk(1, "%s()\n", __func__);

	cx23885_shutकरोwn(dev);

	cx_ग_लिखो(PCI_INT_STAT, 0xffffffff);
	cx_ग_लिखो(VID_A_INT_STAT, 0xffffffff);
	cx_ग_लिखो(VID_B_INT_STAT, 0xffffffff);
	cx_ग_लिखो(VID_C_INT_STAT, 0xffffffff);
	cx_ग_लिखो(AUDIO_INT_INT_STAT, 0xffffffff);
	cx_ग_लिखो(AUDIO_EXT_INT_STAT, 0xffffffff);
	cx_ग_लिखो(CLK_DELAY, cx_पढ़ो(CLK_DELAY) & 0x80000000);
	cx_ग_लिखो(PAD_CTRL, 0x00500300);

	/* clear dma in progress */
	cx23885_clear_bridge_error(dev);
	msleep(100);

	cx23885_sram_channel_setup(dev, &dev->sram_channels[SRAM_CH01],
		720*4, 0);
	cx23885_sram_channel_setup(dev, &dev->sram_channels[SRAM_CH02], 128, 0);
	cx23885_sram_channel_setup(dev, &dev->sram_channels[SRAM_CH03],
		188*4, 0);
	cx23885_sram_channel_setup(dev, &dev->sram_channels[SRAM_CH04], 128, 0);
	cx23885_sram_channel_setup(dev, &dev->sram_channels[SRAM_CH05], 128, 0);
	cx23885_sram_channel_setup(dev, &dev->sram_channels[SRAM_CH06],
		188*4, 0);
	cx23885_sram_channel_setup(dev, &dev->sram_channels[SRAM_CH07], 128, 0);
	cx23885_sram_channel_setup(dev, &dev->sram_channels[SRAM_CH08], 128, 0);
	cx23885_sram_channel_setup(dev, &dev->sram_channels[SRAM_CH09], 128, 0);

	cx23885_gpio_setup(dev);

	cx23885_irq_get_mask(dev);

	/* clear dma in progress */
	cx23885_clear_bridge_error(dev);
पूर्ण


अटल पूर्णांक cx23885_pci_quirks(काष्ठा cx23885_dev *dev)
अणु
	dprपूर्णांकk(1, "%s()\n", __func__);

	/* The cx23885 bridge has a weird bug which causes NMI to be निश्चितed
	 * when DMA begins अगर RDR_TLCTL0 bit4 is not cleared. It करोes not
	 * occur on the cx23887 bridge.
	 */
	अगर (dev->bridge == CX23885_BRIDGE_885)
		cx_clear(RDR_TLCTL0, 1 << 4);

	/* clear dma in progress */
	cx23885_clear_bridge_error(dev);
	वापस 0;
पूर्ण

अटल पूर्णांक get_resources(काष्ठा cx23885_dev *dev)
अणु
	अगर (request_mem_region(pci_resource_start(dev->pci, 0),
			       pci_resource_len(dev->pci, 0),
			       dev->name))
		वापस 0;

	pr_err("%s: can't get MMIO memory @ 0x%llx\n",
	       dev->name, (अचिन्हित दीर्घ दीर्घ)pci_resource_start(dev->pci, 0));

	वापस -EBUSY;
पूर्ण

अटल पूर्णांक cx23885_init_tsport(काष्ठा cx23885_dev *dev,
	काष्ठा cx23885_tsport *port, पूर्णांक portno)
अणु
	dprपूर्णांकk(1, "%s(portno=%d)\n", __func__, portno);

	/* Transport bus init dma queue  - Common settings */
	port->dma_ctl_val        = 0x11; /* Enable RISC controller and Fअगरo */
	port->ts_पूर्णांक_msk_val     = 0x1111; /* TS port bits क्रम RISC */
	port->vld_misc_val       = 0x0;
	port->hw_sop_ctrl_val    = (0x47 << 16 | 188 << 4);

	spin_lock_init(&port->slock);
	port->dev = dev;
	port->nr = portno;

	INIT_LIST_HEAD(&port->mpegq.active);
	mutex_init(&port->frontends.lock);
	INIT_LIST_HEAD(&port->frontends.felist);
	port->frontends.active_fe_id = 0;

	/* This should be hardcoded allow a single frontend
	 * attachment to this tsport, keeping the -dvb.c
	 * code clean and safe.
	 */
	अगर (!port->num_frontends)
		port->num_frontends = 1;

	चयन (portno) अणु
	हाल 1:
		port->reg_gpcnt          = VID_B_GPCNT;
		port->reg_gpcnt_ctl      = VID_B_GPCNT_CTL;
		port->reg_dma_ctl        = VID_B_DMA_CTL;
		port->reg_lngth          = VID_B_LNGTH;
		port->reg_hw_sop_ctrl    = VID_B_HW_SOP_CTL;
		port->reg_gen_ctrl       = VID_B_GEN_CTL;
		port->reg_bd_pkt_status  = VID_B_BD_PKT_STATUS;
		port->reg_sop_status     = VID_B_SOP_STATUS;
		port->reg_fअगरo_ovfl_stat = VID_B_FIFO_OVFL_STAT;
		port->reg_vld_misc       = VID_B_VLD_MISC;
		port->reg_ts_clk_en      = VID_B_TS_CLK_EN;
		port->reg_src_sel        = VID_B_SRC_SEL;
		port->reg_ts_पूर्णांक_msk     = VID_B_INT_MSK;
		port->reg_ts_पूर्णांक_stat    = VID_B_INT_STAT;
		port->sram_chno          = SRAM_CH03; /* VID_B */
		port->pci_irqmask        = 0x02; /* VID_B bit1 */
		अवरोध;
	हाल 2:
		port->reg_gpcnt          = VID_C_GPCNT;
		port->reg_gpcnt_ctl      = VID_C_GPCNT_CTL;
		port->reg_dma_ctl        = VID_C_DMA_CTL;
		port->reg_lngth          = VID_C_LNGTH;
		port->reg_hw_sop_ctrl    = VID_C_HW_SOP_CTL;
		port->reg_gen_ctrl       = VID_C_GEN_CTL;
		port->reg_bd_pkt_status  = VID_C_BD_PKT_STATUS;
		port->reg_sop_status     = VID_C_SOP_STATUS;
		port->reg_fअगरo_ovfl_stat = VID_C_FIFO_OVFL_STAT;
		port->reg_vld_misc       = VID_C_VLD_MISC;
		port->reg_ts_clk_en      = VID_C_TS_CLK_EN;
		port->reg_src_sel        = 0;
		port->reg_ts_पूर्णांक_msk     = VID_C_INT_MSK;
		port->reg_ts_पूर्णांक_stat    = VID_C_INT_STAT;
		port->sram_chno          = SRAM_CH06; /* VID_C */
		port->pci_irqmask        = 0x04; /* VID_C bit2 */
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम cx23885_dev_checkrevision(काष्ठा cx23885_dev *dev)
अणु
	चयन (cx_पढ़ो(RDR_CFG2) & 0xff) अणु
	हाल 0x00:
		/* cx23885 */
		dev->hwrevision = 0xa0;
		अवरोध;
	हाल 0x01:
		/* CX23885-12Z */
		dev->hwrevision = 0xa1;
		अवरोध;
	हाल 0x02:
		/* CX23885-13Z/14Z */
		dev->hwrevision = 0xb0;
		अवरोध;
	हाल 0x03:
		अगर (dev->pci->device == 0x8880) अणु
			/* CX23888-21Z/22Z */
			dev->hwrevision = 0xc0;
		पूर्ण अन्यथा अणु
			/* CX23885-14Z */
			dev->hwrevision = 0xa4;
		पूर्ण
		अवरोध;
	हाल 0x04:
		अगर (dev->pci->device == 0x8880) अणु
			/* CX23888-31Z */
			dev->hwrevision = 0xd0;
		पूर्ण अन्यथा अणु
			/* CX23885-15Z, CX23888-31Z */
			dev->hwrevision = 0xa5;
		पूर्ण
		अवरोध;
	हाल 0x0e:
		/* CX23887-15Z */
		dev->hwrevision = 0xc0;
		अवरोध;
	हाल 0x0f:
		/* CX23887-14Z */
		dev->hwrevision = 0xb1;
		अवरोध;
	शेष:
		pr_err("%s() New hardware revision found 0x%x\n",
		       __func__, dev->hwrevision);
	पूर्ण
	अगर (dev->hwrevision)
		pr_info("%s() Hardware revision = 0x%02x\n",
			__func__, dev->hwrevision);
	अन्यथा
		pr_err("%s() Hardware revision unknown 0x%x\n",
		       __func__, dev->hwrevision);
पूर्ण

/* Find the first v4l2_subdev member of the group id in hw */
काष्ठा v4l2_subdev *cx23885_find_hw(काष्ठा cx23885_dev *dev, u32 hw)
अणु
	काष्ठा v4l2_subdev *result = शून्य;
	काष्ठा v4l2_subdev *sd;

	spin_lock(&dev->v4l2_dev.lock);
	v4l2_device_क्रम_each_subdev(sd, &dev->v4l2_dev) अणु
		अगर (sd->grp_id == hw) अणु
			result = sd;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock(&dev->v4l2_dev.lock);
	वापस result;
पूर्ण

अटल पूर्णांक cx23885_dev_setup(काष्ठा cx23885_dev *dev)
अणु
	पूर्णांक i;

	spin_lock_init(&dev->pci_irqmask_lock);
	spin_lock_init(&dev->slock);

	mutex_init(&dev->lock);
	mutex_init(&dev->gpio_lock);

	atomic_inc(&dev->refcount);

	dev->nr = cx23885_devcount++;
	प्र_लिखो(dev->name, "cx23885[%d]", dev->nr);

	/* Configure the पूर्णांकernal memory */
	अगर (dev->pci->device == 0x8880) अणु
		/* Could be 887 or 888, assume an 888 शेष */
		dev->bridge = CX23885_BRIDGE_888;
		/* Apply a sensible घड़ी frequency क्रम the PCIe bridge */
		dev->clk_freq = 50000000;
		dev->sram_channels = cx23887_sram_channels;
	पूर्ण अन्यथा
	अगर (dev->pci->device == 0x8852) अणु
		dev->bridge = CX23885_BRIDGE_885;
		/* Apply a sensible घड़ी frequency क्रम the PCIe bridge */
		dev->clk_freq = 28000000;
		dev->sram_channels = cx23885_sram_channels;
	पूर्ण अन्यथा
		BUG();

	dprपूर्णांकk(1, "%s() Memory configured for PCIe bridge type %d\n",
		__func__, dev->bridge);

	/* board config */
	dev->board = UNSET;
	अगर (card[dev->nr] < cx23885_bcount)
		dev->board = card[dev->nr];
	क्रम (i = 0; UNSET == dev->board  &&  i < cx23885_idcount; i++)
		अगर (dev->pci->subप्रणाली_venकरोr == cx23885_subids[i].subvenकरोr &&
		    dev->pci->subप्रणाली_device == cx23885_subids[i].subdevice)
			dev->board = cx23885_subids[i].card;
	अगर (UNSET == dev->board) अणु
		dev->board = CX23885_BOARD_UNKNOWN;
		cx23885_card_list(dev);
	पूर्ण

	अगर (dev->pci->device == 0x8852) अणु
		/* no DIF on cx23885, so no analog tuner support possible */
		अगर (dev->board == CX23885_BOARD_HAUPPAUGE_QUADHD_ATSC)
			dev->board = CX23885_BOARD_HAUPPAUGE_QUADHD_ATSC_885;
		अन्यथा अगर (dev->board == CX23885_BOARD_HAUPPAUGE_QUADHD_DVB)
			dev->board = CX23885_BOARD_HAUPPAUGE_QUADHD_DVB_885;
	पूर्ण

	/* If the user specअगरic a clk freq override, apply it */
	अगर (cx23885_boards[dev->board].clk_freq > 0)
		dev->clk_freq = cx23885_boards[dev->board].clk_freq;

	अगर (dev->board == CX23885_BOARD_HAUPPAUGE_IMPACTVCBE &&
		dev->pci->subप्रणाली_device == 0x7137) अणु
		/* Hauppauge ImpactVCBe device ID 0x7137 is populated
		 * with an 888, and a 25Mhz crystal, instead of the
		 * usual third overtone 50Mhz. The शेष घड़ी rate must
		 * be overridden so the cx25840 is properly configured
		 */
		dev->clk_freq = 25000000;
	पूर्ण

	dev->pci_bus  = dev->pci->bus->number;
	dev->pci_slot = PCI_SLOT(dev->pci->devfn);
	cx23885_irq_add(dev, 0x001f00);

	/* External Master 1 Bus */
	dev->i2c_bus[0].nr = 0;
	dev->i2c_bus[0].dev = dev;
	dev->i2c_bus[0].reg_stat  = I2C1_STAT;
	dev->i2c_bus[0].reg_ctrl  = I2C1_CTRL;
	dev->i2c_bus[0].reg_addr  = I2C1_ADDR;
	dev->i2c_bus[0].reg_rdata = I2C1_RDATA;
	dev->i2c_bus[0].reg_wdata = I2C1_WDATA;
	dev->i2c_bus[0].i2c_period = (0x9d << 24); /* 100kHz */

	/* External Master 2 Bus */
	dev->i2c_bus[1].nr = 1;
	dev->i2c_bus[1].dev = dev;
	dev->i2c_bus[1].reg_stat  = I2C2_STAT;
	dev->i2c_bus[1].reg_ctrl  = I2C2_CTRL;
	dev->i2c_bus[1].reg_addr  = I2C2_ADDR;
	dev->i2c_bus[1].reg_rdata = I2C2_RDATA;
	dev->i2c_bus[1].reg_wdata = I2C2_WDATA;
	dev->i2c_bus[1].i2c_period = (0x9d << 24); /* 100kHz */

	/* Internal Master 3 Bus */
	dev->i2c_bus[2].nr = 2;
	dev->i2c_bus[2].dev = dev;
	dev->i2c_bus[2].reg_stat  = I2C3_STAT;
	dev->i2c_bus[2].reg_ctrl  = I2C3_CTRL;
	dev->i2c_bus[2].reg_addr  = I2C3_ADDR;
	dev->i2c_bus[2].reg_rdata = I2C3_RDATA;
	dev->i2c_bus[2].reg_wdata = I2C3_WDATA;
	dev->i2c_bus[2].i2c_period = (0x07 << 24); /* 1.95MHz */

	अगर ((cx23885_boards[dev->board].portb == CX23885_MPEG_DVB) ||
		(cx23885_boards[dev->board].portb == CX23885_MPEG_ENCODER))
		cx23885_init_tsport(dev, &dev->ts1, 1);

	अगर ((cx23885_boards[dev->board].portc == CX23885_MPEG_DVB) ||
		(cx23885_boards[dev->board].portc == CX23885_MPEG_ENCODER))
		cx23885_init_tsport(dev, &dev->ts2, 2);

	अगर (get_resources(dev) < 0) अणु
		pr_err("CORE %s No more PCIe resources for subsystem: %04x:%04x\n",
		       dev->name, dev->pci->subप्रणाली_venकरोr,
		       dev->pci->subप्रणाली_device);

		cx23885_devcount--;
		वापस -ENODEV;
	पूर्ण

	/* PCIe stuff */
	dev->lmmio = ioremap(pci_resource_start(dev->pci, 0),
			     pci_resource_len(dev->pci, 0));

	dev->bmmio = (u8 __iomem *)dev->lmmio;

	pr_info("CORE %s: subsystem: %04x:%04x, board: %s [card=%d,%s]\n",
		dev->name, dev->pci->subप्रणाली_venकरोr,
		dev->pci->subप्रणाली_device, cx23885_boards[dev->board].name,
		dev->board, card[dev->nr] == dev->board ?
		"insmod option" : "autodetected");

	cx23885_pci_quirks(dev);

	/* Assume some sensible शेषs */
	dev->tuner_type = cx23885_boards[dev->board].tuner_type;
	dev->tuner_addr = cx23885_boards[dev->board].tuner_addr;
	dev->tuner_bus = cx23885_boards[dev->board].tuner_bus;
	dev->radio_type = cx23885_boards[dev->board].radio_type;
	dev->radio_addr = cx23885_boards[dev->board].radio_addr;

	dprपूर्णांकk(1, "%s() tuner_type = 0x%x tuner_addr = 0x%x tuner_bus = %d\n",
		__func__, dev->tuner_type, dev->tuner_addr, dev->tuner_bus);
	dprपूर्णांकk(1, "%s() radio_type = 0x%x radio_addr = 0x%x\n",
		__func__, dev->radio_type, dev->radio_addr);

	/* The cx23417 encoder has GPIO's that need to be initialised
	 * beक्रमe DVB, so that demodulators and tuners are out of
	 * reset beक्रमe DVB uses them.
	 */
	अगर ((cx23885_boards[dev->board].portb == CX23885_MPEG_ENCODER) ||
		(cx23885_boards[dev->board].portc == CX23885_MPEG_ENCODER))
			cx23885_mc417_init(dev);

	/* init hardware */
	cx23885_reset(dev);

	cx23885_i2c_रेजिस्टर(&dev->i2c_bus[0]);
	cx23885_i2c_रेजिस्टर(&dev->i2c_bus[1]);
	cx23885_i2c_रेजिस्टर(&dev->i2c_bus[2]);
	cx23885_card_setup(dev);
	call_all(dev, tuner, standby);
	cx23885_ir_init(dev);

	अगर (dev->board == CX23885_BOARD_VIEWCAST_460E) अणु
		/*
		 * GPIOs 9/8 are input detection bits क्रम the अवरोधout video
		 * (gpio 8) and audio (gpio 9) cables. When they're attached,
		 * this gpios are pulled high. Make sure these GPIOs are marked
		 * as inमाला_दो.
		 */
		cx23885_gpio_enable(dev, 0x300, 0);
	पूर्ण

	अगर (cx23885_boards[dev->board].porta == CX23885_ANALOG_VIDEO) अणु
		अगर (cx23885_video_रेजिस्टर(dev) < 0) अणु
			pr_err("%s() Failed to register analog video adapters on VID_A\n",
			       __func__);
		पूर्ण
	पूर्ण

	अगर (cx23885_boards[dev->board].portb == CX23885_MPEG_DVB) अणु
		अगर (cx23885_boards[dev->board].num_fds_portb)
			dev->ts1.num_frontends =
				cx23885_boards[dev->board].num_fds_portb;
		अगर (cx23885_dvb_रेजिस्टर(&dev->ts1) < 0) अणु
			pr_err("%s() Failed to register dvb adapters on VID_B\n",
			       __func__);
		पूर्ण
	पूर्ण अन्यथा
	अगर (cx23885_boards[dev->board].portb == CX23885_MPEG_ENCODER) अणु
		अगर (cx23885_417_रेजिस्टर(dev) < 0) अणु
			pr_err("%s() Failed to register 417 on VID_B\n",
			       __func__);
		पूर्ण
	पूर्ण

	अगर (cx23885_boards[dev->board].portc == CX23885_MPEG_DVB) अणु
		अगर (cx23885_boards[dev->board].num_fds_portc)
			dev->ts2.num_frontends =
				cx23885_boards[dev->board].num_fds_portc;
		अगर (cx23885_dvb_रेजिस्टर(&dev->ts2) < 0) अणु
			pr_err("%s() Failed to register dvb on VID_C\n",
			       __func__);
		पूर्ण
	पूर्ण अन्यथा
	अगर (cx23885_boards[dev->board].portc == CX23885_MPEG_ENCODER) अणु
		अगर (cx23885_417_रेजिस्टर(dev) < 0) अणु
			pr_err("%s() Failed to register 417 on VID_C\n",
			       __func__);
		पूर्ण
	पूर्ण

	cx23885_dev_checkrevision(dev);

	/* disable MSI क्रम NetUP cards, otherwise CI is not working */
	अगर (cx23885_boards[dev->board].ci_type > 0)
		cx_clear(RDR_RDRCTL1, 1 << 8);

	चयन (dev->board) अणु
	हाल CX23885_BOARD_TEVII_S470:
	हाल CX23885_BOARD_TEVII_S471:
		cx_clear(RDR_RDRCTL1, 1 << 8);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम cx23885_dev_unरेजिस्टर(काष्ठा cx23885_dev *dev)
अणु
	release_mem_region(pci_resource_start(dev->pci, 0),
			   pci_resource_len(dev->pci, 0));

	अगर (!atomic_dec_and_test(&dev->refcount))
		वापस;

	अगर (cx23885_boards[dev->board].porta == CX23885_ANALOG_VIDEO)
		cx23885_video_unरेजिस्टर(dev);

	अगर (cx23885_boards[dev->board].portb == CX23885_MPEG_DVB)
		cx23885_dvb_unरेजिस्टर(&dev->ts1);

	अगर (cx23885_boards[dev->board].portb == CX23885_MPEG_ENCODER)
		cx23885_417_unरेजिस्टर(dev);

	अगर (cx23885_boards[dev->board].portc == CX23885_MPEG_DVB)
		cx23885_dvb_unरेजिस्टर(&dev->ts2);

	अगर (cx23885_boards[dev->board].portc == CX23885_MPEG_ENCODER)
		cx23885_417_unरेजिस्टर(dev);

	cx23885_i2c_unरेजिस्टर(&dev->i2c_bus[2]);
	cx23885_i2c_unरेजिस्टर(&dev->i2c_bus[1]);
	cx23885_i2c_unरेजिस्टर(&dev->i2c_bus[0]);

	iounmap(dev->lmmio);
पूर्ण

अटल __le32 *cx23885_risc_field(__le32 *rp, काष्ठा scatterlist *sglist,
			       अचिन्हित पूर्णांक offset, u32 sync_line,
			       अचिन्हित पूर्णांक bpl, अचिन्हित पूर्णांक padding,
			       अचिन्हित पूर्णांक lines,  अचिन्हित पूर्णांक lpi, bool jump)
अणु
	काष्ठा scatterlist *sg;
	अचिन्हित पूर्णांक line, toकरो, sol;


	अगर (jump) अणु
		*(rp++) = cpu_to_le32(RISC_JUMP);
		*(rp++) = cpu_to_le32(0);
		*(rp++) = cpu_to_le32(0); /* bits 63-32 */
	पूर्ण

	/* sync inकाष्ठाion */
	अगर (sync_line != NO_SYNC_LINE)
		*(rp++) = cpu_to_le32(RISC_RESYNC | sync_line);

	/* scan lines */
	sg = sglist;
	क्रम (line = 0; line < lines; line++) अणु
		जबतक (offset && offset >= sg_dma_len(sg)) अणु
			offset -= sg_dma_len(sg);
			sg = sg_next(sg);
		पूर्ण

		अगर (lpi && line > 0 && !(line % lpi))
			sol = RISC_SOL | RISC_IRQ1 | RISC_CNT_INC;
		अन्यथा
			sol = RISC_SOL;

		अगर (bpl <= sg_dma_len(sg)-offset) अणु
			/* fits पूर्णांकo current chunk */
			*(rp++) = cpu_to_le32(RISC_WRITE|sol|RISC_EOL|bpl);
			*(rp++) = cpu_to_le32(sg_dma_address(sg)+offset);
			*(rp++) = cpu_to_le32(0); /* bits 63-32 */
			offset += bpl;
		पूर्ण अन्यथा अणु
			/* scanline needs to be split */
			toकरो = bpl;
			*(rp++) = cpu_to_le32(RISC_WRITE|sol|
					    (sg_dma_len(sg)-offset));
			*(rp++) = cpu_to_le32(sg_dma_address(sg)+offset);
			*(rp++) = cpu_to_le32(0); /* bits 63-32 */
			toकरो -= (sg_dma_len(sg)-offset);
			offset = 0;
			sg = sg_next(sg);
			जबतक (toकरो > sg_dma_len(sg)) अणु
				*(rp++) = cpu_to_le32(RISC_WRITE|
						    sg_dma_len(sg));
				*(rp++) = cpu_to_le32(sg_dma_address(sg));
				*(rp++) = cpu_to_le32(0); /* bits 63-32 */
				toकरो -= sg_dma_len(sg);
				sg = sg_next(sg);
			पूर्ण
			*(rp++) = cpu_to_le32(RISC_WRITE|RISC_EOL|toकरो);
			*(rp++) = cpu_to_le32(sg_dma_address(sg));
			*(rp++) = cpu_to_le32(0); /* bits 63-32 */
			offset += toकरो;
		पूर्ण
		offset += padding;
	पूर्ण

	वापस rp;
पूर्ण

पूर्णांक cx23885_risc_buffer(काष्ठा pci_dev *pci, काष्ठा cx23885_riscmem *risc,
			काष्ठा scatterlist *sglist, अचिन्हित पूर्णांक top_offset,
			अचिन्हित पूर्णांक bottom_offset, अचिन्हित पूर्णांक bpl,
			अचिन्हित पूर्णांक padding, अचिन्हित पूर्णांक lines)
अणु
	u32 inकाष्ठाions, fields;
	__le32 *rp;

	fields = 0;
	अगर (UNSET != top_offset)
		fields++;
	अगर (UNSET != bottom_offset)
		fields++;

	/* estimate risc mem: worst हाल is one ग_लिखो per page border +
	   one ग_लिखो per scan line + syncs + jump (all 2 dwords).  Padding
	   can cause next bpl to start बंद to a page border.  First DMA
	   region may be smaller than PAGE_SIZE */
	/* ग_लिखो and jump need and extra dword */
	inकाष्ठाions  = fields * (1 + ((bpl + padding) * lines)
		/ PAGE_SIZE + lines);
	inकाष्ठाions += 5;
	risc->size = inकाष्ठाions * 12;
	risc->cpu = dma_alloc_coherent(&pci->dev, risc->size, &risc->dma,
				       GFP_KERNEL);
	अगर (risc->cpu == शून्य)
		वापस -ENOMEM;

	/* ग_लिखो risc inकाष्ठाions */
	rp = risc->cpu;
	अगर (UNSET != top_offset)
		rp = cx23885_risc_field(rp, sglist, top_offset, 0,
					bpl, padding, lines, 0, true);
	अगर (UNSET != bottom_offset)
		rp = cx23885_risc_field(rp, sglist, bottom_offset, 0x200,
					bpl, padding, lines, 0, UNSET == top_offset);

	/* save poपूर्णांकer to jmp inकाष्ठाion address */
	risc->jmp = rp;
	BUG_ON((risc->jmp - risc->cpu + 2) * माप(*risc->cpu) > risc->size);
	वापस 0;
पूर्ण

पूर्णांक cx23885_risc_databuffer(काष्ठा pci_dev *pci,
				   काष्ठा cx23885_riscmem *risc,
				   काष्ठा scatterlist *sglist,
				   अचिन्हित पूर्णांक bpl,
				   अचिन्हित पूर्णांक lines, अचिन्हित पूर्णांक lpi)
अणु
	u32 inकाष्ठाions;
	__le32 *rp;

	/* estimate risc mem: worst हाल is one ग_लिखो per page border +
	   one ग_लिखो per scan line + syncs + jump (all 2 dwords).  Here
	   there is no padding and no sync.  First DMA region may be smaller
	   than PAGE_SIZE */
	/* Jump and ग_लिखो need an extra dword */
	inकाष्ठाions  = 1 + (bpl * lines) / PAGE_SIZE + lines;
	inकाष्ठाions += 4;

	risc->size = inकाष्ठाions * 12;
	risc->cpu = dma_alloc_coherent(&pci->dev, risc->size, &risc->dma,
				       GFP_KERNEL);
	अगर (risc->cpu == शून्य)
		वापस -ENOMEM;

	/* ग_लिखो risc inकाष्ठाions */
	rp = risc->cpu;
	rp = cx23885_risc_field(rp, sglist, 0, NO_SYNC_LINE,
				bpl, 0, lines, lpi, lpi == 0);

	/* save poपूर्णांकer to jmp inकाष्ठाion address */
	risc->jmp = rp;
	BUG_ON((risc->jmp - risc->cpu + 2) * माप(*risc->cpu) > risc->size);
	वापस 0;
पूर्ण

पूर्णांक cx23885_risc_vbibuffer(काष्ठा pci_dev *pci, काष्ठा cx23885_riscmem *risc,
			काष्ठा scatterlist *sglist, अचिन्हित पूर्णांक top_offset,
			अचिन्हित पूर्णांक bottom_offset, अचिन्हित पूर्णांक bpl,
			अचिन्हित पूर्णांक padding, अचिन्हित पूर्णांक lines)
अणु
	u32 inकाष्ठाions, fields;
	__le32 *rp;

	fields = 0;
	अगर (UNSET != top_offset)
		fields++;
	अगर (UNSET != bottom_offset)
		fields++;

	/* estimate risc mem: worst हाल is one ग_लिखो per page border +
	   one ग_लिखो per scan line + syncs + jump (all 2 dwords).  Padding
	   can cause next bpl to start बंद to a page border.  First DMA
	   region may be smaller than PAGE_SIZE */
	/* ग_लिखो and jump need and extra dword */
	inकाष्ठाions  = fields * (1 + ((bpl + padding) * lines)
		/ PAGE_SIZE + lines);
	inकाष्ठाions += 5;
	risc->size = inकाष्ठाions * 12;
	risc->cpu = dma_alloc_coherent(&pci->dev, risc->size, &risc->dma,
				       GFP_KERNEL);
	अगर (risc->cpu == शून्य)
		वापस -ENOMEM;
	/* ग_लिखो risc inकाष्ठाions */
	rp = risc->cpu;

	/* Sync to line 6, so US CC line 21 will appear in line '12'
	 * in the userland vbi payload */
	अगर (UNSET != top_offset)
		rp = cx23885_risc_field(rp, sglist, top_offset, 0,
					bpl, padding, lines, 0, true);

	अगर (UNSET != bottom_offset)
		rp = cx23885_risc_field(rp, sglist, bottom_offset, 0x200,
					bpl, padding, lines, 0, UNSET == top_offset);



	/* save poपूर्णांकer to jmp inकाष्ठाion address */
	risc->jmp = rp;
	BUG_ON((risc->jmp - risc->cpu + 2) * माप(*risc->cpu) > risc->size);
	वापस 0;
पूर्ण


व्योम cx23885_मुक्त_buffer(काष्ठा cx23885_dev *dev, काष्ठा cx23885_buffer *buf)
अणु
	काष्ठा cx23885_riscmem *risc = &buf->risc;

	dma_मुक्त_coherent(&dev->pci->dev, risc->size, risc->cpu, risc->dma);
पूर्ण

अटल व्योम cx23885_tsport_reg_dump(काष्ठा cx23885_tsport *port)
अणु
	काष्ठा cx23885_dev *dev = port->dev;

	dprपूर्णांकk(1, "%s() Register Dump\n", __func__);
	dprपूर्णांकk(1, "%s() DEV_CNTRL2               0x%08X\n", __func__,
		cx_पढ़ो(DEV_CNTRL2));
	dprपूर्णांकk(1, "%s() PCI_INT_MSK              0x%08X\n", __func__,
		cx23885_irq_get_mask(dev));
	dprपूर्णांकk(1, "%s() AUD_INT_INT_MSK          0x%08X\n", __func__,
		cx_पढ़ो(AUDIO_INT_INT_MSK));
	dprपूर्णांकk(1, "%s() AUD_INT_DMA_CTL          0x%08X\n", __func__,
		cx_पढ़ो(AUD_INT_DMA_CTL));
	dprपूर्णांकk(1, "%s() AUD_EXT_INT_MSK          0x%08X\n", __func__,
		cx_पढ़ो(AUDIO_EXT_INT_MSK));
	dprपूर्णांकk(1, "%s() AUD_EXT_DMA_CTL          0x%08X\n", __func__,
		cx_पढ़ो(AUD_EXT_DMA_CTL));
	dprपूर्णांकk(1, "%s() PAD_CTRL                 0x%08X\n", __func__,
		cx_पढ़ो(PAD_CTRL));
	dprपूर्णांकk(1, "%s() ALT_PIN_OUT_SEL          0x%08X\n", __func__,
		cx_पढ़ो(ALT_PIN_OUT_SEL));
	dprपूर्णांकk(1, "%s() GPIO2                    0x%08X\n", __func__,
		cx_पढ़ो(GPIO2));
	dprपूर्णांकk(1, "%s() gpcnt(0x%08X)          0x%08X\n", __func__,
		port->reg_gpcnt, cx_पढ़ो(port->reg_gpcnt));
	dprपूर्णांकk(1, "%s() gpcnt_ctl(0x%08X)      0x%08x\n", __func__,
		port->reg_gpcnt_ctl, cx_पढ़ो(port->reg_gpcnt_ctl));
	dprपूर्णांकk(1, "%s() dma_ctl(0x%08X)        0x%08x\n", __func__,
		port->reg_dma_ctl, cx_पढ़ो(port->reg_dma_ctl));
	अगर (port->reg_src_sel)
		dprपूर्णांकk(1, "%s() src_sel(0x%08X)        0x%08x\n", __func__,
			port->reg_src_sel, cx_पढ़ो(port->reg_src_sel));
	dprपूर्णांकk(1, "%s() lngth(0x%08X)          0x%08x\n", __func__,
		port->reg_lngth, cx_पढ़ो(port->reg_lngth));
	dprपूर्णांकk(1, "%s() hw_sop_ctrl(0x%08X)    0x%08x\n", __func__,
		port->reg_hw_sop_ctrl, cx_पढ़ो(port->reg_hw_sop_ctrl));
	dprपूर्णांकk(1, "%s() gen_ctrl(0x%08X)       0x%08x\n", __func__,
		port->reg_gen_ctrl, cx_पढ़ो(port->reg_gen_ctrl));
	dprपूर्णांकk(1, "%s() bd_pkt_status(0x%08X)  0x%08x\n", __func__,
		port->reg_bd_pkt_status, cx_पढ़ो(port->reg_bd_pkt_status));
	dprपूर्णांकk(1, "%s() sop_status(0x%08X)     0x%08x\n", __func__,
		port->reg_sop_status, cx_पढ़ो(port->reg_sop_status));
	dprपूर्णांकk(1, "%s() fifo_ovfl_stat(0x%08X) 0x%08x\n", __func__,
		port->reg_fअगरo_ovfl_stat, cx_पढ़ो(port->reg_fअगरo_ovfl_stat));
	dprपूर्णांकk(1, "%s() vld_misc(0x%08X)       0x%08x\n", __func__,
		port->reg_vld_misc, cx_पढ़ो(port->reg_vld_misc));
	dprपूर्णांकk(1, "%s() ts_clk_en(0x%08X)      0x%08x\n", __func__,
		port->reg_ts_clk_en, cx_पढ़ो(port->reg_ts_clk_en));
	dprपूर्णांकk(1, "%s() ts_int_msk(0x%08X)     0x%08x\n", __func__,
		port->reg_ts_पूर्णांक_msk, cx_पढ़ो(port->reg_ts_पूर्णांक_msk));
	dprपूर्णांकk(1, "%s() ts_int_status(0x%08X)  0x%08x\n", __func__,
		port->reg_ts_पूर्णांक_stat, cx_पढ़ो(port->reg_ts_पूर्णांक_stat));
	dprपूर्णांकk(1, "%s() PCI_INT_STAT           0x%08X\n", __func__,
		cx_पढ़ो(PCI_INT_STAT));
	dprपूर्णांकk(1, "%s() VID_B_INT_MSTAT        0x%08X\n", __func__,
		cx_पढ़ो(VID_B_INT_MSTAT));
	dprपूर्णांकk(1, "%s() VID_B_INT_SSTAT        0x%08X\n", __func__,
		cx_पढ़ो(VID_B_INT_SSTAT));
	dprपूर्णांकk(1, "%s() VID_C_INT_MSTAT        0x%08X\n", __func__,
		cx_पढ़ो(VID_C_INT_MSTAT));
	dprपूर्णांकk(1, "%s() VID_C_INT_SSTAT        0x%08X\n", __func__,
		cx_पढ़ो(VID_C_INT_SSTAT));
पूर्ण

पूर्णांक cx23885_start_dma(काष्ठा cx23885_tsport *port,
			     काष्ठा cx23885_dmaqueue *q,
			     काष्ठा cx23885_buffer   *buf)
अणु
	काष्ठा cx23885_dev *dev = port->dev;
	u32 reg;

	dprपूर्णांकk(1, "%s() w: %d, h: %d, f: %d\n", __func__,
		dev->width, dev->height, dev->field);

	/* clear dma in progress */
	cx23885_clear_bridge_error(dev);

	/* Stop the fअगरo and risc engine क्रम this port */
	cx_clear(port->reg_dma_ctl, port->dma_ctl_val);

	/* setup fअगरo + क्रमmat */
	cx23885_sram_channel_setup(dev,
				   &dev->sram_channels[port->sram_chno],
				   port->ts_packet_size, buf->risc.dma);
	अगर (debug > 5) अणु
		cx23885_sram_channel_dump(dev,
			&dev->sram_channels[port->sram_chno]);
		cx23885_risc_disयंत्र(port, &buf->risc);
	पूर्ण

	/* ग_लिखो TS length to chip */
	cx_ग_लिखो(port->reg_lngth, port->ts_packet_size);

	अगर ((!(cx23885_boards[dev->board].portb & CX23885_MPEG_DVB)) &&
		(!(cx23885_boards[dev->board].portc & CX23885_MPEG_DVB))) अणु
		pr_err("%s() Unsupported .portb/c (0x%08x)/(0x%08x)\n",
			__func__,
			cx23885_boards[dev->board].portb,
			cx23885_boards[dev->board].portc);
		वापस -EINVAL;
	पूर्ण

	अगर (cx23885_boards[dev->board].portb == CX23885_MPEG_ENCODER)
		cx23885_av_clk(dev, 0);

	udelay(100);

	/* If the port supports SRC SELECT, configure it */
	अगर (port->reg_src_sel)
		cx_ग_लिखो(port->reg_src_sel, port->src_sel_val);

	cx_ग_लिखो(port->reg_hw_sop_ctrl, port->hw_sop_ctrl_val);
	cx_ग_लिखो(port->reg_ts_clk_en, port->ts_clk_en_val);
	cx_ग_लिखो(port->reg_vld_misc, port->vld_misc_val);
	cx_ग_लिखो(port->reg_gen_ctrl, port->gen_ctrl_val);
	udelay(100);

	/* NOTE: this is 2 (reserved) क्रम portb, करोes it matter? */
	/* reset counter to zero */
	cx_ग_लिखो(port->reg_gpcnt_ctl, 3);
	q->count = 0;

	/* Set VIDB pins to input */
	अगर (cx23885_boards[dev->board].portb == CX23885_MPEG_DVB) अणु
		reg = cx_पढ़ो(PAD_CTRL);
		reg &= ~0x3; /* Clear TS1_OE & TS1_SOP_OE */
		cx_ग_लिखो(PAD_CTRL, reg);
	पूर्ण

	/* Set VIDC pins to input */
	अगर (cx23885_boards[dev->board].portc == CX23885_MPEG_DVB) अणु
		reg = cx_पढ़ो(PAD_CTRL);
		reg &= ~0x4; /* Clear TS2_SOP_OE */
		cx_ग_लिखो(PAD_CTRL, reg);
	पूर्ण

	अगर (cx23885_boards[dev->board].portb == CX23885_MPEG_ENCODER) अणु

		reg = cx_पढ़ो(PAD_CTRL);
		reg = reg & ~0x1;    /* Clear TS1_OE */

		/* FIXME, bit 2 writing here is questionable */
		/* set TS1_SOP_OE and TS1_OE_HI */
		reg = reg | 0xa;
		cx_ग_लिखो(PAD_CTRL, reg);

		/* Sets MOE_CLK_DIS to disable MoE घड़ी */
		/* sets MCLK_DLY_SEL/BCLK_DLY_SEL to 1 buffer delay each */
		cx_ग_लिखो(CLK_DELAY, cx_पढ़ो(CLK_DELAY) | 0x80000011);

		/* ALT_GPIO_ALT_SET: GPIO[0]
		 * IR_ALT_TX_SEL: GPIO[1]
		 * GPIO1_ALT_SEL: VIP_656_DATA[0]
		 * GPIO0_ALT_SEL: VIP_656_CLK
		 */
		cx_ग_लिखो(ALT_PIN_OUT_SEL, 0x10100045);
	पूर्ण

	चयन (dev->bridge) अणु
	हाल CX23885_BRIDGE_885:
	हाल CX23885_BRIDGE_887:
	हाल CX23885_BRIDGE_888:
		/* enable irqs */
		dprपूर्णांकk(1, "%s() enabling TS int's and DMA\n", __func__);
		/* clear dma in progress */
		cx23885_clear_bridge_error(dev);
		cx_set(port->reg_ts_पूर्णांक_msk,  port->ts_पूर्णांक_msk_val);
		cx_set(port->reg_dma_ctl, port->dma_ctl_val);

		/* clear dma in progress */
		cx23885_clear_bridge_error(dev);
		cx23885_irq_add(dev, port->pci_irqmask);
		cx23885_irq_enable_all(dev);

		/* clear dma in progress */
		cx23885_clear_bridge_error(dev);
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	cx_set(DEV_CNTRL2, (1<<5)); /* Enable RISC controller */
	/* clear dma in progress */
	cx23885_clear_bridge_error(dev);

	अगर (cx23885_boards[dev->board].portb == CX23885_MPEG_ENCODER)
		cx23885_av_clk(dev, 1);

	अगर (debug > 4)
		cx23885_tsport_reg_dump(port);

	cx23885_irq_get_mask(dev);

	/* clear dma in progress */
	cx23885_clear_bridge_error(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक cx23885_stop_dma(काष्ठा cx23885_tsport *port)
अणु
	काष्ठा cx23885_dev *dev = port->dev;
	u32 reg;
	पूर्णांक delay = 0;
	uपूर्णांक32_t reg1_val;
	uपूर्णांक32_t reg2_val;

	dprपूर्णांकk(1, "%s()\n", __func__);

	/* Stop पूर्णांकerrupts and DMA */
	cx_clear(port->reg_ts_पूर्णांक_msk, port->ts_पूर्णांक_msk_val);
	cx_clear(port->reg_dma_ctl, port->dma_ctl_val);
	/* just in हाल रुको क्रम any dma to complete beक्रमe allowing dealloc */
	mdelay(20);
	क्रम (delay = 0; delay < 100; delay++) अणु
		reg1_val = cx_पढ़ो(TC_REQ);
		reg2_val = cx_पढ़ो(TC_REQ_SET);
		अगर (reg1_val == 0 || reg2_val == 0)
			अवरोध;
		mdelay(1);
	पूर्ण
	dev_dbg(&dev->pci->dev, "delay=%d reg1=0x%08x reg2=0x%08x\n",
		delay, reg1_val, reg2_val);

	अगर (cx23885_boards[dev->board].portb == CX23885_MPEG_ENCODER) अणु
		reg = cx_पढ़ो(PAD_CTRL);

		/* Set TS1_OE */
		reg = reg | 0x1;

		/* clear TS1_SOP_OE and TS1_OE_HI */
		reg = reg & ~0xa;
		cx_ग_लिखो(PAD_CTRL, reg);
		cx_ग_लिखो(port->reg_src_sel, 0);
		cx_ग_लिखो(port->reg_gen_ctrl, 8);
	पूर्ण

	अगर (cx23885_boards[dev->board].portb == CX23885_MPEG_ENCODER)
		cx23885_av_clk(dev, 0);

	वापस 0;
पूर्ण

/* ------------------------------------------------------------------ */

पूर्णांक cx23885_buf_prepare(काष्ठा cx23885_buffer *buf, काष्ठा cx23885_tsport *port)
अणु
	काष्ठा cx23885_dev *dev = port->dev;
	पूर्णांक size = port->ts_packet_size * port->ts_packet_count;
	काष्ठा sg_table *sgt = vb2_dma_sg_plane_desc(&buf->vb.vb2_buf, 0);

	dprपूर्णांकk(1, "%s: %p\n", __func__, buf);
	अगर (vb2_plane_size(&buf->vb.vb2_buf, 0) < size)
		वापस -EINVAL;
	vb2_set_plane_payload(&buf->vb.vb2_buf, 0, size);

	cx23885_risc_databuffer(dev->pci, &buf->risc,
				sgt->sgl,
				port->ts_packet_size, port->ts_packet_count, 0);
	वापस 0;
पूर्ण

/*
 * The risc program क्रम each buffer works as follows: it starts with a simple
 * 'JUMP to addr + 12', which is effectively a NOP. Then the code to DMA the
 * buffer follows and at the end we have a JUMP back to the start + 12 (skipping
 * the initial JUMP).
 *
 * This is the risc program of the first buffer to be queued अगर the active list
 * is empty and it just keeps DMAing this buffer without generating any
 * पूर्णांकerrupts.
 *
 * If a new buffer is added then the initial JUMP in the code क्रम that buffer
 * will generate an पूर्णांकerrupt which संकेतs that the previous buffer has been
 * DMAed successfully and that it can be वापसed to userspace.
 *
 * It also sets the final jump of the previous buffer to the start of the new
 * buffer, thus chaining the new buffer पूर्णांकo the DMA chain. This is a single
 * atomic u32 ग_लिखो, so there is no race condition.
 *
 * The end-result of all this that you only get an पूर्णांकerrupt when a buffer
 * is पढ़ोy, so the control flow is very easy.
 */
व्योम cx23885_buf_queue(काष्ठा cx23885_tsport *port, काष्ठा cx23885_buffer *buf)
अणु
	काष्ठा cx23885_buffer    *prev;
	काष्ठा cx23885_dev *dev = port->dev;
	काष्ठा cx23885_dmaqueue  *cx88q = &port->mpegq;
	अचिन्हित दीर्घ flags;

	buf->risc.cpu[1] = cpu_to_le32(buf->risc.dma + 12);
	buf->risc.jmp[0] = cpu_to_le32(RISC_JUMP | RISC_CNT_INC);
	buf->risc.jmp[1] = cpu_to_le32(buf->risc.dma + 12);
	buf->risc.jmp[2] = cpu_to_le32(0); /* bits 63-32 */

	spin_lock_irqsave(&dev->slock, flags);
	अगर (list_empty(&cx88q->active)) अणु
		list_add_tail(&buf->queue, &cx88q->active);
		dprपूर्णांकk(1, "[%p/%d] %s - first active\n",
			buf, buf->vb.vb2_buf.index, __func__);
	पूर्ण अन्यथा अणु
		buf->risc.cpu[0] |= cpu_to_le32(RISC_IRQ1);
		prev = list_entry(cx88q->active.prev, काष्ठा cx23885_buffer,
				  queue);
		list_add_tail(&buf->queue, &cx88q->active);
		prev->risc.jmp[1] = cpu_to_le32(buf->risc.dma);
		dprपूर्णांकk(1, "[%p/%d] %s - append to active\n",
			 buf, buf->vb.vb2_buf.index, __func__);
	पूर्ण
	spin_unlock_irqrestore(&dev->slock, flags);
पूर्ण

/* ----------------------------------------------------------- */

अटल व्योम करो_cancel_buffers(काष्ठा cx23885_tsport *port, अक्षर *reason)
अणु
	काष्ठा cx23885_dmaqueue *q = &port->mpegq;
	काष्ठा cx23885_buffer *buf;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&port->slock, flags);
	जबतक (!list_empty(&q->active)) अणु
		buf = list_entry(q->active.next, काष्ठा cx23885_buffer,
				 queue);
		list_del(&buf->queue);
		vb2_buffer_करोne(&buf->vb.vb2_buf, VB2_BUF_STATE_ERROR);
		dprपूर्णांकk(1, "[%p/%d] %s - dma=0x%08lx\n",
			buf, buf->vb.vb2_buf.index, reason,
			(अचिन्हित दीर्घ)buf->risc.dma);
	पूर्ण
	spin_unlock_irqrestore(&port->slock, flags);
पूर्ण

व्योम cx23885_cancel_buffers(काष्ठा cx23885_tsport *port)
अणु
	dprपूर्णांकk(1, "%s()\n", __func__);
	cx23885_stop_dma(port);
	करो_cancel_buffers(port, "cancel");
पूर्ण

पूर्णांक cx23885_irq_417(काष्ठा cx23885_dev *dev, u32 status)
अणु
	/* FIXME: port1 assumption here. */
	काष्ठा cx23885_tsport *port = &dev->ts1;
	पूर्णांक count = 0;
	पूर्णांक handled = 0;

	अगर (status == 0)
		वापस handled;

	count = cx_पढ़ो(port->reg_gpcnt);
	dprपूर्णांकk(7, "status: 0x%08x  mask: 0x%08x count: 0x%x\n",
		status, cx_पढ़ो(port->reg_ts_पूर्णांक_msk), count);

	अगर ((status & VID_B_MSK_BAD_PKT)         ||
		(status & VID_B_MSK_OPC_ERR)     ||
		(status & VID_B_MSK_VBI_OPC_ERR) ||
		(status & VID_B_MSK_SYNC)        ||
		(status & VID_B_MSK_VBI_SYNC)    ||
		(status & VID_B_MSK_OF)          ||
		(status & VID_B_MSK_VBI_OF)) अणु
		pr_err("%s: V4L mpeg risc op code error, status = 0x%x\n",
		       dev->name, status);
		अगर (status & VID_B_MSK_BAD_PKT)
			dprपूर्णांकk(1, "        VID_B_MSK_BAD_PKT\n");
		अगर (status & VID_B_MSK_OPC_ERR)
			dprपूर्णांकk(1, "        VID_B_MSK_OPC_ERR\n");
		अगर (status & VID_B_MSK_VBI_OPC_ERR)
			dprपूर्णांकk(1, "        VID_B_MSK_VBI_OPC_ERR\n");
		अगर (status & VID_B_MSK_SYNC)
			dprपूर्णांकk(1, "        VID_B_MSK_SYNC\n");
		अगर (status & VID_B_MSK_VBI_SYNC)
			dprपूर्णांकk(1, "        VID_B_MSK_VBI_SYNC\n");
		अगर (status & VID_B_MSK_OF)
			dprपूर्णांकk(1, "        VID_B_MSK_OF\n");
		अगर (status & VID_B_MSK_VBI_OF)
			dprपूर्णांकk(1, "        VID_B_MSK_VBI_OF\n");

		cx_clear(port->reg_dma_ctl, port->dma_ctl_val);
		cx23885_sram_channel_dump(dev,
			&dev->sram_channels[port->sram_chno]);
		cx23885_417_check_encoder(dev);
	पूर्ण अन्यथा अगर (status & VID_B_MSK_RISCI1) अणु
		dprपूर्णांकk(7, "        VID_B_MSK_RISCI1\n");
		spin_lock(&port->slock);
		cx23885_wakeup(port, &port->mpegq, count);
		spin_unlock(&port->slock);
	पूर्ण
	अगर (status) अणु
		cx_ग_लिखो(port->reg_ts_पूर्णांक_stat, status);
		handled = 1;
	पूर्ण

	वापस handled;
पूर्ण

अटल पूर्णांक cx23885_irq_ts(काष्ठा cx23885_tsport *port, u32 status)
अणु
	काष्ठा cx23885_dev *dev = port->dev;
	पूर्णांक handled = 0;
	u32 count;

	अगर ((status & VID_BC_MSK_OPC_ERR) ||
		(status & VID_BC_MSK_BAD_PKT) ||
		(status & VID_BC_MSK_SYNC) ||
		(status & VID_BC_MSK_OF)) अणु

		अगर (status & VID_BC_MSK_OPC_ERR)
			dprपूर्णांकk(7, " (VID_BC_MSK_OPC_ERR 0x%08x)\n",
				VID_BC_MSK_OPC_ERR);

		अगर (status & VID_BC_MSK_BAD_PKT)
			dprपूर्णांकk(7, " (VID_BC_MSK_BAD_PKT 0x%08x)\n",
				VID_BC_MSK_BAD_PKT);

		अगर (status & VID_BC_MSK_SYNC)
			dprपूर्णांकk(7, " (VID_BC_MSK_SYNC    0x%08x)\n",
				VID_BC_MSK_SYNC);

		अगर (status & VID_BC_MSK_OF)
			dprपूर्णांकk(7, " (VID_BC_MSK_OF      0x%08x)\n",
				VID_BC_MSK_OF);

		pr_err("%s: mpeg risc op code error\n", dev->name);

		cx_clear(port->reg_dma_ctl, port->dma_ctl_val);
		cx23885_sram_channel_dump(dev,
			&dev->sram_channels[port->sram_chno]);

	पूर्ण अन्यथा अगर (status & VID_BC_MSK_RISCI1) अणु

		dprपूर्णांकk(7, " (RISCI1            0x%08x)\n", VID_BC_MSK_RISCI1);

		spin_lock(&port->slock);
		count = cx_पढ़ो(port->reg_gpcnt);
		cx23885_wakeup(port, &port->mpegq, count);
		spin_unlock(&port->slock);

	पूर्ण
	अगर (status) अणु
		cx_ग_लिखो(port->reg_ts_पूर्णांक_stat, status);
		handled = 1;
	पूर्ण

	वापस handled;
पूर्ण

अटल irqवापस_t cx23885_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा cx23885_dev *dev = dev_id;
	काष्ठा cx23885_tsport *ts1 = &dev->ts1;
	काष्ठा cx23885_tsport *ts2 = &dev->ts2;
	u32 pci_status, pci_mask;
	u32 vida_status, vida_mask;
	u32 audपूर्णांक_status, audपूर्णांक_mask;
	u32 ts1_status, ts1_mask;
	u32 ts2_status, ts2_mask;
	पूर्णांक vida_count = 0, ts1_count = 0, ts2_count = 0, handled = 0;
	पूर्णांक audपूर्णांक_count = 0;
	bool subdev_handled;

	pci_status = cx_पढ़ो(PCI_INT_STAT);
	pci_mask = cx23885_irq_get_mask(dev);
	अगर ((pci_status & pci_mask) == 0) अणु
		dprपूर्णांकk(7, "pci_status: 0x%08x  pci_mask: 0x%08x\n",
			pci_status, pci_mask);
		जाओ out;
	पूर्ण

	vida_status = cx_पढ़ो(VID_A_INT_STAT);
	vida_mask = cx_पढ़ो(VID_A_INT_MSK);
	audपूर्णांक_status = cx_पढ़ो(AUDIO_INT_INT_STAT);
	audपूर्णांक_mask = cx_पढ़ो(AUDIO_INT_INT_MSK);
	ts1_status = cx_पढ़ो(VID_B_INT_STAT);
	ts1_mask = cx_पढ़ो(VID_B_INT_MSK);
	ts2_status = cx_पढ़ो(VID_C_INT_STAT);
	ts2_mask = cx_पढ़ो(VID_C_INT_MSK);

	अगर (((pci_status & pci_mask) == 0) &&
		((ts2_status & ts2_mask) == 0) &&
		((ts1_status & ts1_mask) == 0))
		जाओ out;

	vida_count = cx_पढ़ो(VID_A_GPCNT);
	audपूर्णांक_count = cx_पढ़ो(AUD_INT_A_GPCNT);
	ts1_count = cx_पढ़ो(ts1->reg_gpcnt);
	ts2_count = cx_पढ़ो(ts2->reg_gpcnt);
	dprपूर्णांकk(7, "pci_status: 0x%08x  pci_mask: 0x%08x\n",
		pci_status, pci_mask);
	dprपूर्णांकk(7, "vida_status: 0x%08x vida_mask: 0x%08x count: 0x%x\n",
		vida_status, vida_mask, vida_count);
	dprपूर्णांकk(7, "audint_status: 0x%08x audint_mask: 0x%08x count: 0x%x\n",
		audपूर्णांक_status, audपूर्णांक_mask, audपूर्णांक_count);
	dprपूर्णांकk(7, "ts1_status: 0x%08x  ts1_mask: 0x%08x count: 0x%x\n",
		ts1_status, ts1_mask, ts1_count);
	dprपूर्णांकk(7, "ts2_status: 0x%08x  ts2_mask: 0x%08x count: 0x%x\n",
		ts2_status, ts2_mask, ts2_count);

	अगर (pci_status & (PCI_MSK_RISC_RD | PCI_MSK_RISC_WR |
			  PCI_MSK_AL_RD   | PCI_MSK_AL_WR   | PCI_MSK_APB_DMA |
			  PCI_MSK_VID_C   | PCI_MSK_VID_B   | PCI_MSK_VID_A   |
			  PCI_MSK_AUD_INT | PCI_MSK_AUD_EXT |
			  PCI_MSK_GPIO0   | PCI_MSK_GPIO1   |
			  PCI_MSK_AV_CORE | PCI_MSK_IR)) अणु

		अगर (pci_status & PCI_MSK_RISC_RD)
			dprपूर्णांकk(7, " (PCI_MSK_RISC_RD   0x%08x)\n",
				PCI_MSK_RISC_RD);

		अगर (pci_status & PCI_MSK_RISC_WR)
			dprपूर्णांकk(7, " (PCI_MSK_RISC_WR   0x%08x)\n",
				PCI_MSK_RISC_WR);

		अगर (pci_status & PCI_MSK_AL_RD)
			dprपूर्णांकk(7, " (PCI_MSK_AL_RD     0x%08x)\n",
				PCI_MSK_AL_RD);

		अगर (pci_status & PCI_MSK_AL_WR)
			dprपूर्णांकk(7, " (PCI_MSK_AL_WR     0x%08x)\n",
				PCI_MSK_AL_WR);

		अगर (pci_status & PCI_MSK_APB_DMA)
			dprपूर्णांकk(7, " (PCI_MSK_APB_DMA   0x%08x)\n",
				PCI_MSK_APB_DMA);

		अगर (pci_status & PCI_MSK_VID_C)
			dprपूर्णांकk(7, " (PCI_MSK_VID_C     0x%08x)\n",
				PCI_MSK_VID_C);

		अगर (pci_status & PCI_MSK_VID_B)
			dprपूर्णांकk(7, " (PCI_MSK_VID_B     0x%08x)\n",
				PCI_MSK_VID_B);

		अगर (pci_status & PCI_MSK_VID_A)
			dprपूर्णांकk(7, " (PCI_MSK_VID_A     0x%08x)\n",
				PCI_MSK_VID_A);

		अगर (pci_status & PCI_MSK_AUD_INT)
			dprपूर्णांकk(7, " (PCI_MSK_AUD_INT   0x%08x)\n",
				PCI_MSK_AUD_INT);

		अगर (pci_status & PCI_MSK_AUD_EXT)
			dprपूर्णांकk(7, " (PCI_MSK_AUD_EXT   0x%08x)\n",
				PCI_MSK_AUD_EXT);

		अगर (pci_status & PCI_MSK_GPIO0)
			dprपूर्णांकk(7, " (PCI_MSK_GPIO0     0x%08x)\n",
				PCI_MSK_GPIO0);

		अगर (pci_status & PCI_MSK_GPIO1)
			dprपूर्णांकk(7, " (PCI_MSK_GPIO1     0x%08x)\n",
				PCI_MSK_GPIO1);

		अगर (pci_status & PCI_MSK_AV_CORE)
			dprपूर्णांकk(7, " (PCI_MSK_AV_CORE   0x%08x)\n",
				PCI_MSK_AV_CORE);

		अगर (pci_status & PCI_MSK_IR)
			dprपूर्णांकk(7, " (PCI_MSK_IR        0x%08x)\n",
				PCI_MSK_IR);
	पूर्ण

	अगर (cx23885_boards[dev->board].ci_type == 1 &&
			(pci_status & (PCI_MSK_GPIO1 | PCI_MSK_GPIO0)))
		handled += netup_ci_slot_status(dev, pci_status);

	अगर (cx23885_boards[dev->board].ci_type == 2 &&
			(pci_status & PCI_MSK_GPIO0))
		handled += altera_ci_irq(dev);

	अगर (ts1_status) अणु
		अगर (cx23885_boards[dev->board].portb == CX23885_MPEG_DVB)
			handled += cx23885_irq_ts(ts1, ts1_status);
		अन्यथा
		अगर (cx23885_boards[dev->board].portb == CX23885_MPEG_ENCODER)
			handled += cx23885_irq_417(dev, ts1_status);
	पूर्ण

	अगर (ts2_status) अणु
		अगर (cx23885_boards[dev->board].portc == CX23885_MPEG_DVB)
			handled += cx23885_irq_ts(ts2, ts2_status);
		अन्यथा
		अगर (cx23885_boards[dev->board].portc == CX23885_MPEG_ENCODER)
			handled += cx23885_irq_417(dev, ts2_status);
	पूर्ण

	अगर (vida_status)
		handled += cx23885_video_irq(dev, vida_status);

	अगर (audपूर्णांक_status)
		handled += cx23885_audio_irq(dev, audपूर्णांक_status, audपूर्णांक_mask);

	अगर (pci_status & PCI_MSK_IR) अणु
		subdev_handled = false;
		v4l2_subdev_call(dev->sd_ir, core, पूर्णांकerrupt_service_routine,
				 pci_status, &subdev_handled);
		अगर (subdev_handled)
			handled++;
	पूर्ण

	अगर ((pci_status & pci_mask) & PCI_MSK_AV_CORE) अणु
		cx23885_irq_disable(dev, PCI_MSK_AV_CORE);
		schedule_work(&dev->cx25840_work);
		handled++;
	पूर्ण

	अगर (handled)
		cx_ग_लिखो(PCI_INT_STAT, pci_status & pci_mask);
out:
	वापस IRQ_RETVAL(handled);
पूर्ण

अटल व्योम cx23885_v4l2_dev_notअगरy(काष्ठा v4l2_subdev *sd,
				    अचिन्हित पूर्णांक notअगरication, व्योम *arg)
अणु
	काष्ठा cx23885_dev *dev;

	अगर (sd == शून्य)
		वापस;

	dev = to_cx23885(sd->v4l2_dev);

	चयन (notअगरication) अणु
	हाल V4L2_SUBDEV_IR_RX_NOTIFY: /* Possibly called in an IRQ context */
		अगर (sd == dev->sd_ir)
			cx23885_ir_rx_v4l2_dev_notअगरy(sd, *(u32 *)arg);
		अवरोध;
	हाल V4L2_SUBDEV_IR_TX_NOTIFY: /* Possibly called in an IRQ context */
		अगर (sd == dev->sd_ir)
			cx23885_ir_tx_v4l2_dev_notअगरy(sd, *(u32 *)arg);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम cx23885_v4l2_dev_notअगरy_init(काष्ठा cx23885_dev *dev)
अणु
	INIT_WORK(&dev->cx25840_work, cx23885_av_work_handler);
	INIT_WORK(&dev->ir_rx_work, cx23885_ir_rx_work_handler);
	INIT_WORK(&dev->ir_tx_work, cx23885_ir_tx_work_handler);
	dev->v4l2_dev.notअगरy = cx23885_v4l2_dev_notअगरy;
पूर्ण

अटल अंतरभूत पूर्णांक encoder_on_portb(काष्ठा cx23885_dev *dev)
अणु
	वापस cx23885_boards[dev->board].portb == CX23885_MPEG_ENCODER;
पूर्ण

अटल अंतरभूत पूर्णांक encoder_on_portc(काष्ठा cx23885_dev *dev)
अणु
	वापस cx23885_boards[dev->board].portc == CX23885_MPEG_ENCODER;
पूर्ण

/* Mask represents 32 dअगरferent GPIOs, GPIO's are split पूर्णांकo multiple
 * रेजिस्टरs depending on the board configuration (and whether the
 * 417 encoder (wi it's own GPIO's) are present. Each GPIO bit will
 * be pushed पूर्णांकo the correct hardware रेजिस्टर, regardless of the
 * physical location. Certain रेजिस्टरs are shared so we sanity check
 * and report errors अगर we think we're tampering with a GPIo that might
 * be asचिन्हित to the encoder (and used क्रम the host bus).
 *
 * GPIO  2 through  0 - On the cx23885 bridge
 * GPIO 18 through  3 - On the cx23417 host bus पूर्णांकerface
 * GPIO 23 through 19 - On the cx25840 a/v core
 */
व्योम cx23885_gpio_set(काष्ठा cx23885_dev *dev, u32 mask)
अणु
	अगर (mask & 0x7)
		cx_set(GP0_IO, mask & 0x7);

	अगर (mask & 0x0007fff8) अणु
		अगर (encoder_on_portb(dev) || encoder_on_portc(dev))
			pr_err("%s: Setting GPIO on encoder ports\n",
				dev->name);
		cx_set(MC417_RWD, (mask & 0x0007fff8) >> 3);
	पूर्ण

	/* TODO: 23-19 */
	अगर (mask & 0x00f80000)
		pr_info("%s: Unsupported\n", dev->name);
पूर्ण

व्योम cx23885_gpio_clear(काष्ठा cx23885_dev *dev, u32 mask)
अणु
	अगर (mask & 0x00000007)
		cx_clear(GP0_IO, mask & 0x7);

	अगर (mask & 0x0007fff8) अणु
		अगर (encoder_on_portb(dev) || encoder_on_portc(dev))
			pr_err("%s: Clearing GPIO moving on encoder ports\n",
				dev->name);
		cx_clear(MC417_RWD, (mask & 0x7fff8) >> 3);
	पूर्ण

	/* TODO: 23-19 */
	अगर (mask & 0x00f80000)
		pr_info("%s: Unsupported\n", dev->name);
पूर्ण

u32 cx23885_gpio_get(काष्ठा cx23885_dev *dev, u32 mask)
अणु
	अगर (mask & 0x00000007)
		वापस (cx_पढ़ो(GP0_IO) >> 8) & mask & 0x7;

	अगर (mask & 0x0007fff8) अणु
		अगर (encoder_on_portb(dev) || encoder_on_portc(dev))
			pr_err("%s: Reading GPIO moving on encoder ports\n",
				dev->name);
		वापस (cx_पढ़ो(MC417_RWD) & ((mask & 0x7fff8) >> 3)) << 3;
	पूर्ण

	/* TODO: 23-19 */
	अगर (mask & 0x00f80000)
		pr_info("%s: Unsupported\n", dev->name);

	वापस 0;
पूर्ण

व्योम cx23885_gpio_enable(काष्ठा cx23885_dev *dev, u32 mask, पूर्णांक asoutput)
अणु
	अगर ((mask & 0x00000007) && asoutput)
		cx_set(GP0_IO, (mask & 0x7) << 16);
	अन्यथा अगर ((mask & 0x00000007) && !asoutput)
		cx_clear(GP0_IO, (mask & 0x7) << 16);

	अगर (mask & 0x0007fff8) अणु
		अगर (encoder_on_portb(dev) || encoder_on_portc(dev))
			pr_err("%s: Enabling GPIO on encoder ports\n",
				dev->name);
	पूर्ण

	/* MC417_OEN is active low क्रम output, ग_लिखो 1 क्रम an input */
	अगर ((mask & 0x0007fff8) && asoutput)
		cx_clear(MC417_OEN, (mask & 0x7fff8) >> 3);

	अन्यथा अगर ((mask & 0x0007fff8) && !asoutput)
		cx_set(MC417_OEN, (mask & 0x7fff8) >> 3);

	/* TODO: 23-19 */
पूर्ण

अटल काष्ठा अणु
	पूर्णांक venकरोr, dev;
पूर्ण स्थिर broken_dev_id[] = अणु
	/* According with
	 * https://खोलोbenchmarking.org/प्रणाली/1703021-RI-AMDZEN08075/Ryzen%207%201800X/lspci,
	 * 0x1451 is PCI ID क्रम the IOMMU found on Ryzen
	 */
	अणु PCI_VENDOR_ID_AMD, 0x1451 पूर्ण,
	/* According to suकरो lspci -nn,
	 * 0x1423 is the PCI ID क्रम the IOMMU found on Kaveri
	 */
	अणु PCI_VENDOR_ID_AMD, 0x1423 पूर्ण,
	/* 0x1481 is the PCI ID क्रम the IOMMU found on Starship/Matisse
	 */
	अणु PCI_VENDOR_ID_AMD, 0x1481 पूर्ण,
	/* 0x1419 is the PCI ID क्रम the IOMMU found on 15h (Models 10h-1fh) family
	 */
	अणु PCI_VENDOR_ID_AMD, 0x1419 पूर्ण,
	/* 0x5a23 is the PCI ID क्रम the IOMMU found on RD890S/RD990
	 */
	अणु PCI_VENDOR_ID_ATI, 0x5a23 पूर्ण,
पूर्ण;

अटल bool cx23885_करोes_need_dma_reset(व्योम)
अणु
	पूर्णांक i;
	काष्ठा pci_dev *pdev = शून्य;

	अगर (dma_reset_workaround == 0)
		वापस false;
	अन्यथा अगर (dma_reset_workaround == 2)
		वापस true;

	क्रम (i = 0; i < ARRAY_SIZE(broken_dev_id); i++) अणु
		pdev = pci_get_device(broken_dev_id[i].venकरोr,
				      broken_dev_id[i].dev, शून्य);
		अगर (pdev) अणु
			pci_dev_put(pdev);
			वापस true;
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण

अटल पूर्णांक cx23885_initdev(काष्ठा pci_dev *pci_dev,
			   स्थिर काष्ठा pci_device_id *pci_id)
अणु
	काष्ठा cx23885_dev *dev;
	काष्ठा v4l2_ctrl_handler *hdl;
	पूर्णांक err;

	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (शून्य == dev)
		वापस -ENOMEM;

	dev->need_dma_reset = cx23885_करोes_need_dma_reset();

	err = v4l2_device_रेजिस्टर(&pci_dev->dev, &dev->v4l2_dev);
	अगर (err < 0)
		जाओ fail_मुक्त;

	hdl = &dev->ctrl_handler;
	v4l2_ctrl_handler_init(hdl, 6);
	अगर (hdl->error) अणु
		err = hdl->error;
		जाओ fail_ctrl;
	पूर्ण
	dev->v4l2_dev.ctrl_handler = hdl;

	/* Prepare to handle notअगरications from subdevices */
	cx23885_v4l2_dev_notअगरy_init(dev);

	/* pci init */
	dev->pci = pci_dev;
	अगर (pci_enable_device(pci_dev)) अणु
		err = -EIO;
		जाओ fail_ctrl;
	पूर्ण

	अगर (cx23885_dev_setup(dev) < 0) अणु
		err = -EINVAL;
		जाओ fail_ctrl;
	पूर्ण

	/* prपूर्णांक pci info */
	dev->pci_rev = pci_dev->revision;
	pci_पढ़ो_config_byte(pci_dev, PCI_LATENCY_TIMER,  &dev->pci_lat);
	pr_info("%s/0: found at %s, rev: %d, irq: %d, latency: %d, mmio: 0x%llx\n",
	       dev->name,
	       pci_name(pci_dev), dev->pci_rev, pci_dev->irq,
	       dev->pci_lat,
		(अचिन्हित दीर्घ दीर्घ)pci_resource_start(pci_dev, 0));

	pci_set_master(pci_dev);
	err = dma_set_mask(&pci_dev->dev, 0xffffffff);
	अगर (err) अणु
		pr_err("%s/0: Oops: no 32bit PCI DMA ???\n", dev->name);
		जाओ fail_ctrl;
	पूर्ण

	err = request_irq(pci_dev->irq, cx23885_irq,
			  IRQF_SHARED, dev->name, dev);
	अगर (err < 0) अणु
		pr_err("%s: can't get IRQ %d\n",
		       dev->name, pci_dev->irq);
		जाओ fail_irq;
	पूर्ण

	चयन (dev->board) अणु
	हाल CX23885_BOARD_NETUP_DUAL_DVBS2_CI:
		cx23885_irq_add_enable(dev, PCI_MSK_GPIO1 | PCI_MSK_GPIO0);
		अवरोध;
	हाल CX23885_BOARD_NETUP_DUAL_DVB_T_C_CI_RF:
		cx23885_irq_add_enable(dev, PCI_MSK_GPIO0);
		अवरोध;
	पूर्ण

	/*
	 * The CX2388[58] IR controller can start firing पूर्णांकerrupts when
	 * enabled, so these have to take place after the cx23885_irq() handler
	 * is hooked up by the call to request_irq() above.
	 */
	cx23885_ir_pci_पूर्णांक_enable(dev);
	cx23885_input_init(dev);

	वापस 0;

fail_irq:
	cx23885_dev_unरेजिस्टर(dev);
fail_ctrl:
	v4l2_ctrl_handler_मुक्त(hdl);
	v4l2_device_unरेजिस्टर(&dev->v4l2_dev);
fail_मुक्त:
	kमुक्त(dev);
	वापस err;
पूर्ण

अटल व्योम cx23885_finidev(काष्ठा pci_dev *pci_dev)
अणु
	काष्ठा v4l2_device *v4l2_dev = pci_get_drvdata(pci_dev);
	काष्ठा cx23885_dev *dev = to_cx23885(v4l2_dev);

	cx23885_input_fini(dev);
	cx23885_ir_fini(dev);

	cx23885_shutकरोwn(dev);

	/* unरेजिस्टर stuff */
	मुक्त_irq(pci_dev->irq, dev);

	pci_disable_device(pci_dev);

	cx23885_dev_unरेजिस्टर(dev);
	v4l2_ctrl_handler_मुक्त(&dev->ctrl_handler);
	v4l2_device_unरेजिस्टर(v4l2_dev);
	kमुक्त(dev);
पूर्ण

अटल स्थिर काष्ठा pci_device_id cx23885_pci_tbl[] = अणु
	अणु
		/* CX23885 */
		.venकरोr       = 0x14f1,
		.device       = 0x8852,
		.subvenकरोr    = PCI_ANY_ID,
		.subdevice    = PCI_ANY_ID,
	पूर्ण, अणु
		/* CX23887 Rev 2 */
		.venकरोr       = 0x14f1,
		.device       = 0x8880,
		.subvenकरोr    = PCI_ANY_ID,
		.subdevice    = PCI_ANY_ID,
	पूर्ण, अणु
		/* --- end of list --- */
	पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, cx23885_pci_tbl);

अटल काष्ठा pci_driver cx23885_pci_driver = अणु
	.name     = "cx23885",
	.id_table = cx23885_pci_tbl,
	.probe    = cx23885_initdev,
	.हटाओ   = cx23885_finidev,
पूर्ण;

अटल पूर्णांक __init cx23885_init(व्योम)
अणु
	pr_info("cx23885 driver version %s loaded\n",
		CX23885_VERSION);
	वापस pci_रेजिस्टर_driver(&cx23885_pci_driver);
पूर्ण

अटल व्योम __निकास cx23885_fini(व्योम)
अणु
	pci_unरेजिस्टर_driver(&cx23885_pci_driver);
पूर्ण

module_init(cx23885_init);
module_निकास(cx23885_fini);
