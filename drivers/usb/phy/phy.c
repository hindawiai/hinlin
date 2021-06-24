<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * phy.c -- USB phy handling
 *
 * Copyright (C) 2004-2013 Texas Instruments
 */
#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/err.h>
#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>

#समावेश <linux/usb/phy.h>

/* Default current range by अक्षरger type. */
#घोषणा DEFAULT_SDP_CUR_MIN	2
#घोषणा DEFAULT_SDP_CUR_MAX	500
#घोषणा DEFAULT_SDP_CUR_MIN_SS	150
#घोषणा DEFAULT_SDP_CUR_MAX_SS	900
#घोषणा DEFAULT_DCP_CUR_MIN	500
#घोषणा DEFAULT_DCP_CUR_MAX	5000
#घोषणा DEFAULT_CDP_CUR_MIN	1500
#घोषणा DEFAULT_CDP_CUR_MAX	5000
#घोषणा DEFAULT_ACA_CUR_MIN	1500
#घोषणा DEFAULT_ACA_CUR_MAX	5000

अटल LIST_HEAD(phy_list);
अटल DEFINE_SPINLOCK(phy_lock);

काष्ठा phy_devm अणु
	काष्ठा usb_phy *phy;
	काष्ठा notअगरier_block *nb;
पूर्ण;

अटल स्थिर अक्षर *स्थिर usb_chger_type[] = अणु
	[UNKNOWN_TYPE]			= "USB_CHARGER_UNKNOWN_TYPE",
	[SDP_TYPE]			= "USB_CHARGER_SDP_TYPE",
	[CDP_TYPE]			= "USB_CHARGER_CDP_TYPE",
	[DCP_TYPE]			= "USB_CHARGER_DCP_TYPE",
	[ACA_TYPE]			= "USB_CHARGER_ACA_TYPE",
पूर्ण;

अटल काष्ठा usb_phy *__usb_find_phy(काष्ठा list_head *list,
	क्रमागत usb_phy_type type)
अणु
	काष्ठा usb_phy  *phy = शून्य;

	list_क्रम_each_entry(phy, list, head) अणु
		अगर (phy->type != type)
			जारी;

		वापस phy;
	पूर्ण

	वापस ERR_PTR(-ENODEV);
पूर्ण

अटल काष्ठा usb_phy *__of_usb_find_phy(काष्ठा device_node *node)
अणु
	काष्ठा usb_phy  *phy;

	अगर (!of_device_is_available(node))
		वापस ERR_PTR(-ENODEV);

	list_क्रम_each_entry(phy, &phy_list, head) अणु
		अगर (node != phy->dev->of_node)
			जारी;

		वापस phy;
	पूर्ण

	वापस ERR_PTR(-EPROBE_DEFER);
पूर्ण

अटल व्योम usb_phy_set_शेष_current(काष्ठा usb_phy *usb_phy)
अणु
	usb_phy->chg_cur.sdp_min = DEFAULT_SDP_CUR_MIN;
	usb_phy->chg_cur.sdp_max = DEFAULT_SDP_CUR_MAX;
	usb_phy->chg_cur.dcp_min = DEFAULT_DCP_CUR_MIN;
	usb_phy->chg_cur.dcp_max = DEFAULT_DCP_CUR_MAX;
	usb_phy->chg_cur.cdp_min = DEFAULT_CDP_CUR_MIN;
	usb_phy->chg_cur.cdp_max = DEFAULT_CDP_CUR_MAX;
	usb_phy->chg_cur.aca_min = DEFAULT_ACA_CUR_MIN;
	usb_phy->chg_cur.aca_max = DEFAULT_ACA_CUR_MAX;
पूर्ण

