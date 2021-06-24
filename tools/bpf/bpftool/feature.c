<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause)
/* Copyright (c) 2019 Netronome Systems, Inc. */

#समावेश <प्रकार.स>
#समावेश <त्रुटिसं.स>
#समावेश <माला.स>
#समावेश <unistd.h>
#समावेश <net/अगर.h>
#अगर_घोषित USE_LIBCAP
#समावेश <sys/capability.h>
#पूर्ण_अगर
#समावेश <sys/utsname.h>
#समावेश <sys/vfs.h>

#समावेश <linux/filter.h>
#समावेश <linux/सीमा.स>

#समावेश <bpf/bpf.h>
#समावेश <bpf/libbpf.h>
#समावेश <zlib.h>

#समावेश "main.h"

#अगर_अघोषित PROC_SUPER_MAGIC
# define PROC_SUPER_MAGIC	0x9fa0
#पूर्ण_अगर

क्रमागत probe_component अणु
	COMPONENT_UNSPEC,
	COMPONENT_KERNEL,
	COMPONENT_DEVICE,
पूर्ण;

#घोषणा BPF_HELPER_MAKE_ENTRY(name)	[BPF_FUNC_ ## name] = "bpf_" # name
अटल स्थिर अक्षर * स्थिर helper_name[] = अणु
	__BPF_FUNC_MAPPER(BPF_HELPER_MAKE_ENTRY)
पूर्ण;

#अघोषित BPF_HELPER_MAKE_ENTRY

अटल bool full_mode;
#अगर_घोषित USE_LIBCAP
अटल bool run_as_unprivileged;
#पूर्ण_अगर

/* Miscellaneous utility functions */

अटल bool check_procfs(व्योम)
अणु
	काष्ठा statfs st_fs;

	अगर (statfs("/proc", &st_fs) < 0)
		वापस false;
	अगर ((अचिन्हित दीर्घ)st_fs.f_type != PROC_SUPER_MAGIC)
		वापस false;

	वापस true;
पूर्ण

अटल व्योम upperहाल(अक्षर *str, माप_प्रकार len)
अणु
	माप_प्रकार i;

	क्रम (i = 0; i < len && str[i] != '\0'; i++)
		str[i] = बड़े(str[i]);
पूर्ण

/* Prपूर्णांकing utility functions */

अटल व्योम
prपूर्णांक_bool_feature(स्थिर अक्षर *feat_name, स्थिर अक्षर *plain_name,
		   स्थिर अक्षर *define_name, bool res, स्थिर अक्षर *define_prefix)
अणु
	अगर (json_output)
		jsonw_bool_field(json_wtr, feat_name, res);
	अन्यथा अगर (define_prefix)
		म_लिखो("#define %s%sHAVE_%s\n", define_prefix,
		       res ? "" : "NO_", define_name);
	अन्यथा
		म_लिखो("%s is %savailable\n", plain_name, res ? "" : "NOT ");
पूर्ण

अटल व्योम prपूर्णांक_kernel_option(स्थिर अक्षर *name, स्थिर अक्षर *value,
				स्थिर अक्षर *define_prefix)
अणु
	अक्षर *endptr;
	पूर्णांक res;

	अगर (json_output) अणु
		अगर (!value) अणु
			jsonw_null_field(json_wtr, name);
			वापस;
		पूर्ण
		त्रुटि_सं = 0;
		res = म_से_दीर्घ(value, &endptr, 0);
		अगर (!त्रुटि_सं && *endptr == '\n')
			jsonw_पूर्णांक_field(json_wtr, name, res);
		अन्यथा
			jsonw_string_field(json_wtr, name, value);
	पूर्ण अन्यथा अगर (define_prefix) अणु
		अगर (value)
			म_लिखो("#define %s%s %s\n", define_prefix,
			       name, value);
		अन्यथा
			म_लिखो("/* %s%s is not set */\n", define_prefix, name);
	पूर्ण अन्यथा अणु
		अगर (value)
			म_लिखो("%s is set to %s\n", name, value);
		अन्यथा
			म_लिखो("%s is not set\n", name);
	पूर्ण
पूर्ण

अटल व्योम
prपूर्णांक_start_section(स्थिर अक्षर *json_title, स्थिर अक्षर *plain_title,
		    स्थिर अक्षर *define_comment, स्थिर अक्षर *define_prefix)
अणु
	अगर (json_output) अणु
		jsonw_name(json_wtr, json_title);
		jsonw_start_object(json_wtr);
	पूर्ण अन्यथा अगर (define_prefix) अणु
		म_लिखो("%s\n", define_comment);
	पूर्ण अन्यथा अणु
		म_लिखो("%s\n", plain_title);
	पूर्ण
पूर्ण

अटल व्योम prपूर्णांक_end_section(व्योम)
अणु
	अगर (json_output)
		jsonw_end_object(json_wtr);
	अन्यथा
		म_लिखो("\n");
