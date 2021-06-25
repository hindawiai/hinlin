<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0 */
/* Copyright (c) 2017-2019 Mellanox Technologies. All rights reserved */

#अगर_अघोषित _MLXFW_MFA2_FORMAT_H
#घोषणा _MLXFW_MFA2_FORMAT_H

#समावेश "mlxfw_mfa2_file.h"
#समावेश "mlxfw_mfa2_tlv.h"

क्रमागत mlxfw_mfa2_tlv_type अणु
	MLXFW_MFA2_TLV_MULTI_PART = 0x01,
	MLXFW_MFA2_TLV_PACKAGE_DESCRIPTOR = 0x02,
	MLXFW_MFA2_TLV_COMPONENT_DESCRIPTOR = 0x04,
	MLXFW_MFA2_TLV_COMPONENT_PTR = 0x22,
	MLXFW_MFA2_TLV_PSID = 0x2A,
पूर्ण;

क्रमागत mlxfw_mfa2_compression_type अणु
	MLXFW_MFA2_COMPRESSION_TYPE_NONE,
	MLXFW_MFA2_COMPRESSION_TYPE_XZ,
पूर्ण;

काष्ठा mlxfw_mfa2_tlv_package_descriptor अणु
	__be16 num_components;
	__be16 num_devices;
	__be32 cb_offset;
	__be32 cb_archive_size;
	__be32 cb_size_h;
	__be32 cb_size_l;
	u8 padding[3];
	u8 cv_compression;
	__be32 user_data_offset;
पूर्ण __packed;

MLXFW_MFA2_TLV(package_descriptor, काष्ठा mlxfw_mfa2_tlv_package_descriptor,
	       MLXFW_MFA2_TLV_PACKAGE_DESCRIPTOR);

काष्ठा mlxfw_mfa2_tlv_multi अणु
	__be16 num_extensions;
	__be16 total_len;
पूर्ण __packed;

MLXFW_MFA2_TLV(multi, काष्ठा mlxfw_mfa2_tlv_multi,
	       MLXFW_MFA2_TLV_MULTI_PART);

काष्ठा mlxfw_mfa2_tlv_psid अणु
	u8 psid[0];
पूर्ण __packed;

MLXFW_MFA2_TLV_VARSIZE(psid, काष्ठा mlxfw_mfa2_tlv_psid,
		       MLXFW_MFA2_TLV_PSID);

काष्ठा mlxfw_mfa2_tlv_component_ptr अणु
	__be16 storage_id;
	__be16 component_index;
	__be32 storage_address;
पूर्ण __packed;

MLXFW_MFA2_TLV(component_ptr, काष्ठा mlxfw_mfa2_tlv_component_ptr,
	       MLXFW_MFA2_TLV_COMPONENT_PTR);

काष्ठा mlxfw_mfa2_tlv_component_descriptor अणु
	__be16 pldm_classअगरication;
	__be16 identअगरier;
	__be32 cb_offset_h;
	__be32 cb_offset_l;
	__be32 size;
पूर्ण __packed;

MLXFW_MFA2_TLV(component_descriptor, काष्ठा mlxfw_mfa2_tlv_component_descriptor,
	       MLXFW_MFA2_TLV_COMPONENT_DESCRIPTOR);

#पूर्ण_अगर