/**
 * usb_phy_notअगरy_अक्षरger_work - notअगरy the USB अक्षरger state
 * @work: the अक्षरger work to notअगरy the USB अक्षरger state
 *
 * This work can be issued when USB अक्षरger state has been changed or
 * USB अक्षरger current has been changed, then we can notअगरy the current
 * what can be drawn to घातer user and the अक्षरger state to userspace.
 *
 * If we get the अक्षरger type from extcon subप्रणाली, we can notअगरy the
 * अक्षरger state to घातer user स्वतःmatically by usb_phy_get_अक्षरger_type()
 * issuing from extcon subप्रणाली.
 *
 * If we get the अक्षरger type from ->अक्षरger_detect() instead of extcon
 * subप्रणाली, the usb phy driver should issue usb_phy_set_अक्षरger_state()
 * to set अक्षरger state when the अक्षरger state has been changed.
 */
अटल व्योम usb_phy_notअगरy_अक्षरger_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा usb_phy *usb_phy = container_of(work, काष्ठा usb_phy, chg_work);
	अक्षर uchger_state[50] = अणु 0 पूर्ण;
	अक्षर uchger_type[50] = अणु 0 पूर्ण;
	अक्षर *envp[] = अणु uchger_state, uchger_type, शून्य पूर्ण;
	अचिन्हित पूर्णांक min, max;

	चयन (usb_phy->chg_state) अणु
	हाल USB_CHARGER_PRESENT:
		usb_phy_get_अक्षरger_current(usb_phy, &min, &max);

		atomic_notअगरier_call_chain(&usb_phy->notअगरier, max, usb_phy);
		snम_लिखो(uchger_state, ARRAY_SIZE(uchger_state),
			 "USB_CHARGER_STATE=%s", "USB_CHARGER_PRESENT");
		अवरोध;
	हाल USB_CHARGER_ABSENT:
		usb_phy_set_शेष_current(usb_phy);

		atomic_notअगरier_call_chain(&usb_phy->notअगरier, 0, usb_phy);
		snम_लिखो(uchger_state, ARRAY_SIZE(uchger_state),
			 "USB_CHARGER_STATE=%s", "USB_CHARGER_ABSENT");
		अवरोध;
	शेष:
		dev_warn(usb_phy->dev, "Unknown USB charger state: %d\n",
			 usb_phy->chg_state);
		वापस;
	पूर्ण

	snम_लिखो(uchger_type, ARRAY_SIZE(uchger_type),
		 "USB_CHARGER_TYPE=%s", usb_chger_type[usb_phy->chg_type]);
	kobject_uevent_env(&usb_phy->dev->kobj, KOBJ_CHANGE, envp);
पूर्ण

अटल व्योम __usb_phy_get_अक्षरger_type(काष्ठा usb_phy *usb_phy)
अणु
	अगर (extcon_get_state(usb_phy->edev, EXTCON_CHG_USB_SDP) > 0) अणु
		usb_phy->chg_type = SDP_TYPE;
		usb_phy->chg_state = USB_CHARGER_PRESENT;
	पूर्ण अन्यथा अगर (extcon_get_state(usb_phy->edev, EXTCON_CHG_USB_CDP) > 0) अणु
		usb_phy->chg_type = CDP_TYPE;
		usb_phy->chg_state = USB_CHARGER_PRESENT;
	पूर्ण अन्यथा अगर (extcon_get_state(usb_phy->edev, EXTCON_CHG_USB_DCP) > 0) अणु
		usb_phy->chg_type = DCP_TYPE;
		usb_phy->chg_state = USB_CHARGER_PRESENT;
	पूर्ण अन्यथा अगर (extcon_get_state(usb_phy->edev, EXTCON_CHG_USB_ACA) > 0) अणु
		usb_phy->chg_type = ACA_TYPE;
		usb_phy->chg_state = USB_CHARGER_PRESENT;
	पूर्ण अन्यथा अणु
		usb_phy->chg_type = UNKNOWN_TYPE;
		usb_phy->chg_state = USB_CHARGER_ABSENT;
	पूर्ण

	schedule_work(&usb_phy->chg_work);
पूर्ण

/**
 * usb_phy_get_अक्षरger_type - get अक्षरger type from extcon subप्रणाली
 * @nb: the notअगरier block to determine अक्षरger type
 * @state: the cable state
 * @data: निजी data
 *
 * Determin the अक्षरger type from extcon subप्रणाली which also means the
 * अक्षरger state has been chaned, then we should notअगरy this event.
 */
