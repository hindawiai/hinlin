<शैली गुरु>
/*
 * Copyright 2018 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: AMD
 *
 */

#समावेश <linux/uaccess.h>

#समावेश "dc.h"
#समावेश "amdgpu.h"
#समावेश "amdgpu_dm.h"
#समावेश "amdgpu_dm_debugfs.h"
#समावेश "dm_helpers.h"
#समावेश "dmub/dmub_srv.h"
#समावेश "resource.h"
#समावेश "dsc.h"
#समावेश "dc_link_dp.h"
#समावेश "link_hwss.h"
#समावेश "dc/dc_dmub_srv.h"

काष्ठा dmub_debugfs_trace_header अणु
	uपूर्णांक32_t entry_count;
	uपूर्णांक32_t reserved[3];
पूर्ण;

काष्ठा dmub_debugfs_trace_entry अणु
	uपूर्णांक32_t trace_code;
	uपूर्णांक32_t tick_count;
	uपूर्णांक32_t param0;
	uपूर्णांक32_t param1;
पूर्ण;

अटल अंतरभूत स्थिर अक्षर *yesno(bool v)
अणु
	वापस v ? "yes" : "no";
पूर्ण

/* parse_ग_लिखो_buffer_पूर्णांकo_params - Helper function to parse debugfs ग_लिखो buffer पूर्णांकo an array
 *
 * Function takes in attributes passed to debugfs ग_लिखो entry
 * and ग_लिखोs पूर्णांकo param array.
 * The user passes max_param_num to identअगरy maximum number of
 * parameters that could be parsed.
 *
 */
अटल पूर्णांक parse_ग_लिखो_buffer_पूर्णांकo_params(अक्षर *wr_buf, uपूर्णांक32_t wr_buf_size,
					  दीर्घ *param, स्थिर अक्षर __user *buf,
					  पूर्णांक max_param_num,
					  uपूर्णांक8_t *param_nums)
अणु
	अक्षर *wr_buf_ptr = शून्य;
	uपूर्णांक32_t wr_buf_count = 0;
	पूर्णांक r;
	अक्षर *sub_str = शून्य;
	स्थिर अक्षर delimiter[3] = अणु' ', '\n', '\0'पूर्ण;
	uपूर्णांक8_t param_index = 0;

	*param_nums = 0;

	wr_buf_ptr = wr_buf;

	r = copy_from_user(wr_buf_ptr, buf, wr_buf_size);

		/* r is bytes not be copied */
	अगर (r >= wr_buf_size) अणु
		DRM_DEBUG_DRIVER("user data not be read\n");
		वापस -EINVAL;
	पूर्ण

	/* check number of parameters. है_खाली could not dअगरfer space and \न */
	जबतक ((*wr_buf_ptr != 0xa) && (wr_buf_count < wr_buf_size)) अणु
		/* skip space*/
		जबतक (है_खाली(*wr_buf_ptr) && (wr_buf_count < wr_buf_size)) अणु
			wr_buf_ptr++;
			wr_buf_count++;
			पूर्ण

		अगर (wr_buf_count == wr_buf_size)
			अवरोध;

		/* skip non-space*/
		जबतक ((!है_खाली(*wr_buf_ptr)) && (wr_buf_count < wr_buf_size)) अणु
			wr_buf_ptr++;
			wr_buf_count++;
		पूर्ण

		(*param_nums)++;

		अगर (wr_buf_count == wr_buf_size)
			अवरोध;
	पूर्ण

	अगर (*param_nums > max_param_num)
		*param_nums = max_param_num;

	wr_buf_ptr = wr_buf; /* reset buf poपूर्णांकer */
	wr_buf_count = 0; /* number of अक्षर alपढ़ोy checked */

	जबतक (है_खाली(*wr_buf_ptr) && (wr_buf_count < wr_buf_size)) अणु
		wr_buf_ptr++;
		wr_buf_count++;
	पूर्ण

	जबतक (param_index < *param_nums) अणु
		/* after strsep, wr_buf_ptr will be moved to after space */
		sub_str = strsep(&wr_buf_ptr, delimiter);

		r = kम_से_दीर्घ(sub_str, 16, &(param[param_index]));

		अगर (r)
			DRM_DEBUG_DRIVER("string to int convert error code: %d\n", r);

		param_index++;
	पूर्ण

	वापस 0;
पूर्ण

/* function description
 * get/ set DP configuration: lane_count, link_rate, spपढ़ो_spectrum
 *
 * valid lane count value: 1, 2, 4
 * valid link rate value:
 * 06h = 1.62Gbps per lane
 * 0Ah = 2.7Gbps per lane
 * 0Ch = 3.24Gbps per lane
 * 14h = 5.4Gbps per lane
 * 1Eh = 8.1Gbps per lane
 *
 * debugfs is located at /sys/kernel/debug/dri/0/DP-x/link_settings
 *
 * --- to get dp configuration
 *
 * cat /sys/kernel/debug/dri/0/DP-x/link_settings
 *
 * It will list current, verअगरied, reported, preferred dp configuration.
 * current -- क्रम current video mode
 * verअगरied --- maximum configuration which pass link training
 * reported --- DP rx report caps (DPCD रेजिस्टर offset 0, 1 2)
 * preferred --- user क्रमce settings
 *
 * --- set (or क्रमce) dp configuration
 *
 * echo <lane_count>  <link_rate> > link_settings
 *
 * क्रम example, to क्रमce to  2 lane, 2.7GHz,
 * echo 4 0xa > /sys/kernel/debug/dri/0/DP-x/link_settings
 *
 * spपढ़ो_spectrum could not be changed dynamically.
 *
 * in हाल invalid lane count, link rate are क्रमce, no hw programming will be
 * करोne. please check link settings after क्रमce operation to see अगर HW get
 * programming.
 *
 * cat /sys/kernel/debug/dri/0/DP-x/link_settings
 *
 * check current and preferred settings.
 *
 */
अटल sमाप_प्रकार dp_link_settings_पढ़ो(काष्ठा file *f, अक्षर __user *buf,
				 माप_प्रकार size, loff_t *pos)
अणु
	काष्ठा amdgpu_dm_connector *connector = file_inode(f)->i_निजी;
	काष्ठा dc_link *link = connector->dc_link;
	अक्षर *rd_buf = शून्य;
	अक्षर *rd_buf_ptr = शून्य;
	स्थिर uपूर्णांक32_t rd_buf_size = 100;
	uपूर्णांक32_t result = 0;
	uपूर्णांक8_t str_len = 0;
	पूर्णांक r;

	अगर (*pos & 3 || size & 3)
		वापस -EINVAL;

	rd_buf = kसुस्मृति(rd_buf_size, माप(अक्षर), GFP_KERNEL);
	अगर (!rd_buf)
		वापस 0;

	rd_buf_ptr = rd_buf;

	str_len = म_माप("Current:  %d  %d  %d  ");
	snम_लिखो(rd_buf_ptr, str_len, "Current:  %d  %d  %d  ",
			link->cur_link_settings.lane_count,
			link->cur_link_settings.link_rate,
			link->cur_link_settings.link_spपढ़ो);
	rd_buf_ptr += str_len;

	str_len = म_माप("Verified:  %d  %d  %d  ");
	snम_लिखो(rd_buf_ptr, str_len, "Verified:  %d  %d  %d  ",
			link->verअगरied_link_cap.lane_count,
			link->verअगरied_link_cap.link_rate,
			link->verअगरied_link_cap.link_spपढ़ो);
	rd_buf_ptr += str_len;

	str_len = म_माप("Reported:  %d  %d  %d  ");
	snम_लिखो(rd_buf_ptr, str_len, "Reported:  %d  %d  %d  ",
			link->reported_link_cap.lane_count,
			link->reported_link_cap.link_rate,
			link->reported_link_cap.link_spपढ़ो);
	rd_buf_ptr += str_len;

	str_len = म_माप("Preferred:  %d  %d  %d  ");
	snम_लिखो(rd_buf_ptr, str_len, "Preferred:  %d  %d  %d\n",
			link->preferred_link_setting.lane_count,
			link->preferred_link_setting.link_rate,
			link->preferred_link_setting.link_spपढ़ो);

	जबतक (size) अणु
		अगर (*pos >= rd_buf_size)
			अवरोध;

		r = put_user(*(rd_buf + result), buf);
		अगर (r)
			वापस r; /* r = -EFAULT */

		buf += 1;
		size -= 1;
		*pos += 1;
		result += 1;
	पूर्ण

	kमुक्त(rd_buf);
	वापस result;
पूर्ण

अटल sमाप_प्रकार dp_link_settings_ग_लिखो(काष्ठा file *f, स्थिर अक्षर __user *buf,
				 माप_प्रकार size, loff_t *pos)
अणु
	काष्ठा amdgpu_dm_connector *connector = file_inode(f)->i_निजी;
	काष्ठा dc_link *link = connector->dc_link;
	काष्ठा dc_link_settings prefer_link_settings;
	अक्षर *wr_buf = शून्य;
	स्थिर uपूर्णांक32_t wr_buf_size = 40;
	/* 0: lane_count; 1: link_rate */
	पूर्णांक max_param_num = 2;
	uपूर्णांक8_t param_nums = 0;
	दीर्घ param[2];
	bool valid_input = true;

	अगर (size == 0)
		वापस -EINVAL;

	wr_buf = kसुस्मृति(wr_buf_size, माप(अक्षर), GFP_KERNEL);
	अगर (!wr_buf)
		वापस -ENOSPC;

	अगर (parse_ग_लिखो_buffer_पूर्णांकo_params(wr_buf, size,
					   (दीर्घ *)param, buf,
					   max_param_num,
					   &param_nums)) अणु
		kमुक्त(wr_buf);
		वापस -EINVAL;
	पूर्ण

	अगर (param_nums <= 0) अणु
		kमुक्त(wr_buf);
		DRM_DEBUG_DRIVER("user data not be read\n");
		वापस -EINVAL;
	पूर्ण

	चयन (param[0]) अणु
	हाल LANE_COUNT_ONE:
	हाल LANE_COUNT_TWO:
	हाल LANE_COUNT_FOUR:
		अवरोध;
	शेष:
		valid_input = false;
		अवरोध;
	पूर्ण

	चयन (param[1]) अणु
	हाल LINK_RATE_LOW:
	हाल LINK_RATE_HIGH:
	हाल LINK_RATE_RBR2:
	हाल LINK_RATE_HIGH2:
	हाल LINK_RATE_HIGH3:
		अवरोध;
	शेष:
		valid_input = false;
		अवरोध;
	पूर्ण

	अगर (!valid_input) अणु
		kमुक्त(wr_buf);
		DRM_DEBUG_DRIVER("Invalid Input value No HW will be programmed\n");
		वापस size;
	पूर्ण

	/* save user क्रमce lane_count, link_rate to preferred settings
	 * spपढ़ो spectrum will not be changed
	 */
	prefer_link_settings.link_spपढ़ो = link->cur_link_settings.link_spपढ़ो;
	prefer_link_settings.use_link_rate_set = false;
	prefer_link_settings.lane_count = param[0];
	prefer_link_settings.link_rate = param[1];

	dp_retrain_link_dp_test(link, &prefer_link_settings, false);

	kमुक्त(wr_buf);
	वापस size;
पूर्ण

/* function: get current DP PHY settings: voltage swing, pre-emphasis,
 * post-cursor2 (defined by VESA DP specअगरication)
 *
 * valid values
 * voltage swing: 0,1,2,3
 * pre-emphasis : 0,1,2,3
 * post cursor2 : 0,1,2,3
 *
 *
 * how to use this debugfs
 *
 * debugfs is located at /sys/kernel/debug/dri/0/DP-x
 *
 * there will be directories, like DP-1, DP-2,DP-3, etc. क्रम DP display
 *
 * To figure out which DP-x is the display क्रम DP to be check,
 * cd DP-x
 * ls -ll
 * There should be debugfs file, like link_settings, phy_settings.
 * cat link_settings
 * from lane_count, link_rate to figure which DP-x is क्रम display to be worked
 * on
 *
 * To get current DP PHY settings,
 * cat phy_settings
 *
 * To change DP PHY settings,
 * echo <voltage_swing> <pre-emphasis> <post_cursor2> > phy_settings
 * क्रम examle, to change voltage swing to 2, pre-emphasis to 3, post_cursor2 to
 * 0,
 * echo 2 3 0 > phy_settings
 *
 * To check अगर change be applied, get current phy settings by
 * cat phy_settings
 *
 * In हाल invalid values are set by user, like
 * echo 1 4 0 > phy_settings
 *
 * HW will NOT be programmed by these settings.
 * cat phy_settings will show the previous valid settings.
 */
अटल sमाप_प्रकार dp_phy_settings_पढ़ो(काष्ठा file *f, अक्षर __user *buf,
				 माप_प्रकार size, loff_t *pos)
अणु
	काष्ठा amdgpu_dm_connector *connector = file_inode(f)->i_निजी;
	काष्ठा dc_link *link = connector->dc_link;
	अक्षर *rd_buf = शून्य;
	स्थिर uपूर्णांक32_t rd_buf_size = 20;
	uपूर्णांक32_t result = 0;
	पूर्णांक r;

	अगर (*pos & 3 || size & 3)
		वापस -EINVAL;

	rd_buf = kसुस्मृति(rd_buf_size, माप(अक्षर), GFP_KERNEL);
	अगर (!rd_buf)
		वापस -EINVAL;

	snम_लिखो(rd_buf, rd_buf_size, "  %d  %d  %d  ",
			link->cur_lane_setting.VOLTAGE_SWING,
			link->cur_lane_setting.PRE_EMPHASIS,
			link->cur_lane_setting.POST_CURSOR2);

	जबतक (size) अणु
		अगर (*pos >= rd_buf_size)
			अवरोध;

		r = put_user((*(rd_buf + result)), buf);
		अगर (r)
			वापस r; /* r = -EFAULT */

		buf += 1;
		size -= 1;
		*pos += 1;
		result += 1;
	पूर्ण

	kमुक्त(rd_buf);
	वापस result;
पूर्ण

अटल पूर्णांक dp_lttpr_status_show(काष्ठा seq_file *m, व्योम *d)
अणु
	अक्षर *data;
	काष्ठा amdgpu_dm_connector *connector = file_inode(m->file)->i_निजी;
	काष्ठा dc_link *link = connector->dc_link;
	uपूर्णांक32_t पढ़ो_size = 1;
	uपूर्णांक8_t repeater_count = 0;

	data = kzalloc(पढ़ो_size, GFP_KERNEL);
	अगर (!data)
		वापस 0;

	dm_helpers_dp_पढ़ो_dpcd(link->ctx, link, 0xF0002, data, पढ़ो_size);

	चयन ((uपूर्णांक8_t)*data) अणु
	हाल 0x80:
		repeater_count = 1;
		अवरोध;
	हाल 0x40:
		repeater_count = 2;
		अवरोध;
	हाल 0x20:
		repeater_count = 3;
		अवरोध;
	हाल 0x10:
		repeater_count = 4;
		अवरोध;
	हाल 0x8:
		repeater_count = 5;
		अवरोध;
	हाल 0x4:
		repeater_count = 6;
		अवरोध;
	हाल 0x2:
		repeater_count = 7;
		अवरोध;
	हाल 0x1:
		repeater_count = 8;
		अवरोध;
	हाल 0x0:
		repeater_count = 0;
		अवरोध;
	शेष:
		repeater_count = (uपूर्णांक8_t)*data;
		अवरोध;
	पूर्ण

	seq_म_लिखो(m, "phy repeater count: %d\n", repeater_count);

	dm_helpers_dp_पढ़ो_dpcd(link->ctx, link, 0xF0003, data, पढ़ो_size);

	अगर ((uपूर्णांक8_t)*data == 0x55)
		seq_म_लिखो(m, "phy repeater mode: transparent\n");
	अन्यथा अगर ((uपूर्णांक8_t)*data == 0xAA)
		seq_म_लिखो(m, "phy repeater mode: non-transparent\n");
	अन्यथा अगर ((uपूर्णांक8_t)*data == 0x00)
		seq_म_लिखो(m, "phy repeater mode: non lttpr\n");
	अन्यथा
		seq_म_लिखो(m, "phy repeater mode: read error\n");

	kमुक्त(data);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार dp_phy_settings_ग_लिखो(काष्ठा file *f, स्थिर अक्षर __user *buf,
				 माप_प्रकार size, loff_t *pos)
