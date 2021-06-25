<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_VIRTIO_H
#घोषणा _LINUX_VIRTIO_H
/* Everything a virtio driver needs to work with any particular virtio
 * implementation. */
#समावेश <linux/types.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/device.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/gfp.h>

/**
 * virtqueue - a queue to रेजिस्टर buffers क्रम sending or receiving.
 * @list: the chain of virtqueues क्रम this device
 * @callback: the function to call when buffers are consumed (can be शून्य).
 * @name: the name of this virtqueue (मुख्यly क्रम debugging)
 * @vdev: the virtio device this queue was created क्रम.
 * @priv: a poपूर्णांकer क्रम the virtqueue implementation to use.
 * @index: the zero-based ordinal number क्रम this queue.
 * @num_मुक्त: number of elements we expect to be able to fit.
 *
 * A note on @num_मुक्त: with indirect buffers, each buffer needs one
 * element in the queue, otherwise a buffer will need one element per
 * sg element.
 */
काष्ठा virtqueue अणु
	काष्ठा list_head list;
	व्योम (*callback)(काष्ठा virtqueue *vq);
	स्थिर अक्षर *name;
	काष्ठा virtio_device *vdev;
	अचिन्हित पूर्णांक index;
	अचिन्हित पूर्णांक num_मुक्त;
	व्योम *priv;
पूर्ण;

पूर्णांक virtqueue_add_outbuf(काष्ठा virtqueue *vq,
			 काष्ठा scatterlist sg[], अचिन्हित पूर्णांक num,
			 व्योम *data,
			 gfp_t gfp);

पूर्णांक virtqueue_add_inbuf(काष्ठा virtqueue *vq,
			काष्ठा scatterlist sg[], अचिन्हित पूर्णांक num,
			व्योम *data,
			gfp_t gfp);

पूर्णांक virtqueue_add_inbuf_ctx(काष्ठा virtqueue *vq,
			    काष्ठा scatterlist sg[], अचिन्हित पूर्णांक num,
			    व्योम *data,
			    व्योम *ctx,
			    gfp_t gfp);

पूर्णांक virtqueue_add_sgs(काष्ठा virtqueue *vq,
		      काष्ठा scatterlist *sgs[],
		      अचिन्हित पूर्णांक out_sgs,
		      अचिन्हित पूर्णांक in_sgs,
		      व्योम *data,
		      gfp_t gfp);

bool virtqueue_kick(काष्ठा virtqueue *vq);

bool virtqueue_kick_prepare(काष्ठा virtqueue *vq);

bool virtqueue_notअगरy(काष्ठा virtqueue *vq);

व्योम *virtqueue_get_buf(काष्ठा virtqueue *vq, अचिन्हित पूर्णांक *len);

व्योम *virtqueue_get_buf_ctx(काष्ठा virtqueue *vq, अचिन्हित पूर्णांक *len,
			    व्योम **ctx);

व्योम virtqueue_disable_cb(काष्ठा virtqueue *vq);

bool virtqueue_enable_cb(काष्ठा virtqueue *vq);

अचिन्हित virtqueue_enable_cb_prepare(काष्ठा virtqueue *vq);

bool virtqueue_poll(काष्ठा virtqueue *vq, अचिन्हित);

bool virtqueue_enable_cb_delayed(काष्ठा virtqueue *vq);

व्योम *virtqueue_detach_unused_buf(काष्ठा virtqueue *vq);

अचिन्हित पूर्णांक virtqueue_get_vring_size(काष्ठा virtqueue *vq);

bool virtqueue_is_broken(काष्ठा virtqueue *vq);

स्थिर काष्ठा vring *virtqueue_get_vring(काष्ठा virtqueue *vq);
dma_addr_t virtqueue_get_desc_addr(काष्ठा virtqueue *vq);
dma_addr_t virtqueue_get_avail_addr(काष्ठा virtqueue *vq);
dma_addr_t virtqueue_get_used_addr(काष्ठा virtqueue *vq);

/**
 * virtio_device - representation of a device using virtio
 * @index: unique position on the virtio bus
 * @failed: saved value क्रम VIRTIO_CONFIG_S_FAILED bit (क्रम restore)
 * @config_enabled: configuration change reporting enabled
 * @config_change_pending: configuration change reported जबतक disabled
 * @config_lock: protects configuration change reporting
 * @dev: underlying device.
 * @id: the device type identअगरication (used to match it with a driver).
 * @config: the configuration ops क्रम this device.
 * @vringh_config: configuration ops क्रम host vrings.
 * @vqs: the list of virtqueues क्रम this device.
 * @features: the features supported by both driver and device.
 * @priv: निजी poपूर्णांकer क्रम the driver's use.
 */
