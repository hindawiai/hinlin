<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2017-2020, The Linux Foundation. All rights reserved.
 */

#घोषणा pr_fmt(fmt)"[drm-dp] %s: " fmt, __func__

#समावेश <linux/debugfs.h>
#समावेश <drm/drm_connector.h>
#समावेश <drm/drm_file.h>

#समावेश "dp_parser.h"
#समावेश "dp_catalog.h"
#समावेश "dp_aux.h"
#समावेश "dp_ctrl.h"
#समावेश "dp_debug.h"
#समावेश "dp_display.h"

#घोषणा DEBUG_NAME "msm_dp"

काष्ठा dp_debug_निजी अणु
	काष्ठा dentry *root;

	काष्ठा dp_usbpd *usbpd;
	काष्ठा dp_link *link;
	काष्ठा dp_panel *panel;
	काष्ठा drm_connector **connector;
	काष्ठा device *dev;
	काष्ठा drm_device *drm_dev;

	काष्ठा dp_debug dp_debug;
पूर्ण;

अटल पूर्णांक dp_debug_check_buffer_overflow(पूर्णांक rc, पूर्णांक *max_size, पूर्णांक *len)
अणु
	अगर (rc >= *max_size) अणु
		DRM_ERROR("buffer overflow\n");
		वापस -EINVAL;
	पूर्ण
	*len += rc;
	*max_size = SZ_4K - *len;

	वापस 0;
पूर्ण

