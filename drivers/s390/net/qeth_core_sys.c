<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *    Copyright IBM Corp. 2007
 *    Author(s): Utz Bacher <utz.bacher@de.ibm.com>,
 *		 Frank Pavlic <fpavlic@de.ibm.com>,
 *		 Thomas Spatzier <tspat@de.ibm.com>,
 *		 Frank Blaschka <frank.blaschka@de.ibm.com>
 */

#घोषणा KMSG_COMPONENT "qeth"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/list.h>
#समावेश <linux/rwsem.h>
#समावेश <यंत्र/ebcdic.h>

#समावेश "qeth_core.h"

अटल sमाप_प्रकार qeth_dev_state_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा qeth_card *card = dev_get_drvdata(dev);

	चयन (card->state) अणु
	हाल CARD_STATE_DOWN:
		वापस प्र_लिखो(buf, "DOWN\n");
	हाल CARD_STATE_SOFTSETUP:
		अगर (card->dev->flags & IFF_UP)
			वापस प्र_लिखो(buf, "UP (LAN %s)\n",
				       netअगर_carrier_ok(card->dev) ? "ONLINE" :
								     "OFFLINE");
		वापस प्र_लिखो(buf, "SOFTSETUP\n");
	शेष:
		वापस प्र_लिखो(buf, "UNKNOWN\n");
	पूर्ण
पूर्ण

अटल DEVICE_ATTR(state, 0444, qeth_dev_state_show, शून्य);

अटल sमाप_प्रकार qeth_dev_chpid_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा qeth_card *card = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%02X\n", card->info.chpid);
पूर्ण

अटल DEVICE_ATTR(chpid, 0444, qeth_dev_chpid_show, शून्य);

अटल sमाप_प्रकार qeth_dev_अगर_name_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा qeth_card *card = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%s\n", netdev_name(card->dev));
पूर्ण

अटल DEVICE_ATTR(अगर_name, 0444, qeth_dev_अगर_name_show, शून्य);

अटल sमाप_प्रकार qeth_dev_card_type_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा qeth_card *card = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%s\n", qeth_get_cardname_लघु(card));
पूर्ण

अटल DEVICE_ATTR(card_type, 0444, qeth_dev_card_type_show, शून्य);

अटल स्थिर अक्षर *qeth_get_bufsize_str(काष्ठा qeth_card *card)
अणु
	अगर (card->qdio.in_buf_size == 16384)
		वापस "16k";
	अन्यथा अगर (card->qdio.in_buf_size == 24576)
		वापस "24k";
	अन्यथा अगर (card->qdio.in_buf_size == 32768)
		वापस "32k";
	अन्यथा अगर (card->qdio.in_buf_size == 40960)
		वापस "40k";
	अन्यथा
		वापस "64k";
पूर्ण

अटल sमाप_प्रकार qeth_dev_inbuf_size_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा qeth_card *card = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%s\n", qeth_get_bufsize_str(card));
पूर्ण

अटल DEVICE_ATTR(inbuf_size, 0444, qeth_dev_inbuf_size_show, शून्य);

अटल sमाप_प्रकार qeth_dev_portno_show(काष्ठा device *dev,
			काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा qeth_card *card = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%i\n", card->dev->dev_port);
पूर्ण

अटल sमाप_प्रकार qeth_dev_portno_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा qeth_card *card = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक portno, limit;
	पूर्णांक rc = 0;

	rc = kstrtouपूर्णांक(buf, 16, &portno);
	अगर (rc)
		वापस rc;
	अगर (portno > QETH_MAX_PORTNO)
		वापस -EINVAL;

	mutex_lock(&card->conf_mutex);
	अगर (card->state != CARD_STATE_DOWN) अणु
		rc = -EPERM;
		जाओ out;
	पूर्ण

	limit = (card->ssqd.pcnt ? card->ssqd.pcnt - 1 : card->ssqd.pcnt);
	अगर (portno > limit) अणु
		rc = -EINVAL;
		जाओ out;
	पूर्ण
	card->dev->dev_port = portno;
out:
	mutex_unlock(&card->conf_mutex);
	वापस rc ? rc : count;
पूर्ण

अटल DEVICE_ATTR(portno, 0644, qeth_dev_portno_show, qeth_dev_portno_store);

अटल sमाप_प्रकार qeth_dev_portname_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "no portname required\n");
पूर्ण

