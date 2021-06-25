<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम Digigram miXart soundcards
 *
 * low level पूर्णांकerface with पूर्णांकerrupt handling and mail box implementation
 *
 * Copyright (c) 2003 by Digigram <alsa@digigram.com>
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mutex.h>
#समावेश <linux/pci.h>
#समावेश <linux/पन.स>

#समावेश <sound/core.h>
#समावेश "mixart.h"
#समावेश "mixart_hwdep.h"
#समावेश "mixart_core.h"


#घोषणा MSG_TIMEOUT_JIFFIES         (400 * HZ) / 1000 /* 400 ms */

#घोषणा MSG_DESCRIPTOR_SIZE         0x24
#घोषणा MSG_HEADER_SIZE             (MSG_DESCRIPTOR_SIZE + 4)

#घोषणा MSG_DEFAULT_SIZE            512

#घोषणा MSG_TYPE_MASK               0x00000003    /* mask क्रम following types */
#घोषणा MSG_TYPE_NOTIFY             0             /* embedded -> driver (only notअगरication, करो not get_msg() !) */
#घोषणा MSG_TYPE_COMMAND            1             /* driver <-> embedded (a command has no answer) */
#घोषणा MSG_TYPE_REQUEST            2             /* driver -> embedded (request will get an answer back) */
#घोषणा MSG_TYPE_ANSWER             3             /* embedded -> driver */
#घोषणा MSG_CANCEL_NOTIFY_MASK      0x80000000    /* this bit is set क्रम a notअगरication that has been canceled */


अटल पूर्णांक retrieve_msg_frame(काष्ठा mixart_mgr *mgr, u32 *msg_frame)
अणु
	/* पढ़ो the message frame fअगरo */
	u32 headptr, tailptr;

	tailptr = पढ़ोl_be(MIXART_MEM(mgr, MSG_OUTBOUND_POST_TAIL));
	headptr = पढ़ोl_be(MIXART_MEM(mgr, MSG_OUTBOUND_POST_HEAD));

	अगर (tailptr == headptr)
		वापस 0; /* no message posted */

	अगर (tailptr < MSG_OUTBOUND_POST_STACK)
		वापस 0; /* error */
	अगर (tailptr >= MSG_OUTBOUND_POST_STACK + MSG_BOUND_STACK_SIZE)
		वापस 0; /* error */

	*msg_frame = पढ़ोl_be(MIXART_MEM(mgr, tailptr));

	/* increment the tail index */
	tailptr += 4;
	अगर( tailptr >= (MSG_OUTBOUND_POST_STACK+MSG_BOUND_STACK_SIZE) )
		tailptr = MSG_OUTBOUND_POST_STACK;
	ग_लिखोl_be(tailptr, MIXART_MEM(mgr, MSG_OUTBOUND_POST_TAIL));

	वापस 1;
पूर्ण

अटल पूर्णांक get_msg(काष्ठा mixart_mgr *mgr, काष्ठा mixart_msg *resp,
		   u32 msg_frame_address )
अणु
	u32  headptr;
	u32  size;
	पूर्णांक  err;
#अगर_अघोषित __BIG_ENDIAN
	अचिन्हित पूर्णांक i;
#पूर्ण_अगर

	err = 0;

	/* copy message descriptor from miXart to driver */
	size                =  पढ़ोl_be(MIXART_MEM(mgr, msg_frame_address));       /* size of descriptor + response */
	resp->message_id    =  पढ़ोl_be(MIXART_MEM(mgr, msg_frame_address + 4));   /* dwMessageID */
	resp->uid.object_id =  पढ़ोl_be(MIXART_MEM(mgr, msg_frame_address + 8));   /* uidDest */
	resp->uid.desc      =  पढ़ोl_be(MIXART_MEM(mgr, msg_frame_address + 12));  /* */

	अगर( (size < MSG_DESCRIPTOR_SIZE) || (resp->size < (size - MSG_DESCRIPTOR_SIZE))) अणु
		err = -EINVAL;
		dev_err(&mgr->pci->dev,
			"problem with response size = %d\n", size);
		जाओ _clean_निकास;
	पूर्ण
	size -= MSG_DESCRIPTOR_SIZE;

	स_नकल_fromio(resp->data, MIXART_MEM(mgr, msg_frame_address + MSG_HEADER_SIZE ), size);
	resp->size = size;

	/* swap अगर necessary */
