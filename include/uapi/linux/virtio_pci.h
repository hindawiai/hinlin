<शैली गुरु>
/*
 * Virtio PCI driver
 *
 * This module allows virtio devices to be used over a भव PCI device.
 * This can be used with QEMU based VMMs like KVM or Xen.
 *
 * Copyright IBM Corp. 2007
 *
 * Authors:
 *  Anthony Liguori  <aliguori@us.ibm.com>
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

#अगर_अघोषित _LINUX_VIRTIO_PCI_H
#घोषणा _LINUX_VIRTIO_PCI_H

#समावेश <linux/types.h>

#अगर_अघोषित VIRTIO_PCI_NO_LEGACY

/* A 32-bit r/o biपंचांगask of the features supported by the host */
#घोषणा VIRTIO_PCI_HOST_FEATURES	0

/* A 32-bit r/w biपंचांगask of features activated by the guest */
#घोषणा VIRTIO_PCI_GUEST_FEATURES	4

/* A 32-bit r/w PFN क्रम the currently selected queue */
#घोषणा VIRTIO_PCI_QUEUE_PFN		8

/* A 16-bit r/o queue size क्रम the currently selected queue */
#घोषणा VIRTIO_PCI_QUEUE_NUM		12

/* A 16-bit r/w queue selector */
#घोषणा VIRTIO_PCI_QUEUE_SEL		14

/* A 16-bit r/w queue notअगरier */
#घोषणा VIRTIO_PCI_QUEUE_NOTIFY		16

/* An 8-bit device status रेजिस्टर.  */
#घोषणा VIRTIO_PCI_STATUS		18

/* An 8-bit r/o पूर्णांकerrupt status रेजिस्टर.  Reading the value will वापस the
 * current contents of the ISR and will also clear it.  This is effectively
 * a पढ़ो-and-acknowledge. */
#घोषणा VIRTIO_PCI_ISR			19

/* MSI-X रेजिस्टरs: only enabled अगर MSI-X is enabled. */
/* A 16-bit vector क्रम configuration changes. */
#घोषणा VIRTIO_MSI_CONFIG_VECTOR        20
/* A 16-bit vector क्रम selected queue notअगरications. */
#घोषणा VIRTIO_MSI_QUEUE_VECTOR         22

/* The reमुख्यing space is defined by each driver as the per-driver
 * configuration space */
#घोषणा VIRTIO_PCI_CONFIG_OFF(msix_enabled)	((msix_enabled) ? 24 : 20)
/* Deprecated: please use VIRTIO_PCI_CONFIG_OFF instead */
#घोषणा VIRTIO_PCI_CONFIG(dev)	VIRTIO_PCI_CONFIG_OFF((dev)->msix_enabled)

/* Virtio ABI version, this must match exactly */
#घोषणा VIRTIO_PCI_ABI_VERSION		0

/* How many bits to shअगरt physical queue address written to QUEUE_PFN.
 * 12 is historical, and due to x86 page size. */
#घोषणा VIRTIO_PCI_QUEUE_ADDR_SHIFT	12

/* The alignment to use between consumer and producer parts of vring.
 * x86 pagesize again. */
#घोषणा VIRTIO_PCI_VRING_ALIGN		4096

#पूर्ण_अगर /* VIRTIO_PCI_NO_LEGACY */

/* The bit of the ISR which indicates a device configuration change. */
#घोषणा VIRTIO_PCI_ISR_CONFIG		0x2
/* Vector value used to disable MSI क्रम queue */
#घोषणा VIRTIO_MSI_NO_VECTOR            0xffff

#अगर_अघोषित VIRTIO_PCI_NO_MODERN

/* IDs क्रम dअगरferent capabilities.  Must all exist. */

/* Common configuration */
#घोषणा VIRTIO_PCI_CAP_COMMON_CFG	1
/* Notअगरications */
#घोषणा VIRTIO_PCI_CAP_NOTIFY_CFG	2
/* ISR access */
#घोषणा VIRTIO_PCI_CAP_ISR_CFG		3
/* Device specअगरic configuration */
#घोषणा VIRTIO_PCI_CAP_DEVICE_CFG	4
/* PCI configuration access */
#घोषणा VIRTIO_PCI_CAP_PCI_CFG		5
/* Additional shared memory capability */
#घोषणा VIRTIO_PCI_CAP_SHARED_MEMORY_CFG 8

/* This is the PCI capability header: */
काष्ठा virtio_pci_cap अणु
	__u8 cap_vndr;		/* Generic PCI field: PCI_CAP_ID_VNDR */
	__u8 cap_next;		/* Generic PCI field: next ptr. */
	__u8 cap_len;		/* Generic PCI field: capability length */
	__u8 cfg_type;		/* Identअगरies the काष्ठाure. */
	__u8 bar;		/* Where to find it. */
	__u8 id;		/* Multiple capabilities of the same type */
	__u8 padding[2];	/* Pad to full dword. */
	__le32 offset;		/* Offset within bar. */
	__le32 length;		/* Length of the काष्ठाure, in bytes. */
