<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Author(s)......: Holger Smolinski <Holger.Smolinski@de.ibm.com>
 *		    Horst Hummel <Horst.Hummel@de.ibm.com>
 *		    Carsten Otte <Cotte@de.ibm.com>
 *		    Martin Schwidefsky <schwidefsky@de.ibm.com>
 * Bugreports.to..: <Linux390@de.ibm.com>
 * Copyright IBM Corp. 1999,2001
 *
 * Device mapping and dasd= parameter parsing functions. All devmap
 * functions may not be called from पूर्णांकerrupt context. In particular
 * dasd_get_device is a no-no from पूर्णांकerrupt context.
 *
 */

#घोषणा KMSG_COMPONENT "dasd"

#समावेश <linux/प्रकार.स>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/debug.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/ipl.h>

/* This is ugly... */
#घोषणा PRINTK_HEADER "dasd_devmap:"
#घोषणा DASD_BUS_ID_SIZE 20
#घोषणा DASD_MAX_PARAMS 256

#समावेश "dasd_int.h"

काष्ठा kmem_cache *dasd_page_cache;
EXPORT_SYMBOL_GPL(dasd_page_cache);

/*
 * dasd_devmap_t is used to store the features and the relation
 * between device number and device index. To find a dasd_devmap_t
 * that corresponds to a device number of a device index each
 * dasd_devmap_t is added to two linked lists, one to search by
 * the device number and one to search by the device index. As
 * soon as big minor numbers are available the device index list
 * can be हटाओd since the device number will then be identical
 * to the device index.
 */
काष्ठा dasd_devmap अणु
	काष्ठा list_head list;
	अक्षर bus_id[DASD_BUS_ID_SIZE];
        अचिन्हित पूर्णांक devindex;
        अचिन्हित लघु features;
	काष्ठा dasd_device *device;
पूर्ण;

/*
 * Parameter parsing functions क्रम dasd= parameter. The syntax is:
 *   <devno>		: (0x)?[0-9a-fA-F]+
 *   <busid>		: [0-0a-f]\.[0-9a-f]\.(0x)?[0-9a-fA-F]+
 *   <feature>		: ro
 *   <feature_list>	: \(<feature>(:<feature>)*\)
 *   <devno-range>	: <devno>(-<devno>)?<feature_list>?
 *   <busid-range>	: <busid>(-<busid>)?<feature_list>?
 *   <devices>		: <devno-range>|<busid-range>
 *   <dasd_module>	: dasd_diag_mod|dasd_eckd_mod|dasd_fba_mod
 *
 *   <dasd>		: स्वतःdetect|probeonly|<devices>(,<devices>)*
 */

पूर्णांक dasd_probeonly =  0;	/* is true, when probeonly mode is active */
पूर्णांक dasd_स्वतःdetect = 0;	/* is true, when स्वतःdetection is active */
पूर्णांक dasd_nopav = 0;		/* is true, when PAV is disabled */
EXPORT_SYMBOL_GPL(dasd_nopav);
पूर्णांक dasd_nofcx;			/* disable High Perक्रमmance Ficon */
EXPORT_SYMBOL_GPL(dasd_nofcx);

/*
 * अक्षर *dasd[] is पूर्णांकended to hold the ranges supplied by the dasd= statement
 * it is named 'dasd' to directly be filled by insmod with the comma separated
 * strings when running as a module.
 */
अटल अक्षर *dasd[DASD_MAX_PARAMS];
module_param_array(dasd, अक्षरp, शून्य, S_IRUGO);

/*
 * Single spinlock to protect devmap and servermap काष्ठाures and lists.
 */
अटल DEFINE_SPINLOCK(dasd_devmap_lock);

/*
 * Hash lists क्रम devmap काष्ठाures.
 */
अटल काष्ठा list_head dasd_hashlists[256];
पूर्णांक dasd_max_devindex;

अटल काष्ठा dasd_devmap *dasd_add_busid(स्थिर अक्षर *, पूर्णांक);

अटल अंतरभूत पूर्णांक
dasd_hash_busid(स्थिर अक्षर *bus_id)
अणु
	पूर्णांक hash, i;

	hash = 0;
	क्रम (i = 0; (i < DASD_BUS_ID_SIZE) && *bus_id; i++, bus_id++)
		hash += *bus_id;
	वापस hash & 0xff;
पूर्ण

#अगर_अघोषित MODULE
अटल पूर्णांक __init dasd_call_setup(अक्षर *opt)
अणु
	अटल पूर्णांक i __initdata;
	अक्षर *पंचांगp;

	जबतक (i < DASD_MAX_PARAMS) अणु
		पंचांगp = strsep(&opt, ",");
		अगर (!पंचांगp)
			अवरोध;

		dasd[i++] = पंचांगp;
	पूर्ण

	वापस 1;
पूर्ण

__setup ("dasd=", dasd_call_setup);
#पूर्ण_अगर	/* #अगर_अघोषित MODULE */

#घोषणा	DASD_IPLDEV	"ipldev"

/*
 * Read a device busid/devno from a string.
 */
अटल पूर्णांक __init dasd_busid(अक्षर *str, पूर्णांक *id0, पूर्णांक *id1, पूर्णांक *devno)
अणु
	अचिन्हित पूर्णांक val;
	अक्षर *tok;

	/* Interpret ipldev busid */
	अगर (म_भेदन(DASD_IPLDEV, str, म_माप(DASD_IPLDEV)) == 0) अणु
		अगर (ipl_info.type != IPL_TYPE_CCW) अणु
			pr_err("The IPL device is not a CCW device\n");
			वापस -EINVAL;
		पूर्ण
		*id0 = 0;
		*id1 = ipl_info.data.ccw.dev_id.ssid;
		*devno = ipl_info.data.ccw.dev_id.devno;

		वापस 0;
	पूर्ण

	/* Old style 0xXXXX or XXXX */
	अगर (!kstrtouपूर्णांक(str, 16, &val)) अणु
		*id0 = *id1 = 0;
		अगर (val > 0xffff)
			वापस -EINVAL;
		*devno = val;
		वापस 0;
	पूर्ण

	/* New style x.y.z busid */
	tok = strsep(&str, ".");
	अगर (kstrtouपूर्णांक(tok, 16, &val) || val > 0xff)
		वापस -EINVAL;
	*id0 = val;

	tok = strsep(&str, ".");
	अगर (kstrtouपूर्णांक(tok, 16, &val) || val > 0xff)
		वापस -EINVAL;
	*id1 = val;

	tok = strsep(&str, ".");
	अगर (kstrtouपूर्णांक(tok, 16, &val) || val > 0xffff)
		वापस -EINVAL;
	*devno = val;

	वापस 0;
पूर्ण

/*
 * Read colon separated list of dasd features.
 */
अटल पूर्णांक __init dasd_feature_list(अक्षर *str)
अणु
	पूर्णांक features, len, rc;

	features = 0;
	rc = 0;

	अगर (!str)
		वापस DASD_FEATURE_DEFAULT;

	जबतक (1) अणु
		क्रम (len = 0;
		     str[len] && str[len] != ':' && str[len] != ')'; len++);
		अगर (len == 2 && !म_भेदन(str, "ro", 2))
			features |= DASD_FEATURE_READONLY;
		अन्यथा अगर (len == 4 && !म_भेदन(str, "diag", 4))
			features |= DASD_FEATURE_USEDIAG;
		अन्यथा अगर (len == 3 && !म_भेदन(str, "raw", 3))
			features |= DASD_FEATURE_USERAW;
		अन्यथा अगर (len == 6 && !म_भेदन(str, "erplog", 6))
			features |= DASD_FEATURE_ERPLOG;
		अन्यथा अगर (len == 8 && !म_भेदन(str, "failfast", 8))
			features |= DASD_FEATURE_FAILFAST;
		अन्यथा अणु
			pr_warn("%.*s is not a supported device option\n",
				len, str);
			rc = -EINVAL;
		पूर्ण
		str += len;
		अगर (*str != ':')
			अवरोध;
		str++;
	पूर्ण

	वापस rc ? : features;
पूर्ण

/*
 * Try to match the first element on the comma separated parse string
 * with one of the known keywords. If a keyword is found, take the approprate
 * action and वापस a poपूर्णांकer to the residual string. If the first element
 * could not be matched to any keyword then वापस an error code.
 */
