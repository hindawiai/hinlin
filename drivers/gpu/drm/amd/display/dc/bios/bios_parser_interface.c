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

#समावेश "dm_services.h"
#समावेश "include/logger_interface.h"

#समावेश "bios_parser_interface.h"
#समावेश "bios_parser.h"

#समावेश "bios_parser2.h"


काष्ठा dc_bios *dal_bios_parser_create(
	काष्ठा bp_init_data *init,
	क्रमागत dce_version dce_version)
अणु
	काष्ठा dc_bios *bios = शून्य;

	bios = firmware_parser_create(init, dce_version);

	/* Fall back to old bios parser क्रम older asics */
	अगर (bios == शून्य)
		bios = bios_parser_create(init, dce_version);

	वापस bios;
पूर्ण

व्योम dal_bios_parser_destroy(काष्ठा dc_bios **dcb)
अणु
	काष्ठा dc_bios *bios = *dcb;

	bios->funcs->bios_parser_destroy(dcb);
पूर्ण

