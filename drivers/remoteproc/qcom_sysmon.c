<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2017, Linaro Ltd.
 */
#समावेश <linux/firmware.h>
#समावेश <linux/module.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/remoteproc/qcom_rproc.h>
#समावेश <linux/rpmsg.h>

#समावेश "qcom_common.h"

अटल BLOCKING_NOTIFIER_HEAD(sysmon_notअगरiers);

काष्ठा qcom_sysmon अणु
	काष्ठा rproc_subdev subdev;
	काष्ठा rproc *rproc;

	पूर्णांक state;
	काष्ठा mutex state_lock;

	काष्ठा list_head node;

	स्थिर अक्षर *name;

	पूर्णांक shutकरोwn_irq;
	पूर्णांक ssctl_version;
	पूर्णांक ssctl_instance;

	काष्ठा notअगरier_block nb;

	काष्ठा device *dev;

	काष्ठा rpmsg_endpoपूर्णांक *ept;
	काष्ठा completion comp;
	काष्ठा completion ind_comp;
	काष्ठा completion shutकरोwn_comp;
	काष्ठा mutex lock;

	bool ssr_ack;
	bool shutकरोwn_acked;

	काष्ठा qmi_handle qmi;
	काष्ठा sockaddr_qrtr ssctl;
पूर्ण;

क्रमागत अणु
	SSCTL_SSR_EVENT_BEFORE_POWERUP,
	SSCTL_SSR_EVENT_AFTER_POWERUP,
	SSCTL_SSR_EVENT_BEFORE_SHUTDOWN,
	SSCTL_SSR_EVENT_AFTER_SHUTDOWN,
पूर्ण;

अटल स्थिर अक्षर * स्थिर sysmon_state_string[] = अणु
	[SSCTL_SSR_EVENT_BEFORE_POWERUP]	= "before_powerup",
	[SSCTL_SSR_EVENT_AFTER_POWERUP]		= "after_powerup",
	[SSCTL_SSR_EVENT_BEFORE_SHUTDOWN]	= "before_shutdown",
	[SSCTL_SSR_EVENT_AFTER_SHUTDOWN]	= "after_shutdown",
पूर्ण;

काष्ठा sysmon_event अणु
	स्थिर अक्षर *subsys_name;
	u32 ssr_event;
पूर्ण;

अटल DEFINE_MUTEX(sysmon_lock);
अटल LIST_HEAD(sysmon_list);

/**
 * sysmon_send_event() - send notअगरication of other remote's SSR event
 * @sysmon:	sysmon context
 * @event:	sysmon event context
 */
अटल व्योम sysmon_send_event(काष्ठा qcom_sysmon *sysmon,
			      स्थिर काष्ठा sysmon_event *event)
अणु
	अक्षर req[50];
	पूर्णांक len;
	पूर्णांक ret;

	len = snम_लिखो(req, माप(req), "ssr:%s:%s", event->subsys_name,
		       sysmon_state_string[event->ssr_event]);
	अगर (len >= माप(req))
		वापस;

	mutex_lock(&sysmon->lock);
	reinit_completion(&sysmon->comp);
	sysmon->ssr_ack = false;

	ret = rpmsg_send(sysmon->ept, req, len);
	अगर (ret < 0) अणु
		dev_err(sysmon->dev, "failed to send sysmon event\n");
		जाओ out_unlock;
	पूर्ण

	ret = रुको_क्रम_completion_समयout(&sysmon->comp,
					  msecs_to_jअगरfies(5000));
	अगर (!ret) अणु
		dev_err(sysmon->dev, "timeout waiting for sysmon ack\n");
		जाओ out_unlock;
	पूर्ण

	अगर (!sysmon->ssr_ack)
		dev_err(sysmon->dev, "unexpected response to sysmon event\n");

out_unlock:
	mutex_unlock(&sysmon->lock);
पूर्ण

/**
 * sysmon_request_shutकरोwn() - request graceful shutकरोwn of remote
 * @sysmon:	sysmon context
 *
 * Return: boolean indicator of the remote processor acking the request
 */
