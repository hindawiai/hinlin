<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *  Copyright IBM Corp. 2001, 2012
 *  Author(s): Robert Burroughs
 *	       Eric Rossman (edrossma@us.ibm.com)
 *
 *  Hotplug & misc device support: Jochen Roehrig (roehrig@de.ibm.com)
 *  Major cleanup & driver split: Martin Schwidefsky <schwidefsky@de.ibm.com>
 *				  Ralph Wuerthner <rwuerthn@de.ibm.com>
 *  MSGTYPE reकाष्ठा:		  Holger Dengler <hd@linux.vnet.ibm.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/atomic.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/mod_devicetable.h>

#समावेश "ap_bus.h"
#समावेश "zcrypt_api.h"
#समावेश "zcrypt_error.h"
#समावेश "zcrypt_cex2a.h"
#समावेश "zcrypt_msgtype50.h"

#घोषणा CEX2A_MIN_MOD_SIZE	  1	/*    8 bits	*/
#घोषणा CEX2A_MAX_MOD_SIZE	256	/* 2048 bits	*/
#घोषणा CEX3A_MIN_MOD_SIZE	CEX2A_MIN_MOD_SIZE
#घोषणा CEX3A_MAX_MOD_SIZE	512	/* 4096 bits	*/

#घोषणा CEX2A_MAX_MESSAGE_SIZE	0x390	/* माप(काष्ठा type50_crb2_msg)    */
#घोषणा CEX2A_MAX_RESPONSE_SIZE 0x110	/* max outputdatalength + type80_hdr */

#घोषणा CEX3A_MAX_RESPONSE_SIZE	0x210	/* 512 bit modulus
					 * (max outputdatalength) +
					 * type80_hdr*/
#घोषणा CEX3A_MAX_MESSAGE_SIZE	माप(काष्ठा type50_crb3_msg)

#घोषणा CEX2A_CLEANUP_TIME	(15*HZ)
#घोषणा CEX3A_CLEANUP_TIME	CEX2A_CLEANUP_TIME

MODULE_AUTHOR("IBM Corporation");
MODULE_DESCRIPTION("CEX2A/CEX3A Cryptographic Coprocessor device driver, " \
		   "Copyright IBM Corp. 2001, 2018");
MODULE_LICENSE("GPL");

अटल काष्ठा ap_device_id zcrypt_cex2a_card_ids[] = अणु
	अणु .dev_type = AP_DEVICE_TYPE_CEX2A,
	  .match_flags = AP_DEVICE_ID_MATCH_CARD_TYPE पूर्ण,
	अणु .dev_type = AP_DEVICE_TYPE_CEX3A,
	  .match_flags = AP_DEVICE_ID_MATCH_CARD_TYPE पूर्ण,
	अणु /* end of list */ पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(ap, zcrypt_cex2a_card_ids);

अटल काष्ठा ap_device_id zcrypt_cex2a_queue_ids[] = अणु
	अणु .dev_type = AP_DEVICE_TYPE_CEX2A,
	  .match_flags = AP_DEVICE_ID_MATCH_QUEUE_TYPE पूर्ण,
	अणु .dev_type = AP_DEVICE_TYPE_CEX3A,
	  .match_flags = AP_DEVICE_ID_MATCH_QUEUE_TYPE पूर्ण,
	अणु /* end of list */ पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(ap, zcrypt_cex2a_queue_ids);

/**
 * Probe function क्रम CEX2A card devices. It always accepts the AP device
 * since the bus_match alपढ़ोy checked the card type.
 * @ap_dev: poपूर्णांकer to the AP device.
 */
अटल पूर्णांक zcrypt_cex2a_card_probe(काष्ठा ap_device *ap_dev)
अणु
	/*
	 * Normalized speed ratings per crypto adapter
	 * MEX_1k, MEX_2k, MEX_4k, CRT_1k, CRT_2k, CRT_4k, RNG, SECKEY
	 */
	अटल स्थिर पूर्णांक CEX2A_SPEED_IDX[] = अणु
		800, 1000, 2000,  900, 1200, 2400, 0, 0पूर्ण;
	अटल स्थिर पूर्णांक CEX3A_SPEED_IDX[] = अणु
		400,  500, 1000,  450,	550, 1200, 0, 0पूर्ण;

	काष्ठा ap_card *ac = to_ap_card(&ap_dev->device);
	काष्ठा zcrypt_card *zc;
	पूर्णांक rc = 0;

	zc = zcrypt_card_alloc();
	अगर (!zc)
		वापस -ENOMEM;
	zc->card = ac;
	ac->निजी = zc;

	अगर (ac->ap_dev.device_type == AP_DEVICE_TYPE_CEX2A) अणु
		zc->min_mod_size = CEX2A_MIN_MOD_SIZE;
		zc->max_mod_size = CEX2A_MAX_MOD_SIZE;
		zc->speed_rating = CEX2A_SPEED_IDX;
		zc->max_exp_bit_length = CEX2A_MAX_MOD_SIZE;
		zc->type_string = "CEX2A";
		zc->user_space_type = ZCRYPT_CEX2A;
	पूर्ण अन्यथा अगर (ac->ap_dev.device_type == AP_DEVICE_TYPE_CEX3A) अणु
		zc->min_mod_size = CEX2A_MIN_MOD_SIZE;
		zc->max_mod_size = CEX2A_MAX_MOD_SIZE;
		zc->max_exp_bit_length = CEX2A_MAX_MOD_SIZE;
		अगर (ap_test_bit(&ac->functions, AP_FUNC_MEX4K) &&
		    ap_test_bit(&ac->functions, AP_FUNC_CRT4K)) अणु
			zc->max_mod_size = CEX3A_MAX_MOD_SIZE;
			zc->max_exp_bit_length = CEX3A_MAX_MOD_SIZE;
		पूर्ण
		zc->speed_rating = CEX3A_SPEED_IDX;
		zc->type_string = "CEX3A";
		zc->user_space_type = ZCRYPT_CEX3A;
	पूर्ण अन्यथा अणु
		zcrypt_card_मुक्त(zc);
		वापस -ENODEV;
	पूर्ण
	zc->online = 1;

	rc = zcrypt_card_रेजिस्टर(zc);
	अगर (rc) अणु
		ac->निजी = शून्य;
		zcrypt_card_मुक्त(zc);
	पूर्ण

	वापस rc;
