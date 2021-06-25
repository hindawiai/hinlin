<शैली गुरु>

/*
 * edac_device.c
 * (C) 2007 www.करोuglaskthompson.com
 *
 * This file may be distributed under the terms of the
 * GNU General Public License.
 *
 * Written by Doug Thompson <norsk5@xmission.com>
 *
 * edac_device API implementation
 * 19 Jan 2007
 */

#समावेश <यंत्र/page.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/init.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/smp.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/समयr.h>

#समावेश "edac_device.h"
#समावेश "edac_module.h"

/* lock क्रम the list: 'edac_device_list', manipulation of this list
 * is रक्षित by the 'device_ctls_mutex' lock
 */
अटल DEFINE_MUTEX(device_ctls_mutex);
अटल LIST_HEAD(edac_device_list);

#अगर_घोषित CONFIG_EDAC_DEBUG
अटल व्योम edac_device_dump_device(काष्ठा edac_device_ctl_info *edac_dev)
अणु
	edac_dbg(3, "\tedac_dev = %p dev_idx=%d\n",
		 edac_dev, edac_dev->dev_idx);
	edac_dbg(4, "\tedac_dev->edac_check = %p\n", edac_dev->edac_check);
	edac_dbg(3, "\tdev = %p\n", edac_dev->dev);
	edac_dbg(3, "\tmod_name:ctl_name = %s:%s\n",
		 edac_dev->mod_name, edac_dev->ctl_name);
	edac_dbg(3, "\tpvt_info = %p\n\n", edac_dev->pvt_info);
पूर्ण
#पूर्ण_अगर				/* CONFIG_EDAC_DEBUG */

काष्ठा edac_device_ctl_info *edac_device_alloc_ctl_info(
	अचिन्हित sz_निजी,
	अक्षर *edac_device_name, अचिन्हित nr_instances,
	अक्षर *edac_block_name, अचिन्हित nr_blocks,
	अचिन्हित offset_value,		/* zero, 1, or other based offset */
	काष्ठा edac_dev_sysfs_block_attribute *attrib_spec, अचिन्हित nr_attrib,
	पूर्णांक device_index)