अटल bool sysmon_request_shutकरोwn(काष्ठा qcom_sysmon *sysmon)
अणु
	अक्षर *req = "ssr:shutdown";
	bool acked = false;
	पूर्णांक ret;

	mutex_lock(&sysmon->lock);
	reinit_completion(&sysmon->comp);
	sysmon->ssr_ack = false;

	ret = rpmsg_send(sysmon->ept, req, म_माप(req) + 1);
	अगर (ret < 0) अणु
		dev_err(sysmon->dev, "send sysmon shutdown request failed\n");
		जाओ out_unlock;
	पूर्ण

	ret = रुको_क्रम_completion_समयout(&sysmon->comp,
					  msecs_to_jअगरfies(5000));
	अगर (!ret) अणु
		dev_err(sysmon->dev, "timeout waiting for sysmon ack\n");
		जाओ out_unlock;
	पूर्ण

	अगर (!sysmon->ssr_ack)
		dev_err(sysmon->dev,
			"unexpected response to sysmon shutdown request\n");
	अन्यथा
		acked = true;

out_unlock:
	mutex_unlock(&sysmon->lock);

	वापस acked;
पूर्ण

अटल पूर्णांक sysmon_callback(काष्ठा rpmsg_device *rpdev, व्योम *data, पूर्णांक count,
			   व्योम *priv, u32 addr)
अणु
	काष्ठा qcom_sysmon *sysmon = priv;
	स्थिर अक्षर *ssr_ack = "ssr:ack";
	स्थिर पूर्णांक ssr_ack_len = म_माप(ssr_ack) + 1;

	अगर (!sysmon)
		वापस -EINVAL;

	अगर (count >= ssr_ack_len && !स_भेद(data, ssr_ack, ssr_ack_len))
		sysmon->ssr_ack = true;

	complete(&sysmon->comp);

	वापस 0;
पूर्ण

#घोषणा SSCTL_SHUTDOWN_REQ		0x21
#घोषणा SSCTL_SHUTDOWN_READY_IND	0x21
#घोषणा SSCTL_SUBSYS_EVENT_REQ		0x23

#घोषणा SSCTL_MAX_MSG_LEN		7

#घोषणा SSCTL_SUBSYS_NAME_LENGTH	15

क्रमागत अणु
	SSCTL_SSR_EVENT_FORCED,
	SSCTL_SSR_EVENT_GRACEFUL,
पूर्ण;

काष्ठा ssctl_shutकरोwn_resp अणु
	काष्ठा qmi_response_type_v01 resp;
पूर्ण;

अटल काष्ठा qmi_elem_info ssctl_shutकरोwn_resp_ei[] = अणु
	अणु
		.data_type	= QMI_STRUCT,
		.elem_len	= 1,
		.elem_size	= माप(काष्ठा qmi_response_type_v01),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x02,
		.offset		= दुरत्व(काष्ठा ssctl_shutकरोwn_resp, resp),
		.ei_array	= qmi_response_type_v01_ei,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

काष्ठा ssctl_subsys_event_req अणु
	u8 subsys_name_len;
	अक्षर subsys_name[SSCTL_SUBSYS_NAME_LENGTH];
	u32 event;
	u8 evt_driven_valid;
	u32 evt_driven;
पूर्ण;

अटल काष्ठा qmi_elem_info ssctl_subsys_event_req_ei[] = अणु
	अणु
		.data_type	= QMI_DATA_LEN,
		.elem_len	= 1,
		.elem_size	= माप(uपूर्णांक8_t),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x01,
		.offset		= दुरत्व(काष्ठा ssctl_subsys_event_req,
					   subsys_name_len),
		.ei_array	= शून्य,
	पूर्ण,
	अणु
		.data_type	= QMI_UNSIGNED_1_BYTE,
		.elem_len	= SSCTL_SUBSYS_NAME_LENGTH,
		.elem_size	= माप(अक्षर),
		.array_type	= VAR_LEN_ARRAY,
		.tlv_type	= 0x01,
		.offset		= दुरत्व(काष्ठा ssctl_subsys_event_req,
					   subsys_name),
		.ei_array	= शून्य,
	पूर्ण,
	अणु
		.data_type	= QMI_SIGNED_4_BYTE_ENUM,
		.elem_len	= 1,
		.elem_size	= माप(uपूर्णांक32_t),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x02,
		.offset		= दुरत्व(काष्ठा ssctl_subsys_event_req,
					   event),
		.ei_array	= शून्य,
	पूर्ण,
	अणु
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= माप(uपूर्णांक8_t),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x10,
		.offset		= दुरत्व(काष्ठा ssctl_subsys_event_req,
					   evt_driven_valid),
		.ei_array	= शून्य,
	पूर्ण,
	अणु
		.data_type	= QMI_SIGNED_4_BYTE_ENUM,
		.elem_len	= 1,
		.elem_size	= माप(uपूर्णांक32_t),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x10,
		.offset		= दुरत्व(काष्ठा ssctl_subsys_event_req,
					   evt_driven),
		.ei_array	= शून्य,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

