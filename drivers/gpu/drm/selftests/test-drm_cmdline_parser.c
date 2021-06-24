<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2019 Bootlin
 */

#घोषणा pr_fmt(fmt) "drm_cmdline: " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>

#समावेश <drm/drm_connector.h>
#समावेश <drm/drm_modes.h>

#घोषणा TESTS "drm_cmdline_selftests.h"
#समावेश "drm_selftest.h"
#समावेश "test-drm_modeset_common.h"

अटल स्थिर काष्ठा drm_connector no_connector = अणुपूर्ण;

अटल पूर्णांक drm_cmdline_test_क्रमce_e_only(व्योम *ignored)
अणु
	काष्ठा drm_cmdline_mode mode = अणु पूर्ण;

	FAIL_ON(!drm_mode_parse_command_line_क्रम_connector("e",
							   &no_connector,
							   &mode));
	FAIL_ON(mode.specअगरied);
	FAIL_ON(mode.refresh_specअगरied);
	FAIL_ON(mode.bpp_specअगरied);

	FAIL_ON(mode.rb);
	FAIL_ON(mode.cvt);
	FAIL_ON(mode.पूर्णांकerlace);
	FAIL_ON(mode.margins);
	FAIL_ON(mode.क्रमce != DRM_FORCE_ON);

	वापस 0;
पूर्ण

अटल पूर्णांक drm_cmdline_test_क्रमce_D_only_not_digital(व्योम *ignored)
अणु
	काष्ठा drm_cmdline_mode mode = अणु पूर्ण;

	FAIL_ON(!drm_mode_parse_command_line_क्रम_connector("D",
							   &no_connector,
							   &mode));
	FAIL_ON(mode.specअगरied);
	FAIL_ON(mode.refresh_specअगरied);
	FAIL_ON(mode.bpp_specअगरied);

	FAIL_ON(mode.rb);
	FAIL_ON(mode.cvt);
	FAIL_ON(mode.पूर्णांकerlace);
	FAIL_ON(mode.margins);
	FAIL_ON(mode.क्रमce != DRM_FORCE_ON);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_connector connector_hdmi = अणु
	.connector_type	= DRM_MODE_CONNECTOR_HDMIB,
पूर्ण;

अटल पूर्णांक drm_cmdline_test_क्रमce_D_only_hdmi(व्योम *ignored)
अणु
	काष्ठा drm_cmdline_mode mode = अणु पूर्ण;

	FAIL_ON(!drm_mode_parse_command_line_क्रम_connector("D",
							   &connector_hdmi,
							   &mode));
	FAIL_ON(mode.specअगरied);
	FAIL_ON(mode.refresh_specअगरied);
	FAIL_ON(mode.bpp_specअगरied);

	FAIL_ON(mode.rb);
	FAIL_ON(mode.cvt);
	FAIL_ON(mode.पूर्णांकerlace);
	FAIL_ON(mode.margins);
	FAIL_ON(mode.क्रमce != DRM_FORCE_ON_DIGITAL);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_connector connector_dvi = अणु
	.connector_type	= DRM_MODE_CONNECTOR_DVII,
पूर्ण;

अटल पूर्णांक drm_cmdline_test_क्रमce_D_only_dvi(व्योम *ignored)
अणु
	काष्ठा drm_cmdline_mode mode = अणु पूर्ण;

	FAIL_ON(!drm_mode_parse_command_line_क्रम_connector("D",
							   &connector_dvi,
							   &mode));
	FAIL_ON(mode.specअगरied);
	FAIL_ON(mode.refresh_specअगरied);
	FAIL_ON(mode.bpp_specअगरied);

	FAIL_ON(mode.rb);
	FAIL_ON(mode.cvt);
	FAIL_ON(mode.पूर्णांकerlace);
	FAIL_ON(mode.margins);
	FAIL_ON(mode.क्रमce != DRM_FORCE_ON_DIGITAL);

	वापस 0;
पूर्ण

अटल पूर्णांक drm_cmdline_test_क्रमce_d_only(व्योम *ignored)
अणु
	काष्ठा drm_cmdline_mode mode = अणु पूर्ण;

	FAIL_ON(!drm_mode_parse_command_line_क्रम_connector("d",
							   &no_connector,
							   &mode));
	FAIL_ON(mode.specअगरied);
	FAIL_ON(mode.refresh_specअगरied);
	FAIL_ON(mode.bpp_specअगरied);

	FAIL_ON(mode.rb);
	FAIL_ON(mode.cvt);
	FAIL_ON(mode.पूर्णांकerlace);
	FAIL_ON(mode.margins);
	FAIL_ON(mode.क्रमce != DRM_FORCE_OFF);

	वापस 0;
पूर्ण

अटल पूर्णांक drm_cmdline_test_margin_only(व्योम *ignored)
अणु
	काष्ठा drm_cmdline_mode mode = अणु पूर्ण;

	FAIL_ON(drm_mode_parse_command_line_क्रम_connector("m",
							  &no_connector,
							  &mode));

	वापस 0;
पूर्ण

अटल पूर्णांक drm_cmdline_test_पूर्णांकerlace_only(व्योम *ignored)
अणु
	काष्ठा drm_cmdline_mode mode = अणु पूर्ण;

	FAIL_ON(drm_mode_parse_command_line_क्रम_connector("i",
							  &no_connector,
							  &mode));

	वापस 0;
पूर्ण

