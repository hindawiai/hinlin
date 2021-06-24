<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2012 ARM Ltd.
 */
#अगर_अघोषित __CLKSOURCE_ARM_ARCH_TIMER_H
#घोषणा __CLKSOURCE_ARM_ARCH_TIMER_H

#समावेश <linux/bitops.h>
#समावेश <linux/समयcounter.h>
#समावेश <linux/types.h>

#घोषणा ARCH_TIMER_TYPE_CP15		BIT(0)
#घोषणा ARCH_TIMER_TYPE_MEM		BIT(1)

#घोषणा ARCH_TIMER_CTRL_ENABLE		(1 << 0)
#घोषणा ARCH_TIMER_CTRL_IT_MASK		(1 << 1)
#घोषणा ARCH_TIMER_CTRL_IT_STAT		(1 << 2)

#घोषणा CNTHCTL_EL1PCTEN		(1 << 0)
#घोषणा CNTHCTL_EL1PCEN			(1 << 1)
#घोषणा CNTHCTL_EVNTEN			(1 << 2)
#घोषणा CNTHCTL_EVNTसूची			(1 << 3)
#घोषणा CNTHCTL_EVNTI			(0xF << 4)

क्रमागत arch_समयr_reg अणु
	ARCH_TIMER_REG_CTRL,
	ARCH_TIMER_REG_TVAL,
पूर्ण;

क्रमागत arch_समयr_ppi_nr अणु
	ARCH_TIMER_PHYS_SECURE_PPI,
	ARCH_TIMER_PHYS_NONSECURE_PPI,
	ARCH_TIMER_VIRT_PPI,
	ARCH_TIMER_HYP_PPI,
	ARCH_TIMER_HYP_VIRT_PPI,
	ARCH_TIMER_MAX_TIMER_PPI
पूर्ण;

क्रमागत arch_समयr_spi_nr अणु
	ARCH_TIMER_PHYS_SPI,
	ARCH_TIMER_VIRT_SPI,
	ARCH_TIMER_MAX_TIMER_SPI
पूर्ण;

#घोषणा ARCH_TIMER_PHYS_ACCESS		0
#घोषणा ARCH_TIMER_VIRT_ACCESS		1
#घोषणा ARCH_TIMER_MEM_PHYS_ACCESS	2
#घोषणा ARCH_TIMER_MEM_VIRT_ACCESS	3

#घोषणा ARCH_TIMER_MEM_MAX_FRAMES	8

#घोषणा ARCH_TIMER_USR_PCT_ACCESS_EN	(1 << 0) /* physical counter */
#घोषणा ARCH_TIMER_USR_VCT_ACCESS_EN	(1 << 1) /* भव counter */
#घोषणा ARCH_TIMER_VIRT_EVT_EN		(1 << 2)
#घोषणा ARCH_TIMER_EVT_TRIGGER_SHIFT	(4)
#घोषणा ARCH_TIMER_EVT_TRIGGER_MASK	(0xF << ARCH_TIMER_EVT_TRIGGER_SHIFT)
#घोषणा ARCH_TIMER_USR_VT_ACCESS_EN	(1 << 8) /* भव समयr रेजिस्टरs */
#घोषणा ARCH_TIMER_USR_PT_ACCESS_EN	(1 << 9) /* physical समयr रेजिस्टरs */

#घोषणा ARCH_TIMER_EVT_STREAM_PERIOD_US	100
#घोषणा ARCH_TIMER_EVT_STREAM_FREQ				\
	(USEC_PER_SEC / ARCH_TIMER_EVT_STREAM_PERIOD_US)

काष्ठा arch_समयr_kvm_info अणु
	काष्ठा समयcounter समयcounter;
	पूर्णांक भव_irq;
	पूर्णांक physical_irq;
पूर्ण;

काष्ठा arch_समयr_mem_frame अणु
	bool valid;
	phys_addr_t cntbase;
	माप_प्रकार size;
	पूर्णांक phys_irq;
	पूर्णांक virt_irq;
पूर्ण;

काष्ठा arch_समयr_mem अणु
	phys_addr_t cntctlbase;
	माप_प्रकार size;
	काष्ठा arch_समयr_mem_frame frame[ARCH_TIMER_MEM_MAX_FRAMES];
पूर्ण;

#अगर_घोषित CONFIG_ARM_ARCH_TIMER

बाह्य u32 arch_समयr_get_rate(व्योम);
बाह्य u64 (*arch_समयr_पढ़ो_counter)(व्योम);
बाह्य काष्ठा arch_समयr_kvm_info *arch_समयr_get_kvm_info(व्योम);
बाह्य bool arch_समयr_evtstrm_available(व्योम);

#अन्यथा

अटल अंतरभूत u32 arch_समयr_get_rate(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत u64 arch_समयr_पढ़ो_counter(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत bool arch_समयr_evtstrm_available(व्योम)
अणु
	वापस false;
पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर
