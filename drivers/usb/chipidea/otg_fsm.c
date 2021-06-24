<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * otg_fsm.c - ChipIdea USB IP core OTG FSM driver
 *
 * Copyright (C) 2014 Freescale Semiconductor, Inc.
 *
 * Author: Jun Li
 */

/*
 * This file मुख्यly handles OTG fsm, it includes OTG fsm operations
 * क्रम HNP and SRP.
 *
 * TODO List
 * - ADP
 * - OTG test device
 */

#समावेश <linux/usb/otg.h>
#समावेश <linux/usb/gadget.h>
#समावेश <linux/usb/hcd.h>
#समावेश <linux/usb/chipidea.h>
#समावेश <linux/regulator/consumer.h>

#समावेश "ci.h"
#समावेश "bits.h"
#समावेश "otg.h"
#समावेश "otg_fsm.h"

/* Add क्रम otg: पूर्णांकeract with user space app */
अटल sमाप_प्रकार
a_bus_req_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	अक्षर		*next;
	अचिन्हित	size, t;
	काष्ठा ci_hdrc	*ci = dev_get_drvdata(dev);

	next = buf;
	size = PAGE_SIZE;
	t = scnम_लिखो(next, size, "%d\n", ci->fsm.a_bus_req);
	size -= t;
	next += t;

	वापस PAGE_SIZE - size;
पूर्ण

अटल sमाप_प्रकार
a_bus_req_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
					स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा ci_hdrc *ci = dev_get_drvdata(dev);

	अगर (count > 2)
		वापस -1;

	mutex_lock(&ci->fsm.lock);
	अगर (buf[0] == '0') अणु
		ci->fsm.a_bus_req = 0;
	पूर्ण अन्यथा अगर (buf[0] == '1') अणु
		/* If a_bus_drop is TRUE, a_bus_req can't be set */
		अगर (ci->fsm.a_bus_drop) अणु
			mutex_unlock(&ci->fsm.lock);
			वापस count;
		पूर्ण
		ci->fsm.a_bus_req = 1;
		अगर (ci->fsm.otg->state == OTG_STATE_A_PERIPHERAL) अणु
			ci->gadget.host_request_flag = 1;
			mutex_unlock(&ci->fsm.lock);
			वापस count;
		पूर्ण
	पूर्ण

	ci_otg_queue_work(ci);
	mutex_unlock(&ci->fsm.lock);

	वापस count;
पूर्ण
अटल DEVICE_ATTR_RW(a_bus_req);

अटल sमाप_प्रकार
a_bus_drop_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	अक्षर		*next;
	अचिन्हित	size, t;
	काष्ठा ci_hdrc	*ci = dev_get_drvdata(dev);

	next = buf;
	size = PAGE_SIZE;
	t = scnम_लिखो(next, size, "%d\n", ci->fsm.a_bus_drop);
	size -= t;
	next += t;

	वापस PAGE_SIZE - size;
पूर्ण

अटल sमाप_प्रकार
a_bus_drop_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
					स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा ci_hdrc	*ci = dev_get_drvdata(dev);

	अगर (count > 2)
		वापस -1;

	mutex_lock(&ci->fsm.lock);
	अगर (buf[0] == '0') अणु
		ci->fsm.a_bus_drop = 0;
	पूर्ण अन्यथा अगर (buf[0] == '1') अणु
		ci->fsm.a_bus_drop = 1;
		ci->fsm.a_bus_req = 0;
	पूर्ण

	ci_otg_queue_work(ci);
	mutex_unlock(&ci->fsm.lock);

	वापस count;
पूर्ण
अटल DEVICE_ATTR_RW(a_bus_drop);

अटल sमाप_प्रकार
b_bus_req_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	अक्षर		*next;
	अचिन्हित	size, t;
	काष्ठा ci_hdrc	*ci = dev_get_drvdata(dev);

	next = buf;
	size = PAGE_SIZE;
	t = scnम_लिखो(next, size, "%d\n", ci->fsm.b_bus_req);
	size -= t;
	next += t;

	वापस PAGE_SIZE - size;
पूर्ण