अणु
	काष्ठा edac_device_ctl_info *dev_ctl;
	काष्ठा edac_device_instance *dev_inst, *inst;
	काष्ठा edac_device_block *dev_blk, *blk_p, *blk;
	काष्ठा edac_dev_sysfs_block_attribute *dev_attrib, *attrib_p, *attrib;
	अचिन्हित total_size;
	अचिन्हित count;
	अचिन्हित instance, block, attr;
	व्योम *pvt, *p;
	पूर्णांक err;

	edac_dbg(4, "instances=%d blocks=%d\n", nr_instances, nr_blocks);

	/* Calculate the size of memory we need to allocate AND
	 * determine the offsets of the various item arrays
	 * (instance,block,attrib) from the start of an  allocated काष्ठाure.
	 * We want the alignment of each item  (instance,block,attrib)
	 * to be at least as stringent as what the compiler would
	 * provide अगर we could simply hardcode everything पूर्णांकo a single काष्ठा.
	 */
	p = शून्य;
	dev_ctl = edac_align_ptr(&p, माप(*dev_ctl), 1);

	/* Calc the 'end' offset past end of ONE ctl_info काष्ठाure
	 * which will become the start of the 'instance' array
	 */
	dev_inst = edac_align_ptr(&p, माप(*dev_inst), nr_instances);

	/* Calc the 'end' offset past the instance array within the ctl_info
	 * which will become the start of the block array
	 */
	count = nr_instances * nr_blocks;
	dev_blk = edac_align_ptr(&p, माप(*dev_blk), count);

	/* Calc the 'end' offset past the dev_blk array
	 * which will become the start of the attrib array, अगर any.
	 */
	/* calc how many nr_attrib we need */
	अगर (nr_attrib > 0)
		count *= nr_attrib;
	dev_attrib = edac_align_ptr(&p, माप(*dev_attrib), count);

	/* Calc the 'end' offset past the attributes array */
	pvt = edac_align_ptr(&p, sz_निजी, 1);

	/* 'pvt' now poपूर्णांकs to where the निजी data area is.
	 * At this poपूर्णांक 'pvt' (like dev_inst,dev_blk and dev_attrib)
	 * is baselined at ZERO
	 */
	total_size = ((अचिन्हित दीर्घ)pvt) + sz_निजी;

	/* Allocate the amount of memory क्रम the set of control काष्ठाures */
	dev_ctl = kzalloc(total_size, GFP_KERNEL);
	अगर (dev_ctl == शून्य)
		वापस शून्य;

	/* Adjust poपूर्णांकers so they poपूर्णांक within the actual memory we
	 * just allocated rather than an imaginary chunk of memory
	 * located at address 0.
	 * 'dev_ctl' poपूर्णांकs to REAL memory, जबतक the others are
	 * ZERO based and thus need to be adjusted to poपूर्णांक within
	 * the allocated memory.
	 */
	dev_inst = (काष्ठा edac_device_instance *)
		(((अक्षर *)dev_ctl) + ((अचिन्हित दीर्घ)dev_inst));
	dev_blk = (काष्ठा edac_device_block *)
		(((अक्षर *)dev_ctl) + ((अचिन्हित दीर्घ)dev_blk));
	dev_attrib = (काष्ठा edac_dev_sysfs_block_attribute *)
		(((अक्षर *)dev_ctl) + ((अचिन्हित दीर्घ)dev_attrib));
	pvt = sz_निजी ? (((अक्षर *)dev_ctl) + ((अचिन्हित दीर्घ)pvt)) : शून्य;

	/* Begin storing the inक्रमmation पूर्णांकo the control info काष्ठाure */
	dev_ctl->dev_idx = device_index;
	dev_ctl->nr_instances = nr_instances;
	dev_ctl->instances = dev_inst;
	dev_ctl->pvt_info = pvt;

	/* Default logging of CEs and UEs */
	dev_ctl->log_ce = 1;
	dev_ctl->log_ue = 1;

	/* Name of this edac device */
	snम_लिखो(dev_ctl->name,माप(dev_ctl->name),"%s",edac_device_name);

	edac_dbg(4, "edac_dev=%p next after end=%p\n",
		 dev_ctl, pvt + sz_निजी);

	/* Initialize every Instance */
	क्रम (instance = 0; instance < nr_instances; instance++) अणु
		inst = &dev_inst[instance];
		inst->ctl = dev_ctl;
		inst->nr_blocks = nr_blocks;
		blk_p = &dev_blk[instance * nr_blocks];
		inst->blocks = blk_p;

		/* name of this instance */
		snम_लिखो(inst->name, माप(inst->name),
			 "%s%u", edac_device_name, instance);

		/* Initialize every block in each instance */
		क्रम (block = 0; block < nr_blocks; block++) अणु
			blk = &blk_p[block];
			blk->instance = inst;
			snम_लिखो(blk->name, माप(blk->name),
				 "%s%d", edac_block_name, block+offset_value);

			edac_dbg(4, "instance=%d inst_p=%p block=#%d block_p=%p name='%s'\n",
				 instance, inst, block, blk, blk->name);

			/* अगर there are NO attributes OR no attribute poपूर्णांकer
			 * then जारी on to next block iteration
			 */
			अगर ((nr_attrib == 0) || (attrib_spec == शून्य))
				जारी;

			/* setup the attribute array क्रम this block */
			blk->nr_attribs = nr_attrib;
			attrib_p = &dev_attrib[block*nr_instances*nr_attrib];
			blk->block_attributes = attrib_p;

			edac_dbg(4, "THIS BLOCK_ATTRIB=%p\n",
				 blk->block_attributes);

			/* Initialize every user specअगरied attribute in this
			 * block with the data the caller passed in
			 * Each block माला_लो its own copy of poपूर्णांकers,
			 * and its unique 'value'
			 */
			क्रम (attr = 0; attr < nr_attrib; attr++) अणु
				attrib = &attrib_p[attr];

				/* populate the unique per attrib
				 * with the code poपूर्णांकers and info
				 */
				attrib->attr = attrib_spec[attr].attr;
				attrib->show = attrib_spec[attr].show;
				attrib->store = attrib_spec[attr].store;

				attrib->block = blk;	/* up link */

				edac_dbg(4, "alloc-attrib=%p attrib_name='%s' attrib-spec=%p spec-name=%s\n",
					 attrib, attrib->attr.name,
					 &attrib_spec[attr],
					 attrib_spec[attr].attr.name
					);
			पूर्ण
		पूर्ण
	पूर्ण

	/* Mark this instance as merely ALLOCATED */
	dev_ctl->op_state = OP_ALLOC;

	/*
	 * Initialize the 'root' kobj क्रम the edac_device controller
	 */
	err = edac_device_रेजिस्टर_sysfs_मुख्य_kobj(dev_ctl);
	अगर (err) अणु
		kमुक्त(dev_ctl);
		वापस शून्य;
	पूर्ण

	/* at this poपूर्णांक, the root kobj is valid, and in order to
	 * 'free' the object, then the function:
	 *	edac_device_unरेजिस्टर_sysfs_मुख्य_kobj() must be called
	 * which will perक्रमm kobj unregistration and the actual मुक्त
	 * will occur during the kobject callback operation
	 */

	वापस dev_ctl;
