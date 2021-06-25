<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright IBM Corp. 2016
 * Author(s): Martin Schwidefsky <schwidefsky@de.ibm.com>
 *
 * Adjunct processor bus, queue related code.
 */

#घोषणा KMSG_COMPONENT "ap"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/facility.h>

#समावेश "ap_bus.h"
#समावेश "ap_debug.h"

अटल व्योम __ap_flush_queue(काष्ठा ap_queue *aq);

/**
 * ap_queue_enable_पूर्णांकerruption(): Enable पूर्णांकerruption on an AP queue.
 * @qid: The AP queue number
 * @ind: the notअगरication indicator byte
 *
 * Enables पूर्णांकerruption on AP queue via ap_aqic(). Based on the वापस
 * value it रुकोs a जबतक and tests the AP queue अगर पूर्णांकerrupts
 * have been चयनed on using ap_test_queue().
 */
अटल पूर्णांक ap_queue_enable_पूर्णांकerruption(काष्ठा ap_queue *aq, व्योम *ind)
अणु
	काष्ठा ap_queue_status status;
	काष्ठा ap_qirq_ctrl qirqctrl = अणु 0 पूर्ण;

	qirqctrl.ir = 1;
	qirqctrl.isc = AP_ISC;
	status = ap_aqic(aq->qid, qirqctrl, ind);
	चयन (status.response_code) अणु
	हाल AP_RESPONSE_NORMAL:
	हाल AP_RESPONSE_OTHERWISE_CHANGED:
		वापस 0;
	हाल AP_RESPONSE_Q_NOT_AVAIL:
	हाल AP_RESPONSE_DECONFIGURED:
	हाल AP_RESPONSE_CHECKSTOPPED:
	हाल AP_RESPONSE_INVALID_ADDRESS:
		pr_err("Registering adapter interrupts for AP device %02x.%04x failed\n",
		       AP_QID_CARD(aq->qid),
		       AP_QID_QUEUE(aq->qid));
		वापस -EOPNOTSUPP;
	हाल AP_RESPONSE_RESET_IN_PROGRESS:
	हाल AP_RESPONSE_BUSY:
	शेष:
		वापस -EBUSY;
	पूर्ण
पूर्ण

/**
 * __ap_send(): Send message to adjunct processor queue.
 * @qid: The AP queue number
 * @psmid: The program supplied message identअगरier
 * @msg: The message text
 * @length: The message length
 * @special: Special Bit
 *
 * Returns AP queue status काष्ठाure.
 * Condition code 1 on NQAP can't happen because the L bit is 1.
 * Condition code 2 on NQAP also means the send is incomplete,
 * because a segment boundary was reached. The NQAP is repeated.
 */
अटल अंतरभूत काष्ठा ap_queue_status
__ap_send(ap_qid_t qid, अचिन्हित दीर्घ दीर्घ psmid, व्योम *msg, माप_प्रकार length,
	  पूर्णांक special)
अणु
	अगर (special)
		qid |= 0x400000UL;
	वापस ap_nqap(qid, psmid, msg, length);
पूर्ण

पूर्णांक ap_send(ap_qid_t qid, अचिन्हित दीर्घ दीर्घ psmid, व्योम *msg, माप_प्रकार length)
अणु
	काष्ठा ap_queue_status status;

	status = __ap_send(qid, psmid, msg, length, 0);
	चयन (status.response_code) अणु
	हाल AP_RESPONSE_NORMAL:
		वापस 0;
	हाल AP_RESPONSE_Q_FULL:
	हाल AP_RESPONSE_RESET_IN_PROGRESS:
		वापस -EBUSY;
	हाल AP_RESPONSE_REQ_FAC_NOT_INST:
		वापस -EINVAL;
	शेष:	/* Device is gone. */
		वापस -ENODEV;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(ap_send);

पूर्णांक ap_recv(ap_qid_t qid, अचिन्हित दीर्घ दीर्घ *psmid, व्योम *msg, माप_प्रकार length)
अणु
	काष्ठा ap_queue_status status;

	अगर (msg == शून्य)
		वापस -EINVAL;
	status = ap_dqap(qid, psmid, msg, length);
	चयन (status.response_code) अणु
	हाल AP_RESPONSE_NORMAL:
		वापस 0;
	हाल AP_RESPONSE_NO_PENDING_REPLY:
		अगर (status.queue_empty)
			वापस -ENOENT;
		वापस -EBUSY;
	हाल AP_RESPONSE_RESET_IN_PROGRESS:
		वापस -EBUSY;
	शेष:
		वापस -ENODEV;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(ap_recv);

/* State machine definitions and helpers */

अटल क्रमागत ap_sm_रुको ap_sm_nop(काष्ठा ap_queue *aq)
अणु
	वापस AP_SM_WAIT_NONE;
पूर्ण

