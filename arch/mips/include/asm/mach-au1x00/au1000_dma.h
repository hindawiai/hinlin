<शैली गुरु>
/*
 * BRIEF MODULE DESCRIPTION
 *	Defines क्रम using and allocating DMA channels on the Alchemy
 *      Au1x00 MIPS processors.
 *
 * Copyright 2000, 2008 MontaVista Software Inc.
 * Author: MontaVista Software, Inc. <source@mvista.com>
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
#अगर_अघोषित __ASM_AU1000_DMA_H
#घोषणा __ASM_AU1000_DMA_H

#समावेश <linux/पन.स>		/* need byte IO */
#समावेश <linux/spinlock.h>	/* And spinlocks */
#समावेश <linux/delay.h>

#घोषणा NUM_AU1000_DMA_CHANNELS 8

/* DMA Channel Register Offsets */
#घोषणा DMA_MODE_SET		0x00000000
#घोषणा DMA_MODE_READ		DMA_MODE_SET
#घोषणा DMA_MODE_CLEAR		0x00000004
/* DMA Mode रेजिस्टर bits follow */
#घोषणा DMA_DAH_MASK		(0x0f << 20)
#घोषणा DMA_DID_BIT		16
#घोषणा DMA_DID_MASK		(0x0f << DMA_DID_BIT)
#घोषणा DMA_DS			(1 << 15)
#घोषणा DMA_BE			(1 << 13)
#घोषणा DMA_DR			(1 << 12)
#घोषणा DMA_TS8			(1 << 11)
#घोषणा DMA_DW_BIT		9
#घोषणा DMA_DW_MASK		(0x03 << DMA_DW_BIT)
#घोषणा DMA_DW8			(0 << DMA_DW_BIT)
#घोषणा DMA_DW16		(1 << DMA_DW_BIT)
#घोषणा DMA_DW32		(2 << DMA_DW_BIT)
#घोषणा DMA_NC			(1 << 8)
#घोषणा DMA_IE			(1 << 7)
#घोषणा DMA_HALT		(1 << 6)
#घोषणा DMA_GO			(1 << 5)
#घोषणा DMA_AB			(1 << 4)
#घोषणा DMA_D1			(1 << 3)
#घोषणा DMA_BE1			(1 << 2)
#घोषणा DMA_D0			(1 << 1)
#घोषणा DMA_BE0			(1 << 0)

#घोषणा DMA_PERIPHERAL_ADDR	0x00000008
#घोषणा DMA_BUFFER0_START	0x0000000C
#घोषणा DMA_BUFFER1_START	0x00000014
#घोषणा DMA_BUFFER0_COUNT	0x00000010
#घोषणा DMA_BUFFER1_COUNT	0x00000018
#घोषणा DMA_BAH_BIT	16
#घोषणा DMA_BAH_MASK	(0x0f << DMA_BAH_BIT)
#घोषणा DMA_COUNT_BIT	0
#घोषणा DMA_COUNT_MASK	(0xffff << DMA_COUNT_BIT)

/* DMA Device IDs follow */
क्रमागत अणु
	DMA_ID_UART0_TX = 0,
	DMA_ID_UART0_RX,
	DMA_ID_GP04,
	DMA_ID_GP05,
	DMA_ID_AC97C_TX,
	DMA_ID_AC97C_RX,
	DMA_ID_UART3_TX,
	DMA_ID_UART3_RX,
	DMA_ID_USBDEV_EP0_RX,
	DMA_ID_USBDEV_EP0_TX,
	DMA_ID_USBDEV_EP2_TX,
	DMA_ID_USBDEV_EP3_TX,
	DMA_ID_USBDEV_EP4_RX,
	DMA_ID_USBDEV_EP5_RX,
	DMA_ID_I2S_TX,
	DMA_ID_I2S_RX,
	DMA_NUM_DEV
पूर्ण;

/* DMA Device ID's क्रम 2nd bank (AU1100) follow */
क्रमागत अणु
	DMA_ID_SD0_TX = 0,
	DMA_ID_SD0_RX,
	DMA_ID_SD1_TX,
	DMA_ID_SD1_RX,
	DMA_NUM_DEV_BANK2
पूर्ण;

काष्ठा dma_chan अणु
	पूर्णांक dev_id;		/* this channel is allocated अगर >= 0, */
				/* मुक्त otherwise */
	व्योम __iomem *io;
	स्थिर अक्षर *dev_str;
	पूर्णांक irq;
	व्योम *irq_dev;
	अचिन्हित पूर्णांक fअगरo_addr;
	अचिन्हित पूर्णांक mode;
