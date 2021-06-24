<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * PTP 1588 घड़ी support - sysfs पूर्णांकerface.
 *
 * Copyright (C) 2010 OMICRON electronics GmbH
 */
#समावेश <linux/capability.h>
#समावेश <linux/slab.h>

#समावेश "ptp_private.h"

अटल sमाप_प्रकार घड़ी_name_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *page)
अणु
	काष्ठा ptp_घड़ी *ptp = dev_get_drvdata(dev);
	वापस snम_लिखो(page, PAGE_SIZE-1, "%s\n", ptp->info->name);
पूर्ण
अटल DEVICE_ATTR_RO(घड़ी_name);

#घोषणा PTP_SHOW_INT(name, var)						\
अटल sमाप_प्रकार var##_show(काष्ठा device *dev,				\
			   काष्ठा device_attribute *attr, अक्षर *page)	\
अणु									\
	काष्ठा ptp_घड़ी *ptp = dev_get_drvdata(dev);			\
	वापस snम_लिखो(page, PAGE_SIZE-1, "%d\n", ptp->info->var);	\
पूर्ण									\
अटल DEVICE_ATTR(name, 0444, var##_show, शून्य);

PTP_SHOW_INT(max_adjusपंचांगent, max_adj);
PTP_SHOW_INT(n_alarms, n_alarm);
PTP_SHOW_INT(n_बाह्यal_बारtamps, n_ext_ts);
PTP_SHOW_INT(n_periodic_outमाला_दो, n_per_out);
PTP_SHOW_INT(n_programmable_pins, n_pins);
PTP_SHOW_INT(pps_available, pps);

अटल sमाप_प्रकार extts_enable_store(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा ptp_घड़ी *ptp = dev_get_drvdata(dev);
	काष्ठा ptp_घड़ी_info *ops = ptp->info;
	काष्ठा ptp_घड़ी_request req = अणु .type = PTP_CLK_REQ_EXTTS पूर्ण;
	पूर्णांक cnt, enable;
	पूर्णांक err = -EINVAL;

	cnt = माला_पूछो(buf, "%u %d", &req.extts.index, &enable);
	अगर (cnt != 2)
		जाओ out;
	अगर (req.extts.index >= ops->n_ext_ts)
		जाओ out;

	err = ops->enable(ops, &req, enable ? 1 : 0);
	अगर (err)
		जाओ out;

	वापस count;
out:
	वापस err;
पूर्ण
अटल DEVICE_ATTR(extts_enable, 0220, शून्य, extts_enable_store);

अटल sमाप_प्रकार extts_fअगरo_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *page)
अणु
	काष्ठा ptp_घड़ी *ptp = dev_get_drvdata(dev);
	काष्ठा बारtamp_event_queue *queue = &ptp->tsevq;
	काष्ठा ptp_extts_event event;
	अचिन्हित दीर्घ flags;
	माप_प्रकार qcnt;
	पूर्णांक cnt = 0;

	स_रखो(&event, 0, माप(event));

	अगर (mutex_lock_पूर्णांकerruptible(&ptp->tsevq_mux))
		वापस -ERESTARTSYS;

	spin_lock_irqsave(&queue->lock, flags);
	qcnt = queue_cnt(queue);
	अगर (qcnt) अणु
		event = queue->buf[queue->head];
		queue->head = (queue->head + 1) % PTP_MAX_TIMESTAMPS;
	पूर्ण
	spin_unlock_irqrestore(&queue->lock, flags);

	अगर (!qcnt)
		जाओ out;

	cnt = snम_लिखो(page, PAGE_SIZE, "%u %lld %u\n",
		       event.index, event.t.sec, event.t.nsec);
out:
	mutex_unlock(&ptp->tsevq_mux);
	वापस cnt;
पूर्ण
अटल DEVICE_ATTR(fअगरo, 0444, extts_fअगरo_show, शून्य);

अटल sमाप_प्रकार period_store(काष्ठा device *dev,
			    काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा ptp_घड़ी *ptp = dev_get_drvdata(dev);
	काष्ठा ptp_घड़ी_info *ops = ptp->info;
	काष्ठा ptp_घड़ी_request req = अणु .type = PTP_CLK_REQ_PEROUT पूर्ण;
	पूर्णांक cnt, enable, err = -EINVAL;

	cnt = माला_पूछो(buf, "%u %lld %u %lld %u", &req.perout.index,
		     &req.perout.start.sec, &req.perout.start.nsec,
		     &req.perout.period.sec, &req.perout.period.nsec);
	अगर (cnt != 5)
		जाओ out;
	अगर (req.perout.index >= ops->n_per_out)
		जाओ out;

	enable = req.perout.period.sec || req.perout.period.nsec;
	err = ops->enable(ops, &req, enable);
	अगर (err)
		जाओ out;

	वापस count;
out:
	वापस err;
पूर्ण
अटल DEVICE_ATTR(period, 0220, शून्य, period_store);

अटल sमाप_प्रकार pps_enable_store(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा ptp_घड़ी *ptp = dev_get_drvdata(dev);
	काष्ठा ptp_घड़ी_info *ops = ptp->info;
	काष्ठा ptp_घड़ी_request req = अणु .type = PTP_CLK_REQ_PPS पूर्ण;
	पूर्णांक cnt, enable;
	पूर्णांक err = -EINVAL;

	अगर (!capable(CAP_SYS_TIME))
		वापस -EPERM;

	cnt = माला_पूछो(buf, "%d", &enable);
	अगर (cnt != 1)
		जाओ out;

	err = ops->enable(ops, &req, enable ? 1 : 0);
	अगर (err)
		जाओ out;

	वापस count;
out:
	वापस err;
पूर्ण
अटल DEVICE_ATTR(pps_enable, 0220, शून्य, pps_enable_store);

अटल काष्ठा attribute *ptp_attrs[] = अणु
	&dev_attr_घड़ी_name.attr,

	&dev_attr_max_adjusपंचांगent.attr,
	&dev_attr_n_alarms.attr,
	&dev_attr_n_बाह्यal_बारtamps.attr,
	&dev_attr_n_periodic_outमाला_दो.attr,
	&dev_attr_n_programmable_pins.attr,
	&dev_attr_pps_available.attr,

	&dev_attr_extts_enable.attr,
	&dev_attr_fअगरo.attr,
	&dev_attr_period.attr,
	&dev_attr_pps_enable.attr,
	शून्य
पूर्ण;

अटल umode_t ptp_is_attribute_visible(काष्ठा kobject *kobj,
					काष्ठा attribute *attr, पूर्णांक n)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा ptp_घड़ी *ptp = dev_get_drvdata(dev);
	काष्ठा ptp_घड़ी_info *info = ptp->info;
	umode_t mode = attr->mode;

	अगर (attr == &dev_attr_extts_enable.attr ||
	    attr == &dev_attr_fअगरo.attr) अणु
		अगर (!info->n_ext_ts)
			mode = 0;
	पूर्ण अन्यथा अगर (attr == &dev_attr_period.attr) अणु
		अगर (!info->n_per_out)
			mode = 0;
	पूर्ण अन्यथा अगर (attr == &dev_attr_pps_enable.attr) अणु
		अगर (!info->pps)
			mode = 0;
	पूर्ण

	वापस mode;
पूर्ण

अटल स्थिर काष्ठा attribute_group ptp_group = अणु
	.is_visible	= ptp_is_attribute_visible,
	.attrs		= ptp_attrs,
पूर्ण;

स्थिर काष्ठा attribute_group *ptp_groups[] = अणु
	&ptp_group,
	शून्य
पूर्ण;

अटल पूर्णांक ptp_pin_name2index(काष्ठा ptp_घड़ी *ptp, स्थिर अक्षर *name)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < ptp->info->n_pins; i++) अणु
		अगर (!म_भेद(ptp->info->pin_config[i].name, name))
			वापस i;
	पूर्ण
	वापस -1;
पूर्ण

अटल sमाप_प्रकार ptp_pin_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    अक्षर *page)
अणु
	काष्ठा ptp_घड़ी *ptp = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक func, chan;
	पूर्णांक index;

	index = ptp_pin_name2index(ptp, attr->attr.name);
	अगर (index < 0)
		वापस -EINVAL;

	अगर (mutex_lock_पूर्णांकerruptible(&ptp->pincfg_mux))
		वापस -ERESTARTSYS;

	func = ptp->info->pin_config[index].func;
	chan = ptp->info->pin_config[index].chan;

	mutex_unlock(&ptp->pincfg_mux);

	वापस snम_लिखो(page, PAGE_SIZE, "%u %u\n", func, chan);
पूर्ण

अटल sमाप_प्रकार ptp_pin_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा ptp_घड़ी *ptp = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक func, chan;
	पूर्णांक cnt, err, index;

	cnt = माला_पूछो(buf, "%u %u", &func, &chan);
	अगर (cnt != 2)
		वापस -EINVAL;

	index = ptp_pin_name2index(ptp, attr->attr.name);
	अगर (index < 0)
		वापस -EINVAL;

	अगर (mutex_lock_पूर्णांकerruptible(&ptp->pincfg_mux))
		वापस -ERESTARTSYS;
	err = ptp_set_pinfunc(ptp, index, func, chan);
	mutex_unlock(&ptp->pincfg_mux);
	अगर (err)
		वापस err;

	वापस count;
पूर्ण

पूर्णांक ptp_populate_pin_groups(काष्ठा ptp_घड़ी *ptp)
अणु
	काष्ठा ptp_घड़ी_info *info = ptp->info;
	पूर्णांक err = -ENOMEM, i, n_pins = info->n_pins;

	अगर (!n_pins)
		वापस 0;

	ptp->pin_dev_attr = kसुस्मृति(n_pins, माप(*ptp->pin_dev_attr),
				    GFP_KERNEL);
	अगर (!ptp->pin_dev_attr)
		जाओ no_dev_attr;

	ptp->pin_attr = kसुस्मृति(1 + n_pins, माप(*ptp->pin_attr), GFP_KERNEL);
	अगर (!ptp->pin_attr)
		जाओ no_pin_attr;

	क्रम (i = 0; i < n_pins; i++) अणु
		काष्ठा device_attribute *da = &ptp->pin_dev_attr[i];
		sysfs_attr_init(&da->attr);
		da->attr.name = info->pin_config[i].name;
		da->attr.mode = 0644;
		da->show = ptp_pin_show;
		da->store = ptp_pin_store;
		ptp->pin_attr[i] = &da->attr;
	पूर्ण

	ptp->pin_attr_group.name = "pins";
	ptp->pin_attr_group.attrs = ptp->pin_attr;

	ptp->pin_attr_groups[0] = &ptp->pin_attr_group;

	वापस 0;

no_pin_attr:
	kमुक्त(ptp->pin_dev_attr);
no_dev_attr:
	वापस err;
पूर्ण

व्योम ptp_cleanup_pin_groups(काष्ठा ptp_घड़ी *ptp)
अणु
	kमुक्त(ptp->pin_attr);
	kमुक्त(ptp->pin_dev_attr);
पूर्ण
