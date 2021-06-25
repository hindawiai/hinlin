<शैली गुरु>
/*
 * AGPGART driver frontend
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

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mman.h>
#समावेश <linux/pci.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/agp_backend.h>
#समावेश <linux/agpgart.h>
#समावेश <linux/slab.h>
#समावेश <linux/mm.h>
#समावेश <linux/fs.h>
#समावेश <linux/sched.h>
#समावेश <linux/uaccess.h>
#समावेश "agp.h"

काष्ठा agp_front_data agp_fe;

काष्ठा agp_memory *agp_find_mem_by_key(पूर्णांक key)
अणु
	काष्ठा agp_memory *curr;

	अगर (agp_fe.current_controller == शून्य)
		वापस शून्य;

	curr = agp_fe.current_controller->pool;

	जबतक (curr != शून्य) अणु
		अगर (curr->key == key)
			अवरोध;
		curr = curr->next;
	पूर्ण

	DBG("key=%d -> mem=%p", key, curr);
	वापस curr;
पूर्ण

अटल व्योम agp_हटाओ_from_pool(काष्ठा agp_memory *temp)
अणु
	काष्ठा agp_memory *prev;
	काष्ठा agp_memory *next;

	/* Check to see अगर this is even in the memory pool */

	DBG("mem=%p", temp);
	अगर (agp_find_mem_by_key(temp->key) != शून्य) अणु
		next = temp->next;
		prev = temp->prev;

		अगर (prev != शून्य) अणु
			prev->next = next;
			अगर (next != शून्य)
				next->prev = prev;

		पूर्ण अन्यथा अणु
			/* This is the first item on the list */
			अगर (next != शून्य)
				next->prev = शून्य;

			agp_fe.current_controller->pool = next;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Routines क्रम managing each client's segment list -
 * These routines handle adding and removing segments
 * to each auth'ed client.
 */

अटल काष्ठा
agp_segment_priv *agp_find_seg_in_client(स्थिर काष्ठा agp_client *client,
						अचिन्हित दीर्घ offset,
					    पूर्णांक size, pgprot_t page_prot)
अणु
	काष्ठा agp_segment_priv *seg;
	पूर्णांक i;
	off_t pg_start;
	माप_प्रकार pg_count;

	pg_start = offset / 4096;
	pg_count = size / 4096;
	seg = *(client->segments);

	क्रम (i = 0; i < client->num_segments; i++) अणु
		अगर ((seg[i].pg_start == pg_start) &&
		    (seg[i].pg_count == pg_count) &&
		    (pgprot_val(seg[i].prot) == pgprot_val(page_prot))) अणु
			वापस seg + i;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम agp_हटाओ_seg_from_client(काष्ठा agp_client *client)
अणु
	DBG("client=%p", client);

	अगर (client->segments != शून्य) अणु
		अगर (*(client->segments) != शून्य) अणु
			DBG("Freeing %p from client %p", *(client->segments), client);
			kमुक्त(*(client->segments));
		पूर्ण
		DBG("Freeing %p from client %p", client->segments, client);
		kमुक्त(client->segments);
		client->segments = शून्य;
	पूर्ण
पूर्ण

अटल व्योम agp_add_seg_to_client(काष्ठा agp_client *client,
			       काष्ठा agp_segment_priv ** seg, पूर्णांक num_segments)
अणु
	काष्ठा agp_segment_priv **prev_seg;

	prev_seg = client->segments;

	अगर (prev_seg != शून्य)
		agp_हटाओ_seg_from_client(client);

	DBG("Adding seg %p (%d segments) to client %p", seg, num_segments, client);
	client->num_segments = num_segments;
	client->segments = seg;
पूर्ण

अटल pgprot_t agp_convert_mmap_flags(पूर्णांक prot)
अणु
	अचिन्हित दीर्घ prot_bits;

	prot_bits = calc_vm_prot_bits(prot, 0) | VM_SHARED;
	वापस vm_get_page_prot(prot_bits);
पूर्ण

