<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Function Control Protocol (IEC 61883-1) helper functions
 *
 * Copyright (c) Clemens Ladisch <clemens@ladisch.de>
 */

#समावेश <linux/device.h>
#समावेश <linux/firewire.h>
#समावेश <linux/firewire-स्थिरants.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/रुको.h>
#समावेश <linux/delay.h>
#समावेश "fcp.h"
#समावेश "lib.h"
#समावेश "amdtp-stream.h"

#घोषणा CTS_AVC 0x00

#घोषणा ERROR_RETRIES	3
#घोषणा ERROR_DELAY_MS	5
#घोषणा FCP_TIMEOUT_MS	125

पूर्णांक avc_general_set_sig_fmt(काष्ठा fw_unit *unit, अचिन्हित पूर्णांक rate,
			    क्रमागत avc_general_plug_dir dir,
			    अचिन्हित लघु pid)
अणु
	अचिन्हित पूर्णांक sfc;
	u8 *buf;
	bool flag;
	पूर्णांक err;

	flag = false;
	क्रम (sfc = 0; sfc < CIP_SFC_COUNT; sfc++) अणु
		अगर (amdtp_rate_table[sfc] == rate) अणु
			flag = true;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!flag)
		वापस -EINVAL;

	buf = kzalloc(8, GFP_KERNEL);
	अगर (buf == शून्य)
		वापस -ENOMEM;

	buf[0] = 0x00;		/* AV/C CONTROL */
	buf[1] = 0xff;		/* UNIT */
	अगर (dir == AVC_GENERAL_PLUG_सूची_IN)
		buf[2] = 0x19;	/* INPUT PLUG SIGNAL FORMAT */
	अन्यथा
		buf[2] = 0x18;	/* OUTPUT PLUG SIGNAL FORMAT */
	buf[3] = 0xff & pid;	/* plug id */
	buf[4] = 0x90;		/* EOH_1, Form_1, FMT. AM824 */
	buf[5] = 0x07 & sfc;	/* FDF-hi. AM824, frequency */
	buf[6] = 0xff;		/* FDF-mid. AM824, SYT hi (not used)*/
	buf[7] = 0xff;		/* FDF-low. AM824, SYT lo (not used) */

	/* करो transaction and check buf[1-5] are the same against command */
	err = fcp_avc_transaction(unit, buf, 8, buf, 8,
				  BIT(1) | BIT(2) | BIT(3) | BIT(4) | BIT(5));
	अगर (err < 0)
		;
	अन्यथा अगर (err < 8)
		err = -EIO;
	अन्यथा अगर (buf[0] == 0x08) /* NOT IMPLEMENTED */
		err = -ENOSYS;
	अन्यथा अगर (buf[0] == 0x0a) /* REJECTED */
		err = -EINVAL;
	अगर (err < 0)
		जाओ end;

	err = 0;
end:
	kमुक्त(buf);
	वापस err;
पूर्ण
EXPORT_SYMBOL(avc_general_set_sig_fmt);

पूर्णांक avc_general_get_sig_fmt(काष्ठा fw_unit *unit, अचिन्हित पूर्णांक *rate,
			    क्रमागत avc_general_plug_dir dir,
			    अचिन्हित लघु pid)