अटल पूर्णांक drm_cmdline_test_res(व्योम *ignored)
अणु
	काष्ठा drm_cmdline_mode mode = अणु पूर्ण;

	FAIL_ON(!drm_mode_parse_command_line_क्रम_connector("720x480",
							   &no_connector,
							   &mode));
	FAIL_ON(!mode.specअगरied);
	FAIL_ON(mode.xres != 720);
	FAIL_ON(mode.yres != 480);

	FAIL_ON(mode.refresh_specअगरied);

	FAIL_ON(mode.bpp_specअगरied);

	FAIL_ON(mode.rb);
	FAIL_ON(mode.cvt);
	FAIL_ON(mode.पूर्णांकerlace);
	FAIL_ON(mode.margins);
	FAIL_ON(mode.क्रमce != DRM_FORCE_UNSPECIFIED);

	वापस 0;
पूर्ण

अटल पूर्णांक drm_cmdline_test_res_missing_x(व्योम *ignored)
अणु
	काष्ठा drm_cmdline_mode mode = अणु पूर्ण;

	FAIL_ON(drm_mode_parse_command_line_क्रम_connector("x480",
							  &no_connector,
							  &mode));

	वापस 0;
पूर्ण

अटल पूर्णांक drm_cmdline_test_res_missing_y(व्योम *ignored)
अणु
	काष्ठा drm_cmdline_mode mode = अणु पूर्ण;

	FAIL_ON(drm_mode_parse_command_line_क्रम_connector("1024x",
							  &no_connector,
							  &mode));

	वापस 0;
पूर्ण

अटल पूर्णांक drm_cmdline_test_res_bad_y(व्योम *ignored)
अणु
	काष्ठा drm_cmdline_mode mode = अणु पूर्ण;

	FAIL_ON(drm_mode_parse_command_line_क्रम_connector("1024xtest",
							  &no_connector,
							  &mode));

	वापस 0;
पूर्ण

अटल पूर्णांक drm_cmdline_test_res_missing_y_bpp(व्योम *ignored)
अणु
	काष्ठा drm_cmdline_mode mode = अणु पूर्ण;

	FAIL_ON(drm_mode_parse_command_line_क्रम_connector("1024x-24",
							  &no_connector,
							  &mode));

	वापस 0;
पूर्ण

अटल पूर्णांक drm_cmdline_test_res_vesa(व्योम *ignored)
अणु
	काष्ठा drm_cmdline_mode mode = अणु पूर्ण;

	FAIL_ON(!drm_mode_parse_command_line_क्रम_connector("720x480M",
							   &no_connector,
							   &mode));
	FAIL_ON(!mode.specअगरied);
	FAIL_ON(mode.xres != 720);
	FAIL_ON(mode.yres != 480);

	FAIL_ON(mode.refresh_specअगरied);

	FAIL_ON(mode.bpp_specअगरied);

	FAIL_ON(mode.rb);
	FAIL_ON(!mode.cvt);
	FAIL_ON(mode.पूर्णांकerlace);
	FAIL_ON(mode.margins);
	FAIL_ON(mode.क्रमce != DRM_FORCE_UNSPECIFIED);

	वापस 0;
पूर्ण

अटल पूर्णांक drm_cmdline_test_res_vesa_rblank(व्योम *ignored)
अणु
	काष्ठा drm_cmdline_mode mode = अणु पूर्ण;

	FAIL_ON(!drm_mode_parse_command_line_क्रम_connector("720x480MR",
							   &no_connector,
							   &mode));
	FAIL_ON(!mode.specअगरied);
	FAIL_ON(mode.xres != 720);
	FAIL_ON(mode.yres != 480);

	FAIL_ON(mode.refresh_specअगरied);

	FAIL_ON(mode.bpp_specअगरied);

	FAIL_ON(!mode.rb);
	FAIL_ON(!mode.cvt);
	FAIL_ON(mode.पूर्णांकerlace);
	FAIL_ON(mode.margins);
	FAIL_ON(mode.क्रमce != DRM_FORCE_UNSPECIFIED);

	वापस 0;
पूर्ण

अटल पूर्णांक drm_cmdline_test_res_rblank(व्योम *ignored)
अणु
	काष्ठा drm_cmdline_mode mode = अणु पूर्ण;

	FAIL_ON(!drm_mode_parse_command_line_क्रम_connector("720x480R",
							   &no_connector,
							   &mode));
	FAIL_ON(!mode.specअगरied);
	FAIL_ON(mode.xres != 720);
	FAIL_ON(mode.yres != 480);

	FAIL_ON(mode.refresh_specअगरied);

	FAIL_ON(mode.bpp_specअगरied);

	FAIL_ON(!mode.rb);
	FAIL_ON(mode.cvt);
	FAIL_ON(mode.पूर्णांकerlace);
	FAIL_ON(mode.margins);
	FAIL_ON(mode.क्रमce != DRM_FORCE_UNSPECIFIED);

	वापस 0;
पूर्ण

अटल पूर्णांक drm_cmdline_test_res_bpp(व्योम *ignored)
अणु
	काष्ठा drm_cmdline_mode mode = अणु पूर्ण;

	FAIL_ON(!drm_mode_parse_command_line_क्रम_connector("720x480-24",
							   &no_connector,
							   &mode));
	FAIL_ON(!mode.specअगरied);
	FAIL_ON(mode.xres != 720);
	FAIL_ON(mode.yres != 480);

	FAIL_ON(mode.refresh_specअगरied);

	FAIL_ON(!mode.bpp_specअगरied);
	FAIL_ON(mode.bpp != 24);

	FAIL_ON(mode.rb);
	FAIL_ON(mode.cvt);
	FAIL_ON(mode.पूर्णांकerlace);
	FAIL_ON(mode.margins);
	FAIL_ON(mode.क्रमce != DRM_FORCE_UNSPECIFIED);

	वापस 0;
