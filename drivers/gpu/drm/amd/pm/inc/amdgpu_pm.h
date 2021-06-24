<शैली गुरु>
/*
 * Copyright 2014 Advanced Micro Devices, Inc.
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

#अगर_अघोषित __AMDGPU_PM_H__
#घोषणा __AMDGPU_PM_H__

काष्ठा cg_flag_name
अणु
	u32 flag;
	स्थिर अक्षर *name;
पूर्ण;

क्रमागत amdgpu_device_attr_flags अणु
	ATTR_FLAG_BASIC = (1 << 0),
	ATTR_FLAG_ONEVF = (1 << 16),
पूर्ण;

#घोषणा ATTR_FLAG_TYPE_MASK	(0x0000ffff)
#घोषणा ATTR_FLAG_MODE_MASK	(0xffff0000)
#घोषणा ATTR_FLAG_MASK_ALL	(0xffffffff)

क्रमागत amdgpu_device_attr_states अणु
	ATTR_STATE_UNSUPPORTED = 0,
	ATTR_STATE_SUPPORTED,
पूर्ण;

काष्ठा amdgpu_device_attr अणु
	काष्ठा device_attribute dev_attr;
	क्रमागत amdgpu_device_attr_flags flags;
	पूर्णांक (*attr_update)(काष्ठा amdgpu_device *adev, काष्ठा amdgpu_device_attr *attr,
			   uपूर्णांक32_t mask, क्रमागत amdgpu_device_attr_states *states);

पूर्ण;

काष्ठा amdgpu_device_attr_entry अणु
	काष्ठा list_head entry;
	काष्ठा amdgpu_device_attr *attr;
पूर्ण;

#घोषणा to_amdgpu_device_attr(_dev_attr) \
	container_of(_dev_attr, काष्ठा amdgpu_device_attr, dev_attr)

#घोषणा __AMDGPU_DEVICE_ATTR(_name, _mode, _show, _store, _flags, ...)	\
	अणु .dev_attr = __ATTR(_name, _mode, _show, _store),		\
	  .flags = _flags,						\
	  ##__VA_ARGS__, पूर्ण

#घोषणा AMDGPU_DEVICE_ATTR(_name, _mode, _flags, ...)			\
	__AMDGPU_DEVICE_ATTR(_name, _mode,				\
			     amdgpu_get_##_name, amdgpu_set_##_name,	\
			     _flags, ##__VA_ARGS__)

#घोषणा AMDGPU_DEVICE_ATTR_RW(_name, _flags, ...)			\
	AMDGPU_DEVICE_ATTR(_name, S_IRUGO | S_IWUSR,			\
			   _flags, ##__VA_ARGS__)

#घोषणा AMDGPU_DEVICE_ATTR_RO(_name, _flags, ...)			\
	__AMDGPU_DEVICE_ATTR(_name, S_IRUGO,				\
			     amdgpu_get_##_name, शून्य,			\
			     _flags, ##__VA_ARGS__)

पूर्णांक amdgpu_pm_sysfs_init(काष्ठा amdgpu_device *adev);
पूर्णांक amdgpu_pm_virt_sysfs_init(काष्ठा amdgpu_device *adev);
व्योम amdgpu_pm_sysfs_fini(काष्ठा amdgpu_device *adev);
व्योम amdgpu_pm_virt_sysfs_fini(काष्ठा amdgpu_device *adev);

व्योम amdgpu_debugfs_pm_init(काष्ठा amdgpu_device *adev);

#पूर्ण_अगर
