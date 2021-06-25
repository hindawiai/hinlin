<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2019 Lubomir Rपूर्णांकel <lkundrak@v3.sk>
 */
#समावेश <linux/पन.स>
#समावेश <यंत्र/smp_scu.h>
#समावेश <यंत्र/smp.h>
#समावेश "addr-map.h"

#घोषणा SW_BRANCH_VIRT_ADDR	CIU_REG(0x24)

अटल पूर्णांक mmp3_boot_secondary(अचिन्हित पूर्णांक cpu, काष्ठा task_काष्ठा *idle)
अणु
	/*
	 * Apparently, the boot ROM on the second core spins on this
	 * रेजिस्टर becoming non-zero and then jumps to the address written
	 * there. No IPIs involved.
	 */
	__raw_ग_लिखोl(__pa_symbol(secondary_startup), SW_BRANCH_VIRT_ADDR);
	वापस 0;
पूर्ण

अटल व्योम mmp3_smp_prepare_cpus(अचिन्हित पूर्णांक max_cpus)
अणु
	scu_enable(SCU_VIRT_BASE);
पूर्ण

अटल स्थिर काष्ठा smp_operations mmp3_smp_ops __initस्थिर = अणु
	.smp_prepare_cpus	= mmp3_smp_prepare_cpus,
	.smp_boot_secondary	= mmp3_boot_secondary,
पूर्ण;
CPU_METHOD_OF_DECLARE(mmp3_smp, "marvell,mmp3-smp", &mmp3_smp_ops);
