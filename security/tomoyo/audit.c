<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * security/tomoyo/audit.c
 *
 * Copyright (C) 2005-2011  NTT DATA CORPORATION
 */

#समावेश "common.h"
#समावेश <linux/slab.h>

/**
 * tomoyo_prपूर्णांक_bprm - Prपूर्णांक "struct linux_binprm" क्रम auditing.
 *
 * @bprm: Poपूर्णांकer to "struct linux_binprm".
 * @dump: Poपूर्णांकer to "struct tomoyo_page_dump".
 *
 * Returns the contents of @bprm on success, शून्य otherwise.
 *
 * This function uses kzalloc(), so caller must kमुक्त() अगर this function
 * didn't वापस शून्य.
 */
अटल अक्षर *tomoyo_prपूर्णांक_bprm(काष्ठा linux_binprm *bprm,
			       काष्ठा tomoyo_page_dump *dump)
अणु
	अटल स्थिर पूर्णांक tomoyo_buffer_len = 4096 * 2;
	अक्षर *buffer = kzalloc(tomoyo_buffer_len, GFP_NOFS);
	अक्षर *cp;
	अक्षर *last_start;
	पूर्णांक len;
	अचिन्हित दीर्घ pos = bprm->p;
	पूर्णांक offset = pos % PAGE_SIZE;
	पूर्णांक argv_count = bprm->argc;
	पूर्णांक envp_count = bprm->envc;
	bool truncated = false;

	अगर (!buffer)
		वापस शून्य;
	len = snम_लिखो(buffer, tomoyo_buffer_len - 1, "argv[]={ ");
	cp = buffer + len;
	अगर (!argv_count) अणु
		स_हटाओ(cp, "} envp[]={ ", 11);
		cp += 11;
	पूर्ण
	last_start = cp;
	जबतक (argv_count || envp_count) अणु
		अगर (!tomoyo_dump_page(bprm, pos, dump))
			जाओ out;
		pos += PAGE_SIZE - offset;
		/* Read. */
		जबतक (offset < PAGE_SIZE) अणु
			स्थिर अक्षर *kaddr = dump->data;
			स्थिर अचिन्हित अक्षर c = kaddr[offset++];

			अगर (cp == last_start)
				*cp++ = '"';
			अगर (cp >= buffer + tomoyo_buffer_len - 32) अणु
				/* Reserve some room क्रम "..." string. */
				truncated = true;
			पूर्ण अन्यथा अगर (c == '\\') अणु
				*cp++ = '\\';
				*cp++ = '\\';
			पूर्ण अन्यथा अगर (c > ' ' && c < 127) अणु
				*cp++ = c;
			पूर्ण अन्यथा अगर (!c) अणु
				*cp++ = '"';
				*cp++ = ' ';
				last_start = cp;
			पूर्ण अन्यथा अणु
				*cp++ = '\\';
				*cp++ = (c >> 6) + '0';
				*cp++ = ((c >> 3) & 7) + '0';
				*cp++ = (c & 7) + '0';
			पूर्ण
			अगर (c)
				जारी;
			अगर (argv_count) अणु
				अगर (--argv_count == 0) अणु
					अगर (truncated) अणु
						cp = last_start;
						स_हटाओ(cp, "... ", 4);
						cp += 4;
					पूर्ण
					स_हटाओ(cp, "} envp[]={ ", 11);
					cp += 11;
					last_start = cp;
					truncated = false;
				पूर्ण
			पूर्ण अन्यथा अगर (envp_count) अणु
				अगर (--envp_count == 0) अणु
					अगर (truncated) अणु
						cp = last_start;
						स_हटाओ(cp, "... ", 4);
						cp += 4;
					पूर्ण
				पूर्ण
			पूर्ण
			अगर (!argv_count && !envp_count)
				अवरोध;
		पूर्ण
		offset = 0;
	पूर्ण
	*cp++ = '}';
	*cp = '\0';
	वापस buffer;
out:
	snम_लिखो(buffer, tomoyo_buffer_len - 1,
		 "argv[]={ ... } envp[]= { ... }");
	वापस buffer;
पूर्ण