अटल पूर्णांक usb_phy_get_अक्षरger_type(काष्ठा notअगरier_block *nb,
				    अचिन्हित दीर्घ state, व्योम *data)
अणु
	काष्ठा usb_phy *usb_phy = container_of(nb, काष्ठा usb_phy, type_nb);

	__usb_phy_get_अक्षरger_type(usb_phy);
	वापस NOTIFY_OK;
पूर्ण

/**
 * usb_phy_set_अक्षरger_current - set the USB अक्षरger current
 * @usb_phy: the USB phy to be used
 * @mA: the current need to be set
 *
 * Usually we only change the अक्षरger शेष current when USB finished the
 * क्रमागतeration as one SDP अक्षरger. As one SDP अक्षरger, usb_phy_set_घातer()
 * will issue this function to change अक्षरger current when after setting USB
 * configuration, or suspend/resume USB. For other type अक्षरger, we should
 * use the शेष अक्षरger current and we करो not suggest to issue this function
 * to change the अक्षरger current.
 *
 * When USB अक्षरger current has been changed, we need to notअगरy the घातer users.
 */
व्योम usb_phy_set_अक्षरger_current(काष्ठा usb_phy *usb_phy, अचिन्हित पूर्णांक mA)
अणु
	चयन (usb_phy->chg_type) अणु
	हाल SDP_TYPE:
		अगर (usb_phy->chg_cur.sdp_max == mA)
			वापस;

		usb_phy->chg_cur.sdp_max = (mA > DEFAULT_SDP_CUR_MAX_SS) ?
			DEFAULT_SDP_CUR_MAX_SS : mA;
		अवरोध;
	हाल DCP_TYPE:
		अगर (usb_phy->chg_cur.dcp_max == mA)
			वापस;

		usb_phy->chg_cur.dcp_max = (mA > DEFAULT_DCP_CUR_MAX) ?
			DEFAULT_DCP_CUR_MAX : mA;
		अवरोध;
	हाल CDP_TYPE:
		अगर (usb_phy->chg_cur.cdp_max == mA)
			वापस;

		usb_phy->chg_cur.cdp_max = (mA > DEFAULT_CDP_CUR_MAX) ?
			DEFAULT_CDP_CUR_MAX : mA;
		अवरोध;
	हाल ACA_TYPE:
		अगर (usb_phy->chg_cur.aca_max == mA)
			वापस;

		usb_phy->chg_cur.aca_max = (mA > DEFAULT_ACA_CUR_MAX) ?
			DEFAULT_ACA_CUR_MAX : mA;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	schedule_work(&usb_phy->chg_work);
पूर्ण
EXPORT_SYMBOL_GPL(usb_phy_set_अक्षरger_current);

/**
 * usb_phy_get_अक्षरger_current - get the USB अक्षरger current
 * @usb_phy: the USB phy to be used
 * @min: the minimum current
 * @max: the maximum current
 *
 * Usually we will notअगरy the maximum current to घातer user, but क्रम some
 * special हाल, घातer user also need the minimum current value. Then the
 * घातer user can issue this function to get the suitable current.
 */
व्योम usb_phy_get_अक्षरger_current(काष्ठा usb_phy *usb_phy,
				 अचिन्हित पूर्णांक *min, अचिन्हित पूर्णांक *max)
अणु
	चयन (usb_phy->chg_type) अणु
	हाल SDP_TYPE:
		*min = usb_phy->chg_cur.sdp_min;
		*max = usb_phy->chg_cur.sdp_max;
		अवरोध;
	हाल DCP_TYPE:
		*min = usb_phy->chg_cur.dcp_min;
		*max = usb_phy->chg_cur.dcp_max;
		अवरोध;
	हाल CDP_TYPE:
		*min = usb_phy->chg_cur.cdp_min;
		*max = usb_phy->chg_cur.cdp_max;
		अवरोध;
	हाल ACA_TYPE:
		*min = usb_phy->chg_cur.aca_min;
		*max = usb_phy->chg_cur.aca_max;
		अवरोध;
	शेष:
		*min = 0;
		*max = 0;
		अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(usb_phy_get_अक्षरger_current);

