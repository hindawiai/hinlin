<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_VIRTIO_CONFIG_H
#घोषणा _LINUX_VIRTIO_CONFIG_H

#समावेश <linux/err.h>
#समावेश <linux/bug.h>
#समावेश <linux/virtपन.स>
#समावेश <linux/virtio_byteorder.h>
#समावेश <linux/compiler_types.h>
#समावेश <uapi/linux/virtio_config.h>

काष्ठा irq_affinity;

काष्ठा virtio_shm_region अणु
	u64 addr;
	u64 len;
पूर्ण;

/**
 * virtio_config_ops - operations क्रम configuring a virtio device
 * Note: Do not assume that a transport implements all of the operations
 *       getting/setting a value as a simple पढ़ो/ग_लिखो! Generally speaking,
 *       any of @get/@set, @get_status/@set_status, or @get_features/
 *       @finalize_features are NOT safe to be called from an atomic
 *       context.
 * @get: पढ़ो the value of a configuration field
 *	vdev: the virtio_device
 *	offset: the offset of the configuration field
 *	buf: the buffer to ग_लिखो the field value पूर्णांकo.
 *	len: the length of the buffer
 * @set: ग_लिखो the value of a configuration field
 *	vdev: the virtio_device
 *	offset: the offset of the configuration field
 *	buf: the buffer to पढ़ो the field value from.
 *	len: the length of the buffer
 * @generation: config generation counter (optional)
 *	vdev: the virtio_device
 *	Returns the config generation counter
 * @get_status: पढ़ो the status byte
 *	vdev: the virtio_device
 *	Returns the status byte
 * @set_status: ग_लिखो the status byte
 *	vdev: the virtio_device
 *	status: the new status byte
 * @reset: reset the device
 *	vdev: the virtio device
 *	After this, status and feature negotiation must be करोne again
 *	Device must not be reset from its vq/config callbacks, or in
 *	parallel with being added/हटाओd.
 * @find_vqs: find virtqueues and instantiate them.
 *	vdev: the virtio_device
 *	nvqs: the number of virtqueues to find
 *	vqs: on success, includes new virtqueues
 *	callbacks: array of callbacks, क्रम each virtqueue
 *		include a शून्य entry क्रम vqs that करो not need a callback
 *	names: array of virtqueue names (मुख्यly क्रम debugging)
 *		include a शून्य entry क्रम vqs unused by driver
 *	Returns 0 on success or error status
 * @del_vqs: मुक्त virtqueues found by find_vqs().
 * @get_features: get the array of feature bits क्रम this device.
 *	vdev: the virtio_device
 *	Returns the first 64 feature bits (all we currently need).
 * @finalize_features: confirm what device features we'll be using.
 *	vdev: the virtio_device
 *	This gives the final feature bits क्रम the device: it can change
 *	the dev->feature bits अगर it wants.
 *	Returns 0 on success or error status
 * @bus_name: वापस the bus name associated with the device (optional)
 *	vdev: the virtio_device
 *      This वापसs a poपूर्णांकer to the bus name a la pci_name from which
 *      the caller can then copy.
 * @set_vq_affinity: set the affinity क्रम a virtqueue (optional).
 * @get_vq_affinity: get the affinity क्रम a virtqueue (optional).
 * @get_shm_region: get a shared memory region based on the index.
 */
प्रकार व्योम vq_callback_t(काष्ठा virtqueue *);
काष्ठा virtio_config_ops अणु
	व्योम (*get)(काष्ठा virtio_device *vdev, अचिन्हित offset,
		    व्योम *buf, अचिन्हित len);
	व्योम (*set)(काष्ठा virtio_device *vdev, अचिन्हित offset,
		    स्थिर व्योम *buf, अचिन्हित len);
	u32 (*generation)(काष्ठा virtio_device *vdev);
	u8 (*get_status)(काष्ठा virtio_device *vdev);
	व्योम (*set_status)(काष्ठा virtio_device *vdev, u8 status);
	व्योम (*reset)(काष्ठा virtio_device *vdev);
	पूर्णांक (*find_vqs)(काष्ठा virtio_device *, अचिन्हित nvqs,
			काष्ठा virtqueue *vqs[], vq_callback_t *callbacks[],
			स्थिर अक्षर * स्थिर names[], स्थिर bool *ctx,
			काष्ठा irq_affinity *desc);
	व्योम (*del_vqs)(काष्ठा virtio_device *);
	u64 (*get_features)(काष्ठा virtio_device *vdev);
	पूर्णांक (*finalize_features)(काष्ठा virtio_device *vdev);
	स्थिर अक्षर *(*bus_name)(काष्ठा virtio_device *vdev);
	पूर्णांक (*set_vq_affinity)(काष्ठा virtqueue *vq,
			       स्थिर काष्ठा cpumask *cpu_mask);
	स्थिर काष्ठा cpumask *(*get_vq_affinity)(काष्ठा virtio_device *vdev,
			पूर्णांक index);
	bool (*get_shm_region)(काष्ठा virtio_device *vdev,
			       काष्ठा virtio_shm_region *region, u8 id);
