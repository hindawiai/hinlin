<शैली गुरु>
/*
   CMTP implementation क्रम Linux Bluetooth stack (BlueZ).
   Copyright (C) 2002-2003 Marcel Holपंचांगann <marcel@holपंचांगann.org>

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

#समावेश <linux/export.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/slab.h>
#समावेश <linux/poll.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/socket.h>
#समावेश <linux/ioctl.h>
#समावेश <linux/file.h>
#समावेश <linux/रुको.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <net/sock.h>

#समावेश <linux/isdn/capilli.h>
#समावेश <linux/isdn/capicmd.h>
#समावेश <linux/isdn/capiutil.h>

#समावेश "cmtp.h"

#घोषणा CAPI_INTEROPERABILITY		0x20

#घोषणा CAPI_INTEROPERABILITY_REQ	CAPICMD(CAPI_INTEROPERABILITY, CAPI_REQ)
#घोषणा CAPI_INTEROPERABILITY_CONF	CAPICMD(CAPI_INTEROPERABILITY, CAPI_CONF)
#घोषणा CAPI_INTEROPERABILITY_IND	CAPICMD(CAPI_INTEROPERABILITY, CAPI_IND)
#घोषणा CAPI_INTEROPERABILITY_RESP	CAPICMD(CAPI_INTEROPERABILITY, CAPI_RESP)

#घोषणा CAPI_INTEROPERABILITY_REQ_LEN	(CAPI_MSG_BASELEN + 2)
#घोषणा CAPI_INTEROPERABILITY_CONF_LEN	(CAPI_MSG_BASELEN + 4)
#घोषणा CAPI_INTEROPERABILITY_IND_LEN	(CAPI_MSG_BASELEN + 2)
#घोषणा CAPI_INTEROPERABILITY_RESP_LEN	(CAPI_MSG_BASELEN + 2)

#घोषणा CAPI_FUNCTION_REGISTER		0
#घोषणा CAPI_FUNCTION_RELEASE		1
#घोषणा CAPI_FUNCTION_GET_PROखाता	2
#घोषणा CAPI_FUNCTION_GET_MANUFACTURER	3
#घोषणा CAPI_FUNCTION_GET_VERSION	4
#घोषणा CAPI_FUNCTION_GET_SERIAL_NUMBER	5
#घोषणा CAPI_FUNCTION_MANUFACTURER	6
#घोषणा CAPI_FUNCTION_LOOPBACK		7


#घोषणा CMTP_MSGNUM	1
#घोषणा CMTP_APPLID	2
#घोषणा CMTP_MAPPING	3

अटल काष्ठा cmtp_application *cmtp_application_add(काष्ठा cmtp_session *session, __u16 appl)
अणु
	काष्ठा cmtp_application *app = kzalloc(माप(*app), GFP_KERNEL);

	BT_DBG("session %p application %p appl %d", session, app, appl);

	अगर (!app)
		वापस शून्य;

	app->state = BT_OPEN;
	app->appl = appl;

	list_add_tail(&app->list, &session->applications);

	वापस app;
पूर्ण

अटल व्योम cmtp_application_del(काष्ठा cmtp_session *session, काष्ठा cmtp_application *app)
अणु
	BT_DBG("session %p application %p", session, app);

	अगर (app) अणु
		list_del(&app->list);
		kमुक्त(app);
	पूर्ण
पूर्ण

अटल काष्ठा cmtp_application *cmtp_application_get(काष्ठा cmtp_session *session, पूर्णांक pattern, __u16 value)
अणु
	काष्ठा cmtp_application *app;

	list_क्रम_each_entry(app, &session->applications, list) अणु
		चयन (pattern) अणु
		हाल CMTP_MSGNUM:
			अगर (app->msgnum == value)
				वापस app;
			अवरोध;
		हाल CMTP_APPLID:
			अगर (app->appl == value)
				वापस app;
			अवरोध;
		हाल CMTP_MAPPING:
			अगर (app->mapping == value)
				वापस app;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक cmtp_msgnum_get(काष्ठा cmtp_session *session)
अणु
	session->msgnum++;

	अगर ((session->msgnum & 0xff) > 200)
		session->msgnum = CMTP_INITIAL_MSGNUM + 1;

	वापस session->msgnum;
पूर्ण

अटल व्योम cmtp_send_capimsg(काष्ठा cmtp_session *session, काष्ठा sk_buff *skb)
अणु
	काष्ठा cmtp_scb *scb = (व्योम *) skb->cb;

	BT_DBG("session %p skb %p len %d", session, skb, skb->len);

	scb->id = -1;
	scb->data = (CAPIMSG_COMMAND(skb->data) == CAPI_DATA_B3);

	skb_queue_tail(&session->transmit, skb);

	wake_up_पूर्णांकerruptible(sk_sleep(session->sock->sk));
पूर्ण

अटल व्योम cmtp_send_पूर्णांकeropmsg(काष्ठा cmtp_session *session,
					__u8 subcmd, __u16 appl, __u16 msgnum,
					__u16 function, अचिन्हित अक्षर *buf, पूर्णांक len)
अणु
	काष्ठा sk_buff *skb;
	अचिन्हित अक्षर *s;

	BT_DBG("session %p subcmd 0x%02x appl %d msgnum %d", session, subcmd, appl, msgnum);

	skb = alloc_skb(CAPI_MSG_BASELEN + 6 + len, GFP_ATOMIC);
	अगर (!skb) अणु
		BT_ERR("Can't allocate memory for interoperability packet");
		वापस;
	पूर्ण

	s = skb_put(skb, CAPI_MSG_BASELEN + 6 + len);

	capimsg_setu16(s, 0, CAPI_MSG_BASELEN + 6 + len);
	capimsg_setu16(s, 2, appl);
	capimsg_setu8 (s, 4, CAPI_INTEROPERABILITY);
	capimsg_setu8 (s, 5, subcmd);
	capimsg_setu16(s, 6, msgnum);

	/* Interoperability selector (Bluetooth Device Management) */
	capimsg_setu16(s, 8, 0x0001);

	capimsg_setu8 (s, 10, 3 + len);
	capimsg_setu16(s, 11, function);
	capimsg_setu8 (s, 13, len);

	अगर (len > 0)
		स_नकल(s + 14, buf, len);

	cmtp_send_capimsg(session, skb);
