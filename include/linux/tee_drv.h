<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2015-2016, Linaro Limited
 */

#अगर_अघोषित __TEE_DRV_H
#घोषणा __TEE_DRV_H

#समावेश <linux/device.h>
#समावेश <linux/idr.h>
#समावेश <linux/kref.h>
#समावेश <linux/list.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/tee.h>
#समावेश <linux/types.h>
#समावेश <linux/uuid.h>

/*
 * The file describes the API provided by the generic TEE driver to the
 * specअगरic TEE driver.
 */

#घोषणा TEE_SHM_MAPPED		BIT(0)	/* Memory mapped by the kernel */
#घोषणा TEE_SHM_DMA_BUF		BIT(1)	/* Memory with dma-buf handle */
#घोषणा TEE_SHM_EXT_DMA_BUF	BIT(2)	/* Memory with dma-buf handle */
#घोषणा TEE_SHM_REGISTER	BIT(3)  /* Memory रेजिस्टरed in secure world */
#घोषणा TEE_SHM_USER_MAPPED	BIT(4)  /* Memory mapped in user space */
#घोषणा TEE_SHM_POOL		BIT(5)  /* Memory allocated from pool */
#घोषणा TEE_SHM_KERNEL_MAPPED	BIT(6)  /* Memory mapped in kernel space */

काष्ठा device;
काष्ठा tee_device;
काष्ठा tee_shm;
काष्ठा tee_shm_pool;

/**
 * काष्ठा tee_context - driver specअगरic context on file poपूर्णांकer data
 * @teedev:	poपूर्णांकer to this drivers काष्ठा tee_device
 * @list_shm:	List of shared memory object owned by this context
 * @data:	driver specअगरic context data, managed by the driver
 * @refcount:	reference counter क्रम this काष्ठाure
 * @releasing:  flag that indicates अगर context is being released right now.
 *		It is needed to अवरोध circular dependency on context during
 *              shared memory release.
 * @supp_noरुको: flag that indicates that requests in this context should not
 *              रुको क्रम tee-supplicant daemon to be started अगर not present
 *              and just वापस with an error code. It is needed क्रम requests
 *              that arises from TEE based kernel drivers that should be
 *              non-blocking in nature.
 * @cap_memref_null: flag indicating अगर the TEE Client support shared
 *                   memory buffer with a शून्य poपूर्णांकer.
 */
काष्ठा tee_context अणु
	काष्ठा tee_device *teedev;
	व्योम *data;
	काष्ठा kref refcount;
	bool releasing;
	bool supp_noरुको;
	bool cap_memref_null;
पूर्ण;

काष्ठा tee_param_memref अणु
	माप_प्रकार shm_offs;
	माप_प्रकार size;
	काष्ठा tee_shm *shm;
पूर्ण;

काष्ठा tee_param_value अणु
	u64 a;
	u64 b;
	u64 c;
पूर्ण;

काष्ठा tee_param अणु
	u64 attr;
	जोड़ अणु
		काष्ठा tee_param_memref memref;
		काष्ठा tee_param_value value;
	पूर्ण u;
पूर्ण;

/**
 * काष्ठा tee_driver_ops - driver operations vtable
 * @get_version:	वापसs version of driver
 * @खोलो:		called when the device file is खोलोed
 * @release:		release this खोलो file
 * @खोलो_session:	खोलो a new session
 * @बंद_session:	बंद a session
 * @invoke_func:	invoke a trusted function
 * @cancel_req:		request cancel of an ongoing invoke or खोलो
 * @supp_recv:		called क्रम supplicant to get a command
 * @supp_send:		called क्रम supplicant to send a response
 * @shm_रेजिस्टर:	रेजिस्टर shared memory buffer in TEE
 * @shm_unरेजिस्टर:	unरेजिस्टर shared memory buffer in TEE
 */
