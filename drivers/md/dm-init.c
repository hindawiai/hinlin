<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 * dm-init.c
 * Copyright (C) 2017 The Chromium OS Authors <chromium-os-dev@chromium.org>
 *
 * This file is released under the GPLv2.
 */

#समावेश <linux/प्रकार.स>
#समावेश <linux/device.h>
#समावेश <linux/device-mapper.h>
#समावेश <linux/init.h>
#समावेश <linux/list.h>
#समावेश <linux/moduleparam.h>

#घोषणा DM_MSG_PREFIX "init"
#घोषणा DM_MAX_DEVICES 256
#घोषणा DM_MAX_TARGETS 256
#घोषणा DM_MAX_STR_SIZE 4096

अटल अक्षर *create;

/*
 * Format: dm-mod.create=<name>,<uuid>,<minor>,<flags>,<table>[,<table>+][;<name>,<uuid>,<minor>,<flags>,<table>[,<table>+]+]
 * Table क्रमmat: <start_sector> <num_sectors> <target_type> <target_args>
 *
 * See Documentation/admin-guide/device-mapper/dm-init.rst क्रम dm-mod.create="..." क्रमmat
 * details.
 */

काष्ठा dm_device अणु
	काष्ठा dm_ioctl dmi;
	काष्ठा dm_target_spec *table[DM_MAX_TARGETS];
	अक्षर *target_args_array[DM_MAX_TARGETS];
	काष्ठा list_head list;
पूर्ण;

अटल स्थिर अक्षर * स्थिर dm_allowed_tarमाला_लो[] __initस्थिर = अणु
	"crypt",
	"delay",
	"linear",
	"snapshot-origin",
	"striped",
	"verity",
पूर्ण;

अटल पूर्णांक __init dm_verअगरy_target_type(स्थिर अक्षर *target)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(dm_allowed_tarमाला_लो); i++) अणु
		अगर (!म_भेद(dm_allowed_tarमाला_लो[i], target))
			वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल व्योम __init dm_setup_cleanup(काष्ठा list_head *devices)
अणु
	काष्ठा dm_device *dev, *पंचांगp;
	अचिन्हित पूर्णांक i;

	list_क्रम_each_entry_safe(dev, पंचांगp, devices, list) अणु
		list_del(&dev->list);
		क्रम (i = 0; i < dev->dmi.target_count; i++) अणु
			kमुक्त(dev->table[i]);
			kमुक्त(dev->target_args_array[i]);
		पूर्ण
		kमुक्त(dev);
	पूर्ण
पूर्ण

/**
 * str_field_delimit - delimit a string based on a separator अक्षर.
 * @str: the poपूर्णांकer to the string to delimit.
 * @separator: अक्षर that delimits the field
 *
 * Find a @separator and replace it by '\0'.
 * Remove leading and trailing spaces.
 * Return the reमुख्यder string after the @separator.
 */
अटल अक्षर __init *str_field_delimit(अक्षर **str, अक्षर separator)
अणु
	अक्षर *s;

	/* TODO: add support क्रम escaped अक्षरacters */
	*str = skip_spaces(*str);
	s = म_अक्षर(*str, separator);
	/* Delimit the field and हटाओ trailing spaces */
	अगर (s)
		*s = '\0';
	*str = strim(*str);
	वापस s ? ++s : शून्य;
पूर्ण

/**
 * dm_parse_table_entry - parse a table entry
 * @dev: device to store the parsed inक्रमmation.
 * @str: the poपूर्णांकer to a string with the क्रमmat:
 *	<start_sector> <num_sectors> <target_type> <target_args>[, ...]
 *
 * Return the reमुख्यder string after the table entry, i.e, after the comma which
 * delimits the entry or शून्य अगर reached the end of the string.
 */
अटल अक्षर __init *dm_parse_table_entry(काष्ठा dm_device *dev, अक्षर *str)
अणु
	स्थिर अचिन्हित पूर्णांक n = dev->dmi.target_count - 1;
	काष्ठा dm_target_spec *sp;
	अचिन्हित पूर्णांक i;
	/* fields:  */
	अक्षर *field[4];
	अक्षर *next;

	field[0] = str;
	/* Delimit first 3 fields that are separated by space */
	क्रम (i = 0; i < ARRAY_SIZE(field) - 1; i++) अणु
		field[i + 1] = str_field_delimit(&field[i], ' ');
		अगर (!field[i + 1])
			वापस ERR_PTR(-EINVAL);
	पूर्ण
	/* Delimit last field that can be terminated by comma */
	next = str_field_delimit(&field[i], ',');

	sp = kzalloc(माप(*sp), GFP_KERNEL);
	अगर (!sp)
		वापस ERR_PTR(-ENOMEM);
	dev->table[n] = sp;

	/* start_sector */
	अगर (kम_से_अदीर्घl(field[0], 0, &sp->sector_start))
		वापस ERR_PTR(-EINVAL);
	/* num_sector */
	अगर (kम_से_अदीर्घl(field[1], 0, &sp->length))
		वापस ERR_PTR(-EINVAL);
	/* target_type */
	strscpy(sp->target_type, field[2], माप(sp->target_type));
	अगर (dm_verअगरy_target_type(sp->target_type)) अणु
		DMERR("invalid type \"%s\"", sp->target_type);
		वापस ERR_PTR(-EINVAL);
	पूर्ण
	/* target_args */
	dev->target_args_array[n] = kstrndup(field[3], DM_MAX_STR_SIZE,
					     GFP_KERNEL);
	अगर (!dev->target_args_array[n])
		वापस ERR_PTR(-ENOMEM);

	वापस next;
