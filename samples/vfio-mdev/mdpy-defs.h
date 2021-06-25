<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Simple pci display device.
 *
 * Framebuffer memory is pci bar 0.
 * Configuration (पढ़ो-only) is in pci config space.
 * Format field uses drm fourcc codes.
 * ATM only DRM_FORMAT_XRGB8888 is supported.
 */

/* pci ids */
#घोषणा MDPY_PCI_VENDOR_ID	PCI_VENDOR_ID_REDHAT
#घोषणा MDPY_PCI_DEVICE_ID	0x000f
#घोषणा MDPY_PCI_SUBVENDOR_ID	PCI_SUBVENDOR_ID_REDHAT_QUMRANET
#घोषणा MDPY_PCI_SUBDEVICE_ID	PCI_SUBDEVICE_ID_QEMU

/* pci cfg space offsets क्रम fb config (dword) */
#घोषणा MDPY_VENDORCAP_OFFSET   0x40
#घोषणा MDPY_VENDORCAP_SIZE     0x10
#घोषणा MDPY_FORMAT_OFFSET	(MDPY_VENDORCAP_OFFSET + 0x04)
#घोषणा MDPY_WIDTH_OFFSET	(MDPY_VENDORCAP_OFFSET + 0x08)
#घोषणा MDPY_HEIGHT_OFFSET	(MDPY_VENDORCAP_OFFSET + 0x0c)
