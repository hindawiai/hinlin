<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 *  Copyright IBM Corp. 2001, 2019
 *  Author(s): Robert Burroughs
 *	       Eric Rossman (edrossma@us.ibm.com)
 *	       Cornelia Huck <cornelia.huck@de.ibm.com>
 *
 *  Hotplug & misc device support: Jochen Roehrig (roehrig@de.ibm.com)
 *  Major cleanup & driver split: Martin Schwidefsky <schwidefsky@de.ibm.com>
 *				  Ralph Wuerthner <rwuerthn@de.ibm.com>
 *  MSGTYPE reकाष्ठा:		  Holger Dengler <hd@linux.vnet.ibm.com>
 */

#अगर_अघोषित _ZCRYPT_API_H_
#घोषणा _ZCRYPT_API_H_

#समावेश <linux/atomic.h>
#समावेश <यंत्र/debug.h>
#समावेश <यंत्र/zcrypt.h>
#समावेश "ap_bus.h"

/**
 * Supported device types
 */
#घोषणा ZCRYPT_CEX2C		5
#घोषणा ZCRYPT_CEX2A		6
#घोषणा ZCRYPT_CEX3C		7
#घोषणा ZCRYPT_CEX3A		8
#घोषणा ZCRYPT_CEX4	       10
#घोषणा ZCRYPT_CEX5	       11
#घोषणा ZCRYPT_CEX6	       12
#घोषणा ZCRYPT_CEX7	       13

/**
 * Large अक्रमom numbers are pulled in 4096 byte chunks from the crypto cards
 * and stored in a page. Be careful when increasing this buffer due to size
 * limitations क्रम AP requests.
 */
#घोषणा ZCRYPT_RNG_BUFFER_SIZE	4096

/*
 * Identअगरier क्रम Crypto Request Perक्रमmance Index
 */
क्रमागत crypto_ops अणु
	MEX_1K,
	MEX_2K,
	MEX_4K,
	CRT_1K,
	CRT_2K,
	CRT_4K,
	HWRNG,
	SECKEY,
	NUM_OPS
पूर्ण;

काष्ठा zcrypt_queue;

/* काष्ठा to hold tracking inक्रमmation क्रम a userspace request/response */
काष्ठा zcrypt_track अणु
	पूर्णांक again_counter;		/* retry attempts counter */
	पूर्णांक last_qid;			/* last qid used */
	पूर्णांक last_rc;			/* last वापस code */
#अगर_घोषित CONFIG_ZCRYPT_DEBUG
	काष्ठा ap_fi fi;		/* failure injection cmd */
#पूर्ण_अगर
पूर्ण;

/* defines related to message tracking */
#घोषणा TRACK_AGAIN_MAX 10
#घोषणा TRACK_AGAIN_CARD_WEIGHT_PENALTY  1000
#घोषणा TRACK_AGAIN_QUEUE_WEIGHT_PENALTY 10000

काष्ठा zcrypt_ops अणु
	दीर्घ (*rsa_modexpo)(काष्ठा zcrypt_queue *, काष्ठा ica_rsa_modexpo *,
			    काष्ठा ap_message *);
	दीर्घ (*rsa_modexpo_crt)(काष्ठा zcrypt_queue *,
				काष्ठा ica_rsa_modexpo_crt *,
				काष्ठा ap_message *);
	दीर्घ (*send_cprb)(bool userspace, काष्ठा zcrypt_queue *, काष्ठा ica_xcRB *,
			  काष्ठा ap_message *);
	दीर्घ (*send_ep11_cprb)(bool userspace, काष्ठा zcrypt_queue *, काष्ठा ep11_urb *,
			       काष्ठा ap_message *);
	दीर्घ (*rng)(काष्ठा zcrypt_queue *, अक्षर *, काष्ठा ap_message *);
	काष्ठा list_head list;		/* zcrypt ops list. */
	काष्ठा module *owner;
	पूर्णांक variant;
	अक्षर name[128];
पूर्ण;

काष्ठा zcrypt_card अणु
	काष्ठा list_head list;		/* Device list. */
	काष्ठा list_head zqueues;	/* List of zcrypt queues */
	काष्ठा kref refcount;		/* device refcounting */
	काष्ठा ap_card *card;		/* The "real" ap card device. */
	पूर्णांक online;			/* User online/offline */

	पूर्णांक user_space_type;		/* User space device id. */
	अक्षर *type_string;		/* User space device name. */
	पूर्णांक min_mod_size;		/* Min number of bits. */
	पूर्णांक max_mod_size;		/* Max number of bits. */
	पूर्णांक max_exp_bit_length;
	स्थिर पूर्णांक *speed_rating;	/* Speed idx of crypto ops. */
	atomic_t load;			/* Utilization of the crypto device */

	पूर्णांक request_count;		/* # current requests. */
