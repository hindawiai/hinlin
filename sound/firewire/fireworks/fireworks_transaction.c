<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * fireworks_transaction.c - a part of driver क्रम Fireworks based devices
 *
 * Copyright (c) 2013-2014 Takashi Sakamoto
 */

/*
 * Fireworks have its own transaction. The transaction can be delivered by AV/C
 * Venकरोr Specअगरic command frame or usual asynchronous transaction. At least,
 * Winकरोws driver and firmware version 5.5 or later करोn't use AV/C command.
 *
 * Transaction substance:
 *  At first, 6 data exist. Following to the data, parameters क्रम each command
 *  exist. All of the parameters are 32 bit aligned to big endian.
 *   data[0]:	Length of transaction substance
 *   data[1]:	Transaction version
 *   data[2]:	Sequence number. This is incremented by the device
 *   data[3]:	Transaction category
 *   data[4]:	Transaction command
 *   data[5]:	Return value in response.
 *   data[6-]:	Parameters
 *
 * Transaction address:
 *  command:	0xecc000000000
 *  response:	0xecc080000000 (शेष)
 *
 * I note that the address क्रम response can be changed by command. But this
 * module uses the शेष address.
 */
#समावेश "./fireworks.h"

#घोषणा MEMORY_SPACE_EFW_COMMAND	0xecc000000000ULL
#घोषणा MEMORY_SPACE_EFW_RESPONSE	0xecc080000000ULL

#घोषणा ERROR_RETRIES 3
#घोषणा ERROR_DELAY_MS 5
#घोषणा EFC_TIMEOUT_MS 125

अटल DEFINE_SPINLOCK(instances_lock);
अटल काष्ठा snd_efw *instances[SNDRV_CARDS] = SNDRV_DEFAULT_PTR;

अटल DEFINE_SPINLOCK(transaction_queues_lock);
अटल LIST_HEAD(transaction_queues);

क्रमागत transaction_queue_state अणु
	STATE_PENDING,
	STATE_BUS_RESET,
	STATE_COMPLETE
पूर्ण;

काष्ठा transaction_queue अणु
	काष्ठा list_head list;
	काष्ठा fw_unit *unit;
	व्योम *buf;
	अचिन्हित पूर्णांक size;
	u32 seqnum;
	क्रमागत transaction_queue_state state;
	रुको_queue_head_t रुको;
पूर्ण;

पूर्णांक snd_efw_transaction_cmd(काष्ठा fw_unit *unit,
			    स्थिर व्योम *cmd, अचिन्हित पूर्णांक size)
अणु
	वापस snd_fw_transaction(unit, TCODE_WRITE_BLOCK_REQUEST,
				  MEMORY_SPACE_EFW_COMMAND,
				  (व्योम *)cmd, size, 0);
पूर्ण

पूर्णांक snd_efw_transaction_run(काष्ठा fw_unit *unit,
			    स्थिर व्योम *cmd, अचिन्हित पूर्णांक cmd_size,
			    व्योम *resp, अचिन्हित पूर्णांक resp_size)
अणु
	काष्ठा transaction_queue t;
	अचिन्हित पूर्णांक tries;
	पूर्णांक ret;

	t.unit = unit;
	t.buf = resp;
	t.size = resp_size;
	t.seqnum = be32_to_cpu(((काष्ठा snd_efw_transaction *)cmd)->seqnum) + 1;
	t.state = STATE_PENDING;
	init_रुकोqueue_head(&t.रुको);

	spin_lock_irq(&transaction_queues_lock);
	list_add_tail(&t.list, &transaction_queues);
	spin_unlock_irq(&transaction_queues_lock);

	tries = 0;
	करो अणु
		ret = snd_efw_transaction_cmd(t.unit, (व्योम *)cmd, cmd_size);
		अगर (ret < 0)
			अवरोध;

		रुको_event_समयout(t.रुको, t.state != STATE_PENDING,
				   msecs_to_jअगरfies(EFC_TIMEOUT_MS));

		अगर (t.state == STATE_COMPLETE) अणु
			ret = t.size;
			अवरोध;
		पूर्ण अन्यथा अगर (t.state == STATE_BUS_RESET) अणु
			msleep(ERROR_DELAY_MS);
		पूर्ण अन्यथा अगर (++tries >= ERROR_RETRIES) अणु
			dev_err(&t.unit->device, "EFW transaction timed out\n");
			ret = -EIO;
			अवरोध;
		पूर्ण
	पूर्ण जबतक (1);

	spin_lock_irq(&transaction_queues_lock);
	list_del(&t.list);
	spin_unlock_irq(&transaction_queues_lock);

	वापस ret;
