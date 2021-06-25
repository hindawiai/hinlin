<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __I8254_H
#घोषणा __I8254_H

#समावेश <linux/kthपढ़ो.h>

#समावेश <kvm/iodev.h>

काष्ठा kvm_kpit_channel_state अणु
	u32 count; /* can be 65536 */
	u16 latched_count;
	u8 count_latched;
	u8 status_latched;
	u8 status;
	u8 पढ़ो_state;
	u8 ग_लिखो_state;
	u8 ग_लिखो_latch;
	u8 rw_mode;
	u8 mode;
	u8 bcd; /* not supported */
	u8 gate; /* समयr start */
	kसमय_प्रकार count_load_समय;
पूर्ण;

काष्ठा kvm_kpit_state अणु
	/* All members beक्रमe "struct mutex lock" are रक्षित by the lock. */
	काष्ठा kvm_kpit_channel_state channels[3];
	u32 flags;
	bool is_periodic;
	s64 period; 				/* unit: ns */
	काष्ठा hrसमयr समयr;
	u32    speaker_data_on;

	काष्ठा mutex lock;
	atomic_t reinject;
	atomic_t pending; /* accumulated triggered समयrs */
	atomic_t irq_ack;
	काष्ठा kvm_irq_ack_notअगरier irq_ack_notअगरier;
पूर्ण;

काष्ठा kvm_pit अणु
	काष्ठा kvm_io_device dev;
	काष्ठा kvm_io_device speaker_dev;
	काष्ठा kvm *kvm;
	काष्ठा kvm_kpit_state pit_state;
	पूर्णांक irq_source_id;
	काष्ठा kvm_irq_mask_notअगरier mask_notअगरier;
	काष्ठा kthपढ़ो_worker *worker;
	काष्ठा kthपढ़ो_work expired;
पूर्ण;

#घोषणा KVM_PIT_BASE_ADDRESS	    0x40
#घोषणा KVM_SPEAKER_BASE_ADDRESS    0x61
#घोषणा KVM_PIT_MEM_LENGTH	    4
#घोषणा KVM_PIT_FREQ		    1193181
#घोषणा KVM_MAX_PIT_INTR_INTERVAL   HZ / 100
#घोषणा KVM_PIT_CHANNEL_MASK	    0x3

काष्ठा kvm_pit *kvm_create_pit(काष्ठा kvm *kvm, u32 flags);
व्योम kvm_मुक्त_pit(काष्ठा kvm *kvm);

व्योम kvm_pit_load_count(काष्ठा kvm_pit *pit, पूर्णांक channel, u32 val,
		पूर्णांक hpet_legacy_start);
व्योम kvm_pit_set_reinject(काष्ठा kvm_pit *pit, bool reinject);

#पूर्ण_अगर
