<शैली गुरु>
/*
 *
 * BRIEF MODULE DESCRIPTION
 *      A DMA channel allocator क्रम Au1x00. API is modeled loosely off of
 *      linux/kernel/dma.c.
 *
 * Copyright 2000, 2008 MontaVista Software Inc.
 * Author: MontaVista Software, Inc. <source@mvista.com>
 * Copyright (C) 2005 Ralf Baechle (ralf@linux-mips.org)
 *
 *  This program is मुक्त software; you can redistribute  it and/or modअगरy it
 *  under  the terms of  the GNU General  Public License as published by the
 *  Free Software Foundation;  either version 2 of the  License, or (at your
 *  option) any later version.
 *
 *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS'' AND   ANY  EXPRESS OR IMPLIED
 *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF
 *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN
 *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   सूचीECT, INसूचीECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF
 *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *  You should have received a copy of the  GNU General Public License aदीर्घ
 *  with this program; अगर not, ग_लिखो  to the Free Software Foundation, Inc.,
 *  675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */

#समावेश <linux/init.h>
#समावेश <linux/export.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/spinlock.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश <यंत्र/mach-au1x00/au1000.h>
#समावेश <यंत्र/mach-au1x00/au1000_dma.h>

/*
 * A note on resource allocation:
 *
 * All drivers needing DMA channels, should allocate and release them
 * through the खुला routines `request_dma()' and `free_dma()'.
 *
 * In order to aव्योम problems, all processes should allocate resources in
 * the same sequence and release them in the reverse order.
 *
 * So, when allocating DMAs and IRQs, first allocate the DMA, then the IRQ.
 * When releasing them, first release the IRQ, then release the DMA. The
 * मुख्य reason क्रम this order is that, अगर you are requesting the DMA buffer
 * करोne पूर्णांकerrupt, you won't know the irq number until the DMA channel is
 * वापसed from request_dma.
 */

/* DMA Channel रेजिस्टर block spacing */
#घोषणा DMA_CHANNEL_LEN		0x00000100

DEFINE_SPINLOCK(au1000_dma_spin_lock);

काष्ठा dma_chan au1000_dma_table[NUM_AU1000_DMA_CHANNELS] = अणु
      अणु.dev_id = -1,पूर्ण,
      अणु.dev_id = -1,पूर्ण,
      अणु.dev_id = -1,पूर्ण,
      अणु.dev_id = -1,पूर्ण,
      अणु.dev_id = -1,पूर्ण,
      अणु.dev_id = -1,पूर्ण,
      अणु.dev_id = -1,पूर्ण,
      अणु.dev_id = -1,पूर्ण
पूर्ण;
EXPORT_SYMBOL(au1000_dma_table);

/* Device FIFO addresses and शेष DMA modes */
अटल स्थिर काष्ठा dma_dev अणु
	अचिन्हित पूर्णांक fअगरo_addr;
	अचिन्हित पूर्णांक dma_mode;
