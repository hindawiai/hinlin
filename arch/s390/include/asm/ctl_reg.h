<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright IBM Corp. 1999, 2009
 *
 * Author(s): Martin Schwidefsky <schwidefsky@de.ibm.com>
 */

#अगर_अघोषित __ASM_CTL_REG_H
#घोषणा __ASM_CTL_REG_H

#समावेश <linux/bits.h>

#घोषणा CR0_CLOCK_COMPARATOR_SIGN	BIT(63 - 10)
#घोषणा CR0_LOW_ADDRESS_PROTECTION	BIT(63 - 35)
#घोषणा CR0_EMERGENCY_SIGNAL_SUBMASK	BIT(63 - 49)
#घोषणा CR0_EXTERNAL_CALL_SUBMASK	BIT(63 - 50)
#घोषणा CR0_CLOCK_COMPARATOR_SUBMASK	BIT(63 - 52)
#घोषणा CR0_CPU_TIMER_SUBMASK		BIT(63 - 53)
#घोषणा CR0_SERVICE_SIGNAL_SUBMASK	BIT(63 - 54)
#घोषणा CR0_UNUSED_56			BIT(63 - 56)
#घोषणा CR0_INTERRUPT_KEY_SUBMASK	BIT(63 - 57)
#घोषणा CR0_MEASUREMENT_ALERT_SUBMASK	BIT(63 - 58)

#घोषणा CR2_GUARDED_STORAGE		BIT(63 - 59)

#घोषणा CR14_UNUSED_32			BIT(63 - 32)
#घोषणा CR14_UNUSED_33			BIT(63 - 33)
#घोषणा CR14_CHANNEL_REPORT_SUBMASK	BIT(63 - 35)
#घोषणा CR14_RECOVERY_SUBMASK		BIT(63 - 36)
#घोषणा CR14_DEGRADATION_SUBMASK	BIT(63 - 37)
#घोषणा CR14_EXTERNAL_DAMAGE_SUBMASK	BIT(63 - 38)
#घोषणा CR14_WARNING_SUBMASK		BIT(63 - 39)

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/bug.h>

#घोषणा __ctl_load(array, low, high) करो अणु				\
	प्रकार काष्ठा अणु अक्षर _[माप(array)]; पूर्ण addrtype;		\
									\
	BUILD_BUG_ON(माप(addrtype) != (high - low + 1) * माप(दीर्घ));\
	यंत्र अस्थिर(							\
		"	lctlg	%1,%2,%0\n"				\
		:							\
		: "Q" (*(addrtype *)(&array)), "i" (low), "i" (high)	\
		: "memory");						\
पूर्ण जबतक (0)

#घोषणा __ctl_store(array, low, high) करो अणु				\
	प्रकार काष्ठा अणु अक्षर _[माप(array)]; पूर्ण addrtype;		\
									\
	BUILD_BUG_ON(माप(addrtype) != (high - low + 1) * माप(दीर्घ));\
	यंत्र अस्थिर(							\
		"	stctg	%1,%2,%0\n"				\
		: "=Q" (*(addrtype *)(&array))				\
		: "i" (low), "i" (high));				\
पूर्ण जबतक (0)

अटल __always_अंतरभूत व्योम __ctl_set_bit(अचिन्हित पूर्णांक cr, अचिन्हित पूर्णांक bit)
अणु
	अचिन्हित दीर्घ reg;

	__ctl_store(reg, cr, cr);
	reg |= 1UL << bit;
	__ctl_load(reg, cr, cr);
पूर्ण

अटल __always_अंतरभूत व्योम __ctl_clear_bit(अचिन्हित पूर्णांक cr, अचिन्हित पूर्णांक bit)
अणु
	अचिन्हित दीर्घ reg;

	__ctl_store(reg, cr, cr);
	reg &= ~(1UL << bit);
	__ctl_load(reg, cr, cr);
पूर्ण

व्योम smp_ctl_set_bit(पूर्णांक cr, पूर्णांक bit);
व्योम smp_ctl_clear_bit(पूर्णांक cr, पूर्णांक bit);

जोड़ ctlreg0 अणु
	अचिन्हित दीर्घ val;
	काष्ठा अणु
		अचिन्हित दीर्घ	   : 8;
		अचिन्हित दीर्घ tcx  : 1;	/* Transactional-Execution control */
		अचिन्हित दीर्घ pअगरo : 1;	/* Transactional-Execution Program-
					   Interruption-Filtering Override */
		अचिन्हित दीर्घ	   : 22;
		अचिन्हित दीर्घ	   : 3;
		अचिन्हित दीर्घ lap  : 1; /* Low-address-protection control */
		अचिन्हित दीर्घ	   : 4;
		अचिन्हित दीर्घ edat : 1; /* Enhanced-DAT-enablement control */
		अचिन्हित दीर्घ	   : 2;
		अचिन्हित दीर्घ iep  : 1; /* Inकाष्ठाion-Execution-Protection */
		अचिन्हित दीर्घ	   : 1;
		अचिन्हित दीर्घ afp  : 1; /* AFP-रेजिस्टर control */
		अचिन्हित दीर्घ vx   : 1; /* Vector enablement control */
		अचिन्हित दीर्घ	   : 7;
		अचिन्हित दीर्घ sssm : 1; /* Service संकेत subclass mask */
		अचिन्हित दीर्घ	   : 9;
	पूर्ण;
पूर्ण;

जोड़ ctlreg2 अणु
	अचिन्हित दीर्घ val;
	काष्ठा अणु
		अचिन्हित दीर्घ	    : 33;
		अचिन्हित दीर्घ ducto : 25;
		अचिन्हित दीर्घ	    : 1;
		अचिन्हित दीर्घ gse   : 1;
		अचिन्हित दीर्घ	    : 1;
		अचिन्हित दीर्घ tds   : 1;
		अचिन्हित दीर्घ tdc   : 2;
	पूर्ण;
पूर्ण;

#घोषणा ctl_set_bit(cr, bit) smp_ctl_set_bit(cr, bit)
#घोषणा ctl_clear_bit(cr, bit) smp_ctl_clear_bit(cr, bit)

#पूर्ण_अगर /* __ASSEMBLY__ */
#पूर्ण_अगर /* __ASM_CTL_REG_H */
