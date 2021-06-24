<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause */
/*
 * Virtio-iommu definition v0.12
 *
 * Copyright (C) 2019 Arm Ltd.
 */
#अगर_अघोषित _UAPI_LINUX_VIRTIO_IOMMU_H
#घोषणा _UAPI_LINUX_VIRTIO_IOMMU_H

#समावेश <linux/types.h>

/* Feature bits */
#घोषणा VIRTIO_IOMMU_F_INPUT_RANGE		0
#घोषणा VIRTIO_IOMMU_F_DOMAIN_RANGE		1
#घोषणा VIRTIO_IOMMU_F_MAP_UNMAP		2
#घोषणा VIRTIO_IOMMU_F_BYPASS			3
#घोषणा VIRTIO_IOMMU_F_PROBE			4
#घोषणा VIRTIO_IOMMU_F_MMIO			5

काष्ठा virtio_iommu_range_64 अणु
	__le64					start;
	__le64					end;
पूर्ण;

काष्ठा virtio_iommu_range_32 अणु
	__le32					start;
	__le32					end;
पूर्ण;

काष्ठा virtio_iommu_config अणु
	/* Supported page sizes */
	__le64					page_size_mask;
	/* Supported IOVA range */
	काष्ठा virtio_iommu_range_64		input_range;
	/* Max करोमुख्य ID size */
	काष्ठा virtio_iommu_range_32		करोमुख्य_range;
	/* Probe buffer size */
	__le32					probe_size;
पूर्ण;

/* Request types */
#घोषणा VIRTIO_IOMMU_T_ATTACH			0x01
#घोषणा VIRTIO_IOMMU_T_DETACH			0x02
#घोषणा VIRTIO_IOMMU_T_MAP			0x03
#घोषणा VIRTIO_IOMMU_T_UNMAP			0x04
#घोषणा VIRTIO_IOMMU_T_PROBE			0x05

/* Status types */
#घोषणा VIRTIO_IOMMU_S_OK			0x00
#घोषणा VIRTIO_IOMMU_S_IOERR			0x01
#घोषणा VIRTIO_IOMMU_S_UNSUPP			0x02
#घोषणा VIRTIO_IOMMU_S_DEVERR			0x03
#घोषणा VIRTIO_IOMMU_S_INVAL			0x04
#घोषणा VIRTIO_IOMMU_S_RANGE			0x05
#घोषणा VIRTIO_IOMMU_S_NOENT			0x06
#घोषणा VIRTIO_IOMMU_S_FAULT			0x07
#घोषणा VIRTIO_IOMMU_S_NOMEM			0x08

काष्ठा virtio_iommu_req_head अणु
	__u8					type;
	__u8					reserved[3];
पूर्ण;

काष्ठा virtio_iommu_req_tail अणु
	__u8					status;
	__u8					reserved[3];
पूर्ण;

काष्ठा virtio_iommu_req_attach अणु
	काष्ठा virtio_iommu_req_head		head;
	__le32					करोमुख्य;
	__le32					endpoपूर्णांक;
	__u8					reserved[8];
	काष्ठा virtio_iommu_req_tail		tail;
पूर्ण;

काष्ठा virtio_iommu_req_detach अणु
	काष्ठा virtio_iommu_req_head		head;
	__le32					करोमुख्य;
	__le32					endpoपूर्णांक;
	__u8					reserved[8];
	काष्ठा virtio_iommu_req_tail		tail;
पूर्ण;

#घोषणा VIRTIO_IOMMU_MAP_F_READ			(1 << 0)
#घोषणा VIRTIO_IOMMU_MAP_F_WRITE		(1 << 1)
#घोषणा VIRTIO_IOMMU_MAP_F_MMIO			(1 << 2)

#घोषणा VIRTIO_IOMMU_MAP_F_MASK			(VIRTIO_IOMMU_MAP_F_READ |	\
						 VIRTIO_IOMMU_MAP_F_WRITE |	\
						 VIRTIO_IOMMU_MAP_F_MMIO)

काष्ठा virtio_iommu_req_map अणु
	काष्ठा virtio_iommu_req_head		head;
	__le32					करोमुख्य;
	__le64					virt_start;
	__le64					virt_end;
	__le64					phys_start;
	__le32					flags;
	काष्ठा virtio_iommu_req_tail		tail;
पूर्ण;

काष्ठा virtio_iommu_req_unmap अणु
	काष्ठा virtio_iommu_req_head		head;
	__le32					करोमुख्य;
	__le64					virt_start;
	__le64					virt_end;
	__u8					reserved[4];
	काष्ठा virtio_iommu_req_tail		tail;
पूर्ण;

#घोषणा VIRTIO_IOMMU_PROBE_T_NONE		0
#घोषणा VIRTIO_IOMMU_PROBE_T_RESV_MEM		1

#घोषणा VIRTIO_IOMMU_PROBE_T_MASK		0xfff

काष्ठा virtio_iommu_probe_property अणु
	__le16					type;
	__le16					length;
पूर्ण;

#घोषणा VIRTIO_IOMMU_RESV_MEM_T_RESERVED	0
#घोषणा VIRTIO_IOMMU_RESV_MEM_T_MSI		1

काष्ठा virtio_iommu_probe_resv_mem अणु
	काष्ठा virtio_iommu_probe_property	head;
	__u8					subtype;
	__u8					reserved[3];
	__le64					start;
	__le64					end;
पूर्ण;

काष्ठा virtio_iommu_req_probe अणु
	काष्ठा virtio_iommu_req_head		head;
	__le32					endpoपूर्णांक;
	__u8					reserved[64];

	__u8					properties[];

	/*
	 * Tail follows the variable-length properties array. No padding,
	 * property lengths are all aligned on 8 bytes.
	 */
पूर्ण;

/* Fault types */
#घोषणा VIRTIO_IOMMU_FAULT_R_UNKNOWN		0
#घोषणा VIRTIO_IOMMU_FAULT_R_DOMAIN		1
#घोषणा VIRTIO_IOMMU_FAULT_R_MAPPING		2

#घोषणा VIRTIO_IOMMU_FAULT_F_READ		(1 << 0)
#घोषणा VIRTIO_IOMMU_FAULT_F_WRITE		(1 << 1)
#घोषणा VIRTIO_IOMMU_FAULT_F_EXEC		(1 << 2)
#घोषणा VIRTIO_IOMMU_FAULT_F_ADDRESS		(1 << 8)

काष्ठा virtio_iommu_fault अणु
	__u8					reason;
	__u8					reserved[3];
	__le32					flags;
	__le32					endpoपूर्णांक;
	__u8					reserved2[4];
	__le64					address;
पूर्ण;

#पूर्ण_अगर
