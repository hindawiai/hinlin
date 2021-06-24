<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (c) 2009-2013, NVIDIA Corporation. All rights reserved.
 */

#अगर_अघोषित __LINUX_HOST1X_H
#घोषणा __LINUX_HOST1X_H

#समावेश <linux/device.h>
#समावेश <linux/types.h>

क्रमागत host1x_class अणु
	HOST1X_CLASS_HOST1X = 0x1,
	HOST1X_CLASS_GR2D = 0x51,
	HOST1X_CLASS_GR2D_SB = 0x52,
	HOST1X_CLASS_VIC = 0x5D,
	HOST1X_CLASS_GR3D = 0x60,
पूर्ण;

काष्ठा host1x;
काष्ठा host1x_client;
काष्ठा iommu_group;

u64 host1x_get_dma_mask(काष्ठा host1x *host1x);

/**
 * काष्ठा host1x_client_ops - host1x client operations
 * @early_init: host1x client early initialization code
 * @init: host1x client initialization code
 * @निकास: host1x client tear करोwn code
 * @late_निकास: host1x client late tear करोwn code
 * @suspend: host1x client suspend code
 * @resume: host1x client resume code
 */
काष्ठा host1x_client_ops अणु
	पूर्णांक (*early_init)(काष्ठा host1x_client *client);
	पूर्णांक (*init)(काष्ठा host1x_client *client);
	पूर्णांक (*निकास)(काष्ठा host1x_client *client);
	पूर्णांक (*late_निकास)(काष्ठा host1x_client *client);
	पूर्णांक (*suspend)(काष्ठा host1x_client *client);
	पूर्णांक (*resume)(काष्ठा host1x_client *client);
पूर्ण;

/**
 * काष्ठा host1x_client - host1x client काष्ठाure
 * @list: list node क्रम the host1x client
 * @host: poपूर्णांकer to काष्ठा device representing the host1x controller
 * @dev: poपूर्णांकer to काष्ठा device backing this host1x client
 * @group: IOMMU group that this client is a member of
 * @ops: host1x client operations
 * @class: host1x class represented by this client
 * @channel: host1x channel associated with this client
 * @syncpts: array of syncpoपूर्णांकs requested क्रम this client
 * @num_syncpts: number of syncpoपूर्णांकs requested क्रम this client
 * @parent: poपूर्णांकer to parent काष्ठाure
 * @usecount: reference count क्रम this काष्ठाure
 * @lock: mutex क्रम mutually exclusive concurrency
 */
काष्ठा host1x_client अणु
	काष्ठा list_head list;
	काष्ठा device *host;
	काष्ठा device *dev;
	काष्ठा iommu_group *group;

	स्थिर काष्ठा host1x_client_ops *ops;

	क्रमागत host1x_class class;
	काष्ठा host1x_channel *channel;

	काष्ठा host1x_syncpt **syncpts;
	अचिन्हित पूर्णांक num_syncpts;

	काष्ठा host1x_client *parent;
	अचिन्हित पूर्णांक usecount;
	काष्ठा mutex lock;
पूर्ण;

/*
 * host1x buffer objects
 */

काष्ठा host1x_bo;
काष्ठा sg_table;

काष्ठा host1x_bo_ops अणु
	काष्ठा host1x_bo *(*get)(काष्ठा host1x_bo *bo);
	व्योम (*put)(काष्ठा host1x_bo *bo);
	काष्ठा sg_table *(*pin)(काष्ठा device *dev, काष्ठा host1x_bo *bo,
				dma_addr_t *phys);
	व्योम (*unpin)(काष्ठा device *dev, काष्ठा sg_table *sgt);
	व्योम *(*mmap)(काष्ठा host1x_bo *bo);
	व्योम (*munmap)(काष्ठा host1x_bo *bo, व्योम *addr);
पूर्ण;

काष्ठा host1x_bo अणु
	स्थिर काष्ठा host1x_bo_ops *ops;
पूर्ण;