अटल sमाप_प्रकार dp_debug_पढ़ो_info(काष्ठा file *file, अक्षर __user *user_buff,
		माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा dp_debug_निजी *debug = file->निजी_data;
	अक्षर *buf;
	u32 len = 0, rc = 0;
	u64 lclk = 0;
	u32 max_size = SZ_4K;
	u32 link_params_rate;
	काष्ठा drm_display_mode *drm_mode;

	अगर (!debug)
		वापस -ENODEV;

	अगर (*ppos)
		वापस 0;

	buf = kzalloc(SZ_4K, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	drm_mode = &debug->panel->dp_mode.drm_mode;

	rc = snम_लिखो(buf + len, max_size, "\tname = %s\n", DEBUG_NAME);
	अगर (dp_debug_check_buffer_overflow(rc, &max_size, &len))
		जाओ error;

	rc = snम_लिखो(buf + len, max_size,
			"\tdp_panel\n\t\tmax_pclk_khz = %d\n",
			debug->panel->max_pclk_khz);
	अगर (dp_debug_check_buffer_overflow(rc, &max_size, &len))
		जाओ error;

	rc = snम_लिखो(buf + len, max_size,
			"\tdrm_dp_link\n\t\trate = %u\n",
			debug->panel->link_info.rate);
	अगर (dp_debug_check_buffer_overflow(rc, &max_size, &len))
		जाओ error;

	rc = snम_लिखो(buf + len, max_size,
			 "\t\tnum_lanes = %u\n",
			debug->panel->link_info.num_lanes);
	अगर (dp_debug_check_buffer_overflow(rc, &max_size, &len))
		जाओ error;

	rc = snम_लिखो(buf + len, max_size,
			"\t\tcapabilities = %lu\n",
			debug->panel->link_info.capabilities);
	अगर (dp_debug_check_buffer_overflow(rc, &max_size, &len))
		जाओ error;

	rc = snम_लिखो(buf + len, max_size,
			"\tdp_panel_info:\n\t\tactive = %dx%d\n",
			drm_mode->hdisplay,
			drm_mode->vdisplay);
	अगर (dp_debug_check_buffer_overflow(rc, &max_size, &len))
		जाओ error;

	rc = snम_लिखो(buf + len, max_size,
			"\t\tback_porch = %dx%d\n",
			drm_mode->htotal - drm_mode->hsync_end,
			drm_mode->vtotal - drm_mode->vsync_end);
	अगर (dp_debug_check_buffer_overflow(rc, &max_size, &len))
		जाओ error;

	rc = snम_लिखो(buf + len, max_size,
			"\t\tfront_porch = %dx%d\n",
			drm_mode->hsync_start - drm_mode->hdisplay,
			drm_mode->vsync_start - drm_mode->vdisplay);
	अगर (dp_debug_check_buffer_overflow(rc, &max_size, &len))
		जाओ error;

	rc = snम_लिखो(buf + len, max_size,
			"\t\tsync_width = %dx%d\n",
			drm_mode->hsync_end - drm_mode->hsync_start,
			drm_mode->vsync_end - drm_mode->vsync_start);
	अगर (dp_debug_check_buffer_overflow(rc, &max_size, &len))
		जाओ error;

	rc = snम_लिखो(buf + len, max_size,
			"\t\tactive_low = %dx%d\n",
			debug->panel->dp_mode.h_active_low,
			debug->panel->dp_mode.v_active_low);
	अगर (dp_debug_check_buffer_overflow(rc, &max_size, &len))
		जाओ error;

	rc = snम_लिखो(buf + len, max_size,
			"\t\th_skew = %d\n",
			drm_mode->hskew);
	अगर (dp_debug_check_buffer_overflow(rc, &max_size, &len))
		जाओ error;

	rc = snम_लिखो(buf + len, max_size,
			"\t\trefresh rate = %d\n",
			drm_mode_vrefresh(drm_mode));
	अगर (dp_debug_check_buffer_overflow(rc, &max_size, &len))
		जाओ error;

	rc = snम_लिखो(buf + len, max_size,
			"\t\tpixel clock khz = %d\n",
			drm_mode->घड़ी);
	अगर (dp_debug_check_buffer_overflow(rc, &max_size, &len))
		जाओ error;

	rc = snम_लिखो(buf + len, max_size,
			"\t\tbpp = %d\n",
			debug->panel->dp_mode.bpp);
	अगर (dp_debug_check_buffer_overflow(rc, &max_size, &len))
		जाओ error;

	/* Link Inक्रमmation */
	rc = snम_लिखो(buf + len, max_size,
			"\tdp_link:\n\t\ttest_requested = %d\n",
			debug->link->sink_request);
	अगर (dp_debug_check_buffer_overflow(rc, &max_size, &len))
		जाओ error;

	rc = snम_लिखो(buf + len, max_size,
			"\t\tnum_lanes = %d\n",
			debug->link->link_params.num_lanes);
	अगर (dp_debug_check_buffer_overflow(rc, &max_size, &len))
		जाओ error;

	link_params_rate = debug->link->link_params.rate;
	rc = snम_लिखो(buf + len, max_size,
			"\t\tbw_code = %d\n",
			drm_dp_link_rate_to_bw_code(link_params_rate));
	अगर (dp_debug_check_buffer_overflow(rc, &max_size, &len))
		जाओ error;

	lclk = debug->link->link_params.rate * 1000;
	rc = snम_लिखो(buf + len, max_size,
			"\t\tlclk = %lld\n", lclk);
	अगर (dp_debug_check_buffer_overflow(rc, &max_size, &len))
		जाओ error;

	rc = snम_लिखो(buf + len, max_size,
			"\t\tv_level = %d\n",
			debug->link->phy_params.v_level);
	अगर (dp_debug_check_buffer_overflow(rc, &max_size, &len))
		जाओ error;

	rc = snम_लिखो(buf + len, max_size,
			"\t\tp_level = %d\n",
			debug->link->phy_params.p_level);
	अगर (dp_debug_check_buffer_overflow(rc, &max_size, &len))
		जाओ error;

	अगर (copy_to_user(user_buff, buf, len))
		जाओ error;

	*ppos += len;

	kमुक्त(buf);
	वापस len;
 error:
	kमुक्त(buf);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक dp_test_data_show(काष्ठा seq_file *m, व्योम *data)
अणु
	काष्ठा drm_device *dev;
	काष्ठा dp_debug_निजी *debug;
	काष्ठा drm_connector *connector;
	काष्ठा drm_connector_list_iter conn_iter;
	u32 bpc;

	debug = m->निजी;
	dev = debug->drm_dev;
	drm_connector_list_iter_begin(dev, &conn_iter);
	drm_क्रम_each_connector_iter(connector, &conn_iter) अणु

		अगर (connector->connector_type !=
			DRM_MODE_CONNECTOR_DisplayPort)
			जारी;

		अगर (connector->status == connector_status_connected) अणु
			bpc = debug->link->test_video.test_bit_depth;
			seq_म_लिखो(m, "hdisplay: %d\n",
					debug->link->test_video.test_h_width);
			seq_म_लिखो(m, "vdisplay: %d\n",
					debug->link->test_video.test_v_height);
			seq_म_लिखो(m, "bpc: %u\n",
					dp_link_bit_depth_to_bpc(bpc));
		पूर्ण अन्यथा
			seq_माला_दो(m, "0");
	पूर्ण

	drm_connector_list_iter_end(&conn_iter);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(dp_test_data);

अटल पूर्णांक dp_test_type_show(काष्ठा seq_file *m, व्योम *data)
अणु
	काष्ठा dp_debug_निजी *debug = m->निजी;
	काष्ठा drm_device *dev = debug->drm_dev;
	काष्ठा drm_connector *connector;
	काष्ठा drm_connector_list_iter conn_iter;

	drm_connector_list_iter_begin(dev, &conn_iter);
	drm_क्रम_each_connector_iter(connector, &conn_iter) अणु

		अगर (connector->connector_type !=
			DRM_MODE_CONNECTOR_DisplayPort)
			जारी;

		अगर (connector->status == connector_status_connected)
			seq_म_लिखो(m, "%02x", DP_TEST_LINK_VIDEO_PATTERN);
		अन्यथा
			seq_माला_दो(m, "0");
	पूर्ण
	drm_connector_list_iter_end(&conn_iter);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(dp_test_type);

अटल sमाप_प्रकार dp_test_active_ग_लिखो(काष्ठा file *file,
		स्थिर अक्षर __user *ubuf,
		माप_प्रकार len, loff_t *offp)
अणु
	अक्षर *input_buffer;
	पूर्णांक status = 0;
	काष्ठा dp_debug_निजी *debug;
	काष्ठा drm_device *dev;
	काष्ठा drm_connector *connector;
	काष्ठा drm_connector_list_iter conn_iter;
	पूर्णांक val = 0;

	debug = ((काष्ठा seq_file *)file->निजी_data)->निजी;
	dev = debug->drm_dev;

	अगर (len == 0)
		वापस 0;

	input_buffer = memdup_user_nul(ubuf, len);
	अगर (IS_ERR(input_buffer))
		वापस PTR_ERR(input_buffer);

	DRM_DEBUG_DRIVER("Copied %d bytes from user\n", (अचिन्हित पूर्णांक)len);

	drm_connector_list_iter_begin(dev, &conn_iter);
	drm_क्रम_each_connector_iter(connector, &conn_iter) अणु
		अगर (connector->connector_type !=
			DRM_MODE_CONNECTOR_DisplayPort)
			जारी;

		अगर (connector->status == connector_status_connected) अणु
			status = kstrtoपूर्णांक(input_buffer, 10, &val);
			अगर (status < 0)
				अवरोध;
			DRM_DEBUG_DRIVER("Got %d for test active\n", val);
			/* To prevent erroneous activation of the compliance
			 * testing code, only accept an actual value of 1 here
			 */
			अगर (val == 1)
				debug->panel->video_test = true;
			अन्यथा
				debug->panel->video_test = false;
		पूर्ण
	पूर्ण
	drm_connector_list_iter_end(&conn_iter);
	kमुक्त(input_buffer);
	अगर (status < 0)
		वापस status;

	*offp += len;
	वापस len;
पूर्ण

अटल पूर्णांक dp_test_active_show(काष्ठा seq_file *m, व्योम *data)
अणु
	काष्ठा dp_debug_निजी *debug = m->निजी;
	काष्ठा drm_device *dev = debug->drm_dev;
	काष्ठा drm_connector *connector;
	काष्ठा drm_connector_list_iter conn_iter;

	drm_connector_list_iter_begin(dev, &conn_iter);
	drm_क्रम_each_connector_iter(connector, &conn_iter) अणु
		अगर (connector->connector_type !=
			DRM_MODE_CONNECTOR_DisplayPort)
			जारी;

		अगर (connector->status == connector_status_connected) अणु
			अगर (debug->panel->video_test)
				seq_माला_दो(m, "1");
			अन्यथा
				seq_माला_दो(m, "0");
		पूर्ण अन्यथा
			seq_माला_दो(m, "0");
	पूर्ण
	drm_connector_list_iter_end(&conn_iter);

	वापस 0;
पूर्ण

अटल पूर्णांक dp_test_active_खोलो(काष्ठा inode *inode,
		काष्ठा file *file)
अणु
	वापस single_खोलो(file, dp_test_active_show,
			inode->i_निजी);
पूर्ण

अटल स्थिर काष्ठा file_operations dp_debug_fops = अणु
	.खोलो = simple_खोलो,
	.पढ़ो = dp_debug_पढ़ो_info,
पूर्ण;

अटल स्थिर काष्ठा file_operations test_active_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = dp_test_active_खोलो,
	.पढ़ो = seq_पढ़ो,
	.llseek = seq_lseek,
	.release = single_release,
	.ग_लिखो = dp_test_active_ग_लिखो
पूर्ण;

अटल पूर्णांक dp_debug_init(काष्ठा dp_debug *dp_debug, काष्ठा drm_minor *minor)
अणु
	पूर्णांक rc = 0;
	काष्ठा dp_debug_निजी *debug = container_of(dp_debug,
			काष्ठा dp_debug_निजी, dp_debug);

	debugfs_create_file("dp_debug", 0444, minor->debugfs_root,
			debug, &dp_debug_fops);

	debugfs_create_file("msm_dp_test_active", 0444,
			minor->debugfs_root,
			debug, &test_active_fops);

	debugfs_create_file("msm_dp_test_data", 0444,
			minor->debugfs_root,
			debug, &dp_test_data_fops);

	debugfs_create_file("msm_dp_test_type", 0444,
			minor->debugfs_root,
			debug, &dp_test_type_fops);

	debug->root = minor->debugfs_root;

	वापस rc;
पूर्ण

काष्ठा dp_debug *dp_debug_get(काष्ठा device *dev, काष्ठा dp_panel *panel,
		काष्ठा dp_usbpd *usbpd, काष्ठा dp_link *link,
		काष्ठा drm_connector **connector, काष्ठा drm_minor *minor)
अणु
	पूर्णांक rc = 0;
	काष्ठा dp_debug_निजी *debug;
	काष्ठा dp_debug *dp_debug;

	अगर (!dev || !panel || !usbpd || !link) अणु
		DRM_ERROR("invalid input\n");
		rc = -EINVAL;
		जाओ error;
	पूर्ण

	debug = devm_kzalloc(dev, माप(*debug), GFP_KERNEL);
	अगर (!debug) अणु
		rc = -ENOMEM;
		जाओ error;
	पूर्ण

	debug->dp_debug.debug_en = false;
	debug->usbpd = usbpd;
	debug->link = link;
	debug->panel = panel;
	debug->dev = dev;
	debug->drm_dev = minor->dev;
	debug->connector = connector;

	dp_debug = &debug->dp_debug;
	dp_debug->vdisplay = 0;
	dp_debug->hdisplay = 0;
	dp_debug->vrefresh = 0;

	rc = dp_debug_init(dp_debug, minor);
	अगर (rc) अणु
		devm_kमुक्त(dev, debug);
		जाओ error;
	पूर्ण

	वापस dp_debug;
 error:
	वापस ERR_PTR(rc);
पूर्ण

अटल पूर्णांक dp_debug_deinit(काष्ठा dp_debug *dp_debug)
अणु
	काष्ठा dp_debug_निजी *debug;

	अगर (!dp_debug)
		वापस -EINVAL;

	debug = container_of(dp_debug, काष्ठा dp_debug_निजी, dp_debug);

	debugfs_हटाओ_recursive(debug->root);

	वापस 0;
पूर्ण

व्योम dp_debug_put(काष्ठा dp_debug *dp_debug)
अणु
	काष्ठा dp_debug_निजी *debug;

	अगर (!dp_debug)
		वापस;

	debug = container_of(dp_debug, काष्ठा dp_debug_निजी, dp_debug);

	dp_debug_deinit(dp_debug);

	devm_kमुक्त(debug->dev, debug);
पूर्ण
