<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *    Copyright IBM Corp. 1999, 2010
 *    Author(s): Cornelia Huck (cornelia.huck@de.ibm.com)
 *		 Arnd Bergmann (arndb@de.ibm.com)
 *		 Peter Oberparleiter <peter.oberparleiter@de.ibm.com>
 */

#समावेश <linux/bug.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/export.h>
#समावेश <linux/sched.h>
#समावेश <linux/init.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/रुको.h>
#समावेश <linux/mutex.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <यंत्र/chpid.h>
#समावेश <यंत्र/sclp.h>
#समावेश <यंत्र/crw.h>

#समावेश "cio.h"
#समावेश "css.h"
#समावेश "ioasm.h"
#समावेश "cio_debug.h"
#समावेश "chp.h"

#घोषणा to_channelpath(device) container_of(device, काष्ठा channel_path, dev)
#घोषणा CHP_INFO_UPDATE_INTERVAL	1*HZ

क्रमागत cfg_task_t अणु
	cfg_none,
	cfg_configure,
	cfg_deconfigure
पूर्ण;

/* Map क्रम pending configure tasks. */
अटल क्रमागत cfg_task_t chp_cfg_task[__MAX_CSSID + 1][__MAX_CHPID + 1];
अटल DEFINE_SPINLOCK(cfg_lock);

/* Map क्रम channel-path status. */
अटल काष्ठा sclp_chp_info chp_info;
अटल DEFINE_MUTEX(info_lock);

/* Time after which channel-path status may be outdated. */
अटल अचिन्हित दीर्घ chp_info_expires;

अटल काष्ठा work_काष्ठा cfg_work;

/* Wait queue क्रम configure completion events. */
अटल DECLARE_WAIT_QUEUE_HEAD(cfg_रुको_queue);

/* Set vary state क्रम given chpid. */
अटल व्योम set_chp_logically_online(काष्ठा chp_id chpid, पूर्णांक onoff)
अणु
	chpid_to_chp(chpid)->state = onoff;
पूर्ण

/* On success वापस 0 अगर channel-path is varied offline, 1 अगर it is varied
 * online. Return -ENODEV अगर channel-path is not रेजिस्टरed. */
पूर्णांक chp_get_status(काष्ठा chp_id chpid)
अणु
	वापस (chpid_to_chp(chpid) ? chpid_to_chp(chpid)->state : -ENODEV);
पूर्ण

/**
 * chp_get_sch_opm - वापस opm क्रम subchannel
 * @sch: subchannel
 *
 * Calculate and वापस the operational path mask (opm) based on the chpids
 * used by the subchannel and the status of the associated channel-paths.
 */
u8 chp_get_sch_opm(काष्ठा subchannel *sch)
अणु
	काष्ठा chp_id chpid;
	पूर्णांक opm;
	पूर्णांक i;

	opm = 0;
	chp_id_init(&chpid);
	क्रम (i = 0; i < 8; i++) अणु
		opm <<= 1;
		chpid.id = sch->schib.pmcw.chpid[i];
		अगर (chp_get_status(chpid) != 0)
			opm |= 1;
	पूर्ण
	वापस opm;
पूर्ण
EXPORT_SYMBOL_GPL(chp_get_sch_opm);

/**
 * chp_is_रेजिस्टरed - check अगर a channel-path is रेजिस्टरed
 * @chpid: channel-path ID
 *
 * Return non-zero अगर a channel-path with the given chpid is रेजिस्टरed,
 * zero otherwise.
 */
पूर्णांक chp_is_रेजिस्टरed(काष्ठा chp_id chpid)
अणु
	वापस chpid_to_chp(chpid) != शून्य;
पूर्ण

/*
 * Function: s390_vary_chpid
 * Varies the specअगरied chpid online or offline
 */
अटल पूर्णांक s390_vary_chpid(काष्ठा chp_id chpid, पूर्णांक on)
अणु
	अक्षर dbf_text[15];
	पूर्णांक status;

	प्र_लिखो(dbf_text, on?"varyon%x.%02x":"varyoff%x.%02x", chpid.cssid,
		chpid.id);
	CIO_TRACE_EVENT(2, dbf_text);

	status = chp_get_status(chpid);
	अगर (!on && !status)
		वापस 0;

	set_chp_logically_online(chpid, on);
	chsc_chp_vary(chpid, on);
	वापस 0;
