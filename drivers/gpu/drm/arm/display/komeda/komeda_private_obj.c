<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * (C) COPYRIGHT 2018 ARM Limited. All rights reserved.
 * Author: James.Qian.Wang <james.qian.wang@arm.com>
 *
 */
#समावेश "komeda_dev.h"
#समावेश "komeda_kms.h"

अटल व्योम
komeda_component_state_reset(काष्ठा komeda_component_state *st)
अणु
	st->binding_user = शून्य;
	st->affected_inमाला_दो = st->active_inमाला_दो;
	st->active_inमाला_दो = 0;
	st->changed_active_inमाला_दो = 0;
पूर्ण

अटल काष्ठा drm_निजी_state *
komeda_layer_atomic_duplicate_state(काष्ठा drm_निजी_obj *obj)
अणु
	काष्ठा komeda_layer_state *st;

	st = kmemdup(obj->state, माप(*st), GFP_KERNEL);
	अगर (!st)
		वापस शून्य;

	komeda_component_state_reset(&st->base);
	__drm_atomic_helper_निजी_obj_duplicate_state(obj, &st->base.obj);

	वापस &st->base.obj;
पूर्ण

अटल व्योम
komeda_layer_atomic_destroy_state(काष्ठा drm_निजी_obj *obj,
				  काष्ठा drm_निजी_state *state)
अणु
	काष्ठा komeda_layer_state *st = to_layer_st(priv_to_comp_st(state));

	kमुक्त(st);
पूर्ण

अटल स्थिर काष्ठा drm_निजी_state_funcs komeda_layer_obj_funcs = अणु
	.atomic_duplicate_state	= komeda_layer_atomic_duplicate_state,
	.atomic_destroy_state	= komeda_layer_atomic_destroy_state,
पूर्ण;

अटल पूर्णांक komeda_layer_obj_add(काष्ठा komeda_kms_dev *kms,
				काष्ठा komeda_layer *layer)
अणु
	काष्ठा komeda_layer_state *st;

	st = kzalloc(माप(*st), GFP_KERNEL);
	अगर (!st)
		वापस -ENOMEM;

	st->base.component = &layer->base;
	drm_atomic_निजी_obj_init(&kms->base, &layer->base.obj, &st->base.obj,
				    &komeda_layer_obj_funcs);
	वापस 0;
पूर्ण

अटल काष्ठा drm_निजी_state *
komeda_scaler_atomic_duplicate_state(काष्ठा drm_निजी_obj *obj)
अणु
	काष्ठा komeda_scaler_state *st;

	st = kmemdup(obj->state, माप(*st), GFP_KERNEL);
	अगर (!st)
		वापस शून्य;

	komeda_component_state_reset(&st->base);
	__drm_atomic_helper_निजी_obj_duplicate_state(obj, &st->base.obj);

	वापस &st->base.obj;
पूर्ण

अटल व्योम
komeda_scaler_atomic_destroy_state(काष्ठा drm_निजी_obj *obj,
				   काष्ठा drm_निजी_state *state)
अणु
	kमुक्त(to_scaler_st(priv_to_comp_st(state)));
पूर्ण

अटल स्थिर काष्ठा drm_निजी_state_funcs komeda_scaler_obj_funcs = अणु
	.atomic_duplicate_state	= komeda_scaler_atomic_duplicate_state,
	.atomic_destroy_state	= komeda_scaler_atomic_destroy_state,
पूर्ण;

अटल पूर्णांक komeda_scaler_obj_add(काष्ठा komeda_kms_dev *kms,
				 काष्ठा komeda_scaler *scaler)
अणु
	काष्ठा komeda_scaler_state *st;

	st = kzalloc(माप(*st), GFP_KERNEL);
	अगर (!st)
		वापस -ENOMEM;

	st->base.component = &scaler->base;
	drm_atomic_निजी_obj_init(&kms->base,
				    &scaler->base.obj, &st->base.obj,
				    &komeda_scaler_obj_funcs);
	वापस 0;
पूर्ण