#अगर_अघोषित __BIG_ENDIAN
	size /= 4; /* u32 size */
	क्रम(i=0; i < size; i++) अणु
		((u32*)resp->data)[i] = be32_to_cpu(((__be32*)resp->data)[i]);
	पूर्ण
#पूर्ण_अगर

	/*
	 * मुक्त message frame address
	 */
	headptr = पढ़ोl_be(MIXART_MEM(mgr, MSG_OUTBOUND_FREE_HEAD));

	अगर( (headptr < MSG_OUTBOUND_FREE_STACK) || ( headptr >= (MSG_OUTBOUND_FREE_STACK+MSG_BOUND_STACK_SIZE))) अणु
		err = -EINVAL;
		जाओ _clean_निकास;
	पूर्ण

	/* give address back to outbound fअगरo */
	ग_लिखोl_be(msg_frame_address, MIXART_MEM(mgr, headptr));

	/* increment the outbound मुक्त head */
	headptr += 4;
	अगर( headptr >= (MSG_OUTBOUND_FREE_STACK+MSG_BOUND_STACK_SIZE) )
		headptr = MSG_OUTBOUND_FREE_STACK;

	ग_लिखोl_be(headptr, MIXART_MEM(mgr, MSG_OUTBOUND_FREE_HEAD));

 _clean_निकास:
	वापस err;
पूर्ण


/*
 * send a message to miXart. वापस: the msg_frame used क्रम this message
 */
/* call with mgr->msg_lock held! */
अटल पूर्णांक send_msg( काष्ठा mixart_mgr *mgr,
		     काष्ठा mixart_msg *msg,
		     पूर्णांक max_answersize,
		     पूर्णांक mark_pending,
		     u32 *msg_event)
