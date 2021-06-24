<शैली गुरु>
/*
 *
 * BRIEF MODULE DESCRIPTION
 *      The Descriptor Based DMA channel manager that first appeared
 *	on the Au1550.  I started with dma.c, but I think all that is
 *	left is this initial comment :-)
 *
 * Copyright 2004 Embedded Edge, LLC
 *	dan@embeddededge.com
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
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/export.h>
#समावेश <linux/syscore_ops.h>
#समावेश <यंत्र/mach-au1x00/au1000.h>
#समावेश <यंत्र/mach-au1x00/au1xxx_dbdma.h>

/*
 * The Descriptor Based DMA supports up to 16 channels.
 *
 * There are 32 devices defined. We keep an पूर्णांकernal काष्ठाure
 * of devices using these channels, aदीर्घ with additional
 * inक्रमmation.
 *
 * We allocate the descriptors and allow access to them through various
 * functions.  The drivers allocate the data buffers and assign them
 * to the descriptors.
 */
अटल DEFINE_SPINLOCK(au1xxx_dbdma_spin_lock);

/* I couldn't find a macro that did this... */
#घोषणा ALIGN_ADDR(x, a)	((((u32)(x)) + (a-1)) & ~(a-1))

अटल dbdma_global_t *dbdma_gptr =
			(dbdma_global_t *)KSEG1ADDR(AU1550_DBDMA_CONF_PHYS_ADDR);
अटल पूर्णांक dbdma_initialized;

अटल dbdev_tab_t *dbdev_tab;

अटल dbdev_tab_t au1550_dbdev_tab[] __initdata = अणु
	/* UARTS */
	अणु AU1550_DSCR_CMD0_UART0_TX, DEV_FLAGS_OUT, 0, 8, 0x11100004, 0, 0 पूर्ण,
	अणु AU1550_DSCR_CMD0_UART0_RX, DEV_FLAGS_IN,  0, 8, 0x11100000, 0, 0 पूर्ण,
	अणु AU1550_DSCR_CMD0_UART3_TX, DEV_FLAGS_OUT, 0, 8, 0x11400004, 0, 0 पूर्ण,
	अणु AU1550_DSCR_CMD0_UART3_RX, DEV_FLAGS_IN,  0, 8, 0x11400000, 0, 0 पूर्ण,

	/* EXT DMA */
	अणु AU1550_DSCR_CMD0_DMA_REQ0, 0, 0, 0, 0x00000000, 0, 0 पूर्ण,
	अणु AU1550_DSCR_CMD0_DMA_REQ1, 0, 0, 0, 0x00000000, 0, 0 पूर्ण,
	अणु AU1550_DSCR_CMD0_DMA_REQ2, 0, 0, 0, 0x00000000, 0, 0 पूर्ण,
	अणु AU1550_DSCR_CMD0_DMA_REQ3, 0, 0, 0, 0x00000000, 0, 0 पूर्ण,

	/* USB DEV */
	अणु AU1550_DSCR_CMD0_USBDEV_RX0, DEV_FLAGS_IN,  4, 8, 0x10200000, 0, 0 पूर्ण,
	अणु AU1550_DSCR_CMD0_USBDEV_TX0, DEV_FLAGS_OUT, 4, 8, 0x10200004, 0, 0 पूर्ण,
	अणु AU1550_DSCR_CMD0_USBDEV_TX1, DEV_FLAGS_OUT, 4, 8, 0x10200008, 0, 0 पूर्ण,
	अणु AU1550_DSCR_CMD0_USBDEV_TX2, DEV_FLAGS_OUT, 4, 8, 0x1020000c, 0, 0 पूर्ण,
	अणु AU1550_DSCR_CMD0_USBDEV_RX3, DEV_FLAGS_IN,  4, 8, 0x10200010, 0, 0 पूर्ण,
	अणु AU1550_DSCR_CMD0_USBDEV_RX4, DEV_FLAGS_IN,  4, 8, 0x10200014, 0, 0 पूर्ण,

	/* PSCs */
	अणु AU1550_DSCR_CMD0_PSC0_TX, DEV_FLAGS_OUT, 0, 0, 0x11a0001c, 0, 0 पूर्ण,
	अणु AU1550_DSCR_CMD0_PSC0_RX, DEV_FLAGS_IN,  0, 0, 0x11a0001c, 0, 0 पूर्ण,
	अणु AU1550_DSCR_CMD0_PSC1_TX, DEV_FLAGS_OUT, 0, 0, 0x11b0001c, 0, 0 पूर्ण,
	अणु AU1550_DSCR_CMD0_PSC1_RX, DEV_FLAGS_IN,  0, 0, 0x11b0001c, 0, 0 पूर्ण,
	अणु AU1550_DSCR_CMD0_PSC2_TX, DEV_FLAGS_OUT, 0, 0, 0x10a0001c, 0, 0 पूर्ण,
	अणु AU1550_DSCR_CMD0_PSC2_RX, DEV_FLAGS_IN,  0, 0, 0x10a0001c, 0, 0 पूर्ण,
	अणु AU1550_DSCR_CMD0_PSC3_TX, DEV_FLAGS_OUT, 0, 0, 0x10b0001c, 0, 0 पूर्ण,
	अणु AU1550_DSCR_CMD0_PSC3_RX, DEV_FLAGS_IN,  0, 0, 0x10b0001c, 0, 0 पूर्ण,

	अणु AU1550_DSCR_CMD0_PCI_WRITE,  0, 0, 0, 0x00000000, 0, 0 पूर्ण,  /* PCI */
	अणु AU1550_DSCR_CMD0_न_अंकD_FLASH, 0, 0, 0, 0x00000000, 0, 0 पूर्ण, /* न_अंकD */

	/* MAC 0 */
	अणु AU1550_DSCR_CMD0_MAC0_RX, DEV_FLAGS_IN,  0, 0, 0x00000000, 0, 0 पूर्ण,
	अणु AU1550_DSCR_CMD0_MAC0_TX, DEV_FLAGS_OUT, 0, 0, 0x00000000, 0, 0 पूर्ण,

	/* MAC 1 */
	अणु AU1550_DSCR_CMD0_MAC1_RX, DEV_FLAGS_IN,  0, 0, 0x00000000, 0, 0 पूर्ण,
	अणु AU1550_DSCR_CMD0_MAC1_TX, DEV_FLAGS_OUT, 0, 0, 0x00000000, 0, 0 पूर्ण,

	अणु DSCR_CMD0_THROTTLE, DEV_FLAGS_ANYUSE, 0, 0, 0x00000000, 0, 0 पूर्ण,
	अणु DSCR_CMD0_ALWAYS,   DEV_FLAGS_ANYUSE, 0, 0, 0x00000000, 0, 0 पूर्ण,
पूर्ण;

