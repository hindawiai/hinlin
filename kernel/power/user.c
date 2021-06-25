<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/kernel/घातer/user.c
 *
 * This file provides the user space पूर्णांकerface क्रम software suspend/resume.
 *
 * Copyright (C) 2006 Rafael J. Wysocki <rjw@sisk.pl>
 */

#समावेश <linux/suspend.h>
#समावेश <linux/reboot.h>
#समावेश <linux/माला.स>
#समावेश <linux/device.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/mm.h>
#समावेश <linux/swap.h>
#समावेश <linux/swapops.h>
#समावेश <linux/pm.h>
#समावेश <linux/fs.h>
#समावेश <linux/compat.h>
#समावेश <linux/console.h>
#समावेश <linux/cpu.h>
#समावेश <linux/मुक्तzer.h>

#समावेश <linux/uaccess.h>

#समावेश "power.h"


अटल काष्ठा snapshot_data अणु
	काष्ठा snapshot_handle handle;
	पूर्णांक swap;
	पूर्णांक mode;
	bool frozen;
	bool पढ़ोy;
	bool platक्रमm_support;
	bool मुक्त_biपंचांगaps;
	dev_t dev;
पूर्ण snapshot_state;

पूर्णांक is_hibernate_resume_dev(dev_t dev)
अणु
	वापस hibernation_available() && snapshot_state.dev == dev;
पूर्ण

अटल पूर्णांक snapshot_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा snapshot_data *data;
	पूर्णांक error;

	अगर (!hibernation_available())
		वापस -EPERM;

	lock_प्रणाली_sleep();

	अगर (!hibernate_acquire()) अणु
		error = -EBUSY;
		जाओ Unlock;
	पूर्ण

	अगर ((filp->f_flags & O_ACCMODE) == O_RDWR) अणु
		hibernate_release();
		error = -ENOSYS;
		जाओ Unlock;
	पूर्ण
	nonseekable_खोलो(inode, filp);
	data = &snapshot_state;
	filp->निजी_data = data;
	स_रखो(&data->handle, 0, माप(काष्ठा snapshot_handle));
	अगर ((filp->f_flags & O_ACCMODE) == O_RDONLY) अणु
		/* Hibernating.  The image device should be accessible. */
		data->swap = swap_type_of(swsusp_resume_device, 0);
		data->mode = O_RDONLY;
		data->मुक्त_biपंचांगaps = false;
		error = pm_notअगरier_call_chain_robust(PM_HIBERNATION_PREPARE, PM_POST_HIBERNATION);
	पूर्ण अन्यथा अणु
		/*
		 * Resuming.  We may need to रुको क्रम the image device to
		 * appear.
		 */
		रुको_क्रम_device_probe();

		data->swap = -1;
		data->mode = O_WRONLY;
		error = pm_notअगरier_call_chain_robust(PM_RESTORE_PREPARE, PM_POST_RESTORE);
		अगर (!error) अणु
			error = create_basic_memory_biपंचांगaps();
			data->मुक्त_biपंचांगaps = !error;
		पूर्ण
	पूर्ण
	अगर (error)
		hibernate_release();

	data->frozen = false;
	data->पढ़ोy = false;
	data->platक्रमm_support = false;
	data->dev = 0;

 Unlock:
	unlock_प्रणाली_sleep();

	वापस error;
पूर्ण

अटल पूर्णांक snapshot_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा snapshot_data *data;

	lock_प्रणाली_sleep();

	swsusp_मुक्त();
	data = filp->निजी_data;
	data->dev = 0;
	मुक्त_all_swap_pages(data->swap);
	अगर (data->frozen) अणु
		pm_restore_gfp_mask();
		मुक्त_basic_memory_biपंचांगaps();
		thaw_processes();
	पूर्ण अन्यथा अगर (data->मुक्त_biपंचांगaps) अणु
		मुक्त_basic_memory_biपंचांगaps();
	पूर्ण
	pm_notअगरier_call_chain(data->mode == O_RDONLY ?
			PM_POST_HIBERNATION : PM_POST_RESTORE);
	hibernate_release();

	unlock_प्रणाली_sleep();

	वापस 0;
पूर्ण

अटल sमाप_प्रकार snapshot_पढ़ो(काष्ठा file *filp, अक्षर __user *buf,
                             माप_प्रकार count, loff_t *offp)
अणु
	काष्ठा snapshot_data *data;
	sमाप_प्रकार res;
	loff_t pg_offp = *offp & ~PAGE_MASK;

	lock_प्रणाली_sleep();

	data = filp->निजी_data;
	अगर (!data->पढ़ोy) अणु
		res = -ENODATA;
		जाओ Unlock;
	पूर्ण
	अगर (!pg_offp) अणु /* on page boundary? */
		res = snapshot_पढ़ो_next(&data->handle);
		अगर (res <= 0)
			जाओ Unlock;
	पूर्ण अन्यथा अणु
		res = PAGE_SIZE - pg_offp;
	पूर्ण

	res = simple_पढ़ो_from_buffer(buf, count, &pg_offp,
			data_of(data->handle), res);
	अगर (res > 0)
		*offp += res;

 Unlock:
	unlock_प्रणाली_sleep();

	वापस res;
