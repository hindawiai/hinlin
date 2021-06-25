<शैली गुरु>
/*
 * Copyright 2012-15 Advanced Micro Devices, Inc.
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

#समावेश <linux/slab.h>

#समावेश "dm_services.h"

/*
 * Pre-requisites: headers required by header of this unit
 */
#समावेश "include/gpio_types.h"

/*
 * Header of this unit
 */

#समावेश "hw_factory.h"

/*
 * Post-requisites: headers required by this unit
 */

#अगर defined(CONFIG_DRM_AMD_DC_SI)
#समावेश "dce60/hw_factory_dce60.h"
#पूर्ण_अगर
#समावेश "dce80/hw_factory_dce80.h"
#समावेश "dce110/hw_factory_dce110.h"
#समावेश "dce120/hw_factory_dce120.h"
#अगर defined(CONFIG_DRM_AMD_DC_DCN)
#समावेश "dcn10/hw_factory_dcn10.h"
#समावेश "dcn20/hw_factory_dcn20.h"
#समावेश "dcn21/hw_factory_dcn21.h"
#समावेश "dcn30/hw_factory_dcn30.h"
#पूर्ण_अगर

#समावेश "diagnostics/hw_factory_diag.h"

/*
 * This unit
 */

bool dal_hw_factory_init(
	काष्ठा hw_factory *factory,
	क्रमागत dce_version dce_version,
	क्रमागत dce_environment dce_environment)
अणु
	अगर (IS_FPGA_MAXIMUS_DC(dce_environment)) अणु
		dal_hw_factory_diag_fpga_init(factory);
		वापस true;
	पूर्ण

	चयन (dce_version) अणु
#अगर defined(CONFIG_DRM_AMD_DC_SI)
	हाल DCE_VERSION_6_0:
	हाल DCE_VERSION_6_1:
	हाल DCE_VERSION_6_4:
		dal_hw_factory_dce60_init(factory);
		वापस true;
#पूर्ण_अगर
	हाल DCE_VERSION_8_0:
	हाल DCE_VERSION_8_1:
	हाल DCE_VERSION_8_3:
		dal_hw_factory_dce80_init(factory);
		वापस true;

	हाल DCE_VERSION_10_0:
		dal_hw_factory_dce110_init(factory);
		वापस true;
	हाल DCE_VERSION_11_0:
	हाल DCE_VERSION_11_2:
	हाल DCE_VERSION_11_22:
		dal_hw_factory_dce110_init(factory);
		वापस true;
	हाल DCE_VERSION_12_0:
	हाल DCE_VERSION_12_1:
		dal_hw_factory_dce120_init(factory);
		वापस true;
#अगर defined(CONFIG_DRM_AMD_DC_DCN)
	हाल DCN_VERSION_1_0:
	हाल DCN_VERSION_1_01:
		dal_hw_factory_dcn10_init(factory);
		वापस true;
	हाल DCN_VERSION_2_0:
		dal_hw_factory_dcn20_init(factory);
		वापस true;
	हाल DCN_VERSION_2_1:
		dal_hw_factory_dcn21_init(factory);
		वापस true;
	हाल DCN_VERSION_3_0:
	हाल DCN_VERSION_3_01:
	हाल DCN_VERSION_3_02:
		dal_hw_factory_dcn30_init(factory);
		वापस true;
#पूर्ण_अगर
	शेष:
		ASSERT_CRITICAL(false);
		वापस false;
	पूर्ण
पूर्ण