पूर्ण

/* Probing functions */

अटल पूर्णांक पढ़ो_procfs(स्थिर अक्षर *path)
अणु
	अक्षर *endptr, *line = शून्य;
	माप_प्रकार len = 0;
	खाता *fd;
	पूर्णांक res;

	fd = ख_खोलो(path, "r");
	अगर (!fd)
		वापस -1;

	res = getline(&line, &len, fd);
	ख_बंद(fd);
	अगर (res < 0)
		वापस -1;

	त्रुटि_सं = 0;
	res = म_से_दीर्घ(line, &endptr, 10);
	अगर (त्रुटि_सं || *line == '\0' || *endptr != '\n')
		res = -1;
	मुक्त(line);

	वापस res;
पूर्ण

अटल व्योम probe_unprivileged_disabled(व्योम)
अणु
	पूर्णांक res;

	/* No support क्रम C-style ouptut */

	res = पढ़ो_procfs("/proc/sys/kernel/unprivileged_bpf_disabled");
	अगर (json_output) अणु
		jsonw_पूर्णांक_field(json_wtr, "unprivileged_bpf_disabled", res);
	पूर्ण अन्यथा अणु
		चयन (res) अणु
		हाल 0:
			म_लिखो("bpf() syscall for unprivileged users is enabled\n");
			अवरोध;
		हाल 1:
			म_लिखो("bpf() syscall restricted to privileged users\n");
			अवरोध;
		हाल -1:
			म_लिखो("Unable to retrieve required privileges for bpf() syscall\n");
			अवरोध;
		शेष:
			म_लिखो("bpf() syscall restriction has unknown value %d\n", res);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम probe_jit_enable(व्योम)
अणु
	पूर्णांक res;

	/* No support क्रम C-style ouptut */

	res = पढ़ो_procfs("/proc/sys/net/core/bpf_jit_enable");
	अगर (json_output) अणु
		jsonw_पूर्णांक_field(json_wtr, "bpf_jit_enable", res);
	पूर्ण अन्यथा अणु
		चयन (res) अणु
		हाल 0:
			म_लिखो("JIT compiler is disabled\n");
			अवरोध;
		हाल 1:
			म_लिखो("JIT compiler is enabled\n");
			अवरोध;
		हाल 2:
			म_लिखो("JIT compiler is enabled with debugging traces in kernel logs\n");
			अवरोध;
		हाल -1:
			म_लिखो("Unable to retrieve JIT-compiler status\n");
			अवरोध;
		शेष:
			म_लिखो("JIT-compiler status has unknown value %d\n",
			       res);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम probe_jit_harden(व्योम)
अणु
	पूर्णांक res;

	/* No support क्रम C-style ouptut */

	res = पढ़ो_procfs("/proc/sys/net/core/bpf_jit_harden");
	अगर (json_output) अणु
		jsonw_पूर्णांक_field(json_wtr, "bpf_jit_harden", res);
	पूर्ण अन्यथा अणु
		चयन (res) अणु
		हाल 0:
			म_लिखो("JIT compiler hardening is disabled\n");
			अवरोध;
		हाल 1:
			म_लिखो("JIT compiler hardening is enabled for unprivileged users\n");
			अवरोध;
		हाल 2:
			म_लिखो("JIT compiler hardening is enabled for all users\n");
			अवरोध;
		हाल -1:
			म_लिखो("Unable to retrieve JIT hardening status\n");
			अवरोध;
		शेष:
			म_लिखो("JIT hardening status has unknown value %d\n",
			       res);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम probe_jit_kallsyms(व्योम)
अणु
	पूर्णांक res;

	/* No support क्रम C-style ouptut */

	res = पढ़ो_procfs("/proc/sys/net/core/bpf_jit_kallsyms");
	अगर (json_output) अणु
		jsonw_पूर्णांक_field(json_wtr, "bpf_jit_kallsyms", res);
	पूर्ण अन्यथा अणु
		चयन (res) अणु
		हाल 0:
			म_लिखो("JIT compiler kallsyms exports are disabled\n");
			अवरोध;
		हाल 1:
			म_लिखो("JIT compiler kallsyms exports are enabled for root\n");
			अवरोध;
		हाल -1:
			म_लिखो("Unable to retrieve JIT kallsyms export status\n");
			अवरोध;
		शेष:
			म_लिखो("JIT kallsyms exports status has unknown value %d\n", res);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम probe_jit_limit(व्योम)
अणु
	पूर्णांक res;

	/* No support क्रम C-style ouptut */

	res = पढ़ो_procfs("/proc/sys/net/core/bpf_jit_limit");
	अगर (json_output) अणु
		jsonw_पूर्णांक_field(json_wtr, "bpf_jit_limit", res);
	पूर्ण अन्यथा अणु
		चयन (res) अणु
		हाल -1:
			म_लिखो("Unable to retrieve global memory limit for JIT compiler for unprivileged users\n");
			अवरोध;
		शेष:
			म_लिखो("Global memory limit for JIT compiler for unprivileged users is %d bytes\n", res);
		पूर्ण
	पूर्ण
