<शैली गुरु>
/*
 * Defines, काष्ठाures, APIs क्रम edac_device
 *
 * (C) 2007 Linux Networx (http://lnxi.com)
 * This file may be distributed under the terms of the
 * GNU General Public License.
 *
 * Written by Thayne Harbaugh
 * Based on work by Dan Hollis <goemon at anime करोt net> and others.
 *	http://www.anime.net/~goemon/linux-ecc/
 *
 * NMI handling support added by
 *     Dave Peterson <dsp@llnl.gov> <dave_peterson@pobox.com>
 *
 * Refactored क्रम multi-source files:
 *	Doug Thompson <norsk5@xmission.com>
 *
 * Please look at Documentation/driver-api/edac.rst क्रम more info about
 * EDAC core काष्ठाs and functions.
 */

#अगर_अघोषित _EDAC_DEVICE_H_
#घोषणा _EDAC_DEVICE_H_

#समावेश <linux/completion.h>
#समावेश <linux/device.h>
#समावेश <linux/edac.h>
#समावेश <linux/kobject.h>
#समावेश <linux/list.h>
#समावेश <linux/types.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/workqueue.h>


/*
 * The following are the काष्ठाures to provide क्रम a generic
 * or असलtract 'edac_device'. This set of काष्ठाures and the
 * code that implements the APIs क्रम the same, provide क्रम
 * रेजिस्टरing EDAC type devices which are NOT standard memory.
 *
 * CPU caches (L1 and L2)
 * DMA engines
 * Core CPU चयनes
 * Fabric चयन units
 * PCIe पूर्णांकerface controllers
 * other EDAC/ECC type devices that can be monitored क्रम
 * errors, etc.
 *
 * It allows क्रम a 2 level set of hierarchy. For example:
 *
 * cache could be composed of L1, L2 and L3 levels of cache.
 * Each CPU core would have its own L1 cache, जबतक sharing
 * L2 and maybe L3 caches.
 *
 * View them arranged, via the sysfs presentation:
 * /sys/devices/प्रणाली/edac/..
 *
 *	mc/		<existing memory device directory>
 *	cpu/cpu0/..	<L1 and L2 block directory>
 *		/L1-cache/ce_count
 *			 /ue_count
 *		/L2-cache/ce_count
 *			 /ue_count
 *	cpu/cpu1/..	<L1 and L2 block directory>
 *		/L1-cache/ce_count
 *			 /ue_count
 *		/L2-cache/ce_count
 *			 /ue_count
 *	...
 *
 *	the L1 and L2 directories would be "edac_device_block's"
 */

काष्ठा edac_device_counter अणु
	u32 ue_count;
	u32 ce_count;
पूर्ण;

/* क्रमward reference */
काष्ठा edac_device_ctl_info;
काष्ठा edac_device_block;

/* edac_dev_sysfs_attribute काष्ठाure
 *	used क्रम driver sysfs attributes in mem_ctl_info
 *	क्रम extra controls and attributes:
 *		like high level error Injection controls
 */
काष्ठा edac_dev_sysfs_attribute अणु
	काष्ठा attribute attr;
	sमाप_प्रकार (*show)(काष्ठा edac_device_ctl_info *, अक्षर *);
	sमाप_प्रकार (*store)(काष्ठा edac_device_ctl_info *, स्थिर अक्षर *, माप_प्रकार);
पूर्ण;

/* edac_dev_sysfs_block_attribute काष्ठाure
 *
 *	used in leaf 'block' nodes क्रम adding controls/attributes
 *
 *	each block in each instance of the containing control काष्ठाure
 *	can have an array of the following. The show and store functions
 *	will be filled in with the show/store function in the
 *	low level driver.
 *
 *	The 'value' field will be the actual value field used क्रम
 *	counting
 */
काष्ठा edac_dev_sysfs_block_attribute अणु
	काष्ठा attribute attr;
	sमाप_प्रकार (*show)(काष्ठा kobject *, काष्ठा attribute *, अक्षर *);
	sमाप_प्रकार (*store)(काष्ठा kobject *, काष्ठा attribute *,
			स्थिर अक्षर *, माप_प्रकार);
	काष्ठा edac_device_block *block;

	अचिन्हित पूर्णांक value;
पूर्ण;

/* device block control काष्ठाure */
काष्ठा edac_device_block अणु
	काष्ठा edac_device_instance *instance;	/* Up Poपूर्णांकer */
	अक्षर name[EDAC_DEVICE_NAME_LEN + 1];

	काष्ठा edac_device_counter counters;	/* basic UE and CE counters */

	पूर्णांक nr_attribs;		/* how many attributes */

	/* this block's attributes, could be शून्य */
	काष्ठा edac_dev_sysfs_block_attribute *block_attributes;

	/* edac sysfs device control */
	काष्ठा kobject kobj;