पूर्ण

अटल व्योम cmtp_recv_पूर्णांकeropmsg(काष्ठा cmtp_session *session, काष्ठा sk_buff *skb)
अणु
	काष्ठा capi_ctr *ctrl = &session->ctrl;
	काष्ठा cmtp_application *application;
	__u16 appl, msgnum, func, info;
	__u32 controller;

	BT_DBG("session %p skb %p len %d", session, skb, skb->len);

	चयन (CAPIMSG_SUBCOMMAND(skb->data)) अणु
	हाल CAPI_CONF:
		अगर (skb->len < CAPI_MSG_BASELEN + 10)
			अवरोध;

		func = CAPIMSG_U16(skb->data, CAPI_MSG_BASELEN + 5);
		info = CAPIMSG_U16(skb->data, CAPI_MSG_BASELEN + 8);

		चयन (func) अणु
		हाल CAPI_FUNCTION_REGISTER:
			msgnum = CAPIMSG_MSGID(skb->data);

			application = cmtp_application_get(session, CMTP_MSGNUM, msgnum);
			अगर (application) अणु
				application->state = BT_CONNECTED;
				application->msgnum = 0;
				application->mapping = CAPIMSG_APPID(skb->data);
				wake_up_पूर्णांकerruptible(&session->रुको);
			पूर्ण

			अवरोध;

		हाल CAPI_FUNCTION_RELEASE:
			appl = CAPIMSG_APPID(skb->data);

			application = cmtp_application_get(session, CMTP_MAPPING, appl);
			अगर (application) अणु
				application->state = BT_CLOSED;
				application->msgnum = 0;
				wake_up_पूर्णांकerruptible(&session->रुको);
			पूर्ण

			अवरोध;

		हाल CAPI_FUNCTION_GET_PROखाता:
			अगर (skb->len < CAPI_MSG_BASELEN + 11 + माप(capi_profile))
				अवरोध;

			controller = CAPIMSG_U16(skb->data, CAPI_MSG_BASELEN + 11);
			msgnum = CAPIMSG_MSGID(skb->data);

			अगर (!info && (msgnum == CMTP_INITIAL_MSGNUM)) अणु
				session->ncontroller = controller;
				wake_up_पूर्णांकerruptible(&session->रुको);
				अवरोध;
			पूर्ण

			अगर (!info && ctrl) अणु
				स_नकल(&ctrl->profile,
					skb->data + CAPI_MSG_BASELEN + 11,
					माप(capi_profile));
				session->state = BT_CONNECTED;
				capi_ctr_पढ़ोy(ctrl);
			पूर्ण

			अवरोध;

		हाल CAPI_FUNCTION_GET_MANUFACTURER:
			अगर (skb->len < CAPI_MSG_BASELEN + 15)
				अवरोध;

			अगर (!info && ctrl) अणु
				पूर्णांक len = min_t(uपूर्णांक, CAPI_MANUFACTURER_LEN,
						skb->data[CAPI_MSG_BASELEN + 14]);

				स_रखो(ctrl->manu, 0, CAPI_MANUFACTURER_LEN);
				म_नकलन(ctrl->manu,
					skb->data + CAPI_MSG_BASELEN + 15, len);
			पूर्ण

			अवरोध;

		हाल CAPI_FUNCTION_GET_VERSION:
			अगर (skb->len < CAPI_MSG_BASELEN + 32)
				अवरोध;

			अगर (!info && ctrl) अणु
				ctrl->version.majorversion = CAPIMSG_U32(skb->data, CAPI_MSG_BASELEN + 16);
				ctrl->version.minorversion = CAPIMSG_U32(skb->data, CAPI_MSG_BASELEN + 20);
				ctrl->version.majormanuversion = CAPIMSG_U32(skb->data, CAPI_MSG_BASELEN + 24);
				ctrl->version.minormanuversion = CAPIMSG_U32(skb->data, CAPI_MSG_BASELEN + 28);
			पूर्ण

			अवरोध;

		हाल CAPI_FUNCTION_GET_SERIAL_NUMBER:
			अगर (skb->len < CAPI_MSG_BASELEN + 17)
				अवरोध;

			अगर (!info && ctrl) अणु
				पूर्णांक len = min_t(uपूर्णांक, CAPI_SERIAL_LEN,
						skb->data[CAPI_MSG_BASELEN + 16]);

				स_रखो(ctrl->serial, 0, CAPI_SERIAL_LEN);
				म_नकलन(ctrl->serial,
					skb->data + CAPI_MSG_BASELEN + 17, len);
			पूर्ण

			अवरोध;
		पूर्ण

		अवरोध;

	हाल CAPI_IND:
		अगर (skb->len < CAPI_MSG_BASELEN + 6)
			अवरोध;

		func = CAPIMSG_U16(skb->data, CAPI_MSG_BASELEN + 3);

		अगर (func == CAPI_FUNCTION_LOOPBACK) अणु
			पूर्णांक len = min_t(uपूर्णांक, skb->len - CAPI_MSG_BASELEN - 6,
						skb->data[CAPI_MSG_BASELEN + 5]);
			appl = CAPIMSG_APPID(skb->data);
			msgnum = CAPIMSG_MSGID(skb->data);
			cmtp_send_पूर्णांकeropmsg(session, CAPI_RESP, appl, msgnum, func,
						skb->data + CAPI_MSG_BASELEN + 6, len);
		पूर्ण

		अवरोध;
	पूर्ण

	kमुक्त_skb(skb);