पूर्णांक agp_create_segment(काष्ठा agp_client *client, काष्ठा agp_region *region)
अणु
	काष्ठा agp_segment_priv **ret_seg;
	काष्ठा agp_segment_priv *seg;
	काष्ठा agp_segment *user_seg;
	माप_प्रकार i;

	seg = kzalloc((माप(काष्ठा agp_segment_priv) * region->seg_count), GFP_KERNEL);
	अगर (seg == शून्य) अणु
		kमुक्त(region->seg_list);
		region->seg_list = शून्य;
		वापस -ENOMEM;
	पूर्ण
	user_seg = region->seg_list;

	क्रम (i = 0; i < region->seg_count; i++) अणु
		seg[i].pg_start = user_seg[i].pg_start;
		seg[i].pg_count = user_seg[i].pg_count;
		seg[i].prot = agp_convert_mmap_flags(user_seg[i].prot);
	पूर्ण
	kमुक्त(region->seg_list);
	region->seg_list = शून्य;

	ret_seg = kदो_स्मृति(माप(व्योम *), GFP_KERNEL);
	अगर (ret_seg == शून्य) अणु
		kमुक्त(seg);
		वापस -ENOMEM;
	पूर्ण
	*ret_seg = seg;
	agp_add_seg_to_client(client, ret_seg, region->seg_count);
	वापस 0;
पूर्ण

/* End - Routines क्रम managing each client's segment list */

/* This function must only be called when current_controller != शून्य */
अटल व्योम agp_insert_पूर्णांकo_pool(काष्ठा agp_memory * temp)
अणु
	काष्ठा agp_memory *prev;

	prev = agp_fe.current_controller->pool;

	अगर (prev != शून्य) अणु
		prev->prev = temp;
		temp->next = prev;
	पूर्ण
	agp_fe.current_controller->pool = temp;
पूर्ण


/* File निजी list routines */

काष्ठा agp_file_निजी *agp_find_निजी(pid_t pid)
अणु
	काष्ठा agp_file_निजी *curr;

	curr = agp_fe.file_priv_list;

	जबतक (curr != शून्य) अणु
		अगर (curr->my_pid == pid)
			वापस curr;
		curr = curr->next;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम agp_insert_file_निजी(काष्ठा agp_file_निजी * priv)
अणु
	काष्ठा agp_file_निजी *prev;

	prev = agp_fe.file_priv_list;

	अगर (prev != शून्य)
		prev->prev = priv;
	priv->next = prev;
	agp_fe.file_priv_list = priv;
पूर्ण

अटल व्योम agp_हटाओ_file_निजी(काष्ठा agp_file_निजी * priv)
अणु
	काष्ठा agp_file_निजी *next;
	काष्ठा agp_file_निजी *prev;

	next = priv->next;
	prev = priv->prev;

	अगर (prev != शून्य) अणु
		prev->next = next;

		अगर (next != शून्य)
			next->prev = prev;

	पूर्ण अन्यथा अणु
		अगर (next != शून्य)
			next->prev = शून्य;

		agp_fe.file_priv_list = next;
	पूर्ण
पूर्ण

/* End - File flag list routines */

/*
 * Wrappers क्रम agp_मुक्त_memory & agp_allocate_memory
 * These make sure that पूर्णांकernal lists are kept updated.
 */
व्योम agp_मुक्त_memory_wrap(काष्ठा agp_memory *memory)
अणु
	agp_हटाओ_from_pool(memory);
	agp_मुक्त_memory(memory);
पूर्ण

काष्ठा agp_memory *agp_allocate_memory_wrap(माप_प्रकार pg_count, u32 type)
अणु
	काष्ठा agp_memory *memory;

	memory = agp_allocate_memory(agp_bridge, pg_count, type);
	अगर (memory == शून्य)
		वापस शून्य;

	agp_insert_पूर्णांकo_pool(memory);
	वापस memory;
पूर्ण

/* Routines क्रम managing the list of controllers -
 * These routines manage the current controller, and the list of
 * controllers
 */

अटल काष्ठा agp_controller *agp_find_controller_by_pid(pid_t id)
अणु
	काष्ठा agp_controller *controller;

	controller = agp_fe.controllers;

	जबतक (controller != शून्य) अणु
		अगर (controller->pid == id)
			वापस controller;
		controller = controller->next;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा agp_controller *agp_create_controller(pid_t id)
