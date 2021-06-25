<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *  Copyright IBM Corp. 2001, 2018
 *  Author(s): Robert Burroughs
 *	       Eric Rossman (edrossma@us.ibm.com)
 *
 *  Hotplug & misc device support: Jochen Roehrig (roehrig@de.ibm.com)
 *  Major cleanup & driver split: Martin Schwidefsky <schwidefsky@de.ibm.com>
 *				  Ralph Wuerthner <rwuerthn@de.ibm.com>
 *  MSGTYPE reकाष्ठा:		  Holger Dengler <hd@linux.vnet.ibm.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/atomic.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/mod_devicetable.h>

#समावेश "ap_bus.h"
#समावेश "zcrypt_api.h"
#समावेश "zcrypt_error.h"
#समावेश "zcrypt_msgtype6.h"
#समावेश "zcrypt_cex2c.h"
#समावेश "zcrypt_cca_key.h"
#समावेश "zcrypt_ccamisc.h"

#घोषणा CEX2C_MIN_MOD_SIZE	 16	/*  128 bits	*/
#घोषणा CEX2C_MAX_MOD_SIZE	256	/* 2048 bits	*/
#घोषणा CEX3C_MIN_MOD_SIZE	 16	/*  128 bits	*/
#घोषणा CEX3C_MAX_MOD_SIZE	512	/* 4096 bits	*/
#घोषणा CEX2C_MAX_XCRB_MESSAGE_SIZE (12*1024)
#घोषणा CEX2C_CLEANUP_TIME	(15*HZ)

MODULE_AUTHOR("IBM Corporation");
MODULE_DESCRIPTION("CEX2C/CEX3C Cryptographic Coprocessor device driver, " \
		   "Copyright IBM Corp. 2001, 2018");
MODULE_LICENSE("GPL");

अटल काष्ठा ap_device_id zcrypt_cex2c_card_ids[] = अणु
	अणु .dev_type = AP_DEVICE_TYPE_CEX2C,
	  .match_flags = AP_DEVICE_ID_MATCH_CARD_TYPE पूर्ण,
	अणु .dev_type = AP_DEVICE_TYPE_CEX3C,
	  .match_flags = AP_DEVICE_ID_MATCH_CARD_TYPE पूर्ण,
	अणु /* end of list */ पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(ap, zcrypt_cex2c_card_ids);

अटल काष्ठा ap_device_id zcrypt_cex2c_queue_ids[] = अणु
	अणु .dev_type = AP_DEVICE_TYPE_CEX2C,
	  .match_flags = AP_DEVICE_ID_MATCH_QUEUE_TYPE पूर्ण,
	अणु .dev_type = AP_DEVICE_TYPE_CEX3C,
	  .match_flags = AP_DEVICE_ID_MATCH_QUEUE_TYPE पूर्ण,
	अणु /* end of list */ पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(ap, zcrypt_cex2c_queue_ids);

/*
 * CCA card additional device attributes
 */
अटल sमाप_प्रकार cca_serialnr_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 अक्षर *buf)
अणु
	काष्ठा cca_info ci;
	काष्ठा ap_card *ac = to_ap_card(dev);
	काष्ठा zcrypt_card *zc = ac->निजी;

	स_रखो(&ci, 0, माप(ci));

	अगर (ap_करोमुख्य_index >= 0)
		cca_get_info(ac->id, ap_करोमुख्य_index, &ci, zc->online);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%s\n", ci.serial);
पूर्ण

अटल काष्ठा device_attribute dev_attr_cca_serialnr =
	__ATTR(serialnr, 0444, cca_serialnr_show, शून्य);

अटल काष्ठा attribute *cca_card_attrs[] = अणु
	&dev_attr_cca_serialnr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group cca_card_attr_grp = अणु
	.attrs = cca_card_attrs,
पूर्ण;

 /*
  * CCA queue additional device attributes
  */