पूर्ण;

/* If driver didn't advertise the feature, it will never appear. */
व्योम virtio_check_driver_offered_feature(स्थिर काष्ठा virtio_device *vdev,
					 अचिन्हित पूर्णांक fbit);

/**
 * __virtio_test_bit - helper to test feature bits. For use by transports.
 *                     Devices should normally use virtio_has_feature,
 *                     which includes more checks.
 * @vdev: the device
 * @fbit: the feature bit
 */
अटल अंतरभूत bool __virtio_test_bit(स्थिर काष्ठा virtio_device *vdev,
				     अचिन्हित पूर्णांक fbit)
अणु
	/* Did you क्रमget to fix assumptions on max features? */
	अगर (__builtin_स्थिरant_p(fbit))
		BUILD_BUG_ON(fbit >= 64);
	अन्यथा
		BUG_ON(fbit >= 64);

	वापस vdev->features & BIT_ULL(fbit);
पूर्ण

/**
 * __virtio_set_bit - helper to set feature bits. For use by transports.
 * @vdev: the device
 * @fbit: the feature bit
 */
अटल अंतरभूत व्योम __virtio_set_bit(काष्ठा virtio_device *vdev,
				    अचिन्हित पूर्णांक fbit)
अणु
	/* Did you क्रमget to fix assumptions on max features? */
	अगर (__builtin_स्थिरant_p(fbit))
		BUILD_BUG_ON(fbit >= 64);
	अन्यथा
		BUG_ON(fbit >= 64);

	vdev->features |= BIT_ULL(fbit);
पूर्ण

/**
 * __virtio_clear_bit - helper to clear feature bits. For use by transports.
 * @vdev: the device
 * @fbit: the feature bit
 */
अटल अंतरभूत व्योम __virtio_clear_bit(काष्ठा virtio_device *vdev,
				      अचिन्हित पूर्णांक fbit)
अणु
	/* Did you क्रमget to fix assumptions on max features? */
	अगर (__builtin_स्थिरant_p(fbit))
		BUILD_BUG_ON(fbit >= 64);
	अन्यथा
		BUG_ON(fbit >= 64);

	vdev->features &= ~BIT_ULL(fbit);
पूर्ण

/**
 * virtio_has_feature - helper to determine अगर this device has this feature.
 * @vdev: the device
 * @fbit: the feature bit
 */
अटल अंतरभूत bool virtio_has_feature(स्थिर काष्ठा virtio_device *vdev,
				      अचिन्हित पूर्णांक fbit)
अणु
	अगर (fbit < VIRTIO_TRANSPORT_F_START)
		virtio_check_driver_offered_feature(vdev, fbit);

	वापस __virtio_test_bit(vdev, fbit);
पूर्ण

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

अटल अंतरभूत
काष्ठा virtqueue *virtio_find_single_vq(काष्ठा virtio_device *vdev,
					vq_callback_t *c, स्थिर अक्षर *n)
अणु
	vq_callback_t *callbacks[] = अणु c पूर्ण;
	स्थिर अक्षर *names[] = अणु n पूर्ण;
	काष्ठा virtqueue *vq;
	पूर्णांक err = vdev->config->find_vqs(vdev, 1, &vq, callbacks, names, शून्य,
					 शून्य);
	अगर (err < 0)
		वापस ERR_PTR(err);
	वापस vq;
पूर्ण

अटल अंतरभूत
पूर्णांक virtio_find_vqs(काष्ठा virtio_device *vdev, अचिन्हित nvqs,
			काष्ठा virtqueue *vqs[], vq_callback_t *callbacks[],
			स्थिर अक्षर * स्थिर names[],
			काष्ठा irq_affinity *desc)
अणु
	वापस vdev->config->find_vqs(vdev, nvqs, vqs, callbacks, names, शून्य, desc);
