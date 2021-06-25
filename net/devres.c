<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * This file contains all networking devres helpers.
 */

#समावेश <linux/device.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/netdevice.h>

काष्ठा net_device_devres अणु
	काष्ठा net_device *ndev;
पूर्ण;

अटल व्योम devm_मुक्त_netdev(काष्ठा device *dev, व्योम *this)
अणु
	काष्ठा net_device_devres *res = this;

	मुक्त_netdev(res->ndev);
पूर्ण

काष्ठा net_device *devm_alloc_etherdev_mqs(काष्ठा device *dev, पूर्णांक माप_priv,
					   अचिन्हित पूर्णांक txqs, अचिन्हित पूर्णांक rxqs)
अणु
	काष्ठा net_device_devres *dr;

	dr = devres_alloc(devm_मुक्त_netdev, माप(*dr), GFP_KERNEL);
	अगर (!dr)
		वापस शून्य;

	dr->ndev = alloc_etherdev_mqs(माप_priv, txqs, rxqs);
	अगर (!dr->ndev) अणु
		devres_मुक्त(dr);
		वापस शून्य;
	पूर्ण

	devres_add(dev, dr);

	वापस dr->ndev;
पूर्ण
EXPORT_SYMBOL(devm_alloc_etherdev_mqs);

अटल व्योम devm_unरेजिस्टर_netdev(काष्ठा device *dev, व्योम *this)
अणु
	काष्ठा net_device_devres *res = this;

	unरेजिस्टर_netdev(res->ndev);
पूर्ण

अटल पूर्णांक netdev_devres_match(काष्ठा device *dev, व्योम *this, व्योम *match_data)
अणु
	काष्ठा net_device_devres *res = this;
	काष्ठा net_device *ndev = match_data;

	वापस ndev == res->ndev;
पूर्ण

/**
 *	devm_रेजिस्टर_netdev - resource managed variant of रेजिस्टर_netdev()
 *	@dev: managing device क्रम this netdev - usually the parent device
 *	@ndev: device to रेजिस्टर
 *
 *	This is a devres variant of रेजिस्टर_netdev() क्रम which the unरेजिस्टर
 *	function will be call स्वतःmatically when the managing device is
 *	detached. Note: the net_device used must also be resource managed by
 *	the same काष्ठा device.
 */
पूर्णांक devm_रेजिस्टर_netdev(काष्ठा device *dev, काष्ठा net_device *ndev)
अणु
	काष्ठा net_device_devres *dr;
	पूर्णांक ret;

	/* काष्ठा net_device must itself be managed. For now a managed netdev
	 * can only be allocated by devm_alloc_etherdev_mqs() so the check is
	 * straightक्रमward.
	 */
	अगर (WARN_ON(!devres_find(dev, devm_मुक्त_netdev,
				 netdev_devres_match, ndev)))
		वापस -EINVAL;

	dr = devres_alloc(devm_unरेजिस्टर_netdev, माप(*dr), GFP_KERNEL);
	अगर (!dr)
		वापस -ENOMEM;

	ret = रेजिस्टर_netdev(ndev);
	अगर (ret) अणु
		devres_मुक्त(dr);
		वापस ret;
	पूर्ण

	dr->ndev = ndev;
	devres_add(ndev->dev.parent, dr);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(devm_रेजिस्टर_netdev);
