<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * VMware vSockets Driver
 *
 * Copyright (C) 2007-2013 VMware, Inc. All rights reserved.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation version 2 and no later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License क्रम
 * more details.
 */

#अगर_अघोषित _UAPI_VM_SOCKETS_H
#घोषणा _UAPI_VM_SOCKETS_H

#समावेश <linux/socket.h>
#समावेश <linux/types.h>

/* Option name क्रम STREAM socket buffer size.  Use as the option name in
 * setsockopt(3) or माला_लोockopt(3) to set or get an अचिन्हित दीर्घ दीर्घ that
 * specअगरies the size of the buffer underlying a vSockets STREAM socket.
 * Value is clamped to the MIN and MAX.
 */

#घोषणा SO_VM_SOCKETS_BUFFER_SIZE 0

/* Option name क्रम STREAM socket minimum buffer size.  Use as the option name
 * in setsockopt(3) or माला_लोockopt(3) to set or get an अचिन्हित दीर्घ दीर्घ that
 * specअगरies the minimum size allowed क्रम the buffer underlying a vSockets
 * STREAM socket.
 */

#घोषणा SO_VM_SOCKETS_BUFFER_MIN_SIZE 1

/* Option name क्रम STREAM socket maximum buffer size.  Use as the option name
 * in setsockopt(3) or माला_लोockopt(3) to set or get an अचिन्हित दीर्घ दीर्घ
 * that specअगरies the maximum size allowed क्रम the buffer underlying a
 * vSockets STREAM socket.
 */

#घोषणा SO_VM_SOCKETS_BUFFER_MAX_SIZE 2

/* Option name क्रम socket peer's host-specअगरic VM ID.  Use as the option name
 * in माला_लोockopt(3) to get a host-specअगरic identअगरier क्रम the peer endpoपूर्णांक's
 * VM.  The identअगरier is a चिन्हित पूर्णांकeger.
 * Only available क्रम hypervisor endpoपूर्णांकs.
 */

#घोषणा SO_VM_SOCKETS_PEER_HOST_VM_ID 3

/* Option name क्रम determining अगर a socket is trusted.  Use as the option name
 * in माला_लोockopt(3) to determine अगर a socket is trusted.  The value is a
 * चिन्हित पूर्णांकeger.
 */

#घोषणा SO_VM_SOCKETS_TRUSTED 5

/* Option name क्रम STREAM socket connection समयout.  Use as the option name
 * in setsockopt(3) or माला_लोockopt(3) to set or get the connection
 * समयout क्रम a STREAM socket.
 */

#घोषणा SO_VM_SOCKETS_CONNECT_TIMEOUT 6

/* Option name क्रम using non-blocking send/receive.  Use as the option name
 * क्रम setsockopt(3) or माला_लोockopt(3) to set or get the non-blocking
 * transmit/receive flag क्रम a STREAM socket.  This flag determines whether
 * send() and recv() can be called in non-blocking contexts क्रम the given
 * socket.  The value is a चिन्हित पूर्णांकeger.
 *
 * This option is only relevant to kernel endpoपूर्णांकs, where descheduling the
 * thपढ़ो of execution is not allowed, क्रम example, जबतक holding a spinlock.
 * It is not to be confused with conventional non-blocking socket operations.
 *
 * Only available क्रम hypervisor endpoपूर्णांकs.
 */

#घोषणा SO_VM_SOCKETS_NONBLOCK_TXRX 7

/* The vSocket equivalent of INADDR_ANY.  This works क्रम the svm_cid field of
 * sockaddr_vm and indicates the context ID of the current endpoपूर्णांक.
 */

#घोषणा VMADDR_CID_ANY -1U

/* Bind to any available port.  Works क्रम the svm_port field of
 * sockaddr_vm.
 */

#घोषणा VMADDR_PORT_ANY -1U

/* Use this as the destination CID in an address when referring to the
 * hypervisor.  VMCI relies on it being 0, but this would be useful क्रम other
 * transports too.
 */

#घोषणा VMADDR_CID_HYPERVISOR 0

/* Use this as the destination CID in an address when referring to the
 * local communication (loopback).
 * (This was VMADDR_CID_RESERVED, but even VMCI करोesn't use it anymore,
 * it was a legacy value from an older release).
 */

#घोषणा VMADDR_CID_LOCAL 1

/* Use this as the destination CID in an address when referring to the host
 * (any process other than the hypervisor).  VMCI relies on it being 2, but
 * this would be useful क्रम other transports too.
 */

#घोषणा VMADDR_CID_HOST 2

/* The current शेष use हाल क्रम the vsock channel is the following:
 * local vsock communication between guest and host and nested VMs setup.
 * In addition to this, implicitly, the vsock packets are क्रमwarded to the host
 * अगर no host->guest vsock transport is set.
 *
 * Set this flag value in the sockaddr_vm corresponding field अगर the vsock
 * packets need to be always क्रमwarded to the host. Using this behavior,
 * vsock communication between sibling VMs can be setup.
 *
 * This way can explicitly distinguish between vsock channels created क्रम
 * dअगरferent use हालs, such as nested VMs (or local communication between
 * guest and host) and sibling VMs.
 *
 * The flag can be set in the connect logic in the user space application flow.
 * In the listen logic (from kernel space) the flag is set on the remote peer
 * address. This happens क्रम an incoming connection when it is routed from the
 * host and comes from the guest (local CID and remote CID > VMADDR_CID_HOST).
 */
#घोषणा VMADDR_FLAG_TO_HOST 0x01

/* Invalid vSockets version. */

#घोषणा VM_SOCKETS_INVALID_VERSION -1U

/* The epoch (first) component of the vSockets version.  A single byte
 * representing the epoch component of the vSockets version.
 */

#घोषणा VM_SOCKETS_VERSION_EPOCH(_v) (((_v) & 0xFF000000) >> 24)

/* The major (second) component of the vSockets version.   A single byte
 * representing the major component of the vSockets version.  Typically
 * changes क्रम every major release of a product.
 */

#घोषणा VM_SOCKETS_VERSION_MAJOR(_v) (((_v) & 0x00FF0000) >> 16)

/* The minor (third) component of the vSockets version.  Two bytes representing
 * the minor component of the vSockets version.
 */

#घोषणा VM_SOCKETS_VERSION_MINOR(_v) (((_v) & 0x0000FFFF))

/* Address काष्ठाure क्रम vSockets.   The address family should be set to
 * AF_VSOCK.  The काष्ठाure members should all align on their natural
 * boundaries without resorting to compiler packing directives.  The total size
 * of this काष्ठाure should be exactly the same as that of काष्ठा sockaddr.
 */

काष्ठा sockaddr_vm अणु
	__kernel_sa_family_t svm_family;
	अचिन्हित लघु svm_reserved1;
	अचिन्हित पूर्णांक svm_port;
	अचिन्हित पूर्णांक svm_cid;
	__u8 svm_flags;
	अचिन्हित अक्षर svm_zero[माप(काष्ठा sockaddr) -
			       माप(sa_family_t) -
			       माप(अचिन्हित लघु) -
			       माप(अचिन्हित पूर्णांक) -
			       माप(अचिन्हित पूर्णांक) -
			       माप(__u8)];
पूर्ण;

#घोषणा IOCTL_VM_SOCKETS_GET_LOCAL_CID		_IO(7, 0xb9)

#पूर्ण_अगर /* _UAPI_VM_SOCKETS_H */
