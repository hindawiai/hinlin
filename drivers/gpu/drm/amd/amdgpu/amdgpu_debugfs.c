<शैली गुरु>
/*
 * Copyright 2008 Advanced Micro Devices, Inc.
 * Copyright 2008 Red Hat Inc.
 * Copyright 2009 Jerome Glisse.
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

#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/pci.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/poll.h>

#समावेश "amdgpu.h"
#समावेश "amdgpu_pm.h"
#समावेश "amdgpu_dm_debugfs.h"
#समावेश "amdgpu_ras.h"
#समावेश "amdgpu_rap.h"
#समावेश "amdgpu_securedisplay.h"
#समावेश "amdgpu_fw_attestation.h"

पूर्णांक amdgpu_debugfs_रुको_dump(काष्ठा amdgpu_device *adev)
अणु
#अगर defined(CONFIG_DEBUG_FS)
	अचिन्हित दीर्घ समयout = 600 * HZ;
	पूर्णांक ret;

	wake_up_पूर्णांकerruptible(&adev->स्वतःdump.gpu_hang);

	ret = रुको_क्रम_completion_पूर्णांकerruptible_समयout(&adev->स्वतःdump.dumping, समयout);
	अगर (ret == 0) अणु
		pr_err("autodump: timeout, move on to gpu recovery\n");
		वापस -ETIMEDOUT;
	पूर्ण
#पूर्ण_अगर
	वापस 0;
पूर्ण

#अगर defined(CONFIG_DEBUG_FS)

अटल पूर्णांक amdgpu_debugfs_स्वतःdump_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा amdgpu_device *adev = inode->i_निजी;
	पूर्णांक ret;

	file->निजी_data = adev;

	ret = करोwn_पढ़ो_समाप्तable(&adev->reset_sem);
	अगर (ret)
		वापस ret;

	अगर (adev->स्वतःdump.dumping.करोne) अणु
		reinit_completion(&adev->स्वतःdump.dumping);
		ret = 0;
	पूर्ण अन्यथा अणु
		ret = -EBUSY;
	पूर्ण

	up_पढ़ो(&adev->reset_sem);

	वापस ret;
पूर्ण

अटल पूर्णांक amdgpu_debugfs_स्वतःdump_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा amdgpu_device *adev = file->निजी_data;

	complete_all(&adev->स्वतःdump.dumping);
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक amdgpu_debugfs_स्वतःdump_poll(काष्ठा file *file, काष्ठा poll_table_काष्ठा *poll_table)
अणु
	काष्ठा amdgpu_device *adev = file->निजी_data;

	poll_रुको(file, &adev->स्वतःdump.gpu_hang, poll_table);

	अगर (amdgpu_in_reset(adev))
		वापस POLLIN | POLLRDNORM | POLLWRNORM;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations स्वतःdump_debug_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = amdgpu_debugfs_स्वतःdump_खोलो,
	.poll = amdgpu_debugfs_स्वतःdump_poll,
	.release = amdgpu_debugfs_स्वतःdump_release,
पूर्ण;

अटल व्योम amdgpu_debugfs_स्वतःdump_init(काष्ठा amdgpu_device *adev)
अणु
	init_completion(&adev->स्वतःdump.dumping);
	complete_all(&adev->स्वतःdump.dumping);
	init_रुकोqueue_head(&adev->स्वतःdump.gpu_hang);

	debugfs_create_file("amdgpu_autodump", 0600,
		adev_to_drm(adev)->primary->debugfs_root,
		adev, &स्वतःdump_debug_fops);
पूर्ण

/**
 * amdgpu_debugfs_process_reg_op - Handle MMIO रेजिस्टर पढ़ोs/ग_लिखोs
 *
 * @पढ़ो: True अगर पढ़ोing
 * @f: खोलो file handle
 * @buf: User buffer to ग_लिखो/पढ़ो to
 * @size: Number of bytes to ग_लिखो/पढ़ो
 * @pos:  Offset to seek to
 *
 * This debugfs entry has special meaning on the offset being sought.
 * Various bits have dअगरferent meanings:
 *
 * Bit 62:  Indicates a GRBM bank चयन is needed
 * Bit 61:  Indicates a SRBM bank चयन is needed (implies bit 62 is
 * 	    zero)
 * Bits 24..33: The SE or ME selector अगर needed
 * Bits 34..43: The SH (or SA) or PIPE selector अगर needed
 * Bits 44..53: The INSTANCE (or CU/WGP) or QUEUE selector अगर needed
 *
 * Bit 23:  Indicates that the PM घातer gating lock should be held
 * 	    This is necessary to पढ़ो रेजिस्टरs that might be
 * 	    unreliable during a घातer gating transistion.
 *
 * The lower bits are the BYTE offset of the रेजिस्टर to पढ़ो.  This
 * allows पढ़ोing multiple रेजिस्टरs in a single call and having
 * the वापसed size reflect that.
 */
अटल पूर्णांक  amdgpu_debugfs_process_reg_op(bool पढ़ो, काष्ठा file *f,
		अक्षर __user *buf, माप_प्रकार size, loff_t *pos)
अणु
	काष्ठा amdgpu_device *adev = file_inode(f)->i_निजी;
	sमाप_प्रकार result = 0;
	पूर्णांक r;
	bool pm_pg_lock, use_bank, use_ring;
	अचिन्हित instance_bank, sh_bank, se_bank, me, pipe, queue, vmid;

	pm_pg_lock = use_bank = use_ring = false;
	instance_bank = sh_bank = se_bank = me = pipe = queue = vmid = 0;

	अगर (size & 0x3 || *pos & 0x3 ||
			((*pos & (1ULL << 62)) && (*pos & (1ULL << 61))))
		वापस -EINVAL;

	/* are we पढ़ोing रेजिस्टरs क्रम which a PG lock is necessary? */
	pm_pg_lock = (*pos >> 23) & 1;

	अगर (*pos & (1ULL << 62)) अणु
		se_bank = (*pos & GENMASK_ULL(33, 24)) >> 24;
		sh_bank = (*pos & GENMASK_ULL(43, 34)) >> 34;
		instance_bank = (*pos & GENMASK_ULL(53, 44)) >> 44;

		अगर (se_bank == 0x3FF)
			se_bank = 0xFFFFFFFF;
		अगर (sh_bank == 0x3FF)
			sh_bank = 0xFFFFFFFF;
		अगर (instance_bank == 0x3FF)
			instance_bank = 0xFFFFFFFF;
		use_bank = true;
	पूर्ण अन्यथा अगर (*pos & (1ULL << 61)) अणु

		me = (*pos & GENMASK_ULL(33, 24)) >> 24;
		pipe = (*pos & GENMASK_ULL(43, 34)) >> 34;
		queue = (*pos & GENMASK_ULL(53, 44)) >> 44;
		vmid = (*pos & GENMASK_ULL(58, 54)) >> 54;

		use_ring = true;
	पूर्ण अन्यथा अणु
		use_bank = use_ring = false;
	पूर्ण

	*pos &= (1UL << 22) - 1;

	r = pm_runसमय_get_sync(adev_to_drm(adev)->dev);
	अगर (r < 0) अणु
		pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);
		वापस r;
	पूर्ण

	r = amdgpu_virt_enable_access_debugfs(adev);
	अगर (r < 0) अणु
		pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);
		वापस r;
	पूर्ण

	अगर (use_bank) अणु
		अगर ((sh_bank != 0xFFFFFFFF && sh_bank >= adev->gfx.config.max_sh_per_se) ||
		    (se_bank != 0xFFFFFFFF && se_bank >= adev->gfx.config.max_shader_engines)) अणु
			pm_runसमय_mark_last_busy(adev_to_drm(adev)->dev);
			pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);
			amdgpu_virt_disable_access_debugfs(adev);
			वापस -EINVAL;
		पूर्ण
		mutex_lock(&adev->grbm_idx_mutex);
		amdgpu_gfx_select_se_sh(adev, se_bank,
					sh_bank, instance_bank);
	पूर्ण अन्यथा अगर (use_ring) अणु
		mutex_lock(&adev->srbm_mutex);
		amdgpu_gfx_select_me_pipe_q(adev, me, pipe, queue, vmid);
	पूर्ण

	अगर (pm_pg_lock)
		mutex_lock(&adev->pm.mutex);

	जबतक (size) अणु
		uपूर्णांक32_t value;

		अगर (पढ़ो) अणु
			value = RREG32(*pos >> 2);
			r = put_user(value, (uपूर्णांक32_t *)buf);
		पूर्ण अन्यथा अणु
			r = get_user(value, (uपूर्णांक32_t *)buf);
			अगर (!r)
				amdgpu_mm_wreg_mmio_rlc(adev, *pos >> 2, value);
		पूर्ण
		अगर (r) अणु
			result = r;
			जाओ end;
		पूर्ण

		result += 4;
		buf += 4;
		*pos += 4;
		size -= 4;
	पूर्ण

