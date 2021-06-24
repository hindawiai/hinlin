<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Driver क्रम the Surface ACPI Notअगरy (SAN) पूर्णांकerface/shim.
 *
 * Translates communication from ACPI to Surface System Aggregator Module
 * (SSAM/SAM) requests and back, specअगरically SAM-over-SSH. Translates SSAM
 * events back to ACPI notअगरications. Allows handling of discrete GPU
 * notअगरications sent from ACPI via the SAN पूर्णांकerface by providing them to any
 * रेजिस्टरed बाह्यal driver.
 *
 * Copyright (C) 2019-2020 Maximilian Luz <luzmaximilian@gmail.com>
 */

#समावेश <यंत्र/unaligned.h>
#समावेश <linux/acpi.h>
#समावेश <linux/delay.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/rwsem.h>

#समावेश <linux/surface_aggregator/controller.h>
#समावेश <linux/surface_acpi_notअगरy.h>

काष्ठा san_data अणु
	काष्ठा device *dev;
	काष्ठा ssam_controller *ctrl;

	काष्ठा acpi_connection_info info;

	काष्ठा ssam_event_notअगरier nf_bat;
	काष्ठा ssam_event_notअगरier nf_पंचांगp;
पूर्ण;

#घोषणा to_san_data(ptr, member) \
	container_of(ptr, काष्ठा san_data, member)


/* -- dGPU notअगरier पूर्णांकerface. ---------------------------------------------- */

काष्ठा san_rqsg_अगर अणु
	काष्ठा rw_semaphore lock;
	काष्ठा device *dev;
	काष्ठा blocking_notअगरier_head nh;
पूर्ण;

अटल काष्ठा san_rqsg_अगर san_rqsg_अगर = अणु
	.lock = __RWSEM_INITIALIZER(san_rqsg_अगर.lock),
	.dev = शून्य,
	.nh = BLOCKING_NOTIFIER_INIT(san_rqsg_अगर.nh),
पूर्ण;

अटल पूर्णांक san_set_rqsg_पूर्णांकerface_device(काष्ठा device *dev)
अणु
	पूर्णांक status = 0;

	करोwn_ग_लिखो(&san_rqsg_अगर.lock);
	अगर (!san_rqsg_अगर.dev && dev)
		san_rqsg_अगर.dev = dev;
	अन्यथा
		status = -EBUSY;
	up_ग_लिखो(&san_rqsg_अगर.lock);

	वापस status;
पूर्ण

/**
 * san_client_link() - Link client as consumer to SAN device.
 * @client: The client to link.
 *
 * Sets up a device link between the provided client device as consumer and
 * the SAN device as provider. This function can be used to ensure that the
 * SAN पूर्णांकerface has been set up and will be set up क्रम as दीर्घ as the driver
 * of the client device is bound. This guarantees that, during that समय, all
 * dGPU events will be received by any रेजिस्टरed notअगरier.
 *
 * The link will be स्वतःmatically हटाओd once the client device's driver is
 * unbound.
 *
 * Return: Returns zero on success, %-ENXIO अगर the SAN पूर्णांकerface has not been
 * set up yet, and %-ENOMEM अगर device link creation failed.
 */
पूर्णांक san_client_link(काष्ठा device *client)
अणु
	स्थिर u32 flags = DL_FLAG_PM_RUNTIME | DL_FLAG_AUTOREMOVE_CONSUMER;
	काष्ठा device_link *link;

	करोwn_पढ़ो(&san_rqsg_अगर.lock);

	अगर (!san_rqsg_अगर.dev) अणु
		up_पढ़ो(&san_rqsg_अगर.lock);
		वापस -ENXIO;
	पूर्ण

	link = device_link_add(client, san_rqsg_अगर.dev, flags);
	अगर (!link) अणु
		up_पढ़ो(&san_rqsg_अगर.lock);
		वापस -ENOMEM;
	पूर्ण

	अगर (READ_ONCE(link->status) == DL_STATE_SUPPLIER_UNBIND) अणु
		up_पढ़ो(&san_rqsg_अगर.lock);
		वापस -ENXIO;
	पूर्ण

	up_पढ़ो(&san_rqsg_अगर.lock);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(san_client_link);

/**
 * san_dgpu_notअगरier_रेजिस्टर() - Register a SAN dGPU notअगरier.
 * @nb: The notअगरier-block to रेजिस्टर.
 *
 * Registers a SAN dGPU notअगरier, receiving any new SAN dGPU events sent from
 * ACPI. The रेजिस्टरed notअगरier will be called with &काष्ठा san_dgpu_event
 * as notअगरier data and the command ID of that event as notअगरier action.
 */
