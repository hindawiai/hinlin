<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2012, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/device.h>
#समावेश <linux/पन.स>
#समावेश <linux/err.h>
#समावेश <linux/export.h>
#समावेश <linux/slab.h>
#समावेश <linux/stringhash.h>
#समावेश <linux/mutex.h>
#समावेश <linux/clk.h>
#समावेश <linux/coresight.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm_runसमय.स>

#समावेश "coresight-etm-perf.h"
#समावेश "coresight-priv.h"

अटल DEFINE_MUTEX(coresight_mutex);
अटल DEFINE_PER_CPU(काष्ठा coresight_device *, csdev_sink);

/**
 * काष्ठा coresight_node - elements of a path, from source to sink
 * @csdev:	Address of an element.
 * @link:	hook to the list.
 */
काष्ठा coresight_node अणु
	काष्ठा coresight_device *csdev;
	काष्ठा list_head link;
पूर्ण;

/*
 * When operating Coresight drivers from the sysFS पूर्णांकerface, only a single
 * path can exist from a tracer (associated to a CPU) to a sink.
 */
अटल DEFINE_PER_CPU(काष्ठा list_head *, tracer_path);

/*
 * As of this writing only a single STM can be found in CS topologies.  Since
 * there is no way to know अगर we'll ever see more and what kind of
 * configuration they will enact, क्रम the समय being only define a single path
 * क्रम STM.
 */
अटल काष्ठा list_head *sपंचांग_path;

/*
 * When losing synchronisation a new barrier packet needs to be inserted at the
 * beginning of the data collected in a buffer.  That way the decoder knows that
 * it needs to look क्रम another sync sequence.
 */
स्थिर u32 coresight_barrier_pkt[4] = अणु0x7fffffff, 0x7fffffff, 0x7fffffff, 0x7fffffffपूर्ण;
EXPORT_SYMBOL_GPL(coresight_barrier_pkt);

अटल स्थिर काष्ठा cti_assoc_op *cti_assoc_ops;

व्योम coresight_set_cti_ops(स्थिर काष्ठा cti_assoc_op *cti_op)
अणु
	cti_assoc_ops = cti_op;
पूर्ण
EXPORT_SYMBOL_GPL(coresight_set_cti_ops);

व्योम coresight_हटाओ_cti_ops(व्योम)
अणु
	cti_assoc_ops = शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(coresight_हटाओ_cti_ops);

व्योम coresight_set_percpu_sink(पूर्णांक cpu, काष्ठा coresight_device *csdev)
अणु
	per_cpu(csdev_sink, cpu) = csdev;
पूर्ण
EXPORT_SYMBOL_GPL(coresight_set_percpu_sink);

काष्ठा coresight_device *coresight_get_percpu_sink(पूर्णांक cpu)
अणु
	वापस per_cpu(csdev_sink, cpu);
पूर्ण
EXPORT_SYMBOL_GPL(coresight_get_percpu_sink);

अटल पूर्णांक coresight_id_match(काष्ठा device *dev, व्योम *data)
अणु
	पूर्णांक trace_id, i_trace_id;
	काष्ठा coresight_device *csdev, *i_csdev;

	csdev = data;
	i_csdev = to_coresight_device(dev);

	/*
	 * No need to care about oneself and components that are not
	 * sources or not enabled
	 */
	अगर (i_csdev == csdev || !i_csdev->enable ||
	    i_csdev->type != CORESIGHT_DEV_TYPE_SOURCE)
		वापस 0;

	/* Get the source ID क्रम both components */
	trace_id = source_ops(csdev)->trace_id(csdev);
	i_trace_id = source_ops(i_csdev)->trace_id(i_csdev);

	/* All you need is one */
	अगर (trace_id == i_trace_id)
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक coresight_source_is_unique(काष्ठा coresight_device *csdev)
अणु
	पूर्णांक trace_id = source_ops(csdev)->trace_id(csdev);

	/* this shouldn't happen */
	अगर (trace_id < 0)
		वापस 0;

	वापस !bus_क्रम_each_dev(&coresight_bustype, शून्य,
				 csdev, coresight_id_match);
पूर्ण

अटल पूर्णांक coresight_find_link_inport(काष्ठा coresight_device *csdev,
				      काष्ठा coresight_device *parent)
अणु
	पूर्णांक i;
	काष्ठा coresight_connection *conn;

	क्रम (i = 0; i < parent->pdata->nr_outport; i++) अणु
		conn = &parent->pdata->conns[i];
		अगर (conn->child_dev == csdev)
			वापस conn->child_port;
	पूर्ण

	dev_err(&csdev->dev, "couldn't find inport, parent: %s, child: %s\n",
		dev_name(&parent->dev), dev_name(&csdev->dev));

	वापस -ENODEV;
पूर्ण

अटल पूर्णांक coresight_find_link_outport(काष्ठा coresight_device *csdev,
				       काष्ठा coresight_device *child)
अणु
	पूर्णांक i;
	काष्ठा coresight_connection *conn;

	क्रम (i = 0; i < csdev->pdata->nr_outport; i++) अणु
		conn = &csdev->pdata->conns[i];
		अगर (conn->child_dev == child)
			वापस conn->outport;
	पूर्ण

	dev_err(&csdev->dev, "couldn't find outport, parent: %s, child: %s\n",
		dev_name(&csdev->dev), dev_name(&child->dev));

	वापस -ENODEV;
पूर्ण

अटल अंतरभूत u32 coresight_पढ़ो_claim_tags(काष्ठा coresight_device *csdev)
अणु
	वापस csdev_access_relaxed_पढ़ो32(&csdev->access, CORESIGHT_CLAIMCLR);
पूर्ण

अटल अंतरभूत bool coresight_is_claimed_self_hosted(काष्ठा coresight_device *csdev)
अणु
	वापस coresight_पढ़ो_claim_tags(csdev) == CORESIGHT_CLAIM_SELF_HOSTED;
पूर्ण

अटल अंतरभूत bool coresight_is_claimed_any(काष्ठा coresight_device *csdev)
अणु
	वापस coresight_पढ़ो_claim_tags(csdev) != 0;
पूर्ण

अटल अंतरभूत व्योम coresight_set_claim_tags(काष्ठा coresight_device *csdev)
अणु
	csdev_access_relaxed_ग_लिखो32(&csdev->access, CORESIGHT_CLAIM_SELF_HOSTED,
				     CORESIGHT_CLAIMSET);
	isb();
पूर्ण

अटल अंतरभूत व्योम coresight_clear_claim_tags(काष्ठा coresight_device *csdev)
अणु
	csdev_access_relaxed_ग_लिखो32(&csdev->access, CORESIGHT_CLAIM_SELF_HOSTED,
				     CORESIGHT_CLAIMCLR);
	isb();
पूर्ण

/*
 * coresight_claim_device_unlocked : Claim the device क्रम self-hosted usage
 * to prevent an बाह्यal tool from touching this device. As per PSCI
 * standards, section "Preserving the execution context" => "Debug and Trace
 * save and Restore", DBGCLAIM[1] is reserved क्रम Self-hosted debug/trace and
 * DBGCLAIM[0] is reserved क्रम बाह्यal tools.
 *
 * Called with CS_UNLOCKed क्रम the component.
 * Returns : 0 on success
 */
