<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
 /* Driver क्रम Virtio crypto device.
  *
  * Copyright 2016 HUAWEI TECHNOLOGIES CO., LTD.
  */

#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/virtio_config.h>
#समावेश <linux/cpu.h>

#समावेश <uapi/linux/virtio_crypto.h>
#समावेश "virtio_crypto_common.h"


व्योम
virtcrypto_clear_request(काष्ठा virtio_crypto_request *vc_req)
अणु
	अगर (vc_req) अणु
		kमुक्त_sensitive(vc_req->req_data);
		kमुक्त(vc_req->sgs);
	पूर्ण
पूर्ण

अटल व्योम virtcrypto_dataq_callback(काष्ठा virtqueue *vq)
अणु
	काष्ठा virtio_crypto *vcrypto = vq->vdev->priv;
	काष्ठा virtio_crypto_request *vc_req;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक len;
	अचिन्हित पूर्णांक qid = vq->index;

	spin_lock_irqsave(&vcrypto->data_vq[qid].lock, flags);
	करो अणु
		virtqueue_disable_cb(vq);
		जबतक ((vc_req = virtqueue_get_buf(vq, &len)) != शून्य) अणु
			spin_unlock_irqrestore(
				&vcrypto->data_vq[qid].lock, flags);
			अगर (vc_req->alg_cb)
				vc_req->alg_cb(vc_req, len);
			spin_lock_irqsave(
				&vcrypto->data_vq[qid].lock, flags);
		पूर्ण
	पूर्ण जबतक (!virtqueue_enable_cb(vq));
	spin_unlock_irqrestore(&vcrypto->data_vq[qid].lock, flags);
पूर्ण

अटल पूर्णांक virtcrypto_find_vqs(काष्ठा virtio_crypto *vi)
अणु
	vq_callback_t **callbacks;
	काष्ठा virtqueue **vqs;
	पूर्णांक ret = -ENOMEM;
	पूर्णांक i, total_vqs;
	स्थिर अक्षर **names;
	काष्ठा device *dev = &vi->vdev->dev;

	/*
	 * We expect 1 data virtqueue, followed by
	 * possible N-1 data queues used in multiqueue mode,
	 * followed by control vq.
	 */
	total_vqs = vi->max_data_queues + 1;

	/* Allocate space क्रम find_vqs parameters */
	vqs = kसुस्मृति(total_vqs, माप(*vqs), GFP_KERNEL);
	अगर (!vqs)
		जाओ err_vq;
	callbacks = kसुस्मृति(total_vqs, माप(*callbacks), GFP_KERNEL);
	अगर (!callbacks)
		जाओ err_callback;
	names = kसुस्मृति(total_vqs, माप(*names), GFP_KERNEL);
	अगर (!names)
		जाओ err_names;

	/* Parameters क्रम control virtqueue */
	callbacks[total_vqs - 1] = शून्य;
	names[total_vqs - 1] = "controlq";

	/* Allocate/initialize parameters क्रम data virtqueues */
	क्रम (i = 0; i < vi->max_data_queues; i++) अणु
		callbacks[i] = virtcrypto_dataq_callback;
		snम_लिखो(vi->data_vq[i].name, माप(vi->data_vq[i].name),
				"dataq.%d", i);
		names[i] = vi->data_vq[i].name;
	पूर्ण

	ret = virtio_find_vqs(vi->vdev, total_vqs, vqs, callbacks, names, शून्य);
	अगर (ret)
		जाओ err_find;

	vi->ctrl_vq = vqs[total_vqs - 1];

	क्रम (i = 0; i < vi->max_data_queues; i++) अणु
		spin_lock_init(&vi->data_vq[i].lock);
		vi->data_vq[i].vq = vqs[i];
		/* Initialize crypto engine */
		vi->data_vq[i].engine = crypto_engine_alloc_init(dev, 1);
		अगर (!vi->data_vq[i].engine) अणु
			ret = -ENOMEM;
			जाओ err_engine;
		पूर्ण
	पूर्ण

	kमुक्त(names);
	kमुक्त(callbacks);
	kमुक्त(vqs);

	वापस 0;