अटल sमाप_प्रकार
b_bus_req_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
					स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा ci_hdrc	*ci = dev_get_drvdata(dev);

	अगर (count > 2)
		वापस -1;

	mutex_lock(&ci->fsm.lock);
	अगर (buf[0] == '0')
		ci->fsm.b_bus_req = 0;
	अन्यथा अगर (buf[0] == '1') अणु
		ci->fsm.b_bus_req = 1;
		अगर (ci->fsm.otg->state == OTG_STATE_B_PERIPHERAL) अणु
			ci->gadget.host_request_flag = 1;
			mutex_unlock(&ci->fsm.lock);
			वापस count;
		पूर्ण
	पूर्ण

	ci_otg_queue_work(ci);
	mutex_unlock(&ci->fsm.lock);

	वापस count;
पूर्ण
अटल DEVICE_ATTR_RW(b_bus_req);

अटल sमाप_प्रकार
a_clr_err_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
					स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा ci_hdrc	*ci = dev_get_drvdata(dev);

	अगर (count > 2)
		वापस -1;

	mutex_lock(&ci->fsm.lock);
	अगर (buf[0] == '1')
		ci->fsm.a_clr_err = 1;

	ci_otg_queue_work(ci);
	mutex_unlock(&ci->fsm.lock);

	वापस count;
पूर्ण
अटल DEVICE_ATTR_WO(a_clr_err);

अटल काष्ठा attribute *inमाला_दो_attrs[] = अणु
	&dev_attr_a_bus_req.attr,
	&dev_attr_a_bus_drop.attr,
	&dev_attr_b_bus_req.attr,
	&dev_attr_a_clr_err.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group inमाला_दो_attr_group = अणु
	.name = "inputs",
	.attrs = inमाला_दो_attrs,
पूर्ण;

/*
 * Keep this list in the same order as समयrs indexed
 * by क्रमागत otg_fsm_समयr in include/linux/usb/otg-fsm.h
 */
अटल अचिन्हित otg_समयr_ms[] = अणु
	TA_WAIT_VRISE,
	TA_WAIT_VFALL,
	TA_WAIT_BCON,
	TA_AIDL_BDIS,
	TB_ASE0_BRST,
	TA_BIDL_ADIS,
	TB_AIDL_BDIS,
	TB_SE0_SRP,
	TB_SRP_FAIL,
	0,
	TB_DATA_PLS,
	TB_SSEND_SRP,
पूर्ण;

/*
 * Add समयr to active समयr list
 */
अटल व्योम ci_otg_add_समयr(काष्ठा ci_hdrc *ci, क्रमागत otg_fsm_समयr t)
अणु
	अचिन्हित दीर्घ flags, समयr_sec, समयr_nsec;

	अगर (t >= NUM_OTG_FSM_TIMERS)
		वापस;

	spin_lock_irqsave(&ci->lock, flags);
	समयr_sec = otg_समयr_ms[t] / MSEC_PER_SEC;
	समयr_nsec = (otg_समयr_ms[t] % MSEC_PER_SEC) * NSEC_PER_MSEC;
	ci->hr_समयouts[t] = kसमय_add(kसमय_get(),
				kसमय_set(समयr_sec, समयr_nsec));
	ci->enabled_otg_समयr_bits |= (1 << t);
	अगर ((ci->next_otg_समयr == NUM_OTG_FSM_TIMERS) ||
			kसमय_after(ci->hr_समयouts[ci->next_otg_समयr],
						ci->hr_समयouts[t])) अणु
			ci->next_otg_समयr = t;
			hrसमयr_start_range_ns(&ci->otg_fsm_hrसमयr,
					ci->hr_समयouts[t], NSEC_PER_MSEC,
							HRTIMER_MODE_ABS);
	पूर्ण
	spin_unlock_irqrestore(&ci->lock, flags);
पूर्ण

/*
 * Remove समयr from active समयr list
 */
