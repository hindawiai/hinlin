<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Windfarm PowerMac thermal control. Core
 *
 * (c) Copyright 2005 Benjamin Herrenschmidt, IBM Corp.
 *                    <benh@kernel.crashing.org>
 *
 * This core code tracks the list of sensors & controls, रेजिस्टर
 * clients, and holds the kernel thपढ़ो used क्रम control.
 *
 * TODO:
 *
 * Add some inक्रमmation about sensor/control type and data क्रमmat to
 * sensors/controls, and have the sysfs attribute stuff be moved
 * generically here instead of hard coded in the platक्रमm specअगरic
 * driver as it us currently
 *
 * This however requires solving some annoying lअगरeसमय issues with
 * sysfs which करोesn't seem to have lअगरeसमय rules क्रम काष्ठा attribute,
 * I may have to create full features kobjects क्रम every sensor/control
 * instead which is a bit of an overसमाप्त imho
 */

#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/reboot.h>
#समावेश <linux/device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mutex.h>
#समावेश <linux/मुक्तzer.h>

#समावेश <यंत्र/prom.h>

#समावेश "windfarm.h"

#घोषणा VERSION "0.2"

#अघोषित DEBUG

#अगर_घोषित DEBUG
#घोषणा DBG(args...)	prपूर्णांकk(args)
#अन्यथा
#घोषणा DBG(args...)	करो अणु पूर्ण जबतक(0)
#पूर्ण_अगर

अटल LIST_HEAD(wf_controls);
अटल LIST_HEAD(wf_sensors);
अटल DEFINE_MUTEX(wf_lock);
अटल BLOCKING_NOTIFIER_HEAD(wf_client_list);
अटल पूर्णांक wf_client_count;
अटल अचिन्हित पूर्णांक wf_overtemp;
अटल अचिन्हित पूर्णांक wf_overtemp_counter;
अटल काष्ठा task_काष्ठा *wf_thपढ़ो;

अटल काष्ठा platक्रमm_device wf_platक्रमm_device = अणु
	.name	= "windfarm",
पूर्ण;

/*
 * Utilities & tick thपढ़ो
 */

अटल अंतरभूत व्योम wf_notअगरy(पूर्णांक event, व्योम *param)
अणु
	blocking_notअगरier_call_chain(&wf_client_list, event, param);
पूर्ण

अटल पूर्णांक wf_critical_overtemp(व्योम)
अणु
	अटल अक्षर स्थिर critical_overtemp_path[] = "/sbin/critical_overtemp";
	अक्षर *argv[] = अणु (अक्षर *)critical_overtemp_path, शून्य पूर्ण;
	अटल अक्षर *envp[] = अणु "HOME=/",
				"TERM=linux",
				"PATH=/sbin:/usr/sbin:/bin:/usr/bin",
				शून्य पूर्ण;

	वापस call_usermodehelper(critical_overtemp_path,
				   argv, envp, UMH_WAIT_EXEC);
पूर्ण

अटल पूर्णांक wf_thपढ़ो_func(व्योम *data)
अणु
	अचिन्हित दीर्घ next, delay;

	next = jअगरfies;

	DBG("wf: thread started\n");

	set_मुक्तzable();
	जबतक (!kthपढ़ो_should_stop()) अणु
		try_to_मुक्तze();

		अगर (समय_after_eq(jअगरfies, next)) अणु
			wf_notअगरy(WF_EVENT_TICK, शून्य);
			अगर (wf_overtemp) अणु
				wf_overtemp_counter++;
				/* 10 seconds overtemp, notअगरy userland */
				अगर (wf_overtemp_counter > 10)
					wf_critical_overtemp();
				/* 30 seconds, shutकरोwn */
				अगर (wf_overtemp_counter > 30) अणु
					prपूर्णांकk(KERN_ERR "windfarm: Overtemp "
					       "for more than 30"
					       " seconds, shutting down\n");
					machine_घातer_off();
				पूर्ण
			पूर्ण
			next += HZ;
		पूर्ण

		delay = next - jअगरfies;
		अगर (delay <= HZ)
			schedule_समयout_पूर्णांकerruptible(delay);
	पूर्ण

	DBG("wf: thread stopped\n");

	वापस 0;