पूर्ण

अटल bool पढ़ो_next_kernel_config_option(gzFile file, अक्षर *buf, माप_प्रकार n,
					   अक्षर **value)
अणु
	अक्षर *sep;

	जबतक (gzमाला_लो(file, buf, n)) अणु
		अगर (म_भेदन(buf, "CONFIG_", 7))
			जारी;

		sep = म_अक्षर(buf, '=');
		अगर (!sep)
			जारी;

		/* Trim ending '\n' */
		buf[म_माप(buf) - 1] = '\0';

		/* Split on '=' and ensure that a value is present. */
		*sep = '\0';
		अगर (!sep[1])
			जारी;

		*value = sep + 1;
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम probe_kernel_image_config(स्थिर अक्षर *define_prefix)
अणु
	अटल स्थिर काष्ठा अणु
		स्थिर अक्षर * स्थिर name;
		bool macro_dump;
	पूर्ण options[] = अणु
		/* Enable BPF */
		अणु "CONFIG_BPF", पूर्ण,
		/* Enable bpf() syscall */
		अणु "CONFIG_BPF_SYSCALL", पूर्ण,
		/* Does selected architecture support eBPF JIT compiler */
		अणु "CONFIG_HAVE_EBPF_JIT", पूर्ण,
		/* Compile eBPF JIT compiler */
		अणु "CONFIG_BPF_JIT", पूर्ण,
		/* Aव्योम compiling eBPF पूर्णांकerpreter (use JIT only) */
		अणु "CONFIG_BPF_JIT_ALWAYS_ON", पूर्ण,
		/* Kernel BTF debug inक्रमmation available */
		अणु "CONFIG_DEBUG_INFO_BTF", पूर्ण,
		/* Kernel module BTF debug inक्रमmation available */
		अणु "CONFIG_DEBUG_INFO_BTF_MODULES", पूर्ण,

		/* cgroups */
		अणु "CONFIG_CGROUPS", पूर्ण,
		/* BPF programs attached to cgroups */
		अणु "CONFIG_CGROUP_BPF", पूर्ण,
		/* bpf_get_cgroup_classid() helper */
		अणु "CONFIG_CGROUP_NET_CLASSID", पूर्ण,
		/* bpf_skb_अणु,ancestor_पूर्णcgroup_id() helpers */
		अणु "CONFIG_SOCK_CGROUP_DATA", पूर्ण,

		/* Tracing: attach BPF to kprobes, tracepoपूर्णांकs, etc. */
		अणु "CONFIG_BPF_EVENTS", पूर्ण,
		/* Kprobes */
		अणु "CONFIG_KPROBE_EVENTS", पूर्ण,
		/* Uprobes */
		अणु "CONFIG_UPROBE_EVENTS", पूर्ण,
		/* Tracepoपूर्णांकs */
		अणु "CONFIG_TRACING", पूर्ण,
		/* Syscall tracepoपूर्णांकs */
		अणु "CONFIG_FTRACE_SYSCALLS", पूर्ण,
		/* bpf_override_वापस() helper support क्रम selected arch */
		अणु "CONFIG_FUNCTION_ERROR_INJECTION", पूर्ण,
		/* bpf_override_वापस() helper */
		अणु "CONFIG_BPF_KPROBE_OVERRIDE", पूर्ण,

		/* Network */
		अणु "CONFIG_NET", पूर्ण,
		/* AF_XDP sockets */
		अणु "CONFIG_XDP_SOCKETS", पूर्ण,
		/* BPF_PROG_TYPE_LWT_* and related helpers */
		अणु "CONFIG_LWTUNNEL_BPF", पूर्ण,
		/* BPF_PROG_TYPE_SCHED_ACT, TC (traffic control) actions */
		अणु "CONFIG_NET_ACT_BPF", पूर्ण,
		/* BPF_PROG_TYPE_SCHED_CLS, TC filters */
		अणु "CONFIG_NET_CLS_BPF", पूर्ण,
		/* TC clsact qdisc */
		अणु "CONFIG_NET_CLS_ACT", पूर्ण,
		/* Ingress filtering with TC */
		अणु "CONFIG_NET_SCH_INGRESS", पूर्ण,
		/* bpf_skb_get_xfrm_state() helper */
		अणु "CONFIG_XFRM", पूर्ण,
		/* bpf_get_route_realm() helper */
		अणु "CONFIG_IP_ROUTE_CLASSID", पूर्ण,
		/* BPF_PROG_TYPE_LWT_SEG6_LOCAL and related helpers */
		अणु "CONFIG_IPV6_SEG6_BPF", पूर्ण,
		/* BPF_PROG_TYPE_LIRC_MODE2 and related helpers */
		अणु "CONFIG_BPF_LIRC_MODE2", पूर्ण,
		/* BPF stream parser and BPF socket maps */
		अणु "CONFIG_BPF_STREAM_PARSER", पूर्ण,
		/* xt_bpf module क्रम passing BPF programs to netfilter  */
		अणु "CONFIG_NETFILTER_XT_MATCH_BPF", पूर्ण,
		/* bpfilter back-end क्रम iptables */
		अणु "CONFIG_BPFILTER", पूर्ण,
		/* bpftilter module with "user mode helper" */
		अणु "CONFIG_BPFILTER_UMH", पूर्ण,

		/* test_bpf module क्रम BPF tests */
		अणु "CONFIG_TEST_BPF", पूर्ण,

		/* Misc configs useful in BPF C programs */
		/* jअगरfies <-> sec conversion क्रम bpf_jअगरfies64() helper */
		अणु "CONFIG_HZ", true, पूर्ण
	पूर्ण;
	अक्षर *values[ARRAY_SIZE(options)] = अणु पूर्ण;
	काष्ठा utsname utsn;
	अक्षर path[PATH_MAX];
	gzFile file = शून्य;
	अक्षर buf[4096];
	अक्षर *value;
	माप_प्रकार i;

	अगर (!uname(&utsn)) अणु
		snम_लिखो(path, माप(path), "/boot/config-%s", utsn.release);

		/* gzखोलो also accepts uncompressed files. */
		file = gzखोलो(path, "r");
	पूर्ण

	अगर (!file) अणु
		/* Some distributions build with CONFIG_IKCONFIG=y and put the
		 * config file at /proc/config.gz.
		 */
		file = gzखोलो("/proc/config.gz", "r");
	पूर्ण
	अगर (!file) अणु
		p_info("skipping kernel config, can't open file: %s",
		       म_त्रुटि(त्रुटि_सं));
		जाओ end_parse;
	पूर्ण
	/* Sanity checks */
	अगर (!gzमाला_लो(file, buf, माप(buf)) ||
	    !gzमाला_लो(file, buf, माप(buf))) अणु
		p_info("skipping kernel config, can't read from file: %s",
		       म_त्रुटि(त्रुटि_सं));
		जाओ end_parse;
	पूर्ण
	अगर (म_भेद(buf, "# Automatically generated file; DO NOT EDIT.\n")) अणु
		p_info("skipping kernel config, can't find correct file");
		जाओ end_parse;
	पूर्ण

	जबतक (पढ़ो_next_kernel_config_option(file, buf, माप(buf), &value)) अणु
		क्रम (i = 0; i < ARRAY_SIZE(options); i++) अणु
			अगर ((define_prefix && !options[i].macro_dump) ||
			    values[i] || म_भेद(buf, options[i].name))
				जारी;

			values[i] = strdup(value);
		पूर्ण
	पूर्ण

