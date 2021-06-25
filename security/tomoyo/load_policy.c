<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * security/tomoyo/load_policy.c
 *
 * Copyright (C) 2005-2011  NTT DATA CORPORATION
 */

#समावेश "common.h"

#अगर_अघोषित CONFIG_SECURITY_TOMOYO_OMIT_USERSPACE_LOADER

/*
 * Path to the policy loader. (शेष = CONFIG_SECURITY_TOMOYO_POLICY_LOADER)
 */
अटल स्थिर अक्षर *tomoyo_loader;

/**
 * tomoyo_loader_setup - Set policy loader.
 *
 * @str: Program to use as a policy loader (e.g. /sbin/tomoyo-init ).
 *
 * Returns 0.
 */
अटल पूर्णांक __init tomoyo_loader_setup(अक्षर *str)
अणु
	tomoyo_loader = str;
	वापस 0;
पूर्ण

__setup("TOMOYO_loader=", tomoyo_loader_setup);

/**
 * tomoyo_policy_loader_exists - Check whether /sbin/tomoyo-init exists.
 *
 * Returns true अगर /sbin/tomoyo-init exists, false otherwise.
 */
अटल bool tomoyo_policy_loader_exists(व्योम)
अणु
	काष्ठा path path;

	अगर (!tomoyo_loader)
		tomoyo_loader = CONFIG_SECURITY_TOMOYO_POLICY_LOADER;
	अगर (kern_path(tomoyo_loader, LOOKUP_FOLLOW, &path)) अणु
		pr_info("Not activating Mandatory Access Control as %s does not exist.\n",
			tomoyo_loader);
		वापस false;
	पूर्ण
	path_put(&path);
	वापस true;
पूर्ण

/*
 * Path to the trigger. (शेष = CONFIG_SECURITY_TOMOYO_ACTIVATION_TRIGGER)
 */
अटल स्थिर अक्षर *tomoyo_trigger;

/**
 * tomoyo_trigger_setup - Set trigger क्रम activation.
 *
 * @str: Program to use as an activation trigger (e.g. /sbin/init ).
 *
 * Returns 0.
 */
अटल पूर्णांक __init tomoyo_trigger_setup(अक्षर *str)
अणु
	tomoyo_trigger = str;
	वापस 0;
पूर्ण

__setup("TOMOYO_trigger=", tomoyo_trigger_setup);

/**
 * tomoyo_load_policy - Run बाह्यal policy loader to load policy.
 *
 * @filename: The program about to start.
 *
 * This function checks whether @filename is /sbin/init , and अगर so
 * invoke /sbin/tomoyo-init and रुको क्रम the termination of /sbin/tomoyo-init
 * and then जारीs invocation of /sbin/init.
 * /sbin/tomoyo-init पढ़ोs policy files in /etc/tomoyo/ directory and
 * ग_लिखोs to /sys/kernel/security/tomoyo/ पूर्णांकerfaces.
 *
 * Returns nothing.
 */
व्योम tomoyo_load_policy(स्थिर अक्षर *filename)
अणु
	अटल bool करोne;
	अक्षर *argv[2];
	अक्षर *envp[3];

	अगर (tomoyo_policy_loaded || करोne)
		वापस;
	अगर (!tomoyo_trigger)
		tomoyo_trigger = CONFIG_SECURITY_TOMOYO_ACTIVATION_TRIGGER;
	अगर (म_भेद(filename, tomoyo_trigger))
		वापस;
	अगर (!tomoyo_policy_loader_exists())
		वापस;
	करोne = true;
	pr_info("Calling %s to load policy. Please wait.\n", tomoyo_loader);
	argv[0] = (अक्षर *) tomoyo_loader;
	argv[1] = शून्य;
	envp[0] = "HOME=/";
	envp[1] = "PATH=/sbin:/bin:/usr/sbin:/usr/bin";
	envp[2] = शून्य;
	call_usermodehelper(argv[0], argv, envp, UMH_WAIT_PROC);
	tomoyo_check_profile();
पूर्ण

#पूर्ण_अगर
