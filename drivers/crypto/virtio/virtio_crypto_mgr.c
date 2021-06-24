<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
 /* Management क्रम virtio crypto devices (refer to adf_dev_mgr.c)
  *
  * Copyright 2016 HUAWEI TECHNOLOGIES CO., LTD.
  */

#समावेश <linux/mutex.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>

#समावेश <uapi/linux/virtio_crypto.h>
#समावेश "virtio_crypto_common.h"

अटल LIST_HEAD(virtio_crypto_table);
अटल uपूर्णांक32_t num_devices;

/* The table_lock protects the above global list and num_devices */
अटल DEFINE_MUTEX(table_lock);

#घोषणा VIRTIO_CRYPTO_MAX_DEVICES 32


/*
 * virtcrypto_devmgr_add_dev() - Add vcrypto_dev to the acceleration
 * framework.
 * @vcrypto_dev:  Poपूर्णांकer to virtio crypto device.
 *
 * Function adds virtio crypto device to the global list.
 * To be used by virtio crypto device specअगरic drivers.
 *
 * Return: 0 on success, error code othewise.
 */
पूर्णांक virtcrypto_devmgr_add_dev(काष्ठा virtio_crypto *vcrypto_dev)
अणु
	काष्ठा list_head *itr;

	mutex_lock(&table_lock);
	अगर (num_devices == VIRTIO_CRYPTO_MAX_DEVICES) अणु
		pr_info("virtio_crypto: only support up to %d devices\n",
			    VIRTIO_CRYPTO_MAX_DEVICES);
		mutex_unlock(&table_lock);
		वापस -EFAULT;
	पूर्ण

	list_क्रम_each(itr, &virtio_crypto_table) अणु
		काष्ठा virtio_crypto *ptr =
				list_entry(itr, काष्ठा virtio_crypto, list);

		अगर (ptr == vcrypto_dev) अणु
			mutex_unlock(&table_lock);
			वापस -EEXIST;
		पूर्ण
	पूर्ण
	atomic_set(&vcrypto_dev->ref_count, 0);
	list_add_tail(&vcrypto_dev->list, &virtio_crypto_table);
	vcrypto_dev->dev_id = num_devices++;
	mutex_unlock(&table_lock);
	वापस 0;
पूर्ण

काष्ठा list_head *virtcrypto_devmgr_get_head(व्योम)
अणु
	वापस &virtio_crypto_table;
पूर्ण

/*
 * virtcrypto_devmgr_rm_dev() - Remove vcrypto_dev from the acceleration
 * framework.
 * @vcrypto_dev:  Poपूर्णांकer to virtio crypto device.
 *
 * Function हटाओs virtio crypto device from the acceleration framework.
 * To be used by virtio crypto device specअगरic drivers.
 *
 * Return: व्योम
 */
व्योम virtcrypto_devmgr_rm_dev(काष्ठा virtio_crypto *vcrypto_dev)
अणु
	mutex_lock(&table_lock);
	list_del(&vcrypto_dev->list);
	num_devices--;
	mutex_unlock(&table_lock);
पूर्ण

/*
 * virtcrypto_devmgr_get_first()
 *
 * Function वापसs the first virtio crypto device from the acceleration
 * framework.
 *
 * To be used by virtio crypto device specअगरic drivers.
 *
 * Return: poपूर्णांकer to vcrypto_dev or शून्य अगर not found.
 */
काष्ठा virtio_crypto *virtcrypto_devmgr_get_first(व्योम)
अणु
	काष्ठा virtio_crypto *dev = शून्य;

	mutex_lock(&table_lock);
	अगर (!list_empty(&virtio_crypto_table))
		dev = list_first_entry(&virtio_crypto_table,
					काष्ठा virtio_crypto,
				    list);
	mutex_unlock(&table_lock);
	वापस dev;
पूर्ण

