<शैली गुरु>
/*
 * Copyright 2016 Advanced Micro Devices, Inc.
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

#अगर_अघोषित _SMU7_CLOCK_POWER_GATING_H_
#घोषणा _SMU7_CLOCK_POWER_GATING_H_

#समावेश "smu7_hwmgr.h"

व्योम smu7_घातergate_vce(काष्ठा pp_hwmgr *hwmgr, bool bgate);
व्योम smu7_घातergate_uvd(काष्ठा pp_hwmgr *hwmgr, bool bgate);
पूर्णांक smu7_घातerकरोwn_uvd(काष्ठा pp_hwmgr *hwmgr);
पूर्णांक smu7_घातergate_acp(काष्ठा pp_hwmgr *hwmgr, bool bgate);
पूर्णांक smu7_disable_घड़ी_घातer_gating(काष्ठा pp_hwmgr *hwmgr);
पूर्णांक smu7_update_घड़ी_gatings(काष्ठा pp_hwmgr *hwmgr,
					स्थिर uपूर्णांक32_t *msg_id);
पूर्णांक smu7_घातergate_gfx(काष्ठा pp_hwmgr *hwmgr, bool enable);

#पूर्ण_अगर