अटल sमाप_प्रकार qeth_dev_portname_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा qeth_card *card = dev_get_drvdata(dev);

	dev_warn_once(&card->gdev->dev,
		      "portname is deprecated and is ignored\n");
	वापस count;
पूर्ण

अटल DEVICE_ATTR(portname, 0644, qeth_dev_portname_show,
		qeth_dev_portname_store);

अटल sमाप_प्रकार qeth_dev_prioqing_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा qeth_card *card = dev_get_drvdata(dev);

	चयन (card->qdio.करो_prio_queueing) अणु
	हाल QETH_PRIO_Q_ING_PREC:
		वापस प्र_लिखो(buf, "%s\n", "by precedence");
	हाल QETH_PRIO_Q_ING_TOS:
		वापस प्र_लिखो(buf, "%s\n", "by type of service");
	हाल QETH_PRIO_Q_ING_SKB:
		वापस प्र_लिखो(buf, "%s\n", "by skb-priority");
	हाल QETH_PRIO_Q_ING_VLAN:
		वापस प्र_लिखो(buf, "%s\n", "by VLAN headers");
	हाल QETH_PRIO_Q_ING_FIXED:
		वापस प्र_लिखो(buf, "always queue %i\n",
			       card->qdio.शेष_out_queue);
	शेष:
		वापस प्र_लिखो(buf, "disabled\n");
	पूर्ण
पूर्ण

अटल sमाप_प्रकार qeth_dev_prioqing_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा qeth_card *card = dev_get_drvdata(dev);
	पूर्णांक rc = 0;

	अगर (IS_IQD(card) || IS_VM_NIC(card))
		वापस -EOPNOTSUPP;

	mutex_lock(&card->conf_mutex);
	अगर (card->state != CARD_STATE_DOWN) अणु
		rc = -EPERM;
		जाओ out;
	पूर्ण

	/* check अगर 1920 devices are supported ,
	 * अगर though we have to permit priority queueing
	 */
	अगर (card->qdio.no_out_queues == 1) अणु
		card->qdio.करो_prio_queueing = QETH_PRIOQ_DEFAULT;
		rc = -EPERM;
		जाओ out;
	पूर्ण

	अगर (sysfs_streq(buf, "prio_queueing_prec")) अणु
		card->qdio.करो_prio_queueing = QETH_PRIO_Q_ING_PREC;
		card->qdio.शेष_out_queue = QETH_DEFAULT_QUEUE;
	पूर्ण अन्यथा अगर (sysfs_streq(buf, "prio_queueing_skb")) अणु
		card->qdio.करो_prio_queueing = QETH_PRIO_Q_ING_SKB;
		card->qdio.शेष_out_queue = QETH_DEFAULT_QUEUE;
	पूर्ण अन्यथा अगर (sysfs_streq(buf, "prio_queueing_tos")) अणु
		card->qdio.करो_prio_queueing = QETH_PRIO_Q_ING_TOS;
		card->qdio.शेष_out_queue = QETH_DEFAULT_QUEUE;
	पूर्ण अन्यथा अगर (sysfs_streq(buf, "prio_queueing_vlan")) अणु
		अगर (IS_LAYER3(card)) अणु
			rc = -EOPNOTSUPP;
			जाओ out;
		पूर्ण
		card->qdio.करो_prio_queueing = QETH_PRIO_Q_ING_VLAN;
		card->qdio.शेष_out_queue = QETH_DEFAULT_QUEUE;
	पूर्ण अन्यथा अगर (sysfs_streq(buf, "no_prio_queueing:0")) अणु
		card->qdio.करो_prio_queueing = QETH_PRIO_Q_ING_FIXED;
		card->qdio.शेष_out_queue = 0;
	पूर्ण अन्यथा अगर (sysfs_streq(buf, "no_prio_queueing:1")) अणु
		card->qdio.करो_prio_queueing = QETH_PRIO_Q_ING_FIXED;
		card->qdio.शेष_out_queue = 1;
	पूर्ण अन्यथा अगर (sysfs_streq(buf, "no_prio_queueing:2")) अणु
		card->qdio.करो_prio_queueing = QETH_PRIO_Q_ING_FIXED;
		card->qdio.शेष_out_queue = 2;
	पूर्ण अन्यथा अगर (sysfs_streq(buf, "no_prio_queueing:3")) अणु
		card->qdio.करो_prio_queueing = QETH_PRIO_Q_ING_FIXED;
		card->qdio.शेष_out_queue = 3;
	पूर्ण अन्यथा अगर (sysfs_streq(buf, "no_prio_queueing")) अणु
		card->qdio.करो_prio_queueing = QETH_NO_PRIO_QUEUEING;
		card->qdio.शेष_out_queue = QETH_DEFAULT_QUEUE;
	पूर्ण अन्यथा
		rc = -EINVAL;