पूर्णांक san_dgpu_notअगरier_रेजिस्टर(काष्ठा notअगरier_block *nb)
अणु
	वापस blocking_notअगरier_chain_रेजिस्टर(&san_rqsg_अगर.nh, nb);
पूर्ण
EXPORT_SYMBOL_GPL(san_dgpu_notअगरier_रेजिस्टर);

/**
 * san_dgpu_notअगरier_unरेजिस्टर() - Unरेजिस्टर a SAN dGPU notअगरier.
 * @nb: The notअगरier-block to unरेजिस्टर.
 */
पूर्णांक san_dgpu_notअगरier_unरेजिस्टर(काष्ठा notअगरier_block *nb)
अणु
	वापस blocking_notअगरier_chain_unरेजिस्टर(&san_rqsg_अगर.nh, nb);
पूर्ण
EXPORT_SYMBOL_GPL(san_dgpu_notअगरier_unरेजिस्टर);

अटल पूर्णांक san_dgpu_notअगरier_call(काष्ठा san_dgpu_event *evt)
अणु
	पूर्णांक ret;

	ret = blocking_notअगरier_call_chain(&san_rqsg_अगर.nh, evt->command, evt);
	वापस notअगरier_to_त्रुटि_सं(ret);
पूर्ण


/* -- ACPI _DSM event relay. ------------------------------------------------ */

#घोषणा SAN_DSM_REVISION	0

/* 93b666c5-70c6-469f-a215-3d487c91ab3c */
अटल स्थिर guid_t SAN_DSM_UUID =
	GUID_INIT(0x93b666c5, 0x70c6, 0x469f, 0xa2, 0x15, 0x3d,
		  0x48, 0x7c, 0x91, 0xab, 0x3c);

क्रमागत san_dsm_event_fn अणु
	SAN_DSM_EVENT_FN_BAT1_STAT = 0x03,
	SAN_DSM_EVENT_FN_BAT1_INFO = 0x04,
	SAN_DSM_EVENT_FN_ADP1_STAT = 0x05,
	SAN_DSM_EVENT_FN_ADP1_INFO = 0x06,
	SAN_DSM_EVENT_FN_BAT2_STAT = 0x07,
	SAN_DSM_EVENT_FN_BAT2_INFO = 0x08,
	SAN_DSM_EVENT_FN_THERMAL   = 0x09,
	SAN_DSM_EVENT_FN_DPTF      = 0x0a,
पूर्ण;

क्रमागत sam_event_cid_bat अणु
	SAM_EVENT_CID_BAT_BIX  = 0x15,
	SAM_EVENT_CID_BAT_BST  = 0x16,
	SAM_EVENT_CID_BAT_ADP  = 0x17,
	SAM_EVENT_CID_BAT_PROT = 0x18,
	SAM_EVENT_CID_BAT_DPTF = 0x4f,
पूर्ण;

क्रमागत sam_event_cid_पंचांगp अणु
	SAM_EVENT_CID_TMP_TRIP = 0x0b,
पूर्ण;

काष्ठा san_event_work अणु
	काष्ठा delayed_work work;
	काष्ठा device *dev;
	काष्ठा ssam_event event;	/* must be last */
पूर्ण;

अटल पूर्णांक san_acpi_notअगरy_event(काष्ठा device *dev, u64 func,
				 जोड़ acpi_object *param)
अणु
	acpi_handle san = ACPI_HANDLE(dev);
	जोड़ acpi_object *obj;
	पूर्णांक status = 0;

	अगर (!acpi_check_dsm(san, &SAN_DSM_UUID, SAN_DSM_REVISION, BIT_ULL(func)))
		वापस 0;

	dev_dbg(dev, "notify event %#04llx\n", func);

	obj = acpi_evaluate_dsm_typed(san, &SAN_DSM_UUID, SAN_DSM_REVISION,
				      func, param, ACPI_TYPE_BUFFER);
	अगर (!obj)
		वापस -EFAULT;

	अगर (obj->buffer.length != 1 || obj->buffer.poपूर्णांकer[0] != 0) अणु
		dev_err(dev, "got unexpected result from _DSM\n");
		status = -EPROTO;
	पूर्ण

	ACPI_FREE(obj);
	वापस status;
पूर्ण

