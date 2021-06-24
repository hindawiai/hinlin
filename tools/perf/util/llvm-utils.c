<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2015, Wang Nan <wangnan0@huawei.com>
 * Copyright (C) 2015, Huawei Inc.
 */

#समावेश <त्रुटिसं.स>
#समावेश <सीमा.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <unistd.h>
#समावेश <linux/err.h>
#समावेश <linux/माला.स>
#समावेश <linux/zभाग.स>
#समावेश "debug.h"
#समावेश "llvm-utils.h"
#समावेश "config.h"
#समावेश "util.h"
#समावेश <sys/रुको.h>
#समावेश <subcmd/exec-cmd.h>

#घोषणा CLANG_BPF_CMD_DEFAULT_TEMPLATE				\
		"$CLANG_EXEC -D__KERNEL__ -D__NR_CPUS__=$NR_CPUS "\
		"-DLINUX_VERSION_CODE=$LINUX_VERSION_CODE "	\
		"$CLANG_OPTIONS $PERF_BPF_INC_OPTIONS $KERNEL_INC_OPTIONS " \
		"-Wno-unused-value -Wno-pointer-sign "		\
		"-working-directory $WORKING_DIR "		\
		"-c \"$CLANG_SOURCE\" -target bpf $CLANG_EMIT_LLVM -O2 -o - $LLVM_OPTIONS_PIPE"

काष्ठा llvm_param llvm_param = अणु
	.clang_path = "clang",
	.llc_path = "llc",
	.clang_bpf_cmd_ढाँचा = CLANG_BPF_CMD_DEFAULT_TEMPLATE,
	.clang_opt = शून्य,
	.opts = शून्य,
	.kbuild_dir = शून्य,
	.kbuild_opts = शून्य,
	.user_set_param = false,
पूर्ण;

पूर्णांक perf_llvm_config(स्थिर अक्षर *var, स्थिर अक्षर *value)
अणु
	अगर (!strstarts(var, "llvm."))
		वापस 0;
	var += माप("llvm.") - 1;

	अगर (!म_भेद(var, "clang-path"))
		llvm_param.clang_path = strdup(value);
	अन्यथा अगर (!म_भेद(var, "clang-bpf-cmd-template"))
		llvm_param.clang_bpf_cmd_ढाँचा = strdup(value);
	अन्यथा अगर (!म_भेद(var, "clang-opt"))
		llvm_param.clang_opt = strdup(value);
	अन्यथा अगर (!म_भेद(var, "kbuild-dir"))
		llvm_param.kbuild_dir = strdup(value);
	अन्यथा अगर (!म_भेद(var, "kbuild-opts"))
		llvm_param.kbuild_opts = strdup(value);
	अन्यथा अगर (!म_भेद(var, "dump-obj"))
		llvm_param.dump_obj = !!perf_config_bool(var, value);
	अन्यथा अगर (!म_भेद(var, "opts"))
		llvm_param.opts = strdup(value);
	अन्यथा अणु
		pr_debug("Invalid LLVM config option: %s\n", value);
		वापस -1;
	पूर्ण
	llvm_param.user_set_param = true;
	वापस 0;
पूर्ण

अटल पूर्णांक
search_program(स्थिर अक्षर *def, स्थिर अक्षर *name,
	       अक्षर *output)
अणु
	अक्षर *env, *path, *पंचांगp = शून्य;
	अक्षर buf[PATH_MAX];
	पूर्णांक ret;

	output[0] = '\0';
	अगर (def && def[0] != '\0') अणु
		अगर (def[0] == '/') अणु
			अगर (access(def, F_OK) == 0) अणु
				strlcpy(output, def, PATH_MAX);
				वापस 0;
			पूर्ण
		पूर्ण अन्यथा अगर (def[0] != '\0')
			name = def;
	पूर्ण

	env = दो_पर्या("PATH");
	अगर (!env)
		वापस -1;
	env = strdup(env);
	अगर (!env)
		वापस -1;

	ret = -ENOENT;
	path = म_मोहर_r(env, ":",  &पंचांगp);
	जबतक (path) अणु
		scnम_लिखो(buf, माप(buf), "%s/%s", path, name);
		अगर (access(buf, F_OK) == 0) अणु
			strlcpy(output, buf, PATH_MAX);
			ret = 0;
			अवरोध;
		पूर्ण
		path = म_मोहर_r(शून्य, ":", &पंचांगp);
	पूर्ण

	मुक्त(env);
	वापस ret;