/**
 * usb_phy_set_अक्षरger_state - set the USB अक्षरger state
 * @usb_phy: the USB phy to be used
 * @state: the new state need to be set क्रम अक्षरger
 *
 * The usb phy driver can issue this function when the usb phy driver
 * detected the अक्षरger state has been changed, in this हाल the अक्षरger
 * type should be get from ->अक्षरger_detect().
 */
व्योम usb_phy_set_अक्षरger_state(काष्ठा usb_phy *usb_phy,
			       क्रमागत usb_अक्षरger_state state)
अणु
	अगर (usb_phy->chg_state == state || !usb_phy->अक्षरger_detect)
		वापस;

	usb_phy->chg_state = state;
	अगर (usb_phy->chg_state == USB_CHARGER_PRESENT)
		usb_phy->chg_type = usb_phy->अक्षरger_detect(usb_phy);
	अन्यथा
		usb_phy->chg_type = UNKNOWN_TYPE;

	schedule_work(&usb_phy->chg_work);
पूर्ण
EXPORT_SYMBOL_GPL(usb_phy_set_अक्षरger_state);

अटल व्योम devm_usb_phy_release(काष्ठा device *dev, व्योम *res)
अणु
	काष्ठा usb_phy *phy = *(काष्ठा usb_phy **)res;

	usb_put_phy(phy);
पूर्ण

अटल व्योम devm_usb_phy_release2(काष्ठा device *dev, व्योम *_res)
अणु
	काष्ठा phy_devm *res = _res;

	अगर (res->nb)
		usb_unरेजिस्टर_notअगरier(res->phy, res->nb);
	usb_put_phy(res->phy);
पूर्ण

अटल पूर्णांक devm_usb_phy_match(काष्ठा device *dev, व्योम *res, व्योम *match_data)
अणु
	काष्ठा usb_phy **phy = res;

	वापस *phy == match_data;
पूर्ण

अटल व्योम usb_अक्षरger_init(काष्ठा usb_phy *usb_phy)
अणु
	usb_phy->chg_type = UNKNOWN_TYPE;
	usb_phy->chg_state = USB_CHARGER_DEFAULT;
	usb_phy_set_शेष_current(usb_phy);
	INIT_WORK(&usb_phy->chg_work, usb_phy_notअगरy_अक्षरger_work);
पूर्ण

अटल पूर्णांक usb_add_extcon(काष्ठा usb_phy *x)
अणु
	पूर्णांक ret;

	अगर (of_property_पढ़ो_bool(x->dev->of_node, "extcon")) अणु
		x->edev = extcon_get_edev_by_phandle(x->dev, 0);
		अगर (IS_ERR(x->edev))
			वापस PTR_ERR(x->edev);

		x->id_edev = extcon_get_edev_by_phandle(x->dev, 1);
		अगर (IS_ERR(x->id_edev)) अणु
			x->id_edev = शून्य;
			dev_info(x->dev, "No separate ID extcon device\n");
		पूर्ण

		अगर (x->vbus_nb.notअगरier_call) अणु
			ret = devm_extcon_रेजिस्टर_notअगरier(x->dev, x->edev,
							    EXTCON_USB,
							    &x->vbus_nb);
			अगर (ret < 0) अणु
				dev_err(x->dev,
					"register VBUS notifier failed\n");
				वापस ret;
			पूर्ण
		पूर्ण अन्यथा अणु
			x->type_nb.notअगरier_call = usb_phy_get_अक्षरger_type;

			ret = devm_extcon_रेजिस्टर_notअगरier(x->dev, x->edev,
							    EXTCON_CHG_USB_SDP,
							    &x->type_nb);
			अगर (ret) अणु
				dev_err(x->dev,
					"register extcon USB SDP failed.\n");
				वापस ret;
			पूर्ण

			ret = devm_extcon_रेजिस्टर_notअगरier(x->dev, x->edev,
							    EXTCON_CHG_USB_CDP,
							    &x->type_nb);
			अगर (ret) अणु
				dev_err(x->dev,
					"register extcon USB CDP failed.\n");
				वापस ret;
			पूर्ण

			ret = devm_extcon_रेजिस्टर_notअगरier(x->dev, x->edev,
							    EXTCON_CHG_USB_DCP,
							    &x->type_nb);
			अगर (ret) अणु
				dev_err(x->dev,
					"register extcon USB DCP failed.\n");
				वापस ret;
			पूर्ण

			ret = devm_extcon_रेजिस्टर_notअगरier(x->dev, x->edev,
							    EXTCON_CHG_USB_ACA,
							    &x->type_nb);
			अगर (ret) अणु
				dev_err(x->dev,
					"register extcon USB ACA failed.\n");
				वापस ret;
			पूर्ण
		पूर्ण

		अगर (x->id_nb.notअगरier_call) अणु
			काष्ठा extcon_dev *id_ext;

			अगर (x->id_edev)
				id_ext = x->id_edev;
			अन्यथा
				id_ext = x->edev;

			ret = devm_extcon_रेजिस्टर_notअगरier(x->dev, id_ext,
							    EXTCON_USB_HOST,
							    &x->id_nb);
			अगर (ret < 0) अणु
				dev_err(x->dev,
					"register ID notifier failed\n");
				वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (x->type_nb.notअगरier_call)
		__usb_phy_get_अक्षरger_type(x);

	वापस 0;