अटल पूर्णांक san_evt_bat_adp(काष्ठा device *dev, स्थिर काष्ठा ssam_event *event)
अणु
	पूर्णांक status;

	status = san_acpi_notअगरy_event(dev, SAN_DSM_EVENT_FN_ADP1_STAT, शून्य);
	अगर (status)
		वापस status;

	/*
	 * Ensure that the battery states get updated correctly. When the
	 * battery is fully अक्षरged and an adapter is plugged in, it someबार
	 * is not updated correctly, instead showing it as अक्षरging.
	 * Explicitly trigger battery updates to fix this.
	 */

	status = san_acpi_notअगरy_event(dev, SAN_DSM_EVENT_FN_BAT1_STAT, शून्य);
	अगर (status)
		वापस status;

	वापस san_acpi_notअगरy_event(dev, SAN_DSM_EVENT_FN_BAT2_STAT, शून्य);
पूर्ण

अटल पूर्णांक san_evt_bat_bix(काष्ठा device *dev, स्थिर काष्ठा ssam_event *event)
अणु
	क्रमागत san_dsm_event_fn fn;

	अगर (event->instance_id == 0x02)
		fn = SAN_DSM_EVENT_FN_BAT2_INFO;
	अन्यथा
		fn = SAN_DSM_EVENT_FN_BAT1_INFO;

	वापस san_acpi_notअगरy_event(dev, fn, शून्य);
पूर्ण

अटल पूर्णांक san_evt_bat_bst(काष्ठा device *dev, स्थिर काष्ठा ssam_event *event)
अणु
	क्रमागत san_dsm_event_fn fn;

	अगर (event->instance_id == 0x02)
		fn = SAN_DSM_EVENT_FN_BAT2_STAT;
	अन्यथा
		fn = SAN_DSM_EVENT_FN_BAT1_STAT;

	वापस san_acpi_notअगरy_event(dev, fn, शून्य);
पूर्ण

अटल पूर्णांक san_evt_bat_dptf(काष्ठा device *dev, स्थिर काष्ठा ssam_event *event)
अणु
	जोड़ acpi_object payload;

	/*
	 * The Surface ACPI expects a buffer and not a package. It specअगरically
	 * checks क्रम ObjectType (Arg3) == 0x03. This will cause a warning in
	 * acpica/nsarguments.c, but that warning can be safely ignored.
	 */
	payload.type = ACPI_TYPE_BUFFER;
	payload.buffer.length = event->length;
	payload.buffer.poपूर्णांकer = (u8 *)&event->data[0];

	वापस san_acpi_notअगरy_event(dev, SAN_DSM_EVENT_FN_DPTF, &payload);
पूर्ण

अटल अचिन्हित दीर्घ san_evt_bat_delay(u8 cid)
अणु
	चयन (cid) अणु
	हाल SAM_EVENT_CID_BAT_ADP:
		/*
		 * Wait क्रम battery state to update beक्रमe संकेतing adapter
		 * change.
		 */
		वापस msecs_to_jअगरfies(5000);

	हाल SAM_EVENT_CID_BAT_BST:
		/* Ensure we करो not miss anything important due to caching. */
		वापस msecs_to_jअगरfies(2000);

	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल bool san_evt_bat(स्थिर काष्ठा ssam_event *event, काष्ठा device *dev)
अणु
	पूर्णांक status;

	चयन (event->command_id) अणु
	हाल SAM_EVENT_CID_BAT_BIX:
		status = san_evt_bat_bix(dev, event);
		अवरोध;

	हाल SAM_EVENT_CID_BAT_BST:
		status = san_evt_bat_bst(dev, event);
		अवरोध;

	हाल SAM_EVENT_CID_BAT_ADP:
		status = san_evt_bat_adp(dev, event);
		अवरोध;

	हाल SAM_EVENT_CID_BAT_PROT:
		/*
		 * TODO: Implement support क्रम battery protection status change
		 *       event.
		 */
		वापस true;

	हाल SAM_EVENT_CID_BAT_DPTF:
		status = san_evt_bat_dptf(dev, event);
		अवरोध;

	शेष:
		वापस false;
	पूर्ण

	अगर (status) अणु
		dev_err(dev, "error handling power event (cid = %#04x)\n",
			event->command_id);
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम san_evt_bat_workfn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा san_event_work *ev;

	ev = container_of(work, काष्ठा san_event_work, work.work);
	san_evt_bat(&ev->event, ev->dev);
	kमुक्त(ev);