पूर्ण

#घोषणा READ_SIZE	4096
अटल पूर्णांक
पढ़ो_from_pipe(स्थिर अक्षर *cmd, व्योम **p_buf, माप_प्रकार *p_पढ़ो_sz)
अणु
	पूर्णांक err = 0;
	व्योम *buf = शून्य;
	खाता *file = शून्य;
	माप_प्रकार पढ़ो_sz = 0, buf_sz = 0;
	अक्षर serr[STRERR_बफ_मानE];

	file = pखोलो(cmd, "r");
	अगर (!file) अणु
		pr_err("ERROR: unable to popen cmd: %s\n",
		       str_error_r(त्रुटि_सं, serr, माप(serr)));
		वापस -EINVAL;
	पूर्ण

	जबतक (!ख_पूर्ण(file) && !ख_त्रुटि(file)) अणु
		/*
		 * Make buf_sz always have obe byte extra space so we
		 * can put '\0' there.
		 */
		अगर (buf_sz - पढ़ो_sz < READ_SIZE + 1) अणु
			व्योम *new_buf;

			buf_sz = पढ़ो_sz + READ_SIZE + 1;
			new_buf = पुनः_स्मृति(buf, buf_sz);

			अगर (!new_buf) अणु
				pr_err("ERROR: failed to realloc memory\n");
				err = -ENOMEM;
				जाओ errout;
			पूर्ण

			buf = new_buf;
		पूर्ण
		पढ़ो_sz += ख_पढ़ो(buf + पढ़ो_sz, 1, READ_SIZE, file);
	पूर्ण

	अगर (buf_sz - पढ़ो_sz < 1) अणु
		pr_err("ERROR: internal error\n");
		err = -EINVAL;
		जाओ errout;
	पूर्ण

	अगर (ख_त्रुटि(file)) अणु
		pr_err("ERROR: error occurred when reading from pipe: %s\n",
		       str_error_r(त्रुटि_सं, serr, माप(serr)));
		err = -EIO;
		जाओ errout;
	पूर्ण

	err = WEXITSTATUS(pबंद(file));
	file = शून्य;
	अगर (err) अणु
		err = -EINVAL;
		जाओ errout;
	पूर्ण

	/*
	 * If buf is string, give it terminal '\0' to make our lअगरe
	 * easier. If buf is not string, that '\0' is out of space
	 * indicated by पढ़ो_sz so caller won't even notice it.
	 */
	((अक्षर *)buf)[पढ़ो_sz] = '\0';

	अगर (!p_buf)
		मुक्त(buf);
	अन्यथा
		*p_buf = buf;

	अगर (p_पढ़ो_sz)
		*p_पढ़ो_sz = पढ़ो_sz;
	वापस 0;

errout:
	अगर (file)
		pबंद(file);
	मुक्त(buf);
	अगर (p_buf)
		*p_buf = शून्य;
	अगर (p_पढ़ो_sz)
		*p_पढ़ो_sz = 0;
	वापस err;
पूर्ण

अटल अंतरभूत व्योम
क्रमce_set_env(स्थिर अक्षर *var, स्थिर अक्षर *value)
अणु
	अगर (value) अणु
		setenv(var, value, 1);
		pr_debug("set env: %s=%s\n", var, value);
	पूर्ण अन्यथा अणु
		unsetenv(var);
		pr_debug("unset env: %s\n", var);
	पूर्ण
पूर्ण

