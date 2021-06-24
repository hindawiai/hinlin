<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *
 * irqfd: Allows an fd to be used to inject an पूर्णांकerrupt to the guest
 * Credit goes to Avi Kivity क्रम the original idea.
 */

#अगर_अघोषित __LINUX_KVM_IRQFD_H
#घोषणा __LINUX_KVM_IRQFD_H

#समावेश <linux/kvm_host.h>
#समावेश <linux/poll.h>

/*
 * Resampling irqfds are a special variety of irqfds used to emulate
 * level triggered पूर्णांकerrupts.  The पूर्णांकerrupt is निश्चितed on eventfd
 * trigger.  On acknowledgment through the irq ack notअगरier, the
 * पूर्णांकerrupt is de-निश्चितed and userspace is notअगरied through the
 * resamplefd.  All resamplers on the same gsi are de-निश्चितed
 * together, so we करोn't need to track the state of each inभागidual
 * user.  We can also thereक्रमe share the same irq source ID.
 */
काष्ठा kvm_kernel_irqfd_resampler अणु
	काष्ठा kvm *kvm;
	/*
	 * List of resampling काष्ठा _irqfd objects sharing this gsi.
	 * RCU list modअगरied under kvm->irqfds.resampler_lock
	 */
	काष्ठा list_head list;
	काष्ठा kvm_irq_ack_notअगरier notअगरier;
	/*
	 * Entry in list of kvm->irqfd.resampler_list.  Use क्रम sharing
	 * resamplers among irqfds on the same gsi.
	 * Accessed and modअगरied under kvm->irqfds.resampler_lock
	 */
	काष्ठा list_head link;
पूर्ण;

काष्ठा kvm_kernel_irqfd अणु
	/* Used क्रम MSI fast-path */
	काष्ठा kvm *kvm;
	रुको_queue_entry_t रुको;
	/* Update side is रक्षित by irqfds.lock */
	काष्ठा kvm_kernel_irq_routing_entry irq_entry;
	seqcount_spinlock_t irq_entry_sc;
	/* Used क्रम level IRQ fast-path */
	पूर्णांक gsi;
	काष्ठा work_काष्ठा inject;
	/* The resampler used by this irqfd (resampler-only) */
	काष्ठा kvm_kernel_irqfd_resampler *resampler;
	/* Eventfd notअगरied on resample (resampler-only) */
	काष्ठा eventfd_ctx *resamplefd;
	/* Entry in list of irqfds क्रम a resampler (resampler-only) */
	काष्ठा list_head resampler_link;
	/* Used क्रम setup/shutकरोwn */
	काष्ठा eventfd_ctx *eventfd;
	काष्ठा list_head list;
	poll_table pt;
	काष्ठा work_काष्ठा shutकरोwn;
	काष्ठा irq_bypass_consumer consumer;
	काष्ठा irq_bypass_producer *producer;
पूर्ण;

#पूर्ण_अगर /* __LINUX_KVM_IRQFD_H */