अटल व्योम ci_otg_del_समयr(काष्ठा ci_hdrc *ci, क्रमागत otg_fsm_समयr t)
अणु
	अचिन्हित दीर्घ flags, enabled_समयr_bits;
	क्रमागत otg_fsm_समयr cur_समयr, next_समयr = NUM_OTG_FSM_TIMERS;

	अगर ((t >= NUM_OTG_FSM_TIMERS) ||
			!(ci->enabled_otg_समयr_bits & (1 << t)))
		वापस;

	spin_lock_irqsave(&ci->lock, flags);
	ci->enabled_otg_समयr_bits &= ~(1 << t);
	अगर (ci->next_otg_समयr == t) अणु
		अगर (ci->enabled_otg_समयr_bits == 0) अणु
			/* No enabled समयrs after delete it */
			hrसमयr_cancel(&ci->otg_fsm_hrसमयr);
			ci->next_otg_समयr = NUM_OTG_FSM_TIMERS;
		पूर्ण अन्यथा अणु
			/* Find the next समयr */
			enabled_समयr_bits = ci->enabled_otg_समयr_bits;
			क्रम_each_set_bit(cur_समयr, &enabled_समयr_bits,
							NUM_OTG_FSM_TIMERS) अणु
				अगर ((next_समयr == NUM_OTG_FSM_TIMERS) ||
					kसमय_beक्रमe(ci->hr_समयouts[next_समयr],
					 ci->hr_समयouts[cur_समयr]))
					next_समयr = cur_समयr;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (next_समयr != NUM_OTG_FSM_TIMERS) अणु
		ci->next_otg_समयr = next_समयr;
		hrसमयr_start_range_ns(&ci->otg_fsm_hrसमयr,
			ci->hr_समयouts[next_समयr], NSEC_PER_MSEC,
							HRTIMER_MODE_ABS);
	पूर्ण
	spin_unlock_irqrestore(&ci->lock, flags);
पूर्ण

/* OTG FSM समयr handlers */
अटल पूर्णांक a_रुको_vrise_पंचांगout(काष्ठा ci_hdrc *ci)
अणु
	ci->fsm.a_रुको_vrise_पंचांगout = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक a_रुको_vfall_पंचांगout(काष्ठा ci_hdrc *ci)
अणु
	ci->fsm.a_रुको_vfall_पंचांगout = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक a_रुको_bcon_पंचांगout(काष्ठा ci_hdrc *ci)
अणु
	ci->fsm.a_रुको_bcon_पंचांगout = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक a_aidl_bdis_पंचांगout(काष्ठा ci_hdrc *ci)
अणु
	ci->fsm.a_aidl_bdis_पंचांगout = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक b_ase0_brst_पंचांगout(काष्ठा ci_hdrc *ci)
अणु
	ci->fsm.b_ase0_brst_पंचांगout = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक a_bidl_adis_पंचांगout(काष्ठा ci_hdrc *ci)
अणु
	ci->fsm.a_bidl_adis_पंचांगout = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक b_aidl_bdis_पंचांगout(काष्ठा ci_hdrc *ci)
अणु
	ci->fsm.a_bus_suspend = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक b_se0_srp_पंचांगout(काष्ठा ci_hdrc *ci)
अणु
	ci->fsm.b_se0_srp = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक b_srp_fail_पंचांगout(काष्ठा ci_hdrc *ci)
अणु
	ci->fsm.b_srp_करोne = 1;
	वापस 1;
पूर्ण

अटल पूर्णांक b_data_pls_पंचांगout(काष्ठा ci_hdrc *ci)
अणु
	ci->fsm.b_srp_करोne = 1;
	ci->fsm.b_bus_req = 0;
	अगर (ci->fsm.घातer_up)
		ci->fsm.घातer_up = 0;
	hw_ग_लिखो_otgsc(ci, OTGSC_HABA, 0);
	pm_runसमय_put(ci->dev);
	वापस 0;
पूर्ण

अटल पूर्णांक b_ssend_srp_पंचांगout(काष्ठा ci_hdrc *ci)
अणु
	ci->fsm.b_ssend_srp = 1;
	/* only vbus fall below B_sess_vld in b_idle state */
	अगर (ci->fsm.otg->state == OTG_STATE_B_IDLE)
		वापस 0;
	अन्यथा
		वापस 1;
पूर्ण

/*
 * Keep this list in the same order as समयrs indexed
 * by क्रमागत otg_fsm_समयr in include/linux/usb/otg-fsm.h
 */