पूर्ण

व्योम cmtp_recv_capimsg(काष्ठा cmtp_session *session, काष्ठा sk_buff *skb)
अणु
	काष्ठा capi_ctr *ctrl = &session->ctrl;
	काष्ठा cmtp_application *application;
	__u16 appl;
	__u32 contr;

	BT_DBG("session %p skb %p len %d", session, skb, skb->len);

	अगर (skb->len < CAPI_MSG_BASELEN)
		वापस;

	अगर (CAPIMSG_COMMAND(skb->data) == CAPI_INTEROPERABILITY) अणु
		cmtp_recv_पूर्णांकeropmsg(session, skb);
		वापस;
	पूर्ण

	अगर (session->flags & BIT(CMTP_LOOPBACK)) अणु
		kमुक्त_skb(skb);
		वापस;
	पूर्ण

	appl = CAPIMSG_APPID(skb->data);
	contr = CAPIMSG_CONTROL(skb->data);

	application = cmtp_application_get(session, CMTP_MAPPING, appl);
	अगर (application) अणु
		appl = application->appl;
		CAPIMSG_SETAPPID(skb->data, appl);
	पूर्ण अन्यथा अणु
		BT_ERR("Can't find application with id %d", appl);
		kमुक्त_skb(skb);
		वापस;
	पूर्ण

	अगर ((contr & 0x7f) == 0x01) अणु
		contr = (contr & 0xffffff80) | session->num;
		CAPIMSG_SETCONTROL(skb->data, contr);
	पूर्ण

	capi_ctr_handle_message(ctrl, appl, skb);