अणु
	u32 headptr, tailptr;
	u32 msg_frame_address;
	पूर्णांक i;

	अगर (snd_BUG_ON(msg->size % 4))
		वापस -EINVAL;

	/* get message frame address */
	tailptr = पढ़ोl_be(MIXART_MEM(mgr, MSG_INBOUND_FREE_TAIL));
	headptr = पढ़ोl_be(MIXART_MEM(mgr, MSG_INBOUND_FREE_HEAD));

	अगर (tailptr == headptr) अणु
		dev_err(&mgr->pci->dev, "error: no message frame available\n");
		वापस -EBUSY;
	पूर्ण

	अगर( (tailptr < MSG_INBOUND_FREE_STACK) || (tailptr >= (MSG_INBOUND_FREE_STACK+MSG_BOUND_STACK_SIZE))) अणु
		वापस -EINVAL;
	पूर्ण

	msg_frame_address = पढ़ोl_be(MIXART_MEM(mgr, tailptr));
	ग_लिखोl(0, MIXART_MEM(mgr, tailptr)); /* set address to zero on this fअगरo position */

	/* increment the inbound मुक्त tail */
	tailptr += 4;
	अगर( tailptr >= (MSG_INBOUND_FREE_STACK+MSG_BOUND_STACK_SIZE) )
		tailptr = MSG_INBOUND_FREE_STACK;

	ग_लिखोl_be(tailptr, MIXART_MEM(mgr, MSG_INBOUND_FREE_TAIL));

	/* TODO : use स_नकल_toio() with पूर्णांकermediate buffer to copy the message */

	/* copy message descriptor to card memory */
	ग_लिखोl_be( msg->size + MSG_DESCRIPTOR_SIZE,      MIXART_MEM(mgr, msg_frame_address) );      /* size of descriptor + request */
	ग_लिखोl_be( msg->message_id ,                     MIXART_MEM(mgr, msg_frame_address + 4) );  /* dwMessageID */
	ग_लिखोl_be( msg->uid.object_id,                   MIXART_MEM(mgr, msg_frame_address + 8) );  /* uidDest */
	ग_लिखोl_be( msg->uid.desc,                        MIXART_MEM(mgr, msg_frame_address + 12) ); /* */
	ग_लिखोl_be( MSG_DESCRIPTOR_SIZE,                  MIXART_MEM(mgr, msg_frame_address + 16) ); /* SizeHeader */
	ग_लिखोl_be( MSG_DESCRIPTOR_SIZE,                  MIXART_MEM(mgr, msg_frame_address + 20) ); /* OffsetDLL_T16 */
	ग_लिखोl_be( msg->size,                            MIXART_MEM(mgr, msg_frame_address + 24) ); /* SizeDLL_T16 */
	ग_लिखोl_be( MSG_DESCRIPTOR_SIZE,                  MIXART_MEM(mgr, msg_frame_address + 28) ); /* OffsetDLL_DRV */
	ग_लिखोl_be( 0,                                    MIXART_MEM(mgr, msg_frame_address + 32) ); /* SizeDLL_DRV */
	ग_लिखोl_be( MSG_DESCRIPTOR_SIZE + max_answersize, MIXART_MEM(mgr, msg_frame_address + 36) ); /* dwExpectedAnswerSize */

	/* copy message data to card memory */
	क्रम( i=0; i < msg->size; i+=4 ) अणु
		ग_लिखोl_be( *(u32*)(msg->data + i), MIXART_MEM(mgr, MSG_HEADER_SIZE + msg_frame_address + i)  );
	पूर्ण

	अगर( mark_pending ) अणु
		अगर( *msg_event ) अणु
			/* the pending event is the notअगरication we रुको क्रम ! */
			mgr->pending_event = *msg_event;
		पूर्ण
		अन्यथा अणु
			/* the pending event is the answer we रुको क्रम (same address than the request)! */
			mgr->pending_event = msg_frame_address;

			/* copy address back to caller */
			*msg_event = msg_frame_address;
		पूर्ण
	पूर्ण

	/* mark the frame as a request (will have an answer) */
	msg_frame_address |= MSG_TYPE_REQUEST;

	/* post the frame */
	headptr = पढ़ोl_be(MIXART_MEM(mgr, MSG_INBOUND_POST_HEAD));

	अगर( (headptr < MSG_INBOUND_POST_STACK) || (headptr >= (MSG_INBOUND_POST_STACK+MSG_BOUND_STACK_SIZE))) अणु
		वापस -EINVAL;
	पूर्ण

	ग_लिखोl_be(msg_frame_address, MIXART_MEM(mgr, headptr));

	/* increment the inbound post head */
	headptr += 4;
	अगर( headptr >= (MSG_INBOUND_POST_STACK+MSG_BOUND_STACK_SIZE) )
		headptr = MSG_INBOUND_POST_STACK;

	ग_लिखोl_be(headptr, MIXART_MEM(mgr, MSG_INBOUND_POST_HEAD));

	वापस 0;
पूर्ण


