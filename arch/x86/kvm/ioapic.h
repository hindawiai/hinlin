<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __KVM_IO_APIC_H
#घोषणा __KVM_IO_APIC_H

#समावेश <linux/kvm_host.h>
#समावेश <kvm/iodev.h>
#समावेश "irq.h"

काष्ठा kvm;
काष्ठा kvm_vcpu;

#घोषणा IOAPIC_NUM_PINS  KVM_IOAPIC_NUM_PINS
#घोषणा MAX_NR_RESERVED_IOAPIC_PINS KVM_MAX_IRQ_ROUTES
#घोषणा IOAPIC_VERSION_ID 0x11	/* IOAPIC version */
#घोषणा IOAPIC_EDGE_TRIG  0
#घोषणा IOAPIC_LEVEL_TRIG 1

#घोषणा IOAPIC_DEFAULT_BASE_ADDRESS  0xfec00000
#घोषणा IOAPIC_MEM_LENGTH            0x100

/* Direct रेजिस्टरs. */
#घोषणा IOAPIC_REG_SELECT  0x00
#घोषणा IOAPIC_REG_WINDOW  0x10

/* Indirect रेजिस्टरs. */
#घोषणा IOAPIC_REG_APIC_ID 0x00	/* x86 IOAPIC only */
#घोषणा IOAPIC_REG_VERSION 0x01
#घोषणा IOAPIC_REG_ARB_ID  0x02	/* x86 IOAPIC only */

/*ioapic delivery mode*/
#घोषणा	IOAPIC_FIXED			0x0
#घोषणा	IOAPIC_LOWEST_PRIORITY		0x1
#घोषणा	IOAPIC_PMI			0x2
#घोषणा	IOAPIC_NMI			0x4
#घोषणा	IOAPIC_INIT			0x5
#घोषणा	IOAPIC_EXTINT			0x7

#अगर_घोषित CONFIG_X86
#घोषणा RTC_GSI 8
#अन्यथा
#घोषणा RTC_GSI -1U
#पूर्ण_अगर

काष्ठा dest_map अणु
	/* vcpu biपंचांगap where IRQ has been sent */
	DECLARE_BITMAP(map, KVM_MAX_VCPU_ID);

	/*
	 * Vector sent to a given vcpu, only valid when
	 * the vcpu's bit in map is set
	 */
	u8 vectors[KVM_MAX_VCPU_ID];
पूर्ण;


काष्ठा rtc_status अणु
	पूर्णांक pending_eoi;
	काष्ठा dest_map dest_map;
पूर्ण;

जोड़ kvm_ioapic_redirect_entry अणु
	u64 bits;
	काष्ठा अणु
		u8 vector;
		u8 delivery_mode:3;
		u8 dest_mode:1;
		u8 delivery_status:1;
		u8 polarity:1;
		u8 remote_irr:1;
		u8 trig_mode:1;
		u8 mask:1;
		u8 reserve:7;
		u8 reserved[4];
		u8 dest_id;
	पूर्ण fields;
पूर्ण;

काष्ठा kvm_ioapic अणु
	u64 base_address;
	u32 ioregsel;
	u32 id;
	u32 irr;
	u32 pad;
	जोड़ kvm_ioapic_redirect_entry redirtbl[IOAPIC_NUM_PINS];
	अचिन्हित दीर्घ irq_states[IOAPIC_NUM_PINS];
	काष्ठा kvm_io_device dev;
	काष्ठा kvm *kvm;
	व्योम (*ack_notअगरier)(व्योम *opaque, पूर्णांक irq);
	spinlock_t lock;
	काष्ठा rtc_status rtc_status;
	काष्ठा delayed_work eoi_inject;
	u32 irq_eoi[IOAPIC_NUM_PINS];
	u32 irr_delivered;
पूर्ण;

#अगर_घोषित DEBUG
#घोषणा ASSERT(x)  							\
करो अणु									\
	अगर (!(x)) अणु							\
		prपूर्णांकk(KERN_EMERG "assertion failed %s: %d: %s\n",	\
		       __खाता__, __LINE__, #x);				\
		BUG();							\
	पूर्ण								\
पूर्ण जबतक (0)
#अन्यथा
#घोषणा ASSERT(x) करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक ioapic_in_kernel(काष्ठा kvm *kvm)
अणु
	वापस irqchip_kernel(kvm);
पूर्ण

व्योम kvm_rtc_eoi_tracking_restore_one(काष्ठा kvm_vcpu *vcpu);
व्योम kvm_ioapic_update_eoi(काष्ठा kvm_vcpu *vcpu, पूर्णांक vector,
			पूर्णांक trigger_mode);
पूर्णांक kvm_ioapic_init(काष्ठा kvm *kvm);
व्योम kvm_ioapic_destroy(काष्ठा kvm *kvm);
पूर्णांक kvm_ioapic_set_irq(काष्ठा kvm_ioapic *ioapic, पूर्णांक irq, पूर्णांक irq_source_id,
		       पूर्णांक level, bool line_status);
व्योम kvm_ioapic_clear_all(काष्ठा kvm_ioapic *ioapic, पूर्णांक irq_source_id);
व्योम kvm_get_ioapic(काष्ठा kvm *kvm, काष्ठा kvm_ioapic_state *state);
व्योम kvm_set_ioapic(काष्ठा kvm *kvm, काष्ठा kvm_ioapic_state *state);
व्योम kvm_ioapic_scan_entry(काष्ठा kvm_vcpu *vcpu,
			   uदीर्घ *ioapic_handled_vectors);
व्योम kvm_scan_ioapic_routes(काष्ठा kvm_vcpu *vcpu,
			    uदीर्घ *ioapic_handled_vectors);
#पूर्ण_अगर