end_parse:
	अगर (file)
		gzबंद(file);

	क्रम (i = 0; i < ARRAY_SIZE(options); i++) अणु
		अगर (define_prefix && !options[i].macro_dump)
			जारी;
		prपूर्णांक_kernel_option(options[i].name, values[i], define_prefix);
		मुक्त(values[i]);
	पूर्ण
पूर्ण

अटल bool probe_bpf_syscall(स्थिर अक्षर *define_prefix)
अणु
	bool res;

	bpf_load_program(BPF_PROG_TYPE_UNSPEC, शून्य, 0, शून्य, 0, शून्य, 0);
	res = (त्रुटि_सं != ENOSYS);

	prपूर्णांक_bool_feature("have_bpf_syscall",
			   "bpf() syscall",
			   "BPF_SYSCALL",
			   res, define_prefix);

	वापस res;
पूर्ण

अटल व्योम
probe_prog_type(क्रमागत bpf_prog_type prog_type, bool *supported_types,
		स्थिर अक्षर *define_prefix, __u32 अगरindex)
अणु
	अक्षर feat_name[128], plain_desc[128], define_name[128];
	स्थिर अक्षर *plain_comment = "eBPF program_type ";
	माप_प्रकार maxlen;
	bool res;

	अगर (अगरindex)
		/* Only test offload-able program types */
		चयन (prog_type) अणु
		हाल BPF_PROG_TYPE_SCHED_CLS:
		हाल BPF_PROG_TYPE_XDP:
			अवरोध;
		शेष:
			वापस;
		पूर्ण

	res = bpf_probe_prog_type(prog_type, अगरindex);
#अगर_घोषित USE_LIBCAP
	/* Probe may succeed even अगर program load fails, क्रम unprivileged users
	 * check that we did not fail because of insufficient permissions
	 */
	अगर (run_as_unprivileged && त्रुटि_सं == EPERM)
		res = false;
