<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * linux/drivers/अक्षर/hpilo.h
 *
 * Copyright (C) 2008 Hewlett-Packard Development Company, L.P.
 *	David Altobelli <david.altobelli@hp.com>
 */
#अगर_अघोषित __HPILO_H
#घोषणा __HPILO_H

#घोषणा ILO_NAME "hpilo"

/* max number of खोलो channel control blocks per device, hw limited to 32 */
#घोषणा MAX_CCB	       24
/* min number of खोलो channel control blocks per device, hw limited to 32 */
#घोषणा MIN_CCB		8
/* max number of supported devices */
#घोषणा MAX_ILO_DEV	1
/* max number of files */
#घोषणा MAX_OPEN	(MAX_CCB * MAX_ILO_DEV)
/* total रुको समय in usec */
#घोषणा MAX_WAIT_TIME	10000
/* per spin रुको समय in usec */
#घोषणा WAIT_TIME	10
/* spin counter क्रम खोलो/बंद delay */
#घोषणा MAX_WAIT	(MAX_WAIT_TIME / WAIT_TIME)

/*
 * Per device, used to track global memory allocations.
 */
काष्ठा ilo_hwinfo अणु
	/* mmio रेजिस्टरs on device */
	अक्षर __iomem *mmio_vaddr;

	/* करोorbell रेजिस्टरs on device */
	अक्षर __iomem *db_vaddr;

	/* shared memory on device used क्रम channel control blocks */
	अक्षर __iomem *ram_vaddr;

	/* files corresponding to this device */
	काष्ठा ccb_data *ccb_alloc[MAX_CCB];

	काष्ठा pci_dev *ilo_dev;

	/*
	 * खोलो_lock      serializes ccb_cnt during खोलो and बंद
	 * [ irq disabled ]
	 * -> alloc_lock  used when adding/removing/searching ccb_alloc,
	 *                which represents all ccbs खोलो on the device
	 * --> fअगरo_lock  controls access to fअगरo queues shared with hw
	 *
	 * Locks must be taken in this order, but खोलो_lock and alloc_lock
	 * are optional, they करो not need to be held in order to take a
	 * lower level lock.
	 */
	spinlock_t खोलो_lock;
	spinlock_t alloc_lock;
	spinlock_t fअगरo_lock;

	काष्ठा cdev cdev;
पूर्ण;

/* offset from mmio_vaddr क्रम enabling करोorbell पूर्णांकerrupts */
#घोषणा DB_IRQ		0xB2
/* offset from mmio_vaddr क्रम outbound communications */
#घोषणा DB_OUT		0xD4
/* DB_OUT reset bit */
#घोषणा DB_RESET	26

/*
 * Channel control block. Used to manage hardware queues.
 * The क्रमmat must match hw's version.  The hw ccb is 128 bytes,
 * but the context area shouldn't be touched by the driver.
 */
#घोषणा ILOSW_CCB_SZ	64
#घोषणा ILOHW_CCB_SZ 	128
काष्ठा ccb अणु
	जोड़ अणु
		अक्षर *send_fअगरobar;
		u64 send_fअगरobar_pa;
	पूर्ण ccb_u1;
	जोड़ अणु
		अक्षर *send_desc;
		u64 send_desc_pa;
	पूर्ण ccb_u2;
	u64 send_ctrl;

	जोड़ अणु
		अक्षर *recv_fअगरobar;
		u64 recv_fअगरobar_pa;
	पूर्ण ccb_u3;
	जोड़ अणु
		अक्षर *recv_desc;
		u64 recv_desc_pa;
	पूर्ण ccb_u4;
	u64 recv_ctrl;

	जोड़ अणु
		अक्षर __iomem *db_base;
		u64 padding5;
	पूर्ण ccb_u5;

	u64 channel;

	/* unused context area (64 bytes) */
पूर्ण;

/* ccb queue parameters */
#घोषणा SENDQ		1
#घोषणा RECVQ 		2
#घोषणा NR_QENTRY    	4
#घोषणा L2_QENTRY_SZ 	12

/* ccb ctrl bitfields */
#घोषणा CTRL_BITPOS_L2SZ             0
#घोषणा CTRL_BITPOS_FIFOINDEXMASK    4
#घोषणा CTRL_BITPOS_DESCLIMIT        18
#घोषणा CTRL_BITPOS_A                30
#घोषणा CTRL_BITPOS_G                31

