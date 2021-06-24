<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * (C) COPYRIGHT 2016 ARM Limited. All rights reserved.
 * Author: Liviu Dudau <Liviu.Dudau@arm.com>
 *
 * ARM Mali DP500/DP550/DP650 KMS/DRM driver
 */

#समावेश <linux/module.h>
#समावेश <linux/clk.h>
#समावेश <linux/component.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/of_reserved_स्मृति.स>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/debugfs.h>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_fb_cma_helper.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_gem_cma_helper.h>
#समावेश <drm/drm_gem_framebuffer_helper.h>
#समावेश <drm/drm_modeset_helper.h>
#समावेश <drm/drm_of.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_vblank.h>

#समावेश "malidp_drv.h"
#समावेश "malidp_mw.h"
#समावेश "malidp_regs.h"
#समावेश "malidp_hw.h"

#घोषणा MALIDP_CONF_VALID_TIMEOUT	250
#घोषणा AFBC_HEADER_SIZE		16
#घोषणा AFBC_SUPERBLK_ALIGNMENT		128

अटल व्योम malidp_ग_लिखो_gamma_table(काष्ठा malidp_hw_device *hwdev,
				     u32 data[MALIDP_COEFFTAB_NUM_COEFFS])
अणु
	पूर्णांक i;
	/* Update all channels with a single gamma curve. */
	स्थिर u32 gamma_ग_लिखो_mask = GENMASK(18, 16);
	/*
	 * Always ग_लिखो an entire table, so the address field in
	 * DE_COEFFTAB_ADDR is 0 and we can use the gamma_ग_लिखो_mask biपंचांगask
	 * directly.
	 */
	malidp_hw_ग_लिखो(hwdev, gamma_ग_लिखो_mask,
			hwdev->hw->map.coeffs_base + MALIDP_COEF_TABLE_ADDR);
	क्रम (i = 0; i < MALIDP_COEFFTAB_NUM_COEFFS; ++i)
		malidp_hw_ग_लिखो(hwdev, data[i],
				hwdev->hw->map.coeffs_base +
				MALIDP_COEF_TABLE_DATA);
पूर्ण

अटल व्योम malidp_atomic_commit_update_gamma(काष्ठा drm_crtc *crtc,
					      काष्ठा drm_crtc_state *old_state)
अणु
	काष्ठा malidp_drm *malidp = crtc_to_malidp_device(crtc);
	काष्ठा malidp_hw_device *hwdev = malidp->dev;

	अगर (!crtc->state->color_mgmt_changed)
		वापस;

	अगर (!crtc->state->gamma_lut) अणु
		malidp_hw_clearbits(hwdev,
				    MALIDP_DISP_FUNC_GAMMA,
				    MALIDP_DE_DISPLAY_FUNC);
	पूर्ण अन्यथा अणु
		काष्ठा malidp_crtc_state *mc =
			to_malidp_crtc_state(crtc->state);

		अगर (!old_state->gamma_lut || (crtc->state->gamma_lut->base.id !=
					      old_state->gamma_lut->base.id))
			malidp_ग_लिखो_gamma_table(hwdev, mc->gamma_coeffs);

		malidp_hw_setbits(hwdev, MALIDP_DISP_FUNC_GAMMA,
				  MALIDP_DE_DISPLAY_FUNC);
	पूर्ण
पूर्ण

अटल
व्योम malidp_atomic_commit_update_coloradj(काष्ठा drm_crtc *crtc,
					  काष्ठा drm_crtc_state *old_state)
अणु
	काष्ठा malidp_drm *malidp = crtc_to_malidp_device(crtc);
	काष्ठा malidp_hw_device *hwdev = malidp->dev;
	पूर्णांक i;

	अगर (!crtc->state->color_mgmt_changed)
		वापस;

	अगर (!crtc->state->cपंचांग) अणु
		malidp_hw_clearbits(hwdev, MALIDP_DISP_FUNC_CADJ,
				    MALIDP_DE_DISPLAY_FUNC);
	पूर्ण अन्यथा अणु
		काष्ठा malidp_crtc_state *mc =
			to_malidp_crtc_state(crtc->state);

		अगर (!old_state->cपंचांग || (crtc->state->cपंचांग->base.id !=
					old_state->cपंचांग->base.id))
			क्रम (i = 0; i < MALIDP_COLORADJ_NUM_COEFFS; ++i)
				malidp_hw_ग_लिखो(hwdev,
						mc->coloradj_coeffs[i],
						hwdev->hw->map.coeffs_base +
						MALIDP_COLOR_ADJ_COEF + 4 * i);

		malidp_hw_setbits(hwdev, MALIDP_DISP_FUNC_CADJ,
				  MALIDP_DE_DISPLAY_FUNC);
	पूर्ण
पूर्ण

अटल व्योम malidp_atomic_commit_se_config(काष्ठा drm_crtc *crtc,
					   काष्ठा drm_crtc_state *old_state)