#पूर्ण_अगर

	supported_types[prog_type] |= res;

	अगर (!prog_type_name[prog_type]) अणु
		p_info("program type name not found (type %d)", prog_type);
		वापस;
	पूर्ण
	maxlen = माप(plain_desc) - म_माप(plain_comment) - 1;
	अगर (म_माप(prog_type_name[prog_type]) > maxlen) अणु
		p_info("program type name too long");
		वापस;
	पूर्ण

	प्र_लिखो(feat_name, "have_%s_prog_type", prog_type_name[prog_type]);
	प्र_लिखो(define_name, "%s_prog_type", prog_type_name[prog_type]);
	upperहाल(define_name, माप(define_name));
	प्र_लिखो(plain_desc, "%s%s", plain_comment, prog_type_name[prog_type]);
	prपूर्णांक_bool_feature(feat_name, plain_desc, define_name, res,
			   define_prefix);
पूर्ण

अटल व्योम
probe_map_type(क्रमागत bpf_map_type map_type, स्थिर अक्षर *define_prefix,
	       __u32 अगरindex)
अणु
	अक्षर feat_name[128], plain_desc[128], define_name[128];
	स्थिर अक्षर *plain_comment = "eBPF map_type ";
	माप_प्रकार maxlen;
	bool res;

	res = bpf_probe_map_type(map_type, अगरindex);

	/* Probe result depends on the success of map creation, no additional
	 * check required क्रम unprivileged users
	 */

	अगर (!map_type_name[map_type]) अणु
		p_info("map type name not found (type %d)", map_type);
		वापस;
	पूर्ण
	maxlen = माप(plain_desc) - म_माप(plain_comment) - 1;
	अगर (म_माप(map_type_name[map_type]) > maxlen) अणु
		p_info("map type name too long");
		वापस;
	पूर्ण

	प्र_लिखो(feat_name, "have_%s_map_type", map_type_name[map_type]);
	प्र_लिखो(define_name, "%s_map_type", map_type_name[map_type]);
	upperहाल(define_name, माप(define_name));
	प्र_लिखो(plain_desc, "%s%s", plain_comment, map_type_name[map_type]);
	prपूर्णांक_bool_feature(feat_name, plain_desc, define_name, res,
			   define_prefix);
पूर्ण

अटल व्योम
probe_helper_क्रम_progtype(क्रमागत bpf_prog_type prog_type, bool supported_type,
			  स्थिर अक्षर *define_prefix, अचिन्हित पूर्णांक id,
			  स्थिर अक्षर *ptype_name, __u32 अगरindex)
अणु
	bool res = false;

	अगर (supported_type) अणु
		res = bpf_probe_helper(id, prog_type, अगरindex);
#अगर_घोषित USE_LIBCAP
		/* Probe may succeed even अगर program load fails, क्रम
		 * unprivileged users check that we did not fail because of
		 * insufficient permissions
		 */
		अगर (run_as_unprivileged && त्रुटि_सं == EPERM)
			res = false;
#पूर्ण_अगर
	पूर्ण

	अगर (json_output) अणु
		अगर (res)
			jsonw_string(json_wtr, helper_name[id]);
	पूर्ण अन्यथा अगर (define_prefix) अणु
		म_लिखो("#define %sBPF__PROG_TYPE_%s__HELPER_%s %s\n",
		       define_prefix, ptype_name, helper_name[id],
		       res ? "1" : "0");
	पूर्ण अन्यथा अणु
		अगर (res)
			म_लिखो("\n\t- %s", helper_name[id]);
	पूर्ण
पूर्ण

अटल व्योम
probe_helpers_क्रम_progtype(क्रमागत bpf_prog_type prog_type, bool supported_type,
			   स्थिर अक्षर *define_prefix, __u32 अगरindex)
अणु
	स्थिर अक्षर *ptype_name = prog_type_name[prog_type];
	अक्षर feat_name[128];
	अचिन्हित पूर्णांक id;

	अगर (अगरindex)
		/* Only test helpers क्रम offload-able program types */
		चयन (prog_type) अणु
		हाल BPF_PROG_TYPE_SCHED_CLS:
		हाल BPF_PROG_TYPE_XDP:
			अवरोध;
		शेष:
			वापस;
		पूर्ण

	अगर (json_output) अणु
		प्र_लिखो(feat_name, "%s_available_helpers", ptype_name);
		jsonw_name(json_wtr, feat_name);
		jsonw_start_array(json_wtr);
	पूर्ण अन्यथा अगर (!define_prefix) अणु
		म_लिखो("eBPF helpers supported for program type %s:",
		       ptype_name);
	पूर्ण

	क्रम (id = 1; id < ARRAY_SIZE(helper_name); id++) अणु
		/* Skip helper functions which emit dmesg messages when not in
		 * the full mode.
		 */
		चयन (id) अणु
		हाल BPF_FUNC_trace_prपूर्णांकk:
		हाल BPF_FUNC_probe_ग_लिखो_user:
			अगर (!full_mode)
				जारी;
			/* fallthrough */
		शेष:
			probe_helper_क्रम_progtype(prog_type, supported_type,
						  define_prefix, id, ptype_name,
						  अगरindex);
		पूर्ण
	पूर्ण

	अगर (json_output)
		jsonw_end_array(json_wtr);
	अन्यथा अगर (!define_prefix)
		म_लिखो("\n");