अटल dbdev_tab_t au1200_dbdev_tab[] __initdata = अणु
	अणु AU1200_DSCR_CMD0_UART0_TX, DEV_FLAGS_OUT, 0, 8, 0x11100004, 0, 0 पूर्ण,
	अणु AU1200_DSCR_CMD0_UART0_RX, DEV_FLAGS_IN,  0, 8, 0x11100000, 0, 0 पूर्ण,
	अणु AU1200_DSCR_CMD0_UART1_TX, DEV_FLAGS_OUT, 0, 8, 0x11200004, 0, 0 पूर्ण,
	अणु AU1200_DSCR_CMD0_UART1_RX, DEV_FLAGS_IN,  0, 8, 0x11200000, 0, 0 पूर्ण,

	अणु AU1200_DSCR_CMD0_DMA_REQ0, 0, 0, 0, 0x00000000, 0, 0 पूर्ण,
	अणु AU1200_DSCR_CMD0_DMA_REQ1, 0, 0, 0, 0x00000000, 0, 0 पूर्ण,

	अणु AU1200_DSCR_CMD0_MAE_BE, DEV_FLAGS_ANYUSE, 0, 0, 0x00000000, 0, 0 पूर्ण,
	अणु AU1200_DSCR_CMD0_MAE_FE, DEV_FLAGS_ANYUSE, 0, 0, 0x00000000, 0, 0 पूर्ण,
	अणु AU1200_DSCR_CMD0_MAE_BOTH, DEV_FLAGS_ANYUSE, 0, 0, 0x00000000, 0, 0 पूर्ण,
	अणु AU1200_DSCR_CMD0_LCD, DEV_FLAGS_ANYUSE, 0, 0, 0x00000000, 0, 0 पूर्ण,

	अणु AU1200_DSCR_CMD0_SDMS_TX0, DEV_FLAGS_OUT, 4, 8, 0x10600000, 0, 0 पूर्ण,
	अणु AU1200_DSCR_CMD0_SDMS_RX0, DEV_FLAGS_IN,  4, 8, 0x10600004, 0, 0 पूर्ण,
	अणु AU1200_DSCR_CMD0_SDMS_TX1, DEV_FLAGS_OUT, 4, 8, 0x10680000, 0, 0 पूर्ण,
	अणु AU1200_DSCR_CMD0_SDMS_RX1, DEV_FLAGS_IN,  4, 8, 0x10680004, 0, 0 पूर्ण,

	अणु AU1200_DSCR_CMD0_AES_RX, DEV_FLAGS_IN , 4, 32, 0x10300008, 0, 0 पूर्ण,
	अणु AU1200_DSCR_CMD0_AES_TX, DEV_FLAGS_OUT, 4, 32, 0x10300004, 0, 0 पूर्ण,

	अणु AU1200_DSCR_CMD0_PSC0_TX,   DEV_FLAGS_OUT, 0, 16, 0x11a0001c, 0, 0 पूर्ण,
	अणु AU1200_DSCR_CMD0_PSC0_RX,   DEV_FLAGS_IN,  0, 16, 0x11a0001c, 0, 0 पूर्ण,
	अणु AU1200_DSCR_CMD0_PSC0_SYNC, DEV_FLAGS_ANYUSE, 0, 0, 0x00000000, 0, 0 पूर्ण,
	अणु AU1200_DSCR_CMD0_PSC1_TX,   DEV_FLAGS_OUT, 0, 16, 0x11b0001c, 0, 0 पूर्ण,
	अणु AU1200_DSCR_CMD0_PSC1_RX,   DEV_FLAGS_IN,  0, 16, 0x11b0001c, 0, 0 पूर्ण,
	अणु AU1200_DSCR_CMD0_PSC1_SYNC, DEV_FLAGS_ANYUSE, 0, 0, 0x00000000, 0, 0 पूर्ण,

	अणु AU1200_DSCR_CMD0_CIM_RXA,  DEV_FLAGS_IN, 0, 32, 0x14004020, 0, 0 पूर्ण,
	अणु AU1200_DSCR_CMD0_CIM_RXB,  DEV_FLAGS_IN, 0, 32, 0x14004040, 0, 0 पूर्ण,
	अणु AU1200_DSCR_CMD0_CIM_RXC,  DEV_FLAGS_IN, 0, 32, 0x14004060, 0, 0 पूर्ण,
	अणु AU1200_DSCR_CMD0_CIM_SYNC, DEV_FLAGS_ANYUSE, 0, 0, 0x00000000, 0, 0 पूर्ण,

	अणु AU1200_DSCR_CMD0_न_अंकD_FLASH, DEV_FLAGS_IN, 0, 0, 0x00000000, 0, 0 पूर्ण,

	अणु DSCR_CMD0_THROTTLE, DEV_FLAGS_ANYUSE, 0, 0, 0x00000000, 0, 0 पूर्ण,
	अणु DSCR_CMD0_ALWAYS,   DEV_FLAGS_ANYUSE, 0, 0, 0x00000000, 0, 0 पूर्ण,
पूर्ण;

