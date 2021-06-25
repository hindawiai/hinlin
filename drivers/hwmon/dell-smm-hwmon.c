<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * dell-smm-hwmon.c -- Linux driver क्रम accessing the SMM BIOS on Dell laptops.
 *
 * Copyright (C) 2001  Massimo Dal Zotto <dz@debian.org>
 *
 * Hwmon पूर्णांकegration:
 * Copyright (C) 2011  Jean Delvare <jdelvare@suse.de>
 * Copyright (C) 2013, 2014  Guenter Roeck <linux@roeck-us.net>
 * Copyright (C) 2014, 2015  Pali Rohथँr <pali@kernel.org>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/cpu.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/init.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/dmi.h>
#समावेश <linux/capability.h>
#समावेश <linux/mutex.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/पन.स>
#समावेश <linux/sched.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/smp.h>

#समावेश <linux/i8k.h>

#घोषणा I8K_SMM_FN_STATUS	0x0025
#घोषणा I8K_SMM_POWER_STATUS	0x0069
#घोषणा I8K_SMM_SET_FAN		0x01a3
#घोषणा I8K_SMM_GET_FAN		0x00a3
#घोषणा I8K_SMM_GET_SPEED	0x02a3
#घोषणा I8K_SMM_GET_FAN_TYPE	0x03a3
#घोषणा I8K_SMM_GET_NOM_SPEED	0x04a3
#घोषणा I8K_SMM_GET_TEMP	0x10a3
#घोषणा I8K_SMM_GET_TEMP_TYPE	0x11a3
#घोषणा I8K_SMM_GET_DELL_SIG1	0xfea3
#घोषणा I8K_SMM_GET_DELL_SIG2	0xffa3

#घोषणा I8K_FAN_MULT		30
#घोषणा I8K_FAN_MAX_RPM		30000
#घोषणा I8K_MAX_TEMP		127

#घोषणा I8K_FN_NONE		0x00
#घोषणा I8K_FN_UP		0x01
#घोषणा I8K_FN_DOWN		0x02
#घोषणा I8K_FN_MUTE		0x04
#घोषणा I8K_FN_MASK		0x07
#घोषणा I8K_FN_SHIFT		8

#घोषणा I8K_POWER_AC		0x05
#घोषणा I8K_POWER_BATTERY	0x01

अटल DEFINE_MUTEX(i8k_mutex);
अटल अक्षर bios_version[4];
अटल अक्षर bios_machineid[16];
अटल काष्ठा device *i8k_hwmon_dev;
अटल u32 i8k_hwmon_flags;
अटल uपूर्णांक i8k_fan_mult = I8K_FAN_MULT;
अटल uपूर्णांक i8k_pwm_mult;
अटल uपूर्णांक i8k_fan_max = I8K_FAN_HIGH;
अटल bool disallow_fan_type_call;
अटल bool disallow_fan_support;
अटल अचिन्हित पूर्णांक manual_fan;
अटल अचिन्हित पूर्णांक स्वतः_fan;

#घोषणा I8K_HWMON_HAVE_TEMP1	(1 << 0)
#घोषणा I8K_HWMON_HAVE_TEMP2	(1 << 1)
#घोषणा I8K_HWMON_HAVE_TEMP3	(1 << 2)
#घोषणा I8K_HWMON_HAVE_TEMP4	(1 << 3)
#घोषणा I8K_HWMON_HAVE_TEMP5	(1 << 4)
#घोषणा I8K_HWMON_HAVE_TEMP6	(1 << 5)
#घोषणा I8K_HWMON_HAVE_TEMP7	(1 << 6)
#घोषणा I8K_HWMON_HAVE_TEMP8	(1 << 7)
#घोषणा I8K_HWMON_HAVE_TEMP9	(1 << 8)
#घोषणा I8K_HWMON_HAVE_TEMP10	(1 << 9)
#घोषणा I8K_HWMON_HAVE_FAN1	(1 << 10)
#घोषणा I8K_HWMON_HAVE_FAN2	(1 << 11)
#घोषणा I8K_HWMON_HAVE_FAN3	(1 << 12)

