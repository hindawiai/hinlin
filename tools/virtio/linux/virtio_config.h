<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#समावेश <linux/virtio_byteorder.h>
#समावेश <linux/virtपन.स>
#समावेश <uapi/linux/virtio_config.h>

/*
 * __virtio_test_bit - helper to test feature bits. For use by transports.
 *                     Devices should normally use virtio_has_feature,
 *                     which includes more checks.
 * @vdev: the device
 * @fbit: the feature bit
 */
अटल अंतरभूत bool __virtio_test_bit(स्थिर काष्ठा virtio_device *vdev,
				     अचिन्हित पूर्णांक fbit)
अणु
	वापस vdev->features & (1ULL << fbit);
पूर्ण

/**
 * __virtio_set_bit - helper to set feature bits. For use by transports.
 * @vdev: the device
 * @fbit: the feature bit
 */
अटल अंतरभूत व्योम __virtio_set_bit(काष्ठा virtio_device *vdev,
				    अचिन्हित पूर्णांक fbit)
अणु
	vdev->features |= (1ULL << fbit);
पूर्ण

/**
 * __virtio_clear_bit - helper to clear feature bits. For use by transports.
 * @vdev: the device
 * @fbit: the feature bit
 */
अटल अंतरभूत व्योम __virtio_clear_bit(काष्ठा virtio_device *vdev,
				      अचिन्हित पूर्णांक fbit)
अणु
	vdev->features &= ~(1ULL << fbit);
पूर्ण

#घोषणा virtio_has_feature(dev, feature) \
	(__virtio_test_bit((dev), feature))

/**
 * virtio_has_dma_quirk - determine whether this device has the DMA quirk
 * @vdev: the device
 */
अटल अंतरभूत bool virtio_has_dma_quirk(स्थिर काष्ठा virtio_device *vdev)
अणु
	/*
	 * Note the reverse polarity of the quirk feature (compared to most
	 * other features), this is क्रम compatibility with legacy प्रणालीs.
	 */
	वापस !virtio_has_feature(vdev, VIRTIO_F_ACCESS_PLATFORM);
पूर्ण

अटल अंतरभूत bool virtio_is_little_endian(काष्ठा virtio_device *vdev)
अणु
	वापस virtio_has_feature(vdev, VIRTIO_F_VERSION_1) ||
		virtio_legacy_is_little_endian();
पूर्ण

/* Memory accessors */
अटल अंतरभूत u16 virtio16_to_cpu(काष्ठा virtio_device *vdev, __virtio16 val)
अणु
	वापस __virtio16_to_cpu(virtio_is_little_endian(vdev), val);
पूर्ण

अटल अंतरभूत __virtio16 cpu_to_virtio16(काष्ठा virtio_device *vdev, u16 val)
अणु
	वापस __cpu_to_virtio16(virtio_is_little_endian(vdev), val);
पूर्ण

अटल अंतरभूत u32 virtio32_to_cpu(काष्ठा virtio_device *vdev, __virtio32 val)
अणु
	वापस __virtio32_to_cpu(virtio_is_little_endian(vdev), val);
पूर्ण

अटल अंतरभूत __virtio32 cpu_to_virtio32(काष्ठा virtio_device *vdev, u32 val)
अणु
	वापस __cpu_to_virtio32(virtio_is_little_endian(vdev), val);
पूर्ण

अटल अंतरभूत u64 virtio64_to_cpu(काष्ठा virtio_device *vdev, __virtio64 val)
अणु
	वापस __virtio64_to_cpu(virtio_is_little_endian(vdev), val);
पूर्ण

अटल अंतरभूत __virtio64 cpu_to_virtio64(काष्ठा virtio_device *vdev, u64 val)
अणु
	वापस __cpu_to_virtio64(virtio_is_little_endian(vdev), val);
पूर्ण