काष्ठा tee_driver_ops अणु
	व्योम (*get_version)(काष्ठा tee_device *teedev,
			    काष्ठा tee_ioctl_version_data *vers);
	पूर्णांक (*खोलो)(काष्ठा tee_context *ctx);
	व्योम (*release)(काष्ठा tee_context *ctx);
	पूर्णांक (*खोलो_session)(काष्ठा tee_context *ctx,
			    काष्ठा tee_ioctl_खोलो_session_arg *arg,
			    काष्ठा tee_param *param);
	पूर्णांक (*बंद_session)(काष्ठा tee_context *ctx, u32 session);
	पूर्णांक (*invoke_func)(काष्ठा tee_context *ctx,
			   काष्ठा tee_ioctl_invoke_arg *arg,
			   काष्ठा tee_param *param);
	पूर्णांक (*cancel_req)(काष्ठा tee_context *ctx, u32 cancel_id, u32 session);
	पूर्णांक (*supp_recv)(काष्ठा tee_context *ctx, u32 *func, u32 *num_params,
			 काष्ठा tee_param *param);
	पूर्णांक (*supp_send)(काष्ठा tee_context *ctx, u32 ret, u32 num_params,
			 काष्ठा tee_param *param);
	पूर्णांक (*shm_रेजिस्टर)(काष्ठा tee_context *ctx, काष्ठा tee_shm *shm,
			    काष्ठा page **pages, माप_प्रकार num_pages,
			    अचिन्हित दीर्घ start);
	पूर्णांक (*shm_unरेजिस्टर)(काष्ठा tee_context *ctx, काष्ठा tee_shm *shm);
पूर्ण;

/**
 * काष्ठा tee_desc - Describes the TEE driver to the subप्रणाली
 * @name:	name of driver
 * @ops:	driver operations vtable
 * @owner:	module providing the driver
 * @flags:	Extra properties of driver, defined by TEE_DESC_* below
 */
#घोषणा TEE_DESC_PRIVILEGED	0x1
काष्ठा tee_desc अणु
	स्थिर अक्षर *name;
	स्थिर काष्ठा tee_driver_ops *ops;
	काष्ठा module *owner;
	u32 flags;
पूर्ण;

/**
 * tee_device_alloc() - Allocate a new काष्ठा tee_device instance
 * @teedesc:	Descriptor क्रम this driver
 * @dev:	Parent device क्रम this device
 * @pool:	Shared memory pool, शून्य अगर not used
 * @driver_data: Private driver data क्रम this device
 *
 * Allocates a new काष्ठा tee_device instance. The device is
 * हटाओd by tee_device_unरेजिस्टर().
 *
 * @वापसs a poपूर्णांकer to a 'struct tee_device' or an ERR_PTR on failure
 */
काष्ठा tee_device *tee_device_alloc(स्थिर काष्ठा tee_desc *teedesc,
				    काष्ठा device *dev,
				    काष्ठा tee_shm_pool *pool,
				    व्योम *driver_data);

/**
 * tee_device_रेजिस्टर() - Registers a TEE device
 * @teedev:	Device to रेजिस्टर
 *
 * tee_device_unरेजिस्टर() need to be called to हटाओ the @teedev अगर
 * this function fails.
 *
 * @वापसs < 0 on failure
 */
पूर्णांक tee_device_रेजिस्टर(काष्ठा tee_device *teedev);

/**
 * tee_device_unरेजिस्टर() - Removes a TEE device
 * @teedev:	Device to unरेजिस्टर
 *
 * This function should be called to हटाओ the @teedev even अगर
 * tee_device_रेजिस्टर() hasn't been called yet. Does nothing अगर
 * @teedev is शून्य.
 */
व्योम tee_device_unरेजिस्टर(काष्ठा tee_device *teedev);

/**
 * tee_session_calc_client_uuid() - Calculates client UUID क्रम session
 * @uuid:		Resulting UUID
 * @connection_method:	Connection method क्रम session (TEE_IOCTL_LOGIN_*)
 * @connectuon_data:	Connection data क्रम खोलोing session
 *
 * Based on connection method calculates UUIDv5 based client UUID.
 *
 * For group based logins verअगरies that calling process has specअगरied
 * credentials.
 *
 * @वापस < 0 on failure
 */
पूर्णांक tee_session_calc_client_uuid(uuid_t *uuid, u32 connection_method,
				 स्थिर u8 connection_data[TEE_IOCTL_UUID_LEN]);

