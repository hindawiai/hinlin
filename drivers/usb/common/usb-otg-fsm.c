<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * OTG Finite State Machine from OTG spec
 *
 * Copyright (C) 2007,2008 Freescale Semiconductor, Inc.
 *
 * Author:	Li Yang <LeoLi@मुक्तscale.com>
 *		Jerry Huang <Chang-Ming.Huang@मुक्तscale.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/mutex.h>
#समावेश <linux/delay.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/gadget.h>
#समावेश <linux/usb/otg.h>
#समावेश <linux/usb/otg-fsm.h>

#अगर_घोषित VERBOSE
#घोषणा VDBG(fmt, args...) pr_debug("[%s]  " fmt, \
				 __func__, ## args)
#अन्यथा
#घोषणा VDBG(stuff...)	करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

/* Change USB protocol when there is a protocol change */
अटल पूर्णांक otg_set_protocol(काष्ठा otg_fsm *fsm, पूर्णांक protocol)
अणु
	पूर्णांक ret = 0;

	अगर (fsm->protocol != protocol) अणु
		VDBG("Changing role fsm->protocol= %d; new protocol= %d\n",
			fsm->protocol, protocol);
		/* stop old protocol */
		अगर (fsm->protocol == PROTO_HOST)
			ret = otg_start_host(fsm, 0);
		अन्यथा अगर (fsm->protocol == PROTO_GADGET)
			ret = otg_start_gadget(fsm, 0);
		अगर (ret)
			वापस ret;

		/* start new protocol */
		अगर (protocol == PROTO_HOST)
			ret = otg_start_host(fsm, 1);
		अन्यथा अगर (protocol == PROTO_GADGET)
			ret = otg_start_gadget(fsm, 1);
		अगर (ret)
			वापस ret;

		fsm->protocol = protocol;
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

