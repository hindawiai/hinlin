<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_VDPA_H
#घोषणा _LINUX_VDPA_H

#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/vhost_iotlb.h>

/**
 * काष्ठा vdpa_calllback - vDPA callback definition.
 * @callback: पूर्णांकerrupt callback function
 * @निजी: the data passed to the callback function
 */
काष्ठा vdpa_callback अणु
	irqवापस_t (*callback)(व्योम *data);
	व्योम *निजी;
पूर्ण;

/**
 * काष्ठा vdpa_notअगरication_area - vDPA notअगरication area
 * @addr: base address of the notअगरication area
 * @size: size of the notअगरication area
 */
काष्ठा vdpa_notअगरication_area अणु
	resource_माप_प्रकार addr;
	resource_माप_प्रकार size;
पूर्ण;

/**
 * काष्ठा vdpa_vq_state - vDPA vq_state definition
 * @avail_index: available index
 */
काष्ठा vdpa_vq_state अणु
	u16	avail_index;
पूर्ण;

काष्ठा vdpa_mgmt_dev;

/**
 * काष्ठा vdpa_device - representation of a vDPA device
 * @dev: underlying device
 * @dma_dev: the actual device that is perक्रमming DMA
 * @config: the configuration ops क्रम this device.
 * @index: device index
 * @features_valid: were features initialized? क्रम legacy guests
 * @nvqs: maximum number of supported virtqueues
 * @mdev: management device poपूर्णांकer; caller must setup when रेजिस्टरing device as part
 *	  of dev_add() mgmtdev ops callback beक्रमe invoking _vdpa_रेजिस्टर_device().
 */
काष्ठा vdpa_device अणु
	काष्ठा device dev;
	काष्ठा device *dma_dev;
	स्थिर काष्ठा vdpa_config_ops *config;
	अचिन्हित पूर्णांक index;
	bool features_valid;
	पूर्णांक nvqs;
	काष्ठा vdpa_mgmt_dev *mdev;
पूर्ण;

/**
 * काष्ठा vdpa_iova_range - the IOVA range support by the device
 * @first: start of the IOVA range
 * @last: end of the IOVA range
 */
काष्ठा vdpa_iova_range अणु
	u64 first;
	u64 last;
पूर्ण;

