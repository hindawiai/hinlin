<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Greybus Camera protocol driver.
 *
 * Copyright 2015 Google Inc.
 * Copyright 2015 Linaro Ltd.
 */

#समावेश <linux/debugfs.h>
#समावेश <linux/fs.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/uaccess.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/greybus.h>

#समावेश "gb-camera.h"
#समावेश "greybus_protocols.h"

क्रमागत gb_camera_debugs_buffer_id अणु
	GB_CAMERA_DEBUGFS_BUFFER_CAPABILITIES,
	GB_CAMERA_DEBUGFS_BUFFER_STREAMS,
	GB_CAMERA_DEBUGFS_BUFFER_CAPTURE,
	GB_CAMERA_DEBUGFS_BUFFER_FLUSH,
	GB_CAMERA_DEBUGFS_BUFFER_MAX,
पूर्ण;

काष्ठा gb_camera_debugfs_buffer अणु
	अक्षर data[PAGE_SIZE];
	माप_प्रकार length;
पूर्ण;

क्रमागत gb_camera_state अणु
	GB_CAMERA_STATE_UNCONFIGURED,
	GB_CAMERA_STATE_CONFIGURED,
पूर्ण;

/**
 * काष्ठा gb_camera - A Greybus Camera Device
 * @connection: the greybus connection क्रम camera management
 * @data_connection: the greybus connection क्रम camera data
 * @data_cport_id: the data CPort ID on the module side
 * @mutex: protects the connection and state fields
 * @state: the current module state
 * @debugfs: debugfs entries क्रम camera protocol operations testing
 * @module: Greybus camera module रेजिस्टरed to HOST processor.
 */
काष्ठा gb_camera अणु
	काष्ठा gb_bundle *bundle;
	काष्ठा gb_connection *connection;
	काष्ठा gb_connection *data_connection;
	u16 data_cport_id;

	काष्ठा mutex mutex;
	क्रमागत gb_camera_state state;

	काष्ठा अणु
		काष्ठा dentry *root;
		काष्ठा gb_camera_debugfs_buffer *buffers;
	पूर्ण debugfs;

	काष्ठा gb_camera_module module;
पूर्ण;

काष्ठा gb_camera_stream_config अणु
	अचिन्हित पूर्णांक width;
	अचिन्हित पूर्णांक height;
	अचिन्हित पूर्णांक क्रमmat;
	अचिन्हित पूर्णांक vc;
	अचिन्हित पूर्णांक dt[2];
	अचिन्हित पूर्णांक max_size;
पूर्ण;

काष्ठा gb_camera_fmt_info अणु
	क्रमागत v4l2_mbus_pixelcode mbus_code;
	अचिन्हित पूर्णांक gb_क्रमmat;
	अचिन्हित पूर्णांक bpp;
पूर्ण;

/* GB क्रमmat to media code map */
अटल स्थिर काष्ठा gb_camera_fmt_info gb_fmt_info[] = अणु
	अणु
		.mbus_code = V4L2_MBUS_FMT_UYVY8_1X16,
		.gb_क्रमmat = 0x01,
		.bpp	   = 16,
	पूर्ण,
	अणु
		.mbus_code = V4L2_MBUS_FMT_NV12_1x8,
		.gb_क्रमmat = 0x12,
		.bpp	   = 12,
	पूर्ण,
	अणु
		.mbus_code = V4L2_MBUS_FMT_NV21_1x8,
		.gb_क्रमmat = 0x13,
		.bpp	   = 12,
	पूर्ण,
	अणु
		.mbus_code = V4L2_MBUS_FMT_YU12_1x8,
		.gb_क्रमmat = 0x16,
		.bpp	   = 12,
	पूर्ण,
	अणु
		.mbus_code = V4L2_MBUS_FMT_YV12_1x8,
		.gb_क्रमmat = 0x17,
		.bpp	   = 12,
	पूर्ण,
	अणु
		.mbus_code = V4L2_MBUS_FMT_JPEG_1X8,
		.gb_क्रमmat = 0x40,
		.bpp	   = 0,
	पूर्ण,
	अणु
		.mbus_code = V4L2_MBUS_FMT_GB_CAM_METADATA_1X8,
		.gb_क्रमmat = 0x41,
		.bpp	   = 0,
	पूर्ण,
	अणु
		.mbus_code = V4L2_MBUS_FMT_GB_CAM_DEBUG_DATA_1X8,
		.gb_क्रमmat = 0x42,
		.bpp	   = 0,
	पूर्ण,
	अणु
		.mbus_code = V4L2_MBUS_FMT_SBGGR10_1X10,
		.gb_क्रमmat = 0x80,
		.bpp	   = 10,
	पूर्ण,
	अणु
		.mbus_code = V4L2_MBUS_FMT_SGBRG10_1X10,
		.gb_क्रमmat = 0x81,
		.bpp	   = 10,
	पूर्ण,
	अणु
		.mbus_code = V4L2_MBUS_FMT_SGRBG10_1X10,
		.gb_क्रमmat = 0x82,
		.bpp	   = 10,
	पूर्ण,
	अणु
		.mbus_code = V4L2_MBUS_FMT_SRGGB10_1X10,
		.gb_क्रमmat = 0x83,
		.bpp	   = 10,
	पूर्ण,
	अणु
		.mbus_code = V4L2_MBUS_FMT_SBGGR12_1X12,
		.gb_क्रमmat = 0x84,
		.bpp	   = 12,
	पूर्ण,
	अणु
		.mbus_code = V4L2_MBUS_FMT_SGBRG12_1X12,
		.gb_क्रमmat = 0x85,
		.bpp	   = 12,
	पूर्ण,
	अणु
		.mbus_code = V4L2_MBUS_FMT_SGRBG12_1X12,
		.gb_क्रमmat = 0x86,
		.bpp	   = 12,
	पूर्ण,
	अणु
		.mbus_code = V4L2_MBUS_FMT_SRGGB12_1X12,
		.gb_क्रमmat = 0x87,
		.bpp	   = 12,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा gb_camera_fmt_info *gb_camera_get_क्रमmat_info(u16 gb_fmt)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(gb_fmt_info); i++) अणु
		अगर (gb_fmt_info[i].gb_क्रमmat == gb_fmt)
			वापस &gb_fmt_info[i];
	पूर्ण

	वापस शून्य;