/*
 * virtcrypto_dev_in_use() - Check whether vcrypto_dev is currently in use
 * @vcrypto_dev: Poपूर्णांकer to virtio crypto device.
 *
 * To be used by virtio crypto device specअगरic drivers.
 *
 * Return: 1 when device is in use, 0 otherwise.
 */
पूर्णांक virtcrypto_dev_in_use(काष्ठा virtio_crypto *vcrypto_dev)
अणु
	वापस atomic_पढ़ो(&vcrypto_dev->ref_count) != 0;
पूर्ण

/*
 * virtcrypto_dev_get() - Increment vcrypto_dev reference count
 * @vcrypto_dev: Poपूर्णांकer to virtio crypto device.
 *
 * Increment the vcrypto_dev refcount and अगर this is the first समय
 * incrementing it during this period the vcrypto_dev is in use,
 * increment the module refcount too.
 * To be used by virtio crypto device specअगरic drivers.
 *
 * Return: 0 when successful, EFAULT when fail to bump module refcount
 */
पूर्णांक virtcrypto_dev_get(काष्ठा virtio_crypto *vcrypto_dev)
अणु
	अगर (atomic_add_वापस(1, &vcrypto_dev->ref_count) == 1)
		अगर (!try_module_get(vcrypto_dev->owner))
			वापस -EFAULT;
	वापस 0;
पूर्ण

/*
 * virtcrypto_dev_put() - Decrement vcrypto_dev reference count
 * @vcrypto_dev: Poपूर्णांकer to virtio crypto device.
 *
 * Decrement the vcrypto_dev refcount and अगर this is the last समय
 * decrementing it during this period the vcrypto_dev is in use,
 * decrement the module refcount too.
 * To be used by virtio crypto device specअगरic drivers.
 *
 * Return: व्योम
 */
व्योम virtcrypto_dev_put(काष्ठा virtio_crypto *vcrypto_dev)
अणु
	अगर (atomic_sub_वापस(1, &vcrypto_dev->ref_count) == 0)
		module_put(vcrypto_dev->owner);
पूर्ण

/*
 * virtcrypto_dev_started() - Check whether device has started
 * @vcrypto_dev: Poपूर्णांकer to virtio crypto device.
 *
 * To be used by virtio crypto device specअगरic drivers.
 *
 * Return: 1 when the device has started, 0 otherwise
 */
पूर्णांक virtcrypto_dev_started(काष्ठा virtio_crypto *vcrypto_dev)
अणु
	वापस (vcrypto_dev->status & VIRTIO_CRYPTO_S_HW_READY);
पूर्ण

/*
 * virtcrypto_get_dev_node() - Get vcrypto_dev on the node.
 * @node:  Node id the driver works.
 * @service: Crypto service that needs to be supported by the
 *	      dev
 * @algo: The algorithm number that needs to be supported by the
 *	  dev
 *
 * Function वापसs the virtio crypto device used fewest on the node,
 * and supports the given crypto service and algorithm.
 *
 * To be used by virtio crypto device specअगरic drivers.
 *
 * Return: poपूर्णांकer to vcrypto_dev or शून्य अगर not found.
 */
काष्ठा virtio_crypto *virtcrypto_get_dev_node(पूर्णांक node, uपूर्णांक32_t service,
					      uपूर्णांक32_t algo)
अणु
	काष्ठा virtio_crypto *vcrypto_dev = शून्य, *पंचांगp_dev;
	अचिन्हित दीर्घ best = ~0;
	अचिन्हित दीर्घ ctr;

	mutex_lock(&table_lock);
	list_क्रम_each_entry(पंचांगp_dev, virtcrypto_devmgr_get_head(), list) अणु

		अगर ((node == dev_to_node(&पंचांगp_dev->vdev->dev) ||
		     dev_to_node(&पंचांगp_dev->vdev->dev) < 0) &&
		    virtcrypto_dev_started(पंचांगp_dev) &&
		    virtcrypto_algo_is_supported(पंचांगp_dev, service, algo)) अणु
			ctr = atomic_पढ़ो(&पंचांगp_dev->ref_count);
			अगर (best > ctr) अणु
				vcrypto_dev = पंचांगp_dev;
				best = ctr;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!vcrypto_dev) अणु
		pr_info("virtio_crypto: Could not find a device on node %d\n",
				node);
		/* Get any started device */
		list_क्रम_each_entry(पंचांगp_dev,
				virtcrypto_devmgr_get_head(), list) अणु
			अगर (virtcrypto_dev_started(पंचांगp_dev) &&
			    virtcrypto_algo_is_supported(पंचांगp_dev,
			    service, algo)) अणु
				vcrypto_dev = पंचांगp_dev;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	mutex_unlock(&table_lock);
	अगर (!vcrypto_dev)
		वापस शून्य;

	virtcrypto_dev_get(vcrypto_dev);
	वापस vcrypto_dev;