/**
 * tomoyo_filetype - Get string representation of file type.
 *
 * @mode: Mode value क्रम stat().
 *
 * Returns file type string.
 */
अटल अंतरभूत स्थिर अक्षर *tomoyo_filetype(स्थिर umode_t mode)
अणु
	चयन (mode & S_IFMT) अणु
	हाल S_IFREG:
	हाल 0:
		वापस tomoyo_condition_keyword[TOMOYO_TYPE_IS_खाता];
	हाल S_IFसूची:
		वापस tomoyo_condition_keyword[TOMOYO_TYPE_IS_सूचीECTORY];
	हाल S_IFLNK:
		वापस tomoyo_condition_keyword[TOMOYO_TYPE_IS_SYMLINK];
	हाल S_IFIFO:
		वापस tomoyo_condition_keyword[TOMOYO_TYPE_IS_FIFO];
	हाल S_IFSOCK:
		वापस tomoyo_condition_keyword[TOMOYO_TYPE_IS_SOCKET];
	हाल S_IFBLK:
		वापस tomoyo_condition_keyword[TOMOYO_TYPE_IS_BLOCK_DEV];
	हाल S_IFCHR:
		वापस tomoyo_condition_keyword[TOMOYO_TYPE_IS_CHAR_DEV];
	पूर्ण
	वापस "unknown"; /* This should not happen. */
पूर्ण

/**
 * tomoyo_prपूर्णांक_header - Get header line of audit log.
 *
 * @r: Poपूर्णांकer to "struct tomoyo_request_info".
 *
 * Returns string representation.
 *
 * This function uses kदो_स्मृति(), so caller must kमुक्त() अगर this function
 * didn't वापस शून्य.
 */
अटल अक्षर *tomoyo_prपूर्णांक_header(काष्ठा tomoyo_request_info *r)
अणु
	काष्ठा tomoyo_समय stamp;
	स्थिर pid_t gpid = task_pid_nr(current);
	काष्ठा tomoyo_obj_info *obj = r->obj;
	अटल स्थिर पूर्णांक tomoyo_buffer_len = 4096;
	अक्षर *buffer = kदो_स्मृति(tomoyo_buffer_len, GFP_NOFS);
	पूर्णांक pos;
	u8 i;

	अगर (!buffer)
		वापस शून्य;

	tomoyo_convert_समय(kसमय_get_real_seconds(), &stamp);

	pos = snम_लिखो(buffer, tomoyo_buffer_len - 1,
		       "#%04u/%02u/%02u %02u:%02u:%02u# profile=%u mode=%s granted=%s (global-pid=%u) task={ pid=%u ppid=%u uid=%u gid=%u euid=%u egid=%u suid=%u sgid=%u fsuid=%u fsgid=%u }",
		       stamp.year, stamp.month, stamp.day, stamp.hour,
		       stamp.min, stamp.sec, r->profile, tomoyo_mode[r->mode],
		       tomoyo_yesno(r->granted), gpid, tomoyo_sys_getpid(),
		       tomoyo_sys_getppid(),
		       from_kuid(&init_user_ns, current_uid()),
		       from_kgid(&init_user_ns, current_gid()),
		       from_kuid(&init_user_ns, current_euid()),
		       from_kgid(&init_user_ns, current_egid()),
		       from_kuid(&init_user_ns, current_suid()),
		       from_kgid(&init_user_ns, current_sgid()),
		       from_kuid(&init_user_ns, current_fsuid()),
		       from_kgid(&init_user_ns, current_fsgid()));
	अगर (!obj)
		जाओ no_obj_info;
	अगर (!obj->validate_करोne) अणु
		tomoyo_get_attributes(obj);
		obj->validate_करोne = true;
	पूर्ण
	क्रम (i = 0; i < TOMOYO_MAX_PATH_STAT; i++) अणु
		काष्ठा tomoyo_mini_stat *stat;
		अचिन्हित पूर्णांक dev;
		umode_t mode;

		अगर (!obj->stat_valid[i])
			जारी;
		stat = &obj->stat[i];
		dev = stat->dev;
		mode = stat->mode;
		अगर (i & 1) अणु
			pos += snम_लिखो(buffer + pos,
					tomoyo_buffer_len - 1 - pos,
					" path%u.parent={ uid=%u gid=%u ino=%lu perm=0%o }",
					(i >> 1) + 1,
					from_kuid(&init_user_ns, stat->uid),
					from_kgid(&init_user_ns, stat->gid),
					(अचिन्हित दीर्घ)stat->ino,
					stat->mode & S_IALLUGO);
			जारी;
		पूर्ण
		pos += snम_लिखो(buffer + pos, tomoyo_buffer_len - 1 - pos,
				" path%u={ uid=%u gid=%u ino=%lu major=%u minor=%u perm=0%o type=%s",
				(i >> 1) + 1,
				from_kuid(&init_user_ns, stat->uid),
				from_kgid(&init_user_ns, stat->gid),
				(अचिन्हित दीर्घ)stat->ino,
				MAJOR(dev), MINOR(dev),
				mode & S_IALLUGO, tomoyo_filetype(mode));
		अगर (S_ISCHR(mode) || S_ISBLK(mode)) अणु
			dev = stat->rdev;
			pos += snम_लिखो(buffer + pos,
					tomoyo_buffer_len - 1 - pos,
					" dev_major=%u dev_minor=%u",
					MAJOR(dev), MINOR(dev));
		पूर्ण
		pos += snम_लिखो(buffer + pos, tomoyo_buffer_len - 1 - pos,
				" }");
	पूर्ण
