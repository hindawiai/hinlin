<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Xilinx Video Timing Controller
 *
 * Copyright (C) 2013-2015 Ideas on Board
 * Copyright (C) 2013-2015 Xilinx, Inc.
 *
 * Contacts: Hyun Kwon <hyun.kwon@xilinx.com>
 *           Laurent Pinअक्षरt <laurent.pinअक्षरt@ideasonboard.com>
 */

#अगर_अघोषित __XILINX_VTC_H__
#घोषणा __XILINX_VTC_H__

काष्ठा device_node;
काष्ठा xvtc_device;

#घोषणा XVTC_MAX_HSIZE			8191
#घोषणा XVTC_MAX_VSIZE			8191

काष्ठा xvtc_config अणु
	अचिन्हित पूर्णांक hblank_start;
	अचिन्हित पूर्णांक hsync_start;
	अचिन्हित पूर्णांक hsync_end;
	अचिन्हित पूर्णांक hsize;
	अचिन्हित पूर्णांक vblank_start;
	अचिन्हित पूर्णांक vsync_start;
	अचिन्हित पूर्णांक vsync_end;
	अचिन्हित पूर्णांक vsize;
पूर्ण;

काष्ठा xvtc_device *xvtc_of_get(काष्ठा device_node *np);
व्योम xvtc_put(काष्ठा xvtc_device *xvtc);

पूर्णांक xvtc_generator_start(काष्ठा xvtc_device *xvtc,
			 स्थिर काष्ठा xvtc_config *config);
पूर्णांक xvtc_generator_stop(काष्ठा xvtc_device *xvtc);

#पूर्ण_अगर /* __XILINX_VTC_H__ */
