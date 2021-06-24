<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * security/tomoyo/common.c
 *
 * Copyright (C) 2005-2011  NTT DATA CORPORATION
 */

#समावेश <linux/uaccess.h>
#समावेश <linux/slab.h>
#समावेश <linux/security.h>
#समावेश "common.h"

/* String table क्रम operation mode. */
स्थिर अक्षर * स्थिर tomoyo_mode[TOMOYO_CONFIG_MAX_MODE] = अणु
	[TOMOYO_CONFIG_DISABLED]   = "disabled",
	[TOMOYO_CONFIG_LEARNING]   = "learning",
	[TOMOYO_CONFIG_PERMISSIVE] = "permissive",
	[TOMOYO_CONFIG_ENFORCING]  = "enforcing"
पूर्ण;

/* String table क्रम /sys/kernel/security/tomoyo/profile */
स्थिर अक्षर * स्थिर tomoyo_mac_keywords[TOMOYO_MAX_MAC_INDEX
				       + TOMOYO_MAX_MAC_CATEGORY_INDEX] = अणु
	/* CONFIG::file group */
	[TOMOYO_MAC_खाता_EXECUTE]    = "execute",
	[TOMOYO_MAC_खाता_OPEN]       = "open",
	[TOMOYO_MAC_खाता_CREATE]     = "create",
	[TOMOYO_MAC_खाता_UNLINK]     = "unlink",
	[TOMOYO_MAC_खाता_GETATTR]    = "getattr",
	[TOMOYO_MAC_खाता_MKसूची]      = "mkdir",
	[TOMOYO_MAC_खाता_RMसूची]      = "rmdir",
	[TOMOYO_MAC_खाता_MKFIFO]     = "mkfifo",
	[TOMOYO_MAC_खाता_MKSOCK]     = "mksock",
	[TOMOYO_MAC_खाता_TRUNCATE]   = "truncate",
	[TOMOYO_MAC_खाता_SYMLINK]    = "symlink",
	[TOMOYO_MAC_खाता_MKBLOCK]    = "mkblock",
	[TOMOYO_MAC_खाता_MKCHAR]     = "mkchar",
	[TOMOYO_MAC_खाता_LINK]       = "link",
	[TOMOYO_MAC_खाता_RENAME]     = "rename",
	[TOMOYO_MAC_खाता_CHMOD]      = "chmod",
	[TOMOYO_MAC_खाता_CHOWN]      = "chown",
	[TOMOYO_MAC_खाता_CHGRP]      = "chgrp",
	[TOMOYO_MAC_खाता_IOCTL]      = "ioctl",
	[TOMOYO_MAC_खाता_CHROOT]     = "chroot",
	[TOMOYO_MAC_खाता_MOUNT]      = "mount",
	[TOMOYO_MAC_खाता_UMOUNT]     = "unmount",
	[TOMOYO_MAC_खाता_PIVOT_ROOT] = "pivot_root",
	/* CONFIG::network group */
	[TOMOYO_MAC_NETWORK_INET_STREAM_BIND]       = "inet_stream_bind",
	[TOMOYO_MAC_NETWORK_INET_STREAM_LISTEN]     = "inet_stream_listen",
	[TOMOYO_MAC_NETWORK_INET_STREAM_CONNECT]    = "inet_stream_connect",
	[TOMOYO_MAC_NETWORK_INET_DGRAM_BIND]        = "inet_dgram_bind",
	[TOMOYO_MAC_NETWORK_INET_DGRAM_SEND]        = "inet_dgram_send",
	[TOMOYO_MAC_NETWORK_INET_RAW_BIND]          = "inet_raw_bind",
	[TOMOYO_MAC_NETWORK_INET_RAW_SEND]          = "inet_raw_send",
	[TOMOYO_MAC_NETWORK_UNIX_STREAM_BIND]       = "unix_stream_bind",
	[TOMOYO_MAC_NETWORK_UNIX_STREAM_LISTEN]     = "unix_stream_listen",
	[TOMOYO_MAC_NETWORK_UNIX_STREAM_CONNECT]    = "unix_stream_connect",
	[TOMOYO_MAC_NETWORK_UNIX_DGRAM_BIND]        = "unix_dgram_bind",
	[TOMOYO_MAC_NETWORK_UNIX_DGRAM_SEND]        = "unix_dgram_send",
	[TOMOYO_MAC_NETWORK_UNIX_SEQPACKET_BIND]    = "unix_seqpacket_bind",
	[TOMOYO_MAC_NETWORK_UNIX_SEQPACKET_LISTEN]  = "unix_seqpacket_listen",
	[TOMOYO_MAC_NETWORK_UNIX_SEQPACKET_CONNECT] = "unix_seqpacket_connect",
	/* CONFIG::misc group */
	[TOMOYO_MAC_ENVIRON] = "env",
	/* CONFIG group */
	[TOMOYO_MAX_MAC_INDEX + TOMOYO_MAC_CATEGORY_खाता] = "file",
	[TOMOYO_MAX_MAC_INDEX + TOMOYO_MAC_CATEGORY_NETWORK] = "network",
	[TOMOYO_MAX_MAC_INDEX + TOMOYO_MAC_CATEGORY_MISC] = "misc",
पूर्ण;

/* String table क्रम conditions. */
स्थिर अक्षर * स्थिर tomoyo_condition_keyword[TOMOYO_MAX_CONDITION_KEYWORD] = अणु
	[TOMOYO_TASK_UID]             = "task.uid",
	[TOMOYO_TASK_EUID]            = "task.euid",
	[TOMOYO_TASK_SUID]            = "task.suid",
	[TOMOYO_TASK_FSUID]           = "task.fsuid",
	[TOMOYO_TASK_GID]             = "task.gid",
	[TOMOYO_TASK_EGID]            = "task.egid",
	[TOMOYO_TASK_SGID]            = "task.sgid",
	[TOMOYO_TASK_FSGID]           = "task.fsgid",
	[TOMOYO_TASK_PID]             = "task.pid",
	[TOMOYO_TASK_PPID]            = "task.ppid",
	[TOMOYO_EXEC_ARGC]            = "exec.argc",
	[TOMOYO_EXEC_ENVC]            = "exec.envc",
	[TOMOYO_TYPE_IS_SOCKET]       = "socket",
	[TOMOYO_TYPE_IS_SYMLINK]      = "symlink",
	[TOMOYO_TYPE_IS_खाता]         = "file",
	[TOMOYO_TYPE_IS_BLOCK_DEV]    = "block",
	[TOMOYO_TYPE_IS_सूचीECTORY]    = "directory",
	[TOMOYO_TYPE_IS_CHAR_DEV]     = "char",
	[TOMOYO_TYPE_IS_FIFO]         = "fifo",
	[TOMOYO_MODE_SETUID]          = "setuid",
	[TOMOYO_MODE_SETGID]          = "setgid",
	[TOMOYO_MODE_STICKY]          = "sticky",
	[TOMOYO_MODE_OWNER_READ]      = "owner_read",
	[TOMOYO_MODE_OWNER_WRITE]     = "owner_write",
	[TOMOYO_MODE_OWNER_EXECUTE]   = "owner_execute",
	[TOMOYO_MODE_GROUP_READ]      = "group_read",
	[TOMOYO_MODE_GROUP_WRITE]     = "group_write",
	[TOMOYO_MODE_GROUP_EXECUTE]   = "group_execute",
	[TOMOYO_MODE_OTHERS_READ]     = "others_read",
	[TOMOYO_MODE_OTHERS_WRITE]    = "others_write",
	[TOMOYO_MODE_OTHERS_EXECUTE]  = "others_execute",
	[TOMOYO_EXEC_REALPATH]        = "exec.realpath",
	[TOMOYO_SYMLINK_TARGET]       = "symlink.target",
	[TOMOYO_PATH1_UID]            = "path1.uid",
	[TOMOYO_PATH1_GID]            = "path1.gid",
	[TOMOYO_PATH1_INO]            = "path1.ino",
	[TOMOYO_PATH1_MAJOR]          = "path1.major",
	[TOMOYO_PATH1_MINOR]          = "path1.minor",
	[TOMOYO_PATH1_PERM]           = "path1.perm",
	[TOMOYO_PATH1_TYPE]           = "path1.type",
	[TOMOYO_PATH1_DEV_MAJOR]      = "path1.dev_major",
	[TOMOYO_PATH1_DEV_MINOR]      = "path1.dev_minor",
	[TOMOYO_PATH2_UID]            = "path2.uid",
	[TOMOYO_PATH2_GID]            = "path2.gid",
	[TOMOYO_PATH2_INO]            = "path2.ino",
	[TOMOYO_PATH2_MAJOR]          = "path2.major",
	[TOMOYO_PATH2_MINOR]          = "path2.minor",
	[TOMOYO_PATH2_PERM]           = "path2.perm",
	[TOMOYO_PATH2_TYPE]           = "path2.type",
	[TOMOYO_PATH2_DEV_MAJOR]      = "path2.dev_major",
	[TOMOYO_PATH2_DEV_MINOR]      = "path2.dev_minor",
	[TOMOYO_PATH1_PARENT_UID]     = "path1.parent.uid",
	[TOMOYO_PATH1_PARENT_GID]     = "path1.parent.gid",
	[TOMOYO_PATH1_PARENT_INO]     = "path1.parent.ino",
	[TOMOYO_PATH1_PARENT_PERM]    = "path1.parent.perm",
	[TOMOYO_PATH2_PARENT_UID]     = "path2.parent.uid",
	[TOMOYO_PATH2_PARENT_GID]     = "path2.parent.gid",
	[TOMOYO_PATH2_PARENT_INO]     = "path2.parent.ino",
	[TOMOYO_PATH2_PARENT_PERM]    = "path2.parent.perm",
पूर्ण;

/* String table क्रम PREFERENCE keyword. */
अटल स्थिर अक्षर * स्थिर tomoyo_pref_keywords[TOMOYO_MAX_PREF] = अणु
	[TOMOYO_PREF_MAX_AUDIT_LOG]      = "max_audit_log",
	[TOMOYO_PREF_MAX_LEARNING_ENTRY] = "max_learning_entry",
पूर्ण;

/* String table क्रम path operation. */
स्थिर अक्षर * स्थिर tomoyo_path_keyword[TOMOYO_MAX_PATH_OPERATION] = अणु
	[TOMOYO_TYPE_EXECUTE]    = "execute",
	[TOMOYO_TYPE_READ]       = "read",
	[TOMOYO_TYPE_WRITE]      = "write",
	[TOMOYO_TYPE_APPEND]     = "append",
	[TOMOYO_TYPE_UNLINK]     = "unlink",
	[TOMOYO_TYPE_GETATTR]    = "getattr",
	[TOMOYO_TYPE_RMसूची]      = "rmdir",
	[TOMOYO_TYPE_TRUNCATE]   = "truncate",
	[TOMOYO_TYPE_SYMLINK]    = "symlink",
	[TOMOYO_TYPE_CHROOT]     = "chroot",
	[TOMOYO_TYPE_UMOUNT]     = "unmount",
पूर्ण;

/* String table क्रम socket's operation. */
स्थिर अक्षर * स्थिर tomoyo_socket_keyword[TOMOYO_MAX_NETWORK_OPERATION] = अणु
	[TOMOYO_NETWORK_BIND]    = "bind",
	[TOMOYO_NETWORK_LISTEN]  = "listen",
	[TOMOYO_NETWORK_CONNECT] = "connect",
	[TOMOYO_NETWORK_SEND]    = "send",
पूर्ण;

/* String table क्रम categories. */
अटल स्थिर अक्षर * स्थिर tomoyo_category_keywords
[TOMOYO_MAX_MAC_CATEGORY_INDEX] = अणु
	[TOMOYO_MAC_CATEGORY_खाता]    = "file",
	[TOMOYO_MAC_CATEGORY_NETWORK] = "network",
	[TOMOYO_MAC_CATEGORY_MISC]    = "misc",
पूर्ण;

/* Permit policy management by non-root user? */
अटल bool tomoyo_manage_by_non_root;

/* Utility functions. */

/**
 * tomoyo_yesno - Return "yes" or "no".
 *
 * @value: Bool value.
 */
स्थिर अक्षर *tomoyo_yesno(स्थिर अचिन्हित पूर्णांक value)
अणु
	वापस value ? "yes" : "no";
पूर्ण

/**
 * tomoyo_addम_लिखो - म_जोड़न()-like-snम_लिखो().
 *
 * @buffer: Buffer to ग_लिखो to. Must be '\0'-terminated.
 * @len:    Size of @buffer.
 * @fmt:    The म_लिखो()'s क्रमmat string, followed by parameters.
 *
 * Returns nothing.
 */
