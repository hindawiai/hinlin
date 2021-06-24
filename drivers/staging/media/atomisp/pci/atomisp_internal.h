<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Support क्रम Medअगरield PNW Camera Imaging ISP subप्रणाली.
 *
 * Copyright (c) 2010 Intel Corporation. All Rights Reserved.
 *
 * Copyright (c) 2010 Silicon Hive www.siliconhive.com.
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License version
 * 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 *
 */
#अगर_अघोषित __ATOMISP_INTERNAL_H__
#घोषणा __ATOMISP_INTERNAL_H__

#समावेश "../../include/linux/atomisp_platform.h"
#समावेश <linux/firmware.h>
#समावेश <linux/kernel.h>
#समावेश <linux/pm_qos.h>
#समावेश <linux/idr.h>

#समावेश <media/media-device.h>
#समावेश <media/v4l2-subdev.h>

/* ISP2400*/
#समावेश "ia_css_types.h"
#समावेश "sh_css_legacy.h"

#समावेश "atomisp_csi2.h"
#समावेश "atomisp_file.h"
#समावेश "atomisp_subdev.h"
#समावेश "atomisp_tpg.h"
#समावेश "atomisp_compat.h"

#समावेश "gp_device.h"
#समावेश "irq.h"
#समावेश <linux/vदो_स्मृति.h>

#घोषणा V4L2_EVENT_FRAME_END          5

#घोषणा IS_HWREVISION(isp, rev) \
	(((isp)->media_dev.hw_revision & ATOMISP_HW_REVISION_MASK) == \
	 ((rev) << ATOMISP_HW_REVISION_SHIFT))

#घोषणा MAX_STREAM_NUM	2

#घोषणा ATOMISP_PCI_DEVICE_SOC_MASK	0xfff8
/* MRFLD with 0x1178: ISP freq can burst to 457MHz */
#घोषणा ATOMISP_PCI_DEVICE_SOC_MRFLD	0x1178
/* MRFLD with 0x1179: max ISP freq limited to 400MHz */
#घोषणा ATOMISP_PCI_DEVICE_SOC_MRFLD_1179	0x1179
/* MRFLD with 0x117a: max ISP freq is 400MHz and max freq at Vmin is 200MHz */
#घोषणा ATOMISP_PCI_DEVICE_SOC_MRFLD_117A	0x117a
#घोषणा ATOMISP_PCI_DEVICE_SOC_BYT	0x0f38
#घोषणा ATOMISP_PCI_DEVICE_SOC_ANN	0x1478
#घोषणा ATOMISP_PCI_DEVICE_SOC_CHT	0x22b8

#घोषणा ATOMISP_PCI_REV_MRFLD_A0_MAX	0
#घोषणा ATOMISP_PCI_REV_BYT_A0_MAX	4

#घोषणा ATOM_ISP_STEP_WIDTH	2
#घोषणा ATOM_ISP_STEP_HEIGHT	2

#घोषणा ATOM_ISP_MIN_WIDTH	4
#घोषणा ATOM_ISP_MIN_HEIGHT	4
#घोषणा ATOM_ISP_MAX_WIDTH	अच_पूर्णांक_उच्च
#घोषणा ATOM_ISP_MAX_HEIGHT	अच_पूर्णांक_उच्च

/* sub-QCIF resolution */
#घोषणा ATOM_RESOLUTION_SUBQCIF_WIDTH	128
#घोषणा ATOM_RESOLUTION_SUBQCIF_HEIGHT	96

#घोषणा ATOM_ISP_MAX_WIDTH_TMP	1280
#घोषणा ATOM_ISP_MAX_HEIGHT_TMP	720

#घोषणा ATOM_ISP_I2C_BUS_1	4
#घोषणा ATOM_ISP_I2C_BUS_2	5

#घोषणा ATOM_ISP_POWER_DOWN	0
#घोषणा ATOM_ISP_POWER_UP	1

#घोषणा ATOM_ISP_MAX_INPUTS	4

#घोषणा ATOMISP_SC_TYPE_SIZE	2

#घोषणा ATOMISP_ISP_TIMEOUT_DURATION		(2 * HZ)
#घोषणा ATOMISP_EXT_ISP_TIMEOUT_DURATION        (6 * HZ)
#घोषणा ATOMISP_ISP_खाता_TIMEOUT_DURATION	(60 * HZ)
#घोषणा ATOMISP_WDT_KEEP_CURRENT_DELAY          0
#घोषणा ATOMISP_ISP_MAX_TIMEOUT_COUNT	2
#घोषणा ATOMISP_CSS_STOP_TIMEOUT_US	200000

