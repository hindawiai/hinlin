<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Copyright IBM Corp. 2012, 2019
 *  Author(s): Holger Dengler <hd@linux.vnet.ibm.com>
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
#समावेश "zcrypt_msgtype6.h"
#समावेश "zcrypt_msgtype50.h"
#समावेश "zcrypt_error.h"
#समावेश "zcrypt_cex4.h"
#समावेश "zcrypt_ccamisc.h"
#समावेश "zcrypt_ep11misc.h"

#घोषणा CEX4A_MIN_MOD_SIZE	  1	/*    8 bits	*/
#घोषणा CEX4A_MAX_MOD_SIZE_2K	256	/* 2048 bits	*/
#घोषणा CEX4A_MAX_MOD_SIZE_4K	512	/* 4096 bits	*/

#घोषणा CEX4C_MIN_MOD_SIZE	 16	/*  256 bits	*/
#घोषणा CEX4C_MAX_MOD_SIZE	512	/* 4096 bits	*/

#घोषणा CEX4A_MAX_MESSAGE_SIZE	MSGTYPE50_CRB3_MAX_MSG_SIZE
#घोषणा CEX4C_MAX_MESSAGE_SIZE	MSGTYPE06_MAX_MSG_SIZE

/* Waiting समय क्रम requests to be processed.
 * Currently there are some types of request which are not deterministic.
 * But the maximum समय limit managed by the stomper code is set to 60sec.
 * Hence we have to रुको at least that समय period.
 */
#घोषणा CEX4_CLEANUP_TIME	(900*HZ)

MODULE_AUTHOR("IBM Corporation");
MODULE_DESCRIPTION("CEX4/CEX5/CEX6/CEX7 Cryptographic Card device driver, " \
		   "Copyright IBM Corp. 2019");
MODULE_LICENSE("GPL");

अटल काष्ठा ap_device_id zcrypt_cex4_card_ids[] = अणु
	अणु .dev_type = AP_DEVICE_TYPE_CEX4,
	  .match_flags = AP_DEVICE_ID_MATCH_CARD_TYPE पूर्ण,
	अणु .dev_type = AP_DEVICE_TYPE_CEX5,
	  .match_flags = AP_DEVICE_ID_MATCH_CARD_TYPE पूर्ण,
	अणु .dev_type = AP_DEVICE_TYPE_CEX6,
	  .match_flags = AP_DEVICE_ID_MATCH_CARD_TYPE पूर्ण,
	अणु .dev_type = AP_DEVICE_TYPE_CEX7,
	  .match_flags = AP_DEVICE_ID_MATCH_CARD_TYPE पूर्ण,
	अणु /* end of list */ पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(ap, zcrypt_cex4_card_ids);

अटल काष्ठा ap_device_id zcrypt_cex4_queue_ids[] = अणु
	अणु .dev_type = AP_DEVICE_TYPE_CEX4,
	  .match_flags = AP_DEVICE_ID_MATCH_QUEUE_TYPE पूर्ण,
	अणु .dev_type = AP_DEVICE_TYPE_CEX5,
	  .match_flags = AP_DEVICE_ID_MATCH_QUEUE_TYPE पूर्ण,
	अणु .dev_type = AP_DEVICE_TYPE_CEX6,
	  .match_flags = AP_DEVICE_ID_MATCH_QUEUE_TYPE पूर्ण,
	अणु .dev_type = AP_DEVICE_TYPE_CEX7,
	  .match_flags = AP_DEVICE_ID_MATCH_QUEUE_TYPE पूर्ण,
	अणु /* end of list */ पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(ap, zcrypt_cex4_queue_ids);

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

/*
 * EP11 card additional device attributes
 */
अटल sमाप_प्रकार ep11_api_ordinalnr_show(काष्ठा device *dev,
				       काष्ठा device_attribute *attr,
				       अक्षर *buf)
