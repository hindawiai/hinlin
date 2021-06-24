<शैली गुरु>
/*
   HIDP implementation क्रम Linux Bluetooth stack (BlueZ).
   Copyright (C) 2003-2004 Marcel Holपंचांगann <marcel@holपंचांगann.org>
   Copyright (C) 2013 David Herrmann <dh.herrmann@gmail.com>

   This program is मुक्त software; you can redistribute it and/or modअगरy
   it under the terms of the GNU General Public License version 2 as
   published by the Free Software Foundation;

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF THIRD PARTY RIGHTS.
   IN NO EVENT SHALL THE COPYRIGHT HOLDER(S) AND AUTHOR(S) BE LIABLE FOR ANY
   CLAIM, OR ANY SPECIAL INसूचीECT OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES
   WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
   ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
   OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

   ALL LIABILITY, INCLUDING LIABILITY FOR INFRINGEMENT OF ANY PATENTS,
   COPYRIGHTS, TRADEMARKS OR OTHER RIGHTS, RELATING TO USE OF THIS
   SOFTWARE IS DISCLAIMED.
*/

#समावेश <linux/kref.h>
#समावेश <linux/module.h>
#समावेश <linux/file.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/hidraw.h>

#समावेश <net/bluetooth/bluetooth.h>
#समावेश <net/bluetooth/hci_core.h>
#समावेश <net/bluetooth/l2cap.h>

#समावेश "hidp.h"

#घोषणा VERSION "1.2"

अटल DECLARE_RWSEM(hidp_session_sem);
अटल DECLARE_WAIT_QUEUE_HEAD(hidp_session_wq);
अटल LIST_HEAD(hidp_session_list);

अटल अचिन्हित अक्षर hidp_keycode[256] = अणु
	  0,   0,   0,   0,  30,  48,  46,  32,  18,  33,  34,  35,  23,  36,
	 37,  38,  50,  49,  24,  25,  16,  19,  31,  20,  22,  47,  17,  45,
	 21,  44,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  28,   1,
	 14,  15,  57,  12,  13,  26,  27,  43,  43,  39,  40,  41,  51,  52,
	 53,  58,  59,  60,  61,  62,  63,  64,  65,  66,  67,  68,  87,  88,
	 99,  70, 119, 110, 102, 104, 111, 107, 109, 106, 105, 108, 103,  69,
	 98,  55,  74,  78,  96,  79,  80,  81,  75,  76,  77,  71,  72,  73,
	 82,  83,  86, 127, 116, 117, 183, 184, 185, 186, 187, 188, 189, 190,
	191, 192, 193, 194, 134, 138, 130, 132, 128, 129, 131, 137, 133, 135,
	136, 113, 115, 114,   0,   0,   0, 121,   0,  89,  93, 124,  92,  94,
	 95,   0,   0,   0, 122, 123,  90,  91,  85,   0,   0,   0,   0,   0,
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	 29,  42,  56, 125,  97,  54, 100, 126, 164, 166, 165, 163, 161, 115,
	114, 113, 150, 158, 159, 128, 136, 177, 178, 176, 142, 152, 173, 140
पूर्ण;

अटल अचिन्हित अक्षर hidp_mkeyspat[] = अणु 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 पूर्ण;

अटल पूर्णांक hidp_session_probe(काष्ठा l2cap_conn *conn,
			      काष्ठा l2cap_user *user);
अटल व्योम hidp_session_हटाओ(काष्ठा l2cap_conn *conn,
				काष्ठा l2cap_user *user);
अटल पूर्णांक hidp_session_thपढ़ो(व्योम *arg);
अटल व्योम hidp_session_terminate(काष्ठा hidp_session *s);

अटल व्योम hidp_copy_session(काष्ठा hidp_session *session, काष्ठा hidp_conninfo *ci)
अणु
	u32 valid_flags = 0;
	स_रखो(ci, 0, माप(*ci));
	bacpy(&ci->bdaddr, &session->bdaddr);

	ci->flags = session->flags & valid_flags;
	ci->state = BT_CONNECTED;

	अगर (session->input) अणु
		ci->venकरोr  = session->input->id.venकरोr;
		ci->product = session->input->id.product;
		ci->version = session->input->id.version;
		अगर (session->input->name)
			strlcpy(ci->name, session->input->name, 128);
		अन्यथा
			strlcpy(ci->name, "HID Boot Device", 128);
	पूर्ण अन्यथा अगर (session->hid) अणु
		ci->venकरोr  = session->hid->venकरोr;
		ci->product = session->hid->product;
		ci->version = session->hid->version;
		strlcpy(ci->name, session->hid->name, 128);
	पूर्ण
पूर्ण

/* assemble skb, queue message on @transmit and wake up the session thपढ़ो */
अटल पूर्णांक hidp_send_message(काष्ठा hidp_session *session, काष्ठा socket *sock,
			     काष्ठा sk_buff_head *transmit, अचिन्हित अक्षर hdr,
			     स्थिर अचिन्हित अक्षर *data, पूर्णांक size)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा sock *sk = sock->sk;
	पूर्णांक ret;

	BT_DBG("session %p data %p size %d", session, data, size);

	अगर (atomic_पढ़ो(&session->terminate))
		वापस -EIO;

	skb = alloc_skb(size + 1, GFP_ATOMIC);
	अगर (!skb) अणु
		BT_ERR("Can't allocate memory for new frame");
		वापस -ENOMEM;
	पूर्ण

	skb_put_u8(skb, hdr);
	अगर (data && size > 0) अणु
		skb_put_data(skb, data, size);
		ret = size;
	पूर्ण अन्यथा अणु
		ret = 0;
	पूर्ण

	skb_queue_tail(transmit, skb);
	wake_up_पूर्णांकerruptible(sk_sleep(sk));

	वापस ret;
पूर्ण

अटल पूर्णांक hidp_send_ctrl_message(काष्ठा hidp_session *session,
				  अचिन्हित अक्षर hdr, स्थिर अचिन्हित अक्षर *data,
				  पूर्णांक size)
अणु
	वापस hidp_send_message(session, session->ctrl_sock,
				 &session->ctrl_transmit, hdr, data, size);
पूर्ण

अटल पूर्णांक hidp_send_पूर्णांकr_message(काष्ठा hidp_session *session,
				  अचिन्हित अक्षर hdr, स्थिर अचिन्हित अक्षर *data,
				  पूर्णांक size)
अणु
	वापस hidp_send_message(session, session->पूर्णांकr_sock,
				 &session->पूर्णांकr_transmit, hdr, data, size);
पूर्ण

अटल पूर्णांक hidp_input_event(काष्ठा input_dev *dev, अचिन्हित पूर्णांक type,
			    अचिन्हित पूर्णांक code, पूर्णांक value)
