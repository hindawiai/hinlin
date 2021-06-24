<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *    Support क्रम adapter पूर्णांकerruptions
 *
 *    Copyright IBM Corp. 1999, 2007
 *    Author(s): Ingo Adlung <adlung@de.ibm.com>
 *		 Cornelia Huck <cornelia.huck@de.ibm.com>
 *		 Arnd Bergmann <arndb@de.ibm.com>
 *		 Peter Oberparleiter <peter.oberparleiter@de.ibm.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/irq.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/rculist.h>
#समावेश <linux/slab.h>
#समावेश <linux/dmapool.h>

#समावेश <यंत्र/airq.h>
#समावेश <यंत्र/isc.h>
#समावेश <यंत्र/cपन.स>

#समावेश "cio.h"
#समावेश "cio_debug.h"
#समावेश "ioasm.h"

अटल DEFINE_SPINLOCK(airq_lists_lock);
अटल काष्ठा hlist_head airq_lists[MAX_ISC+1];

अटल काष्ठा dma_pool *airq_iv_cache;

/**
 * रेजिस्टर_adapter_पूर्णांकerrupt() - रेजिस्टर adapter पूर्णांकerrupt handler
 * @airq: poपूर्णांकer to adapter पूर्णांकerrupt descriptor
 *
 * Returns 0 on success, or -EINVAL.
 */
पूर्णांक रेजिस्टर_adapter_पूर्णांकerrupt(काष्ठा airq_काष्ठा *airq)
अणु
	अक्षर dbf_txt[32];

	अगर (!airq->handler || airq->isc > MAX_ISC)
		वापस -EINVAL;
	अगर (!airq->lsi_ptr) अणु
		airq->lsi_ptr = kzalloc(1, GFP_KERNEL);
		अगर (!airq->lsi_ptr)
			वापस -ENOMEM;
		airq->flags |= AIRQ_PTR_ALLOCATED;
	पूर्ण
	अगर (!airq->lsi_mask)
		airq->lsi_mask = 0xff;
	snम_लिखो(dbf_txt, माप(dbf_txt), "rairq:%p", airq);
	CIO_TRACE_EVENT(4, dbf_txt);
	isc_रेजिस्टर(airq->isc);
	spin_lock(&airq_lists_lock);
	hlist_add_head_rcu(&airq->list, &airq_lists[airq->isc]);
	spin_unlock(&airq_lists_lock);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(रेजिस्टर_adapter_पूर्णांकerrupt);

/**
 * unरेजिस्टर_adapter_पूर्णांकerrupt - unरेजिस्टर adapter पूर्णांकerrupt handler
 * @airq: poपूर्णांकer to adapter पूर्णांकerrupt descriptor
 */
व्योम unरेजिस्टर_adapter_पूर्णांकerrupt(काष्ठा airq_काष्ठा *airq)
अणु
	अक्षर dbf_txt[32];

	अगर (hlist_unhashed(&airq->list))
		वापस;
	snम_लिखो(dbf_txt, माप(dbf_txt), "urairq:%p", airq);
	CIO_TRACE_EVENT(4, dbf_txt);
	spin_lock(&airq_lists_lock);
	hlist_del_rcu(&airq->list);
	spin_unlock(&airq_lists_lock);
	synchronize_rcu();
	isc_unरेजिस्टर(airq->isc);
	अगर (airq->flags & AIRQ_PTR_ALLOCATED) अणु
		kमुक्त(airq->lsi_ptr);
		airq->lsi_ptr = शून्य;
		airq->flags &= ~AIRQ_PTR_ALLOCATED;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(unरेजिस्टर_adapter_पूर्णांकerrupt);

अटल irqवापस_t करो_airq_पूर्णांकerrupt(पूर्णांक irq, व्योम *dummy)
अणु
	काष्ठा tpi_info *tpi_info;
	काष्ठा airq_काष्ठा *airq;
	काष्ठा hlist_head *head;

	set_cpu_flag(CIF_NOHZ_DELAY);
	tpi_info = (काष्ठा tpi_info *) &get_irq_regs()->पूर्णांक_code;
	trace_s390_cio_adapter_पूर्णांक(tpi_info);
	head = &airq_lists[tpi_info->isc];
	rcu_पढ़ो_lock();
	hlist_क्रम_each_entry_rcu(airq, head, list)
		अगर ((*airq->lsi_ptr & airq->lsi_mask) != 0)
			airq->handler(airq, !tpi_info->directed_irq);
	rcu_पढ़ो_unlock();

	वापस IRQ_HANDLED;