पूर्ण
EXPORT_SYMBOL_GPL(edac_device_alloc_ctl_info);

व्योम edac_device_मुक्त_ctl_info(काष्ठा edac_device_ctl_info *ctl_info)
अणु
	edac_device_unरेजिस्टर_sysfs_मुख्य_kobj(ctl_info);
पूर्ण
EXPORT_SYMBOL_GPL(edac_device_मुक्त_ctl_info);

/*
 * find_edac_device_by_dev
 *	scans the edac_device list क्रम a specअगरic 'struct device *'
 *
 *	lock to be held prior to call:	device_ctls_mutex
 *
 *	Return:
 *		poपूर्णांकer to control काष्ठाure managing 'dev'
 *		शून्य अगर not found on list
 */
अटल काष्ठा edac_device_ctl_info *find_edac_device_by_dev(काष्ठा device *dev)
अणु
	काष्ठा edac_device_ctl_info *edac_dev;
	काष्ठा list_head *item;

	edac_dbg(0, "\n");

	list_क्रम_each(item, &edac_device_list) अणु
		edac_dev = list_entry(item, काष्ठा edac_device_ctl_info, link);

		अगर (edac_dev->dev == dev)
			वापस edac_dev;
	पूर्ण

	वापस शून्य;
पूर्ण

/*
 * add_edac_dev_to_global_list
 *	Beक्रमe calling this function, caller must
 *	assign a unique value to edac_dev->dev_idx.
 *
 *	lock to be held prior to call:	device_ctls_mutex
 *
 *	Return:
 *		0 on success
 *		1 on failure.
 */
अटल पूर्णांक add_edac_dev_to_global_list(काष्ठा edac_device_ctl_info *edac_dev)
अणु
	काष्ठा list_head *item, *insert_beक्रमe;
	काष्ठा edac_device_ctl_info *rover;

	insert_beक्रमe = &edac_device_list;

	/* Determine अगर alपढ़ोy on the list */
	rover = find_edac_device_by_dev(edac_dev->dev);
	अगर (unlikely(rover != शून्य))
		जाओ fail0;

	/* Insert in ascending order by 'dev_idx', so find position */
	list_क्रम_each(item, &edac_device_list) अणु
		rover = list_entry(item, काष्ठा edac_device_ctl_info, link);

		अगर (rover->dev_idx >= edac_dev->dev_idx) अणु
			अगर (unlikely(rover->dev_idx == edac_dev->dev_idx))
				जाओ fail1;

			insert_beक्रमe = item;
			अवरोध;
		पूर्ण
	पूर्ण

	list_add_tail_rcu(&edac_dev->link, insert_beक्रमe);
	वापस 0;

fail0:
	edac_prपूर्णांकk(KERN_WARNING, EDAC_MC,
			"%s (%s) %s %s already assigned %d\n",
			dev_name(rover->dev), edac_dev_name(rover),
			rover->mod_name, rover->ctl_name, rover->dev_idx);
	वापस 1;

fail1:
	edac_prपूर्णांकk(KERN_WARNING, EDAC_MC,
			"bug in low-level driver: attempt to assign\n"
			"    duplicate dev_idx %d in %s()\n", rover->dev_idx,
			__func__);
	वापस 1;
पूर्ण

/*
 * del_edac_device_from_global_list
 */
अटल व्योम del_edac_device_from_global_list(काष्ठा edac_device_ctl_info
						*edac_device)