पूर्ण

अटल अंतरभूत
पूर्णांक virtio_find_vqs_ctx(काष्ठा virtio_device *vdev, अचिन्हित nvqs,
			काष्ठा virtqueue *vqs[], vq_callback_t *callbacks[],
			स्थिर अक्षर * स्थिर names[], स्थिर bool *ctx,
			काष्ठा irq_affinity *desc)
अणु
	वापस vdev->config->find_vqs(vdev, nvqs, vqs, callbacks, names, ctx,
				      desc);
पूर्ण

/**
 * virtio_device_पढ़ोy - enable vq use in probe function
 * @vdev: the device
 *
 * Driver must call this to use vqs in the probe function.
 *
 * Note: vqs are enabled स्वतःmatically after probe वापसs.
 */
अटल अंतरभूत
व्योम virtio_device_पढ़ोy(काष्ठा virtio_device *dev)
अणु
	अचिन्हित status = dev->config->get_status(dev);

	BUG_ON(status & VIRTIO_CONFIG_S_DRIVER_OK);
	dev->config->set_status(dev, status | VIRTIO_CONFIG_S_DRIVER_OK);
पूर्ण

अटल अंतरभूत
स्थिर अक्षर *virtio_bus_name(काष्ठा virtio_device *vdev)
अणु
	अगर (!vdev->config->bus_name)
		वापस "virtio";
	वापस vdev->config->bus_name(vdev);
पूर्ण

/**
 * virtqueue_set_affinity - setting affinity क्रम a virtqueue
 * @vq: the virtqueue
 * @cpu: the cpu no.
 *
 * Pay attention the function are best-efक्रमt: the affinity hपूर्णांक may not be set
 * due to config support, irq type and sharing.
 *
 */
अटल अंतरभूत
पूर्णांक virtqueue_set_affinity(काष्ठा virtqueue *vq, स्थिर काष्ठा cpumask *cpu_mask)
अणु
	काष्ठा virtio_device *vdev = vq->vdev;
	अगर (vdev->config->set_vq_affinity)
		वापस vdev->config->set_vq_affinity(vq, cpu_mask);
	वापस 0;
पूर्ण

अटल अंतरभूत
bool virtio_get_shm_region(काष्ठा virtio_device *vdev,
			   काष्ठा virtio_shm_region *region, u8 id)
अणु
	अगर (!vdev->config->get_shm_region)
		वापस false;
	वापस vdev->config->get_shm_region(vdev, region, id);
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

#घोषणा virtio_to_cpu(vdev, x) \
	_Generic((x), \
		__u8: (x), \
		__virtio16: virtio16_to_cpu((vdev), (x)), \
		__virtio32: virtio32_to_cpu((vdev), (x)), \
		__virtio64: virtio64_to_cpu((vdev), (x)) \
		)

#घोषणा cpu_to_virtio(vdev, x, m) \
	_Generic((m), \
		__u8: (x), \
		__virtio16: cpu_to_virtio16((vdev), (x)), \
		__virtio32: cpu_to_virtio32((vdev), (x)), \
		__virtio64: cpu_to_virtio64((vdev), (x)) \
		)

#घोषणा __virtio_native_type(काष्ठाname, member) \
	typeof(virtio_to_cpu(शून्य, ((काष्ठाname*)0)->member))

/* Config space accessors. */
#घोषणा virtio_cपढ़ो(vdev, काष्ठाname, member, ptr)			\
	करो अणु								\
		typeof(((काष्ठाname*)0)->member) virtio_cपढ़ो_v;	\
									\
		might_sleep();						\
		/* Sanity check: must match the member's type */	\
		typecheck(typeof(virtio_to_cpu((vdev), virtio_cपढ़ो_v)), *(ptr)); \
									\
		चयन (माप(virtio_cपढ़ो_v)) अणु			\
		हाल 1:							\
		हाल 2:							\
		हाल 4:							\
			vdev->config->get((vdev), 			\
					  दुरत्व(काष्ठाname, member), \
					  &virtio_cपढ़ो_v,		\
					  माप(virtio_cपढ़ो_v));	\
			अवरोध;						\
		शेष:						\
			__virtio_cपढ़ो_many((vdev), 			\
					  दुरत्व(काष्ठाname, member), \
					  &virtio_cपढ़ो_v,		\
					  1,				\
					  माप(virtio_cपढ़ो_v));	\
			अवरोध;						\
		पूर्ण							\
		*(ptr) = virtio_to_cpu(vdev, virtio_cपढ़ो_v);		\
	पूर्ण जबतक(0)