पूर्ण;

/* These are in arch/mips/au1000/common/dma.c */
बाह्य काष्ठा dma_chan au1000_dma_table[];
बाह्य पूर्णांक request_au1000_dma(पूर्णांक dev_id,
			      स्थिर अक्षर *dev_str,
			      irq_handler_t irqhandler,
			      अचिन्हित दीर्घ irqflags,
			      व्योम *irq_dev_id);
बाह्य व्योम मुक्त_au1000_dma(अचिन्हित पूर्णांक dmanr);
बाह्य पूर्णांक au1000_dma_पढ़ो_proc(अक्षर *buf, अक्षर **start, off_t fpos,
				पूर्णांक length, पूर्णांक *eof, व्योम *data);
बाह्य व्योम dump_au1000_dma_channel(अचिन्हित पूर्णांक dmanr);
बाह्य spinlock_t au1000_dma_spin_lock;

अटल अंतरभूत काष्ठा dma_chan *get_dma_chan(अचिन्हित पूर्णांक dmanr)
अणु
	अगर (dmanr >= NUM_AU1000_DMA_CHANNELS ||
	    au1000_dma_table[dmanr].dev_id < 0)
		वापस शून्य;
	वापस &au1000_dma_table[dmanr];
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ claim_dma_lock(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&au1000_dma_spin_lock, flags);
	वापस flags;
पूर्ण

अटल अंतरभूत व्योम release_dma_lock(अचिन्हित दीर्घ flags)
अणु
	spin_unlock_irqrestore(&au1000_dma_spin_lock, flags);
पूर्ण

/*
 * Set the DMA buffer enable bits in the mode रेजिस्टर.
 */
अटल अंतरभूत व्योम enable_dma_buffer0(अचिन्हित पूर्णांक dmanr)
अणु
	काष्ठा dma_chan *chan = get_dma_chan(dmanr);

	अगर (!chan)
		वापस;
	__raw_ग_लिखोl(DMA_BE0, chan->io + DMA_MODE_SET);
पूर्ण

अटल अंतरभूत व्योम enable_dma_buffer1(अचिन्हित पूर्णांक dmanr)
अणु
	काष्ठा dma_chan *chan = get_dma_chan(dmanr);

	अगर (!chan)
		वापस;
	__raw_ग_लिखोl(DMA_BE1, chan->io + DMA_MODE_SET);
पूर्ण
अटल अंतरभूत व्योम enable_dma_buffers(अचिन्हित पूर्णांक dmanr)
अणु
	काष्ठा dma_chan *chan = get_dma_chan(dmanr);

	अगर (!chan)
		वापस;
	__raw_ग_लिखोl(DMA_BE0 | DMA_BE1, chan->io + DMA_MODE_SET);
पूर्ण

अटल अंतरभूत व्योम start_dma(अचिन्हित पूर्णांक dmanr)
अणु
	काष्ठा dma_chan *chan = get_dma_chan(dmanr);

	अगर (!chan)
		वापस;
	__raw_ग_लिखोl(DMA_GO, chan->io + DMA_MODE_SET);
पूर्ण

#घोषणा DMA_HALT_POLL 0x5000

अटल अंतरभूत व्योम halt_dma(अचिन्हित पूर्णांक dmanr)
अणु
	काष्ठा dma_chan *chan = get_dma_chan(dmanr);
	पूर्णांक i;

	अगर (!chan)
		वापस;
	__raw_ग_लिखोl(DMA_GO, chan->io + DMA_MODE_CLEAR);

	/* Poll the halt bit */
	क्रम (i = 0; i < DMA_HALT_POLL; i++)
		अगर (__raw_पढ़ोl(chan->io + DMA_MODE_READ) & DMA_HALT)
			अवरोध;
	अगर (i == DMA_HALT_POLL)
		prपूर्णांकk(KERN_INFO "halt_dma: HALT poll expired!\n");
पूर्ण

अटल अंतरभूत व्योम disable_dma(अचिन्हित पूर्णांक dmanr)
अणु
	काष्ठा dma_chan *chan = get_dma_chan(dmanr);

	अगर (!chan)
		वापस;

	halt_dma(dmanr);

	/* Now we can disable the buffers */
	__raw_ग_लिखोl(~DMA_GO, chan->io + DMA_MODE_CLEAR);
पूर्ण