अणु
	काष्ठा agp_controller *controller;

	controller = kzalloc(माप(काष्ठा agp_controller), GFP_KERNEL);
	अगर (controller == शून्य)
		वापस शून्य;

	controller->pid = id;
	वापस controller;
पूर्ण

अटल पूर्णांक agp_insert_controller(काष्ठा agp_controller *controller)
अणु
	काष्ठा agp_controller *prev_controller;

	prev_controller = agp_fe.controllers;
	controller->next = prev_controller;

	अगर (prev_controller != शून्य)
		prev_controller->prev = controller;

	agp_fe.controllers = controller;

	वापस 0;
पूर्ण

अटल व्योम agp_हटाओ_all_clients(काष्ठा agp_controller *controller)
अणु
	काष्ठा agp_client *client;
	काष्ठा agp_client *temp;

	client = controller->clients;

	जबतक (client) अणु
		काष्ठा agp_file_निजी *priv;

		temp = client;
		agp_हटाओ_seg_from_client(temp);
		priv = agp_find_निजी(temp->pid);

		अगर (priv != शून्य) अणु
			clear_bit(AGP_FF_IS_VALID, &priv->access_flags);
			clear_bit(AGP_FF_IS_CLIENT, &priv->access_flags);
		पूर्ण
		client = client->next;
		kमुक्त(temp);
	पूर्ण
पूर्ण

अटल व्योम agp_हटाओ_all_memory(काष्ठा agp_controller *controller)
अणु
	काष्ठा agp_memory *memory;
	काष्ठा agp_memory *temp;

	memory = controller->pool;

	जबतक (memory) अणु
		temp = memory;
		memory = memory->next;
		agp_मुक्त_memory_wrap(temp);
	पूर्ण
पूर्ण

अटल पूर्णांक agp_हटाओ_controller(काष्ठा agp_controller *controller)
अणु
	काष्ठा agp_controller *prev_controller;
	काष्ठा agp_controller *next_controller;

	prev_controller = controller->prev;
	next_controller = controller->next;

	अगर (prev_controller != शून्य) अणु
		prev_controller->next = next_controller;
		अगर (next_controller != शून्य)
			next_controller->prev = prev_controller;

	पूर्ण अन्यथा अणु
		अगर (next_controller != शून्य)
			next_controller->prev = शून्य;

		agp_fe.controllers = next_controller;
	पूर्ण

	agp_हटाओ_all_memory(controller);
	agp_हटाओ_all_clients(controller);

	अगर (agp_fe.current_controller == controller) अणु
		agp_fe.current_controller = शून्य;
		agp_fe.backend_acquired = false;
		agp_backend_release(agp_bridge);
	पूर्ण
	kमुक्त(controller);
	वापस 0;
पूर्ण

अटल व्योम agp_controller_make_current(काष्ठा agp_controller *controller)
अणु
	काष्ठा agp_client *clients;

	clients = controller->clients;

	जबतक (clients != शून्य) अणु
		काष्ठा agp_file_निजी *priv;

		priv = agp_find_निजी(clients->pid);

		अगर (priv != शून्य) अणु
			set_bit(AGP_FF_IS_VALID, &priv->access_flags);
			set_bit(AGP_FF_IS_CLIENT, &priv->access_flags);
		पूर्ण
		clients = clients->next;
	पूर्ण

	agp_fe.current_controller = controller;
पूर्ण

अटल व्योम agp_controller_release_current(काष्ठा agp_controller *controller,
				      काष्ठा agp_file_निजी *controller_priv)
अणु
	काष्ठा agp_client *clients;

	clear_bit(AGP_FF_IS_VALID, &controller_priv->access_flags);
	clients = controller->clients;

	जबतक (clients != शून्य) अणु
		काष्ठा agp_file_निजी *priv;

		priv = agp_find_निजी(clients->pid);

		अगर (priv != शून्य)
			clear_bit(AGP_FF_IS_VALID, &priv->access_flags);

		clients = clients->next;
	पूर्ण

	agp_fe.current_controller = शून्य;
	agp_fe.used_by_controller = false;
	agp_backend_release(agp_bridge);