अटल dbdev_tab_t au1300_dbdev_tab[] __initdata = अणु
	अणु AU1300_DSCR_CMD0_UART0_TX, DEV_FLAGS_OUT, 0, 8,  0x10100004, 0, 0 पूर्ण,
	अणु AU1300_DSCR_CMD0_UART0_RX, DEV_FLAGS_IN,  0, 8,  0x10100000, 0, 0 पूर्ण,
	अणु AU1300_DSCR_CMD0_UART1_TX, DEV_FLAGS_OUT, 0, 8,  0x10101004, 0, 0 पूर्ण,
	अणु AU1300_DSCR_CMD0_UART1_RX, DEV_FLAGS_IN,  0, 8,  0x10101000, 0, 0 पूर्ण,
	अणु AU1300_DSCR_CMD0_UART2_TX, DEV_FLAGS_OUT, 0, 8,  0x10102004, 0, 0 पूर्ण,
	अणु AU1300_DSCR_CMD0_UART2_RX, DEV_FLAGS_IN,  0, 8,  0x10102000, 0, 0 पूर्ण,
	अणु AU1300_DSCR_CMD0_UART3_TX, DEV_FLAGS_OUT, 0, 8,  0x10103004, 0, 0 पूर्ण,
	अणु AU1300_DSCR_CMD0_UART3_RX, DEV_FLAGS_IN,  0, 8,  0x10103000, 0, 0 पूर्ण,

	अणु AU1300_DSCR_CMD0_SDMS_TX0, DEV_FLAGS_OUT, 4, 8,  0x10600000, 0, 0 पूर्ण,
	अणु AU1300_DSCR_CMD0_SDMS_RX0, DEV_FLAGS_IN,  4, 8,  0x10600004, 0, 0 पूर्ण,
	अणु AU1300_DSCR_CMD0_SDMS_TX1, DEV_FLAGS_OUT, 8, 8,  0x10601000, 0, 0 पूर्ण,
	अणु AU1300_DSCR_CMD0_SDMS_RX1, DEV_FLAGS_IN,  8, 8,  0x10601004, 0, 0 पूर्ण,

	अणु AU1300_DSCR_CMD0_AES_RX, DEV_FLAGS_IN ,   4, 32, 0x10300008, 0, 0 पूर्ण,
	अणु AU1300_DSCR_CMD0_AES_TX, DEV_FLAGS_OUT,   4, 32, 0x10300004, 0, 0 पूर्ण,

	अणु AU1300_DSCR_CMD0_PSC0_TX, DEV_FLAGS_OUT,  0, 16, 0x10a0001c, 0, 0 पूर्ण,
	अणु AU1300_DSCR_CMD0_PSC0_RX, DEV_FLAGS_IN,   0, 16, 0x10a0001c, 0, 0 पूर्ण,
	अणु AU1300_DSCR_CMD0_PSC1_TX, DEV_FLAGS_OUT,  0, 16, 0x10a0101c, 0, 0 पूर्ण,
	अणु AU1300_DSCR_CMD0_PSC1_RX, DEV_FLAGS_IN,   0, 16, 0x10a0101c, 0, 0 पूर्ण,
	अणु AU1300_DSCR_CMD0_PSC2_TX, DEV_FLAGS_OUT,  0, 16, 0x10a0201c, 0, 0 पूर्ण,
	अणु AU1300_DSCR_CMD0_PSC2_RX, DEV_FLAGS_IN,   0, 16, 0x10a0201c, 0, 0 पूर्ण,
	अणु AU1300_DSCR_CMD0_PSC3_TX, DEV_FLAGS_OUT,  0, 16, 0x10a0301c, 0, 0 पूर्ण,
	अणु AU1300_DSCR_CMD0_PSC3_RX, DEV_FLAGS_IN,   0, 16, 0x10a0301c, 0, 0 पूर्ण,

	अणु AU1300_DSCR_CMD0_LCD, DEV_FLAGS_ANYUSE,   0, 0,  0x00000000, 0, 0 पूर्ण,
	अणु AU1300_DSCR_CMD0_न_अंकD_FLASH, DEV_FLAGS_IN, 0, 0, 0x00000000, 0, 0 पूर्ण,

	अणु AU1300_DSCR_CMD0_SDMS_TX2, DEV_FLAGS_OUT, 4, 8,  0x10602000, 0, 0 पूर्ण,
	अणु AU1300_DSCR_CMD0_SDMS_RX2, DEV_FLAGS_IN,  4, 8,  0x10602004, 0, 0 पूर्ण,

	अणु AU1300_DSCR_CMD0_CIM_SYNC, DEV_FLAGS_ANYUSE, 0, 0, 0x00000000, 0, 0 पूर्ण,

	अणु AU1300_DSCR_CMD0_UDMA, DEV_FLAGS_ANYUSE,  0, 32, 0x14001810, 0, 0 पूर्ण,

	अणु AU1300_DSCR_CMD0_DMA_REQ0, 0, 0, 0, 0x00000000, 0, 0 पूर्ण,
	अणु AU1300_DSCR_CMD0_DMA_REQ1, 0, 0, 0, 0x00000000, 0, 0 पूर्ण,

	अणु DSCR_CMD0_THROTTLE, DEV_FLAGS_ANYUSE, 0, 0, 0x00000000, 0, 0 पूर्ण,
	अणु DSCR_CMD0_ALWAYS,   DEV_FLAGS_ANYUSE, 0, 0, 0x00000000, 0, 0 पूर्ण,
पूर्ण;

/* 32 predefined plus 32 custom */
#घोषणा DBDEV_TAB_SIZE		64

अटल chan_tab_t *chan_tab_ptr[NUM_DBDMA_CHANS];

अटल dbdev_tab_t *find_dbdev_id(u32 id)
अणु
	पूर्णांक i;
	dbdev_tab_t *p;
	क्रम (i = 0; i < DBDEV_TAB_SIZE; ++i) अणु
		p = &dbdev_tab[i];
		अगर (p->dev_id == id)
			वापस p;
	पूर्ण
	वापस शून्य;
पूर्ण

व्योम *au1xxx_ddma_get_nextptr_virt(au1x_ddma_desc_t *dp)
अणु
	वापस phys_to_virt(DSCR_GET_NXTPTR(dp->dscr_nxtptr));
पूर्ण
EXPORT_SYMBOL(au1xxx_ddma_get_nextptr_virt);

u32 au1xxx_ddma_add_device(dbdev_tab_t *dev)
अणु
	u32 ret = 0;
	dbdev_tab_t *p;
	अटल u16 new_id = 0x1000;

	p = find_dbdev_id(~0);
	अगर (शून्य != p) अणु
		स_नकल(p, dev, माप(dbdev_tab_t));
		p->dev_id = DSCR_DEV2CUSTOM_ID(new_id, dev->dev_id);
		ret = p->dev_id;
		new_id++;
#अगर 0
		prपूर्णांकk(KERN_DEBUG "add_device: id:%x flags:%x padd:%x\n",
				  p->dev_id, p->dev_flags, p->dev_physaddr);
#पूर्ण_अगर
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL(au1xxx_ddma_add_device);

व्योम au1xxx_ddma_del_device(u32 devid)
अणु
	dbdev_tab_t *p = find_dbdev_id(devid);

	अगर (p != शून्य) अणु
		स_रखो(p, 0, माप(dbdev_tab_t));
		p->dev_id = ~0;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(au1xxx_ddma_del_device);

/* Allocate a channel and वापस a non-zero descriptor अगर successful. */
u32 au1xxx_dbdma_chan_alloc(u32 srcid, u32 destid,
       व्योम (*callback)(पूर्णांक, व्योम *), व्योम *callparam)
