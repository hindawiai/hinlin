<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2016-2018, The Linux Foundation. All rights reserved.
 * Copyright (C) 2013 Red Hat
 * Author: Rob Clark <robdclark@gmail.com>
 */

#अगर_अघोषित __MSM_DRV_H__
#घोषणा __MSM_DRV_H__

#समावेश <linux/kernel.h>
#समावेश <linux/clk.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/module.h>
#समावेश <linux/component.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/slab.h>
#समावेश <linux/list.h>
#समावेश <linux/iommu.h>
#समावेश <linux/types.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/of_device.h>
#समावेश <linux/sizes.h>
#समावेश <linux/kthपढ़ो.h>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_plane_helper.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/msm_drm.h>
#समावेश <drm/drm_gem.h>

काष्ठा msm_kms;
काष्ठा msm_gpu;
काष्ठा msm_mmu;
काष्ठा msm_mdss;
काष्ठा msm_rd_state;
काष्ठा msm_perf_state;
काष्ठा msm_gem_submit;
काष्ठा msm_fence_context;
काष्ठा msm_gem_address_space;
काष्ठा msm_gem_vma;

#घोषणा MAX_CRTCS      8
#घोषणा MAX_PLANES     20
#घोषणा MAX_ENCODERS   8
#घोषणा MAX_BRIDGES    8
#घोषणा MAX_CONNECTORS 8

#घोषणा FRAC_16_16(mult, भाग)    (((mult) << 16) / (भाग))

काष्ठा msm_file_निजी अणु
	rwlock_t queuelock;
	काष्ठा list_head submitqueues;
	पूर्णांक queueid;
	काष्ठा msm_gem_address_space *aspace;
	काष्ठा kref ref;
पूर्ण;

क्रमागत msm_mdp_plane_property अणु
	PLANE_PROP_ZPOS,
	PLANE_PROP_ALPHA,
	PLANE_PROP_PREMULTIPLIED,
	PLANE_PROP_MAX_NUM
पूर्ण;

#घोषणा MSM_GPU_MAX_RINGS 4
#घोषणा MAX_H_TILES_PER_DISPLAY 2

/**
 * क्रमागत msm_display_caps - features/capabilities supported by displays
 * @MSM_DISPLAY_CAP_VID_MODE:           Video or "active" mode supported
 * @MSM_DISPLAY_CAP_CMD_MODE:           Command mode supported
 * @MSM_DISPLAY_CAP_HOT_PLUG:           Hot plug detection supported
 * @MSM_DISPLAY_CAP_EDID:               EDID supported
 */
क्रमागत msm_display_caps अणु
	MSM_DISPLAY_CAP_VID_MODE	= BIT(0),
	MSM_DISPLAY_CAP_CMD_MODE	= BIT(1),
	MSM_DISPLAY_CAP_HOT_PLUG	= BIT(2),
	MSM_DISPLAY_CAP_EDID		= BIT(3),
पूर्ण;

/**
 * क्रमागत msm_event_रुको - type of HW events to रुको क्रम
 * @MSM_ENC_COMMIT_DONE - रुको क्रम the driver to flush the रेजिस्टरs to HW
 * @MSM_ENC_TX_COMPLETE - रुको क्रम the HW to transfer the frame to panel
 * @MSM_ENC_VBLANK - रुको क्रम the HW VBLANK event (क्रम driver-पूर्णांकernal रुकोers)
 */
क्रमागत msm_event_रुको अणु
	MSM_ENC_COMMIT_DONE = 0,
	MSM_ENC_TX_COMPLETE,
	MSM_ENC_VBLANK,
पूर्ण;

/**
 * काष्ठा msm_display_topology - defines a display topology pipeline
 * @num_lm:       number of layer mixers used
 * @num_enc:      number of compression encoder blocks used
 * @num_पूर्णांकf:     number of पूर्णांकerfaces the panel is mounted on
 */
काष्ठा msm_display_topology अणु
	u32 num_lm;
	u32 num_enc;
	u32 num_पूर्णांकf;
	u32 num_dspp;
पूर्ण;

/**
 * काष्ठा msm_display_info - defines display properties
 * @पूर्णांकf_type:          DRM_MODE_ENCODER_ type
 * @capabilities:       Biपंचांगask of display flags
 * @num_of_h_tiles:     Number of horizontal tiles in हाल of split पूर्णांकerface
 * @h_tile_instance:    Controller instance used per tile. Number of elements is
 *                      based on num_of_h_tiles
 * @is_te_using_watchकरोg_समयr:  Boolean to indicate watchकरोg TE is
 *				 used instead of panel TE in cmd mode panels
 */
