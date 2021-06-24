<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * otg.c - ChipIdea USB IP core OTG driver
 *
 * Copyright (C) 2013 Freescale Semiconductor, Inc.
 *
 * Author: Peter Chen
 */

/*
 * This file मुख्यly handles otgsc रेजिस्टर, OTG fsm operations क्रम HNP and SRP
 * are also included.
 */

#समावेश <linux/usb/otg.h>
#समावेश <linux/usb/gadget.h>
#समावेश <linux/usb/chipidea.h>

#समावेश "ci.h"
#समावेश "bits.h"
#समावेश "otg.h"
#समावेश "otg_fsm.h"

/**
 * hw_पढ़ो_otgsc वापसs otgsc रेजिस्टर bits value.
 * @ci: the controller
 * @mask: bitfield mask
 */
u32 hw_पढ़ो_otgsc(काष्ठा ci_hdrc *ci, u32 mask)
अणु
	काष्ठा ci_hdrc_cable *cable;
	u32 val = hw_पढ़ो(ci, OP_OTGSC, mask);

	/*
	 * If using extcon framework क्रम VBUS and/or ID संकेत
	 * detection overग_लिखो OTGSC रेजिस्टर value
	 */
	cable = &ci->platdata->vbus_extcon;
	अगर (!IS_ERR(cable->edev) || ci->role_चयन) अणु
		अगर (cable->changed)
			val |= OTGSC_BSVIS;
		अन्यथा
			val &= ~OTGSC_BSVIS;

		अगर (cable->connected)
			val |= OTGSC_BSV;
		अन्यथा
			val &= ~OTGSC_BSV;

		अगर (cable->enabled)
			val |= OTGSC_BSVIE;
		अन्यथा
			val &= ~OTGSC_BSVIE;
	पूर्ण

	cable = &ci->platdata->id_extcon;
	अगर (!IS_ERR(cable->edev) || ci->role_चयन) अणु
		अगर (cable->changed)
			val |= OTGSC_IDIS;
		अन्यथा
			val &= ~OTGSC_IDIS;

		अगर (cable->connected)
			val &= ~OTGSC_ID; /* host */
		अन्यथा
			val |= OTGSC_ID; /* device */

		अगर (cable->enabled)
			val |= OTGSC_IDIE;
		अन्यथा
			val &= ~OTGSC_IDIE;
	पूर्ण

	वापस val & mask;
पूर्ण

/**
 * hw_ग_लिखो_otgsc updates target bits of OTGSC रेजिस्टर.
 * @ci: the controller
 * @mask: bitfield mask
 * @data: to be written
 */
व्योम hw_ग_लिखो_otgsc(काष्ठा ci_hdrc *ci, u32 mask, u32 data)
अणु
	काष्ठा ci_hdrc_cable *cable;

	cable = &ci->platdata->vbus_extcon;
	अगर (!IS_ERR(cable->edev) || ci->role_चयन) अणु
		अगर (data & mask & OTGSC_BSVIS)
			cable->changed = false;

		/* Don't enable vbus पूर्णांकerrupt अगर using बाह्यal notअगरier */
		अगर (data & mask & OTGSC_BSVIE) अणु
			cable->enabled = true;
			data &= ~OTGSC_BSVIE;
		पूर्ण अन्यथा अगर (mask & OTGSC_BSVIE) अणु
			cable->enabled = false;
		पूर्ण
	पूर्ण

	cable = &ci->platdata->id_extcon;
	अगर (!IS_ERR(cable->edev) || ci->role_चयन) अणु
		अगर (data & mask & OTGSC_IDIS)
			cable->changed = false;

		/* Don't enable id पूर्णांकerrupt अगर using बाह्यal notअगरier */
		अगर (data & mask & OTGSC_IDIE) अणु
			cable->enabled = true;
			data &= ~OTGSC_IDIE;
		पूर्ण अन्यथा अगर (mask & OTGSC_IDIE) अणु
			cable->enabled = false;
		पूर्ण
	पूर्ण

	hw_ग_लिखो(ci, OP_OTGSC, mask | OTGSC_INT_STATUS_BITS, data);
पूर्ण

/**
 * ci_otg_role - pick role based on ID pin state
 * @ci: the controller
 */
क्रमागत ci_role ci_otg_role(काष्ठा ci_hdrc *ci)
अणु
	क्रमागत ci_role role = hw_पढ़ो_otgsc(ci, OTGSC_ID)
		? CI_ROLE_GADGET
		: CI_ROLE_HOST;

	वापस role;
पूर्ण