अटल पूर्णांक (*otg_समयr_handlers[])(काष्ठा ci_hdrc *) = अणु
	a_रुको_vrise_पंचांगout,	/* A_WAIT_VRISE */
	a_रुको_vfall_पंचांगout,	/* A_WAIT_VFALL */
	a_रुको_bcon_पंचांगout,	/* A_WAIT_BCON */
	a_aidl_bdis_पंचांगout,	/* A_AIDL_BDIS */
	b_ase0_brst_पंचांगout,	/* B_ASE0_BRST */
	a_bidl_adis_पंचांगout,	/* A_BIDL_ADIS */
	b_aidl_bdis_पंचांगout,	/* B_AIDL_BDIS */
	b_se0_srp_पंचांगout,	/* B_SE0_SRP */
	b_srp_fail_पंचांगout,	/* B_SRP_FAIL */
	शून्य,			/* A_WAIT_ENUM */
	b_data_pls_पंचांगout,	/* B_DATA_PLS */
	b_ssend_srp_पंचांगout,	/* B_SSEND_SRP */
पूर्ण;

/*
 * Enable the next nearest enabled समयr अगर have
 */
अटल क्रमागत hrसमयr_restart ci_otg_hrसमयr_func(काष्ठा hrसमयr *t)
अणु
	काष्ठा ci_hdrc *ci = container_of(t, काष्ठा ci_hdrc, otg_fsm_hrसमयr);
	kसमय_प्रकार	now, *समयout;
	अचिन्हित दीर्घ   enabled_समयr_bits;
	अचिन्हित दीर्घ   flags;
	क्रमागत otg_fsm_समयr cur_समयr, next_समयr = NUM_OTG_FSM_TIMERS;
	पूर्णांक ret = -EINVAL;

	spin_lock_irqsave(&ci->lock, flags);
	enabled_समयr_bits = ci->enabled_otg_समयr_bits;
	ci->next_otg_समयr = NUM_OTG_FSM_TIMERS;

	now = kसमय_get();
	क्रम_each_set_bit(cur_समयr, &enabled_समयr_bits, NUM_OTG_FSM_TIMERS) अणु
		अगर (kसमय_compare(now, ci->hr_समयouts[cur_समयr]) >= 0) अणु
			ci->enabled_otg_समयr_bits &= ~(1 << cur_समयr);
			अगर (otg_समयr_handlers[cur_समयr])
				ret = otg_समयr_handlers[cur_समयr](ci);
		पूर्ण अन्यथा अणु
			अगर ((next_समयr == NUM_OTG_FSM_TIMERS) ||
				kसमय_beक्रमe(ci->hr_समयouts[cur_समयr],
					ci->hr_समयouts[next_समयr]))
				next_समयr = cur_समयr;
		पूर्ण
	पूर्ण
	/* Enable the next nearest समयr */
	अगर (next_समयr < NUM_OTG_FSM_TIMERS) अणु
		समयout = &ci->hr_समयouts[next_समयr];
		hrसमयr_start_range_ns(&ci->otg_fsm_hrसमयr, *समयout,
					NSEC_PER_MSEC, HRTIMER_MODE_ABS);
		ci->next_otg_समयr = next_समयr;
	पूर्ण
	spin_unlock_irqrestore(&ci->lock, flags);

	अगर (!ret)
		ci_otg_queue_work(ci);

	वापस HRTIMER_NORESTART;
पूर्ण

/* Initialize समयrs */
अटल पूर्णांक ci_otg_init_समयrs(काष्ठा ci_hdrc *ci)
अणु
	hrसमयr_init(&ci->otg_fsm_hrसमयr, CLOCK_MONOTONIC, HRTIMER_MODE_ABS);
	ci->otg_fsm_hrसमयr.function = ci_otg_hrसमयr_func;

	वापस 0;
पूर्ण

/* -------------------------------------------------------------*/
/* Operations that will be called from OTG Finite State Machine */
/* -------------------------------------------------------------*/
अटल व्योम ci_otg_fsm_add_समयr(काष्ठा otg_fsm *fsm, क्रमागत otg_fsm_समयr t)
अणु
	काष्ठा ci_hdrc	*ci = container_of(fsm, काष्ठा ci_hdrc, fsm);

	अगर (t < NUM_OTG_FSM_TIMERS)
		ci_otg_add_समयr(ci, t);
	वापस;
पूर्ण

अटल व्योम ci_otg_fsm_del_समयr(काष्ठा otg_fsm *fsm, क्रमागत otg_fsm_समयr t)
अणु
	काष्ठा ci_hdrc	*ci = container_of(fsm, काष्ठा ci_hdrc, fsm);

	अगर (t < NUM_OTG_FSM_TIMERS)
		ci_otg_del_समयr(ci, t);
	वापस;
