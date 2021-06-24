<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _M68K_DMA_H
#घोषणा _M68K_DMA_H 1

#अगर_घोषित CONFIG_COLDFIRE
/*
 * ColdFire DMA Model:
 *   ColdFire DMA supports two क्रमms of DMA: Single and Dual address. Single
 * address mode emits a source address, and expects that the device will either
 * pick up the data (DMA READ) or source data (DMA WRITE). This implies that
 * the device will place data on the correct byte(s) of the data bus, as the
 * memory transactions are always 32 bits. This implies that only 32 bit
 * devices will find single mode transfers useful. Dual address DMA mode
 * perक्रमms two cycles: source पढ़ो and destination ग_लिखो. ColdFire will
 * align the data so that the device will always get the correct bytes, thus
 * is useful क्रम 8 and 16 bit devices. This is the mode that is supported
 * below.
 *
 * AUG/22/2000 : added support क्रम 32-bit Dual-Address-Mode (K) 2000
 *               Oliver Kamphenkel (O.Kamphenkel@tu-bs.de)
 *
 * AUG/25/2000 : added support क्रम 8, 16 and 32-bit Single-Address-Mode (K)2000
 *               Oliver Kamphenkel (O.Kamphenkel@tu-bs.de)
 *
 * APR/18/2002 : added proper support क्रम MCF5272 DMA controller.
 *               Arthur Shipkowski (art@videon-central.com)
 */

#समावेश <यंत्र/coldfire.h>
#समावेश <यंत्र/mcfsim.h>
#समावेश <यंत्र/mcfdma.h>

/*
 * Set number of channels of DMA on ColdFire क्रम dअगरferent implementations.
 */
#अगर defined(CONFIG_M5249) || defined(CONFIG_M5307) || defined(CONFIG_M5407) || \
	defined(CONFIG_M523x) || defined(CONFIG_M527x) || \
	defined(CONFIG_M528x) || defined(CONFIG_M525x)

#घोषणा MAX_M68K_DMA_CHANNELS 4
#या_अगर defined(CONFIG_M5272)
#घोषणा MAX_M68K_DMA_CHANNELS 1
#या_अगर defined(CONFIG_M53xx)
#घोषणा MAX_M68K_DMA_CHANNELS 0
#अन्यथा
#घोषणा MAX_M68K_DMA_CHANNELS 2
#पूर्ण_अगर

बाह्य अचिन्हित पूर्णांक dma_base_addr[MAX_M68K_DMA_CHANNELS];
बाह्य अचिन्हित पूर्णांक dma_device_address[MAX_M68K_DMA_CHANNELS];

#अगर !defined(CONFIG_M5272)
#घोषणा DMA_MODE_WRITE_BIT  0x01  /* Memory/IO to IO/Memory select */
#घोषणा DMA_MODE_WORD_BIT   0x02  /* 8 or 16 bit transfers */
#घोषणा DMA_MODE_LONG_BIT   0x04  /* or 32 bit transfers */
#घोषणा DMA_MODE_SINGLE_BIT 0x08  /* single-address-mode */

/* I/O to memory, 8 bits, mode */
#घोषणा DMA_MODE_READ	            0
/* memory to I/O, 8 bits, mode */
#घोषणा DMA_MODE_WRITE	            1
/* I/O to memory, 16 bits, mode */
#घोषणा DMA_MODE_READ_WORD          2
/* memory to I/O, 16 bits, mode */
#घोषणा DMA_MODE_WRITE_WORD         3
/* I/O to memory, 32 bits, mode */
#घोषणा DMA_MODE_READ_LONG          4
/* memory to I/O, 32 bits, mode */
#घोषणा DMA_MODE_WRITE_LONG         5
/* I/O to memory, 8 bits, single-address-mode */
#घोषणा DMA_MODE_READ_SINGLE        8
/* memory to I/O, 8 bits, single-address-mode */
#घोषणा DMA_MODE_WRITE_SINGLE       9
/* I/O to memory, 16 bits, single-address-mode */
#घोषणा DMA_MODE_READ_WORD_SINGLE  10
/* memory to I/O, 16 bits, single-address-mode */
#घोषणा DMA_MODE_WRITE_WORD_SINGLE 11
/* I/O to memory, 32 bits, single-address-mode */
#घोषणा DMA_MODE_READ_LONG_SINGLE  12
/* memory to I/O, 32 bits, single-address-mode */
#घोषणा DMA_MODE_WRITE_LONG_SINGLE 13

