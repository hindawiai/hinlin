<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _LINUX_VHOST_H
#घोषणा _LINUX_VHOST_H
/* Userspace पूर्णांकerface क्रम in-kernel virtio accelerators. */

/* vhost is used to reduce the number of प्रणाली calls involved in virtio.
 *
 * Existing virtio net code is used in the guest without modअगरication.
 *
 * This header includes पूर्णांकerface used by userspace hypervisor क्रम
 * device configuration.
 */

#समावेश <linux/vhost_types.h>
#समावेश <linux/types.h>
#समावेश <linux/ioctl.h>

#घोषणा VHOST_खाता_UNBIND -1

/* ioctls */

#घोषणा VHOST_VIRTIO 0xAF

/* Features biपंचांगask क्रम क्रमward compatibility.  Transport bits are used क्रम
 * vhost specअगरic features. */
#घोषणा VHOST_GET_FEATURES	_IOR(VHOST_VIRTIO, 0x00, __u64)
#घोषणा VHOST_SET_FEATURES	_IOW(VHOST_VIRTIO, 0x00, __u64)

/* Set current process as the (exclusive) owner of this file descriptor.  This
 * must be called beक्रमe any other vhost command.  Further calls to
 * VHOST_OWNER_SET fail until VHOST_OWNER_RESET is called. */
#घोषणा VHOST_SET_OWNER _IO(VHOST_VIRTIO, 0x01)
/* Give up ownership, and reset the device to शेष values.
 * Allows subsequent call to VHOST_OWNER_SET to succeed. */
#घोषणा VHOST_RESET_OWNER _IO(VHOST_VIRTIO, 0x02)

/* Set up/modअगरy memory layout */
#घोषणा VHOST_SET_MEM_TABLE	_IOW(VHOST_VIRTIO, 0x03, काष्ठा vhost_memory)

/* Write logging setup. */
/* Memory ग_लिखोs can optionally be logged by setting bit at an offset
 * (calculated from the physical address) from specअगरied log base.
 * The bit is set using an atomic 32 bit operation. */
/* Set base address क्रम logging. */
#घोषणा VHOST_SET_LOG_BASE _IOW(VHOST_VIRTIO, 0x04, __u64)
/* Specअगरy an eventfd file descriptor to संकेत on log ग_लिखो. */
#घोषणा VHOST_SET_LOG_FD _IOW(VHOST_VIRTIO, 0x07, पूर्णांक)

/* Ring setup. */
/* Set number of descriptors in ring. This parameter can not
 * be modअगरied जबतक ring is running (bound to a device). */
#घोषणा VHOST_SET_VRING_NUM _IOW(VHOST_VIRTIO, 0x10, काष्ठा vhost_vring_state)
/* Set addresses क्रम the ring. */
#घोषणा VHOST_SET_VRING_ADDR _IOW(VHOST_VIRTIO, 0x11, काष्ठा vhost_vring_addr)
/* Base value where queue looks क्रम available descriptors */
#घोषणा VHOST_SET_VRING_BASE _IOW(VHOST_VIRTIO, 0x12, काष्ठा vhost_vring_state)
/* Get accessor: पढ़ोs index, ग_लिखोs value in num */
#घोषणा VHOST_GET_VRING_BASE _IOWR(VHOST_VIRTIO, 0x12, काष्ठा vhost_vring_state)

/* Set the vring byte order in num. Valid values are VHOST_VRING_LITTLE_ENDIAN
 * or VHOST_VRING_BIG_ENDIAN (other values वापस -EINVAL).
 * The byte order cannot be changed जबतक the device is active: trying to करो so
 * वापसs -EBUSY.
 * This is a legacy only API that is simply ignored when VIRTIO_F_VERSION_1 is
 * set.
 * Not all kernel configurations support this ioctl, but all configurations that
 * support SET also support GET.
 */
#घोषणा VHOST_VRING_LITTLE_ENDIAN 0
#घोषणा VHOST_VRING_BIG_ENDIAN 1
#घोषणा VHOST_SET_VRING_ENDIAN _IOW(VHOST_VIRTIO, 0x13, काष्ठा vhost_vring_state)
#घोषणा VHOST_GET_VRING_ENDIAN _IOW(VHOST_VIRTIO, 0x14, काष्ठा vhost_vring_state)

/* The following ioctls use eventfd file descriptors to संकेत and poll
 * क्रम events. */

/* Set eventfd to poll क्रम added buffers */
#घोषणा VHOST_SET_VRING_KICK _IOW(VHOST_VIRTIO, 0x20, काष्ठा vhost_vring_file)
/* Set eventfd to संकेत when buffers have beed used */
#घोषणा VHOST_SET_VRING_CALL _IOW(VHOST_VIRTIO, 0x21, काष्ठा vhost_vring_file)
/* Set eventfd to संकेत an error */
#घोषणा VHOST_SET_VRING_ERR _IOW(VHOST_VIRTIO, 0x22, काष्ठा vhost_vring_file)
/* Set busy loop समयout (in us) */
#घोषणा VHOST_SET_VRING_BUSYLOOP_TIMEOUT _IOW(VHOST_VIRTIO, 0x23,	\
					 काष्ठा vhost_vring_state)