MODULE_AUTHOR("Massimo Dal Zotto (dz@debian.org)");
MODULE_AUTHOR("Pali Rohथँr <pali@kernel.org>");
MODULE_DESCRIPTION("Dell laptop SMM BIOS hwmon driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("i8k");

अटल bool क्रमce;
module_param(क्रमce, bool, 0);
MODULE_PARM_DESC(क्रमce, "Force loading without checking for supported models");

अटल bool ignore_dmi;
module_param(ignore_dmi, bool, 0);
MODULE_PARM_DESC(ignore_dmi, "Continue probing hardware even if DMI data does not match");

#अगर IS_ENABLED(CONFIG_I8K)
अटल bool restricted = true;
module_param(restricted, bool, 0);
MODULE_PARM_DESC(restricted, "Restrict fan control and serial number to CAP_SYS_ADMIN (default: 1)");

अटल bool घातer_status;
module_param(घातer_status, bool, 0600);
MODULE_PARM_DESC(घातer_status, "Report power status in /proc/i8k (default: 0)");
#पूर्ण_अगर

अटल uपूर्णांक fan_mult;
module_param(fan_mult, uपूर्णांक, 0);
MODULE_PARM_DESC(fan_mult, "Factor to multiply fan speed with (default: autodetect)");

अटल uपूर्णांक fan_max;
module_param(fan_max, uपूर्णांक, 0);
MODULE_PARM_DESC(fan_max, "Maximum configurable fan speed (default: autodetect)");

काष्ठा smm_regs अणु
	अचिन्हित पूर्णांक eax;
	अचिन्हित पूर्णांक ebx __packed;
	अचिन्हित पूर्णांक ecx __packed;
	अचिन्हित पूर्णांक edx __packed;
	अचिन्हित पूर्णांक esi __packed;
	अचिन्हित पूर्णांक edi __packed;
पूर्ण;

अटल अंतरभूत स्थिर अक्षर *i8k_get_dmi_data(पूर्णांक field)
अणु
	स्थिर अक्षर *dmi_data = dmi_get_प्रणाली_info(field);

	वापस dmi_data && *dmi_data ? dmi_data : "?";
पूर्ण

/*
 * Call the System Management Mode BIOS. Code provided by Jonathan Buzzard.
 */
अटल पूर्णांक i8k_smm_func(व्योम *par)
अणु
	पूर्णांक rc;
	काष्ठा smm_regs *regs = par;
	पूर्णांक eax = regs->eax;

#अगर_घोषित DEBUG
	पूर्णांक ebx = regs->ebx;
	अचिन्हित दीर्घ duration;
	kसमय_प्रकार callसमय, delta, retसमय;

	callसमय = kसमय_get();
#पूर्ण_अगर

	/* SMM requires CPU 0 */
	अगर (smp_processor_id() != 0)
		वापस -EBUSY;

#अगर defined(CONFIG_X86_64)
	यंत्र अस्थिर("pushq %%rax\n\t"
		"movl 0(%%rax),%%edx\n\t"
		"pushq %%rdx\n\t"
		"movl 4(%%rax),%%ebx\n\t"
		"movl 8(%%rax),%%ecx\n\t"
		"movl 12(%%rax),%%edx\n\t"
		"movl 16(%%rax),%%esi\n\t"
		"movl 20(%%rax),%%edi\n\t"
		"popq %%rax\n\t"
		"out %%al,$0xb2\n\t"
		"out %%al,$0x84\n\t"
		"xchgq %%rax,(%%rsp)\n\t"
		"movl %%ebx,4(%%rax)\n\t"
		"movl %%ecx,8(%%rax)\n\t"
		"movl %%edx,12(%%rax)\n\t"
		"movl %%esi,16(%%rax)\n\t"
		"movl %%edi,20(%%rax)\n\t"
		"popq %%rdx\n\t"
		"movl %%edx,0(%%rax)\n\t"
		"pushfq\n\t"
		"popq %%rax\n\t"
		"andl $1,%%eax\n"
		: "=a"(rc)
		:    "a"(regs)
		:    "%ebx", "%ecx", "%edx", "%esi", "%edi", "memory");
#अन्यथा
	यंत्र अस्थिर("pushl %%eax\n\t"
	    "movl 0(%%eax),%%edx\n\t"
	    "push %%edx\n\t"
	    "movl 4(%%eax),%%ebx\n\t"
	    "movl 8(%%eax),%%ecx\n\t"
	    "movl 12(%%eax),%%edx\n\t"
	    "movl 16(%%eax),%%esi\n\t"
	    "movl 20(%%eax),%%edi\n\t"
	    "popl %%eax\n\t"
	    "out %%al,$0xb2\n\t"
	    "out %%al,$0x84\n\t"
	    "xchgl %%eax,(%%esp)\n\t"
	    "movl %%ebx,4(%%eax)\n\t"
	    "movl %%ecx,8(%%eax)\n\t"
	    "movl %%edx,12(%%eax)\n\t"
	    "movl %%esi,16(%%eax)\n\t"
	    "movl %%edi,20(%%eax)\n\t"
	    "popl %%edx\n\t"
	    "movl %%edx,0(%%eax)\n\t"
	    "lahf\n\t"
	    "shrl $8,%%eax\n\t"
	    "andl $1,%%eax\n"
	    : "=a"(rc)
	    :    "a"(regs)
	    :    "%ebx", "%ecx", "%edx", "%esi", "%edi", "memory");
#पूर्ण_अगर
	अगर (rc != 0 || (regs->eax & 0xffff) == 0xffff || regs->eax == eax)
		rc = -EINVAL;

#अगर_घोषित DEBUG
	retसमय = kसमय_get();
	delta = kसमय_sub(retसमय, callसमय);
	duration = kसमय_प्रकारo_ns(delta) >> 10;
	pr_debug("smm(0x%.4x 0x%.4x) = 0x%.4x  (took %7lu usecs)\n", eax, ebx,
		(rc ? 0xffff : regs->eax & 0xffff), duration);
#पूर्ण_अगर

	वापस rc;
पूर्ण

/*
 * Call the System Management Mode BIOS.
 */
अटल पूर्णांक i8k_smm(काष्ठा smm_regs *regs)
अणु
	पूर्णांक ret;

	get_online_cpus();
	ret = smp_call_on_cpu(0, i8k_smm_func, regs, true);
	put_online_cpus();

	वापस ret;
पूर्ण

/*
 * Read the fan status.
 */
अटल पूर्णांक i8k_get_fan_status(पूर्णांक fan)
अणु
	काष्ठा smm_regs regs = अणु .eax = I8K_SMM_GET_FAN, पूर्ण;

	अगर (disallow_fan_support)
		वापस -EINVAL;

	regs.ebx = fan & 0xff;
	वापस i8k_smm(&regs) ? : regs.eax & 0xff;
पूर्ण

/*
 * Read the fan speed in RPM.
 */
अटल पूर्णांक i8k_get_fan_speed(पूर्णांक fan)
अणु
	काष्ठा smm_regs regs = अणु .eax = I8K_SMM_GET_SPEED, पूर्ण;

	अगर (disallow_fan_support)
		वापस -EINVAL;

	regs.ebx = fan & 0xff;
	वापस i8k_smm(&regs) ? : (regs.eax & 0xffff) * i8k_fan_mult;
पूर्ण

/*
 * Read the fan type.
 */
अटल पूर्णांक _i8k_get_fan_type(पूर्णांक fan)
अणु
	काष्ठा smm_regs regs = अणु .eax = I8K_SMM_GET_FAN_TYPE, पूर्ण;

	अगर (disallow_fan_support || disallow_fan_type_call)
		वापस -EINVAL;

	regs.ebx = fan & 0xff;
	वापस i8k_smm(&regs) ? : regs.eax & 0xff;
पूर्ण

अटल पूर्णांक i8k_get_fan_type(पूर्णांक fan)
अणु
	/* I8K_SMM_GET_FAN_TYPE SMM call is expensive, so cache values */
	अटल पूर्णांक types[3] = अणु पूर्णांक_न्यून, पूर्णांक_न्यून, पूर्णांक_न्यून पूर्ण;

	अगर (types[fan] == पूर्णांक_न्यून)
		types[fan] = _i8k_get_fan_type(fan);

	वापस types[fan];
पूर्ण

/*
 * Read the fan nominal rpm क्रम specअगरic fan speed.
 */
अटल पूर्णांक i8k_get_fan_nominal_speed(पूर्णांक fan, पूर्णांक speed)
अणु
	काष्ठा smm_regs regs = अणु .eax = I8K_SMM_GET_NOM_SPEED, पूर्ण;

	अगर (disallow_fan_support)
		वापस -EINVAL;

	regs.ebx = (fan & 0xff) | (speed << 8);
	वापस i8k_smm(&regs) ? : (regs.eax & 0xffff) * i8k_fan_mult;
पूर्ण

/*
 * Enable or disable स्वतःmatic BIOS fan control support
 */
अटल पूर्णांक i8k_enable_fan_स्वतः_mode(bool enable)
अणु
	काष्ठा smm_regs regs = अणु पूर्ण;

	अगर (disallow_fan_support)
		वापस -EINVAL;

	regs.eax = enable ? स्वतः_fan : manual_fan;
	वापस i8k_smm(&regs);
पूर्ण

/*
 * Set the fan speed (off, low, high). Returns the new fan status.
 */
अटल पूर्णांक i8k_set_fan(पूर्णांक fan, पूर्णांक speed)
अणु
	काष्ठा smm_regs regs = अणु .eax = I8K_SMM_SET_FAN, पूर्ण;

	अगर (disallow_fan_support)
		वापस -EINVAL;

	speed = (speed < 0) ? 0 : ((speed > i8k_fan_max) ? i8k_fan_max : speed);
	regs.ebx = (fan & 0xff) | (speed << 8);

	वापस i8k_smm(&regs) ? : i8k_get_fan_status(fan);
पूर्ण

अटल पूर्णांक i8k_get_temp_type(पूर्णांक sensor)
अणु
	काष्ठा smm_regs regs = अणु .eax = I8K_SMM_GET_TEMP_TYPE, पूर्ण;

	regs.ebx = sensor & 0xff;
	वापस i8k_smm(&regs) ? : regs.eax & 0xff;
पूर्ण

/*
 * Read the cpu temperature.
 */
अटल पूर्णांक _i8k_get_temp(पूर्णांक sensor)
अणु
	काष्ठा smm_regs regs = अणु
		.eax = I8K_SMM_GET_TEMP,
		.ebx = sensor & 0xff,
	पूर्ण;

	वापस i8k_smm(&regs) ? : regs.eax & 0xff;
पूर्ण

अटल पूर्णांक i8k_get_temp(पूर्णांक sensor)
अणु
	पूर्णांक temp = _i8k_get_temp(sensor);

	/*
	 * Someबार the temperature sensor वापसs 0x99, which is out of range.
	 * In this हाल we retry (once) beक्रमe वापसing an error.
	 # 1003655137 00000058 00005a4b
	 # 1003655138 00000099 00003a80 <--- 0x99 = 153 degrees
	 # 1003655139 00000054 00005c52
	 */
	अगर (temp == 0x99) अणु
		msleep(100);
		temp = _i8k_get_temp(sensor);
	पूर्ण
	/*
	 * Return -ENODATA क्रम all invalid temperatures.
	 *
	 * Known instances are the 0x99 value as seen above as well as
	 * 0xc1 (193), which may be वापसed when trying to पढ़ो the GPU
	 * temperature अगर the प्रणाली supports a GPU and it is currently
	 * turned off.
	 */
	अगर (temp > I8K_MAX_TEMP)
		वापस -ENODATA;

	वापस temp;
पूर्ण

अटल पूर्णांक i8k_get_dell_signature(पूर्णांक req_fn)
अणु
	काष्ठा smm_regs regs = अणु .eax = req_fn, पूर्ण;
	पूर्णांक rc;

	rc = i8k_smm(&regs);
	अगर (rc < 0)
		वापस rc;

	वापस regs.eax == 1145651527 && regs.edx == 1145392204 ? 0 : -1;
पूर्ण

#अगर IS_ENABLED(CONFIG_I8K)

/*
 * Read the Fn key status.
 */
अटल पूर्णांक i8k_get_fn_status(व्योम)
अणु
	काष्ठा smm_regs regs = अणु .eax = I8K_SMM_FN_STATUS, पूर्ण;
	पूर्णांक rc;

	rc = i8k_smm(&regs);
	अगर (rc < 0)
		वापस rc;

	चयन ((regs.eax >> I8K_FN_SHIFT) & I8K_FN_MASK) अणु
	हाल I8K_FN_UP:
		वापस I8K_VOL_UP;
	हाल I8K_FN_DOWN:
		वापस I8K_VOL_DOWN;
	हाल I8K_FN_MUTE:
		वापस I8K_VOL_MUTE;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

/*
 * Read the घातer status.
 */
अटल पूर्णांक i8k_get_घातer_status(व्योम)
अणु
	काष्ठा smm_regs regs = अणु .eax = I8K_SMM_POWER_STATUS, पूर्ण;
	पूर्णांक rc;

	rc = i8k_smm(&regs);
	अगर (rc < 0)
		वापस rc;

	वापस (regs.eax & 0xff) == I8K_POWER_AC ? I8K_AC : I8K_BATTERY;
पूर्ण

/*
 * Procfs पूर्णांकerface
 */

अटल पूर्णांक
i8k_ioctl_unlocked(काष्ठा file *fp, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	पूर्णांक val = 0;
	पूर्णांक speed;
	अचिन्हित अक्षर buff[16];
	पूर्णांक __user *argp = (पूर्णांक __user *)arg;

	अगर (!argp)
		वापस -EINVAL;

	चयन (cmd) अणु
	हाल I8K_BIOS_VERSION:
		अगर (!है_अंक(bios_version[0]) || !है_अंक(bios_version[1]) ||
		    !है_अंक(bios_version[2]))
			वापस -EINVAL;

		val = (bios_version[0] << 16) |
				(bios_version[1] << 8) | bios_version[2];
		अवरोध;

	हाल I8K_MACHINE_ID:
		अगर (restricted && !capable(CAP_SYS_ADMIN))
			वापस -EPERM;

		स_रखो(buff, 0, माप(buff));
		strlcpy(buff, bios_machineid, माप(buff));
		अवरोध;

	हाल I8K_FN_STATUS:
		val = i8k_get_fn_status();
		अवरोध;

	हाल I8K_POWER_STATUS:
		val = i8k_get_घातer_status();
		अवरोध;

	हाल I8K_GET_TEMP:
		val = i8k_get_temp(0);
		अवरोध;

	हाल I8K_GET_SPEED:
		अगर (copy_from_user(&val, argp, माप(पूर्णांक)))
			वापस -EFAULT;

		val = i8k_get_fan_speed(val);
		अवरोध;

	हाल I8K_GET_FAN:
		अगर (copy_from_user(&val, argp, माप(पूर्णांक)))
			वापस -EFAULT;

		val = i8k_get_fan_status(val);
		अवरोध;

	हाल I8K_SET_FAN:
		अगर (restricted && !capable(CAP_SYS_ADMIN))
			वापस -EPERM;

		अगर (copy_from_user(&val, argp, माप(पूर्णांक)))
			वापस -EFAULT;

		अगर (copy_from_user(&speed, argp + 1, माप(पूर्णांक)))
			वापस -EFAULT;

		val = i8k_set_fan(val, speed);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (val < 0)
		वापस val;

	चयन (cmd) अणु
	हाल I8K_BIOS_VERSION:
		अगर (copy_to_user(argp, &val, 4))
			वापस -EFAULT;

		अवरोध;
	हाल I8K_MACHINE_ID:
		अगर (copy_to_user(argp, buff, 16))
			वापस -EFAULT;

		अवरोध;
	शेष:
		अगर (copy_to_user(argp, &val, माप(पूर्णांक)))
			वापस -EFAULT;

		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल दीर्घ i8k_ioctl(काष्ठा file *fp, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	दीर्घ ret;

	mutex_lock(&i8k_mutex);
	ret = i8k_ioctl_unlocked(fp, cmd, arg);
	mutex_unlock(&i8k_mutex);

	वापस ret;
पूर्ण

/*
 * Prपूर्णांक the inक्रमmation क्रम /proc/i8k.
 */
अटल पूर्णांक i8k_proc_show(काष्ठा seq_file *seq, व्योम *offset)
अणु
	पूर्णांक fn_key, cpu_temp, ac_घातer;
	पूर्णांक left_fan, right_fan, left_speed, right_speed;

	cpu_temp	= i8k_get_temp(0);			/* 11100 तगs */
	left_fan	= i8k_get_fan_status(I8K_FAN_LEFT);	/*   580 तगs */
	right_fan	= i8k_get_fan_status(I8K_FAN_RIGHT);	/*   580 तगs */
	left_speed	= i8k_get_fan_speed(I8K_FAN_LEFT);	/*   580 तगs */
	right_speed	= i8k_get_fan_speed(I8K_FAN_RIGHT);	/*   580 तगs */
	fn_key		= i8k_get_fn_status();			/*   750 तगs */
	अगर (घातer_status)
		ac_घातer = i8k_get_घातer_status();		/* 14700 तगs */
	अन्यथा
		ac_घातer = -1;

	/*
	 * Info:
	 *
	 * 1)  Format version (this will change अगर क्रमmat changes)
	 * 2)  BIOS version
	 * 3)  BIOS machine ID
	 * 4)  Cpu temperature
	 * 5)  Left fan status
	 * 6)  Right fan status
	 * 7)  Left fan speed
	 * 8)  Right fan speed
	 * 9)  AC घातer
	 * 10) Fn Key status
	 */
	seq_म_लिखो(seq, "%s %s %s %d %d %d %d %d %d %d\n",
		   I8K_PROC_FMT,
		   bios_version,
		   (restricted && !capable(CAP_SYS_ADMIN)) ? "-1" : bios_machineid,
		   cpu_temp,
		   left_fan, right_fan, left_speed, right_speed,
		   ac_घातer, fn_key);

	वापस 0;
पूर्ण

अटल पूर्णांक i8k_खोलो_fs(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, i8k_proc_show, शून्य);
पूर्ण

अटल स्थिर काष्ठा proc_ops i8k_proc_ops = अणु
	.proc_खोलो	= i8k_खोलो_fs,
	.proc_पढ़ो	= seq_पढ़ो,
	.proc_lseek	= seq_lseek,
	.proc_release	= single_release,
	.proc_ioctl	= i8k_ioctl,
पूर्ण;

अटल व्योम __init i8k_init_procfs(व्योम)
अणु
	/* Register the proc entry */
	proc_create("i8k", 0, शून्य, &i8k_proc_ops);
पूर्ण

अटल व्योम __निकास i8k_निकास_procfs(व्योम)
अणु
	हटाओ_proc_entry("i8k", शून्य);
पूर्ण

#अन्यथा

अटल अंतरभूत व्योम __init i8k_init_procfs(व्योम)
अणु
पूर्ण

अटल अंतरभूत व्योम __निकास i8k_निकास_procfs(व्योम)
अणु
पूर्ण

#पूर्ण_अगर

/*
 * Hwmon पूर्णांकerface
 */

अटल sमाप_प्रकार i8k_hwmon_temp_label_show(काष्ठा device *dev,
					 काष्ठा device_attribute *devattr,
					 अक्षर *buf)
अणु
	अटल स्थिर अक्षर * स्थिर labels[] = अणु
		"CPU",
		"GPU",
		"SODIMM",
		"Other",
		"Ambient",
		"Other",
	पूर्ण;
	पूर्णांक index = to_sensor_dev_attr(devattr)->index;
	पूर्णांक type;

	type = i8k_get_temp_type(index);
	अगर (type < 0)
		वापस type;
	अगर (type >= ARRAY_SIZE(labels))
		type = ARRAY_SIZE(labels) - 1;
	वापस प्र_लिखो(buf, "%s\n", labels[type]);
पूर्ण

अटल sमाप_प्रकार i8k_hwmon_temp_show(काष्ठा device *dev,
				   काष्ठा device_attribute *devattr,
				   अक्षर *buf)
अणु
	पूर्णांक index = to_sensor_dev_attr(devattr)->index;
	पूर्णांक temp;

	temp = i8k_get_temp(index);
	अगर (temp < 0)
		वापस temp;
	वापस प्र_लिखो(buf, "%d\n", temp * 1000);
पूर्ण

अटल sमाप_प्रकार i8k_hwmon_fan_label_show(काष्ठा device *dev,
					काष्ठा device_attribute *devattr,
					अक्षर *buf)
अणु
	अटल स्थिर अक्षर * स्थिर labels[] = अणु
		"Processor Fan",
		"Motherboard Fan",
		"Video Fan",
		"Power Supply Fan",
		"Chipset Fan",
		"Other Fan",
	पूर्ण;
	पूर्णांक index = to_sensor_dev_attr(devattr)->index;
	bool करोck = false;
	पूर्णांक type;

	type = i8k_get_fan_type(index);
	अगर (type < 0)
		वापस type;

	अगर (type & 0x10) अणु
		करोck = true;
		type &= 0x0F;
	पूर्ण

	अगर (type >= ARRAY_SIZE(labels))
		type = (ARRAY_SIZE(labels) - 1);

	वापस प्र_लिखो(buf, "%s%s\n", (करोck ? "Docking " : ""), labels[type]);
पूर्ण

अटल sमाप_प्रकार i8k_hwmon_fan_show(काष्ठा device *dev,
				  काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	पूर्णांक index = to_sensor_dev_attr(devattr)->index;
	पूर्णांक fan_speed;

	fan_speed = i8k_get_fan_speed(index);
	अगर (fan_speed < 0)
		वापस fan_speed;
	वापस प्र_लिखो(buf, "%d\n", fan_speed);
पूर्ण

अटल sमाप_प्रकार i8k_hwmon_pwm_show(काष्ठा device *dev,
				  काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	पूर्णांक index = to_sensor_dev_attr(devattr)->index;
	पूर्णांक status;

	status = i8k_get_fan_status(index);
	अगर (status < 0)
		वापस -EIO;
	वापस प्र_लिखो(buf, "%d\n", clamp_val(status * i8k_pwm_mult, 0, 255));
पूर्ण

अटल sमाप_प्रकार i8k_hwmon_pwm_store(काष्ठा device *dev,
				   काष्ठा device_attribute *attr,
				   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक index = to_sensor_dev_attr(attr)->index;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;
	val = clamp_val(DIV_ROUND_CLOSEST(val, i8k_pwm_mult), 0, i8k_fan_max);

	mutex_lock(&i8k_mutex);
	err = i8k_set_fan(index, val);
	mutex_unlock(&i8k_mutex);

	वापस err < 0 ? -EIO : count;
पूर्ण

अटल sमाप_प्रकार i8k_hwmon_pwm_enable_store(काष्ठा device *dev,
					  काष्ठा device_attribute *attr,
					  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक err;
	bool enable;
	अचिन्हित दीर्घ val;

	अगर (!स्वतः_fan)
		वापस -ENODEV;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	अगर (val == 1)
		enable = false;
	अन्यथा अगर (val == 2)
		enable = true;
	अन्यथा
		वापस -EINVAL;

	mutex_lock(&i8k_mutex);
	err = i8k_enable_fan_स्वतः_mode(enable);
	mutex_unlock(&i8k_mutex);

	वापस err ? err : count;
पूर्ण

अटल SENSOR_DEVICE_ATTR_RO(temp1_input, i8k_hwmon_temp, 0);
अटल SENSOR_DEVICE_ATTR_RO(temp1_label, i8k_hwmon_temp_label, 0);
अटल SENSOR_DEVICE_ATTR_RO(temp2_input, i8k_hwmon_temp, 1);
अटल SENSOR_DEVICE_ATTR_RO(temp2_label, i8k_hwmon_temp_label, 1);
अटल SENSOR_DEVICE_ATTR_RO(temp3_input, i8k_hwmon_temp, 2);
अटल SENSOR_DEVICE_ATTR_RO(temp3_label, i8k_hwmon_temp_label, 2);
अटल SENSOR_DEVICE_ATTR_RO(temp4_input, i8k_hwmon_temp, 3);
अटल SENSOR_DEVICE_ATTR_RO(temp4_label, i8k_hwmon_temp_label, 3);
अटल SENSOR_DEVICE_ATTR_RO(temp5_input, i8k_hwmon_temp, 4);
अटल SENSOR_DEVICE_ATTR_RO(temp5_label, i8k_hwmon_temp_label, 4);
अटल SENSOR_DEVICE_ATTR_RO(temp6_input, i8k_hwmon_temp, 5);
अटल SENSOR_DEVICE_ATTR_RO(temp6_label, i8k_hwmon_temp_label, 5);
अटल SENSOR_DEVICE_ATTR_RO(temp7_input, i8k_hwmon_temp, 6);
अटल SENSOR_DEVICE_ATTR_RO(temp7_label, i8k_hwmon_temp_label, 6);
अटल SENSOR_DEVICE_ATTR_RO(temp8_input, i8k_hwmon_temp, 7);
अटल SENSOR_DEVICE_ATTR_RO(temp8_label, i8k_hwmon_temp_label, 7);
अटल SENSOR_DEVICE_ATTR_RO(temp9_input, i8k_hwmon_temp, 8);
अटल SENSOR_DEVICE_ATTR_RO(temp9_label, i8k_hwmon_temp_label, 8);
अटल SENSOR_DEVICE_ATTR_RO(temp10_input, i8k_hwmon_temp, 9);
अटल SENSOR_DEVICE_ATTR_RO(temp10_label, i8k_hwmon_temp_label, 9);
अटल SENSOR_DEVICE_ATTR_RO(fan1_input, i8k_hwmon_fan, 0);
अटल SENSOR_DEVICE_ATTR_RO(fan1_label, i8k_hwmon_fan_label, 0);
अटल SENSOR_DEVICE_ATTR_RW(pwm1, i8k_hwmon_pwm, 0);
अटल SENSOR_DEVICE_ATTR_WO(pwm1_enable, i8k_hwmon_pwm_enable, 0);
अटल SENSOR_DEVICE_ATTR_RO(fan2_input, i8k_hwmon_fan, 1);
अटल SENSOR_DEVICE_ATTR_RO(fan2_label, i8k_hwmon_fan_label, 1);
अटल SENSOR_DEVICE_ATTR_RW(pwm2, i8k_hwmon_pwm, 1);
अटल SENSOR_DEVICE_ATTR_RO(fan3_input, i8k_hwmon_fan, 2);
अटल SENSOR_DEVICE_ATTR_RO(fan3_label, i8k_hwmon_fan_label, 2);
अटल SENSOR_DEVICE_ATTR_RW(pwm3, i8k_hwmon_pwm, 2);

अटल काष्ठा attribute *i8k_attrs[] = अणु
	&sensor_dev_attr_temp1_input.dev_attr.attr,	/* 0 */
	&sensor_dev_attr_temp1_label.dev_attr.attr,	/* 1 */
	&sensor_dev_attr_temp2_input.dev_attr.attr,	/* 2 */
	&sensor_dev_attr_temp2_label.dev_attr.attr,	/* 3 */
	&sensor_dev_attr_temp3_input.dev_attr.attr,	/* 4 */
	&sensor_dev_attr_temp3_label.dev_attr.attr,	/* 5 */
	&sensor_dev_attr_temp4_input.dev_attr.attr,	/* 6 */
	&sensor_dev_attr_temp4_label.dev_attr.attr,	/* 7 */
	&sensor_dev_attr_temp5_input.dev_attr.attr,	/* 8 */
	&sensor_dev_attr_temp5_label.dev_attr.attr,	/* 9 */
	&sensor_dev_attr_temp6_input.dev_attr.attr,	/* 10 */
	&sensor_dev_attr_temp6_label.dev_attr.attr,	/* 11 */
	&sensor_dev_attr_temp7_input.dev_attr.attr,	/* 12 */
	&sensor_dev_attr_temp7_label.dev_attr.attr,	/* 13 */
	&sensor_dev_attr_temp8_input.dev_attr.attr,	/* 14 */
	&sensor_dev_attr_temp8_label.dev_attr.attr,	/* 15 */
	&sensor_dev_attr_temp9_input.dev_attr.attr,	/* 16 */
	&sensor_dev_attr_temp9_label.dev_attr.attr,	/* 17 */
	&sensor_dev_attr_temp10_input.dev_attr.attr,	/* 18 */
	&sensor_dev_attr_temp10_label.dev_attr.attr,	/* 19 */
	&sensor_dev_attr_fan1_input.dev_attr.attr,	/* 20 */
	&sensor_dev_attr_fan1_label.dev_attr.attr,	/* 21 */
	&sensor_dev_attr_pwm1.dev_attr.attr,		/* 22 */
	&sensor_dev_attr_pwm1_enable.dev_attr.attr,	/* 23 */
	&sensor_dev_attr_fan2_input.dev_attr.attr,	/* 24 */
	&sensor_dev_attr_fan2_label.dev_attr.attr,	/* 25 */
	&sensor_dev_attr_pwm2.dev_attr.attr,		/* 26 */
	&sensor_dev_attr_fan3_input.dev_attr.attr,	/* 27 */
	&sensor_dev_attr_fan3_label.dev_attr.attr,	/* 28 */
	&sensor_dev_attr_pwm3.dev_attr.attr,		/* 29 */
	शून्य
पूर्ण;

अटल umode_t i8k_is_visible(काष्ठा kobject *kobj, काष्ठा attribute *attr,
			      पूर्णांक index)
अणु
	अगर (disallow_fan_support && index >= 20)
		वापस 0;
	अगर (disallow_fan_type_call &&
	    (index == 21 || index == 25 || index == 28))
		वापस 0;
	अगर (index >= 0 && index <= 1 &&
	    !(i8k_hwmon_flags & I8K_HWMON_HAVE_TEMP1))
		वापस 0;
	अगर (index >= 2 && index <= 3 &&
	    !(i8k_hwmon_flags & I8K_HWMON_HAVE_TEMP2))
		वापस 0;
	अगर (index >= 4 && index <= 5 &&
	    !(i8k_hwmon_flags & I8K_HWMON_HAVE_TEMP3))
		वापस 0;
	अगर (index >= 6 && index <= 7 &&
	    !(i8k_hwmon_flags & I8K_HWMON_HAVE_TEMP4))
		वापस 0;
	अगर (index >= 8 && index <= 9 &&
	    !(i8k_hwmon_flags & I8K_HWMON_HAVE_TEMP5))
		वापस 0;
	अगर (index >= 10 && index <= 11 &&
	    !(i8k_hwmon_flags & I8K_HWMON_HAVE_TEMP6))
		वापस 0;
	अगर (index >= 12 && index <= 13 &&
	    !(i8k_hwmon_flags & I8K_HWMON_HAVE_TEMP7))
		वापस 0;
	अगर (index >= 14 && index <= 15 &&
	    !(i8k_hwmon_flags & I8K_HWMON_HAVE_TEMP8))
		वापस 0;
	अगर (index >= 16 && index <= 17 &&
	    !(i8k_hwmon_flags & I8K_HWMON_HAVE_TEMP9))
		वापस 0;
	अगर (index >= 18 && index <= 19 &&
	    !(i8k_hwmon_flags & I8K_HWMON_HAVE_TEMP10))
		वापस 0;

	अगर (index >= 20 && index <= 23 &&
	    !(i8k_hwmon_flags & I8K_HWMON_HAVE_FAN1))
		वापस 0;
	अगर (index >= 24 && index <= 26 &&
	    !(i8k_hwmon_flags & I8K_HWMON_HAVE_FAN2))
		वापस 0;
	अगर (index >= 27 && index <= 29 &&
	    !(i8k_hwmon_flags & I8K_HWMON_HAVE_FAN3))
		वापस 0;

	अगर (index == 23 && !स्वतः_fan)
		वापस 0;

	वापस attr->mode;
पूर्ण

अटल स्थिर काष्ठा attribute_group i8k_group = अणु
	.attrs = i8k_attrs,
	.is_visible = i8k_is_visible,
पूर्ण;
__ATTRIBUTE_GROUPS(i8k);

अटल पूर्णांक __init i8k_init_hwmon(व्योम)
अणु
	पूर्णांक err;

	i8k_hwmon_flags = 0;

	/* CPU temperature attributes, अगर temperature type is OK */
	err = i8k_get_temp_type(0);
	अगर (err >= 0)
		i8k_hwmon_flags |= I8K_HWMON_HAVE_TEMP1;
	/* check क्रम additional temperature sensors */
	err = i8k_get_temp_type(1);
	अगर (err >= 0)
		i8k_hwmon_flags |= I8K_HWMON_HAVE_TEMP2;
	err = i8k_get_temp_type(2);
	अगर (err >= 0)
		i8k_hwmon_flags |= I8K_HWMON_HAVE_TEMP3;
	err = i8k_get_temp_type(3);
	अगर (err >= 0)
		i8k_hwmon_flags |= I8K_HWMON_HAVE_TEMP4;
	err = i8k_get_temp_type(4);
	अगर (err >= 0)
		i8k_hwmon_flags |= I8K_HWMON_HAVE_TEMP5;
	err = i8k_get_temp_type(5);
	अगर (err >= 0)
		i8k_hwmon_flags |= I8K_HWMON_HAVE_TEMP6;
	err = i8k_get_temp_type(6);
	अगर (err >= 0)
		i8k_hwmon_flags |= I8K_HWMON_HAVE_TEMP7;
	err = i8k_get_temp_type(7);
	अगर (err >= 0)
		i8k_hwmon_flags |= I8K_HWMON_HAVE_TEMP8;
	err = i8k_get_temp_type(8);
	अगर (err >= 0)
		i8k_hwmon_flags |= I8K_HWMON_HAVE_TEMP9;
	err = i8k_get_temp_type(9);
	अगर (err >= 0)
		i8k_hwmon_flags |= I8K_HWMON_HAVE_TEMP10;

	/* First fan attributes, अगर fan status or type is OK */
	err = i8k_get_fan_status(0);
	अगर (err < 0)
		err = i8k_get_fan_type(0);
	अगर (err >= 0)
		i8k_hwmon_flags |= I8K_HWMON_HAVE_FAN1;

	/* Second fan attributes, अगर fan status or type is OK */
	err = i8k_get_fan_status(1);
	अगर (err < 0)
		err = i8k_get_fan_type(1);
	अगर (err >= 0)
		i8k_hwmon_flags |= I8K_HWMON_HAVE_FAN2;

	/* Third fan attributes, अगर fan status or type is OK */
	err = i8k_get_fan_status(2);
	अगर (err < 0)
		err = i8k_get_fan_type(2);
	अगर (err >= 0)
		i8k_hwmon_flags |= I8K_HWMON_HAVE_FAN3;

	i8k_hwmon_dev = hwmon_device_रेजिस्टर_with_groups(शून्य, "dell_smm",
							  शून्य, i8k_groups);
	अगर (IS_ERR(i8k_hwmon_dev)) अणु
		err = PTR_ERR(i8k_hwmon_dev);
		i8k_hwmon_dev = शून्य;
		pr_err("hwmon registration failed (%d)\n", err);
		वापस err;
	पूर्ण
	वापस 0;
पूर्ण

काष्ठा i8k_config_data अणु
	uपूर्णांक fan_mult;
	uपूर्णांक fan_max;
पूर्ण;

क्रमागत i8k_configs अणु
	DELL_LATITUDE_D520,
	DELL_PRECISION_490,
	DELL_STUDIO,
	DELL_XPS,
पूर्ण;

अटल स्थिर काष्ठा i8k_config_data i8k_config_data[] = अणु
	[DELL_LATITUDE_D520] = अणु
		.fan_mult = 1,
		.fan_max = I8K_FAN_TURBO,
	पूर्ण,
	[DELL_PRECISION_490] = अणु
		.fan_mult = 1,
		.fan_max = I8K_FAN_TURBO,
	पूर्ण,
	[DELL_STUDIO] = अणु
		.fan_mult = 1,
		.fan_max = I8K_FAN_HIGH,
	पूर्ण,
	[DELL_XPS] = अणु
		.fan_mult = 1,
		.fan_max = I8K_FAN_HIGH,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा dmi_प्रणाली_id i8k_dmi_table[] __initस्थिर = अणु
	अणु
		.ident = "Dell Inspiron",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Computer"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Inspiron"),
		पूर्ण,
	पूर्ण,
	अणु
		.ident = "Dell Latitude",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Computer"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Latitude"),
		पूर्ण,
	पूर्ण,
	अणु
		.ident = "Dell Inspiron 2",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "Inspiron"),
		पूर्ण,
	पूर्ण,
	अणु
		.ident = "Dell Latitude D520",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "Latitude D520"),
		पूर्ण,
		.driver_data = (व्योम *)&i8k_config_data[DELL_LATITUDE_D520],
	पूर्ण,
	अणु
		.ident = "Dell Latitude 2",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "Latitude"),
		पूर्ण,
	पूर्ण,
	अणु	/* UK Inspiron 6400  */
		.ident = "Dell Inspiron 3",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "MM061"),
		पूर्ण,
	पूर्ण,
	अणु
		.ident = "Dell Inspiron 3",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "MP061"),
		पूर्ण,
	पूर्ण,
	अणु
		.ident = "Dell Precision 490",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME,
				  "Precision WorkStation 490"),
		पूर्ण,
		.driver_data = (व्योम *)&i8k_config_data[DELL_PRECISION_490],
	पूर्ण,
	अणु
		.ident = "Dell Precision",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "Precision"),
		पूर्ण,
	पूर्ण,
	अणु
		.ident = "Dell Vostro",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "Vostro"),
		पूर्ण,
	पूर्ण,
	अणु
		.ident = "Dell Studio",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "Studio"),
		पूर्ण,
		.driver_data = (व्योम *)&i8k_config_data[DELL_STUDIO],
	पूर्ण,
	अणु
		.ident = "Dell XPS M140",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "MXC051"),
		पूर्ण,
		.driver_data = (व्योम *)&i8k_config_data[DELL_XPS],
	पूर्ण,
	अणु
		.ident = "Dell XPS",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "XPS"),
		पूर्ण,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(dmi, i8k_dmi_table);

