<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_IA64_IOSAPIC_H
#घोषणा __ASM_IA64_IOSAPIC_H

#घोषणा	IOSAPIC_REG_SELECT	0x0
#घोषणा	IOSAPIC_WINDOW		0x10
#घोषणा	IOSAPIC_EOI		0x40

#घोषणा	IOSAPIC_VERSION		0x1

/*
 * Redirection table entry
 */
#घोषणा	IOSAPIC_RTE_LOW(i)	(0x10+i*2)
#घोषणा	IOSAPIC_RTE_HIGH(i)	(0x11+i*2)

#घोषणा	IOSAPIC_DEST_SHIFT		16

/*
 * Delivery mode
 */
#घोषणा	IOSAPIC_DELIVERY_SHIFT		8
#घोषणा	IOSAPIC_FIXED			0x0
#घोषणा	IOSAPIC_LOWEST_PRIORITY	0x1
#घोषणा	IOSAPIC_PMI			0x2
#घोषणा	IOSAPIC_NMI			0x4
#घोषणा	IOSAPIC_INIT			0x5
#घोषणा	IOSAPIC_EXTINT			0x7

/*
 * Interrupt polarity
 */
#घोषणा	IOSAPIC_POLARITY_SHIFT		13
#घोषणा	IOSAPIC_POL_HIGH		0
#घोषणा	IOSAPIC_POL_LOW		1

/*
 * Trigger mode
 */
#घोषणा	IOSAPIC_TRIGGER_SHIFT		15
#घोषणा	IOSAPIC_EDGE			0
#घोषणा	IOSAPIC_LEVEL			1

/*
 * Mask bit
 */

#घोषणा	IOSAPIC_MASK_SHIFT		16
#घोषणा	IOSAPIC_MASK			(1<<IOSAPIC_MASK_SHIFT)

#घोषणा IOSAPIC_VECTOR_MASK		0xffffff00

#अगर_अघोषित __ASSEMBLY__

#घोषणा NR_IOSAPICS			256

#घोषणा iosapic_pcat_compat_init	ia64_native_iosapic_pcat_compat_init
#घोषणा __iosapic_पढ़ो			__ia64_native_iosapic_पढ़ो
#घोषणा __iosapic_ग_लिखो			__ia64_native_iosapic_ग_लिखो
#घोषणा iosapic_get_irq_chip		ia64_native_iosapic_get_irq_chip

बाह्य व्योम __init ia64_native_iosapic_pcat_compat_init(व्योम);
बाह्य काष्ठा irq_chip *ia64_native_iosapic_get_irq_chip(अचिन्हित दीर्घ trigger);

अटल अंतरभूत अचिन्हित पूर्णांक
__ia64_native_iosapic_पढ़ो(अक्षर __iomem *iosapic, अचिन्हित पूर्णांक reg)
अणु
	ग_लिखोl(reg, iosapic + IOSAPIC_REG_SELECT);
	वापस पढ़ोl(iosapic + IOSAPIC_WINDOW);
पूर्ण

अटल अंतरभूत व्योम
__ia64_native_iosapic_ग_लिखो(अक्षर __iomem *iosapic, अचिन्हित पूर्णांक reg, u32 val)
अणु
	ग_लिखोl(reg, iosapic + IOSAPIC_REG_SELECT);
	ग_लिखोl(val, iosapic + IOSAPIC_WINDOW);
पूर्ण

अटल अंतरभूत व्योम iosapic_eoi(अक्षर __iomem *iosapic, u32 vector)
अणु
	ग_लिखोl(vector, iosapic + IOSAPIC_EOI);
पूर्ण

बाह्य व्योम __init iosapic_प्रणाली_init (पूर्णांक pcat_compat);
बाह्य पूर्णांक iosapic_init (अचिन्हित दीर्घ address, अचिन्हित पूर्णांक gsi_base);
बाह्य पूर्णांक iosapic_हटाओ (अचिन्हित पूर्णांक gsi_base);
बाह्य पूर्णांक gsi_to_irq (अचिन्हित पूर्णांक gsi);
बाह्य पूर्णांक iosapic_रेजिस्टर_पूर्णांकr (अचिन्हित पूर्णांक gsi, अचिन्हित दीर्घ polarity,
				  अचिन्हित दीर्घ trigger);
बाह्य व्योम iosapic_unरेजिस्टर_पूर्णांकr (अचिन्हित पूर्णांक irq);
बाह्य व्योम iosapic_override_isa_irq (अचिन्हित पूर्णांक isa_irq, अचिन्हित पूर्णांक gsi,
				      अचिन्हित दीर्घ polarity,
				      अचिन्हित दीर्घ trigger);
बाह्य पूर्णांक __init iosapic_रेजिस्टर_platक्रमm_पूर्णांकr (u32 पूर्णांक_type,
					   अचिन्हित पूर्णांक gsi,
					   पूर्णांक pmi_vector,
					   u16 eid, u16 id,
					   अचिन्हित दीर्घ polarity,
					   अचिन्हित दीर्घ trigger);

#अगर_घोषित CONFIG_NUMA
बाह्य व्योम map_iosapic_to_node (अचिन्हित पूर्णांक, पूर्णांक);
#पूर्ण_अगर

# endअगर /* !__ASSEMBLY__ */
#पूर्ण_अगर /* __ASM_IA64_IOSAPIC_H */
