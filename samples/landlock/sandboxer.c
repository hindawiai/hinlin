<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause
/*
 * Simple Landlock sandbox manager able to launch a process restricted by a
 * user-defined fileप्रणाली access control policy.
 *
 * Copyright तऊ 2017-2020 Mickaथ+l Salaथञn <mic@digikod.net>
 * Copyright तऊ 2020 ANSSI
 */

#घोषणा _GNU_SOURCE
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <linux/landlock.h>
#समावेश <linux/prctl.h>
#समावेश <मानकघोष.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <sys/prctl.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/syscall.h>
#समावेश <unistd.h>

#अगर_अघोषित landlock_create_ruleset
अटल अंतरभूत पूर्णांक landlock_create_ruleset(
		स्थिर काष्ठा landlock_ruleset_attr *स्थिर attr,
		स्थिर माप_प्रकार size, स्थिर __u32 flags)
अणु
	वापस syscall(__NR_landlock_create_ruleset, attr, size, flags);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित landlock_add_rule
अटल अंतरभूत पूर्णांक landlock_add_rule(स्थिर पूर्णांक ruleset_fd,
		स्थिर क्रमागत landlock_rule_type rule_type,
		स्थिर व्योम *स्थिर rule_attr, स्थिर __u32 flags)
अणु
	वापस syscall(__NR_landlock_add_rule, ruleset_fd, rule_type,
			rule_attr, flags);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित landlock_restrict_self
अटल अंतरभूत पूर्णांक landlock_restrict_self(स्थिर पूर्णांक ruleset_fd,
		स्थिर __u32 flags)
अणु
	वापस syscall(__NR_landlock_restrict_self, ruleset_fd, flags);
पूर्ण
#पूर्ण_अगर

#घोषणा ENV_FS_RO_NAME "LL_FS_RO"
#घोषणा ENV_FS_RW_NAME "LL_FS_RW"
#घोषणा ENV_PATH_TOKEN ":"

अटल पूर्णांक parse_path(अक्षर *env_path, स्थिर अक्षर ***स्थिर path_list)
अणु
	पूर्णांक i, num_paths = 0;

	अगर (env_path) अणु
		num_paths++;
		क्रम (i = 0; env_path[i]; i++) अणु
			अगर (env_path[i] == ENV_PATH_TOKEN[0])
				num_paths++;
		पूर्ण
	पूर्ण
	*path_list = दो_स्मृति(num_paths * माप(**path_list));
	क्रम (i = 0; i < num_paths; i++)
		(*path_list)[i] = strsep(&env_path, ENV_PATH_TOKEN);

	वापस num_paths;
पूर्ण

#घोषणा ACCESS_खाता ( \
	LANDLOCK_ACCESS_FS_EXECUTE | \
	LANDLOCK_ACCESS_FS_WRITE_खाता | \
	LANDLOCK_ACCESS_FS_READ_खाता)

अटल पूर्णांक populate_ruleset(
		स्थिर अक्षर *स्थिर env_var, स्थिर पूर्णांक ruleset_fd,
		स्थिर __u64 allowed_access)
अणु
	पूर्णांक num_paths, i, ret = 1;
	अक्षर *env_path_name;
	स्थिर अक्षर **path_list = शून्य;
	काष्ठा landlock_path_beneath_attr path_beneath = अणु
		.parent_fd = -1,
	पूर्ण;

	env_path_name = दो_पर्या(env_var);
	अगर (!env_path_name) अणु
		/* Prevents users to क्रमget a setting. */
		ख_लिखो(मानक_त्रुटि, "Missing environment variable %s\n", env_var);
		वापस 1;
	पूर्ण
	env_path_name = strdup(env_path_name);
	unsetenv(env_var);
	num_paths = parse_path(env_path_name, &path_list);
	अगर (num_paths == 1 && path_list[0][0] == '\0') अणु
		/*
		 * Allows to not use all possible restrictions (e.g. use
		 * LL_FS_RO without LL_FS_RW).
		 */
		ret = 0;
		जाओ out_मुक्त_name;
	पूर्ण

	क्रम (i = 0; i < num_paths; i++) अणु
		काष्ठा stat statbuf;

		path_beneath.parent_fd = खोलो(path_list[i], O_PATH |
				O_CLOEXEC);
		अगर (path_beneath.parent_fd < 0) अणु
			ख_लिखो(मानक_त्रुटि, "Failed to open \"%s\": %s\n",
					path_list[i],
					म_त्रुटि(त्रुटि_सं));
			जाओ out_मुक्त_name;
		पूर्ण
		अगर (ख_स्थिति(path_beneath.parent_fd, &statbuf)) अणु
			बंद(path_beneath.parent_fd);
			जाओ out_मुक्त_name;
		पूर्ण
		path_beneath.allowed_access = allowed_access;
		अगर (!S_ISसूची(statbuf.st_mode))
			path_beneath.allowed_access &= ACCESS_खाता;
		अगर (landlock_add_rule(ruleset_fd, LANDLOCK_RULE_PATH_BENEATH,
					&path_beneath, 0)) अणु
			ख_लिखो(मानक_त्रुटि, "Failed to update the ruleset with \"%s\": %s\n",
					path_list[i], म_त्रुटि(त्रुटि_सं));
			बंद(path_beneath.parent_fd);
			जाओ out_मुक्त_name;
		पूर्ण
		बंद(path_beneath.parent_fd);
	पूर्ण
	ret = 0;

