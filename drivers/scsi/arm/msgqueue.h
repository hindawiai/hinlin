<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  linux/drivers/acorn/scsi/msgqueue.h
 *
 *  Copyright (C) 1997 Russell King
 *
 *  message queue handling
 */
#अगर_अघोषित MSGQUEUE_H
#घोषणा MSGQUEUE_H

काष्ठा message अणु
    अक्षर msg[8];
    पूर्णांक length;
    पूर्णांक fअगरo;
पूर्ण;

काष्ठा msgqueue_entry अणु
    काष्ठा message msg;
    काष्ठा msgqueue_entry *next;
पूर्ण;

#घोषणा NR_MESSAGES 4

प्रकार काष्ठा अणु
    काष्ठा msgqueue_entry *qe;
    काष्ठा msgqueue_entry *मुक्त;
    काष्ठा msgqueue_entry entries[NR_MESSAGES];
पूर्ण MsgQueue_t;

/*
 * Function: व्योम msgqueue_initialise(MsgQueue_t *msgq)
 * Purpose : initialise a message queue
 * Params  : msgq - queue to initialise
 */
बाह्य व्योम msgqueue_initialise(MsgQueue_t *msgq);

/*
 * Function: व्योम msgqueue_मुक्त(MsgQueue_t *msgq)
 * Purpose : मुक्त a queue
 * Params  : msgq - queue to मुक्त
 */
बाह्य व्योम msgqueue_मुक्त(MsgQueue_t *msgq);

/*
 * Function: पूर्णांक msgqueue_msglength(MsgQueue_t *msgq)
 * Purpose : calculate the total length of all messages on the message queue
 * Params  : msgq - queue to examine
 * Returns : number of bytes of messages in queue
 */
बाह्य पूर्णांक msgqueue_msglength(MsgQueue_t *msgq);

/*
 * Function: काष्ठा message *msgqueue_geपंचांगsg(MsgQueue_t *msgq, पूर्णांक msgno)
 * Purpose : वापस a message & its length
 * Params  : msgq   - queue to obtain message from
 *         : msgno  - message number
 * Returns : poपूर्णांकer to message string, or शून्य
 */
बाह्य काष्ठा message *msgqueue_geपंचांगsg(MsgQueue_t *msgq, पूर्णांक msgno);

/*
 * Function: पूर्णांक msgqueue_addmsg(MsgQueue_t *msgq, पूर्णांक length, ...)
 * Purpose : add a message onto a message queue
 * Params  : msgq   - queue to add message on
 *	     length - length of message
 *	     ...    - message bytes
 * Returns : != 0 अगर successful
 */
बाह्य पूर्णांक msgqueue_addmsg(MsgQueue_t *msgq, पूर्णांक length, ...);

/*
 * Function: व्योम msgqueue_flush(MsgQueue_t *msgq)
 * Purpose : flush all messages from message queue
 * Params  : msgq - queue to flush
 */
बाह्य व्योम msgqueue_flush(MsgQueue_t *msgq);

#पूर्ण_अगर
