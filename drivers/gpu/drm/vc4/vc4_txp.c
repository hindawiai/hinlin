<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright तऊ 2018 Broadcom
 *
 * Authors:
 *	Eric Anholt <eric@anholt.net>
 *	Boris Brezillon <boris.brezillon@bootlin.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/component.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/pm_runसमय.स>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_edid.h>
#समावेश <drm/drm_fb_cma_helper.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_panel.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_vblank.h>
#समावेश <drm/drm_ग_लिखोback.h>

#समावेश "vc4_drv.h"
#समावेश "vc4_regs.h"

/* Base address of the output.  Raster क्रमmats must be 4-byte aligned,
 * T and LT must be 16-byte aligned or maybe utile-aligned (करोcs are
 * inconsistent, but probably utile).
 */
#घोषणा TXP_DST_PTR		0x00

/* Pitch in bytes क्रम raster images, 16-byte aligned.  For tiled, it's
 * the width in tiles.
 */
#घोषणा TXP_DST_PITCH		0x04
/* For T-tiled imgaes, DST_PITCH should be the number of tiles wide,
 * shअगरted up.
 */
# define TXP_T_TILE_WIDTH_SHIFT		7
/* For LT-tiled images, DST_PITCH should be the number of utiles wide,
 * shअगरted up.
 */
# define TXP_LT_TILE_WIDTH_SHIFT	4

/* Pre-rotation width/height of the image.  Must match HVS config.
 *
 * If TFORMAT and 32-bit, limit is 1920 क्रम 32-bit and 3840 to 16-bit
 * and width/height must be tile or utile-aligned as appropriate.  If
 * transposing (rotating), width is limited to 1920.
 *
 * Height is limited to various numbers between 4088 and 4095.  I'd
 * just use 4088 to be safe.
 */
#घोषणा TXP_DIM			0x08
# define TXP_HEIGHT_SHIFT		16
# define TXP_HEIGHT_MASK		GENMASK(31, 16)
# define TXP_WIDTH_SHIFT		0
# define TXP_WIDTH_MASK			GENMASK(15, 0)

#घोषणा TXP_DST_CTRL		0x0c
/* These bits are set to 0x54 */
#घोषणा TXP_PILOT_SHIFT			24
#घोषणा TXP_PILOT_MASK			GENMASK(31, 24)
/* Bits 22-23 are set to 0x01 */
#घोषणा TXP_VERSION_SHIFT		22
#घोषणा TXP_VERSION_MASK		GENMASK(23, 22)

/* Powers करोwn the पूर्णांकernal memory. */
# define TXP_POWERDOWN			BIT(21)

/* Enables storing the alpha component in 8888/4444, instead of
 * filling with ~ALPHA_INVERT.
 */
# define TXP_ALPHA_ENABLE		BIT(20)

/* 4 bits, each enables stores क्रम a channel in each set of 4 bytes.
 * Set to 0xf क्रम normal operation.
 */
# define TXP_BYTE_ENABLE_SHIFT		16
# define TXP_BYTE_ENABLE_MASK		GENMASK(19, 16)

/* Debug: Generate VSTART again at खातापूर्ण. */
# define TXP_VSTART_AT_खातापूर्ण		BIT(15)

/* Debug: Terminate the current frame immediately.  Stops AXI
 * ग_लिखोs.
 */
# define TXP_ABORT			BIT(14)

# define TXP_DITHER			BIT(13)

/* Inverts alpha अगर TXP_ALPHA_ENABLE, chooses fill value क्रम
 * !TXP_ALPHA_ENABLE.
 */
# define TXP_ALPHA_INVERT		BIT(12)

/* Note: I've listed the channels here in high bit (in byte 3/2/1) to
 * low bit (in byte 0) order.
 */
# define TXP_FORMAT_SHIFT		8
# define TXP_FORMAT_MASK		GENMASK(11, 8)
# define TXP_FORMAT_ABGR4444		0
# define TXP_FORMAT_ARGB4444		1
# define TXP_FORMAT_BGRA4444		2
# define TXP_FORMAT_RGBA4444		3
# define TXP_FORMAT_BGR565		6
# define TXP_FORMAT_RGB565		7
/* 888s are non-rotated, raster-only */
# define TXP_FORMAT_BGR888		8
# define TXP_FORMAT_RGB888		9
# define TXP_FORMAT_ABGR8888		12
# define TXP_FORMAT_ARGB8888		13
# define TXP_FORMAT_BGRA8888		14
# define TXP_FORMAT_RGBA8888		15