पूर्ण

अटल व्योम
copy_resp_to_buf(काष्ठा snd_efw *efw, व्योम *data, माप_प्रकार length, पूर्णांक *rcode)
अणु
	माप_प्रकार capacity, till_end;
	काष्ठा snd_efw_transaction *t;

	t = (काष्ठा snd_efw_transaction *)data;
	length = min_t(माप_प्रकार, be32_to_cpu(t->length) * माप(u32), length);

	spin_lock(&efw->lock);

	अगर (efw->push_ptr < efw->pull_ptr)
		capacity = (अचिन्हित पूर्णांक)(efw->pull_ptr - efw->push_ptr);
	अन्यथा
		capacity = snd_efw_resp_buf_size -
			   (अचिन्हित पूर्णांक)(efw->push_ptr - efw->pull_ptr);

	/* confirm enough space क्रम this response */
	अगर (capacity < length) अणु
		*rcode = RCODE_CONFLICT_ERROR;
		जाओ end;
	पूर्ण

	/* copy to ring buffer */
	जबतक (length > 0) अणु
		till_end = snd_efw_resp_buf_size -
			   (अचिन्हित पूर्णांक)(efw->push_ptr - efw->resp_buf);
		till_end = min_t(अचिन्हित पूर्णांक, length, till_end);

		स_नकल(efw->push_ptr, data, till_end);

		efw->push_ptr += till_end;
		अगर (efw->push_ptr >= efw->resp_buf + snd_efw_resp_buf_size)
			efw->push_ptr -= snd_efw_resp_buf_size;

		length -= till_end;
		data += till_end;
	पूर्ण

	/* क्रम hwdep */
	wake_up(&efw->hwdep_रुको);

	*rcode = RCODE_COMPLETE;
end:
	spin_unlock_irq(&efw->lock);
पूर्ण

अटल व्योम
handle_resp_क्रम_user(काष्ठा fw_card *card, पूर्णांक generation, पूर्णांक source,
		     व्योम *data, माप_प्रकार length, पूर्णांक *rcode)
अणु
	काष्ठा fw_device *device;
	काष्ठा snd_efw *efw;
	अचिन्हित पूर्णांक i;

	spin_lock_irq(&instances_lock);

	क्रम (i = 0; i < SNDRV_CARDS; i++) अणु
		efw = instances[i];
		अगर (efw == शून्य)
			जारी;
		device = fw_parent_device(efw->unit);
		अगर ((device->card != card) ||
		    (device->generation != generation))
			जारी;
		smp_rmb();	/* node id vs. generation */
		अगर (device->node_id != source)
			जारी;

		अवरोध;
	पूर्ण
	अगर (i == SNDRV_CARDS)
		जाओ end;

	copy_resp_to_buf(efw, data, length, rcode);
end:
	spin_unlock(&instances_lock);
पूर्ण

अटल व्योम
handle_resp_क्रम_kernel(काष्ठा fw_card *card, पूर्णांक generation, पूर्णांक source,
		       व्योम *data, माप_प्रकार length, पूर्णांक *rcode, u32 seqnum)
अणु
	काष्ठा fw_device *device;
	काष्ठा transaction_queue *t;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&transaction_queues_lock, flags);
	list_क्रम_each_entry(t, &transaction_queues, list) अणु
		device = fw_parent_device(t->unit);
		अगर ((device->card != card) ||
		    (device->generation != generation))
			जारी;
		smp_rmb();	/* node_id vs. generation */
		अगर (device->node_id != source)
			जारी;

		अगर ((t->state == STATE_PENDING) && (t->seqnum == seqnum)) अणु
			t->state = STATE_COMPLETE;
			t->size = min_t(अचिन्हित पूर्णांक, length, t->size);
			स_नकल(t->buf, data, t->size);
			wake_up(&t->रुको);
			*rcode = RCODE_COMPLETE;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&transaction_queues_lock, flags);