अटल व्योम tomoyo_addम_लिखो(अक्षर *buffer, पूर्णांक len, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;
	स्थिर पूर्णांक pos = म_माप(buffer);

	बहु_शुरू(args, fmt);
	vsnम_लिखो(buffer + pos, len - pos - 1, fmt, args);
	बहु_पूर्ण(args);
पूर्ण

/**
 * tomoyo_flush - Flush queued string to userspace's buffer.
 *
 * @head:   Poपूर्णांकer to "struct tomoyo_io_buffer".
 *
 * Returns true अगर all data was flushed, false otherwise.
 */
अटल bool tomoyo_flush(काष्ठा tomoyo_io_buffer *head)
अणु
	जबतक (head->r.w_pos) अणु
		स्थिर अक्षर *w = head->r.w[0];
		माप_प्रकार len = म_माप(w);

		अगर (len) अणु
			अगर (len > head->पढ़ो_user_buf_avail)
				len = head->पढ़ो_user_buf_avail;
			अगर (!len)
				वापस false;
			अगर (copy_to_user(head->पढ़ो_user_buf, w, len))
				वापस false;
			head->पढ़ो_user_buf_avail -= len;
			head->पढ़ो_user_buf += len;
			w += len;
		पूर्ण
		head->r.w[0] = w;
		अगर (*w)
			वापस false;
		/* Add '\0' क्रम audit logs and query. */
		अगर (head->poll) अणु
			अगर (!head->पढ़ो_user_buf_avail ||
			    copy_to_user(head->पढ़ो_user_buf, "", 1))
				वापस false;
			head->पढ़ो_user_buf_avail--;
			head->पढ़ो_user_buf++;
		पूर्ण
		head->r.w_pos--;
		क्रम (len = 0; len < head->r.w_pos; len++)
			head->r.w[len] = head->r.w[len + 1];
	पूर्ण
	head->r.avail = 0;
	वापस true;
पूर्ण

/**
 * tomoyo_set_string - Queue string to "struct tomoyo_io_buffer" काष्ठाure.
 *
 * @head:   Poपूर्णांकer to "struct tomoyo_io_buffer".
 * @string: String to prपूर्णांक.
 *
 * Note that @string has to be kept valid until @head is kमुक्त()d.
 * This means that अक्षर[] allocated on stack memory cannot be passed to
 * this function. Use tomoyo_io_म_लिखो() क्रम अक्षर[] allocated on stack memory.
 */
अटल व्योम tomoyo_set_string(काष्ठा tomoyo_io_buffer *head, स्थिर अक्षर *string)
अणु
	अगर (head->r.w_pos < TOMOYO_MAX_IO_READ_QUEUE) अणु
		head->r.w[head->r.w_pos++] = string;
		tomoyo_flush(head);
	पूर्ण अन्यथा
		WARN_ON(1);
पूर्ण

अटल व्योम tomoyo_io_म_लिखो(काष्ठा tomoyo_io_buffer *head, स्थिर अक्षर *fmt,
			     ...) __म_लिखो(2, 3);

/**
 * tomoyo_io_म_लिखो - म_लिखो() to "struct tomoyo_io_buffer" काष्ठाure.
 *
 * @head: Poपूर्णांकer to "struct tomoyo_io_buffer".
 * @fmt:  The म_लिखो()'s क्रमmat string, followed by parameters.
 */
अटल व्योम tomoyo_io_म_लिखो(काष्ठा tomoyo_io_buffer *head, स्थिर अक्षर *fmt,
			     ...)
अणु
	बहु_सूची args;
	माप_प्रकार len;
	माप_प्रकार pos = head->r.avail;
	पूर्णांक size = head->पढ़ोbuf_size - pos;

	अगर (size <= 0)
		वापस;
	बहु_शुरू(args, fmt);
	len = vsnम_लिखो(head->पढ़ो_buf + pos, size, fmt, args) + 1;
	बहु_पूर्ण(args);
	अगर (pos + len >= head->पढ़ोbuf_size) अणु
		WARN_ON(1);
		वापस;
	पूर्ण
	head->r.avail += len;
	tomoyo_set_string(head, head->पढ़ो_buf + pos);
पूर्ण

/**
 * tomoyo_set_space - Put a space to "struct tomoyo_io_buffer" काष्ठाure.
 *
 * @head: Poपूर्णांकer to "struct tomoyo_io_buffer".
 *
 * Returns nothing.
 */
अटल व्योम tomoyo_set_space(काष्ठा tomoyo_io_buffer *head)
अणु
	tomoyo_set_string(head, " ");
पूर्ण

/**
 * tomoyo_set_lf - Put a line feed to "struct tomoyo_io_buffer" काष्ठाure.
 *
 * @head: Poपूर्णांकer to "struct tomoyo_io_buffer".
 *
 * Returns nothing.
 */
अटल bool tomoyo_set_lf(काष्ठा tomoyo_io_buffer *head)
अणु
	tomoyo_set_string(head, "\n");
	वापस !head->r.w_pos;
पूर्ण

/**
 * tomoyo_set_slash - Put a shash to "struct tomoyo_io_buffer" काष्ठाure.
 *
 * @head: Poपूर्णांकer to "struct tomoyo_io_buffer".
 *
 * Returns nothing.
 */
अटल व्योम tomoyo_set_slash(काष्ठा tomoyo_io_buffer *head)
अणु
	tomoyo_set_string(head, "/");
पूर्ण

/* List of namespaces. */
LIST_HEAD(tomoyo_namespace_list);
/* True अगर namespace other than tomoyo_kernel_namespace is defined. */
अटल bool tomoyo_namespace_enabled;

/**
 * tomoyo_init_policy_namespace - Initialize namespace.
 *
 * @ns: Poपूर्णांकer to "struct tomoyo_policy_namespace".
 *
 * Returns nothing.
 */
व्योम tomoyo_init_policy_namespace(काष्ठा tomoyo_policy_namespace *ns)
अणु
	अचिन्हित पूर्णांक idx;

	क्रम (idx = 0; idx < TOMOYO_MAX_ACL_GROUPS; idx++)
		INIT_LIST_HEAD(&ns->acl_group[idx]);
	क्रम (idx = 0; idx < TOMOYO_MAX_GROUP; idx++)
		INIT_LIST_HEAD(&ns->group_list[idx]);
	क्रम (idx = 0; idx < TOMOYO_MAX_POLICY; idx++)
		INIT_LIST_HEAD(&ns->policy_list[idx]);
	ns->profile_version = 20150505;
	tomoyo_namespace_enabled = !list_empty(&tomoyo_namespace_list);
	list_add_tail_rcu(&ns->namespace_list, &tomoyo_namespace_list);
पूर्ण

/**
 * tomoyo_prपूर्णांक_namespace - Prपूर्णांक namespace header.
 *
 * @head: Poपूर्णांकer to "struct tomoyo_io_buffer".
 *
 * Returns nothing.
 */
अटल व्योम tomoyo_prपूर्णांक_namespace(काष्ठा tomoyo_io_buffer *head)
अणु
	अगर (!tomoyo_namespace_enabled)
		वापस;
	tomoyo_set_string(head,
			  container_of(head->r.ns,
				       काष्ठा tomoyo_policy_namespace,
				       namespace_list)->name);
	tomoyo_set_space(head);
पूर्ण

/**
 * tomoyo_prपूर्णांक_name_जोड़ - Prपूर्णांक a tomoyo_name_जोड़.
 *
 * @head: Poपूर्णांकer to "struct tomoyo_io_buffer".
 * @ptr:  Poपूर्णांकer to "struct tomoyo_name_union".
 */
अटल व्योम tomoyo_prपूर्णांक_name_जोड़(काष्ठा tomoyo_io_buffer *head,
				    स्थिर काष्ठा tomoyo_name_जोड़ *ptr)
अणु
	tomoyo_set_space(head);
	अगर (ptr->group) अणु
		tomoyo_set_string(head, "@");
		tomoyo_set_string(head, ptr->group->group_name->name);
	पूर्ण अन्यथा अणु
		tomoyo_set_string(head, ptr->filename->name);
	पूर्ण
पूर्ण

/**
 * tomoyo_prपूर्णांक_name_जोड़_quoted - Prपूर्णांक a tomoyo_name_जोड़ with a quote.
 *
 * @head: Poपूर्णांकer to "struct tomoyo_io_buffer".
 * @ptr:  Poपूर्णांकer to "struct tomoyo_name_union".
 *
 * Returns nothing.
 */
अटल व्योम tomoyo_prपूर्णांक_name_जोड़_quoted(काष्ठा tomoyo_io_buffer *head,
					   स्थिर काष्ठा tomoyo_name_जोड़ *ptr)
अणु
	अगर (ptr->group) अणु
		tomoyo_set_string(head, "@");
		tomoyo_set_string(head, ptr->group->group_name->name);
	पूर्ण अन्यथा अणु
		tomoyo_set_string(head, "\"");
		tomoyo_set_string(head, ptr->filename->name);
		tomoyo_set_string(head, "\"");
	पूर्ण
पूर्ण

/**
 * tomoyo_prपूर्णांक_number_जोड़_nospace - Prपूर्णांक a tomoyo_number_जोड़ without a space.
 *
 * @head: Poपूर्णांकer to "struct tomoyo_io_buffer".
 * @ptr:  Poपूर्णांकer to "struct tomoyo_number_union".
 *
 * Returns nothing.
 */
अटल व्योम tomoyo_prपूर्णांक_number_जोड़_nospace
(काष्ठा tomoyo_io_buffer *head, स्थिर काष्ठा tomoyo_number_जोड़ *ptr)
अणु
	अगर (ptr->group) अणु
		tomoyo_set_string(head, "@");
		tomoyo_set_string(head, ptr->group->group_name->name);
	पूर्ण अन्यथा अणु
		पूर्णांक i;
		अचिन्हित दीर्घ min = ptr->values[0];
		स्थिर अचिन्हित दीर्घ max = ptr->values[1];
		u8 min_type = ptr->value_type[0];
		स्थिर u8 max_type = ptr->value_type[1];
		अक्षर buffer[128];

		buffer[0] = '\0';
		क्रम (i = 0; i < 2; i++) अणु
			चयन (min_type) अणु
			हाल TOMOYO_VALUE_TYPE_HEXADECIMAL:
				tomoyo_addम_लिखो(buffer, माप(buffer),
						 "0x%lX", min);
				अवरोध;
			हाल TOMOYO_VALUE_TYPE_OCTAL:
				tomoyo_addम_लिखो(buffer, माप(buffer),
						 "0%lo", min);
				अवरोध;
			शेष:
				tomoyo_addम_लिखो(buffer, माप(buffer), "%lu",
						 min);
				अवरोध;
			पूर्ण
			अगर (min == max && min_type == max_type)
				अवरोध;
			tomoyo_addम_लिखो(buffer, माप(buffer), "-");
			min_type = max_type;
			min = max;
		पूर्ण
		tomoyo_io_म_लिखो(head, "%s", buffer);
	पूर्ण
पूर्ण

/**
 * tomoyo_prपूर्णांक_number_जोड़ - Prपूर्णांक a tomoyo_number_जोड़.
 *
 * @head: Poपूर्णांकer to "struct tomoyo_io_buffer".
 * @ptr:  Poपूर्णांकer to "struct tomoyo_number_union".
 *
 * Returns nothing.
 */
अटल व्योम tomoyo_prपूर्णांक_number_जोड़(काष्ठा tomoyo_io_buffer *head,
				      स्थिर काष्ठा tomoyo_number_जोड़ *ptr)
अणु
	tomoyo_set_space(head);
	tomoyo_prपूर्णांक_number_जोड़_nospace(head, ptr);
पूर्ण

/**
 * tomoyo_assign_profile - Create a new profile.
 *
 * @ns:      Poपूर्णांकer to "struct tomoyo_policy_namespace".
 * @profile: Profile number to create.
 *
 * Returns poपूर्णांकer to "struct tomoyo_profile" on success, शून्य otherwise.
 */
अटल काष्ठा tomoyo_profile *tomoyo_assign_profile
(काष्ठा tomoyo_policy_namespace *ns, स्थिर अचिन्हित पूर्णांक profile)
अणु
	काष्ठा tomoyo_profile *ptr;
	काष्ठा tomoyo_profile *entry;

	अगर (profile >= TOMOYO_MAX_PROखाताS)
		वापस शून्य;
	ptr = ns->profile_ptr[profile];
	अगर (ptr)
		वापस ptr;
	entry = kzalloc(माप(*entry), GFP_NOFS | __GFP_NOWARN);
	अगर (mutex_lock_पूर्णांकerruptible(&tomoyo_policy_lock))
		जाओ out;
	ptr = ns->profile_ptr[profile];
	अगर (!ptr && tomoyo_memory_ok(entry)) अणु
		ptr = entry;
		ptr->शेष_config = TOMOYO_CONFIG_DISABLED |
			TOMOYO_CONFIG_WANT_GRANT_LOG |
			TOMOYO_CONFIG_WANT_REJECT_LOG;
		स_रखो(ptr->config, TOMOYO_CONFIG_USE_DEFAULT,
		       माप(ptr->config));
		ptr->pref[TOMOYO_PREF_MAX_AUDIT_LOG] =
			CONFIG_SECURITY_TOMOYO_MAX_AUDIT_LOG;
		ptr->pref[TOMOYO_PREF_MAX_LEARNING_ENTRY] =
			CONFIG_SECURITY_TOMOYO_MAX_ACCEPT_ENTRY;
		mb(); /* Aव्योम out-of-order execution. */
		ns->profile_ptr[profile] = ptr;
		entry = शून्य;
	पूर्ण
	mutex_unlock(&tomoyo_policy_lock);
 out:
	kमुक्त(entry);
	वापस ptr;
पूर्ण

/**
 * tomoyo_profile - Find a profile.
 *
 * @ns:      Poपूर्णांकer to "struct tomoyo_policy_namespace".
 * @profile: Profile number to find.
 *
 * Returns poपूर्णांकer to "struct tomoyo_profile".
 */
काष्ठा tomoyo_profile *tomoyo_profile(स्थिर काष्ठा tomoyo_policy_namespace *ns,
				      स्थिर u8 profile)
अणु
	अटल काष्ठा tomoyo_profile tomoyo_null_profile;
	काष्ठा tomoyo_profile *ptr = ns->profile_ptr[profile];

	अगर (!ptr)
		ptr = &tomoyo_null_profile;
	वापस ptr;
पूर्ण

/**
 * tomoyo_find_yesno - Find values क्रम specअगरied keyword.
 *
 * @string: String to check.
 * @find:   Name of keyword.
 *
 * Returns 1 अगर "@find=yes" was found, 0 अगर "@find=no" was found, -1 otherwise.
 */
अटल s8 tomoyo_find_yesno(स्थिर अक्षर *string, स्थिर अक्षर *find)
अणु
	स्थिर अक्षर *cp = म_माला(string, find);

	अगर (cp) अणु
		cp += म_माप(find);
		अगर (!म_भेदन(cp, "=yes", 4))
			वापस 1;
		अन्यथा अगर (!म_भेदन(cp, "=no", 3))
			वापस 0;
	पूर्ण
	वापस -1;
पूर्ण

/**
 * tomoyo_set_uपूर्णांक - Set value क्रम specअगरied preference.
 *
 * @i:      Poपूर्णांकer to "unsigned int".
 * @string: String to check.
 * @find:   Name of keyword.
 *
 * Returns nothing.
 */
अटल व्योम tomoyo_set_uपूर्णांक(अचिन्हित पूर्णांक *i, स्थिर अक्षर *string,
			    स्थिर अक्षर *find)
अणु
	स्थिर अक्षर *cp = म_माला(string, find);

	अगर (cp)
		माला_पूछो(cp + म_माप(find), "=%u", i);
पूर्ण

/**
 * tomoyo_set_mode - Set mode क्रम specअगरied profile.
 *
 * @name:    Name of functionality.
 * @value:   Mode क्रम @name.
 * @profile: Poपूर्णांकer to "struct tomoyo_profile".
 *
 * Returns 0 on success, negative value otherwise.
 */
अटल पूर्णांक tomoyo_set_mode(अक्षर *name, स्थिर अक्षर *value,
			   काष्ठा tomoyo_profile *profile)
अणु
	u8 i;
	u8 config;

	अगर (!म_भेद(name, "CONFIG")) अणु
		i = TOMOYO_MAX_MAC_INDEX + TOMOYO_MAX_MAC_CATEGORY_INDEX;
		config = profile->शेष_config;
	पूर्ण अन्यथा अगर (tomoyo_str_starts(&name, "CONFIG::")) अणु
		config = 0;
		क्रम (i = 0; i < TOMOYO_MAX_MAC_INDEX
			     + TOMOYO_MAX_MAC_CATEGORY_INDEX; i++) अणु
			पूर्णांक len = 0;

			अगर (i < TOMOYO_MAX_MAC_INDEX) अणु
				स्थिर u8 c = tomoyo_index2category[i];
				स्थिर अक्षर *category =
					tomoyo_category_keywords[c];

				len = म_माप(category);
				अगर (म_भेदन(name, category, len) ||
				    name[len++] != ':' || name[len++] != ':')
					जारी;
			पूर्ण
			अगर (म_भेद(name + len, tomoyo_mac_keywords[i]))
				जारी;
			config = profile->config[i];
			अवरोध;
		पूर्ण
		अगर (i == TOMOYO_MAX_MAC_INDEX + TOMOYO_MAX_MAC_CATEGORY_INDEX)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण
	अगर (म_माला(value, "use_default")) अणु
		config = TOMOYO_CONFIG_USE_DEFAULT;
	पूर्ण अन्यथा अणु
		u8 mode;

		क्रम (mode = 0; mode < 4; mode++)
			अगर (म_माला(value, tomoyo_mode[mode]))
				/*
				 * Update lower 3 bits in order to distinguish
				 * 'config' from 'TOMOYO_CONFIG_USE_DEFAULT'.
				 */
				config = (config & ~7) | mode;
		अगर (config != TOMOYO_CONFIG_USE_DEFAULT) अणु
			चयन (tomoyo_find_yesno(value, "grant_log")) अणु
			हाल 1:
				config |= TOMOYO_CONFIG_WANT_GRANT_LOG;
				अवरोध;
			हाल 0:
				config &= ~TOMOYO_CONFIG_WANT_GRANT_LOG;
				अवरोध;
			पूर्ण
			चयन (tomoyo_find_yesno(value, "reject_log")) अणु
			हाल 1:
				config |= TOMOYO_CONFIG_WANT_REJECT_LOG;
				अवरोध;
			हाल 0:
				config &= ~TOMOYO_CONFIG_WANT_REJECT_LOG;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (i < TOMOYO_MAX_MAC_INDEX + TOMOYO_MAX_MAC_CATEGORY_INDEX)
		profile->config[i] = config;
	अन्यथा अगर (config != TOMOYO_CONFIG_USE_DEFAULT)
		profile->शेष_config = config;
	वापस 0;
पूर्ण

/**
 * tomoyo_ग_लिखो_profile - Write profile table.
 *
 * @head: Poपूर्णांकer to "struct tomoyo_io_buffer".
 *
 * Returns 0 on success, negative value otherwise.
 */
अटल पूर्णांक tomoyo_ग_लिखो_profile(काष्ठा tomoyo_io_buffer *head)
अणु
	अक्षर *data = head->ग_लिखो_buf;
	अचिन्हित पूर्णांक i;
	अक्षर *cp;
	काष्ठा tomoyo_profile *profile;

	अगर (माला_पूछो(data, "PROFILE_VERSION=%u", &head->w.ns->profile_version)
	    == 1)
		वापस 0;
	i = simple_म_से_अदीर्घ(data, &cp, 10);
	अगर (*cp != '-')
		वापस -EINVAL;
	data = cp + 1;
	profile = tomoyo_assign_profile(head->w.ns, i);
	अगर (!profile)
		वापस -EINVAL;
	cp = म_अक्षर(data, '=');
	अगर (!cp)
		वापस -EINVAL;
	*cp++ = '\0';
	अगर (!म_भेद(data, "COMMENT")) अणु
		अटल DEFINE_SPINLOCK(lock);
		स्थिर काष्ठा tomoyo_path_info *new_comment
			= tomoyo_get_name(cp);
		स्थिर काष्ठा tomoyo_path_info *old_comment;

		अगर (!new_comment)
			वापस -ENOMEM;
		spin_lock(&lock);
		old_comment = profile->comment;
		profile->comment = new_comment;
		spin_unlock(&lock);
		tomoyo_put_name(old_comment);
		वापस 0;
	पूर्ण
	अगर (!म_भेद(data, "PREFERENCE")) अणु
		क्रम (i = 0; i < TOMOYO_MAX_PREF; i++)
			tomoyo_set_uपूर्णांक(&profile->pref[i], cp,
					tomoyo_pref_keywords[i]);
		वापस 0;
	पूर्ण
	वापस tomoyo_set_mode(data, cp, profile);
पूर्ण

/**
 * tomoyo_prपूर्णांक_config - Prपूर्णांक mode क्रम specअगरied functionality.
 *
 * @head:   Poपूर्णांकer to "struct tomoyo_io_buffer".
 * @config: Mode क्रम that functionality.
 *
 * Returns nothing.
 *
 * Caller prपूर्णांकs functionality's name.
 */
अटल व्योम tomoyo_prपूर्णांक_config(काष्ठा tomoyo_io_buffer *head, स्थिर u8 config)
अणु
	tomoyo_io_म_लिखो(head, "={ mode=%s grant_log=%s reject_log=%s }\n",
			 tomoyo_mode[config & 3],
			 tomoyo_yesno(config & TOMOYO_CONFIG_WANT_GRANT_LOG),
			 tomoyo_yesno(config & TOMOYO_CONFIG_WANT_REJECT_LOG));
पूर्ण

/**
 * tomoyo_पढ़ो_profile - Read profile table.
 *
 * @head: Poपूर्णांकer to "struct tomoyo_io_buffer".
 *
 * Returns nothing.
 */
अटल व्योम tomoyo_पढ़ो_profile(काष्ठा tomoyo_io_buffer *head)
अणु
	u8 index;
	काष्ठा tomoyo_policy_namespace *ns =
		container_of(head->r.ns, typeof(*ns), namespace_list);
	स्थिर काष्ठा tomoyo_profile *profile;

	अगर (head->r.eof)
		वापस;
 next:
	index = head->r.index;
	profile = ns->profile_ptr[index];
	चयन (head->r.step) अणु
	हाल 0:
		tomoyo_prपूर्णांक_namespace(head);
		tomoyo_io_म_लिखो(head, "PROFILE_VERSION=%u\n",
				 ns->profile_version);
		head->r.step++;
		अवरोध;
	हाल 1:
		क्रम ( ; head->r.index < TOMOYO_MAX_PROखाताS;
		      head->r.index++)
			अगर (ns->profile_ptr[head->r.index])
				अवरोध;
		अगर (head->r.index == TOMOYO_MAX_PROखाताS) अणु
			head->r.eof = true;
			वापस;
		पूर्ण
		head->r.step++;
		अवरोध;
	हाल 2:
		अणु
			u8 i;
			स्थिर काष्ठा tomoyo_path_info *comment =
				profile->comment;

			tomoyo_prपूर्णांक_namespace(head);
			tomoyo_io_म_लिखो(head, "%u-COMMENT=", index);
			tomoyo_set_string(head, comment ? comment->name : "");
			tomoyo_set_lf(head);
			tomoyo_prपूर्णांक_namespace(head);
			tomoyo_io_म_लिखो(head, "%u-PREFERENCE={ ", index);
			क्रम (i = 0; i < TOMOYO_MAX_PREF; i++)
				tomoyo_io_म_लिखो(head, "%s=%u ",
						 tomoyo_pref_keywords[i],
						 profile->pref[i]);
			tomoyo_set_string(head, "}\n");
			head->r.step++;
		पूर्ण
		अवरोध;
	हाल 3:
		अणु
			tomoyo_prपूर्णांक_namespace(head);
			tomoyo_io_म_लिखो(head, "%u-%s", index, "CONFIG");
			tomoyo_prपूर्णांक_config(head, profile->शेष_config);
			head->r.bit = 0;
			head->r.step++;
		पूर्ण
		अवरोध;
	हाल 4:
		क्रम ( ; head->r.bit < TOMOYO_MAX_MAC_INDEX
			      + TOMOYO_MAX_MAC_CATEGORY_INDEX; head->r.bit++) अणु
			स्थिर u8 i = head->r.bit;
			स्थिर u8 config = profile->config[i];

			अगर (config == TOMOYO_CONFIG_USE_DEFAULT)
				जारी;
			tomoyo_prपूर्णांक_namespace(head);
			अगर (i < TOMOYO_MAX_MAC_INDEX)
				tomoyo_io_म_लिखो(head, "%u-CONFIG::%s::%s",
						 index,
						 tomoyo_category_keywords
						 [tomoyo_index2category[i]],
						 tomoyo_mac_keywords[i]);
			अन्यथा
				tomoyo_io_म_लिखो(head, "%u-CONFIG::%s", index,
						 tomoyo_mac_keywords[i]);
			tomoyo_prपूर्णांक_config(head, config);
			head->r.bit++;
			अवरोध;
		पूर्ण
		अगर (head->r.bit == TOMOYO_MAX_MAC_INDEX
		    + TOMOYO_MAX_MAC_CATEGORY_INDEX) अणु
			head->r.index++;
			head->r.step = 1;
		पूर्ण
		अवरोध;
	पूर्ण
	अगर (tomoyo_flush(head))
		जाओ next;
पूर्ण

/**
 * tomoyo_same_manager - Check क्रम duplicated "struct tomoyo_manager" entry.
 *
 * @a: Poपूर्णांकer to "struct tomoyo_acl_head".
 * @b: Poपूर्णांकer to "struct tomoyo_acl_head".
 *
 * Returns true अगर @a == @b, false otherwise.
 */
अटल bool tomoyo_same_manager(स्थिर काष्ठा tomoyo_acl_head *a,
				स्थिर काष्ठा tomoyo_acl_head *b)
अणु
	वापस container_of(a, काष्ठा tomoyo_manager, head)->manager ==
		container_of(b, काष्ठा tomoyo_manager, head)->manager;
पूर्ण

/**
 * tomoyo_update_manager_entry - Add a manager entry.
 *
 * @manager:   The path to manager or the करोमुख्यnamme.
 * @is_delete: True अगर it is a delete request.
 *
 * Returns 0 on success, negative value otherwise.
 *
 * Caller holds tomoyo_पढ़ो_lock().
 */
अटल पूर्णांक tomoyo_update_manager_entry(स्थिर अक्षर *manager,
				       स्थिर bool is_delete)
अणु
	काष्ठा tomoyo_manager e = अणु पूर्ण;
	काष्ठा tomoyo_acl_param param = अणु
		/* .ns = &tomoyo_kernel_namespace, */
		.is_delete = is_delete,
		.list = &tomoyo_kernel_namespace.policy_list[TOMOYO_ID_MANAGER],
	पूर्ण;
	पूर्णांक error = is_delete ? -ENOENT : -ENOMEM;

	अगर (!tomoyo_correct_करोमुख्य(manager) &&
	    !tomoyo_correct_word(manager))
		वापस -EINVAL;
	e.manager = tomoyo_get_name(manager);
	अगर (e.manager) अणु
		error = tomoyo_update_policy(&e.head, माप(e), &param,
					     tomoyo_same_manager);
		tomoyo_put_name(e.manager);
	पूर्ण
	वापस error;
पूर्ण

/**
 * tomoyo_ग_लिखो_manager - Write manager policy.
 *
 * @head: Poपूर्णांकer to "struct tomoyo_io_buffer".
 *
 * Returns 0 on success, negative value otherwise.
 *
 * Caller holds tomoyo_पढ़ो_lock().
 */
अटल पूर्णांक tomoyo_ग_लिखो_manager(काष्ठा tomoyo_io_buffer *head)
अणु
	अक्षर *data = head->ग_लिखो_buf;

	अगर (!म_भेद(data, "manage_by_non_root")) अणु
		tomoyo_manage_by_non_root = !head->w.is_delete;
		वापस 0;
	पूर्ण
	वापस tomoyo_update_manager_entry(data, head->w.is_delete);
पूर्ण

/**
 * tomoyo_पढ़ो_manager - Read manager policy.
 *
 * @head: Poपूर्णांकer to "struct tomoyo_io_buffer".
 *
 * Caller holds tomoyo_पढ़ो_lock().
 */
अटल व्योम tomoyo_पढ़ो_manager(काष्ठा tomoyo_io_buffer *head)
अणु
	अगर (head->r.eof)
		वापस;
	list_क्रम_each_cookie(head->r.acl, &tomoyo_kernel_namespace.policy_list[TOMOYO_ID_MANAGER]) अणु
		काष्ठा tomoyo_manager *ptr =
			list_entry(head->r.acl, typeof(*ptr), head.list);

		अगर (ptr->head.is_deleted)
			जारी;
		अगर (!tomoyo_flush(head))
			वापस;
		tomoyo_set_string(head, ptr->manager->name);
		tomoyo_set_lf(head);
	पूर्ण
	head->r.eof = true;
पूर्ण

/**
 * tomoyo_manager - Check whether the current process is a policy manager.
 *
 * Returns true अगर the current process is permitted to modअगरy policy
 * via /sys/kernel/security/tomoyo/ पूर्णांकerface.
 *
 * Caller holds tomoyo_पढ़ो_lock().
 */
अटल bool tomoyo_manager(व्योम)
अणु
	काष्ठा tomoyo_manager *ptr;
	स्थिर अक्षर *exe;
	स्थिर काष्ठा task_काष्ठा *task = current;
	स्थिर काष्ठा tomoyo_path_info *करोमुख्यname = tomoyo_करोमुख्य()->करोमुख्यname;
	bool found = IS_ENABLED(CONFIG_SECURITY_TOMOYO_INSECURE_BUILTIN_SETTING);

	अगर (!tomoyo_policy_loaded)
		वापस true;
	अगर (!tomoyo_manage_by_non_root &&
	    (!uid_eq(task->cred->uid,  GLOBAL_ROOT_UID) ||
	     !uid_eq(task->cred->euid, GLOBAL_ROOT_UID)))
		वापस false;
	exe = tomoyo_get_exe();
	अगर (!exe)
		वापस false;
	list_क्रम_each_entry_rcu(ptr, &tomoyo_kernel_namespace.policy_list[TOMOYO_ID_MANAGER], head.list,
				srcu_पढ़ो_lock_held(&tomoyo_ss)) अणु
		अगर (!ptr->head.is_deleted &&
		    (!tomoyo_pathcmp(करोमुख्यname, ptr->manager) ||
		     !म_भेद(exe, ptr->manager->name))) अणु
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!found) अणु /* Reduce error messages. */
		अटल pid_t last_pid;
		स्थिर pid_t pid = current->pid;

		अगर (last_pid != pid) अणु
			pr_warn("%s ( %s ) is not permitted to update policies.\n",
				करोमुख्यname->name, exe);
			last_pid = pid;
		पूर्ण
	पूर्ण
	kमुक्त(exe);
	वापस found;
