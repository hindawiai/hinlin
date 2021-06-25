<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * driver क्रम channel subप्रणाली
 *
 * Copyright IBM Corp. 2002, 2010
 *
 * Author(s): Arnd Bergmann (arndb@de.ibm.com)
 *	      Cornelia Huck (cornelia.huck@de.ibm.com)
 */

#घोषणा KMSG_COMPONENT "cio"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/export.h>
#समावेश <linux/init.h>
#समावेश <linux/device.h>
#समावेश <linux/slab.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/list.h>
#समावेश <linux/reboot.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/genभाग.स>
#समावेश <linux/dma-mapping.h>
#समावेश <यंत्र/isc.h>
#समावेश <यंत्र/crw.h>

#समावेश "css.h"
#समावेश "cio.h"
#समावेश "blacklist.h"
#समावेश "cio_debug.h"
#समावेश "ioasm.h"
#समावेश "chsc.h"
#समावेश "device.h"
#समावेश "idset.h"
#समावेश "chp.h"

पूर्णांक css_init_करोne = 0;
पूर्णांक max_ssid;

#घोषणा MAX_CSS_IDX 0
काष्ठा channel_subप्रणाली *channel_subप्रणालीs[MAX_CSS_IDX + 1];
अटल काष्ठा bus_type css_bus_type;

पूर्णांक
क्रम_each_subchannel(पूर्णांक(*fn)(काष्ठा subchannel_id, व्योम *), व्योम *data)
अणु
	काष्ठा subchannel_id schid;
	पूर्णांक ret;

	init_subchannel_id(&schid);
	करो अणु
		करो अणु
			ret = fn(schid, data);
			अगर (ret)
				अवरोध;
		पूर्ण जबतक (schid.sch_no++ < __MAX_SUBCHANNEL);
		schid.sch_no = 0;
	पूर्ण जबतक (schid.ssid++ < max_ssid);
	वापस ret;
पूर्ण

काष्ठा cb_data अणु
	व्योम *data;
	काष्ठा idset *set;
	पूर्णांक (*fn_known_sch)(काष्ठा subchannel *, व्योम *);
	पूर्णांक (*fn_unknown_sch)(काष्ठा subchannel_id, व्योम *);
पूर्ण;

