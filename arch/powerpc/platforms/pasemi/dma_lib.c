<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2006-2007 PA Semi, Inc
 *
 * Common functions क्रम DMA access on PA Semi PWRficient
 */

#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश <linux/sched.h>

#समावेश <यंत्र/pasemi_dma.h>

#घोषणा MAX_TXCH 64
#घोषणा MAX_RXCH 64
#घोषणा MAX_FLAGS 64
#घोषणा MAX_FUN 8

अटल काष्ठा pasdma_status *dma_status;

अटल व्योम __iomem *iob_regs;
अटल व्योम __iomem *mac_regs[6];
अटल व्योम __iomem *dma_regs;

अटल पूर्णांक base_hw_irq;

अटल पूर्णांक num_txch, num_rxch;

अटल काष्ठा pci_dev *dma_pdev;

/* Biपंचांगaps to handle allocation of channels */

अटल DECLARE_BITMAP(txch_मुक्त, MAX_TXCH);
अटल DECLARE_BITMAP(rxch_मुक्त, MAX_RXCH);
अटल DECLARE_BITMAP(flags_मुक्त, MAX_FLAGS);
अटल DECLARE_BITMAP(fun_मुक्त, MAX_FUN);

/* pasemi_पढ़ो_iob_reg - पढ़ो IOB रेजिस्टर
 * @reg: Register to पढ़ो (offset पूर्णांकo PCI CFG space)
 */
अचिन्हित पूर्णांक pasemi_पढ़ो_iob_reg(अचिन्हित पूर्णांक reg)
अणु
	वापस in_le32(iob_regs+reg);
पूर्ण
EXPORT_SYMBOL(pasemi_पढ़ो_iob_reg);

/* pasemi_ग_लिखो_iob_reg - ग_लिखो IOB रेजिस्टर
 * @reg: Register to ग_लिखो to (offset पूर्णांकo PCI CFG space)
 * @val: Value to ग_लिखो
 */
व्योम pasemi_ग_लिखो_iob_reg(अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक val)
अणु
	out_le32(iob_regs+reg, val);
पूर्ण
EXPORT_SYMBOL(pasemi_ग_लिखो_iob_reg);

/* pasemi_पढ़ो_mac_reg - पढ़ो MAC रेजिस्टर
 * @पूर्णांकf: MAC पूर्णांकerface
 * @reg: Register to पढ़ो (offset पूर्णांकo PCI CFG space)
 */
अचिन्हित पूर्णांक pasemi_पढ़ो_mac_reg(पूर्णांक पूर्णांकf, अचिन्हित पूर्णांक reg)
अणु
	वापस in_le32(mac_regs[पूर्णांकf]+reg);
पूर्ण
EXPORT_SYMBOL(pasemi_पढ़ो_mac_reg);

/* pasemi_ग_लिखो_mac_reg - ग_लिखो MAC रेजिस्टर
 * @पूर्णांकf: MAC पूर्णांकerface
 * @reg: Register to ग_लिखो to (offset पूर्णांकo PCI CFG space)
 * @val: Value to ग_लिखो
 */
व्योम pasemi_ग_लिखो_mac_reg(पूर्णांक पूर्णांकf, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक val)
अणु
	out_le32(mac_regs[पूर्णांकf]+reg, val);
पूर्ण
EXPORT_SYMBOL(pasemi_ग_लिखो_mac_reg);

/* pasemi_पढ़ो_dma_reg - पढ़ो DMA रेजिस्टर
 * @reg: Register to पढ़ो (offset पूर्णांकo PCI CFG space)
 */
अचिन्हित पूर्णांक pasemi_पढ़ो_dma_reg(अचिन्हित पूर्णांक reg)
अणु
	वापस in_le32(dma_regs+reg);
पूर्ण
EXPORT_SYMBOL(pasemi_पढ़ो_dma_reg);

/* pasemi_ग_लिखो_dma_reg - ग_लिखो DMA रेजिस्टर
 * @reg: Register to ग_लिखो to (offset पूर्णांकo PCI CFG space)
 * @val: Value to ग_लिखो
 */
व्योम pasemi_ग_लिखो_dma_reg(अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक val)
अणु
	out_le32(dma_regs+reg, val);
पूर्ण
EXPORT_SYMBOL(pasemi_ग_लिखो_dma_reg);

