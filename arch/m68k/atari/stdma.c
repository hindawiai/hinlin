<शैली गुरु>
/*
 *  linux/arch/m68k/atari/sपंचांगda.c
 *
 *  Copyright (C) 1994 Roman Hodek
 *
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 */


/* This file contains some function क्रम controlling the access to the  */
/* ST-DMA chip that may be shared between devices. Currently we have:  */
/*   TT:     Floppy and ACSI bus                                       */
/*   Falcon: Floppy and SCSI                                           */
/*                                                                     */
/* The controlling functions set up a रुको queue क्रम access to the     */
/* ST-DMA chip. Callers to stdma_lock() that cannot granted access are */
/* put onto a queue and waked up later अगर the owner calls              */
/* stdma_release(). Additionally, the caller gives his पूर्णांकerrupt       */
/* service routine to stdma_lock().                                    */
/*                                                                     */
/* On the Falcon, the IDE bus uses just the ACSI/Floppy पूर्णांकerrupt, but */
/* not the ST-DMA chip itself. So falhd.c needs not to lock the        */
/* chip. The पूर्णांकerrupt is routed to falhd.c अगर IDE is configured, the  */
/* model is a Falcon and the पूर्णांकerrupt was caused by the HD controller */
/* (can be determined by looking at its status रेजिस्टर).              */


#समावेश <linux/types.h>
#समावेश <linux/kdev_t.h>
#समावेश <linux/genhd.h>
#समावेश <linux/sched.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/रुको.h>
#समावेश <linux/module.h>

#समावेश <यंत्र/atari_stdma.h>
#समावेश <यंत्र/atariपूर्णांकs.h>
#समावेश <यंत्र/atarihw.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>

अटल पूर्णांक stdma_locked;			/* the semaphore */
						/* पूर्णांक func to be called */
अटल irq_handler_t stdma_isr;
अटल व्योम *stdma_isr_data;			/* data passed to isr */
अटल DECLARE_WAIT_QUEUE_HEAD(stdma_रुको);	/* रुको queue क्रम ST-DMA */




/***************************** Prototypes *****************************/

अटल irqवापस_t stdma_पूर्णांक (पूर्णांक irq, व्योम *dummy);

/************************* End of Prototypes **************************/


/**
 * stdma_try_lock - attempt to acquire ST DMA पूर्णांकerrupt "lock"
 * @handler: पूर्णांकerrupt handler to use after acquisition
 *
 * Returns !0 अगर lock was acquired; otherwise 0.
 */

पूर्णांक stdma_try_lock(irq_handler_t handler, व्योम *data)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	अगर (stdma_locked) अणु
		local_irq_restore(flags);
		वापस 0;
	पूर्ण

	stdma_locked   = 1;
	stdma_isr      = handler;
	stdma_isr_data = data;
	local_irq_restore(flags);
	वापस 1;
पूर्ण
EXPORT_SYMBOL(stdma_try_lock);


/*
 * Function: व्योम stdma_lock( isrfunc isr, व्योम *data )
 *
 * Purpose: Tries to get a lock on the ST-DMA chip that is used by more
 *   then one device driver. Waits on stdma_रुको until lock is मुक्त.
 *   stdma_lock() may not be called from an पूर्णांकerrupt! You have to
 *   get the lock in your मुख्य routine and release it when your
 *   request is finished.
 *
 * Inमाला_दो: A पूर्णांकerrupt function that is called until the lock is
 *   released.
 *
 * Returns: nothing
 *
 */

व्योम stdma_lock(irq_handler_t handler, व्योम *data)
अणु
	/* Since the DMA is used क्रम file प्रणाली purposes, we
	 have to sleep unपूर्णांकerruptible (there may be locked
	 buffers) */
	रुको_event(stdma_रुको, stdma_try_lock(handler, data));
पूर्ण
EXPORT_SYMBOL(stdma_lock);


/*
 * Function: व्योम stdma_release( व्योम )
 *
 * Purpose: Releases the lock on the ST-DMA chip.
 *
 * Inमाला_दो: none
 *
 * Returns: nothing
 *
 */

व्योम stdma_release(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);

	stdma_locked   = 0;
	stdma_isr      = शून्य;
	stdma_isr_data = शून्य;
	wake_up(&stdma_रुको);

	local_irq_restore(flags);
पूर्ण
EXPORT_SYMBOL(stdma_release);


/**
 * stdma_is_locked_by - allow lock holder to check whether it needs to release.
 * @handler: पूर्णांकerrupt handler previously used to acquire lock.
 *
 * Returns !0 अगर locked क्रम the given handler; 0 otherwise.
 */

पूर्णांक stdma_is_locked_by(irq_handler_t handler)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक result;

	local_irq_save(flags);
	result = stdma_locked && (stdma_isr == handler);
	local_irq_restore(flags);

	वापस result;
पूर्ण
EXPORT_SYMBOL(stdma_is_locked_by);


/*
 * Function: पूर्णांक stdma_islocked( व्योम )
 *
 * Purpose: Check अगर the ST-DMA is currently locked.
 * Note: Returned status is only valid अगर पूर्णांकs are disabled जबतक calling and
 *       as दीर्घ as they reमुख्य disabled.
 *       If called with पूर्णांकs enabled, status can change only from locked to
 *       unlocked, because पूर्णांकs may not lock the ST-DMA.
 *
 * Inमाला_दो: none
 *
 * Returns: != 0 अगर locked, 0 otherwise
 *
 */

पूर्णांक stdma_islocked(व्योम)
अणु
	वापस stdma_locked;
पूर्ण
EXPORT_SYMBOL(stdma_islocked);


/*
 * Function: व्योम stdma_init( व्योम )
 *
 * Purpose: Initialize the ST-DMA chip access controlling.
 *   It sets up the पूर्णांकerrupt and its service routine. The पूर्णांक is रेजिस्टरed
 *   as slow पूर्णांक, client devices have to live with that (no problem
 *   currently).
 *
 * Inमाला_दो: none
 *
 * Return: nothing
 *
 */

व्योम __init stdma_init(व्योम)
अणु
	stdma_isr = शून्य;
	अगर (request_irq(IRQ_MFP_FDC, stdma_पूर्णांक, IRQF_SHARED,
			"ST-DMA floppy,ACSI,IDE,Falcon-SCSI", stdma_पूर्णांक))
		pr_err("Couldn't register ST-DMA interrupt\n");
पूर्ण


/*
 * Function: व्योम stdma_पूर्णांक()
 *
 * Purpose: The पूर्णांकerrupt routine क्रम the ST-DMA. It calls the isr
 *   रेजिस्टरed by stdma_lock().
 *
 */

अटल irqवापस_t stdma_पूर्णांक(पूर्णांक irq, व्योम *dummy)
अणु
  अगर (stdma_isr)
      (*stdma_isr)(irq, stdma_isr_data);
  वापस IRQ_HANDLED;
पूर्ण