पूर्ण

अटल पूर्णांक drm_cmdline_test_res_bad_bpp(व्योम *ignored)
अणु
	काष्ठा drm_cmdline_mode mode = अणु पूर्ण;

	FAIL_ON(drm_mode_parse_command_line_क्रम_connector("720x480-test",
							  &no_connector,
							  &mode));

	वापस 0;
पूर्ण

अटल पूर्णांक drm_cmdline_test_res_refresh(व्योम *ignored)
अणु
	काष्ठा drm_cmdline_mode mode = अणु पूर्ण;

	FAIL_ON(!drm_mode_parse_command_line_क्रम_connector("720x480@60",
							   &no_connector,
							   &mode));
	FAIL_ON(!mode.specअगरied);
	FAIL_ON(mode.xres != 720);
	FAIL_ON(mode.yres != 480);

	FAIL_ON(!mode.refresh_specअगरied);
	FAIL_ON(mode.refresh != 60);

	FAIL_ON(mode.bpp_specअगरied);

	FAIL_ON(mode.rb);
	FAIL_ON(mode.cvt);
	FAIL_ON(mode.पूर्णांकerlace);
	FAIL_ON(mode.margins);
	FAIL_ON(mode.क्रमce != DRM_FORCE_UNSPECIFIED);

	वापस 0;
पूर्ण

अटल पूर्णांक drm_cmdline_test_res_bad_refresh(व्योम *ignored)
अणु
	काष्ठा drm_cmdline_mode mode = अणु पूर्ण;

	FAIL_ON(drm_mode_parse_command_line_क्रम_connector("720x480@refresh",
							  &no_connector,
							  &mode));

	वापस 0;
पूर्ण

अटल पूर्णांक drm_cmdline_test_res_bpp_refresh(व्योम *ignored)
अणु
	काष्ठा drm_cmdline_mode mode = अणु पूर्ण;

	FAIL_ON(!drm_mode_parse_command_line_क्रम_connector("720x480-24@60",
							   &no_connector,
							   &mode));
	FAIL_ON(!mode.specअगरied);
	FAIL_ON(mode.xres != 720);
	FAIL_ON(mode.yres != 480);

	FAIL_ON(!mode.refresh_specअगरied);
	FAIL_ON(mode.refresh != 60);

	FAIL_ON(!mode.bpp_specअगरied);
	FAIL_ON(mode.bpp != 24);

	FAIL_ON(mode.rb);
	FAIL_ON(mode.cvt);
	FAIL_ON(mode.पूर्णांकerlace);
	FAIL_ON(mode.margins);
	FAIL_ON(mode.क्रमce != DRM_FORCE_UNSPECIFIED);

	वापस 0;
पूर्ण

अटल पूर्णांक drm_cmdline_test_res_bpp_refresh_पूर्णांकerlaced(व्योम *ignored)
अणु
	काष्ठा drm_cmdline_mode mode = अणु पूर्ण;

	FAIL_ON(!drm_mode_parse_command_line_क्रम_connector("720x480-24@60i",
							   &no_connector,
							   &mode));
	FAIL_ON(!mode.specअगरied);
	FAIL_ON(mode.xres != 720);
	FAIL_ON(mode.yres != 480);

	FAIL_ON(!mode.refresh_specअगरied);
	FAIL_ON(mode.refresh != 60);

	FAIL_ON(!mode.bpp_specअगरied);
	FAIL_ON(mode.bpp != 24);

	FAIL_ON(mode.rb);
	FAIL_ON(mode.cvt);
	FAIL_ON(!mode.पूर्णांकerlace);
	FAIL_ON(mode.margins);
	FAIL_ON(mode.क्रमce != DRM_FORCE_UNSPECIFIED);

	वापस 0;
पूर्ण

अटल पूर्णांक drm_cmdline_test_res_bpp_refresh_margins(व्योम *ignored)
अणु
	काष्ठा drm_cmdline_mode mode = अणु पूर्ण;

	FAIL_ON(!drm_mode_parse_command_line_क्रम_connector("720x480-24@60m",
							   &no_connector,
							   &mode));
	FAIL_ON(!mode.specअगरied);
	FAIL_ON(mode.xres != 720);
	FAIL_ON(mode.yres != 480);

	FAIL_ON(!mode.refresh_specअगरied);
	FAIL_ON(mode.refresh != 60);

	FAIL_ON(!mode.bpp_specअगरied);
	FAIL_ON(mode.bpp != 24);

	FAIL_ON(mode.rb);
	FAIL_ON(mode.cvt);
	FAIL_ON(mode.पूर्णांकerlace);
	FAIL_ON(!mode.margins);
	FAIL_ON(mode.क्रमce != DRM_FORCE_UNSPECIFIED);

	वापस 0;
पूर्ण