अटल पूर्णांक __init dasd_parse_keyword(अक्षर *keyword)
अणु
	पूर्णांक length = म_माप(keyword);

	अगर (म_भेदन("autodetect", keyword, length) == 0) अणु
		dasd_स्वतःdetect = 1;
		pr_info("The autodetection mode has been activated\n");
		वापस 0;
        पूर्ण
	अगर (म_भेदन("probeonly", keyword, length) == 0) अणु
		dasd_probeonly = 1;
		pr_info("The probeonly mode has been activated\n");
		वापस 0;
        पूर्ण
	अगर (म_भेदन("nopav", keyword, length) == 0) अणु
		अगर (MACHINE_IS_VM)
			pr_info("'nopav' is not supported on z/VM\n");
		अन्यथा अणु
			dasd_nopav = 1;
			pr_info("PAV support has be deactivated\n");
		पूर्ण
		वापस 0;
	पूर्ण
	अगर (म_भेदन("nofcx", keyword, length) == 0) अणु
		dasd_nofcx = 1;
		pr_info("High Performance FICON support has been "
			"deactivated\n");
		वापस 0;
	पूर्ण
	अगर (म_भेदन("fixedbuffers", keyword, length) == 0) अणु
		अगर (dasd_page_cache)
			वापस 0;
		dasd_page_cache =
			kmem_cache_create("dasd_page_cache", PAGE_SIZE,
					  PAGE_SIZE, SLAB_CACHE_DMA,
					  शून्य);
		अगर (!dasd_page_cache)
			DBF_EVENT(DBF_WARNING, "%s", "Failed to create slab, "
				"fixed buffer mode disabled.");
		अन्यथा
			DBF_EVENT(DBF_INFO, "%s",
				 "turning on fixed buffer mode");
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

/*
 * Split a string of a device range पूर्णांकo its pieces and वापस the from, to, and
 * feature parts separately.
 * e.g.:
 * 0.0.1234-0.0.5678(ro:erplog) -> from: 0.0.1234 to: 0.0.5678 features: ro:erplog
 * 0.0.8765(raw) -> from: 0.0.8765 to: null features: raw
 * 0x4321 -> from: 0x4321 to: null features: null
 */
अटल पूर्णांक __init dasd_evaluate_range_param(अक्षर *range, अक्षर **from_str,
					    अक्षर **to_str, अक्षर **features_str)
अणु
	पूर्णांक rc = 0;

	/* Do we have a range or a single device? */
	अगर (म_अक्षर(range, '-')) अणु
		*from_str = strsep(&range, "-");
		*to_str = strsep(&range, "(");
		*features_str = strsep(&range, ")");
	पूर्ण अन्यथा अणु
		*from_str = strsep(&range, "(");
		*features_str = strsep(&range, ")");
	पूर्ण

	अगर (*features_str && !range) अणु
		pr_warn("A closing parenthesis ')' is missing in the dasd= parameter\n");
		rc = -EINVAL;
	पूर्ण

	वापस rc;
पूर्ण

/*
 * Try to पूर्णांकerprete the range string as a device number or a range of devices.
 * If the पूर्णांकerpretation is successful, create the matching dasd_devmap entries.
 * If पूर्णांकerpretation fails or in हाल of an error, वापस an error code.
 */
अटल पूर्णांक __init dasd_parse_range(स्थिर अक्षर *range)
अणु
	काष्ठा dasd_devmap *devmap;
	पूर्णांक from, from_id0, from_id1;
	पूर्णांक to, to_id0, to_id1;
	पूर्णांक features;
	अक्षर bus_id[DASD_BUS_ID_SIZE + 1];
	अक्षर *features_str = शून्य;
	अक्षर *from_str = शून्य;
	अक्षर *to_str = शून्य;
	पूर्णांक rc = 0;
	अक्षर *पंचांगp;

	पंचांगp = kstrdup(range, GFP_KERNEL);
	अगर (!पंचांगp)
		वापस -ENOMEM;

	अगर (dasd_evaluate_range_param(पंचांगp, &from_str, &to_str, &features_str)) अणु
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (dasd_busid(from_str, &from_id0, &from_id1, &from)) अणु
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	to = from;
	to_id0 = from_id0;
	to_id1 = from_id1;
	अगर (to_str) अणु
		अगर (dasd_busid(to_str, &to_id0, &to_id1, &to)) अणु
			rc = -EINVAL;
			जाओ out;
		पूर्ण
		अगर (from_id0 != to_id0 || from_id1 != to_id1 || from > to) अणु
			pr_err("%s is not a valid device range\n", range);
			rc = -EINVAL;
			जाओ out;
		पूर्ण
	पूर्ण

	features = dasd_feature_list(features_str);
	अगर (features < 0) अणु
		rc = -EINVAL;
		जाओ out;
	पूर्ण
	/* each device in dasd= parameter should be set initially online */
	features |= DASD_FEATURE_INITIAL_ONLINE;
	जबतक (from <= to) अणु
		प्र_लिखो(bus_id, "%01x.%01x.%04x", from_id0, from_id1, from++);
		devmap = dasd_add_busid(bus_id, features);
		अगर (IS_ERR(devmap)) अणु
			rc = PTR_ERR(devmap);
			जाओ out;
		पूर्ण
	पूर्ण

out:
	kमुक्त(पंचांगp);

	वापस rc;
पूर्ण

/*
 * Parse parameters stored in dasd[]
 * The 'dasd=...' parameter allows to specअगरy a comma separated list of
 * keywords and device ranges. The parameters in that list will be stored as
 * separate elementes in dasd[].
 */
पूर्णांक __init dasd_parse(व्योम)
अणु
	पूर्णांक rc, i;
	अक्षर *cur;

	rc = 0;
	क्रम (i = 0; i < DASD_MAX_PARAMS; i++) अणु
		cur = dasd[i];
		अगर (!cur)
			अवरोध;
		अगर (*cur == '\0')
			जारी;

		rc = dasd_parse_keyword(cur);
		अगर (rc)
			rc = dasd_parse_range(cur);

		अगर (rc)
			अवरोध;
	पूर्ण

	वापस rc;
पूर्ण

/*
 * Add a devmap क्रम the device specअगरied by busid. It is possible that
 * the devmap alपढ़ोy exists (dasd= parameter). The order of the devices
 * added through this function will define the kdevs क्रम the inभागidual
 * devices.
 */
अटल काष्ठा dasd_devmap *
dasd_add_busid(स्थिर अक्षर *bus_id, पूर्णांक features)
अणु
	काष्ठा dasd_devmap *devmap, *new, *पंचांगp;
	पूर्णांक hash;

	new = kzalloc(माप(काष्ठा dasd_devmap), GFP_KERNEL);
	अगर (!new)
		वापस ERR_PTR(-ENOMEM);
	spin_lock(&dasd_devmap_lock);
	devmap = शून्य;
	hash = dasd_hash_busid(bus_id);
	list_क्रम_each_entry(पंचांगp, &dasd_hashlists[hash], list)
		अगर (म_भेदन(पंचांगp->bus_id, bus_id, DASD_BUS_ID_SIZE) == 0) अणु
			devmap = पंचांगp;
			अवरोध;
		पूर्ण
	अगर (!devmap) अणु
		/* This bus_id is new. */
		new->devindex = dasd_max_devindex++;
		strlcpy(new->bus_id, bus_id, DASD_BUS_ID_SIZE);
		new->features = features;
		new->device = शून्य;
		list_add(&new->list, &dasd_hashlists[hash]);
		devmap = new;
		new = शून्य;
	पूर्ण
	spin_unlock(&dasd_devmap_lock);
	kमुक्त(new);
	वापस devmap;
पूर्ण

/*
 * Find devmap क्रम device with given bus_id.
 */
अटल काष्ठा dasd_devmap *
dasd_find_busid(स्थिर अक्षर *bus_id)
अणु
	काष्ठा dasd_devmap *devmap, *पंचांगp;
	पूर्णांक hash;

	spin_lock(&dasd_devmap_lock);
	devmap = ERR_PTR(-ENODEV);
	hash = dasd_hash_busid(bus_id);
	list_क्रम_each_entry(पंचांगp, &dasd_hashlists[hash], list) अणु
		अगर (म_भेदन(पंचांगp->bus_id, bus_id, DASD_BUS_ID_SIZE) == 0) अणु
			devmap = पंचांगp;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock(&dasd_devmap_lock);
	वापस devmap;