out:
	mutex_unlock(&card->conf_mutex);
	वापस rc ? rc : count;
पूर्ण

अटल DEVICE_ATTR(priority_queueing, 0644, qeth_dev_prioqing_show,
		qeth_dev_prioqing_store);

अटल sमाप_प्रकार qeth_dev_bufcnt_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा qeth_card *card = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%i\n", card->qdio.in_buf_pool.buf_count);
पूर्ण

अटल sमाप_प्रकार qeth_dev_bufcnt_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा qeth_card *card = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक cnt;
	पूर्णांक rc = 0;

	rc = kstrtouपूर्णांक(buf, 10, &cnt);
	अगर (rc)
		वापस rc;

	mutex_lock(&card->conf_mutex);
	अगर (card->state != CARD_STATE_DOWN) अणु
		rc = -EPERM;
		जाओ out;
	पूर्ण

	cnt = clamp(cnt, QETH_IN_BUF_COUNT_MIN, QETH_IN_BUF_COUNT_MAX);
	rc = qeth_resize_buffer_pool(card, cnt);

out:
	mutex_unlock(&card->conf_mutex);
	वापस rc ? rc : count;
पूर्ण

अटल DEVICE_ATTR(buffer_count, 0644, qeth_dev_bufcnt_show,
		qeth_dev_bufcnt_store);

अटल sमाप_प्रकार qeth_dev_recover_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा qeth_card *card = dev_get_drvdata(dev);
	bool reset;
	पूर्णांक rc;

	rc = kstrtobool(buf, &reset);
	अगर (rc)
		वापस rc;

	अगर (!qeth_card_hw_is_reachable(card))
		वापस -EPERM;

	अगर (reset)
		rc = qeth_schedule_recovery(card);

	वापस rc ? rc : count;
पूर्ण

अटल DEVICE_ATTR(recover, 0200, शून्य, qeth_dev_recover_store);

अटल sमाप_प्रकार qeth_dev_perक्रमmance_stats_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "1\n");
पूर्ण

अटल sमाप_प्रकार qeth_dev_perक्रमmance_stats_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा qeth_card *card = dev_get_drvdata(dev);
	काष्ठा qeth_qdio_out_q *queue;
	अचिन्हित पूर्णांक i;
	bool reset;
	पूर्णांक rc;

	rc = kstrtobool(buf, &reset);
	अगर (rc)
		वापस rc;

	अगर (reset) अणु
		स_रखो(&card->stats, 0, माप(card->stats));
		क्रम (i = 0; i < card->qdio.no_out_queues; i++) अणु
			queue = card->qdio.out_qs[i];
			अगर (!queue)
				अवरोध;
			स_रखो(&queue->stats, 0, माप(queue->stats));
		पूर्ण
	पूर्ण

	वापस count;
पूर्ण

अटल DEVICE_ATTR(perक्रमmance_stats, 0644, qeth_dev_perक्रमmance_stats_show,
		   qeth_dev_perक्रमmance_stats_store);