अणु
	काष्ठा hidp_session *session = input_get_drvdata(dev);
	अचिन्हित अक्षर newleds;
	अचिन्हित अक्षर hdr, data[2];

	BT_DBG("session %p type %d code %d value %d",
	       session, type, code, value);

	अगर (type != EV_LED)
		वापस -1;

	newleds = (!!test_bit(LED_KANA,    dev->led) << 3) |
		  (!!test_bit(LED_COMPOSE, dev->led) << 3) |
		  (!!test_bit(LED_SCROLLL, dev->led) << 2) |
		  (!!test_bit(LED_CAPSL,   dev->led) << 1) |
		  (!!test_bit(LED_NUML,    dev->led) << 0);

	अगर (session->leds == newleds)
		वापस 0;

	session->leds = newleds;

	hdr = HIDP_TRANS_DATA | HIDP_DATA_RTYPE_OUPUT;
	data[0] = 0x01;
	data[1] = newleds;

	वापस hidp_send_पूर्णांकr_message(session, hdr, data, 2);
पूर्ण

अटल व्योम hidp_input_report(काष्ठा hidp_session *session, काष्ठा sk_buff *skb)
अणु
	काष्ठा input_dev *dev = session->input;
	अचिन्हित अक्षर *keys = session->keys;
	अचिन्हित अक्षर *udata = skb->data + 1;
	चिन्हित अक्षर *sdata = skb->data + 1;
	पूर्णांक i, size = skb->len - 1;

	चयन (skb->data[0]) अणु
	हाल 0x01:	/* Keyboard report */
		क्रम (i = 0; i < 8; i++)
			input_report_key(dev, hidp_keycode[i + 224], (udata[0] >> i) & 1);

		/* If all the key codes have been set to 0x01, it means
		 * too many keys were pressed at the same समय. */
		अगर (!स_भेद(udata + 2, hidp_mkeyspat, 6))
			अवरोध;

		क्रम (i = 2; i < 8; i++) अणु
			अगर (keys[i] > 3 && memscan(udata + 2, keys[i], 6) == udata + 8) अणु
				अगर (hidp_keycode[keys[i]])
					input_report_key(dev, hidp_keycode[keys[i]], 0);
				अन्यथा
					BT_ERR("Unknown key (scancode %#x) released.", keys[i]);
			पूर्ण

			अगर (udata[i] > 3 && memscan(keys + 2, udata[i], 6) == keys + 8) अणु
				अगर (hidp_keycode[udata[i]])
					input_report_key(dev, hidp_keycode[udata[i]], 1);
				अन्यथा
					BT_ERR("Unknown key (scancode %#x) pressed.", udata[i]);
			पूर्ण
		पूर्ण

		स_नकल(keys, udata, 8);
		अवरोध;

	हाल 0x02:	/* Mouse report */
		input_report_key(dev, BTN_LEFT,   sdata[0] & 0x01);
		input_report_key(dev, BTN_RIGHT,  sdata[0] & 0x02);
		input_report_key(dev, BTN_MIDDLE, sdata[0] & 0x04);
		input_report_key(dev, BTN_SIDE,   sdata[0] & 0x08);
		input_report_key(dev, BTN_EXTRA,  sdata[0] & 0x10);

		input_report_rel(dev, REL_X, sdata[1]);
		input_report_rel(dev, REL_Y, sdata[2]);

		अगर (size > 3)
			input_report_rel(dev, REL_WHEEL, sdata[3]);
		अवरोध;
	पूर्ण

	input_sync(dev);
पूर्ण

अटल पूर्णांक hidp_get_raw_report(काष्ठा hid_device *hid,
		अचिन्हित अक्षर report_number,
		अचिन्हित अक्षर *data, माप_प्रकार count,
		अचिन्हित अक्षर report_type)
अणु
	काष्ठा hidp_session *session = hid->driver_data;
	काष्ठा sk_buff *skb;
	माप_प्रकार len;
	पूर्णांक numbered_reports = hid->report_क्रमागत[report_type].numbered;
	पूर्णांक ret;

	अगर (atomic_पढ़ो(&session->terminate))
		वापस -EIO;

	चयन (report_type) अणु
	हाल HID_FEATURE_REPORT:
		report_type = HIDP_TRANS_GET_REPORT | HIDP_DATA_RTYPE_FEATURE;
		अवरोध;
	हाल HID_INPUT_REPORT:
		report_type = HIDP_TRANS_GET_REPORT | HIDP_DATA_RTYPE_INPUT;
		अवरोध;
	हाल HID_OUTPUT_REPORT:
		report_type = HIDP_TRANS_GET_REPORT | HIDP_DATA_RTYPE_OUPUT;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (mutex_lock_पूर्णांकerruptible(&session->report_mutex))
		वापस -ERESTARTSYS;

	/* Set up our रुको, and send the report request to the device. */
	session->रुकोing_report_type = report_type & HIDP_DATA_RTYPE_MASK;
	session->रुकोing_report_number = numbered_reports ? report_number : -1;
	set_bit(HIDP_WAITING_FOR_RETURN, &session->flags);
	data[0] = report_number;
	ret = hidp_send_ctrl_message(session, report_type, data, 1);
	अगर (ret < 0)
		जाओ err;

	/* Wait क्रम the वापस of the report. The वापसed report
	   माला_लो put in session->report_वापस.  */
	जबतक (test_bit(HIDP_WAITING_FOR_RETURN, &session->flags) &&
	       !atomic_पढ़ो(&session->terminate)) अणु
		पूर्णांक res;

		res = रुको_event_पूर्णांकerruptible_समयout(session->report_queue,
			!test_bit(HIDP_WAITING_FOR_RETURN, &session->flags)
				|| atomic_पढ़ो(&session->terminate),
			5*HZ);
		अगर (res == 0) अणु
			/* समयout */
			ret = -EIO;
			जाओ err;
		पूर्ण
		अगर (res < 0) अणु
			/* संकेत */
			ret = -ERESTARTSYS;
			जाओ err;
		पूर्ण
	पूर्ण

	skb = session->report_वापस;
	अगर (skb) अणु
		len = skb->len < count ? skb->len : count;
		स_नकल(data, skb->data, len);

		kमुक्त_skb(skb);
		session->report_वापस = शून्य;
	पूर्ण अन्यथा अणु
		/* Device वापसed a HANDSHAKE, indicating  protocol error. */
		len = -EIO;
	पूर्ण

	clear_bit(HIDP_WAITING_FOR_RETURN, &session->flags);
	mutex_unlock(&session->report_mutex);

	वापस len;