/**
 * ap_sm_recv(): Receive pending reply messages from an AP queue but करो
 *	not change the state of the device.
 * @aq: poपूर्णांकer to the AP queue
 *
 * Returns AP_SM_WAIT_NONE, AP_SM_WAIT_AGAIN, or AP_SM_WAIT_INTERRUPT
 */
अटल काष्ठा ap_queue_status ap_sm_recv(काष्ठा ap_queue *aq)
अणु
	काष्ठा ap_queue_status status;
	काष्ठा ap_message *ap_msg;
	bool found = false;

	status = ap_dqap(aq->qid, &aq->reply->psmid,
			 aq->reply->msg, aq->reply->len);
	चयन (status.response_code) अणु
	हाल AP_RESPONSE_NORMAL:
		aq->queue_count = max_t(पूर्णांक, 0, aq->queue_count - 1);
		अगर (aq->queue_count > 0)
			mod_समयr(&aq->समयout,
				  jअगरfies + aq->request_समयout);
		list_क्रम_each_entry(ap_msg, &aq->pendingq, list) अणु
			अगर (ap_msg->psmid != aq->reply->psmid)
				जारी;
			list_del_init(&ap_msg->list);
			aq->pendingq_count--;
			ap_msg->receive(aq, ap_msg, aq->reply);
			found = true;
			अवरोध;
		पूर्ण
		अगर (!found) अणु
			AP_DBF_WARN("%s unassociated reply psmid=0x%016llx on 0x%02x.%04x\n",
				    __func__, aq->reply->psmid,
				    AP_QID_CARD(aq->qid), AP_QID_QUEUE(aq->qid));
		पूर्ण
		fallthrough;
	हाल AP_RESPONSE_NO_PENDING_REPLY:
		अगर (!status.queue_empty || aq->queue_count <= 0)
			अवरोध;
		/* The card shouldn't क्रमget requests but who knows. */
		aq->queue_count = 0;
		list_splice_init(&aq->pendingq, &aq->requestq);
		aq->requestq_count += aq->pendingq_count;
		aq->pendingq_count = 0;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस status;
पूर्ण

/**
 * ap_sm_पढ़ो(): Receive pending reply messages from an AP queue.
 * @aq: poपूर्णांकer to the AP queue
 *
 * Returns AP_SM_WAIT_NONE, AP_SM_WAIT_AGAIN, or AP_SM_WAIT_INTERRUPT
 */
अटल क्रमागत ap_sm_रुको ap_sm_पढ़ो(काष्ठा ap_queue *aq)
अणु
	काष्ठा ap_queue_status status;

	अगर (!aq->reply)
		वापस AP_SM_WAIT_NONE;
	status = ap_sm_recv(aq);
	चयन (status.response_code) अणु
	हाल AP_RESPONSE_NORMAL:
		अगर (aq->queue_count > 0) अणु
			aq->sm_state = AP_SM_STATE_WORKING;
			वापस AP_SM_WAIT_AGAIN;
		पूर्ण
		aq->sm_state = AP_SM_STATE_IDLE;
		वापस AP_SM_WAIT_NONE;
	हाल AP_RESPONSE_NO_PENDING_REPLY:
		अगर (aq->queue_count > 0)
			वापस AP_SM_WAIT_INTERRUPT;
		aq->sm_state = AP_SM_STATE_IDLE;
		वापस AP_SM_WAIT_NONE;
	शेष:
		aq->dev_state = AP_DEV_STATE_ERROR;
		aq->last_err_rc = status.response_code;
		AP_DBF_WARN("%s RC 0x%02x on 0x%02x.%04x -> AP_DEV_STATE_ERROR\n",
			    __func__, status.response_code,
			    AP_QID_CARD(aq->qid), AP_QID_QUEUE(aq->qid));
		वापस AP_SM_WAIT_NONE;
	पूर्ण
पूर्ण

/**
 * ap_sm_ग_लिखो(): Send messages from the request queue to an AP queue.
 * @aq: poपूर्णांकer to the AP queue
 *
 * Returns AP_SM_WAIT_NONE, AP_SM_WAIT_AGAIN, or AP_SM_WAIT_INTERRUPT
 */
अटल क्रमागत ap_sm_रुको ap_sm_ग_लिखो(काष्ठा ap_queue *aq)
अणु
	काष्ठा ap_queue_status status;
	काष्ठा ap_message *ap_msg;
	ap_qid_t qid = aq->qid;

	अगर (aq->requestq_count <= 0)
		वापस AP_SM_WAIT_NONE;
	/* Start the next request on the queue. */
	ap_msg = list_entry(aq->requestq.next, काष्ठा ap_message, list);
#अगर_घोषित CONFIG_ZCRYPT_DEBUG
	अगर (ap_msg->fi.action == AP_FI_ACTION_NQAP_QID_INVAL) अणु
		AP_DBF_WARN("%s fi cmd 0x%04x: forcing invalid qid 0xFF00\n",
			    __func__, ap_msg->fi.cmd);
		qid = 0xFF00;
	पूर्ण