पूर्ण

अटल sमाप_प्रकार snapshot_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *buf,
                              माप_प्रकार count, loff_t *offp)
अणु
	काष्ठा snapshot_data *data;
	sमाप_प्रकार res;
	loff_t pg_offp = *offp & ~PAGE_MASK;

	lock_प्रणाली_sleep();

	data = filp->निजी_data;

	अगर (!pg_offp) अणु
		res = snapshot_ग_लिखो_next(&data->handle);
		अगर (res <= 0)
			जाओ unlock;
	पूर्ण अन्यथा अणु
		res = PAGE_SIZE - pg_offp;
	पूर्ण

	अगर (!data_of(data->handle)) अणु
		res = -EINVAL;
		जाओ unlock;
	पूर्ण

	res = simple_ग_लिखो_to_buffer(data_of(data->handle), res, &pg_offp,
			buf, count);
	अगर (res > 0)
		*offp += res;
unlock:
	unlock_प्रणाली_sleep();

	वापस res;
पूर्ण

काष्ठा compat_resume_swap_area अणु
	compat_loff_t offset;
	u32 dev;
पूर्ण __packed;

अटल पूर्णांक snapshot_set_swap_area(काष्ठा snapshot_data *data,
		व्योम __user *argp)
अणु
	sector_t offset;
	dev_t swdev;

	अगर (swsusp_swap_in_use())
		वापस -EPERM;

	अगर (in_compat_syscall()) अणु
		काष्ठा compat_resume_swap_area swap_area;

		अगर (copy_from_user(&swap_area, argp, माप(swap_area)))
			वापस -EFAULT;
		swdev = new_decode_dev(swap_area.dev);
		offset = swap_area.offset;
	पूर्ण अन्यथा अणु
		काष्ठा resume_swap_area swap_area;

		अगर (copy_from_user(&swap_area, argp, माप(swap_area)))
			वापस -EFAULT;
		swdev = new_decode_dev(swap_area.dev);
		offset = swap_area.offset;
	पूर्ण

	/*
	 * User space encodes device types as two-byte values,
	 * so we need to recode them
	 */
	data->swap = swap_type_of(swdev, offset);
	अगर (data->swap < 0)
		वापस swdev ? -ENODEV : -EINVAL;
	data->dev = swdev;
	वापस 0;
पूर्ण

अटल दीर्घ snapshot_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd,
							अचिन्हित दीर्घ arg)
