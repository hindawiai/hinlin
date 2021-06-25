<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
// Copyright (C) 2005-2017 Andes Technology Corporation

#समावेश <यंत्र/nds32.h>
#समावेश <nds32_पूर्णांकrinsic.h>

#घोषणा arch_local_irq_disable()	\
	GIE_DISABLE();

#घोषणा arch_local_irq_enable()	\
	GIE_ENABLE();
अटल अंतरभूत अचिन्हित दीर्घ arch_local_irq_save(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	flags = __nds32__mfsr(NDS32_SR_PSW) & PSW_mskGIE;
	GIE_DISABLE();
	वापस flags;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ arch_local_save_flags(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	flags = __nds32__mfsr(NDS32_SR_PSW) & PSW_mskGIE;
	वापस flags;
पूर्ण

अटल अंतरभूत व्योम arch_local_irq_restore(अचिन्हित दीर्घ flags)
अणु
	अगर(flags)
		GIE_ENABLE();
पूर्ण

अटल अंतरभूत पूर्णांक arch_irqs_disabled_flags(अचिन्हित दीर्घ flags)
अणु
	वापस !flags;
पूर्ण

अटल अंतरभूत पूर्णांक arch_irqs_disabled(व्योम)
अणु
	वापस arch_irqs_disabled_flags(arch_local_save_flags());
पूर्ण
