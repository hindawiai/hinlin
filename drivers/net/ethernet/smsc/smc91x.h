<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*------------------------------------------------------------------------
 . smc91x.h - macros क्रम SMSC's 91C9x/91C1xx single-chip Ethernet device.
 .
 . Copyright (C) 1996 by Erik Stahlman
 . Copyright (C) 2001 Standard Microप्रणालीs Corporation
 .	Developed by Simple Network Magic Corporation
 . Copyright (C) 2003 Monta Vista Software, Inc.
 .	Unअगरied SMC91x driver by Nicolas Pitre
 .
 .
 . Inक्रमmation contained in this file was obtained from the LAN91C111
 . manual from SMC.  To get a copy, अगर you really want one, you can find
 . inक्रमmation under www.smsc.com.
 .
 . Authors
 .	Erik Stahlman		<erik@vt.edu>
 .	Daris A Nevil		<dnevil@snmc.com>
 .	Nicolas Pitre 		<nico@fluxnic.net>
 .
 ---------------------------------------------------------------------------*/
#अगर_अघोषित _SMC91X_H_
#घोषणा _SMC91X_H_

#समावेश <linux/dmaengine.h>
#समावेश <linux/smc91x.h>

/*
 * Any 16-bit access is perक्रमmed with two 8-bit accesses अगर the hardware
 * can't करो it directly. Most रेजिस्टरs are 16-bit so those are mandatory.
 */
#घोषणा SMC_outw_b(x, a, r)						\
	करो अणु								\
		अचिन्हित पूर्णांक __val16 = (x);				\
		अचिन्हित पूर्णांक __reg = (r);				\
		SMC_outb(__val16, a, __reg);				\
		SMC_outb(__val16 >> 8, a, __reg + (1 << SMC_IO_SHIFT));	\
	पूर्ण जबतक (0)

#घोषणा SMC_inw_b(a, r)							\
	(अणु								\
		अचिन्हित पूर्णांक __val16;					\
		अचिन्हित पूर्णांक __reg = r;					\
		__val16  = SMC_inb(a, __reg);				\
		__val16 |= SMC_inb(a, __reg + (1 << SMC_IO_SHIFT)) << 8; \
		__val16;						\
	पूर्ण)

/*
 * Define your architecture specअगरic bus configuration parameters here.
 */

#अगर defined(CONFIG_ARM)

#समावेश <यंत्र/mach-types.h>

/* Now the bus width is specअगरied in the platक्रमm data
 * pretend here to support all I/O access types
 */
#घोषणा SMC_CAN_USE_8BIT	1
#घोषणा SMC_CAN_USE_16BIT	1
#घोषणा SMC_CAN_USE_32BIT	1
#घोषणा SMC_NOWAIT		1

#घोषणा SMC_IO_SHIFT		(lp->io_shअगरt)

#घोषणा SMC_inb(a, r)		पढ़ोb((a) + (r))
#घोषणा SMC_inw(a, r)							\
	(अणु								\
		अचिन्हित पूर्णांक __smc_r = r;				\
		SMC_16BIT(lp) ? पढ़ोw((a) + __smc_r) :			\
		SMC_8BIT(lp) ? SMC_inw_b(a, __smc_r) :			\
		(अणु BUG(); 0; पूर्ण);					\
	पूर्ण)

#घोषणा SMC_inl(a, r)		पढ़ोl((a) + (r))
#घोषणा SMC_outb(v, a, r)	ग_लिखोb(v, (a) + (r))
#घोषणा SMC_outw(lp, v, a, r)						\
	करो अणु								\
		अचिन्हित पूर्णांक __v = v, __smc_r = r;			\
		अगर (SMC_16BIT(lp))					\
			__SMC_outw(lp, __v, a, __smc_r);		\
		अन्यथा अगर (SMC_8BIT(lp))					\
			SMC_outw_b(__v, a, __smc_r);			\
		अन्यथा							\
			BUG();						\
	पूर्ण जबतक (0)

#घोषणा SMC_outl(v, a, r)	ग_लिखोl(v, (a) + (r))
#घोषणा SMC_insb(a, r, p, l)	पढ़ोsb((a) + (r), p, l)
#घोषणा SMC_outsb(a, r, p, l)	ग_लिखोsb((a) + (r), p, l)
#घोषणा SMC_insw(a, r, p, l)	पढ़ोsw((a) + (r), p, l)
#घोषणा SMC_outsw(a, r, p, l)	ग_लिखोsw((a) + (r), p, l)
#घोषणा SMC_insl(a, r, p, l)	पढ़ोsl((a) + (r), p, l)
#घोषणा SMC_outsl(a, r, p, l)	ग_लिखोsl((a) + (r), p, l)
#घोषणा SMC_IRQ_FLAGS		(-1)	/* from resource */

/* We actually can't ग_लिखो halfwords properly अगर not word aligned */
अटल अंतरभूत व्योम _SMC_outw_align4(u16 val, व्योम __iomem *ioaddr, पूर्णांक reg,
				    bool use_align4_workaround)
अणु
	अगर (use_align4_workaround) अणु
		अचिन्हित पूर्णांक v = val << 16;
		v |= पढ़ोl(ioaddr + (reg & ~2)) & 0xffff;
		ग_लिखोl(v, ioaddr + (reg & ~2));
	पूर्ण अन्यथा अणु
		ग_लिखोw(val, ioaddr + reg);
	पूर्ण
पूर्ण

#घोषणा __SMC_outw(lp, v, a, r)						\
	_SMC_outw_align4((v), (a), (r),					\
			 IS_BUILTIN(CONFIG_ARCH_PXA) && ((r) & 2) &&	\
			 (lp)->cfg.pxa_u16_align4)


#या_अगर	defined(CONFIG_SH_SH4202_MICRODEV)

#घोषणा SMC_CAN_USE_8BIT	0
#घोषणा SMC_CAN_USE_16BIT	1
#घोषणा SMC_CAN_USE_32BIT	0

#घोषणा SMC_inb(a, r)		inb((a) + (r) - 0xa0000000)
#घोषणा SMC_inw(a, r)		inw((a) + (r) - 0xa0000000)
#घोषणा SMC_inl(a, r)		inl((a) + (r) - 0xa0000000)
#घोषणा SMC_outb(v, a, r)	outb(v, (a) + (r) - 0xa0000000)
#घोषणा SMC_outw(lp, v, a, r)	outw(v, (a) + (r) - 0xa0000000)
#घोषणा SMC_outl(v, a, r)	outl(v, (a) + (r) - 0xa0000000)
#घोषणा SMC_insl(a, r, p, l)	insl((a) + (r) - 0xa0000000, p, l)
#घोषणा SMC_outsl(a, r, p, l)	outsl((a) + (r) - 0xa0000000, p, l)
#घोषणा SMC_insw(a, r, p, l)	insw((a) + (r) - 0xa0000000, p, l)
#घोषणा SMC_outsw(a, r, p, l)	outsw((a) + (r) - 0xa0000000, p, l)

#घोषणा SMC_IRQ_FLAGS		(0)

#या_अगर defined(CONFIG_ATARI)

