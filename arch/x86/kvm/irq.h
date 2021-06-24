<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * irq.h: in kernel पूर्णांकerrupt controller related definitions
 * Copyright (c) 2007, Intel Corporation.
 *
 * Authors:
 *   Yaozu (Eddie) Dong <Eddie.करोng@पूर्णांकel.com>
 */

#अगर_अघोषित __IRQ_H
#घोषणा __IRQ_H

#समावेश <linux/mm_types.h>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/kvm_host.h>
#समावेश <linux/spinlock.h>

#समावेश <kvm/iodev.h>
#समावेश "lapic.h"

#घोषणा PIC_NUM_PINS 16
#घोषणा SELECT_PIC(irq) \
	((irq) < 8 ? KVM_IRQCHIP_PIC_MASTER : KVM_IRQCHIP_PIC_SLAVE)

काष्ठा kvm;
काष्ठा kvm_vcpu;

काष्ठा kvm_kpic_state अणु
	u8 last_irr;	/* edge detection */
	u8 irr;		/* पूर्णांकerrupt request रेजिस्टर */
	u8 imr;		/* पूर्णांकerrupt mask रेजिस्टर */
	u8 isr;		/* पूर्णांकerrupt service रेजिस्टर */
	u8 priority_add;	/* highest irq priority */
	u8 irq_base;
	u8 पढ़ो_reg_select;
	u8 poll;
	u8 special_mask;
	u8 init_state;
	u8 स्वतः_eoi;
	u8 rotate_on_स्वतः_eoi;
	u8 special_fully_nested_mode;
	u8 init4;		/* true अगर 4 byte init */
	u8 elcr;		/* PIIX edge/trigger selection */
	u8 elcr_mask;
	u8 isr_ack;	/* पूर्णांकerrupt ack detection */
	काष्ठा kvm_pic *pics_state;
पूर्ण;

काष्ठा kvm_pic अणु
	spinlock_t lock;
	bool wakeup_needed;
	अचिन्हित pending_acks;
	काष्ठा kvm *kvm;
	काष्ठा kvm_kpic_state pics[2]; /* 0 is master pic, 1 is slave pic */
	पूर्णांक output;		/* पूर्णांकr from master PIC */
	काष्ठा kvm_io_device dev_master;
	काष्ठा kvm_io_device dev_slave;
	काष्ठा kvm_io_device dev_eclr;
	व्योम (*ack_notअगरier)(व्योम *opaque, पूर्णांक irq);
	अचिन्हित दीर्घ irq_states[PIC_NUM_PINS];
पूर्ण;

पूर्णांक kvm_pic_init(काष्ठा kvm *kvm);
व्योम kvm_pic_destroy(काष्ठा kvm *kvm);
पूर्णांक kvm_pic_पढ़ो_irq(काष्ठा kvm *kvm);
व्योम kvm_pic_update_irq(काष्ठा kvm_pic *s);

अटल अंतरभूत पूर्णांक irqchip_split(काष्ठा kvm *kvm)
अणु
	पूर्णांक mode = kvm->arch.irqchip_mode;

	/* Matches smp_wmb() when setting irqchip_mode */
	smp_rmb();
	वापस mode == KVM_IRQCHIP_SPLIT;
पूर्ण

अटल अंतरभूत पूर्णांक irqchip_kernel(काष्ठा kvm *kvm)
अणु
	पूर्णांक mode = kvm->arch.irqchip_mode;

	/* Matches smp_wmb() when setting irqchip_mode */
	smp_rmb();
	वापस mode == KVM_IRQCHIP_KERNEL;
पूर्ण

अटल अंतरभूत पूर्णांक pic_in_kernel(काष्ठा kvm *kvm)
अणु
	वापस irqchip_kernel(kvm);
पूर्ण

अटल अंतरभूत पूर्णांक irqchip_in_kernel(काष्ठा kvm *kvm)
अणु
	पूर्णांक mode = kvm->arch.irqchip_mode;

	/* Matches smp_wmb() when setting irqchip_mode */
	smp_rmb();
	वापस mode != KVM_IRQCHIP_NONE;
पूर्ण

व्योम kvm_inject_pending_समयr_irqs(काष्ठा kvm_vcpu *vcpu);
व्योम kvm_inject_apic_समयr_irqs(काष्ठा kvm_vcpu *vcpu);
व्योम kvm_apic_nmi_wd_deliver(काष्ठा kvm_vcpu *vcpu);
व्योम __kvm_migrate_apic_समयr(काष्ठा kvm_vcpu *vcpu);
व्योम __kvm_migrate_pit_समयr(काष्ठा kvm_vcpu *vcpu);
व्योम __kvm_migrate_समयrs(काष्ठा kvm_vcpu *vcpu);

पूर्णांक apic_has_pending_समयr(काष्ठा kvm_vcpu *vcpu);

पूर्णांक kvm_setup_शेष_irq_routing(काष्ठा kvm *kvm);
पूर्णांक kvm_setup_empty_irq_routing(काष्ठा kvm *kvm);
पूर्णांक kvm_irq_delivery_to_apic(काष्ठा kvm *kvm, काष्ठा kvm_lapic *src,
			     काष्ठा kvm_lapic_irq *irq,
			     काष्ठा dest_map *dest_map);

#पूर्ण_अगर