#घोषणा ATOMISP_CSS_Q_DEPTH	3
#घोषणा ATOMISP_CSS_EVENTS_MAX  16
#घोषणा ATOMISP_CONT_RAW_FRAMES 15
#घोषणा ATOMISP_METADATA_QUEUE_DEPTH_FOR_HAL	8
#घोषणा ATOMISP_S3A_BUF_QUEUE_DEPTH_FOR_HAL	8

#घोषणा ATOMISP_DELAYED_INIT_NOT_QUEUED	0
#घोषणा ATOMISP_DELAYED_INIT_QUEUED	1
#घोषणा ATOMISP_DELAYED_INIT_DONE	2

#घोषणा ATOMISP_CALC_CSS_PREV_OVERLAP(lines) \
	((lines) * 38 / 100 & 0xfffffe)

/*
 * Define how fast CPU should be able to serve ISP पूर्णांकerrupts.
 * The bigger the value, the higher risk that the ISP is not
 * triggered sufficiently fast क्रम it to process image during
 * vertical blanking समय, increasing risk of dropped frames.
 * 1000 us is a reasonable value considering that the processing
 * समय is typically ~2000 us.
 */
#घोषणा ATOMISP_MAX_ISR_LATENCY	1000

/* Add new YUVPP pipe क्रम SOC sensor. */
#घोषणा ATOMISP_CSS_SUPPORT_YUVPP     1

#घोषणा ATOMISP_CSS_OUTPUT_SECOND_INDEX     1
#घोषणा ATOMISP_CSS_OUTPUT_DEFAULT_INDEX    0

/*
 * ATOMISP_SOC_CAMERA
 * This is to dअगरferentiate between ext-isp and soc camera in
 * Moorefield/Baytrail platक्रमm.
 */
#घोषणा ATOMISP_SOC_CAMERA(asd)  \
	(asd->isp->inमाला_दो[asd->input_curr].type == SOC_CAMERA \
	&& asd->isp->inमाला_दो[asd->input_curr].camera_caps-> \
	   sensor[asd->sensor_curr].stream_num == 1)

#घोषणा ATOMISP_USE_YUVPP(asd)  \
	(ATOMISP_SOC_CAMERA(asd) && ATOMISP_CSS_SUPPORT_YUVPP && \
	!asd->copy_mode)

#घोषणा ATOMISP_DEPTH_SENSOR_STREAMON_COUNT 2

#घोषणा ATOMISP_DEPTH_DEFAULT_MASTER_SENSOR 0
#घोषणा ATOMISP_DEPTH_DEFAULT_SLAVE_SENSOR 1

/* ISP2401 */
#घोषणा ATOMISP_ION_DEVICE_FD_OFFSET   16
#घोषणा ATOMISP_ION_SHARED_FD_MASK     (0xFFFF)
#घोषणा ATOMISP_ION_DEVICE_FD_MASK     (~ATOMISP_ION_SHARED_FD_MASK)
#घोषणा ION_FD_UNSET (-1)

#घोषणा DIV_NEAREST_STEP(n, d, step) \
	round_करोwn((2 * (n) + (d) * (step)) / (2 * (d)), (step))

काष्ठा atomisp_input_subdev अणु
	अचिन्हित पूर्णांक type;
	क्रमागत atomisp_camera_port port;
	काष्ठा v4l2_subdev *camera;
	काष्ठा v4l2_subdev *motor;
	काष्ठा v4l2_frmsizeक्रमागत frame_size;

	/*
	 * To show this resource is used by
	 * which stream, in ISP multiple stream mode
	 */
	काष्ठा atomisp_sub_device *asd;

	स्थिर काष्ठा atomisp_camera_caps *camera_caps;
	पूर्णांक sensor_index;
पूर्ण;

क्रमागत atomisp_dfs_mode अणु
	ATOMISP_DFS_MODE_AUTO = 0,
	ATOMISP_DFS_MODE_LOW,
	ATOMISP_DFS_MODE_MAX,
पूर्ण;

काष्ठा atomisp_regs अणु
	/* PCI config space info */
	u16 pcicmdsts;
	u32 ispmmadr;
	u32 msicap;
	u32 msi_addr;
	u16 msi_data;
	u8 पूर्णांकr;
	u32 पूर्णांकerrupt_control;
	u32 pmcs;
	u32 cg_dis;
	u32 i_control;

	/* I-Unit PHY related info */
	u32 csi_rcomp_config;
	u32 csi_afe_dly;
	u32 csi_control;

	/* New क्रम MRFLD */
	u32 csi_afe_rcomp_config;
	u32 csi_afe_hs_control;
	u32 csi_deadline_control;
	u32 csi_access_viol;