#पूर्ण_अगर
	status = __ap_send(qid, ap_msg->psmid,
			   ap_msg->msg, ap_msg->len,
			   ap_msg->flags & AP_MSG_FLAG_SPECIAL);
	चयन (status.response_code) अणु
	हाल AP_RESPONSE_NORMAL:
		aq->queue_count = max_t(पूर्णांक, 1, aq->queue_count + 1);
		अगर (aq->queue_count == 1)
			mod_समयr(&aq->समयout, jअगरfies + aq->request_समयout);
		list_move_tail(&ap_msg->list, &aq->pendingq);
		aq->requestq_count--;
		aq->pendingq_count++;
		अगर (aq->queue_count < aq->card->queue_depth) अणु
			aq->sm_state = AP_SM_STATE_WORKING;
			वापस AP_SM_WAIT_AGAIN;
		पूर्ण
		fallthrough;
	हाल AP_RESPONSE_Q_FULL:
		aq->sm_state = AP_SM_STATE_QUEUE_FULL;
		वापस AP_SM_WAIT_INTERRUPT;
	हाल AP_RESPONSE_RESET_IN_PROGRESS:
		aq->sm_state = AP_SM_STATE_RESET_WAIT;
		वापस AP_SM_WAIT_TIMEOUT;
	हाल AP_RESPONSE_INVALID_DOMAIN:
		AP_DBF(DBF_WARN, "AP_RESPONSE_INVALID_DOMAIN on NQAP\n");
		fallthrough;
	हाल AP_RESPONSE_MESSAGE_TOO_BIG:
	हाल AP_RESPONSE_REQ_FAC_NOT_INST:
		list_del_init(&ap_msg->list);
		aq->requestq_count--;
		ap_msg->rc = -EINVAL;
		ap_msg->receive(aq, ap_msg, शून्य);
		वापस AP_SM_WAIT_AGAIN;
	शेष:
		aq->dev_state = AP_DEV_STATE_ERROR;
		aq->last_err_rc = status.response_code;
		AP_DBF_WARN("%s RC 0x%02x on 0x%02x.%04x -> AP_DEV_STATE_ERROR\n",
			    __func__, status.response_code,
			    AP_QID_CARD(aq->qid), AP_QID_QUEUE(aq->qid));
		वापस AP_SM_WAIT_NONE;
	पूर्ण
पूर्ण

/**
 * ap_sm_पढ़ो_ग_लिखो(): Send and receive messages to/from an AP queue.
 * @aq: poपूर्णांकer to the AP queue
 *
 * Returns AP_SM_WAIT_NONE, AP_SM_WAIT_AGAIN, or AP_SM_WAIT_INTERRUPT
 */
अटल क्रमागत ap_sm_रुको ap_sm_पढ़ो_ग_लिखो(काष्ठा ap_queue *aq)
अणु
	वापस min(ap_sm_पढ़ो(aq), ap_sm_ग_लिखो(aq));
पूर्ण

/**
 * ap_sm_reset(): Reset an AP queue.
 * @qid: The AP queue number
 *
 * Submit the Reset command to an AP queue.
 */
अटल क्रमागत ap_sm_रुको ap_sm_reset(काष्ठा ap_queue *aq)
अणु
	काष्ठा ap_queue_status status;

	status = ap_rapq(aq->qid);
	चयन (status.response_code) अणु
	हाल AP_RESPONSE_NORMAL:
	हाल AP_RESPONSE_RESET_IN_PROGRESS:
		aq->sm_state = AP_SM_STATE_RESET_WAIT;
		aq->पूर्णांकerrupt = AP_INTR_DISABLED;
		वापस AP_SM_WAIT_TIMEOUT;
	शेष:
		aq->dev_state = AP_DEV_STATE_ERROR;
		aq->last_err_rc = status.response_code;
		AP_DBF_WARN("%s RC 0x%02x on 0x%02x.%04x -> AP_DEV_STATE_ERROR\n",
			    __func__, status.response_code,
			    AP_QID_CARD(aq->qid), AP_QID_QUEUE(aq->qid));
		वापस AP_SM_WAIT_NONE;
	पूर्ण
पूर्ण

/**
 * ap_sm_reset_रुको(): Test queue क्रम completion of the reset operation
 * @aq: poपूर्णांकer to the AP queue
 *
 * Returns AP_POLL_IMMEDIATELY, AP_POLL_AFTER_TIMEROUT or 0.
 */