#अन्यथा /* CONFIG_M5272 is defined */

/* Source अटल-address mode */
#घोषणा DMA_MODE_SRC_SA_BIT 0x01
/* Two bits to select between all four modes */
#घोषणा DMA_MODE_SSIZE_MASK 0x06
/* Offset to shअगरt bits in */
#घोषणा DMA_MODE_SSIZE_OFF  0x01
/* Destination अटल-address mode */
#घोषणा DMA_MODE_DES_SA_BIT 0x10
/* Two bits to select between all four modes */
#घोषणा DMA_MODE_DSIZE_MASK 0x60
/* Offset to shअगरt bits in */
#घोषणा DMA_MODE_DSIZE_OFF  0x05
/* Size modअगरiers */
#घोषणा DMA_MODE_SIZE_LONG  0x00
#घोषणा DMA_MODE_SIZE_BYTE  0x01
#घोषणा DMA_MODE_SIZE_WORD  0x02
#घोषणा DMA_MODE_SIZE_LINE  0x03

/*
 * Aliases to help speed quick ports; these may be suboptimal, however. They
 * करो not include the SINGLE mode modअगरiers since the MCF5272 करोes not have a
 * mode where the device is in control of its addressing.
 */

/* I/O to memory, 8 bits, mode */
#घोषणा DMA_MODE_READ	              ((DMA_MODE_SIZE_BYTE << DMA_MODE_DSIZE_OFF) | (DMA_MODE_SIZE_BYTE << DMA_MODE_SSIZE_OFF) | DMA_SRC_SA_BIT)
/* memory to I/O, 8 bits, mode */
#घोषणा DMA_MODE_WRITE	            ((DMA_MODE_SIZE_BYTE << DMA_MODE_DSIZE_OFF) | (DMA_MODE_SIZE_BYTE << DMA_MODE_SSIZE_OFF) | DMA_DES_SA_BIT)
/* I/O to memory, 16 bits, mode */
#घोषणा DMA_MODE_READ_WORD	        ((DMA_MODE_SIZE_WORD << DMA_MODE_DSIZE_OFF) | (DMA_MODE_SIZE_WORD << DMA_MODE_SSIZE_OFF) | DMA_SRC_SA_BIT)
/* memory to I/O, 16 bits, mode */
#घोषणा DMA_MODE_WRITE_WORD         ((DMA_MODE_SIZE_WORD << DMA_MODE_DSIZE_OFF) | (DMA_MODE_SIZE_WORD << DMA_MODE_SSIZE_OFF) | DMA_DES_SA_BIT)
/* I/O to memory, 32 bits, mode */
#घोषणा DMA_MODE_READ_LONG	        ((DMA_MODE_SIZE_LONG << DMA_MODE_DSIZE_OFF) | (DMA_MODE_SIZE_LONG << DMA_MODE_SSIZE_OFF) | DMA_SRC_SA_BIT)
/* memory to I/O, 32 bits, mode */
#घोषणा DMA_MODE_WRITE_LONG         ((DMA_MODE_SIZE_LONG << DMA_MODE_DSIZE_OFF) | (DMA_MODE_SIZE_LONG << DMA_MODE_SSIZE_OFF) | DMA_DES_SA_BIT)

#पूर्ण_अगर /* !defined(CONFIG_M5272) */

#अगर !defined(CONFIG_M5272)
/* enable/disable a specअगरic DMA channel */
अटल __अंतरभूत__ व्योम enable_dma(अचिन्हित पूर्णांक dmanr)
अणु
  अस्थिर अचिन्हित लघु *dmawp;