पूर्ण

अटल काष्ठा tomoyo_करोमुख्य_info *tomoyo_find_करोमुख्य_by_qid
(अचिन्हित पूर्णांक serial);

/**
 * tomoyo_select_करोमुख्य - Parse select command.
 *
 * @head: Poपूर्णांकer to "struct tomoyo_io_buffer".
 * @data: String to parse.
 *
 * Returns true on success, false otherwise.
 *
 * Caller holds tomoyo_पढ़ो_lock().
 */
अटल bool tomoyo_select_करोमुख्य(काष्ठा tomoyo_io_buffer *head,
				 स्थिर अक्षर *data)
अणु
	अचिन्हित पूर्णांक pid;
	काष्ठा tomoyo_करोमुख्य_info *करोमुख्य = शून्य;
	bool global_pid = false;

	अगर (म_भेदन(data, "select ", 7))
		वापस false;
	data += 7;
	अगर (माला_पूछो(data, "pid=%u", &pid) == 1 ||
	    (global_pid = true, माला_पूछो(data, "global-pid=%u", &pid) == 1)) अणु
		काष्ठा task_काष्ठा *p;

		rcu_पढ़ो_lock();
		अगर (global_pid)
			p = find_task_by_pid_ns(pid, &init_pid_ns);
		अन्यथा
			p = find_task_by_vpid(pid);
		अगर (p)
			करोमुख्य = tomoyo_task(p)->करोमुख्य_info;
		rcu_पढ़ो_unlock();
	पूर्ण अन्यथा अगर (!म_भेदन(data, "domain=", 7)) अणु
		अगर (tomoyo_करोमुख्य_def(data + 7))
			करोमुख्य = tomoyo_find_करोमुख्य(data + 7);
	पूर्ण अन्यथा अगर (माला_पूछो(data, "Q=%u", &pid) == 1) अणु
		करोमुख्य = tomoyo_find_करोमुख्य_by_qid(pid);
	पूर्ण अन्यथा
		वापस false;
	head->w.करोमुख्य = करोमुख्य;
	/* Accessing पढ़ो_buf is safe because head->io_sem is held. */
	अगर (!head->पढ़ो_buf)
		वापस true; /* Do nothing अगर खोलो(O_WRONLY). */
	स_रखो(&head->r, 0, माप(head->r));
	head->r.prपूर्णांक_this_करोमुख्य_only = true;
	अगर (करोमुख्य)
		head->r.करोमुख्य = &करोमुख्य->list;
	अन्यथा
		head->r.eof = true;
	tomoyo_io_म_लिखो(head, "# select %s\n", data);
	अगर (करोमुख्य && करोमुख्य->is_deleted)
		tomoyo_io_म_लिखो(head, "# This is a deleted domain.\n");
	वापस true;
