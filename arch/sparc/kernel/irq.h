<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#समावेश <linux/platक्रमm_device.h>

#समावेश <यंत्र/cpu_type.h>

काष्ठा irq_bucket अणु
        काष्ठा irq_bucket *next;
        अचिन्हित पूर्णांक real_irq;
        अचिन्हित पूर्णांक irq;
        अचिन्हित पूर्णांक pil;
पूर्ण;

#घोषणा SUN4M_HARD_INT(x)       (0x000000001 << (x))
#घोषणा SUN4M_SOFT_INT(x)       (0x000010000 << (x))

#घोषणा SUN4D_MAX_BOARD 10
#घोषणा SUN4D_MAX_IRQ ((SUN4D_MAX_BOARD + 2) << 5)

/* Map between the irq identअगरier used in hw to the
 * irq_bucket. The map is sufficient large to hold
 * the sun4d hw identअगरiers.
 */
बाह्य काष्ठा irq_bucket *irq_map[SUN4D_MAX_IRQ];


/* sun4m specअगरic type definitions */

/* This maps direct to CPU specअगरic पूर्णांकerrupt रेजिस्टरs */
काष्ठा sun4m_irq_percpu अणु
	u32	pending;
	u32	clear;
	u32	set;
पूर्ण;

/* This maps direct to global पूर्णांकerrupt रेजिस्टरs */
काष्ठा sun4m_irq_global अणु
	u32	pending;
	u32	mask;
	u32	mask_clear;
	u32	mask_set;
	u32	पूर्णांकerrupt_target;
पूर्ण;

बाह्य काष्ठा sun4m_irq_percpu __iomem *sun4m_irq_percpu[SUN4M_NCPUS];
बाह्य काष्ठा sun4m_irq_global __iomem *sun4m_irq_global;

/* The following definitions describe the inभागidual platक्रमm features: */
#घोषणा FEAT_L10_CLOCKSOURCE (1 << 0) /* L10 समयr is used as a घड़ीsource */
#घोषणा FEAT_L10_CLOCKEVENT  (1 << 1) /* L10 समयr is used as a घड़ीevent */
#घोषणा FEAT_L14_ONESHOT     (1 << 2) /* L14 समयr घड़ीevent can oneshot */

/*
 * Platक्रमm specअगरic configuration
 * The inभागidual platक्रमms assign their platक्रमm
 * specअगरics in their init functions.
 */
काष्ठा sparc_config अणु
	व्योम (*init_समयrs)(व्योम);
	अचिन्हित पूर्णांक (*build_device_irq)(काष्ठा platक्रमm_device *op,
	                                 अचिन्हित पूर्णांक real_irq);

	/* generic घड़ीevent features - see FEAT_* above */
	पूर्णांक features;

	/* घड़ी rate used क्रम घड़ी event समयr */
	पूर्णांक घड़ी_rate;

	/* one period क्रम घड़ी source समयr */
	अचिन्हित पूर्णांक cs_period;

	/* function to obtain offsett क्रम cs period */
	अचिन्हित पूर्णांक (*get_cycles_offset)(व्योम);

	व्योम (*clear_घड़ी_irq)(व्योम);
	व्योम (*load_profile_irq)(पूर्णांक cpu, अचिन्हित पूर्णांक limit);
पूर्ण;
बाह्य काष्ठा sparc_config sparc_config;

अचिन्हित पूर्णांक irq_alloc(अचिन्हित पूर्णांक real_irq, अचिन्हित पूर्णांक pil);
व्योम irq_link(अचिन्हित पूर्णांक irq);
व्योम irq_unlink(अचिन्हित पूर्णांक irq);
व्योम handler_irq(अचिन्हित पूर्णांक pil, काष्ठा pt_regs *regs);

अचिन्हित दीर्घ leon_get_irqmask(अचिन्हित पूर्णांक irq);

/* irq_32.c */
व्योम sparc_floppy_irq(पूर्णांक irq, व्योम *dev_id, काष्ठा pt_regs *regs);

/* sun4m_irq.c */
व्योम sun4m_nmi(काष्ठा pt_regs *regs);

/* sun4d_irq.c */
व्योम sun4d_handler_irq(अचिन्हित पूर्णांक pil, काष्ठा pt_regs *regs);

#अगर_घोषित CONFIG_SMP

/* All SUN4D IPIs are sent on this IRQ, may be shared with hard IRQs */
#घोषणा SUN4D_IPI_IRQ 13

व्योम sun4d_ipi_पूर्णांकerrupt(व्योम);

#पूर्ण_अगर
