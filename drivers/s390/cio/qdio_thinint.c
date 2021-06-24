<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright IBM Corp. 2000, 2009
 * Author(s): Utz Bacher <utz.bacher@de.ibm.com>
 *	      Cornelia Huck <cornelia.huck@de.ibm.com>
 *	      Jan Glauber <jang@linux.vnet.ibm.com>
 */
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/atomic.h>
#समावेश <linux/rculist.h>

#समावेश <यंत्र/debug.h>
#समावेश <यंत्र/qdपन.स>
#समावेश <यंत्र/airq.h>
#समावेश <यंत्र/isc.h>

#समावेश "cio.h"
#समावेश "ioasm.h"
#समावेश "qdio.h"
#समावेश "qdio_debug.h"

/*
 * Restriction: only 63 iqdio subchannels would have its own indicator,
 * after that, subsequent subchannels share one indicator
 */
#घोषणा TIQDIO_NR_NONSHARED_IND		63
#घोषणा TIQDIO_NR_INDICATORS		(TIQDIO_NR_NONSHARED_IND + 1)
#घोषणा TIQDIO_SHARED_IND		63

/* device state change indicators */
काष्ठा indicator_t अणु
	u32 ind;	/* u32 because of compare-and-swap perक्रमmance */
	atomic_t count; /* use count, 0 or 1 क्रम non-shared indicators */
पूर्ण;

/* list of thin पूर्णांकerrupt input queues */
अटल LIST_HEAD(tiq_list);
अटल DEFINE_MUTEX(tiq_list_lock);

अटल काष्ठा indicator_t *q_indicators;

u64 last_ai_समय;

/* वापसs addr क्रम the device state change indicator */
अटल u32 *get_indicator(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < TIQDIO_NR_NONSHARED_IND; i++)
		अगर (!atomic_cmpxchg(&q_indicators[i].count, 0, 1))
			वापस &q_indicators[i].ind;

	/* use the shared indicator */
	atomic_inc(&q_indicators[TIQDIO_SHARED_IND].count);
	वापस &q_indicators[TIQDIO_SHARED_IND].ind;
पूर्ण

अटल व्योम put_indicator(u32 *addr)
अणु
	काष्ठा indicator_t *ind = container_of(addr, काष्ठा indicator_t, ind);

	अगर (!addr)
		वापस;
	atomic_dec(&ind->count);
पूर्ण

अटल अंतरभूत पूर्णांक references_shared_dsci(काष्ठा qdio_irq *irq_ptr)
अणु
	वापस irq_ptr->dsci == &q_indicators[TIQDIO_SHARED_IND].ind;
पूर्ण

पूर्णांक test_nonshared_ind(काष्ठा qdio_irq *irq_ptr)
अणु
	अगर (!is_thinपूर्णांक_irq(irq_ptr))
		वापस 0;
	अगर (references_shared_dsci(irq_ptr))
		वापस 0;
	अगर (*irq_ptr->dsci)
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

अटल अंतरभूत u32 clear_shared_ind(व्योम)
अणु
	अगर (!atomic_पढ़ो(&q_indicators[TIQDIO_SHARED_IND].count))
		वापस 0;
	वापस xchg(&q_indicators[TIQDIO_SHARED_IND].ind, 0);
पूर्ण

/**
 * tiqdio_thinपूर्णांक_handler - thin पूर्णांकerrupt handler क्रम qdio
 * @airq: poपूर्णांकer to adapter पूर्णांकerrupt descriptor
 * @भग्नing: flag to recognize भग्नing vs. directed पूर्णांकerrupts (unused)
 */
अटल व्योम tiqdio_thinपूर्णांक_handler(काष्ठा airq_काष्ठा *airq, bool भग्नing)
अणु
	u64 irq_समय = S390_lowcore.पूर्णांक_घड़ी;
	u32 si_used = clear_shared_ind();
	काष्ठा qdio_irq *irq;

	last_ai_समय = irq_समय;
	inc_irq_stat(IRQIO_QAI);

	/* protect tiq_list entries, only changed in activate or shutकरोwn */
	rcu_पढ़ो_lock();

	list_क्रम_each_entry_rcu(irq, &tiq_list, entry) अणु
		/* only process queues from changed sets */
		अगर (unlikely(references_shared_dsci(irq))) अणु
			अगर (!si_used)
				जारी;
		पूर्ण अन्यथा अणु
			अगर (!*irq->dsci)
				जारी;

			xchg(irq->dsci, 0);
		पूर्ण

		qdio_deliver_irq(irq);
		irq->last_data_irq_समय = irq_समय;

		QDIO_PERF_STAT_INC(irq, adapter_पूर्णांक);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