end:
	अगर (use_bank) अणु
		amdgpu_gfx_select_se_sh(adev, 0xffffffff, 0xffffffff, 0xffffffff);
		mutex_unlock(&adev->grbm_idx_mutex);
	पूर्ण अन्यथा अगर (use_ring) अणु
		amdgpu_gfx_select_me_pipe_q(adev, 0, 0, 0, 0);
		mutex_unlock(&adev->srbm_mutex);
	पूर्ण

	अगर (pm_pg_lock)
		mutex_unlock(&adev->pm.mutex);

	pm_runसमय_mark_last_busy(adev_to_drm(adev)->dev);
	pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);

	amdgpu_virt_disable_access_debugfs(adev);
	वापस result;
पूर्ण

/*
 * amdgpu_debugfs_regs_पढ़ो - Callback क्रम पढ़ोing MMIO रेजिस्टरs
 */
अटल sमाप_प्रकार amdgpu_debugfs_regs_पढ़ो(काष्ठा file *f, अक्षर __user *buf,
					माप_प्रकार size, loff_t *pos)
अणु
	वापस amdgpu_debugfs_process_reg_op(true, f, buf, size, pos);
पूर्ण

/*
 * amdgpu_debugfs_regs_ग_लिखो - Callback क्रम writing MMIO रेजिस्टरs
 */
अटल sमाप_प्रकार amdgpu_debugfs_regs_ग_लिखो(काष्ठा file *f, स्थिर अक्षर __user *buf,
					 माप_प्रकार size, loff_t *pos)
अणु
	वापस amdgpu_debugfs_process_reg_op(false, f, (अक्षर __user *)buf, size, pos);
पूर्ण


/**
 * amdgpu_debugfs_regs_pcie_पढ़ो - Read from a PCIE रेजिस्टर
 *
 * @f: खोलो file handle
 * @buf: User buffer to store पढ़ो data in
 * @size: Number of bytes to पढ़ो
 * @pos:  Offset to seek to
 *
 * The lower bits are the BYTE offset of the रेजिस्टर to पढ़ो.  This
 * allows पढ़ोing multiple रेजिस्टरs in a single call and having
 * the वापसed size reflect that.
 */
अटल sमाप_प्रकार amdgpu_debugfs_regs_pcie_पढ़ो(काष्ठा file *f, अक्षर __user *buf,
					माप_प्रकार size, loff_t *pos)
अणु
	काष्ठा amdgpu_device *adev = file_inode(f)->i_निजी;
	sमाप_प्रकार result = 0;
	पूर्णांक r;

	अगर (size & 0x3 || *pos & 0x3)
		वापस -EINVAL;

	r = pm_runसमय_get_sync(adev_to_drm(adev)->dev);
	अगर (r < 0) अणु
		pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);
		वापस r;
	पूर्ण

	r = amdgpu_virt_enable_access_debugfs(adev);
	अगर (r < 0) अणु
		pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);
		वापस r;
	पूर्ण

	जबतक (size) अणु
		uपूर्णांक32_t value;

		value = RREG32_PCIE(*pos);
		r = put_user(value, (uपूर्णांक32_t *)buf);
		अगर (r) अणु
			pm_runसमय_mark_last_busy(adev_to_drm(adev)->dev);
			pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);
			amdgpu_virt_disable_access_debugfs(adev);
			वापस r;
		पूर्ण

		result += 4;
		buf += 4;
		*pos += 4;
		size -= 4;
	पूर्ण

	pm_runसमय_mark_last_busy(adev_to_drm(adev)->dev);
	pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);

	amdgpu_virt_disable_access_debugfs(adev);
	वापस result;
पूर्ण

/**
 * amdgpu_debugfs_regs_pcie_ग_लिखो - Write to a PCIE रेजिस्टर
 *
 * @f: खोलो file handle
 * @buf: User buffer to ग_लिखो data from
 * @size: Number of bytes to ग_लिखो
 * @pos:  Offset to seek to
 *
 * The lower bits are the BYTE offset of the रेजिस्टर to ग_लिखो.  This
 * allows writing multiple रेजिस्टरs in a single call and having
 * the वापसed size reflect that.
 */
अटल sमाप_प्रकार amdgpu_debugfs_regs_pcie_ग_लिखो(काष्ठा file *f, स्थिर अक्षर __user *buf,
					 माप_प्रकार size, loff_t *pos)
अणु
	काष्ठा amdgpu_device *adev = file_inode(f)->i_निजी;
	sमाप_प्रकार result = 0;
	पूर्णांक r;

	अगर (size & 0x3 || *pos & 0x3)
		वापस -EINVAL;

	r = pm_runसमय_get_sync(adev_to_drm(adev)->dev);
	अगर (r < 0) अणु
		pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);
		वापस r;
	पूर्ण

	r = amdgpu_virt_enable_access_debugfs(adev);
	अगर (r < 0) अणु
		pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);
		वापस r;
	पूर्ण

	जबतक (size) अणु
		uपूर्णांक32_t value;

		r = get_user(value, (uपूर्णांक32_t *)buf);
		अगर (r) अणु
			pm_runसमय_mark_last_busy(adev_to_drm(adev)->dev);
			pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);
			amdgpu_virt_disable_access_debugfs(adev);
			वापस r;
		पूर्ण

		WREG32_PCIE(*pos, value);

		result += 4;
		buf += 4;
		*pos += 4;
		size -= 4;
	पूर्ण

	pm_runसमय_mark_last_busy(adev_to_drm(adev)->dev);
	pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);

	amdgpu_virt_disable_access_debugfs(adev);
	वापस result;
पूर्ण

/**
 * amdgpu_debugfs_regs_didt_पढ़ो - Read from a DIDT रेजिस्टर
 *
 * @f: खोलो file handle
 * @buf: User buffer to store पढ़ो data in
 * @size: Number of bytes to पढ़ो
 * @pos:  Offset to seek to
 *
 * The lower bits are the BYTE offset of the रेजिस्टर to पढ़ो.  This
 * allows पढ़ोing multiple रेजिस्टरs in a single call and having
 * the वापसed size reflect that.
 */
