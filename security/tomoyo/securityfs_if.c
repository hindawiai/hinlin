<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * security/tomoyo/securityfs_अगर.c
 *
 * Copyright (C) 2005-2011  NTT DATA CORPORATION
 */

#समावेश <linux/security.h>
#समावेश "common.h"

/**
 * tomoyo_check_task_acl - Check permission क्रम task operation.
 *
 * @r:   Poपूर्णांकer to "struct tomoyo_request_info".
 * @ptr: Poपूर्णांकer to "struct tomoyo_acl_info".
 *
 * Returns true अगर granted, false otherwise.
 */
अटल bool tomoyo_check_task_acl(काष्ठा tomoyo_request_info *r,
				  स्थिर काष्ठा tomoyo_acl_info *ptr)
अणु
	स्थिर काष्ठा tomoyo_task_acl *acl = container_of(ptr, typeof(*acl),
							 head);

	वापस !tomoyo_pathcmp(r->param.task.करोमुख्यname, acl->करोमुख्यname);
पूर्ण

/**
 * tomoyo_ग_लिखो_self - ग_लिखो() क्रम /sys/kernel/security/tomoyo/self_करोमुख्य पूर्णांकerface.
 *
 * @file:  Poपूर्णांकer to "struct file".
 * @buf:   Doमुख्यname to transit to.
 * @count: Size of @buf.
 * @ppos:  Unused.
 *
 * Returns @count on success, negative value otherwise.
 *
 * If करोमुख्य transition was permitted but the करोमुख्य transition failed, this
 * function वापसs error rather than terminating current thपढ़ो with SIGKILL.
 */
अटल sमाप_प्रकार tomoyo_ग_लिखो_self(काष्ठा file *file, स्थिर अक्षर __user *buf,
			      माप_प्रकार count, loff_t *ppos)
अणु
	अक्षर *data;
	पूर्णांक error;

	अगर (!count || count >= TOMOYO_EXEC_TMPSIZE - 10)
		वापस -ENOMEM;
	data = memdup_user_nul(buf, count);
	अगर (IS_ERR(data))
		वापस PTR_ERR(data);
	tomoyo_normalize_line(data);
	अगर (tomoyo_correct_करोमुख्य(data)) अणु
		स्थिर पूर्णांक idx = tomoyo_पढ़ो_lock();
		काष्ठा tomoyo_path_info name;
		काष्ठा tomoyo_request_info r;

		name.name = data;
		tomoyo_fill_path_info(&name);
		/* Check "task manual_domain_transition" permission. */
		tomoyo_init_request_info(&r, शून्य, TOMOYO_MAC_खाता_EXECUTE);
		r.param_type = TOMOYO_TYPE_MANUAL_TASK_ACL;
		r.param.task.करोमुख्यname = &name;
		tomoyo_check_acl(&r, tomoyo_check_task_acl);
		अगर (!r.granted)
			error = -EPERM;
		अन्यथा अणु
			काष्ठा tomoyo_करोमुख्य_info *new_करोमुख्य =
				tomoyo_assign_करोमुख्य(data, true);
			अगर (!new_करोमुख्य) अणु
				error = -ENOENT;
			पूर्ण अन्यथा अणु
				काष्ठा tomoyo_task *s = tomoyo_task(current);
				काष्ठा tomoyo_करोमुख्य_info *old_करोमुख्य =
					s->करोमुख्य_info;

				s->करोमुख्य_info = new_करोमुख्य;
				atomic_inc(&new_करोमुख्य->users);
				atomic_dec(&old_करोमुख्य->users);
				error = 0;
			पूर्ण
		पूर्ण
		tomoyo_पढ़ो_unlock(idx);
	पूर्ण अन्यथा
		error = -EINVAL;
	kमुक्त(data);
	वापस error ? error : count;
पूर्ण