पूर्ण

/*
 * A-device drive vbus: turn on vbus regulator and enable port घातer
 * Data pulse irq should be disabled जबतक vbus is on.
 */
अटल व्योम ci_otg_drv_vbus(काष्ठा otg_fsm *fsm, पूर्णांक on)
अणु
	पूर्णांक ret;
	काष्ठा ci_hdrc	*ci = container_of(fsm, काष्ठा ci_hdrc, fsm);

	अगर (on) अणु
		/* Enable घातer घातer */
		hw_ग_लिखो(ci, OP_PORTSC, PORTSC_W1C_BITS | PORTSC_PP,
							PORTSC_PP);
		अगर (ci->platdata->reg_vbus) अणु
			ret = regulator_enable(ci->platdata->reg_vbus);
			अगर (ret) अणु
				dev_err(ci->dev,
				"Failed to enable vbus regulator, ret=%d\n",
				ret);
				वापस;
			पूर्ण
		पूर्ण
		/* Disable data pulse irq */
		hw_ग_लिखो_otgsc(ci, OTGSC_DPIE, 0);

		fsm->a_srp_det = 0;
		fsm->घातer_up = 0;
	पूर्ण अन्यथा अणु
		अगर (ci->platdata->reg_vbus)
			regulator_disable(ci->platdata->reg_vbus);

		fsm->a_bus_drop = 1;
		fsm->a_bus_req = 0;
	पूर्ण
पूर्ण

/*
 * Control data line by Run Stop bit.
 */
अटल व्योम ci_otg_loc_conn(काष्ठा otg_fsm *fsm, पूर्णांक on)
अणु
	काष्ठा ci_hdrc	*ci = container_of(fsm, काष्ठा ci_hdrc, fsm);

	अगर (on)
		hw_ग_लिखो(ci, OP_USBCMD, USBCMD_RS, USBCMD_RS);
	अन्यथा
		hw_ग_लिखो(ci, OP_USBCMD, USBCMD_RS, 0);
पूर्ण

/*
 * Generate SOF by host.
 * In host mode, controller will स्वतःmatically send SOF.
 * Suspend will block the data on the port.
 *
 * This is controlled through usbcore by usb स्वतःsuspend,
 * so the usb device class driver need support स्वतःsuspend,
 * otherwise the bus suspend will not happen.
 */
अटल व्योम ci_otg_loc_sof(काष्ठा otg_fsm *fsm, पूर्णांक on)
अणु
	काष्ठा usb_device *udev;

	अगर (!fsm->otg->host)
		वापस;

	udev = usb_hub_find_child(fsm->otg->host->root_hub, 1);
	अगर (!udev)
		वापस;

	अगर (on) अणु
		usb_disable_स्वतःsuspend(udev);
	पूर्ण अन्यथा अणु
		pm_runसमय_set_स्वतःsuspend_delay(&udev->dev, 0);
		usb_enable_स्वतःsuspend(udev);
	पूर्ण
पूर्ण

/*
 * Start SRP pulsing by data-line pulsing,
 * no v-bus pulsing followed
 */
अटल व्योम ci_otg_start_pulse(काष्ठा otg_fsm *fsm)
अणु
	काष्ठा ci_hdrc	*ci = container_of(fsm, काष्ठा ci_hdrc, fsm);

	/* Hardware Assistant Data pulse */
	hw_ग_लिखो_otgsc(ci, OTGSC_HADP, OTGSC_HADP);

	pm_runसमय_get(ci->dev);
	ci_otg_add_समयr(ci, B_DATA_PLS);
पूर्ण

अटल पूर्णांक ci_otg_start_host(काष्ठा otg_fsm *fsm, पूर्णांक on)
अणु
	काष्ठा ci_hdrc	*ci = container_of(fsm, काष्ठा ci_hdrc, fsm);

	अगर (on) अणु
		ci_role_stop(ci);
		ci_role_start(ci, CI_ROLE_HOST);
	पूर्ण अन्यथा अणु
		ci_role_stop(ci);
		ci_role_start(ci, CI_ROLE_GADGET);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ci_otg_start_gadget(काष्ठा otg_fsm *fsm, पूर्णांक on)
