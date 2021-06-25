<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * EISA bus support functions क्रम sysfs.
 *
 * (C) 2002, 2003 Marc Zyngier <maz@wild-wind.fr.eu.org>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/eisa.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/ioport.h>
#समावेश <यंत्र/पन.स>

#घोषणा SLOT_ADDRESS(r,n) (r->bus_base_addr + (0x1000 * n))

#घोषणा EISA_DEVINFO(i,s) अणु .id = अणु .sig = i पूर्ण, .name = s पूर्ण

काष्ठा eisa_device_info अणु
	काष्ठा eisa_device_id id;
	अक्षर name[50];
पूर्ण;

#अगर_घोषित CONFIG_EISA_NAMES
अटल काष्ठा eisa_device_info __initdata eisa_table[] = अणु
#समावेश "devlist.h"
पूर्ण;
#घोषणा EISA_INFOS (माप (eisa_table) / (माप (काष्ठा eisa_device_info)))
#पूर्ण_अगर

#घोषणा EISA_MAX_FORCED_DEV 16

अटल पूर्णांक enable_dev[EISA_MAX_FORCED_DEV];
अटल अचिन्हित पूर्णांक enable_dev_count;
अटल पूर्णांक disable_dev[EISA_MAX_FORCED_DEV];
अटल अचिन्हित पूर्णांक disable_dev_count;

अटल पूर्णांक is_क्रमced_dev(पूर्णांक *क्रमced_tab,
			 पूर्णांक क्रमced_count,
			 काष्ठा eisa_root_device *root,
			 काष्ठा eisa_device *edev)
अणु
	पूर्णांक i, x;

	क्रम (i = 0; i < क्रमced_count; i++) अणु
		x = (root->bus_nr << 8) | edev->slot;
		अगर (क्रमced_tab[i] == x)
			वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __init eisa_name_device(काष्ठा eisa_device *edev)
अणु
#अगर_घोषित CONFIG_EISA_NAMES
	पूर्णांक i;
	क्रम (i = 0; i < EISA_INFOS; i++) अणु
		अगर (!म_भेद(edev->id.sig, eisa_table[i].id.sig)) अणु
			strlcpy(edev->pretty_name,
				eisa_table[i].name,
				माप(edev->pretty_name));
			वापस;
		पूर्ण
	पूर्ण

	/* No name was found */
	प्र_लिखो(edev->pretty_name, "EISA device %.7s", edev->id.sig);
#पूर्ण_अगर
पूर्ण

अटल अक्षर __init *decode_eisa_sig(अचिन्हित दीर्घ addr)
अणु
	अटल अक्षर sig_str[EISA_SIG_LEN];
	u8 sig[4];
	u16 rev;
	पूर्णांक i;

	क्रम (i = 0; i < 4; i++) अणु
#अगर_घोषित CONFIG_EISA_VLB_PRIMING
		/*
		 * This ugly stuff is used to wake up VL-bus cards
		 * (AHA-284x is the only known example), so we can
		 * पढ़ो the EISA id.
		 *
		 * Thankfully, this only exists on x86...
		 */
		outb(0x80 + i, addr);
#पूर्ण_अगर
		sig[i] = inb(addr + i);

		अगर (!i && (sig[0] & 0x80))
			वापस शून्य;
	पूर्ण

	sig_str[0] = ((sig[0] >> 2) & 0x1f) + ('A' - 1);
	sig_str[1] = (((sig[0] & 3) << 3) | (sig[1] >> 5)) + ('A' - 1);
	sig_str[2] = (sig[1] & 0x1f) + ('A' - 1);
	rev = (sig[2] << 8) | sig[3];
	प्र_लिखो(sig_str + 3, "%04X", rev);

	वापस sig_str;
पूर्ण

