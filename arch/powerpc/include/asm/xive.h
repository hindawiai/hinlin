<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright 2016,2017 IBM Corporation.
 */
#अगर_अघोषित _ASM_POWERPC_XIVE_H
#घोषणा _ASM_POWERPC_XIVE_H

#समावेश <यंत्र/opal-api.h>

#घोषणा XIVE_INVALID_VP	0xffffffff

#अगर_घोषित CONFIG_PPC_XIVE

/*
 * Thपढ़ो Interrupt Management Area (TIMA)
 *
 * This is a global MMIO region भागided in 4 pages of varying access
 * permissions, providing access to per-cpu पूर्णांकerrupt management
 * functions. It always identअगरies the CPU करोing the access based
 * on the PowerBus initiator ID, thus we always access via the
 * same offset regardless of where the code is executing
 */
बाह्य व्योम __iomem *xive_tima;
बाह्य अचिन्हित दीर्घ xive_tima_os;

/*
 * Offset in the TM area of our current execution level (provided by
 * the backend)
 */
बाह्य u32 xive_tima_offset;

/*
 * Per-irq data (irq_get_handler_data क्रम normal IRQs), IPIs
 * have it stored in the xive_cpu काष्ठाure. We also cache
 * क्रम normal पूर्णांकerrupts the current target CPU.
 *
 * This काष्ठाure is setup by the backend क्रम each पूर्णांकerrupt.
 */
काष्ठा xive_irq_data अणु
	u64 flags;
	u64 eoi_page;
	व्योम __iomem *eoi_mmio;
	u64 trig_page;
	व्योम __iomem *trig_mmio;
	u32 esb_shअगरt;
	पूर्णांक src_chip;
	u32 hw_irq;

	/* Setup/used by frontend */
	पूर्णांक target;
	/*
	 * saved_p means that there is a queue entry क्रम this पूर्णांकerrupt
	 * in some CPU's queue (not including guest vcpu queues), even
	 * अगर P is not set in the source ESB.
	 * stale_p means that there is no queue entry क्रम this पूर्णांकerrupt
	 * in some CPU's queue, even अगर P is set in the source ESB.
	 */
	bool saved_p;
	bool stale_p;
पूर्ण;
#घोषणा XIVE_IRQ_FLAG_STORE_EOI	0x01
#घोषणा XIVE_IRQ_FLAG_LSI	0x02
/* #घोषणा XIVE_IRQ_FLAG_SHIFT_BUG	0x04 */ /* P9 DD1.0 workaround */
/* #घोषणा XIVE_IRQ_FLAG_MASK_FW	0x08 */ /* P9 DD1.0 workaround */
/* #घोषणा XIVE_IRQ_FLAG_EOI_FW	0x10 */ /* P9 DD1.0 workaround */
#घोषणा XIVE_IRQ_FLAG_H_INT_ESB	0x20

/* Special flag set by KVM क्रम excalation पूर्णांकerrupts */
#घोषणा XIVE_IRQ_FLAG_NO_EOI	0x80

#घोषणा XIVE_INVALID_CHIP_ID	-1

/* A queue tracking काष्ठाure in a CPU */
काष्ठा xive_q अणु
	__be32 			*qpage;
	u32			msk;
	u32			idx;
	u32			toggle;
	u64			eoi_phys;
	u32			esc_irq;
	atomic_t		count;
	atomic_t		pending_count;
	u64			guest_qaddr;
	u32			guest_qshअगरt;
पूर्ण;

/* Global enable flags क्रम the XIVE support */
बाह्य bool __xive_enabled;

अटल अंतरभूत bool xive_enabled(व्योम) अणु वापस __xive_enabled; पूर्ण

bool xive_spapr_init(व्योम);
bool xive_native_init(व्योम);
व्योम xive_smp_probe(व्योम);
पूर्णांक  xive_smp_prepare_cpu(अचिन्हित पूर्णांक cpu);
व्योम xive_smp_setup_cpu(व्योम);
व्योम xive_smp_disable_cpu(व्योम);
व्योम xive_tearकरोwn_cpu(व्योम);
व्योम xive_shutकरोwn(व्योम);
व्योम xive_flush_पूर्णांकerrupt(व्योम);

