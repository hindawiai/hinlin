<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Samsung S5P/Exynos4 SoC series camera पूर्णांकerface driver header
 *
 * Copyright (C) 2010 - 2013 Samsung Electronics Co., Ltd.
 * Sylwester Nawrocki <s.nawrocki@samsung.com>
 */

#अगर_अघोषित S5P_FIMC_H_
#घोषणा S5P_FIMC_H_

#समावेश <media/media-entity.h>
#समावेश <media/v4l2-dev.h>
#समावेश <media/v4l2-mediabus.h>

/*
 * Enumeration of data inमाला_दो to the camera subप्रणाली.
 */
क्रमागत fimc_input अणु
	FIMC_INPUT_PARALLEL_0	= 1,
	FIMC_INPUT_PARALLEL_1,
	FIMC_INPUT_MIPI_CSI2_0	= 3,
	FIMC_INPUT_MIPI_CSI2_1,
	FIMC_INPUT_WRITEBACK_A	= 5,
	FIMC_INPUT_WRITEBACK_B,
	FIMC_INPUT_WRITEBACK_ISP = 5,
पूर्ण;

/*
 * Enumeration of the FIMC data bus types.
 */
क्रमागत fimc_bus_type अणु
	/* Camera parallel bus */
	FIMC_BUS_TYPE_ITU_601 = 1,
	/* Camera parallel bus with embedded synchronization */
	FIMC_BUS_TYPE_ITU_656,
	/* Camera MIPI-CSI2 serial bus */
	FIMC_BUS_TYPE_MIPI_CSI2,
	/* FIFO link from LCD controller (WriteBack A) */
	FIMC_BUS_TYPE_LCD_WRITEBACK_A,
	/* FIFO link from LCD controller (WriteBack B) */
	FIMC_BUS_TYPE_LCD_WRITEBACK_B,
	/* FIFO link from FIMC-IS */
	FIMC_BUS_TYPE_ISP_WRITEBACK = FIMC_BUS_TYPE_LCD_WRITEBACK_B,
पूर्ण;

#घोषणा fimc_input_is_parallel(x) ((x) == 1 || (x) == 2)
#घोषणा fimc_input_is_mipi_csi(x) ((x) == 3 || (x) == 4)

/*
 * The subdevices' group IDs.
 */
#घोषणा GRP_ID_SENSOR		(1 << 8)
#घोषणा GRP_ID_FIMC_IS_SENSOR	(1 << 9)
#घोषणा GRP_ID_WRITEBACK	(1 << 10)
#घोषणा GRP_ID_CSIS		(1 << 11)
#घोषणा GRP_ID_FIMC		(1 << 12)
#घोषणा GRP_ID_FLITE		(1 << 13)
#घोषणा GRP_ID_FIMC_IS		(1 << 14)

/**
 * काष्ठा fimc_source_info - video source description required क्रम the host
 *			     पूर्णांकerface configuration
 *
 * @fimc_bus_type: FIMC camera input type
 * @sensor_bus_type: image sensor bus type, MIPI, ITU-R BT.601 etc.
 * @flags: the parallel sensor bus flags defining संकेतs polarity (V4L2_MBUS_*)
 * @mux_id: FIMC camera पूर्णांकerface multiplexer index (separate क्रम MIPI and ITU)
 */
काष्ठा fimc_source_info अणु
	क्रमागत fimc_bus_type fimc_bus_type;
	क्रमागत fimc_bus_type sensor_bus_type;
	u16 flags;
	u16 mux_id;
पूर्ण;

/*
 * v4l2_device notअगरication id. This is only क्रम पूर्णांकernal use in the kernel.
 * Sensor subdevs should issue S5P_FIMC_TX_END_NOTIFY notअगरication in single
 * frame capture mode when there is only one VSYNC pulse issued by the sensor
 * at beginning of the frame transmission.
 */
#घोषणा S5P_FIMC_TX_END_NOTIFY _IO('e', 0)

#घोषणा FIMC_MAX_PLANES	3

/**
 * काष्ठा fimc_fmt - color क्रमmat data काष्ठाure
 * @mbus_code: media bus pixel code, -1 अगर not applicable
 * @fourcc: fourcc code क्रम this क्रमmat, 0 अगर not applicable
 * @color: the driver's निजी color क्रमmat id
 * @memplanes: number of physically non-contiguous data planes
 * @colplanes: number of physically contiguous data planes
 * @colorspace: v4l2 colorspace (V4L2_COLORSPACE_*)
 * @depth: per plane driver's private 'number of bits per pixel'
 * @mdataplanes: biपंचांगask indicating meta data plane(s), (1 << plane_no)
 * @flags: flags indicating which operation mode क्रमmat applies to
 */
काष्ठा fimc_fmt अणु
	u32 mbus_code;
	u32	fourcc;
	u32	color;
	u16	memplanes;
	u16	colplanes;
	u8	colorspace;
	u8	depth[FIMC_MAX_PLANES];
	u16	mdataplanes;
	u16	flags;
#घोषणा FMT_FLAGS_CAM		(1 << 0)
#घोषणा FMT_FLAGS_M2M_IN	(1 << 1)
#घोषणा FMT_FLAGS_M2M_OUT	(1 << 2)
#घोषणा FMT_FLAGS_M2M		(1 << 1 | 1 << 2)
#घोषणा FMT_HAS_ALPHA		(1 << 3)
#घोषणा FMT_FLAGS_COMPRESSED	(1 << 4)
#घोषणा FMT_FLAGS_WRITEBACK	(1 << 5)
#घोषणा FMT_FLAGS_RAW_BAYER	(1 << 6)
#घोषणा FMT_FLAGS_YUV		(1 << 7)
पूर्ण;

काष्ठा exynos_media_pipeline;

/*
 * Media pipeline operations to be called from within a video node,  i.e. the
 * last entity within the pipeline. Implemented by related media device driver.
 */
काष्ठा exynos_media_pipeline_ops अणु
	पूर्णांक (*prepare)(काष्ठा exynos_media_pipeline *p,
						काष्ठा media_entity *me);
	पूर्णांक (*unprepare)(काष्ठा exynos_media_pipeline *p);
	पूर्णांक (*खोलो)(काष्ठा exynos_media_pipeline *p, काष्ठा media_entity *me,
							bool resume);
	पूर्णांक (*बंद)(काष्ठा exynos_media_pipeline *p);
	पूर्णांक (*set_stream)(काष्ठा exynos_media_pipeline *p, bool state);
पूर्ण;

काष्ठा exynos_video_entity अणु
	काष्ठा video_device vdev;
	काष्ठा exynos_media_pipeline *pipe;
पूर्ण;

काष्ठा exynos_media_pipeline अणु
	काष्ठा media_pipeline mp;
	स्थिर काष्ठा exynos_media_pipeline_ops *ops;
पूर्ण;

अटल अंतरभूत काष्ठा exynos_video_entity *vdev_to_exynos_video_entity(
					काष्ठा video_device *vdev)
अणु
	वापस container_of(vdev, काष्ठा exynos_video_entity, vdev);
पूर्ण

#घोषणा fimc_pipeline_call(ent, op, args...)				  \
	((!(ent) || !(ent)->pipe) ? -ENOENT : \
	(((ent)->pipe->ops && (ent)->pipe->ops->op) ? \
	(ent)->pipe->ops->op(((ent)->pipe), ##args) : -ENOIOCTLCMD))	  \

#पूर्ण_अगर /* S5P_FIMC_H_ */