अटल sमाप_प्रकार cca_mkvps_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	पूर्णांक n = 0;
	काष्ठा cca_info ci;
	काष्ठा zcrypt_queue *zq = to_ap_queue(dev)->निजी;
	अटल स्थिर अक्षर * स्थिर cao_state[] = अणु "invalid", "valid" पूर्ण;
	अटल स्थिर अक्षर * स्थिर new_state[] = अणु "empty", "partial", "full" पूर्ण;

	स_रखो(&ci, 0, माप(ci));

	cca_get_info(AP_QID_CARD(zq->queue->qid),
		     AP_QID_QUEUE(zq->queue->qid),
		     &ci, zq->online);

	अगर (ci.new_aes_mk_state >= '1' && ci.new_aes_mk_state <= '3')
		n = scnम_लिखो(buf, PAGE_SIZE, "AES NEW: %s 0x%016llx\n",
			      new_state[ci.new_aes_mk_state - '1'],
			      ci.new_aes_mkvp);
	अन्यथा
		n = scnम_लिखो(buf, PAGE_SIZE, "AES NEW: - -\n");

	अगर (ci.cur_aes_mk_state >= '1' && ci.cur_aes_mk_state <= '2')
		n += scnम_लिखो(buf + n, PAGE_SIZE - n,
			       "AES CUR: %s 0x%016llx\n",
			       cao_state[ci.cur_aes_mk_state - '1'],
			       ci.cur_aes_mkvp);
	अन्यथा
		n += scnम_लिखो(buf + n, PAGE_SIZE - n, "AES CUR: - -\n");

	अगर (ci.old_aes_mk_state >= '1' && ci.old_aes_mk_state <= '2')
		n += scnम_लिखो(buf + n, PAGE_SIZE - n,
			       "AES OLD: %s 0x%016llx\n",
			       cao_state[ci.old_aes_mk_state - '1'],
			       ci.old_aes_mkvp);
	अन्यथा
		n += scnम_लिखो(buf + n, PAGE_SIZE - n, "AES OLD: - -\n");

	अगर (ci.new_apka_mk_state >= '1' && ci.new_apka_mk_state <= '3')
		n += scnम_लिखो(buf + n, PAGE_SIZE - n,
			       "APKA NEW: %s 0x%016llx\n",
			       new_state[ci.new_apka_mk_state - '1'],
			       ci.new_apka_mkvp);
	अन्यथा
		n += scnम_लिखो(buf + n, PAGE_SIZE - n, "APKA NEW: - -\n");

	अगर (ci.cur_apka_mk_state >= '1' && ci.cur_apka_mk_state <= '2')
		n += scnम_लिखो(buf + n, PAGE_SIZE - n,
			       "APKA CUR: %s 0x%016llx\n",
			       cao_state[ci.cur_apka_mk_state - '1'],
			       ci.cur_apka_mkvp);
	अन्यथा
		n += scnम_लिखो(buf + n, PAGE_SIZE - n, "APKA CUR: - -\n");

	अगर (ci.old_apka_mk_state >= '1' && ci.old_apka_mk_state <= '2')
		n += scnम_लिखो(buf + n, PAGE_SIZE - n,
			       "APKA OLD: %s 0x%016llx\n",
			       cao_state[ci.old_apka_mk_state - '1'],
			       ci.old_apka_mkvp);
	अन्यथा
		n += scnम_लिखो(buf + n, PAGE_SIZE - n, "APKA OLD: - -\n");

	वापस n;
पूर्ण

अटल काष्ठा device_attribute dev_attr_cca_mkvps =
	__ATTR(mkvps, 0444, cca_mkvps_show, शून्य);

अटल काष्ठा attribute *cca_queue_attrs[] = अणु
	&dev_attr_cca_mkvps.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group cca_queue_attr_grp = अणु
	.attrs = cca_queue_attrs,
पूर्ण;

/**
 * Large अक्रमom number detection function. Its sends a message to a CEX2C/CEX3C
 * card to find out अगर large अक्रमom numbers are supported.
 * @ap_dev: poपूर्णांकer to the AP device.
 *
 * Returns 1 अगर large अक्रमom numbers are supported, 0 अगर not and < 0 on error.
 */
अटल पूर्णांक zcrypt_cex2c_rng_supported(काष्ठा ap_queue *aq)
अणु
	काष्ठा ap_message ap_msg;
	अचिन्हित दीर्घ दीर्घ psmid;
	अचिन्हित पूर्णांक करोमुख्य;
	काष्ठा अणु
		काष्ठा type86_hdr hdr;
		काष्ठा type86_fmt2_ext fmt2;
		काष्ठा CPRBX cprbx;
	पूर्ण __packed *reply;
	काष्ठा अणु
		काष्ठा type6_hdr hdr;
		काष्ठा CPRBX cprbx;
		अक्षर function_code[2];
		लघु पूर्णांक rule_length;
		अक्षर rule[8];
		लघु पूर्णांक verb_length;
		लघु पूर्णांक key_length;
	पूर्ण __packed *msg;
	पूर्णांक rc, i;

	ap_init_message(&ap_msg);
	ap_msg.msg = (व्योम *) get_zeroed_page(GFP_KERNEL);
	अगर (!ap_msg.msg)
		वापस -ENOMEM;

	rng_type6CPRB_msgX(&ap_msg, 4, &करोमुख्य);

	msg = ap_msg.msg;
	msg->cprbx.करोमुख्य = AP_QID_QUEUE(aq->qid);

	rc = ap_send(aq->qid, 0x0102030405060708ULL, ap_msg.msg, ap_msg.len);
	अगर (rc)
		जाओ out_मुक्त;

	/* Wait क्रम the test message to complete. */
	क्रम (i = 0; i < 2 * HZ; i++) अणु
		msleep(1000 / HZ);
		rc = ap_recv(aq->qid, &psmid, ap_msg.msg, 4096);
		अगर (rc == 0 && psmid == 0x0102030405060708ULL)
			अवरोध;
	पूर्ण

	अगर (i >= 2 * HZ) अणु
		/* Got no answer. */
		rc = -ENODEV;
		जाओ out_मुक्त;
	पूर्ण

	reply = ap_msg.msg;
	अगर (reply->cprbx.ccp_rtcode == 0 && reply->cprbx.ccp_rscode == 0)
		rc = 1;
	अन्यथा
		rc = 0;
