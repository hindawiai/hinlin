<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
  A FORE Systems 200E-series driver क्रम ATM on Linux.
  Christophe Lizzi (lizzi@cnam.fr), October 1999-March 2003.

  Based on the PCA-200E driver from Uwe Dannowski (Uwe.Dannowski@inf.tu-dresden.de).

  This driver simultaneously supports PCA-200E and SBA-200E adapters
  on i386, alpha (untested), घातerpc, sparc and sparc64 architectures.

*/


#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/capability.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/bitops.h>
#समावेश <linux/pci.h>
#समावेश <linux/module.h>
#समावेश <linux/aपंचांगdev.h>
#समावेश <linux/sonet.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/delay.h>
#समावेश <linux/firmware.h>
#समावेश <linux/pgtable.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/माला.स>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/atomic.h>

#अगर_घोषित CONFIG_SBUS
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <यंत्र/idprom.h>
#समावेश <यंत्र/खोलोprom.h>
#समावेश <यंत्र/oplib.h>
#पूर्ण_अगर

#अगर defined(CONFIG_ATM_FORE200E_USE_TASKLET) /* defer पूर्णांकerrupt work to a tasklet */
#घोषणा FORE200E_USE_TASKLET
#पूर्ण_अगर

#अगर 0 /* enable the debugging code of the buffer supply queues */
#घोषणा FORE200E_BSQ_DEBUG
#पूर्ण_अगर

#अगर 1 /* ensure correct handling of 52-byte AAL0 SDUs expected by aपंचांगdump-like apps */
#घोषणा FORE200E_52BYTE_AAL0_SDU
#पूर्ण_अगर

#समावेश "fore200e.h"
#समावेश "suni.h"

#घोषणा FORE200E_VERSION "0.3e"

#घोषणा FORE200E         "fore200e: "