/* xmon hook */
व्योम xmon_xive_करो_dump(पूर्णांक cpu);
पूर्णांक xmon_xive_get_irq_config(u32 hw_irq, काष्ठा irq_data *d);
व्योम xmon_xive_get_irq_all(व्योम);

/* APIs used by KVM */
u32 xive_native_शेष_eq_shअगरt(व्योम);
u32 xive_native_alloc_vp_block(u32 max_vcpus);
व्योम xive_native_मुक्त_vp_block(u32 vp_base);
पूर्णांक xive_native_populate_irq_data(u32 hw_irq,
				  काष्ठा xive_irq_data *data);
व्योम xive_cleanup_irq_data(काष्ठा xive_irq_data *xd);
व्योम xive_native_मुक्त_irq(u32 irq);
पूर्णांक xive_native_configure_irq(u32 hw_irq, u32 target, u8 prio, u32 sw_irq);

पूर्णांक xive_native_configure_queue(u32 vp_id, काष्ठा xive_q *q, u8 prio,
				__be32 *qpage, u32 order, bool can_escalate);
व्योम xive_native_disable_queue(u32 vp_id, काष्ठा xive_q *q, u8 prio);

व्योम xive_native_sync_source(u32 hw_irq);
व्योम xive_native_sync_queue(u32 hw_irq);
bool is_xive_irq(काष्ठा irq_chip *chip);
पूर्णांक xive_native_enable_vp(u32 vp_id, bool single_escalation);
पूर्णांक xive_native_disable_vp(u32 vp_id);
पूर्णांक xive_native_get_vp_info(u32 vp_id, u32 *out_cam_id, u32 *out_chip_id);
bool xive_native_has_single_escalation(व्योम);

पूर्णांक xive_native_get_queue_info(u32 vp_id, uपूर्णांक32_t prio,
			       u64 *out_qpage,
			       u64 *out_qsize,
			       u64 *out_qeoi_page,
			       u32 *out_escalate_irq,
			       u64 *out_qflags);

पूर्णांक xive_native_get_queue_state(u32 vp_id, uपूर्णांक32_t prio, u32 *qtoggle,
				u32 *qindex);
पूर्णांक xive_native_set_queue_state(u32 vp_id, uपूर्णांक32_t prio, u32 qtoggle,
				u32 qindex);
पूर्णांक xive_native_get_vp_state(u32 vp_id, u64 *out_state);
bool xive_native_has_queue_state_support(व्योम);
बाह्य u32 xive_native_alloc_irq_on_chip(u32 chip_id);

अटल अंतरभूत u32 xive_native_alloc_irq(व्योम)
अणु
	वापस xive_native_alloc_irq_on_chip(OPAL_XIVE_ANY_CHIP);
पूर्ण

#अन्यथा

अटल अंतरभूत bool xive_enabled(व्योम) अणु वापस false; पूर्ण

अटल अंतरभूत bool xive_spapr_init(व्योम) अणु वापस false; पूर्ण
अटल अंतरभूत bool xive_native_init(व्योम) अणु वापस false; पूर्ण
अटल अंतरभूत व्योम xive_smp_probe(व्योम) अणु पूर्ण
अटल अंतरभूत पूर्णांक  xive_smp_prepare_cpu(अचिन्हित पूर्णांक cpu) अणु वापस -EINVAL; पूर्ण
अटल अंतरभूत व्योम xive_smp_setup_cpu(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम xive_smp_disable_cpu(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम xive_shutकरोwn(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम xive_flush_पूर्णांकerrupt(व्योम) अणु पूर्ण

अटल अंतरभूत u32 xive_native_alloc_vp_block(u32 max_vcpus) अणु वापस XIVE_INVALID_VP; पूर्ण
अटल अंतरभूत व्योम xive_native_मुक्त_vp_block(u32 vp_base) अणु पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_POWERPC_XIVE_H */
