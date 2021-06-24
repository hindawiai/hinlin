<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * u_uvc.h
 *
 * Utility definitions क्रम the uvc function
 *
 * Copyright (c) 2013-2014 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * Author: Andrzej Pietrasiewicz <andrzejtp2010@gmail.com>
 */

#अगर_अघोषित U_UVC_H
#घोषणा U_UVC_H

#समावेश <linux/mutex.h>
#समावेश <linux/usb/composite.h>
#समावेश <linux/usb/video.h>

#घोषणा fi_to_f_uvc_opts(f)	container_of(f, काष्ठा f_uvc_opts, func_inst)

काष्ठा f_uvc_opts अणु
	काष्ठा usb_function_instance			func_inst;
	अचिन्हित पूर्णांक					streaming_पूर्णांकerval;
	अचिन्हित पूर्णांक					streaming_maxpacket;
	अचिन्हित पूर्णांक					streaming_maxburst;

	अचिन्हित पूर्णांक					control_पूर्णांकerface;
	अचिन्हित पूर्णांक					streaming_पूर्णांकerface;

	/*
	 * Control descriptors array poपूर्णांकers क्रम full-/high-speed and
	 * super-speed. They poपूर्णांक by शेष to the uvc_fs_control_cls and
	 * uvc_ss_control_cls arrays respectively. Legacy gadमाला_लो must
	 * override them in their gadget bind callback.
	 */
	स्थिर काष्ठा uvc_descriptor_header * स्थिर	*fs_control;
	स्थिर काष्ठा uvc_descriptor_header * स्थिर	*ss_control;

	/*
	 * Streaming descriptors array poपूर्णांकers क्रम full-speed, high-speed and
	 * super-speed. They will poपूर्णांक to the uvc_[fhs]s_streaming_cls arrays
	 * क्रम configfs-based gadमाला_लो. Legacy gadमाला_लो must initialize them in
	 * their gadget bind callback.
	 */
	स्थिर काष्ठा uvc_descriptor_header * स्थिर	*fs_streaming;
	स्थिर काष्ठा uvc_descriptor_header * स्थिर	*hs_streaming;
	स्थिर काष्ठा uvc_descriptor_header * स्थिर	*ss_streaming;

	/* Default control descriptors क्रम configfs-based gadमाला_लो. */
	काष्ठा uvc_camera_terminal_descriptor		uvc_camera_terminal;
	काष्ठा uvc_processing_unit_descriptor		uvc_processing;
	काष्ठा uvc_output_terminal_descriptor		uvc_output_terminal;
	काष्ठा uvc_color_matching_descriptor		uvc_color_matching;

	/*
	 * Control descriptors poपूर्णांकers arrays क्रम full-/high-speed and
	 * super-speed. The first element is a configurable control header
	 * descriptor, the other elements poपूर्णांक to the fixed शेष control
	 * descriptors. Used by configfs only, must not be touched by legacy
	 * gadमाला_लो.
	 */
	काष्ठा uvc_descriptor_header			*uvc_fs_control_cls[5];
	काष्ठा uvc_descriptor_header			*uvc_ss_control_cls[5];

	/*
	 * Streaming descriptors क्रम full-speed, high-speed and super-speed.
	 * Used by configfs only, must not be touched by legacy gadमाला_लो. The
	 * arrays are allocated at runसमय as the number of descriptors isn't
	 * known in advance.
	 */
	काष्ठा uvc_descriptor_header			**uvc_fs_streaming_cls;
	काष्ठा uvc_descriptor_header			**uvc_hs_streaming_cls;
	काष्ठा uvc_descriptor_header			**uvc_ss_streaming_cls;

	/*
	 * Read/ग_लिखो access to configfs attributes is handled by configfs.
	 *
	 * This lock protects the descriptors from concurrent access by
	 * पढ़ो/ग_लिखो and symlink creation/removal.
	 */
	काष्ठा mutex			lock;
	पूर्णांक				refcnt;
पूर्ण;

#पूर्ण_अगर /* U_UVC_H */
