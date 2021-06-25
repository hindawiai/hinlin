<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * device.h - generic, centralized driver model
 *
 * Copyright (c) 2001-2003 Patrick Mochel <mochel@osdl.org>
 * Copyright (c) 2004-2009 Greg Kroah-Harपंचांगan <gregkh@suse.de>
 * Copyright (c) 2008-2009 Novell Inc.
 *
 * See Documentation/driver-api/driver-model/ क्रम more inक्रमmation.
 */

#अगर_अघोषित _DEVICE_H_
#घोषणा _DEVICE_H_

#समावेश <linux/dev_prपूर्णांकk.h>
#समावेश <linux/energy_model.h>
#समावेश <linux/ioport.h>
#समावेश <linux/kobject.h>
#समावेश <linux/klist.h>
#समावेश <linux/list.h>
#समावेश <linux/lockdep.h>
#समावेश <linux/compiler.h>
#समावेश <linux/types.h>
#समावेश <linux/mutex.h>
#समावेश <linux/pm.h>
#समावेश <linux/atomic.h>
#समावेश <linux/uidgid.h>
#समावेश <linux/gfp.h>
#समावेश <linux/overflow.h>
#समावेश <linux/device/bus.h>
#समावेश <linux/device/class.h>
#समावेश <linux/device/driver.h>
#समावेश <यंत्र/device.h>

काष्ठा device;
काष्ठा device_निजी;
काष्ठा device_driver;
काष्ठा driver_निजी;
काष्ठा module;
काष्ठा class;
काष्ठा subsys_निजी;
काष्ठा device_node;
काष्ठा fwnode_handle;
काष्ठा iommu_ops;
काष्ठा iommu_group;
काष्ठा dev_pin_info;
काष्ठा dev_iommu;

/**
 * काष्ठा subsys_पूर्णांकerface - पूर्णांकerfaces to device functions
 * @name:       name of the device function
 * @subsys:     subप्रणाली of the devices to attach to
 * @node:       the list of functions रेजिस्टरed at the subप्रणाली
 * @add_dev:    device hookup to device function handler
 * @हटाओ_dev: device hookup to device function handler
 *
 * Simple पूर्णांकerfaces attached to a subप्रणाली. Multiple पूर्णांकerfaces can
 * attach to a subप्रणाली and its devices. Unlike drivers, they करो not
 * exclusively claim or control devices. Interfaces usually represent
 * a specअगरic functionality of a subप्रणाली/class of devices.
 */
काष्ठा subsys_पूर्णांकerface अणु
	स्थिर अक्षर *name;
	काष्ठा bus_type *subsys;
	काष्ठा list_head node;
	पूर्णांक (*add_dev)(काष्ठा device *dev, काष्ठा subsys_पूर्णांकerface *sअगर);
	व्योम (*हटाओ_dev)(काष्ठा device *dev, काष्ठा subsys_पूर्णांकerface *sअगर);
पूर्ण;

पूर्णांक subsys_पूर्णांकerface_रेजिस्टर(काष्ठा subsys_पूर्णांकerface *sअगर);
व्योम subsys_पूर्णांकerface_unरेजिस्टर(काष्ठा subsys_पूर्णांकerface *sअगर);

पूर्णांक subsys_प्रणाली_रेजिस्टर(काष्ठा bus_type *subsys,
			   स्थिर काष्ठा attribute_group **groups);
पूर्णांक subsys_भव_रेजिस्टर(काष्ठा bus_type *subsys,
			    स्थिर काष्ठा attribute_group **groups);

/*
 * The type of device, "struct device" is embedded in. A class
 * or bus can contain devices of dअगरferent types
 * like "partitions" and "disks", "mouse" and "event".
 * This identअगरies the device type and carries type-specअगरic
 * inक्रमmation, equivalent to the kobj_type of a kobject.
 * If "name" is specअगरied, the uevent will contain it in
 * the DEVTYPE variable.
 */
काष्ठा device_type अणु
	स्थिर अक्षर *name;
	स्थिर काष्ठा attribute_group **groups;
	पूर्णांक (*uevent)(काष्ठा device *dev, काष्ठा kobj_uevent_env *env);
	अक्षर *(*devnode)(काष्ठा device *dev, umode_t *mode,
			 kuid_t *uid, kgid_t *gid);
	व्योम (*release)(काष्ठा device *dev);

	स्थिर काष्ठा dev_pm_ops *pm;
पूर्ण;

/* पूर्णांकerface क्रम exporting device attributes */
काष्ठा device_attribute अणु
	काष्ठा attribute	attr;
	sमाप_प्रकार (*show)(काष्ठा device *dev, काष्ठा device_attribute *attr,
			अक्षर *buf);
	sमाप_प्रकार (*store)(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 स्थिर अक्षर *buf, माप_प्रकार count);
पूर्ण;

काष्ठा dev_ext_attribute अणु
	काष्ठा device_attribute attr;
	व्योम *var;
पूर्ण;

sमाप_प्रकार device_show_uदीर्घ(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *buf);
sमाप_प्रकार device_store_uदीर्घ(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   स्थिर अक्षर *buf, माप_प्रकार count);
sमाप_प्रकार device_show_पूर्णांक(काष्ठा device *dev, काष्ठा device_attribute *attr,
			अक्षर *buf);
sमाप_प्रकार device_store_पूर्णांक(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 स्थिर अक्षर *buf, माप_प्रकार count);
sमाप_प्रकार device_show_bool(काष्ठा device *dev, काष्ठा device_attribute *attr,
			अक्षर *buf);
sमाप_प्रकार device_store_bool(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 स्थिर अक्षर *buf, माप_प्रकार count);

#घोषणा DEVICE_ATTR(_name, _mode, _show, _store) \
	काष्ठा device_attribute dev_attr_##_name = __ATTR(_name, _mode, _show, _store)