अटल काष्ठा drm_निजी_state *
komeda_compiz_atomic_duplicate_state(काष्ठा drm_निजी_obj *obj)
अणु
	काष्ठा komeda_compiz_state *st;

	st = kmemdup(obj->state, माप(*st), GFP_KERNEL);
	अगर (!st)
		वापस शून्य;

	komeda_component_state_reset(&st->base);
	__drm_atomic_helper_निजी_obj_duplicate_state(obj, &st->base.obj);

	वापस &st->base.obj;
पूर्ण

अटल व्योम
komeda_compiz_atomic_destroy_state(काष्ठा drm_निजी_obj *obj,
				   काष्ठा drm_निजी_state *state)
अणु
	kमुक्त(to_compiz_st(priv_to_comp_st(state)));
पूर्ण

अटल स्थिर काष्ठा drm_निजी_state_funcs komeda_compiz_obj_funcs = अणु
	.atomic_duplicate_state	= komeda_compiz_atomic_duplicate_state,
	.atomic_destroy_state	= komeda_compiz_atomic_destroy_state,
पूर्ण;

अटल पूर्णांक komeda_compiz_obj_add(काष्ठा komeda_kms_dev *kms,
				 काष्ठा komeda_compiz *compiz)
अणु
	काष्ठा komeda_compiz_state *st;

	st = kzalloc(माप(*st), GFP_KERNEL);
	अगर (!st)
		वापस -ENOMEM;

	st->base.component = &compiz->base;
	drm_atomic_निजी_obj_init(&kms->base, &compiz->base.obj, &st->base.obj,
				    &komeda_compiz_obj_funcs);

	वापस 0;
पूर्ण

अटल काष्ठा drm_निजी_state *
komeda_splitter_atomic_duplicate_state(काष्ठा drm_निजी_obj *obj)
अणु
	काष्ठा komeda_splitter_state *st;

	st = kmemdup(obj->state, माप(*st), GFP_KERNEL);
	अगर (!st)
		वापस शून्य;

	komeda_component_state_reset(&st->base);
	__drm_atomic_helper_निजी_obj_duplicate_state(obj, &st->base.obj);

	वापस &st->base.obj;
पूर्ण

अटल व्योम
komeda_splitter_atomic_destroy_state(काष्ठा drm_निजी_obj *obj,
				     काष्ठा drm_निजी_state *state)
अणु
	kमुक्त(to_splitter_st(priv_to_comp_st(state)));
पूर्ण

अटल स्थिर काष्ठा drm_निजी_state_funcs komeda_splitter_obj_funcs = अणु
	.atomic_duplicate_state	= komeda_splitter_atomic_duplicate_state,
	.atomic_destroy_state	= komeda_splitter_atomic_destroy_state,
पूर्ण;

अटल पूर्णांक komeda_splitter_obj_add(काष्ठा komeda_kms_dev *kms,
				   काष्ठा komeda_splitter *splitter)
अणु
	काष्ठा komeda_splitter_state *st;

	st = kzalloc(माप(*st), GFP_KERNEL);
	अगर (!st)
		वापस -ENOMEM;

	st->base.component = &splitter->base;
	drm_atomic_निजी_obj_init(&kms->base,
				    &splitter->base.obj, &st->base.obj,
				    &komeda_splitter_obj_funcs);

	वापस 0;
पूर्ण

अटल काष्ठा drm_निजी_state *
komeda_merger_atomic_duplicate_state(काष्ठा drm_निजी_obj *obj)
अणु
	काष्ठा komeda_merger_state *st;

	st = kmemdup(obj->state, माप(*st), GFP_KERNEL);
	अगर (!st)
		वापस शून्य;

	komeda_component_state_reset(&st->base);
	__drm_atomic_helper_निजी_obj_duplicate_state(obj, &st->base.obj);

	वापस &st->base.obj;
पूर्ण

अटल व्योम komeda_merger_atomic_destroy_state(काष्ठा drm_निजी_obj *obj,
					       काष्ठा drm_निजी_state *state)
अणु
	kमुक्त(to_merger_st(priv_to_comp_st(state)));
