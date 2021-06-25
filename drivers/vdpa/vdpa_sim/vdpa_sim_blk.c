<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * VDPA simulator क्रम block device.
 *
 * Copyright (c) 2020, NVIDIA CORPORATION. All rights reserved.
 * Copyright (c) 2021, Red Hat Inc. All rights reserved.
 *
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/vringh.h>
#समावेश <linux/vdpa.h>
#समावेश <linux/blkdev.h>
#समावेश <uapi/linux/virtio_blk.h>

#समावेश "vdpa_sim.h"

#घोषणा DRV_VERSION  "0.1"
#घोषणा DRV_AUTHOR   "Max Gurtovoy <mgurtovoy@nvidia.com>"
#घोषणा DRV_DESC     "vDPA Device Simulator for block device"
#घोषणा DRV_LICENSE  "GPL v2"

#घोषणा VDPASIM_BLK_FEATURES	(VDPASIM_FEATURES | \
				 (1ULL << VIRTIO_BLK_F_SIZE_MAX) | \
				 (1ULL << VIRTIO_BLK_F_SEG_MAX)  | \
				 (1ULL << VIRTIO_BLK_F_BLK_SIZE) | \
				 (1ULL << VIRTIO_BLK_F_TOPOLOGY) | \
				 (1ULL << VIRTIO_BLK_F_MQ))

#घोषणा VDPASIM_BLK_CAPACITY	0x40000
#घोषणा VDPASIM_BLK_SIZE_MAX	0x1000
#घोषणा VDPASIM_BLK_SEG_MAX	32
#घोषणा VDPASIM_BLK_VQ_NUM	1

अटल अक्षर vdpasim_blk_id[VIRTIO_BLK_ID_BYTES] = "vdpa_blk_sim";

अटल bool vdpasim_blk_check_range(u64 start_sector, माप_प्रकार range_size)
अणु
	u64 range_sectors = range_size >> SECTOR_SHIFT;

	अगर (range_size > VDPASIM_BLK_SIZE_MAX * VDPASIM_BLK_SEG_MAX)
		वापस false;

	अगर (start_sector > VDPASIM_BLK_CAPACITY)
		वापस false;

	अगर (range_sectors > VDPASIM_BLK_CAPACITY - start_sector)
		वापस false;

	वापस true;
पूर्ण

/* Returns 'true' अगर the request is handled (with or without an I/O error)
 * and the status is correctly written in the last byte of the 'in iov',
 * 'false' otherwise.
 */
अटल bool vdpasim_blk_handle_req(काष्ठा vdpasim *vdpasim,
				   काष्ठा vdpasim_virtqueue *vq)