/**
 * काष्ठा vdpa_config_ops - operations क्रम configuring a vDPA device.
 * Note: vDPA device drivers are required to implement all of the
 * operations unless it is mentioned to be optional in the following
 * list.
 *
 * @set_vq_address:		Set the address of virtqueue
 *				@vdev: vdpa device
 *				@idx: virtqueue index
 *				@desc_area: address of desc area
 *				@driver_area: address of driver area
 *				@device_area: address of device area
 *				Returns पूर्णांकeger: success (0) or error (< 0)
 * @set_vq_num:			Set the size of virtqueue
 *				@vdev: vdpa device
 *				@idx: virtqueue index
 *				@num: the size of virtqueue
 * @kick_vq:			Kick the virtqueue
 *				@vdev: vdpa device
 *				@idx: virtqueue index
 * @set_vq_cb:			Set the पूर्णांकerrupt callback function क्रम
 *				a virtqueue
 *				@vdev: vdpa device
 *				@idx: virtqueue index
 *				@cb: virtio-vdev पूर्णांकerrupt callback काष्ठाure
 * @set_vq_पढ़ोy:		Set पढ़ोy status क्रम a virtqueue
 *				@vdev: vdpa device
 *				@idx: virtqueue index
 *				@पढ़ोy: पढ़ोy (true) not पढ़ोy(false)
 * @get_vq_पढ़ोy:		Get पढ़ोy status क्रम a virtqueue
 *				@vdev: vdpa device
 *				@idx: virtqueue index
 *				Returns boolean: पढ़ोy (true) or not (false)
 * @set_vq_state:		Set the state क्रम a virtqueue
 *				@vdev: vdpa device
 *				@idx: virtqueue index
 *				@state: poपूर्णांकer to set virtqueue state (last_avail_idx)
 *				Returns पूर्णांकeger: success (0) or error (< 0)
 * @get_vq_state:		Get the state क्रम a virtqueue
 *				@vdev: vdpa device
 *				@idx: virtqueue index
 *				@state: poपूर्णांकer to वापसed state (last_avail_idx)
 * @get_vq_notअगरication: 	Get the notअगरication area क्रम a virtqueue
 *				@vdev: vdpa device
 *				@idx: virtqueue index
 *				Returns the notअगरcation area
 * @get_vq_irq:			Get the irq number of a virtqueue (optional,
 *				but must implemented अगर require vq irq offloading)
 *				@vdev: vdpa device
 *				@idx: virtqueue index
 *				Returns पूर्णांक: irq number of a virtqueue,
 *				negative number अगर no irq asचिन्हित.
 * @get_vq_align:		Get the virtqueue align requirement
 *				क्रम the device
 *				@vdev: vdpa device
 *				Returns virtqueue algin requirement
 * @get_features:		Get virtio features supported by the device
 *				@vdev: vdpa device
 *				Returns the virtio features support by the
 *				device
 * @set_features:		Set virtio features supported by the driver
 *				@vdev: vdpa device
 *				@features: feature support by the driver
 *				Returns पूर्णांकeger: success (0) or error (< 0)
 * @set_config_cb:		Set the config पूर्णांकerrupt callback
 *				@vdev: vdpa device
 *				@cb: virtio-vdev पूर्णांकerrupt callback काष्ठाure
 * @get_vq_num_max:		Get the max size of virtqueue
 *				@vdev: vdpa device
 *				Returns u16: max size of virtqueue
 * @get_device_id:		Get virtio device id
 *				@vdev: vdpa device
 *				Returns u32: virtio device id
 * @get_venकरोr_id:		Get id क्रम the venकरोr that provides this device
 *				@vdev: vdpa device
 *				Returns u32: virtio venकरोr id
 * @get_status:			Get the device status
 *				@vdev: vdpa device
 *				Returns u8: virtio device status
 * @set_status:			Set the device status
 *				@vdev: vdpa device
 *				@status: virtio device status
 * @get_config_size:		Get the size of the configuration space
 *				@vdev: vdpa device
 *				Returns माप_प्रकार: configuration size
 * @get_config:			Read from device specअगरic configuration space
 *				@vdev: vdpa device
 *				@offset: offset from the beginning of
 *				configuration space
 *				@buf: buffer used to पढ़ो to
 *				@len: the length to पढ़ो from
 *				configuration space
 * @set_config:			Write to device specअगरic configuration space
 *				@vdev: vdpa device
 *				@offset: offset from the beginning of
 *				configuration space
 *				@buf: buffer used to ग_लिखो from
 *				@len: the length to ग_लिखो to
 *				configuration space
 * @get_generation:		Get device config generation (optional)
 *				@vdev: vdpa device
 *				Returns u32: device generation
 * @get_iova_range:		Get supported iova range (optional)
 *				@vdev: vdpa device
 *				Returns the iova range supported by
 *				the device.
 * @set_map:			Set device memory mapping (optional)
 *				Needed क्रम device that using device
 *				specअगरic DMA translation (on-chip IOMMU)
 *				@vdev: vdpa device
 *				@iotlb: vhost memory mapping to be
 *				used by the vDPA
 *				Returns पूर्णांकeger: success (0) or error (< 0)
 * @dma_map:			Map an area of PA to IOVA (optional)
 *				Needed क्रम device that using device
 *				specअगरic DMA translation (on-chip IOMMU)
 *				and preferring incremental map.
 *				@vdev: vdpa device
 *				@iova: iova to be mapped
 *				@size: size of the area
 *				@pa: physical address क्रम the map
 *				@perm: device access permission (VHOST_MAP_XX)
 *				Returns पूर्णांकeger: success (0) or error (< 0)
 * @dma_unmap:			Unmap an area of IOVA (optional but
 *				must be implemented with dma_map)
 *				Needed क्रम device that using device
 *				specअगरic DMA translation (on-chip IOMMU)
 *				and preferring incremental unmap.
 *				@vdev: vdpa device
 *				@iova: iova to be unmapped
 *				@size: size of the area
 *				Returns पूर्णांकeger: success (0) or error (< 0)
 * @मुक्त:			Free resources that beदीर्घs to vDPA (optional)
 *				@vdev: vdpa device
 */