#घोषणा DEVICE_ATTR_PREALLOC(_name, _mode, _show, _store) \
	काष्ठा device_attribute dev_attr_##_name = \
		__ATTR_PREALLOC(_name, _mode, _show, _store)
#घोषणा DEVICE_ATTR_RW(_name) \
	काष्ठा device_attribute dev_attr_##_name = __ATTR_RW(_name)
#घोषणा DEVICE_ATTR_ADMIN_RW(_name) \
	काष्ठा device_attribute dev_attr_##_name = __ATTR_RW_MODE(_name, 0600)
#घोषणा DEVICE_ATTR_RO(_name) \
	काष्ठा device_attribute dev_attr_##_name = __ATTR_RO(_name)
#घोषणा DEVICE_ATTR_ADMIN_RO(_name) \
	काष्ठा device_attribute dev_attr_##_name = __ATTR_RO_MODE(_name, 0400)
#घोषणा DEVICE_ATTR_WO(_name) \
	काष्ठा device_attribute dev_attr_##_name = __ATTR_WO(_name)
#घोषणा DEVICE_ULONG_ATTR(_name, _mode, _var) \
	काष्ठा dev_ext_attribute dev_attr_##_name = \
		अणु __ATTR(_name, _mode, device_show_uदीर्घ, device_store_uदीर्घ), &(_var) पूर्ण
#घोषणा DEVICE_INT_ATTR(_name, _mode, _var) \
	काष्ठा dev_ext_attribute dev_attr_##_name = \
		अणु __ATTR(_name, _mode, device_show_पूर्णांक, device_store_पूर्णांक), &(_var) पूर्ण
#घोषणा DEVICE_BOOL_ATTR(_name, _mode, _var) \
	काष्ठा dev_ext_attribute dev_attr_##_name = \
		अणु __ATTR(_name, _mode, device_show_bool, device_store_bool), &(_var) पूर्ण
#घोषणा DEVICE_ATTR_IGNORE_LOCKDEP(_name, _mode, _show, _store) \
	काष्ठा device_attribute dev_attr_##_name =		\
		__ATTR_IGNORE_LOCKDEP(_name, _mode, _show, _store)

पूर्णांक device_create_file(काष्ठा device *device,
		       स्थिर काष्ठा device_attribute *entry);
व्योम device_हटाओ_file(काष्ठा device *dev,
			स्थिर काष्ठा device_attribute *attr);
bool device_हटाओ_file_self(काष्ठा device *dev,
			     स्थिर काष्ठा device_attribute *attr);
पूर्णांक __must_check device_create_bin_file(काष्ठा device *dev,
					स्थिर काष्ठा bin_attribute *attr);
व्योम device_हटाओ_bin_file(काष्ठा device *dev,
			    स्थिर काष्ठा bin_attribute *attr);

/* device resource management */
प्रकार व्योम (*dr_release_t)(काष्ठा device *dev, व्योम *res);
प्रकार पूर्णांक (*dr_match_t)(काष्ठा device *dev, व्योम *res, व्योम *match_data);

#अगर_घोषित CONFIG_DEBUG_DEVRES
व्योम *__devres_alloc_node(dr_release_t release, माप_प्रकार size, gfp_t gfp,
			  पूर्णांक nid, स्थिर अक्षर *name) __दो_स्मृति;
