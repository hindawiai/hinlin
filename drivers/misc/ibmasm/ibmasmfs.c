<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * IBM ASM Service Processor Device Driver
 *
 * Copyright (C) IBM Corporation, 2004
 *
 * Author: Max Asbथघck <amax@us.ibm.com>
 */

/*
 * Parts of this code are based on an article by Jonathan Corbet
 * that appeared in Linux Weekly News.
 */


/*
 * The IBMASM file भव fileप्रणाली. It creates the following hierarchy
 * dynamically when mounted from user space:
 *
 *    /ibmयंत्र
 *    |-- 0
 *    |   |-- command
 *    |   |-- event
 *    |   |-- reverse_heartbeat
 *    |   `-- remote_video
 *    |       |-- depth
 *    |       |-- height
 *    |       `-- width
 *    .
 *    .
 *    .
 *    `-- n
 *        |-- command
 *        |-- event
 *        |-- reverse_heartbeat
 *        `-- remote_video
 *            |-- depth
 *            |-- height
 *            `-- width
 *
 * For each service processor the following files are created:
 *
 * command: execute करोt commands
 *	ग_लिखो: execute a करोt command on the service processor
 *	पढ़ो: वापस the result of a previously executed करोt command
 *
 * events: listen क्रम service processor events
 *	पढ़ो: sleep (पूर्णांकerruptible) until an event occurs
 *      ग_लिखो: wakeup sleeping event listener
 *
 * reverse_heartbeat: send a heartbeat to the service processor
 *	पढ़ो: sleep (पूर्णांकerruptible) until the reverse heartbeat fails
 *      ग_लिखो: wakeup sleeping heartbeat listener
 *
 * remote_video/width
 * remote_video/height
 * remote_video/width: control remote display settings
 *	ग_लिखो: set value
 *	पढ़ो: पढ़ो value
 */

#समावेश <linux/fs.h>
#समावेश <linux/fs_context.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/पन.स>
#समावेश "ibmasm.h"
#समावेश "remote.h"
#समावेश "dot_command.h"

#घोषणा IBMASMFS_MAGIC 0x66726f67

अटल LIST_HEAD(service_processors);

अटल काष्ठा inode *ibmयंत्रfs_make_inode(काष्ठा super_block *sb, पूर्णांक mode);
अटल व्योम ibmयंत्रfs_create_files (काष्ठा super_block *sb);
अटल पूर्णांक ibmयंत्रfs_fill_super(काष्ठा super_block *sb, काष्ठा fs_context *fc);

अटल पूर्णांक ibmयंत्रfs_get_tree(काष्ठा fs_context *fc)
अणु
	वापस get_tree_single(fc, ibmयंत्रfs_fill_super);
पूर्ण

अटल स्थिर काष्ठा fs_context_operations ibmयंत्रfs_context_ops = अणु
	.get_tree	= ibmयंत्रfs_get_tree,
पूर्ण;

अटल पूर्णांक ibmयंत्रfs_init_fs_context(काष्ठा fs_context *fc)
अणु
	fc->ops = &ibmयंत्रfs_context_ops;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा super_operations ibmयंत्रfs_s_ops = अणु
	.statfs		= simple_statfs,
	.drop_inode	= generic_delete_inode,
पूर्ण;

अटल स्थिर काष्ठा file_operations *ibmयंत्रfs_dir_ops = &simple_dir_operations;

अटल काष्ठा file_प्रणाली_type ibmयंत्रfs_type = अणु
	.owner          = THIS_MODULE,
	.name           = "ibmasmfs",
	.init_fs_context = ibmयंत्रfs_init_fs_context,
	.समाप्त_sb        = समाप्त_litter_super,
पूर्ण;
MODULE_ALIAS_FS("ibmasmfs");

अटल पूर्णांक ibmयंत्रfs_fill_super(काष्ठा super_block *sb, काष्ठा fs_context *fc)
अणु
	काष्ठा inode *root;

	sb->s_blocksize = PAGE_SIZE;
	sb->s_blocksize_bits = PAGE_SHIFT;
	sb->s_magic = IBMASMFS_MAGIC;
	sb->s_op = &ibmयंत्रfs_s_ops;
	sb->s_समय_gran = 1;

	root = ibmयंत्रfs_make_inode (sb, S_IFसूची | 0500);
	अगर (!root)
		वापस -ENOMEM;

	root->i_op = &simple_dir_inode_operations;
	root->i_fop = ibmयंत्रfs_dir_ops;

	sb->s_root = d_make_root(root);
	अगर (!sb->s_root)
		वापस -ENOMEM;

	ibmयंत्रfs_create_files(sb);
	वापस 0;