/* Called when leaving a state.  Do state clean up jobs here */
अटल व्योम otg_leave_state(काष्ठा otg_fsm *fsm, क्रमागत usb_otg_state old_state)
अणु
	चयन (old_state) अणु
	हाल OTG_STATE_B_IDLE:
		otg_del_समयr(fsm, B_SE0_SRP);
		fsm->b_se0_srp = 0;
		fsm->adp_sns = 0;
		fsm->adp_prb = 0;
		अवरोध;
	हाल OTG_STATE_B_SRP_INIT:
		fsm->data_pulse = 0;
		fsm->b_srp_करोne = 0;
		अवरोध;
	हाल OTG_STATE_B_PERIPHERAL:
		अगर (fsm->otg->gadget)
			fsm->otg->gadget->host_request_flag = 0;
		अवरोध;
	हाल OTG_STATE_B_WAIT_ACON:
		otg_del_समयr(fsm, B_ASE0_BRST);
		fsm->b_ase0_brst_पंचांगout = 0;
		अवरोध;
	हाल OTG_STATE_B_HOST:
		अवरोध;
	हाल OTG_STATE_A_IDLE:
		fsm->adp_prb = 0;
		अवरोध;
	हाल OTG_STATE_A_WAIT_VRISE:
		otg_del_समयr(fsm, A_WAIT_VRISE);
		fsm->a_रुको_vrise_पंचांगout = 0;
		अवरोध;
	हाल OTG_STATE_A_WAIT_BCON:
		otg_del_समयr(fsm, A_WAIT_BCON);
		fsm->a_रुको_bcon_पंचांगout = 0;
		अवरोध;
	हाल OTG_STATE_A_HOST:
		otg_del_समयr(fsm, A_WAIT_ENUM);
		अवरोध;
	हाल OTG_STATE_A_SUSPEND:
		otg_del_समयr(fsm, A_AIDL_BDIS);
		fsm->a_aidl_bdis_पंचांगout = 0;
		fsm->a_suspend_req_inf = 0;
		अवरोध;
	हाल OTG_STATE_A_PERIPHERAL:
		otg_del_समयr(fsm, A_BIDL_ADIS);
		fsm->a_bidl_adis_पंचांगout = 0;
		अगर (fsm->otg->gadget)
			fsm->otg->gadget->host_request_flag = 0;
		अवरोध;
	हाल OTG_STATE_A_WAIT_VFALL:
		otg_del_समयr(fsm, A_WAIT_VFALL);
		fsm->a_रुको_vfall_पंचांगout = 0;
		otg_del_समयr(fsm, A_WAIT_VRISE);
		अवरोध;
	हाल OTG_STATE_A_VBUS_ERR:
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम otg_hnp_polling_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा otg_fsm *fsm = container_of(to_delayed_work(work),
				काष्ठा otg_fsm, hnp_polling_work);
	काष्ठा usb_device *udev;
	क्रमागत usb_otg_state state = fsm->otg->state;
	u8 flag;
	पूर्णांक retval;

	अगर (state != OTG_STATE_A_HOST && state != OTG_STATE_B_HOST)
		वापस;

	udev = usb_hub_find_child(fsm->otg->host->root_hub, 1);
	अगर (!udev) अणु
		dev_err(fsm->otg->host->controller,
			"no usb dev connected, can't start HNP polling\n");
		वापस;
	पूर्ण

	*fsm->host_req_flag = 0;
	/* Get host request flag from connected USB device */
	retval = usb_control_msg(udev,
				usb_rcvctrlpipe(udev, 0),
				USB_REQ_GET_STATUS,
				USB_सूची_IN | USB_RECIP_DEVICE,
				0,
				OTG_STS_SELECTOR,
				fsm->host_req_flag,
				1,
				USB_CTRL_GET_TIMEOUT);
	अगर (retval != 1) अणु
		dev_err(&udev->dev, "Get one byte OTG status failed\n");
		वापस;
	पूर्ण

	flag = *fsm->host_req_flag;
	अगर (flag == 0) अणु
		/* Continue HNP polling */
		schedule_delayed_work(&fsm->hnp_polling_work,
					msecs_to_jअगरfies(T_HOST_REQ_POLL));
		वापस;
	पूर्ण अन्यथा अगर (flag != HOST_REQUEST_FLAG) अणु
		dev_err(&udev->dev, "host request flag %d is invalid\n", flag);
		वापस;
	पूर्ण

	/* Host request flag is set */
	अगर (state == OTG_STATE_A_HOST) अणु
		/* Set b_hnp_enable */
		अगर (!fsm->otg->host->b_hnp_enable) अणु
			retval = usb_control_msg(udev,
					usb_sndctrlpipe(udev, 0),
					USB_REQ_SET_FEATURE, 0,
					USB_DEVICE_B_HNP_ENABLE,
					0, शून्य, 0,
					USB_CTRL_SET_TIMEOUT);
			अगर (retval >= 0)
				fsm->otg->host->b_hnp_enable = 1;
		पूर्ण
		fsm->a_bus_req = 0;
	पूर्ण अन्यथा अगर (state == OTG_STATE_B_HOST) अणु
		fsm->b_bus_req = 0;
	पूर्ण

	otg_statemachine(fsm);
पूर्ण

अटल व्योम otg_start_hnp_polling(काष्ठा otg_fsm *fsm)
अणु
	/*
	 * The memory of host_req_flag should be allocated by
	 * controller driver, otherwise, hnp polling is not started.
	 */
	अगर (!fsm->host_req_flag)
		वापस;

	INIT_DELAYED_WORK(&fsm->hnp_polling_work, otg_hnp_polling_work);
	schedule_delayed_work(&fsm->hnp_polling_work,
					msecs_to_jअगरfies(T_HOST_REQ_POLL));
पूर्ण