अटल काष्ठा airq_काष्ठा tiqdio_airq = अणु
	.handler = tiqdio_thinपूर्णांक_handler,
	.isc = QDIO_AIRQ_ISC,
पूर्ण;

अटल पूर्णांक set_subchannel_ind(काष्ठा qdio_irq *irq_ptr, पूर्णांक reset)
अणु
	काष्ठा chsc_scssc_area *scssc = (व्योम *)irq_ptr->chsc_page;
	u64 summary_indicator_addr, subchannel_indicator_addr;
	पूर्णांक rc;

	अगर (reset) अणु
		summary_indicator_addr = 0;
		subchannel_indicator_addr = 0;
	पूर्ण अन्यथा अणु
		summary_indicator_addr = virt_to_phys(tiqdio_airq.lsi_ptr);
		subchannel_indicator_addr = virt_to_phys(irq_ptr->dsci);
	पूर्ण

	rc = chsc_sadc(irq_ptr->schid, scssc, summary_indicator_addr,
		       subchannel_indicator_addr, tiqdio_airq.isc);
	अगर (rc) अणु
		DBF_ERROR("%4x SSI r:%4x", irq_ptr->schid.sch_no,
			  scssc->response.code);
		जाओ out;
	पूर्ण

	DBF_EVENT("setscind");
	DBF_HEX(&summary_indicator_addr, माप(summary_indicator_addr));
	DBF_HEX(&subchannel_indicator_addr, माप(subchannel_indicator_addr));
out:
	वापस rc;
पूर्ण

पूर्णांक qdio_establish_thinपूर्णांक(काष्ठा qdio_irq *irq_ptr)
अणु
	पूर्णांक rc;

	अगर (!is_thinपूर्णांक_irq(irq_ptr))
		वापस 0;

	irq_ptr->dsci = get_indicator();
	DBF_HEX(&irq_ptr->dsci, माप(व्योम *));

	rc = set_subchannel_ind(irq_ptr, 0);
	अगर (rc) अणु
		put_indicator(irq_ptr->dsci);
		वापस rc;
	पूर्ण

	mutex_lock(&tiq_list_lock);
	list_add_rcu(&irq_ptr->entry, &tiq_list);
	mutex_unlock(&tiq_list_lock);
	वापस 0;
पूर्ण

व्योम qdio_shutकरोwn_thinपूर्णांक(काष्ठा qdio_irq *irq_ptr)
अणु
	अगर (!is_thinपूर्णांक_irq(irq_ptr))
		वापस;

	mutex_lock(&tiq_list_lock);
	list_del_rcu(&irq_ptr->entry);
	mutex_unlock(&tiq_list_lock);
	synchronize_rcu();

	/* reset adapter पूर्णांकerrupt indicators */
	set_subchannel_ind(irq_ptr, 1);
	put_indicator(irq_ptr->dsci);
पूर्ण

पूर्णांक __init qdio_thinपूर्णांक_init(व्योम)
अणु
	पूर्णांक rc;

	q_indicators = kसुस्मृति(TIQDIO_NR_INDICATORS, माप(काष्ठा indicator_t),
			       GFP_KERNEL);
	अगर (!q_indicators)
		वापस -ENOMEM;

	rc = रेजिस्टर_adapter_पूर्णांकerrupt(&tiqdio_airq);
	अगर (rc) अणु
		DBF_EVENT("RTI:%x", rc);
		kमुक्त(q_indicators);
		वापस rc;
	पूर्ण
	वापस 0;
पूर्ण

व्योम __निकास qdio_thinपूर्णांक_निकास(व्योम)
अणु
	WARN_ON(!list_empty(&tiq_list));
	unरेजिस्टर_adapter_पूर्णांकerrupt(&tiqdio_airq);
	kमुक्त(q_indicators);
पूर्ण