पूर्ण;

/* device instance control काष्ठाure */
काष्ठा edac_device_instance अणु
	काष्ठा edac_device_ctl_info *ctl;	/* Up poपूर्णांकer */
	अक्षर name[EDAC_DEVICE_NAME_LEN + 4];

	काष्ठा edac_device_counter counters;	/* instance counters */

	u32 nr_blocks;		/* how many blocks */
	काष्ठा edac_device_block *blocks;	/* block array */

	/* edac sysfs device control */
	काष्ठा kobject kobj;
पूर्ण;


/*
 * Abstract edac_device control info काष्ठाure
 *
 */
काष्ठा edac_device_ctl_info अणु
	/* क्रम global list of edac_device_ctl_info काष्ठाs */
	काष्ठा list_head link;

	काष्ठा module *owner;	/* Module owner of this control काष्ठा */

	पूर्णांक dev_idx;

	/* Per instance controls क्रम this edac_device */
	पूर्णांक log_ue;		/* boolean क्रम logging UEs */
	पूर्णांक log_ce;		/* boolean क्रम logging CEs */
	पूर्णांक panic_on_ue;	/* boolean क्रम panic'ing on an UE */
	अचिन्हित poll_msec;	/* number of milliseconds to poll पूर्णांकerval */
	अचिन्हित दीर्घ delay;	/* number of jअगरfies क्रम poll_msec */

	/* Additional top controller level attributes, but specअगरied
	 * by the low level driver.
	 *
	 * Set by the low level driver to provide attributes at the
	 * controller level, same level as 'ue_count' and 'ce_count' above.
	 * An array of काष्ठाures, शून्य terminated
	 *
	 * If attributes are desired, then set to array of attributes
	 * If no attributes are desired, leave शून्य
	 */
	काष्ठा edac_dev_sysfs_attribute *sysfs_attributes;

	/* poपूर्णांकer to मुख्य 'edac' subsys in sysfs */
	काष्ठा bus_type *edac_subsys;

	/* the पूर्णांकernal state of this controller instance */
	पूर्णांक op_state;
	/* work काष्ठा क्रम this instance */
	काष्ठा delayed_work work;

	/* poपूर्णांकer to edac polling checking routine:
	 *      If NOT शून्य: poपूर्णांकs to polling check routine
	 *      If शून्य: Then assumes INTERRUPT operation, where
	 *              MC driver will receive events
	 */
	व्योम (*edac_check) (काष्ठा edac_device_ctl_info * edac_dev);

	काष्ठा device *dev;	/* poपूर्णांकer to device काष्ठाure */

	स्थिर अक्षर *mod_name;	/* module name */
	स्थिर अक्षर *ctl_name;	/* edac controller  name */
	स्थिर अक्षर *dev_name;	/* pci/platक्रमm/etc... name */

	व्योम *pvt_info;		/* poपूर्णांकer to 'private driver' info */

	अचिन्हित दीर्घ start_समय;	/* edac_device load start समय (jअगरfies) */

	काष्ठा completion removal_complete;

	/* sysfs top name under 'edac' directory
	 * and instance name:
	 *      cpu/cpu0/...
	 *      cpu/cpu1/...
	 *      cpu/cpu2/...
	 *      ...
	 */
	अक्षर name[EDAC_DEVICE_NAME_LEN + 1];

	/* Number of instances supported on this control काष्ठाure
	 * and the array of those instances
	 */
	u32 nr_instances;
	काष्ठा edac_device_instance *instances;

	/* Event counters क्रम the this whole EDAC Device */
	काष्ठा edac_device_counter counters;

	/* edac sysfs device control क्रम the 'name'
	 * device this काष्ठाure controls
	 */
	काष्ठा kobject kobj;
पूर्ण;

/* To get from the instance's wq to the beginning of the ctl काष्ठाure */
#घोषणा to_edac_mem_ctl_work(w) \
		container_of(w, काष्ठा mem_ctl_info, work)

#घोषणा to_edac_device_ctl_work(w) \
		container_of(w,काष्ठा edac_device_ctl_info,work)

/*
 * The alloc() and मुक्त() functions क्रम the 'edac_device' control info
 * काष्ठाure. A MC driver will allocate one of these क्रम each edac_device
 * it is going to control/रेजिस्टर with the EDAC CORE.
 */
बाह्य काष्ठा edac_device_ctl_info *edac_device_alloc_ctl_info(
		अचिन्हित माप_निजी,
		अक्षर *edac_device_name, अचिन्हित nr_instances,
		अक्षर *edac_block_name, अचिन्हित nr_blocks,
		अचिन्हित offset_value,
		काष्ठा edac_dev_sysfs_block_attribute *block_attributes,
		अचिन्हित nr_attribs,
		पूर्णांक device_index);

