<शैली गुरु>
/*
 * Copyright 2003-2011 NetLogic Microप्रणालीs, Inc. (NetLogic). All rights
 * reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the NetLogic
 * license below:
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the करोcumentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY NETLOGIC ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL NETLOGIC OR CONTRIBUTORS BE LIABLE
 * FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#अगर_अघोषित _NLM_HAL_PIC_H
#घोषणा _NLM_HAL_PIC_H

/* PIC Specअगरic रेजिस्टरs */
#घोषणा PIC_CTRL		0x00

/* PIC control रेजिस्टर defines */
#घोषणा PIC_CTRL_ITV		32 /* पूर्णांकerrupt समयout value */
#घोषणा PIC_CTRL_ICI		19 /* ICI पूर्णांकerrupt समयout enable */
#घोषणा PIC_CTRL_ITE		18 /* पूर्णांकerrupt समयout enable */
#घोषणा PIC_CTRL_STE		10 /* प्रणाली समयr पूर्णांकerrupt enable */
#घोषणा PIC_CTRL_WWR1		8  /* watchकरोg 1 wraparound count क्रम reset */
#घोषणा PIC_CTRL_WWR0		6  /* watchकरोg 0 wraparound count क्रम reset */
#घोषणा PIC_CTRL_WWN1		4  /* watchकरोg 1 wraparound count क्रम NMI */
#घोषणा PIC_CTRL_WWN0		2  /* watchकरोg 0 wraparound count क्रम NMI */
#घोषणा PIC_CTRL_WTE		0  /* watchकरोg समयr enable */

/* PIC Status रेजिस्टर defines */
#घोषणा PIC_ICI_STATUS		33 /* ICI पूर्णांकerrupt समयout status */
#घोषणा PIC_ITE_STATUS		32 /* पूर्णांकerrupt समयout status */
#घोषणा PIC_STS_STATUS		4  /* System समयr पूर्णांकerrupt status */
#घोषणा PIC_WNS_STATUS		2  /* NMI status क्रम watchकरोg समयrs */
#घोषणा PIC_WIS_STATUS		0  /* Interrupt status क्रम watchकरोg समयrs */

/* PIC IPI control रेजिस्टर offsets */
#घोषणा PIC_IPICTRL_NMI		32
#घोषणा PIC_IPICTRL_RIV		20 /* received पूर्णांकerrupt vector */
#घोषणा PIC_IPICTRL_IDB		16 /* पूर्णांकerrupt destination base */
#घोषणा PIC_IPICTRL_DTE		 0 /* पूर्णांकerrupt destination thपढ़ो enables */

/* PIC IRT रेजिस्टर offsets */
#घोषणा PIC_IRT_ENABLE		31
#घोषणा PIC_IRT_NMI		29
#घोषणा PIC_IRT_SCH		28 /* Scheduling scheme */
#घोषणा PIC_IRT_RVEC		20 /* Interrupt receive vectors */
#घोषणा PIC_IRT_DT		19 /* Destination type */
#घोषणा PIC_IRT_DB		16 /* Destination base */
#घोषणा PIC_IRT_DTE		0  /* Destination thपढ़ो enables */

#घोषणा PIC_BYTESWAP		0x02
#घोषणा PIC_STATUS		0x04
#घोषणा PIC_INTR_TIMEOUT	0x06
#घोषणा PIC_ICI0_INTR_TIMEOUT	0x08
#घोषणा PIC_ICI1_INTR_TIMEOUT	0x0a
#घोषणा PIC_ICI2_INTR_TIMEOUT	0x0c
#घोषणा PIC_IPI_CTL		0x0e
#घोषणा PIC_INT_ACK		0x10
#घोषणा PIC_INT_PENDING0	0x12
#घोषणा PIC_INT_PENDING1	0x14
#घोषणा PIC_INT_PENDING2	0x16

#घोषणा PIC_WDOG0_MAXVAL	0x18
#घोषणा PIC_WDOG0_COUNT		0x1a
#घोषणा PIC_WDOG0_ENABLE0	0x1c
#घोषणा PIC_WDOG0_ENABLE1	0x1e
#घोषणा PIC_WDOG0_BEATCMD	0x20
#घोषणा PIC_WDOG0_BEAT0		0x22
#घोषणा PIC_WDOG0_BEAT1		0x24

