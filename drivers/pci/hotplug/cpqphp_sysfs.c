<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Compaq Hot Plug Controller Driver
 *
 * Copyright (C) 1995,2001 Compaq Computer Corporation
 * Copyright (C) 2001,2003 Greg Kroah-Harपंचांगan (greg@kroah.com)
 * Copyright (C) 2001 IBM Corp.
 *
 * All rights reserved.
 *
 * Send feedback to <greg@kroah.com>
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci_hotplug.h>
#समावेश <linux/mutex.h>
#समावेश <linux/debugfs.h>
#समावेश "cpqphp.h"

अटल DEFINE_MUTEX(cpqphp_mutex);
अटल पूर्णांक show_ctrl(काष्ठा controller *ctrl, अक्षर *buf)
अणु
	अक्षर *out = buf;
	पूर्णांक index;
	काष्ठा pci_resource *res;

	out += प्र_लिखो(buf, "Free resources: memory\n");
	index = 11;
	res = ctrl->mem_head;
	जबतक (res && index--) अणु
		out += प्र_लिखो(out, "start = %8.8x, length = %8.8x\n", res->base, res->length);
		res = res->next;
	पूर्ण
	out += प्र_लिखो(out, "Free resources: prefetchable memory\n");
	index = 11;
	res = ctrl->p_mem_head;
	जबतक (res && index--) अणु
		out += प्र_लिखो(out, "start = %8.8x, length = %8.8x\n", res->base, res->length);
		res = res->next;
	पूर्ण
	out += प्र_लिखो(out, "Free resources: IO\n");
	index = 11;
	res = ctrl->io_head;
	जबतक (res && index--) अणु
		out += प्र_लिखो(out, "start = %8.8x, length = %8.8x\n", res->base, res->length);
		res = res->next;
	पूर्ण
	out += प्र_लिखो(out, "Free resources: bus numbers\n");
	index = 11;
	res = ctrl->bus_head;
	जबतक (res && index--) अणु
		out += प्र_लिखो(out, "start = %8.8x, length = %8.8x\n", res->base, res->length);
		res = res->next;
	पूर्ण

	वापस out - buf;
पूर्ण

अटल पूर्णांक show_dev(काष्ठा controller *ctrl, अक्षर *buf)
अणु
	अक्षर *out = buf;
	पूर्णांक index;
	काष्ठा pci_resource *res;
	काष्ठा pci_func *new_slot;
	काष्ठा slot *slot;

	slot = ctrl->slot;

	जबतक (slot) अणु
		new_slot = cpqhp_slot_find(slot->bus, slot->device, 0);
		अगर (!new_slot)
			अवरोध;
		out += प्र_लिखो(out, "assigned resources: memory\n");
		index = 11;
		res = new_slot->mem_head;
		जबतक (res && index--) अणु
			out += प्र_लिखो(out, "start = %8.8x, length = %8.8x\n", res->base, res->length);
			res = res->next;
		पूर्ण
		out += प्र_लिखो(out, "assigned resources: prefetchable memory\n");
		index = 11;
		res = new_slot->p_mem_head;
		जबतक (res && index--) अणु
			out += प्र_लिखो(out, "start = %8.8x, length = %8.8x\n", res->base, res->length);
			res = res->next;
		पूर्ण
		out += प्र_लिखो(out, "assigned resources: IO\n");
		index = 11;
		res = new_slot->io_head;
		जबतक (res && index--) अणु
			out += प्र_लिखो(out, "start = %8.8x, length = %8.8x\n", res->base, res->length);
			res = res->next;
		पूर्ण
		out += प्र_लिखो(out, "assigned resources: bus numbers\n");
		index = 11;
		res = new_slot->bus_head;
		जबतक (res && index--) अणु
			out += प्र_लिखो(out, "start = %8.8x, length = %8.8x\n", res->base, res->length);
			res = res->next;
		पूर्ण
		slot = slot->next;
	पूर्ण

	वापस out - buf;
पूर्ण

अटल पूर्णांक spew_debug_info(काष्ठा controller *ctrl, अक्षर *data, पूर्णांक size)
अणु
	पूर्णांक used;

	used = size - show_ctrl(ctrl, data);
	used = (size - used) - show_dev(ctrl, &data[used]);
	वापस used;
पूर्ण

काष्ठा ctrl_dbg अणु
	पूर्णांक size;
	अक्षर *data;
	काष्ठा controller *ctrl;
पूर्ण;

#घोषणा MAX_OUTPUT	(4*PAGE_SIZE)

अटल पूर्णांक खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा controller *ctrl = inode->i_निजी;
	काष्ठा ctrl_dbg *dbg;
	पूर्णांक retval = -ENOMEM;

	mutex_lock(&cpqphp_mutex);
	dbg = kदो_स्मृति(माप(*dbg), GFP_KERNEL);
	अगर (!dbg)
		जाओ निकास;
	dbg->data = kदो_स्मृति(MAX_OUTPUT, GFP_KERNEL);
	अगर (!dbg->data) अणु
		kमुक्त(dbg);
		जाओ निकास;
	पूर्ण
	dbg->size = spew_debug_info(ctrl, dbg->data, MAX_OUTPUT);
	file->निजी_data = dbg;
	retval = 0;
निकास:
	mutex_unlock(&cpqphp_mutex);
	वापस retval;
पूर्ण

अटल loff_t lseek(काष्ठा file *file, loff_t off, पूर्णांक whence)
अणु
	काष्ठा ctrl_dbg *dbg = file->निजी_data;
	वापस fixed_size_llseek(file, off, whence, dbg->size);
पूर्ण

अटल sमाप_प्रकार पढ़ो(काष्ठा file *file, अक्षर __user *buf,
		    माप_प्रकार nbytes, loff_t *ppos)
अणु
	काष्ठा ctrl_dbg *dbg = file->निजी_data;
	वापस simple_पढ़ो_from_buffer(buf, nbytes, ppos, dbg->data, dbg->size);
पूर्ण

अटल पूर्णांक release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा ctrl_dbg *dbg = file->निजी_data;

	kमुक्त(dbg->data);
	kमुक्त(dbg);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations debug_ops = अणु
	.owner = THIS_MODULE,
	.खोलो = खोलो,
	.llseek = lseek,
	.पढ़ो = पढ़ो,
	.release = release,
पूर्ण;

अटल काष्ठा dentry *root;

व्योम cpqhp_initialize_debugfs(व्योम)
अणु
	अगर (!root)
		root = debugfs_create_dir("cpqhp", शून्य);
पूर्ण

व्योम cpqhp_shutकरोwn_debugfs(व्योम)
अणु
	debugfs_हटाओ(root);
पूर्ण

व्योम cpqhp_create_debugfs_files(काष्ठा controller *ctrl)
अणु
	ctrl->dentry = debugfs_create_file(dev_name(&ctrl->pci_dev->dev),
					   S_IRUGO, root, ctrl, &debug_ops);
पूर्ण

व्योम cpqhp_हटाओ_debugfs_files(काष्ठा controller *ctrl)
अणु
	debugfs_हटाओ(ctrl->dentry);
	ctrl->dentry = शून्य;
पूर्ण