अटल sमाप_प्रकार amdgpu_debugfs_regs_didt_पढ़ो(काष्ठा file *f, अक्षर __user *buf,
					माप_प्रकार size, loff_t *pos)
अणु
	काष्ठा amdgpu_device *adev = file_inode(f)->i_निजी;
	sमाप_प्रकार result = 0;
	पूर्णांक r;

	अगर (size & 0x3 || *pos & 0x3)
		वापस -EINVAL;

	r = pm_runसमय_get_sync(adev_to_drm(adev)->dev);
	अगर (r < 0) अणु
		pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);
		वापस r;
	पूर्ण

	r = amdgpu_virt_enable_access_debugfs(adev);
	अगर (r < 0) अणु
		pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);
		वापस r;
	पूर्ण

	जबतक (size) अणु
		uपूर्णांक32_t value;

		value = RREG32_DIDT(*pos >> 2);
		r = put_user(value, (uपूर्णांक32_t *)buf);
		अगर (r) अणु
			pm_runसमय_mark_last_busy(adev_to_drm(adev)->dev);
			pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);
			amdgpu_virt_disable_access_debugfs(adev);
			वापस r;
		पूर्ण

		result += 4;
		buf += 4;
		*pos += 4;
		size -= 4;
	पूर्ण

	pm_runसमय_mark_last_busy(adev_to_drm(adev)->dev);
	pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);

	amdgpu_virt_disable_access_debugfs(adev);
	वापस result;
पूर्ण

/**
 * amdgpu_debugfs_regs_didt_ग_लिखो - Write to a DIDT रेजिस्टर
 *
 * @f: खोलो file handle
 * @buf: User buffer to ग_लिखो data from
 * @size: Number of bytes to ग_लिखो
 * @pos:  Offset to seek to
 *
 * The lower bits are the BYTE offset of the रेजिस्टर to ग_लिखो.  This
 * allows writing multiple रेजिस्टरs in a single call and having
 * the वापसed size reflect that.
 */
अटल sमाप_प्रकार amdgpu_debugfs_regs_didt_ग_लिखो(काष्ठा file *f, स्थिर अक्षर __user *buf,
					 माप_प्रकार size, loff_t *pos)
अणु
	काष्ठा amdgpu_device *adev = file_inode(f)->i_निजी;
	sमाप_प्रकार result = 0;
	पूर्णांक r;

	अगर (size & 0x3 || *pos & 0x3)
		वापस -EINVAL;

	r = pm_runसमय_get_sync(adev_to_drm(adev)->dev);
	अगर (r < 0) अणु
		pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);
		वापस r;
	पूर्ण

	r = amdgpu_virt_enable_access_debugfs(adev);
	अगर (r < 0) अणु
		pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);
		वापस r;
	पूर्ण

	जबतक (size) अणु
		uपूर्णांक32_t value;

		r = get_user(value, (uपूर्णांक32_t *)buf);
		अगर (r) अणु
			pm_runसमय_mark_last_busy(adev_to_drm(adev)->dev);
			pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);
			amdgpu_virt_disable_access_debugfs(adev);
			वापस r;
		पूर्ण

		WREG32_DIDT(*pos >> 2, value);

		result += 4;
		buf += 4;
		*pos += 4;
		size -= 4;
	पूर्ण

	pm_runसमय_mark_last_busy(adev_to_drm(adev)->dev);
	pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);

	amdgpu_virt_disable_access_debugfs(adev);
	वापस result;
पूर्ण

/**
 * amdgpu_debugfs_regs_smc_पढ़ो - Read from a SMC रेजिस्टर
 *
 * @f: खोलो file handle
 * @buf: User buffer to store पढ़ो data in
 * @size: Number of bytes to पढ़ो
 * @pos:  Offset to seek to
 *
 * The lower bits are the BYTE offset of the रेजिस्टर to पढ़ो.  This
 * allows पढ़ोing multiple रेजिस्टरs in a single call and having
 * the वापसed size reflect that.
 */
अटल sमाप_प्रकार amdgpu_debugfs_regs_smc_पढ़ो(काष्ठा file *f, अक्षर __user *buf,
					माप_प्रकार size, loff_t *pos)
अणु
	काष्ठा amdgpu_device *adev = file_inode(f)->i_निजी;
	sमाप_प्रकार result = 0;
	पूर्णांक r;

	अगर (size & 0x3 || *pos & 0x3)
		वापस -EINVAL;

	r = pm_runसमय_get_sync(adev_to_drm(adev)->dev);
	अगर (r < 0) अणु
		pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);
		वापस r;
	पूर्ण

	r = amdgpu_virt_enable_access_debugfs(adev);
	अगर (r < 0) अणु
		pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);
		वापस r;
	पूर्ण

	जबतक (size) अणु
		uपूर्णांक32_t value;

		value = RREG32_SMC(*pos);
		r = put_user(value, (uपूर्णांक32_t *)buf);
		अगर (r) अणु
			pm_runसमय_mark_last_busy(adev_to_drm(adev)->dev);
			pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);
			amdgpu_virt_disable_access_debugfs(adev);
			वापस r;
		पूर्ण

		result += 4;
		buf += 4;
		*pos += 4;
		size -= 4;
	पूर्ण

	pm_runसमय_mark_last_busy(adev_to_drm(adev)->dev);
	pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);

	amdgpu_virt_disable_access_debugfs(adev);
	वापस result;
पूर्ण

/**
 * amdgpu_debugfs_regs_smc_ग_लिखो - Write to a SMC रेजिस्टर
 *
 * @f: खोलो file handle
 * @buf: User buffer to ग_लिखो data from
 * @size: Number of bytes to ग_लिखो
 * @pos:  Offset to seek to
 *
 * The lower bits are the BYTE offset of the रेजिस्टर to ग_लिखो.  This
 * allows writing multiple रेजिस्टरs in a single call and having
 * the वापसed size reflect that.
 */
अटल sमाप_प्रकार amdgpu_debugfs_regs_smc_ग_लिखो(काष्ठा file *f, स्थिर अक्षर __user *buf,
					 माप_प्रकार size, loff_t *pos)
अणु
	काष्ठा amdgpu_device *adev = file_inode(f)->i_निजी;
	sमाप_प्रकार result = 0;
	पूर्णांक r;

	अगर (size & 0x3 || *pos & 0x3)
		वापस -EINVAL;

	r = pm_runसमय_get_sync(adev_to_drm(adev)->dev);
	अगर (r < 0) अणु
		pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);
		वापस r;
	पूर्ण

	r = amdgpu_virt_enable_access_debugfs(adev);
	अगर (r < 0) अणु
		pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);
		वापस r;
	पूर्ण

	जबतक (size) अणु
		uपूर्णांक32_t value;

		r = get_user(value, (uपूर्णांक32_t *)buf);
		अगर (r) अणु
			pm_runसमय_mark_last_busy(adev_to_drm(adev)->dev);
			pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);
			amdgpu_virt_disable_access_debugfs(adev);
			वापस r;
		पूर्ण

		WREG32_SMC(*pos, value);

		result += 4;
		buf += 4;
		*pos += 4;
		size -= 4;
	पूर्ण

	pm_runसमय_mark_last_busy(adev_to_drm(adev)->dev);
	pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);

	amdgpu_virt_disable_access_debugfs(adev);
	वापस result;
पूर्ण