#घोषणा SMC_CAN_USE_8BIT        1
#घोषणा SMC_CAN_USE_16BIT       1
#घोषणा SMC_CAN_USE_32BIT       1
#घोषणा SMC_NOWAIT              1

#घोषणा SMC_inb(a, r)           पढ़ोb((a) + (r))
#घोषणा SMC_inw(a, r)           पढ़ोw((a) + (r))
#घोषणा SMC_inl(a, r)           पढ़ोl((a) + (r))
#घोषणा SMC_outb(v, a, r)       ग_लिखोb(v, (a) + (r))
#घोषणा SMC_outw(lp, v, a, r)   ग_लिखोw(v, (a) + (r))
#घोषणा SMC_outl(v, a, r)       ग_लिखोl(v, (a) + (r))
#घोषणा SMC_insw(a, r, p, l)    पढ़ोsw((a) + (r), p, l)
#घोषणा SMC_outsw(a, r, p, l)   ग_लिखोsw((a) + (r), p, l)
#घोषणा SMC_insl(a, r, p, l)    पढ़ोsl((a) + (r), p, l)
#घोषणा SMC_outsl(a, r, p, l)   ग_लिखोsl((a) + (r), p, l)

#घोषणा RPC_LSA_DEFAULT         RPC_LED_100_10
#घोषणा RPC_LSB_DEFAULT         RPC_LED_TX_RX

#या_अगर defined(CONFIG_COLDFIRE)

#घोषणा SMC_CAN_USE_8BIT	0
#घोषणा SMC_CAN_USE_16BIT	1
#घोषणा SMC_CAN_USE_32BIT	0
#घोषणा SMC_NOWAIT		1

अटल अंतरभूत व्योम mcf_insw(व्योम *a, अचिन्हित अक्षर *p, पूर्णांक l)
अणु
	u16 *wp = (u16 *) p;
	जबतक (l-- > 0)
		*wp++ = पढ़ोw(a);
पूर्ण

अटल अंतरभूत व्योम mcf_outsw(व्योम *a, अचिन्हित अक्षर *p, पूर्णांक l)
अणु
	u16 *wp = (u16 *) p;
	जबतक (l-- > 0)
		ग_लिखोw(*wp++, a);
पूर्ण

#घोषणा SMC_inw(a, r)		_swapw(पढ़ोw((a) + (r)))
#घोषणा SMC_outw(lp, v, a, r)	ग_लिखोw(_swapw(v), (a) + (r))
#घोषणा SMC_insw(a, r, p, l)	mcf_insw(a + r, p, l)
#घोषणा SMC_outsw(a, r, p, l)	mcf_outsw(a + r, p, l)

#घोषणा SMC_IRQ_FLAGS		0

#या_अगर defined(CONFIG_H8300)
#घोषणा SMC_CAN_USE_8BIT	1
#घोषणा SMC_CAN_USE_16BIT	0
#घोषणा SMC_CAN_USE_32BIT	0
#घोषणा SMC_NOWAIT		0

#घोषणा SMC_inb(a, r)		ioपढ़ो8((a) + (r))
#घोषणा SMC_outb(v, a, r)	ioग_लिखो8(v, (a) + (r))
#घोषणा SMC_insb(a, r, p, l)	ioपढ़ो8_rep((a) + (r), p, l)
#घोषणा SMC_outsb(a, r, p, l)	ioग_लिखो8_rep((a) + (r), p, l)

#अन्यथा

/*
 * Default configuration
 */

#घोषणा SMC_CAN_USE_8BIT	1
#घोषणा SMC_CAN_USE_16BIT	1
#घोषणा SMC_CAN_USE_32BIT	1
#घोषणा SMC_NOWAIT		1

#घोषणा SMC_IO_SHIFT		(lp->io_shअगरt)

#घोषणा SMC_inb(a, r)		ioपढ़ो8((a) + (r))
#घोषणा SMC_inw(a, r)		ioपढ़ो16((a) + (r))
#घोषणा SMC_inl(a, r)		ioपढ़ो32((a) + (r))
#घोषणा SMC_outb(v, a, r)	ioग_लिखो8(v, (a) + (r))
#घोषणा SMC_outw(lp, v, a, r)	ioग_लिखो16(v, (a) + (r))
#घोषणा SMC_outl(v, a, r)	ioग_लिखो32(v, (a) + (r))
#घोषणा SMC_insw(a, r, p, l)	ioपढ़ो16_rep((a) + (r), p, l)
#घोषणा SMC_outsw(a, r, p, l)	ioग_लिखो16_rep((a) + (r), p, l)
#घोषणा SMC_insl(a, r, p, l)	ioपढ़ो32_rep((a) + (r), p, l)
#घोषणा SMC_outsl(a, r, p, l)	ioग_लिखो32_rep((a) + (r), p, l)

#घोषणा RPC_LSA_DEFAULT		RPC_LED_100_10
#घोषणा RPC_LSB_DEFAULT		RPC_LED_TX_RX

#पूर्ण_अगर


/* store this inक्रमmation क्रम the driver.. */
काष्ठा smc_local अणु
	/*
	 * If I have to रुको until memory is available to send a
	 * packet, I will store the skbuff here, until I get the
	 * desired memory.  Then, I'll send it out and मुक्त it.
	 */
	काष्ठा sk_buff *pending_tx_skb;
	काष्ठा tasklet_काष्ठा tx_task;

	काष्ठा gpio_desc *घातer_gpio;
	काष्ठा gpio_desc *reset_gpio;

	/* version/revision of the SMC91x chip */
	पूर्णांक	version;

	/* Contains the current active transmission mode */
	पूर्णांक	tcr_cur_mode;

	/* Contains the current active receive mode */
	पूर्णांक	rcr_cur_mode;

	/* Contains the current active receive/phy mode */
	पूर्णांक	rpc_cur_mode;
	पूर्णांक	ctl_rfduplx;
	पूर्णांक	ctl_rspeed;

	u32	msg_enable;
	u32	phy_type;
	काष्ठा mii_अगर_info mii;

	/* work queue */
	काष्ठा work_काष्ठा phy_configure;
	काष्ठा net_device *dev;
	पूर्णांक	work_pending;

	spinlock_t lock;

#अगर_घोषित CONFIG_ARCH_PXA
	/* DMA needs the physical address of the chip */
	u_दीर्घ physaddr;
	काष्ठा device *device;
#पूर्ण_अगर
	काष्ठा dma_chan *dma_chan;
	व्योम __iomem *base;
	व्योम __iomem *datacs;

	/* the low address lines on some platक्रमms aren't connected... */
	पूर्णांक	io_shअगरt;
	/* on some platक्रमms a u16 ग_लिखो must be 4-bytes aligned */
	bool	half_word_align4;

	काष्ठा smc91x_platdata cfg;
पूर्ण;

#घोषणा SMC_8BIT(p)	((p)->cfg.flags & SMC91X_USE_8BIT)
#घोषणा SMC_16BIT(p)	((p)->cfg.flags & SMC91X_USE_16BIT)
#घोषणा SMC_32BIT(p)	((p)->cfg.flags & SMC91X_USE_32BIT)