पूर्ण;

काष्ठा zcrypt_queue अणु
	काष्ठा list_head list;		/* Device list. */
	काष्ठा kref refcount;		/* device refcounting */
	काष्ठा zcrypt_card *zcard;
	काष्ठा zcrypt_ops *ops;		/* Crypto operations. */
	काष्ठा ap_queue *queue;		/* The "real" ap queue device. */
	पूर्णांक online;			/* User online/offline */

	atomic_t load;			/* Utilization of the crypto device */

	पूर्णांक request_count;		/* # current requests. */

	काष्ठा ap_message reply;	/* Per-device reply काष्ठाure. */
पूर्ण;

/* transport layer rescanning */
बाह्य atomic_t zcrypt_rescan_req;

बाह्य spinlock_t zcrypt_list_lock;
बाह्य पूर्णांक zcrypt_device_count;
बाह्य काष्ठा list_head zcrypt_card_list;

#घोषणा क्रम_each_zcrypt_card(_zc) \
	list_क्रम_each_entry(_zc, &zcrypt_card_list, list)

#घोषणा क्रम_each_zcrypt_queue(_zq, _zc) \
	list_क्रम_each_entry(_zq, &(_zc)->zqueues, list)

काष्ठा zcrypt_card *zcrypt_card_alloc(व्योम);
व्योम zcrypt_card_मुक्त(काष्ठा zcrypt_card *);
व्योम zcrypt_card_get(काष्ठा zcrypt_card *);
पूर्णांक zcrypt_card_put(काष्ठा zcrypt_card *);
पूर्णांक zcrypt_card_रेजिस्टर(काष्ठा zcrypt_card *);
व्योम zcrypt_card_unरेजिस्टर(काष्ठा zcrypt_card *);

काष्ठा zcrypt_queue *zcrypt_queue_alloc(माप_प्रकार);
व्योम zcrypt_queue_मुक्त(काष्ठा zcrypt_queue *);
व्योम zcrypt_queue_get(काष्ठा zcrypt_queue *);
पूर्णांक zcrypt_queue_put(काष्ठा zcrypt_queue *);
पूर्णांक zcrypt_queue_रेजिस्टर(काष्ठा zcrypt_queue *);
व्योम zcrypt_queue_unरेजिस्टर(काष्ठा zcrypt_queue *);
व्योम zcrypt_queue_क्रमce_online(काष्ठा zcrypt_queue *, पूर्णांक);

पूर्णांक zcrypt_rng_device_add(व्योम);
व्योम zcrypt_rng_device_हटाओ(व्योम);

व्योम zcrypt_msgtype_रेजिस्टर(काष्ठा zcrypt_ops *);
व्योम zcrypt_msgtype_unरेजिस्टर(काष्ठा zcrypt_ops *);
काष्ठा zcrypt_ops *zcrypt_msgtype(अचिन्हित अक्षर *, पूर्णांक);
पूर्णांक zcrypt_api_init(व्योम);
व्योम zcrypt_api_निकास(व्योम);
दीर्घ zcrypt_send_cprb(काष्ठा ica_xcRB *xcRB);
दीर्घ zcrypt_send_ep11_cprb(काष्ठा ep11_urb *urb);
व्योम zcrypt_device_status_mask_ext(काष्ठा zcrypt_device_status_ext *devstatus);
पूर्णांक zcrypt_device_status_ext(पूर्णांक card, पूर्णांक queue,
			     काष्ठा zcrypt_device_status_ext *devstatus);

पूर्णांक zcrypt_रुको_api_operational(व्योम);

अटल अंतरभूत अचिन्हित दीर्घ z_copy_from_user(bool userspace,
					     व्योम *to,
					     स्थिर व्योम __user *from,
					     अचिन्हित दीर्घ n)
अणु
	अगर (likely(userspace))
		वापस copy_from_user(to, from, n);
	स_नकल(to, (व्योम __क्रमce *) from, n);
	वापस 0;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ z_copy_to_user(bool userspace,
					   व्योम __user *to,
					   स्थिर व्योम *from,
					   अचिन्हित दीर्घ n)
अणु
	अगर (likely(userspace))
		वापस copy_to_user(to, from, n);
	स_नकल((व्योम __क्रमce *) to, from, n);
	वापस 0;
पूर्ण

#पूर्ण_अगर /* _ZCRYPT_API_H_ */
