<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * (C) COPYRIGHT 2018 ARM Limited. All rights reserved.
 * Author: James.Qian.Wang <james.qian.wang@arm.com>
 *
 */
#अगर_अघोषित _MALIDP_PRODUCT_H_
#घोषणा _MALIDP_PRODUCT_H_

/* Product identअगरication */
#घोषणा MALIDP_CORE_ID(__product, __major, __minor, __status) \
	((((__product) & 0xFFFF) << 16) | (((__major) & 0xF) << 12) | \
	(((__minor) & 0xF) << 8) | ((__status) & 0xFF))

#घोषणा MALIDP_CORE_ID_PRODUCT_ID(__core_id) ((__u32)(__core_id) >> 16)
#घोषणा MALIDP_CORE_ID_MAJOR(__core_id)      (((__u32)(__core_id) >> 12) & 0xF)
#घोषणा MALIDP_CORE_ID_MINOR(__core_id)      (((__u32)(__core_id) >> 8) & 0xF)
#घोषणा MALIDP_CORE_ID_STATUS(__core_id)     (((__u32)(__core_id)) & 0xFF)

/* Mali-display product IDs */
#घोषणा MALIDP_D71_PRODUCT_ID	0x0071
#घोषणा MALIDP_D32_PRODUCT_ID	0x0032

जोड़ komeda_config_id अणु
	काष्ठा अणु
		__u32	max_line_sz:16,
			n_pipelines:2,
			n_scalers:2, /* number of scalers per pipeline */
			n_layers:3, /* number of layers per pipeline */
			n_richs:3, /* number of rich layers per pipeline */
			reserved_bits:6;
	पूर्ण;
	__u32 value;
पूर्ण;

#पूर्ण_अगर /* _MALIDP_PRODUCT_H_ */
