<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * obपन.स:  Some useful locations in 0xFXXXXXXXX PA obio space on sun4d.
 *
 * Copyright (C) 1997 Jakub Jelinek <jj@sunsite.mff.cuni.cz>
 */

#अगर_अघोषित _SPARC_OBIO_H
#घोषणा _SPARC_OBIO_H

#समावेश <यंत्र/asi.h>

/* This weird monster likes to use the very upper parts of
   36bit PA क्रम these things :) */
   
/* CSR space (क्रम each XDBUS)
 *  ------------------------------------------------------------------------
 *  |   0xFE  |   DEVID    |                | XDBUS ID |                   |
 *  ------------------------------------------------------------------------
 *  35      28 27        20 19            10 9        8 7                 0
 */
   
#घोषणा CSR_BASE_ADDR		0xe0000000
#घोषणा CSR_CPU_SHIFT		(32 - 4 - 5)
#घोषणा CSR_XDBUS_SHIFT		8

#घोषणा CSR_BASE(cpu) (((CSR_BASE_ADDR >> CSR_CPU_SHIFT) + cpu) << CSR_CPU_SHIFT)

/* ECSR space (not क्रम each XDBUS)
 *  ------------------------------------------------------------------------
 *  |   0xF  | DEVID[7:1] |                			           |
 *  ------------------------------------------------------------------------
 *  35     32 31        25 24                 				  0
 */
   
#घोषणा ECSR_BASE_ADDR		0x00000000
#घोषणा ECSR_CPU_SHIFT		(32 - 5)
#घोषणा ECSR_DEV_SHIFT		(32 - 8)

#घोषणा ECSR_BASE(cpu) ((cpu) << ECSR_CPU_SHIFT)
#घोषणा ECSR_DEV_BASE(devid) ((devid) << ECSR_DEV_SHIFT) 

/* Bus Watcher */
#घोषणा BW_LOCAL_BASE		0xfff00000

#घोषणा BW_CID			0x00000000
#घोषणा BW_DBUS_CTRL		0x00000008
#घोषणा BW_DBUS_DATA		0x00000010
#घोषणा BW_CTRL			0x00001000
#घोषणा BW_INTR_TABLE		0x00001040
#घोषणा BW_INTR_TABLE_CLEAR	0x00001080
#घोषणा BW_PRESCALER		0x000010c0
#घोषणा BW_PTIMER_LIMIT		0x00002000
#घोषणा BW_PTIMER_COUNTER2	0x00002004
#घोषणा BW_PTIMER_NDLIMIT	0x00002008
#घोषणा BW_PTIMER_CTRL		0x0000200c
#घोषणा BW_PTIMER_COUNTER	0x00002010
#घोषणा BW_TIMER_LIMIT		0x00003000
#घोषणा BW_TIMER_COUNTER2	0x00003004
#घोषणा BW_TIMER_NDLIMIT	0x00003008
#घोषणा BW_TIMER_CTRL		0x0000300c
#घोषणा BW_TIMER_COUNTER	0x00003010

/* BW Control */
#घोषणा BW_CTRL_USER_TIMER	0x00000004	/* Is User Timer Free run enabled */

/* Boot Bus */
#घोषणा BB_LOCAL_BASE		0xf0000000

#घोषणा BB_STAT1		0x00100000
#घोषणा BB_STAT2		0x00120000
#घोषणा BB_STAT3		0x00140000
#घोषणा BB_LEDS			0x002e0000

/* Bits in BB_STAT2 */
#घोषणा BB_STAT2_AC_INTR	0x04	/* Aiee! 5ms and घातer is gone... */
#घोषणा BB_STAT2_TMP_INTR	0x10	/* My Penguins are burning. Are you able to smell it? */
#घोषणा BB_STAT2_FAN_INTR	0x20	/* My fan refuses to work */
#घोषणा BB_STAT2_PWR_INTR	0x40	/* On SC2000, one of the two ACs died. Ok, we go on... */
#घोषणा BB_STAT2_MASK		(BB_STAT2_AC_INTR|BB_STAT2_TMP_INTR|BB_STAT2_FAN_INTR|BB_STAT2_PWR_INTR)

/* Cache Controller */
#घोषणा CC_BASE		0x1F00000
#घोषणा CC_DATSTREAM	0x1F00000  /* Data stream रेजिस्टर */
#घोषणा CC_DATSIZE	0x1F0003F  /* Size */
#घोषणा CC_SRCSTREAM	0x1F00100  /* Source stream रेजिस्टर */
#घोषणा CC_DESSTREAM	0x1F00200  /* Destination stream रेजिस्टर */
#घोषणा CC_RMCOUNT	0x1F00300  /* Count of references and misses */
#घोषणा CC_IPEN		0x1F00406  /* Pending Interrupts */
#घोषणा CC_IMSK		0x1F00506  /* Interrupt Mask */
#घोषणा CC_ICLR		0x1F00606  /* Clear pending Interrupts */
#घोषणा CC_IGEN		0x1F00704  /* Generate Interrupt रेजिस्टर */
#घोषणा CC_STEST	0x1F00804  /* Internal self-test */
#घोषणा CC_CREG		0x1F00A04  /* Control रेजिस्टर */
#घोषणा CC_SREG		0x1F00B00  /* Status रेजिस्टर */
#घोषणा CC_RREG		0x1F00C04  /* Reset रेजिस्टर */
#घोषणा CC_EREG		0x1F00E00  /* Error code रेजिस्टर */
#घोषणा CC_CID		0x1F00F04  /* Component ID */

