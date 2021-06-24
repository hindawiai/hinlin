<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Greybus Camera protocol driver.
 *
 * Copyright 2015 Google Inc.
 */
#अगर_अघोषित __GB_CAMERA_H
#घोषणा __GB_CAMERA_H

#समावेश <linux/v4l2-mediabus.h>

/* Input flags need to be set from the caller */
#घोषणा GB_CAMERA_IN_FLAG_TEST		(1 << 0)
/* Output flags वापसed */
#घोषणा GB_CAMERA_OUT_FLAG_ADJUSTED	(1 << 0)

/**
 * काष्ठा gb_camera_stream - Represents greybus camera stream.
 * @width: Stream width in pixels.
 * @height: Stream height in pixels.
 * @pixel_code: Media bus pixel code.
 * @vc: MIPI CSI भव channel.
 * @dt: MIPI CSI data types. Most क्रमmats use a single data type, in which हाल
 *      the second element will be ignored.
 * @max_size: Maximum size of a frame in bytes. The camera module guarantees
 *            that all data between the Frame Start and Frame End packet क्रम
 *            the associated भव channel and data type(s) will not exceed
 *            this size.
 */
काष्ठा gb_camera_stream अणु
	अचिन्हित पूर्णांक width;
	अचिन्हित पूर्णांक height;
	क्रमागत v4l2_mbus_pixelcode pixel_code;
	अचिन्हित पूर्णांक vc;
	अचिन्हित पूर्णांक dt[2];
	अचिन्हित पूर्णांक max_size;
पूर्ण;

/**
 * काष्ठा gb_camera_csi_params - CSI configuration parameters
 * @num_lanes: number of CSI data lanes
 * @clk_freq: CSI घड़ी frequency in Hz
 */
काष्ठा gb_camera_csi_params अणु
	अचिन्हित पूर्णांक num_lanes;
	अचिन्हित पूर्णांक clk_freq;
पूर्ण;

/**
 * काष्ठा gb_camera_ops - Greybus camera operations, used by the Greybus camera
 *                        driver to expose operations to the host camera driver.
 * @capabilities: Retrieve camera capabilities and store them in the buffer
 *                'buf' capabilities. The buffer maximum size is specअगरied by
 *                the caller in the 'size' parameter, and the effective
 *                capabilities size is वापसed from the function. If the buffer
 *                size is too small to hold the capabilities an error is
 *                वापसed and the buffer is left untouched.
 *
 * @configure_streams: Negotiate configuration and prepare the module क्रम video
 *                     capture. The caller specअगरies the number of streams it
 *                     requests in the 'nstreams' argument and the associated
 *                     streams configurations in the 'streams' argument. The
 *                     GB_CAMERA_IN_FLAG_TEST 'flag' can be set to test a
 *                     configuration without applying it, otherwise the
 *                     configuration is applied by the module. The module can
 *                     decide to modअगरy the requested configuration, including
 *                     using a dअगरferent number of streams. In that हाल the
 *                     modअगरied configuration won't be applied, the
 *                     GB_CAMERA_OUT_FLAG_ADJUSTED 'flag' will be set upon
 *                     वापस, and the modअगरied configuration and number of
 *                     streams stored in 'streams' and 'array'. The module
 *                     वापसs its CSI-2 bus parameters in the 'csi_params'
 *                     काष्ठाure in all हालs.
 *
 * @capture: Submit a capture request. The supplied 'request_id' must be unique
 *           and higher than the IDs of all the previously submitted requests.
 *           The 'streams' argument specअगरies which streams are affected by the
 *           request in the क्रमm of a biपंचांगask, with bits corresponding to the
 *           configured streams indexes. If the request contains settings, the
 *           'settings' argument poपूर्णांकs to the settings buffer and its size is
 *           specअगरied by the 'settings_size' argument. Otherwise the 'settings'
 *           argument should be set to शून्य and 'settings_size' to 0.
 *
 * @flush: Flush the capture requests queue. Return the ID of the last request
 *         that will processed by the device beक्रमe it stops transmitting video
 *         frames. All queued capture requests with IDs higher than the वापसed
 *         ID will be dropped without being processed.
 */
काष्ठा gb_camera_ops अणु
	sमाप_प्रकार (*capabilities)(व्योम *priv, अक्षर *buf, माप_प्रकार len);
	पूर्णांक (*configure_streams)(व्योम *priv, अचिन्हित पूर्णांक *nstreams,
			अचिन्हित पूर्णांक *flags, काष्ठा gb_camera_stream *streams,
			काष्ठा gb_camera_csi_params *csi_params);
	पूर्णांक (*capture)(व्योम *priv, u32 request_id,
			अचिन्हित पूर्णांक streams, अचिन्हित पूर्णांक num_frames,
			माप_प्रकार settings_size, स्थिर व्योम *settings);
	पूर्णांक (*flush)(व्योम *priv, u32 *request_id);
पूर्ण;

/**
 * काष्ठा gb_camera_module - Represents greybus camera module.
 * @priv: Module निजी data, passed to all camera operations.
 * @ops: Greybus camera operation callbacks.
 * @पूर्णांकerface_id: Interface id of the module.
 * @refcount: Reference counting object.
 * @release: Module release function.
 * @list: List entry in the camera modules list.
 */
काष्ठा gb_camera_module अणु
	व्योम *priv;
	स्थिर काष्ठा gb_camera_ops *ops;

	अचिन्हित पूर्णांक पूर्णांकerface_id;
	काष्ठा kref refcount;
	व्योम (*release)(काष्ठा kref *kref);
	काष्ठा list_head list; /* Global list */
पूर्ण;

#घोषणा gb_camera_call(f, op, args...)      \
	(!(f) ? -ENODEV : (((f)->ops->op) ?  \
	(f)->ops->op((f)->priv, ##args) : -ENOIOCTLCMD))

पूर्णांक gb_camera_रेजिस्टर(काष्ठा gb_camera_module *module);
पूर्णांक gb_camera_unरेजिस्टर(काष्ठा gb_camera_module *module);

#पूर्ण_अगर /* __GB_CAMERA_H */