काष्ठा ssctl_subsys_event_resp अणु
	काष्ठा qmi_response_type_v01 resp;
पूर्ण;

अटल काष्ठा qmi_elem_info ssctl_subsys_event_resp_ei[] = अणु
	अणु
		.data_type	= QMI_STRUCT,
		.elem_len	= 1,
		.elem_size	= माप(काष्ठा qmi_response_type_v01),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x02,
		.offset		= दुरत्व(काष्ठा ssctl_subsys_event_resp,
					   resp),
		.ei_array	= qmi_response_type_v01_ei,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा qmi_elem_info ssctl_shutकरोwn_ind_ei[] = अणु
	अणुपूर्ण
पूर्ण;

अटल व्योम sysmon_ind_cb(काष्ठा qmi_handle *qmi, काष्ठा sockaddr_qrtr *sq,
			  काष्ठा qmi_txn *txn, स्थिर व्योम *data)
अणु
	काष्ठा qcom_sysmon *sysmon = container_of(qmi, काष्ठा qcom_sysmon, qmi);

	complete(&sysmon->ind_comp);
पूर्ण

अटल स्थिर काष्ठा qmi_msg_handler qmi_indication_handler[] = अणु
	अणु
		.type = QMI_INDICATION,
		.msg_id = SSCTL_SHUTDOWN_READY_IND,
		.ei = ssctl_shutकरोwn_ind_ei,
		.decoded_size = 0,
		.fn = sysmon_ind_cb
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल bool ssctl_request_shutकरोwn_रुको(काष्ठा qcom_sysmon *sysmon)
अणु
	पूर्णांक ret;

	ret = रुको_क्रम_completion_समयout(&sysmon->shutकरोwn_comp, 10 * HZ);
	अगर (ret)
		वापस true;

	ret = try_रुको_क्रम_completion(&sysmon->ind_comp);
	अगर (ret)
		वापस true;

	dev_err(sysmon->dev, "timeout waiting for shutdown ack\n");
	वापस false;
पूर्ण

/**
 * ssctl_request_shutकरोwn() - request shutकरोwn via SSCTL QMI service
 * @sysmon:	sysmon context
 *
 * Return: boolean indicator of the remote processor acking the request
 */
अटल bool ssctl_request_shutकरोwn(काष्ठा qcom_sysmon *sysmon)
अणु
	काष्ठा ssctl_shutकरोwn_resp resp;
	काष्ठा qmi_txn txn;
	bool acked = false;
	पूर्णांक ret;

	reinit_completion(&sysmon->ind_comp);
	reinit_completion(&sysmon->shutकरोwn_comp);
	ret = qmi_txn_init(&sysmon->qmi, &txn, ssctl_shutकरोwn_resp_ei, &resp);
	अगर (ret < 0) अणु
		dev_err(sysmon->dev, "failed to allocate QMI txn\n");
		वापस false;
	पूर्ण

	ret = qmi_send_request(&sysmon->qmi, &sysmon->ssctl, &txn,
			       SSCTL_SHUTDOWN_REQ, 0, शून्य, शून्य);
	अगर (ret < 0) अणु
		dev_err(sysmon->dev, "failed to send shutdown request\n");
		qmi_txn_cancel(&txn);
		वापस false;
	पूर्ण

	ret = qmi_txn_रुको(&txn, 5 * HZ);
	अगर (ret < 0) अणु
		dev_err(sysmon->dev, "timeout waiting for shutdown response\n");
	पूर्ण अन्यथा अगर (resp.resp.result) अणु
		dev_err(sysmon->dev, "shutdown request rejected\n");
	पूर्ण अन्यथा अणु
		dev_dbg(sysmon->dev, "shutdown request completed\n");
		acked = true;
	पूर्ण

	अगर (sysmon->shutकरोwn_irq > 0)
		वापस ssctl_request_shutकरोwn_रुको(sysmon);

	वापस acked;
