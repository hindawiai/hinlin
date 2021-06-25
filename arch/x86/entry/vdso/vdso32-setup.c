<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * (C) Copyright 2002 Linus Torvalds
 * Portions based on the vdso-अक्रमomization code from exec-shield:
 * Copyright(C) 2005-2006, Red Hat, Inc., Ingo Molnar
 *
 * This file contains the needed initializations to support sysenter.
 */

#समावेश <linux/init.h>
#समावेश <linux/smp.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm_types.h>
#समावेश <linux/elf.h>

#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/vdso.h>

#अगर_घोषित CONFIG_COMPAT_VDSO
#घोषणा VDSO_DEFAULT	0
#अन्यथा
#घोषणा VDSO_DEFAULT	1
#पूर्ण_अगर

/*
 * Should the kernel map a VDSO page पूर्णांकo processes and pass its
 * address करोwn to glibc upon exec()?
 */
अचिन्हित पूर्णांक __पढ़ो_mostly vdso32_enabled = VDSO_DEFAULT;

अटल पूर्णांक __init vdso32_setup(अक्षर *s)
अणु
	vdso32_enabled = simple_म_से_अदीर्घ(s, शून्य, 0);

	अगर (vdso32_enabled > 1) अणु
		pr_warn("vdso32 values other than 0 and 1 are no longer allowed; vdso disabled\n");
		vdso32_enabled = 0;
	पूर्ण

	वापस 1;
पूर्ण

/*
 * For consistency, the argument vdso32=[012] affects the 32-bit vDSO
 * behavior on both 64-bit and 32-bit kernels.
 * On 32-bit kernels, vdso=[012] means the same thing.
 */
__setup("vdso32=", vdso32_setup);

#अगर_घोषित CONFIG_X86_32
__setup_param("vdso=", vdso_setup, vdso32_setup, 0);
#पूर्ण_अगर

पूर्णांक __init sysenter_setup(व्योम)
अणु
	init_vdso_image(&vdso_image_32);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_X86_64

subsys_initcall(sysenter_setup);

#अगर_घोषित CONFIG_SYSCTL
/* Register vsyscall32 पूर्णांकo the ABI table */
#समावेश <linux/sysctl.h>

अटल काष्ठा ctl_table abi_table2[] = अणु
	अणु
		.procname	= "vsyscall32",
		.data		= &vdso32_enabled,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ZERO,
		.extra2		= SYSCTL_ONE,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा ctl_table abi_root_table2[] = अणु
	अणु
		.procname = "abi",
		.mode = 0555,
		.child = abi_table2
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल __init पूर्णांक ia32_binfmt_init(व्योम)
अणु
	रेजिस्टर_sysctl_table(abi_root_table2);
	वापस 0;
पूर्ण
__initcall(ia32_binfmt_init);
#पूर्ण_अगर /* CONFIG_SYSCTL */

#पूर्ण_अगर	/* CONFIG_X86_64 */
