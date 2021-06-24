<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *    Copyright IBM Corp. 2002, 2007
 *    Author(s): Ingo Adlung <adlung@de.ibm.com>
 *		 Cornelia Huck <cornelia.huck@de.ibm.com>
 *		 Arnd Bergmann <arndb@de.ibm.com>
 *		 Peter Oberparleiter <peter.oberparleiter@de.ibm.com>
 */

#अगर_अघोषित _ASM_S390_AIRQ_H
#घोषणा _ASM_S390_AIRQ_H

#समावेश <linux/bit_spinlock.h>
#समावेश <linux/dma-mapping.h>

काष्ठा airq_काष्ठा अणु
	काष्ठा hlist_node list;		/* Handler queueing. */
	व्योम (*handler)(काष्ठा airq_काष्ठा *airq, bool भग्नing);
	u8 *lsi_ptr;			/* Local-Summary-Indicator poपूर्णांकer */
	u8 lsi_mask;			/* Local-Summary-Indicator mask */
	u8 isc;				/* Interrupt-subclass */
	u8 flags;
पूर्ण;

#घोषणा AIRQ_PTR_ALLOCATED	0x01

पूर्णांक रेजिस्टर_adapter_पूर्णांकerrupt(काष्ठा airq_काष्ठा *airq);
व्योम unरेजिस्टर_adapter_पूर्णांकerrupt(काष्ठा airq_काष्ठा *airq);

/* Adapter पूर्णांकerrupt bit vector */
काष्ठा airq_iv अणु
	अचिन्हित दीर्घ *vector;	/* Adapter पूर्णांकerrupt bit vector */
	dma_addr_t vector_dma; /* Adapter पूर्णांकerrupt bit vector dma */
	अचिन्हित दीर्घ *avail;	/* Allocation bit mask क्रम the bit vector */
	अचिन्हित दीर्घ *bitlock;	/* Lock bit mask क्रम the bit vector */
	अचिन्हित दीर्घ *ptr;	/* Poपूर्णांकer associated with each bit */
	अचिन्हित पूर्णांक *data;	/* 32 bit value associated with each bit */
	अचिन्हित दीर्घ bits;	/* Number of bits in the vector */
	अचिन्हित दीर्घ end;	/* Number of highest allocated bit + 1 */
	अचिन्हित दीर्घ flags;	/* Allocation flags */
	spinlock_t lock;	/* Lock to protect alloc & मुक्त */
पूर्ण;

#घोषणा AIRQ_IV_ALLOC		1	/* Use an allocation bit mask */
#घोषणा AIRQ_IV_BITLOCK		2	/* Allocate the lock bit mask */
#घोषणा AIRQ_IV_PTR		4	/* Allocate the ptr array */
#घोषणा AIRQ_IV_DATA		8	/* Allocate the data array */
#घोषणा AIRQ_IV_CACHELINE	16	/* Cacheline alignment क्रम the vector */

काष्ठा airq_iv *airq_iv_create(अचिन्हित दीर्घ bits, अचिन्हित दीर्घ flags);
व्योम airq_iv_release(काष्ठा airq_iv *iv);
अचिन्हित दीर्घ airq_iv_alloc(काष्ठा airq_iv *iv, अचिन्हित दीर्घ num);
व्योम airq_iv_मुक्त(काष्ठा airq_iv *iv, अचिन्हित दीर्घ bit, अचिन्हित दीर्घ num);
अचिन्हित दीर्घ airq_iv_scan(काष्ठा airq_iv *iv, अचिन्हित दीर्घ start,
			   अचिन्हित दीर्घ end);

अटल अंतरभूत अचिन्हित दीर्घ airq_iv_alloc_bit(काष्ठा airq_iv *iv)
अणु
	वापस airq_iv_alloc(iv, 1);
पूर्ण

अटल अंतरभूत व्योम airq_iv_मुक्त_bit(काष्ठा airq_iv *iv, अचिन्हित दीर्घ bit)
अणु
	airq_iv_मुक्त(iv, bit, 1);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ airq_iv_end(काष्ठा airq_iv *iv)
अणु
	वापस iv->end;
पूर्ण

अटल अंतरभूत व्योम airq_iv_lock(काष्ठा airq_iv *iv, अचिन्हित दीर्घ bit)
अणु
	स्थिर अचिन्हित दीर्घ be_to_le = BITS_PER_LONG - 1;
	bit_spin_lock(bit ^ be_to_le, iv->bitlock);
पूर्ण

अटल अंतरभूत व्योम airq_iv_unlock(काष्ठा airq_iv *iv, अचिन्हित दीर्घ bit)
अणु
	स्थिर अचिन्हित दीर्घ be_to_le = BITS_PER_LONG - 1;
	bit_spin_unlock(bit ^ be_to_le, iv->bitlock);
पूर्ण

अटल अंतरभूत व्योम airq_iv_set_data(काष्ठा airq_iv *iv, अचिन्हित दीर्घ bit,
				    अचिन्हित पूर्णांक data)
अणु
	iv->data[bit] = data;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक airq_iv_get_data(काष्ठा airq_iv *iv,
					    अचिन्हित दीर्घ bit)
अणु
	वापस iv->data[bit];
पूर्ण

अटल अंतरभूत व्योम airq_iv_set_ptr(काष्ठा airq_iv *iv, अचिन्हित दीर्घ bit,
				   अचिन्हित दीर्घ ptr)
अणु
	iv->ptr[bit] = ptr;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ airq_iv_get_ptr(काष्ठा airq_iv *iv,
					    अचिन्हित दीर्घ bit)
अणु
	वापस iv->ptr[bit];
पूर्ण

#पूर्ण_अगर /* _ASM_S390_AIRQ_H */