अटल अंतरभूत व्योम host1x_bo_init(काष्ठा host1x_bo *bo,
				  स्थिर काष्ठा host1x_bo_ops *ops)
अणु
	bo->ops = ops;
पूर्ण

अटल अंतरभूत काष्ठा host1x_bo *host1x_bo_get(काष्ठा host1x_bo *bo)
अणु
	वापस bo->ops->get(bo);
पूर्ण

अटल अंतरभूत व्योम host1x_bo_put(काष्ठा host1x_bo *bo)
अणु
	bo->ops->put(bo);
पूर्ण

अटल अंतरभूत काष्ठा sg_table *host1x_bo_pin(काष्ठा device *dev,
					     काष्ठा host1x_bo *bo,
					     dma_addr_t *phys)
अणु
	वापस bo->ops->pin(dev, bo, phys);
पूर्ण

अटल अंतरभूत व्योम host1x_bo_unpin(काष्ठा device *dev, काष्ठा host1x_bo *bo,
				   काष्ठा sg_table *sgt)
अणु
	bo->ops->unpin(dev, sgt);
पूर्ण

अटल अंतरभूत व्योम *host1x_bo_mmap(काष्ठा host1x_bo *bo)
अणु
	वापस bo->ops->mmap(bo);
पूर्ण

अटल अंतरभूत व्योम host1x_bo_munmap(काष्ठा host1x_bo *bo, व्योम *addr)
अणु
	bo->ops->munmap(bo, addr);
पूर्ण

/*
 * host1x syncpoपूर्णांकs
 */

#घोषणा HOST1X_SYNCPT_CLIENT_MANAGED	(1 << 0)
#घोषणा HOST1X_SYNCPT_HAS_BASE		(1 << 1)

काष्ठा host1x_syncpt_base;
काष्ठा host1x_syncpt;
काष्ठा host1x;

काष्ठा host1x_syncpt *host1x_syncpt_get_by_id(काष्ठा host1x *host, u32 id);
काष्ठा host1x_syncpt *host1x_syncpt_get_by_id_noref(काष्ठा host1x *host, u32 id);
काष्ठा host1x_syncpt *host1x_syncpt_get(काष्ठा host1x_syncpt *sp);
u32 host1x_syncpt_id(काष्ठा host1x_syncpt *sp);
u32 host1x_syncpt_पढ़ो_min(काष्ठा host1x_syncpt *sp);
u32 host1x_syncpt_पढ़ो_max(काष्ठा host1x_syncpt *sp);
u32 host1x_syncpt_पढ़ो(काष्ठा host1x_syncpt *sp);
पूर्णांक host1x_syncpt_incr(काष्ठा host1x_syncpt *sp);
u32 host1x_syncpt_incr_max(काष्ठा host1x_syncpt *sp, u32 incrs);
पूर्णांक host1x_syncpt_रुको(काष्ठा host1x_syncpt *sp, u32 thresh, दीर्घ समयout,
		       u32 *value);
काष्ठा host1x_syncpt *host1x_syncpt_request(काष्ठा host1x_client *client,
					    अचिन्हित दीर्घ flags);
व्योम host1x_syncpt_put(काष्ठा host1x_syncpt *sp);
काष्ठा host1x_syncpt *host1x_syncpt_alloc(काष्ठा host1x *host,
					  अचिन्हित दीर्घ flags,
					  स्थिर अक्षर *name);

काष्ठा host1x_syncpt_base *host1x_syncpt_get_base(काष्ठा host1x_syncpt *sp);
u32 host1x_syncpt_base_id(काष्ठा host1x_syncpt_base *base);

व्योम host1x_syncpt_release_vblank_reservation(काष्ठा host1x_client *client,
					      u32 syncpt_id);

/*
 * host1x channel
 */

काष्ठा host1x_channel;
काष्ठा host1x_job;