अणु
	काष्ठा malidp_crtc_state *cs = to_malidp_crtc_state(crtc->state);
	काष्ठा malidp_crtc_state *old_cs = to_malidp_crtc_state(old_state);
	काष्ठा malidp_drm *malidp = crtc_to_malidp_device(crtc);
	काष्ठा malidp_hw_device *hwdev = malidp->dev;
	काष्ठा malidp_se_config *s = &cs->scaler_config;
	काष्ठा malidp_se_config *old_s = &old_cs->scaler_config;
	u32 se_control = hwdev->hw->map.se_base +
			 ((hwdev->hw->map.features & MALIDP_REGMAP_HAS_CLEARIRQ) ?
			 0x10 : 0xC);
	u32 layer_control = se_control + MALIDP_SE_LAYER_CONTROL;
	u32 scr = se_control + MALIDP_SE_SCALING_CONTROL;
	u32 val;

	/* Set SE_CONTROL */
	अगर (!s->scale_enable) अणु
		val = malidp_hw_पढ़ो(hwdev, se_control);
		val &= ~MALIDP_SE_SCALING_EN;
		malidp_hw_ग_लिखो(hwdev, val, se_control);
		वापस;
	पूर्ण

	hwdev->hw->se_set_scaling_coeffs(hwdev, s, old_s);
	val = malidp_hw_पढ़ो(hwdev, se_control);
	val |= MALIDP_SE_SCALING_EN | MALIDP_SE_ALPHA_EN;

	val &= ~MALIDP_SE_ENH(MALIDP_SE_ENH_MASK);
	val |= s->enhancer_enable ? MALIDP_SE_ENH(3) : 0;

	val |= MALIDP_SE_RGBO_IF_EN;
	malidp_hw_ग_लिखो(hwdev, val, se_control);

	/* Set IN_SIZE & OUT_SIZE. */
	val = MALIDP_SE_SET_V_SIZE(s->input_h) |
	      MALIDP_SE_SET_H_SIZE(s->input_w);
	malidp_hw_ग_लिखो(hwdev, val, layer_control + MALIDP_SE_L0_IN_SIZE);
	val = MALIDP_SE_SET_V_SIZE(s->output_h) |
	      MALIDP_SE_SET_H_SIZE(s->output_w);
	malidp_hw_ग_लिखो(hwdev, val, layer_control + MALIDP_SE_L0_OUT_SIZE);

	/* Set phase regs. */
	malidp_hw_ग_लिखो(hwdev, s->h_init_phase, scr + MALIDP_SE_H_INIT_PH);
	malidp_hw_ग_लिखो(hwdev, s->h_delta_phase, scr + MALIDP_SE_H_DELTA_PH);
	malidp_hw_ग_लिखो(hwdev, s->v_init_phase, scr + MALIDP_SE_V_INIT_PH);
	malidp_hw_ग_लिखो(hwdev, s->v_delta_phase, scr + MALIDP_SE_V_DELTA_PH);
पूर्ण

/*
 * set the "config valid" bit and रुको until the hardware acts on it
 */
अटल पूर्णांक malidp_set_and_रुको_config_valid(काष्ठा drm_device *drm)
अणु
	काष्ठा malidp_drm *malidp = drm->dev_निजी;
	काष्ठा malidp_hw_device *hwdev = malidp->dev;
	पूर्णांक ret;

	hwdev->hw->set_config_valid(hwdev, 1);
	/* करोn't रुको क्रम config_valid flag अगर we are in config mode */
	अगर (hwdev->hw->in_config_mode(hwdev)) अणु
		atomic_set(&malidp->config_valid, MALIDP_CONFIG_VALID_DONE);
		वापस 0;
	पूर्ण

	ret = रुको_event_पूर्णांकerruptible_समयout(malidp->wq,
			atomic_पढ़ो(&malidp->config_valid) == MALIDP_CONFIG_VALID_DONE,
			msecs_to_jअगरfies(MALIDP_CONF_VALID_TIMEOUT));

	वापस (ret > 0) ? 0 : -ETIMEDOUT;
पूर्ण