#घोषणा PIC_WDOG1_MAXVAL	0x26
#घोषणा PIC_WDOG1_COUNT		0x28
#घोषणा PIC_WDOG1_ENABLE0	0x2a
#घोषणा PIC_WDOG1_ENABLE1	0x2c
#घोषणा PIC_WDOG1_BEATCMD	0x2e
#घोषणा PIC_WDOG1_BEAT0		0x30
#घोषणा PIC_WDOG1_BEAT1		0x32

#घोषणा PIC_WDOG_MAXVAL(i)	(PIC_WDOG0_MAXVAL + ((i) ? 7 : 0))
#घोषणा PIC_WDOG_COUNT(i)	(PIC_WDOG0_COUNT + ((i) ? 7 : 0))
#घोषणा PIC_WDOG_ENABLE0(i)	(PIC_WDOG0_ENABLE0 + ((i) ? 7 : 0))
#घोषणा PIC_WDOG_ENABLE1(i)	(PIC_WDOG0_ENABLE1 + ((i) ? 7 : 0))
#घोषणा PIC_WDOG_BEATCMD(i)	(PIC_WDOG0_BEATCMD + ((i) ? 7 : 0))
#घोषणा PIC_WDOG_BEAT0(i)	(PIC_WDOG0_BEAT0 + ((i) ? 7 : 0))
#घोषणा PIC_WDOG_BEAT1(i)	(PIC_WDOG0_BEAT1 + ((i) ? 7 : 0))

#घोषणा PIC_TIMER0_MAXVAL    0x34
#घोषणा PIC_TIMER1_MAXVAL    0x36
#घोषणा PIC_TIMER2_MAXVAL    0x38
#घोषणा PIC_TIMER3_MAXVAL    0x3a
#घोषणा PIC_TIMER4_MAXVAL    0x3c
#घोषणा PIC_TIMER5_MAXVAL    0x3e
#घोषणा PIC_TIMER6_MAXVAL    0x40
#घोषणा PIC_TIMER7_MAXVAL    0x42
#घोषणा PIC_TIMER_MAXVAL(i)  (PIC_TIMER0_MAXVAL + ((i) * 2))

#घोषणा PIC_TIMER0_COUNT     0x44
#घोषणा PIC_TIMER1_COUNT     0x46
#घोषणा PIC_TIMER2_COUNT     0x48
#घोषणा PIC_TIMER3_COUNT     0x4a
#घोषणा PIC_TIMER4_COUNT     0x4c
#घोषणा PIC_TIMER5_COUNT     0x4e
#घोषणा PIC_TIMER6_COUNT     0x50
#घोषणा PIC_TIMER7_COUNT     0x52
#घोषणा PIC_TIMER_COUNT(i)   (PIC_TIMER0_COUNT + ((i) * 2))

#घोषणा PIC_ITE0_N0_N1		0x54
#घोषणा PIC_ITE1_N0_N1		0x58
#घोषणा PIC_ITE2_N0_N1		0x5c
#घोषणा PIC_ITE3_N0_N1		0x60
#घोषणा PIC_ITE4_N0_N1		0x64
#घोषणा PIC_ITE5_N0_N1		0x68
#घोषणा PIC_ITE6_N0_N1		0x6c
#घोषणा PIC_ITE7_N0_N1		0x70
#घोषणा PIC_ITE_N0_N1(i)	(PIC_ITE0_N0_N1 + ((i) * 4))

#घोषणा PIC_ITE0_N2_N3		0x56
#घोषणा PIC_ITE1_N2_N3		0x5a
#घोषणा PIC_ITE2_N2_N3		0x5e
#घोषणा PIC_ITE3_N2_N3		0x62
#घोषणा PIC_ITE4_N2_N3		0x66
#घोषणा PIC_ITE5_N2_N3		0x6a
#घोषणा PIC_ITE6_N2_N3		0x6e
#घोषणा PIC_ITE7_N2_N3		0x72
#घोषणा PIC_ITE_N2_N3(i)	(PIC_ITE0_N2_N3 + ((i) * 4))

