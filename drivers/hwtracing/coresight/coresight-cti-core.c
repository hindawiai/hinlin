<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2018 Linaro Limited, All rights reserved.
 * Author: Mike Leach <mike.leach@linaro.org>
 */

#समावेश <linux/amba/bus.h>
#समावेश <linux/atomic.h>
#समावेश <linux/bits.h>
#समावेश <linux/coresight.h>
#समावेश <linux/cpu_pm.h>
#समावेश <linux/cpuhotplug.h>
#समावेश <linux/device.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/mutex.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/property.h>
#समावेश <linux/spinlock.h>

#समावेश "coresight-priv.h"
#समावेश "coresight-cti.h"

/**
 * CTI devices can be associated with a PE, or be connected to CoreSight
 * hardware. We have a list of all CTIs irrespective of CPU bound or
 * otherwise.
 *
 * We assume that the non-CPU CTIs are always घातered as we करो with sinks etc.
 *
 * We leave the client to figure out अगर all the CTIs are पूर्णांकerconnected with
 * the same CTM, in general this is the हाल but करोes not always have to be.
 */

/* net of CTI devices connected via CTM */
अटल LIST_HEAD(ect_net);

/* protect the list */
अटल DEFINE_MUTEX(ect_mutex);

#घोषणा csdev_to_cti_drvdata(csdev)	\
	dev_get_drvdata(csdev->dev.parent)

/* घातer management handling */
अटल पूर्णांक nr_cti_cpu;

/* quick lookup list क्रम CPU bound CTIs when घातer handling */
अटल काष्ठा cti_drvdata *cti_cpu_drvdata[NR_CPUS];

/*
 * CTI naming. CTI bound to cores will have the name cti_cpu<N> where
 * N is the CPU ID. System CTIs will have the name cti_sys<I> where I
 * is an index allocated by order of discovery.
 *
 * CTI device name list - क्रम CTI not bound to cores.
 */
DEFINE_CORESIGHT_DEVLIST(cti_sys_devs, "cti_sys");

/* ग_लिखो set of regs to hardware - call with spinlock claimed */
व्योम cti_ग_लिखो_all_hw_regs(काष्ठा cti_drvdata *drvdata)
अणु
	काष्ठा cti_config *config = &drvdata->config;
	पूर्णांक i;

	CS_UNLOCK(drvdata->base);

	/* disable CTI beक्रमe writing रेजिस्टरs */
	ग_लिखोl_relaxed(0, drvdata->base + CTICONTROL);

	/* ग_लिखो the CTI trigger रेजिस्टरs */
	क्रम (i = 0; i < config->nr_trig_max; i++) अणु
		ग_लिखोl_relaxed(config->ctiinen[i], drvdata->base + CTIINEN(i));
		ग_लिखोl_relaxed(config->ctiouten[i],
			       drvdata->base + CTIOUTEN(i));
	पूर्ण

	/* other regs */
	ग_लिखोl_relaxed(config->ctigate, drvdata->base + CTIGATE);
	ग_लिखोl_relaxed(config->asicctl, drvdata->base + ASICCTL);
	ग_लिखोl_relaxed(config->ctiappset, drvdata->base + CTIAPPSET);

	/* re-enable CTI */
	ग_लिखोl_relaxed(1, drvdata->base + CTICONTROL);

	CS_LOCK(drvdata->base);
पूर्ण

/* ग_लिखो regs to hardware and enable */
अटल पूर्णांक cti_enable_hw(काष्ठा cti_drvdata *drvdata)
अणु
	काष्ठा cti_config *config = &drvdata->config;
	काष्ठा device *dev = &drvdata->csdev->dev;
	अचिन्हित दीर्घ flags;
	पूर्णांक rc = 0;

	pm_runसमय_get_sync(dev->parent);
	spin_lock_irqsave(&drvdata->spinlock, flags);

	/* no need to करो anything अगर enabled or unघातered*/
	अगर (config->hw_enabled || !config->hw_घातered)
		जाओ cti_state_unchanged;

	/* claim the device */
	rc = coresight_claim_device(drvdata->csdev);
	अगर (rc)
		जाओ cti_err_not_enabled;

	cti_ग_लिखो_all_hw_regs(drvdata);

	config->hw_enabled = true;
	atomic_inc(&drvdata->config.enable_req_count);
	spin_unlock_irqrestore(&drvdata->spinlock, flags);
	वापस rc;

cti_state_unchanged:
	atomic_inc(&drvdata->config.enable_req_count);

	/* cannot enable due to error */
cti_err_not_enabled:
	spin_unlock_irqrestore(&drvdata->spinlock, flags);
	pm_runसमय_put(dev->parent);
	वापस rc;
पूर्ण

