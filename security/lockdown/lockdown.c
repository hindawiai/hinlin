<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Lock करोwn the kernel
 *
 * Copyright (C) 2016 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public Licence
 * as published by the Free Software Foundation; either version
 * 2 of the Licence, or (at your option) any later version.
 */

#समावेश <linux/security.h>
#समावेश <linux/export.h>
#समावेश <linux/lsm_hooks.h>

अटल क्रमागत lockकरोwn_reason kernel_locked_करोwn;

अटल स्थिर क्रमागत lockकरोwn_reason lockकरोwn_levels[] = अणुLOCKDOWN_NONE,
						 LOCKDOWN_INTEGRITY_MAX,
						 LOCKDOWN_CONFIDENTIALITY_MAXपूर्ण;

/*
 * Put the kernel पूर्णांकo lock-करोwn mode.
 */
अटल पूर्णांक lock_kernel_करोwn(स्थिर अक्षर *where, क्रमागत lockकरोwn_reason level)
अणु
	अगर (kernel_locked_करोwn >= level)
		वापस -EPERM;

	kernel_locked_करोwn = level;
	pr_notice("Kernel is locked down from %s; see man kernel_lockdown.7\n",
		  where);
	वापस 0;
पूर्ण

अटल पूर्णांक __init lockकरोwn_param(अक्षर *level)
अणु
	अगर (!level)
		वापस -EINVAL;

	अगर (म_भेद(level, "integrity") == 0)
		lock_kernel_करोwn("command line", LOCKDOWN_INTEGRITY_MAX);
	अन्यथा अगर (म_भेद(level, "confidentiality") == 0)
		lock_kernel_करोwn("command line", LOCKDOWN_CONFIDENTIALITY_MAX);
	अन्यथा
		वापस -EINVAL;

	वापस 0;
पूर्ण

early_param("lockdown", lockकरोwn_param);

/**
 * lockकरोwn_is_locked_करोwn - Find out अगर the kernel is locked करोwn
 * @what: Tag to use in notice generated अगर lockकरोwn is in effect
 */
अटल पूर्णांक lockकरोwn_is_locked_करोwn(क्रमागत lockकरोwn_reason what)
अणु
	अगर (WARN(what >= LOCKDOWN_CONFIDENTIALITY_MAX,
		 "Invalid lockdown reason"))
		वापस -EPERM;

	अगर (kernel_locked_करोwn >= what) अणु
		अगर (lockकरोwn_reasons[what])
			pr_notice("Lockdown: %s: %s is restricted; see man kernel_lockdown.7\n",
				  current->comm, lockकरोwn_reasons[what]);
		वापस -EPERM;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा security_hook_list lockकरोwn_hooks[] __lsm_ro_after_init = अणु
	LSM_HOOK_INIT(locked_करोwn, lockकरोwn_is_locked_करोwn),
पूर्ण;

अटल पूर्णांक __init lockकरोwn_lsm_init(व्योम)
अणु
#अगर defined(CONFIG_LOCK_DOWN_KERNEL_FORCE_INTEGRITY)
	lock_kernel_करोwn("Kernel configuration", LOCKDOWN_INTEGRITY_MAX);
#या_अगर defined(CONFIG_LOCK_DOWN_KERNEL_FORCE_CONFIDENTIALITY)
	lock_kernel_करोwn("Kernel configuration", LOCKDOWN_CONFIDENTIALITY_MAX);
#पूर्ण_अगर
	security_add_hooks(lockकरोwn_hooks, ARRAY_SIZE(lockकरोwn_hooks),
			   "lockdown");
	वापस 0;
पूर्ण

अटल sमाप_प्रकार lockकरोwn_पढ़ो(काष्ठा file *filp, अक्षर __user *buf, माप_प्रकार count,
			     loff_t *ppos)
अणु
	अक्षर temp[80];
	पूर्णांक i, offset = 0;

	क्रम (i = 0; i < ARRAY_SIZE(lockकरोwn_levels); i++) अणु
		क्रमागत lockकरोwn_reason level = lockकरोwn_levels[i];

		अगर (lockकरोwn_reasons[level]) अणु
			स्थिर अक्षर *label = lockकरोwn_reasons[level];

			अगर (kernel_locked_करोwn == level)
				offset += प्र_लिखो(temp+offset, "[%s] ", label);
			अन्यथा
				offset += प्र_लिखो(temp+offset, "%s ", label);
		पूर्ण
	पूर्ण

	/* Convert the last space to a newline अगर needed. */
	अगर (offset > 0)
		temp[offset-1] = '\n';

	वापस simple_पढ़ो_from_buffer(buf, count, ppos, temp, म_माप(temp));
पूर्ण

अटल sमाप_प्रकार lockकरोwn_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
			      माप_प्रकार n, loff_t *ppos)
अणु
	अक्षर *state;
	पूर्णांक i, len, err = -EINVAL;

	state = memdup_user_nul(buf, n);
	अगर (IS_ERR(state))
		वापस PTR_ERR(state);

	len = म_माप(state);
	अगर (len && state[len-1] == '\n') अणु
		state[len-1] = '\0';
		len--;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(lockकरोwn_levels); i++) अणु
		क्रमागत lockकरोwn_reason level = lockकरोwn_levels[i];
		स्थिर अक्षर *label = lockकरोwn_reasons[level];

		अगर (label && !म_भेद(state, label))
			err = lock_kernel_करोwn("securityfs", level);
	पूर्ण

	kमुक्त(state);
	वापस err ? err : n;
पूर्ण

अटल स्थिर काष्ठा file_operations lockकरोwn_ops = अणु
	.पढ़ो  = lockकरोwn_पढ़ो,
	.ग_लिखो = lockकरोwn_ग_लिखो,
पूर्ण;

अटल पूर्णांक __init lockकरोwn_secfs_init(व्योम)
अणु
	काष्ठा dentry *dentry;

	dentry = securityfs_create_file("lockdown", 0644, शून्य, शून्य,
					&lockकरोwn_ops);
	वापस PTR_ERR_OR_ZERO(dentry);
पूर्ण

core_initcall(lockकरोwn_secfs_init);

#अगर_घोषित CONFIG_SECURITY_LOCKDOWN_LSM_EARLY
DEFINE_EARLY_LSM(lockकरोwn) = अणु
#अन्यथा
DEFINE_LSM(lockकरोwn) = अणु
#पूर्ण_अगर
	.name = "lockdown",
	.init = lockकरोwn_lsm_init,
पूर्ण;