पूर्ण;

काष्ठा virtio_pci_cap64 अणु
	काष्ठा virtio_pci_cap cap;
	__le32 offset_hi;             /* Most sig 32 bits of offset */
	__le32 length_hi;             /* Most sig 32 bits of length */
पूर्ण;

काष्ठा virtio_pci_notअगरy_cap अणु
	काष्ठा virtio_pci_cap cap;
	__le32 notअगरy_off_multiplier;	/* Multiplier क्रम queue_notअगरy_off. */
पूर्ण;

/* Fields in VIRTIO_PCI_CAP_COMMON_CFG: */
काष्ठा virtio_pci_common_cfg अणु
	/* About the whole device. */
	__le32 device_feature_select;	/* पढ़ो-ग_लिखो */
	__le32 device_feature;		/* पढ़ो-only */
	__le32 guest_feature_select;	/* पढ़ो-ग_लिखो */
	__le32 guest_feature;		/* पढ़ो-ग_लिखो */
	__le16 msix_config;		/* पढ़ो-ग_लिखो */
	__le16 num_queues;		/* पढ़ो-only */
	__u8 device_status;		/* पढ़ो-ग_लिखो */
	__u8 config_generation;		/* पढ़ो-only */

	/* About a specअगरic virtqueue. */
	__le16 queue_select;		/* पढ़ो-ग_लिखो */
	__le16 queue_size;		/* पढ़ो-ग_लिखो, घातer of 2. */
	__le16 queue_msix_vector;	/* पढ़ो-ग_लिखो */
	__le16 queue_enable;		/* पढ़ो-ग_लिखो */
	__le16 queue_notअगरy_off;	/* पढ़ो-only */
	__le32 queue_desc_lo;		/* पढ़ो-ग_लिखो */
	__le32 queue_desc_hi;		/* पढ़ो-ग_लिखो */
	__le32 queue_avail_lo;		/* पढ़ो-ग_लिखो */
	__le32 queue_avail_hi;		/* पढ़ो-ग_लिखो */
	__le32 queue_used_lo;		/* पढ़ो-ग_लिखो */
	__le32 queue_used_hi;		/* पढ़ो-ग_लिखो */
पूर्ण;

/* Fields in VIRTIO_PCI_CAP_PCI_CFG: */
काष्ठा virtio_pci_cfg_cap अणु
	काष्ठा virtio_pci_cap cap;
	__u8 pci_cfg_data[4]; /* Data क्रम BAR access. */
पूर्ण;

/* Macro versions of offsets क्रम the Old Timers! */
#घोषणा VIRTIO_PCI_CAP_VNDR		0
#घोषणा VIRTIO_PCI_CAP_NEXT		1
#घोषणा VIRTIO_PCI_CAP_LEN		2
#घोषणा VIRTIO_PCI_CAP_CFG_TYPE		3
#घोषणा VIRTIO_PCI_CAP_BAR		4
#घोषणा VIRTIO_PCI_CAP_OFFSET		8
#घोषणा VIRTIO_PCI_CAP_LENGTH		12

#घोषणा VIRTIO_PCI_NOTIFY_CAP_MULT	16

#घोषणा VIRTIO_PCI_COMMON_DFSELECT	0
#घोषणा VIRTIO_PCI_COMMON_DF		4
#घोषणा VIRTIO_PCI_COMMON_GFSELECT	8
#घोषणा VIRTIO_PCI_COMMON_GF		12
#घोषणा VIRTIO_PCI_COMMON_MSIX		16
#घोषणा VIRTIO_PCI_COMMON_NUMQ		18
#घोषणा VIRTIO_PCI_COMMON_STATUS	20
#घोषणा VIRTIO_PCI_COMMON_CFGGENERATION	21
#घोषणा VIRTIO_PCI_COMMON_Q_SELECT	22
#घोषणा VIRTIO_PCI_COMMON_Q_SIZE	24
#घोषणा VIRTIO_PCI_COMMON_Q_MSIX	26
#घोषणा VIRTIO_PCI_COMMON_Q_ENABLE	28
#घोषणा VIRTIO_PCI_COMMON_Q_NOFF	30
#घोषणा VIRTIO_PCI_COMMON_Q_DESCLO	32
#घोषणा VIRTIO_PCI_COMMON_Q_DESCHI	36
#घोषणा VIRTIO_PCI_COMMON_Q_AVAILLO	40
#घोषणा VIRTIO_PCI_COMMON_Q_AVAILHI	44
#घोषणा VIRTIO_PCI_COMMON_Q_USEDLO	48
#घोषणा VIRTIO_PCI_COMMON_Q_USEDHI	52

#पूर्ण_अगर /* VIRTIO_PCI_NO_MODERN */

#पूर्ण_अगर
