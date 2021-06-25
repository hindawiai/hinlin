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
#अगर_अघोषित _SMU7_POWERTUNE_H
#घोषणा _SMU7_POWERTUNE_H

#घोषणा DIDT_SQ_CTRL0__UNUSED_0_MASK    0xfffc0000
#घोषणा DIDT_SQ_CTRL0__UNUSED_0__SHIFT  0x12
#घोषणा DIDT_TD_CTRL0__UNUSED_0_MASK    0xfffc0000
#घोषणा DIDT_TD_CTRL0__UNUSED_0__SHIFT  0x12
#घोषणा DIDT_TCP_CTRL0__UNUSED_0_MASK   0xfffc0000
#घोषणा DIDT_TCP_CTRL0__UNUSED_0__SHIFT 0x12
#घोषणा DIDT_SQ_TUNING_CTRL__UNUSED_0_MASK                 0xc0000000
#घोषणा DIDT_SQ_TUNING_CTRL__UNUSED_0__SHIFT               0x0000001e
#घोषणा DIDT_TD_TUNING_CTRL__UNUSED_0_MASK                 0xc0000000
#घोषणा DIDT_TD_TUNING_CTRL__UNUSED_0__SHIFT               0x0000001e
#घोषणा DIDT_TCP_TUNING_CTRL__UNUSED_0_MASK                0xc0000000
#घोषणा DIDT_TCP_TUNING_CTRL__UNUSED_0__SHIFT              0x0000001e

/* PowerContainment Features */
#घोषणा POWERCONTAINMENT_FEATURE_DTE             0x00000001
#घोषणा POWERCONTAINMENT_FEATURE_TDCLimit        0x00000002
#घोषणा POWERCONTAINMENT_FEATURE_PkgPwrLimit     0x00000004

#घोषणा ixGC_CAC_CNTL 0x0000
#घोषणा ixDIDT_SQ_STALL_CTRL 0x0004
#घोषणा ixDIDT_SQ_TUNING_CTRL 0x0005
#घोषणा ixDIDT_TD_STALL_CTRL 0x0044
#घोषणा ixDIDT_TD_TUNING_CTRL 0x0045
#घोषणा ixDIDT_TCP_STALL_CTRL 0x0064
#घोषणा ixDIDT_TCP_TUNING_CTRL 0x0065


पूर्णांक smu7_enable_smc_cac(काष्ठा pp_hwmgr *hwmgr);
पूर्णांक smu7_disable_smc_cac(काष्ठा pp_hwmgr *hwmgr);
पूर्णांक smu7_enable_घातer_containment(काष्ठा pp_hwmgr *hwmgr);
पूर्णांक smu7_disable_घातer_containment(काष्ठा pp_hwmgr *hwmgr);
पूर्णांक smu7_set_घातer_limit(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t n);
पूर्णांक smu7_घातer_control_set_level(काष्ठा pp_hwmgr *hwmgr);
पूर्णांक smu7_enable_didt_config(काष्ठा pp_hwmgr *hwmgr);
पूर्णांक smu7_disable_didt_config(काष्ठा pp_hwmgr *hwmgr);
#पूर्ण_अगर  /* DGPU_POWERTUNE_H */

