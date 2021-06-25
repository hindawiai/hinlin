<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * vsp1_entity.h  --  R-Car VSP1 Base Entity
 *
 * Copyright (C) 2013-2014 Renesas Electronics Corporation
 *
 * Contact: Laurent Pinअक्षरt (laurent.pinअक्षरt@ideasonboard.com)
 */
#अगर_अघोषित __VSP1_ENTITY_H__
#घोषणा __VSP1_ENTITY_H__

#समावेश <linux/list.h>
#समावेश <linux/mutex.h>

#समावेश <media/v4l2-subdev.h>

काष्ठा vsp1_device;
काष्ठा vsp1_dl_body;
काष्ठा vsp1_dl_list;
काष्ठा vsp1_pipeline;
काष्ठा vsp1_partition;
काष्ठा vsp1_partition_winकरोw;

क्रमागत vsp1_entity_type अणु
	VSP1_ENTITY_BRS,
	VSP1_ENTITY_BRU,
	VSP1_ENTITY_CLU,
	VSP1_ENTITY_HGO,
	VSP1_ENTITY_HGT,
	VSP1_ENTITY_HSI,
	VSP1_ENTITY_HST,
	VSP1_ENTITY_LIF,
	VSP1_ENTITY_LUT,
	VSP1_ENTITY_RPF,
	VSP1_ENTITY_SRU,
	VSP1_ENTITY_UDS,
	VSP1_ENTITY_UIF,
	VSP1_ENTITY_WPF,
पूर्ण;

#घोषणा VSP1_ENTITY_MAX_INPUTS		5	/* For the BRU */

/*
 * काष्ठा vsp1_route - Entity routing configuration
 * @type: Entity type this routing entry is associated with
 * @index: Entity index this routing entry is associated with
 * @reg: Output routing configuration रेजिस्टर
 * @inमाला_दो: Target node value क्रम each input
 * @output: Target node value क्रम entity output
 *
 * Each $vsp1_route entry describes routing configuration क्रम the entity
 * specअगरied by the entry's @type and @index. @reg indicates the रेजिस्टर that
 * holds output routing configuration क्रम the entity, and the @inमाला_दो array
 * store the target node value क्रम each input of the entity. The @output field
 * stores the target node value of the entity output when used as a source क्रम
 * histogram generation.
 */
काष्ठा vsp1_route अणु
	क्रमागत vsp1_entity_type type;
	अचिन्हित पूर्णांक index;
	अचिन्हित पूर्णांक reg;
	अचिन्हित पूर्णांक inमाला_दो[VSP1_ENTITY_MAX_INPUTS];
	अचिन्हित पूर्णांक output;
पूर्ण;

/**
 * काष्ठा vsp1_entity_operations - Entity operations
 * @destroy:	Destroy the entity.
 * @configure_stream:	Setup the hardware parameters क्रम the stream which करो
 *			not vary between frames (pipeline, क्रमmats). Note that
 *			the vsp1_dl_list argument is only valid क्रम display
 *			pipeline and will be शून्य क्रम mem-to-mem pipelines.
 * @configure_frame:	Configure the runसमय parameters क्रम each frame.
 * @configure_partition: Configure partition specअगरic parameters.
 * @max_width:	Return the max supported width of data that the entity can
 *		process in a single operation.
 * @partition:	Process the partition स्थिरruction based on this entity's
 *		configuration.
 */
काष्ठा vsp1_entity_operations अणु
	व्योम (*destroy)(काष्ठा vsp1_entity *);
	व्योम (*configure_stream)(काष्ठा vsp1_entity *, काष्ठा vsp1_pipeline *,
				 काष्ठा vsp1_dl_list *, काष्ठा vsp1_dl_body *);
	व्योम (*configure_frame)(काष्ठा vsp1_entity *, काष्ठा vsp1_pipeline *,
				काष्ठा vsp1_dl_list *, काष्ठा vsp1_dl_body *);
	व्योम (*configure_partition)(काष्ठा vsp1_entity *,
				    काष्ठा vsp1_pipeline *,
				    काष्ठा vsp1_dl_list *,
				    काष्ठा vsp1_dl_body *);
	अचिन्हित पूर्णांक (*max_width)(काष्ठा vsp1_entity *, काष्ठा vsp1_pipeline *);
	व्योम (*partition)(काष्ठा vsp1_entity *, काष्ठा vsp1_pipeline *,
			  काष्ठा vsp1_partition *, अचिन्हित पूर्णांक,
			  काष्ठा vsp1_partition_winकरोw *);
पूर्ण;

काष्ठा vsp1_entity अणु
	काष्ठा vsp1_device *vsp1;

	स्थिर काष्ठा vsp1_entity_operations *ops;

	क्रमागत vsp1_entity_type type;
	अचिन्हित पूर्णांक index;
	स्थिर काष्ठा vsp1_route *route;

	काष्ठा vsp1_pipeline *pipe;

	काष्ठा list_head list_dev;
	काष्ठा list_head list_pipe;

	काष्ठा media_pad *pads;
	अचिन्हित पूर्णांक source_pad;

	काष्ठा vsp1_entity **sources;
	काष्ठा vsp1_entity *sink;
	अचिन्हित पूर्णांक sink_pad;

	काष्ठा v4l2_subdev subdev;
	काष्ठा v4l2_subdev_pad_config *config;

	काष्ठा mutex lock;	/* Protects the pad config */