/**
 * काष्ठा tee_shm - shared memory object
 * @ctx:	context using the object
 * @paddr:	physical address of the shared memory
 * @kaddr:	भव address of the shared memory
 * @size:	size of shared memory
 * @offset:	offset of buffer in user space
 * @pages:	locked pages from userspace
 * @num_pages:	number of locked pages
 * @dmabuf:	dmabuf used to क्रम exporting to user space
 * @flags:	defined by TEE_SHM_* in tee_drv.h
 * @id:		unique id of a shared memory object on this device
 *
 * This pool is only supposed to be accessed directly from the TEE
 * subप्रणाली and from drivers that implements their own shm pool manager.
 */
काष्ठा tee_shm अणु
	काष्ठा tee_context *ctx;
	phys_addr_t paddr;
	व्योम *kaddr;
	माप_प्रकार size;
	अचिन्हित पूर्णांक offset;
	काष्ठा page **pages;
	माप_प्रकार num_pages;
	काष्ठा dma_buf *dmabuf;
	u32 flags;
	पूर्णांक id;
पूर्ण;

/**
 * काष्ठा tee_shm_pool_mgr - shared memory manager
 * @ops:		operations
 * @निजी_data:	निजी data क्रम the shared memory manager
 */
काष्ठा tee_shm_pool_mgr अणु
	स्थिर काष्ठा tee_shm_pool_mgr_ops *ops;
	व्योम *निजी_data;
पूर्ण;

/**
 * काष्ठा tee_shm_pool_mgr_ops - shared memory pool manager operations
 * @alloc:		called when allocating shared memory
 * @मुक्त:		called when मुक्तing shared memory
 * @destroy_poolmgr:	called when destroying the pool manager
 */
काष्ठा tee_shm_pool_mgr_ops अणु
	पूर्णांक (*alloc)(काष्ठा tee_shm_pool_mgr *poolmgr, काष्ठा tee_shm *shm,
		     माप_प्रकार size);
	व्योम (*मुक्त)(काष्ठा tee_shm_pool_mgr *poolmgr, काष्ठा tee_shm *shm);
	व्योम (*destroy_poolmgr)(काष्ठा tee_shm_pool_mgr *poolmgr);
पूर्ण;

/**
 * tee_shm_pool_alloc() - Create a shared memory pool from shm managers
 * @priv_mgr:	manager क्रम driver निजी shared memory allocations
 * @dmabuf_mgr:	manager क्रम dma-buf shared memory allocations
 *
 * Allocation with the flag TEE_SHM_DMA_BUF set will use the range supplied
 * in @dmabuf, others will use the range provided by @priv.
 *
 * @वापसs poपूर्णांकer to a 'struct tee_shm_pool' or an ERR_PTR on failure.
 */
काष्ठा tee_shm_pool *tee_shm_pool_alloc(काष्ठा tee_shm_pool_mgr *priv_mgr,
					काष्ठा tee_shm_pool_mgr *dmabuf_mgr);

/*
 * tee_shm_pool_mgr_alloc_res_mem() - Create a shm manager क्रम reserved
 * memory
 * @vaddr:	Virtual address of start of pool
 * @paddr:	Physical address of start of pool
 * @size:	Size in bytes of the pool
 *
 * @वापसs poपूर्णांकer to a 'struct tee_shm_pool_mgr' or an ERR_PTR on failure.
 */
काष्ठा tee_shm_pool_mgr *tee_shm_pool_mgr_alloc_res_mem(अचिन्हित दीर्घ vaddr,
							phys_addr_t paddr,
							माप_प्रकार size,
							पूर्णांक min_alloc_order);

/**
 * tee_shm_pool_mgr_destroy() - Free a shared memory manager
 */
अटल अंतरभूत व्योम tee_shm_pool_mgr_destroy(काष्ठा tee_shm_pool_mgr *poolm)
अणु
	poolm->ops->destroy_poolmgr(poolm);
पूर्ण

/**
 * काष्ठा tee_shm_pool_mem_info - holds inक्रमmation needed to create a shared
 * memory pool
 * @vaddr:	Virtual address of start of pool
 * @paddr:	Physical address of start of pool
 * @size:	Size in bytes of the pool
 */