अटल अंतरभूत पूर्णांक dma_halted(अचिन्हित पूर्णांक dmanr)
अणु
	काष्ठा dma_chan *chan = get_dma_chan(dmanr);

	अगर (!chan)
		वापस 1;
	वापस (__raw_पढ़ोl(chan->io + DMA_MODE_READ) & DMA_HALT) ? 1 : 0;
पूर्ण

/* Initialize a DMA channel. */
अटल अंतरभूत व्योम init_dma(अचिन्हित पूर्णांक dmanr)
अणु
	काष्ठा dma_chan *chan = get_dma_chan(dmanr);
	u32 mode;

	अगर (!chan)
		वापस;

	disable_dma(dmanr);

	/* Set device FIFO address */
	__raw_ग_लिखोl(CPHYSADDR(chan->fअगरo_addr), chan->io + DMA_PERIPHERAL_ADDR);

	mode = chan->mode | (chan->dev_id << DMA_DID_BIT);
	अगर (chan->irq)
		mode |= DMA_IE;

	__raw_ग_लिखोl(~mode, chan->io + DMA_MODE_CLEAR);
	__raw_ग_लिखोl(mode,	 chan->io + DMA_MODE_SET);
पूर्ण

/*
 * Set mode क्रम a specअगरic DMA channel
 */
अटल अंतरभूत व्योम set_dma_mode(अचिन्हित पूर्णांक dmanr, अचिन्हित पूर्णांक mode)
अणु
	काष्ठा dma_chan *chan = get_dma_chan(dmanr);

	अगर (!chan)
		वापस;
	/*
	 * set_dma_mode is only allowed to change endianess, direction,
	 * transfer size, device FIFO width, and coherency settings.
	 * Make sure anything अन्यथा is masked off.
	 */
	mode &= (DMA_BE | DMA_DR | DMA_TS8 | DMA_DW_MASK | DMA_NC);
	chan->mode &= ~(DMA_BE | DMA_DR | DMA_TS8 | DMA_DW_MASK | DMA_NC);
	chan->mode |= mode;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक get_dma_mode(अचिन्हित पूर्णांक dmanr)
अणु
	काष्ठा dma_chan *chan = get_dma_chan(dmanr);

	अगर (!chan)
		वापस 0;
	वापस chan->mode;
पूर्ण

अटल अंतरभूत पूर्णांक get_dma_active_buffer(अचिन्हित पूर्णांक dmanr)
अणु
	काष्ठा dma_chan *chan = get_dma_chan(dmanr);

	अगर (!chan)
		वापस -1;
	वापस (__raw_पढ़ोl(chan->io + DMA_MODE_READ) & DMA_AB) ? 1 : 0;
पूर्ण

/*
 * Set the device FIFO address क्रम a specअगरic DMA channel - only
 * applicable to GPO4 and GPO5. All the other devices have fixed
 * FIFO addresses.
 */
अटल अंतरभूत व्योम set_dma_fअगरo_addr(अचिन्हित पूर्णांक dmanr, अचिन्हित पूर्णांक a)
अणु
	काष्ठा dma_chan *chan = get_dma_chan(dmanr);

	अगर (!chan)
		वापस;

	अगर (chan->mode & DMA_DS)	/* second bank of device IDs */
		वापस;

	अगर (chan->dev_id != DMA_ID_GP04 && chan->dev_id != DMA_ID_GP05)
		वापस;

	__raw_ग_लिखोl(CPHYSADDR(a), chan->io + DMA_PERIPHERAL_ADDR);
पूर्ण

/*
 * Clear the DMA buffer करोne bits in the mode रेजिस्टर.
 */
अटल अंतरभूत व्योम clear_dma_करोne0(अचिन्हित पूर्णांक dmanr)
अणु
	काष्ठा dma_chan *chan = get_dma_chan(dmanr);

	अगर (!chan)
		वापस;
	__raw_ग_लिखोl(DMA_D0, chan->io + DMA_MODE_CLEAR);
पूर्ण

अटल अंतरभूत व्योम clear_dma_करोne1(अचिन्हित पूर्णांक dmanr)
अणु
	काष्ठा dma_chan *chan = get_dma_chan(dmanr);

	अगर (!chan)
		वापस;
	__raw_ग_लिखोl(DMA_D1, chan->io + DMA_MODE_CLEAR);
पूर्ण

/*
 * This करोes nothing - not applicable to Au1000 DMA.
 */
अटल अंतरभूत व्योम set_dma_page(अचिन्हित पूर्णांक dmanr, अक्षर pagenr)
अणु
पूर्ण

/*
 * Set Buffer 0 transfer address क्रम specअगरic DMA channel.
 */