पूर्ण;

अटल अंतरभूत काष्ठा vsp1_entity *to_vsp1_entity(काष्ठा v4l2_subdev *subdev)
अणु
	वापस container_of(subdev, काष्ठा vsp1_entity, subdev);
पूर्ण

पूर्णांक vsp1_entity_init(काष्ठा vsp1_device *vsp1, काष्ठा vsp1_entity *entity,
		     स्थिर अक्षर *name, अचिन्हित पूर्णांक num_pads,
		     स्थिर काष्ठा v4l2_subdev_ops *ops, u32 function);
व्योम vsp1_entity_destroy(काष्ठा vsp1_entity *entity);

बाह्य स्थिर काष्ठा v4l2_subdev_पूर्णांकernal_ops vsp1_subdev_पूर्णांकernal_ops;

पूर्णांक vsp1_entity_link_setup(काष्ठा media_entity *entity,
			   स्थिर काष्ठा media_pad *local,
			   स्थिर काष्ठा media_pad *remote, u32 flags);

काष्ठा v4l2_subdev_pad_config *
vsp1_entity_get_pad_config(काष्ठा vsp1_entity *entity,
			   काष्ठा v4l2_subdev_pad_config *cfg,
			   क्रमागत v4l2_subdev_क्रमmat_whence which);
काष्ठा v4l2_mbus_framefmt *
vsp1_entity_get_pad_क्रमmat(काष्ठा vsp1_entity *entity,
			   काष्ठा v4l2_subdev_pad_config *cfg,
			   अचिन्हित पूर्णांक pad);
काष्ठा v4l2_rect *
vsp1_entity_get_pad_selection(काष्ठा vsp1_entity *entity,
			      काष्ठा v4l2_subdev_pad_config *cfg,
			      अचिन्हित पूर्णांक pad, अचिन्हित पूर्णांक target);
पूर्णांक vsp1_entity_init_cfg(काष्ठा v4l2_subdev *subdev,
			 काष्ठा v4l2_subdev_pad_config *cfg);

व्योम vsp1_entity_route_setup(काष्ठा vsp1_entity *entity,
			     काष्ठा vsp1_pipeline *pipe,
			     काष्ठा vsp1_dl_body *dlb);

व्योम vsp1_entity_configure_stream(काष्ठा vsp1_entity *entity,
				  काष्ठा vsp1_pipeline *pipe,
				  काष्ठा vsp1_dl_list *dl,
				  काष्ठा vsp1_dl_body *dlb);

व्योम vsp1_entity_configure_frame(काष्ठा vsp1_entity *entity,
				 काष्ठा vsp1_pipeline *pipe,
				 काष्ठा vsp1_dl_list *dl,
				 काष्ठा vsp1_dl_body *dlb);

व्योम vsp1_entity_configure_partition(काष्ठा vsp1_entity *entity,
				     काष्ठा vsp1_pipeline *pipe,
				     काष्ठा vsp1_dl_list *dl,
				     काष्ठा vsp1_dl_body *dlb);

काष्ठा media_pad *vsp1_entity_remote_pad(काष्ठा media_pad *pad);

पूर्णांक vsp1_subdev_get_pad_क्रमmat(काष्ठा v4l2_subdev *subdev,
			       काष्ठा v4l2_subdev_pad_config *cfg,
			       काष्ठा v4l2_subdev_क्रमmat *fmt);
पूर्णांक vsp1_subdev_set_pad_क्रमmat(काष्ठा v4l2_subdev *subdev,
			       काष्ठा v4l2_subdev_pad_config *cfg,
			       काष्ठा v4l2_subdev_क्रमmat *fmt,
			       स्थिर अचिन्हित पूर्णांक *codes, अचिन्हित पूर्णांक ncodes,
			       अचिन्हित पूर्णांक min_width, अचिन्हित पूर्णांक min_height,
			       अचिन्हित पूर्णांक max_width, अचिन्हित पूर्णांक max_height);
पूर्णांक vsp1_subdev_क्रमागत_mbus_code(काष्ठा v4l2_subdev *subdev,
			       काष्ठा v4l2_subdev_pad_config *cfg,
			       काष्ठा v4l2_subdev_mbus_code_क्रमागत *code,
			       स्थिर अचिन्हित पूर्णांक *codes, अचिन्हित पूर्णांक ncodes);
पूर्णांक vsp1_subdev_क्रमागत_frame_size(काष्ठा v4l2_subdev *subdev,
				काष्ठा v4l2_subdev_pad_config *cfg,
				काष्ठा v4l2_subdev_frame_size_क्रमागत *fse,
				अचिन्हित पूर्णांक min_w, अचिन्हित पूर्णांक min_h,
				अचिन्हित पूर्णांक max_w, अचिन्हित पूर्णांक max_h);

#पूर्ण_अगर /* __VSP1_ENTITY_H__ */