अणु
	काष्ठा amdgpu_dm_connector *connector = file_inode(f)->i_निजी;
	काष्ठा dc_link *link = connector->dc_link;
	काष्ठा dc *dc = (काष्ठा dc *)link->dc;
	अक्षर *wr_buf = शून्य;
	uपूर्णांक32_t wr_buf_size = 40;
	दीर्घ param[3];
	bool use_prefer_link_setting;
	काष्ठा link_training_settings link_lane_settings;
	पूर्णांक max_param_num = 3;
	uपूर्णांक8_t param_nums = 0;
	पूर्णांक r = 0;


	अगर (size == 0)
		वापस -EINVAL;

	wr_buf = kसुस्मृति(wr_buf_size, माप(अक्षर), GFP_KERNEL);
	अगर (!wr_buf)
		वापस -ENOSPC;

	अगर (parse_ग_लिखो_buffer_पूर्णांकo_params(wr_buf, size,
					   (दीर्घ *)param, buf,
					   max_param_num,
					   &param_nums)) अणु
		kमुक्त(wr_buf);
		वापस -EINVAL;
	पूर्ण

	अगर (param_nums <= 0) अणु
		kमुक्त(wr_buf);
		DRM_DEBUG_DRIVER("user data not be read\n");
		वापस -EINVAL;
	पूर्ण

	अगर ((param[0] > VOLTAGE_SWING_MAX_LEVEL) ||
			(param[1] > PRE_EMPHASIS_MAX_LEVEL) ||
			(param[2] > POST_CURSOR2_MAX_LEVEL)) अणु
		kमुक्त(wr_buf);
		DRM_DEBUG_DRIVER("Invalid Input No HW will be programmed\n");
		वापस size;
	पूर्ण

	/* get link settings: lane count, link rate */
	use_prefer_link_setting =
		((link->preferred_link_setting.link_rate != LINK_RATE_UNKNOWN) &&
		(link->test_pattern_enabled));

	स_रखो(&link_lane_settings, 0, माप(link_lane_settings));

	अगर (use_prefer_link_setting) अणु
		link_lane_settings.link_settings.lane_count =
				link->preferred_link_setting.lane_count;
		link_lane_settings.link_settings.link_rate =
				link->preferred_link_setting.link_rate;
		link_lane_settings.link_settings.link_spपढ़ो =
				link->preferred_link_setting.link_spपढ़ो;
	पूर्ण अन्यथा अणु
		link_lane_settings.link_settings.lane_count =
				link->cur_link_settings.lane_count;
		link_lane_settings.link_settings.link_rate =
				link->cur_link_settings.link_rate;
		link_lane_settings.link_settings.link_spपढ़ो =
				link->cur_link_settings.link_spपढ़ो;
	पूर्ण

	/* apply phy settings from user */
	क्रम (r = 0; r < link_lane_settings.link_settings.lane_count; r++) अणु
		link_lane_settings.lane_settings[r].VOLTAGE_SWING =
				(क्रमागत dc_voltage_swing) (param[0]);
		link_lane_settings.lane_settings[r].PRE_EMPHASIS =
				(क्रमागत dc_pre_emphasis) (param[1]);
		link_lane_settings.lane_settings[r].POST_CURSOR2 =
				(क्रमागत dc_post_cursor2) (param[2]);
	पूर्ण

	/* program ASIC रेजिस्टरs and DPCD रेजिस्टरs */
	dc_link_set_drive_settings(dc, &link_lane_settings, link);

	kमुक्त(wr_buf);
	वापस size;
पूर्ण

/* function description
 *
 * set PHY layer or Link layer test pattern
 * PHY test pattern is used क्रम PHY SI check.
 * Link layer test will not affect PHY SI.
 *
 * Reset Test Pattern:
 * 0 = DP_TEST_PATTERN_VIDEO_MODE
 *
 * PHY test pattern supported:
 * 1 = DP_TEST_PATTERN_D102
 * 2 = DP_TEST_PATTERN_SYMBOL_ERROR
 * 3 = DP_TEST_PATTERN_PRBS7
 * 4 = DP_TEST_PATTERN_80BIT_CUSTOM
 * 5 = DP_TEST_PATTERN_CP2520_1
 * 6 = DP_TEST_PATTERN_CP2520_2 = DP_TEST_PATTERN_HBR2_COMPLIANCE_EYE
 * 7 = DP_TEST_PATTERN_CP2520_3
 *
 * DP PHY Link Training Patterns
 * 8 = DP_TEST_PATTERN_TRAINING_PATTERN1
 * 9 = DP_TEST_PATTERN_TRAINING_PATTERN2
 * a = DP_TEST_PATTERN_TRAINING_PATTERN3
 * b = DP_TEST_PATTERN_TRAINING_PATTERN4
 *
 * DP Link Layer Test pattern
 * c = DP_TEST_PATTERN_COLOR_SQUARES
 * d = DP_TEST_PATTERN_COLOR_SQUARES_CEA
 * e = DP_TEST_PATTERN_VERTICAL_BARS
 * f = DP_TEST_PATTERN_HORIZONTAL_BARS
 * 10= DP_TEST_PATTERN_COLOR_RAMP
 *
 * debugfs phy_test_pattern is located at /syskernel/debug/dri/0/DP-x
 *
 * --- set test pattern
 * echo <test pattern #> > test_pattern
 *
 * If test pattern # is not supported, NO HW programming will be करोne.
 * क्रम DP_TEST_PATTERN_80BIT_CUSTOM, it needs extra 10 bytes of data
 * क्रम the user pattern. input 10 bytes data are separated by space
 *
 * echo 0x4 0x11 0x22 0x33 0x44 0x55 0x66 0x77 0x88 0x99 0xaa > test_pattern
 *
 * --- reset test pattern
 * echo 0 > test_pattern
 *
 * --- HPD detection is disabled when set PHY test pattern
 *
 * when PHY test pattern (pattern # within [1,7]) is set, HPD pin of HW ASIC
 * is disable. User could unplug DP display from DP connected and plug scope to
 * check test pattern PHY SI.
 * If there is need unplug scope and plug DP display back, करो steps below:
 * echo 0 > phy_test_pattern
 * unplug scope
 * plug DP display.
 *
 * "echo 0 > phy_test_pattern" will re-enable HPD pin again so that video sw
 * driver could detect "unplug scope" and "plug DP display"
 */
अटल sमाप_प्रकार dp_phy_test_pattern_debugfs_ग_लिखो(काष्ठा file *f, स्थिर अक्षर __user *buf,
				 माप_प्रकार size, loff_t *pos)
अणु
	काष्ठा amdgpu_dm_connector *connector = file_inode(f)->i_निजी;
	काष्ठा dc_link *link = connector->dc_link;
	अक्षर *wr_buf = शून्य;
	uपूर्णांक32_t wr_buf_size = 100;
	दीर्घ param[11] = अणु0x0पूर्ण;
	पूर्णांक max_param_num = 11;
	क्रमागत dp_test_pattern test_pattern = DP_TEST_PATTERN_UNSUPPORTED;
	bool disable_hpd = false;
	bool valid_test_pattern = false;
	uपूर्णांक8_t param_nums = 0;
	/* init with शेष 80bit custom pattern */
	uपूर्णांक8_t custom_pattern[10] = अणु
			0x1f, 0x7c, 0xf0, 0xc1, 0x07,
			0x1f, 0x7c, 0xf0, 0xc1, 0x07
			पूर्ण;
	काष्ठा dc_link_settings prefer_link_settings = अणुLANE_COUNT_UNKNOWN,
			LINK_RATE_UNKNOWN, LINK_SPREAD_DISABLEDपूर्ण;
	काष्ठा dc_link_settings cur_link_settings = अणुLANE_COUNT_UNKNOWN,
			LINK_RATE_UNKNOWN, LINK_SPREAD_DISABLEDपूर्ण;
	काष्ठा link_training_settings link_training_settings;
	पूर्णांक i;

	अगर (size == 0)
		वापस -EINVAL;

	wr_buf = kसुस्मृति(wr_buf_size, माप(अक्षर), GFP_KERNEL);
	अगर (!wr_buf)
		वापस -ENOSPC;

	अगर (parse_ग_लिखो_buffer_पूर्णांकo_params(wr_buf, size,
					   (दीर्घ *)param, buf,
					   max_param_num,
					   &param_nums)) अणु
		kमुक्त(wr_buf);
		वापस -EINVAL;
	पूर्ण

	अगर (param_nums <= 0) अणु
		kमुक्त(wr_buf);
		DRM_DEBUG_DRIVER("user data not be read\n");
		वापस -EINVAL;
	पूर्ण


	test_pattern = param[0];

	चयन (test_pattern) अणु
	हाल DP_TEST_PATTERN_VIDEO_MODE:
	हाल DP_TEST_PATTERN_COLOR_SQUARES:
	हाल DP_TEST_PATTERN_COLOR_SQUARES_CEA:
	हाल DP_TEST_PATTERN_VERTICAL_BARS:
	हाल DP_TEST_PATTERN_HORIZONTAL_BARS:
	हाल DP_TEST_PATTERN_COLOR_RAMP:
		valid_test_pattern = true;
		अवरोध;

	हाल DP_TEST_PATTERN_D102:
	हाल DP_TEST_PATTERN_SYMBOL_ERROR:
	हाल DP_TEST_PATTERN_PRBS7:
	हाल DP_TEST_PATTERN_80BIT_CUSTOM:
	हाल DP_TEST_PATTERN_HBR2_COMPLIANCE_EYE:
	हाल DP_TEST_PATTERN_TRAINING_PATTERN4:
		disable_hpd = true;
		valid_test_pattern = true;
		अवरोध;

	शेष:
		valid_test_pattern = false;
		test_pattern = DP_TEST_PATTERN_UNSUPPORTED;
		अवरोध;
	पूर्ण

	अगर (!valid_test_pattern) अणु
		kमुक्त(wr_buf);
		DRM_DEBUG_DRIVER("Invalid Test Pattern Parameters\n");
		वापस size;
	पूर्ण

	अगर (test_pattern == DP_TEST_PATTERN_80BIT_CUSTOM) अणु
		क्रम (i = 0; i < 10; i++) अणु
			अगर ((uपूर्णांक8_t) param[i + 1] != 0x0)
				अवरोध;
		पूर्ण

		अगर (i < 10) अणु
			/* not use शेष value */
			क्रम (i = 0; i < 10; i++)
				custom_pattern[i] = (uपूर्णांक8_t) param[i + 1];
		पूर्ण
	पूर्ण

	/* Usage: set DP physical test pattern using debugfs with normal DP
	 * panel. Then plug out DP panel and connect a scope to measure
	 * For normal video mode and test pattern generated from CRCT,
	 * they are visibile to user. So करो not disable HPD.
	 * Video Mode is also set to clear the test pattern, so enable HPD
	 * because it might have been disabled after a test pattern was set.
	 * AUX depends on HPD * sequence dependent, करो not move!
	 */
	अगर (!disable_hpd)
		dc_link_enable_hpd(link);

	prefer_link_settings.lane_count = link->verअगरied_link_cap.lane_count;
	prefer_link_settings.link_rate = link->verअगरied_link_cap.link_rate;
	prefer_link_settings.link_spपढ़ो = link->verअगरied_link_cap.link_spपढ़ो;

	cur_link_settings.lane_count = link->cur_link_settings.lane_count;
	cur_link_settings.link_rate = link->cur_link_settings.link_rate;
	cur_link_settings.link_spपढ़ो = link->cur_link_settings.link_spपढ़ो;

	link_training_settings.link_settings = cur_link_settings;


	अगर (test_pattern != DP_TEST_PATTERN_VIDEO_MODE) अणु
		अगर (prefer_link_settings.lane_count != LANE_COUNT_UNKNOWN &&
			prefer_link_settings.link_rate !=  LINK_RATE_UNKNOWN &&
			(prefer_link_settings.lane_count != cur_link_settings.lane_count ||
			prefer_link_settings.link_rate != cur_link_settings.link_rate))
			link_training_settings.link_settings = prefer_link_settings;
	पूर्ण

	क्रम (i = 0; i < (अचिन्हित पूर्णांक)(link_training_settings.link_settings.lane_count); i++)
		link_training_settings.lane_settings[i] = link->cur_lane_setting;

	dc_link_set_test_pattern(
		link,
		test_pattern,
		DP_TEST_PATTERN_COLOR_SPACE_RGB,
		&link_training_settings,
		custom_pattern,
		10);

	/* Usage: Set DP physical test pattern using AMDDP with normal DP panel
	 * Then plug out DP panel and connect a scope to measure DP PHY संकेत.
	 * Need disable पूर्णांकerrupt to aव्योम SW driver disable DP output. This is
	 * करोne after the test pattern is set.
	 */
	अगर (valid_test_pattern && disable_hpd)
		dc_link_disable_hpd(link);

	kमुक्त(wr_buf);

	वापस size;
पूर्ण

/*
 * Returns the DMCUB tracebuffer contents.
 * Example usage: cat /sys/kernel/debug/dri/0/amdgpu_dm_dmub_tracebuffer
 */
अटल पूर्णांक dmub_tracebuffer_show(काष्ठा seq_file *m, व्योम *data)
अणु
	काष्ठा amdgpu_device *adev = m->निजी;
	काष्ठा dmub_srv_fb_info *fb_info = adev->dm.dmub_fb_info;
	काष्ठा dmub_debugfs_trace_entry *entries;
	uपूर्णांक8_t *tbuf_base;
	uपूर्णांक32_t tbuf_size, max_entries, num_entries, i;

	अगर (!fb_info)
		वापस 0;

	tbuf_base = (uपूर्णांक8_t *)fb_info->fb[DMUB_WINDOW_5_TRACEBUFF].cpu_addr;
	अगर (!tbuf_base)
		वापस 0;

	tbuf_size = fb_info->fb[DMUB_WINDOW_5_TRACEBUFF].size;
	max_entries = (tbuf_size - माप(काष्ठा dmub_debugfs_trace_header)) /
		      माप(काष्ठा dmub_debugfs_trace_entry);

	num_entries =
		((काष्ठा dmub_debugfs_trace_header *)tbuf_base)->entry_count;

	num_entries = min(num_entries, max_entries);

	entries = (काष्ठा dmub_debugfs_trace_entry
			   *)(tbuf_base +
			      माप(काष्ठा dmub_debugfs_trace_header));

	क्रम (i = 0; i < num_entries; ++i) अणु
		काष्ठा dmub_debugfs_trace_entry *entry = &entries[i];

		seq_म_लिखो(m,
			   "trace_code=%u tick_count=%u param0=%u param1=%u\n",
			   entry->trace_code, entry->tick_count, entry->param0,
			   entry->param1);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Returns the DMCUB firmware state contents.
 * Example usage: cat /sys/kernel/debug/dri/0/amdgpu_dm_dmub_fw_state
 */
