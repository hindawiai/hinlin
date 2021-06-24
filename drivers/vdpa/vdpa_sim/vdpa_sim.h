<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2020, Red Hat Inc. All rights reserved.
 */

#अगर_अघोषित _VDPA_SIM_H
#घोषणा _VDPA_SIM_H

#समावेश <linux/iova.h>
#समावेश <linux/vringh.h>
#समावेश <linux/vdpa.h>
#समावेश <linux/virtio_byteorder.h>
#समावेश <linux/vhost_iotlb.h>
#समावेश <uapi/linux/virtio_config.h>

#घोषणा VDPASIM_FEATURES	((1ULL << VIRTIO_F_ANY_LAYOUT) | \
				 (1ULL << VIRTIO_F_VERSION_1)  | \
				 (1ULL << VIRTIO_F_ACCESS_PLATFORM))

काष्ठा vdpasim;

काष्ठा vdpasim_virtqueue अणु
	काष्ठा vringh vring;
	काष्ठा vringh_kiov in_iov;
	काष्ठा vringh_kiov out_iov;
	अचिन्हित लघु head;
	bool पढ़ोy;
	u64 desc_addr;
	u64 device_addr;
	u64 driver_addr;
	u32 num;
	व्योम *निजी;
	irqवापस_t (*cb)(व्योम *data);
पूर्ण;

काष्ठा vdpasim_dev_attr अणु
	काष्ठा vdpa_mgmt_dev *mgmt_dev;
	स्थिर अक्षर *name;
	u64 supported_features;
	माप_प्रकार config_size;
	माप_प्रकार buffer_size;
	पूर्णांक nvqs;
	u32 id;

	work_func_t work_fn;
	व्योम (*get_config)(काष्ठा vdpasim *vdpasim, व्योम *config);
	व्योम (*set_config)(काष्ठा vdpasim *vdpasim, स्थिर व्योम *config);
पूर्ण;

/* State of each vdpasim device */
काष्ठा vdpasim अणु
	काष्ठा vdpa_device vdpa;
	काष्ठा vdpasim_virtqueue *vqs;
	काष्ठा work_काष्ठा work;
	काष्ठा vdpasim_dev_attr dev_attr;
	/* spinlock to synchronize virtqueue state */
	spinlock_t lock;
	/* virtio config according to device type */
	व्योम *config;
	काष्ठा vhost_iotlb *iommu;
	काष्ठा iova_करोमुख्य iova;
	व्योम *buffer;
	u32 status;
	u32 generation;
	u64 features;
	/* spinlock to synchronize iommu table */
	spinlock_t iommu_lock;
पूर्ण;

काष्ठा vdpasim *vdpasim_create(काष्ठा vdpasim_dev_attr *attr);

/* TODO: cross-endian support */
अटल अंतरभूत bool vdpasim_is_little_endian(काष्ठा vdpasim *vdpasim)
अणु
	वापस virtio_legacy_is_little_endian() ||
		(vdpasim->features & (1ULL << VIRTIO_F_VERSION_1));
पूर्ण

अटल अंतरभूत u16 vdpasim16_to_cpu(काष्ठा vdpasim *vdpasim, __virtio16 val)
अणु
	वापस __virtio16_to_cpu(vdpasim_is_little_endian(vdpasim), val);
पूर्ण

अटल अंतरभूत __virtio16 cpu_to_vdpasim16(काष्ठा vdpasim *vdpasim, u16 val)
अणु
	वापस __cpu_to_virtio16(vdpasim_is_little_endian(vdpasim), val);
पूर्ण

अटल अंतरभूत u32 vdpasim32_to_cpu(काष्ठा vdpasim *vdpasim, __virtio32 val)
अणु
	वापस __virtio32_to_cpu(vdpasim_is_little_endian(vdpasim), val);
पूर्ण

अटल अंतरभूत __virtio32 cpu_to_vdpasim32(काष्ठा vdpasim *vdpasim, u32 val)
अणु
	वापस __cpu_to_virtio32(vdpasim_is_little_endian(vdpasim), val);
पूर्ण

अटल अंतरभूत u64 vdpasim64_to_cpu(काष्ठा vdpasim *vdpasim, __virtio64 val)
अणु
	वापस __virtio64_to_cpu(vdpasim_is_little_endian(vdpasim), val);
पूर्ण

अटल अंतरभूत __virtio64 cpu_to_vdpasim64(काष्ठा vdpasim *vdpasim, u64 val)
अणु
	वापस __cpu_to_virtio64(vdpasim_is_little_endian(vdpasim), val);
पूर्ण

#पूर्ण_अगर
