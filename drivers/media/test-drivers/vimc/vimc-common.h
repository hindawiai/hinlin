<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * vimc-common.h Virtual Media Controller Driver
 *
 * Copyright (C) 2015-2017 Helen Koike <helen.क्रमnazier@gmail.com>
 */

#अगर_अघोषित _VIMC_COMMON_H_
#घोषणा _VIMC_COMMON_H_

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <media/media-device.h>
#समावेश <media/v4l2-device.h>

#घोषणा VIMC_PDEV_NAME "vimc"

/* VIMC-specअगरic controls */
#घोषणा VIMC_CID_VIMC_BASE		(0x00f00000 | 0xf000)
#घोषणा VIMC_CID_VIMC_CLASS		(0x00f00000 | 1)
#घोषणा VIMC_CID_TEST_PATTERN		(VIMC_CID_VIMC_BASE + 0)
#घोषणा VIMC_CID_MEAN_WIN_SIZE		(VIMC_CID_VIMC_BASE + 1)
#घोषणा VIMC_CID_OSD_TEXT_MODE		(VIMC_CID_VIMC_BASE + 2)

#घोषणा VIMC_FRAME_MAX_WIDTH 4096
#घोषणा VIMC_FRAME_MAX_HEIGHT 2160
#घोषणा VIMC_FRAME_MIN_WIDTH 16
#घोषणा VIMC_FRAME_MIN_HEIGHT 16

#घोषणा VIMC_FRAME_INDEX(lin, col, width, bpp) ((lin * width + col) * bpp)

/* Source and sink pad checks */
#घोषणा VIMC_IS_SRC(pad)	(pad)
#घोषणा VIMC_IS_SINK(pad)	(!(pad))

#घोषणा VIMC_PIX_FMT_MAX_CODES 8

/**
 * vimc_colorimetry_clamp - Adjust colorimetry parameters
 *
 * @fmt:		the poपूर्णांकer to काष्ठा v4l2_pix_क्रमmat or
 *			काष्ठा v4l2_mbus_framefmt
 *
 * Entities must check अगर colorimetry given by the userspace is valid, अगर not
 * then set them as DEFAULT
 */
#घोषणा vimc_colorimetry_clamp(fmt)					\
करो अणु									\
	अगर ((fmt)->colorspace == V4L2_COLORSPACE_DEFAULT		\
	    || (fmt)->colorspace > V4L2_COLORSPACE_DCI_P3) अणु		\
		(fmt)->colorspace = V4L2_COLORSPACE_DEFAULT;		\
		(fmt)->ycbcr_enc = V4L2_YCBCR_ENC_DEFAULT;		\
		(fmt)->quantization = V4L2_QUANTIZATION_DEFAULT;	\
		(fmt)->xfer_func = V4L2_XFER_FUNC_DEFAULT;		\
	पूर्ण								\
	अगर ((fmt)->ycbcr_enc > V4L2_YCBCR_ENC_SMPTE240M)		\
		(fmt)->ycbcr_enc = V4L2_YCBCR_ENC_DEFAULT;		\
	अगर ((fmt)->quantization > V4L2_QUANTIZATION_LIM_RANGE)		\
		(fmt)->quantization = V4L2_QUANTIZATION_DEFAULT;	\
	अगर ((fmt)->xfer_func > V4L2_XFER_FUNC_SMPTE2084)		\
		(fmt)->xfer_func = V4L2_XFER_FUNC_DEFAULT;		\
पूर्ण जबतक (0)

/**
 * काष्ठा vimc_pix_map - maps media bus code with v4l2 pixel क्रमmat
 *
 * @code:		media bus क्रमmat code defined by MEDIA_BUS_FMT_* macros
 * @bpp:		number of bytes each pixel occupies
 * @pixelक्रमmat:	pixel क्रमmat defined by V4L2_PIX_FMT_* macros
 * @bayer:		true अगर this is a bayer क्रमmat
 *
 * Struct which matches the MEDIA_BUS_FMT_* codes with the corresponding
 * V4L2_PIX_FMT_* fourcc pixelक्रमmat and its bytes per pixel (bpp)
 */
काष्ठा vimc_pix_map अणु
	अचिन्हित पूर्णांक code[VIMC_PIX_FMT_MAX_CODES];
	अचिन्हित पूर्णांक bpp;
	u32 pixelक्रमmat;
	bool bayer;
पूर्ण;

/**
 * काष्ठा vimc_ent_device - core काष्ठा that represents an entity in the
 * topology
 *
 * @dev:		a poपूर्णांकer of the device काष्ठा of the driver
 * @ent:		the poपूर्णांकer to काष्ठा media_entity क्रम the node
 * @process_frame:	callback send a frame to that node
 * @vdev_get_क्रमmat:	callback that वापसs the current क्रमmat a pad, used
 *			only when is_media_entity_v4l2_video_device(ent) वापसs
 *			true
 *
 * Each node of the topology must create a vimc_ent_device काष्ठा. Depending on
 * the node it will be of an instance of v4l2_subdev or video_device काष्ठा
 * where both contains a काष्ठा media_entity.
 * Those काष्ठाures should embedded the vimc_ent_device काष्ठा through
 * v4l2_set_subdevdata() and video_set_drvdata() respectively, allowing the
 * vimc_ent_device काष्ठा to be retrieved from the corresponding काष्ठा
 * media_entity
 */
काष्ठा vimc_ent_device अणु
	काष्ठा device *dev;
	काष्ठा media_entity *ent;
	व्योम * (*process_frame)(काष्ठा vimc_ent_device *ved,
				स्थिर व्योम *frame);
	व्योम (*vdev_get_क्रमmat)(काष्ठा vimc_ent_device *ved,
			      काष्ठा v4l2_pix_क्रमmat *fmt);
