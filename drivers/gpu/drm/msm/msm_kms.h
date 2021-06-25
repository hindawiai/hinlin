<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2016-2018, The Linux Foundation. All rights reserved.
 * Copyright (C) 2013 Red Hat
 * Author: Rob Clark <robdclark@gmail.com>
 */

#अगर_अघोषित __MSM_KMS_H__
#घोषणा __MSM_KMS_H__

#समावेश <linux/clk.h>
#समावेश <linux/regulator/consumer.h>

#समावेश "msm_drv.h"

#घोषणा MAX_PLANE	4

/* As there are dअगरferent display controller blocks depending on the
 * snapdragon version, the kms support is split out and the appropriate
 * implementation is loaded at runसमय.  The kms module is responsible
 * क्रम स्थिरructing the appropriate planes/crtcs/encoders/connectors.
 */
काष्ठा msm_kms_funcs अणु
	/* hw initialization: */
	पूर्णांक (*hw_init)(काष्ठा msm_kms *kms);
	/* irq handling: */
	व्योम (*irq_preinstall)(काष्ठा msm_kms *kms);
	पूर्णांक (*irq_postinstall)(काष्ठा msm_kms *kms);
	व्योम (*irq_uninstall)(काष्ठा msm_kms *kms);
	irqवापस_t (*irq)(काष्ठा msm_kms *kms);
	पूर्णांक (*enable_vblank)(काष्ठा msm_kms *kms, काष्ठा drm_crtc *crtc);
	व्योम (*disable_vblank)(काष्ठा msm_kms *kms, काष्ठा drm_crtc *crtc);

	/*
	 * Atomic commit handling:
	 *
	 * Note that in the हाल of async commits, the funcs which take
	 * a crtc_mask (ie. ->flush_commit(), and ->complete_commit())
	 * might not be evenly balanced with ->prepare_commit(), however
	 * each crtc that effected by a ->prepare_commit() (potentially
	 * multiple बार) will eventually (at end of vsync period) be
	 * flushed and completed.
	 *
	 * This has some implications about tracking of cleanup state,
	 * क्रम example SMP blocks to release after commit completes.  Ie.
	 * cleanup state should be also duplicated in the various
	 * duplicate_state() methods, as the current cleanup state at
	 * ->complete_commit() समय may have accumulated cleanup work
	 * from multiple commits.
	 */

	/**
	 * Enable/disable घातer/clks needed क्रम hw access करोne in other
	 * commit related methods.
	 *
	 * If mdp4 is migrated to runpm, we could probably drop these
	 * and use runpm directly.
	 */
	व्योम (*enable_commit)(काष्ठा msm_kms *kms);
	व्योम (*disable_commit)(काष्ठा msm_kms *kms);

	/**
	 * If the kms backend supports async commit, it should implement
	 * this method to वापस the समय of the next vsync.  This is
	 * used to determine a समय slightly beक्रमe vsync, क्रम the async
	 * commit समयr to run and complete an async commit.
	 */
	kसमय_प्रकार (*vsync_समय)(काष्ठा msm_kms *kms, काष्ठा drm_crtc *crtc);

	/**
	 * Prepare क्रम atomic commit.  This is called after any previous
	 * (async or otherwise) commit has completed.
	 */
	व्योम (*prepare_commit)(काष्ठा msm_kms *kms, काष्ठा drm_atomic_state *state);

	/**
	 * Flush an atomic commit.  This is called after the hardware
	 * updates have alपढ़ोy been pushed करोwn to effected planes/
	 * crtcs/encoders/connectors.
	 */
	व्योम (*flush_commit)(काष्ठा msm_kms *kms, अचिन्हित crtc_mask);

	/**
	 * Wait क्रम any in-progress flush to complete on the specअगरied
	 * crtcs.  This should not block अगर there is no in-progress
	 * commit (ie. करोn't just रुको क्रम a vblank), as it will also
	 * be called beक्रमe ->prepare_commit() to ensure any potential
	 * "async" commit has completed.
	 */
	व्योम (*रुको_flush)(काष्ठा msm_kms *kms, अचिन्हित crtc_mask);

	/**
	 * Clean up after commit is completed.  This is called after
	 * ->रुको_flush(), to give the backend a chance to करो any
	 * post-commit cleanup.
	 */
	व्योम (*complete_commit)(काष्ठा msm_kms *kms, अचिन्हित crtc_mask);

	/*
	 * Format handling:
	 */

	/* get msm_क्रमmat w/ optional क्रमmat modअगरiers from drm_mode_fb_cmd2 */
	स्थिर काष्ठा msm_क्रमmat *(*get_क्रमmat)(काष्ठा msm_kms *kms,
					स्थिर uपूर्णांक32_t क्रमmat,
					स्थिर uपूर्णांक64_t modअगरiers);
	/* करो क्रमmat checking on क्रमmat modअगरied through fb_cmd2 modअगरiers */
	पूर्णांक (*check_modअगरied_क्रमmat)(स्थिर काष्ठा msm_kms *kms,
			स्थिर काष्ठा msm_क्रमmat *msm_fmt,
			स्थिर काष्ठा drm_mode_fb_cmd2 *cmd,
			काष्ठा drm_gem_object **bos);

	/* misc: */
	दीर्घ (*round_pixclk)(काष्ठा msm_kms *kms, अचिन्हित दीर्घ rate,
			काष्ठा drm_encoder *encoder);
	पूर्णांक (*set_split_display)(काष्ठा msm_kms *kms,
			काष्ठा drm_encoder *encoder,
			काष्ठा drm_encoder *slave_encoder,
			bool is_cmd_mode);
	व्योम (*set_encoder_mode)(काष्ठा msm_kms *kms,
				 काष्ठा drm_encoder *encoder,
				 bool cmd_mode);
	/* cleanup: */
	व्योम (*destroy)(काष्ठा msm_kms *kms);
