<शैली गुरु>
/*
 * Copyright 2017 Advanced Micro Devices, Inc.
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

#अगर_अघोषित PP_PSM_H
#घोषणा PP_PSM_H

#समावेश "hwmgr.h"

पूर्णांक psm_init_घातer_state_table(काष्ठा pp_hwmgr *hwmgr);
पूर्णांक psm_fini_घातer_state_table(काष्ठा pp_hwmgr *hwmgr);
पूर्णांक psm_set_boot_states(काष्ठा pp_hwmgr *hwmgr);
पूर्णांक psm_set_perक्रमmance_states(काष्ठा pp_hwmgr *hwmgr);
पूर्णांक psm_set_user_perक्रमmance_state(काष्ठा pp_hwmgr *hwmgr,
					क्रमागत PP_StateUILabel label_id,
					काष्ठा pp_घातer_state **state);
पूर्णांक psm_adjust_घातer_state_dynamic(काष्ठा pp_hwmgr *hwmgr,
				bool skip_display_settings,
				काष्ठा pp_घातer_state *new_ps);

#पूर्ण_अगर
