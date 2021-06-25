<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * CPU Microcode Update Driver क्रम Linux
 *
 * Copyright (C) 2000-2006 Tigran Aivazian <aivazian.tigran@gmail.com>
 *	      2006	Shaohua Li <shaohua.li@पूर्णांकel.com>
 *	      2013-2016	Borislav Petkov <bp@alien8.de>
 *
 * X86 CPU microcode early update क्रम Linux:
 *
 *	Copyright (C) 2012 Fenghua Yu <fenghua.yu@पूर्णांकel.com>
 *			   H Peter Anvin" <hpa@zytor.com>
 *		  (C) 2015 Borislav Petkov <bp@alien8.de>
 *
 * This driver allows to upgrade microcode on x86 processors.
 */

#घोषणा pr_fmt(fmt) "microcode: " fmt

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/stop_machine.h>
#समावेश <linux/syscore_ops.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/capability.h>
#समावेश <linux/firmware.h>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/mutex.h>
#समावेश <linux/cpu.h>
#समावेश <linux/nmi.h>
#समावेश <linux/fs.h>
#समावेश <linux/mm.h>

#समावेश <यंत्र/microcode_पूर्णांकel.h>
#समावेश <यंत्र/cpu_device_id.h>
#समावेश <यंत्र/microcode_amd.h>
#समावेश <यंत्र/perf_event.h>
#समावेश <यंत्र/microcode.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/cmdline.h>
#समावेश <यंत्र/setup.h>

#घोषणा DRIVER_VERSION	"2.2"

अटल काष्ठा microcode_ops	*microcode_ops;
अटल bool dis_ucode_ldr = true;

bool initrd_gone;

LIST_HEAD(microcode_cache);

/*
 * Synchronization.
 *
 * All non cpu-hotplug-callback call sites use:
 *
 * - microcode_mutex to synchronize with each other;
 * - get/put_online_cpus() to synchronize with
 *   the cpu-hotplug-callback call sites.
 *
 * We guarantee that only a single cpu is being
 * updated at any particular moment of समय.
 */
अटल DEFINE_MUTEX(microcode_mutex);

काष्ठा ucode_cpu_info		ucode_cpu_info[NR_CPUS];

काष्ठा cpu_info_ctx अणु
	काष्ठा cpu_signature	*cpu_sig;
	पूर्णांक			err;
पूर्ण;

/*
 * Those patch levels cannot be updated to newer ones and thus should be final.
 */
अटल u32 final_levels[] = अणु
	0x01000098,
	0x0100009f,
	0x010000af,
	0, /* T-101 terminator */
पूर्ण;

/*
 * Check the current patch level on this CPU.
 *
 * Returns:
 *  - true: अगर update should stop
 *  - false: otherwise
 */
अटल bool amd_check_current_patch_level(व्योम)
अणु
	u32 lvl, dummy, i;
	u32 *levels;

	native_rdmsr(MSR_AMD64_PATCH_LEVEL, lvl, dummy);

	अगर (IS_ENABLED(CONFIG_X86_32))
		levels = (u32 *)__pa_nodebug(&final_levels);
	अन्यथा
		levels = final_levels;

	क्रम (i = 0; levels[i]; i++) अणु
		अगर (lvl == levels[i])
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल bool __init check_loader_disabled_bsp(व्योम)
अणु
	अटल स्थिर अक्षर *__dis_opt_str = "dis_ucode_ldr";

#अगर_घोषित CONFIG_X86_32
	स्थिर अक्षर *cmdline = (स्थिर अक्षर *)__pa_nodebug(boot_command_line);
	स्थिर अक्षर *option  = (स्थिर अक्षर *)__pa_nodebug(__dis_opt_str);
	bool *res = (bool *)__pa_nodebug(&dis_ucode_ldr);

#अन्यथा /* CONFIG_X86_64 */
	स्थिर अक्षर *cmdline = boot_command_line;
	स्थिर अक्षर *option  = __dis_opt_str;
	bool *res = &dis_ucode_ldr;