पूर्ण

/**
 * tomoyo_same_task_acl - Check क्रम duplicated "struct tomoyo_task_acl" entry.
 *
 * @a: Poपूर्णांकer to "struct tomoyo_acl_info".
 * @b: Poपूर्णांकer to "struct tomoyo_acl_info".
 *
 * Returns true अगर @a == @b, false otherwise.
 */
अटल bool tomoyo_same_task_acl(स्थिर काष्ठा tomoyo_acl_info *a,
				 स्थिर काष्ठा tomoyo_acl_info *b)
अणु
	स्थिर काष्ठा tomoyo_task_acl *p1 = container_of(a, typeof(*p1), head);
	स्थिर काष्ठा tomoyo_task_acl *p2 = container_of(b, typeof(*p2), head);

	वापस p1->करोमुख्यname == p2->करोमुख्यname;
पूर्ण

/**
 * tomoyo_ग_लिखो_task - Update task related list.
 *
 * @param: Poपूर्णांकer to "struct tomoyo_acl_param".
 *
 * Returns 0 on success, negative value otherwise.
 *
 * Caller holds tomoyo_पढ़ो_lock().
 */
अटल पूर्णांक tomoyo_ग_लिखो_task(काष्ठा tomoyo_acl_param *param)
अणु
	पूर्णांक error = -EINVAL;

	अगर (tomoyo_str_starts(&param->data, "manual_domain_transition ")) अणु
		काष्ठा tomoyo_task_acl e = अणु
			.head.type = TOMOYO_TYPE_MANUAL_TASK_ACL,
			.करोमुख्यname = tomoyo_get_करोमुख्यname(param),
		पूर्ण;

		अगर (e.करोमुख्यname)
			error = tomoyo_update_करोमुख्य(&e.head, माप(e), param,
						     tomoyo_same_task_acl,
						     शून्य);
		tomoyo_put_name(e.करोमुख्यname);
	पूर्ण
	वापस error;
पूर्ण

/**
 * tomoyo_delete_करोमुख्य - Delete a करोमुख्य.
 *
 * @करोमुख्यname: The name of करोमुख्य.
 *
 * Returns 0 on success, negative value otherwise.
 *
 * Caller holds tomoyo_पढ़ो_lock().
 */
अटल पूर्णांक tomoyo_delete_करोमुख्य(अक्षर *करोमुख्यname)
अणु
	काष्ठा tomoyo_करोमुख्य_info *करोमुख्य;
	काष्ठा tomoyo_path_info name;

	name.name = करोमुख्यname;
	tomoyo_fill_path_info(&name);
	अगर (mutex_lock_पूर्णांकerruptible(&tomoyo_policy_lock))
		वापस -EINTR;
	/* Is there an active करोमुख्य? */
	list_क्रम_each_entry_rcu(करोमुख्य, &tomoyo_करोमुख्य_list, list,
				srcu_पढ़ो_lock_held(&tomoyo_ss)) अणु
		/* Never delete tomoyo_kernel_करोमुख्य */
		अगर (करोमुख्य == &tomoyo_kernel_करोमुख्य)
			जारी;
		अगर (करोमुख्य->is_deleted ||
		    tomoyo_pathcmp(करोमुख्य->करोमुख्यname, &name))
			जारी;
		करोमुख्य->is_deleted = true;
		अवरोध;
	पूर्ण
	mutex_unlock(&tomoyo_policy_lock);
	वापस 0;
पूर्ण

/**
 * tomoyo_ग_लिखो_करोमुख्य2 - Write करोमुख्य policy.
 *
 * @ns:        Poपूर्णांकer to "struct tomoyo_policy_namespace".
 * @list:      Poपूर्णांकer to "struct list_head".
 * @data:      Policy to be पूर्णांकerpreted.
 * @is_delete: True अगर it is a delete request.
 *
 * Returns 0 on success, negative value otherwise.
 *
 * Caller holds tomoyo_पढ़ो_lock().
 */
अटल पूर्णांक tomoyo_ग_लिखो_करोमुख्य2(काष्ठा tomoyo_policy_namespace *ns,
				काष्ठा list_head *list, अक्षर *data,
				स्थिर bool is_delete)
अणु
	काष्ठा tomoyo_acl_param param = अणु
		.ns = ns,
		.list = list,
		.data = data,
		.is_delete = is_delete,
	पूर्ण;
	अटल स्थिर काष्ठा अणु
		स्थिर अक्षर *keyword;
		पूर्णांक (*ग_लिखो)(काष्ठा tomoyo_acl_param *param);
	पूर्ण tomoyo_callback[5] = अणु
		अणु "file ", tomoyo_ग_लिखो_file पूर्ण,
		अणु "network inet ", tomoyo_ग_लिखो_inet_network पूर्ण,
		अणु "network unix ", tomoyo_ग_लिखो_unix_network पूर्ण,
		अणु "misc ", tomoyo_ग_लिखो_misc पूर्ण,
		अणु "task ", tomoyo_ग_लिखो_task पूर्ण,
	पूर्ण;
	u8 i;

	क्रम (i = 0; i < ARRAY_SIZE(tomoyo_callback); i++) अणु
		अगर (!tomoyo_str_starts(&param.data,
				       tomoyo_callback[i].keyword))
			जारी;
		वापस tomoyo_callback[i].ग_लिखो(&param);
	पूर्ण
	वापस -EINVAL;
पूर्ण

/* String table क्रम करोमुख्य flags. */
स्थिर अक्षर * स्थिर tomoyo_dअगर[TOMOYO_MAX_DOMAIN_INFO_FLAGS] = अणु
	[TOMOYO_DIF_QUOTA_WARNED]      = "quota_exceeded\n",
	[TOMOYO_DIF_TRANSITION_FAILED] = "transition_failed\n",
पूर्ण;

/**
 * tomoyo_ग_लिखो_करोमुख्य - Write करोमुख्य policy.
 *
 * @head: Poपूर्णांकer to "struct tomoyo_io_buffer".
 *
 * Returns 0 on success, negative value otherwise.
 *
 * Caller holds tomoyo_पढ़ो_lock().
 */
अटल पूर्णांक tomoyo_ग_लिखो_करोमुख्य(काष्ठा tomoyo_io_buffer *head)
अणु
	अक्षर *data = head->ग_लिखो_buf;
	काष्ठा tomoyo_policy_namespace *ns;
	काष्ठा tomoyo_करोमुख्य_info *करोमुख्य = head->w.करोमुख्य;
	स्थिर bool is_delete = head->w.is_delete;
	bool is_select = !is_delete && tomoyo_str_starts(&data, "select ");
	अचिन्हित पूर्णांक idx;

	अगर (*data == '<') अणु
		पूर्णांक ret = 0;

		करोमुख्य = शून्य;
		अगर (is_delete)
			ret = tomoyo_delete_करोमुख्य(data);
		अन्यथा अगर (is_select)
			करोमुख्य = tomoyo_find_करोमुख्य(data);
		अन्यथा
			करोमुख्य = tomoyo_assign_करोमुख्य(data, false);
		head->w.करोमुख्य = करोमुख्य;
		वापस ret;
	पूर्ण
	अगर (!करोमुख्य)
		वापस -EINVAL;
	ns = करोमुख्य->ns;
	अगर (माला_पूछो(data, "use_profile %u", &idx) == 1
	    && idx < TOMOYO_MAX_PROखाताS) अणु
		अगर (!tomoyo_policy_loaded || ns->profile_ptr[idx])
			अगर (!is_delete)
				करोमुख्य->profile = (u8) idx;
		वापस 0;
	पूर्ण
	अगर (माला_पूछो(data, "use_group %u\n", &idx) == 1
	    && idx < TOMOYO_MAX_ACL_GROUPS) अणु
		अगर (!is_delete)
			set_bit(idx, करोमुख्य->group);
		अन्यथा
			clear_bit(idx, करोमुख्य->group);
		वापस 0;
	पूर्ण
	क्रम (idx = 0; idx < TOMOYO_MAX_DOMAIN_INFO_FLAGS; idx++) अणु
		स्थिर अक्षर *cp = tomoyo_dअगर[idx];

		अगर (म_भेदन(data, cp, म_माप(cp) - 1))
			जारी;
		करोमुख्य->flags[idx] = !is_delete;
		वापस 0;
	पूर्ण
	वापस tomoyo_ग_लिखो_करोमुख्य2(ns, &करोमुख्य->acl_info_list, data,
				    is_delete);
पूर्ण

/**
 * tomoyo_prपूर्णांक_condition - Prपूर्णांक condition part.
 *
 * @head: Poपूर्णांकer to "struct tomoyo_io_buffer".
 * @cond: Poपूर्णांकer to "struct tomoyo_condition".
 *
 * Returns true on success, false otherwise.
 */
अटल bool tomoyo_prपूर्णांक_condition(काष्ठा tomoyo_io_buffer *head,
				   स्थिर काष्ठा tomoyo_condition *cond)
अणु
	चयन (head->r.cond_step) अणु
	हाल 0:
		head->r.cond_index = 0;
		head->r.cond_step++;
		अगर (cond->transit) अणु
			tomoyo_set_space(head);
			tomoyo_set_string(head, cond->transit->name);
		पूर्ण
		fallthrough;
	हाल 1:
		अणु
			स्थिर u16 condc = cond->condc;
			स्थिर काष्ठा tomoyo_condition_element *condp =
				(typeof(condp)) (cond + 1);
			स्थिर काष्ठा tomoyo_number_जोड़ *numbers_p =
				(typeof(numbers_p)) (condp + condc);
			स्थिर काष्ठा tomoyo_name_जोड़ *names_p =
				(typeof(names_p))
				(numbers_p + cond->numbers_count);
			स्थिर काष्ठा tomoyo_argv *argv =
				(typeof(argv)) (names_p + cond->names_count);
			स्थिर काष्ठा tomoyo_envp *envp =
				(typeof(envp)) (argv + cond->argc);
			u16 skip;

			क्रम (skip = 0; skip < head->r.cond_index; skip++) अणु
				स्थिर u8 left = condp->left;
				स्थिर u8 right = condp->right;

				condp++;
				चयन (left) अणु
				हाल TOMOYO_ARGV_ENTRY:
					argv++;
					जारी;
				हाल TOMOYO_ENVP_ENTRY:
					envp++;
					जारी;
				हाल TOMOYO_NUMBER_UNION:
					numbers_p++;
					अवरोध;
				पूर्ण
				चयन (right) अणु
				हाल TOMOYO_NAME_UNION:
					names_p++;
					अवरोध;
				हाल TOMOYO_NUMBER_UNION:
					numbers_p++;
					अवरोध;
				पूर्ण
			पूर्ण
			जबतक (head->r.cond_index < condc) अणु
				स्थिर u8 match = condp->equals;
				स्थिर u8 left = condp->left;
				स्थिर u8 right = condp->right;

				अगर (!tomoyo_flush(head))
					वापस false;
				condp++;
				head->r.cond_index++;
				tomoyo_set_space(head);
				चयन (left) अणु
				हाल TOMOYO_ARGV_ENTRY:
					tomoyo_io_म_लिखो(head,
							 "exec.argv[%lu]%s=\"",
							 argv->index, argv->is_not ? "!" : "");
					tomoyo_set_string(head,
							  argv->value->name);
					tomoyo_set_string(head, "\"");
					argv++;
					जारी;
				हाल TOMOYO_ENVP_ENTRY:
					tomoyo_set_string(head,
							  "exec.envp[\"");
					tomoyo_set_string(head,
							  envp->name->name);
					tomoyo_io_म_लिखो(head, "\"]%s=", envp->is_not ? "!" : "");
					अगर (envp->value) अणु
						tomoyo_set_string(head, "\"");
						tomoyo_set_string(head, envp->value->name);
						tomoyo_set_string(head, "\"");
					पूर्ण अन्यथा अणु
						tomoyo_set_string(head,
								  "NULL");
					पूर्ण
					envp++;
					जारी;
				हाल TOMOYO_NUMBER_UNION:
					tomoyo_prपूर्णांक_number_जोड़_nospace
						(head, numbers_p++);
					अवरोध;
				शेष:
					tomoyo_set_string(head,
					       tomoyo_condition_keyword[left]);
					अवरोध;
				पूर्ण
				tomoyo_set_string(head, match ? "=" : "!=");
				चयन (right) अणु
				हाल TOMOYO_NAME_UNION:
					tomoyo_prपूर्णांक_name_जोड़_quoted
						(head, names_p++);
					अवरोध;
				हाल TOMOYO_NUMBER_UNION:
					tomoyo_prपूर्णांक_number_जोड़_nospace
						(head, numbers_p++);
					अवरोध;
				शेष:
					tomoyo_set_string(head,
					  tomoyo_condition_keyword[right]);
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
		head->r.cond_step++;
		fallthrough;
	हाल 2:
		अगर (!tomoyo_flush(head))
			अवरोध;
		head->r.cond_step++;
		fallthrough;
	हाल 3:
		अगर (cond->grant_log != TOMOYO_GRANTLOG_AUTO)
			tomoyo_io_म_लिखो(head, " grant_log=%s",
					 tomoyo_yesno(cond->grant_log ==
						      TOMOYO_GRANTLOG_YES));
		tomoyo_set_lf(head);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

/**
 * tomoyo_set_group - Prपूर्णांक "acl_group " header keyword and category name.
 *
 * @head:     Poपूर्णांकer to "struct tomoyo_io_buffer".
 * @category: Category name.
 *
 * Returns nothing.
 */
अटल व्योम tomoyo_set_group(काष्ठा tomoyo_io_buffer *head,
			     स्थिर अक्षर *category)
अणु
	अगर (head->type == TOMOYO_EXCEPTIONPOLICY) अणु
		tomoyo_prपूर्णांक_namespace(head);
		tomoyo_io_म_लिखो(head, "acl_group %u ",
				 head->r.acl_group_index);
	पूर्ण
	tomoyo_set_string(head, category);
पूर्ण

/**
 * tomoyo_prपूर्णांक_entry - Prपूर्णांक an ACL entry.
 *
 * @head: Poपूर्णांकer to "struct tomoyo_io_buffer".
 * @acl:  Poपूर्णांकer to an ACL entry.
 *
 * Returns true on success, false otherwise.
 */
अटल bool tomoyo_prपूर्णांक_entry(काष्ठा tomoyo_io_buffer *head,
			       काष्ठा tomoyo_acl_info *acl)
