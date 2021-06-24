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
 */

#अगर_अघोषित __KFD_IOMMU_H__
#घोषणा __KFD_IOMMU_H__

#समावेश <linux/kconfig.h>

#अगर IS_REACHABLE(CONFIG_AMD_IOMMU_V2)

#घोषणा KFD_SUPPORT_IOMMU_V2

पूर्णांक kfd_iommu_check_device(काष्ठा kfd_dev *kfd);
पूर्णांक kfd_iommu_device_init(काष्ठा kfd_dev *kfd);

पूर्णांक kfd_iommu_bind_process_to_device(काष्ठा kfd_process_device *pdd);
व्योम kfd_iommu_unbind_process(काष्ठा kfd_process *p);

व्योम kfd_iommu_suspend(काष्ठा kfd_dev *kfd);
पूर्णांक kfd_iommu_resume(काष्ठा kfd_dev *kfd);

पूर्णांक kfd_iommu_add_perf_counters(काष्ठा kfd_topology_device *kdev);

#अन्यथा

अटल अंतरभूत पूर्णांक kfd_iommu_check_device(काष्ठा kfd_dev *kfd)
अणु
	वापस -ENODEV;
पूर्ण
अटल अंतरभूत पूर्णांक kfd_iommu_device_init(काष्ठा kfd_dev *kfd)
अणु
#अगर IS_MODULE(CONFIG_AMD_IOMMU_V2)
	WARN_ONCE(1, "iommu_v2 module is not usable by built-in KFD");
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक kfd_iommu_bind_process_to_device(
	काष्ठा kfd_process_device *pdd)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम kfd_iommu_unbind_process(काष्ठा kfd_process *p)
अणु
	/* empty */
पूर्ण

अटल अंतरभूत व्योम kfd_iommu_suspend(काष्ठा kfd_dev *kfd)
अणु
	/* empty */
पूर्ण
अटल अंतरभूत पूर्णांक kfd_iommu_resume(काष्ठा kfd_dev *kfd)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक kfd_iommu_add_perf_counters(काष्ठा kfd_topology_device *kdev)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर /* IS_REACHABLE(CONFIG_AMD_IOMMU_V2) */

#पूर्ण_अगर /* __KFD_IOMMU_H__ */