#अगर_घोषित CONFIG_ARCH_PXA
/*
 * Let's use the DMA engine on the XScale PXA2xx क्रम RX packets. This is
 * always happening in irq context so no need to worry about races.  TX is
 * dअगरferent and probably not worth it क्रम that reason, and not as critical
 * as RX which can overrun memory and lose packets.
 */
#समावेश <linux/dma-mapping.h>

#अगर_घोषित SMC_insl
#अघोषित SMC_insl
#घोषणा SMC_insl(a, r, p, l) \
	smc_pxa_dma_insl(a, lp, r, dev->dma, p, l)
अटल अंतरभूत व्योम
smc_pxa_dma_inpump(काष्ठा smc_local *lp, u_अक्षर *buf, पूर्णांक len)
अणु
	dma_addr_t dmabuf;
	काष्ठा dma_async_tx_descriptor *tx;
	dma_cookie_t cookie;
	क्रमागत dma_status status;
	काष्ठा dma_tx_state state;

	dmabuf = dma_map_single(lp->device, buf, len, DMA_FROM_DEVICE);
	tx = dmaengine_prep_slave_single(lp->dma_chan, dmabuf, len,
					 DMA_DEV_TO_MEM, 0);
	अगर (tx) अणु
		cookie = dmaengine_submit(tx);
		dma_async_issue_pending(lp->dma_chan);
		करो अणु
			status = dmaengine_tx_status(lp->dma_chan, cookie,
						     &state);
			cpu_relax();
		पूर्ण जबतक (status != DMA_COMPLETE && status != DMA_ERROR &&
			 state.residue);
		dmaengine_terminate_all(lp->dma_chan);
	पूर्ण
	dma_unmap_single(lp->device, dmabuf, len, DMA_FROM_DEVICE);
पूर्ण

अटल अंतरभूत व्योम
smc_pxa_dma_insl(व्योम __iomem *ioaddr, काष्ठा smc_local *lp, पूर्णांक reg, पूर्णांक dma,
		 u_अक्षर *buf, पूर्णांक len)
अणु
	काष्ठा dma_slave_config	config;
	पूर्णांक ret;

	/* fallback अगर no DMA available */
	अगर (!lp->dma_chan) अणु
		पढ़ोsl(ioaddr + reg, buf, len);
		वापस;
	पूर्ण

	/* 64 bit alignment is required क्रम memory to memory DMA */
	अगर ((दीर्घ)buf & 4) अणु
		*((u32 *)buf) = SMC_inl(ioaddr, reg);
		buf += 4;
		len--;
	पूर्ण

	स_रखो(&config, 0, माप(config));
	config.src_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
	config.dst_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
	config.src_addr = lp->physaddr + reg;
	config.dst_addr = lp->physaddr + reg;
	config.src_maxburst = 32;
	config.dst_maxburst = 32;
	ret = dmaengine_slave_config(lp->dma_chan, &config);
	अगर (ret) अणु
		dev_err(lp->device, "dma channel configuration failed: %d\n",
			ret);
		वापस;
	पूर्ण

	len *= 4;
	smc_pxa_dma_inpump(lp, buf, len);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित SMC_insw
#अघोषित SMC_insw
#घोषणा SMC_insw(a, r, p, l) \
	smc_pxa_dma_insw(a, lp, r, dev->dma, p, l)
अटल अंतरभूत व्योम
smc_pxa_dma_insw(व्योम __iomem *ioaddr, काष्ठा smc_local *lp, पूर्णांक reg, पूर्णांक dma,
		 u_अक्षर *buf, पूर्णांक len)
अणु
	काष्ठा dma_slave_config	config;
	पूर्णांक ret;

	/* fallback अगर no DMA available */
	अगर (!lp->dma_chan) अणु
		पढ़ोsw(ioaddr + reg, buf, len);
		वापस;
	पूर्ण

	/* 64 bit alignment is required क्रम memory to memory DMA */
	जबतक ((दीर्घ)buf & 6) अणु
		*((u16 *)buf) = SMC_inw(ioaddr, reg);
		buf += 2;
		len--;
	पूर्ण

	स_रखो(&config, 0, माप(config));
	config.src_addr_width = DMA_SLAVE_BUSWIDTH_2_BYTES;
	config.dst_addr_width = DMA_SLAVE_BUSWIDTH_2_BYTES;
	config.src_addr = lp->physaddr + reg;
	config.dst_addr = lp->physaddr + reg;
	config.src_maxburst = 32;
	config.dst_maxburst = 32;
	ret = dmaengine_slave_config(lp->dma_chan, &config);
	अगर (ret) अणु
		dev_err(lp->device, "dma channel configuration failed: %d\n",
			ret);
		वापस;
	पूर्ण

	len *= 2;
	smc_pxa_dma_inpump(lp, buf, len);
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर  /* CONFIG_ARCH_PXA */


/*
 * Everything a particular hardware setup needs should have been defined
 * at this poपूर्णांक.  Add stubs क्रम the undefined हालs, मुख्यly to aव्योम
 * compilation warnings since they'll be optimized away, or to prevent buggy
 * use of them.
 */

#अगर ! SMC_CAN_USE_32BIT
#घोषणा SMC_inl(ioaddr, reg)		(अणु BUG(); 0; पूर्ण)
#घोषणा SMC_outl(x, ioaddr, reg)	BUG()
#घोषणा SMC_insl(a, r, p, l)		BUG()
#घोषणा SMC_outsl(a, r, p, l)		BUG()
#पूर्ण_अगर

#अगर !defined(SMC_insl) || !defined(SMC_outsl)
#घोषणा SMC_insl(a, r, p, l)		BUG()
#घोषणा SMC_outsl(a, r, p, l)		BUG()
#पूर्ण_अगर

#अगर ! SMC_CAN_USE_16BIT

#घोषणा SMC_outw(lp, x, ioaddr, reg)	SMC_outw_b(x, ioaddr, reg)
#घोषणा SMC_inw(ioaddr, reg)		SMC_inw_b(ioaddr, reg)
#घोषणा SMC_insw(a, r, p, l)		BUG()
#घोषणा SMC_outsw(a, r, p, l)		BUG()

#पूर्ण_अगर

#अगर !defined(SMC_insw) || !defined(SMC_outsw)
#घोषणा SMC_insw(a, r, p, l)		BUG()
#घोषणा SMC_outsw(a, r, p, l)		BUG()
#पूर्ण_अगर

#अगर ! SMC_CAN_USE_8BIT
#अघोषित SMC_inb
#घोषणा SMC_inb(ioaddr, reg)		(अणु BUG(); 0; पूर्ण)
#अघोषित SMC_outb
#घोषणा SMC_outb(x, ioaddr, reg)	BUG()
#घोषणा SMC_insb(a, r, p, l)		BUG()
#घोषणा SMC_outsb(a, r, p, l)		BUG()
#पूर्ण_अगर

#अगर !defined(SMC_insb) || !defined(SMC_outsb)
#घोषणा SMC_insb(a, r, p, l)		BUG()
#घोषणा SMC_outsb(a, r, p, l)		BUG()
#पूर्ण_अगर