अटल पूर्णांक pasemi_alloc_tx_chan(क्रमागत pasemi_dmachan_type type)
अणु
	पूर्णांक bit;
	पूर्णांक start, limit;

	चयन (type & (TXCHAN_EVT0|TXCHAN_EVT1)) अणु
	हाल TXCHAN_EVT0:
		start = 0;
		limit = 10;
		अवरोध;
	हाल TXCHAN_EVT1:
		start = 10;
		limit = MAX_TXCH;
		अवरोध;
	शेष:
		start = 0;
		limit = MAX_TXCH;
		अवरोध;
	पूर्ण
retry:
	bit = find_next_bit(txch_मुक्त, MAX_TXCH, start);
	अगर (bit >= limit)
		वापस -ENOSPC;
	अगर (!test_and_clear_bit(bit, txch_मुक्त))
		जाओ retry;

	वापस bit;
पूर्ण

अटल व्योम pasemi_मुक्त_tx_chan(पूर्णांक chan)
अणु
	BUG_ON(test_bit(chan, txch_मुक्त));
	set_bit(chan, txch_मुक्त);
पूर्ण

अटल पूर्णांक pasemi_alloc_rx_chan(व्योम)
अणु
	पूर्णांक bit;
retry:
	bit = find_first_bit(rxch_मुक्त, MAX_RXCH);
	अगर (bit >= MAX_TXCH)
		वापस -ENOSPC;
	अगर (!test_and_clear_bit(bit, rxch_मुक्त))
		जाओ retry;

	वापस bit;
पूर्ण

अटल व्योम pasemi_मुक्त_rx_chan(पूर्णांक chan)
अणु
	BUG_ON(test_bit(chan, rxch_मुक्त));
	set_bit(chan, rxch_मुक्त);
पूर्ण

/* pasemi_dma_alloc_chan - Allocate a DMA channel
 * @type: Type of channel to allocate
 * @total_size: Total size of काष्ठाure to allocate (to allow क्रम more
 *		room behind the काष्ठाure to be used by the client)
 * @offset: Offset in bytes from start of the total काष्ठाure to the beginning
 *	    of काष्ठा pasemi_dmachan. Needed when काष्ठा pasemi_dmachan is
 *	    not the first member of the client काष्ठाure.
 *
 * pasemi_dma_alloc_chan allocates a DMA channel क्रम use by a client. The
 * type argument specअगरies whether it's a RX or TX channel, and in the हाल
 * of TX channels which group it needs to beदीर्घ to (अगर any).
 *
 * Returns a poपूर्णांकer to the total काष्ठाure allocated on success, शून्य
 * on failure.
 */
व्योम *pasemi_dma_alloc_chan(क्रमागत pasemi_dmachan_type type,
			    पूर्णांक total_size, पूर्णांक offset)
अणु
	व्योम *buf;
	काष्ठा pasemi_dmachan *chan;
	पूर्णांक chno;

	BUG_ON(total_size < माप(काष्ठा pasemi_dmachan));

	buf = kzalloc(total_size, GFP_KERNEL);

	अगर (!buf)
		वापस शून्य;
	chan = buf + offset;

	chan->priv = buf;

	चयन (type & (TXCHAN|RXCHAN)) अणु
	हाल RXCHAN:
		chno = pasemi_alloc_rx_chan();
		chan->chno = chno;
		chan->irq = irq_create_mapping(शून्य,
					       base_hw_irq + num_txch + chno);
		chan->status = &dma_status->rx_sta[chno];
		अवरोध;
	हाल TXCHAN:
		chno = pasemi_alloc_tx_chan(type);
		chan->chno = chno;
		chan->irq = irq_create_mapping(शून्य, base_hw_irq + chno);
		chan->status = &dma_status->tx_sta[chno];
		अवरोध;
	पूर्ण

	chan->chan_type = type;

	वापस chan;
पूर्ण
EXPORT_SYMBOL(pasemi_dma_alloc_chan);

/* pasemi_dma_मुक्त_chan - Free a previously allocated channel
 * @chan: Channel to मुक्त
 *
 * Frees a previously allocated channel. It will also deallocate any
 * descriptor ring associated with the channel, अगर allocated.
 */