अटल पूर्णांक eisa_bus_match(काष्ठा device *dev, काष्ठा device_driver *drv)
अणु
	काष्ठा eisa_device *edev = to_eisa_device(dev);
	काष्ठा eisa_driver *edrv = to_eisa_driver(drv);
	स्थिर काष्ठा eisa_device_id *eids = edrv->id_table;

	अगर (!eids)
		वापस 0;

	जबतक (म_माप(eids->sig)) अणु
		अगर (!म_भेद(eids->sig, edev->id.sig) &&
		    edev->state & EISA_CONFIG_ENABLED) अणु
			edev->id.driver_data = eids->driver_data;
			वापस 1;
		पूर्ण

		eids++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक eisa_bus_uevent(काष्ठा device *dev, काष्ठा kobj_uevent_env *env)
अणु
	काष्ठा eisa_device *edev = to_eisa_device(dev);

	add_uevent_var(env, "MODALIAS=" EISA_DEVICE_MODALIAS_FMT, edev->id.sig);
	वापस 0;
पूर्ण

काष्ठा bus_type eisa_bus_type = अणु
	.name  = "eisa",
	.match = eisa_bus_match,
	.uevent = eisa_bus_uevent,
पूर्ण;
EXPORT_SYMBOL(eisa_bus_type);

पूर्णांक eisa_driver_रेजिस्टर(काष्ठा eisa_driver *edrv)
अणु
	edrv->driver.bus = &eisa_bus_type;
	वापस driver_रेजिस्टर(&edrv->driver);
पूर्ण
EXPORT_SYMBOL(eisa_driver_रेजिस्टर);

व्योम eisa_driver_unरेजिस्टर(काष्ठा eisa_driver *edrv)
अणु
	driver_unरेजिस्टर(&edrv->driver);
पूर्ण
EXPORT_SYMBOL(eisa_driver_unरेजिस्टर);