पूर्ण

अटल काष्ठा inode *ibmयंत्रfs_make_inode(काष्ठा super_block *sb, पूर्णांक mode)
अणु
	काष्ठा inode *ret = new_inode(sb);

	अगर (ret) अणु
		ret->i_ino = get_next_ino();
		ret->i_mode = mode;
		ret->i_aसमय = ret->i_mसमय = ret->i_स_समय = current_समय(ret);
	पूर्ण
	वापस ret;
पूर्ण

अटल काष्ठा dentry *ibmयंत्रfs_create_file(काष्ठा dentry *parent,
			स्थिर अक्षर *name,
			स्थिर काष्ठा file_operations *fops,
			व्योम *data,
			पूर्णांक mode)
अणु
	काष्ठा dentry *dentry;
	काष्ठा inode *inode;

	dentry = d_alloc_name(parent, name);
	अगर (!dentry)
		वापस शून्य;

	inode = ibmयंत्रfs_make_inode(parent->d_sb, S_IFREG | mode);
	अगर (!inode) अणु
		dput(dentry);
		वापस शून्य;
	पूर्ण

	inode->i_fop = fops;
	inode->i_निजी = data;

	d_add(dentry, inode);
	वापस dentry;
पूर्ण

अटल काष्ठा dentry *ibmयंत्रfs_create_dir(काष्ठा dentry *parent,
				स्थिर अक्षर *name)
अणु
	काष्ठा dentry *dentry;
	काष्ठा inode *inode;

	dentry = d_alloc_name(parent, name);
	अगर (!dentry)
		वापस शून्य;

	inode = ibmयंत्रfs_make_inode(parent->d_sb, S_IFसूची | 0500);
	अगर (!inode) अणु
		dput(dentry);
		वापस शून्य;
	पूर्ण

	inode->i_op = &simple_dir_inode_operations;
	inode->i_fop = ibmयंत्रfs_dir_ops;

	d_add(dentry, inode);
	वापस dentry;
पूर्ण

पूर्णांक ibmयंत्रfs_रेजिस्टर(व्योम)
अणु
	वापस रेजिस्टर_fileप्रणाली(&ibmयंत्रfs_type);
पूर्ण

व्योम ibmयंत्रfs_unरेजिस्टर(व्योम)
अणु
	unरेजिस्टर_fileप्रणाली(&ibmयंत्रfs_type);
पूर्ण

व्योम ibmयंत्रfs_add_sp(काष्ठा service_processor *sp)
अणु
	list_add(&sp->node, &service_processors);
पूर्ण

/* काष्ठा to save state between command file operations */
काष्ठा ibmयंत्रfs_command_data अणु
	काष्ठा service_processor	*sp;
	काष्ठा command			*command;
पूर्ण;

/* काष्ठा to save state between event file operations */
काष्ठा ibmयंत्रfs_event_data अणु
	काष्ठा service_processor	*sp;
	काष्ठा event_पढ़ोer		पढ़ोer;
	पूर्णांक				active;
पूर्ण;

/* काष्ठा to save state between reverse heartbeat file operations */
काष्ठा ibmयंत्रfs_heartbeat_data अणु
	काष्ठा service_processor	*sp;
	काष्ठा reverse_heartbeat	heartbeat;
	पूर्णांक				active;
पूर्ण;

अटल पूर्णांक command_file_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा ibmयंत्रfs_command_data *command_data;

	अगर (!inode->i_निजी)
		वापस -ENODEV;

	command_data = kदो_स्मृति(माप(काष्ठा ibmयंत्रfs_command_data), GFP_KERNEL);
	अगर (!command_data)
		वापस -ENOMEM;

	command_data->command = शून्य;
	command_data->sp = inode->i_निजी;
	file->निजी_data = command_data;
	वापस 0;
पूर्ण

