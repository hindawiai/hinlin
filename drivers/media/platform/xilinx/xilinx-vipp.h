<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Xilinx Video IP Composite Device
 *
 * Copyright (C) 2013-2015 Ideas on Board
 * Copyright (C) 2013-2015 Xilinx, Inc.
 *
 * Contacts: Hyun Kwon <hyun.kwon@xilinx.com>
 *           Laurent Pinअक्षरt <laurent.pinअक्षरt@ideasonboard.com>
 */

#अगर_अघोषित __XILINX_VIPP_H__
#घोषणा __XILINX_VIPP_H__

#समावेश <linux/list.h>
#समावेश <linux/mutex.h>
#समावेश <media/media-device.h>
#समावेश <media/v4l2-async.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>

/**
 * काष्ठा xvip_composite_device - Xilinx Video IP device काष्ठाure
 * @v4l2_dev: V4L2 device
 * @media_dev: media device
 * @dev: (OF) device
 * @notअगरier: V4L2 asynchronous subdevs notअगरier
 * @dmas: list of DMA channels at the pipeline output and input
 * @v4l2_caps: V4L2 capabilities of the whole device (see VIDIOC_QUERYCAP)
 */
काष्ठा xvip_composite_device अणु
	काष्ठा v4l2_device v4l2_dev;
	काष्ठा media_device media_dev;
	काष्ठा device *dev;

	काष्ठा v4l2_async_notअगरier notअगरier;

	काष्ठा list_head dmas;
	u32 v4l2_caps;
पूर्ण;

#पूर्ण_अगर /* __XILINX_VIPP_H__ */