अटल पूर्णांक drm_cmdline_test_res_bpp_refresh_क्रमce_off(व्योम *ignored)
अणु
	काष्ठा drm_cmdline_mode mode = अणु पूर्ण;

	FAIL_ON(!drm_mode_parse_command_line_क्रम_connector("720x480-24@60d",
							   &no_connector,
							   &mode));
	FAIL_ON(!mode.specअगरied);
	FAIL_ON(mode.xres != 720);
	FAIL_ON(mode.yres != 480);

	FAIL_ON(!mode.refresh_specअगरied);
	FAIL_ON(mode.refresh != 60);

	FAIL_ON(!mode.bpp_specअगरied);
	FAIL_ON(mode.bpp != 24);

	FAIL_ON(mode.rb);
	FAIL_ON(mode.cvt);
	FAIL_ON(mode.पूर्णांकerlace);
	FAIL_ON(mode.margins);
	FAIL_ON(mode.क्रमce != DRM_FORCE_OFF);

	वापस 0;
पूर्ण

अटल पूर्णांक drm_cmdline_test_res_bpp_refresh_क्रमce_on_off(व्योम *ignored)
अणु
	काष्ठा drm_cmdline_mode mode = अणु पूर्ण;

	FAIL_ON(drm_mode_parse_command_line_क्रम_connector("720x480-24@60de",
							  &no_connector,
							  &mode));

	वापस 0;
पूर्ण

अटल पूर्णांक drm_cmdline_test_res_bpp_refresh_क्रमce_on(व्योम *ignored)
अणु
	काष्ठा drm_cmdline_mode mode = अणु पूर्ण;

	FAIL_ON(!drm_mode_parse_command_line_क्रम_connector("720x480-24@60e",
							   &no_connector,
							   &mode));
	FAIL_ON(!mode.specअगरied);
	FAIL_ON(mode.xres != 720);
	FAIL_ON(mode.yres != 480);

	FAIL_ON(!mode.refresh_specअगरied);
	FAIL_ON(mode.refresh != 60);

	FAIL_ON(!mode.bpp_specअगरied);
	FAIL_ON(mode.bpp != 24);

	FAIL_ON(mode.rb);
	FAIL_ON(mode.cvt);
	FAIL_ON(mode.पूर्णांकerlace);
	FAIL_ON(mode.margins);
	FAIL_ON(mode.क्रमce != DRM_FORCE_ON);

	वापस 0;
पूर्ण

अटल पूर्णांक drm_cmdline_test_res_bpp_refresh_क्रमce_on_analog(व्योम *ignored)
अणु
	काष्ठा drm_cmdline_mode mode = अणु पूर्ण;

	FAIL_ON(!drm_mode_parse_command_line_क्रम_connector("720x480-24@60D",
							   &no_connector,
							   &mode));
	FAIL_ON(!mode.specअगरied);
	FAIL_ON(mode.xres != 720);
	FAIL_ON(mode.yres != 480);

	FAIL_ON(!mode.refresh_specअगरied);
	FAIL_ON(mode.refresh != 60);

	FAIL_ON(!mode.bpp_specअगरied);
	FAIL_ON(mode.bpp != 24);

	FAIL_ON(mode.rb);
	FAIL_ON(mode.cvt);
	FAIL_ON(mode.पूर्णांकerlace);
	FAIL_ON(mode.margins);
	FAIL_ON(mode.क्रमce != DRM_FORCE_ON);

	वापस 0;
पूर्ण

अटल पूर्णांक drm_cmdline_test_res_bpp_refresh_क्रमce_on_digital(व्योम *ignored)
अणु
	काष्ठा drm_cmdline_mode mode = अणु पूर्ण;
	अटल स्थिर काष्ठा drm_connector connector = अणु
		.connector_type = DRM_MODE_CONNECTOR_DVII,
	पूर्ण;

	FAIL_ON(!drm_mode_parse_command_line_क्रम_connector("720x480-24@60D",
							   &connector,
							   &mode));
	FAIL_ON(!mode.specअगरied);
	FAIL_ON(mode.xres != 720);
	FAIL_ON(mode.yres != 480);

	FAIL_ON(!mode.refresh_specअगरied);
	FAIL_ON(mode.refresh != 60);

	FAIL_ON(!mode.bpp_specअगरied);
	FAIL_ON(mode.bpp != 24);

	FAIL_ON(mode.rb);
	FAIL_ON(mode.cvt);
	FAIL_ON(mode.पूर्णांकerlace);
	FAIL_ON(mode.margins);
	FAIL_ON(mode.क्रमce != DRM_FORCE_ON_DIGITAL);

	वापस 0;
पूर्ण

अटल पूर्णांक drm_cmdline_test_res_bpp_refresh_पूर्णांकerlaced_margins_क्रमce_on(व्योम *ignored)
अणु
	काष्ठा drm_cmdline_mode mode = अणु पूर्ण;

	FAIL_ON(!drm_mode_parse_command_line_क्रम_connector("720x480-24@60ime",
							   &no_connector,
							   &mode));
	FAIL_ON(!mode.specअगरied);
	FAIL_ON(mode.xres != 720);
	FAIL_ON(mode.yres != 480);

	FAIL_ON(!mode.refresh_specअगरied);
	FAIL_ON(mode.refresh != 60);

	FAIL_ON(!mode.bpp_specअगरied);
	FAIL_ON(mode.bpp != 24);

	FAIL_ON(mode.rb);
	FAIL_ON(mode.cvt);
	FAIL_ON(!mode.पूर्णांकerlace);
	FAIL_ON(!mode.margins);
	FAIL_ON(mode.क्रमce != DRM_FORCE_ON);

	वापस 0;
पूर्ण