पूर्णांक snd_mixart_send_msg(काष्ठा mixart_mgr *mgr, काष्ठा mixart_msg *request, पूर्णांक max_resp_size, व्योम *resp_data)
अणु
	काष्ठा mixart_msg resp;
	u32 msg_frame = 0; /* set to 0, so it's no notअगरication to रुको क्रम, but the answer */
	पूर्णांक err;
	रुको_queue_entry_t रुको;
	दीर्घ समयout;

	init_रुकोqueue_entry(&रुको, current);

	mutex_lock(&mgr->msg_lock);
	/* send the message */
	err = send_msg(mgr, request, max_resp_size, 1, &msg_frame);  /* send and mark the answer pending */
	अगर (err) अणु
		mutex_unlock(&mgr->msg_lock);
		वापस err;
	पूर्ण

	set_current_state(TASK_UNINTERRUPTIBLE);
	add_रुको_queue(&mgr->msg_sleep, &रुको);
	mutex_unlock(&mgr->msg_lock);
	समयout = schedule_समयout(MSG_TIMEOUT_JIFFIES);
	हटाओ_रुको_queue(&mgr->msg_sleep, &रुको);

	अगर (! समयout) अणु
		/* error - no ack */
		dev_err(&mgr->pci->dev,
			"error: no response on msg %x\n", msg_frame);
		वापस -EIO;
	पूर्ण

	/* retrieve the answer पूर्णांकo the same काष्ठा mixart_msg */
	resp.message_id = 0;
	resp.uid = (काष्ठा mixart_uid)अणु0,0पूर्ण;
	resp.data = resp_data;
	resp.size = max_resp_size;

	mutex_lock(&mgr->msg_lock);
	err = get_msg(mgr, &resp, msg_frame);
	mutex_unlock(&mgr->msg_lock);

	अगर( request->message_id != resp.message_id )
		dev_err(&mgr->pci->dev, "RESPONSE ERROR!\n");

	वापस err;
पूर्ण


पूर्णांक snd_mixart_send_msg_रुको_notअगर(काष्ठा mixart_mgr *mgr,
				   काष्ठा mixart_msg *request, u32 notअगर_event)
अणु
	पूर्णांक err;
	रुको_queue_entry_t रुको;
	दीर्घ समयout;

	अगर (snd_BUG_ON(!notअगर_event))
		वापस -EINVAL;
	अगर (snd_BUG_ON((notअगर_event & MSG_TYPE_MASK) != MSG_TYPE_NOTIFY))
		वापस -EINVAL;
	अगर (snd_BUG_ON(notअगर_event & MSG_CANCEL_NOTIFY_MASK))
		वापस -EINVAL;

	init_रुकोqueue_entry(&रुको, current);

	mutex_lock(&mgr->msg_lock);
	/* send the message */
	err = send_msg(mgr, request, MSG_DEFAULT_SIZE, 1, &notअगर_event);  /* send and mark the notअगरication event pending */
	अगर(err) अणु
		mutex_unlock(&mgr->msg_lock);
		वापस err;
	पूर्ण

	set_current_state(TASK_UNINTERRUPTIBLE);
	add_रुको_queue(&mgr->msg_sleep, &रुको);
	mutex_unlock(&mgr->msg_lock);
	समयout = schedule_समयout(MSG_TIMEOUT_JIFFIES);
	हटाओ_रुको_queue(&mgr->msg_sleep, &रुको);

	अगर (! समयout) अणु
		/* error - no ack */
		dev_err(&mgr->pci->dev,
			"error: notification %x not received\n", notअगर_event);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण


पूर्णांक snd_mixart_send_msg_nonblock(काष्ठा mixart_mgr *mgr, काष्ठा mixart_msg *request)
अणु
	u32 message_frame;
	पूर्णांक err;

	/* just send the message (करो not mark it as a pending one) */
	mutex_lock(&mgr->msg_lock);
	err = send_msg(mgr, request, MSG_DEFAULT_SIZE, 0, &message_frame);
	mutex_unlock(&mgr->msg_lock);

	/* the answer will be handled by snd_काष्ठा mixart_msgasklet()  */
	atomic_inc(&mgr->msg_processed);

	वापस err;
पूर्ण


/* common buffer of पूर्णांकerrupt to send/receive messages */
अटल u32 mixart_msg_data[MSG_DEFAULT_SIZE / 4];