पूर्ण

/**
 * This is called to हटाओ the CEX2A card driver inक्रमmation
 * अगर an AP card device is हटाओd.
 */
अटल व्योम zcrypt_cex2a_card_हटाओ(काष्ठा ap_device *ap_dev)
अणु
	काष्ठा zcrypt_card *zc = to_ap_card(&ap_dev->device)->निजी;

	अगर (zc)
		zcrypt_card_unरेजिस्टर(zc);
पूर्ण

अटल काष्ठा ap_driver zcrypt_cex2a_card_driver = अणु
	.probe = zcrypt_cex2a_card_probe,
	.हटाओ = zcrypt_cex2a_card_हटाओ,
	.ids = zcrypt_cex2a_card_ids,
	.flags = AP_DRIVER_FLAG_DEFAULT,
पूर्ण;

/**
 * Probe function क्रम CEX2A queue devices. It always accepts the AP device
 * since the bus_match alपढ़ोy checked the queue type.
 * @ap_dev: poपूर्णांकer to the AP device.
 */
अटल पूर्णांक zcrypt_cex2a_queue_probe(काष्ठा ap_device *ap_dev)
अणु
	काष्ठा ap_queue *aq = to_ap_queue(&ap_dev->device);
	काष्ठा zcrypt_queue *zq = शून्य;
	पूर्णांक rc;

	चयन (ap_dev->device_type) अणु
	हाल AP_DEVICE_TYPE_CEX2A:
		zq = zcrypt_queue_alloc(CEX2A_MAX_RESPONSE_SIZE);
		अगर (!zq)
			वापस -ENOMEM;
		अवरोध;
	हाल AP_DEVICE_TYPE_CEX3A:
		zq = zcrypt_queue_alloc(CEX3A_MAX_RESPONSE_SIZE);
		अगर (!zq)
			वापस -ENOMEM;
		अवरोध;
	पूर्ण
	अगर (!zq)
		वापस -ENODEV;
	zq->ops = zcrypt_msgtype(MSGTYPE50_NAME, MSGTYPE50_VARIANT_DEFAULT);
	zq->queue = aq;
	zq->online = 1;
	atomic_set(&zq->load, 0);
	ap_queue_init_state(aq);
	ap_queue_init_reply(aq, &zq->reply);
	aq->request_समयout = CEX2A_CLEANUP_TIME;
	aq->निजी = zq;
	rc = zcrypt_queue_रेजिस्टर(zq);
	अगर (rc) अणु
		aq->निजी = शून्य;
		zcrypt_queue_मुक्त(zq);
	पूर्ण

	वापस rc;
पूर्ण

/**
 * This is called to हटाओ the CEX2A queue driver inक्रमmation
 * अगर an AP queue device is हटाओd.
 */
अटल व्योम zcrypt_cex2a_queue_हटाओ(काष्ठा ap_device *ap_dev)
अणु
	काष्ठा ap_queue *aq = to_ap_queue(&ap_dev->device);
	काष्ठा zcrypt_queue *zq = aq->निजी;

	अगर (zq)
		zcrypt_queue_unरेजिस्टर(zq);
पूर्ण

अटल काष्ठा ap_driver zcrypt_cex2a_queue_driver = अणु
	.probe = zcrypt_cex2a_queue_probe,
	.हटाओ = zcrypt_cex2a_queue_हटाओ,
	.ids = zcrypt_cex2a_queue_ids,
	.flags = AP_DRIVER_FLAG_DEFAULT,
पूर्ण;

पूर्णांक __init zcrypt_cex2a_init(व्योम)
अणु
	पूर्णांक rc;

	rc = ap_driver_रेजिस्टर(&zcrypt_cex2a_card_driver,
				THIS_MODULE, "cex2acard");
	अगर (rc)
		वापस rc;

	rc = ap_driver_रेजिस्टर(&zcrypt_cex2a_queue_driver,
				THIS_MODULE, "cex2aqueue");
	अगर (rc)
		ap_driver_unरेजिस्टर(&zcrypt_cex2a_card_driver);

	वापस rc;
पूर्ण

व्योम __निकास zcrypt_cex2a_निकास(व्योम)
अणु
	ap_driver_unरेजिस्टर(&zcrypt_cex2a_queue_driver);
	ap_driver_unरेजिस्टर(&zcrypt_cex2a_card_driver);
पूर्ण

module_init(zcrypt_cex2a_init);
module_निकास(zcrypt_cex2a_निकास);
