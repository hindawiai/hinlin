<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * drd.c - DesignWare USB2 DRD Controller Dual-role support
 *
 * Copyright (C) 2020 STMicroelectronics
 *
 * Author(s): Amelie Delaunay <amelie.delaunay@st.com>
 */

#समावेश <linux/iopoll.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/usb/role.h>
#समावेश "core.h"

अटल व्योम dwc2_ovr_init(काष्ठा dwc2_hsotg *hsotg)
अणु
	अचिन्हित दीर्घ flags;
	u32 gotgctl;

	spin_lock_irqsave(&hsotg->lock, flags);

	gotgctl = dwc2_पढ़ोl(hsotg, GOTGCTL);
	gotgctl |= GOTGCTL_BVALOEN | GOTGCTL_AVALOEN | GOTGCTL_VBVALOEN;
	gotgctl |= GOTGCTL_DBNCE_FLTR_BYPASS;
	gotgctl &= ~(GOTGCTL_BVALOVAL | GOTGCTL_AVALOVAL | GOTGCTL_VBVALOVAL);
	dwc2_ग_लिखोl(hsotg, gotgctl, GOTGCTL);

	dwc2_क्रमce_mode(hsotg, false);

	spin_unlock_irqrestore(&hsotg->lock, flags);
पूर्ण

अटल पूर्णांक dwc2_ovr_avalid(काष्ठा dwc2_hsotg *hsotg, bool valid)
अणु
	u32 gotgctl = dwc2_पढ़ोl(hsotg, GOTGCTL);

	/* Check अगर A-Session is alपढ़ोy in the right state */
	अगर ((valid && (gotgctl & GOTGCTL_ASESVLD)) ||
	    (!valid && !(gotgctl & GOTGCTL_ASESVLD)))
		वापस -EALREADY;

	अगर (valid)
		gotgctl |= GOTGCTL_AVALOVAL | GOTGCTL_VBVALOVAL;
	अन्यथा
		gotgctl &= ~(GOTGCTL_AVALOVAL | GOTGCTL_VBVALOVAL);
	dwc2_ग_लिखोl(hsotg, gotgctl, GOTGCTL);

	वापस 0;
पूर्ण

अटल पूर्णांक dwc2_ovr_bvalid(काष्ठा dwc2_hsotg *hsotg, bool valid)
अणु
	u32 gotgctl = dwc2_पढ़ोl(hsotg, GOTGCTL);

	/* Check अगर B-Session is alपढ़ोy in the right state */
	अगर ((valid && (gotgctl & GOTGCTL_BSESVLD)) ||
	    (!valid && !(gotgctl & GOTGCTL_BSESVLD)))
		वापस -EALREADY;

	अगर (valid)
		gotgctl |= GOTGCTL_BVALOVAL | GOTGCTL_VBVALOVAL;
	अन्यथा
		gotgctl &= ~(GOTGCTL_BVALOVAL | GOTGCTL_VBVALOVAL);
	dwc2_ग_लिखोl(hsotg, gotgctl, GOTGCTL);

	वापस 0;
पूर्ण

अटल पूर्णांक dwc2_drd_role_sw_set(काष्ठा usb_role_चयन *sw, क्रमागत usb_role role)
अणु
	काष्ठा dwc2_hsotg *hsotg = usb_role_चयन_get_drvdata(sw);
	अचिन्हित दीर्घ flags;
	पूर्णांक alपढ़ोy = 0;

	/* Skip session not in line with dr_mode */
	अगर ((role == USB_ROLE_DEVICE && hsotg->dr_mode == USB_DR_MODE_HOST) ||
	    (role == USB_ROLE_HOST && hsotg->dr_mode == USB_DR_MODE_PERIPHERAL))
		वापस -EINVAL;

#अगर IS_ENABLED(CONFIG_USB_DWC2_PERIPHERAL) || \
	IS_ENABLED(CONFIG_USB_DWC2_DUAL_ROLE)
	/* Skip session अगर core is in test mode */
	अगर (role == USB_ROLE_NONE && hsotg->test_mode) अणु
		dev_dbg(hsotg->dev, "Core is in test mode\n");
		वापस -EBUSY;
	पूर्ण