#पूर्ण_अगर

	/*
	 * CPUID(1).ECX[31]: reserved क्रम hypervisor use. This is still not
	 * completely accurate as xen pv guests करोn't see that CPUID bit set but
	 * that's good enough as they don't land on the BSP path anyway.
	 */
	अगर (native_cpuid_ecx(1) & BIT(31))
		वापस *res;

	अगर (x86_cpuid_venकरोr() == X86_VENDOR_AMD) अणु
		अगर (amd_check_current_patch_level())
			वापस *res;
	पूर्ण

	अगर (cmdline_find_option_bool(cmdline, option) <= 0)
		*res = false;

	वापस *res;
पूर्ण

बाह्य काष्ठा builtin_fw __start_builtin_fw[];
बाह्य काष्ठा builtin_fw __end_builtin_fw[];

bool get_builtin_firmware(काष्ठा cpio_data *cd, स्थिर अक्षर *name)
अणु
	काष्ठा builtin_fw *b_fw;

	क्रम (b_fw = __start_builtin_fw; b_fw != __end_builtin_fw; b_fw++) अणु
		अगर (!म_भेद(name, b_fw->name)) अणु
			cd->size = b_fw->size;
			cd->data = b_fw->data;
			वापस true;
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण

व्योम __init load_ucode_bsp(व्योम)
अणु
	अचिन्हित पूर्णांक cpuid_1_eax;
	bool पूर्णांकel = true;

	अगर (!have_cpuid_p())
		वापस;

	cpuid_1_eax = native_cpuid_eax(1);

	चयन (x86_cpuid_venकरोr()) अणु
	हाल X86_VENDOR_INTEL:
		अगर (x86_family(cpuid_1_eax) < 6)
			वापस;
		अवरोध;

	हाल X86_VENDOR_AMD:
		अगर (x86_family(cpuid_1_eax) < 0x10)
			वापस;
		पूर्णांकel = false;
		अवरोध;

	शेष:
		वापस;
	पूर्ण

	अगर (check_loader_disabled_bsp())
		वापस;

	अगर (पूर्णांकel)
		load_ucode_पूर्णांकel_bsp();
	अन्यथा
		load_ucode_amd_bsp(cpuid_1_eax);
पूर्ण

अटल bool check_loader_disabled_ap(व्योम)
अणु
#अगर_घोषित CONFIG_X86_32
	वापस *((bool *)__pa_nodebug(&dis_ucode_ldr));
#अन्यथा
	वापस dis_ucode_ldr;
#पूर्ण_अगर
पूर्ण

व्योम load_ucode_ap(व्योम)
अणु
	अचिन्हित पूर्णांक cpuid_1_eax;

	अगर (check_loader_disabled_ap())
		वापस;

	cpuid_1_eax = native_cpuid_eax(1);

	चयन (x86_cpuid_venकरोr()) अणु
	हाल X86_VENDOR_INTEL:
		अगर (x86_family(cpuid_1_eax) >= 6)
			load_ucode_पूर्णांकel_ap();
		अवरोध;
	हाल X86_VENDOR_AMD:
		अगर (x86_family(cpuid_1_eax) >= 0x10)
			load_ucode_amd_ap(cpuid_1_eax);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक __init save_microcode_in_initrd(व्योम)
अणु
	काष्ठा cpuinfo_x86 *c = &boot_cpu_data;
	पूर्णांक ret = -EINVAL;

	चयन (c->x86_venकरोr) अणु
	हाल X86_VENDOR_INTEL:
		अगर (c->x86 >= 6)
			ret = save_microcode_in_initrd_पूर्णांकel();
		अवरोध;
	हाल X86_VENDOR_AMD:
		अगर (c->x86 >= 0x10)
			ret = save_microcode_in_initrd_amd(cpuid_eax(1));
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	initrd_gone = true;

	वापस ret;
पूर्ण

काष्ठा cpio_data find_microcode_in_initrd(स्थिर अक्षर *path, bool use_pa)
अणु
#अगर_घोषित CONFIG_BLK_DEV_INITRD
	अचिन्हित दीर्घ start = 0;
	माप_प्रकार size;

#अगर_घोषित CONFIG_X86_32
	काष्ठा boot_params *params;

	अगर (use_pa)
		params = (काष्ठा boot_params *)__pa_nodebug(&boot_params);
	अन्यथा
		params = &boot_params;

	size = params->hdr.ramdisk_size;

	/*
	 * Set start only अगर we have an initrd image. We cannot use initrd_start
	 * because it is not set that early yet.
	 */
	अगर (size)
		start = params->hdr.ramdisk_image;