अणु
	अचिन्हित दीर्घ	flags;
	u32		used, chan;
	u32		dcp;
	पूर्णांक		i;
	dbdev_tab_t	*stp, *dtp;
	chan_tab_t	*ctp;
	au1x_dma_chan_t *cp;

	/*
	 * We करो the initialization on the first channel allocation.
	 * We have to रुको because of the पूर्णांकerrupt handler initialization
	 * which can't be करोne successfully during board set up.
	 */
	अगर (!dbdma_initialized)
		वापस 0;

	stp = find_dbdev_id(srcid);
	अगर (stp == शून्य)
		वापस 0;
	dtp = find_dbdev_id(destid);
	अगर (dtp == शून्य)
		वापस 0;

	used = 0;

	/* Check to see अगर we can get both channels. */
	spin_lock_irqsave(&au1xxx_dbdma_spin_lock, flags);
	अगर (!(stp->dev_flags & DEV_FLAGS_INUSE) ||
	     (stp->dev_flags & DEV_FLAGS_ANYUSE)) अणु
		/* Got source */
		stp->dev_flags |= DEV_FLAGS_INUSE;
		अगर (!(dtp->dev_flags & DEV_FLAGS_INUSE) ||
		     (dtp->dev_flags & DEV_FLAGS_ANYUSE)) अणु
			/* Got destination */
			dtp->dev_flags |= DEV_FLAGS_INUSE;
		पूर्ण अन्यथा अणु
			/* Can't get dest.  Release src. */
			stp->dev_flags &= ~DEV_FLAGS_INUSE;
			used++;
		पूर्ण
	पूर्ण अन्यथा
		used++;
	spin_unlock_irqrestore(&au1xxx_dbdma_spin_lock, flags);

	अगर (used)
		वापस 0;

	/* Let's see अगर we can allocate a channel क्रम it. */
	ctp = शून्य;
	chan = 0;
	spin_lock_irqsave(&au1xxx_dbdma_spin_lock, flags);
	क्रम (i = 0; i < NUM_DBDMA_CHANS; i++)
		अगर (chan_tab_ptr[i] == शून्य) अणु
			/*
			 * If kदो_स्मृति fails, it is caught below same
			 * as a channel not available.
			 */
			ctp = kदो_स्मृति(माप(chan_tab_t), GFP_ATOMIC);
			chan_tab_ptr[i] = ctp;
			अवरोध;
		पूर्ण
	spin_unlock_irqrestore(&au1xxx_dbdma_spin_lock, flags);

	अगर (ctp != शून्य) अणु
		स_रखो(ctp, 0, माप(chan_tab_t));
		ctp->chan_index = chan = i;
		dcp = KSEG1ADDR(AU1550_DBDMA_PHYS_ADDR);
		dcp += (0x0100 * chan);
		ctp->chan_ptr = (au1x_dma_chan_t *)dcp;
		cp = (au1x_dma_chan_t *)dcp;
		ctp->chan_src = stp;
		ctp->chan_dest = dtp;
		ctp->chan_callback = callback;
		ctp->chan_callparam = callparam;

		/* Initialize channel configuration. */
		i = 0;
		अगर (stp->dev_पूर्णांकlevel)
			i |= DDMA_CFG_SED;
		अगर (stp->dev_पूर्णांकpolarity)
			i |= DDMA_CFG_SP;
		अगर (dtp->dev_पूर्णांकlevel)
			i |= DDMA_CFG_DED;
		अगर (dtp->dev_पूर्णांकpolarity)
			i |= DDMA_CFG_DP;
		अगर ((stp->dev_flags & DEV_FLAGS_SYNC) ||
			(dtp->dev_flags & DEV_FLAGS_SYNC))
				i |= DDMA_CFG_SYNC;
		cp->ddma_cfg = i;
		wmb(); /* drain ग_लिखोbuffer */

		/*
		 * Return a non-zero value that can be used to find the channel
		 * inक्रमmation in subsequent operations.
		 */
		वापस (u32)(&chan_tab_ptr[chan]);
	पूर्ण

	/* Release devices */
	stp->dev_flags &= ~DEV_FLAGS_INUSE;
	dtp->dev_flags &= ~DEV_FLAGS_INUSE;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(au1xxx_dbdma_chan_alloc);

/*
 * Set the device width अगर source or destination is a FIFO.
 * Should be 8, 16, or 32 bits.
 */
u32 au1xxx_dbdma_set_devwidth(u32 chanid, पूर्णांक bits)
अणु
	u32		rv;
	chan_tab_t	*ctp;
	dbdev_tab_t	*stp, *dtp;

	ctp = *((chan_tab_t **)chanid);
	stp = ctp->chan_src;
	dtp = ctp->chan_dest;
	rv = 0;

	अगर (stp->dev_flags & DEV_FLAGS_IN) अणु	/* Source in fअगरo */
		rv = stp->dev_devwidth;
		stp->dev_devwidth = bits;
	पूर्ण
	अगर (dtp->dev_flags & DEV_FLAGS_OUT) अणु	/* Destination out fअगरo */
		rv = dtp->dev_devwidth;
		dtp->dev_devwidth = bits;
	पूर्ण

	वापस rv;
पूर्ण
EXPORT_SYMBOL(au1xxx_dbdma_set_devwidth);

