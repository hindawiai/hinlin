<शैली गुरु>
// SPDX--License-Identअगरier: GPL-2.0

#समावेश <यंत्र/platक्रमm_early.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/pm.h>

अटल __initdata LIST_HEAD(sh_early_platक्रमm_driver_list);
अटल __initdata LIST_HEAD(sh_early_platक्रमm_device_list);

अटल स्थिर काष्ठा platक्रमm_device_id *
platक्रमm_match_id(स्थिर काष्ठा platक्रमm_device_id *id,
		  काष्ठा platक्रमm_device *pdev)
अणु
	जबतक (id->name[0]) अणु
		अगर (म_भेद(pdev->name, id->name) == 0) अणु
			pdev->id_entry = id;
			वापस id;
		पूर्ण
		id++;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक platक्रमm_match(काष्ठा device *dev, काष्ठा device_driver *drv)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा platक्रमm_driver *pdrv = to_platक्रमm_driver(drv);

	/* When driver_override is set, only bind to the matching driver */
	अगर (pdev->driver_override)
		वापस !म_भेद(pdev->driver_override, drv->name);

	/* Then try to match against the id table */
	अगर (pdrv->id_table)
		वापस platक्रमm_match_id(pdrv->id_table, pdev) != शून्य;

	/* fall-back to driver name match */
	वापस (म_भेद(pdev->name, drv->name) == 0);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल व्योम device_pm_init_common(काष्ठा device *dev)
अणु
	अगर (!dev->घातer.early_init) अणु
		spin_lock_init(&dev->घातer.lock);
		dev->घातer.qos = शून्य;
		dev->घातer.early_init = true;
	पूर्ण
पूर्ण

अटल व्योम pm_runसमय_early_init(काष्ठा device *dev)
अणु
	dev->घातer.disable_depth = 1;
	device_pm_init_common(dev);
पूर्ण
#अन्यथा
अटल व्योम pm_runसमय_early_init(काष्ठा device *dev) अणुपूर्ण
#पूर्ण_अगर

/**
 * sh_early_platक्रमm_driver_रेजिस्टर - रेजिस्टर early platक्रमm driver
 * @epdrv: sh_early_platक्रमm driver काष्ठाure
 * @buf: string passed from early_param()
 *
 * Helper function क्रम sh_early_platक्रमm_init() / sh_early_platक्रमm_init_buffer()
 */
पूर्णांक __init sh_early_platक्रमm_driver_रेजिस्टर(काष्ठा sh_early_platक्रमm_driver *epdrv,
					  अक्षर *buf)
अणु
	अक्षर *पंचांगp;
	पूर्णांक n;

	/* Simply add the driver to the end of the global list.
	 * Drivers will by शेष be put on the list in compiled-in order.
	 */
	अगर (!epdrv->list.next) अणु
		INIT_LIST_HEAD(&epdrv->list);
		list_add_tail(&epdrv->list, &sh_early_platक्रमm_driver_list);
	पूर्ण

	/* If the user has specअगरied device then make sure the driver
	 * माला_लो prioritized. The driver of the last device specअगरied on
	 * command line will be put first on the list.
	 */
	n = म_माप(epdrv->pdrv->driver.name);
	अगर (buf && !म_भेदन(buf, epdrv->pdrv->driver.name, n)) अणु
		list_move(&epdrv->list, &sh_early_platक्रमm_driver_list);

		/* Allow passing parameters after device name */
		अगर (buf[n] == '\0' || buf[n] == ',')
			epdrv->requested_id = -1;
		अन्यथा अणु
			epdrv->requested_id = simple_म_से_अदीर्घ(&buf[n + 1],
							     &पंचांगp, 10);

			अगर (buf[n] != '.' || (पंचांगp == &buf[n + 1])) अणु
				epdrv->requested_id = EARLY_PLATFORM_ID_ERROR;
				n = 0;
			पूर्ण अन्यथा
				n += म_खोज(&buf[n + 1], ",") + 1;
		पूर्ण

		अगर (buf[n] == ',')
			n++;

		अगर (epdrv->bufsize) अणु
			स_नकल(epdrv->buffer, &buf[n],
			       min_t(पूर्णांक, epdrv->bufsize, म_माप(&buf[n]) + 1));
			epdrv->buffer[epdrv->bufsize - 1] = '\0';
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * sh_early_platक्रमm_add_devices - adds a number of early platक्रमm devices
 * @devs: array of early platक्रमm devices to add
 * @num: number of early platक्रमm devices in array
 *
 * Used by early architecture code to रेजिस्टर early platक्रमm devices and
 * their platक्रमm data.
 */