#घोषणा PIC_IRT0		0x74
#घोषणा PIC_IRT(i)		(PIC_IRT0 + ((i) * 2))

#घोषणा PIC_9XX_PENDING_0	0x6
#घोषणा PIC_9XX_PENDING_1	0x8
#घोषणा PIC_9XX_PENDING_2	0xa
#घोषणा PIC_9XX_PENDING_3	0xc

#घोषणा PIC_9XX_IRT0		0x1c0
#घोषणा PIC_9XX_IRT(i)		(PIC_9XX_IRT0 + ((i) * 2))

/*
 *    IRT Map
 */
#घोषणा PIC_NUM_IRTS		160
#घोषणा PIC_9XX_NUM_IRTS	256

#घोषणा PIC_IRT_WD_0_INDEX	0
#घोषणा PIC_IRT_WD_1_INDEX	1
#घोषणा PIC_IRT_WD_NMI_0_INDEX	2
#घोषणा PIC_IRT_WD_NMI_1_INDEX	3
#घोषणा PIC_IRT_TIMER_0_INDEX	4
#घोषणा PIC_IRT_TIMER_1_INDEX	5
#घोषणा PIC_IRT_TIMER_2_INDEX	6
#घोषणा PIC_IRT_TIMER_3_INDEX	7
#घोषणा PIC_IRT_TIMER_4_INDEX	8
#घोषणा PIC_IRT_TIMER_5_INDEX	9
#घोषणा PIC_IRT_TIMER_6_INDEX	10
#घोषणा PIC_IRT_TIMER_7_INDEX	11
#घोषणा PIC_IRT_CLOCK_INDEX	PIC_IRT_TIMER_7_INDEX
#घोषणा PIC_IRT_TIMER_INDEX(num)	((num) + PIC_IRT_TIMER_0_INDEX)


/* 11 and 12 */
#घोषणा PIC_NUM_MSG_Q_IRTS	32
#घोषणा PIC_IRT_MSG_Q0_INDEX	12
#घोषणा PIC_IRT_MSG_Q_INDEX(qid)	((qid) + PIC_IRT_MSG_Q0_INDEX)
/* 12 to 43 */
#घोषणा PIC_IRT_MSG_0_INDEX	44
#घोषणा PIC_IRT_MSG_1_INDEX	45
/* 44 and 45 */
#घोषणा PIC_NUM_PCIE_MSIX_IRTS	32
#घोषणा PIC_IRT_PCIE_MSIX_0_INDEX	46
#घोषणा PIC_IRT_PCIE_MSIX_INDEX(num)	((num) + PIC_IRT_PCIE_MSIX_0_INDEX)
/* 46 to 77 */
#घोषणा PIC_NUM_PCIE_LINK_IRTS		4
#घोषणा PIC_IRT_PCIE_LINK_0_INDEX	78
#घोषणा PIC_IRT_PCIE_LINK_1_INDEX	79
#घोषणा PIC_IRT_PCIE_LINK_2_INDEX	80
#घोषणा PIC_IRT_PCIE_LINK_3_INDEX	81
#घोषणा PIC_IRT_PCIE_LINK_INDEX(num)	((num) + PIC_IRT_PCIE_LINK_0_INDEX)

#घोषणा PIC_9XX_IRT_PCIE_LINK_0_INDEX	191
#घोषणा PIC_9XX_IRT_PCIE_LINK_INDEX(num) \
				((num) + PIC_9XX_IRT_PCIE_LINK_0_INDEX)

#घोषणा PIC_CLOCK_TIMER			7

#अगर !defined(LOCORE) && !defined(__ASSEMBLY__)

/*
 *   Misc
 */
#घोषणा PIC_IRT_VALID			1
#घोषणा PIC_LOCAL_SCHEDULING		1
#घोषणा PIC_GLOBAL_SCHEDULING		0