#अगर_अघोषित __ASSEMBLY__

अटल अंतरभूत पूर्णांक bw_get_पूर्णांकr_mask(पूर्णांक sbus_level)
अणु
	पूर्णांक mask;
	
	__यंत्र__ __अस्थिर__ ("lduha [%1] %2, %0" :
			      "=r" (mask) :
			      "r" (BW_LOCAL_BASE + BW_INTR_TABLE + (sbus_level << 3)),
			      "i" (ASI_M_CTL));
	वापस mask;
पूर्ण

अटल अंतरभूत व्योम bw_clear_पूर्णांकr_mask(पूर्णांक sbus_level, पूर्णांक mask)
अणु
	__यंत्र__ __अस्थिर__ ("stha %0, [%1] %2" : :
			      "r" (mask),
			      "r" (BW_LOCAL_BASE + BW_INTR_TABLE_CLEAR + (sbus_level << 3)),
			      "i" (ASI_M_CTL));
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक bw_get_prof_limit(पूर्णांक cpu)
अणु
	अचिन्हित पूर्णांक limit;
	
	__यंत्र__ __अस्थिर__ ("lda [%1] %2, %0" :
			      "=r" (limit) :
			      "r" (CSR_BASE(cpu) + BW_PTIMER_LIMIT),
			      "i" (ASI_M_CTL));
	वापस limit;
पूर्ण

अटल अंतरभूत व्योम bw_set_prof_limit(पूर्णांक cpu, अचिन्हित पूर्णांक limit)
अणु
	__यंत्र__ __अस्थिर__ ("sta %0, [%1] %2" : :
			      "r" (limit),
			      "r" (CSR_BASE(cpu) + BW_PTIMER_LIMIT),
			      "i" (ASI_M_CTL));
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक bw_get_ctrl(पूर्णांक cpu)
अणु
	अचिन्हित पूर्णांक ctrl;
	
	__यंत्र__ __अस्थिर__ ("lda [%1] %2, %0" :
			      "=r" (ctrl) :
			      "r" (CSR_BASE(cpu) + BW_CTRL),
			      "i" (ASI_M_CTL));
	वापस ctrl;
पूर्ण

अटल अंतरभूत व्योम bw_set_ctrl(पूर्णांक cpu, अचिन्हित पूर्णांक ctrl)
अणु
	__यंत्र__ __अस्थिर__ ("sta %0, [%1] %2" : :
			      "r" (ctrl),
			      "r" (CSR_BASE(cpu) + BW_CTRL),
			      "i" (ASI_M_CTL));
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक cc_get_ipen(व्योम)
अणु
	अचिन्हित पूर्णांक pending;
	
	__यंत्र__ __अस्थिर__ ("lduha [%1] %2, %0" :
			      "=r" (pending) :
			      "r" (CC_IPEN),
			      "i" (ASI_M_MXCC));
	वापस pending;
पूर्ण

अटल अंतरभूत व्योम cc_set_iclr(अचिन्हित पूर्णांक clear)
अणु
	__यंत्र__ __अस्थिर__ ("stha %0, [%1] %2" : :
			      "r" (clear),
			      "r" (CC_ICLR),
			      "i" (ASI_M_MXCC));
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक cc_get_imsk(व्योम)
अणु
	अचिन्हित पूर्णांक mask;
	
	__यंत्र__ __अस्थिर__ ("lduha [%1] %2, %0" :
			      "=r" (mask) :
			      "r" (CC_IMSK),
			      "i" (ASI_M_MXCC));
	वापस mask;
पूर्ण

अटल अंतरभूत व्योम cc_set_imsk(अचिन्हित पूर्णांक mask)
अणु
	__यंत्र__ __अस्थिर__ ("stha %0, [%1] %2" : :
			      "r" (mask),
			      "r" (CC_IMSK),
			      "i" (ASI_M_MXCC));
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक cc_get_imsk_other(पूर्णांक cpuid)
अणु
	अचिन्हित पूर्णांक mask;
	
	__यंत्र__ __अस्थिर__ ("lduha [%1] %2, %0" :
			      "=r" (mask) :
			      "r" (ECSR_BASE(cpuid) | CC_IMSK),
			      "i" (ASI_M_CTL));
	वापस mask;
पूर्ण

अटल अंतरभूत व्योम cc_set_imsk_other(पूर्णांक cpuid, अचिन्हित पूर्णांक mask)
अणु
	__यंत्र__ __अस्थिर__ ("stha %0, [%1] %2" : :
			      "r" (mask),
			      "r" (ECSR_BASE(cpuid) | CC_IMSK),
			      "i" (ASI_M_CTL));
पूर्ण

अटल अंतरभूत व्योम cc_set_igen(अचिन्हित पूर्णांक gen)
अणु
	__यंत्र__ __अस्थिर__ ("sta %0, [%1] %2" : :
			      "r" (gen),
			      "r" (CC_IGEN),
			      "i" (ASI_M_MXCC));
पूर्ण

#पूर्ण_अगर /* !__ASSEMBLY__ */

#पूर्ण_अगर /* !(_SPARC_OBIO_H) */
