<शैली गुरु>
/*
 * Copyright 2020 Advanced Micro Devices, Inc.
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

#अगर_अघोषित KFD_SMI_EVENTS_H_INCLUDED
#घोषणा KFD_SMI_EVENTS_H_INCLUDED

पूर्णांक kfd_smi_event_खोलो(काष्ठा kfd_dev *dev, uपूर्णांक32_t *fd);
व्योम kfd_smi_event_update_vmfault(काष्ठा kfd_dev *dev, uपूर्णांक16_t pasid);
व्योम kfd_smi_event_update_thermal_throttling(काष्ठा kfd_dev *dev,
					     uपूर्णांक32_t throttle_biपंचांगask);
व्योम kfd_smi_event_update_gpu_reset(काष्ठा kfd_dev *dev, bool post_reset);

#पूर्ण_अगर