/* Allocate a descriptor ring, initializing as much as possible. */
u32 au1xxx_dbdma_ring_alloc(u32 chanid, पूर्णांक entries)
अणु
	पूर्णांक			i;
	u32			desc_base, srcid, destid;
	u32			cmd0, cmd1, src1, dest1;
	u32			src0, dest0;
	chan_tab_t		*ctp;
	dbdev_tab_t		*stp, *dtp;
	au1x_ddma_desc_t	*dp;

	/*
	 * I guess we could check this to be within the
	 * range of the table......
	 */
	ctp = *((chan_tab_t **)chanid);
	stp = ctp->chan_src;
	dtp = ctp->chan_dest;

	/*
	 * The descriptors must be 32-byte aligned.  There is a
	 * possibility the allocation will give us such an address,
	 * and अगर we try that first we are likely to not waste larger
	 * sद_असल of memory.
	 */
	desc_base = (u32)kदो_स्मृति_array(entries, माप(au1x_ddma_desc_t),
				       GFP_KERNEL|GFP_DMA);
	अगर (desc_base == 0)
		वापस 0;

	अगर (desc_base & 0x1f) अणु
		/*
		 * Lost....करो it again, allocate extra, and round
		 * the address base.
		 */
		kमुक्त((स्थिर व्योम *)desc_base);
		i = entries * माप(au1x_ddma_desc_t);
		i += (माप(au1x_ddma_desc_t) - 1);
		desc_base = (u32)kदो_स्मृति(i, GFP_KERNEL|GFP_DMA);
		अगर (desc_base == 0)
			वापस 0;

		ctp->cdb_membase = desc_base;
		desc_base = ALIGN_ADDR(desc_base, माप(au1x_ddma_desc_t));
	पूर्ण अन्यथा
		ctp->cdb_membase = desc_base;

	dp = (au1x_ddma_desc_t *)desc_base;

	/* Keep track of the base descriptor. */
	ctp->chan_desc_base = dp;

	/* Initialize the rings with as much inक्रमmation as we know. */
	srcid = stp->dev_id;
	destid = dtp->dev_id;

	cmd0 = cmd1 = src1 = dest1 = 0;
	src0 = dest0 = 0;

	cmd0 |= DSCR_CMD0_SID(srcid);
	cmd0 |= DSCR_CMD0_DID(destid);
	cmd0 |= DSCR_CMD0_IE | DSCR_CMD0_CV;
	cmd0 |= DSCR_CMD0_ST(DSCR_CMD0_ST_NOCHANGE);

	/* Is it mem to mem transfer? */
	अगर (((DSCR_CUSTOM2DEV_ID(srcid) == DSCR_CMD0_THROTTLE) ||
	     (DSCR_CUSTOM2DEV_ID(srcid) == DSCR_CMD0_ALWAYS)) &&
	    ((DSCR_CUSTOM2DEV_ID(destid) == DSCR_CMD0_THROTTLE) ||
	     (DSCR_CUSTOM2DEV_ID(destid) == DSCR_CMD0_ALWAYS)))
		cmd0 |= DSCR_CMD0_MEM;

	चयन (stp->dev_devwidth) अणु
	हाल 8:
		cmd0 |= DSCR_CMD0_SW(DSCR_CMD0_BYTE);
		अवरोध;
	हाल 16:
		cmd0 |= DSCR_CMD0_SW(DSCR_CMD0_HALFWORD);
		अवरोध;
	हाल 32:
	शेष:
		cmd0 |= DSCR_CMD0_SW(DSCR_CMD0_WORD);
		अवरोध;
	पूर्ण

	चयन (dtp->dev_devwidth) अणु
	हाल 8:
		cmd0 |= DSCR_CMD0_DW(DSCR_CMD0_BYTE);
		अवरोध;
	हाल 16:
		cmd0 |= DSCR_CMD0_DW(DSCR_CMD0_HALFWORD);
		अवरोध;
	हाल 32:
	शेष:
		cmd0 |= DSCR_CMD0_DW(DSCR_CMD0_WORD);
		अवरोध;
	पूर्ण

	/*
	 * If the device is marked as an in/out FIFO, ensure it is
	 * set non-coherent.
	 */
	अगर (stp->dev_flags & DEV_FLAGS_IN)
		cmd0 |= DSCR_CMD0_SN;		/* Source in FIFO */
	अगर (dtp->dev_flags & DEV_FLAGS_OUT)
		cmd0 |= DSCR_CMD0_DN;		/* Destination out FIFO */

	/*
	 * Set up source1.  For now, assume no stride and increment.
	 * A channel attribute update can change this later.
	 */
	चयन (stp->dev_tsize) अणु
	हाल 1:
		src1 |= DSCR_SRC1_STS(DSCR_xTS_SIZE1);
		अवरोध;
	हाल 2:
		src1 |= DSCR_SRC1_STS(DSCR_xTS_SIZE2);
		अवरोध;
	हाल 4:
		src1 |= DSCR_SRC1_STS(DSCR_xTS_SIZE4);
		अवरोध;
	हाल 8:
	शेष:
		src1 |= DSCR_SRC1_STS(DSCR_xTS_SIZE8);
		अवरोध;
	पूर्ण

	/* If source input is FIFO, set अटल address. */
	अगर (stp->dev_flags & DEV_FLAGS_IN) अणु
		अगर (stp->dev_flags & DEV_FLAGS_BURSTABLE)
			src1 |= DSCR_SRC1_SAM(DSCR_xAM_BURST);
		अन्यथा
			src1 |= DSCR_SRC1_SAM(DSCR_xAM_STATIC);
	पूर्ण

	अगर (stp->dev_physaddr)
		src0 = stp->dev_physaddr;

	/*
	 * Set up dest1.  For now, assume no stride and increment.
	 * A channel attribute update can change this later.
	 */
	चयन (dtp->dev_tsize) अणु
	हाल 1:
		dest1 |= DSCR_DEST1_DTS(DSCR_xTS_SIZE1);
		अवरोध;
	हाल 2:
		dest1 |= DSCR_DEST1_DTS(DSCR_xTS_SIZE2);
		अवरोध;
	हाल 4:
		dest1 |= DSCR_DEST1_DTS(DSCR_xTS_SIZE4);
		अवरोध;
	हाल 8:
	शेष:
		dest1 |= DSCR_DEST1_DTS(DSCR_xTS_SIZE8);
		अवरोध;
	पूर्ण

	/* If destination output is FIFO, set अटल address. */
	अगर (dtp->dev_flags & DEV_FLAGS_OUT) अणु
		अगर (dtp->dev_flags & DEV_FLAGS_BURSTABLE)
			dest1 |= DSCR_DEST1_DAM(DSCR_xAM_BURST);
		अन्यथा
			dest1 |= DSCR_DEST1_DAM(DSCR_xAM_STATIC);
	पूर्ण

	अगर (dtp->dev_physaddr)
		dest0 = dtp->dev_physaddr;

#अगर 0
		prपूर्णांकk(KERN_DEBUG "did:%x sid:%x cmd0:%x cmd1:%x source0:%x "
				  "source1:%x dest0:%x dest1:%x\n",
				  dtp->dev_id, stp->dev_id, cmd0, cmd1, src0,
				  src1, dest0, dest1);
#पूर्ण_अगर
	क्रम (i = 0; i < entries; i++) अणु
		dp->dscr_cmd0 = cmd0;
		dp->dscr_cmd1 = cmd1;
		dp->dscr_source0 = src0;
		dp->dscr_source1 = src1;
		dp->dscr_dest0 = dest0;
		dp->dscr_dest1 = dest1;
		dp->dscr_stat = 0;
		dp->sw_context = 0;
		dp->sw_status = 0;
		dp->dscr_nxtptr = DSCR_NXTPTR(virt_to_phys(dp + 1));
		dp++;
	पूर्ण

	/* Make last descrptor poपूर्णांक to the first. */
	dp--;
	dp->dscr_nxtptr = DSCR_NXTPTR(virt_to_phys(ctp->chan_desc_base));
	ctp->get_ptr = ctp->put_ptr = ctp->cur_ptr = ctp->chan_desc_base;

	वापस (u32)ctp->chan_desc_base;
पूर्ण
EXPORT_SYMBOL(au1xxx_dbdma_ring_alloc);

/*
 * Put a source buffer पूर्णांकo the DMA ring.
 * This updates the source poपूर्णांकer and byte count.  Normally used
 * क्रम memory to fअगरo transfers.
 */
u32 au1xxx_dbdma_put_source(u32 chanid, dma_addr_t buf, पूर्णांक nbytes, u32 flags)
अणु
	chan_tab_t		*ctp;
	au1x_ddma_desc_t	*dp;

	/*
	 * I guess we could check this to be within the
	 * range of the table......
	 */
	ctp = *(chan_tab_t **)chanid;

	/*
	 * We should have multiple callers क्रम a particular channel,
	 * an पूर्णांकerrupt करोesn't affect this poपूर्णांकer nor the descriptor,
	 * so no locking should be needed.
	 */
	dp = ctp->put_ptr;

	/*
	 * If the descriptor is valid, we are way ahead of the DMA
	 * engine, so just वापस an error condition.
	 */
	अगर (dp->dscr_cmd0 & DSCR_CMD0_V)
		वापस 0;

	/* Load up buffer address and byte count. */
	dp->dscr_source0 = buf & ~0UL;
	dp->dscr_cmd1 = nbytes;
	/* Check flags */
	अगर (flags & DDMA_FLAGS_IE)
		dp->dscr_cmd0 |= DSCR_CMD0_IE;
	अगर (flags & DDMA_FLAGS_NOIE)
		dp->dscr_cmd0 &= ~DSCR_CMD0_IE;

	/*
	 * There is an errata on the Au1200/Au1550 parts that could result
	 * in "stale" data being DMA'ed. It has to करो with the snoop logic on
	 * the cache eviction buffer.  DMA_NONCOHERENT is on by शेष क्रम
	 * these parts. If it is fixed in the future, these dma_cache_inv will
	 * just be nothing more than empty macros. See पन.स.
	 */
	dma_cache_wback_inv((अचिन्हित दीर्घ)buf, nbytes);
	dp->dscr_cmd0 |= DSCR_CMD0_V;	/* Let it rip */
	wmb(); /* drain ग_लिखोbuffer */
	dma_cache_wback_inv((अचिन्हित दीर्घ)dp, माप(*dp));
	ctp->chan_ptr->ddma_dbell = 0;

	/* Get next descriptor poपूर्णांकer. */
	ctp->put_ptr = phys_to_virt(DSCR_GET_NXTPTR(dp->dscr_nxtptr));

	/* Return something non-zero. */
	वापस nbytes;