पूर्ण;

काष्ठा atomisp_sw_contex अणु
	bool file_input;
	पूर्णांक घातer_state;
	पूर्णांक running_freq;
पूर्ण;

#घोषणा ATOMISP_DEVICE_STREAMING_DISABLED	0
#घोषणा ATOMISP_DEVICE_STREAMING_ENABLED	1
#घोषणा ATOMISP_DEVICE_STREAMING_STOPPING	2

/*
 * ci device काष्ठा
 */
काष्ठा atomisp_device अणु
	काष्ठा device *dev;
	काष्ठा v4l2_device v4l2_dev;
	काष्ठा media_device media_dev;
	काष्ठा atomisp_platक्रमm_data *pdata;
	व्योम *mmu_l1_base;
	व्योम __iomem *base;
	स्थिर काष्ठा firmware *firmware;

	काष्ठा pm_qos_request pm_qos;
	s32 max_isr_latency;

	/*
	 * ISP modules
	 * Multiple streams are represents by multiple
	 * atomisp_sub_device instances
	 */
	काष्ठा atomisp_sub_device *asd;
	/*
	 * this will be asचिन्हित dyanamically.
	 * For Merr/BTY(ISP2400), 2 streams are supported.
	 */
	अचिन्हित पूर्णांक num_of_streams;

	काष्ठा atomisp_mipi_csi2_device csi2_port[ATOMISP_CAMERA_NR_PORTS];
	काष्ठा atomisp_tpg_device tpg;
	काष्ठा atomisp_file_device file_dev;

	/* Purpose of mutex is to protect and serialize use of isp data
	 * काष्ठाures and css API calls. */
	काष्ठा rt_mutex mutex;
	/*
	 * Serialise streamoff: mutex is dropped during streamoff to
	 * cancel the watchकरोg queue. MUST be acquired BEFORE
	 * "mutex".
	 */
	काष्ठा mutex streamoff_mutex;

	अचिन्हित पूर्णांक input_cnt;
	काष्ठा atomisp_input_subdev inमाला_दो[ATOM_ISP_MAX_INPUTS];
	काष्ठा v4l2_subdev *flash;
	काष्ठा v4l2_subdev *motor;

	काष्ठा atomisp_regs saved_regs;
	काष्ठा atomisp_sw_contex sw_contex;
	काष्ठा atomisp_css_env css_env;

	/* isp समयout status flag */
	bool isp_समयout;
	bool isp_fatal_error;
	काष्ठा workqueue_काष्ठा *wdt_work_queue;
	काष्ठा work_काष्ठा wdt_work;

	/* ISP2400 */
	atomic_t wdt_count;

	atomic_t wdt_work_queued;

	spinlock_t lock; /* Just क्रम streaming below */

	bool need_gfx_throttle;

	अचिन्हित पूर्णांक mipi_frame_size;
	स्थिर काष्ठा atomisp_dfs_config *dfs;
	अचिन्हित पूर्णांक hpll_freq;

	bool css_initialized;
पूर्ण;

#घोषणा v4l2_dev_to_atomisp_device(dev) \
	container_of(dev, काष्ठा atomisp_device, v4l2_dev)

बाह्य काष्ठा device *atomisp_dev;

#घोषणा atomisp_is_wdt_running(a) समयr_pending(&(a)->wdt)

/* ISP2401 */
व्योम atomisp_wdt_refresh_pipe(काष्ठा atomisp_video_pipe *pipe,
			      अचिन्हित पूर्णांक delay);
व्योम atomisp_wdt_refresh(काष्ठा atomisp_sub_device *asd, अचिन्हित पूर्णांक delay);

/* ISP2400 */
व्योम atomisp_wdt_start(काष्ठा atomisp_sub_device *asd);

/* ISP2401 */
व्योम atomisp_wdt_start_pipe(काष्ठा atomisp_video_pipe *pipe);
व्योम atomisp_wdt_stop_pipe(काष्ठा atomisp_video_pipe *pipe, bool sync);

व्योम atomisp_wdt_stop(काष्ठा atomisp_sub_device *asd, bool sync);

#पूर्ण_अगर /* __ATOMISP_INTERNAL_H__ */
