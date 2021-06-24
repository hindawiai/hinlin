<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * VMware VMCI Driver
 *
 * Copyright (C) 2012 VMware, Inc. All rights reserved.
 */

#अगर_अघोषित _VMCI_DRIVER_H_
#घोषणा _VMCI_DRIVER_H_

#समावेश <linux/vmw_vmci_defs.h>
#समावेश <linux/रुको.h>

#समावेश "vmci_queue_pair.h"
#समावेश "vmci_context.h"

क्रमागत vmci_obj_type अणु
	VMCIOBJ_VMX_VM = 10,
	VMCIOBJ_CONTEXT,
	VMCIOBJ_SOCKET,
	VMCIOBJ_NOT_SET,
पूर्ण;

/* For storing VMCI काष्ठाures in file handles. */
काष्ठा vmci_obj अणु
	व्योम *ptr;
	क्रमागत vmci_obj_type type;
पूर्ण;

/*
 * Needed by other components of this module.  It's okay to have one global
 * instance of this because there can only ever be one VMCI device.  Our
 * भव hardware enक्रमces this.
 */
बाह्य काष्ठा pci_dev *vmci_pdev;

u32 vmci_get_context_id(व्योम);
पूर्णांक vmci_send_datagram(काष्ठा vmci_datagram *dg);
व्योम vmci_call_vsock_callback(bool is_host);

पूर्णांक vmci_host_init(व्योम);
व्योम vmci_host_निकास(व्योम);
bool vmci_host_code_active(व्योम);
पूर्णांक vmci_host_users(व्योम);

पूर्णांक vmci_guest_init(व्योम);
व्योम vmci_guest_निकास(व्योम);
bool vmci_guest_code_active(व्योम);
u32 vmci_get_vm_context_id(व्योम);

bool vmci_use_ppn64(व्योम);

#पूर्ण_अगर /* _VMCI_DRIVER_H_ */