पूर्ण

#घोषणा ES2_APB_CDSI0_CPORT		16
#घोषणा ES2_APB_CDSI1_CPORT		17

#घोषणा GB_CAMERA_MAX_SETTINGS_SIZE	8192

#घोषणा gcam_dbg(gcam, क्रमmat...)	dev_dbg(&gcam->bundle->dev, क्रमmat)
#घोषणा gcam_info(gcam, क्रमmat...)	dev_info(&gcam->bundle->dev, क्रमmat)
#घोषणा gcam_err(gcam, क्रमmat...)	dev_err(&gcam->bundle->dev, क्रमmat)

अटल पूर्णांक gb_camera_operation_sync_flags(काष्ठा gb_connection *connection,
					  पूर्णांक type, अचिन्हित पूर्णांक flags,
					  व्योम *request, माप_प्रकार request_size,
					  व्योम *response, माप_प्रकार *response_size)
अणु
	काष्ठा gb_operation *operation;
	पूर्णांक ret;

	operation = gb_operation_create_flags(connection, type, request_size,
					      *response_size, flags,
					      GFP_KERNEL);
	अगर (!operation)
		वापस  -ENOMEM;

	अगर (request_size)
		स_नकल(operation->request->payload, request, request_size);

	ret = gb_operation_request_send_sync(operation);
	अगर (ret) अणु
		dev_err(&connection->hd->dev,
			"%s: synchronous operation of type 0x%02x failed: %d\n",
			connection->name, type, ret);
	पूर्ण अन्यथा अणु
		*response_size = operation->response->payload_size;

		अगर (operation->response->payload_size)
			स_नकल(response, operation->response->payload,
			       operation->response->payload_size);
	पूर्ण

	gb_operation_put(operation);

	वापस ret;
पूर्ण

अटल पूर्णांक gb_camera_get_max_pkt_size(काष्ठा gb_camera *gcam,
		काष्ठा gb_camera_configure_streams_response *resp)
अणु
	अचिन्हित पूर्णांक max_pkt_size = 0;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < resp->num_streams; i++) अणु
		काष्ठा gb_camera_stream_config_response *cfg = &resp->config[i];
		स्थिर काष्ठा gb_camera_fmt_info *fmt_info;
		अचिन्हित पूर्णांक pkt_size;

		fmt_info = gb_camera_get_क्रमmat_info(cfg->क्रमmat);
		अगर (!fmt_info) अणु
			gcam_err(gcam, "unsupported greybus image format: %d\n",
				 cfg->क्रमmat);
			वापस -EIO;
		पूर्ण

		अगर (fmt_info->bpp == 0) अणु
			pkt_size = le32_to_cpu(cfg->max_pkt_size);

			अगर (pkt_size == 0) अणु
				gcam_err(gcam,
					 "Stream %u: invalid zero maximum packet size\n",
					 i);
				वापस -EIO;
			पूर्ण
		पूर्ण अन्यथा अणु
			pkt_size = le16_to_cpu(cfg->width) * fmt_info->bpp / 8;

			अगर (pkt_size != le32_to_cpu(cfg->max_pkt_size)) अणु
				gcam_err(gcam,
					 "Stream %u: maximum packet size mismatch (%u/%u)\n",
					 i, pkt_size, cfg->max_pkt_size);
				वापस -EIO;
			पूर्ण
		पूर्ण

		max_pkt_size = max(pkt_size, max_pkt_size);
	पूर्ण

	वापस max_pkt_size;
पूर्ण

/*
 * Validate the stream configuration response verअगरying padding is correctly
 * set and the वापसed number of streams is supported
 */
अटल स्थिर पूर्णांक gb_camera_configure_streams_validate_response(
		काष्ठा gb_camera *gcam,
		काष्ठा gb_camera_configure_streams_response *resp,
		अचिन्हित पूर्णांक nstreams)
अणु
	अचिन्हित पूर्णांक i;

	/* Validate the वापसed response काष्ठाure */
	अगर (resp->padding[0] || resp->padding[1]) अणु
		gcam_err(gcam, "response padding != 0\n");
		वापस -EIO;
	पूर्ण

	अगर (resp->num_streams > nstreams) अणु
		gcam_err(gcam, "got #streams %u > request %u\n",
			 resp->num_streams, nstreams);
		वापस -EIO;
	पूर्ण

	क्रम (i = 0; i < resp->num_streams; i++) अणु
		काष्ठा gb_camera_stream_config_response *cfg = &resp->config[i];

		अगर (cfg->padding) अणु
			gcam_err(gcam, "stream #%u padding != 0\n", i);
			वापस -EIO;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* -----------------------------------------------------------------------------
 * Hardware Configuration
 */

अटल पूर्णांक gb_camera_set_पूर्णांकf_घातer_mode(काष्ठा gb_camera *gcam, u8 पूर्णांकf_id,
					 bool hs)
अणु
	काष्ठा gb_svc *svc = gcam->connection->hd->svc;
	पूर्णांक ret;

	अगर (hs)
		ret = gb_svc_पूर्णांकf_set_घातer_mode(svc, पूर्णांकf_id,
						 GB_SVC_UNIPRO_HS_SERIES_A,
						 GB_SVC_UNIPRO_FAST_MODE, 2, 2,
						 GB_SVC_SMALL_AMPLITUDE,
						 GB_SVC_NO_DE_EMPHASIS,
						 GB_SVC_UNIPRO_FAST_MODE, 2, 2,
						 GB_SVC_PWRM_RXTERMINATION |
						 GB_SVC_PWRM_TXTERMINATION, 0,
						 शून्य, शून्य);
	अन्यथा
		ret = gb_svc_पूर्णांकf_set_घातer_mode(svc, पूर्णांकf_id,
						 GB_SVC_UNIPRO_HS_SERIES_A,
						 GB_SVC_UNIPRO_SLOW_AUTO_MODE,
						 2, 1,
						 GB_SVC_SMALL_AMPLITUDE,
						 GB_SVC_NO_DE_EMPHASIS,
						 GB_SVC_UNIPRO_SLOW_AUTO_MODE,
						 2, 1,
						 0, 0,
						 शून्य, शून्य);

	वापस ret;
पूर्ण