पूर्ण

/*
 * Channel measurement related functions
 */
अटल sमाप_प्रकार chp_measurement_अक्षरs_पढ़ो(काष्ठा file *filp,
					  काष्ठा kobject *kobj,
					  काष्ठा bin_attribute *bin_attr,
					  अक्षर *buf, loff_t off, माप_प्रकार count)
अणु
	काष्ठा channel_path *chp;
	काष्ठा device *device;

	device = kobj_to_dev(kobj);
	chp = to_channelpath(device);
	अगर (chp->cmg == -1)
		वापस 0;

	वापस memory_पढ़ो_from_buffer(buf, count, &off, &chp->cmg_अक्षरs,
				       माप(chp->cmg_अक्षरs));
पूर्ण

अटल स्थिर काष्ठा bin_attribute chp_measurement_अक्षरs_attr = अणु
	.attr = अणु
		.name = "measurement_chars",
		.mode = S_IRUSR,
	पूर्ण,
	.size = माप(काष्ठा cmg_अक्षरs),
	.पढ़ो = chp_measurement_अक्षरs_पढ़ो,
पूर्ण;

अटल व्योम chp_measurement_copy_block(काष्ठा cmg_entry *buf,
				       काष्ठा channel_subप्रणाली *css,
				       काष्ठा chp_id chpid)
अणु
	व्योम *area;
	काष्ठा cmg_entry *entry, reference_buf;
	पूर्णांक idx;

	अगर (chpid.id < 128) अणु
		area = css->cub_addr1;
		idx = chpid.id;
	पूर्ण अन्यथा अणु
		area = css->cub_addr2;
		idx = chpid.id - 128;
	पूर्ण
	entry = area + (idx * माप(काष्ठा cmg_entry));
	करो अणु
		स_नकल(buf, entry, माप(*entry));
		स_नकल(&reference_buf, entry, माप(*entry));
	पूर्ण जबतक (reference_buf.values[0] != buf->values[0]);
पूर्ण

अटल sमाप_प्रकार chp_measurement_पढ़ो(काष्ठा file *filp, काष्ठा kobject *kobj,
				    काष्ठा bin_attribute *bin_attr,
				    अक्षर *buf, loff_t off, माप_प्रकार count)
अणु
	काष्ठा channel_path *chp;
	काष्ठा channel_subप्रणाली *css;
	काष्ठा device *device;
	अचिन्हित पूर्णांक size;

	device = kobj_to_dev(kobj);
	chp = to_channelpath(device);
	css = to_css(chp->dev.parent);

	size = माप(काष्ठा cmg_entry);

	/* Only allow single पढ़ोs. */
	अगर (off || count < size)
		वापस 0;
	chp_measurement_copy_block((काष्ठा cmg_entry *)buf, css, chp->chpid);
	count = size;
	वापस count;
पूर्ण

अटल स्थिर काष्ठा bin_attribute chp_measurement_attr = अणु
	.attr = अणु
		.name = "measurement",
		.mode = S_IRUSR,
	पूर्ण,
	.size = माप(काष्ठा cmg_entry),
	.पढ़ो = chp_measurement_पढ़ो,
पूर्ण;

व्योम chp_हटाओ_cmg_attr(काष्ठा channel_path *chp)
अणु
	device_हटाओ_bin_file(&chp->dev, &chp_measurement_अक्षरs_attr);
	device_हटाओ_bin_file(&chp->dev, &chp_measurement_attr);
पूर्ण

पूर्णांक chp_add_cmg_attr(काष्ठा channel_path *chp)
अणु
	पूर्णांक ret;

	ret = device_create_bin_file(&chp->dev, &chp_measurement_अक्षरs_attr);
	अगर (ret)
		वापस ret;
	ret = device_create_bin_file(&chp->dev, &chp_measurement_attr);
	अगर (ret)
		device_हटाओ_bin_file(&chp->dev, &chp_measurement_अक्षरs_attr);
	वापस ret;
पूर्ण

/*
 * Files क्रम the channel path entries.
 */