no_obj_info:
	अगर (pos < tomoyo_buffer_len - 1)
		वापस buffer;
	kमुक्त(buffer);
	वापस शून्य;
पूर्ण

/**
 * tomoyo_init_log - Allocate buffer क्रम audit logs.
 *
 * @r:    Poपूर्णांकer to "struct tomoyo_request_info".
 * @len:  Buffer size needed क्रम @fmt and @args.
 * @fmt:  The म_लिखो()'s क्रमmat string.
 * @args: बहु_सूची काष्ठाure क्रम @fmt.
 *
 * Returns poपूर्णांकer to allocated memory.
 *
 * This function uses kzalloc(), so caller must kमुक्त() अगर this function
 * didn't वापस शून्य.
 */
अक्षर *tomoyo_init_log(काष्ठा tomoyo_request_info *r, पूर्णांक len, स्थिर अक्षर *fmt,
		      बहु_सूची args)
अणु
	अक्षर *buf = शून्य;
	अक्षर *bprm_info = शून्य;
	स्थिर अक्षर *header = शून्य;
	अक्षर *realpath = शून्य;
	स्थिर अक्षर *symlink = शून्य;
	पूर्णांक pos;
	स्थिर अक्षर *करोमुख्यname = r->करोमुख्य->करोमुख्यname->name;

	header = tomoyo_prपूर्णांक_header(r);
	अगर (!header)
		वापस शून्य;
	/* +10 is क्रम '\n' etc. and '\0'. */
	len += म_माप(करोमुख्यname) + म_माप(header) + 10;
	अगर (r->ee) अणु
		काष्ठा file *file = r->ee->bprm->file;

		realpath = tomoyo_realpath_from_path(&file->f_path);
		bprm_info = tomoyo_prपूर्णांक_bprm(r->ee->bprm, &r->ee->dump);
		अगर (!realpath || !bprm_info)
			जाओ out;
		/* +80 is क्रम " exec={ realpath=\"%s\" argc=%d envc=%d %s }" */
		len += म_माप(realpath) + 80 + म_माप(bprm_info);
	पूर्ण अन्यथा अगर (r->obj && r->obj->symlink_target) अणु
		symlink = r->obj->symlink_target->name;
		/* +18 is क्रम " symlink.target=\"%s\"" */
		len += 18 + म_माप(symlink);
	पूर्ण
	len = tomoyo_round2(len);
	buf = kzalloc(len, GFP_NOFS);
	अगर (!buf)
		जाओ out;
	len--;
	pos = snम_लिखो(buf, len, "%s", header);
	अगर (realpath) अणु
		काष्ठा linux_binprm *bprm = r->ee->bprm;

		pos += snम_लिखो(buf + pos, len - pos,
				" exec={ realpath=\"%s\" argc=%d envc=%d %s }",
				realpath, bprm->argc, bprm->envc, bprm_info);
	पूर्ण अन्यथा अगर (symlink)
		pos += snम_लिखो(buf + pos, len - pos, " symlink.target=\"%s\"",
				symlink);
	pos += snम_लिखो(buf + pos, len - pos, "\n%s\n", करोमुख्यname);
	vsnम_लिखो(buf + pos, len - pos, fmt, args);
