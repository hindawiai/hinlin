<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *    Copyright IBM Corp. 2007
 *    Author(s): Heiko Carstens <heiko.carstens@de.ibm.com>
 */

#घोषणा KMSG_COMPONENT "sclp_config"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/cpu.h>
#समावेश <linux/device.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/slab.h>
#समावेश <linux/sysfs.h>
#समावेश <यंत्र/smp.h>

#समावेश "sclp.h"

काष्ठा conf_mgm_data अणु
	u8 reserved;
	u8 ev_qualअगरier;
पूर्ण __attribute__((packed));

#घोषणा OFB_DATA_MAX 64

काष्ठा sclp_ofb_evbuf अणु
	काष्ठा evbuf_header header;
	काष्ठा conf_mgm_data cm_data;
	अक्षर ev_data[OFB_DATA_MAX];
पूर्ण __packed;

काष्ठा sclp_ofb_sccb अणु
	काष्ठा sccb_header header;
	काष्ठा sclp_ofb_evbuf ofb_evbuf;
पूर्ण __packed;

#घोषणा EV_QUAL_CPU_CHANGE	1
#घोषणा EV_QUAL_CAP_CHANGE	3
#घोषणा EV_QUAL_OPEN4BUSINESS	5

अटल काष्ठा work_काष्ठा sclp_cpu_capability_work;
अटल काष्ठा work_काष्ठा sclp_cpu_change_work;

अटल व्योम sclp_cpu_capability_notअगरy(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक cpu;
	काष्ठा device *dev;

	s390_update_cpu_mhz();
	pr_info("CPU capability may have changed\n");
	get_online_cpus();
	क्रम_each_online_cpu(cpu) अणु
		dev = get_cpu_device(cpu);
		kobject_uevent(&dev->kobj, KOBJ_CHANGE);
	पूर्ण
	put_online_cpus();
पूर्ण

अटल व्योम __ref sclp_cpu_change_notअगरy(काष्ठा work_काष्ठा *work)
अणु
	lock_device_hotplug();
	smp_rescan_cpus();
	unlock_device_hotplug();
पूर्ण

अटल व्योम sclp_conf_receiver_fn(काष्ठा evbuf_header *evbuf)
अणु
	काष्ठा conf_mgm_data *cdata;

	cdata = (काष्ठा conf_mgm_data *)(evbuf + 1);
	चयन (cdata->ev_qualअगरier) अणु
	हाल EV_QUAL_CPU_CHANGE:
		schedule_work(&sclp_cpu_change_work);
		अवरोध;
	हाल EV_QUAL_CAP_CHANGE:
		schedule_work(&sclp_cpu_capability_work);
		अवरोध;
	पूर्ण
पूर्ण

अटल काष्ठा sclp_रेजिस्टर sclp_conf_रेजिस्टर =
अणु
#अगर_घोषित CONFIG_SCLP_OFB
	.send_mask    = EVTYP_CONFMGMDATA_MASK,
#पूर्ण_अगर
	.receive_mask = EVTYP_CONFMGMDATA_MASK,
	.receiver_fn  = sclp_conf_receiver_fn,
पूर्ण;

#अगर_घोषित CONFIG_SCLP_OFB
अटल पूर्णांक sclp_ofb_send_req(अक्षर *ev_data, माप_प्रकार len)
अणु
	अटल DEFINE_MUTEX(send_mutex);
	काष्ठा sclp_ofb_sccb *sccb;
	पूर्णांक rc, response;

	अगर (len > OFB_DATA_MAX)
		वापस -EINVAL;
	sccb = (काष्ठा sclp_ofb_sccb *) get_zeroed_page(GFP_KERNEL | GFP_DMA);
	अगर (!sccb)
		वापस -ENOMEM;
	/* Setup SCCB क्रम Control-Program Identअगरication */
	sccb->header.length = माप(काष्ठा sclp_ofb_sccb);
	sccb->ofb_evbuf.header.length = माप(काष्ठा sclp_ofb_evbuf);
	sccb->ofb_evbuf.header.type = EVTYP_CONFMGMDATA;
	sccb->ofb_evbuf.cm_data.ev_qualअगरier = EV_QUAL_OPEN4BUSINESS;
	स_नकल(sccb->ofb_evbuf.ev_data, ev_data, len);

	अगर (!(sclp_conf_रेजिस्टर.sclp_receive_mask & EVTYP_CONFMGMDATA_MASK))
		pr_warn("SCLP receiver did not register to receive "
			"Configuration Management Data Events.\n");

	mutex_lock(&send_mutex);
	rc = sclp_sync_request(SCLP_CMDW_WRITE_EVENT_DATA, sccb);
	mutex_unlock(&send_mutex);
	अगर (rc)
		जाओ out;
	response = sccb->header.response_code;
	अगर (response != 0x0020) अणु
		pr_err("Open for Business request failed with response code "
		       "0x%04x\n", response);
		rc = -EIO;
	पूर्ण
out:
	मुक्त_page((अचिन्हित दीर्घ)sccb);
	वापस rc;
पूर्ण

अटल sमाप_प्रकार sysfs_ofb_data_ग_लिखो(काष्ठा file *filp, काष्ठा kobject *kobj,
				    काष्ठा bin_attribute *bin_attr,
				    अक्षर *buf, loff_t off, माप_प्रकार count)
अणु
	पूर्णांक rc;

	rc = sclp_ofb_send_req(buf, count);
	वापस rc ?: count;
पूर्ण

अटल स्थिर काष्ठा bin_attribute ofb_bin_attr = अणु
	.attr = अणु
		.name = "event_data",
		.mode = S_IWUSR,
	पूर्ण,
	.ग_लिखो = sysfs_ofb_data_ग_लिखो,
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक __init sclp_ofb_setup(व्योम)
अणु
#अगर_घोषित CONFIG_SCLP_OFB
	काष्ठा kset *ofb_kset;
	पूर्णांक rc;

	ofb_kset = kset_create_and_add("ofb", शून्य, firmware_kobj);
	अगर (!ofb_kset)
		वापस -ENOMEM;
	rc = sysfs_create_bin_file(&ofb_kset->kobj, &ofb_bin_attr);
	अगर (rc) अणु
		kset_unरेजिस्टर(ofb_kset);
		वापस rc;
	पूर्ण
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल पूर्णांक __init sclp_conf_init(व्योम)
अणु
	पूर्णांक rc;

	INIT_WORK(&sclp_cpu_capability_work, sclp_cpu_capability_notअगरy);
	INIT_WORK(&sclp_cpu_change_work, sclp_cpu_change_notअगरy);
	rc = sclp_रेजिस्टर(&sclp_conf_रेजिस्टर);
	अगर (rc)
		वापस rc;
	वापस sclp_ofb_setup();
पूर्ण

__initcall(sclp_conf_init);