#अगर_घोषित DMA_DEBUG
  prपूर्णांकk("enable_dma(dmanr=%d)\n", dmanr);
#पूर्ण_अगर

  dmawp = (अचिन्हित लघु *) dma_base_addr[dmanr];
  dmawp[MCFDMA_DCR] |= MCFDMA_DCR_EEXT;
पूर्ण

अटल __अंतरभूत__ व्योम disable_dma(अचिन्हित पूर्णांक dmanr)
अणु
  अस्थिर अचिन्हित लघु *dmawp;
  अस्थिर अचिन्हित अक्षर  *dmapb;

#अगर_घोषित DMA_DEBUG
  prपूर्णांकk("disable_dma(dmanr=%d)\n", dmanr);
#पूर्ण_अगर

  dmawp = (अचिन्हित लघु *) dma_base_addr[dmanr];
  dmapb = (अचिन्हित अक्षर *) dma_base_addr[dmanr];

  /* Turn off बाह्यal requests, and stop any DMA in progress */
  dmawp[MCFDMA_DCR] &= ~MCFDMA_DCR_EEXT;
  dmapb[MCFDMA_DSR] = MCFDMA_DSR_DONE;
पूर्ण

/*
 * Clear the 'DMA Pointer Flip Flop'.
 * Write 0 क्रम LSB/MSB, 1 क्रम MSB/LSB access.
 * Use this once to initialize the FF to a known state.
 * After that, keep track of it. :-)
 * --- In order to करो that, the DMA routines below should ---
 * --- only be used जबतक पूर्णांकerrupts are disabled! ---
 *
 * This is a NOP क्रम ColdFire. Provide a stub क्रम compatibility.
 */
अटल __अंतरभूत__ व्योम clear_dma_ff(अचिन्हित पूर्णांक dmanr)
अणु
पूर्ण

/* set mode (above) क्रम a specअगरic DMA channel */
अटल __अंतरभूत__ व्योम set_dma_mode(अचिन्हित पूर्णांक dmanr, अक्षर mode)
अणु

  अस्थिर अचिन्हित अक्षर  *dmabp;
  अस्थिर अचिन्हित लघु *dmawp;

#अगर_घोषित DMA_DEBUG
  prपूर्णांकk("set_dma_mode(dmanr=%d,mode=%d)\n", dmanr, mode);
#पूर्ण_अगर

  dmabp = (अचिन्हित अक्षर *) dma_base_addr[dmanr];
  dmawp = (अचिन्हित लघु *) dma_base_addr[dmanr];

  /* Clear config errors */
  dmabp[MCFDMA_DSR] = MCFDMA_DSR_DONE;

  /* Set command रेजिस्टर */
  dmawp[MCFDMA_DCR] =
    MCFDMA_DCR_INT |         /* Enable completion irq */
    MCFDMA_DCR_CS |          /* Force one xfer per request */
    MCFDMA_DCR_AA |          /* Enable स्वतः alignment */
    /* single-address-mode */
    ((mode & DMA_MODE_SINGLE_BIT) ? MCFDMA_DCR_SAA : 0) |
    /* sets s_rw (-> r/w) high अगर Memory to I/0 */
    ((mode & DMA_MODE_WRITE_BIT) ? MCFDMA_DCR_S_RW : 0) |
    /* Memory to I/O or I/O to Memory */
    ((mode & DMA_MODE_WRITE_BIT) ? MCFDMA_DCR_SINC : MCFDMA_DCR_DINC) |
    /* 32 bit, 16 bit or 8 bit transfers */
    ((mode & DMA_MODE_WORD_BIT)  ? MCFDMA_DCR_SSIZE_WORD :
     ((mode & DMA_MODE_LONG_BIT) ? MCFDMA_DCR_SSIZE_LONG :
                                   MCFDMA_DCR_SSIZE_BYTE)) |
    ((mode & DMA_MODE_WORD_BIT)  ? MCFDMA_DCR_DSIZE_WORD :
     ((mode & DMA_MODE_LONG_BIT) ? MCFDMA_DCR_DSIZE_LONG :
                                   MCFDMA_DCR_DSIZE_BYTE));