काष्ठा tee_shm_pool_mem_info अणु
	अचिन्हित दीर्घ vaddr;
	phys_addr_t paddr;
	माप_प्रकार size;
पूर्ण;

/**
 * tee_shm_pool_alloc_res_mem() - Create a shared memory pool from reserved
 * memory range
 * @priv_info:	 Inक्रमmation क्रम driver निजी shared memory pool
 * @dmabuf_info: Inक्रमmation क्रम dma-buf shared memory pool
 *
 * Start and end of pools will must be page aligned.
 *
 * Allocation with the flag TEE_SHM_DMA_BUF set will use the range supplied
 * in @dmabuf, others will use the range provided by @priv.
 *
 * @वापसs poपूर्णांकer to a 'struct tee_shm_pool' or an ERR_PTR on failure.
 */
काष्ठा tee_shm_pool *
tee_shm_pool_alloc_res_mem(काष्ठा tee_shm_pool_mem_info *priv_info,
			   काष्ठा tee_shm_pool_mem_info *dmabuf_info);

/**
 * tee_shm_pool_मुक्त() - Free a shared memory pool
 * @pool:	The shared memory pool to मुक्त
 *
 * The must be no reमुख्यing shared memory allocated from this pool when
 * this function is called.
 */
व्योम tee_shm_pool_मुक्त(काष्ठा tee_shm_pool *pool);

/**
 * tee_get_drvdata() - Return driver_data poपूर्णांकer
 * @वापसs the driver_data poपूर्णांकer supplied to tee_रेजिस्टर().
 */
व्योम *tee_get_drvdata(काष्ठा tee_device *teedev);

/**
 * tee_shm_alloc() - Allocate shared memory
 * @ctx:	Context that allocates the shared memory
 * @size:	Requested size of shared memory
 * @flags:	Flags setting properties क्रम the requested shared memory.
 *
 * Memory allocated as global shared memory is स्वतःmatically मुक्तd when the
 * TEE file poपूर्णांकer is बंदd. The @flags field uses the bits defined by
 * TEE_SHM_* above. TEE_SHM_MAPPED must currently always be set. If
 * TEE_SHM_DMA_BUF global shared memory will be allocated and associated
 * with a dma-buf handle, अन्यथा driver निजी memory.
 *
 * @वापसs a poपूर्णांकer to 'struct tee_shm'
 */
काष्ठा tee_shm *tee_shm_alloc(काष्ठा tee_context *ctx, माप_प्रकार size, u32 flags);

/**
 * tee_shm_रेजिस्टर() - Register shared memory buffer
 * @ctx:	Context that रेजिस्टरs the shared memory
 * @addr:	Address is userspace of the shared buffer
 * @length:	Length of the shared buffer
 * @flags:	Flags setting properties क्रम the requested shared memory.
 *
 * @वापसs a poपूर्णांकer to 'struct tee_shm'
 */
काष्ठा tee_shm *tee_shm_रेजिस्टर(काष्ठा tee_context *ctx, अचिन्हित दीर्घ addr,
				 माप_प्रकार length, u32 flags);

/**
 * tee_shm_is_रेजिस्टरed() - Check अगर shared memory object in रेजिस्टरed in TEE
 * @shm:	Shared memory handle
 * @वापसs true अगर object is रेजिस्टरed in TEE
 */
अटल अंतरभूत bool tee_shm_is_रेजिस्टरed(काष्ठा tee_shm *shm)
अणु
	वापस shm && (shm->flags & TEE_SHM_REGISTER);
पूर्ण

/**
 * tee_shm_मुक्त() - Free shared memory
 * @shm:	Handle to shared memory to मुक्त
 */
व्योम tee_shm_मुक्त(काष्ठा tee_shm *shm);

/**
 * tee_shm_put() - Decrease reference count on a shared memory handle
 * @shm:	Shared memory handle
 */
व्योम tee_shm_put(काष्ठा tee_shm *shm);

/**
 * tee_shm_va2pa() - Get physical address of a भव address
 * @shm:	Shared memory handle
 * @va:		Virtual address to tranlsate
 * @pa:		Returned physical address
 * @वापसs 0 on success and < 0 on failure
 */