/* re-enable CTI on CPU when using CPU hotplug */
अटल व्योम cti_cpuhp_enable_hw(काष्ठा cti_drvdata *drvdata)
अणु
	काष्ठा cti_config *config = &drvdata->config;

	spin_lock(&drvdata->spinlock);
	config->hw_घातered = true;

	/* no need to करो anything अगर no enable request */
	अगर (!atomic_पढ़ो(&drvdata->config.enable_req_count))
		जाओ cti_hp_not_enabled;

	/* try to claim the device */
	अगर (coresight_claim_device(drvdata->csdev))
		जाओ cti_hp_not_enabled;

	cti_ग_लिखो_all_hw_regs(drvdata);
	config->hw_enabled = true;
	spin_unlock(&drvdata->spinlock);
	वापस;

	/* did not re-enable due to no claim / no request */
cti_hp_not_enabled:
	spin_unlock(&drvdata->spinlock);
पूर्ण

/* disable hardware */
अटल पूर्णांक cti_disable_hw(काष्ठा cti_drvdata *drvdata)
अणु
	काष्ठा cti_config *config = &drvdata->config;
	काष्ठा device *dev = &drvdata->csdev->dev;
	काष्ठा coresight_device *csdev = drvdata->csdev;

	spin_lock(&drvdata->spinlock);

	/* check refcount - disable on 0 */
	अगर (atomic_dec_वापस(&drvdata->config.enable_req_count) > 0)
		जाओ cti_not_disabled;

	/* no need to करो anything अगर disabled or cpu unघातered */
	अगर (!config->hw_enabled || !config->hw_घातered)
		जाओ cti_not_disabled;

	CS_UNLOCK(drvdata->base);

	/* disable CTI */
	ग_लिखोl_relaxed(0, drvdata->base + CTICONTROL);
	config->hw_enabled = false;

	coresight_disclaim_device_unlocked(csdev);
	CS_LOCK(drvdata->base);
	spin_unlock(&drvdata->spinlock);
	pm_runसमय_put(dev);
	वापस 0;

	/* not disabled this call */
cti_not_disabled:
	spin_unlock(&drvdata->spinlock);
	वापस 0;
पूर्ण

व्योम cti_ग_लिखो_single_reg(काष्ठा cti_drvdata *drvdata, पूर्णांक offset, u32 value)
अणु
	CS_UNLOCK(drvdata->base);
	ग_लिखोl_relaxed(value, drvdata->base + offset);
	CS_LOCK(drvdata->base);
पूर्ण

व्योम cti_ग_लिखो_पूर्णांकack(काष्ठा device *dev, u32 ackval)
अणु
	काष्ठा cti_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा cti_config *config = &drvdata->config;

	spin_lock(&drvdata->spinlock);
	/* ग_लिखो अगर enabled */
	अगर (cti_active(config))
		cti_ग_लिखो_single_reg(drvdata, CTIINTACK, ackval);
	spin_unlock(&drvdata->spinlock);
पूर्ण

/*
 * Look at the HW DEVID रेजिस्टर क्रम some of the HW settings.
 * DEVID[15:8] - max number of in / out triggers.
 */
#घोषणा CTI_DEVID_MAXTRIGS(devid_val) ((पूर्णांक) BMVAL(devid_val, 8, 15))

/* DEVID[19:16] - number of CTM channels */
#घोषणा CTI_DEVID_CTMCHANNELS(devid_val) ((पूर्णांक) BMVAL(devid_val, 16, 19))

अटल व्योम cti_set_शेष_config(काष्ठा device *dev,
				   काष्ठा cti_drvdata *drvdata)
अणु
	काष्ठा cti_config *config = &drvdata->config;
	u32 devid;

	devid = पढ़ोl_relaxed(drvdata->base + CORESIGHT_DEVID);
	config->nr_trig_max = CTI_DEVID_MAXTRIGS(devid);

	/*
	 * no current hardware should exceed this, but protect the driver
	 * in हाल of fault / out of spec hw
	 */
	अगर (config->nr_trig_max > CTIINOUTEN_MAX) अणु
		dev_warn_once(dev,
			"Limiting HW MaxTrig value(%d) to driver max(%d)\n",
			config->nr_trig_max, CTIINOUTEN_MAX);
		config->nr_trig_max = CTIINOUTEN_MAX;
	पूर्ण

	config->nr_cपंचांग_channels = CTI_DEVID_CTMCHANNELS(devid);

	/* Most regs शेष to 0 as zalloc'ed except...*/
	config->trig_filter_enable = true;
	config->ctigate = GENMASK(config->nr_cपंचांग_channels - 1, 0);
	atomic_set(&config->enable_req_count, 0);
पूर्ण

/*
 * Add a connection entry to the list of connections क्रम this
 * CTI device.
 */