err_engine:
err_find:
	kमुक्त(names);
err_names:
	kमुक्त(callbacks);
err_callback:
	kमुक्त(vqs);
err_vq:
	वापस ret;
पूर्ण

अटल पूर्णांक virtcrypto_alloc_queues(काष्ठा virtio_crypto *vi)
अणु
	vi->data_vq = kसुस्मृति(vi->max_data_queues, माप(*vi->data_vq),
				GFP_KERNEL);
	अगर (!vi->data_vq)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम virtcrypto_clean_affinity(काष्ठा virtio_crypto *vi, दीर्घ hcpu)
अणु
	पूर्णांक i;

	अगर (vi->affinity_hपूर्णांक_set) अणु
		क्रम (i = 0; i < vi->max_data_queues; i++)
			virtqueue_set_affinity(vi->data_vq[i].vq, शून्य);

		vi->affinity_hपूर्णांक_set = false;
	पूर्ण
पूर्ण

अटल व्योम virtcrypto_set_affinity(काष्ठा virtio_crypto *vcrypto)
अणु
	पूर्णांक i = 0;
	पूर्णांक cpu;

	/*
	 * In single queue mode, we करोn't set the cpu affinity.
	 */
	अगर (vcrypto->curr_queue == 1 || vcrypto->max_data_queues == 1) अणु
		virtcrypto_clean_affinity(vcrypto, -1);
		वापस;
	पूर्ण

	/*
	 * In multiqueue mode, we let the queue to be निजी to one cpu
	 * by setting the affinity hपूर्णांक to eliminate the contention.
	 *
	 * TODO: adds cpu hotplug support by रेजिस्टर cpu notअगरier.
	 *
	 */
	क्रम_each_online_cpu(cpu) अणु
		virtqueue_set_affinity(vcrypto->data_vq[i].vq, cpumask_of(cpu));
		अगर (++i >= vcrypto->max_data_queues)
			अवरोध;
	पूर्ण

	vcrypto->affinity_hपूर्णांक_set = true;
पूर्ण

अटल व्योम virtcrypto_मुक्त_queues(काष्ठा virtio_crypto *vi)
अणु
	kमुक्त(vi->data_vq);
पूर्ण

अटल पूर्णांक virtcrypto_init_vqs(काष्ठा virtio_crypto *vi)
अणु
	पूर्णांक ret;

	/* Allocate send & receive queues */
	ret = virtcrypto_alloc_queues(vi);
	अगर (ret)
		जाओ err;

	ret = virtcrypto_find_vqs(vi);
	अगर (ret)
		जाओ err_मुक्त;

	get_online_cpus();
	virtcrypto_set_affinity(vi);
	put_online_cpus();

	वापस 0;

err_मुक्त:
	virtcrypto_मुक्त_queues(vi);
err:
	वापस ret;
पूर्ण

