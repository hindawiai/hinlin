<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2011 Marvell International Ltd. All rights reserved.
 * Author: Chao Xie <chao.xie@marvell.com>
 *	   Neil Zhang <zhangwm@marvell.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/device.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/clk.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <linux/usb.h>
#समावेश <linux/usb/ch9.h>
#समावेश <linux/usb/otg.h>
#समावेश <linux/usb/gadget.h>
#समावेश <linux/usb/hcd.h>
#समावेश <linux/platक्रमm_data/mv_usb.h>

#समावेश "phy-mv-usb.h"

#घोषणा	DRIVER_DESC	"Marvell USB OTG transceiver driver"

MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");

अटल स्थिर अक्षर driver_name[] = "mv-otg";

अटल अक्षर *state_string[] = अणु
	"undefined",
	"b_idle",
	"b_srp_init",
	"b_peripheral",
	"b_wait_acon",
	"b_host",
	"a_idle",
	"a_wait_vrise",
	"a_wait_bcon",
	"a_host",
	"a_suspend",
	"a_peripheral",
	"a_wait_vfall",
	"a_vbus_err"
पूर्ण;

अटल पूर्णांक mv_otg_set_vbus(काष्ठा usb_otg *otg, bool on)
अणु
	काष्ठा mv_otg *mvotg = container_of(otg->usb_phy, काष्ठा mv_otg, phy);
	अगर (mvotg->pdata->set_vbus == शून्य)
		वापस -ENODEV;

	वापस mvotg->pdata->set_vbus(on);
पूर्ण

अटल पूर्णांक mv_otg_set_host(काष्ठा usb_otg *otg,
			   काष्ठा usb_bus *host)
अणु
	otg->host = host;

	वापस 0;
पूर्ण

अटल पूर्णांक mv_otg_set_peripheral(काष्ठा usb_otg *otg,
				 काष्ठा usb_gadget *gadget)
अणु
	otg->gadget = gadget;

	वापस 0;
पूर्ण

अटल व्योम mv_otg_run_state_machine(काष्ठा mv_otg *mvotg,
				     अचिन्हित दीर्घ delay)
अणु
	dev_dbg(&mvotg->pdev->dev, "transceiver is updated\n");
	अगर (!mvotg->qwork)
		वापस;

	queue_delayed_work(mvotg->qwork, &mvotg->work, delay);
पूर्ण

अटल व्योम mv_otg_समयr_aरुको_bcon(काष्ठा समयr_list *t)
अणु
	काष्ठा mv_otg *mvotg = from_समयr(mvotg, t,
					  otg_ctrl.समयr[A_WAIT_BCON_TIMER]);

	mvotg->otg_ctrl.a_रुको_bcon_समयout = 1;

	dev_info(&mvotg->pdev->dev, "B Device No Response!\n");

	अगर (spin_trylock(&mvotg->wq_lock)) अणु
		mv_otg_run_state_machine(mvotg, 0);
		spin_unlock(&mvotg->wq_lock);
	पूर्ण
पूर्ण

अटल पूर्णांक mv_otg_cancel_समयr(काष्ठा mv_otg *mvotg, अचिन्हित पूर्णांक id)
अणु
	काष्ठा समयr_list *समयr;

	अगर (id >= OTG_TIMER_NUM)
		वापस -EINVAL;

	समयr = &mvotg->otg_ctrl.समयr[id];

	अगर (समयr_pending(समयr))
		del_समयr(समयr);

	वापस 0;
पूर्ण

अटल पूर्णांक mv_otg_set_समयr(काष्ठा mv_otg *mvotg, अचिन्हित पूर्णांक id,
			    अचिन्हित दीर्घ पूर्णांकerval)
अणु
	काष्ठा समयr_list *समयr;

	अगर (id >= OTG_TIMER_NUM)
		वापस -EINVAL;

	समयr = &mvotg->otg_ctrl.समयr[id];
	अगर (समयr_pending(समयr)) अणु
		dev_err(&mvotg->pdev->dev, "Timer%d is already running\n", id);
		वापस -EBUSY;
	पूर्ण

	समयr->expires = jअगरfies + पूर्णांकerval;
	add_समयr(समयr);

	वापस 0;
पूर्ण

