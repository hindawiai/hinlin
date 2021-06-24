<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * VDPA simulator क्रम networking device.
 *
 * Copyright (c) 2020, Red Hat Inc. All rights reserved.
 *     Author: Jason Wang <jasowang@redhat.com>
 *
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/vringh.h>
#समावेश <linux/vdpa.h>
#समावेश <uapi/linux/virtio_net.h>

#समावेश "vdpa_sim.h"

#घोषणा DRV_VERSION  "0.1"
#घोषणा DRV_AUTHOR   "Jason Wang <jasowang@redhat.com>"
#घोषणा DRV_DESC     "vDPA Device Simulator for networking device"
#घोषणा DRV_LICENSE  "GPL v2"

#घोषणा VDPASIM_NET_FEATURES	(VDPASIM_FEATURES | \
				 (1ULL << VIRTIO_NET_F_MAC))

#घोषणा VDPASIM_NET_VQ_NUM	2

अटल अक्षर *macaddr;
module_param(macaddr, अक्षरp, 0);
MODULE_PARM_DESC(macaddr, "Ethernet MAC address");

अटल u8 macaddr_buf[ETH_ALEN];

अटल व्योम vdpasim_net_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा vdpasim *vdpasim = container_of(work, काष्ठा vdpasim, work);
	काष्ठा vdpasim_virtqueue *txq = &vdpasim->vqs[1];
	काष्ठा vdpasim_virtqueue *rxq = &vdpasim->vqs[0];
	sमाप_प्रकार पढ़ो, ग_लिखो;
	माप_प्रकार total_ग_लिखो;
	पूर्णांक pkts = 0;
	पूर्णांक err;

	spin_lock(&vdpasim->lock);

	अगर (!(vdpasim->status & VIRTIO_CONFIG_S_DRIVER_OK))
		जाओ out;

	अगर (!txq->पढ़ोy || !rxq->पढ़ोy)
		जाओ out;

	जबतक (true) अणु
		total_ग_लिखो = 0;
		err = vringh_getdesc_iotlb(&txq->vring, &txq->out_iov, शून्य,
					   &txq->head, GFP_ATOMIC);
		अगर (err <= 0)
			अवरोध;

		err = vringh_getdesc_iotlb(&rxq->vring, शून्य, &rxq->in_iov,
					   &rxq->head, GFP_ATOMIC);
		अगर (err <= 0) अणु
			vringh_complete_iotlb(&txq->vring, txq->head, 0);
			अवरोध;
		पूर्ण

		जबतक (true) अणु
			पढ़ो = vringh_iov_pull_iotlb(&txq->vring, &txq->out_iov,
						     vdpasim->buffer,
						     PAGE_SIZE);
			अगर (पढ़ो <= 0)
				अवरोध;

			ग_लिखो = vringh_iov_push_iotlb(&rxq->vring, &rxq->in_iov,
						      vdpasim->buffer, पढ़ो);
			अगर (ग_लिखो <= 0)
				अवरोध;

			total_ग_लिखो += ग_लिखो;
		पूर्ण

		/* Make sure data is wrote beक्रमe advancing index */
		smp_wmb();

		vringh_complete_iotlb(&txq->vring, txq->head, 0);
		vringh_complete_iotlb(&rxq->vring, rxq->head, total_ग_लिखो);

		/* Make sure used is visible beक्रमe rasing the पूर्णांकerrupt. */
		smp_wmb();

		local_bh_disable();
		अगर (vringh_need_notअगरy_iotlb(&txq->vring) > 0)
			vringh_notअगरy(&txq->vring);
		अगर (vringh_need_notअगरy_iotlb(&rxq->vring) > 0)
			vringh_notअगरy(&rxq->vring);
		local_bh_enable();

		अगर (++pkts > 4) अणु
			schedule_work(&vdpasim->work);
			जाओ out;
		पूर्ण
	पूर्ण

out:
	spin_unlock(&vdpasim->lock);
पूर्ण

अटल व्योम vdpasim_net_get_config(काष्ठा vdpasim *vdpasim, व्योम *config)
अणु
	काष्ठा virtio_net_config *net_config = config;

	net_config->mtu = cpu_to_vdpasim16(vdpasim, 1500);
	net_config->status = cpu_to_vdpasim16(vdpasim, VIRTIO_NET_S_LINK_UP);
	स_नकल(net_config->mac, macaddr_buf, ETH_ALEN);
