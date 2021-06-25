<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _LINUX_VHOST_TYPES_H
#घोषणा _LINUX_VHOST_TYPES_H
/* Userspace पूर्णांकerface क्रम in-kernel virtio accelerators. */

/* vhost is used to reduce the number of प्रणाली calls involved in virtio.
 *
 * Existing virtio net code is used in the guest without modअगरication.
 *
 * This header includes पूर्णांकerface used by userspace hypervisor क्रम
 * device configuration.
 */

#समावेश <linux/types.h>
#समावेश <linux/compiler.h>
#समावेश <linux/virtio_config.h>
#समावेश <linux/virtio_ring.h>

काष्ठा vhost_vring_state अणु
	अचिन्हित पूर्णांक index;
	अचिन्हित पूर्णांक num;
पूर्ण;

काष्ठा vhost_vring_file अणु
	अचिन्हित पूर्णांक index;
	पूर्णांक fd; /* Pass -1 to unbind from file. */

पूर्ण;

काष्ठा vhost_vring_addr अणु
	अचिन्हित पूर्णांक index;
	/* Option flags. */
	अचिन्हित पूर्णांक flags;
	/* Flag values: */
	/* Whether log address is valid. If set enables logging. */
#घोषणा VHOST_VRING_F_LOG 0

	/* Start of array of descriptors (भवly contiguous) */
	__u64 desc_user_addr;
	/* Used काष्ठाure address. Must be 32 bit aligned */
	__u64 used_user_addr;
	/* Available काष्ठाure address. Must be 16 bit aligned */
	__u64 avail_user_addr;
	/* Logging support. */
	/* Log ग_लिखोs to used काष्ठाure, at offset calculated from specअगरied
	 * address. Address must be 32 bit aligned. */
	__u64 log_guest_addr;
पूर्ण;

/* no alignment requirement */
काष्ठा vhost_iotlb_msg अणु
	__u64 iova;
	__u64 size;
	__u64 uaddr;
#घोषणा VHOST_ACCESS_RO      0x1
#घोषणा VHOST_ACCESS_WO      0x2
#घोषणा VHOST_ACCESS_RW      0x3
	__u8 perm;
#घोषणा VHOST_IOTLB_MISS           1
#घोषणा VHOST_IOTLB_UPDATE         2
#घोषणा VHOST_IOTLB_INVALIDATE     3
#घोषणा VHOST_IOTLB_ACCESS_FAIL    4
/*
 * VHOST_IOTLB_BATCH_BEGIN and VHOST_IOTLB_BATCH_END allow modअगरying
 * multiple mappings in one go: beginning with
 * VHOST_IOTLB_BATCH_BEGIN, followed by any number of
 * VHOST_IOTLB_UPDATE messages, and ending with VHOST_IOTLB_BATCH_END.
 * When one of these two values is used as the message type, the rest
 * of the fields in the message are ignored. There's no guarantee that
 * these changes take place स्वतःmatically in the device.
 */
#घोषणा VHOST_IOTLB_BATCH_BEGIN    5
#घोषणा VHOST_IOTLB_BATCH_END      6
	__u8 type;
पूर्ण;

#घोषणा VHOST_IOTLB_MSG 0x1
#घोषणा VHOST_IOTLB_MSG_V2 0x2

काष्ठा vhost_msg अणु
	पूर्णांक type;
	जोड़ अणु
		काष्ठा vhost_iotlb_msg iotlb;
		__u8 padding[64];
	पूर्ण;
पूर्ण;

काष्ठा vhost_msg_v2 अणु
	__u32 type;
	__u32 reserved;
	जोड़ अणु
		काष्ठा vhost_iotlb_msg iotlb;
		__u8 padding[64];
	पूर्ण;
पूर्ण;

काष्ठा vhost_memory_region अणु
	__u64 guest_phys_addr;
	__u64 memory_size; /* bytes */
	__u64 userspace_addr;
	__u64 flags_padding; /* No flags are currently specअगरied. */
पूर्ण;

/* All region addresses and sizes must be 4K aligned. */
#घोषणा VHOST_PAGE_SIZE 0x1000

काष्ठा vhost_memory अणु
	__u32 nregions;
	__u32 padding;
	काष्ठा vhost_memory_region regions[0];
पूर्ण;

/* VHOST_SCSI specअगरic definitions */

/*
 * Used by QEMU userspace to ensure a consistent vhost-scsi ABI.
 *
 * ABI Rev 0: July 2012 version starting poपूर्णांक क्रम v3.6-rc merge candidate +
 *            RFC-v2 vhost-scsi userspace.  Add GET_ABI_VERSION ioctl usage
 * ABI Rev 1: January 2013. Ignore vhost_tpgt field in काष्ठा vhost_scsi_target.
 *            All the tarमाला_लो under vhost_wwpn can be seen and used by guset.
 */

#घोषणा VHOST_SCSI_ABI_VERSION	1

काष्ठा vhost_scsi_target अणु
	पूर्णांक abi_version;
	अक्षर vhost_wwpn[224]; /* TRANSPORT_IQN_LEN */
	अचिन्हित लघु vhost_tpgt;
	अचिन्हित लघु reserved;
पूर्ण;

/* VHOST_VDPA specअगरic definitions */

काष्ठा vhost_vdpa_config अणु
	__u32 off;
	__u32 len;
	__u8 buf[0];
पूर्ण;

/* vhost vdpa IOVA range
 * @first: First address that can be mapped by vhost-vDPA
 * @last: Last address that can be mapped by vhost-vDPA
 */
काष्ठा vhost_vdpa_iova_range अणु
	__u64 first;
	__u64 last;
पूर्ण;

/* Feature bits */
/* Log all ग_लिखो descriptors. Can be changed जबतक device is active. */
#घोषणा VHOST_F_LOG_ALL 26
/* vhost-net should add virtio_net_hdr क्रम RX, and strip क्रम TX packets. */
#घोषणा VHOST_NET_F_VIRTIO_NET_HDR 27

#पूर्ण_अगर