अटल sमाप_प्रकार qeth_dev_layer2_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा qeth_card *card = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%i\n", card->options.layer);
पूर्ण

अटल sमाप_प्रकार qeth_dev_layer2_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा qeth_card *card = dev_get_drvdata(dev);
	काष्ठा net_device *ndev;
	क्रमागत qeth_discipline_id newdis;
	अचिन्हित पूर्णांक input;
	पूर्णांक rc;

	rc = kstrtouपूर्णांक(buf, 16, &input);
	अगर (rc)
		वापस rc;

	चयन (input) अणु
	हाल 0:
		newdis = QETH_DISCIPLINE_LAYER3;
		अवरोध;
	हाल 1:
		newdis = QETH_DISCIPLINE_LAYER2;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&card->discipline_mutex);
	अगर (card->state != CARD_STATE_DOWN) अणु
		rc = -EPERM;
		जाओ out;
	पूर्ण

	अगर (card->options.layer == newdis)
		जाओ out;
	अगर (card->info.layer_enक्रमced) अणु
		/* fixed layer, can't चयन */
		rc = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	अगर (card->discipline) अणु
		/* start with a new, pristine netdevice: */
		ndev = qeth_clone_netdev(card->dev);
		अगर (!ndev) अणु
			rc = -ENOMEM;
			जाओ out;
		पूर्ण

		qeth_हटाओ_discipline(card);
		मुक्त_netdev(card->dev);
		card->dev = ndev;
	पूर्ण

	rc = qeth_setup_discipline(card, newdis);

out:
	mutex_unlock(&card->discipline_mutex);
	वापस rc ? rc : count;
पूर्ण

अटल DEVICE_ATTR(layer2, 0644, qeth_dev_layer2_show,
		   qeth_dev_layer2_store);

#घोषणा ATTR_QETH_ISOLATION_NONE	("none")
#घोषणा ATTR_QETH_ISOLATION_FWD		("forward")
#घोषणा ATTR_QETH_ISOLATION_DROP	("drop")

अटल sमाप_प्रकार qeth_dev_isolation_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा qeth_card *card = dev_get_drvdata(dev);

	चयन (card->options.isolation) अणु
	हाल ISOLATION_MODE_NONE:
		वापस snम_लिखो(buf, 6, "%s\n", ATTR_QETH_ISOLATION_NONE);
	हाल ISOLATION_MODE_FWD:
		वापस snम_लिखो(buf, 9, "%s\n", ATTR_QETH_ISOLATION_FWD);
	हाल ISOLATION_MODE_DROP:
		वापस snम_लिखो(buf, 6, "%s\n", ATTR_QETH_ISOLATION_DROP);
	शेष:
		वापस snम_लिखो(buf, 5, "%s\n", "N/A");
	पूर्ण
पूर्ण

अटल sमाप_प्रकार qeth_dev_isolation_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा qeth_card *card = dev_get_drvdata(dev);
	क्रमागत qeth_ipa_isolation_modes isolation;
	पूर्णांक rc = 0;

	mutex_lock(&card->conf_mutex);
	अगर (!IS_OSD(card) && !IS_OSX(card)) अणु
		rc = -EOPNOTSUPP;
		dev_err(&card->gdev->dev, "Adapter does not "
			"support QDIO data connection isolation\n");
		जाओ out;
	पूर्ण

	/* parse input पूर्णांकo isolation mode */
	अगर (sysfs_streq(buf, ATTR_QETH_ISOLATION_NONE)) अणु
		isolation = ISOLATION_MODE_NONE;
	पूर्ण अन्यथा अगर (sysfs_streq(buf, ATTR_QETH_ISOLATION_FWD)) अणु
		isolation = ISOLATION_MODE_FWD;
	पूर्ण अन्यथा अगर (sysfs_streq(buf, ATTR_QETH_ISOLATION_DROP)) अणु
		isolation = ISOLATION_MODE_DROP;
	पूर्ण अन्यथा अणु
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (qeth_card_hw_is_reachable(card))
		rc = qeth_setadpparms_set_access_ctrl(card, isolation);

	अगर (!rc)
		WRITE_ONCE(card->options.isolation, isolation);