पूर्ण

व्योम __init init_airq_पूर्णांकerrupts(व्योम)
अणु
	irq_set_chip_and_handler(THIN_INTERRUPT,
				 &dummy_irq_chip, handle_percpu_irq);
	अगर (request_irq(THIN_INTERRUPT, करो_airq_पूर्णांकerrupt, 0, "AIO", शून्य))
		panic("Failed to register AIO interrupt\n");
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ iv_size(अचिन्हित दीर्घ bits)
अणु
	वापस BITS_TO_LONGS(bits) * माप(अचिन्हित दीर्घ);
पूर्ण

/**
 * airq_iv_create - create an पूर्णांकerrupt vector
 * @bits: number of bits in the पूर्णांकerrupt vector
 * @flags: allocation flags
 *
 * Returns a poपूर्णांकer to an पूर्णांकerrupt vector काष्ठाure
 */
काष्ठा airq_iv *airq_iv_create(अचिन्हित दीर्घ bits, अचिन्हित दीर्घ flags)
अणु
	काष्ठा airq_iv *iv;
	अचिन्हित दीर्घ size;

	iv = kzalloc(माप(*iv), GFP_KERNEL);
	अगर (!iv)
		जाओ out;
	iv->bits = bits;
	iv->flags = flags;
	size = iv_size(bits);

	अगर (flags & AIRQ_IV_CACHELINE) अणु
		अगर ((cache_line_size() * BITS_PER_BYTE) < bits
				|| !airq_iv_cache)
			जाओ out_मुक्त;

		iv->vector = dma_pool_zalloc(airq_iv_cache, GFP_KERNEL,
					     &iv->vector_dma);
		अगर (!iv->vector)
			जाओ out_मुक्त;
	पूर्ण अन्यथा अणु
		iv->vector = cio_dma_zalloc(size);
		अगर (!iv->vector)
			जाओ out_मुक्त;
	पूर्ण
	अगर (flags & AIRQ_IV_ALLOC) अणु
		iv->avail = kदो_स्मृति(size, GFP_KERNEL);
		अगर (!iv->avail)
			जाओ out_मुक्त;
		स_रखो(iv->avail, 0xff, size);
		iv->end = 0;
	पूर्ण अन्यथा
		iv->end = bits;
	अगर (flags & AIRQ_IV_BITLOCK) अणु
		iv->bitlock = kzalloc(size, GFP_KERNEL);
		अगर (!iv->bitlock)
			जाओ out_मुक्त;
	पूर्ण
	अगर (flags & AIRQ_IV_PTR) अणु
		size = bits * माप(अचिन्हित दीर्घ);
		iv->ptr = kzalloc(size, GFP_KERNEL);
		अगर (!iv->ptr)
			जाओ out_मुक्त;
	पूर्ण
	अगर (flags & AIRQ_IV_DATA) अणु
		size = bits * माप(अचिन्हित पूर्णांक);
		iv->data = kzalloc(size, GFP_KERNEL);
		अगर (!iv->data)
			जाओ out_मुक्त;
	पूर्ण
	spin_lock_init(&iv->lock);
	वापस iv;

out_मुक्त:
	kमुक्त(iv->ptr);
	kमुक्त(iv->bitlock);
	kमुक्त(iv->avail);
	अगर (iv->flags & AIRQ_IV_CACHELINE && iv->vector)
		dma_pool_मुक्त(airq_iv_cache, iv->vector, iv->vector_dma);
	अन्यथा
		cio_dma_मुक्त(iv->vector, size);
	kमुक्त(iv);
out:
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(airq_iv_create);

/**
 * airq_iv_release - release an पूर्णांकerrupt vector
 * @iv: poपूर्णांकer to पूर्णांकerrupt vector काष्ठाure
 */
व्योम airq_iv_release(काष्ठा airq_iv *iv)
अणु
	kमुक्त(iv->data);
	kमुक्त(iv->ptr);
	kमुक्त(iv->bitlock);
	अगर (iv->flags & AIRQ_IV_CACHELINE)
		dma_pool_मुक्त(airq_iv_cache, iv->vector, iv->vector_dma);
	अन्यथा
		cio_dma_मुक्त(iv->vector, iv_size(iv->bits));
	kमुक्त(iv->avail);
	kमुक्त(iv);