अटल पूर्णांक dmub_fw_state_show(काष्ठा seq_file *m, व्योम *data)
अणु
	काष्ठा amdgpu_device *adev = m->निजी;
	काष्ठा dmub_srv_fb_info *fb_info = adev->dm.dmub_fb_info;
	uपूर्णांक8_t *state_base;
	uपूर्णांक32_t state_size;

	अगर (!fb_info)
		वापस 0;

	state_base = (uपूर्णांक8_t *)fb_info->fb[DMUB_WINDOW_6_FW_STATE].cpu_addr;
	अगर (!state_base)
		वापस 0;

	state_size = fb_info->fb[DMUB_WINDOW_6_FW_STATE].size;

	वापस seq_ग_लिखो(m, state_base, state_size);
पूर्ण

/*
 * Returns the current and maximum output bpc क्रम the connector.
 * Example usage: cat /sys/kernel/debug/dri/0/DP-1/output_bpc
 */
अटल पूर्णांक output_bpc_show(काष्ठा seq_file *m, व्योम *data)
अणु
	काष्ठा drm_connector *connector = m->निजी;
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा drm_crtc *crtc = शून्य;
	काष्ठा dm_crtc_state *dm_crtc_state = शून्य;
	पूर्णांक res = -ENODEV;
	अचिन्हित पूर्णांक bpc;

	mutex_lock(&dev->mode_config.mutex);
	drm_modeset_lock(&dev->mode_config.connection_mutex, शून्य);

	अगर (connector->state == शून्य)
		जाओ unlock;

	crtc = connector->state->crtc;
	अगर (crtc == शून्य)
		जाओ unlock;

	drm_modeset_lock(&crtc->mutex, शून्य);
	अगर (crtc->state == शून्य)
		जाओ unlock;

	dm_crtc_state = to_dm_crtc_state(crtc->state);
	अगर (dm_crtc_state->stream == शून्य)
		जाओ unlock;

	चयन (dm_crtc_state->stream->timing.display_color_depth) अणु
	हाल COLOR_DEPTH_666:
		bpc = 6;
		अवरोध;
	हाल COLOR_DEPTH_888:
		bpc = 8;
		अवरोध;
	हाल COLOR_DEPTH_101010:
		bpc = 10;
		अवरोध;
	हाल COLOR_DEPTH_121212:
		bpc = 12;
		अवरोध;
	हाल COLOR_DEPTH_161616:
		bpc = 16;
		अवरोध;
	शेष:
		जाओ unlock;
	पूर्ण

	seq_म_लिखो(m, "Current: %u\n", bpc);
	seq_म_लिखो(m, "Maximum: %u\n", connector->display_info.bpc);
	res = 0;

unlock:
	अगर (crtc)
		drm_modeset_unlock(&crtc->mutex);

	drm_modeset_unlock(&dev->mode_config.connection_mutex);
	mutex_unlock(&dev->mode_config.mutex);

	वापस res;
पूर्ण

#अगर_घोषित CONFIG_DRM_AMD_DC_HDCP
/*
 * Returns the HDCP capability of the Display (1.4 क्रम now).
 *
 * NOTE* Not all HDMI displays report their HDCP caps even when they are capable.
 * Since its rare क्रम a display to not be HDCP 1.4 capable, we set HDMI as always capable.
 *
 * Example usage: cat /sys/kernel/debug/dri/0/DP-1/hdcp_sink_capability
 *		or cat /sys/kernel/debug/dri/0/HDMI-A-1/hdcp_sink_capability
 */
अटल पूर्णांक hdcp_sink_capability_show(काष्ठा seq_file *m, व्योम *data)
अणु
	काष्ठा drm_connector *connector = m->निजी;
	काष्ठा amdgpu_dm_connector *aconnector = to_amdgpu_dm_connector(connector);
	bool hdcp_cap, hdcp2_cap;

	अगर (connector->status != connector_status_connected)
		वापस -ENODEV;

	seq_म_लिखो(m, "%s:%d HDCP version: ", connector->name, connector->base.id);

	hdcp_cap = dc_link_is_hdcp14(aconnector->dc_link, aconnector->dc_sink->sink_संकेत);
	hdcp2_cap = dc_link_is_hdcp22(aconnector->dc_link, aconnector->dc_sink->sink_संकेत);


	अगर (hdcp_cap)
		seq_म_लिखो(m, "%s ", "HDCP1.4");
	अगर (hdcp2_cap)
		seq_म_लिखो(m, "%s ", "HDCP2.2");

	अगर (!hdcp_cap && !hdcp2_cap)
		seq_म_लिखो(m, "%s ", "None");

	seq_माला_दो(m, "\n");

	वापस 0;
पूर्ण
#पूर्ण_अगर
/* function description
 *
 * generic SDP message access क्रम testing
 *
 * debugfs sdp_message is located at /syskernel/debug/dri/0/DP-x
 *
 * SDP header
 * Hb0 : Secondary-Data Packet ID
 * Hb1 : Secondary-Data Packet type
 * Hb2 : Secondary-Data-packet-specअगरic header, Byte 0
 * Hb3 : Secondary-Data-packet-specअगरic header, Byte 1
 *
 * क्रम using custom sdp message: input 4 bytes SDP header and 32 bytes raw data
 */
अटल sमाप_प्रकार dp_sdp_message_debugfs_ग_लिखो(काष्ठा file *f, स्थिर अक्षर __user *buf,
				 माप_प्रकार size, loff_t *pos)
अणु
	पूर्णांक r;
	uपूर्णांक8_t data[36];
	काष्ठा amdgpu_dm_connector *connector = file_inode(f)->i_निजी;
	काष्ठा dm_crtc_state *acrtc_state;
	uपूर्णांक32_t ग_लिखो_size = 36;

	अगर (connector->base.status != connector_status_connected)
		वापस -ENODEV;

	अगर (size == 0)
		वापस 0;

	acrtc_state = to_dm_crtc_state(connector->base.state->crtc->state);

	r = copy_from_user(data, buf, ग_लिखो_size);

	ग_लिखो_size -= r;

	dc_stream_send_dp_sdp(acrtc_state->stream, data, ग_लिखो_size);

	वापस ग_लिखो_size;
पूर्ण

अटल sमाप_प्रकार dp_dpcd_address_ग_लिखो(काष्ठा file *f, स्थिर अक्षर __user *buf,
				 माप_प्रकार size, loff_t *pos)
अणु
	पूर्णांक r;
	काष्ठा amdgpu_dm_connector *connector = file_inode(f)->i_निजी;

	अगर (size < माप(connector->debugfs_dpcd_address))
		वापस -EINVAL;

	r = copy_from_user(&connector->debugfs_dpcd_address,
			buf, माप(connector->debugfs_dpcd_address));

	वापस size - r;
पूर्ण

अटल sमाप_प्रकार dp_dpcd_size_ग_लिखो(काष्ठा file *f, स्थिर अक्षर __user *buf,
				 माप_प्रकार size, loff_t *pos)
अणु
	पूर्णांक r;
	काष्ठा amdgpu_dm_connector *connector = file_inode(f)->i_निजी;

	अगर (size < माप(connector->debugfs_dpcd_size))
		वापस -EINVAL;

	r = copy_from_user(&connector->debugfs_dpcd_size,
			buf, माप(connector->debugfs_dpcd_size));

	अगर (connector->debugfs_dpcd_size > 256)
		connector->debugfs_dpcd_size = 0;

	वापस size - r;
पूर्ण

अटल sमाप_प्रकार dp_dpcd_data_ग_लिखो(काष्ठा file *f, स्थिर अक्षर __user *buf,
				 माप_प्रकार size, loff_t *pos)
अणु
	पूर्णांक r;
	अक्षर *data;
	काष्ठा amdgpu_dm_connector *connector = file_inode(f)->i_निजी;
	काष्ठा dc_link *link = connector->dc_link;
	uपूर्णांक32_t ग_लिखो_size = connector->debugfs_dpcd_size;

	अगर (!ग_लिखो_size || size < ग_लिखो_size)
		वापस -EINVAL;

	data = kzalloc(ग_लिखो_size, GFP_KERNEL);
	अगर (!data)
		वापस 0;

	r = copy_from_user(data, buf, ग_लिखो_size);

	dm_helpers_dp_ग_लिखो_dpcd(link->ctx, link,
			connector->debugfs_dpcd_address, data, ग_लिखो_size - r);
	kमुक्त(data);
	वापस ग_लिखो_size - r;
पूर्ण

अटल sमाप_प्रकार dp_dpcd_data_पढ़ो(काष्ठा file *f, अक्षर __user *buf,
				 माप_प्रकार size, loff_t *pos)
अणु
	पूर्णांक r;
	अक्षर *data;
	काष्ठा amdgpu_dm_connector *connector = file_inode(f)->i_निजी;
	काष्ठा dc_link *link = connector->dc_link;
	uपूर्णांक32_t पढ़ो_size = connector->debugfs_dpcd_size;

	अगर (!पढ़ो_size || size < पढ़ो_size)
		वापस 0;

	data = kzalloc(पढ़ो_size, GFP_KERNEL);
	अगर (!data)
		वापस 0;

	dm_helpers_dp_पढ़ो_dpcd(link->ctx, link,
			connector->debugfs_dpcd_address, data, पढ़ो_size);

	r = copy_to_user(buf, data, पढ़ो_size);

	kमुक्त(data);
	वापस पढ़ो_size - r;
पूर्ण

/* function: Read link's DSC & FEC capabilities
 *
 *
 * Access it with the following command (you need to specअगरy
 * connector like DP-1):
 *
 *	cat /sys/kernel/debug/dri/0/DP-X/dp_dsc_fec_support
 *
 */
अटल पूर्णांक dp_dsc_fec_support_show(काष्ठा seq_file *m, व्योम *data)
अणु
	काष्ठा drm_connector *connector = m->निजी;
	काष्ठा drm_modeset_acquire_ctx ctx;
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा amdgpu_dm_connector *aconnector = to_amdgpu_dm_connector(connector);
	पूर्णांक ret = 0;
	bool try_again = false;
	bool is_fec_supported = false;
	bool is_dsc_supported = false;
	काष्ठा dpcd_caps dpcd_caps;

	drm_modeset_acquire_init(&ctx, DRM_MODESET_ACQUIRE_INTERRUPTIBLE);
	करो अणु
		try_again = false;
		ret = drm_modeset_lock(&dev->mode_config.connection_mutex, &ctx);
		अगर (ret) अणु
			अगर (ret == -EDEADLK) अणु
				ret = drm_modeset_backoff(&ctx);
				अगर (!ret) अणु
					try_again = true;
					जारी;
				पूर्ण
			पूर्ण
			अवरोध;
		पूर्ण
		अगर (connector->status != connector_status_connected) अणु
			ret = -ENODEV;
			अवरोध;
		पूर्ण
		dpcd_caps = aconnector->dc_link->dpcd_caps;
		अगर (aconnector->port) अणु
			/* aconnector sets dsc_aux during get_modes call
			 * अगर MST connector has it means it can either
			 * enable DSC on the sink device or on MST branch
			 * its connected to.
			 */
			अगर (aconnector->dsc_aux) अणु
				is_fec_supported = true;
				is_dsc_supported = true;
			पूर्ण
		पूर्ण अन्यथा अणु
			is_fec_supported = dpcd_caps.fec_cap.raw & 0x1;
			is_dsc_supported = dpcd_caps.dsc_caps.dsc_basic_caps.raw[0] & 0x1;
		पूर्ण
	पूर्ण जबतक (try_again);

	drm_modeset_drop_locks(&ctx);
	drm_modeset_acquire_fini(&ctx);

	seq_म_लिखो(m, "FEC_Sink_Support: %s\n", yesno(is_fec_supported));
	seq_म_लिखो(m, "DSC_Sink_Support: %s\n", yesno(is_dsc_supported));

	वापस ret;
पूर्ण

/* function: Trigger भव HPD redetection on connector
 *
 * This function will perक्रमm link rediscovery, link disable
 * and enable, and dm connector state update.
 *
 * Retrigger HPD on an existing connector by echoing 1 पूर्णांकo
 * its respectful "trigger_hotplug" debugfs entry:
 *
 *	echo 1 > /sys/kernel/debug/dri/0/DP-X/trigger_hotplug
 *
 * This function can perक्रमm HPD unplug:
 *
 *	echo 0 > /sys/kernel/debug/dri/0/DP-X/trigger_hotplug
 *
 */
अटल sमाप_प्रकार trigger_hotplug(काष्ठा file *f, स्थिर अक्षर __user *buf,
							माप_प्रकार size, loff_t *pos)
अणु
	काष्ठा amdgpu_dm_connector *aconnector = file_inode(f)->i_निजी;
	काष्ठा drm_connector *connector = &aconnector->base;
	काष्ठा dc_link *link = शून्य;
	काष्ठा drm_device *dev = connector->dev;
	क्रमागत dc_connection_type new_connection_type = dc_connection_none;
	अक्षर *wr_buf = शून्य;
	uपूर्णांक32_t wr_buf_size = 42;
	पूर्णांक max_param_num = 1;
	दीर्घ param[1] = अणु0पूर्ण;
	uपूर्णांक8_t param_nums = 0;

	अगर (!aconnector || !aconnector->dc_link)
		वापस -EINVAL;

	अगर (size == 0)
		वापस -EINVAL;

	wr_buf = kसुस्मृति(wr_buf_size, माप(अक्षर), GFP_KERNEL);

	अगर (!wr_buf) अणु
		DRM_DEBUG_DRIVER("no memory to allocate write buffer\n");
		वापस -ENOSPC;
	पूर्ण

	अगर (parse_ग_लिखो_buffer_पूर्णांकo_params(wr_buf, size,
						(दीर्घ *)param, buf,
						max_param_num,
						&param_nums)) अणु
		kमुक्त(wr_buf);
		वापस -EINVAL;
	पूर्ण

	अगर (param_nums <= 0) अणु
		DRM_DEBUG_DRIVER("user data not be read\n");
		kमुक्त(wr_buf);
		वापस -EINVAL;
	पूर्ण

	अगर (param[0] == 1) अणु
		mutex_lock(&aconnector->hpd_lock);

		अगर (!dc_link_detect_sink(aconnector->dc_link, &new_connection_type) &&
			new_connection_type != dc_connection_none)
			जाओ unlock;

		अगर (!dc_link_detect(aconnector->dc_link, DETECT_REASON_HPD))
			जाओ unlock;

		amdgpu_dm_update_connector_after_detect(aconnector);

		drm_modeset_lock_all(dev);
		dm_restore_drm_connector_state(dev, connector);
		drm_modeset_unlock_all(dev);

		drm_kms_helper_hotplug_event(dev);
	पूर्ण अन्यथा अगर (param[0] == 0) अणु
		अगर (!aconnector->dc_link)
			जाओ unlock;

		link = aconnector->dc_link;

		अगर (link->local_sink) अणु
			dc_sink_release(link->local_sink);
			link->local_sink = शून्य;
		पूर्ण

		link->dpcd_sink_count = 0;
		link->type = dc_connection_none;
		link->करोngle_max_pix_clk = 0;

		amdgpu_dm_update_connector_after_detect(aconnector);

		drm_modeset_lock_all(dev);
		dm_restore_drm_connector_state(dev, connector);
		drm_modeset_unlock_all(dev);

		drm_kms_helper_hotplug_event(dev);
	पूर्ण

unlock:
	mutex_unlock(&aconnector->hpd_lock);

	kमुक्त(wr_buf);
	वापस size;
पूर्ण