out:
	kमुक्त(realpath);
	kमुक्त(bprm_info);
	kमुक्त(header);
	वापस buf;
पूर्ण

/* Wait queue क्रम /sys/kernel/security/tomoyo/audit. */
अटल DECLARE_WAIT_QUEUE_HEAD(tomoyo_log_रुको);

/* Structure क्रम audit log. */
काष्ठा tomoyo_log अणु
	काष्ठा list_head list;
	अक्षर *log;
	पूर्णांक size;
पूर्ण;

/* The list क्रम "struct tomoyo_log". */
अटल LIST_HEAD(tomoyo_log);

/* Lock क्रम "struct list_head tomoyo_log". */
अटल DEFINE_SPINLOCK(tomoyo_log_lock);

/* Length of "struct list_head tomoyo_log". */
अटल अचिन्हित पूर्णांक tomoyo_log_count;

/**
 * tomoyo_get_audit - Get audit mode.
 *
 * @ns:          Poपूर्णांकer to "struct tomoyo_policy_namespace".
 * @profile:     Profile number.
 * @index:       Index number of functionality.
 * @is_granted:  True अगर granted log, false otherwise.
 *
 * Returns true अगर this request should be audited, false otherwise.
 */
अटल bool tomoyo_get_audit(स्थिर काष्ठा tomoyo_policy_namespace *ns,
			     स्थिर u8 profile, स्थिर u8 index,
			     स्थिर काष्ठा tomoyo_acl_info *matched_acl,
			     स्थिर bool is_granted)
अणु
	u8 mode;
	स्थिर u8 category = tomoyo_index2category[index] +
		TOMOYO_MAX_MAC_INDEX;
	काष्ठा tomoyo_profile *p;

	अगर (!tomoyo_policy_loaded)
		वापस false;
	p = tomoyo_profile(ns, profile);
	अगर (tomoyo_log_count >= p->pref[TOMOYO_PREF_MAX_AUDIT_LOG])
		वापस false;
	अगर (is_granted && matched_acl && matched_acl->cond &&
	    matched_acl->cond->grant_log != TOMOYO_GRANTLOG_AUTO)
		वापस matched_acl->cond->grant_log == TOMOYO_GRANTLOG_YES;
	mode = p->config[index];
	अगर (mode == TOMOYO_CONFIG_USE_DEFAULT)
		mode = p->config[category];
	अगर (mode == TOMOYO_CONFIG_USE_DEFAULT)
		mode = p->शेष_config;
	अगर (is_granted)
		वापस mode & TOMOYO_CONFIG_WANT_GRANT_LOG;
	वापस mode & TOMOYO_CONFIG_WANT_REJECT_LOG;
पूर्ण

/**
 * tomoyo_ग_लिखो_log2 - Write an audit log.
 *
 * @r:    Poपूर्णांकer to "struct tomoyo_request_info".
 * @len:  Buffer size needed क्रम @fmt and @args.
 * @fmt:  The म_लिखो()'s क्रमmat string.
 * @args: बहु_सूची काष्ठाure क्रम @fmt.
 *
 * Returns nothing.
 */
व्योम tomoyo_ग_लिखो_log2(काष्ठा tomoyo_request_info *r, पूर्णांक len, स्थिर अक्षर *fmt,
		       बहु_सूची args)