अटल पूर्णांक mv_otg_reset(काष्ठा mv_otg *mvotg)
अणु
	u32 पंचांगp;
	पूर्णांक ret;

	/* Stop the controller */
	पंचांगp = पढ़ोl(&mvotg->op_regs->usbcmd);
	पंचांगp &= ~USBCMD_RUN_STOP;
	ग_लिखोl(पंचांगp, &mvotg->op_regs->usbcmd);

	/* Reset the controller to get शेष values */
	ग_लिखोl(USBCMD_CTRL_RESET, &mvotg->op_regs->usbcmd);

	ret = पढ़ोl_poll_समयout_atomic(&mvotg->op_regs->usbcmd, पंचांगp,
				(पंचांगp & USBCMD_CTRL_RESET), 10, 10000);
	अगर (ret < 0) अणु
		dev_err(&mvotg->pdev->dev,
			"Wait for RESET completed TIMEOUT\n");
		वापस ret;
	पूर्ण

	ग_लिखोl(0x0, &mvotg->op_regs->usbपूर्णांकr);
	पंचांगp = पढ़ोl(&mvotg->op_regs->usbsts);
	ग_लिखोl(पंचांगp, &mvotg->op_regs->usbsts);

	वापस 0;
पूर्ण

अटल व्योम mv_otg_init_irq(काष्ठा mv_otg *mvotg)
अणु
	u32 otgsc;

	mvotg->irq_en = OTGSC_INTR_A_SESSION_VALID
	    | OTGSC_INTR_A_VBUS_VALID;
	mvotg->irq_status = OTGSC_INTSTS_A_SESSION_VALID
	    | OTGSC_INTSTS_A_VBUS_VALID;

	अगर (mvotg->pdata->vbus == शून्य) अणु
		mvotg->irq_en |= OTGSC_INTR_B_SESSION_VALID
		    | OTGSC_INTR_B_SESSION_END;
		mvotg->irq_status |= OTGSC_INTSTS_B_SESSION_VALID
		    | OTGSC_INTSTS_B_SESSION_END;
	पूर्ण

	अगर (mvotg->pdata->id == शून्य) अणु
		mvotg->irq_en |= OTGSC_INTR_USB_ID;
		mvotg->irq_status |= OTGSC_INTSTS_USB_ID;
	पूर्ण

	otgsc = पढ़ोl(&mvotg->op_regs->otgsc);
	otgsc |= mvotg->irq_en;
	ग_लिखोl(otgsc, &mvotg->op_regs->otgsc);
पूर्ण

अटल व्योम mv_otg_start_host(काष्ठा mv_otg *mvotg, पूर्णांक on)
अणु
#अगर_घोषित CONFIG_USB
	काष्ठा usb_otg *otg = mvotg->phy.otg;
	काष्ठा usb_hcd *hcd;

	अगर (!otg->host)
		वापस;

	dev_info(&mvotg->pdev->dev, "%s host\n", on ? "start" : "stop");

	hcd = bus_to_hcd(otg->host);

	अगर (on) अणु
		usb_add_hcd(hcd, hcd->irq, IRQF_SHARED);
		device_wakeup_enable(hcd->self.controller);
	पूर्ण अन्यथा अणु
		usb_हटाओ_hcd(hcd);
	पूर्ण
#पूर्ण_अगर /* CONFIG_USB */
पूर्ण

अटल व्योम mv_otg_start_periphrals(काष्ठा mv_otg *mvotg, पूर्णांक on)
अणु
	काष्ठा usb_otg *otg = mvotg->phy.otg;

	अगर (!otg->gadget)
		वापस;

	dev_info(mvotg->phy.dev, "gadget %s\n", on ? "on" : "off");

	अगर (on)
		usb_gadget_vbus_connect(otg->gadget);
	अन्यथा
		usb_gadget_vbus_disconnect(otg->gadget);
पूर्ण

अटल व्योम otg_घड़ी_enable(काष्ठा mv_otg *mvotg)
अणु
	clk_prepare_enable(mvotg->clk);
पूर्ण

अटल व्योम otg_घड़ी_disable(काष्ठा mv_otg *mvotg)
अणु
	clk_disable_unprepare(mvotg->clk);
पूर्ण