out_मुक्त_name:
	मुक्त(env_path_name);
	वापस ret;
पूर्ण

#घोषणा ACCESS_FS_ROUGHLY_READ ( \
	LANDLOCK_ACCESS_FS_EXECUTE | \
	LANDLOCK_ACCESS_FS_READ_खाता | \
	LANDLOCK_ACCESS_FS_READ_सूची)

#घोषणा ACCESS_FS_ROUGHLY_WRITE ( \
	LANDLOCK_ACCESS_FS_WRITE_खाता | \
	LANDLOCK_ACCESS_FS_REMOVE_सूची | \
	LANDLOCK_ACCESS_FS_REMOVE_खाता | \
	LANDLOCK_ACCESS_FS_MAKE_CHAR | \
	LANDLOCK_ACCESS_FS_MAKE_सूची | \
	LANDLOCK_ACCESS_FS_MAKE_REG | \
	LANDLOCK_ACCESS_FS_MAKE_SOCK | \
	LANDLOCK_ACCESS_FS_MAKE_FIFO | \
	LANDLOCK_ACCESS_FS_MAKE_BLOCK | \
	LANDLOCK_ACCESS_FS_MAKE_SYM)

पूर्णांक मुख्य(स्थिर पूर्णांक argc, अक्षर *स्थिर argv[], अक्षर *स्थिर *स्थिर envp)
अणु
	स्थिर अक्षर *cmd_path;
	अक्षर *स्थिर *cmd_argv;
	पूर्णांक ruleset_fd;
	काष्ठा landlock_ruleset_attr ruleset_attr = अणु
		.handled_access_fs = ACCESS_FS_ROUGHLY_READ |
			ACCESS_FS_ROUGHLY_WRITE,
	पूर्ण;

	अगर (argc < 2) अणु
		ख_लिखो(मानक_त्रुटि, "usage: %s=\"...\" %s=\"...\" %s <cmd> [args]...\n\n",
				ENV_FS_RO_NAME, ENV_FS_RW_NAME, argv[0]);
		ख_लिखो(मानक_त्रुटि, "Launch a command in a restricted environment.\n\n");
		ख_लिखो(मानक_त्रुटि, "Environment variables containing paths, "
				"each separated by a colon:\n");
		ख_लिखो(मानक_त्रुटि, "* %s: list of paths allowed to be used in a read-only way.\n",
				ENV_FS_RO_NAME);
		ख_लिखो(मानक_त्रुटि, "* %s: list of paths allowed to be used in a read-write way.\n",
				ENV_FS_RW_NAME);
		ख_लिखो(मानक_त्रुटि, "\nexample:\n"
				"%s=\"/bin:/lib:/usr:/proc:/etc:/dev/urandom\" "
				"%s=\"/dev/null:/dev/full:/dev/zero:/dev/pts:/tmp\" "
				"%s bash -i\n",
				ENV_FS_RO_NAME, ENV_FS_RW_NAME, argv[0]);
		वापस 1;
	पूर्ण

	ruleset_fd = landlock_create_ruleset(&ruleset_attr, माप(ruleset_attr), 0);
	अगर (ruleset_fd < 0) अणु
		स्थिर पूर्णांक err = त्रुटि_सं;

		लिखो_त्रुटि("Failed to create a ruleset");
		चयन (err) अणु
		हाल ENOSYS:
			ख_लिखो(मानक_त्रुटि, "Hint: Landlock is not supported by the current kernel. "
					"To support it, build the kernel with "
					"CONFIG_SECURITY_LANDLOCK=y and prepend "
					"\"landlock,\" to the content of CONFIG_LSM.\n");
			अवरोध;
		हाल EOPNOTSUPP:
			ख_लिखो(मानक_त्रुटि, "Hint: Landlock is currently disabled. "
					"It can be enabled in the kernel configuration by "
					"prepending \"landlock,\" to the content of CONFIG_LSM, "
					"or at boot time by setting the same content to the "
					"\"lsm\" kernel parameter.\n");
			अवरोध;
		पूर्ण
		वापस 1;
	पूर्ण
	अगर (populate_ruleset(ENV_FS_RO_NAME, ruleset_fd,
				ACCESS_FS_ROUGHLY_READ)) अणु
		जाओ err_बंद_ruleset;
	पूर्ण
	अगर (populate_ruleset(ENV_FS_RW_NAME, ruleset_fd,
				ACCESS_FS_ROUGHLY_READ | ACCESS_FS_ROUGHLY_WRITE)) अणु
		जाओ err_बंद_ruleset;
	पूर्ण
	अगर (prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0)) अणु
		लिखो_त्रुटि("Failed to restrict privileges");
		जाओ err_बंद_ruleset;
	पूर्ण
	अगर (landlock_restrict_self(ruleset_fd, 0)) अणु
		लिखो_त्रुटि("Failed to enforce ruleset");
		जाओ err_बंद_ruleset;
	पूर्ण
	बंद(ruleset_fd);

	cmd_path = argv[1];
	cmd_argv = argv + 1;
	execvpe(cmd_path, cmd_argv, envp);
	ख_लिखो(मानक_त्रुटि, "Failed to execute \"%s\": %s\n", cmd_path,
			म_त्रुटि(त्रुटि_सं));
	ख_लिखो(मानक_त्रुटि, "Hint: access to the binary, the interpreter or "
			"shared libraries may be denied.\n");
	वापस 1;

err_बंद_ruleset:
	बंद(ruleset_fd);
	वापस 1;
पूर्ण