अटल व्योम snd_mixart_process_msg(काष्ठा mixart_mgr *mgr)
अणु
	काष्ठा mixart_msg resp;
	u32 msg, addr, type;
	पूर्णांक err;

	जबतक (mgr->msg_fअगरo_पढ़ोptr != mgr->msg_fअगरo_ग_लिखोptr) अणु
		msg = mgr->msg_fअगरo[mgr->msg_fअगरo_पढ़ोptr];
		mgr->msg_fअगरo_पढ़ोptr++;
		mgr->msg_fअगरo_पढ़ोptr %= MSG_FIFO_SIZE;

		/* process the message ... */
		addr = msg & ~MSG_TYPE_MASK;
		type = msg & MSG_TYPE_MASK;

		चयन (type) अणु
		हाल MSG_TYPE_ANSWER:
			/* answer to a message on that we did not रुको क्रम (send_msg_nonblock) */
			resp.message_id = 0;
			resp.data = mixart_msg_data;
			resp.size = माप(mixart_msg_data);
			err = get_msg(mgr, &resp, addr);
			अगर( err < 0 ) अणु
				dev_err(&mgr->pci->dev,
					"error(%d) reading mf %x\n",
					err, msg);
				अवरोध;
			पूर्ण

			चयन(resp.message_id) अणु
			हाल MSG_STREAM_START_INPUT_STAGE_PACKET:
			हाल MSG_STREAM_START_OUTPUT_STAGE_PACKET:
			हाल MSG_STREAM_STOP_INPUT_STAGE_PACKET:
			हाल MSG_STREAM_STOP_OUTPUT_STAGE_PACKET:
				अगर(mixart_msg_data[0])
					dev_err(&mgr->pci->dev,
						"error MSG_STREAM_ST***_***PUT_STAGE_PACKET status=%x\n",
						mixart_msg_data[0]);
				अवरोध;
			शेष:
				dev_dbg(&mgr->pci->dev,
					"received mf(%x) : msg_id(%x) uid(%x, %x) size(%zd)\n",
					   msg, resp.message_id, resp.uid.object_id, resp.uid.desc, resp.size);
				अवरोध;
			पूर्ण
			अवरोध;
 		हाल MSG_TYPE_NOTIFY:
			/* msg contains no address ! करो not get_msg() ! */
		हाल MSG_TYPE_COMMAND:
			/* get_msg() necessary */
		शेष:
			dev_err(&mgr->pci->dev,
				"doesn't know what to do with message %x\n",
				msg);
		पूर्ण /* चयन type */

		/* decrement counter */
		atomic_dec(&mgr->msg_processed);

	पूर्ण /* जबतक there is a msg in fअगरo */
पूर्ण


irqवापस_t snd_mixart_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा mixart_mgr *mgr = dev_id;
	u32 it_reg;

	it_reg = पढ़ोl_le(MIXART_REG(mgr, MIXART_PCI_OMISR_OFFSET));
	अगर( !(it_reg & MIXART_OIDI) ) अणु
		/* this device did not cause the पूर्णांकerrupt */
		वापस IRQ_NONE;
	पूर्ण

	/* mask all पूर्णांकerrupts */
	ग_लिखोl_le(MIXART_HOST_ALL_INTERRUPT_MASKED, MIXART_REG(mgr, MIXART_PCI_OMIMR_OFFSET));

	/* outकरोorbell रेजिस्टर clear */
	it_reg = पढ़ोl(MIXART_REG(mgr, MIXART_PCI_ODBR_OFFSET));
	ग_लिखोl(it_reg, MIXART_REG(mgr, MIXART_PCI_ODBR_OFFSET));

	/* clear पूर्णांकerrupt */
	ग_लिखोl_le( MIXART_OIDI, MIXART_REG(mgr, MIXART_PCI_OMISR_OFFSET) );

	वापस IRQ_WAKE_THREAD;
पूर्ण