पूर्ण

अटल स्थिर काष्ठा drm_निजी_state_funcs komeda_merger_obj_funcs = अणु
	.atomic_duplicate_state	= komeda_merger_atomic_duplicate_state,
	.atomic_destroy_state	= komeda_merger_atomic_destroy_state,
पूर्ण;

अटल पूर्णांक komeda_merger_obj_add(काष्ठा komeda_kms_dev *kms,
				 काष्ठा komeda_merger *merger)
अणु
	काष्ठा komeda_merger_state *st;

	st = kzalloc(माप(*st), GFP_KERNEL);
	अगर (!st)
		वापस -ENOMEM;

	st->base.component = &merger->base;
	drm_atomic_निजी_obj_init(&kms->base,
				    &merger->base.obj, &st->base.obj,
				    &komeda_merger_obj_funcs);

	वापस 0;
पूर्ण

अटल काष्ठा drm_निजी_state *
komeda_improc_atomic_duplicate_state(काष्ठा drm_निजी_obj *obj)
अणु
	काष्ठा komeda_improc_state *st;

	st = kmemdup(obj->state, माप(*st), GFP_KERNEL);
	अगर (!st)
		वापस शून्य;

	komeda_component_state_reset(&st->base);
	__drm_atomic_helper_निजी_obj_duplicate_state(obj, &st->base.obj);

	वापस &st->base.obj;
पूर्ण

अटल व्योम
komeda_improc_atomic_destroy_state(काष्ठा drm_निजी_obj *obj,
				   काष्ठा drm_निजी_state *state)
अणु
	kमुक्त(to_improc_st(priv_to_comp_st(state)));
पूर्ण

अटल स्थिर काष्ठा drm_निजी_state_funcs komeda_improc_obj_funcs = अणु
	.atomic_duplicate_state	= komeda_improc_atomic_duplicate_state,
	.atomic_destroy_state	= komeda_improc_atomic_destroy_state,
पूर्ण;

अटल पूर्णांक komeda_improc_obj_add(काष्ठा komeda_kms_dev *kms,
				 काष्ठा komeda_improc *improc)
अणु
	काष्ठा komeda_improc_state *st;

	st = kzalloc(माप(*st), GFP_KERNEL);
	अगर (!st)
		वापस -ENOMEM;

	st->base.component = &improc->base;
	drm_atomic_निजी_obj_init(&kms->base, &improc->base.obj, &st->base.obj,
				    &komeda_improc_obj_funcs);

	वापस 0;
पूर्ण

अटल काष्ठा drm_निजी_state *
komeda_timing_ctrlr_atomic_duplicate_state(काष्ठा drm_निजी_obj *obj)
अणु
	काष्ठा komeda_timing_ctrlr_state *st;

	st = kmemdup(obj->state, माप(*st), GFP_KERNEL);
	अगर (!st)
		वापस शून्य;

	komeda_component_state_reset(&st->base);
	__drm_atomic_helper_निजी_obj_duplicate_state(obj, &st->base.obj);

	वापस &st->base.obj;
पूर्ण

अटल व्योम
komeda_timing_ctrlr_atomic_destroy_state(काष्ठा drm_निजी_obj *obj,
					 काष्ठा drm_निजी_state *state)
अणु
	kमुक्त(to_ctrlr_st(priv_to_comp_st(state)));
पूर्ण

अटल स्थिर काष्ठा drm_निजी_state_funcs komeda_timing_ctrlr_obj_funcs = अणु
	.atomic_duplicate_state	= komeda_timing_ctrlr_atomic_duplicate_state,
	.atomic_destroy_state	= komeda_timing_ctrlr_atomic_destroy_state,
पूर्ण;

अटल पूर्णांक komeda_timing_ctrlr_obj_add(काष्ठा komeda_kms_dev *kms,
				       काष्ठा komeda_timing_ctrlr *ctrlr)
