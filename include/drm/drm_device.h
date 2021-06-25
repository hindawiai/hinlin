<शैली गुरु>
#अगर_अघोषित _DRM_DEVICE_H_
#घोषणा _DRM_DEVICE_H_

#समावेश <linux/list.h>
#समावेश <linux/kref.h>
#समावेश <linux/mutex.h>
#समावेश <linux/idr.h>

#समावेश <drm/drm_hashtab.h>
#समावेश <drm/drm_mode_config.h>

काष्ठा drm_driver;
काष्ठा drm_minor;
काष्ठा drm_master;
काष्ठा drm_device_dma;
काष्ठा drm_vblank_crtc;
काष्ठा drm_sg_mem;
काष्ठा drm_local_map;
काष्ठा drm_vma_offset_manager;
काष्ठा drm_vram_mm;
काष्ठा drm_fb_helper;

काष्ठा inode;

काष्ठा pci_dev;
काष्ठा pci_controller;


/**
 * क्रमागत चयन_घातer_state - घातer state of drm device
 */

क्रमागत चयन_घातer_state अणु
	/** @DRM_SWITCH_POWER_ON: Power state is ON */
	DRM_SWITCH_POWER_ON = 0,

	/** @DRM_SWITCH_POWER_OFF: Power state is OFF */
	DRM_SWITCH_POWER_OFF = 1,

	/** @DRM_SWITCH_POWER_CHANGING: Power state is changing */
	DRM_SWITCH_POWER_CHANGING = 2,

	/** @DRM_SWITCH_POWER_DYNAMIC_OFF: Suspended */
	DRM_SWITCH_POWER_DYNAMIC_OFF = 3,
पूर्ण;

/**
 * काष्ठा drm_device - DRM device काष्ठाure
 *
 * This काष्ठाure represent a complete card that
 * may contain multiple heads.
 */
