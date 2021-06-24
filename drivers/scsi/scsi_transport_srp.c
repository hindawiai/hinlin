<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * SCSI RDMA (SRP) transport class
 *
 * Copyright (C) 2007 FUJITA Tomonori <tomof@acm.org>
 */
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>

#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_transport.h>
#समावेश <scsi/scsi_transport_srp.h>
#समावेश "scsi_priv.h"

काष्ठा srp_host_attrs अणु
	atomic_t next_port_id;
पूर्ण;
#घोषणा to_srp_host_attrs(host)	((काष्ठा srp_host_attrs *)(host)->shost_data)

#घोषणा SRP_HOST_ATTRS 0
#घोषणा SRP_RPORT_ATTRS 8

काष्ठा srp_पूर्णांकernal अणु
	काष्ठा scsi_transport_ढाँचा t;
	काष्ठा srp_function_ढाँचा *f;

	काष्ठा device_attribute *host_attrs[SRP_HOST_ATTRS + 1];

	काष्ठा device_attribute *rport_attrs[SRP_RPORT_ATTRS + 1];
	काष्ठा transport_container rport_attr_cont;
पूर्ण;

अटल पूर्णांक scsi_is_srp_rport(स्थिर काष्ठा device *dev);

#घोषणा to_srp_पूर्णांकernal(पंचांगpl) container_of(पंचांगpl, काष्ठा srp_पूर्णांकernal, t)

#घोषणा	dev_to_rport(d)	container_of(d, काष्ठा srp_rport, dev)
#घोषणा transport_class_to_srp_rport(dev) dev_to_rport((dev)->parent)
अटल अंतरभूत काष्ठा Scsi_Host *rport_to_shost(काष्ठा srp_rport *r)
अणु
	वापस dev_to_shost(r->dev.parent);
पूर्ण