अटल पूर्णांक virtcrypto_update_status(काष्ठा virtio_crypto *vcrypto)
अणु
	u32 status;
	पूर्णांक err;

	virtio_cपढ़ो_le(vcrypto->vdev,
			काष्ठा virtio_crypto_config, status, &status);

	/*
	 * Unknown status bits would be a host error and the driver
	 * should consider the device to be broken.
	 */
	अगर (status & (~VIRTIO_CRYPTO_S_HW_READY)) अणु
		dev_warn(&vcrypto->vdev->dev,
				"Unknown status bits: 0x%x\n", status);

		virtio_अवरोध_device(vcrypto->vdev);
		वापस -EPERM;
	पूर्ण

	अगर (vcrypto->status == status)
		वापस 0;

	vcrypto->status = status;

	अगर (vcrypto->status & VIRTIO_CRYPTO_S_HW_READY) अणु
		err = virtcrypto_dev_start(vcrypto);
		अगर (err) अणु
			dev_err(&vcrypto->vdev->dev,
				"Failed to start virtio crypto device.\n");

			वापस -EPERM;
		पूर्ण
		dev_info(&vcrypto->vdev->dev, "Accelerator device is ready\n");
	पूर्ण अन्यथा अणु
		virtcrypto_dev_stop(vcrypto);
		dev_info(&vcrypto->vdev->dev, "Accelerator is not ready\n");
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक virtcrypto_start_crypto_engines(काष्ठा virtio_crypto *vcrypto)
अणु
	पूर्णांक32_t i;
	पूर्णांक ret;

	क्रम (i = 0; i < vcrypto->max_data_queues; i++) अणु
		अगर (vcrypto->data_vq[i].engine) अणु
			ret = crypto_engine_start(vcrypto->data_vq[i].engine);
			अगर (ret)
				जाओ err;
		पूर्ण
	पूर्ण

	वापस 0;

err:
	जबतक (--i >= 0)
		अगर (vcrypto->data_vq[i].engine)
			crypto_engine_निकास(vcrypto->data_vq[i].engine);

	वापस ret;
पूर्ण

अटल व्योम virtcrypto_clear_crypto_engines(काष्ठा virtio_crypto *vcrypto)
अणु
	u32 i;

	क्रम (i = 0; i < vcrypto->max_data_queues; i++)
		अगर (vcrypto->data_vq[i].engine)
			crypto_engine_निकास(vcrypto->data_vq[i].engine);
पूर्ण

अटल व्योम virtcrypto_del_vqs(काष्ठा virtio_crypto *vcrypto)
अणु
	काष्ठा virtio_device *vdev = vcrypto->vdev;

	virtcrypto_clean_affinity(vcrypto, -1);

	vdev->config->del_vqs(vdev);

	virtcrypto_मुक्त_queues(vcrypto);
पूर्ण