अणु
	पूर्णांक error = 0;
	काष्ठा snapshot_data *data;
	loff_t size;
	sector_t offset;

	अगर (_IOC_TYPE(cmd) != SNAPSHOT_IOC_MAGIC)
		वापस -ENOTTY;
	अगर (_IOC_NR(cmd) > SNAPSHOT_IOC_MAXNR)
		वापस -ENOTTY;
	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	अगर (!mutex_trylock(&प्रणाली_transition_mutex))
		वापस -EBUSY;

	lock_device_hotplug();
	data = filp->निजी_data;

	चयन (cmd) अणु

	हाल SNAPSHOT_FREEZE:
		अगर (data->frozen)
			अवरोध;

		ksys_sync_helper();

		error = मुक्तze_processes();
		अगर (error)
			अवरोध;

		error = create_basic_memory_biपंचांगaps();
		अगर (error)
			thaw_processes();
		अन्यथा
			data->frozen = true;

		अवरोध;

	हाल SNAPSHOT_UNFREEZE:
		अगर (!data->frozen || data->पढ़ोy)
			अवरोध;
		pm_restore_gfp_mask();
		मुक्त_basic_memory_biपंचांगaps();
		data->मुक्त_biपंचांगaps = false;
		thaw_processes();
		data->frozen = false;
		अवरोध;

	हाल SNAPSHOT_CREATE_IMAGE:
		अगर (data->mode != O_RDONLY || !data->frozen  || data->पढ़ोy) अणु
			error = -EPERM;
			अवरोध;
		पूर्ण
		pm_restore_gfp_mask();
		error = hibernation_snapshot(data->platक्रमm_support);
		अगर (!error) अणु
			error = put_user(in_suspend, (पूर्णांक __user *)arg);
			data->पढ़ोy = !मुक्तzer_test_करोne && !error;
			मुक्तzer_test_करोne = false;
		पूर्ण
		अवरोध;

	हाल SNAPSHOT_ATOMIC_RESTORE:
		snapshot_ग_लिखो_finalize(&data->handle);
		अगर (data->mode != O_WRONLY || !data->frozen ||
		    !snapshot_image_loaded(&data->handle)) अणु
			error = -EPERM;
			अवरोध;
		पूर्ण
		error = hibernation_restore(data->platक्रमm_support);
		अवरोध;

	हाल SNAPSHOT_FREE:
		swsusp_मुक्त();
		स_रखो(&data->handle, 0, माप(काष्ठा snapshot_handle));
		data->पढ़ोy = false;
		/*
		 * It is necessary to thaw kernel thपढ़ोs here, because
		 * SNAPSHOT_CREATE_IMAGE may be invoked directly after
		 * SNAPSHOT_FREE.  In that हाल, अगर kernel thपढ़ोs were not
		 * thawed, the pपुनः_स्मृतिation of memory carried out by
		 * hibernation_snapshot() might run पूर्णांकo problems (i.e. it
		 * might fail or even deadlock).
		 */
		thaw_kernel_thपढ़ोs();
		अवरोध;

	हाल SNAPSHOT_PREF_IMAGE_SIZE:
		image_size = arg;
		अवरोध;

	हाल SNAPSHOT_GET_IMAGE_SIZE:
		अगर (!data->पढ़ोy) अणु
			error = -ENODATA;
			अवरोध;
		पूर्ण
		size = snapshot_get_image_size();
		size <<= PAGE_SHIFT;
		error = put_user(size, (loff_t __user *)arg);
		अवरोध;

	हाल SNAPSHOT_AVAIL_SWAP_SIZE:
		size = count_swap_pages(data->swap, 1);
		size <<= PAGE_SHIFT;
		error = put_user(size, (loff_t __user *)arg);
		अवरोध;

	हाल SNAPSHOT_ALLOC_SWAP_PAGE:
		अगर (data->swap < 0 || data->swap >= MAX_SWAPखाताS) अणु
			error = -ENODEV;
			अवरोध;
		पूर्ण
		offset = alloc_swapdev_block(data->swap);
		अगर (offset) अणु
			offset <<= PAGE_SHIFT;
			error = put_user(offset, (loff_t __user *)arg);
		पूर्ण अन्यथा अणु
			error = -ENOSPC;
		पूर्ण
		अवरोध;

	हाल SNAPSHOT_FREE_SWAP_PAGES:
		अगर (data->swap < 0 || data->swap >= MAX_SWAPखाताS) अणु
			error = -ENODEV;
			अवरोध;
		पूर्ण
		मुक्त_all_swap_pages(data->swap);
		अवरोध;

	हाल SNAPSHOT_S2RAM:
		अगर (!data->frozen) अणु
			error = -EPERM;
			अवरोध;
		पूर्ण
		/*
		 * Tasks are frozen and the notअगरiers have been called with
		 * PM_HIBERNATION_PREPARE
		 */
		error = suspend_devices_and_enter(PM_SUSPEND_MEM);
		data->पढ़ोy = false;
		अवरोध;

	हाल SNAPSHOT_PLATFORM_SUPPORT:
		data->platक्रमm_support = !!arg;
		अवरोध;

	हाल SNAPSHOT_POWER_OFF:
		अगर (data->platक्रमm_support)
			error = hibernation_platक्रमm_enter();
		अवरोध;

	हाल SNAPSHOT_SET_SWAP_AREA:
		error = snapshot_set_swap_area(data, (व्योम __user *)arg);
		अवरोध;

	शेष:
		error = -ENOTTY;

	पूर्ण

	unlock_device_hotplug();
	mutex_unlock(&प्रणाली_transition_mutex);

	वापस error;
पूर्ण

#अगर_घोषित CONFIG_COMPAT
अटल दीर्घ
snapshot_compat_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	BUILD_BUG_ON(माप(loff_t) != माप(compat_loff_t));

	चयन (cmd) अणु
	हाल SNAPSHOT_GET_IMAGE_SIZE:
	हाल SNAPSHOT_AVAIL_SWAP_SIZE:
	हाल SNAPSHOT_ALLOC_SWAP_PAGE:
	हाल SNAPSHOT_CREATE_IMAGE:
	हाल SNAPSHOT_SET_SWAP_AREA:
		वापस snapshot_ioctl(file, cmd,
				      (अचिन्हित दीर्घ) compat_ptr(arg));
	शेष:
		वापस snapshot_ioctl(file, cmd, arg);
	पूर्ण
पूर्ण
#पूर्ण_अगर /* CONFIG_COMPAT */

अटल स्थिर काष्ठा file_operations snapshot_fops = अणु
	.खोलो = snapshot_खोलो,
	.release = snapshot_release,
	.पढ़ो = snapshot_पढ़ो,
	.ग_लिखो = snapshot_ग_लिखो,
	.llseek = no_llseek,
	.unlocked_ioctl = snapshot_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl = snapshot_compat_ioctl,
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा miscdevice snapshot_device = अणु
	.minor = SNAPSHOT_MINOR,
	.name = "snapshot",
	.fops = &snapshot_fops,
पूर्ण;

अटल पूर्णांक __init snapshot_device_init(व्योम)
अणु
	वापस misc_रेजिस्टर(&snapshot_device);
पूर्ण;

device_initcall(snapshot_device_init);