अणु
	काष्ठा ci_hdrc	*ci = container_of(fsm, काष्ठा ci_hdrc, fsm);

	अगर (on)
		usb_gadget_vbus_connect(&ci->gadget);
	अन्यथा
		usb_gadget_vbus_disconnect(&ci->gadget);

	वापस 0;
पूर्ण

अटल काष्ठा otg_fsm_ops ci_otg_ops = अणु
	.drv_vbus = ci_otg_drv_vbus,
	.loc_conn = ci_otg_loc_conn,
	.loc_sof = ci_otg_loc_sof,
	.start_pulse = ci_otg_start_pulse,
	.add_समयr = ci_otg_fsm_add_समयr,
	.del_समयr = ci_otg_fsm_del_समयr,
	.start_host = ci_otg_start_host,
	.start_gadget = ci_otg_start_gadget,
पूर्ण;

पूर्णांक ci_otg_fsm_work(काष्ठा ci_hdrc *ci)
अणु
	/*
	 * Don't करो fsm transition क्रम B device
	 * when there is no gadget class driver
	 */
	अगर (ci->fsm.id && !(ci->driver) &&
		ci->fsm.otg->state < OTG_STATE_A_IDLE)
		वापस 0;

	pm_runसमय_get_sync(ci->dev);
	अगर (otg_statemachine(&ci->fsm)) अणु
		अगर (ci->fsm.otg->state == OTG_STATE_A_IDLE) अणु
			/*
			 * Further state change क्रम हालs:
			 * a_idle to b_idle; or
			 * a_idle to a_रुको_vrise due to ID change(1->0), so
			 * B-dev becomes A-dev can try to start new session
			 * consequently; or
			 * a_idle to a_रुको_vrise when घातer up
			 */
			अगर ((ci->fsm.id) || (ci->id_event) ||
						(ci->fsm.घातer_up)) अणु
				ci_otg_queue_work(ci);
			पूर्ण अन्यथा अणु
				/* Enable data pulse irq */
				hw_ग_लिखो(ci, OP_PORTSC, PORTSC_W1C_BITS |
								PORTSC_PP, 0);
				hw_ग_लिखो_otgsc(ci, OTGSC_DPIS, OTGSC_DPIS);
				hw_ग_लिखो_otgsc(ci, OTGSC_DPIE, OTGSC_DPIE);
			पूर्ण
			अगर (ci->id_event)
				ci->id_event = false;
		पूर्ण अन्यथा अगर (ci->fsm.otg->state == OTG_STATE_B_IDLE) अणु
			अगर (ci->fsm.b_sess_vld) अणु
				ci->fsm.घातer_up = 0;
				/*
				 * Further transite to b_periphearl state
				 * when रेजिस्टर gadget driver with vbus on
				 */
				ci_otg_queue_work(ci);
			पूर्ण
		पूर्ण अन्यथा अगर (ci->fsm.otg->state == OTG_STATE_A_HOST) अणु
			pm_runसमय_mark_last_busy(ci->dev);
			pm_runसमय_put_स्वतःsuspend(ci->dev);
			वापस 0;
		पूर्ण
	पूर्ण
	pm_runसमय_put_sync(ci->dev);
	वापस 0;
पूर्ण

/*
 * Update fsm variables in each state अगर catching expected पूर्णांकerrupts,
 * called by otg fsm isr.
 */