पूर्ण

अटल पूर्णांक cmtp_load_firmware(काष्ठा capi_ctr *ctrl, capiloaddata *data)
अणु
	BT_DBG("ctrl %p data %p", ctrl, data);

	वापस 0;
पूर्ण

अटल व्योम cmtp_reset_ctr(काष्ठा capi_ctr *ctrl)
अणु
	काष्ठा cmtp_session *session = ctrl->driverdata;

	BT_DBG("ctrl %p", ctrl);

	capi_ctr_करोwn(ctrl);

	atomic_inc(&session->terminate);
	wake_up_process(session->task);
पूर्ण

अटल व्योम cmtp_रेजिस्टर_appl(काष्ठा capi_ctr *ctrl, __u16 appl, capi_रेजिस्टर_params *rp)
अणु
	DECLARE_WAITQUEUE(रुको, current);
	काष्ठा cmtp_session *session = ctrl->driverdata;
	काष्ठा cmtp_application *application;
	अचिन्हित दीर्घ समयo = CMTP_INTEROP_TIMEOUT;
	अचिन्हित अक्षर buf[8];
	पूर्णांक err = 0, nconn, want = rp->level3cnt;

	BT_DBG("ctrl %p appl %d level3cnt %d datablkcnt %d datablklen %d",
		ctrl, appl, rp->level3cnt, rp->datablkcnt, rp->datablklen);

	application = cmtp_application_add(session, appl);
	अगर (!application) अणु
		BT_ERR("Can't allocate memory for new application");
		वापस;
	पूर्ण

	अगर (want < 0)
		nconn = ctrl->profile.nbchannel * -want;
	अन्यथा
		nconn = want;

	अगर (nconn == 0)
		nconn = ctrl->profile.nbchannel;

	capimsg_setu16(buf, 0, nconn);
	capimsg_setu16(buf, 2, rp->datablkcnt);
	capimsg_setu16(buf, 4, rp->datablklen);

	application->state = BT_CONFIG;
	application->msgnum = cmtp_msgnum_get(session);

	cmtp_send_पूर्णांकeropmsg(session, CAPI_REQ, 0x0000, application->msgnum,
				CAPI_FUNCTION_REGISTER, buf, 6);

	add_रुको_queue(&session->रुको, &रुको);
	जबतक (1) अणु
		set_current_state(TASK_INTERRUPTIBLE);

		अगर (!समयo) अणु
			err = -EAGAIN;
			अवरोध;
		पूर्ण

		अगर (application->state == BT_CLOSED) अणु
			err = -application->err;
			अवरोध;
		पूर्ण

		अगर (application->state == BT_CONNECTED)
			अवरोध;

		अगर (संकेत_pending(current)) अणु
			err = -EINTR;
			अवरोध;
		पूर्ण

		समयo = schedule_समयout(समयo);
	पूर्ण
	set_current_state(TASK_RUNNING);
	हटाओ_रुको_queue(&session->रुको, &रुको);

	अगर (err) अणु
		cmtp_application_del(session, application);
		वापस;
	पूर्ण
पूर्ण

अटल व्योम cmtp_release_appl(काष्ठा capi_ctr *ctrl, __u16 appl)
अणु
	काष्ठा cmtp_session *session = ctrl->driverdata;
	काष्ठा cmtp_application *application;

	BT_DBG("ctrl %p appl %d", ctrl, appl);

	application = cmtp_application_get(session, CMTP_APPLID, appl);
	अगर (!application) अणु
		BT_ERR("Can't find application");
		वापस;
	पूर्ण

	application->msgnum = cmtp_msgnum_get(session);

	cmtp_send_पूर्णांकeropmsg(session, CAPI_REQ, application->mapping, application->msgnum,
				CAPI_FUNCTION_RELEASE, शून्य, 0);

	रुको_event_पूर्णांकerruptible_समयout(session->रुको,
			(application->state == BT_CLOSED), CMTP_INTEROP_TIMEOUT);

	cmtp_application_del(session, application);
पूर्ण

