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
 */

#समावेश <linux/types.h>
#समावेश "atom-types.h"
#समावेश "atombios.h"
#समावेश "pppcielanes.h"

/** \पile
 * Functions related to PCIe lane changes.
 */

/* For converting from number of lanes to lane bits.  */
अटल स्थिर अचिन्हित अक्षर pp_r600_encode_lanes[] = अणु
	0,          /*  0 Not Supported  */
	1,          /*  1 Lane  */
	2,          /*  2 Lanes  */
	0,          /*  3 Not Supported  */
	3,          /*  4 Lanes  */
	0,          /*  5 Not Supported  */
	0,          /*  6 Not Supported  */
	0,          /*  7 Not Supported  */
	4,          /*  8 Lanes  */
	0,          /*  9 Not Supported  */
	0,          /* 10 Not Supported  */
	0,          /* 11 Not Supported  */
	5,          /* 12 Lanes (Not actually supported)  */
	0,          /* 13 Not Supported  */
	0,          /* 14 Not Supported  */
	0,          /* 15 Not Supported  */
	6           /* 16 Lanes  */
पूर्ण;

अटल स्थिर अचिन्हित अक्षर pp_r600_decoded_lanes[8] = अणु 16, 1, 2, 4, 8, 12, 16, पूर्ण;

uपूर्णांक8_t encode_pcie_lane_width(uपूर्णांक32_t num_lanes)
अणु
	वापस pp_r600_encode_lanes[num_lanes];
पूर्ण

uपूर्णांक8_t decode_pcie_lane_width(uपूर्णांक32_t num_lanes)
अणु
	वापस pp_r600_decoded_lanes[num_lanes];
पूर्ण