अटल क्रमागत ap_sm_रुको ap_sm_reset_रुको(काष्ठा ap_queue *aq)
अणु
	काष्ठा ap_queue_status status;
	व्योम *lsi_ptr;

	अगर (aq->queue_count > 0 && aq->reply)
		/* Try to पढ़ो a completed message and get the status */
		status = ap_sm_recv(aq);
	अन्यथा
		/* Get the status with TAPQ */
		status = ap_tapq(aq->qid, शून्य);

	चयन (status.response_code) अणु
	हाल AP_RESPONSE_NORMAL:
		lsi_ptr = ap_airq_ptr();
		अगर (lsi_ptr && ap_queue_enable_पूर्णांकerruption(aq, lsi_ptr) == 0)
			aq->sm_state = AP_SM_STATE_SETIRQ_WAIT;
		अन्यथा
			aq->sm_state = (aq->queue_count > 0) ?
				AP_SM_STATE_WORKING : AP_SM_STATE_IDLE;
		वापस AP_SM_WAIT_AGAIN;
	हाल AP_RESPONSE_BUSY:
	हाल AP_RESPONSE_RESET_IN_PROGRESS:
		वापस AP_SM_WAIT_TIMEOUT;
	हाल AP_RESPONSE_Q_NOT_AVAIL:
	हाल AP_RESPONSE_DECONFIGURED:
	हाल AP_RESPONSE_CHECKSTOPPED:
	शेष:
		aq->dev_state = AP_DEV_STATE_ERROR;
		aq->last_err_rc = status.response_code;
		AP_DBF_WARN("%s RC 0x%02x on 0x%02x.%04x -> AP_DEV_STATE_ERROR\n",
			    __func__, status.response_code,
			    AP_QID_CARD(aq->qid), AP_QID_QUEUE(aq->qid));
		वापस AP_SM_WAIT_NONE;
	पूर्ण
पूर्ण

/**
 * ap_sm_setirq_रुको(): Test queue क्रम completion of the irq enablement
 * @aq: poपूर्णांकer to the AP queue
 *
 * Returns AP_POLL_IMMEDIATELY, AP_POLL_AFTER_TIMEROUT or 0.
 */
अटल क्रमागत ap_sm_रुको ap_sm_setirq_रुको(काष्ठा ap_queue *aq)
अणु
	काष्ठा ap_queue_status status;

	अगर (aq->queue_count > 0 && aq->reply)
		/* Try to पढ़ो a completed message and get the status */
		status = ap_sm_recv(aq);
	अन्यथा
		/* Get the status with TAPQ */
		status = ap_tapq(aq->qid, शून्य);

	अगर (status.irq_enabled == 1) अणु
		/* Irqs are now enabled */
		aq->पूर्णांकerrupt = AP_INTR_ENABLED;
		aq->sm_state = (aq->queue_count > 0) ?
			AP_SM_STATE_WORKING : AP_SM_STATE_IDLE;
	पूर्ण

	चयन (status.response_code) अणु
	हाल AP_RESPONSE_NORMAL:
		अगर (aq->queue_count > 0)
			वापस AP_SM_WAIT_AGAIN;
		fallthrough;
	हाल AP_RESPONSE_NO_PENDING_REPLY:
		वापस AP_SM_WAIT_TIMEOUT;
	शेष:
		aq->dev_state = AP_DEV_STATE_ERROR;
		aq->last_err_rc = status.response_code;
		AP_DBF_WARN("%s RC 0x%02x on 0x%02x.%04x -> AP_DEV_STATE_ERROR\n",
			    __func__, status.response_code,
			    AP_QID_CARD(aq->qid), AP_QID_QUEUE(aq->qid));
		वापस AP_SM_WAIT_NONE;
	पूर्ण
पूर्ण

/*
 * AP state machine jump table
 */
अटल ap_func_t *ap_jumptable[NR_AP_SM_STATES][NR_AP_SM_EVENTS] = अणु
	[AP_SM_STATE_RESET_START] = अणु
		[AP_SM_EVENT_POLL] = ap_sm_reset,
		[AP_SM_EVENT_TIMEOUT] = ap_sm_nop,
	पूर्ण,
	[AP_SM_STATE_RESET_WAIT] = अणु
		[AP_SM_EVENT_POLL] = ap_sm_reset_रुको,
		[AP_SM_EVENT_TIMEOUT] = ap_sm_nop,
	पूर्ण,
	[AP_SM_STATE_SETIRQ_WAIT] = अणु
		[AP_SM_EVENT_POLL] = ap_sm_setirq_रुको,
		[AP_SM_EVENT_TIMEOUT] = ap_sm_nop,
	पूर्ण,
	[AP_SM_STATE_IDLE] = अणु
		[AP_SM_EVENT_POLL] = ap_sm_ग_लिखो,
		[AP_SM_EVENT_TIMEOUT] = ap_sm_nop,
	पूर्ण,
	[AP_SM_STATE_WORKING] = अणु
		[AP_SM_EVENT_POLL] = ap_sm_पढ़ो_ग_लिखो,
		[AP_SM_EVENT_TIMEOUT] = ap_sm_reset,
	पूर्ण,
	[AP_SM_STATE_QUEUE_FULL] = अणु
		[AP_SM_EVENT_POLL] = ap_sm_पढ़ो,
		[AP_SM_EVENT_TIMEOUT] = ap_sm_reset,
	पूर्ण,