#घोषणा nlm_पढ़ो_pic_reg(b, r)	nlm_पढ़ो_reg64(b, r)
#घोषणा nlm_ग_लिखो_pic_reg(b, r, v) nlm_ग_लिखो_reg64(b, r, v)
#घोषणा nlm_get_pic_pcibase(node)	nlm_pcicfg_base(cpu_is_xlp9xx() ? \
		XLP9XX_IO_PIC_OFFSET(node) : XLP_IO_PIC_OFFSET(node))
#घोषणा nlm_get_pic_regbase(node) (nlm_get_pic_pcibase(node) + XLP_IO_PCI_HDRSZ)

/* We use PIC on node 0 as a समयr */
#घोषणा pic_समयr_freq()		nlm_get_pic_frequency(0)

/* IRT and h/w पूर्णांकerrupt routines */
अटल अंतरभूत व्योम
nlm_9xx_pic_ग_लिखो_irt(uपूर्णांक64_t base, पूर्णांक irt_num, पूर्णांक en, पूर्णांक nmi,
	पूर्णांक sch, पूर्णांक vec, पूर्णांक dt, पूर्णांक db, पूर्णांक cpu)
अणु
	uपूर्णांक64_t val;

	val = (((uपूर्णांक64_t)en & 0x1) << 22) | ((nmi & 0x1) << 23) |
			((0 /*mc*/) << 20) | ((vec & 0x3f) << 24) |
			((dt & 0x1) << 21) | (0 /*ptr*/ << 16) |
			(cpu & 0x3ff);

	nlm_ग_लिखो_pic_reg(base, PIC_9XX_IRT(irt_num), val);
पूर्ण

अटल अंतरभूत व्योम
nlm_pic_ग_लिखो_irt(uपूर्णांक64_t base, पूर्णांक irt_num, पूर्णांक en, पूर्णांक nmi,
	पूर्णांक sch, पूर्णांक vec, पूर्णांक dt, पूर्णांक db, पूर्णांक dte)
अणु
	uपूर्णांक64_t val;

	val = (((uपूर्णांक64_t)en & 0x1) << 31) | ((nmi & 0x1) << 29) |
			((sch & 0x1) << 28) | ((vec & 0x3f) << 20) |
			((dt & 0x1) << 19) | ((db & 0x7) << 16) |
			(dte & 0xffff);

	nlm_ग_लिखो_pic_reg(base, PIC_IRT(irt_num), val);
पूर्ण

अटल अंतरभूत व्योम
nlm_pic_ग_लिखो_irt_direct(uपूर्णांक64_t base, पूर्णांक irt_num, पूर्णांक en, पूर्णांक nmi,
	पूर्णांक sch, पूर्णांक vec, पूर्णांक cpu)
अणु
	अगर (cpu_is_xlp9xx())
		nlm_9xx_pic_ग_लिखो_irt(base, irt_num, en, nmi, sch, vec,
							1, 0, cpu);
	अन्यथा
		nlm_pic_ग_लिखो_irt(base, irt_num, en, nmi, sch, vec, 1,
			(cpu >> 4),		/* thपढ़ो group */
			1 << (cpu & 0xf));	/* thपढ़ो mask */
पूर्ण

अटल अंतरभूत uपूर्णांक64_t
nlm_pic_पढ़ो_समयr(uपूर्णांक64_t base, पूर्णांक समयr)
अणु
	वापस nlm_पढ़ो_pic_reg(base, PIC_TIMER_COUNT(समयr));
पूर्ण

अटल अंतरभूत uपूर्णांक32_t
nlm_pic_पढ़ो_समयr32(uपूर्णांक64_t base, पूर्णांक समयr)
अणु
	वापस (uपूर्णांक32_t)nlm_पढ़ो_pic_reg(base, PIC_TIMER_COUNT(समयr));
पूर्ण

अटल अंतरभूत व्योम
nlm_pic_ग_लिखो_समयr(uपूर्णांक64_t base, पूर्णांक समयr, uपूर्णांक64_t value)
अणु
	nlm_ग_लिखो_pic_reg(base, PIC_TIMER_COUNT(समयr), value);
पूर्ण

