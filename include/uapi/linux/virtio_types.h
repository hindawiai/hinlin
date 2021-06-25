<शैली गुरु>
#अगर_अघोषित _UAPI_LINUX_VIRTIO_TYPES_H
#घोषणा _UAPI_LINUX_VIRTIO_TYPES_H
/* Type definitions क्रम virtio implementations.
 *
 * This header is BSD licensed so anyone can use the definitions to implement
 * compatible drivers/servers.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    करोcumentation and/or other materials provided with the distribution.
 * 3. Neither the name of IBM nor the names of its contributors
 *    may be used to enकरोrse or promote products derived from this software
 *    without specअगरic prior written permission.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL IBM OR CONTRIBUTORS BE LIABLE
 * FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * Copyright (C) 2014 Red Hat, Inc.
 * Author: Michael S. Tsirkin <mst@redhat.com>
 */
#समावेश <linux/types.h>

/*
 * __virtioअणु16,32,64पूर्ण have the following meaning:
 * - __uअणु16,32,64पूर्ण क्रम virtio devices in legacy mode, accessed in native endian
 * - __leअणु16,32,64पूर्ण क्रम standard-compliant virtio devices
 */

प्रकार __u16 __bitwise __virtio16;
प्रकार __u32 __bitwise __virtio32;
प्रकार __u64 __bitwise __virtio64;

#पूर्ण_अगर /* _UAPI_LINUX_VIRTIO_TYPES_H */