पूर्ण
EXPORT_SYMBOL(au1xxx_dbdma_put_source);

/* Put a destination buffer पूर्णांकo the DMA ring.
 * This updates the destination poपूर्णांकer and byte count.  Normally used
 * to place an empty buffer पूर्णांकo the ring क्रम fअगरo to memory transfers.
 */
u32 au1xxx_dbdma_put_dest(u32 chanid, dma_addr_t buf, पूर्णांक nbytes, u32 flags)
अणु
	chan_tab_t		*ctp;
	au1x_ddma_desc_t	*dp;

	/* I guess we could check this to be within the
	 * range of the table......
	 */
	ctp = *((chan_tab_t **)chanid);

	/* We should have multiple callers क्रम a particular channel,
	 * an पूर्णांकerrupt करोesn't affect this poपूर्णांकer nor the descriptor,
	 * so no locking should be needed.
	 */
	dp = ctp->put_ptr;

	/* If the descriptor is valid, we are way ahead of the DMA
	 * engine, so just वापस an error condition.
	 */
	अगर (dp->dscr_cmd0 & DSCR_CMD0_V)
		वापस 0;

	/* Load up buffer address and byte count */

	/* Check flags  */
	अगर (flags & DDMA_FLAGS_IE)
		dp->dscr_cmd0 |= DSCR_CMD0_IE;
	अगर (flags & DDMA_FLAGS_NOIE)
		dp->dscr_cmd0 &= ~DSCR_CMD0_IE;

	dp->dscr_dest0 = buf & ~0UL;
	dp->dscr_cmd1 = nbytes;
#अगर 0
	prपूर्णांकk(KERN_DEBUG "cmd0:%x cmd1:%x source0:%x source1:%x dest0:%x dest1:%x\n",
			  dp->dscr_cmd0, dp->dscr_cmd1, dp->dscr_source0,
			  dp->dscr_source1, dp->dscr_dest0, dp->dscr_dest1);
#पूर्ण_अगर
	/*
	 * There is an errata on the Au1200/Au1550 parts that could result in
	 * "stale" data being DMA'ed. It has to करो with the snoop logic on the
	 * cache eviction buffer.  DMA_NONCOHERENT is on by शेष क्रम these
	 * parts. If it is fixed in the future, these dma_cache_inv will just
	 * be nothing more than empty macros. See पन.स.
	 */
	dma_cache_inv((अचिन्हित दीर्घ)buf, nbytes);
	dp->dscr_cmd0 |= DSCR_CMD0_V;	/* Let it rip */
	wmb(); /* drain ग_लिखोbuffer */
	dma_cache_wback_inv((अचिन्हित दीर्घ)dp, माप(*dp));
	ctp->chan_ptr->ddma_dbell = 0;

	/* Get next descriptor poपूर्णांकer. */
	ctp->put_ptr = phys_to_virt(DSCR_GET_NXTPTR(dp->dscr_nxtptr));

	/* Return something non-zero. */
	वापस nbytes;
पूर्ण
EXPORT_SYMBOL(au1xxx_dbdma_put_dest);

/*
 * Get a destination buffer पूर्णांकo the DMA ring.
 * Normally used to get a full buffer from the ring during fअगरo
 * to memory transfers.  This करोes not set the valid bit, you will
 * have to put another destination buffer to keep the DMA going.
 */
u32 au1xxx_dbdma_get_dest(u32 chanid, व्योम **buf, पूर्णांक *nbytes)
अणु
	chan_tab_t		*ctp;
	au1x_ddma_desc_t	*dp;
	u32			rv;

	/*
	 * I guess we could check this to be within the
	 * range of the table......
	 */
	ctp = *((chan_tab_t **)chanid);

	/*
	 * We should have multiple callers क्रम a particular channel,
	 * an पूर्णांकerrupt करोesn't affect this poपूर्णांकer nor the descriptor,
	 * so no locking should be needed.
	 */
	dp = ctp->get_ptr;

	/*
	 * If the descriptor is valid, we are way ahead of the DMA
	 * engine, so just वापस an error condition.
	 */
	अगर (dp->dscr_cmd0 & DSCR_CMD0_V)
		वापस 0;

	/* Return buffer address and byte count. */
	*buf = (व्योम *)(phys_to_virt(dp->dscr_dest0));
	*nbytes = dp->dscr_cmd1;
	rv = dp->dscr_stat;

	/* Get next descriptor poपूर्णांकer. */
	ctp->get_ptr = phys_to_virt(DSCR_GET_NXTPTR(dp->dscr_nxtptr));

	/* Return something non-zero. */
	वापस rv;
पूर्ण
EXPORT_SYMBOL_GPL(au1xxx_dbdma_get_dest);

व्योम au1xxx_dbdma_stop(u32 chanid)
अणु
	chan_tab_t	*ctp;
	au1x_dma_chan_t *cp;
	पूर्णांक halt_समयout = 0;

	ctp = *((chan_tab_t **)chanid);

	cp = ctp->chan_ptr;
	cp->ddma_cfg &= ~DDMA_CFG_EN;	/* Disable channel */
	wmb(); /* drain ग_लिखोbuffer */
	जबतक (!(cp->ddma_stat & DDMA_STAT_H)) अणु
		udelay(1);
		halt_समयout++;
		अगर (halt_समयout > 100) अणु
			prपूर्णांकk(KERN_WARNING "warning: DMA channel won't halt\n");
			अवरोध;
		पूर्ण
	पूर्ण
	/* clear current desc valid and करोorbell */
	cp->ddma_stat |= (DDMA_STAT_DB | DDMA_STAT_V);
	wmb(); /* drain ग_लिखोbuffer */
पूर्ण
EXPORT_SYMBOL(au1xxx_dbdma_stop);

/*
 * Start using the current descriptor poपूर्णांकer.  If the DBDMA encounters
 * a non-valid descriptor, it will stop.  In this हाल, we can just
 * जारी by adding a buffer to the list and starting again.
 */
व्योम au1xxx_dbdma_start(u32 chanid)
अणु
	chan_tab_t	*ctp;
	au1x_dma_chan_t *cp;

	ctp = *((chan_tab_t **)chanid);
	cp = ctp->chan_ptr;
	cp->ddma_desptr = virt_to_phys(ctp->cur_ptr);
	cp->ddma_cfg |= DDMA_CFG_EN;	/* Enable channel */
	wmb(); /* drain ग_लिखोbuffer */
	cp->ddma_dbell = 0;
	wmb(); /* drain ग_लिखोbuffer */