अटल व्योम
version_notice(व्योम)
अणु
	pr_err(
"     \tLLVM 3.7 or newer is required. Which can be found from http://llvm.org\n"
"     \tYou may want to try git trunk:\n"
"     \t\tgit clone http://llvm.org/git/llvm.git\n"
"     \t\t     and\n"
"     \t\tgit clone http://llvm.org/git/clang.git\n\n"
"     \tOr fetch the latest clang/llvm 3.7 from pre-built llvm packages for\n"
"     \tdebian/ubuntu:\n"
"     \t\thttp://llvm.org/apt\n\n"
"     \tIf you are using old version of clang, change 'clang-bpf-cmd-template'\n"
"     \toption in [llvm] section of ~/.perfconfig to:\n\n"
"     \t  \"$CLANG_EXEC $CLANG_OPTIONS $KERNEL_INC_OPTIONS $PERF_BPF_INC_OPTIONS \\\n"
"     \t     -working-directory $WORKING_DIR -c $CLANG_SOURCE \\\n"
"     \t     -emit-llvm -o - | /path/to/llc -march=bpf -filetype=obj -o -\"\n"
"     \t(Replace /path/to/llc with path to your llc)\n\n"
);
पूर्ण

अटल पूर्णांक detect_kbuild_dir(अक्षर **kbuild_dir)
अणु
	स्थिर अक्षर *test_dir = llvm_param.kbuild_dir;
	स्थिर अक्षर *prefix_dir = "";
	स्थिर अक्षर *suffix_dir = "";

	/* _UTSNAME_LENGTH is 65 */
	अक्षर release[128];

	अक्षर *स्वतःconf_path;

	पूर्णांक err;

	अगर (!test_dir) अणु
		err = fetch_kernel_version(शून्य, release,
					   माप(release));
		अगर (err)
			वापस -EINVAL;

		test_dir = release;
		prefix_dir = "/lib/modules/";
		suffix_dir = "/build";
	पूर्ण

	err = aप्र_लिखो(&स्वतःconf_path, "%s%s%s/include/generated/autoconf.h",
		       prefix_dir, test_dir, suffix_dir);
	अगर (err < 0)
		वापस -ENOMEM;

	अगर (access(स्वतःconf_path, R_OK) == 0) अणु
		मुक्त(स्वतःconf_path);

		err = aप्र_लिखो(kbuild_dir, "%s%s%s", prefix_dir, test_dir,
			       suffix_dir);
		अगर (err < 0)
			वापस -ENOMEM;
		वापस 0;
	पूर्ण
	pr_debug("%s: Couldn't find \"%s\", missing kernel-devel package?.\n",
		 __func__, स्वतःconf_path);
	मुक्त(स्वतःconf_path);
	वापस -ENOENT;
पूर्ण

अटल स्थिर अक्षर *kinc_fetch_script =
"#!/usr/bin/env sh\n"
"if ! test -d \"$KBUILD_DIR\"\n"
"then\n"
"	exit 1\n"
"fi\n"
"if ! test -f \"$KBUILD_DIR/include/generated/autoconf.h\"\n"
"then\n"
"	exit 1\n"
"fi\n"
"TMPDIR=`mktemp -d`\n"
"if test -z \"$TMPDIR\"\n"
"then\n"
"    exit 1\n"
"fi\n"
"cat << EOF > $TMPDIR/Makefile\n"
"obj-y := dummy.o\n"
"\\$(obj)/%.o: \\$(src)/%.c\n"
"\t@echo -n \"\\$(NOSTDINC_FLAGS) \\$(LINUXINCLUDE) \\$(EXTRA_CFLAGS)\"\n"
"\t\\$(CC) -c -o \\$@ \\$<\n"
"EOF\n"
"touch $TMPDIR/dummy.c\n"
"make -s -C $KBUILD_DIR M=$TMPDIR $KBUILD_OPTS dummy.o 2>/dev/null\n"
"RET=$?\n"
"rm -rf $TMPDIR\n"
"exit $RET\n";