अटल व्योम ci_otg_fsm_event(काष्ठा ci_hdrc *ci)
अणु
	u32 पूर्णांकr_sts, otg_bsess_vld, port_conn;
	काष्ठा otg_fsm *fsm = &ci->fsm;

	पूर्णांकr_sts = hw_पढ़ो_पूर्णांकr_status(ci);
	otg_bsess_vld = hw_पढ़ो_otgsc(ci, OTGSC_BSV);
	port_conn = hw_पढ़ो(ci, OP_PORTSC, PORTSC_CCS);

	चयन (ci->fsm.otg->state) अणु
	हाल OTG_STATE_A_WAIT_BCON:
		अगर (port_conn) अणु
			fsm->b_conn = 1;
			fsm->a_bus_req = 1;
			ci_otg_queue_work(ci);
		पूर्ण
		अवरोध;
	हाल OTG_STATE_B_IDLE:
		अगर (otg_bsess_vld && (पूर्णांकr_sts & USBi_PCI) && port_conn) अणु
			fsm->b_sess_vld = 1;
			ci_otg_queue_work(ci);
		पूर्ण
		अवरोध;
	हाल OTG_STATE_B_PERIPHERAL:
		अगर ((पूर्णांकr_sts & USBi_SLI) && port_conn && otg_bsess_vld) अणु
			ci_otg_add_समयr(ci, B_AIDL_BDIS);
		पूर्ण अन्यथा अगर (पूर्णांकr_sts & USBi_PCI) अणु
			ci_otg_del_समयr(ci, B_AIDL_BDIS);
			अगर (fsm->a_bus_suspend == 1)
				fsm->a_bus_suspend = 0;
		पूर्ण
		अवरोध;
	हाल OTG_STATE_B_HOST:
		अगर ((पूर्णांकr_sts & USBi_PCI) && !port_conn) अणु
			fsm->a_conn = 0;
			fsm->b_bus_req = 0;
			ci_otg_queue_work(ci);
		पूर्ण
		अवरोध;
	हाल OTG_STATE_A_PERIPHERAL:
		अगर (पूर्णांकr_sts & USBi_SLI) अणु
			 fsm->b_bus_suspend = 1;
			/*
			 * Init a समयr to know how दीर्घ this suspend
			 * will जारी, अगर समय out, indicates B no दीर्घer
			 * wants to be host role
			 */
			 ci_otg_add_समयr(ci, A_BIDL_ADIS);
		पूर्ण

		अगर (पूर्णांकr_sts & USBi_URI)
			ci_otg_del_समयr(ci, A_BIDL_ADIS);

		अगर (पूर्णांकr_sts & USBi_PCI) अणु
			अगर (fsm->b_bus_suspend == 1) अणु
				ci_otg_del_समयr(ci, A_BIDL_ADIS);
				fsm->b_bus_suspend = 0;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल OTG_STATE_A_SUSPEND:
		अगर ((पूर्णांकr_sts & USBi_PCI) && !port_conn) अणु
			fsm->b_conn = 0;

			/* अगर gadget driver is binded */
			अगर (ci->driver) अणु
				/* A device to be peripheral mode */
				ci->gadget.is_a_peripheral = 1;
			पूर्ण
			ci_otg_queue_work(ci);
		पूर्ण
		अवरोध;
	हाल OTG_STATE_A_HOST:
		अगर ((पूर्णांकr_sts & USBi_PCI) && !port_conn) अणु
			fsm->b_conn = 0;
			ci_otg_queue_work(ci);
		पूर्ण
		अवरोध;
	हाल OTG_STATE_B_WAIT_ACON:
		अगर ((पूर्णांकr_sts & USBi_PCI) && port_conn) अणु
			fsm->a_conn = 1;
			ci_otg_queue_work(ci);
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/*
 * ci_otg_irq - otg fsm related irq handling
 * and also update otg fsm variable by monitoring usb host and udc
 * state change पूर्णांकerrupts.
 * @ci: ci_hdrc
 */