अटल पूर्णांक command_file_बंद(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा ibmयंत्रfs_command_data *command_data = file->निजी_data;

	अगर (command_data->command)
		command_put(command_data->command);

	kमुक्त(command_data);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार command_file_पढ़ो(काष्ठा file *file, अक्षर __user *buf, माप_प्रकार count, loff_t *offset)
अणु
	काष्ठा ibmयंत्रfs_command_data *command_data = file->निजी_data;
	काष्ठा command *cmd;
	पूर्णांक len;
	अचिन्हित दीर्घ flags;

	अगर (*offset < 0)
		वापस -EINVAL;
	अगर (count == 0 || count > IBMASM_CMD_MAX_BUFFER_SIZE)
		वापस 0;
	अगर (*offset != 0)
		वापस 0;

	spin_lock_irqsave(&command_data->sp->lock, flags);
	cmd = command_data->command;
	अगर (cmd == शून्य) अणु
		spin_unlock_irqrestore(&command_data->sp->lock, flags);
		वापस 0;
	पूर्ण
	command_data->command = शून्य;
	spin_unlock_irqrestore(&command_data->sp->lock, flags);

	अगर (cmd->status != IBMASM_CMD_COMPLETE) अणु
		command_put(cmd);
		वापस -EIO;
	पूर्ण
	len = min(count, cmd->buffer_size);
	अगर (copy_to_user(buf, cmd->buffer, len)) अणु
		command_put(cmd);
		वापस -EFAULT;
	पूर्ण
	command_put(cmd);

	वापस len;
पूर्ण

अटल sमाप_प्रकार command_file_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *ubuff, माप_प्रकार count, loff_t *offset)
अणु
	काष्ठा ibmयंत्रfs_command_data *command_data = file->निजी_data;
	काष्ठा command *cmd;
	अचिन्हित दीर्घ flags;

	अगर (*offset < 0)
		वापस -EINVAL;
	अगर (count == 0 || count > IBMASM_CMD_MAX_BUFFER_SIZE)
		वापस 0;
	अगर (*offset != 0)
		वापस 0;

	/* commands are executed sequentially, only one command at a समय */
	अगर (command_data->command)
		वापस -EAGAIN;

	cmd = ibmयंत्र_new_command(command_data->sp, count);
	अगर (!cmd)
		वापस -ENOMEM;

	अगर (copy_from_user(cmd->buffer, ubuff, count)) अणु
		command_put(cmd);
		वापस -EFAULT;
	पूर्ण

	spin_lock_irqsave(&command_data->sp->lock, flags);
	अगर (command_data->command) अणु
		spin_unlock_irqrestore(&command_data->sp->lock, flags);
		command_put(cmd);
		वापस -EAGAIN;
	पूर्ण
	command_data->command = cmd;
	spin_unlock_irqrestore(&command_data->sp->lock, flags);

	ibmयंत्र_exec_command(command_data->sp, cmd);
	ibmयंत्र_रुको_क्रम_response(cmd, get_करोt_command_समयout(cmd->buffer));

	वापस count;
पूर्ण

अटल पूर्णांक event_file_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा ibmयंत्रfs_event_data *event_data;
	काष्ठा service_processor *sp;

	अगर (!inode->i_निजी)
		वापस -ENODEV;

	sp = inode->i_निजी;

	event_data = kदो_स्मृति(माप(काष्ठा ibmयंत्रfs_event_data), GFP_KERNEL);
	अगर (!event_data)
		वापस -ENOMEM;

	ibmयंत्र_event_पढ़ोer_रेजिस्टर(sp, &event_data->पढ़ोer);

	event_data->sp = sp;
	event_data->active = 0;
	file->निजी_data = event_data;
	वापस 0;
पूर्ण