अटल पूर्णांक drm_cmdline_test_res_margins_क्रमce_on(व्योम *ignored)
अणु
	काष्ठा drm_cmdline_mode mode = अणु पूर्ण;

	FAIL_ON(!drm_mode_parse_command_line_क्रम_connector("720x480me",
							   &no_connector,
							   &mode));
	FAIL_ON(!mode.specअगरied);
	FAIL_ON(mode.xres != 720);
	FAIL_ON(mode.yres != 480);

	FAIL_ON(mode.refresh_specअगरied);

	FAIL_ON(mode.bpp_specअगरied);

	FAIL_ON(mode.rb);
	FAIL_ON(mode.cvt);
	FAIL_ON(mode.पूर्णांकerlace);
	FAIL_ON(!mode.margins);
	FAIL_ON(mode.क्रमce != DRM_FORCE_ON);

	वापस 0;
पूर्ण

अटल पूर्णांक drm_cmdline_test_res_vesa_margins(व्योम *ignored)
अणु
	काष्ठा drm_cmdline_mode mode = अणु पूर्ण;

	FAIL_ON(!drm_mode_parse_command_line_क्रम_connector("720x480Mm",
							   &no_connector,
							   &mode));
	FAIL_ON(!mode.specअगरied);
	FAIL_ON(mode.xres != 720);
	FAIL_ON(mode.yres != 480);

	FAIL_ON(mode.refresh_specअगरied);

	FAIL_ON(mode.bpp_specअगरied);

	FAIL_ON(mode.rb);
	FAIL_ON(!mode.cvt);
	FAIL_ON(mode.पूर्णांकerlace);
	FAIL_ON(!mode.margins);
	FAIL_ON(mode.क्रमce != DRM_FORCE_UNSPECIFIED);

	वापस 0;
पूर्ण

अटल पूर्णांक drm_cmdline_test_res_invalid_mode(व्योम *ignored)
अणु
	काष्ठा drm_cmdline_mode mode = अणु पूर्ण;

	FAIL_ON(drm_mode_parse_command_line_क्रम_connector("720x480f",
							  &no_connector,
							  &mode));

	वापस 0;
पूर्ण

अटल पूर्णांक drm_cmdline_test_res_bpp_wrong_place_mode(व्योम *ignored)
अणु
	काष्ठा drm_cmdline_mode mode = अणु पूर्ण;

	FAIL_ON(drm_mode_parse_command_line_क्रम_connector("720x480e-24",
							  &no_connector,
							  &mode));

	वापस 0;
पूर्ण

अटल पूर्णांक drm_cmdline_test_name(व्योम *ignored)
अणु
	काष्ठा drm_cmdline_mode mode = अणु पूर्ण;

	FAIL_ON(!drm_mode_parse_command_line_क्रम_connector("NTSC",
							   &no_connector,
							   &mode));
	FAIL_ON(म_भेद(mode.name, "NTSC"));
	FAIL_ON(mode.refresh_specअगरied);
	FAIL_ON(mode.bpp_specअगरied);

	वापस 0;
पूर्ण

अटल पूर्णांक drm_cmdline_test_name_bpp(व्योम *ignored)
अणु
	काष्ठा drm_cmdline_mode mode = अणु पूर्ण;

	FAIL_ON(!drm_mode_parse_command_line_क्रम_connector("NTSC-24",
							   &no_connector,
							   &mode));
	FAIL_ON(म_भेद(mode.name, "NTSC"));

	FAIL_ON(mode.refresh_specअगरied);

	FAIL_ON(!mode.bpp_specअगरied);
	FAIL_ON(mode.bpp != 24);

	वापस 0;
पूर्ण

अटल पूर्णांक drm_cmdline_test_name_bpp_refresh(व्योम *ignored)
अणु
	काष्ठा drm_cmdline_mode mode = अणु पूर्ण;

	FAIL_ON(drm_mode_parse_command_line_क्रम_connector("NTSC-24@60",
							  &no_connector,
							  &mode));

	वापस 0;
पूर्ण

अटल पूर्णांक drm_cmdline_test_name_refresh(व्योम *ignored)
अणु
	काष्ठा drm_cmdline_mode mode = अणु पूर्ण;

	FAIL_ON(drm_mode_parse_command_line_क्रम_connector("NTSC@60",
							  &no_connector,
							  &mode));

	वापस 0;
पूर्ण

अटल पूर्णांक drm_cmdline_test_name_refresh_wrong_mode(व्योम *ignored)
अणु
	काष्ठा drm_cmdline_mode mode = अणु पूर्ण;

	FAIL_ON(drm_mode_parse_command_line_क्रम_connector("NTSC@60m",
							  &no_connector,
							  &mode));

	वापस 0;
पूर्ण

अटल पूर्णांक drm_cmdline_test_name_refresh_invalid_mode(व्योम *ignored)
अणु
	काष्ठा drm_cmdline_mode mode = अणु पूर्ण;

	FAIL_ON(drm_mode_parse_command_line_क्रम_connector("NTSC@60f",
							  &no_connector,
							  &mode));

	वापस 0;
पूर्ण

अटल पूर्णांक drm_cmdline_test_name_option(व्योम *ignored)
अणु
	काष्ठा drm_cmdline_mode mode = अणु पूर्ण;

	FAIL_ON(!drm_mode_parse_command_line_क्रम_connector("NTSC,rotate=180",
							   &no_connector,
							   &mode));
	FAIL_ON(!mode.specअगरied);
	FAIL_ON(म_भेद(mode.name, "NTSC"));
	FAIL_ON(mode.rotation_reflection != DRM_MODE_ROTATE_180);

	वापस 0;