अटल पूर्णांक virtcrypto_probe(काष्ठा virtio_device *vdev)
अणु
	पूर्णांक err = -EFAULT;
	काष्ठा virtio_crypto *vcrypto;
	u32 max_data_queues = 0, max_cipher_key_len = 0;
	u32 max_auth_key_len = 0;
	u64 max_size = 0;
	u32 cipher_algo_l = 0;
	u32 cipher_algo_h = 0;
	u32 hash_algo = 0;
	u32 mac_algo_l = 0;
	u32 mac_algo_h = 0;
	u32 aead_algo = 0;
	u32 crypto_services = 0;

	अगर (!virtio_has_feature(vdev, VIRTIO_F_VERSION_1))
		वापस -ENODEV;

	अगर (!vdev->config->get) अणु
		dev_err(&vdev->dev, "%s failure: config access disabled\n",
			__func__);
		वापस -EINVAL;
	पूर्ण

	अगर (num_possible_nodes() > 1 && dev_to_node(&vdev->dev) < 0) अणु
		/*
		 * If the accelerator is connected to a node with no memory
		 * there is no poपूर्णांक in using the accelerator since the remote
		 * memory transaction will be very slow.
		 */
		dev_err(&vdev->dev, "Invalid NUMA configuration.\n");
		वापस -EINVAL;
	पूर्ण

	vcrypto = kzalloc_node(माप(*vcrypto), GFP_KERNEL,
					dev_to_node(&vdev->dev));
	अगर (!vcrypto)
		वापस -ENOMEM;

	virtio_cपढ़ो_le(vdev, काष्ठा virtio_crypto_config,
			max_dataqueues, &max_data_queues);
	अगर (max_data_queues < 1)
		max_data_queues = 1;

	virtio_cपढ़ो_le(vdev, काष्ठा virtio_crypto_config,
			max_cipher_key_len, &max_cipher_key_len);
	virtio_cपढ़ो_le(vdev, काष्ठा virtio_crypto_config,
			max_auth_key_len, &max_auth_key_len);
	virtio_cपढ़ो_le(vdev, काष्ठा virtio_crypto_config,
			max_size, &max_size);
	virtio_cपढ़ो_le(vdev, काष्ठा virtio_crypto_config,
			crypto_services, &crypto_services);
	virtio_cपढ़ो_le(vdev, काष्ठा virtio_crypto_config,
			cipher_algo_l, &cipher_algo_l);
	virtio_cपढ़ो_le(vdev, काष्ठा virtio_crypto_config,
			cipher_algo_h, &cipher_algo_h);
	virtio_cपढ़ो_le(vdev, काष्ठा virtio_crypto_config,
			hash_algo, &hash_algo);
	virtio_cपढ़ो_le(vdev, काष्ठा virtio_crypto_config,
			mac_algo_l, &mac_algo_l);
	virtio_cपढ़ो_le(vdev, काष्ठा virtio_crypto_config,
			mac_algo_h, &mac_algo_h);
	virtio_cपढ़ो_le(vdev, काष्ठा virtio_crypto_config,
			aead_algo, &aead_algo);

	/* Add virtio crypto device to global table */
	err = virtcrypto_devmgr_add_dev(vcrypto);
	अगर (err) अणु
		dev_err(&vdev->dev, "Failed to add new virtio crypto device.\n");
		जाओ मुक्त;
	पूर्ण
	vcrypto->owner = THIS_MODULE;
	vcrypto = vdev->priv = vcrypto;
	vcrypto->vdev = vdev;

	spin_lock_init(&vcrypto->ctrl_lock);

	/* Use single data queue as शेष */
	vcrypto->curr_queue = 1;
	vcrypto->max_data_queues = max_data_queues;
	vcrypto->max_cipher_key_len = max_cipher_key_len;
	vcrypto->max_auth_key_len = max_auth_key_len;
	vcrypto->max_size = max_size;
	vcrypto->crypto_services = crypto_services;
	vcrypto->cipher_algo_l = cipher_algo_l;
	vcrypto->cipher_algo_h = cipher_algo_h;
	vcrypto->mac_algo_l = mac_algo_l;
	vcrypto->mac_algo_h = mac_algo_h;
	vcrypto->hash_algo = hash_algo;
	vcrypto->aead_algo = aead_algo;


	dev_info(&vdev->dev,
		"max_queues: %u, max_cipher_key_len: %u, max_auth_key_len: %u, max_size 0x%llx\n",
		vcrypto->max_data_queues,
		vcrypto->max_cipher_key_len,
		vcrypto->max_auth_key_len,
		vcrypto->max_size);

	err = virtcrypto_init_vqs(vcrypto);
	अगर (err) अणु
		dev_err(&vdev->dev, "Failed to initialize vqs.\n");
		जाओ मुक्त_dev;
	पूर्ण

	err = virtcrypto_start_crypto_engines(vcrypto);
	अगर (err)
		जाओ मुक्त_vqs;

	virtio_device_पढ़ोy(vdev);

	err = virtcrypto_update_status(vcrypto);
	अगर (err)
		जाओ मुक्त_engines;

	वापस 0;

मुक्त_engines:
	virtcrypto_clear_crypto_engines(vcrypto);
मुक्त_vqs:
	vcrypto->vdev->config->reset(vdev);
	virtcrypto_del_vqs(vcrypto);
मुक्त_dev:
	virtcrypto_devmgr_rm_dev(vcrypto);
मुक्त:
	kमुक्त(vcrypto);
	वापस err;
पूर्ण