अटल व्योम malidp_atomic_commit_hw_करोne(काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_device *drm = state->dev;
	काष्ठा malidp_drm *malidp = drm->dev_निजी;
	पूर्णांक loop = 5;

	malidp->event = malidp->crtc.state->event;
	malidp->crtc.state->event = शून्य;

	अगर (malidp->crtc.state->active) अणु
		/*
		 * अगर we have an event to deliver to userspace, make sure
		 * the vblank is enabled as we are sending it from the IRQ
		 * handler.
		 */
		अगर (malidp->event)
			drm_crtc_vblank_get(&malidp->crtc);

		/* only set config_valid अगर the CRTC is enabled */
		अगर (malidp_set_and_रुको_config_valid(drm) < 0) अणु
			/*
			 * make a loop around the second CVAL setting and
			 * try 5 बार beक्रमe giving up.
			 */
			जबतक (loop--) अणु
				अगर (!malidp_set_and_रुको_config_valid(drm))
					अवरोध;
			पूर्ण
			DRM_DEBUG_DRIVER("timed out waiting for updated configuration\n");
		पूर्ण

	पूर्ण अन्यथा अगर (malidp->event) अणु
		/* CRTC inactive means vblank IRQ is disabled, send event directly */
		spin_lock_irq(&drm->event_lock);
		drm_crtc_send_vblank_event(&malidp->crtc, malidp->event);
		malidp->event = शून्य;
		spin_unlock_irq(&drm->event_lock);
	पूर्ण
	drm_atomic_helper_commit_hw_करोne(state);
पूर्ण

अटल व्योम malidp_atomic_commit_tail(काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_device *drm = state->dev;
	काष्ठा malidp_drm *malidp = drm->dev_निजी;
	काष्ठा drm_crtc *crtc;
	काष्ठा drm_crtc_state *old_crtc_state;
	पूर्णांक i;
	bool fence_cookie = dma_fence_begin_संकेतling();

	pm_runसमय_get_sync(drm->dev);

	/*
	 * set config_valid to a special value to let IRQ handlers
	 * know that we are updating रेजिस्टरs
	 */
	atomic_set(&malidp->config_valid, MALIDP_CONFIG_START);
	malidp->dev->hw->set_config_valid(malidp->dev, 0);

	drm_atomic_helper_commit_modeset_disables(drm, state);

	क्रम_each_old_crtc_in_state(state, crtc, old_crtc_state, i) अणु
		malidp_atomic_commit_update_gamma(crtc, old_crtc_state);
		malidp_atomic_commit_update_coloradj(crtc, old_crtc_state);
		malidp_atomic_commit_se_config(crtc, old_crtc_state);
	पूर्ण

	drm_atomic_helper_commit_planes(drm, state, DRM_PLANE_COMMIT_ACTIVE_ONLY);

	malidp_mw_atomic_commit(drm, state);

	drm_atomic_helper_commit_modeset_enables(drm, state);

	malidp_atomic_commit_hw_करोne(state);

	dma_fence_end_संकेतling(fence_cookie);

	pm_runसमय_put(drm->dev);

	drm_atomic_helper_cleanup_planes(drm, state);
पूर्ण

अटल स्थिर काष्ठा drm_mode_config_helper_funcs malidp_mode_config_helpers = अणु
	.atomic_commit_tail = malidp_atomic_commit_tail,
पूर्ण;

अटल bool
malidp_verअगरy_afbc_framebuffer_caps(काष्ठा drm_device *dev,
				    स्थिर काष्ठा drm_mode_fb_cmd2 *mode_cmd)
अणु
	अगर (malidp_क्रमmat_mod_supported(dev, mode_cmd->pixel_क्रमmat,
					mode_cmd->modअगरier[0]) == false)
		वापस false;

	अगर (mode_cmd->offsets[0] != 0) अणु
		DRM_DEBUG_KMS("AFBC buffers' plane offset should be 0\n");
		वापस false;
	पूर्ण

	चयन (mode_cmd->modअगरier[0] & AFBC_SIZE_MASK) अणु
	हाल AFBC_SIZE_16X16:
		अगर ((mode_cmd->width % 16) || (mode_cmd->height % 16)) अणु
			DRM_DEBUG_KMS("AFBC buffers must be aligned to 16 pixels\n");
			वापस false;
		पूर्ण
		अवरोध;
	शेष:
		DRM_DEBUG_KMS("Unsupported AFBC block size\n");
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल bool
malidp_verअगरy_afbc_framebuffer_size(काष्ठा drm_device *dev,
				    काष्ठा drm_file *file,
				    स्थिर काष्ठा drm_mode_fb_cmd2 *mode_cmd)
अणु
	पूर्णांक n_superblocks = 0;
	स्थिर काष्ठा drm_क्रमmat_info *info;
	काष्ठा drm_gem_object *objs = शून्य;
	u32 afbc_superblock_size = 0, afbc_superblock_height = 0;
	u32 afbc_superblock_width = 0, afbc_size = 0;
	पूर्णांक bpp = 0;

	चयन (mode_cmd->modअगरier[0] & AFBC_SIZE_MASK) अणु
	हाल AFBC_SIZE_16X16:
		afbc_superblock_height = 16;
		afbc_superblock_width = 16;
		अवरोध;
	शेष:
		DRM_DEBUG_KMS("AFBC superblock size is not supported\n");
		वापस false;
	पूर्ण

	info = drm_get_क्रमmat_info(dev, mode_cmd);

	n_superblocks = (mode_cmd->width / afbc_superblock_width) *
		(mode_cmd->height / afbc_superblock_height);

	bpp = malidp_क्रमmat_get_bpp(info->क्रमmat);

	afbc_superblock_size = (bpp * afbc_superblock_width * afbc_superblock_height)
				/ BITS_PER_BYTE;

	afbc_size = ALIGN(n_superblocks * AFBC_HEADER_SIZE, AFBC_SUPERBLK_ALIGNMENT);
	afbc_size += n_superblocks * ALIGN(afbc_superblock_size, AFBC_SUPERBLK_ALIGNMENT);

	अगर ((mode_cmd->width * bpp) != (mode_cmd->pitches[0] * BITS_PER_BYTE)) अणु
		DRM_DEBUG_KMS("Invalid value of (pitch * BITS_PER_BYTE) (=%u) "
			      "should be same as width (=%u) * bpp (=%u)\n",
			      (mode_cmd->pitches[0] * BITS_PER_BYTE),
			      mode_cmd->width, bpp);
		वापस false;
	पूर्ण

	objs = drm_gem_object_lookup(file, mode_cmd->handles[0]);
	अगर (!objs) अणु
		DRM_DEBUG_KMS("Failed to lookup GEM object\n");
		वापस false;
	पूर्ण

	अगर (objs->size < afbc_size) अणु
		DRM_DEBUG_KMS("buffer size (%zu) too small for AFBC buffer size = %u\n",
			      objs->size, afbc_size);
		drm_gem_object_put(objs);
		वापस false;
	पूर्ण

	drm_gem_object_put(objs);

	वापस true;
पूर्ण

अटल bool
malidp_verअगरy_afbc_framebuffer(काष्ठा drm_device *dev, काष्ठा drm_file *file,
			       स्थिर काष्ठा drm_mode_fb_cmd2 *mode_cmd)
अणु
	अगर (malidp_verअगरy_afbc_framebuffer_caps(dev, mode_cmd))
		वापस malidp_verअगरy_afbc_framebuffer_size(dev, file, mode_cmd);

	वापस false;
पूर्ण

अटल काष्ठा drm_framebuffer *
malidp_fb_create(काष्ठा drm_device *dev, काष्ठा drm_file *file,
		 स्थिर काष्ठा drm_mode_fb_cmd2 *mode_cmd)
अणु
	अगर (mode_cmd->modअगरier[0]) अणु
		अगर (!malidp_verअगरy_afbc_framebuffer(dev, file, mode_cmd))
			वापस ERR_PTR(-EINVAL);
	पूर्ण

	वापस drm_gem_fb_create(dev, file, mode_cmd);
पूर्ण

अटल स्थिर काष्ठा drm_mode_config_funcs malidp_mode_config_funcs = अणु
	.fb_create = malidp_fb_create,
	.atomic_check = drm_atomic_helper_check,
	.atomic_commit = drm_atomic_helper_commit,
पूर्ण;

अटल पूर्णांक malidp_init(काष्ठा drm_device *drm)
अणु
	पूर्णांक ret;
	काष्ठा malidp_drm *malidp = drm->dev_निजी;
	काष्ठा malidp_hw_device *hwdev = malidp->dev;

	drm_mode_config_init(drm);

	drm->mode_config.min_width = hwdev->min_line_size;
	drm->mode_config.min_height = hwdev->min_line_size;
	drm->mode_config.max_width = hwdev->max_line_size;
	drm->mode_config.max_height = hwdev->max_line_size;
	drm->mode_config.funcs = &malidp_mode_config_funcs;
	drm->mode_config.helper_निजी = &malidp_mode_config_helpers;
	drm->mode_config.allow_fb_modअगरiers = true;

	ret = malidp_crtc_init(drm);
	अगर (ret)
		जाओ crtc_fail;

	ret = malidp_mw_connector_init(drm);
	अगर (ret)
		जाओ crtc_fail;

	वापस 0;

crtc_fail:
	drm_mode_config_cleanup(drm);
	वापस ret;
पूर्ण

अटल व्योम malidp_fini(काष्ठा drm_device *drm)
अणु
	drm_mode_config_cleanup(drm);
पूर्ण

अटल पूर्णांक malidp_irq_init(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक irq_de, irq_se, ret = 0;
	काष्ठा drm_device *drm = dev_get_drvdata(&pdev->dev);
	काष्ठा malidp_drm *malidp = drm->dev_निजी;
	काष्ठा malidp_hw_device *hwdev = malidp->dev;

	/* fetch the पूर्णांकerrupts from DT */
	irq_de = platक्रमm_get_irq_byname(pdev, "DE");
	अगर (irq_de < 0) अणु
		DRM_ERROR("no 'DE' IRQ specified!\n");
		वापस irq_de;
	पूर्ण
	irq_se = platक्रमm_get_irq_byname(pdev, "SE");
	अगर (irq_se < 0) अणु
		DRM_ERROR("no 'SE' IRQ specified!\n");
		वापस irq_se;
	पूर्ण

	ret = malidp_de_irq_init(drm, irq_de);
	अगर (ret)
		वापस ret;

	ret = malidp_se_irq_init(drm, irq_se);
	अगर (ret) अणु
		malidp_de_irq_fini(hwdev);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

DEFINE_DRM_GEM_CMA_FOPS(fops);

अटल पूर्णांक malidp_dumb_create(काष्ठा drm_file *file_priv,
			      काष्ठा drm_device *drm,
			      काष्ठा drm_mode_create_dumb *args)
अणु
	काष्ठा malidp_drm *malidp = drm->dev_निजी;
	/* allocate क्रम the worst हाल scenario, i.e. rotated buffers */
	u8 alignment = malidp_hw_get_pitch_align(malidp->dev, 1);

	args->pitch = ALIGN(DIV_ROUND_UP(args->width * args->bpp, 8), alignment);

	वापस drm_gem_cma_dumb_create_पूर्णांकernal(file_priv, drm, args);
पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS

अटल व्योम malidp_error_stats_init(काष्ठा malidp_error_stats *error_stats)
अणु
	error_stats->num_errors = 0;
	error_stats->last_error_status = 0;
	error_stats->last_error_vblank = -1;
पूर्ण

व्योम malidp_error(काष्ठा malidp_drm *malidp,
		  काष्ठा malidp_error_stats *error_stats, u32 status,
		  u64 vblank)
अणु
	अचिन्हित दीर्घ irqflags;

	spin_lock_irqsave(&malidp->errors_lock, irqflags);
	error_stats->last_error_status = status;
	error_stats->last_error_vblank = vblank;
	error_stats->num_errors++;
	spin_unlock_irqrestore(&malidp->errors_lock, irqflags);
पूर्ण

अटल व्योम malidp_error_stats_dump(स्थिर अक्षर *prefix,
				    काष्ठा malidp_error_stats error_stats,
				    काष्ठा seq_file *m)
अणु
	seq_म_लिखो(m, "[%s] num_errors : %d\n", prefix,
		   error_stats.num_errors);
	seq_म_लिखो(m, "[%s] last_error_status  : 0x%08x\n", prefix,
		   error_stats.last_error_status);
	seq_म_लिखो(m, "[%s] last_error_vblank : %lld\n", prefix,
		   error_stats.last_error_vblank);
पूर्ण

अटल पूर्णांक malidp_show_stats(काष्ठा seq_file *m, व्योम *arg)
अणु
	काष्ठा drm_device *drm = m->निजी;
	काष्ठा malidp_drm *malidp = drm->dev_निजी;
	अचिन्हित दीर्घ irqflags;
	काष्ठा malidp_error_stats de_errors, se_errors;

	spin_lock_irqsave(&malidp->errors_lock, irqflags);
	de_errors = malidp->de_errors;
	se_errors = malidp->se_errors;
	spin_unlock_irqrestore(&malidp->errors_lock, irqflags);
	malidp_error_stats_dump("DE", de_errors, m);
	malidp_error_stats_dump("SE", se_errors, m);
	वापस 0;
पूर्ण

अटल पूर्णांक malidp_debugfs_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, malidp_show_stats, inode->i_निजी);
पूर्ण

अटल sमाप_प्रकार malidp_debugfs_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *ubuf,
				    माप_प्रकार len, loff_t *offp)
अणु
	काष्ठा seq_file *m = file->निजी_data;
	काष्ठा drm_device *drm = m->निजी;
	काष्ठा malidp_drm *malidp = drm->dev_निजी;
	अचिन्हित दीर्घ irqflags;

	spin_lock_irqsave(&malidp->errors_lock, irqflags);
	malidp_error_stats_init(&malidp->de_errors);
	malidp_error_stats_init(&malidp->se_errors);
	spin_unlock_irqrestore(&malidp->errors_lock, irqflags);
	वापस len;
पूर्ण

अटल स्थिर काष्ठा file_operations malidp_debugfs_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = malidp_debugfs_खोलो,
	.पढ़ो = seq_पढ़ो,
	.ग_लिखो = malidp_debugfs_ग_लिखो,
	.llseek = seq_lseek,
	.release = single_release,
पूर्ण;

अटल व्योम malidp_debugfs_init(काष्ठा drm_minor *minor)
अणु
	काष्ठा malidp_drm *malidp = minor->dev->dev_निजी;

	malidp_error_stats_init(&malidp->de_errors);
	malidp_error_stats_init(&malidp->se_errors);
	spin_lock_init(&malidp->errors_lock);
	debugfs_create_file("debug", S_IRUGO | S_IWUSR, minor->debugfs_root,
			    minor->dev, &malidp_debugfs_fops);
पूर्ण

#पूर्ण_अगर //CONFIG_DEBUG_FS

अटल स्थिर काष्ठा drm_driver malidp_driver = अणु
	.driver_features = DRIVER_GEM | DRIVER_MODESET | DRIVER_ATOMIC,
	DRM_GEM_CMA_DRIVER_OPS_WITH_DUMB_CREATE(malidp_dumb_create),
#अगर_घोषित CONFIG_DEBUG_FS
	.debugfs_init = malidp_debugfs_init,
#पूर्ण_अगर
	.fops = &fops,
	.name = "mali-dp",
	.desc = "ARM Mali Display Processor driver",
	.date = "20160106",
	.major = 1,
	.minor = 0,
पूर्ण;

अटल स्थिर काष्ठा of_device_id  malidp_drm_of_match[] = अणु
	अणु
		.compatible = "arm,mali-dp500",
		.data = &malidp_device[MALIDP_500]
	पूर्ण,
	अणु
		.compatible = "arm,mali-dp550",
		.data = &malidp_device[MALIDP_550]
	पूर्ण,
	अणु
		.compatible = "arm,mali-dp650",
		.data = &malidp_device[MALIDP_650]
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, malidp_drm_of_match);