व्योम pasemi_dma_मुक्त_chan(काष्ठा pasemi_dmachan *chan)
अणु
	अगर (chan->ring_virt)
		pasemi_dma_मुक्त_ring(chan);

	चयन (chan->chan_type & (RXCHAN|TXCHAN)) अणु
	हाल RXCHAN:
		pasemi_मुक्त_rx_chan(chan->chno);
		अवरोध;
	हाल TXCHAN:
		pasemi_मुक्त_tx_chan(chan->chno);
		अवरोध;
	पूर्ण

	kमुक्त(chan->priv);
पूर्ण
EXPORT_SYMBOL(pasemi_dma_मुक्त_chan);

/* pasemi_dma_alloc_ring - Allocate descriptor ring क्रम a channel
 * @chan: Channel क्रम which to allocate
 * @ring_size: Ring size in 64-bit (8-byte) words
 *
 * Allocate a descriptor ring क्रम a channel. Returns 0 on success, त्रुटि_सं
 * on failure. The passed in काष्ठा pasemi_dmachan is updated with the
 * भव and DMA addresses of the ring.
 */
पूर्णांक pasemi_dma_alloc_ring(काष्ठा pasemi_dmachan *chan, पूर्णांक ring_size)
अणु
	BUG_ON(chan->ring_virt);

	chan->ring_size = ring_size;

	chan->ring_virt = dma_alloc_coherent(&dma_pdev->dev,
					     ring_size * माप(u64),
					     &chan->ring_dma, GFP_KERNEL);

	अगर (!chan->ring_virt)
		वापस -ENOMEM;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(pasemi_dma_alloc_ring);

/* pasemi_dma_मुक्त_ring - Free an allocated descriptor ring क्रम a channel
 * @chan: Channel क्रम which to मुक्त the descriptor ring
 *
 * Frees a previously allocated descriptor ring क्रम a channel.
 */
व्योम pasemi_dma_मुक्त_ring(काष्ठा pasemi_dmachan *chan)
अणु
	BUG_ON(!chan->ring_virt);

	dma_मुक्त_coherent(&dma_pdev->dev, chan->ring_size * माप(u64),
			  chan->ring_virt, chan->ring_dma);
	chan->ring_virt = शून्य;
	chan->ring_size = 0;
	chan->ring_dma = 0;
पूर्ण
EXPORT_SYMBOL(pasemi_dma_मुक्त_ring);

/* pasemi_dma_start_chan - Start a DMA channel
 * @chan: Channel to start
 * @cmdsta: Additional CCMDSTA/TCMDSTA bits to ग_लिखो
 *
 * Enables (starts) a DMA channel with optional additional arguments.
 */
व्योम pasemi_dma_start_chan(स्थिर काष्ठा pasemi_dmachan *chan, स्थिर u32 cmdsta)
अणु
	अगर (chan->chan_type == RXCHAN)
		pasemi_ग_लिखो_dma_reg(PAS_DMA_RXCHAN_CCMDSTA(chan->chno),
				     cmdsta | PAS_DMA_RXCHAN_CCMDSTA_EN);
	अन्यथा
		pasemi_ग_लिखो_dma_reg(PAS_DMA_TXCHAN_TCMDSTA(chan->chno),
				     cmdsta | PAS_DMA_TXCHAN_TCMDSTA_EN);
पूर्ण
EXPORT_SYMBOL(pasemi_dma_start_chan);

/* pasemi_dma_stop_chan - Stop a DMA channel
 * @chan: Channel to stop
 *
 * Stops (disables) a DMA channel. This is करोne by setting the ST bit in the
 * CMDSTA रेजिस्टर and रुकोing on the ACT (active) bit to clear, then
 * finally disabling the whole channel.
 *
 * This function will only try क्रम a लघु जबतक क्रम the channel to stop, अगर
 * it करोesn't it will वापस failure.
 *
 * Returns 1 on success, 0 on failure.
 */
