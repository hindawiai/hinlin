<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * drivers/extcon/devres.c - EXTCON device's resource management
 *
 * Copyright (C) 2016 Samsung Electronics
 * Author: Chanwoo Choi <cw00.choi@samsung.com>
 */

#समावेश "extcon.h"

अटल पूर्णांक devm_extcon_dev_match(काष्ठा device *dev, व्योम *res, व्योम *data)
अणु
	काष्ठा extcon_dev **r = res;

	अगर (WARN_ON(!r || !*r))
		वापस 0;

	वापस *r == data;
पूर्ण

अटल व्योम devm_extcon_dev_release(काष्ठा device *dev, व्योम *res)
अणु
	extcon_dev_मुक्त(*(काष्ठा extcon_dev **)res);
पूर्ण


अटल व्योम devm_extcon_dev_unreg(काष्ठा device *dev, व्योम *res)
अणु
	extcon_dev_unरेजिस्टर(*(काष्ठा extcon_dev **)res);
पूर्ण

काष्ठा extcon_dev_notअगरier_devres अणु
	काष्ठा extcon_dev *edev;
	अचिन्हित पूर्णांक id;
	काष्ठा notअगरier_block *nb;
पूर्ण;

अटल व्योम devm_extcon_dev_notअगरier_unreg(काष्ठा device *dev, व्योम *res)
अणु
	काष्ठा extcon_dev_notअगरier_devres *this = res;

	extcon_unरेजिस्टर_notअगरier(this->edev, this->id, this->nb);
पूर्ण

अटल व्योम devm_extcon_dev_notअगरier_all_unreg(काष्ठा device *dev, व्योम *res)
अणु
	काष्ठा extcon_dev_notअगरier_devres *this = res;

	extcon_unरेजिस्टर_notअगरier_all(this->edev, this->nb);
पूर्ण

/**
 * devm_extcon_dev_allocate - Allocate managed extcon device
 * @dev:		the device owning the extcon device being created
 * @supported_cable:	the array of the supported बाह्यal connectors
 *			ending with EXTCON_NONE.
 *
 * This function manages स्वतःmatically the memory of extcon device using device
 * resource management and simplअगरy the control of मुक्तing the memory of extcon
 * device.
 *
 * Returns the poपूर्णांकer memory of allocated extcon_dev अगर success
 * or ERR_PTR(err) अगर fail
 */
काष्ठा extcon_dev *devm_extcon_dev_allocate(काष्ठा device *dev,
					स्थिर अचिन्हित पूर्णांक *supported_cable)
अणु
	काष्ठा extcon_dev **ptr, *edev;

	ptr = devres_alloc(devm_extcon_dev_release, माप(*ptr), GFP_KERNEL);
	अगर (!ptr)
		वापस ERR_PTR(-ENOMEM);

	edev = extcon_dev_allocate(supported_cable);
	अगर (IS_ERR(edev)) अणु
		devres_मुक्त(ptr);
		वापस edev;
	पूर्ण

	edev->dev.parent = dev;

	*ptr = edev;
	devres_add(dev, ptr);

	वापस edev;
पूर्ण
EXPORT_SYMBOL_GPL(devm_extcon_dev_allocate);

/**
 * devm_extcon_dev_मुक्त() - Resource-managed extcon_dev_unरेजिस्टर()
 * @dev:	the device owning the extcon device being created
 * @edev:	the extcon device to be मुक्तd
 *
 * Free the memory that is allocated with devm_extcon_dev_allocate()
 * function.
 */
व्योम devm_extcon_dev_मुक्त(काष्ठा device *dev, काष्ठा extcon_dev *edev)
अणु
	WARN_ON(devres_release(dev, devm_extcon_dev_release,
			       devm_extcon_dev_match, edev));
पूर्ण
EXPORT_SYMBOL_GPL(devm_extcon_dev_मुक्त);

/**
 * devm_extcon_dev_रेजिस्टर() - Resource-managed extcon_dev_रेजिस्टर()
 * @dev:	the device owning the extcon device being created
 * @edev:	the extcon device to be रेजिस्टरed
 *
 * this function, that extcon device is स्वतःmatically unरेजिस्टरed on driver
 * detach. Internally this function calls extcon_dev_रेजिस्टर() function.
 * To get more inक्रमmation, refer that function.
 *
 * If extcon device is रेजिस्टरed with this function and the device needs to be
 * unरेजिस्टरed separately, devm_extcon_dev_unरेजिस्टर() should be used.
 *
 * Returns 0 अगर success or negaive error number अगर failure.
 */
पूर्णांक devm_extcon_dev_रेजिस्टर(काष्ठा device *dev, काष्ठा extcon_dev *edev)
अणु
	काष्ठा extcon_dev **ptr;
	पूर्णांक ret;

	ptr = devres_alloc(devm_extcon_dev_unreg, माप(*ptr), GFP_KERNEL);
	अगर (!ptr)
		वापस -ENOMEM;

	ret = extcon_dev_रेजिस्टर(edev);
	अगर (ret) अणु
		devres_मुक्त(ptr);
		वापस ret;
	पूर्ण

	*ptr = edev;
	devres_add(dev, ptr);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(devm_extcon_dev_रेजिस्टर);

