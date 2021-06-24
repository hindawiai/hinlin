<शैली गुरु>
/*
 * AGPGART driver frontend compatibility ioctls
 * Copyright (C) 2004 Silicon Graphics, Inc.
 * Copyright (C) 2002-2003 Dave Jones
 * Copyright (C) 1999 Jeff Harपंचांगann
 * Copyright (C) 1999 Precision Insight, Inc.
 * Copyright (C) 1999 Xi Graphics, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * JEFF HARTMANN, OR ANY OTHER CONTRIBUTORS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
 * OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/fs.h>
#समावेश <linux/agpgart.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश "agp.h"
#समावेश "compat_ioctl.h"

अटल पूर्णांक compat_agpioc_info_wrap(काष्ठा agp_file_निजी *priv, व्योम __user *arg)
अणु
	काष्ठा agp_info32 userinfo;
	काष्ठा agp_kern_info kerninfo;

	agp_copy_info(agp_bridge, &kerninfo);

	userinfo.version.major = kerninfo.version.major;
	userinfo.version.minor = kerninfo.version.minor;
	userinfo.bridge_id = kerninfo.device->venकरोr |
	    (kerninfo.device->device << 16);
	userinfo.agp_mode = kerninfo.mode;
	userinfo.aper_base = (compat_दीर्घ_t)kerninfo.aper_base;
	userinfo.aper_size = kerninfo.aper_size;
	userinfo.pg_total = userinfo.pg_प्रणाली = kerninfo.max_memory;
	userinfo.pg_used = kerninfo.current_memory;

	अगर (copy_to_user(arg, &userinfo, माप(userinfo)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक compat_agpioc_reserve_wrap(काष्ठा agp_file_निजी *priv, व्योम __user *arg)
अणु
	काष्ठा agp_region32 ureserve;
	काष्ठा agp_region kreserve;
	काष्ठा agp_client *client;
	काष्ठा agp_file_निजी *client_priv;

	DBG("");
	अगर (copy_from_user(&ureserve, arg, माप(ureserve)))
		वापस -EFAULT;

	अगर ((अचिन्हित) ureserve.seg_count >= ~0U/माप(काष्ठा agp_segment32))
		वापस -EFAULT;

	kreserve.pid = ureserve.pid;
	kreserve.seg_count = ureserve.seg_count;

	client = agp_find_client_by_pid(kreserve.pid);

	अगर (kreserve.seg_count == 0) अणु
		/* हटाओ a client */
		client_priv = agp_find_निजी(kreserve.pid);

		अगर (client_priv != शून्य) अणु
			set_bit(AGP_FF_IS_CLIENT, &client_priv->access_flags);
			set_bit(AGP_FF_IS_VALID, &client_priv->access_flags);
		पूर्ण
		अगर (client == शून्य) अणु
			/* client is alपढ़ोy हटाओd */
			वापस 0;
		पूर्ण
		वापस agp_हटाओ_client(kreserve.pid);
	पूर्ण अन्यथा अणु
		काष्ठा agp_segment32 *usegment;
		काष्ठा agp_segment *ksegment;
		पूर्णांक seg;

		अगर (ureserve.seg_count >= 16384)
			वापस -EINVAL;

		usegment = kदो_स्मृति_array(ureserve.seg_count,
					 माप(*usegment),
					 GFP_KERNEL);
		अगर (!usegment)
			वापस -ENOMEM;

		ksegment = kदो_स्मृति_array(kreserve.seg_count,
					 माप(*ksegment),
					 GFP_KERNEL);
		अगर (!ksegment) अणु
			kमुक्त(usegment);
			वापस -ENOMEM;
		पूर्ण

		अगर (copy_from_user(usegment, (व्योम __user *) ureserve.seg_list,
				   माप(*usegment) * ureserve.seg_count)) अणु
			kमुक्त(usegment);
			kमुक्त(ksegment);
			वापस -EFAULT;
		पूर्ण

		क्रम (seg = 0; seg < ureserve.seg_count; seg++) अणु
			ksegment[seg].pg_start = usegment[seg].pg_start;
			ksegment[seg].pg_count = usegment[seg].pg_count;
			ksegment[seg].prot = usegment[seg].prot;
		पूर्ण

		kमुक्त(usegment);
		kreserve.seg_list = ksegment;

		अगर (client == शून्य) अणु
			/* Create the client and add the segment */
			client = agp_create_client(kreserve.pid);

			अगर (client == शून्य) अणु
				kमुक्त(ksegment);
				वापस -ENOMEM;
			पूर्ण
			client_priv = agp_find_निजी(kreserve.pid);

			अगर (client_priv != शून्य) अणु
				set_bit(AGP_FF_IS_CLIENT, &client_priv->access_flags);
				set_bit(AGP_FF_IS_VALID, &client_priv->access_flags);
			पूर्ण
		पूर्ण
		वापस agp_create_segment(client, &kreserve);
	पूर्ण
	/* Will never really happen */
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक compat_agpioc_allocate_wrap(काष्ठा agp_file_निजी *priv, व्योम __user *arg)
अणु
	काष्ठा agp_memory *memory;
	काष्ठा agp_allocate32 alloc;

	DBG("");
	अगर (copy_from_user(&alloc, arg, माप(alloc)))
		वापस -EFAULT;

	memory = agp_allocate_memory_wrap(alloc.pg_count, alloc.type);

	अगर (memory == शून्य)
		वापस -ENOMEM;

	alloc.key = memory->key;
	alloc.physical = memory->physical;

	अगर (copy_to_user(arg, &alloc, माप(alloc))) अणु
		agp_मुक्त_memory_wrap(memory);
		वापस -EFAULT;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक compat_agpioc_bind_wrap(काष्ठा agp_file_निजी *priv, व्योम __user *arg)
