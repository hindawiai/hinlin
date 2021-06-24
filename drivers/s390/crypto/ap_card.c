<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright IBM Corp. 2016
 * Author(s): Martin Schwidefsky <schwidefsky@de.ibm.com>
 *
 * Adjunct processor bus, card related code.
 */

#घोषणा KMSG_COMPONENT "ap"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/facility.h>
#समावेश <यंत्र/sclp.h>

#समावेश "ap_bus.h"

/*
 * AP card related attributes.
 */
अटल sमाप_प्रकार hwtype_show(काष्ठा device *dev,
			   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ap_card *ac = to_ap_card(dev);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", ac->ap_dev.device_type);
पूर्ण

अटल DEVICE_ATTR_RO(hwtype);

अटल sमाप_प्रकार raw_hwtype_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ap_card *ac = to_ap_card(dev);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", ac->raw_hwtype);
पूर्ण

अटल DEVICE_ATTR_RO(raw_hwtype);

अटल sमाप_प्रकार depth_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	काष्ठा ap_card *ac = to_ap_card(dev);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", ac->queue_depth);
पूर्ण

अटल DEVICE_ATTR_RO(depth);

अटल sमाप_प्रकार ap_functions_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ap_card *ac = to_ap_card(dev);

	वापस scnम_लिखो(buf, PAGE_SIZE, "0x%08X\n", ac->functions);
पूर्ण

अटल DEVICE_ATTR_RO(ap_functions);

अटल sमाप_प्रकार request_count_show(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  अक्षर *buf)
अणु
	काष्ठा ap_card *ac = to_ap_card(dev);
	u64 req_cnt;

	req_cnt = 0;
	spin_lock_bh(&ap_queues_lock);
	req_cnt = atomic64_पढ़ो(&ac->total_request_count);
	spin_unlock_bh(&ap_queues_lock);
	वापस scnम_लिखो(buf, PAGE_SIZE, "%llu\n", req_cnt);
पूर्ण

अटल sमाप_प्रकार request_count_store(काष्ठा device *dev,
				   काष्ठा device_attribute *attr,
				   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक bkt;
	काष्ठा ap_queue *aq;
	काष्ठा ap_card *ac = to_ap_card(dev);

	spin_lock_bh(&ap_queues_lock);
	hash_क्रम_each(ap_queues, bkt, aq, hnode)
		अगर (ac == aq->card)
			aq->total_request_count = 0;
	spin_unlock_bh(&ap_queues_lock);
	atomic64_set(&ac->total_request_count, 0);

	वापस count;
पूर्ण

अटल DEVICE_ATTR_RW(request_count);

अटल sमाप_प्रकार requestq_count_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक bkt;
	काष्ठा ap_queue *aq;
	अचिन्हित पूर्णांक reqq_cnt;
	काष्ठा ap_card *ac = to_ap_card(dev);

	reqq_cnt = 0;
	spin_lock_bh(&ap_queues_lock);
	hash_क्रम_each(ap_queues, bkt, aq, hnode)
		अगर (ac == aq->card)
			reqq_cnt += aq->requestq_count;
	spin_unlock_bh(&ap_queues_lock);
	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", reqq_cnt);
पूर्ण

अटल DEVICE_ATTR_RO(requestq_count);

अटल sमाप_प्रकार pendingq_count_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक bkt;
	काष्ठा ap_queue *aq;
	अचिन्हित पूर्णांक penq_cnt;
	काष्ठा ap_card *ac = to_ap_card(dev);

	penq_cnt = 0;
	spin_lock_bh(&ap_queues_lock);
	hash_क्रम_each(ap_queues, bkt, aq, hnode)
		अगर (ac == aq->card)
			penq_cnt += aq->pendingq_count;
	spin_unlock_bh(&ap_queues_lock);
	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", penq_cnt);
पूर्ण

अटल DEVICE_ATTR_RO(pendingq_count);

अटल sमाप_प्रकार modalias_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस scnम_लिखो(buf, PAGE_SIZE, "ap:t%02X\n",
			 to_ap_dev(dev)->device_type);
पूर्ण

अटल DEVICE_ATTR_RO(modalias);

अटल sमाप_प्रकार config_show(काष्ठा device *dev,
			   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ap_card *ac = to_ap_card(dev);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", ac->config ? 1 : 0);
पूर्ण

अटल sमाप_प्रकार config_store(काष्ठा device *dev,
			    काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक rc = 0, cfg;
	काष्ठा ap_card *ac = to_ap_card(dev);

	अगर (माला_पूछो(buf, "%d\n", &cfg) != 1 || cfg < 0 || cfg > 1)
		वापस -EINVAL;

	अगर (cfg && !ac->config)
		rc = sclp_ap_configure(ac->id);
	अन्यथा अगर (!cfg && ac->config)
		rc = sclp_ap_deconfigure(ac->id);
	अगर (rc)
		वापस rc;

	ac->config = cfg ? true : false;

	वापस count;
पूर्ण

अटल DEVICE_ATTR_RW(config);

अटल काष्ठा attribute *ap_card_dev_attrs[] = अणु
	&dev_attr_hwtype.attr,
	&dev_attr_raw_hwtype.attr,
	&dev_attr_depth.attr,
	&dev_attr_ap_functions.attr,
	&dev_attr_request_count.attr,
	&dev_attr_requestq_count.attr,
	&dev_attr_pendingq_count.attr,
	&dev_attr_modalias.attr,
	&dev_attr_config.attr,
	शून्य
पूर्ण;

अटल काष्ठा attribute_group ap_card_dev_attr_group = अणु
	.attrs = ap_card_dev_attrs
पूर्ण;

अटल स्थिर काष्ठा attribute_group *ap_card_dev_attr_groups[] = अणु
	&ap_card_dev_attr_group,
	शून्य
पूर्ण;

अटल काष्ठा device_type ap_card_type = अणु
	.name = "ap_card",
	.groups = ap_card_dev_attr_groups,
पूर्ण;

अटल व्योम ap_card_device_release(काष्ठा device *dev)
अणु
	काष्ठा ap_card *ac = to_ap_card(dev);

	kमुक्त(ac);
पूर्ण

काष्ठा ap_card *ap_card_create(पूर्णांक id, पूर्णांक queue_depth, पूर्णांक raw_type,
			       पूर्णांक comp_type, अचिन्हित पूर्णांक functions)
अणु
	काष्ठा ap_card *ac;

	ac = kzalloc(माप(*ac), GFP_KERNEL);
	अगर (!ac)
		वापस शून्य;
	ac->ap_dev.device.release = ap_card_device_release;
	ac->ap_dev.device.type = &ap_card_type;
	ac->ap_dev.device_type = comp_type;
	ac->raw_hwtype = raw_type;
	ac->queue_depth = queue_depth;
	ac->functions = functions;
	ac->id = id;
	वापस ac;
पूर्ण