पूर्ण

अटल u32 san_evt_bat_nf(काष्ठा ssam_event_notअगरier *nf,
			  स्थिर काष्ठा ssam_event *event)
अणु
	काष्ठा san_data *d = to_san_data(nf, nf_bat);
	काष्ठा san_event_work *work;
	अचिन्हित दीर्घ delay = san_evt_bat_delay(event->command_id);

	अगर (delay == 0)
		वापस san_evt_bat(event, d->dev) ? SSAM_NOTIF_HANDLED : 0;

	work = kzalloc(माप(*work) + event->length, GFP_KERNEL);
	अगर (!work)
		वापस ssam_notअगरier_from_त्रुटि_सं(-ENOMEM);

	INIT_DELAYED_WORK(&work->work, san_evt_bat_workfn);
	work->dev = d->dev;

	स_नकल(&work->event, event, माप(काष्ठा ssam_event) + event->length);

	schedule_delayed_work(&work->work, delay);
	वापस SSAM_NOTIF_HANDLED;
पूर्ण

अटल पूर्णांक san_evt_पंचांगp_trip(काष्ठा device *dev, स्थिर काष्ठा ssam_event *event)
अणु
	जोड़ acpi_object param;

	/*
	 * The Surface ACPI expects an पूर्णांकeger and not a package. This will
	 * cause a warning in acpica/nsarguments.c, but that warning can be
	 * safely ignored.
	 */
	param.type = ACPI_TYPE_INTEGER;
	param.पूर्णांकeger.value = event->instance_id;

	वापस san_acpi_notअगरy_event(dev, SAN_DSM_EVENT_FN_THERMAL, &param);
पूर्ण

अटल bool san_evt_पंचांगp(स्थिर काष्ठा ssam_event *event, काष्ठा device *dev)
अणु
	पूर्णांक status;

	चयन (event->command_id) अणु
	हाल SAM_EVENT_CID_TMP_TRIP:
		status = san_evt_पंचांगp_trip(dev, event);
		अवरोध;

	शेष:
		वापस false;
	पूर्ण

	अगर (status) अणु
		dev_err(dev, "error handling thermal event (cid = %#04x)\n",
			event->command_id);
	पूर्ण

	वापस true;
पूर्ण

अटल u32 san_evt_पंचांगp_nf(काष्ठा ssam_event_notअगरier *nf,
			  स्थिर काष्ठा ssam_event *event)
अणु
	काष्ठा san_data *d = to_san_data(nf, nf_पंचांगp);

	वापस san_evt_पंचांगp(event, d->dev) ? SSAM_NOTIF_HANDLED : 0;
पूर्ण


/* -- ACPI GSB OperationRegion handler -------------------------------------- */

काष्ठा gsb_data_in अणु
	u8 cv;
पूर्ण __packed;

काष्ठा gsb_data_rqsx अणु
	u8 cv;				/* Command value (san_gsb_request_cv). */
	u8 tc;				/* Target category. */
	u8 tid;				/* Target ID. */
	u8 iid;				/* Instance ID. */
	u8 snc;				/* Expect-response-flag. */
	u8 cid;				/* Command ID. */
	u16 cdl;			/* Payload length. */
	u8 pld[];			/* Payload. */
पूर्ण __packed;

काष्ठा gsb_data_etwl अणु
	u8 cv;				/* Command value (should be 0x02). */
	u8 etw3;			/* Unknown. */
	u8 etw4;			/* Unknown. */
	u8 msg[];			/* Error message (ASCIIZ). */
पूर्ण __packed;

काष्ठा gsb_data_out अणु
	u8 status;			/* _SSH communication status. */
	u8 len;				/* _SSH payload length. */
	u8 pld[];			/* _SSH payload. */
पूर्ण __packed;

जोड़ gsb_buffer_data अणु
	काष्ठा gsb_data_in   in;	/* Common input. */
	काष्ठा gsb_data_rqsx rqsx;	/* RQSX input. */
	काष्ठा gsb_data_etwl etwl;	/* ETWL input. */
	काष्ठा gsb_data_out  out;	/* Output. */
पूर्ण;

काष्ठा gsb_buffer अणु
	u8 status;			/* GSB AttribRawProcess status. */
	u8 len;				/* GSB AttribRawProcess length. */
	जोड़ gsb_buffer_data data;
पूर्ण __packed;