out_मुक्त:
	मुक्त_page((अचिन्हित दीर्घ) ap_msg.msg);
	वापस rc;
पूर्ण

/**
 * Probe function क्रम CEX2C/CEX3C card devices. It always accepts the
 * AP device since the bus_match alपढ़ोy checked the hardware type.
 * @ap_dev: poपूर्णांकer to the AP card device.
 */
अटल पूर्णांक zcrypt_cex2c_card_probe(काष्ठा ap_device *ap_dev)
अणु
	/*
	 * Normalized speed ratings per crypto adapter
	 * MEX_1k, MEX_2k, MEX_4k, CRT_1k, CRT_2k, CRT_4k, RNG, SECKEY
	 */
	अटल स्थिर पूर्णांक CEX2C_SPEED_IDX[] = अणु
		1000, 1400, 2400, 1100, 1500, 2600, 100, 12पूर्ण;
	अटल स्थिर पूर्णांक CEX3C_SPEED_IDX[] = अणु
		500,  700, 1400,  550,	800, 1500,  80, 10पूर्ण;

	काष्ठा ap_card *ac = to_ap_card(&ap_dev->device);
	काष्ठा zcrypt_card *zc;
	पूर्णांक rc = 0;

	zc = zcrypt_card_alloc();
	अगर (!zc)
		वापस -ENOMEM;
	zc->card = ac;
	ac->निजी = zc;
	चयन (ac->ap_dev.device_type) अणु
	हाल AP_DEVICE_TYPE_CEX2C:
		zc->user_space_type = ZCRYPT_CEX2C;
		zc->type_string = "CEX2C";
		zc->speed_rating = CEX2C_SPEED_IDX;
		zc->min_mod_size = CEX2C_MIN_MOD_SIZE;
		zc->max_mod_size = CEX2C_MAX_MOD_SIZE;
		zc->max_exp_bit_length = CEX2C_MAX_MOD_SIZE;
		अवरोध;
	हाल AP_DEVICE_TYPE_CEX3C:
		zc->user_space_type = ZCRYPT_CEX3C;
		zc->type_string = "CEX3C";
		zc->speed_rating = CEX3C_SPEED_IDX;
		zc->min_mod_size = CEX3C_MIN_MOD_SIZE;
		zc->max_mod_size = CEX3C_MAX_MOD_SIZE;
		zc->max_exp_bit_length = CEX3C_MAX_MOD_SIZE;
		अवरोध;
	शेष:
		zcrypt_card_मुक्त(zc);
		वापस -ENODEV;
	पूर्ण
	zc->online = 1;

	rc = zcrypt_card_रेजिस्टर(zc);
	अगर (rc) अणु
		ac->निजी = शून्य;
		zcrypt_card_मुक्त(zc);
		वापस rc;
	पूर्ण

	अगर (ap_test_bit(&ac->functions, AP_FUNC_COPRO)) अणु
		rc = sysfs_create_group(&ap_dev->device.kobj,
					&cca_card_attr_grp);
		अगर (rc) अणु
			zcrypt_card_unरेजिस्टर(zc);
			ac->निजी = शून्य;
			zcrypt_card_मुक्त(zc);
		पूर्ण
	पूर्ण

	वापस rc;
पूर्ण

/**
 * This is called to हटाओ the CEX2C/CEX3C card driver inक्रमmation
 * अगर an AP card device is हटाओd.
 */
अटल व्योम zcrypt_cex2c_card_हटाओ(काष्ठा ap_device *ap_dev)
अणु
	काष्ठा ap_card *ac = to_ap_card(&ap_dev->device);
	काष्ठा zcrypt_card *zc = to_ap_card(&ap_dev->device)->निजी;

	अगर (ap_test_bit(&ac->functions, AP_FUNC_COPRO))
		sysfs_हटाओ_group(&ap_dev->device.kobj, &cca_card_attr_grp);
	अगर (zc)
		zcrypt_card_unरेजिस्टर(zc);