अटल व्योम virtcrypto_मुक्त_unused_reqs(काष्ठा virtio_crypto *vcrypto)
अणु
	काष्ठा virtio_crypto_request *vc_req;
	पूर्णांक i;
	काष्ठा virtqueue *vq;

	क्रम (i = 0; i < vcrypto->max_data_queues; i++) अणु
		vq = vcrypto->data_vq[i].vq;
		जबतक ((vc_req = virtqueue_detach_unused_buf(vq)) != शून्य) अणु
			kमुक्त(vc_req->req_data);
			kमुक्त(vc_req->sgs);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम virtcrypto_हटाओ(काष्ठा virtio_device *vdev)
अणु
	काष्ठा virtio_crypto *vcrypto = vdev->priv;

	dev_info(&vdev->dev, "Start virtcrypto_remove.\n");

	अगर (virtcrypto_dev_started(vcrypto))
		virtcrypto_dev_stop(vcrypto);
	vdev->config->reset(vdev);
	virtcrypto_मुक्त_unused_reqs(vcrypto);
	virtcrypto_clear_crypto_engines(vcrypto);
	virtcrypto_del_vqs(vcrypto);
	virtcrypto_devmgr_rm_dev(vcrypto);
	kमुक्त(vcrypto);
पूर्ण

अटल व्योम virtcrypto_config_changed(काष्ठा virtio_device *vdev)
अणु
	काष्ठा virtio_crypto *vcrypto = vdev->priv;

	virtcrypto_update_status(vcrypto);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक virtcrypto_मुक्तze(काष्ठा virtio_device *vdev)
अणु
	काष्ठा virtio_crypto *vcrypto = vdev->priv;

	vdev->config->reset(vdev);
	virtcrypto_मुक्त_unused_reqs(vcrypto);
	अगर (virtcrypto_dev_started(vcrypto))
		virtcrypto_dev_stop(vcrypto);

	virtcrypto_clear_crypto_engines(vcrypto);
	virtcrypto_del_vqs(vcrypto);
	वापस 0;
पूर्ण

अटल पूर्णांक virtcrypto_restore(काष्ठा virtio_device *vdev)
अणु
	काष्ठा virtio_crypto *vcrypto = vdev->priv;
	पूर्णांक err;

	err = virtcrypto_init_vqs(vcrypto);
	अगर (err)
		वापस err;

	err = virtcrypto_start_crypto_engines(vcrypto);
	अगर (err)
		जाओ मुक्त_vqs;

	virtio_device_पढ़ोy(vdev);

	err = virtcrypto_dev_start(vcrypto);
	अगर (err) अणु
		dev_err(&vdev->dev, "Failed to start virtio crypto device.\n");
		जाओ मुक्त_engines;
	पूर्ण

	वापस 0;

मुक्त_engines:
	virtcrypto_clear_crypto_engines(vcrypto);
मुक्त_vqs:
	vcrypto->vdev->config->reset(vdev);
	virtcrypto_del_vqs(vcrypto);
	वापस err;
पूर्ण
#पूर्ण_अगर

अटल स्थिर अचिन्हित पूर्णांक features[] = अणु
	/* none */
पूर्ण;

अटल स्थिर काष्ठा virtio_device_id id_table[] = अणु
	अणु VIRTIO_ID_CRYPTO, VIRTIO_DEV_ANY_ID पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल काष्ठा virtio_driver virtio_crypto_driver = अणु
	.driver.name         = KBUILD_MODNAME,
	.driver.owner        = THIS_MODULE,
	.feature_table       = features,
	.feature_table_size  = ARRAY_SIZE(features),
	.id_table            = id_table,
	.probe               = virtcrypto_probe,
	.हटाओ              = virtcrypto_हटाओ,
	.config_changed = virtcrypto_config_changed,
#अगर_घोषित CONFIG_PM_SLEEP
	.मुक्तze = virtcrypto_मुक्तze,
	.restore = virtcrypto_restore,
#पूर्ण_अगर
पूर्ण;

module_virtio_driver(virtio_crypto_driver);

MODULE_DEVICE_TABLE(virtio, id_table);
MODULE_DESCRIPTION("virtio crypto device driver");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Gonglei <arei.gonglei@huawei.com>");