व्योम __init sh_early_platक्रमm_add_devices(काष्ठा platक्रमm_device **devs, पूर्णांक num)
अणु
	काष्ठा device *dev;
	पूर्णांक i;

	/* simply add the devices to list */
	क्रम (i = 0; i < num; i++) अणु
		dev = &devs[i]->dev;

		अगर (!dev->devres_head.next) अणु
			pm_runसमय_early_init(dev);
			INIT_LIST_HEAD(&dev->devres_head);
			list_add_tail(&dev->devres_head,
				      &sh_early_platक्रमm_device_list);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * sh_early_platक्रमm_driver_रेजिस्टर_all - रेजिस्टर early platक्रमm drivers
 * @class_str: string to identअगरy early platक्रमm driver class
 *
 * Used by architecture code to रेजिस्टर all early platक्रमm drivers
 * क्रम a certain class. If omitted then only early platक्रमm drivers
 * with matching kernel command line class parameters will be रेजिस्टरed.
 */
व्योम __init sh_early_platक्रमm_driver_रेजिस्टर_all(अक्षर *class_str)
अणु
	/* The "class_str" parameter may or may not be present on the kernel
	 * command line. If it is present then there may be more than one
	 * matching parameter.
	 *
	 * Since we रेजिस्टर our early platक्रमm drivers using early_param()
	 * we need to make sure that they also get रेजिस्टरed in the हाल
	 * when the parameter is missing from the kernel command line.
	 *
	 * We use parse_early_options() to make sure the early_param() माला_लो
	 * called at least once. The early_param() may be called more than
	 * once since the name of the preferred device may be specअगरied on
	 * the kernel command line. sh_early_platक्रमm_driver_रेजिस्टर() handles
	 * this हाल क्रम us.
	 */
	parse_early_options(class_str);
पूर्ण

/**
 * sh_early_platक्रमm_match - find early platक्रमm device matching driver
 * @epdrv: early platक्रमm driver काष्ठाure
 * @id: id to match against
 */
अटल काष्ठा platक्रमm_device * __init
sh_early_platक्रमm_match(काष्ठा sh_early_platक्रमm_driver *epdrv, पूर्णांक id)
अणु
	काष्ठा platक्रमm_device *pd;

	list_क्रम_each_entry(pd, &sh_early_platक्रमm_device_list, dev.devres_head)
		अगर (platक्रमm_match(&pd->dev, &epdrv->pdrv->driver))
			अगर (pd->id == id)
				वापस pd;

	वापस शून्य;
पूर्ण

/**
 * sh_early_platक्रमm_left - check अगर early platक्रमm driver has matching devices
 * @epdrv: early platक्रमm driver काष्ठाure
 * @id: वापस true अगर id or above exists
 */
अटल पूर्णांक __init sh_early_platक्रमm_left(काष्ठा sh_early_platक्रमm_driver *epdrv,
				       पूर्णांक id)
अणु
	काष्ठा platक्रमm_device *pd;

	list_क्रम_each_entry(pd, &sh_early_platक्रमm_device_list, dev.devres_head)
		अगर (platक्रमm_match(&pd->dev, &epdrv->pdrv->driver))
			अगर (pd->id >= id)
				वापस 1;

	वापस 0;
पूर्ण

/**
 * sh_early_platक्रमm_driver_probe_id - probe drivers matching class_str and id
 * @class_str: string to identअगरy early platक्रमm driver class
 * @id: id to match against
 * @nr_probe: number of platक्रमm devices to successfully probe beक्रमe निकासing
 */
अटल पूर्णांक __init sh_early_platक्रमm_driver_probe_id(अक्षर *class_str,
						 पूर्णांक id,
						 पूर्णांक nr_probe)
