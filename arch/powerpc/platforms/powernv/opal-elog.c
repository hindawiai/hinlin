<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Error log support on PowerNV.
 *
 * Copyright 2013,2014 IBM Corp.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/of.h>
#समावेश <linux/slab.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/fs.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/kobject.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/opal.h>

काष्ठा elog_obj अणु
	काष्ठा kobject kobj;
	काष्ठा bin_attribute raw_attr;
	uपूर्णांक64_t id;
	uपूर्णांक64_t type;
	माप_प्रकार size;
	अक्षर *buffer;
पूर्ण;
#घोषणा to_elog_obj(x) container_of(x, काष्ठा elog_obj, kobj)

काष्ठा elog_attribute अणु
	काष्ठा attribute attr;
	sमाप_प्रकार (*show)(काष्ठा elog_obj *elog, काष्ठा elog_attribute *attr,
			अक्षर *buf);
	sमाप_प्रकार (*store)(काष्ठा elog_obj *elog, काष्ठा elog_attribute *attr,
			 स्थिर अक्षर *buf, माप_प्रकार count);
पूर्ण;
#घोषणा to_elog_attr(x) container_of(x, काष्ठा elog_attribute, attr)

अटल sमाप_प्रकार elog_id_show(काष्ठा elog_obj *elog_obj,
			    काष्ठा elog_attribute *attr,
			    अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "0x%llx\n", elog_obj->id);
पूर्ण

अटल स्थिर अक्षर *elog_type_to_string(uपूर्णांक64_t type)
अणु
	चयन (type) अणु
	हाल 0: वापस "PEL";
	शेष: वापस "unknown";
	पूर्ण
पूर्ण

अटल sमाप_प्रकार elog_type_show(काष्ठा elog_obj *elog_obj,
			      काष्ठा elog_attribute *attr,
			      अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "0x%llx %s\n",
		       elog_obj->type,
		       elog_type_to_string(elog_obj->type));
पूर्ण

अटल sमाप_प्रकार elog_ack_show(काष्ठा elog_obj *elog_obj,
			     काष्ठा elog_attribute *attr,
			     अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "ack - acknowledge log message\n");
पूर्ण

अटल sमाप_प्रकार elog_ack_store(काष्ठा elog_obj *elog_obj,
			      काष्ठा elog_attribute *attr,
			      स्थिर अक्षर *buf,
			      माप_प्रकार count)
अणु
	/*
	 * Try to self हटाओ this attribute. If we are successful,
	 * delete the kobject itself.
	 */
	अगर (sysfs_हटाओ_file_self(&elog_obj->kobj, &attr->attr)) अणु
		opal_send_ack_elog(elog_obj->id);
		kobject_put(&elog_obj->kobj);
	पूर्ण
	वापस count;
पूर्ण

अटल काष्ठा elog_attribute id_attribute =
	__ATTR(id, 0444, elog_id_show, शून्य);
अटल काष्ठा elog_attribute type_attribute =
	__ATTR(type, 0444, elog_type_show, शून्य);
अटल काष्ठा elog_attribute ack_attribute =
	__ATTR(acknowledge, 0660, elog_ack_show, elog_ack_store);

अटल काष्ठा kset *elog_kset;

अटल sमाप_प्रकार elog_attr_show(काष्ठा kobject *kobj,
			      काष्ठा attribute *attr,
			      अक्षर *buf)
अणु
	काष्ठा elog_attribute *attribute;
	काष्ठा elog_obj *elog;

	attribute = to_elog_attr(attr);
	elog = to_elog_obj(kobj);

	अगर (!attribute->show)
		वापस -EIO;

	वापस attribute->show(elog, attribute, buf);
पूर्ण