err:
	clear_bit(HIDP_WAITING_FOR_RETURN, &session->flags);
	mutex_unlock(&session->report_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक hidp_set_raw_report(काष्ठा hid_device *hid, अचिन्हित अक्षर reportnum,
			       अचिन्हित अक्षर *data, माप_प्रकार count,
			       अचिन्हित अक्षर report_type)
अणु
	काष्ठा hidp_session *session = hid->driver_data;
	पूर्णांक ret;

	चयन (report_type) अणु
	हाल HID_FEATURE_REPORT:
		report_type = HIDP_TRANS_SET_REPORT | HIDP_DATA_RTYPE_FEATURE;
		अवरोध;
	हाल HID_INPUT_REPORT:
		report_type = HIDP_TRANS_SET_REPORT | HIDP_DATA_RTYPE_INPUT;
		अवरोध;
	हाल HID_OUTPUT_REPORT:
		report_type = HIDP_TRANS_SET_REPORT | HIDP_DATA_RTYPE_OUPUT;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (mutex_lock_पूर्णांकerruptible(&session->report_mutex))
		वापस -ERESTARTSYS;

	/* Set up our रुको, and send the report request to the device. */
	data[0] = reportnum;
	set_bit(HIDP_WAITING_FOR_SEND_ACK, &session->flags);
	ret = hidp_send_ctrl_message(session, report_type, data, count);
	अगर (ret < 0)
		जाओ err;

	/* Wait क्रम the ACK from the device. */
	जबतक (test_bit(HIDP_WAITING_FOR_SEND_ACK, &session->flags) &&
	       !atomic_पढ़ो(&session->terminate)) अणु
		पूर्णांक res;

		res = रुको_event_पूर्णांकerruptible_समयout(session->report_queue,
			!test_bit(HIDP_WAITING_FOR_SEND_ACK, &session->flags)
				|| atomic_पढ़ो(&session->terminate),
			10*HZ);
		अगर (res == 0) अणु
			/* समयout */
			ret = -EIO;
			जाओ err;
		पूर्ण
		अगर (res < 0) अणु
			/* संकेत */
			ret = -ERESTARTSYS;
			जाओ err;
		पूर्ण
	पूर्ण

	अगर (!session->output_report_success) अणु
		ret = -EIO;
		जाओ err;
	पूर्ण

	ret = count;

err:
	clear_bit(HIDP_WAITING_FOR_SEND_ACK, &session->flags);
	mutex_unlock(&session->report_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक hidp_output_report(काष्ठा hid_device *hid, __u8 *data, माप_प्रकार count)
अणु
	काष्ठा hidp_session *session = hid->driver_data;

	वापस hidp_send_पूर्णांकr_message(session,
				      HIDP_TRANS_DATA | HIDP_DATA_RTYPE_OUPUT,
				      data, count);
पूर्ण

अटल पूर्णांक hidp_raw_request(काष्ठा hid_device *hid, अचिन्हित अक्षर reportnum,
			    __u8 *buf, माप_प्रकार len, अचिन्हित अक्षर rtype,
			    पूर्णांक reqtype)
अणु
	चयन (reqtype) अणु
	हाल HID_REQ_GET_REPORT:
		वापस hidp_get_raw_report(hid, reportnum, buf, len, rtype);
	हाल HID_REQ_SET_REPORT:
		वापस hidp_set_raw_report(hid, reportnum, buf, len, rtype);
	शेष:
		वापस -EIO;
	पूर्ण
पूर्ण

अटल व्योम hidp_idle_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा hidp_session *session = from_समयr(session, t, समयr);

	/* The HIDP user-space API only contains calls to add and हटाओ
	 * devices. There is no way to क्रमward events of any kind. Thereक्रमe,
	 * we have to क्रमcefully disconnect a device on idle-समयouts. This is
	 * unक्रमtunate and weird API design, but it is spec-compliant and
	 * required क्रम backwards-compatibility. Hence, on idle-समयout, we
	 * संकेत driver-detach events, so poll() will be woken up with an
	 * error-condition on both sockets.
	 */

	session->पूर्णांकr_sock->sk->sk_err = EUNATCH;
	session->ctrl_sock->sk->sk_err = EUNATCH;
	wake_up_पूर्णांकerruptible(sk_sleep(session->पूर्णांकr_sock->sk));
	wake_up_पूर्णांकerruptible(sk_sleep(session->ctrl_sock->sk));

	hidp_session_terminate(session);
पूर्ण

अटल व्योम hidp_set_समयr(काष्ठा hidp_session *session)
अणु
	अगर (session->idle_to > 0)
		mod_समयr(&session->समयr, jअगरfies + HZ * session->idle_to);
पूर्ण

अटल व्योम hidp_del_समयr(काष्ठा hidp_session *session)
अणु
	अगर (session->idle_to > 0)
		del_समयr(&session->समयr);
पूर्ण

अटल व्योम hidp_process_report(काष्ठा hidp_session *session, पूर्णांक type,
				स्थिर u8 *data, अचिन्हित पूर्णांक len, पूर्णांक पूर्णांकr)
अणु
	अगर (len > HID_MAX_BUFFER_SIZE)
		len = HID_MAX_BUFFER_SIZE;

	स_नकल(session->input_buf, data, len);
	hid_input_report(session->hid, type, session->input_buf, len, पूर्णांकr);
पूर्ण

अटल व्योम hidp_process_handshake(काष्ठा hidp_session *session,
					अचिन्हित अक्षर param)
अणु
	BT_DBG("session %p param 0x%02x", session, param);
	session->output_report_success = 0; /* शेष condition */

	चयन (param) अणु
	हाल HIDP_HSHK_SUCCESSFUL:
		/* FIXME: Call पूर्णांकo SET_ GET_ handlers here */
		session->output_report_success = 1;
		अवरोध;

	हाल HIDP_HSHK_NOT_READY:
	हाल HIDP_HSHK_ERR_INVALID_REPORT_ID:
	हाल HIDP_HSHK_ERR_UNSUPPORTED_REQUEST:
	हाल HIDP_HSHK_ERR_INVALID_PARAMETER:
		अगर (test_and_clear_bit(HIDP_WAITING_FOR_RETURN, &session->flags))
			wake_up_पूर्णांकerruptible(&session->report_queue);

		/* FIXME: Call पूर्णांकo SET_ GET_ handlers here */
		अवरोध;

	हाल HIDP_HSHK_ERR_UNKNOWN:
		अवरोध;

	हाल HIDP_HSHK_ERR_FATAL:
		/* Device requests a reboot, as this is the only way this error
		 * can be recovered. */
		hidp_send_ctrl_message(session,
			HIDP_TRANS_HID_CONTROL | HIDP_CTRL_SOFT_RESET, शून्य, 0);
		अवरोध;

	शेष:
		hidp_send_ctrl_message(session,
			HIDP_TRANS_HANDSHAKE | HIDP_HSHK_ERR_INVALID_PARAMETER, शून्य, 0);
		अवरोध;
	पूर्ण

	/* Wake up the रुकोing thपढ़ो. */
	अगर (test_and_clear_bit(HIDP_WAITING_FOR_SEND_ACK, &session->flags))
		wake_up_पूर्णांकerruptible(&session->report_queue);
पूर्ण

अटल व्योम hidp_process_hid_control(काष्ठा hidp_session *session,
					अचिन्हित अक्षर param)
अणु
	BT_DBG("session %p param 0x%02x", session, param);

	अगर (param == HIDP_CTRL_VIRTUAL_CABLE_UNPLUG) अणु
		/* Flush the transmit queues */
		skb_queue_purge(&session->ctrl_transmit);
		skb_queue_purge(&session->पूर्णांकr_transmit);

		hidp_session_terminate(session);
	पूर्ण
पूर्ण

/* Returns true अगर the passed-in skb should be मुक्तd by the caller. */
अटल पूर्णांक hidp_process_data(काष्ठा hidp_session *session, काष्ठा sk_buff *skb,
				अचिन्हित अक्षर param)
अणु
	पूर्णांक करोne_with_skb = 1;
	BT_DBG("session %p skb %p len %d param 0x%02x", session, skb, skb->len, param);

	चयन (param) अणु
	हाल HIDP_DATA_RTYPE_INPUT:
		hidp_set_समयr(session);

		अगर (session->input)
			hidp_input_report(session, skb);

		अगर (session->hid)
			hidp_process_report(session, HID_INPUT_REPORT,
					    skb->data, skb->len, 0);
		अवरोध;

	हाल HIDP_DATA_RTYPE_OTHER:
	हाल HIDP_DATA_RTYPE_OUPUT:
	हाल HIDP_DATA_RTYPE_FEATURE:
		अवरोध;

	शेष:
		hidp_send_ctrl_message(session,
			HIDP_TRANS_HANDSHAKE | HIDP_HSHK_ERR_INVALID_PARAMETER, शून्य, 0);
	पूर्ण

	अगर (test_bit(HIDP_WAITING_FOR_RETURN, &session->flags) &&
				param == session->रुकोing_report_type) अणु
		अगर (session->रुकोing_report_number < 0 ||
		    session->रुकोing_report_number == skb->data[0]) अणु
			/* hidp_get_raw_report() is रुकोing on this report. */
			session->report_वापस = skb;
			करोne_with_skb = 0;
			clear_bit(HIDP_WAITING_FOR_RETURN, &session->flags);
			wake_up_पूर्णांकerruptible(&session->report_queue);
		पूर्ण
	पूर्ण

	वापस करोne_with_skb;
पूर्ण

अटल व्योम hidp_recv_ctrl_frame(काष्ठा hidp_session *session,
					काष्ठा sk_buff *skb)
अणु
	अचिन्हित अक्षर hdr, type, param;
	पूर्णांक मुक्त_skb = 1;

	BT_DBG("session %p skb %p len %d", session, skb, skb->len);

	hdr = skb->data[0];
	skb_pull(skb, 1);

	type = hdr & HIDP_HEADER_TRANS_MASK;
	param = hdr & HIDP_HEADER_PARAM_MASK;

	चयन (type) अणु
	हाल HIDP_TRANS_HANDSHAKE:
		hidp_process_handshake(session, param);
		अवरोध;

	हाल HIDP_TRANS_HID_CONTROL:
		hidp_process_hid_control(session, param);
		अवरोध;

	हाल HIDP_TRANS_DATA:
		मुक्त_skb = hidp_process_data(session, skb, param);
		अवरोध;

	शेष:
		hidp_send_ctrl_message(session,
			HIDP_TRANS_HANDSHAKE | HIDP_HSHK_ERR_UNSUPPORTED_REQUEST, शून्य, 0);
		अवरोध;
	पूर्ण

	अगर (मुक्त_skb)
		kमुक्त_skb(skb);
पूर्ण

अटल व्योम hidp_recv_पूर्णांकr_frame(काष्ठा hidp_session *session,
				काष्ठा sk_buff *skb)
अणु
	अचिन्हित अक्षर hdr;

	BT_DBG("session %p skb %p len %d", session, skb, skb->len);

	hdr = skb->data[0];
	skb_pull(skb, 1);

	अगर (hdr == (HIDP_TRANS_DATA | HIDP_DATA_RTYPE_INPUT)) अणु
		hidp_set_समयr(session);

		अगर (session->input)
			hidp_input_report(session, skb);

		अगर (session->hid) अणु
			hidp_process_report(session, HID_INPUT_REPORT,
					    skb->data, skb->len, 1);
			BT_DBG("report len %d", skb->len);
		पूर्ण
	पूर्ण अन्यथा अणु
		BT_DBG("Unsupported protocol header 0x%02x", hdr);
	पूर्ण

	kमुक्त_skb(skb);
पूर्ण

अटल पूर्णांक hidp_send_frame(काष्ठा socket *sock, अचिन्हित अक्षर *data, पूर्णांक len)
अणु
	काष्ठा kvec iv = अणु data, len पूर्ण;
	काष्ठा msghdr msg;

	BT_DBG("sock %p data %p len %d", sock, data, len);

	अगर (!len)
		वापस 0;

	स_रखो(&msg, 0, माप(msg));

	वापस kernel_sendmsg(sock, &msg, &iv, 1, len);
पूर्ण

/* dequeue message from @transmit and send via @sock */
अटल व्योम hidp_process_transmit(काष्ठा hidp_session *session,
				  काष्ठा sk_buff_head *transmit,
				  काष्ठा socket *sock)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक ret;

	BT_DBG("session %p", session);

	जबतक ((skb = skb_dequeue(transmit))) अणु
		ret = hidp_send_frame(sock, skb->data, skb->len);
		अगर (ret == -EAGAIN) अणु
			skb_queue_head(transmit, skb);
			अवरोध;
		पूर्ण अन्यथा अगर (ret < 0) अणु
			hidp_session_terminate(session);
			kमुक्त_skb(skb);
			अवरोध;
		पूर्ण

		hidp_set_समयr(session);
		kमुक्त_skb(skb);
	पूर्ण
पूर्ण

अटल पूर्णांक hidp_setup_input(काष्ठा hidp_session *session,
				स्थिर काष्ठा hidp_connadd_req *req)
अणु
	काष्ठा input_dev *input;
	पूर्णांक i;

	input = input_allocate_device();
	अगर (!input)
		वापस -ENOMEM;

	session->input = input;

	input_set_drvdata(input, session);

	input->name = "Bluetooth HID Boot Protocol Device";

	input->id.bustype = BUS_BLUETOOTH;
	input->id.venकरोr  = req->venकरोr;
	input->id.product = req->product;
	input->id.version = req->version;

	अगर (req->subclass & 0x40) अणु
		set_bit(EV_KEY, input->evbit);
		set_bit(EV_LED, input->evbit);
		set_bit(EV_REP, input->evbit);

		set_bit(LED_NUML,    input->ledbit);
		set_bit(LED_CAPSL,   input->ledbit);
		set_bit(LED_SCROLLL, input->ledbit);
		set_bit(LED_COMPOSE, input->ledbit);
		set_bit(LED_KANA,    input->ledbit);

		क्रम (i = 0; i < माप(hidp_keycode); i++)
			set_bit(hidp_keycode[i], input->keybit);
		clear_bit(0, input->keybit);
	पूर्ण

	अगर (req->subclass & 0x80) अणु
		input->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_REL);
		input->keybit[BIT_WORD(BTN_MOUSE)] = BIT_MASK(BTN_LEFT) |
			BIT_MASK(BTN_RIGHT) | BIT_MASK(BTN_MIDDLE);
		input->relbit[0] = BIT_MASK(REL_X) | BIT_MASK(REL_Y);
		input->keybit[BIT_WORD(BTN_MOUSE)] |= BIT_MASK(BTN_SIDE) |
			BIT_MASK(BTN_EXTRA);
		input->relbit[0] |= BIT_MASK(REL_WHEEL);
	पूर्ण

	input->dev.parent = &session->conn->hcon->dev;

	input->event = hidp_input_event;

	वापस 0;
पूर्ण

अटल पूर्णांक hidp_खोलो(काष्ठा hid_device *hid)
अणु
	वापस 0;
पूर्ण

अटल व्योम hidp_बंद(काष्ठा hid_device *hid)
अणु
पूर्ण

अटल पूर्णांक hidp_parse(काष्ठा hid_device *hid)
अणु
	काष्ठा hidp_session *session = hid->driver_data;

	वापस hid_parse_report(session->hid, session->rd_data,
			session->rd_size);
पूर्ण

अटल पूर्णांक hidp_start(काष्ठा hid_device *hid)
अणु
	वापस 0;
पूर्ण

अटल व्योम hidp_stop(काष्ठा hid_device *hid)
अणु
	काष्ठा hidp_session *session = hid->driver_data;

	skb_queue_purge(&session->ctrl_transmit);
	skb_queue_purge(&session->पूर्णांकr_transmit);

	hid->claimed = 0;
पूर्ण

काष्ठा hid_ll_driver hidp_hid_driver = अणु
	.parse = hidp_parse,
	.start = hidp_start,
	.stop = hidp_stop,
	.खोलो  = hidp_खोलो,
	.बंद = hidp_बंद,
	.raw_request = hidp_raw_request,
	.output_report = hidp_output_report,
पूर्ण;
EXPORT_SYMBOL_GPL(hidp_hid_driver);

/* This function sets up the hid device. It करोes not add it
   to the HID प्रणाली. That is करोne in hidp_add_connection(). */
अटल पूर्णांक hidp_setup_hid(काष्ठा hidp_session *session,
				स्थिर काष्ठा hidp_connadd_req *req)
अणु
	काष्ठा hid_device *hid;
	पूर्णांक err;

	session->rd_data = memdup_user(req->rd_data, req->rd_size);
	अगर (IS_ERR(session->rd_data))
		वापस PTR_ERR(session->rd_data);

	session->rd_size = req->rd_size;

	hid = hid_allocate_device();
	अगर (IS_ERR(hid)) अणु
		err = PTR_ERR(hid);
		जाओ fault;
	पूर्ण

	session->hid = hid;

	hid->driver_data = session;

	hid->bus     = BUS_BLUETOOTH;
	hid->venकरोr  = req->venकरोr;
	hid->product = req->product;
	hid->version = req->version;
	hid->country = req->country;

	strscpy(hid->name, req->name, माप(hid->name));

	snम_लिखो(hid->phys, माप(hid->phys), "%pMR",
		 &l2cap_pi(session->ctrl_sock->sk)->chan->src);

	/* NOTE: Some device modules depend on the dst address being stored in
	 * uniq. Please be aware of this beक्रमe making changes to this behavior.
	 */
	snम_लिखो(hid->uniq, माप(hid->uniq), "%pMR",
		 &l2cap_pi(session->ctrl_sock->sk)->chan->dst);

	hid->dev.parent = &session->conn->hcon->dev;
	hid->ll_driver = &hidp_hid_driver;

	/* True अगर device is blacklisted in drivers/hid/hid-quirks.c */
	अगर (hid_ignore(hid)) अणु
		hid_destroy_device(session->hid);
		session->hid = शून्य;
		वापस -ENODEV;
	पूर्ण

	वापस 0;

fault:
	kमुक्त(session->rd_data);
	session->rd_data = शून्य;

	वापस err;
पूर्ण

/* initialize session devices */
अटल पूर्णांक hidp_session_dev_init(काष्ठा hidp_session *session,
				 स्थिर काष्ठा hidp_connadd_req *req)
अणु
	पूर्णांक ret;

	अगर (req->rd_size > 0) अणु
		ret = hidp_setup_hid(session, req);
		अगर (ret && ret != -ENODEV)
			वापस ret;
	पूर्ण

	अगर (!session->hid) अणु
		ret = hidp_setup_input(session, req);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/* destroy session devices */
अटल व्योम hidp_session_dev_destroy(काष्ठा hidp_session *session)
अणु
	अगर (session->hid)
		put_device(&session->hid->dev);
	अन्यथा अगर (session->input)
		input_put_device(session->input);

	kमुक्त(session->rd_data);
	session->rd_data = शून्य;
पूर्ण

/* add HID/input devices to their underlying bus प्रणालीs */
अटल पूर्णांक hidp_session_dev_add(काष्ठा hidp_session *session)
अणु
	पूर्णांक ret;

	/* Both HID and input प्रणालीs drop a ref-count when unरेजिस्टरing the
	 * device but they करोn't take a ref-count when रेजिस्टरing them. Work
	 * around this by explicitly taking a refcount during registration
	 * which is dropped स्वतःmatically by unरेजिस्टरing the devices. */

	अगर (session->hid) अणु
		ret = hid_add_device(session->hid);
		अगर (ret)
			वापस ret;
		get_device(&session->hid->dev);
	पूर्ण अन्यथा अगर (session->input) अणु
		ret = input_रेजिस्टर_device(session->input);
		अगर (ret)
			वापस ret;
		input_get_device(session->input);
	पूर्ण

	वापस 0;
पूर्ण

/* हटाओ HID/input devices from their bus प्रणालीs */
अटल व्योम hidp_session_dev_del(काष्ठा hidp_session *session)
अणु
	अगर (session->hid)
		hid_destroy_device(session->hid);
	अन्यथा अगर (session->input)
		input_unरेजिस्टर_device(session->input);
पूर्ण

/*
 * Asynchronous device registration
 * HID device drivers might want to perक्रमm I/O during initialization to
 * detect device types. Thereक्रमe, call device registration in a separate
 * worker so the HIDP thपढ़ो can schedule I/O operations.
 * Note that this must be called after the worker thपढ़ो was initialized
 * successfully. This will then add the devices and increase session state
 * on success, otherwise it will terminate the session thपढ़ो.
 */
अटल व्योम hidp_session_dev_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hidp_session *session = container_of(work,
						    काष्ठा hidp_session,
						    dev_init);
	पूर्णांक ret;

	ret = hidp_session_dev_add(session);
	अगर (!ret)
		atomic_inc(&session->state);
	अन्यथा
		hidp_session_terminate(session);
पूर्ण

/*
 * Create new session object
 * Allocate session object, initialize अटल fields, copy input data पूर्णांकo the
 * object and take a reference to all sub-objects.
 * This वापसs 0 on success and माला_दो a poपूर्णांकer to the new session object in
 * \out. Otherwise, an error code is वापसed.
 * The new session object has an initial ref-count of 1.
 */
अटल पूर्णांक hidp_session_new(काष्ठा hidp_session **out, स्थिर bdaddr_t *bdaddr,
			    काष्ठा socket *ctrl_sock,
			    काष्ठा socket *पूर्णांकr_sock,
			    स्थिर काष्ठा hidp_connadd_req *req,
			    काष्ठा l2cap_conn *conn)
अणु
	काष्ठा hidp_session *session;
	पूर्णांक ret;
	काष्ठा bt_sock *ctrl, *पूर्णांकr;

	ctrl = bt_sk(ctrl_sock->sk);
	पूर्णांकr = bt_sk(पूर्णांकr_sock->sk);

	session = kzalloc(माप(*session), GFP_KERNEL);
	अगर (!session)
		वापस -ENOMEM;

	/* object and runसमय management */
	kref_init(&session->ref);
	atomic_set(&session->state, HIDP_SESSION_IDLING);
	init_रुकोqueue_head(&session->state_queue);
	session->flags = req->flags & BIT(HIDP_BLUETOOTH_VENDOR_ID);

	/* connection management */
	bacpy(&session->bdaddr, bdaddr);
	session->conn = l2cap_conn_get(conn);
	session->user.probe = hidp_session_probe;
	session->user.हटाओ = hidp_session_हटाओ;
	INIT_LIST_HEAD(&session->user.list);
	session->ctrl_sock = ctrl_sock;
	session->पूर्णांकr_sock = पूर्णांकr_sock;
	skb_queue_head_init(&session->ctrl_transmit);
	skb_queue_head_init(&session->पूर्णांकr_transmit);
	session->ctrl_mtu = min_t(uपूर्णांक, l2cap_pi(ctrl)->chan->omtu,
					l2cap_pi(ctrl)->chan->imtu);
	session->पूर्णांकr_mtu = min_t(uपूर्णांक, l2cap_pi(पूर्णांकr)->chan->omtu,
					l2cap_pi(पूर्णांकr)->chan->imtu);
	session->idle_to = req->idle_to;

	/* device management */
	INIT_WORK(&session->dev_init, hidp_session_dev_work);
	समयr_setup(&session->समयr, hidp_idle_समयout, 0);

	/* session data */
	mutex_init(&session->report_mutex);
	init_रुकोqueue_head(&session->report_queue);

	ret = hidp_session_dev_init(session, req);
	अगर (ret)
		जाओ err_मुक्त;

	get_file(session->पूर्णांकr_sock->file);
	get_file(session->ctrl_sock->file);
	*out = session;
	वापस 0;

err_मुक्त:
	l2cap_conn_put(session->conn);
	kमुक्त(session);
	वापस ret;
पूर्ण

/* increase ref-count of the given session by one */
अटल व्योम hidp_session_get(काष्ठा hidp_session *session)
अणु
	kref_get(&session->ref);
पूर्ण

/* release callback */
अटल व्योम session_मुक्त(काष्ठा kref *ref)
अणु
	काष्ठा hidp_session *session = container_of(ref, काष्ठा hidp_session,
						    ref);

	hidp_session_dev_destroy(session);
	skb_queue_purge(&session->ctrl_transmit);
	skb_queue_purge(&session->पूर्णांकr_transmit);
	fput(session->पूर्णांकr_sock->file);
	fput(session->ctrl_sock->file);
	l2cap_conn_put(session->conn);
	kमुक्त(session);
पूर्ण

/* decrease ref-count of the given session by one */
अटल व्योम hidp_session_put(काष्ठा hidp_session *session)
अणु
	kref_put(&session->ref, session_मुक्त);
पूर्ण

/*
 * Search the list of active sessions क्रम a session with target address
 * \मdaddr. You must hold at least a पढ़ो-lock on \hidp_session_sem. As दीर्घ as
 * you करो not release this lock, the session objects cannot vanish and you can
 * safely take a reference to the session yourself.
 */
अटल काष्ठा hidp_session *__hidp_session_find(स्थिर bdaddr_t *bdaddr)
अणु
	काष्ठा hidp_session *session;

	list_क्रम_each_entry(session, &hidp_session_list, list) अणु
		अगर (!bacmp(bdaddr, &session->bdaddr))
			वापस session;
	पूर्ण

	वापस शून्य;
पूर्ण

/*
 * Same as __hidp_session_find() but no locks must be held. This also takes a
 * reference of the वापसed session (अगर non-शून्य) so you must drop this
 * reference अगर you no दीर्घer use the object.
 */
अटल काष्ठा hidp_session *hidp_session_find(स्थिर bdaddr_t *bdaddr)
अणु
	काष्ठा hidp_session *session;

	करोwn_पढ़ो(&hidp_session_sem);

	session = __hidp_session_find(bdaddr);
	अगर (session)
		hidp_session_get(session);

	up_पढ़ो(&hidp_session_sem);

	वापस session;
पूर्ण

/*
 * Start session synchronously
 * This starts a session thपढ़ो and रुकोs until initialization
 * is करोne or वापसs an error अगर it couldn't be started.
 * If this वापसs 0 the session thपढ़ो is up and running. You must call
 * hipd_session_stop_sync() beक्रमe deleting any runसमय resources.
 */
अटल पूर्णांक hidp_session_start_sync(काष्ठा hidp_session *session)
अणु
	अचिन्हित पूर्णांक venकरोr, product;

	अगर (session->hid) अणु
		venकरोr  = session->hid->venकरोr;
		product = session->hid->product;
	पूर्ण अन्यथा अगर (session->input) अणु
		venकरोr  = session->input->id.venकरोr;
		product = session->input->id.product;
	पूर्ण अन्यथा अणु
		venकरोr = 0x0000;
		product = 0x0000;
	पूर्ण

	session->task = kthपढ़ो_run(hidp_session_thपढ़ो, session,
				    "khidpd_%04x%04x", venकरोr, product);
	अगर (IS_ERR(session->task))
		वापस PTR_ERR(session->task);

	जबतक (atomic_पढ़ो(&session->state) <= HIDP_SESSION_IDLING)
		रुको_event(session->state_queue,
			   atomic_पढ़ो(&session->state) > HIDP_SESSION_IDLING);

	वापस 0;
पूर्ण

/*
 * Terminate session thपढ़ो
 * Wake up session thपढ़ो and notअगरy it to stop. This is asynchronous and
 * वापसs immediately. Call this whenever a runसमय error occurs and you want
 * the session to stop.
 * Note: wake_up_पूर्णांकerruptible() perक्रमms any necessary memory-barriers क्रम us.
 */
अटल व्योम hidp_session_terminate(काष्ठा hidp_session *session)
अणु
	atomic_inc(&session->terminate);
	/*
	 * See the comment preceding the call to रुको_woken()
	 * in hidp_session_run().
	 */
	wake_up_पूर्णांकerruptible(&hidp_session_wq);
पूर्ण

/*
 * Probe HIDP session
 * This is called from the l2cap_conn core when our l2cap_user object is bound
 * to the hci-connection. We get the session via the \user object and can now
 * start the session thपढ़ो, link it पूर्णांकo the global session list and
 * schedule HID/input device registration.
 * The global session-list owns its own reference to the session object so you
 * can drop your own reference after रेजिस्टरing the l2cap_user object.
 */
अटल पूर्णांक hidp_session_probe(काष्ठा l2cap_conn *conn,
			      काष्ठा l2cap_user *user)
अणु
	काष्ठा hidp_session *session = container_of(user,
						    काष्ठा hidp_session,
						    user);
	काष्ठा hidp_session *s;
	पूर्णांक ret;

	करोwn_ग_लिखो(&hidp_session_sem);

	/* check that no other session क्रम this device exists */
	s = __hidp_session_find(&session->bdaddr);
	अगर (s) अणु
		ret = -EEXIST;
		जाओ out_unlock;
	पूर्ण

	अगर (session->input) अणु
		ret = hidp_session_dev_add(session);
		अगर (ret)
			जाओ out_unlock;
	पूर्ण

	ret = hidp_session_start_sync(session);
	अगर (ret)
		जाओ out_del;

	/* HID device registration is async to allow I/O during probe */
	अगर (session->input)
		atomic_inc(&session->state);
	अन्यथा
		schedule_work(&session->dev_init);

	hidp_session_get(session);
	list_add(&session->list, &hidp_session_list);
	ret = 0;
	जाओ out_unlock;

out_del:
	अगर (session->input)
		hidp_session_dev_del(session);
out_unlock:
	up_ग_लिखो(&hidp_session_sem);
	वापस ret;
पूर्ण

/*
 * Remove HIDP session
 * Called from the l2cap_conn core when either we explicitly unरेजिस्टरed
 * the l2cap_user object or अगर the underlying connection is shut करोwn.
 * We संकेत the hidp-session thपढ़ो to shut करोwn, unरेजिस्टर the HID/input
 * devices and unlink the session from the global list.
 * This drops the reference to the session that is owned by the global
 * session-list.
 * Note: We _must_ not synchronosly रुको क्रम the session-thपढ़ो to shut करोwn.
 * This is, because the session-thपढ़ो might be रुकोing क्रम an HCI lock that is
 * held जबतक we are called. Thereक्रमe, we only unरेजिस्टर the devices and
 * notअगरy the session-thपढ़ो to terminate. The thपढ़ो itself owns a reference
 * to the session object so it can safely shut करोwn.
 */
अटल व्योम hidp_session_हटाओ(काष्ठा l2cap_conn *conn,
				काष्ठा l2cap_user *user)
अणु
	काष्ठा hidp_session *session = container_of(user,
						    काष्ठा hidp_session,
						    user);

	करोwn_ग_लिखो(&hidp_session_sem);

	hidp_session_terminate(session);

	cancel_work_sync(&session->dev_init);
	अगर (session->input ||
	    atomic_पढ़ो(&session->state) > HIDP_SESSION_PREPARING)
		hidp_session_dev_del(session);

	list_del(&session->list);

	up_ग_लिखो(&hidp_session_sem);

	hidp_session_put(session);
पूर्ण

/*
 * Session Worker
 * This perक्रमms the actual मुख्य-loop of the HIDP worker. We first check
 * whether the underlying connection is still alive, then parse all pending
 * messages and finally send all outstanding messages.
 */
अटल व्योम hidp_session_run(काष्ठा hidp_session *session)
अणु
	काष्ठा sock *ctrl_sk = session->ctrl_sock->sk;
	काष्ठा sock *पूर्णांकr_sk = session->पूर्णांकr_sock->sk;
	काष्ठा sk_buff *skb;
	DEFINE_WAIT_FUNC(रुको, woken_wake_function);

	add_रुको_queue(&hidp_session_wq, &रुको);
	क्रम (;;) अणु
		/*
		 * This thपढ़ो can be woken up two ways:
		 *  - You call hidp_session_terminate() which sets the
		 *    session->terminate flag and wakes this thपढ़ो up.
		 *  - Via modअगरying the socket state of ctrl/पूर्णांकr_sock. This
		 *    thपढ़ो is woken up by ->sk_state_changed().
		 */

		अगर (atomic_पढ़ो(&session->terminate))
			अवरोध;

		अगर (ctrl_sk->sk_state != BT_CONNECTED ||
		    पूर्णांकr_sk->sk_state != BT_CONNECTED)
			अवरोध;

		/* parse incoming पूर्णांकr-skbs */
		जबतक ((skb = skb_dequeue(&पूर्णांकr_sk->sk_receive_queue))) अणु
			skb_orphan(skb);
			अगर (!skb_linearize(skb))
				hidp_recv_पूर्णांकr_frame(session, skb);
			अन्यथा
				kमुक्त_skb(skb);
		पूर्ण

		/* send pending पूर्णांकr-skbs */
		hidp_process_transmit(session, &session->पूर्णांकr_transmit,
				      session->पूर्णांकr_sock);

		/* parse incoming ctrl-skbs */
		जबतक ((skb = skb_dequeue(&ctrl_sk->sk_receive_queue))) अणु
			skb_orphan(skb);
			अगर (!skb_linearize(skb))
				hidp_recv_ctrl_frame(session, skb);
			अन्यथा
				kमुक्त_skb(skb);
		पूर्ण

		/* send pending ctrl-skbs */
		hidp_process_transmit(session, &session->ctrl_transmit,
				      session->ctrl_sock);

		/*
		 * रुको_woken() perक्रमms the necessary memory barriers
		 * क्रम us; see the header comment क्रम this primitive.
		 */
		रुको_woken(&रुको, TASK_INTERRUPTIBLE, MAX_SCHEDULE_TIMEOUT);
	पूर्ण
	हटाओ_रुको_queue(&hidp_session_wq, &रुको);

	atomic_inc(&session->terminate);
पूर्ण

अटल पूर्णांक hidp_session_wake_function(रुको_queue_entry_t *रुको,
				      अचिन्हित पूर्णांक mode,
				      पूर्णांक sync, व्योम *key)
अणु
	wake_up_पूर्णांकerruptible(&hidp_session_wq);
	वापस false;
पूर्ण

/*
 * HIDP session thपढ़ो
 * This thपढ़ो runs the I/O क्रम a single HIDP session. Startup is synchronous
 * which allows us to take references to ourself here instead of करोing that in
 * the caller.
 * When we are पढ़ोy to run we notअगरy the caller and call hidp_session_run().
 */
अटल पूर्णांक hidp_session_thपढ़ो(व्योम *arg)
अणु
	काष्ठा hidp_session *session = arg;
	DEFINE_WAIT_FUNC(ctrl_रुको, hidp_session_wake_function);
	DEFINE_WAIT_FUNC(पूर्णांकr_रुको, hidp_session_wake_function);

	BT_DBG("session %p", session);

	/* initialize runसमय environment */
	hidp_session_get(session);
	__module_get(THIS_MODULE);
	set_user_nice(current, -15);
	hidp_set_समयr(session);

	add_रुको_queue(sk_sleep(session->ctrl_sock->sk), &ctrl_रुको);
	add_रुको_queue(sk_sleep(session->पूर्णांकr_sock->sk), &पूर्णांकr_रुको);
	/* This memory barrier is paired with wq_has_sleeper(). See
	 * sock_poll_रुको() क्रम more inक्रमmation why this is needed. */
	smp_mb__beक्रमe_atomic();

	/* notअगरy synchronous startup that we're पढ़ोy */
	atomic_inc(&session->state);
	wake_up(&session->state_queue);

	/* run session */
	hidp_session_run(session);

	/* cleanup runसमय environment */
	हटाओ_रुको_queue(sk_sleep(session->पूर्णांकr_sock->sk), &पूर्णांकr_रुको);
	हटाओ_रुको_queue(sk_sleep(session->ctrl_sock->sk), &ctrl_रुको);
	wake_up_पूर्णांकerruptible(&session->report_queue);
	hidp_del_समयr(session);

	/*
	 * If we stopped ourself due to any पूर्णांकernal संकेत, we should try to
	 * unरेजिस्टर our own session here to aव्योम having it linger until the
	 * parent l2cap_conn dies or user-space cleans it up.
	 * This करोes not deadlock as we करोn't करो any synchronous shutकरोwn.
	 * Instead, this call has the same semantics as अगर user-space tried to
	 * delete the session.
	 */
	l2cap_unरेजिस्टर_user(session->conn, &session->user);
	hidp_session_put(session);

	module_put_and_निकास(0);
	वापस 0;
पूर्ण

अटल पूर्णांक hidp_verअगरy_sockets(काष्ठा socket *ctrl_sock,
			       काष्ठा socket *पूर्णांकr_sock)
अणु
	काष्ठा l2cap_chan *ctrl_chan, *पूर्णांकr_chan;
	काष्ठा bt_sock *ctrl, *पूर्णांकr;
	काष्ठा hidp_session *session;

	अगर (!l2cap_is_socket(ctrl_sock) || !l2cap_is_socket(पूर्णांकr_sock))
		वापस -EINVAL;

	ctrl_chan = l2cap_pi(ctrl_sock->sk)->chan;
	पूर्णांकr_chan = l2cap_pi(पूर्णांकr_sock->sk)->chan;

	अगर (bacmp(&ctrl_chan->src, &पूर्णांकr_chan->src) ||
	    bacmp(&ctrl_chan->dst, &पूर्णांकr_chan->dst))
		वापस -ENOTUNIQ;

	ctrl = bt_sk(ctrl_sock->sk);
	पूर्णांकr = bt_sk(पूर्णांकr_sock->sk);

	अगर (ctrl->sk.sk_state != BT_CONNECTED ||
	    पूर्णांकr->sk.sk_state != BT_CONNECTED)
		वापस -EBADFD;

	/* early session check, we check again during session registration */
	session = hidp_session_find(&ctrl_chan->dst);
	अगर (session) अणु
		hidp_session_put(session);
		वापस -EEXIST;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक hidp_connection_add(स्थिर काष्ठा hidp_connadd_req *req,
			काष्ठा socket *ctrl_sock,
			काष्ठा socket *पूर्णांकr_sock)
अणु
	u32 valid_flags = BIT(HIDP_VIRTUAL_CABLE_UNPLUG) |
			  BIT(HIDP_BOOT_PROTOCOL_MODE);
	काष्ठा hidp_session *session;
	काष्ठा l2cap_conn *conn;
	काष्ठा l2cap_chan *chan;
	पूर्णांक ret;

	ret = hidp_verअगरy_sockets(ctrl_sock, पूर्णांकr_sock);
	अगर (ret)
		वापस ret;

	अगर (req->flags & ~valid_flags)
		वापस -EINVAL;

	chan = l2cap_pi(ctrl_sock->sk)->chan;
	conn = शून्य;
	l2cap_chan_lock(chan);
	अगर (chan->conn)
		conn = l2cap_conn_get(chan->conn);
	l2cap_chan_unlock(chan);

	अगर (!conn)
		वापस -EBADFD;

	ret = hidp_session_new(&session, &chan->dst, ctrl_sock,
			       पूर्णांकr_sock, req, conn);
	अगर (ret)
		जाओ out_conn;

	ret = l2cap_रेजिस्टर_user(conn, &session->user);
	अगर (ret)
		जाओ out_session;

	ret = 0;

out_session:
	hidp_session_put(session);
out_conn:
	l2cap_conn_put(conn);
	वापस ret;
पूर्ण

पूर्णांक hidp_connection_del(काष्ठा hidp_conndel_req *req)
अणु
	u32 valid_flags = BIT(HIDP_VIRTUAL_CABLE_UNPLUG);
	काष्ठा hidp_session *session;

	अगर (req->flags & ~valid_flags)
		वापस -EINVAL;

	session = hidp_session_find(&req->bdaddr);
	अगर (!session)
		वापस -ENOENT;

	अगर (req->flags & BIT(HIDP_VIRTUAL_CABLE_UNPLUG))
		hidp_send_ctrl_message(session,
				       HIDP_TRANS_HID_CONTROL |
				         HIDP_CTRL_VIRTUAL_CABLE_UNPLUG,
				       शून्य, 0);
	अन्यथा
		l2cap_unरेजिस्टर_user(session->conn, &session->user);

	hidp_session_put(session);

	वापस 0;
पूर्ण

पूर्णांक hidp_get_connlist(काष्ठा hidp_connlist_req *req)
अणु
	काष्ठा hidp_session *session;
	पूर्णांक err = 0, n = 0;

	BT_DBG("");

	करोwn_पढ़ो(&hidp_session_sem);

	list_क्रम_each_entry(session, &hidp_session_list, list) अणु
		काष्ठा hidp_conninfo ci;

		hidp_copy_session(session, &ci);

		अगर (copy_to_user(req->ci, &ci, माप(ci))) अणु
			err = -EFAULT;
			अवरोध;
		पूर्ण

		अगर (++n >= req->cnum)
			अवरोध;

		req->ci++;
	पूर्ण
	req->cnum = n;

	up_पढ़ो(&hidp_session_sem);
	वापस err;
पूर्ण

पूर्णांक hidp_get_conninfo(काष्ठा hidp_conninfo *ci)
अणु
	काष्ठा hidp_session *session;

	session = hidp_session_find(&ci->bdaddr);
	अगर (session) अणु
		hidp_copy_session(session, ci);
		hidp_session_put(session);
	पूर्ण

	वापस session ? 0 : -ENOENT;
पूर्ण

अटल पूर्णांक __init hidp_init(व्योम)
अणु
	BT_INFO("HIDP (Human Interface Emulation) ver %s", VERSION);

	वापस hidp_init_sockets();
पूर्ण

अटल व्योम __निकास hidp_निकास(व्योम)
अणु
	hidp_cleanup_sockets();
पूर्ण

module_init(hidp_init);
module_निकास(hidp_निकास);

MODULE_AUTHOR("Marcel Holtmann <marcel@holtmann.org>");
MODULE_AUTHOR("David Herrmann <dh.herrmann@gmail.com>");
MODULE_DESCRIPTION("Bluetooth HIDP ver " VERSION);
MODULE_VERSION(VERSION);
MODULE_LICENSE("GPL");
MODULE_ALIAS("bt-proto-6");