#अगर_अघोषित SMC_CAN_USE_DATACS
#घोषणा SMC_CAN_USE_DATACS	0
#पूर्ण_अगर

#अगर_अघोषित SMC_IO_SHIFT
#घोषणा SMC_IO_SHIFT	0
#पूर्ण_अगर

#अगर_अघोषित	SMC_IRQ_FLAGS
#घोषणा	SMC_IRQ_FLAGS		IRQF_TRIGGER_RISING
#पूर्ण_अगर

#अगर_अघोषित SMC_INTERRUPT_PREAMBLE
#घोषणा SMC_INTERRUPT_PREAMBLE
#पूर्ण_अगर


/* Because of bank चयनing, the LAN91x uses only 16 I/O ports */
#घोषणा SMC_IO_EXTENT	(16 << SMC_IO_SHIFT)
#घोषणा SMC_DATA_EXTENT (4)

/*
 . Bank Select Register:
 .
 .		yyyy yyyy 0000 00xx
 .		xx 		= bank number
 .		yyyy yyyy	= 0x33, क्रम identअगरication purposes.
*/
#घोषणा BANK_SELECT		(14 << SMC_IO_SHIFT)


// Transmit Control Register
/* BANK 0  */
#घोषणा TCR_REG(lp) 	SMC_REG(lp, 0x0000, 0)
#घोषणा TCR_ENABLE	0x0001	// When 1 we can transmit
#घोषणा TCR_LOOP	0x0002	// Controls output pin LBK
#घोषणा TCR_FORCOL	0x0004	// When 1 will क्रमce a collision
#घोषणा TCR_PAD_EN	0x0080	// When 1 will pad tx frames < 64 bytes w/0
#घोषणा TCR_NOCRC	0x0100	// When 1 will not append CRC to tx frames
#घोषणा TCR_MON_CSN	0x0400	// When 1 tx monitors carrier
#घोषणा TCR_FDUPLX    	0x0800  // When 1 enables full duplex operation
#घोषणा TCR_STP_SQET	0x1000	// When 1 stops tx अगर Signal Quality Error
#घोषणा TCR_EPH_LOOP	0x2000	// When 1 enables EPH block loopback
#घोषणा TCR_SWFDUP	0x8000	// When 1 enables Switched Full Duplex mode

#घोषणा TCR_CLEAR	0	/* करो NOTHING */
/* the शेष settings क्रम the TCR रेजिस्टर : */
#घोषणा TCR_DEFAULT	(TCR_ENABLE | TCR_PAD_EN)


// EPH Status Register
/* BANK 0  */
#घोषणा EPH_STATUS_REG(lp)	SMC_REG(lp, 0x0002, 0)
#घोषणा ES_TX_SUC	0x0001	// Last TX was successful
#घोषणा ES_SNGL_COL	0x0002	// Single collision detected क्रम last tx
#घोषणा ES_MUL_COL	0x0004	// Multiple collisions detected क्रम last tx
#घोषणा ES_LTX_MULT	0x0008	// Last tx was a multicast
#घोषणा ES_16COL	0x0010	// 16 Collisions Reached
#घोषणा ES_SQET		0x0020	// Signal Quality Error Test
#घोषणा ES_LTXBRD	0x0040	// Last tx was a broadcast
#घोषणा ES_TXDEFR	0x0080	// Transmit Deferred
#घोषणा ES_LATCOL	0x0200	// Late collision detected on last tx
#घोषणा ES_LOSTCARR	0x0400	// Lost Carrier Sense
#घोषणा ES_EXC_DEF	0x0800	// Excessive Deferral
#घोषणा ES_CTR_ROL	0x1000	// Counter Roll Over indication
#घोषणा ES_LINK_OK	0x4000	// Driven by inverted value of nLNK pin
#घोषणा ES_TXUNRN	0x8000	// Tx Underrun


// Receive Control Register
/* BANK 0  */
#घोषणा RCR_REG(lp)		SMC_REG(lp, 0x0004, 0)
#घोषणा RCR_RX_ABORT	0x0001	// Set अगर a rx frame was पातed
#घोषणा RCR_PRMS	0x0002	// Enable promiscuous mode
#घोषणा RCR_ALMUL	0x0004	// When set accepts all multicast frames
#घोषणा RCR_RXEN	0x0100	// IFF this is set, we can receive packets
#घोषणा RCR_STRIP_CRC	0x0200	// When set strips CRC from rx packets
#घोषणा RCR_ABORT_ENB	0x0200	// When set will पात rx on collision
#घोषणा RCR_FILT_CAR	0x0400	// When set filters leading 12 bit s of carrier
#घोषणा RCR_SOFTRST	0x8000 	// resets the chip

/* the normal settings क्रम the RCR रेजिस्टर : */
#घोषणा RCR_DEFAULT	(RCR_STRIP_CRC | RCR_RXEN)
#घोषणा RCR_CLEAR	0x0	// set it to a base state


// Counter Register
/* BANK 0  */
#घोषणा COUNTER_REG(lp)	SMC_REG(lp, 0x0006, 0)


// Memory Inक्रमmation Register
/* BANK 0  */
#घोषणा MIR_REG(lp)		SMC_REG(lp, 0x0008, 0)


// Receive/Phy Control Register
/* BANK 0  */
#घोषणा RPC_REG(lp)		SMC_REG(lp, 0x000A, 0)
#घोषणा RPC_SPEED	0x2000	// When 1 PHY is in 100Mbps mode.
#घोषणा RPC_DPLX	0x1000	// When 1 PHY is in Full-Duplex Mode
#घोषणा RPC_ANEG	0x0800	// When 1 PHY is in Auto-Negotiate Mode
#घोषणा RPC_LSXA_SHFT	5	// Bits to shअगरt LS2A,LS1A,LS0A to lsb
#घोषणा RPC_LSXB_SHFT	2	// Bits to get LS2B,LS1B,LS0B to lsb

#अगर_अघोषित RPC_LSA_DEFAULT
#घोषणा RPC_LSA_DEFAULT	RPC_LED_100
#पूर्ण_अगर
#अगर_अघोषित RPC_LSB_DEFAULT
#घोषणा RPC_LSB_DEFAULT RPC_LED_FD
#पूर्ण_अगर

#घोषणा RPC_DEFAULT (RPC_ANEG | RPC_SPEED | RPC_DPLX)


/* Bank 0 0x0C is reserved */

// Bank Select Register
/* All Banks */
#घोषणा BSR_REG		0x000E


// Configuration Reg
/* BANK 1 */
#घोषणा CONFIG_REG(lp)	SMC_REG(lp, 0x0000,	1)
#घोषणा CONFIG_EXT_PHY	0x0200	// 1=बाह्यal MII, 0=पूर्णांकernal Phy
#घोषणा CONFIG_GPCNTRL	0x0400	// Inverse value drives pin nCNTRL
#घोषणा CONFIG_NO_WAIT	0x1000	// When 1 no extra रुको states on ISA bus
#घोषणा CONFIG_EPH_POWER_EN 0x8000 // When 0 EPH is placed पूर्णांकo low घातer mode.