पूर्ण

अटल व्योम wf_start_thपढ़ो(व्योम)
अणु
	wf_thपढ़ो = kthपढ़ो_run(wf_thपढ़ो_func, शून्य, "kwindfarm");
	अगर (IS_ERR(wf_thपढ़ो)) अणु
		prपूर्णांकk(KERN_ERR "windfarm: failed to create thread,err %ld\n",
		       PTR_ERR(wf_thपढ़ो));
		wf_thपढ़ो = शून्य;
	पूर्ण
पूर्ण


अटल व्योम wf_stop_thपढ़ो(व्योम)
अणु
	अगर (wf_thपढ़ो)
		kthपढ़ो_stop(wf_thपढ़ो);
	wf_thपढ़ो = शून्य;
पूर्ण

/*
 * Controls
 */

अटल व्योम wf_control_release(काष्ठा kref *kref)
अणु
	काष्ठा wf_control *ct = container_of(kref, काष्ठा wf_control, ref);

	DBG("wf: Deleting control %s\n", ct->name);

	अगर (ct->ops && ct->ops->release)
		ct->ops->release(ct);
	अन्यथा
		kमुक्त(ct);
पूर्ण

अटल sमाप_प्रकार wf_show_control(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा wf_control *ctrl = container_of(attr, काष्ठा wf_control, attr);
	स्थिर अक्षर *typestr;
	s32 val = 0;
	पूर्णांक err;

	err = ctrl->ops->get_value(ctrl, &val);
	अगर (err < 0) अणु
		अगर (err == -EFAULT)
			वापस प्र_लिखो(buf, "<HW FAULT>\n");
		वापस err;
	पूर्ण
	चयन(ctrl->type) अणु
	हाल WF_CONTROL_RPM_FAN:
		typestr = " RPM";
		अवरोध;
	हाल WF_CONTROL_PWM_FAN:
		typestr = " %";
		अवरोध;
	शेष:
		typestr = "";
	पूर्ण
	वापस प्र_लिखो(buf, "%d%s\n", val, typestr);
पूर्ण

/* This is really only क्रम debugging... */
अटल sमाप_प्रकार wf_store_control(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा wf_control *ctrl = container_of(attr, काष्ठा wf_control, attr);
	पूर्णांक val;
	पूर्णांक err;
	अक्षर *endp;

	val = simple_म_से_अदीर्घ(buf, &endp, 0);
	जबतक (endp < buf + count && (*endp == ' ' || *endp == '\n'))
		++endp;
	अगर (endp - buf < count)
		वापस -EINVAL;
	err = ctrl->ops->set_value(ctrl, val);
	अगर (err < 0)
		वापस err;
	वापस count;
पूर्ण

पूर्णांक wf_रेजिस्टर_control(काष्ठा wf_control *new_ct)
अणु
	काष्ठा wf_control *ct;

	mutex_lock(&wf_lock);
	list_क्रम_each_entry(ct, &wf_controls, link) अणु
		अगर (!म_भेद(ct->name, new_ct->name)) अणु
			prपूर्णांकk(KERN_WARNING "windfarm: trying to register"
			       " duplicate control %s\n", ct->name);
			mutex_unlock(&wf_lock);
			वापस -EEXIST;
		पूर्ण
	पूर्ण
	kref_init(&new_ct->ref);
	list_add(&new_ct->link, &wf_controls);

	sysfs_attr_init(&new_ct->attr.attr);
	new_ct->attr.attr.name = new_ct->name;
	new_ct->attr.attr.mode = 0644;
	new_ct->attr.show = wf_show_control;
	new_ct->attr.store = wf_store_control;
	अगर (device_create_file(&wf_platक्रमm_device.dev, &new_ct->attr))
		prपूर्णांकk(KERN_WARNING "windfarm: device_create_file failed"
			" for %s\n", new_ct->name);
		/* the subप्रणाली still करोes useful work without the file */

	DBG("wf: Registered control %s\n", new_ct->name);

	wf_notअगरy(WF_EVENT_NEW_CONTROL, new_ct);
	mutex_unlock(&wf_lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(wf_रेजिस्टर_control);

व्योम wf_unरेजिस्टर_control(काष्ठा wf_control *ct)
अणु
	mutex_lock(&wf_lock);
	list_del(&ct->link);
	mutex_unlock(&wf_lock);

	DBG("wf: Unregistered control %s\n", ct->name);

	kref_put(&ct->ref, wf_control_release);
पूर्ण
EXPORT_SYMBOL_GPL(wf_unरेजिस्टर_control);

पूर्णांक wf_get_control(काष्ठा wf_control *ct)
अणु
	अगर (!try_module_get(ct->ops->owner))
		वापस -ENODEV;
	kref_get(&ct->ref);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(wf_get_control);

व्योम wf_put_control(काष्ठा wf_control *ct)
अणु
	काष्ठा module *mod = ct->ops->owner;
	kref_put(&ct->ref, wf_control_release);
	module_put(mod);
पूर्ण
EXPORT_SYMBOL_GPL(wf_put_control);


/*
 * Sensors
 */


अटल व्योम wf_sensor_release(काष्ठा kref *kref)
अणु
	काष्ठा wf_sensor *sr = container_of(kref, काष्ठा wf_sensor, ref);

	DBG("wf: Deleting sensor %s\n", sr->name);

	अगर (sr->ops && sr->ops->release)
		sr->ops->release(sr);
	अन्यथा
		kमुक्त(sr);
पूर्ण

अटल sमाप_प्रकार wf_show_sensor(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा wf_sensor *sens = container_of(attr, काष्ठा wf_sensor, attr);
	s32 val = 0;
	पूर्णांक err;

	err = sens->ops->get_value(sens, &val);
	अगर (err < 0)
		वापस err;
	वापस प्र_लिखो(buf, "%d.%03d\n", FIX32TOPRINT(val));
पूर्ण

पूर्णांक wf_रेजिस्टर_sensor(काष्ठा wf_sensor *new_sr)
अणु
	काष्ठा wf_sensor *sr;

	mutex_lock(&wf_lock);
	list_क्रम_each_entry(sr, &wf_sensors, link) अणु
		अगर (!म_भेद(sr->name, new_sr->name)) अणु
			prपूर्णांकk(KERN_WARNING "windfarm: trying to register"
			       " duplicate sensor %s\n", sr->name);
			mutex_unlock(&wf_lock);
			वापस -EEXIST;
		पूर्ण
	पूर्ण
	kref_init(&new_sr->ref);
	list_add(&new_sr->link, &wf_sensors);

	sysfs_attr_init(&new_sr->attr.attr);
	new_sr->attr.attr.name = new_sr->name;
	new_sr->attr.attr.mode = 0444;
	new_sr->attr.show = wf_show_sensor;
	new_sr->attr.store = शून्य;
	अगर (device_create_file(&wf_platक्रमm_device.dev, &new_sr->attr))
		prपूर्णांकk(KERN_WARNING "windfarm: device_create_file failed"
			" for %s\n", new_sr->name);
		/* the subप्रणाली still करोes useful work without the file */

	DBG("wf: Registered sensor %s\n", new_sr->name);

	wf_notअगरy(WF_EVENT_NEW_SENSOR, new_sr);
	mutex_unlock(&wf_lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(wf_रेजिस्टर_sensor);

व्योम wf_unरेजिस्टर_sensor(काष्ठा wf_sensor *sr)
अणु
	mutex_lock(&wf_lock);
	list_del(&sr->link);
	mutex_unlock(&wf_lock);

	DBG("wf: Unregistered sensor %s\n", sr->name);

	wf_put_sensor(sr);
पूर्ण
EXPORT_SYMBOL_GPL(wf_unरेजिस्टर_sensor);

पूर्णांक wf_get_sensor(काष्ठा wf_sensor *sr)
अणु
	अगर (!try_module_get(sr->ops->owner))
		वापस -ENODEV;
	kref_get(&sr->ref);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(wf_get_sensor);

व्योम wf_put_sensor(काष्ठा wf_sensor *sr)
अणु
	काष्ठा module *mod = sr->ops->owner;
	kref_put(&sr->ref, wf_sensor_release);
	module_put(mod);
पूर्ण
EXPORT_SYMBOL_GPL(wf_put_sensor);


/*
 * Client & notअगरication
 */

पूर्णांक wf_रेजिस्टर_client(काष्ठा notअगरier_block *nb)
अणु
	पूर्णांक rc;
	काष्ठा wf_control *ct;
	काष्ठा wf_sensor *sr;

	mutex_lock(&wf_lock);
	rc = blocking_notअगरier_chain_रेजिस्टर(&wf_client_list, nb);
	अगर (rc != 0)
		जाओ bail;
	wf_client_count++;
	list_क्रम_each_entry(ct, &wf_controls, link)
		wf_notअगरy(WF_EVENT_NEW_CONTROL, ct);
	list_क्रम_each_entry(sr, &wf_sensors, link)
		wf_notअगरy(WF_EVENT_NEW_SENSOR, sr);
	अगर (wf_client_count == 1)
		wf_start_thपढ़ो();
 bail:
	mutex_unlock(&wf_lock);
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(wf_रेजिस्टर_client);

पूर्णांक wf_unरेजिस्टर_client(काष्ठा notअगरier_block *nb)
अणु
	mutex_lock(&wf_lock);
	blocking_notअगरier_chain_unरेजिस्टर(&wf_client_list, nb);
	wf_client_count--;
	अगर (wf_client_count == 0)
		wf_stop_thपढ़ो();
	mutex_unlock(&wf_lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(wf_unरेजिस्टर_client);

व्योम wf_set_overtemp(व्योम)
अणु
	mutex_lock(&wf_lock);
	wf_overtemp++;
	अगर (wf_overtemp == 1) अणु
		prपूर्णांकk(KERN_WARNING "windfarm: Overtemp condition detected !\n");
		wf_overtemp_counter = 0;
		wf_notअगरy(WF_EVENT_OVERTEMP, शून्य);
	पूर्ण
	mutex_unlock(&wf_lock);
पूर्ण
EXPORT_SYMBOL_GPL(wf_set_overtemp);

व्योम wf_clear_overtemp(व्योम)
अणु
	mutex_lock(&wf_lock);
	WARN_ON(wf_overtemp == 0);
	अगर (wf_overtemp == 0) अणु
		mutex_unlock(&wf_lock);
		वापस;
	पूर्ण
	wf_overtemp--;
	अगर (wf_overtemp == 0) अणु
		prपूर्णांकk(KERN_WARNING "windfarm: Overtemp condition cleared !\n");
		wf_notअगरy(WF_EVENT_NORMALTEMP, शून्य);
	पूर्ण
	mutex_unlock(&wf_lock);
पूर्ण
EXPORT_SYMBOL_GPL(wf_clear_overtemp);

अटल पूर्णांक __init windfarm_core_init(व्योम)
अणु
	DBG("wf: core loaded\n");

	platक्रमm_device_रेजिस्टर(&wf_platक्रमm_device);
	वापस 0;
पूर्ण

अटल व्योम __निकास windfarm_core_निकास(व्योम)
अणु
	BUG_ON(wf_client_count != 0);

	DBG("wf: core unloaded\n");

	platक्रमm_device_unरेजिस्टर(&wf_platक्रमm_device);
पूर्ण


module_init(windfarm_core_init);
module_निकास(windfarm_core_निकास);

MODULE_AUTHOR("Benjamin Herrenschmidt <benh@kernel.crashing.org>");
MODULE_DESCRIPTION("Core component of PowerMac thermal control");
MODULE_LICENSE("GPL");