काष्ठा drm_device अणु
	/** @अगर_version: Highest पूर्णांकerface version set */
	पूर्णांक अगर_version;

	/** @ref: Object ref-count */
	काष्ठा kref ref;

	/** @dev: Device काष्ठाure of bus-device */
	काष्ठा device *dev;

	/**
	 * @managed:
	 *
	 * Managed resources linked to the lअगरeसमय of this &drm_device as
	 * tracked by @ref.
	 */
	काष्ठा अणु
		/** @managed.resources: managed resources list */
		काष्ठा list_head resources;
		/** @managed.final_kमुक्त: poपूर्णांकer क्रम final kमुक्त() call */
		व्योम *final_kमुक्त;
		/** @managed.lock: protects @managed.resources */
		spinlock_t lock;
	पूर्ण managed;

	/** @driver: DRM driver managing the device */
	स्थिर काष्ठा drm_driver *driver;

	/**
	 * @dev_निजी:
	 *
	 * DRM driver निजी data. This is deprecated and should be left set to
	 * शून्य.
	 *
	 * Instead of using this poपूर्णांकer it is recommended that drivers use
	 * devm_drm_dev_alloc() and embed काष्ठा &drm_device in their larger
	 * per-device काष्ठाure.
	 */
	व्योम *dev_निजी;

	/** @primary: Primary node */
	काष्ठा drm_minor *primary;

	/** @render: Render node */
	काष्ठा drm_minor *render;

	/**
	 * @रेजिस्टरed:
	 *
	 * Internally used by drm_dev_रेजिस्टर() and drm_connector_रेजिस्टर().
	 */
	bool रेजिस्टरed;

	/**
	 * @master:
	 *
	 * Currently active master क्रम this device.
	 * Protected by &master_mutex
	 */
	काष्ठा drm_master *master;

	/**
	 * @driver_features: per-device driver features
	 *
	 * Drivers can clear specअगरic flags here to disallow
	 * certain features on a per-device basis जबतक still
	 * sharing a single &काष्ठा drm_driver instance across
	 * all devices.
	 */
	u32 driver_features;

	/**
	 * @unplugged:
	 *
	 * Flag to tell अगर the device has been unplugged.
	 * See drm_dev_enter() and drm_dev_is_unplugged().
	 */
	bool unplugged;

	/** @anon_inode: inode क्रम निजी address-space */
	काष्ठा inode *anon_inode;

	/** @unique: Unique name of the device */
	अक्षर *unique;

	/**
	 * @काष्ठा_mutex:
	 *
	 * Lock क्रम others (not &drm_minor.master and &drm_file.is_master)
	 *
	 * WARNING:
	 * Only drivers annotated with DRIVER_LEGACY should be using this.
	 */
	काष्ठा mutex काष्ठा_mutex;

	/**
	 * @master_mutex:
	 *
	 * Lock क्रम &drm_minor.master and &drm_file.is_master
	 */
	काष्ठा mutex master_mutex;

	/**
	 * @खोलो_count:
	 *
	 * Usage counter क्रम outstanding files खोलो,
	 * रक्षित by drm_global_mutex
	 */
	atomic_t खोलो_count;

	/** @filelist_mutex: Protects @filelist. */
	काष्ठा mutex filelist_mutex;
	/**
	 * @filelist:
	 *
	 * List of userspace clients, linked through &drm_file.lhead.
	 */
	काष्ठा list_head filelist;

	/**
	 * @filelist_पूर्णांकernal:
	 *
	 * List of खोलो DRM files क्रम in-kernel clients.
	 * Protected by &filelist_mutex.
	 */
	काष्ठा list_head filelist_पूर्णांकernal;

	/**
	 * @clientlist_mutex:
	 *
	 * Protects &clientlist access.
	 */
	काष्ठा mutex clientlist_mutex;

	/**
	 * @clientlist:
	 *
	 * List of in-kernel clients. Protected by &clientlist_mutex.
	 */
	काष्ठा list_head clientlist;

	/**
	 * @irq_enabled:
	 *
	 * Indicates that पूर्णांकerrupt handling is enabled, specअगरically vblank
	 * handling. Drivers which करोn't use drm_irq_install() need to set this
	 * to true manually.
	 */
	bool irq_enabled;

	/**
	 * @irq: Used by the drm_irq_install() and drm_irq_unistall() helpers.
	 */
	पूर्णांक irq;

	/**
	 * @vblank_disable_immediate:
	 *
	 * If true, vblank पूर्णांकerrupt will be disabled immediately when the
	 * refcount drops to zero, as opposed to via the vblank disable
	 * समयr.
	 *
	 * This can be set to true it the hardware has a working vblank counter
	 * with high-precision बारtamping (otherwise there are races) and the
	 * driver uses drm_crtc_vblank_on() and drm_crtc_vblank_off()
	 * appropriately. See also @max_vblank_count and
	 * &drm_crtc_funcs.get_vblank_counter.
	 */
	bool vblank_disable_immediate;

	/**
	 * @vblank:
	 *
	 * Array of vblank tracking काष्ठाures, one per &काष्ठा drm_crtc. For
	 * historical reasons (vblank support predates kernel modesetting) this
	 * is मुक्त-standing and not part of &काष्ठा drm_crtc itself. It must be
	 * initialized explicitly by calling drm_vblank_init().
	 */
	काष्ठा drm_vblank_crtc *vblank;

	/**
	 * @vblank_समय_lock:
	 *
	 *  Protects vblank count and समय updates during vblank enable/disable
	 */
	spinlock_t vblank_समय_lock;
	/**
	 * @vbl_lock: Top-level vblank references lock, wraps the low-level
	 * @vblank_समय_lock.
	 */
	spinlock_t vbl_lock;

	/**
	 * @max_vblank_count:
	 *
	 * Maximum value of the vblank रेजिस्टरs. This value +1 will result in a
	 * wrap-around of the vblank रेजिस्टर. It is used by the vblank core to
	 * handle wrap-arounds.
	 *
	 * If set to zero the vblank core will try to guess the elapsed vblanks
	 * between बार when the vblank पूर्णांकerrupt is disabled through
	 * high-precision बारtamps. That approach is suffering from small
	 * races and imprecision over दीर्घer समय periods, hence exposing a
	 * hardware vblank counter is always recommended.
	 *
	 * This is the अटलally configured device wide maximum. The driver
	 * can instead choose to use a runसमय configurable per-crtc value
	 * &drm_vblank_crtc.max_vblank_count, in which हाल @max_vblank_count
	 * must be left at zero. See drm_crtc_set_max_vblank_count() on how
	 * to use the per-crtc value.
	 *
	 * If non-zero, &drm_crtc_funcs.get_vblank_counter must be set.
	 */
	u32 max_vblank_count;

	/** @vblank_event_list: List of vblank events */
	काष्ठा list_head vblank_event_list;

	/**
	 * @event_lock:
	 *
	 * Protects @vblank_event_list and event delivery in
	 * general. See drm_send_event() and drm_send_event_locked().
	 */
	spinlock_t event_lock;

	/** @agp: AGP data */
	काष्ठा drm_agp_head *agp;

	/** @pdev: PCI device काष्ठाure */
	काष्ठा pci_dev *pdev;

	/** @num_crtcs: Number of CRTCs on this device */
	अचिन्हित पूर्णांक num_crtcs;

	/** @mode_config: Current mode config */
	काष्ठा drm_mode_config mode_config;

	/** @object_name_lock: GEM inक्रमmation */
	काष्ठा mutex object_name_lock;

	/** @object_name_idr: GEM inक्रमmation */
	काष्ठा idr object_name_idr;

	/** @vma_offset_manager: GEM inक्रमmation */
	काष्ठा drm_vma_offset_manager *vma_offset_manager;

	/** @vram_mm: VRAM MM memory manager */
	काष्ठा drm_vram_mm *vram_mm;

	/**
	 * @चयन_घातer_state:
	 *
	 * Power state of the client.
	 * Used by drivers supporting the चयनeroo driver.
	 * The state is मुख्यtained in the
	 * &vga_चयनeroo_client_ops.set_gpu_state callback
	 */
	क्रमागत चयन_घातer_state चयन_घातer_state;

	/**
	 * @fb_helper:
	 *
	 * Poपूर्णांकer to the fbdev emulation काष्ठाure.
	 * Set by drm_fb_helper_init() and cleared by drm_fb_helper_fini().
	 */
	काष्ठा drm_fb_helper *fb_helper;

	/* Everything below here is क्रम legacy driver, never use! */
	/* निजी: */
