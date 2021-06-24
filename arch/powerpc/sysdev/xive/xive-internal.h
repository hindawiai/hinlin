<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright 2016,2017 IBM Corporation.
 */
#अगर_अघोषित __XIVE_INTERNAL_H
#घोषणा __XIVE_INTERNAL_H

/*
 * A "disabled" पूर्णांकerrupt should never fire, to catch problems
 * we set its logical number to this
 */
#घोषणा XIVE_BAD_IRQ		0x7fffffff
#घोषणा XIVE_MAX_IRQ		(XIVE_BAD_IRQ - 1)

/* Each CPU carry one of these with various per-CPU state */
काष्ठा xive_cpu अणु
#अगर_घोषित CONFIG_SMP
	/* HW irq number and data of IPI */
	u32 hw_ipi;
	काष्ठा xive_irq_data ipi_data;
#पूर्ण_अगर /* CONFIG_SMP */

	पूर्णांक chip_id;

	/* Queue datas. Only one is populated */
#घोषणा XIVE_MAX_QUEUES	8
	काष्ठा xive_q queue[XIVE_MAX_QUEUES];

	/*
	 * Pending mask. Each bit corresponds to a priority that
	 * potentially has pending पूर्णांकerrupts.
	 */
	u8 pending_prio;

	/* Cache of HW CPPR */
	u8 cppr;
पूर्ण;

/* Backend ops */
काष्ठा xive_ops अणु
	पूर्णांक	(*populate_irq_data)(u32 hw_irq, काष्ठा xive_irq_data *data);
	पूर्णांक 	(*configure_irq)(u32 hw_irq, u32 target, u8 prio, u32 sw_irq);
	पूर्णांक	(*get_irq_config)(u32 hw_irq, u32 *target, u8 *prio,
				  u32 *sw_irq);
	पूर्णांक	(*setup_queue)(अचिन्हित पूर्णांक cpu, काष्ठा xive_cpu *xc, u8 prio);
	व्योम	(*cleanup_queue)(अचिन्हित पूर्णांक cpu, काष्ठा xive_cpu *xc, u8 prio);
	व्योम	(*prepare_cpu)(अचिन्हित पूर्णांक cpu, काष्ठा xive_cpu *xc);
	व्योम	(*setup_cpu)(अचिन्हित पूर्णांक cpu, काष्ठा xive_cpu *xc);
	व्योम	(*tearकरोwn_cpu)(अचिन्हित पूर्णांक cpu, काष्ठा xive_cpu *xc);
	bool	(*match)(काष्ठा device_node *np);
	व्योम	(*shutकरोwn)(व्योम);

	व्योम	(*update_pending)(काष्ठा xive_cpu *xc);
	व्योम	(*sync_source)(u32 hw_irq);
	u64	(*esb_rw)(u32 hw_irq, u32 offset, u64 data, bool ग_लिखो);
#अगर_घोषित CONFIG_SMP
	पूर्णांक	(*get_ipi)(अचिन्हित पूर्णांक cpu, काष्ठा xive_cpu *xc);
	व्योम	(*put_ipi)(अचिन्हित पूर्णांक cpu, काष्ठा xive_cpu *xc);
#पूर्ण_अगर
	पूर्णांक	(*debug_show)(काष्ठा seq_file *m, व्योम *निजी);
	स्थिर अक्षर *name;
पूर्ण;

bool xive_core_init(काष्ठा device_node *np, स्थिर काष्ठा xive_ops *ops,
		    व्योम __iomem *area, u32 offset, u8 max_prio);
__be32 *xive_queue_page_alloc(अचिन्हित पूर्णांक cpu, u32 queue_shअगरt);
पूर्णांक xive_core_debug_init(व्योम);

अटल अंतरभूत u32 xive_alloc_order(u32 queue_shअगरt)
अणु
	वापस (queue_shअगरt > PAGE_SHIFT) ? (queue_shअगरt - PAGE_SHIFT) : 0;
पूर्ण

बाह्य bool xive_cmdline_disabled;

#पूर्ण_अगर /*  __XIVE_INTERNAL_H */