अटल bool malidp_is_compatible_hw_id(काष्ठा malidp_hw_device *hwdev,
				       स्थिर काष्ठा of_device_id *dev_id)
अणु
	u32 core_id;
	स्थिर अक्षर *compatstr_dp500 = "arm,mali-dp500";
	bool is_dp500;
	bool dt_is_dp500;

	/*
	 * The DP500 CORE_ID रेजिस्टर is in a dअगरferent location, so check it
	 * first. If the product id field matches, then this is DP500, otherwise
	 * check the DP550/650 CORE_ID रेजिस्टर.
	 */
	core_id = malidp_hw_पढ़ो(hwdev, MALIDP500_DC_BASE + MALIDP_DE_CORE_ID);
	/* Offset 0x18 will never पढ़ो 0x500 on products other than DP500. */
	is_dp500 = (MALIDP_PRODUCT_ID(core_id) == 0x500);
	dt_is_dp500 = strnstr(dev_id->compatible, compatstr_dp500,
			      माप(dev_id->compatible)) != शून्य;
	अगर (is_dp500 != dt_is_dp500) अणु
		DRM_ERROR("Device-tree expects %s, but hardware %s DP500.\n",
			  dev_id->compatible, is_dp500 ? "is" : "is not");
		वापस false;
	पूर्ण अन्यथा अगर (!dt_is_dp500) अणु
		u16 product_id;
		अक्षर buf[32];

		core_id = malidp_hw_पढ़ो(hwdev,
					 MALIDP550_DC_BASE + MALIDP_DE_CORE_ID);
		product_id = MALIDP_PRODUCT_ID(core_id);
		snम_लिखो(buf, माप(buf), "arm,mali-dp%X", product_id);
		अगर (!strnstr(dev_id->compatible, buf,
			     माप(dev_id->compatible))) अणु
			DRM_ERROR("Device-tree expects %s, but hardware is DP%03X.\n",
				  dev_id->compatible, product_id);
			वापस false;
		पूर्ण
	पूर्ण
	वापस true;
