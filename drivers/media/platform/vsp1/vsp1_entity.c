<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * vsp1_entity.c  --  R-Car VSP1 Base Entity
 *
 * Copyright (C) 2013-2014 Renesas Electronics Corporation
 *
 * Contact: Laurent Pinअक्षरt (laurent.pinअक्षरt@ideasonboard.com)
 */

#समावेश <linux/device.h>
#समावेश <linux/gfp.h>

#समावेश <media/media-entity.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-subdev.h>

#समावेश "vsp1.h"
#समावेश "vsp1_dl.h"
#समावेश "vsp1_entity.h"
#समावेश "vsp1_pipe.h"
#समावेश "vsp1_rwpf.h"

व्योम vsp1_entity_route_setup(काष्ठा vsp1_entity *entity,
			     काष्ठा vsp1_pipeline *pipe,
			     काष्ठा vsp1_dl_body *dlb)
अणु
	काष्ठा vsp1_entity *source;
	u32 route;

	अगर (entity->type == VSP1_ENTITY_HGO) अणु
		u32 smppt;

		/*
		 * The HGO is a special हाल, its routing is configured on the
		 * sink pad.
		 */
		source = entity->sources[0];
		smppt = (pipe->output->entity.index << VI6_DPR_SMPPT_TGW_SHIFT)
		      | (source->route->output << VI6_DPR_SMPPT_PT_SHIFT);

		vsp1_dl_body_ग_लिखो(dlb, VI6_DPR_HGO_SMPPT, smppt);
		वापस;
	पूर्ण अन्यथा अगर (entity->type == VSP1_ENTITY_HGT) अणु
		u32 smppt;

		/*
		 * The HGT is a special हाल, its routing is configured on the
		 * sink pad.
		 */
		source = entity->sources[0];
		smppt = (pipe->output->entity.index << VI6_DPR_SMPPT_TGW_SHIFT)
		      | (source->route->output << VI6_DPR_SMPPT_PT_SHIFT);

		vsp1_dl_body_ग_लिखो(dlb, VI6_DPR_HGT_SMPPT, smppt);
		वापस;
	पूर्ण

	source = entity;
	अगर (source->route->reg == 0)
		वापस;

	route = source->sink->route->inमाला_दो[source->sink_pad];
	/*
	 * The ILV and BRS share the same data path route. The extra BRSSEL bit
	 * selects between the ILV and BRS.
	 */
	अगर (source->type == VSP1_ENTITY_BRS)
		route |= VI6_DPR_ROUTE_BRSSEL;
	vsp1_dl_body_ग_लिखो(dlb, source->route->reg, route);
पूर्ण

व्योम vsp1_entity_configure_stream(काष्ठा vsp1_entity *entity,
				  काष्ठा vsp1_pipeline *pipe,
				  काष्ठा vsp1_dl_list *dl,
				  काष्ठा vsp1_dl_body *dlb)
अणु
	अगर (entity->ops->configure_stream)
		entity->ops->configure_stream(entity, pipe, dl, dlb);
पूर्ण

व्योम vsp1_entity_configure_frame(काष्ठा vsp1_entity *entity,
				 काष्ठा vsp1_pipeline *pipe,
				 काष्ठा vsp1_dl_list *dl,
				 काष्ठा vsp1_dl_body *dlb)
अणु
	अगर (entity->ops->configure_frame)
		entity->ops->configure_frame(entity, pipe, dl, dlb);
पूर्ण

व्योम vsp1_entity_configure_partition(काष्ठा vsp1_entity *entity,
				     काष्ठा vsp1_pipeline *pipe,
				     काष्ठा vsp1_dl_list *dl,
				     काष्ठा vsp1_dl_body *dlb)
अणु
	अगर (entity->ops->configure_partition)
		entity->ops->configure_partition(entity, pipe, dl, dlb);
पूर्ण

/* -----------------------------------------------------------------------------
 * V4L2 Subdevice Operations
 */