काष्ठा msm_display_info अणु
	पूर्णांक पूर्णांकf_type;
	uपूर्णांक32_t capabilities;
	uपूर्णांक32_t num_of_h_tiles;
	uपूर्णांक32_t h_tile_instance[MAX_H_TILES_PER_DISPLAY];
	bool is_te_using_watchकरोg_समयr;
पूर्ण;

/* Commit/Event thपढ़ो specअगरic काष्ठाure */
काष्ठा msm_drm_thपढ़ो अणु
	काष्ठा drm_device *dev;
	अचिन्हित पूर्णांक crtc_id;
	काष्ठा kthपढ़ो_worker *worker;
पूर्ण;

काष्ठा msm_drm_निजी अणु

	काष्ठा drm_device *dev;

	काष्ठा msm_kms *kms;

	/* subordinate devices, अगर present: */
	काष्ठा platक्रमm_device *gpu_pdev;

	/* top level MDSS wrapper device (क्रम MDP5/DPU only) */
	काष्ठा msm_mdss *mdss;

	/* possibly this should be in the kms component, but it is
	 * shared by both mdp4 and mdp5..
	 */
	काष्ठा hdmi *hdmi;

	/* eDP is क्रम mdp5 only, but kms has not been created
	 * when edp_bind() and edp_init() are called. Here is the only
	 * place to keep the edp instance.
	 */
	काष्ठा msm_edp *edp;

	/* DSI is shared by mdp4 and mdp5 */
	काष्ठा msm_dsi *dsi[2];

	काष्ठा msm_dp *dp;

	/* when we have more than one 'msm_gpu' these need to be an array: */
	काष्ठा msm_gpu *gpu;
	काष्ठा msm_file_निजी *lastctx;
	/* gpu is only set on खोलो(), but we need this info earlier */
	bool is_a2xx;

	काष्ठा drm_fb_helper *fbdev;

	काष्ठा msm_rd_state *rd;       /* debugfs to dump all submits */
	काष्ठा msm_rd_state *hangrd;   /* debugfs to dump hanging submits */
	काष्ठा msm_perf_state *perf;

	/**
	 * List of all GEM objects (मुख्यly क्रम debugfs, रक्षित by obj_lock
	 * (acquire beक्रमe per GEM object lock)
	 */
	काष्ठा list_head objects;
	काष्ठा mutex obj_lock;

	/**
	 * LRUs of inactive GEM objects.  Every bo is either in one of the
	 * inactive lists (depending on whether or not it is shrinkable) or
	 * gpu->active_list (क्रम the gpu it is active on[1]), or transiently
	 * on a temporary list as the shrinker is running.
	 *
	 * Note that inactive_willneed also contains pinned and vmap'd bos,
	 * but the number of pinned-but-not-active objects is small (scanout
	 * buffers, ringbuffer, etc).
	 *
	 * These lists are रक्षित by mm_lock (which should be acquired
	 * beक्रमe per GEM object lock).  One should *not* hold mm_lock in
	 * get_pages()/vmap()/etc paths, as they can trigger the shrinker.
	 *
	 * [1] अगर someone ever added support क्रम the old 2d cores, there could be
	 *     more than one gpu object
	 */
	काष्ठा list_head inactive_willneed;  /* inactive + potentially unpin/evictable */
	काष्ठा list_head inactive_करोntneed;  /* inactive + shrinkable */
	काष्ठा list_head inactive_unpinned;  /* inactive + purged or unpinned */
	दीर्घ shrinkable_count;               /* ग_लिखो access under mm_lock */
	दीर्घ evictable_count;                /* ग_लिखो access under mm_lock */
	काष्ठा mutex mm_lock;

	काष्ठा workqueue_काष्ठा *wq;

	अचिन्हित पूर्णांक num_planes;
	काष्ठा drm_plane *planes[MAX_PLANES];

	अचिन्हित पूर्णांक num_crtcs;
	काष्ठा drm_crtc *crtcs[MAX_CRTCS];

	काष्ठा msm_drm_thपढ़ो event_thपढ़ो[MAX_CRTCS];

	अचिन्हित पूर्णांक num_encoders;
	काष्ठा drm_encoder *encoders[MAX_ENCODERS];

	अचिन्हित पूर्णांक num_bridges;
	काष्ठा drm_bridge *bridges[MAX_BRIDGES];

	अचिन्हित पूर्णांक num_connectors;
	काष्ठा drm_connector *connectors[MAX_CONNECTORS];

	/* Properties */
	काष्ठा drm_property *plane_property[PLANE_PROP_MAX_NUM];

	/* VRAM carveout, used when no IOMMU: */
	काष्ठा अणु
		अचिन्हित दीर्घ size;
		dma_addr_t paddr;
		/* NOTE: mm managed at the page level, size is in # of pages
		 * and position mm_node->start is in # of pages:
		 */
		काष्ठा drm_mm mm;
		spinlock_t lock; /* Protects drm_mm node allocation/removal */
	पूर्ण vram;

	काष्ठा notअगरier_block vmap_notअगरier;
	काष्ठा shrinker shrinker;

	काष्ठा drm_atomic_state *pm_state;