/**
 * amdgpu_debugfs_gca_config_पढ़ो - Read from gfx config data
 *
 * @f: खोलो file handle
 * @buf: User buffer to store पढ़ो data in
 * @size: Number of bytes to पढ़ो
 * @pos:  Offset to seek to
 *
 * This file is used to access configuration data in a somewhat
 * stable fashion.  The क्रमmat is a series of DWORDs with the first
 * indicating which revision it is.  New content is appended to the
 * end so that older software can still पढ़ो the data.
 */

अटल sमाप_प्रकार amdgpu_debugfs_gca_config_पढ़ो(काष्ठा file *f, अक्षर __user *buf,
					माप_प्रकार size, loff_t *pos)
अणु
	काष्ठा amdgpu_device *adev = file_inode(f)->i_निजी;
	sमाप_प्रकार result = 0;
	पूर्णांक r;
	uपूर्णांक32_t *config, no_regs = 0;

	अगर (size & 0x3 || *pos & 0x3)
		वापस -EINVAL;

	config = kदो_स्मृति_array(256, माप(*config), GFP_KERNEL);
	अगर (!config)
		वापस -ENOMEM;

	/* version, increment each समय something is added */
	config[no_regs++] = 3;
	config[no_regs++] = adev->gfx.config.max_shader_engines;
	config[no_regs++] = adev->gfx.config.max_tile_pipes;
	config[no_regs++] = adev->gfx.config.max_cu_per_sh;
	config[no_regs++] = adev->gfx.config.max_sh_per_se;
	config[no_regs++] = adev->gfx.config.max_backends_per_se;
	config[no_regs++] = adev->gfx.config.max_texture_channel_caches;
	config[no_regs++] = adev->gfx.config.max_gprs;
	config[no_regs++] = adev->gfx.config.max_gs_thपढ़ोs;
	config[no_regs++] = adev->gfx.config.max_hw_contexts;
	config[no_regs++] = adev->gfx.config.sc_prim_fअगरo_size_frontend;
	config[no_regs++] = adev->gfx.config.sc_prim_fअगरo_size_backend;
	config[no_regs++] = adev->gfx.config.sc_hiz_tile_fअगरo_size;
	config[no_regs++] = adev->gfx.config.sc_earlyz_tile_fअगरo_size;
	config[no_regs++] = adev->gfx.config.num_tile_pipes;
	config[no_regs++] = adev->gfx.config.backend_enable_mask;
	config[no_regs++] = adev->gfx.config.mem_max_burst_length_bytes;
	config[no_regs++] = adev->gfx.config.mem_row_size_in_kb;
	config[no_regs++] = adev->gfx.config.shader_engine_tile_size;
	config[no_regs++] = adev->gfx.config.num_gpus;
	config[no_regs++] = adev->gfx.config.multi_gpu_tile_size;
	config[no_regs++] = adev->gfx.config.mc_arb_ramcfg;
	config[no_regs++] = adev->gfx.config.gb_addr_config;
	config[no_regs++] = adev->gfx.config.num_rbs;

	/* rev==1 */
	config[no_regs++] = adev->rev_id;
	config[no_regs++] = adev->pg_flags;
	config[no_regs++] = adev->cg_flags;

	/* rev==2 */
	config[no_regs++] = adev->family;
	config[no_regs++] = adev->बाह्यal_rev_id;

	/* rev==3 */
	config[no_regs++] = adev->pdev->device;
	config[no_regs++] = adev->pdev->revision;
	config[no_regs++] = adev->pdev->subप्रणाली_device;
	config[no_regs++] = adev->pdev->subप्रणाली_venकरोr;

	जबतक (size && (*pos < no_regs * 4)) अणु
		uपूर्णांक32_t value;

		value = config[*pos >> 2];
		r = put_user(value, (uपूर्णांक32_t *)buf);
		अगर (r) अणु
			kमुक्त(config);
			वापस r;
		पूर्ण

		result += 4;
		buf += 4;
		*pos += 4;
		size -= 4;
	पूर्ण

	kमुक्त(config);
	वापस result;
पूर्ण

/**
 * amdgpu_debugfs_sensor_पढ़ो - Read from the घातerplay sensors
 *
 * @f: खोलो file handle
 * @buf: User buffer to store पढ़ो data in
 * @size: Number of bytes to पढ़ो
 * @pos:  Offset to seek to
 *
 * The offset is treated as the BYTE address of one of the sensors
 * क्रमागतerated in amd/include/kgd_pp_पूर्णांकerface.h under the
 * 'amd_pp_sensors' क्रमागतeration.  For instance to पढ़ो the UVD VCLK
 * you would use the offset 3 * 4 = 12.
 */
अटल sमाप_प्रकार amdgpu_debugfs_sensor_पढ़ो(काष्ठा file *f, अक्षर __user *buf,
					माप_प्रकार size, loff_t *pos)
अणु
	काष्ठा amdgpu_device *adev = file_inode(f)->i_निजी;
	पूर्णांक idx, x, outsize, r, valuesize;
	uपूर्णांक32_t values[16];

	अगर (size & 3 || *pos & 0x3)
		वापस -EINVAL;

	अगर (!adev->pm.dpm_enabled)
		वापस -EINVAL;

	/* convert offset to sensor number */
	idx = *pos >> 2;

	valuesize = माप(values);

	r = pm_runसमय_get_sync(adev_to_drm(adev)->dev);
	अगर (r < 0) अणु
		pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);
		वापस r;
	पूर्ण

	r = amdgpu_virt_enable_access_debugfs(adev);
	अगर (r < 0) अणु
		pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);
		वापस r;
	पूर्ण

	r = amdgpu_dpm_पढ़ो_sensor(adev, idx, &values[0], &valuesize);

	pm_runसमय_mark_last_busy(adev_to_drm(adev)->dev);
	pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);

	अगर (r) अणु
		amdgpu_virt_disable_access_debugfs(adev);
		वापस r;
	पूर्ण

	अगर (size > valuesize) अणु
		amdgpu_virt_disable_access_debugfs(adev);
		वापस -EINVAL;
	पूर्ण

	outsize = 0;
	x = 0;
	अगर (!r) अणु
		जबतक (size) अणु
			r = put_user(values[x++], (पूर्णांक32_t *)buf);
			buf += 4;
			size -= 4;
			outsize += 4;
		पूर्ण
	पूर्ण

	amdgpu_virt_disable_access_debugfs(adev);
	वापस !r ? outsize : r;
पूर्ण

/** amdgpu_debugfs_wave_पढ़ो - Read WAVE STATUS data
 *
 * @f: खोलो file handle
 * @buf: User buffer to store पढ़ो data in
 * @size: Number of bytes to पढ़ो
 * @pos:  Offset to seek to
 *
 * The offset being sought changes which wave that the status data
 * will be वापसed क्रम.  The bits are used as follows:
 *
 * Bits 0..6: 	Byte offset पूर्णांकo data
 * Bits 7..14:	SE selector
 * Bits 15..22:	SH/SA selector
 * Bits 23..30: CU/अणुWGP+SIMDपूर्ण selector
 * Bits 31..36: WAVE ID selector
 * Bits 37..44: SIMD ID selector
 *
 * The वापसed data begins with one DWORD of version inक्रमmation
 * Followed by WAVE STATUS रेजिस्टरs relevant to the GFX IP version
 * being used.  See gfx_v8_0_पढ़ो_wave_data() क्रम an example output.
 */
अटल sमाप_प्रकार amdgpu_debugfs_wave_पढ़ो(काष्ठा file *f, अक्षर __user *buf,
					माप_प्रकार size, loff_t *pos)