पूर्ण

/*
 * Routines क्रम managing client lists -
 * These routines are क्रम managing the list of auth'ed clients.
 */

अटल काष्ठा agp_client
*agp_find_client_in_controller(काष्ठा agp_controller *controller, pid_t id)
अणु
	काष्ठा agp_client *client;

	अगर (controller == शून्य)
		वापस शून्य;

	client = controller->clients;

	जबतक (client != शून्य) अणु
		अगर (client->pid == id)
			वापस client;
		client = client->next;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा agp_controller *agp_find_controller_क्रम_client(pid_t id)
अणु
	काष्ठा agp_controller *controller;

	controller = agp_fe.controllers;

	जबतक (controller != शून्य) अणु
		अगर ((agp_find_client_in_controller(controller, id)) != शून्य)
			वापस controller;
		controller = controller->next;
	पूर्ण

	वापस शून्य;
पूर्ण

काष्ठा agp_client *agp_find_client_by_pid(pid_t id)
अणु
	काष्ठा agp_client *temp;

	अगर (agp_fe.current_controller == शून्य)
		वापस शून्य;

	temp = agp_find_client_in_controller(agp_fe.current_controller, id);
	वापस temp;
पूर्ण

अटल व्योम agp_insert_client(काष्ठा agp_client *client)
अणु
	काष्ठा agp_client *prev_client;

	prev_client = agp_fe.current_controller->clients;
	client->next = prev_client;

	अगर (prev_client != शून्य)
		prev_client->prev = client;

	agp_fe.current_controller->clients = client;
	agp_fe.current_controller->num_clients++;
पूर्ण

काष्ठा agp_client *agp_create_client(pid_t id)
अणु
	काष्ठा agp_client *new_client;

	new_client = kzalloc(माप(काष्ठा agp_client), GFP_KERNEL);
	अगर (new_client == शून्य)
		वापस शून्य;

	new_client->pid = id;
	agp_insert_client(new_client);
	वापस new_client;
पूर्ण

पूर्णांक agp_हटाओ_client(pid_t id)
अणु
	काष्ठा agp_client *client;
	काष्ठा agp_client *prev_client;
	काष्ठा agp_client *next_client;
	काष्ठा agp_controller *controller;

	controller = agp_find_controller_क्रम_client(id);
	अगर (controller == शून्य)
		वापस -EINVAL;

	client = agp_find_client_in_controller(controller, id);
	अगर (client == शून्य)
		वापस -EINVAL;

	prev_client = client->prev;
	next_client = client->next;

	अगर (prev_client != शून्य) अणु
		prev_client->next = next_client;
		अगर (next_client != शून्य)
			next_client->prev = prev_client;

	पूर्ण अन्यथा अणु
		अगर (next_client != शून्य)
			next_client->prev = शून्य;
		controller->clients = next_client;
	पूर्ण

	controller->num_clients--;
	agp_हटाओ_seg_from_client(client);
	kमुक्त(client);
	वापस 0;
पूर्ण

/* End - Routines क्रम managing client lists */

/* File Operations */