/* function: पढ़ो DSC status on the connector
 *
 * The पढ़ो function: dp_dsc_घड़ी_en_पढ़ो
 * वापसs current status of DSC घड़ी on the connector.
 * The वापस is a boolean flag: 1 or 0.
 *
 * Access it with the following command (you need to specअगरy
 * connector like DP-1):
 *
 *	cat /sys/kernel/debug/dri/0/DP-X/dsc_घड़ी_en
 *
 * Expected output:
 * 1 - means that DSC is currently enabled
 * 0 - means that DSC is disabled
 */
अटल sमाप_प्रकार dp_dsc_घड़ी_en_पढ़ो(काष्ठा file *f, अक्षर __user *buf,
				    माप_प्रकार size, loff_t *pos)
अणु
	अक्षर *rd_buf = शून्य;
	अक्षर *rd_buf_ptr = शून्य;
	काष्ठा amdgpu_dm_connector *aconnector = file_inode(f)->i_निजी;
	काष्ठा display_stream_compressor *dsc;
	काष्ठा dcn_dsc_state dsc_state = अणु0पूर्ण;
	स्थिर uपूर्णांक32_t rd_buf_size = 10;
	काष्ठा pipe_ctx *pipe_ctx;
	sमाप_प्रकार result = 0;
	पूर्णांक i, r, str_len = 30;

	rd_buf = kसुस्मृति(rd_buf_size, माप(अक्षर), GFP_KERNEL);

	अगर (!rd_buf)
		वापस -ENOMEM;

	rd_buf_ptr = rd_buf;

	क्रम (i = 0; i < MAX_PIPES; i++) अणु
		pipe_ctx = &aconnector->dc_link->dc->current_state->res_ctx.pipe_ctx[i];
			अगर (pipe_ctx && pipe_ctx->stream &&
			    pipe_ctx->stream->link == aconnector->dc_link)
				अवरोध;
	पूर्ण

	अगर (!pipe_ctx)
		वापस -ENXIO;

	dsc = pipe_ctx->stream_res.dsc;
	अगर (dsc)
		dsc->funcs->dsc_पढ़ो_state(dsc, &dsc_state);

	snम_लिखो(rd_buf_ptr, str_len,
		"%d\n",
		dsc_state.dsc_घड़ी_en);
	rd_buf_ptr += str_len;

	जबतक (size) अणु
		अगर (*pos >= rd_buf_size)
			अवरोध;

		r = put_user(*(rd_buf + result), buf);
		अगर (r)
			वापस r; /* r = -EFAULT */

		buf += 1;
		size -= 1;
		*pos += 1;
		result += 1;
	पूर्ण

	kमुक्त(rd_buf);
	वापस result;
पूर्ण

/* function: ग_लिखो क्रमce DSC on the connector
 *
 * The ग_लिखो function: dp_dsc_घड़ी_en_ग_लिखो
 * enables to क्रमce DSC on the connector.
 * User can ग_लिखो to either क्रमce enable or क्रमce disable DSC
 * on the next modeset or set it to driver शेष
 *
 * Accepted inमाला_दो:
 * 0 - शेष DSC enablement policy
 * 1 - क्रमce enable DSC on the connector
 * 2 - क्रमce disable DSC on the connector (might cause fail in atomic_check)
 *
 * Writing DSC settings is करोne with the following command:
 * - To क्रमce enable DSC (you need to specअगरy
 * connector like DP-1):
 *
 *	echo 0x1 > /sys/kernel/debug/dri/0/DP-X/dsc_घड़ी_en
 *
 * - To वापस to शेष state set the flag to zero and
 * let driver deal with DSC स्वतःmatically
 * (you need to specअगरy connector like DP-1):
 *
 *	echo 0x0 > /sys/kernel/debug/dri/0/DP-X/dsc_घड़ी_en
 *
 */
अटल sमाप_प्रकार dp_dsc_घड़ी_en_ग_लिखो(काष्ठा file *f, स्थिर अक्षर __user *buf,
				     माप_प्रकार size, loff_t *pos)
अणु
	काष्ठा amdgpu_dm_connector *aconnector = file_inode(f)->i_निजी;
	काष्ठा drm_connector *connector = &aconnector->base;
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा drm_crtc *crtc = शून्य;
	काष्ठा dm_crtc_state *dm_crtc_state = शून्य;
	काष्ठा pipe_ctx *pipe_ctx;
	पूर्णांक i;
	अक्षर *wr_buf = शून्य;
	uपूर्णांक32_t wr_buf_size = 42;
	पूर्णांक max_param_num = 1;
	दीर्घ param[1] = अणु0पूर्ण;
	uपूर्णांक8_t param_nums = 0;

	अगर (size == 0)
		वापस -EINVAL;

	wr_buf = kसुस्मृति(wr_buf_size, माप(अक्षर), GFP_KERNEL);

	अगर (!wr_buf) अणु
		DRM_DEBUG_DRIVER("no memory to allocate write buffer\n");
		वापस -ENOSPC;
	पूर्ण

	अगर (parse_ग_लिखो_buffer_पूर्णांकo_params(wr_buf, size,
					    (दीर्घ *)param, buf,
					    max_param_num,
					    &param_nums)) अणु
		kमुक्त(wr_buf);
		वापस -EINVAL;
	पूर्ण

	अगर (param_nums <= 0) अणु
		DRM_DEBUG_DRIVER("user data not be read\n");
		kमुक्त(wr_buf);
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < MAX_PIPES; i++) अणु
		pipe_ctx = &aconnector->dc_link->dc->current_state->res_ctx.pipe_ctx[i];
			अगर (pipe_ctx && pipe_ctx->stream &&
			    pipe_ctx->stream->link == aconnector->dc_link)
				अवरोध;
	पूर्ण

	अगर (!pipe_ctx || !pipe_ctx->stream)
		जाओ करोne;

	// Get CRTC state
	mutex_lock(&dev->mode_config.mutex);
	drm_modeset_lock(&dev->mode_config.connection_mutex, शून्य);

	अगर (connector->state == शून्य)
		जाओ unlock;

	crtc = connector->state->crtc;
	अगर (crtc == शून्य)
		जाओ unlock;

	drm_modeset_lock(&crtc->mutex, शून्य);
	अगर (crtc->state == शून्य)
		जाओ unlock;

	dm_crtc_state = to_dm_crtc_state(crtc->state);
	अगर (dm_crtc_state->stream == शून्य)
		जाओ unlock;

	अगर (param[0] == 1)
		aconnector->dsc_settings.dsc_क्रमce_enable = DSC_CLK_FORCE_ENABLE;
	अन्यथा अगर (param[0] == 2)
		aconnector->dsc_settings.dsc_क्रमce_enable = DSC_CLK_FORCE_DISABLE;
	अन्यथा
		aconnector->dsc_settings.dsc_क्रमce_enable = DSC_CLK_FORCE_DEFAULT;

	dm_crtc_state->dsc_क्रमce_changed = true;

unlock:
	अगर (crtc)
		drm_modeset_unlock(&crtc->mutex);
	drm_modeset_unlock(&dev->mode_config.connection_mutex);
	mutex_unlock(&dev->mode_config.mutex);

करोne:
	kमुक्त(wr_buf);
	वापस size;
पूर्ण

/* function: पढ़ो DSC slice width parameter on the connector
 *
 * The पढ़ो function: dp_dsc_slice_width_पढ़ो
 * वापसs dsc slice width used in the current configuration
 * The वापस is an पूर्णांकeger: 0 or other positive number
 *
 * Access the status with the following command:
 *
 *	cat /sys/kernel/debug/dri/0/DP-X/dsc_slice_width
 *
 * 0 - means that DSC is disabled
 *
 * Any other number more than zero represents the
 * slice width currently used by DSC in pixels
 *
 */
अटल sमाप_प्रकार dp_dsc_slice_width_पढ़ो(काष्ठा file *f, अक्षर __user *buf,
				    माप_प्रकार size, loff_t *pos)
अणु
	अक्षर *rd_buf = शून्य;
	अक्षर *rd_buf_ptr = शून्य;
	काष्ठा amdgpu_dm_connector *aconnector = file_inode(f)->i_निजी;
	काष्ठा display_stream_compressor *dsc;
	काष्ठा dcn_dsc_state dsc_state = अणु0पूर्ण;
	स्थिर uपूर्णांक32_t rd_buf_size = 100;
	काष्ठा pipe_ctx *pipe_ctx;
	sमाप_प्रकार result = 0;
	पूर्णांक i, r, str_len = 30;

	rd_buf = kसुस्मृति(rd_buf_size, माप(अक्षर), GFP_KERNEL);

	अगर (!rd_buf)
		वापस -ENOMEM;

	rd_buf_ptr = rd_buf;

	क्रम (i = 0; i < MAX_PIPES; i++) अणु
		pipe_ctx = &aconnector->dc_link->dc->current_state->res_ctx.pipe_ctx[i];
			अगर (pipe_ctx && pipe_ctx->stream &&
			    pipe_ctx->stream->link == aconnector->dc_link)
				अवरोध;
	पूर्ण

	अगर (!pipe_ctx)
		वापस -ENXIO;

	dsc = pipe_ctx->stream_res.dsc;
	अगर (dsc)
		dsc->funcs->dsc_पढ़ो_state(dsc, &dsc_state);

	snम_लिखो(rd_buf_ptr, str_len,
		"%d\n",
		dsc_state.dsc_slice_width);
	rd_buf_ptr += str_len;

	जबतक (size) अणु
		अगर (*pos >= rd_buf_size)
			अवरोध;

		r = put_user(*(rd_buf + result), buf);
		अगर (r)
			वापस r; /* r = -EFAULT */

		buf += 1;
		size -= 1;
		*pos += 1;
		result += 1;
	पूर्ण

	kमुक्त(rd_buf);
	वापस result;
पूर्ण

/* function: ग_लिखो DSC slice width parameter
 *
 * The ग_लिखो function: dp_dsc_slice_width_ग_लिखो
 * overग_लिखोs स्वतःmatically generated DSC configuration
 * of slice width.
 *
 * The user has to ग_लिखो the slice width भागisible by the
 * picture width.
 *
 * Also the user has to ग_लिखो width in hexidecimal
 * rather than in decimal.
 *
 * Writing DSC settings is करोne with the following command:
 * - To क्रमce overग_लिखो slice width: (example sets to 1920 pixels)
 *
 *	echo 0x780 > /sys/kernel/debug/dri/0/DP-X/dsc_slice_width
 *
 *  - To stop overwriting and let driver find the optimal size,
 * set the width to zero:
 *
 *	echo 0x0 > /sys/kernel/debug/dri/0/DP-X/dsc_slice_width
 *
 */
अटल sमाप_प्रकार dp_dsc_slice_width_ग_लिखो(काष्ठा file *f, स्थिर अक्षर __user *buf,
				     माप_प्रकार size, loff_t *pos)
अणु
	काष्ठा amdgpu_dm_connector *aconnector = file_inode(f)->i_निजी;
	काष्ठा pipe_ctx *pipe_ctx;
	काष्ठा drm_connector *connector = &aconnector->base;
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा drm_crtc *crtc = शून्य;
	काष्ठा dm_crtc_state *dm_crtc_state = शून्य;
	पूर्णांक i;
	अक्षर *wr_buf = शून्य;
	uपूर्णांक32_t wr_buf_size = 42;
	पूर्णांक max_param_num = 1;
	दीर्घ param[1] = अणु0पूर्ण;
	uपूर्णांक8_t param_nums = 0;

	अगर (size == 0)
		वापस -EINVAL;

	wr_buf = kसुस्मृति(wr_buf_size, माप(अक्षर), GFP_KERNEL);

	अगर (!wr_buf) अणु
		DRM_DEBUG_DRIVER("no memory to allocate write buffer\n");
		वापस -ENOSPC;
	पूर्ण

	अगर (parse_ग_लिखो_buffer_पूर्णांकo_params(wr_buf, size,
					    (दीर्घ *)param, buf,
					    max_param_num,
					    &param_nums)) अणु
		kमुक्त(wr_buf);
		वापस -EINVAL;
	पूर्ण

	अगर (param_nums <= 0) अणु
		DRM_DEBUG_DRIVER("user data not be read\n");
		kमुक्त(wr_buf);
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < MAX_PIPES; i++) अणु
		pipe_ctx = &aconnector->dc_link->dc->current_state->res_ctx.pipe_ctx[i];
			अगर (pipe_ctx && pipe_ctx->stream &&
			    pipe_ctx->stream->link == aconnector->dc_link)
				अवरोध;
	पूर्ण

	अगर (!pipe_ctx || !pipe_ctx->stream)
		जाओ करोne;

	// Safely get CRTC state
	mutex_lock(&dev->mode_config.mutex);
	drm_modeset_lock(&dev->mode_config.connection_mutex, शून्य);

	अगर (connector->state == शून्य)
		जाओ unlock;

	crtc = connector->state->crtc;
	अगर (crtc == शून्य)
		जाओ unlock;

	drm_modeset_lock(&crtc->mutex, शून्य);
	अगर (crtc->state == शून्य)
		जाओ unlock;

	dm_crtc_state = to_dm_crtc_state(crtc->state);
	अगर (dm_crtc_state->stream == शून्य)
		जाओ unlock;

	अगर (param[0] > 0)
		aconnector->dsc_settings.dsc_num_slices_h = DIV_ROUND_UP(
					pipe_ctx->stream->timing.h_addressable,
					param[0]);
	अन्यथा
		aconnector->dsc_settings.dsc_num_slices_h = 0;

	dm_crtc_state->dsc_क्रमce_changed = true;

unlock:
	अगर (crtc)
		drm_modeset_unlock(&crtc->mutex);
	drm_modeset_unlock(&dev->mode_config.connection_mutex);
	mutex_unlock(&dev->mode_config.mutex);

करोne:
	kमुक्त(wr_buf);
	वापस size;
पूर्ण

/* function: पढ़ो DSC slice height parameter on the connector
 *
 * The पढ़ो function: dp_dsc_slice_height_पढ़ो
 * वापसs dsc slice height used in the current configuration
 * The वापस is an पूर्णांकeger: 0 or other positive number
 *
 * Access the status with the following command:
 *
 *	cat /sys/kernel/debug/dri/0/DP-X/dsc_slice_height
 *
 * 0 - means that DSC is disabled
 *
 * Any other number more than zero represents the
 * slice height currently used by DSC in pixels
 *
 */
अटल sमाप_प्रकार dp_dsc_slice_height_पढ़ो(काष्ठा file *f, अक्षर __user *buf,
				    माप_प्रकार size, loff_t *pos)
अणु
	अक्षर *rd_buf = शून्य;
	अक्षर *rd_buf_ptr = शून्य;
	काष्ठा amdgpu_dm_connector *aconnector = file_inode(f)->i_निजी;
	काष्ठा display_stream_compressor *dsc;
	काष्ठा dcn_dsc_state dsc_state = अणु0पूर्ण;
	स्थिर uपूर्णांक32_t rd_buf_size = 100;
	काष्ठा pipe_ctx *pipe_ctx;
	sमाप_प्रकार result = 0;
	पूर्णांक i, r, str_len = 30;

	rd_buf = kसुस्मृति(rd_buf_size, माप(अक्षर), GFP_KERNEL);

	अगर (!rd_buf)
		वापस -ENOMEM;

	rd_buf_ptr = rd_buf;

	क्रम (i = 0; i < MAX_PIPES; i++) अणु
		pipe_ctx = &aconnector->dc_link->dc->current_state->res_ctx.pipe_ctx[i];
			अगर (pipe_ctx && pipe_ctx->stream &&
			    pipe_ctx->stream->link == aconnector->dc_link)
				अवरोध;
	पूर्ण

	अगर (!pipe_ctx)
		वापस -ENXIO;

	dsc = pipe_ctx->stream_res.dsc;
	अगर (dsc)
		dsc->funcs->dsc_पढ़ो_state(dsc, &dsc_state);

	snम_लिखो(rd_buf_ptr, str_len,
		"%d\n",
		dsc_state.dsc_slice_height);
	rd_buf_ptr += str_len;

	जबतक (size) अणु
		अगर (*pos >= rd_buf_size)
			अवरोध;

		r = put_user(*(rd_buf + result), buf);
		अगर (r)
			वापस r; /* r = -EFAULT */

		buf += 1;
		size -= 1;
		*pos += 1;
		result += 1;
	पूर्ण

	kमुक्त(rd_buf);
	वापस result;