// Default is घातered-up, Internal Phy, Wait States, and pin nCNTRL=low
#घोषणा CONFIG_DEFAULT	(CONFIG_EPH_POWER_EN)


// Base Address Register
/* BANK 1 */
#घोषणा BASE_REG(lp)	SMC_REG(lp, 0x0002, 1)


// Inभागidual Address Registers
/* BANK 1 */
#घोषणा ADDR0_REG(lp)	SMC_REG(lp, 0x0004, 1)
#घोषणा ADDR1_REG(lp)	SMC_REG(lp, 0x0006, 1)
#घोषणा ADDR2_REG(lp)	SMC_REG(lp, 0x0008, 1)


// General Purpose Register
/* BANK 1 */
#घोषणा GP_REG(lp)		SMC_REG(lp, 0x000A, 1)


// Control Register
/* BANK 1 */
#घोषणा CTL_REG(lp)		SMC_REG(lp, 0x000C, 1)
#घोषणा CTL_RCV_BAD	0x4000 // When 1 bad CRC packets are received
#घोषणा CTL_AUTO_RELEASE 0x0800 // When 1 tx pages are released स्वतःmatically
#घोषणा CTL_LE_ENABLE	0x0080 // When 1 enables Link Error पूर्णांकerrupt
#घोषणा CTL_CR_ENABLE	0x0040 // When 1 enables Counter Rollover पूर्णांकerrupt
#घोषणा CTL_TE_ENABLE	0x0020 // When 1 enables Transmit Error पूर्णांकerrupt
#घोषणा CTL_EEPROM_SELECT 0x0004 // Controls EEPROM reload & store
#घोषणा CTL_RELOAD	0x0002 // When set पढ़ोs EEPROM पूर्णांकo रेजिस्टरs
#घोषणा CTL_STORE	0x0001 // When set stores रेजिस्टरs पूर्णांकo EEPROM


// MMU Command Register
/* BANK 2 */
#घोषणा MMU_CMD_REG(lp)	SMC_REG(lp, 0x0000, 2)
#घोषणा MC_BUSY		1	// When 1 the last release has not completed
#घोषणा MC_NOP		(0<<5)	// No Op
#घोषणा MC_ALLOC	(1<<5) 	// OR with number of 256 byte packets
#घोषणा MC_RESET	(2<<5)	// Reset MMU to initial state
#घोषणा MC_REMOVE	(3<<5) 	// Remove the current rx packet
#घोषणा MC_RELEASE  	(4<<5) 	// Remove and release the current rx packet
#घोषणा MC_FREEPKT  	(5<<5) 	// Release packet in PNR रेजिस्टर
#घोषणा MC_ENQUEUE	(6<<5)	// Enqueue the packet क्रम transmit
#घोषणा MC_RSTTXFIFO	(7<<5)	// Reset the TX FIFOs


// Packet Number Register
/* BANK 2 */
#घोषणा PN_REG(lp)		SMC_REG(lp, 0x0002, 2)


// Allocation Result Register
/* BANK 2 */
#घोषणा AR_REG(lp)		SMC_REG(lp, 0x0003, 2)
#घोषणा AR_FAILED	0x80	// Alocation Failed


// TX FIFO Ports Register
/* BANK 2 */
#घोषणा TXFIFO_REG(lp)	SMC_REG(lp, 0x0004, 2)
#घोषणा TXFIFO_TEMPTY	0x80	// TX FIFO Empty

// RX FIFO Ports Register
/* BANK 2 */
#घोषणा RXFIFO_REG(lp)	SMC_REG(lp, 0x0005, 2)
#घोषणा RXFIFO_REMPTY	0x80	// RX FIFO Empty

#घोषणा FIFO_REG(lp)	SMC_REG(lp, 0x0004, 2)

// Poपूर्णांकer Register
/* BANK 2 */
#घोषणा PTR_REG(lp)		SMC_REG(lp, 0x0006, 2)
#घोषणा PTR_RCV		0x8000 // 1=Receive area, 0=Transmit area
#घोषणा PTR_AUTOINC 	0x4000 // Auto increment the poपूर्णांकer on each access
#घोषणा PTR_READ	0x2000 // When 1 the operation is a पढ़ो


// Data Register
/* BANK 2 */
#घोषणा DATA_REG(lp)	SMC_REG(lp, 0x0008, 2)


// Interrupt Status/Acknowledge Register
/* BANK 2 */
#घोषणा INT_REG(lp)		SMC_REG(lp, 0x000C, 2)


// Interrupt Mask Register
/* BANK 2 */
#घोषणा IM_REG(lp)		SMC_REG(lp, 0x000D, 2)
#घोषणा IM_MDINT	0x80 // PHY MI Register 18 Interrupt
#घोषणा IM_ERCV_INT	0x40 // Early Receive Interrupt
#घोषणा IM_EPH_INT	0x20 // Set by Ethernet Protocol Handler section
#घोषणा IM_RX_OVRN_INT	0x10 // Set by Receiver Overruns
#घोषणा IM_ALLOC_INT	0x08 // Set when allocation request is completed
#घोषणा IM_TX_EMPTY_INT	0x04 // Set अगर the TX FIFO goes empty
#घोषणा IM_TX_INT	0x02 // Transmit Interrupt
#घोषणा IM_RCV_INT	0x01 // Receive Interrupt


// Multicast Table Registers
/* BANK 3 */
#घोषणा MCAST_REG1(lp)	SMC_REG(lp, 0x0000, 3)
#घोषणा MCAST_REG2(lp)	SMC_REG(lp, 0x0002, 3)
#घोषणा MCAST_REG3(lp)	SMC_REG(lp, 0x0004, 3)
#घोषणा MCAST_REG4(lp)	SMC_REG(lp, 0x0006, 3)


// Management Interface Register (MII)
/* BANK 3 */
#घोषणा MII_REG(lp)		SMC_REG(lp, 0x0008, 3)
#घोषणा MII_MSK_CRS100	0x4000 // Disables CRS100 detection during tx half dup
#घोषणा MII_MDOE	0x0008 // MII Output Enable
#घोषणा MII_MCLK	0x0004 // MII Clock, pin MDCLK
#घोषणा MII_MDI		0x0002 // MII Input, pin MDI
#घोषणा MII_MDO		0x0001 // MII Output, pin MDO


// Revision Register
/* BANK 3 */
/* ( hi: chip id   low: rev # ) */
#घोषणा REV_REG(lp)		SMC_REG(lp, 0x000A, 3)


// Early RCV Register
/* BANK 3 */
/* this is NOT on SMC9192 */
#घोषणा ERCV_REG(lp)	SMC_REG(lp, 0x000C, 3)
#घोषणा ERCV_RCV_DISCRD	0x0080 // When 1 discards a packet being received
#घोषणा ERCV_THRESHOLD	0x001F // ERCV Threshold Mask


// External Register
/* BANK 7 */
#घोषणा EXT_REG(lp)		SMC_REG(lp, 0x0000, 7)


