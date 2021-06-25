<शैली गुरु>
/*
 * Copyright 2018 Advanced Micro Devices, Inc.
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
#अगर_अघोषित _SMU9_SMUMANAGER_H_
#घोषणा _SMU9_SMUMANAGER_H_

bool smu9_is_smc_ram_running(काष्ठा pp_hwmgr *hwmgr);
पूर्णांक smu9_send_msg_to_smc(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक16_t msg);
पूर्णांक smu9_send_msg_to_smc_with_parameter(काष्ठा pp_hwmgr *hwmgr,
					uपूर्णांक16_t msg, uपूर्णांक32_t parameter);
uपूर्णांक32_t smu9_get_argument(काष्ठा pp_hwmgr *hwmgr);

#पूर्ण_अगर