अटल अंतरभूत व्योम set_dma_addr0(अचिन्हित पूर्णांक dmanr, अचिन्हित पूर्णांक a)
अणु
	काष्ठा dma_chan *chan = get_dma_chan(dmanr);

	अगर (!chan)
		वापस;
	__raw_ग_लिखोl(a, chan->io + DMA_BUFFER0_START);
पूर्ण

/*
 * Set Buffer 1 transfer address क्रम specअगरic DMA channel.
 */
अटल अंतरभूत व्योम set_dma_addr1(अचिन्हित पूर्णांक dmanr, अचिन्हित पूर्णांक a)
अणु
	काष्ठा dma_chan *chan = get_dma_chan(dmanr);

	अगर (!chan)
		वापस;
	__raw_ग_लिखोl(a, chan->io + DMA_BUFFER1_START);
पूर्ण


/*
 * Set Buffer 0 transfer size (max 64k) क्रम a specअगरic DMA channel.
 */
अटल अंतरभूत व्योम set_dma_count0(अचिन्हित पूर्णांक dmanr, अचिन्हित पूर्णांक count)
अणु
	काष्ठा dma_chan *chan = get_dma_chan(dmanr);

	अगर (!chan)
		वापस;
	count &= DMA_COUNT_MASK;
	__raw_ग_लिखोl(count, chan->io + DMA_BUFFER0_COUNT);
पूर्ण

/*
 * Set Buffer 1 transfer size (max 64k) क्रम a specअगरic DMA channel.
 */
अटल अंतरभूत व्योम set_dma_count1(अचिन्हित पूर्णांक dmanr, अचिन्हित पूर्णांक count)
अणु
	काष्ठा dma_chan *chan = get_dma_chan(dmanr);

	अगर (!chan)
		वापस;
	count &= DMA_COUNT_MASK;
	__raw_ग_लिखोl(count, chan->io + DMA_BUFFER1_COUNT);
पूर्ण

/*
 * Set both buffer transfer sizes (max 64k) क्रम a specअगरic DMA channel.
 */
अटल अंतरभूत व्योम set_dma_count(अचिन्हित पूर्णांक dmanr, अचिन्हित पूर्णांक count)
अणु
	काष्ठा dma_chan *chan = get_dma_chan(dmanr);

	अगर (!chan)
		वापस;
	count &= DMA_COUNT_MASK;
	__raw_ग_लिखोl(count, chan->io + DMA_BUFFER0_COUNT);
	__raw_ग_लिखोl(count, chan->io + DMA_BUFFER1_COUNT);
पूर्ण

/*
 * Returns which buffer has its करोne bit set in the mode रेजिस्टर.
 * Returns -1 अगर neither or both करोne bits set.
 */
अटल अंतरभूत अचिन्हित पूर्णांक get_dma_buffer_करोne(अचिन्हित पूर्णांक dmanr)
अणु
	काष्ठा dma_chan *chan = get_dma_chan(dmanr);

	अगर (!chan)
		वापस 0;
	वापस __raw_पढ़ोl(chan->io + DMA_MODE_READ) & (DMA_D0 | DMA_D1);
पूर्ण


/*
 * Returns the DMA channel's Buffer Done IRQ number.
 */
अटल अंतरभूत पूर्णांक get_dma_करोne_irq(अचिन्हित पूर्णांक dmanr)
अणु
	काष्ठा dma_chan *chan = get_dma_chan(dmanr);

	अगर (!chan)
		वापस -1;
	वापस chan->irq;
पूर्ण

/*
 * Get DMA residue count. Returns the number of _bytes_ left to transfer.
 */
अटल अंतरभूत पूर्णांक get_dma_residue(अचिन्हित पूर्णांक dmanr)
अणु
	पूर्णांक curBufCntReg, count;
	काष्ठा dma_chan *chan = get_dma_chan(dmanr);

	अगर (!chan)
		वापस 0;

	curBufCntReg = (__raw_पढ़ोl(chan->io + DMA_MODE_READ) & DMA_AB) ?
	    DMA_BUFFER1_COUNT : DMA_BUFFER0_COUNT;

	count = __raw_पढ़ोl(chan->io + curBufCntReg) & DMA_COUNT_MASK;

	अगर ((chan->mode & DMA_DW_MASK) == DMA_DW16)
		count <<= 1;
	अन्यथा अगर ((chan->mode & DMA_DW_MASK) == DMA_DW32)
		count <<= 2;

	वापस count;
पूर्ण

#पूर्ण_अगर /* __ASM_AU1000_DMA_H */