अटल पूर्णांक agp_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	अचिन्हित पूर्णांक size, current_size;
	अचिन्हित दीर्घ offset;
	काष्ठा agp_client *client;
	काष्ठा agp_file_निजी *priv = file->निजी_data;
	काष्ठा agp_kern_info kerninfo;

	mutex_lock(&(agp_fe.agp_mutex));

	अगर (agp_fe.backend_acquired != true)
		जाओ out_eperm;

	अगर (!(test_bit(AGP_FF_IS_VALID, &priv->access_flags)))
		जाओ out_eperm;

	agp_copy_info(agp_bridge, &kerninfo);
	size = vma->vm_end - vma->vm_start;
	current_size = kerninfo.aper_size;
	current_size = current_size * 0x100000;
	offset = vma->vm_pgoff << PAGE_SHIFT;
	DBG("%lx:%lx", offset, offset+size);

	अगर (test_bit(AGP_FF_IS_CLIENT, &priv->access_flags)) अणु
		अगर ((size + offset) > current_size)
			जाओ out_inval;

		client = agp_find_client_by_pid(current->pid);

		अगर (client == शून्य)
			जाओ out_eperm;

		अगर (!agp_find_seg_in_client(client, offset, size, vma->vm_page_prot))
			जाओ out_inval;

		DBG("client vm_ops=%p", kerninfo.vm_ops);
		अगर (kerninfo.vm_ops) अणु
			vma->vm_ops = kerninfo.vm_ops;
		पूर्ण अन्यथा अगर (io_remap_pfn_range(vma, vma->vm_start,
				(kerninfo.aper_base + offset) >> PAGE_SHIFT,
				size,
				pgprot_ग_लिखोcombine(vma->vm_page_prot))) अणु
			जाओ out_again;
		पूर्ण
		mutex_unlock(&(agp_fe.agp_mutex));
		वापस 0;
	पूर्ण

	अगर (test_bit(AGP_FF_IS_CONTROLLER, &priv->access_flags)) अणु
		अगर (size != current_size)
			जाओ out_inval;

		DBG("controller vm_ops=%p", kerninfo.vm_ops);
		अगर (kerninfo.vm_ops) अणु
			vma->vm_ops = kerninfo.vm_ops;
		पूर्ण अन्यथा अगर (io_remap_pfn_range(vma, vma->vm_start,
				kerninfo.aper_base >> PAGE_SHIFT,
				size,
				pgprot_ग_लिखोcombine(vma->vm_page_prot))) अणु
			जाओ out_again;
		पूर्ण
		mutex_unlock(&(agp_fe.agp_mutex));
		वापस 0;
	पूर्ण

out_eperm:
	mutex_unlock(&(agp_fe.agp_mutex));
	वापस -EPERM;

out_inval:
	mutex_unlock(&(agp_fe.agp_mutex));
	वापस -EINVAL;

out_again:
	mutex_unlock(&(agp_fe.agp_mutex));
	वापस -EAGAIN;
पूर्ण

अटल पूर्णांक agp_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा agp_file_निजी *priv = file->निजी_data;

	mutex_lock(&(agp_fe.agp_mutex));

	DBG("priv=%p", priv);

	अगर (test_bit(AGP_FF_IS_CONTROLLER, &priv->access_flags)) अणु
		काष्ठा agp_controller *controller;

		controller = agp_find_controller_by_pid(priv->my_pid);

		अगर (controller != शून्य) अणु
			अगर (controller == agp_fe.current_controller)
				agp_controller_release_current(controller, priv);
			agp_हटाओ_controller(controller);
			controller = शून्य;
		पूर्ण
	पूर्ण

	अगर (test_bit(AGP_FF_IS_CLIENT, &priv->access_flags))
		agp_हटाओ_client(priv->my_pid);

	agp_हटाओ_file_निजी(priv);
	kमुक्त(priv);
	file->निजी_data = शून्य;
	mutex_unlock(&(agp_fe.agp_mutex));
	वापस 0;
पूर्ण

अटल पूर्णांक agp_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	पूर्णांक minor = iminor(inode);
	काष्ठा agp_file_निजी *priv;
	काष्ठा agp_client *client;

	अगर (minor != AGPGART_MINOR)
		वापस -ENXIO;

	mutex_lock(&(agp_fe.agp_mutex));

	priv = kzalloc(माप(काष्ठा agp_file_निजी), GFP_KERNEL);
	अगर (priv == शून्य) अणु
		mutex_unlock(&(agp_fe.agp_mutex));
		वापस -ENOMEM;
	पूर्ण

	set_bit(AGP_FF_ALLOW_CLIENT, &priv->access_flags);
	priv->my_pid = current->pid;

	अगर (capable(CAP_SYS_RAWIO))
		/* Root priv, can be controller */
		set_bit(AGP_FF_ALLOW_CONTROLLER, &priv->access_flags);

	client = agp_find_client_by_pid(current->pid);

	अगर (client != शून्य) अणु
		set_bit(AGP_FF_IS_CLIENT, &priv->access_flags);
		set_bit(AGP_FF_IS_VALID, &priv->access_flags);
	पूर्ण
	file->निजी_data = (व्योम *) priv;
	agp_insert_file_निजी(priv);
	DBG("private=%p, client=%p", priv, client);

	mutex_unlock(&(agp_fe.agp_mutex));

	वापस 0;