/* If TFORMAT is set, generates LT instead of T क्रमmat. */
# define TXP_LINEAR_UTILE		BIT(7)

/* Rotate output by 90 degrees. */
# define TXP_TRANSPOSE			BIT(6)

/* Generate a tiled क्रमmat क्रम V3D. */
# define TXP_TFORMAT			BIT(5)

/* Generates some undefined test mode output. */
# define TXP_TEST_MODE			BIT(4)

/* Request odd field from HVS. */
# define TXP_FIELD			BIT(3)

/* Raise पूर्णांकerrupt when idle. */
# define TXP_EI				BIT(2)

/* Set when generating a frame, clears when idle. */
# define TXP_BUSY			BIT(1)

/* Starts a frame.  Self-clearing. */
# define TXP_GO				BIT(0)

/* Number of lines received and committed to memory. */
#घोषणा TXP_PROGRESS		0x10

#घोषणा TXP_READ(offset) पढ़ोl(txp->regs + (offset))
#घोषणा TXP_WRITE(offset, val) ग_लिखोl(val, txp->regs + (offset))

काष्ठा vc4_txp अणु
	काष्ठा vc4_crtc	base;

	काष्ठा platक्रमm_device *pdev;

	काष्ठा drm_ग_लिखोback_connector connector;

	व्योम __iomem *regs;
	काष्ठा debugfs_regset32 regset;
पूर्ण;

अटल अंतरभूत काष्ठा vc4_txp *encoder_to_vc4_txp(काष्ठा drm_encoder *encoder)
अणु
	वापस container_of(encoder, काष्ठा vc4_txp, connector.encoder);
पूर्ण

अटल अंतरभूत काष्ठा vc4_txp *connector_to_vc4_txp(काष्ठा drm_connector *conn)
अणु
	वापस container_of(conn, काष्ठा vc4_txp, connector.base);
पूर्ण

अटल स्थिर काष्ठा debugfs_reg32 txp_regs[] = अणु
	VC4_REG32(TXP_DST_PTR),
	VC4_REG32(TXP_DST_PITCH),
	VC4_REG32(TXP_DIM),
	VC4_REG32(TXP_DST_CTRL),
	VC4_REG32(TXP_PROGRESS),
पूर्ण;

अटल पूर्णांक vc4_txp_connector_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_device *dev = connector->dev;

	वापस drm_add_modes_noedid(connector, dev->mode_config.max_width,
				    dev->mode_config.max_height);
पूर्ण

अटल क्रमागत drm_mode_status
vc4_txp_connector_mode_valid(काष्ठा drm_connector *connector,
			     काष्ठा drm_display_mode *mode)
अणु
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा drm_mode_config *mode_config = &dev->mode_config;
	पूर्णांक w = mode->hdisplay, h = mode->vdisplay;

	अगर (w < mode_config->min_width || w > mode_config->max_width)
		वापस MODE_BAD_HVALUE;

	अगर (h < mode_config->min_height || h > mode_config->max_height)
		वापस MODE_BAD_VVALUE;

	वापस MODE_OK;
पूर्ण

अटल स्थिर u32 drm_fmts[] = अणु
	DRM_FORMAT_RGB888,
	DRM_FORMAT_BGR888,
	DRM_FORMAT_XRGB8888,
	DRM_FORMAT_XBGR8888,
	DRM_FORMAT_ARGB8888,
	DRM_FORMAT_ABGR8888,
	DRM_FORMAT_RGBX8888,
	DRM_FORMAT_BGRX8888,
	DRM_FORMAT_RGBA8888,
	DRM_FORMAT_BGRA8888,
पूर्ण;

अटल स्थिर u32 txp_fmts[] = अणु
	TXP_FORMAT_RGB888,
	TXP_FORMAT_BGR888,
	TXP_FORMAT_ARGB8888,
	TXP_FORMAT_ABGR8888,
	TXP_FORMAT_ARGB8888,
	TXP_FORMAT_ABGR8888,
	TXP_FORMAT_RGBA8888,
	TXP_FORMAT_BGRA8888,
	TXP_FORMAT_RGBA8888,
	TXP_FORMAT_BGRA8888,