अटल पूर्णांक call_fn_known_sch(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा subchannel *sch = to_subchannel(dev);
	काष्ठा cb_data *cb = data;
	पूर्णांक rc = 0;

	अगर (cb->set)
		idset_sch_del(cb->set, sch->schid);
	अगर (cb->fn_known_sch)
		rc = cb->fn_known_sch(sch, cb->data);
	वापस rc;
पूर्ण

अटल पूर्णांक call_fn_unknown_sch(काष्ठा subchannel_id schid, व्योम *data)
अणु
	काष्ठा cb_data *cb = data;
	पूर्णांक rc = 0;

	अगर (idset_sch_contains(cb->set, schid))
		rc = cb->fn_unknown_sch(schid, cb->data);
	वापस rc;
पूर्ण

अटल पूर्णांक call_fn_all_sch(काष्ठा subchannel_id schid, व्योम *data)
अणु
	काष्ठा cb_data *cb = data;
	काष्ठा subchannel *sch;
	पूर्णांक rc = 0;

	sch = get_subchannel_by_schid(schid);
	अगर (sch) अणु
		अगर (cb->fn_known_sch)
			rc = cb->fn_known_sch(sch, cb->data);
		put_device(&sch->dev);
	पूर्ण अन्यथा अणु
		अगर (cb->fn_unknown_sch)
			rc = cb->fn_unknown_sch(schid, cb->data);
	पूर्ण

	वापस rc;
पूर्ण

पूर्णांक क्रम_each_subchannel_staged(पूर्णांक (*fn_known)(काष्ठा subchannel *, व्योम *),
			       पूर्णांक (*fn_unknown)(काष्ठा subchannel_id,
			       व्योम *), व्योम *data)
अणु
	काष्ठा cb_data cb;
	पूर्णांक rc;

	cb.data = data;
	cb.fn_known_sch = fn_known;
	cb.fn_unknown_sch = fn_unknown;

	अगर (fn_known && !fn_unknown) अणु
		/* Skip idset allocation in हाल of known-only loop. */
		cb.set = शून्य;
		वापस bus_क्रम_each_dev(&css_bus_type, शून्य, &cb,
					call_fn_known_sch);
	पूर्ण

	cb.set = idset_sch_new();
	अगर (!cb.set)
		/* fall back to brute क्रमce scanning in हाल of oom */
		वापस क्रम_each_subchannel(call_fn_all_sch, &cb);

	idset_fill(cb.set);

	/* Process रेजिस्टरed subchannels. */
	rc = bus_क्रम_each_dev(&css_bus_type, शून्य, &cb, call_fn_known_sch);
	अगर (rc)
		जाओ out;
	/* Process unरेजिस्टरed subchannels. */
	अगर (fn_unknown)
		rc = क्रम_each_subchannel(call_fn_unknown_sch, &cb);
out:
	idset_मुक्त(cb.set);

	वापस rc;
पूर्ण

अटल व्योम css_sch_toकरो(काष्ठा work_काष्ठा *work);

अटल पूर्णांक css_sch_create_locks(काष्ठा subchannel *sch)
अणु
	sch->lock = kदो_स्मृति(माप(*sch->lock), GFP_KERNEL);
	अगर (!sch->lock)
		वापस -ENOMEM;

	spin_lock_init(sch->lock);
	mutex_init(&sch->reg_mutex);

	वापस 0;
पूर्ण

अटल व्योम css_subchannel_release(काष्ठा device *dev)
अणु
	काष्ठा subchannel *sch = to_subchannel(dev);

	sch->config.पूर्णांकparm = 0;
	cio_commit_config(sch);
	kमुक्त(sch->driver_override);
	kमुक्त(sch->lock);
	kमुक्त(sch);
पूर्ण

अटल पूर्णांक css_validate_subchannel(काष्ठा subchannel_id schid,
				   काष्ठा schib *schib)
अणु
	पूर्णांक err;

	चयन (schib->pmcw.st) अणु
	हाल SUBCHANNEL_TYPE_IO:
	हाल SUBCHANNEL_TYPE_MSG:
		अगर (!css_sch_is_valid(schib))
			err = -ENODEV;
		अन्यथा अगर (is_blacklisted(schid.ssid, schib->pmcw.dev)) अणु
			CIO_MSG_EVENT(6, "Blacklisted device detected "
				      "at devno %04X, subchannel set %x\n",
				      schib->pmcw.dev, schid.ssid);
			err = -ENODEV;
		पूर्ण अन्यथा
			err = 0;
		अवरोध;
	शेष:
		err = 0;
	पूर्ण
	अगर (err)
		जाओ out;

	CIO_MSG_EVENT(4, "Subchannel 0.%x.%04x reports subchannel type %04X\n",
		      schid.ssid, schid.sch_no, schib->pmcw.st);
out:
	वापस err;
पूर्ण

काष्ठा subchannel *css_alloc_subchannel(काष्ठा subchannel_id schid,
					काष्ठा schib *schib)
अणु
	काष्ठा subchannel *sch;
	पूर्णांक ret;

	ret = css_validate_subchannel(schid, schib);
	अगर (ret < 0)
		वापस ERR_PTR(ret);

	sch = kzalloc(माप(*sch), GFP_KERNEL | GFP_DMA);
	अगर (!sch)
		वापस ERR_PTR(-ENOMEM);

	sch->schid = schid;
	sch->schib = *schib;
	sch->st = schib->pmcw.st;

	ret = css_sch_create_locks(sch);
	अगर (ret)
		जाओ err;

	INIT_WORK(&sch->toकरो_work, css_sch_toकरो);
	sch->dev.release = &css_subchannel_release;
	sch->dev.dma_mask = &sch->dma_mask;
	device_initialize(&sch->dev);
	/*
	 * The physical addresses क्रम some of the dma काष्ठाures that can
	 * beदीर्घ to a subchannel need to fit 31 bit width (e.g. ccw).
	 */
	ret = dma_set_coherent_mask(&sch->dev, DMA_BIT_MASK(31));
	अगर (ret)
		जाओ err;
	/*
	 * But we करोn't have such restrictions imposed on the stuff that
	 * is handled by the streaming API.
	 */
	ret = dma_set_mask(&sch->dev, DMA_BIT_MASK(64));
	अगर (ret)
		जाओ err;

	वापस sch;

err:
	kमुक्त(sch);
	वापस ERR_PTR(ret);
पूर्ण

अटल पूर्णांक css_sch_device_रेजिस्टर(काष्ठा subchannel *sch)
अणु
	पूर्णांक ret;

	mutex_lock(&sch->reg_mutex);
	dev_set_name(&sch->dev, "0.%x.%04x", sch->schid.ssid,
		     sch->schid.sch_no);
	ret = device_add(&sch->dev);
	mutex_unlock(&sch->reg_mutex);
	वापस ret;
पूर्ण

/**
 * css_sch_device_unरेजिस्टर - unरेजिस्टर a subchannel
 * @sch: subchannel to be unरेजिस्टरed
 */
व्योम css_sch_device_unरेजिस्टर(काष्ठा subchannel *sch)
अणु
	mutex_lock(&sch->reg_mutex);
	अगर (device_is_रेजिस्टरed(&sch->dev))
		device_unरेजिस्टर(&sch->dev);
	mutex_unlock(&sch->reg_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(css_sch_device_unरेजिस्टर);

अटल व्योम ssd_from_pmcw(काष्ठा chsc_ssd_info *ssd, काष्ठा pmcw *pmcw)
अणु
	पूर्णांक i;
	पूर्णांक mask;

	स_रखो(ssd, 0, माप(काष्ठा chsc_ssd_info));
	ssd->path_mask = pmcw->pim;
	क्रम (i = 0; i < 8; i++) अणु
		mask = 0x80 >> i;
		अगर (pmcw->pim & mask) अणु
			chp_id_init(&ssd->chpid[i]);
			ssd->chpid[i].id = pmcw->chpid[i];
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम ssd_रेजिस्टर_chpids(काष्ठा chsc_ssd_info *ssd)
अणु
	पूर्णांक i;
	पूर्णांक mask;

	क्रम (i = 0; i < 8; i++) अणु
		mask = 0x80 >> i;
		अगर (ssd->path_mask & mask)
			chp_new(ssd->chpid[i]);
	पूर्ण
पूर्ण

व्योम css_update_ssd_info(काष्ठा subchannel *sch)
अणु
	पूर्णांक ret;

	ret = chsc_get_ssd_info(sch->schid, &sch->ssd_info);
	अगर (ret)
		ssd_from_pmcw(&sch->ssd_info, &sch->schib.pmcw);

	ssd_रेजिस्टर_chpids(&sch->ssd_info);
पूर्ण

अटल sमाप_प्रकार type_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा subchannel *sch = to_subchannel(dev);

	वापस प्र_लिखो(buf, "%01x\n", sch->st);
पूर्ण

अटल DEVICE_ATTR_RO(type);

अटल sमाप_प्रकार modalias_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा subchannel *sch = to_subchannel(dev);

	वापस प्र_लिखो(buf, "css:t%01X\n", sch->st);
पूर्ण

अटल DEVICE_ATTR_RO(modalias);

अटल sमाप_प्रकार driver_override_store(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा subchannel *sch = to_subchannel(dev);
	अक्षर *driver_override, *old, *cp;

	/* We need to keep extra room क्रम a newline */
	अगर (count >= (PAGE_SIZE - 1))
		वापस -EINVAL;

	driver_override = kstrndup(buf, count, GFP_KERNEL);
	अगर (!driver_override)
		वापस -ENOMEM;

	cp = म_अक्षर(driver_override, '\n');
	अगर (cp)
		*cp = '\0';

	device_lock(dev);
	old = sch->driver_override;
	अगर (म_माप(driver_override)) अणु
		sch->driver_override = driver_override;
	पूर्ण अन्यथा अणु
		kमुक्त(driver_override);
		sch->driver_override = शून्य;
	पूर्ण
	device_unlock(dev);

	kमुक्त(old);

	वापस count;
पूर्ण

अटल sमाप_प्रकार driver_override_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा subchannel *sch = to_subchannel(dev);
	sमाप_प्रकार len;

	device_lock(dev);
	len = snम_लिखो(buf, PAGE_SIZE, "%s\n", sch->driver_override);
	device_unlock(dev);
	वापस len;
पूर्ण
अटल DEVICE_ATTR_RW(driver_override);

अटल काष्ठा attribute *subch_attrs[] = अणु
	&dev_attr_type.attr,
	&dev_attr_modalias.attr,
	&dev_attr_driver_override.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group subch_attr_group = अणु
	.attrs = subch_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *शेष_subch_attr_groups[] = अणु
	&subch_attr_group,
	शून्य,
पूर्ण;

अटल sमाप_प्रकार chpids_show(काष्ठा device *dev,
			   काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा subchannel *sch = to_subchannel(dev);
	काष्ठा chsc_ssd_info *ssd = &sch->ssd_info;
	sमाप_प्रकार ret = 0;
	पूर्णांक mask;
	पूर्णांक chp;

	क्रम (chp = 0; chp < 8; chp++) अणु
		mask = 0x80 >> chp;
		अगर (ssd->path_mask & mask)
			ret += प्र_लिखो(buf + ret, "%02x ", ssd->chpid[chp].id);
		अन्यथा
			ret += प्र_लिखो(buf + ret, "00 ");
	पूर्ण
	ret += प्र_लिखो(buf + ret, "\n");
	वापस ret;
पूर्ण
अटल DEVICE_ATTR_RO(chpids);

अटल sमाप_प्रकार pimpampom_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	काष्ठा subchannel *sch = to_subchannel(dev);
	काष्ठा pmcw *pmcw = &sch->schib.pmcw;

	वापस प्र_लिखो(buf, "%02x %02x %02x\n",
		       pmcw->pim, pmcw->pam, pmcw->pom);
पूर्ण
अटल DEVICE_ATTR_RO(pimpampom);

अटल काष्ठा attribute *io_subchannel_type_attrs[] = अणु
	&dev_attr_chpids.attr,
	&dev_attr_pimpampom.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(io_subchannel_type);

अटल स्थिर काष्ठा device_type io_subchannel_type = अणु
	.groups = io_subchannel_type_groups,
पूर्ण;

पूर्णांक css_रेजिस्टर_subchannel(काष्ठा subchannel *sch)
अणु
	पूर्णांक ret;

	/* Initialize the subchannel काष्ठाure */
	sch->dev.parent = &channel_subप्रणालीs[0]->device;
	sch->dev.bus = &css_bus_type;
	sch->dev.groups = शेष_subch_attr_groups;

	अगर (sch->st == SUBCHANNEL_TYPE_IO)
		sch->dev.type = &io_subchannel_type;

	/*
	 * We करोn't want to generate uevents for I/O subchannels that don't
	 * have a working ccw device behind them since they will be
	 * unरेजिस्टरed beक्रमe they can be used anyway, so we delay the add
	 * uevent until after device recognition was successful.
	 * Note that we suppress the uevent क्रम all subchannel types;
	 * the subchannel driver can decide itself when it wants to inक्रमm
	 * userspace of its existence.
	 */
	dev_set_uevent_suppress(&sch->dev, 1);
	css_update_ssd_info(sch);
	/* make it known to the प्रणाली */
	ret = css_sch_device_रेजिस्टर(sch);
	अगर (ret) अणु
		CIO_MSG_EVENT(0, "Could not register sch 0.%x.%04x: %d\n",
			      sch->schid.ssid, sch->schid.sch_no, ret);
		वापस ret;
	पूर्ण
	अगर (!sch->driver) अणु
		/*
		 * No driver matched. Generate the uevent now so that
		 * a fitting driver module may be loaded based on the
		 * modalias.
		 */
		dev_set_uevent_suppress(&sch->dev, 0);
		kobject_uevent(&sch->dev.kobj, KOBJ_ADD);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक css_probe_device(काष्ठा subchannel_id schid, काष्ठा schib *schib)
अणु
	काष्ठा subchannel *sch;
	पूर्णांक ret;

	sch = css_alloc_subchannel(schid, schib);
	अगर (IS_ERR(sch))
		वापस PTR_ERR(sch);

	ret = css_रेजिस्टर_subchannel(sch);
	अगर (ret)
		put_device(&sch->dev);

	वापस ret;
पूर्ण

अटल पूर्णांक
check_subchannel(काष्ठा device *dev, स्थिर व्योम *data)
अणु
	काष्ठा subchannel *sch;
	काष्ठा subchannel_id *schid = (व्योम *)data;

	sch = to_subchannel(dev);
	वापस schid_equal(&sch->schid, schid);
पूर्ण

काष्ठा subchannel *
get_subchannel_by_schid(काष्ठा subchannel_id schid)
अणु
	काष्ठा device *dev;

	dev = bus_find_device(&css_bus_type, शून्य,
			      &schid, check_subchannel);

	वापस dev ? to_subchannel(dev) : शून्य;
पूर्ण

/**
 * css_sch_is_valid() - check अगर a subchannel is valid
 * @schib: subchannel inक्रमmation block क्रम the subchannel
 */
पूर्णांक css_sch_is_valid(काष्ठा schib *schib)
अणु
	अगर ((schib->pmcw.st == SUBCHANNEL_TYPE_IO) && !schib->pmcw.dnv)
		वापस 0;
	अगर ((schib->pmcw.st == SUBCHANNEL_TYPE_MSG) && !schib->pmcw.w)
		वापस 0;
	वापस 1;
पूर्ण
EXPORT_SYMBOL_GPL(css_sch_is_valid);

अटल पूर्णांक css_evaluate_new_subchannel(काष्ठा subchannel_id schid, पूर्णांक slow)
अणु
	काष्ठा schib schib;
	पूर्णांक ccode;

	अगर (!slow) अणु
		/* Will be करोne on the slow path. */
		वापस -EAGAIN;
	पूर्ण
	/*
	 * The first subchannel that is not-operational (ccode==3)
	 * indicates that there aren't any more devices available.
	 * If stsch माला_लो an exception, it means the current subchannel set
	 * is not valid.
	 */
	ccode = stsch(schid, &schib);
	अगर (ccode)
		वापस (ccode == 3) ? -ENXIO : ccode;

	वापस css_probe_device(schid, &schib);
पूर्ण

अटल पूर्णांक css_evaluate_known_subchannel(काष्ठा subchannel *sch, पूर्णांक slow)
अणु
	पूर्णांक ret = 0;

	अगर (sch->driver) अणु
		अगर (sch->driver->sch_event)
			ret = sch->driver->sch_event(sch, slow);
		अन्यथा
			dev_dbg(&sch->dev,
				"Got subchannel machine check but "
				"no sch_event handler provided.\n");
	पूर्ण
	अगर (ret != 0 && ret != -EAGAIN) अणु
		CIO_MSG_EVENT(2, "eval: sch 0.%x.%04x, rc=%d\n",
			      sch->schid.ssid, sch->schid.sch_no, ret);
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम css_evaluate_subchannel(काष्ठा subchannel_id schid, पूर्णांक slow)
अणु
	काष्ठा subchannel *sch;
	पूर्णांक ret;

	sch = get_subchannel_by_schid(schid);
	अगर (sch) अणु
		ret = css_evaluate_known_subchannel(sch, slow);
		put_device(&sch->dev);
	पूर्ण अन्यथा
		ret = css_evaluate_new_subchannel(schid, slow);
	अगर (ret == -EAGAIN)
		css_schedule_eval(schid);
पूर्ण

/**
 * css_sched_sch_toकरो - schedule a subchannel operation
 * @sch: subchannel
 * @toकरो: toकरो
 *
 * Schedule the operation identअगरied by @toकरो to be perक्रमmed on the slow path
 * workqueue. Do nothing अगर another operation with higher priority is alपढ़ोy
 * scheduled. Needs to be called with subchannel lock held.
 */
व्योम css_sched_sch_toकरो(काष्ठा subchannel *sch, क्रमागत sch_toकरो toकरो)
अणु
	CIO_MSG_EVENT(4, "sch_todo: sched sch=0.%x.%04x todo=%d\n",
		      sch->schid.ssid, sch->schid.sch_no, toकरो);
	अगर (sch->toकरो >= toकरो)
		वापस;
	/* Get workqueue ref. */
	अगर (!get_device(&sch->dev))
		वापस;
	sch->toकरो = toकरो;
	अगर (!queue_work(cio_work_q, &sch->toकरो_work)) अणु
		/* Alपढ़ोy queued, release workqueue ref. */
		put_device(&sch->dev);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(css_sched_sch_toकरो);

अटल व्योम css_sch_toकरो(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा subchannel *sch;
	क्रमागत sch_toकरो toकरो;
	पूर्णांक ret;

	sch = container_of(work, काष्ठा subchannel, toकरो_work);
	/* Find out toकरो. */
	spin_lock_irq(sch->lock);
	toकरो = sch->toकरो;
	CIO_MSG_EVENT(4, "sch_todo: sch=0.%x.%04x, todo=%d\n", sch->schid.ssid,
		      sch->schid.sch_no, toकरो);
	sch->toकरो = SCH_TODO_NOTHING;
	spin_unlock_irq(sch->lock);
	/* Perक्रमm toकरो. */
	चयन (toकरो) अणु
	हाल SCH_TODO_NOTHING:
		अवरोध;
	हाल SCH_TODO_EVAL:
		ret = css_evaluate_known_subchannel(sch, 1);
		अगर (ret == -EAGAIN) अणु
			spin_lock_irq(sch->lock);
			css_sched_sch_toकरो(sch, toकरो);
			spin_unlock_irq(sch->lock);
		पूर्ण
		अवरोध;
	हाल SCH_TODO_UNREG:
		css_sch_device_unरेजिस्टर(sch);
		अवरोध;
	पूर्ण
	/* Release workqueue ref. */
	put_device(&sch->dev);
पूर्ण

अटल काष्ठा idset *slow_subchannel_set;
अटल DEFINE_SPINLOCK(slow_subchannel_lock);
अटल DECLARE_WAIT_QUEUE_HEAD(css_eval_wq);
अटल atomic_t css_eval_scheduled;

अटल पूर्णांक __init slow_subchannel_init(व्योम)
अणु
	atomic_set(&css_eval_scheduled, 0);
	slow_subchannel_set = idset_sch_new();
	अगर (!slow_subchannel_set) अणु
		CIO_MSG_EVENT(0, "could not allocate slow subchannel set\n");
		वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक slow_eval_known_fn(काष्ठा subchannel *sch, व्योम *data)
अणु
	पूर्णांक eval;
	पूर्णांक rc;

	spin_lock_irq(&slow_subchannel_lock);
	eval = idset_sch_contains(slow_subchannel_set, sch->schid);
	idset_sch_del(slow_subchannel_set, sch->schid);
	spin_unlock_irq(&slow_subchannel_lock);
	अगर (eval) अणु
		rc = css_evaluate_known_subchannel(sch, 1);
		अगर (rc == -EAGAIN)
			css_schedule_eval(sch->schid);
		/*
		 * The loop might take दीर्घ समय क्रम platक्रमms with lots of
		 * known devices. Allow scheduling here.
		 */
		cond_resched();
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक slow_eval_unknown_fn(काष्ठा subchannel_id schid, व्योम *data)
अणु
	पूर्णांक eval;
	पूर्णांक rc = 0;

	spin_lock_irq(&slow_subchannel_lock);
	eval = idset_sch_contains(slow_subchannel_set, schid);
	idset_sch_del(slow_subchannel_set, schid);
	spin_unlock_irq(&slow_subchannel_lock);
	अगर (eval) अणु
		rc = css_evaluate_new_subchannel(schid, 1);
		चयन (rc) अणु
		हाल -EAGAIN:
			css_schedule_eval(schid);
			rc = 0;
			अवरोध;
		हाल -ENXIO:
		हाल -ENOMEM:
		हाल -EIO:
			/* These should पात looping */
			spin_lock_irq(&slow_subchannel_lock);
			idset_sch_del_subseq(slow_subchannel_set, schid);
			spin_unlock_irq(&slow_subchannel_lock);
			अवरोध;
		शेष:
			rc = 0;
		पूर्ण
		/* Allow scheduling here since the containing loop might
		 * take a जबतक.  */
		cond_resched();
	पूर्ण
	वापस rc;
पूर्ण

अटल व्योम css_slow_path_func(काष्ठा work_काष्ठा *unused)
अणु
	अचिन्हित दीर्घ flags;

	CIO_TRACE_EVENT(4, "slowpath");
	क्रम_each_subchannel_staged(slow_eval_known_fn, slow_eval_unknown_fn,
				   शून्य);
	spin_lock_irqsave(&slow_subchannel_lock, flags);
	अगर (idset_is_empty(slow_subchannel_set)) अणु
		atomic_set(&css_eval_scheduled, 0);
		wake_up(&css_eval_wq);
	पूर्ण
	spin_unlock_irqrestore(&slow_subchannel_lock, flags);
पूर्ण

अटल DECLARE_DELAYED_WORK(slow_path_work, css_slow_path_func);
काष्ठा workqueue_काष्ठा *cio_work_q;

व्योम css_schedule_eval(काष्ठा subchannel_id schid)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&slow_subchannel_lock, flags);
	idset_sch_add(slow_subchannel_set, schid);
	atomic_set(&css_eval_scheduled, 1);
	queue_delayed_work(cio_work_q, &slow_path_work, 0);
	spin_unlock_irqrestore(&slow_subchannel_lock, flags);
पूर्ण

व्योम css_schedule_eval_all(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&slow_subchannel_lock, flags);
	idset_fill(slow_subchannel_set);
	atomic_set(&css_eval_scheduled, 1);
	queue_delayed_work(cio_work_q, &slow_path_work, 0);
	spin_unlock_irqrestore(&slow_subchannel_lock, flags);
पूर्ण

अटल पूर्णांक __unset_रेजिस्टरed(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा idset *set = data;
	काष्ठा subchannel *sch = to_subchannel(dev);

	idset_sch_del(set, sch->schid);
	वापस 0;
पूर्ण

व्योम css_schedule_eval_all_unreg(अचिन्हित दीर्घ delay)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा idset *unreg_set;

	/* Find unरेजिस्टरed subchannels. */
	unreg_set = idset_sch_new();
	अगर (!unreg_set) अणु
		/* Fallback. */
		css_schedule_eval_all();
		वापस;
	पूर्ण
	idset_fill(unreg_set);
	bus_क्रम_each_dev(&css_bus_type, शून्य, unreg_set, __unset_रेजिस्टरed);
	/* Apply to slow_subchannel_set. */
	spin_lock_irqsave(&slow_subchannel_lock, flags);
	idset_add_set(slow_subchannel_set, unreg_set);
	atomic_set(&css_eval_scheduled, 1);
	queue_delayed_work(cio_work_q, &slow_path_work, delay);
	spin_unlock_irqrestore(&slow_subchannel_lock, flags);
	idset_मुक्त(unreg_set);
पूर्ण

व्योम css_रुको_क्रम_slow_path(व्योम)
अणु
	flush_workqueue(cio_work_q);
पूर्ण

/* Schedule reprobing of all unरेजिस्टरed subchannels. */
व्योम css_schedule_reprobe(व्योम)
अणु
	/* Schedule with a delay to allow merging of subsequent calls. */
	css_schedule_eval_all_unreg(1 * HZ);
पूर्ण
EXPORT_SYMBOL_GPL(css_schedule_reprobe);

/*
 * Called from the machine check handler क्रम subchannel report words.
 */
अटल व्योम css_process_crw(काष्ठा crw *crw0, काष्ठा crw *crw1, पूर्णांक overflow)
अणु
	काष्ठा subchannel_id mchk_schid;
	काष्ठा subchannel *sch;

	अगर (overflow) अणु
		css_schedule_eval_all();
		वापस;
	पूर्ण
	CIO_CRW_EVENT(2, "CRW0 reports slct=%d, oflw=%d, "
		      "chn=%d, rsc=%X, anc=%d, erc=%X, rsid=%X\n",
		      crw0->slct, crw0->oflw, crw0->chn, crw0->rsc, crw0->anc,
		      crw0->erc, crw0->rsid);
	अगर (crw1)
		CIO_CRW_EVENT(2, "CRW1 reports slct=%d, oflw=%d, "
			      "chn=%d, rsc=%X, anc=%d, erc=%X, rsid=%X\n",
			      crw1->slct, crw1->oflw, crw1->chn, crw1->rsc,
			      crw1->anc, crw1->erc, crw1->rsid);
	init_subchannel_id(&mchk_schid);
	mchk_schid.sch_no = crw0->rsid;
	अगर (crw1)
		mchk_schid.ssid = (crw1->rsid >> 4) & 3;

	अगर (crw0->erc == CRW_ERC_PMOD) अणु
		sch = get_subchannel_by_schid(mchk_schid);
		अगर (sch) अणु
			css_update_ssd_info(sch);
			put_device(&sch->dev);
		पूर्ण
	पूर्ण
	/*
	 * Since we are always presented with IPI in the CRW, we have to
	 * use stsch() to find out अगर the subchannel in question has come
	 * or gone.
	 */
	css_evaluate_subchannel(mchk_schid, 0);
पूर्ण

अटल व्योम __init
css_generate_pgid(काष्ठा channel_subप्रणाली *css, u32 tod_high)
अणु
	काष्ठा cpuid cpu_id;

	अगर (css_general_अक्षरacteristics.mcss) अणु
		css->global_pgid.pgid_high.ext_cssid.version = 0x80;
		css->global_pgid.pgid_high.ext_cssid.cssid =
			css->id_valid ? css->cssid : 0;
	पूर्ण अन्यथा अणु
		css->global_pgid.pgid_high.cpu_addr = stap();
	पूर्ण
	get_cpu_id(&cpu_id);
	css->global_pgid.cpu_id = cpu_id.ident;
	css->global_pgid.cpu_model = cpu_id.machine;
	css->global_pgid.tod_high = tod_high;
पूर्ण

अटल व्योम channel_subप्रणाली_release(काष्ठा device *dev)
अणु
	काष्ठा channel_subप्रणाली *css = to_css(dev);

	mutex_destroy(&css->mutex);
	kमुक्त(css);
पूर्ण

अटल sमाप_प्रकार real_cssid_show(काष्ठा device *dev, काष्ठा device_attribute *a,
			       अक्षर *buf)
अणु
	काष्ठा channel_subप्रणाली *css = to_css(dev);

	अगर (!css->id_valid)
		वापस -EINVAL;

	वापस प्र_लिखो(buf, "%x\n", css->cssid);
पूर्ण
अटल DEVICE_ATTR_RO(real_cssid);

अटल sमाप_प्रकार cm_enable_show(काष्ठा device *dev, काष्ठा device_attribute *a,
			      अक्षर *buf)
अणु
	काष्ठा channel_subप्रणाली *css = to_css(dev);
	पूर्णांक ret;

	mutex_lock(&css->mutex);
	ret = प्र_लिखो(buf, "%x\n", css->cm_enabled);
	mutex_unlock(&css->mutex);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार cm_enable_store(काष्ठा device *dev, काष्ठा device_attribute *a,
			       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा channel_subप्रणाली *css = to_css(dev);
	अचिन्हित दीर्घ val;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(buf, 16, &val);
	अगर (ret)
		वापस ret;
	mutex_lock(&css->mutex);
	चयन (val) अणु
	हाल 0:
		ret = css->cm_enabled ? chsc_secm(css, 0) : 0;
		अवरोध;
	हाल 1:
		ret = css->cm_enabled ? 0 : chsc_secm(css, 1);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण
	mutex_unlock(&css->mutex);
	वापस ret < 0 ? ret : count;
पूर्ण
अटल DEVICE_ATTR_RW(cm_enable);

अटल umode_t cm_enable_mode(काष्ठा kobject *kobj, काष्ठा attribute *attr,
			      पूर्णांक index)
अणु
	वापस css_chsc_अक्षरacteristics.secm ? attr->mode : 0;
पूर्ण

अटल काष्ठा attribute *cssdev_attrs[] = अणु
	&dev_attr_real_cssid.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group cssdev_attr_group = अणु
	.attrs = cssdev_attrs,
पूर्ण;

अटल काष्ठा attribute *cssdev_cm_attrs[] = अणु
	&dev_attr_cm_enable.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group cssdev_cm_attr_group = अणु
	.attrs = cssdev_cm_attrs,
	.is_visible = cm_enable_mode,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *cssdev_attr_groups[] = अणु
	&cssdev_attr_group,
	&cssdev_cm_attr_group,
	शून्य,
पूर्ण;

अटल पूर्णांक __init setup_css(पूर्णांक nr)
अणु
	काष्ठा channel_subप्रणाली *css;
	पूर्णांक ret;

	css = kzalloc(माप(*css), GFP_KERNEL);
	अगर (!css)
		वापस -ENOMEM;

	channel_subप्रणालीs[nr] = css;
	dev_set_name(&css->device, "css%x", nr);
	css->device.groups = cssdev_attr_groups;
	css->device.release = channel_subप्रणाली_release;
	/*
	 * We currently allocate notअगरier bits with this (using
	 * css->device as the device argument with the DMA API)
	 * and are fine with 64 bit addresses.
	 */
	ret = dma_coerce_mask_and_coherent(&css->device, DMA_BIT_MASK(64));
	अगर (ret) अणु
		kमुक्त(css);
		जाओ out_err;
	पूर्ण

	mutex_init(&css->mutex);
	ret = chsc_get_cssid_iid(nr, &css->cssid, &css->iid);
	अगर (!ret) अणु
		css->id_valid = true;
		pr_info("Partition identifier %01x.%01x\n", css->cssid,
			css->iid);
	पूर्ण
	css_generate_pgid(css, (u32) (get_tod_घड़ी() >> 32));

	ret = device_रेजिस्टर(&css->device);
	अगर (ret) अणु
		put_device(&css->device);
		जाओ out_err;
	पूर्ण

	css->pseuकरो_subchannel = kzalloc(माप(*css->pseuकरो_subchannel),
					 GFP_KERNEL);
	अगर (!css->pseuकरो_subchannel) अणु
		device_unरेजिस्टर(&css->device);
		ret = -ENOMEM;
		जाओ out_err;
	पूर्ण

	css->pseuकरो_subchannel->dev.parent = &css->device;
	css->pseuकरो_subchannel->dev.release = css_subchannel_release;
	mutex_init(&css->pseuकरो_subchannel->reg_mutex);
	ret = css_sch_create_locks(css->pseuकरो_subchannel);
	अगर (ret) अणु
		kमुक्त(css->pseuकरो_subchannel);
		device_unरेजिस्टर(&css->device);
		जाओ out_err;
	पूर्ण

	dev_set_name(&css->pseuकरो_subchannel->dev, "defunct");
	ret = device_रेजिस्टर(&css->pseuकरो_subchannel->dev);
	अगर (ret) अणु
		put_device(&css->pseuकरो_subchannel->dev);
		device_unरेजिस्टर(&css->device);
		जाओ out_err;
	पूर्ण

	वापस ret;
out_err:
	channel_subप्रणालीs[nr] = शून्य;
	वापस ret;
पूर्ण

अटल पूर्णांक css_reboot_event(काष्ठा notअगरier_block *this,
			    अचिन्हित दीर्घ event,
			    व्योम *ptr)
अणु
	काष्ठा channel_subप्रणाली *css;
	पूर्णांक ret;

	ret = NOTIFY_DONE;
	क्रम_each_css(css) अणु
		mutex_lock(&css->mutex);
		अगर (css->cm_enabled)
			अगर (chsc_secm(css, 0))
				ret = NOTIFY_BAD;
		mutex_unlock(&css->mutex);
	पूर्ण

	वापस ret;
पूर्ण

अटल काष्ठा notअगरier_block css_reboot_notअगरier = अणु
	.notअगरier_call = css_reboot_event,
पूर्ण;

#घोषणा  CIO_DMA_GFP (GFP_KERNEL | __GFP_ZERO)
अटल काष्ठा gen_pool *cio_dma_pool;

/* Currently cio supports only a single css */
काष्ठा device *cio_get_dma_css_dev(व्योम)
अणु
	वापस &channel_subप्रणालीs[0]->device;
पूर्ण

काष्ठा gen_pool *cio_gp_dma_create(काष्ठा device *dma_dev, पूर्णांक nr_pages)
अणु
	काष्ठा gen_pool *gp_dma;
	व्योम *cpu_addr;
	dma_addr_t dma_addr;
	पूर्णांक i;

	gp_dma = gen_pool_create(3, -1);
	अगर (!gp_dma)
		वापस शून्य;
	क्रम (i = 0; i < nr_pages; ++i) अणु
		cpu_addr = dma_alloc_coherent(dma_dev, PAGE_SIZE, &dma_addr,
					      CIO_DMA_GFP);
		अगर (!cpu_addr)
			वापस gp_dma;
		gen_pool_add_virt(gp_dma, (अचिन्हित दीर्घ) cpu_addr,
				  dma_addr, PAGE_SIZE, -1);
	पूर्ण
	वापस gp_dma;
पूर्ण

अटल व्योम __gp_dma_मुक्त_dma(काष्ठा gen_pool *pool,
			      काष्ठा gen_pool_chunk *chunk, व्योम *data)
अणु
	माप_प्रकार chunk_size = chunk->end_addr - chunk->start_addr + 1;

	dma_मुक्त_coherent((काष्ठा device *) data, chunk_size,
			 (व्योम *) chunk->start_addr,
			 (dma_addr_t) chunk->phys_addr);
पूर्ण

व्योम cio_gp_dma_destroy(काष्ठा gen_pool *gp_dma, काष्ठा device *dma_dev)
अणु
	अगर (!gp_dma)
		वापस;
	/* this is quite ugly but no better idea */
	gen_pool_क्रम_each_chunk(gp_dma, __gp_dma_मुक्त_dma, dma_dev);
	gen_pool_destroy(gp_dma);
पूर्ण

अटल पूर्णांक cio_dma_pool_init(व्योम)
अणु
	/* No need to मुक्त up the resources: compiled in */
	cio_dma_pool = cio_gp_dma_create(cio_get_dma_css_dev(), 1);
	अगर (!cio_dma_pool)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

व्योम *cio_gp_dma_zalloc(काष्ठा gen_pool *gp_dma, काष्ठा device *dma_dev,
			माप_प्रकार size)
अणु
	dma_addr_t dma_addr;
	अचिन्हित दीर्घ addr;
	माप_प्रकार chunk_size;

	अगर (!gp_dma)
		वापस शून्य;
	addr = gen_pool_alloc(gp_dma, size);
	जबतक (!addr) अणु
		chunk_size = round_up(size, PAGE_SIZE);
		addr = (अचिन्हित दीर्घ) dma_alloc_coherent(dma_dev,
					 chunk_size, &dma_addr, CIO_DMA_GFP);
		अगर (!addr)
			वापस शून्य;
		gen_pool_add_virt(gp_dma, addr, dma_addr, chunk_size, -1);
		addr = gen_pool_alloc(gp_dma, size);
	पूर्ण
	वापस (व्योम *) addr;
पूर्ण

व्योम cio_gp_dma_मुक्त(काष्ठा gen_pool *gp_dma, व्योम *cpu_addr, माप_प्रकार size)
अणु
	अगर (!cpu_addr)
		वापस;
	स_रखो(cpu_addr, 0, size);
	gen_pool_मुक्त(gp_dma, (अचिन्हित दीर्घ) cpu_addr, size);
पूर्ण

/*
 * Allocate dma memory from the css global pool. Intended क्रम memory not
 * specअगरic to any single device within the css. The allocated memory
 * is not guaranteed to be 31-bit addressable.
 *
 * Caution: Not suitable क्रम early stuff like console.
 */
व्योम *cio_dma_zalloc(माप_प्रकार size)
अणु
	वापस cio_gp_dma_zalloc(cio_dma_pool, cio_get_dma_css_dev(), size);
पूर्ण

व्योम cio_dma_मुक्त(व्योम *cpu_addr, माप_प्रकार size)
अणु
	cio_gp_dma_मुक्त(cio_dma_pool, cpu_addr, size);
पूर्ण

/*
 * Now that the driver core is running, we can setup our channel subप्रणाली.
 * The काष्ठा subchannel's are created during probing.
 */
अटल पूर्णांक __init css_bus_init(व्योम)
अणु
	पूर्णांक ret, i;

	ret = chsc_init();
	अगर (ret)
		वापस ret;

	chsc_determine_css_अक्षरacteristics();
	/* Try to enable MSS. */
	ret = chsc_enable_facility(CHSC_SDA_OC_MSS);
	अगर (ret)
		max_ssid = 0;
	अन्यथा /* Success. */
		max_ssid = __MAX_SSID;

	ret = slow_subchannel_init();
	अगर (ret)
		जाओ out;

	ret = crw_रेजिस्टर_handler(CRW_RSC_SCH, css_process_crw);
	अगर (ret)
		जाओ out;

	अगर ((ret = bus_रेजिस्टर(&css_bus_type)))
		जाओ out;

	/* Setup css काष्ठाure. */
	क्रम (i = 0; i <= MAX_CSS_IDX; i++) अणु
		ret = setup_css(i);
		अगर (ret)
			जाओ out_unरेजिस्टर;
	पूर्ण
	ret = रेजिस्टर_reboot_notअगरier(&css_reboot_notअगरier);
	अगर (ret)
		जाओ out_unरेजिस्टर;
	ret = cio_dma_pool_init();
	अगर (ret)
		जाओ out_unरेजिस्टर_rn;
	airq_init();
	css_init_करोne = 1;

	/* Enable शेष isc क्रम I/O subchannels. */
	isc_रेजिस्टर(IO_SCH_ISC);

	वापस 0;
out_unरेजिस्टर_rn:
	unरेजिस्टर_reboot_notअगरier(&css_reboot_notअगरier);
out_unरेजिस्टर:
	जबतक (i-- > 0) अणु
		काष्ठा channel_subप्रणाली *css = channel_subप्रणालीs[i];
		device_unरेजिस्टर(&css->pseuकरो_subchannel->dev);
		device_unरेजिस्टर(&css->device);
	पूर्ण
	bus_unरेजिस्टर(&css_bus_type);
out:
	crw_unरेजिस्टर_handler(CRW_RSC_SCH);
	idset_मुक्त(slow_subchannel_set);
	chsc_init_cleanup();
	pr_alert("The CSS device driver initialization failed with "
		 "errno=%d\n", ret);
	वापस ret;
पूर्ण

अटल व्योम __init css_bus_cleanup(व्योम)
अणु
	काष्ठा channel_subप्रणाली *css;

	क्रम_each_css(css) अणु
		device_unरेजिस्टर(&css->pseuकरो_subchannel->dev);
		device_unरेजिस्टर(&css->device);
	पूर्ण
	bus_unरेजिस्टर(&css_bus_type);
	crw_unरेजिस्टर_handler(CRW_RSC_SCH);
	idset_मुक्त(slow_subchannel_set);
	chsc_init_cleanup();
	isc_unरेजिस्टर(IO_SCH_ISC);
पूर्ण

अटल पूर्णांक __init channel_subप्रणाली_init(व्योम)
अणु
	पूर्णांक ret;

	ret = css_bus_init();
	अगर (ret)
		वापस ret;
	cio_work_q = create_singlethपढ़ो_workqueue("cio");
	अगर (!cio_work_q) अणु
		ret = -ENOMEM;
		जाओ out_bus;
	पूर्ण
	ret = io_subchannel_init();
	अगर (ret)
		जाओ out_wq;

	/* Register subchannels which are alपढ़ोy in use. */
	cio_रेजिस्टर_early_subchannels();
	/* Start initial subchannel evaluation. */
	css_schedule_eval_all();

	वापस ret;
out_wq:
	destroy_workqueue(cio_work_q);
out_bus:
	css_bus_cleanup();
	वापस ret;
पूर्ण
subsys_initcall(channel_subप्रणाली_init);

अटल पूर्णांक css_settle(काष्ठा device_driver *drv, व्योम *unused)
अणु
	काष्ठा css_driver *cssdrv = to_cssdriver(drv);

	अगर (cssdrv->settle)
		वापस cssdrv->settle();
	वापस 0;
पूर्ण

पूर्णांक css_complete_work(व्योम)
अणु
	पूर्णांक ret;

	/* Wait क्रम the evaluation of subchannels to finish. */
	ret = रुको_event_पूर्णांकerruptible(css_eval_wq,
				       atomic_पढ़ो(&css_eval_scheduled) == 0);
	अगर (ret)
		वापस -EINTR;
	flush_workqueue(cio_work_q);
	/* Wait क्रम the subchannel type specअगरic initialization to finish */
	वापस bus_क्रम_each_drv(&css_bus_type, शून्य, शून्य, css_settle);
पूर्ण


/*
 * Wait क्रम the initialization of devices to finish, to make sure we are
 * करोne with our setup अगर the search क्रम the root device starts.
 */
अटल पूर्णांक __init channel_subप्रणाली_init_sync(व्योम)
अणु
	css_complete_work();
	वापस 0;
पूर्ण
subsys_initcall_sync(channel_subप्रणाली_init_sync);

#अगर_घोषित CONFIG_PROC_FS
अटल sमाप_प्रकार cio_settle_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
				माप_प्रकार count, loff_t *ppos)
अणु
	पूर्णांक ret;

	/* Handle pending CRW's. */
	crw_रुको_क्रम_channel_report();
	ret = css_complete_work();

	वापस ret ? ret : count;
पूर्ण

अटल स्थिर काष्ठा proc_ops cio_settle_proc_ops = अणु
	.proc_खोलो	= nonseekable_खोलो,
	.proc_ग_लिखो	= cio_settle_ग_लिखो,
	.proc_lseek	= no_llseek,
पूर्ण;

अटल पूर्णांक __init cio_settle_init(व्योम)
अणु
	काष्ठा proc_dir_entry *entry;

	entry = proc_create("cio_settle", S_IWUSR, शून्य, &cio_settle_proc_ops);
	अगर (!entry)
		वापस -ENOMEM;
	वापस 0;
पूर्ण
device_initcall(cio_settle_init);
#पूर्ण_अगर /*CONFIG_PROC_FS*/

पूर्णांक sch_is_pseuकरो_sch(काष्ठा subchannel *sch)
अणु
	अगर (!sch->dev.parent)
		वापस 0;
	वापस sch == to_css(sch->dev.parent)->pseuकरो_subchannel;
पूर्ण

अटल पूर्णांक css_bus_match(काष्ठा device *dev, काष्ठा device_driver *drv)
अणु
	काष्ठा subchannel *sch = to_subchannel(dev);
	काष्ठा css_driver *driver = to_cssdriver(drv);
	काष्ठा css_device_id *id;

	/* When driver_override is set, only bind to the matching driver */
	अगर (sch->driver_override && म_भेद(sch->driver_override, drv->name))
		वापस 0;

	क्रम (id = driver->subchannel_type; id->match_flags; id++) अणु
		अगर (sch->st == id->type)
			वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक css_probe(काष्ठा device *dev)
अणु
	काष्ठा subchannel *sch;
	पूर्णांक ret;

	sch = to_subchannel(dev);
	sch->driver = to_cssdriver(dev->driver);
	ret = sch->driver->probe ? sch->driver->probe(sch) : 0;
	अगर (ret)
		sch->driver = शून्य;
	वापस ret;
पूर्ण

अटल पूर्णांक css_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा subchannel *sch;
	पूर्णांक ret;

	sch = to_subchannel(dev);
	ret = sch->driver->हटाओ ? sch->driver->हटाओ(sch) : 0;
	sch->driver = शून्य;
	वापस ret;
पूर्ण

अटल व्योम css_shutकरोwn(काष्ठा device *dev)
अणु
	काष्ठा subchannel *sch;

	sch = to_subchannel(dev);
	अगर (sch->driver && sch->driver->shutकरोwn)
		sch->driver->shutकरोwn(sch);
पूर्ण

अटल पूर्णांक css_uevent(काष्ठा device *dev, काष्ठा kobj_uevent_env *env)
अणु
	काष्ठा subchannel *sch = to_subchannel(dev);
	पूर्णांक ret;

	ret = add_uevent_var(env, "ST=%01X", sch->st);
	अगर (ret)
		वापस ret;
	ret = add_uevent_var(env, "MODALIAS=css:t%01X", sch->st);
	वापस ret;
पूर्ण

अटल काष्ठा bus_type css_bus_type = अणु
	.name     = "css",
	.match    = css_bus_match,
	.probe    = css_probe,
	.हटाओ   = css_हटाओ,
	.shutकरोwn = css_shutकरोwn,
	.uevent   = css_uevent,
पूर्ण;

/**
 * css_driver_रेजिस्टर - रेजिस्टर a css driver
 * @cdrv: css driver to रेजिस्टर
 *
 * This is मुख्यly a wrapper around driver_रेजिस्टर that sets name
 * and bus_type in the embedded काष्ठा device_driver correctly.
 */
पूर्णांक css_driver_रेजिस्टर(काष्ठा css_driver *cdrv)
अणु
	cdrv->drv.bus = &css_bus_type;
	वापस driver_रेजिस्टर(&cdrv->drv);
पूर्ण
EXPORT_SYMBOL_GPL(css_driver_रेजिस्टर);

/**
 * css_driver_unरेजिस्टर - unरेजिस्टर a css driver
 * @cdrv: css driver to unरेजिस्टर
 *
 * This is a wrapper around driver_unरेजिस्टर.
 */
व्योम css_driver_unरेजिस्टर(काष्ठा css_driver *cdrv)
अणु
	driver_unरेजिस्टर(&cdrv->drv);
पूर्ण
EXPORT_SYMBOL_GPL(css_driver_unरेजिस्टर);