अणु
	माप_प्रकार pushed = 0, to_pull, to_push;
	काष्ठा virtio_blk_outhdr hdr;
	sमाप_प्रकार bytes;
	loff_t offset;
	u64 sector;
	u8 status;
	u32 type;
	पूर्णांक ret;

	ret = vringh_getdesc_iotlb(&vq->vring, &vq->out_iov, &vq->in_iov,
				   &vq->head, GFP_ATOMIC);
	अगर (ret != 1)
		वापस false;

	अगर (vq->out_iov.used < 1 || vq->in_iov.used < 1) अणु
		dev_err(&vdpasim->vdpa.dev, "missing headers - out_iov: %u in_iov %u\n",
			vq->out_iov.used, vq->in_iov.used);
		वापस false;
	पूर्ण

	अगर (vq->in_iov.iov[vq->in_iov.used - 1].iov_len < 1) अणु
		dev_err(&vdpasim->vdpa.dev, "request in header too short\n");
		वापस false;
	पूर्ण

	/* The last byte is the status and we checked अगर the last iov has
	 * enough room क्रम it.
	 */
	to_push = vringh_kiov_length(&vq->in_iov) - 1;

	to_pull = vringh_kiov_length(&vq->out_iov);

	bytes = vringh_iov_pull_iotlb(&vq->vring, &vq->out_iov, &hdr,
				      माप(hdr));
	अगर (bytes != माप(hdr)) अणु
		dev_err(&vdpasim->vdpa.dev, "request out header too short\n");
		वापस false;
	पूर्ण

	to_pull -= bytes;

	type = vdpasim32_to_cpu(vdpasim, hdr.type);
	sector = vdpasim64_to_cpu(vdpasim, hdr.sector);
	offset = sector << SECTOR_SHIFT;
	status = VIRTIO_BLK_S_OK;

	चयन (type) अणु
	हाल VIRTIO_BLK_T_IN:
		अगर (!vdpasim_blk_check_range(sector, to_push)) अणु
			dev_err(&vdpasim->vdpa.dev,
				"reading over the capacity - offset: 0x%llx len: 0x%zx\n",
				offset, to_push);
			status = VIRTIO_BLK_S_IOERR;
			अवरोध;
		पूर्ण

		bytes = vringh_iov_push_iotlb(&vq->vring, &vq->in_iov,
					      vdpasim->buffer + offset,
					      to_push);
		अगर (bytes < 0) अणु
			dev_err(&vdpasim->vdpa.dev,
				"vringh_iov_push_iotlb() error: %zd offset: 0x%llx len: 0x%zx\n",
				bytes, offset, to_push);
			status = VIRTIO_BLK_S_IOERR;
			अवरोध;
		पूर्ण

		pushed += bytes;
		अवरोध;

	हाल VIRTIO_BLK_T_OUT:
		अगर (!vdpasim_blk_check_range(sector, to_pull)) अणु
			dev_err(&vdpasim->vdpa.dev,
				"writing over the capacity - offset: 0x%llx len: 0x%zx\n",
				offset, to_pull);
			status = VIRTIO_BLK_S_IOERR;
			अवरोध;
		पूर्ण

		bytes = vringh_iov_pull_iotlb(&vq->vring, &vq->out_iov,
					      vdpasim->buffer + offset,
					      to_pull);
		अगर (bytes < 0) अणु
			dev_err(&vdpasim->vdpa.dev,
				"vringh_iov_pull_iotlb() error: %zd offset: 0x%llx len: 0x%zx\n",
				bytes, offset, to_pull);
			status = VIRTIO_BLK_S_IOERR;
			अवरोध;
		पूर्ण
		अवरोध;

	हाल VIRTIO_BLK_T_GET_ID:
		bytes = vringh_iov_push_iotlb(&vq->vring, &vq->in_iov,
					      vdpasim_blk_id,
					      VIRTIO_BLK_ID_BYTES);
		अगर (bytes < 0) अणु
			dev_err(&vdpasim->vdpa.dev,
				"vringh_iov_push_iotlb() error: %zd\n", bytes);
			status = VIRTIO_BLK_S_IOERR;
			अवरोध;
		पूर्ण

		pushed += bytes;
		अवरोध;

	शेष:
		dev_warn(&vdpasim->vdpa.dev,
			 "Unsupported request type %d\n", type);
		status = VIRTIO_BLK_S_IOERR;
		अवरोध;
	पूर्ण

	/* If some operations fail, we need to skip the reमुख्यing bytes
	 * to put the status in the last byte
	 */
	अगर (to_push - pushed > 0)
		vringh_kiov_advance(&vq->in_iov, to_push - pushed);

	/* Last byte is the status */
	bytes = vringh_iov_push_iotlb(&vq->vring, &vq->in_iov, &status, 1);
	अगर (bytes != 1)
		वापस false;

	pushed += bytes;

	/* Make sure data is wrote beक्रमe advancing index */
	smp_wmb();

	vringh_complete_iotlb(&vq->vring, vq->head, pushed);

	वापस true;
पूर्ण

अटल व्योम vdpasim_blk_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा vdpasim *vdpasim = container_of(work, काष्ठा vdpasim, work);
	पूर्णांक i;

	spin_lock(&vdpasim->lock);

	अगर (!(vdpasim->status & VIRTIO_CONFIG_S_DRIVER_OK))
		जाओ out;

	क्रम (i = 0; i < VDPASIM_BLK_VQ_NUM; i++) अणु
		काष्ठा vdpasim_virtqueue *vq = &vdpasim->vqs[i];

		अगर (!vq->पढ़ोy)
			जारी;

		जबतक (vdpasim_blk_handle_req(vdpasim, vq)) अणु
			/* Make sure used is visible beक्रमe rasing the पूर्णांकerrupt. */
			smp_wmb();

			local_bh_disable();
			अगर (vringh_need_notअगरy_iotlb(&vq->vring) > 0)
				vringh_notअगरy(&vq->vring);
			local_bh_enable();
		पूर्ण
	पूर्ण
out:
	spin_unlock(&vdpasim->lock);
पूर्ण