# अन्यथा /* CONFIG_X86_64 */
	size  = (अचिन्हित दीर्घ)boot_params.ext_ramdisk_size << 32;
	size |= boot_params.hdr.ramdisk_size;

	अगर (size) अणु
		start  = (अचिन्हित दीर्घ)boot_params.ext_ramdisk_image << 32;
		start |= boot_params.hdr.ramdisk_image;

		start += PAGE_OFFSET;
	पूर्ण
# endअगर

	/*
	 * Fixup the start address: after reserve_initrd() runs, initrd_start
	 * has the भव address of the beginning of the initrd. It also
	 * possibly relocates the ramdisk. In either हाल, initrd_start contains
	 * the updated address so use that instead.
	 *
	 * initrd_gone is क्रम the hotplug हाल where we've thrown out initrd
	 * alपढ़ोy.
	 */
	अगर (!use_pa) अणु
		अगर (initrd_gone)
			वापस (काष्ठा cpio_data)अणु शून्य, 0, "" पूर्ण;
		अगर (initrd_start)
			start = initrd_start;
	पूर्ण अन्यथा अणु
		/*
		 * The picture with physical addresses is a bit dअगरferent: we
		 * need to get the *physical* address to which the ramdisk was
		 * relocated, i.e., relocated_ramdisk (not initrd_start) and
		 * since we're running from physical addresses, we need to access
		 * relocated_ramdisk through its *physical* address too.
		 */
		u64 *rr = (u64 *)__pa_nodebug(&relocated_ramdisk);
		अगर (*rr)
			start = *rr;
	पूर्ण

	वापस find_cpio_data(path, (व्योम *)start, size, शून्य);
#अन्यथा /* !CONFIG_BLK_DEV_INITRD */
	वापस (काष्ठा cpio_data)अणु शून्य, 0, "" पूर्ण;
#पूर्ण_अगर
पूर्ण

व्योम reload_early_microcode(व्योम)
अणु
	पूर्णांक venकरोr, family;

	venकरोr = x86_cpuid_venकरोr();
	family = x86_cpuid_family();

	चयन (venकरोr) अणु
	हाल X86_VENDOR_INTEL:
		अगर (family >= 6)
			reload_ucode_पूर्णांकel();
		अवरोध;
	हाल X86_VENDOR_AMD:
		अगर (family >= 0x10)
			reload_ucode_amd();
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम collect_cpu_info_local(व्योम *arg)
अणु
	काष्ठा cpu_info_ctx *ctx = arg;

	ctx->err = microcode_ops->collect_cpu_info(smp_processor_id(),
						   ctx->cpu_sig);
पूर्ण

अटल पूर्णांक collect_cpu_info_on_target(पूर्णांक cpu, काष्ठा cpu_signature *cpu_sig)
अणु
	काष्ठा cpu_info_ctx ctx = अणु .cpu_sig = cpu_sig, .err = 0 पूर्ण;
	पूर्णांक ret;

	ret = smp_call_function_single(cpu, collect_cpu_info_local, &ctx, 1);
	अगर (!ret)
		ret = ctx.err;

	वापस ret;
पूर्ण

अटल पूर्णांक collect_cpu_info(पूर्णांक cpu)
अणु
	काष्ठा ucode_cpu_info *uci = ucode_cpu_info + cpu;
	पूर्णांक ret;

	स_रखो(uci, 0, माप(*uci));

	ret = collect_cpu_info_on_target(cpu, &uci->cpu_sig);
	अगर (!ret)
		uci->valid = 1;

	वापस ret;
पूर्ण

अटल व्योम apply_microcode_local(व्योम *arg)
अणु
	क्रमागत ucode_state *err = arg;

	*err = microcode_ops->apply_microcode(smp_processor_id());
पूर्ण