पूर्ण

/**
 * ssctl_send_event() - send notअगरication of other remote's SSR event
 * @sysmon:	sysmon context
 * @event:	sysmon event context
 */
अटल व्योम ssctl_send_event(काष्ठा qcom_sysmon *sysmon,
			     स्थिर काष्ठा sysmon_event *event)
अणु
	काष्ठा ssctl_subsys_event_resp resp;
	काष्ठा ssctl_subsys_event_req req;
	काष्ठा qmi_txn txn;
	पूर्णांक ret;

	स_रखो(&resp, 0, माप(resp));
	ret = qmi_txn_init(&sysmon->qmi, &txn, ssctl_subsys_event_resp_ei, &resp);
	अगर (ret < 0) अणु
		dev_err(sysmon->dev, "failed to allocate QMI txn\n");
		वापस;
	पूर्ण

	स_रखो(&req, 0, माप(req));
	strlcpy(req.subsys_name, event->subsys_name, माप(req.subsys_name));
	req.subsys_name_len = म_माप(req.subsys_name);
	req.event = event->ssr_event;
	req.evt_driven_valid = true;
	req.evt_driven = SSCTL_SSR_EVENT_FORCED;

	ret = qmi_send_request(&sysmon->qmi, &sysmon->ssctl, &txn,
			       SSCTL_SUBSYS_EVENT_REQ, 40,
			       ssctl_subsys_event_req_ei, &req);
	अगर (ret < 0) अणु
		dev_err(sysmon->dev, "failed to send subsystem event\n");
		qmi_txn_cancel(&txn);
		वापस;
	पूर्ण

	ret = qmi_txn_रुको(&txn, 5 * HZ);
	अगर (ret < 0)
		dev_err(sysmon->dev, "timeout waiting for subsystem event response\n");
	अन्यथा अगर (resp.resp.result)
		dev_err(sysmon->dev, "subsystem event rejected\n");
	अन्यथा
		dev_dbg(sysmon->dev, "subsystem event accepted\n");
पूर्ण

/**
 * ssctl_new_server() - QMI callback indicating a new service
 * @qmi:	QMI handle
 * @svc:	service inक्रमmation
 *
 * Return: 0 अगर we're पूर्णांकerested in this service, -EINVAL otherwise.
 */
अटल पूर्णांक ssctl_new_server(काष्ठा qmi_handle *qmi, काष्ठा qmi_service *svc)
अणु
	काष्ठा qcom_sysmon *sysmon = container_of(qmi, काष्ठा qcom_sysmon, qmi);

	चयन (svc->version) अणु
	हाल 1:
		अगर (svc->instance != 0)
			वापस -EINVAL;
		अगर (म_भेद(sysmon->name, "modem"))
			वापस -EINVAL;
		अवरोध;
	हाल 2:
		अगर (svc->instance != sysmon->ssctl_instance)
			वापस -EINVAL;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	sysmon->ssctl_version = svc->version;

	sysmon->ssctl.sq_family = AF_QIPCRTR;
	sysmon->ssctl.sq_node = svc->node;
	sysmon->ssctl.sq_port = svc->port;

	svc->priv = sysmon;

	वापस 0;
पूर्ण

/**
 * ssctl_del_server() - QMI callback indicating that @svc is हटाओd
 * @qmi:	QMI handle
 * @svc:	service inक्रमmation
 */
अटल व्योम ssctl_del_server(काष्ठा qmi_handle *qmi, काष्ठा qmi_service *svc)
अणु
	काष्ठा qcom_sysmon *sysmon = svc->priv;

	sysmon->ssctl_version = 0;
पूर्ण

अटल स्थिर काष्ठा qmi_ops ssctl_ops = अणु
	.new_server = ssctl_new_server,
	.del_server = ssctl_del_server,
पूर्ण;

अटल पूर्णांक sysmon_prepare(काष्ठा rproc_subdev *subdev)
अणु
	काष्ठा qcom_sysmon *sysmon = container_of(subdev, काष्ठा qcom_sysmon,
						  subdev);
	काष्ठा sysmon_event event = अणु
		.subsys_name = sysmon->name,
		.ssr_event = SSCTL_SSR_EVENT_BEFORE_POWERUP
	पूर्ण;

	mutex_lock(&sysmon->state_lock);
	sysmon->state = SSCTL_SSR_EVENT_BEFORE_POWERUP;
	blocking_notअगरier_call_chain(&sysmon_notअगरiers, 0, (व्योम *)&event);
	mutex_unlock(&sysmon->state_lock);

	वापस 0;