पूर्णांक cti_add_connection_entry(काष्ठा device *dev, काष्ठा cti_drvdata *drvdata,
			     काष्ठा cti_trig_con *tc,
			     काष्ठा coresight_device *csdev,
			     स्थिर अक्षर *assoc_dev_name)
अणु
	काष्ठा cti_device *cti_dev = &drvdata->ctidev;

	tc->con_dev = csdev;
	/*
	 * Prefer actual associated CS device dev name to supplied value -
	 * which is likely to be node name / other conn name.
	 */
	अगर (csdev)
		tc->con_dev_name = dev_name(&csdev->dev);
	अन्यथा अगर (assoc_dev_name != शून्य) अणु
		tc->con_dev_name = devm_kstrdup(dev,
						assoc_dev_name, GFP_KERNEL);
		अगर (!tc->con_dev_name)
			वापस -ENOMEM;
	पूर्ण
	list_add_tail(&tc->node, &cti_dev->trig_cons);
	cti_dev->nr_trig_con++;

	/* add connection usage bit info to overall info */
	drvdata->config.trig_in_use |= tc->con_in->used_mask;
	drvdata->config.trig_out_use |= tc->con_out->used_mask;

	वापस 0;
पूर्ण

/* create a trigger connection with appropriately sized संकेत groups */
काष्ठा cti_trig_con *cti_allocate_trig_con(काष्ठा device *dev, पूर्णांक in_sigs,
					   पूर्णांक out_sigs)
अणु
	काष्ठा cti_trig_con *tc = शून्य;
	काष्ठा cti_trig_grp *in = शून्य, *out = शून्य;

	tc = devm_kzalloc(dev, माप(काष्ठा cti_trig_con), GFP_KERNEL);
	अगर (!tc)
		वापस tc;

	in = devm_kzalloc(dev,
			  दुरत्व(काष्ठा cti_trig_grp, sig_types[in_sigs]),
			  GFP_KERNEL);
	अगर (!in)
		वापस शून्य;

	out = devm_kzalloc(dev,
			   दुरत्व(काष्ठा cti_trig_grp, sig_types[out_sigs]),
			   GFP_KERNEL);
	अगर (!out)
		वापस शून्य;

	tc->con_in = in;
	tc->con_out = out;
	tc->con_in->nr_sigs = in_sigs;
	tc->con_out->nr_sigs = out_sigs;
	वापस tc;
पूर्ण

/*
 * Add a शेष connection अगर nothing अन्यथा is specअगरied.
 * single connection based on max in/out info, no assoc device
 */
पूर्णांक cti_add_शेष_connection(काष्ठा device *dev, काष्ठा cti_drvdata *drvdata)
अणु
	पूर्णांक ret = 0;
	पूर्णांक n_trigs = drvdata->config.nr_trig_max;
	u32 n_trig_mask = GENMASK(n_trigs - 1, 0);
	काष्ठा cti_trig_con *tc = शून्य;

	/*
	 * Assume max trigs क्रम in and out,
	 * all used, शेष sig types allocated
	 */
	tc = cti_allocate_trig_con(dev, n_trigs, n_trigs);
	अगर (!tc)
		वापस -ENOMEM;

	tc->con_in->used_mask = n_trig_mask;
	tc->con_out->used_mask = n_trig_mask;
	ret = cti_add_connection_entry(dev, drvdata, tc, शून्य, "default");
	वापस ret;
पूर्ण

/** cti channel api **/
/* attach/detach channel from trigger - ग_लिखो through अगर enabled. */
पूर्णांक cti_channel_trig_op(काष्ठा device *dev, क्रमागत cti_chan_op op,
			क्रमागत cti_trig_dir direction, u32 channel_idx,
			u32 trigger_idx)