पूर्ण dma_dev_table[DMA_NUM_DEV] = अणु
	अणु AU1000_UART0_PHYS_ADDR + 0x04, DMA_DW8 पूर्ण,		/* UART0_TX */
	अणु AU1000_UART0_PHYS_ADDR + 0x00, DMA_DW8 | DMA_DR पूर्ण,	/* UART0_RX */
	अणु 0, 0 पूर्ण,	/* DMA_REQ0 */
	अणु 0, 0 पूर्ण,	/* DMA_REQ1 */
	अणु AU1000_AC97_PHYS_ADDR + 0x08, DMA_DW16 पूर्ण,		/* AC97 TX c */
	अणु AU1000_AC97_PHYS_ADDR + 0x08, DMA_DW16 | DMA_DR पूर्ण,	/* AC97 RX c */
	अणु AU1000_UART3_PHYS_ADDR + 0x04, DMA_DW8 | DMA_NC पूर्ण,	/* UART3_TX */
	अणु AU1000_UART3_PHYS_ADDR + 0x00, DMA_DW8 | DMA_NC | DMA_DR पूर्ण, /* UART3_RX */
	अणु AU1000_USB_UDC_PHYS_ADDR + 0x00, DMA_DW8 | DMA_NC | DMA_DR पूर्ण, /* EP0RD */
	अणु AU1000_USB_UDC_PHYS_ADDR + 0x04, DMA_DW8 | DMA_NC पूर्ण, /* EP0WR */
	अणु AU1000_USB_UDC_PHYS_ADDR + 0x08, DMA_DW8 | DMA_NC पूर्ण, /* EP2WR */
	अणु AU1000_USB_UDC_PHYS_ADDR + 0x0c, DMA_DW8 | DMA_NC पूर्ण, /* EP3WR */
	अणु AU1000_USB_UDC_PHYS_ADDR + 0x10, DMA_DW8 | DMA_NC | DMA_DR पूर्ण, /* EP4RD */
	अणु AU1000_USB_UDC_PHYS_ADDR + 0x14, DMA_DW8 | DMA_NC | DMA_DR पूर्ण, /* EP5RD */
	/* on Au1500, these 2 are DMA_REQ2/3 (GPIO208/209) instead! */
	अणु AU1000_I2S_PHYS_ADDR + 0x00, DMA_DW32 | DMA_NCपूर्ण,	/* I2S TX */
	अणु AU1000_I2S_PHYS_ADDR + 0x00, DMA_DW32 | DMA_NC | DMA_DRपूर्ण, /* I2S RX */
पूर्ण;

पूर्णांक au1000_dma_पढ़ो_proc(अक्षर *buf, अक्षर **start, off_t fpos,
			 पूर्णांक length, पूर्णांक *eof, व्योम *data)
अणु
	पूर्णांक i, len = 0;
	काष्ठा dma_chan *chan;

	क्रम (i = 0; i < NUM_AU1000_DMA_CHANNELS; i++) अणु
		chan = get_dma_chan(i);
		अगर (chan != शून्य)
			len += प्र_लिखो(buf + len, "%2d: %s\n",
				       i, chan->dev_str);
	पूर्ण

	अगर (fpos >= len) अणु
		*start = buf;
		*eof = 1;
		वापस 0;
	पूर्ण
	*start = buf + fpos;
	len -= fpos;
	अगर (len > length)
		वापस length;
	*eof = 1;
	वापस len;
पूर्ण

/* Device FIFO addresses and शेष DMA modes - 2nd bank */
अटल स्थिर काष्ठा dma_dev dma_dev_table_bank2[DMA_NUM_DEV_BANK2] = अणु
	अणु AU1100_SD0_PHYS_ADDR + 0x00, DMA_DS | DMA_DW8 पूर्ण,		/* coherent */
	अणु AU1100_SD0_PHYS_ADDR + 0x04, DMA_DS | DMA_DW8 | DMA_DR पूर्ण,	/* coherent */
	अणु AU1100_SD1_PHYS_ADDR + 0x00, DMA_DS | DMA_DW8 पूर्ण,		/* coherent */
	अणु AU1100_SD1_PHYS_ADDR + 0x04, DMA_DS | DMA_DW8 | DMA_DR पूर्ण	/* coherent */
पूर्ण;

व्योम dump_au1000_dma_channel(अचिन्हित पूर्णांक dmanr)
अणु
	काष्ठा dma_chan *chan;

	अगर (dmanr >= NUM_AU1000_DMA_CHANNELS)
		वापस;
	chan = &au1000_dma_table[dmanr];

	prपूर्णांकk(KERN_INFO "Au1000 DMA%d Register Dump:\n", dmanr);
	prपूर्णांकk(KERN_INFO "  mode = 0x%08x\n",
	       __raw_पढ़ोl(chan->io + DMA_MODE_SET));
	prपूर्णांकk(KERN_INFO "  addr = 0x%08x\n",
	       __raw_पढ़ोl(chan->io + DMA_PERIPHERAL_ADDR));
	prपूर्णांकk(KERN_INFO "  start0 = 0x%08x\n",
	       __raw_पढ़ोl(chan->io + DMA_BUFFER0_START));
	prपूर्णांकk(KERN_INFO "  start1 = 0x%08x\n",
	       __raw_पढ़ोl(chan->io + DMA_BUFFER1_START));
	prपूर्णांकk(KERN_INFO "  count0 = 0x%08x\n",
	       __raw_पढ़ोl(chan->io + DMA_BUFFER0_COUNT));
	prपूर्णांकk(KERN_INFO "  count1 = 0x%08x\n",
	       __raw_पढ़ोl(chan->io + DMA_BUFFER1_COUNT));