पूर्ण

/**
 * sysmon_start() - start callback क्रम the sysmon remoteproc subdevice
 * @subdev:	instance of the sysmon subdevice
 *
 * Inक्रमm all the listners of sysmon notअगरications that the rproc associated
 * to @subdev has booted up. The rproc that booted up also needs to know
 * which rprocs are alपढ़ोy up and running, so send start notअगरications
 * on behalf of all the online rprocs.
 */
अटल पूर्णांक sysmon_start(काष्ठा rproc_subdev *subdev)
अणु
	काष्ठा qcom_sysmon *sysmon = container_of(subdev, काष्ठा qcom_sysmon,
						  subdev);
	काष्ठा qcom_sysmon *target;
	काष्ठा sysmon_event event = अणु
		.subsys_name = sysmon->name,
		.ssr_event = SSCTL_SSR_EVENT_AFTER_POWERUP
	पूर्ण;

	mutex_lock(&sysmon->state_lock);
	sysmon->state = SSCTL_SSR_EVENT_AFTER_POWERUP;
	blocking_notअगरier_call_chain(&sysmon_notअगरiers, 0, (व्योम *)&event);
	mutex_unlock(&sysmon->state_lock);

	mutex_lock(&sysmon_lock);
	list_क्रम_each_entry(target, &sysmon_list, node) अणु
		अगर (target == sysmon)
			जारी;

		mutex_lock(&target->state_lock);
		event.subsys_name = target->name;
		event.ssr_event = target->state;

		अगर (sysmon->ssctl_version == 2)
			ssctl_send_event(sysmon, &event);
		अन्यथा अगर (sysmon->ept)
			sysmon_send_event(sysmon, &event);
		mutex_unlock(&target->state_lock);
	पूर्ण
	mutex_unlock(&sysmon_lock);

	वापस 0;
पूर्ण

अटल व्योम sysmon_stop(काष्ठा rproc_subdev *subdev, bool crashed)
अणु
	काष्ठा qcom_sysmon *sysmon = container_of(subdev, काष्ठा qcom_sysmon, subdev);
	काष्ठा sysmon_event event = अणु
		.subsys_name = sysmon->name,
		.ssr_event = SSCTL_SSR_EVENT_BEFORE_SHUTDOWN
	पूर्ण;

	sysmon->shutकरोwn_acked = false;

	mutex_lock(&sysmon->state_lock);
	sysmon->state = SSCTL_SSR_EVENT_BEFORE_SHUTDOWN;
	blocking_notअगरier_call_chain(&sysmon_notअगरiers, 0, (व्योम *)&event);
	mutex_unlock(&sysmon->state_lock);

	/* Don't request graceful shutdown if we've crashed */
	अगर (crashed)
		वापस;

	अगर (sysmon->ssctl_version)
		sysmon->shutकरोwn_acked = ssctl_request_shutकरोwn(sysmon);
	अन्यथा अगर (sysmon->ept)
		sysmon->shutकरोwn_acked = sysmon_request_shutकरोwn(sysmon);
पूर्ण

अटल व्योम sysmon_unprepare(काष्ठा rproc_subdev *subdev)
अणु
	काष्ठा qcom_sysmon *sysmon = container_of(subdev, काष्ठा qcom_sysmon,
						  subdev);
	काष्ठा sysmon_event event = अणु
		.subsys_name = sysmon->name,
		.ssr_event = SSCTL_SSR_EVENT_AFTER_SHUTDOWN
	पूर्ण;

	mutex_lock(&sysmon->state_lock);
	sysmon->state = SSCTL_SSR_EVENT_AFTER_SHUTDOWN;
	blocking_notअगरier_call_chain(&sysmon_notअगरiers, 0, (व्योम *)&event);
	mutex_unlock(&sysmon->state_lock);
पूर्ण

/**
 * sysmon_notअगरy() - notअगरy sysmon target of another's SSR
 * @nb:		notअगरier_block associated with sysmon instance
 * @event:	unused
 * @data:	SSR identअगरier of the remote that is going करोwn
 */