पूर्ण

/*
 * Check अगर busid has been added to the list of dasd ranges.
 */
पूर्णांक
dasd_busid_known(स्थिर अक्षर *bus_id)
अणु
	वापस IS_ERR(dasd_find_busid(bus_id)) ? -ENOENT : 0;
पूर्ण

/*
 * Forget all about the device numbers added so far.
 * This may only be called at module unload or प्रणाली shutकरोwn.
 */
अटल व्योम
dasd_क्रमget_ranges(व्योम)
अणु
	काष्ठा dasd_devmap *devmap, *n;
	पूर्णांक i;

	spin_lock(&dasd_devmap_lock);
	क्रम (i = 0; i < 256; i++) अणु
		list_क्रम_each_entry_safe(devmap, n, &dasd_hashlists[i], list) अणु
			BUG_ON(devmap->device != शून्य);
			list_del(&devmap->list);
			kमुक्त(devmap);
		पूर्ण
	पूर्ण
	spin_unlock(&dasd_devmap_lock);
पूर्ण

/*
 * Find the device काष्ठा by its device index.
 */
काष्ठा dasd_device *
dasd_device_from_devindex(पूर्णांक devindex)
अणु
	काष्ठा dasd_devmap *devmap, *पंचांगp;
	काष्ठा dasd_device *device;
	पूर्णांक i;

	spin_lock(&dasd_devmap_lock);
	devmap = शून्य;
	क्रम (i = 0; (i < 256) && !devmap; i++)
		list_क्रम_each_entry(पंचांगp, &dasd_hashlists[i], list)
			अगर (पंचांगp->devindex == devindex) अणु
				/* Found the devmap क्रम the device. */
				devmap = पंचांगp;
				अवरोध;
			पूर्ण
	अगर (devmap && devmap->device) अणु
		device = devmap->device;
		dasd_get_device(device);
	पूर्ण अन्यथा
		device = ERR_PTR(-ENODEV);
	spin_unlock(&dasd_devmap_lock);
	वापस device;
पूर्ण

/*
 * Return devmap क्रम cdev. If no devmap exists yet, create one and
 * connect it to the cdev.
 */
अटल काष्ठा dasd_devmap *
dasd_devmap_from_cdev(काष्ठा ccw_device *cdev)
अणु
	काष्ठा dasd_devmap *devmap;

	devmap = dasd_find_busid(dev_name(&cdev->dev));
	अगर (IS_ERR(devmap))
		devmap = dasd_add_busid(dev_name(&cdev->dev),
					DASD_FEATURE_DEFAULT);
	वापस devmap;
पूर्ण

/*
 * Create a dasd device काष्ठाure क्रम cdev.
 */
काष्ठा dasd_device *
dasd_create_device(काष्ठा ccw_device *cdev)
अणु
	काष्ठा dasd_devmap *devmap;
	काष्ठा dasd_device *device;
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;

	devmap = dasd_devmap_from_cdev(cdev);
	अगर (IS_ERR(devmap))
		वापस (व्योम *) devmap;

	device = dasd_alloc_device();
	अगर (IS_ERR(device))
		वापस device;
	atomic_set(&device->ref_count, 3);

	spin_lock(&dasd_devmap_lock);
	अगर (!devmap->device) अणु
		devmap->device = device;
		device->devindex = devmap->devindex;
		device->features = devmap->features;
		get_device(&cdev->dev);
		device->cdev = cdev;
		rc = 0;
	पूर्ण अन्यथा
		/* Someone अन्यथा was faster. */
		rc = -EBUSY;
	spin_unlock(&dasd_devmap_lock);

	अगर (rc) अणु
		dasd_मुक्त_device(device);
		वापस ERR_PTR(rc);
	पूर्ण

	spin_lock_irqsave(get_ccwdev_lock(cdev), flags);
	dev_set_drvdata(&cdev->dev, device);
	spin_unlock_irqrestore(get_ccwdev_lock(cdev), flags);

	device->paths_info = kset_create_and_add("paths_info", शून्य,
						 &device->cdev->dev.kobj);
	अगर (!device->paths_info)
		dev_warn(&cdev->dev, "Could not create paths_info kset\n");

	वापस device;
पूर्ण

/*
 * Wait queue क्रम dasd_delete_device रुकोs.
 */
अटल DECLARE_WAIT_QUEUE_HEAD(dasd_delete_wq);

/*
 * Remove a dasd device काष्ठाure. The passed referenced
 * is destroyed.
 */
व्योम
dasd_delete_device(काष्ठा dasd_device *device)
अणु
	काष्ठा ccw_device *cdev;
	काष्ठा dasd_devmap *devmap;
	अचिन्हित दीर्घ flags;

	/* First हटाओ device poपूर्णांकer from devmap. */
	devmap = dasd_find_busid(dev_name(&device->cdev->dev));
	BUG_ON(IS_ERR(devmap));
	spin_lock(&dasd_devmap_lock);
	अगर (devmap->device != device) अणु
		spin_unlock(&dasd_devmap_lock);
		dasd_put_device(device);
		वापस;
	पूर्ण
	devmap->device = शून्य;
	spin_unlock(&dasd_devmap_lock);

	/* Disconnect dasd_device काष्ठाure from ccw_device काष्ठाure. */
	spin_lock_irqsave(get_ccwdev_lock(device->cdev), flags);
	dev_set_drvdata(&device->cdev->dev, शून्य);
	spin_unlock_irqrestore(get_ccwdev_lock(device->cdev), flags);

	/*
	 * Drop ref_count by 3, one क्रम the devmap reference, one क्रम
	 * the cdev reference and one क्रम the passed reference.
	 */
	atomic_sub(3, &device->ref_count);

	/* Wait क्रम reference counter to drop to zero. */
	रुको_event(dasd_delete_wq, atomic_पढ़ो(&device->ref_count) == 0);

	dasd_generic_मुक्त_discipline(device);

	kset_unरेजिस्टर(device->paths_info);

	/* Disconnect dasd_device काष्ठाure from ccw_device काष्ठाure. */
	cdev = device->cdev;
	device->cdev = शून्य;

	/* Put ccw_device काष्ठाure. */
	put_device(&cdev->dev);

	/* Now the device काष्ठाure can be मुक्तd. */
	dasd_मुक्त_device(device);
पूर्ण

/*
 * Reference counter dropped to zero. Wake up रुकोer
 * in dasd_delete_device.
 */
व्योम
dasd_put_device_wake(काष्ठा dasd_device *device)
अणु
	wake_up(&dasd_delete_wq);
पूर्ण
EXPORT_SYMBOL_GPL(dasd_put_device_wake);

/*
 * Return dasd_device काष्ठाure associated with cdev.
 * This function needs to be called with the ccw device
 * lock held. It can be used from पूर्णांकerrupt context.
 */
काष्ठा dasd_device *
dasd_device_from_cdev_locked(काष्ठा ccw_device *cdev)
अणु
	काष्ठा dasd_device *device = dev_get_drvdata(&cdev->dev);

	अगर (!device)
		वापस ERR_PTR(-ENODEV);
	dasd_get_device(device);
	वापस device;
पूर्ण

/*
 * Return dasd_device काष्ठाure associated with cdev.
 */
काष्ठा dasd_device *
dasd_device_from_cdev(काष्ठा ccw_device *cdev)
अणु
	काष्ठा dasd_device *device;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(get_ccwdev_lock(cdev), flags);
	device = dasd_device_from_cdev_locked(cdev);
	spin_unlock_irqrestore(get_ccwdev_lock(cdev), flags);
	वापस device;
पूर्ण

व्योम dasd_add_link_to_gendisk(काष्ठा gendisk *gdp, काष्ठा dasd_device *device)
अणु
	काष्ठा dasd_devmap *devmap;

	devmap = dasd_find_busid(dev_name(&device->cdev->dev));
	अगर (IS_ERR(devmap))
		वापस;
	spin_lock(&dasd_devmap_lock);
	gdp->निजी_data = devmap;
	spin_unlock(&dasd_devmap_lock);
पूर्ण

