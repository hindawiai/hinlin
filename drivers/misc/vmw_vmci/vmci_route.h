<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * VMware VMCI Driver
 *
 * Copyright (C) 2012 VMware, Inc. All rights reserved.
 */

#अगर_अघोषित _VMCI_ROUTE_H_
#घोषणा _VMCI_ROUTE_H_

#समावेश <linux/vmw_vmci_defs.h>

क्रमागत vmci_route अणु
	VMCI_ROUTE_NONE,
	VMCI_ROUTE_AS_HOST,
	VMCI_ROUTE_AS_GUEST,
पूर्ण;

पूर्णांक vmci_route(काष्ठा vmci_handle *src, स्थिर काष्ठा vmci_handle *dst,
	       bool from_guest, क्रमागत vmci_route *route);

#पूर्ण_अगर /* _VMCI_ROUTE_H_ */