अटल पूर्णांक mv_otg_enable_पूर्णांकernal(काष्ठा mv_otg *mvotg)
अणु
	पूर्णांक retval = 0;

	अगर (mvotg->active)
		वापस 0;

	dev_dbg(&mvotg->pdev->dev, "otg enabled\n");

	otg_घड़ी_enable(mvotg);
	अगर (mvotg->pdata->phy_init) अणु
		retval = mvotg->pdata->phy_init(mvotg->phy_regs);
		अगर (retval) अणु
			dev_err(&mvotg->pdev->dev,
				"init phy error %d\n", retval);
			otg_घड़ी_disable(mvotg);
			वापस retval;
		पूर्ण
	पूर्ण
	mvotg->active = 1;

	वापस 0;

पूर्ण

अटल पूर्णांक mv_otg_enable(काष्ठा mv_otg *mvotg)
अणु
	अगर (mvotg->घड़ी_gating)
		वापस mv_otg_enable_पूर्णांकernal(mvotg);

	वापस 0;
पूर्ण

अटल व्योम mv_otg_disable_पूर्णांकernal(काष्ठा mv_otg *mvotg)
अणु
	अगर (mvotg->active) अणु
		dev_dbg(&mvotg->pdev->dev, "otg disabled\n");
		अगर (mvotg->pdata->phy_deinit)
			mvotg->pdata->phy_deinit(mvotg->phy_regs);
		otg_घड़ी_disable(mvotg);
		mvotg->active = 0;
	पूर्ण
पूर्ण

अटल व्योम mv_otg_disable(काष्ठा mv_otg *mvotg)
अणु
	अगर (mvotg->घड़ी_gating)
		mv_otg_disable_पूर्णांकernal(mvotg);
पूर्ण

अटल व्योम mv_otg_update_inमाला_दो(काष्ठा mv_otg *mvotg)
अणु
	काष्ठा mv_otg_ctrl *otg_ctrl = &mvotg->otg_ctrl;
	u32 otgsc;

	otgsc = पढ़ोl(&mvotg->op_regs->otgsc);

	अगर (mvotg->pdata->vbus) अणु
		अगर (mvotg->pdata->vbus->poll() == VBUS_HIGH) अणु
			otg_ctrl->b_sess_vld = 1;
			otg_ctrl->b_sess_end = 0;
		पूर्ण अन्यथा अणु
			otg_ctrl->b_sess_vld = 0;
			otg_ctrl->b_sess_end = 1;
		पूर्ण
	पूर्ण अन्यथा अणु
		otg_ctrl->b_sess_vld = !!(otgsc & OTGSC_STS_B_SESSION_VALID);
		otg_ctrl->b_sess_end = !!(otgsc & OTGSC_STS_B_SESSION_END);
	पूर्ण

	अगर (mvotg->pdata->id)
		otg_ctrl->id = !!mvotg->pdata->id->poll();
	अन्यथा
		otg_ctrl->id = !!(otgsc & OTGSC_STS_USB_ID);

	अगर (mvotg->pdata->otg_क्रमce_a_bus_req && !otg_ctrl->id)
		otg_ctrl->a_bus_req = 1;

	otg_ctrl->a_sess_vld = !!(otgsc & OTGSC_STS_A_SESSION_VALID);
	otg_ctrl->a_vbus_vld = !!(otgsc & OTGSC_STS_A_VBUS_VALID);

	dev_dbg(&mvotg->pdev->dev, "%s: ", __func__);
	dev_dbg(&mvotg->pdev->dev, "id %d\n", otg_ctrl->id);
	dev_dbg(&mvotg->pdev->dev, "b_sess_vld %d\n", otg_ctrl->b_sess_vld);
	dev_dbg(&mvotg->pdev->dev, "b_sess_end %d\n", otg_ctrl->b_sess_end);
	dev_dbg(&mvotg->pdev->dev, "a_vbus_vld %d\n", otg_ctrl->a_vbus_vld);
	dev_dbg(&mvotg->pdev->dev, "a_sess_vld %d\n", otg_ctrl->a_sess_vld);
पूर्ण

