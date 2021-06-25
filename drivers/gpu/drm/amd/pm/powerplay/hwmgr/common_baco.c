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

#समावेश "common_baco.h"


अटल bool baco_रुको_रेजिस्टर(काष्ठा pp_hwmgr *hwmgr, u32 reg, u32 mask, u32 value)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)(hwmgr->adev);
	u32 समयout = 5000, data;

	करो अणु
		msleep(1);
		data = RREG32(reg);
		समयout--;
	पूर्ण जबतक (value != (data & mask) && (समयout != 0));

	अगर (समयout == 0)
		वापस false;

	वापस true;
पूर्ण

अटल bool baco_cmd_handler(काष्ठा pp_hwmgr *hwmgr, u32 command, u32 reg, u32 mask,
			        u32 shअगरt, u32 value, u32 समयout)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)(hwmgr->adev);
	u32 data;
	bool ret = true;

	चयन (command) अणु
	हाल CMD_WRITE:
		WREG32(reg, value << shअगरt);
		अवरोध;
	हाल CMD_READMODIFYWRITE:
		data = RREG32(reg);
		data = (data & (~mask)) | (value << shअगरt);
		WREG32(reg, data);
		अवरोध;
	हाल CMD_WAITFOR:
		ret = baco_रुको_रेजिस्टर(hwmgr, reg, mask, value);
		अवरोध;
	हाल CMD_DELAY_MS:
		अगर (समयout)
			/* Delay in milli Seconds */
			msleep(समयout);
		अवरोध;
	हाल CMD_DELAY_US:
		अगर (समयout)
			/* Delay in micro Seconds */
			udelay(समयout);
		अवरोध;

	शेष:
		dev_warn(adev->dev, "Invalid BACO command.\n");
		ret = false;
	पूर्ण

	वापस ret;
पूर्ण

bool baco_program_रेजिस्टरs(काष्ठा pp_hwmgr *hwmgr,
			    स्थिर काष्ठा baco_cmd_entry *entry,
			    स्थिर u32 array_size)
अणु
	u32 i, reg = 0;

	क्रम (i = 0; i < array_size; i++) अणु
		अगर ((entry[i].cmd == CMD_WRITE) ||
		    (entry[i].cmd == CMD_READMODIFYWRITE) ||
		    (entry[i].cmd == CMD_WAITFOR))
			reg = entry[i].reg_offset;
		अगर (!baco_cmd_handler(hwmgr, entry[i].cmd, reg, entry[i].mask,
				     entry[i].shअगरt, entry[i].val, entry[i].समयout))
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

bool soc15_baco_program_रेजिस्टरs(काष्ठा pp_hwmgr *hwmgr,
				 स्थिर काष्ठा soc15_baco_cmd_entry *entry,
				 स्थिर u32 array_size)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)(hwmgr->adev);
	u32 i, reg = 0;

	क्रम (i = 0; i < array_size; i++) अणु
		अगर ((entry[i].cmd == CMD_WRITE) ||
		    (entry[i].cmd == CMD_READMODIFYWRITE) ||
		    (entry[i].cmd == CMD_WAITFOR))
			reg = adev->reg_offset[entry[i].hwip][entry[i].inst][entry[i].seg]
				+ entry[i].reg_offset;
		अगर (!baco_cmd_handler(hwmgr, entry[i].cmd, reg, entry[i].mask,
				     entry[i].shअगरt, entry[i].val, entry[i].समयout))
			वापस false;
	पूर्ण

	वापस true;
पूर्ण