#घोषणा CHIP_9192	3
#घोषणा CHIP_9194	4
#घोषणा CHIP_9195	5
#घोषणा CHIP_9196	6
#घोषणा CHIP_91100	7
#घोषणा CHIP_91100FD	8
#घोषणा CHIP_91111FD	9

अटल स्थिर अक्षर * chip_ids[ 16 ] =  अणु
	शून्य, शून्य, शून्य,
	/* 3 */ "SMC91C90/91C92",
	/* 4 */ "SMC91C94",
	/* 5 */ "SMC91C95",
	/* 6 */ "SMC91C96",
	/* 7 */ "SMC91C100",
	/* 8 */ "SMC91C100FD",
	/* 9 */ "SMC91C11xFD",
	शून्य, शून्य, शून्य,
	शून्य, शून्य, शून्यपूर्ण;


/*
 . Receive status bits
*/
#घोषणा RS_ALGNERR	0x8000
#घोषणा RS_BRODCAST	0x4000
#घोषणा RS_BADCRC	0x2000
#घोषणा RS_ODDFRAME	0x1000
#घोषणा RS_TOOLONG	0x0800
#घोषणा RS_TOOSHORT	0x0400
#घोषणा RS_MULTICAST	0x0001
#घोषणा RS_ERRORS	(RS_ALGNERR | RS_BADCRC | RS_TOOLONG | RS_TOOSHORT)


/*
 * PHY IDs
 *  LAN83C183 == LAN91C111 Internal PHY
 */
#घोषणा PHY_LAN83C183	0x0016f840
#घोषणा PHY_LAN83C180	0x02821c50

/*
 * PHY Register Addresses (LAN91C111 Internal PHY)
 *
 * Generic PHY रेजिस्टरs can be found in <linux/mii.h>
 *
 * These phy रेजिस्टरs are specअगरic to our on-board phy.
 */

// PHY Configuration Register 1
#घोषणा PHY_CFG1_REG		0x10
#घोषणा PHY_CFG1_LNKDIS		0x8000	// 1=Rx Link Detect Function disabled
#घोषणा PHY_CFG1_XMTDIS		0x4000	// 1=TP Transmitter Disabled
#घोषणा PHY_CFG1_XMTPDN		0x2000	// 1=TP Transmitter Powered Down
#घोषणा PHY_CFG1_BYPSCR		0x0400	// 1=Bypass scrambler/descrambler
#घोषणा PHY_CFG1_UNSCDS		0x0200	// 1=Unscramble Idle Reception Disable
#घोषणा PHY_CFG1_EQLZR		0x0100	// 1=Rx Equalizer Disabled
#घोषणा PHY_CFG1_CABLE		0x0080	// 1=STP(150ohm), 0=UTP(100ohm)
#घोषणा PHY_CFG1_RLVL0		0x0040	// 1=Rx Squelch level reduced by 4.5db
#घोषणा PHY_CFG1_TLVL_SHIFT	2	// Transmit Output Level Adjust
#घोषणा PHY_CFG1_TLVL_MASK	0x003C
#घोषणा PHY_CFG1_TRF_MASK	0x0003	// Transmitter Rise/Fall समय


// PHY Configuration Register 2
#घोषणा PHY_CFG2_REG		0x11
#घोषणा PHY_CFG2_APOLDIS	0x0020	// 1=Auto Polarity Correction disabled
#घोषणा PHY_CFG2_JABDIS		0x0010	// 1=Jabber disabled
#घोषणा PHY_CFG2_MREG		0x0008	// 1=Multiple रेजिस्टर access (MII mgt)
#घोषणा PHY_CFG2_INTMDIO	0x0004	// 1=Interrupt संकेतed with MDIO pulseo

// PHY Status Output (and Interrupt status) Register
#घोषणा PHY_INT_REG		0x12	// Status Output (Interrupt Status)
#घोषणा PHY_INT_INT		0x8000	// 1=bits have changed since last पढ़ो
#घोषणा PHY_INT_LNKFAIL		0x4000	// 1=Link Not detected
#घोषणा PHY_INT_LOSSSYNC	0x2000	// 1=Descrambler has lost sync
#घोषणा PHY_INT_CWRD		0x1000	// 1=Invalid 4B5B code detected on rx
#घोषणा PHY_INT_SSD		0x0800	// 1=No Start Of Stream detected on rx
#घोषणा PHY_INT_ESD		0x0400	// 1=No End Of Stream detected on rx
#घोषणा PHY_INT_RPOL		0x0200	// 1=Reverse Polarity detected
#घोषणा PHY_INT_JAB		0x0100	// 1=Jabber detected
#घोषणा PHY_INT_SPDDET		0x0080	// 1=100Base-TX mode, 0=10Base-T mode
#घोषणा PHY_INT_DPLXDET		0x0040	// 1=Device in Full Duplex

// PHY Interrupt/Status Mask Register
#घोषणा PHY_MASK_REG		0x13	// Interrupt Mask
// Uses the same bit definitions as PHY_INT_REG


/*
 * SMC91C96 ethernet config and status रेजिस्टरs.
 * These are in the "attribute" space.
 */
#घोषणा ECOR			0x8000
#घोषणा ECOR_RESET		0x80
#घोषणा ECOR_LEVEL_IRQ		0x40
#घोषणा ECOR_WR_ATTRIB		0x04
#घोषणा ECOR_ENABLE		0x01

#घोषणा ECSR			0x8002
#घोषणा ECSR_IOIS8		0x20
#घोषणा ECSR_PWRDWN		0x04
#घोषणा ECSR_INT		0x02

#घोषणा ATTRIB_SIZE		((64*1024) << SMC_IO_SHIFT)


/*
 * Macros to असलtract रेजिस्टर access according to the data bus
 * capabilities.  Please use those and not the in/out primitives.
 * Note: the following macros करो *not* select the bank -- this must
 * be करोne separately as needed in the मुख्य code.  The SMC_REG() macro
 * only uses the bank argument क्रम debugging purposes (when enabled).
 *
 * Note: despite अंतरभूत functions being safer, everything leading to this
 * should preferably be macros to let BUG() display the line number in
 * the core source code since we're पूर्णांकerested in the top call site
 * not in any अंतरभूत function location.
 */

#अगर SMC_DEBUG > 0
#घोषणा SMC_REG(lp, reg, bank)					\
	(अणु								\
		पूर्णांक __b = SMC_CURRENT_BANK(lp);			\
		अगर (unlikely((__b & ~0xf0) != (0x3300 | bank))) अणु	\
			pr_err("%s: bank reg screwed (0x%04x)\n",	\
			       CARDNAME, __b);				\
			BUG();						\
		पूर्ण							\
		reg<<SMC_IO_SHIFT;					\
	पूर्ण)
#अन्यथा
#घोषणा SMC_REG(lp, reg, bank)	(reg<<SMC_IO_SHIFT)
#पूर्ण_अगर

