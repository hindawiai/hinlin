<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright 2012 Calxeda, Inc.
 */
#अगर_अघोषित _ASM_ARM_PERCPU_H_
#घोषणा _ASM_ARM_PERCPU_H_

रेजिस्टर अचिन्हित दीर्घ current_stack_poपूर्णांकer यंत्र ("sp");

/*
 * Same as यंत्र-generic/percpu.h, except that we store the per cpu offset
 * in the TPIDRPRW. TPIDRPRW only exists on V6K and V7
 */
#अगर defined(CONFIG_SMP) && !defined(CONFIG_CPU_V6)
अटल अंतरभूत व्योम set_my_cpu_offset(अचिन्हित दीर्घ off)
अणु
	/* Set TPIDRPRW */
	यंत्र अस्थिर("mcr p15, 0, %0, c13, c0, 4" : : "r" (off) : "memory");
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ __my_cpu_offset(व्योम)
अणु
	अचिन्हित दीर्घ off;

	/*
	 * Read TPIDRPRW.
	 * We want to allow caching the value, so aव्योम using अस्थिर and
	 * instead use a fake stack पढ़ो to hazard against barrier().
	 */
	यंत्र("mrc p15, 0, %0, c13, c0, 4" : "=r" (off)
		: "Q" (*(स्थिर अचिन्हित दीर्घ *)current_stack_poपूर्णांकer));

	वापस off;
पूर्ण
#घोषणा __my_cpu_offset __my_cpu_offset()
#अन्यथा
#घोषणा set_my_cpu_offset(x)	करो अणुपूर्ण जबतक(0)

#पूर्ण_अगर /* CONFIG_SMP */

#समावेश <यंत्र-generic/percpu.h>

#पूर्ण_अगर /* _ASM_ARM_PERCPU_H_ */