पूर्ण

अटल व्योम
probe_large_insn_limit(स्थिर अक्षर *define_prefix, __u32 अगरindex)
अणु
	bool res;

	res = bpf_probe_large_insn_limit(अगरindex);
	prपूर्णांक_bool_feature("have_large_insn_limit",
			   "Large program size limit",
			   "LARGE_INSN_LIMIT",
			   res, define_prefix);
पूर्ण

अटल व्योम
section_प्रणाली_config(क्रमागत probe_component target, स्थिर अक्षर *define_prefix)
अणु
	चयन (target) अणु
	हाल COMPONENT_KERNEL:
	हाल COMPONENT_UNSPEC:
		prपूर्णांक_start_section("system_config",
				    "Scanning system configuration...",
				    "/*** Misc kernel config items ***/",
				    define_prefix);
		अगर (!define_prefix) अणु
			अगर (check_procfs()) अणु
				probe_unprivileged_disabled();
				probe_jit_enable();
				probe_jit_harden();
				probe_jit_kallsyms();
				probe_jit_limit();
			पूर्ण अन्यथा अणु
				p_info("/* procfs not mounted, skipping related probes */");
			पूर्ण
		पूर्ण
		probe_kernel_image_config(define_prefix);
		prपूर्णांक_end_section();
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल bool section_syscall_config(स्थिर अक्षर *define_prefix)
अणु
	bool res;

	prपूर्णांक_start_section("syscall_config",
			    "Scanning system call availability...",
			    "/*** System call availability ***/",
			    define_prefix);
	res = probe_bpf_syscall(define_prefix);
	prपूर्णांक_end_section();

	वापस res;
पूर्ण

अटल व्योम
section_program_types(bool *supported_types, स्थिर अक्षर *define_prefix,
		      __u32 अगरindex)
अणु
	अचिन्हित पूर्णांक i;

	prपूर्णांक_start_section("program_types",
			    "Scanning eBPF program types...",
			    "/*** eBPF program types ***/",
			    define_prefix);

	क्रम (i = BPF_PROG_TYPE_UNSPEC + 1; i < prog_type_name_size; i++)
		probe_prog_type(i, supported_types, define_prefix, अगरindex);

	prपूर्णांक_end_section();
पूर्ण

अटल व्योम section_map_types(स्थिर अक्षर *define_prefix, __u32 अगरindex)
अणु
	अचिन्हित पूर्णांक i;

	prपूर्णांक_start_section("map_types",
			    "Scanning eBPF map types...",
			    "/*** eBPF map types ***/",
			    define_prefix);

	क्रम (i = BPF_MAP_TYPE_UNSPEC + 1; i < map_type_name_size; i++)
		probe_map_type(i, define_prefix, अगरindex);

	prपूर्णांक_end_section();
पूर्ण

अटल व्योम
section_helpers(bool *supported_types, स्थिर अक्षर *define_prefix, __u32 अगरindex)
अणु
	अचिन्हित पूर्णांक i;

	prपूर्णांक_start_section("helpers",
			    "Scanning eBPF helper functions...",
			    "/*** eBPF helper functions ***/",
			    define_prefix);

	अगर (define_prefix)
		म_लिखो("/*\n"
		       " * Use %sHAVE_PROG_TYPE_HELPER(prog_type_name, helper_name)\n"
		       " * to determine if <helper_name> is available for <prog_type_name>,\n"
		       " * e.g.\n"
		       " *	#if %sHAVE_PROG_TYPE_HELPER(xdp, bpf_redirect)\n"
		       " *		// do stuff with this helper\n"
		       " *	#elif\n"
		       " *		// use a workaround\n"
		       " *	#endif\n"
		       " */\n"
		       "#define %sHAVE_PROG_TYPE_HELPER(prog_type, helper)	\\\n"
		       "	%sBPF__PROG_TYPE_ ## prog_type ## __HELPER_ ## helper\n",
		       define_prefix, define_prefix, define_prefix,
		       define_prefix);
	क्रम (i = BPF_PROG_TYPE_UNSPEC + 1; i < prog_type_name_size; i++)
		probe_helpers_क्रम_progtype(i, supported_types[i], define_prefix,
					   अगरindex);

	prपूर्णांक_end_section();
पूर्ण