/* Config space accessors. */
#घोषणा virtio_cग_लिखो(vdev, काष्ठाname, member, ptr)			\
	करो अणु								\
		typeof(((काष्ठाname*)0)->member) virtio_cग_लिखो_v =	\
			cpu_to_virtio(vdev, *(ptr), ((काष्ठाname*)0)->member); \
									\
		might_sleep();						\
		/* Sanity check: must match the member's type */	\
		typecheck(typeof(virtio_to_cpu((vdev), virtio_cग_लिखो_v)), *(ptr)); \
									\
		vdev->config->set((vdev), दुरत्व(काष्ठाname, member),	\
				  &virtio_cग_लिखो_v,			\
				  माप(virtio_cग_लिखो_v));		\
	पूर्ण जबतक(0)

/*
 * Nothing virtio-specअगरic about these, but let's worry about generalizing
 * these later.
 */
#घोषणा virtio_le_to_cpu(x) \
	_Generic((x), \
		__u8: (u8)(x), \
		 __le16: (u16)le16_to_cpu(x), \
		 __le32: (u32)le32_to_cpu(x), \
		 __le64: (u64)le64_to_cpu(x) \
		)

#घोषणा virtio_cpu_to_le(x, m) \
	_Generic((m), \
		 __u8: (x), \
		 __le16: cpu_to_le16(x), \
		 __le32: cpu_to_le32(x), \
		 __le64: cpu_to_le64(x) \
		)

/* LE (e.g. modern) Config space accessors. */
#घोषणा virtio_cपढ़ो_le(vdev, काष्ठाname, member, ptr)			\
	करो अणु								\
		typeof(((काष्ठाname*)0)->member) virtio_cपढ़ो_v;	\
									\
		might_sleep();						\
		/* Sanity check: must match the member's type */	\
		typecheck(typeof(virtio_le_to_cpu(virtio_cपढ़ो_v)), *(ptr)); \
									\
		चयन (माप(virtio_cपढ़ो_v)) अणु			\
		हाल 1:							\
		हाल 2:							\
		हाल 4:							\
			vdev->config->get((vdev), 			\
					  दुरत्व(काष्ठाname, member), \
					  &virtio_cपढ़ो_v,		\
					  माप(virtio_cपढ़ो_v));	\
			अवरोध;						\
		शेष:						\
			__virtio_cपढ़ो_many((vdev), 			\
					  दुरत्व(काष्ठाname, member), \
					  &virtio_cपढ़ो_v,		\
					  1,				\
					  माप(virtio_cपढ़ो_v));	\
			अवरोध;						\
		पूर्ण							\
		*(ptr) = virtio_le_to_cpu(virtio_cपढ़ो_v);		\
	पूर्ण जबतक(0)

#घोषणा virtio_cग_लिखो_le(vdev, काष्ठाname, member, ptr)			\
	करो अणु								\
		typeof(((काष्ठाname*)0)->member) virtio_cग_लिखो_v =	\
			virtio_cpu_to_le(*(ptr), ((काष्ठाname*)0)->member); \
									\
		might_sleep();						\
		/* Sanity check: must match the member's type */	\
		typecheck(typeof(virtio_le_to_cpu(virtio_cग_लिखो_v)), *(ptr)); \
									\
		vdev->config->set((vdev), दुरत्व(काष्ठाname, member),	\
				  &virtio_cग_लिखो_v,			\
				  माप(virtio_cग_लिखो_v));		\
	पूर्ण जबतक(0)


/* Read @count fields, @bytes each. */
अटल अंतरभूत व्योम __virtio_cपढ़ो_many(काष्ठा virtio_device *vdev,
				       अचिन्हित पूर्णांक offset,
				       व्योम *buf, माप_प्रकार count, माप_प्रकार bytes)
अणु
	u32 old, gen = vdev->config->generation ?
		vdev->config->generation(vdev) : 0;
	पूर्णांक i;

	might_sleep();
	करो अणु
		old = gen;

		क्रम (i = 0; i < count; i++)
			vdev->config->get(vdev, offset + bytes * i,
					  buf + i * bytes, bytes);

		gen = vdev->config->generation ?
			vdev->config->generation(vdev) : 0;
	पूर्ण जबतक (gen != old);