पूर्ण

/*
 * virtcrypto_dev_start() - Start virtio crypto device
 * @vcrypto:    Poपूर्णांकer to virtio crypto device.
 *
 * Function notअगरies all the रेजिस्टरed services that the virtio crypto device
 * is पढ़ोy to be used.
 * To be used by virtio crypto device specअगरic drivers.
 *
 * Return: 0 on success, EFAULT when fail to रेजिस्टर algorithms
 */
पूर्णांक virtcrypto_dev_start(काष्ठा virtio_crypto *vcrypto)
अणु
	अगर (virtio_crypto_algs_रेजिस्टर(vcrypto)) अणु
		pr_err("virtio_crypto: Failed to register crypto algs\n");
		वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * virtcrypto_dev_stop() - Stop virtio crypto device
 * @vcrypto:    Poपूर्णांकer to virtio crypto device.
 *
 * Function notअगरies all the रेजिस्टरed services that the virtio crypto device
 * is पढ़ोy to be used.
 * To be used by virtio crypto device specअगरic drivers.
 *
 * Return: व्योम
 */
व्योम virtcrypto_dev_stop(काष्ठा virtio_crypto *vcrypto)
अणु
	virtio_crypto_algs_unरेजिस्टर(vcrypto);
पूर्ण

/*
 * vcrypto_algo_is_supported()
 * @vcrypto: Poपूर्णांकer to virtio crypto device.
 * @service: The bit number क्रम service validate.
 *	      See VIRTIO_CRYPTO_SERVICE_*
 * @algo : The bit number क्रम the algorithm to validate.
 *
 *
 * Validate अगर the virtio crypto device supports a service and
 * algo.
 *
 * Return true अगर device supports a service and algo.
 */

bool virtcrypto_algo_is_supported(काष्ठा virtio_crypto *vcrypto,
				  uपूर्णांक32_t service,
				  uपूर्णांक32_t algo)
अणु
	uपूर्णांक32_t service_mask = 1u << service;
	uपूर्णांक32_t algo_mask = 0;
	bool low = true;

	अगर (algo > 31) अणु
		algo -= 32;
		low = false;
	पूर्ण

	अगर (!(vcrypto->crypto_services & service_mask))
		वापस false;

	चयन (service) अणु
	हाल VIRTIO_CRYPTO_SERVICE_CIPHER:
		अगर (low)
			algo_mask = vcrypto->cipher_algo_l;
		अन्यथा
			algo_mask = vcrypto->cipher_algo_h;
		अवरोध;

	हाल VIRTIO_CRYPTO_SERVICE_HASH:
		algo_mask = vcrypto->hash_algo;
		अवरोध;

	हाल VIRTIO_CRYPTO_SERVICE_MAC:
		अगर (low)
			algo_mask = vcrypto->mac_algo_l;
		अन्यथा
			algo_mask = vcrypto->mac_algo_h;
		अवरोध;

	हाल VIRTIO_CRYPTO_SERVICE_AEAD:
		algo_mask = vcrypto->aead_algo;
		अवरोध;
	पूर्ण

	अगर (!(algo_mask & (1u << algo)))
		वापस false;

	वापस true;
पूर्ण