पूर्णांक tee_shm_va2pa(काष्ठा tee_shm *shm, व्योम *va, phys_addr_t *pa);

/**
 * tee_shm_pa2va() - Get भव address of a physical address
 * @shm:	Shared memory handle
 * @pa:		Physical address to tranlsate
 * @va:		Returned भव address
 * @वापसs 0 on success and < 0 on failure
 */
पूर्णांक tee_shm_pa2va(काष्ठा tee_shm *shm, phys_addr_t pa, व्योम **va);

/**
 * tee_shm_get_va() - Get भव address of a shared memory plus an offset
 * @shm:	Shared memory handle
 * @offs:	Offset from start of this shared memory
 * @वापसs भव address of the shared memory + offs अगर offs is within
 *	the bounds of this shared memory, अन्यथा an ERR_PTR
 */
व्योम *tee_shm_get_va(काष्ठा tee_shm *shm, माप_प्रकार offs);

/**
 * tee_shm_get_pa() - Get physical address of a shared memory plus an offset
 * @shm:	Shared memory handle
 * @offs:	Offset from start of this shared memory
 * @pa:		Physical address to वापस
 * @वापसs 0 अगर offs is within the bounds of this shared memory, अन्यथा an
 *	error code.
 */
पूर्णांक tee_shm_get_pa(काष्ठा tee_shm *shm, माप_प्रकार offs, phys_addr_t *pa);

/**
 * tee_shm_get_size() - Get size of shared memory buffer
 * @shm:	Shared memory handle
 * @वापसs size of shared memory
 */
अटल अंतरभूत माप_प्रकार tee_shm_get_size(काष्ठा tee_shm *shm)
अणु
	वापस shm->size;
पूर्ण

/**
 * tee_shm_get_pages() - Get list of pages that hold shared buffer
 * @shm:	Shared memory handle
 * @num_pages:	Number of pages will be stored there
 * @वापसs poपूर्णांकer to pages array
 */
अटल अंतरभूत काष्ठा page **tee_shm_get_pages(काष्ठा tee_shm *shm,
					      माप_प्रकार *num_pages)
अणु
	*num_pages = shm->num_pages;
	वापस shm->pages;
पूर्ण

/**
 * tee_shm_get_page_offset() - Get shared buffer offset from page start
 * @shm:	Shared memory handle
 * @वापसs page offset of shared buffer
 */
अटल अंतरभूत माप_प्रकार tee_shm_get_page_offset(काष्ठा tee_shm *shm)
अणु
	वापस shm->offset;
पूर्ण

/**
 * tee_shm_get_id() - Get id of a shared memory object
 * @shm:	Shared memory handle
 * @वापसs id
 */
अटल अंतरभूत पूर्णांक tee_shm_get_id(काष्ठा tee_shm *shm)
अणु
	वापस shm->id;
पूर्ण

/**
 * tee_shm_get_from_id() - Find shared memory object and increase reference
 * count
 * @ctx:	Context owning the shared memory
 * @id:		Id of shared memory object
 * @वापसs a poपूर्णांकer to 'struct tee_shm' on success or an ERR_PTR on failure
 */
काष्ठा tee_shm *tee_shm_get_from_id(काष्ठा tee_context *ctx, पूर्णांक id);

/**
 * tee_client_खोलो_context() - Open a TEE context
 * @start:	अगर not शून्य, जारी search after this context
 * @match:	function to check TEE device
 * @data:	data क्रम match function
 * @vers:	अगर not शून्य, version data of TEE device of the context वापसed
 *
 * This function करोes an operation similar to खोलो("/dev/teeX") in user space.
 * A वापसed context must be released with tee_client_बंद_context().
 *
 * Returns a TEE context of the first TEE device matched by the match()
 * callback or an ERR_PTR.
 */
काष्ठा tee_context *
tee_client_खोलो_context(काष्ठा tee_context *start,
			पूर्णांक (*match)(काष्ठा tee_ioctl_version_data *,
				     स्थिर व्योम *),
			स्थिर व्योम *data, काष्ठा tee_ioctl_version_data *vers);