पूर्ण

अटल अंतरभूत व्योम virtio_cपढ़ो_bytes(काष्ठा virtio_device *vdev,
				      अचिन्हित पूर्णांक offset,
				      व्योम *buf, माप_प्रकार len)
अणु
	__virtio_cपढ़ो_many(vdev, offset, buf, len, 1);
पूर्ण

अटल अंतरभूत u8 virtio_cपढ़ो8(काष्ठा virtio_device *vdev, अचिन्हित पूर्णांक offset)
अणु
	u8 ret;

	might_sleep();
	vdev->config->get(vdev, offset, &ret, माप(ret));
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम virtio_cग_लिखो8(काष्ठा virtio_device *vdev,
				  अचिन्हित पूर्णांक offset, u8 val)
अणु
	might_sleep();
	vdev->config->set(vdev, offset, &val, माप(val));
पूर्ण

अटल अंतरभूत u16 virtio_cपढ़ो16(काष्ठा virtio_device *vdev,
				 अचिन्हित पूर्णांक offset)
अणु
	__virtio16 ret;

	might_sleep();
	vdev->config->get(vdev, offset, &ret, माप(ret));
	वापस virtio16_to_cpu(vdev, ret);
पूर्ण

अटल अंतरभूत व्योम virtio_cग_लिखो16(काष्ठा virtio_device *vdev,
				   अचिन्हित पूर्णांक offset, u16 val)
अणु
	__virtio16 v;

	might_sleep();
	v = cpu_to_virtio16(vdev, val);
	vdev->config->set(vdev, offset, &v, माप(v));
पूर्ण

अटल अंतरभूत u32 virtio_cपढ़ो32(काष्ठा virtio_device *vdev,
				 अचिन्हित पूर्णांक offset)
अणु
	__virtio32 ret;

	might_sleep();
	vdev->config->get(vdev, offset, &ret, माप(ret));
	वापस virtio32_to_cpu(vdev, ret);
पूर्ण

अटल अंतरभूत व्योम virtio_cग_लिखो32(काष्ठा virtio_device *vdev,
				   अचिन्हित पूर्णांक offset, u32 val)
अणु
	__virtio32 v;

	might_sleep();
	v = cpu_to_virtio32(vdev, val);
	vdev->config->set(vdev, offset, &v, माप(v));
पूर्ण

अटल अंतरभूत u64 virtio_cपढ़ो64(काष्ठा virtio_device *vdev,
				 अचिन्हित पूर्णांक offset)
अणु
	__virtio64 ret;

	__virtio_cपढ़ो_many(vdev, offset, &ret, 1, माप(ret));
	वापस virtio64_to_cpu(vdev, ret);
पूर्ण

अटल अंतरभूत व्योम virtio_cग_लिखो64(काष्ठा virtio_device *vdev,
				   अचिन्हित पूर्णांक offset, u64 val)
अणु
	__virtio64 v;

	might_sleep();
	v = cpu_to_virtio64(vdev, val);
	vdev->config->set(vdev, offset, &v, माप(v));
पूर्ण

/* Conditional config space accessors. */
#घोषणा virtio_cपढ़ो_feature(vdev, fbit, काष्ठाname, member, ptr)	\
	(अणु								\
		पूर्णांक _r = 0;						\
		अगर (!virtio_has_feature(vdev, fbit))			\
			_r = -ENOENT;					\
		अन्यथा							\
			virtio_cपढ़ो((vdev), काष्ठाname, member, ptr);	\
		_r;							\
	पूर्ण)

/* Conditional config space accessors. */
#घोषणा virtio_cपढ़ो_le_feature(vdev, fbit, काष्ठाname, member, ptr)	\
	(अणु								\
		पूर्णांक _r = 0;						\
		अगर (!virtio_has_feature(vdev, fbit))			\
			_r = -ENOENT;					\
		अन्यथा							\
			virtio_cपढ़ो_le((vdev), काष्ठाname, member, ptr); \
		_r;							\
	पूर्ण)

#अगर_घोषित CONFIG_ARCH_HAS_RESTRICTED_VIRTIO_MEMORY_ACCESS
पूर्णांक arch_has_restricted_virtio_memory_access(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक arch_has_restricted_virtio_memory_access(व्योम)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_ARCH_HAS_RESTRICTED_VIRTIO_MEMORY_ACCESS */

#पूर्ण_अगर /* _LINUX_VIRTIO_CONFIG_H */
