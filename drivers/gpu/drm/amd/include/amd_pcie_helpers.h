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
 */

#अगर_अघोषित __AMD_PCIE_HELPERS_H__
#घोषणा __AMD_PCIE_HELPERS_H__

#समावेश "amd_pcie.h"

अटल अंतरभूत bool is_pcie_gen3_supported(uपूर्णांक32_t pcie_link_speed_cap)
अणु
	अगर (pcie_link_speed_cap & CAIL_PCIE_LINK_SPEED_SUPPORT_GEN3)
		वापस true;

	वापस false;
पूर्ण

अटल अंतरभूत bool is_pcie_gen2_supported(uपूर्णांक32_t pcie_link_speed_cap)
अणु
	अगर (pcie_link_speed_cap & CAIL_PCIE_LINK_SPEED_SUPPORT_GEN2)
		वापस true;

	वापस false;
पूर्ण

/* Get the new PCIE speed given the ASIC PCIE Cap and the NewState's requested PCIE speed*/
अटल अंतरभूत uपूर्णांक16_t get_pcie_gen_support(uपूर्णांक32_t pcie_link_speed_cap,
					    uपूर्णांक16_t ns_pcie_gen)
अणु
	uपूर्णांक32_t asic_pcie_link_speed_cap = (pcie_link_speed_cap &
		CAIL_ASIC_PCIE_LINK_SPEED_SUPPORT_MASK);
	uपूर्णांक32_t sys_pcie_link_speed_cap  = (pcie_link_speed_cap &
		CAIL_PCIE_LINK_SPEED_SUPPORT_MASK);

	चयन (asic_pcie_link_speed_cap) अणु
	हाल CAIL_ASIC_PCIE_LINK_SPEED_SUPPORT_GEN1:
		वापस PP_PCIEGen1;

	हाल CAIL_ASIC_PCIE_LINK_SPEED_SUPPORT_GEN2:
		वापस PP_PCIEGen2;

	हाल CAIL_ASIC_PCIE_LINK_SPEED_SUPPORT_GEN3:
		वापस PP_PCIEGen3;

	शेष:
		अगर (is_pcie_gen3_supported(sys_pcie_link_speed_cap) &&
			(ns_pcie_gen == PP_PCIEGen3)) अणु
			वापस PP_PCIEGen3;
		पूर्ण अन्यथा अगर (is_pcie_gen2_supported(sys_pcie_link_speed_cap) &&
			((ns_pcie_gen == PP_PCIEGen3) || (ns_pcie_gen == PP_PCIEGen2))) अणु
			वापस PP_PCIEGen2;
		पूर्ण
	पूर्ण

	वापस PP_PCIEGen1;
पूर्ण

अटल अंतरभूत uपूर्णांक16_t get_pcie_lane_support(uपूर्णांक32_t pcie_lane_width_cap,
					     uपूर्णांक16_t ns_pcie_lanes)
अणु
	पूर्णांक i, j;
	uपूर्णांक16_t new_pcie_lanes = ns_pcie_lanes;
	uपूर्णांक16_t pcie_lanes[7] = अणु1, 2, 4, 8, 12, 16, 32पूर्ण;

	चयन (pcie_lane_width_cap) अणु
	हाल 0:
		pr_err("No valid PCIE lane width reported\n");
		अवरोध;
	हाल CAIL_PCIE_LINK_WIDTH_SUPPORT_X1:
		new_pcie_lanes = 1;
		अवरोध;
	हाल CAIL_PCIE_LINK_WIDTH_SUPPORT_X2:
		new_pcie_lanes = 2;
		अवरोध;
	हाल CAIL_PCIE_LINK_WIDTH_SUPPORT_X4:
		new_pcie_lanes = 4;
		अवरोध;
	हाल CAIL_PCIE_LINK_WIDTH_SUPPORT_X8:
		new_pcie_lanes = 8;
		अवरोध;
	हाल CAIL_PCIE_LINK_WIDTH_SUPPORT_X12:
		new_pcie_lanes = 12;
		अवरोध;
	हाल CAIL_PCIE_LINK_WIDTH_SUPPORT_X16:
		new_pcie_lanes = 16;
		अवरोध;
	हाल CAIL_PCIE_LINK_WIDTH_SUPPORT_X32:
		new_pcie_lanes = 32;
		अवरोध;
	शेष:
		क्रम (i = 0; i < 7; i++) अणु
			अगर (ns_pcie_lanes == pcie_lanes[i]) अणु
				अगर (pcie_lane_width_cap & (0x10000 << i)) अणु
					अवरोध;
				पूर्ण अन्यथा अणु
					क्रम (j = i - 1; j >= 0; j--) अणु
						अगर (pcie_lane_width_cap & (0x10000 << j)) अणु
							new_pcie_lanes = pcie_lanes[j];
							अवरोध;
						पूर्ण
					पूर्ण

					अगर (j < 0) अणु
						क्रम (j = i + 1; j < 7; j++) अणु
							अगर (pcie_lane_width_cap & (0x10000 << j)) अणु
								new_pcie_lanes = pcie_lanes[j];
								अवरोध;
							पूर्ण
						पूर्ण
						अगर (j > 7)
							pr_err("Cannot find a valid PCIE lane width!\n");
					पूर्ण
				पूर्ण
				अवरोध;
			पूर्ण
		पूर्ण
		अवरोध;
	पूर्ण

	वापस new_pcie_lanes;
पूर्ण

#पूर्ण_अगर