व्योम llvm__get_kbuild_opts(अक्षर **kbuild_dir, अक्षर **kbuild_include_opts)
अणु
	अटल अक्षर *saved_kbuild_dir;
	अटल अक्षर *saved_kbuild_include_opts;
	पूर्णांक err;

	अगर (!kbuild_dir || !kbuild_include_opts)
		वापस;

	*kbuild_dir = शून्य;
	*kbuild_include_opts = शून्य;

	अगर (saved_kbuild_dir && saved_kbuild_include_opts &&
	    !IS_ERR(saved_kbuild_dir) && !IS_ERR(saved_kbuild_include_opts)) अणु
		*kbuild_dir = strdup(saved_kbuild_dir);
		*kbuild_include_opts = strdup(saved_kbuild_include_opts);

		अगर (*kbuild_dir && *kbuild_include_opts)
			वापस;

		zमुक्त(kbuild_dir);
		zमुक्त(kbuild_include_opts);
		/*
		 * Don't fall through: it may अवरोधs saved_kbuild_dir and
		 * saved_kbuild_include_opts अगर detect them again when
		 * memory is low.
		 */
		वापस;
	पूर्ण

	अगर (llvm_param.kbuild_dir && !llvm_param.kbuild_dir[0]) अणु
		pr_debug("[llvm.kbuild-dir] is set to \"\" deliberately.\n");
		pr_debug("Skip kbuild options detection.\n");
		जाओ errout;
	पूर्ण

	err = detect_kbuild_dir(kbuild_dir);
	अगर (err) अणु
		pr_warning(
"WARNING:\tunable to get correct kernel building directory.\n"
"Hint:\tSet correct kbuild directory using 'kbuild-dir' option in [llvm]\n"
"     \tsection of ~/.perfconfig or set it to \"\" to suppress kbuild\n"
"     \tdetection.\n\n");
		जाओ errout;
	पूर्ण

	pr_debug("Kernel build dir is set to %s\n", *kbuild_dir);
	क्रमce_set_env("KBUILD_DIR", *kbuild_dir);
	क्रमce_set_env("KBUILD_OPTS", llvm_param.kbuild_opts);
	err = पढ़ो_from_pipe(kinc_fetch_script,
			     (व्योम **)kbuild_include_opts,
			     शून्य);
	अगर (err) अणु
		pr_warning(
"WARNING:\tunable to get kernel include directories from '%s'\n"
"Hint:\tTry set clang include options using 'clang-bpf-cmd-template'\n"
"     \toption in [llvm] section of ~/.perfconfig and set 'kbuild-dir'\n"
"     \toption in [llvm] to \"\" to suppress this detection.\n\n",
			*kbuild_dir);

		zमुक्त(kbuild_dir);
		जाओ errout;
	पूर्ण

	pr_debug("include option is set to %s\n", *kbuild_include_opts);

	saved_kbuild_dir = strdup(*kbuild_dir);
	saved_kbuild_include_opts = strdup(*kbuild_include_opts);

	अगर (!saved_kbuild_dir || !saved_kbuild_include_opts) अणु
		zमुक्त(&saved_kbuild_dir);
		zमुक्त(&saved_kbuild_include_opts);
	पूर्ण
	वापस;
errout:
	saved_kbuild_dir = ERR_PTR(-EINVAL);
	saved_kbuild_include_opts = ERR_PTR(-EINVAL);
पूर्ण

पूर्णांक llvm__get_nr_cpus(व्योम)
अणु
	अटल पूर्णांक nr_cpus_avail = 0;
	अक्षर serr[STRERR_बफ_मानE];

	अगर (nr_cpus_avail > 0)
		वापस nr_cpus_avail;

	nr_cpus_avail = sysconf(_SC_NPROCESSORS_CONF);
	अगर (nr_cpus_avail <= 0) अणु
		pr_err(
"WARNING:\tunable to get available CPUs in this system: %s\n"
"        \tUse 128 instead.\n", str_error_r(त्रुटि_सं, serr, माप(serr)));
		nr_cpus_avail = 128;
	पूर्ण
	वापस nr_cpus_avail;
पूर्ण