अणु
	काष्ठा amdgpu_device *adev = f->f_inode->i_निजी;
	पूर्णांक r, x;
	sमाप_प्रकार result = 0;
	uपूर्णांक32_t offset, se, sh, cu, wave, simd, data[32];

	अगर (size & 3 || *pos & 3)
		वापस -EINVAL;

	/* decode offset */
	offset = (*pos & GENMASK_ULL(6, 0));
	se = (*pos & GENMASK_ULL(14, 7)) >> 7;
	sh = (*pos & GENMASK_ULL(22, 15)) >> 15;
	cu = (*pos & GENMASK_ULL(30, 23)) >> 23;
	wave = (*pos & GENMASK_ULL(36, 31)) >> 31;
	simd = (*pos & GENMASK_ULL(44, 37)) >> 37;

	r = pm_runसमय_get_sync(adev_to_drm(adev)->dev);
	अगर (r < 0) अणु
		pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);
		वापस r;
	पूर्ण

	r = amdgpu_virt_enable_access_debugfs(adev);
	अगर (r < 0) अणु
		pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);
		वापस r;
	पूर्ण

	/* चयन to the specअगरic se/sh/cu */
	mutex_lock(&adev->grbm_idx_mutex);
	amdgpu_gfx_select_se_sh(adev, se, sh, cu);

	x = 0;
	अगर (adev->gfx.funcs->पढ़ो_wave_data)
		adev->gfx.funcs->पढ़ो_wave_data(adev, simd, wave, data, &x);

	amdgpu_gfx_select_se_sh(adev, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF);
	mutex_unlock(&adev->grbm_idx_mutex);

	pm_runसमय_mark_last_busy(adev_to_drm(adev)->dev);
	pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);

	अगर (!x) अणु
		amdgpu_virt_disable_access_debugfs(adev);
		वापस -EINVAL;
	पूर्ण

	जबतक (size && (offset < x * 4)) अणु
		uपूर्णांक32_t value;

		value = data[offset >> 2];
		r = put_user(value, (uपूर्णांक32_t *)buf);
		अगर (r) अणु
			amdgpu_virt_disable_access_debugfs(adev);
			वापस r;
		पूर्ण

		result += 4;
		buf += 4;
		offset += 4;
		size -= 4;
	पूर्ण

	amdgpu_virt_disable_access_debugfs(adev);
	वापस result;
पूर्ण

/** amdgpu_debugfs_gpr_पढ़ो - Read wave gprs
 *
 * @f: खोलो file handle
 * @buf: User buffer to store पढ़ो data in
 * @size: Number of bytes to पढ़ो
 * @pos:  Offset to seek to
 *
 * The offset being sought changes which wave that the status data
 * will be वापसed क्रम.  The bits are used as follows:
 *
 * Bits 0..11:	Byte offset पूर्णांकo data
 * Bits 12..19:	SE selector
 * Bits 20..27:	SH/SA selector
 * Bits 28..35: CU/अणुWGP+SIMDपूर्ण selector
 * Bits 36..43: WAVE ID selector
 * Bits 37..44: SIMD ID selector
 * Bits 52..59: Thपढ़ो selector
 * Bits 60..61: Bank selector (VGPR=0,SGPR=1)
 *
 * The वापस data comes from the SGPR or VGPR रेजिस्टर bank क्रम
 * the selected operational unit.
 */
अटल sमाप_प्रकार amdgpu_debugfs_gpr_पढ़ो(काष्ठा file *f, अक्षर __user *buf,
					माप_प्रकार size, loff_t *pos)
अणु
	काष्ठा amdgpu_device *adev = f->f_inode->i_निजी;
	पूर्णांक r;
	sमाप_प्रकार result = 0;
	uपूर्णांक32_t offset, se, sh, cu, wave, simd, thपढ़ो, bank, *data;

	अगर (size > 4096 || size & 3 || *pos & 3)
		वापस -EINVAL;

	/* decode offset */
	offset = (*pos & GENMASK_ULL(11, 0)) >> 2;
	se = (*pos & GENMASK_ULL(19, 12)) >> 12;
	sh = (*pos & GENMASK_ULL(27, 20)) >> 20;
	cu = (*pos & GENMASK_ULL(35, 28)) >> 28;
	wave = (*pos & GENMASK_ULL(43, 36)) >> 36;
	simd = (*pos & GENMASK_ULL(51, 44)) >> 44;
	thपढ़ो = (*pos & GENMASK_ULL(59, 52)) >> 52;
	bank = (*pos & GENMASK_ULL(61, 60)) >> 60;

	data = kसुस्मृति(1024, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	r = pm_runसमय_get_sync(adev_to_drm(adev)->dev);
	अगर (r < 0)
		जाओ err;

	r = amdgpu_virt_enable_access_debugfs(adev);
	अगर (r < 0)
		जाओ err;

	/* चयन to the specअगरic se/sh/cu */
	mutex_lock(&adev->grbm_idx_mutex);
	amdgpu_gfx_select_se_sh(adev, se, sh, cu);

	अगर (bank == 0) अणु
		अगर (adev->gfx.funcs->पढ़ो_wave_vgprs)
			adev->gfx.funcs->पढ़ो_wave_vgprs(adev, simd, wave, thपढ़ो, offset, size>>2, data);
	पूर्ण अन्यथा अणु
		अगर (adev->gfx.funcs->पढ़ो_wave_sgprs)
			adev->gfx.funcs->पढ़ो_wave_sgprs(adev, simd, wave, offset, size>>2, data);
	पूर्ण

	amdgpu_gfx_select_se_sh(adev, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF);
	mutex_unlock(&adev->grbm_idx_mutex);

	pm_runसमय_mark_last_busy(adev_to_drm(adev)->dev);
	pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);

	जबतक (size) अणु
		uपूर्णांक32_t value;

		value = data[result >> 2];
		r = put_user(value, (uपूर्णांक32_t *)buf);
		अगर (r) अणु
			amdgpu_virt_disable_access_debugfs(adev);
			जाओ err;
		पूर्ण

		result += 4;
		buf += 4;
		size -= 4;
	पूर्ण

	kमुक्त(data);
	amdgpu_virt_disable_access_debugfs(adev);
	वापस result;

err:
	pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);
	kमुक्त(data);
	वापस r;
पूर्ण

/**
 * amdgpu_debugfs_regs_gfxoff_ग_लिखो - Enable/disable GFXOFF
 *
 * @f: खोलो file handle
 * @buf: User buffer to ग_लिखो data from
 * @size: Number of bytes to ग_लिखो
 * @pos:  Offset to seek to
 *
 * Write a 32-bit zero to disable or a 32-bit non-zero to enable
 */
अटल sमाप_प्रकार amdgpu_debugfs_gfxoff_ग_लिखो(काष्ठा file *f, स्थिर अक्षर __user *buf,
					 माप_प्रकार size, loff_t *pos)
अणु
	काष्ठा amdgpu_device *adev = file_inode(f)->i_निजी;
	sमाप_प्रकार result = 0;
	पूर्णांक r;

	अगर (size & 0x3 || *pos & 0x3)
		वापस -EINVAL;

	r = pm_runसमय_get_sync(adev_to_drm(adev)->dev);
	अगर (r < 0) अणु
		pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);
		वापस r;
	पूर्ण

	जबतक (size) अणु
		uपूर्णांक32_t value;

		r = get_user(value, (uपूर्णांक32_t *)buf);
		अगर (r) अणु
			pm_runसमय_mark_last_busy(adev_to_drm(adev)->dev);
			pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);
			वापस r;
		पूर्ण

		amdgpu_gfx_off_ctrl(adev, value ? true : false);

		result += 4;
		buf += 4;
		*pos += 4;
		size -= 4;
	पूर्ण

	pm_runसमय_mark_last_busy(adev_to_drm(adev)->dev);
	pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);

	वापस result;
