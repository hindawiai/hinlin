<शैली गुरु>
/* radeon_evergreen.h -- Private header क्रम radeon driver -*- linux-c -*-
 *
 * Copyright 2010 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * PRECISION INSIGHT AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 */

#अगर_अघोषित __RADEON_EVERGREEN_H__
#घोषणा __RADEON_EVERGREEN_H__

काष्ठा evergreen_mc_save;
काष्ठा evergreen_घातer_info;
काष्ठा radeon_device;

bool evergreen_is_display_hung(काष्ठा radeon_device *rdev);
व्योम evergreen_prपूर्णांक_gpu_status_regs(काष्ठा radeon_device *rdev);
व्योम evergreen_mc_stop(काष्ठा radeon_device *rdev, काष्ठा evergreen_mc_save *save);
व्योम evergreen_mc_resume(काष्ठा radeon_device *rdev, काष्ठा evergreen_mc_save *save);
पूर्णांक evergreen_mc_रुको_क्रम_idle(काष्ठा radeon_device *rdev);
व्योम evergreen_mc_program(काष्ठा radeon_device *rdev);
व्योम evergreen_irq_suspend(काष्ठा radeon_device *rdev);
पूर्णांक evergreen_mc_init(काष्ठा radeon_device *rdev);
व्योम evergreen_fix_pci_max_पढ़ो_req_size(काष्ठा radeon_device *rdev);
व्योम evergreen_pcie_gen2_enable(काष्ठा radeon_device *rdev);
व्योम evergreen_program_aspm(काष्ठा radeon_device *rdev);
व्योम sumo_rlc_fini(काष्ठा radeon_device *rdev);
पूर्णांक sumo_rlc_init(काष्ठा radeon_device *rdev);
व्योम evergreen_gpu_pci_config_reset(काष्ठा radeon_device *rdev);
u32 evergreen_get_number_of_dram_channels(काष्ठा radeon_device *rdev);
व्योम evergreen_prपूर्णांक_gpu_status_regs(काष्ठा radeon_device *rdev);
u32 evergreen_gpu_check_soft_reset(काष्ठा radeon_device *rdev);
पूर्णांक evergreen_rlc_resume(काष्ठा radeon_device *rdev);
काष्ठा evergreen_घातer_info *evergreen_get_pi(काष्ठा radeon_device *rdev);

#पूर्ण_अगर				/* __RADEON_EVERGREEN_H__ */