/* Get busy loop समयout (in us) */
#घोषणा VHOST_GET_VRING_BUSYLOOP_TIMEOUT _IOW(VHOST_VIRTIO, 0x24,	\
					 काष्ठा vhost_vring_state)

/* Set or get vhost backend capability */

/* Use message type V2 */
#घोषणा VHOST_BACKEND_F_IOTLB_MSG_V2 0x1
/* IOTLB can accept batching hपूर्णांकs */
#घोषणा VHOST_BACKEND_F_IOTLB_BATCH  0x2

#घोषणा VHOST_SET_BACKEND_FEATURES _IOW(VHOST_VIRTIO, 0x25, __u64)
#घोषणा VHOST_GET_BACKEND_FEATURES _IOR(VHOST_VIRTIO, 0x26, __u64)

/* VHOST_NET specअगरic defines */

/* Attach virtio net ring to a raw socket, or tap device.
 * The socket must be alपढ़ोy bound to an ethernet device, this device will be
 * used क्रम transmit.  Pass fd -1 to unbind from the socket and the transmit
 * device.  This can be used to stop the ring (e.g. क्रम migration). */
#घोषणा VHOST_NET_SET_BACKEND _IOW(VHOST_VIRTIO, 0x30, काष्ठा vhost_vring_file)

/* VHOST_SCSI specअगरic defines */

#घोषणा VHOST_SCSI_SET_ENDPOINT _IOW(VHOST_VIRTIO, 0x40, काष्ठा vhost_scsi_target)
#घोषणा VHOST_SCSI_CLEAR_ENDPOINT _IOW(VHOST_VIRTIO, 0x41, काष्ठा vhost_scsi_target)
/* Changing this अवरोधs userspace. */
#घोषणा VHOST_SCSI_GET_ABI_VERSION _IOW(VHOST_VIRTIO, 0x42, पूर्णांक)
/* Set and get the events missed flag */
#घोषणा VHOST_SCSI_SET_EVENTS_MISSED _IOW(VHOST_VIRTIO, 0x43, __u32)
#घोषणा VHOST_SCSI_GET_EVENTS_MISSED _IOW(VHOST_VIRTIO, 0x44, __u32)

/* VHOST_VSOCK specअगरic defines */

#घोषणा VHOST_VSOCK_SET_GUEST_CID	_IOW(VHOST_VIRTIO, 0x60, __u64)
#घोषणा VHOST_VSOCK_SET_RUNNING		_IOW(VHOST_VIRTIO, 0x61, पूर्णांक)

/* VHOST_VDPA specअगरic defines */

/* Get the device id. The device ids follow the same definition of
 * the device id defined in virtio-spec.
 */
#घोषणा VHOST_VDPA_GET_DEVICE_ID	_IOR(VHOST_VIRTIO, 0x70, __u32)
/* Get and set the status. The status bits follow the same definition
 * of the device status defined in virtio-spec.
 */
#घोषणा VHOST_VDPA_GET_STATUS		_IOR(VHOST_VIRTIO, 0x71, __u8)
#घोषणा VHOST_VDPA_SET_STATUS		_IOW(VHOST_VIRTIO, 0x72, __u8)
/* Get and set the device config. The device config follows the same
 * definition of the device config defined in virtio-spec.
 */
#घोषणा VHOST_VDPA_GET_CONFIG		_IOR(VHOST_VIRTIO, 0x73, \
					     काष्ठा vhost_vdpa_config)
#घोषणा VHOST_VDPA_SET_CONFIG		_IOW(VHOST_VIRTIO, 0x74, \
					     काष्ठा vhost_vdpa_config)
/* Enable/disable the ring. */
#घोषणा VHOST_VDPA_SET_VRING_ENABLE	_IOW(VHOST_VIRTIO, 0x75, \
					     काष्ठा vhost_vring_state)
/* Get the max ring size. */
#घोषणा VHOST_VDPA_GET_VRING_NUM	_IOR(VHOST_VIRTIO, 0x76, __u16)

/* Set event fd क्रम config पूर्णांकerrupt*/
#घोषणा VHOST_VDPA_SET_CONFIG_CALL	_IOW(VHOST_VIRTIO, 0x77, पूर्णांक)

/* Get the valid iova range */
#घोषणा VHOST_VDPA_GET_IOVA_RANGE	_IOR(VHOST_VIRTIO, 0x78, \
					     काष्ठा vhost_vdpa_iova_range)
#पूर्ण_अगर