पूर्ण

अटल पूर्णांक agpioc_info_wrap(काष्ठा agp_file_निजी *priv, व्योम __user *arg)
अणु
	काष्ठा agp_info userinfo;
	काष्ठा agp_kern_info kerninfo;

	agp_copy_info(agp_bridge, &kerninfo);

	स_रखो(&userinfo, 0, माप(userinfo));
	userinfo.version.major = kerninfo.version.major;
	userinfo.version.minor = kerninfo.version.minor;
	userinfo.bridge_id = kerninfo.device->venकरोr |
	    (kerninfo.device->device << 16);
	userinfo.agp_mode = kerninfo.mode;
	userinfo.aper_base = kerninfo.aper_base;
	userinfo.aper_size = kerninfo.aper_size;
	userinfo.pg_total = userinfo.pg_प्रणाली = kerninfo.max_memory;
	userinfo.pg_used = kerninfo.current_memory;

	अगर (copy_to_user(arg, &userinfo, माप(काष्ठा agp_info)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

पूर्णांक agpioc_acquire_wrap(काष्ठा agp_file_निजी *priv)
अणु
	काष्ठा agp_controller *controller;

	DBG("");

	अगर (!(test_bit(AGP_FF_ALLOW_CONTROLLER, &priv->access_flags)))
		वापस -EPERM;

	अगर (agp_fe.current_controller != शून्य)
		वापस -EBUSY;

	अगर (!agp_bridge)
		वापस -ENODEV;

        अगर (atomic_पढ़ो(&agp_bridge->agp_in_use))
                वापस -EBUSY;

	atomic_inc(&agp_bridge->agp_in_use);

	agp_fe.backend_acquired = true;

	controller = agp_find_controller_by_pid(priv->my_pid);

	अगर (controller != शून्य) अणु
		agp_controller_make_current(controller);
	पूर्ण अन्यथा अणु
		controller = agp_create_controller(priv->my_pid);

		अगर (controller == शून्य) अणु
			agp_fe.backend_acquired = false;
			agp_backend_release(agp_bridge);
			वापस -ENOMEM;
		पूर्ण
		agp_insert_controller(controller);
		agp_controller_make_current(controller);
	पूर्ण

	set_bit(AGP_FF_IS_CONTROLLER, &priv->access_flags);
	set_bit(AGP_FF_IS_VALID, &priv->access_flags);
	वापस 0;
पूर्ण

पूर्णांक agpioc_release_wrap(काष्ठा agp_file_निजी *priv)
अणु
	DBG("");
	agp_controller_release_current(agp_fe.current_controller, priv);
	वापस 0;
पूर्ण

पूर्णांक agpioc_setup_wrap(काष्ठा agp_file_निजी *priv, व्योम __user *arg)
अणु
	काष्ठा agp_setup mode;

	DBG("");
	अगर (copy_from_user(&mode, arg, माप(काष्ठा agp_setup)))
		वापस -EFAULT;

	agp_enable(agp_bridge, mode.agp_mode);
	वापस 0;
पूर्ण

अटल पूर्णांक agpioc_reserve_wrap(काष्ठा agp_file_निजी *priv, व्योम __user *arg)
अणु
	काष्ठा agp_region reserve;
	काष्ठा agp_client *client;
	काष्ठा agp_file_निजी *client_priv;

	DBG("");
	अगर (copy_from_user(&reserve, arg, माप(काष्ठा agp_region)))
		वापस -EFAULT;

	अगर ((अचिन्हित) reserve.seg_count >= ~0U/माप(काष्ठा agp_segment))
		वापस -EFAULT;

	client = agp_find_client_by_pid(reserve.pid);

	अगर (reserve.seg_count == 0) अणु
		/* हटाओ a client */
		client_priv = agp_find_निजी(reserve.pid);

		अगर (client_priv != शून्य) अणु
			set_bit(AGP_FF_IS_CLIENT, &client_priv->access_flags);
			set_bit(AGP_FF_IS_VALID, &client_priv->access_flags);
		पूर्ण
		अगर (client == शून्य) अणु
			/* client is alपढ़ोy हटाओd */
			वापस 0;
		पूर्ण
		वापस agp_हटाओ_client(reserve.pid);
	पूर्ण अन्यथा अणु
		काष्ठा agp_segment *segment;

		अगर (reserve.seg_count >= 16384)
			वापस -EINVAL;

		segment = kदो_स्मृति((माप(काष्ठा agp_segment) * reserve.seg_count),
				  GFP_KERNEL);

		अगर (segment == शून्य)
			वापस -ENOMEM;

		अगर (copy_from_user(segment, (व्योम __user *) reserve.seg_list,
				   माप(काष्ठा agp_segment) * reserve.seg_count)) अणु
			kमुक्त(segment);
			वापस -EFAULT;
		पूर्ण
		reserve.seg_list = segment;

		अगर (client == शून्य) अणु
			/* Create the client and add the segment */
			client = agp_create_client(reserve.pid);

			अगर (client == शून्य) अणु
				kमुक्त(segment);
				वापस -ENOMEM;
			पूर्ण
			client_priv = agp_find_निजी(reserve.pid);

			अगर (client_priv != शून्य) अणु
				set_bit(AGP_FF_IS_CLIENT, &client_priv->access_flags);
				set_bit(AGP_FF_IS_VALID, &client_priv->access_flags);
			पूर्ण
		पूर्ण
		वापस agp_create_segment(client, &reserve);
	पूर्ण
	/* Will never really happen */
	वापस -EINVAL;
पूर्ण

पूर्णांक agpioc_protect_wrap(काष्ठा agp_file_निजी *priv)
अणु
	DBG("");
	/* This function is not currently implemented */
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक agpioc_allocate_wrap(काष्ठा agp_file_निजी *priv, व्योम __user *arg)
अणु
	काष्ठा agp_memory *memory;
	काष्ठा agp_allocate alloc;

	DBG("");
	अगर (copy_from_user(&alloc, arg, माप(काष्ठा agp_allocate)))
		वापस -EFAULT;

	अगर (alloc.type >= AGP_USER_TYPES)
		वापस -EINVAL;

	memory = agp_allocate_memory_wrap(alloc.pg_count, alloc.type);

	अगर (memory == शून्य)
		वापस -ENOMEM;

	alloc.key = memory->key;
	alloc.physical = memory->physical;

	अगर (copy_to_user(arg, &alloc, माप(काष्ठा agp_allocate))) अणु
		agp_मुक्त_memory_wrap(memory);
		वापस -EFAULT;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक agpioc_deallocate_wrap(काष्ठा agp_file_निजी *priv, पूर्णांक arg)
अणु
	काष्ठा agp_memory *memory;

	DBG("");
	memory = agp_find_mem_by_key(arg);

	अगर (memory == शून्य)
		वापस -EINVAL;

	agp_मुक्त_memory_wrap(memory);
	वापस 0;
पूर्ण

अटल पूर्णांक agpioc_bind_wrap(काष्ठा agp_file_निजी *priv, व्योम __user *arg)
अणु
	काष्ठा agp_bind bind_info;
	काष्ठा agp_memory *memory;

	DBG("");
	अगर (copy_from_user(&bind_info, arg, माप(काष्ठा agp_bind)))
		वापस -EFAULT;

	memory = agp_find_mem_by_key(bind_info.key);

	अगर (memory == शून्य)
		वापस -EINVAL;

	वापस agp_bind_memory(memory, bind_info.pg_start);
पूर्ण

अटल पूर्णांक agpioc_unbind_wrap(काष्ठा agp_file_निजी *priv, व्योम __user *arg)
अणु
	काष्ठा agp_memory *memory;
	काष्ठा agp_unbind unbind;

	DBG("");
	अगर (copy_from_user(&unbind, arg, माप(काष्ठा agp_unbind)))
		वापस -EFAULT;

	memory = agp_find_mem_by_key(unbind.key);

	अगर (memory == शून्य)
		वापस -EINVAL;

	वापस agp_unbind_memory(memory);
पूर्ण

अटल दीर्घ agp_ioctl(काष्ठा file *file,
		     अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा agp_file_निजी *curr_priv = file->निजी_data;
	पूर्णांक ret_val = -ENOTTY;

	DBG("priv=%p, cmd=%x", curr_priv, cmd);
	mutex_lock(&(agp_fe.agp_mutex));

	अगर ((agp_fe.current_controller == शून्य) &&
	    (cmd != AGPIOC_ACQUIRE)) अणु
		ret_val = -EINVAL;
		जाओ ioctl_out;
	पूर्ण
	अगर ((agp_fe.backend_acquired != true) &&
	    (cmd != AGPIOC_ACQUIRE)) अणु
		ret_val = -EBUSY;
		जाओ ioctl_out;
	पूर्ण
	अगर (cmd != AGPIOC_ACQUIRE) अणु
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
	हाल AGPIOC_INFO:
		ret_val = agpioc_info_wrap(curr_priv, (व्योम __user *) arg);
		अवरोध;

	हाल AGPIOC_ACQUIRE:
		ret_val = agpioc_acquire_wrap(curr_priv);
		अवरोध;

	हाल AGPIOC_RELEASE:
		ret_val = agpioc_release_wrap(curr_priv);
		अवरोध;

	हाल AGPIOC_SETUP:
		ret_val = agpioc_setup_wrap(curr_priv, (व्योम __user *) arg);
		अवरोध;

	हाल AGPIOC_RESERVE:
		ret_val = agpioc_reserve_wrap(curr_priv, (व्योम __user *) arg);
		अवरोध;

	हाल AGPIOC_PROTECT:
		ret_val = agpioc_protect_wrap(curr_priv);
		अवरोध;

	हाल AGPIOC_ALLOCATE:
		ret_val = agpioc_allocate_wrap(curr_priv, (व्योम __user *) arg);
		अवरोध;

	हाल AGPIOC_DEALLOCATE:
		ret_val = agpioc_deallocate_wrap(curr_priv, (पूर्णांक) arg);
		अवरोध;

	हाल AGPIOC_BIND:
		ret_val = agpioc_bind_wrap(curr_priv, (व्योम __user *) arg);
		अवरोध;

	हाल AGPIOC_UNBIND:
		ret_val = agpioc_unbind_wrap(curr_priv, (व्योम __user *) arg);
		अवरोध;
	       
	हाल AGPIOC_CHIPSET_FLUSH:
		अवरोध;
	पूर्ण

ioctl_out:
	DBG("ioctl returns %d\n", ret_val);
	mutex_unlock(&(agp_fe.agp_mutex));
	वापस ret_val;
पूर्ण

अटल स्थिर काष्ठा file_operations agp_fops =
अणु
	.owner		= THIS_MODULE,
	.llseek		= no_llseek,
	.unlocked_ioctl	= agp_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl	= compat_agp_ioctl,
#पूर्ण_अगर
	.mmap		= agp_mmap,
	.खोलो		= agp_खोलो,
	.release	= agp_release,
पूर्ण;

अटल काष्ठा miscdevice agp_miscdev =
अणु
	.minor	= AGPGART_MINOR,
	.name	= "agpgart",
	.fops	= &agp_fops
पूर्ण;

पूर्णांक agp_frontend_initialize(व्योम)
अणु
	स_रखो(&agp_fe, 0, माप(काष्ठा agp_front_data));
	mutex_init(&(agp_fe.agp_mutex));

	अगर (misc_रेजिस्टर(&agp_miscdev)) अणु
		prपूर्णांकk(KERN_ERR PFX "unable to get minor: %d\n", AGPGART_MINOR);
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

व्योम agp_frontend_cleanup(व्योम)
अणु
	misc_deरेजिस्टर(&agp_miscdev);
पूर्ण