पूर्ण
EXPORT_SYMBOL(au1xxx_dbdma_start);

व्योम au1xxx_dbdma_reset(u32 chanid)
अणु
	chan_tab_t		*ctp;
	au1x_ddma_desc_t	*dp;

	au1xxx_dbdma_stop(chanid);

	ctp = *((chan_tab_t **)chanid);
	ctp->get_ptr = ctp->put_ptr = ctp->cur_ptr = ctp->chan_desc_base;

	/* Run through the descriptors and reset the valid indicator. */
	dp = ctp->chan_desc_base;

	करो अणु
		dp->dscr_cmd0 &= ~DSCR_CMD0_V;
		/*
		 * Reset our software status -- this is used to determine
		 * अगर a descriptor is in use by upper level software. Since
		 * posting can reset 'V' bit.
		 */
		dp->sw_status = 0;
		dp = phys_to_virt(DSCR_GET_NXTPTR(dp->dscr_nxtptr));
	पूर्ण जबतक (dp != ctp->chan_desc_base);
पूर्ण
EXPORT_SYMBOL(au1xxx_dbdma_reset);

u32 au1xxx_get_dma_residue(u32 chanid)
अणु
	chan_tab_t	*ctp;
	au1x_dma_chan_t *cp;
	u32		rv;

	ctp = *((chan_tab_t **)chanid);
	cp = ctp->chan_ptr;

	/* This is only valid अगर the channel is stopped. */
	rv = cp->ddma_bytecnt;
	wmb(); /* drain ग_लिखोbuffer */

	वापस rv;
पूर्ण
EXPORT_SYMBOL_GPL(au1xxx_get_dma_residue);

व्योम au1xxx_dbdma_chan_मुक्त(u32 chanid)
अणु
	chan_tab_t	*ctp;
	dbdev_tab_t	*stp, *dtp;

	ctp = *((chan_tab_t **)chanid);
	stp = ctp->chan_src;
	dtp = ctp->chan_dest;

	au1xxx_dbdma_stop(chanid);

	kमुक्त((व्योम *)ctp->cdb_membase);

	stp->dev_flags &= ~DEV_FLAGS_INUSE;
	dtp->dev_flags &= ~DEV_FLAGS_INUSE;
	chan_tab_ptr[ctp->chan_index] = शून्य;

	kमुक्त(ctp);
पूर्ण
EXPORT_SYMBOL(au1xxx_dbdma_chan_मुक्त);

अटल irqवापस_t dbdma_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	u32 पूर्णांकstat;
	u32 chan_index;
	chan_tab_t		*ctp;
	au1x_ddma_desc_t	*dp;
	au1x_dma_chan_t *cp;

	पूर्णांकstat = dbdma_gptr->ddma_पूर्णांकstat;
	wmb(); /* drain ग_लिखोbuffer */
	chan_index = __ffs(पूर्णांकstat);

	ctp = chan_tab_ptr[chan_index];
	cp = ctp->chan_ptr;
	dp = ctp->cur_ptr;

	/* Reset पूर्णांकerrupt. */
	cp->ddma_irq = 0;
	wmb(); /* drain ग_लिखोbuffer */

	अगर (ctp->chan_callback)
		ctp->chan_callback(irq, ctp->chan_callparam);

	ctp->cur_ptr = phys_to_virt(DSCR_GET_NXTPTR(dp->dscr_nxtptr));
	वापस IRQ_RETVAL(1);
पूर्ण

व्योम au1xxx_dbdma_dump(u32 chanid)
अणु
	chan_tab_t	 *ctp;
	au1x_ddma_desc_t *dp;
	dbdev_tab_t	 *stp, *dtp;
	au1x_dma_chan_t	 *cp;
	u32 i		 = 0;

	ctp = *((chan_tab_t **)chanid);
	stp = ctp->chan_src;
	dtp = ctp->chan_dest;
	cp = ctp->chan_ptr;

	prपूर्णांकk(KERN_DEBUG "Chan %x, stp %x (dev %d)  dtp %x (dev %d)\n",
			  (u32)ctp, (u32)stp, stp - dbdev_tab, (u32)dtp,
			  dtp - dbdev_tab);
	prपूर्णांकk(KERN_DEBUG "desc base %x, get %x, put %x, cur %x\n",
			  (u32)(ctp->chan_desc_base), (u32)(ctp->get_ptr),
			  (u32)(ctp->put_ptr), (u32)(ctp->cur_ptr));

	prपूर्णांकk(KERN_DEBUG "dbdma chan %x\n", (u32)cp);
	prपूर्णांकk(KERN_DEBUG "cfg %08x, desptr %08x, statptr %08x\n",
			  cp->ddma_cfg, cp->ddma_desptr, cp->ddma_statptr);
	prपूर्णांकk(KERN_DEBUG "dbell %08x, irq %08x, stat %08x, bytecnt %08x\n",
			  cp->ddma_dbell, cp->ddma_irq, cp->ddma_stat,
			  cp->ddma_bytecnt);

	/* Run through the descriptors */
	dp = ctp->chan_desc_base;

	करो अणु
		prपूर्णांकk(KERN_DEBUG "Dp[%d]= %08x, cmd0 %08x, cmd1 %08x\n",
				  i++, (u32)dp, dp->dscr_cmd0, dp->dscr_cmd1);
		prपूर्णांकk(KERN_DEBUG "src0 %08x, src1 %08x, dest0 %08x, dest1 %08x\n",
				  dp->dscr_source0, dp->dscr_source1,
				  dp->dscr_dest0, dp->dscr_dest1);
		prपूर्णांकk(KERN_DEBUG "stat %08x, nxtptr %08x\n",
				  dp->dscr_stat, dp->dscr_nxtptr);
		dp = phys_to_virt(DSCR_GET_NXTPTR(dp->dscr_nxtptr));
	पूर्ण जबतक (dp != ctp->chan_desc_base);
पूर्ण

/* Put a descriptor पूर्णांकo the DMA ring.
 * This updates the source/destination poपूर्णांकers and byte count.
 */
u32 au1xxx_dbdma_put_dscr(u32 chanid, au1x_ddma_desc_t *dscr)
अणु
	chan_tab_t *ctp;
	au1x_ddma_desc_t *dp;
	u32 nbytes = 0;

	/*
	 * I guess we could check this to be within the
	 * range of the table......
	 */
	ctp = *((chan_tab_t **)chanid);

	/*
	 * We should have multiple callers क्रम a particular channel,
	 * an पूर्णांकerrupt करोesn't affect this poपूर्णांकer nor the descriptor,
	 * so no locking should be needed.
	 */
	dp = ctp->put_ptr;

	/*
	 * If the descriptor is valid, we are way ahead of the DMA
	 * engine, so just वापस an error condition.
	 */
	अगर (dp->dscr_cmd0 & DSCR_CMD0_V)
		वापस 0;

	/* Load up buffer addresses and byte count. */
	dp->dscr_dest0 = dscr->dscr_dest0;
	dp->dscr_source0 = dscr->dscr_source0;
	dp->dscr_dest1 = dscr->dscr_dest1;
	dp->dscr_source1 = dscr->dscr_source1;
	dp->dscr_cmd1 = dscr->dscr_cmd1;
	nbytes = dscr->dscr_cmd1;
	/* Allow the caller to specअगरy अगर an पूर्णांकerrupt is generated */
	dp->dscr_cmd0 &= ~DSCR_CMD0_IE;
	dp->dscr_cmd0 |= dscr->dscr_cmd0 | DSCR_CMD0_V;
	ctp->chan_ptr->ddma_dbell = 0;

	/* Get next descriptor poपूर्णांकer. */
	ctp->put_ptr = phys_to_virt(DSCR_GET_NXTPTR(dp->dscr_nxtptr));

	/* Return something non-zero. */
	वापस nbytes;
