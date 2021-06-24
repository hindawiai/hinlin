<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2017 Icenowy Zheng <icenowy@aosc.io>
 */

#अगर_अघोषित _SUNXI_ENGINE_H_
#घोषणा _SUNXI_ENGINE_H_

काष्ठा drm_plane;
काष्ठा drm_device;
काष्ठा drm_crtc_state;

काष्ठा sunxi_engine;

/**
 * काष्ठा sunxi_engine_ops - helper operations क्रम sunXi engines
 *
 * These hooks are used by the common part of the DRM driver to
 * implement the proper behaviour.
 */
काष्ठा sunxi_engine_ops अणु
	/**
	 * @atomic_begin:
	 *
	 * This callback allows to prepare our engine क्रम an atomic
	 * update. This is mirroring the
	 * &drm_crtc_helper_funcs.atomic_begin callback, so any
	 * करोcumentation there applies.
	 *
	 * This function is optional.
	 */
	व्योम (*atomic_begin)(काष्ठा sunxi_engine *engine,
			     काष्ठा drm_crtc_state *old_state);

	/**
	 * @atomic_check:
	 *
	 * This callback allows to validate plane-update related CRTC
	 * स्थिरraपूर्णांकs specअगरic to engines. This is mirroring the
	 * &drm_crtc_helper_funcs.atomic_check callback, so any
	 * करोcumentation there applies.
	 *
	 * This function is optional.
	 *
	 * RETURNS:
	 *
	 * 0 on success or a negative error code.
	 */
	पूर्णांक (*atomic_check)(काष्ठा sunxi_engine *engine,
			    काष्ठा drm_crtc_state *state);

	/**
	 * @commit:
	 *
	 * This callback will trigger the hardware चयन to commit
	 * the new configuration that has been setup during the next
	 * vblank period.
	 *
	 * This function is optional.
	 */
	व्योम (*commit)(काष्ठा sunxi_engine *engine);

	/**
	 * @layers_init:
	 *
	 * This callback is used to allocate, initialize and रेजिस्टर
	 * the layers supported by that engine.
	 *
	 * This function is mandatory.
	 *
	 * RETURNS:
	 *
	 * The array of काष्ठा drm_plane backing the layers, or an
	 * error poपूर्णांकer on failure.
	 */
	काष्ठा drm_plane **(*layers_init)(काष्ठा drm_device *drm,
					  काष्ठा sunxi_engine *engine);

	/**
	 * @apply_color_correction:
	 *
	 * This callback will enable the color correction in the
	 * engine. This is useful only क्रम the composite output.
	 *
	 * This function is optional.
	 */
	व्योम (*apply_color_correction)(काष्ठा sunxi_engine *engine);

	/**
	 * @disable_color_correction:
	 *
	 * This callback will stop the color correction in the
	 * engine. This is useful only क्रम the composite output.
	 *
	 * This function is optional.
	 */
	व्योम (*disable_color_correction)(काष्ठा sunxi_engine *engine);

	/**
	 * @vblank_quirk:
	 *
	 * This callback is used to implement engine-specअगरic
	 * behaviour part of the VBLANK event. It is run with all the
	 * स्थिरraपूर्णांकs of an पूर्णांकerrupt (can't sleep, all local
	 * पूर्णांकerrupts disabled) and thereक्रमe should be as fast as
	 * possible.
	 *
	 * This function is optional.
	 */
	व्योम (*vblank_quirk)(काष्ठा sunxi_engine *engine);
पूर्ण;

/**
 * काष्ठा sunxi_engine - the common parts of an engine क्रम sun4i-drm driver
 * @ops:	the operations of the engine
 * @node:	the of device node of the engine
 * @regs:	the regmap of the engine
 * @id:		the id of the engine (-1 अगर not used)
 */
काष्ठा sunxi_engine अणु
	स्थिर काष्ठा sunxi_engine_ops	*ops;

	काष्ठा device_node		*node;
	काष्ठा regmap			*regs;

	पूर्णांक id;

	/* Engine list management */
	काष्ठा list_head		list;
पूर्ण;

/**
 * sunxi_engine_commit() - commit all changes of the engine
 * @engine:	poपूर्णांकer to the engine
 */
अटल अंतरभूत व्योम
sunxi_engine_commit(काष्ठा sunxi_engine *engine)
अणु
	अगर (engine->ops && engine->ops->commit)
		engine->ops->commit(engine);
पूर्ण

/**
 * sunxi_engine_layers_init() - Create planes (layers) क्रम the engine
 * @drm:	poपूर्णांकer to the drm_device क्रम which planes will be created
 * @engine:	poपूर्णांकer to the engine
 */
अटल अंतरभूत काष्ठा drm_plane **
sunxi_engine_layers_init(काष्ठा drm_device *drm, काष्ठा sunxi_engine *engine)
अणु
	अगर (engine->ops && engine->ops->layers_init)
		वापस engine->ops->layers_init(drm, engine);
	वापस ERR_PTR(-ENOSYS);
पूर्ण

/**
 * sunxi_engine_apply_color_correction - Apply the RGB2YUV color correction
 * @engine:	poपूर्णांकer to the engine
 *
 * This functionality is optional क्रम an engine, however, अगर the engine is
 * पूर्णांकended to be used with TV Encoder, the output will be incorrect
 * without the color correction, due to TV Encoder expects the engine to
 * output directly YUV संकेत.
 */
अटल अंतरभूत व्योम
sunxi_engine_apply_color_correction(काष्ठा sunxi_engine *engine)
अणु
	अगर (engine->ops && engine->ops->apply_color_correction)
		engine->ops->apply_color_correction(engine);
पूर्ण

/**
 * sunxi_engine_disable_color_correction - Disable the color space correction
 * @engine:	poपूर्णांकer to the engine
 *
 * This function is paired with apply_color_correction().
 */
अटल अंतरभूत व्योम
sunxi_engine_disable_color_correction(काष्ठा sunxi_engine *engine)
अणु
	अगर (engine->ops && engine->ops->disable_color_correction)
		engine->ops->disable_color_correction(engine);
पूर्ण
#पूर्ण_अगर /* _SUNXI_ENGINE_H_ */