#अगर_घोषित DEBUG_DMA
  prपूर्णांकk("%s(%d): dmanr=%d DSR[%x]=%x DCR[%x]=%x\n", __खाता__, __LINE__,
         dmanr, (पूर्णांक) &dmabp[MCFDMA_DSR], dmabp[MCFDMA_DSR],
	 (पूर्णांक) &dmawp[MCFDMA_DCR], dmawp[MCFDMA_DCR]);
#पूर्ण_अगर
पूर्ण

/* Set transfer address क्रम specअगरic DMA channel */
अटल __अंतरभूत__ व्योम set_dma_addr(अचिन्हित पूर्णांक dmanr, अचिन्हित पूर्णांक a)
अणु
  अस्थिर अचिन्हित लघु *dmawp;
  अस्थिर अचिन्हित पूर्णांक   *dmalp;

#अगर_घोषित DMA_DEBUG
  prपूर्णांकk("set_dma_addr(dmanr=%d,a=%x)\n", dmanr, a);
#पूर्ण_अगर

  dmawp = (अचिन्हित लघु *) dma_base_addr[dmanr];
  dmalp = (अचिन्हित पूर्णांक *) dma_base_addr[dmanr];

  /* Determine which address रेजिस्टरs are used क्रम memory/device accesses */
  अगर (dmawp[MCFDMA_DCR] & MCFDMA_DCR_SINC) अणु
    /* Source incrementing, must be memory */
    dmalp[MCFDMA_SAR] = a;
    /* Set dest address, must be device */
    dmalp[MCFDMA_DAR] = dma_device_address[dmanr];
  पूर्ण अन्यथा अणु
    /* Destination incrementing, must be memory */
    dmalp[MCFDMA_DAR] = a;
    /* Set source address, must be device */
    dmalp[MCFDMA_SAR] = dma_device_address[dmanr];
  पूर्ण

#अगर_घोषित DEBUG_DMA
  prपूर्णांकk("%s(%d): dmanr=%d DCR[%x]=%x SAR[%x]=%08x DAR[%x]=%08x\n",
	__खाता__, __LINE__, dmanr, (पूर्णांक) &dmawp[MCFDMA_DCR], dmawp[MCFDMA_DCR],
	(पूर्णांक) &dmalp[MCFDMA_SAR], dmalp[MCFDMA_SAR],
	(पूर्णांक) &dmalp[MCFDMA_DAR], dmalp[MCFDMA_DAR]);
#पूर्ण_अगर
पूर्ण

/*
 * Specअगरic क्रम Coldfire - sets device address.
 * Should be called after the mode set call, and beक्रमe set DMA address.
 */
अटल __अंतरभूत__ व्योम set_dma_device_addr(अचिन्हित पूर्णांक dmanr, अचिन्हित पूर्णांक a)
अणु
#अगर_घोषित DMA_DEBUG
  prपूर्णांकk("set_dma_device_addr(dmanr=%d,a=%x)\n", dmanr, a);
#पूर्ण_अगर

  dma_device_address[dmanr] = a;
पूर्ण

/*
 * NOTE 2: "count" represents _bytes_.
 */
अटल __अंतरभूत__ व्योम set_dma_count(अचिन्हित पूर्णांक dmanr, अचिन्हित पूर्णांक count)
अणु
  अस्थिर अचिन्हित लघु *dmawp;

#अगर_घोषित DMA_DEBUG
  prपूर्णांकk("set_dma_count(dmanr=%d,count=%d)\n", dmanr, count);
#पूर्ण_अगर

  dmawp = (अचिन्हित लघु *) dma_base_addr[dmanr];
  dmawp[MCFDMA_BCR] = (अचिन्हित लघु)count;
पूर्ण

