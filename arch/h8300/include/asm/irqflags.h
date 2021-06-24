<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _H8300_IRQFLAGS_H
#घोषणा _H8300_IRQFLAGS_H

#अगर_घोषित CONFIG_CPU_H8300H
प्रकार अचिन्हित अक्षर h8300flags;

अटल अंतरभूत h8300flags arch_local_save_flags(व्योम)
अणु
	h8300flags flags;

	__यंत्र__ अस्थिर ("stc ccr,%w0" : "=r" (flags));
	वापस flags;
पूर्ण

अटल अंतरभूत व्योम arch_local_irq_disable(व्योम)
अणु
	__यंत्र__ अस्थिर ("orc  #0xc0,ccr");
पूर्ण

अटल अंतरभूत व्योम arch_local_irq_enable(व्योम)
अणु
	__यंत्र__ अस्थिर ("andc #0x3f,ccr");
पूर्ण

अटल अंतरभूत h8300flags arch_local_irq_save(व्योम)
अणु
	h8300flags flags;

	__यंत्र__ अस्थिर ("stc ccr,%w0\n\t"
		      "orc  #0xc0,ccr" : "=r" (flags));
	वापस flags;
पूर्ण

अटल अंतरभूत व्योम arch_local_irq_restore(h8300flags flags)
अणु
	__यंत्र__ अस्थिर ("ldc %w0,ccr" : : "r" (flags) : "cc");
पूर्ण

अटल अंतरभूत पूर्णांक arch_irqs_disabled_flags(अचिन्हित दीर्घ flags)
अणु
	वापस (flags & 0xc0) == 0xc0;
पूर्ण
#पूर्ण_अगर
#अगर_घोषित CONFIG_CPU_H8S
प्रकार अचिन्हित लघु h8300flags;

अटल अंतरभूत h8300flags arch_local_save_flags(व्योम)
अणु
	h8300flags flags;

	__यंत्र__ अस्थिर ("stc ccr,%w0\n\tstc exr,%x0" : "=r" (flags));
	वापस flags;
पूर्ण

अटल अंतरभूत व्योम arch_local_irq_disable(व्योम)
अणु
	__यंत्र__ अस्थिर ("orc #0x80,ccr\n\t");
पूर्ण

अटल अंतरभूत व्योम arch_local_irq_enable(व्योम)
अणु
	__यंत्र__ अस्थिर ("andc #0x7f,ccr\n\t"
		      "andc #0xf0,exr\n\t");
पूर्ण

अटल अंतरभूत h8300flags arch_local_irq_save(व्योम)
अणु
	h8300flags flags;

	__यंत्र__ अस्थिर ("stc ccr,%w0\n\t"
		      "stc exr,%x0\n\t"
		      "orc  #0x80,ccr\n\t"
		      : "=r" (flags));
	वापस flags;
पूर्ण

अटल अंतरभूत व्योम arch_local_irq_restore(h8300flags flags)
अणु
	__यंत्र__ अस्थिर ("ldc %w0,ccr\n\t"
		      "ldc %x0,exr"
		      : : "r" (flags) : "cc");
पूर्ण

अटल अंतरभूत पूर्णांक arch_irqs_disabled_flags(h8300flags flags)
अणु
	वापस (flags & 0x0080) == 0x0080;
पूर्ण

#पूर्ण_अगर

अटल अंतरभूत पूर्णांक arch_irqs_disabled(व्योम)
अणु
	वापस arch_irqs_disabled_flags(arch_local_save_flags());
पूर्ण

#पूर्ण_अगर /* _H8300_IRQFLAGS_H */