#घोषणा MAX_RETRIES 5000
पूर्णांक pasemi_dma_stop_chan(स्थिर काष्ठा pasemi_dmachan *chan)
अणु
	पूर्णांक reg, retries;
	u32 sta;

	अगर (chan->chan_type == RXCHAN) अणु
		reg = PAS_DMA_RXCHAN_CCMDSTA(chan->chno);
		pasemi_ग_लिखो_dma_reg(reg, PAS_DMA_RXCHAN_CCMDSTA_ST);
		क्रम (retries = 0; retries < MAX_RETRIES; retries++) अणु
			sta = pasemi_पढ़ो_dma_reg(reg);
			अगर (!(sta & PAS_DMA_RXCHAN_CCMDSTA_ACT)) अणु
				pasemi_ग_लिखो_dma_reg(reg, 0);
				वापस 1;
			पूर्ण
			cond_resched();
		पूर्ण
	पूर्ण अन्यथा अणु
		reg = PAS_DMA_TXCHAN_TCMDSTA(chan->chno);
		pasemi_ग_लिखो_dma_reg(reg, PAS_DMA_TXCHAN_TCMDSTA_ST);
		क्रम (retries = 0; retries < MAX_RETRIES; retries++) अणु
			sta = pasemi_पढ़ो_dma_reg(reg);
			अगर (!(sta & PAS_DMA_TXCHAN_TCMDSTA_ACT)) अणु
				pasemi_ग_लिखो_dma_reg(reg, 0);
				वापस 1;
			पूर्ण
			cond_resched();
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(pasemi_dma_stop_chan);

/* pasemi_dma_alloc_buf - Allocate a buffer to use क्रम DMA
 * @chan: Channel to allocate क्रम
 * @size: Size of buffer in bytes
 * @handle: DMA handle
 *
 * Allocate a buffer to be used by the DMA engine क्रम पढ़ो/ग_लिखो,
 * similar to dma_alloc_coherent().
 *
 * Returns the भव address of the buffer, or शून्य in हाल of failure.
 */
व्योम *pasemi_dma_alloc_buf(काष्ठा pasemi_dmachan *chan, पूर्णांक size,
			   dma_addr_t *handle)
अणु
	वापस dma_alloc_coherent(&dma_pdev->dev, size, handle, GFP_KERNEL);
पूर्ण
EXPORT_SYMBOL(pasemi_dma_alloc_buf);

/* pasemi_dma_मुक्त_buf - Free a buffer used क्रम DMA
 * @chan: Channel the buffer was allocated क्रम
 * @size: Size of buffer in bytes
 * @handle: DMA handle
 *
 * Frees a previously allocated buffer.
 */
व्योम pasemi_dma_मुक्त_buf(काष्ठा pasemi_dmachan *chan, पूर्णांक size,
			 dma_addr_t *handle)
अणु
	dma_मुक्त_coherent(&dma_pdev->dev, size, handle, GFP_KERNEL);
पूर्ण
EXPORT_SYMBOL(pasemi_dma_मुक्त_buf);

/* pasemi_dma_alloc_flag - Allocate a flag (event) क्रम channel synchronization
 *
 * Allocates a flag क्रम use with channel synchronization (event descriptors).
 * Returns allocated flag (0-63), < 0 on error.
 */
पूर्णांक pasemi_dma_alloc_flag(व्योम)
अणु
	पूर्णांक bit;

retry:
	bit = find_next_bit(flags_मुक्त, MAX_FLAGS, 0);
	अगर (bit >= MAX_FLAGS)
		वापस -ENOSPC;
	अगर (!test_and_clear_bit(bit, flags_मुक्त))
		जाओ retry;

	वापस bit;
पूर्ण
EXPORT_SYMBOL(pasemi_dma_alloc_flag);


/* pasemi_dma_मुक्त_flag - Deallocates a flag (event)
 * @flag: Flag number to deallocate
 *
 * Frees up a flag so it can be reused क्रम other purposes.
 */
व्योम pasemi_dma_मुक्त_flag(पूर्णांक flag)
अणु
	BUG_ON(test_bit(flag, flags_मुक्त));
	BUG_ON(flag >= MAX_FLAGS);
	set_bit(flag, flags_मुक्त);
पूर्ण
EXPORT_SYMBOL(pasemi_dma_मुक्त_flag);


/* pasemi_dma_set_flag - Sets a flag (event) to 1
 * @flag: Flag number to set active
 *
 * Sets the flag provided to 1.
 */
व्योम pasemi_dma_set_flag(पूर्णांक flag)
अणु
	BUG_ON(flag >= MAX_FLAGS);
	अगर (flag < 32)
		pasemi_ग_लिखो_dma_reg(PAS_DMA_TXF_SFLG0, 1 << flag);
	अन्यथा
		pasemi_ग_लिखो_dma_reg(PAS_DMA_TXF_SFLG1, 1 << flag);