पूर्ण

/* function: ग_लिखो DSC slice height parameter
 *
 * The ग_लिखो function: dp_dsc_slice_height_ग_लिखो
 * overग_लिखोs स्वतःmatically generated DSC configuration
 * of slice height.
 *
 * The user has to ग_लिखो the slice height भागisible by the
 * picture height.
 *
 * Also the user has to ग_लिखो height in hexidecimal
 * rather than in decimal.
 *
 * Writing DSC settings is करोne with the following command:
 * - To क्रमce overग_लिखो slice height (example sets to 128 pixels):
 *
 *	echo 0x80 > /sys/kernel/debug/dri/0/DP-X/dsc_slice_height
 *
 *  - To stop overwriting and let driver find the optimal size,
 * set the height to zero:
 *
 *	echo 0x0 > /sys/kernel/debug/dri/0/DP-X/dsc_slice_height
 *
 */
अटल sमाप_प्रकार dp_dsc_slice_height_ग_लिखो(काष्ठा file *f, स्थिर अक्षर __user *buf,
				     माप_प्रकार size, loff_t *pos)
अणु
	काष्ठा amdgpu_dm_connector *aconnector = file_inode(f)->i_निजी;
	काष्ठा drm_connector *connector = &aconnector->base;
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा drm_crtc *crtc = शून्य;
	काष्ठा dm_crtc_state *dm_crtc_state = शून्य;
	काष्ठा pipe_ctx *pipe_ctx;
	पूर्णांक i;
	अक्षर *wr_buf = शून्य;
	uपूर्णांक32_t wr_buf_size = 42;
	पूर्णांक max_param_num = 1;
	uपूर्णांक8_t param_nums = 0;
	दीर्घ param[1] = अणु0पूर्ण;

	अगर (size == 0)
		वापस -EINVAL;

	wr_buf = kसुस्मृति(wr_buf_size, माप(अक्षर), GFP_KERNEL);

	अगर (!wr_buf) अणु
		DRM_DEBUG_DRIVER("no memory to allocate write buffer\n");
		वापस -ENOSPC;
	पूर्ण

	अगर (parse_ग_लिखो_buffer_पूर्णांकo_params(wr_buf, size,
					    (दीर्घ *)param, buf,
					    max_param_num,
					    &param_nums)) अणु
		kमुक्त(wr_buf);
		वापस -EINVAL;
	पूर्ण

	अगर (param_nums <= 0) अणु
		DRM_DEBUG_DRIVER("user data not be read\n");
		kमुक्त(wr_buf);
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < MAX_PIPES; i++) अणु
		pipe_ctx = &aconnector->dc_link->dc->current_state->res_ctx.pipe_ctx[i];
			अगर (pipe_ctx && pipe_ctx->stream &&
			    pipe_ctx->stream->link == aconnector->dc_link)
				अवरोध;
	पूर्ण

	अगर (!pipe_ctx || !pipe_ctx->stream)
		जाओ करोne;

	// Get CRTC state
	mutex_lock(&dev->mode_config.mutex);
	drm_modeset_lock(&dev->mode_config.connection_mutex, शून्य);

	अगर (connector->state == शून्य)
		जाओ unlock;

	crtc = connector->state->crtc;
	अगर (crtc == शून्य)
		जाओ unlock;

	drm_modeset_lock(&crtc->mutex, शून्य);
	अगर (crtc->state == शून्य)
		जाओ unlock;

	dm_crtc_state = to_dm_crtc_state(crtc->state);
	अगर (dm_crtc_state->stream == शून्य)
		जाओ unlock;

	अगर (param[0] > 0)
		aconnector->dsc_settings.dsc_num_slices_v = DIV_ROUND_UP(
					pipe_ctx->stream->timing.v_addressable,
					param[0]);
	अन्यथा
		aconnector->dsc_settings.dsc_num_slices_v = 0;

	dm_crtc_state->dsc_क्रमce_changed = true;

unlock:
	अगर (crtc)
		drm_modeset_unlock(&crtc->mutex);
	drm_modeset_unlock(&dev->mode_config.connection_mutex);
	mutex_unlock(&dev->mode_config.mutex);

करोne:
	kमुक्त(wr_buf);
	वापस size;
पूर्ण

/* function: पढ़ो DSC target rate on the connector in bits per pixel
 *
 * The पढ़ो function: dp_dsc_bits_per_pixel_पढ़ो
 * वापसs target rate of compression in bits per pixel
 * The वापस is an पूर्णांकeger: 0 or other positive पूर्णांकeger
 *
 * Access it with the following command:
 *
 *	cat /sys/kernel/debug/dri/0/DP-X/dsc_bits_per_pixel
 *
 *  0 - means that DSC is disabled
 */
अटल sमाप_प्रकार dp_dsc_bits_per_pixel_पढ़ो(काष्ठा file *f, अक्षर __user *buf,
				    माप_प्रकार size, loff_t *pos)
अणु
	अक्षर *rd_buf = शून्य;
	अक्षर *rd_buf_ptr = शून्य;
	काष्ठा amdgpu_dm_connector *aconnector = file_inode(f)->i_निजी;
	काष्ठा display_stream_compressor *dsc;
	काष्ठा dcn_dsc_state dsc_state = अणु0पूर्ण;
	स्थिर uपूर्णांक32_t rd_buf_size = 100;
	काष्ठा pipe_ctx *pipe_ctx;
	sमाप_प्रकार result = 0;
	पूर्णांक i, r, str_len = 30;

	rd_buf = kसुस्मृति(rd_buf_size, माप(अक्षर), GFP_KERNEL);

	अगर (!rd_buf)
		वापस -ENOMEM;

	rd_buf_ptr = rd_buf;

	क्रम (i = 0; i < MAX_PIPES; i++) अणु
		pipe_ctx = &aconnector->dc_link->dc->current_state->res_ctx.pipe_ctx[i];
			अगर (pipe_ctx && pipe_ctx->stream &&
			    pipe_ctx->stream->link == aconnector->dc_link)
				अवरोध;
	पूर्ण

	अगर (!pipe_ctx)
		वापस -ENXIO;

	dsc = pipe_ctx->stream_res.dsc;
	अगर (dsc)
		dsc->funcs->dsc_पढ़ो_state(dsc, &dsc_state);

	snम_लिखो(rd_buf_ptr, str_len,
		"%d\n",
		dsc_state.dsc_bits_per_pixel);
	rd_buf_ptr += str_len;

	जबतक (size) अणु
		अगर (*pos >= rd_buf_size)
			अवरोध;

		r = put_user(*(rd_buf + result), buf);
		अगर (r)
			वापस r; /* r = -EFAULT */

		buf += 1;
		size -= 1;
		*pos += 1;
		result += 1;
	पूर्ण

	kमुक्त(rd_buf);
	वापस result;
पूर्ण

/* function: ग_लिखो DSC target rate in bits per pixel
 *
 * The ग_लिखो function: dp_dsc_bits_per_pixel_ग_लिखो
 * overग_लिखोs स्वतःmatically generated DSC configuration
 * of DSC target bit rate.
 *
 * Also the user has to ग_लिखो bpp in hexidecimal
 * rather than in decimal.
 *
 * Writing DSC settings is करोne with the following command:
 * - To क्रमce overग_लिखो rate (example sets to 256 bpp x 1/16):
 *
 *	echo 0x100 > /sys/kernel/debug/dri/0/DP-X/dsc_bits_per_pixel
 *
 *  - To stop overwriting and let driver find the optimal rate,
 * set the rate to zero:
 *
 *	echo 0x0 > /sys/kernel/debug/dri/0/DP-X/dsc_bits_per_pixel
 *
 */
अटल sमाप_प्रकार dp_dsc_bits_per_pixel_ग_लिखो(काष्ठा file *f, स्थिर अक्षर __user *buf,
				     माप_प्रकार size, loff_t *pos)
अणु
	काष्ठा amdgpu_dm_connector *aconnector = file_inode(f)->i_निजी;
	काष्ठा drm_connector *connector = &aconnector->base;
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा drm_crtc *crtc = शून्य;
	काष्ठा dm_crtc_state *dm_crtc_state = शून्य;
	काष्ठा pipe_ctx *pipe_ctx;
	पूर्णांक i;
	अक्षर *wr_buf = शून्य;
	uपूर्णांक32_t wr_buf_size = 42;
	पूर्णांक max_param_num = 1;
	uपूर्णांक8_t param_nums = 0;
	दीर्घ param[1] = अणु0पूर्ण;

	अगर (size == 0)
		वापस -EINVAL;

	wr_buf = kसुस्मृति(wr_buf_size, माप(अक्षर), GFP_KERNEL);

	अगर (!wr_buf) अणु
		DRM_DEBUG_DRIVER("no memory to allocate write buffer\n");
		वापस -ENOSPC;
	पूर्ण

	अगर (parse_ग_लिखो_buffer_पूर्णांकo_params(wr_buf, size,
					    (दीर्घ *)param, buf,
					    max_param_num,
					    &param_nums)) अणु
		kमुक्त(wr_buf);
		वापस -EINVAL;
	पूर्ण

	अगर (param_nums <= 0) अणु
		DRM_DEBUG_DRIVER("user data not be read\n");
		kमुक्त(wr_buf);
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < MAX_PIPES; i++) अणु
		pipe_ctx = &aconnector->dc_link->dc->current_state->res_ctx.pipe_ctx[i];
			अगर (pipe_ctx && pipe_ctx->stream &&
			    pipe_ctx->stream->link == aconnector->dc_link)
				अवरोध;
	पूर्ण

	अगर (!pipe_ctx || !pipe_ctx->stream)
		जाओ करोne;

	// Get CRTC state
	mutex_lock(&dev->mode_config.mutex);
	drm_modeset_lock(&dev->mode_config.connection_mutex, शून्य);

	अगर (connector->state == शून्य)
		जाओ unlock;

	crtc = connector->state->crtc;
	अगर (crtc == शून्य)
		जाओ unlock;

	drm_modeset_lock(&crtc->mutex, शून्य);
	अगर (crtc->state == शून्य)
		जाओ unlock;

	dm_crtc_state = to_dm_crtc_state(crtc->state);
	अगर (dm_crtc_state->stream == शून्य)
		जाओ unlock;

	aconnector->dsc_settings.dsc_bits_per_pixel = param[0];

	dm_crtc_state->dsc_क्रमce_changed = true;

unlock:
	अगर (crtc)
		drm_modeset_unlock(&crtc->mutex);
	drm_modeset_unlock(&dev->mode_config.connection_mutex);
	mutex_unlock(&dev->mode_config.mutex);

करोne:
	kमुक्त(wr_buf);
	वापस size;
पूर्ण

/* function: पढ़ो DSC picture width parameter on the connector
 *
 * The पढ़ो function: dp_dsc_pic_width_पढ़ो
 * वापसs dsc picture width used in the current configuration
 * It is the same as h_addressable of the current
 * display's timing
 * The वापस is an पूर्णांकeger: 0 or other positive पूर्णांकeger
 * If 0 then DSC is disabled.
 *
 * Access it with the following command:
 *
 *	cat /sys/kernel/debug/dri/0/DP-X/dsc_pic_width
 *
 * 0 - means that DSC is disabled
 */
अटल sमाप_प्रकार dp_dsc_pic_width_पढ़ो(काष्ठा file *f, अक्षर __user *buf,
				    माप_प्रकार size, loff_t *pos)
अणु
	अक्षर *rd_buf = शून्य;
	अक्षर *rd_buf_ptr = शून्य;
	काष्ठा amdgpu_dm_connector *aconnector = file_inode(f)->i_निजी;
	काष्ठा display_stream_compressor *dsc;
	काष्ठा dcn_dsc_state dsc_state = अणु0पूर्ण;
	स्थिर uपूर्णांक32_t rd_buf_size = 100;
	काष्ठा pipe_ctx *pipe_ctx;
	sमाप_प्रकार result = 0;
	पूर्णांक i, r, str_len = 30;

	rd_buf = kसुस्मृति(rd_buf_size, माप(अक्षर), GFP_KERNEL);

	अगर (!rd_buf)
		वापस -ENOMEM;

	rd_buf_ptr = rd_buf;

	क्रम (i = 0; i < MAX_PIPES; i++) अणु
		pipe_ctx = &aconnector->dc_link->dc->current_state->res_ctx.pipe_ctx[i];
			अगर (pipe_ctx && pipe_ctx->stream &&
			    pipe_ctx->stream->link == aconnector->dc_link)
				अवरोध;
	पूर्ण

	अगर (!pipe_ctx)
		वापस -ENXIO;

	dsc = pipe_ctx->stream_res.dsc;
	अगर (dsc)
		dsc->funcs->dsc_पढ़ो_state(dsc, &dsc_state);

	snम_लिखो(rd_buf_ptr, str_len,
		"%d\n",
		dsc_state.dsc_pic_width);
	rd_buf_ptr += str_len;

	जबतक (size) अणु
		अगर (*pos >= rd_buf_size)
			अवरोध;

		r = put_user(*(rd_buf + result), buf);
		अगर (r)
			वापस r; /* r = -EFAULT */

		buf += 1;
		size -= 1;
		*pos += 1;
		result += 1;
	पूर्ण

	kमुक्त(rd_buf);
	वापस result;
पूर्ण

अटल sमाप_प्रकार dp_dsc_pic_height_पढ़ो(काष्ठा file *f, अक्षर __user *buf,
				    माप_प्रकार size, loff_t *pos)
अणु
	अक्षर *rd_buf = शून्य;
	अक्षर *rd_buf_ptr = शून्य;
	काष्ठा amdgpu_dm_connector *aconnector = file_inode(f)->i_निजी;
	काष्ठा display_stream_compressor *dsc;
	काष्ठा dcn_dsc_state dsc_state = अणु0पूर्ण;
	स्थिर uपूर्णांक32_t rd_buf_size = 100;
	काष्ठा pipe_ctx *pipe_ctx;
	sमाप_प्रकार result = 0;
	पूर्णांक i, r, str_len = 30;

	rd_buf = kसुस्मृति(rd_buf_size, माप(अक्षर), GFP_KERNEL);

	अगर (!rd_buf)
		वापस -ENOMEM;

	rd_buf_ptr = rd_buf;

	क्रम (i = 0; i < MAX_PIPES; i++) अणु
		pipe_ctx = &aconnector->dc_link->dc->current_state->res_ctx.pipe_ctx[i];
			अगर (pipe_ctx && pipe_ctx->stream &&
			    pipe_ctx->stream->link == aconnector->dc_link)
				अवरोध;
	पूर्ण

	अगर (!pipe_ctx)
		वापस -ENXIO;

	dsc = pipe_ctx->stream_res.dsc;
	अगर (dsc)
		dsc->funcs->dsc_पढ़ो_state(dsc, &dsc_state);

	snम_लिखो(rd_buf_ptr, str_len,
		"%d\n",
		dsc_state.dsc_pic_height);
	rd_buf_ptr += str_len;

	जबतक (size) अणु
		अगर (*pos >= rd_buf_size)
			अवरोध;

		r = put_user(*(rd_buf + result), buf);
		अगर (r)
			वापस r; /* r = -EFAULT */

		buf += 1;
		size -= 1;
		*pos += 1;
		result += 1;
	पूर्ण

	kमुक्त(rd_buf);
	वापस result;