अटल पूर्णांक sysmon_notअगरy(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ event,
			 व्योम *data)
अणु
	काष्ठा qcom_sysmon *sysmon = container_of(nb, काष्ठा qcom_sysmon, nb);
	काष्ठा sysmon_event *sysmon_event = data;

	/* Skip non-running rprocs and the originating instance */
	अगर (sysmon->state != SSCTL_SSR_EVENT_AFTER_POWERUP ||
	    !म_भेद(sysmon_event->subsys_name, sysmon->name)) अणु
		dev_dbg(sysmon->dev, "not notifying %s\n", sysmon->name);
		वापस NOTIFY_DONE;
	पूर्ण

	/* Only SSCTL version 2 supports SSR events */
	अगर (sysmon->ssctl_version == 2)
		ssctl_send_event(sysmon, sysmon_event);
	अन्यथा अगर (sysmon->ept)
		sysmon_send_event(sysmon, sysmon_event);

	वापस NOTIFY_DONE;
पूर्ण

अटल irqवापस_t sysmon_shutकरोwn_पूर्णांकerrupt(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा qcom_sysmon *sysmon = data;

	complete(&sysmon->shutकरोwn_comp);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * qcom_add_sysmon_subdev() - create a sysmon subdev क्रम the given remoteproc
 * @rproc:	rproc context to associate the subdev with
 * @name:	name of this subdev, to use in SSR
 * @ssctl_instance: instance id of the ssctl QMI service
 *
 * Return: A new qcom_sysmon object, or शून्य on failure
 */
काष्ठा qcom_sysmon *qcom_add_sysmon_subdev(काष्ठा rproc *rproc,
					   स्थिर अक्षर *name,
					   पूर्णांक ssctl_instance)
अणु
	काष्ठा qcom_sysmon *sysmon;
	पूर्णांक ret;

	sysmon = kzalloc(माप(*sysmon), GFP_KERNEL);
	अगर (!sysmon)
		वापस ERR_PTR(-ENOMEM);

	sysmon->dev = rproc->dev.parent;
	sysmon->rproc = rproc;

	sysmon->name = name;
	sysmon->ssctl_instance = ssctl_instance;

	init_completion(&sysmon->comp);
	init_completion(&sysmon->ind_comp);
	init_completion(&sysmon->shutकरोwn_comp);
	mutex_init(&sysmon->lock);
	mutex_init(&sysmon->state_lock);

	sysmon->shutकरोwn_irq = of_irq_get_byname(sysmon->dev->of_node,
						 "shutdown-ack");
	अगर (sysmon->shutकरोwn_irq < 0) अणु
		अगर (sysmon->shutकरोwn_irq != -ENODATA) अणु
			dev_err(sysmon->dev,
				"failed to retrieve shutdown-ack IRQ\n");
			वापस ERR_PTR(sysmon->shutकरोwn_irq);
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = devm_request_thपढ़ोed_irq(sysmon->dev,
						sysmon->shutकरोwn_irq,
						शून्य, sysmon_shutकरोwn_पूर्णांकerrupt,
						IRQF_TRIGGER_RISING | IRQF_ONESHOT,
						"q6v5 shutdown-ack", sysmon);
		अगर (ret) अणु
			dev_err(sysmon->dev,
				"failed to acquire shutdown-ack IRQ\n");
			वापस ERR_PTR(ret);
		पूर्ण
	पूर्ण

	ret = qmi_handle_init(&sysmon->qmi, SSCTL_MAX_MSG_LEN, &ssctl_ops,
			      qmi_indication_handler);
	अगर (ret < 0) अणु
		dev_err(sysmon->dev, "failed to initialize qmi handle\n");
		kमुक्त(sysmon);
		वापस ERR_PTR(ret);
	पूर्ण

	qmi_add_lookup(&sysmon->qmi, 43, 0, 0);

	sysmon->subdev.prepare = sysmon_prepare;
	sysmon->subdev.start = sysmon_start;
	sysmon->subdev.stop = sysmon_stop;
	sysmon->subdev.unprepare = sysmon_unprepare;

	rproc_add_subdev(rproc, &sysmon->subdev);

	sysmon->nb.notअगरier_call = sysmon_notअगरy;
	blocking_notअगरier_chain_रेजिस्टर(&sysmon_notअगरiers, &sysmon->nb);

	mutex_lock(&sysmon_lock);
	list_add(&sysmon->node, &sysmon_list);
	mutex_unlock(&sysmon_lock);

	वापस sysmon;
पूर्ण
EXPORT_SYMBOL_GPL(qcom_add_sysmon_subdev);

/**
 * qcom_हटाओ_sysmon_subdev() - release a qcom_sysmon
 * @sysmon:	sysmon context, as retrieved by qcom_add_sysmon_subdev()
 */
व्योम qcom_हटाओ_sysmon_subdev(काष्ठा qcom_sysmon *sysmon)
अणु
	अगर (!sysmon)
		वापस;

	mutex_lock(&sysmon_lock);
	list_del(&sysmon->node);
	mutex_unlock(&sysmon_lock);

	blocking_notअगरier_chain_unरेजिस्टर(&sysmon_notअगरiers, &sysmon->nb);

	rproc_हटाओ_subdev(sysmon->rproc, &sysmon->subdev);

	qmi_handle_release(&sysmon->qmi);

	kमुक्त(sysmon);
पूर्ण
EXPORT_SYMBOL_GPL(qcom_हटाओ_sysmon_subdev);

/**
 * qcom_sysmon_shutकरोwn_acked() - query the success of the last shutकरोwn
 * @sysmon:	sysmon context
 *
 * When sysmon is used to request a graceful shutकरोwn of the remote processor
 * this can be used by the remoteproc driver to query the success, in order to
 * know अगर it should fall back to other means of requesting a shutकरोwn.
 *
 * Return: boolean indicator of the success of the last shutकरोwn request
 */
bool qcom_sysmon_shutकरोwn_acked(काष्ठा qcom_sysmon *sysmon)
अणु
	वापस sysmon && sysmon->shutकरोwn_acked;
पूर्ण
EXPORT_SYMBOL_GPL(qcom_sysmon_shutकरोwn_acked);

/**
 * sysmon_probe() - probe sys_mon channel
 * @rpdev:	rpmsg device handle
 *
 * Find the sysmon context associated with the ancestor remoteproc and assign
 * this rpmsg device with said sysmon context.
 *
 * Return: 0 on success, negative त्रुटि_सं on failure.
 */
अटल पूर्णांक sysmon_probe(काष्ठा rpmsg_device *rpdev)
अणु
	काष्ठा qcom_sysmon *sysmon;
	काष्ठा rproc *rproc;

	rproc = rproc_get_by_child(&rpdev->dev);
	अगर (!rproc) अणु
		dev_err(&rpdev->dev, "sysmon device not child of rproc\n");
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&sysmon_lock);
	list_क्रम_each_entry(sysmon, &sysmon_list, node) अणु
		अगर (sysmon->rproc == rproc)
			जाओ found;
	पूर्ण
	mutex_unlock(&sysmon_lock);

	dev_err(&rpdev->dev, "no sysmon associated with parent rproc\n");

	वापस -EINVAL;

found:
	mutex_unlock(&sysmon_lock);

	rpdev->ept->priv = sysmon;
	sysmon->ept = rpdev->ept;

	वापस 0;
पूर्ण

/**
 * sysmon_हटाओ() - sys_mon channel हटाओ handler
 * @rpdev:	rpmsg device handle
 *
 * Disassociate the rpmsg device with the sysmon instance.
 */
अटल व्योम sysmon_हटाओ(काष्ठा rpmsg_device *rpdev)
अणु
	काष्ठा qcom_sysmon *sysmon = rpdev->ept->priv;

	sysmon->ept = शून्य;
पूर्ण

अटल स्थिर काष्ठा rpmsg_device_id sysmon_match[] = अणु
	अणु "sys_mon" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा rpmsg_driver sysmon_driver = अणु
	.probe = sysmon_probe,
	.हटाओ = sysmon_हटाओ,
	.callback = sysmon_callback,
	.id_table = sysmon_match,
	.drv = अणु
		.name = "qcom_sysmon",
	पूर्ण,
पूर्ण;

module_rpmsg_driver(sysmon_driver);

MODULE_DESCRIPTION("Qualcomm sysmon driver");
MODULE_LICENSE("GPL v2");
