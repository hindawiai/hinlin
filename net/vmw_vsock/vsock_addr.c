<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * VMware vSockets Driver
 *
 * Copyright (C) 2007-2012 VMware, Inc. All rights reserved.
 */

#समावेश <linux/types.h>
#समावेश <linux/socket.h>
#समावेश <linux/मानकघोष.स>
#समावेश <net/sock.h>
#समावेश <net/vsock_addr.h>

व्योम vsock_addr_init(काष्ठा sockaddr_vm *addr, u32 cid, u32 port)
अणु
	स_रखो(addr, 0, माप(*addr));
	addr->svm_family = AF_VSOCK;
	addr->svm_cid = cid;
	addr->svm_port = port;
पूर्ण
EXPORT_SYMBOL_GPL(vsock_addr_init);

पूर्णांक vsock_addr_validate(स्थिर काष्ठा sockaddr_vm *addr)
अणु
	__u8 svm_valid_flags = VMADDR_FLAG_TO_HOST;

	अगर (!addr)
		वापस -EFAULT;

	अगर (addr->svm_family != AF_VSOCK)
		वापस -EAFNOSUPPORT;

	अगर (addr->svm_flags & ~svm_valid_flags)
		वापस -EINVAL;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(vsock_addr_validate);

bool vsock_addr_bound(स्थिर काष्ठा sockaddr_vm *addr)
अणु
	वापस addr->svm_port != VMADDR_PORT_ANY;
पूर्ण
EXPORT_SYMBOL_GPL(vsock_addr_bound);

व्योम vsock_addr_unbind(काष्ठा sockaddr_vm *addr)
अणु
	vsock_addr_init(addr, VMADDR_CID_ANY, VMADDR_PORT_ANY);
पूर्ण
EXPORT_SYMBOL_GPL(vsock_addr_unbind);

bool vsock_addr_equals_addr(स्थिर काष्ठा sockaddr_vm *addr,
			    स्थिर काष्ठा sockaddr_vm *other)
अणु
	वापस addr->svm_cid == other->svm_cid &&
		addr->svm_port == other->svm_port;
पूर्ण
EXPORT_SYMBOL_GPL(vsock_addr_equals_addr);

पूर्णांक vsock_addr_cast(स्थिर काष्ठा sockaddr *addr,
		    माप_प्रकार len, काष्ठा sockaddr_vm **out_addr)
अणु
	अगर (len < माप(**out_addr))
		वापस -EFAULT;

	*out_addr = (काष्ठा sockaddr_vm *)addr;
	वापस vsock_addr_validate(*out_addr);
पूर्ण
EXPORT_SYMBOL_GPL(vsock_addr_cast);