अटल sमाप_प्रकार eisa_show_sig(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा eisa_device *edev = to_eisa_device(dev);
	वापस प्र_लिखो(buf, "%s\n", edev->id.sig);
पूर्ण

अटल DEVICE_ATTR(signature, S_IRUGO, eisa_show_sig, शून्य);

अटल sमाप_प्रकार eisa_show_state(काष्ठा device *dev,
			       काष्ठा device_attribute *attr,
			       अक्षर *buf)
अणु
	काष्ठा eisa_device *edev = to_eisa_device(dev);
	वापस प्र_लिखो(buf, "%d\n", edev->state & EISA_CONFIG_ENABLED);
पूर्ण

अटल DEVICE_ATTR(enabled, S_IRUGO, eisa_show_state, शून्य);

अटल sमाप_प्रकार eisa_show_modalias(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  अक्षर *buf)
अणु
	काष्ठा eisa_device *edev = to_eisa_device(dev);
	वापस प्र_लिखो(buf, EISA_DEVICE_MODALIAS_FMT "\n", edev->id.sig);
पूर्ण

अटल DEVICE_ATTR(modalias, S_IRUGO, eisa_show_modalias, शून्य);

अटल पूर्णांक __init eisa_init_device(काष्ठा eisa_root_device *root,
				   काष्ठा eisa_device *edev,
				   पूर्णांक slot)
अणु
	अक्षर *sig;
	अचिन्हित दीर्घ sig_addr;
	पूर्णांक i;

	sig_addr = SLOT_ADDRESS(root, slot) + EISA_VENDOR_ID_OFFSET;

	sig = decode_eisa_sig(sig_addr);
	अगर (!sig)
		वापस -1;	/* No EISA device here */

	स_नकल(edev->id.sig, sig, EISA_SIG_LEN);
	edev->slot = slot;
	edev->state = inb(SLOT_ADDRESS(root, slot) + EISA_CONFIG_OFFSET)
		      & EISA_CONFIG_ENABLED;
	edev->base_addr = SLOT_ADDRESS(root, slot);
	edev->dma_mask = root->dma_mask; /* Default DMA mask */
	eisa_name_device(edev);
	edev->dev.parent = root->dev;
	edev->dev.bus = &eisa_bus_type;
	edev->dev.dma_mask = &edev->dma_mask;
	edev->dev.coherent_dma_mask = edev->dma_mask;
	dev_set_name(&edev->dev, "%02X:%02X", root->bus_nr, slot);

	क्रम (i = 0; i < EISA_MAX_RESOURCES; i++) अणु
#अगर_घोषित CONFIG_EISA_NAMES
		edev->res[i].name = edev->pretty_name;
#अन्यथा
		edev->res[i].name = edev->id.sig;
#पूर्ण_अगर
	पूर्ण

	अगर (is_क्रमced_dev(enable_dev, enable_dev_count, root, edev))
		edev->state = EISA_CONFIG_ENABLED | EISA_CONFIG_FORCED;

	अगर (is_क्रमced_dev(disable_dev, disable_dev_count, root, edev))
		edev->state = EISA_CONFIG_FORCED;

	वापस 0;
पूर्ण

अटल पूर्णांक __init eisa_रेजिस्टर_device(काष्ठा eisa_device *edev)
अणु
	पूर्णांक rc = device_रेजिस्टर(&edev->dev);
	अगर (rc) अणु
		put_device(&edev->dev);
		वापस rc;
	पूर्ण

	rc = device_create_file(&edev->dev, &dev_attr_signature);
	अगर (rc)
		जाओ err_devreg;
	rc = device_create_file(&edev->dev, &dev_attr_enabled);
	अगर (rc)
		जाओ err_sig;
	rc = device_create_file(&edev->dev, &dev_attr_modalias);
	अगर (rc)
		जाओ err_enab;

	वापस 0;

err_enab:
	device_हटाओ_file(&edev->dev, &dev_attr_enabled);
err_sig:
	device_हटाओ_file(&edev->dev, &dev_attr_signature);
err_devreg:
	device_unरेजिस्टर(&edev->dev);
	वापस rc;
पूर्ण

अटल पूर्णांक __init eisa_request_resources(काष्ठा eisa_root_device *root,
					 काष्ठा eisa_device *edev,
					 पूर्णांक slot)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < EISA_MAX_RESOURCES; i++) अणु
		/* Don't रेजिस्टर resource क्रम slot 0, since this is
		 * very likely to fail... :-( Instead, grab the EISA
		 * id, now we can display something in /proc/ioports.
		 */

		/* Only one region क्रम मुख्यboard */
		अगर (!slot && i > 0) अणु
			edev->res[i].start = edev->res[i].end = 0;
			जारी;
		पूर्ण

		अगर (slot) अणु
			edev->res[i].name  = शून्य;
			edev->res[i].start = SLOT_ADDRESS(root, slot)
					     + (i * 0x400);
			edev->res[i].end   = edev->res[i].start + 0xff;
			edev->res[i].flags = IORESOURCE_IO;
		पूर्ण अन्यथा अणु
			edev->res[i].name  = शून्य;
			edev->res[i].start = SLOT_ADDRESS(root, slot)
					     + EISA_VENDOR_ID_OFFSET;
			edev->res[i].end   = edev->res[i].start + 3;
			edev->res[i].flags = IORESOURCE_IO | IORESOURCE_BUSY;
		पूर्ण

		अगर (request_resource(root->res, &edev->res[i]))
			जाओ failed;
	पूर्ण

	वापस 0;

 failed:
	जबतक (--i >= 0)
		release_resource(&edev->res[i]);

	वापस -1;
पूर्ण

अटल व्योम __init eisa_release_resources(काष्ठा eisa_device *edev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < EISA_MAX_RESOURCES; i++)
		अगर (edev->res[i].start || edev->res[i].end)
			release_resource(&edev->res[i]);
पूर्ण

