<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/init/मुख्य.c
 *
 *  Copyright (C) 1991, 1992  Linus Torvalds
 *
 *  GK 2/5/95  -  Changed to support mounting root fs via NFS
 *  Added initrd & change_root: Werner Almesberger & Hans Lermen, Feb '96
 *  Moan early अगर gcc is old, aव्योमing bogus kernels - Paul Gorपंचांगaker, May '96
 *  Simplअगरied starting of init:  Michael A. Grअगरfith <grअगर@acm.org>
 */

#घोषणा DEBUG		/* Enable initcall_debug */

#समावेश <linux/types.h>
#समावेश <linux/extable.h>
#समावेश <linux/module.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/binfmts.h>
#समावेश <linux/kernel.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/stackprotector.h>
#समावेश <linux/माला.स>
#समावेश <linux/प्रकार.स>
#समावेश <linux/delay.h>
#समावेश <linux/ioport.h>
#समावेश <linux/init.h>
#समावेश <linux/initrd.h>
#समावेश <linux/memblock.h>
#समावेश <linux/acpi.h>
#समावेश <linux/bootconfig.h>
#समावेश <linux/console.h>
#समावेश <linux/nmi.h>
#समावेश <linux/percpu.h>
#समावेश <linux/kmod.h>
#समावेश <linux/kprobes.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/start_kernel.h>
#समावेश <linux/security.h>
#समावेश <linux/smp.h>
#समावेश <linux/profile.h>
#समावेश <linux/kfence.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/kallsyms.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/cpu.h>
#समावेश <linux/cpuset.h>
#समावेश <linux/cgroup.h>
#समावेश <linux/efi.h>
#समावेश <linux/tick.h>
#समावेश <linux/sched/isolation.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/taskstats_kern.h>
#समावेश <linux/delayacct.h>
#समावेश <linux/unistd.h>
#समावेश <linux/utsname.h>
#समावेश <linux/rmap.h>
#समावेश <linux/mempolicy.h>
#समावेश <linux/key.h>
#समावेश <linux/page_ext.h>
#समावेश <linux/debug_locks.h>
#समावेश <linux/debugobjects.h>
#समावेश <linux/lockdep.h>
#समावेश <linux/kmemleak.h>
#समावेश <linux/padata.h>
#समावेश <linux/pid_namespace.h>
#समावेश <linux/device/driver.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/init.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/idr.h>
#समावेश <linux/kgdb.h>
#समावेश <linux/ftrace.h>
#समावेश <linux/async.h>
#समावेश <linux/shmem_fs.h>
#समावेश <linux/slab.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/pti.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/elevator.h>
#समावेश <linux/sched/घड़ी.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/context_tracking.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/list.h>
#समावेश <linux/पूर्णांकegrity.h>
#समावेश <linux/proc_ns.h>
#समावेश <linux/पन.स>
#समावेश <linux/cache.h>
#समावेश <linux/rodata_test.h>
#समावेश <linux/jump_label.h>
#समावेश <linux/mem_encrypt.h>
#समावेश <linux/kcsan.h>
#समावेश <linux/init_syscalls.h>
#समावेश <linux/stackdepot.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/bugs.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/cacheflush.h>

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/initcall.h>

#समावेश <kunit/test.h>

अटल पूर्णांक kernel_init(व्योम *);

बाह्य व्योम init_IRQ(व्योम);
बाह्य व्योम radix_tree_init(व्योम);

/*
 * Debug helper: via this flag we know that we are in 'early bootup code'
 * where only the boot processor is running with IRQ disabled.  This means
 * two things - IRQ must not be enabled beक्रमe the flag is cleared and some
 * operations which are not allowed with IRQ disabled are allowed जबतक the
 * flag is set.
 */
bool early_boot_irqs_disabled __पढ़ो_mostly;

क्रमागत प्रणाली_states प्रणाली_state __पढ़ो_mostly;
EXPORT_SYMBOL(प्रणाली_state);

/*
 * Boot command-line arguments
 */
#घोषणा MAX_INIT_ARGS CONFIG_INIT_ENV_ARG_LIMIT
#घोषणा MAX_INIT_ENVS CONFIG_INIT_ENV_ARG_LIMIT

बाह्य व्योम समय_init(व्योम);
/* Default late समय init is शून्य. archs can override this later. */
व्योम (*__initdata late_समय_init)(व्योम);

/* Untouched command line saved by arch-specअगरic code. */
अक्षर __initdata boot_command_line[COMMAND_LINE_SIZE];
/* Untouched saved command line (eg. क्रम /proc) */
अक्षर *saved_command_line;
/* Command line क्रम parameter parsing */
अटल अक्षर *अटल_command_line;
/* Untouched extra command line */
अटल अक्षर *extra_command_line;
/* Extra init arguments */
अटल अक्षर *extra_init_args;

#अगर_घोषित CONFIG_BOOT_CONFIG
/* Is bootconfig on command line? */
अटल bool bootconfig_found;
अटल bool initargs_found;
#अन्यथा
# define bootconfig_found false
# define initargs_found false
#पूर्ण_अगर

अटल अक्षर *execute_command;
अटल अक्षर *ramdisk_execute_command = "/init";

/*
 * Used to generate warnings अगर अटल_key manipulation functions are used
 * beक्रमe jump_label_init is called.
 */
bool अटल_key_initialized __पढ़ो_mostly;
EXPORT_SYMBOL_GPL(अटल_key_initialized);

/*
 * If set, this is an indication to the drivers that reset the underlying
 * device beक्रमe going ahead with the initialization otherwise driver might
 * rely on the BIOS and skip the reset operation.
 *
 * This is useful अगर kernel is booting in an unreliable environment.
 * For ex. kdump situation where previous kernel has crashed, BIOS has been
 * skipped and devices will be in unknown state.
 */
अचिन्हित पूर्णांक reset_devices;
EXPORT_SYMBOL(reset_devices);

अटल पूर्णांक __init set_reset_devices(अक्षर *str)
अणु
	reset_devices = 1;
	वापस 1;
पूर्ण

__setup("reset_devices", set_reset_devices);

अटल स्थिर अक्षर *argv_init[MAX_INIT_ARGS+2] = अणु "init", शून्य, पूर्ण;
स्थिर अक्षर *envp_init[MAX_INIT_ENVS+2] = अणु "HOME=/", "TERM=linux", शून्य, पूर्ण;
अटल स्थिर अक्षर *panic_later, *panic_param;

बाह्य स्थिर काष्ठा obs_kernel_param __setup_start[], __setup_end[];

