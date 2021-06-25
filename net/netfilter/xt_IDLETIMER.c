<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/net/netfilter/xt_IDLETIMER.c
 *
 * Netfilter module to trigger a समयr when packet matches.
 * After समयr expires a kevent will be sent.
 *
 * Copyright (C) 2004, 2010 Nokia Corporation
 * Written by Timo Teras <ext-timo.teras@nokia.com>
 *
 * Converted to x_tables and reworked क्रम upstream inclusion
 * by Luciano Coelho <luciano.coelho@nokia.com>
 *
 * Contact: Luciano Coelho <luciano.coelho@nokia.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/समयr.h>
#समावेश <linux/alarmसमयr.h>
#समावेश <linux/list.h>
#समावेश <linux/mutex.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter/x_tables.h>
#समावेश <linux/netfilter/xt_IDLETIMER.h>
#समावेश <linux/kdev_t.h>
#समावेश <linux/kobject.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/sysfs.h>

काष्ठा idleसमयr_tg अणु
	काष्ठा list_head entry;
	काष्ठा alarm alarm;
	काष्ठा समयr_list समयr;
	काष्ठा work_काष्ठा work;

	काष्ठा kobject *kobj;
	काष्ठा device_attribute attr;

	अचिन्हित पूर्णांक refcnt;
	u8 समयr_type;
पूर्ण;

अटल LIST_HEAD(idleसमयr_tg_list);
अटल DEFINE_MUTEX(list_mutex);

अटल काष्ठा kobject *idleसमयr_tg_kobj;

अटल
काष्ठा idleसमयr_tg *__idleसमयr_tg_find_by_label(स्थिर अक्षर *label)
अणु
	काष्ठा idleसमयr_tg *entry;

	list_क्रम_each_entry(entry, &idleसमयr_tg_list, entry) अणु
		अगर (!म_भेद(label, entry->attr.attr.name))
			वापस entry;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल sमाप_प्रकार idleसमयr_tg_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा idleसमयr_tg *समयr;
	अचिन्हित दीर्घ expires = 0;
	काष्ठा बारpec64 kबारpec = अणुपूर्ण;
	दीर्घ समय_dअगरf = 0;

	mutex_lock(&list_mutex);

	समयr =	__idleसमयr_tg_find_by_label(attr->attr.name);
	अगर (समयr) अणु
		अगर (समयr->समयr_type & XT_IDLETIMER_ALARM) अणु
			kसमय_प्रकार expires_alarm = alarm_expires_reमुख्यing(&समयr->alarm);
			kबारpec = kसमय_प्रकारo_बारpec64(expires_alarm);
			समय_dअगरf = kबारpec.tv_sec;
		पूर्ण अन्यथा अणु
			expires = समयr->समयr.expires;
			समय_dअगरf = jअगरfies_to_msecs(expires - jअगरfies) / 1000;
		पूर्ण
	पूर्ण

	mutex_unlock(&list_mutex);

	अगर (समय_after(expires, jअगरfies) || kबारpec.tv_sec > 0)
		वापस snम_लिखो(buf, PAGE_SIZE, "%ld\n", समय_dअगरf);

	वापस snम_लिखो(buf, PAGE_SIZE, "0\n");
पूर्ण

अटल व्योम idleसमयr_tg_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा idleसमयr_tg *समयr = container_of(work, काष्ठा idleसमयr_tg,
						  work);

	sysfs_notअगरy(idleसमयr_tg_kobj, शून्य, समयr->attr.attr.name);
पूर्ण

अटल व्योम idleसमयr_tg_expired(काष्ठा समयr_list *t)
अणु
	काष्ठा idleसमयr_tg *समयr = from_समयr(समयr, t, समयr);

	pr_debug("timer %s expired\n", समयr->attr.attr.name);

	schedule_work(&समयr->work);
पूर्ण

अटल क्रमागत alarmसमयr_restart idleसमयr_tg_alarmproc(काष्ठा alarm *alarm,
							  kसमय_प्रकार now)
