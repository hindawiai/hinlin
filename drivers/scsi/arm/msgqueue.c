<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/drivers/acorn/scsi/msgqueue.c
 *
 *  Copyright (C) 1997-1998 Russell King
 *
 *  message queue handling
 */
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/init.h>

#समावेश "msgqueue.h"

/*
 * Function: काष्ठा msgqueue_entry *mqe_alloc(MsgQueue_t *msgq)
 * Purpose : Allocate a message queue entry
 * Params  : msgq - message queue to claim entry क्रम
 * Returns : message queue entry or शून्य.
 */
अटल काष्ठा msgqueue_entry *mqe_alloc(MsgQueue_t *msgq)
अणु
	काष्ठा msgqueue_entry *mq;

	अगर ((mq = msgq->मुक्त) != शून्य)
		msgq->मुक्त = mq->next;

	वापस mq;
पूर्ण

/*
 * Function: व्योम mqe_मुक्त(MsgQueue_t *msgq, काष्ठा msgqueue_entry *mq)
 * Purpose : मुक्त a message queue entry
 * Params  : msgq - message queue to मुक्त entry from
 *	     mq   - message queue entry to मुक्त
 */
अटल व्योम mqe_मुक्त(MsgQueue_t *msgq, काष्ठा msgqueue_entry *mq)
अणु
	अगर (mq) अणु
		mq->next = msgq->मुक्त;
		msgq->मुक्त = mq;
	पूर्ण
पूर्ण

/*
 * Function: व्योम msgqueue_initialise(MsgQueue_t *msgq)
 * Purpose : initialise a message queue
 * Params  : msgq - queue to initialise
 */
व्योम msgqueue_initialise(MsgQueue_t *msgq)
अणु
	पूर्णांक i;

	msgq->qe = शून्य;
	msgq->मुक्त = &msgq->entries[0];

	क्रम (i = 0; i < NR_MESSAGES; i++)
		msgq->entries[i].next = &msgq->entries[i + 1];

	msgq->entries[NR_MESSAGES - 1].next = शून्य;
पूर्ण


/*
 * Function: व्योम msgqueue_मुक्त(MsgQueue_t *msgq)
 * Purpose : मुक्त a queue
 * Params  : msgq - queue to मुक्त
 */
व्योम msgqueue_मुक्त(MsgQueue_t *msgq)
अणु
पूर्ण

/*
 * Function: पूर्णांक msgqueue_msglength(MsgQueue_t *msgq)
 * Purpose : calculate the total length of all messages on the message queue
 * Params  : msgq - queue to examine
 * Returns : number of bytes of messages in queue
 */
पूर्णांक msgqueue_msglength(MsgQueue_t *msgq)
अणु
	काष्ठा msgqueue_entry *mq = msgq->qe;
	पूर्णांक length = 0;

	क्रम (mq = msgq->qe; mq; mq = mq->next)
		length += mq->msg.length;

	वापस length;
पूर्ण

/*
 * Function: काष्ठा message *msgqueue_geपंचांगsg(MsgQueue_t *msgq, पूर्णांक msgno)
 * Purpose : वापस a message
 * Params  : msgq   - queue to obtain message from
 *	   : msgno  - message number
 * Returns : poपूर्णांकer to message string, or शून्य
 */
काष्ठा message *msgqueue_geपंचांगsg(MsgQueue_t *msgq, पूर्णांक msgno)
अणु
	काष्ठा msgqueue_entry *mq;

	क्रम (mq = msgq->qe; mq && msgno; mq = mq->next, msgno--);

	वापस mq ? &mq->msg : शून्य;
पूर्ण

/*
 * Function: पूर्णांक msgqueue_addmsg(MsgQueue_t *msgq, पूर्णांक length, ...)
 * Purpose : add a message onto a message queue
 * Params  : msgq   - queue to add message on
 *	     length - length of message
 *	     ...    - message bytes
 * Returns : != 0 अगर successful
 */
पूर्णांक msgqueue_addmsg(MsgQueue_t *msgq, पूर्णांक length, ...)
अणु
	काष्ठा msgqueue_entry *mq = mqe_alloc(msgq);
	बहु_सूची ap;

	अगर (mq) अणु
		काष्ठा msgqueue_entry **mqp;
		पूर्णांक i;

		बहु_शुरू(ap, length);
		क्रम (i = 0; i < length; i++)
			mq->msg.msg[i] = बहु_तर्क(ap, अचिन्हित पूर्णांक);
		बहु_पूर्ण(ap);

		mq->msg.length = length;
		mq->msg.fअगरo = 0;
		mq->next = शून्य;

		mqp = &msgq->qe;
		जबतक (*mqp)
			mqp = &(*mqp)->next;

		*mqp = mq;
	पूर्ण

	वापस mq != शून्य;
पूर्ण

/*
 * Function: व्योम msgqueue_flush(MsgQueue_t *msgq)
 * Purpose : flush all messages from message queue
 * Params  : msgq - queue to flush
 */
व्योम msgqueue_flush(MsgQueue_t *msgq)
अणु
	काष्ठा msgqueue_entry *mq, *mqnext;

	क्रम (mq = msgq->qe; mq; mq = mqnext) अणु
		mqnext = mq->next;
		mqe_मुक्त(msgq, mq);
	पूर्ण
	msgq->qe = शून्य;
पूर्ण

EXPORT_SYMBOL(msgqueue_initialise);
EXPORT_SYMBOL(msgqueue_मुक्त);
EXPORT_SYMBOL(msgqueue_msglength);
EXPORT_SYMBOL(msgqueue_geपंचांगsg);
EXPORT_SYMBOL(msgqueue_addmsg);
EXPORT_SYMBOL(msgqueue_flush);

MODULE_AUTHOR("Russell King");
MODULE_DESCRIPTION("SCSI message queue handling");
MODULE_LICENSE("GPL");