अटल व्योम vdpasim_blk_get_config(काष्ठा vdpasim *vdpasim, व्योम *config)
अणु
	काष्ठा virtio_blk_config *blk_config = config;

	स_रखो(config, 0, माप(काष्ठा virtio_blk_config));

	blk_config->capacity = cpu_to_vdpasim64(vdpasim, VDPASIM_BLK_CAPACITY);
	blk_config->size_max = cpu_to_vdpasim32(vdpasim, VDPASIM_BLK_SIZE_MAX);
	blk_config->seg_max = cpu_to_vdpasim32(vdpasim, VDPASIM_BLK_SEG_MAX);
	blk_config->num_queues = cpu_to_vdpasim16(vdpasim, VDPASIM_BLK_VQ_NUM);
	blk_config->min_io_size = cpu_to_vdpasim16(vdpasim, 1);
	blk_config->opt_io_size = cpu_to_vdpasim32(vdpasim, 1);
	blk_config->blk_size = cpu_to_vdpasim32(vdpasim, SECTOR_SIZE);
पूर्ण

अटल व्योम vdpasim_blk_mgmtdev_release(काष्ठा device *dev)
अणु
पूर्ण

अटल काष्ठा device vdpasim_blk_mgmtdev = अणु
	.init_name = "vdpasim_blk",
	.release = vdpasim_blk_mgmtdev_release,
पूर्ण;

अटल पूर्णांक vdpasim_blk_dev_add(काष्ठा vdpa_mgmt_dev *mdev, स्थिर अक्षर *name)
अणु
	काष्ठा vdpasim_dev_attr dev_attr = अणुपूर्ण;
	काष्ठा vdpasim *simdev;
	पूर्णांक ret;

	dev_attr.mgmt_dev = mdev;
	dev_attr.name = name;
	dev_attr.id = VIRTIO_ID_BLOCK;
	dev_attr.supported_features = VDPASIM_BLK_FEATURES;
	dev_attr.nvqs = VDPASIM_BLK_VQ_NUM;
	dev_attr.config_size = माप(काष्ठा virtio_blk_config);
	dev_attr.get_config = vdpasim_blk_get_config;
	dev_attr.work_fn = vdpasim_blk_work;
	dev_attr.buffer_size = VDPASIM_BLK_CAPACITY << SECTOR_SHIFT;

	simdev = vdpasim_create(&dev_attr);
	अगर (IS_ERR(simdev))
		वापस PTR_ERR(simdev);

	ret = _vdpa_रेजिस्टर_device(&simdev->vdpa, VDPASIM_BLK_VQ_NUM);
	अगर (ret)
		जाओ put_dev;

	वापस 0;

put_dev:
	put_device(&simdev->vdpa.dev);
	वापस ret;
पूर्ण

अटल व्योम vdpasim_blk_dev_del(काष्ठा vdpa_mgmt_dev *mdev,
				काष्ठा vdpa_device *dev)
अणु
	काष्ठा vdpasim *simdev = container_of(dev, काष्ठा vdpasim, vdpa);

	_vdpa_unरेजिस्टर_device(&simdev->vdpa);
पूर्ण

अटल स्थिर काष्ठा vdpa_mgmtdev_ops vdpasim_blk_mgmtdev_ops = अणु
	.dev_add = vdpasim_blk_dev_add,
	.dev_del = vdpasim_blk_dev_del
पूर्ण;

अटल काष्ठा virtio_device_id id_table[] = अणु
	अणु VIRTIO_ID_BLOCK, VIRTIO_DEV_ANY_ID पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल काष्ठा vdpa_mgmt_dev mgmt_dev = अणु
	.device = &vdpasim_blk_mgmtdev,
	.id_table = id_table,
	.ops = &vdpasim_blk_mgmtdev_ops,
पूर्ण;

अटल पूर्णांक __init vdpasim_blk_init(व्योम)
अणु
	पूर्णांक ret;

	ret = device_रेजिस्टर(&vdpasim_blk_mgmtdev);
	अगर (ret)
		वापस ret;

	ret = vdpa_mgmtdev_रेजिस्टर(&mgmt_dev);
	अगर (ret)
		जाओ parent_err;

	वापस 0;

parent_err:
	device_unरेजिस्टर(&vdpasim_blk_mgmtdev);
	वापस ret;
पूर्ण

अटल व्योम __निकास vdpasim_blk_निकास(व्योम)
अणु
	vdpa_mgmtdev_unरेजिस्टर(&mgmt_dev);
	device_unरेजिस्टर(&vdpasim_blk_mgmtdev);
पूर्ण

module_init(vdpasim_blk_init)
module_निकास(vdpasim_blk_निकास)

MODULE_VERSION(DRV_VERSION);
MODULE_LICENSE(DRV_LICENSE);
MODULE_AUTHOR(DRV_AUTHOR);
MODULE_DESCRIPTION(DRV_DESC);