अटल sमाप_प्रकार chp_status_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा channel_path *chp = to_channelpath(dev);
	पूर्णांक status;

	mutex_lock(&chp->lock);
	status = chp->state;
	mutex_unlock(&chp->lock);

	वापस status ? प्र_लिखो(buf, "online\n") : प्र_लिखो(buf, "offline\n");
पूर्ण

अटल sमाप_प्रकार chp_status_ग_लिखो(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा channel_path *cp = to_channelpath(dev);
	अक्षर cmd[10];
	पूर्णांक num_args;
	पूर्णांक error;

	num_args = माला_पूछो(buf, "%5s", cmd);
	अगर (!num_args)
		वापस count;

	अगर (!strnहालcmp(cmd, "on", 2) || !म_भेद(cmd, "1")) अणु
		mutex_lock(&cp->lock);
		error = s390_vary_chpid(cp->chpid, 1);
		mutex_unlock(&cp->lock);
	पूर्ण अन्यथा अगर (!strnहालcmp(cmd, "off", 3) || !म_भेद(cmd, "0")) अणु
		mutex_lock(&cp->lock);
		error = s390_vary_chpid(cp->chpid, 0);
		mutex_unlock(&cp->lock);
	पूर्ण अन्यथा
		error = -EINVAL;

	वापस error < 0 ? error : count;
पूर्ण

अटल DEVICE_ATTR(status, 0644, chp_status_show, chp_status_ग_लिखो);

अटल sमाप_प्रकार chp_configure_show(काष्ठा device *dev,
				  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा channel_path *cp;
	पूर्णांक status;

	cp = to_channelpath(dev);
	status = chp_info_get_status(cp->chpid);
	अगर (status < 0)
		वापस status;

	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", status);
पूर्ण

अटल पूर्णांक cfg_रुको_idle(व्योम);

अटल sमाप_प्रकार chp_configure_ग_लिखो(काष्ठा device *dev,
				   काष्ठा device_attribute *attr,
				   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा channel_path *cp;
	पूर्णांक val;
	अक्षर delim;

	अगर (माला_पूछो(buf, "%d %c", &val, &delim) != 1)
		वापस -EINVAL;
	अगर (val != 0 && val != 1)
		वापस -EINVAL;
	cp = to_channelpath(dev);
	chp_cfg_schedule(cp->chpid, val);
	cfg_रुको_idle();

	वापस count;
पूर्ण

अटल DEVICE_ATTR(configure, 0644, chp_configure_show, chp_configure_ग_लिखो);

अटल sमाप_प्रकार chp_type_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा channel_path *chp = to_channelpath(dev);
	u8 type;

	mutex_lock(&chp->lock);
	type = chp->desc.desc;
	mutex_unlock(&chp->lock);
	वापस प्र_लिखो(buf, "%x\n", type);
पूर्ण

अटल DEVICE_ATTR(type, 0444, chp_type_show, शून्य);

अटल sमाप_प्रकार chp_cmg_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	काष्ठा channel_path *chp = to_channelpath(dev);

	अगर (!chp)
		वापस 0;
	अगर (chp->cmg == -1) /* channel measurements not available */
		वापस प्र_लिखो(buf, "unknown\n");
	वापस प्र_लिखो(buf, "%x\n", chp->cmg);
पूर्ण

अटल DEVICE_ATTR(cmg, 0444, chp_cmg_show, शून्य);

अटल sमाप_प्रकार chp_shared_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा channel_path *chp = to_channelpath(dev);

	अगर (!chp)
		वापस 0;
	अगर (chp->shared == -1) /* channel measurements not available */
		वापस प्र_लिखो(buf, "unknown\n");
	वापस प्र_लिखो(buf, "%x\n", chp->shared);
पूर्ण

अटल DEVICE_ATTR(shared, 0444, chp_shared_show, शून्य);

अटल sमाप_प्रकार chp_chid_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा channel_path *chp = to_channelpath(dev);
	sमाप_प्रकार rc;

	mutex_lock(&chp->lock);
	अगर (chp->desc_fmt1.flags & 0x10)
		rc = प्र_लिखो(buf, "%04x\n", chp->desc_fmt1.chid);
	अन्यथा
		rc = 0;
	mutex_unlock(&chp->lock);

	वापस rc;
पूर्ण
अटल DEVICE_ATTR(chid, 0444, chp_chid_show, शून्य);

अटल sमाप_प्रकार chp_chid_बाह्यal_show(काष्ठा device *dev,
				      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा channel_path *chp = to_channelpath(dev);
	sमाप_प्रकार rc;

	mutex_lock(&chp->lock);
	अगर (chp->desc_fmt1.flags & 0x10)
		rc = प्र_लिखो(buf, "%x\n", chp->desc_fmt1.flags & 0x8 ? 1 : 0);
	अन्यथा
		rc = 0;
	mutex_unlock(&chp->lock);

	वापस rc;
पूर्ण
अटल DEVICE_ATTR(chid_बाह्यal, 0444, chp_chid_बाह्यal_show, शून्य);

अटल sमाप_प्रकार chp_esc_show(काष्ठा device *dev,
			    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा channel_path *chp = to_channelpath(dev);
	sमाप_प्रकार rc;

	mutex_lock(&chp->lock);
	rc = प्र_लिखो(buf, "%x\n", chp->desc_fmt1.esc);
	mutex_unlock(&chp->lock);

	वापस rc;
पूर्ण
अटल DEVICE_ATTR(esc, 0444, chp_esc_show, शून्य);

अटल sमाप_प्रकार util_string_पढ़ो(काष्ठा file *filp, काष्ठा kobject *kobj,
				काष्ठा bin_attribute *attr, अक्षर *buf,
				loff_t off, माप_प्रकार count)
अणु
	काष्ठा channel_path *chp = to_channelpath(kobj_to_dev(kobj));
	sमाप_प्रकार rc;

	mutex_lock(&chp->lock);
	rc = memory_पढ़ो_from_buffer(buf, count, &off, chp->desc_fmt3.util_str,
				     माप(chp->desc_fmt3.util_str));
	mutex_unlock(&chp->lock);

	वापस rc;
पूर्ण
अटल BIN_ATTR_RO(util_string,
		   माप(((काष्ठा channel_path_desc_fmt3 *)0)->util_str));

अटल काष्ठा bin_attribute *chp_bin_attrs[] = अणु
	&bin_attr_util_string,
	शून्य,
पूर्ण;

अटल काष्ठा attribute *chp_attrs[] = अणु
	&dev_attr_status.attr,
	&dev_attr_configure.attr,
	&dev_attr_type.attr,
	&dev_attr_cmg.attr,
	&dev_attr_shared.attr,
	&dev_attr_chid.attr,
	&dev_attr_chid_बाह्यal.attr,
	&dev_attr_esc.attr,
	शून्य,
पूर्ण;
अटल काष्ठा attribute_group chp_attr_group = अणु
	.attrs = chp_attrs,
	.bin_attrs = chp_bin_attrs,
पूर्ण;
अटल स्थिर काष्ठा attribute_group *chp_attr_groups[] = अणु
	&chp_attr_group,
	शून्य,
पूर्ण;

अटल व्योम chp_release(काष्ठा device *dev)
अणु
	काष्ठा channel_path *cp;

	cp = to_channelpath(dev);
	kमुक्त(cp);
पूर्ण

/**
 * chp_update_desc - update channel-path description
 * @chp: channel-path
 *
 * Update the channel-path description of the specअगरied channel-path
 * including channel measurement related inक्रमmation.
 * Return zero on success, non-zero otherwise.
 */
पूर्णांक chp_update_desc(काष्ठा channel_path *chp)
अणु
	पूर्णांक rc;

	rc = chsc_determine_fmt0_channel_path_desc(chp->chpid, &chp->desc);
	अगर (rc)
		वापस rc;

	/*
	 * Fetching the following data is optional. Not all machines or
	 * hypervisors implement the required chsc commands.
	 */
	chsc_determine_fmt1_channel_path_desc(chp->chpid, &chp->desc_fmt1);
	chsc_determine_fmt3_channel_path_desc(chp->chpid, &chp->desc_fmt3);
	chsc_get_channel_measurement_अक्षरs(chp);

	वापस 0;
पूर्ण

/**
 * chp_new - रेजिस्टर a new channel-path
 * @chpid: channel-path ID
 *
 * Create and रेजिस्टर data काष्ठाure representing new channel-path. Return
 * zero on success, non-zero otherwise.
 */
पूर्णांक chp_new(काष्ठा chp_id chpid)
अणु
	काष्ठा channel_subप्रणाली *css = css_by_id(chpid.cssid);
	काष्ठा channel_path *chp;
	पूर्णांक ret = 0;

	mutex_lock(&css->mutex);
	अगर (chp_is_रेजिस्टरed(chpid))
		जाओ out;

	chp = kzalloc(माप(काष्ठा channel_path), GFP_KERNEL);
	अगर (!chp) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	/* fill in status, etc. */
	chp->chpid = chpid;
	chp->state = 1;
	chp->dev.parent = &css->device;
	chp->dev.groups = chp_attr_groups;
	chp->dev.release = chp_release;
	mutex_init(&chp->lock);

	/* Obtain channel path description and fill it in. */
	ret = chp_update_desc(chp);
	अगर (ret)
		जाओ out_मुक्त;
	अगर ((chp->desc.flags & 0x80) == 0) अणु
		ret = -ENODEV;
		जाओ out_मुक्त;
	पूर्ण
	dev_set_name(&chp->dev, "chp%x.%02x", chpid.cssid, chpid.id);

	/* make it known to the प्रणाली */
	ret = device_रेजिस्टर(&chp->dev);
	अगर (ret) अणु
		CIO_MSG_EVENT(0, "Could not register chp%x.%02x: %d\n",
			      chpid.cssid, chpid.id, ret);
		put_device(&chp->dev);
		जाओ out;
	पूर्ण

	अगर (css->cm_enabled) अणु
		ret = chp_add_cmg_attr(chp);
		अगर (ret) अणु
			device_unरेजिस्टर(&chp->dev);
			जाओ out;
		पूर्ण
	पूर्ण
	css->chps[chpid.id] = chp;
	जाओ out;
out_मुक्त:
	kमुक्त(chp);
out:
	mutex_unlock(&css->mutex);
	वापस ret;
पूर्ण

/**
 * chp_get_chp_desc - वापस newly allocated channel-path description
 * @chpid: channel-path ID
 *
 * On success वापस a newly allocated copy of the channel-path description
 * data associated with the given channel-path ID. Return %शून्य on error.
 */
काष्ठा channel_path_desc_fmt0 *chp_get_chp_desc(काष्ठा chp_id chpid)
अणु
	काष्ठा channel_path *chp;
	काष्ठा channel_path_desc_fmt0 *desc;

	chp = chpid_to_chp(chpid);
	अगर (!chp)
		वापस शून्य;
	desc = kदो_स्मृति(माप(*desc), GFP_KERNEL);
	अगर (!desc)
		वापस शून्य;

	mutex_lock(&chp->lock);
	स_नकल(desc, &chp->desc, माप(*desc));
	mutex_unlock(&chp->lock);
	वापस desc;
पूर्ण

/**
 * chp_process_crw - process channel-path status change
 * @crw0: channel report-word to handler
 * @crw1: second channel-report word (always शून्य)
 * @overflow: crw overflow indication
 *
 * Handle channel-report-words indicating that the status of a channel-path
 * has changed.
 */
अटल व्योम chp_process_crw(काष्ठा crw *crw0, काष्ठा crw *crw1,
			    पूर्णांक overflow)
अणु
	काष्ठा chp_id chpid;

	अगर (overflow) अणु
		css_schedule_eval_all();
		वापस;
	पूर्ण
	CIO_CRW_EVENT(2, "CRW reports slct=%d, oflw=%d, "
		      "chn=%d, rsc=%X, anc=%d, erc=%X, rsid=%X\n",
		      crw0->slct, crw0->oflw, crw0->chn, crw0->rsc, crw0->anc,
		      crw0->erc, crw0->rsid);
	/*
	 * Check क्रम solicited machine checks. These are
	 * created by reset channel path and need not be
	 * handled here.
	 */
	अगर (crw0->slct) अणु
		CIO_CRW_EVENT(2, "solicited machine check for "
			      "channel path %02X\n", crw0->rsid);
		वापस;
	पूर्ण
	chp_id_init(&chpid);
	chpid.id = crw0->rsid;
	चयन (crw0->erc) अणु
	हाल CRW_ERC_IPARM: /* Path has come. */
	हाल CRW_ERC_INIT:
		chp_new(chpid);
		chsc_chp_online(chpid);
		अवरोध;
	हाल CRW_ERC_PERRI: /* Path has gone. */
	हाल CRW_ERC_PERRN:
		chsc_chp_offline(chpid);
		अवरोध;
	शेष:
		CIO_CRW_EVENT(2, "Don't know how to handle erc=%x\n",
			      crw0->erc);
	पूर्ण
पूर्ण

पूर्णांक chp_ssd_get_mask(काष्ठा chsc_ssd_info *ssd, काष्ठा chp_link *link)
अणु
	पूर्णांक i;
	पूर्णांक mask;

	क्रम (i = 0; i < 8; i++) अणु
		mask = 0x80 >> i;
		अगर (!(ssd->path_mask & mask))
			जारी;
		अगर (!chp_id_is_equal(&ssd->chpid[i], &link->chpid))
			जारी;
		अगर ((ssd->fla_valid_mask & mask) &&
		    ((ssd->fla[i] & link->fla_mask) != link->fla))
			जारी;
		वापस mask;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(chp_ssd_get_mask);

अटल अंतरभूत पूर्णांक info_bit_num(काष्ठा chp_id id)
अणु
	वापस id.id + id.cssid * (__MAX_CHPID + 1);
पूर्ण

/* Force chp_info refresh on next call to info_validate(). */
अटल व्योम info_expire(व्योम)
अणु
	mutex_lock(&info_lock);
	chp_info_expires = jअगरfies - 1;
	mutex_unlock(&info_lock);
पूर्ण

/* Ensure that chp_info is up-to-date. */
अटल पूर्णांक info_update(व्योम)
अणु
	पूर्णांक rc;

	mutex_lock(&info_lock);
	rc = 0;
	अगर (समय_after(jअगरfies, chp_info_expires)) अणु
		/* Data is too old, update. */
		rc = sclp_chp_पढ़ो_info(&chp_info);
		chp_info_expires = jअगरfies + CHP_INFO_UPDATE_INTERVAL ;
	पूर्ण
	mutex_unlock(&info_lock);

	वापस rc;
पूर्ण

/**
 * chp_info_get_status - retrieve configure status of a channel-path
 * @chpid: channel-path ID
 *
 * On success, वापस 0 क्रम standby, 1 क्रम configured, 2 क्रम reserved,
 * 3 क्रम not recognized. Return negative error code on error.
 */
पूर्णांक chp_info_get_status(काष्ठा chp_id chpid)
अणु
	पूर्णांक rc;
	पूर्णांक bit;

	rc = info_update();
	अगर (rc)
		वापस rc;

	bit = info_bit_num(chpid);
	mutex_lock(&info_lock);
	अगर (!chp_test_bit(chp_info.recognized, bit))
		rc = CHP_STATUS_NOT_RECOGNIZED;
	अन्यथा अगर (chp_test_bit(chp_info.configured, bit))
		rc = CHP_STATUS_CONFIGURED;
	अन्यथा अगर (chp_test_bit(chp_info.standby, bit))
		rc = CHP_STATUS_STANDBY;
	अन्यथा
		rc = CHP_STATUS_RESERVED;
	mutex_unlock(&info_lock);

	वापस rc;
पूर्ण

/* Return configure task क्रम chpid. */
अटल क्रमागत cfg_task_t cfg_get_task(काष्ठा chp_id chpid)
अणु
	वापस chp_cfg_task[chpid.cssid][chpid.id];
पूर्ण

/* Set configure task क्रम chpid. */
अटल व्योम cfg_set_task(काष्ठा chp_id chpid, क्रमागत cfg_task_t cfg)
अणु
	chp_cfg_task[chpid.cssid][chpid.id] = cfg;
पूर्ण

/* Fetch the first configure task. Set chpid accordingly. */
अटल क्रमागत cfg_task_t chp_cfg_fetch_task(काष्ठा chp_id *chpid)
अणु
	क्रमागत cfg_task_t t = cfg_none;

	chp_id_क्रम_each(chpid) अणु
		t = cfg_get_task(*chpid);
		अगर (t != cfg_none)
			अवरोध;
	पूर्ण

	वापस t;
पूर्ण

/* Perक्रमm one configure/deconfigure request. Reschedule work function until
 * last request. */
अटल व्योम cfg_func(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा chp_id chpid;
	क्रमागत cfg_task_t t;
	पूर्णांक rc;

	spin_lock(&cfg_lock);
	t = chp_cfg_fetch_task(&chpid);
	spin_unlock(&cfg_lock);

	चयन (t) अणु
	हाल cfg_configure:
		rc = sclp_chp_configure(chpid);
		अगर (rc)
			CIO_MSG_EVENT(2, "chp: sclp_chp_configure(%x.%02x)="
				      "%d\n", chpid.cssid, chpid.id, rc);
		अन्यथा अणु
			info_expire();
			chsc_chp_online(chpid);
		पूर्ण
		अवरोध;
	हाल cfg_deconfigure:
		rc = sclp_chp_deconfigure(chpid);
		अगर (rc)
			CIO_MSG_EVENT(2, "chp: sclp_chp_deconfigure(%x.%02x)="
				      "%d\n", chpid.cssid, chpid.id, rc);
		अन्यथा अणु
			info_expire();
			chsc_chp_offline(chpid);
		पूर्ण
		अवरोध;
	हाल cfg_none:
		/* Get updated inक्रमmation after last change. */
		info_update();
		wake_up_पूर्णांकerruptible(&cfg_रुको_queue);
		वापस;
	पूर्ण
	spin_lock(&cfg_lock);
	अगर (t == cfg_get_task(chpid))
		cfg_set_task(chpid, cfg_none);
	spin_unlock(&cfg_lock);
	schedule_work(&cfg_work);
पूर्ण

/**
 * chp_cfg_schedule - schedule chpid configuration request
 * @chpid: channel-path ID
 * @configure: Non-zero क्रम configure, zero क्रम deconfigure
 *
 * Schedule a channel-path configuration/deconfiguration request.
 */
व्योम chp_cfg_schedule(काष्ठा chp_id chpid, पूर्णांक configure)
अणु
	CIO_MSG_EVENT(2, "chp_cfg_sched%x.%02x=%d\n", chpid.cssid, chpid.id,
		      configure);
	spin_lock(&cfg_lock);
	cfg_set_task(chpid, configure ? cfg_configure : cfg_deconfigure);
	spin_unlock(&cfg_lock);
	schedule_work(&cfg_work);
पूर्ण

/**
 * chp_cfg_cancel_deconfigure - cancel chpid deconfiguration request
 * @chpid: channel-path ID
 *
 * Cancel an active channel-path deconfiguration request अगर it has not yet
 * been perक्रमmed.
 */
व्योम chp_cfg_cancel_deconfigure(काष्ठा chp_id chpid)
अणु
	CIO_MSG_EVENT(2, "chp_cfg_cancel:%x.%02x\n", chpid.cssid, chpid.id);
	spin_lock(&cfg_lock);
	अगर (cfg_get_task(chpid) == cfg_deconfigure)
		cfg_set_task(chpid, cfg_none);
	spin_unlock(&cfg_lock);
पूर्ण

अटल bool cfg_idle(व्योम)
अणु
	काष्ठा chp_id chpid;
	क्रमागत cfg_task_t t;

	spin_lock(&cfg_lock);
	t = chp_cfg_fetch_task(&chpid);
	spin_unlock(&cfg_lock);

	वापस t == cfg_none;
पूर्ण

अटल पूर्णांक cfg_रुको_idle(व्योम)
अणु
	अगर (रुको_event_पूर्णांकerruptible(cfg_रुको_queue, cfg_idle()))
		वापस -ERESTARTSYS;
	वापस 0;
पूर्ण

अटल पूर्णांक __init chp_init(व्योम)
अणु
	काष्ठा chp_id chpid;
	पूर्णांक state, ret;

	ret = crw_रेजिस्टर_handler(CRW_RSC_CPATH, chp_process_crw);
	अगर (ret)
		वापस ret;
	INIT_WORK(&cfg_work, cfg_func);
	अगर (info_update())
		वापस 0;
	/* Register available channel-paths. */
	chp_id_क्रम_each(&chpid) अणु
		state = chp_info_get_status(chpid);
		अगर (state == CHP_STATUS_CONFIGURED ||
		    state == CHP_STATUS_STANDBY)
			chp_new(chpid);
	पूर्ण

	वापस 0;
पूर्ण

subsys_initcall(chp_init);