/* Called when entering a state */
अटल पूर्णांक otg_set_state(काष्ठा otg_fsm *fsm, क्रमागत usb_otg_state new_state)
अणु
	अगर (fsm->otg->state == new_state)
		वापस 0;
	VDBG("Set state: %s\n", usb_otg_state_string(new_state));
	otg_leave_state(fsm, fsm->otg->state);
	चयन (new_state) अणु
	हाल OTG_STATE_B_IDLE:
		otg_drv_vbus(fsm, 0);
		otg_chrg_vbus(fsm, 0);
		otg_loc_conn(fsm, 0);
		otg_loc_sof(fsm, 0);
		/*
		 * Driver is responsible क्रम starting ADP probing
		 * अगर ADP sensing बार out.
		 */
		otg_start_adp_sns(fsm);
		otg_set_protocol(fsm, PROTO_UNDEF);
		otg_add_समयr(fsm, B_SE0_SRP);
		अवरोध;
	हाल OTG_STATE_B_SRP_INIT:
		otg_start_pulse(fsm);
		otg_loc_sof(fsm, 0);
		otg_set_protocol(fsm, PROTO_UNDEF);
		otg_add_समयr(fsm, B_SRP_FAIL);
		अवरोध;
	हाल OTG_STATE_B_PERIPHERAL:
		otg_chrg_vbus(fsm, 0);
		otg_loc_sof(fsm, 0);
		otg_set_protocol(fsm, PROTO_GADGET);
		otg_loc_conn(fsm, 1);
		अवरोध;
	हाल OTG_STATE_B_WAIT_ACON:
		otg_chrg_vbus(fsm, 0);
		otg_loc_conn(fsm, 0);
		otg_loc_sof(fsm, 0);
		otg_set_protocol(fsm, PROTO_HOST);
		otg_add_समयr(fsm, B_ASE0_BRST);
		fsm->a_bus_suspend = 0;
		अवरोध;
	हाल OTG_STATE_B_HOST:
		otg_chrg_vbus(fsm, 0);
		otg_loc_conn(fsm, 0);
		otg_loc_sof(fsm, 1);
		otg_set_protocol(fsm, PROTO_HOST);
		usb_bus_start_क्रमागत(fsm->otg->host,
				fsm->otg->host->otg_port);
		otg_start_hnp_polling(fsm);
		अवरोध;
	हाल OTG_STATE_A_IDLE:
		otg_drv_vbus(fsm, 0);
		otg_chrg_vbus(fsm, 0);
		otg_loc_conn(fsm, 0);
		otg_loc_sof(fsm, 0);
		otg_start_adp_prb(fsm);
		otg_set_protocol(fsm, PROTO_HOST);
		अवरोध;
	हाल OTG_STATE_A_WAIT_VRISE:
		otg_drv_vbus(fsm, 1);
		otg_loc_conn(fsm, 0);
		otg_loc_sof(fsm, 0);
		otg_set_protocol(fsm, PROTO_HOST);
		otg_add_समयr(fsm, A_WAIT_VRISE);
		अवरोध;
	हाल OTG_STATE_A_WAIT_BCON:
		otg_drv_vbus(fsm, 1);
		otg_loc_conn(fsm, 0);
		otg_loc_sof(fsm, 0);
		otg_set_protocol(fsm, PROTO_HOST);
		otg_add_समयr(fsm, A_WAIT_BCON);
		अवरोध;
	हाल OTG_STATE_A_HOST:
		otg_drv_vbus(fsm, 1);
		otg_loc_conn(fsm, 0);
		otg_loc_sof(fsm, 1);
		otg_set_protocol(fsm, PROTO_HOST);
		/*
		 * When HNP is triggered जबतक a_bus_req = 0, a_host will
		 * suspend too fast to complete a_set_b_hnp_en
		 */
		अगर (!fsm->a_bus_req || fsm->a_suspend_req_inf)
			otg_add_समयr(fsm, A_WAIT_ENUM);
		otg_start_hnp_polling(fsm);
		अवरोध;
	हाल OTG_STATE_A_SUSPEND:
		otg_drv_vbus(fsm, 1);
		otg_loc_conn(fsm, 0);
		otg_loc_sof(fsm, 0);
		otg_set_protocol(fsm, PROTO_HOST);
		otg_add_समयr(fsm, A_AIDL_BDIS);

		अवरोध;
	हाल OTG_STATE_A_PERIPHERAL:
		otg_loc_sof(fsm, 0);
		otg_set_protocol(fsm, PROTO_GADGET);
		otg_drv_vbus(fsm, 1);
		otg_loc_conn(fsm, 1);
		otg_add_समयr(fsm, A_BIDL_ADIS);
		अवरोध;
	हाल OTG_STATE_A_WAIT_VFALL:
		otg_drv_vbus(fsm, 0);
		otg_loc_conn(fsm, 0);
		otg_loc_sof(fsm, 0);
		otg_set_protocol(fsm, PROTO_HOST);
		otg_add_समयr(fsm, A_WAIT_VFALL);
		अवरोध;
	हाल OTG_STATE_A_VBUS_ERR:
		otg_drv_vbus(fsm, 0);
		otg_loc_conn(fsm, 0);
		otg_loc_sof(fsm, 0);
		otg_set_protocol(fsm, PROTO_UNDEF);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	fsm->otg->state = new_state;
	fsm->state_changed = 1;
	वापस 0;