/**
 * devm_extcon_dev_unरेजिस्टर() - Resource-managed extcon_dev_unरेजिस्टर()
 * @dev:	the device owning the extcon device being created
 * @edev:	the extcon device to unरेजिस्टरed
 *
 * Unरेजिस्टर extcon device that is रेजिस्टरed with devm_extcon_dev_रेजिस्टर()
 * function.
 */
व्योम devm_extcon_dev_unरेजिस्टर(काष्ठा device *dev, काष्ठा extcon_dev *edev)
अणु
	WARN_ON(devres_release(dev, devm_extcon_dev_unreg,
			       devm_extcon_dev_match, edev));
पूर्ण
EXPORT_SYMBOL_GPL(devm_extcon_dev_unरेजिस्टर);

/**
 * devm_extcon_रेजिस्टर_notअगरier() - Resource-managed extcon_रेजिस्टर_notअगरier()
 * @dev:	the device owning the extcon device being created
 * @edev:	the extcon device
 * @id:		the unique id among the extcon क्रमागतeration
 * @nb:		a notअगरier block to be रेजिस्टरed
 *
 * This function manages स्वतःmatically the notअगरier of extcon device using
 * device resource management and simplअगरy the control of unरेजिस्टरing
 * the notअगरier of extcon device.
 *
 * Note that the second parameter given to the callback of nb (val) is
 * "old_state", not the current state. The current state can be retrieved
 * by looking at the third pameter (edev poपूर्णांकer)'s state value.
 *
 * Returns 0 अगर success or negaive error number अगर failure.
 */
पूर्णांक devm_extcon_रेजिस्टर_notअगरier(काष्ठा device *dev, काष्ठा extcon_dev *edev,
				अचिन्हित पूर्णांक id, काष्ठा notअगरier_block *nb)
अणु
	काष्ठा extcon_dev_notअगरier_devres *ptr;
	पूर्णांक ret;

	ptr = devres_alloc(devm_extcon_dev_notअगरier_unreg, माप(*ptr),
				GFP_KERNEL);
	अगर (!ptr)
		वापस -ENOMEM;

	ret = extcon_रेजिस्टर_notअगरier(edev, id, nb);
	अगर (ret) अणु
		devres_मुक्त(ptr);
		वापस ret;
	पूर्ण

	ptr->edev = edev;
	ptr->id = id;
	ptr->nb = nb;
	devres_add(dev, ptr);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(devm_extcon_रेजिस्टर_notअगरier);

/**
 * devm_extcon_unरेजिस्टर_notअगरier()
 *			- Resource-managed extcon_unरेजिस्टर_notअगरier()
 * @dev:	the device owning the extcon device being created
 * @edev:	the extcon device
 * @id:		the unique id among the extcon क्रमागतeration
 * @nb:		a notअगरier block to be रेजिस्टरed
 */
व्योम devm_extcon_unरेजिस्टर_notअगरier(काष्ठा device *dev,
				काष्ठा extcon_dev *edev, अचिन्हित पूर्णांक id,
				काष्ठा notअगरier_block *nb)
अणु
	WARN_ON(devres_release(dev, devm_extcon_dev_notअगरier_unreg,
			       devm_extcon_dev_match, edev));
पूर्ण
EXPORT_SYMBOL(devm_extcon_unरेजिस्टर_notअगरier);

/**
 * devm_extcon_रेजिस्टर_notअगरier_all()
 *		- Resource-managed extcon_रेजिस्टर_notअगरier_all()
 * @dev:	the device owning the extcon device being created
 * @edev:	the extcon device
 * @nb:		a notअगरier block to be रेजिस्टरed
 *
 * This function manages स्वतःmatically the notअगरier of extcon device using
 * device resource management and simplअगरy the control of unरेजिस्टरing
 * the notअगरier of extcon device. To get more inक्रमmation, refer that function.
 *
 * Returns 0 अगर success or negaive error number अगर failure.
 */
पूर्णांक devm_extcon_रेजिस्टर_notअगरier_all(काष्ठा device *dev, काष्ठा extcon_dev *edev,
				काष्ठा notअगरier_block *nb)
अणु
	काष्ठा extcon_dev_notअगरier_devres *ptr;
	पूर्णांक ret;

	ptr = devres_alloc(devm_extcon_dev_notअगरier_all_unreg, माप(*ptr),
				GFP_KERNEL);
	अगर (!ptr)
		वापस -ENOMEM;

	ret = extcon_रेजिस्टर_notअगरier_all(edev, nb);
	अगर (ret) अणु
		devres_मुक्त(ptr);
		वापस ret;
	पूर्ण

	ptr->edev = edev;
	ptr->nb = nb;
	devres_add(dev, ptr);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(devm_extcon_रेजिस्टर_notअगरier_all);

/**
 * devm_extcon_unरेजिस्टर_notअगरier_all()
 *		- Resource-managed extcon_unरेजिस्टर_notअगरier_all()
 * @dev:	the device owning the extcon device being created
 * @edev:	the extcon device
 * @nb:		a notअगरier block to be रेजिस्टरed
 */
व्योम devm_extcon_unरेजिस्टर_notअगरier_all(काष्ठा device *dev,
				काष्ठा extcon_dev *edev,
				काष्ठा notअगरier_block *nb)
अणु
	WARN_ON(devres_release(dev, devm_extcon_dev_notअगरier_all_unreg,
			       devm_extcon_dev_match, edev));
पूर्ण
EXPORT_SYMBOL(devm_extcon_unरेजिस्टर_notअगरier_all);