अटल पूर्णांक apply_microcode_on_target(पूर्णांक cpu)
अणु
	क्रमागत ucode_state err;
	पूर्णांक ret;

	ret = smp_call_function_single(cpu, apply_microcode_local, &err, 1);
	अगर (!ret) अणु
		अगर (err == UCODE_ERROR)
			ret = 1;
	पूर्ण
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_MICROCODE_OLD_INTERFACE
अटल पूर्णांक करो_microcode_update(स्थिर व्योम __user *buf, माप_प्रकार size)
अणु
	पूर्णांक error = 0;
	पूर्णांक cpu;

	क्रम_each_online_cpu(cpu) अणु
		काष्ठा ucode_cpu_info *uci = ucode_cpu_info + cpu;
		क्रमागत ucode_state ustate;

		अगर (!uci->valid)
			जारी;

		ustate = microcode_ops->request_microcode_user(cpu, buf, size);
		अगर (ustate == UCODE_ERROR) अणु
			error = -1;
			अवरोध;
		पूर्ण अन्यथा अगर (ustate == UCODE_NEW) अणु
			apply_microcode_on_target(cpu);
		पूर्ण
	पूर्ण

	वापस error;
पूर्ण

अटल पूर्णांक microcode_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस capable(CAP_SYS_RAWIO) ? stream_खोलो(inode, file) : -EPERM;
पूर्ण

अटल sमाप_प्रकार microcode_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
			       माप_प्रकार len, loff_t *ppos)
अणु
	sमाप_प्रकार ret = -EINVAL;
	अचिन्हित दीर्घ nr_pages = totalram_pages();

	अगर ((len >> PAGE_SHIFT) > nr_pages) अणु
		pr_err("too much data (max %ld pages)\n", nr_pages);
		वापस ret;
	पूर्ण

	get_online_cpus();
	mutex_lock(&microcode_mutex);

	अगर (करो_microcode_update(buf, len) == 0)
		ret = (sमाप_प्रकार)len;

	अगर (ret > 0)
		perf_check_microcode();

	mutex_unlock(&microcode_mutex);
	put_online_cpus();

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations microcode_fops = अणु
	.owner			= THIS_MODULE,
	.ग_लिखो			= microcode_ग_लिखो,
	.खोलो			= microcode_खोलो,
	.llseek		= no_llseek,
पूर्ण;

अटल काष्ठा miscdevice microcode_dev = अणु
	.minor			= MICROCODE_MINOR,
	.name			= "microcode",
	.nodename		= "cpu/microcode",
	.fops			= &microcode_fops,
पूर्ण;

अटल पूर्णांक __init microcode_dev_init(व्योम)
अणु
	पूर्णांक error;

	error = misc_रेजिस्टर(&microcode_dev);
	अगर (error) अणु
		pr_err("can't misc_register on minor=%d\n", MICROCODE_MINOR);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास microcode_dev_निकास(व्योम)
अणु
	misc_deरेजिस्टर(&microcode_dev);
पूर्ण
#अन्यथा
#घोषणा microcode_dev_init()	0
#घोषणा microcode_dev_निकास()	करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

/* fake device क्रम request_firmware */
अटल काष्ठा platक्रमm_device	*microcode_pdev;

/*
 * Late loading dance. Why the heavy-handed stomp_machine efक्रमt?
 *
 * - HT siblings must be idle and not execute other code जबतक the other sibling
 *   is loading microcode in order to aव्योम any negative पूर्णांकeractions caused by
 *   the loading.
 *
 * - In addition, microcode update on the cores must be serialized until this
 *   requirement can be relaxed in the future. Right now, this is conservative
 *   and good.
 */
#घोषणा SPINUNIT 100 /* 100 nsec */