पूर्ण


अटल अचिन्हित दीर्घ alchemy_dbdma_pm_data[NUM_DBDMA_CHANS + 1][6];

अटल पूर्णांक alchemy_dbdma_suspend(व्योम)
अणु
	पूर्णांक i;
	व्योम __iomem *addr;

	addr = (व्योम __iomem *)KSEG1ADDR(AU1550_DBDMA_CONF_PHYS_ADDR);
	alchemy_dbdma_pm_data[0][0] = __raw_पढ़ोl(addr + 0x00);
	alchemy_dbdma_pm_data[0][1] = __raw_पढ़ोl(addr + 0x04);
	alchemy_dbdma_pm_data[0][2] = __raw_पढ़ोl(addr + 0x08);
	alchemy_dbdma_pm_data[0][3] = __raw_पढ़ोl(addr + 0x0c);

	/* save channel configurations */
	addr = (व्योम __iomem *)KSEG1ADDR(AU1550_DBDMA_PHYS_ADDR);
	क्रम (i = 1; i <= NUM_DBDMA_CHANS; i++) अणु
		alchemy_dbdma_pm_data[i][0] = __raw_पढ़ोl(addr + 0x00);
		alchemy_dbdma_pm_data[i][1] = __raw_पढ़ोl(addr + 0x04);
		alchemy_dbdma_pm_data[i][2] = __raw_पढ़ोl(addr + 0x08);
		alchemy_dbdma_pm_data[i][3] = __raw_पढ़ोl(addr + 0x0c);
		alchemy_dbdma_pm_data[i][4] = __raw_पढ़ोl(addr + 0x10);
		alchemy_dbdma_pm_data[i][5] = __raw_पढ़ोl(addr + 0x14);

		/* halt channel */
		__raw_ग_लिखोl(alchemy_dbdma_pm_data[i][0] & ~1, addr + 0x00);
		wmb();
		जबतक (!(__raw_पढ़ोl(addr + 0x14) & 1))
			wmb();

		addr += 0x100;	/* next channel base */
	पूर्ण
	/* disable channel पूर्णांकerrupts */
	addr = (व्योम __iomem *)KSEG1ADDR(AU1550_DBDMA_CONF_PHYS_ADDR);
	__raw_ग_लिखोl(0, addr + 0x0c);
	wmb();

	वापस 0;
पूर्ण

अटल व्योम alchemy_dbdma_resume(व्योम)
अणु
	पूर्णांक i;
	व्योम __iomem *addr;

	addr = (व्योम __iomem *)KSEG1ADDR(AU1550_DBDMA_CONF_PHYS_ADDR);
	__raw_ग_लिखोl(alchemy_dbdma_pm_data[0][0], addr + 0x00);
	__raw_ग_लिखोl(alchemy_dbdma_pm_data[0][1], addr + 0x04);
	__raw_ग_लिखोl(alchemy_dbdma_pm_data[0][2], addr + 0x08);
	__raw_ग_लिखोl(alchemy_dbdma_pm_data[0][3], addr + 0x0c);

	/* restore channel configurations */
	addr = (व्योम __iomem *)KSEG1ADDR(AU1550_DBDMA_PHYS_ADDR);
	क्रम (i = 1; i <= NUM_DBDMA_CHANS; i++) अणु
		__raw_ग_लिखोl(alchemy_dbdma_pm_data[i][0], addr + 0x00);
		__raw_ग_लिखोl(alchemy_dbdma_pm_data[i][1], addr + 0x04);
		__raw_ग_लिखोl(alchemy_dbdma_pm_data[i][2], addr + 0x08);
		__raw_ग_लिखोl(alchemy_dbdma_pm_data[i][3], addr + 0x0c);
		__raw_ग_लिखोl(alchemy_dbdma_pm_data[i][4], addr + 0x10);
		__raw_ग_लिखोl(alchemy_dbdma_pm_data[i][5], addr + 0x14);
		wmb();
		addr += 0x100;	/* next channel base */
	पूर्ण
पूर्ण

अटल काष्ठा syscore_ops alchemy_dbdma_syscore_ops = अणु
	.suspend	= alchemy_dbdma_suspend,
	.resume		= alchemy_dbdma_resume,
पूर्ण;

अटल पूर्णांक __init dbdma_setup(अचिन्हित पूर्णांक irq, dbdev_tab_t *idtable)
अणु
	पूर्णांक ret;

	dbdev_tab = kसुस्मृति(DBDEV_TAB_SIZE, माप(dbdev_tab_t), GFP_KERNEL);
	अगर (!dbdev_tab)
		वापस -ENOMEM;

	स_नकल(dbdev_tab, idtable, 32 * माप(dbdev_tab_t));
	क्रम (ret = 32; ret < DBDEV_TAB_SIZE; ret++)
		dbdev_tab[ret].dev_id = ~0;

	dbdma_gptr->ddma_config = 0;
	dbdma_gptr->ddma_throttle = 0;
	dbdma_gptr->ddma_पूर्णांकen = 0xffff;
	wmb(); /* drain ग_लिखोbuffer */

	ret = request_irq(irq, dbdma_पूर्णांकerrupt, 0, "dbdma", (व्योम *)dbdma_gptr);
	अगर (ret)
		prपूर्णांकk(KERN_ERR "Cannot grab DBDMA interrupt!\n");
	अन्यथा अणु
		dbdma_initialized = 1;
		रेजिस्टर_syscore_ops(&alchemy_dbdma_syscore_ops);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक __init alchemy_dbdma_init(व्योम)
अणु
	चयन (alchemy_get_cputype()) अणु
	हाल ALCHEMY_CPU_AU1550:
		वापस dbdma_setup(AU1550_DDMA_INT, au1550_dbdev_tab);
	हाल ALCHEMY_CPU_AU1200:
		वापस dbdma_setup(AU1200_DDMA_INT, au1200_dbdev_tab);
	हाल ALCHEMY_CPU_AU1300:
		वापस dbdma_setup(AU1300_DDMA_INT, au1300_dbdev_tab);
	पूर्ण
	वापस 0;
पूर्ण
subsys_initcall(alchemy_dbdma_init);