पूर्ण;

काष्ठा msm_क्रमmat अणु
	uपूर्णांक32_t pixel_क्रमmat;
पूर्ण;

काष्ठा msm_pending_समयr;

पूर्णांक msm_atomic_prepare_fb(काष्ठा drm_plane *plane,
			  काष्ठा drm_plane_state *new_state);
पूर्णांक msm_atomic_init_pending_समयr(काष्ठा msm_pending_समयr *समयr,
		काष्ठा msm_kms *kms, पूर्णांक crtc_idx);
व्योम msm_atomic_destroy_pending_समयr(काष्ठा msm_pending_समयr *समयr);
व्योम msm_atomic_commit_tail(काष्ठा drm_atomic_state *state);
काष्ठा drm_atomic_state *msm_atomic_state_alloc(काष्ठा drm_device *dev);
व्योम msm_atomic_state_clear(काष्ठा drm_atomic_state *state);
व्योम msm_atomic_state_मुक्त(काष्ठा drm_atomic_state *state);

पूर्णांक msm_crtc_enable_vblank(काष्ठा drm_crtc *crtc);
व्योम msm_crtc_disable_vblank(काष्ठा drm_crtc *crtc);

पूर्णांक msm_gem_init_vma(काष्ठा msm_gem_address_space *aspace,
		काष्ठा msm_gem_vma *vma, पूर्णांक npages,
		u64 range_start, u64 range_end);
व्योम msm_gem_purge_vma(काष्ठा msm_gem_address_space *aspace,
		काष्ठा msm_gem_vma *vma);
व्योम msm_gem_unmap_vma(काष्ठा msm_gem_address_space *aspace,
		काष्ठा msm_gem_vma *vma);
पूर्णांक msm_gem_map_vma(काष्ठा msm_gem_address_space *aspace,
		काष्ठा msm_gem_vma *vma, पूर्णांक prot,
		काष्ठा sg_table *sgt, पूर्णांक npages);
व्योम msm_gem_बंद_vma(काष्ठा msm_gem_address_space *aspace,
		काष्ठा msm_gem_vma *vma);


काष्ठा msm_gem_address_space *
msm_gem_address_space_get(काष्ठा msm_gem_address_space *aspace);

व्योम msm_gem_address_space_put(काष्ठा msm_gem_address_space *aspace);

काष्ठा msm_gem_address_space *
msm_gem_address_space_create(काष्ठा msm_mmu *mmu, स्थिर अक्षर *name,
		u64 बहु_शुरू, u64 size);

पूर्णांक msm_रेजिस्टर_mmu(काष्ठा drm_device *dev, काष्ठा msm_mmu *mmu);
व्योम msm_unरेजिस्टर_mmu(काष्ठा drm_device *dev, काष्ठा msm_mmu *mmu);

bool msm_use_mmu(काष्ठा drm_device *dev);

पूर्णांक msm_ioctl_gem_submit(काष्ठा drm_device *dev, व्योम *data,
		काष्ठा drm_file *file);

व्योम msm_gem_shrinker_init(काष्ठा drm_device *dev);
व्योम msm_gem_shrinker_cleanup(काष्ठा drm_device *dev);