/*
 * Hack Alert: Some setups just can't ग_लिखो 8 or 16 bits reliably when not
 * aligned to a 32 bit boundary.  I tell you that करोes exist!
 * Fortunately the affected रेजिस्टर accesses can be easily worked around
 * since we can ग_लिखो zeroes to the preceding 16 bits without adverse
 * effects and use a 32-bit access.
 *
 * Enक्रमce it on any 32-bit capable setup क्रम now.
 */
#घोषणा SMC_MUST_ALIGN_WRITE(lp)	SMC_32BIT(lp)

#घोषणा SMC_GET_PN(lp)						\
	(SMC_8BIT(lp)	? (SMC_inb(ioaddr, PN_REG(lp)))	\
				: (SMC_inw(ioaddr, PN_REG(lp)) & 0xFF))

#घोषणा SMC_SET_PN(lp, x)						\
	करो अणु								\
		अगर (SMC_MUST_ALIGN_WRITE(lp))				\
			SMC_outl((x)<<16, ioaddr, SMC_REG(lp, 0, 2));	\
		अन्यथा अगर (SMC_8BIT(lp))				\
			SMC_outb(x, ioaddr, PN_REG(lp));		\
		अन्यथा							\
			SMC_outw(lp, x, ioaddr, PN_REG(lp));		\
	पूर्ण जबतक (0)

#घोषणा SMC_GET_AR(lp)						\
	(SMC_8BIT(lp)	? (SMC_inb(ioaddr, AR_REG(lp)))	\
				: (SMC_inw(ioaddr, PN_REG(lp)) >> 8))

#घोषणा SMC_GET_TXFIFO(lp)						\
	(SMC_8BIT(lp)	? (SMC_inb(ioaddr, TXFIFO_REG(lp)))	\
				: (SMC_inw(ioaddr, TXFIFO_REG(lp)) & 0xFF))

#घोषणा SMC_GET_RXFIFO(lp)						\
	(SMC_8BIT(lp)	? (SMC_inb(ioaddr, RXFIFO_REG(lp)))	\
				: (SMC_inw(ioaddr, TXFIFO_REG(lp)) >> 8))

#घोषणा SMC_GET_INT(lp)						\
	(SMC_8BIT(lp)	? (SMC_inb(ioaddr, INT_REG(lp)))	\
				: (SMC_inw(ioaddr, INT_REG(lp)) & 0xFF))

#घोषणा SMC_ACK_INT(lp, x)						\
	करो अणु								\
		अगर (SMC_8BIT(lp))					\
			SMC_outb(x, ioaddr, INT_REG(lp));		\
		अन्यथा अणु							\
			अचिन्हित दीर्घ __flags;				\
			पूर्णांक __mask;					\
			local_irq_save(__flags);			\
			__mask = SMC_inw(ioaddr, INT_REG(lp)) & ~0xff; \
			SMC_outw(lp, __mask | (x), ioaddr, INT_REG(lp)); \
			local_irq_restore(__flags);			\
		पूर्ण							\
	पूर्ण जबतक (0)

#घोषणा SMC_GET_INT_MASK(lp)						\
	(SMC_8BIT(lp)	? (SMC_inb(ioaddr, IM_REG(lp)))	\
				: (SMC_inw(ioaddr, INT_REG(lp)) >> 8))

#घोषणा SMC_SET_INT_MASK(lp, x)					\
	करो अणु								\
		अगर (SMC_8BIT(lp))					\
			SMC_outb(x, ioaddr, IM_REG(lp));		\
		अन्यथा							\
			SMC_outw(lp, (x) << 8, ioaddr, INT_REG(lp));	\
	पूर्ण जबतक (0)

#घोषणा SMC_CURRENT_BANK(lp)	SMC_inw(ioaddr, BANK_SELECT)

#घोषणा SMC_SELECT_BANK(lp, x)					\
	करो अणु								\
		अगर (SMC_MUST_ALIGN_WRITE(lp))				\
			SMC_outl((x)<<16, ioaddr, 12<<SMC_IO_SHIFT);	\
		अन्यथा							\
			SMC_outw(lp, x, ioaddr, BANK_SELECT);		\
	पूर्ण जबतक (0)

#घोषणा SMC_GET_BASE(lp)		SMC_inw(ioaddr, BASE_REG(lp))

#घोषणा SMC_SET_BASE(lp, x)	SMC_outw(lp, x, ioaddr, BASE_REG(lp))

#घोषणा SMC_GET_CONFIG(lp)	SMC_inw(ioaddr, CONFIG_REG(lp))

#घोषणा SMC_SET_CONFIG(lp, x)	SMC_outw(lp, x, ioaddr, CONFIG_REG(lp))

#घोषणा SMC_GET_COUNTER(lp)	SMC_inw(ioaddr, COUNTER_REG(lp))

#घोषणा SMC_GET_CTL(lp)		SMC_inw(ioaddr, CTL_REG(lp))

#घोषणा SMC_SET_CTL(lp, x)	SMC_outw(lp, x, ioaddr, CTL_REG(lp))

#घोषणा SMC_GET_MII(lp)		SMC_inw(ioaddr, MII_REG(lp))

#घोषणा SMC_GET_GP(lp)		SMC_inw(ioaddr, GP_REG(lp))

#घोषणा SMC_SET_GP(lp, x)						\
	करो अणु								\
		अगर (SMC_MUST_ALIGN_WRITE(lp))				\
			SMC_outl((x)<<16, ioaddr, SMC_REG(lp, 8, 1));	\
		अन्यथा							\
			SMC_outw(lp, x, ioaddr, GP_REG(lp));		\
	पूर्ण जबतक (0)

#घोषणा SMC_SET_MII(lp, x)	SMC_outw(lp, x, ioaddr, MII_REG(lp))

#घोषणा SMC_GET_MIR(lp)		SMC_inw(ioaddr, MIR_REG(lp))

#घोषणा SMC_SET_MIR(lp, x)	SMC_outw(lp, x, ioaddr, MIR_REG(lp))

#घोषणा SMC_GET_MMU_CMD(lp)	SMC_inw(ioaddr, MMU_CMD_REG(lp))

#घोषणा SMC_SET_MMU_CMD(lp, x)	SMC_outw(lp, x, ioaddr, MMU_CMD_REG(lp))

#घोषणा SMC_GET_FIFO(lp)	SMC_inw(ioaddr, FIFO_REG(lp))

#घोषणा SMC_GET_PTR(lp)		SMC_inw(ioaddr, PTR_REG(lp))

#घोषणा SMC_SET_PTR(lp, x)						\
	करो अणु								\
		अगर (SMC_MUST_ALIGN_WRITE(lp))				\
			SMC_outl((x)<<16, ioaddr, SMC_REG(lp, 4, 2));	\
		अन्यथा							\
			SMC_outw(lp, x, ioaddr, PTR_REG(lp));		\
	पूर्ण जबतक (0)

#घोषणा SMC_GET_EPH_STATUS(lp)	SMC_inw(ioaddr, EPH_STATUS_REG(lp))

#घोषणा SMC_GET_RCR(lp)		SMC_inw(ioaddr, RCR_REG(lp))

#घोषणा SMC_SET_RCR(lp, x)		SMC_outw(lp, x, ioaddr, RCR_REG(lp))