अणु
	काष्ठा ep11_card_info ci;
	काष्ठा ap_card *ac = to_ap_card(dev);
	काष्ठा zcrypt_card *zc = ac->निजी;

	स_रखो(&ci, 0, माप(ci));

	ep11_get_card_info(ac->id, &ci, zc->online);

	अगर (ci.API_ord_nr > 0)
		वापस scnम_लिखो(buf, PAGE_SIZE, "%u\n", ci.API_ord_nr);
	अन्यथा
		वापस scnम_लिखो(buf, PAGE_SIZE, "\n");
पूर्ण

अटल काष्ठा device_attribute dev_attr_ep11_api_ordinalnr =
	__ATTR(API_ordinalnr, 0444, ep11_api_ordinalnr_show, शून्य);

अटल sमाप_प्रकार ep11_fw_version_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    अक्षर *buf)
अणु
	काष्ठा ep11_card_info ci;
	काष्ठा ap_card *ac = to_ap_card(dev);
	काष्ठा zcrypt_card *zc = ac->निजी;

	स_रखो(&ci, 0, माप(ci));

	ep11_get_card_info(ac->id, &ci, zc->online);

	अगर (ci.FW_version > 0)
		वापस scnम_लिखो(buf, PAGE_SIZE, "%d.%d\n",
				 (पूर्णांक)(ci.FW_version >> 8),
				 (पूर्णांक)(ci.FW_version & 0xFF));
	अन्यथा
		वापस scnम_लिखो(buf, PAGE_SIZE, "\n");
पूर्ण

अटल काष्ठा device_attribute dev_attr_ep11_fw_version =
	__ATTR(FW_version, 0444, ep11_fw_version_show, शून्य);

अटल sमाप_प्रकार ep11_serialnr_show(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  अक्षर *buf)
अणु
	काष्ठा ep11_card_info ci;
	काष्ठा ap_card *ac = to_ap_card(dev);
	काष्ठा zcrypt_card *zc = ac->निजी;

	स_रखो(&ci, 0, माप(ci));

	ep11_get_card_info(ac->id, &ci, zc->online);

	अगर (ci.serial[0])
		वापस scnम_लिखो(buf, PAGE_SIZE, "%16.16s\n", ci.serial);
	अन्यथा
		वापस scnम_लिखो(buf, PAGE_SIZE, "\n");
पूर्ण

अटल काष्ठा device_attribute dev_attr_ep11_serialnr =
	__ATTR(serialnr, 0444, ep11_serialnr_show, शून्य);

अटल स्थिर काष्ठा अणु
	पूर्णांक	    mode_bit;
	स्थिर अक्षर *mode_txt;
पूर्ण ep11_op_modes[] = अणु
	अणु 0, "FIPS2009" पूर्ण,
	अणु 1, "BSI2009" पूर्ण,
	अणु 2, "FIPS2011" पूर्ण,
	अणु 3, "BSI2011" पूर्ण,
	अणु 6, "BSICC2017" पूर्ण,
	अणु 0, शून्य पूर्ण
पूर्ण;

अटल sमाप_प्रकार ep11_card_op_modes_show(काष्ठा device *dev,
				       काष्ठा device_attribute *attr,
				       अक्षर *buf)
अणु
	पूर्णांक i, n = 0;
	काष्ठा ep11_card_info ci;
	काष्ठा ap_card *ac = to_ap_card(dev);
	काष्ठा zcrypt_card *zc = ac->निजी;

	स_रखो(&ci, 0, माप(ci));

	ep11_get_card_info(ac->id, &ci, zc->online);

	क्रम (i = 0; ep11_op_modes[i].mode_txt; i++) अणु
		अगर (ci.op_mode & (1ULL << ep11_op_modes[i].mode_bit)) अणु
			अगर (n > 0)
				buf[n++] = ' ';
			n += scnम_लिखो(buf + n, PAGE_SIZE - n,
				       "%s", ep11_op_modes[i].mode_txt);
		पूर्ण
	पूर्ण
	n += scnम_लिखो(buf + n, PAGE_SIZE - n, "\n");

	वापस n;
पूर्ण