#अगर IS_ENABLED(CONFIG_DRM_LEGACY)
	/* List of devices per driver क्रम stealth attach cleanup */
	काष्ठा list_head legacy_dev_list;

#अगर_घोषित __alpha__
	/** @hose: PCI hose, only used on ALPHA platक्रमms. */
	काष्ठा pci_controller *hose;
#पूर्ण_अगर

	/* Context handle management - linked list of context handles */
	काष्ठा list_head ctxlist;

	/* Context handle management - mutex क्रम &ctxlist */
	काष्ठा mutex ctxlist_mutex;

	/* Context handle management */
	काष्ठा idr ctx_idr;

	/* Memory management - linked list of regions */
	काष्ठा list_head maplist;

	/* Memory management - user token hash table क्रम maps */
	काष्ठा drm_खोलो_hash map_hash;

	/* Context handle management - list of vmas (क्रम debugging) */
	काष्ठा list_head vmalist;

	/* Optional poपूर्णांकer क्रम DMA support */
	काष्ठा drm_device_dma *dma;

	/* Context swapping flag */
	__अस्थिर__ दीर्घ context_flag;

	/* Last current context */
	पूर्णांक last_context;

	/* Lock क्रम &buf_use and a few other things. */
	spinlock_t buf_lock;

	/* Usage counter क्रम buffers in use -- cannot alloc */
	पूर्णांक buf_use;

	/* Buffer allocation in progress */
	atomic_t buf_alloc;

	काष्ठा अणु
		पूर्णांक context;
		काष्ठा drm_hw_lock *lock;
	पूर्ण sigdata;

	काष्ठा drm_local_map *agp_buffer_map;
	अचिन्हित पूर्णांक agp_buffer_token;

	/* Scatter gather memory */
	काष्ठा drm_sg_mem *sg;
#पूर्ण_अगर
पूर्ण;

#पूर्ण_अगर