पूर्ण


/**
 * amdgpu_debugfs_regs_gfxoff_status - पढ़ो gfxoff status
 *
 * @f: खोलो file handle
 * @buf: User buffer to store पढ़ो data in
 * @size: Number of bytes to पढ़ो
 * @pos:  Offset to seek to
 */
अटल sमाप_प्रकार amdgpu_debugfs_gfxoff_पढ़ो(काष्ठा file *f, अक्षर __user *buf,
					 माप_प्रकार size, loff_t *pos)
अणु
	काष्ठा amdgpu_device *adev = file_inode(f)->i_निजी;
	sमाप_प्रकार result = 0;
	पूर्णांक r;

	अगर (size & 0x3 || *pos & 0x3)
		वापस -EINVAL;

	r = pm_runसमय_get_sync(adev_to_drm(adev)->dev);
	अगर (r < 0)
		वापस r;

	जबतक (size) अणु
		uपूर्णांक32_t value;

		r = amdgpu_get_gfx_off_status(adev, &value);
		अगर (r) अणु
			pm_runसमय_mark_last_busy(adev_to_drm(adev)->dev);
			pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);
			वापस r;
		पूर्ण

		r = put_user(value, (uपूर्णांक32_t *)buf);
		अगर (r) अणु
			pm_runसमय_mark_last_busy(adev_to_drm(adev)->dev);
			pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);
			वापस r;
		पूर्ण

		result += 4;
		buf += 4;
		*pos += 4;
		size -= 4;
	पूर्ण

	pm_runसमय_mark_last_busy(adev_to_drm(adev)->dev);
	pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);

	वापस result;
पूर्ण

अटल स्थिर काष्ठा file_operations amdgpu_debugfs_regs_fops = अणु
	.owner = THIS_MODULE,
	.पढ़ो = amdgpu_debugfs_regs_पढ़ो,
	.ग_लिखो = amdgpu_debugfs_regs_ग_लिखो,
	.llseek = शेष_llseek
पूर्ण;
अटल स्थिर काष्ठा file_operations amdgpu_debugfs_regs_didt_fops = अणु
	.owner = THIS_MODULE,
	.पढ़ो = amdgpu_debugfs_regs_didt_पढ़ो,
	.ग_लिखो = amdgpu_debugfs_regs_didt_ग_लिखो,
	.llseek = शेष_llseek
पूर्ण;
अटल स्थिर काष्ठा file_operations amdgpu_debugfs_regs_pcie_fops = अणु
	.owner = THIS_MODULE,
	.पढ़ो = amdgpu_debugfs_regs_pcie_पढ़ो,
	.ग_लिखो = amdgpu_debugfs_regs_pcie_ग_लिखो,
	.llseek = शेष_llseek
पूर्ण;
अटल स्थिर काष्ठा file_operations amdgpu_debugfs_regs_smc_fops = अणु
	.owner = THIS_MODULE,
	.पढ़ो = amdgpu_debugfs_regs_smc_पढ़ो,
	.ग_लिखो = amdgpu_debugfs_regs_smc_ग_लिखो,
	.llseek = शेष_llseek
पूर्ण;

अटल स्थिर काष्ठा file_operations amdgpu_debugfs_gca_config_fops = अणु
	.owner = THIS_MODULE,
	.पढ़ो = amdgpu_debugfs_gca_config_पढ़ो,
	.llseek = शेष_llseek
पूर्ण;

अटल स्थिर काष्ठा file_operations amdgpu_debugfs_sensors_fops = अणु
	.owner = THIS_MODULE,
	.पढ़ो = amdgpu_debugfs_sensor_पढ़ो,
	.llseek = शेष_llseek
पूर्ण;

अटल स्थिर काष्ठा file_operations amdgpu_debugfs_wave_fops = अणु
	.owner = THIS_MODULE,
	.पढ़ो = amdgpu_debugfs_wave_पढ़ो,
	.llseek = शेष_llseek
पूर्ण;
अटल स्थिर काष्ठा file_operations amdgpu_debugfs_gpr_fops = अणु
	.owner = THIS_MODULE,
	.पढ़ो = amdgpu_debugfs_gpr_पढ़ो,
	.llseek = शेष_llseek
पूर्ण;

अटल स्थिर काष्ठा file_operations amdgpu_debugfs_gfxoff_fops = अणु
	.owner = THIS_MODULE,
	.पढ़ो = amdgpu_debugfs_gfxoff_पढ़ो,
	.ग_लिखो = amdgpu_debugfs_gfxoff_ग_लिखो,
	.llseek = शेष_llseek
पूर्ण;

अटल स्थिर काष्ठा file_operations *debugfs_regs[] = अणु
	&amdgpu_debugfs_regs_fops,
	&amdgpu_debugfs_regs_didt_fops,
	&amdgpu_debugfs_regs_pcie_fops,
	&amdgpu_debugfs_regs_smc_fops,
	&amdgpu_debugfs_gca_config_fops,
	&amdgpu_debugfs_sensors_fops,
	&amdgpu_debugfs_wave_fops,
	&amdgpu_debugfs_gpr_fops,
	&amdgpu_debugfs_gfxoff_fops,
पूर्ण;

अटल स्थिर अक्षर *debugfs_regs_names[] = अणु
	"amdgpu_regs",
	"amdgpu_regs_didt",
	"amdgpu_regs_pcie",
	"amdgpu_regs_smc",
	"amdgpu_gca_config",
	"amdgpu_sensors",
	"amdgpu_wave",
	"amdgpu_gpr",
	"amdgpu_gfxoff",
पूर्ण;

/**
 * amdgpu_debugfs_regs_init -	Initialize debugfs entries that provide
 * 				रेजिस्टर access.
 *
 * @adev: The device to attach the debugfs entries to
 */