पूर्ण

/**
 * devm_usb_get_phy - find the USB PHY
 * @dev: device that requests this phy
 * @type: the type of the phy the controller requires
 *
 * Gets the phy using usb_get_phy(), and associates a device with it using
 * devres. On driver detach, release function is invoked on the devres data,
 * then, devres data is मुक्तd.
 *
 * For use by USB host and peripheral drivers.
 */
काष्ठा usb_phy *devm_usb_get_phy(काष्ठा device *dev, क्रमागत usb_phy_type type)
अणु
	काष्ठा usb_phy **ptr, *phy;

	ptr = devres_alloc(devm_usb_phy_release, माप(*ptr), GFP_KERNEL);
	अगर (!ptr)
		वापस ERR_PTR(-ENOMEM);

	phy = usb_get_phy(type);
	अगर (!IS_ERR(phy)) अणु
		*ptr = phy;
		devres_add(dev, ptr);
	पूर्ण अन्यथा
		devres_मुक्त(ptr);

	वापस phy;
पूर्ण
EXPORT_SYMBOL_GPL(devm_usb_get_phy);

/**
 * usb_get_phy - find the USB PHY
 * @type: the type of the phy the controller requires
 *
 * Returns the phy driver, after getting a refcount to it; or
 * -ENODEV अगर there is no such phy.  The caller is responsible क्रम
 * calling usb_put_phy() to release that count.
 *
 * For use by USB host and peripheral drivers.
 */
काष्ठा usb_phy *usb_get_phy(क्रमागत usb_phy_type type)
अणु
	काष्ठा usb_phy	*phy = शून्य;
	अचिन्हित दीर्घ	flags;

	spin_lock_irqsave(&phy_lock, flags);

	phy = __usb_find_phy(&phy_list, type);
	अगर (IS_ERR(phy) || !try_module_get(phy->dev->driver->owner)) अणु
		pr_debug("PHY: unable to find transceiver of type %s\n",
			usb_phy_type_string(type));
		अगर (!IS_ERR(phy))
			phy = ERR_PTR(-ENODEV);

		जाओ err0;
	पूर्ण

	get_device(phy->dev);

err0:
	spin_unlock_irqrestore(&phy_lock, flags);

	वापस phy;
पूर्ण
EXPORT_SYMBOL_GPL(usb_get_phy);