अटल पूर्णांक check_online_cpus(व्योम)
अणु
	अचिन्हित पूर्णांक cpu;

	/*
	 * Make sure all CPUs are online.  It's fine क्रम SMT to be disabled अगर
	 * all the primary thपढ़ोs are still online.
	 */
	क्रम_each_present_cpu(cpu) अणु
		अगर (topology_is_primary_thपढ़ो(cpu) && !cpu_online(cpu)) अणु
			pr_err("Not all CPUs online, aborting microcode update.\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल atomic_t late_cpus_in;
अटल atomic_t late_cpus_out;

अटल पूर्णांक __रुको_क्रम_cpus(atomic_t *t, दीर्घ दीर्घ समयout)
अणु
	पूर्णांक all_cpus = num_online_cpus();

	atomic_inc(t);

	जबतक (atomic_पढ़ो(t) < all_cpus) अणु
		अगर (समयout < SPINUNIT) अणु
			pr_err("Timeout while waiting for CPUs rendezvous, remaining: %d\n",
				all_cpus - atomic_पढ़ो(t));
			वापस 1;
		पूर्ण

		ndelay(SPINUNIT);
		समयout -= SPINUNIT;

		touch_nmi_watchकरोg();
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Returns:
 * < 0 - on error
 *   0 - success (no update करोne or microcode was updated)
 */
अटल पूर्णांक __reload_late(व्योम *info)
अणु
	पूर्णांक cpu = smp_processor_id();
	क्रमागत ucode_state err;
	पूर्णांक ret = 0;

	/*
	 * Wait क्रम all CPUs to arrive. A load will not be attempted unless all
	 * CPUs show up.
	 * */
	अगर (__रुको_क्रम_cpus(&late_cpus_in, NSEC_PER_SEC))
		वापस -1;

	/*
	 * On an SMT प्रणाली, it suffices to load the microcode on one sibling of
	 * the core because the microcode engine is shared between the thपढ़ोs.
	 * Synchronization still needs to take place so that no concurrent
	 * loading attempts happen on multiple thपढ़ोs of an SMT core. See
	 * below.
	 */
	अगर (cpumask_first(topology_sibling_cpumask(cpu)) == cpu)
		apply_microcode_local(&err);
	अन्यथा
		जाओ रुको_क्रम_siblings;

	अगर (err >= UCODE_NFOUND) अणु
		अगर (err == UCODE_ERROR)
			pr_warn("Error reloading microcode on CPU %d\n", cpu);

		ret = -1;
	पूर्ण

रुको_क्रम_siblings:
	अगर (__रुको_क्रम_cpus(&late_cpus_out, NSEC_PER_SEC))
		panic("Timeout during microcode update!\n");

	/*
	 * At least one thपढ़ो has completed update on each core.
	 * For others, simply call the update to make sure the
	 * per-cpu cpuinfo can be updated with right microcode
	 * revision.
	 */
	अगर (cpumask_first(topology_sibling_cpumask(cpu)) != cpu)
		apply_microcode_local(&err);

	वापस ret;
पूर्ण

/*
 * Reload microcode late on all CPUs. Wait क्रम a sec until they
 * all gather together.
 */
अटल पूर्णांक microcode_reload_late(व्योम)
अणु
	पूर्णांक ret;

	atomic_set(&late_cpus_in,  0);
	atomic_set(&late_cpus_out, 0);

	ret = stop_machine_cpuslocked(__reload_late, शून्य, cpu_online_mask);
	अगर (ret == 0)
		microcode_check();

	pr_info("Reload completed, microcode revision: 0x%x\n", boot_cpu_data.microcode);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार reload_store(काष्ठा device *dev,
			    काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	क्रमागत ucode_state पंचांगp_ret = UCODE_OK;
	पूर्णांक bsp = boot_cpu_data.cpu_index;
	अचिन्हित दीर्घ val;
	sमाप_प्रकार ret = 0;

	ret = kम_से_अदीर्घ(buf, 0, &val);
	अगर (ret)
		वापस ret;

	अगर (val != 1)
		वापस size;

	get_online_cpus();

	ret = check_online_cpus();
	अगर (ret)
		जाओ put;

	पंचांगp_ret = microcode_ops->request_microcode_fw(bsp, &microcode_pdev->dev, true);
	अगर (पंचांगp_ret != UCODE_NEW)
		जाओ put;

	mutex_lock(&microcode_mutex);
	ret = microcode_reload_late();
	mutex_unlock(&microcode_mutex);

put:
	put_online_cpus();

	अगर (ret == 0)
		ret = size;

	वापस ret;
पूर्ण

अटल sमाप_प्रकार version_show(काष्ठा device *dev,
			काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ucode_cpu_info *uci = ucode_cpu_info + dev->id;

	वापस प्र_लिखो(buf, "0x%x\n", uci->cpu_sig.rev);
पूर्ण

अटल sमाप_प्रकार pf_show(काष्ठा device *dev,
			काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ucode_cpu_info *uci = ucode_cpu_info + dev->id;

	वापस प्र_लिखो(buf, "0x%x\n", uci->cpu_sig.pf);
पूर्ण

अटल DEVICE_ATTR_WO(reload);
अटल DEVICE_ATTR(version, 0444, version_show, शून्य);
अटल DEVICE_ATTR(processor_flags, 0444, pf_show, शून्य);

अटल काष्ठा attribute *mc_शेष_attrs[] = अणु
	&dev_attr_version.attr,
	&dev_attr_processor_flags.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group mc_attr_group = अणु
	.attrs			= mc_शेष_attrs,
	.name			= "microcode",
पूर्ण;

अटल व्योम microcode_fini_cpu(पूर्णांक cpu)
अणु
	अगर (microcode_ops->microcode_fini_cpu)
		microcode_ops->microcode_fini_cpu(cpu);
पूर्ण

अटल क्रमागत ucode_state microcode_resume_cpu(पूर्णांक cpu)
अणु
	अगर (apply_microcode_on_target(cpu))
		वापस UCODE_ERROR;

	pr_debug("CPU%d updated upon resume\n", cpu);

	वापस UCODE_OK;
पूर्ण

अटल क्रमागत ucode_state microcode_init_cpu(पूर्णांक cpu, bool refresh_fw)
अणु
	क्रमागत ucode_state ustate;
	काष्ठा ucode_cpu_info *uci = ucode_cpu_info + cpu;

	अगर (uci->valid)
		वापस UCODE_OK;

	अगर (collect_cpu_info(cpu))
		वापस UCODE_ERROR;

	/* --dimm. Trigger a delayed update? */
	अगर (प्रणाली_state != SYSTEM_RUNNING)
		वापस UCODE_NFOUND;

	ustate = microcode_ops->request_microcode_fw(cpu, &microcode_pdev->dev, refresh_fw);
	अगर (ustate == UCODE_NEW) अणु
		pr_debug("CPU%d updated upon init\n", cpu);
		apply_microcode_on_target(cpu);
	पूर्ण

	वापस ustate;
पूर्ण

अटल क्रमागत ucode_state microcode_update_cpu(पूर्णांक cpu)
अणु
	काष्ठा ucode_cpu_info *uci = ucode_cpu_info + cpu;

	/* Refresh CPU microcode revision after resume. */
	collect_cpu_info(cpu);

	अगर (uci->valid)
		वापस microcode_resume_cpu(cpu);

	वापस microcode_init_cpu(cpu, false);
पूर्ण

अटल पूर्णांक mc_device_add(काष्ठा device *dev, काष्ठा subsys_पूर्णांकerface *sअगर)
अणु
	पूर्णांक err, cpu = dev->id;

	अगर (!cpu_online(cpu))
		वापस 0;

	pr_debug("CPU%d added\n", cpu);

	err = sysfs_create_group(&dev->kobj, &mc_attr_group);
	अगर (err)
		वापस err;

	अगर (microcode_init_cpu(cpu, true) == UCODE_ERROR)
		वापस -EINVAL;

	वापस err;
पूर्ण

अटल व्योम mc_device_हटाओ(काष्ठा device *dev, काष्ठा subsys_पूर्णांकerface *sअगर)
अणु
	पूर्णांक cpu = dev->id;

	अगर (!cpu_online(cpu))
		वापस;

	pr_debug("CPU%d removed\n", cpu);
	microcode_fini_cpu(cpu);
	sysfs_हटाओ_group(&dev->kobj, &mc_attr_group);
पूर्ण

अटल काष्ठा subsys_पूर्णांकerface mc_cpu_पूर्णांकerface = अणु
	.name			= "microcode",
	.subsys			= &cpu_subsys,
	.add_dev		= mc_device_add,
	.हटाओ_dev		= mc_device_हटाओ,
पूर्ण;

/**
 * mc_bp_resume - Update boot CPU microcode during resume.
 */
अटल व्योम mc_bp_resume(व्योम)
अणु
	पूर्णांक cpu = smp_processor_id();
	काष्ठा ucode_cpu_info *uci = ucode_cpu_info + cpu;

	अगर (uci->valid && uci->mc)
		microcode_ops->apply_microcode(cpu);
	अन्यथा अगर (!uci->mc)
		reload_early_microcode();
पूर्ण

अटल काष्ठा syscore_ops mc_syscore_ops = अणु
	.resume			= mc_bp_resume,
पूर्ण;

अटल पूर्णांक mc_cpu_starting(अचिन्हित पूर्णांक cpu)
अणु
	microcode_update_cpu(cpu);
	pr_debug("CPU%d added\n", cpu);
	वापस 0;
पूर्ण

अटल पूर्णांक mc_cpu_online(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा device *dev = get_cpu_device(cpu);

	अगर (sysfs_create_group(&dev->kobj, &mc_attr_group))
		pr_err("Failed to create group for CPU%d\n", cpu);
	वापस 0;
पूर्ण

अटल पूर्णांक mc_cpu_करोwn_prep(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा device *dev;

	dev = get_cpu_device(cpu);
	/* Suspend is in progress, only हटाओ the पूर्णांकerface */
	sysfs_हटाओ_group(&dev->kobj, &mc_attr_group);
	pr_debug("CPU%d removed\n", cpu);

	वापस 0;
पूर्ण

अटल काष्ठा attribute *cpu_root_microcode_attrs[] = अणु
	&dev_attr_reload.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group cpu_root_microcode_group = अणु
	.name  = "microcode",
	.attrs = cpu_root_microcode_attrs,
पूर्ण;

अटल पूर्णांक __init microcode_init(व्योम)
अणु
	काष्ठा cpuinfo_x86 *c = &boot_cpu_data;
	पूर्णांक error;

	अगर (dis_ucode_ldr)
		वापस -EINVAL;

	अगर (c->x86_venकरोr == X86_VENDOR_INTEL)
		microcode_ops = init_पूर्णांकel_microcode();
	अन्यथा अगर (c->x86_venकरोr == X86_VENDOR_AMD)
		microcode_ops = init_amd_microcode();
	अन्यथा
		pr_err("no support for this CPU vendor\n");

	अगर (!microcode_ops)
		वापस -ENODEV;

	microcode_pdev = platक्रमm_device_रेजिस्टर_simple("microcode", -1,
							 शून्य, 0);
	अगर (IS_ERR(microcode_pdev))
		वापस PTR_ERR(microcode_pdev);

	get_online_cpus();
	mutex_lock(&microcode_mutex);

	error = subsys_पूर्णांकerface_रेजिस्टर(&mc_cpu_पूर्णांकerface);
	अगर (!error)
		perf_check_microcode();
	mutex_unlock(&microcode_mutex);
	put_online_cpus();

	अगर (error)
		जाओ out_pdev;

	error = sysfs_create_group(&cpu_subsys.dev_root->kobj,
				   &cpu_root_microcode_group);

	अगर (error) अणु
		pr_err("Error creating microcode group!\n");
		जाओ out_driver;
	पूर्ण

	error = microcode_dev_init();
	अगर (error)
		जाओ out_ucode_group;

	रेजिस्टर_syscore_ops(&mc_syscore_ops);
	cpuhp_setup_state_nocalls(CPUHP_AP_MICROCODE_LOADER, "x86/microcode:starting",
				  mc_cpu_starting, शून्य);
	cpuhp_setup_state_nocalls(CPUHP_AP_ONLINE_DYN, "x86/microcode:online",
				  mc_cpu_online, mc_cpu_करोwn_prep);

	pr_info("Microcode Update Driver: v%s.", DRIVER_VERSION);

	वापस 0;

 out_ucode_group:
	sysfs_हटाओ_group(&cpu_subsys.dev_root->kobj,
			   &cpu_root_microcode_group);

 out_driver:
	get_online_cpus();
	mutex_lock(&microcode_mutex);

	subsys_पूर्णांकerface_unरेजिस्टर(&mc_cpu_पूर्णांकerface);

	mutex_unlock(&microcode_mutex);
	put_online_cpus();

 out_pdev:
	platक्रमm_device_unरेजिस्टर(microcode_pdev);
	वापस error;

पूर्ण
fs_initcall(save_microcode_in_initrd);
late_initcall(microcode_init);