अटल bool __init obsolete_checksetup(अक्षर *line)
अणु
	स्थिर काष्ठा obs_kernel_param *p;
	bool had_early_param = false;

	p = __setup_start;
	करो अणु
		पूर्णांक n = म_माप(p->str);
		अगर (parameqn(line, p->str, n)) अणु
			अगर (p->early) अणु
				/* Alपढ़ोy करोne in parse_early_param?
				 * (Needs exact match on param part).
				 * Keep iterating, as we can have early
				 * params and __setups of same names 8( */
				अगर (line[n] == '\0' || line[n] == '=')
					had_early_param = true;
			पूर्ण अन्यथा अगर (!p->setup_func) अणु
				pr_warn("Parameter %s is obsolete, ignored\n",
					p->str);
				वापस true;
			पूर्ण अन्यथा अगर (p->setup_func(line + n))
				वापस true;
		पूर्ण
		p++;
	पूर्ण जबतक (p < __setup_end);

	वापस had_early_param;
पूर्ण

/*
 * This should be approx 2 Bo*oMips to start (note initial shअगरt), and will
 * still work even अगर initially too large, it will just take slightly दीर्घer
 */
अचिन्हित दीर्घ loops_per_jअगरfy = (1<<12);
EXPORT_SYMBOL(loops_per_jअगरfy);

अटल पूर्णांक __init debug_kernel(अक्षर *str)
अणु
	console_loglevel = CONSOLE_LOGLEVEL_DEBUG;
	वापस 0;
पूर्ण

अटल पूर्णांक __init quiet_kernel(अक्षर *str)
अणु
	console_loglevel = CONSOLE_LOGLEVEL_QUIET;
	वापस 0;
पूर्ण

early_param("debug", debug_kernel);
early_param("quiet", quiet_kernel);

अटल पूर्णांक __init loglevel(अक्षर *str)
अणु
	पूर्णांक newlevel;

	/*
	 * Only update loglevel value when a correct setting was passed,
	 * to prevent blind crashes (when loglevel being set to 0) that
	 * are quite hard to debug
	 */
	अगर (get_option(&str, &newlevel)) अणु
		console_loglevel = newlevel;
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

early_param("loglevel", loglevel);

#अगर_घोषित CONFIG_BLK_DEV_INITRD
अटल व्योम * __init get_boot_config_from_initrd(u32 *_size, u32 *_csum)
अणु
	u32 size, csum;
	अक्षर *data;
	u32 *hdr;
	पूर्णांक i;

	अगर (!initrd_end)
		वापस शून्य;

	data = (अक्षर *)initrd_end - BOOTCONFIG_MAGIC_LEN;
	/*
	 * Since Grub may align the size of initrd to 4, we must
	 * check the preceding 3 bytes as well.
	 */
	क्रम (i = 0; i < 4; i++) अणु
		अगर (!स_भेद(data, BOOTCONFIG_MAGIC, BOOTCONFIG_MAGIC_LEN))
			जाओ found;
		data--;
	पूर्ण
	वापस शून्य;

found:
	hdr = (u32 *)(data - 8);
	size = le32_to_cpu(hdr[0]);
	csum = le32_to_cpu(hdr[1]);

	data = ((व्योम *)hdr) - size;
	अगर ((अचिन्हित दीर्घ)data < initrd_start) अणु
		pr_err("bootconfig size %d is greater than initrd size %ld\n",
			size, initrd_end - initrd_start);
		वापस शून्य;
	पूर्ण

	/* Remove bootconfig from initramfs/initrd */
	initrd_end = (अचिन्हित दीर्घ)data;
	अगर (_size)
		*_size = size;
	अगर (_csum)
		*_csum = csum;

	वापस data;
पूर्ण
#अन्यथा
अटल व्योम * __init get_boot_config_from_initrd(u32 *_size, u32 *_csum)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_BOOT_CONFIG

अटल अक्षर xbc_namebuf[XBC_KEYLEN_MAX] __initdata;

#घोषणा rest(dst, end) ((end) > (dst) ? (end) - (dst) : 0)

अटल पूर्णांक __init xbc_snprपूर्णांक_cmdline(अक्षर *buf, माप_प्रकार size,
				      काष्ठा xbc_node *root)
अणु
	काष्ठा xbc_node *knode, *vnode;
	अक्षर *end = buf + size;
	स्थिर अक्षर *val;
	पूर्णांक ret;

	xbc_node_क्रम_each_key_value(root, knode, val) अणु
		ret = xbc_node_compose_key_after(root, knode,
					xbc_namebuf, XBC_KEYLEN_MAX);
		अगर (ret < 0)
			वापस ret;

		vnode = xbc_node_get_child(knode);
		अगर (!vnode) अणु
			ret = snम_लिखो(buf, rest(buf, end), "%s ", xbc_namebuf);
			अगर (ret < 0)
				वापस ret;
			buf += ret;
			जारी;
		पूर्ण
		xbc_array_क्रम_each_value(vnode, val) अणु
			ret = snम_लिखो(buf, rest(buf, end), "%s=\"%s\" ",
				       xbc_namebuf, val);
			अगर (ret < 0)
				वापस ret;
			buf += ret;
		पूर्ण
	पूर्ण

	वापस buf - (end - size);
पूर्ण
#अघोषित rest

/* Make an extra command line under given key word */
अटल अक्षर * __init xbc_make_cmdline(स्थिर अक्षर *key)
अणु
	काष्ठा xbc_node *root;
	अक्षर *new_cmdline;
	पूर्णांक ret, len = 0;

	root = xbc_find_node(key);
	अगर (!root)
		वापस शून्य;

	/* Count required buffer size */
	len = xbc_snprपूर्णांक_cmdline(शून्य, 0, root);
	अगर (len <= 0)
		वापस शून्य;

	new_cmdline = memblock_alloc(len + 1, SMP_CACHE_BYTES);
	अगर (!new_cmdline) अणु
		pr_err("Failed to allocate memory for extra kernel cmdline.\n");
		वापस शून्य;
	पूर्ण

	ret = xbc_snprपूर्णांक_cmdline(new_cmdline, len + 1, root);
	अगर (ret < 0 || ret > len) अणु
		pr_err("Failed to print extra kernel cmdline.\n");
		वापस शून्य;
	पूर्ण

	वापस new_cmdline;
पूर्ण

अटल u32 boot_config_checksum(अचिन्हित अक्षर *p, u32 size)
अणु
	u32 ret = 0;

	जबतक (size--)
		ret += *p++;

	वापस ret;
पूर्ण

अटल पूर्णांक __init bootconfig_params(अक्षर *param, अक्षर *val,
				    स्थिर अक्षर *unused, व्योम *arg)
अणु
	अगर (म_भेद(param, "bootconfig") == 0) अणु
		bootconfig_found = true;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम __init setup_boot_config(व्योम)