#अगर 0 /* override .config */
#घोषणा CONFIG_ATM_FORE200E_DEBUG 1
#पूर्ण_अगर
#अगर defined(CONFIG_ATM_FORE200E_DEBUG) && (CONFIG_ATM_FORE200E_DEBUG > 0)
#घोषणा DPRINTK(level, क्रमmat, args...)  करो अणु अगर (CONFIG_ATM_FORE200E_DEBUG >= (level)) \
                                                  prपूर्णांकk(FORE200E क्रमmat, ##args); पूर्ण जबतक (0)
#अन्यथा
#घोषणा DPRINTK(level, क्रमmat, args...)  करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर


#घोषणा FORE200E_ALIGN(addr, alignment) \
        ((((अचिन्हित दीर्घ)(addr) + (alignment - 1)) & ~(alignment - 1)) - (अचिन्हित दीर्घ)(addr))

#घोषणा FORE200E_DMA_INDEX(dma_addr, type, index)  ((dma_addr) + (index) * माप(type))

#घोषणा FORE200E_INDEX(virt_addr, type, index)     (&((type *)(virt_addr))[ index ])

#घोषणा FORE200E_NEXT_ENTRY(index, modulo)         (index = ((index) + 1) % (modulo))

#अगर 1
#घोषणा ASSERT(expr)     अगर (!(expr)) अणु \
			     prपूर्णांकk(FORE200E "assertion failed! %s[%d]: %s\n", \
				    __func__, __LINE__, #expr); \
			     panic(FORE200E "%s", __func__); \
			 पूर्ण
#अन्यथा
#घोषणा ASSERT(expr)     करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर


अटल स्थिर काष्ठा aपंचांगdev_ops   क्रमe200e_ops;

अटल LIST_HEAD(क्रमe200e_boards);


MODULE_AUTHOR("Christophe Lizzi - credits to Uwe Dannowski and Heikki Vatiainen");
MODULE_DESCRIPTION("FORE Systems 200E-series ATM driver - version " FORE200E_VERSION);

अटल स्थिर पूर्णांक क्रमe200e_rx_buf_nbr[ BUFFER_SCHEME_NBR ][ BUFFER_MAGN_NBR ] = अणु
    अणु BUFFER_S1_NBR, BUFFER_L1_NBR पूर्ण,
    अणु BUFFER_S2_NBR, BUFFER_L2_NBR पूर्ण
पूर्ण;

अटल स्थिर पूर्णांक क्रमe200e_rx_buf_size[ BUFFER_SCHEME_NBR ][ BUFFER_MAGN_NBR ] = अणु
    अणु BUFFER_S1_SIZE, BUFFER_L1_SIZE पूर्ण,
    अणु BUFFER_S2_SIZE, BUFFER_L2_SIZE पूर्ण
पूर्ण;


#अगर defined(CONFIG_ATM_FORE200E_DEBUG) && (CONFIG_ATM_FORE200E_DEBUG > 0)
अटल स्थिर अक्षर* क्रमe200e_traffic_class[] = अणु "NONE", "UBR", "CBR", "VBR", "ABR", "ANY" पूर्ण;
#पूर्ण_अगर


#अगर 0 /* currently unused */
अटल पूर्णांक 
क्रमe200e_क्रमe2aपंचांग_aal(क्रमागत क्रमe200e_aal aal)
अणु
    चयन(aal) अणु
    हाल FORE200E_AAL0:  वापस ATM_AAL0;
    हाल FORE200E_AAL34: वापस ATM_AAL34;
    हाल FORE200E_AAL5:  वापस ATM_AAL5;
    पूर्ण

    वापस -EINVAL;
पूर्ण
#पूर्ण_अगर


अटल क्रमागत क्रमe200e_aal
क्रमe200e_aपंचांग2क्रमe_aal(पूर्णांक aal)
अणु
    चयन(aal) अणु
    हाल ATM_AAL0:  वापस FORE200E_AAL0;
    हाल ATM_AAL34: वापस FORE200E_AAL34;
    हाल ATM_AAL1:
    हाल ATM_AAL2:
    हाल ATM_AAL5:  वापस FORE200E_AAL5;
    पूर्ण

    वापस -EINVAL;
पूर्ण


अटल अक्षर*
क्रमe200e_irq_itoa(पूर्णांक irq)
अणु
    अटल अक्षर str[8];
    प्र_लिखो(str, "%d", irq);
    वापस str;
पूर्ण


/* allocate and align a chunk of memory पूर्णांकended to hold the data behing exchanged
   between the driver and the adapter (using streaming DVMA) */

अटल पूर्णांक
क्रमe200e_chunk_alloc(काष्ठा क्रमe200e* क्रमe200e, काष्ठा chunk* chunk, पूर्णांक size, पूर्णांक alignment, पूर्णांक direction)
अणु
    अचिन्हित दीर्घ offset = 0;

    अगर (alignment <= माप(पूर्णांक))
	alignment = 0;

    chunk->alloc_size = size + alignment;
    chunk->direction  = direction;

    chunk->alloc_addr = kzalloc(chunk->alloc_size, GFP_KERNEL);
    अगर (chunk->alloc_addr == शून्य)
	वापस -ENOMEM;

    अगर (alignment > 0)
	offset = FORE200E_ALIGN(chunk->alloc_addr, alignment); 
    
    chunk->align_addr = chunk->alloc_addr + offset;

    chunk->dma_addr = dma_map_single(क्रमe200e->dev, chunk->align_addr,
				     size, direction);
    अगर (dma_mapping_error(क्रमe200e->dev, chunk->dma_addr)) अणु
	kमुक्त(chunk->alloc_addr);
	वापस -ENOMEM;
    पूर्ण
    वापस 0;
पूर्ण


/* मुक्त a chunk of memory */

अटल व्योम
क्रमe200e_chunk_मुक्त(काष्ठा क्रमe200e* क्रमe200e, काष्ठा chunk* chunk)
अणु
    dma_unmap_single(क्रमe200e->dev, chunk->dma_addr, chunk->dma_size,
		     chunk->direction);
    kमुक्त(chunk->alloc_addr);
पूर्ण

/*
 * Allocate a DMA consistent chunk of memory पूर्णांकended to act as a communication
 * mechanism (to hold descriptors, status, queues, etc.) shared by the driver
 * and the adapter.
 */
अटल पूर्णांक
क्रमe200e_dma_chunk_alloc(काष्ठा क्रमe200e *क्रमe200e, काष्ठा chunk *chunk,
		पूर्णांक size, पूर्णांक nbr, पूर्णांक alignment)
अणु
	/* वापसed chunks are page-aligned */
	chunk->alloc_size = size * nbr;
	chunk->alloc_addr = dma_alloc_coherent(क्रमe200e->dev, chunk->alloc_size,
					       &chunk->dma_addr, GFP_KERNEL);
	अगर (!chunk->alloc_addr)
		वापस -ENOMEM;
	chunk->align_addr = chunk->alloc_addr;
	वापस 0;
पूर्ण

/*
 * Free a DMA consistent chunk of memory.
 */
अटल व्योम
क्रमe200e_dma_chunk_मुक्त(काष्ठा क्रमe200e* क्रमe200e, काष्ठा chunk* chunk)
अणु
	dma_मुक्त_coherent(क्रमe200e->dev, chunk->alloc_size, chunk->alloc_addr,
			  chunk->dma_addr);
पूर्ण

अटल व्योम
क्रमe200e_spin(पूर्णांक msecs)
अणु
    अचिन्हित दीर्घ समयout = jअगरfies + msecs_to_jअगरfies(msecs);
    जबतक (समय_beक्रमe(jअगरfies, समयout));
पूर्ण


अटल पूर्णांक
क्रमe200e_poll(काष्ठा क्रमe200e* क्रमe200e, अस्थिर u32* addr, u32 val, पूर्णांक msecs)
अणु
    अचिन्हित दीर्घ समयout = jअगरfies + msecs_to_jअगरfies(msecs);
    पूर्णांक           ok;

    mb();
    करो अणु
	अगर ((ok = (*addr == val)) || (*addr & STATUS_ERROR))
	    अवरोध;

    पूर्ण जबतक (समय_beक्रमe(jअगरfies, समयout));

#अगर 1
    अगर (!ok) अणु
	prपूर्णांकk(FORE200E "cmd polling failed, got status 0x%08x, expected 0x%08x\n",
	       *addr, val);
    पूर्ण
#पूर्ण_अगर

    वापस ok;
पूर्ण


अटल पूर्णांक
क्रमe200e_io_poll(काष्ठा क्रमe200e* क्रमe200e, अस्थिर u32 __iomem *addr, u32 val, पूर्णांक msecs)
अणु
    अचिन्हित दीर्घ समयout = jअगरfies + msecs_to_jअगरfies(msecs);
    पूर्णांक           ok;

    करो अणु
	अगर ((ok = (क्रमe200e->bus->पढ़ो(addr) == val)))
	    अवरोध;

    पूर्ण जबतक (समय_beक्रमe(jअगरfies, समयout));

#अगर 1
    अगर (!ok) अणु
	prपूर्णांकk(FORE200E "I/O polling failed, got status 0x%08x, expected 0x%08x\n",
	       क्रमe200e->bus->पढ़ो(addr), val);
    पूर्ण
#पूर्ण_अगर

    वापस ok;
पूर्ण


अटल व्योम
क्रमe200e_मुक्त_rx_buf(काष्ठा क्रमe200e* क्रमe200e)
अणु
    पूर्णांक scheme, magn, nbr;
    काष्ठा buffer* buffer;

    क्रम (scheme = 0; scheme < BUFFER_SCHEME_NBR; scheme++) अणु
	क्रम (magn = 0; magn < BUFFER_MAGN_NBR; magn++) अणु

	    अगर ((buffer = क्रमe200e->host_bsq[ scheme ][ magn ].buffer) != शून्य) अणु

		क्रम (nbr = 0; nbr < क्रमe200e_rx_buf_nbr[ scheme ][ magn ]; nbr++) अणु

		    काष्ठा chunk* data = &buffer[ nbr ].data;

		    अगर (data->alloc_addr != शून्य)
			क्रमe200e_chunk_मुक्त(क्रमe200e, data);
		पूर्ण
	    पूर्ण
	पूर्ण
    पूर्ण
पूर्ण


अटल व्योम
क्रमe200e_uninit_bs_queue(काष्ठा क्रमe200e* क्रमe200e)
अणु
    पूर्णांक scheme, magn;
    
    क्रम (scheme = 0; scheme < BUFFER_SCHEME_NBR; scheme++) अणु
	क्रम (magn = 0; magn < BUFFER_MAGN_NBR; magn++) अणु

	    काष्ठा chunk* status    = &क्रमe200e->host_bsq[ scheme ][ magn ].status;
	    काष्ठा chunk* rbd_block = &क्रमe200e->host_bsq[ scheme ][ magn ].rbd_block;
	    
	    अगर (status->alloc_addr)
		क्रमe200e_dma_chunk_मुक्त(क्रमe200e, status);
	    
	    अगर (rbd_block->alloc_addr)
		क्रमe200e_dma_chunk_मुक्त(क्रमe200e, rbd_block);
	पूर्ण
    पूर्ण
पूर्ण


अटल पूर्णांक
क्रमe200e_reset(काष्ठा क्रमe200e* क्रमe200e, पूर्णांक diag)
अणु
    पूर्णांक ok;

    क्रमe200e->cp_monitor = क्रमe200e->virt_base + FORE200E_CP_MONITOR_OFFSET;
    
    क्रमe200e->bus->ग_लिखो(BSTAT_COLD_START, &क्रमe200e->cp_monitor->bstat);

    क्रमe200e->bus->reset(क्रमe200e);

    अगर (diag) अणु
	ok = क्रमe200e_io_poll(क्रमe200e, &क्रमe200e->cp_monitor->bstat, BSTAT_SELFTEST_OK, 1000);
	अगर (ok == 0) अणु
	    
	    prपूर्णांकk(FORE200E "device %s self-test failed\n", क्रमe200e->name);
	    वापस -ENODEV;
	पूर्ण

	prपूर्णांकk(FORE200E "device %s self-test passed\n", क्रमe200e->name);
	
	क्रमe200e->state = FORE200E_STATE_RESET;
    पूर्ण

    वापस 0;
पूर्ण


अटल व्योम
क्रमe200e_shutकरोwn(काष्ठा क्रमe200e* क्रमe200e)
अणु
    prपूर्णांकk(FORE200E "removing device %s at 0x%lx, IRQ %s\n",
	   क्रमe200e->name, क्रमe200e->phys_base, 
	   क्रमe200e_irq_itoa(क्रमe200e->irq));
    
    अगर (क्रमe200e->state > FORE200E_STATE_RESET) अणु
	/* first, reset the board to prevent further पूर्णांकerrupts or data transfers */
	क्रमe200e_reset(क्रमe200e, 0);
    पूर्ण
    
    /* then, release all allocated resources */
    चयन(क्रमe200e->state) अणु

    हाल FORE200E_STATE_COMPLETE:
	kमुक्त(क्रमe200e->stats);

	fallthrough;
    हाल FORE200E_STATE_IRQ:
	मुक्त_irq(क्रमe200e->irq, क्रमe200e->aपंचांग_dev);

	fallthrough;
    हाल FORE200E_STATE_ALLOC_BUF:
	क्रमe200e_मुक्त_rx_buf(क्रमe200e);

	fallthrough;
    हाल FORE200E_STATE_INIT_BSQ:
	क्रमe200e_uninit_bs_queue(क्रमe200e);

	fallthrough;
    हाल FORE200E_STATE_INIT_RXQ:
	क्रमe200e_dma_chunk_मुक्त(क्रमe200e, &क्रमe200e->host_rxq.status);
	क्रमe200e_dma_chunk_मुक्त(क्रमe200e, &क्रमe200e->host_rxq.rpd);

	fallthrough;
    हाल FORE200E_STATE_INIT_TXQ:
	क्रमe200e_dma_chunk_मुक्त(क्रमe200e, &क्रमe200e->host_txq.status);
	क्रमe200e_dma_chunk_मुक्त(क्रमe200e, &क्रमe200e->host_txq.tpd);

	fallthrough;
    हाल FORE200E_STATE_INIT_CMDQ:
	क्रमe200e_dma_chunk_मुक्त(क्रमe200e, &क्रमe200e->host_cmdq.status);

	fallthrough;
    हाल FORE200E_STATE_INITIALIZE:
	/* nothing to करो क्रम that state */

    हाल FORE200E_STATE_START_FW:
	/* nothing to करो क्रम that state */

    हाल FORE200E_STATE_RESET:
	/* nothing to करो क्रम that state */

    हाल FORE200E_STATE_MAP:
	क्रमe200e->bus->unmap(क्रमe200e);

	fallthrough;
    हाल FORE200E_STATE_CONFIGURE:
	/* nothing to करो क्रम that state */

    हाल FORE200E_STATE_REGISTER:
	/* XXX shouldn't we *start* by deरेजिस्टरing the device? */
	aपंचांग_dev_deरेजिस्टर(क्रमe200e->aपंचांग_dev);

    हाल FORE200E_STATE_BLANK:
	/* nothing to करो क्रम that state */
	अवरोध;
    पूर्ण
पूर्ण


#अगर_घोषित CONFIG_PCI

अटल u32 क्रमe200e_pca_पढ़ो(अस्थिर u32 __iomem *addr)
अणु
    /* on big-endian hosts, the board is configured to convert
       the endianess of slave RAM accesses  */
    वापस le32_to_cpu(पढ़ोl(addr));
पूर्ण


अटल व्योम क्रमe200e_pca_ग_लिखो(u32 val, अस्थिर u32 __iomem *addr)
अणु
    /* on big-endian hosts, the board is configured to convert
       the endianess of slave RAM accesses  */
    ग_लिखोl(cpu_to_le32(val), addr);
पूर्ण

अटल पूर्णांक
क्रमe200e_pca_irq_check(काष्ठा क्रमe200e* क्रमe200e)
अणु
    /* this is a 1 bit रेजिस्टर */
    पूर्णांक irq_posted = पढ़ोl(क्रमe200e->regs.pca.psr);

#अगर defined(CONFIG_ATM_FORE200E_DEBUG) && (CONFIG_ATM_FORE200E_DEBUG == 2)
    अगर (irq_posted && (पढ़ोl(क्रमe200e->regs.pca.hcr) & PCA200E_HCR_OUTFULL)) अणु
	DPRINTK(2,"FIFO OUT full, device %d\n", क्रमe200e->aपंचांग_dev->number);
    पूर्ण
#पूर्ण_अगर

    वापस irq_posted;
पूर्ण


अटल व्योम
क्रमe200e_pca_irq_ack(काष्ठा क्रमe200e* क्रमe200e)
अणु
    ग_लिखोl(PCA200E_HCR_CLRINTR, क्रमe200e->regs.pca.hcr);
पूर्ण


अटल व्योम
क्रमe200e_pca_reset(काष्ठा क्रमe200e* क्रमe200e)
अणु
    ग_लिखोl(PCA200E_HCR_RESET, क्रमe200e->regs.pca.hcr);
    क्रमe200e_spin(10);
    ग_लिखोl(0, क्रमe200e->regs.pca.hcr);
पूर्ण


अटल पूर्णांक क्रमe200e_pca_map(काष्ठा क्रमe200e* क्रमe200e)
अणु
    DPRINTK(2, "device %s being mapped in memory\n", क्रमe200e->name);

    क्रमe200e->virt_base = ioremap(क्रमe200e->phys_base, PCA200E_IOSPACE_LENGTH);
    
    अगर (क्रमe200e->virt_base == शून्य) अणु
	prपूर्णांकk(FORE200E "can't map device %s\n", क्रमe200e->name);
	वापस -EFAULT;
    पूर्ण

    DPRINTK(1, "device %s mapped to 0x%p\n", क्रमe200e->name, क्रमe200e->virt_base);

    /* gain access to the PCA specअगरic रेजिस्टरs  */
    क्रमe200e->regs.pca.hcr = क्रमe200e->virt_base + PCA200E_HCR_OFFSET;
    क्रमe200e->regs.pca.imr = क्रमe200e->virt_base + PCA200E_IMR_OFFSET;
    क्रमe200e->regs.pca.psr = क्रमe200e->virt_base + PCA200E_PSR_OFFSET;

    क्रमe200e->state = FORE200E_STATE_MAP;
    वापस 0;
पूर्ण


अटल व्योम
क्रमe200e_pca_unmap(काष्ठा क्रमe200e* क्रमe200e)
अणु
    DPRINTK(2, "device %s being unmapped from memory\n", क्रमe200e->name);

    अगर (क्रमe200e->virt_base != शून्य)
	iounmap(क्रमe200e->virt_base);
पूर्ण


अटल पूर्णांक क्रमe200e_pca_configure(काष्ठा क्रमe200e *क्रमe200e)
अणु
    काष्ठा pci_dev *pci_dev = to_pci_dev(क्रमe200e->dev);
    u8              master_ctrl, latency;

    DPRINTK(2, "device %s being configured\n", क्रमe200e->name);

    अगर ((pci_dev->irq == 0) || (pci_dev->irq == 0xFF)) अणु
	prपूर्णांकk(FORE200E "incorrect IRQ setting - misconfigured PCI-PCI bridge?\n");
	वापस -EIO;
    पूर्ण

    pci_पढ़ो_config_byte(pci_dev, PCA200E_PCI_MASTER_CTRL, &master_ctrl);

    master_ctrl = master_ctrl
#अगर defined(__BIG_ENDIAN)
	/* request the PCA board to convert the endianess of slave RAM accesses */
	| PCA200E_CTRL_CONVERT_ENDIAN
#पूर्ण_अगर
#अगर 0
        | PCA200E_CTRL_DIS_CACHE_RD
        | PCA200E_CTRL_DIS_WRT_INVAL
        | PCA200E_CTRL_ENA_CONT_REQ_MODE
        | PCA200E_CTRL_2_CACHE_WRT_INVAL
#पूर्ण_अगर
	| PCA200E_CTRL_LARGE_PCI_BURSTS;
    
    pci_ग_लिखो_config_byte(pci_dev, PCA200E_PCI_MASTER_CTRL, master_ctrl);

    /* उठाओ latency from 32 (शेष) to 192, as this seems to prevent NIC
       lockups (under heavy rx loads) due to continuous 'FIFO OUT full' condition.
       this may impact the perक्रमmances of other PCI devices on the same bus, though */
    latency = 192;
    pci_ग_लिखो_config_byte(pci_dev, PCI_LATENCY_TIMER, latency);

    क्रमe200e->state = FORE200E_STATE_CONFIGURE;
    वापस 0;
पूर्ण


अटल पूर्णांक __init
क्रमe200e_pca_prom_पढ़ो(काष्ठा क्रमe200e* क्रमe200e, काष्ठा prom_data* prom)
अणु
    काष्ठा host_cmdq*       cmdq  = &क्रमe200e->host_cmdq;
    काष्ठा host_cmdq_entry* entry = &cmdq->host_entry[ cmdq->head ];
    काष्ठा prom_opcode      opcode;
    पूर्णांक                     ok;
    u32                     prom_dma;

    FORE200E_NEXT_ENTRY(cmdq->head, QUEUE_SIZE_CMD);

    opcode.opcode = OPCODE_GET_PROM;
    opcode.pad    = 0;

    prom_dma = dma_map_single(क्रमe200e->dev, prom, माप(काष्ठा prom_data),
			      DMA_FROM_DEVICE);
    अगर (dma_mapping_error(क्रमe200e->dev, prom_dma))
	वापस -ENOMEM;

    क्रमe200e->bus->ग_लिखो(prom_dma, &entry->cp_entry->cmd.prom_block.prom_haddr);
    
    *entry->status = STATUS_PENDING;

    क्रमe200e->bus->ग_लिखो(*(u32*)&opcode, (u32 __iomem *)&entry->cp_entry->cmd.prom_block.opcode);

    ok = क्रमe200e_poll(क्रमe200e, entry->status, STATUS_COMPLETE, 400);

    *entry->status = STATUS_FREE;

    dma_unmap_single(क्रमe200e->dev, prom_dma, माप(काष्ठा prom_data), DMA_FROM_DEVICE);

    अगर (ok == 0) अणु
	prपूर्णांकk(FORE200E "unable to get PROM data from device %s\n", क्रमe200e->name);
	वापस -EIO;
    पूर्ण

#अगर defined(__BIG_ENDIAN)
    
#घोषणा swap_here(addr) (*((u32*)(addr)) = swab32( *((u32*)(addr)) ))

    /* MAC address is stored as little-endian */
    swap_here(&prom->mac_addr[0]);
    swap_here(&prom->mac_addr[4]);
#पूर्ण_अगर
    
    वापस 0;
पूर्ण


अटल पूर्णांक
क्रमe200e_pca_proc_पढ़ो(काष्ठा क्रमe200e* क्रमe200e, अक्षर *page)
अणु
    काष्ठा pci_dev *pci_dev = to_pci_dev(क्रमe200e->dev);

    वापस प्र_लिखो(page, "   PCI bus/slot/function:\t%d/%d/%d\n",
		   pci_dev->bus->number, PCI_SLOT(pci_dev->devfn), PCI_FUNC(pci_dev->devfn));
पूर्ण

अटल स्थिर काष्ठा क्रमe200e_bus क्रमe200e_pci_ops = अणु
	.model_name		= "PCA-200E",
	.proc_name		= "pca200e",
	.descr_alignment	= 32,
	.buffer_alignment	= 4,
	.status_alignment	= 32,
	.पढ़ो			= क्रमe200e_pca_पढ़ो,
	.ग_लिखो			= क्रमe200e_pca_ग_लिखो,
	.configure		= क्रमe200e_pca_configure,
	.map			= क्रमe200e_pca_map,
	.reset			= क्रमe200e_pca_reset,
	.prom_पढ़ो		= क्रमe200e_pca_prom_पढ़ो,
	.unmap			= क्रमe200e_pca_unmap,
	.irq_check		= क्रमe200e_pca_irq_check,
	.irq_ack		= क्रमe200e_pca_irq_ack,
	.proc_पढ़ो		= क्रमe200e_pca_proc_पढ़ो,
पूर्ण;
#पूर्ण_अगर /* CONFIG_PCI */

#अगर_घोषित CONFIG_SBUS

अटल u32 क्रमe200e_sba_पढ़ो(अस्थिर u32 __iomem *addr)
अणु
    वापस sbus_पढ़ोl(addr);
पूर्ण

अटल व्योम क्रमe200e_sba_ग_लिखो(u32 val, अस्थिर u32 __iomem *addr)
अणु
    sbus_ग_लिखोl(val, addr);
पूर्ण

अटल व्योम क्रमe200e_sba_irq_enable(काष्ठा क्रमe200e *क्रमe200e)
अणु
	u32 hcr = क्रमe200e->bus->पढ़ो(क्रमe200e->regs.sba.hcr) & SBA200E_HCR_STICKY;
	क्रमe200e->bus->ग_लिखो(hcr | SBA200E_HCR_INTR_ENA, क्रमe200e->regs.sba.hcr);
पूर्ण

अटल पूर्णांक क्रमe200e_sba_irq_check(काष्ठा क्रमe200e *क्रमe200e)
अणु
	वापस क्रमe200e->bus->पढ़ो(क्रमe200e->regs.sba.hcr) & SBA200E_HCR_INTR_REQ;
पूर्ण

अटल व्योम क्रमe200e_sba_irq_ack(काष्ठा क्रमe200e *क्रमe200e)
अणु
	u32 hcr = क्रमe200e->bus->पढ़ो(क्रमe200e->regs.sba.hcr) & SBA200E_HCR_STICKY;
	क्रमe200e->bus->ग_लिखो(hcr | SBA200E_HCR_INTR_CLR, क्रमe200e->regs.sba.hcr);
पूर्ण

अटल व्योम क्रमe200e_sba_reset(काष्ठा क्रमe200e *क्रमe200e)
अणु
	क्रमe200e->bus->ग_लिखो(SBA200E_HCR_RESET, क्रमe200e->regs.sba.hcr);
	क्रमe200e_spin(10);
	क्रमe200e->bus->ग_लिखो(0, क्रमe200e->regs.sba.hcr);
पूर्ण

अटल पूर्णांक __init क्रमe200e_sba_map(काष्ठा क्रमe200e *क्रमe200e)
अणु
	काष्ठा platक्रमm_device *op = to_platक्रमm_device(क्रमe200e->dev);
	अचिन्हित पूर्णांक bursts;

	/* gain access to the SBA specअगरic रेजिस्टरs  */
	क्रमe200e->regs.sba.hcr = of_ioremap(&op->resource[0], 0, SBA200E_HCR_LENGTH, "SBA HCR");
	क्रमe200e->regs.sba.bsr = of_ioremap(&op->resource[1], 0, SBA200E_BSR_LENGTH, "SBA BSR");
	क्रमe200e->regs.sba.isr = of_ioremap(&op->resource[2], 0, SBA200E_ISR_LENGTH, "SBA ISR");
	क्रमe200e->virt_base    = of_ioremap(&op->resource[3], 0, SBA200E_RAM_LENGTH, "SBA RAM");

	अगर (!क्रमe200e->virt_base) अणु
		prपूर्णांकk(FORE200E "unable to map RAM of device %s\n", क्रमe200e->name);
		वापस -EFAULT;
	पूर्ण

	DPRINTK(1, "device %s mapped to 0x%p\n", क्रमe200e->name, क्रमe200e->virt_base);
    
	क्रमe200e->bus->ग_लिखो(0x02, क्रमe200e->regs.sba.isr); /* XXX hardwired पूर्णांकerrupt level */

	/* get the supported DVMA burst sizes */
	bursts = of_getपूर्णांकprop_शेष(op->dev.of_node->parent, "burst-sizes", 0x00);

	अगर (sbus_can_dma_64bit())
		sbus_set_sbus64(&op->dev, bursts);

	क्रमe200e->state = FORE200E_STATE_MAP;
	वापस 0;
पूर्ण

अटल व्योम क्रमe200e_sba_unmap(काष्ठा क्रमe200e *क्रमe200e)
अणु
	काष्ठा platक्रमm_device *op = to_platक्रमm_device(क्रमe200e->dev);

	of_iounmap(&op->resource[0], क्रमe200e->regs.sba.hcr, SBA200E_HCR_LENGTH);
	of_iounmap(&op->resource[1], क्रमe200e->regs.sba.bsr, SBA200E_BSR_LENGTH);
	of_iounmap(&op->resource[2], क्रमe200e->regs.sba.isr, SBA200E_ISR_LENGTH);
	of_iounmap(&op->resource[3], क्रमe200e->virt_base,    SBA200E_RAM_LENGTH);
पूर्ण

अटल पूर्णांक __init क्रमe200e_sba_configure(काष्ठा क्रमe200e *क्रमe200e)
अणु
	क्रमe200e->state = FORE200E_STATE_CONFIGURE;
	वापस 0;
पूर्ण

अटल पूर्णांक __init क्रमe200e_sba_prom_पढ़ो(काष्ठा क्रमe200e *क्रमe200e, काष्ठा prom_data *prom)
अणु
	काष्ठा platक्रमm_device *op = to_platक्रमm_device(क्रमe200e->dev);
	स्थिर u8 *prop;
	पूर्णांक len;

	prop = of_get_property(op->dev.of_node, "madaddrlo2", &len);
	अगर (!prop)
		वापस -ENODEV;
	स_नकल(&prom->mac_addr[4], prop, 4);

	prop = of_get_property(op->dev.of_node, "madaddrhi4", &len);
	अगर (!prop)
		वापस -ENODEV;
	स_नकल(&prom->mac_addr[2], prop, 4);

	prom->serial_number = of_getपूर्णांकprop_शेष(op->dev.of_node,
						    "serialnumber", 0);
	prom->hw_revision = of_getपूर्णांकprop_शेष(op->dev.of_node,
						  "promversion", 0);
    
	वापस 0;
पूर्ण

अटल पूर्णांक क्रमe200e_sba_proc_पढ़ो(काष्ठा क्रमe200e *क्रमe200e, अक्षर *page)
अणु
	काष्ठा platक्रमm_device *op = to_platक्रमm_device(क्रमe200e->dev);
	स्थिर काष्ठा linux_prom_रेजिस्टरs *regs;

	regs = of_get_property(op->dev.of_node, "reg", शून्य);

	वापस प्र_लिखो(page, "   SBUS slot/device:\t\t%d/'%pOFn'\n",
		       (regs ? regs->which_io : 0), op->dev.of_node);
पूर्ण

अटल स्थिर काष्ठा क्रमe200e_bus क्रमe200e_sbus_ops = अणु
	.model_name		= "SBA-200E",
	.proc_name		= "sba200e",
	.descr_alignment	= 32,
	.buffer_alignment	= 64,
	.status_alignment	= 32,
	.पढ़ो			= क्रमe200e_sba_पढ़ो,
	.ग_लिखो			= क्रमe200e_sba_ग_लिखो,
	.configure		= क्रमe200e_sba_configure,
	.map			= क्रमe200e_sba_map,
	.reset			= क्रमe200e_sba_reset,
	.prom_पढ़ो		= क्रमe200e_sba_prom_पढ़ो,
	.unmap			= क्रमe200e_sba_unmap,
	.irq_enable		= क्रमe200e_sba_irq_enable,
	.irq_check		= क्रमe200e_sba_irq_check,
	.irq_ack		= क्रमe200e_sba_irq_ack,
	.proc_पढ़ो		= क्रमe200e_sba_proc_पढ़ो,
पूर्ण;
#पूर्ण_अगर /* CONFIG_SBUS */

अटल व्योम
क्रमe200e_tx_irq(काष्ठा क्रमe200e* क्रमe200e)
अणु
    काष्ठा host_txq*        txq = &क्रमe200e->host_txq;
    काष्ठा host_txq_entry*  entry;
    काष्ठा aपंचांग_vcc*         vcc;
    काष्ठा क्रमe200e_vc_map* vc_map;

    अगर (क्रमe200e->host_txq.txing == 0)
	वापस;

    क्रम (;;) अणु
	
	entry = &txq->host_entry[ txq->tail ];

        अगर ((*entry->status & STATUS_COMPLETE) == 0) अणु
	    अवरोध;
	पूर्ण

	DPRINTK(3, "TX COMPLETED: entry = %p [tail = %d], vc_map = %p, skb = %p\n", 
		entry, txq->tail, entry->vc_map, entry->skb);

	/* मुक्त copy of misaligned data */
	kमुक्त(entry->data);
	
	/* हटाओ DMA mapping */
	dma_unmap_single(क्रमe200e->dev, entry->tpd->tsd[ 0 ].buffer, entry->tpd->tsd[ 0 ].length,
				 DMA_TO_DEVICE);

	vc_map = entry->vc_map;

	/* vcc बंदd since the समय the entry was submitted क्रम tx? */
	अगर ((vc_map->vcc == शून्य) ||
	    (test_bit(ATM_VF_READY, &vc_map->vcc->flags) == 0)) अणु

	    DPRINTK(1, "no ready vcc found for PDU sent on device %d\n",
		    क्रमe200e->aपंचांग_dev->number);

	    dev_kमुक्त_skb_any(entry->skb);
	पूर्ण
	अन्यथा अणु
	    ASSERT(vc_map->vcc);

	    /* vcc बंदd then immediately re-खोलोed? */
	    अगर (vc_map->incarn != entry->incarn) अणु

		/* when a vcc is बंदd, some PDUs may be still pending in the tx queue.
		   अगर the same vcc is immediately re-खोलोed, those pending PDUs must
		   not be popped after the completion of their emission, as they refer
		   to the prior incarnation of that vcc. otherwise, sk_aपंचांग(vcc)->sk_wmem_alloc
		   would be decremented by the size of the (unrelated) skb, possibly
		   leading to a negative sk->sk_wmem_alloc count, ultimately मुक्तzing the vcc.
		   we thus bind the tx entry to the current incarnation of the vcc
		   when the entry is submitted क्रम tx. When the tx later completes,
		   अगर the incarnation number of the tx entry करोes not match the one
		   of the vcc, then this implies that the vcc has been बंदd then re-खोलोed.
		   we thus just drop the skb here. */

		DPRINTK(1, "vcc closed-then-re-opened; dropping PDU sent on device %d\n",
			क्रमe200e->aपंचांग_dev->number);

		dev_kमुक्त_skb_any(entry->skb);
	    पूर्ण
	    अन्यथा अणु
		vcc = vc_map->vcc;
		ASSERT(vcc);

		/* notअगरy tx completion */
		अगर (vcc->pop) अणु
		    vcc->pop(vcc, entry->skb);
		पूर्ण
		अन्यथा अणु
		    dev_kमुक्त_skb_any(entry->skb);
		पूर्ण

		/* check error condition */
		अगर (*entry->status & STATUS_ERROR)
		    atomic_inc(&vcc->stats->tx_err);
		अन्यथा
		    atomic_inc(&vcc->stats->tx);
	    पूर्ण
	पूर्ण

	*entry->status = STATUS_FREE;

	क्रमe200e->host_txq.txing--;

	FORE200E_NEXT_ENTRY(txq->tail, QUEUE_SIZE_TX);
    पूर्ण
पूर्ण


#अगर_घोषित FORE200E_BSQ_DEBUG
पूर्णांक bsq_audit(पूर्णांक where, काष्ठा host_bsq* bsq, पूर्णांक scheme, पूर्णांक magn)
अणु
    काष्ठा buffer* buffer;
    पूर्णांक count = 0;

    buffer = bsq->मुक्तbuf;
    जबतक (buffer) अणु

	अगर (buffer->supplied) अणु
	    prपूर्णांकk(FORE200E "bsq_audit(%d): queue %d.%d, buffer %ld supplied but in free list!\n",
		   where, scheme, magn, buffer->index);
	पूर्ण

	अगर (buffer->magn != magn) अणु
	    prपूर्णांकk(FORE200E "bsq_audit(%d): queue %d.%d, buffer %ld, unexpected magn = %d\n",
		   where, scheme, magn, buffer->index, buffer->magn);
	पूर्ण

	अगर (buffer->scheme != scheme) अणु
	    prपूर्णांकk(FORE200E "bsq_audit(%d): queue %d.%d, buffer %ld, unexpected scheme = %d\n",
		   where, scheme, magn, buffer->index, buffer->scheme);
	पूर्ण

	अगर ((buffer->index < 0) || (buffer->index >= क्रमe200e_rx_buf_nbr[ scheme ][ magn ])) अणु
	    prपूर्णांकk(FORE200E "bsq_audit(%d): queue %d.%d, out of range buffer index = %ld !\n",
		   where, scheme, magn, buffer->index);
	पूर्ण

	count++;
	buffer = buffer->next;
    पूर्ण

    अगर (count != bsq->मुक्तbuf_count) अणु
	prपूर्णांकk(FORE200E "bsq_audit(%d): queue %d.%d, %d bufs in free list, but freebuf_count = %d\n",
	       where, scheme, magn, count, bsq->मुक्तbuf_count);
    पूर्ण
    वापस 0;
पूर्ण
#पूर्ण_अगर


अटल व्योम
क्रमe200e_supply(काष्ठा क्रमe200e* क्रमe200e)
अणु
    पूर्णांक  scheme, magn, i;

    काष्ठा host_bsq*       bsq;
    काष्ठा host_bsq_entry* entry;
    काष्ठा buffer*         buffer;

    क्रम (scheme = 0; scheme < BUFFER_SCHEME_NBR; scheme++) अणु
	क्रम (magn = 0; magn < BUFFER_MAGN_NBR; magn++) अणु

	    bsq = &क्रमe200e->host_bsq[ scheme ][ magn ];

#अगर_घोषित FORE200E_BSQ_DEBUG
	    bsq_audit(1, bsq, scheme, magn);
#पूर्ण_अगर
	    जबतक (bsq->मुक्तbuf_count >= RBD_BLK_SIZE) अणु

		DPRINTK(2, "supplying %d rx buffers to queue %d / %d, freebuf_count = %d\n",
			RBD_BLK_SIZE, scheme, magn, bsq->मुक्तbuf_count);

		entry = &bsq->host_entry[ bsq->head ];

		क्रम (i = 0; i < RBD_BLK_SIZE; i++) अणु

		    /* take the first buffer in the मुक्त buffer list */
		    buffer = bsq->मुक्तbuf;
		    अगर (!buffer) अणु
			prपूर्णांकk(FORE200E "no more free bufs in queue %d.%d, but freebuf_count = %d\n",
			       scheme, magn, bsq->मुक्तbuf_count);
			वापस;
		    पूर्ण
		    bsq->मुक्तbuf = buffer->next;
		    
#अगर_घोषित FORE200E_BSQ_DEBUG
		    अगर (buffer->supplied)
			prपूर्णांकk(FORE200E "queue %d.%d, buffer %lu already supplied\n",
			       scheme, magn, buffer->index);
		    buffer->supplied = 1;
#पूर्ण_अगर
		    entry->rbd_block->rbd[ i ].buffer_haddr = buffer->data.dma_addr;
		    entry->rbd_block->rbd[ i ].handle       = FORE200E_BUF2HDL(buffer);
		पूर्ण

		FORE200E_NEXT_ENTRY(bsq->head, QUEUE_SIZE_BS);

 		/* decrease accordingly the number of मुक्त rx buffers */
		bsq->मुक्तbuf_count -= RBD_BLK_SIZE;

		*entry->status = STATUS_PENDING;
		क्रमe200e->bus->ग_लिखो(entry->rbd_block_dma, &entry->cp_entry->rbd_block_haddr);
	    पूर्ण
	पूर्ण
    पूर्ण
पूर्ण


अटल पूर्णांक
क्रमe200e_push_rpd(काष्ठा क्रमe200e* क्रमe200e, काष्ठा aपंचांग_vcc* vcc, काष्ठा rpd* rpd)
अणु
    काष्ठा sk_buff*      skb;
    काष्ठा buffer*       buffer;
    काष्ठा क्रमe200e_vcc* क्रमe200e_vcc;
    पूर्णांक                  i, pdu_len = 0;
#अगर_घोषित FORE200E_52BYTE_AAL0_SDU
    u32                  cell_header = 0;
#पूर्ण_अगर

    ASSERT(vcc);
    
    क्रमe200e_vcc = FORE200E_VCC(vcc);
    ASSERT(क्रमe200e_vcc);

#अगर_घोषित FORE200E_52BYTE_AAL0_SDU
    अगर ((vcc->qos.aal == ATM_AAL0) && (vcc->qos.rxtp.max_sdu == ATM_AAL0_SDU)) अणु

	cell_header = (rpd->aपंचांग_header.gfc << ATM_HDR_GFC_SHIFT) |
	              (rpd->aपंचांग_header.vpi << ATM_HDR_VPI_SHIFT) |
                      (rpd->aपंचांग_header.vci << ATM_HDR_VCI_SHIFT) |
                      (rpd->aपंचांग_header.plt << ATM_HDR_PTI_SHIFT) | 
                       rpd->aपंचांग_header.clp;
	pdu_len = 4;
    पूर्ण
#पूर्ण_अगर
    
    /* compute total PDU length */
    क्रम (i = 0; i < rpd->nseg; i++)
	pdu_len += rpd->rsd[ i ].length;
    
    skb = alloc_skb(pdu_len, GFP_ATOMIC);
    अगर (skb == शून्य) अणु
	DPRINTK(2, "unable to alloc new skb, rx PDU length = %d\n", pdu_len);

	atomic_inc(&vcc->stats->rx_drop);
	वापस -ENOMEM;
    पूर्ण 

    __net_बारtamp(skb);
    
#अगर_घोषित FORE200E_52BYTE_AAL0_SDU
    अगर (cell_header) अणु
	*((u32*)skb_put(skb, 4)) = cell_header;
    पूर्ण
#पूर्ण_अगर

    /* reassemble segments */
    क्रम (i = 0; i < rpd->nseg; i++) अणु
	
	/* rebuild rx buffer address from rsd handle */
	buffer = FORE200E_HDL2BUF(rpd->rsd[ i ].handle);
	
	/* Make device DMA transfer visible to CPU.  */
	dma_sync_single_क्रम_cpu(क्रमe200e->dev, buffer->data.dma_addr,
				rpd->rsd[i].length, DMA_FROM_DEVICE);
	
	skb_put_data(skb, buffer->data.align_addr, rpd->rsd[i].length);

	/* Now let the device get at it again.  */
	dma_sync_single_क्रम_device(क्रमe200e->dev, buffer->data.dma_addr,
				   rpd->rsd[i].length, DMA_FROM_DEVICE);
    पूर्ण

    DPRINTK(3, "rx skb: len = %d, truesize = %d\n", skb->len, skb->truesize);
    
    अगर (pdu_len < क्रमe200e_vcc->rx_min_pdu)
	क्रमe200e_vcc->rx_min_pdu = pdu_len;
    अगर (pdu_len > क्रमe200e_vcc->rx_max_pdu)
	क्रमe200e_vcc->rx_max_pdu = pdu_len;
    क्रमe200e_vcc->rx_pdu++;

    /* push PDU */
    अगर (aपंचांग_अक्षरge(vcc, skb->truesize) == 0) अणु

	DPRINTK(2, "receive buffers saturated for %d.%d.%d - PDU dropped\n",
		vcc->itf, vcc->vpi, vcc->vci);

	dev_kमुक्त_skb_any(skb);

	atomic_inc(&vcc->stats->rx_drop);
	वापस -ENOMEM;
    पूर्ण

    vcc->push(vcc, skb);
    atomic_inc(&vcc->stats->rx);

    वापस 0;
पूर्ण


अटल व्योम
क्रमe200e_collect_rpd(काष्ठा क्रमe200e* क्रमe200e, काष्ठा rpd* rpd)
अणु
    काष्ठा host_bsq* bsq;
    काष्ठा buffer*   buffer;
    पूर्णांक              i;
    
    क्रम (i = 0; i < rpd->nseg; i++) अणु

	/* rebuild rx buffer address from rsd handle */
	buffer = FORE200E_HDL2BUF(rpd->rsd[ i ].handle);

	bsq = &क्रमe200e->host_bsq[ buffer->scheme ][ buffer->magn ];

#अगर_घोषित FORE200E_BSQ_DEBUG
	bsq_audit(2, bsq, buffer->scheme, buffer->magn);

	अगर (buffer->supplied == 0)
	    prपूर्णांकk(FORE200E "queue %d.%d, buffer %ld was not supplied\n",
		   buffer->scheme, buffer->magn, buffer->index);
	buffer->supplied = 0;
#पूर्ण_अगर

	/* re-insert the buffer पूर्णांकo the मुक्त buffer list */
	buffer->next = bsq->मुक्तbuf;
	bsq->मुक्तbuf = buffer;

	/* then increment the number of मुक्त rx buffers */
	bsq->मुक्तbuf_count++;
    पूर्ण
पूर्ण


अटल व्योम
क्रमe200e_rx_irq(काष्ठा क्रमe200e* क्रमe200e)
अणु
    काष्ठा host_rxq*        rxq = &क्रमe200e->host_rxq;
    काष्ठा host_rxq_entry*  entry;
    काष्ठा aपंचांग_vcc*         vcc;
    काष्ठा क्रमe200e_vc_map* vc_map;

    क्रम (;;) अणु
	
	entry = &rxq->host_entry[ rxq->head ];

	/* no more received PDUs */
	अगर ((*entry->status & STATUS_COMPLETE) == 0)
	    अवरोध;

	vc_map = FORE200E_VC_MAP(क्रमe200e, entry->rpd->aपंचांग_header.vpi, entry->rpd->aपंचांग_header.vci);

	अगर ((vc_map->vcc == शून्य) ||
	    (test_bit(ATM_VF_READY, &vc_map->vcc->flags) == 0)) अणु

	    DPRINTK(1, "no ready VC found for PDU received on %d.%d.%d\n",
		    क्रमe200e->aपंचांग_dev->number,
		    entry->rpd->aपंचांग_header.vpi, entry->rpd->aपंचांग_header.vci);
	पूर्ण
	अन्यथा अणु
	    vcc = vc_map->vcc;
	    ASSERT(vcc);

	    अगर ((*entry->status & STATUS_ERROR) == 0) अणु

		क्रमe200e_push_rpd(क्रमe200e, vcc, entry->rpd);
	    पूर्ण
	    अन्यथा अणु
		DPRINTK(2, "damaged PDU on %d.%d.%d\n",
			क्रमe200e->aपंचांग_dev->number,
			entry->rpd->aपंचांग_header.vpi, entry->rpd->aपंचांग_header.vci);
		atomic_inc(&vcc->stats->rx_err);
	    पूर्ण
	पूर्ण

	FORE200E_NEXT_ENTRY(rxq->head, QUEUE_SIZE_RX);

	क्रमe200e_collect_rpd(क्रमe200e, entry->rpd);

	/* reग_लिखो the rpd address to ack the received PDU */
	क्रमe200e->bus->ग_लिखो(entry->rpd_dma, &entry->cp_entry->rpd_haddr);
	*entry->status = STATUS_FREE;

	क्रमe200e_supply(क्रमe200e);
    पूर्ण
पूर्ण


#अगर_अघोषित FORE200E_USE_TASKLET
अटल व्योम
क्रमe200e_irq(काष्ठा क्रमe200e* क्रमe200e)
अणु
    अचिन्हित दीर्घ flags;

    spin_lock_irqsave(&क्रमe200e->q_lock, flags);
    क्रमe200e_rx_irq(क्रमe200e);
    spin_unlock_irqrestore(&क्रमe200e->q_lock, flags);

    spin_lock_irqsave(&क्रमe200e->q_lock, flags);
    क्रमe200e_tx_irq(क्रमe200e);
    spin_unlock_irqrestore(&क्रमe200e->q_lock, flags);
पूर्ण
#पूर्ण_अगर


अटल irqवापस_t
क्रमe200e_पूर्णांकerrupt(पूर्णांक irq, व्योम* dev)
अणु
    काष्ठा क्रमe200e* क्रमe200e = FORE200E_DEV((काष्ठा aपंचांग_dev*)dev);

    अगर (क्रमe200e->bus->irq_check(क्रमe200e) == 0) अणु
	
	DPRINTK(3, "interrupt NOT triggered by device %d\n", क्रमe200e->aपंचांग_dev->number);
	वापस IRQ_NONE;
    पूर्ण
    DPRINTK(3, "interrupt triggered by device %d\n", क्रमe200e->aपंचांग_dev->number);

#अगर_घोषित FORE200E_USE_TASKLET
    tasklet_schedule(&क्रमe200e->tx_tasklet);
    tasklet_schedule(&क्रमe200e->rx_tasklet);
#अन्यथा
    क्रमe200e_irq(क्रमe200e);
#पूर्ण_अगर
    
    क्रमe200e->bus->irq_ack(क्रमe200e);
    वापस IRQ_HANDLED;
पूर्ण


#अगर_घोषित FORE200E_USE_TASKLET
अटल व्योम
क्रमe200e_tx_tasklet(अचिन्हित दीर्घ data)
अणु
    काष्ठा क्रमe200e* क्रमe200e = (काष्ठा क्रमe200e*) data;
    अचिन्हित दीर्घ flags;

    DPRINTK(3, "tx tasklet scheduled for device %d\n", क्रमe200e->aपंचांग_dev->number);

    spin_lock_irqsave(&क्रमe200e->q_lock, flags);
    क्रमe200e_tx_irq(क्रमe200e);
    spin_unlock_irqrestore(&क्रमe200e->q_lock, flags);
पूर्ण


अटल व्योम
क्रमe200e_rx_tasklet(अचिन्हित दीर्घ data)
अणु
    काष्ठा क्रमe200e* क्रमe200e = (काष्ठा क्रमe200e*) data;
    अचिन्हित दीर्घ    flags;

    DPRINTK(3, "rx tasklet scheduled for device %d\n", क्रमe200e->aपंचांग_dev->number);

    spin_lock_irqsave(&क्रमe200e->q_lock, flags);
    क्रमe200e_rx_irq((काष्ठा क्रमe200e*) data);
    spin_unlock_irqrestore(&क्रमe200e->q_lock, flags);
पूर्ण
#पूर्ण_अगर


अटल पूर्णांक
क्रमe200e_select_scheme(काष्ठा aपंचांग_vcc* vcc)
अणु
    /* fairly balance the VCs over (identical) buffer schemes */
    पूर्णांक scheme = vcc->vci % 2 ? BUFFER_SCHEME_ONE : BUFFER_SCHEME_TWO;

    DPRINTK(1, "VC %d.%d.%d uses buffer scheme %d\n",
	    vcc->itf, vcc->vpi, vcc->vci, scheme);

    वापस scheme;
पूर्ण


अटल पूर्णांक 
क्रमe200e_activate_vcin(काष्ठा क्रमe200e* क्रमe200e, पूर्णांक activate, काष्ठा aपंचांग_vcc* vcc, पूर्णांक mtu)
अणु
    काष्ठा host_cmdq*        cmdq  = &क्रमe200e->host_cmdq;
    काष्ठा host_cmdq_entry*  entry = &cmdq->host_entry[ cmdq->head ];
    काष्ठा activate_opcode   activ_opcode;
    काष्ठा deactivate_opcode deactiv_opcode;
    काष्ठा vpvc              vpvc;
    पूर्णांक                      ok;
    क्रमागत क्रमe200e_aal        aal = क्रमe200e_aपंचांग2क्रमe_aal(vcc->qos.aal);

    FORE200E_NEXT_ENTRY(cmdq->head, QUEUE_SIZE_CMD);
    
    अगर (activate) अणु
	FORE200E_VCC(vcc)->scheme = क्रमe200e_select_scheme(vcc);
	
	activ_opcode.opcode = OPCODE_ACTIVATE_VCIN;
	activ_opcode.aal    = aal;
	activ_opcode.scheme = FORE200E_VCC(vcc)->scheme;
	activ_opcode.pad    = 0;
    पूर्ण
    अन्यथा अणु
	deactiv_opcode.opcode = OPCODE_DEACTIVATE_VCIN;
	deactiv_opcode.pad    = 0;
    पूर्ण

    vpvc.vci = vcc->vci;
    vpvc.vpi = vcc->vpi;

    *entry->status = STATUS_PENDING;

    अगर (activate) अणु

#अगर_घोषित FORE200E_52BYTE_AAL0_SDU
	mtu = 48;
#पूर्ण_अगर
	/* the MTU is not used by the cp, except in the हाल of AAL0 */
	क्रमe200e->bus->ग_लिखो(mtu,                        &entry->cp_entry->cmd.activate_block.mtu);
	क्रमe200e->bus->ग_लिखो(*(u32*)&vpvc,         (u32 __iomem *)&entry->cp_entry->cmd.activate_block.vpvc);
	क्रमe200e->bus->ग_लिखो(*(u32*)&activ_opcode, (u32 __iomem *)&entry->cp_entry->cmd.activate_block.opcode);
    पूर्ण
    अन्यथा अणु
	क्रमe200e->bus->ग_लिखो(*(u32*)&vpvc,         (u32 __iomem *)&entry->cp_entry->cmd.deactivate_block.vpvc);
	क्रमe200e->bus->ग_लिखो(*(u32*)&deactiv_opcode, (u32 __iomem *)&entry->cp_entry->cmd.deactivate_block.opcode);
    पूर्ण

    ok = क्रमe200e_poll(क्रमe200e, entry->status, STATUS_COMPLETE, 400);

    *entry->status = STATUS_FREE;

    अगर (ok == 0) अणु
	prपूर्णांकk(FORE200E "unable to %s VC %d.%d.%d\n",
	       activate ? "open" : "close", vcc->itf, vcc->vpi, vcc->vci);
	वापस -EIO;
    पूर्ण

    DPRINTK(1, "VC %d.%d.%d %sed\n", vcc->itf, vcc->vpi, vcc->vci, 
	    activate ? "open" : "clos");

    वापस 0;
पूर्ण


#घोषणा FORE200E_MAX_BACK2BACK_CELLS 255    /* XXX depends on CDVT */

अटल व्योम
क्रमe200e_rate_ctrl(काष्ठा aपंचांग_qos* qos, काष्ठा tpd_rate* rate)
अणु
    अगर (qos->txtp.max_pcr < ATM_OC3_PCR) अणु
    
	/* compute the data cells to idle cells ratio from the tx PCR */
	rate->data_cells = qos->txtp.max_pcr * FORE200E_MAX_BACK2BACK_CELLS / ATM_OC3_PCR;
	rate->idle_cells = FORE200E_MAX_BACK2BACK_CELLS - rate->data_cells;
    पूर्ण
    अन्यथा अणु
	/* disable rate control */
	rate->data_cells = rate->idle_cells = 0;
    पूर्ण
पूर्ण


अटल पूर्णांक
क्रमe200e_खोलो(काष्ठा aपंचांग_vcc *vcc)
अणु
    काष्ठा क्रमe200e*        क्रमe200e = FORE200E_DEV(vcc->dev);
    काष्ठा क्रमe200e_vcc*    क्रमe200e_vcc;
    काष्ठा क्रमe200e_vc_map* vc_map;
    अचिन्हित दीर्घ	    flags;
    पूर्णांक			    vci = vcc->vci;
    लघु		    vpi = vcc->vpi;

    ASSERT((vpi >= 0) && (vpi < 1<<FORE200E_VPI_BITS));
    ASSERT((vci >= 0) && (vci < 1<<FORE200E_VCI_BITS));

    spin_lock_irqsave(&क्रमe200e->q_lock, flags);

    vc_map = FORE200E_VC_MAP(क्रमe200e, vpi, vci);
    अगर (vc_map->vcc) अणु

	spin_unlock_irqrestore(&क्रमe200e->q_lock, flags);

	prपूर्णांकk(FORE200E "VC %d.%d.%d already in use\n",
	       क्रमe200e->aपंचांग_dev->number, vpi, vci);

	वापस -EINVAL;
    पूर्ण

    vc_map->vcc = vcc;

    spin_unlock_irqrestore(&क्रमe200e->q_lock, flags);

    क्रमe200e_vcc = kzalloc(माप(काष्ठा क्रमe200e_vcc), GFP_ATOMIC);
    अगर (क्रमe200e_vcc == शून्य) अणु
	vc_map->vcc = शून्य;
	वापस -ENOMEM;
    पूर्ण

    DPRINTK(2, "opening %d.%d.%d:%d QoS = (tx: cl=%s, pcr=%d-%d, cdv=%d, max_sdu=%d; "
	    "rx: cl=%s, pcr=%d-%d, cdv=%d, max_sdu=%d)\n",
	    vcc->itf, vcc->vpi, vcc->vci, क्रमe200e_aपंचांग2क्रमe_aal(vcc->qos.aal),
	    क्रमe200e_traffic_class[ vcc->qos.txtp.traffic_class ],
	    vcc->qos.txtp.min_pcr, vcc->qos.txtp.max_pcr, vcc->qos.txtp.max_cdv, vcc->qos.txtp.max_sdu,
	    क्रमe200e_traffic_class[ vcc->qos.rxtp.traffic_class ],
	    vcc->qos.rxtp.min_pcr, vcc->qos.rxtp.max_pcr, vcc->qos.rxtp.max_cdv, vcc->qos.rxtp.max_sdu);
    
    /* pseuकरो-CBR bandwidth requested? */
    अगर ((vcc->qos.txtp.traffic_class == ATM_CBR) && (vcc->qos.txtp.max_pcr > 0)) अणु
	
	mutex_lock(&क्रमe200e->rate_mtx);
	अगर (क्रमe200e->available_cell_rate < vcc->qos.txtp.max_pcr) अणु
	    mutex_unlock(&क्रमe200e->rate_mtx);

	    kमुक्त(क्रमe200e_vcc);
	    vc_map->vcc = शून्य;
	    वापस -EAGAIN;
	पूर्ण

	/* reserve bandwidth */
	क्रमe200e->available_cell_rate -= vcc->qos.txtp.max_pcr;
	mutex_unlock(&क्रमe200e->rate_mtx);
    पूर्ण
    
    vcc->itf = vcc->dev->number;

    set_bit(ATM_VF_PARTIAL,&vcc->flags);
    set_bit(ATM_VF_ADDR, &vcc->flags);

    vcc->dev_data = क्रमe200e_vcc;
    
    अगर (क्रमe200e_activate_vcin(क्रमe200e, 1, vcc, vcc->qos.rxtp.max_sdu) < 0) अणु

	vc_map->vcc = शून्य;

	clear_bit(ATM_VF_ADDR, &vcc->flags);
	clear_bit(ATM_VF_PARTIAL,&vcc->flags);

	vcc->dev_data = शून्य;

	क्रमe200e->available_cell_rate += vcc->qos.txtp.max_pcr;

	kमुक्त(क्रमe200e_vcc);
	वापस -EINVAL;
    पूर्ण
    
    /* compute rate control parameters */
    अगर ((vcc->qos.txtp.traffic_class == ATM_CBR) && (vcc->qos.txtp.max_pcr > 0)) अणु
	
	क्रमe200e_rate_ctrl(&vcc->qos, &क्रमe200e_vcc->rate);
	set_bit(ATM_VF_HASQOS, &vcc->flags);

	DPRINTK(3, "tx on %d.%d.%d:%d, tx PCR = %d, rx PCR = %d, data_cells = %u, idle_cells = %u\n",
		vcc->itf, vcc->vpi, vcc->vci, क्रमe200e_aपंचांग2क्रमe_aal(vcc->qos.aal),
		vcc->qos.txtp.max_pcr, vcc->qos.rxtp.max_pcr, 
		क्रमe200e_vcc->rate.data_cells, क्रमe200e_vcc->rate.idle_cells);
    पूर्ण
    
    क्रमe200e_vcc->tx_min_pdu = क्रमe200e_vcc->rx_min_pdu = MAX_PDU_SIZE + 1;
    क्रमe200e_vcc->tx_max_pdu = क्रमe200e_vcc->rx_max_pdu = 0;
    क्रमe200e_vcc->tx_pdu     = क्रमe200e_vcc->rx_pdu     = 0;

    /* new incarnation of the vcc */
    vc_map->incarn = ++क्रमe200e->incarn_count;

    /* VC unusable beक्रमe this flag is set */
    set_bit(ATM_VF_READY, &vcc->flags);

    वापस 0;
पूर्ण


अटल व्योम
क्रमe200e_बंद(काष्ठा aपंचांग_vcc* vcc)
अणु
    काष्ठा क्रमe200e_vcc*    क्रमe200e_vcc;
    काष्ठा क्रमe200e*        क्रमe200e;
    काष्ठा क्रमe200e_vc_map* vc_map;
    अचिन्हित दीर्घ           flags;

    ASSERT(vcc);
    क्रमe200e = FORE200E_DEV(vcc->dev);

    ASSERT((vcc->vpi >= 0) && (vcc->vpi < 1<<FORE200E_VPI_BITS));
    ASSERT((vcc->vci >= 0) && (vcc->vci < 1<<FORE200E_VCI_BITS));

    DPRINTK(2, "closing %d.%d.%d:%d\n", vcc->itf, vcc->vpi, vcc->vci, क्रमe200e_aपंचांग2क्रमe_aal(vcc->qos.aal));

    clear_bit(ATM_VF_READY, &vcc->flags);

    क्रमe200e_activate_vcin(क्रमe200e, 0, vcc, 0);

    spin_lock_irqsave(&क्रमe200e->q_lock, flags);

    vc_map = FORE200E_VC_MAP(क्रमe200e, vcc->vpi, vcc->vci);

    /* the vc is no दीर्घer considered as "in use" by क्रमe200e_खोलो() */
    vc_map->vcc = शून्य;

    vcc->itf = vcc->vci = vcc->vpi = 0;

    क्रमe200e_vcc = FORE200E_VCC(vcc);
    vcc->dev_data = शून्य;

    spin_unlock_irqrestore(&क्रमe200e->q_lock, flags);

    /* release reserved bandwidth, अगर any */
    अगर ((vcc->qos.txtp.traffic_class == ATM_CBR) && (vcc->qos.txtp.max_pcr > 0)) अणु

	mutex_lock(&क्रमe200e->rate_mtx);
	क्रमe200e->available_cell_rate += vcc->qos.txtp.max_pcr;
	mutex_unlock(&क्रमe200e->rate_mtx);

	clear_bit(ATM_VF_HASQOS, &vcc->flags);
    पूर्ण

    clear_bit(ATM_VF_ADDR, &vcc->flags);
    clear_bit(ATM_VF_PARTIAL,&vcc->flags);

    ASSERT(क्रमe200e_vcc);
    kमुक्त(क्रमe200e_vcc);
पूर्ण


अटल पूर्णांक
क्रमe200e_send(काष्ठा aपंचांग_vcc *vcc, काष्ठा sk_buff *skb)
अणु
    काष्ठा क्रमe200e*        क्रमe200e;
    काष्ठा क्रमe200e_vcc*    क्रमe200e_vcc;
    काष्ठा क्रमe200e_vc_map* vc_map;
    काष्ठा host_txq*        txq;
    काष्ठा host_txq_entry*  entry;
    काष्ठा tpd*             tpd;
    काष्ठा tpd_haddr        tpd_haddr;
    पूर्णांक                     retry        = CONFIG_ATM_FORE200E_TX_RETRY;
    पूर्णांक                     tx_copy      = 0;
    पूर्णांक                     tx_len       = skb->len;
    u32*                    cell_header  = शून्य;
    अचिन्हित अक्षर*          skb_data;
    पूर्णांक                     skb_len;
    अचिन्हित अक्षर*          data;
    अचिन्हित दीर्घ           flags;

    अगर (!vcc)
        वापस -EINVAL;

    क्रमe200e = FORE200E_DEV(vcc->dev);
    क्रमe200e_vcc = FORE200E_VCC(vcc);

    अगर (!क्रमe200e)
        वापस -EINVAL;

    txq = &क्रमe200e->host_txq;
    अगर (!क्रमe200e_vcc)
        वापस -EINVAL;

    अगर (!test_bit(ATM_VF_READY, &vcc->flags)) अणु
	DPRINTK(1, "VC %d.%d.%d not ready for tx\n", vcc->itf, vcc->vpi, vcc->vpi);
	dev_kमुक्त_skb_any(skb);
	वापस -EINVAL;
    पूर्ण

#अगर_घोषित FORE200E_52BYTE_AAL0_SDU
    अगर ((vcc->qos.aal == ATM_AAL0) && (vcc->qos.txtp.max_sdu == ATM_AAL0_SDU)) अणु
	cell_header = (u32*) skb->data;
	skb_data    = skb->data + 4;    /* skip 4-byte cell header */
	skb_len     = tx_len = skb->len  - 4;

	DPRINTK(3, "user-supplied cell header = 0x%08x\n", *cell_header);
    पूर्ण
    अन्यथा 
#पूर्ण_अगर
    अणु
	skb_data = skb->data;
	skb_len  = skb->len;
    पूर्ण
    
    अगर (((अचिन्हित दीर्घ)skb_data) & 0x3) अणु

	DPRINTK(2, "misaligned tx PDU on device %s\n", क्रमe200e->name);
	tx_copy = 1;
	tx_len  = skb_len;
    पूर्ण

    अगर ((vcc->qos.aal == ATM_AAL0) && (skb_len % ATM_CELL_PAYLOAD)) अणु

        /* this simply NUKES the PCA board */
	DPRINTK(2, "incomplete tx AAL0 PDU on device %s\n", क्रमe200e->name);
	tx_copy = 1;
	tx_len  = ((skb_len / ATM_CELL_PAYLOAD) + 1) * ATM_CELL_PAYLOAD;
    पूर्ण
    
    अगर (tx_copy) अणु
	data = kदो_स्मृति(tx_len, GFP_ATOMIC);
	अगर (data == शून्य) अणु
	    अगर (vcc->pop) अणु
		vcc->pop(vcc, skb);
	    पूर्ण
	    अन्यथा अणु
		dev_kमुक्त_skb_any(skb);
	    पूर्ण
	    वापस -ENOMEM;
	पूर्ण

	स_नकल(data, skb_data, skb_len);
	अगर (skb_len < tx_len)
	    स_रखो(data + skb_len, 0x00, tx_len - skb_len);
    पूर्ण
    अन्यथा अणु
	data = skb_data;
    पूर्ण

    vc_map = FORE200E_VC_MAP(क्रमe200e, vcc->vpi, vcc->vci);
    ASSERT(vc_map->vcc == vcc);

  retry_here:

    spin_lock_irqsave(&क्रमe200e->q_lock, flags);

    entry = &txq->host_entry[ txq->head ];

    अगर ((*entry->status != STATUS_FREE) || (txq->txing >= QUEUE_SIZE_TX - 2)) अणु

	/* try to मुक्त completed tx queue entries */
	क्रमe200e_tx_irq(क्रमe200e);

	अगर (*entry->status != STATUS_FREE) अणु

	    spin_unlock_irqrestore(&क्रमe200e->q_lock, flags);

	    /* retry once again? */
	    अगर (--retry > 0) अणु
		udelay(50);
		जाओ retry_here;
	    पूर्ण

	    atomic_inc(&vcc->stats->tx_err);

	    क्रमe200e->tx_sat++;
	    DPRINTK(2, "tx queue of device %s is saturated, PDU dropped - heartbeat is %08x\n",
		    क्रमe200e->name, क्रमe200e->cp_queues->heartbeat);
	    अगर (vcc->pop) अणु
		vcc->pop(vcc, skb);
	    पूर्ण
	    अन्यथा अणु
		dev_kमुक्त_skb_any(skb);
	    पूर्ण

	    अगर (tx_copy)
		kमुक्त(data);

	    वापस -ENOBUFS;
	पूर्ण
    पूर्ण

    entry->incarn = vc_map->incarn;
    entry->vc_map = vc_map;
    entry->skb    = skb;
    entry->data   = tx_copy ? data : शून्य;

    tpd = entry->tpd;
    tpd->tsd[ 0 ].buffer = dma_map_single(क्रमe200e->dev, data, tx_len,
					  DMA_TO_DEVICE);
    अगर (dma_mapping_error(क्रमe200e->dev, tpd->tsd[0].buffer)) अणु
	अगर (tx_copy)
	    kमुक्त(data);
	spin_unlock_irqrestore(&क्रमe200e->q_lock, flags);
	वापस -ENOMEM;
    पूर्ण
    tpd->tsd[ 0 ].length = tx_len;

    FORE200E_NEXT_ENTRY(txq->head, QUEUE_SIZE_TX);
    txq->txing++;

    /* The dma_map call above implies a dma_sync so the device can use it,
     * thus no explicit dma_sync call is necessary here.
     */
    
    DPRINTK(3, "tx on %d.%d.%d:%d, len = %u (%u)\n", 
	    vcc->itf, vcc->vpi, vcc->vci, क्रमe200e_aपंचांग2क्रमe_aal(vcc->qos.aal),
	    tpd->tsd[0].length, skb_len);

    अगर (skb_len < क्रमe200e_vcc->tx_min_pdu)
	क्रमe200e_vcc->tx_min_pdu = skb_len;
    अगर (skb_len > क्रमe200e_vcc->tx_max_pdu)
	क्रमe200e_vcc->tx_max_pdu = skb_len;
    क्रमe200e_vcc->tx_pdu++;

    /* set tx rate control inक्रमmation */
    tpd->rate.data_cells = क्रमe200e_vcc->rate.data_cells;
    tpd->rate.idle_cells = क्रमe200e_vcc->rate.idle_cells;

    अगर (cell_header) अणु
	tpd->aपंचांग_header.clp = (*cell_header & ATM_HDR_CLP);
	tpd->aपंचांग_header.plt = (*cell_header & ATM_HDR_PTI_MASK) >> ATM_HDR_PTI_SHIFT;
	tpd->aपंचांग_header.vci = (*cell_header & ATM_HDR_VCI_MASK) >> ATM_HDR_VCI_SHIFT;
	tpd->aपंचांग_header.vpi = (*cell_header & ATM_HDR_VPI_MASK) >> ATM_HDR_VPI_SHIFT;
	tpd->aपंचांग_header.gfc = (*cell_header & ATM_HDR_GFC_MASK) >> ATM_HDR_GFC_SHIFT;
    पूर्ण
    अन्यथा अणु
	/* set the ATM header, common to all cells conveying the PDU */
	tpd->aपंचांग_header.clp = 0;
	tpd->aपंचांग_header.plt = 0;
	tpd->aपंचांग_header.vci = vcc->vci;
	tpd->aपंचांग_header.vpi = vcc->vpi;
	tpd->aपंचांग_header.gfc = 0;
    पूर्ण

    tpd->spec.length = tx_len;
    tpd->spec.nseg   = 1;
    tpd->spec.aal    = क्रमe200e_aपंचांग2क्रमe_aal(vcc->qos.aal);
    tpd->spec.पूर्णांकr   = 1;

    tpd_haddr.size  = माप(काष्ठा tpd) / (1<<TPD_HADDR_SHIFT);  /* size is expressed in 32 byte blocks */
    tpd_haddr.pad   = 0;
    tpd_haddr.haddr = entry->tpd_dma >> TPD_HADDR_SHIFT;          /* shअगरt the address, as we are in a bitfield */

    *entry->status = STATUS_PENDING;
    क्रमe200e->bus->ग_लिखो(*(u32*)&tpd_haddr, (u32 __iomem *)&entry->cp_entry->tpd_haddr);

    spin_unlock_irqrestore(&क्रमe200e->q_lock, flags);

    वापस 0;
पूर्ण


अटल पूर्णांक
क्रमe200e_माला_लोtats(काष्ठा क्रमe200e* क्रमe200e)
अणु
    काष्ठा host_cmdq*       cmdq  = &क्रमe200e->host_cmdq;
    काष्ठा host_cmdq_entry* entry = &cmdq->host_entry[ cmdq->head ];
    काष्ठा stats_opcode     opcode;
    पूर्णांक                     ok;
    u32                     stats_dma_addr;

    अगर (क्रमe200e->stats == शून्य) अणु
	क्रमe200e->stats = kzalloc(माप(काष्ठा stats), GFP_KERNEL);
	अगर (क्रमe200e->stats == शून्य)
	    वापस -ENOMEM;
    पूर्ण
    
    stats_dma_addr = dma_map_single(क्रमe200e->dev, क्रमe200e->stats,
				    माप(काष्ठा stats), DMA_FROM_DEVICE);
    अगर (dma_mapping_error(क्रमe200e->dev, stats_dma_addr))
    	वापस -ENOMEM;
    
    FORE200E_NEXT_ENTRY(cmdq->head, QUEUE_SIZE_CMD);

    opcode.opcode = OPCODE_GET_STATS;
    opcode.pad    = 0;

    क्रमe200e->bus->ग_लिखो(stats_dma_addr, &entry->cp_entry->cmd.stats_block.stats_haddr);
    
    *entry->status = STATUS_PENDING;

    क्रमe200e->bus->ग_लिखो(*(u32*)&opcode, (u32 __iomem *)&entry->cp_entry->cmd.stats_block.opcode);

    ok = क्रमe200e_poll(क्रमe200e, entry->status, STATUS_COMPLETE, 400);

    *entry->status = STATUS_FREE;

    dma_unmap_single(क्रमe200e->dev, stats_dma_addr, माप(काष्ठा stats), DMA_FROM_DEVICE);
    
    अगर (ok == 0) अणु
	prपूर्णांकk(FORE200E "unable to get statistics from device %s\n", क्रमe200e->name);
	वापस -EIO;
    पूर्ण

    वापस 0;
पूर्ण

#अगर 0 /* currently unused */
अटल पूर्णांक
क्रमe200e_get_oc3(काष्ठा क्रमe200e* क्रमe200e, काष्ठा oc3_regs* regs)
अणु
    काष्ठा host_cmdq*       cmdq  = &क्रमe200e->host_cmdq;
    काष्ठा host_cmdq_entry* entry = &cmdq->host_entry[ cmdq->head ];
    काष्ठा oc3_opcode       opcode;
    पूर्णांक                     ok;
    u32                     oc3_regs_dma_addr;

    oc3_regs_dma_addr = क्रमe200e->bus->dma_map(क्रमe200e, regs, माप(काष्ठा oc3_regs), DMA_FROM_DEVICE);

    FORE200E_NEXT_ENTRY(cmdq->head, QUEUE_SIZE_CMD);

    opcode.opcode = OPCODE_GET_OC3;
    opcode.reg    = 0;
    opcode.value  = 0;
    opcode.mask   = 0;

    क्रमe200e->bus->ग_लिखो(oc3_regs_dma_addr, &entry->cp_entry->cmd.oc3_block.regs_haddr);
    
    *entry->status = STATUS_PENDING;

    क्रमe200e->bus->ग_लिखो(*(u32*)&opcode, (u32*)&entry->cp_entry->cmd.oc3_block.opcode);

    ok = क्रमe200e_poll(क्रमe200e, entry->status, STATUS_COMPLETE, 400);

    *entry->status = STATUS_FREE;

    क्रमe200e->bus->dma_unmap(क्रमe200e, oc3_regs_dma_addr, माप(काष्ठा oc3_regs), DMA_FROM_DEVICE);
    
    अगर (ok == 0) अणु
	prपूर्णांकk(FORE200E "unable to get OC-3 regs of device %s\n", क्रमe200e->name);
	वापस -EIO;
    पूर्ण

    वापस 0;
पूर्ण
#पूर्ण_अगर


अटल पूर्णांक
क्रमe200e_set_oc3(काष्ठा क्रमe200e* क्रमe200e, u32 reg, u32 value, u32 mask)
अणु
    काष्ठा host_cmdq*       cmdq  = &क्रमe200e->host_cmdq;
    काष्ठा host_cmdq_entry* entry = &cmdq->host_entry[ cmdq->head ];
    काष्ठा oc3_opcode       opcode;
    पूर्णांक                     ok;

    DPRINTK(2, "set OC-3 reg = 0x%02x, value = 0x%02x, mask = 0x%02x\n", reg, value, mask);

    FORE200E_NEXT_ENTRY(cmdq->head, QUEUE_SIZE_CMD);

    opcode.opcode = OPCODE_SET_OC3;
    opcode.reg    = reg;
    opcode.value  = value;
    opcode.mask   = mask;

    क्रमe200e->bus->ग_लिखो(0, &entry->cp_entry->cmd.oc3_block.regs_haddr);
    
    *entry->status = STATUS_PENDING;

    क्रमe200e->bus->ग_लिखो(*(u32*)&opcode, (u32 __iomem *)&entry->cp_entry->cmd.oc3_block.opcode);

    ok = क्रमe200e_poll(क्रमe200e, entry->status, STATUS_COMPLETE, 400);

    *entry->status = STATUS_FREE;

    अगर (ok == 0) अणु
	prपूर्णांकk(FORE200E "unable to set OC-3 reg 0x%02x of device %s\n", reg, क्रमe200e->name);
	वापस -EIO;
    पूर्ण

    वापस 0;
पूर्ण


अटल पूर्णांक
क्रमe200e_setloop(काष्ठा क्रमe200e* क्रमe200e, पूर्णांक loop_mode)
अणु
    u32 mct_value, mct_mask;
    पूर्णांक error;

    अगर (!capable(CAP_NET_ADMIN))
	वापस -EPERM;
    
    चयन (loop_mode) अणु

    हाल ATM_LM_NONE:
	mct_value = 0; 
	mct_mask  = SUNI_MCT_DLE | SUNI_MCT_LLE;
	अवरोध;
	
    हाल ATM_LM_LOC_PHY:
	mct_value = mct_mask = SUNI_MCT_DLE;
	अवरोध;

    हाल ATM_LM_RMT_PHY:
	mct_value = mct_mask = SUNI_MCT_LLE;
	अवरोध;

    शेष:
	वापस -EINVAL;
    पूर्ण

    error = क्रमe200e_set_oc3(क्रमe200e, SUNI_MCT, mct_value, mct_mask);
    अगर (error == 0)
	क्रमe200e->loop_mode = loop_mode;

    वापस error;
पूर्ण


अटल पूर्णांक
क्रमe200e_fetch_stats(काष्ठा क्रमe200e* क्रमe200e, काष्ठा sonet_stats __user *arg)
अणु
    काष्ठा sonet_stats पंचांगp;

    अगर (क्रमe200e_माला_लोtats(क्रमe200e) < 0)
	वापस -EIO;

    पंचांगp.section_bip = be32_to_cpu(क्रमe200e->stats->oc3.section_bip8_errors);
    पंचांगp.line_bip    = be32_to_cpu(क्रमe200e->stats->oc3.line_bip24_errors);
    पंचांगp.path_bip    = be32_to_cpu(क्रमe200e->stats->oc3.path_bip8_errors);
    पंचांगp.line_febe   = be32_to_cpu(क्रमe200e->stats->oc3.line_febe_errors);
    पंचांगp.path_febe   = be32_to_cpu(क्रमe200e->stats->oc3.path_febe_errors);
    पंचांगp.corr_hcs    = be32_to_cpu(क्रमe200e->stats->oc3.corr_hcs_errors);
    पंचांगp.uncorr_hcs  = be32_to_cpu(क्रमe200e->stats->oc3.ucorr_hcs_errors);
    पंचांगp.tx_cells    = be32_to_cpu(क्रमe200e->stats->aal0.cells_transmitted)  +
	              be32_to_cpu(क्रमe200e->stats->aal34.cells_transmitted) +
	              be32_to_cpu(क्रमe200e->stats->aal5.cells_transmitted);
    पंचांगp.rx_cells    = be32_to_cpu(क्रमe200e->stats->aal0.cells_received)     +
	              be32_to_cpu(क्रमe200e->stats->aal34.cells_received)    +
	              be32_to_cpu(क्रमe200e->stats->aal5.cells_received);

    अगर (arg)
	वापस copy_to_user(arg, &पंचांगp, माप(काष्ठा sonet_stats)) ? -EFAULT : 0;	
    
    वापस 0;
पूर्ण


अटल पूर्णांक
क्रमe200e_ioctl(काष्ठा aपंचांग_dev* dev, अचिन्हित पूर्णांक cmd, व्योम __user * arg)
अणु
    काष्ठा क्रमe200e* क्रमe200e = FORE200E_DEV(dev);
    
    DPRINTK(2, "ioctl cmd = 0x%x (%u), arg = 0x%p (%lu)\n", cmd, cmd, arg, (अचिन्हित दीर्घ)arg);

    चयन (cmd) अणु

    हाल SONET_GETSTAT:
	वापस क्रमe200e_fetch_stats(क्रमe200e, (काष्ठा sonet_stats __user *)arg);

    हाल SONET_GETDIAG:
	वापस put_user(0, (पूर्णांक __user *)arg) ? -EFAULT : 0;

    हाल ATM_SETLOOP:
	वापस क्रमe200e_setloop(क्रमe200e, (पूर्णांक)(अचिन्हित दीर्घ)arg);

    हाल ATM_GETLOOP:
	वापस put_user(क्रमe200e->loop_mode, (पूर्णांक __user *)arg) ? -EFAULT : 0;

    हाल ATM_QUERYLOOP:
	वापस put_user(ATM_LM_LOC_PHY | ATM_LM_RMT_PHY, (पूर्णांक __user *)arg) ? -EFAULT : 0;
    पूर्ण

    वापस -ENOSYS; /* not implemented */
पूर्ण


अटल पूर्णांक
क्रमe200e_change_qos(काष्ठा aपंचांग_vcc* vcc,काष्ठा aपंचांग_qos* qos, पूर्णांक flags)
अणु
    काष्ठा क्रमe200e_vcc* क्रमe200e_vcc = FORE200E_VCC(vcc);
    काष्ठा क्रमe200e*     क्रमe200e     = FORE200E_DEV(vcc->dev);

    अगर (!test_bit(ATM_VF_READY, &vcc->flags)) अणु
	DPRINTK(1, "VC %d.%d.%d not ready for QoS change\n", vcc->itf, vcc->vpi, vcc->vpi);
	वापस -EINVAL;
    पूर्ण

    DPRINTK(2, "change_qos %d.%d.%d, "
	    "(tx: cl=%s, pcr=%d-%d, cdv=%d, max_sdu=%d; "
	    "rx: cl=%s, pcr=%d-%d, cdv=%d, max_sdu=%d), flags = 0x%x\n"
	    "available_cell_rate = %u",
	    vcc->itf, vcc->vpi, vcc->vci,
	    क्रमe200e_traffic_class[ qos->txtp.traffic_class ],
	    qos->txtp.min_pcr, qos->txtp.max_pcr, qos->txtp.max_cdv, qos->txtp.max_sdu,
	    क्रमe200e_traffic_class[ qos->rxtp.traffic_class ],
	    qos->rxtp.min_pcr, qos->rxtp.max_pcr, qos->rxtp.max_cdv, qos->rxtp.max_sdu,
	    flags, क्रमe200e->available_cell_rate);

    अगर ((qos->txtp.traffic_class == ATM_CBR) && (qos->txtp.max_pcr > 0)) अणु

	mutex_lock(&क्रमe200e->rate_mtx);
	अगर (क्रमe200e->available_cell_rate + vcc->qos.txtp.max_pcr < qos->txtp.max_pcr) अणु
	    mutex_unlock(&क्रमe200e->rate_mtx);
	    वापस -EAGAIN;
	पूर्ण

	क्रमe200e->available_cell_rate += vcc->qos.txtp.max_pcr;
	क्रमe200e->available_cell_rate -= qos->txtp.max_pcr;

	mutex_unlock(&क्रमe200e->rate_mtx);
	
	स_नकल(&vcc->qos, qos, माप(काष्ठा aपंचांग_qos));
	
	/* update rate control parameters */
	क्रमe200e_rate_ctrl(qos, &क्रमe200e_vcc->rate);

	set_bit(ATM_VF_HASQOS, &vcc->flags);

	वापस 0;
    पूर्ण
    
    वापस -EINVAL;
पूर्ण
    

अटल पूर्णांक क्रमe200e_irq_request(काष्ठा क्रमe200e *क्रमe200e)
अणु
    अगर (request_irq(क्रमe200e->irq, क्रमe200e_पूर्णांकerrupt, IRQF_SHARED, क्रमe200e->name, क्रमe200e->aपंचांग_dev) < 0) अणु

	prपूर्णांकk(FORE200E "unable to reserve IRQ %s for device %s\n",
	       क्रमe200e_irq_itoa(क्रमe200e->irq), क्रमe200e->name);
	वापस -EBUSY;
    पूर्ण

    prपूर्णांकk(FORE200E "IRQ %s reserved for device %s\n",
	   क्रमe200e_irq_itoa(क्रमe200e->irq), क्रमe200e->name);

#अगर_घोषित FORE200E_USE_TASKLET
    tasklet_init(&क्रमe200e->tx_tasklet, क्रमe200e_tx_tasklet, (अचिन्हित दीर्घ)क्रमe200e);
    tasklet_init(&क्रमe200e->rx_tasklet, क्रमe200e_rx_tasklet, (अचिन्हित दीर्घ)क्रमe200e);
#पूर्ण_अगर

    क्रमe200e->state = FORE200E_STATE_IRQ;
    वापस 0;
पूर्ण


अटल पूर्णांक क्रमe200e_get_esi(काष्ठा क्रमe200e *क्रमe200e)
अणु
    काष्ठा prom_data* prom = kzalloc(माप(काष्ठा prom_data), GFP_KERNEL);
    पूर्णांक ok, i;

    अगर (!prom)
	वापस -ENOMEM;

    ok = क्रमe200e->bus->prom_पढ़ो(क्रमe200e, prom);
    अगर (ok < 0) अणु
	kमुक्त(prom);
	वापस -EBUSY;
    पूर्ण
	
    prपूर्णांकk(FORE200E "device %s, rev. %c, S/N: %d, ESI: %pM\n",
	   क्रमe200e->name, 
	   (prom->hw_revision & 0xFF) + '@',    /* probably meaningless with SBA boards */
	   prom->serial_number & 0xFFFF, &prom->mac_addr[2]);
	
    क्रम (i = 0; i < ESI_LEN; i++) अणु
	क्रमe200e->esi[ i ] = क्रमe200e->aपंचांग_dev->esi[ i ] = prom->mac_addr[ i + 2 ];
    पूर्ण
    
    kमुक्त(prom);

    वापस 0;
पूर्ण


अटल पूर्णांक क्रमe200e_alloc_rx_buf(काष्ठा क्रमe200e *क्रमe200e)
अणु
    पूर्णांक scheme, magn, nbr, size, i;

    काष्ठा host_bsq* bsq;
    काष्ठा buffer*   buffer;

    क्रम (scheme = 0; scheme < BUFFER_SCHEME_NBR; scheme++) अणु
	क्रम (magn = 0; magn < BUFFER_MAGN_NBR; magn++) अणु

	    bsq = &क्रमe200e->host_bsq[ scheme ][ magn ];

	    nbr  = क्रमe200e_rx_buf_nbr[ scheme ][ magn ];
	    size = क्रमe200e_rx_buf_size[ scheme ][ magn ];

	    DPRINTK(2, "rx buffers %d / %d are being allocated\n", scheme, magn);

	    /* allocate the array of receive buffers */
	    buffer = bsq->buffer = kसुस्मृति(nbr, माप(काष्ठा buffer),
                                           GFP_KERNEL);

	    अगर (buffer == शून्य)
		वापस -ENOMEM;

	    bsq->मुक्तbuf = शून्य;

	    क्रम (i = 0; i < nbr; i++) अणु

		buffer[ i ].scheme = scheme;
		buffer[ i ].magn   = magn;
#अगर_घोषित FORE200E_BSQ_DEBUG
		buffer[ i ].index  = i;
		buffer[ i ].supplied = 0;
#पूर्ण_अगर

		/* allocate the receive buffer body */
		अगर (क्रमe200e_chunk_alloc(क्रमe200e,
					 &buffer[ i ].data, size, क्रमe200e->bus->buffer_alignment,
					 DMA_FROM_DEVICE) < 0) अणु
		    
		    जबतक (i > 0)
			क्रमe200e_chunk_मुक्त(क्रमe200e, &buffer[ --i ].data);
		    kमुक्त(buffer);
		    
		    वापस -ENOMEM;
		पूर्ण

		/* insert the buffer पूर्णांकo the मुक्त buffer list */
		buffer[ i ].next = bsq->मुक्तbuf;
		bsq->मुक्तbuf = &buffer[ i ];
	    पूर्ण
	    /* all the buffers are मुक्त, initially */
	    bsq->मुक्तbuf_count = nbr;

#अगर_घोषित FORE200E_BSQ_DEBUG
	    bsq_audit(3, bsq, scheme, magn);
#पूर्ण_अगर
	पूर्ण
    पूर्ण

    क्रमe200e->state = FORE200E_STATE_ALLOC_BUF;
    वापस 0;
पूर्ण


अटल पूर्णांक क्रमe200e_init_bs_queue(काष्ठा क्रमe200e *क्रमe200e)
अणु
    पूर्णांक scheme, magn, i;

    काष्ठा host_bsq*     bsq;
    काष्ठा cp_bsq_entry __iomem * cp_entry;

    क्रम (scheme = 0; scheme < BUFFER_SCHEME_NBR; scheme++) अणु
	क्रम (magn = 0; magn < BUFFER_MAGN_NBR; magn++) अणु

	    DPRINTK(2, "buffer supply queue %d / %d is being initialized\n", scheme, magn);

	    bsq = &क्रमe200e->host_bsq[ scheme ][ magn ];

	    /* allocate and align the array of status words */
	    अगर (क्रमe200e_dma_chunk_alloc(क्रमe200e,
					       &bsq->status,
					       माप(क्रमागत status), 
					       QUEUE_SIZE_BS,
					       क्रमe200e->bus->status_alignment) < 0) अणु
		वापस -ENOMEM;
	    पूर्ण

	    /* allocate and align the array of receive buffer descriptors */
	    अगर (क्रमe200e_dma_chunk_alloc(क्रमe200e,
					       &bsq->rbd_block,
					       माप(काष्ठा rbd_block),
					       QUEUE_SIZE_BS,
					       क्रमe200e->bus->descr_alignment) < 0) अणु
		
		क्रमe200e_dma_chunk_मुक्त(क्रमe200e, &bsq->status);
		वापस -ENOMEM;
	    पूर्ण
	    
	    /* get the base address of the cp resident buffer supply queue entries */
	    cp_entry = क्रमe200e->virt_base + 
		       क्रमe200e->bus->पढ़ो(&क्रमe200e->cp_queues->cp_bsq[ scheme ][ magn ]);
	    
	    /* fill the host resident and cp resident buffer supply queue entries */
	    क्रम (i = 0; i < QUEUE_SIZE_BS; i++) अणु
		
		bsq->host_entry[ i ].status = 
		                     FORE200E_INDEX(bsq->status.align_addr, क्रमागत status, i);
	        bsq->host_entry[ i ].rbd_block =
		                     FORE200E_INDEX(bsq->rbd_block.align_addr, काष्ठा rbd_block, i);
		bsq->host_entry[ i ].rbd_block_dma =
		                     FORE200E_DMA_INDEX(bsq->rbd_block.dma_addr, काष्ठा rbd_block, i);
		bsq->host_entry[ i ].cp_entry = &cp_entry[ i ];
		
		*bsq->host_entry[ i ].status = STATUS_FREE;
		
		क्रमe200e->bus->ग_लिखो(FORE200E_DMA_INDEX(bsq->status.dma_addr, क्रमागत status, i), 
				     &cp_entry[ i ].status_haddr);
	    पूर्ण
	पूर्ण
    पूर्ण

    क्रमe200e->state = FORE200E_STATE_INIT_BSQ;
    वापस 0;
पूर्ण


अटल पूर्णांक क्रमe200e_init_rx_queue(काष्ठा क्रमe200e *क्रमe200e)
अणु
    काष्ठा host_rxq*     rxq =  &क्रमe200e->host_rxq;
    काष्ठा cp_rxq_entry __iomem * cp_entry;
    पूर्णांक i;

    DPRINTK(2, "receive queue is being initialized\n");

    /* allocate and align the array of status words */
    अगर (क्रमe200e_dma_chunk_alloc(क्रमe200e,
				       &rxq->status,
				       माप(क्रमागत status), 
				       QUEUE_SIZE_RX,
				       क्रमe200e->bus->status_alignment) < 0) अणु
	वापस -ENOMEM;
    पूर्ण

    /* allocate and align the array of receive PDU descriptors */
    अगर (क्रमe200e_dma_chunk_alloc(क्रमe200e,
				       &rxq->rpd,
				       माप(काष्ठा rpd), 
				       QUEUE_SIZE_RX,
				       क्रमe200e->bus->descr_alignment) < 0) अणु
	
	क्रमe200e_dma_chunk_मुक्त(क्रमe200e, &rxq->status);
	वापस -ENOMEM;
    पूर्ण

    /* get the base address of the cp resident rx queue entries */
    cp_entry = क्रमe200e->virt_base + क्रमe200e->bus->पढ़ो(&क्रमe200e->cp_queues->cp_rxq);

    /* fill the host resident and cp resident rx entries */
    क्रम (i=0; i < QUEUE_SIZE_RX; i++) अणु
	
	rxq->host_entry[ i ].status = 
	                     FORE200E_INDEX(rxq->status.align_addr, क्रमागत status, i);
	rxq->host_entry[ i ].rpd = 
	                     FORE200E_INDEX(rxq->rpd.align_addr, काष्ठा rpd, i);
	rxq->host_entry[ i ].rpd_dma = 
	                     FORE200E_DMA_INDEX(rxq->rpd.dma_addr, काष्ठा rpd, i);
	rxq->host_entry[ i ].cp_entry = &cp_entry[ i ];

	*rxq->host_entry[ i ].status = STATUS_FREE;

	क्रमe200e->bus->ग_लिखो(FORE200E_DMA_INDEX(rxq->status.dma_addr, क्रमागत status, i), 
			     &cp_entry[ i ].status_haddr);

	क्रमe200e->bus->ग_लिखो(FORE200E_DMA_INDEX(rxq->rpd.dma_addr, काष्ठा rpd, i),
			     &cp_entry[ i ].rpd_haddr);
    पूर्ण

    /* set the head entry of the queue */
    rxq->head = 0;

    क्रमe200e->state = FORE200E_STATE_INIT_RXQ;
    वापस 0;
पूर्ण


अटल पूर्णांक क्रमe200e_init_tx_queue(काष्ठा क्रमe200e *क्रमe200e)
अणु
    काष्ठा host_txq*     txq =  &क्रमe200e->host_txq;
    काष्ठा cp_txq_entry __iomem * cp_entry;
    पूर्णांक i;

    DPRINTK(2, "transmit queue is being initialized\n");

    /* allocate and align the array of status words */
    अगर (क्रमe200e_dma_chunk_alloc(क्रमe200e,
				       &txq->status,
				       माप(क्रमागत status), 
				       QUEUE_SIZE_TX,
				       क्रमe200e->bus->status_alignment) < 0) अणु
	वापस -ENOMEM;
    पूर्ण

    /* allocate and align the array of transmit PDU descriptors */
    अगर (क्रमe200e_dma_chunk_alloc(क्रमe200e,
				       &txq->tpd,
				       माप(काष्ठा tpd), 
				       QUEUE_SIZE_TX,
				       क्रमe200e->bus->descr_alignment) < 0) अणु
	
	क्रमe200e_dma_chunk_मुक्त(क्रमe200e, &txq->status);
	वापस -ENOMEM;
    पूर्ण

    /* get the base address of the cp resident tx queue entries */
    cp_entry = क्रमe200e->virt_base + क्रमe200e->bus->पढ़ो(&क्रमe200e->cp_queues->cp_txq);

    /* fill the host resident and cp resident tx entries */
    क्रम (i=0; i < QUEUE_SIZE_TX; i++) अणु
	
	txq->host_entry[ i ].status = 
	                     FORE200E_INDEX(txq->status.align_addr, क्रमागत status, i);
	txq->host_entry[ i ].tpd = 
	                     FORE200E_INDEX(txq->tpd.align_addr, काष्ठा tpd, i);
	txq->host_entry[ i ].tpd_dma  = 
                             FORE200E_DMA_INDEX(txq->tpd.dma_addr, काष्ठा tpd, i);
	txq->host_entry[ i ].cp_entry = &cp_entry[ i ];

	*txq->host_entry[ i ].status = STATUS_FREE;
	
	क्रमe200e->bus->ग_लिखो(FORE200E_DMA_INDEX(txq->status.dma_addr, क्रमागत status, i), 
			     &cp_entry[ i ].status_haddr);
	
        /* although there is a one-to-one mapping of tx queue entries and tpds,
	   we करो not ग_लिखो here the DMA (physical) base address of each tpd पूर्णांकo
	   the related cp resident entry, because the cp relies on this ग_लिखो
	   operation to detect that a new pdu has been submitted क्रम tx */
    पूर्ण

    /* set the head and tail entries of the queue */
    txq->head = 0;
    txq->tail = 0;

    क्रमe200e->state = FORE200E_STATE_INIT_TXQ;
    वापस 0;
पूर्ण


अटल पूर्णांक क्रमe200e_init_cmd_queue(काष्ठा क्रमe200e *क्रमe200e)
अणु
    काष्ठा host_cmdq*     cmdq =  &क्रमe200e->host_cmdq;
    काष्ठा cp_cmdq_entry __iomem * cp_entry;
    पूर्णांक i;

    DPRINTK(2, "command queue is being initialized\n");

    /* allocate and align the array of status words */
    अगर (क्रमe200e_dma_chunk_alloc(क्रमe200e,
				       &cmdq->status,
				       माप(क्रमागत status), 
				       QUEUE_SIZE_CMD,
				       क्रमe200e->bus->status_alignment) < 0) अणु
	वापस -ENOMEM;
    पूर्ण
    
    /* get the base address of the cp resident cmd queue entries */
    cp_entry = क्रमe200e->virt_base + क्रमe200e->bus->पढ़ो(&क्रमe200e->cp_queues->cp_cmdq);

    /* fill the host resident and cp resident cmd entries */
    क्रम (i=0; i < QUEUE_SIZE_CMD; i++) अणु
	
	cmdq->host_entry[ i ].status   = 
                              FORE200E_INDEX(cmdq->status.align_addr, क्रमागत status, i);
	cmdq->host_entry[ i ].cp_entry = &cp_entry[ i ];

	*cmdq->host_entry[ i ].status = STATUS_FREE;

	क्रमe200e->bus->ग_लिखो(FORE200E_DMA_INDEX(cmdq->status.dma_addr, क्रमागत status, i), 
                             &cp_entry[ i ].status_haddr);
    पूर्ण

    /* set the head entry of the queue */
    cmdq->head = 0;

    क्रमe200e->state = FORE200E_STATE_INIT_CMDQ;
    वापस 0;
पूर्ण


अटल व्योम क्रमe200e_param_bs_queue(काष्ठा क्रमe200e *क्रमe200e,
				    क्रमागत buffer_scheme scheme,
				    क्रमागत buffer_magn magn, पूर्णांक queue_length,
				    पूर्णांक pool_size, पूर्णांक supply_blksize)
अणु
    काष्ठा bs_spec __iomem * bs_spec = &क्रमe200e->cp_queues->init.bs_spec[ scheme ][ magn ];

    क्रमe200e->bus->ग_लिखो(queue_length,                           &bs_spec->queue_length);
    क्रमe200e->bus->ग_लिखो(क्रमe200e_rx_buf_size[ scheme ][ magn ], &bs_spec->buffer_size);
    क्रमe200e->bus->ग_लिखो(pool_size,                              &bs_spec->pool_size);
    क्रमe200e->bus->ग_लिखो(supply_blksize,                         &bs_spec->supply_blksize);
पूर्ण


अटल पूर्णांक क्रमe200e_initialize(काष्ठा क्रमe200e *क्रमe200e)
अणु
    काष्ठा cp_queues __iomem * cpq;
    पूर्णांक               ok, scheme, magn;

    DPRINTK(2, "device %s being initialized\n", क्रमe200e->name);

    mutex_init(&क्रमe200e->rate_mtx);
    spin_lock_init(&क्रमe200e->q_lock);

    cpq = क्रमe200e->cp_queues = क्रमe200e->virt_base + FORE200E_CP_QUEUES_OFFSET;

    /* enable cp to host पूर्णांकerrupts */
    क्रमe200e->bus->ग_लिखो(1, &cpq->imask);

    अगर (क्रमe200e->bus->irq_enable)
	क्रमe200e->bus->irq_enable(क्रमe200e);
    
    क्रमe200e->bus->ग_लिखो(NBR_CONNECT, &cpq->init.num_connect);

    क्रमe200e->bus->ग_लिखो(QUEUE_SIZE_CMD, &cpq->init.cmd_queue_len);
    क्रमe200e->bus->ग_लिखो(QUEUE_SIZE_RX,  &cpq->init.rx_queue_len);
    क्रमe200e->bus->ग_लिखो(QUEUE_SIZE_TX,  &cpq->init.tx_queue_len);

    क्रमe200e->bus->ग_लिखो(RSD_EXTENSION,  &cpq->init.rsd_extension);
    क्रमe200e->bus->ग_लिखो(TSD_EXTENSION,  &cpq->init.tsd_extension);

    क्रम (scheme = 0; scheme < BUFFER_SCHEME_NBR; scheme++)
	क्रम (magn = 0; magn < BUFFER_MAGN_NBR; magn++)
	    क्रमe200e_param_bs_queue(क्रमe200e, scheme, magn,
				    QUEUE_SIZE_BS, 
				    क्रमe200e_rx_buf_nbr[ scheme ][ magn ],
				    RBD_BLK_SIZE);

    /* issue the initialize command */
    क्रमe200e->bus->ग_लिखो(STATUS_PENDING,    &cpq->init.status);
    क्रमe200e->bus->ग_लिखो(OPCODE_INITIALIZE, &cpq->init.opcode);

    ok = क्रमe200e_io_poll(क्रमe200e, &cpq->init.status, STATUS_COMPLETE, 3000);
    अगर (ok == 0) अणु
	prपूर्णांकk(FORE200E "device %s initialization failed\n", क्रमe200e->name);
	वापस -ENODEV;
    पूर्ण

    prपूर्णांकk(FORE200E "device %s initialized\n", क्रमe200e->name);

    क्रमe200e->state = FORE200E_STATE_INITIALIZE;
    वापस 0;
पूर्ण


अटल व्योम क्रमe200e_monitor_अ_दो(काष्ठा क्रमe200e *क्रमe200e, अक्षर c)
अणु
    काष्ठा cp_monitor __iomem * monitor = क्रमe200e->cp_monitor;

#अगर 0
    prपूर्णांकk("%c", c);
#पूर्ण_अगर
    क्रमe200e->bus->ग_लिखो(((u32) c) | FORE200E_CP_MONITOR_UART_AVAIL, &monitor->soft_uart.send);
पूर्ण


अटल पूर्णांक क्रमe200e_monitor_अ_लो(काष्ठा क्रमe200e *क्रमe200e)
अणु
    काष्ठा cp_monitor __iomem * monitor = क्रमe200e->cp_monitor;
    अचिन्हित दीर्घ      समयout = jअगरfies + msecs_to_jअगरfies(50);
    पूर्णांक                c;

    जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु

	c = (पूर्णांक) क्रमe200e->bus->पढ़ो(&monitor->soft_uart.recv);

	अगर (c & FORE200E_CP_MONITOR_UART_AVAIL) अणु

	    क्रमe200e->bus->ग_लिखो(FORE200E_CP_MONITOR_UART_FREE, &monitor->soft_uart.recv);
#अगर 0
	    prपूर्णांकk("%c", c & 0xFF);
#पूर्ण_अगर
	    वापस c & 0xFF;
	पूर्ण
    पूर्ण

    वापस -1;
पूर्ण


अटल व्योम क्रमe200e_monitor_माला_दो(काष्ठा क्रमe200e *क्रमe200e, अक्षर *str)
अणु
    जबतक (*str) अणु

	/* the i960 monitor करोesn't accept any new अक्षरacter अगर it has something to say */
	जबतक (क्रमe200e_monitor_अ_लो(क्रमe200e) >= 0);
	
	क्रमe200e_monitor_अ_दो(क्रमe200e, *str++);
    पूर्ण

    जबतक (क्रमe200e_monitor_अ_लो(क्रमe200e) >= 0);
पूर्ण

#अगर_घोषित __LITTLE_ENDIAN
#घोषणा FW_EXT ".bin"
#अन्यथा
#घोषणा FW_EXT "_ecd.bin2"
#पूर्ण_अगर

अटल पूर्णांक क्रमe200e_load_and_start_fw(काष्ठा क्रमe200e *क्रमe200e)
अणु
    स्थिर काष्ठा firmware *firmware;
    स्थिर काष्ठा fw_header *fw_header;
    स्थिर __le32 *fw_data;
    u32 fw_size;
    u32 __iomem *load_addr;
    अक्षर buf[48];
    पूर्णांक err;

    प्र_लिखो(buf, "%s%s", क्रमe200e->bus->proc_name, FW_EXT);
    अगर ((err = request_firmware(&firmware, buf, क्रमe200e->dev)) < 0) अणु
	prपूर्णांकk(FORE200E "problem loading firmware image %s\n", क्रमe200e->bus->model_name);
	वापस err;
    पूर्ण

    fw_data = (स्थिर __le32 *)firmware->data;
    fw_size = firmware->size / माप(u32);
    fw_header = (स्थिर काष्ठा fw_header *)firmware->data;
    load_addr = क्रमe200e->virt_base + le32_to_cpu(fw_header->load_offset);

    DPRINTK(2, "device %s firmware being loaded at 0x%p (%d words)\n",
	    क्रमe200e->name, load_addr, fw_size);

    अगर (le32_to_cpu(fw_header->magic) != FW_HEADER_MAGIC) अणु
	prपूर्णांकk(FORE200E "corrupted %s firmware image\n", क्रमe200e->bus->model_name);
	जाओ release;
    पूर्ण

    क्रम (; fw_size--; fw_data++, load_addr++)
	क्रमe200e->bus->ग_लिखो(le32_to_cpu(*fw_data), load_addr);

    DPRINTK(2, "device %s firmware being started\n", क्रमe200e->name);

#अगर defined(__sparc_v9__)
    /* reported to be required by SBA cards on some sparc64 hosts */
    क्रमe200e_spin(100);
#पूर्ण_अगर

    प्र_लिखो(buf, "\rgo %x\r", le32_to_cpu(fw_header->start_offset));
    क्रमe200e_monitor_माला_दो(क्रमe200e, buf);

    अगर (क्रमe200e_io_poll(क्रमe200e, &क्रमe200e->cp_monitor->bstat, BSTAT_CP_RUNNING, 1000) == 0) अणु
	prपूर्णांकk(FORE200E "device %s firmware didn't start\n", क्रमe200e->name);
	जाओ release;
    पूर्ण

    prपूर्णांकk(FORE200E "device %s firmware started\n", क्रमe200e->name);

    क्रमe200e->state = FORE200E_STATE_START_FW;
    err = 0;

release:
    release_firmware(firmware);
    वापस err;
पूर्ण


अटल पूर्णांक क्रमe200e_रेजिस्टर(काष्ठा क्रमe200e *क्रमe200e, काष्ठा device *parent)
अणु
    काष्ठा aपंचांग_dev* aपंचांग_dev;

    DPRINTK(2, "device %s being registered\n", क्रमe200e->name);

    aपंचांग_dev = aपंचांग_dev_रेजिस्टर(क्रमe200e->bus->proc_name, parent, &क्रमe200e_ops,
                               -1, शून्य);
    अगर (aपंचांग_dev == शून्य) अणु
	prपूर्णांकk(FORE200E "unable to register device %s\n", क्रमe200e->name);
	वापस -ENODEV;
    पूर्ण

    aपंचांग_dev->dev_data = क्रमe200e;
    क्रमe200e->aपंचांग_dev = aपंचांग_dev;

    aपंचांग_dev->ci_range.vpi_bits = FORE200E_VPI_BITS;
    aपंचांग_dev->ci_range.vci_bits = FORE200E_VCI_BITS;

    क्रमe200e->available_cell_rate = ATM_OC3_PCR;

    क्रमe200e->state = FORE200E_STATE_REGISTER;
    वापस 0;
पूर्ण


अटल पूर्णांक क्रमe200e_init(काष्ठा क्रमe200e *क्रमe200e, काष्ठा device *parent)
अणु
    अगर (क्रमe200e_रेजिस्टर(क्रमe200e, parent) < 0)
	वापस -ENODEV;
    
    अगर (क्रमe200e->bus->configure(क्रमe200e) < 0)
	वापस -ENODEV;

    अगर (क्रमe200e->bus->map(क्रमe200e) < 0)
	वापस -ENODEV;

    अगर (क्रमe200e_reset(क्रमe200e, 1) < 0)
	वापस -ENODEV;

    अगर (क्रमe200e_load_and_start_fw(क्रमe200e) < 0)
	वापस -ENODEV;

    अगर (क्रमe200e_initialize(क्रमe200e) < 0)
	वापस -ENODEV;

    अगर (क्रमe200e_init_cmd_queue(क्रमe200e) < 0)
	वापस -ENOMEM;

    अगर (क्रमe200e_init_tx_queue(क्रमe200e) < 0)
	वापस -ENOMEM;

    अगर (क्रमe200e_init_rx_queue(क्रमe200e) < 0)
	वापस -ENOMEM;

    अगर (क्रमe200e_init_bs_queue(क्रमe200e) < 0)
	वापस -ENOMEM;

    अगर (क्रमe200e_alloc_rx_buf(क्रमe200e) < 0)
	वापस -ENOMEM;

    अगर (क्रमe200e_get_esi(क्रमe200e) < 0)
	वापस -EIO;

    अगर (क्रमe200e_irq_request(क्रमe200e) < 0)
	वापस -EBUSY;

    क्रमe200e_supply(क्रमe200e);

    /* all करोne, board initialization is now complete */
    क्रमe200e->state = FORE200E_STATE_COMPLETE;
    वापस 0;
पूर्ण

#अगर_घोषित CONFIG_SBUS
अटल स्थिर काष्ठा of_device_id क्रमe200e_sba_match[];
अटल पूर्णांक क्रमe200e_sba_probe(काष्ठा platक्रमm_device *op)
अणु
	स्थिर काष्ठा of_device_id *match;
	काष्ठा क्रमe200e *क्रमe200e;
	अटल पूर्णांक index = 0;
	पूर्णांक err;

	match = of_match_device(क्रमe200e_sba_match, &op->dev);
	अगर (!match)
		वापस -EINVAL;

	क्रमe200e = kzalloc(माप(काष्ठा क्रमe200e), GFP_KERNEL);
	अगर (!क्रमe200e)
		वापस -ENOMEM;

	क्रमe200e->bus = &क्रमe200e_sbus_ops;
	क्रमe200e->dev = &op->dev;
	क्रमe200e->irq = op->archdata.irqs[0];
	क्रमe200e->phys_base = op->resource[0].start;

	प्र_लिखो(क्रमe200e->name, "SBA-200E-%d", index);

	err = क्रमe200e_init(क्रमe200e, &op->dev);
	अगर (err < 0) अणु
		क्रमe200e_shutकरोwn(क्रमe200e);
		kमुक्त(क्रमe200e);
		वापस err;
	पूर्ण

	index++;
	dev_set_drvdata(&op->dev, क्रमe200e);

	वापस 0;
पूर्ण

अटल पूर्णांक क्रमe200e_sba_हटाओ(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा क्रमe200e *क्रमe200e = dev_get_drvdata(&op->dev);

	क्रमe200e_shutकरोwn(क्रमe200e);
	kमुक्त(क्रमe200e);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id क्रमe200e_sba_match[] = अणु
	अणु
		.name = SBA200E_PROM_NAME,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, क्रमe200e_sba_match);

अटल काष्ठा platक्रमm_driver क्रमe200e_sba_driver = अणु
	.driver = अणु
		.name = "fore_200e",
		.of_match_table = क्रमe200e_sba_match,
	पूर्ण,
	.probe		= क्रमe200e_sba_probe,
	.हटाओ		= क्रमe200e_sba_हटाओ,
पूर्ण;
#पूर्ण_अगर

#अगर_घोषित CONFIG_PCI
अटल पूर्णांक क्रमe200e_pca_detect(काष्ठा pci_dev *pci_dev,
			       स्थिर काष्ठा pci_device_id *pci_ent)
अणु
    काष्ठा क्रमe200e* क्रमe200e;
    पूर्णांक err = 0;
    अटल पूर्णांक index = 0;

    अगर (pci_enable_device(pci_dev)) अणु
	err = -EINVAL;
	जाओ out;
    पूर्ण

    अगर (dma_set_mask_and_coherent(&pci_dev->dev, DMA_BIT_MASK(32))) अणु
	err = -EINVAL;
	जाओ out;
    पूर्ण
    
    क्रमe200e = kzalloc(माप(काष्ठा क्रमe200e), GFP_KERNEL);
    अगर (क्रमe200e == शून्य) अणु
	err = -ENOMEM;
	जाओ out_disable;
    पूर्ण

    क्रमe200e->bus       = &क्रमe200e_pci_ops;
    क्रमe200e->dev	= &pci_dev->dev;
    क्रमe200e->irq       = pci_dev->irq;
    क्रमe200e->phys_base = pci_resource_start(pci_dev, 0);

    प्र_लिखो(क्रमe200e->name, "PCA-200E-%d", index - 1);

    pci_set_master(pci_dev);

    prपूर्णांकk(FORE200E "device PCA-200E found at 0x%lx, IRQ %s\n",
	   क्रमe200e->phys_base, क्रमe200e_irq_itoa(क्रमe200e->irq));

    प्र_लिखो(क्रमe200e->name, "PCA-200E-%d", index);

    err = क्रमe200e_init(क्रमe200e, &pci_dev->dev);
    अगर (err < 0) अणु
	क्रमe200e_shutकरोwn(क्रमe200e);
	जाओ out_मुक्त;
    पूर्ण

    ++index;
    pci_set_drvdata(pci_dev, क्रमe200e);

out:
    वापस err;

out_मुक्त:
    kमुक्त(क्रमe200e);
out_disable:
    pci_disable_device(pci_dev);
    जाओ out;
पूर्ण


अटल व्योम क्रमe200e_pca_हटाओ_one(काष्ठा pci_dev *pci_dev)
अणु
    काष्ठा क्रमe200e *क्रमe200e;

    क्रमe200e = pci_get_drvdata(pci_dev);

    क्रमe200e_shutकरोwn(क्रमe200e);
    kमुक्त(क्रमe200e);
    pci_disable_device(pci_dev);
पूर्ण


अटल स्थिर काष्ठा pci_device_id क्रमe200e_pca_tbl[] = अणु
    अणु PCI_VENDOR_ID_FORE, PCI_DEVICE_ID_FORE_PCA200E, PCI_ANY_ID, PCI_ANY_ID पूर्ण,
    अणु 0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, क्रमe200e_pca_tbl);

अटल काष्ठा pci_driver क्रमe200e_pca_driver = अणु
    .name =     "fore_200e",
    .probe =    क्रमe200e_pca_detect,
    .हटाओ =   क्रमe200e_pca_हटाओ_one,
    .id_table = क्रमe200e_pca_tbl,
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक __init क्रमe200e_module_init(व्योम)
अणु
	पूर्णांक err = 0;

	prपूर्णांकk(FORE200E "FORE Systems 200E-series ATM driver - version " FORE200E_VERSION "\n");

#अगर_घोषित CONFIG_SBUS
	err = platक्रमm_driver_रेजिस्टर(&क्रमe200e_sba_driver);
	अगर (err)
		वापस err;
#पूर्ण_अगर

#अगर_घोषित CONFIG_PCI
	err = pci_रेजिस्टर_driver(&क्रमe200e_pca_driver);
#पूर्ण_अगर

#अगर_घोषित CONFIG_SBUS
	अगर (err)
		platक्रमm_driver_unरेजिस्टर(&क्रमe200e_sba_driver);
#पूर्ण_अगर

	वापस err;
पूर्ण

अटल व्योम __निकास क्रमe200e_module_cleanup(व्योम)
अणु
#अगर_घोषित CONFIG_PCI
	pci_unरेजिस्टर_driver(&क्रमe200e_pca_driver);
#पूर्ण_अगर
#अगर_घोषित CONFIG_SBUS
	platक्रमm_driver_unरेजिस्टर(&क्रमe200e_sba_driver);
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक
क्रमe200e_proc_पढ़ो(काष्ठा aपंचांग_dev *dev, loff_t* pos, अक्षर* page)
अणु
    काष्ठा क्रमe200e*     क्रमe200e  = FORE200E_DEV(dev);
    काष्ठा क्रमe200e_vcc* क्रमe200e_vcc;
    काष्ठा aपंचांग_vcc*      vcc;
    पूर्णांक                  i, len, left = *pos;
    अचिन्हित दीर्घ        flags;

    अगर (!left--) अणु

	अगर (क्रमe200e_माला_लोtats(क्रमe200e) < 0)
	    वापस -EIO;

	len = प्र_लिखो(page,"\n"
		       " device:\n"
		       "   internal name:\t\t%s\n", क्रमe200e->name);

	/* prपूर्णांक bus-specअगरic inक्रमmation */
	अगर (क्रमe200e->bus->proc_पढ़ो)
	    len += क्रमe200e->bus->proc_पढ़ो(क्रमe200e, page + len);
	
	len += प्र_लिखो(page + len,
		"   interrupt line:\t\t%s\n"
		"   physical base address:\t0x%p\n"
		"   virtual base address:\t0x%p\n"
		"   factory address (ESI):\t%pM\n"
		"   board serial number:\t\t%d\n\n",
		क्रमe200e_irq_itoa(क्रमe200e->irq),
		(व्योम*)क्रमe200e->phys_base,
		क्रमe200e->virt_base,
		क्रमe200e->esi,
		क्रमe200e->esi[4] * 256 + क्रमe200e->esi[5]);

	वापस len;
    पूर्ण

    अगर (!left--)
	वापस प्र_लिखो(page,
		       "   free small bufs, scheme 1:\t%d\n"
		       "   free large bufs, scheme 1:\t%d\n"
		       "   free small bufs, scheme 2:\t%d\n"
		       "   free large bufs, scheme 2:\t%d\n",
		       क्रमe200e->host_bsq[ BUFFER_SCHEME_ONE ][ BUFFER_MAGN_SMALL ].मुक्तbuf_count,
		       क्रमe200e->host_bsq[ BUFFER_SCHEME_ONE ][ BUFFER_MAGN_LARGE ].मुक्तbuf_count,
		       क्रमe200e->host_bsq[ BUFFER_SCHEME_TWO ][ BUFFER_MAGN_SMALL ].मुक्तbuf_count,
		       क्रमe200e->host_bsq[ BUFFER_SCHEME_TWO ][ BUFFER_MAGN_LARGE ].मुक्तbuf_count);

    अगर (!left--) अणु
	u32 hb = क्रमe200e->bus->पढ़ो(&क्रमe200e->cp_queues->heartbeat);

	len = प्र_लिखो(page,"\n\n"
		      " cell processor:\n"
		      "   heartbeat state:\t\t");
	
	अगर (hb >> 16 != 0xDEAD)
	    len += प्र_लिखो(page + len, "0x%08x\n", hb);
	अन्यथा
	    len += प्र_लिखो(page + len, "*** FATAL ERROR %04x ***\n", hb & 0xFFFF);

	वापस len;
    पूर्ण

    अगर (!left--) अणु
	अटल स्थिर अक्षर* media_name[] = अणु
	    "unshielded twisted pair",
	    "multimode optical fiber ST",
	    "multimode optical fiber SC",
	    "single-mode optical fiber ST",
	    "single-mode optical fiber SC",
	    "unknown"
	पूर्ण;

	अटल स्थिर अक्षर* oc3_mode[] = अणु
	    "normal operation",
	    "diagnostic loopback",
	    "line loopback",
	    "unknown"
	पूर्ण;

	u32 fw_release     = क्रमe200e->bus->पढ़ो(&क्रमe200e->cp_queues->fw_release);
	u32 mon960_release = क्रमe200e->bus->पढ़ो(&क्रमe200e->cp_queues->mon960_release);
	u32 oc3_revision   = क्रमe200e->bus->पढ़ो(&क्रमe200e->cp_queues->oc3_revision);
	u32 media_index    = FORE200E_MEDIA_INDEX(क्रमe200e->bus->पढ़ो(&क्रमe200e->cp_queues->media_type));
	u32 oc3_index;

	अगर (media_index > 4)
		media_index = 5;
	
	चयन (क्रमe200e->loop_mode) अणु
	    हाल ATM_LM_NONE:    oc3_index = 0;
		                 अवरोध;
	    हाल ATM_LM_LOC_PHY: oc3_index = 1;
		                 अवरोध;
	    हाल ATM_LM_RMT_PHY: oc3_index = 2;
		                 अवरोध;
	    शेष:             oc3_index = 3;
	पूर्ण

	वापस प्र_लिखो(page,
		       "   firmware release:\t\t%d.%d.%d\n"
		       "   monitor release:\t\t%d.%d\n"
		       "   media type:\t\t\t%s\n"
		       "   OC-3 revision:\t\t0x%x\n"
                       "   OC-3 mode:\t\t\t%s",
		       fw_release >> 16, fw_release << 16 >> 24,  fw_release << 24 >> 24,
		       mon960_release >> 16, mon960_release << 16 >> 16,
		       media_name[ media_index ],
		       oc3_revision,
		       oc3_mode[ oc3_index ]);
    पूर्ण

    अगर (!left--) अणु
	काष्ठा cp_monitor __iomem * cp_monitor = क्रमe200e->cp_monitor;

	वापस प्र_लिखो(page,
		       "\n\n"
		       " monitor:\n"
		       "   version number:\t\t%d\n"
		       "   boot status word:\t\t0x%08x\n",
		       क्रमe200e->bus->पढ़ो(&cp_monitor->mon_version),
		       क्रमe200e->bus->पढ़ो(&cp_monitor->bstat));
    पूर्ण

    अगर (!left--)
	वापस प्र_लिखो(page,
		       "\n"
		       " device statistics:\n"
		       "  4b5b:\n"
		       "     crc_header_errors:\t\t%10u\n"
		       "     framing_errors:\t\t%10u\n",
		       be32_to_cpu(क्रमe200e->stats->phy.crc_header_errors),
		       be32_to_cpu(क्रमe200e->stats->phy.framing_errors));
    
    अगर (!left--)
	वापस प्र_लिखो(page, "\n"
		       "  OC-3:\n"
		       "     section_bip8_errors:\t%10u\n"
		       "     path_bip8_errors:\t\t%10u\n"
		       "     line_bip24_errors:\t\t%10u\n"
		       "     line_febe_errors:\t\t%10u\n"
		       "     path_febe_errors:\t\t%10u\n"
		       "     corr_hcs_errors:\t\t%10u\n"
		       "     ucorr_hcs_errors:\t\t%10u\n",
		       be32_to_cpu(क्रमe200e->stats->oc3.section_bip8_errors),
		       be32_to_cpu(क्रमe200e->stats->oc3.path_bip8_errors),
		       be32_to_cpu(क्रमe200e->stats->oc3.line_bip24_errors),
		       be32_to_cpu(क्रमe200e->stats->oc3.line_febe_errors),
		       be32_to_cpu(क्रमe200e->stats->oc3.path_febe_errors),
		       be32_to_cpu(क्रमe200e->stats->oc3.corr_hcs_errors),
		       be32_to_cpu(क्रमe200e->stats->oc3.ucorr_hcs_errors));

    अगर (!left--)
	वापस प्र_लिखो(page,"\n"
		       "   ATM:\t\t\t\t     cells\n"
		       "     TX:\t\t\t%10u\n"
		       "     RX:\t\t\t%10u\n"
		       "     vpi out of range:\t\t%10u\n"
		       "     vpi no conn:\t\t%10u\n"
		       "     vci out of range:\t\t%10u\n"
		       "     vci no conn:\t\t%10u\n",
		       be32_to_cpu(क्रमe200e->stats->aपंचांग.cells_transmitted),
		       be32_to_cpu(क्रमe200e->stats->aपंचांग.cells_received),
		       be32_to_cpu(क्रमe200e->stats->aपंचांग.vpi_bad_range),
		       be32_to_cpu(क्रमe200e->stats->aपंचांग.vpi_no_conn),
		       be32_to_cpu(क्रमe200e->stats->aपंचांग.vci_bad_range),
		       be32_to_cpu(क्रमe200e->stats->aपंचांग.vci_no_conn));
    
    अगर (!left--)
	वापस प्र_लिखो(page,"\n"
		       "   AAL0:\t\t\t     cells\n"
		       "     TX:\t\t\t%10u\n"
		       "     RX:\t\t\t%10u\n"
		       "     dropped:\t\t\t%10u\n",
		       be32_to_cpu(क्रमe200e->stats->aal0.cells_transmitted),
		       be32_to_cpu(क्रमe200e->stats->aal0.cells_received),
		       be32_to_cpu(क्रमe200e->stats->aal0.cells_dropped));
    
    अगर (!left--)
	वापस प्र_लिखो(page,"\n"
		       "   AAL3/4:\n"
		       "     SAR sublayer:\t\t     cells\n"
		       "       TX:\t\t\t%10u\n"
		       "       RX:\t\t\t%10u\n"
		       "       dropped:\t\t\t%10u\n"
		       "       CRC errors:\t\t%10u\n"
		       "       protocol errors:\t\t%10u\n\n"
		       "     CS  sublayer:\t\t      PDUs\n"
		       "       TX:\t\t\t%10u\n"
		       "       RX:\t\t\t%10u\n"
		       "       dropped:\t\t\t%10u\n"
		       "       protocol errors:\t\t%10u\n",
		       be32_to_cpu(क्रमe200e->stats->aal34.cells_transmitted),
		       be32_to_cpu(क्रमe200e->stats->aal34.cells_received),
		       be32_to_cpu(क्रमe200e->stats->aal34.cells_dropped),
		       be32_to_cpu(क्रमe200e->stats->aal34.cells_crc_errors),
		       be32_to_cpu(क्रमe200e->stats->aal34.cells_protocol_errors),
		       be32_to_cpu(क्रमe200e->stats->aal34.cspdus_transmitted),
		       be32_to_cpu(क्रमe200e->stats->aal34.cspdus_received),
		       be32_to_cpu(क्रमe200e->stats->aal34.cspdus_dropped),
		       be32_to_cpu(क्रमe200e->stats->aal34.cspdus_protocol_errors));
    
    अगर (!left--)
	वापस प्र_लिखो(page,"\n"
		       "   AAL5:\n"
		       "     SAR sublayer:\t\t     cells\n"
		       "       TX:\t\t\t%10u\n"
		       "       RX:\t\t\t%10u\n"
		       "       dropped:\t\t\t%10u\n"
		       "       congestions:\t\t%10u\n\n"
		       "     CS  sublayer:\t\t      PDUs\n"
		       "       TX:\t\t\t%10u\n"
		       "       RX:\t\t\t%10u\n"
		       "       dropped:\t\t\t%10u\n"
		       "       CRC errors:\t\t%10u\n"
		       "       protocol errors:\t\t%10u\n",
		       be32_to_cpu(क्रमe200e->stats->aal5.cells_transmitted),
		       be32_to_cpu(क्रमe200e->stats->aal5.cells_received),
		       be32_to_cpu(क्रमe200e->stats->aal5.cells_dropped),
		       be32_to_cpu(क्रमe200e->stats->aal5.congestion_experienced),
		       be32_to_cpu(क्रमe200e->stats->aal5.cspdus_transmitted),
		       be32_to_cpu(क्रमe200e->stats->aal5.cspdus_received),
		       be32_to_cpu(क्रमe200e->stats->aal5.cspdus_dropped),
		       be32_to_cpu(क्रमe200e->stats->aal5.cspdus_crc_errors),
		       be32_to_cpu(क्रमe200e->stats->aal5.cspdus_protocol_errors));
    
    अगर (!left--)
	वापस प्र_लिखो(page,"\n"
		       "   AUX:\t\t       allocation failures\n"
		       "     small b1:\t\t\t%10u\n"
		       "     large b1:\t\t\t%10u\n"
		       "     small b2:\t\t\t%10u\n"
		       "     large b2:\t\t\t%10u\n"
		       "     RX PDUs:\t\t\t%10u\n"
		       "     TX PDUs:\t\t\t%10lu\n",
		       be32_to_cpu(क्रमe200e->stats->aux.small_b1_failed),
		       be32_to_cpu(क्रमe200e->stats->aux.large_b1_failed),
		       be32_to_cpu(क्रमe200e->stats->aux.small_b2_failed),
		       be32_to_cpu(क्रमe200e->stats->aux.large_b2_failed),
		       be32_to_cpu(क्रमe200e->stats->aux.rpd_alloc_failed),
		       क्रमe200e->tx_sat);
    
    अगर (!left--)
	वापस प्र_लिखो(page,"\n"
		       " receive carrier:\t\t\t%s\n",
		       क्रमe200e->stats->aux.receive_carrier ? "ON" : "OFF!");
    
    अगर (!left--) अणु
        वापस प्र_लिखो(page,"\n"
		       " VCCs:\n  address   VPI VCI   AAL "
		       "TX PDUs   TX min/max size  RX PDUs   RX min/max size\n");
    पूर्ण

    क्रम (i = 0; i < NBR_CONNECT; i++) अणु

	vcc = क्रमe200e->vc_map[i].vcc;

	अगर (vcc == शून्य)
	    जारी;

	spin_lock_irqsave(&क्रमe200e->q_lock, flags);

	अगर (vcc && test_bit(ATM_VF_READY, &vcc->flags) && !left--) अणु

	    क्रमe200e_vcc = FORE200E_VCC(vcc);
	    ASSERT(क्रमe200e_vcc);

	    len = प्र_लिखो(page,
			  "  %pK  %03d %05d %1d   %09lu %05d/%05d      %09lu %05d/%05d\n",
			  vcc,
			  vcc->vpi, vcc->vci, क्रमe200e_aपंचांग2क्रमe_aal(vcc->qos.aal),
			  क्रमe200e_vcc->tx_pdu,
			  क्रमe200e_vcc->tx_min_pdu > 0xFFFF ? 0 : क्रमe200e_vcc->tx_min_pdu,
			  क्रमe200e_vcc->tx_max_pdu,
			  क्रमe200e_vcc->rx_pdu,
			  क्रमe200e_vcc->rx_min_pdu > 0xFFFF ? 0 : क्रमe200e_vcc->rx_min_pdu,
			  क्रमe200e_vcc->rx_max_pdu);

	    spin_unlock_irqrestore(&क्रमe200e->q_lock, flags);
	    वापस len;
	पूर्ण

	spin_unlock_irqrestore(&क्रमe200e->q_lock, flags);
    पूर्ण
    
    वापस 0;
पूर्ण

module_init(क्रमe200e_module_init);
module_निकास(क्रमe200e_module_cleanup);


अटल स्थिर काष्ठा aपंचांगdev_ops क्रमe200e_ops = अणु
	.खोलो       = क्रमe200e_खोलो,
	.बंद      = क्रमe200e_बंद,
	.ioctl      = क्रमe200e_ioctl,
	.send       = क्रमe200e_send,
	.change_qos = क्रमe200e_change_qos,
	.proc_पढ़ो  = क्रमe200e_proc_पढ़ो,
	.owner      = THIS_MODULE
पूर्ण;

MODULE_LICENSE("GPL");
#अगर_घोषित CONFIG_PCI
#अगर_घोषित __LITTLE_ENDIAN__
MODULE_FIRMWARE("pca200e.bin");
#अन्यथा
MODULE_FIRMWARE("pca200e_ecd.bin2");
#पूर्ण_अगर
#पूर्ण_अगर /* CONFIG_PCI */
#अगर_घोषित CONFIG_SBUS
MODULE_FIRMWARE("sba200e_ecd.bin2");
#पूर्ण_अगर