पूर्ण

अटल bool malidp_has_sufficient_address_space(स्थिर काष्ठा resource *res,
						स्थिर काष्ठा of_device_id *dev_id)
अणु
	resource_माप_प्रकार res_size = resource_size(res);
	स्थिर अक्षर *compatstr_dp500 = "arm,mali-dp500";

	अगर (!strnstr(dev_id->compatible, compatstr_dp500,
		     माप(dev_id->compatible)))
		वापस res_size >= MALIDP550_ADDR_SPACE_SIZE;
	अन्यथा अगर (res_size < MALIDP500_ADDR_SPACE_SIZE)
		वापस false;
	वापस true;
पूर्ण

अटल sमाप_प्रकार core_id_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	काष्ठा drm_device *drm = dev_get_drvdata(dev);
	काष्ठा malidp_drm *malidp = drm->dev_निजी;

	वापस snम_लिखो(buf, PAGE_SIZE, "%08x\n", malidp->core_id);
पूर्ण

अटल DEVICE_ATTR_RO(core_id);

अटल काष्ठा attribute *mali_dp_attrs[] = अणु
	&dev_attr_core_id.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(mali_dp);

#घोषणा MAX_OUTPUT_CHANNELS	3

अटल पूर्णांक malidp_runसमय_pm_suspend(काष्ठा device *dev)
अणु
	काष्ठा drm_device *drm = dev_get_drvdata(dev);
	काष्ठा malidp_drm *malidp = drm->dev_निजी;
	काष्ठा malidp_hw_device *hwdev = malidp->dev;

	/* we can only suspend अगर the hardware is in config mode */
	WARN_ON(!hwdev->hw->in_config_mode(hwdev));

	malidp_se_irq_fini(hwdev);
	malidp_de_irq_fini(hwdev);
	hwdev->pm_suspended = true;
	clk_disable_unprepare(hwdev->mclk);
	clk_disable_unprepare(hwdev->aclk);
	clk_disable_unprepare(hwdev->pclk);

	वापस 0;