अटल पूर्णांक gb_camera_set_घातer_mode(काष्ठा gb_camera *gcam, bool hs)
अणु
	काष्ठा gb_पूर्णांकerface *पूर्णांकf = gcam->connection->पूर्णांकf;
	काष्ठा gb_svc *svc = gcam->connection->hd->svc;
	पूर्णांक ret;

	ret = gb_camera_set_पूर्णांकf_घातer_mode(gcam, पूर्णांकf->पूर्णांकerface_id, hs);
	अगर (ret < 0) अणु
		gcam_err(gcam, "failed to set module interface to %s (%d)\n",
			 hs ? "HS" : "PWM", ret);
		वापस ret;
	पूर्ण

	ret = gb_camera_set_पूर्णांकf_घातer_mode(gcam, svc->ap_पूर्णांकf_id, hs);
	अगर (ret < 0) अणु
		gb_camera_set_पूर्णांकf_घातer_mode(gcam, पूर्णांकf->पूर्णांकerface_id, !hs);
		gcam_err(gcam, "failed to set AP interface to %s (%d)\n",
			 hs ? "HS" : "PWM", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा ap_csi_config_request अणु
	__u8 csi_id;
	__u8 flags;
#घोषणा GB_CAMERA_CSI_FLAG_CLOCK_CONTINUOUS 0x01
	__u8 num_lanes;
	__u8 padding;
	__le32 csi_clk_freq;
	__le32 max_pkt_size;
पूर्ण __packed;

/*
 * TODO: Compute the number of lanes dynamically based on bandwidth
 * requirements.
 */
#घोषणा GB_CAMERA_CSI_NUM_DATA_LANES		4

#घोषणा GB_CAMERA_CSI_CLK_FREQ_MAX		999000000U
#घोषणा GB_CAMERA_CSI_CLK_FREQ_MIN		100000000U
#घोषणा GB_CAMERA_CSI_CLK_FREQ_MARGIN		150000000U

अटल पूर्णांक gb_camera_setup_data_connection(काष्ठा gb_camera *gcam,
		काष्ठा gb_camera_configure_streams_response *resp,
		काष्ठा gb_camera_csi_params *csi_params)
अणु
	काष्ठा ap_csi_config_request csi_cfg;
	काष्ठा gb_connection *conn;
	अचिन्हित पूर्णांक clk_freq;
	पूर्णांक ret;

	/*
	 * Create the data connection between the camera module data CPort and
	 * APB CDSI1. The CDSI1 CPort ID is hardcoded by the ES2 bridge.
	 */
	conn = gb_connection_create_offloaded(gcam->bundle, gcam->data_cport_id,
					      GB_CONNECTION_FLAG_NO_FLOWCTRL |
					      GB_CONNECTION_FLAG_CDSI1);
	अगर (IS_ERR(conn))
		वापस PTR_ERR(conn);

	gcam->data_connection = conn;
	gb_connection_set_data(conn, gcam);

	ret = gb_connection_enable(conn);
	अगर (ret)
		जाओ error_conn_destroy;

	/* Set the UniPro link to high speed mode. */
	ret = gb_camera_set_घातer_mode(gcam, true);
	अगर (ret < 0)
		जाओ error_conn_disable;

	/*
	 * Configure the APB-A CSI-2 transmitter.
	 *
	 * Hardcode the number of lanes to 4 and compute the bus घड़ी frequency
	 * based on the module bandwidth requirements with a safety margin.
	 */
	स_रखो(&csi_cfg, 0, माप(csi_cfg));
	csi_cfg.csi_id = 1;
	csi_cfg.flags = 0;
	csi_cfg.num_lanes = GB_CAMERA_CSI_NUM_DATA_LANES;

	clk_freq = resp->data_rate / 2 / GB_CAMERA_CSI_NUM_DATA_LANES;
	clk_freq = clamp(clk_freq + GB_CAMERA_CSI_CLK_FREQ_MARGIN,
			 GB_CAMERA_CSI_CLK_FREQ_MIN,
			 GB_CAMERA_CSI_CLK_FREQ_MAX);
	csi_cfg.csi_clk_freq = clk_freq;

	ret = gb_camera_get_max_pkt_size(gcam, resp);
	अगर (ret < 0) अणु
		ret = -EIO;
		जाओ error_घातer;
	पूर्ण
	csi_cfg.max_pkt_size = ret;

	ret = gb_hd_output(gcam->connection->hd, &csi_cfg,
			   माप(csi_cfg),
			   GB_APB_REQUEST_CSI_TX_CONTROL, false);
	अगर (ret < 0) अणु
		gcam_err(gcam, "failed to start the CSI transmitter\n");
		जाओ error_घातer;
	पूर्ण

	अगर (csi_params) अणु
		csi_params->clk_freq = csi_cfg.csi_clk_freq;
		csi_params->num_lanes = csi_cfg.num_lanes;
	पूर्ण

	वापस 0;

error_घातer:
	gb_camera_set_घातer_mode(gcam, false);
error_conn_disable:
	gb_connection_disable(gcam->data_connection);
error_conn_destroy:
	gb_connection_destroy(gcam->data_connection);
	gcam->data_connection = शून्य;
	वापस ret;
पूर्ण

अटल व्योम gb_camera_tearकरोwn_data_connection(काष्ठा gb_camera *gcam)
अणु
	काष्ठा ap_csi_config_request csi_cfg;
	पूर्णांक ret;

	/* Stop the APB1 CSI transmitter. */
	स_रखो(&csi_cfg, 0, माप(csi_cfg));
	csi_cfg.csi_id = 1;

	ret = gb_hd_output(gcam->connection->hd, &csi_cfg,
			   माप(csi_cfg),
			   GB_APB_REQUEST_CSI_TX_CONTROL, false);

	अगर (ret < 0)
		gcam_err(gcam, "failed to stop the CSI transmitter\n");

	/* Set the UniPro link to low speed mode. */
	gb_camera_set_घातer_mode(gcam, false);

	/* Destroy the data connection. */
	gb_connection_disable(gcam->data_connection);
	gb_connection_destroy(gcam->data_connection);
	gcam->data_connection = शून्य;
पूर्ण

/* -----------------------------------------------------------------------------
 * Camera Protocol Operations
 */

अटल पूर्णांक gb_camera_capabilities(काष्ठा gb_camera *gcam,
				  u8 *capabilities, माप_प्रकार *size)
अणु
	पूर्णांक ret;

	ret = gb_pm_runसमय_get_sync(gcam->bundle);
	अगर (ret)
		वापस ret;

	mutex_lock(&gcam->mutex);

	अगर (!gcam->connection) अणु
		ret = -EINVAL;
		जाओ करोne;
	पूर्ण

	ret = gb_camera_operation_sync_flags(gcam->connection,
					     GB_CAMERA_TYPE_CAPABILITIES,
					     GB_OPERATION_FLAG_SHORT_RESPONSE,
					     शून्य, 0,
					     (व्योम *)capabilities, size);
	अगर (ret)
		gcam_err(gcam, "failed to retrieve capabilities: %d\n", ret);

करोne:
	mutex_unlock(&gcam->mutex);

	gb_pm_runसमय_put_स्वतःsuspend(gcam->bundle);

	वापस ret;
पूर्ण

अटल पूर्णांक gb_camera_configure_streams(काष्ठा gb_camera *gcam,
				       अचिन्हित पूर्णांक *num_streams,
				       अचिन्हित पूर्णांक *flags,
				       काष्ठा gb_camera_stream_config *streams,
				       काष्ठा gb_camera_csi_params *csi_params)
अणु
	काष्ठा gb_camera_configure_streams_request *req;
	काष्ठा gb_camera_configure_streams_response *resp;
	अचिन्हित पूर्णांक nstreams = *num_streams;
	अचिन्हित पूर्णांक i;
	माप_प्रकार req_size;
	माप_प्रकार resp_size;
	पूर्णांक ret;

	अगर (nstreams > GB_CAMERA_MAX_STREAMS)
		वापस -EINVAL;

	req_size = माप(*req) + nstreams * माप(req->config[0]);
	resp_size = माप(*resp) + nstreams * माप(resp->config[0]);

	req = kदो_स्मृति(req_size, GFP_KERNEL);
	resp = kदो_स्मृति(resp_size, GFP_KERNEL);
	अगर (!req || !resp) अणु
		kमुक्त(req);
		kमुक्त(resp);
		वापस -ENOMEM;
	पूर्ण

	req->num_streams = nstreams;
	req->flags = *flags;
	req->padding = 0;

	क्रम (i = 0; i < nstreams; ++i) अणु
		काष्ठा gb_camera_stream_config_request *cfg = &req->config[i];

		cfg->width = cpu_to_le16(streams[i].width);
		cfg->height = cpu_to_le16(streams[i].height);
		cfg->क्रमmat = cpu_to_le16(streams[i].क्रमmat);
		cfg->padding = 0;
	पूर्ण

	mutex_lock(&gcam->mutex);

	ret = gb_pm_runसमय_get_sync(gcam->bundle);
	अगर (ret)
		जाओ करोne_skip_pm_put;

	अगर (!gcam->connection) अणु
		ret = -EINVAL;
		जाओ करोne;
	पूर्ण

	ret = gb_camera_operation_sync_flags(gcam->connection,
					     GB_CAMERA_TYPE_CONFIGURE_STREAMS,
					     GB_OPERATION_FLAG_SHORT_RESPONSE,
					     req, req_size,
					     resp, &resp_size);
	अगर (ret < 0)
		जाओ करोne;

	ret = gb_camera_configure_streams_validate_response(gcam, resp,
							    nstreams);
	अगर (ret < 0)
		जाओ करोne;

	*flags = resp->flags;
	*num_streams = resp->num_streams;

	क्रम (i = 0; i < resp->num_streams; ++i) अणु
		काष्ठा gb_camera_stream_config_response *cfg = &resp->config[i];

		streams[i].width = le16_to_cpu(cfg->width);
		streams[i].height = le16_to_cpu(cfg->height);
		streams[i].क्रमmat = le16_to_cpu(cfg->क्रमmat);
		streams[i].vc = cfg->भव_channel;
		streams[i].dt[0] = cfg->data_type[0];
		streams[i].dt[1] = cfg->data_type[1];
		streams[i].max_size = le32_to_cpu(cfg->max_size);
	पूर्ण

	अगर ((resp->flags & GB_CAMERA_CONFIGURE_STREAMS_ADJUSTED) ||
	    (req->flags & GB_CAMERA_CONFIGURE_STREAMS_TEST_ONLY))
		जाओ करोne;

	अगर (gcam->state == GB_CAMERA_STATE_CONFIGURED) अणु
		gb_camera_tearकरोwn_data_connection(gcam);
		gcam->state = GB_CAMERA_STATE_UNCONFIGURED;

		/*
		 * When unconfiguring streams release the PM runसमय reference
		 * that was acquired when streams were configured. The bundle
		 * won't be suspended until the PM runसमय reference acquired at
		 * the beginning of this function माला_लो released right beक्रमe
		 * वापसing.
		 */
		gb_pm_runसमय_put_noidle(gcam->bundle);
	पूर्ण

	अगर (resp->num_streams == 0)
		जाओ करोne;

	/*
	 * Make sure the bundle won't be suspended until streams get
	 * unconfigured after the stream is configured successfully
	 */
	gb_pm_runसमय_get_noresume(gcam->bundle);

	/* Setup CSI-2 connection from APB-A to AP */
	ret = gb_camera_setup_data_connection(gcam, resp, csi_params);
	अगर (ret < 0) अणु
		स_रखो(req, 0, माप(*req));
		gb_operation_sync(gcam->connection,
				  GB_CAMERA_TYPE_CONFIGURE_STREAMS,
				  req, माप(*req),
				  resp, माप(*resp));
		*flags = 0;
		*num_streams = 0;
		gb_pm_runसमय_put_noidle(gcam->bundle);
		जाओ करोne;
	पूर्ण

	gcam->state = GB_CAMERA_STATE_CONFIGURED;

करोne:
	gb_pm_runसमय_put_स्वतःsuspend(gcam->bundle);

करोne_skip_pm_put:
	mutex_unlock(&gcam->mutex);
	kमुक्त(req);
	kमुक्त(resp);
	वापस ret;
पूर्ण

अटल पूर्णांक gb_camera_capture(काष्ठा gb_camera *gcam, u32 request_id,
			     अचिन्हित पूर्णांक streams, अचिन्हित पूर्णांक num_frames,
			     माप_प्रकार settings_size, स्थिर व्योम *settings)
अणु
	काष्ठा gb_camera_capture_request *req;
	माप_प्रकार req_size;
	पूर्णांक ret;

	अगर (settings_size > GB_CAMERA_MAX_SETTINGS_SIZE)
		वापस -EINVAL;

	req_size = माप(*req) + settings_size;
	req = kदो_स्मृति(req_size, GFP_KERNEL);
	अगर (!req)
		वापस -ENOMEM;

	req->request_id = cpu_to_le32(request_id);
	req->streams = streams;
	req->padding = 0;
	req->num_frames = cpu_to_le16(num_frames);
	स_नकल(req->settings, settings, settings_size);

	mutex_lock(&gcam->mutex);

	अगर (!gcam->connection) अणु
		ret = -EINVAL;
		जाओ करोne;
	पूर्ण

	ret = gb_operation_sync(gcam->connection, GB_CAMERA_TYPE_CAPTURE,
				req, req_size, शून्य, 0);
करोne:
	mutex_unlock(&gcam->mutex);

	kमुक्त(req);

	वापस ret;
पूर्ण

अटल पूर्णांक gb_camera_flush(काष्ठा gb_camera *gcam, u32 *request_id)
अणु
	काष्ठा gb_camera_flush_response resp;
	पूर्णांक ret;

	mutex_lock(&gcam->mutex);

	अगर (!gcam->connection) अणु
		ret = -EINVAL;
		जाओ करोne;
	पूर्ण

	ret = gb_operation_sync(gcam->connection, GB_CAMERA_TYPE_FLUSH, शून्य, 0,
				&resp, माप(resp));

	अगर (ret < 0)
		जाओ करोne;

	अगर (request_id)
		*request_id = le32_to_cpu(resp.request_id);

करोne:
	mutex_unlock(&gcam->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक gb_camera_request_handler(काष्ठा gb_operation *op)
अणु
	काष्ठा gb_camera *gcam = gb_connection_get_data(op->connection);
	काष्ठा gb_camera_metadata_request *payload;
	काष्ठा gb_message *request;

	अगर (op->type != GB_CAMERA_TYPE_METADATA) अणु
		gcam_err(gcam, "Unsupported unsolicited event: %u\n", op->type);
		वापस -EINVAL;
	पूर्ण

	request = op->request;

	अगर (request->payload_size < माप(*payload)) अणु
		gcam_err(gcam, "Wrong event size received (%zu < %zu)\n",
			 request->payload_size, माप(*payload));
		वापस -EINVAL;
	पूर्ण

	payload = request->payload;

	gcam_dbg(gcam, "received metadata for request %u, frame %u, stream %u\n",
		 payload->request_id, payload->frame_number, payload->stream);

	वापस 0;
पूर्ण

/* -----------------------------------------------------------------------------
 * Interface with HOST gmp camera.
 */
अटल अचिन्हित पूर्णांक gb_camera_mbus_to_gb(क्रमागत v4l2_mbus_pixelcode mbus_code)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(gb_fmt_info); i++) अणु
		अगर (gb_fmt_info[i].mbus_code == mbus_code)
			वापस gb_fmt_info[i].gb_क्रमmat;
	पूर्ण
	वापस gb_fmt_info[0].gb_क्रमmat;
पूर्ण

अटल क्रमागत v4l2_mbus_pixelcode gb_camera_gb_to_mbus(u16 gb_fmt)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(gb_fmt_info); i++) अणु
		अगर (gb_fmt_info[i].gb_क्रमmat == gb_fmt)
			वापस gb_fmt_info[i].mbus_code;
	पूर्ण
	वापस gb_fmt_info[0].mbus_code;
