<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 * nmi.h
 *
 * NMI callback registration and reason codes.
 *
 * Copyright (c) 2005, Keir Fraser <keir@xensource.com>
 */

#अगर_अघोषित __XEN_PUBLIC_NMI_H__
#घोषणा __XEN_PUBLIC_NMI_H__

#समावेश <xen/पूर्णांकerface/xen.h>

/*
 * NMI reason codes:
 * Currently these are x86-specअगरic, stored in arch_shared_info.nmi_reason.
 */
 /* I/O-check error reported via ISA port 0x61, bit 6. */
#घोषणा _XEN_NMIREASON_io_error     0
#घोषणा XEN_NMIREASON_io_error      (1UL << _XEN_NMIREASON_io_error)
 /* PCI SERR reported via ISA port 0x61, bit 7. */
#घोषणा _XEN_NMIREASON_pci_serr     1
#घोषणा XEN_NMIREASON_pci_serr      (1UL << _XEN_NMIREASON_pci_serr)
 /* Unknown hardware-generated NMI. */
#घोषणा _XEN_NMIREASON_unknown      2
#घोषणा XEN_NMIREASON_unknown       (1UL << _XEN_NMIREASON_unknown)

/*
 * दीर्घ nmi_op(अचिन्हित पूर्णांक cmd, व्योम *arg)
 * NB. All ops वापस zero on success, अन्यथा a negative error code.
 */

/*
 * Register NMI callback क्रम this (calling) VCPU. Currently this only makes
 * sense क्रम करोमुख्य 0, vcpu 0. All other callers will be वापसed EINVAL.
 * arg == poपूर्णांकer to xennmi_callback काष्ठाure.
 */
#घोषणा XENNMI_रेजिस्टर_callback   0
काष्ठा xennmi_callback अणु
    अचिन्हित दीर्घ handler_address;
    अचिन्हित दीर्घ pad;
पूर्ण;
DEFINE_GUEST_HANDLE_STRUCT(xennmi_callback);

/*
 * Deरेजिस्टर NMI callback क्रम this (calling) VCPU.
 * arg == शून्य.
 */
#घोषणा XENNMI_unरेजिस्टर_callback 1

#पूर्ण_अगर /* __XEN_PUBLIC_NMI_H__ */