out:
	mutex_unlock(&card->conf_mutex);

	वापस rc ? rc : count;
पूर्ण

अटल DEVICE_ATTR(isolation, 0644, qeth_dev_isolation_show,
			qeth_dev_isolation_store);

अटल sमाप_प्रकार qeth_dev_चयन_attrs_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा qeth_card *card = dev_get_drvdata(dev);
	काष्ठा qeth_चयन_info sw_info;
	पूर्णांक	rc = 0;

	अगर (!qeth_card_hw_is_reachable(card))
		वापस प्र_लिखो(buf, "n/a\n");

	rc = qeth_query_चयन_attributes(card, &sw_info);
	अगर (rc)
		वापस rc;

	अगर (!sw_info.capabilities)
		rc = प्र_लिखो(buf, "unknown");

	अगर (sw_info.capabilities & QETH_SWITCH_FORW_802_1)
		rc = प्र_लिखो(buf, (sw_info.settings & QETH_SWITCH_FORW_802_1 ?
							"[802.1]" : "802.1"));
	अगर (sw_info.capabilities & QETH_SWITCH_FORW_REFL_RELAY)
		rc += प्र_लिखो(buf + rc,
			(sw_info.settings & QETH_SWITCH_FORW_REFL_RELAY ?
							" [rr]" : " rr"));
	rc += प्र_लिखो(buf + rc, "\n");

	वापस rc;
पूर्ण

अटल DEVICE_ATTR(चयन_attrs, 0444,
		   qeth_dev_चयन_attrs_show, शून्य);

अटल sमाप_प्रकार qeth_hw_trap_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा qeth_card *card = dev_get_drvdata(dev);

	अगर (card->info.hwtrap)
		वापस snम_लिखो(buf, 5, "arm\n");
	अन्यथा
		वापस snम_लिखो(buf, 8, "disarm\n");
पूर्ण

अटल sमाप_प्रकार qeth_hw_trap_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा qeth_card *card = dev_get_drvdata(dev);
	पूर्णांक rc = 0;
	पूर्णांक state = 0;

	mutex_lock(&card->conf_mutex);
	अगर (qeth_card_hw_is_reachable(card))
		state = 1;

	अगर (sysfs_streq(buf, "arm") && !card->info.hwtrap) अणु
		अगर (state) अणु
			अगर (qeth_is_diagass_supported(card,
			    QETH_DIAGS_CMD_TRAP)) अणु
				rc = qeth_hw_trap(card, QETH_DIAGS_TRAP_ARM);
				अगर (!rc)
					card->info.hwtrap = 1;
			पूर्ण अन्यथा
				rc = -EINVAL;
		पूर्ण अन्यथा
			card->info.hwtrap = 1;
	पूर्ण अन्यथा अगर (sysfs_streq(buf, "disarm") && card->info.hwtrap) अणु
		अगर (state) अणु
			rc = qeth_hw_trap(card, QETH_DIAGS_TRAP_DISARM);
			अगर (!rc)
				card->info.hwtrap = 0;
		पूर्ण अन्यथा
			card->info.hwtrap = 0;
	पूर्ण अन्यथा अगर (sysfs_streq(buf, "trap") && state && card->info.hwtrap)
		rc = qeth_hw_trap(card, QETH_DIAGS_TRAP_CAPTURE);
	अन्यथा
		rc = -EINVAL;

	mutex_unlock(&card->conf_mutex);
	वापस rc ? rc : count;
पूर्ण

अटल DEVICE_ATTR(hw_trap, 0644, qeth_hw_trap_show,
		   qeth_hw_trap_store);

अटल sमाप_प्रकार qeth_dev_blkt_store(काष्ठा qeth_card *card,
		स्थिर अक्षर *buf, माप_प्रकार count, पूर्णांक *value, पूर्णांक max_value)