#घोषणा SAN_GSB_MAX_RQSX_PAYLOAD  (U8_MAX - 2 - माप(काष्ठा gsb_data_rqsx))
#घोषणा SAN_GSB_MAX_RESPONSE	  (U8_MAX - 2 - माप(काष्ठा gsb_data_out))

#घोषणा SAN_GSB_COMMAND		0

क्रमागत san_gsb_request_cv अणु
	SAN_GSB_REQUEST_CV_RQST = 0x01,
	SAN_GSB_REQUEST_CV_ETWL = 0x02,
	SAN_GSB_REQUEST_CV_RQSG = 0x03,
पूर्ण;

#घोषणा SAN_REQUEST_NUM_TRIES	5

अटल acpi_status san_etwl(काष्ठा san_data *d, काष्ठा gsb_buffer *b)
अणु
	काष्ठा gsb_data_etwl *etwl = &b->data.etwl;

	अगर (b->len < माप(काष्ठा gsb_data_etwl)) अणु
		dev_err(d->dev, "invalid ETWL package (len = %d)\n", b->len);
		वापस AE_OK;
	पूर्ण

	dev_err(d->dev, "ETWL(%#04x, %#04x): %.*s\n", etwl->etw3, etwl->etw4,
		(अचिन्हित पूर्णांक)(b->len - माप(काष्ठा gsb_data_etwl)),
		(अक्षर *)etwl->msg);

	/* Indicate success. */
	b->status = 0x00;
	b->len = 0x00;

	वापस AE_OK;
पूर्ण

अटल
काष्ठा gsb_data_rqsx *san_validate_rqsx(काष्ठा device *dev, स्थिर अक्षर *type,
					काष्ठा gsb_buffer *b)
अणु
	काष्ठा gsb_data_rqsx *rqsx = &b->data.rqsx;

	अगर (b->len < माप(काष्ठा gsb_data_rqsx)) अणु
		dev_err(dev, "invalid %s package (len = %d)\n", type, b->len);
		वापस शून्य;
	पूर्ण

	अगर (get_unaligned(&rqsx->cdl) != b->len - माप(काष्ठा gsb_data_rqsx)) अणु
		dev_err(dev, "bogus %s package (len = %d, cdl = %d)\n",
			type, b->len, get_unaligned(&rqsx->cdl));
		वापस शून्य;
	पूर्ण

	अगर (get_unaligned(&rqsx->cdl) > SAN_GSB_MAX_RQSX_PAYLOAD) अणु
		dev_err(dev, "payload for %s package too large (cdl = %d)\n",
			type, get_unaligned(&rqsx->cdl));
		वापस शून्य;
	पूर्ण

	वापस rqsx;
पूर्ण

अटल व्योम gsb_rqsx_response_error(काष्ठा gsb_buffer *gsb, पूर्णांक status)
अणु
	gsb->status = 0x00;
	gsb->len = 0x02;
	gsb->data.out.status = (u8)(-status);
	gsb->data.out.len = 0x00;
पूर्ण

अटल व्योम gsb_rqsx_response_success(काष्ठा gsb_buffer *gsb, u8 *ptr, माप_प्रकार len)
अणु
	gsb->status = 0x00;
	gsb->len = len + 2;
	gsb->data.out.status = 0x00;
	gsb->data.out.len = len;

	अगर (len)
		स_नकल(&gsb->data.out.pld[0], ptr, len);
पूर्ण

अटल acpi_status san_rqst_fixup_suspended(काष्ठा san_data *d,
					    काष्ठा ssam_request *rqst,
					    काष्ठा gsb_buffer *gsb)
अणु
	अगर (rqst->target_category == SSAM_SSH_TC_BAS && rqst->command_id == 0x0D) अणु
		u8 base_state = 1;

		/* Base state quirk:
		 * The base state may be queried from ACPI when the EC is still
		 * suspended. In this हाल it will वापस '-EPERM'. This query
		 * will only be triggered from the ACPI lid GPE पूर्णांकerrupt, thus
		 * we are either in laptop or studio mode (base status 0x01 or
		 * 0x02). Furthermore, we will only get here अगर the device (and
		 * EC) have been suspended.
		 *
		 * We now assume that the device is in laptop mode (0x01). This
		 * has the drawback that it will wake the device when unfolding
		 * it in studio mode, but it also allows us to aव्योम actively
		 * रुकोing क्रम the EC to wake up, which may incur a notable
		 * delay.
		 */

		dev_dbg(d->dev, "rqst: fixup: base-state quirk\n");

		gsb_rqsx_response_success(gsb, &base_state, माप(base_state));
		वापस AE_OK;
	पूर्ण

	gsb_rqsx_response_error(gsb, -ENXIO);
	वापस AE_OK;