पूर्ण

अटल पूर्णांक malidp_runसमय_pm_resume(काष्ठा device *dev)
अणु
	काष्ठा drm_device *drm = dev_get_drvdata(dev);
	काष्ठा malidp_drm *malidp = drm->dev_निजी;
	काष्ठा malidp_hw_device *hwdev = malidp->dev;

	clk_prepare_enable(hwdev->pclk);
	clk_prepare_enable(hwdev->aclk);
	clk_prepare_enable(hwdev->mclk);
	hwdev->pm_suspended = false;
	malidp_de_irq_hw_init(hwdev);
	malidp_se_irq_hw_init(hwdev);

	वापस 0;
पूर्ण

अटल पूर्णांक malidp_bind(काष्ठा device *dev)
अणु
	काष्ठा resource *res;
	काष्ठा drm_device *drm;
	काष्ठा malidp_drm *malidp;
	काष्ठा malidp_hw_device *hwdev;
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा of_device_id स्थिर *dev_id;
	काष्ठा drm_encoder *encoder;
	/* number of lines क्रम the R, G and B output */
	u8 output_width[MAX_OUTPUT_CHANNELS];
	पूर्णांक ret = 0, i;
	u32 version, out_depth = 0;

	malidp = devm_kzalloc(dev, माप(*malidp), GFP_KERNEL);
	अगर (!malidp)
		वापस -ENOMEM;

	hwdev = devm_kzalloc(dev, माप(*hwdev), GFP_KERNEL);
	अगर (!hwdev)
		वापस -ENOMEM;

	hwdev->hw = (काष्ठा malidp_hw *)of_device_get_match_data(dev);
	malidp->dev = hwdev;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	hwdev->regs = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(hwdev->regs))
		वापस PTR_ERR(hwdev->regs);

	hwdev->pclk = devm_clk_get(dev, "pclk");
	अगर (IS_ERR(hwdev->pclk))
		वापस PTR_ERR(hwdev->pclk);

	hwdev->aclk = devm_clk_get(dev, "aclk");
	अगर (IS_ERR(hwdev->aclk))
		वापस PTR_ERR(hwdev->aclk);

	hwdev->mclk = devm_clk_get(dev, "mclk");
	अगर (IS_ERR(hwdev->mclk))
		वापस PTR_ERR(hwdev->mclk);

	hwdev->pxlclk = devm_clk_get(dev, "pxlclk");
	अगर (IS_ERR(hwdev->pxlclk))
		वापस PTR_ERR(hwdev->pxlclk);

	/* Get the optional framebuffer memory resource */
	ret = of_reserved_mem_device_init(dev);
	अगर (ret && ret != -ENODEV)
		वापस ret;

	drm = drm_dev_alloc(&malidp_driver, dev);
	अगर (IS_ERR(drm)) अणु
		ret = PTR_ERR(drm);
		जाओ alloc_fail;
	पूर्ण

	drm->dev_निजी = malidp;
	dev_set_drvdata(dev, drm);

	/* Enable घातer management */
	pm_runसमय_enable(dev);

	/* Resume device to enable the घड़ीs */
	अगर (pm_runसमय_enabled(dev))
		pm_runसमय_get_sync(dev);
	अन्यथा
		malidp_runसमय_pm_resume(dev);

	dev_id = of_match_device(malidp_drm_of_match, dev);
	अगर (!dev_id) अणु
		ret = -EINVAL;
		जाओ query_hw_fail;
	पूर्ण

	अगर (!malidp_has_sufficient_address_space(res, dev_id)) अणु
		DRM_ERROR("Insufficient address space in device-tree.\n");
		ret = -EINVAL;
		जाओ query_hw_fail;
	पूर्ण

	अगर (!malidp_is_compatible_hw_id(hwdev, dev_id)) अणु
		ret = -EINVAL;
		जाओ query_hw_fail;
	पूर्ण

	ret = hwdev->hw->query_hw(hwdev);
	अगर (ret) अणु
		DRM_ERROR("Invalid HW configuration\n");
		जाओ query_hw_fail;
	पूर्ण

	version = malidp_hw_पढ़ो(hwdev, hwdev->hw->map.dc_base + MALIDP_DE_CORE_ID);
	DRM_INFO("found ARM Mali-DP%3x version r%dp%d\n", version >> 16,
		 (version >> 12) & 0xf, (version >> 8) & 0xf);

	malidp->core_id = version;

	ret = of_property_पढ़ो_u32(dev->of_node,
					"arm,malidp-arqos-value",
					&hwdev->arqos_value);
	अगर (ret)
		hwdev->arqos_value = 0x0;

	/* set the number of lines used क्रम output of RGB data */
	ret = of_property_पढ़ो_u8_array(dev->of_node,
					"arm,malidp-output-port-lines",
					output_width, MAX_OUTPUT_CHANNELS);
	अगर (ret)
		जाओ query_hw_fail;

	क्रम (i = 0; i < MAX_OUTPUT_CHANNELS; i++)
		out_depth = (out_depth << 8) | (output_width[i] & 0xf);
	malidp_hw_ग_लिखो(hwdev, out_depth, hwdev->hw->map.out_depth_base);
	hwdev->output_color_depth = out_depth;

	atomic_set(&malidp->config_valid, MALIDP_CONFIG_VALID_INIT);
	init_रुकोqueue_head(&malidp->wq);

	ret = malidp_init(drm);
	अगर (ret < 0)
		जाओ query_hw_fail;

	/* Set the CRTC's port so that the encoder component can find it */
	malidp->crtc.port = of_graph_get_port_by_id(dev->of_node, 0);

	ret = component_bind_all(dev, drm);
	अगर (ret) अणु
		DRM_ERROR("Failed to bind all components\n");
		जाओ bind_fail;
	पूर्ण

	/* We expect to have a maximum of two encoders one क्रम the actual
	 * display and a भव one क्रम the ग_लिखोback connector
	 */
	WARN_ON(drm->mode_config.num_encoder > 2);
	list_क्रम_each_entry(encoder, &drm->mode_config.encoder_list, head) अणु
		encoder->possible_clones =
				(1 << drm->mode_config.num_encoder) -  1;
	पूर्ण

	ret = malidp_irq_init(pdev);
	अगर (ret < 0)
		जाओ irq_init_fail;

	drm->irq_enabled = true;

	ret = drm_vblank_init(drm, drm->mode_config.num_crtc);
	अगर (ret < 0) अणु
		DRM_ERROR("failed to initialise vblank\n");
		जाओ vblank_fail;
	पूर्ण
	pm_runसमय_put(dev);

	drm_mode_config_reset(drm);

	drm_kms_helper_poll_init(drm);

	ret = drm_dev_रेजिस्टर(drm, 0);
	अगर (ret)
		जाओ रेजिस्टर_fail;

	drm_fbdev_generic_setup(drm, 32);

	वापस 0;

