<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित _DRIVERS_VIRTIO_VIRTIO_PCI_COMMON_H
#घोषणा _DRIVERS_VIRTIO_VIRTIO_PCI_COMMON_H
/*
 * Virtio PCI driver - APIs क्रम common functionality क्रम all device versions
 *
 * This module allows virtio devices to be used over a भव PCI device.
 * This can be used with QEMU based VMMs like KVM or Xen.
 *
 * Copyright IBM Corp. 2007
 * Copyright Red Hat, Inc. 2014
 *
 * Authors:
 *  Anthony Liguori  <aliguori@us.ibm.com>
 *  Rusty Russell <rusty@rustcorp.com.au>
 *  Michael S. Tsirkin <mst@redhat.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/list.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/virtपन.स>
#समावेश <linux/virtio_config.h>
#समावेश <linux/virtio_ring.h>
#समावेश <linux/virtio_pci.h>
#समावेश <linux/virtio_pci_modern.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/spinlock.h>

काष्ठा virtio_pci_vq_info अणु
	/* the actual virtqueue */
	काष्ठा virtqueue *vq;

	/* the list node क्रम the virtqueues list */
	काष्ठा list_head node;

	/* MSI-X vector (or none) */
	अचिन्हित msix_vector;
पूर्ण;

/* Our device काष्ठाure */
काष्ठा virtio_pci_device अणु
	काष्ठा virtio_device vdev;
	काष्ठा pci_dev *pci_dev;
	काष्ठा virtio_pci_modern_device mdev;

	/* In legacy mode, these two poपूर्णांक to within ->legacy. */
	/* Where to पढ़ो and clear पूर्णांकerrupt */
	u8 __iomem *isr;

	/* Legacy only field */
	/* the IO mapping क्रम the PCI config space */
	व्योम __iomem *ioaddr;

	/* a list of queues so we can dispatch IRQs */
	spinlock_t lock;
	काष्ठा list_head virtqueues;

	/* array of all queues क्रम house-keeping */
	काष्ठा virtio_pci_vq_info **vqs;

	/* MSI-X support */
	पूर्णांक msix_enabled;
	पूर्णांक पूर्णांकx_enabled;
	cpumask_var_t *msix_affinity_masks;
	/* Name strings क्रम पूर्णांकerrupts. This size should be enough,
	 * and I'm too lazy to allocate each name separately. */
	अक्षर (*msix_names)[256];
	/* Number of available vectors */
	अचिन्हित msix_vectors;
	/* Vectors allocated, excluding per-vq vectors अगर any */
	अचिन्हित msix_used_vectors;

	/* Whether we have vector per vq */
	bool per_vq_vectors;

	काष्ठा virtqueue *(*setup_vq)(काष्ठा virtio_pci_device *vp_dev,
				      काष्ठा virtio_pci_vq_info *info,
				      अचिन्हित idx,
				      व्योम (*callback)(काष्ठा virtqueue *vq),
				      स्थिर अक्षर *name,
				      bool ctx,
				      u16 msix_vec);
	व्योम (*del_vq)(काष्ठा virtio_pci_vq_info *info);

	u16 (*config_vector)(काष्ठा virtio_pci_device *vp_dev, u16 vector);
पूर्ण;

/* Constants क्रम MSI-X */
/* Use first vector क्रम configuration changes, second and the rest क्रम
 * virtqueues Thus, we need at least 2 vectors क्रम MSI. */
क्रमागत अणु
	VP_MSIX_CONFIG_VECTOR = 0,
	VP_MSIX_VQ_VECTOR = 1,
पूर्ण;

/* Convert a generic virtio device to our काष्ठाure */
अटल काष्ठा virtio_pci_device *to_vp_device(काष्ठा virtio_device *vdev)
अणु
	वापस container_of(vdev, काष्ठा virtio_pci_device, vdev);
पूर्ण

/* रुको क्रम pending irq handlers */
व्योम vp_synchronize_vectors(काष्ठा virtio_device *vdev);
/* the notअगरy function used when creating a virt queue */
bool vp_notअगरy(काष्ठा virtqueue *vq);
/* the config->del_vqs() implementation */
व्योम vp_del_vqs(काष्ठा virtio_device *vdev);
/* the config->find_vqs() implementation */
पूर्णांक vp_find_vqs(काष्ठा virtio_device *vdev, अचिन्हित nvqs,
		काष्ठा virtqueue *vqs[], vq_callback_t *callbacks[],
		स्थिर अक्षर * स्थिर names[], स्थिर bool *ctx,
		काष्ठा irq_affinity *desc);
स्थिर अक्षर *vp_bus_name(काष्ठा virtio_device *vdev);

/* Setup the affinity क्रम a virtqueue:
 * - क्रमce the affinity क्रम per vq vector
 * - OR over all affinities क्रम shared MSI
 * - ignore the affinity request अगर we're using INTX
 */
पूर्णांक vp_set_vq_affinity(काष्ठा virtqueue *vq, स्थिर काष्ठा cpumask *cpu_mask);

स्थिर काष्ठा cpumask *vp_get_vq_affinity(काष्ठा virtio_device *vdev, पूर्णांक index);

#अगर IS_ENABLED(CONFIG_VIRTIO_PCI_LEGACY)
पूर्णांक virtio_pci_legacy_probe(काष्ठा virtio_pci_device *);
व्योम virtio_pci_legacy_हटाओ(काष्ठा virtio_pci_device *);
#अन्यथा
अटल अंतरभूत पूर्णांक virtio_pci_legacy_probe(काष्ठा virtio_pci_device *vp_dev)
अणु
	वापस -ENODEV;
पूर्ण
अटल अंतरभूत व्योम virtio_pci_legacy_हटाओ(काष्ठा virtio_pci_device *vp_dev)
अणु
पूर्ण
#पूर्ण_अगर
पूर्णांक virtio_pci_modern_probe(काष्ठा virtio_pci_device *);
व्योम virtio_pci_modern_हटाओ(काष्ठा virtio_pci_device *);

#पूर्ण_अगर