/**
 * vsp1_entity_get_pad_config - Get the pad configuration क्रम an entity
 * @entity: the entity
 * @cfg: the TRY pad configuration
 * @which: configuration selector (ACTIVE or TRY)
 *
 * When called with which set to V4L2_SUBDEV_FORMAT_ACTIVE the caller must hold
 * the entity lock to access the वापसed configuration.
 *
 * Return the pad configuration requested by the which argument. The TRY
 * configuration is passed explicitly to the function through the cfg argument
 * and simply वापसed when requested. The ACTIVE configuration comes from the
 * entity काष्ठाure.
 */
काष्ठा v4l2_subdev_pad_config *
vsp1_entity_get_pad_config(काष्ठा vsp1_entity *entity,
			   काष्ठा v4l2_subdev_pad_config *cfg,
			   क्रमागत v4l2_subdev_क्रमmat_whence which)
अणु
	चयन (which) अणु
	हाल V4L2_SUBDEV_FORMAT_ACTIVE:
		वापस entity->config;
	हाल V4L2_SUBDEV_FORMAT_TRY:
	शेष:
		वापस cfg;
	पूर्ण
पूर्ण

/**
 * vsp1_entity_get_pad_क्रमmat - Get a pad क्रमmat from storage क्रम an entity
 * @entity: the entity
 * @cfg: the configuration storage
 * @pad: the pad number
 *
 * Return the क्रमmat stored in the given configuration क्रम an entity's pad. The
 * configuration can be an ACTIVE or TRY configuration.
 */
काष्ठा v4l2_mbus_framefmt *
vsp1_entity_get_pad_क्रमmat(काष्ठा vsp1_entity *entity,
			   काष्ठा v4l2_subdev_pad_config *cfg,
			   अचिन्हित पूर्णांक pad)
अणु
	वापस v4l2_subdev_get_try_क्रमmat(&entity->subdev, cfg, pad);
पूर्ण

/**
 * vsp1_entity_get_pad_selection - Get a pad selection from storage क्रम entity
 * @entity: the entity
 * @cfg: the configuration storage
 * @pad: the pad number
 * @target: the selection target
 *
 * Return the selection rectangle stored in the given configuration क्रम an
 * entity's pad. The configuration can be an ACTIVE or TRY configuration. The
 * selection target can be COMPOSE or CROP.
 */
काष्ठा v4l2_rect *
vsp1_entity_get_pad_selection(काष्ठा vsp1_entity *entity,
			      काष्ठा v4l2_subdev_pad_config *cfg,
			      अचिन्हित पूर्णांक pad, अचिन्हित पूर्णांक target)
अणु
	चयन (target) अणु
	हाल V4L2_SEL_TGT_COMPOSE:
		वापस v4l2_subdev_get_try_compose(&entity->subdev, cfg, pad);
	हाल V4L2_SEL_TGT_CROP:
		वापस v4l2_subdev_get_try_crop(&entity->subdev, cfg, pad);
	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण

/*
 * vsp1_entity_init_cfg - Initialize क्रमmats on all pads
 * @subdev: V4L2 subdevice
 * @cfg: V4L2 subdev pad configuration
 *
 * Initialize all pad क्रमmats with शेष values in the given pad config. This
 * function can be used as a handler क्रम the subdev pad::init_cfg operation.
 */
पूर्णांक vsp1_entity_init_cfg(काष्ठा v4l2_subdev *subdev,
			 काष्ठा v4l2_subdev_pad_config *cfg)
अणु
	काष्ठा v4l2_subdev_क्रमmat क्रमmat;
	अचिन्हित पूर्णांक pad;

	क्रम (pad = 0; pad < subdev->entity.num_pads - 1; ++pad) अणु
		स_रखो(&क्रमmat, 0, माप(क्रमmat));

		क्रमmat.pad = pad;
		क्रमmat.which = cfg ? V4L2_SUBDEV_FORMAT_TRY
			     : V4L2_SUBDEV_FORMAT_ACTIVE;

		v4l2_subdev_call(subdev, pad, set_fmt, cfg, &क्रमmat);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * vsp1_subdev_get_pad_क्रमmat - Subdev pad get_fmt handler
 * @subdev: V4L2 subdevice
 * @cfg: V4L2 subdev pad configuration
 * @fmt: V4L2 subdev क्रमmat
 *
 * This function implements the subdev get_fmt pad operation. It can be used as
 * a direct drop-in क्रम the operation handler.
 */