#घोषणा devres_alloc(release, size, gfp) \
	__devres_alloc_node(release, size, gfp, NUMA_NO_NODE, #release)
#घोषणा devres_alloc_node(release, size, gfp, nid) \
	__devres_alloc_node(release, size, gfp, nid, #release)
#अन्यथा
व्योम *devres_alloc_node(dr_release_t release, माप_प्रकार size,
			gfp_t gfp, पूर्णांक nid) __दो_स्मृति;
अटल अंतरभूत व्योम *devres_alloc(dr_release_t release, माप_प्रकार size, gfp_t gfp)
अणु
	वापस devres_alloc_node(release, size, gfp, NUMA_NO_NODE);
पूर्ण
#पूर्ण_अगर

व्योम devres_क्रम_each_res(काष्ठा device *dev, dr_release_t release,
			 dr_match_t match, व्योम *match_data,
			 व्योम (*fn)(काष्ठा device *, व्योम *, व्योम *),
			 व्योम *data);
व्योम devres_मुक्त(व्योम *res);
व्योम devres_add(काष्ठा device *dev, व्योम *res);
व्योम *devres_find(काष्ठा device *dev, dr_release_t release,
		  dr_match_t match, व्योम *match_data);
व्योम *devres_get(काष्ठा device *dev, व्योम *new_res,
		 dr_match_t match, व्योम *match_data);
व्योम *devres_हटाओ(काष्ठा device *dev, dr_release_t release,
		    dr_match_t match, व्योम *match_data);
पूर्णांक devres_destroy(काष्ठा device *dev, dr_release_t release,
		   dr_match_t match, व्योम *match_data);
पूर्णांक devres_release(काष्ठा device *dev, dr_release_t release,
		   dr_match_t match, व्योम *match_data);

/* devres group */
व्योम * __must_check devres_खोलो_group(काष्ठा device *dev, व्योम *id, gfp_t gfp);
व्योम devres_बंद_group(काष्ठा device *dev, व्योम *id);
व्योम devres_हटाओ_group(काष्ठा device *dev, व्योम *id);
पूर्णांक devres_release_group(काष्ठा device *dev, व्योम *id);

/* managed devm_k.alloc/kमुक्त क्रम device drivers */
व्योम *devm_kदो_स्मृति(काष्ठा device *dev, माप_प्रकार size, gfp_t gfp) __दो_स्मृति;
व्योम *devm_kपुनः_स्मृति(काष्ठा device *dev, व्योम *ptr, माप_प्रकार size,
		    gfp_t gfp) __must_check;
__म_लिखो(3, 0) अक्षर *devm_kvaप्र_लिखो(काष्ठा device *dev, gfp_t gfp,
				     स्थिर अक्षर *fmt, बहु_सूची ap) __दो_स्मृति;
__म_लिखो(3, 4) अक्षर *devm_kaप्र_लिखो(काष्ठा device *dev, gfp_t gfp,
				    स्थिर अक्षर *fmt, ...) __दो_स्मृति;
अटल अंतरभूत व्योम *devm_kzalloc(काष्ठा device *dev, माप_प्रकार size, gfp_t gfp)
अणु
	वापस devm_kदो_स्मृति(dev, size, gfp | __GFP_ZERO);
पूर्ण
अटल अंतरभूत व्योम *devm_kदो_स्मृति_array(काष्ठा device *dev,
				       माप_प्रकार n, माप_प्रकार size, gfp_t flags)
अणु
	माप_प्रकार bytes;

	अगर (unlikely(check_mul_overflow(n, size, &bytes)))
		वापस शून्य;

	वापस devm_kदो_स्मृति(dev, bytes, flags);
पूर्ण
अटल अंतरभूत व्योम *devm_kसुस्मृति(काष्ठा device *dev,
				 माप_प्रकार n, माप_प्रकार size, gfp_t flags)
अणु
	वापस devm_kदो_स्मृति_array(dev, n, size, flags | __GFP_ZERO);
पूर्ण
व्योम devm_kमुक्त(काष्ठा device *dev, स्थिर व्योम *p);
अक्षर *devm_kstrdup(काष्ठा device *dev, स्थिर अक्षर *s, gfp_t gfp) __दो_स्मृति;
स्थिर अक्षर *devm_kstrdup_स्थिर(काष्ठा device *dev, स्थिर अक्षर *s, gfp_t gfp);
व्योम *devm_kmemdup(काष्ठा device *dev, स्थिर व्योम *src, माप_प्रकार len, gfp_t gfp);

अचिन्हित दीर्घ devm_get_मुक्त_pages(काष्ठा device *dev,
				  gfp_t gfp_mask, अचिन्हित पूर्णांक order);
व्योम devm_मुक्त_pages(काष्ठा device *dev, अचिन्हित दीर्घ addr);

व्योम __iomem *devm_ioremap_resource(काष्ठा device *dev,
				    स्थिर काष्ठा resource *res);
व्योम __iomem *devm_ioremap_resource_wc(काष्ठा device *dev,
				       स्थिर काष्ठा resource *res);

व्योम __iomem *devm_of_iomap(काष्ठा device *dev,
			    काष्ठा device_node *node, पूर्णांक index,
			    resource_माप_प्रकार *size);

/* allows to add/हटाओ a custom action to devres stack */
पूर्णांक devm_add_action(काष्ठा device *dev, व्योम (*action)(व्योम *), व्योम *data);
व्योम devm_हटाओ_action(काष्ठा device *dev, व्योम (*action)(व्योम *), व्योम *data);
व्योम devm_release_action(काष्ठा device *dev, व्योम (*action)(व्योम *), व्योम *data);

अटल अंतरभूत पूर्णांक devm_add_action_or_reset(काष्ठा device *dev,
					   व्योम (*action)(व्योम *), व्योम *data)
अणु
	पूर्णांक ret;

	ret = devm_add_action(dev, action, data);
	अगर (ret)
		action(data);

	वापस ret;
पूर्ण

/**
 * devm_alloc_percpu - Resource-managed alloc_percpu
 * @dev: Device to allocate per-cpu memory क्रम
 * @type: Type to allocate per-cpu memory क्रम
 *
 * Managed alloc_percpu. Per-cpu memory allocated with this function is
 * स्वतःmatically मुक्तd on driver detach.
 *
 * RETURNS:
 * Poपूर्णांकer to allocated memory on success, शून्य on failure.
 */
#घोषणा devm_alloc_percpu(dev, type)      \
	((typeof(type) __percpu *)__devm_alloc_percpu((dev), माप(type), \
						      __alignof__(type)))

व्योम __percpu *__devm_alloc_percpu(काष्ठा device *dev, माप_प्रकार size,
				   माप_प्रकार align);
व्योम devm_मुक्त_percpu(काष्ठा device *dev, व्योम __percpu *pdata);

काष्ठा device_dma_parameters अणु
	/*
	 * a low level driver may set these to teach IOMMU code about
	 * sg limitations.
	 */
	अचिन्हित पूर्णांक max_segment_size;
	अचिन्हित पूर्णांक min_align_mask;
	अचिन्हित दीर्घ segment_boundary_mask;
पूर्ण;

/**
 * क्रमागत device_link_state - Device link states.
 * @DL_STATE_NONE: The presence of the drivers is not being tracked.
 * @DL_STATE_DORMANT: None of the supplier/consumer drivers is present.
 * @DL_STATE_AVAILABLE: The supplier driver is present, but the consumer is not.
 * @DL_STATE_CONSUMER_PROBE: The consumer is probing (supplier driver present).
 * @DL_STATE_ACTIVE: Both the supplier and consumer drivers are present.
 * @DL_STATE_SUPPLIER_UNBIND: The supplier driver is unbinding.
 */
क्रमागत device_link_state अणु
	DL_STATE_NONE = -1,
	DL_STATE_DORMANT = 0,
	DL_STATE_AVAILABLE,
	DL_STATE_CONSUMER_PROBE,
	DL_STATE_ACTIVE,
	DL_STATE_SUPPLIER_UNBIND,
पूर्ण;

/*
 * Device link flags.
 *
 * STATELESS: The core will not हटाओ this link स्वतःmatically.
 * AUTOREMOVE_CONSUMER: Remove the link स्वतःmatically on consumer driver unbind.
 * PM_RUNTIME: If set, the runसमय PM framework will use this link.
 * RPM_ACTIVE: Run pm_runसमय_get_sync() on the supplier during link creation.
 * AUTOREMOVE_SUPPLIER: Remove the link स्वतःmatically on supplier driver unbind.
 * AUTOPROBE_CONSUMER: Probe consumer driver स्वतःmatically after supplier binds.
 * MANAGED: The core tracks presence of supplier/consumer drivers (पूर्णांकernal).
 * SYNC_STATE_ONLY: Link only affects sync_state() behavior.
 * INFERRED: Inferred from data (eg: firmware) and not from driver actions.
 */
#घोषणा DL_FLAG_STATELESS		BIT(0)
#घोषणा DL_FLAG_AUTOREMOVE_CONSUMER	BIT(1)
#घोषणा DL_FLAG_PM_RUNTIME		BIT(2)
#घोषणा DL_FLAG_RPM_ACTIVE		BIT(3)
#घोषणा DL_FLAG_AUTOREMOVE_SUPPLIER	BIT(4)
#घोषणा DL_FLAG_AUTOPROBE_CONSUMER	BIT(5)
#घोषणा DL_FLAG_MANAGED			BIT(6)
#घोषणा DL_FLAG_SYNC_STATE_ONLY		BIT(7)
#घोषणा DL_FLAG_INFERRED		BIT(8)

/**
 * क्रमागत dl_dev_state - Device driver presence tracking inक्रमmation.
 * @DL_DEV_NO_DRIVER: There is no driver attached to the device.
 * @DL_DEV_PROBING: A driver is probing.
 * @DL_DEV_DRIVER_BOUND: The driver has been bound to the device.
 * @DL_DEV_UNBINDING: The driver is unbinding from the device.
 */
क्रमागत dl_dev_state अणु
	DL_DEV_NO_DRIVER = 0,
	DL_DEV_PROBING,
	DL_DEV_DRIVER_BOUND,
	DL_DEV_UNBINDING,
पूर्ण;

/**
 * काष्ठा dev_links_info - Device data related to device links.
 * @suppliers: List of links to supplier devices.
 * @consumers: List of links to consumer devices.
 * @defer_sync: Hook to global list of devices that have deferred sync_state.
 * @status: Driver status inक्रमmation.
 */
काष्ठा dev_links_info अणु
	काष्ठा list_head suppliers;
	काष्ठा list_head consumers;
	काष्ठा list_head defer_sync;
	क्रमागत dl_dev_state status;
पूर्ण;

/**
 * काष्ठा device - The basic device काष्ठाure
 * @parent:	The device's "parent" device, the device to which it is attached.
 * 		In most हालs, a parent device is some sort of bus or host
 * 		controller. If parent is शून्य, the device, is a top-level device,
 * 		which is not usually what you want.
 * @p:		Holds the निजी data of the driver core portions of the device.
 * 		See the comment of the काष्ठा device_निजी क्रम detail.
 * @kobj:	A top-level, असलtract class from which other classes are derived.
 * @init_name:	Initial name of the device.
 * @type:	The type of device.
 * 		This identअगरies the device type and carries type-specअगरic
 * 		inक्रमmation.
 * @mutex:	Mutex to synchronize calls to its driver.
 * @lockdep_mutex: An optional debug lock that a subप्रणाली can use as a
 * 		peer lock to gain localized lockdep coverage of the device_lock.
 * @bus:	Type of bus device is on.
 * @driver:	Which driver has allocated this
 * @platक्रमm_data: Platक्रमm data specअगरic to the device.
 * 		Example: For devices on custom boards, as typical of embedded
 * 		and SOC based hardware, Linux often uses platक्रमm_data to poपूर्णांक
 * 		to board-specअगरic काष्ठाures describing devices and how they
 * 		are wired.  That can include what ports are available, chip
 * 		variants, which GPIO pins act in what additional roles, and so
 * 		on.  This shrinks the "Board Support Packages" (BSPs) and
 * 		minimizes board-specअगरic #अगर_घोषितs in drivers.
 * @driver_data: Private poपूर्णांकer क्रम driver specअगरic info.
 * @links:	Links to suppliers and consumers of this device.
 * @घातer:	For device घातer management.
 *		See Documentation/driver-api/pm/devices.rst क्रम details.
 * @pm_करोमुख्य:	Provide callbacks that are executed during प्रणाली suspend,
 * 		hibernation, प्रणाली resume and during runसमय PM transitions
 * 		aदीर्घ with subप्रणाली-level and driver-level callbacks.
 * @em_pd:	device's energy model perक्रमmance करोमुख्य
 * @pins:	For device pin management.
 *		See Documentation/driver-api/pinctl.rst क्रम details.
 * @msi_list:	Hosts MSI descriptors
 * @msi_करोमुख्य: The generic MSI करोमुख्य this device is using.
 * @numa_node:	NUMA node this device is बंद to.
 * @dma_ops:    DMA mapping operations क्रम this device.
 * @dma_mask:	Dma mask (अगर dma'ble device).
 * @coherent_dma_mask: Like dma_mask, but क्रम alloc_coherent mapping as not all
 * 		hardware supports 64-bit addresses क्रम consistent allocations
 * 		such descriptors.
 * @bus_dma_limit: Limit of an upstream bridge or bus which imposes a smaller
 *		DMA limit than the device itself supports.
 * @dma_range_map: map क्रम DMA memory ranges relative to that of RAM
 * @dma_parms:	A low level driver may set these to teach IOMMU code about
 * 		segment limitations.
 * @dma_pools:	Dma pools (अगर dma'ble device).
 * @dma_mem:	Internal क्रम coherent mem override.
 * @cma_area:	Contiguous memory area क्रम dma allocations
 * @archdata:	For arch-specअगरic additions.
 * @of_node:	Associated device tree node.
 * @fwnode:	Associated device node supplied by platक्रमm firmware.
 * @devt:	For creating the sysfs "dev".
 * @id:		device instance
 * @devres_lock: Spinlock to protect the resource of the device.
 * @devres_head: The resources list of the device.
 * @knode_class: The node used to add the device to the class list.
 * @class:	The class of the device.
 * @groups:	Optional attribute groups.
 * @release:	Callback to मुक्त the device after all references have
 * 		gone away. This should be set by the allocator of the
 * 		device (i.e. the bus driver that discovered the device).
 * @iommu_group: IOMMU group the device beदीर्घs to.
 * @iommu:	Per device generic IOMMU runसमय data
 *
 * @offline_disabled: If set, the device is permanently online.
 * @offline:	Set after successful invocation of bus type's .offline().
 * @of_node_reused: Set अगर the device-tree node is shared with an ancestor
 *              device.
 * @state_synced: The hardware state of this device has been synced to match
 *		  the software state of this device by calling the driver/bus
 *		  sync_state() callback.
 * @can_match:	The device has matched with a driver at least once or it is in
 *		a bus (like AMBA) which can't check क्रम matching drivers until
 *		other devices probe successfully.
 * @dma_coherent: this particular device is dma coherent, even अगर the
 *		architecture supports non-coherent devices.
 * @dma_ops_bypass: If set to %true then the dma_ops are bypassed क्रम the
 *		streaming DMA operations (->map_* / ->unmap_* / ->sync_*),
 *		and optionall (अगर the coherent mask is large enough) also
 *		क्रम dma allocations.  This flag is managed by the dma ops
 *		instance from ->dma_supported.
 *
 * At the lowest level, every device in a Linux प्रणाली is represented by an
 * instance of काष्ठा device. The device काष्ठाure contains the inक्रमmation
 * that the device model core needs to model the प्रणाली. Most subप्रणालीs,
 * however, track additional inक्रमmation about the devices they host. As a
 * result, it is rare क्रम devices to be represented by bare device काष्ठाures;
 * instead, that काष्ठाure, like kobject काष्ठाures, is usually embedded within
 * a higher-level representation of the device.
 */
काष्ठा device अणु
	काष्ठा kobject kobj;
	काष्ठा device		*parent;

	काष्ठा device_निजी	*p;

	स्थिर अक्षर		*init_name; /* initial name of the device */
	स्थिर काष्ठा device_type *type;

	काष्ठा bus_type	*bus;		/* type of bus device is on */
	काष्ठा device_driver *driver;	/* which driver has allocated this
					   device */
	व्योम		*platक्रमm_data;	/* Platक्रमm specअगरic data, device
					   core करोesn't touch it */
	व्योम		*driver_data;	/* Driver data, set and get with
					   dev_set_drvdata/dev_get_drvdata */
#अगर_घोषित CONFIG_PROVE_LOCKING
	काष्ठा mutex		lockdep_mutex;
#पूर्ण_अगर
	काष्ठा mutex		mutex;	/* mutex to synchronize calls to
					 * its driver.
					 */

	काष्ठा dev_links_info	links;
	काष्ठा dev_pm_info	घातer;
	काष्ठा dev_pm_करोमुख्य	*pm_करोमुख्य;

#अगर_घोषित CONFIG_ENERGY_MODEL
	काष्ठा em_perf_करोमुख्य	*em_pd;
#पूर्ण_अगर

#अगर_घोषित CONFIG_GENERIC_MSI_IRQ_DOMAIN
	काष्ठा irq_करोमुख्य	*msi_करोमुख्य;
#पूर्ण_अगर
#अगर_घोषित CONFIG_PINCTRL
	काष्ठा dev_pin_info	*pins;
#पूर्ण_अगर
#अगर_घोषित CONFIG_GENERIC_MSI_IRQ
	काष्ठा list_head	msi_list;
#पूर्ण_अगर
#अगर_घोषित CONFIG_DMA_OPS
	स्थिर काष्ठा dma_map_ops *dma_ops;
#पूर्ण_अगर
	u64		*dma_mask;	/* dma mask (अगर dma'able device) */
	u64		coherent_dma_mask;/* Like dma_mask, but क्रम
					     alloc_coherent mappings as
					     not all hardware supports
					     64 bit addresses क्रम consistent
					     allocations such descriptors. */
	u64		bus_dma_limit;	/* upstream dma स्थिरraपूर्णांक */
	स्थिर काष्ठा bus_dma_region *dma_range_map;

	काष्ठा device_dma_parameters *dma_parms;

	काष्ठा list_head	dma_pools;	/* dma pools (अगर dma'ble) */

#अगर_घोषित CONFIG_DMA_DECLARE_COHERENT
	काष्ठा dma_coherent_mem	*dma_mem; /* पूर्णांकernal क्रम coherent mem
					     override */
#पूर्ण_अगर
#अगर_घोषित CONFIG_DMA_CMA
	काष्ठा cma *cma_area;		/* contiguous memory area क्रम dma
					   allocations */
#पूर्ण_अगर
	/* arch specअगरic additions */
	काष्ठा dev_archdata	archdata;

	काष्ठा device_node	*of_node; /* associated device tree node */
	काष्ठा fwnode_handle	*fwnode; /* firmware device node */

#अगर_घोषित CONFIG_NUMA
	पूर्णांक		numa_node;	/* NUMA node this device is बंद to */
#पूर्ण_अगर
	dev_t			devt;	/* dev_t, creates the sysfs "dev" */
	u32			id;	/* device instance */

	spinlock_t		devres_lock;
	काष्ठा list_head	devres_head;

	काष्ठा class		*class;
	स्थिर काष्ठा attribute_group **groups;	/* optional groups */

	व्योम	(*release)(काष्ठा device *dev);
	काष्ठा iommu_group	*iommu_group;
	काष्ठा dev_iommu	*iommu;

	bool			offline_disabled:1;
	bool			offline:1;
	bool			of_node_reused:1;
	bool			state_synced:1;
	bool			can_match:1;
#अगर defined(CONFIG_ARCH_HAS_SYNC_DMA_FOR_DEVICE) || \
    defined(CONFIG_ARCH_HAS_SYNC_DMA_FOR_CPU) || \
    defined(CONFIG_ARCH_HAS_SYNC_DMA_FOR_CPU_ALL)
	bool			dma_coherent:1;
#पूर्ण_अगर
#अगर_घोषित CONFIG_DMA_OPS_BYPASS
	bool			dma_ops_bypass : 1;
#पूर्ण_अगर
पूर्ण;

/**
 * काष्ठा device_link - Device link representation.
 * @supplier: The device on the supplier end of the link.
 * @s_node: Hook to the supplier device's list of links to consumers.
 * @consumer: The device on the consumer end of the link.
 * @c_node: Hook to the consumer device's list of links to suppliers.
 * @link_dev: device used to expose link details in sysfs
 * @status: The state of the link (with respect to the presence of drivers).
 * @flags: Link flags.
 * @rpm_active: Whether or not the consumer device is runसमय-PM-active.
 * @kref: Count repeated addition of the same link.
 * @rm_work: Work काष्ठाure used क्रम removing the link.
 * @supplier_preactivated: Supplier has been made active beक्रमe consumer probe.
 */
काष्ठा device_link अणु
	काष्ठा device *supplier;
	काष्ठा list_head s_node;
	काष्ठा device *consumer;
	काष्ठा list_head c_node;
	काष्ठा device link_dev;
	क्रमागत device_link_state status;
	u32 flags;
	refcount_t rpm_active;
	काष्ठा kref kref;
	काष्ठा work_काष्ठा rm_work;
	bool supplier_preactivated; /* Owned by consumer probe. */
पूर्ण;

अटल अंतरभूत काष्ठा device *kobj_to_dev(काष्ठा kobject *kobj)
अणु
	वापस container_of(kobj, काष्ठा device, kobj);
पूर्ण

/**
 * device_iommu_mapped - Returns true when the device DMA is translated
 *			 by an IOMMU
 * @dev: Device to perक्रमm the check on
 */
अटल अंतरभूत bool device_iommu_mapped(काष्ठा device *dev)
अणु
	वापस (dev->iommu_group != शून्य);
पूर्ण

/* Get the wakeup routines, which depend on काष्ठा device */
#समावेश <linux/pm_wakeup.h>

अटल अंतरभूत स्थिर अक्षर *dev_name(स्थिर काष्ठा device *dev)
अणु
	/* Use the init name until the kobject becomes available */
	अगर (dev->init_name)
		वापस dev->init_name;

	वापस kobject_name(&dev->kobj);
पूर्ण

/**
 * dev_bus_name - Return a device's bus/class name, अगर at all possible
 * @dev: काष्ठा device to get the bus/class name of
 *
 * Will वापस the name of the bus/class the device is attached to.  If it is
 * not attached to a bus/class, an empty string will be वापसed.
 */
अटल अंतरभूत स्थिर अक्षर *dev_bus_name(स्थिर काष्ठा device *dev)
अणु
	वापस dev->bus ? dev->bus->name : (dev->class ? dev->class->name : "");
पूर्ण

__म_लिखो(2, 3) पूर्णांक dev_set_name(काष्ठा device *dev, स्थिर अक्षर *name, ...);

#अगर_घोषित CONFIG_NUMA
अटल अंतरभूत पूर्णांक dev_to_node(काष्ठा device *dev)
अणु
	वापस dev->numa_node;
पूर्ण
अटल अंतरभूत व्योम set_dev_node(काष्ठा device *dev, पूर्णांक node)
अणु
	dev->numa_node = node;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक dev_to_node(काष्ठा device *dev)
अणु
	वापस NUMA_NO_NODE;
पूर्ण
अटल अंतरभूत व्योम set_dev_node(काष्ठा device *dev, पूर्णांक node)
अणु
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत काष्ठा irq_करोमुख्य *dev_get_msi_करोमुख्य(स्थिर काष्ठा device *dev)
अणु
#अगर_घोषित CONFIG_GENERIC_MSI_IRQ_DOMAIN
	वापस dev->msi_करोमुख्य;
#अन्यथा
	वापस शून्य;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम dev_set_msi_करोमुख्य(काष्ठा device *dev, काष्ठा irq_करोमुख्य *d)
अणु
#अगर_घोषित CONFIG_GENERIC_MSI_IRQ_DOMAIN
	dev->msi_करोमुख्य = d;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम *dev_get_drvdata(स्थिर काष्ठा device *dev)
अणु
	वापस dev->driver_data;
पूर्ण

अटल अंतरभूत व्योम dev_set_drvdata(काष्ठा device *dev, व्योम *data)
अणु
	dev->driver_data = data;
पूर्ण

अटल अंतरभूत काष्ठा pm_subsys_data *dev_to_psd(काष्ठा device *dev)
अणु
	वापस dev ? dev->घातer.subsys_data : शून्य;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक dev_get_uevent_suppress(स्थिर काष्ठा device *dev)
अणु
	वापस dev->kobj.uevent_suppress;
पूर्ण

अटल अंतरभूत व्योम dev_set_uevent_suppress(काष्ठा device *dev, पूर्णांक val)
अणु
	dev->kobj.uevent_suppress = val;
पूर्ण

अटल अंतरभूत पूर्णांक device_is_रेजिस्टरed(काष्ठा device *dev)
अणु
	वापस dev->kobj.state_in_sysfs;
पूर्ण

अटल अंतरभूत व्योम device_enable_async_suspend(काष्ठा device *dev)
अणु
	अगर (!dev->घातer.is_prepared)
		dev->घातer.async_suspend = true;
पूर्ण

अटल अंतरभूत व्योम device_disable_async_suspend(काष्ठा device *dev)
अणु
	अगर (!dev->घातer.is_prepared)
		dev->घातer.async_suspend = false;
पूर्ण

अटल अंतरभूत bool device_async_suspend_enabled(काष्ठा device *dev)
अणु
	वापस !!dev->घातer.async_suspend;
पूर्ण

अटल अंतरभूत bool device_pm_not_required(काष्ठा device *dev)
अणु
	वापस dev->घातer.no_pm;
पूर्ण

अटल अंतरभूत व्योम device_set_pm_not_required(काष्ठा device *dev)
अणु
	dev->घातer.no_pm = true;
पूर्ण

अटल अंतरभूत व्योम dev_pm_syscore_device(काष्ठा device *dev, bool val)
अणु
#अगर_घोषित CONFIG_PM_SLEEP
	dev->घातer.syscore = val;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम dev_pm_set_driver_flags(काष्ठा device *dev, u32 flags)
अणु
	dev->घातer.driver_flags = flags;
पूर्ण

अटल अंतरभूत bool dev_pm_test_driver_flags(काष्ठा device *dev, u32 flags)
अणु
	वापस !!(dev->घातer.driver_flags & flags);
पूर्ण

अटल अंतरभूत व्योम device_lock(काष्ठा device *dev)
अणु
	mutex_lock(&dev->mutex);
पूर्ण

अटल अंतरभूत पूर्णांक device_lock_पूर्णांकerruptible(काष्ठा device *dev)
अणु
	वापस mutex_lock_पूर्णांकerruptible(&dev->mutex);
पूर्ण

अटल अंतरभूत पूर्णांक device_trylock(काष्ठा device *dev)
अणु
	वापस mutex_trylock(&dev->mutex);
पूर्ण

अटल अंतरभूत व्योम device_unlock(काष्ठा device *dev)
अणु
	mutex_unlock(&dev->mutex);
पूर्ण

अटल अंतरभूत व्योम device_lock_निश्चित(काष्ठा device *dev)
अणु
	lockdep_निश्चित_held(&dev->mutex);
पूर्ण

अटल अंतरभूत काष्ठा device_node *dev_of_node(काष्ठा device *dev)
अणु
	अगर (!IS_ENABLED(CONFIG_OF) || !dev)
		वापस शून्य;
	वापस dev->of_node;
पूर्ण

अटल अंतरभूत bool dev_has_sync_state(काष्ठा device *dev)
अणु
	अगर (!dev)
		वापस false;
	अगर (dev->driver && dev->driver->sync_state)
		वापस true;
	अगर (dev->bus && dev->bus->sync_state)
		वापस true;
	वापस false;
पूर्ण

/*
 * High level routines क्रम use by the bus drivers
 */
पूर्णांक __must_check device_रेजिस्टर(काष्ठा device *dev);
व्योम device_unरेजिस्टर(काष्ठा device *dev);
व्योम device_initialize(काष्ठा device *dev);
पूर्णांक __must_check device_add(काष्ठा device *dev);
व्योम device_del(काष्ठा device *dev);
पूर्णांक device_क्रम_each_child(काष्ठा device *dev, व्योम *data,
			  पूर्णांक (*fn)(काष्ठा device *dev, व्योम *data));
पूर्णांक device_क्रम_each_child_reverse(काष्ठा device *dev, व्योम *data,
				  पूर्णांक (*fn)(काष्ठा device *dev, व्योम *data));
काष्ठा device *device_find_child(काष्ठा device *dev, व्योम *data,
				 पूर्णांक (*match)(काष्ठा device *dev, व्योम *data));
काष्ठा device *device_find_child_by_name(काष्ठा device *parent,
					 स्थिर अक्षर *name);
पूर्णांक device_नाम(काष्ठा device *dev, स्थिर अक्षर *new_name);
पूर्णांक device_move(काष्ठा device *dev, काष्ठा device *new_parent,
		क्रमागत dpm_order dpm_order);
पूर्णांक device_change_owner(काष्ठा device *dev, kuid_t kuid, kgid_t kgid);
स्थिर अक्षर *device_get_devnode(काष्ठा device *dev, umode_t *mode, kuid_t *uid,
			       kgid_t *gid, स्थिर अक्षर **पंचांगp);
पूर्णांक device_is_dependent(काष्ठा device *dev, व्योम *target);

अटल अंतरभूत bool device_supports_offline(काष्ठा device *dev)
अणु
	वापस dev->bus && dev->bus->offline && dev->bus->online;
पूर्ण

व्योम lock_device_hotplug(व्योम);
व्योम unlock_device_hotplug(व्योम);
पूर्णांक lock_device_hotplug_sysfs(व्योम);
पूर्णांक device_offline(काष्ठा device *dev);
पूर्णांक device_online(काष्ठा device *dev);
व्योम set_primary_fwnode(काष्ठा device *dev, काष्ठा fwnode_handle *fwnode);
व्योम set_secondary_fwnode(काष्ठा device *dev, काष्ठा fwnode_handle *fwnode);
व्योम device_set_of_node_from_dev(काष्ठा device *dev, स्थिर काष्ठा device *dev2);

अटल अंतरभूत पूर्णांक dev_num_vf(काष्ठा device *dev)
अणु
	अगर (dev->bus && dev->bus->num_vf)
		वापस dev->bus->num_vf(dev);
	वापस 0;
पूर्ण

/*
 * Root device objects क्रम grouping under /sys/devices
 */
काष्ठा device *__root_device_रेजिस्टर(स्थिर अक्षर *name, काष्ठा module *owner);

/* This is a macro to aव्योम include problems with THIS_MODULE */
#घोषणा root_device_रेजिस्टर(name) \
	__root_device_रेजिस्टर(name, THIS_MODULE)

व्योम root_device_unरेजिस्टर(काष्ठा device *root);

अटल अंतरभूत व्योम *dev_get_platdata(स्थिर काष्ठा device *dev)
अणु
	वापस dev->platक्रमm_data;
पूर्ण

/*
 * Manual binding of a device to driver. See drivers/base/bus.c
 * क्रम inक्रमmation on use.
 */
पूर्णांक __must_check device_bind_driver(काष्ठा device *dev);
व्योम device_release_driver(काष्ठा device *dev);
पूर्णांक  __must_check device_attach(काष्ठा device *dev);
पूर्णांक __must_check driver_attach(काष्ठा device_driver *drv);
व्योम device_initial_probe(काष्ठा device *dev);
पूर्णांक __must_check device_reprobe(काष्ठा device *dev);

bool device_is_bound(काष्ठा device *dev);

/*
 * Easy functions क्रम dynamically creating devices on the fly
 */
__म_लिखो(5, 6) काष्ठा device *
device_create(काष्ठा class *cls, काष्ठा device *parent, dev_t devt,
	      व्योम *drvdata, स्थिर अक्षर *fmt, ...);
__म_लिखो(6, 7) काष्ठा device *
device_create_with_groups(काष्ठा class *cls, काष्ठा device *parent, dev_t devt,
			  व्योम *drvdata, स्थिर काष्ठा attribute_group **groups,
			  स्थिर अक्षर *fmt, ...);
व्योम device_destroy(काष्ठा class *cls, dev_t devt);

पूर्णांक __must_check device_add_groups(काष्ठा device *dev,
				   स्थिर काष्ठा attribute_group **groups);
व्योम device_हटाओ_groups(काष्ठा device *dev,
			  स्थिर काष्ठा attribute_group **groups);

अटल अंतरभूत पूर्णांक __must_check device_add_group(काष्ठा device *dev,
					स्थिर काष्ठा attribute_group *grp)
अणु
	स्थिर काष्ठा attribute_group *groups[] = अणु grp, शून्य पूर्ण;

	वापस device_add_groups(dev, groups);
पूर्ण

अटल अंतरभूत व्योम device_हटाओ_group(काष्ठा device *dev,
				       स्थिर काष्ठा attribute_group *grp)
अणु
	स्थिर काष्ठा attribute_group *groups[] = अणु grp, शून्य पूर्ण;

	वापस device_हटाओ_groups(dev, groups);
पूर्ण

पूर्णांक __must_check devm_device_add_groups(काष्ठा device *dev,
					स्थिर काष्ठा attribute_group **groups);
व्योम devm_device_हटाओ_groups(काष्ठा device *dev,
			       स्थिर काष्ठा attribute_group **groups);
पूर्णांक __must_check devm_device_add_group(काष्ठा device *dev,
				       स्थिर काष्ठा attribute_group *grp);
व्योम devm_device_हटाओ_group(काष्ठा device *dev,
			      स्थिर काष्ठा attribute_group *grp);

/*
 * Platक्रमm "fixup" functions - allow the platक्रमm to have their say
 * about devices and actions that the general device layer करोesn't
 * know about.
 */
/* Notअगरy platक्रमm of device discovery */
बाह्य पूर्णांक (*platक्रमm_notअगरy)(काष्ठा device *dev);

बाह्य पूर्णांक (*platक्रमm_notअगरy_हटाओ)(काष्ठा device *dev);


/*
 * get_device - atomically increment the reference count क्रम the device.
 *
 */
काष्ठा device *get_device(काष्ठा device *dev);
व्योम put_device(काष्ठा device *dev);
bool समाप्त_device(काष्ठा device *dev);

#अगर_घोषित CONFIG_DEVTMPFS
पूर्णांक devपंचांगpfs_mount(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक devपंचांगpfs_mount(व्योम) अणु वापस 0; पूर्ण
#पूर्ण_अगर

/* drivers/base/घातer/shutकरोwn.c */
व्योम device_shutकरोwn(व्योम);

/* debugging and troubleshooting/diagnostic helpers. */
स्थिर अक्षर *dev_driver_string(स्थिर काष्ठा device *dev);

/* Device links पूर्णांकerface. */
काष्ठा device_link *device_link_add(काष्ठा device *consumer,
				    काष्ठा device *supplier, u32 flags);
व्योम device_link_del(काष्ठा device_link *link);
व्योम device_link_हटाओ(व्योम *consumer, काष्ठा device *supplier);
व्योम device_links_supplier_sync_state_छोड़ो(व्योम);
व्योम device_links_supplier_sync_state_resume(व्योम);

बाह्य __म_लिखो(3, 4)
पूर्णांक dev_err_probe(स्थिर काष्ठा device *dev, पूर्णांक err, स्थिर अक्षर *fmt, ...);

/* Create alias, so I can be स्वतःloaded. */
#घोषणा MODULE_ALIAS_CHARDEV(major,minor) \
	MODULE_ALIAS("char-major-" __stringअगरy(major) "-" __stringअगरy(minor))
#घोषणा MODULE_ALIAS_CHARDEV_MAJOR(major) \
	MODULE_ALIAS("char-major-" __stringअगरy(major) "-*")

#अगर_घोषित CONFIG_SYSFS_DEPRECATED
बाह्य दीर्घ sysfs_deprecated;
#अन्यथा
#घोषणा sysfs_deprecated 0
#पूर्ण_अगर

#पूर्ण_अगर /* _DEVICE_H_ */