पूर्ण
EXPORT_SYMBOL(pasemi_dma_set_flag);

/* pasemi_dma_clear_flag - Sets a flag (event) to 0
 * @flag: Flag number to set inactive
 *
 * Sets the flag provided to 0.
 */
व्योम pasemi_dma_clear_flag(पूर्णांक flag)
अणु
	BUG_ON(flag >= MAX_FLAGS);
	अगर (flag < 32)
		pasemi_ग_लिखो_dma_reg(PAS_DMA_TXF_CFLG0, 1 << flag);
	अन्यथा
		pasemi_ग_लिखो_dma_reg(PAS_DMA_TXF_CFLG1, 1 << flag);
पूर्ण
EXPORT_SYMBOL(pasemi_dma_clear_flag);

/* pasemi_dma_alloc_fun - Allocate a function engine
 *
 * Allocates a function engine to use क्रम crypto/checksum offload
 * Returns allocated engine (0-8), < 0 on error.
 */
पूर्णांक pasemi_dma_alloc_fun(व्योम)
अणु
	पूर्णांक bit;

retry:
	bit = find_next_bit(fun_मुक्त, MAX_FLAGS, 0);
	अगर (bit >= MAX_FLAGS)
		वापस -ENOSPC;
	अगर (!test_and_clear_bit(bit, fun_मुक्त))
		जाओ retry;

	वापस bit;
पूर्ण
EXPORT_SYMBOL(pasemi_dma_alloc_fun);


/* pasemi_dma_मुक्त_fun - Deallocates a function engine
 * @flag: Engine number to deallocate
 *
 * Frees up a function engine so it can be used क्रम other purposes.
 */
व्योम pasemi_dma_मुक्त_fun(पूर्णांक fun)
अणु
	BUG_ON(test_bit(fun, fun_मुक्त));
	BUG_ON(fun >= MAX_FLAGS);
	set_bit(fun, fun_मुक्त);
पूर्ण
EXPORT_SYMBOL(pasemi_dma_मुक्त_fun);


अटल व्योम *map_onedev(काष्ठा pci_dev *p, पूर्णांक index)
अणु
	काष्ठा device_node *dn;
	व्योम __iomem *ret;

	dn = pci_device_to_OF_node(p);
	अगर (!dn)
		जाओ fallback;

	ret = of_iomap(dn, index);
	अगर (!ret)
		जाओ fallback;

	वापस ret;
fallback:
	/* This is hardcoded and ugly, but we have some firmware versions
	 * that करोn't provide the रेजिस्टर space in the device tree. Luckily
	 * they are at well-known locations so we can just करो the math here.
	 */
	वापस ioremap(0xe0000000 + (p->devfn << 12), 0x2000);
पूर्ण

/* pasemi_dma_init - Initialize the PA Semi DMA library
 *
 * This function initializes the DMA library. It must be called beक्रमe
 * any other function in the library.
 *
 * Returns 0 on success, त्रुटि_सं on failure.
 */