पूर्णांक amdgpu_debugfs_regs_init(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा drm_minor *minor = adev_to_drm(adev)->primary;
	काष्ठा dentry *ent, *root = minor->debugfs_root;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(debugfs_regs); i++) अणु
		ent = debugfs_create_file(debugfs_regs_names[i],
					  S_IFREG | S_IRUGO, root,
					  adev, debugfs_regs[i]);
		अगर (!i && !IS_ERR_OR_शून्य(ent))
			i_size_ग_लिखो(ent->d_inode, adev->rmmio_size);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक amdgpu_debugfs_test_ib_show(काष्ठा seq_file *m, व्योम *unused)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)m->निजी;
	काष्ठा drm_device *dev = adev_to_drm(adev);
	पूर्णांक r = 0, i;

	r = pm_runसमय_get_sync(dev->dev);
	अगर (r < 0) अणु
		pm_runसमय_put_स्वतःsuspend(dev->dev);
		वापस r;
	पूर्ण

	/* Aव्योम accidently unparking the sched thपढ़ो during GPU reset */
	r = करोwn_पढ़ो_समाप्तable(&adev->reset_sem);
	अगर (r)
		वापस r;

	/* hold on the scheduler */
	क्रम (i = 0; i < AMDGPU_MAX_RINGS; i++) अणु
		काष्ठा amdgpu_ring *ring = adev->rings[i];

		अगर (!ring || !ring->sched.thपढ़ो)
			जारी;
		kthपढ़ो_park(ring->sched.thपढ़ो);
	पूर्ण

	seq_म_लिखो(m, "run ib test:\n");
	r = amdgpu_ib_ring_tests(adev);
	अगर (r)
		seq_म_लिखो(m, "ib ring tests failed (%d).\n", r);
	अन्यथा
		seq_म_लिखो(m, "ib ring tests passed.\n");

	/* go on the scheduler */
	क्रम (i = 0; i < AMDGPU_MAX_RINGS; i++) अणु
		काष्ठा amdgpu_ring *ring = adev->rings[i];

		अगर (!ring || !ring->sched.thपढ़ो)
			जारी;
		kthपढ़ो_unpark(ring->sched.thपढ़ो);
	पूर्ण

	up_पढ़ो(&adev->reset_sem);

	pm_runसमय_mark_last_busy(dev->dev);
	pm_runसमय_put_स्वतःsuspend(dev->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक amdgpu_debugfs_evict_vram(व्योम *data, u64 *val)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)data;
	काष्ठा drm_device *dev = adev_to_drm(adev);
	पूर्णांक r;

	r = pm_runसमय_get_sync(dev->dev);
	अगर (r < 0) अणु
		pm_runसमय_put_स्वतःsuspend(dev->dev);
		वापस r;
	पूर्ण

	*val = amdgpu_bo_evict_vram(adev);

	pm_runसमय_mark_last_busy(dev->dev);
	pm_runसमय_put_स्वतःsuspend(dev->dev);

	वापस 0;
पूर्ण


अटल पूर्णांक amdgpu_debugfs_evict_gtt(व्योम *data, u64 *val)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)data;
	काष्ठा drm_device *dev = adev_to_drm(adev);
	काष्ठा tपंचांग_resource_manager *man;
	पूर्णांक r;

	r = pm_runसमय_get_sync(dev->dev);
	अगर (r < 0) अणु
		pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);
		वापस r;
	पूर्ण

	man = tपंचांग_manager_type(&adev->mman.bdev, TTM_PL_TT);
	*val = tपंचांग_resource_manager_evict_all(&adev->mman.bdev, man);

	pm_runसमय_mark_last_busy(dev->dev);
	pm_runसमय_put_स्वतःsuspend(dev->dev);

	वापस 0;
पूर्ण


अटल पूर्णांक amdgpu_debugfs_vm_info_show(काष्ठा seq_file *m, व्योम *unused)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)m->निजी;
	काष्ठा drm_device *dev = adev_to_drm(adev);
	काष्ठा drm_file *file;
	पूर्णांक r;

	r = mutex_lock_पूर्णांकerruptible(&dev->filelist_mutex);
	अगर (r)
		वापस r;

	list_क्रम_each_entry(file, &dev->filelist, lhead) अणु
		काष्ठा amdgpu_fpriv *fpriv = file->driver_priv;
		काष्ठा amdgpu_vm *vm = &fpriv->vm;

		seq_म_लिखो(m, "pid:%d\tProcess:%s ----------\n",
				vm->task_info.pid, vm->task_info.process_name);
		r = amdgpu_bo_reserve(vm->root.base.bo, true);
		अगर (r)
			अवरोध;
		amdgpu_debugfs_vm_bo_info(vm, m);
		amdgpu_bo_unreserve(vm->root.base.bo);
	पूर्ण

	mutex_unlock(&dev->filelist_mutex);

	वापस r;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(amdgpu_debugfs_test_ib);
DEFINE_SHOW_ATTRIBUTE(amdgpu_debugfs_vm_info);
DEFINE_DEBUGFS_ATTRIBUTE(amdgpu_evict_vram_fops, amdgpu_debugfs_evict_vram,
			 शून्य, "%lld\n");
DEFINE_DEBUGFS_ATTRIBUTE(amdgpu_evict_gtt_fops, amdgpu_debugfs_evict_gtt,
			 शून्य, "%lld\n");

अटल व्योम amdgpu_ib_preempt_fences_swap(काष्ठा amdgpu_ring *ring,
					  काष्ठा dma_fence **fences)
अणु
	काष्ठा amdgpu_fence_driver *drv = &ring->fence_drv;
	uपूर्णांक32_t sync_seq, last_seq;

	last_seq = atomic_पढ़ो(&ring->fence_drv.last_seq);
	sync_seq = ring->fence_drv.sync_seq;

	last_seq &= drv->num_fences_mask;
	sync_seq &= drv->num_fences_mask;

	करो अणु
		काष्ठा dma_fence *fence, **ptr;

		++last_seq;
		last_seq &= drv->num_fences_mask;
		ptr = &drv->fences[last_seq];

		fence = rcu_dereference_रक्षित(*ptr, 1);
		RCU_INIT_POINTER(*ptr, शून्य);

		अगर (!fence)
			जारी;

		fences[last_seq] = fence;

	पूर्ण जबतक (last_seq != sync_seq);
पूर्ण

अटल व्योम amdgpu_ib_preempt_संकेत_fences(काष्ठा dma_fence **fences,
					    पूर्णांक length)
अणु
	पूर्णांक i;
	काष्ठा dma_fence *fence;

	क्रम (i = 0; i < length; i++) अणु
		fence = fences[i];
		अगर (!fence)
			जारी;
		dma_fence_संकेत(fence);
		dma_fence_put(fence);
	पूर्ण
पूर्ण

अटल व्योम amdgpu_ib_preempt_job_recovery(काष्ठा drm_gpu_scheduler *sched)
अणु
	काष्ठा drm_sched_job *s_job;
	काष्ठा dma_fence *fence;

	spin_lock(&sched->job_list_lock);
	list_क्रम_each_entry(s_job, &sched->pending_list, list) अणु
		fence = sched->ops->run_job(s_job);
		dma_fence_put(fence);
	पूर्ण
	spin_unlock(&sched->job_list_lock);
पूर्ण