अणु
	अक्षर *buf;
	काष्ठा tomoyo_log *entry;
	bool quota_exceeded = false;

	अगर (!tomoyo_get_audit(r->करोमुख्य->ns, r->profile, r->type,
			      r->matched_acl, r->granted))
		जाओ out;
	buf = tomoyo_init_log(r, len, fmt, args);
	अगर (!buf)
		जाओ out;
	entry = kzalloc(माप(*entry), GFP_NOFS);
	अगर (!entry) अणु
		kमुक्त(buf);
		जाओ out;
	पूर्ण
	entry->log = buf;
	len = tomoyo_round2(म_माप(buf) + 1);
	/*
	 * The entry->size is used क्रम memory quota checks.
	 * Don't go beyond म_माप(entry->log).
	 */
	entry->size = len + tomoyo_round2(माप(*entry));
	spin_lock(&tomoyo_log_lock);
	अगर (tomoyo_memory_quota[TOMOYO_MEMORY_AUDIT] &&
	    tomoyo_memory_used[TOMOYO_MEMORY_AUDIT] + entry->size >=
	    tomoyo_memory_quota[TOMOYO_MEMORY_AUDIT]) अणु
		quota_exceeded = true;
	पूर्ण अन्यथा अणु
		tomoyo_memory_used[TOMOYO_MEMORY_AUDIT] += entry->size;
		list_add_tail(&entry->list, &tomoyo_log);
		tomoyo_log_count++;
	पूर्ण
	spin_unlock(&tomoyo_log_lock);
	अगर (quota_exceeded) अणु
		kमुक्त(buf);
		kमुक्त(entry);
		जाओ out;
	पूर्ण
	wake_up(&tomoyo_log_रुको);
out:
	वापस;
पूर्ण

/**
 * tomoyo_ग_लिखो_log - Write an audit log.
 *
 * @r:   Poपूर्णांकer to "struct tomoyo_request_info".
 * @fmt: The म_लिखो()'s क्रमmat string, followed by parameters.
 *
 * Returns nothing.
 */
व्योम tomoyo_ग_लिखो_log(काष्ठा tomoyo_request_info *r, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;
	पूर्णांक len;

	बहु_शुरू(args, fmt);
	len = vsnम_लिखो((अक्षर *) &len, 1, fmt, args) + 1;
	बहु_पूर्ण(args);
	बहु_शुरू(args, fmt);
	tomoyo_ग_लिखो_log2(r, len, fmt, args);
	बहु_पूर्ण(args);
पूर्ण

/**
 * tomoyo_पढ़ो_log - Read an audit log.
 *
 * @head: Poपूर्णांकer to "struct tomoyo_io_buffer".
 *
 * Returns nothing.
 */
व्योम tomoyo_पढ़ो_log(काष्ठा tomoyo_io_buffer *head)
अणु
	काष्ठा tomoyo_log *ptr = शून्य;

	अगर (head->r.w_pos)
		वापस;
	kमुक्त(head->पढ़ो_buf);
	head->पढ़ो_buf = शून्य;
	spin_lock(&tomoyo_log_lock);
	अगर (!list_empty(&tomoyo_log)) अणु
		ptr = list_entry(tomoyo_log.next, typeof(*ptr), list);
		list_del(&ptr->list);
		tomoyo_log_count--;
		tomoyo_memory_used[TOMOYO_MEMORY_AUDIT] -= ptr->size;
	पूर्ण
	spin_unlock(&tomoyo_log_lock);
	अगर (ptr) अणु
		head->पढ़ो_buf = ptr->log;
		head->r.w[head->r.w_pos++] = head->पढ़ो_buf;
		kमुक्त(ptr);
	पूर्ण
पूर्ण

/**
 * tomoyo_poll_log - Wait क्रम an audit log.
 *
 * @file: Poपूर्णांकer to "struct file".
 * @रुको: Poपूर्णांकer to "poll_table". Maybe शून्य.
 *
 * Returns EPOLLIN | EPOLLRDNORM when पढ़ोy to पढ़ो an audit log.
 */
__poll_t tomoyo_poll_log(काष्ठा file *file, poll_table *रुको)
अणु
	अगर (tomoyo_log_count)
		वापस EPOLLIN | EPOLLRDNORM;
	poll_रुको(file, &tomoyo_log_रुको, रुको);
	अगर (tomoyo_log_count)
		वापस EPOLLIN | EPOLLRDNORM;
	वापस 0;
पूर्ण