अटल व्योम section_misc(स्थिर अक्षर *define_prefix, __u32 अगरindex)
अणु
	prपूर्णांक_start_section("misc",
			    "Scanning miscellaneous eBPF features...",
			    "/*** eBPF misc features ***/",
			    define_prefix);
	probe_large_insn_limit(define_prefix, अगरindex);
	prपूर्णांक_end_section();
पूर्ण

#अगर_घोषित USE_LIBCAP
#घोषणा capability(c) अणु c, false, #c पूर्ण
#घोषणा capability_msg(a, i) a[i].set ? "" : a[i].name, a[i].set ? "" : ", "
#पूर्ण_अगर

अटल पूर्णांक handle_perms(व्योम)
अणु
#अगर_घोषित USE_LIBCAP
	काष्ठा अणु
		cap_value_t cap;
		bool set;
		अक्षर name[14];	/* म_माप("CAP_SYS_ADMIN") */
	पूर्ण bpf_caps[] = अणु
		capability(CAP_SYS_ADMIN),
#अगर_घोषित CAP_BPF
		capability(CAP_BPF),
		capability(CAP_NET_ADMIN),
		capability(CAP_PERFMON),
#पूर्ण_अगर
	पूर्ण;
	cap_value_t cap_list[ARRAY_SIZE(bpf_caps)];
	अचिन्हित पूर्णांक i, nb_bpf_caps = 0;
	bool cap_sys_admin_only = true;
	cap_flag_value_t val;
	पूर्णांक res = -1;
	cap_t caps;

	caps = cap_get_proc();
	अगर (!caps) अणु
		p_err("failed to get capabilities for process: %s",
		      म_त्रुटि(त्रुटि_सं));
		वापस -1;
	पूर्ण

#अगर_घोषित CAP_BPF
	अगर (CAP_IS_SUPPORTED(CAP_BPF))
		cap_sys_admin_only = false;
#पूर्ण_अगर

	क्रम (i = 0; i < ARRAY_SIZE(bpf_caps); i++) अणु
		स्थिर अक्षर *cap_name = bpf_caps[i].name;
		cap_value_t cap = bpf_caps[i].cap;

		अगर (cap_get_flag(caps, cap, CAP_EFFECTIVE, &val)) अणु
			p_err("bug: failed to retrieve %s status: %s", cap_name,
			      म_त्रुटि(त्रुटि_सं));
			जाओ निकास_मुक्त;
		पूर्ण

		अगर (val == CAP_SET) अणु
			bpf_caps[i].set = true;
			cap_list[nb_bpf_caps++] = cap;
		पूर्ण

		अगर (cap_sys_admin_only)
			/* System करोes not know about CAP_BPF, meaning that
			 * CAP_SYS_ADMIN is the only capability required. We
			 * just checked it, अवरोध.
			 */
			अवरोध;
	पूर्ण

	अगर ((run_as_unprivileged && !nb_bpf_caps) ||
	    (!run_as_unprivileged && nb_bpf_caps == ARRAY_SIZE(bpf_caps)) ||
	    (!run_as_unprivileged && cap_sys_admin_only && nb_bpf_caps)) अणु
		/* We are all good, निकास now */
		res = 0;
		जाओ निकास_मुक्त;
	पूर्ण

	अगर (!run_as_unprivileged) अणु
		अगर (cap_sys_admin_only)
			p_err("missing %s, required for full feature probing; run as root or use 'unprivileged'",
			      bpf_caps[0].name);
		अन्यथा
			p_err("missing %s%s%s%s%s%s%s%srequired for full feature probing; run as root or use 'unprivileged'",
			      capability_msg(bpf_caps, 0),
#अगर_घोषित CAP_BPF
			      capability_msg(bpf_caps, 1),
			      capability_msg(bpf_caps, 2),
			      capability_msg(bpf_caps, 3)
#अन्यथा
				"", "", "", "", "", ""
#पूर्ण_अगर /* CAP_BPF */
				);
		जाओ निकास_मुक्त;
	पूर्ण

	/* अगर (run_as_unprivileged && nb_bpf_caps > 0), drop capabilities. */
	अगर (cap_set_flag(caps, CAP_EFFECTIVE, nb_bpf_caps, cap_list,
			 CAP_CLEAR)) अणु
		p_err("bug: failed to clear capabilities: %s", म_त्रुटि(त्रुटि_सं));
		जाओ निकास_मुक्त;
	पूर्ण

	अगर (cap_set_proc(caps)) अणु
		p_err("failed to drop capabilities: %s", म_त्रुटि(त्रुटि_सं));
		जाओ निकास_मुक्त;
	पूर्ण

	res = 0;

निकास_मुक्त:
	अगर (cap_मुक्त(caps) && !res) अणु
		p_err("failed to clear storage object for capabilities: %s",
		      म_त्रुटि(त्रुटि_सं));
		res = -1;
	पूर्ण

	वापस res;