पूर्ण

अटल sमाप_प्रकार gb_camera_op_capabilities(व्योम *priv, अक्षर *data, माप_प्रकार len)
अणु
	काष्ठा gb_camera *gcam = priv;
	माप_प्रकार capabilities_len = len;
	पूर्णांक ret;

	ret = gb_camera_capabilities(gcam, data, &capabilities_len);
	अगर (ret)
		वापस ret;

	वापस capabilities_len;
पूर्ण

अटल पूर्णांक gb_camera_op_configure_streams(व्योम *priv, अचिन्हित पूर्णांक *nstreams,
		अचिन्हित पूर्णांक *flags, काष्ठा gb_camera_stream *streams,
		काष्ठा gb_camera_csi_params *csi_params)
अणु
	काष्ठा gb_camera *gcam = priv;
	काष्ठा gb_camera_stream_config *gb_streams;
	अचिन्हित पूर्णांक gb_flags = 0;
	अचिन्हित पूर्णांक gb_nstreams = *nstreams;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	अगर (gb_nstreams > GB_CAMERA_MAX_STREAMS)
		वापस -EINVAL;

	gb_streams = kसुस्मृति(gb_nstreams, माप(*gb_streams), GFP_KERNEL);
	अगर (!gb_streams)
		वापस -ENOMEM;

	क्रम (i = 0; i < gb_nstreams; i++) अणु
		gb_streams[i].width = streams[i].width;
		gb_streams[i].height = streams[i].height;
		gb_streams[i].क्रमmat =
			gb_camera_mbus_to_gb(streams[i].pixel_code);
	पूर्ण

	अगर (*flags & GB_CAMERA_IN_FLAG_TEST)
		gb_flags |= GB_CAMERA_CONFIGURE_STREAMS_TEST_ONLY;

	ret = gb_camera_configure_streams(gcam, &gb_nstreams,
					  &gb_flags, gb_streams, csi_params);
	अगर (ret < 0)
		जाओ करोne;
	अगर (gb_nstreams > *nstreams) अणु
		ret = -EINVAL;
		जाओ करोne;
	पूर्ण

	*flags = 0;
	अगर (gb_flags & GB_CAMERA_CONFIGURE_STREAMS_ADJUSTED)
		*flags |= GB_CAMERA_OUT_FLAG_ADJUSTED;

	क्रम (i = 0; i < gb_nstreams; i++) अणु
		streams[i].width = gb_streams[i].width;
		streams[i].height = gb_streams[i].height;
		streams[i].vc = gb_streams[i].vc;
		streams[i].dt[0] = gb_streams[i].dt[0];
		streams[i].dt[1] = gb_streams[i].dt[1];
		streams[i].max_size = gb_streams[i].max_size;
		streams[i].pixel_code =
			gb_camera_gb_to_mbus(gb_streams[i].क्रमmat);
	पूर्ण
	*nstreams = gb_nstreams;