रेजिस्टर_fail:
	drm_kms_helper_poll_fini(drm);
	pm_runसमय_get_sync(dev);
vblank_fail:
	malidp_se_irq_fini(hwdev);
	malidp_de_irq_fini(hwdev);
	drm->irq_enabled = false;
irq_init_fail:
	drm_atomic_helper_shutकरोwn(drm);
	component_unbind_all(dev, drm);
bind_fail:
	of_node_put(malidp->crtc.port);
	malidp->crtc.port = शून्य;
	malidp_fini(drm);
query_hw_fail:
	pm_runसमय_put(dev);
	अगर (pm_runसमय_enabled(dev))
		pm_runसमय_disable(dev);
	अन्यथा
		malidp_runसमय_pm_suspend(dev);
	drm->dev_निजी = शून्य;
	dev_set_drvdata(dev, शून्य);
	drm_dev_put(drm);
alloc_fail:
	of_reserved_mem_device_release(dev);

	वापस ret;
पूर्ण

अटल व्योम malidp_unbind(काष्ठा device *dev)
अणु
	काष्ठा drm_device *drm = dev_get_drvdata(dev);
	काष्ठा malidp_drm *malidp = drm->dev_निजी;
	काष्ठा malidp_hw_device *hwdev = malidp->dev;

	drm_dev_unरेजिस्टर(drm);
	drm_kms_helper_poll_fini(drm);
	pm_runसमय_get_sync(dev);
	drm_atomic_helper_shutकरोwn(drm);
	malidp_se_irq_fini(hwdev);
	malidp_de_irq_fini(hwdev);
	drm->irq_enabled = false;
	component_unbind_all(dev, drm);
	of_node_put(malidp->crtc.port);
	malidp->crtc.port = शून्य;
	malidp_fini(drm);
	pm_runसमय_put(dev);
	अगर (pm_runसमय_enabled(dev))
		pm_runसमय_disable(dev);
	अन्यथा
		malidp_runसमय_pm_suspend(dev);
	drm->dev_निजी = शून्य;
	dev_set_drvdata(dev, शून्य);
	drm_dev_put(drm);
	of_reserved_mem_device_release(dev);