अटल पूर्णांक event_file_बंद(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा ibmयंत्रfs_event_data *event_data = file->निजी_data;

	ibmयंत्र_event_पढ़ोer_unरेजिस्टर(event_data->sp, &event_data->पढ़ोer);
	kमुक्त(event_data);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार event_file_पढ़ो(काष्ठा file *file, अक्षर __user *buf, माप_प्रकार count, loff_t *offset)
अणु
	काष्ठा ibmयंत्रfs_event_data *event_data = file->निजी_data;
	काष्ठा event_पढ़ोer *पढ़ोer = &event_data->पढ़ोer;
	काष्ठा service_processor *sp = event_data->sp;
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;

	अगर (*offset < 0)
		वापस -EINVAL;
	अगर (count == 0 || count > IBMASM_EVENT_MAX_SIZE)
		वापस 0;
	अगर (*offset != 0)
		वापस 0;

	spin_lock_irqsave(&sp->lock, flags);
	अगर (event_data->active) अणु
		spin_unlock_irqrestore(&sp->lock, flags);
		वापस -EBUSY;
	पूर्ण
	event_data->active = 1;
	spin_unlock_irqrestore(&sp->lock, flags);

	ret = ibmयंत्र_get_next_event(sp, पढ़ोer);
	अगर (ret <= 0)
		जाओ out;

	अगर (count < पढ़ोer->data_size) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

        अगर (copy_to_user(buf, पढ़ोer->data, पढ़ोer->data_size)) अणु
		ret = -EFAULT;
		जाओ out;
	पूर्ण
	ret = पढ़ोer->data_size;

out:
	event_data->active = 0;
	वापस ret;
पूर्ण

अटल sमाप_प्रकार event_file_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf, माप_प्रकार count, loff_t *offset)
अणु
	काष्ठा ibmयंत्रfs_event_data *event_data = file->निजी_data;

	अगर (*offset < 0)
		वापस -EINVAL;
	अगर (count != 1)
		वापस 0;
	अगर (*offset != 0)
		वापस 0;

	ibmयंत्र_cancel_next_event(&event_data->पढ़ोer);
	वापस 0;
पूर्ण

अटल पूर्णांक r_heartbeat_file_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा ibmयंत्रfs_heartbeat_data *rhbeat;

	अगर (!inode->i_निजी)
		वापस -ENODEV;

	rhbeat = kदो_स्मृति(माप(काष्ठा ibmयंत्रfs_heartbeat_data), GFP_KERNEL);
	अगर (!rhbeat)
		वापस -ENOMEM;

	rhbeat->sp = inode->i_निजी;
	rhbeat->active = 0;
	ibmयंत्र_init_reverse_heartbeat(rhbeat->sp, &rhbeat->heartbeat);
	file->निजी_data = rhbeat;
	वापस 0;
पूर्ण

अटल पूर्णांक r_heartbeat_file_बंद(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा ibmयंत्रfs_heartbeat_data *rhbeat = file->निजी_data;

	kमुक्त(rhbeat);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार r_heartbeat_file_पढ़ो(काष्ठा file *file, अक्षर __user *buf, माप_प्रकार count, loff_t *offset)
अणु
	काष्ठा ibmयंत्रfs_heartbeat_data *rhbeat = file->निजी_data;
	अचिन्हित दीर्घ flags;
	पूर्णांक result;

	अगर (*offset < 0)
		वापस -EINVAL;
	अगर (count == 0 || count > 1024)
		वापस 0;
	अगर (*offset != 0)
		वापस 0;

	/* allow only one reverse heartbeat per process */
	spin_lock_irqsave(&rhbeat->sp->lock, flags);
	अगर (rhbeat->active) अणु
		spin_unlock_irqrestore(&rhbeat->sp->lock, flags);
		वापस -EBUSY;
	पूर्ण
	rhbeat->active = 1;
	spin_unlock_irqrestore(&rhbeat->sp->lock, flags);

	result = ibmयंत्र_start_reverse_heartbeat(rhbeat->sp, &rhbeat->heartbeat);
	rhbeat->active = 0;

	वापस result;
पूर्ण

अटल sमाप_प्रकार r_heartbeat_file_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf, माप_प्रकार count, loff_t *offset)
अणु
	काष्ठा ibmयंत्रfs_heartbeat_data *rhbeat = file->निजी_data;

	अगर (*offset < 0)
		वापस -EINVAL;
	अगर (count != 1)
		वापस 0;
	अगर (*offset != 0)
		वापस 0;

	अगर (rhbeat->active)
		ibmयंत्र_stop_reverse_heartbeat(&rhbeat->heartbeat);

	वापस 1;
पूर्ण