पूर्णांक coresight_claim_device_unlocked(काष्ठा coresight_device *csdev)
अणु
	अगर (WARN_ON(!csdev))
		वापस -EINVAL;

	अगर (coresight_is_claimed_any(csdev))
		वापस -EBUSY;

	coresight_set_claim_tags(csdev);
	अगर (coresight_is_claimed_self_hosted(csdev))
		वापस 0;
	/* There was a race setting the tags, clean up and fail */
	coresight_clear_claim_tags(csdev);
	वापस -EBUSY;
पूर्ण
EXPORT_SYMBOL_GPL(coresight_claim_device_unlocked);

पूर्णांक coresight_claim_device(काष्ठा coresight_device *csdev)
अणु
	पूर्णांक rc;

	अगर (WARN_ON(!csdev))
		वापस -EINVAL;

	CS_UNLOCK(csdev->access.base);
	rc = coresight_claim_device_unlocked(csdev);
	CS_LOCK(csdev->access.base);

	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(coresight_claim_device);

/*
 * coresight_disclaim_device_unlocked : Clear the claim tags क्रम the device.
 * Called with CS_UNLOCKed क्रम the component.
 */
व्योम coresight_disclaim_device_unlocked(काष्ठा coresight_device *csdev)
अणु

	अगर (WARN_ON(!csdev))
		वापस;

	अगर (coresight_is_claimed_self_hosted(csdev))
		coresight_clear_claim_tags(csdev);
	अन्यथा
		/*
		 * The बाह्यal agent may have not honoured our claim
		 * and has manipulated it. Or something अन्यथा has seriously
		 * gone wrong in our driver.
		 */
		WARN_ON_ONCE(1);
पूर्ण
EXPORT_SYMBOL_GPL(coresight_disclaim_device_unlocked);

व्योम coresight_disclaim_device(काष्ठा coresight_device *csdev)
अणु
	अगर (WARN_ON(!csdev))
		वापस;

	CS_UNLOCK(csdev->access.base);
	coresight_disclaim_device_unlocked(csdev);
	CS_LOCK(csdev->access.base);
पूर्ण
EXPORT_SYMBOL_GPL(coresight_disclaim_device);

/* enable or disable an associated CTI device of the supplied CS device */
अटल पूर्णांक
coresight_control_assoc_ectdev(काष्ठा coresight_device *csdev, bool enable)
अणु
	पूर्णांक ect_ret = 0;
	काष्ठा coresight_device *ect_csdev = csdev->ect_dev;
	काष्ठा module *mod;

	अगर (!ect_csdev)
		वापस 0;
	अगर ((!ect_ops(ect_csdev)->enable) || (!ect_ops(ect_csdev)->disable))
		वापस 0;

	mod = ect_csdev->dev.parent->driver->owner;
	अगर (enable) अणु
		अगर (try_module_get(mod)) अणु
			ect_ret = ect_ops(ect_csdev)->enable(ect_csdev);
			अगर (ect_ret) अणु
				module_put(mod);
			पूर्ण अन्यथा अणु
				get_device(ect_csdev->dev.parent);
				csdev->ect_enabled = true;
			पूर्ण
		पूर्ण अन्यथा
			ect_ret = -ENODEV;
	पूर्ण अन्यथा अणु
		अगर (csdev->ect_enabled) अणु
			ect_ret = ect_ops(ect_csdev)->disable(ect_csdev);
			put_device(ect_csdev->dev.parent);
			module_put(mod);
			csdev->ect_enabled = false;
		पूर्ण
	पूर्ण

	/* output warning अगर ECT enable is preventing trace operation */
	अगर (ect_ret)
		dev_info(&csdev->dev, "Associated ECT device (%s) %s failed\n",
			 dev_name(&ect_csdev->dev),
			 enable ? "enable" : "disable");
	वापस ect_ret;
पूर्ण

/*
 * Set the associated ect / cti device जबतक holding the coresight_mutex
 * to aव्योम a race with coresight_enable that may try to use this value.
 */
व्योम coresight_set_assoc_ectdev_mutex(काष्ठा coresight_device *csdev,
				      काष्ठा coresight_device *ect_csdev)