irqवापस_t snd_mixart_thपढ़ोed_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा mixart_mgr *mgr = dev_id;
	पूर्णांक err;
	काष्ठा mixart_msg resp;
	u32 msg;

	mutex_lock(&mgr->lock);
	/* process पूर्णांकerrupt */
	जबतक (retrieve_msg_frame(mgr, &msg)) अणु

		चयन (msg & MSG_TYPE_MASK) अणु
		हाल MSG_TYPE_COMMAND:
			resp.message_id = 0;
			resp.data = mixart_msg_data;
			resp.size = माप(mixart_msg_data);
			err = get_msg(mgr, &resp, msg & ~MSG_TYPE_MASK);
			अगर( err < 0 ) अणु
				dev_err(&mgr->pci->dev,
					"interrupt: error(%d) reading mf %x\n",
					err, msg);
				अवरोध;
			पूर्ण

			अगर(resp.message_id == MSG_SERVICES_TIMER_NOTIFY) अणु
				पूर्णांक i;
				काष्ठा mixart_समयr_notअगरy *notअगरy;
				notअगरy = (काष्ठा mixart_समयr_notअगरy *)mixart_msg_data;

				क्रम(i=0; i<notअगरy->stream_count; i++) अणु

					u32 buffer_id = notअगरy->streams[i].buffer_id;
					अचिन्हित पूर्णांक chip_number =  (buffer_id & MIXART_NOTIFY_CARD_MASK) >> MIXART_NOTIFY_CARD_OFFSET; /* card0 to 3 */
					अचिन्हित पूर्णांक pcm_number  =  (buffer_id & MIXART_NOTIFY_PCM_MASK ) >> MIXART_NOTIFY_PCM_OFFSET;  /* pcm0 to 3  */
					अचिन्हित पूर्णांक sub_number  =   buffer_id & MIXART_NOTIFY_SUBS_MASK;             /* 0 to MIXART_PLAYBACK_STREAMS */
					अचिन्हित पूर्णांक is_capture  = ((buffer_id & MIXART_NOTIFY_CAPT_MASK) != 0);      /* playback == 0 / capture == 1 */

					काष्ठा snd_mixart *chip  = mgr->chip[chip_number];
					काष्ठा mixart_stream *stream;

					अगर ((chip_number >= mgr->num_cards) || (pcm_number >= MIXART_PCM_TOTAL) || (sub_number >= MIXART_PLAYBACK_STREAMS)) अणु
						dev_err(&mgr->pci->dev,
							"error MSG_SERVICES_TIMER_NOTIFY buffer_id (%x) pos(%d)\n",
							   buffer_id, notअगरy->streams[i].sample_pos_low_part);
						अवरोध;
					पूर्ण

					अगर (is_capture)
						stream = &chip->capture_stream[pcm_number];
					अन्यथा
						stream = &chip->playback_stream[pcm_number][sub_number];

					अगर (stream->substream && (stream->status == MIXART_STREAM_STATUS_RUNNING)) अणु
						काष्ठा snd_pcm_runसमय *runसमय = stream->substream->runसमय;
						पूर्णांक elapsed = 0;
						u64 sample_count = ((u64)notअगरy->streams[i].sample_pos_high_part) << 32;
						sample_count |= notअगरy->streams[i].sample_pos_low_part;

						जबतक (1) अणु
							u64 new_elapse_pos = stream->असल_period_elapsed +  runसमय->period_size;

							अगर (new_elapse_pos > sample_count) अणु
								अवरोध; /* जबतक */
							पूर्ण
							अन्यथा अणु
								elapsed = 1;
								stream->buf_periods++;
								अगर (stream->buf_periods >= runसमय->periods)
									stream->buf_periods = 0;

								stream->असल_period_elapsed = new_elapse_pos;
							पूर्ण
						पूर्ण
						stream->buf_period_frag = (u32)( sample_count - stream->असल_period_elapsed );

						अगर(elapsed) अणु
							mutex_unlock(&mgr->lock);
							snd_pcm_period_elapsed(stream->substream);
							mutex_lock(&mgr->lock);
						पूर्ण
					पूर्ण
				पूर्ण
				अवरोध;
			पूर्ण
			अगर(resp.message_id == MSG_SERVICES_REPORT_TRACES) अणु
				अगर(resp.size > 1) अणु