अटल पूर्णांक remote_settings_file_बंद(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस 0;
पूर्ण

अटल sमाप_प्रकार remote_settings_file_पढ़ो(काष्ठा file *file, अक्षर __user *buf, माप_प्रकार count, loff_t *offset)
अणु
	व्योम __iomem *address = (व्योम __iomem *)file->निजी_data;
	पूर्णांक len = 0;
	अचिन्हित पूर्णांक value;
	अक्षर lbuf[20];

	value = पढ़ोl(address);
	len = snम_लिखो(lbuf, माप(lbuf), "%d\n", value);

	वापस simple_पढ़ो_from_buffer(buf, count, offset, lbuf, len);
पूर्ण

अटल sमाप_प्रकार remote_settings_file_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *ubuff, माप_प्रकार count, loff_t *offset)
अणु
	व्योम __iomem *address = (व्योम __iomem *)file->निजी_data;
	अक्षर *buff;
	अचिन्हित पूर्णांक value;

	अगर (*offset < 0)
		वापस -EINVAL;
	अगर (count == 0 || count > 1024)
		वापस 0;
	अगर (*offset != 0)
		वापस 0;

	buff = kzalloc (count + 1, GFP_KERNEL);
	अगर (!buff)
		वापस -ENOMEM;


	अगर (copy_from_user(buff, ubuff, count)) अणु
		kमुक्त(buff);
		वापस -EFAULT;
	पूर्ण

	value = simple_म_से_अदीर्घ(buff, शून्य, 10);
	ग_लिखोl(value, address);
	kमुक्त(buff);

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations command_fops = अणु
	.खोलो =		command_file_खोलो,
	.release =	command_file_बंद,
	.पढ़ो =		command_file_पढ़ो,
	.ग_लिखो =	command_file_ग_लिखो,
	.llseek =	generic_file_llseek,
पूर्ण;

अटल स्थिर काष्ठा file_operations event_fops = अणु
	.खोलो =		event_file_खोलो,
	.release =	event_file_बंद,
	.पढ़ो =		event_file_पढ़ो,
	.ग_लिखो =	event_file_ग_लिखो,
	.llseek =	generic_file_llseek,
पूर्ण;

अटल स्थिर काष्ठा file_operations r_heartbeat_fops = अणु
	.खोलो =		r_heartbeat_file_खोलो,
	.release =	r_heartbeat_file_बंद,
	.पढ़ो =		r_heartbeat_file_पढ़ो,
	.ग_लिखो =	r_heartbeat_file_ग_लिखो,
	.llseek =	generic_file_llseek,
पूर्ण;

अटल स्थिर काष्ठा file_operations remote_settings_fops = अणु
	.खोलो =		simple_खोलो,
	.release =	remote_settings_file_बंद,
	.पढ़ो =		remote_settings_file_पढ़ो,
	.ग_लिखो =	remote_settings_file_ग_लिखो,
	.llseek =	generic_file_llseek,
पूर्ण;


अटल व्योम ibmयंत्रfs_create_files (काष्ठा super_block *sb)
अणु
	काष्ठा list_head *entry;
	काष्ठा service_processor *sp;

	list_क्रम_each(entry, &service_processors) अणु
		काष्ठा dentry *dir;
		काष्ठा dentry *remote_dir;
		sp = list_entry(entry, काष्ठा service_processor, node);
		dir = ibmयंत्रfs_create_dir(sb->s_root, sp->स_नाम);
		अगर (!dir)
			जारी;

		ibmयंत्रfs_create_file(dir, "command", &command_fops, sp, S_IRUSR|S_IWUSR);
		ibmयंत्रfs_create_file(dir, "event", &event_fops, sp, S_IRUSR|S_IWUSR);
		ibmयंत्रfs_create_file(dir, "reverse_heartbeat", &r_heartbeat_fops, sp, S_IRUSR|S_IWUSR);

		remote_dir = ibmयंत्रfs_create_dir(dir, "remote_video");
		अगर (!remote_dir)
			जारी;

		ibmयंत्रfs_create_file(remote_dir, "width", &remote_settings_fops, (व्योम *)display_width(sp), S_IRUSR|S_IWUSR);
		ibmयंत्रfs_create_file(remote_dir, "height", &remote_settings_fops, (व्योम *)display_height(sp), S_IRUSR|S_IWUSR);
		ibmयंत्रfs_create_file(remote_dir, "depth", &remote_settings_fops, (व्योम *)display_depth(sp), S_IRUSR|S_IWUSR);
	पूर्ण
पूर्ण