अणु
	अटल अक्षर पंचांगp_cmdline[COMMAND_LINE_SIZE] __initdata;
	स्थिर अक्षर *msg;
	पूर्णांक pos;
	u32 size, csum;
	अक्षर *data, *copy, *err;
	पूर्णांक ret;

	/* Cut out the bootconfig data even अगर we have no bootconfig option */
	data = get_boot_config_from_initrd(&size, &csum);

	strlcpy(पंचांगp_cmdline, boot_command_line, COMMAND_LINE_SIZE);
	err = parse_args("bootconfig", पंचांगp_cmdline, शून्य, 0, 0, 0, शून्य,
			 bootconfig_params);

	अगर (IS_ERR(err) || !bootconfig_found)
		वापस;

	/* parse_args() stops at '--' and वापसs an address */
	अगर (err)
		initargs_found = true;

	अगर (!data) अणु
		pr_err("'bootconfig' found on command line, but no bootconfig found\n");
		वापस;
	पूर्ण

	अगर (size >= XBC_DATA_MAX) अणु
		pr_err("bootconfig size %d greater than max size %d\n",
			size, XBC_DATA_MAX);
		वापस;
	पूर्ण

	अगर (boot_config_checksum((अचिन्हित अक्षर *)data, size) != csum) अणु
		pr_err("bootconfig checksum failed\n");
		वापस;
	पूर्ण

	copy = memblock_alloc(size + 1, SMP_CACHE_BYTES);
	अगर (!copy) अणु
		pr_err("Failed to allocate memory for bootconfig\n");
		वापस;
	पूर्ण

	स_नकल(copy, data, size);
	copy[size] = '\0';

	ret = xbc_init(copy, &msg, &pos);
	अगर (ret < 0) अणु
		अगर (pos < 0)
			pr_err("Failed to init bootconfig: %s.\n", msg);
		अन्यथा
			pr_err("Failed to parse bootconfig: %s at %d.\n",
				msg, pos);
	पूर्ण अन्यथा अणु
		pr_info("Load bootconfig: %d bytes %d nodes\n", size, ret);
		/* keys starting with "kernel." are passed via cmdline */
		extra_command_line = xbc_make_cmdline("kernel");
		/* Also, "init." keys are init arguments */
		extra_init_args = xbc_make_cmdline("init");
	पूर्ण
	वापस;
पूर्ण

#अन्यथा

अटल व्योम __init setup_boot_config(व्योम)
अणु
	/* Remove bootconfig data from initrd */
	get_boot_config_from_initrd(शून्य, शून्य);
पूर्ण

अटल पूर्णांक __init warn_bootconfig(अक्षर *str)
अणु
	pr_warn("WARNING: 'bootconfig' found on the kernel command line but CONFIG_BOOT_CONFIG is not set.\n");
	वापस 0;
पूर्ण
early_param("bootconfig", warn_bootconfig);

#पूर्ण_अगर

/* Change NUL term back to "=", to make "param" the whole string. */
अटल व्योम __init repair_env_string(अक्षर *param, अक्षर *val)
अणु
	अगर (val) अणु
		/* param=val or param="val"? */
		अगर (val == param+म_माप(param)+1)
			val[-1] = '=';
		अन्यथा अगर (val == param+म_माप(param)+2) अणु
			val[-2] = '=';
			स_हटाओ(val-1, val, म_माप(val)+1);
		पूर्ण अन्यथा
			BUG();
	पूर्ण
पूर्ण

/* Anything after -- माला_लो handed straight to init. */
अटल पूर्णांक __init set_init_arg(अक्षर *param, अक्षर *val,
			       स्थिर अक्षर *unused, व्योम *arg)
अणु
	अचिन्हित पूर्णांक i;

	अगर (panic_later)
		वापस 0;

	repair_env_string(param, val);

	क्रम (i = 0; argv_init[i]; i++) अणु
		अगर (i == MAX_INIT_ARGS) अणु
			panic_later = "init";
			panic_param = param;
			वापस 0;
		पूर्ण
	पूर्ण
	argv_init[i] = param;
	वापस 0;
पूर्ण

/*
 * Unknown boot options get handed to init, unless they look like
 * unused parameters (modprobe will find them in /proc/cmdline).
 */
अटल पूर्णांक __init unknown_bootoption(अक्षर *param, अक्षर *val,
				     स्थिर अक्षर *unused, व्योम *arg)
अणु
	माप_प्रकार len = म_माप(param);

	repair_env_string(param, val);

	/* Handle obsolete-style parameters */
	अगर (obsolete_checksetup(param))
		वापस 0;

	/* Unused module parameter. */
	अगर (strnchr(param, len, '.'))
		वापस 0;

	अगर (panic_later)
		वापस 0;

	अगर (val) अणु
		/* Environment option */
		अचिन्हित पूर्णांक i;
		क्रम (i = 0; envp_init[i]; i++) अणु
			अगर (i == MAX_INIT_ENVS) अणु
				panic_later = "env";
				panic_param = param;
			पूर्ण
			अगर (!म_भेदन(param, envp_init[i], len+1))
				अवरोध;
		पूर्ण
		envp_init[i] = param;
	पूर्ण अन्यथा अणु
		/* Command line option */
		अचिन्हित पूर्णांक i;
		क्रम (i = 0; argv_init[i]; i++) अणु
			अगर (i == MAX_INIT_ARGS) अणु
				panic_later = "init";
				panic_param = param;
			पूर्ण
		पूर्ण
		argv_init[i] = param;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __init init_setup(अक्षर *str)
अणु
	अचिन्हित पूर्णांक i;

	execute_command = str;
	/*
	 * In हाल LILO is going to boot us with शेष command line,
	 * it prepends "auto" beक्रमe the whole cmdline which makes
	 * the shell think it should execute a script with such name.
	 * So we ignore all arguments entered _beक्रमe_ init=... [MJ]
	 */
	क्रम (i = 1; i < MAX_INIT_ARGS; i++)
		argv_init[i] = शून्य;
	वापस 1;
पूर्ण
__setup("init=", init_setup);

अटल पूर्णांक __init rdinit_setup(अक्षर *str)
अणु
	अचिन्हित पूर्णांक i;

	ramdisk_execute_command = str;
	/* See "auto" comment in init_setup */
	क्रम (i = 1; i < MAX_INIT_ARGS; i++)
		argv_init[i] = शून्य;
	वापस 1;
पूर्ण
__setup("rdinit=", rdinit_setup);

