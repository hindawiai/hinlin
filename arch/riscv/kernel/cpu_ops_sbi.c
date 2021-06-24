<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * HSM extension and cpu_ops implementation.
 *
 * Copyright (c) 2020 Western Digital Corporation or its affiliates.
 */

#समावेश <linux/init.h>
#समावेश <linux/mm.h>
#समावेश <यंत्र/cpu_ops.h>
#समावेश <यंत्र/sbi.h>
#समावेश <यंत्र/smp.h>

बाह्य अक्षर secondary_start_sbi[];
स्थिर काष्ठा cpu_operations cpu_ops_sbi;

अटल पूर्णांक sbi_hsm_hart_start(अचिन्हित दीर्घ hartid, अचिन्हित दीर्घ saddr,
			      अचिन्हित दीर्घ priv)
अणु
	काष्ठा sbiret ret;

	ret = sbi_ecall(SBI_EXT_HSM, SBI_EXT_HSM_HART_START,
			hartid, saddr, priv, 0, 0, 0);
	अगर (ret.error)
		वापस sbi_err_map_linux_त्रुटि_सं(ret.error);
	अन्यथा
		वापस 0;
पूर्ण

#अगर_घोषित CONFIG_HOTPLUG_CPU
अटल पूर्णांक sbi_hsm_hart_stop(व्योम)
अणु
	काष्ठा sbiret ret;

	ret = sbi_ecall(SBI_EXT_HSM, SBI_EXT_HSM_HART_STOP, 0, 0, 0, 0, 0, 0);

	अगर (ret.error)
		वापस sbi_err_map_linux_त्रुटि_सं(ret.error);
	अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक sbi_hsm_hart_get_status(अचिन्हित दीर्घ hartid)
अणु
	काष्ठा sbiret ret;

	ret = sbi_ecall(SBI_EXT_HSM, SBI_EXT_HSM_HART_STATUS,
			hartid, 0, 0, 0, 0, 0);
	अगर (ret.error)
		वापस sbi_err_map_linux_त्रुटि_सं(ret.error);
	अन्यथा
		वापस ret.value;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक sbi_cpu_start(अचिन्हित पूर्णांक cpuid, काष्ठा task_काष्ठा *tidle)
अणु
	पूर्णांक rc;
	अचिन्हित दीर्घ boot_addr = __pa_symbol(secondary_start_sbi);
	पूर्णांक hartid = cpuid_to_hartid_map(cpuid);

	cpu_update_secondary_bootdata(cpuid, tidle);
	rc = sbi_hsm_hart_start(hartid, boot_addr, 0);

	वापस rc;
पूर्ण

अटल पूर्णांक sbi_cpu_prepare(अचिन्हित पूर्णांक cpuid)
अणु
	अगर (!cpu_ops_sbi.cpu_start) अणु
		pr_err("cpu start method not defined for CPU [%d]\n", cpuid);
		वापस -ENODEV;
	पूर्ण
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_HOTPLUG_CPU
अटल पूर्णांक sbi_cpu_disable(अचिन्हित पूर्णांक cpuid)
अणु
	अगर (!cpu_ops_sbi.cpu_stop)
		वापस -EOPNOTSUPP;
	वापस 0;
पूर्ण

अटल व्योम sbi_cpu_stop(व्योम)
अणु
	पूर्णांक ret;

	ret = sbi_hsm_hart_stop();
	pr_crit("Unable to stop the cpu %u (%d)\n", smp_processor_id(), ret);
पूर्ण

अटल पूर्णांक sbi_cpu_is_stopped(अचिन्हित पूर्णांक cpuid)
अणु
	पूर्णांक rc;
	पूर्णांक hartid = cpuid_to_hartid_map(cpuid);

	rc = sbi_hsm_hart_get_status(hartid);

	अगर (rc == SBI_HSM_HART_STATUS_STOPPED)
		वापस 0;
	वापस rc;
पूर्ण
#पूर्ण_अगर

स्थिर काष्ठा cpu_operations cpu_ops_sbi = अणु
	.name		= "sbi",
	.cpu_prepare	= sbi_cpu_prepare,
	.cpu_start	= sbi_cpu_start,
#अगर_घोषित CONFIG_HOTPLUG_CPU
	.cpu_disable	= sbi_cpu_disable,
	.cpu_stop	= sbi_cpu_stop,
	.cpu_is_stopped	= sbi_cpu_is_stopped,
#पूर्ण_अगर
पूर्ण;