पूर्ण

अटल व्योम
efw_response(काष्ठा fw_card *card, काष्ठा fw_request *request,
	     पूर्णांक tcode, पूर्णांक destination, पूर्णांक source,
	     पूर्णांक generation, अचिन्हित दीर्घ दीर्घ offset,
	     व्योम *data, माप_प्रकार length, व्योम *callback_data)
अणु
	पूर्णांक rcode, dummy;
	u32 seqnum;

	rcode = RCODE_TYPE_ERROR;
	अगर (length < माप(काष्ठा snd_efw_transaction)) अणु
		rcode = RCODE_DATA_ERROR;
		जाओ end;
	पूर्ण अन्यथा अगर (offset != MEMORY_SPACE_EFW_RESPONSE) अणु
		rcode = RCODE_ADDRESS_ERROR;
		जाओ end;
	पूर्ण

	seqnum = be32_to_cpu(((काष्ठा snd_efw_transaction *)data)->seqnum);
	अगर (seqnum > SND_EFW_TRANSACTION_USER_SEQNUM_MAX + 1) अणु
		handle_resp_क्रम_kernel(card, generation, source,
				       data, length, &rcode, seqnum);
		अगर (snd_efw_resp_buf_debug)
			handle_resp_क्रम_user(card, generation, source,
					     data, length, &dummy);
	पूर्ण अन्यथा अणु
		handle_resp_क्रम_user(card, generation, source,
				     data, length, &rcode);
	पूर्ण
end:
	fw_send_response(card, request, rcode);
पूर्ण

व्योम snd_efw_transaction_add_instance(काष्ठा snd_efw *efw)
अणु
	अचिन्हित पूर्णांक i;

	spin_lock_irq(&instances_lock);

	क्रम (i = 0; i < SNDRV_CARDS; i++) अणु
		अगर (instances[i] != शून्य)
			जारी;
		instances[i] = efw;
		अवरोध;
	पूर्ण

	spin_unlock_irq(&instances_lock);
पूर्ण

व्योम snd_efw_transaction_हटाओ_instance(काष्ठा snd_efw *efw)
अणु
	अचिन्हित पूर्णांक i;

	spin_lock_irq(&instances_lock);

	क्रम (i = 0; i < SNDRV_CARDS; i++) अणु
		अगर (instances[i] != efw)
			जारी;
		instances[i] = शून्य;
	पूर्ण

	spin_unlock_irq(&instances_lock);
पूर्ण

व्योम snd_efw_transaction_bus_reset(काष्ठा fw_unit *unit)
अणु
	काष्ठा transaction_queue *t;

	spin_lock_irq(&transaction_queues_lock);
	list_क्रम_each_entry(t, &transaction_queues, list) अणु
		अगर ((t->unit == unit) &&
		    (t->state == STATE_PENDING)) अणु
			t->state = STATE_BUS_RESET;
			wake_up(&t->रुको);
		पूर्ण
	पूर्ण
	spin_unlock_irq(&transaction_queues_lock);
पूर्ण

अटल काष्ठा fw_address_handler resp_रेजिस्टर_handler = अणु
	.length = SND_EFW_RESPONSE_MAXIMUM_BYTES,
	.address_callback = efw_response
पूर्ण;

पूर्णांक snd_efw_transaction_रेजिस्टर(व्योम)
अणु
	अटल स्थिर काष्ठा fw_address_region resp_रेजिस्टर_region = अणु
		.start	= MEMORY_SPACE_EFW_RESPONSE,
		.end	= MEMORY_SPACE_EFW_RESPONSE +
			  SND_EFW_RESPONSE_MAXIMUM_BYTES
	पूर्ण;
	वापस fw_core_add_address_handler(&resp_रेजिस्टर_handler,
					   &resp_रेजिस्टर_region);
पूर्ण

व्योम snd_efw_transaction_unरेजिस्टर(व्योम)
अणु
	WARN_ON(!list_empty(&transaction_queues));
	fw_core_हटाओ_address_handler(&resp_रेजिस्टर_handler);
पूर्ण
