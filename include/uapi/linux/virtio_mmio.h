<शैली गुरु>
/*
 * Virtio platक्रमm device driver
 *
 * Copyright 2011, ARM Ltd.
 *
 * Based on Virtio PCI driver by Anthony Liguori, copyright IBM Corp. 2007
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
 */

#अगर_अघोषित _LINUX_VIRTIO_MMIO_H
#घोषणा _LINUX_VIRTIO_MMIO_H

/*
 * Control रेजिस्टरs
 */

/* Magic value ("virt" string) - Read Only */
#घोषणा VIRTIO_MMIO_MAGIC_VALUE		0x000

/* Virtio device version - Read Only */
#घोषणा VIRTIO_MMIO_VERSION		0x004

/* Virtio device ID - Read Only */
#घोषणा VIRTIO_MMIO_DEVICE_ID		0x008

/* Virtio venकरोr ID - Read Only */
#घोषणा VIRTIO_MMIO_VENDOR_ID		0x00c

/* Biपंचांगask of the features supported by the device (host)
 * (32 bits per set) - Read Only */
#घोषणा VIRTIO_MMIO_DEVICE_FEATURES	0x010

/* Device (host) features set selector - Write Only */
#घोषणा VIRTIO_MMIO_DEVICE_FEATURES_SEL	0x014

/* Biपंचांगask of features activated by the driver (guest)
 * (32 bits per set) - Write Only */
#घोषणा VIRTIO_MMIO_DRIVER_FEATURES	0x020

/* Activated features set selector - Write Only */
#घोषणा VIRTIO_MMIO_DRIVER_FEATURES_SEL	0x024


#अगर_अघोषित VIRTIO_MMIO_NO_LEGACY /* LEGACY DEVICES ONLY! */

/* Guest's memory page size in bytes - Write Only */
#घोषणा VIRTIO_MMIO_GUEST_PAGE_SIZE	0x028

#पूर्ण_अगर


/* Queue selector - Write Only */
#घोषणा VIRTIO_MMIO_QUEUE_SEL		0x030

/* Maximum size of the currently selected queue - Read Only */
#घोषणा VIRTIO_MMIO_QUEUE_NUM_MAX	0x034

/* Queue size क्रम the currently selected queue - Write Only */
#घोषणा VIRTIO_MMIO_QUEUE_NUM		0x038


#अगर_अघोषित VIRTIO_MMIO_NO_LEGACY /* LEGACY DEVICES ONLY! */

/* Used Ring alignment क्रम the currently selected queue - Write Only */
#घोषणा VIRTIO_MMIO_QUEUE_ALIGN		0x03c

/* Guest's PFN क्रम the currently selected queue - Read Write */
#घोषणा VIRTIO_MMIO_QUEUE_PFN		0x040

#पूर्ण_अगर


/* Ready bit क्रम the currently selected queue - Read Write */
#घोषणा VIRTIO_MMIO_QUEUE_READY		0x044

/* Queue notअगरier - Write Only */
#घोषणा VIRTIO_MMIO_QUEUE_NOTIFY	0x050

/* Interrupt status - Read Only */
#घोषणा VIRTIO_MMIO_INTERRUPT_STATUS	0x060

/* Interrupt acknowledge - Write Only */
#घोषणा VIRTIO_MMIO_INTERRUPT_ACK	0x064

/* Device status रेजिस्टर - Read Write */
#घोषणा VIRTIO_MMIO_STATUS		0x070

/* Selected queue's Descriptor Table address, 64 bits in two halves */
#घोषणा VIRTIO_MMIO_QUEUE_DESC_LOW	0x080
#घोषणा VIRTIO_MMIO_QUEUE_DESC_HIGH	0x084

/* Selected queue's Available Ring address, 64 bits in two halves */
#घोषणा VIRTIO_MMIO_QUEUE_AVAIL_LOW	0x090
#घोषणा VIRTIO_MMIO_QUEUE_AVAIL_HIGH	0x094

/* Selected queue's Used Ring address, 64 bits in two halves */
#घोषणा VIRTIO_MMIO_QUEUE_USED_LOW	0x0a0
#घोषणा VIRTIO_MMIO_QUEUE_USED_HIGH	0x0a4

/* Shared memory region id */
#घोषणा VIRTIO_MMIO_SHM_SEL             0x0ac

/* Shared memory region length, 64 bits in two halves */
#घोषणा VIRTIO_MMIO_SHM_LEN_LOW         0x0b0
#घोषणा VIRTIO_MMIO_SHM_LEN_HIGH        0x0b4

/* Shared memory region base address, 64 bits in two halves */
#घोषणा VIRTIO_MMIO_SHM_BASE_LOW        0x0b8
#घोषणा VIRTIO_MMIO_SHM_BASE_HIGH       0x0bc

/* Configuration atomicity value */
#घोषणा VIRTIO_MMIO_CONFIG_GENERATION	0x0fc

/* The config space is defined by each driver as
 * the per-driver configuration space - Read Write */
#घोषणा VIRTIO_MMIO_CONFIG		0x100



/*
 * Interrupt flags (re: पूर्णांकerrupt status & acknowledge रेजिस्टरs)
 */

#घोषणा VIRTIO_MMIO_INT_VRING		(1 << 0)
#घोषणा VIRTIO_MMIO_INT_CONFIG		(1 << 1)

#पूर्ण_अगर
