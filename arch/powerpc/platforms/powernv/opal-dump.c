<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * PowerNV OPAL Dump Interface
 *
 * Copyright 2013,2014 IBM Corp.
 */

#समावेश <linux/kobject.h>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश <यंत्र/opal.h>

#घोषणा DUMP_TYPE_FSP	0x01

काष्ठा dump_obj अणु
	काष्ठा kobject  kobj;
	काष्ठा bin_attribute dump_attr;
	uपूर्णांक32_t	id;  /* becomes object name */
	uपूर्णांक32_t	type;
	uपूर्णांक32_t	size;
	अक्षर		*buffer;
पूर्ण;
#घोषणा to_dump_obj(x) container_of(x, काष्ठा dump_obj, kobj)

काष्ठा dump_attribute अणु
	काष्ठा attribute attr;
	sमाप_प्रकार (*show)(काष्ठा dump_obj *dump, काष्ठा dump_attribute *attr,
			अक्षर *buf);
	sमाप_प्रकार (*store)(काष्ठा dump_obj *dump, काष्ठा dump_attribute *attr,
			 स्थिर अक्षर *buf, माप_प्रकार count);
पूर्ण;
#घोषणा to_dump_attr(x) container_of(x, काष्ठा dump_attribute, attr)

अटल sमाप_प्रकार dump_id_show(काष्ठा dump_obj *dump_obj,
			    काष्ठा dump_attribute *attr,
			    अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "0x%x\n", dump_obj->id);
पूर्ण

अटल स्थिर अक्षर* dump_type_to_string(uपूर्णांक32_t type)
अणु
	चयन (type) अणु
	हाल 0x01: वापस "SP Dump";
	हाल 0x02: वापस "System/Platform Dump";
	हाल 0x03: वापस "SMA Dump";
	शेष: वापस "unknown";
	पूर्ण
पूर्ण

अटल sमाप_प्रकार dump_type_show(काष्ठा dump_obj *dump_obj,
			      काष्ठा dump_attribute *attr,
			      अक्षर *buf)
अणु

	वापस प्र_लिखो(buf, "0x%x %s\n", dump_obj->type,
		       dump_type_to_string(dump_obj->type));
पूर्ण

अटल sमाप_प्रकार dump_ack_show(काष्ठा dump_obj *dump_obj,
			     काष्ठा dump_attribute *attr,
			     अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "ack - acknowledge dump\n");
पूर्ण

/*
 * Send acknowledgement to OPAL
 */
अटल पूर्णांक64_t dump_send_ack(uपूर्णांक32_t dump_id)
अणु
	पूर्णांक rc;

	rc = opal_dump_ack(dump_id);
	अगर (rc)
		pr_warn("%s: Failed to send ack to Dump ID 0x%x (%d)\n",
			__func__, dump_id, rc);
	वापस rc;
पूर्ण

अटल sमाप_प्रकार dump_ack_store(काष्ठा dump_obj *dump_obj,
			      काष्ठा dump_attribute *attr,
			      स्थिर अक्षर *buf,
			      माप_प्रकार count)
अणु
	/*
	 * Try to self हटाओ this attribute. If we are successful,
	 * delete the kobject itself.
	 */
	अगर (sysfs_हटाओ_file_self(&dump_obj->kobj, &attr->attr)) अणु
		dump_send_ack(dump_obj->id);
		kobject_put(&dump_obj->kobj);
	पूर्ण
	वापस count;
पूर्ण

/* Attributes of a dump
 * The binary attribute of the dump itself is dynamic
 * due to the dynamic size of the dump
 */
अटल काष्ठा dump_attribute id_attribute =
	__ATTR(id, 0444, dump_id_show, शून्य);
अटल काष्ठा dump_attribute type_attribute =
	__ATTR(type, 0444, dump_type_show, शून्य);
अटल काष्ठा dump_attribute ack_attribute =
	__ATTR(acknowledge, 0660, dump_ack_show, dump_ack_store);