पूर्ण;

अटल व्योम vc4_txp_armed(काष्ठा drm_crtc_state *state)
अणु
	काष्ठा vc4_crtc_state *vc4_state = to_vc4_crtc_state(state);

	vc4_state->txp_armed = true;
पूर्ण

अटल पूर्णांक vc4_txp_connector_atomic_check(काष्ठा drm_connector *conn,
					  काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_connector_state *conn_state;
	काष्ठा drm_crtc_state *crtc_state;
	काष्ठा drm_framebuffer *fb;
	पूर्णांक i;

	conn_state = drm_atomic_get_new_connector_state(state, conn);
	अगर (!conn_state->ग_लिखोback_job)
		वापस 0;

	crtc_state = drm_atomic_get_new_crtc_state(state, conn_state->crtc);

	fb = conn_state->ग_लिखोback_job->fb;
	अगर (fb->width != crtc_state->mode.hdisplay ||
	    fb->height != crtc_state->mode.vdisplay) अणु
		DRM_DEBUG_KMS("Invalid framebuffer size %ux%u\n",
			      fb->width, fb->height);
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(drm_fmts); i++) अणु
		अगर (fb->क्रमmat->क्रमmat == drm_fmts[i])
			अवरोध;
	पूर्ण

	अगर (i == ARRAY_SIZE(drm_fmts))
		वापस -EINVAL;

	/* Pitch must be aligned on 16 bytes. */
	अगर (fb->pitches[0] & GENMASK(3, 0))
		वापस -EINVAL;

	vc4_txp_armed(crtc_state);

	वापस 0;
पूर्ण

