<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* 
 *    Interfaces to retrieve and set PDC Stable options (firmware)
 *
 *    Copyright (C) 2005-2006 Thibaut VARENE <varenet@parisc-linux.org>
 *
 *    DEV NOTE: the PDC Procedures reference states that:
 *    "A minimum of 96 bytes of Stable Storage is required. Providing more than
 *    96 bytes of Stable Storage is optional [...]. Failure to provide the
 *    optional locations from 96 to 192 results in the loss of certain
 *    functionality during boot."
 *
 *    Since locations between 96 and 192 are the various paths, most (अगर not
 *    all) PA-RISC machines should have them. Anyway, क्रम safety reasons, the
 *    following code can deal with just 96 bytes of Stable Storage, and all
 *    sizes between 96 and 192 bytes (provided they are multiple of काष्ठा
 *    device_path size, eg: 128, 160 and 192) to provide full inक्रमmation.
 *    One last word: there's one path we can always count on: the primary path.
 *    Anything above 224 bytes is used क्रम 'osdep2' OS-dependent storage area.
 *
 *    The first OS-dependent area should always be available. Obviously, this is
 *    not true क्रम the other one. Also bear in mind that पढ़ोing/writing from/to
 *    osdep2 is much more expensive than from/to osdep1.
 *    NOTE: We करो not handle the 2 bytes OS-dep area at 0x5D, nor the first
 *    2 bytes of storage available right after OSID. That's a total of 4 bytes
 *    sacrअगरiced: -ETOOLAZY :P
 *
 *    The current policy wrt file permissions is:
 *	- ग_लिखो: root only
 *	- पढ़ो: (पढ़ोing triggers PDC calls) ? root only : everyone
 *    The rationale is that PDC calls could hog (DoS) the machine.
 *
 *	TODO:
 *	- समयr/fastsize ग_लिखो calls
 */

#अघोषित PDCS_DEBUG
#अगर_घोषित PDCS_DEBUG
#घोषणा DPRINTK(fmt, args...)	prपूर्णांकk(KERN_DEBUG fmt, ## args)
#अन्यथा
#घोषणा DPRINTK(fmt, args...)
#पूर्ण_अगर

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/capability.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/sysfs.h>
#समावेश <linux/kobject.h>
#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/spinlock.h>

#समावेश <यंत्र/pdc.h>
#समावेश <यंत्र/page.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/hardware.h>

#घोषणा PDCS_VERSION	"0.30"
#घोषणा PDCS_PREFIX	"PDC Stable Storage"

#घोषणा PDCS_ADDR_PPRI	0x00
#घोषणा PDCS_ADDR_OSID	0x40
#घोषणा PDCS_ADDR_OSD1	0x48
#घोषणा PDCS_ADDR_DIAG	0x58
#घोषणा PDCS_ADDR_FSIZ	0x5C
#घोषणा PDCS_ADDR_PCON	0x60
#घोषणा PDCS_ADDR_PALT	0x80
#घोषणा PDCS_ADDR_PKBD	0xA0
#घोषणा PDCS_ADDR_OSD2	0xE0

MODULE_AUTHOR("Thibaut VARENE <varenet@parisc-linux.org>");
MODULE_DESCRIPTION("sysfs interface to HP PDC Stable Storage data");
MODULE_LICENSE("GPL");
MODULE_VERSION(PDCS_VERSION);

/* holds Stable Storage size. Initialized once and क्रम all, no lock needed */
अटल अचिन्हित दीर्घ pdcs_size __पढ़ो_mostly;

/* holds OS ID. Initialized once and क्रम all, hopefully to 0x0006 */
अटल u16 pdcs_osid __पढ़ो_mostly;

/* This काष्ठा defines what we need to deal with a parisc pdc path entry */
काष्ठा pdcspath_entry अणु
	rwlock_t rw_lock;		/* to protect path entry access */
	लघु पढ़ोy;			/* entry record is valid अगर != 0 */
	अचिन्हित दीर्घ addr;		/* entry address in stable storage */
	अक्षर *name;			/* entry name */
	काष्ठा device_path devpath;	/* device path in parisc representation */
	काष्ठा device *dev;		/* corresponding device */
	काष्ठा kobject kobj;
पूर्ण;

काष्ठा pdcspath_attribute अणु
	काष्ठा attribute attr;
	sमाप_प्रकार (*show)(काष्ठा pdcspath_entry *entry, अक्षर *buf);
	sमाप_प्रकार (*store)(काष्ठा pdcspath_entry *entry, स्थिर अक्षर *buf, माप_प्रकार count);
पूर्ण;

#घोषणा PDCSPATH_ENTRY(_addr, _name) \
काष्ठा pdcspath_entry pdcspath_entry_##_name = अणु \
	.पढ़ोy = 0, \
	.addr = _addr, \
	.name = __stringअगरy(_name), \
पूर्ण;

#घोषणा PDCS_ATTR(_name, _mode, _show, _store) \
काष्ठा kobj_attribute pdcs_attr_##_name = अणु \
	.attr = अणु.name = __stringअगरy(_name), .mode = _modeपूर्ण, \
	.show = _show, \
	.store = _store, \
पूर्ण;

#घोषणा PATHS_ATTR(_name, _mode, _show, _store) \
काष्ठा pdcspath_attribute paths_attr_##_name = अणु \
	.attr = अणु.name = __stringअगरy(_name), .mode = _modeपूर्ण, \
	.show = _show, \
	.store = _store, \