#घोषणा SMC_GET_REV(lp)		SMC_inw(ioaddr, REV_REG(lp))

#घोषणा SMC_GET_RPC(lp)		SMC_inw(ioaddr, RPC_REG(lp))

#घोषणा SMC_SET_RPC(lp, x)						\
	करो अणु								\
		अगर (SMC_MUST_ALIGN_WRITE(lp))				\
			SMC_outl((x)<<16, ioaddr, SMC_REG(lp, 8, 0));	\
		अन्यथा							\
			SMC_outw(lp, x, ioaddr, RPC_REG(lp));		\
	पूर्ण जबतक (0)

#घोषणा SMC_GET_TCR(lp)		SMC_inw(ioaddr, TCR_REG(lp))

#घोषणा SMC_SET_TCR(lp, x)	SMC_outw(lp, x, ioaddr, TCR_REG(lp))

#अगर_अघोषित SMC_GET_MAC_ADDR
#घोषणा SMC_GET_MAC_ADDR(lp, addr)					\
	करो अणु								\
		अचिन्हित पूर्णांक __v;					\
		__v = SMC_inw(ioaddr, ADDR0_REG(lp));			\
		addr[0] = __v; addr[1] = __v >> 8;			\
		__v = SMC_inw(ioaddr, ADDR1_REG(lp));			\
		addr[2] = __v; addr[3] = __v >> 8;			\
		__v = SMC_inw(ioaddr, ADDR2_REG(lp));			\
		addr[4] = __v; addr[5] = __v >> 8;			\
	पूर्ण जबतक (0)
#पूर्ण_अगर

#घोषणा SMC_SET_MAC_ADDR(lp, addr)					\
	करो अणु								\
		SMC_outw(lp, addr[0] | (addr[1] << 8), ioaddr, ADDR0_REG(lp)); \
		SMC_outw(lp, addr[2] | (addr[3] << 8), ioaddr, ADDR1_REG(lp)); \
		SMC_outw(lp, addr[4] | (addr[5] << 8), ioaddr, ADDR2_REG(lp)); \
	पूर्ण जबतक (0)

#घोषणा SMC_SET_MCAST(lp, x)						\
	करो अणु								\
		स्थिर अचिन्हित अक्षर *mt = (x);				\
		SMC_outw(lp, mt[0] | (mt[1] << 8), ioaddr, MCAST_REG1(lp)); \
		SMC_outw(lp, mt[2] | (mt[3] << 8), ioaddr, MCAST_REG2(lp)); \
		SMC_outw(lp, mt[4] | (mt[5] << 8), ioaddr, MCAST_REG3(lp)); \
		SMC_outw(lp, mt[6] | (mt[7] << 8), ioaddr, MCAST_REG4(lp)); \
	पूर्ण जबतक (0)

#घोषणा SMC_PUT_PKT_HDR(lp, status, length)				\
	करो अणु								\
		अगर (SMC_32BIT(lp))					\
			SMC_outl((status) | (length)<<16, ioaddr,	\
				 DATA_REG(lp));			\
		अन्यथा अणु							\
			SMC_outw(lp, status, ioaddr, DATA_REG(lp));	\
			SMC_outw(lp, length, ioaddr, DATA_REG(lp));	\
		पूर्ण							\
	पूर्ण जबतक (0)

#घोषणा SMC_GET_PKT_HDR(lp, status, length)				\
	करो अणु								\
		अगर (SMC_32BIT(lp)) अणु				\
			अचिन्हित पूर्णांक __val = SMC_inl(ioaddr, DATA_REG(lp)); \
			(status) = __val & 0xffff;			\
			(length) = __val >> 16;				\
		पूर्ण अन्यथा अणु						\
			(status) = SMC_inw(ioaddr, DATA_REG(lp));	\
			(length) = SMC_inw(ioaddr, DATA_REG(lp));	\
		पूर्ण							\
	पूर्ण जबतक (0)

#घोषणा SMC_PUSH_DATA(lp, p, l)					\
	करो अणु								\
		अगर (SMC_32BIT(lp)) अणु				\
			व्योम *__ptr = (p);				\
			पूर्णांक __len = (l);				\
			व्योम __iomem *__ioaddr = ioaddr;		\
			अगर (__len >= 2 && (अचिन्हित दीर्घ)__ptr & 2) अणु	\
				__len -= 2;				\
				SMC_outsw(ioaddr, DATA_REG(lp), __ptr, 1); \
				__ptr += 2;				\
			पूर्ण						\
			अगर (SMC_CAN_USE_DATACS && lp->datacs)		\
				__ioaddr = lp->datacs;			\
			SMC_outsl(__ioaddr, DATA_REG(lp), __ptr, __len>>2); \
			अगर (__len & 2) अणु				\
				__ptr += (__len & ~3);			\
				SMC_outsw(ioaddr, DATA_REG(lp), __ptr, 1); \
			पूर्ण						\
		पूर्ण अन्यथा अगर (SMC_16BIT(lp))				\
			SMC_outsw(ioaddr, DATA_REG(lp), p, (l) >> 1);	\
		अन्यथा अगर (SMC_8BIT(lp))				\
			SMC_outsb(ioaddr, DATA_REG(lp), p, l);	\
	पूर्ण जबतक (0)

#घोषणा SMC_PULL_DATA(lp, p, l)					\
	करो अणु								\
		अगर (SMC_32BIT(lp)) अणु				\
			व्योम *__ptr = (p);				\
			पूर्णांक __len = (l);				\
			व्योम __iomem *__ioaddr = ioaddr;		\
			अगर ((अचिन्हित दीर्घ)__ptr & 2) अणु			\
				/*					\
				 * We want 32bit alignment here.	\
				 * Since some buses perक्रमm a full	\
				 * 32bit fetch even क्रम 16bit data	\
				 * we can't use SMC_inw() here.		\
				 * Back both source (on-chip) and	\
				 * destination poपूर्णांकers of 2 bytes.	\
				 * This is possible since the call to	\
				 * SMC_GET_PKT_HDR() alपढ़ोy advanced	\
				 * the source poपूर्णांकer of 4 bytes, and	\
				 * the skb_reserve(skb, 2) advanced	\
				 * the destination poपूर्णांकer of 2 bytes.	\
				 */					\
				__ptr -= 2;				\
				__len += 2;				\
				SMC_SET_PTR(lp,			\
					2|PTR_READ|PTR_RCV|PTR_AUTOINC); \
			पूर्ण						\
			अगर (SMC_CAN_USE_DATACS && lp->datacs)		\
				__ioaddr = lp->datacs;			\
			__len += 2;					\
			SMC_insl(__ioaddr, DATA_REG(lp), __ptr, __len>>2); \
		पूर्ण अन्यथा अगर (SMC_16BIT(lp))				\
			SMC_insw(ioaddr, DATA_REG(lp), p, (l) >> 1);	\
		अन्यथा अगर (SMC_8BIT(lp))				\
			SMC_insb(ioaddr, DATA_REG(lp), p, l);		\
	पूर्ण जबतक (0)

#पूर्ण_अगर  /* _SMC91X_H_ */
