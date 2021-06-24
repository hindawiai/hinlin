<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */

/*
 *  Copyright (c) 2008 Silicon Graphics, Inc.  All Rights Reserved.
 */
#अगर_अघोषित __GRU_KSERVICES_H_
#घोषणा __GRU_KSERVICES_H_


/*
 * Message queues using the GRU to send/receive messages.
 *
 * These function allow the user to create a message queue क्रम
 * sending/receiving 1 or 2 cacheline messages using the GRU.
 *
 * Processes SENDING messages will use a kernel CBR/DSR to send
 * the message. This is transparent to the caller.
 *
 * The receiver करोes not use any GRU resources.
 *
 * The functions support:
 * 	- single receiver
 * 	- multiple senders
 *	- cross partition message
 *
 * Missing features ZZZ:
 * 	- user options क्रम dealing with समयouts, queue full, etc.
 * 	- gru_create_message_queue() needs पूर्णांकerrupt vector info
 */

काष्ठा gru_message_queue_desc अणु
	व्योम		*mq;			/* message queue vaddress */
	अचिन्हित दीर्घ	mq_gpa;			/* global address of mq */
	पूर्णांक		qlines;			/* queue size in CL */
	पूर्णांक		पूर्णांकerrupt_vector;	/* पूर्णांकerrupt vector */
	पूर्णांक		पूर्णांकerrupt_pnode;	/* pnode क्रम पूर्णांकerrupt */
	पूर्णांक		पूर्णांकerrupt_apicid;	/* lapicid क्रम पूर्णांकerrupt */
पूर्ण;

/*
 * Initialize a user allocated chunk of memory to be used as
 * a message queue. The caller must ensure that the queue is
 * in contiguous physical memory and is cacheline aligned.
 *
 * Message queue size is the total number of bytes allocated
 * to the queue including a 2 cacheline header that is used
 * to manage the queue.
 *
 *  Input:
 * 	mqd	poपूर्णांकer to message queue descriptor
 * 	p	poपूर्णांकer to user allocated mesq memory.
 * 	bytes	size of message queue in bytes
 *      vector	पूर्णांकerrupt vector (zero अगर no पूर्णांकerrupts)
 *      nasid	nasid of blade where पूर्णांकerrupt is delivered
 *      apicid	apicid of cpu क्रम पूर्णांकerrupt
 *
 *  Errors:
 *  	0	OK
 *  	>0	error
 */
बाह्य पूर्णांक gru_create_message_queue(काष्ठा gru_message_queue_desc *mqd,
		व्योम *p, अचिन्हित पूर्णांक bytes, पूर्णांक nasid, पूर्णांक vector, पूर्णांक apicid);

/*
 * Send a message to a message queue.
 *
 * Note: The message queue transport mechanism uses the first 32
 * bits of the message. Users should aव्योम using these bits.
 *
 *
 *   Input:
 * 	mqd	poपूर्णांकer to message queue descriptor
 * 	mesg	poपूर्णांकer to message. Must be 64-bit aligned
 * 	bytes	size of message in bytes
 *
 *   Output:
 *      0	message sent
 *     >0	Send failure - see error codes below
 *
 */
बाह्य पूर्णांक gru_send_message_gpa(काष्ठा gru_message_queue_desc *mqd,
			व्योम *mesg, अचिन्हित पूर्णांक bytes);

/* Status values क्रम gru_send_message() */
#घोषणा MQE_OK			0	/* message sent successfully */
#घोषणा MQE_CONGESTION		1	/* temporary congestion, try again */
#घोषणा MQE_QUEUE_FULL		2	/* queue is full */
#घोषणा MQE_UNEXPECTED_CB_ERR	3	/* unexpected CB error */
#घोषणा MQE_PAGE_OVERFLOW	10	/* BUG - queue overflowed a page */
#घोषणा MQE_BUG_NO_RESOURCES	11	/* BUG - could not alloc GRU cb/dsr */

/*
 * Advance the receive poपूर्णांकer क्रम the message queue to the next message.
 * Note: current API requires messages to be gotten & मुक्तd in order. Future
 * API extensions may allow क्रम out-of-order मुक्तing.
 *
 *   Input
 * 	mqd	poपूर्णांकer to message queue descriptor
 * 	mesq	message being मुक्तd
 */
बाह्य व्योम gru_मुक्त_message(काष्ठा gru_message_queue_desc *mqd,
			     व्योम *mesq);

/*
 * Get next message from message queue. Returns poपूर्णांकer to
 * message OR शून्य अगर no message present.
 * User must call gru_मुक्त_message() after message is processed
 * in order to move the queue poपूर्णांकers to next message.
 *
 *   Input
 * 	mqd	poपूर्णांकer to message queue descriptor
 *
 *   Output:
 *	p	poपूर्णांकer to message
 *	शून्य	no message available
 */
बाह्य व्योम *gru_get_next_message(काष्ठा gru_message_queue_desc *mqd);


/*
 * Read a GRU global GPA. Source can be located in a remote partition.
 *
 *    Input:
 *    	value		memory address where MMR value is वापसed
 *    	gpa		source numalink physical address of GPA
 *
 *    Output:
 *	0		OK
 *	>0		error
 */
पूर्णांक gru_पढ़ो_gpa(अचिन्हित दीर्घ *value, अचिन्हित दीर्घ gpa);


/*
 * Copy data using the GRU. Source or destination can be located in a remote
 * partition.
 *
 *    Input:
 *    	dest_gpa	destination global physical address
 *    	src_gpa		source global physical address
 *    	bytes		number of bytes to copy
 *
 *    Output:
 *	0		OK
 *	>0		error
 */
बाह्य पूर्णांक gru_copy_gpa(अचिन्हित दीर्घ dest_gpa, अचिन्हित दीर्घ src_gpa,
							अचिन्हित पूर्णांक bytes);

/*
 * Reserve GRU resources to be used asynchronously.
 *
 * 	input:
 * 		blade_id  - blade on which resources should be reserved
 * 		cbrs	  - number of CBRs
 * 		dsr_bytes - number of DSR bytes needed
 * 		cmp	  - completion काष्ठाure क्रम रुकोing क्रम
 * 			    async completions
 *	output:
 *		handle to identअगरy resource
 *		(0 = no resources)
 */
बाह्य अचिन्हित दीर्घ gru_reserve_async_resources(पूर्णांक blade_id, पूर्णांक cbrs, पूर्णांक dsr_bytes,
				काष्ठा completion *cmp);

/*
 * Release async resources previously reserved.
 *
 *	input:
 *		han - handle to identअगरy resources
 */
बाह्य व्योम gru_release_async_resources(अचिन्हित दीर्घ han);

/*
 * Wait क्रम async GRU inकाष्ठाions to complete.
 *
 *	input:
 *		han - handle to identअगरy resources
 */
बाह्य व्योम gru_रुको_async_cbr(अचिन्हित दीर्घ han);

/*
 * Lock previous reserved async GRU resources
 *
 *	input:
 *		han - handle to identअगरy resources
 *	output:
 *		cb  - poपूर्णांकer to first CBR
 *		dsr - poपूर्णांकer to first DSR
 */
बाह्य व्योम gru_lock_async_resource(अचिन्हित दीर्घ han,  व्योम **cb, व्योम **dsr);

/*
 * Unlock previous reserved async GRU resources
 *
 *	input:
 *		han - handle to identअगरy resources
 */
बाह्य व्योम gru_unlock_async_resource(अचिन्हित दीर्घ han);

#पूर्ण_अगर 		/* __GRU_KSERVICES_H_ */
