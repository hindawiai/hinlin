<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *   Channel report handling code
 *
 *    Copyright IBM Corp. 2000, 2009
 *    Author(s): Ingo Adlung <adlung@de.ibm.com>,
 *		 Martin Schwidefsky <schwidefsky@de.ibm.com>,
 *		 Cornelia Huck <cornelia.huck@de.ibm.com>,
 *		 Heiko Carstens <heiko.carstens@de.ibm.com>,
 */

#समावेश <linux/mutex.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/init.h>
#समावेश <linux/रुको.h>
#समावेश <यंत्र/crw.h>
#समावेश <यंत्र/ctl_reg.h>
#समावेश "ioasm.h"

अटल DEFINE_MUTEX(crw_handler_mutex);
अटल crw_handler_t crw_handlers[NR_RSCS];
अटल atomic_t crw_nr_req = ATOMIC_INIT(0);
अटल DECLARE_WAIT_QUEUE_HEAD(crw_handler_रुको_q);

/**
 * crw_रेजिस्टर_handler() - रेजिस्टर a channel report word handler
 * @rsc: reporting source code to handle
 * @handler: handler to be रेजिस्टरed
 *
 * Returns %0 on success and a negative error value otherwise.
 */
पूर्णांक crw_रेजिस्टर_handler(पूर्णांक rsc, crw_handler_t handler)
अणु
	पूर्णांक rc = 0;

	अगर ((rsc < 0) || (rsc >= NR_RSCS))
		वापस -EINVAL;
	mutex_lock(&crw_handler_mutex);
	अगर (crw_handlers[rsc])
		rc = -EBUSY;
	अन्यथा
		crw_handlers[rsc] = handler;
	mutex_unlock(&crw_handler_mutex);
	वापस rc;
पूर्ण

/**
 * crw_unरेजिस्टर_handler() - unरेजिस्टर a channel report word handler
 * @rsc: reporting source code to handle
 */
व्योम crw_unरेजिस्टर_handler(पूर्णांक rsc)
अणु
	अगर ((rsc < 0) || (rsc >= NR_RSCS))
		वापस;
	mutex_lock(&crw_handler_mutex);
	crw_handlers[rsc] = शून्य;
	mutex_unlock(&crw_handler_mutex);
पूर्ण

/*
 * Retrieve CRWs and call function to handle event.
 */
अटल पूर्णांक crw_collect_info(व्योम *unused)
अणु
	काष्ठा crw crw[2];
	पूर्णांक ccode, संकेत;
	अचिन्हित पूर्णांक chain;

repeat:
	संकेत = रुको_event_पूर्णांकerruptible(crw_handler_रुको_q,
					  atomic_पढ़ो(&crw_nr_req) > 0);
	अगर (unlikely(संकेत))
		atomic_inc(&crw_nr_req);
	chain = 0;
	जबतक (1) अणु
		crw_handler_t handler;

		अगर (unlikely(chain > 1)) अणु
			काष्ठा crw पंचांगp_crw;

			prपूर्णांकk(KERN_WARNING"%s: Code does not support more "
			       "than two chained crws; please report to "
			       "linux390@de.ibm.com!\n", __func__);
			ccode = stcrw(&पंचांगp_crw);
			prपूर्णांकk(KERN_WARNING"%s: crw reports slct=%d, oflw=%d, "
			       "chn=%d, rsc=%X, anc=%d, erc=%X, rsid=%X\n",
			       __func__, पंचांगp_crw.slct, पंचांगp_crw.oflw,
			       पंचांगp_crw.chn, पंचांगp_crw.rsc, पंचांगp_crw.anc,
			       पंचांगp_crw.erc, पंचांगp_crw.rsid);
			prपूर्णांकk(KERN_WARNING"%s: This was crw number %x in the "
			       "chain\n", __func__, chain);
			अगर (ccode != 0)
				अवरोध;
			chain = पंचांगp_crw.chn ? chain + 1 : 0;
			जारी;
		पूर्ण
		ccode = stcrw(&crw[chain]);
		अगर (ccode != 0)
			अवरोध;
		prपूर्णांकk(KERN_DEBUG "crw_info : CRW reports slct=%d, oflw=%d, "
		       "chn=%d, rsc=%X, anc=%d, erc=%X, rsid=%X\n",
		       crw[chain].slct, crw[chain].oflw, crw[chain].chn,
		       crw[chain].rsc, crw[chain].anc, crw[chain].erc,
		       crw[chain].rsid);
		/* Check क्रम overflows. */
		अगर (crw[chain].oflw) अणु
			पूर्णांक i;

			pr_debug("%s: crw overflow detected!\n", __func__);
			mutex_lock(&crw_handler_mutex);
			क्रम (i = 0; i < NR_RSCS; i++) अणु
				अगर (crw_handlers[i])
					crw_handlers[i](शून्य, शून्य, 1);
			पूर्ण
			mutex_unlock(&crw_handler_mutex);
			chain = 0;
			जारी;
		पूर्ण
		अगर (crw[0].chn && !chain) अणु
			chain++;
			जारी;
		पूर्ण
		mutex_lock(&crw_handler_mutex);
		handler = crw_handlers[crw[chain].rsc];
		अगर (handler)
			handler(&crw[0], chain ? &crw[1] : शून्य, 0);
		mutex_unlock(&crw_handler_mutex);
		/* chain is always 0 or 1 here. */
		chain = crw[chain].chn ? chain + 1 : 0;
	पूर्ण
	अगर (atomic_dec_and_test(&crw_nr_req))
		wake_up(&crw_handler_रुको_q);
	जाओ repeat;
	वापस 0;
पूर्ण

व्योम crw_handle_channel_report(व्योम)
अणु
	atomic_inc(&crw_nr_req);
	wake_up(&crw_handler_रुको_q);
पूर्ण

व्योम crw_रुको_क्रम_channel_report(व्योम)
अणु
	crw_handle_channel_report();
	रुको_event(crw_handler_रुको_q, atomic_पढ़ो(&crw_nr_req) == 0);
पूर्ण

/*
 * Machine checks क्रम the channel subप्रणाली must be enabled
 * after the channel subप्रणाली is initialized
 */
अटल पूर्णांक __init crw_machine_check_init(व्योम)
अणु
	काष्ठा task_काष्ठा *task;

	task = kthपढ़ो_run(crw_collect_info, शून्य, "kmcheck");
	अगर (IS_ERR(task))
		वापस PTR_ERR(task);
	ctl_set_bit(14, 28);	/* enable channel report MCH */
	वापस 0;
पूर्ण
device_initcall(crw_machine_check_init);