अटल पूर्णांक find_child_rport(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा device **child = data;

	अगर (scsi_is_srp_rport(dev)) अणु
		WARN_ON_ONCE(*child);
		*child = dev;
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा srp_rport *shost_to_rport(काष्ठा Scsi_Host *shost)
अणु
	काष्ठा device *child = शून्य;

	WARN_ON_ONCE(device_क्रम_each_child(&shost->shost_gendev, &child,
					   find_child_rport) < 0);
	वापस child ? dev_to_rport(child) : शून्य;
पूर्ण

/**
 * srp_पंचांगo_valid() - check समयout combination validity
 * @reconnect_delay: Reconnect delay in seconds.
 * @fast_io_fail_पंचांगo: Fast I/O fail समयout in seconds.
 * @dev_loss_पंचांगo: Device loss समयout in seconds.
 *
 * The combination of the समयout parameters must be such that SCSI commands
 * are finished in a reasonable समय. Hence करो not allow the fast I/O fail
 * समयout to exceed SCSI_DEVICE_BLOCK_MAX_TIMEOUT nor allow dev_loss_पंचांगo to
 * exceed that limit अगर failing I/O fast has been disabled. Furthermore, these
 * parameters must be such that multipath can detect failed paths समयly.
 * Hence करो not allow all three parameters to be disabled simultaneously.
 */
पूर्णांक srp_पंचांगo_valid(पूर्णांक reconnect_delay, पूर्णांक fast_io_fail_पंचांगo, दीर्घ dev_loss_पंचांगo)
अणु
	अगर (reconnect_delay < 0 && fast_io_fail_पंचांगo < 0 && dev_loss_पंचांगo < 0)
		वापस -EINVAL;
	अगर (reconnect_delay == 0)
		वापस -EINVAL;
	अगर (fast_io_fail_पंचांगo > SCSI_DEVICE_BLOCK_MAX_TIMEOUT)
		वापस -EINVAL;
	अगर (fast_io_fail_पंचांगo < 0 &&
	    dev_loss_पंचांगo > SCSI_DEVICE_BLOCK_MAX_TIMEOUT)
		वापस -EINVAL;
	अगर (dev_loss_पंचांगo >= दीर्घ_उच्च / HZ)
		वापस -EINVAL;
	अगर (fast_io_fail_पंचांगo >= 0 && dev_loss_पंचांगo >= 0 &&
	    fast_io_fail_पंचांगo >= dev_loss_पंचांगo)
		वापस -EINVAL;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(srp_पंचांगo_valid);

अटल पूर्णांक srp_host_setup(काष्ठा transport_container *tc, काष्ठा device *dev,
			  काष्ठा device *cdev)
अणु
	काष्ठा Scsi_Host *shost = dev_to_shost(dev);
	काष्ठा srp_host_attrs *srp_host = to_srp_host_attrs(shost);

	atomic_set(&srp_host->next_port_id, 0);
	वापस 0;
पूर्ण

अटल DECLARE_TRANSPORT_CLASS(srp_host_class, "srp_host", srp_host_setup,
			       शून्य, शून्य);

अटल DECLARE_TRANSPORT_CLASS(srp_rport_class, "srp_remote_ports",
			       शून्य, शून्य, शून्य);

अटल sमाप_प्रकार
show_srp_rport_id(काष्ठा device *dev, काष्ठा device_attribute *attr,
		  अक्षर *buf)
अणु
	काष्ठा srp_rport *rport = transport_class_to_srp_rport(dev);
	वापस प्र_लिखो(buf, "%16phC\n", rport->port_id);
पूर्ण

अटल DEVICE_ATTR(port_id, S_IRUGO, show_srp_rport_id, शून्य);

अटल स्थिर काष्ठा अणु
	u32 value;
	अक्षर *name;
पूर्ण srp_rport_role_names[] = अणु
	अणुSRP_RPORT_ROLE_INITIATOR, "SRP Initiator"पूर्ण,
	अणुSRP_RPORT_ROLE_TARGET, "SRP Target"पूर्ण,
पूर्ण;

अटल sमाप_प्रकार
show_srp_rport_roles(काष्ठा device *dev, काष्ठा device_attribute *attr,
		     अक्षर *buf)
अणु
	काष्ठा srp_rport *rport = transport_class_to_srp_rport(dev);
	पूर्णांक i;
	अक्षर *name = शून्य;

	क्रम (i = 0; i < ARRAY_SIZE(srp_rport_role_names); i++)
		अगर (srp_rport_role_names[i].value == rport->roles) अणु
			name = srp_rport_role_names[i].name;
			अवरोध;
		पूर्ण
	वापस प्र_लिखो(buf, "%s\n", name ? : "unknown");
पूर्ण

अटल DEVICE_ATTR(roles, S_IRUGO, show_srp_rport_roles, शून्य);

अटल sमाप_प्रकार store_srp_rport_delete(काष्ठा device *dev,
				      काष्ठा device_attribute *attr,
				      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा srp_rport *rport = transport_class_to_srp_rport(dev);
	काष्ठा Scsi_Host *shost = dev_to_shost(dev);
	काष्ठा srp_पूर्णांकernal *i = to_srp_पूर्णांकernal(shost->transportt);

	अगर (i->f->rport_delete) अणु
		i->f->rport_delete(rport);
		वापस count;
	पूर्ण अन्यथा अणु
		वापस -ENOSYS;
	पूर्ण
पूर्ण

अटल DEVICE_ATTR(delete, S_IWUSR, शून्य, store_srp_rport_delete);

अटल sमाप_प्रकार show_srp_rport_state(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    अक्षर *buf)
अणु
	अटल स्थिर अक्षर *स्थिर state_name[] = अणु
		[SRP_RPORT_RUNNING]	= "running",
		[SRP_RPORT_BLOCKED]	= "blocked",
		[SRP_RPORT_FAIL_FAST]	= "fail-fast",
		[SRP_RPORT_LOST]	= "lost",
	पूर्ण;
	काष्ठा srp_rport *rport = transport_class_to_srp_rport(dev);
	क्रमागत srp_rport_state state = rport->state;

	वापस प्र_लिखो(buf, "%s\n",
		       (अचिन्हित)state < ARRAY_SIZE(state_name) ?
		       state_name[state] : "???");
पूर्ण

अटल DEVICE_ATTR(state, S_IRUGO, show_srp_rport_state, शून्य);

अटल sमाप_प्रकार srp_show_पंचांगo(अक्षर *buf, पूर्णांक पंचांगo)
अणु
	वापस पंचांगo >= 0 ? प्र_लिखो(buf, "%d\n", पंचांगo) : प्र_लिखो(buf, "off\n");
पूर्ण

पूर्णांक srp_parse_पंचांगo(पूर्णांक *पंचांगo, स्थिर अक्षर *buf)
अणु
	पूर्णांक res = 0;

	अगर (म_भेदन(buf, "off", 3) != 0)
		res = kstrtoपूर्णांक(buf, 0, पंचांगo);
	अन्यथा
		*पंचांगo = -1;

	वापस res;
पूर्ण
EXPORT_SYMBOL(srp_parse_पंचांगo);

अटल sमाप_प्रकार show_reconnect_delay(काष्ठा device *dev,
				    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा srp_rport *rport = transport_class_to_srp_rport(dev);

	वापस srp_show_पंचांगo(buf, rport->reconnect_delay);
पूर्ण

अटल sमाप_प्रकार store_reconnect_delay(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     स्थिर अक्षर *buf, स्थिर माप_प्रकार count)
अणु
	काष्ठा srp_rport *rport = transport_class_to_srp_rport(dev);
	पूर्णांक res, delay;

	res = srp_parse_पंचांगo(&delay, buf);
	अगर (res)
		जाओ out;
	res = srp_पंचांगo_valid(delay, rport->fast_io_fail_पंचांगo,
			    rport->dev_loss_पंचांगo);
	अगर (res)
		जाओ out;

	अगर (rport->reconnect_delay <= 0 && delay > 0 &&
	    rport->state != SRP_RPORT_RUNNING) अणु
		queue_delayed_work(प्रणाली_दीर्घ_wq, &rport->reconnect_work,
				   delay * HZ);
	पूर्ण अन्यथा अगर (delay <= 0) अणु
		cancel_delayed_work(&rport->reconnect_work);
	पूर्ण
	rport->reconnect_delay = delay;
	res = count;

out:
	वापस res;
पूर्ण

अटल DEVICE_ATTR(reconnect_delay, S_IRUGO | S_IWUSR, show_reconnect_delay,
		   store_reconnect_delay);

अटल sमाप_प्रकार show_failed_reconnects(काष्ठा device *dev,
				      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा srp_rport *rport = transport_class_to_srp_rport(dev);

	वापस प्र_लिखो(buf, "%d\n", rport->failed_reconnects);
पूर्ण

अटल DEVICE_ATTR(failed_reconnects, S_IRUGO, show_failed_reconnects, शून्य);

अटल sमाप_प्रकार show_srp_rport_fast_io_fail_पंचांगo(काष्ठा device *dev,
					       काष्ठा device_attribute *attr,
					       अक्षर *buf)
अणु
	काष्ठा srp_rport *rport = transport_class_to_srp_rport(dev);

	वापस srp_show_पंचांगo(buf, rport->fast_io_fail_पंचांगo);
पूर्ण

अटल sमाप_प्रकार store_srp_rport_fast_io_fail_पंचांगo(काष्ठा device *dev,
						काष्ठा device_attribute *attr,
						स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा srp_rport *rport = transport_class_to_srp_rport(dev);
	पूर्णांक res;
	पूर्णांक fast_io_fail_पंचांगo;

	res = srp_parse_पंचांगo(&fast_io_fail_पंचांगo, buf);
	अगर (res)
		जाओ out;
	res = srp_पंचांगo_valid(rport->reconnect_delay, fast_io_fail_पंचांगo,
			    rport->dev_loss_पंचांगo);
	अगर (res)
		जाओ out;
	rport->fast_io_fail_पंचांगo = fast_io_fail_पंचांगo;
	res = count;

out:
	वापस res;
पूर्ण

अटल DEVICE_ATTR(fast_io_fail_पंचांगo, S_IRUGO | S_IWUSR,
		   show_srp_rport_fast_io_fail_पंचांगo,
		   store_srp_rport_fast_io_fail_पंचांगo);

अटल sमाप_प्रकार show_srp_rport_dev_loss_पंचांगo(काष्ठा device *dev,
					   काष्ठा device_attribute *attr,
					   अक्षर *buf)
अणु
	काष्ठा srp_rport *rport = transport_class_to_srp_rport(dev);

	वापस srp_show_पंचांगo(buf, rport->dev_loss_पंचांगo);
पूर्ण

अटल sमाप_प्रकार store_srp_rport_dev_loss_पंचांगo(काष्ठा device *dev,
					    काष्ठा device_attribute *attr,
					    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा srp_rport *rport = transport_class_to_srp_rport(dev);
	पूर्णांक res;
	पूर्णांक dev_loss_पंचांगo;

	res = srp_parse_पंचांगo(&dev_loss_पंचांगo, buf);
	अगर (res)
		जाओ out;
	res = srp_पंचांगo_valid(rport->reconnect_delay, rport->fast_io_fail_पंचांगo,
			    dev_loss_पंचांगo);
	अगर (res)
		जाओ out;
	rport->dev_loss_पंचांगo = dev_loss_पंचांगo;
	res = count;

out:
	वापस res;
पूर्ण

अटल DEVICE_ATTR(dev_loss_पंचांगo, S_IRUGO | S_IWUSR,
		   show_srp_rport_dev_loss_पंचांगo,
		   store_srp_rport_dev_loss_पंचांगo);

अटल पूर्णांक srp_rport_set_state(काष्ठा srp_rport *rport,
			       क्रमागत srp_rport_state new_state)
अणु
	क्रमागत srp_rport_state old_state = rport->state;

	lockdep_निश्चित_held(&rport->mutex);

	चयन (new_state) अणु
	हाल SRP_RPORT_RUNNING:
		चयन (old_state) अणु
		हाल SRP_RPORT_LOST:
			जाओ invalid;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल SRP_RPORT_BLOCKED:
		चयन (old_state) अणु
		हाल SRP_RPORT_RUNNING:
			अवरोध;
		शेष:
			जाओ invalid;
		पूर्ण
		अवरोध;
	हाल SRP_RPORT_FAIL_FAST:
		चयन (old_state) अणु
		हाल SRP_RPORT_LOST:
			जाओ invalid;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल SRP_RPORT_LOST:
		अवरोध;
	पूर्ण
	rport->state = new_state;
	वापस 0;

invalid:
	वापस -EINVAL;
पूर्ण

/**
 * srp_reconnect_work() - reconnect and schedule a new attempt अगर necessary
 * @work: Work काष्ठाure used क्रम scheduling this operation.
 */
अटल व्योम srp_reconnect_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा srp_rport *rport = container_of(to_delayed_work(work),
					काष्ठा srp_rport, reconnect_work);
	काष्ठा Scsi_Host *shost = rport_to_shost(rport);
	पूर्णांक delay, res;

	res = srp_reconnect_rport(rport);
	अगर (res != 0) अणु
		shost_prपूर्णांकk(KERN_ERR, shost,
			     "reconnect attempt %d failed (%d)\n",
			     ++rport->failed_reconnects, res);
		delay = rport->reconnect_delay *
			min(100, max(1, rport->failed_reconnects - 10));
		अगर (delay > 0)
			queue_delayed_work(प्रणाली_दीर्घ_wq,
					   &rport->reconnect_work, delay * HZ);
	पूर्ण
पूर्ण

/*
 * scsi_target_block() must have been called beक्रमe this function is
 * called to guarantee that no .queuecommand() calls are in progress.
 */
अटल व्योम __rport_fail_io_fast(काष्ठा srp_rport *rport)
अणु
	काष्ठा Scsi_Host *shost = rport_to_shost(rport);
	काष्ठा srp_पूर्णांकernal *i;

	lockdep_निश्चित_held(&rport->mutex);

	अगर (srp_rport_set_state(rport, SRP_RPORT_FAIL_FAST))
		वापस;

	scsi_target_unblock(rport->dev.parent, SDEV_TRANSPORT_OFFLINE);

	/* Involve the LLD अगर possible to terminate all I/O on the rport. */
	i = to_srp_पूर्णांकernal(shost->transportt);
	अगर (i->f->terminate_rport_io)
		i->f->terminate_rport_io(rport);
पूर्ण

/**
 * rport_fast_io_fail_समयकरोut() - fast I/O failure समयout handler
 * @work: Work काष्ठाure used क्रम scheduling this operation.
 */
अटल व्योम rport_fast_io_fail_समयकरोut(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा srp_rport *rport = container_of(to_delayed_work(work),
					काष्ठा srp_rport, fast_io_fail_work);
	काष्ठा Scsi_Host *shost = rport_to_shost(rport);

	pr_info("fast_io_fail_tmo expired for SRP %s / %s.\n",
		dev_name(&rport->dev), dev_name(&shost->shost_gendev));

	mutex_lock(&rport->mutex);
	अगर (rport->state == SRP_RPORT_BLOCKED)
		__rport_fail_io_fast(rport);
	mutex_unlock(&rport->mutex);
पूर्ण

/**
 * rport_dev_loss_समयकरोut() - device loss समयout handler
 * @work: Work काष्ठाure used क्रम scheduling this operation.
 */
अटल व्योम rport_dev_loss_समयकरोut(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा srp_rport *rport = container_of(to_delayed_work(work),
					काष्ठा srp_rport, dev_loss_work);
	काष्ठा Scsi_Host *shost = rport_to_shost(rport);
	काष्ठा srp_पूर्णांकernal *i = to_srp_पूर्णांकernal(shost->transportt);

	pr_info("dev_loss_tmo expired for SRP %s / %s.\n",
		dev_name(&rport->dev), dev_name(&shost->shost_gendev));

	mutex_lock(&rport->mutex);
	WARN_ON(srp_rport_set_state(rport, SRP_RPORT_LOST) != 0);
	scsi_target_unblock(rport->dev.parent, SDEV_TRANSPORT_OFFLINE);
	mutex_unlock(&rport->mutex);

	i->f->rport_delete(rport);
पूर्ण

अटल व्योम __srp_start_tl_fail_समयrs(काष्ठा srp_rport *rport)
अणु
	काष्ठा Scsi_Host *shost = rport_to_shost(rport);
	पूर्णांक delay, fast_io_fail_पंचांगo, dev_loss_पंचांगo;

	lockdep_निश्चित_held(&rport->mutex);

	delay = rport->reconnect_delay;
	fast_io_fail_पंचांगo = rport->fast_io_fail_पंचांगo;
	dev_loss_पंचांगo = rport->dev_loss_पंचांगo;
	pr_debug("%s current state: %d\n", dev_name(&shost->shost_gendev),
		 rport->state);

	अगर (rport->state == SRP_RPORT_LOST)
		वापस;
	अगर (delay > 0)
		queue_delayed_work(प्रणाली_दीर्घ_wq, &rport->reconnect_work,
				   1UL * delay * HZ);
	अगर ((fast_io_fail_पंचांगo >= 0 || dev_loss_पंचांगo >= 0) &&
	    srp_rport_set_state(rport, SRP_RPORT_BLOCKED) == 0) अणु
		pr_debug("%s new state: %d\n", dev_name(&shost->shost_gendev),
			 rport->state);
		scsi_target_block(&shost->shost_gendev);
		अगर (fast_io_fail_पंचांगo >= 0)
			queue_delayed_work(प्रणाली_दीर्घ_wq,
					   &rport->fast_io_fail_work,
					   1UL * fast_io_fail_पंचांगo * HZ);
		अगर (dev_loss_पंचांगo >= 0)
			queue_delayed_work(प्रणाली_दीर्घ_wq,
					   &rport->dev_loss_work,
					   1UL * dev_loss_पंचांगo * HZ);
	पूर्ण
पूर्ण

/**
 * srp_start_tl_fail_समयrs() - start the transport layer failure समयrs
 * @rport: SRP target port.
 *
 * Start the transport layer fast I/O failure and device loss समयrs. Do not
 * modअगरy a समयr that was alपढ़ोy started.
 */
व्योम srp_start_tl_fail_समयrs(काष्ठा srp_rport *rport)
अणु
	mutex_lock(&rport->mutex);
	__srp_start_tl_fail_समयrs(rport);
	mutex_unlock(&rport->mutex);
पूर्ण
EXPORT_SYMBOL(srp_start_tl_fail_समयrs);

/**
 * srp_reconnect_rport() - reconnect to an SRP target port
 * @rport: SRP target port.
 *
 * Blocks SCSI command queueing beक्रमe invoking reconnect() such that
 * queuecommand() won't be invoked concurrently with reconnect() from outside
 * the SCSI EH. This is important since a reconnect() implementation may
 * पुनः_स्मृतिate resources needed by queuecommand().
 *
 * Notes:
 * - This function neither रुकोs until outstanding requests have finished nor
 *   tries to पात these. It is the responsibility of the reconnect()
 *   function to finish outstanding commands beक्रमe reconnecting to the target
 *   port.
 * - It is the responsibility of the caller to ensure that the resources
 *   पुनः_स्मृतिated by the reconnect() function won't be used जबतक this function
 *   is in progress. One possible strategy is to invoke this function from
 *   the context of the SCSI EH thपढ़ो only. Another possible strategy is to
 *   lock the rport mutex inside each SCSI LLD callback that can be invoked by
 *   the SCSI EH (the scsi_host_ढाँचा.eh_*() functions and also the
 *   scsi_host_ढाँचा.queuecommand() function).
 */
पूर्णांक srp_reconnect_rport(काष्ठा srp_rport *rport)
अणु
	काष्ठा Scsi_Host *shost = rport_to_shost(rport);
	काष्ठा srp_पूर्णांकernal *i = to_srp_पूर्णांकernal(shost->transportt);
	काष्ठा scsi_device *sdev;
	पूर्णांक res;

	pr_debug("SCSI host %s\n", dev_name(&shost->shost_gendev));

	res = mutex_lock_पूर्णांकerruptible(&rport->mutex);
	अगर (res)
		जाओ out;
	अगर (rport->state != SRP_RPORT_FAIL_FAST && rport->state != SRP_RPORT_LOST)
		/*
		 * sdev state must be SDEV_TRANSPORT_OFFLINE, transition
		 * to SDEV_BLOCK is illegal. Calling scsi_target_unblock()
		 * later is ok though, scsi_पूर्णांकernal_device_unblock_noरुको()
		 * treats SDEV_TRANSPORT_OFFLINE like SDEV_BLOCK.
		 */
		scsi_target_block(&shost->shost_gendev);
	res = rport->state != SRP_RPORT_LOST ? i->f->reconnect(rport) : -ENODEV;
	pr_debug("%s (state %d): transport.reconnect() returned %d\n",
		 dev_name(&shost->shost_gendev), rport->state, res);
	अगर (res == 0) अणु
		cancel_delayed_work(&rport->fast_io_fail_work);
		cancel_delayed_work(&rport->dev_loss_work);

		rport->failed_reconnects = 0;
		srp_rport_set_state(rport, SRP_RPORT_RUNNING);
		scsi_target_unblock(&shost->shost_gendev, SDEV_RUNNING);
		/*
		 * If the SCSI error handler has offlined one or more devices,
		 * invoking scsi_target_unblock() won't change the state of
		 * these devices पूर्णांकo running so करो that explicitly.
		 */
		shost_क्रम_each_device(sdev, shost) अणु
			mutex_lock(&sdev->state_mutex);
			अगर (sdev->sdev_state == SDEV_OFFLINE)
				sdev->sdev_state = SDEV_RUNNING;
			mutex_unlock(&sdev->state_mutex);
		पूर्ण
	पूर्ण अन्यथा अगर (rport->state == SRP_RPORT_RUNNING) अणु
		/*
		 * srp_reconnect_rport() has been invoked with fast_io_fail
		 * and dev_loss off. Mark the port as failed and start the TL
		 * failure समयrs अगर these had not yet been started.
		 */
		__rport_fail_io_fast(rport);
		__srp_start_tl_fail_समयrs(rport);
	पूर्ण अन्यथा अगर (rport->state != SRP_RPORT_BLOCKED) अणु
		scsi_target_unblock(&shost->shost_gendev,
				    SDEV_TRANSPORT_OFFLINE);
	पूर्ण
	mutex_unlock(&rport->mutex);

out:
	वापस res;
पूर्ण
EXPORT_SYMBOL(srp_reconnect_rport);

/**
 * srp_समयd_out() - SRP transport पूर्णांकercept of the SCSI समयout EH
 * @scmd: SCSI command.
 *
 * If a समयout occurs जबतक an rport is in the blocked state, ask the SCSI
 * EH to जारी रुकोing (BLK_EH_RESET_TIMER). Otherwise let the SCSI core
 * handle the समयout (BLK_EH_DONE).
 *
 * Note: This function is called from soft-IRQ context and with the request
 * queue lock held.
 */
क्रमागत blk_eh_समयr_वापस srp_समयd_out(काष्ठा scsi_cmnd *scmd)
अणु
	काष्ठा scsi_device *sdev = scmd->device;
	काष्ठा Scsi_Host *shost = sdev->host;
	काष्ठा srp_पूर्णांकernal *i = to_srp_पूर्णांकernal(shost->transportt);
	काष्ठा srp_rport *rport = shost_to_rport(shost);

	pr_debug("timeout for sdev %s\n", dev_name(&sdev->sdev_gendev));
	वापस rport && rport->fast_io_fail_पंचांगo < 0 &&
		rport->dev_loss_पंचांगo < 0 &&
		i->f->reset_समयr_अगर_blocked && scsi_device_blocked(sdev) ?
		BLK_EH_RESET_TIMER : BLK_EH_DONE;
पूर्ण
EXPORT_SYMBOL(srp_समयd_out);

अटल व्योम srp_rport_release(काष्ठा device *dev)
अणु
	काष्ठा srp_rport *rport = dev_to_rport(dev);

	put_device(dev->parent);
	kमुक्त(rport);
पूर्ण

अटल पूर्णांक scsi_is_srp_rport(स्थिर काष्ठा device *dev)
अणु
	वापस dev->release == srp_rport_release;
पूर्ण

अटल पूर्णांक srp_rport_match(काष्ठा attribute_container *cont,
			   काष्ठा device *dev)
अणु
	काष्ठा Scsi_Host *shost;
	काष्ठा srp_पूर्णांकernal *i;

	अगर (!scsi_is_srp_rport(dev))
		वापस 0;

	shost = dev_to_shost(dev->parent);
	अगर (!shost->transportt)
		वापस 0;
	अगर (shost->transportt->host_attrs.ac.class != &srp_host_class.class)
		वापस 0;

	i = to_srp_पूर्णांकernal(shost->transportt);
	वापस &i->rport_attr_cont.ac == cont;
पूर्ण

अटल पूर्णांक srp_host_match(काष्ठा attribute_container *cont, काष्ठा device *dev)
अणु
	काष्ठा Scsi_Host *shost;
	काष्ठा srp_पूर्णांकernal *i;

	अगर (!scsi_is_host_device(dev))
		वापस 0;

	shost = dev_to_shost(dev);
	अगर (!shost->transportt)
		वापस 0;
	अगर (shost->transportt->host_attrs.ac.class != &srp_host_class.class)
		वापस 0;

	i = to_srp_पूर्णांकernal(shost->transportt);
	वापस &i->t.host_attrs.ac == cont;
पूर्ण

/**
 * srp_rport_get() - increment rport reference count
 * @rport: SRP target port.
 */
व्योम srp_rport_get(काष्ठा srp_rport *rport)
अणु
	get_device(&rport->dev);
पूर्ण
EXPORT_SYMBOL(srp_rport_get);

/**
 * srp_rport_put() - decrement rport reference count
 * @rport: SRP target port.
 */
व्योम srp_rport_put(काष्ठा srp_rport *rport)
अणु
	put_device(&rport->dev);
पूर्ण
EXPORT_SYMBOL(srp_rport_put);

/**
 * srp_rport_add - add a SRP remote port to the device hierarchy
 * @shost:	scsi host the remote port is connected to.
 * @ids:	The port id क्रम the remote port.
 *
 * Publishes a port to the rest of the प्रणाली.
 */
काष्ठा srp_rport *srp_rport_add(काष्ठा Scsi_Host *shost,
				काष्ठा srp_rport_identअगरiers *ids)
अणु
	काष्ठा srp_rport *rport;
	काष्ठा device *parent = &shost->shost_gendev;
	काष्ठा srp_पूर्णांकernal *i = to_srp_पूर्णांकernal(shost->transportt);
	पूर्णांक id, ret;

	rport = kzalloc(माप(*rport), GFP_KERNEL);
	अगर (!rport)
		वापस ERR_PTR(-ENOMEM);

	mutex_init(&rport->mutex);

	device_initialize(&rport->dev);

	rport->dev.parent = get_device(parent);
	rport->dev.release = srp_rport_release;

	स_नकल(rport->port_id, ids->port_id, माप(rport->port_id));
	rport->roles = ids->roles;

	अगर (i->f->reconnect)
		rport->reconnect_delay = i->f->reconnect_delay ?
			*i->f->reconnect_delay : 10;
	INIT_DELAYED_WORK(&rport->reconnect_work, srp_reconnect_work);
	rport->fast_io_fail_पंचांगo = i->f->fast_io_fail_पंचांगo ?
		*i->f->fast_io_fail_पंचांगo : 15;
	rport->dev_loss_पंचांगo = i->f->dev_loss_पंचांगo ? *i->f->dev_loss_पंचांगo : 60;
	INIT_DELAYED_WORK(&rport->fast_io_fail_work,
			  rport_fast_io_fail_समयकरोut);
	INIT_DELAYED_WORK(&rport->dev_loss_work, rport_dev_loss_समयकरोut);

	id = atomic_inc_वापस(&to_srp_host_attrs(shost)->next_port_id);
	dev_set_name(&rport->dev, "port-%d:%d", shost->host_no, id);

	transport_setup_device(&rport->dev);

	ret = device_add(&rport->dev);
	अगर (ret) अणु
		transport_destroy_device(&rport->dev);
		put_device(&rport->dev);
		वापस ERR_PTR(ret);
	पूर्ण

	transport_add_device(&rport->dev);
	transport_configure_device(&rport->dev);

	वापस rport;
पूर्ण
EXPORT_SYMBOL_GPL(srp_rport_add);

/**
 * srp_rport_del  -  हटाओ a SRP remote port
 * @rport:	SRP remote port to हटाओ
 *
 * Removes the specअगरied SRP remote port.
 */
व्योम srp_rport_del(काष्ठा srp_rport *rport)
अणु
	काष्ठा device *dev = &rport->dev;

	transport_हटाओ_device(dev);
	device_del(dev);
	transport_destroy_device(dev);

	put_device(dev);
पूर्ण
EXPORT_SYMBOL_GPL(srp_rport_del);

अटल पूर्णांक करो_srp_rport_del(काष्ठा device *dev, व्योम *data)
अणु
	अगर (scsi_is_srp_rport(dev))
		srp_rport_del(dev_to_rport(dev));
	वापस 0;
पूर्ण

/**
 * srp_हटाओ_host  -  tear करोwn a Scsi_Host's SRP data काष्ठाures
 * @shost:	Scsi Host that is torn करोwn
 *
 * Removes all SRP remote ports क्रम a given Scsi_Host.
 * Must be called just beक्रमe scsi_हटाओ_host क्रम SRP HBAs.
 */
व्योम srp_हटाओ_host(काष्ठा Scsi_Host *shost)
अणु
	device_क्रम_each_child(&shost->shost_gendev, शून्य, करो_srp_rport_del);
पूर्ण
EXPORT_SYMBOL_GPL(srp_हटाओ_host);

/**
 * srp_stop_rport_समयrs - stop the transport layer recovery समयrs
 * @rport: SRP remote port क्रम which to stop the समयrs.
 *
 * Must be called after srp_हटाओ_host() and scsi_हटाओ_host(). The caller
 * must hold a reference on the rport (rport->dev) and on the SCSI host
 * (rport->dev.parent).
 */
व्योम srp_stop_rport_समयrs(काष्ठा srp_rport *rport)
अणु
	mutex_lock(&rport->mutex);
	अगर (rport->state == SRP_RPORT_BLOCKED)
		__rport_fail_io_fast(rport);
	srp_rport_set_state(rport, SRP_RPORT_LOST);
	mutex_unlock(&rport->mutex);

	cancel_delayed_work_sync(&rport->reconnect_work);
	cancel_delayed_work_sync(&rport->fast_io_fail_work);
	cancel_delayed_work_sync(&rport->dev_loss_work);
पूर्ण
EXPORT_SYMBOL_GPL(srp_stop_rport_समयrs);

/**
 * srp_attach_transport  -  instantiate SRP transport ढाँचा
 * @ft:		SRP transport class function ढाँचा
 */
काष्ठा scsi_transport_ढाँचा *
srp_attach_transport(काष्ठा srp_function_ढाँचा *ft)
अणु
	पूर्णांक count;
	काष्ठा srp_पूर्णांकernal *i;

	i = kzalloc(माप(*i), GFP_KERNEL);
	अगर (!i)
		वापस शून्य;

	i->t.host_size = माप(काष्ठा srp_host_attrs);
	i->t.host_attrs.ac.attrs = &i->host_attrs[0];
	i->t.host_attrs.ac.class = &srp_host_class.class;
	i->t.host_attrs.ac.match = srp_host_match;
	i->host_attrs[0] = शून्य;
	transport_container_रेजिस्टर(&i->t.host_attrs);

	i->rport_attr_cont.ac.attrs = &i->rport_attrs[0];
	i->rport_attr_cont.ac.class = &srp_rport_class.class;
	i->rport_attr_cont.ac.match = srp_rport_match;

	count = 0;
	i->rport_attrs[count++] = &dev_attr_port_id;
	i->rport_attrs[count++] = &dev_attr_roles;
	अगर (ft->has_rport_state) अणु
		i->rport_attrs[count++] = &dev_attr_state;
		i->rport_attrs[count++] = &dev_attr_fast_io_fail_पंचांगo;
		i->rport_attrs[count++] = &dev_attr_dev_loss_पंचांगo;
	पूर्ण
	अगर (ft->reconnect) अणु
		i->rport_attrs[count++] = &dev_attr_reconnect_delay;
		i->rport_attrs[count++] = &dev_attr_failed_reconnects;
	पूर्ण
	अगर (ft->rport_delete)
		i->rport_attrs[count++] = &dev_attr_delete;
	i->rport_attrs[count++] = शून्य;
	BUG_ON(count > ARRAY_SIZE(i->rport_attrs));

	transport_container_रेजिस्टर(&i->rport_attr_cont);

	i->f = ft;

	वापस &i->t;
पूर्ण
EXPORT_SYMBOL_GPL(srp_attach_transport);

/**
 * srp_release_transport  -  release SRP transport ढाँचा instance
 * @t:		transport ढाँचा instance
 */
व्योम srp_release_transport(काष्ठा scsi_transport_ढाँचा *t)
अणु
	काष्ठा srp_पूर्णांकernal *i = to_srp_पूर्णांकernal(t);

	transport_container_unरेजिस्टर(&i->t.host_attrs);
	transport_container_unरेजिस्टर(&i->rport_attr_cont);

	kमुक्त(i);
पूर्ण
EXPORT_SYMBOL_GPL(srp_release_transport);

अटल __init पूर्णांक srp_transport_init(व्योम)
अणु
	पूर्णांक ret;

	ret = transport_class_रेजिस्टर(&srp_host_class);
	अगर (ret)
		वापस ret;
	ret = transport_class_रेजिस्टर(&srp_rport_class);
	अगर (ret)
		जाओ unरेजिस्टर_host_class;

	वापस 0;
unरेजिस्टर_host_class:
	transport_class_unरेजिस्टर(&srp_host_class);
	वापस ret;
पूर्ण

अटल व्योम __निकास srp_transport_निकास(व्योम)
अणु
	transport_class_unरेजिस्टर(&srp_host_class);
	transport_class_unरेजिस्टर(&srp_rport_class);
पूर्ण

MODULE_AUTHOR("FUJITA Tomonori");
MODULE_DESCRIPTION("SRP Transport Attributes");
MODULE_LICENSE("GPL");

module_init(srp_transport_init);
module_निकास(srp_transport_निकास);
