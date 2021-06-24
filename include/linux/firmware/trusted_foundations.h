<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (c) 2013, NVIDIA Corporation.
 */

/*
 * Support क्रम the Trusted Foundations secure monitor.
 *
 * Trusted Foundation comes active on some ARM consumer devices (most
 * Tegra-based devices sold on the market are concerned). Such devices can only
 * perक्रमm some basic operations, like setting the CPU reset vector, through
 * SMC calls to the secure monitor. The calls are completely specअगरic to
 * Trusted Foundations, and करो *not* follow the SMC calling convention or the
 * PSCI standard.
 */

#अगर_अघोषित __FIRMWARE_TRUSTED_FOUNDATIONS_H
#घोषणा __FIRMWARE_TRUSTED_FOUNDATIONS_H

#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/bug.h>
#समावेश <linux/of.h>
#समावेश <linux/cpu.h>
#समावेश <linux/smp.h>
#समावेश <linux/types.h>

#समावेश <यंत्र/hardware/cache-l2x0.h>
#समावेश <यंत्र/outercache.h>

#घोषणा TF_PM_MODE_LP0			0
#घोषणा TF_PM_MODE_LP1			1
#घोषणा TF_PM_MODE_LP1_NO_MC_CLK	2
#घोषणा TF_PM_MODE_LP2			3
#घोषणा TF_PM_MODE_LP2_NOFLUSH_L2	4
#घोषणा TF_PM_MODE_NONE			5

काष्ठा trusted_foundations_platक्रमm_data अणु
	अचिन्हित पूर्णांक version_major;
	अचिन्हित पूर्णांक version_minor;
पूर्ण;

#अगर IS_ENABLED(CONFIG_TRUSTED_FOUNDATIONS)

व्योम रेजिस्टर_trusted_foundations(काष्ठा trusted_foundations_platक्रमm_data *pd);
व्योम of_रेजिस्टर_trusted_foundations(व्योम);
bool trusted_foundations_रेजिस्टरed(व्योम);

#अन्यथा /* CONFIG_TRUSTED_FOUNDATIONS */
अटल अंतरभूत व्योम tf_dummy_ग_लिखो_sec(अचिन्हित दीर्घ val, अचिन्हित पूर्णांक reg)
अणु
पूर्ण

अटल अंतरभूत व्योम रेजिस्टर_trusted_foundations(
				   काष्ठा trusted_foundations_platक्रमm_data *pd)
अणु
	/*
	 * If the प्रणाली requires TF and we cannot provide it, जारी booting
	 * but disable features that cannot be provided.
	 */
	pr_err("No support for Trusted Foundations, continuing in degraded mode.\n");
	pr_err("Secondary processors as well as CPU PM will be disabled.\n");
#अगर IS_ENABLED(CONFIG_CACHE_L2X0)
	pr_err("L2X0 cache will be kept disabled.\n");
	outer_cache.ग_लिखो_sec = tf_dummy_ग_लिखो_sec;
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_SMP)
	setup_max_cpus = 0;
#पूर्ण_अगर
	cpu_idle_poll_ctrl(true);
पूर्ण

अटल अंतरभूत व्योम of_रेजिस्टर_trusted_foundations(व्योम)
अणु
	/*
	 * If we find the target should enable TF but करोes not support it,
	 * fail as the प्रणाली won't be able to करो much anyway
	 */
	अगर (of_find_compatible_node(शून्य, शून्य, "tlm,trusted-foundations"))
		रेजिस्टर_trusted_foundations(शून्य);
पूर्ण

अटल अंतरभूत bool trusted_foundations_रेजिस्टरed(व्योम)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर /* CONFIG_TRUSTED_FOUNDATIONS */

#पूर्ण_अगर