पूर्ण

अटल स्थिर काष्ठा component_master_ops malidp_master_ops = अणु
	.bind = malidp_bind,
	.unbind = malidp_unbind,
पूर्ण;

अटल पूर्णांक malidp_compare_dev(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा device_node *np = data;

	वापस dev->of_node == np;
पूर्ण

अटल पूर्णांक malidp_platक्रमm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *port;
	काष्ठा component_match *match = शून्य;

	अगर (!pdev->dev.of_node)
		वापस -ENODEV;

	/* there is only one output port inside each device, find it */
	port = of_graph_get_remote_node(pdev->dev.of_node, 0, 0);
	अगर (!port)
		वापस -ENODEV;

	drm_of_component_match_add(&pdev->dev, &match, malidp_compare_dev,
				   port);
	of_node_put(port);
	वापस component_master_add_with_match(&pdev->dev, &malidp_master_ops,
					       match);
पूर्ण

अटल पूर्णांक malidp_platक्रमm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	component_master_del(&pdev->dev, &malidp_master_ops);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused malidp_pm_suspend(काष्ठा device *dev)
अणु
	काष्ठा drm_device *drm = dev_get_drvdata(dev);

	वापस drm_mode_config_helper_suspend(drm);
पूर्ण

अटल पूर्णांक __maybe_unused malidp_pm_resume(काष्ठा device *dev)
अणु
	काष्ठा drm_device *drm = dev_get_drvdata(dev);

	drm_mode_config_helper_resume(drm);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused malidp_pm_suspend_late(काष्ठा device *dev)
अणु
	अगर (!pm_runसमय_status_suspended(dev)) अणु
		malidp_runसमय_pm_suspend(dev);
		pm_runसमय_set_suspended(dev);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused malidp_pm_resume_early(काष्ठा device *dev)
अणु
	malidp_runसमय_pm_resume(dev);
	pm_runसमय_set_active(dev);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops malidp_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(malidp_pm_suspend, malidp_pm_resume) \
	SET_LATE_SYSTEM_SLEEP_PM_OPS(malidp_pm_suspend_late, malidp_pm_resume_early) \
	SET_RUNTIME_PM_OPS(malidp_runसमय_pm_suspend, malidp_runसमय_pm_resume, शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver malidp_platक्रमm_driver = अणु
	.probe		= malidp_platक्रमm_probe,
	.हटाओ		= malidp_platक्रमm_हटाओ,
	.driver	= अणु
		.name = "mali-dp",
		.pm = &malidp_pm_ops,
		.of_match_table	= malidp_drm_of_match,
		.dev_groups = mali_dp_groups,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(malidp_platक्रमm_driver);

MODULE_AUTHOR("Liviu Dudau <Liviu.Dudau@arm.com>");
MODULE_DESCRIPTION("ARM Mali DP DRM driver");
MODULE_LICENSE("GPL v2");