काष्ठा dasd_device *dasd_device_from_gendisk(काष्ठा gendisk *gdp)
अणु
	काष्ठा dasd_device *device;
	काष्ठा dasd_devmap *devmap;

	अगर (!gdp->निजी_data)
		वापस शून्य;
	device = शून्य;
	spin_lock(&dasd_devmap_lock);
	devmap = gdp->निजी_data;
	अगर (devmap && devmap->device) अणु
		device = devmap->device;
		dasd_get_device(device);
	पूर्ण
	spin_unlock(&dasd_devmap_lock);
	वापस device;
पूर्ण

/*
 * SECTION: files in sysfs
 */

/*
 * failfast controls the behaviour, अगर no path is available
 */
अटल sमाप_प्रकार dasd_ff_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	काष्ठा dasd_devmap *devmap;
	पूर्णांक ff_flag;

	devmap = dasd_find_busid(dev_name(dev));
	अगर (!IS_ERR(devmap))
		ff_flag = (devmap->features & DASD_FEATURE_FAILFAST) != 0;
	अन्यथा
		ff_flag = (DASD_FEATURE_DEFAULT & DASD_FEATURE_FAILFAST) != 0;
	वापस snम_लिखो(buf, PAGE_SIZE, ff_flag ? "1\n" : "0\n");
पूर्ण

अटल sमाप_प्रकार dasd_ff_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
	      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक rc;

	अगर (kstrtouपूर्णांक(buf, 0, &val) || val > 1)
		वापस -EINVAL;

	rc = dasd_set_feature(to_ccwdev(dev), DASD_FEATURE_FAILFAST, val);

	वापस rc ? : count;
पूर्ण

अटल DEVICE_ATTR(failfast, 0644, dasd_ff_show, dasd_ff_store);

/*
 * पढ़ोonly controls the पढ़ोonly status of a dasd
 */
अटल sमाप_प्रकार
dasd_ro_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा dasd_devmap *devmap;
	काष्ठा dasd_device *device;
	पूर्णांक ro_flag = 0;

	devmap = dasd_find_busid(dev_name(dev));
	अगर (IS_ERR(devmap))
		जाओ out;

	ro_flag = !!(devmap->features & DASD_FEATURE_READONLY);

	spin_lock(&dasd_devmap_lock);
	device = devmap->device;
	अगर (device)
		ro_flag |= test_bit(DASD_FLAG_DEVICE_RO, &device->flags);
	spin_unlock(&dasd_devmap_lock);

out:
	वापस snम_लिखो(buf, PAGE_SIZE, ro_flag ? "1\n" : "0\n");
पूर्ण

अटल sमाप_प्रकार
dasd_ro_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
	      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा ccw_device *cdev = to_ccwdev(dev);
	काष्ठा dasd_device *device;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक val;
	पूर्णांक rc;

	अगर (kstrtouपूर्णांक(buf, 0, &val) || val > 1)
		वापस -EINVAL;

	rc = dasd_set_feature(cdev, DASD_FEATURE_READONLY, val);
	अगर (rc)
		वापस rc;

	device = dasd_device_from_cdev(cdev);
	अगर (IS_ERR(device))
		वापस count;

	spin_lock_irqsave(get_ccwdev_lock(cdev), flags);
	val = val || test_bit(DASD_FLAG_DEVICE_RO, &device->flags);

	अगर (!device->block || !device->block->gdp ||
	    test_bit(DASD_FLAG_OFFLINE, &device->flags)) अणु
		spin_unlock_irqrestore(get_ccwdev_lock(cdev), flags);
		जाओ out;
	पूर्ण
	/* Increase खोलो_count to aव्योम losing the block device */
	atomic_inc(&device->block->खोलो_count);
	spin_unlock_irqrestore(get_ccwdev_lock(cdev), flags);

	set_disk_ro(device->block->gdp, val);
	atomic_dec(&device->block->खोलो_count);

out:
	dasd_put_device(device);

	वापस count;
पूर्ण

अटल DEVICE_ATTR(पढ़ोonly, 0644, dasd_ro_show, dasd_ro_store);
/*
 * erplog controls the logging of ERP related data
 * (e.g. failing channel programs).
 */
अटल sमाप_प्रकार
dasd_erplog_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा dasd_devmap *devmap;
	पूर्णांक erplog;

	devmap = dasd_find_busid(dev_name(dev));
	अगर (!IS_ERR(devmap))
		erplog = (devmap->features & DASD_FEATURE_ERPLOG) != 0;
	अन्यथा
		erplog = (DASD_FEATURE_DEFAULT & DASD_FEATURE_ERPLOG) != 0;
	वापस snम_लिखो(buf, PAGE_SIZE, erplog ? "1\n" : "0\n");
पूर्ण

अटल sमाप_प्रकार
dasd_erplog_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
	      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक rc;

	अगर (kstrtouपूर्णांक(buf, 0, &val) || val > 1)
		वापस -EINVAL;

	rc = dasd_set_feature(to_ccwdev(dev), DASD_FEATURE_ERPLOG, val);

	वापस rc ? : count;
पूर्ण

अटल DEVICE_ATTR(erplog, 0644, dasd_erplog_show, dasd_erplog_store);

/*
 * use_diag controls whether the driver should use diag rather than ssch
 * to talk to the device
 */
अटल sमाप_प्रकार
dasd_use_diag_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा dasd_devmap *devmap;
	पूर्णांक use_diag;

	devmap = dasd_find_busid(dev_name(dev));
	अगर (!IS_ERR(devmap))
		use_diag = (devmap->features & DASD_FEATURE_USEDIAG) != 0;
	अन्यथा
		use_diag = (DASD_FEATURE_DEFAULT & DASD_FEATURE_USEDIAG) != 0;
	वापस प्र_लिखो(buf, use_diag ? "1\n" : "0\n");
पूर्ण

अटल sमाप_प्रकार
dasd_use_diag_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
		    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा dasd_devmap *devmap;
	अचिन्हित पूर्णांक val;
	sमाप_प्रकार rc;

	devmap = dasd_devmap_from_cdev(to_ccwdev(dev));
	अगर (IS_ERR(devmap))
		वापस PTR_ERR(devmap);

	अगर (kstrtouपूर्णांक(buf, 0, &val) || val > 1)
		वापस -EINVAL;

	spin_lock(&dasd_devmap_lock);
	/* Changing diag discipline flag is only allowed in offline state. */
	rc = count;
	अगर (!devmap->device && !(devmap->features & DASD_FEATURE_USERAW)) अणु
		अगर (val)
			devmap->features |= DASD_FEATURE_USEDIAG;
		अन्यथा
			devmap->features &= ~DASD_FEATURE_USEDIAG;
	पूर्ण अन्यथा
		rc = -EPERM;
	spin_unlock(&dasd_devmap_lock);
	वापस rc;
पूर्ण

अटल DEVICE_ATTR(use_diag, 0644, dasd_use_diag_show, dasd_use_diag_store);

/*
 * use_raw controls whether the driver should give access to raw eckd data or
 * operate in standard mode
 */
अटल sमाप_प्रकार
dasd_use_raw_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा dasd_devmap *devmap;
	पूर्णांक use_raw;

	devmap = dasd_find_busid(dev_name(dev));
	अगर (!IS_ERR(devmap))
		use_raw = (devmap->features & DASD_FEATURE_USERAW) != 0;
	अन्यथा
		use_raw = (DASD_FEATURE_DEFAULT & DASD_FEATURE_USERAW) != 0;
	वापस प्र_लिखो(buf, use_raw ? "1\n" : "0\n");
पूर्ण

अटल sमाप_प्रकार
dasd_use_raw_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
		    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा dasd_devmap *devmap;
	sमाप_प्रकार rc;
	अचिन्हित दीर्घ val;

	devmap = dasd_devmap_from_cdev(to_ccwdev(dev));
	अगर (IS_ERR(devmap))
		वापस PTR_ERR(devmap);

	अगर ((kम_से_अदीर्घ(buf, 10, &val) != 0) || val > 1)
		वापस -EINVAL;

	spin_lock(&dasd_devmap_lock);
	/* Changing diag discipline flag is only allowed in offline state. */
	rc = count;
	अगर (!devmap->device && !(devmap->features & DASD_FEATURE_USEDIAG)) अणु
		अगर (val)
			devmap->features |= DASD_FEATURE_USERAW;
		अन्यथा
			devmap->features &= ~DASD_FEATURE_USERAW;
	पूर्ण अन्यथा
		rc = -EPERM;
	spin_unlock(&dasd_devmap_lock);
	वापस rc;