irqवापस_t ci_otg_fsm_irq(काष्ठा ci_hdrc *ci)
अणु
	irqवापस_t retval =  IRQ_NONE;
	u32 otgsc, otg_पूर्णांक_src = 0;
	काष्ठा otg_fsm *fsm = &ci->fsm;

	otgsc = hw_पढ़ो_otgsc(ci, ~0);
	otg_पूर्णांक_src = otgsc & OTGSC_INT_STATUS_BITS & (otgsc >> 8);
	fsm->id = (otgsc & OTGSC_ID) ? 1 : 0;

	अगर (otg_पूर्णांक_src) अणु
		अगर (otg_पूर्णांक_src & OTGSC_DPIS) अणु
			hw_ग_लिखो_otgsc(ci, OTGSC_DPIS, OTGSC_DPIS);
			fsm->a_srp_det = 1;
			fsm->a_bus_drop = 0;
		पूर्ण अन्यथा अगर (otg_पूर्णांक_src & OTGSC_IDIS) अणु
			hw_ग_लिखो_otgsc(ci, OTGSC_IDIS, OTGSC_IDIS);
			अगर (fsm->id == 0) अणु
				fsm->a_bus_drop = 0;
				fsm->a_bus_req = 1;
				ci->id_event = true;
			पूर्ण
		पूर्ण अन्यथा अगर (otg_पूर्णांक_src & OTGSC_BSVIS) अणु
			hw_ग_लिखो_otgsc(ci, OTGSC_BSVIS, OTGSC_BSVIS);
			अगर (otgsc & OTGSC_BSV) अणु
				fsm->b_sess_vld = 1;
				ci_otg_del_समयr(ci, B_SSEND_SRP);
				ci_otg_del_समयr(ci, B_SRP_FAIL);
				fsm->b_ssend_srp = 0;
			पूर्ण अन्यथा अणु
				fsm->b_sess_vld = 0;
				अगर (fsm->id)
					ci_otg_add_समयr(ci, B_SSEND_SRP);
			पूर्ण
		पूर्ण अन्यथा अगर (otg_पूर्णांक_src & OTGSC_AVVIS) अणु
			hw_ग_लिखो_otgsc(ci, OTGSC_AVVIS, OTGSC_AVVIS);
			अगर (otgsc & OTGSC_AVV) अणु
				fsm->a_vbus_vld = 1;
			पूर्ण अन्यथा अणु
				fsm->a_vbus_vld = 0;
				fsm->b_conn = 0;
			पूर्ण
		पूर्ण
		ci_otg_queue_work(ci);
		वापस IRQ_HANDLED;
	पूर्ण

	ci_otg_fsm_event(ci);

	वापस retval;
पूर्ण

व्योम ci_hdrc_otg_fsm_start(काष्ठा ci_hdrc *ci)
अणु
	ci_otg_queue_work(ci);
पूर्ण

पूर्णांक ci_hdrc_otg_fsm_init(काष्ठा ci_hdrc *ci)
अणु
	पूर्णांक retval = 0;

	अगर (ci->phy)
		ci->otg.phy = ci->phy;
	अन्यथा
		ci->otg.usb_phy = ci->usb_phy;

	ci->otg.gadget = &ci->gadget;
	ci->fsm.otg = &ci->otg;
	ci->fsm.घातer_up = 1;
	ci->fsm.id = hw_पढ़ो_otgsc(ci, OTGSC_ID) ? 1 : 0;
	ci->fsm.otg->state = OTG_STATE_UNDEFINED;
	ci->fsm.ops = &ci_otg_ops;
	ci->gadget.hnp_polling_support = 1;
	ci->fsm.host_req_flag = devm_kzalloc(ci->dev, 1, GFP_KERNEL);
	अगर (!ci->fsm.host_req_flag)
		वापस -ENOMEM;

	mutex_init(&ci->fsm.lock);

	retval = ci_otg_init_समयrs(ci);
	अगर (retval) अणु
		dev_err(ci->dev, "Couldn't init OTG timers\n");
		वापस retval;
	पूर्ण
	ci->enabled_otg_समयr_bits = 0;
	ci->next_otg_समयr = NUM_OTG_FSM_TIMERS;

	retval = sysfs_create_group(&ci->dev->kobj, &inमाला_दो_attr_group);
	अगर (retval < 0) अणु
		dev_dbg(ci->dev,
			"Can't register sysfs attr group: %d\n", retval);
		वापस retval;
	पूर्ण

	/* Enable A vbus valid irq */
	hw_ग_लिखो_otgsc(ci, OTGSC_AVVIE, OTGSC_AVVIE);

	अगर (ci->fsm.id) अणु
		ci->fsm.b_ssend_srp =
			hw_पढ़ो_otgsc(ci, OTGSC_BSV) ? 0 : 1;
		ci->fsm.b_sess_vld =
			hw_पढ़ो_otgsc(ci, OTGSC_BSV) ? 1 : 0;
		/* Enable BSV irq */
		hw_ग_लिखो_otgsc(ci, OTGSC_BSVIE, OTGSC_BSVIE);
	पूर्ण

	वापस 0;
पूर्ण

व्योम ci_hdrc_otg_fsm_हटाओ(काष्ठा ci_hdrc *ci)
अणु
	sysfs_हटाओ_group(&ci->dev->kobj, &inमाला_दो_attr_group);
पूर्ण