#अगर_अघोषित __BIG_ENDIAN
					/* Traces are text: the swapped msg_data has to be swapped back ! */
					पूर्णांक i;
					क्रम(i=0; i<(resp.size/4); i++) अणु
						((__be32*)mixart_msg_data)[i] = cpu_to_be32((mixart_msg_data)[i]);
					पूर्ण
#पूर्ण_अगर
					((अक्षर*)mixart_msg_data)[resp.size - 1] = 0;
					dev_dbg(&mgr->pci->dev,
						"MIXART TRACE : %s\n",
						(अक्षर *)mixart_msg_data);
				पूर्ण
				अवरोध;
			पूर्ण

			dev_dbg(&mgr->pci->dev, "command %x not handled\n",
				resp.message_id);
			अवरोध;

		हाल MSG_TYPE_NOTIFY:
			अगर(msg & MSG_CANCEL_NOTIFY_MASK) अणु
				msg &= ~MSG_CANCEL_NOTIFY_MASK;
				dev_err(&mgr->pci->dev,
					"canceled notification %x !\n", msg);
			पूर्ण
			fallthrough;
		हाल MSG_TYPE_ANSWER:
			/* answer or notअगरication to a message we are रुकोing क्रम*/
			mutex_lock(&mgr->msg_lock);
			अगर( (msg & ~MSG_TYPE_MASK) == mgr->pending_event ) अणु
				wake_up(&mgr->msg_sleep);
				mgr->pending_event = 0;
			पूर्ण
			/* answer to a message we did't want to रुको क्रम */
			अन्यथा अणु
				mgr->msg_fअगरo[mgr->msg_fअगरo_ग_लिखोptr] = msg;
				mgr->msg_fअगरo_ग_लिखोptr++;
				mgr->msg_fअगरo_ग_लिखोptr %= MSG_FIFO_SIZE;
				snd_mixart_process_msg(mgr);
			पूर्ण
			mutex_unlock(&mgr->msg_lock);
			अवरोध;
		हाल MSG_TYPE_REQUEST:
		शेष:
			dev_dbg(&mgr->pci->dev,
				"interrupt received request %x\n", msg);
			/* TODO : are there things to करो here ? */
			अवरोध;
		पूर्ण /* चयन on msg type */
	पूर्ण /* जबतक there are msgs */

	/* allow पूर्णांकerrupt again */
	ग_लिखोl_le( MIXART_ALLOW_OUTBOUND_DOORBELL, MIXART_REG( mgr, MIXART_PCI_OMIMR_OFFSET));

	mutex_unlock(&mgr->lock);

	वापस IRQ_HANDLED;
पूर्ण


व्योम snd_mixart_init_mailbox(काष्ठा mixart_mgr *mgr)
अणु
	ग_लिखोl( 0, MIXART_MEM( mgr, MSG_HOST_RSC_PROTECTION ) );
	ग_लिखोl( 0, MIXART_MEM( mgr, MSG_AGENT_RSC_PROTECTION ) );

	/* allow outbound messagebox to generate पूर्णांकerrupts */
	अगर(mgr->irq >= 0) अणु
		ग_लिखोl_le( MIXART_ALLOW_OUTBOUND_DOORBELL, MIXART_REG( mgr, MIXART_PCI_OMIMR_OFFSET));
	पूर्ण
	वापस;
पूर्ण

व्योम snd_mixart_निकास_mailbox(काष्ठा mixart_mgr *mgr)
अणु
	/* no more पूर्णांकerrupts on outbound messagebox */
	ग_लिखोl_le( MIXART_HOST_ALL_INTERRUPT_MASKED, MIXART_REG( mgr, MIXART_PCI_OMIMR_OFFSET));
	वापस;
पूर्ण

व्योम snd_mixart_reset_board(काष्ठा mixart_mgr *mgr)
अणु
	/* reset miXart */
	ग_लिखोl_be( 1, MIXART_REG(mgr, MIXART_BA1_BRUTAL_RESET_OFFSET) );
	वापस;
पूर्ण