#अन्यथा
	/* Detection assumes user has specअगरic privileges.
	 * We करो not use libpcap so let's approximate, and restrict usage to
	 * root user only.
	 */
	अगर (geteuid()) अणु
		p_err("full feature probing requires root privileges");
		वापस -1;
	पूर्ण

	वापस 0;
#पूर्ण_अगर /* USE_LIBCAP */
पूर्ण

अटल पूर्णांक करो_probe(पूर्णांक argc, अक्षर **argv)
अणु
	क्रमागत probe_component target = COMPONENT_UNSPEC;
	स्थिर अक्षर *define_prefix = शून्य;
	bool supported_types[128] = अणुपूर्ण;
	__u32 अगरindex = 0;
	अक्षर *अगरname;

	set_max_rlimit();

	जबतक (argc) अणु
		अगर (is_prefix(*argv, "kernel")) अणु
			अगर (target != COMPONENT_UNSPEC) अणु
				p_err("component to probe already specified");
				वापस -1;
			पूर्ण
			target = COMPONENT_KERNEL;
			NEXT_ARG();
		पूर्ण अन्यथा अगर (is_prefix(*argv, "dev")) अणु
			NEXT_ARG();

			अगर (target != COMPONENT_UNSPEC || अगरindex) अणु
				p_err("component to probe already specified");
				वापस -1;
			पूर्ण
			अगर (!REQ_ARGS(1))
				वापस -1;

			target = COMPONENT_DEVICE;
			अगरname = GET_ARG();
			अगरindex = अगर_nametoindex(अगरname);
			अगर (!अगरindex) अणु
				p_err("unrecognized netdevice '%s': %s", अगरname,
				      म_त्रुटि(त्रुटि_सं));
				वापस -1;
			पूर्ण
		पूर्ण अन्यथा अगर (is_prefix(*argv, "full")) अणु
			full_mode = true;
			NEXT_ARG();
		पूर्ण अन्यथा अगर (is_prefix(*argv, "macros") && !define_prefix) अणु
			define_prefix = "";
			NEXT_ARG();
		पूर्ण अन्यथा अगर (is_prefix(*argv, "prefix")) अणु
			अगर (!define_prefix) अणु
				p_err("'prefix' argument can only be use after 'macros'");
				वापस -1;
			पूर्ण
			अगर (म_भेद(define_prefix, "")) अणु
				p_err("'prefix' already defined");
				वापस -1;
			पूर्ण
			NEXT_ARG();

			अगर (!REQ_ARGS(1))
				वापस -1;
			define_prefix = GET_ARG();
		पूर्ण अन्यथा अगर (is_prefix(*argv, "unprivileged")) अणु
#अगर_घोषित USE_LIBCAP
			run_as_unprivileged = true;
			NEXT_ARG();
#अन्यथा
			p_err("unprivileged run not supported, recompile bpftool with libcap");
			वापस -1;
#पूर्ण_अगर
		पूर्ण अन्यथा अणु
			p_err("expected no more arguments, 'kernel', 'dev', 'macros' or 'prefix', got: '%s'?",
			      *argv);
			वापस -1;
		पूर्ण
	पूर्ण

	/* Full feature detection requires specअगरic privileges.
	 * Let's approximate, and warn अगर user is not root.
	 */
	अगर (handle_perms())
		वापस -1;

	अगर (json_output) अणु
		define_prefix = शून्य;
		jsonw_start_object(json_wtr);
	पूर्ण

	section_प्रणाली_config(target, define_prefix);
	अगर (!section_syscall_config(define_prefix))
		/* bpf() syscall unavailable, करोn't probe other BPF features */
		जाओ निकास_बंद_json;
	section_program_types(supported_types, define_prefix, अगरindex);
	section_map_types(define_prefix, अगरindex);
	section_helpers(supported_types, define_prefix, अगरindex);
	section_misc(define_prefix, अगरindex);

निकास_बंद_json:
	अगर (json_output)
		/* End root object */
		jsonw_end_object(json_wtr);

	वापस 0;
पूर्ण

अटल पूर्णांक करो_help(पूर्णांक argc, अक्षर **argv)
अणु
	अगर (json_output) अणु
		jsonw_null(json_wtr);
		वापस 0;
	पूर्ण

	ख_लिखो(मानक_त्रुटि,
		"Usage: %1$s %2$s probe [COMPONENT] [full] [unprivileged] [macros [prefix PREFIX]]\n"
		"       %1$s %2$s help\n"
		"\n"
		"       COMPONENT := { kernel | dev NAME }\n"
		"",
		bin_name, argv[-2]);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा cmd cmds[] = अणु
	अणु "probe",	करो_probe पूर्ण,
	अणु "help",	करो_help पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

पूर्णांक करो_feature(पूर्णांक argc, अक्षर **argv)
अणु
	वापस cmd_select(cmds, argc, argv, करो_help);
पूर्ण