काष्ठा host1x_channel *host1x_channel_request(काष्ठा host1x_client *client);
काष्ठा host1x_channel *host1x_channel_get(काष्ठा host1x_channel *channel);
व्योम host1x_channel_put(काष्ठा host1x_channel *channel);
पूर्णांक host1x_job_submit(काष्ठा host1x_job *job);

/*
 * host1x job
 */

#घोषणा HOST1X_RELOC_READ	(1 << 0)
#घोषणा HOST1X_RELOC_WRITE	(1 << 1)

काष्ठा host1x_reloc अणु
	काष्ठा अणु
		काष्ठा host1x_bo *bo;
		अचिन्हित दीर्घ offset;
	पूर्ण cmdbuf;
	काष्ठा अणु
		काष्ठा host1x_bo *bo;
		अचिन्हित दीर्घ offset;
	पूर्ण target;
	अचिन्हित दीर्घ shअगरt;
	अचिन्हित दीर्घ flags;
पूर्ण;

काष्ठा host1x_job अणु
	/* When refcount goes to zero, job can be मुक्तd */
	काष्ठा kref ref;

	/* List entry */
	काष्ठा list_head list;

	/* Channel where job is submitted to */
	काष्ठा host1x_channel *channel;

	/* client where the job originated */
	काष्ठा host1x_client *client;

	/* Gathers and their memory */
	काष्ठा host1x_job_gather *gathers;
	अचिन्हित पूर्णांक num_gathers;

	/* Array of handles to be pinned & unpinned */
	काष्ठा host1x_reloc *relocs;
	अचिन्हित पूर्णांक num_relocs;
	काष्ठा host1x_job_unpin_data *unpins;
	अचिन्हित पूर्णांक num_unpins;

	dma_addr_t *addr_phys;
	dma_addr_t *gather_addr_phys;
	dma_addr_t *reloc_addr_phys;

	/* Sync poपूर्णांक id, number of increments and end related to the submit */
	काष्ठा host1x_syncpt *syncpt;
	u32 syncpt_incrs;
	u32 syncpt_end;

	/* Maximum समय to रुको क्रम this job */
	अचिन्हित पूर्णांक समयout;

	/* Index and number of slots used in the push buffer */
	अचिन्हित पूर्णांक first_get;
	अचिन्हित पूर्णांक num_slots;

	/* Copy of gathers */
	माप_प्रकार gather_copy_size;
	dma_addr_t gather_copy;
	u8 *gather_copy_mapped;

	/* Check अगर रेजिस्टर is marked as an address reg */
	पूर्णांक (*is_addr_reg)(काष्ठा device *dev, u32 class, u32 reg);

	/* Check अगर class beदीर्घs to the unit */
	पूर्णांक (*is_valid_class)(u32 class);

	/* Request a SETCLASS to this class */
	u32 class;

	/* Add a channel रुको क्रम previous ops to complete */
	bool serialize;
पूर्ण;

काष्ठा host1x_job *host1x_job_alloc(काष्ठा host1x_channel *ch,
				    u32 num_cmdbufs, u32 num_relocs);
व्योम host1x_job_add_gather(काष्ठा host1x_job *job, काष्ठा host1x_bo *bo,
			   अचिन्हित पूर्णांक words, अचिन्हित पूर्णांक offset);
काष्ठा host1x_job *host1x_job_get(काष्ठा host1x_job *job);
व्योम host1x_job_put(काष्ठा host1x_job *job);
पूर्णांक host1x_job_pin(काष्ठा host1x_job *job, काष्ठा device *dev);
व्योम host1x_job_unpin(काष्ठा host1x_job *job);

/*
 * subdevice probe infraकाष्ठाure
 */

काष्ठा host1x_device;

/**
 * काष्ठा host1x_driver - host1x logical device driver
 * @driver: core driver
 * @subdevs: table of OF device IDs matching subdevices क्रम this driver
 * @list: list node क्रम the driver
 * @probe: called when the host1x logical device is probed
 * @हटाओ: called when the host1x logical device is हटाओd
 * @shutकरोwn: called when the host1x logical device is shut करोwn
 */