/*
 * Get DMA residue count. After a DMA transfer, this
 * should वापस zero. Reading this जबतक a DMA transfer is
 * still in progress will वापस unpredictable results.
 * Otherwise, it वापसs the number of _bytes_ left to transfer.
 */
अटल __अंतरभूत__ पूर्णांक get_dma_residue(अचिन्हित पूर्णांक dmanr)
अणु
  अस्थिर अचिन्हित लघु *dmawp;
  अचिन्हित लघु count;

#अगर_घोषित DMA_DEBUG
  prपूर्णांकk("get_dma_residue(dmanr=%d)\n", dmanr);
#पूर्ण_अगर

  dmawp = (अचिन्हित लघु *) dma_base_addr[dmanr];
  count = dmawp[MCFDMA_BCR];
  वापस((पूर्णांक) count);
पूर्ण
#अन्यथा /* CONFIG_M5272 is defined */

/*
 * The MCF5272 DMA controller is very dअगरferent than the controller defined above
 * in terms of रेजिस्टर mapping.  For instance, with the exception of the 16-bit
 * पूर्णांकerrupt रेजिस्टर (IRQ#85, क्रम reference), all of the रेजिस्टरs are 32-bit.
 *
 * The big dअगरference, however, is the lack of device-requested DMA.  All modes
 * are dual address transfer, and there is no 'device' setup or direction bit.
 * You can DMA between a device and memory, between memory and memory, or even between
 * two devices directly, with any combination of incrementing and non-incrementing
 * addresses you choose.  This माला_दो a crimp in distinguishing between the 'device
 * address' set up by set_dma_device_addr.
 *
 * Thereक्रमe, there are two options.  One is to use set_dma_addr and set_dma_device_addr,
 * which will act exactly as above in -- it will look to see अगर the source is set to
 * स्वतःincrement, and अगर so it will make the source use the set_dma_addr value and the
 * destination the set_dma_device_addr value.  Otherwise the source will be set to the
 * set_dma_device_addr value and the destination will get the set_dma_addr value.
 *
 * The other is to use the provided set_dma_src_addr and set_dma_dest_addr functions
 * and make it explicit.  Depending on what you're करोing, one of these two should work
 * क्रम you, but करोn't mix them in the same transfer setup.
 */

/* enable/disable a specअगरic DMA channel */
अटल __अंतरभूत__ व्योम enable_dma(अचिन्हित पूर्णांक dmanr)
अणु
  अस्थिर अचिन्हित पूर्णांक  *dmalp;

#अगर_घोषित DMA_DEBUG
  prपूर्णांकk("enable_dma(dmanr=%d)\n", dmanr);
#पूर्ण_अगर

  dmalp = (अचिन्हित पूर्णांक *) dma_base_addr[dmanr];
  dmalp[MCFDMA_DMR] |= MCFDMA_DMR_EN;
पूर्ण

अटल __अंतरभूत__ व्योम disable_dma(अचिन्हित पूर्णांक dmanr)
अणु
  अस्थिर अचिन्हित पूर्णांक   *dmalp;

#अगर_घोषित DMA_DEBUG
  prपूर्णांकk("disable_dma(dmanr=%d)\n", dmanr);
#पूर्ण_अगर

  dmalp = (अचिन्हित पूर्णांक *) dma_base_addr[dmanr];

  /* Turn off बाह्यal requests, and stop any DMA in progress */
  dmalp[MCFDMA_DMR] &= ~MCFDMA_DMR_EN;
  dmalp[MCFDMA_DMR] |= MCFDMA_DMR_RESET;
पूर्ण

/*
 * Clear the 'DMA Pointer Flip Flop'.
 * Write 0 क्रम LSB/MSB, 1 क्रम MSB/LSB access.
 * Use this once to initialize the FF to a known state.
 * After that, keep track of it. :-)
 * --- In order to करो that, the DMA routines below should ---
 * --- only be used जबतक पूर्णांकerrupts are disabled! ---
 *
 * This is a NOP क्रम ColdFire. Provide a stub क्रम compatibility.
 */
