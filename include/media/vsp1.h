<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * vsp1.h  --  R-Car VSP1 API
 *
 * Copyright (C) 2015 Renesas Electronics Corporation
 *
 * Contact: Laurent Pinअक्षरt (laurent.pinअक्षरt@ideasonboard.com)
 */
#अगर_अघोषित __MEDIA_VSP1_H__
#घोषणा __MEDIA_VSP1_H__

#समावेश <linux/scatterlist.h>
#समावेश <linux/types.h>
#समावेश <linux/videodev2.h>

काष्ठा device;

पूर्णांक vsp1_du_init(काष्ठा device *dev);

#घोषणा VSP1_DU_STATUS_COMPLETE		BIT(0)
#घोषणा VSP1_DU_STATUS_WRITEBACK	BIT(1)

/**
 * काष्ठा vsp1_du_lअगर_config - VSP LIF configuration
 * @width: output frame width
 * @height: output frame height
 * @पूर्णांकerlaced: true क्रम पूर्णांकerlaced pipelines
 * @callback: frame completion callback function (optional). When a callback
 *	      is provided, the VSP driver guarantees that it will be called once
 *	      and only once क्रम each vsp1_du_atomic_flush() call.
 * @callback_data: data to be passed to the frame completion callback
 */
काष्ठा vsp1_du_lअगर_config अणु
	अचिन्हित पूर्णांक width;
	अचिन्हित पूर्णांक height;
	bool पूर्णांकerlaced;

	व्योम (*callback)(व्योम *data, अचिन्हित पूर्णांक status, u32 crc);
	व्योम *callback_data;
पूर्ण;

पूर्णांक vsp1_du_setup_lअगर(काष्ठा device *dev, अचिन्हित पूर्णांक pipe_index,
		      स्थिर काष्ठा vsp1_du_lअगर_config *cfg);

/**
 * काष्ठा vsp1_du_atomic_config - VSP atomic configuration parameters
 * @pixelक्रमmat: plane pixel क्रमmat (V4L2 4CC)
 * @pitch: line pitch in bytes क्रम the first plane
 * @mem: DMA memory address क्रम each plane of the frame buffer
 * @src: source rectangle in the frame buffer (पूर्णांकeger coordinates)
 * @dst: destination rectangle on the display (पूर्णांकeger coordinates)
 * @alpha: alpha value (0: fully transparent, 255: fully opaque)
 * @zpos: Z position of the plane (from 0 to number of planes minus 1)
 */
काष्ठा vsp1_du_atomic_config अणु
	u32 pixelक्रमmat;
	अचिन्हित पूर्णांक pitch;
	dma_addr_t mem[3];
	काष्ठा v4l2_rect src;
	काष्ठा v4l2_rect dst;
	अचिन्हित पूर्णांक alpha;
	अचिन्हित पूर्णांक zpos;
पूर्ण;

/**
 * क्रमागत vsp1_du_crc_source - Source used क्रम CRC calculation
 * @VSP1_DU_CRC_NONE: CRC calculation disabled
 * @VSP1_DU_CRC_PLANE: Perक्रमm CRC calculation on an input plane
 * @VSP1_DU_CRC_OUTPUT: Perक्रमm CRC calculation on the composed output
 */
क्रमागत vsp1_du_crc_source अणु
	VSP1_DU_CRC_NONE,
	VSP1_DU_CRC_PLANE,
	VSP1_DU_CRC_OUTPUT,
पूर्ण;

/**
 * काष्ठा vsp1_du_crc_config - VSP CRC computation configuration parameters
 * @source: source क्रम CRC calculation
 * @index: index of the CRC source plane (when source is set to plane)
 */
काष्ठा vsp1_du_crc_config अणु
	क्रमागत vsp1_du_crc_source source;
	अचिन्हित पूर्णांक index;
पूर्ण;

/**
 * काष्ठा vsp1_du_ग_लिखोback_config - VSP ग_लिखोback configuration parameters
 * @pixelक्रमmat: plane pixel क्रमmat (V4L2 4CC)
 * @pitch: line pitch in bytes क्रम the first plane
 * @mem: DMA memory address क्रम each plane of the frame buffer
 */
काष्ठा vsp1_du_ग_लिखोback_config अणु
	u32 pixelक्रमmat;
	अचिन्हित पूर्णांक pitch;
	dma_addr_t mem[3];
पूर्ण;

/**
 * काष्ठा vsp1_du_atomic_pipe_config - VSP atomic pipe configuration parameters
 * @crc: CRC computation configuration
 * @ग_लिखोback: ग_लिखोback configuration
 */
काष्ठा vsp1_du_atomic_pipe_config अणु
	काष्ठा vsp1_du_crc_config crc;
	काष्ठा vsp1_du_ग_लिखोback_config ग_लिखोback;
पूर्ण;

व्योम vsp1_du_atomic_begin(काष्ठा device *dev, अचिन्हित पूर्णांक pipe_index);
पूर्णांक vsp1_du_atomic_update(काष्ठा device *dev, अचिन्हित पूर्णांक pipe_index,
			  अचिन्हित पूर्णांक rpf,
			  स्थिर काष्ठा vsp1_du_atomic_config *cfg);
व्योम vsp1_du_atomic_flush(काष्ठा device *dev, अचिन्हित पूर्णांक pipe_index,
			  स्थिर काष्ठा vsp1_du_atomic_pipe_config *cfg);
पूर्णांक vsp1_du_map_sg(काष्ठा device *dev, काष्ठा sg_table *sgt);
व्योम vsp1_du_unmap_sg(काष्ठा device *dev, काष्ठा sg_table *sgt);

#पूर्ण_अगर /* __MEDIA_VSP1_H__ */