व्योम llvm__dump_obj(स्थिर अक्षर *path, व्योम *obj_buf, माप_प्रकार size)
अणु
	अक्षर *obj_path = strdup(path);
	खाता *fp;
	अक्षर *p;

	अगर (!obj_path) अणु
		pr_warning("WARNING: Not enough memory, skip object dumping\n");
		वापस;
	पूर्ण

	p = म_खोजप(obj_path, '.');
	अगर (!p || (म_भेद(p, ".c") != 0)) अणु
		pr_warning("WARNING: invalid llvm source path: '%s', skip object dumping\n",
			   obj_path);
		जाओ out;
	पूर्ण

	p[1] = 'o';
	fp = ख_खोलो(obj_path, "wb");
	अगर (!fp) अणु
		pr_warning("WARNING: failed to open '%s': %s, skip object dumping\n",
			   obj_path, म_त्रुटि(त्रुटि_सं));
		जाओ out;
	पूर्ण

	pr_debug("LLVM: dumping %s\n", obj_path);
	अगर (ख_डालो(obj_buf, size, 1, fp) != 1)
		pr_debug("WARNING: failed to write to file '%s': %s, skip object dumping\n", obj_path, म_त्रुटि(त्रुटि_सं));
	ख_बंद(fp);
out:
	मुक्त(obj_path);
पूर्ण

पूर्णांक llvm__compile_bpf(स्थिर अक्षर *path, व्योम **p_obj_buf,
		      माप_प्रकार *p_obj_buf_sz)