अटल व्योम mv_otg_update_state(काष्ठा mv_otg *mvotg)
अणु
	काष्ठा mv_otg_ctrl *otg_ctrl = &mvotg->otg_ctrl;
	पूर्णांक old_state = mvotg->phy.otg->state;

	चयन (old_state) अणु
	हाल OTG_STATE_UNDEFINED:
		mvotg->phy.otg->state = OTG_STATE_B_IDLE;
		fallthrough;
	हाल OTG_STATE_B_IDLE:
		अगर (otg_ctrl->id == 0)
			mvotg->phy.otg->state = OTG_STATE_A_IDLE;
		अन्यथा अगर (otg_ctrl->b_sess_vld)
			mvotg->phy.otg->state = OTG_STATE_B_PERIPHERAL;
		अवरोध;
	हाल OTG_STATE_B_PERIPHERAL:
		अगर (!otg_ctrl->b_sess_vld || otg_ctrl->id == 0)
			mvotg->phy.otg->state = OTG_STATE_B_IDLE;
		अवरोध;
	हाल OTG_STATE_A_IDLE:
		अगर (otg_ctrl->id)
			mvotg->phy.otg->state = OTG_STATE_B_IDLE;
		अन्यथा अगर (!(otg_ctrl->a_bus_drop) &&
			 (otg_ctrl->a_bus_req || otg_ctrl->a_srp_det))
			mvotg->phy.otg->state = OTG_STATE_A_WAIT_VRISE;
		अवरोध;
	हाल OTG_STATE_A_WAIT_VRISE:
		अगर (otg_ctrl->a_vbus_vld)
			mvotg->phy.otg->state = OTG_STATE_A_WAIT_BCON;
		अवरोध;
	हाल OTG_STATE_A_WAIT_BCON:
		अगर (otg_ctrl->id || otg_ctrl->a_bus_drop
		    || otg_ctrl->a_रुको_bcon_समयout) अणु
			mv_otg_cancel_समयr(mvotg, A_WAIT_BCON_TIMER);
			mvotg->otg_ctrl.a_रुको_bcon_समयout = 0;
			mvotg->phy.otg->state = OTG_STATE_A_WAIT_VFALL;
			otg_ctrl->a_bus_req = 0;
		पूर्ण अन्यथा अगर (!otg_ctrl->a_vbus_vld) अणु
			mv_otg_cancel_समयr(mvotg, A_WAIT_BCON_TIMER);
			mvotg->otg_ctrl.a_रुको_bcon_समयout = 0;
			mvotg->phy.otg->state = OTG_STATE_A_VBUS_ERR;
		पूर्ण अन्यथा अगर (otg_ctrl->b_conn) अणु
			mv_otg_cancel_समयr(mvotg, A_WAIT_BCON_TIMER);
			mvotg->otg_ctrl.a_रुको_bcon_समयout = 0;
			mvotg->phy.otg->state = OTG_STATE_A_HOST;
		पूर्ण
		अवरोध;
	हाल OTG_STATE_A_HOST:
		अगर (otg_ctrl->id || !otg_ctrl->b_conn
		    || otg_ctrl->a_bus_drop)
			mvotg->phy.otg->state = OTG_STATE_A_WAIT_BCON;
		अन्यथा अगर (!otg_ctrl->a_vbus_vld)
			mvotg->phy.otg->state = OTG_STATE_A_VBUS_ERR;
		अवरोध;
	हाल OTG_STATE_A_WAIT_VFALL:
		अगर (otg_ctrl->id
		    || (!otg_ctrl->b_conn && otg_ctrl->a_sess_vld)
		    || otg_ctrl->a_bus_req)
			mvotg->phy.otg->state = OTG_STATE_A_IDLE;
		अवरोध;
	हाल OTG_STATE_A_VBUS_ERR:
		अगर (otg_ctrl->id || otg_ctrl->a_clr_err
		    || otg_ctrl->a_bus_drop) अणु
			otg_ctrl->a_clr_err = 0;
			mvotg->phy.otg->state = OTG_STATE_A_WAIT_VFALL;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम mv_otg_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mv_otg *mvotg;
	काष्ठा usb_otg *otg;
	पूर्णांक old_state;

	mvotg = container_of(to_delayed_work(work), काष्ठा mv_otg, work);