अणु
	list_del_rcu(&edac_device->link);

	/* these are क्रम safe removal of devices from global list जबतक
	 * NMI handlers may be traversing list
	 */
	synchronize_rcu();
	INIT_LIST_HEAD(&edac_device->link);
पूर्ण

/*
 * edac_device_workq_function
 *	perक्रमms the operation scheduled by a workq request
 *
 *	this workq is embedded within an edac_device_ctl_info
 *	काष्ठाure, that needs to be polled क्रम possible error events.
 *
 *	This operation is to acquire the list mutex lock
 *	(thus preventing insertation or deletion)
 *	and then call the device's poll function IFF this device is
 *	running polled and there is a poll function defined.
 */
अटल व्योम edac_device_workq_function(काष्ठा work_काष्ठा *work_req)
अणु
	काष्ठा delayed_work *d_work = to_delayed_work(work_req);
	काष्ठा edac_device_ctl_info *edac_dev = to_edac_device_ctl_work(d_work);

	mutex_lock(&device_ctls_mutex);

	/* If we are being हटाओd, bail out immediately */
	अगर (edac_dev->op_state == OP_OFFLINE) अणु
		mutex_unlock(&device_ctls_mutex);
		वापस;
	पूर्ण

	/* Only poll controllers that are running polled and have a check */
	अगर ((edac_dev->op_state == OP_RUNNING_POLL) &&
		(edac_dev->edac_check != शून्य)) अणु
			edac_dev->edac_check(edac_dev);
	पूर्ण

	mutex_unlock(&device_ctls_mutex);

	/* Reschedule the workq क्रम the next समय period to start again
	 * अगर the number of msec is क्रम 1 sec, then adjust to the next
	 * whole one second to save समयrs firing all over the period
	 * between पूर्णांकegral seconds
	 */
	अगर (edac_dev->poll_msec == 1000)
		edac_queue_work(&edac_dev->work, round_jअगरfies_relative(edac_dev->delay));
	अन्यथा
		edac_queue_work(&edac_dev->work, edac_dev->delay);
पूर्ण

/*
 * edac_device_workq_setup
 *	initialize a workq item क्रम this edac_device instance
 *	passing in the new delay period in msec
 */
अटल व्योम edac_device_workq_setup(काष्ठा edac_device_ctl_info *edac_dev,
				    अचिन्हित msec)
अणु
	edac_dbg(0, "\n");

	/* take the arg 'msec' and set it पूर्णांकo the control काष्ठाure
	 * to used in the समय period calculation
	 * then calc the number of jअगरfies that represents
	 */
	edac_dev->poll_msec = msec;
	edac_dev->delay = msecs_to_jअगरfies(msec);

	INIT_DELAYED_WORK(&edac_dev->work, edac_device_workq_function);

	/* optimize here क्रम the 1 second हाल, which will be normal value, to
	 * fire ON the 1 second समय event. This helps reduce all sorts of
	 * समयrs firing on sub-second basis, जबतक they are happy
	 * to fire together on the 1 second exactly
	 */
	अगर (edac_dev->poll_msec == 1000)
		edac_queue_work(&edac_dev->work, round_jअगरfies_relative(edac_dev->delay));
	अन्यथा
		edac_queue_work(&edac_dev->work, edac_dev->delay);
पूर्ण

/*
 * edac_device_workq_tearकरोwn
 *	stop the workq processing on this edac_dev
 */
अटल व्योम edac_device_workq_tearकरोwn(काष्ठा edac_device_ctl_info *edac_dev)
अणु
	अगर (!edac_dev->edac_check)
		वापस;

	edac_dev->op_state = OP_OFFLINE;

	edac_stop_work(&edac_dev->work);
पूर्ण

/*
 * edac_device_reset_delay_period
 *
 *	need to stop any outstanding workq queued up at this समय
 *	because we will be resetting the sleep समय.
 *	Then restart the workq on the new delay
 */
व्योम edac_device_reset_delay_period(काष्ठा edac_device_ctl_info *edac_dev,
					अचिन्हित दीर्घ value)
अणु
	अचिन्हित दीर्घ jअगरfs = msecs_to_jअगरfies(value);

	अगर (value == 1000)
		jअगरfs = round_jअगरfies_relative(value);

	edac_dev->poll_msec = value;
	edac_dev->delay	    = jअगरfs;

	edac_mod_work(&edac_dev->work, jअगरfs);