पूर्ण

अटल DEVICE_ATTR(raw_track_access, 0644, dasd_use_raw_show,
		   dasd_use_raw_store);

अटल sमाप_प्रकार
dasd_safe_offline_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा ccw_device *cdev = to_ccwdev(dev);
	काष्ठा dasd_device *device;
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;

	spin_lock_irqsave(get_ccwdev_lock(cdev), flags);
	device = dasd_device_from_cdev_locked(cdev);
	अगर (IS_ERR(device)) अणु
		rc = PTR_ERR(device);
		spin_unlock_irqrestore(get_ccwdev_lock(cdev), flags);
		जाओ out;
	पूर्ण

	अगर (test_bit(DASD_FLAG_OFFLINE, &device->flags) ||
	    test_bit(DASD_FLAG_SAFE_OFFLINE_RUNNING, &device->flags)) अणु
		/* Alपढ़ोy करोing offline processing */
		dasd_put_device(device);
		spin_unlock_irqrestore(get_ccwdev_lock(cdev), flags);
		rc = -EBUSY;
		जाओ out;
	पूर्ण

	set_bit(DASD_FLAG_SAFE_OFFLINE, &device->flags);
	dasd_put_device(device);
	spin_unlock_irqrestore(get_ccwdev_lock(cdev), flags);

	rc = ccw_device_set_offline(cdev);

out:
	वापस rc ? rc : count;
पूर्ण

अटल DEVICE_ATTR(safe_offline, 0200, शून्य, dasd_safe_offline_store);

अटल sमाप_प्रकार
dasd_access_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		 अक्षर *buf)
अणु
	काष्ठा ccw_device *cdev = to_ccwdev(dev);
	काष्ठा dasd_device *device;
	पूर्णांक count;

	device = dasd_device_from_cdev(cdev);
	अगर (IS_ERR(device))
		वापस PTR_ERR(device);

	अगर (!device->discipline)
		count = -ENODEV;
	अन्यथा अगर (!device->discipline->host_access_count)
		count = -EOPNOTSUPP;
	अन्यथा
		count = device->discipline->host_access_count(device);

	dasd_put_device(device);
	अगर (count < 0)
		वापस count;

	वापस प्र_लिखो(buf, "%d\n", count);
पूर्ण

अटल DEVICE_ATTR(host_access_count, 0444, dasd_access_show, शून्य);

अटल sमाप_प्रकार
dasd_discipline_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		     अक्षर *buf)
अणु
	काष्ठा dasd_device *device;
	sमाप_प्रकार len;

	device = dasd_device_from_cdev(to_ccwdev(dev));
	अगर (IS_ERR(device))
		जाओ out;
	अन्यथा अगर (!device->discipline) अणु
		dasd_put_device(device);
		जाओ out;
	पूर्ण अन्यथा अणु
		len = snम_लिखो(buf, PAGE_SIZE, "%s\n",
			       device->discipline->name);
		dasd_put_device(device);
		वापस len;
	पूर्ण
out:
	len = snम_लिखो(buf, PAGE_SIZE, "none\n");
	वापस len;
पूर्ण

अटल DEVICE_ATTR(discipline, 0444, dasd_discipline_show, शून्य);

अटल sमाप_प्रकार
dasd_device_status_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		     अक्षर *buf)
अणु
	काष्ठा dasd_device *device;
	sमाप_प्रकार len;

	device = dasd_device_from_cdev(to_ccwdev(dev));
	अगर (!IS_ERR(device)) अणु
		चयन (device->state) अणु
		हाल DASD_STATE_NEW:
			len = snम_लिखो(buf, PAGE_SIZE, "new\n");
			अवरोध;
		हाल DASD_STATE_KNOWN:
			len = snम_लिखो(buf, PAGE_SIZE, "detected\n");
			अवरोध;
		हाल DASD_STATE_BASIC:
			len = snम_लिखो(buf, PAGE_SIZE, "basic\n");
			अवरोध;
		हाल DASD_STATE_UNFMT:
			len = snम_लिखो(buf, PAGE_SIZE, "unformatted\n");
			अवरोध;
		हाल DASD_STATE_READY:
			len = snम_लिखो(buf, PAGE_SIZE, "ready\n");
			अवरोध;
		हाल DASD_STATE_ONLINE:
			len = snम_लिखो(buf, PAGE_SIZE, "online\n");
			अवरोध;
		शेष:
			len = snम_लिखो(buf, PAGE_SIZE, "no stat\n");
			अवरोध;
		पूर्ण
		dasd_put_device(device);
	पूर्ण अन्यथा
		len = snम_लिखो(buf, PAGE_SIZE, "unknown\n");
	वापस len;
पूर्ण

अटल DEVICE_ATTR(status, 0444, dasd_device_status_show, शून्य);

अटल sमाप_प्रकार dasd_alias_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा dasd_device *device;
	काष्ठा dasd_uid uid;

	device = dasd_device_from_cdev(to_ccwdev(dev));
	अगर (IS_ERR(device))
		वापस प्र_लिखो(buf, "0\n");

	अगर (device->discipline && device->discipline->get_uid &&
	    !device->discipline->get_uid(device, &uid)) अणु
		अगर (uid.type == UA_BASE_PAV_ALIAS ||
		    uid.type == UA_HYPER_PAV_ALIAS) अणु
			dasd_put_device(device);
			वापस प्र_लिखो(buf, "1\n");
		पूर्ण
	पूर्ण
	dasd_put_device(device);

	वापस प्र_लिखो(buf, "0\n");
पूर्ण

अटल DEVICE_ATTR(alias, 0444, dasd_alias_show, शून्य);

अटल sमाप_प्रकार dasd_venकरोr_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा dasd_device *device;
	काष्ठा dasd_uid uid;
	अक्षर *venकरोr;

	device = dasd_device_from_cdev(to_ccwdev(dev));
	venकरोr = "";
	अगर (IS_ERR(device))
		वापस snम_लिखो(buf, PAGE_SIZE, "%s\n", venकरोr);

	अगर (device->discipline && device->discipline->get_uid &&
	    !device->discipline->get_uid(device, &uid))
			venकरोr = uid.venकरोr;

	dasd_put_device(device);

	वापस snम_लिखो(buf, PAGE_SIZE, "%s\n", venकरोr);
पूर्ण

अटल DEVICE_ATTR(venकरोr, 0444, dasd_venकरोr_show, शून्य);

#घोषणा UID_STRLEN ( /* venकरोr */ 3 + 1 + /* serial    */ 14 + 1 +\
		     /* SSID   */ 4 + 1 + /* unit addr */ 2 + 1 +\
		     /* vduit */ 32 + 1)

अटल sमाप_प्रकार
dasd_uid_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा dasd_device *device;
	काष्ठा dasd_uid uid;
	अक्षर uid_string[UID_STRLEN];
	अक्षर ua_string[3];

	device = dasd_device_from_cdev(to_ccwdev(dev));
	uid_string[0] = 0;
	अगर (IS_ERR(device))
		वापस snम_लिखो(buf, PAGE_SIZE, "%s\n", uid_string);

	अगर (device->discipline && device->discipline->get_uid &&
	    !device->discipline->get_uid(device, &uid)) अणु
		चयन (uid.type) अणु
		हाल UA_BASE_DEVICE:
			snम_लिखो(ua_string, माप(ua_string), "%02x",
				 uid.real_unit_addr);
			अवरोध;
		हाल UA_BASE_PAV_ALIAS:
			snम_लिखो(ua_string, माप(ua_string), "%02x",
				 uid.base_unit_addr);
			अवरोध;
		हाल UA_HYPER_PAV_ALIAS:
			snम_लिखो(ua_string, माप(ua_string), "xx");
			अवरोध;
		शेष:
			/* should not happen, treat like base device */
			snम_लिखो(ua_string, माप(ua_string), "%02x",
				 uid.real_unit_addr);
			अवरोध;
		पूर्ण

		अगर (म_माप(uid.vduit) > 0)
			snम_लिखो(uid_string, माप(uid_string),
				 "%s.%s.%04x.%s.%s",
				 uid.venकरोr, uid.serial, uid.ssid, ua_string,
				 uid.vduit);
		अन्यथा
			snम_लिखो(uid_string, माप(uid_string),
				 "%s.%s.%04x.%s",
				 uid.venकरोr, uid.serial, uid.ssid, ua_string);
	पूर्ण
	dasd_put_device(device);

	वापस snम_लिखो(buf, PAGE_SIZE, "%s\n", uid_string);