अणु
	अचिन्हित पूर्णांक sfc;
	u8 *buf;
	पूर्णांक err;

	buf = kzalloc(8, GFP_KERNEL);
	अगर (buf == शून्य)
		वापस -ENOMEM;

	buf[0] = 0x01;		/* AV/C STATUS */
	buf[1] = 0xff;		/* Unit */
	अगर (dir == AVC_GENERAL_PLUG_सूची_IN)
		buf[2] = 0x19;	/* INPUT PLUG SIGNAL FORMAT */
	अन्यथा
		buf[2] = 0x18;	/* OUTPUT PLUG SIGNAL FORMAT */
	buf[3] = 0xff & pid;	/* plug id */
	buf[4] = 0x90;		/* EOH_1, Form_1, FMT. AM824 */
	buf[5] = 0xff;		/* FDF-hi. AM824, frequency */
	buf[6] = 0xff;		/* FDF-mid. AM824, SYT hi (not used) */
	buf[7] = 0xff;		/* FDF-low. AM824, SYT lo (not used) */

	/* करो transaction and check buf[1-4] are the same against command */
	err = fcp_avc_transaction(unit, buf, 8, buf, 8,
				  BIT(1) | BIT(2) | BIT(3) | BIT(4));
	अगर (err < 0)
		;
	अन्यथा अगर (err < 8)
		err = -EIO;
	अन्यथा अगर (buf[0] == 0x08) /* NOT IMPLEMENTED */
		err = -ENOSYS;
	अन्यथा अगर (buf[0] == 0x0a) /* REJECTED */
		err = -EINVAL;
	अन्यथा अगर (buf[0] == 0x0b) /* IN TRANSITION */
		err = -EAGAIN;
	अगर (err < 0)
		जाओ end;

	/* check sfc field and pick up rate */
	sfc = 0x07 & buf[5];
	अगर (sfc >= CIP_SFC_COUNT) अणु
		err = -EAGAIN;	/* also in transition */
		जाओ end;
	पूर्ण

	*rate = amdtp_rate_table[sfc];
	err = 0;
end:
	kमुक्त(buf);
	वापस err;
पूर्ण
EXPORT_SYMBOL(avc_general_get_sig_fmt);

पूर्णांक avc_general_get_plug_info(काष्ठा fw_unit *unit, अचिन्हित पूर्णांक subunit_type,
			      अचिन्हित पूर्णांक subunit_id, अचिन्हित पूर्णांक subfunction,
			      u8 info[AVC_PLUG_INFO_BUF_BYTES])
अणु
	u8 *buf;
	पूर्णांक err;

	/* extended subunit in spec.4.2 is not supported */
	अगर ((subunit_type == 0x1E) || (subunit_id == 5))
		वापस -EINVAL;

	buf = kzalloc(8, GFP_KERNEL);
	अगर (buf == शून्य)
		वापस -ENOMEM;

	buf[0] = 0x01;	/* AV/C STATUS */
	/* UNIT or Subunit, Functionblock */
	buf[1] = ((subunit_type & 0x1f) << 3) | (subunit_id & 0x7);
	buf[2] = 0x02;	/* PLUG INFO */
	buf[3] = 0xff & subfunction;

	err = fcp_avc_transaction(unit, buf, 8, buf, 8, BIT(1) | BIT(2));
	अगर (err < 0)
		;
	अन्यथा अगर (err < 8)
		err = -EIO;
	अन्यथा अगर (buf[0] == 0x08) /* NOT IMPLEMENTED */
		err = -ENOSYS;
	अन्यथा अगर (buf[0] == 0x0a) /* REJECTED */
		err = -EINVAL;
	अन्यथा अगर (buf[0] == 0x0b) /* IN TRANSITION */
		err = -EAGAIN;
	अगर (err < 0)
		जाओ end;

	info[0] = buf[4];
	info[1] = buf[5];
	info[2] = buf[6];
	info[3] = buf[7];

	err = 0;
end:
	kमुक्त(buf);
	वापस err;
पूर्ण
EXPORT_SYMBOL(avc_general_get_plug_info);

अटल DEFINE_SPINLOCK(transactions_lock);
अटल LIST_HEAD(transactions);

क्रमागत fcp_state अणु
	STATE_PENDING,
	STATE_BUS_RESET,
	STATE_COMPLETE,
	STATE_DEFERRED,
पूर्ण;

काष्ठा fcp_transaction अणु
	काष्ठा list_head list;
	काष्ठा fw_unit *unit;
	व्योम *response_buffer;
	अचिन्हित पूर्णांक response_size;
	अचिन्हित पूर्णांक response_match_bytes;
	क्रमागत fcp_state state;
	रुको_queue_head_t रुको;
	bool deferrable;