अणु
	काष्ठा komeda_compiz_state *st;

	st = kzalloc(माप(*st), GFP_KERNEL);
	अगर (!st)
		वापस -ENOMEM;

	st->base.component = &ctrlr->base;
	drm_atomic_निजी_obj_init(&kms->base, &ctrlr->base.obj, &st->base.obj,
				    &komeda_timing_ctrlr_obj_funcs);

	वापस 0;
पूर्ण

अटल काष्ठा drm_निजी_state *
komeda_pipeline_atomic_duplicate_state(काष्ठा drm_निजी_obj *obj)
अणु
	काष्ठा komeda_pipeline_state *st;

	st = kmemdup(obj->state, माप(*st), GFP_KERNEL);
	अगर (!st)
		वापस शून्य;

	st->active_comps = 0;

	__drm_atomic_helper_निजी_obj_duplicate_state(obj, &st->obj);

	वापस &st->obj;
पूर्ण

अटल व्योम
komeda_pipeline_atomic_destroy_state(काष्ठा drm_निजी_obj *obj,
				     काष्ठा drm_निजी_state *state)
अणु
	kमुक्त(priv_to_pipe_st(state));
पूर्ण

अटल स्थिर काष्ठा drm_निजी_state_funcs komeda_pipeline_obj_funcs = अणु
	.atomic_duplicate_state	= komeda_pipeline_atomic_duplicate_state,
	.atomic_destroy_state	= komeda_pipeline_atomic_destroy_state,
पूर्ण;

अटल पूर्णांक komeda_pipeline_obj_add(काष्ठा komeda_kms_dev *kms,
				   काष्ठा komeda_pipeline *pipe)
अणु
	काष्ठा komeda_pipeline_state *st;

	st = kzalloc(माप(*st), GFP_KERNEL);
	अगर (!st)
		वापस -ENOMEM;

	st->pipe = pipe;
	drm_atomic_निजी_obj_init(&kms->base, &pipe->obj, &st->obj,
				    &komeda_pipeline_obj_funcs);

	वापस 0;
पूर्ण

पूर्णांक komeda_kms_add_निजी_objs(काष्ठा komeda_kms_dev *kms,
				काष्ठा komeda_dev *mdev)
अणु
	काष्ठा komeda_pipeline *pipe;
	पूर्णांक i, j, err;

	क्रम (i = 0; i < mdev->n_pipelines; i++) अणु
		pipe = mdev->pipelines[i];

		err = komeda_pipeline_obj_add(kms, pipe);
		अगर (err)
			वापस err;

		क्रम (j = 0; j < pipe->n_layers; j++) अणु
			err = komeda_layer_obj_add(kms, pipe->layers[j]);
			अगर (err)
				वापस err;
		पूर्ण

		अगर (pipe->wb_layer) अणु
			err = komeda_layer_obj_add(kms, pipe->wb_layer);
			अगर (err)
				वापस err;
		पूर्ण

		क्रम (j = 0; j < pipe->n_scalers; j++) अणु
			err = komeda_scaler_obj_add(kms, pipe->scalers[j]);
			अगर (err)
				वापस err;
		पूर्ण

		err = komeda_compiz_obj_add(kms, pipe->compiz);
		अगर (err)
			वापस err;

		अगर (pipe->splitter) अणु
			err = komeda_splitter_obj_add(kms, pipe->splitter);
			अगर (err)
				वापस err;
		पूर्ण

		अगर (pipe->merger) अणु
			err = komeda_merger_obj_add(kms, pipe->merger);
			अगर (err)
				वापस err;
		पूर्ण

		err = komeda_improc_obj_add(kms, pipe->improc);
		अगर (err)
			वापस err;

		err = komeda_timing_ctrlr_obj_add(kms, pipe->ctrlr);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

व्योम komeda_kms_cleanup_निजी_objs(काष्ठा komeda_kms_dev *kms)
अणु
	काष्ठा drm_mode_config *config = &kms->base.mode_config;
	काष्ठा drm_निजी_obj *obj, *next;

	list_क्रम_each_entry_safe(obj, next, &config->privobj_list, head)
		drm_atomic_निजी_obj_fini(obj);
पूर्ण