पूर्ण
अटल DEVICE_ATTR(uid, 0444, dasd_uid_show, शून्य);

/*
 * extended error-reporting
 */
अटल sमाप_प्रकार
dasd_eer_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा dasd_devmap *devmap;
	पूर्णांक eer_flag;

	devmap = dasd_find_busid(dev_name(dev));
	अगर (!IS_ERR(devmap) && devmap->device)
		eer_flag = dasd_eer_enabled(devmap->device);
	अन्यथा
		eer_flag = 0;
	वापस snम_लिखो(buf, PAGE_SIZE, eer_flag ? "1\n" : "0\n");
पूर्ण

अटल sमाप_प्रकार
dasd_eer_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
	       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा dasd_device *device;
	अचिन्हित पूर्णांक val;
	पूर्णांक rc = 0;

	device = dasd_device_from_cdev(to_ccwdev(dev));
	अगर (IS_ERR(device))
		वापस PTR_ERR(device);

	अगर (kstrtouपूर्णांक(buf, 0, &val) || val > 1)
		वापस -EINVAL;

	अगर (val)
		rc = dasd_eer_enable(device);
	अन्यथा
		dasd_eer_disable(device);

	dasd_put_device(device);

	वापस rc ? : count;
पूर्ण

अटल DEVICE_ATTR(eer_enabled, 0644, dasd_eer_show, dasd_eer_store);

/*
 * expiration समय क्रम शेष requests
 */
अटल sमाप_प्रकार
dasd_expires_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा dasd_device *device;
	पूर्णांक len;

	device = dasd_device_from_cdev(to_ccwdev(dev));
	अगर (IS_ERR(device))
		वापस -ENODEV;
	len = snम_लिखो(buf, PAGE_SIZE, "%lu\n", device->शेष_expires);
	dasd_put_device(device);
	वापस len;
पूर्ण

अटल sमाप_प्रकार
dasd_expires_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
	       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा dasd_device *device;
	अचिन्हित दीर्घ val;

	device = dasd_device_from_cdev(to_ccwdev(dev));
	अगर (IS_ERR(device))
		वापस -ENODEV;

	अगर ((kम_से_अदीर्घ(buf, 10, &val) != 0) ||
	    (val > DASD_EXPIRES_MAX) || val == 0) अणु
		dasd_put_device(device);
		वापस -EINVAL;
	पूर्ण

	अगर (val)
		device->शेष_expires = val;

	dasd_put_device(device);
	वापस count;
पूर्ण

अटल DEVICE_ATTR(expires, 0644, dasd_expires_show, dasd_expires_store);

अटल sमाप_प्रकार
dasd_retries_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा dasd_device *device;
	पूर्णांक len;

	device = dasd_device_from_cdev(to_ccwdev(dev));
	अगर (IS_ERR(device))
		वापस -ENODEV;
	len = snम_लिखो(buf, PAGE_SIZE, "%lu\n", device->शेष_retries);
	dasd_put_device(device);
	वापस len;
पूर्ण

अटल sमाप_प्रकार
dasd_retries_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
		   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा dasd_device *device;
	अचिन्हित दीर्घ val;

	device = dasd_device_from_cdev(to_ccwdev(dev));
	अगर (IS_ERR(device))
		वापस -ENODEV;

	अगर ((kम_से_अदीर्घ(buf, 10, &val) != 0) ||
	    (val > DASD_RETRIES_MAX)) अणु
		dasd_put_device(device);
		वापस -EINVAL;
	पूर्ण

	अगर (val)
		device->शेष_retries = val;

	dasd_put_device(device);
	वापस count;
पूर्ण

अटल DEVICE_ATTR(retries, 0644, dasd_retries_show, dasd_retries_store);

अटल sमाप_प्रकार
dasd_समयout_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		  अक्षर *buf)
अणु
	काष्ठा dasd_device *device;
	पूर्णांक len;

	device = dasd_device_from_cdev(to_ccwdev(dev));
	अगर (IS_ERR(device))
		वापस -ENODEV;
	len = snम_लिखो(buf, PAGE_SIZE, "%lu\n", device->blk_समयout);
	dasd_put_device(device);
	वापस len;
पूर्ण

अटल sमाप_प्रकार
dasd_समयout_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
		   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा dasd_device *device;
	काष्ठा request_queue *q;
	अचिन्हित दीर्घ val;

	device = dasd_device_from_cdev(to_ccwdev(dev));
	अगर (IS_ERR(device) || !device->block)
		वापस -ENODEV;

	अगर ((kम_से_अदीर्घ(buf, 10, &val) != 0) ||
	    val > अच_पूर्णांक_उच्च / HZ) अणु
		dasd_put_device(device);
		वापस -EINVAL;
	पूर्ण
	q = device->block->request_queue;
	अगर (!q) अणु
		dasd_put_device(device);
		वापस -ENODEV;
	पूर्ण

	device->blk_समयout = val;

	blk_queue_rq_समयout(q, device->blk_समयout * HZ);

	dasd_put_device(device);
	वापस count;
पूर्ण

अटल DEVICE_ATTR(समयout, 0644,
		   dasd_समयout_show, dasd_समयout_store);


अटल sमाप_प्रकार
dasd_path_reset_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
		      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा dasd_device *device;
	अचिन्हित पूर्णांक val;

	device = dasd_device_from_cdev(to_ccwdev(dev));
	अगर (IS_ERR(device))
		वापस -ENODEV;

	अगर ((kstrtouपूर्णांक(buf, 16, &val) != 0) || val > 0xff)
		val = 0;

	अगर (device->discipline && device->discipline->reset_path)
		device->discipline->reset_path(device, (__u8) val);

	dasd_put_device(device);
	वापस count;
पूर्ण

अटल DEVICE_ATTR(path_reset, 0200, शून्य, dasd_path_reset_store);

अटल sमाप_प्रकार dasd_hpf_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा dasd_device *device;
	पूर्णांक hpf;

	device = dasd_device_from_cdev(to_ccwdev(dev));
	अगर (IS_ERR(device))
		वापस -ENODEV;
	अगर (!device->discipline || !device->discipline->hpf_enabled) अणु
		dasd_put_device(device);
		वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", dasd_nofcx);
	पूर्ण
	hpf = device->discipline->hpf_enabled(device);
	dasd_put_device(device);
	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", hpf);
पूर्ण

अटल DEVICE_ATTR(hpf, 0444, dasd_hpf_show, शून्य);

अटल sमाप_प्रकार dasd_reservation_policy_show(काष्ठा device *dev,
					    काष्ठा device_attribute *attr,
					    अक्षर *buf)
अणु
	काष्ठा dasd_devmap *devmap;
	पूर्णांक rc = 0;

	devmap = dasd_find_busid(dev_name(dev));
	अगर (IS_ERR(devmap)) अणु
		rc = snम_लिखो(buf, PAGE_SIZE, "ignore\n");
	पूर्ण अन्यथा अणु
		spin_lock(&dasd_devmap_lock);
		अगर (devmap->features & DASD_FEATURE_FAILONSLCK)
			rc = snम_लिखो(buf, PAGE_SIZE, "fail\n");
		अन्यथा
			rc = snम_लिखो(buf, PAGE_SIZE, "ignore\n");
		spin_unlock(&dasd_devmap_lock);
	पूर्ण
	वापस rc;
पूर्ण

