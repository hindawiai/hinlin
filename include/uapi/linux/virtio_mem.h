<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause */
/*
 * Virtio Mem Device
 *
 * Copyright Red Hat, Inc. 2020
 *
 * Authors:
 *     David Hildenbअक्रम <david@redhat.com>
 *
 * This header is BSD licensed so anyone can use the definitions
 * to implement compatible drivers/servers:
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
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL IBM OR
 * CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#अगर_अघोषित _LINUX_VIRTIO_MEM_H
#घोषणा _LINUX_VIRTIO_MEM_H

#समावेश <linux/types.h>
#समावेश <linux/virtio_types.h>
#समावेश <linux/virtio_ids.h>
#समावेश <linux/virtio_config.h>

/*
 * Each virtio-mem device manages a dedicated region in physical address
 * space. Each device can beदीर्घ to a single NUMA node, multiple devices
 * क्रम a single NUMA node are possible. A virtio-mem device is like a
 * "resizable DIMM" consisting of small memory blocks that can be plugged
 * or unplugged. The device driver is responsible क्रम (un)plugging memory
 * blocks on demand.
 *
 * Virtio-mem devices can only operate on their asचिन्हित memory region in
 * order to (un)plug memory. A device cannot (un)plug memory beदीर्घing to
 * other devices.
 *
 * The "region_size" corresponds to the maximum amount of memory that can
 * be provided by a device. The "size" corresponds to the amount of memory
 * that is currently plugged. "requested_size" corresponds to a request
 * from the device to the device driver to (un)plug blocks. The
 * device driver should try to (un)plug blocks in order to reach the
 * "requested_size". It is impossible to plug more memory than requested.
 *
 * The "usable_region_size" represents the memory region that can actually
 * be used to (un)plug memory. It is always at least as big as the
 * "requested_size" and will grow dynamically. It will only shrink when
 * explicitly triggered (VIRTIO_MEM_REQ_UNPLUG).
 *
 * There are no guarantees what will happen अगर unplugged memory is
 * पढ़ो/written. Such memory should, in general, not be touched. E.g.,
 * even writing might succeed, but the values will simply be discarded at
 * अक्रमom poपूर्णांकs in समय.
 *
 * It can happen that the device cannot process a request, because it is
 * busy. The device driver has to retry later.
 *
 * Usually, during प्रणाली resets all memory will get unplugged, so the
 * device driver can start with a clean state. However, in specअगरic
 * scenarios (अगर the device is busy) it can happen that the device still
 * has memory plugged. The device driver can request to unplug all memory
 * (VIRTIO_MEM_REQ_UNPLUG) - which might take a जबतक to succeed अगर the
 * device is busy.
 */

/* --- virtio-mem: feature bits --- */

/* node_id is an ACPI PXM and is valid */
#घोषणा VIRTIO_MEM_F_ACPI_PXM		0


/* --- virtio-mem: guest -> host requests --- */

/* request to plug memory blocks */
#घोषणा VIRTIO_MEM_REQ_PLUG			0
/* request to unplug memory blocks */
#घोषणा VIRTIO_MEM_REQ_UNPLUG			1
/* request to unplug all blocks and shrink the usable size */
#घोषणा VIRTIO_MEM_REQ_UNPLUG_ALL		2
/* request inक्रमmation about the plugged state of memory blocks */
#घोषणा VIRTIO_MEM_REQ_STATE			3

काष्ठा virtio_mem_req_plug अणु
	__virtio64 addr;
	__virtio16 nb_blocks;
	__virtio16 padding[3];
पूर्ण;

काष्ठा virtio_mem_req_unplug अणु
	__virtio64 addr;
	__virtio16 nb_blocks;
	__virtio16 padding[3];
पूर्ण;

काष्ठा virtio_mem_req_state अणु
	__virtio64 addr;
	__virtio16 nb_blocks;
	__virtio16 padding[3];
पूर्ण;

काष्ठा virtio_mem_req अणु
	__virtio16 type;
	__virtio16 padding[3];

	जोड़ अणु
		काष्ठा virtio_mem_req_plug plug;
		काष्ठा virtio_mem_req_unplug unplug;
		काष्ठा virtio_mem_req_state state;
	पूर्ण u;
पूर्ण;


/* --- virtio-mem: host -> guest response --- */

/*
 * Request processed successfully, applicable क्रम
 * - VIRTIO_MEM_REQ_PLUG
 * - VIRTIO_MEM_REQ_UNPLUG
 * - VIRTIO_MEM_REQ_UNPLUG_ALL
 * - VIRTIO_MEM_REQ_STATE
 */
#घोषणा VIRTIO_MEM_RESP_ACK			0
/*
 * Request denied - e.g. trying to plug more than requested, applicable क्रम
 * - VIRTIO_MEM_REQ_PLUG
 */
#घोषणा VIRTIO_MEM_RESP_NACK			1
/*
 * Request cannot be processed right now, try again later, applicable क्रम
 * - VIRTIO_MEM_REQ_PLUG
 * - VIRTIO_MEM_REQ_UNPLUG
 * - VIRTIO_MEM_REQ_UNPLUG_ALL
 */
#घोषणा VIRTIO_MEM_RESP_BUSY			2
/*
 * Error in request (e.g. addresses/alignment), applicable क्रम
 * - VIRTIO_MEM_REQ_PLUG
 * - VIRTIO_MEM_REQ_UNPLUG
 * - VIRTIO_MEM_REQ_STATE
 */
#घोषणा VIRTIO_MEM_RESP_ERROR			3


/* State of memory blocks is "plugged" */
#घोषणा VIRTIO_MEM_STATE_PLUGGED		0
/* State of memory blocks is "unplugged" */
#घोषणा VIRTIO_MEM_STATE_UNPLUGGED		1
/* State of memory blocks is "mixed" */
#घोषणा VIRTIO_MEM_STATE_MIXED			2

काष्ठा virtio_mem_resp_state अणु
	__virtio16 state;
पूर्ण;

काष्ठा virtio_mem_resp अणु
	__virtio16 type;
	__virtio16 padding[3];

	जोड़ अणु
		काष्ठा virtio_mem_resp_state state;
	पूर्ण u;
पूर्ण;

/* --- virtio-mem: configuration --- */

काष्ठा virtio_mem_config अणु
	/* Block size and alignment. Cannot change. */
	__le64 block_size;
	/* Valid with VIRTIO_MEM_F_ACPI_PXM. Cannot change. */
	__le16 node_id;
	__u8 padding[6];
	/* Start address of the memory region. Cannot change. */
	__le64 addr;
	/* Region size (maximum). Cannot change. */
	__le64 region_size;
	/*
	 * Currently usable region size. Can grow up to region_size. Can
	 * shrink due to VIRTIO_MEM_REQ_UNPLUG_ALL (in which हाल no config
	 * update will be sent).
	 */
	__le64 usable_region_size;
	/*
	 * Currently used size. Changes due to plug/unplug requests, but no
	 * config updates will be sent.
	 */
	__le64 plugged_size;
	/* Requested size. New plug requests cannot exceed it. Can change. */
	__le64 requested_size;
पूर्ण;

#पूर्ण_अगर /* _LINUX_VIRTIO_MEM_H */
