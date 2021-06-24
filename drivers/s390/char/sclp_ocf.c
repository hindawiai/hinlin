<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *    SCLP OCF communication parameters sysfs पूर्णांकerface
 *
 *    Copyright IBM Corp. 2011
 *    Author(s): Martin Schwidefsky <schwidefsky@de.ibm.com>
 */

#घोषणा KMSG_COMPONENT "sclp_ocf"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/device.h>
#समावेश <linux/माला.स>
#समावेश <linux/प्रकार.स>
#समावेश <linux/kmod.h>
#समावेश <linux/समयr.h>
#समावेश <linux/err.h>
#समावेश <यंत्र/ebcdic.h>
#समावेश <यंत्र/sclp.h>

#समावेश "sclp.h"

#घोषणा OCF_LENGTH_HMC_NETWORK 8UL
#घोषणा OCF_LENGTH_CPC_NAME 8UL

अटल अक्षर hmc_network[OCF_LENGTH_HMC_NETWORK + 1];
अटल अक्षर cpc_name[OCF_LENGTH_CPC_NAME]; /* in EBCDIC */

अटल DEFINE_SPINLOCK(sclp_ocf_lock);
अटल काष्ठा work_काष्ठा sclp_ocf_change_work;

अटल काष्ठा kset *ocf_kset;

अटल व्योम sclp_ocf_change_notअगरy(काष्ठा work_काष्ठा *work)
अणु
	kobject_uevent(&ocf_kset->kobj, KOBJ_CHANGE);
पूर्ण

/* Handler क्रम OCF event. Look क्रम the CPC image name. */
अटल व्योम sclp_ocf_handler(काष्ठा evbuf_header *evbuf)
अणु
	काष्ठा gds_vector *v;
	काष्ठा gds_subvector *sv, *netid, *cpc;
	माप_प्रकार size;

	/* Find the 0x9f00 block. */
	v = sclp_find_gds_vector(evbuf + 1, (व्योम *) evbuf + evbuf->length,
				 0x9f00);
	अगर (!v)
		वापस;
	/* Find the 0x9f22 block inside the 0x9f00 block. */
	v = sclp_find_gds_vector(v + 1, (व्योम *) v + v->length, 0x9f22);
	अगर (!v)
		वापस;
	/* Find the 0x81 block inside the 0x9f22 block. */
	sv = sclp_find_gds_subvector(v + 1, (व्योम *) v + v->length, 0x81);
	अगर (!sv)
		वापस;
	/* Find the 0x01 block inside the 0x81 block. */
	netid = sclp_find_gds_subvector(sv + 1, (व्योम *) sv + sv->length, 1);
	/* Find the 0x02 block inside the 0x81 block. */
	cpc = sclp_find_gds_subvector(sv + 1, (व्योम *) sv + sv->length, 2);
	/* Copy network name and cpc name. */
	spin_lock(&sclp_ocf_lock);
	अगर (netid) अणु
		size = min(OCF_LENGTH_HMC_NETWORK, (माप_प्रकार) netid->length);
		स_नकल(hmc_network, netid + 1, size);
		EBCASC(hmc_network, size);
		hmc_network[size] = 0;
	पूर्ण
	अगर (cpc) अणु
		size = min(OCF_LENGTH_CPC_NAME, (माप_प्रकार) cpc->length);
		स_रखो(cpc_name, 0, OCF_LENGTH_CPC_NAME);
		स_नकल(cpc_name, cpc + 1, size);
	पूर्ण
	spin_unlock(&sclp_ocf_lock);
	schedule_work(&sclp_ocf_change_work);
पूर्ण

अटल काष्ठा sclp_रेजिस्टर sclp_ocf_event = अणु
	.receive_mask = EVTYP_OCF_MASK,
	.receiver_fn = sclp_ocf_handler,
पूर्ण;

व्योम sclp_ocf_cpc_name_copy(अक्षर *dst)
अणु
	spin_lock_irq(&sclp_ocf_lock);
	स_नकल(dst, cpc_name, OCF_LENGTH_CPC_NAME);
	spin_unlock_irq(&sclp_ocf_lock);
पूर्ण
EXPORT_SYMBOL(sclp_ocf_cpc_name_copy);

अटल sमाप_प्रकार cpc_name_show(काष्ठा kobject *kobj,
			     काष्ठा kobj_attribute *attr, अक्षर *page)
अणु
	अक्षर name[OCF_LENGTH_CPC_NAME + 1];

	sclp_ocf_cpc_name_copy(name);
	name[OCF_LENGTH_CPC_NAME] = 0;
	EBCASC(name, OCF_LENGTH_CPC_NAME);
	वापस snम_लिखो(page, PAGE_SIZE, "%s\n", name);
पूर्ण

अटल काष्ठा kobj_attribute cpc_name_attr =
	__ATTR(cpc_name, 0444, cpc_name_show, शून्य);

अटल sमाप_प्रकार hmc_network_show(काष्ठा kobject *kobj,
				काष्ठा kobj_attribute *attr, अक्षर *page)
अणु
	पूर्णांक rc;

	spin_lock_irq(&sclp_ocf_lock);
	rc = snम_लिखो(page, PAGE_SIZE, "%s\n", hmc_network);
	spin_unlock_irq(&sclp_ocf_lock);
	वापस rc;
पूर्ण

अटल काष्ठा kobj_attribute hmc_network_attr =
	__ATTR(hmc_network, 0444, hmc_network_show, शून्य);

अटल काष्ठा attribute *ocf_attrs[] = अणु
	&cpc_name_attr.attr,
	&hmc_network_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group ocf_attr_group = अणु
	.attrs = ocf_attrs,
पूर्ण;

अटल पूर्णांक __init ocf_init(व्योम)
अणु
	पूर्णांक rc;

	INIT_WORK(&sclp_ocf_change_work, sclp_ocf_change_notअगरy);
	ocf_kset = kset_create_and_add("ocf", शून्य, firmware_kobj);
	अगर (!ocf_kset)
		वापस -ENOMEM;

	rc = sysfs_create_group(&ocf_kset->kobj, &ocf_attr_group);
	अगर (rc) अणु
		kset_unरेजिस्टर(ocf_kset);
		वापस rc;
	पूर्ण

	वापस sclp_रेजिस्टर(&sclp_ocf_event);
पूर्ण

device_initcall(ocf_init);