#अगर_अघोषित CONFIG_SMP
अटल स्थिर अचिन्हित पूर्णांक setup_max_cpus = NR_CPUS;
अटल अंतरभूत व्योम setup_nr_cpu_ids(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम smp_prepare_cpus(अचिन्हित पूर्णांक maxcpus) अणु पूर्ण
#पूर्ण_अगर

/*
 * We need to store the untouched command line क्रम future reference.
 * We also need to store the touched command line since the parameter
 * parsing is perक्रमmed in place, and we should allow a component to
 * store reference of name/value क्रम future reference.
 */
अटल व्योम __init setup_command_line(अक्षर *command_line)
अणु
	माप_प्रकार len, xlen = 0, ilen = 0;

	अगर (extra_command_line)
		xlen = म_माप(extra_command_line);
	अगर (extra_init_args)
		ilen = म_माप(extra_init_args) + 4; /* क्रम " -- " */

	len = xlen + म_माप(boot_command_line) + 1;

	saved_command_line = memblock_alloc(len + ilen, SMP_CACHE_BYTES);
	अगर (!saved_command_line)
		panic("%s: Failed to allocate %zu bytes\n", __func__, len + ilen);

	अटल_command_line = memblock_alloc(len, SMP_CACHE_BYTES);
	अगर (!अटल_command_line)
		panic("%s: Failed to allocate %zu bytes\n", __func__, len);

	अगर (xlen) अणु
		/*
		 * We have to put extra_command_line beक्रमe boot command
		 * lines because there could be dashes (separator of init
		 * command line) in the command lines.
		 */
		म_नकल(saved_command_line, extra_command_line);
		म_नकल(अटल_command_line, extra_command_line);
	पूर्ण
	म_नकल(saved_command_line + xlen, boot_command_line);
	म_नकल(अटल_command_line + xlen, command_line);

	अगर (ilen) अणु
		/*
		 * Append supplemental init boot args to saved_command_line
		 * so that user can check what command line options passed
		 * to init.
		 */
		len = म_माप(saved_command_line);
		अगर (initargs_found) अणु
			saved_command_line[len++] = ' ';
		पूर्ण अन्यथा अणु
			म_नकल(saved_command_line + len, " -- ");
			len += 4;
		पूर्ण

		म_नकल(saved_command_line + len, extra_init_args);
	पूर्ण
पूर्ण

/*
 * We need to finalize in a non-__init function or अन्यथा race conditions
 * between the root thपढ़ो and the init thपढ़ो may cause start_kernel to
 * be reaped by मुक्त_iniपंचांगem beक्रमe the root thपढ़ो has proceeded to
 * cpu_idle.
 *
 * gcc-3.4 accidentally अंतरभूतs this function, so use noअंतरभूत.
 */

अटल __initdata DECLARE_COMPLETION(kthपढ़ोd_करोne);

noअंतरभूत व्योम __ref rest_init(व्योम)
अणु
	काष्ठा task_काष्ठा *tsk;
	पूर्णांक pid;

	rcu_scheduler_starting();
	/*
	 * We need to spawn init first so that it obtains pid 1, however
	 * the init task will end up wanting to create kthपढ़ोs, which, अगर
	 * we schedule it beक्रमe we create kthपढ़ोd, will OOPS.
	 */
	pid = kernel_thपढ़ो(kernel_init, शून्य, CLONE_FS);
	/*
	 * Pin init on the boot CPU. Task migration is not properly working
	 * until sched_init_smp() has been run. It will set the allowed
	 * CPUs क्रम init to the non isolated CPUs.
	 */
	rcu_पढ़ो_lock();
	tsk = find_task_by_pid_ns(pid, &init_pid_ns);
	set_cpus_allowed_ptr(tsk, cpumask_of(smp_processor_id()));
	rcu_पढ़ो_unlock();

	numa_शेष_policy();
	pid = kernel_thपढ़ो(kthपढ़ोd, शून्य, CLONE_FS | CLONE_खाताS);
	rcu_पढ़ो_lock();
	kthपढ़ोd_task = find_task_by_pid_ns(pid, &init_pid_ns);
	rcu_पढ़ो_unlock();

	/*
	 * Enable might_sleep() and smp_processor_id() checks.
	 * They cannot be enabled earlier because with CONFIG_PREEMPTION=y
	 * kernel_thपढ़ो() would trigger might_sleep() splats. With
	 * CONFIG_PREEMPT_VOLUNTARY=y the init task might have scheduled
	 * alपढ़ोy, but it's stuck on the kthपढ़ोd_करोne completion.
	 */
	प्रणाली_state = SYSTEM_SCHEDULING;

	complete(&kthपढ़ोd_करोne);

	/*
	 * The boot idle thपढ़ो must execute schedule()
	 * at least once to get things moving:
	 */
	schedule_preempt_disabled();
	/* Call पूर्णांकo cpu_idle with preempt disabled */
	cpu_startup_entry(CPUHP_ONLINE);
पूर्ण

/* Check क्रम early params. */
अटल पूर्णांक __init करो_early_param(अक्षर *param, अक्षर *val,
				 स्थिर अक्षर *unused, व्योम *arg)
अणु
	स्थिर काष्ठा obs_kernel_param *p;

	क्रम (p = __setup_start; p < __setup_end; p++) अणु
		अगर ((p->early && parameq(param, p->str)) ||
		    (म_भेद(param, "console") == 0 &&
		     म_भेद(p->str, "earlycon") == 0)
		) अणु
			अगर (p->setup_func(val) != 0)
				pr_warn("Malformed early option '%s'\n", param);
		पूर्ण
	पूर्ण
	/* We accept everything at this stage. */
	वापस 0;
पूर्ण

व्योम __init parse_early_options(अक्षर *cmdline)
अणु
	parse_args("early options", cmdline, शून्य, 0, 0, 0, शून्य,
		   करो_early_param);
पूर्ण

/* Arch code calls this early on, or अगर not, just beक्रमe other parsing. */
व्योम __init parse_early_param(व्योम)
अणु
	अटल पूर्णांक करोne __initdata;
	अटल अक्षर पंचांगp_cmdline[COMMAND_LINE_SIZE] __initdata;

	अगर (करोne)
		वापस;

	/* All fall through to करो_early_param. */
	strlcpy(पंचांगp_cmdline, boot_command_line, COMMAND_LINE_SIZE);
	parse_early_options(पंचांगp_cmdline);
	करोne = 1;
पूर्ण

व्योम __init __weak arch_post_acpi_subsys_init(व्योम) अणु पूर्ण

व्योम __init __weak smp_setup_processor_id(व्योम)
अणु
पूर्ण

# अगर THREAD_SIZE >= PAGE_SIZE
व्योम __init __weak thपढ़ो_stack_cache_init(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

व्योम __init __weak mem_encrypt_init(व्योम) अणु पूर्ण

व्योम __init __weak poking_init(व्योम) अणु पूर्ण

व्योम __init __weak pgtable_cache_init(व्योम) अणु पूर्ण

bool initcall_debug;
core_param(initcall_debug, initcall_debug, bool, 0644);

#अगर_घोषित TRACEPOINTS_ENABLED
अटल व्योम __init initcall_debug_enable(व्योम);
#अन्यथा
अटल अंतरभूत व्योम initcall_debug_enable(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

/* Report memory स्वतः-initialization states क्रम this boot. */
अटल व्योम __init report_meminit(व्योम)
अणु
	स्थिर अक्षर *stack;

	अगर (IS_ENABLED(CONFIG_INIT_STACK_ALL_PATTERN))
		stack = "all(pattern)";
	अन्यथा अगर (IS_ENABLED(CONFIG_INIT_STACK_ALL_ZERO))
		stack = "all(zero)";
	अन्यथा अगर (IS_ENABLED(CONFIG_GCC_PLUGIN_STRUCTLEAK_BYREF_ALL))
		stack = "byref_all(zero)";
	अन्यथा अगर (IS_ENABLED(CONFIG_GCC_PLUGIN_STRUCTLEAK_BYREF))
		stack = "byref(zero)";
	अन्यथा अगर (IS_ENABLED(CONFIG_GCC_PLUGIN_STRUCTLEAK_USER))
		stack = "__user(zero)";
	अन्यथा
		stack = "off";

	pr_info("mem auto-init: stack:%s, heap alloc:%s, heap free:%s\n",
		stack, want_init_on_alloc(GFP_KERNEL) ? "on" : "off",
		want_init_on_मुक्त() ? "on" : "off");
	अगर (want_init_on_मुक्त())
		pr_info("mem auto-init: clearing system memory may take some time...\n");
पूर्ण

/*
 * Set up kernel memory allocators
 */
अटल व्योम __init mm_init(व्योम)
अणु
	/*
	 * page_ext requires contiguous pages,
	 * bigger than MAX_ORDER unless SPARSEMEM.
	 */
	page_ext_init_flaपंचांगem();
	init_mem_debugging_and_hardening();
	kfence_alloc_pool();
	report_meminit();
	stack_depot_init();
	mem_init();
	mem_init_prपूर्णांक_info();
	/* page_owner must be initialized after buddy is पढ़ोy */
	page_ext_init_flaपंचांगem_late();
	kmem_cache_init();
	kmemleak_init();
	pgtable_init();
	debug_objects_mem_init();
	vदो_स्मृति_init();
	/* Should be run beक्रमe the first non-init thपढ़ो is created */
	init_espfix_bsp();
	/* Should be run after espfix64 is set up. */
	pti_init();
पूर्ण

#अगर_घोषित CONFIG_HAVE_ARCH_RANDOMIZE_KSTACK_OFFSET
DEFINE_STATIC_KEY_MAYBE_RO(CONFIG_RANDOMIZE_KSTACK_OFFSET_DEFAULT,
			   अक्रमomize_kstack_offset);
DEFINE_PER_CPU(u32, kstack_offset);

अटल पूर्णांक __init early_अक्रमomize_kstack_offset(अक्षर *buf)
अणु
	पूर्णांक ret;
	bool bool_result;

	ret = kstrtobool(buf, &bool_result);
	अगर (ret)
		वापस ret;

	अगर (bool_result)
		अटल_branch_enable(&अक्रमomize_kstack_offset);
	अन्यथा
		अटल_branch_disable(&अक्रमomize_kstack_offset);
	वापस 0;
पूर्ण
early_param("randomize_kstack_offset", early_अक्रमomize_kstack_offset);
#पूर्ण_अगर

व्योम __init __weak arch_call_rest_init(व्योम)
अणु
	rest_init();
पूर्ण

यंत्रlinkage __visible व्योम __init __no_sanitize_address start_kernel(व्योम)
अणु
	अक्षर *command_line;
	अक्षर *after_dashes;

	set_task_stack_end_magic(&init_task);
	smp_setup_processor_id();
	debug_objects_early_init();

	cgroup_init_early();

	local_irq_disable();
	early_boot_irqs_disabled = true;

	/*
	 * Interrupts are still disabled. Do necessary setups, then
	 * enable them.
	 */
	boot_cpu_init();
	page_address_init();
	pr_notice("%s", linux_banner);
	early_security_init();
	setup_arch(&command_line);
	setup_boot_config();
	setup_command_line(command_line);
	setup_nr_cpu_ids();
	setup_per_cpu_areas();
	smp_prepare_boot_cpu();	/* arch-specअगरic boot-cpu hooks */
	boot_cpu_hotplug_init();

	build_all_zonelists(शून्य);
	page_alloc_init();

	pr_notice("Kernel command line: %s\n", saved_command_line);
	/* parameters may set अटल keys */
	jump_label_init();
	parse_early_param();
	after_dashes = parse_args("Booting kernel",
				  अटल_command_line, __start___param,
				  __stop___param - __start___param,
				  -1, -1, शून्य, &unknown_bootoption);
	अगर (!IS_ERR_OR_शून्य(after_dashes))
		parse_args("Setting init args", after_dashes, शून्य, 0, -1, -1,
			   शून्य, set_init_arg);
	अगर (extra_init_args)
		parse_args("Setting extra init args", extra_init_args,
			   शून्य, 0, -1, -1, शून्य, set_init_arg);

	/*
	 * These use large booपंचांगem allocations and must precede
	 * kmem_cache_init()
	 */
	setup_log_buf(0);
	vfs_caches_init_early();
	sort_मुख्य_extable();
	trap_init();
	mm_init();

	ftrace_init();

	/* trace_prपूर्णांकk can be enabled here */
	early_trace_init();

	/*
	 * Set up the scheduler prior starting any पूर्णांकerrupts (such as the
	 * समयr पूर्णांकerrupt). Full topology setup happens at smp_init()
	 * समय - but meanजबतक we still have a functioning scheduler.
	 */
	sched_init();
	/*
	 * Disable preemption - early bootup scheduling is extremely
	 * fragile until we cpu_idle() क्रम the first समय.
	 */
	preempt_disable();
	अगर (WARN(!irqs_disabled(),
		 "Interrupts were enabled *very* early, fixing it\n"))
		local_irq_disable();
	radix_tree_init();

	/*
	 * Set up housekeeping beक्रमe setting up workqueues to allow the unbound
	 * workqueue to take non-housekeeping पूर्णांकo account.
	 */
	housekeeping_init();

	/*
	 * Allow workqueue creation and work item queueing/cancelling
	 * early.  Work item execution depends on kthपढ़ोs and starts after
	 * workqueue_init().
	 */
	workqueue_init_early();

	rcu_init();

	/* Trace events are available after this */
	trace_init();

	अगर (initcall_debug)
		initcall_debug_enable();

	context_tracking_init();
	/* init some links beक्रमe init_ISA_irqs() */
	early_irq_init();
	init_IRQ();
	tick_init();
	rcu_init_nohz();
	init_समयrs();
	hrसमयrs_init();
	softirq_init();
	समयkeeping_init();
	kfence_init();

	/*
	 * For best initial stack canary entropy, prepare it after:
	 * - setup_arch() क्रम any UEFI RNG entropy and boot cmdline access
	 * - समयkeeping_init() क्रम kसमय entropy used in अक्रम_initialize()
	 * - अक्रम_initialize() to get any arch-specअगरic entropy like RDRAND
	 * - add_latent_entropy() to get any latent entropy
	 * - adding command line entropy
	 */
	अक्रम_initialize();
	add_latent_entropy();
	add_device_अक्रमomness(command_line, म_माप(command_line));
	boot_init_stack_canary();

	समय_init();
	perf_event_init();
	profile_init();
	call_function_init();
	WARN(!irqs_disabled(), "Interrupts were enabled early\n");

	early_boot_irqs_disabled = false;
	local_irq_enable();

	kmem_cache_init_late();

	/*
	 * HACK ALERT! This is early. We're enabling the console beक्रमe
	 * we've करोne PCI setups etc, and console_init() must be aware of
	 * this. But we करो want output early, in हाल something goes wrong.
	 */
	console_init();
	अगर (panic_later)
		panic("Too many boot %s vars at `%s'", panic_later,
		      panic_param);

	lockdep_init();

	/*
	 * Need to run this when irqs are enabled, because it wants
	 * to self-test [hard/soft]-irqs on/off lock inversion bugs
	 * too:
	 */
	locking_selftest();

	/*
	 * This needs to be called beक्रमe any devices perक्रमm DMA
	 * operations that might use the SWIOTLB bounce buffers. It will
	 * mark the bounce buffers as decrypted so that their usage will
	 * not cause "plain-text" data to be decrypted when accessed.
	 */
	mem_encrypt_init();

#अगर_घोषित CONFIG_BLK_DEV_INITRD
	अगर (initrd_start && !initrd_below_start_ok &&
	    page_to_pfn(virt_to_page((व्योम *)initrd_start)) < min_low_pfn) अणु
		pr_crit("initrd overwritten (0x%08lx < 0x%08lx) - disabling it.\n",
		    page_to_pfn(virt_to_page((व्योम *)initrd_start)),
		    min_low_pfn);
		initrd_start = 0;
	पूर्ण
#पूर्ण_अगर
	setup_per_cpu_pageset();
	numa_policy_init();
	acpi_early_init();
	अगर (late_समय_init)
		late_समय_init();
	sched_घड़ी_init();
	calibrate_delay();
	pid_idr_init();
	anon_vma_init();
#अगर_घोषित CONFIG_X86
	अगर (efi_enabled(EFI_RUNTIME_SERVICES))
		efi_enter_भव_mode();
#पूर्ण_अगर
	thपढ़ो_stack_cache_init();
	cred_init();
	विभाजन_init();
	proc_caches_init();
	uts_ns_init();
	key_init();
	security_init();
	dbg_late_init();
	vfs_caches_init();
	pagecache_init();
	संकेतs_init();
	seq_file_init();
	proc_root_init();
	nsfs_init();
	cpuset_init();
	cgroup_init();
	taskstats_init_early();
	delayacct_init();

	poking_init();
	check_bugs();

	acpi_subप्रणाली_init();
	arch_post_acpi_subsys_init();
	kcsan_init();

	/* Do the rest non-__init'ed, we're now alive */
	arch_call_rest_init();

	prevent_tail_call_optimization();
पूर्ण

/* Call all स्थिरructor functions linked पूर्णांकo the kernel. */
अटल व्योम __init करो_ctors(व्योम)
अणु
/*
 * For UML, the स्थिरructors have alपढ़ोy been called by the
 * normal setup code as it's just a normal ELF binary, so we
 * cannot करो it again - but we करो need CONFIG_CONSTRUCTORS
 * even on UML क्रम modules.
 */
#अगर defined(CONFIG_CONSTRUCTORS) && !defined(CONFIG_UML)
	ctor_fn_t *fn = (ctor_fn_t *) __ctors_start;

	क्रम (; fn < (ctor_fn_t *) __ctors_end; fn++)
		(*fn)();
#पूर्ण_अगर
पूर्ण

#अगर_घोषित CONFIG_KALLSYMS
काष्ठा blacklist_entry अणु
	काष्ठा list_head next;
	अक्षर *buf;
पूर्ण;

अटल __initdata_or_module LIST_HEAD(blacklisted_initcalls);

अटल पूर्णांक __init initcall_blacklist(अक्षर *str)
अणु
	अक्षर *str_entry;
	काष्ठा blacklist_entry *entry;

	/* str argument is a comma-separated list of functions */
	करो अणु
		str_entry = strsep(&str, ",");
		अगर (str_entry) अणु
			pr_debug("blacklisting initcall %s\n", str_entry);
			entry = memblock_alloc(माप(*entry),
					       SMP_CACHE_BYTES);
			अगर (!entry)
				panic("%s: Failed to allocate %zu bytes\n",
				      __func__, माप(*entry));
			entry->buf = memblock_alloc(म_माप(str_entry) + 1,
						    SMP_CACHE_BYTES);
			अगर (!entry->buf)
				panic("%s: Failed to allocate %zu bytes\n",
				      __func__, म_माप(str_entry) + 1);
			म_नकल(entry->buf, str_entry);
			list_add(&entry->next, &blacklisted_initcalls);
		पूर्ण
	पूर्ण जबतक (str_entry);

	वापस 0;
पूर्ण

अटल bool __init_or_module initcall_blacklisted(initcall_t fn)
अणु
	काष्ठा blacklist_entry *entry;
	अक्षर fn_name[KSYM_SYMBOL_LEN];
	अचिन्हित दीर्घ addr;

	अगर (list_empty(&blacklisted_initcalls))
		वापस false;

	addr = (अचिन्हित दीर्घ) dereference_function_descriptor(fn);
	sprपूर्णांक_symbol_no_offset(fn_name, addr);

	/*
	 * fn will be "function_name [module_name]" where [module_name] is not
	 * displayed क्रम built-in init functions.  Strip off the [module_name].
	 */
	strreplace(fn_name, ' ', '\0');

	list_क्रम_each_entry(entry, &blacklisted_initcalls, next) अणु
		अगर (!म_भेद(fn_name, entry->buf)) अणु
			pr_debug("initcall %s blacklisted\n", fn_name);
			वापस true;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण
#अन्यथा
अटल पूर्णांक __init initcall_blacklist(अक्षर *str)
अणु
	pr_warn("initcall_blacklist requires CONFIG_KALLSYMS\n");
	वापस 0;
पूर्ण

अटल bool __init_or_module initcall_blacklisted(initcall_t fn)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर
__setup("initcall_blacklist=", initcall_blacklist);

अटल __init_or_module व्योम
trace_initcall_start_cb(व्योम *data, initcall_t fn)
अणु
	kसमय_प्रकार *callसमय = (kसमय_प्रकार *)data;

	prपूर्णांकk(KERN_DEBUG "calling  %pS @ %i\n", fn, task_pid_nr(current));
	*callसमय = kसमय_get();
पूर्ण

अटल __init_or_module व्योम
trace_initcall_finish_cb(व्योम *data, initcall_t fn, पूर्णांक ret)
अणु
	kसमय_प्रकार *callसमय = (kसमय_प्रकार *)data;
	kसमय_प्रकार delta, retसमय;
	अचिन्हित दीर्घ दीर्घ duration;

	retसमय = kसमय_get();
	delta = kसमय_sub(retसमय, *callसमय);
	duration = (अचिन्हित दीर्घ दीर्घ) kसमय_प्रकारo_ns(delta) >> 10;
	prपूर्णांकk(KERN_DEBUG "initcall %pS returned %d after %lld usecs\n",
		 fn, ret, duration);
पूर्ण

अटल kसमय_प्रकार initcall_callसमय;

#अगर_घोषित TRACEPOINTS_ENABLED
अटल व्योम __init initcall_debug_enable(व्योम)
अणु
	पूर्णांक ret;

	ret = रेजिस्टर_trace_initcall_start(trace_initcall_start_cb,
					    &initcall_callसमय);
	ret |= रेजिस्टर_trace_initcall_finish(trace_initcall_finish_cb,
					      &initcall_callसमय);
	WARN(ret, "Failed to register initcall tracepoints\n");
पूर्ण
# define करो_trace_initcall_start	trace_initcall_start
# define करो_trace_initcall_finish	trace_initcall_finish
#अन्यथा
अटल अंतरभूत व्योम करो_trace_initcall_start(initcall_t fn)
अणु
	अगर (!initcall_debug)
		वापस;
	trace_initcall_start_cb(&initcall_callसमय, fn);
पूर्ण
अटल अंतरभूत व्योम करो_trace_initcall_finish(initcall_t fn, पूर्णांक ret)
अणु
	अगर (!initcall_debug)
		वापस;
	trace_initcall_finish_cb(&initcall_callसमय, fn, ret);
पूर्ण
#पूर्ण_अगर /* !TRACEPOINTS_ENABLED */

पूर्णांक __init_or_module करो_one_initcall(initcall_t fn)
अणु
	पूर्णांक count = preempt_count();
	अक्षर msgbuf[64];
	पूर्णांक ret;

	अगर (initcall_blacklisted(fn))
		वापस -EPERM;

	करो_trace_initcall_start(fn);
	ret = fn();
	करो_trace_initcall_finish(fn, ret);

	msgbuf[0] = 0;

	अगर (preempt_count() != count) अणु
		प्र_लिखो(msgbuf, "preemption imbalance ");
		preempt_count_set(count);
	पूर्ण
	अगर (irqs_disabled()) अणु
		strlcat(msgbuf, "disabled interrupts ", माप(msgbuf));
		local_irq_enable();
	पूर्ण
	WARN(msgbuf[0], "initcall %pS returned with %s\n", fn, msgbuf);

	add_latent_entropy();
	वापस ret;
पूर्ण


बाह्य initcall_entry_t __initcall_start[];
बाह्य initcall_entry_t __initcall0_start[];
बाह्य initcall_entry_t __initcall1_start[];
बाह्य initcall_entry_t __initcall2_start[];
बाह्य initcall_entry_t __initcall3_start[];
बाह्य initcall_entry_t __initcall4_start[];
बाह्य initcall_entry_t __initcall5_start[];
बाह्य initcall_entry_t __initcall6_start[];
बाह्य initcall_entry_t __initcall7_start[];
बाह्य initcall_entry_t __initcall_end[];

अटल initcall_entry_t *initcall_levels[] __initdata = अणु
	__initcall0_start,
	__initcall1_start,
	__initcall2_start,
	__initcall3_start,
	__initcall4_start,
	__initcall5_start,
	__initcall6_start,
	__initcall7_start,
	__initcall_end,
पूर्ण;

/* Keep these in sync with initcalls in include/linux/init.h */
अटल स्थिर अक्षर *initcall_level_names[] __initdata = अणु
	"pure",
	"core",
	"postcore",
	"arch",
	"subsys",
	"fs",
	"device",
	"late",
पूर्ण;

अटल पूर्णांक __init ignore_unknown_bootoption(अक्षर *param, अक्षर *val,
			       स्थिर अक्षर *unused, व्योम *arg)
अणु
	वापस 0;
पूर्ण

अटल व्योम __init करो_initcall_level(पूर्णांक level, अक्षर *command_line)
अणु
	initcall_entry_t *fn;

	parse_args(initcall_level_names[level],
		   command_line, __start___param,
		   __stop___param - __start___param,
		   level, level,
		   शून्य, ignore_unknown_bootoption);

	trace_initcall_level(initcall_level_names[level]);
	क्रम (fn = initcall_levels[level]; fn < initcall_levels[level+1]; fn++)
		करो_one_initcall(initcall_from_entry(fn));
पूर्ण

अटल व्योम __init करो_initcalls(व्योम)
अणु
	पूर्णांक level;
	माप_प्रकार len = म_माप(saved_command_line) + 1;
	अक्षर *command_line;

	command_line = kzalloc(len, GFP_KERNEL);
	अगर (!command_line)
		panic("%s: Failed to allocate %zu bytes\n", __func__, len);

	क्रम (level = 0; level < ARRAY_SIZE(initcall_levels) - 1; level++) अणु
		/* Parser modअगरies command_line, restore it each समय */
		म_नकल(command_line, saved_command_line);
		करो_initcall_level(level, command_line);
	पूर्ण

	kमुक्त(command_line);
पूर्ण

/*
 * Ok, the machine is now initialized. None of the devices
 * have been touched yet, but the CPU subप्रणाली is up and
 * running, and memory and process management works.
 *
 * Now we can finally start करोing some real work..
 */
अटल व्योम __init करो_basic_setup(व्योम)
अणु
	cpuset_init_smp();
	driver_init();
	init_irq_proc();
	करो_ctors();
	usermodehelper_enable();
	करो_initcalls();
पूर्ण

अटल व्योम __init करो_pre_smp_initcalls(व्योम)
अणु
	initcall_entry_t *fn;

	trace_initcall_level("early");
	क्रम (fn = __initcall_start; fn < __initcall0_start; fn++)
		करो_one_initcall(initcall_from_entry(fn));
पूर्ण

अटल पूर्णांक run_init_process(स्थिर अक्षर *init_filename)
अणु
	स्थिर अक्षर *स्थिर *p;

	argv_init[0] = init_filename;
	pr_info("Run %s as init process\n", init_filename);
	pr_debug("  with arguments:\n");
	क्रम (p = argv_init; *p; p++)
		pr_debug("    %s\n", *p);
	pr_debug("  with environment:\n");
	क्रम (p = envp_init; *p; p++)
		pr_debug("    %s\n", *p);
	वापस kernel_execve(init_filename, argv_init, envp_init);
पूर्ण

अटल पूर्णांक try_to_run_init_process(स्थिर अक्षर *init_filename)
अणु
	पूर्णांक ret;

	ret = run_init_process(init_filename);

	अगर (ret && ret != -ENOENT) अणु
		pr_err("Starting init: %s exists but couldn't execute it (error %d)\n",
		       init_filename, ret);
	पूर्ण

	वापस ret;
पूर्ण

अटल noअंतरभूत व्योम __init kernel_init_मुक्तable(व्योम);

#अगर defined(CONFIG_STRICT_KERNEL_RWX) || defined(CONFIG_STRICT_MODULE_RWX)
bool rodata_enabled __ro_after_init = true;
अटल पूर्णांक __init set_debug_rodata(अक्षर *str)
अणु
	वापस strtobool(str, &rodata_enabled);
पूर्ण
__setup("rodata=", set_debug_rodata);
#पूर्ण_अगर

#अगर_घोषित CONFIG_STRICT_KERNEL_RWX
अटल व्योम mark_पढ़ोonly(व्योम)
अणु
	अगर (rodata_enabled) अणु
		/*
		 * load_module() results in W+X mappings, which are cleaned
		 * up with call_rcu().  Let's make sure that queued work is
		 * flushed so that we करोn't hit false positives looking क्रम
		 * insecure pages which are W+X.
		 */
		rcu_barrier();
		mark_rodata_ro();
		rodata_test();
	पूर्ण अन्यथा
		pr_info("Kernel memory protection disabled.\n");
पूर्ण
#या_अगर defined(CONFIG_ARCH_HAS_STRICT_KERNEL_RWX)
अटल अंतरभूत व्योम mark_पढ़ोonly(व्योम)
अणु
	pr_warn("Kernel memory protection not selected by kernel config.\n");
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम mark_पढ़ोonly(व्योम)
अणु
	pr_warn("This architecture does not have kernel memory protection.\n");
पूर्ण
#पूर्ण_अगर

व्योम __weak मुक्त_iniपंचांगem(व्योम)
अणु
	मुक्त_iniपंचांगem_शेष(POISON_FREE_INITMEM);
पूर्ण

अटल पूर्णांक __ref kernel_init(व्योम *unused)
अणु
	पूर्णांक ret;

	kernel_init_मुक्तable();
	/* need to finish all async __init code beक्रमe मुक्तing the memory */
	async_synchronize_full();
	kprobe_मुक्त_init_mem();
	ftrace_मुक्त_init_mem();
	kgdb_मुक्त_init_mem();
	मुक्त_iniपंचांगem();
	mark_पढ़ोonly();

	/*
	 * Kernel mappings are now finalized - update the userspace page-table
	 * to finalize PTI.
	 */
	pti_finalize();

	प्रणाली_state = SYSTEM_RUNNING;
	numa_शेष_policy();

	rcu_end_inkernel_boot();

	करो_sysctl_args();

	अगर (ramdisk_execute_command) अणु
		ret = run_init_process(ramdisk_execute_command);
		अगर (!ret)
			वापस 0;
		pr_err("Failed to execute %s (error %d)\n",
		       ramdisk_execute_command, ret);
	पूर्ण

	/*
	 * We try each of these until one succeeds.
	 *
	 * The Bourne shell can be used instead of init अगर we are
	 * trying to recover a really broken machine.
	 */
	अगर (execute_command) अणु
		ret = run_init_process(execute_command);
		अगर (!ret)
			वापस 0;
		panic("Requested init %s failed (error %d).",
		      execute_command, ret);
	पूर्ण

	अगर (CONFIG_DEFAULT_INIT[0] != '\0') अणु
		ret = run_init_process(CONFIG_DEFAULT_INIT);
		अगर (ret)
			pr_err("Default init %s failed (error %d)\n",
			       CONFIG_DEFAULT_INIT, ret);
		अन्यथा
			वापस 0;
	पूर्ण

	अगर (!try_to_run_init_process("/sbin/init") ||
	    !try_to_run_init_process("/etc/init") ||
	    !try_to_run_init_process("/bin/init") ||
	    !try_to_run_init_process("/bin/sh"))
		वापस 0;

	panic("No working init found.  Try passing init= option to kernel. "
	      "See Linux Documentation/admin-guide/init.rst for guidance.");
पूर्ण

/* Open /dev/console, क्रम मानक_निवेश/मानक_निकास/मानक_त्रुटि, this should never fail */
व्योम __init console_on_rootfs(व्योम)
अणु
	काष्ठा file *file = filp_खोलो("/dev/console", O_RDWR, 0);

	अगर (IS_ERR(file)) अणु
		pr_err("Warning: unable to open an initial console.\n");
		वापस;
	पूर्ण
	init_dup(file);
	init_dup(file);
	init_dup(file);
	fput(file);
पूर्ण

अटल noअंतरभूत व्योम __init kernel_init_मुक्तable(व्योम)
अणु
	/*
	 * Wait until kthपढ़ोd is all set-up.
	 */
	रुको_क्रम_completion(&kthपढ़ोd_करोne);

	/* Now the scheduler is fully set up and can करो blocking allocations */
	gfp_allowed_mask = __GFP_BITS_MASK;

	/*
	 * init can allocate pages on any node
	 */
	set_mems_allowed(node_states[N_MEMORY]);

	cad_pid = get_pid(task_pid(current));

	smp_prepare_cpus(setup_max_cpus);

	workqueue_init();

	init_mm_पूर्णांकernals();

	rcu_init_tasks_generic();
	करो_pre_smp_initcalls();
	lockup_detector_init();

	smp_init();
	sched_init_smp();

	padata_init();
	page_alloc_init_late();
	/* Initialize page ext after all काष्ठा pages are initialized. */
	page_ext_init();

	करो_basic_setup();

	kunit_run_all_tests();

	रुको_क्रम_initramfs();
	console_on_rootfs();

	/*
	 * check अगर there is an early userspace init.  If yes, let it करो all
	 * the work
	 */
	अगर (init_eaccess(ramdisk_execute_command) != 0) अणु
		ramdisk_execute_command = शून्य;
		prepare_namespace();
	पूर्ण

	/*
	 * Ok, we have completed the initial bootup, and
	 * we're essentially up and running. Get rid of the
	 * iniपंचांगem segments and start the user-mode stuff..
	 *
	 * rootfs is available now, try loading the खुला keys
	 * and शेष modules
	 */

	पूर्णांकegrity_load_keys();
पूर्ण