/* The offset value can be:
 *	-1 indicating no offset value
 *	0 क्रम zero-based block numbers
 *	1 क्रम 1-based block number
 *	other क्रम other-based block number
 */
#घोषणा	BLOCK_OFFSET_VALUE_OFF	((अचिन्हित) -1)

बाह्य व्योम edac_device_मुक्त_ctl_info(काष्ठा edac_device_ctl_info *ctl_info);

/**
 * edac_device_add_device - Insert the 'edac_dev' काष्ठाure पूर्णांकo the
 *	 edac_device global list and create sysfs entries associated with
 *	 edac_device काष्ठाure.
 *
 * @edac_dev: poपूर्णांकer to edac_device काष्ठाure to be added to the list
 *	'edac_device' काष्ठाure.
 *
 * Returns:
 *	0 on Success, or an error code on failure
 */
बाह्य पूर्णांक edac_device_add_device(काष्ठा edac_device_ctl_info *edac_dev);

/**
 * edac_device_del_device - Remove sysfs entries क्रम specअगरied edac_device
 *	काष्ठाure and then हटाओ edac_device काष्ठाure from global list
 *
 * @dev:
 *	Poपूर्णांकer to काष्ठा &device representing the edac device
 *	काष्ठाure to हटाओ.
 *
 * Returns:
 *	Poपूर्णांकer to हटाओd edac_device काष्ठाure,
 *	or %शून्य अगर device not found.
 */
बाह्य काष्ठा edac_device_ctl_info *edac_device_del_device(काष्ठा device *dev);

/**
 * edac_device_handle_ce_count - Log correctable errors.
 *
 * @edac_dev: poपूर्णांकer to काष्ठा &edac_device_ctl_info
 * @inst_nr: number of the instance where the CE error happened
 * @count: Number of errors to log.
 * @block_nr: number of the block where the CE error happened
 * @msg: message to be prपूर्णांकed
 */
व्योम edac_device_handle_ce_count(काष्ठा edac_device_ctl_info *edac_dev,
				 अचिन्हित पूर्णांक count, पूर्णांक inst_nr, पूर्णांक block_nr,
				 स्थिर अक्षर *msg);

/**
 * edac_device_handle_ue_count - Log uncorrectable errors.
 *
 * @edac_dev: poपूर्णांकer to काष्ठा &edac_device_ctl_info
 * @inst_nr: number of the instance where the CE error happened
 * @count: Number of errors to log.
 * @block_nr: number of the block where the CE error happened
 * @msg: message to be prपूर्णांकed
 */
व्योम edac_device_handle_ue_count(काष्ठा edac_device_ctl_info *edac_dev,
				 अचिन्हित पूर्णांक count, पूर्णांक inst_nr, पूर्णांक block_nr,
				 स्थिर अक्षर *msg);

/**
 * edac_device_handle_ce(): Log a single correctable error
 *
 * @edac_dev: poपूर्णांकer to काष्ठा &edac_device_ctl_info
 * @inst_nr: number of the instance where the CE error happened
 * @block_nr: number of the block where the CE error happened
 * @msg: message to be prपूर्णांकed
 */
अटल अंतरभूत व्योम
edac_device_handle_ce(काष्ठा edac_device_ctl_info *edac_dev, पूर्णांक inst_nr,
		      पूर्णांक block_nr, स्थिर अक्षर *msg)
अणु
	edac_device_handle_ce_count(edac_dev, 1, inst_nr, block_nr, msg);
पूर्ण

/**
 * edac_device_handle_ue(): Log a single uncorrectable error
 *
 * @edac_dev: poपूर्णांकer to काष्ठा &edac_device_ctl_info
 * @inst_nr: number of the instance where the UE error happened
 * @block_nr: number of the block where the UE error happened
 * @msg: message to be prपूर्णांकed
 */
अटल अंतरभूत व्योम
edac_device_handle_ue(काष्ठा edac_device_ctl_info *edac_dev, पूर्णांक inst_nr,
		      पूर्णांक block_nr, स्थिर अक्षर *msg)
अणु
	edac_device_handle_ue_count(edac_dev, 1, inst_nr, block_nr, msg);
पूर्ण

/**
 * edac_device_alloc_index: Allocate a unique device index number
 *
 * Returns:
 *	allocated index number
 */
बाह्य पूर्णांक edac_device_alloc_index(व्योम);
बाह्य स्थिर अक्षर *edac_layer_name[];
#पूर्ण_अगर