पूर्ण

अटल काष्ठा ap_driver zcrypt_cex2c_card_driver = अणु
	.probe = zcrypt_cex2c_card_probe,
	.हटाओ = zcrypt_cex2c_card_हटाओ,
	.ids = zcrypt_cex2c_card_ids,
	.flags = AP_DRIVER_FLAG_DEFAULT,
पूर्ण;

/**
 * Probe function क्रम CEX2C/CEX3C queue devices. It always accepts the
 * AP device since the bus_match alपढ़ोy checked the hardware type.
 * @ap_dev: poपूर्णांकer to the AP card device.
 */
अटल पूर्णांक zcrypt_cex2c_queue_probe(काष्ठा ap_device *ap_dev)
अणु
	काष्ठा ap_queue *aq = to_ap_queue(&ap_dev->device);
	काष्ठा zcrypt_queue *zq;
	पूर्णांक rc;

	zq = zcrypt_queue_alloc(CEX2C_MAX_XCRB_MESSAGE_SIZE);
	अगर (!zq)
		वापस -ENOMEM;
	zq->queue = aq;
	zq->online = 1;
	atomic_set(&zq->load, 0);
	ap_rapq(aq->qid);
	rc = zcrypt_cex2c_rng_supported(aq);
	अगर (rc < 0) अणु
		zcrypt_queue_मुक्त(zq);
		वापस rc;
	पूर्ण
	अगर (rc)
		zq->ops = zcrypt_msgtype(MSGTYPE06_NAME,
					 MSGTYPE06_VARIANT_DEFAULT);
	अन्यथा
		zq->ops = zcrypt_msgtype(MSGTYPE06_NAME,
					 MSGTYPE06_VARIANT_NORNG);
	ap_queue_init_state(aq);
	ap_queue_init_reply(aq, &zq->reply);
	aq->request_समयout = CEX2C_CLEANUP_TIME;
	aq->निजी = zq;
	rc = zcrypt_queue_रेजिस्टर(zq);
	अगर (rc) अणु
		aq->निजी = शून्य;
		zcrypt_queue_मुक्त(zq);
		वापस rc;
	पूर्ण

	अगर (ap_test_bit(&aq->card->functions, AP_FUNC_COPRO)) अणु
		rc = sysfs_create_group(&ap_dev->device.kobj,
					&cca_queue_attr_grp);
		अगर (rc) अणु
			zcrypt_queue_unरेजिस्टर(zq);
			aq->निजी = शून्य;
			zcrypt_queue_मुक्त(zq);
		पूर्ण
	पूर्ण

	वापस rc;
पूर्ण

/**
 * This is called to हटाओ the CEX2C/CEX3C queue driver inक्रमmation
 * अगर an AP queue device is हटाओd.
 */
अटल व्योम zcrypt_cex2c_queue_हटाओ(काष्ठा ap_device *ap_dev)
अणु
	काष्ठा ap_queue *aq = to_ap_queue(&ap_dev->device);
	काष्ठा zcrypt_queue *zq = aq->निजी;

	अगर (ap_test_bit(&aq->card->functions, AP_FUNC_COPRO))
		sysfs_हटाओ_group(&ap_dev->device.kobj, &cca_queue_attr_grp);
	अगर (zq)
		zcrypt_queue_unरेजिस्टर(zq);
पूर्ण

अटल काष्ठा ap_driver zcrypt_cex2c_queue_driver = अणु
	.probe = zcrypt_cex2c_queue_probe,
	.हटाओ = zcrypt_cex2c_queue_हटाओ,
	.ids = zcrypt_cex2c_queue_ids,
	.flags = AP_DRIVER_FLAG_DEFAULT,
पूर्ण;

पूर्णांक __init zcrypt_cex2c_init(व्योम)
अणु
	पूर्णांक rc;

	rc = ap_driver_रेजिस्टर(&zcrypt_cex2c_card_driver,
				THIS_MODULE, "cex2card");
	अगर (rc)
		वापस rc;

	rc = ap_driver_रेजिस्टर(&zcrypt_cex2c_queue_driver,
				THIS_MODULE, "cex2cqueue");
	अगर (rc)
		ap_driver_unरेजिस्टर(&zcrypt_cex2c_card_driver);

	वापस rc;
पूर्ण

व्योम zcrypt_cex2c_निकास(व्योम)
अणु
	ap_driver_unरेजिस्टर(&zcrypt_cex2c_queue_driver);
	ap_driver_unरेजिस्टर(&zcrypt_cex2c_card_driver);
पूर्ण

module_init(zcrypt_cex2c_init);
module_निकास(zcrypt_cex2c_निकास);