अटल sमाप_प्रकार dasd_reservation_policy_store(काष्ठा device *dev,
					     काष्ठा device_attribute *attr,
					     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा ccw_device *cdev = to_ccwdev(dev);
	पूर्णांक rc;

	अगर (sysfs_streq("ignore", buf))
		rc = dasd_set_feature(cdev, DASD_FEATURE_FAILONSLCK, 0);
	अन्यथा अगर (sysfs_streq("fail", buf))
		rc = dasd_set_feature(cdev, DASD_FEATURE_FAILONSLCK, 1);
	अन्यथा
		rc = -EINVAL;

	वापस rc ? : count;
पूर्ण

अटल DEVICE_ATTR(reservation_policy, 0644,
		   dasd_reservation_policy_show, dasd_reservation_policy_store);

अटल sमाप_प्रकार dasd_reservation_state_show(काष्ठा device *dev,
					   काष्ठा device_attribute *attr,
					   अक्षर *buf)
अणु
	काष्ठा dasd_device *device;
	पूर्णांक rc = 0;

	device = dasd_device_from_cdev(to_ccwdev(dev));
	अगर (IS_ERR(device))
		वापस snम_लिखो(buf, PAGE_SIZE, "none\n");

	अगर (test_bit(DASD_FLAG_IS_RESERVED, &device->flags))
		rc = snम_लिखो(buf, PAGE_SIZE, "reserved\n");
	अन्यथा अगर (test_bit(DASD_FLAG_LOCK_STOLEN, &device->flags))
		rc = snम_लिखो(buf, PAGE_SIZE, "lost\n");
	अन्यथा
		rc = snम_लिखो(buf, PAGE_SIZE, "none\n");
	dasd_put_device(device);
	वापस rc;
पूर्ण

अटल sमाप_प्रकार dasd_reservation_state_store(काष्ठा device *dev,
					    काष्ठा device_attribute *attr,
					    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा dasd_device *device;
	पूर्णांक rc = 0;

	device = dasd_device_from_cdev(to_ccwdev(dev));
	अगर (IS_ERR(device))
		वापस -ENODEV;
	अगर (sysfs_streq("reset", buf))
		clear_bit(DASD_FLAG_LOCK_STOLEN, &device->flags);
	अन्यथा
		rc = -EINVAL;
	dasd_put_device(device);

	अगर (rc)
		वापस rc;
	अन्यथा
		वापस count;
पूर्ण

अटल DEVICE_ATTR(last_known_reservation_state, 0644,
		   dasd_reservation_state_show, dasd_reservation_state_store);

अटल sमाप_प्रकार dasd_pm_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा dasd_device *device;
	u8 opm, nppm, cablepm, cuirpm, hpfpm, अगरccpm;

	device = dasd_device_from_cdev(to_ccwdev(dev));
	अगर (IS_ERR(device))
		वापस प्र_लिखो(buf, "0\n");

	opm = dasd_path_get_opm(device);
	nppm = dasd_path_get_nppm(device);
	cablepm = dasd_path_get_cablepm(device);
	cuirpm = dasd_path_get_cuirpm(device);
	hpfpm = dasd_path_get_hpfpm(device);
	अगरccpm = dasd_path_get_अगरccpm(device);
	dasd_put_device(device);

	वापस प्र_लिखो(buf, "%02x %02x %02x %02x %02x %02x\n", opm, nppm,
		       cablepm, cuirpm, hpfpm, अगरccpm);
पूर्ण

अटल DEVICE_ATTR(path_masks, 0444, dasd_pm_show, शून्य);

/*
 * threshold value क्रम IFCC/CCC errors
 */
अटल sमाप_प्रकार
dasd_path_threshold_show(काष्ठा device *dev,
			  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा dasd_device *device;
	पूर्णांक len;

	device = dasd_device_from_cdev(to_ccwdev(dev));
	अगर (IS_ERR(device))
		वापस -ENODEV;
	len = snम_लिखो(buf, PAGE_SIZE, "%lu\n", device->path_thrhld);
	dasd_put_device(device);
	वापस len;
पूर्ण

अटल sमाप_प्रकार
dasd_path_threshold_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा dasd_device *device;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ val;

	device = dasd_device_from_cdev(to_ccwdev(dev));
	अगर (IS_ERR(device))
		वापस -ENODEV;

	अगर (kम_से_अदीर्घ(buf, 10, &val) != 0 || val > DASD_THRHLD_MAX) अणु
		dasd_put_device(device);
		वापस -EINVAL;
	पूर्ण
	spin_lock_irqsave(get_ccwdev_lock(to_ccwdev(dev)), flags);
	device->path_thrhld = val;
	spin_unlock_irqrestore(get_ccwdev_lock(to_ccwdev(dev)), flags);
	dasd_put_device(device);
	वापस count;
पूर्ण
अटल DEVICE_ATTR(path_threshold, 0644, dasd_path_threshold_show,
		   dasd_path_threshold_store);

/*
 * configure अगर path is disabled after IFCC/CCC error threshold is
 * exceeded
 */
अटल sमाप_प्रकार
dasd_path_स्वतःdisable_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा dasd_devmap *devmap;
	पूर्णांक flag;

	devmap = dasd_find_busid(dev_name(dev));
	अगर (!IS_ERR(devmap))
		flag = (devmap->features & DASD_FEATURE_PATH_AUTODISABLE) != 0;
	अन्यथा
		flag = (DASD_FEATURE_DEFAULT &
			DASD_FEATURE_PATH_AUTODISABLE) != 0;
	वापस snम_लिखो(buf, PAGE_SIZE, flag ? "1\n" : "0\n");
पूर्ण

अटल sमाप_प्रकार
dasd_path_स्वतःdisable_store(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक rc;

	अगर (kstrtouपूर्णांक(buf, 0, &val) || val > 1)
		वापस -EINVAL;

	rc = dasd_set_feature(to_ccwdev(dev),
			      DASD_FEATURE_PATH_AUTODISABLE, val);

	वापस rc ? : count;
पूर्ण

अटल DEVICE_ATTR(path_स्वतःdisable, 0644,
		   dasd_path_स्वतःdisable_show,
		   dasd_path_स्वतःdisable_store);
/*
 * पूर्णांकerval क्रम IFCC/CCC checks
 * meaning समय with no IFCC/CCC error beक्रमe the error counter
 * माला_लो reset
 */
अटल sमाप_प्रकार
dasd_path_पूर्णांकerval_show(काष्ठा device *dev,
			काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा dasd_device *device;
	पूर्णांक len;

	device = dasd_device_from_cdev(to_ccwdev(dev));
	अगर (IS_ERR(device))
		वापस -ENODEV;
	len = snम_लिखो(buf, PAGE_SIZE, "%lu\n", device->path_पूर्णांकerval);
	dasd_put_device(device);
	वापस len;
पूर्ण

अटल sमाप_प्रकार
dasd_path_पूर्णांकerval_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
	       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा dasd_device *device;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ val;

	device = dasd_device_from_cdev(to_ccwdev(dev));
	अगर (IS_ERR(device))
		वापस -ENODEV;

	अगर ((kम_से_अदीर्घ(buf, 10, &val) != 0) ||
	    (val > DASD_INTERVAL_MAX) || val == 0) अणु
		dasd_put_device(device);
		वापस -EINVAL;
	पूर्ण
	spin_lock_irqsave(get_ccwdev_lock(to_ccwdev(dev)), flags);
	अगर (val)
		device->path_पूर्णांकerval = val;
	spin_unlock_irqrestore(get_ccwdev_lock(to_ccwdev(dev)), flags);
	dasd_put_device(device);
	वापस count;
पूर्ण

अटल DEVICE_ATTR(path_पूर्णांकerval, 0644, dasd_path_पूर्णांकerval_show,
		   dasd_path_पूर्णांकerval_store);

अटल sमाप_प्रकार
dasd_device_fcs_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		     अक्षर *buf)
अणु
	काष्ठा dasd_device *device;
	पूर्णांक fc_sec;
	पूर्णांक rc;

	device = dasd_device_from_cdev(to_ccwdev(dev));
	अगर (IS_ERR(device))
		वापस -ENODEV;
	fc_sec = dasd_path_get_fcs_device(device);
	अगर (fc_sec == -EINVAL)
		rc = snम_लिखो(buf, PAGE_SIZE, "Inconsistent\n");
	अन्यथा
		rc = snम_लिखो(buf, PAGE_SIZE, "%s\n", dasd_path_get_fcs_str(fc_sec));
	dasd_put_device(device);

	वापस rc;
पूर्ण
अटल DEVICE_ATTR(fc_security, 0444, dasd_device_fcs_show, शून्य);

अटल sमाप_प्रकार
dasd_path_fcs_show(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	काष्ठा dasd_path *path = to_dasd_path(kobj);
	अचिन्हित पूर्णांक fc_sec = path->fc_security;

	वापस snम_लिखो(buf, PAGE_SIZE, "%s\n", dasd_path_get_fcs_str(fc_sec));
पूर्ण

अटल काष्ठा kobj_attribute path_fcs_attribute =
	__ATTR(fc_security, 0444, dasd_path_fcs_show, शून्य);

#घोषणा DASD_DEFINE_ATTR(_name, _func)					\
अटल sमाप_प्रकार dasd_##_name##_show(काष्ठा device *dev,			\
				   काष्ठा device_attribute *attr,	\
				   अक्षर *buf)				\
अणु									\
	काष्ठा ccw_device *cdev = to_ccwdev(dev);			\
	काष्ठा dasd_device *device = dasd_device_from_cdev(cdev);	\
	पूर्णांक val = 0;							\
									\
	अगर (IS_ERR(device))						\
		वापस -ENODEV;						\
	अगर (device->discipline && _func)				\
		val = _func(device);					\
	dasd_put_device(device);					\
									\
	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", val);			\
पूर्ण									\
अटल DEVICE_ATTR(_name, 0444, dasd_##_name##_show, शून्य);		\

DASD_DEFINE_ATTR(ese, device->discipline->is_ese);
DASD_DEFINE_ATTR(extent_size, device->discipline->ext_size);
DASD_DEFINE_ATTR(pool_id, device->discipline->ext_pool_id);
DASD_DEFINE_ATTR(space_configured, device->discipline->space_configured);
DASD_DEFINE_ATTR(space_allocated, device->discipline->space_allocated);
DASD_DEFINE_ATTR(logical_capacity, device->discipline->logical_capacity);
DASD_DEFINE_ATTR(warn_threshold, device->discipline->ext_pool_warn_thrshld);
DASD_DEFINE_ATTR(cap_at_warnlevel, device->discipline->ext_pool_cap_at_warnlevel);
DASD_DEFINE_ATTR(pool_oos, device->discipline->ext_pool_oos);

अटल काष्ठा attribute * dasd_attrs[] = अणु
	&dev_attr_पढ़ोonly.attr,
	&dev_attr_discipline.attr,
	&dev_attr_status.attr,
	&dev_attr_alias.attr,
	&dev_attr_venकरोr.attr,
	&dev_attr_uid.attr,
	&dev_attr_use_diag.attr,
	&dev_attr_raw_track_access.attr,
	&dev_attr_eer_enabled.attr,
	&dev_attr_erplog.attr,
	&dev_attr_failfast.attr,
	&dev_attr_expires.attr,
	&dev_attr_retries.attr,
	&dev_attr_समयout.attr,
	&dev_attr_reservation_policy.attr,
	&dev_attr_last_known_reservation_state.attr,
	&dev_attr_safe_offline.attr,
	&dev_attr_host_access_count.attr,
	&dev_attr_path_masks.attr,
	&dev_attr_path_threshold.attr,
	&dev_attr_path_स्वतःdisable.attr,
	&dev_attr_path_पूर्णांकerval.attr,
	&dev_attr_path_reset.attr,
	&dev_attr_hpf.attr,
	&dev_attr_ese.attr,
	&dev_attr_fc_security.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group dasd_attr_group = अणु
	.attrs = dasd_attrs,
पूर्ण;

अटल काष्ठा attribute *capacity_attrs[] = अणु
	&dev_attr_space_configured.attr,
	&dev_attr_space_allocated.attr,
	&dev_attr_logical_capacity.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group capacity_attr_group = अणु
	.name = "capacity",
	.attrs = capacity_attrs,
पूर्ण;

अटल काष्ठा attribute *ext_pool_attrs[] = अणु
	&dev_attr_pool_id.attr,
	&dev_attr_extent_size.attr,
	&dev_attr_warn_threshold.attr,
	&dev_attr_cap_at_warnlevel.attr,
	&dev_attr_pool_oos.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group ext_pool_attr_group = अणु
	.name = "extent_pool",
	.attrs = ext_pool_attrs,
पूर्ण;

स्थिर काष्ठा attribute_group *dasd_dev_groups[] = अणु
	&dasd_attr_group,
	&capacity_attr_group,
	&ext_pool_attr_group,
	शून्य,
पूर्ण;
EXPORT_SYMBOL_GPL(dasd_dev_groups);

/*
 * Return value of the specअगरied feature.
 */
पूर्णांक
dasd_get_feature(काष्ठा ccw_device *cdev, पूर्णांक feature)
अणु
	काष्ठा dasd_devmap *devmap;

	devmap = dasd_find_busid(dev_name(&cdev->dev));
	अगर (IS_ERR(devmap))
		वापस PTR_ERR(devmap);

	वापस ((devmap->features & feature) != 0);
पूर्ण

/*
 * Set / reset given feature.
 * Flag indicates whether to set (!=0) or the reset (=0) the feature.
 */
पूर्णांक
dasd_set_feature(काष्ठा ccw_device *cdev, पूर्णांक feature, पूर्णांक flag)
अणु
	काष्ठा dasd_devmap *devmap;

	devmap = dasd_devmap_from_cdev(cdev);
	अगर (IS_ERR(devmap))
		वापस PTR_ERR(devmap);

	spin_lock(&dasd_devmap_lock);
	अगर (flag)
		devmap->features |= feature;
	अन्यथा
		devmap->features &= ~feature;
	अगर (devmap->device)
		devmap->device->features = devmap->features;
	spin_unlock(&dasd_devmap_lock);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(dasd_set_feature);

अटल काष्ठा attribute *paths_info_attrs[] = अणु
	&path_fcs_attribute.attr,
	शून्य,
पूर्ण;

अटल काष्ठा kobj_type path_attr_type = अणु
	.release	= dasd_path_release,
	.शेष_attrs	= paths_info_attrs,
	.sysfs_ops	= &kobj_sysfs_ops,
पूर्ण;

अटल व्योम dasd_path_init_kobj(काष्ठा dasd_device *device, पूर्णांक chp)
अणु
	device->path[chp].kobj.kset = device->paths_info;
	kobject_init(&device->path[chp].kobj, &path_attr_type);
पूर्ण

व्योम dasd_path_create_kobj(काष्ठा dasd_device *device, पूर्णांक chp)
अणु
	पूर्णांक rc;

	अगर (test_bit(DASD_FLAG_OFFLINE, &device->flags))
		वापस;
	अगर (!device->paths_info) अणु
		dev_warn(&device->cdev->dev, "Unable to create paths objects\n");
		वापस;
	पूर्ण
	अगर (device->path[chp].in_sysfs)
		वापस;
	अगर (!device->path[chp].conf_data)
		वापस;

	dasd_path_init_kobj(device, chp);

	rc = kobject_add(&device->path[chp].kobj, शून्य, "%x.%02x",
			 device->path[chp].cssid, device->path[chp].chpid);
	अगर (rc)
		kobject_put(&device->path[chp].kobj);
	device->path[chp].in_sysfs = true;
पूर्ण
EXPORT_SYMBOL(dasd_path_create_kobj);

व्योम dasd_path_create_kobjects(काष्ठा dasd_device *device)
अणु
	u8 lpm, opm;

	opm = dasd_path_get_opm(device);
	क्रम (lpm = 0x80; lpm; lpm >>= 1) अणु
		अगर (!(lpm & opm))
			जारी;
		dasd_path_create_kobj(device, pathmask_to_pos(lpm));
	पूर्ण
पूर्ण
EXPORT_SYMBOL(dasd_path_create_kobjects);

अटल व्योम dasd_path_हटाओ_kobj(काष्ठा dasd_device *device, पूर्णांक chp)
अणु
	अगर (device->path[chp].in_sysfs) अणु
		kobject_put(&device->path[chp].kobj);
		device->path[chp].in_sysfs = false;
	पूर्ण
पूर्ण

/*
 * As we keep kobjects क्रम the lअगरeसमय of a device, this function must not be
 * called anywhere but in the context of offlining a device.
 */
व्योम dasd_path_हटाओ_kobjects(काष्ठा dasd_device *device)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 8; i++)
		dasd_path_हटाओ_kobj(device, i);
पूर्ण
EXPORT_SYMBOL(dasd_path_हटाओ_kobjects);

पूर्णांक
dasd_devmap_init(व्योम)
अणु
	पूर्णांक i;

	/* Initialize devmap काष्ठाures. */
	dasd_max_devindex = 0;
	क्रम (i = 0; i < 256; i++)
		INIT_LIST_HEAD(&dasd_hashlists[i]);
	वापस 0;
पूर्ण

व्योम
dasd_devmap_निकास(व्योम)
अणु
	dasd_क्रमget_ranges();
पूर्ण