पूर्ण

अटल व्योम vdpasim_net_mgmtdev_release(काष्ठा device *dev)
अणु
पूर्ण

अटल काष्ठा device vdpasim_net_mgmtdev = अणु
	.init_name = "vdpasim_net",
	.release = vdpasim_net_mgmtdev_release,
पूर्ण;

अटल पूर्णांक vdpasim_net_dev_add(काष्ठा vdpa_mgmt_dev *mdev, स्थिर अक्षर *name)
अणु
	काष्ठा vdpasim_dev_attr dev_attr = अणुपूर्ण;
	काष्ठा vdpasim *simdev;
	पूर्णांक ret;

	dev_attr.mgmt_dev = mdev;
	dev_attr.name = name;
	dev_attr.id = VIRTIO_ID_NET;
	dev_attr.supported_features = VDPASIM_NET_FEATURES;
	dev_attr.nvqs = VDPASIM_NET_VQ_NUM;
	dev_attr.config_size = माप(काष्ठा virtio_net_config);
	dev_attr.get_config = vdpasim_net_get_config;
	dev_attr.work_fn = vdpasim_net_work;
	dev_attr.buffer_size = PAGE_SIZE;

	simdev = vdpasim_create(&dev_attr);
	अगर (IS_ERR(simdev))
		वापस PTR_ERR(simdev);

	ret = _vdpa_रेजिस्टर_device(&simdev->vdpa, VDPASIM_NET_VQ_NUM);
	अगर (ret)
		जाओ reg_err;

	वापस 0;

reg_err:
	put_device(&simdev->vdpa.dev);
	वापस ret;
पूर्ण

अटल व्योम vdpasim_net_dev_del(काष्ठा vdpa_mgmt_dev *mdev,
				काष्ठा vdpa_device *dev)
अणु
	काष्ठा vdpasim *simdev = container_of(dev, काष्ठा vdpasim, vdpa);

	_vdpa_unरेजिस्टर_device(&simdev->vdpa);
पूर्ण

अटल स्थिर काष्ठा vdpa_mgmtdev_ops vdpasim_net_mgmtdev_ops = अणु
	.dev_add = vdpasim_net_dev_add,
	.dev_del = vdpasim_net_dev_del
पूर्ण;

अटल काष्ठा virtio_device_id id_table[] = अणु
	अणु VIRTIO_ID_NET, VIRTIO_DEV_ANY_ID पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल काष्ठा vdpa_mgmt_dev mgmt_dev = अणु
	.device = &vdpasim_net_mgmtdev,
	.id_table = id_table,
	.ops = &vdpasim_net_mgmtdev_ops,
पूर्ण;

अटल पूर्णांक __init vdpasim_net_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (macaddr) अणु
		mac_pton(macaddr, macaddr_buf);
		अगर (!is_valid_ether_addr(macaddr_buf))
			वापस -EADDRNOTAVAIL;
	पूर्ण अन्यथा अणु
		eth_अक्रमom_addr(macaddr_buf);
	पूर्ण

	ret = device_रेजिस्टर(&vdpasim_net_mgmtdev);
	अगर (ret)
		वापस ret;

	ret = vdpa_mgmtdev_रेजिस्टर(&mgmt_dev);
	अगर (ret)
		जाओ parent_err;
	वापस 0;

parent_err:
	device_unरेजिस्टर(&vdpasim_net_mgmtdev);
	वापस ret;
पूर्ण

अटल व्योम __निकास vdpasim_net_निकास(व्योम)
अणु
	vdpa_mgmtdev_unरेजिस्टर(&mgmt_dev);
	device_unरेजिस्टर(&vdpasim_net_mgmtdev);
पूर्ण

module_init(vdpasim_net_init);
module_निकास(vdpasim_net_निकास);

MODULE_VERSION(DRV_VERSION);
MODULE_LICENSE(DRV_LICENSE);
MODULE_AUTHOR(DRV_AUTHOR);
MODULE_DESCRIPTION(DRV_DESC);
