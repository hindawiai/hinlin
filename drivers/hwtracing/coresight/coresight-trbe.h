<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * This contains all required hardware related helper functions क्रम
 * Trace Buffer Extension (TRBE) driver in the coresight framework.
 *
 * Copyright (C) 2020 ARM Ltd.
 *
 * Author: Anshuman Khandual <anshuman.khandual@arm.com>
 */
#समावेश <linux/coresight.h>
#समावेश <linux/device.h>
#समावेश <linux/irq.h>
#समावेश <linux/kernel.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/smp.h>

#समावेश "coresight-etm-perf.h"

अटल अंतरभूत bool is_trbe_available(व्योम)
अणु
	u64 aa64dfr0 = पढ़ो_sysreg_s(SYS_ID_AA64DFR0_EL1);
	अचिन्हित पूर्णांक trbe = cpuid_feature_extract_अचिन्हित_field(aa64dfr0, ID_AA64DFR0_TRBE_SHIFT);

	वापस trbe >= 0b0001;
पूर्ण

अटल अंतरभूत bool is_trbe_enabled(व्योम)
अणु
	u64 trblimitr = पढ़ो_sysreg_s(SYS_TRBLIMITR_EL1);

	वापस trblimitr & TRBLIMITR_ENABLE;
पूर्ण

#घोषणा TRBE_EC_OTHERS		0
#घोषणा TRBE_EC_STAGE1_ABORT	36
#घोषणा TRBE_EC_STAGE2_ABORT	37

अटल अंतरभूत पूर्णांक get_trbe_ec(u64 trbsr)
अणु
	वापस (trbsr >> TRBSR_EC_SHIFT) & TRBSR_EC_MASK;
पूर्ण

#घोषणा TRBE_BSC_NOT_STOPPED 0
#घोषणा TRBE_BSC_FILLED      1
#घोषणा TRBE_BSC_TRIGGERED   2

अटल अंतरभूत पूर्णांक get_trbe_bsc(u64 trbsr)
अणु
	वापस (trbsr >> TRBSR_BSC_SHIFT) & TRBSR_BSC_MASK;
पूर्ण

अटल अंतरभूत व्योम clr_trbe_irq(व्योम)
अणु
	u64 trbsr = पढ़ो_sysreg_s(SYS_TRBSR_EL1);

	trbsr &= ~TRBSR_IRQ;
	ग_लिखो_sysreg_s(trbsr, SYS_TRBSR_EL1);
पूर्ण

अटल अंतरभूत bool is_trbe_irq(u64 trbsr)
अणु
	वापस trbsr & TRBSR_IRQ;
पूर्ण

अटल अंतरभूत bool is_trbe_trg(u64 trbsr)
अणु
	वापस trbsr & TRBSR_TRG;
पूर्ण

अटल अंतरभूत bool is_trbe_wrap(u64 trbsr)
अणु
	वापस trbsr & TRBSR_WRAP;
पूर्ण

अटल अंतरभूत bool is_trbe_पात(u64 trbsr)
अणु
	वापस trbsr & TRBSR_ABORT;
पूर्ण

अटल अंतरभूत bool is_trbe_running(u64 trbsr)
अणु
	वापस !(trbsr & TRBSR_STOP);
पूर्ण

#घोषणा TRBE_TRIG_MODE_STOP		0
#घोषणा TRBE_TRIG_MODE_IRQ		1
#घोषणा TRBE_TRIG_MODE_IGNORE		3

#घोषणा TRBE_FILL_MODE_FILL		0
#घोषणा TRBE_FILL_MODE_WRAP		1
#घोषणा TRBE_FILL_MODE_CIRCULAR_BUFFER	3

अटल अंतरभूत व्योम set_trbe_disabled(व्योम)
अणु
	u64 trblimitr = पढ़ो_sysreg_s(SYS_TRBLIMITR_EL1);

	trblimitr &= ~TRBLIMITR_ENABLE;
	ग_लिखो_sysreg_s(trblimitr, SYS_TRBLIMITR_EL1);
पूर्ण

अटल अंतरभूत bool get_trbe_flag_update(u64 trbidr)
अणु
	वापस trbidr & TRBIDR_FLAG;
पूर्ण

अटल अंतरभूत bool is_trbe_programmable(u64 trbidr)
अणु
	वापस !(trbidr & TRBIDR_PROG);
पूर्ण

अटल अंतरभूत पूर्णांक get_trbe_address_align(u64 trbidr)
अणु
	वापस (trbidr >> TRBIDR_ALIGN_SHIFT) & TRBIDR_ALIGN_MASK;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ get_trbe_ग_लिखो_poपूर्णांकer(व्योम)
अणु
	वापस पढ़ो_sysreg_s(SYS_TRBPTR_EL1);
पूर्ण

अटल अंतरभूत व्योम set_trbe_ग_लिखो_poपूर्णांकer(अचिन्हित दीर्घ addr)
अणु
	WARN_ON(is_trbe_enabled());
	ग_लिखो_sysreg_s(addr, SYS_TRBPTR_EL1);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ get_trbe_limit_poपूर्णांकer(व्योम)
अणु
	u64 trblimitr = पढ़ो_sysreg_s(SYS_TRBLIMITR_EL1);
	अचिन्हित दीर्घ addr = trblimitr & (TRBLIMITR_LIMIT_MASK << TRBLIMITR_LIMIT_SHIFT);

	WARN_ON(!IS_ALIGNED(addr, PAGE_SIZE));
	वापस addr;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ get_trbe_base_poपूर्णांकer(व्योम)
अणु
	u64 trbbaser = पढ़ो_sysreg_s(SYS_TRBBASER_EL1);
	अचिन्हित दीर्घ addr = trbbaser & (TRBBASER_BASE_MASK << TRBBASER_BASE_SHIFT);

	WARN_ON(!IS_ALIGNED(addr, PAGE_SIZE));
	वापस addr;
पूर्ण

अटल अंतरभूत व्योम set_trbe_base_poपूर्णांकer(अचिन्हित दीर्घ addr)
अणु
	WARN_ON(is_trbe_enabled());
	WARN_ON(!IS_ALIGNED(addr, (1UL << TRBBASER_BASE_SHIFT)));
	WARN_ON(!IS_ALIGNED(addr, PAGE_SIZE));
	ग_लिखो_sysreg_s(addr, SYS_TRBBASER_EL1);
पूर्ण