पूर्ण;

#घोषणा to_pdcspath_attribute(_attr) container_of(_attr, काष्ठा pdcspath_attribute, attr)
#घोषणा to_pdcspath_entry(obj)  container_of(obj, काष्ठा pdcspath_entry, kobj)

/**
 * pdcspath_fetch - This function populates the path entry काष्ठाs.
 * @entry: A poपूर्णांकer to an allocated pdcspath_entry.
 * 
 * The general idea is that you करोn't पढ़ो from the Stable Storage every समय
 * you access the files provided by the facilities. We store a copy of the
 * content of the stable storage WRT various paths in these काष्ठाs. We पढ़ो
 * these काष्ठाs when पढ़ोing the files, and we will ग_लिखो to these काष्ठाs when
 * writing to the files, and only then ग_लिखो them back to the Stable Storage.
 *
 * This function expects to be called with @entry->rw_lock ग_लिखो-hold.
 */
अटल पूर्णांक
pdcspath_fetch(काष्ठा pdcspath_entry *entry)
अणु
	काष्ठा device_path *devpath;

	अगर (!entry)
		वापस -EINVAL;

	devpath = &entry->devpath;
	
	DPRINTK("%s: fetch: 0x%p, 0x%p, addr: 0x%lx\n", __func__,
			entry, devpath, entry->addr);

	/* addr, devpath and count must be word aligned */
	अगर (pdc_stable_पढ़ो(entry->addr, devpath, माप(*devpath)) != PDC_OK)
		वापस -EIO;
		
	/* Find the matching device.
	   NOTE: hardware_path overlays with device_path, so the nice cast can
	   be used */
	entry->dev = hwpath_to_device((काष्ठा hardware_path *)devpath);

	entry->पढ़ोy = 1;
	
	DPRINTK("%s: device: 0x%p\n", __func__, entry->dev);
	
	वापस 0;
पूर्ण

/**
 * pdcspath_store - This function ग_लिखोs a path to stable storage.
 * @entry: A poपूर्णांकer to an allocated pdcspath_entry.
 * 
 * It can be used in two ways: either by passing it a preset devpath काष्ठा
 * containing an alपढ़ोy computed hardware path, or by passing it a device
 * poपूर्णांकer, from which it'll find out the corresponding hardware path.
 * For now we करो not handle the हाल where there's an error in writing to the
 * Stable Storage area, so you'd better not mess up the data :P
 *
 * This function expects to be called with @entry->rw_lock ग_लिखो-hold.
 */
अटल व्योम
pdcspath_store(काष्ठा pdcspath_entry *entry)
अणु
	काष्ठा device_path *devpath;

	BUG_ON(!entry);

	devpath = &entry->devpath;
	
	/* We expect the caller to set the पढ़ोy flag to 0 अगर the hardware
	   path काष्ठा provided is invalid, so that we know we have to fill it.
	   First हाल, we करोn't have a preset hwpath... */
	अगर (!entry->पढ़ोy) अणु
		/* ...but we have a device, map it */
		BUG_ON(!entry->dev);
		device_to_hwpath(entry->dev, (काष्ठा hardware_path *)devpath);
	पूर्ण
	/* अन्यथा, we expect the provided hwpath to be valid. */
	
	DPRINTK("%s: store: 0x%p, 0x%p, addr: 0x%lx\n", __func__,
			entry, devpath, entry->addr);

	/* addr, devpath and count must be word aligned */
	अगर (pdc_stable_ग_लिखो(entry->addr, devpath, माप(*devpath)) != PDC_OK)
		WARN(1, KERN_ERR "%s: an error occurred when writing to PDC.\n"
				"It is likely that the Stable Storage data has been corrupted.\n"
				"Please check it carefully upon next reboot.\n", __func__);
		
	/* kobject is alपढ़ोy रेजिस्टरed */
	entry->पढ़ोy = 2;
	
	DPRINTK("%s: device: 0x%p\n", __func__, entry->dev);
पूर्ण

/**
 * pdcspath_hwpath_पढ़ो - This function handles hardware path pretty prपूर्णांकing.
 * @entry: An allocated and populated pdscpath_entry काष्ठा.
 * @buf: The output buffer to ग_लिखो to.
 * 
 * We will call this function to क्रमmat the output of the hwpath attribute file.
 */
अटल sमाप_प्रकार
pdcspath_hwpath_पढ़ो(काष्ठा pdcspath_entry *entry, अक्षर *buf)
अणु
	अक्षर *out = buf;
	काष्ठा device_path *devpath;
	लघु i;

	अगर (!entry || !buf)
		वापस -EINVAL;

	पढ़ो_lock(&entry->rw_lock);
	devpath = &entry->devpath;
	i = entry->पढ़ोy;
	पढ़ो_unlock(&entry->rw_lock);

	अगर (!i)	/* entry is not पढ़ोy */
		वापस -ENODATA;
	
	क्रम (i = 0; i < 6; i++) अणु
		अगर (devpath->bc[i] >= 128)
			जारी;
		out += प्र_लिखो(out, "%u/", (अचिन्हित अक्षर)devpath->bc[i]);
	पूर्ण
	out += प्र_लिखो(out, "%u\n", (अचिन्हित अक्षर)devpath->mod);
	
	वापस out - buf;
पूर्ण