अणु
	स्थिर u8 acl_type = acl->type;
	bool first = true;
	u8 bit;

	अगर (head->r.prपूर्णांक_cond_part)
		जाओ prपूर्णांक_cond_part;
	अगर (acl->is_deleted)
		वापस true;
	अगर (!tomoyo_flush(head))
		वापस false;
	अन्यथा अगर (acl_type == TOMOYO_TYPE_PATH_ACL) अणु
		काष्ठा tomoyo_path_acl *ptr =
			container_of(acl, typeof(*ptr), head);
		स्थिर u16 perm = ptr->perm;

		क्रम (bit = 0; bit < TOMOYO_MAX_PATH_OPERATION; bit++) अणु
			अगर (!(perm & (1 << bit)))
				जारी;
			अगर (head->r.prपूर्णांक_transition_related_only &&
			    bit != TOMOYO_TYPE_EXECUTE)
				जारी;
			अगर (first) अणु
				tomoyo_set_group(head, "file ");
				first = false;
			पूर्ण अन्यथा अणु
				tomoyo_set_slash(head);
			पूर्ण
			tomoyo_set_string(head, tomoyo_path_keyword[bit]);
		पूर्ण
		अगर (first)
			वापस true;
		tomoyo_prपूर्णांक_name_जोड़(head, &ptr->name);
	पूर्ण अन्यथा अगर (acl_type == TOMOYO_TYPE_MANUAL_TASK_ACL) अणु
		काष्ठा tomoyo_task_acl *ptr =
			container_of(acl, typeof(*ptr), head);

		tomoyo_set_group(head, "task ");
		tomoyo_set_string(head, "manual_domain_transition ");
		tomoyo_set_string(head, ptr->करोमुख्यname->name);
	पूर्ण अन्यथा अगर (head->r.prपूर्णांक_transition_related_only) अणु
		वापस true;
	पूर्ण अन्यथा अगर (acl_type == TOMOYO_TYPE_PATH2_ACL) अणु
		काष्ठा tomoyo_path2_acl *ptr =
			container_of(acl, typeof(*ptr), head);
		स्थिर u8 perm = ptr->perm;

		क्रम (bit = 0; bit < TOMOYO_MAX_PATH2_OPERATION; bit++) अणु
			अगर (!(perm & (1 << bit)))
				जारी;
			अगर (first) अणु
				tomoyo_set_group(head, "file ");
				first = false;
			पूर्ण अन्यथा अणु
				tomoyo_set_slash(head);
			पूर्ण
			tomoyo_set_string(head, tomoyo_mac_keywords
					  [tomoyo_pp2mac[bit]]);
		पूर्ण
		अगर (first)
			वापस true;
		tomoyo_prपूर्णांक_name_जोड़(head, &ptr->name1);
		tomoyo_prपूर्णांक_name_जोड़(head, &ptr->name2);
	पूर्ण अन्यथा अगर (acl_type == TOMOYO_TYPE_PATH_NUMBER_ACL) अणु
		काष्ठा tomoyo_path_number_acl *ptr =
			container_of(acl, typeof(*ptr), head);
		स्थिर u8 perm = ptr->perm;

		क्रम (bit = 0; bit < TOMOYO_MAX_PATH_NUMBER_OPERATION; bit++) अणु
			अगर (!(perm & (1 << bit)))
				जारी;
			अगर (first) अणु
				tomoyo_set_group(head, "file ");
				first = false;
			पूर्ण अन्यथा अणु
				tomoyo_set_slash(head);
			पूर्ण
			tomoyo_set_string(head, tomoyo_mac_keywords
					  [tomoyo_pn2mac[bit]]);
		पूर्ण
		अगर (first)
			वापस true;
		tomoyo_prपूर्णांक_name_जोड़(head, &ptr->name);
		tomoyo_prपूर्णांक_number_जोड़(head, &ptr->number);
	पूर्ण अन्यथा अगर (acl_type == TOMOYO_TYPE_MKDEV_ACL) अणु
		काष्ठा tomoyo_mkdev_acl *ptr =
			container_of(acl, typeof(*ptr), head);
		स्थिर u8 perm = ptr->perm;

		क्रम (bit = 0; bit < TOMOYO_MAX_MKDEV_OPERATION; bit++) अणु
			अगर (!(perm & (1 << bit)))
				जारी;
			अगर (first) अणु
				tomoyo_set_group(head, "file ");
				first = false;
			पूर्ण अन्यथा अणु
				tomoyo_set_slash(head);
			पूर्ण
			tomoyo_set_string(head, tomoyo_mac_keywords
					  [tomoyo_pnnn2mac[bit]]);
		पूर्ण
		अगर (first)
			वापस true;
		tomoyo_prपूर्णांक_name_जोड़(head, &ptr->name);
		tomoyo_prपूर्णांक_number_जोड़(head, &ptr->mode);
		tomoyo_prपूर्णांक_number_जोड़(head, &ptr->major);
		tomoyo_prपूर्णांक_number_जोड़(head, &ptr->minor);
	पूर्ण अन्यथा अगर (acl_type == TOMOYO_TYPE_INET_ACL) अणु
		काष्ठा tomoyo_inet_acl *ptr =
			container_of(acl, typeof(*ptr), head);
		स्थिर u8 perm = ptr->perm;

		क्रम (bit = 0; bit < TOMOYO_MAX_NETWORK_OPERATION; bit++) अणु
			अगर (!(perm & (1 << bit)))
				जारी;
			अगर (first) अणु
				tomoyo_set_group(head, "network inet ");
				tomoyo_set_string(head, tomoyo_proto_keyword
						  [ptr->protocol]);
				tomoyo_set_space(head);
				first = false;
			पूर्ण अन्यथा अणु
				tomoyo_set_slash(head);
			पूर्ण
			tomoyo_set_string(head, tomoyo_socket_keyword[bit]);
		पूर्ण
		अगर (first)
			वापस true;
		tomoyo_set_space(head);
		अगर (ptr->address.group) अणु
			tomoyo_set_string(head, "@");
			tomoyo_set_string(head, ptr->address.group->group_name
					  ->name);
		पूर्ण अन्यथा अणु
			अक्षर buf[128];

			tomoyo_prपूर्णांक_ip(buf, माप(buf), &ptr->address);
			tomoyo_io_म_लिखो(head, "%s", buf);
		पूर्ण
		tomoyo_prपूर्णांक_number_जोड़(head, &ptr->port);
	पूर्ण अन्यथा अगर (acl_type == TOMOYO_TYPE_UNIX_ACL) अणु
		काष्ठा tomoyo_unix_acl *ptr =
			container_of(acl, typeof(*ptr), head);
		स्थिर u8 perm = ptr->perm;

		क्रम (bit = 0; bit < TOMOYO_MAX_NETWORK_OPERATION; bit++) अणु
			अगर (!(perm & (1 << bit)))
				जारी;
			अगर (first) अणु
				tomoyo_set_group(head, "network unix ");
				tomoyo_set_string(head, tomoyo_proto_keyword
						  [ptr->protocol]);
				tomoyo_set_space(head);
				first = false;
			पूर्ण अन्यथा अणु
				tomoyo_set_slash(head);
			पूर्ण
			tomoyo_set_string(head, tomoyo_socket_keyword[bit]);
		पूर्ण
		अगर (first)
			वापस true;
		tomoyo_prपूर्णांक_name_जोड़(head, &ptr->name);
	पूर्ण अन्यथा अगर (acl_type == TOMOYO_TYPE_MOUNT_ACL) अणु
		काष्ठा tomoyo_mount_acl *ptr =
			container_of(acl, typeof(*ptr), head);

		tomoyo_set_group(head, "file mount");
		tomoyo_prपूर्णांक_name_जोड़(head, &ptr->dev_name);
		tomoyo_prपूर्णांक_name_जोड़(head, &ptr->dir_name);
		tomoyo_prपूर्णांक_name_जोड़(head, &ptr->fs_type);
		tomoyo_prपूर्णांक_number_जोड़(head, &ptr->flags);
	पूर्ण अन्यथा अगर (acl_type == TOMOYO_TYPE_ENV_ACL) अणु
		काष्ठा tomoyo_env_acl *ptr =
			container_of(acl, typeof(*ptr), head);

		tomoyo_set_group(head, "misc env ");
		tomoyo_set_string(head, ptr->env->name);
	पूर्ण
	अगर (acl->cond) अणु
		head->r.prपूर्णांक_cond_part = true;
		head->r.cond_step = 0;
		अगर (!tomoyo_flush(head))
			वापस false;
prपूर्णांक_cond_part:
		अगर (!tomoyo_prपूर्णांक_condition(head, acl->cond))
			वापस false;
		head->r.prपूर्णांक_cond_part = false;
	पूर्ण अन्यथा अणु
		tomoyo_set_lf(head);
	पूर्ण
	वापस true;
पूर्ण

/**
 * tomoyo_पढ़ो_करोमुख्य2 - Read करोमुख्य policy.
 *
 * @head: Poपूर्णांकer to "struct tomoyo_io_buffer".
 * @list: Poपूर्णांकer to "struct list_head".
 *
 * Caller holds tomoyo_पढ़ो_lock().
 *
 * Returns true on success, false otherwise.
 */
अटल bool tomoyo_पढ़ो_करोमुख्य2(काष्ठा tomoyo_io_buffer *head,
				काष्ठा list_head *list)
अणु
	list_क्रम_each_cookie(head->r.acl, list) अणु
		काष्ठा tomoyo_acl_info *ptr =
			list_entry(head->r.acl, typeof(*ptr), list);

		अगर (!tomoyo_prपूर्णांक_entry(head, ptr))
			वापस false;
	पूर्ण
	head->r.acl = शून्य;
	वापस true;
पूर्ण

/**
 * tomoyo_पढ़ो_करोमुख्य - Read करोमुख्य policy.
 *
 * @head: Poपूर्णांकer to "struct tomoyo_io_buffer".
 *
 * Caller holds tomoyo_पढ़ो_lock().
 */
अटल व्योम tomoyo_पढ़ो_करोमुख्य(काष्ठा tomoyo_io_buffer *head)
अणु
	अगर (head->r.eof)
		वापस;
	list_क्रम_each_cookie(head->r.करोमुख्य, &tomoyo_करोमुख्य_list) अणु
		काष्ठा tomoyo_करोमुख्य_info *करोमुख्य =
			list_entry(head->r.करोमुख्य, typeof(*करोमुख्य), list);
		u8 i;

		चयन (head->r.step) अणु
		हाल 0:
			अगर (करोमुख्य->is_deleted &&
			    !head->r.prपूर्णांक_this_करोमुख्य_only)
				जारी;
			/* Prपूर्णांक करोमुख्यname and flags. */
			tomoyo_set_string(head, करोमुख्य->करोमुख्यname->name);
			tomoyo_set_lf(head);
			tomoyo_io_म_लिखो(head, "use_profile %u\n",
					 करोमुख्य->profile);
			क्रम (i = 0; i < TOMOYO_MAX_DOMAIN_INFO_FLAGS; i++)
				अगर (करोमुख्य->flags[i])
					tomoyo_set_string(head, tomoyo_dअगर[i]);
			head->r.index = 0;
			head->r.step++;
			fallthrough;
		हाल 1:
			जबतक (head->r.index < TOMOYO_MAX_ACL_GROUPS) अणु
				i = head->r.index++;
				अगर (!test_bit(i, करोमुख्य->group))
					जारी;
				tomoyo_io_म_लिखो(head, "use_group %u\n", i);
				अगर (!tomoyo_flush(head))
					वापस;
			पूर्ण
			head->r.index = 0;
			head->r.step++;
			tomoyo_set_lf(head);
			fallthrough;
		हाल 2:
			अगर (!tomoyo_पढ़ो_करोमुख्य2(head, &करोमुख्य->acl_info_list))
				वापस;
			head->r.step++;
			अगर (!tomoyo_set_lf(head))
				वापस;
			fallthrough;
		हाल 3:
			head->r.step = 0;
			अगर (head->r.prपूर्णांक_this_करोमुख्य_only)
				जाओ करोne;
		पूर्ण
	पूर्ण
 करोne:
	head->r.eof = true;
पूर्ण

/**
 * tomoyo_ग_लिखो_pid: Specअगरy PID to obtain करोमुख्यname.
 *
 * @head: Poपूर्णांकer to "struct tomoyo_io_buffer".
 *
 * Returns 0.
 */
अटल पूर्णांक tomoyo_ग_लिखो_pid(काष्ठा tomoyo_io_buffer *head)
अणु
	head->r.eof = false;
	वापस 0;
पूर्ण

/**
 * tomoyo_पढ़ो_pid - Get करोमुख्यname of the specअगरied PID.
 *
 * @head: Poपूर्णांकer to "struct tomoyo_io_buffer".
 *
 * Returns the करोमुख्यname which the specअगरied PID is in on success,
 * empty string otherwise.
 * The PID is specअगरied by tomoyo_ग_लिखो_pid() so that the user can obtain
 * using पढ़ो()/ग_लिखो() पूर्णांकerface rather than sysctl() पूर्णांकerface.
 */
अटल व्योम tomoyo_पढ़ो_pid(काष्ठा tomoyo_io_buffer *head)
अणु
	अक्षर *buf = head->ग_लिखो_buf;
	bool global_pid = false;
	अचिन्हित पूर्णांक pid;
	काष्ठा task_काष्ठा *p;
	काष्ठा tomoyo_करोमुख्य_info *करोमुख्य = शून्य;

	/* Accessing ग_लिखो_buf is safe because head->io_sem is held. */
	अगर (!buf) अणु
		head->r.eof = true;
		वापस; /* Do nothing अगर खोलो(O_RDONLY). */
	पूर्ण
	अगर (head->r.w_pos || head->r.eof)
		वापस;
	head->r.eof = true;
	अगर (tomoyo_str_starts(&buf, "global-pid "))
		global_pid = true;
	अगर (kstrtouपूर्णांक(buf, 10, &pid))
		वापस;
	rcu_पढ़ो_lock();
	अगर (global_pid)
		p = find_task_by_pid_ns(pid, &init_pid_ns);
	अन्यथा
		p = find_task_by_vpid(pid);
	अगर (p)
		करोमुख्य = tomoyo_task(p)->करोमुख्य_info;
	rcu_पढ़ो_unlock();
	अगर (!करोमुख्य)
		वापस;
	tomoyo_io_म_लिखो(head, "%u %u ", pid, करोमुख्य->profile);
	tomoyo_set_string(head, करोमुख्य->करोमुख्यname->name);
पूर्ण

/* String table क्रम करोमुख्य transition control keywords. */
अटल स्थिर अक्षर *tomoyo_transition_type[TOMOYO_MAX_TRANSITION_TYPE] = अणु
	[TOMOYO_TRANSITION_CONTROL_NO_RESET]      = "no_reset_domain ",
	[TOMOYO_TRANSITION_CONTROL_RESET]         = "reset_domain ",
	[TOMOYO_TRANSITION_CONTROL_NO_INITIALIZE] = "no_initialize_domain ",
	[TOMOYO_TRANSITION_CONTROL_INITIALIZE]    = "initialize_domain ",
	[TOMOYO_TRANSITION_CONTROL_NO_KEEP]       = "no_keep_domain ",
	[TOMOYO_TRANSITION_CONTROL_KEEP]          = "keep_domain ",
पूर्ण;

/* String table क्रम grouping keywords. */
अटल स्थिर अक्षर *tomoyo_group_name[TOMOYO_MAX_GROUP] = अणु
	[TOMOYO_PATH_GROUP]    = "path_group ",
	[TOMOYO_NUMBER_GROUP]  = "number_group ",
	[TOMOYO_ADDRESS_GROUP] = "address_group ",
पूर्ण;

/**
 * tomoyo_ग_लिखो_exception - Write exception policy.
 *
 * @head: Poपूर्णांकer to "struct tomoyo_io_buffer".
 *
 * Returns 0 on success, negative value otherwise.
 *
 * Caller holds tomoyo_पढ़ो_lock().
 */
