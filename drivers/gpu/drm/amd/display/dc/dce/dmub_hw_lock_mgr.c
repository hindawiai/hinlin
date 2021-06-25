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
 * Authors: AMD
 *
 */

#समावेश "dmub_hw_lock_mgr.h"
#समावेश "dc_dmub_srv.h"
#समावेश "dc_types.h"
#समावेश "core_types.h"

व्योम dmub_hw_lock_mgr_cmd(काष्ठा dc_dmub_srv *dmub_srv,
				bool lock,
				जोड़ dmub_hw_lock_flags *hw_locks,
				काष्ठा dmub_hw_lock_inst_flags *inst_flags)
अणु
	जोड़ dmub_rb_cmd cmd;

	स_रखो(&cmd, 0, माप(cmd));
	cmd.lock_hw.header.type = DMUB_CMD__HW_LOCK;
	cmd.lock_hw.header.sub_type = 0;
	cmd.lock_hw.header.payload_bytes = माप(काष्ठा dmub_cmd_lock_hw_data);
	cmd.lock_hw.lock_hw_data.client = HW_LOCK_CLIENT_DRIVER;
	cmd.lock_hw.lock_hw_data.lock = lock;
	cmd.lock_hw.lock_hw_data.hw_locks.u8All = hw_locks->u8All;
	स_नकल(&cmd.lock_hw.lock_hw_data.inst_flags, inst_flags, माप(काष्ठा dmub_hw_lock_inst_flags));

	अगर (!lock)
		cmd.lock_hw.lock_hw_data.should_release = 1;

	dc_dmub_srv_cmd_queue(dmub_srv, &cmd);
	dc_dmub_srv_cmd_execute(dmub_srv);
	dc_dmub_srv_रुको_idle(dmub_srv);
पूर्ण

bool should_use_dmub_lock(काष्ठा dc_link *link)
अणु
	वापस false;
पूर्ण