व्योम ci_handle_vbus_change(काष्ठा ci_hdrc *ci)
अणु
	अगर (!ci->is_otg)
		वापस;

	अगर (hw_पढ़ो_otgsc(ci, OTGSC_BSV) && !ci->vbus_active)
		usb_gadget_vbus_connect(&ci->gadget);
	अन्यथा अगर (!hw_पढ़ो_otgsc(ci, OTGSC_BSV) && ci->vbus_active)
		usb_gadget_vbus_disconnect(&ci->gadget);
पूर्ण

/**
 * When we चयन to device mode, the vbus value should be lower
 * than OTGSC_BSV beक्रमe connecting to host.
 *
 * @ci: the controller
 *
 * This function वापसs an error code अगर समयout
 */
अटल पूर्णांक hw_रुको_vbus_lower_bsv(काष्ठा ci_hdrc *ci)
अणु
	अचिन्हित दीर्घ elapse = jअगरfies + msecs_to_jअगरfies(5000);
	u32 mask = OTGSC_BSV;

	जबतक (hw_पढ़ो_otgsc(ci, mask)) अणु
		अगर (समय_after(jअगरfies, elapse)) अणु
			dev_err(ci->dev, "timeout waiting for %08x in OTGSC\n",
					mask);
			वापस -ETIMEDOUT;
		पूर्ण
		msleep(20);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ci_handle_id_चयन(काष्ठा ci_hdrc *ci)
अणु
	क्रमागत ci_role role = ci_otg_role(ci);

	अगर (role != ci->role) अणु
		dev_dbg(ci->dev, "switching from %s to %s\n",
			ci_role(ci)->name, ci->roles[role]->name);

		अगर (ci->vbus_active && ci->role == CI_ROLE_GADGET)
			/*
			 * vbus disconnect event is lost due to role
			 * चयन occurs during प्रणाली suspend.
			 */
			usb_gadget_vbus_disconnect(&ci->gadget);

		ci_role_stop(ci);

		अगर (role == CI_ROLE_GADGET &&
				IS_ERR(ci->platdata->vbus_extcon.edev))
			/*
			 * Wait vbus lower than OTGSC_BSV beक्रमe connecting
			 * to host. If connecting status is from an बाह्यal
			 * connector instead of रेजिस्टर, we करोn't need to
			 * care vbus on the board, since it will not affect
			 * बाह्यal connector status.
			 */
			hw_रुको_vbus_lower_bsv(ci);

		ci_role_start(ci, role);
		/* vbus change may have alपढ़ोy occurred */
		अगर (role == CI_ROLE_GADGET)
			ci_handle_vbus_change(ci);
	पूर्ण
पूर्ण
/**
 * ci_otg_work - perक्रमm otg (vbus/id) event handle
 * @work: work काष्ठा
 */
अटल व्योम ci_otg_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ci_hdrc *ci = container_of(work, काष्ठा ci_hdrc, work);

	अगर (ci_otg_is_fsm_mode(ci) && !ci_otg_fsm_work(ci)) अणु
		enable_irq(ci->irq);
		वापस;
	पूर्ण

	pm_runसमय_get_sync(ci->dev);

	अगर (ci->id_event) अणु
		ci->id_event = false;
		ci_handle_id_चयन(ci);
	पूर्ण

	अगर (ci->b_sess_valid_event) अणु
		ci->b_sess_valid_event = false;
		ci_handle_vbus_change(ci);
	पूर्ण

	pm_runसमय_put_sync(ci->dev);

	enable_irq(ci->irq);
पूर्ण


/**
 * ci_hdrc_otg_init - initialize otg काष्ठा
 * @ci: the controller
 */
पूर्णांक ci_hdrc_otg_init(काष्ठा ci_hdrc *ci)
अणु
	INIT_WORK(&ci->work, ci_otg_work);
	ci->wq = create_मुक्तzable_workqueue("ci_otg");
	अगर (!ci->wq) अणु
		dev_err(ci->dev, "can't create workqueue\n");
		वापस -ENODEV;
	पूर्ण

	अगर (ci_otg_is_fsm_mode(ci))
		वापस ci_hdrc_otg_fsm_init(ci);

	वापस 0;
पूर्ण

/**
 * ci_hdrc_otg_destroy - destroy otg काष्ठा
 * @ci: the controller
 */
व्योम ci_hdrc_otg_destroy(काष्ठा ci_hdrc *ci)
अणु
	अगर (ci->wq) अणु
		flush_workqueue(ci->wq);
		destroy_workqueue(ci->wq);
	पूर्ण
	/* Disable all OTG irq and clear status */
	hw_ग_लिखो_otgsc(ci, OTGSC_INT_EN_BITS | OTGSC_INT_STATUS_BITS,
						OTGSC_INT_STATUS_BITS);
	अगर (ci_otg_is_fsm_mode(ci))
		ci_hdrc_otg_fsm_हटाओ(ci);
पूर्ण