अणु
	काष्ठा sh_early_platक्रमm_driver *epdrv;
	काष्ठा platक्रमm_device *match;
	पूर्णांक match_id;
	पूर्णांक n = 0;
	पूर्णांक left = 0;

	list_क्रम_each_entry(epdrv, &sh_early_platक्रमm_driver_list, list) अणु
		/* only use drivers matching our class_str */
		अगर (म_भेद(class_str, epdrv->class_str))
			जारी;

		अगर (id == -2) अणु
			match_id = epdrv->requested_id;
			left = 1;

		पूर्ण अन्यथा अणु
			match_id = id;
			left += sh_early_platक्रमm_left(epdrv, id);

			/* skip requested id */
			चयन (epdrv->requested_id) अणु
			हाल EARLY_PLATFORM_ID_ERROR:
			हाल EARLY_PLATFORM_ID_UNSET:
				अवरोध;
			शेष:
				अगर (epdrv->requested_id == id)
					match_id = EARLY_PLATFORM_ID_UNSET;
			पूर्ण
		पूर्ण

		चयन (match_id) अणु
		हाल EARLY_PLATFORM_ID_ERROR:
			pr_warn("%s: unable to parse %s parameter\n",
				class_str, epdrv->pdrv->driver.name);
			fallthrough;
		हाल EARLY_PLATFORM_ID_UNSET:
			match = शून्य;
			अवरोध;
		शेष:
			match = sh_early_platक्रमm_match(epdrv, match_id);
		पूर्ण

		अगर (match) अणु
			/*
			 * Set up a sensible init_name to enable
			 * dev_name() and others to be used beक्रमe the
			 * rest of the driver core is initialized.
			 */
			अगर (!match->dev.init_name && slab_is_available()) अणु
				अगर (match->id != -1)
					match->dev.init_name =
						kaप्र_लिखो(GFP_KERNEL, "%s.%d",
							  match->name,
							  match->id);
				अन्यथा
					match->dev.init_name =
						kaप्र_लिखो(GFP_KERNEL, "%s",
							  match->name);

				अगर (!match->dev.init_name)
					वापस -ENOMEM;
			पूर्ण

			अगर (epdrv->pdrv->probe(match))
				pr_warn("%s: unable to probe %s early.\n",
					class_str, match->name);
			अन्यथा
				n++;
		पूर्ण

		अगर (n >= nr_probe)
			अवरोध;
	पूर्ण

	अगर (left)
		वापस n;
	अन्यथा
		वापस -ENODEV;
पूर्ण

/**
 * sh_early_platक्रमm_driver_probe - probe a class of रेजिस्टरed drivers
 * @class_str: string to identअगरy early platक्रमm driver class
 * @nr_probe: number of platक्रमm devices to successfully probe beक्रमe निकासing
 * @user_only: only probe user specअगरied early platक्रमm devices
 *
 * Used by architecture code to probe रेजिस्टरed early platक्रमm drivers
 * within a certain class. For probe to happen a रेजिस्टरed early platक्रमm
 * device matching a रेजिस्टरed early platक्रमm driver is needed.
 */
पूर्णांक __init sh_early_platक्रमm_driver_probe(अक्षर *class_str,
				       पूर्णांक nr_probe,
				       पूर्णांक user_only)
अणु
	पूर्णांक k, n, i;

	n = 0;
	क्रम (i = -2; n < nr_probe; i++) अणु
		k = sh_early_platक्रमm_driver_probe_id(class_str, i, nr_probe - n);

		अगर (k < 0)
			अवरोध;

		n += k;

		अगर (user_only)
			अवरोध;
	पूर्ण

	वापस n;
पूर्ण

/**
 * early_platक्रमm_cleanup - clean up early platक्रमm code
 */
व्योम __init early_platक्रमm_cleanup(व्योम)
अणु
	काष्ठा platक्रमm_device *pd, *pd2;

	/* clean up the devres list used to chain devices */
	list_क्रम_each_entry_safe(pd, pd2, &sh_early_platक्रमm_device_list,
				 dev.devres_head) अणु
		list_del(&pd->dev.devres_head);
		स_रखो(&pd->dev.devres_head, 0, माप(pd->dev.devres_head));
	पूर्ण
पूर्ण