/**
 * tee_client_बंद_context() - Close a TEE context
 * @ctx:	TEE context to बंद
 *
 * Note that all sessions previously खोलोed with this context will be
 * बंदd when this function is called.
 */
व्योम tee_client_बंद_context(काष्ठा tee_context *ctx);

/**
 * tee_client_get_version() - Query version of TEE
 * @ctx:	TEE context to TEE to query
 * @vers:	Poपूर्णांकer to version data
 */
व्योम tee_client_get_version(काष्ठा tee_context *ctx,
			    काष्ठा tee_ioctl_version_data *vers);

/**
 * tee_client_खोलो_session() - Open a session to a Trusted Application
 * @ctx:	TEE context
 * @arg:	Open session arguments, see description of
 *		काष्ठा tee_ioctl_खोलो_session_arg
 * @param:	Parameters passed to the Trusted Application
 *
 * Returns < 0 on error अन्यथा see @arg->ret क्रम result. If @arg->ret
 * is TEEC_SUCCESS the session identअगरier is available in @arg->session.
 */
पूर्णांक tee_client_खोलो_session(काष्ठा tee_context *ctx,
			    काष्ठा tee_ioctl_खोलो_session_arg *arg,
			    काष्ठा tee_param *param);

/**
 * tee_client_बंद_session() - Close a session to a Trusted Application
 * @ctx:	TEE Context
 * @session:	Session id
 *
 * Return < 0 on error अन्यथा 0, regardless the session will not be
 * valid after this function has वापसed.
 */
पूर्णांक tee_client_बंद_session(काष्ठा tee_context *ctx, u32 session);

/**
 * tee_client_invoke_func() - Invoke a function in a Trusted Application
 * @ctx:	TEE Context
 * @arg:	Invoke arguments, see description of
 *		काष्ठा tee_ioctl_invoke_arg
 * @param:	Parameters passed to the Trusted Application
 *
 * Returns < 0 on error अन्यथा see @arg->ret क्रम result.
 */
पूर्णांक tee_client_invoke_func(काष्ठा tee_context *ctx,
			   काष्ठा tee_ioctl_invoke_arg *arg,
			   काष्ठा tee_param *param);

/**
 * tee_client_cancel_req() - Request cancellation of the previous खोलो-session
 * or invoke-command operations in a Trusted Application
 * @ctx:       TEE Context
 * @arg:       Cancellation arguments, see description of
 *             काष्ठा tee_ioctl_cancel_arg
 *
 * Returns < 0 on error अन्यथा 0 अगर the cancellation was successfully requested.
 */
पूर्णांक tee_client_cancel_req(काष्ठा tee_context *ctx,
			  काष्ठा tee_ioctl_cancel_arg *arg);

अटल अंतरभूत bool tee_param_is_memref(काष्ठा tee_param *param)
अणु
	चयन (param->attr & TEE_IOCTL_PARAM_ATTR_TYPE_MASK) अणु
	हाल TEE_IOCTL_PARAM_ATTR_TYPE_MEMREF_INPUT:
	हाल TEE_IOCTL_PARAM_ATTR_TYPE_MEMREF_OUTPUT:
	हाल TEE_IOCTL_PARAM_ATTR_TYPE_MEMREF_INOUT:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

बाह्य काष्ठा bus_type tee_bus_type;

/**
 * काष्ठा tee_client_device - tee based device
 * @id:			device identअगरier
 * @dev:		device काष्ठाure
 */
काष्ठा tee_client_device अणु
	काष्ठा tee_client_device_id id;
	काष्ठा device dev;
पूर्ण;

#घोषणा to_tee_client_device(d) container_of(d, काष्ठा tee_client_device, dev)

/**
 * काष्ठा tee_client_driver - tee client driver
 * @id_table:		device id table supported by this driver
 * @driver:		driver काष्ठाure
 */
काष्ठा tee_client_driver अणु
	स्थिर काष्ठा tee_client_device_id *id_table;
	काष्ठा device_driver driver;
पूर्ण;

#घोषणा to_tee_client_driver(d) \
		container_of(d, काष्ठा tee_client_driver, driver)

#पूर्ण_अगर /*__TEE_DRV_H*/