काष्ठा sg_table *msm_gem_prime_get_sg_table(काष्ठा drm_gem_object *obj);
पूर्णांक msm_gem_prime_vmap(काष्ठा drm_gem_object *obj, काष्ठा dma_buf_map *map);
व्योम msm_gem_prime_vunmap(काष्ठा drm_gem_object *obj, काष्ठा dma_buf_map *map);
पूर्णांक msm_gem_prime_mmap(काष्ठा drm_gem_object *obj, काष्ठा vm_area_काष्ठा *vma);
काष्ठा drm_gem_object *msm_gem_prime_import_sg_table(काष्ठा drm_device *dev,
		काष्ठा dma_buf_attachment *attach, काष्ठा sg_table *sg);
पूर्णांक msm_gem_prime_pin(काष्ठा drm_gem_object *obj);
व्योम msm_gem_prime_unpin(काष्ठा drm_gem_object *obj);

पूर्णांक msm_framebuffer_prepare(काष्ठा drm_framebuffer *fb,
		काष्ठा msm_gem_address_space *aspace);
व्योम msm_framebuffer_cleanup(काष्ठा drm_framebuffer *fb,
		काष्ठा msm_gem_address_space *aspace);
uपूर्णांक32_t msm_framebuffer_iova(काष्ठा drm_framebuffer *fb,
		काष्ठा msm_gem_address_space *aspace, पूर्णांक plane);
काष्ठा drm_gem_object *msm_framebuffer_bo(काष्ठा drm_framebuffer *fb, पूर्णांक plane);
स्थिर काष्ठा msm_क्रमmat *msm_framebuffer_क्रमmat(काष्ठा drm_framebuffer *fb);
काष्ठा drm_framebuffer *msm_framebuffer_create(काष्ठा drm_device *dev,
		काष्ठा drm_file *file, स्थिर काष्ठा drm_mode_fb_cmd2 *mode_cmd);
काष्ठा drm_framebuffer * msm_alloc_stolen_fb(काष्ठा drm_device *dev,
		पूर्णांक w, पूर्णांक h, पूर्णांक p, uपूर्णांक32_t क्रमmat);

काष्ठा drm_fb_helper *msm_fbdev_init(काष्ठा drm_device *dev);
व्योम msm_fbdev_मुक्त(काष्ठा drm_device *dev);

काष्ठा hdmi;
पूर्णांक msm_hdmi_modeset_init(काष्ठा hdmi *hdmi, काष्ठा drm_device *dev,
		काष्ठा drm_encoder *encoder);
व्योम __init msm_hdmi_रेजिस्टर(व्योम);
व्योम __निकास msm_hdmi_unरेजिस्टर(व्योम);

काष्ठा msm_edp;
व्योम __init msm_edp_रेजिस्टर(व्योम);
व्योम __निकास msm_edp_unरेजिस्टर(व्योम);
पूर्णांक msm_edp_modeset_init(काष्ठा msm_edp *edp, काष्ठा drm_device *dev,
		काष्ठा drm_encoder *encoder);

काष्ठा msm_dsi;
#अगर_घोषित CONFIG_DRM_MSM_DSI
व्योम __init msm_dsi_रेजिस्टर(व्योम);
व्योम __निकास msm_dsi_unरेजिस्टर(व्योम);
पूर्णांक msm_dsi_modeset_init(काष्ठा msm_dsi *msm_dsi, काष्ठा drm_device *dev,
			 काष्ठा drm_encoder *encoder);
#अन्यथा
अटल अंतरभूत व्योम __init msm_dsi_रेजिस्टर(व्योम)
अणु
पूर्ण
अटल अंतरभूत व्योम __निकास msm_dsi_unरेजिस्टर(व्योम)
अणु
पूर्ण
अटल अंतरभूत पूर्णांक msm_dsi_modeset_init(काष्ठा msm_dsi *msm_dsi,
				       काष्ठा drm_device *dev,
				       काष्ठा drm_encoder *encoder)
अणु
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_DRM_MSM_DP
पूर्णांक __init msm_dp_रेजिस्टर(व्योम);
व्योम __निकास msm_dp_unरेजिस्टर(व्योम);
पूर्णांक msm_dp_modeset_init(काष्ठा msm_dp *dp_display, काष्ठा drm_device *dev,
			 काष्ठा drm_encoder *encoder);
पूर्णांक msm_dp_display_enable(काष्ठा msm_dp *dp, काष्ठा drm_encoder *encoder);
पूर्णांक msm_dp_display_disable(काष्ठा msm_dp *dp, काष्ठा drm_encoder *encoder);
पूर्णांक msm_dp_display_pre_disable(काष्ठा msm_dp *dp, काष्ठा drm_encoder *encoder);
व्योम msm_dp_display_mode_set(काष्ठा msm_dp *dp, काष्ठा drm_encoder *encoder,
				काष्ठा drm_display_mode *mode,
				काष्ठा drm_display_mode *adjusted_mode);