अटल sमाप_प्रकार elog_attr_store(काष्ठा kobject *kobj,
			       काष्ठा attribute *attr,
			       स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा elog_attribute *attribute;
	काष्ठा elog_obj *elog;

	attribute = to_elog_attr(attr);
	elog = to_elog_obj(kobj);

	अगर (!attribute->store)
		वापस -EIO;

	वापस attribute->store(elog, attribute, buf, len);
पूर्ण

अटल स्थिर काष्ठा sysfs_ops elog_sysfs_ops = अणु
	.show = elog_attr_show,
	.store = elog_attr_store,
पूर्ण;

अटल व्योम elog_release(काष्ठा kobject *kobj)
अणु
	काष्ठा elog_obj *elog;

	elog = to_elog_obj(kobj);
	kमुक्त(elog->buffer);
	kमुक्त(elog);
पूर्ण

अटल काष्ठा attribute *elog_शेष_attrs[] = अणु
	&id_attribute.attr,
	&type_attribute.attr,
	&ack_attribute.attr,
	शून्य,
पूर्ण;

अटल काष्ठा kobj_type elog_ktype = अणु
	.sysfs_ops = &elog_sysfs_ops,
	.release = &elog_release,
	.शेष_attrs = elog_शेष_attrs,
पूर्ण;

/* Maximum size of a single log on FSP is 16KB */
#घोषणा OPAL_MAX_ERRLOG_SIZE	16384

अटल sमाप_प्रकार raw_attr_पढ़ो(काष्ठा file *filep, काष्ठा kobject *kobj,
			     काष्ठा bin_attribute *bin_attr,
			     अक्षर *buffer, loff_t pos, माप_प्रकार count)
अणु
	पूर्णांक opal_rc;

	काष्ठा elog_obj *elog = to_elog_obj(kobj);

	/* We may have had an error पढ़ोing beक्रमe, so let's retry */
	अगर (!elog->buffer) अणु
		elog->buffer = kzalloc(elog->size, GFP_KERNEL);
		अगर (!elog->buffer)
			वापस -EIO;

		opal_rc = opal_पढ़ो_elog(__pa(elog->buffer),
					 elog->size, elog->id);
		अगर (opal_rc != OPAL_SUCCESS) अणु
			pr_err_ratelimited("ELOG: log read failed for log-id=%llx\n",
					   elog->id);
			kमुक्त(elog->buffer);
			elog->buffer = शून्य;
			वापस -EIO;
		पूर्ण
	पूर्ण

	स_नकल(buffer, elog->buffer + pos, count);

	वापस count;
पूर्ण

अटल व्योम create_elog_obj(uपूर्णांक64_t id, माप_प्रकार size, uपूर्णांक64_t type)
अणु
	काष्ठा elog_obj *elog;
	पूर्णांक rc;

	elog = kzalloc(माप(*elog), GFP_KERNEL);
	अगर (!elog)
		वापस;

	elog->kobj.kset = elog_kset;

	kobject_init(&elog->kobj, &elog_ktype);

	sysfs_bin_attr_init(&elog->raw_attr);

	elog->raw_attr.attr.name = "raw";
	elog->raw_attr.attr.mode = 0400;
	elog->raw_attr.size = size;
	elog->raw_attr.पढ़ो = raw_attr_पढ़ो;

	elog->id = id;
	elog->size = size;
	elog->type = type;

	elog->buffer = kzalloc(elog->size, GFP_KERNEL);

	अगर (elog->buffer) अणु
		rc = opal_पढ़ो_elog(__pa(elog->buffer),
					 elog->size, elog->id);
		अगर (rc != OPAL_SUCCESS) अणु
			pr_err("ELOG: log read failed for log-id=%llx\n",
			       elog->id);
			kमुक्त(elog->buffer);
			elog->buffer = शून्य;
		पूर्ण
	पूर्ण

	rc = kobject_add(&elog->kobj, शून्य, "0x%llx", id);
	अगर (rc) अणु
		kobject_put(&elog->kobj);
		वापस;
	पूर्ण

	/*
	 * As soon as the sysfs file क्रम this elog is created/activated there is
	 * a chance the opal_errd daemon (or any userspace) might पढ़ो and
	 * acknowledge the elog beक्रमe kobject_uevent() is called. If that
	 * happens then there is a potential race between
	 * elog_ack_store->kobject_put() and kobject_uevent() which leads to a
	 * use-after-मुक्त of a kernfs object resulting in a kernel crash.
	 *
	 * To aव्योम that, we need to take a reference on behalf of the bin file,
	 * so that our reference reमुख्यs valid जबतक we call kobject_uevent().
	 * We then drop our reference beक्रमe निकासing the function, leaving the
	 * bin file to drop the last reference (अगर it hasn't alपढ़ोy).
	 */

	/* Take a reference क्रम the bin file */
	kobject_get(&elog->kobj);
	rc = sysfs_create_bin_file(&elog->kobj, &elog->raw_attr);
	अगर (rc == 0) अणु
		kobject_uevent(&elog->kobj, KOBJ_ADD);
	पूर्ण अन्यथा अणु
		/* Drop the reference taken क्रम the bin file */
		kobject_put(&elog->kobj);
	पूर्ण

	/* Drop our reference */
	kobject_put(&elog->kobj);

	वापस;
पूर्ण

अटल irqवापस_t elog_event(पूर्णांक irq, व्योम *data)
अणु
	__be64 size;
	__be64 id;
	__be64 type;
	uपूर्णांक64_t elog_size;
	uपूर्णांक64_t log_id;
	uपूर्णांक64_t elog_type;
	पूर्णांक rc;
	अक्षर name[2+16+1];
	काष्ठा kobject *kobj;

	rc = opal_get_elog_size(&id, &size, &type);
	अगर (rc != OPAL_SUCCESS) अणु
		pr_err("ELOG: OPAL log info read failed\n");
		वापस IRQ_HANDLED;
	पूर्ण

	elog_size = be64_to_cpu(size);
	log_id = be64_to_cpu(id);
	elog_type = be64_to_cpu(type);

	WARN_ON(elog_size > OPAL_MAX_ERRLOG_SIZE);

	अगर (elog_size >= OPAL_MAX_ERRLOG_SIZE)
		elog_size  =  OPAL_MAX_ERRLOG_SIZE;

	प्र_लिखो(name, "0x%llx", log_id);

	/* we may get notअगरied twice, let's handle
	 * that gracefully and not create two conflicting
	 * entries.
	 */
	kobj = kset_find_obj(elog_kset, name);
	अगर (kobj) अणु
		/* Drop reference added by kset_find_obj() */
		kobject_put(kobj);
		वापस IRQ_HANDLED;
	पूर्ण

	create_elog_obj(log_id, elog_size, elog_type);

	वापस IRQ_HANDLED;
पूर्ण

पूर्णांक __init opal_elog_init(व्योम)
अणु
	पूर्णांक rc = 0, irq;

	/* ELOG not supported by firmware */
	अगर (!opal_check_token(OPAL_ELOG_READ))
		वापस -1;

	elog_kset = kset_create_and_add("elog", शून्य, opal_kobj);
	अगर (!elog_kset) अणु
		pr_warn("%s: failed to create elog kset\n", __func__);
		वापस -1;
	पूर्ण

	irq = opal_event_request(ilog2(OPAL_EVENT_ERROR_LOG_AVAIL));
	अगर (!irq) अणु
		pr_err("%s: Can't register OPAL event irq (%d)\n",
		       __func__, irq);
		वापस irq;
	पूर्ण

	rc = request_thपढ़ोed_irq(irq, शून्य, elog_event,
			IRQF_TRIGGER_HIGH | IRQF_ONESHOT, "opal-elog", शून्य);
	अगर (rc) अणु
		pr_err("%s: Can't request OPAL event irq (%d)\n",
		       __func__, rc);
		वापस rc;
	पूर्ण

	/* We are now पढ़ोy to pull error logs from opal. */
	अगर (opal_check_token(OPAL_ELOG_RESEND))
		opal_resend_pending_logs();

	वापस 0;
पूर्ण