अणु
	माप_प्रकार obj_buf_sz;
	व्योम *obj_buf = शून्य;
	पूर्णांक err, nr_cpus_avail;
	अचिन्हित पूर्णांक kernel_version;
	अक्षर linux_version_code_str[64];
	स्थिर अक्षर *clang_opt = llvm_param.clang_opt;
	अक्षर clang_path[PATH_MAX], llc_path[PATH_MAX], असलpath[PATH_MAX], nr_cpus_avail_str[64];
	अक्षर serr[STRERR_बफ_मानE];
	अक्षर *kbuild_dir = शून्य, *kbuild_include_opts = शून्य,
	     *perf_bpf_include_opts = शून्य;
	स्थिर अक्षर *ढाँचा = llvm_param.clang_bpf_cmd_ढाँचा;
	अक्षर *pipe_ढाँचा = शून्य;
	स्थिर अक्षर *opts = llvm_param.opts;
	अक्षर *command_echo = शून्य, *command_out;
	अक्षर *perf_include_dir = प्रणाली_path(PERF_INCLUDE_सूची);

	अगर (path[0] != '-' && realpath(path, असलpath) == शून्य) अणु
		err = त्रुटि_सं;
		pr_err("ERROR: problems with path %s: %s\n",
		       path, str_error_r(err, serr, माप(serr)));
		वापस -err;
	पूर्ण

	अगर (!ढाँचा)
		ढाँचा = CLANG_BPF_CMD_DEFAULT_TEMPLATE;

	err = search_program(llvm_param.clang_path,
			     "clang", clang_path);
	अगर (err) अणु
		pr_err(
"ERROR:\tunable to find clang.\n"
"Hint:\tTry to install latest clang/llvm to support BPF. Check your $PATH\n"
"     \tand 'clang-path' option in [llvm] section of ~/.perfconfig.\n");
		version_notice();
		वापस -ENOENT;
	पूर्ण

	/*
	 * This is an optional work. Even it fail we can जारी our
	 * work. Needn't check error वापस.
	 */
	llvm__get_kbuild_opts(&kbuild_dir, &kbuild_include_opts);

	nr_cpus_avail = llvm__get_nr_cpus();
	snम_लिखो(nr_cpus_avail_str, माप(nr_cpus_avail_str), "%d",
		 nr_cpus_avail);

	अगर (fetch_kernel_version(&kernel_version, शून्य, 0))
		kernel_version = 0;

	snम_लिखो(linux_version_code_str, माप(linux_version_code_str),
		 "0x%x", kernel_version);
	अगर (aप्र_लिखो(&perf_bpf_include_opts, "-I%s/bpf", perf_include_dir) < 0)
		जाओ errout;
	क्रमce_set_env("NR_CPUS", nr_cpus_avail_str);
	क्रमce_set_env("LINUX_VERSION_CODE", linux_version_code_str);
	क्रमce_set_env("CLANG_EXEC", clang_path);
	क्रमce_set_env("CLANG_OPTIONS", clang_opt);
	क्रमce_set_env("KERNEL_INC_OPTIONS", kbuild_include_opts);
	क्रमce_set_env("PERF_BPF_INC_OPTIONS", perf_bpf_include_opts);
	क्रमce_set_env("WORKING_DIR", kbuild_dir ? : ".");

	अगर (opts) अणु
		err = search_program(llvm_param.llc_path, "llc", llc_path);
		अगर (err) अणु
			pr_err("ERROR:\tunable to find llc.\n"
			       "Hint:\tTry to install latest clang/llvm to support BPF. Check your $PATH\n"
			       "     \tand 'llc-path' option in [llvm] section of ~/.perfconfig.\n");
			version_notice();
			जाओ errout;
		पूर्ण

		अगर (aप्र_लिखो(&pipe_ढाँचा, "%s -emit-llvm | %s -march=bpf %s -filetype=obj -o -",
			      ढाँचा, llc_path, opts) < 0) अणु
			pr_err("ERROR:\tnot enough memory to setup command line\n");
			जाओ errout;
		पूर्ण

		ढाँचा = pipe_ढाँचा;

	पूर्ण

	/*
	 * Since we may reset clang's working dir, path of source file
	 * should be transferred पूर्णांकo असलolute path, except we want
	 * मानक_निवेश to be source file (testing).
	 */
	क्रमce_set_env("CLANG_SOURCE",
		      (path[0] == '-') ? path : असलpath);

	pr_debug("llvm compiling command template: %s\n", ढाँचा);

	अगर (aप्र_लिखो(&command_echo, "echo -n \"%s\"", ढाँचा) < 0)
		जाओ errout;

	err = पढ़ो_from_pipe(command_echo, (व्योम **) &command_out, शून्य);
	अगर (err)
		जाओ errout;

	pr_debug("llvm compiling command : %s\n", command_out);

	err = पढ़ो_from_pipe(ढाँचा, &obj_buf, &obj_buf_sz);
	अगर (err) अणु
		pr_err("ERROR:\tunable to compile %s\n", path);
		pr_err("Hint:\tCheck error message shown above.\n");
		pr_err("Hint:\tYou can also pre-compile it into .o using:\n");
		pr_err("     \t\tclang -target bpf -O2 -c %s\n", path);
		pr_err("     \twith proper -I and -D options.\n");
		जाओ errout;
	पूर्ण

	मुक्त(command_echo);
	मुक्त(command_out);
	मुक्त(kbuild_dir);
	मुक्त(kbuild_include_opts);
	मुक्त(perf_bpf_include_opts);
	मुक्त(perf_include_dir);

	अगर (!p_obj_buf)
		मुक्त(obj_buf);
	अन्यथा
		*p_obj_buf = obj_buf;

	अगर (p_obj_buf_sz)
		*p_obj_buf_sz = obj_buf_sz;
	वापस 0;
errout:
	मुक्त(command_echo);
	मुक्त(kbuild_dir);
	मुक्त(kbuild_include_opts);
	मुक्त(obj_buf);
	मुक्त(perf_bpf_include_opts);
	मुक्त(perf_include_dir);
	मुक्त(pipe_ढाँचा);
	अगर (p_obj_buf)
		*p_obj_buf = शून्य;
	अगर (p_obj_buf_sz)
		*p_obj_buf_sz = 0;
	वापस err;
पूर्ण

पूर्णांक llvm__search_clang(व्योम)
अणु
	अक्षर clang_path[PATH_MAX];

	वापस search_program(llvm_param.clang_path, "clang", clang_path);
पूर्ण