अणु
	अचिन्हित पूर्णांक input;
	पूर्णांक rc;

	rc = kstrtouपूर्णांक(buf, 10, &input);
	अगर (rc)
		वापस rc;

	अगर (input > max_value)
		वापस -EINVAL;

	mutex_lock(&card->conf_mutex);
	अगर (card->state != CARD_STATE_DOWN)
		rc = -EPERM;
	अन्यथा
		*value = input;
	mutex_unlock(&card->conf_mutex);
	वापस rc ? rc : count;
पूर्ण

अटल sमाप_प्रकार qeth_dev_blkt_total_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा qeth_card *card = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%i\n", card->info.blkt.समय_प्रकारotal);
पूर्ण

अटल sमाप_प्रकार qeth_dev_blkt_total_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा qeth_card *card = dev_get_drvdata(dev);

	वापस qeth_dev_blkt_store(card, buf, count,
				   &card->info.blkt.समय_प्रकारotal, 5000);
पूर्ण

अटल DEVICE_ATTR(total, 0644, qeth_dev_blkt_total_show,
		   qeth_dev_blkt_total_store);

अटल sमाप_प्रकार qeth_dev_blkt_पूर्णांकer_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा qeth_card *card = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%i\n", card->info.blkt.पूर्णांकer_packet);
पूर्ण

अटल sमाप_प्रकार qeth_dev_blkt_पूर्णांकer_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा qeth_card *card = dev_get_drvdata(dev);

	वापस qeth_dev_blkt_store(card, buf, count,
				   &card->info.blkt.पूर्णांकer_packet, 1000);
पूर्ण

अटल DEVICE_ATTR(पूर्णांकer, 0644, qeth_dev_blkt_पूर्णांकer_show,
		   qeth_dev_blkt_पूर्णांकer_store);

अटल sमाप_प्रकार qeth_dev_blkt_पूर्णांकer_jumbo_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा qeth_card *card = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%i\n", card->info.blkt.पूर्णांकer_packet_jumbo);
पूर्ण

अटल sमाप_प्रकार qeth_dev_blkt_पूर्णांकer_jumbo_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा qeth_card *card = dev_get_drvdata(dev);

	वापस qeth_dev_blkt_store(card, buf, count,
				   &card->info.blkt.पूर्णांकer_packet_jumbo, 1000);
पूर्ण

अटल DEVICE_ATTR(पूर्णांकer_jumbo, 0644, qeth_dev_blkt_पूर्णांकer_jumbo_show,
		   qeth_dev_blkt_पूर्णांकer_jumbo_store);

अटल काष्ठा attribute *qeth_blkt_device_attrs[] = अणु
	&dev_attr_total.attr,
	&dev_attr_पूर्णांकer.attr,
	&dev_attr_पूर्णांकer_jumbo.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group qeth_dev_blkt_group = अणु
	.name = "blkt",
	.attrs = qeth_blkt_device_attrs,
पूर्ण;

अटल काष्ठा attribute *qeth_dev_extended_attrs[] = अणु
	&dev_attr_inbuf_size.attr,
	&dev_attr_portno.attr,
	&dev_attr_portname.attr,
	&dev_attr_priority_queueing.attr,
	&dev_attr_perक्रमmance_stats.attr,
	&dev_attr_layer2.attr,
	&dev_attr_isolation.attr,
	&dev_attr_hw_trap.attr,
	&dev_attr_चयन_attrs.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group qeth_dev_extended_group = अणु
	.attrs = qeth_dev_extended_attrs,
पूर्ण;

अटल काष्ठा attribute *qeth_dev_attrs[] = अणु
	&dev_attr_state.attr,
	&dev_attr_chpid.attr,
	&dev_attr_अगर_name.attr,
	&dev_attr_card_type.attr,
	&dev_attr_buffer_count.attr,
	&dev_attr_recover.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group qeth_dev_group = अणु
	.attrs = qeth_dev_attrs,
पूर्ण;

स्थिर काष्ठा attribute_group *qeth_osn_dev_groups[] = अणु
	&qeth_dev_group,
	शून्य,
पूर्ण;

स्थिर काष्ठा attribute_group *qeth_dev_groups[] = अणु
	&qeth_dev_group,
	&qeth_dev_extended_group,
	&qeth_dev_blkt_group,
	शून्य,
पूर्ण;
