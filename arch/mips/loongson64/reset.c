<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 * Copyright (C) 2007 Lemote, Inc. & Institute of Computing Technology
 * Author: Fuxin Zhang, zhangfx@lemote.com
 * Copyright (C) 2009 Lemote, Inc.
 * Author: Zhangjin Wu, wuzhangjin@gmail.com
 */
#समावेश <linux/cpu.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/kexec.h>
#समावेश <linux/pm.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/idle.h>
#समावेश <यंत्र/reboot.h>

#समावेश <loongson.h>
#समावेश <boot_param.h>

अटल व्योम loongson_restart(अक्षर *command)
अणु

	व्योम (*fw_restart)(व्योम) = (व्योम *)loongson_sysconf.restart_addr;

	fw_restart();
	जबतक (1) अणु
		अगर (cpu_रुको)
			cpu_रुको();
	पूर्ण
पूर्ण

अटल व्योम loongson_घातeroff(व्योम)
अणु
	व्योम (*fw_घातeroff)(व्योम) = (व्योम *)loongson_sysconf.घातeroff_addr;

	fw_घातeroff();
	जबतक (1) अणु
		अगर (cpu_रुको)
			cpu_रुको();
	पूर्ण
पूर्ण

अटल व्योम loongson_halt(व्योम)
अणु
	pr_notice("\n\n** You can safely turn off the power now **\n\n");
	जबतक (1) अणु
		अगर (cpu_रुको)
			cpu_रुको();
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_KEXEC

/* 0X80000000~0X80200000 is safe */
#घोषणा MAX_ARGS	64
#घोषणा KEXEC_CTRL_CODE	0xFFFFFFFF80100000UL
#घोषणा KEXEC_ARGV_ADDR	0xFFFFFFFF80108000UL
#घोषणा KEXEC_ARGV_SIZE	COMMAND_LINE_SIZE
#घोषणा KEXEC_ENVP_SIZE	4800

अटल पूर्णांक kexec_argc;
अटल पूर्णांक kdump_argc;
अटल व्योम *kexec_argv;
अटल व्योम *kdump_argv;
अटल व्योम *kexec_envp;

अटल पूर्णांक loongson_kexec_prepare(काष्ठा kimage *image)
अणु
	पूर्णांक i, argc = 0;
	अचिन्हित पूर्णांक *argv;
	अक्षर *str, *ptr, *bootloader = "kexec";

	/* argv at offset 0, argv[] at offset KEXEC_ARGV_SIZE/2 */
	अगर (image->type == KEXEC_TYPE_DEFAULT)
		argv = (अचिन्हित पूर्णांक *)kexec_argv;
	अन्यथा
		argv = (अचिन्हित पूर्णांक *)kdump_argv;

	argv[argc++] = (अचिन्हित पूर्णांक)(KEXEC_ARGV_ADDR + KEXEC_ARGV_SIZE/2);

	क्रम (i = 0; i < image->nr_segments; i++) अणु
		अगर (!म_भेदन(bootloader, (अक्षर *)image->segment[i].buf,
				म_माप(bootloader))) अणु
			/*
			 * convert command line string to array
			 * of parameters (as bootloader करोes).
			 */
			पूर्णांक offt;
			str = (अक्षर *)argv + KEXEC_ARGV_SIZE/2;
			स_नकल(str, image->segment[i].buf, KEXEC_ARGV_SIZE/2);
			ptr = म_अक्षर(str, ' ');

			जबतक (ptr && (argc < MAX_ARGS)) अणु
				*ptr = '\0';
				अगर (ptr[1] != ' ') अणु
					offt = (पूर्णांक)(ptr - str + 1);
					argv[argc] = KEXEC_ARGV_ADDR + KEXEC_ARGV_SIZE/2 + offt;
					argc++;
				पूर्ण
				ptr = म_अक्षर(ptr + 1, ' ');
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (image->type == KEXEC_TYPE_DEFAULT)
		kexec_argc = argc;
	अन्यथा
		kdump_argc = argc;

	/* kexec/kdump need a safe page to save reboot_code_buffer */
	image->control_code_page = virt_to_page((व्योम *)KEXEC_CTRL_CODE);

	वापस 0;
पूर्ण

अटल व्योम loongson_kexec_shutकरोwn(व्योम)
अणु
#अगर_घोषित CONFIG_SMP
	पूर्णांक cpu;

	/* All CPUs go to reboot_code_buffer */
	क्रम_each_possible_cpu(cpu)
		अगर (!cpu_online(cpu))
			cpu_device_up(get_cpu_device(cpu));
#पूर्ण_अगर
	kexec_args[0] = kexec_argc;
	kexec_args[1] = fw_arg1;
	kexec_args[2] = fw_arg2;
	secondary_kexec_args[0] = TO_UNCAC(0x3ff01000);
	स_नकल((व्योम *)fw_arg1, kexec_argv, KEXEC_ARGV_SIZE);
	स_नकल((व्योम *)fw_arg2, kexec_envp, KEXEC_ENVP_SIZE);
पूर्ण

अटल व्योम loongson_crash_shutकरोwn(काष्ठा pt_regs *regs)
अणु
	शेष_machine_crash_shutकरोwn(regs);
	kexec_args[0] = kdump_argc;
	kexec_args[1] = fw_arg1;
	kexec_args[2] = fw_arg2;
	secondary_kexec_args[0] = TO_UNCAC(0x3ff01000);
	स_नकल((व्योम *)fw_arg1, kdump_argv, KEXEC_ARGV_SIZE);
	स_नकल((व्योम *)fw_arg2, kexec_envp, KEXEC_ENVP_SIZE);
पूर्ण

#पूर्ण_अगर

अटल पूर्णांक __init mips_reboot_setup(व्योम)
अणु
	_machine_restart = loongson_restart;
	_machine_halt = loongson_halt;
	pm_घातer_off = loongson_घातeroff;

#अगर_घोषित CONFIG_KEXEC
	kexec_argv = kदो_स्मृति(KEXEC_ARGV_SIZE, GFP_KERNEL);
	kdump_argv = kदो_स्मृति(KEXEC_ARGV_SIZE, GFP_KERNEL);
	kexec_envp = kदो_स्मृति(KEXEC_ENVP_SIZE, GFP_KERNEL);
	fw_arg1 = KEXEC_ARGV_ADDR;
	स_नकल(kexec_envp, (व्योम *)fw_arg2, KEXEC_ENVP_SIZE);

	_machine_kexec_prepare = loongson_kexec_prepare;
	_machine_kexec_shutकरोwn = loongson_kexec_shutकरोwn;
	_machine_crash_shutकरोwn = loongson_crash_shutकरोwn;
#पूर्ण_अगर

	वापस 0;
पूर्ण

arch_initcall(mips_reboot_setup);