अटल __अंतरभूत__ व्योम clear_dma_ff(अचिन्हित पूर्णांक dmanr)
अणु
पूर्ण

/* set mode (above) क्रम a specअगरic DMA channel */
अटल __अंतरभूत__ व्योम set_dma_mode(अचिन्हित पूर्णांक dmanr, अक्षर mode)
अणु

  अस्थिर अचिन्हित पूर्णांक   *dmalp;
  अस्थिर अचिन्हित लघु *dmawp;

#अगर_घोषित DMA_DEBUG
  prपूर्णांकk("set_dma_mode(dmanr=%d,mode=%d)\n", dmanr, mode);
#पूर्ण_अगर
  dmalp = (अचिन्हित पूर्णांक *) dma_base_addr[dmanr];
  dmawp = (अचिन्हित लघु *) dma_base_addr[dmanr];

  /* Clear config errors */
  dmalp[MCFDMA_DMR] |= MCFDMA_DMR_RESET;

  /* Set command रेजिस्टर */
  dmalp[MCFDMA_DMR] =
    MCFDMA_DMR_RQM_DUAL |         /* Mandatory Request Mode setting */
    MCFDMA_DMR_DSTT_SD  |         /* Set up addressing types; set to supervisor-data. */
    MCFDMA_DMR_SRCT_SD  |         /* Set up addressing types; set to supervisor-data. */
    /* source अटल-address-mode */
    ((mode & DMA_MODE_SRC_SA_BIT) ? MCFDMA_DMR_SRCM_SA : MCFDMA_DMR_SRCM_IA) |
    /* dest अटल-address-mode */
    ((mode & DMA_MODE_DES_SA_BIT) ? MCFDMA_DMR_DSTM_SA : MCFDMA_DMR_DSTM_IA) |
    /* burst, 32 bit, 16 bit or 8 bit transfers are separately configurable on the MCF5272 */
    (((mode & DMA_MODE_SSIZE_MASK) >> DMA_MODE_SSIZE_OFF) << MCFDMA_DMR_DSTS_OFF) |
    (((mode & DMA_MODE_SSIZE_MASK) >> DMA_MODE_SSIZE_OFF) << MCFDMA_DMR_SRCS_OFF);

  dmawp[MCFDMA_सूची] |= MCFDMA_सूची_ASCEN;   /* Enable completion पूर्णांकerrupts */

#अगर_घोषित DEBUG_DMA
  prपूर्णांकk("%s(%d): dmanr=%d DMR[%x]=%x DIR[%x]=%x\n", __खाता__, __LINE__,
	 dmanr, (पूर्णांक) &dmalp[MCFDMA_DMR], dmalp[MCFDMA_DMR],
	 (पूर्णांक) &dmawp[MCFDMA_सूची], dmawp[MCFDMA_सूची]);
#पूर्ण_अगर
पूर्ण

/* Set transfer address क्रम specअगरic DMA channel */
अटल __अंतरभूत__ व्योम set_dma_addr(अचिन्हित पूर्णांक dmanr, अचिन्हित पूर्णांक a)
अणु
  अस्थिर अचिन्हित पूर्णांक   *dmalp;

#अगर_घोषित DMA_DEBUG
  prपूर्णांकk("set_dma_addr(dmanr=%d,a=%x)\n", dmanr, a);
#पूर्ण_अगर

  dmalp = (अचिन्हित पूर्णांक *) dma_base_addr[dmanr];

  /* Determine which address रेजिस्टरs are used क्रम memory/device accesses */
  अगर (dmalp[MCFDMA_DMR] & MCFDMA_DMR_SRCM) अणु
    /* Source incrementing, must be memory */
    dmalp[MCFDMA_DSAR] = a;
    /* Set dest address, must be device */
    dmalp[MCFDMA_DDAR] = dma_device_address[dmanr];
  पूर्ण अन्यथा अणु
    /* Destination incrementing, must be memory */
    dmalp[MCFDMA_DDAR] = a;
    /* Set source address, must be device */
    dmalp[MCFDMA_DSAR] = dma_device_address[dmanr];
  पूर्ण