अटल sमाप_प्रकार init_dump_show(काष्ठा dump_obj *dump_obj,
			      काष्ठा dump_attribute *attr,
			      अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "1 - initiate Service Processor(FSP) dump\n");
पूर्ण

अटल पूर्णांक64_t dump_fips_init(uपूर्णांक8_t type)
अणु
	पूर्णांक rc;

	rc = opal_dump_init(type);
	अगर (rc)
		pr_warn("%s: Failed to initiate FSP dump (%d)\n",
			__func__, rc);
	वापस rc;
पूर्ण

अटल sमाप_प्रकार init_dump_store(काष्ठा dump_obj *dump_obj,
			       काष्ठा dump_attribute *attr,
			       स्थिर अक्षर *buf,
			       माप_प्रकार count)
अणु
	पूर्णांक rc;

	rc = dump_fips_init(DUMP_TYPE_FSP);
	अगर (rc == OPAL_SUCCESS)
		pr_info("%s: Initiated FSP dump\n", __func__);

	वापस count;
पूर्ण

अटल काष्ठा dump_attribute initiate_attribute =
	__ATTR(initiate_dump, 0600, init_dump_show, init_dump_store);

अटल काष्ठा attribute *initiate_attrs[] = अणु
	&initiate_attribute.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group initiate_attr_group = अणु
	.attrs = initiate_attrs,
पूर्ण;

अटल काष्ठा kset *dump_kset;

अटल sमाप_प्रकार dump_attr_show(काष्ठा kobject *kobj,
			      काष्ठा attribute *attr,
			      अक्षर *buf)
अणु
	काष्ठा dump_attribute *attribute;
	काष्ठा dump_obj *dump;

	attribute = to_dump_attr(attr);
	dump = to_dump_obj(kobj);

	अगर (!attribute->show)
		वापस -EIO;

	वापस attribute->show(dump, attribute, buf);
पूर्ण