अटल काष्ठा device_attribute dev_attr_ep11_card_op_modes =
	__ATTR(op_modes, 0444, ep11_card_op_modes_show, शून्य);

अटल काष्ठा attribute *ep11_card_attrs[] = अणु
	&dev_attr_ep11_api_ordinalnr.attr,
	&dev_attr_ep11_fw_version.attr,
	&dev_attr_ep11_serialnr.attr,
	&dev_attr_ep11_card_op_modes.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group ep11_card_attr_grp = अणु
	.attrs = ep11_card_attrs,
पूर्ण;

/*
 * EP11 queue additional device attributes
 */

अटल sमाप_प्रकार ep11_mkvps_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr,
			       अक्षर *buf)
अणु
	पूर्णांक n = 0;
	काष्ठा ep11_करोमुख्य_info di;
	काष्ठा zcrypt_queue *zq = to_ap_queue(dev)->निजी;
	अटल स्थिर अक्षर * स्थिर cwk_state[] = अणु "invalid", "valid" पूर्ण;
	अटल स्थिर अक्षर * स्थिर nwk_state[] = अणु "empty", "uncommitted",
						  "committed" पूर्ण;

	स_रखो(&di, 0, माप(di));

	अगर (zq->online)
		ep11_get_करोमुख्य_info(AP_QID_CARD(zq->queue->qid),
				     AP_QID_QUEUE(zq->queue->qid),
				     &di);

	अगर (di.cur_wk_state == '0') अणु
		n = scnम_लिखो(buf, PAGE_SIZE, "WK CUR: %s -\n",
			      cwk_state[di.cur_wk_state - '0']);
	पूर्ण अन्यथा अगर (di.cur_wk_state == '1') अणु
		n = scnम_लिखो(buf, PAGE_SIZE, "WK CUR: %s 0x",
			      cwk_state[di.cur_wk_state - '0']);
		bin2hex(buf + n, di.cur_wkvp, माप(di.cur_wkvp));
		n += 2 * माप(di.cur_wkvp);
		n += scnम_लिखो(buf + n, PAGE_SIZE - n, "\n");
	पूर्ण अन्यथा
		n = scnम_लिखो(buf, PAGE_SIZE, "WK CUR: - -\n");

	अगर (di.new_wk_state == '0') अणु
		n += scnम_लिखो(buf + n, PAGE_SIZE - n, "WK NEW: %s -\n",
			       nwk_state[di.new_wk_state - '0']);
	पूर्ण अन्यथा अगर (di.new_wk_state >= '1' && di.new_wk_state <= '2') अणु
		n += scnम_लिखो(buf + n, PAGE_SIZE - n, "WK NEW: %s 0x",
			       nwk_state[di.new_wk_state - '0']);
		bin2hex(buf + n, di.new_wkvp, माप(di.new_wkvp));
		n += 2 * माप(di.new_wkvp);
		n += scnम_लिखो(buf + n, PAGE_SIZE - n, "\n");
	पूर्ण अन्यथा
		n += scnम_लिखो(buf + n, PAGE_SIZE - n, "WK NEW: - -\n");

	वापस n;
पूर्ण

अटल काष्ठा device_attribute dev_attr_ep11_mkvps =
	__ATTR(mkvps, 0444, ep11_mkvps_show, शून्य);