अणु
	काष्ठा agp_bind32 bind_info;
	काष्ठा agp_memory *memory;

	DBG("");
	अगर (copy_from_user(&bind_info, arg, माप(bind_info)))
		वापस -EFAULT;

	memory = agp_find_mem_by_key(bind_info.key);

	अगर (memory == शून्य)
		वापस -EINVAL;

	वापस agp_bind_memory(memory, bind_info.pg_start);
पूर्ण

अटल पूर्णांक compat_agpioc_unbind_wrap(काष्ठा agp_file_निजी *priv, व्योम __user *arg)
अणु
	काष्ठा agp_memory *memory;
	काष्ठा agp_unbind32 unbind;

	DBG("");
	अगर (copy_from_user(&unbind, arg, माप(unbind)))
		वापस -EFAULT;

	memory = agp_find_mem_by_key(unbind.key);

	अगर (memory == शून्य)
		वापस -EINVAL;

	वापस agp_unbind_memory(memory);
पूर्ण

दीर्घ compat_agp_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा agp_file_निजी *curr_priv = file->निजी_data;
	पूर्णांक ret_val = -ENOTTY;

	mutex_lock(&(agp_fe.agp_mutex));

	अगर ((agp_fe.current_controller == शून्य) &&
	    (cmd != AGPIOC_ACQUIRE32)) अणु
		ret_val = -EINVAL;
		जाओ ioctl_out;
	पूर्ण
	अगर ((agp_fe.backend_acquired != true) &&
	    (cmd != AGPIOC_ACQUIRE32)) अणु
		ret_val = -EBUSY;
		जाओ ioctl_out;
	पूर्ण
	अगर (cmd != AGPIOC_ACQUIRE32) अणु
		अगर (!(test_bit(AGP_FF_IS_CONTROLLER, &curr_priv->access_flags))) अणु
			ret_val = -EPERM;
			जाओ ioctl_out;
		पूर्ण
		/* Use the original pid of the controller,
		 * in हाल it's thपढ़ोed */

		अगर (agp_fe.current_controller->pid != curr_priv->my_pid) अणु
			ret_val = -EBUSY;
			जाओ ioctl_out;
		पूर्ण
	पूर्ण

	चयन (cmd) अणु
	हाल AGPIOC_INFO32:
		ret_val = compat_agpioc_info_wrap(curr_priv, (व्योम __user *) arg);
		अवरोध;

	हाल AGPIOC_ACQUIRE32:
		ret_val = agpioc_acquire_wrap(curr_priv);
		अवरोध;

	हाल AGPIOC_RELEASE32:
		ret_val = agpioc_release_wrap(curr_priv);
		अवरोध;

	हाल AGPIOC_SETUP32:
		ret_val = agpioc_setup_wrap(curr_priv, (व्योम __user *) arg);
		अवरोध;

	हाल AGPIOC_RESERVE32:
		ret_val = compat_agpioc_reserve_wrap(curr_priv, (व्योम __user *) arg);
		अवरोध;

	हाल AGPIOC_PROTECT32:
		ret_val = agpioc_protect_wrap(curr_priv);
		अवरोध;

	हाल AGPIOC_ALLOCATE32:
		ret_val = compat_agpioc_allocate_wrap(curr_priv, (व्योम __user *) arg);
		अवरोध;

	हाल AGPIOC_DEALLOCATE32:
		ret_val = agpioc_deallocate_wrap(curr_priv, (पूर्णांक) arg);
		अवरोध;

	हाल AGPIOC_BIND32:
		ret_val = compat_agpioc_bind_wrap(curr_priv, (व्योम __user *) arg);
		अवरोध;

	हाल AGPIOC_UNBIND32:
		ret_val = compat_agpioc_unbind_wrap(curr_priv, (व्योम __user *) arg);
		अवरोध;

	हाल AGPIOC_CHIPSET_FLUSH32:
		अवरोध;
	पूर्ण

ioctl_out:
	DBG("ioctl returns %d\n", ret_val);
	mutex_unlock(&(agp_fe.agp_mutex));
	वापस ret_val;
पूर्ण

