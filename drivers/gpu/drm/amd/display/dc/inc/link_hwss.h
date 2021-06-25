<शैली गुरु>
/*
 * Copyright 2015 Advanced Micro Devices, Inc.
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

#अगर_अघोषित __DC_LINK_HWSS_H__
#घोषणा __DC_LINK_HWSS_H__

#समावेश "inc/core_status.h"

क्रमागत dc_status core_link_पढ़ो_dpcd(
	काष्ठा dc_link *link,
	uपूर्णांक32_t address,
	uपूर्णांक8_t *data,
	uपूर्णांक32_t size);

क्रमागत dc_status core_link_ग_लिखो_dpcd(
	काष्ठा dc_link *link,
	uपूर्णांक32_t address,
	स्थिर uपूर्णांक8_t *data,
	uपूर्णांक32_t size);

काष्ठा gpio *get_hpd_gpio(काष्ठा dc_bios *dcb,
		काष्ठा graphics_object_id link_id,
		काष्ठा gpio_service *gpio_service);

व्योम dp_enable_link_phy(
	काष्ठा dc_link *link,
	क्रमागत संकेत_type संकेत,
	क्रमागत घड़ी_source_id घड़ी_source,
	स्थिर काष्ठा dc_link_settings *link_settings);

व्योम dp_receiver_घातer_ctrl(काष्ठा dc_link *link, bool on);
व्योम edp_add_delay_क्रम_T9(काष्ठा dc_link *link);
bool edp_receiver_पढ़ोy_T9(काष्ठा dc_link *link);
bool edp_receiver_पढ़ोy_T7(काष्ठा dc_link *link);

व्योम dp_disable_link_phy(काष्ठा dc_link *link, क्रमागत संकेत_type संकेत);

व्योम dp_disable_link_phy_mst(काष्ठा dc_link *link, क्रमागत संकेत_type संकेत);

bool dp_set_hw_training_pattern(
	काष्ठा dc_link *link,
	क्रमागत dc_dp_training_pattern pattern,
	uपूर्णांक32_t offset);

व्योम dp_set_hw_lane_settings(
	काष्ठा dc_link *link,
	स्थिर काष्ठा link_training_settings *link_settings,
	uपूर्णांक32_t offset);

व्योम dp_set_hw_test_pattern(
	काष्ठा dc_link *link,
	क्रमागत dp_test_pattern test_pattern,
	uपूर्णांक8_t *custom_pattern,
	uपूर्णांक32_t custom_pattern_size);

व्योम dp_retrain_link_dp_test(काष्ठा dc_link *link,
		काष्ठा dc_link_settings *link_setting,
		bool skip_video_pattern);

#पूर्ण_अगर /* __DC_LINK_HWSS_H__ */
