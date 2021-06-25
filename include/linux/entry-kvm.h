<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_ENTRYKVM_H
#घोषणा __LINUX_ENTRYKVM_H

#समावेश <linux/entry-common.h>
#समावेश <linux/tick.h>

/* Transfer to guest mode work */
#अगर_घोषित CONFIG_KVM_XFER_TO_GUEST_WORK

#अगर_अघोषित ARCH_XFER_TO_GUEST_MODE_WORK
# define ARCH_XFER_TO_GUEST_MODE_WORK	(0)
#पूर्ण_अगर

#घोषणा XFER_TO_GUEST_MODE_WORK						\
	(_TIF_NEED_RESCHED | _TIF_SIGPENDING | _TIF_NOTIFY_SIGNAL |	\
	 _TIF_NOTIFY_RESUME | ARCH_XFER_TO_GUEST_MODE_WORK)

काष्ठा kvm_vcpu;

/**
 * arch_xfer_to_guest_mode_handle_work - Architecture specअगरic xfer to guest
 *					 mode work handling function.
 * @vcpu:	Poपूर्णांकer to current's VCPU data
 * @ti_work:	Cached TIF flags gathered in xfer_to_guest_mode_handle_work()
 *
 * Invoked from xfer_to_guest_mode_handle_work(). Defaults to NOOP. Can be
 * replaced by architecture specअगरic code.
 */
अटल अंतरभूत पूर्णांक arch_xfer_to_guest_mode_handle_work(काष्ठा kvm_vcpu *vcpu,
						      अचिन्हित दीर्घ ti_work);

#अगर_अघोषित arch_xfer_to_guest_mode_work
अटल अंतरभूत पूर्णांक arch_xfer_to_guest_mode_handle_work(काष्ठा kvm_vcpu *vcpu,
						      अचिन्हित दीर्घ ti_work)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

/**
 * xfer_to_guest_mode_handle_work - Check and handle pending work which needs
 *				    to be handled beक्रमe going to guest mode
 * @vcpu:	Poपूर्णांकer to current's VCPU data
 *
 * Returns: 0 or an error code
 */
पूर्णांक xfer_to_guest_mode_handle_work(काष्ठा kvm_vcpu *vcpu);

/**
 * xfer_to_guest_mode_prepare - Perक्रमm last minute preparation work that
 *				need to be handled जबतक IRQs are disabled
 *				upon entering to guest.
 *
 * Has to be invoked with पूर्णांकerrupts disabled beक्रमe the last call
 * to xfer_to_guest_mode_work_pending().
 */
अटल अंतरभूत व्योम xfer_to_guest_mode_prepare(व्योम)
अणु
	lockdep_निश्चित_irqs_disabled();
	tick_nohz_user_enter_prepare();
पूर्ण

/**
 * __xfer_to_guest_mode_work_pending - Check अगर work is pending
 *
 * Returns: True अगर work pending, False otherwise.
 *
 * Bare variant of xfer_to_guest_mode_work_pending(). Can be called from
 * पूर्णांकerrupt enabled code क्रम racy quick checks with care.
 */
अटल अंतरभूत bool __xfer_to_guest_mode_work_pending(व्योम)
अणु
	अचिन्हित दीर्घ ti_work = READ_ONCE(current_thपढ़ो_info()->flags);

	वापस !!(ti_work & XFER_TO_GUEST_MODE_WORK);
पूर्ण

/**
 * xfer_to_guest_mode_work_pending - Check अगर work is pending which needs to be
 *				     handled beक्रमe वापसing to guest mode
 *
 * Returns: True अगर work pending, False otherwise.
 *
 * Has to be invoked with पूर्णांकerrupts disabled beक्रमe the transition to
 * guest mode.
 */
अटल अंतरभूत bool xfer_to_guest_mode_work_pending(व्योम)
अणु
	lockdep_निश्चित_irqs_disabled();
	वापस __xfer_to_guest_mode_work_pending();
पूर्ण
#पूर्ण_अगर /* CONFIG_KVM_XFER_TO_GUEST_WORK */

#पूर्ण_अगर