काष्ठा vdpa_config_ops अणु
	/* Virtqueue ops */
	पूर्णांक (*set_vq_address)(काष्ठा vdpa_device *vdev,
			      u16 idx, u64 desc_area, u64 driver_area,
			      u64 device_area);
	व्योम (*set_vq_num)(काष्ठा vdpa_device *vdev, u16 idx, u32 num);
	व्योम (*kick_vq)(काष्ठा vdpa_device *vdev, u16 idx);
	व्योम (*set_vq_cb)(काष्ठा vdpa_device *vdev, u16 idx,
			  काष्ठा vdpa_callback *cb);
	व्योम (*set_vq_पढ़ोy)(काष्ठा vdpa_device *vdev, u16 idx, bool पढ़ोy);
	bool (*get_vq_पढ़ोy)(काष्ठा vdpa_device *vdev, u16 idx);
	पूर्णांक (*set_vq_state)(काष्ठा vdpa_device *vdev, u16 idx,
			    स्थिर काष्ठा vdpa_vq_state *state);
	पूर्णांक (*get_vq_state)(काष्ठा vdpa_device *vdev, u16 idx,
			    काष्ठा vdpa_vq_state *state);
	काष्ठा vdpa_notअगरication_area
	(*get_vq_notअगरication)(काष्ठा vdpa_device *vdev, u16 idx);
	/* vq irq is not expected to be changed once DRIVER_OK is set */
	पूर्णांक (*get_vq_irq)(काष्ठा vdpa_device *vdv, u16 idx);

	/* Device ops */
	u32 (*get_vq_align)(काष्ठा vdpa_device *vdev);
	u64 (*get_features)(काष्ठा vdpa_device *vdev);
	पूर्णांक (*set_features)(काष्ठा vdpa_device *vdev, u64 features);
	व्योम (*set_config_cb)(काष्ठा vdpa_device *vdev,
			      काष्ठा vdpa_callback *cb);
	u16 (*get_vq_num_max)(काष्ठा vdpa_device *vdev);
	u32 (*get_device_id)(काष्ठा vdpa_device *vdev);
	u32 (*get_venकरोr_id)(काष्ठा vdpa_device *vdev);
	u8 (*get_status)(काष्ठा vdpa_device *vdev);
	व्योम (*set_status)(काष्ठा vdpa_device *vdev, u8 status);
	माप_प्रकार (*get_config_size)(काष्ठा vdpa_device *vdev);
	व्योम (*get_config)(काष्ठा vdpa_device *vdev, अचिन्हित पूर्णांक offset,
			   व्योम *buf, अचिन्हित पूर्णांक len);
	व्योम (*set_config)(काष्ठा vdpa_device *vdev, अचिन्हित पूर्णांक offset,
			   स्थिर व्योम *buf, अचिन्हित पूर्णांक len);
	u32 (*get_generation)(काष्ठा vdpa_device *vdev);
	काष्ठा vdpa_iova_range (*get_iova_range)(काष्ठा vdpa_device *vdev);

	/* DMA ops */
	पूर्णांक (*set_map)(काष्ठा vdpa_device *vdev, काष्ठा vhost_iotlb *iotlb);
	पूर्णांक (*dma_map)(काष्ठा vdpa_device *vdev, u64 iova, u64 size,
		       u64 pa, u32 perm);
	पूर्णांक (*dma_unmap)(काष्ठा vdpa_device *vdev, u64 iova, u64 size);

	/* Free device resources */
	व्योम (*मुक्त)(काष्ठा vdpa_device *vdev);
पूर्ण;

काष्ठा vdpa_device *__vdpa_alloc_device(काष्ठा device *parent,
					स्थिर काष्ठा vdpa_config_ops *config,
					माप_प्रकार size, स्थिर अक्षर *name);

#घोषणा vdpa_alloc_device(dev_काष्ठा, member, parent, config, name)   \
			  container_of(__vdpa_alloc_device( \
				       parent, config, \
				       माप(dev_काष्ठा) + \
				       BUILD_BUG_ON_ZERO(दुरत्व( \
				       dev_काष्ठा, member)), name), \
				       dev_काष्ठा, member)

पूर्णांक vdpa_रेजिस्टर_device(काष्ठा vdpa_device *vdev, पूर्णांक nvqs);
व्योम vdpa_unरेजिस्टर_device(काष्ठा vdpa_device *vdev);

पूर्णांक _vdpa_रेजिस्टर_device(काष्ठा vdpa_device *vdev, पूर्णांक nvqs);
व्योम _vdpa_unरेजिस्टर_device(काष्ठा vdpa_device *vdev);

/**
 * काष्ठा vdpa_driver - operations क्रम a vDPA driver
 * @driver: underlying device driver
 * @probe: the function to call when a device is found.  Returns 0 or -त्रुटि_सं.
 * @हटाओ: the function to call when a device is हटाओd.
 */
काष्ठा vdpa_driver अणु
	काष्ठा device_driver driver;
	पूर्णांक (*probe)(काष्ठा vdpa_device *vdev);
	व्योम (*हटाओ)(काष्ठा vdpa_device *vdev);
पूर्ण;

