<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* Common header क्रम Virtio crypto device.
 *
 * Copyright 2016 HUAWEI TECHNOLOGIES CO., LTD.
 */

#अगर_अघोषित _VIRTIO_CRYPTO_COMMON_H
#घोषणा _VIRTIO_CRYPTO_COMMON_H

#समावेश <linux/virtपन.स>
#समावेश <linux/crypto.h>
#समावेश <linux/spinlock.h>
#समावेश <crypto/aead.h>
#समावेश <crypto/aes.h>
#समावेश <crypto/engine.h>


/* Internal representation of a data virtqueue */
काष्ठा data_queue अणु
	/* Virtqueue associated with this send _queue */
	काष्ठा virtqueue *vq;

	/* To protect the vq operations क्रम the dataq */
	spinlock_t lock;

	/* Name of the tx queue: dataq.$index */
	अक्षर name[32];

	काष्ठा crypto_engine *engine;
पूर्ण;

काष्ठा virtio_crypto अणु
	काष्ठा virtio_device *vdev;
	काष्ठा virtqueue *ctrl_vq;
	काष्ठा data_queue *data_vq;

	/* To protect the vq operations क्रम the controlq */
	spinlock_t ctrl_lock;

	/* Maximum of data queues supported by the device */
	u32 max_data_queues;

	/* Number of queue currently used by the driver */
	u32 curr_queue;

	/*
	 * Specअगरies the services mask which the device support,
	 * see VIRTIO_CRYPTO_SERVICE_*
	 */
	u32 crypto_services;

	/* Detailed algorithms mask */
	u32 cipher_algo_l;
	u32 cipher_algo_h;
	u32 hash_algo;
	u32 mac_algo_l;
	u32 mac_algo_h;
	u32 aead_algo;

	/* Maximum length of cipher key */
	u32 max_cipher_key_len;
	/* Maximum length of authenticated key */
	u32 max_auth_key_len;
	/* Maximum size of per request */
	u64 max_size;

	/* Control VQ buffers: रक्षित by the ctrl_lock */
	काष्ठा virtio_crypto_op_ctrl_req ctrl;
	काष्ठा virtio_crypto_session_input input;
	काष्ठा virtio_crypto_inhdr ctrl_status;

	अचिन्हित दीर्घ status;
	atomic_t ref_count;
	काष्ठा list_head list;
	काष्ठा module *owner;
	uपूर्णांक8_t dev_id;

	/* Does the affinity hपूर्णांक is set क्रम virtqueues? */
	bool affinity_hपूर्णांक_set;
पूर्ण;

काष्ठा virtio_crypto_sym_session_info अणु
	/* Backend session id, which come from the host side */
	__u64 session_id;
पूर्ण;

काष्ठा virtio_crypto_request;
प्रकार व्योम (*virtio_crypto_data_callback)
		(काष्ठा virtio_crypto_request *vc_req, पूर्णांक len);

काष्ठा virtio_crypto_request अणु
	uपूर्णांक8_t status;
	काष्ठा virtio_crypto_op_data_req *req_data;
	काष्ठा scatterlist **sgs;
	काष्ठा data_queue *dataq;
	virtio_crypto_data_callback alg_cb;
पूर्ण;

पूर्णांक virtcrypto_devmgr_add_dev(काष्ठा virtio_crypto *vcrypto_dev);
काष्ठा list_head *virtcrypto_devmgr_get_head(व्योम);
व्योम virtcrypto_devmgr_rm_dev(काष्ठा virtio_crypto *vcrypto_dev);
काष्ठा virtio_crypto *virtcrypto_devmgr_get_first(व्योम);
पूर्णांक virtcrypto_dev_in_use(काष्ठा virtio_crypto *vcrypto_dev);
पूर्णांक virtcrypto_dev_get(काष्ठा virtio_crypto *vcrypto_dev);
व्योम virtcrypto_dev_put(काष्ठा virtio_crypto *vcrypto_dev);
पूर्णांक virtcrypto_dev_started(काष्ठा virtio_crypto *vcrypto_dev);
bool virtcrypto_algo_is_supported(काष्ठा virtio_crypto *vcrypto_dev,
				  uपूर्णांक32_t service,
				  uपूर्णांक32_t algo);
काष्ठा virtio_crypto *virtcrypto_get_dev_node(पूर्णांक node,
					      uपूर्णांक32_t service,
					      uपूर्णांक32_t algo);
पूर्णांक virtcrypto_dev_start(काष्ठा virtio_crypto *vcrypto);
व्योम virtcrypto_dev_stop(काष्ठा virtio_crypto *vcrypto);
पूर्णांक virtio_crypto_skcipher_crypt_req(
	काष्ठा crypto_engine *engine, व्योम *vreq);

व्योम
virtcrypto_clear_request(काष्ठा virtio_crypto_request *vc_req);

अटल अंतरभूत पूर्णांक virtio_crypto_get_current_node(व्योम)
अणु
	पूर्णांक cpu, node;

	cpu = get_cpu();
	node = topology_physical_package_id(cpu);
	put_cpu();

	वापस node;
पूर्ण

पूर्णांक virtio_crypto_algs_रेजिस्टर(काष्ठा virtio_crypto *vcrypto);
व्योम virtio_crypto_algs_unरेजिस्टर(काष्ठा virtio_crypto *vcrypto);

#पूर्ण_अगर /* _VIRTIO_CRYPTO_COMMON_H */