run:
	/* work queue is single thपढ़ो, or we need spin_lock to protect */
	otg = mvotg->phy.otg;
	old_state = otg->state;

	अगर (!mvotg->active)
		वापस;

	mv_otg_update_inमाला_दो(mvotg);
	mv_otg_update_state(mvotg);

	अगर (old_state != mvotg->phy.otg->state) अणु
		dev_info(&mvotg->pdev->dev, "change from state %s to %s\n",
			 state_string[old_state],
			 state_string[mvotg->phy.otg->state]);

		चयन (mvotg->phy.otg->state) अणु
		हाल OTG_STATE_B_IDLE:
			otg->शेष_a = 0;
			अगर (old_state == OTG_STATE_B_PERIPHERAL)
				mv_otg_start_periphrals(mvotg, 0);
			mv_otg_reset(mvotg);
			mv_otg_disable(mvotg);
			usb_phy_set_event(&mvotg->phy, USB_EVENT_NONE);
			अवरोध;
		हाल OTG_STATE_B_PERIPHERAL:
			mv_otg_enable(mvotg);
			mv_otg_start_periphrals(mvotg, 1);
			usb_phy_set_event(&mvotg->phy, USB_EVENT_ENUMERATED);
			अवरोध;
		हाल OTG_STATE_A_IDLE:
			otg->शेष_a = 1;
			mv_otg_enable(mvotg);
			अगर (old_state == OTG_STATE_A_WAIT_VFALL)
				mv_otg_start_host(mvotg, 0);
			mv_otg_reset(mvotg);
			अवरोध;
		हाल OTG_STATE_A_WAIT_VRISE:
			mv_otg_set_vbus(otg, 1);
			अवरोध;
		हाल OTG_STATE_A_WAIT_BCON:
			अगर (old_state != OTG_STATE_A_HOST)
				mv_otg_start_host(mvotg, 1);
			mv_otg_set_समयr(mvotg, A_WAIT_BCON_TIMER,
					 T_A_WAIT_BCON);
			/*
			 * Now, we directly enter A_HOST. So set b_conn = 1
			 * here. In fact, it need host driver to notअगरy us.
			 */
			mvotg->otg_ctrl.b_conn = 1;
			अवरोध;
		हाल OTG_STATE_A_HOST:
			अवरोध;
		हाल OTG_STATE_A_WAIT_VFALL:
			/*
			 * Now, we has निकासed A_HOST. So set b_conn = 0
			 * here. In fact, it need host driver to notअगरy us.
			 */
			mvotg->otg_ctrl.b_conn = 0;
			mv_otg_set_vbus(otg, 0);
			अवरोध;
		हाल OTG_STATE_A_VBUS_ERR:
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		जाओ run;
	पूर्ण
पूर्ण