अणु
	काष्ठा cti_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा cti_config *config = &drvdata->config;
	u32 trig_biपंचांगask;
	u32 chan_biपंचांगask;
	u32 reg_value;
	पूर्णांक reg_offset;

	/* ensure indexes in range */
	अगर ((channel_idx >= config->nr_cपंचांग_channels) ||
	   (trigger_idx >= config->nr_trig_max))
		वापस -EINVAL;

	trig_biपंचांगask = BIT(trigger_idx);

	/* ensure रेजिस्टरed triggers and not out filtered */
	अगर (direction == CTI_TRIG_IN)	अणु
		अगर (!(trig_biपंचांगask & config->trig_in_use))
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		अगर (!(trig_biपंचांगask & config->trig_out_use))
			वापस -EINVAL;

		अगर ((config->trig_filter_enable) &&
		    (config->trig_out_filter & trig_biपंचांगask))
			वापस -EINVAL;
	पूर्ण

	/* update the local रेजिस्टर values */
	chan_biपंचांगask = BIT(channel_idx);
	reg_offset = (direction == CTI_TRIG_IN ? CTIINEN(trigger_idx) :
		      CTIOUTEN(trigger_idx));

	spin_lock(&drvdata->spinlock);

	/* पढ़ो - modअगरy ग_लिखो - the trigger / channel enable value */
	reg_value = direction == CTI_TRIG_IN ? config->ctiinen[trigger_idx] :
		     config->ctiouten[trigger_idx];
	अगर (op == CTI_CHAN_ATTACH)
		reg_value |= chan_biपंचांगask;
	अन्यथा
		reg_value &= ~chan_biपंचांगask;

	/* ग_लिखो local copy */
	अगर (direction == CTI_TRIG_IN)
		config->ctiinen[trigger_idx] = reg_value;
	अन्यथा
		config->ctiouten[trigger_idx] = reg_value;

	/* ग_लिखो through अगर enabled */
	अगर (cti_active(config))
		cti_ग_लिखो_single_reg(drvdata, reg_offset, reg_value);
	spin_unlock(&drvdata->spinlock);
	वापस 0;
पूर्ण

पूर्णांक cti_channel_gate_op(काष्ठा device *dev, क्रमागत cti_chan_gate_op op,
			u32 channel_idx)
अणु
	काष्ठा cti_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा cti_config *config = &drvdata->config;
	u32 chan_biपंचांगask;
	u32 reg_value;
	पूर्णांक err = 0;

	अगर (channel_idx >= config->nr_cपंचांग_channels)
		वापस -EINVAL;

	chan_biपंचांगask = BIT(channel_idx);

	spin_lock(&drvdata->spinlock);
	reg_value = config->ctigate;
	चयन (op) अणु
	हाल CTI_GATE_CHAN_ENABLE:
		reg_value |= chan_biपंचांगask;
		अवरोध;

	हाल CTI_GATE_CHAN_DISABLE:
		reg_value &= ~chan_biपंचांगask;
		अवरोध;

	शेष:
		err = -EINVAL;
		अवरोध;
	पूर्ण
	अगर (err == 0) अणु
		config->ctigate = reg_value;
		अगर (cti_active(config))
			cti_ग_लिखो_single_reg(drvdata, CTIGATE, reg_value);
	पूर्ण
	spin_unlock(&drvdata->spinlock);
	वापस err;
पूर्ण

पूर्णांक cti_channel_setop(काष्ठा device *dev, क्रमागत cti_chan_set_op op,
		      u32 channel_idx)
अणु
	काष्ठा cti_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा cti_config *config = &drvdata->config;
	u32 chan_biपंचांगask;
	u32 reg_value;
	u32 reg_offset;
	पूर्णांक err = 0;

	अगर (channel_idx >= config->nr_cपंचांग_channels)
		वापस -EINVAL;

	chan_biपंचांगask = BIT(channel_idx);

	spin_lock(&drvdata->spinlock);
	reg_value = config->ctiappset;
	चयन (op) अणु
	हाल CTI_CHAN_SET:
		config->ctiappset |= chan_biपंचांगask;
		reg_value  = config->ctiappset;
		reg_offset = CTIAPPSET;
		अवरोध;

	हाल CTI_CHAN_CLR:
		config->ctiappset &= ~chan_biपंचांगask;
		reg_value = chan_biपंचांगask;
		reg_offset = CTIAPPCLEAR;
		अवरोध;

	हाल CTI_CHAN_PULSE:
		config->ctiappset &= ~chan_biपंचांगask;
		reg_value = chan_biपंचांगask;
		reg_offset = CTIAPPPULSE;
		अवरोध;

	शेष:
		err = -EINVAL;
		अवरोध;
	पूर्ण

	अगर ((err == 0) && cti_active(config))
		cti_ग_लिखो_single_reg(drvdata, reg_offset, reg_value);
	spin_unlock(&drvdata->spinlock);

	वापस err;
पूर्ण

अटल bool cti_add_sysfs_link(काष्ठा cti_drvdata *drvdata,
			       काष्ठा cti_trig_con *tc)
अणु
	काष्ठा coresight_sysfs_link link_info;
	पूर्णांक link_err = 0;

	link_info.orig = drvdata->csdev;
	link_info.orig_name = tc->con_dev_name;
	link_info.target = tc->con_dev;
	link_info.target_name = dev_name(&drvdata->csdev->dev);

	link_err = coresight_add_sysfs_link(&link_info);
	अगर (link_err)
		dev_warn(&drvdata->csdev->dev,
			 "Failed to set CTI sysfs link %s<=>%s\n",
			 link_info.orig_name, link_info.target_name);
	वापस !link_err;
पूर्ण