/*
 * On some machines once I8K_SMM_GET_FAN_TYPE is issued then CPU fan speed
 * अक्रमomly going up and करोwn due to bug in Dell SMM or BIOS. Here is blacklist
 * of affected Dell machines क्रम which we disallow I8K_SMM_GET_FAN_TYPE call.
 * See bug: https://bugzilla.kernel.org/show_bug.cgi?id=100121
 */
अटल स्थिर काष्ठा dmi_प्रणाली_id i8k_blacklist_fan_type_dmi_table[] __initस्थिर = अणु
	अणु
		.ident = "Dell Studio XPS 8000",
		.matches = अणु
			DMI_EXACT_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "Studio XPS 8000"),
		पूर्ण,
	पूर्ण,
	अणु
		.ident = "Dell Studio XPS 8100",
		.matches = अणु
			DMI_EXACT_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "Studio XPS 8100"),
		पूर्ण,
	पूर्ण,
	अणु
		.ident = "Dell Inspiron 580",
		.matches = अणु
			DMI_EXACT_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "Inspiron 580 "),
		पूर्ण,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

/*
 * On some machines all fan related SMM functions implemented by Dell BIOS
 * firmware मुक्तze kernel क्रम about 500ms. Until Dell fixes these problems fan
 * support क्रम affected blacklisted Dell machines stay disabled.
 * See bug: https://bugzilla.kernel.org/show_bug.cgi?id=195751
 */