/**
 * devm_usb_get_phy_by_node - find the USB PHY by device_node
 * @dev: device that requests this phy
 * @node: the device_node क्रम the phy device.
 * @nb: a notअगरier_block to रेजिस्टर with the phy.
 *
 * Returns the phy driver associated with the given device_node,
 * after getting a refcount to it, -ENODEV अगर there is no such phy or
 * -EPROBE_DEFER अगर the device is not yet loaded. While at that, it
 * also associates the device with
 * the phy using devres. On driver detach, release function is invoked
 * on the devres data, then, devres data is मुक्तd.
 *
 * For use by peripheral drivers क्रम devices related to a phy,
 * such as a अक्षरger.
 */
काष्ठा  usb_phy *devm_usb_get_phy_by_node(काष्ठा device *dev,
					  काष्ठा device_node *node,
					  काष्ठा notअगरier_block *nb)
अणु
	काष्ठा usb_phy	*phy = ERR_PTR(-ENOMEM);
	काष्ठा phy_devm	*ptr;
	अचिन्हित दीर्घ	flags;

	ptr = devres_alloc(devm_usb_phy_release2, माप(*ptr), GFP_KERNEL);
	अगर (!ptr) अणु
		dev_dbg(dev, "failed to allocate memory for devres\n");
		जाओ err0;
	पूर्ण

	spin_lock_irqsave(&phy_lock, flags);

	phy = __of_usb_find_phy(node);
	अगर (IS_ERR(phy)) अणु
		devres_मुक्त(ptr);
		जाओ err1;
	पूर्ण

	अगर (!try_module_get(phy->dev->driver->owner)) अणु
		phy = ERR_PTR(-ENODEV);
		devres_मुक्त(ptr);
		जाओ err1;
	पूर्ण
	अगर (nb)
		usb_रेजिस्टर_notअगरier(phy, nb);
	ptr->phy = phy;
	ptr->nb = nb;
	devres_add(dev, ptr);

	get_device(phy->dev);

err1:
	spin_unlock_irqrestore(&phy_lock, flags);

err0:

	वापस phy;
पूर्ण
EXPORT_SYMBOL_GPL(devm_usb_get_phy_by_node);

/**
 * devm_usb_get_phy_by_phandle - find the USB PHY by phandle
 * @dev: device that requests this phy
 * @phandle: name of the property holding the phy phandle value
 * @index: the index of the phy
 *
 * Returns the phy driver associated with the given phandle value,
 * after getting a refcount to it, -ENODEV अगर there is no such phy or
 * -EPROBE_DEFER अगर there is a phandle to the phy, but the device is
 * not yet loaded. While at that, it also associates the device with
 * the phy using devres. On driver detach, release function is invoked
 * on the devres data, then, devres data is मुक्तd.
 *
 * For use by USB host and peripheral drivers.
 */
काष्ठा usb_phy *devm_usb_get_phy_by_phandle(काष्ठा device *dev,
	स्थिर अक्षर *phandle, u8 index)