पूर्ण;

/**
 * fcp_avc_transaction - send an AV/C command and रुको क्रम its response
 * @unit: a unit on the target device
 * @command: a buffer containing the command frame; must be DMA-able
 * @command_size: the size of @command
 * @response: a buffer क्रम the response frame
 * @response_size: the maximum size of @response
 * @response_match_bytes: a biपंचांगap specअगरying the bytes used to detect the
 *                        correct response frame
 *
 * This function sends a FCP command frame to the target and रुकोs क्रम the
 * corresponding response frame to be वापसed.
 *
 * Because it is possible क्रम multiple FCP transactions to be active at the
 * same समय, the correct response frame is detected by the value of certain
 * bytes.  These bytes must be set in @response beक्रमe calling this function,
 * and the corresponding bits must be set in @response_match_bytes.
 *
 * @command and @response can poपूर्णांक to the same buffer.
 *
 * Returns the actual size of the response frame, or a negative error code.
 */
पूर्णांक fcp_avc_transaction(काष्ठा fw_unit *unit,
			स्थिर व्योम *command, अचिन्हित पूर्णांक command_size,
			व्योम *response, अचिन्हित पूर्णांक response_size,
			अचिन्हित पूर्णांक response_match_bytes)
अणु
	काष्ठा fcp_transaction t;
	पूर्णांक tcode, ret, tries = 0;

	t.unit = unit;
	t.response_buffer = response;
	t.response_size = response_size;
	t.response_match_bytes = response_match_bytes;
	t.state = STATE_PENDING;
	init_रुकोqueue_head(&t.रुको);

	अगर (*(स्थिर u8 *)command == 0x00 || *(स्थिर u8 *)command == 0x03)
		t.deferrable = true;

	spin_lock_irq(&transactions_lock);
	list_add_tail(&t.list, &transactions);
	spin_unlock_irq(&transactions_lock);

	क्रम (;;) अणु
		tcode = command_size == 4 ? TCODE_WRITE_QUADLET_REQUEST
					  : TCODE_WRITE_BLOCK_REQUEST;
		ret = snd_fw_transaction(t.unit, tcode,
					 CSR_REGISTER_BASE + CSR_FCP_COMMAND,
					 (व्योम *)command, command_size, 0);
		अगर (ret < 0)
			अवरोध;
