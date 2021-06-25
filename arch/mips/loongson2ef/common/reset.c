<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 * Copyright (C) 2007 Lemote, Inc. & Institute of Computing Technology
 * Author: Fuxin Zhang, zhangfx@lemote.com
 * Copyright (C) 2009 Lemote, Inc.
 * Author: Zhangjin Wu, wuzhangjin@gmail.com
 */
#समावेश <linux/init.h>
#समावेश <linux/pm.h>

#समावेश <यंत्र/idle.h>
#समावेश <यंत्र/reboot.h>

#समावेश <loongson.h>

अटल अंतरभूत व्योम loongson_reboot(व्योम)
अणु
#अगर_अघोषित CONFIG_CPU_JUMP_WORKAROUNDS
	((व्योम (*)(व्योम))ioremap(LOONGSON_BOOT_BASE, 4)) ();
#अन्यथा
	व्योम (*func)(व्योम);

	func = (व्योम *)ioremap(LOONGSON_BOOT_BASE, 4);

	__यंत्र__ __अस्थिर__(
	"	.set	noat						\n"
	"	jr	%[func]						\n"
	"	.set	at						\n"
	: /* No outमाला_दो */
	: [func] "r" (func));
#पूर्ण_अगर
पूर्ण

अटल व्योम loongson_restart(अक्षर *command)
अणु
	/* करो preparation क्रम reboot */
	mach_prepare_reboot();

	/* reboot via jumping to boot base address */
	loongson_reboot();
पूर्ण

अटल व्योम loongson_घातeroff(व्योम)
अणु
	mach_prepare_shutकरोwn();

	/*
	 * It needs a रुको loop here, but mips/kernel/reset.c alपढ़ोy calls
	 * a generic delay loop, machine_hang(), so simply वापस.
	 */
	वापस;
पूर्ण

अटल व्योम loongson_halt(व्योम)
अणु
	pr_notice("\n\n** You can safely turn off the power now **\n\n");
	जबतक (1) अणु
		अगर (cpu_रुको)
			cpu_रुको();
	पूर्ण
पूर्ण

अटल पूर्णांक __init mips_reboot_setup(व्योम)
अणु
	_machine_restart = loongson_restart;
	_machine_halt = loongson_halt;
	pm_घातer_off = loongson_घातeroff;

	वापस 0;
पूर्ण

arch_initcall(mips_reboot_setup);