अटल व्योम cti_हटाओ_sysfs_link(काष्ठा cti_drvdata *drvdata,
				  काष्ठा cti_trig_con *tc)
अणु
	काष्ठा coresight_sysfs_link link_info;

	link_info.orig = drvdata->csdev;
	link_info.orig_name = tc->con_dev_name;
	link_info.target = tc->con_dev;
	link_info.target_name = dev_name(&drvdata->csdev->dev);
	coresight_हटाओ_sysfs_link(&link_info);
पूर्ण

/*
 * Look क्रम a matching connection device name in the list of connections.
 * If found then swap in the csdev name, set trig con association poपूर्णांकer
 * and वापस found.
 */
अटल bool
cti_match_fixup_csdev(काष्ठा cti_device *ctidev, स्थिर अक्षर *node_name,
		      काष्ठा coresight_device *csdev)
अणु
	काष्ठा cti_trig_con *tc;
	काष्ठा cti_drvdata *drvdata = container_of(ctidev, काष्ठा cti_drvdata,
						   ctidev);

	list_क्रम_each_entry(tc, &ctidev->trig_cons, node) अणु
		अगर (tc->con_dev_name) अणु
			अगर (!म_भेद(node_name, tc->con_dev_name)) अणु
				/* match: so swap in csdev name & dev */
				tc->con_dev_name = dev_name(&csdev->dev);
				tc->con_dev = csdev;
				/* try to set sysfs link */
				अगर (cti_add_sysfs_link(drvdata, tc))
					वापस true;
				/* link failed - हटाओ CTI reference */
				tc->con_dev = शून्य;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण

/*
 * Search the cti list to add an associated CTI पूर्णांकo the supplied CS device
 * This will set the association अगर CTI declared beक्रमe the CS device.
 * (called from coresight_रेजिस्टर() with coresight_mutex locked).
 */
अटल व्योम cti_add_assoc_to_csdev(काष्ठा coresight_device *csdev)
अणु
	काष्ठा cti_drvdata *ect_item;
	काष्ठा cti_device *ctidev;
	स्थिर अक्षर *node_name = शून्य;

	/* protect the list */
	mutex_lock(&ect_mutex);

	/* निकास अगर current is an ECT device.*/
	अगर ((csdev->type == CORESIGHT_DEV_TYPE_ECT) || list_empty(&ect_net))
		जाओ cti_add_करोne;

	/* अगर we didn't find the csdev previously we used the fwnode name */
	node_name = cti_plat_get_node_name(dev_fwnode(csdev->dev.parent));
	अगर (!node_name)
		जाओ cti_add_करोne;

	/* क्रम each CTI in list... */
	list_क्रम_each_entry(ect_item, &ect_net, node) अणु
		ctidev = &ect_item->ctidev;
		अगर (cti_match_fixup_csdev(ctidev, node_name, csdev)) अणु
			/*
			 * अगर we found a matching csdev then update the ECT
			 * association poपूर्णांकer क्रम the device with this CTI.
			 */
			csdev->ect_dev = ect_item->csdev;
			अवरोध;
		पूर्ण
	पूर्ण
cti_add_करोne:
	mutex_unlock(&ect_mutex);
पूर्ण

/*
 * Removing the associated devices is easier.
 * A CTI will not have a value क्रम csdev->ect_dev.
 */
अटल व्योम cti_हटाओ_assoc_from_csdev(काष्ठा coresight_device *csdev)
अणु
	काष्ठा cti_drvdata *ctidrv;
	काष्ठा cti_trig_con *tc;
	काष्ठा cti_device *ctidev;

	mutex_lock(&ect_mutex);
	अगर (csdev->ect_dev) अणु
		ctidrv = csdev_to_cti_drvdata(csdev->ect_dev);
		ctidev = &ctidrv->ctidev;
		list_क्रम_each_entry(tc, &ctidev->trig_cons, node) अणु
			अगर (tc->con_dev == csdev) अणु
				cti_हटाओ_sysfs_link(ctidrv, tc);
				tc->con_dev = शून्य;
				अवरोध;
			पूर्ण
		पूर्ण
		csdev->ect_dev = शून्य;
	पूर्ण
	mutex_unlock(&ect_mutex);
पूर्ण

/*
 * Operations to add and हटाओ associated CTI.
 * Register to coresight core driver as call back function.
 */
अटल काष्ठा cti_assoc_op cti_assoc_ops = अणु
	.add = cti_add_assoc_to_csdev,
	.हटाओ = cti_हटाओ_assoc_from_csdev
पूर्ण;

/*
 * Update the cross references where the associated device was found
 * जबतक we were building the connection info. This will occur अगर the
 * assoc device was रेजिस्टरed beक्रमe the CTI.
 */