पूर्ण

पूर्णांक edac_device_alloc_index(व्योम)
अणु
	अटल atomic_t device_indexes = ATOMIC_INIT(0);

	वापस atomic_inc_वापस(&device_indexes) - 1;
पूर्ण
EXPORT_SYMBOL_GPL(edac_device_alloc_index);

पूर्णांक edac_device_add_device(काष्ठा edac_device_ctl_info *edac_dev)
अणु
	edac_dbg(0, "\n");

#अगर_घोषित CONFIG_EDAC_DEBUG
	अगर (edac_debug_level >= 3)
		edac_device_dump_device(edac_dev);
#पूर्ण_अगर
	mutex_lock(&device_ctls_mutex);

	अगर (add_edac_dev_to_global_list(edac_dev))
		जाओ fail0;

	/* set load समय so that error rate can be tracked */
	edac_dev->start_समय = jअगरfies;

	/* create this instance's sysfs entries */
	अगर (edac_device_create_sysfs(edac_dev)) अणु
		edac_device_prपूर्णांकk(edac_dev, KERN_WARNING,
					"failed to create sysfs device\n");
		जाओ fail1;
	पूर्ण

	/* If there IS a check routine, then we are running POLLED */
	अगर (edac_dev->edac_check != शून्य) अणु
		/* This instance is NOW RUNNING */
		edac_dev->op_state = OP_RUNNING_POLL;

		/*
		 * enable workq processing on this instance,
		 * शेष = 1000 msec
		 */
		edac_device_workq_setup(edac_dev, 1000);
	पूर्ण अन्यथा अणु
		edac_dev->op_state = OP_RUNNING_INTERRUPT;
	पूर्ण

	/* Report action taken */
	edac_device_prपूर्णांकk(edac_dev, KERN_INFO,
		"Giving out device to module %s controller %s: DEV %s (%s)\n",
		edac_dev->mod_name, edac_dev->ctl_name, edac_dev->dev_name,
		edac_op_state_to_string(edac_dev->op_state));

	mutex_unlock(&device_ctls_mutex);
	वापस 0;

fail1:
	/* Some error, so हटाओ the entry from the lsit */
	del_edac_device_from_global_list(edac_dev);

fail0:
	mutex_unlock(&device_ctls_mutex);
	वापस 1;
पूर्ण
EXPORT_SYMBOL_GPL(edac_device_add_device);

काष्ठा edac_device_ctl_info *edac_device_del_device(काष्ठा device *dev)
अणु
	काष्ठा edac_device_ctl_info *edac_dev;

	edac_dbg(0, "\n");

	mutex_lock(&device_ctls_mutex);

	/* Find the काष्ठाure on the list, अगर not there, then leave */
	edac_dev = find_edac_device_by_dev(dev);
	अगर (edac_dev == शून्य) अणु
		mutex_unlock(&device_ctls_mutex);
		वापस शून्य;
	पूर्ण

	/* mark this instance as OFFLINE */
	edac_dev->op_state = OP_OFFLINE;

	/* deरेजिस्टर from global list */
	del_edac_device_from_global_list(edac_dev);

	mutex_unlock(&device_ctls_mutex);

	/* clear workq processing on this instance */
	edac_device_workq_tearकरोwn(edac_dev);

	/* Tear करोwn the sysfs entries क्रम this instance */
	edac_device_हटाओ_sysfs(edac_dev);

	edac_prपूर्णांकk(KERN_INFO, EDAC_MC,
		"Removed device %d for %s %s: DEV %s\n",
		edac_dev->dev_idx,
		edac_dev->mod_name, edac_dev->ctl_name, edac_dev_name(edac_dev));

	वापस edac_dev;
पूर्ण
EXPORT_SYMBOL_GPL(edac_device_del_device);

अटल अंतरभूत पूर्णांक edac_device_get_log_ce(काष्ठा edac_device_ctl_info *edac_dev)
अणु
	वापस edac_dev->log_ce;
पूर्ण

अटल अंतरभूत पूर्णांक edac_device_get_log_ue(काष्ठा edac_device_ctl_info *edac_dev)
अणु
	वापस edac_dev->log_ue;