#घोषणा vdpa_रेजिस्टर_driver(drv) \
	__vdpa_रेजिस्टर_driver(drv, THIS_MODULE)
पूर्णांक __vdpa_रेजिस्टर_driver(काष्ठा vdpa_driver *drv, काष्ठा module *owner);
व्योम vdpa_unरेजिस्टर_driver(काष्ठा vdpa_driver *drv);

#घोषणा module_vdpa_driver(__vdpa_driver) \
	module_driver(__vdpa_driver, vdpa_रेजिस्टर_driver,	\
		      vdpa_unरेजिस्टर_driver)

अटल अंतरभूत काष्ठा vdpa_driver *drv_to_vdpa(काष्ठा device_driver *driver)
अणु
	वापस container_of(driver, काष्ठा vdpa_driver, driver);
पूर्ण

अटल अंतरभूत काष्ठा vdpa_device *dev_to_vdpa(काष्ठा device *_dev)
अणु
	वापस container_of(_dev, काष्ठा vdpa_device, dev);
पूर्ण

अटल अंतरभूत व्योम *vdpa_get_drvdata(स्थिर काष्ठा vdpa_device *vdev)
अणु
	वापस dev_get_drvdata(&vdev->dev);
पूर्ण

अटल अंतरभूत व्योम vdpa_set_drvdata(काष्ठा vdpa_device *vdev, व्योम *data)
अणु
	dev_set_drvdata(&vdev->dev, data);
पूर्ण

अटल अंतरभूत काष्ठा device *vdpa_get_dma_dev(काष्ठा vdpa_device *vdev)
अणु
	वापस vdev->dma_dev;
पूर्ण

अटल अंतरभूत व्योम vdpa_reset(काष्ठा vdpa_device *vdev)
अणु
        स्थिर काष्ठा vdpa_config_ops *ops = vdev->config;

	vdev->features_valid = false;
        ops->set_status(vdev, 0);
पूर्ण

अटल अंतरभूत पूर्णांक vdpa_set_features(काष्ठा vdpa_device *vdev, u64 features)
अणु
        स्थिर काष्ठा vdpa_config_ops *ops = vdev->config;

	vdev->features_valid = true;
        वापस ops->set_features(vdev, features);
पूर्ण


अटल अंतरभूत व्योम vdpa_get_config(काष्ठा vdpa_device *vdev, अचिन्हित offset,
				   व्योम *buf, अचिन्हित पूर्णांक len)
अणु
        स्थिर काष्ठा vdpa_config_ops *ops = vdev->config;

	/*
	 * Config accesses aren't supposed to trigger beक्रमe features are set.
	 * If it करोes happen we assume a legacy guest.
	 */
	अगर (!vdev->features_valid)
		vdpa_set_features(vdev, 0);
	ops->get_config(vdev, offset, buf, len);
पूर्ण

/**
 * काष्ठा vdpa_mgmtdev_ops - vdpa device ops
 * @dev_add: Add a vdpa device using alloc and रेजिस्टर
 *	     @mdev: parent device to use क्रम device addition
 *	     @name: name of the new vdpa device
 *	     Driver need to add a new device using _vdpa_रेजिस्टर_device()
 *	     after fully initializing the vdpa device. Driver must वापस 0
 *	     on success or appropriate error code.
 * @dev_del: Remove a vdpa device using unरेजिस्टर
 *	     @mdev: parent device to use क्रम device removal
 *	     @dev: vdpa device to हटाओ
 *	     Driver need to हटाओ the specअगरied device by calling
 *	     _vdpa_unरेजिस्टर_device().
 */
काष्ठा vdpa_mgmtdev_ops अणु
	पूर्णांक (*dev_add)(काष्ठा vdpa_mgmt_dev *mdev, स्थिर अक्षर *name);
	व्योम (*dev_del)(काष्ठा vdpa_mgmt_dev *mdev, काष्ठा vdpa_device *dev);
पूर्ण;

काष्ठा vdpa_mgmt_dev अणु
	काष्ठा device *device;
	स्थिर काष्ठा vdpa_mgmtdev_ops *ops;
	स्थिर काष्ठा virtio_device_id *id_table; /* supported ids */
	काष्ठा list_head list;
पूर्ण;

पूर्णांक vdpa_mgmtdev_रेजिस्टर(काष्ठा vdpa_mgmt_dev *mdev);
व्योम vdpa_mgmtdev_unरेजिस्टर(काष्ठा vdpa_mgmt_dev *mdev);

#पूर्ण_अगर /* _LINUX_VDPA_H */