पूर्ण

/* function: पढ़ो DSC chunk size parameter on the connector
 *
 * The पढ़ो function: dp_dsc_chunk_size_पढ़ो
 * वापसs dsc chunk size set in the current configuration
 * The value is calculated स्वतःmatically by DSC code
 * and depends on slice parameters and bpp target rate
 * The वापस is an पूर्णांकeger: 0 or other positive पूर्णांकeger
 * If 0 then DSC is disabled.
 *
 * Access it with the following command:
 *
 *	cat /sys/kernel/debug/dri/0/DP-X/dsc_chunk_size
 *
 * 0 - means that DSC is disabled
 */
अटल sमाप_प्रकार dp_dsc_chunk_size_पढ़ो(काष्ठा file *f, अक्षर __user *buf,
				    माप_प्रकार size, loff_t *pos)
अणु
	अक्षर *rd_buf = शून्य;
	अक्षर *rd_buf_ptr = शून्य;
	काष्ठा amdgpu_dm_connector *aconnector = file_inode(f)->i_निजी;
	काष्ठा display_stream_compressor *dsc;
	काष्ठा dcn_dsc_state dsc_state = अणु0पूर्ण;
	स्थिर uपूर्णांक32_t rd_buf_size = 100;
	काष्ठा pipe_ctx *pipe_ctx;
	sमाप_प्रकार result = 0;
	पूर्णांक i, r, str_len = 30;

	rd_buf = kसुस्मृति(rd_buf_size, माप(अक्षर), GFP_KERNEL);

	अगर (!rd_buf)
		वापस -ENOMEM;

	rd_buf_ptr = rd_buf;

	क्रम (i = 0; i < MAX_PIPES; i++) अणु
		pipe_ctx = &aconnector->dc_link->dc->current_state->res_ctx.pipe_ctx[i];
			अगर (pipe_ctx && pipe_ctx->stream &&
			    pipe_ctx->stream->link == aconnector->dc_link)
				अवरोध;
	पूर्ण

	अगर (!pipe_ctx)
		वापस -ENXIO;

	dsc = pipe_ctx->stream_res.dsc;
	अगर (dsc)
		dsc->funcs->dsc_पढ़ो_state(dsc, &dsc_state);

	snम_लिखो(rd_buf_ptr, str_len,
		"%d\n",
		dsc_state.dsc_chunk_size);
	rd_buf_ptr += str_len;

	जबतक (size) अणु
		अगर (*pos >= rd_buf_size)
			अवरोध;

		r = put_user(*(rd_buf + result), buf);
		अगर (r)
			वापस r; /* r = -EFAULT */

		buf += 1;
		size -= 1;
		*pos += 1;
		result += 1;
	पूर्ण

	kमुक्त(rd_buf);
	वापस result;
पूर्ण

/* function: पढ़ो DSC slice bpg offset on the connector
 *
 * The पढ़ो function: dp_dsc_slice_bpg_offset_पढ़ो
 * वापसs dsc bpg slice offset set in the current configuration
 * The value is calculated स्वतःmatically by DSC code
 * and depends on slice parameters and bpp target rate
 * The वापस is an पूर्णांकeger: 0 or other positive पूर्णांकeger
 * If 0 then DSC is disabled.
 *
 * Access it with the following command:
 *
 *	cat /sys/kernel/debug/dri/0/DP-X/dsc_slice_bpg_offset
 *
 * 0 - means that DSC is disabled
 */
अटल sमाप_प्रकार dp_dsc_slice_bpg_offset_पढ़ो(काष्ठा file *f, अक्षर __user *buf,
				    माप_प्रकार size, loff_t *pos)
अणु
	अक्षर *rd_buf = शून्य;
	अक्षर *rd_buf_ptr = शून्य;
	काष्ठा amdgpu_dm_connector *aconnector = file_inode(f)->i_निजी;
	काष्ठा display_stream_compressor *dsc;
	काष्ठा dcn_dsc_state dsc_state = अणु0पूर्ण;
	स्थिर uपूर्णांक32_t rd_buf_size = 100;
	काष्ठा pipe_ctx *pipe_ctx;
	sमाप_प्रकार result = 0;
	पूर्णांक i, r, str_len = 30;

	rd_buf = kसुस्मृति(rd_buf_size, माप(अक्षर), GFP_KERNEL);

	अगर (!rd_buf)
		वापस -ENOMEM;

	rd_buf_ptr = rd_buf;

	क्रम (i = 0; i < MAX_PIPES; i++) अणु
		pipe_ctx = &aconnector->dc_link->dc->current_state->res_ctx.pipe_ctx[i];
			अगर (pipe_ctx && pipe_ctx->stream &&
			    pipe_ctx->stream->link == aconnector->dc_link)
				अवरोध;
	पूर्ण

	अगर (!pipe_ctx)
		वापस -ENXIO;

	dsc = pipe_ctx->stream_res.dsc;
	अगर (dsc)
		dsc->funcs->dsc_पढ़ो_state(dsc, &dsc_state);

	snम_लिखो(rd_buf_ptr, str_len,
		"%d\n",
		dsc_state.dsc_slice_bpg_offset);
	rd_buf_ptr += str_len;

	जबतक (size) अणु
		अगर (*pos >= rd_buf_size)
			अवरोध;

		r = put_user(*(rd_buf + result), buf);
		अगर (r)
			वापस r; /* r = -EFAULT */

		buf += 1;
		size -= 1;
		*pos += 1;
		result += 1;
	पूर्ण

	kमुक्त(rd_buf);
	वापस result;
पूर्ण


/*
 * function description: Read max_requested_bpc property from the connector
 *
 * Access it with the following command:
 *
 *	cat /sys/kernel/debug/dri/0/DP-X/max_bpc
 *
 */
अटल sमाप_प्रकार dp_max_bpc_पढ़ो(काष्ठा file *f, अक्षर __user *buf,
		माप_प्रकार size, loff_t *pos)
अणु
	काष्ठा amdgpu_dm_connector *aconnector = file_inode(f)->i_निजी;
	काष्ठा drm_connector *connector = &aconnector->base;
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा dm_connector_state *state;
	sमाप_प्रकार result = 0;
	अक्षर *rd_buf = शून्य;
	अक्षर *rd_buf_ptr = शून्य;
	स्थिर uपूर्णांक32_t rd_buf_size = 10;
	पूर्णांक r;

	rd_buf = kसुस्मृति(rd_buf_size, माप(अक्षर), GFP_KERNEL);

	अगर (!rd_buf)
		वापस -ENOMEM;

	mutex_lock(&dev->mode_config.mutex);
	drm_modeset_lock(&dev->mode_config.connection_mutex, शून्य);

	अगर (connector->state == शून्य)
		जाओ unlock;

	state = to_dm_connector_state(connector->state);

	rd_buf_ptr = rd_buf;
	snम_लिखो(rd_buf_ptr, rd_buf_size,
		"%u\n",
		state->base.max_requested_bpc);

	जबतक (size) अणु
		अगर (*pos >= rd_buf_size)
			अवरोध;

		r = put_user(*(rd_buf + result), buf);
		अगर (r) अणु
			result = r; /* r = -EFAULT */
			जाओ unlock;
		पूर्ण
		buf += 1;
		size -= 1;
		*pos += 1;
		result += 1;
	पूर्ण
unlock:
	drm_modeset_unlock(&dev->mode_config.connection_mutex);
	mutex_unlock(&dev->mode_config.mutex);
	kमुक्त(rd_buf);
	वापस result;
पूर्ण


/*
 * function description: Set max_requested_bpc property on the connector
 *
 * This function will not क्रमce the input BPC on connector, it will only
 * change the max value. This is equivalent to setting max_bpc through
 * xअक्रमr.
 *
 * The BPC value written must be >= 6 and <= 16. Values outside of this
 * range will result in errors.
 *
 * BPC values:
 *	0x6 - 6 BPC
 *	0x8 - 8 BPC
 *	0xa - 10 BPC
 *	0xc - 12 BPC
 *	0x10 - 16 BPC
 *
 * Write the max_bpc in the following way:
 *
 * echo 0x6 > /sys/kernel/debug/dri/0/DP-X/max_bpc
 *
 */
अटल sमाप_प्रकार dp_max_bpc_ग_लिखो(काष्ठा file *f, स्थिर अक्षर __user *buf,
				     माप_प्रकार size, loff_t *pos)
अणु
	काष्ठा amdgpu_dm_connector *aconnector = file_inode(f)->i_निजी;
	काष्ठा drm_connector *connector = &aconnector->base;
	काष्ठा dm_connector_state *state;
	काष्ठा drm_device *dev = connector->dev;
	अक्षर *wr_buf = शून्य;
	uपूर्णांक32_t wr_buf_size = 42;
	पूर्णांक max_param_num = 1;
	दीर्घ param[1] = अणु0पूर्ण;
	uपूर्णांक8_t param_nums = 0;

	अगर (size == 0)
		वापस -EINVAL;

	wr_buf = kसुस्मृति(wr_buf_size, माप(अक्षर), GFP_KERNEL);

	अगर (!wr_buf) अणु
		DRM_DEBUG_DRIVER("no memory to allocate write buffer\n");
		वापस -ENOSPC;
	पूर्ण

	अगर (parse_ग_लिखो_buffer_पूर्णांकo_params(wr_buf, size,
					   (दीर्घ *)param, buf,
					   max_param_num,
					   &param_nums)) अणु
		kमुक्त(wr_buf);
		वापस -EINVAL;
	पूर्ण

	अगर (param_nums <= 0) अणु
		DRM_DEBUG_DRIVER("user data not be read\n");
		kमुक्त(wr_buf);
		वापस -EINVAL;
	पूर्ण

	अगर (param[0] < 6 || param[0] > 16) अणु
		DRM_DEBUG_DRIVER("bad max_bpc value\n");
		kमुक्त(wr_buf);
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&dev->mode_config.mutex);
	drm_modeset_lock(&dev->mode_config.connection_mutex, शून्य);

	अगर (connector->state == शून्य)
		जाओ unlock;

	state = to_dm_connector_state(connector->state);
	state->base.max_requested_bpc = param[0];
unlock:
	drm_modeset_unlock(&dev->mode_config.connection_mutex);
	mutex_unlock(&dev->mode_config.mutex);

	kमुक्त(wr_buf);
	वापस size;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(dp_dsc_fec_support);
DEFINE_SHOW_ATTRIBUTE(dmub_fw_state);
DEFINE_SHOW_ATTRIBUTE(dmub_tracebuffer);
DEFINE_SHOW_ATTRIBUTE(output_bpc);
DEFINE_SHOW_ATTRIBUTE(dp_lttpr_status);
#अगर_घोषित CONFIG_DRM_AMD_DC_HDCP
DEFINE_SHOW_ATTRIBUTE(hdcp_sink_capability);
#पूर्ण_अगर

अटल स्थिर काष्ठा file_operations dp_dsc_घड़ी_en_debugfs_fops = अणु
	.owner = THIS_MODULE,
	.पढ़ो = dp_dsc_घड़ी_en_पढ़ो,
	.ग_लिखो = dp_dsc_घड़ी_en_ग_लिखो,
	.llseek = शेष_llseek
पूर्ण;

अटल स्थिर काष्ठा file_operations dp_dsc_slice_width_debugfs_fops = अणु
	.owner = THIS_MODULE,
	.पढ़ो = dp_dsc_slice_width_पढ़ो,
	.ग_लिखो = dp_dsc_slice_width_ग_लिखो,
	.llseek = शेष_llseek
पूर्ण;

अटल स्थिर काष्ठा file_operations dp_dsc_slice_height_debugfs_fops = अणु
	.owner = THIS_MODULE,
	.पढ़ो = dp_dsc_slice_height_पढ़ो,
	.ग_लिखो = dp_dsc_slice_height_ग_लिखो,
	.llseek = शेष_llseek
पूर्ण;

अटल स्थिर काष्ठा file_operations dp_dsc_bits_per_pixel_debugfs_fops = अणु
	.owner = THIS_MODULE,
	.पढ़ो = dp_dsc_bits_per_pixel_पढ़ो,
	.ग_लिखो = dp_dsc_bits_per_pixel_ग_लिखो,
	.llseek = शेष_llseek
पूर्ण;

अटल स्थिर काष्ठा file_operations dp_dsc_pic_width_debugfs_fops = अणु
	.owner = THIS_MODULE,
	.पढ़ो = dp_dsc_pic_width_पढ़ो,
	.llseek = शेष_llseek
पूर्ण;

अटल स्थिर काष्ठा file_operations dp_dsc_pic_height_debugfs_fops = अणु
	.owner = THIS_MODULE,
	.पढ़ो = dp_dsc_pic_height_पढ़ो,
	.llseek = शेष_llseek
पूर्ण;

अटल स्थिर काष्ठा file_operations dp_dsc_chunk_size_debugfs_fops = अणु
	.owner = THIS_MODULE,
	.पढ़ो = dp_dsc_chunk_size_पढ़ो,
	.llseek = शेष_llseek
पूर्ण;

अटल स्थिर काष्ठा file_operations dp_dsc_slice_bpg_offset_debugfs_fops = अणु
	.owner = THIS_MODULE,
	.पढ़ो = dp_dsc_slice_bpg_offset_पढ़ो,
	.llseek = शेष_llseek
पूर्ण;

अटल स्थिर काष्ठा file_operations trigger_hotplug_debugfs_fops = अणु
	.owner = THIS_MODULE,
	.ग_लिखो = trigger_hotplug,
	.llseek = शेष_llseek
पूर्ण;

अटल स्थिर काष्ठा file_operations dp_link_settings_debugfs_fops = अणु
	.owner = THIS_MODULE,
	.पढ़ो = dp_link_settings_पढ़ो,
	.ग_लिखो = dp_link_settings_ग_लिखो,
	.llseek = शेष_llseek
पूर्ण;

अटल स्थिर काष्ठा file_operations dp_phy_settings_debugfs_fop = अणु
	.owner = THIS_MODULE,
	.पढ़ो = dp_phy_settings_पढ़ो,
	.ग_लिखो = dp_phy_settings_ग_लिखो,
	.llseek = शेष_llseek
पूर्ण;

अटल स्थिर काष्ठा file_operations dp_phy_test_pattern_fops = अणु
	.owner = THIS_MODULE,
	.ग_लिखो = dp_phy_test_pattern_debugfs_ग_लिखो,
	.llseek = शेष_llseek
पूर्ण;

अटल स्थिर काष्ठा file_operations sdp_message_fops = अणु
	.owner = THIS_MODULE,
	.ग_लिखो = dp_sdp_message_debugfs_ग_लिखो,
	.llseek = शेष_llseek
पूर्ण;

अटल स्थिर काष्ठा file_operations dp_dpcd_address_debugfs_fops = अणु
	.owner = THIS_MODULE,
	.ग_लिखो = dp_dpcd_address_ग_लिखो,
	.llseek = शेष_llseek
पूर्ण;

अटल स्थिर काष्ठा file_operations dp_dpcd_size_debugfs_fops = अणु
	.owner = THIS_MODULE,
	.ग_लिखो = dp_dpcd_size_ग_लिखो,
	.llseek = शेष_llseek
पूर्ण;

अटल स्थिर काष्ठा file_operations dp_dpcd_data_debugfs_fops = अणु
	.owner = THIS_MODULE,
	.पढ़ो = dp_dpcd_data_पढ़ो,
	.ग_लिखो = dp_dpcd_data_ग_लिखो,
	.llseek = शेष_llseek
