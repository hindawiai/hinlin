<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * (C) COPYRIGHT 2018 ARM Limited. All rights reserved.
 * Author: James.Qian.Wang <james.qian.wang@arm.com>
 *
 */
#समावेश <drm/drm_prपूर्णांक.h>

#समावेश "komeda_dev.h"
#समावेश "komeda_pipeline.h"

/** komeda_pipeline_add - Add a pipeline to &komeda_dev */
काष्ठा komeda_pipeline *
komeda_pipeline_add(काष्ठा komeda_dev *mdev, माप_प्रकार size,
		    स्थिर काष्ठा komeda_pipeline_funcs *funcs)
अणु
	काष्ठा komeda_pipeline *pipe;

	अगर (mdev->n_pipelines + 1 > KOMEDA_MAX_PIPELINES) अणु
		DRM_ERROR("Exceed max support %d pipelines.\n",
			  KOMEDA_MAX_PIPELINES);
		वापस ERR_PTR(-ENOSPC);
	पूर्ण

	अगर (size < माप(*pipe)) अणु
		DRM_ERROR("Request pipeline size too small.\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	pipe = devm_kzalloc(mdev->dev, size, GFP_KERNEL);
	अगर (!pipe)
		वापस ERR_PTR(-ENOMEM);

	pipe->mdev = mdev;
	pipe->id   = mdev->n_pipelines;
	pipe->funcs = funcs;

	mdev->pipelines[mdev->n_pipelines] = pipe;
	mdev->n_pipelines++;

	वापस pipe;
पूर्ण

व्योम komeda_pipeline_destroy(काष्ठा komeda_dev *mdev,
			     काष्ठा komeda_pipeline *pipe)
अणु
	काष्ठा komeda_component *c;
	पूर्णांक i;
	अचिन्हित दीर्घ avail_comps = pipe->avail_comps;

	क्रम_each_set_bit(i, &avail_comps, 32) अणु
		c = komeda_pipeline_get_component(pipe, i);
		komeda_component_destroy(mdev, c);
	पूर्ण

	clk_put(pipe->pxlclk);

	of_node_put(pipe->of_output_links[0]);
	of_node_put(pipe->of_output_links[1]);
	of_node_put(pipe->of_output_port);
	of_node_put(pipe->of_node);

	devm_kमुक्त(mdev->dev, pipe);
पूर्ण

अटल काष्ठा komeda_component **
komeda_pipeline_get_component_pos(काष्ठा komeda_pipeline *pipe, पूर्णांक id)
अणु
	काष्ठा komeda_dev *mdev = pipe->mdev;
	काष्ठा komeda_pipeline *temp = शून्य;
	काष्ठा komeda_component **pos = शून्य;

	चयन (id) अणु
	हाल KOMEDA_COMPONENT_LAYER0:
	हाल KOMEDA_COMPONENT_LAYER1:
	हाल KOMEDA_COMPONENT_LAYER2:
	हाल KOMEDA_COMPONENT_LAYER3:
		pos = to_cpos(pipe->layers[id - KOMEDA_COMPONENT_LAYER0]);
		अवरोध;
	हाल KOMEDA_COMPONENT_WB_LAYER:
		pos = to_cpos(pipe->wb_layer);
		अवरोध;
	हाल KOMEDA_COMPONENT_COMPIZ0:
	हाल KOMEDA_COMPONENT_COMPIZ1:
		temp = mdev->pipelines[id - KOMEDA_COMPONENT_COMPIZ0];
		अगर (!temp) अणु
			DRM_ERROR("compiz-%d doesn't exist.\n", id);
			वापस शून्य;
		पूर्ण
		pos = to_cpos(temp->compiz);
		अवरोध;
	हाल KOMEDA_COMPONENT_SCALER0:
	हाल KOMEDA_COMPONENT_SCALER1:
		pos = to_cpos(pipe->scalers[id - KOMEDA_COMPONENT_SCALER0]);
		अवरोध;
	हाल KOMEDA_COMPONENT_SPLITTER:
		pos = to_cpos(pipe->splitter);
		अवरोध;
	हाल KOMEDA_COMPONENT_MERGER:
		pos = to_cpos(pipe->merger);
		अवरोध;
	हाल KOMEDA_COMPONENT_IPS0:
	हाल KOMEDA_COMPONENT_IPS1:
		temp = mdev->pipelines[id - KOMEDA_COMPONENT_IPS0];
		अगर (!temp) अणु
			DRM_ERROR("ips-%d doesn't exist.\n", id);
			वापस शून्य;
		पूर्ण
		pos = to_cpos(temp->improc);
		अवरोध;
	हाल KOMEDA_COMPONENT_TIMING_CTRLR:
		pos = to_cpos(pipe->ctrlr);
		अवरोध;
	शेष:
		pos = शून्य;
		DRM_ERROR("Unknown pipeline resource ID: %d.\n", id);
		अवरोध;
	पूर्ण

	वापस pos;
पूर्ण

काष्ठा komeda_component *
komeda_pipeline_get_component(काष्ठा komeda_pipeline *pipe, पूर्णांक id)
अणु
	काष्ठा komeda_component **pos = शून्य;
	काष्ठा komeda_component *c = शून्य;

	pos = komeda_pipeline_get_component_pos(pipe, id);
	अगर (pos)
		c = *pos;

	वापस c;
पूर्ण

काष्ठा komeda_component *
komeda_pipeline_get_first_component(काष्ठा komeda_pipeline *pipe,
				    u32 comp_mask)
अणु
	काष्ठा komeda_component *c = शून्य;
	अचिन्हित दीर्घ comp_mask_local = (अचिन्हित दीर्घ)comp_mask;
	पूर्णांक id;

	id = find_first_bit(&comp_mask_local, 32);
	अगर (id < 32)
		c = komeda_pipeline_get_component(pipe, id);

	वापस c;
पूर्ण

अटल काष्ठा komeda_component *
komeda_component_pickup_input(काष्ठा komeda_component *c, u32 avail_comps)
अणु
	u32 avail_inमाला_दो = c->supported_inमाला_दो & (avail_comps);

	वापस komeda_pipeline_get_first_component(c->pipeline, avail_inमाला_दो);
पूर्ण

/** komeda_component_add - Add a component to &komeda_pipeline */
काष्ठा komeda_component *
komeda_component_add(काष्ठा komeda_pipeline *pipe,
		     माप_प्रकार comp_sz, u32 id, u32 hw_id,
		     स्थिर काष्ठा komeda_component_funcs *funcs,
		     u8 max_active_inमाला_दो, u32 supported_inमाला_दो,
		     u8 max_active_outमाला_दो, u32 __iomem *reg,
		     स्थिर अक्षर *name_fmt, ...)
अणु
	काष्ठा komeda_component **pos;
	काष्ठा komeda_component *c;
	पूर्णांक idx, *num = शून्य;

	अगर (max_active_inमाला_दो > KOMEDA_COMPONENT_N_INPUTS) अणु
		WARN(1, "please large KOMEDA_COMPONENT_N_INPUTS to %d.\n",
		     max_active_inमाला_दो);
		वापस ERR_PTR(-ENOSPC);
	पूर्ण

	pos = komeda_pipeline_get_component_pos(pipe, id);
	अगर (!pos || (*pos))
		वापस ERR_PTR(-EINVAL);

	अगर (has_bit(id, KOMEDA_PIPELINE_LAYERS)) अणु
		idx = id - KOMEDA_COMPONENT_LAYER0;
		num = &pipe->n_layers;
		अगर (idx != pipe->n_layers) अणु
			DRM_ERROR("please add Layer by id sequence.\n");
			वापस ERR_PTR(-EINVAL);
		पूर्ण
	पूर्ण अन्यथा अगर (has_bit(id,  KOMEDA_PIPELINE_SCALERS)) अणु
		idx = id - KOMEDA_COMPONENT_SCALER0;
		num = &pipe->n_scalers;
		अगर (idx != pipe->n_scalers) अणु
			DRM_ERROR("please add Scaler by id sequence.\n");
			वापस ERR_PTR(-EINVAL);
		पूर्ण
	पूर्ण

	c = devm_kzalloc(pipe->mdev->dev, comp_sz, GFP_KERNEL);
	अगर (!c)
		वापस ERR_PTR(-ENOMEM);

	c->id = id;
	c->hw_id = hw_id;
	c->reg = reg;
	c->pipeline = pipe;
	c->max_active_inमाला_दो = max_active_inमाला_दो;
	c->max_active_outमाला_दो = max_active_outमाला_दो;
	c->supported_inमाला_दो = supported_inमाला_दो;
	c->funcs = funcs;

	अगर (name_fmt) अणु
		बहु_सूची args;

		बहु_शुरू(args, name_fmt);
		vsnम_लिखो(c->name, माप(c->name), name_fmt, args);
		बहु_पूर्ण(args);
	पूर्ण

	अगर (num)
		*num = *num + 1;

	pipe->avail_comps |= BIT(c->id);
	*pos = c;

	वापस c;
पूर्ण

व्योम komeda_component_destroy(काष्ठा komeda_dev *mdev,
			      काष्ठा komeda_component *c)
अणु
	devm_kमुक्त(mdev->dev, c);
पूर्ण

अटल व्योम komeda_component_dump(काष्ठा komeda_component *c)
अणु
	अगर (!c)
		वापस;

	DRM_DEBUG("	%s: ID %d-0x%08lx.\n",
		  c->name, c->id, BIT(c->id));
	DRM_DEBUG("		max_active_inputs:%d, supported_inputs: 0x%08x.\n",
		  c->max_active_inमाला_दो, c->supported_inमाला_दो);
	DRM_DEBUG("		max_active_outputs:%d, supported_outputs: 0x%08x.\n",
		  c->max_active_outमाला_दो, c->supported_outमाला_दो);
पूर्ण

अटल व्योम komeda_pipeline_dump(काष्ठा komeda_pipeline *pipe)
अणु
	काष्ठा komeda_component *c;
	पूर्णांक id;
	अचिन्हित दीर्घ avail_comps = pipe->avail_comps;

	DRM_INFO("Pipeline-%d: n_layers: %d, n_scalers: %d, output: %s.\n",
		 pipe->id, pipe->n_layers, pipe->n_scalers,
		 pipe->dual_link ? "dual-link" : "single-link");
	DRM_INFO("	output_link[0]: %s.\n",
		 pipe->of_output_links[0] ?
		 pipe->of_output_links[0]->full_name : "none");
	DRM_INFO("	output_link[1]: %s.\n",
		 pipe->of_output_links[1] ?
		 pipe->of_output_links[1]->full_name : "none");

	क्रम_each_set_bit(id, &avail_comps, 32) अणु
		c = komeda_pipeline_get_component(pipe, id);

		komeda_component_dump(c);
	पूर्ण
पूर्ण

अटल व्योम komeda_component_verअगरy_inमाला_दो(काष्ठा komeda_component *c)
अणु
	काष्ठा komeda_pipeline *pipe = c->pipeline;
	काष्ठा komeda_component *input;
	पूर्णांक id;
	अचिन्हित दीर्घ supported_inमाला_दो = c->supported_inमाला_दो;

	क्रम_each_set_bit(id, &supported_inमाला_दो, 32) अणु
		input = komeda_pipeline_get_component(pipe, id);
		अगर (!input) अणु
			c->supported_inमाला_दो &= ~(BIT(id));
			DRM_WARN("Can not find input(ID-%d) for component: %s.\n",
				 id, c->name);
			जारी;
		पूर्ण

		input->supported_outमाला_दो |= BIT(c->id);
	पूर्ण
पूर्ण

अटल काष्ठा komeda_layer *
komeda_get_layer_split_right_layer(काष्ठा komeda_pipeline *pipe,
				   काष्ठा komeda_layer *left)
अणु
	पूर्णांक index = left->base.id - KOMEDA_COMPONENT_LAYER0;
	पूर्णांक i;

	क्रम (i = index + 1; i < pipe->n_layers; i++)
		अगर (left->layer_type == pipe->layers[i]->layer_type)
			वापस pipe->layers[i];
	वापस शून्य;
पूर्ण

अटल व्योम komeda_pipeline_assemble(काष्ठा komeda_pipeline *pipe)
अणु
	काष्ठा komeda_component *c;
	काष्ठा komeda_layer *layer;
	पूर्णांक i, id;
	अचिन्हित दीर्घ avail_comps = pipe->avail_comps;

	क्रम_each_set_bit(id, &avail_comps, 32) अणु
		c = komeda_pipeline_get_component(pipe, id);
		komeda_component_verअगरy_inमाला_दो(c);
	पूर्ण
	/* calculate right layer क्रम the layer split */
	क्रम (i = 0; i < pipe->n_layers; i++) अणु
		layer = pipe->layers[i];

		layer->right = komeda_get_layer_split_right_layer(pipe, layer);
	पूर्ण

	अगर (pipe->dual_link && !pipe->ctrlr->supports_dual_link) अणु
		pipe->dual_link = false;
		DRM_WARN("PIPE-%d doesn't support dual-link, ignore DT dual-link configuration.\n",
			 pipe->id);
	पूर्ण
पूर्ण

/* अगर pipeline_A accept another pipeline_B's component as input, treat
 * pipeline_B as slave of pipeline_A.
 */
काष्ठा komeda_pipeline *
komeda_pipeline_get_slave(काष्ठा komeda_pipeline *master)
अणु
	काष्ठा komeda_component *slave;

	slave = komeda_component_pickup_input(&master->compiz->base,
					      KOMEDA_PIPELINE_COMPIZS);

	वापस slave ? slave->pipeline : शून्य;
पूर्ण

पूर्णांक komeda_assemble_pipelines(काष्ठा komeda_dev *mdev)
अणु
	काष्ठा komeda_pipeline *pipe;
	पूर्णांक i;

	क्रम (i = 0; i < mdev->n_pipelines; i++) अणु
		pipe = mdev->pipelines[i];

		komeda_pipeline_assemble(pipe);
		komeda_pipeline_dump(pipe);
	पूर्ण

	वापस 0;
पूर्ण

व्योम komeda_pipeline_dump_रेजिस्टर(काष्ठा komeda_pipeline *pipe,
				   काष्ठा seq_file *sf)
अणु
	काष्ठा komeda_component *c;
	u32 id;
	अचिन्हित दीर्घ avail_comps;

	seq_म_लिखो(sf, "\n======== Pipeline-%d ==========\n", pipe->id);

	अगर (pipe->funcs && pipe->funcs->dump_रेजिस्टर)
		pipe->funcs->dump_रेजिस्टर(pipe, sf);

	avail_comps = pipe->avail_comps;
	क्रम_each_set_bit(id, &avail_comps, 32) अणु
		c = komeda_pipeline_get_component(pipe, id);

		seq_म_लिखो(sf, "\n------%s------\n", c->name);
		अगर (c->funcs->dump_रेजिस्टर)
			c->funcs->dump_रेजिस्टर(c, sf);
	पूर्ण
पूर्ण
