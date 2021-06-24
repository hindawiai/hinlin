<शैली गुरु>
#अगर_अघोषित _UAPI_LINUX_VIRTIO_CONFIG_H
#घोषणा _UAPI_LINUX_VIRTIO_CONFIG_H
/* This header, excluding the #अगर_घोषित __KERNEL__ part, is BSD licensed so
 * anyone can use the definitions to implement compatible drivers/servers.
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
 * SUCH DAMAGE. */

/* Virtio devices use a standardized configuration space to define their
 * features and pass configuration inक्रमmation, but each implementation can
 * store and access that space dअगरferently. */
#समावेश <linux/types.h>

/* Status byte क्रम guest to report progress, and synchronize features. */
/* We have seen device and processed generic fields (VIRTIO_CONFIG_F_VIRTIO) */
#घोषणा VIRTIO_CONFIG_S_ACKNOWLEDGE	1
/* We have found a driver क्रम the device. */
#घोषणा VIRTIO_CONFIG_S_DRIVER		2
/* Driver has used its parts of the config, and is happy */
#घोषणा VIRTIO_CONFIG_S_DRIVER_OK	4
/* Driver has finished configuring features */
#घोषणा VIRTIO_CONFIG_S_FEATURES_OK	8
/* Device entered invalid state, driver must reset it */
#घोषणा VIRTIO_CONFIG_S_NEEDS_RESET	0x40
/* We've given up on this device. */
#घोषणा VIRTIO_CONFIG_S_FAILED		0x80

/*
 * Virtio feature bits VIRTIO_TRANSPORT_F_START through
 * VIRTIO_TRANSPORT_F_END are reserved क्रम the transport
 * being used (e.g. virtio_ring, virtio_pci etc.), the
 * rest are per-device feature bits.
 */
#घोषणा VIRTIO_TRANSPORT_F_START	28
#घोषणा VIRTIO_TRANSPORT_F_END		38

#अगर_अघोषित VIRTIO_CONFIG_NO_LEGACY
/* Do we get callbacks when the ring is completely used, even अगर we've
 * suppressed them? */
#घोषणा VIRTIO_F_NOTIFY_ON_EMPTY	24

/* Can the device handle any descriptor layout? */
#घोषणा VIRTIO_F_ANY_LAYOUT		27
#पूर्ण_अगर /* VIRTIO_CONFIG_NO_LEGACY */

/* v1.0 compliant. */
#घोषणा VIRTIO_F_VERSION_1		32

/*
 * If clear - device has the platक्रमm DMA (e.g. IOMMU) bypass quirk feature.
 * If set - use platक्रमm DMA tools to access the memory.
 *
 * Note the reverse polarity (compared to most other features),
 * this is क्रम compatibility with legacy प्रणालीs.
 */
#घोषणा VIRTIO_F_ACCESS_PLATFORM	33
#अगर_अघोषित __KERNEL__
/* Legacy name क्रम VIRTIO_F_ACCESS_PLATFORM (क्रम compatibility with old userspace) */
#घोषणा VIRTIO_F_IOMMU_PLATFORM		VIRTIO_F_ACCESS_PLATFORM
#पूर्ण_अगर /* __KERNEL__ */

/* This feature indicates support क्रम the packed virtqueue layout. */
#घोषणा VIRTIO_F_RING_PACKED		34

/*
 * This feature indicates that memory accesses by the driver and the
 * device are ordered in a way described by the platक्रमm.
 */
#घोषणा VIRTIO_F_ORDER_PLATFORM		36

/*
 * Does the device support Single Root I/O Virtualization?
 */
#घोषणा VIRTIO_F_SR_IOV			37
#पूर्ण_अगर /* _UAPI_LINUX_VIRTIO_CONFIG_H */
