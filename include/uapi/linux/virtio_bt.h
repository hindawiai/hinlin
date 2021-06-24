<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause */

#अगर_अघोषित _UAPI_LINUX_VIRTIO_BT_H
#घोषणा _UAPI_LINUX_VIRTIO_BT_H

#समावेश <linux/virtio_types.h>

/* Feature bits */
#घोषणा VIRTIO_BT_F_VND_HCI	0	/* Indicates venकरोr command support */
#घोषणा VIRTIO_BT_F_MSFT_EXT	1	/* Indicates MSFT venकरोr support */
#घोषणा VIRTIO_BT_F_AOSP_EXT	2	/* Indicates AOSP venकरोr support */

क्रमागत virtio_bt_config_type अणु
	VIRTIO_BT_CONFIG_TYPE_PRIMARY	= 0,
	VIRTIO_BT_CONFIG_TYPE_AMP	= 1,
पूर्ण;

क्रमागत virtio_bt_config_venकरोr अणु
	VIRTIO_BT_CONFIG_VENDOR_NONE	= 0,
	VIRTIO_BT_CONFIG_VENDOR_ZEPHYR	= 1,
	VIRTIO_BT_CONFIG_VENDOR_INTEL	= 2,
	VIRTIO_BT_CONFIG_VENDOR_REALTEK	= 3,
पूर्ण;

काष्ठा virtio_bt_config अणु
	__u8  type;
	__u16 venकरोr;
	__u16 msft_opcode;
पूर्ण __attribute__((packed));

#पूर्ण_अगर /* _UAPI_LINUX_VIRTIO_BT_H */