अणु
	काष्ठा idleसमयr_tg *समयr = alarm->data;

	pr_debug("alarm %s expired\n", समयr->attr.attr.name);
	schedule_work(&समयr->work);
	वापस ALARMTIMER_NORESTART;
पूर्ण

अटल पूर्णांक idleसमयr_check_sysfs_name(स्थिर अक्षर *name, अचिन्हित पूर्णांक size)
अणु
	पूर्णांक ret;

	ret = xt_check_proc_name(name, size);
	अगर (ret < 0)
		वापस ret;

	अगर (!म_भेद(name, "power") ||
	    !म_भेद(name, "subsystem") ||
	    !म_भेद(name, "uevent"))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक idleसमयr_tg_create(काष्ठा idleसमयr_tg_info *info)
अणु
	पूर्णांक ret;

	info->समयr = kदो_स्मृति(माप(*info->समयr), GFP_KERNEL);
	अगर (!info->समयr) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	ret = idleसमयr_check_sysfs_name(info->label, माप(info->label));
	अगर (ret < 0)
		जाओ out_मुक्त_समयr;

	sysfs_attr_init(&info->समयr->attr.attr);
	info->समयr->attr.attr.name = kstrdup(info->label, GFP_KERNEL);
	अगर (!info->समयr->attr.attr.name) अणु
		ret = -ENOMEM;
		जाओ out_मुक्त_समयr;
	पूर्ण
	info->समयr->attr.attr.mode = 0444;
	info->समयr->attr.show = idleसमयr_tg_show;

	ret = sysfs_create_file(idleसमयr_tg_kobj, &info->समयr->attr.attr);
	अगर (ret < 0) अणु
		pr_debug("couldn't add file to sysfs");
		जाओ out_मुक्त_attr;
	पूर्ण

	list_add(&info->समयr->entry, &idleसमयr_tg_list);

	समयr_setup(&info->समयr->समयr, idleसमयr_tg_expired, 0);
	info->समयr->refcnt = 1;

	INIT_WORK(&info->समयr->work, idleसमयr_tg_work);

	mod_समयr(&info->समयr->समयr,
		  msecs_to_jअगरfies(info->समयout * 1000) + jअगरfies);

	वापस 0;

out_मुक्त_attr:
	kमुक्त(info->समयr->attr.attr.name);
out_मुक्त_समयr:
	kमुक्त(info->समयr);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक idleसमयr_tg_create_v1(काष्ठा idleसमयr_tg_info_v1 *info)
अणु
	पूर्णांक ret;

	info->समयr = kदो_स्मृति(माप(*info->समयr), GFP_KERNEL);
	अगर (!info->समयr) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	ret = idleसमयr_check_sysfs_name(info->label, माप(info->label));
	अगर (ret < 0)
		जाओ out_मुक्त_समयr;

	sysfs_attr_init(&info->समयr->attr.attr);
	info->समयr->attr.attr.name = kstrdup(info->label, GFP_KERNEL);
	अगर (!info->समयr->attr.attr.name) अणु
		ret = -ENOMEM;
		जाओ out_मुक्त_समयr;
	पूर्ण
	info->समयr->attr.attr.mode = 0444;
	info->समयr->attr.show = idleसमयr_tg_show;

	ret = sysfs_create_file(idleसमयr_tg_kobj, &info->समयr->attr.attr);
	अगर (ret < 0) अणु
		pr_debug("couldn't add file to sysfs");
		जाओ out_मुक्त_attr;
	पूर्ण

	/*  notअगरy userspace  */
	kobject_uevent(idleसमयr_tg_kobj,KOBJ_ADD);

	list_add(&info->समयr->entry, &idleसमयr_tg_list);
	pr_debug("timer type value is %u", info->समयr_type);
	info->समयr->समयr_type = info->समयr_type;
	info->समयr->refcnt = 1;

	INIT_WORK(&info->समयr->work, idleसमयr_tg_work);

	अगर (info->समयr->समयr_type & XT_IDLETIMER_ALARM) अणु
		kसमय_प्रकार tout;
		alarm_init(&info->समयr->alarm, ALARM_BOOTTIME,
			   idleसमयr_tg_alarmproc);
		info->समयr->alarm.data = info->समयr;
		tout = kसमय_set(info->समयout, 0);
		alarm_start_relative(&info->समयr->alarm, tout);
	पूर्ण अन्यथा अणु
		समयr_setup(&info->समयr->समयr, idleसमयr_tg_expired, 0);
		mod_समयr(&info->समयr->समयr,
				msecs_to_jअगरfies(info->समयout * 1000) + jअगरfies);
	पूर्ण

	वापस 0;