व्योम msm_dp_irq_postinstall(काष्ठा msm_dp *dp_display);

व्योम msm_dp_debugfs_init(काष्ठा msm_dp *dp_display, काष्ठा drm_minor *minor);

#अन्यथा
अटल अंतरभूत पूर्णांक __init msm_dp_रेजिस्टर(व्योम)
अणु
	वापस -EINVAL;
पूर्ण
अटल अंतरभूत व्योम __निकास msm_dp_unरेजिस्टर(व्योम)
अणु
पूर्ण
अटल अंतरभूत पूर्णांक msm_dp_modeset_init(काष्ठा msm_dp *dp_display,
				       काष्ठा drm_device *dev,
				       काष्ठा drm_encoder *encoder)
अणु
	वापस -EINVAL;
पूर्ण
अटल अंतरभूत पूर्णांक msm_dp_display_enable(काष्ठा msm_dp *dp,
					काष्ठा drm_encoder *encoder)
अणु
	वापस -EINVAL;
पूर्ण
अटल अंतरभूत पूर्णांक msm_dp_display_disable(काष्ठा msm_dp *dp,
					काष्ठा drm_encoder *encoder)
अणु
	वापस -EINVAL;
पूर्ण
अटल अंतरभूत पूर्णांक msm_dp_display_pre_disable(काष्ठा msm_dp *dp,
					काष्ठा drm_encoder *encoder)
अणु
	वापस -EINVAL;
पूर्ण
अटल अंतरभूत व्योम msm_dp_display_mode_set(काष्ठा msm_dp *dp,
				काष्ठा drm_encoder *encoder,
				काष्ठा drm_display_mode *mode,
				काष्ठा drm_display_mode *adjusted_mode)
अणु
पूर्ण

अटल अंतरभूत व्योम msm_dp_irq_postinstall(काष्ठा msm_dp *dp_display)
अणु
पूर्ण

अटल अंतरभूत व्योम msm_dp_debugfs_init(काष्ठा msm_dp *dp_display,
		काष्ठा drm_minor *minor)
अणु
पूर्ण

#पूर्ण_अगर

व्योम __init msm_mdp_रेजिस्टर(व्योम);
व्योम __निकास msm_mdp_unरेजिस्टर(व्योम);
व्योम __init msm_dpu_रेजिस्टर(व्योम);
व्योम __निकास msm_dpu_unरेजिस्टर(व्योम);

#अगर_घोषित CONFIG_DEBUG_FS
व्योम msm_framebuffer_describe(काष्ठा drm_framebuffer *fb, काष्ठा seq_file *m);
पूर्णांक msm_debugfs_late_init(काष्ठा drm_device *dev);
पूर्णांक msm_rd_debugfs_init(काष्ठा drm_minor *minor);
व्योम msm_rd_debugfs_cleanup(काष्ठा msm_drm_निजी *priv);
__म_लिखो(3, 4)
व्योम msm_rd_dump_submit(काष्ठा msm_rd_state *rd, काष्ठा msm_gem_submit *submit,
		स्थिर अक्षर *fmt, ...);
पूर्णांक msm_perf_debugfs_init(काष्ठा drm_minor *minor);
व्योम msm_perf_debugfs_cleanup(काष्ठा msm_drm_निजी *priv);
#अन्यथा
अटल अंतरभूत पूर्णांक msm_debugfs_late_init(काष्ठा drm_device *dev) अणु वापस 0; पूर्ण
__म_लिखो(3, 4)
अटल अंतरभूत व्योम msm_rd_dump_submit(काष्ठा msm_rd_state *rd,
			काष्ठा msm_gem_submit *submit,
			स्थिर अक्षर *fmt, ...) अणुपूर्ण
अटल अंतरभूत व्योम msm_rd_debugfs_cleanup(काष्ठा msm_drm_निजी *priv) अणुपूर्ण
अटल अंतरभूत व्योम msm_perf_debugfs_cleanup(काष्ठा msm_drm_निजी *priv) अणुपूर्ण
#पूर्ण_अगर

काष्ठा clk *msm_clk_get(काष्ठा platक्रमm_device *pdev, स्थिर अक्षर *name);