अटल sमाप_प्रकार ep11_queue_op_modes_show(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	पूर्णांक i, n = 0;
	काष्ठा ep11_करोमुख्य_info di;
	काष्ठा zcrypt_queue *zq = to_ap_queue(dev)->निजी;

	स_रखो(&di, 0, माप(di));

	अगर (zq->online)
		ep11_get_करोमुख्य_info(AP_QID_CARD(zq->queue->qid),
				     AP_QID_QUEUE(zq->queue->qid),
				     &di);

	क्रम (i = 0; ep11_op_modes[i].mode_txt; i++) अणु
		अगर (di.op_mode & (1ULL << ep11_op_modes[i].mode_bit)) अणु
			अगर (n > 0)
				buf[n++] = ' ';
			n += scnम_लिखो(buf + n, PAGE_SIZE - n,
				       "%s", ep11_op_modes[i].mode_txt);
		पूर्ण
	पूर्ण
	n += scnम_लिखो(buf + n, PAGE_SIZE - n, "\n");

	वापस n;
पूर्ण

अटल काष्ठा device_attribute dev_attr_ep11_queue_op_modes =
	__ATTR(op_modes, 0444, ep11_queue_op_modes_show, शून्य);

अटल काष्ठा attribute *ep11_queue_attrs[] = अणु
	&dev_attr_ep11_mkvps.attr,
	&dev_attr_ep11_queue_op_modes.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group ep11_queue_attr_grp = अणु
	.attrs = ep11_queue_attrs,
पूर्ण;

/**
 * Probe function क्रम CEX4/CEX5/CEX6/CEX7 card device. It always
 * accepts the AP device since the bus_match alपढ़ोy checked
 * the hardware type.
 * @ap_dev: poपूर्णांकer to the AP device.
 */
अटल पूर्णांक zcrypt_cex4_card_probe(काष्ठा ap_device *ap_dev)
अणु
	/*
	 * Normalized speed ratings per crypto adapter
	 * MEX_1k, MEX_2k, MEX_4k, CRT_1k, CRT_2k, CRT_4k, RNG, SECKEY
	 */
	अटल स्थिर पूर्णांक CEX4A_SPEED_IDX[NUM_OPS] = अणु
		 14,  19, 249, 42, 228, 1458, 0, 0पूर्ण;
	अटल स्थिर पूर्णांक CEX5A_SPEED_IDX[NUM_OPS] = अणु
		  8,   9,  20, 18,  66,	 458, 0, 0पूर्ण;
	अटल स्थिर पूर्णांक CEX6A_SPEED_IDX[NUM_OPS] = अणु
		  6,   9,  20, 17,  65,	 438, 0, 0पूर्ण;
	अटल स्थिर पूर्णांक CEX7A_SPEED_IDX[NUM_OPS] = अणु
		  6,   8,  17, 15,  54,	 362, 0, 0पूर्ण;

	अटल स्थिर पूर्णांक CEX4C_SPEED_IDX[NUM_OPS] = अणु
		 59,  69, 308, 83, 278, 2204, 209, 40पूर्ण;
	अटल स्थिर पूर्णांक CEX5C_SPEED_IDX[] = अणु
		 24,  31,  50, 37,  90,	 479,  27, 10पूर्ण;
	अटल स्थिर पूर्णांक CEX6C_SPEED_IDX[NUM_OPS] = अणु
		 16,  20,  32, 27,  77,	 455,  24,  9पूर्ण;
	अटल स्थिर पूर्णांक CEX7C_SPEED_IDX[NUM_OPS] = अणु
		 14,  16,  26, 23,  64,	 376,  23,  8पूर्ण;

	अटल स्थिर पूर्णांक CEX4P_SPEED_IDX[NUM_OPS] = अणु
		  0,   0,   0,	 0,   0,   0,	0,  50पूर्ण;
	अटल स्थिर पूर्णांक CEX5P_SPEED_IDX[NUM_OPS] = अणु
		  0,   0,   0,	 0,   0,   0,	0,  10पूर्ण;
	अटल स्थिर पूर्णांक CEX6P_SPEED_IDX[NUM_OPS] = अणु
		  0,   0,   0,	 0,   0,   0,	0,   9पूर्ण;
	अटल स्थिर पूर्णांक CEX7P_SPEED_IDX[NUM_OPS] = अणु
		  0,   0,   0,	 0,   0,   0,	0,   8पूर्ण;

	काष्ठा ap_card *ac = to_ap_card(&ap_dev->device);
	काष्ठा zcrypt_card *zc;
	पूर्णांक rc = 0;

	zc = zcrypt_card_alloc();
	अगर (!zc)
		वापस -ENOMEM;
	zc->card = ac;
	ac->निजी = zc;
	अगर (ap_test_bit(&ac->functions, AP_FUNC_ACCEL)) अणु
		अगर (ac->ap_dev.device_type == AP_DEVICE_TYPE_CEX4) अणु
			zc->type_string = "CEX4A";
			zc->user_space_type = ZCRYPT_CEX4;
			zc->speed_rating = CEX4A_SPEED_IDX;
		पूर्ण अन्यथा अगर (ac->ap_dev.device_type == AP_DEVICE_TYPE_CEX5) अणु
			zc->type_string = "CEX5A";
			zc->user_space_type = ZCRYPT_CEX5;
			zc->speed_rating = CEX5A_SPEED_IDX;
		पूर्ण अन्यथा अगर (ac->ap_dev.device_type == AP_DEVICE_TYPE_CEX6) अणु
			zc->type_string = "CEX6A";
			zc->user_space_type = ZCRYPT_CEX6;
			zc->speed_rating = CEX6A_SPEED_IDX;
		पूर्ण अन्यथा अणु
			zc->type_string = "CEX7A";
			/* wrong user space type, just क्रम compatibility
			 * with the ZCRYPT_STATUS_MASK ioctl.
			 */
			zc->user_space_type = ZCRYPT_CEX6;
			zc->speed_rating = CEX7A_SPEED_IDX;
		पूर्ण
		zc->min_mod_size = CEX4A_MIN_MOD_SIZE;
		अगर (ap_test_bit(&ac->functions, AP_FUNC_MEX4K) &&
		    ap_test_bit(&ac->functions, AP_FUNC_CRT4K)) अणु
			zc->max_mod_size = CEX4A_MAX_MOD_SIZE_4K;
			zc->max_exp_bit_length =
				CEX4A_MAX_MOD_SIZE_4K;
		पूर्ण अन्यथा अणु
			zc->max_mod_size = CEX4A_MAX_MOD_SIZE_2K;
			zc->max_exp_bit_length =
				CEX4A_MAX_MOD_SIZE_2K;
		पूर्ण
	पूर्ण अन्यथा अगर (ap_test_bit(&ac->functions, AP_FUNC_COPRO)) अणु
		अगर (ac->ap_dev.device_type == AP_DEVICE_TYPE_CEX4) अणु
			zc->type_string = "CEX4C";
			/* wrong user space type, must be CEX4
			 * just keep it क्रम cca compatibility
			 */
			zc->user_space_type = ZCRYPT_CEX3C;
			zc->speed_rating = CEX4C_SPEED_IDX;
		पूर्ण अन्यथा अगर (ac->ap_dev.device_type == AP_DEVICE_TYPE_CEX5) अणु
			zc->type_string = "CEX5C";
			/* wrong user space type, must be CEX5
			 * just keep it क्रम cca compatibility
			 */
			zc->user_space_type = ZCRYPT_CEX3C;
			zc->speed_rating = CEX5C_SPEED_IDX;
		पूर्ण अन्यथा अगर (ac->ap_dev.device_type == AP_DEVICE_TYPE_CEX6) अणु
			zc->type_string = "CEX6C";
			/* wrong user space type, must be CEX6
			 * just keep it क्रम cca compatibility
			 */
			zc->user_space_type = ZCRYPT_CEX3C;
			zc->speed_rating = CEX6C_SPEED_IDX;
		पूर्ण अन्यथा अणु
			zc->type_string = "CEX7C";
			/* wrong user space type, must be CEX7
			 * just keep it क्रम cca compatibility
			 */
			zc->user_space_type = ZCRYPT_CEX3C;
			zc->speed_rating = CEX7C_SPEED_IDX;
		पूर्ण
		zc->min_mod_size = CEX4C_MIN_MOD_SIZE;
		zc->max_mod_size = CEX4C_MAX_MOD_SIZE;
		zc->max_exp_bit_length = CEX4C_MAX_MOD_SIZE;
	पूर्ण अन्यथा अगर (ap_test_bit(&ac->functions, AP_FUNC_EP11)) अणु
		अगर (ac->ap_dev.device_type == AP_DEVICE_TYPE_CEX4) अणु
			zc->type_string = "CEX4P";
			zc->user_space_type = ZCRYPT_CEX4;
			zc->speed_rating = CEX4P_SPEED_IDX;
		पूर्ण अन्यथा अगर (ac->ap_dev.device_type == AP_DEVICE_TYPE_CEX5) अणु
			zc->type_string = "CEX5P";
			zc->user_space_type = ZCRYPT_CEX5;
			zc->speed_rating = CEX5P_SPEED_IDX;
		पूर्ण अन्यथा अगर (ac->ap_dev.device_type == AP_DEVICE_TYPE_CEX6) अणु
			zc->type_string = "CEX6P";
			zc->user_space_type = ZCRYPT_CEX6;
			zc->speed_rating = CEX6P_SPEED_IDX;
		पूर्ण अन्यथा अणु
			zc->type_string = "CEX7P";
			/* wrong user space type, just क्रम compatibility
			 * with the ZCRYPT_STATUS_MASK ioctl.
			 */
			zc->user_space_type = ZCRYPT_CEX6;
			zc->speed_rating = CEX7P_SPEED_IDX;
		पूर्ण
		zc->min_mod_size = CEX4C_MIN_MOD_SIZE;
		zc->max_mod_size = CEX4C_MAX_MOD_SIZE;
		zc->max_exp_bit_length = CEX4C_MAX_MOD_SIZE;
	पूर्ण अन्यथा अणु
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
	पूर्ण अन्यथा अगर (ap_test_bit(&ac->functions, AP_FUNC_EP11)) अणु
		rc = sysfs_create_group(&ap_dev->device.kobj,
					&ep11_card_attr_grp);
		अगर (rc) अणु
			zcrypt_card_unरेजिस्टर(zc);
			ac->निजी = शून्य;
			zcrypt_card_मुक्त(zc);
		पूर्ण
	पूर्ण

	वापस rc;
पूर्ण

/**
 * This is called to हटाओ the CEX4/CEX5/CEX6/CEX7 card driver
 * inक्रमmation अगर an AP card device is हटाओd.
 */
अटल व्योम zcrypt_cex4_card_हटाओ(काष्ठा ap_device *ap_dev)
अणु
	काष्ठा ap_card *ac = to_ap_card(&ap_dev->device);
	काष्ठा zcrypt_card *zc = ac->निजी;

	अगर (ap_test_bit(&ac->functions, AP_FUNC_COPRO))
		sysfs_हटाओ_group(&ap_dev->device.kobj, &cca_card_attr_grp);
	अन्यथा अगर (ap_test_bit(&ac->functions, AP_FUNC_EP11))
		sysfs_हटाओ_group(&ap_dev->device.kobj, &ep11_card_attr_grp);
	अगर (zc)
		zcrypt_card_unरेजिस्टर(zc);
पूर्ण

अटल काष्ठा ap_driver zcrypt_cex4_card_driver = अणु
	.probe = zcrypt_cex4_card_probe,
	.हटाओ = zcrypt_cex4_card_हटाओ,
	.ids = zcrypt_cex4_card_ids,
	.flags = AP_DRIVER_FLAG_DEFAULT,
पूर्ण;

/**
 * Probe function क्रम CEX4/CEX5/CEX6/CEX7 queue device. It always
 * accepts the AP device since the bus_match alपढ़ोy checked
 * the hardware type.
 * @ap_dev: poपूर्णांकer to the AP device.
 */
अटल पूर्णांक zcrypt_cex4_queue_probe(काष्ठा ap_device *ap_dev)
अणु
	काष्ठा ap_queue *aq = to_ap_queue(&ap_dev->device);
	काष्ठा zcrypt_queue *zq;
	पूर्णांक rc;

	अगर (ap_test_bit(&aq->card->functions, AP_FUNC_ACCEL)) अणु
		zq = zcrypt_queue_alloc(CEX4A_MAX_MESSAGE_SIZE);
		अगर (!zq)
			वापस -ENOMEM;
		zq->ops = zcrypt_msgtype(MSGTYPE50_NAME,
					 MSGTYPE50_VARIANT_DEFAULT);
	पूर्ण अन्यथा अगर (ap_test_bit(&aq->card->functions, AP_FUNC_COPRO)) अणु
		zq = zcrypt_queue_alloc(CEX4C_MAX_MESSAGE_SIZE);
		अगर (!zq)
			वापस -ENOMEM;
		zq->ops = zcrypt_msgtype(MSGTYPE06_NAME,
					 MSGTYPE06_VARIANT_DEFAULT);
	पूर्ण अन्यथा अगर (ap_test_bit(&aq->card->functions, AP_FUNC_EP11)) अणु
		zq = zcrypt_queue_alloc(CEX4C_MAX_MESSAGE_SIZE);
		अगर (!zq)
			वापस -ENOMEM;
		zq->ops = zcrypt_msgtype(MSGTYPE06_NAME,
					 MSGTYPE06_VARIANT_EP11);
	पूर्ण अन्यथा अणु
		वापस -ENODEV;
	पूर्ण

	zq->queue = aq;
	zq->online = 1;
	atomic_set(&zq->load, 0);
	ap_queue_init_state(aq);
	ap_queue_init_reply(aq, &zq->reply);
	aq->request_समयout = CEX4_CLEANUP_TIME;
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
	पूर्ण अन्यथा अगर (ap_test_bit(&aq->card->functions, AP_FUNC_EP11)) अणु
		rc = sysfs_create_group(&ap_dev->device.kobj,
					&ep11_queue_attr_grp);
		अगर (rc) अणु
			zcrypt_queue_unरेजिस्टर(zq);
			aq->निजी = शून्य;
			zcrypt_queue_मुक्त(zq);
		पूर्ण
	पूर्ण

	वापस rc;
पूर्ण

/**
 * This is called to हटाओ the CEX4/CEX5/CEX6/CEX7 queue driver
 * inक्रमmation अगर an AP queue device is हटाओd.
 */
अटल व्योम zcrypt_cex4_queue_हटाओ(काष्ठा ap_device *ap_dev)
अणु
	काष्ठा ap_queue *aq = to_ap_queue(&ap_dev->device);
	काष्ठा zcrypt_queue *zq = aq->निजी;

	अगर (ap_test_bit(&aq->card->functions, AP_FUNC_COPRO))
		sysfs_हटाओ_group(&ap_dev->device.kobj, &cca_queue_attr_grp);
	अन्यथा अगर (ap_test_bit(&aq->card->functions, AP_FUNC_EP11))
		sysfs_हटाओ_group(&ap_dev->device.kobj, &ep11_queue_attr_grp);
	अगर (zq)
		zcrypt_queue_unरेजिस्टर(zq);
पूर्ण

अटल काष्ठा ap_driver zcrypt_cex4_queue_driver = अणु
	.probe = zcrypt_cex4_queue_probe,
	.हटाओ = zcrypt_cex4_queue_हटाओ,
	.ids = zcrypt_cex4_queue_ids,
	.flags = AP_DRIVER_FLAG_DEFAULT,
पूर्ण;

पूर्णांक __init zcrypt_cex4_init(व्योम)
अणु
	पूर्णांक rc;

	rc = ap_driver_रेजिस्टर(&zcrypt_cex4_card_driver,
				THIS_MODULE, "cex4card");
	अगर (rc)
		वापस rc;

	rc = ap_driver_रेजिस्टर(&zcrypt_cex4_queue_driver,
				THIS_MODULE, "cex4queue");
	अगर (rc)
		ap_driver_unरेजिस्टर(&zcrypt_cex4_card_driver);

	वापस rc;
पूर्ण

व्योम __निकास zcrypt_cex4_निकास(व्योम)
अणु
	ap_driver_unरेजिस्टर(&zcrypt_cex4_queue_driver);
	ap_driver_unरेजिस्टर(&zcrypt_cex4_card_driver);
पूर्ण

module_init(zcrypt_cex4_init);
module_निकास(zcrypt_cex4_निकास);