अणु
	काष्ठा device_node *node;
	काष्ठा usb_phy	*phy;

	अगर (!dev->of_node) अणु
		dev_dbg(dev, "device does not have a device node entry\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	node = of_parse_phandle(dev->of_node, phandle, index);
	अगर (!node) अणु
		dev_dbg(dev, "failed to get %s phandle in %pOF node\n", phandle,
			dev->of_node);
		वापस ERR_PTR(-ENODEV);
	पूर्ण
	phy = devm_usb_get_phy_by_node(dev, node, शून्य);
	of_node_put(node);
	वापस phy;
पूर्ण
EXPORT_SYMBOL_GPL(devm_usb_get_phy_by_phandle);

/**
 * devm_usb_put_phy - release the USB PHY
 * @dev: device that wants to release this phy
 * @phy: the phy वापसed by devm_usb_get_phy()
 *
 * destroys the devres associated with this phy and invokes usb_put_phy
 * to release the phy.
 *
 * For use by USB host and peripheral drivers.
 */
व्योम devm_usb_put_phy(काष्ठा device *dev, काष्ठा usb_phy *phy)
अणु
	पूर्णांक r;

	r = devres_destroy(dev, devm_usb_phy_release, devm_usb_phy_match, phy);
	dev_WARN_ONCE(dev, r, "couldn't find PHY resource\n");
पूर्ण
EXPORT_SYMBOL_GPL(devm_usb_put_phy);

/**
 * usb_put_phy - release the USB PHY
 * @x: the phy वापसed by usb_get_phy()
 *
 * Releases a refcount the caller received from usb_get_phy().
 *
 * For use by USB host and peripheral drivers.
 */
व्योम usb_put_phy(काष्ठा usb_phy *x)
अणु
	अगर (x) अणु
		काष्ठा module *owner = x->dev->driver->owner;

		put_device(x->dev);
		module_put(owner);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(usb_put_phy);

/**
 * usb_add_phy: declare the USB PHY
 * @x: the USB phy to be used; or शून्य
 * @type: the type of this PHY
 *
 * This call is exclusively क्रम use by phy drivers, which
 * coordinate the activities of drivers क्रम host and peripheral
 * controllers, and in some हालs क्रम VBUS current regulation.
 */
पूर्णांक usb_add_phy(काष्ठा usb_phy *x, क्रमागत usb_phy_type type)
अणु
	पूर्णांक		ret = 0;
	अचिन्हित दीर्घ	flags;
	काष्ठा usb_phy	*phy;

	अगर (x->type != USB_PHY_TYPE_UNDEFINED) अणु
		dev_err(x->dev, "not accepting initialized PHY %s\n", x->label);
		वापस -EINVAL;
	पूर्ण

	usb_अक्षरger_init(x);
	ret = usb_add_extcon(x);
	अगर (ret)
		वापस ret;

	ATOMIC_INIT_NOTIFIER_HEAD(&x->notअगरier);

	spin_lock_irqsave(&phy_lock, flags);

	list_क्रम_each_entry(phy, &phy_list, head) अणु
		अगर (phy->type == type) अणु
			ret = -EBUSY;
			dev_err(x->dev, "transceiver type %s already exists\n",
						usb_phy_type_string(type));
			जाओ out;
		पूर्ण
	पूर्ण

	x->type = type;
	list_add_tail(&x->head, &phy_list);

out:
	spin_unlock_irqrestore(&phy_lock, flags);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(usb_add_phy);

/**
 * usb_add_phy_dev - declare the USB PHY
 * @x: the USB phy to be used; or शून्य
 *
 * This call is exclusively क्रम use by phy drivers, which
 * coordinate the activities of drivers क्रम host and peripheral
 * controllers, and in some हालs क्रम VBUS current regulation.
 */
पूर्णांक usb_add_phy_dev(काष्ठा usb_phy *x)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	अगर (!x->dev) अणु
		dev_err(x->dev, "no device provided for PHY\n");
		वापस -EINVAL;
	पूर्ण

	usb_अक्षरger_init(x);
	ret = usb_add_extcon(x);
	अगर (ret)
		वापस ret;

	ATOMIC_INIT_NOTIFIER_HEAD(&x->notअगरier);

	spin_lock_irqsave(&phy_lock, flags);
	list_add_tail(&x->head, &phy_list);
	spin_unlock_irqrestore(&phy_lock, flags);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(usb_add_phy_dev);

/**
 * usb_हटाओ_phy - हटाओ the OTG PHY
 * @x: the USB OTG PHY to be हटाओd;
 *
 * This reverts the effects of usb_add_phy
 */
व्योम usb_हटाओ_phy(काष्ठा usb_phy *x)
अणु
	अचिन्हित दीर्घ	flags;

	spin_lock_irqsave(&phy_lock, flags);
	अगर (x)
		list_del(&x->head);
	spin_unlock_irqrestore(&phy_lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(usb_हटाओ_phy);

/**
 * usb_phy_set_event - set event to phy event
 * @x: the phy वापसed by usb_get_phy();
 * @event: event to set
 *
 * This sets event to phy event
 */
व्योम usb_phy_set_event(काष्ठा usb_phy *x, अचिन्हित दीर्घ event)
अणु
	x->last_event = event;
पूर्ण
EXPORT_SYMBOL_GPL(usb_phy_set_event);