अटल sमाप_प्रकार dump_attr_store(काष्ठा kobject *kobj,
			       काष्ठा attribute *attr,
			       स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा dump_attribute *attribute;
	काष्ठा dump_obj *dump;

	attribute = to_dump_attr(attr);
	dump = to_dump_obj(kobj);

	अगर (!attribute->store)
		वापस -EIO;

	वापस attribute->store(dump, attribute, buf, len);
पूर्ण

अटल स्थिर काष्ठा sysfs_ops dump_sysfs_ops = अणु
	.show = dump_attr_show,
	.store = dump_attr_store,
पूर्ण;

अटल व्योम dump_release(काष्ठा kobject *kobj)
अणु
	काष्ठा dump_obj *dump;

	dump = to_dump_obj(kobj);
	vमुक्त(dump->buffer);
	kमुक्त(dump);
पूर्ण

अटल काष्ठा attribute *dump_शेष_attrs[] = अणु
	&id_attribute.attr,
	&type_attribute.attr,
	&ack_attribute.attr,
	शून्य,
पूर्ण;

अटल काष्ठा kobj_type dump_ktype = अणु
	.sysfs_ops = &dump_sysfs_ops,
	.release = &dump_release,
	.शेष_attrs = dump_शेष_attrs,
पूर्ण;

अटल पूर्णांक64_t dump_पढ़ो_info(uपूर्णांक32_t *dump_id, uपूर्णांक32_t *dump_size, uपूर्णांक32_t *dump_type)
अणु
	__be32 id, size, type;
	पूर्णांक rc;

	type = cpu_to_be32(0xffffffff);

	rc = opal_dump_info2(&id, &size, &type);
	अगर (rc == OPAL_PARAMETER)
		rc = opal_dump_info(&id, &size);

	अगर (rc) अणु
		pr_warn("%s: Failed to get dump info (%d)\n",
			__func__, rc);
		वापस rc;
	पूर्ण

	*dump_id = be32_to_cpu(id);
	*dump_size = be32_to_cpu(size);
	*dump_type = be32_to_cpu(type);

	वापस rc;
पूर्ण

अटल पूर्णांक64_t dump_पढ़ो_data(काष्ठा dump_obj *dump)
अणु
	काष्ठा opal_sg_list *list;
	uपूर्णांक64_t addr;
	पूर्णांक64_t rc;

	/* Allocate memory */
	dump->buffer = vzalloc(PAGE_ALIGN(dump->size));
	अगर (!dump->buffer) अणु
		pr_err("%s : Failed to allocate memory\n", __func__);
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	/* Generate SG list */
	list = opal_vदो_स्मृति_to_sg_list(dump->buffer, dump->size);
	अगर (!list) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	/* First entry address */
	addr = __pa(list);

	/* Fetch data */
	rc = OPAL_BUSY_EVENT;
	जबतक (rc == OPAL_BUSY || rc == OPAL_BUSY_EVENT) अणु
		rc = opal_dump_पढ़ो(dump->id, addr);
		अगर (rc == OPAL_BUSY_EVENT) अणु
			opal_poll_events(शून्य);
			msleep(20);
		पूर्ण
	पूर्ण

	अगर (rc != OPAL_SUCCESS && rc != OPAL_PARTIAL)
		pr_warn("%s: Extract dump failed for ID 0x%x\n",
			__func__, dump->id);

	/* Free SG list */
	opal_मुक्त_sg_list(list);

out:
	वापस rc;
पूर्ण

अटल sमाप_प्रकार dump_attr_पढ़ो(काष्ठा file *filep, काष्ठा kobject *kobj,
			      काष्ठा bin_attribute *bin_attr,
			      अक्षर *buffer, loff_t pos, माप_प्रकार count)
अणु
	sमाप_प्रकार rc;

	काष्ठा dump_obj *dump = to_dump_obj(kobj);

	अगर (!dump->buffer) अणु
		rc = dump_पढ़ो_data(dump);

		अगर (rc != OPAL_SUCCESS && rc != OPAL_PARTIAL) अणु
			vमुक्त(dump->buffer);
			dump->buffer = शून्य;

			वापस -EIO;
		पूर्ण
		अगर (rc == OPAL_PARTIAL) अणु
			/* On a partial पढ़ो, we just वापस EIO
			 * and rely on userspace to ask us to try
			 * again.
			 */
			pr_info("%s: Platform dump partially read. ID = 0x%x\n",
				__func__, dump->id);
			वापस -EIO;
		पूर्ण
	पूर्ण

	स_नकल(buffer, dump->buffer + pos, count);

	/* You may think we could मुक्त the dump buffer now and retrieve
	 * it again later अगर needed, but due to current firmware limitation,
	 * that's not the हाल. So, once पढ़ो पूर्णांकo userspace once,
	 * we keep the dump around until it's acknowledged by userspace.
	 */

	वापस count;
पूर्ण

अटल व्योम create_dump_obj(uपूर्णांक32_t id, माप_प्रकार size, uपूर्णांक32_t type)
अणु
	काष्ठा dump_obj *dump;
	पूर्णांक rc;

	dump = kzalloc(माप(*dump), GFP_KERNEL);
	अगर (!dump)
		वापस;

	dump->kobj.kset = dump_kset;

	kobject_init(&dump->kobj, &dump_ktype);

	sysfs_bin_attr_init(&dump->dump_attr);

	dump->dump_attr.attr.name = "dump";
	dump->dump_attr.attr.mode = 0400;
	dump->dump_attr.size = size;
	dump->dump_attr.पढ़ो = dump_attr_पढ़ो;

	dump->id = id;
	dump->size = size;
	dump->type = type;

	rc = kobject_add(&dump->kobj, शून्य, "0x%x-0x%x", type, id);
	अगर (rc) अणु
		kobject_put(&dump->kobj);
		वापस;
	पूर्ण

	/*
	 * As soon as the sysfs file क्रम this dump is created/activated there is
	 * a chance the opal_errd daemon (or any userspace) might पढ़ो and
	 * acknowledge the dump beक्रमe kobject_uevent() is called. If that
	 * happens then there is a potential race between
	 * dump_ack_store->kobject_put() and kobject_uevent() which leads to a
	 * use-after-मुक्त of a kernfs object resulting in a kernel crash.
	 *
	 * To aव्योम that, we need to take a reference on behalf of the bin file,
	 * so that our reference reमुख्यs valid जबतक we call kobject_uevent().
	 * We then drop our reference beक्रमe निकासing the function, leaving the
	 * bin file to drop the last reference (अगर it hasn't alपढ़ोy).
	 */

	/* Take a reference क्रम the bin file */
	kobject_get(&dump->kobj);
	rc = sysfs_create_bin_file(&dump->kobj, &dump->dump_attr);
	अगर (rc == 0) अणु
		kobject_uevent(&dump->kobj, KOBJ_ADD);

		pr_info("%s: New platform dump. ID = 0x%x Size %u\n",
			__func__, dump->id, dump->size);
	पूर्ण अन्यथा अणु
		/* Drop reference count taken क्रम bin file */
		kobject_put(&dump->kobj);
	पूर्ण

	/* Drop our reference */
	kobject_put(&dump->kobj);
	वापस;
पूर्ण

अटल irqवापस_t process_dump(पूर्णांक irq, व्योम *data)
अणु
	पूर्णांक rc;
	uपूर्णांक32_t dump_id, dump_size, dump_type;
	अक्षर name[22];
	काष्ठा kobject *kobj;

	rc = dump_पढ़ो_info(&dump_id, &dump_size, &dump_type);
	अगर (rc != OPAL_SUCCESS)
		वापस IRQ_HANDLED;

	प्र_लिखो(name, "0x%x-0x%x", dump_type, dump_id);

	/* we may get notअगरied twice, let's handle
	 * that gracefully and not create two conflicting
	 * entries.
	 */
	kobj = kset_find_obj(dump_kset, name);
	अगर (kobj) अणु
		/* Drop reference added by kset_find_obj() */
		kobject_put(kobj);
		वापस IRQ_HANDLED;
	पूर्ण

	create_dump_obj(dump_id, dump_size, dump_type);

	वापस IRQ_HANDLED;
पूर्ण

व्योम __init opal_platक्रमm_dump_init(व्योम)
अणु
	पूर्णांक rc;
	पूर्णांक dump_irq;

	/* ELOG not supported by firmware */
	अगर (!opal_check_token(OPAL_DUMP_READ))
		वापस;

	dump_kset = kset_create_and_add("dump", शून्य, opal_kobj);
	अगर (!dump_kset) अणु
		pr_warn("%s: Failed to create dump kset\n", __func__);
		वापस;
	पूर्ण

	rc = sysfs_create_group(&dump_kset->kobj, &initiate_attr_group);
	अगर (rc) अणु
		pr_warn("%s: Failed to create initiate dump attr group\n",
			__func__);
		kobject_put(&dump_kset->kobj);
		वापस;
	पूर्ण

	dump_irq = opal_event_request(ilog2(OPAL_EVENT_DUMP_AVAIL));
	अगर (!dump_irq) अणु
		pr_err("%s: Can't register OPAL event irq (%d)\n",
		       __func__, dump_irq);
		वापस;
	पूर्ण

	rc = request_thपढ़ोed_irq(dump_irq, शून्य, process_dump,
				IRQF_TRIGGER_HIGH | IRQF_ONESHOT,
				"opal-dump", शून्य);
	अगर (rc) अणु
		pr_err("%s: Can't request OPAL event irq (%d)\n",
		       __func__, rc);
		वापस;
	पूर्ण

	अगर (opal_check_token(OPAL_DUMP_RESEND))
		opal_dump_resend_notअगरication();
पूर्ण