पूर्ण;

अटल स्थिर काष्ठा file_operations dp_max_bpc_debugfs_fops = अणु
	.owner = THIS_MODULE,
	.पढ़ो = dp_max_bpc_पढ़ो,
	.ग_लिखो = dp_max_bpc_ग_लिखो,
	.llseek = शेष_llseek
पूर्ण;

अटल स्थिर काष्ठा अणु
	अक्षर *name;
	स्थिर काष्ठा file_operations *fops;
पूर्ण dp_debugfs_entries[] = अणु
		अणु"link_settings", &dp_link_settings_debugfs_fopsपूर्ण,
		अणु"phy_settings", &dp_phy_settings_debugfs_fopपूर्ण,
		अणु"lttpr_status", &dp_lttpr_status_fopsपूर्ण,
		अणु"test_pattern", &dp_phy_test_pattern_fopsपूर्ण,
#अगर_घोषित CONFIG_DRM_AMD_DC_HDCP
		अणु"hdcp_sink_capability", &hdcp_sink_capability_fopsपूर्ण,
#पूर्ण_अगर
		अणु"sdp_message", &sdp_message_fopsपूर्ण,
		अणु"aux_dpcd_address", &dp_dpcd_address_debugfs_fopsपूर्ण,
		अणु"aux_dpcd_size", &dp_dpcd_size_debugfs_fopsपूर्ण,
		अणु"aux_dpcd_data", &dp_dpcd_data_debugfs_fopsपूर्ण,
		अणु"dsc_clock_en", &dp_dsc_घड़ी_en_debugfs_fopsपूर्ण,
		अणु"dsc_slice_width", &dp_dsc_slice_width_debugfs_fopsपूर्ण,
		अणु"dsc_slice_height", &dp_dsc_slice_height_debugfs_fopsपूर्ण,
		अणु"dsc_bits_per_pixel", &dp_dsc_bits_per_pixel_debugfs_fopsपूर्ण,
		अणु"dsc_pic_width", &dp_dsc_pic_width_debugfs_fopsपूर्ण,
		अणु"dsc_pic_height", &dp_dsc_pic_height_debugfs_fopsपूर्ण,
		अणु"dsc_chunk_size", &dp_dsc_chunk_size_debugfs_fopsपूर्ण,
		अणु"dsc_slice_bpg", &dp_dsc_slice_bpg_offset_debugfs_fopsपूर्ण,
		अणु"dp_dsc_fec_support", &dp_dsc_fec_support_fopsपूर्ण,
		अणु"max_bpc", &dp_max_bpc_debugfs_fopsपूर्ण
पूर्ण;

#अगर_घोषित CONFIG_DRM_AMD_DC_HDCP
अटल स्थिर काष्ठा अणु
	अक्षर *name;
	स्थिर काष्ठा file_operations *fops;
पूर्ण hdmi_debugfs_entries[] = अणु
		अणु"hdcp_sink_capability", &hdcp_sink_capability_fopsपूर्ण
पूर्ण;
#पूर्ण_अगर
/*
 * Force YUV420 output अगर available from the given mode
 */
अटल पूर्णांक क्रमce_yuv420_output_set(व्योम *data, u64 val)
अणु
	काष्ठा amdgpu_dm_connector *connector = data;

	connector->क्रमce_yuv420_output = (bool)val;

	वापस 0;
पूर्ण

/*
 * Check अगर YUV420 is क्रमced when available from the given mode
 */
अटल पूर्णांक क्रमce_yuv420_output_get(व्योम *data, u64 *val)
अणु
	काष्ठा amdgpu_dm_connector *connector = data;

	*val = connector->क्रमce_yuv420_output;

	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(क्रमce_yuv420_output_fops, क्रमce_yuv420_output_get,
			 क्रमce_yuv420_output_set, "%llu\n");

/*
 *  Read PSR state
 */
अटल पूर्णांक psr_get(व्योम *data, u64 *val)
अणु
	काष्ठा amdgpu_dm_connector *connector = data;
	काष्ठा dc_link *link = connector->dc_link;
	क्रमागत dc_psr_state state = PSR_STATE0;

	dc_link_get_psr_state(link, &state);

	*val = state;

	वापस 0;
पूर्ण

/*
 * Set dmcub trace event IRQ enable or disable.
 * Usage to enable dmcub trace event IRQ: echo 1 > /sys/kernel/debug/dri/0/amdgpu_dm_dmcub_trace_event_en
 * Usage to disable dmcub trace event IRQ: echo 0 > /sys/kernel/debug/dri/0/amdgpu_dm_dmcub_trace_event_en
 */
अटल पूर्णांक dmcub_trace_event_state_set(व्योम *data, u64 val)
अणु
	काष्ठा amdgpu_device *adev = data;

	अगर (val == 1 || val == 0) अणु
		dc_dmub_trace_event_control(adev->dm.dc, val);
		adev->dm.dmcub_trace_event_en = (bool)val;
	पूर्ण अन्यथा
		वापस 0;

	वापस 0;
पूर्ण

/*
 * The पूर्णांकerface करोesn't need get function, so it will वापस the
 * value of zero
 * Usage: cat /sys/kernel/debug/dri/0/amdgpu_dm_dmcub_trace_event_en
 */
अटल पूर्णांक dmcub_trace_event_state_get(व्योम *data, u64 *val)
अणु
	काष्ठा amdgpu_device *adev = data;

	*val = adev->dm.dmcub_trace_event_en;
	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(dmcub_trace_event_state_fops, dmcub_trace_event_state_get,
			 dmcub_trace_event_state_set, "%llu\n");

DEFINE_DEBUGFS_ATTRIBUTE(psr_fops, psr_get, शून्य, "%llu\n");

अटल स्थिर काष्ठा अणु
	अक्षर *name;
	स्थिर काष्ठा file_operations *fops;
पूर्ण connector_debugfs_entries[] = अणु
		अणु"force_yuv420_output", &क्रमce_yuv420_output_fopsपूर्ण,
		अणु"output_bpc", &output_bpc_fopsपूर्ण,
		अणु"trigger_hotplug", &trigger_hotplug_debugfs_fopsपूर्ण
पूर्ण;

व्योम connector_debugfs_init(काष्ठा amdgpu_dm_connector *connector)
अणु
	पूर्णांक i;
	काष्ठा dentry *dir = connector->base.debugfs_entry;

	अगर (connector->base.connector_type == DRM_MODE_CONNECTOR_DisplayPort ||
	    connector->base.connector_type == DRM_MODE_CONNECTOR_eDP) अणु
		क्रम (i = 0; i < ARRAY_SIZE(dp_debugfs_entries); i++) अणु
			debugfs_create_file(dp_debugfs_entries[i].name,
					    0644, dir, connector,
					    dp_debugfs_entries[i].fops);
		पूर्ण
	पूर्ण
	अगर (connector->base.connector_type == DRM_MODE_CONNECTOR_eDP)
		debugfs_create_file_unsafe("psr_state", 0444, dir, connector, &psr_fops);

	क्रम (i = 0; i < ARRAY_SIZE(connector_debugfs_entries); i++) अणु
		debugfs_create_file(connector_debugfs_entries[i].name,
				    0644, dir, connector,
				    connector_debugfs_entries[i].fops);
	पूर्ण

	connector->debugfs_dpcd_address = 0;
	connector->debugfs_dpcd_size = 0;

#अगर_घोषित CONFIG_DRM_AMD_DC_HDCP
	अगर (connector->base.connector_type == DRM_MODE_CONNECTOR_HDMIA) अणु
		क्रम (i = 0; i < ARRAY_SIZE(hdmi_debugfs_entries); i++) अणु
			debugfs_create_file(hdmi_debugfs_entries[i].name,
					    0644, dir, connector,
					    hdmi_debugfs_entries[i].fops);
		पूर्ण
	पूर्ण
#पूर्ण_अगर
पूर्ण

#अगर_घोषित CONFIG_DRM_AMD_SECURE_DISPLAY
/*
 * Set crc winकरोw coordinate x start
 */
अटल पूर्णांक crc_win_x_start_set(व्योम *data, u64 val)
अणु
	काष्ठा drm_crtc *crtc = data;
	काष्ठा drm_device *drm_dev = crtc->dev;
	काष्ठा amdgpu_crtc *acrtc = to_amdgpu_crtc(crtc);

	spin_lock_irq(&drm_dev->event_lock);
	acrtc->dm_irq_params.crc_winकरोw.x_start = (uपूर्णांक16_t) val;
	acrtc->dm_irq_params.crc_winकरोw.update_win = false;
	spin_unlock_irq(&drm_dev->event_lock);

	वापस 0;
पूर्ण

/*
 * Get crc winकरोw coordinate x start
 */
अटल पूर्णांक crc_win_x_start_get(व्योम *data, u64 *val)
अणु
	काष्ठा drm_crtc *crtc = data;
	काष्ठा drm_device *drm_dev = crtc->dev;
	काष्ठा amdgpu_crtc *acrtc = to_amdgpu_crtc(crtc);

	spin_lock_irq(&drm_dev->event_lock);
	*val = acrtc->dm_irq_params.crc_winकरोw.x_start;
	spin_unlock_irq(&drm_dev->event_lock);

	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(crc_win_x_start_fops, crc_win_x_start_get,
			 crc_win_x_start_set, "%llu\n");


/*
 * Set crc winकरोw coordinate y start
 */
अटल पूर्णांक crc_win_y_start_set(व्योम *data, u64 val)
अणु
	काष्ठा drm_crtc *crtc = data;
	काष्ठा drm_device *drm_dev = crtc->dev;
	काष्ठा amdgpu_crtc *acrtc = to_amdgpu_crtc(crtc);

	spin_lock_irq(&drm_dev->event_lock);
	acrtc->dm_irq_params.crc_winकरोw.y_start = (uपूर्णांक16_t) val;
	acrtc->dm_irq_params.crc_winकरोw.update_win = false;
	spin_unlock_irq(&drm_dev->event_lock);

	वापस 0;
पूर्ण

/*
 * Get crc winकरोw coordinate y start
 */
अटल पूर्णांक crc_win_y_start_get(व्योम *data, u64 *val)
अणु
	काष्ठा drm_crtc *crtc = data;
	काष्ठा drm_device *drm_dev = crtc->dev;
	काष्ठा amdgpu_crtc *acrtc = to_amdgpu_crtc(crtc);

	spin_lock_irq(&drm_dev->event_lock);
	*val = acrtc->dm_irq_params.crc_winकरोw.y_start;
	spin_unlock_irq(&drm_dev->event_lock);

	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(crc_win_y_start_fops, crc_win_y_start_get,
			 crc_win_y_start_set, "%llu\n");

/*
 * Set crc winकरोw coordinate x end
 */
अटल पूर्णांक crc_win_x_end_set(व्योम *data, u64 val)
अणु
	काष्ठा drm_crtc *crtc = data;
	काष्ठा drm_device *drm_dev = crtc->dev;
	काष्ठा amdgpu_crtc *acrtc = to_amdgpu_crtc(crtc);

	spin_lock_irq(&drm_dev->event_lock);
	acrtc->dm_irq_params.crc_winकरोw.x_end = (uपूर्णांक16_t) val;
	acrtc->dm_irq_params.crc_winकरोw.update_win = false;
	spin_unlock_irq(&drm_dev->event_lock);

	वापस 0;
पूर्ण

/*
 * Get crc winकरोw coordinate x end
 */
अटल पूर्णांक crc_win_x_end_get(व्योम *data, u64 *val)
अणु
	काष्ठा drm_crtc *crtc = data;
	काष्ठा drm_device *drm_dev = crtc->dev;
	काष्ठा amdgpu_crtc *acrtc = to_amdgpu_crtc(crtc);

	spin_lock_irq(&drm_dev->event_lock);
	*val = acrtc->dm_irq_params.crc_winकरोw.x_end;
	spin_unlock_irq(&drm_dev->event_lock);

	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(crc_win_x_end_fops, crc_win_x_end_get,
			 crc_win_x_end_set, "%llu\n");

/*
 * Set crc winकरोw coordinate y end
 */
अटल पूर्णांक crc_win_y_end_set(व्योम *data, u64 val)
अणु
	काष्ठा drm_crtc *crtc = data;
	काष्ठा drm_device *drm_dev = crtc->dev;
	काष्ठा amdgpu_crtc *acrtc = to_amdgpu_crtc(crtc);

	spin_lock_irq(&drm_dev->event_lock);
	acrtc->dm_irq_params.crc_winकरोw.y_end = (uपूर्णांक16_t) val;
	acrtc->dm_irq_params.crc_winकरोw.update_win = false;
	spin_unlock_irq(&drm_dev->event_lock);

	वापस 0;
पूर्ण

/*
 * Get crc winकरोw coordinate y end
 */
अटल पूर्णांक crc_win_y_end_get(व्योम *data, u64 *val)
अणु
	काष्ठा drm_crtc *crtc = data;
	काष्ठा drm_device *drm_dev = crtc->dev;
	काष्ठा amdgpu_crtc *acrtc = to_amdgpu_crtc(crtc);

	spin_lock_irq(&drm_dev->event_lock);
	*val = acrtc->dm_irq_params.crc_winकरोw.y_end;
	spin_unlock_irq(&drm_dev->event_lock);

	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(crc_win_y_end_fops, crc_win_y_end_get,
			 crc_win_y_end_set, "%llu\n");
/*
 * Trigger to commit crc winकरोw
 */
अटल पूर्णांक crc_win_update_set(व्योम *data, u64 val)
अणु
	काष्ठा drm_crtc *new_crtc = data;
	काष्ठा drm_crtc *old_crtc = शून्य;
	काष्ठा amdgpu_crtc *new_acrtc, *old_acrtc;
	काष्ठा amdgpu_device *adev = drm_to_adev(new_crtc->dev);
	काष्ठा crc_rd_work *crc_rd_wrk = adev->dm.crc_rd_wrk;

	अगर (val) अणु
		spin_lock_irq(&adev_to_drm(adev)->event_lock);
		spin_lock_irq(&crc_rd_wrk->crc_rd_work_lock);
		अगर (crc_rd_wrk && crc_rd_wrk->crtc) अणु
			old_crtc = crc_rd_wrk->crtc;
			old_acrtc = to_amdgpu_crtc(old_crtc);
		पूर्ण
		new_acrtc = to_amdgpu_crtc(new_crtc);

		अगर (old_crtc && old_crtc != new_crtc) अणु
			old_acrtc->dm_irq_params.crc_winकरोw.activated = false;
			old_acrtc->dm_irq_params.crc_winकरोw.update_win = false;
			old_acrtc->dm_irq_params.crc_winकरोw.skip_frame_cnt = 0;

			new_acrtc->dm_irq_params.crc_winकरोw.activated = true;
			new_acrtc->dm_irq_params.crc_winकरोw.update_win = true;
			new_acrtc->dm_irq_params.crc_winकरोw.skip_frame_cnt = 0;
			crc_rd_wrk->crtc = new_crtc;
		पूर्ण अन्यथा अणु
			new_acrtc->dm_irq_params.crc_winकरोw.activated = true;
			new_acrtc->dm_irq_params.crc_winकरोw.update_win = true;
			new_acrtc->dm_irq_params.crc_winकरोw.skip_frame_cnt = 0;
			crc_rd_wrk->crtc = new_crtc;
		पूर्ण
		spin_unlock_irq(&crc_rd_wrk->crc_rd_work_lock);
		spin_unlock_irq(&adev_to_drm(adev)->event_lock);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Get crc winकरोw update flag
 */