अटल पूर्णांक tomoyo_ग_लिखो_exception(काष्ठा tomoyo_io_buffer *head)
अणु
	स्थिर bool is_delete = head->w.is_delete;
	काष्ठा tomoyo_acl_param param = अणु
		.ns = head->w.ns,
		.is_delete = is_delete,
		.data = head->ग_लिखो_buf,
	पूर्ण;
	u8 i;

	अगर (tomoyo_str_starts(&param.data, "aggregator "))
		वापस tomoyo_ग_लिखो_aggregator(&param);
	क्रम (i = 0; i < TOMOYO_MAX_TRANSITION_TYPE; i++)
		अगर (tomoyo_str_starts(&param.data, tomoyo_transition_type[i]))
			वापस tomoyo_ग_लिखो_transition_control(&param, i);
	क्रम (i = 0; i < TOMOYO_MAX_GROUP; i++)
		अगर (tomoyo_str_starts(&param.data, tomoyo_group_name[i]))
			वापस tomoyo_ग_लिखो_group(&param, i);
	अगर (tomoyo_str_starts(&param.data, "acl_group ")) अणु
		अचिन्हित पूर्णांक group;
		अक्षर *data;

		group = simple_म_से_अदीर्घ(param.data, &data, 10);
		अगर (group < TOMOYO_MAX_ACL_GROUPS && *data++ == ' ')
			वापस tomoyo_ग_लिखो_करोमुख्य2
				(head->w.ns, &head->w.ns->acl_group[group],
				 data, is_delete);
	पूर्ण
	वापस -EINVAL;
पूर्ण

/**
 * tomoyo_पढ़ो_group - Read "struct tomoyo_path_group"/"struct tomoyo_number_group"/"struct tomoyo_address_group" list.
 *
 * @head: Poपूर्णांकer to "struct tomoyo_io_buffer".
 * @idx:  Index number.
 *
 * Returns true on success, false otherwise.
 *
 * Caller holds tomoyo_पढ़ो_lock().
 */
अटल bool tomoyo_पढ़ो_group(काष्ठा tomoyo_io_buffer *head, स्थिर पूर्णांक idx)
अणु
	काष्ठा tomoyo_policy_namespace *ns =
		container_of(head->r.ns, typeof(*ns), namespace_list);
	काष्ठा list_head *list = &ns->group_list[idx];

	list_क्रम_each_cookie(head->r.group, list) अणु
		काष्ठा tomoyo_group *group =
			list_entry(head->r.group, typeof(*group), head.list);

		list_क्रम_each_cookie(head->r.acl, &group->member_list) अणु
			काष्ठा tomoyo_acl_head *ptr =
				list_entry(head->r.acl, typeof(*ptr), list);

			अगर (ptr->is_deleted)
				जारी;
			अगर (!tomoyo_flush(head))
				वापस false;
			tomoyo_prपूर्णांक_namespace(head);
			tomoyo_set_string(head, tomoyo_group_name[idx]);
			tomoyo_set_string(head, group->group_name->name);
			अगर (idx == TOMOYO_PATH_GROUP) अणु
				tomoyo_set_space(head);
				tomoyo_set_string(head, container_of
					       (ptr, काष्ठा tomoyo_path_group,
						head)->member_name->name);
			पूर्ण अन्यथा अगर (idx == TOMOYO_NUMBER_GROUP) अणु
				tomoyo_prपूर्णांक_number_जोड़(head, &container_of
							  (ptr,
						   काष्ठा tomoyo_number_group,
							   head)->number);
			पूर्ण अन्यथा अगर (idx == TOMOYO_ADDRESS_GROUP) अणु
				अक्षर buffer[128];
				काष्ठा tomoyo_address_group *member =
					container_of(ptr, typeof(*member),
						     head);

				tomoyo_prपूर्णांक_ip(buffer, माप(buffer),
						&member->address);
				tomoyo_io_म_लिखो(head, " %s", buffer);
			पूर्ण
			tomoyo_set_lf(head);
		पूर्ण
		head->r.acl = शून्य;
	पूर्ण
	head->r.group = शून्य;
	वापस true;
पूर्ण

/**
 * tomoyo_पढ़ो_policy - Read "struct tomoyo_..._entry" list.
 *
 * @head: Poपूर्णांकer to "struct tomoyo_io_buffer".
 * @idx:  Index number.
 *
 * Returns true on success, false otherwise.
 *
 * Caller holds tomoyo_पढ़ो_lock().
 */
अटल bool tomoyo_पढ़ो_policy(काष्ठा tomoyo_io_buffer *head, स्थिर पूर्णांक idx)
अणु
	काष्ठा tomoyo_policy_namespace *ns =
		container_of(head->r.ns, typeof(*ns), namespace_list);
	काष्ठा list_head *list = &ns->policy_list[idx];

	list_क्रम_each_cookie(head->r.acl, list) अणु
		काष्ठा tomoyo_acl_head *acl =
			container_of(head->r.acl, typeof(*acl), list);
		अगर (acl->is_deleted)
			जारी;
		अगर (!tomoyo_flush(head))
			वापस false;
		चयन (idx) अणु
		हाल TOMOYO_ID_TRANSITION_CONTROL:
			अणु
				काष्ठा tomoyo_transition_control *ptr =
					container_of(acl, typeof(*ptr), head);

				tomoyo_prपूर्णांक_namespace(head);
				tomoyo_set_string(head, tomoyo_transition_type
						  [ptr->type]);
				tomoyo_set_string(head, ptr->program ?
						  ptr->program->name : "any");
				tomoyo_set_string(head, " from ");
				tomoyo_set_string(head, ptr->करोमुख्यname ?
						  ptr->करोमुख्यname->name :
						  "any");
			पूर्ण
			अवरोध;
		हाल TOMOYO_ID_AGGREGATOR:
			अणु
				काष्ठा tomoyo_aggregator *ptr =
					container_of(acl, typeof(*ptr), head);

				tomoyo_prपूर्णांक_namespace(head);
				tomoyo_set_string(head, "aggregator ");
				tomoyo_set_string(head,
						  ptr->original_name->name);
				tomoyo_set_space(head);
				tomoyo_set_string(head,
					       ptr->aggregated_name->name);
			पूर्ण
			अवरोध;
		शेष:
			जारी;
		पूर्ण
		tomoyo_set_lf(head);
	पूर्ण
	head->r.acl = शून्य;
	वापस true;
पूर्ण

/**
 * tomoyo_पढ़ो_exception - Read exception policy.
 *
 * @head: Poपूर्णांकer to "struct tomoyo_io_buffer".
 *
 * Caller holds tomoyo_पढ़ो_lock().
 */
अटल व्योम tomoyo_पढ़ो_exception(काष्ठा tomoyo_io_buffer *head)
अणु
	काष्ठा tomoyo_policy_namespace *ns =
		container_of(head->r.ns, typeof(*ns), namespace_list);

	अगर (head->r.eof)
		वापस;
	जबतक (head->r.step < TOMOYO_MAX_POLICY &&
	       tomoyo_पढ़ो_policy(head, head->r.step))
		head->r.step++;
	अगर (head->r.step < TOMOYO_MAX_POLICY)
		वापस;
	जबतक (head->r.step < TOMOYO_MAX_POLICY + TOMOYO_MAX_GROUP &&
	       tomoyo_पढ़ो_group(head, head->r.step - TOMOYO_MAX_POLICY))
		head->r.step++;
	अगर (head->r.step < TOMOYO_MAX_POLICY + TOMOYO_MAX_GROUP)
		वापस;
	जबतक (head->r.step < TOMOYO_MAX_POLICY + TOMOYO_MAX_GROUP
	       + TOMOYO_MAX_ACL_GROUPS) अणु
		head->r.acl_group_index = head->r.step - TOMOYO_MAX_POLICY
			- TOMOYO_MAX_GROUP;
		अगर (!tomoyo_पढ़ो_करोमुख्य2(head, &ns->acl_group
					 [head->r.acl_group_index]))
			वापस;
		head->r.step++;
	पूर्ण
	head->r.eof = true;
पूर्ण

/* Wait queue क्रम kernel -> userspace notअगरication. */
अटल DECLARE_WAIT_QUEUE_HEAD(tomoyo_query_रुको);
/* Wait queue क्रम userspace -> kernel notअगरication. */
अटल DECLARE_WAIT_QUEUE_HEAD(tomoyo_answer_रुको);

/* Structure क्रम query. */
काष्ठा tomoyo_query अणु
	काष्ठा list_head list;
	काष्ठा tomoyo_करोमुख्य_info *करोमुख्य;
	अक्षर *query;
	माप_प्रकार query_len;
	अचिन्हित पूर्णांक serial;
	u8 समयr;
	u8 answer;
	u8 retry;
पूर्ण;

/* The list क्रम "struct tomoyo_query". */
अटल LIST_HEAD(tomoyo_query_list);

/* Lock क्रम manipulating tomoyo_query_list. */
अटल DEFINE_SPINLOCK(tomoyo_query_list_lock);

/*
 * Number of "struct file" referring /sys/kernel/security/tomoyo/query
 * पूर्णांकerface.
 */
अटल atomic_t tomoyo_query_observers = ATOMIC_INIT(0);

/**
 * tomoyo_truncate - Truncate a line.
 *
 * @str: String to truncate.
 *
 * Returns length of truncated @str.
 */
अटल पूर्णांक tomoyo_truncate(अक्षर *str)
अणु
	अक्षर *start = str;

	जबतक (*(अचिन्हित अक्षर *) str > (अचिन्हित अक्षर) ' ')
		str++;
	*str = '\0';
	वापस म_माप(start) + 1;
पूर्ण

/**
 * tomoyo_add_entry - Add an ACL to current thपढ़ो's करोमुख्य. Used by learning mode.
 *
 * @करोमुख्य: Poपूर्णांकer to "struct tomoyo_domain_info".
 * @header: Lines containing ACL.
 *
 * Returns nothing.
 */
अटल व्योम tomoyo_add_entry(काष्ठा tomoyo_करोमुख्य_info *करोमुख्य, अक्षर *header)
अणु
	अक्षर *buffer;
	अक्षर *realpath = शून्य;
	अक्षर *argv0 = शून्य;
	अक्षर *symlink = शून्य;
	अक्षर *cp = म_अक्षर(header, '\n');
	पूर्णांक len;

	अगर (!cp)
		वापस;
	cp = म_अक्षर(cp + 1, '\n');
	अगर (!cp)
		वापस;
	*cp++ = '\0';
	len = म_माप(cp) + 1;
	/* म_माला() will वापस शून्य अगर ordering is wrong. */
	अगर (*cp == 'f') अणु
		argv0 = म_माला(header, " argv[]={ \"");
		अगर (argv0) अणु
			argv0 += 10;
			len += tomoyo_truncate(argv0) + 14;
		पूर्ण
		realpath = म_माला(header, " exec={ realpath=\"");
		अगर (realpath) अणु
			realpath += 8;
			len += tomoyo_truncate(realpath) + 6;
		पूर्ण
		symlink = म_माला(header, " symlink.target=\"");
		अगर (symlink)
			len += tomoyo_truncate(symlink + 1) + 1;
	पूर्ण
	buffer = kदो_स्मृति(len, GFP_NOFS);
	अगर (!buffer)
		वापस;
	snम_लिखो(buffer, len - 1, "%s", cp);
	अगर (realpath)
		tomoyo_addम_लिखो(buffer, len, " exec.%s", realpath);
	अगर (argv0)
		tomoyo_addम_लिखो(buffer, len, " exec.argv[0]=%s", argv0);
	अगर (symlink)
		tomoyo_addम_लिखो(buffer, len, "%s", symlink);
	tomoyo_normalize_line(buffer);
	अगर (!tomoyo_ग_लिखो_करोमुख्य2(करोमुख्य->ns, &करोमुख्य->acl_info_list, buffer,
				  false))
		tomoyo_update_stat(TOMOYO_STAT_POLICY_UPDATES);
	kमुक्त(buffer);
पूर्ण

/**
 * tomoyo_supervisor - Ask क्रम the supervisor's decision.
 *
 * @r:   Poपूर्णांकer to "struct tomoyo_request_info".
 * @fmt: The म_लिखो()'s क्रमmat string, followed by parameters.
 *
 * Returns 0 अगर the supervisor decided to permit the access request which
 * violated the policy in enक्रमcing mode, TOMOYO_RETRY_REQUEST अगर the
 * supervisor decided to retry the access request which violated the policy in
 * enक्रमcing mode, 0 अगर it is not in enक्रमcing mode, -EPERM otherwise.
 */