पूर्णांक vsp1_subdev_get_pad_क्रमmat(काष्ठा v4l2_subdev *subdev,
			       काष्ठा v4l2_subdev_pad_config *cfg,
			       काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा vsp1_entity *entity = to_vsp1_entity(subdev);
	काष्ठा v4l2_subdev_pad_config *config;

	config = vsp1_entity_get_pad_config(entity, cfg, fmt->which);
	अगर (!config)
		वापस -EINVAL;

	mutex_lock(&entity->lock);
	fmt->क्रमmat = *vsp1_entity_get_pad_क्रमmat(entity, config, fmt->pad);
	mutex_unlock(&entity->lock);

	वापस 0;
पूर्ण

/*
 * vsp1_subdev_क्रमागत_mbus_code - Subdev pad क्रमागत_mbus_code handler
 * @subdev: V4L2 subdevice
 * @cfg: V4L2 subdev pad configuration
 * @code: Media bus code क्रमागतeration
 * @codes: Array of supported media bus codes
 * @ncodes: Number of supported media bus codes
 *
 * This function implements the subdev क्रमागत_mbus_code pad operation क्रम entities
 * that करो not support क्रमmat conversion. It क्रमागतerates the given supported
 * media bus codes on the sink pad and reports a source pad क्रमmat identical to
 * the sink pad.
 */
पूर्णांक vsp1_subdev_क्रमागत_mbus_code(काष्ठा v4l2_subdev *subdev,
			       काष्ठा v4l2_subdev_pad_config *cfg,
			       काष्ठा v4l2_subdev_mbus_code_क्रमागत *code,
			       स्थिर अचिन्हित पूर्णांक *codes, अचिन्हित पूर्णांक ncodes)
अणु
	काष्ठा vsp1_entity *entity = to_vsp1_entity(subdev);

	अगर (code->pad == 0) अणु
		अगर (code->index >= ncodes)
			वापस -EINVAL;

		code->code = codes[code->index];
	पूर्ण अन्यथा अणु
		काष्ठा v4l2_subdev_pad_config *config;
		काष्ठा v4l2_mbus_framefmt *क्रमmat;

		/*
		 * The entity can't perक्रमm क्रमmat conversion, the sink क्रमmat
		 * is always identical to the source क्रमmat.
		 */
		अगर (code->index)
			वापस -EINVAL;

		config = vsp1_entity_get_pad_config(entity, cfg, code->which);
		अगर (!config)
			वापस -EINVAL;

		mutex_lock(&entity->lock);
		क्रमmat = vsp1_entity_get_pad_क्रमmat(entity, config, 0);
		code->code = क्रमmat->code;
		mutex_unlock(&entity->lock);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * vsp1_subdev_क्रमागत_frame_size - Subdev pad क्रमागत_frame_size handler
 * @subdev: V4L2 subdevice
 * @cfg: V4L2 subdev pad configuration
 * @fse: Frame size क्रमागतeration
 * @min_width: Minimum image width
 * @min_height: Minimum image height
 * @max_width: Maximum image width
 * @max_height: Maximum image height
 *
 * This function implements the subdev क्रमागत_frame_size pad operation क्रम
 * entities that करो not support scaling or cropping. It reports the given
 * minimum and maximum frame width and height on the sink pad, and a fixed
 * source pad size identical to the sink pad.
 */
पूर्णांक vsp1_subdev_क्रमागत_frame_size(काष्ठा v4l2_subdev *subdev,
				काष्ठा v4l2_subdev_pad_config *cfg,
				काष्ठा v4l2_subdev_frame_size_क्रमागत *fse,
				अचिन्हित पूर्णांक min_width, अचिन्हित पूर्णांक min_height,
				अचिन्हित पूर्णांक max_width, अचिन्हित पूर्णांक max_height)
अणु
	काष्ठा vsp1_entity *entity = to_vsp1_entity(subdev);
	काष्ठा v4l2_subdev_pad_config *config;
	काष्ठा v4l2_mbus_framefmt *क्रमmat;
	पूर्णांक ret = 0;

	config = vsp1_entity_get_pad_config(entity, cfg, fse->which);
	अगर (!config)
		वापस -EINVAL;

	क्रमmat = vsp1_entity_get_pad_क्रमmat(entity, config, fse->pad);

	mutex_lock(&entity->lock);

	अगर (fse->index || fse->code != क्रमmat->code) अणु
		ret = -EINVAL;
		जाओ करोne;
	पूर्ण

	अगर (fse->pad == 0) अणु
		fse->min_width = min_width;
		fse->max_width = max_width;
		fse->min_height = min_height;
		fse->max_height = max_height;
	पूर्ण अन्यथा अणु
		/*
		 * The size on the source pad are fixed and always identical to
		 * the size on the sink pad.
		 */
		fse->min_width = क्रमmat->width;
		fse->max_width = क्रमmat->width;
		fse->min_height = क्रमmat->height;
		fse->max_height = क्रमmat->height;
	पूर्ण

करोne:
	mutex_unlock(&entity->lock);
	वापस ret;
पूर्ण

/*
 * vsp1_subdev_set_pad_क्रमmat - Subdev pad set_fmt handler
 * @subdev: V4L2 subdevice
 * @cfg: V4L2 subdev pad configuration
 * @fmt: V4L2 subdev क्रमmat
 * @codes: Array of supported media bus codes
 * @ncodes: Number of supported media bus codes
 * @min_width: Minimum image width
 * @min_height: Minimum image height
 * @max_width: Maximum image width
 * @max_height: Maximum image height
 *
 * This function implements the subdev set_fmt pad operation क्रम entities that
 * करो not support scaling or cropping. It शेषs to the first supplied media
 * bus code अगर the requested code isn't supported, clamps the size to the
 * supplied minimum and maximum, and propagates the sink pad क्रमmat to the
 * source pad.
 */
पूर्णांक vsp1_subdev_set_pad_क्रमmat(काष्ठा v4l2_subdev *subdev,
			       काष्ठा v4l2_subdev_pad_config *cfg,
			       काष्ठा v4l2_subdev_क्रमmat *fmt,
			       स्थिर अचिन्हित पूर्णांक *codes, अचिन्हित पूर्णांक ncodes,
			       अचिन्हित पूर्णांक min_width, अचिन्हित पूर्णांक min_height,
			       अचिन्हित पूर्णांक max_width, अचिन्हित पूर्णांक max_height)
अणु
	काष्ठा vsp1_entity *entity = to_vsp1_entity(subdev);
	काष्ठा v4l2_subdev_pad_config *config;
	काष्ठा v4l2_mbus_framefmt *क्रमmat;
	काष्ठा v4l2_rect *selection;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret = 0;

	mutex_lock(&entity->lock);

	config = vsp1_entity_get_pad_config(entity, cfg, fmt->which);
	अगर (!config) अणु
		ret = -EINVAL;
		जाओ करोne;
	पूर्ण

	क्रमmat = vsp1_entity_get_pad_क्रमmat(entity, config, fmt->pad);

	अगर (fmt->pad == entity->source_pad) अणु
		/* The output क्रमmat can't be modअगरied. */
		fmt->क्रमmat = *क्रमmat;
		जाओ करोne;
	पूर्ण

	/*
	 * Default to the first media bus code अगर the requested क्रमmat is not
	 * supported.
	 */
	क्रम (i = 0; i < ncodes; ++i) अणु
		अगर (fmt->क्रमmat.code == codes[i])
			अवरोध;
	पूर्ण

	क्रमmat->code = i < ncodes ? codes[i] : codes[0];
	क्रमmat->width = clamp_t(अचिन्हित पूर्णांक, fmt->क्रमmat.width,
				min_width, max_width);
	क्रमmat->height = clamp_t(अचिन्हित पूर्णांक, fmt->क्रमmat.height,
				 min_height, max_height);
	क्रमmat->field = V4L2_FIELD_NONE;
	क्रमmat->colorspace = V4L2_COLORSPACE_SRGB;

	fmt->क्रमmat = *क्रमmat;

	/* Propagate the क्रमmat to the source pad. */
	क्रमmat = vsp1_entity_get_pad_क्रमmat(entity, config, entity->source_pad);
	*क्रमmat = fmt->क्रमmat;

	/* Reset the crop and compose rectangles. */
	selection = vsp1_entity_get_pad_selection(entity, config, fmt->pad,
						  V4L2_SEL_TGT_CROP);
	selection->left = 0;
	selection->top = 0;
	selection->width = क्रमmat->width;
	selection->height = क्रमmat->height;

	selection = vsp1_entity_get_pad_selection(entity, config, fmt->pad,
						  V4L2_SEL_TGT_COMPOSE);
	selection->left = 0;
	selection->top = 0;
	selection->width = क्रमmat->width;
	selection->height = क्रमmat->height;

करोne:
	mutex_unlock(&entity->lock);
	वापस ret;
पूर्ण

/* -----------------------------------------------------------------------------
 * Media Operations
 */

अटल अंतरभूत काष्ठा vsp1_entity *
media_entity_to_vsp1_entity(काष्ठा media_entity *entity)
अणु
	वापस container_of(entity, काष्ठा vsp1_entity, subdev.entity);
पूर्ण

अटल पूर्णांक vsp1_entity_link_setup_source(स्थिर काष्ठा media_pad *source_pad,
					 स्थिर काष्ठा media_pad *sink_pad,
					 u32 flags)
अणु
	काष्ठा vsp1_entity *source;

	source = media_entity_to_vsp1_entity(source_pad->entity);

	अगर (!source->route)
		वापस 0;

	अगर (flags & MEDIA_LNK_FL_ENABLED) अणु
		काष्ठा vsp1_entity *sink
			= media_entity_to_vsp1_entity(sink_pad->entity);

		/*
		 * Fan-out is limited to one क्रम the normal data path plus
		 * optional HGO and HGT. We ignore the HGO and HGT here.
		 */
		अगर (sink->type != VSP1_ENTITY_HGO &&
		    sink->type != VSP1_ENTITY_HGT) अणु
			अगर (source->sink)
				वापस -EBUSY;
			source->sink = sink;
			source->sink_pad = sink_pad->index;
		पूर्ण
	पूर्ण अन्यथा अणु
		source->sink = शून्य;
		source->sink_pad = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vsp1_entity_link_setup_sink(स्थिर काष्ठा media_pad *source_pad,
				       स्थिर काष्ठा media_pad *sink_pad,
				       u32 flags)
अणु
	काष्ठा vsp1_entity *sink;
	काष्ठा vsp1_entity *source;

	sink = media_entity_to_vsp1_entity(sink_pad->entity);
	source = media_entity_to_vsp1_entity(source_pad->entity);

	अगर (flags & MEDIA_LNK_FL_ENABLED) अणु
		/* Fan-in is limited to one. */
		अगर (sink->sources[sink_pad->index])
			वापस -EBUSY;

		sink->sources[sink_pad->index] = source;
	पूर्ण अन्यथा अणु
		sink->sources[sink_pad->index] = शून्य;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक vsp1_entity_link_setup(काष्ठा media_entity *entity,
			   स्थिर काष्ठा media_pad *local,
			   स्थिर काष्ठा media_pad *remote, u32 flags)
अणु
	अगर (local->flags & MEDIA_PAD_FL_SOURCE)
		वापस vsp1_entity_link_setup_source(local, remote, flags);
	अन्यथा
		वापस vsp1_entity_link_setup_sink(remote, local, flags);
पूर्ण

/**
 * vsp1_entity_remote_pad - Find the pad at the remote end of a link
 * @pad: Pad at the local end of the link
 *
 * Search क्रम a remote pad connected to the given pad by iterating over all
 * links originating or terminating at that pad until an enabled link is found.
 *
 * Our link setup implementation guarantees that the output fan-out will not be
 * higher than one क्रम the data pipelines, except क्रम the links to the HGO and
 * HGT that can be enabled in addition to a regular data link. When traversing
 * outgoing links this function ignores HGO and HGT entities and should thus be
 * used in place of the generic media_entity_remote_pad() function to traverse
 * data pipelines.
 *
 * Return a poपूर्णांकer to the pad at the remote end of the first found enabled
 * link, or शून्य अगर no enabled link has been found.
 */
काष्ठा media_pad *vsp1_entity_remote_pad(काष्ठा media_pad *pad)
अणु
	काष्ठा media_link *link;

	list_क्रम_each_entry(link, &pad->entity->links, list) अणु
		काष्ठा vsp1_entity *entity;

		अगर (!(link->flags & MEDIA_LNK_FL_ENABLED))
			जारी;

		/* If we're the sink the source will never be an HGO or HGT. */
		अगर (link->sink == pad)
			वापस link->source;

		अगर (link->source != pad)
			जारी;

		/* If the sink isn't a subdevice it can't be an HGO or HGT. */
		अगर (!is_media_entity_v4l2_subdev(link->sink->entity))
			वापस link->sink;

		entity = media_entity_to_vsp1_entity(link->sink->entity);
		अगर (entity->type != VSP1_ENTITY_HGO &&
		    entity->type != VSP1_ENTITY_HGT)
			वापस link->sink;
	पूर्ण

	वापस शून्य;

पूर्ण

/* -----------------------------------------------------------------------------
 * Initialization
 */

#घोषणा VSP1_ENTITY_ROUTE(ent)						\
	अणु VSP1_ENTITY_##ent, 0, VI6_DPR_##ent##_ROUTE,			\
	  अणु VI6_DPR_NODE_##ent पूर्ण, VI6_DPR_NODE_##ent पूर्ण

#घोषणा VSP1_ENTITY_ROUTE_RPF(idx)					\
	अणु VSP1_ENTITY_RPF, idx, VI6_DPR_RPF_ROUTE(idx),			\
	  अणु 0, पूर्ण, VI6_DPR_NODE_RPF(idx) पूर्ण

#घोषणा VSP1_ENTITY_ROUTE_UDS(idx)					\
	अणु VSP1_ENTITY_UDS, idx, VI6_DPR_UDS_ROUTE(idx),			\
	  अणु VI6_DPR_NODE_UDS(idx) पूर्ण, VI6_DPR_NODE_UDS(idx) पूर्ण

#घोषणा VSP1_ENTITY_ROUTE_UIF(idx)					\
	अणु VSP1_ENTITY_UIF, idx, VI6_DPR_UIF_ROUTE(idx),			\
	  अणु VI6_DPR_NODE_UIF(idx) पूर्ण, VI6_DPR_NODE_UIF(idx) पूर्ण

#घोषणा VSP1_ENTITY_ROUTE_WPF(idx)					\
	अणु VSP1_ENTITY_WPF, idx, 0,					\
	  अणु VI6_DPR_NODE_WPF(idx) पूर्ण, VI6_DPR_NODE_WPF(idx) पूर्ण

अटल स्थिर काष्ठा vsp1_route vsp1_routes[] = अणु
	अणु VSP1_ENTITY_BRS, 0, VI6_DPR_ILV_BRS_ROUTE,
	  अणु VI6_DPR_NODE_BRS_IN(0), VI6_DPR_NODE_BRS_IN(1) पूर्ण, 0 पूर्ण,
	अणु VSP1_ENTITY_BRU, 0, VI6_DPR_BRU_ROUTE,
	  अणु VI6_DPR_NODE_BRU_IN(0), VI6_DPR_NODE_BRU_IN(1),
	    VI6_DPR_NODE_BRU_IN(2), VI6_DPR_NODE_BRU_IN(3),
	    VI6_DPR_NODE_BRU_IN(4) पूर्ण, VI6_DPR_NODE_BRU_OUT पूर्ण,
	VSP1_ENTITY_ROUTE(CLU),
	अणु VSP1_ENTITY_HGO, 0, 0, अणु 0, पूर्ण, 0 पूर्ण,
	अणु VSP1_ENTITY_HGT, 0, 0, अणु 0, पूर्ण, 0 पूर्ण,
	VSP1_ENTITY_ROUTE(HSI),
	VSP1_ENTITY_ROUTE(HST),
	अणु VSP1_ENTITY_LIF, 0, 0, अणु 0, पूर्ण, 0 पूर्ण,
	अणु VSP1_ENTITY_LIF, 1, 0, अणु 0, पूर्ण, 0 पूर्ण,
	VSP1_ENTITY_ROUTE(LUT),
	VSP1_ENTITY_ROUTE_RPF(0),
	VSP1_ENTITY_ROUTE_RPF(1),
	VSP1_ENTITY_ROUTE_RPF(2),
	VSP1_ENTITY_ROUTE_RPF(3),
	VSP1_ENTITY_ROUTE_RPF(4),
	VSP1_ENTITY_ROUTE(SRU),
	VSP1_ENTITY_ROUTE_UDS(0),
	VSP1_ENTITY_ROUTE_UDS(1),
	VSP1_ENTITY_ROUTE_UDS(2),
	VSP1_ENTITY_ROUTE_UIF(0),	/* Named UIF4 in the करोcumentation */
	VSP1_ENTITY_ROUTE_UIF(1),	/* Named UIF5 in the करोcumentation */
	VSP1_ENTITY_ROUTE_WPF(0),
	VSP1_ENTITY_ROUTE_WPF(1),
	VSP1_ENTITY_ROUTE_WPF(2),
	VSP1_ENTITY_ROUTE_WPF(3),
पूर्ण;

पूर्णांक vsp1_entity_init(काष्ठा vsp1_device *vsp1, काष्ठा vsp1_entity *entity,
		     स्थिर अक्षर *name, अचिन्हित पूर्णांक num_pads,
		     स्थिर काष्ठा v4l2_subdev_ops *ops, u32 function)
अणु
	काष्ठा v4l2_subdev *subdev;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	क्रम (i = 0; i < ARRAY_SIZE(vsp1_routes); ++i) अणु
		अगर (vsp1_routes[i].type == entity->type &&
		    vsp1_routes[i].index == entity->index) अणु
			entity->route = &vsp1_routes[i];
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (i == ARRAY_SIZE(vsp1_routes))
		वापस -EINVAL;

	mutex_init(&entity->lock);

	entity->vsp1 = vsp1;
	entity->source_pad = num_pads - 1;

	/* Allocate and initialize pads. */
	entity->pads = devm_kसुस्मृति(vsp1->dev,
				    num_pads, माप(*entity->pads),
				    GFP_KERNEL);
	अगर (entity->pads == शून्य)
		वापस -ENOMEM;

	क्रम (i = 0; i < num_pads - 1; ++i)
		entity->pads[i].flags = MEDIA_PAD_FL_SINK;

	entity->sources = devm_kसुस्मृति(vsp1->dev, max(num_pads - 1, 1U),
				       माप(*entity->sources), GFP_KERNEL);
	अगर (entity->sources == शून्य)
		वापस -ENOMEM;

	/* Single-pad entities only have a sink. */
	entity->pads[num_pads - 1].flags = num_pads > 1 ? MEDIA_PAD_FL_SOURCE
					 : MEDIA_PAD_FL_SINK;

	/* Initialize the media entity. */
	ret = media_entity_pads_init(&entity->subdev.entity, num_pads,
				     entity->pads);
	अगर (ret < 0)
		वापस ret;

	/* Initialize the V4L2 subdev. */
	subdev = &entity->subdev;
	v4l2_subdev_init(subdev, ops);

	subdev->entity.function = function;
	subdev->entity.ops = &vsp1->media_ops;
	subdev->flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;

	snम_लिखो(subdev->name, माप(subdev->name), "%s %s",
		 dev_name(vsp1->dev), name);

	vsp1_entity_init_cfg(subdev, शून्य);

	/*
	 * Allocate the pad configuration to store क्रमmats and selection
	 * rectangles.
	 */
	entity->config = v4l2_subdev_alloc_pad_config(&entity->subdev);
	अगर (entity->config == शून्य) अणु
		media_entity_cleanup(&entity->subdev.entity);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

व्योम vsp1_entity_destroy(काष्ठा vsp1_entity *entity)
अणु
	अगर (entity->ops && entity->ops->destroy)
		entity->ops->destroy(entity);
	अगर (entity->subdev.ctrl_handler)
		v4l2_ctrl_handler_मुक्त(entity->subdev.ctrl_handler);
	v4l2_subdev_मुक्त_pad_config(entity->config);
	media_entity_cleanup(&entity->subdev.entity);
पूर्ण