अटल व्योम cti_update_conn_xrefs(काष्ठा cti_drvdata *drvdata)
अणु
	काष्ठा cti_trig_con *tc;
	काष्ठा cti_device *ctidev = &drvdata->ctidev;

	list_क्रम_each_entry(tc, &ctidev->trig_cons, node) अणु
		अगर (tc->con_dev) अणु
			/* अगर we can set the sysfs link */
			अगर (cti_add_sysfs_link(drvdata, tc))
				/* set the CTI/csdev association */
				coresight_set_assoc_ectdev_mutex(tc->con_dev,
							 drvdata->csdev);
			अन्यथा
				/* otherwise हटाओ reference from CTI */
				tc->con_dev = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम cti_हटाओ_conn_xrefs(काष्ठा cti_drvdata *drvdata)
अणु
	काष्ठा cti_trig_con *tc;
	काष्ठा cti_device *ctidev = &drvdata->ctidev;

	list_क्रम_each_entry(tc, &ctidev->trig_cons, node) अणु
		अगर (tc->con_dev) अणु
			coresight_set_assoc_ectdev_mutex(tc->con_dev,
							 शून्य);
			cti_हटाओ_sysfs_link(drvdata, tc);
			tc->con_dev = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

/** cti PM callbacks **/
अटल पूर्णांक cti_cpu_pm_notअगरy(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ cmd,
			     व्योम *v)
अणु
	काष्ठा cti_drvdata *drvdata;
	काष्ठा coresight_device *csdev;
	अचिन्हित पूर्णांक cpu = smp_processor_id();
	पूर्णांक notअगरy_res = NOTIFY_OK;

	अगर (!cti_cpu_drvdata[cpu])
		वापस NOTIFY_OK;

	drvdata = cti_cpu_drvdata[cpu];
	csdev = drvdata->csdev;

	अगर (WARN_ON_ONCE(drvdata->ctidev.cpu != cpu))
		वापस NOTIFY_BAD;

	spin_lock(&drvdata->spinlock);

	चयन (cmd) अणु
	हाल CPU_PM_ENTER:
		/* CTI regs all अटल - we have a copy & nothing to save */
		drvdata->config.hw_घातered = false;
		अगर (drvdata->config.hw_enabled)
			coresight_disclaim_device(csdev);
		अवरोध;

	हाल CPU_PM_ENTER_FAILED:
		drvdata->config.hw_घातered = true;
		अगर (drvdata->config.hw_enabled) अणु
			अगर (coresight_claim_device(csdev))
				drvdata->config.hw_enabled = false;
		पूर्ण
		अवरोध;

	हाल CPU_PM_EXIT:
		/* ग_लिखो hardware रेजिस्टरs to re-enable. */
		drvdata->config.hw_घातered = true;
		drvdata->config.hw_enabled = false;

		/* check enable reference count to enable HW */
		अगर (atomic_पढ़ो(&drvdata->config.enable_req_count)) अणु
			/* check we can claim the device as we re-घातer */
			अगर (coresight_claim_device(csdev))
				जाओ cti_notअगरy_निकास;

			drvdata->config.hw_enabled = true;
			cti_ग_लिखो_all_hw_regs(drvdata);
		पूर्ण
		अवरोध;

	शेष:
		notअगरy_res = NOTIFY_DONE;
		अवरोध;
	पूर्ण

cti_notअगरy_निकास:
	spin_unlock(&drvdata->spinlock);
	वापस notअगरy_res;
पूर्ण

अटल काष्ठा notअगरier_block cti_cpu_pm_nb = अणु
	.notअगरier_call = cti_cpu_pm_notअगरy,
पूर्ण;

