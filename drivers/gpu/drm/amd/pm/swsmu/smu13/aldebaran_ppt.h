<शैली गुरु>
/*
 * Copyright 2019 Advanced Micro Devices, Inc.
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
#अगर_अघोषित __ALDEBARAN_PPT_H__
#घोषणा __ALDEBARAN_PPT_H__

#घोषणा ALDEBARAN_UMD_PSTATE_GFXCLK_LEVEL         0x3
#घोषणा ALDEBARAN_UMD_PSTATE_SOCCLK_LEVEL         0x3
#घोषणा ALDEBARAN_UMD_PSTATE_MCLK_LEVEL           0x2

#घोषणा MAX_DPM_NUMBER 16
#घोषणा MAX_PCIE_CONF 2

काष्ठा aldebaran_dpm_level अणु
	bool            enabled;
	uपूर्णांक32_t        value;
	uपूर्णांक32_t        param1;
पूर्ण;

काष्ठा aldebaran_dpm_state अणु
	uपूर्णांक32_t  soft_min_level;
	uपूर्णांक32_t  soft_max_level;
	uपूर्णांक32_t  hard_min_level;
	uपूर्णांक32_t  hard_max_level;
पूर्ण;

काष्ठा aldebaran_single_dpm_table अणु
	uपूर्णांक32_t                count;
	काष्ठा aldebaran_dpm_state dpm_state;
	काष्ठा aldebaran_dpm_level dpm_levels[MAX_DPM_NUMBER];
पूर्ण;

काष्ठा aldebaran_pcie_table अणु
	uपूर्णांक16_t count;
	uपूर्णांक8_t  pcie_gen[MAX_PCIE_CONF];
	uपूर्णांक8_t  pcie_lane[MAX_PCIE_CONF];
	uपूर्णांक32_t lclk[MAX_PCIE_CONF];
पूर्ण;

काष्ठा aldebaran_dpm_table अणु
	काष्ठा aldebaran_single_dpm_table  soc_table;
	काष्ठा aldebaran_single_dpm_table  gfx_table;
	काष्ठा aldebaran_single_dpm_table  mem_table;
	काष्ठा aldebaran_single_dpm_table  eclk_table;
	काष्ठा aldebaran_single_dpm_table  vclk_table;
	काष्ठा aldebaran_single_dpm_table  dclk_table;
	काष्ठा aldebaran_single_dpm_table  fclk_table;
	काष्ठा aldebaran_pcie_table        pcie_table;
पूर्ण;

बाह्य व्योम aldebaran_set_ppt_funcs(काष्ठा smu_context *smu);

#पूर्ण_अगर