पूर्ण

/* State change judgement */
पूर्णांक otg_statemachine(काष्ठा otg_fsm *fsm)
अणु
	क्रमागत usb_otg_state state;

	mutex_lock(&fsm->lock);

	state = fsm->otg->state;
	fsm->state_changed = 0;
	/* State machine state change judgement */

	चयन (state) अणु
	हाल OTG_STATE_UNDEFINED:
		VDBG("fsm->id = %d\n", fsm->id);
		अगर (fsm->id)
			otg_set_state(fsm, OTG_STATE_B_IDLE);
		अन्यथा
			otg_set_state(fsm, OTG_STATE_A_IDLE);
		अवरोध;
	हाल OTG_STATE_B_IDLE:
		अगर (!fsm->id)
			otg_set_state(fsm, OTG_STATE_A_IDLE);
		अन्यथा अगर (fsm->b_sess_vld && fsm->otg->gadget)
			otg_set_state(fsm, OTG_STATE_B_PERIPHERAL);
		अन्यथा अगर ((fsm->b_bus_req || fsm->adp_change || fsm->घातer_up) &&
				fsm->b_ssend_srp && fsm->b_se0_srp)
			otg_set_state(fsm, OTG_STATE_B_SRP_INIT);
		अवरोध;
	हाल OTG_STATE_B_SRP_INIT:
		अगर (!fsm->id || fsm->b_srp_करोne)
			otg_set_state(fsm, OTG_STATE_B_IDLE);
		अवरोध;
	हाल OTG_STATE_B_PERIPHERAL:
		अगर (!fsm->id || !fsm->b_sess_vld)
			otg_set_state(fsm, OTG_STATE_B_IDLE);
		अन्यथा अगर (fsm->b_bus_req && fsm->otg->
				gadget->b_hnp_enable && fsm->a_bus_suspend)
			otg_set_state(fsm, OTG_STATE_B_WAIT_ACON);
		अवरोध;
	हाल OTG_STATE_B_WAIT_ACON:
		अगर (fsm->a_conn)
			otg_set_state(fsm, OTG_STATE_B_HOST);
		अन्यथा अगर (!fsm->id || !fsm->b_sess_vld)
			otg_set_state(fsm, OTG_STATE_B_IDLE);
		अन्यथा अगर (fsm->a_bus_resume || fsm->b_ase0_brst_पंचांगout) अणु
			fsm->b_ase0_brst_पंचांगout = 0;
			otg_set_state(fsm, OTG_STATE_B_PERIPHERAL);
		पूर्ण
		अवरोध;
	हाल OTG_STATE_B_HOST:
		अगर (!fsm->id || !fsm->b_sess_vld)
			otg_set_state(fsm, OTG_STATE_B_IDLE);
		अन्यथा अगर (!fsm->b_bus_req || !fsm->a_conn || fsm->test_device)
			otg_set_state(fsm, OTG_STATE_B_PERIPHERAL);
		अवरोध;
	हाल OTG_STATE_A_IDLE:
		अगर (fsm->id)
			otg_set_state(fsm, OTG_STATE_B_IDLE);
		अन्यथा अगर (!fsm->a_bus_drop && (fsm->a_bus_req ||
			  fsm->a_srp_det || fsm->adp_change || fsm->घातer_up))
			otg_set_state(fsm, OTG_STATE_A_WAIT_VRISE);
		अवरोध;
	हाल OTG_STATE_A_WAIT_VRISE:
		अगर (fsm->a_vbus_vld)
			otg_set_state(fsm, OTG_STATE_A_WAIT_BCON);
		अन्यथा अगर (fsm->id || fsm->a_bus_drop ||
				fsm->a_रुको_vrise_पंचांगout)
			otg_set_state(fsm, OTG_STATE_A_WAIT_VFALL);
		अवरोध;
	हाल OTG_STATE_A_WAIT_BCON:
		अगर (!fsm->a_vbus_vld)
			otg_set_state(fsm, OTG_STATE_A_VBUS_ERR);
		अन्यथा अगर (fsm->b_conn)
			otg_set_state(fsm, OTG_STATE_A_HOST);
		अन्यथा अगर (fsm->id || fsm->a_bus_drop || fsm->a_रुको_bcon_पंचांगout)
			otg_set_state(fsm, OTG_STATE_A_WAIT_VFALL);
		अवरोध;
	हाल OTG_STATE_A_HOST:
		अगर (fsm->id || fsm->a_bus_drop)
			otg_set_state(fsm, OTG_STATE_A_WAIT_VFALL);
		अन्यथा अगर ((!fsm->a_bus_req || fsm->a_suspend_req_inf) &&
				fsm->otg->host->b_hnp_enable)
			otg_set_state(fsm, OTG_STATE_A_SUSPEND);
		अन्यथा अगर (!fsm->b_conn)
			otg_set_state(fsm, OTG_STATE_A_WAIT_BCON);
		अन्यथा अगर (!fsm->a_vbus_vld)
			otg_set_state(fsm, OTG_STATE_A_VBUS_ERR);
		अवरोध;
	हाल OTG_STATE_A_SUSPEND:
		अगर (!fsm->b_conn && fsm->otg->host->b_hnp_enable)
			otg_set_state(fsm, OTG_STATE_A_PERIPHERAL);
		अन्यथा अगर (!fsm->b_conn && !fsm->otg->host->b_hnp_enable)
			otg_set_state(fsm, OTG_STATE_A_WAIT_BCON);
		अन्यथा अगर (fsm->a_bus_req || fsm->b_bus_resume)
			otg_set_state(fsm, OTG_STATE_A_HOST);
		अन्यथा अगर (fsm->id || fsm->a_bus_drop || fsm->a_aidl_bdis_पंचांगout)
			otg_set_state(fsm, OTG_STATE_A_WAIT_VFALL);
		अन्यथा अगर (!fsm->a_vbus_vld)
			otg_set_state(fsm, OTG_STATE_A_VBUS_ERR);
		अवरोध;
	हाल OTG_STATE_A_PERIPHERAL:
		अगर (fsm->id || fsm->a_bus_drop)
			otg_set_state(fsm, OTG_STATE_A_WAIT_VFALL);
		अन्यथा अगर (fsm->a_bidl_adis_पंचांगout || fsm->b_bus_suspend)
			otg_set_state(fsm, OTG_STATE_A_WAIT_BCON);
		अन्यथा अगर (!fsm->a_vbus_vld)
			otg_set_state(fsm, OTG_STATE_A_VBUS_ERR);
		अवरोध;
	हाल OTG_STATE_A_WAIT_VFALL:
		अगर (fsm->a_रुको_vfall_पंचांगout)
			otg_set_state(fsm, OTG_STATE_A_IDLE);
		अवरोध;
	हाल OTG_STATE_A_VBUS_ERR:
		अगर (fsm->id || fsm->a_bus_drop || fsm->a_clr_err)
			otg_set_state(fsm, OTG_STATE_A_WAIT_VFALL);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	mutex_unlock(&fsm->lock);

	VDBG("quit statemachine, changed = %d\n", fsm->state_changed);
	वापस fsm->state_changed;
पूर्ण
EXPORT_SYMBOL_GPL(otg_statemachine);
MODULE_LICENSE("GPL");