पूर्ण;

/**
 * काष्ठा vimc_device - मुख्य device क्रम vimc driver
 *
 * @pipe_cfg:	poपूर्णांकer to the vimc pipeline configuration काष्ठाure
 * @ent_devs:	array of vimc_ent_device poपूर्णांकers
 * @mdev:	the associated media_device parent
 * @v4l2_dev:	Internal v4l2 parent device
 */
काष्ठा vimc_device अणु
	स्थिर काष्ठा vimc_pipeline_config *pipe_cfg;
	काष्ठा vimc_ent_device **ent_devs;
	काष्ठा media_device mdev;
	काष्ठा v4l2_device v4l2_dev;
पूर्ण;

/**
 * काष्ठा vimc_ent_type		Structure क्रम the callbacks of the entity types
 *
 *
 * @add:			initializes and रेजिस्टरs
 *				vimc entity - called from vimc-core
 * @unरेजिस्टर:			unरेजिस्टरs vimc entity - called from vimc-core
 * @release:			releases vimc entity - called from the v4l2_dev
 *				release callback
 */
काष्ठा vimc_ent_type अणु
	काष्ठा vimc_ent_device *(*add)(काष्ठा vimc_device *vimc,
				       स्थिर अक्षर *vcfg_name);
	व्योम (*unरेजिस्टर)(काष्ठा vimc_ent_device *ved);
	व्योम (*release)(काष्ठा vimc_ent_device *ved);
पूर्ण;

/**
 * काष्ठा vimc_ent_config	Structure which describes inभागidual
 *				configuration क्रम each entity
 *
 * @name:			entity name
 * @type:			contain the callbacks of this entity type
 *
 */
काष्ठा vimc_ent_config अणु
	स्थिर अक्षर *name;
	काष्ठा vimc_ent_type *type;
पूर्ण;

/**
 * vimc_is_source - वापसs true अगर the entity has only source pads
 *
 * @ent: poपूर्णांकer to &काष्ठा media_entity
 *
 */
bool vimc_is_source(काष्ठा media_entity *ent);

बाह्य काष्ठा vimc_ent_type vimc_sen_type;
बाह्य काष्ठा vimc_ent_type vimc_deb_type;
बाह्य काष्ठा vimc_ent_type vimc_sca_type;
बाह्य काष्ठा vimc_ent_type vimc_cap_type;

/**
 * vimc_pix_map_by_index - get vimc_pix_map काष्ठा by its index
 *
 * @i:			index of the vimc_pix_map काष्ठा in vimc_pix_map_list
 */
स्थिर काष्ठा vimc_pix_map *vimc_pix_map_by_index(अचिन्हित पूर्णांक i);

/**
 * vimc_mbus_code_by_index - get mbus code by its index
 *
 * @index:		index of the mbus code in vimc_pix_map_list
 *
 * Returns 0 अगर no mbus code is found क्रम the given index.
 */
u32 vimc_mbus_code_by_index(अचिन्हित पूर्णांक index);

/**
 * vimc_pix_map_by_code - get vimc_pix_map काष्ठा by media bus code
 *
 * @code:		media bus क्रमmat code defined by MEDIA_BUS_FMT_* macros
 */
स्थिर काष्ठा vimc_pix_map *vimc_pix_map_by_code(u32 code);

/**
 * vimc_pix_map_by_pixelक्रमmat - get vimc_pix_map काष्ठा by v4l2 pixel क्रमmat
 *
 * @pixelक्रमmat:	pixel क्रमmat defined by V4L2_PIX_FMT_* macros
 */
स्थिर काष्ठा vimc_pix_map *vimc_pix_map_by_pixelक्रमmat(u32 pixelक्रमmat);

/**
 * vimc_ent_sd_रेजिस्टर - initialize and रेजिस्टर a subdev node
 *
 * @ved:	the vimc_ent_device काष्ठा to be initialize
 * @sd:		the v4l2_subdev काष्ठा to be initialize and रेजिस्टरed
 * @v4l2_dev:	the v4l2 device to रेजिस्टर the v4l2_subdev
 * @name:	name of the sub-device. Please notice that the name must be
 *		unique.
 * @function:	media entity function defined by MEDIA_ENT_F_* macros
 * @num_pads:	number of pads to initialize
 * @pads:	the array of pads of the entity, the caller should set the
 *		flags of the pads
 * @sd_ops:	poपूर्णांकer to &काष्ठा v4l2_subdev_ops.
 *
 * Helper function initialize and रेजिस्टर the काष्ठा vimc_ent_device and काष्ठा
 * v4l2_subdev which represents a subdev node in the topology
 */
पूर्णांक vimc_ent_sd_रेजिस्टर(काष्ठा vimc_ent_device *ved,
			 काष्ठा v4l2_subdev *sd,
			 काष्ठा v4l2_device *v4l2_dev,
			 स्थिर अक्षर *स्थिर name,
			 u32 function,
			 u16 num_pads,
			 काष्ठा media_pad *pads,
			 स्थिर काष्ठा v4l2_subdev_ops *sd_ops);

/**
 * vimc_vdev_link_validate - validates a media link
 *
 * @link: poपूर्णांकer to &काष्ठा media_link
 *
 * This function calls validates अगर a media link is valid क्रम streaming.
 */
पूर्णांक vimc_vdev_link_validate(काष्ठा media_link *link);

#पूर्ण_अगर