पूर्ण

अटल अंतरभूत पूर्णांक edac_device_get_panic_on_ue(काष्ठा edac_device_ctl_info
					*edac_dev)
अणु
	वापस edac_dev->panic_on_ue;
पूर्ण

व्योम edac_device_handle_ce_count(काष्ठा edac_device_ctl_info *edac_dev,
				 अचिन्हित पूर्णांक count, पूर्णांक inst_nr, पूर्णांक block_nr,
				 स्थिर अक्षर *msg)
अणु
	काष्ठा edac_device_instance *instance;
	काष्ठा edac_device_block *block = शून्य;

	अगर (!count)
		वापस;

	अगर ((inst_nr >= edac_dev->nr_instances) || (inst_nr < 0)) अणु
		edac_device_prपूर्णांकk(edac_dev, KERN_ERR,
				"INTERNAL ERROR: 'instance' out of range "
				"(%d >= %d)\n", inst_nr,
				edac_dev->nr_instances);
		वापस;
	पूर्ण

	instance = edac_dev->instances + inst_nr;

	अगर ((block_nr >= instance->nr_blocks) || (block_nr < 0)) अणु
		edac_device_prपूर्णांकk(edac_dev, KERN_ERR,
				"INTERNAL ERROR: instance %d 'block' "
				"out of range (%d >= %d)\n",
				inst_nr, block_nr,
				instance->nr_blocks);
		वापस;
	पूर्ण

	अगर (instance->nr_blocks > 0) अणु
		block = instance->blocks + block_nr;
		block->counters.ce_count += count;
	पूर्ण

	/* Propagate the count up the 'totals' tree */
	instance->counters.ce_count += count;
	edac_dev->counters.ce_count += count;

	अगर (edac_device_get_log_ce(edac_dev))
		edac_device_prपूर्णांकk(edac_dev, KERN_WARNING,
				   "CE: %s instance: %s block: %s count: %d '%s'\n",
				   edac_dev->ctl_name, instance->name,
				   block ? block->name : "N/A", count, msg);
पूर्ण
EXPORT_SYMBOL_GPL(edac_device_handle_ce_count);

व्योम edac_device_handle_ue_count(काष्ठा edac_device_ctl_info *edac_dev,
				 अचिन्हित पूर्णांक count, पूर्णांक inst_nr, पूर्णांक block_nr,
				 स्थिर अक्षर *msg)
अणु
	काष्ठा edac_device_instance *instance;
	काष्ठा edac_device_block *block = शून्य;

	अगर (!count)
		वापस;

	अगर ((inst_nr >= edac_dev->nr_instances) || (inst_nr < 0)) अणु
		edac_device_prपूर्णांकk(edac_dev, KERN_ERR,
				"INTERNAL ERROR: 'instance' out of range "
				"(%d >= %d)\n", inst_nr,
				edac_dev->nr_instances);
		वापस;
	पूर्ण

	instance = edac_dev->instances + inst_nr;

	अगर ((block_nr >= instance->nr_blocks) || (block_nr < 0)) अणु
		edac_device_prपूर्णांकk(edac_dev, KERN_ERR,
				"INTERNAL ERROR: instance %d 'block' "
				"out of range (%d >= %d)\n",
				inst_nr, block_nr,
				instance->nr_blocks);
		वापस;
	पूर्ण

	अगर (instance->nr_blocks > 0) अणु
		block = instance->blocks + block_nr;
		block->counters.ue_count += count;
	पूर्ण

	/* Propagate the count up the 'totals' tree */
	instance->counters.ue_count += count;
	edac_dev->counters.ue_count += count;

	अगर (edac_device_get_log_ue(edac_dev))
		edac_device_prपूर्णांकk(edac_dev, KERN_EMERG,
				   "UE: %s instance: %s block: %s count: %d '%s'\n",
				   edac_dev->ctl_name, instance->name,
				   block ? block->name : "N/A", count, msg);

	अगर (edac_device_get_panic_on_ue(edac_dev))
		panic("EDAC %s: UE instance: %s block %s count: %d '%s'\n",
		      edac_dev->ctl_name, instance->name,
		      block ? block->name : "N/A", count, msg);
पूर्ण
EXPORT_SYMBOL_GPL(edac_device_handle_ue_count);