/* ccb करोorbell macros */
#घोषणा L2_DB_SIZE		14
#घोषणा ONE_DB_SIZE		(1 << L2_DB_SIZE)

/*
 * Per fd काष्ठाure used to track the ccb allocated to that dev file.
 */
काष्ठा ccb_data अणु
	/* software version of ccb, using भव addrs */
	काष्ठा ccb  driver_ccb;

	/* hardware version of ccb, using physical addrs */
	काष्ठा ccb  ilo_ccb;

	/* hardware ccb is written to this shared mapped device memory */
	काष्ठा ccb __iomem *mapped_ccb;

	/* dma'able memory used क्रम send/recv queues */
	व्योम       *dma_va;
	dma_addr_t  dma_pa;
	माप_प्रकार      dma_size;

	/* poपूर्णांकer to hardware device info */
	काष्ठा ilo_hwinfo *ilo_hw;

	/* queue क्रम this ccb to रुको क्रम recv data */
	रुको_queue_head_t ccb_रुकोq;

	/* usage count, to allow क्रम shared ccb's */
	पूर्णांक	    ccb_cnt;

	/* खोलो wanted exclusive access to this ccb */
	पूर्णांक	    ccb_excl;
पूर्ण;

/*
 * FIFO queue काष्ठाure, shared with hw.
 */
#घोषणा ILO_START_ALIGN	4096
#घोषणा ILO_CACHE_SZ 	 128
काष्ठा fअगरo अणु
	u64 nrents;	/* user requested number of fअगरo entries */
	u64 imask;  /* mask to extract valid fअगरo index */
	u64 merge;	/*  O/C bits to merge in during enqueue operation */
	u64 reset;	/* set to non-zero when the target device resets */
	u8  pad_0[ILO_CACHE_SZ - (माप(u64) * 4)];

	u64 head;
	u8  pad_1[ILO_CACHE_SZ - (माप(u64))];

	u64 tail;
	u8  pad_2[ILO_CACHE_SZ - (माप(u64))];

	u64 fअगरobar[];
पूर्ण;

/* convert between काष्ठा fअगरo, and the fअगरobar, which is saved in the ccb */
#घोषणा FIFOHANDLESIZE (माप(काष्ठा fअगरo))
#घोषणा FIFOBARTOHANDLE(_fअगरo) \
	((काष्ठा fअगरo *)(((अक्षर *)(_fअगरo)) - FIFOHANDLESIZE))

/* the number of qwords to consume from the entry descriptor */
#घोषणा ENTRY_BITPOS_QWORDS      0
/* descriptor index number (within a specअगरied queue) */
#घोषणा ENTRY_BITPOS_DESCRIPTOR  10
/* state bit, fअगरo entry consumed by consumer */
#घोषणा ENTRY_BITPOS_C           22
/* state bit, fअगरo entry is occupied */
#घोषणा ENTRY_BITPOS_O           23

#घोषणा ENTRY_BITS_QWORDS        10
#घोषणा ENTRY_BITS_DESCRIPTOR    12
#घोषणा ENTRY_BITS_C             1
#घोषणा ENTRY_BITS_O             1
#घोषणा ENTRY_BITS_TOTAL	\
	(ENTRY_BITS_C + ENTRY_BITS_O + \
	 ENTRY_BITS_QWORDS + ENTRY_BITS_DESCRIPTOR)

/* extract various entry fields */
#घोषणा ENTRY_MASK ((1 << ENTRY_BITS_TOTAL) - 1)
#घोषणा ENTRY_MASK_C (((1 << ENTRY_BITS_C) - 1) << ENTRY_BITPOS_C)
#घोषणा ENTRY_MASK_O (((1 << ENTRY_BITS_O) - 1) << ENTRY_BITPOS_O)
#घोषणा ENTRY_MASK_QWORDS \
	(((1 << ENTRY_BITS_QWORDS) - 1) << ENTRY_BITPOS_QWORDS)
#घोषणा ENTRY_MASK_DESCRIPTOR \
	(((1 << ENTRY_BITS_DESCRIPTOR) - 1) << ENTRY_BITPOS_DESCRIPTOR)

#घोषणा ENTRY_MASK_NOSTATE (ENTRY_MASK >> (ENTRY_BITS_C + ENTRY_BITS_O))

#पूर्ण_अगर /* __HPILO_H */