/**
 * pdcspath_hwpath_ग_लिखो - This function handles hardware path modअगरying.
 * @entry: An allocated and populated pdscpath_entry काष्ठा.
 * @buf: The input buffer to पढ़ो from.
 * @count: The number of bytes to be पढ़ो.
 * 
 * We will call this function to change the current hardware path.
 * Hardware paths are to be given '/'-delimited, without brackets.
 * We make sure that the provided path actually maps to an existing
 * device, BUT nothing would prevent some foolish user to set the path to some
 * PCI bridge or even a CPU...
 * A better work around would be to make sure we are at the end of a device tree
 * क्रम instance, but it would be IMHO beyond the simple scope of that driver.
 * The aim is to provide a facility. Data correctness is left to userland.
 */
अटल sमाप_प्रकार
pdcspath_hwpath_ग_लिखो(काष्ठा pdcspath_entry *entry, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा hardware_path hwpath;
	अचिन्हित लघु i;
	अक्षर in[64], *temp;
	काष्ठा device *dev;
	पूर्णांक ret;

	अगर (!entry || !buf || !count)
		वापस -EINVAL;

	/* We'll use a local copy of buf */
	count = min_t(माप_प्रकार, count, माप(in)-1);
	म_नकलन(in, buf, count);
	in[count] = '\0';
	
	/* Let's clean up the target. 0xff is a blank pattern */
	स_रखो(&hwpath, 0xff, माप(hwpath));
	
	/* First, pick the mod field (the last one of the input string) */
	अगर (!(temp = म_खोजप(in, '/')))
		वापस -EINVAL;
			
	hwpath.mod = simple_म_से_अदीर्घ(temp+1, शून्य, 10);
	in[temp-in] = '\0';	/* truncate the reमुख्यing string. just precaution */
	DPRINTK("%s: mod: %d\n", __func__, hwpath.mod);
	
	/* Then, loop क्रम each delimiter, making sure we करोn't have too many.
	   we ग_लिखो the bc fields in a करोwn-top way. No matter what, we stop
	   beक्रमe writing the last field. If there are too many fields anyway,
	   then the user is a moron and it'll be caught up later when we'll
	   check the consistency of the given hwpath. */
	क्रम (i=5; ((temp = म_खोजप(in, '/'))) && (temp-in > 0) && (likely(i)); i--) अणु
		hwpath.bc[i] = simple_म_से_अदीर्घ(temp+1, शून्य, 10);
		in[temp-in] = '\0';
		DPRINTK("%s: bc[%d]: %d\n", __func__, i, hwpath.bc[i]);
	पूर्ण
	
	/* Store the final field */		
	hwpath.bc[i] = simple_म_से_अदीर्घ(in, शून्य, 10);
	DPRINTK("%s: bc[%d]: %d\n", __func__, i, hwpath.bc[i]);
	
	/* Now we check that the user isn't trying to lure us */
	अगर (!(dev = hwpath_to_device((काष्ठा hardware_path *)&hwpath))) अणु
		prपूर्णांकk(KERN_WARNING "%s: attempt to set invalid \"%s\" "
			"hardware path: %s\n", __func__, entry->name, buf);
		वापस -EINVAL;
	पूर्ण
	
	/* So far so good, let's get in deep */
	ग_लिखो_lock(&entry->rw_lock);
	entry->पढ़ोy = 0;
	entry->dev = dev;
	
	/* Now, भागe in. Write back to the hardware */
	pdcspath_store(entry);
	
	/* Update the symlink to the real device */
	sysfs_हटाओ_link(&entry->kobj, "device");
	ग_लिखो_unlock(&entry->rw_lock);

	ret = sysfs_create_link(&entry->kobj, &entry->dev->kobj, "device");
	WARN_ON(ret);

	prपूर्णांकk(KERN_INFO PDCS_PREFIX ": changed \"%s\" path to \"%s\"\n",
		entry->name, buf);
	
	वापस count;
पूर्ण

/**
 * pdcspath_layer_पढ़ो - Extended layer (eg. SCSI ids) pretty prपूर्णांकing.
 * @entry: An allocated and populated pdscpath_entry काष्ठा.
 * @buf: The output buffer to ग_लिखो to.
 * 
 * We will call this function to क्रमmat the output of the layer attribute file.
 */
अटल sमाप_प्रकार
pdcspath_layer_पढ़ो(काष्ठा pdcspath_entry *entry, अक्षर *buf)
अणु
	अक्षर *out = buf;
	काष्ठा device_path *devpath;
	लघु i;

	अगर (!entry || !buf)
		वापस -EINVAL;
	
	पढ़ो_lock(&entry->rw_lock);
	devpath = &entry->devpath;
	i = entry->पढ़ोy;
	पढ़ो_unlock(&entry->rw_lock);

	अगर (!i)	/* entry is not पढ़ोy */
		वापस -ENODATA;
	
	क्रम (i = 0; i < 6 && devpath->layers[i]; i++)
		out += प्र_लिखो(out, "%u ", devpath->layers[i]);

	out += प्र_लिखो(out, "\n");
	
	वापस out - buf;
पूर्ण

/**
 * pdcspath_layer_ग_लिखो - This function handles extended layer modअगरying.
 * @entry: An allocated and populated pdscpath_entry काष्ठा.
 * @buf: The input buffer to पढ़ो from.
 * @count: The number of bytes to be पढ़ो.
 * 
 * We will call this function to change the current layer value.
 * Layers are to be given '.'-delimited, without brackets.
 * XXX beware we are far less checky WRT input data provided than क्रम hwpath.
 * Potential harm can be करोne, since there's no way to check the validity of
 * the layer fields.
 */
अटल sमाप_प्रकार
pdcspath_layer_ग_लिखो(काष्ठा pdcspath_entry *entry, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित पूर्णांक layers[6]; /* device-specअगरic info (ctlr#, unit#, ...) */
	अचिन्हित लघु i;
	अक्षर in[64], *temp;

	अगर (!entry || !buf || !count)
		वापस -EINVAL;

	/* We'll use a local copy of buf */
	count = min_t(माप_प्रकार, count, माप(in)-1);
	म_नकलन(in, buf, count);
	in[count] = '\0';
	
	/* Let's clean up the target. 0 is a blank pattern */
	स_रखो(&layers, 0, माप(layers));
	
	/* First, pick the first layer */
	अगर (unlikely(!है_अंक(*in)))
		वापस -EINVAL;
	layers[0] = simple_म_से_अदीर्घ(in, शून्य, 10);
	DPRINTK("%s: layer[0]: %d\n", __func__, layers[0]);
	
	temp = in;
	क्रम (i=1; ((temp = म_अक्षर(temp, '.'))) && (likely(i<6)); i++) अणु
		अगर (unlikely(!है_अंक(*(++temp))))
			वापस -EINVAL;
		layers[i] = simple_म_से_अदीर्घ(temp, शून्य, 10);
		DPRINTK("%s: layer[%d]: %d\n", __func__, i, layers[i]);
	पूर्ण
		
	/* So far so good, let's get in deep */
	ग_लिखो_lock(&entry->rw_lock);
	
	/* First, overग_लिखो the current layers with the new ones, not touching
	   the hardware path. */
	स_नकल(&entry->devpath.layers, &layers, माप(layers));
	
	/* Now, भागe in. Write back to the hardware */
	pdcspath_store(entry);
	ग_लिखो_unlock(&entry->rw_lock);
	
	prपूर्णांकk(KERN_INFO PDCS_PREFIX ": changed \"%s\" layers to \"%s\"\n",
		entry->name, buf);
	
	वापस count;
पूर्ण

/**
 * pdcspath_attr_show - Generic पढ़ो function call wrapper.
 * @kobj: The kobject to get info from.
 * @attr: The attribute looked upon.
 * @buf: The output buffer.
 */
अटल sमाप_प्रकार
pdcspath_attr_show(काष्ठा kobject *kobj, काष्ठा attribute *attr, अक्षर *buf)
अणु
	काष्ठा pdcspath_entry *entry = to_pdcspath_entry(kobj);
	काष्ठा pdcspath_attribute *pdcs_attr = to_pdcspath_attribute(attr);
	sमाप_प्रकार ret = 0;

	अगर (pdcs_attr->show)
		ret = pdcs_attr->show(entry, buf);

	वापस ret;
पूर्ण

/**
 * pdcspath_attr_store - Generic ग_लिखो function call wrapper.
 * @kobj: The kobject to ग_लिखो info to.
 * @attr: The attribute to be modअगरied.
 * @buf: The input buffer.
 * @count: The size of the buffer.
 */
अटल sमाप_प्रकार
pdcspath_attr_store(काष्ठा kobject *kobj, काष्ठा attribute *attr,
			स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा pdcspath_entry *entry = to_pdcspath_entry(kobj);
	काष्ठा pdcspath_attribute *pdcs_attr = to_pdcspath_attribute(attr);
	sमाप_प्रकार ret = 0;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EACCES;

	अगर (pdcs_attr->store)
		ret = pdcs_attr->store(entry, buf, count);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा sysfs_ops pdcspath_attr_ops = अणु
	.show = pdcspath_attr_show,
	.store = pdcspath_attr_store,
पूर्ण;

/* These are the two attributes of any PDC path. */
अटल PATHS_ATTR(hwpath, 0644, pdcspath_hwpath_पढ़ो, pdcspath_hwpath_ग_लिखो);
अटल PATHS_ATTR(layer, 0644, pdcspath_layer_पढ़ो, pdcspath_layer_ग_लिखो);

अटल काष्ठा attribute *paths_subsys_attrs[] = अणु
	&paths_attr_hwpath.attr,
	&paths_attr_layer.attr,
	शून्य,
पूर्ण;

/* Specअगरic kobject type क्रम our PDC paths */
अटल काष्ठा kobj_type ktype_pdcspath = अणु
	.sysfs_ops = &pdcspath_attr_ops,
	.शेष_attrs = paths_subsys_attrs,
पूर्ण;

/* We hard define the 4 types of path we expect to find */
अटल PDCSPATH_ENTRY(PDCS_ADDR_PPRI, primary);
अटल PDCSPATH_ENTRY(PDCS_ADDR_PCON, console);
अटल PDCSPATH_ENTRY(PDCS_ADDR_PALT, alternative);
अटल PDCSPATH_ENTRY(PDCS_ADDR_PKBD, keyboard);

/* An array containing all PDC paths we will deal with */
अटल काष्ठा pdcspath_entry *pdcspath_entries[] = अणु
	&pdcspath_entry_primary,
	&pdcspath_entry_alternative,
	&pdcspath_entry_console,
	&pdcspath_entry_keyboard,
	शून्य,
पूर्ण;


/* For more insight of what's going on here, refer to PDC Procedures करोc,
 * Section PDC_STABLE */

/**
 * pdcs_size_पढ़ो - Stable Storage size output.
 * @buf: The output buffer to ग_लिखो to.
 */
अटल sमाप_प्रकार pdcs_size_पढ़ो(काष्ठा kobject *kobj,
			      काष्ठा kobj_attribute *attr,
			      अक्षर *buf)
अणु
	अक्षर *out = buf;

	अगर (!buf)
		वापस -EINVAL;

	/* show the size of the stable storage */
	out += प्र_लिखो(out, "%ld\n", pdcs_size);

	वापस out - buf;
पूर्ण

/**
 * pdcs_स्वतः_पढ़ो - Stable Storage स्वतःboot/search flag output.
 * @buf: The output buffer to ग_लिखो to.
 * @knob: The PF_AUTOBOOT or PF_AUTOSEARCH flag
 */
अटल sमाप_प्रकार pdcs_स्वतः_पढ़ो(काष्ठा kobject *kobj,
			      काष्ठा kobj_attribute *attr,
			      अक्षर *buf, पूर्णांक knob)
अणु
	अक्षर *out = buf;
	काष्ठा pdcspath_entry *pathentry;

	अगर (!buf)
		वापस -EINVAL;

	/* Current flags are stored in primary boot path entry */
	pathentry = &pdcspath_entry_primary;

	पढ़ो_lock(&pathentry->rw_lock);
	out += प्र_लिखो(out, "%s\n", (pathentry->devpath.flags & knob) ?
					"On" : "Off");
	पढ़ो_unlock(&pathentry->rw_lock);

	वापस out - buf;
पूर्ण

/**
 * pdcs_स्वतःboot_पढ़ो - Stable Storage स्वतःboot flag output.
 * @buf: The output buffer to ग_लिखो to.
 */
अटल sमाप_प्रकार pdcs_स्वतःboot_पढ़ो(काष्ठा kobject *kobj,
				  काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	वापस pdcs_स्वतः_पढ़ो(kobj, attr, buf, PF_AUTOBOOT);
पूर्ण

/**
 * pdcs_स्वतःsearch_पढ़ो - Stable Storage स्वतःboot flag output.
 * @buf: The output buffer to ग_लिखो to.
 */
अटल sमाप_प्रकार pdcs_स्वतःsearch_पढ़ो(काष्ठा kobject *kobj,
				    काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	वापस pdcs_स्वतः_पढ़ो(kobj, attr, buf, PF_AUTOSEARCH);
पूर्ण

/**
 * pdcs_समयr_पढ़ो - Stable Storage समयr count output (in seconds).
 * @buf: The output buffer to ग_लिखो to.
 *
 * The value of the समयr field correponds to a number of seconds in घातers of 2.
 */
अटल sमाप_प्रकार pdcs_समयr_पढ़ो(काष्ठा kobject *kobj,
			       काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	अक्षर *out = buf;
	काष्ठा pdcspath_entry *pathentry;

	अगर (!buf)
		वापस -EINVAL;

	/* Current flags are stored in primary boot path entry */
	pathentry = &pdcspath_entry_primary;

	/* prपूर्णांक the समयr value in seconds */
	पढ़ो_lock(&pathentry->rw_lock);
	out += प्र_लिखो(out, "%u\n", (pathentry->devpath.flags & PF_TIMER) ?
				(1 << (pathentry->devpath.flags & PF_TIMER)) : 0);
	पढ़ो_unlock(&pathentry->rw_lock);

	वापस out - buf;
पूर्ण

/**
 * pdcs_osid_पढ़ो - Stable Storage OS ID रेजिस्टर output.
 * @buf: The output buffer to ग_लिखो to.
 */
अटल sमाप_प्रकार pdcs_osid_पढ़ो(काष्ठा kobject *kobj,
			      काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	अक्षर *out = buf;

	अगर (!buf)
		वापस -EINVAL;

	out += प्र_लिखो(out, "%s dependent data (0x%.4x)\n",
		os_id_to_string(pdcs_osid), pdcs_osid);

	वापस out - buf;
पूर्ण

/**
 * pdcs_osdep1_पढ़ो - Stable Storage OS-Dependent data area 1 output.
 * @buf: The output buffer to ग_लिखो to.
 *
 * This can hold 16 bytes of OS-Dependent data.
 */
अटल sमाप_प्रकार pdcs_osdep1_पढ़ो(काष्ठा kobject *kobj,
				काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	अक्षर *out = buf;
	u32 result[4];

	अगर (!buf)
		वापस -EINVAL;

	अगर (pdc_stable_पढ़ो(PDCS_ADDR_OSD1, &result, माप(result)) != PDC_OK)
		वापस -EIO;

	out += प्र_लिखो(out, "0x%.8x\n", result[0]);
	out += प्र_लिखो(out, "0x%.8x\n", result[1]);
	out += प्र_लिखो(out, "0x%.8x\n", result[2]);
	out += प्र_लिखो(out, "0x%.8x\n", result[3]);

	वापस out - buf;
पूर्ण

/**
 * pdcs_diagnostic_पढ़ो - Stable Storage Diagnostic रेजिस्टर output.
 * @buf: The output buffer to ग_लिखो to.
 *
 * I have NFC how to पूर्णांकerpret the content of that रेजिस्टर ;-).
 */
अटल sमाप_प्रकार pdcs_diagnostic_पढ़ो(काष्ठा kobject *kobj,
				    काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	अक्षर *out = buf;
	u32 result;

	अगर (!buf)
		वापस -EINVAL;

	/* get diagnostic */
	अगर (pdc_stable_पढ़ो(PDCS_ADDR_DIAG, &result, माप(result)) != PDC_OK)
		वापस -EIO;

	out += प्र_लिखो(out, "0x%.4x\n", (result >> 16));

	वापस out - buf;
पूर्ण

/**
 * pdcs_fastsize_पढ़ो - Stable Storage FastSize रेजिस्टर output.
 * @buf: The output buffer to ग_लिखो to.
 *
 * This रेजिस्टर holds the amount of प्रणाली RAM to be tested during boot sequence.
 */
अटल sमाप_प्रकार pdcs_fastsize_पढ़ो(काष्ठा kobject *kobj,
				  काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	अक्षर *out = buf;
	u32 result;

	अगर (!buf)
		वापस -EINVAL;

	/* get fast-size */
	अगर (pdc_stable_पढ़ो(PDCS_ADDR_FSIZ, &result, माप(result)) != PDC_OK)
		वापस -EIO;

	अगर ((result & 0x0F) < 0x0E)
		out += प्र_लिखो(out, "%d kB", (1<<(result & 0x0F))*256);
	अन्यथा
		out += प्र_लिखो(out, "All");
	out += प्र_लिखो(out, "\n");
	
	वापस out - buf;
पूर्ण

/**
 * pdcs_osdep2_पढ़ो - Stable Storage OS-Dependent data area 2 output.
 * @buf: The output buffer to ग_लिखो to.
 *
 * This can hold pdcs_size - 224 bytes of OS-Dependent data, when available.
 */
अटल sमाप_प्रकार pdcs_osdep2_पढ़ो(काष्ठा kobject *kobj,
				काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	अक्षर *out = buf;
	अचिन्हित दीर्घ size;
	अचिन्हित लघु i;
	u32 result;

	अगर (unlikely(pdcs_size <= 224))
		वापस -ENODATA;

	size = pdcs_size - 224;

	अगर (!buf)
		वापस -EINVAL;

	क्रम (i=0; i<size; i+=4) अणु
		अगर (unlikely(pdc_stable_पढ़ो(PDCS_ADDR_OSD2 + i, &result,
					माप(result)) != PDC_OK))
			वापस -EIO;
		out += प्र_लिखो(out, "0x%.8x\n", result);
	पूर्ण

	वापस out - buf;
पूर्ण

/**
 * pdcs_स्वतः_ग_लिखो - This function handles स्वतःboot/search flag modअगरying.
 * @buf: The input buffer to पढ़ो from.
 * @count: The number of bytes to be पढ़ो.
 * @knob: The PF_AUTOBOOT or PF_AUTOSEARCH flag
 * 
 * We will call this function to change the current स्वतःboot flag.
 * We expect a precise syntax:
 *	\"n\" (n == 0 or 1) to toggle AutoBoot Off or On
 */
अटल sमाप_प्रकार pdcs_स्वतः_ग_लिखो(काष्ठा kobject *kobj,
			       काष्ठा kobj_attribute *attr, स्थिर अक्षर *buf,
			       माप_प्रकार count, पूर्णांक knob)
अणु
	काष्ठा pdcspath_entry *pathentry;
	अचिन्हित अक्षर flags;
	अक्षर in[8], *temp;
	अक्षर c;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EACCES;

	अगर (!buf || !count)
		वापस -EINVAL;

	/* We'll use a local copy of buf */
	count = min_t(माप_प्रकार, count, माप(in)-1);
	म_नकलन(in, buf, count);
	in[count] = '\0';

	/* Current flags are stored in primary boot path entry */
	pathentry = &pdcspath_entry_primary;
	
	/* Be nice to the existing flag record */
	पढ़ो_lock(&pathentry->rw_lock);
	flags = pathentry->devpath.flags;
	पढ़ो_unlock(&pathentry->rw_lock);
	
	DPRINTK("%s: flags before: 0x%X\n", __func__, flags);

	temp = skip_spaces(in);

	c = *temp++ - '0';
	अगर ((c != 0) && (c != 1))
		जाओ parse_error;
	अगर (c == 0)
		flags &= ~knob;
	अन्यथा
		flags |= knob;
	
	DPRINTK("%s: flags after: 0x%X\n", __func__, flags);
		
	/* So far so good, let's get in deep */
	ग_लिखो_lock(&pathentry->rw_lock);
	
	/* Change the path entry flags first */
	pathentry->devpath.flags = flags;
		
	/* Now, भागe in. Write back to the hardware */
	pdcspath_store(pathentry);
	ग_लिखो_unlock(&pathentry->rw_lock);
	
	prपूर्णांकk(KERN_INFO PDCS_PREFIX ": changed \"%s\" to \"%s\"\n",
		(knob & PF_AUTOBOOT) ? "autoboot" : "autosearch",
		(flags & knob) ? "On" : "Off");
	
	वापस count;

parse_error:
	prपूर्णांकk(KERN_WARNING "%s: Parse error: expect \"n\" (n == 0 or 1)\n", __func__);
	वापस -EINVAL;
पूर्ण

/**
 * pdcs_स्वतःboot_ग_लिखो - This function handles स्वतःboot flag modअगरying.
 * @buf: The input buffer to पढ़ो from.
 * @count: The number of bytes to be पढ़ो.
 *
 * We will call this function to change the current boot flags.
 * We expect a precise syntax:
 *	\"n\" (n == 0 or 1) to toggle AutoSearch Off or On
 */
अटल sमाप_प्रकार pdcs_स्वतःboot_ग_लिखो(काष्ठा kobject *kobj,
				   काष्ठा kobj_attribute *attr,
				   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	वापस pdcs_स्वतः_ग_लिखो(kobj, attr, buf, count, PF_AUTOBOOT);
पूर्ण

/**
 * pdcs_स्वतःsearch_ग_लिखो - This function handles स्वतःsearch flag modअगरying.
 * @buf: The input buffer to पढ़ो from.
 * @count: The number of bytes to be पढ़ो.
 *
 * We will call this function to change the current boot flags.
 * We expect a precise syntax:
 *	\"n\" (n == 0 or 1) to toggle AutoSearch Off or On
 */
अटल sमाप_प्रकार pdcs_स्वतःsearch_ग_लिखो(काष्ठा kobject *kobj,
				     काष्ठा kobj_attribute *attr,
				     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	वापस pdcs_स्वतः_ग_लिखो(kobj, attr, buf, count, PF_AUTOSEARCH);
पूर्ण

/**
 * pdcs_osdep1_ग_लिखो - Stable Storage OS-Dependent data area 1 input.
 * @buf: The input buffer to पढ़ो from.
 * @count: The number of bytes to be पढ़ो.
 *
 * This can store 16 bytes of OS-Dependent data. We use a byte-by-byte
 * ग_लिखो approach. It's up to userspace to deal with it when स्थिरructing
 * its input buffer.
 */
अटल sमाप_प्रकार pdcs_osdep1_ग_लिखो(काष्ठा kobject *kobj,
				 काष्ठा kobj_attribute *attr,
				 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	u8 in[16];

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EACCES;

	अगर (!buf || !count)
		वापस -EINVAL;

	अगर (unlikely(pdcs_osid != OS_ID_LINUX))
		वापस -EPERM;

	अगर (count > 16)
		वापस -EMSGSIZE;

	/* We'll use a local copy of buf */
	स_रखो(in, 0, 16);
	स_नकल(in, buf, count);

	अगर (pdc_stable_ग_लिखो(PDCS_ADDR_OSD1, &in, माप(in)) != PDC_OK)
		वापस -EIO;

	वापस count;
पूर्ण

/**
 * pdcs_osdep2_ग_लिखो - Stable Storage OS-Dependent data area 2 input.
 * @buf: The input buffer to पढ़ो from.
 * @count: The number of bytes to be पढ़ो.
 *
 * This can store pdcs_size - 224 bytes of OS-Dependent data. We use a
 * byte-by-byte ग_लिखो approach. It's up to userspace to deal with it when
 * स्थिरructing its input buffer.
 */
अटल sमाप_प्रकार pdcs_osdep2_ग_लिखो(काष्ठा kobject *kobj,
				 काष्ठा kobj_attribute *attr,
				 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित दीर्घ size;
	अचिन्हित लघु i;
	u8 in[4];

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EACCES;

	अगर (!buf || !count)
		वापस -EINVAL;

	अगर (unlikely(pdcs_size <= 224))
		वापस -ENOSYS;

	अगर (unlikely(pdcs_osid != OS_ID_LINUX))
		वापस -EPERM;

	size = pdcs_size - 224;

	अगर (count > size)
		वापस -EMSGSIZE;

	/* We'll use a local copy of buf */

	क्रम (i=0; i<count; i+=4) अणु
		स_रखो(in, 0, 4);
		स_नकल(in, buf+i, (count-i < 4) ? count-i : 4);
		अगर (unlikely(pdc_stable_ग_लिखो(PDCS_ADDR_OSD2 + i, &in,
					माप(in)) != PDC_OK))
			वापस -EIO;
	पूर्ण

	वापस count;
पूर्ण

/* The reमुख्यing attributes. */
अटल PDCS_ATTR(size, 0444, pdcs_size_पढ़ो, शून्य);
अटल PDCS_ATTR(स्वतःboot, 0644, pdcs_स्वतःboot_पढ़ो, pdcs_स्वतःboot_ग_लिखो);
अटल PDCS_ATTR(स्वतःsearch, 0644, pdcs_स्वतःsearch_पढ़ो, pdcs_स्वतःsearch_ग_लिखो);
अटल PDCS_ATTR(समयr, 0444, pdcs_समयr_पढ़ो, शून्य);
अटल PDCS_ATTR(osid, 0444, pdcs_osid_पढ़ो, शून्य);
अटल PDCS_ATTR(osdep1, 0600, pdcs_osdep1_पढ़ो, pdcs_osdep1_ग_लिखो);
अटल PDCS_ATTR(diagnostic, 0400, pdcs_diagnostic_पढ़ो, शून्य);
अटल PDCS_ATTR(fastsize, 0400, pdcs_fastsize_पढ़ो, शून्य);
अटल PDCS_ATTR(osdep2, 0600, pdcs_osdep2_पढ़ो, pdcs_osdep2_ग_लिखो);

अटल काष्ठा attribute *pdcs_subsys_attrs[] = अणु
	&pdcs_attr_size.attr,
	&pdcs_attr_स्वतःboot.attr,
	&pdcs_attr_स्वतःsearch.attr,
	&pdcs_attr_समयr.attr,
	&pdcs_attr_osid.attr,
	&pdcs_attr_osdep1.attr,
	&pdcs_attr_diagnostic.attr,
	&pdcs_attr_fastsize.attr,
	&pdcs_attr_osdep2.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group pdcs_attr_group = अणु
	.attrs = pdcs_subsys_attrs,
पूर्ण;

अटल काष्ठा kobject *stable_kobj;
अटल काष्ठा kset *paths_kset;

/**
 * pdcs_रेजिस्टर_pathentries - Prepares path entries kobjects क्रम sysfs usage.
 * 
 * It creates kobjects corresponding to each path entry with nice sysfs
 * links to the real device. This is where the magic takes place: when
 * रेजिस्टरing the subप्रणाली attributes during module init, each kobject hereby
 * created will show in the sysfs tree as a folder containing files as defined
 * by path_subsys_attr[].
 */
अटल अंतरभूत पूर्णांक __init
pdcs_रेजिस्टर_pathentries(व्योम)
अणु
	अचिन्हित लघु i;
	काष्ठा pdcspath_entry *entry;
	पूर्णांक err;
	
	/* Initialize the entries rw_lock beक्रमe anything अन्यथा */
	क्रम (i = 0; (entry = pdcspath_entries[i]); i++)
		rwlock_init(&entry->rw_lock);

	क्रम (i = 0; (entry = pdcspath_entries[i]); i++) अणु
		ग_लिखो_lock(&entry->rw_lock);
		err = pdcspath_fetch(entry);
		ग_लिखो_unlock(&entry->rw_lock);

		अगर (err < 0)
			जारी;

		entry->kobj.kset = paths_kset;
		err = kobject_init_and_add(&entry->kobj, &ktype_pdcspath, शून्य,
					   "%s", entry->name);
		अगर (err)
			वापस err;

		/* kobject is now रेजिस्टरed */
		ग_लिखो_lock(&entry->rw_lock);
		entry->पढ़ोy = 2;
		ग_लिखो_unlock(&entry->rw_lock);
		
		/* Add a nice symlink to the real device */
		अगर (entry->dev) अणु
			err = sysfs_create_link(&entry->kobj, &entry->dev->kobj, "device");
			WARN_ON(err);
		पूर्ण

		kobject_uevent(&entry->kobj, KOBJ_ADD);
	पूर्ण
	
	वापस 0;
पूर्ण

/**
 * pdcs_unरेजिस्टर_pathentries - Routine called when unरेजिस्टरing the module.
 */
अटल अंतरभूत व्योम
pdcs_unरेजिस्टर_pathentries(व्योम)
अणु
	अचिन्हित लघु i;
	काष्ठा pdcspath_entry *entry;
	
	क्रम (i = 0; (entry = pdcspath_entries[i]); i++) अणु
		पढ़ो_lock(&entry->rw_lock);
		अगर (entry->पढ़ोy >= 2)
			kobject_put(&entry->kobj);
		पढ़ो_unlock(&entry->rw_lock);
	पूर्ण
पूर्ण

/*
 * For now we रेजिस्टर the stable subप्रणाली with the firmware subप्रणाली
 * and the paths subप्रणाली with the stable subप्रणाली
 */
अटल पूर्णांक __init
pdc_stable_init(व्योम)
अणु
	पूर्णांक rc = 0, error = 0;
	u32 result;

	/* find the size of the stable storage */
	अगर (pdc_stable_get_size(&pdcs_size) != PDC_OK) 
		वापस -ENODEV;

	/* make sure we have enough data */
	अगर (pdcs_size < 96)
		वापस -ENODATA;

	prपूर्णांकk(KERN_INFO PDCS_PREFIX " facility v%s\n", PDCS_VERSION);

	/* get OSID */
	अगर (pdc_stable_पढ़ो(PDCS_ADDR_OSID, &result, माप(result)) != PDC_OK)
		वापस -EIO;

	/* the actual result is 16 bits away */
	pdcs_osid = (u16)(result >> 16);

	/* For now we'll रेजिस्टर the directory at /sys/firmware/stable */
	stable_kobj = kobject_create_and_add("stable", firmware_kobj);
	अगर (!stable_kobj) अणु
		rc = -ENOMEM;
		जाओ fail_firmreg;
	पूर्ण

	/* Don't क्रमget the root entries */
	error = sysfs_create_group(stable_kobj, &pdcs_attr_group);

	/* रेजिस्टर the paths kset as a child of the stable kset */
	paths_kset = kset_create_and_add("paths", शून्य, stable_kobj);
	अगर (!paths_kset) अणु
		rc = -ENOMEM;
		जाओ fail_ksetreg;
	पूर्ण

	/* now we create all "files" क्रम the paths kset */
	अगर ((rc = pdcs_रेजिस्टर_pathentries()))
		जाओ fail_pdcsreg;

	वापस rc;
	
fail_pdcsreg:
	pdcs_unरेजिस्टर_pathentries();
	kset_unरेजिस्टर(paths_kset);
	
fail_ksetreg:
	kobject_put(stable_kobj);
	
fail_firmreg:
	prपूर्णांकk(KERN_INFO PDCS_PREFIX " bailing out\n");
	वापस rc;
पूर्ण

अटल व्योम __निकास
pdc_stable_निकास(व्योम)
अणु
	pdcs_unरेजिस्टर_pathentries();
	kset_unरेजिस्टर(paths_kset);
	kobject_put(stable_kobj);
पूर्ण


module_init(pdc_stable_init);
module_निकास(pdc_stable_निकास);