अटल अंतरभूत व्योम
nlm_pic_set_समयr(uपूर्णांक64_t base, पूर्णांक समयr, uपूर्णांक64_t value, पूर्णांक irq, पूर्णांक cpu)
अणु
	uपूर्णांक64_t pic_ctrl = nlm_पढ़ो_pic_reg(base, PIC_CTRL);
	पूर्णांक en;

	en = (irq > 0);
	nlm_ग_लिखो_pic_reg(base, PIC_TIMER_MAXVAL(समयr), value);
	nlm_pic_ग_लिखो_irt_direct(base, PIC_IRT_TIMER_INDEX(समयr),
		en, 0, 0, irq, cpu);

	/* enable the समयr */
	pic_ctrl |= (1 << (PIC_CTRL_STE + समयr));
	nlm_ग_लिखो_pic_reg(base, PIC_CTRL, pic_ctrl);
पूर्ण

अटल अंतरभूत व्योम
nlm_pic_enable_irt(uपूर्णांक64_t base, पूर्णांक irt)
अणु
	uपूर्णांक64_t reg;

	अगर (cpu_is_xlp9xx()) अणु
		reg = nlm_पढ़ो_pic_reg(base, PIC_9XX_IRT(irt));
		nlm_ग_लिखो_pic_reg(base, PIC_9XX_IRT(irt), reg | (1 << 22));
	पूर्ण अन्यथा अणु
		reg = nlm_पढ़ो_pic_reg(base, PIC_IRT(irt));
		nlm_ग_लिखो_pic_reg(base, PIC_IRT(irt), reg | (1u << 31));
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम
nlm_pic_disable_irt(uपूर्णांक64_t base, पूर्णांक irt)
अणु
	uपूर्णांक64_t reg;

	अगर (cpu_is_xlp9xx()) अणु
		reg = nlm_पढ़ो_pic_reg(base, PIC_9XX_IRT(irt));
		reg &= ~((uपूर्णांक64_t)1 << 22);
		nlm_ग_लिखो_pic_reg(base, PIC_9XX_IRT(irt), reg);
	पूर्ण अन्यथा अणु
		reg = nlm_पढ़ो_pic_reg(base, PIC_IRT(irt));
		reg &= ~((uपूर्णांक64_t)1 << 31);
		nlm_ग_लिखो_pic_reg(base, PIC_IRT(irt), reg);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम
nlm_pic_send_ipi(uपूर्णांक64_t base, पूर्णांक hwt, पूर्णांक irq, पूर्णांक nmi)
अणु
	uपूर्णांक64_t ipi;

	अगर (cpu_is_xlp9xx())
		ipi = (nmi << 23) | (irq << 24) |
			(0/*mcm*/ << 20) | (0/*ptr*/ << 16) | hwt;
	अन्यथा
		ipi = ((uपूर्णांक64_t)nmi << 31) | (irq << 20) |
			((hwt >> 4) << 16) | (1 << (hwt & 0xf));

	nlm_ग_लिखो_pic_reg(base, PIC_IPI_CTL, ipi);
पूर्ण

अटल अंतरभूत व्योम
nlm_pic_ack(uपूर्णांक64_t base, पूर्णांक irt_num)
अणु
	nlm_ग_लिखो_pic_reg(base, PIC_INT_ACK, irt_num);

	/* Ack the Status रेजिस्टर क्रम Watchकरोg & System समयrs */
	अगर (irt_num < 12)
		nlm_ग_लिखो_pic_reg(base, PIC_STATUS, (1 << irt_num));
पूर्ण

अटल अंतरभूत व्योम
nlm_pic_init_irt(uपूर्णांक64_t base, पूर्णांक irt, पूर्णांक irq, पूर्णांक hwt, पूर्णांक en)
अणु
	nlm_pic_ग_लिखो_irt_direct(base, irt, en, 0, 0, irq, hwt);
पूर्ण

पूर्णांक nlm_irq_to_irt(पूर्णांक irq);

#पूर्ण_अगर /* __ASSEMBLY__ */
#पूर्ण_अगर /* _NLM_HAL_PIC_H */