पूर्णांक pasemi_dma_init(व्योम)
अणु
	अटल DEFINE_SPINLOCK(init_lock);
	काष्ठा pci_dev *iob_pdev;
	काष्ठा pci_dev *pdev;
	काष्ठा resource res;
	काष्ठा device_node *dn;
	पूर्णांक i, पूर्णांकf, err = 0;
	अचिन्हित दीर्घ समयout;
	u32 पंचांगp;

	अगर (!machine_is(pasemi))
		वापस -ENODEV;

	spin_lock(&init_lock);

	/* Make sure we haven't alपढ़ोy initialized */
	अगर (dma_pdev)
		जाओ out;

	iob_pdev = pci_get_device(PCI_VENDOR_ID_PASEMI, 0xa001, शून्य);
	अगर (!iob_pdev) अणु
		BUG();
		pr_warn("Can't find I/O Bridge\n");
		err = -ENODEV;
		जाओ out;
	पूर्ण
	iob_regs = map_onedev(iob_pdev, 0);

	dma_pdev = pci_get_device(PCI_VENDOR_ID_PASEMI, 0xa007, शून्य);
	अगर (!dma_pdev) अणु
		BUG();
		pr_warn("Can't find DMA controller\n");
		err = -ENODEV;
		जाओ out;
	पूर्ण
	dma_regs = map_onedev(dma_pdev, 0);
	base_hw_irq = virq_to_hw(dma_pdev->irq);

	pci_पढ़ो_config_dword(dma_pdev, PAS_DMA_CAP_TXCH, &पंचांगp);
	num_txch = (पंचांगp & PAS_DMA_CAP_TXCH_TCHN_M) >> PAS_DMA_CAP_TXCH_TCHN_S;

	pci_पढ़ो_config_dword(dma_pdev, PAS_DMA_CAP_RXCH, &पंचांगp);
	num_rxch = (पंचांगp & PAS_DMA_CAP_RXCH_RCHN_M) >> PAS_DMA_CAP_RXCH_RCHN_S;

	पूर्णांकf = 0;
	क्रम (pdev = pci_get_device(PCI_VENDOR_ID_PASEMI, 0xa006, शून्य);
	     pdev;
	     pdev = pci_get_device(PCI_VENDOR_ID_PASEMI, 0xa006, pdev))
		mac_regs[पूर्णांकf++] = map_onedev(pdev, 0);

	pci_dev_put(pdev);

	क्रम (pdev = pci_get_device(PCI_VENDOR_ID_PASEMI, 0xa005, शून्य);
	     pdev;
	     pdev = pci_get_device(PCI_VENDOR_ID_PASEMI, 0xa005, pdev))
		mac_regs[पूर्णांकf++] = map_onedev(pdev, 0);

	pci_dev_put(pdev);

	dn = pci_device_to_OF_node(iob_pdev);
	अगर (dn)
		err = of_address_to_resource(dn, 1, &res);
	अगर (!dn || err) अणु
		/* Fallback क्रम old firmware */
		res.start = 0xfd800000;
		res.end = res.start + 0x1000;
	पूर्ण
	dma_status = ioremap_cache(res.start, resource_size(&res));
	pci_dev_put(iob_pdev);

	क्रम (i = 0; i < MAX_TXCH; i++)
		__set_bit(i, txch_मुक्त);

	क्रम (i = 0; i < MAX_RXCH; i++)
		__set_bit(i, rxch_मुक्त);

	समयout = jअगरfies + HZ;
	pasemi_ग_लिखो_dma_reg(PAS_DMA_COM_RXCMD, 0);
	जबतक (pasemi_पढ़ो_dma_reg(PAS_DMA_COM_RXSTA) & 1) अणु
		अगर (समय_after(jअगरfies, समयout)) अणु
			pr_warn("Warning: Could not disable RX section\n");
			अवरोध;
		पूर्ण
	पूर्ण

	समयout = jअगरfies + HZ;
	pasemi_ग_लिखो_dma_reg(PAS_DMA_COM_TXCMD, 0);
	जबतक (pasemi_पढ़ो_dma_reg(PAS_DMA_COM_TXSTA) & 1) अणु
		अगर (समय_after(jअगरfies, समयout)) अणु
			pr_warn("Warning: Could not disable TX section\n");
			अवरोध;
		पूर्ण
	पूर्ण

	/* setup resource allocations क्रम the dअगरferent DMA sections */
	पंचांगp = pasemi_पढ़ो_dma_reg(PAS_DMA_COM_CFG);
	pasemi_ग_लिखो_dma_reg(PAS_DMA_COM_CFG, पंचांगp | 0x18000000);

	/* enable tx section */
	pasemi_ग_लिखो_dma_reg(PAS_DMA_COM_TXCMD, PAS_DMA_COM_TXCMD_EN);

	/* enable rx section */
	pasemi_ग_लिखो_dma_reg(PAS_DMA_COM_RXCMD, PAS_DMA_COM_RXCMD_EN);

	क्रम (i = 0; i < MAX_FLAGS; i++)
		__set_bit(i, flags_मुक्त);

	क्रम (i = 0; i < MAX_FUN; i++)
		__set_bit(i, fun_मुक्त);

	/* clear all status flags */
	pasemi_ग_लिखो_dma_reg(PAS_DMA_TXF_CFLG0, 0xffffffff);
	pasemi_ग_लिखो_dma_reg(PAS_DMA_TXF_CFLG1, 0xffffffff);

	pr_info("PA Semi PWRficient DMA library initialized "
		"(%d tx, %d rx channels)\n", num_txch, num_rxch);

out:
	spin_unlock(&init_lock);
	वापस err;
पूर्ण
EXPORT_SYMBOL(pasemi_dma_init);