अटल irqवापस_t mv_otg_irq(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा mv_otg *mvotg = dev;
	u32 otgsc;

	otgsc = पढ़ोl(&mvotg->op_regs->otgsc);
	ग_लिखोl(otgsc, &mvotg->op_regs->otgsc);

	/*
	 * अगर we have vbus, then the vbus detection क्रम B-device
	 * will be करोne by mv_otg_inमाला_दो_irq().
	 */
	अगर (mvotg->pdata->vbus)
		अगर ((otgsc & OTGSC_STS_USB_ID) &&
		    !(otgsc & OTGSC_INTSTS_USB_ID))
			वापस IRQ_NONE;

	अगर ((otgsc & mvotg->irq_status) == 0)
		वापस IRQ_NONE;

	mv_otg_run_state_machine(mvotg, 0);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t mv_otg_inमाला_दो_irq(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा mv_otg *mvotg = dev;

	/* The घड़ी may disabled at this समय */
	अगर (!mvotg->active) अणु
		mv_otg_enable(mvotg);
		mv_otg_init_irq(mvotg);
	पूर्ण

	mv_otg_run_state_machine(mvotg, 0);

	वापस IRQ_HANDLED;
पूर्ण

अटल sमाप_प्रकार
a_bus_req_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा mv_otg *mvotg = dev_get_drvdata(dev);
	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n",
			 mvotg->otg_ctrl.a_bus_req);
पूर्ण

अटल sमाप_प्रकार
a_bus_req_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
	      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा mv_otg *mvotg = dev_get_drvdata(dev);

	अगर (count > 2)
		वापस -1;

	/* We will use this पूर्णांकerface to change to A device */
	अगर (mvotg->phy.otg->state != OTG_STATE_B_IDLE
	    && mvotg->phy.otg->state != OTG_STATE_A_IDLE)
		वापस -1;

	/* The घड़ी may disabled and we need to set irq क्रम ID detected */
	mv_otg_enable(mvotg);
	mv_otg_init_irq(mvotg);

	अगर (buf[0] == '1') अणु
		mvotg->otg_ctrl.a_bus_req = 1;
		mvotg->otg_ctrl.a_bus_drop = 0;
		dev_dbg(&mvotg->pdev->dev,
			"User request: a_bus_req = 1\n");

		अगर (spin_trylock(&mvotg->wq_lock)) अणु
			mv_otg_run_state_machine(mvotg, 0);
			spin_unlock(&mvotg->wq_lock);
		पूर्ण
	पूर्ण

	वापस count;
पूर्ण

अटल DEVICE_ATTR_RW(a_bus_req);

अटल sमाप_प्रकार
a_clr_err_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
	      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा mv_otg *mvotg = dev_get_drvdata(dev);
	अगर (!mvotg->phy.otg->शेष_a)
		वापस -1;

	अगर (count > 2)
		वापस -1;

	अगर (buf[0] == '1') अणु
		mvotg->otg_ctrl.a_clr_err = 1;
		dev_dbg(&mvotg->pdev->dev,
			"User request: a_clr_err = 1\n");
	पूर्ण

	अगर (spin_trylock(&mvotg->wq_lock)) अणु
		mv_otg_run_state_machine(mvotg, 0);
		spin_unlock(&mvotg->wq_lock);
	पूर्ण

	वापस count;
पूर्ण

अटल DEVICE_ATTR_WO(a_clr_err);

अटल sमाप_प्रकार
a_bus_drop_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
	       अक्षर *buf)
अणु
	काष्ठा mv_otg *mvotg = dev_get_drvdata(dev);
	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n",
			 mvotg->otg_ctrl.a_bus_drop);
पूर्ण

अटल sमाप_प्रकार
a_bus_drop_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
	       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा mv_otg *mvotg = dev_get_drvdata(dev);
	अगर (!mvotg->phy.otg->शेष_a)
		वापस -1;

	अगर (count > 2)
		वापस -1;

	अगर (buf[0] == '0') अणु
		mvotg->otg_ctrl.a_bus_drop = 0;
		dev_dbg(&mvotg->pdev->dev,
			"User request: a_bus_drop = 0\n");
	पूर्ण अन्यथा अगर (buf[0] == '1') अणु
		mvotg->otg_ctrl.a_bus_drop = 1;
		mvotg->otg_ctrl.a_bus_req = 0;
		dev_dbg(&mvotg->pdev->dev,
			"User request: a_bus_drop = 1\n");
		dev_dbg(&mvotg->pdev->dev,
			"User request: and a_bus_req = 0\n");
	पूर्ण

	अगर (spin_trylock(&mvotg->wq_lock)) अणु
		mv_otg_run_state_machine(mvotg, 0);
		spin_unlock(&mvotg->wq_lock);
	पूर्ण

	वापस count;
पूर्ण

अटल DEVICE_ATTR_RW(a_bus_drop);

अटल काष्ठा attribute *inमाला_दो_attrs[] = अणु
	&dev_attr_a_bus_req.attr,
	&dev_attr_a_clr_err.attr,
	&dev_attr_a_bus_drop.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group inमाला_दो_attr_group = अणु
	.name = "inputs",
	.attrs = inमाला_दो_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *mv_otg_groups[] = अणु
	&inमाला_दो_attr_group,
	शून्य,
पूर्ण;

अटल पूर्णांक mv_otg_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mv_otg *mvotg = platक्रमm_get_drvdata(pdev);

	अगर (mvotg->qwork) अणु
		flush_workqueue(mvotg->qwork);
		destroy_workqueue(mvotg->qwork);
	पूर्ण

	mv_otg_disable(mvotg);

	usb_हटाओ_phy(&mvotg->phy);

	वापस 0;
पूर्ण