पूर्ण

अटल acpi_status san_rqst(काष्ठा san_data *d, काष्ठा gsb_buffer *buffer)
अणु
	u8 rspbuf[SAN_GSB_MAX_RESPONSE];
	काष्ठा gsb_data_rqsx *gsb_rqst;
	काष्ठा ssam_request rqst;
	काष्ठा ssam_response rsp;
	पूर्णांक status = 0;

	gsb_rqst = san_validate_rqsx(d->dev, "RQST", buffer);
	अगर (!gsb_rqst)
		वापस AE_OK;

	rqst.target_category = gsb_rqst->tc;
	rqst.target_id = gsb_rqst->tid;
	rqst.command_id = gsb_rqst->cid;
	rqst.instance_id = gsb_rqst->iid;
	rqst.flags = gsb_rqst->snc ? SSAM_REQUEST_HAS_RESPONSE : 0;
	rqst.length = get_unaligned(&gsb_rqst->cdl);
	rqst.payload = &gsb_rqst->pld[0];

	rsp.capacity = ARRAY_SIZE(rspbuf);
	rsp.length = 0;
	rsp.poपूर्णांकer = &rspbuf[0];

	/* Handle suspended device. */
	अगर (d->dev->घातer.is_suspended) अणु
		dev_warn(d->dev, "rqst: device is suspended, not executing\n");
		वापस san_rqst_fixup_suspended(d, &rqst, buffer);
	पूर्ण

	status = __ssam_retry(ssam_request_sync_onstack, SAN_REQUEST_NUM_TRIES,
			      d->ctrl, &rqst, &rsp, SAN_GSB_MAX_RQSX_PAYLOAD);

	अगर (!status) अणु
		gsb_rqsx_response_success(buffer, rsp.poपूर्णांकer, rsp.length);
	पूर्ण अन्यथा अणु
		dev_err(d->dev, "rqst: failed with error %d\n", status);
		gsb_rqsx_response_error(buffer, status);
	पूर्ण

	वापस AE_OK;
पूर्ण

अटल acpi_status san_rqsg(काष्ठा san_data *d, काष्ठा gsb_buffer *buffer)
अणु
	काष्ठा gsb_data_rqsx *gsb_rqsg;
	काष्ठा san_dgpu_event evt;
	पूर्णांक status;

	gsb_rqsg = san_validate_rqsx(d->dev, "RQSG", buffer);
	अगर (!gsb_rqsg)
		वापस AE_OK;

	evt.category = gsb_rqsg->tc;
	evt.target = gsb_rqsg->tid;
	evt.command = gsb_rqsg->cid;
	evt.instance = gsb_rqsg->iid;
	evt.length = get_unaligned(&gsb_rqsg->cdl);
	evt.payload = &gsb_rqsg->pld[0];

	status = san_dgpu_notअगरier_call(&evt);
	अगर (!status) अणु
		gsb_rqsx_response_success(buffer, शून्य, 0);
	पूर्ण अन्यथा अणु
		dev_err(d->dev, "rqsg: failed with error %d\n", status);
		gsb_rqsx_response_error(buffer, status);
	पूर्ण

	वापस AE_OK;
पूर्ण

अटल acpi_status san_opreg_handler(u32 function, acpi_physical_address command,
				     u32 bits, u64 *value64, व्योम *opreg_context,
				     व्योम *region_context)
अणु
	काष्ठा san_data *d = to_san_data(opreg_context, info);
	काष्ठा gsb_buffer *buffer = (काष्ठा gsb_buffer *)value64;
	पूर्णांक accessor_type = (function & 0xFFFF0000) >> 16;

	अगर (command != SAN_GSB_COMMAND) अणु
		dev_warn(d->dev, "unsupported command: %#04llx\n", command);
		वापस AE_OK;
	पूर्ण

	अगर (accessor_type != ACPI_GSB_ACCESS_ATTRIB_RAW_PROCESS) अणु
		dev_err(d->dev, "invalid access type: %#04x\n", accessor_type);
		वापस AE_OK;
	पूर्ण

	/* Buffer must have at least contain the command-value. */
	अगर (buffer->len == 0) अणु
		dev_err(d->dev, "request-package too small\n");
		वापस AE_OK;
	पूर्ण

	चयन (buffer->data.in.cv) अणु
	हाल SAN_GSB_REQUEST_CV_RQST:
		वापस san_rqst(d, buffer);

	हाल SAN_GSB_REQUEST_CV_ETWL:
		वापस san_etwl(d, buffer);

	हाल SAN_GSB_REQUEST_CV_RQSG:
		वापस san_rqsg(d, buffer);

	शेष:
		dev_warn(d->dev, "unsupported SAN0 request (cv: %#04x)\n",
			 buffer->data.in.cv);
		वापस AE_OK;
	पूर्ण
