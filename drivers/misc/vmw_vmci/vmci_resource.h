<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * VMware VMCI Driver
 *
 * Copyright (C) 2012 VMware, Inc. All rights reserved.
 */

#अगर_अघोषित _VMCI_RESOURCE_H_
#घोषणा _VMCI_RESOURCE_H_

#समावेश <linux/vmw_vmci_defs.h>
#समावेश <linux/types.h>

#समावेश "vmci_context.h"


क्रमागत vmci_resource_type अणु
	VMCI_RESOURCE_TYPE_ANY,
	VMCI_RESOURCE_TYPE_API,
	VMCI_RESOURCE_TYPE_GROUP,
	VMCI_RESOURCE_TYPE_DATAGRAM,
	VMCI_RESOURCE_TYPE_DOORBELL,
	VMCI_RESOURCE_TYPE_QPAIR_GUEST,
	VMCI_RESOURCE_TYPE_QPAIR_HOST
पूर्ण;

काष्ठा vmci_resource अणु
	काष्ठा vmci_handle handle;
	क्रमागत vmci_resource_type type;
	काष्ठा hlist_node node;
	काष्ठा kref kref;
	काष्ठा completion करोne;
पूर्ण;


पूर्णांक vmci_resource_add(काष्ठा vmci_resource *resource,
		      क्रमागत vmci_resource_type resource_type,
		      काष्ठा vmci_handle handle);

व्योम vmci_resource_हटाओ(काष्ठा vmci_resource *resource);

काष्ठा vmci_resource *
vmci_resource_by_handle(काष्ठा vmci_handle resource_handle,
			क्रमागत vmci_resource_type resource_type);

काष्ठा vmci_resource *vmci_resource_get(काष्ठा vmci_resource *resource);
पूर्णांक vmci_resource_put(काष्ठा vmci_resource *resource);

काष्ठा vmci_handle vmci_resource_handle(काष्ठा vmci_resource *resource);

#पूर्ण_अगर /* _VMCI_RESOURCE_H_ */