अटल पूर्णांक crc_win_update_get(व्योम *data, u64 *val)
अणु
	*val = 0;
	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(crc_win_update_fops, crc_win_update_get,
			 crc_win_update_set, "%llu\n");

व्योम crtc_debugfs_init(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा dentry *dir = debugfs_lookup("crc", crtc->debugfs_entry);

	अगर (!dir)
		वापस;

	debugfs_create_file_unsafe("crc_win_x_start", 0644, dir, crtc,
				   &crc_win_x_start_fops);
	debugfs_create_file_unsafe("crc_win_y_start", 0644, dir, crtc,
				   &crc_win_y_start_fops);
	debugfs_create_file_unsafe("crc_win_x_end", 0644, dir, crtc,
				   &crc_win_x_end_fops);
	debugfs_create_file_unsafe("crc_win_y_end", 0644, dir, crtc,
				   &crc_win_y_end_fops);
	debugfs_create_file_unsafe("crc_win_update", 0644, dir, crtc,
				   &crc_win_update_fops);

पूर्ण
#पूर्ण_अगर
/*
 * Writes DTN log state to the user supplied buffer.
 * Example usage: cat /sys/kernel/debug/dri/0/amdgpu_dm_dtn_log
 */
अटल sमाप_प्रकार dtn_log_पढ़ो(
	काष्ठा file *f,
	अक्षर __user *buf,
	माप_प्रकार size,
	loff_t *pos)
अणु
	काष्ठा amdgpu_device *adev = file_inode(f)->i_निजी;
	काष्ठा dc *dc = adev->dm.dc;
	काष्ठा dc_log_buffer_ctx log_ctx = अणु 0 पूर्ण;
	sमाप_प्रकार result = 0;

	अगर (!buf || !size)
		वापस -EINVAL;

	अगर (!dc->hwss.log_hw_state)
		वापस 0;

	dc->hwss.log_hw_state(dc, &log_ctx);

	अगर (*pos < log_ctx.pos) अणु
		माप_प्रकार to_copy = log_ctx.pos - *pos;

		to_copy = min(to_copy, size);

		अगर (!copy_to_user(buf, log_ctx.buf + *pos, to_copy)) अणु
			*pos += to_copy;
			result = to_copy;
		पूर्ण
	पूर्ण

	kमुक्त(log_ctx.buf);

	वापस result;
पूर्ण

/*
 * Writes DTN log state to dmesg when triggered via a ग_लिखो.
 * Example usage: echo 1 > /sys/kernel/debug/dri/0/amdgpu_dm_dtn_log
 */
अटल sमाप_प्रकार dtn_log_ग_लिखो(
	काष्ठा file *f,
	स्थिर अक्षर __user *buf,
	माप_प्रकार size,
	loff_t *pos)
अणु
	काष्ठा amdgpu_device *adev = file_inode(f)->i_निजी;
	काष्ठा dc *dc = adev->dm.dc;

	/* Write triggers log output via dmesg. */
	अगर (size == 0)
		वापस 0;

	अगर (dc->hwss.log_hw_state)
		dc->hwss.log_hw_state(dc, शून्य);

	वापस size;
पूर्ण

/*
 * Backlight at this moment.  Read only.
 * As written to display, taking ABM and backlight lut पूर्णांकo account.
 * Ranges from 0x0 to 0x10000 (= 100% PWM)
 */
अटल पूर्णांक current_backlight_show(काष्ठा seq_file *m, व्योम *unused)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)m->निजी;
	काष्ठा amdgpu_display_manager *dm = &adev->dm;

	अचिन्हित पूर्णांक backlight = dc_link_get_backlight_level(dm->backlight_link);

	seq_म_लिखो(m, "0x%x\n", backlight);
	वापस 0;
पूर्ण

/*
 * Backlight value that is being approached.  Read only.
 * As written to display, taking ABM and backlight lut पूर्णांकo account.
 * Ranges from 0x0 to 0x10000 (= 100% PWM)
 */
अटल पूर्णांक target_backlight_show(काष्ठा seq_file *m, व्योम *unused)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)m->निजी;
	काष्ठा amdgpu_display_manager *dm = &adev->dm;

	अचिन्हित पूर्णांक backlight = dc_link_get_target_backlight_pwm(dm->backlight_link);

	seq_म_लिखो(m, "0x%x\n", backlight);
	वापस 0;
पूर्ण

अटल पूर्णांक mst_topo_show(काष्ठा seq_file *m, व्योम *unused)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)m->निजी;
	काष्ठा drm_device *dev = adev_to_drm(adev);
	काष्ठा drm_connector *connector;
	काष्ठा drm_connector_list_iter conn_iter;
	काष्ठा amdgpu_dm_connector *aconnector;

	drm_connector_list_iter_begin(dev, &conn_iter);
	drm_क्रम_each_connector_iter(connector, &conn_iter) अणु
		अगर (connector->connector_type != DRM_MODE_CONNECTOR_DisplayPort)
			जारी;

		aconnector = to_amdgpu_dm_connector(connector);

		/* Ensure we're only dumping the topology of a root mst node */
		अगर (!aconnector->mst_mgr.mst_state)
			जारी;

		seq_म_लिखो(m, "\nMST topology for connector %d\n", aconnector->connector_id);
		drm_dp_mst_dump_topology(m, &aconnector->mst_mgr);
	पूर्ण
	drm_connector_list_iter_end(&conn_iter);

	वापस 0;
पूर्ण

/*
 * Sets trigger hpd क्रम MST topologies.
 * All connected connectors will be rediscovered and re started as needed अगर val of 1 is sent.
 * All topologies will be disconnected अगर val of 0 is set .
 * Usage to enable topologies: echo 1 > /sys/kernel/debug/dri/0/amdgpu_dm_trigger_hpd_mst
 * Usage to disable topologies: echo 0 > /sys/kernel/debug/dri/0/amdgpu_dm_trigger_hpd_mst
 */
अटल पूर्णांक trigger_hpd_mst_set(व्योम *data, u64 val)
अणु
	काष्ठा amdgpu_device *adev = data;
	काष्ठा drm_device *dev = adev_to_drm(adev);
	काष्ठा drm_connector_list_iter iter;
	काष्ठा amdgpu_dm_connector *aconnector;
	काष्ठा drm_connector *connector;
	काष्ठा dc_link *link = शून्य;

	अगर (val == 1) अणु
		drm_connector_list_iter_begin(dev, &iter);
		drm_क्रम_each_connector_iter(connector, &iter) अणु
			aconnector = to_amdgpu_dm_connector(connector);
			अगर (aconnector->dc_link->type == dc_connection_mst_branch &&
			    aconnector->mst_mgr.aux) अणु
				dc_link_detect(aconnector->dc_link, DETECT_REASON_HPD);
				drm_dp_mst_topology_mgr_set_mst(&aconnector->mst_mgr, true);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (val == 0) अणु
		drm_connector_list_iter_begin(dev, &iter);
		drm_क्रम_each_connector_iter(connector, &iter) अणु
			aconnector = to_amdgpu_dm_connector(connector);
			अगर (!aconnector->dc_link)
				जारी;

			अगर (!aconnector->mst_port)
				जारी;

			link = aconnector->dc_link;
			dp_receiver_घातer_ctrl(link, false);
			drm_dp_mst_topology_mgr_set_mst(&aconnector->mst_port->mst_mgr, false);
			link->mst_stream_alloc_table.stream_count = 0;
			स_रखो(link->mst_stream_alloc_table.stream_allocations, 0,
					माप(link->mst_stream_alloc_table.stream_allocations));
		पूर्ण
	पूर्ण अन्यथा अणु
		वापस 0;
	पूर्ण
	drm_kms_helper_hotplug_event(dev);

	वापस 0;
पूर्ण

/*
 * The पूर्णांकerface करोesn't need get function, so it will वापस the
 * value of zero
 * Usage: cat /sys/kernel/debug/dri/0/amdgpu_dm_trigger_hpd_mst
 */
अटल पूर्णांक trigger_hpd_mst_get(व्योम *data, u64 *val)
अणु
	*val = 0;
	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(trigger_hpd_mst_ops, trigger_hpd_mst_get,
			 trigger_hpd_mst_set, "%llu\n");


/*
 * Sets the क्रमce_timing_sync debug option from the given string.
 * All connected displays will be क्रमce synchronized immediately.
 * Usage: echo 1 > /sys/kernel/debug/dri/0/amdgpu_dm_क्रमce_timing_sync
 */
अटल पूर्णांक क्रमce_timing_sync_set(व्योम *data, u64 val)
अणु
	काष्ठा amdgpu_device *adev = data;

	adev->dm.क्रमce_timing_sync = (bool)val;

	amdgpu_dm_trigger_timing_sync(adev_to_drm(adev));

	वापस 0;
पूर्ण

/*
 * Gets the क्रमce_timing_sync debug option value पूर्णांकo the given buffer.
 * Usage: cat /sys/kernel/debug/dri/0/amdgpu_dm_क्रमce_timing_sync
 */
अटल पूर्णांक क्रमce_timing_sync_get(व्योम *data, u64 *val)
अणु
	काष्ठा amdgpu_device *adev = data;

	*val = adev->dm.क्रमce_timing_sync;

	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(क्रमce_timing_sync_ops, क्रमce_timing_sync_get,
			 क्रमce_timing_sync_set, "%llu\n");


/*
 * Disables all HPD and HPD RX पूर्णांकerrupt handling in the
 * driver when set to 1. Default is 0.
 */
अटल पूर्णांक disable_hpd_set(व्योम *data, u64 val)
अणु
	काष्ठा amdgpu_device *adev = data;

	adev->dm.disable_hpd_irq = (bool)val;

	वापस 0;
पूर्ण


/*
 * Returns 1 अगर HPD and HPRX पूर्णांकerrupt handling is disabled,
 * 0 otherwise.
 */
अटल पूर्णांक disable_hpd_get(व्योम *data, u64 *val)
अणु
	काष्ठा amdgpu_device *adev = data;

	*val = adev->dm.disable_hpd_irq;

	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(disable_hpd_ops, disable_hpd_get,
			 disable_hpd_set, "%llu\n");

/*
 * Sets the DC visual confirm debug option from the given string.
 * Example usage: echo 1 > /sys/kernel/debug/dri/0/amdgpu_visual_confirm
 */
अटल पूर्णांक visual_confirm_set(व्योम *data, u64 val)
अणु
	काष्ठा amdgpu_device *adev = data;

	adev->dm.dc->debug.visual_confirm = (क्रमागत visual_confirm)val;

	वापस 0;
पूर्ण

/*
 * Reads the DC visual confirm debug option value पूर्णांकo the given buffer.
 * Example usage: cat /sys/kernel/debug/dri/0/amdgpu_dm_visual_confirm
 */
अटल पूर्णांक visual_confirm_get(व्योम *data, u64 *val)
अणु
	काष्ठा amdgpu_device *adev = data;

	*val = adev->dm.dc->debug.visual_confirm;

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(current_backlight);
DEFINE_SHOW_ATTRIBUTE(target_backlight);
DEFINE_SHOW_ATTRIBUTE(mst_topo);
DEFINE_DEBUGFS_ATTRIBUTE(visual_confirm_fops, visual_confirm_get,
			 visual_confirm_set, "%llu\n");

/*
 * Dumps the DCC_EN bit क्रम each pipe.
 * Example usage: cat /sys/kernel/debug/dri/0/amdgpu_dm_dcc_en
 */
अटल sमाप_प्रकार dcc_en_bits_पढ़ो(
	काष्ठा file *f,
	अक्षर __user *buf,
	माप_प्रकार size,
	loff_t *pos)
अणु
	काष्ठा amdgpu_device *adev = file_inode(f)->i_निजी;
	काष्ठा dc *dc = adev->dm.dc;
	अक्षर *rd_buf = शून्य;
	स्थिर uपूर्णांक32_t rd_buf_size = 32;
	uपूर्णांक32_t result = 0;
	पूर्णांक offset = 0;
	पूर्णांक num_pipes = dc->res_pool->pipe_count;
	पूर्णांक *dcc_en_bits;
	पूर्णांक i, r;

	dcc_en_bits = kसुस्मृति(num_pipes, माप(पूर्णांक), GFP_KERNEL);
	अगर (!dcc_en_bits)
		वापस -ENOMEM;

	अगर (!dc->hwss.get_dcc_en_bits) अणु
		kमुक्त(dcc_en_bits);
		वापस 0;
	पूर्ण

	dc->hwss.get_dcc_en_bits(dc, dcc_en_bits);

	rd_buf = kसुस्मृति(rd_buf_size, माप(अक्षर), GFP_KERNEL);
	अगर (!rd_buf)
		वापस -ENOMEM;

	क्रम (i = 0; i < num_pipes; i++)
		offset += snम_लिखो(rd_buf + offset, rd_buf_size - offset,
				   "%d  ", dcc_en_bits[i]);
	rd_buf[म_माप(rd_buf)] = '\n';

	kमुक्त(dcc_en_bits);

	जबतक (size) अणु
		अगर (*pos >= rd_buf_size)
			अवरोध;
		r = put_user(*(rd_buf + result), buf);
		अगर (r)
			वापस r; /* r = -EFAULT */
		buf += 1;
		size -= 1;
		*pos += 1;
		result += 1;
	पूर्ण

	kमुक्त(rd_buf);
	वापस result;
पूर्ण

व्योम dtn_debugfs_init(काष्ठा amdgpu_device *adev)
अणु
	अटल स्थिर काष्ठा file_operations dtn_log_fops = अणु
		.owner = THIS_MODULE,
		.पढ़ो = dtn_log_पढ़ो,
		.ग_लिखो = dtn_log_ग_लिखो,
		.llseek = शेष_llseek
	पूर्ण;
	अटल स्थिर काष्ठा file_operations dcc_en_bits_fops = अणु
		.owner = THIS_MODULE,
		.पढ़ो = dcc_en_bits_पढ़ो,
		.llseek = शेष_llseek
	पूर्ण;

	काष्ठा drm_minor *minor = adev_to_drm(adev)->primary;
	काष्ठा dentry *root = minor->debugfs_root;

	debugfs_create_file("amdgpu_current_backlight_pwm", 0444,
			    root, adev, &current_backlight_fops);
	debugfs_create_file("amdgpu_target_backlight_pwm", 0444,
			    root, adev, &target_backlight_fops);
	debugfs_create_file("amdgpu_mst_topology", 0444, root,
			    adev, &mst_topo_fops);
	debugfs_create_file("amdgpu_dm_dtn_log", 0644, root, adev,
			    &dtn_log_fops);

	debugfs_create_file_unsafe("amdgpu_dm_visual_confirm", 0644, root, adev,
				   &visual_confirm_fops);

	debugfs_create_file_unsafe("amdgpu_dm_dmub_tracebuffer", 0644, root,
				   adev, &dmub_tracebuffer_fops);

	debugfs_create_file_unsafe("amdgpu_dm_dmub_fw_state", 0644, root,
				   adev, &dmub_fw_state_fops);

	debugfs_create_file_unsafe("amdgpu_dm_force_timing_sync", 0644, root,
				   adev, &क्रमce_timing_sync_ops);

	debugfs_create_file_unsafe("amdgpu_dm_dmcub_trace_event_en", 0644, root,
				   adev, &dmcub_trace_event_state_fops);

	debugfs_create_file_unsafe("amdgpu_dm_trigger_hpd_mst", 0644, root,
				   adev, &trigger_hpd_mst_ops);

	debugfs_create_file_unsafe("amdgpu_dm_dcc_en", 0644, root, adev,
				   &dcc_en_bits_fops);

	debugfs_create_file_unsafe("amdgpu_dm_disable_hpd", 0644, root, adev,
				   &disable_hpd_ops);

पूर्ण