अटल u16 cmtp_send_message(काष्ठा capi_ctr *ctrl, काष्ठा sk_buff *skb)
अणु
	काष्ठा cmtp_session *session = ctrl->driverdata;
	काष्ठा cmtp_application *application;
	__u16 appl;
	__u32 contr;

	BT_DBG("ctrl %p skb %p", ctrl, skb);

	appl = CAPIMSG_APPID(skb->data);
	contr = CAPIMSG_CONTROL(skb->data);

	application = cmtp_application_get(session, CMTP_APPLID, appl);
	अगर ((!application) || (application->state != BT_CONNECTED)) अणु
		BT_ERR("Can't find application with id %d", appl);
		वापस CAPI_ILLAPPNR;
	पूर्ण

	CAPIMSG_SETAPPID(skb->data, application->mapping);

	अगर ((contr & 0x7f) == session->num) अणु
		contr = (contr & 0xffffff80) | 0x01;
		CAPIMSG_SETCONTROL(skb->data, contr);
	पूर्ण

	cmtp_send_capimsg(session, skb);

	वापस CAPI_NOERROR;
पूर्ण

अटल अक्षर *cmtp_procinfo(काष्ठा capi_ctr *ctrl)
अणु
	वापस "CAPI Message Transport Protocol";
पूर्ण

अटल पूर्णांक cmtp_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा capi_ctr *ctrl = m->निजी;
	काष्ठा cmtp_session *session = ctrl->driverdata;
	काष्ठा cmtp_application *app;

	seq_म_लिखो(m, "%s\n\n", cmtp_procinfo(ctrl));
	seq_म_लिखो(m, "addr %s\n", session->name);
	seq_म_लिखो(m, "ctrl %d\n", session->num);

	list_क्रम_each_entry(app, &session->applications, list) अणु
		seq_म_लिखो(m, "appl %d -> %d\n", app->appl, app->mapping);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक cmtp_attach_device(काष्ठा cmtp_session *session)
अणु
	अचिन्हित अक्षर buf[4];
	दीर्घ ret;

	BT_DBG("session %p", session);

	capimsg_setu32(buf, 0, 0);

	cmtp_send_पूर्णांकeropmsg(session, CAPI_REQ, 0xffff, CMTP_INITIAL_MSGNUM,
				CAPI_FUNCTION_GET_PROखाता, buf, 4);

	ret = रुको_event_पूर्णांकerruptible_समयout(session->रुको,
			session->ncontroller, CMTP_INTEROP_TIMEOUT);

	BT_INFO("Found %d CAPI controller(s) on device %s", session->ncontroller, session->name);

	अगर (!ret)
		वापस -ETIMEDOUT;

	अगर (!session->ncontroller)
		वापस -ENODEV;

	अगर (session->ncontroller > 1)
		BT_INFO("Setting up only CAPI controller 1");

	session->ctrl.owner      = THIS_MODULE;
	session->ctrl.driverdata = session;
	म_नकल(session->ctrl.name, session->name);

	session->ctrl.driver_name   = "cmtp";
	session->ctrl.load_firmware = cmtp_load_firmware;
	session->ctrl.reset_ctr     = cmtp_reset_ctr;
	session->ctrl.रेजिस्टर_appl = cmtp_रेजिस्टर_appl;
	session->ctrl.release_appl  = cmtp_release_appl;
	session->ctrl.send_message  = cmtp_send_message;

	session->ctrl.procinfo      = cmtp_procinfo;
	session->ctrl.proc_show     = cmtp_proc_show;

	अगर (attach_capi_ctr(&session->ctrl) < 0) अणु
		BT_ERR("Can't attach new controller");
		वापस -EBUSY;
	पूर्ण

	session->num = session->ctrl.cnr;

	BT_DBG("session %p num %d", session, session->num);

	capimsg_setu32(buf, 0, 1);

	cmtp_send_पूर्णांकeropmsg(session, CAPI_REQ, 0xffff, cmtp_msgnum_get(session),
				CAPI_FUNCTION_GET_MANUFACTURER, buf, 4);

	cmtp_send_पूर्णांकeropmsg(session, CAPI_REQ, 0xffff, cmtp_msgnum_get(session),
				CAPI_FUNCTION_GET_VERSION, buf, 4);

	cmtp_send_पूर्णांकeropmsg(session, CAPI_REQ, 0xffff, cmtp_msgnum_get(session),
				CAPI_FUNCTION_GET_SERIAL_NUMBER, buf, 4);

	cmtp_send_पूर्णांकeropmsg(session, CAPI_REQ, 0xffff, cmtp_msgnum_get(session),
				CAPI_FUNCTION_GET_PROखाता, buf, 4);

	वापस 0;
पूर्ण

व्योम cmtp_detach_device(काष्ठा cmtp_session *session)
अणु
	BT_DBG("session %p", session);

	detach_capi_ctr(&session->ctrl);
पूर्ण