अटल व्योम vc4_txp_connector_atomic_commit(काष्ठा drm_connector *conn,
					काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_connector_state *conn_state = drm_atomic_get_new_connector_state(state,
										    conn);
	काष्ठा vc4_txp *txp = connector_to_vc4_txp(conn);
	काष्ठा drm_gem_cma_object *gem;
	काष्ठा drm_display_mode *mode;
	काष्ठा drm_framebuffer *fb;
	u32 ctrl;
	पूर्णांक i;

	अगर (WARN_ON(!conn_state->ग_लिखोback_job))
		वापस;

	mode = &conn_state->crtc->state->adjusted_mode;
	fb = conn_state->ग_लिखोback_job->fb;

	क्रम (i = 0; i < ARRAY_SIZE(drm_fmts); i++) अणु
		अगर (fb->क्रमmat->क्रमmat == drm_fmts[i])
			अवरोध;
	पूर्ण

	अगर (WARN_ON(i == ARRAY_SIZE(drm_fmts)))
		वापस;

	ctrl = TXP_GO | TXP_VSTART_AT_खातापूर्ण | TXP_EI |
	       VC4_SET_FIELD(0xf, TXP_BYTE_ENABLE) |
	       VC4_SET_FIELD(txp_fmts[i], TXP_FORMAT);

	अगर (fb->क्रमmat->has_alpha)
		ctrl |= TXP_ALPHA_ENABLE;

	gem = drm_fb_cma_get_gem_obj(fb, 0);
	TXP_WRITE(TXP_DST_PTR, gem->paddr + fb->offsets[0]);
	TXP_WRITE(TXP_DST_PITCH, fb->pitches[0]);
	TXP_WRITE(TXP_DIM,
		  VC4_SET_FIELD(mode->hdisplay, TXP_WIDTH) |
		  VC4_SET_FIELD(mode->vdisplay, TXP_HEIGHT));

	TXP_WRITE(TXP_DST_CTRL, ctrl);

	drm_ग_लिखोback_queue_job(&txp->connector, conn_state);
पूर्ण

अटल स्थिर काष्ठा drm_connector_helper_funcs vc4_txp_connector_helper_funcs = अणु
	.get_modes = vc4_txp_connector_get_modes,
	.mode_valid = vc4_txp_connector_mode_valid,
	.atomic_check = vc4_txp_connector_atomic_check,
	.atomic_commit = vc4_txp_connector_atomic_commit,
पूर्ण;

अटल क्रमागत drm_connector_status
vc4_txp_connector_detect(काष्ठा drm_connector *connector, bool क्रमce)
अणु
	वापस connector_status_connected;
पूर्ण

अटल व्योम vc4_txp_connector_destroy(काष्ठा drm_connector *connector)
अणु
	drm_connector_unरेजिस्टर(connector);
	drm_connector_cleanup(connector);
पूर्ण

अटल स्थिर काष्ठा drm_connector_funcs vc4_txp_connector_funcs = अणु
	.detect = vc4_txp_connector_detect,
	.fill_modes = drm_helper_probe_single_connector_modes,
	.destroy = vc4_txp_connector_destroy,
	.reset = drm_atomic_helper_connector_reset,
	.atomic_duplicate_state = drm_atomic_helper_connector_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_connector_destroy_state,
पूर्ण;

अटल व्योम vc4_txp_encoder_disable(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा vc4_txp *txp = encoder_to_vc4_txp(encoder);

	अगर (TXP_READ(TXP_DST_CTRL) & TXP_BUSY) अणु
		अचिन्हित दीर्घ समयout = jअगरfies + msecs_to_jअगरfies(1000);

		TXP_WRITE(TXP_DST_CTRL, TXP_ABORT);

		जबतक (TXP_READ(TXP_DST_CTRL) & TXP_BUSY &&
		       समय_beक्रमe(jअगरfies, समयout))
			;

		WARN_ON(TXP_READ(TXP_DST_CTRL) & TXP_BUSY);
	पूर्ण

	TXP_WRITE(TXP_DST_CTRL, TXP_POWERDOWN);
पूर्ण

अटल स्थिर काष्ठा drm_encoder_helper_funcs vc4_txp_encoder_helper_funcs = अणु
	.disable = vc4_txp_encoder_disable,
पूर्ण;

अटल पूर्णांक vc4_txp_enable_vblank(काष्ठा drm_crtc *crtc)
अणु
	वापस 0;
पूर्ण

अटल व्योम vc4_txp_disable_vblank(काष्ठा drm_crtc *crtc) अणुपूर्ण

अटल स्थिर काष्ठा drm_crtc_funcs vc4_txp_crtc_funcs = अणु
	.set_config		= drm_atomic_helper_set_config,
	.destroy		= vc4_crtc_destroy,
	.page_flip		= vc4_page_flip,
	.reset			= vc4_crtc_reset,
	.atomic_duplicate_state	= vc4_crtc_duplicate_state,
	.atomic_destroy_state	= vc4_crtc_destroy_state,
	.enable_vblank		= vc4_txp_enable_vblank,
	.disable_vblank		= vc4_txp_disable_vblank,
पूर्ण;

अटल पूर्णांक vc4_txp_atomic_check(काष्ठा drm_crtc *crtc,
				काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_crtc_state *crtc_state = drm_atomic_get_new_crtc_state(state,
									  crtc);
	काष्ठा vc4_crtc_state *vc4_state = to_vc4_crtc_state(crtc_state);
	पूर्णांक ret;

	ret = vc4_hvs_atomic_check(crtc, state);
	अगर (ret)
		वापस ret;

	crtc_state->no_vblank = true;
	vc4_state->feed_txp = true;

	वापस 0;
पूर्ण

अटल व्योम vc4_txp_atomic_enable(काष्ठा drm_crtc *crtc,
				  काष्ठा drm_atomic_state *state)
अणु
	drm_crtc_vblank_on(crtc);
	vc4_hvs_atomic_enable(crtc, state);
पूर्ण

अटल व्योम vc4_txp_atomic_disable(काष्ठा drm_crtc *crtc,
				   काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_device *dev = crtc->dev;

	/* Disable vblank irq handling beक्रमe crtc is disabled. */
	drm_crtc_vblank_off(crtc);

	vc4_hvs_atomic_disable(crtc, state);

	/*
	 * Make sure we issue a vblank event after disabling the CRTC अगर
	 * someone was रुकोing it.
	 */
	अगर (crtc->state->event) अणु
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&dev->event_lock, flags);
		drm_crtc_send_vblank_event(crtc, crtc->state->event);
		crtc->state->event = शून्य;
		spin_unlock_irqrestore(&dev->event_lock, flags);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा drm_crtc_helper_funcs vc4_txp_crtc_helper_funcs = अणु
	.atomic_check	= vc4_txp_atomic_check,
	.atomic_flush	= vc4_hvs_atomic_flush,
	.atomic_enable	= vc4_txp_atomic_enable,
	.atomic_disable	= vc4_txp_atomic_disable,
पूर्ण;

अटल irqवापस_t vc4_txp_पूर्णांकerrupt(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा vc4_txp *txp = data;
	काष्ठा vc4_crtc *vc4_crtc = &txp->base;

	TXP_WRITE(TXP_DST_CTRL, TXP_READ(TXP_DST_CTRL) & ~TXP_EI);
	vc4_crtc_handle_vblank(vc4_crtc);
	drm_ग_लिखोback_संकेत_completion(&txp->connector, 0);

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा vc4_crtc_data vc4_txp_crtc_data = अणु
	.hvs_available_channels = BIT(2),
	.hvs_output = 2,
पूर्ण;

अटल पूर्णांक vc4_txp_bind(काष्ठा device *dev, काष्ठा device *master, व्योम *data)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा drm_device *drm = dev_get_drvdata(master);
	काष्ठा vc4_dev *vc4 = to_vc4_dev(drm);
	काष्ठा vc4_crtc *vc4_crtc;
	काष्ठा vc4_txp *txp;
	काष्ठा drm_crtc *crtc;
	काष्ठा drm_encoder *encoder;
	पूर्णांक ret, irq;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	txp = devm_kzalloc(dev, माप(*txp), GFP_KERNEL);
	अगर (!txp)
		वापस -ENOMEM;
	vc4_crtc = &txp->base;
	crtc = &vc4_crtc->base;

	vc4_crtc->pdev = pdev;
	vc4_crtc->data = &vc4_txp_crtc_data;

	txp->pdev = pdev;

	txp->regs = vc4_ioremap_regs(pdev, 0);
	अगर (IS_ERR(txp->regs))
		वापस PTR_ERR(txp->regs);
	txp->regset.base = txp->regs;
	txp->regset.regs = txp_regs;
	txp->regset.nregs = ARRAY_SIZE(txp_regs);

	drm_connector_helper_add(&txp->connector.base,
				 &vc4_txp_connector_helper_funcs);
	ret = drm_ग_लिखोback_connector_init(drm, &txp->connector,
					   &vc4_txp_connector_funcs,
					   &vc4_txp_encoder_helper_funcs,
					   drm_fmts, ARRAY_SIZE(drm_fmts));
	अगर (ret)
		वापस ret;

	ret = vc4_crtc_init(drm, vc4_crtc,
			    &vc4_txp_crtc_funcs, &vc4_txp_crtc_helper_funcs);
	अगर (ret)
		वापस ret;

	encoder = &txp->connector.encoder;
	encoder->possible_crtcs |= drm_crtc_mask(crtc);

	ret = devm_request_irq(dev, irq, vc4_txp_पूर्णांकerrupt, 0,
			       dev_name(dev), txp);
	अगर (ret)
		वापस ret;

	dev_set_drvdata(dev, txp);
	vc4->txp = txp;

	vc4_debugfs_add_regset32(drm, "txp_regs", &txp->regset);

	वापस 0;
पूर्ण

अटल व्योम vc4_txp_unbind(काष्ठा device *dev, काष्ठा device *master,
			   व्योम *data)
अणु
	काष्ठा drm_device *drm = dev_get_drvdata(master);
	काष्ठा vc4_dev *vc4 = to_vc4_dev(drm);
	काष्ठा vc4_txp *txp = dev_get_drvdata(dev);

	vc4_txp_connector_destroy(&txp->connector.base);

	vc4->txp = शून्य;
पूर्ण

अटल स्थिर काष्ठा component_ops vc4_txp_ops = अणु
	.bind   = vc4_txp_bind,
	.unbind = vc4_txp_unbind,
पूर्ण;

अटल पूर्णांक vc4_txp_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस component_add(&pdev->dev, &vc4_txp_ops);
पूर्ण

अटल पूर्णांक vc4_txp_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	component_del(&pdev->dev, &vc4_txp_ops);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id vc4_txp_dt_match[] = अणु
	अणु .compatible = "brcm,bcm2835-txp" पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;

काष्ठा platक्रमm_driver vc4_txp_driver = अणु
	.probe = vc4_txp_probe,
	.हटाओ = vc4_txp_हटाओ,
	.driver = अणु
		.name = "vc4_txp",
		.of_match_table = vc4_txp_dt_match,
	पूर्ण,
पूर्ण;