काष्ठा host1x_driver अणु
	काष्ठा device_driver driver;

	स्थिर काष्ठा of_device_id *subdevs;
	काष्ठा list_head list;

	पूर्णांक (*probe)(काष्ठा host1x_device *device);
	पूर्णांक (*हटाओ)(काष्ठा host1x_device *device);
	व्योम (*shutकरोwn)(काष्ठा host1x_device *device);
पूर्ण;

अटल अंतरभूत काष्ठा host1x_driver *
to_host1x_driver(काष्ठा device_driver *driver)
अणु
	वापस container_of(driver, काष्ठा host1x_driver, driver);
पूर्ण

पूर्णांक host1x_driver_रेजिस्टर_full(काष्ठा host1x_driver *driver,
				काष्ठा module *owner);
व्योम host1x_driver_unरेजिस्टर(काष्ठा host1x_driver *driver);

#घोषणा host1x_driver_रेजिस्टर(driver) \
	host1x_driver_रेजिस्टर_full(driver, THIS_MODULE)

काष्ठा host1x_device अणु
	काष्ठा host1x_driver *driver;
	काष्ठा list_head list;
	काष्ठा device dev;

	काष्ठा mutex subdevs_lock;
	काष्ठा list_head subdevs;
	काष्ठा list_head active;

	काष्ठा mutex clients_lock;
	काष्ठा list_head clients;

	bool रेजिस्टरed;

	काष्ठा device_dma_parameters dma_parms;
पूर्ण;

अटल अंतरभूत काष्ठा host1x_device *to_host1x_device(काष्ठा device *dev)
अणु
	वापस container_of(dev, काष्ठा host1x_device, dev);
पूर्ण

पूर्णांक host1x_device_init(काष्ठा host1x_device *device);
पूर्णांक host1x_device_निकास(काष्ठा host1x_device *device);

व्योम __host1x_client_init(काष्ठा host1x_client *client, काष्ठा lock_class_key *key);
व्योम host1x_client_निकास(काष्ठा host1x_client *client);

#घोषणा host1x_client_init(client)			\
	(अणु						\
		अटल काष्ठा lock_class_key __key;	\
		__host1x_client_init(client, &__key);	\
	पूर्ण)

पूर्णांक __host1x_client_रेजिस्टर(काष्ठा host1x_client *client);

/*
 * Note that this wrapper calls __host1x_client_init() क्रम compatibility
 * with existing callers. Callers that want to separately initialize and
 * रेजिस्टर a host1x client must first initialize using either of the
 * __host1x_client_init() or host1x_client_init() functions and then use
 * the low-level __host1x_client_रेजिस्टर() function to aव्योम the client
 * getting reinitialized.
 */
#घोषणा host1x_client_रेजिस्टर(client)			\
	(अणु						\
		अटल काष्ठा lock_class_key __key;	\
		__host1x_client_init(client, &__key);	\
		__host1x_client_रेजिस्टर(client);	\
	पूर्ण)

पूर्णांक host1x_client_unरेजिस्टर(काष्ठा host1x_client *client);

पूर्णांक host1x_client_suspend(काष्ठा host1x_client *client);
पूर्णांक host1x_client_resume(काष्ठा host1x_client *client);

काष्ठा tegra_mipi_device;

काष्ठा tegra_mipi_device *tegra_mipi_request(काष्ठा device *device,
					     काष्ठा device_node *np);
व्योम tegra_mipi_मुक्त(काष्ठा tegra_mipi_device *device);
पूर्णांक tegra_mipi_enable(काष्ठा tegra_mipi_device *device);
पूर्णांक tegra_mipi_disable(काष्ठा tegra_mipi_device *device);
पूर्णांक tegra_mipi_start_calibration(काष्ठा tegra_mipi_device *device);
पूर्णांक tegra_mipi_finish_calibration(काष्ठा tegra_mipi_device *device);

#पूर्ण_अगर