पूर्ण
EXPORT_SYMBOL(airq_iv_release);

/**
 * airq_iv_alloc - allocate irq bits from an पूर्णांकerrupt vector
 * @iv: poपूर्णांकer to an पूर्णांकerrupt vector काष्ठाure
 * @num: number of consecutive irq bits to allocate
 *
 * Returns the bit number of the first irq in the allocated block of irqs,
 * or -1UL अगर no bit is available or the AIRQ_IV_ALLOC flag has not been
 * specअगरied
 */
अचिन्हित दीर्घ airq_iv_alloc(काष्ठा airq_iv *iv, अचिन्हित दीर्घ num)
अणु
	अचिन्हित दीर्घ bit, i, flags;

	अगर (!iv->avail || num == 0)
		वापस -1UL;
	spin_lock_irqsave(&iv->lock, flags);
	bit = find_first_bit_inv(iv->avail, iv->bits);
	जबतक (bit + num <= iv->bits) अणु
		क्रम (i = 1; i < num; i++)
			अगर (!test_bit_inv(bit + i, iv->avail))
				अवरोध;
		अगर (i >= num) अणु
			/* Found a suitable block of irqs */
			क्रम (i = 0; i < num; i++)
				clear_bit_inv(bit + i, iv->avail);
			अगर (bit + num >= iv->end)
				iv->end = bit + num + 1;
			अवरोध;
		पूर्ण
		bit = find_next_bit_inv(iv->avail, iv->bits, bit + i + 1);
	पूर्ण
	अगर (bit + num > iv->bits)
		bit = -1UL;
	spin_unlock_irqrestore(&iv->lock, flags);
	वापस bit;
पूर्ण
EXPORT_SYMBOL(airq_iv_alloc);

/**
 * airq_iv_मुक्त - मुक्त irq bits of an पूर्णांकerrupt vector
 * @iv: poपूर्णांकer to पूर्णांकerrupt vector काष्ठाure
 * @bit: number of the first irq bit to मुक्त
 * @num: number of consecutive irq bits to मुक्त
 */
व्योम airq_iv_मुक्त(काष्ठा airq_iv *iv, अचिन्हित दीर्घ bit, अचिन्हित दीर्घ num)
अणु
	अचिन्हित दीर्घ i, flags;

	अगर (!iv->avail || num == 0)
		वापस;
	spin_lock_irqsave(&iv->lock, flags);
	क्रम (i = 0; i < num; i++) अणु
		/* Clear (possibly left over) पूर्णांकerrupt bit */
		clear_bit_inv(bit + i, iv->vector);
		/* Make the bit positions available again */
		set_bit_inv(bit + i, iv->avail);
	पूर्ण
	अगर (bit + num >= iv->end) अणु
		/* Find new end of bit-field */
		जबतक (iv->end > 0 && !test_bit_inv(iv->end - 1, iv->avail))
			iv->end--;
	पूर्ण
	spin_unlock_irqrestore(&iv->lock, flags);
पूर्ण
EXPORT_SYMBOL(airq_iv_मुक्त);

/**
 * airq_iv_scan - scan पूर्णांकerrupt vector क्रम non-zero bits
 * @iv: poपूर्णांकer to पूर्णांकerrupt vector काष्ठाure
 * @start: bit number to start the search
 * @end: bit number to end the search
 *
 * Returns the bit number of the next non-zero पूर्णांकerrupt bit, or
 * -1UL अगर the scan completed without finding any more any non-zero bits.
 */
अचिन्हित दीर्घ airq_iv_scan(काष्ठा airq_iv *iv, अचिन्हित दीर्घ start,
			   अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ bit;

	/* Find non-zero bit starting from 'ivs->next'. */
	bit = find_next_bit_inv(iv->vector, end, start);
	अगर (bit >= end)
		वापस -1UL;
	clear_bit_inv(bit, iv->vector);
	वापस bit;
पूर्ण
EXPORT_SYMBOL(airq_iv_scan);

पूर्णांक __init airq_init(व्योम)
अणु
	airq_iv_cache = dma_pool_create("airq_iv_cache", cio_get_dma_css_dev(),
					cache_line_size(),
					cache_line_size(), PAGE_SIZE);
	अगर (!airq_iv_cache)
		वापस -ENOMEM;
	वापस 0;
पूर्ण