deferred:
		रुको_event_समयout(t.रुको, t.state != STATE_PENDING,
				   msecs_to_jअगरfies(FCP_TIMEOUT_MS));

		अगर (t.state == STATE_DEFERRED) अणु
			/*
			 * 'AV/C General Specification' define no समय limit
			 * on command completion once an INTERIM response has
			 * been sent. but we promise to finish this function
			 * क्रम a caller. Here we use FCP_TIMEOUT_MS क्रम next
			 * पूर्णांकerval. This is not in the specअगरication.
			 */
			t.state = STATE_PENDING;
			जाओ deferred;
		पूर्ण अन्यथा अगर (t.state == STATE_COMPLETE) अणु
			ret = t.response_size;
			अवरोध;
		पूर्ण अन्यथा अगर (t.state == STATE_BUS_RESET) अणु
			msleep(ERROR_DELAY_MS);
		पूर्ण अन्यथा अगर (++tries >= ERROR_RETRIES) अणु
			dev_err(&t.unit->device, "FCP command timed out\n");
			ret = -EIO;
			अवरोध;
		पूर्ण
	पूर्ण

	spin_lock_irq(&transactions_lock);
	list_del(&t.list);
	spin_unlock_irq(&transactions_lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(fcp_avc_transaction);

/**
 * fcp_bus_reset - inक्रमm the target handler about a bus reset
 * @unit: the unit that might be used by fcp_avc_transaction()
 *
 * This function must be called from the driver's .update handler to inक्रमm
 * the FCP transaction handler that a bus reset has happened.  Any pending FCP
 * transactions are retried.
 */
व्योम fcp_bus_reset(काष्ठा fw_unit *unit)
अणु
	काष्ठा fcp_transaction *t;

	spin_lock_irq(&transactions_lock);
	list_क्रम_each_entry(t, &transactions, list) अणु
		अगर (t->unit == unit &&
		    (t->state == STATE_PENDING ||
		     t->state == STATE_DEFERRED)) अणु
			t->state = STATE_BUS_RESET;
			wake_up(&t->रुको);
		पूर्ण
	पूर्ण
	spin_unlock_irq(&transactions_lock);
पूर्ण
EXPORT_SYMBOL(fcp_bus_reset);

/* checks whether the response matches the masked bytes in response_buffer */
अटल bool is_matching_response(काष्ठा fcp_transaction *transaction,
				 स्थिर व्योम *response, माप_प्रकार length)
अणु
	स्थिर u8 *p1, *p2;
	अचिन्हित पूर्णांक mask, i;

	p1 = response;
	p2 = transaction->response_buffer;
	mask = transaction->response_match_bytes;

	क्रम (i = 0; ; ++i) अणु
		अगर ((mask & 1) && p1[i] != p2[i])
			वापस false;
		mask >>= 1;
		अगर (!mask)
			वापस true;
		अगर (--length == 0)
			वापस false;
	पूर्ण
पूर्ण

अटल व्योम fcp_response(काष्ठा fw_card *card, काष्ठा fw_request *request,
			 पूर्णांक tcode, पूर्णांक destination, पूर्णांक source,
			 पूर्णांक generation, अचिन्हित दीर्घ दीर्घ offset,
			 व्योम *data, माप_प्रकार length, व्योम *callback_data)
अणु
	काष्ठा fcp_transaction *t;
	अचिन्हित दीर्घ flags;

	अगर (length < 1 || (*(स्थिर u8 *)data & 0xf0) != CTS_AVC)
		वापस;

	spin_lock_irqsave(&transactions_lock, flags);
	list_क्रम_each_entry(t, &transactions, list) अणु
		काष्ठा fw_device *device = fw_parent_device(t->unit);
		अगर (device->card != card ||
		    device->generation != generation)
			जारी;
		smp_rmb(); /* node_id vs. generation */
		अगर (device->node_id != source)
			जारी;

		अगर (t->state == STATE_PENDING &&
		    is_matching_response(t, data, length)) अणु
			अगर (t->deferrable && *(स्थिर u8 *)data == 0x0f) अणु
				t->state = STATE_DEFERRED;
			पूर्ण अन्यथा अणु
				t->state = STATE_COMPLETE;
				t->response_size = min_t(अचिन्हित पूर्णांक, length,
							 t->response_size);
				स_नकल(t->response_buffer, data,
				       t->response_size);
			पूर्ण
			wake_up(&t->रुको);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&transactions_lock, flags);
पूर्ण

अटल काष्ठा fw_address_handler response_रेजिस्टर_handler = अणु
	.length = 0x200,
	.address_callback = fcp_response,
पूर्ण;

अटल पूर्णांक __init fcp_module_init(व्योम)
अणु
	अटल स्थिर काष्ठा fw_address_region response_रेजिस्टर_region = अणु
		.start = CSR_REGISTER_BASE + CSR_FCP_RESPONSE,
		.end = CSR_REGISTER_BASE + CSR_FCP_END,
	पूर्ण;

	fw_core_add_address_handler(&response_रेजिस्टर_handler,
				    &response_रेजिस्टर_region);

	वापस 0;
पूर्ण

अटल व्योम __निकास fcp_module_निकास(व्योम)
अणु
	WARN_ON(!list_empty(&transactions));
	fw_core_हटाओ_address_handler(&response_रेजिस्टर_handler);
पूर्ण

module_init(fcp_module_init);
module_निकास(fcp_module_निकास);