पूर्ण

अटल पूर्णांक drm_cmdline_test_name_bpp_option(व्योम *ignored)
अणु
	काष्ठा drm_cmdline_mode mode = अणु पूर्ण;

	FAIL_ON(!drm_mode_parse_command_line_क्रम_connector("NTSC-24,rotate=180",
							   &no_connector,
							   &mode));
	FAIL_ON(!mode.specअगरied);
	FAIL_ON(म_भेद(mode.name, "NTSC"));
	FAIL_ON(mode.rotation_reflection != DRM_MODE_ROTATE_180);
	FAIL_ON(!mode.bpp_specअगरied);
	FAIL_ON(mode.bpp != 24);

	वापस 0;
पूर्ण

अटल पूर्णांक drm_cmdline_test_rotate_0(व्योम *ignored)
अणु
	काष्ठा drm_cmdline_mode mode = अणु पूर्ण;

	FAIL_ON(!drm_mode_parse_command_line_क्रम_connector("720x480,rotate=0",
							   &no_connector,
							   &mode));
	FAIL_ON(!mode.specअगरied);
	FAIL_ON(mode.xres != 720);
	FAIL_ON(mode.yres != 480);
	FAIL_ON(mode.rotation_reflection != DRM_MODE_ROTATE_0);

	FAIL_ON(mode.refresh_specअगरied);

	FAIL_ON(mode.bpp_specअगरied);

	FAIL_ON(mode.rb);
	FAIL_ON(mode.cvt);
	FAIL_ON(mode.पूर्णांकerlace);
	FAIL_ON(mode.margins);
	FAIL_ON(mode.क्रमce != DRM_FORCE_UNSPECIFIED);

	वापस 0;
पूर्ण

अटल पूर्णांक drm_cmdline_test_rotate_90(व्योम *ignored)
अणु
	काष्ठा drm_cmdline_mode mode = अणु पूर्ण;

	FAIL_ON(!drm_mode_parse_command_line_क्रम_connector("720x480,rotate=90",
							   &no_connector,
							   &mode));
	FAIL_ON(!mode.specअगरied);
	FAIL_ON(mode.xres != 720);
	FAIL_ON(mode.yres != 480);
	FAIL_ON(mode.rotation_reflection != DRM_MODE_ROTATE_90);

	FAIL_ON(mode.refresh_specअगरied);

	FAIL_ON(mode.bpp_specअगरied);

	FAIL_ON(mode.rb);
	FAIL_ON(mode.cvt);
	FAIL_ON(mode.पूर्णांकerlace);
	FAIL_ON(mode.margins);
	FAIL_ON(mode.क्रमce != DRM_FORCE_UNSPECIFIED);

	वापस 0;
पूर्ण

अटल पूर्णांक drm_cmdline_test_rotate_180(व्योम *ignored)
अणु
	काष्ठा drm_cmdline_mode mode = अणु पूर्ण;

	FAIL_ON(!drm_mode_parse_command_line_क्रम_connector("720x480,rotate=180",
							   &no_connector,
							   &mode));
	FAIL_ON(!mode.specअगरied);
	FAIL_ON(mode.xres != 720);
	FAIL_ON(mode.yres != 480);
	FAIL_ON(mode.rotation_reflection != DRM_MODE_ROTATE_180);

	FAIL_ON(mode.refresh_specअगरied);

	FAIL_ON(mode.bpp_specअगरied);

	FAIL_ON(mode.rb);
	FAIL_ON(mode.cvt);
	FAIL_ON(mode.पूर्णांकerlace);
	FAIL_ON(mode.margins);
	FAIL_ON(mode.क्रमce != DRM_FORCE_UNSPECIFIED);

	वापस 0;
पूर्ण

अटल पूर्णांक drm_cmdline_test_rotate_270(व्योम *ignored)
अणु
	काष्ठा drm_cmdline_mode mode = अणु पूर्ण;

	FAIL_ON(!drm_mode_parse_command_line_क्रम_connector("720x480,rotate=270",
							   &no_connector,
							   &mode));
	FAIL_ON(!mode.specअगरied);
	FAIL_ON(mode.xres != 720);
	FAIL_ON(mode.yres != 480);
	FAIL_ON(mode.rotation_reflection != DRM_MODE_ROTATE_270);

	FAIL_ON(mode.refresh_specअगरied);

	FAIL_ON(mode.bpp_specअगरied);

	FAIL_ON(mode.rb);
	FAIL_ON(mode.cvt);
	FAIL_ON(mode.पूर्णांकerlace);
	FAIL_ON(mode.margins);
	FAIL_ON(mode.क्रमce != DRM_FORCE_UNSPECIFIED);

	वापस 0;
पूर्ण

अटल पूर्णांक drm_cmdline_test_rotate_multiple(व्योम *ignored)
अणु
	काष्ठा drm_cmdline_mode mode = अणु पूर्ण;

	FAIL_ON(drm_mode_parse_command_line_क्रम_connector("720x480,rotate=0,rotate=90",
							  &no_connector,
							  &mode));

	वापस 0;
पूर्ण

अटल पूर्णांक drm_cmdline_test_rotate_invalid_val(व्योम *ignored)
अणु
	काष्ठा drm_cmdline_mode mode = अणु पूर्ण;

	FAIL_ON(drm_mode_parse_command_line_क्रम_connector("720x480,rotate=42",
							  &no_connector,
							  &mode));

	वापस 0;