पूर्ण

/**
 * dm_parse_table - parse "dm-mod.create=" table field
 * @dev: device to store the parsed inक्रमmation.
 * @str: the poपूर्णांकer to a string with the क्रमmat:
 *	<table>[,<table>+]
 */
अटल पूर्णांक __init dm_parse_table(काष्ठा dm_device *dev, अक्षर *str)
अणु
	अक्षर *table_entry = str;

	जबतक (table_entry) अणु
		DMDEBUG("parsing table \"%s\"", str);
		अगर (++dev->dmi.target_count > DM_MAX_TARGETS) अणु
			DMERR("too many targets %u > %d",
			      dev->dmi.target_count, DM_MAX_TARGETS);
			वापस -EINVAL;
		पूर्ण
		table_entry = dm_parse_table_entry(dev, table_entry);
		अगर (IS_ERR(table_entry)) अणु
			DMERR("couldn't parse table");
			वापस PTR_ERR(table_entry);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * dm_parse_device_entry - parse a device entry
 * @dev: device to store the parsed inक्रमmation.
 * @str: the poपूर्णांकer to a string with the क्रमmat:
 *	name,uuid,minor,flags,table[; ...]
 *
 * Return the reमुख्यder string after the table entry, i.e, after the semi-colon
 * which delimits the entry or शून्य अगर reached the end of the string.
 */
अटल अक्षर __init *dm_parse_device_entry(काष्ठा dm_device *dev, अक्षर *str)
अणु
	/* There are 5 fields: name,uuid,minor,flags,table; */
	अक्षर *field[5];
	अचिन्हित पूर्णांक i;
	अक्षर *next;

	field[0] = str;
	/* Delimit first 4 fields that are separated by comma */
	क्रम (i = 0; i < ARRAY_SIZE(field) - 1; i++) अणु
		field[i+1] = str_field_delimit(&field[i], ',');
		अगर (!field[i+1])
			वापस ERR_PTR(-EINVAL);
	पूर्ण
	/* Delimit last field that can be delimited by semi-colon */
	next = str_field_delimit(&field[i], ';');

	/* name */
	strscpy(dev->dmi.name, field[0], माप(dev->dmi.name));
	/* uuid */
	strscpy(dev->dmi.uuid, field[1], माप(dev->dmi.uuid));
	/* minor */
	अगर (म_माप(field[2])) अणु
		अगर (kम_से_अदीर्घl(field[2], 0, &dev->dmi.dev))
			वापस ERR_PTR(-EINVAL);
		dev->dmi.flags |= DM_PERSISTENT_DEV_FLAG;
	पूर्ण
	/* flags */
	अगर (!म_भेद(field[3], "ro"))
		dev->dmi.flags |= DM_READONLY_FLAG;
	अन्यथा अगर (म_भेद(field[3], "rw"))
		वापस ERR_PTR(-EINVAL);
	/* table */
	अगर (dm_parse_table(dev, field[4]))
		वापस ERR_PTR(-EINVAL);

	वापस next;
पूर्ण

/**
 * dm_parse_devices - parse "dm-mod.create=" argument
 * @devices: list of काष्ठा dm_device to store the parsed inक्रमmation.
 * @str: the poपूर्णांकer to a string with the क्रमmat:
 *	<device>[;<device>+]
 */
अटल पूर्णांक __init dm_parse_devices(काष्ठा list_head *devices, अक्षर *str)
अणु
	अचिन्हित दीर्घ ndev = 0;
	काष्ठा dm_device *dev;
	अक्षर *device = str;

	DMDEBUG("parsing \"%s\"", str);
	जबतक (device) अणु
		dev = kzalloc(माप(*dev), GFP_KERNEL);
		अगर (!dev)
			वापस -ENOMEM;
		list_add_tail(&dev->list, devices);

		अगर (++ndev > DM_MAX_DEVICES) अणु
			DMERR("too many devices %lu > %d",
			      ndev, DM_MAX_DEVICES);
			वापस -EINVAL;
		पूर्ण

		device = dm_parse_device_entry(dev, device);
		अगर (IS_ERR(device)) अणु
			DMERR("couldn't parse device");
			वापस PTR_ERR(device);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * dm_init_init - parse "dm-mod.create=" argument and configure drivers
 */
अटल पूर्णांक __init dm_init_init(व्योम)
अणु
	काष्ठा dm_device *dev;
	LIST_HEAD(devices);
	अक्षर *str;
	पूर्णांक r;

	अगर (!create)
		वापस 0;

	अगर (म_माप(create) >= DM_MAX_STR_SIZE) अणु
		DMERR("Argument is too big. Limit is %d", DM_MAX_STR_SIZE);
		वापस -EINVAL;
	पूर्ण
	str = kstrndup(create, DM_MAX_STR_SIZE, GFP_KERNEL);
	अगर (!str)
		वापस -ENOMEM;

	r = dm_parse_devices(&devices, str);
	अगर (r)
		जाओ out;

	DMINFO("waiting for all devices to be available before creating mapped devices");
	रुको_क्रम_device_probe();

	list_क्रम_each_entry(dev, &devices, list) अणु
		अगर (dm_early_create(&dev->dmi, dev->table,
				    dev->target_args_array))
			अवरोध;
	पूर्ण
out:
	kमुक्त(str);
	dm_setup_cleanup(&devices);
	वापस r;
पूर्ण

late_initcall(dm_init_init);

module_param(create, अक्षरp, 0);
MODULE_PARM_DESC(create, "Create a mapped device in early boot");