अणु
	mutex_lock(&coresight_mutex);
	csdev->ect_dev = ect_csdev;
	mutex_unlock(&coresight_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(coresight_set_assoc_ectdev_mutex);

अटल पूर्णांक coresight_enable_sink(काष्ठा coresight_device *csdev,
				 u32 mode, व्योम *data)
अणु
	पूर्णांक ret;

	/*
	 * We need to make sure the "new" session is compatible with the
	 * existing "mode" of operation.
	 */
	अगर (!sink_ops(csdev)->enable)
		वापस -EINVAL;

	ret = coresight_control_assoc_ectdev(csdev, true);
	अगर (ret)
		वापस ret;
	ret = sink_ops(csdev)->enable(csdev, mode, data);
	अगर (ret) अणु
		coresight_control_assoc_ectdev(csdev, false);
		वापस ret;
	पूर्ण
	csdev->enable = true;

	वापस 0;
पूर्ण

अटल व्योम coresight_disable_sink(काष्ठा coresight_device *csdev)
अणु
	पूर्णांक ret;

	अगर (!sink_ops(csdev)->disable)
		वापस;

	ret = sink_ops(csdev)->disable(csdev);
	अगर (ret)
		वापस;
	coresight_control_assoc_ectdev(csdev, false);
	csdev->enable = false;
पूर्ण

अटल पूर्णांक coresight_enable_link(काष्ठा coresight_device *csdev,
				 काष्ठा coresight_device *parent,
				 काष्ठा coresight_device *child)
अणु
	पूर्णांक ret = 0;
	पूर्णांक link_subtype;
	पूर्णांक inport, outport;

	अगर (!parent || !child)
		वापस -EINVAL;

	inport = coresight_find_link_inport(csdev, parent);
	outport = coresight_find_link_outport(csdev, child);
	link_subtype = csdev->subtype.link_subtype;

	अगर (link_subtype == CORESIGHT_DEV_SUBTYPE_LINK_MERG && inport < 0)
		वापस inport;
	अगर (link_subtype == CORESIGHT_DEV_SUBTYPE_LINK_SPLIT && outport < 0)
		वापस outport;

	अगर (link_ops(csdev)->enable) अणु
		ret = coresight_control_assoc_ectdev(csdev, true);
		अगर (!ret) अणु
			ret = link_ops(csdev)->enable(csdev, inport, outport);
			अगर (ret)
				coresight_control_assoc_ectdev(csdev, false);
		पूर्ण
	पूर्ण

	अगर (!ret)
		csdev->enable = true;

	वापस ret;
पूर्ण

अटल व्योम coresight_disable_link(काष्ठा coresight_device *csdev,
				   काष्ठा coresight_device *parent,
				   काष्ठा coresight_device *child)
अणु
	पूर्णांक i, nr_conns;
	पूर्णांक link_subtype;
	पूर्णांक inport, outport;

	अगर (!parent || !child)
		वापस;

	inport = coresight_find_link_inport(csdev, parent);
	outport = coresight_find_link_outport(csdev, child);
	link_subtype = csdev->subtype.link_subtype;

	अगर (link_subtype == CORESIGHT_DEV_SUBTYPE_LINK_MERG) अणु
		nr_conns = csdev->pdata->nr_inport;
	पूर्ण अन्यथा अगर (link_subtype == CORESIGHT_DEV_SUBTYPE_LINK_SPLIT) अणु
		nr_conns = csdev->pdata->nr_outport;
	पूर्ण अन्यथा अणु
		nr_conns = 1;
	पूर्ण

	अगर (link_ops(csdev)->disable) अणु
		link_ops(csdev)->disable(csdev, inport, outport);
		coresight_control_assoc_ectdev(csdev, false);
	पूर्ण

	क्रम (i = 0; i < nr_conns; i++)
		अगर (atomic_पढ़ो(&csdev->refcnt[i]) != 0)
			वापस;

	csdev->enable = false;
पूर्ण

अटल पूर्णांक coresight_enable_source(काष्ठा coresight_device *csdev, u32 mode)
अणु
	पूर्णांक ret;

	अगर (!coresight_source_is_unique(csdev)) अणु
		dev_warn(&csdev->dev, "traceID %d not unique\n",
			 source_ops(csdev)->trace_id(csdev));
		वापस -EINVAL;
	पूर्ण

	अगर (!csdev->enable) अणु
		अगर (source_ops(csdev)->enable) अणु
			ret = coresight_control_assoc_ectdev(csdev, true);
			अगर (ret)
				वापस ret;
			ret = source_ops(csdev)->enable(csdev, शून्य, mode);
			अगर (ret) अणु
				coresight_control_assoc_ectdev(csdev, false);
				वापस ret;
			पूर्ण
		पूर्ण
		csdev->enable = true;
	पूर्ण

	atomic_inc(csdev->refcnt);

	वापस 0;
पूर्ण

/**
 *  coresight_disable_source - Drop the reference count by 1 and disable
 *  the device अगर there are no users left.
 *
 *  @csdev: The coresight device to disable
 *
 *  Returns true अगर the device has been disabled.
 */
अटल bool coresight_disable_source(काष्ठा coresight_device *csdev)
अणु
	अगर (atomic_dec_वापस(csdev->refcnt) == 0) अणु
		अगर (source_ops(csdev)->disable)
			source_ops(csdev)->disable(csdev, शून्य);
		coresight_control_assoc_ectdev(csdev, false);
		csdev->enable = false;
	पूर्ण
	वापस !csdev->enable;
पूर्ण

/*
 * coresight_disable_path_from : Disable components in the given path beyond
 * @nd in the list. If @nd is शून्य, all the components, except the SOURCE are
 * disabled.
 */
अटल व्योम coresight_disable_path_from(काष्ठा list_head *path,
					काष्ठा coresight_node *nd)
अणु
	u32 type;
	काष्ठा coresight_device *csdev, *parent, *child;

	अगर (!nd)
		nd = list_first_entry(path, काष्ठा coresight_node, link);

	list_क्रम_each_entry_जारी(nd, path, link) अणु
		csdev = nd->csdev;
		type = csdev->type;

		/*
		 * ETF devices are tricky... They can be a link or a sink,
		 * depending on how they are configured.  If an ETF has been
		 * "activated" it will be configured as a sink, otherwise
		 * go ahead with the link configuration.
		 */
		अगर (type == CORESIGHT_DEV_TYPE_LINKSINK)
			type = (csdev == coresight_get_sink(path)) ?
						CORESIGHT_DEV_TYPE_SINK :
						CORESIGHT_DEV_TYPE_LINK;

		चयन (type) अणु
		हाल CORESIGHT_DEV_TYPE_SINK:
			coresight_disable_sink(csdev);
			अवरोध;
		हाल CORESIGHT_DEV_TYPE_SOURCE:
			/*
			 * We skip the first node in the path assuming that it
			 * is the source. So we करोn't expect a source device in
			 * the middle of a path.
			 */
			WARN_ON(1);
			अवरोध;
		हाल CORESIGHT_DEV_TYPE_LINK:
			parent = list_prev_entry(nd, link)->csdev;
			child = list_next_entry(nd, link)->csdev;
			coresight_disable_link(csdev, parent, child);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

व्योम coresight_disable_path(काष्ठा list_head *path)
अणु
	coresight_disable_path_from(path, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(coresight_disable_path);

पूर्णांक coresight_enable_path(काष्ठा list_head *path, u32 mode, व्योम *sink_data)
अणु

	पूर्णांक ret = 0;
	u32 type;
	काष्ठा coresight_node *nd;
	काष्ठा coresight_device *csdev, *parent, *child;

	list_क्रम_each_entry_reverse(nd, path, link) अणु
		csdev = nd->csdev;
		type = csdev->type;

		/*
		 * ETF devices are tricky... They can be a link or a sink,
		 * depending on how they are configured.  If an ETF has been
		 * "activated" it will be configured as a sink, otherwise
		 * go ahead with the link configuration.
		 */
		अगर (type == CORESIGHT_DEV_TYPE_LINKSINK)
			type = (csdev == coresight_get_sink(path)) ?
						CORESIGHT_DEV_TYPE_SINK :
						CORESIGHT_DEV_TYPE_LINK;

		चयन (type) अणु
		हाल CORESIGHT_DEV_TYPE_SINK:
			ret = coresight_enable_sink(csdev, mode, sink_data);
			/*
			 * Sink is the first component turned on. If we
			 * failed to enable the sink, there are no components
			 * that need disabling. Disabling the path here
			 * would mean we could disrupt an existing session.
			 */
			अगर (ret)
				जाओ out;
			अवरोध;
		हाल CORESIGHT_DEV_TYPE_SOURCE:
			/* sources are enabled from either sysFS or Perf */
			अवरोध;
		हाल CORESIGHT_DEV_TYPE_LINK:
			parent = list_prev_entry(nd, link)->csdev;
			child = list_next_entry(nd, link)->csdev;
			ret = coresight_enable_link(csdev, parent, child);
			अगर (ret)
				जाओ err;
			अवरोध;
		शेष:
			जाओ err;
		पूर्ण
	पूर्ण

out:
	वापस ret;
err:
	coresight_disable_path_from(path, nd);
	जाओ out;
पूर्ण

काष्ठा coresight_device *coresight_get_sink(काष्ठा list_head *path)
अणु
	काष्ठा coresight_device *csdev;

	अगर (!path)
		वापस शून्य;

	csdev = list_last_entry(path, काष्ठा coresight_node, link)->csdev;
	अगर (csdev->type != CORESIGHT_DEV_TYPE_SINK &&
	    csdev->type != CORESIGHT_DEV_TYPE_LINKSINK)
		वापस शून्य;

	वापस csdev;
पूर्ण

अटल काष्ठा coresight_device *
coresight_find_enabled_sink(काष्ठा coresight_device *csdev)
अणु
	पूर्णांक i;
	काष्ठा coresight_device *sink;

	अगर ((csdev->type == CORESIGHT_DEV_TYPE_SINK ||
	     csdev->type == CORESIGHT_DEV_TYPE_LINKSINK) &&
	     csdev->activated)
		वापस csdev;

	/*
	 * Recursively explore each port found on this element.
	 */
	क्रम (i = 0; i < csdev->pdata->nr_outport; i++) अणु
		काष्ठा coresight_device *child_dev;

		child_dev = csdev->pdata->conns[i].child_dev;
		अगर (child_dev)
			sink = coresight_find_enabled_sink(child_dev);
		अगर (sink)
			वापस sink;
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * coresight_get_enabled_sink - वापसs the first enabled sink using
 * connection based search starting from the source reference
 *
 * @source: Coresight source device reference
 */
काष्ठा coresight_device *
coresight_get_enabled_sink(काष्ठा coresight_device *source)
अणु
	अगर (!source)
		वापस शून्य;

	वापस coresight_find_enabled_sink(source);
पूर्ण

अटल पूर्णांक coresight_sink_by_id(काष्ठा device *dev, स्थिर व्योम *data)
अणु
	काष्ठा coresight_device *csdev = to_coresight_device(dev);
	अचिन्हित दीर्घ hash;

	अगर (csdev->type == CORESIGHT_DEV_TYPE_SINK ||
	     csdev->type == CORESIGHT_DEV_TYPE_LINKSINK) अणु

		अगर (!csdev->ea)
			वापस 0;
		/*
		 * See function eपंचांग_perf_add_symlink_sink() to know where
		 * this comes from.
		 */
		hash = (अचिन्हित दीर्घ)csdev->ea->var;

		अगर ((u32)hash == *(u32 *)data)
			वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * coresight_get_sink_by_id - वापसs the sink that matches the id
 * @id: Id of the sink to match
 *
 * The name of a sink is unique, whether it is found on the AMBA bus or
 * otherwise.  As such the hash of that name can easily be used to identअगरy
 * a sink.
 */
काष्ठा coresight_device *coresight_get_sink_by_id(u32 id)
अणु
	काष्ठा device *dev = शून्य;

	dev = bus_find_device(&coresight_bustype, शून्य, &id,
			      coresight_sink_by_id);

	वापस dev ? to_coresight_device(dev) : शून्य;
पूर्ण

/**
 * coresight_get_ref- Helper function to increase reference count to module
 * and device.
 *
 * @csdev: The coresight device to get a reference on.
 *
 * Return true in successful हाल and घातer up the device.
 * Return false when failed to get reference of module.
 */
अटल अंतरभूत bool coresight_get_ref(काष्ठा coresight_device *csdev)
अणु
	काष्ठा device *dev = csdev->dev.parent;

	/* Make sure the driver can't be हटाओd */
	अगर (!try_module_get(dev->driver->owner))
		वापस false;
	/* Make sure the device can't go away */
	get_device(dev);
	pm_runसमय_get_sync(dev);
	वापस true;
पूर्ण

/**
 * coresight_put_ref- Helper function to decrease reference count to module
 * and device. Power off the device.
 *
 * @csdev: The coresight device to decrement a reference from.
 */
अटल अंतरभूत व्योम coresight_put_ref(काष्ठा coresight_device *csdev)
अणु
	काष्ठा device *dev = csdev->dev.parent;

	pm_runसमय_put(dev);
	put_device(dev);
	module_put(dev->driver->owner);
पूर्ण

/*
 * coresight_grab_device - Power up this device and any of the helper
 * devices connected to it क्रम trace operation. Since the helper devices
 * करोn't appear on the trace path, they should be handled aदीर्घ with the
 * the master device.
 */
अटल पूर्णांक coresight_grab_device(काष्ठा coresight_device *csdev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < csdev->pdata->nr_outport; i++) अणु
		काष्ठा coresight_device *child;

		child  = csdev->pdata->conns[i].child_dev;
		अगर (child && child->type == CORESIGHT_DEV_TYPE_HELPER)
			अगर (!coresight_get_ref(child))
				जाओ err;
	पूर्ण
	अगर (coresight_get_ref(csdev))
		वापस 0;
err:
	क्रम (i--; i >= 0; i--) अणु
		काष्ठा coresight_device *child;

		child  = csdev->pdata->conns[i].child_dev;
		अगर (child && child->type == CORESIGHT_DEV_TYPE_HELPER)
			coresight_put_ref(child);
	पूर्ण
	वापस -ENODEV;
पूर्ण

/*
 * coresight_drop_device - Release this device and any of the helper
 * devices connected to it.
 */
अटल व्योम coresight_drop_device(काष्ठा coresight_device *csdev)
अणु
	पूर्णांक i;

	coresight_put_ref(csdev);
	क्रम (i = 0; i < csdev->pdata->nr_outport; i++) अणु
		काष्ठा coresight_device *child;

		child  = csdev->pdata->conns[i].child_dev;
		अगर (child && child->type == CORESIGHT_DEV_TYPE_HELPER)
			coresight_put_ref(child);
	पूर्ण
पूर्ण

/**
 * _coresight_build_path - recursively build a path from a @csdev to a sink.
 * @csdev:	The device to start from.
 * @sink:	The final sink we want in this path.
 * @path:	The list to add devices to.
 *
 * The tree of Coresight device is traversed until an activated sink is
 * found.  From there the sink is added to the list aदीर्घ with all the
 * devices that led to that poपूर्णांक - the end result is a list from source
 * to sink. In that list the source is the first device and the sink the
 * last one.
 */
अटल पूर्णांक _coresight_build_path(काष्ठा coresight_device *csdev,
				 काष्ठा coresight_device *sink,
				 काष्ठा list_head *path)
अणु
	पूर्णांक i, ret;
	bool found = false;
	काष्ठा coresight_node *node;

	/* An activated sink has been found.  Enqueue the element */
	अगर (csdev == sink)
		जाओ out;

	अगर (coresight_is_percpu_source(csdev) && coresight_is_percpu_sink(sink) &&
	    sink == per_cpu(csdev_sink, source_ops(csdev)->cpu_id(csdev))) अणु
		अगर (_coresight_build_path(sink, sink, path) == 0) अणु
			found = true;
			जाओ out;
		पूर्ण
	पूर्ण

	/* Not a sink - recursively explore each port found on this element */
	क्रम (i = 0; i < csdev->pdata->nr_outport; i++) अणु
		काष्ठा coresight_device *child_dev;

		child_dev = csdev->pdata->conns[i].child_dev;
		अगर (child_dev &&
		    _coresight_build_path(child_dev, sink, path) == 0) अणु
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!found)
		वापस -ENODEV;

out:
	/*
	 * A path from this element to a sink has been found.  The elements
	 * leading to the sink are alपढ़ोy enqueued, all that is left to करो
	 * is tell the PM runसमय core we need this element and add a node
	 * क्रम it.
	 */
	ret = coresight_grab_device(csdev);
	अगर (ret)
		वापस ret;

	node = kzalloc(माप(काष्ठा coresight_node), GFP_KERNEL);
	अगर (!node)
		वापस -ENOMEM;

	node->csdev = csdev;
	list_add(&node->link, path);

	वापस 0;
पूर्ण

काष्ठा list_head *coresight_build_path(काष्ठा coresight_device *source,
				       काष्ठा coresight_device *sink)
अणु
	काष्ठा list_head *path;
	पूर्णांक rc;

	अगर (!sink)
		वापस ERR_PTR(-EINVAL);

	path = kzalloc(माप(काष्ठा list_head), GFP_KERNEL);
	अगर (!path)
		वापस ERR_PTR(-ENOMEM);

	INIT_LIST_HEAD(path);

	rc = _coresight_build_path(source, sink, path);
	अगर (rc) अणु
		kमुक्त(path);
		वापस ERR_PTR(rc);
	पूर्ण

	वापस path;
पूर्ण

/**
 * coresight_release_path - release a previously built path.
 * @path:	the path to release.
 *
 * Go through all the elements of a path and 1) हटाओd it from the list and
 * 2) मुक्त the memory allocated क्रम each node.
 */
व्योम coresight_release_path(काष्ठा list_head *path)
अणु
	काष्ठा coresight_device *csdev;
	काष्ठा coresight_node *nd, *next;

	list_क्रम_each_entry_safe(nd, next, path, link) अणु
		csdev = nd->csdev;

		coresight_drop_device(csdev);
		list_del(&nd->link);
		kमुक्त(nd);
	पूर्ण

	kमुक्त(path);
	path = शून्य;
पूर्ण

/* वापस true अगर the device is a suitable type क्रम a शेष sink */
अटल अंतरभूत bool coresight_is_def_sink_type(काष्ठा coresight_device *csdev)
अणु
	/* sink & correct subtype */
	अगर (((csdev->type == CORESIGHT_DEV_TYPE_SINK) ||
	     (csdev->type == CORESIGHT_DEV_TYPE_LINKSINK)) &&
	    (csdev->subtype.sink_subtype >= CORESIGHT_DEV_SUBTYPE_SINK_BUFFER))
		वापस true;
	वापस false;
पूर्ण

/**
 * coresight_select_best_sink - वापस the best sink क्रम use as शेष from
 * the two provided.
 *
 * @sink:	current best sink.
 * @depth:      search depth where current sink was found.
 * @new_sink:	new sink क्रम comparison with current sink.
 * @new_depth:  search depth where new sink was found.
 *
 * Sinks prioritised according to coresight_dev_subtype_sink, with only
 * subtypes CORESIGHT_DEV_SUBTYPE_SINK_BUFFER or higher being used.
 *
 * Where two sinks of equal priority are found, the sink बंदst to the
 * source is used (smallest search depth).
 *
 * वापस @new_sink & update @depth अगर better than @sink, अन्यथा वापस @sink.
 */
अटल काष्ठा coresight_device *
coresight_select_best_sink(काष्ठा coresight_device *sink, पूर्णांक *depth,
			   काष्ठा coresight_device *new_sink, पूर्णांक new_depth)
अणु
	bool update = false;

	अगर (!sink) अणु
		/* first found at this level */
		update = true;
	पूर्ण अन्यथा अगर (new_sink->subtype.sink_subtype >
		   sink->subtype.sink_subtype) अणु
		/* found better sink */
		update = true;
	पूर्ण अन्यथा अगर ((new_sink->subtype.sink_subtype ==
		    sink->subtype.sink_subtype) &&
		   (*depth > new_depth)) अणु
		/* found same but बंदr sink */
		update = true;
	पूर्ण

	अगर (update)
		*depth = new_depth;
	वापस update ? new_sink : sink;
पूर्ण

/**
 * coresight_find_sink - recursive function to walk trace connections from
 * source to find a suitable शेष sink.
 *
 * @csdev: source / current device to check.
 * @depth: [in] search depth of calling dev, [out] depth of found sink.
 *
 * This will walk the connection path from a source (ETM) till a suitable
 * sink is encountered and वापस that sink to the original caller.
 *
 * If current device is a plain sink वापस that & depth, otherwise recursively
 * call child connections looking क्रम a sink. Select best possible using
 * coresight_select_best_sink.
 *
 * वापस best sink found, or शून्य अगर not found at this node or child nodes.
 */
अटल काष्ठा coresight_device *
coresight_find_sink(काष्ठा coresight_device *csdev, पूर्णांक *depth)
अणु
	पूर्णांक i, curr_depth = *depth + 1, found_depth = 0;
	काष्ठा coresight_device *found_sink = शून्य;

	अगर (coresight_is_def_sink_type(csdev)) अणु
		found_depth = curr_depth;
		found_sink = csdev;
		अगर (csdev->type == CORESIGHT_DEV_TYPE_SINK)
			जाओ वापस_def_sink;
		/* look past LINKSINK क्रम something better */
	पूर्ण

	/*
	 * Not a sink we want - or possible child sink may be better.
	 * recursively explore each port found on this element.
	 */
	क्रम (i = 0; i < csdev->pdata->nr_outport; i++) अणु
		काष्ठा coresight_device *child_dev, *sink = शून्य;
		पूर्णांक child_depth = curr_depth;

		child_dev = csdev->pdata->conns[i].child_dev;
		अगर (child_dev)
			sink = coresight_find_sink(child_dev, &child_depth);

		अगर (sink)
			found_sink = coresight_select_best_sink(found_sink,
								&found_depth,
								sink,
								child_depth);
	पूर्ण

वापस_def_sink:
	/* वापस found sink and depth */
	अगर (found_sink)
		*depth = found_depth;
	वापस found_sink;
पूर्ण

/**
 * coresight_find_शेष_sink: Find a sink suitable क्रम use as a
 * शेष sink.
 *
 * @csdev: starting source to find a connected sink.
 *
 * Walks connections graph looking क्रम a suitable sink to enable क्रम the
 * supplied source. Uses CoreSight device subtypes and distance from source
 * to select the best sink.
 *
 * If a sink is found, then the शेष sink क्रम this device is set and
 * will be स्वतःmatically used in future.
 *
 * Used in हालs where the CoreSight user (perf / sysfs) has not selected a
 * sink.
 */
काष्ठा coresight_device *
coresight_find_शेष_sink(काष्ठा coresight_device *csdev)
अणु
	पूर्णांक depth = 0;

	/* look क्रम a शेष sink अगर we have not found क्रम this device */
	अगर (!csdev->def_sink) अणु
		अगर (coresight_is_percpu_source(csdev))
			csdev->def_sink = per_cpu(csdev_sink, source_ops(csdev)->cpu_id(csdev));
		अगर (!csdev->def_sink)
			csdev->def_sink = coresight_find_sink(csdev, &depth);
	पूर्ण
	वापस csdev->def_sink;
पूर्ण

अटल पूर्णांक coresight_हटाओ_sink_ref(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा coresight_device *sink = data;
	काष्ठा coresight_device *source = to_coresight_device(dev);

	अगर (source->def_sink == sink)
		source->def_sink = शून्य;
	वापस 0;
पूर्ण

/**
 * coresight_clear_शेष_sink: Remove all शेष sink references to the
 * supplied sink.
 *
 * If supplied device is a sink, then check all the bus devices and clear
 * out all the references to this sink from the coresight_device def_sink
 * parameter.
 *
 * @csdev: coresight sink - हटाओ references to this from all sources.
 */
अटल व्योम coresight_clear_शेष_sink(काष्ठा coresight_device *csdev)
अणु
	अगर ((csdev->type == CORESIGHT_DEV_TYPE_SINK) ||
	    (csdev->type == CORESIGHT_DEV_TYPE_LINKSINK)) अणु
		bus_क्रम_each_dev(&coresight_bustype, शून्य, csdev,
				 coresight_हटाओ_sink_ref);
	पूर्ण
पूर्ण

/** coresight_validate_source - make sure a source has the right credentials
 *  @csdev:	the device काष्ठाure क्रम a source.
 *  @function:	the function this was called from.
 *
 * Assumes the coresight_mutex is held.
 */
अटल पूर्णांक coresight_validate_source(काष्ठा coresight_device *csdev,
				     स्थिर अक्षर *function)
अणु
	u32 type, subtype;

	type = csdev->type;
	subtype = csdev->subtype.source_subtype;

	अगर (type != CORESIGHT_DEV_TYPE_SOURCE) अणु
		dev_err(&csdev->dev, "wrong device type in %s\n", function);
		वापस -EINVAL;
	पूर्ण

	अगर (subtype != CORESIGHT_DEV_SUBTYPE_SOURCE_PROC &&
	    subtype != CORESIGHT_DEV_SUBTYPE_SOURCE_SOFTWARE) अणु
		dev_err(&csdev->dev, "wrong device subtype in %s\n", function);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक coresight_enable(काष्ठा coresight_device *csdev)
अणु
	पूर्णांक cpu, ret = 0;
	काष्ठा coresight_device *sink;
	काष्ठा list_head *path;
	क्रमागत coresight_dev_subtype_source subtype;

	subtype = csdev->subtype.source_subtype;

	mutex_lock(&coresight_mutex);

	ret = coresight_validate_source(csdev, __func__);
	अगर (ret)
		जाओ out;

	अगर (csdev->enable) अणु
		/*
		 * There could be multiple applications driving the software
		 * source. So keep the refcount क्रम each such user when the
		 * source is alपढ़ोy enabled.
		 */
		अगर (subtype == CORESIGHT_DEV_SUBTYPE_SOURCE_SOFTWARE)
			atomic_inc(csdev->refcnt);
		जाओ out;
	पूर्ण

	sink = coresight_get_enabled_sink(csdev);
	अगर (!sink) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	path = coresight_build_path(csdev, sink);
	अगर (IS_ERR(path)) अणु
		pr_err("building path(s) failed\n");
		ret = PTR_ERR(path);
		जाओ out;
	पूर्ण

	ret = coresight_enable_path(path, CS_MODE_SYSFS, शून्य);
	अगर (ret)
		जाओ err_path;

	ret = coresight_enable_source(csdev, CS_MODE_SYSFS);
	अगर (ret)
		जाओ err_source;

	चयन (subtype) अणु
	हाल CORESIGHT_DEV_SUBTYPE_SOURCE_PROC:
		/*
		 * When working from sysFS it is important to keep track
		 * of the paths that were created so that they can be
		 * unकरोne in 'coresight_disable()'.  Since there can only
		 * be a single session per tracer (when working from sysFS)
		 * a per-cpu variable will करो just fine.
		 */
		cpu = source_ops(csdev)->cpu_id(csdev);
		per_cpu(tracer_path, cpu) = path;
		अवरोध;
	हाल CORESIGHT_DEV_SUBTYPE_SOURCE_SOFTWARE:
		sपंचांग_path = path;
		अवरोध;
	शेष:
		/* We can't be here */
		अवरोध;
	पूर्ण

out:
	mutex_unlock(&coresight_mutex);
	वापस ret;

err_source:
	coresight_disable_path(path);

err_path:
	coresight_release_path(path);
	जाओ out;
पूर्ण
EXPORT_SYMBOL_GPL(coresight_enable);

व्योम coresight_disable(काष्ठा coresight_device *csdev)
अणु
	पूर्णांक cpu, ret;
	काष्ठा list_head *path = शून्य;

	mutex_lock(&coresight_mutex);

	ret = coresight_validate_source(csdev, __func__);
	अगर (ret)
		जाओ out;

	अगर (!csdev->enable || !coresight_disable_source(csdev))
		जाओ out;

	चयन (csdev->subtype.source_subtype) अणु
	हाल CORESIGHT_DEV_SUBTYPE_SOURCE_PROC:
		cpu = source_ops(csdev)->cpu_id(csdev);
		path = per_cpu(tracer_path, cpu);
		per_cpu(tracer_path, cpu) = शून्य;
		अवरोध;
	हाल CORESIGHT_DEV_SUBTYPE_SOURCE_SOFTWARE:
		path = sपंचांग_path;
		sपंचांग_path = शून्य;
		अवरोध;
	शेष:
		/* We can't be here */
		अवरोध;
	पूर्ण

	coresight_disable_path(path);
	coresight_release_path(path);

out:
	mutex_unlock(&coresight_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(coresight_disable);

अटल sमाप_प्रकार enable_sink_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा coresight_device *csdev = to_coresight_device(dev);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%u\n", csdev->activated);
पूर्ण

अटल sमाप_प्रकार enable_sink_store(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ val;
	काष्ठा coresight_device *csdev = to_coresight_device(dev);

	ret = kम_से_अदीर्घ(buf, 10, &val);
	अगर (ret)
		वापस ret;

	अगर (val)
		csdev->activated = true;
	अन्यथा
		csdev->activated = false;

	वापस size;

पूर्ण
अटल DEVICE_ATTR_RW(enable_sink);

अटल sमाप_प्रकार enable_source_show(काष्ठा device *dev,
				  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा coresight_device *csdev = to_coresight_device(dev);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%u\n", csdev->enable);
पूर्ण

अटल sमाप_प्रकार enable_source_store(काष्ठा device *dev,
				   काष्ठा device_attribute *attr,
				   स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ val;
	काष्ठा coresight_device *csdev = to_coresight_device(dev);

	ret = kम_से_अदीर्घ(buf, 10, &val);
	अगर (ret)
		वापस ret;

	अगर (val) अणु
		ret = coresight_enable(csdev);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		coresight_disable(csdev);
	पूर्ण

	वापस size;
पूर्ण
अटल DEVICE_ATTR_RW(enable_source);

अटल काष्ठा attribute *coresight_sink_attrs[] = अणु
	&dev_attr_enable_sink.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(coresight_sink);

अटल काष्ठा attribute *coresight_source_attrs[] = अणु
	&dev_attr_enable_source.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(coresight_source);

अटल काष्ठा device_type coresight_dev_type[] = अणु
	अणु
		.name = "none",
	पूर्ण,
	अणु
		.name = "sink",
		.groups = coresight_sink_groups,
	पूर्ण,
	अणु
		.name = "link",
	पूर्ण,
	अणु
		.name = "linksink",
		.groups = coresight_sink_groups,
	पूर्ण,
	अणु
		.name = "source",
		.groups = coresight_source_groups,
	पूर्ण,
	अणु
		.name = "helper",
	पूर्ण,
	अणु
		.name = "ect",
	पूर्ण,
पूर्ण;

अटल व्योम coresight_device_release(काष्ठा device *dev)
अणु
	काष्ठा coresight_device *csdev = to_coresight_device(dev);

	fwnode_handle_put(csdev->dev.fwnode);
	kमुक्त(csdev->refcnt);
	kमुक्त(csdev);
पूर्ण

अटल पूर्णांक coresight_orphan_match(काष्ठा device *dev, व्योम *data)
अणु
	पूर्णांक i, ret = 0;
	bool still_orphan = false;
	काष्ठा coresight_device *csdev, *i_csdev;
	काष्ठा coresight_connection *conn;

	csdev = data;
	i_csdev = to_coresight_device(dev);

	/* No need to check oneself */
	अगर (csdev == i_csdev)
		वापस 0;

	/* Move on to another component अगर no connection is orphan */
	अगर (!i_csdev->orphan)
		वापस 0;
	/*
	 * Circle throuch all the connection of that component.  If we find
	 * an orphan connection whose name matches @csdev, link it.
	 */
	क्रम (i = 0; i < i_csdev->pdata->nr_outport; i++) अणु
		conn = &i_csdev->pdata->conns[i];

		/* Skip the port अगर FW करोesn't describe it */
		अगर (!conn->child_fwnode)
			जारी;
		/* We have found at least one orphan connection */
		अगर (conn->child_dev == शून्य) अणु
			/* Does it match this newly added device? */
			अगर (conn->child_fwnode == csdev->dev.fwnode) अणु
				ret = coresight_make_links(i_csdev,
							   conn, csdev);
				अगर (ret)
					वापस ret;
			पूर्ण अन्यथा अणु
				/* This component still has an orphan */
				still_orphan = true;
			पूर्ण
		पूर्ण
	पूर्ण

	i_csdev->orphan = still_orphan;

	/*
	 * Returning '0' in case we didn't encounter any error,
	 * ensures that all known component on the bus will be checked.
	 */
	वापस 0;
पूर्ण

अटल पूर्णांक coresight_fixup_orphan_conns(काष्ठा coresight_device *csdev)
अणु
	वापस bus_क्रम_each_dev(&coresight_bustype, शून्य,
			 csdev, coresight_orphan_match);
पूर्ण


अटल पूर्णांक coresight_fixup_device_conns(काष्ठा coresight_device *csdev)
अणु
	पूर्णांक i, ret = 0;

	क्रम (i = 0; i < csdev->pdata->nr_outport; i++) अणु
		काष्ठा coresight_connection *conn = &csdev->pdata->conns[i];

		अगर (!conn->child_fwnode)
			जारी;
		conn->child_dev =
			coresight_find_csdev_by_fwnode(conn->child_fwnode);
		अगर (conn->child_dev) अणु
			ret = coresight_make_links(csdev, conn,
						   conn->child_dev);
			अगर (ret)
				अवरोध;
		पूर्ण अन्यथा अणु
			csdev->orphan = true;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक coresight_हटाओ_match(काष्ठा device *dev, व्योम *data)
अणु
	पूर्णांक i;
	काष्ठा coresight_device *csdev, *iterator;
	काष्ठा coresight_connection *conn;

	csdev = data;
	iterator = to_coresight_device(dev);

	/* No need to check oneself */
	अगर (csdev == iterator)
		वापस 0;

	/*
	 * Circle throuch all the connection of that component.  If we find
	 * a connection whose name matches @csdev, हटाओ it.
	 */
	क्रम (i = 0; i < iterator->pdata->nr_outport; i++) अणु
		conn = &iterator->pdata->conns[i];

		अगर (conn->child_dev == शून्य || conn->child_fwnode == शून्य)
			जारी;

		अगर (csdev->dev.fwnode == conn->child_fwnode) अणु
			iterator->orphan = true;
			coresight_हटाओ_links(iterator, conn);
			/*
			 * Drop the reference to the handle क्रम the remote
			 * device acquired in parsing the connections from
			 * platक्रमm data.
			 */
			fwnode_handle_put(conn->child_fwnode);
			/* No need to जारी */
			अवरोध;
		पूर्ण
	पूर्ण

	/*
	 * Returning '0' ensures that all known component on the
	 * bus will be checked.
	 */
	वापस 0;
पूर्ण

/*
 * coresight_हटाओ_conns - Remove references to this given devices
 * from the connections of other devices.
 */
अटल व्योम coresight_हटाओ_conns(काष्ठा coresight_device *csdev)
अणु
	/*
	 * Another device will poपूर्णांक to this device only अगर there is
	 * an output port connected to this one. i.e, अगर the device
	 * करोesn't have at least one input port, there is no poपूर्णांक
	 * in searching all the devices.
	 */
	अगर (csdev->pdata->nr_inport)
		bus_क्रम_each_dev(&coresight_bustype, शून्य,
				 csdev, coresight_हटाओ_match);
पूर्ण

/**
 * coresight_समयout - loop until a bit has changed to a specअगरic रेजिस्टर
 *			state.
 * @csa: coresight device access क्रम the device
 * @offset: Offset of the रेजिस्टर from the base of the device.
 * @position: the position of the bit of पूर्णांकerest.
 * @value: the value the bit should have.
 *
 * Return: 0 as soon as the bit has taken the desired state or -EAGAIN अगर
 * TIMEOUT_US has elapsed, which ever happens first.
 */
पूर्णांक coresight_समयout(काष्ठा csdev_access *csa, u32 offset,
		      पूर्णांक position, पूर्णांक value)
अणु
	पूर्णांक i;
	u32 val;

	क्रम (i = TIMEOUT_US; i > 0; i--) अणु
		val = csdev_access_पढ़ो32(csa, offset);
		/* रुकोing on the bit to go from 0 to 1 */
		अगर (value) अणु
			अगर (val & BIT(position))
				वापस 0;
		/* रुकोing on the bit to go from 1 to 0 */
		पूर्ण अन्यथा अणु
			अगर (!(val & BIT(position)))
				वापस 0;
		पूर्ण

		/*
		 * Delay is arbitrary - the specअगरication करोesn't say how दीर्घ
		 * we are expected to रुको.  Extra check required to make sure
		 * we करोn't रुको needlessly on the last iteration.
		 */
		अगर (i - 1)
			udelay(1);
	पूर्ण

	वापस -EAGAIN;
पूर्ण
EXPORT_SYMBOL_GPL(coresight_समयout);

u32 coresight_relaxed_पढ़ो32(काष्ठा coresight_device *csdev, u32 offset)
अणु
	वापस csdev_access_relaxed_पढ़ो32(&csdev->access, offset);
पूर्ण

u32 coresight_पढ़ो32(काष्ठा coresight_device *csdev, u32 offset)
अणु
	वापस csdev_access_पढ़ो32(&csdev->access, offset);
पूर्ण

व्योम coresight_relaxed_ग_लिखो32(काष्ठा coresight_device *csdev,
			       u32 val, u32 offset)
अणु
	csdev_access_relaxed_ग_लिखो32(&csdev->access, val, offset);
पूर्ण

व्योम coresight_ग_लिखो32(काष्ठा coresight_device *csdev, u32 val, u32 offset)
अणु
	csdev_access_ग_लिखो32(&csdev->access, val, offset);
पूर्ण

u64 coresight_relaxed_पढ़ो64(काष्ठा coresight_device *csdev, u32 offset)
अणु
	वापस csdev_access_relaxed_पढ़ो64(&csdev->access, offset);
पूर्ण

u64 coresight_पढ़ो64(काष्ठा coresight_device *csdev, u32 offset)
अणु
	वापस csdev_access_पढ़ो64(&csdev->access, offset);
पूर्ण

व्योम coresight_relaxed_ग_लिखो64(काष्ठा coresight_device *csdev,
			       u64 val, u32 offset)
अणु
	csdev_access_relaxed_ग_लिखो64(&csdev->access, val, offset);
पूर्ण

व्योम coresight_ग_लिखो64(काष्ठा coresight_device *csdev, u64 val, u32 offset)
अणु
	csdev_access_ग_लिखो64(&csdev->access, val, offset);
पूर्ण

/*
 * coresight_release_platक्रमm_data: Release references to the devices connected
 * to the output port of this device.
 */
व्योम coresight_release_platक्रमm_data(काष्ठा coresight_device *csdev,
				     काष्ठा coresight_platक्रमm_data *pdata)
अणु
	पूर्णांक i;
	काष्ठा coresight_connection *conns = pdata->conns;

	क्रम (i = 0; i < pdata->nr_outport; i++) अणु
		/* If we have made the links, हटाओ them now */
		अगर (csdev && conns[i].child_dev)
			coresight_हटाओ_links(csdev, &conns[i]);
		/*
		 * Drop the refcount and clear the handle as this device
		 * is going away
		 */
		अगर (conns[i].child_fwnode) अणु
			fwnode_handle_put(conns[i].child_fwnode);
			pdata->conns[i].child_fwnode = शून्य;
		पूर्ण
	पूर्ण
	अगर (csdev)
		coresight_हटाओ_conns_sysfs_group(csdev);
पूर्ण

काष्ठा coresight_device *coresight_रेजिस्टर(काष्ठा coresight_desc *desc)
अणु
	पूर्णांक ret;
	पूर्णांक link_subtype;
	पूर्णांक nr_refcnts = 1;
	atomic_t *refcnts = शून्य;
	काष्ठा coresight_device *csdev;

	csdev = kzalloc(माप(*csdev), GFP_KERNEL);
	अगर (!csdev) अणु
		ret = -ENOMEM;
		जाओ err_out;
	पूर्ण

	अगर (desc->type == CORESIGHT_DEV_TYPE_LINK ||
	    desc->type == CORESIGHT_DEV_TYPE_LINKSINK) अणु
		link_subtype = desc->subtype.link_subtype;

		अगर (link_subtype == CORESIGHT_DEV_SUBTYPE_LINK_MERG)
			nr_refcnts = desc->pdata->nr_inport;
		अन्यथा अगर (link_subtype == CORESIGHT_DEV_SUBTYPE_LINK_SPLIT)
			nr_refcnts = desc->pdata->nr_outport;
	पूर्ण

	refcnts = kसुस्मृति(nr_refcnts, माप(*refcnts), GFP_KERNEL);
	अगर (!refcnts) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त_csdev;
	पूर्ण

	csdev->refcnt = refcnts;

	csdev->pdata = desc->pdata;

	csdev->type = desc->type;
	csdev->subtype = desc->subtype;
	csdev->ops = desc->ops;
	csdev->access = desc->access;
	csdev->orphan = false;

	csdev->dev.type = &coresight_dev_type[desc->type];
	csdev->dev.groups = desc->groups;
	csdev->dev.parent = desc->dev;
	csdev->dev.release = coresight_device_release;
	csdev->dev.bus = &coresight_bustype;
	/*
	 * Hold the reference to our parent device. This will be
	 * dropped only in coresight_device_release().
	 */
	csdev->dev.fwnode = fwnode_handle_get(dev_fwnode(desc->dev));
	dev_set_name(&csdev->dev, "%s", desc->name);

	ret = device_रेजिस्टर(&csdev->dev);
	अगर (ret) अणु
		put_device(&csdev->dev);
		/*
		 * All resources are मुक्त'd explicitly via
		 * coresight_device_release(), triggered from put_device().
		 */
		जाओ err_out;
	पूर्ण

	अगर (csdev->type == CORESIGHT_DEV_TYPE_SINK ||
	    csdev->type == CORESIGHT_DEV_TYPE_LINKSINK) अणु
		ret = eपंचांग_perf_add_symlink_sink(csdev);

		अगर (ret) अणु
			device_unरेजिस्टर(&csdev->dev);
			/*
			 * As with the above, all resources are मुक्त'd
			 * explicitly via coresight_device_release() triggered
			 * from put_device(), which is in turn called from
			 * function device_unरेजिस्टर().
			 */
			जाओ err_out;
		पूर्ण
	पूर्ण

	mutex_lock(&coresight_mutex);

	ret = coresight_create_conns_sysfs_group(csdev);
	अगर (!ret)
		ret = coresight_fixup_device_conns(csdev);
	अगर (!ret)
		ret = coresight_fixup_orphan_conns(csdev);
	अगर (!ret && cti_assoc_ops && cti_assoc_ops->add)
		cti_assoc_ops->add(csdev);

	mutex_unlock(&coresight_mutex);
	अगर (ret) अणु
		coresight_unरेजिस्टर(csdev);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस csdev;

err_मुक्त_csdev:
	kमुक्त(csdev);
err_out:
	/* Cleanup the connection inक्रमmation */
	coresight_release_platक्रमm_data(शून्य, desc->pdata);
	वापस ERR_PTR(ret);
पूर्ण
EXPORT_SYMBOL_GPL(coresight_रेजिस्टर);

व्योम coresight_unरेजिस्टर(काष्ठा coresight_device *csdev)
अणु
	eपंचांग_perf_del_symlink_sink(csdev);
	/* Remove references of that device in the topology */
	अगर (cti_assoc_ops && cti_assoc_ops->हटाओ)
		cti_assoc_ops->हटाओ(csdev);
	coresight_हटाओ_conns(csdev);
	coresight_clear_शेष_sink(csdev);
	coresight_release_platक्रमm_data(csdev, csdev->pdata);
	device_unरेजिस्टर(&csdev->dev);
पूर्ण
EXPORT_SYMBOL_GPL(coresight_unरेजिस्टर);


/*
 * coresight_search_device_idx - Search the fwnode handle of a device
 * in the given dev_idx list. Must be called with the coresight_mutex held.
 *
 * Returns the index of the entry, when found. Otherwise, -ENOENT.
 */
अटल अंतरभूत पूर्णांक coresight_search_device_idx(काष्ठा coresight_dev_list *dict,
					      काष्ठा fwnode_handle *fwnode)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < dict->nr_idx; i++)
		अगर (dict->fwnode_list[i] == fwnode)
			वापस i;
	वापस -ENOENT;
पूर्ण

bool coresight_loses_context_with_cpu(काष्ठा device *dev)
अणु
	वापस fwnode_property_present(dev_fwnode(dev),
				       "arm,coresight-loses-context-with-cpu");
पूर्ण
EXPORT_SYMBOL_GPL(coresight_loses_context_with_cpu);

/*
 * coresight_alloc_device_name - Get an index क्रम a given device in the
 * device index list specअगरic to a driver. An index is allocated क्रम a
 * device and is tracked with the fwnode_handle to prevent allocating
 * duplicate indices क्रम the same device (e.g, अगर we defer probing of
 * a device due to dependencies), in हाल the index is requested again.
 */
अक्षर *coresight_alloc_device_name(काष्ठा coresight_dev_list *dict,
				  काष्ठा device *dev)
अणु
	पूर्णांक idx;
	अक्षर *name = शून्य;
	काष्ठा fwnode_handle **list;

	mutex_lock(&coresight_mutex);

	idx = coresight_search_device_idx(dict, dev_fwnode(dev));
	अगर (idx < 0) अणु
		/* Make space क्रम the new entry */
		idx = dict->nr_idx;
		list = kपुनः_स्मृति(dict->fwnode_list,
				(idx + 1) * माप(*dict->fwnode_list),
				GFP_KERNEL);
		अगर (ZERO_OR_शून्य_PTR(list)) अणु
			idx = -ENOMEM;
			जाओ करोne;
		पूर्ण

		list[idx] = dev_fwnode(dev);
		dict->fwnode_list = list;
		dict->nr_idx = idx + 1;
	पूर्ण

	name = devm_kaप्र_लिखो(dev, GFP_KERNEL, "%s%d", dict->pfx, idx);
करोne:
	mutex_unlock(&coresight_mutex);
	वापस name;
पूर्ण
EXPORT_SYMBOL_GPL(coresight_alloc_device_name);

काष्ठा bus_type coresight_bustype = अणु
	.name	= "coresight",
पूर्ण;

अटल पूर्णांक __init coresight_init(व्योम)
अणु
	पूर्णांक ret;

	ret = bus_रेजिस्टर(&coresight_bustype);
	अगर (ret)
		वापस ret;

	ret = eपंचांग_perf_init();
	अगर (ret)
		bus_unरेजिस्टर(&coresight_bustype);

	वापस ret;
पूर्ण

अटल व्योम __निकास coresight_निकास(व्योम)
अणु
	eपंचांग_perf_निकास();
	bus_unरेजिस्टर(&coresight_bustype);
पूर्ण

module_init(coresight_init);
module_निकास(coresight_निकास);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Pratik Patel <pratikp@codeaurora.org>");
MODULE_AUTHOR("Mathieu Poirier <mathieu.poirier@linaro.org>");
MODULE_DESCRIPTION("Arm CoreSight tracer driver");