पूर्ण

अटल पूर्णांक drm_cmdline_test_rotate_truncated(व्योम *ignored)
अणु
	काष्ठा drm_cmdline_mode mode = अणु पूर्ण;

	FAIL_ON(drm_mode_parse_command_line_क्रम_connector("720x480,rotate=",
							  &no_connector,
							  &mode));

	वापस 0;
पूर्ण

अटल पूर्णांक drm_cmdline_test_hmirror(व्योम *ignored)
अणु
	काष्ठा drm_cmdline_mode mode = अणु पूर्ण;

	FAIL_ON(!drm_mode_parse_command_line_क्रम_connector("720x480,reflect_x",
							   &no_connector,
							   &mode));
	FAIL_ON(!mode.specअगरied);
	FAIL_ON(mode.xres != 720);
	FAIL_ON(mode.yres != 480);
	FAIL_ON(mode.rotation_reflection != (DRM_MODE_ROTATE_0 | DRM_MODE_REFLECT_X));

	FAIL_ON(mode.refresh_specअगरied);

	FAIL_ON(mode.bpp_specअगरied);

	FAIL_ON(mode.rb);
	FAIL_ON(mode.cvt);
	FAIL_ON(mode.पूर्णांकerlace);
	FAIL_ON(mode.margins);
	FAIL_ON(mode.क्रमce != DRM_FORCE_UNSPECIFIED);

	वापस 0;
पूर्ण

अटल पूर्णांक drm_cmdline_test_vmirror(व्योम *ignored)
अणु
	काष्ठा drm_cmdline_mode mode = अणु पूर्ण;

	FAIL_ON(!drm_mode_parse_command_line_क्रम_connector("720x480,reflect_y",
							   &no_connector,
							   &mode));
	FAIL_ON(!mode.specअगरied);
	FAIL_ON(mode.xres != 720);
	FAIL_ON(mode.yres != 480);
	FAIL_ON(mode.rotation_reflection != (DRM_MODE_ROTATE_0 | DRM_MODE_REFLECT_Y));

	FAIL_ON(mode.refresh_specअगरied);

	FAIL_ON(mode.bpp_specअगरied);

	FAIL_ON(mode.rb);
	FAIL_ON(mode.cvt);
	FAIL_ON(mode.पूर्णांकerlace);
	FAIL_ON(mode.margins);
	FAIL_ON(mode.क्रमce != DRM_FORCE_UNSPECIFIED);

	वापस 0;
पूर्ण

अटल पूर्णांक drm_cmdline_test_margin_options(व्योम *ignored)
अणु
	काष्ठा drm_cmdline_mode mode = अणु पूर्ण;

	FAIL_ON(!drm_mode_parse_command_line_क्रम_connector("720x480,margin_right=14,margin_left=24,margin_bottom=36,margin_top=42",
							   &no_connector,
							   &mode));
	FAIL_ON(!mode.specअगरied);
	FAIL_ON(mode.xres != 720);
	FAIL_ON(mode.yres != 480);
	FAIL_ON(mode.tv_margins.right != 14);
	FAIL_ON(mode.tv_margins.left != 24);
	FAIL_ON(mode.tv_margins.bottom != 36);
	FAIL_ON(mode.tv_margins.top != 42);

	FAIL_ON(mode.refresh_specअगरied);

	FAIL_ON(mode.bpp_specअगरied);

	FAIL_ON(mode.rb);
	FAIL_ON(mode.cvt);
	FAIL_ON(mode.पूर्णांकerlace);
	FAIL_ON(mode.margins);
	FAIL_ON(mode.क्रमce != DRM_FORCE_UNSPECIFIED);

	वापस 0;
पूर्ण

अटल पूर्णांक drm_cmdline_test_multiple_options(व्योम *ignored)
अणु
	काष्ठा drm_cmdline_mode mode = अणु पूर्ण;

	FAIL_ON(!drm_mode_parse_command_line_क्रम_connector("720x480,rotate=270,reflect_x",
							   &no_connector,
							   &mode));
	FAIL_ON(!mode.specअगरied);
	FAIL_ON(mode.xres != 720);
	FAIL_ON(mode.yres != 480);
	FAIL_ON(mode.rotation_reflection != (DRM_MODE_ROTATE_270 | DRM_MODE_REFLECT_X));

	FAIL_ON(mode.refresh_specअगरied);

	FAIL_ON(mode.bpp_specअगरied);

	FAIL_ON(mode.rb);
	FAIL_ON(mode.cvt);
	FAIL_ON(mode.पूर्णांकerlace);
	FAIL_ON(mode.margins);
	FAIL_ON(mode.क्रमce != DRM_FORCE_UNSPECIFIED);

	वापस 0;
पूर्ण

अटल पूर्णांक drm_cmdline_test_invalid_option(व्योम *ignored)
अणु
	काष्ठा drm_cmdline_mode mode = अणु पूर्ण;

	FAIL_ON(drm_mode_parse_command_line_क्रम_connector("720x480,test=42",
							  &no_connector,
							  &mode));

	वापस 0;
पूर्ण