अटल काष्ठा dmi_प्रणाली_id i8k_blacklist_fan_support_dmi_table[] __initdata = अणु
	अणु
		.ident = "Dell Inspiron 7720",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "Inspiron 7720"),
		पूर्ण,
	पूर्ण,
	अणु
		.ident = "Dell Vostro 3360",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "Vostro 3360"),
		पूर्ण,
	पूर्ण,
	अणु
		.ident = "Dell XPS13 9333",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "XPS13 9333"),
		पूर्ण,
	पूर्ण,
	अणु
		.ident = "Dell XPS 15 L502X",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "Dell System XPS L502X"),
		पूर्ण,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

काष्ठा i8k_fan_control_data अणु
	अचिन्हित पूर्णांक manual_fan;
	अचिन्हित पूर्णांक स्वतः_fan;
पूर्ण;

क्रमागत i8k_fan_controls अणु
	I8K_FAN_34A3_35A3,
पूर्ण;

अटल स्थिर काष्ठा i8k_fan_control_data i8k_fan_control_data[] = अणु
	[I8K_FAN_34A3_35A3] = अणु
		.manual_fan = 0x34a3,
		.स्वतः_fan = 0x35a3,
	पूर्ण,
पूर्ण;

अटल काष्ठा dmi_प्रणाली_id i8k_whitelist_fan_control[] __initdata = अणु
	अणु
		.ident = "Dell Precision 5530",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "Precision 5530"),
		पूर्ण,
		.driver_data = (व्योम *)&i8k_fan_control_data[I8K_FAN_34A3_35A3],
	पूर्ण,
	अणु
		.ident = "Dell Latitude 5480",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "Latitude 5480"),
		पूर्ण,
		.driver_data = (व्योम *)&i8k_fan_control_data[I8K_FAN_34A3_35A3],
	पूर्ण,
	अणु
		.ident = "Dell Latitude E6440",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "Latitude E6440"),
		पूर्ण,
		.driver_data = (व्योम *)&i8k_fan_control_data[I8K_FAN_34A3_35A3],
	पूर्ण,
	अणु
		.ident = "Dell Latitude E7440",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "Latitude E7440"),
		पूर्ण,
		.driver_data = (व्योम *)&i8k_fan_control_data[I8K_FAN_34A3_35A3],
	पूर्ण,
	अणु पूर्ण