पूर्णांक tomoyo_supervisor(काष्ठा tomoyo_request_info *r, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;
	पूर्णांक error;
	पूर्णांक len;
	अटल अचिन्हित पूर्णांक tomoyo_serial;
	काष्ठा tomoyo_query entry = अणु पूर्ण;
	bool quota_exceeded = false;

	बहु_शुरू(args, fmt);
	len = vsnम_लिखो((अक्षर *) &len, 1, fmt, args) + 1;
	बहु_पूर्ण(args);
	/* Write /sys/kernel/security/tomoyo/audit. */
	बहु_शुरू(args, fmt);
	tomoyo_ग_लिखो_log2(r, len, fmt, args);
	बहु_पूर्ण(args);
	/* Nothing more to करो अगर granted. */
	अगर (r->granted)
		वापस 0;
	अगर (r->mode)
		tomoyo_update_stat(r->mode);
	चयन (r->mode) अणु
	हाल TOMOYO_CONFIG_ENFORCING:
		error = -EPERM;
		अगर (atomic_पढ़ो(&tomoyo_query_observers))
			अवरोध;
		जाओ out;
	हाल TOMOYO_CONFIG_LEARNING:
		error = 0;
		/* Check max_learning_entry parameter. */
		अगर (tomoyo_करोमुख्य_quota_is_ok(r))
			अवरोध;
		fallthrough;
	शेष:
		वापस 0;
	पूर्ण
	/* Get message. */
	बहु_शुरू(args, fmt);
	entry.query = tomoyo_init_log(r, len, fmt, args);
	बहु_पूर्ण(args);
	अगर (!entry.query)
		जाओ out;
	entry.query_len = म_माप(entry.query) + 1;
	अगर (!error) अणु
		tomoyo_add_entry(r->करोमुख्य, entry.query);
		जाओ out;
	पूर्ण
	len = tomoyo_round2(entry.query_len);
	entry.करोमुख्य = r->करोमुख्य;
	spin_lock(&tomoyo_query_list_lock);
	अगर (tomoyo_memory_quota[TOMOYO_MEMORY_QUERY] &&
	    tomoyo_memory_used[TOMOYO_MEMORY_QUERY] + len
	    >= tomoyo_memory_quota[TOMOYO_MEMORY_QUERY]) अणु
		quota_exceeded = true;
	पूर्ण अन्यथा अणु
		entry.serial = tomoyo_serial++;
		entry.retry = r->retry;
		tomoyo_memory_used[TOMOYO_MEMORY_QUERY] += len;
		list_add_tail(&entry.list, &tomoyo_query_list);
	पूर्ण
	spin_unlock(&tomoyo_query_list_lock);
	अगर (quota_exceeded)
		जाओ out;
	/* Give 10 seconds क्रम supervisor's opinion. */
	जबतक (entry.समयr < 10) अणु
		wake_up_all(&tomoyo_query_रुको);
		अगर (रुको_event_पूर्णांकerruptible_समयout
		    (tomoyo_answer_रुको, entry.answer ||
		     !atomic_पढ़ो(&tomoyo_query_observers), HZ))
			अवरोध;
		entry.समयr++;
	पूर्ण
	spin_lock(&tomoyo_query_list_lock);
	list_del(&entry.list);
	tomoyo_memory_used[TOMOYO_MEMORY_QUERY] -= len;
	spin_unlock(&tomoyo_query_list_lock);
	चयन (entry.answer) अणु
	हाल 3: /* Asked to retry by administrator. */
		error = TOMOYO_RETRY_REQUEST;
		r->retry++;
		अवरोध;
	हाल 1:
		/* Granted by administrator. */
		error = 0;
		अवरोध;
	शेष:
		/* Timed out or rejected by administrator. */
		अवरोध;
	पूर्ण
out:
	kमुक्त(entry.query);
	वापस error;
पूर्ण

/**
 * tomoyo_find_करोमुख्य_by_qid - Get करोमुख्य by query id.
 *
 * @serial: Query ID asचिन्हित by tomoyo_supervisor().
 *
 * Returns poपूर्णांकer to "struct tomoyo_domain_info" अगर found, शून्य otherwise.
 */
अटल काष्ठा tomoyo_करोमुख्य_info *tomoyo_find_करोमुख्य_by_qid
(अचिन्हित पूर्णांक serial)
अणु
	काष्ठा tomoyo_query *ptr;
	काष्ठा tomoyo_करोमुख्य_info *करोमुख्य = शून्य;

	spin_lock(&tomoyo_query_list_lock);
	list_क्रम_each_entry(ptr, &tomoyo_query_list, list) अणु
		अगर (ptr->serial != serial)
			जारी;
		करोमुख्य = ptr->करोमुख्य;
		अवरोध;
	पूर्ण
	spin_unlock(&tomoyo_query_list_lock);
	वापस करोमुख्य;
पूर्ण

/**
 * tomoyo_poll_query - poll() क्रम /sys/kernel/security/tomoyo/query.
 *
 * @file: Poपूर्णांकer to "struct file".
 * @रुको: Poपूर्णांकer to "poll_table".
 *
 * Returns EPOLLIN | EPOLLRDNORM when पढ़ोy to पढ़ो, 0 otherwise.
 *
 * Waits क्रम access requests which violated policy in enक्रमcing mode.
 */
अटल __poll_t tomoyo_poll_query(काष्ठा file *file, poll_table *रुको)
अणु
	अगर (!list_empty(&tomoyo_query_list))
		वापस EPOLLIN | EPOLLRDNORM;
	poll_रुको(file, &tomoyo_query_रुको, रुको);
	अगर (!list_empty(&tomoyo_query_list))
		वापस EPOLLIN | EPOLLRDNORM;
	वापस 0;
पूर्ण

/**
 * tomoyo_पढ़ो_query - Read access requests which violated policy in enक्रमcing mode.
 *
 * @head: Poपूर्णांकer to "struct tomoyo_io_buffer".
 */
अटल व्योम tomoyo_पढ़ो_query(काष्ठा tomoyo_io_buffer *head)
अणु
	काष्ठा list_head *पंचांगp;
	अचिन्हित पूर्णांक pos = 0;
	माप_प्रकार len = 0;
	अक्षर *buf;

	अगर (head->r.w_pos)
		वापस;
	kमुक्त(head->पढ़ो_buf);
	head->पढ़ो_buf = शून्य;
	spin_lock(&tomoyo_query_list_lock);
	list_क्रम_each(पंचांगp, &tomoyo_query_list) अणु
		काष्ठा tomoyo_query *ptr = list_entry(पंचांगp, typeof(*ptr), list);

		अगर (pos++ != head->r.query_index)
			जारी;
		len = ptr->query_len;
		अवरोध;
	पूर्ण
	spin_unlock(&tomoyo_query_list_lock);
	अगर (!len) अणु
		head->r.query_index = 0;
		वापस;
	पूर्ण
	buf = kzalloc(len + 32, GFP_NOFS);
	अगर (!buf)
		वापस;
	pos = 0;
	spin_lock(&tomoyo_query_list_lock);
	list_क्रम_each(पंचांगp, &tomoyo_query_list) अणु
		काष्ठा tomoyo_query *ptr = list_entry(पंचांगp, typeof(*ptr), list);

		अगर (pos++ != head->r.query_index)
			जारी;
		/*
		 * Some query can be skipped because tomoyo_query_list
		 * can change, but I करोn't care.
		 */
		अगर (len == ptr->query_len)
			snम_लिखो(buf, len + 31, "Q%u-%hu\n%s", ptr->serial,
				 ptr->retry, ptr->query);
		अवरोध;
	पूर्ण
	spin_unlock(&tomoyo_query_list_lock);
	अगर (buf[0]) अणु
		head->पढ़ो_buf = buf;
		head->r.w[head->r.w_pos++] = buf;
		head->r.query_index++;
	पूर्ण अन्यथा अणु
		kमुक्त(buf);
	पूर्ण
पूर्ण

/**
 * tomoyo_ग_लिखो_answer - Write the supervisor's decision.
 *
 * @head: Poपूर्णांकer to "struct tomoyo_io_buffer".
 *
 * Returns 0 on success, -EINVAL otherwise.
 */
अटल पूर्णांक tomoyo_ग_लिखो_answer(काष्ठा tomoyo_io_buffer *head)
अणु
	अक्षर *data = head->ग_लिखो_buf;
	काष्ठा list_head *पंचांगp;
	अचिन्हित पूर्णांक serial;
	अचिन्हित पूर्णांक answer;

	spin_lock(&tomoyo_query_list_lock);
	list_क्रम_each(पंचांगp, &tomoyo_query_list) अणु
		काष्ठा tomoyo_query *ptr = list_entry(पंचांगp, typeof(*ptr), list);

		ptr->समयr = 0;
	पूर्ण
	spin_unlock(&tomoyo_query_list_lock);
	अगर (माला_पूछो(data, "A%u=%u", &serial, &answer) != 2)
		वापस -EINVAL;
	spin_lock(&tomoyo_query_list_lock);
	list_क्रम_each(पंचांगp, &tomoyo_query_list) अणु
		काष्ठा tomoyo_query *ptr = list_entry(पंचांगp, typeof(*ptr), list);

		अगर (ptr->serial != serial)
			जारी;
		ptr->answer = answer;
		/* Remove from tomoyo_query_list. */
		अगर (ptr->answer)
			list_del_init(&ptr->list);
		अवरोध;
	पूर्ण
	spin_unlock(&tomoyo_query_list_lock);
	वापस 0;
पूर्ण

/**
 * tomoyo_पढ़ो_version: Get version.
 *
 * @head: Poपूर्णांकer to "struct tomoyo_io_buffer".
 *
 * Returns version inक्रमmation.
 */
अटल व्योम tomoyo_पढ़ो_version(काष्ठा tomoyo_io_buffer *head)
अणु
	अगर (!head->r.eof) अणु
		tomoyo_io_म_लिखो(head, "2.6.0");
		head->r.eof = true;
	पूर्ण
पूर्ण

/* String table क्रम /sys/kernel/security/tomoyo/stat पूर्णांकerface. */
अटल स्थिर अक्षर * स्थिर tomoyo_policy_headers[TOMOYO_MAX_POLICY_STAT] = अणु
	[TOMOYO_STAT_POLICY_UPDATES]    = "update:",
	[TOMOYO_STAT_POLICY_LEARNING]   = "violation in learning mode:",
	[TOMOYO_STAT_POLICY_PERMISSIVE] = "violation in permissive mode:",
	[TOMOYO_STAT_POLICY_ENFORCING]  = "violation in enforcing mode:",
पूर्ण;

/* String table क्रम /sys/kernel/security/tomoyo/stat पूर्णांकerface. */
अटल स्थिर अक्षर * स्थिर tomoyo_memory_headers[TOMOYO_MAX_MEMORY_STAT] = अणु
	[TOMOYO_MEMORY_POLICY] = "policy:",
	[TOMOYO_MEMORY_AUDIT]  = "audit log:",
	[TOMOYO_MEMORY_QUERY]  = "query message:",
पूर्ण;

/* Counter क्रम number of updates. */
अटल atomic_t tomoyo_stat_updated[TOMOYO_MAX_POLICY_STAT];
/* Timestamp counter क्रम last updated. */
अटल समय64_t tomoyo_stat_modअगरied[TOMOYO_MAX_POLICY_STAT];

/**
 * tomoyo_update_stat - Update statistic counters.
 *
 * @index: Index क्रम policy type.
 *
 * Returns nothing.
 */
व्योम tomoyo_update_stat(स्थिर u8 index)
अणु
	atomic_inc(&tomoyo_stat_updated[index]);
	tomoyo_stat_modअगरied[index] = kसमय_get_real_seconds();
पूर्ण

/**
 * tomoyo_पढ़ो_stat - Read statistic data.
 *
 * @head: Poपूर्णांकer to "struct tomoyo_io_buffer".
 *
 * Returns nothing.
 */
अटल व्योम tomoyo_पढ़ो_stat(काष्ठा tomoyo_io_buffer *head)
अणु
	u8 i;
	अचिन्हित पूर्णांक total = 0;

	अगर (head->r.eof)
		वापस;
	क्रम (i = 0; i < TOMOYO_MAX_POLICY_STAT; i++) अणु
		tomoyo_io_म_लिखो(head, "Policy %-30s %10u",
				 tomoyo_policy_headers[i],
				 atomic_पढ़ो(&tomoyo_stat_updated[i]));
		अगर (tomoyo_stat_modअगरied[i]) अणु
			काष्ठा tomoyo_समय stamp;

			tomoyo_convert_समय(tomoyo_stat_modअगरied[i], &stamp);
			tomoyo_io_म_लिखो(head, " (Last: %04u/%02u/%02u %02u:%02u:%02u)",
					 stamp.year, stamp.month, stamp.day,
					 stamp.hour, stamp.min, stamp.sec);
		पूर्ण
		tomoyo_set_lf(head);
	पूर्ण
	क्रम (i = 0; i < TOMOYO_MAX_MEMORY_STAT; i++) अणु
		अचिन्हित पूर्णांक used = tomoyo_memory_used[i];

		total += used;
		tomoyo_io_म_लिखो(head, "Memory used by %-22s %10u",
				 tomoyo_memory_headers[i], used);
		used = tomoyo_memory_quota[i];
		अगर (used)
			tomoyo_io_म_लिखो(head, " (Quota: %10u)", used);
		tomoyo_set_lf(head);
	पूर्ण
	tomoyo_io_म_लिखो(head, "Total memory used:                    %10u\n",
			 total);
	head->r.eof = true;
पूर्ण

/**
 * tomoyo_ग_लिखो_stat - Set memory quota.
 *
 * @head: Poपूर्णांकer to "struct tomoyo_io_buffer".
 *
 * Returns 0.
 */
अटल पूर्णांक tomoyo_ग_लिखो_stat(काष्ठा tomoyo_io_buffer *head)
अणु
	अक्षर *data = head->ग_लिखो_buf;
	u8 i;

	अगर (tomoyo_str_starts(&data, "Memory used by "))
		क्रम (i = 0; i < TOMOYO_MAX_MEMORY_STAT; i++)
			अगर (tomoyo_str_starts(&data, tomoyo_memory_headers[i]))
				माला_पूछो(data, "%u", &tomoyo_memory_quota[i]);
	वापस 0;
पूर्ण

/**
 * tomoyo_खोलो_control - खोलो() क्रम /sys/kernel/security/tomoyo/ पूर्णांकerface.
 *
 * @type: Type of पूर्णांकerface.
 * @file: Poपूर्णांकer to "struct file".
 *
 * Returns 0 on success, negative value otherwise.
 */
पूर्णांक tomoyo_खोलो_control(स्थिर u8 type, काष्ठा file *file)
अणु
	काष्ठा tomoyo_io_buffer *head = kzalloc(माप(*head), GFP_NOFS);

	अगर (!head)
		वापस -ENOMEM;
	mutex_init(&head->io_sem);
	head->type = type;
	चयन (type) अणु
	हाल TOMOYO_DOMAINPOLICY:
		/* /sys/kernel/security/tomoyo/करोमुख्य_policy */
		head->ग_लिखो = tomoyo_ग_लिखो_करोमुख्य;
		head->पढ़ो = tomoyo_पढ़ो_करोमुख्य;
		अवरोध;
	हाल TOMOYO_EXCEPTIONPOLICY:
		/* /sys/kernel/security/tomoyo/exception_policy */
		head->ग_लिखो = tomoyo_ग_लिखो_exception;
		head->पढ़ो = tomoyo_पढ़ो_exception;
		अवरोध;
	हाल TOMOYO_AUDIT:
		/* /sys/kernel/security/tomoyo/audit */
		head->poll = tomoyo_poll_log;
		head->पढ़ो = tomoyo_पढ़ो_log;
		अवरोध;
	हाल TOMOYO_PROCESS_STATUS:
		/* /sys/kernel/security/tomoyo/.process_status */
		head->ग_लिखो = tomoyo_ग_लिखो_pid;
		head->पढ़ो = tomoyo_पढ़ो_pid;
		अवरोध;
	हाल TOMOYO_VERSION:
		/* /sys/kernel/security/tomoyo/version */
		head->पढ़ो = tomoyo_पढ़ो_version;
		head->पढ़ोbuf_size = 128;
		अवरोध;
	हाल TOMOYO_STAT:
		/* /sys/kernel/security/tomoyo/stat */
		head->ग_लिखो = tomoyo_ग_लिखो_stat;
		head->पढ़ो = tomoyo_पढ़ो_stat;
		head->पढ़ोbuf_size = 1024;
		अवरोध;
	हाल TOMOYO_PROखाता:
		/* /sys/kernel/security/tomoyo/profile */
		head->ग_लिखो = tomoyo_ग_लिखो_profile;
		head->पढ़ो = tomoyo_पढ़ो_profile;
		अवरोध;
	हाल TOMOYO_QUERY: /* /sys/kernel/security/tomoyo/query */
		head->poll = tomoyo_poll_query;
		head->ग_लिखो = tomoyo_ग_लिखो_answer;
		head->पढ़ो = tomoyo_पढ़ो_query;
		अवरोध;
	हाल TOMOYO_MANAGER:
		/* /sys/kernel/security/tomoyo/manager */
		head->ग_लिखो = tomoyo_ग_लिखो_manager;
		head->पढ़ो = tomoyo_पढ़ो_manager;
		अवरोध;
	पूर्ण
	अगर (!(file->f_mode & FMODE_READ)) अणु
		/*
		 * No need to allocate पढ़ो_buf since it is not खोलोed
		 * क्रम पढ़ोing.
		 */
		head->पढ़ो = शून्य;
		head->poll = शून्य;
	पूर्ण अन्यथा अगर (!head->poll) अणु
		/* Don't allocate पढ़ो_buf क्रम poll() access. */
		अगर (!head->पढ़ोbuf_size)
			head->पढ़ोbuf_size = 4096 * 2;
		head->पढ़ो_buf = kzalloc(head->पढ़ोbuf_size, GFP_NOFS);
		अगर (!head->पढ़ो_buf) अणु
			kमुक्त(head);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण
	अगर (!(file->f_mode & FMODE_WRITE)) अणु
		/*
		 * No need to allocate ग_लिखो_buf since it is not खोलोed
		 * क्रम writing.
		 */
		head->ग_लिखो = शून्य;
	पूर्ण अन्यथा अगर (head->ग_लिखो) अणु
		head->ग_लिखोbuf_size = 4096 * 2;
		head->ग_लिखो_buf = kzalloc(head->ग_लिखोbuf_size, GFP_NOFS);
		अगर (!head->ग_लिखो_buf) अणु
			kमुक्त(head->पढ़ो_buf);
			kमुक्त(head);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण
	/*
	 * If the file is /sys/kernel/security/tomoyo/query , increment the
	 * observer counter.
	 * The obserber counter is used by tomoyo_supervisor() to see अगर
	 * there is some process monitoring /sys/kernel/security/tomoyo/query.
	 */
	अगर (type == TOMOYO_QUERY)
		atomic_inc(&tomoyo_query_observers);
	file->निजी_data = head;
	tomoyo_notअगरy_gc(head, true);
	वापस 0;
पूर्ण

/**
 * tomoyo_poll_control - poll() क्रम /sys/kernel/security/tomoyo/ पूर्णांकerface.
 *
 * @file: Poपूर्णांकer to "struct file".
 * @रुको: Poपूर्णांकer to "poll_table". Maybe शून्य.
 *
 * Returns EPOLLIN | EPOLLRDNORM | EPOLLOUT | EPOLLWRNORM अगर पढ़ोy to पढ़ो/ग_लिखो,
 * EPOLLOUT | EPOLLWRNORM otherwise.
 */
__poll_t tomoyo_poll_control(काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा tomoyo_io_buffer *head = file->निजी_data;

	अगर (head->poll)
		वापस head->poll(file, रुको) | EPOLLOUT | EPOLLWRNORM;
	वापस EPOLLIN | EPOLLRDNORM | EPOLLOUT | EPOLLWRNORM;
पूर्ण

/**
 * tomoyo_set_namespace_cursor - Set namespace to पढ़ो.
 *
 * @head: Poपूर्णांकer to "struct tomoyo_io_buffer".
 *
 * Returns nothing.
 */
अटल अंतरभूत व्योम tomoyo_set_namespace_cursor(काष्ठा tomoyo_io_buffer *head)
अणु
	काष्ठा list_head *ns;

	अगर (head->type != TOMOYO_EXCEPTIONPOLICY &&
	    head->type != TOMOYO_PROखाता)
		वापस;
	/*
	 * If this is the first पढ़ो, or पढ़ोing previous namespace finished
	 * and has more namespaces to पढ़ो, update the namespace cursor.
	 */
	ns = head->r.ns;
	अगर (!ns || (head->r.eof && ns->next != &tomoyo_namespace_list)) अणु
		/* Clearing is OK because tomoyo_flush() वापसed true. */
		स_रखो(&head->r, 0, माप(head->r));
		head->r.ns = ns ? ns->next : tomoyo_namespace_list.next;
	पूर्ण
पूर्ण

/**
 * tomoyo_has_more_namespace - Check क्रम unपढ़ो namespaces.
 *
 * @head: Poपूर्णांकer to "struct tomoyo_io_buffer".
 *
 * Returns true अगर we have more entries to prपूर्णांक, false otherwise.
 */
अटल अंतरभूत bool tomoyo_has_more_namespace(काष्ठा tomoyo_io_buffer *head)
अणु
	वापस (head->type == TOMOYO_EXCEPTIONPOLICY ||
		head->type == TOMOYO_PROखाता) && head->r.eof &&
		head->r.ns->next != &tomoyo_namespace_list;
पूर्ण

/**
 * tomoyo_पढ़ो_control - पढ़ो() क्रम /sys/kernel/security/tomoyo/ पूर्णांकerface.
 *
 * @head:       Poपूर्णांकer to "struct tomoyo_io_buffer".
 * @buffer:     Poपूर्णांकer to buffer to ग_लिखो to.
 * @buffer_len: Size of @buffer.
 *
 * Returns bytes पढ़ो on success, negative value otherwise.
 */
sमाप_प्रकार tomoyo_पढ़ो_control(काष्ठा tomoyo_io_buffer *head, अक्षर __user *buffer,
			    स्थिर पूर्णांक buffer_len)
अणु
	पूर्णांक len;
	पूर्णांक idx;

	अगर (!head->पढ़ो)
		वापस -EINVAL;
	अगर (mutex_lock_पूर्णांकerruptible(&head->io_sem))
		वापस -EINTR;
	head->पढ़ो_user_buf = buffer;
	head->पढ़ो_user_buf_avail = buffer_len;
	idx = tomoyo_पढ़ो_lock();
	अगर (tomoyo_flush(head))
		/* Call the policy handler. */
		करो अणु
			tomoyo_set_namespace_cursor(head);
			head->पढ़ो(head);
		पूर्ण जबतक (tomoyo_flush(head) &&
			 tomoyo_has_more_namespace(head));
	tomoyo_पढ़ो_unlock(idx);
	len = head->पढ़ो_user_buf - buffer;
	mutex_unlock(&head->io_sem);
	वापस len;
पूर्ण

/**
 * tomoyo_parse_policy - Parse a policy line.
 *
 * @head: Poपूर्णांकer to "struct tomoyo_io_buffer".
 * @line: Line to parse.
 *
 * Returns 0 on success, negative value otherwise.
 *
 * Caller holds tomoyo_पढ़ो_lock().
 */
अटल पूर्णांक tomoyo_parse_policy(काष्ठा tomoyo_io_buffer *head, अक्षर *line)
अणु
	/* Delete request? */
	head->w.is_delete = !म_भेदन(line, "delete ", 7);
	अगर (head->w.is_delete)
		स_हटाओ(line, line + 7, म_माप(line + 7) + 1);
	/* Selecting namespace to update. */
	अगर (head->type == TOMOYO_EXCEPTIONPOLICY ||
	    head->type == TOMOYO_PROखाता) अणु
		अगर (*line == '<') अणु
			अक्षर *cp = म_अक्षर(line, ' ');

			अगर (cp) अणु
				*cp++ = '\0';
				head->w.ns = tomoyo_assign_namespace(line);
				स_हटाओ(line, cp, म_माप(cp) + 1);
			पूर्ण अन्यथा
				head->w.ns = शून्य;
		पूर्ण अन्यथा
			head->w.ns = &tomoyo_kernel_namespace;
		/* Don't allow updating अगर namespace is invalid. */
		अगर (!head->w.ns)
			वापस -ENOENT;
	पूर्ण
	/* Do the update. */
	वापस head->ग_लिखो(head);
पूर्ण

/**
 * tomoyo_ग_लिखो_control - ग_लिखो() क्रम /sys/kernel/security/tomoyo/ पूर्णांकerface.
 *
 * @head:       Poपूर्णांकer to "struct tomoyo_io_buffer".
 * @buffer:     Poपूर्णांकer to buffer to पढ़ो from.
 * @buffer_len: Size of @buffer.
 *
 * Returns @buffer_len on success, negative value otherwise.
 */
sमाप_प्रकार tomoyo_ग_लिखो_control(काष्ठा tomoyo_io_buffer *head,
			     स्थिर अक्षर __user *buffer, स्थिर पूर्णांक buffer_len)
अणु
	पूर्णांक error = buffer_len;
	माप_प्रकार avail_len = buffer_len;
	अक्षर *cp0 = head->ग_लिखो_buf;
	पूर्णांक idx;

	अगर (!head->ग_लिखो)
		वापस -EINVAL;
	अगर (mutex_lock_पूर्णांकerruptible(&head->io_sem))
		वापस -EINTR;
	head->पढ़ो_user_buf_avail = 0;
	idx = tomoyo_पढ़ो_lock();
	/* Read a line and dispatch it to the policy handler. */
	जबतक (avail_len > 0) अणु
		अक्षर c;

		अगर (head->w.avail >= head->ग_लिखोbuf_size - 1) अणु
			स्थिर पूर्णांक len = head->ग_लिखोbuf_size * 2;
			अक्षर *cp = kzalloc(len, GFP_NOFS);

			अगर (!cp) अणु
				error = -ENOMEM;
				अवरोध;
			पूर्ण
			स_हटाओ(cp, cp0, head->w.avail);
			kमुक्त(cp0);
			head->ग_लिखो_buf = cp;
			cp0 = cp;
			head->ग_लिखोbuf_size = len;
		पूर्ण
		अगर (get_user(c, buffer)) अणु
			error = -EFAULT;
			अवरोध;
		पूर्ण
		buffer++;
		avail_len--;
		cp0[head->w.avail++] = c;
		अगर (c != '\n')
			जारी;
		cp0[head->w.avail - 1] = '\0';
		head->w.avail = 0;
		tomoyo_normalize_line(cp0);
		अगर (!म_भेद(cp0, "reset")) अणु
			head->w.ns = &tomoyo_kernel_namespace;
			head->w.करोमुख्य = शून्य;
			स_रखो(&head->r, 0, माप(head->r));
			जारी;
		पूर्ण
		/* Don't allow updating policies by non manager programs. */
		चयन (head->type) अणु
		हाल TOMOYO_PROCESS_STATUS:
			/* This करोes not ग_लिखो anything. */
			अवरोध;
		हाल TOMOYO_DOMAINPOLICY:
			अगर (tomoyo_select_करोमुख्य(head, cp0))
				जारी;
			fallthrough;
		हाल TOMOYO_EXCEPTIONPOLICY:
			अगर (!म_भेद(cp0, "select transition_only")) अणु
				head->r.prपूर्णांक_transition_related_only = true;
				जारी;
			पूर्ण
			fallthrough;
		शेष:
			अगर (!tomoyo_manager()) अणु
				error = -EPERM;
				जाओ out;
			पूर्ण
		पूर्ण
		चयन (tomoyo_parse_policy(head, cp0)) अणु
		हाल -EPERM:
			error = -EPERM;
			जाओ out;
		हाल 0:
			चयन (head->type) अणु
			हाल TOMOYO_DOMAINPOLICY:
			हाल TOMOYO_EXCEPTIONPOLICY:
			हाल TOMOYO_STAT:
			हाल TOMOYO_PROखाता:
			हाल TOMOYO_MANAGER:
				tomoyo_update_stat(TOMOYO_STAT_POLICY_UPDATES);
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण
out:
	tomoyo_पढ़ो_unlock(idx);
	mutex_unlock(&head->io_sem);
	वापस error;
पूर्ण

/**
 * tomoyo_बंद_control - बंद() क्रम /sys/kernel/security/tomoyo/ पूर्णांकerface.
 *
 * @head: Poपूर्णांकer to "struct tomoyo_io_buffer".
 */
व्योम tomoyo_बंद_control(काष्ठा tomoyo_io_buffer *head)
अणु
	/*
	 * If the file is /sys/kernel/security/tomoyo/query , decrement the
	 * observer counter.
	 */
	अगर (head->type == TOMOYO_QUERY &&
	    atomic_dec_and_test(&tomoyo_query_observers))
		wake_up_all(&tomoyo_answer_रुको);
	tomoyo_notअगरy_gc(head, false);
पूर्ण

/**
 * tomoyo_check_profile - Check all profiles currently asचिन्हित to करोमुख्यs are defined.
 */
व्योम tomoyo_check_profile(व्योम)
अणु
	काष्ठा tomoyo_करोमुख्य_info *करोमुख्य;
	स्थिर पूर्णांक idx = tomoyo_पढ़ो_lock();

	tomoyo_policy_loaded = true;
	pr_info("TOMOYO: 2.6.0\n");
	list_क्रम_each_entry_rcu(करोमुख्य, &tomoyo_करोमुख्य_list, list,
				srcu_पढ़ो_lock_held(&tomoyo_ss)) अणु
		स्थिर u8 profile = करोमुख्य->profile;
		काष्ठा tomoyo_policy_namespace *ns = करोमुख्य->ns;

		अगर (ns->profile_version == 20110903) अणु
			pr_info_once("Converting profile version from %u to %u.\n",
				     20110903, 20150505);
			ns->profile_version = 20150505;
		पूर्ण
		अगर (ns->profile_version != 20150505)
			pr_err("Profile version %u is not supported.\n",
			       ns->profile_version);
		अन्यथा अगर (!ns->profile_ptr[profile])
			pr_err("Profile %u (used by '%s') is not defined.\n",
			       profile, करोमुख्य->करोमुख्यname->name);
		अन्यथा
			जारी;
		pr_err("Userland tools for TOMOYO 2.6 must be installed and policy must be initialized.\n");
		pr_err("Please see https://tomoyo.osdn.jp/2.6/ for more information.\n");
		panic("STOP!");
	पूर्ण
	tomoyo_पढ़ो_unlock(idx);
	pr_info("Mandatory Access Control activated.\n");
पूर्ण

/**
 * tomoyo_load_builtin_policy - Load built-in policy.
 *
 * Returns nothing.
 */
व्योम __init tomoyo_load_builtin_policy(व्योम)
अणु
#अगर_घोषित CONFIG_SECURITY_TOMOYO_INSECURE_BUILTIN_SETTING
	अटल अक्षर tomoyo_builtin_profile[] __initdata =
		"PROFILE_VERSION=20150505\n"
		"0-CONFIG={ mode=learning grant_log=no reject_log=yes }\n";
	अटल अक्षर tomoyo_builtin_exception_policy[] __initdata =
		"aggregator proc:/self/exe /proc/self/exe\n";
	अटल अक्षर tomoyo_builtin_करोमुख्य_policy[] __initdata = "";
	अटल अक्षर tomoyo_builtin_manager[] __initdata = "";
	अटल अक्षर tomoyo_builtin_stat[] __initdata = "";
#अन्यथा
	/*
	 * This include file is manually created and contains built-in policy
	 * named "tomoyo_builtin_profile", "tomoyo_builtin_exception_policy",
	 * "tomoyo_builtin_domain_policy", "tomoyo_builtin_manager",
	 * "tomoyo_builtin_stat" in the क्रमm of "static char [] __initdata".
	 */
#समावेश "builtin-policy.h"
#पूर्ण_अगर
	u8 i;
	स्थिर पूर्णांक idx = tomoyo_पढ़ो_lock();

	क्रम (i = 0; i < 5; i++) अणु
		काष्ठा tomoyo_io_buffer head = अणु पूर्ण;
		अक्षर *start = "";

		चयन (i) अणु
		हाल 0:
			start = tomoyo_builtin_profile;
			head.type = TOMOYO_PROखाता;
			head.ग_लिखो = tomoyo_ग_लिखो_profile;
			अवरोध;
		हाल 1:
			start = tomoyo_builtin_exception_policy;
			head.type = TOMOYO_EXCEPTIONPOLICY;
			head.ग_लिखो = tomoyo_ग_लिखो_exception;
			अवरोध;
		हाल 2:
			start = tomoyo_builtin_करोमुख्य_policy;
			head.type = TOMOYO_DOMAINPOLICY;
			head.ग_लिखो = tomoyo_ग_लिखो_करोमुख्य;
			अवरोध;
		हाल 3:
			start = tomoyo_builtin_manager;
			head.type = TOMOYO_MANAGER;
			head.ग_लिखो = tomoyo_ग_लिखो_manager;
			अवरोध;
		हाल 4:
			start = tomoyo_builtin_stat;
			head.type = TOMOYO_STAT;
			head.ग_लिखो = tomoyo_ग_लिखो_stat;
			अवरोध;
		पूर्ण
		जबतक (1) अणु
			अक्षर *end = म_अक्षर(start, '\n');

			अगर (!end)
				अवरोध;
			*end = '\0';
			tomoyo_normalize_line(start);
			head.ग_लिखो_buf = start;
			tomoyo_parse_policy(&head, start);
			start = end + 1;
		पूर्ण
	पूर्ण
	tomoyo_पढ़ो_unlock(idx);
#अगर_घोषित CONFIG_SECURITY_TOMOYO_OMIT_USERSPACE_LOADER
	tomoyo_check_profile();
#पूर्ण_अगर
पूर्ण