अटल पूर्णांक drm_cmdline_test_bpp_extra_and_option(व्योम *ignored)
अणु
	काष्ठा drm_cmdline_mode mode = अणु पूर्ण;

	FAIL_ON(!drm_mode_parse_command_line_क्रम_connector("720x480-24e,rotate=180",
							   &no_connector,
							   &mode));
	FAIL_ON(!mode.specअगरied);
	FAIL_ON(mode.xres != 720);
	FAIL_ON(mode.yres != 480);
	FAIL_ON(mode.rotation_reflection != DRM_MODE_ROTATE_180);

	FAIL_ON(mode.refresh_specअगरied);

	FAIL_ON(!mode.bpp_specअगरied);
	FAIL_ON(mode.bpp != 24);

	FAIL_ON(mode.rb);
	FAIL_ON(mode.cvt);
	FAIL_ON(mode.पूर्णांकerlace);
	FAIL_ON(mode.margins);
	FAIL_ON(mode.क्रमce != DRM_FORCE_ON);

	वापस 0;
पूर्ण

अटल पूर्णांक drm_cmdline_test_extra_and_option(व्योम *ignored)
अणु
	काष्ठा drm_cmdline_mode mode = अणु पूर्ण;

	FAIL_ON(!drm_mode_parse_command_line_क्रम_connector("720x480e,rotate=180",
							   &no_connector,
							   &mode));
	FAIL_ON(!mode.specअगरied);
	FAIL_ON(mode.xres != 720);
	FAIL_ON(mode.yres != 480);
	FAIL_ON(mode.rotation_reflection != DRM_MODE_ROTATE_180);

	FAIL_ON(mode.refresh_specअगरied);
	FAIL_ON(mode.bpp_specअगरied);

	FAIL_ON(mode.rb);
	FAIL_ON(mode.cvt);
	FAIL_ON(mode.पूर्णांकerlace);
	FAIL_ON(mode.margins);
	FAIL_ON(mode.क्रमce != DRM_FORCE_ON);

	वापस 0;
पूर्ण

अटल पूर्णांक drm_cmdline_test_मुक्तstanding_options(व्योम *ignored)
अणु
	काष्ठा drm_cmdline_mode mode = अणु पूर्ण;

	FAIL_ON(!drm_mode_parse_command_line_क्रम_connector("margin_right=14,margin_left=24,margin_bottom=36,margin_top=42",
							   &no_connector,
							   &mode));
	FAIL_ON(mode.specअगरied);
	FAIL_ON(mode.refresh_specअगरied);
	FAIL_ON(mode.bpp_specअगरied);

	FAIL_ON(mode.tv_margins.right != 14);
	FAIL_ON(mode.tv_margins.left != 24);
	FAIL_ON(mode.tv_margins.bottom != 36);
	FAIL_ON(mode.tv_margins.top != 42);

	FAIL_ON(mode.rb);
	FAIL_ON(mode.cvt);
	FAIL_ON(mode.पूर्णांकerlace);
	FAIL_ON(mode.margins);
	FAIL_ON(mode.क्रमce != DRM_FORCE_UNSPECIFIED);

	वापस 0;
पूर्ण

अटल पूर्णांक drm_cmdline_test_मुक्तstanding_क्रमce_e_and_options(व्योम *ignored)
अणु
	काष्ठा drm_cmdline_mode mode = अणु पूर्ण;

	FAIL_ON(!drm_mode_parse_command_line_क्रम_connector("e,margin_right=14,margin_left=24,margin_bottom=36,margin_top=42",
							   &no_connector,
							   &mode));
	FAIL_ON(mode.specअगरied);
	FAIL_ON(mode.refresh_specअगरied);
	FAIL_ON(mode.bpp_specअगरied);

	FAIL_ON(mode.tv_margins.right != 14);
	FAIL_ON(mode.tv_margins.left != 24);
	FAIL_ON(mode.tv_margins.bottom != 36);
	FAIL_ON(mode.tv_margins.top != 42);

	FAIL_ON(mode.rb);
	FAIL_ON(mode.cvt);
	FAIL_ON(mode.पूर्णांकerlace);
	FAIL_ON(mode.margins);
	FAIL_ON(mode.क्रमce != DRM_FORCE_ON);

	वापस 0;
पूर्ण

अटल पूर्णांक drm_cmdline_test_panel_orientation(व्योम *ignored)
अणु
	काष्ठा drm_cmdline_mode mode = अणु पूर्ण;

	FAIL_ON(!drm_mode_parse_command_line_क्रम_connector("panel_orientation=upside_down",
							   &no_connector,
							   &mode));
	FAIL_ON(mode.specअगरied);
	FAIL_ON(mode.refresh_specअगरied);
	FAIL_ON(mode.bpp_specअगरied);

	FAIL_ON(mode.panel_orientation != DRM_MODE_PANEL_ORIENTATION_BOTTOM_UP);

	FAIL_ON(mode.rb);
	FAIL_ON(mode.cvt);
	FAIL_ON(mode.पूर्णांकerlace);
	FAIL_ON(mode.margins);
	FAIL_ON(mode.क्रमce != DRM_FORCE_UNSPECIFIED);

	वापस 0;
पूर्ण

#समावेश "drm_selftest.c"

अटल पूर्णांक __init test_drm_cmdline_init(व्योम)
अणु
	पूर्णांक err;

	err = run_selftests(selftests, ARRAY_SIZE(selftests), शून्य);

	वापस err > 0 ? 0 : err;
पूर्ण
module_init(test_drm_cmdline_init);

MODULE_AUTHOR("Maxime Ripard <maxime.ripard@bootlin.com>");
MODULE_LICENSE("GPL");