काष्ठा clk *msm_clk_bulk_get_घड़ी(काष्ठा clk_bulk_data *bulk, पूर्णांक count,
	स्थिर अक्षर *name);
व्योम __iomem *msm_ioremap(काष्ठा platक्रमm_device *pdev, स्थिर अक्षर *name,
		स्थिर अक्षर *dbgname);
व्योम __iomem *msm_ioremap_quiet(काष्ठा platक्रमm_device *pdev, स्थिर अक्षर *name,
		स्थिर अक्षर *dbgname);
व्योम msm_ग_लिखोl(u32 data, व्योम __iomem *addr);
u32 msm_पढ़ोl(स्थिर व्योम __iomem *addr);
व्योम msm_rmw(व्योम __iomem *addr, u32 mask, u32 or);

काष्ठा msm_gpu_submitqueue;
पूर्णांक msm_submitqueue_init(काष्ठा drm_device *drm, काष्ठा msm_file_निजी *ctx);
काष्ठा msm_gpu_submitqueue *msm_submitqueue_get(काष्ठा msm_file_निजी *ctx,
		u32 id);
पूर्णांक msm_submitqueue_create(काष्ठा drm_device *drm,
		काष्ठा msm_file_निजी *ctx,
		u32 prio, u32 flags, u32 *id);
पूर्णांक msm_submitqueue_query(काष्ठा drm_device *drm, काष्ठा msm_file_निजी *ctx,
		काष्ठा drm_msm_submitqueue_query *args);
पूर्णांक msm_submitqueue_हटाओ(काष्ठा msm_file_निजी *ctx, u32 id);
व्योम msm_submitqueue_बंद(काष्ठा msm_file_निजी *ctx);

व्योम msm_submitqueue_destroy(काष्ठा kref *kref);

अटल अंतरभूत व्योम __msm_file_निजी_destroy(काष्ठा kref *kref)
अणु
	काष्ठा msm_file_निजी *ctx = container_of(kref,
		काष्ठा msm_file_निजी, ref);

	msm_gem_address_space_put(ctx->aspace);
	kमुक्त(ctx);
पूर्ण

अटल अंतरभूत व्योम msm_file_निजी_put(काष्ठा msm_file_निजी *ctx)
अणु
	kref_put(&ctx->ref, __msm_file_निजी_destroy);
पूर्ण

अटल अंतरभूत काष्ठा msm_file_निजी *msm_file_निजी_get(
	काष्ठा msm_file_निजी *ctx)
अणु
	kref_get(&ctx->ref);
	वापस ctx;
पूर्ण

#घोषणा DBG(fmt, ...) DRM_DEBUG_DRIVER(fmt"\n", ##__VA_ARGS__)
#घोषणा VERB(fmt, ...) अगर (0) DRM_DEBUG_DRIVER(fmt"\n", ##__VA_ARGS__)

अटल अंतरभूत पूर्णांक align_pitch(पूर्णांक width, पूर्णांक bpp)
अणु
	पूर्णांक bytespp = (bpp + 7) / 8;
	/* adreno needs pitch aligned to 32 pixels: */
	वापस bytespp * ALIGN(width, 32);
पूर्ण

/* क्रम the generated headers: */
#घोषणा INVALID_IDX(idx) (अणुBUG(); 0;पूर्ण)
#घोषणा fui(x)                (अणुBUG(); 0;पूर्ण)
#घोषणा util_भग्न_to_half(x) (अणुBUG(); 0;पूर्ण)


#घोषणा FIELD(val, name) (((val) & name ## __MASK) >> name ## __SHIFT)

/* क्रम conditionally setting boolean flag(s): */
#घोषणा COND(bool, val) ((bool) ? (val) : 0)

अटल अंतरभूत अचिन्हित दीर्घ समयout_to_jअगरfies(स्थिर kसमय_प्रकार *समयout)
अणु
	kसमय_प्रकार now = kसमय_get();
	अचिन्हित दीर्घ reमुख्यing_jअगरfies;

	अगर (kसमय_compare(*समयout, now) < 0) अणु
		reमुख्यing_jअगरfies = 0;
	पूर्ण अन्यथा अणु
		kसमय_प्रकार rem = kसमय_sub(*समयout, now);
		reमुख्यing_jअगरfies = kसमय_भागns(rem, NSEC_PER_SEC / HZ);
	पूर्ण

	वापस reमुख्यing_jअगरfies;
पूर्ण

#पूर्ण_अगर /* __MSM_DRV_H__ */