करोne:
	kमुक्त(gb_streams);
	वापस ret;
पूर्ण

अटल पूर्णांक gb_camera_op_capture(व्योम *priv, u32 request_id,
				अचिन्हित पूर्णांक streams, अचिन्हित पूर्णांक num_frames,
				माप_प्रकार settings_size, स्थिर व्योम *settings)
अणु
	काष्ठा gb_camera *gcam = priv;

	वापस gb_camera_capture(gcam, request_id, streams, num_frames,
				 settings_size, settings);
पूर्ण

अटल पूर्णांक gb_camera_op_flush(व्योम *priv, u32 *request_id)
अणु
	काष्ठा gb_camera *gcam = priv;

	वापस gb_camera_flush(gcam, request_id);
पूर्ण

अटल स्थिर काष्ठा gb_camera_ops gb_cam_ops = अणु
	.capabilities = gb_camera_op_capabilities,
	.configure_streams = gb_camera_op_configure_streams,
	.capture = gb_camera_op_capture,
	.flush = gb_camera_op_flush,
पूर्ण;

/* -----------------------------------------------------------------------------
 * DebugFS
 */

अटल sमाप_प्रकार gb_camera_debugfs_capabilities(काष्ठा gb_camera *gcam,
					      अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा gb_camera_debugfs_buffer *buffer =
		&gcam->debugfs.buffers[GB_CAMERA_DEBUGFS_BUFFER_CAPABILITIES];
	माप_प्रकार size = 1024;
	अचिन्हित पूर्णांक i;
	u8 *caps;
	पूर्णांक ret;

	caps = kदो_स्मृति(size, GFP_KERNEL);
	अगर (!caps)
		वापस -ENOMEM;

	ret = gb_camera_capabilities(gcam, caps, &size);
	अगर (ret < 0)
		जाओ करोne;

	/*
	 * hex_dump_to_buffer() करोesn't वापस the number of bytes dumped prior
	 * to v4.0, we need our own implementation :-(
	 */
	buffer->length = 0;

	क्रम (i = 0; i < size; i += 16) अणु
		अचिन्हित पूर्णांक nbytes = min_t(अचिन्हित पूर्णांक, size - i, 16);

		buffer->length += प्र_लिखो(buffer->data + buffer->length,
					  "%*ph\n", nbytes, caps + i);
	पूर्ण

करोne:
	kमुक्त(caps);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार gb_camera_debugfs_configure_streams(काष्ठा gb_camera *gcam,
						   अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा gb_camera_debugfs_buffer *buffer =
		&gcam->debugfs.buffers[GB_CAMERA_DEBUGFS_BUFFER_STREAMS];
	काष्ठा gb_camera_stream_config *streams;
	अचिन्हित पूर्णांक nstreams;
	अचिन्हित पूर्णांक flags;
	अचिन्हित पूर्णांक i;
	अक्षर *token;
	पूर्णांक ret;

	/* Retrieve number of streams to configure */
	token = strsep(&buf, ";");
	अगर (!token)
		वापस -EINVAL;

	ret = kstrtouपूर्णांक(token, 10, &nstreams);
	अगर (ret < 0)
		वापस ret;

	अगर (nstreams > GB_CAMERA_MAX_STREAMS)
		वापस -EINVAL;

	token = strsep(&buf, ";");
	अगर (!token)
		वापस -EINVAL;

	ret = kstrtouपूर्णांक(token, 10, &flags);
	अगर (ret < 0)
		वापस ret;

	/* For each stream to configure parse width, height and क्रमmat */
	streams = kसुस्मृति(nstreams, माप(*streams), GFP_KERNEL);
	अगर (!streams)
		वापस -ENOMEM;

	क्रम (i = 0; i < nstreams; ++i) अणु
		काष्ठा gb_camera_stream_config *stream = &streams[i];

		/* width */
		token = strsep(&buf, ";");
		अगर (!token) अणु
			ret = -EINVAL;
			जाओ करोne;
		पूर्ण
		ret = kstrtouपूर्णांक(token, 10, &stream->width);
		अगर (ret < 0)
			जाओ करोne;

		/* height */
		token = strsep(&buf, ";");
		अगर (!token)
			जाओ करोne;

		ret = kstrtouपूर्णांक(token, 10, &stream->height);
		अगर (ret < 0)
			जाओ करोne;

		/* Image क्रमmat code */
		token = strsep(&buf, ";");
		अगर (!token)
			जाओ करोne;

		ret = kstrtouपूर्णांक(token, 16, &stream->क्रमmat);
		अगर (ret < 0)
			जाओ करोne;
	पूर्ण

	ret = gb_camera_configure_streams(gcam, &nstreams, &flags, streams,
					  शून्य);
	अगर (ret < 0)
		जाओ करोne;

	buffer->length = प्र_लिखो(buffer->data, "%u;%u;", nstreams, flags);

	क्रम (i = 0; i < nstreams; ++i) अणु
		काष्ठा gb_camera_stream_config *stream = &streams[i];

		buffer->length += प्र_लिखो(buffer->data + buffer->length,
					  "%u;%u;%u;%u;%u;%u;%u;",
					  stream->width, stream->height,
					  stream->क्रमmat, stream->vc,
					  stream->dt[0], stream->dt[1],
					  stream->max_size);
	पूर्ण

	ret = len;

करोne:
	kमुक्त(streams);
	वापस ret;
पूर्ण;

अटल sमाप_प्रकार gb_camera_debugfs_capture(काष्ठा gb_camera *gcam,
					 अक्षर *buf, माप_प्रकार len)
अणु
	अचिन्हित पूर्णांक request_id;
	अचिन्हित पूर्णांक streams_mask;
	अचिन्हित पूर्णांक num_frames;
	अक्षर *token;
	पूर्णांक ret;

	/* Request id */
	token = strsep(&buf, ";");
	अगर (!token)
		वापस -EINVAL;
	ret = kstrtouपूर्णांक(token, 10, &request_id);
	अगर (ret < 0)
		वापस ret;

	/* Stream mask */
	token = strsep(&buf, ";");
	अगर (!token)
		वापस -EINVAL;
	ret = kstrtouपूर्णांक(token, 16, &streams_mask);
	अगर (ret < 0)
		वापस ret;

	/* number of frames */
	token = strsep(&buf, ";");
	अगर (!token)
		वापस -EINVAL;
	ret = kstrtouपूर्णांक(token, 10, &num_frames);
	अगर (ret < 0)
		वापस ret;

	ret = gb_camera_capture(gcam, request_id, streams_mask, num_frames, 0,
				शून्य);
	अगर (ret < 0)
		वापस ret;

	वापस len;
पूर्ण

अटल sमाप_प्रकार gb_camera_debugfs_flush(काष्ठा gb_camera *gcam,
				       अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा gb_camera_debugfs_buffer *buffer =
		&gcam->debugfs.buffers[GB_CAMERA_DEBUGFS_BUFFER_FLUSH];
	अचिन्हित पूर्णांक req_id;
	पूर्णांक ret;

	ret = gb_camera_flush(gcam, &req_id);
	अगर (ret < 0)
		वापस ret;

	buffer->length = प्र_लिखो(buffer->data, "%u", req_id);

	वापस len;
पूर्ण

काष्ठा gb_camera_debugfs_entry अणु
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक mask;
	अचिन्हित पूर्णांक buffer;
	sमाप_प्रकार (*execute)(काष्ठा gb_camera *gcam, अक्षर *buf, माप_प्रकार len);
पूर्ण;

अटल स्थिर काष्ठा gb_camera_debugfs_entry gb_camera_debugfs_entries[] = अणु
	अणु
		.name = "capabilities",
		.mask = S_IFREG | 0444,
		.buffer = GB_CAMERA_DEBUGFS_BUFFER_CAPABILITIES,
		.execute = gb_camera_debugfs_capabilities,
	पूर्ण, अणु
		.name = "configure_streams",
		.mask = S_IFREG | 0666,
		.buffer = GB_CAMERA_DEBUGFS_BUFFER_STREAMS,
		.execute = gb_camera_debugfs_configure_streams,
	पूर्ण, अणु
		.name = "capture",
		.mask = S_IFREG | 0666,
		.buffer = GB_CAMERA_DEBUGFS_BUFFER_CAPTURE,
		.execute = gb_camera_debugfs_capture,
	पूर्ण, अणु
		.name = "flush",
		.mask = S_IFREG | 0666,
		.buffer = GB_CAMERA_DEBUGFS_BUFFER_FLUSH,
		.execute = gb_camera_debugfs_flush,
	पूर्ण,
पूर्ण;

अटल sमाप_प्रकार gb_camera_debugfs_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
				      माप_प्रकार len, loff_t *offset)
अणु
	स्थिर काष्ठा gb_camera_debugfs_entry *op = file->निजी_data;
	काष्ठा gb_camera *gcam = file_inode(file)->i_निजी;
	काष्ठा gb_camera_debugfs_buffer *buffer;
	sमाप_प्रकार ret;

	/* For पढ़ो-only entries the operation is triggered by a पढ़ो. */
	अगर (!(op->mask & 0222)) अणु
		ret = op->execute(gcam, शून्य, 0);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	buffer = &gcam->debugfs.buffers[op->buffer];

	वापस simple_पढ़ो_from_buffer(buf, len, offset, buffer->data,
				       buffer->length);
पूर्ण

अटल sमाप_प्रकार gb_camera_debugfs_ग_लिखो(काष्ठा file *file,
				       स्थिर अक्षर __user *buf, माप_प्रकार len,
				       loff_t *offset)
अणु
	स्थिर काष्ठा gb_camera_debugfs_entry *op = file->निजी_data;
	काष्ठा gb_camera *gcam = file_inode(file)->i_निजी;
	sमाप_प्रकार ret;
	अक्षर *kbuf;

	अगर (len > 1024)
		वापस -EINVAL;

	kbuf = memdup_user_nul(buf, len);
	अगर (IS_ERR(kbuf))
		वापस PTR_ERR(kbuf);

	ret = op->execute(gcam, kbuf, len);

करोne:
	kमुक्त(kbuf);
	वापस ret;
पूर्ण

अटल पूर्णांक gb_camera_debugfs_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(gb_camera_debugfs_entries); ++i) अणु
		स्थिर काष्ठा gb_camera_debugfs_entry *entry =
			&gb_camera_debugfs_entries[i];

		अगर (!म_भेद(file->f_path.dentry->d_iname, entry->name)) अणु
			file->निजी_data = (व्योम *)entry;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations gb_camera_debugfs_ops = अणु
	.खोलो = gb_camera_debugfs_खोलो,
	.पढ़ो = gb_camera_debugfs_पढ़ो,
	.ग_लिखो = gb_camera_debugfs_ग_लिखो,
पूर्ण;

अटल पूर्णांक gb_camera_debugfs_init(काष्ठा gb_camera *gcam)
अणु
	काष्ठा gb_connection *connection = gcam->connection;
	अक्षर स_नाम[27];
	अचिन्हित पूर्णांक i;

	/*
	 * Create root debugfs entry and a file entry क्रम each camera operation.
	 */
	snम_लिखो(स_नाम, 27, "camera-%u.%u", connection->पूर्णांकf->पूर्णांकerface_id,
		 gcam->bundle->id);

	gcam->debugfs.root = debugfs_create_dir(स_नाम, gb_debugfs_get());

	gcam->debugfs.buffers =
		vदो_स्मृति(array_size(GB_CAMERA_DEBUGFS_BUFFER_MAX,
				   माप(*gcam->debugfs.buffers)));
	अगर (!gcam->debugfs.buffers)
		वापस -ENOMEM;

	क्रम (i = 0; i < ARRAY_SIZE(gb_camera_debugfs_entries); ++i) अणु
		स्थिर काष्ठा gb_camera_debugfs_entry *entry =
			&gb_camera_debugfs_entries[i];

		gcam->debugfs.buffers[i].length = 0;

		debugfs_create_file(entry->name, entry->mask,
				    gcam->debugfs.root, gcam,
				    &gb_camera_debugfs_ops);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम gb_camera_debugfs_cleanup(काष्ठा gb_camera *gcam)
अणु
	debugfs_हटाओ_recursive(gcam->debugfs.root);

	vमुक्त(gcam->debugfs.buffers);
पूर्ण

/* -----------------------------------------------------------------------------
 * Init & Cleanup
 */

अटल व्योम gb_camera_cleanup(काष्ठा gb_camera *gcam)
अणु
	gb_camera_debugfs_cleanup(gcam);

	mutex_lock(&gcam->mutex);
	अगर (gcam->data_connection) अणु
		gb_connection_disable(gcam->data_connection);
		gb_connection_destroy(gcam->data_connection);
		gcam->data_connection = शून्य;
	पूर्ण

	अगर (gcam->connection) अणु
		gb_connection_disable(gcam->connection);
		gb_connection_destroy(gcam->connection);
		gcam->connection = शून्य;
	पूर्ण
	mutex_unlock(&gcam->mutex);
पूर्ण

अटल व्योम gb_camera_release_module(काष्ठा kref *ref)
अणु
	काष्ठा gb_camera_module *cam_mod =
		container_of(ref, काष्ठा gb_camera_module, refcount);
	kमुक्त(cam_mod->priv);
पूर्ण

अटल पूर्णांक gb_camera_probe(काष्ठा gb_bundle *bundle,
			   स्थिर काष्ठा greybus_bundle_id *id)
अणु
	काष्ठा gb_connection *conn;
	काष्ठा gb_camera *gcam;
	u16 mgmt_cport_id = 0;
	u16 data_cport_id = 0;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	/*
	 * The camera bundle must contain exactly two CPorts, one क्रम the
	 * camera management protocol and one क्रम the camera data protocol.
	 */
	अगर (bundle->num_cports != 2)
		वापस -ENODEV;

	क्रम (i = 0; i < bundle->num_cports; ++i) अणु
		काष्ठा greybus_descriptor_cport *desc = &bundle->cport_desc[i];

		चयन (desc->protocol_id) अणु
		हाल GREYBUS_PROTOCOL_CAMERA_MGMT:
			mgmt_cport_id = le16_to_cpu(desc->id);
			अवरोध;
		हाल GREYBUS_PROTOCOL_CAMERA_DATA:
			data_cport_id = le16_to_cpu(desc->id);
			अवरोध;
		शेष:
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	अगर (!mgmt_cport_id || !data_cport_id)
		वापस -ENODEV;

	gcam = kzalloc(माप(*gcam), GFP_KERNEL);
	अगर (!gcam)
		वापस -ENOMEM;

	mutex_init(&gcam->mutex);

	gcam->bundle = bundle;
	gcam->state = GB_CAMERA_STATE_UNCONFIGURED;
	gcam->data_cport_id = data_cport_id;

	conn = gb_connection_create(bundle, mgmt_cport_id,
				    gb_camera_request_handler);
	अगर (IS_ERR(conn)) अणु
		ret = PTR_ERR(conn);
		जाओ error;
	पूर्ण

	gcam->connection = conn;
	gb_connection_set_data(conn, gcam);

	ret = gb_connection_enable(conn);
	अगर (ret)
		जाओ error;

	ret = gb_camera_debugfs_init(gcam);
	अगर (ret < 0)
		जाओ error;

	gcam->module.priv = gcam;
	gcam->module.ops = &gb_cam_ops;
	gcam->module.पूर्णांकerface_id = gcam->connection->पूर्णांकf->पूर्णांकerface_id;
	gcam->module.release = gb_camera_release_module;
	ret = gb_camera_रेजिस्टर(&gcam->module);
	अगर (ret < 0)
		जाओ error;

	greybus_set_drvdata(bundle, gcam);

	gb_pm_runसमय_put_स्वतःsuspend(gcam->bundle);

	वापस 0;

error:
	gb_camera_cleanup(gcam);
	kमुक्त(gcam);
	वापस ret;
पूर्ण

अटल व्योम gb_camera_disconnect(काष्ठा gb_bundle *bundle)
अणु
	काष्ठा gb_camera *gcam = greybus_get_drvdata(bundle);
	पूर्णांक ret;

	ret = gb_pm_runसमय_get_sync(bundle);
	अगर (ret)
		gb_pm_runसमय_get_noresume(bundle);

	gb_camera_cleanup(gcam);
	gb_camera_unरेजिस्टर(&gcam->module);
पूर्ण

अटल स्थिर काष्ठा greybus_bundle_id gb_camera_id_table[] = अणु
	अणु GREYBUS_DEVICE_CLASS(GREYBUS_CLASS_CAMERA) पूर्ण,
	अणु पूर्ण,
पूर्ण;

#अगर_घोषित CONFIG_PM
अटल पूर्णांक gb_camera_suspend(काष्ठा device *dev)
अणु
	काष्ठा gb_bundle *bundle = to_gb_bundle(dev);
	काष्ठा gb_camera *gcam = greybus_get_drvdata(bundle);

	अगर (gcam->data_connection)
		gb_connection_disable(gcam->data_connection);

	gb_connection_disable(gcam->connection);

	वापस 0;
पूर्ण

अटल पूर्णांक gb_camera_resume(काष्ठा device *dev)
अणु
	काष्ठा gb_bundle *bundle = to_gb_bundle(dev);
	काष्ठा gb_camera *gcam = greybus_get_drvdata(bundle);
	पूर्णांक ret;

	ret = gb_connection_enable(gcam->connection);
	अगर (ret) अणु
		gcam_err(gcam, "failed to enable connection: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (gcam->data_connection) अणु
		ret = gb_connection_enable(gcam->data_connection);
		अगर (ret) अणु
			gcam_err(gcam,
				 "failed to enable data connection: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops gb_camera_pm_ops = अणु
	SET_RUNTIME_PM_OPS(gb_camera_suspend, gb_camera_resume, शून्य)
पूर्ण;

अटल काष्ठा greybus_driver gb_camera_driver = अणु
	.name		= "camera",
	.probe		= gb_camera_probe,
	.disconnect	= gb_camera_disconnect,
	.id_table	= gb_camera_id_table,
	.driver.pm	= &gb_camera_pm_ops,
पूर्ण;

module_greybus_driver(gb_camera_driver);

MODULE_LICENSE("GPL v2");