पूर्ण;

क्रमागत ap_sm_रुको ap_sm_event(काष्ठा ap_queue *aq, क्रमागत ap_sm_event event)
अणु
	अगर (aq->dev_state > AP_DEV_STATE_UNINITIATED)
		वापस ap_jumptable[aq->sm_state][event](aq);
	अन्यथा
		वापस AP_SM_WAIT_NONE;
पूर्ण

क्रमागत ap_sm_रुको ap_sm_event_loop(काष्ठा ap_queue *aq, क्रमागत ap_sm_event event)
अणु
	क्रमागत ap_sm_रुको रुको;

	जबतक ((रुको = ap_sm_event(aq, event)) == AP_SM_WAIT_AGAIN)
		;
	वापस रुको;
पूर्ण

/*
 * AP queue related attributes.
 */
अटल sमाप_प्रकार request_count_show(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  अक्षर *buf)
अणु
	काष्ठा ap_queue *aq = to_ap_queue(dev);
	bool valid = false;
	u64 req_cnt;

	spin_lock_bh(&aq->lock);
	अगर (aq->dev_state > AP_DEV_STATE_UNINITIATED) अणु
		req_cnt = aq->total_request_count;
		valid = true;
	पूर्ण
	spin_unlock_bh(&aq->lock);

	अगर (valid)
		वापस scnम_लिखो(buf, PAGE_SIZE, "%llu\n", req_cnt);
	अन्यथा
		वापस scnम_लिखो(buf, PAGE_SIZE, "-\n");
पूर्ण