#पूर्ण_अगर

	spin_lock_irqsave(&hsotg->lock, flags);

	अगर (role == USB_ROLE_HOST) अणु
		alपढ़ोy = dwc2_ovr_avalid(hsotg, true);
	पूर्ण अन्यथा अगर (role == USB_ROLE_DEVICE) अणु
		alपढ़ोy = dwc2_ovr_bvalid(hsotg, true);
		/* This clear DCTL.SFTDISCON bit */
		dwc2_hsotg_core_connect(hsotg);
	पूर्ण अन्यथा अणु
		अगर (dwc2_is_device_mode(hsotg)) अणु
			अगर (!dwc2_ovr_bvalid(hsotg, false))
				/* This set DCTL.SFTDISCON bit */
				dwc2_hsotg_core_disconnect(hsotg);
		पूर्ण अन्यथा अणु
			dwc2_ovr_avalid(hsotg, false);
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&hsotg->lock, flags);

	अगर (!alपढ़ोy && hsotg->dr_mode == USB_DR_MODE_OTG)
		/* This will उठाओ a Connector ID Status Change Interrupt */
		dwc2_क्रमce_mode(hsotg, role == USB_ROLE_HOST);

	dev_dbg(hsotg->dev, "%s-session valid\n",
		role == USB_ROLE_NONE ? "No" :
		role == USB_ROLE_HOST ? "A" : "B");

	वापस 0;
पूर्ण

पूर्णांक dwc2_drd_init(काष्ठा dwc2_hsotg *hsotg)
अणु
	काष्ठा usb_role_चयन_desc role_sw_desc = अणु0पूर्ण;
	काष्ठा usb_role_चयन *role_sw;
	पूर्णांक ret;

	अगर (!device_property_पढ़ो_bool(hsotg->dev, "usb-role-switch"))
		वापस 0;

	role_sw_desc.driver_data = hsotg;
	role_sw_desc.fwnode = dev_fwnode(hsotg->dev);
	role_sw_desc.set = dwc2_drd_role_sw_set;
	role_sw_desc.allow_userspace_control = true;

	role_sw = usb_role_चयन_रेजिस्टर(hsotg->dev, &role_sw_desc);
	अगर (IS_ERR(role_sw)) अणु
		ret = PTR_ERR(role_sw);
		dev_err(hsotg->dev,
			"failed to register role switch: %d\n", ret);
		वापस ret;
	पूर्ण

	hsotg->role_sw = role_sw;

	/* Enable override and initialize values */
	dwc2_ovr_init(hsotg);

	वापस 0;
पूर्ण

व्योम dwc2_drd_suspend(काष्ठा dwc2_hsotg *hsotg)
अणु
	u32 gपूर्णांकsts, gपूर्णांकmsk;

	अगर (hsotg->role_sw && !hsotg->params.बाह्यal_id_pin_ctl) अणु
		gपूर्णांकmsk = dwc2_पढ़ोl(hsotg, GINTMSK);
		gपूर्णांकmsk &= ~GINTSTS_CONIDSTSCHNG;
		dwc2_ग_लिखोl(hsotg, gपूर्णांकmsk, GINTMSK);
		gपूर्णांकsts = dwc2_पढ़ोl(hsotg, GINTSTS);
		dwc2_ग_लिखोl(hsotg, gपूर्णांकsts | GINTSTS_CONIDSTSCHNG, GINTSTS);
	पूर्ण
पूर्ण

व्योम dwc2_drd_resume(काष्ठा dwc2_hsotg *hsotg)
अणु
	u32 gपूर्णांकsts, gपूर्णांकmsk;

	अगर (hsotg->role_sw && !hsotg->params.बाह्यal_id_pin_ctl) अणु
		gपूर्णांकsts = dwc2_पढ़ोl(hsotg, GINTSTS);
		dwc2_ग_लिखोl(hsotg, gपूर्णांकsts | GINTSTS_CONIDSTSCHNG, GINTSTS);
		gपूर्णांकmsk = dwc2_पढ़ोl(hsotg, GINTMSK);
		gपूर्णांकmsk |= GINTSTS_CONIDSTSCHNG;
		dwc2_ग_लिखोl(hsotg, gपूर्णांकmsk, GINTMSK);
	पूर्ण
पूर्ण

व्योम dwc2_drd_निकास(काष्ठा dwc2_hsotg *hsotg)
अणु
	अगर (hsotg->role_sw)
		usb_role_चयन_unरेजिस्टर(hsotg->role_sw);
पूर्ण
