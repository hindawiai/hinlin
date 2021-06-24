<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Trusted Foundations support क्रम ARM CPUs
 *
 * Copyright (c) 2013, NVIDIA Corporation.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/of.h>

#समावेश <linux/firmware/trusted_foundations.h>

#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/hardware/cache-l2x0.h>
#समावेश <यंत्र/outercache.h>

#घोषणा TF_CACHE_MAINT		0xfffff100

#घोषणा TF_CACHE_ENABLE		1
#घोषणा TF_CACHE_DISABLE	2
#घोषणा TF_CACHE_REENABLE	4

#घोषणा TF_SET_CPU_BOOT_ADDR_SMC 0xfffff200

#घोषणा TF_CPU_PM		0xfffffffc
#घोषणा TF_CPU_PM_S3		0xffffffe3
#घोषणा TF_CPU_PM_S2		0xffffffe6
#घोषणा TF_CPU_PM_S2_NO_MC_CLK	0xffffffe5
#घोषणा TF_CPU_PM_S1		0xffffffe4
#घोषणा TF_CPU_PM_S1_NOFLUSH_L2	0xffffffe7

अटल अचिन्हित दीर्घ tf_idle_mode = TF_PM_MODE_NONE;
अटल अचिन्हित दीर्घ cpu_boot_addr;

अटल व्योम tf_generic_smc(u32 type, u32 arg1, u32 arg2)
अणु
	रेजिस्टर u32 r0 यंत्र("r0") = type;
	रेजिस्टर u32 r1 यंत्र("r1") = arg1;
	रेजिस्टर u32 r2 यंत्र("r2") = arg2;

	यंत्र अस्थिर(
		".arch_extension	sec\n\t"
		"stmfd	sp!, {r4 - r11}\n\t"
		__यंत्रeq("%0", "r0")
		__यंत्रeq("%1", "r1")
		__यंत्रeq("%2", "r2")
		"mov	r3, #0\n\t"
		"mov	r4, #0\n\t"
		"smc	#0\n\t"
		"ldmfd	sp!, {r4 - r11}\n\t"
		:
		: "r" (r0), "r" (r1), "r" (r2)
		: "memory", "r3", "r12", "lr");
पूर्ण

अटल पूर्णांक tf_set_cpu_boot_addr(पूर्णांक cpu, अचिन्हित दीर्घ boot_addr)
अणु
	cpu_boot_addr = boot_addr;
	tf_generic_smc(TF_SET_CPU_BOOT_ADDR_SMC, cpu_boot_addr, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक tf_prepare_idle(अचिन्हित दीर्घ mode)
अणु
	चयन (mode) अणु
	हाल TF_PM_MODE_LP0:
		tf_generic_smc(TF_CPU_PM, TF_CPU_PM_S3, cpu_boot_addr);
		अवरोध;

	हाल TF_PM_MODE_LP1:
		tf_generic_smc(TF_CPU_PM, TF_CPU_PM_S2, cpu_boot_addr);
		अवरोध;

	हाल TF_PM_MODE_LP1_NO_MC_CLK:
		tf_generic_smc(TF_CPU_PM, TF_CPU_PM_S2_NO_MC_CLK,
			       cpu_boot_addr);
		अवरोध;

	हाल TF_PM_MODE_LP2:
		tf_generic_smc(TF_CPU_PM, TF_CPU_PM_S1, cpu_boot_addr);
		अवरोध;

	हाल TF_PM_MODE_LP2_NOFLUSH_L2:
		tf_generic_smc(TF_CPU_PM, TF_CPU_PM_S1_NOFLUSH_L2,
			       cpu_boot_addr);
		अवरोध;

	हाल TF_PM_MODE_NONE:
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	tf_idle_mode = mode;

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_CACHE_L2X0
अटल व्योम tf_cache_ग_लिखो_sec(अचिन्हित दीर्घ val, अचिन्हित पूर्णांक reg)
अणु
	u32 enable_op, l2x0_way_mask = 0xff;

	चयन (reg) अणु
	हाल L2X0_CTRL:
		अगर (l2x0_saved_regs.aux_ctrl & L310_AUX_CTRL_ASSOCIATIVITY_16)
			l2x0_way_mask = 0xffff;

		चयन (tf_idle_mode) अणु
		हाल TF_PM_MODE_LP2:
			enable_op = TF_CACHE_REENABLE;
			अवरोध;

		शेष:
			enable_op = TF_CACHE_ENABLE;
			अवरोध;
		पूर्ण

		अगर (val == L2X0_CTRL_EN)
			tf_generic_smc(TF_CACHE_MAINT, enable_op,
				       l2x0_saved_regs.aux_ctrl);
		अन्यथा
			tf_generic_smc(TF_CACHE_MAINT, TF_CACHE_DISABLE,
				       l2x0_way_mask);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक tf_init_cache(व्योम)
अणु
	outer_cache.ग_लिखो_sec = tf_cache_ग_लिखो_sec;

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_CACHE_L2X0 */

अटल स्थिर काष्ठा firmware_ops trusted_foundations_ops = अणु
	.set_cpu_boot_addr = tf_set_cpu_boot_addr,
	.prepare_idle = tf_prepare_idle,
#अगर_घोषित CONFIG_CACHE_L2X0
	.l2x0_init = tf_init_cache,
#पूर्ण_अगर
पूर्ण;

व्योम रेजिस्टर_trusted_foundations(काष्ठा trusted_foundations_platक्रमm_data *pd)
अणु
	/*
	 * we are not using version inक्रमmation क्रम now since currently
	 * supported SMCs are compatible with all TF releases
	 */
	रेजिस्टर_firmware_ops(&trusted_foundations_ops);
पूर्ण

व्योम of_रेजिस्टर_trusted_foundations(व्योम)
अणु
	काष्ठा device_node *node;
	काष्ठा trusted_foundations_platक्रमm_data pdata;
	पूर्णांक err;

	node = of_find_compatible_node(शून्य, शून्य, "tlm,trusted-foundations");
	अगर (!node)
		वापस;

	err = of_property_पढ़ो_u32(node, "tlm,version-major",
				   &pdata.version_major);
	अगर (err != 0)
		panic("Trusted Foundation: missing version-major property\n");
	err = of_property_पढ़ो_u32(node, "tlm,version-minor",
				   &pdata.version_minor);
	अगर (err != 0)
		panic("Trusted Foundation: missing version-minor property\n");
	रेजिस्टर_trusted_foundations(&pdata);
पूर्ण

bool trusted_foundations_रेजिस्टरed(व्योम)
अणु
	वापस firmware_ops == &trusted_foundations_ops;
पूर्ण