अटल पूर्णांक mv_otg_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mv_usb_platक्रमm_data *pdata = dev_get_platdata(&pdev->dev);
	काष्ठा mv_otg *mvotg;
	काष्ठा usb_otg *otg;
	काष्ठा resource *r;
	पूर्णांक retval = 0, i;

	अगर (pdata == शून्य) अणु
		dev_err(&pdev->dev, "failed to get platform data\n");
		वापस -ENODEV;
	पूर्ण

	mvotg = devm_kzalloc(&pdev->dev, माप(*mvotg), GFP_KERNEL);
	अगर (!mvotg)
		वापस -ENOMEM;

	otg = devm_kzalloc(&pdev->dev, माप(*otg), GFP_KERNEL);
	अगर (!otg)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, mvotg);

	mvotg->pdev = pdev;
	mvotg->pdata = pdata;

	mvotg->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(mvotg->clk))
		वापस PTR_ERR(mvotg->clk);

	mvotg->qwork = create_singlethपढ़ो_workqueue("mv_otg_queue");
	अगर (!mvotg->qwork) अणु
		dev_dbg(&pdev->dev, "cannot create workqueue for OTG\n");
		वापस -ENOMEM;
	पूर्ण

	INIT_DELAYED_WORK(&mvotg->work, mv_otg_work);

	/* OTG common part */
	mvotg->pdev = pdev;
	mvotg->phy.dev = &pdev->dev;
	mvotg->phy.otg = otg;
	mvotg->phy.label = driver_name;

	otg->state = OTG_STATE_UNDEFINED;
	otg->usb_phy = &mvotg->phy;
	otg->set_host = mv_otg_set_host;
	otg->set_peripheral = mv_otg_set_peripheral;
	otg->set_vbus = mv_otg_set_vbus;

	क्रम (i = 0; i < OTG_TIMER_NUM; i++)
		समयr_setup(&mvotg->otg_ctrl.समयr[i],
			    mv_otg_समयr_aरुको_bcon, 0);

	r = platक्रमm_get_resource_byname(mvotg->pdev,
					 IORESOURCE_MEM, "phyregs");
	अगर (r == शून्य) अणु
		dev_err(&pdev->dev, "no phy I/O memory resource defined\n");
		retval = -ENODEV;
		जाओ err_destroy_workqueue;
	पूर्ण

	mvotg->phy_regs = devm_ioremap(&pdev->dev, r->start, resource_size(r));
	अगर (mvotg->phy_regs == शून्य) अणु
		dev_err(&pdev->dev, "failed to map phy I/O memory\n");
		retval = -EFAULT;
		जाओ err_destroy_workqueue;
	पूर्ण

	r = platक्रमm_get_resource_byname(mvotg->pdev,
					 IORESOURCE_MEM, "capregs");
	अगर (r == शून्य) अणु
		dev_err(&pdev->dev, "no I/O memory resource defined\n");
		retval = -ENODEV;
		जाओ err_destroy_workqueue;
	पूर्ण

	mvotg->cap_regs = devm_ioremap(&pdev->dev, r->start, resource_size(r));
	अगर (mvotg->cap_regs == शून्य) अणु
		dev_err(&pdev->dev, "failed to map I/O memory\n");
		retval = -EFAULT;
		जाओ err_destroy_workqueue;
	पूर्ण

	/* we will acces controller रेजिस्टर, so enable the udc controller */
	retval = mv_otg_enable_पूर्णांकernal(mvotg);
	अगर (retval) अणु
		dev_err(&pdev->dev, "mv otg enable error %d\n", retval);
		जाओ err_destroy_workqueue;
	पूर्ण

	mvotg->op_regs =
		(काष्ठा mv_otg_regs __iomem *) ((अचिन्हित दीर्घ) mvotg->cap_regs
			+ (पढ़ोl(mvotg->cap_regs) & CAPLENGTH_MASK));

	अगर (pdata->id) अणु
		retval = devm_request_thपढ़ोed_irq(&pdev->dev, pdata->id->irq,
						शून्य, mv_otg_inमाला_दो_irq,
						IRQF_ONESHOT, "id", mvotg);
		अगर (retval) अणु
			dev_info(&pdev->dev,
				 "Failed to request irq for ID\n");
			pdata->id = शून्य;
		पूर्ण
	पूर्ण

	अगर (pdata->vbus) अणु
		mvotg->घड़ी_gating = 1;
		retval = devm_request_thपढ़ोed_irq(&pdev->dev, pdata->vbus->irq,
						शून्य, mv_otg_inमाला_दो_irq,
						IRQF_ONESHOT, "vbus", mvotg);
		अगर (retval) अणु
			dev_info(&pdev->dev,
				 "Failed to request irq for VBUS, "
				 "disable clock gating\n");
			mvotg->घड़ी_gating = 0;
			pdata->vbus = शून्य;
		पूर्ण
	पूर्ण

	अगर (pdata->disable_otg_घड़ी_gating)
		mvotg->घड़ी_gating = 0;

	mv_otg_reset(mvotg);
	mv_otg_init_irq(mvotg);

	r = platक्रमm_get_resource(mvotg->pdev, IORESOURCE_IRQ, 0);
	अगर (r == शून्य) अणु
		dev_err(&pdev->dev, "no IRQ resource defined\n");
		retval = -ENODEV;
		जाओ err_disable_clk;
	पूर्ण

	mvotg->irq = r->start;
	अगर (devm_request_irq(&pdev->dev, mvotg->irq, mv_otg_irq, IRQF_SHARED,
			driver_name, mvotg)) अणु
		dev_err(&pdev->dev, "Request irq %d for OTG failed\n",
			mvotg->irq);
		mvotg->irq = 0;
		retval = -ENODEV;
		जाओ err_disable_clk;
	पूर्ण

	retval = usb_add_phy(&mvotg->phy, USB_PHY_TYPE_USB2);
	अगर (retval < 0) अणु
		dev_err(&pdev->dev, "can't register transceiver, %d\n",
			retval);
		जाओ err_disable_clk;
	पूर्ण

	spin_lock_init(&mvotg->wq_lock);
	अगर (spin_trylock(&mvotg->wq_lock)) अणु
		mv_otg_run_state_machine(mvotg, 2 * HZ);
		spin_unlock(&mvotg->wq_lock);
	पूर्ण

	dev_info(&pdev->dev,
		 "successful probe OTG device %s clock gating.\n",
		 mvotg->घड़ी_gating ? "with" : "without");

	वापस 0;