#अगर_घोषित CONFIG_DEBUG_FS
	/* debugfs: */
	पूर्णांक (*debugfs_init)(काष्ठा msm_kms *kms, काष्ठा drm_minor *minor);
#पूर्ण_अगर
पूर्ण;

काष्ठा msm_kms;

/*
 * A per-crtc समयr क्रम pending async atomic flushes.  Scheduled to expire
 * लघुly beक्रमe vblank to flush pending async updates.
 */
काष्ठा msm_pending_समयr अणु
	काष्ठा hrसमयr समयr;
	काष्ठा kthपढ़ो_work work;
	काष्ठा kthपढ़ो_worker *worker;
	काष्ठा msm_kms *kms;
	अचिन्हित crtc_idx;
पूर्ण;

काष्ठा msm_kms अणु
	स्थिर काष्ठा msm_kms_funcs *funcs;
	काष्ठा drm_device *dev;

	/* irq number to be passed on to drm_irq_install */
	पूर्णांक irq;

	/* mapper-id used to request GEM buffer mapped क्रम scanout: */
	काष्ठा msm_gem_address_space *aspace;

	/*
	 * For async commit, where ->flush_commit() and later happens
	 * from the crtc's pending_समयr बंद to end of the frame:
	 */
	काष्ठा mutex commit_lock[MAX_CRTCS];
	अचिन्हित pending_crtc_mask;
	काष्ठा msm_pending_समयr pending_समयrs[MAX_CRTCS];
पूर्ण;

अटल अंतरभूत पूर्णांक msm_kms_init(काष्ठा msm_kms *kms,
		स्थिर काष्ठा msm_kms_funcs *funcs)
अणु
	अचिन्हित i, ret;

	क्रम (i = 0; i < ARRAY_SIZE(kms->commit_lock); i++)
		mutex_init(&kms->commit_lock[i]);

	kms->funcs = funcs;

	क्रम (i = 0; i < ARRAY_SIZE(kms->pending_समयrs); i++) अणु
		ret = msm_atomic_init_pending_समयr(&kms->pending_समयrs[i], kms, i);
		अगर (ret) अणु
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम msm_kms_destroy(काष्ठा msm_kms *kms)
अणु
	अचिन्हित i;

	क्रम (i = 0; i < ARRAY_SIZE(kms->pending_समयrs); i++)
		msm_atomic_destroy_pending_समयr(&kms->pending_समयrs[i]);
पूर्ण

काष्ठा msm_kms *mdp4_kms_init(काष्ठा drm_device *dev);
काष्ठा msm_kms *mdp5_kms_init(काष्ठा drm_device *dev);
काष्ठा msm_kms *dpu_kms_init(काष्ठा drm_device *dev);

काष्ठा msm_mdss_funcs अणु
	पूर्णांक (*enable)(काष्ठा msm_mdss *mdss);
	पूर्णांक (*disable)(काष्ठा msm_mdss *mdss);
	व्योम (*destroy)(काष्ठा drm_device *dev);
पूर्ण;

काष्ठा msm_mdss अणु
	काष्ठा drm_device *dev;
	स्थिर काष्ठा msm_mdss_funcs *funcs;
पूर्ण;

पूर्णांक mdp5_mdss_init(काष्ठा drm_device *dev);
पूर्णांक dpu_mdss_init(काष्ठा drm_device *dev);

#घोषणा क्रम_each_crtc_mask(dev, crtc, crtc_mask) \
	drm_क्रम_each_crtc(crtc, dev) \
		क्रम_each_अगर (drm_crtc_mask(crtc) & (crtc_mask))

#घोषणा क्रम_each_crtc_mask_reverse(dev, crtc, crtc_mask) \
	drm_क्रम_each_crtc_reverse(crtc, dev) \
		क्रम_each_अगर (drm_crtc_mask(crtc) & (crtc_mask))

#पूर्ण_अगर /* __MSM_KMS_H__ */