#अगर_घोषित DEBUG_DMA
  prपूर्णांकk("%s(%d): dmanr=%d DMR[%x]=%x SAR[%x]=%08x DAR[%x]=%08x\n",
	__खाता__, __LINE__, dmanr, (पूर्णांक) &dmalp[MCFDMA_DMR], dmalp[MCFDMA_DMR],
	(पूर्णांक) &dmalp[MCFDMA_DSAR], dmalp[MCFDMA_DSAR],
	(पूर्णांक) &dmalp[MCFDMA_DDAR], dmalp[MCFDMA_DDAR]);
#पूर्ण_अगर
पूर्ण

/*
 * Specअगरic क्रम Coldfire - sets device address.
 * Should be called after the mode set call, and beक्रमe set DMA address.
 */
अटल __अंतरभूत__ व्योम set_dma_device_addr(अचिन्हित पूर्णांक dmanr, अचिन्हित पूर्णांक a)
अणु
#अगर_घोषित DMA_DEBUG
  prपूर्णांकk("set_dma_device_addr(dmanr=%d,a=%x)\n", dmanr, a);
#पूर्ण_अगर

  dma_device_address[dmanr] = a;
पूर्ण

/*
 * NOTE 2: "count" represents _bytes_.
 *
 * NOTE 3: While a 32-bit रेजिस्टर, "count" is only a maximum 24-bit value.
 */
अटल __अंतरभूत__ व्योम set_dma_count(अचिन्हित पूर्णांक dmanr, अचिन्हित पूर्णांक count)
अणु
  अस्थिर अचिन्हित पूर्णांक *dmalp;

#अगर_घोषित DMA_DEBUG
  prपूर्णांकk("set_dma_count(dmanr=%d,count=%d)\n", dmanr, count);
#पूर्ण_अगर

  dmalp = (अचिन्हित पूर्णांक *) dma_base_addr[dmanr];
  dmalp[MCFDMA_DBCR] = count;
पूर्ण

/*
 * Get DMA residue count. After a DMA transfer, this
 * should वापस zero. Reading this जबतक a DMA transfer is
 * still in progress will वापस unpredictable results.
 * Otherwise, it वापसs the number of _bytes_ left to transfer.
 */
अटल __अंतरभूत__ पूर्णांक get_dma_residue(अचिन्हित पूर्णांक dmanr)
अणु
  अस्थिर अचिन्हित पूर्णांक *dmalp;
  अचिन्हित पूर्णांक count;

#अगर_घोषित DMA_DEBUG
  prपूर्णांकk("get_dma_residue(dmanr=%d)\n", dmanr);
#पूर्ण_अगर

  dmalp = (अचिन्हित पूर्णांक *) dma_base_addr[dmanr];
  count = dmalp[MCFDMA_DBCR];
  वापस(count);
पूर्ण

#पूर्ण_अगर /* !defined(CONFIG_M5272) */
#पूर्ण_अगर /* CONFIG_COLDFIRE */

/* it's useless on the m68k, but unक्रमtunately needed by the new
   booपंचांगem allocator (but this should करो it क्रम this) */
#घोषणा MAX_DMA_ADDRESS PAGE_OFFSET

#घोषणा MAX_DMA_CHANNELS 8

बाह्य पूर्णांक request_dma(अचिन्हित पूर्णांक dmanr, स्थिर अक्षर * device_id);	/* reserve a DMA channel */
बाह्य व्योम मुक्त_dma(अचिन्हित पूर्णांक dmanr);	/* release it again */

#अगर_घोषित CONFIG_PCI
बाह्य पूर्णांक isa_dma_bridge_buggy;
#अन्यथा
#घोषणा isa_dma_bridge_buggy    (0)
#पूर्ण_अगर

#पूर्ण_अगर /* _M68K_DMA_H */