पूर्ण

/*
 * Finds a मुक्त channel, and binds the requested device to it.
 * Returns the allocated channel number, or negative on error.
 * Requests the DMA करोne IRQ अगर irqhandler != शून्य.
 */
पूर्णांक request_au1000_dma(पूर्णांक dev_id, स्थिर अक्षर *dev_str,
		       irq_handler_t irqhandler,
		       अचिन्हित दीर्घ irqflags,
		       व्योम *irq_dev_id)
अणु
	काष्ठा dma_chan *chan;
	स्थिर काष्ठा dma_dev *dev;
	पूर्णांक i, ret;

	अगर (alchemy_get_cputype() == ALCHEMY_CPU_AU1100) अणु
		अगर (dev_id < 0 || dev_id >= (DMA_NUM_DEV + DMA_NUM_DEV_BANK2))
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		अगर (dev_id < 0 || dev_id >= DMA_NUM_DEV)
			वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < NUM_AU1000_DMA_CHANNELS; i++)
		अगर (au1000_dma_table[i].dev_id < 0)
			अवरोध;

	अगर (i == NUM_AU1000_DMA_CHANNELS)
		वापस -ENODEV;

	chan = &au1000_dma_table[i];

	अगर (dev_id >= DMA_NUM_DEV) अणु
		dev_id -= DMA_NUM_DEV;
		dev = &dma_dev_table_bank2[dev_id];
	पूर्ण अन्यथा
		dev = &dma_dev_table[dev_id];

	अगर (irqhandler) अणु
		chan->irq_dev = irq_dev_id;
		ret = request_irq(chan->irq, irqhandler, irqflags, dev_str,
				  chan->irq_dev);
		अगर (ret) अणु
			chan->irq_dev = शून्य;
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		chan->irq_dev = शून्य;
	पूर्ण

	/* fill it in */
	chan->io = (व्योम __iomem *)(KSEG1ADDR(AU1000_DMA_PHYS_ADDR) +
			i * DMA_CHANNEL_LEN);
	chan->dev_id = dev_id;
	chan->dev_str = dev_str;
	chan->fअगरo_addr = dev->fअगरo_addr;
	chan->mode = dev->dma_mode;

	/* initialize the channel beक्रमe वापसing */
	init_dma(i);

	वापस i;
पूर्ण
EXPORT_SYMBOL(request_au1000_dma);

व्योम मुक्त_au1000_dma(अचिन्हित पूर्णांक dmanr)
अणु
	काष्ठा dma_chan *chan = get_dma_chan(dmanr);

	अगर (!chan) अणु
		prपूर्णांकk(KERN_ERR "Error trying to free DMA%d\n", dmanr);
		वापस;
	पूर्ण

	disable_dma(dmanr);
	अगर (chan->irq_dev)
		मुक्त_irq(chan->irq, chan->irq_dev);

	chan->irq_dev = शून्य;
	chan->dev_id = -1;
पूर्ण
EXPORT_SYMBOL(मुक्त_au1000_dma);

अटल पूर्णांक __init au1000_dma_init(व्योम)
अणु
	पूर्णांक base, i;

	चयन (alchemy_get_cputype()) अणु
	हाल ALCHEMY_CPU_AU1000:
		base = AU1000_DMA_INT_BASE;
		अवरोध;
	हाल ALCHEMY_CPU_AU1500:
		base = AU1500_DMA_INT_BASE;
		अवरोध;
	हाल ALCHEMY_CPU_AU1100:
		base = AU1100_DMA_INT_BASE;
		अवरोध;
	शेष:
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < NUM_AU1000_DMA_CHANNELS; i++)
		au1000_dma_table[i].irq = base + i;

	prपूर्णांकk(KERN_INFO "Alchemy DMA initialized\n");

out:
	वापस 0;
पूर्ण
arch_initcall(au1000_dma_init);