out_मुक्त_attr:
	kमुक्त(info->समयr->attr.attr.name);
out_मुक्त_समयr:
	kमुक्त(info->समयr);
out:
	वापस ret;
पूर्ण

/*
 * The actual xt_tables plugin.
 */
अटल अचिन्हित पूर्णांक idleसमयr_tg_target(काष्ठा sk_buff *skb,
					 स्थिर काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा idleसमयr_tg_info *info = par->targinfo;

	pr_debug("resetting timer %s, timeout period %u\n",
		 info->label, info->समयout);

	mod_समयr(&info->समयr->समयr,
		  msecs_to_jअगरfies(info->समयout * 1000) + jअगरfies);

	वापस XT_CONTINUE;
पूर्ण

/*
 * The actual xt_tables plugin.
 */
अटल अचिन्हित पूर्णांक idleसमयr_tg_target_v1(काष्ठा sk_buff *skb,
					 स्थिर काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा idleसमयr_tg_info_v1 *info = par->targinfo;

	pr_debug("resetting timer %s, timeout period %u\n",
		 info->label, info->समयout);

	अगर (info->समयr->समयr_type & XT_IDLETIMER_ALARM) अणु
		kसमय_प्रकार tout = kसमय_set(info->समयout, 0);
		alarm_start_relative(&info->समयr->alarm, tout);
	पूर्ण अन्यथा अणु
		mod_समयr(&info->समयr->समयr,
				msecs_to_jअगरfies(info->समयout * 1000) + jअगरfies);
	पूर्ण

	वापस XT_CONTINUE;
पूर्ण

अटल पूर्णांक idleसमयr_tg_helper(काष्ठा idleसमयr_tg_info *info)
अणु
	अगर (info->समयout == 0) अणु
		pr_debug("timeout value is zero\n");
		वापस -EINVAL;
	पूर्ण
	अगर (info->समयout >= पूर्णांक_उच्च / 1000) अणु
		pr_debug("timeout value is too big\n");
		वापस -EINVAL;
	पूर्ण
	अगर (info->label[0] == '\0' ||
	    strnlen(info->label,
		    MAX_IDLETIMER_LABEL_SIZE) == MAX_IDLETIMER_LABEL_SIZE) अणु
		pr_debug("label is empty or not nul-terminated\n");
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण


अटल पूर्णांक idleसमयr_tg_checkentry(स्थिर काष्ठा xt_tgchk_param *par)
अणु
	काष्ठा idleसमयr_tg_info *info = par->targinfo;
	पूर्णांक ret;

	pr_debug("checkentry targinfo%s\n", info->label);

	ret = idleसमयr_tg_helper(info);
	अगर(ret < 0)
	अणु
		pr_debug("checkentry helper return invalid\n");
		वापस -EINVAL;
	पूर्ण
	mutex_lock(&list_mutex);

	info->समयr = __idleसमयr_tg_find_by_label(info->label);
	अगर (info->समयr) अणु
		info->समयr->refcnt++;
		mod_समयr(&info->समयr->समयr,
			  msecs_to_jअगरfies(info->समयout * 1000) + jअगरfies);

		pr_debug("increased refcnt of timer %s to %u\n",
			 info->label, info->समयr->refcnt);
	पूर्ण अन्यथा अणु
		ret = idleसमयr_tg_create(info);
		अगर (ret < 0) अणु
			pr_debug("failed to create timer\n");
			mutex_unlock(&list_mutex);
			वापस ret;
		पूर्ण
	पूर्ण

	mutex_unlock(&list_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक idleसमयr_tg_checkentry_v1(स्थिर काष्ठा xt_tgchk_param *par)
अणु
	काष्ठा idleसमयr_tg_info_v1 *info = par->targinfo;
	पूर्णांक ret;

	pr_debug("checkentry targinfo%s\n", info->label);

	अगर (info->send_nl_msg)
		वापस -EOPNOTSUPP;

	ret = idleसमयr_tg_helper((काष्ठा idleसमयr_tg_info *)info);
	अगर(ret < 0)
	अणु
		pr_debug("checkentry helper return invalid\n");
		वापस -EINVAL;
	पूर्ण

	अगर (info->समयr_type > XT_IDLETIMER_ALARM) अणु
		pr_debug("invalid value for timer type\n");
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&list_mutex);

	info->समयr = __idleसमयr_tg_find_by_label(info->label);
	अगर (info->समयr) अणु
		अगर (info->समयr->समयr_type != info->समयr_type) अणु
			pr_debug("Adding/Replacing rule with same label and different timer type is not allowed\n");
			mutex_unlock(&list_mutex);
			वापस -EINVAL;
		पूर्ण

		info->समयr->refcnt++;
		अगर (info->समयr_type & XT_IDLETIMER_ALARM) अणु
			/* calculate reमुख्यing expiry समय */
			kसमय_प्रकार tout = alarm_expires_reमुख्यing(&info->समयr->alarm);
			काष्ठा बारpec64 kबारpec = kसमय_प्रकारo_बारpec64(tout);

			अगर (kबारpec.tv_sec > 0) अणु
				pr_debug("time_expiry_remaining %lld\n",
					 kबारpec.tv_sec);
				alarm_start_relative(&info->समयr->alarm, tout);
			पूर्ण
		पूर्ण अन्यथा अणु
				mod_समयr(&info->समयr->समयr,
					msecs_to_jअगरfies(info->समयout * 1000) + jअगरfies);
		पूर्ण
		pr_debug("increased refcnt of timer %s to %u\n",
			 info->label, info->समयr->refcnt);
	पूर्ण अन्यथा अणु
		ret = idleसमयr_tg_create_v1(info);
		अगर (ret < 0) अणु
			pr_debug("failed to create timer\n");
			mutex_unlock(&list_mutex);
			वापस ret;
		पूर्ण
	पूर्ण

	mutex_unlock(&list_mutex);
	वापस 0;
पूर्ण

अटल व्योम idleसमयr_tg_destroy(स्थिर काष्ठा xt_tgdtor_param *par)
अणु
	स्थिर काष्ठा idleसमयr_tg_info *info = par->targinfo;

	pr_debug("destroy targinfo %s\n", info->label);

	mutex_lock(&list_mutex);

	अगर (--info->समयr->refcnt == 0) अणु
		pr_debug("deleting timer %s\n", info->label);

		list_del(&info->समयr->entry);
		del_समयr_sync(&info->समयr->समयr);
		cancel_work_sync(&info->समयr->work);
		sysfs_हटाओ_file(idleसमयr_tg_kobj, &info->समयr->attr.attr);
		kमुक्त(info->समयr->attr.attr.name);
		kमुक्त(info->समयr);
	पूर्ण अन्यथा अणु
		pr_debug("decreased refcnt of timer %s to %u\n",
			 info->label, info->समयr->refcnt);
	पूर्ण

	mutex_unlock(&list_mutex);
पूर्ण

अटल व्योम idleसमयr_tg_destroy_v1(स्थिर काष्ठा xt_tgdtor_param *par)
अणु
	स्थिर काष्ठा idleसमयr_tg_info_v1 *info = par->targinfo;

	pr_debug("destroy targinfo %s\n", info->label);

	mutex_lock(&list_mutex);

	अगर (--info->समयr->refcnt == 0) अणु
		pr_debug("deleting timer %s\n", info->label);

		list_del(&info->समयr->entry);
		अगर (info->समयr->समयr_type & XT_IDLETIMER_ALARM) अणु
			alarm_cancel(&info->समयr->alarm);
		पूर्ण अन्यथा अणु
			del_समयr_sync(&info->समयr->समयr);
		पूर्ण
		cancel_work_sync(&info->समयr->work);
		sysfs_हटाओ_file(idleसमयr_tg_kobj, &info->समयr->attr.attr);
		kमुक्त(info->समयr->attr.attr.name);
		kमुक्त(info->समयr);
	पूर्ण अन्यथा अणु
		pr_debug("decreased refcnt of timer %s to %u\n",
			 info->label, info->समयr->refcnt);
	पूर्ण

	mutex_unlock(&list_mutex);
पूर्ण


अटल काष्ठा xt_target idleसमयr_tg[] __पढ़ो_mostly = अणु
	अणु
	.name		= "IDLETIMER",
	.family		= NFPROTO_UNSPEC,
	.target		= idleसमयr_tg_target,
	.tarमाला_लोize     = माप(काष्ठा idleसमयr_tg_info),
	.usersize	= दुरत्व(काष्ठा idleसमयr_tg_info, समयr),
	.checkentry	= idleसमयr_tg_checkentry,
	.destroy        = idleसमयr_tg_destroy,
	.me		= THIS_MODULE,
	पूर्ण,
	अणु
	.name		= "IDLETIMER",
	.family		= NFPROTO_UNSPEC,
	.revision	= 1,
	.target		= idleसमयr_tg_target_v1,
	.tarमाला_लोize     = माप(काष्ठा idleसमयr_tg_info_v1),
	.usersize	= दुरत्व(काष्ठा idleसमयr_tg_info_v1, समयr),
	.checkentry	= idleसमयr_tg_checkentry_v1,
	.destroy        = idleसमयr_tg_destroy_v1,
	.me		= THIS_MODULE,
	पूर्ण,


पूर्ण;

अटल काष्ठा class *idleसमयr_tg_class;

अटल काष्ठा device *idleसमयr_tg_device;

अटल पूर्णांक __init idleसमयr_tg_init(व्योम)
अणु
	पूर्णांक err;

	idleसमयr_tg_class = class_create(THIS_MODULE, "xt_idletimer");
	err = PTR_ERR(idleसमयr_tg_class);
	अगर (IS_ERR(idleसमयr_tg_class)) अणु
		pr_debug("couldn't register device class\n");
		जाओ out;
	पूर्ण

	idleसमयr_tg_device = device_create(idleसमयr_tg_class, शून्य,
					    MKDEV(0, 0), शून्य, "timers");
	err = PTR_ERR(idleसमयr_tg_device);
	अगर (IS_ERR(idleसमयr_tg_device)) अणु
		pr_debug("couldn't register system device\n");
		जाओ out_class;
	पूर्ण

	idleसमयr_tg_kobj = &idleसमयr_tg_device->kobj;

	err = xt_रेजिस्टर_tarमाला_लो(idleसमयr_tg, ARRAY_SIZE(idleसमयr_tg));

	अगर (err < 0) अणु
		pr_debug("couldn't register xt target\n");
		जाओ out_dev;
	पूर्ण

	वापस 0;
out_dev:
	device_destroy(idleसमयr_tg_class, MKDEV(0, 0));
out_class:
	class_destroy(idleसमयr_tg_class);
out:
	वापस err;
पूर्ण

अटल व्योम __निकास idleसमयr_tg_निकास(व्योम)
अणु
	xt_unरेजिस्टर_tarमाला_लो(idleसमयr_tg, ARRAY_SIZE(idleसमयr_tg));

	device_destroy(idleसमयr_tg_class, MKDEV(0, 0));
	class_destroy(idleसमयr_tg_class);
पूर्ण

module_init(idleसमयr_tg_init);
module_निकास(idleसमयr_tg_निकास);

MODULE_AUTHOR("Timo Teras <ext-timo.teras@nokia.com>");
MODULE_AUTHOR("Luciano Coelho <luciano.coelho@nokia.com>");
MODULE_DESCRIPTION("Xtables: idle time monitor");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("ipt_IDLETIMER");
MODULE_ALIAS("ip6t_IDLETIMER");