err_disable_clk:
	mv_otg_disable_पूर्णांकernal(mvotg);
err_destroy_workqueue:
	flush_workqueue(mvotg->qwork);
	destroy_workqueue(mvotg->qwork);

	वापस retval;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक mv_otg_suspend(काष्ठा platक्रमm_device *pdev, pm_message_t state)
अणु
	काष्ठा mv_otg *mvotg = platक्रमm_get_drvdata(pdev);

	अगर (mvotg->phy.otg->state != OTG_STATE_B_IDLE) अणु
		dev_info(&pdev->dev,
			 "OTG state is not B_IDLE, it is %d!\n",
			 mvotg->phy.otg->state);
		वापस -EAGAIN;
	पूर्ण

	अगर (!mvotg->घड़ी_gating)
		mv_otg_disable_पूर्णांकernal(mvotg);

	वापस 0;
पूर्ण

अटल पूर्णांक mv_otg_resume(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mv_otg *mvotg = platक्रमm_get_drvdata(pdev);
	u32 otgsc;

	अगर (!mvotg->घड़ी_gating) अणु
		mv_otg_enable_पूर्णांकernal(mvotg);

		otgsc = पढ़ोl(&mvotg->op_regs->otgsc);
		otgsc |= mvotg->irq_en;
		ग_लिखोl(otgsc, &mvotg->op_regs->otgsc);

		अगर (spin_trylock(&mvotg->wq_lock)) अणु
			mv_otg_run_state_machine(mvotg, 0);
			spin_unlock(&mvotg->wq_lock);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver mv_otg_driver = अणु
	.probe = mv_otg_probe,
	.हटाओ = mv_otg_हटाओ,
	.driver = अणु
		   .name = driver_name,
		   .dev_groups = mv_otg_groups,
		   पूर्ण,
#अगर_घोषित CONFIG_PM
	.suspend = mv_otg_suspend,
	.resume = mv_otg_resume,
#पूर्ण_अगर
पूर्ण;
module_platक्रमm_driver(mv_otg_driver);