/* CPU HP handlers */
अटल पूर्णांक cti_starting_cpu(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा cti_drvdata *drvdata = cti_cpu_drvdata[cpu];

	अगर (!drvdata)
		वापस 0;

	cti_cpuhp_enable_hw(drvdata);
	वापस 0;
पूर्ण

अटल पूर्णांक cti_dying_cpu(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा cti_drvdata *drvdata = cti_cpu_drvdata[cpu];

	अगर (!drvdata)
		वापस 0;

	spin_lock(&drvdata->spinlock);
	drvdata->config.hw_घातered = false;
	अगर (drvdata->config.hw_enabled)
		coresight_disclaim_device(drvdata->csdev);
	spin_unlock(&drvdata->spinlock);
	वापस 0;
पूर्ण

अटल पूर्णांक cti_pm_setup(काष्ठा cti_drvdata *drvdata)
अणु
	पूर्णांक ret;

	अगर (drvdata->ctidev.cpu == -1)
		वापस 0;

	अगर (nr_cti_cpu)
		जाओ करोne;

	cpus_पढ़ो_lock();
	ret = cpuhp_setup_state_nocalls_cpuslocked(
			CPUHP_AP_ARM_CORESIGHT_CTI_STARTING,
			"arm/coresight_cti:starting",
			cti_starting_cpu, cti_dying_cpu);
	अगर (ret) अणु
		cpus_पढ़ो_unlock();
		वापस ret;
	पूर्ण

	ret = cpu_pm_रेजिस्टर_notअगरier(&cti_cpu_pm_nb);
	cpus_पढ़ो_unlock();
	अगर (ret) अणु
		cpuhp_हटाओ_state_nocalls(CPUHP_AP_ARM_CORESIGHT_CTI_STARTING);
		वापस ret;
	पूर्ण

करोne:
	nr_cti_cpu++;
	cti_cpu_drvdata[drvdata->ctidev.cpu] = drvdata;

	वापस 0;
पूर्ण

/* release PM registrations */
अटल व्योम cti_pm_release(काष्ठा cti_drvdata *drvdata)
अणु
	अगर (drvdata->ctidev.cpu == -1)
		वापस;

	cti_cpu_drvdata[drvdata->ctidev.cpu] = शून्य;
	अगर (--nr_cti_cpu == 0) अणु
		cpu_pm_unरेजिस्टर_notअगरier(&cti_cpu_pm_nb);
		cpuhp_हटाओ_state_nocalls(CPUHP_AP_ARM_CORESIGHT_CTI_STARTING);
	पूर्ण
पूर्ण

/** cti ect operations **/
पूर्णांक cti_enable(काष्ठा coresight_device *csdev)
अणु
	काष्ठा cti_drvdata *drvdata = csdev_to_cti_drvdata(csdev);

	वापस cti_enable_hw(drvdata);
पूर्ण

पूर्णांक cti_disable(काष्ठा coresight_device *csdev)
अणु
	काष्ठा cti_drvdata *drvdata = csdev_to_cti_drvdata(csdev);

	वापस cti_disable_hw(drvdata);
पूर्ण

अटल स्थिर काष्ठा coresight_ops_ect cti_ops_ect = अणु
	.enable = cti_enable,
	.disable = cti_disable,
पूर्ण;

अटल स्थिर काष्ठा coresight_ops cti_ops = अणु
	.ect_ops = &cti_ops_ect,
पूर्ण;

/*
 * Free up CTI specअगरic resources
 * called by dev->release, need to call करोwn to underlying csdev release.
 */
अटल व्योम cti_device_release(काष्ठा device *dev)
अणु
	काष्ठा cti_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा cti_drvdata *ect_item, *ect_पंचांगp;

	mutex_lock(&ect_mutex);
	cti_pm_release(drvdata);

	/* हटाओ from the list */
	list_क्रम_each_entry_safe(ect_item, ect_पंचांगp, &ect_net, node) अणु
		अगर (ect_item == drvdata) अणु
			list_del(&ect_item->node);
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&ect_mutex);

	अगर (drvdata->csdev_release)
		drvdata->csdev_release(dev);
पूर्ण
अटल व्योम cti_हटाओ(काष्ठा amba_device *adev)
अणु
	काष्ठा cti_drvdata *drvdata = dev_get_drvdata(&adev->dev);

	mutex_lock(&ect_mutex);
	cti_हटाओ_conn_xrefs(drvdata);
	mutex_unlock(&ect_mutex);

	coresight_unरेजिस्टर(drvdata->csdev);
पूर्ण

अटल पूर्णांक cti_probe(काष्ठा amba_device *adev, स्थिर काष्ठा amba_id *id)
अणु
	पूर्णांक ret = 0;
	व्योम __iomem *base;
	काष्ठा device *dev = &adev->dev;
	काष्ठा cti_drvdata *drvdata = शून्य;
	काष्ठा coresight_desc cti_desc;
	काष्ठा coresight_platक्रमm_data *pdata = शून्य;
	काष्ठा resource *res = &adev->res;

	/* driver data*/
	drvdata = devm_kzalloc(dev, माप(*drvdata), GFP_KERNEL);
	अगर (!drvdata)
		वापस -ENOMEM;

	/* Validity क्रम the resource is alपढ़ोy checked by the AMBA core */
	base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	drvdata->base = base;
	cti_desc.access = CSDEV_ACCESS_IOMEM(base);

	dev_set_drvdata(dev, drvdata);

	/* शेष CTI device info  */
	drvdata->ctidev.cpu = -1;
	drvdata->ctidev.nr_trig_con = 0;
	drvdata->ctidev.cपंचांग_id = 0;
	INIT_LIST_HEAD(&drvdata->ctidev.trig_cons);

	spin_lock_init(&drvdata->spinlock);

	/* initialise CTI driver config values */
	cti_set_शेष_config(dev, drvdata);

	pdata = coresight_cti_get_platक्रमm_data(dev);
	अगर (IS_ERR(pdata)) अणु
		dev_err(dev, "coresight_cti_get_platform_data err\n");
		वापस  PTR_ERR(pdata);
	पूर्ण

	/* शेष to घातered - could change on PM notअगरications */
	drvdata->config.hw_घातered = true;

	/* set up device name - will depend अगर cpu bound or otherwise */
	अगर (drvdata->ctidev.cpu >= 0)
		cti_desc.name = devm_kaप्र_लिखो(dev, GFP_KERNEL, "cti_cpu%d",
					       drvdata->ctidev.cpu);
	अन्यथा
		cti_desc.name = coresight_alloc_device_name(&cti_sys_devs, dev);
	अगर (!cti_desc.name)
		वापस -ENOMEM;

	/* setup CPU घातer management handling क्रम CPU bound CTI devices. */
	ret = cti_pm_setup(drvdata);
	अगर (ret)
		वापस ret;

	/* create dynamic attributes क्रम connections */
	ret = cti_create_cons_sysfs(dev, drvdata);
	अगर (ret) अणु
		dev_err(dev, "%s: create dynamic sysfs entries failed\n",
			cti_desc.name);
		जाओ pm_release;
	पूर्ण

	/* set up coresight component description */
	cti_desc.pdata = pdata;
	cti_desc.type = CORESIGHT_DEV_TYPE_ECT;
	cti_desc.subtype.ect_subtype = CORESIGHT_DEV_SUBTYPE_ECT_CTI;
	cti_desc.ops = &cti_ops;
	cti_desc.groups = drvdata->ctidev.con_groups;
	cti_desc.dev = dev;
	drvdata->csdev = coresight_रेजिस्टर(&cti_desc);
	अगर (IS_ERR(drvdata->csdev)) अणु
		ret = PTR_ERR(drvdata->csdev);
		जाओ pm_release;
	पूर्ण

	/* add to list of CTI devices */
	mutex_lock(&ect_mutex);
	list_add(&drvdata->node, &ect_net);
	/* set any cross references */
	cti_update_conn_xrefs(drvdata);
	mutex_unlock(&ect_mutex);

	/* set up release chain */
	drvdata->csdev_release = drvdata->csdev->dev.release;
	drvdata->csdev->dev.release = cti_device_release;

	/* all करोne - dec pm refcount */
	pm_runसमय_put(&adev->dev);
	dev_info(&drvdata->csdev->dev, "CTI initialized\n");
	वापस 0;

pm_release:
	cti_pm_release(drvdata);
	वापस ret;
पूर्ण

अटल काष्ठा amba_cs_uci_id uci_id_cti[] = अणु
	अणु
		/*  CTI UCI data */
		.devarch	= 0x47701a14, /* CTI v2 */
		.devarch_mask	= 0xfff0ffff,
		.devtype	= 0x00000014, /* maj(0x4-debug) min(0x1-ECT) */
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा amba_id cti_ids[] = अणु
	CS_AMBA_ID(0x000bb906), /* Coresight CTI (SoC 400), C-A72, C-A57 */
	CS_AMBA_ID(0x000bb922), /* CTI - C-A8 */
	CS_AMBA_ID(0x000bb9a8), /* CTI - C-A53 */
	CS_AMBA_ID(0x000bb9aa), /* CTI - C-A73 */
	CS_AMBA_UCI_ID(0x000bb9da, uci_id_cti), /* CTI - C-A35 */
	CS_AMBA_UCI_ID(0x000bb9ed, uci_id_cti), /* Coresight CTI (SoC 600) */
	अणु 0, 0पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(amba, cti_ids);

अटल काष्ठा amba_driver cti_driver = अणु
	.drv = अणु
		.name	= "coresight-cti",
		.owner = THIS_MODULE,
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe		= cti_probe,
	.हटाओ		= cti_हटाओ,
	.id_table	= cti_ids,
पूर्ण;

अटल पूर्णांक __init cti_init(व्योम)
अणु
	पूर्णांक ret;

	ret = amba_driver_रेजिस्टर(&cti_driver);
	अगर (ret)
		pr_info("Error registering cti driver\n");
	coresight_set_cti_ops(&cti_assoc_ops);
	वापस ret;
पूर्ण

अटल व्योम __निकास cti_निकास(व्योम)
अणु
	coresight_हटाओ_cti_ops();
	amba_driver_unरेजिस्टर(&cti_driver);
पूर्ण

module_init(cti_init);
module_निकास(cti_निकास);

MODULE_AUTHOR("Mike Leach <mike.leach@linaro.org>");
MODULE_DESCRIPTION("Arm CoreSight CTI Driver");
MODULE_LICENSE("GPL v2");