/**
 * tomoyo_पढ़ो_self - पढ़ो() क्रम /sys/kernel/security/tomoyo/self_करोमुख्य पूर्णांकerface.
 *
 * @file:  Poपूर्णांकer to "struct file".
 * @buf:   Doमुख्यname which current thपढ़ो beदीर्घs to.
 * @count: Size of @buf.
 * @ppos:  Bytes पढ़ो by now.
 *
 * Returns पढ़ो size on success, negative value otherwise.
 */
अटल sमाप_प्रकार tomoyo_पढ़ो_self(काष्ठा file *file, अक्षर __user *buf,
				माप_प्रकार count, loff_t *ppos)
अणु
	स्थिर अक्षर *करोमुख्य = tomoyo_करोमुख्य()->करोमुख्यname->name;
	loff_t len = म_माप(करोमुख्य);
	loff_t pos = *ppos;

	अगर (pos >= len || !count)
		वापस 0;
	len -= pos;
	अगर (count < len)
		len = count;
	अगर (copy_to_user(buf, करोमुख्य + pos, len))
		वापस -EFAULT;
	*ppos += len;
	वापस len;
पूर्ण

/* Operations क्रम /sys/kernel/security/tomoyo/self_करोमुख्य पूर्णांकerface. */
अटल स्थिर काष्ठा file_operations tomoyo_self_operations = अणु
	.ग_लिखो = tomoyo_ग_लिखो_self,
	.पढ़ो  = tomoyo_पढ़ो_self,
पूर्ण;

/**
 * tomoyo_खोलो - खोलो() क्रम /sys/kernel/security/tomoyo/ पूर्णांकerface.
 *
 * @inode: Poपूर्णांकer to "struct inode".
 * @file:  Poपूर्णांकer to "struct file".
 *
 * Returns 0 on success, negative value otherwise.
 */
अटल पूर्णांक tomoyo_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	स्थिर u8 key = (uपूर्णांकptr_t) file_inode(file)->i_निजी;

	वापस tomoyo_खोलो_control(key, file);
पूर्ण

/**
 * tomoyo_release - बंद() क्रम /sys/kernel/security/tomoyo/ पूर्णांकerface.
 *
 * @file:  Poपूर्णांकer to "struct file".
 *
 */
अटल पूर्णांक tomoyo_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	tomoyo_बंद_control(file->निजी_data);
	वापस 0;
पूर्ण

/**
 * tomoyo_poll - poll() क्रम /sys/kernel/security/tomoyo/ पूर्णांकerface.
 *
 * @file: Poपूर्णांकer to "struct file".
 * @रुको: Poपूर्णांकer to "poll_table". Maybe शून्य.
 *
 * Returns EPOLLIN | EPOLLRDNORM | EPOLLOUT | EPOLLWRNORM अगर पढ़ोy to पढ़ो/ग_लिखो,
 * EPOLLOUT | EPOLLWRNORM otherwise.
 */
अटल __poll_t tomoyo_poll(काष्ठा file *file, poll_table *रुको)
अणु
	वापस tomoyo_poll_control(file, रुको);
पूर्ण

/**
 * tomoyo_पढ़ो - पढ़ो() क्रम /sys/kernel/security/tomoyo/ पूर्णांकerface.
 *
 * @file:  Poपूर्णांकer to "struct file".
 * @buf:   Poपूर्णांकer to buffer.
 * @count: Size of @buf.
 * @ppos:  Unused.
 *
 * Returns bytes पढ़ो on success, negative value otherwise.
 */
अटल sमाप_प्रकार tomoyo_पढ़ो(काष्ठा file *file, अक्षर __user *buf, माप_प्रकार count,
			   loff_t *ppos)
अणु
	वापस tomoyo_पढ़ो_control(file->निजी_data, buf, count);
पूर्ण

/**
 * tomoyo_ग_लिखो - ग_लिखो() क्रम /sys/kernel/security/tomoyo/ पूर्णांकerface.
 *
 * @file:  Poपूर्णांकer to "struct file".
 * @buf:   Poपूर्णांकer to buffer.
 * @count: Size of @buf.
 * @ppos:  Unused.
 *
 * Returns @count on success, negative value otherwise.
 */