अटल व्योम amdgpu_ib_preempt_mark_partial_job(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_job *job;
	काष्ठा drm_sched_job *s_job, *पंचांगp;
	uपूर्णांक32_t preempt_seq;
	काष्ठा dma_fence *fence, **ptr;
	काष्ठा amdgpu_fence_driver *drv = &ring->fence_drv;
	काष्ठा drm_gpu_scheduler *sched = &ring->sched;
	bool preempted = true;

	अगर (ring->funcs->type != AMDGPU_RING_TYPE_GFX)
		वापस;

	preempt_seq = le32_to_cpu(*(drv->cpu_addr + 2));
	अगर (preempt_seq <= atomic_पढ़ो(&drv->last_seq)) अणु
		preempted = false;
		जाओ no_preempt;
	पूर्ण

	preempt_seq &= drv->num_fences_mask;
	ptr = &drv->fences[preempt_seq];
	fence = rcu_dereference_रक्षित(*ptr, 1);

no_preempt:
	spin_lock(&sched->job_list_lock);
	list_क्रम_each_entry_safe(s_job, पंचांगp, &sched->pending_list, list) अणु
		अगर (dma_fence_is_संकेतed(&s_job->s_fence->finished)) अणु
			/* हटाओ job from ring_mirror_list */
			list_del_init(&s_job->list);
			sched->ops->मुक्त_job(s_job);
			जारी;
		पूर्ण
		job = to_amdgpu_job(s_job);
		अगर (preempted && job->fence == fence)
			/* mark the job as preempted */
			job->preemption_status |= AMDGPU_IB_PREEMPTED;
	पूर्ण
	spin_unlock(&sched->job_list_lock);
पूर्ण

अटल पूर्णांक amdgpu_debugfs_ib_preempt(व्योम *data, u64 val)
अणु
	पूर्णांक r, resched, length;
	काष्ठा amdgpu_ring *ring;
	काष्ठा dma_fence **fences = शून्य;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)data;

	अगर (val >= AMDGPU_MAX_RINGS)
		वापस -EINVAL;

	ring = adev->rings[val];

	अगर (!ring || !ring->funcs->preempt_ib || !ring->sched.thपढ़ो)
		वापस -EINVAL;

	/* the last preemption failed */
	अगर (ring->trail_seq != le32_to_cpu(*ring->trail_fence_cpu_addr))
		वापस -EBUSY;

	length = ring->fence_drv.num_fences_mask + 1;
	fences = kसुस्मृति(length, माप(व्योम *), GFP_KERNEL);
	अगर (!fences)
		वापस -ENOMEM;

	/* Aव्योम accidently unparking the sched thपढ़ो during GPU reset */
	r = करोwn_पढ़ो_समाप्तable(&adev->reset_sem);
	अगर (r)
		जाओ pro_end;

	/* stop the scheduler */
	kthपढ़ो_park(ring->sched.thपढ़ो);

	resched = tपंचांग_bo_lock_delayed_workqueue(&adev->mman.bdev);

	/* preempt the IB */
	r = amdgpu_ring_preempt_ib(ring);
	अगर (r) अणु
		DRM_WARN("failed to preempt ring %d\n", ring->idx);
		जाओ failure;
	पूर्ण

	amdgpu_fence_process(ring);

	अगर (atomic_पढ़ो(&ring->fence_drv.last_seq) !=
	    ring->fence_drv.sync_seq) अणु
		DRM_INFO("ring %d was preempted\n", ring->idx);

		amdgpu_ib_preempt_mark_partial_job(ring);

		/* swap out the old fences */
		amdgpu_ib_preempt_fences_swap(ring, fences);

		amdgpu_fence_driver_क्रमce_completion(ring);

		/* resubmit unfinished jobs */
		amdgpu_ib_preempt_job_recovery(&ring->sched);

		/* रुको क्रम jobs finished */
		amdgpu_fence_रुको_empty(ring);

		/* संकेत the old fences */
		amdgpu_ib_preempt_संकेत_fences(fences, length);
	पूर्ण

failure:
	/* restart the scheduler */
	kthपढ़ो_unpark(ring->sched.thपढ़ो);

	up_पढ़ो(&adev->reset_sem);

	tपंचांग_bo_unlock_delayed_workqueue(&adev->mman.bdev, resched);

pro_end:
	kमुक्त(fences);

	वापस r;
पूर्ण

अटल पूर्णांक amdgpu_debugfs_sclk_set(व्योम *data, u64 val)
अणु
	पूर्णांक ret = 0;
	uपूर्णांक32_t max_freq, min_freq;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)data;

	अगर (amdgpu_sriov_vf(adev) && !amdgpu_sriov_is_pp_one_vf(adev))
		वापस -EINVAL;

	ret = pm_runसमय_get_sync(adev_to_drm(adev)->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);
		वापस ret;
	पूर्ण

	अगर (is_support_sw_smu(adev)) अणु
		ret = smu_get_dpm_freq_range(&adev->smu, SMU_SCLK, &min_freq, &max_freq);
		अगर (ret || val > max_freq || val < min_freq)
			वापस -EINVAL;
		ret = smu_set_soft_freq_range(&adev->smu, SMU_SCLK, (uपूर्णांक32_t)val, (uपूर्णांक32_t)val);
	पूर्ण अन्यथा अणु
		वापस 0;
	पूर्ण

	pm_runसमय_mark_last_busy(adev_to_drm(adev)->dev);
	pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);

	अगर (ret)
		वापस -EINVAL;

	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(fops_ib_preempt, शून्य,
			amdgpu_debugfs_ib_preempt, "%llu\n");

DEFINE_DEBUGFS_ATTRIBUTE(fops_sclk_set, शून्य,
			amdgpu_debugfs_sclk_set, "%llu\n");

पूर्णांक amdgpu_debugfs_init(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा dentry *root = adev_to_drm(adev)->primary->debugfs_root;
	काष्ठा dentry *ent;
	पूर्णांक r, i;



	ent = debugfs_create_file("amdgpu_preempt_ib", 0600, root, adev,
				  &fops_ib_preempt);
	अगर (!ent) अणु
		DRM_ERROR("unable to create amdgpu_preempt_ib debugsfs file\n");
		वापस -EIO;
	पूर्ण

	ent = debugfs_create_file("amdgpu_force_sclk", 0200, root, adev,
				  &fops_sclk_set);
	अगर (!ent) अणु
		DRM_ERROR("unable to create amdgpu_set_sclk debugsfs file\n");
		वापस -EIO;
	पूर्ण

	/* Register debugfs entries क्रम amdgpu_tपंचांग */
	amdgpu_tपंचांग_debugfs_init(adev);
	amdgpu_debugfs_pm_init(adev);
	amdgpu_debugfs_sa_init(adev);
	amdgpu_debugfs_fence_init(adev);
	amdgpu_debugfs_gem_init(adev);

	r = amdgpu_debugfs_regs_init(adev);
	अगर (r)
		DRM_ERROR("registering register debugfs failed (%d).\n", r);

	amdgpu_debugfs_firmware_init(adev);

#अगर defined(CONFIG_DRM_AMD_DC)
	अगर (amdgpu_device_has_dc_support(adev))
		dtn_debugfs_init(adev);
#पूर्ण_अगर

	क्रम (i = 0; i < AMDGPU_MAX_RINGS; ++i) अणु
		काष्ठा amdgpu_ring *ring = adev->rings[i];

		अगर (!ring)
			जारी;

		अगर (amdgpu_debugfs_ring_init(adev, ring)) अणु
			DRM_ERROR("Failed to register debugfs file for rings !\n");
		पूर्ण
	पूर्ण

	amdgpu_ras_debugfs_create_all(adev);
	amdgpu_debugfs_स्वतःdump_init(adev);
	amdgpu_rap_debugfs_init(adev);
	amdgpu_securedisplay_debugfs_init(adev);
	amdgpu_fw_attestation_debugfs_init(adev);

	debugfs_create_file("amdgpu_evict_vram", 0444, root, adev,
			    &amdgpu_evict_vram_fops);
	debugfs_create_file("amdgpu_evict_gtt", 0444, root, adev,
			    &amdgpu_evict_gtt_fops);
	debugfs_create_file("amdgpu_test_ib", 0444, root, adev,
			    &amdgpu_debugfs_test_ib_fops);
	debugfs_create_file("amdgpu_vm_info", 0444, root, adev,
			    &amdgpu_debugfs_vm_info_fops);

	adev->debugfs_vbios_blob.data = adev->bios;
	adev->debugfs_vbios_blob.size = adev->bios_size;
	debugfs_create_blob("amdgpu_vbios", 0444, root,
			    &adev->debugfs_vbios_blob);

	वापस 0;
पूर्ण

#अन्यथा
पूर्णांक amdgpu_debugfs_init(काष्ठा amdgpu_device *adev)
अणु
	वापस 0;
पूर्ण
पूर्णांक amdgpu_debugfs_regs_init(काष्ठा amdgpu_device *adev)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर
