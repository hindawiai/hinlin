<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * VMware vSockets Driver
 *
 * Copyright (C) 2007-2013 VMware, Inc. All rights reserved.
 */

#अगर_अघोषित _VSOCK_ADDR_H_
#घोषणा _VSOCK_ADDR_H_

#समावेश <uapi/linux/vm_sockets.h>

व्योम vsock_addr_init(काष्ठा sockaddr_vm *addr, u32 cid, u32 port);
पूर्णांक vsock_addr_validate(स्थिर काष्ठा sockaddr_vm *addr);
bool vsock_addr_bound(स्थिर काष्ठा sockaddr_vm *addr);
व्योम vsock_addr_unbind(काष्ठा sockaddr_vm *addr);
bool vsock_addr_equals_addr(स्थिर काष्ठा sockaddr_vm *addr,
			    स्थिर काष्ठा sockaddr_vm *other);
पूर्णांक vsock_addr_cast(स्थिर काष्ठा sockaddr *addr, माप_प्रकार len,
		    काष्ठा sockaddr_vm **out_addr);

#पूर्ण_अगर