अटल sमाप_प्रकार request_count_store(काष्ठा device *dev,
				   काष्ठा device_attribute *attr,
				   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा ap_queue *aq = to_ap_queue(dev);

	spin_lock_bh(&aq->lock);
	aq->total_request_count = 0;
	spin_unlock_bh(&aq->lock);

	वापस count;
पूर्ण

अटल DEVICE_ATTR_RW(request_count);

अटल sमाप_प्रकार requestq_count_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ap_queue *aq = to_ap_queue(dev);
	अचिन्हित पूर्णांक reqq_cnt = 0;

	spin_lock_bh(&aq->lock);
	अगर (aq->dev_state > AP_DEV_STATE_UNINITIATED)
		reqq_cnt = aq->requestq_count;
	spin_unlock_bh(&aq->lock);
	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", reqq_cnt);
पूर्ण

अटल DEVICE_ATTR_RO(requestq_count);

अटल sमाप_प्रकार pendingq_count_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ap_queue *aq = to_ap_queue(dev);
	अचिन्हित पूर्णांक penq_cnt = 0;

	spin_lock_bh(&aq->lock);
	अगर (aq->dev_state > AP_DEV_STATE_UNINITIATED)
		penq_cnt = aq->pendingq_count;
	spin_unlock_bh(&aq->lock);
	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", penq_cnt);
पूर्ण

अटल DEVICE_ATTR_RO(pendingq_count);

अटल sमाप_प्रकार reset_show(काष्ठा device *dev,
			  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ap_queue *aq = to_ap_queue(dev);
	पूर्णांक rc = 0;

	spin_lock_bh(&aq->lock);
	चयन (aq->sm_state) अणु
	हाल AP_SM_STATE_RESET_START:
	हाल AP_SM_STATE_RESET_WAIT:
		rc = scnम_लिखो(buf, PAGE_SIZE, "Reset in progress.\n");
		अवरोध;
	हाल AP_SM_STATE_WORKING:
	हाल AP_SM_STATE_QUEUE_FULL:
		rc = scnम_लिखो(buf, PAGE_SIZE, "Reset Timer armed.\n");
		अवरोध;
	शेष:
		rc = scnम_लिखो(buf, PAGE_SIZE, "No Reset Timer set.\n");
	पूर्ण
	spin_unlock_bh(&aq->lock);
	वापस rc;
पूर्ण

अटल sमाप_प्रकार reset_store(काष्ठा device *dev,
			   काष्ठा device_attribute *attr,
			   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा ap_queue *aq = to_ap_queue(dev);

	spin_lock_bh(&aq->lock);
	__ap_flush_queue(aq);
	aq->sm_state = AP_SM_STATE_RESET_START;
	ap_रुको(ap_sm_event(aq, AP_SM_EVENT_POLL));
	spin_unlock_bh(&aq->lock);

	AP_DBF(DBF_INFO, "reset queue=%02x.%04x triggered by user\n",
	       AP_QID_CARD(aq->qid), AP_QID_QUEUE(aq->qid));

	वापस count;
पूर्ण

अटल DEVICE_ATTR_RW(reset);

अटल sमाप_प्रकार पूर्णांकerrupt_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ap_queue *aq = to_ap_queue(dev);
	पूर्णांक rc = 0;

	spin_lock_bh(&aq->lock);
	अगर (aq->sm_state == AP_SM_STATE_SETIRQ_WAIT)
		rc = scnम_लिखो(buf, PAGE_SIZE, "Enable Interrupt pending.\n");
	अन्यथा अगर (aq->पूर्णांकerrupt == AP_INTR_ENABLED)
		rc = scnम_लिखो(buf, PAGE_SIZE, "Interrupts enabled.\n");
	अन्यथा
		rc = scnम_लिखो(buf, PAGE_SIZE, "Interrupts disabled.\n");
	spin_unlock_bh(&aq->lock);
	वापस rc;
पूर्ण

अटल DEVICE_ATTR_RO(पूर्णांकerrupt);

अटल sमाप_प्रकार config_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ap_queue *aq = to_ap_queue(dev);
	पूर्णांक rc;

	spin_lock_bh(&aq->lock);
	rc = scnम_लिखो(buf, PAGE_SIZE, "%d\n", aq->config ? 1 : 0);
	spin_unlock_bh(&aq->lock);
	वापस rc;
पूर्ण

अटल DEVICE_ATTR_RO(config);

#अगर_घोषित CONFIG_ZCRYPT_DEBUG
अटल sमाप_प्रकार states_show(काष्ठा device *dev,
			   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ap_queue *aq = to_ap_queue(dev);
	पूर्णांक rc = 0;

	spin_lock_bh(&aq->lock);
	/* queue device state */
	चयन (aq->dev_state) अणु
	हाल AP_DEV_STATE_UNINITIATED:
		rc = scnम_लिखो(buf, PAGE_SIZE, "UNINITIATED\n");
		अवरोध;
	हाल AP_DEV_STATE_OPERATING:
		rc = scnम_लिखो(buf, PAGE_SIZE, "OPERATING");
		अवरोध;
	हाल AP_DEV_STATE_SHUTDOWN:
		rc = scnम_लिखो(buf, PAGE_SIZE, "SHUTDOWN");
		अवरोध;
	हाल AP_DEV_STATE_ERROR:
		rc = scnम_लिखो(buf, PAGE_SIZE, "ERROR");
		अवरोध;
	शेष:
		rc = scnम_लिखो(buf, PAGE_SIZE, "UNKNOWN");
	पूर्ण
	/* state machine state */
	अगर (aq->dev_state) अणु
		चयन (aq->sm_state) अणु
		हाल AP_SM_STATE_RESET_START:
			rc += scnम_लिखो(buf + rc, PAGE_SIZE - rc,
					" [RESET_START]\n");
			अवरोध;
		हाल AP_SM_STATE_RESET_WAIT:
			rc += scnम_लिखो(buf + rc, PAGE_SIZE - rc,
					" [RESET_WAIT]\n");
			अवरोध;
		हाल AP_SM_STATE_SETIRQ_WAIT:
			rc += scnम_लिखो(buf + rc, PAGE_SIZE - rc,
					" [SETIRQ_WAIT]\n");
			अवरोध;
		हाल AP_SM_STATE_IDLE:
			rc += scnम_लिखो(buf + rc, PAGE_SIZE - rc,
					" [IDLE]\n");
			अवरोध;
		हाल AP_SM_STATE_WORKING:
			rc += scnम_लिखो(buf + rc, PAGE_SIZE - rc,
					" [WORKING]\n");
			अवरोध;
		हाल AP_SM_STATE_QUEUE_FULL:
			rc += scnम_लिखो(buf + rc, PAGE_SIZE - rc,
					" [FULL]\n");
			अवरोध;
		शेष:
			rc += scnम_लिखो(buf + rc, PAGE_SIZE - rc,
					" [UNKNOWN]\n");
		पूर्ण
	पूर्ण
	spin_unlock_bh(&aq->lock);

	वापस rc;
पूर्ण
अटल DEVICE_ATTR_RO(states);

अटल sमाप_प्रकार last_err_rc_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ap_queue *aq = to_ap_queue(dev);
	पूर्णांक rc;

	spin_lock_bh(&aq->lock);
	rc = aq->last_err_rc;
	spin_unlock_bh(&aq->lock);

	चयन (rc) अणु
	हाल AP_RESPONSE_NORMAL:
		वापस scnम_लिखो(buf, PAGE_SIZE, "NORMAL\n");
	हाल AP_RESPONSE_Q_NOT_AVAIL:
		वापस scnम_लिखो(buf, PAGE_SIZE, "Q_NOT_AVAIL\n");
	हाल AP_RESPONSE_RESET_IN_PROGRESS:
		वापस scnम_लिखो(buf, PAGE_SIZE, "RESET_IN_PROGRESS\n");
	हाल AP_RESPONSE_DECONFIGURED:
		वापस scnम_लिखो(buf, PAGE_SIZE, "DECONFIGURED\n");
	हाल AP_RESPONSE_CHECKSTOPPED:
		वापस scnम_लिखो(buf, PAGE_SIZE, "CHECKSTOPPED\n");
	हाल AP_RESPONSE_BUSY:
		वापस scnम_लिखो(buf, PAGE_SIZE, "BUSY\n");
	हाल AP_RESPONSE_INVALID_ADDRESS:
		वापस scnम_लिखो(buf, PAGE_SIZE, "INVALID_ADDRESS\n");
	हाल AP_RESPONSE_OTHERWISE_CHANGED:
		वापस scnम_लिखो(buf, PAGE_SIZE, "OTHERWISE_CHANGED\n");
	हाल AP_RESPONSE_Q_FULL:
		वापस scnम_लिखो(buf, PAGE_SIZE, "Q_FULL/NO_PENDING_REPLY\n");
	हाल AP_RESPONSE_INDEX_TOO_BIG:
		वापस scnम_लिखो(buf, PAGE_SIZE, "INDEX_TOO_BIG\n");
	हाल AP_RESPONSE_NO_FIRST_PART:
		वापस scnम_लिखो(buf, PAGE_SIZE, "NO_FIRST_PART\n");
	हाल AP_RESPONSE_MESSAGE_TOO_BIG:
		वापस scnम_लिखो(buf, PAGE_SIZE, "MESSAGE_TOO_BIG\n");
	हाल AP_RESPONSE_REQ_FAC_NOT_INST:
		वापस scnम_लिखो(buf, PAGE_SIZE, "REQ_FAC_NOT_INST\n");
	शेष:
		वापस scnम_लिखो(buf, PAGE_SIZE, "response code %d\n", rc);
	पूर्ण
पूर्ण
अटल DEVICE_ATTR_RO(last_err_rc);
#पूर्ण_अगर

अटल काष्ठा attribute *ap_queue_dev_attrs[] = अणु
	&dev_attr_request_count.attr,
	&dev_attr_requestq_count.attr,
	&dev_attr_pendingq_count.attr,
	&dev_attr_reset.attr,
	&dev_attr_पूर्णांकerrupt.attr,
	&dev_attr_config.attr,
#अगर_घोषित CONFIG_ZCRYPT_DEBUG
	&dev_attr_states.attr,
	&dev_attr_last_err_rc.attr,
#पूर्ण_अगर
	शून्य
पूर्ण;

अटल काष्ठा attribute_group ap_queue_dev_attr_group = अणु
	.attrs = ap_queue_dev_attrs
पूर्ण;

अटल स्थिर काष्ठा attribute_group *ap_queue_dev_attr_groups[] = अणु
	&ap_queue_dev_attr_group,
	शून्य
पूर्ण;

अटल काष्ठा device_type ap_queue_type = अणु
	.name = "ap_queue",
	.groups = ap_queue_dev_attr_groups,
पूर्ण;

अटल व्योम ap_queue_device_release(काष्ठा device *dev)
अणु
	काष्ठा ap_queue *aq = to_ap_queue(dev);

	spin_lock_bh(&ap_queues_lock);
	hash_del(&aq->hnode);
	spin_unlock_bh(&ap_queues_lock);

	kमुक्त(aq);
पूर्ण

काष्ठा ap_queue *ap_queue_create(ap_qid_t qid, पूर्णांक device_type)
अणु
	काष्ठा ap_queue *aq;

	aq = kzalloc(माप(*aq), GFP_KERNEL);
	अगर (!aq)
		वापस शून्य;
	aq->ap_dev.device.release = ap_queue_device_release;
	aq->ap_dev.device.type = &ap_queue_type;
	aq->ap_dev.device_type = device_type;
	aq->qid = qid;
	aq->पूर्णांकerrupt = AP_INTR_DISABLED;
	spin_lock_init(&aq->lock);
	INIT_LIST_HEAD(&aq->pendingq);
	INIT_LIST_HEAD(&aq->requestq);
	समयr_setup(&aq->समयout, ap_request_समयout, 0);

	वापस aq;
पूर्ण

व्योम ap_queue_init_reply(काष्ठा ap_queue *aq, काष्ठा ap_message *reply)
अणु
	aq->reply = reply;

	spin_lock_bh(&aq->lock);
	ap_रुको(ap_sm_event(aq, AP_SM_EVENT_POLL));
	spin_unlock_bh(&aq->lock);
पूर्ण
EXPORT_SYMBOL(ap_queue_init_reply);

/**
 * ap_queue_message(): Queue a request to an AP device.
 * @aq: The AP device to queue the message to
 * @ap_msg: The message that is to be added
 */
पूर्णांक ap_queue_message(काष्ठा ap_queue *aq, काष्ठा ap_message *ap_msg)
अणु
	पूर्णांक rc = 0;

	/* msg needs to have a valid receive-callback */
	BUG_ON(!ap_msg->receive);

	spin_lock_bh(&aq->lock);

	/* only allow to queue new messages अगर device state is ok */
	अगर (aq->dev_state == AP_DEV_STATE_OPERATING) अणु
		list_add_tail(&ap_msg->list, &aq->requestq);
		aq->requestq_count++;
		aq->total_request_count++;
		atomic64_inc(&aq->card->total_request_count);
	पूर्ण अन्यथा
		rc = -ENODEV;

	/* Send/receive as many request from the queue as possible. */
	ap_रुको(ap_sm_event_loop(aq, AP_SM_EVENT_POLL));

	spin_unlock_bh(&aq->lock);

	वापस rc;
पूर्ण
EXPORT_SYMBOL(ap_queue_message);

/**
 * ap_cancel_message(): Cancel a crypto request.
 * @aq: The AP device that has the message queued
 * @ap_msg: The message that is to be हटाओd
 *
 * Cancel a crypto request. This is करोne by removing the request
 * from the device pending or request queue. Note that the
 * request stays on the AP queue. When it finishes the message
 * reply will be discarded because the psmid can't be found.
 */
व्योम ap_cancel_message(काष्ठा ap_queue *aq, काष्ठा ap_message *ap_msg)
अणु
	काष्ठा ap_message *पंचांगp;

	spin_lock_bh(&aq->lock);
	अगर (!list_empty(&ap_msg->list)) अणु
		list_क्रम_each_entry(पंचांगp, &aq->pendingq, list)
			अगर (पंचांगp->psmid == ap_msg->psmid) अणु
				aq->pendingq_count--;
				जाओ found;
			पूर्ण
		aq->requestq_count--;
found:
		list_del_init(&ap_msg->list);
	पूर्ण
	spin_unlock_bh(&aq->lock);
पूर्ण
EXPORT_SYMBOL(ap_cancel_message);

/**
 * __ap_flush_queue(): Flush requests.
 * @aq: Poपूर्णांकer to the AP queue
 *
 * Flush all requests from the request/pending queue of an AP device.
 */
अटल व्योम __ap_flush_queue(काष्ठा ap_queue *aq)
अणु
	काष्ठा ap_message *ap_msg, *next;

	list_क्रम_each_entry_safe(ap_msg, next, &aq->pendingq, list) अणु
		list_del_init(&ap_msg->list);
		aq->pendingq_count--;
		ap_msg->rc = -EAGAIN;
		ap_msg->receive(aq, ap_msg, शून्य);
	पूर्ण
	list_क्रम_each_entry_safe(ap_msg, next, &aq->requestq, list) अणु
		list_del_init(&ap_msg->list);
		aq->requestq_count--;
		ap_msg->rc = -EAGAIN;
		ap_msg->receive(aq, ap_msg, शून्य);
	पूर्ण
	aq->queue_count = 0;
पूर्ण

व्योम ap_flush_queue(काष्ठा ap_queue *aq)
अणु
	spin_lock_bh(&aq->lock);
	__ap_flush_queue(aq);
	spin_unlock_bh(&aq->lock);
पूर्ण
EXPORT_SYMBOL(ap_flush_queue);

व्योम ap_queue_prepare_हटाओ(काष्ठा ap_queue *aq)
अणु
	spin_lock_bh(&aq->lock);
	/* flush queue */
	__ap_flush_queue(aq);
	/* move queue device state to SHUTDOWN in progress */
	aq->dev_state = AP_DEV_STATE_SHUTDOWN;
	spin_unlock_bh(&aq->lock);
	del_समयr_sync(&aq->समयout);
पूर्ण

व्योम ap_queue_हटाओ(काष्ठा ap_queue *aq)
अणु
	/*
	 * all messages have been flushed and the device state
	 * is SHUTDOWN. Now reset with zero which also clears
	 * the irq registration and move the device state
	 * to the initial value AP_DEV_STATE_UNINITIATED.
	 */
	spin_lock_bh(&aq->lock);
	ap_zapq(aq->qid);
	aq->dev_state = AP_DEV_STATE_UNINITIATED;
	spin_unlock_bh(&aq->lock);
पूर्ण

व्योम ap_queue_init_state(काष्ठा ap_queue *aq)
अणु
	spin_lock_bh(&aq->lock);
	aq->dev_state = AP_DEV_STATE_OPERATING;
	aq->sm_state = AP_SM_STATE_RESET_START;
	ap_रुको(ap_sm_event(aq, AP_SM_EVENT_POLL));
	spin_unlock_bh(&aq->lock);
पूर्ण
EXPORT_SYMBOL(ap_queue_init_state);