काष्ठा virtio_device अणु
	पूर्णांक index;
	bool failed;
	bool config_enabled;
	bool config_change_pending;
	spinlock_t config_lock;
	काष्ठा device dev;
	काष्ठा virtio_device_id id;
	स्थिर काष्ठा virtio_config_ops *config;
	स्थिर काष्ठा vringh_config_ops *vringh_config;
	काष्ठा list_head vqs;
	u64 features;
	व्योम *priv;
पूर्ण;

अटल अंतरभूत काष्ठा virtio_device *dev_to_virtio(काष्ठा device *_dev)
अणु
	वापस container_of(_dev, काष्ठा virtio_device, dev);
पूर्ण

व्योम virtio_add_status(काष्ठा virtio_device *dev, अचिन्हित पूर्णांक status);
पूर्णांक रेजिस्टर_virtio_device(काष्ठा virtio_device *dev);
व्योम unरेजिस्टर_virtio_device(काष्ठा virtio_device *dev);
bool is_virtio_device(काष्ठा device *dev);

व्योम virtio_अवरोध_device(काष्ठा virtio_device *dev);

व्योम virtio_config_changed(काष्ठा virtio_device *dev);
पूर्णांक virtio_finalize_features(काष्ठा virtio_device *dev);
#अगर_घोषित CONFIG_PM_SLEEP
पूर्णांक virtio_device_मुक्तze(काष्ठा virtio_device *dev);
पूर्णांक virtio_device_restore(काष्ठा virtio_device *dev);
#पूर्ण_अगर

माप_प्रकार virtio_max_dma_size(काष्ठा virtio_device *vdev);

#घोषणा virtio_device_क्रम_each_vq(vdev, vq) \
	list_क्रम_each_entry(vq, &vdev->vqs, list)

/**
 * virtio_driver - operations क्रम a virtio I/O driver
 * @driver: underlying device driver (populate name and owner).
 * @id_table: the ids serviced by this driver.
 * @feature_table: an array of feature numbers supported by this driver.
 * @feature_table_size: number of entries in the feature table array.
 * @feature_table_legacy: same as feature_table but when working in legacy mode.
 * @feature_table_size_legacy: number of entries in feature table legacy array.
 * @probe: the function to call when a device is found.  Returns 0 or -त्रुटि_सं.
 * @scan: optional function to call after successful probe; पूर्णांकended
 *    क्रम virtio-scsi to invoke a scan.
 * @हटाओ: the function to call when a device is हटाओd.
 * @config_changed: optional function to call when the device configuration
 *    changes; may be called in पूर्णांकerrupt context.
 * @मुक्तze: optional function to call during suspend/hibernation.
 * @restore: optional function to call on resume.
 */
काष्ठा virtio_driver अणु
	काष्ठा device_driver driver;
	स्थिर काष्ठा virtio_device_id *id_table;
	स्थिर अचिन्हित पूर्णांक *feature_table;
	अचिन्हित पूर्णांक feature_table_size;
	स्थिर अचिन्हित पूर्णांक *feature_table_legacy;
	अचिन्हित पूर्णांक feature_table_size_legacy;
	पूर्णांक (*validate)(काष्ठा virtio_device *dev);
	पूर्णांक (*probe)(काष्ठा virtio_device *dev);
	व्योम (*scan)(काष्ठा virtio_device *dev);
	व्योम (*हटाओ)(काष्ठा virtio_device *dev);
	व्योम (*config_changed)(काष्ठा virtio_device *dev);
#अगर_घोषित CONFIG_PM
	पूर्णांक (*मुक्तze)(काष्ठा virtio_device *dev);
	पूर्णांक (*restore)(काष्ठा virtio_device *dev);
#पूर्ण_अगर
पूर्ण;

अटल अंतरभूत काष्ठा virtio_driver *drv_to_virtio(काष्ठा device_driver *drv)
अणु
	वापस container_of(drv, काष्ठा virtio_driver, driver);
पूर्ण

पूर्णांक रेजिस्टर_virtio_driver(काष्ठा virtio_driver *drv);
व्योम unरेजिस्टर_virtio_driver(काष्ठा virtio_driver *drv);

/* module_virtio_driver() - Helper macro क्रम drivers that करोn't करो
 * anything special in module init/निकास.  This eliminates a lot of
 * boilerplate.  Each module may only use this macro once, and
 * calling it replaces module_init() and module_निकास()
 */
#घोषणा module_virtio_driver(__virtio_driver) \
	module_driver(__virtio_driver, रेजिस्टर_virtio_driver, \
			unरेजिस्टर_virtio_driver)
#पूर्ण_अगर /* _LINUX_VIRTIO_H */