पूर्ण;

/*
 * Probe क्रम the presence of a supported laptop.
 */
अटल पूर्णांक __init i8k_probe(व्योम)
अणु
	स्थिर काष्ठा dmi_प्रणाली_id *id, *fan_control;
	पूर्णांक fan, ret;

	/*
	 * Get DMI inक्रमmation
	 */
	अगर (!dmi_check_प्रणाली(i8k_dmi_table)) अणु
		अगर (!ignore_dmi && !क्रमce)
			वापस -ENODEV;

		pr_info("not running on a supported Dell system.\n");
		pr_info("vendor=%s, model=%s, version=%s\n",
			i8k_get_dmi_data(DMI_SYS_VENDOR),
			i8k_get_dmi_data(DMI_PRODUCT_NAME),
			i8k_get_dmi_data(DMI_BIOS_VERSION));
	पूर्ण

	अगर (dmi_check_प्रणाली(i8k_blacklist_fan_support_dmi_table)) अणु
		pr_warn("broken Dell BIOS detected, disallow fan support\n");
		अगर (!क्रमce)
			disallow_fan_support = true;
	पूर्ण

	अगर (dmi_check_प्रणाली(i8k_blacklist_fan_type_dmi_table)) अणु
		pr_warn("broken Dell BIOS detected, disallow fan type call\n");
		अगर (!क्रमce)
			disallow_fan_type_call = true;
	पूर्ण

	strlcpy(bios_version, i8k_get_dmi_data(DMI_BIOS_VERSION),
		माप(bios_version));
	strlcpy(bios_machineid, i8k_get_dmi_data(DMI_PRODUCT_SERIAL),
		माप(bios_machineid));

	/*
	 * Get SMM Dell signature
	 */
	अगर (i8k_get_dell_signature(I8K_SMM_GET_DELL_SIG1) &&
	    i8k_get_dell_signature(I8K_SMM_GET_DELL_SIG2)) अणु
		pr_err("unable to get SMM Dell signature\n");
		अगर (!क्रमce)
			वापस -ENODEV;
	पूर्ण

	/*
	 * Set fan multiplier and maximal fan speed from dmi config
	 * Values specअगरied in module parameters override values from dmi
	 */
	id = dmi_first_match(i8k_dmi_table);
	अगर (id && id->driver_data) अणु
		स्थिर काष्ठा i8k_config_data *conf = id->driver_data;
		अगर (!fan_mult && conf->fan_mult)
			fan_mult = conf->fan_mult;
		अगर (!fan_max && conf->fan_max)
			fan_max = conf->fan_max;
	पूर्ण

	i8k_fan_max = fan_max ? : I8K_FAN_HIGH;	/* Must not be 0 */
	i8k_pwm_mult = DIV_ROUND_UP(255, i8k_fan_max);

	fan_control = dmi_first_match(i8k_whitelist_fan_control);
	अगर (fan_control && fan_control->driver_data) अणु
		स्थिर काष्ठा i8k_fan_control_data *data = fan_control->driver_data;

		manual_fan = data->manual_fan;
		स्वतः_fan = data->स्वतः_fan;
		pr_info("enabling support for setting automatic/manual fan control\n");
	पूर्ण

	अगर (!fan_mult) अणु
		/*
		 * Autodetect fan multiplier based on nominal rpm
		 * If fan reports rpm value too high then set multiplier to 1
		 */
		क्रम (fan = 0; fan < 2; ++fan) अणु
			ret = i8k_get_fan_nominal_speed(fan, i8k_fan_max);
			अगर (ret < 0)
				जारी;
			अगर (ret > I8K_FAN_MAX_RPM)
				i8k_fan_mult = 1;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Fan multiplier was specअगरied in module param or in dmi */
		i8k_fan_mult = fan_mult;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __init i8k_init(व्योम)
अणु
	पूर्णांक err;

	/* Are we running on an supported laptop? */
	अगर (i8k_probe())
		वापस -ENODEV;

	err = i8k_init_hwmon();
	अगर (err)
		वापस err;

	i8k_init_procfs();
	वापस 0;
पूर्ण

अटल व्योम __निकास i8k_निकास(व्योम)
अणु
	hwmon_device_unरेजिस्टर(i8k_hwmon_dev);
	i8k_निकास_procfs();
पूर्ण

module_init(i8k_init);
module_निकास(i8k_निकास);