पूर्ण


/* -- Driver setup. --------------------------------------------------------- */

अटल पूर्णांक san_events_रेजिस्टर(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा san_data *d = platक्रमm_get_drvdata(pdev);
	पूर्णांक status;

	d->nf_bat.base.priority = 1;
	d->nf_bat.base.fn = san_evt_bat_nf;
	d->nf_bat.event.reg = SSAM_EVENT_REGISTRY_SAM;
	d->nf_bat.event.id.target_category = SSAM_SSH_TC_BAT;
	d->nf_bat.event.id.instance = 0;
	d->nf_bat.event.mask = SSAM_EVENT_MASK_TARGET;
	d->nf_bat.event.flags = SSAM_EVENT_SEQUENCED;

	d->nf_पंचांगp.base.priority = 1;
	d->nf_पंचांगp.base.fn = san_evt_पंचांगp_nf;
	d->nf_पंचांगp.event.reg = SSAM_EVENT_REGISTRY_SAM;
	d->nf_पंचांगp.event.id.target_category = SSAM_SSH_TC_TMP;
	d->nf_पंचांगp.event.id.instance = 0;
	d->nf_पंचांगp.event.mask = SSAM_EVENT_MASK_TARGET;
	d->nf_पंचांगp.event.flags = SSAM_EVENT_SEQUENCED;

	status = ssam_notअगरier_रेजिस्टर(d->ctrl, &d->nf_bat);
	अगर (status)
		वापस status;

	status = ssam_notअगरier_रेजिस्टर(d->ctrl, &d->nf_पंचांगp);
	अगर (status)
		ssam_notअगरier_unरेजिस्टर(d->ctrl, &d->nf_bat);

	वापस status;
पूर्ण

अटल व्योम san_events_unरेजिस्टर(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा san_data *d = platक्रमm_get_drvdata(pdev);

	ssam_notअगरier_unरेजिस्टर(d->ctrl, &d->nf_bat);
	ssam_notअगरier_unरेजिस्टर(d->ctrl, &d->nf_पंचांगp);
पूर्ण

#घोषणा san_consumer_prपूर्णांकk(level, dev, handle, fmt, ...)			\
करो अणु										\
	अक्षर *path = "<error getting consumer path>";				\
	काष्ठा acpi_buffer buffer = अणु						\
		.length = ACPI_ALLOCATE_BUFFER,					\
		.poपूर्णांकer = शून्य,						\
	पूर्ण;									\
										\
	अगर (ACPI_SUCCESS(acpi_get_name(handle, ACPI_FULL_PATHNAME, &buffer)))	\
		path = buffer.poपूर्णांकer;						\
										\
	dev_##level(dev, "[%s]: " fmt, path, ##__VA_ARGS__);			\
	kमुक्त(buffer.poपूर्णांकer);							\
पूर्ण जबतक (0)

#घोषणा san_consumer_dbg(dev, handle, fmt, ...) \
	san_consumer_prपूर्णांकk(dbg, dev, handle, fmt, ##__VA_ARGS__)

#घोषणा san_consumer_warn(dev, handle, fmt, ...) \
	san_consumer_prपूर्णांकk(warn, dev, handle, fmt, ##__VA_ARGS__)

अटल bool is_san_consumer(काष्ठा platक्रमm_device *pdev, acpi_handle handle)
अणु
	काष्ठा acpi_handle_list dep_devices;
	acpi_handle supplier = ACPI_HANDLE(&pdev->dev);
	acpi_status status;
	पूर्णांक i;

	अगर (!acpi_has_method(handle, "_DEP"))
		वापस false;

	status = acpi_evaluate_reference(handle, "_DEP", शून्य, &dep_devices);
	अगर (ACPI_FAILURE(status)) अणु
		san_consumer_dbg(&pdev->dev, handle, "failed to evaluate _DEP\n");
		वापस false;
	पूर्ण

	क्रम (i = 0; i < dep_devices.count; i++) अणु
		अगर (dep_devices.handles[i] == supplier)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल acpi_status san_consumer_setup(acpi_handle handle, u32 lvl,
				      व्योम *context, व्योम **rv)
अणु
	स्थिर u32 flags = DL_FLAG_PM_RUNTIME | DL_FLAG_AUTOREMOVE_SUPPLIER;
	काष्ठा platक्रमm_device *pdev = context;
	काष्ठा acpi_device *adev;
	काष्ठा device_link *link;

	अगर (!is_san_consumer(pdev, handle))
		वापस AE_OK;

	/* Ignore ACPI devices that are not present. */
	अगर (acpi_bus_get_device(handle, &adev) != 0)
		वापस AE_OK;

	san_consumer_dbg(&pdev->dev, handle, "creating device link\n");

	/* Try to set up device links, ignore but log errors. */
	link = device_link_add(&adev->dev, &pdev->dev, flags);
	अगर (!link) अणु
		san_consumer_warn(&pdev->dev, handle, "failed to create device link\n");
		वापस AE_OK;
	पूर्ण

	वापस AE_OK;
पूर्ण

अटल पूर्णांक san_consumer_links_setup(काष्ठा platक्रमm_device *pdev)
अणु
	acpi_status status;

	status = acpi_walk_namespace(ACPI_TYPE_DEVICE, ACPI_ROOT_OBJECT,
				     ACPI_UINT32_MAX, san_consumer_setup, शून्य,
				     pdev, शून्य);

	वापस status ? -EFAULT : 0;
पूर्ण

अटल पूर्णांक san_probe(काष्ठा platक्रमm_device *pdev)
अणु
	acpi_handle san = ACPI_HANDLE(&pdev->dev);
	काष्ठा ssam_controller *ctrl;
	काष्ठा san_data *data;
	acpi_status astatus;
	पूर्णांक status;

	ctrl = ssam_client_bind(&pdev->dev);
	अगर (IS_ERR(ctrl))
		वापस PTR_ERR(ctrl) == -ENODEV ? -EPROBE_DEFER : PTR_ERR(ctrl);

	status = san_consumer_links_setup(pdev);
	अगर (status)
		वापस status;

	data = devm_kzalloc(&pdev->dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->dev = &pdev->dev;
	data->ctrl = ctrl;

	platक्रमm_set_drvdata(pdev, data);

	astatus = acpi_install_address_space_handler(san, ACPI_ADR_SPACE_GSBUS,
						     &san_opreg_handler, शून्य,
						     &data->info);
	अगर (ACPI_FAILURE(astatus))
		वापस -ENXIO;

	status = san_events_रेजिस्टर(pdev);
	अगर (status)
		जाओ err_enable_events;

	status = san_set_rqsg_पूर्णांकerface_device(&pdev->dev);
	अगर (status)
		जाओ err_install_dev;

	acpi_walk_dep_device_list(san);
	वापस 0;

err_install_dev:
	san_events_unरेजिस्टर(pdev);
err_enable_events:
	acpi_हटाओ_address_space_handler(san, ACPI_ADR_SPACE_GSBUS,
					  &san_opreg_handler);
	वापस status;
पूर्ण

अटल पूर्णांक san_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	acpi_handle san = ACPI_HANDLE(&pdev->dev);

	san_set_rqsg_पूर्णांकerface_device(शून्य);
	acpi_हटाओ_address_space_handler(san, ACPI_ADR_SPACE_GSBUS,
					  &san_opreg_handler);
	san_events_unरेजिस्टर(pdev);

	/*
	 * We have unरेजिस्टरed our event sources. Now we need to ensure that
	 * all delayed works they may have spawned are run to completion.
	 */
	flush_scheduled_work();

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा acpi_device_id san_match[] = अणु
	अणु "MSHW0091" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, san_match);

अटल काष्ठा platक्रमm_driver surface_acpi_notअगरy = अणु
	.probe = san_probe,
	.हटाओ = san_हटाओ,
	.driver = अणु
		.name = "surface_acpi_notify",
		.acpi_match_table = san_match,
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(surface_acpi_notअगरy);

MODULE_AUTHOR("Maximilian Luz <luzmaximilian@gmail.com>");
MODULE_DESCRIPTION("Surface ACPI Notify driver for Surface System Aggregator Module");
MODULE_LICENSE("GPL");
