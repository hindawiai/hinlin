<शैली गुरु>
/* SPDX-License-Identअगरier: (BSD-3-Clause OR GPL-2.0-only) */
/* Copyright(c) 2014 - 2020 Intel Corporation */
#अगर_अघोषित _QAT_CRYPTO_INSTANCE_H_
#घोषणा _QAT_CRYPTO_INSTANCE_H_

#समावेश <crypto/aes.h>
#समावेश <linux/list.h>
#समावेश <linux/slab.h>
#समावेश "adf_accel_devices.h"
#समावेश "icp_qat_fw_la.h"

काष्ठा qat_crypto_instance अणु
	काष्ठा adf_etr_ring_data *sym_tx;
	काष्ठा adf_etr_ring_data *sym_rx;
	काष्ठा adf_etr_ring_data *pke_tx;
	काष्ठा adf_etr_ring_data *pke_rx;
	काष्ठा adf_accel_dev *accel_dev;
	काष्ठा list_head list;
	अचिन्हित दीर्घ state;
	पूर्णांक id;
	atomic_t refctr;
पूर्ण;

काष्ठा qat_crypto_request_buffs अणु
	काष्ठा qat_alg_buf_list *bl;
	dma_addr_t blp;
	काष्ठा qat_alg_buf_list *blout;
	dma_addr_t bloutp;
	माप_प्रकार sz;
	माप_प्रकार sz_out;
पूर्ण;

काष्ठा qat_crypto_request;

काष्ठा qat_crypto_request अणु
	काष्ठा icp_qat_fw_la_bulk_req req;
	जोड़ अणु
		काष्ठा qat_alg_aead_ctx *aead_ctx;
		काष्ठा qat_alg_skcipher_ctx *skcipher_ctx;
	पूर्ण;
	जोड़ अणु
		काष्ठा aead_request *aead_req;
		काष्ठा skcipher_request *skcipher_req;
	पूर्ण;
	काष्ठा qat_crypto_request_buffs buf;
	व्योम (*cb)(काष्ठा icp_qat_fw_la_resp *resp,
		   काष्ठा qat_crypto_request *req);
	जोड़ अणु
		काष्ठा अणु
			__be64 iv_hi;
			__be64 iv_lo;
		पूर्ण;
		u8 iv[AES_BLOCK_SIZE];
	पूर्ण;
	bool encryption;
पूर्ण;

अटल अंतरभूत bool adf_hw_dev_has_crypto(काष्ठा adf_accel_dev *accel_dev)
अणु
	काष्ठा adf_hw_device_data *hw_device = accel_dev->hw_device;
	u32 mask = ~hw_device->accel_capabilities_mask;

	अगर (mask & ADF_ACCEL_CAPABILITIES_CRYPTO_SYMMETRIC)
		वापस false;
	अगर (mask & ADF_ACCEL_CAPABILITIES_CRYPTO_ASYMMETRIC)
		वापस false;
	अगर (mask & ADF_ACCEL_CAPABILITIES_AUTHENTICATION)
		वापस false;

	वापस true;
पूर्ण

#पूर्ण_अगर