अटल पूर्णांक __init eisa_probe(काष्ठा eisa_root_device *root)
अणु
	पूर्णांक i, c;
	काष्ठा eisa_device *edev;
	अक्षर *enabled_str;

	dev_info(root->dev, "Probing EISA bus %d\n", root->bus_nr);

	/* First try to get hold of slot 0. If there is no device
	 * here, simply fail, unless root->क्रमce_probe is set. */

	edev = kzalloc(माप(*edev), GFP_KERNEL);
	अगर (!edev)
		वापस -ENOMEM;

	अगर (eisa_request_resources(root, edev, 0)) अणु
		dev_warn(root->dev,
			 "EISA: Cannot allocate resource for mainboard\n");
		kमुक्त(edev);
		अगर (!root->क्रमce_probe)
			वापस -EBUSY;
		जाओ क्रमce_probe;
	पूर्ण

	अगर (eisa_init_device(root, edev, 0)) अणु
		eisa_release_resources(edev);
		kमुक्त(edev);
		अगर (!root->क्रमce_probe)
			वापस -ENODEV;
		जाओ क्रमce_probe;
	पूर्ण

	dev_info(&edev->dev, "EISA: Mainboard %s detected\n", edev->id.sig);

	अगर (eisa_रेजिस्टर_device(edev)) अणु
		dev_err(&edev->dev, "EISA: Failed to register %s\n",
			edev->id.sig);
		eisa_release_resources(edev);
		kमुक्त(edev);
	पूर्ण

 क्रमce_probe:

	क्रम (c = 0, i = 1; i <= root->slots; i++) अणु
		edev = kzalloc(माप(*edev), GFP_KERNEL);
		अगर (!edev) अणु
			dev_err(root->dev, "EISA: Out of memory for slot %d\n",
				i);
			जारी;
		पूर्ण

		अगर (eisa_request_resources(root, edev, i)) अणु
			dev_warn(root->dev,
				 "Cannot allocate resource for EISA slot %d\n",
				 i);
			kमुक्त(edev);
			जारी;
		पूर्ण

		अगर (eisa_init_device(root, edev, i)) अणु
			eisa_release_resources(edev);
			kमुक्त(edev);
			जारी;
		पूर्ण

		अगर (edev->state == (EISA_CONFIG_ENABLED | EISA_CONFIG_FORCED))
			enabled_str = " (forced enabled)";
		अन्यथा अगर (edev->state == EISA_CONFIG_FORCED)
			enabled_str = " (forced disabled)";
		अन्यथा अगर (edev->state == 0)
			enabled_str = " (disabled)";
		अन्यथा
			enabled_str = "";

		dev_info(&edev->dev, "EISA: slot %d: %s detected%s\n", i,
			 edev->id.sig, enabled_str);

		c++;

		अगर (eisa_रेजिस्टर_device(edev)) अणु
			dev_err(&edev->dev, "EISA: Failed to register %s\n",
				edev->id.sig);
			eisa_release_resources(edev);
			kमुक्त(edev);
		पूर्ण
	पूर्ण

	dev_info(root->dev, "EISA: Detected %d card%s\n", c, c == 1 ? "" : "s");
	वापस 0;
पूर्ण

अटल काष्ठा resource eisa_root_res = अणु
	.name  = "EISA root resource",
	.start = 0,
	.end   = 0xffffffff,
	.flags = IORESOURCE_IO,
पूर्ण;

अटल पूर्णांक eisa_bus_count;

पूर्णांक __init eisa_root_रेजिस्टर(काष्ठा eisa_root_device *root)
अणु
	पूर्णांक err;

	/* Use our own resources to check अगर this bus base address has
	 * been alपढ़ोy रेजिस्टरed. This prevents the भव root
	 * device from रेजिस्टरing after the real one has, क्रम
	 * example... */

	root->eisa_root_res.name  = eisa_root_res.name;
	root->eisa_root_res.start = root->res->start;
	root->eisa_root_res.end   = root->res->end;
	root->eisa_root_res.flags = IORESOURCE_BUSY;

	err = request_resource(&eisa_root_res, &root->eisa_root_res);
	अगर (err)
		वापस err;

	root->bus_nr = eisa_bus_count++;

	err = eisa_probe(root);
	अगर (err)
		release_resource(&root->eisa_root_res);

	वापस err;
पूर्ण

अटल पूर्णांक __init eisa_init(व्योम)
अणु
	पूर्णांक r;

	r = bus_रेजिस्टर(&eisa_bus_type);
	अगर (r)
		वापस r;

	prपूर्णांकk(KERN_INFO "EISA bus registered\n");
	वापस 0;
पूर्ण

module_param_array(enable_dev, पूर्णांक, &enable_dev_count, 0444);
module_param_array(disable_dev, पूर्णांक, &disable_dev_count, 0444);

postcore_initcall(eisa_init);

पूर्णांक EISA_bus;		/* क्रम legacy drivers */
EXPORT_SYMBOL(EISA_bus);