अटल sमाप_प्रकार tomoyo_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
			    माप_प्रकार count, loff_t *ppos)
अणु
	वापस tomoyo_ग_लिखो_control(file->निजी_data, buf, count);
पूर्ण

/*
 * tomoyo_operations is a "struct file_operations" which is used क्रम handling
 * /sys/kernel/security/tomoyo/ पूर्णांकerface.
 *
 * Some files under /sys/kernel/security/tomoyo/ directory accept खोलो(O_RDWR).
 * See tomoyo_io_buffer क्रम पूर्णांकernals.
 */
अटल स्थिर काष्ठा file_operations tomoyo_operations = अणु
	.खोलो    = tomoyo_खोलो,
	.release = tomoyo_release,
	.poll    = tomoyo_poll,
	.पढ़ो    = tomoyo_पढ़ो,
	.ग_लिखो   = tomoyo_ग_लिखो,
	.llseek  = noop_llseek,
पूर्ण;

/**
 * tomoyo_create_entry - Create पूर्णांकerface files under /sys/kernel/security/tomoyo/ directory.
 *
 * @name:   The name of the पूर्णांकerface file.
 * @mode:   The permission of the पूर्णांकerface file.
 * @parent: The parent directory.
 * @key:    Type of पूर्णांकerface.
 *
 * Returns nothing.
 */
अटल व्योम __init tomoyo_create_entry(स्थिर अक्षर *name, स्थिर umode_t mode,
				       काष्ठा dentry *parent, स्थिर u8 key)
अणु
	securityfs_create_file(name, mode, parent, (व्योम *) (uपूर्णांकptr_t) key,
			       &tomoyo_operations);
पूर्ण

/**
 * tomoyo_initerface_init - Initialize /sys/kernel/security/tomoyo/ पूर्णांकerface.
 *
 * Returns 0.
 */
अटल पूर्णांक __init tomoyo_initerface_init(व्योम)
अणु
	काष्ठा tomoyo_करोमुख्य_info *करोमुख्य;
	काष्ठा dentry *tomoyo_dir;

	अगर (!tomoyo_enabled)
		वापस 0;
	करोमुख्य = tomoyo_करोमुख्य();
	/* Don't create securityfs entries unless रेजिस्टरed. */
	अगर (करोमुख्य != &tomoyo_kernel_करोमुख्य)
		वापस 0;

	tomoyo_dir = securityfs_create_dir("tomoyo", शून्य);
	tomoyo_create_entry("query",            0600, tomoyo_dir,
			    TOMOYO_QUERY);
	tomoyo_create_entry("domain_policy",    0600, tomoyo_dir,
			    TOMOYO_DOMAINPOLICY);
	tomoyo_create_entry("exception_policy", 0600, tomoyo_dir,
			    TOMOYO_EXCEPTIONPOLICY);
	tomoyo_create_entry("audit",            0400, tomoyo_dir,
			    TOMOYO_AUDIT);
	tomoyo_create_entry(".process_status",  0600, tomoyo_dir,
			    TOMOYO_PROCESS_STATUS);
	tomoyo_create_entry("stat",             0644, tomoyo_dir,
			    TOMOYO_STAT);
	tomoyo_create_entry("profile",          0600, tomoyo_dir,
			    TOMOYO_PROखाता);
	tomoyo_create_entry("manager",          0600, tomoyo_dir,
			    TOMOYO_MANAGER);
	tomoyo_create_entry("version",          0400, tomoyo_dir,
			    TOMOYO_VERSION);
	securityfs_create_file("self_domain", 0666, tomoyo_dir, शून्य,
			       &tomoyo_self_operations);
	tomoyo_load_builtin_policy();
	वापस 0;
पूर्ण

fs_initcall(tomoyo_initerface_init);
