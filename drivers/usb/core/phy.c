<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * A wrapper क्रम multiple PHYs which passes all phy_* function calls to
 * multiple (actual) PHY devices. This is comes handy when initializing
 * all PHYs on a HCD and to keep them all in the same state.
 *
 * Copyright (C) 2018 Martin Blumenstingl <martin.blumenstingl@googlemail.com>
 */

#समावेश <linux/device.h>
#समावेश <linux/list.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/of.h>

#समावेश "phy.h"

काष्ठा usb_phy_roothub अणु
	काष्ठा phy		*phy;
	काष्ठा list_head	list;
पूर्ण;

अटल पूर्णांक usb_phy_roothub_add_phy(काष्ठा device *dev, पूर्णांक index,
				   काष्ठा list_head *list)
अणु
	काष्ठा usb_phy_roothub *roothub_entry;
	काष्ठा phy *phy;

	phy = devm_of_phy_get_by_index(dev, dev->of_node, index);
	अगर (IS_ERR(phy)) अणु
		अगर (PTR_ERR(phy) == -ENODEV)
			वापस 0;
		अन्यथा
			वापस PTR_ERR(phy);
	पूर्ण

	roothub_entry = devm_kzalloc(dev, माप(*roothub_entry), GFP_KERNEL);
	अगर (!roothub_entry)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&roothub_entry->list);

	roothub_entry->phy = phy;

	list_add_tail(&roothub_entry->list, list);

	वापस 0;
पूर्ण

काष्ठा usb_phy_roothub *usb_phy_roothub_alloc(काष्ठा device *dev)
अणु
	काष्ठा usb_phy_roothub *phy_roothub;
	पूर्णांक i, num_phys, err;

	अगर (!IS_ENABLED(CONFIG_GENERIC_PHY))
		वापस शून्य;

	num_phys = of_count_phandle_with_args(dev->of_node, "phys",
					      "#phy-cells");
	अगर (num_phys <= 0)
		वापस शून्य;

	phy_roothub = devm_kzalloc(dev, माप(*phy_roothub), GFP_KERNEL);
	अगर (!phy_roothub)
		वापस ERR_PTR(-ENOMEM);

	INIT_LIST_HEAD(&phy_roothub->list);

	क्रम (i = 0; i < num_phys; i++) अणु
		err = usb_phy_roothub_add_phy(dev, i, &phy_roothub->list);
		अगर (err)
			वापस ERR_PTR(err);
	पूर्ण

	वापस phy_roothub;
पूर्ण
EXPORT_SYMBOL_GPL(usb_phy_roothub_alloc);

पूर्णांक usb_phy_roothub_init(काष्ठा usb_phy_roothub *phy_roothub)
अणु
	काष्ठा usb_phy_roothub *roothub_entry;
	काष्ठा list_head *head;
	पूर्णांक err;

	अगर (!phy_roothub)
		वापस 0;

	head = &phy_roothub->list;

	list_क्रम_each_entry(roothub_entry, head, list) अणु
		err = phy_init(roothub_entry->phy);
		अगर (err)
			जाओ err_निकास_phys;
	पूर्ण

	वापस 0;

err_निकास_phys:
	list_क्रम_each_entry_जारी_reverse(roothub_entry, head, list)
		phy_निकास(roothub_entry->phy);

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(usb_phy_roothub_init);

पूर्णांक usb_phy_roothub_निकास(काष्ठा usb_phy_roothub *phy_roothub)
अणु
	काष्ठा usb_phy_roothub *roothub_entry;
	काष्ठा list_head *head;
	पूर्णांक err, ret = 0;

	अगर (!phy_roothub)
		वापस 0;

	head = &phy_roothub->list;

	list_क्रम_each_entry(roothub_entry, head, list) अणु
		err = phy_निकास(roothub_entry->phy);
		अगर (err)
			ret = err;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(usb_phy_roothub_निकास);

पूर्णांक usb_phy_roothub_set_mode(काष्ठा usb_phy_roothub *phy_roothub,
			     क्रमागत phy_mode mode)
अणु
	काष्ठा usb_phy_roothub *roothub_entry;
	काष्ठा list_head *head;
	पूर्णांक err;

	अगर (!phy_roothub)
		वापस 0;

	head = &phy_roothub->list;

	list_क्रम_each_entry(roothub_entry, head, list) अणु
		err = phy_set_mode(roothub_entry->phy, mode);
		अगर (err)
			जाओ err_out;
	पूर्ण

	वापस 0;

err_out:
	list_क्रम_each_entry_जारी_reverse(roothub_entry, head, list)
		phy_घातer_off(roothub_entry->phy);

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(usb_phy_roothub_set_mode);

पूर्णांक usb_phy_roothub_calibrate(काष्ठा usb_phy_roothub *phy_roothub)
अणु
	काष्ठा usb_phy_roothub *roothub_entry;
	काष्ठा list_head *head;
	पूर्णांक err;

	अगर (!phy_roothub)
		वापस 0;

	head = &phy_roothub->list;

	list_क्रम_each_entry(roothub_entry, head, list) अणु
		err = phy_calibrate(roothub_entry->phy);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(usb_phy_roothub_calibrate);

पूर्णांक usb_phy_roothub_घातer_on(काष्ठा usb_phy_roothub *phy_roothub)
अणु
	काष्ठा usb_phy_roothub *roothub_entry;
	काष्ठा list_head *head;
	पूर्णांक err;

	अगर (!phy_roothub)
		वापस 0;

	head = &phy_roothub->list;

	list_क्रम_each_entry(roothub_entry, head, list) अणु
		err = phy_घातer_on(roothub_entry->phy);
		अगर (err)
			जाओ err_out;
	पूर्ण

	वापस 0;

err_out:
	list_क्रम_each_entry_जारी_reverse(roothub_entry, head, list)
		phy_घातer_off(roothub_entry->phy);

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(usb_phy_roothub_घातer_on);

व्योम usb_phy_roothub_घातer_off(काष्ठा usb_phy_roothub *phy_roothub)
अणु
	काष्ठा usb_phy_roothub *roothub_entry;

	अगर (!phy_roothub)
		वापस;

	list_क्रम_each_entry_reverse(roothub_entry, &phy_roothub->list, list)
		phy_घातer_off(roothub_entry->phy);
पूर्ण
EXPORT_SYMBOL_GPL(usb_phy_roothub_घातer_off);

पूर्णांक usb_phy_roothub_suspend(काष्ठा device *controller_dev,
			    काष्ठा usb_phy_roothub *phy_roothub)
अणु
	usb_phy_roothub_घातer_off(phy_roothub);

	/* keep the PHYs initialized so the device can wake up the प्रणाली */
	अगर (device_may_wakeup(controller_dev))
		वापस 0;

	वापस usb_phy_roothub_निकास(phy_roothub);
पूर्ण
EXPORT_SYMBOL_GPL(usb_phy_roothub_suspend);

पूर्णांक usb_phy_roothub_resume(काष्ठा device *controller_dev,
			   काष्ठा usb_phy_roothub *phy_roothub)
अणु
	पूर्णांक err;

	/* अगर the device can't wake up the प्रणाली _निकास was called */
	अगर (!device_may_wakeup(controller_dev)) अणु
		err = usb_phy_roothub_init(phy_roothub);
		अगर (err)
			वापस err;
	पूर्ण

	err = usb_phy_roothub_घातer_on(phy_roothub);

	/* unकरो _init अगर _घातer_on failed */
	अगर (err && !device_may_wakeup(controller_dev))
		usb_phy_roothub_निकास(phy_roothub);

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(usb_phy_roothub_resume);
