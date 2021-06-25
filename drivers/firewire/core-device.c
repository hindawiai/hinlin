<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Device probing and sysfs code.
 *
 * Copyright (C) 2005-2006  Kristian Hoegsberg <krh@bitplanet.net>
 */

#समावेश <linux/bug.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/firewire.h>
#समावेश <linux/firewire-स्थिरants.h>
#समावेश <linux/idr.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kobject.h>
#समावेश <linux/list.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/माला.स>
#समावेश <linux/workqueue.h>

#समावेश <linux/atomic.h>
#समावेश <यंत्र/byteorder.h>

#समावेश "core.h"

व्योम fw_csr_iterator_init(काष्ठा fw_csr_iterator *ci, स्थिर u32 *p)
अणु
	ci->p = p + 1;
	ci->end = ci->p + (p[0] >> 16);
पूर्ण
EXPORT_SYMBOL(fw_csr_iterator_init);

पूर्णांक fw_csr_iterator_next(काष्ठा fw_csr_iterator *ci, पूर्णांक *key, पूर्णांक *value)
अणु
	*key = *ci->p >> 24;
	*value = *ci->p & 0xffffff;

	वापस ci->p++ < ci->end;
पूर्ण
EXPORT_SYMBOL(fw_csr_iterator_next);

अटल स्थिर u32 *search_leaf(स्थिर u32 *directory, पूर्णांक search_key)
अणु
	काष्ठा fw_csr_iterator ci;
	पूर्णांक last_key = 0, key, value;

	fw_csr_iterator_init(&ci, directory);
	जबतक (fw_csr_iterator_next(&ci, &key, &value)) अणु
		अगर (last_key == search_key &&
		    key == (CSR_DESCRIPTOR | CSR_LEAF))
			वापस ci.p - 1 + value;

		last_key = key;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक textual_leaf_to_string(स्थिर u32 *block, अक्षर *buf, माप_प्रकार size)
अणु
	अचिन्हित पूर्णांक quadlets, i;
	अक्षर c;

	अगर (!size || !buf)
		वापस -EINVAL;

	quadlets = min(block[0] >> 16, 256U);
	अगर (quadlets < 2)
		वापस -ENODATA;

	अगर (block[1] != 0 || block[2] != 0)
		/* unknown language/अक्षरacter set */
		वापस -ENODATA;

	block += 3;
	quadlets -= 2;
	क्रम (i = 0; i < quadlets * 4 && i < size - 1; i++) अणु
		c = block[i / 4] >> (24 - 8 * (i % 4));
		अगर (c == '\0')
			अवरोध;
		buf[i] = c;
	पूर्ण
	buf[i] = '\0';

	वापस i;
पूर्ण

/**
 * fw_csr_string() - पढ़ोs a string from the configuration ROM
 * @directory:	e.g. root directory or unit directory
 * @key:	the key of the preceding directory entry
 * @buf:	where to put the string
 * @size:	size of @buf, in bytes
 *
 * The string is taken from a minimal ASCII text descriptor leaf after
 * the immediate entry with @key.  The string is zero-terminated.
 * An overदीर्घ string is silently truncated such that it and the
 * zero byte fit पूर्णांकo @size.
 *
 * Returns म_माप(buf) or a negative error code.
 */
पूर्णांक fw_csr_string(स्थिर u32 *directory, पूर्णांक key, अक्षर *buf, माप_प्रकार size)
अणु
	स्थिर u32 *leaf = search_leaf(directory, key);
	अगर (!leaf)
		वापस -ENOENT;

	वापस textual_leaf_to_string(leaf, buf, size);
पूर्ण
EXPORT_SYMBOL(fw_csr_string);

अटल व्योम get_ids(स्थिर u32 *directory, पूर्णांक *id)
अणु
	काष्ठा fw_csr_iterator ci;
	पूर्णांक key, value;

	fw_csr_iterator_init(&ci, directory);
	जबतक (fw_csr_iterator_next(&ci, &key, &value)) अणु
		चयन (key) अणु
		हाल CSR_VENDOR:	id[0] = value; अवरोध;
		हाल CSR_MODEL:		id[1] = value; अवरोध;
		हाल CSR_SPECIFIER_ID:	id[2] = value; अवरोध;
		हाल CSR_VERSION:	id[3] = value; अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम get_modalias_ids(काष्ठा fw_unit *unit, पूर्णांक *id)
अणु
	get_ids(&fw_parent_device(unit)->config_rom[5], id);
	get_ids(unit->directory, id);
पूर्ण

अटल bool match_ids(स्थिर काष्ठा ieee1394_device_id *id_table, पूर्णांक *id)
अणु
	पूर्णांक match = 0;

	अगर (id[0] == id_table->venकरोr_id)
		match |= IEEE1394_MATCH_VENDOR_ID;
	अगर (id[1] == id_table->model_id)
		match |= IEEE1394_MATCH_MODEL_ID;
	अगर (id[2] == id_table->specअगरier_id)
		match |= IEEE1394_MATCH_SPECIFIER_ID;
	अगर (id[3] == id_table->version)
		match |= IEEE1394_MATCH_VERSION;

	वापस (match & id_table->match_flags) == id_table->match_flags;
पूर्ण

अटल स्थिर काष्ठा ieee1394_device_id *unit_match(काष्ठा device *dev,
						   काष्ठा device_driver *drv)
अणु
	स्थिर काष्ठा ieee1394_device_id *id_table =
			container_of(drv, काष्ठा fw_driver, driver)->id_table;
	पूर्णांक id[] = अणु0, 0, 0, 0पूर्ण;

	get_modalias_ids(fw_unit(dev), id);

	क्रम (; id_table->match_flags != 0; id_table++)
		अगर (match_ids(id_table, id))
			वापस id_table;

	वापस शून्य;
पूर्ण

अटल bool is_fw_unit(काष्ठा device *dev);

अटल पूर्णांक fw_unit_match(काष्ठा device *dev, काष्ठा device_driver *drv)
अणु
	/* We only allow binding to fw_units. */
	वापस is_fw_unit(dev) && unit_match(dev, drv) != शून्य;
पूर्ण

अटल पूर्णांक fw_unit_probe(काष्ठा device *dev)
अणु
	काष्ठा fw_driver *driver =
			container_of(dev->driver, काष्ठा fw_driver, driver);

	वापस driver->probe(fw_unit(dev), unit_match(dev, dev->driver));
पूर्ण

अटल पूर्णांक fw_unit_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा fw_driver *driver =
			container_of(dev->driver, काष्ठा fw_driver, driver);

	driver->हटाओ(fw_unit(dev));

	वापस 0;
पूर्ण

अटल पूर्णांक get_modalias(काष्ठा fw_unit *unit, अक्षर *buffer, माप_प्रकार buffer_size)
अणु
	पूर्णांक id[] = अणु0, 0, 0, 0पूर्ण;

	get_modalias_ids(unit, id);

	वापस snम_लिखो(buffer, buffer_size,
			"ieee1394:ven%08Xmo%08Xsp%08Xver%08X",
			id[0], id[1], id[2], id[3]);
पूर्ण

अटल पूर्णांक fw_unit_uevent(काष्ठा device *dev, काष्ठा kobj_uevent_env *env)
अणु
	काष्ठा fw_unit *unit = fw_unit(dev);
	अक्षर modalias[64];

	get_modalias(unit, modalias, माप(modalias));

	अगर (add_uevent_var(env, "MODALIAS=%s", modalias))
		वापस -ENOMEM;

	वापस 0;
पूर्ण

काष्ठा bus_type fw_bus_type = अणु
	.name = "firewire",
	.match = fw_unit_match,
	.probe = fw_unit_probe,
	.हटाओ = fw_unit_हटाओ,
पूर्ण;
EXPORT_SYMBOL(fw_bus_type);

पूर्णांक fw_device_enable_phys_dma(काष्ठा fw_device *device)
अणु
	पूर्णांक generation = device->generation;

	/* device->node_id, accessed below, must not be older than generation */
	smp_rmb();

	वापस device->card->driver->enable_phys_dma(device->card,
						     device->node_id,
						     generation);
पूर्ण
EXPORT_SYMBOL(fw_device_enable_phys_dma);

काष्ठा config_rom_attribute अणु
	काष्ठा device_attribute attr;
	u32 key;
पूर्ण;

अटल sमाप_प्रकार show_immediate(काष्ठा device *dev,
			      काष्ठा device_attribute *dattr, अक्षर *buf)
अणु
	काष्ठा config_rom_attribute *attr =
		container_of(dattr, काष्ठा config_rom_attribute, attr);
	काष्ठा fw_csr_iterator ci;
	स्थिर u32 *dir;
	पूर्णांक key, value, ret = -ENOENT;

	करोwn_पढ़ो(&fw_device_rwsem);

	अगर (is_fw_unit(dev))
		dir = fw_unit(dev)->directory;
	अन्यथा
		dir = fw_device(dev)->config_rom + 5;

	fw_csr_iterator_init(&ci, dir);
	जबतक (fw_csr_iterator_next(&ci, &key, &value))
		अगर (attr->key == key) अणु
			ret = snम_लिखो(buf, buf ? PAGE_SIZE : 0,
				       "0x%06x\n", value);
			अवरोध;
		पूर्ण

	up_पढ़ो(&fw_device_rwsem);

	वापस ret;
पूर्ण

#घोषणा IMMEDIATE_ATTR(name, key)				\
	अणु __ATTR(name, S_IRUGO, show_immediate, शून्य), key पूर्ण

अटल sमाप_प्रकार show_text_leaf(काष्ठा device *dev,
			      काष्ठा device_attribute *dattr, अक्षर *buf)
अणु
	काष्ठा config_rom_attribute *attr =
		container_of(dattr, काष्ठा config_rom_attribute, attr);
	स्थिर u32 *dir;
	माप_प्रकार bufsize;
	अक्षर dummy_buf[2];
	पूर्णांक ret;

	करोwn_पढ़ो(&fw_device_rwsem);

	अगर (is_fw_unit(dev))
		dir = fw_unit(dev)->directory;
	अन्यथा
		dir = fw_device(dev)->config_rom + 5;

	अगर (buf) अणु
		bufsize = PAGE_SIZE - 1;
	पूर्ण अन्यथा अणु
		buf = dummy_buf;
		bufsize = 1;
	पूर्ण

	ret = fw_csr_string(dir, attr->key, buf, bufsize);

	अगर (ret >= 0) अणु
		/* Strip trailing whitespace and add newline. */
		जबतक (ret > 0 && है_खाली(buf[ret - 1]))
			ret--;
		म_नकल(buf + ret, "\n");
		ret++;
	पूर्ण

	up_पढ़ो(&fw_device_rwsem);

	वापस ret;
पूर्ण

#घोषणा TEXT_LEAF_ATTR(name, key)				\
	अणु __ATTR(name, S_IRUGO, show_text_leaf, शून्य), key पूर्ण

अटल काष्ठा config_rom_attribute config_rom_attributes[] = अणु
	IMMEDIATE_ATTR(venकरोr, CSR_VENDOR),
	IMMEDIATE_ATTR(hardware_version, CSR_HARDWARE_VERSION),
	IMMEDIATE_ATTR(specअगरier_id, CSR_SPECIFIER_ID),
	IMMEDIATE_ATTR(version, CSR_VERSION),
	IMMEDIATE_ATTR(model, CSR_MODEL),
	TEXT_LEAF_ATTR(venकरोr_name, CSR_VENDOR),
	TEXT_LEAF_ATTR(model_name, CSR_MODEL),
	TEXT_LEAF_ATTR(hardware_version_name, CSR_HARDWARE_VERSION),
पूर्ण;

अटल व्योम init_fw_attribute_group(काष्ठा device *dev,
				    काष्ठा device_attribute *attrs,
				    काष्ठा fw_attribute_group *group)
अणु
	काष्ठा device_attribute *attr;
	पूर्णांक i, j;

	क्रम (j = 0; attrs[j].attr.name != शून्य; j++)
		group->attrs[j] = &attrs[j].attr;

	क्रम (i = 0; i < ARRAY_SIZE(config_rom_attributes); i++) अणु
		attr = &config_rom_attributes[i].attr;
		अगर (attr->show(dev, attr, शून्य) < 0)
			जारी;
		group->attrs[j++] = &attr->attr;
	पूर्ण

	group->attrs[j] = शून्य;
	group->groups[0] = &group->group;
	group->groups[1] = शून्य;
	group->group.attrs = group->attrs;
	dev->groups = (स्थिर काष्ठा attribute_group **) group->groups;
पूर्ण

अटल sमाप_प्रकार modalias_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा fw_unit *unit = fw_unit(dev);
	पूर्णांक length;

	length = get_modalias(unit, buf, PAGE_SIZE);
	म_नकल(buf + length, "\n");

	वापस length + 1;
पूर्ण

अटल sमाप_प्रकार rom_index_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा fw_device *device = fw_device(dev->parent);
	काष्ठा fw_unit *unit = fw_unit(dev);

	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n",
			(पूर्णांक)(unit->directory - device->config_rom));
पूर्ण

अटल काष्ठा device_attribute fw_unit_attributes[] = अणु
	__ATTR_RO(modalias),
	__ATTR_RO(rom_index),
	__ATTR_शून्य,
पूर्ण;

अटल sमाप_प्रकार config_rom_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा fw_device *device = fw_device(dev);
	माप_प्रकार length;

	करोwn_पढ़ो(&fw_device_rwsem);
	length = device->config_rom_length * 4;
	स_नकल(buf, device->config_rom, length);
	up_पढ़ो(&fw_device_rwsem);

	वापस length;
पूर्ण

अटल sमाप_प्रकार guid_show(काष्ठा device *dev,
			 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा fw_device *device = fw_device(dev);
	पूर्णांक ret;

	करोwn_पढ़ो(&fw_device_rwsem);
	ret = snम_लिखो(buf, PAGE_SIZE, "0x%08x%08x\n",
		       device->config_rom[3], device->config_rom[4]);
	up_पढ़ो(&fw_device_rwsem);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार is_local_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा fw_device *device = fw_device(dev);

	वापस प्र_लिखो(buf, "%u\n", device->is_local);
पूर्ण

अटल पूर्णांक units_प्र_लिखो(अक्षर *buf, स्थिर u32 *directory)
अणु
	काष्ठा fw_csr_iterator ci;
	पूर्णांक key, value;
	पूर्णांक specअगरier_id = 0;
	पूर्णांक version = 0;

	fw_csr_iterator_init(&ci, directory);
	जबतक (fw_csr_iterator_next(&ci, &key, &value)) अणु
		चयन (key) अणु
		हाल CSR_SPECIFIER_ID:
			specअगरier_id = value;
			अवरोध;
		हाल CSR_VERSION:
			version = value;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस प्र_लिखो(buf, "0x%06x:0x%06x ", specअगरier_id, version);
पूर्ण

अटल sमाप_प्रकार units_show(काष्ठा device *dev,
			  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा fw_device *device = fw_device(dev);
	काष्ठा fw_csr_iterator ci;
	पूर्णांक key, value, i = 0;

	करोwn_पढ़ो(&fw_device_rwsem);
	fw_csr_iterator_init(&ci, &device->config_rom[5]);
	जबतक (fw_csr_iterator_next(&ci, &key, &value)) अणु
		अगर (key != (CSR_UNIT | CSR_सूचीECTORY))
			जारी;
		i += units_प्र_लिखो(&buf[i], ci.p + value - 1);
		अगर (i >= PAGE_SIZE - (8 + 1 + 8 + 1))
			अवरोध;
	पूर्ण
	up_पढ़ो(&fw_device_rwsem);

	अगर (i)
		buf[i - 1] = '\n';

	वापस i;
पूर्ण

अटल काष्ठा device_attribute fw_device_attributes[] = अणु
	__ATTR_RO(config_rom),
	__ATTR_RO(guid),
	__ATTR_RO(is_local),
	__ATTR_RO(units),
	__ATTR_शून्य,
पूर्ण;

अटल पूर्णांक पढ़ो_rom(काष्ठा fw_device *device,
		    पूर्णांक generation, पूर्णांक index, u32 *data)
अणु
	u64 offset = (CSR_REGISTER_BASE | CSR_CONFIG_ROM) + index * 4;
	पूर्णांक i, rcode;

	/* device->node_id, accessed below, must not be older than generation */
	smp_rmb();

	क्रम (i = 10; i < 100; i += 10) अणु
		rcode = fw_run_transaction(device->card,
				TCODE_READ_QUADLET_REQUEST, device->node_id,
				generation, device->max_speed, offset, data, 4);
		अगर (rcode != RCODE_BUSY)
			अवरोध;
		msleep(i);
	पूर्ण
	be32_to_cpus(data);

	वापस rcode;
पूर्ण

#घोषणा MAX_CONFIG_ROM_SIZE 256

/*
 * Read the bus info block, perक्रमm a speed probe, and पढ़ो all of the rest of
 * the config ROM.  We करो all this with a cached bus generation.  If the bus
 * generation changes under us, पढ़ो_config_rom will fail and get retried.
 * It's better to start all over in this हाल because the node from which we
 * are पढ़ोing the ROM may have changed the ROM during the reset.
 * Returns either a result code or a negative error code.
 */
अटल पूर्णांक पढ़ो_config_rom(काष्ठा fw_device *device, पूर्णांक generation)
अणु
	काष्ठा fw_card *card = device->card;
	स्थिर u32 *old_rom, *new_rom;
	u32 *rom, *stack;
	u32 sp, key;
	पूर्णांक i, end, length, ret;

	rom = kदो_स्मृति(माप(*rom) * MAX_CONFIG_ROM_SIZE +
		      माप(*stack) * MAX_CONFIG_ROM_SIZE, GFP_KERNEL);
	अगर (rom == शून्य)
		वापस -ENOMEM;

	stack = &rom[MAX_CONFIG_ROM_SIZE];
	स_रखो(rom, 0, माप(*rom) * MAX_CONFIG_ROM_SIZE);

	device->max_speed = SCODE_100;

	/* First पढ़ो the bus info block. */
	क्रम (i = 0; i < 5; i++) अणु
		ret = पढ़ो_rom(device, generation, i, &rom[i]);
		अगर (ret != RCODE_COMPLETE)
			जाओ out;
		/*
		 * As per IEEE1212 7.2, during initialization, devices can
		 * reply with a 0 क्रम the first quadlet of the config
		 * rom to indicate that they are booting (क्रम example,
		 * अगर the firmware is on the disk of a बाह्यal
		 * harddisk).  In that हाल we just fail, and the
		 * retry mechanism will try again later.
		 */
		अगर (i == 0 && rom[i] == 0) अणु
			ret = RCODE_BUSY;
			जाओ out;
		पूर्ण
	पूर्ण

	device->max_speed = device->node->max_speed;

	/*
	 * Determine the speed of
	 *   - devices with link speed less than PHY speed,
	 *   - devices with 1394b PHY (unless only connected to 1394a PHYs),
	 *   - all devices अगर there are 1394b repeaters.
	 * Note, we cannot use the bus info block's link_spd as starting poपूर्णांक
	 * because some buggy firmwares set it lower than necessary and because
	 * 1394-1995 nodes करो not have the field.
	 */
	अगर ((rom[2] & 0x7) < device->max_speed ||
	    device->max_speed == SCODE_BETA ||
	    card->beta_repeaters_present) अणु
		u32 dummy;

		/* क्रम S1600 and S3200 */
		अगर (device->max_speed == SCODE_BETA)
			device->max_speed = card->link_speed;

		जबतक (device->max_speed > SCODE_100) अणु
			अगर (पढ़ो_rom(device, generation, 0, &dummy) ==
			    RCODE_COMPLETE)
				अवरोध;
			device->max_speed--;
		पूर्ण
	पूर्ण

	/*
	 * Now parse the config rom.  The config rom is a recursive
	 * directory काष्ठाure so we parse it using a stack of
	 * references to the blocks that make up the काष्ठाure.  We
	 * push a reference to the root directory on the stack to
	 * start things off.
	 */
	length = i;
	sp = 0;
	stack[sp++] = 0xc0000005;
	जबतक (sp > 0) अणु
		/*
		 * Pop the next block reference of the stack.  The
		 * lower 24 bits is the offset पूर्णांकo the config rom,
		 * the upper 8 bits are the type of the reference the
		 * block.
		 */
		key = stack[--sp];
		i = key & 0xffffff;
		अगर (WARN_ON(i >= MAX_CONFIG_ROM_SIZE)) अणु
			ret = -ENXIO;
			जाओ out;
		पूर्ण

		/* Read header quadlet क्रम the block to get the length. */
		ret = पढ़ो_rom(device, generation, i, &rom[i]);
		अगर (ret != RCODE_COMPLETE)
			जाओ out;
		end = i + (rom[i] >> 16) + 1;
		अगर (end > MAX_CONFIG_ROM_SIZE) अणु
			/*
			 * This block extends outside the config ROM which is
			 * a firmware bug.  Ignore this whole block, i.e.
			 * simply set a fake block length of 0.
			 */
			fw_err(card, "skipped invalid ROM block %x at %llx\n",
			       rom[i],
			       i * 4 | CSR_REGISTER_BASE | CSR_CONFIG_ROM);
			rom[i] = 0;
			end = i;
		पूर्ण
		i++;

		/*
		 * Now पढ़ो in the block.  If this is a directory
		 * block, check the entries as we पढ़ो them to see अगर
		 * it references another block, and push it in that हाल.
		 */
		क्रम (; i < end; i++) अणु
			ret = पढ़ो_rom(device, generation, i, &rom[i]);
			अगर (ret != RCODE_COMPLETE)
				जाओ out;

			अगर ((key >> 30) != 3 || (rom[i] >> 30) < 2)
				जारी;
			/*
			 * Offset poपूर्णांकs outside the ROM.  May be a firmware
			 * bug or an Extended ROM entry (IEEE 1212-2001 clause
			 * 7.7.18).  Simply overग_लिखो this poपूर्णांकer here by a
			 * fake immediate entry so that later iterators over
			 * the ROM करोn't have to check offsets all the समय.
			 */
			अगर (i + (rom[i] & 0xffffff) >= MAX_CONFIG_ROM_SIZE) अणु
				fw_err(card,
				       "skipped unsupported ROM entry %x at %llx\n",
				       rom[i],
				       i * 4 | CSR_REGISTER_BASE | CSR_CONFIG_ROM);
				rom[i] = 0;
				जारी;
			पूर्ण
			stack[sp++] = i + rom[i];
		पूर्ण
		अगर (length < i)
			length = i;
	पूर्ण

	old_rom = device->config_rom;
	new_rom = kmemdup(rom, length * 4, GFP_KERNEL);
	अगर (new_rom == शून्य) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	करोwn_ग_लिखो(&fw_device_rwsem);
	device->config_rom = new_rom;
	device->config_rom_length = length;
	up_ग_लिखो(&fw_device_rwsem);

	kमुक्त(old_rom);
	ret = RCODE_COMPLETE;
	device->max_rec	= rom[2] >> 12 & 0xf;
	device->cmc	= rom[2] >> 30 & 1;
	device->irmc	= rom[2] >> 31 & 1;
 out:
	kमुक्त(rom);

	वापस ret;
पूर्ण

अटल व्योम fw_unit_release(काष्ठा device *dev)
अणु
	काष्ठा fw_unit *unit = fw_unit(dev);

	fw_device_put(fw_parent_device(unit));
	kमुक्त(unit);
पूर्ण

अटल काष्ठा device_type fw_unit_type = अणु
	.uevent		= fw_unit_uevent,
	.release	= fw_unit_release,
पूर्ण;

अटल bool is_fw_unit(काष्ठा device *dev)
अणु
	वापस dev->type == &fw_unit_type;
पूर्ण

अटल व्योम create_units(काष्ठा fw_device *device)
अणु
	काष्ठा fw_csr_iterator ci;
	काष्ठा fw_unit *unit;
	पूर्णांक key, value, i;

	i = 0;
	fw_csr_iterator_init(&ci, &device->config_rom[5]);
	जबतक (fw_csr_iterator_next(&ci, &key, &value)) अणु
		अगर (key != (CSR_UNIT | CSR_सूचीECTORY))
			जारी;

		/*
		 * Get the address of the unit directory and try to
		 * match the drivers id_tables against it.
		 */
		unit = kzalloc(माप(*unit), GFP_KERNEL);
		अगर (unit == शून्य)
			जारी;

		unit->directory = ci.p + value - 1;
		unit->device.bus = &fw_bus_type;
		unit->device.type = &fw_unit_type;
		unit->device.parent = &device->device;
		dev_set_name(&unit->device, "%s.%d", dev_name(&device->device), i++);

		BUILD_BUG_ON(ARRAY_SIZE(unit->attribute_group.attrs) <
				ARRAY_SIZE(fw_unit_attributes) +
				ARRAY_SIZE(config_rom_attributes));
		init_fw_attribute_group(&unit->device,
					fw_unit_attributes,
					&unit->attribute_group);

		अगर (device_रेजिस्टर(&unit->device) < 0)
			जाओ skip_unit;

		fw_device_get(device);
		जारी;

	skip_unit:
		kमुक्त(unit);
	पूर्ण
पूर्ण

अटल पूर्णांक shutकरोwn_unit(काष्ठा device *device, व्योम *data)
अणु
	device_unरेजिस्टर(device);

	वापस 0;
पूर्ण

/*
 * fw_device_rwsem acts as dual purpose mutex:
 *   - serializes accesses to fw_device_idr,
 *   - serializes accesses to fw_device.config_rom/.config_rom_length and
 *     fw_unit.directory, unless those accesses happen at safe occasions
 */
DECLARE_RWSEM(fw_device_rwsem);

DEFINE_IDR(fw_device_idr);
पूर्णांक fw_cdev_major;

काष्ठा fw_device *fw_device_get_by_devt(dev_t devt)
अणु
	काष्ठा fw_device *device;

	करोwn_पढ़ो(&fw_device_rwsem);
	device = idr_find(&fw_device_idr, MINOR(devt));
	अगर (device)
		fw_device_get(device);
	up_पढ़ो(&fw_device_rwsem);

	वापस device;
पूर्ण

काष्ठा workqueue_काष्ठा *fw_workqueue;
EXPORT_SYMBOL(fw_workqueue);

अटल व्योम fw_schedule_device_work(काष्ठा fw_device *device,
				    अचिन्हित दीर्घ delay)
अणु
	queue_delayed_work(fw_workqueue, &device->work, delay);
पूर्ण

/*
 * These defines control the retry behavior क्रम पढ़ोing the config
 * rom.  It shouldn't be necessary to tweak these; अगर the device
 * करोesn't respond to a config rom read within 10 seconds, it's not
 * going to respond at all.  As क्रम the initial delay, a lot of
 * devices will be able to respond within half a second after bus
 * reset.  On the other hand, it's not really worth being more
 * aggressive than that, since it scales pretty well; अगर 10 devices
 * are plugged in, they're all getting पढ़ो within one second.
 */

#घोषणा MAX_RETRIES	10
#घोषणा RETRY_DELAY	(3 * HZ)
#घोषणा INITIAL_DELAY	(HZ / 2)
#घोषणा SHUTDOWN_DELAY	(2 * HZ)

अटल व्योम fw_device_shutकरोwn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा fw_device *device =
		container_of(work, काष्ठा fw_device, work.work);
	पूर्णांक minor = MINOR(device->device.devt);

	अगर (समय_beक्रमe64(get_jअगरfies_64(),
			  device->card->reset_jअगरfies + SHUTDOWN_DELAY)
	    && !list_empty(&device->card->link)) अणु
		fw_schedule_device_work(device, SHUTDOWN_DELAY);
		वापस;
	पूर्ण

	अगर (atomic_cmpxchg(&device->state,
			   FW_DEVICE_GONE,
			   FW_DEVICE_SHUTDOWN) != FW_DEVICE_GONE)
		वापस;

	fw_device_cdev_हटाओ(device);
	device_क्रम_each_child(&device->device, शून्य, shutकरोwn_unit);
	device_unरेजिस्टर(&device->device);

	करोwn_ग_लिखो(&fw_device_rwsem);
	idr_हटाओ(&fw_device_idr, minor);
	up_ग_लिखो(&fw_device_rwsem);

	fw_device_put(device);
पूर्ण

अटल व्योम fw_device_release(काष्ठा device *dev)
अणु
	काष्ठा fw_device *device = fw_device(dev);
	काष्ठा fw_card *card = device->card;
	अचिन्हित दीर्घ flags;

	/*
	 * Take the card lock so we करोn't set this to शून्य जबतक a
	 * FW_NODE_UPDATED callback is being handled or जबतक the
	 * bus manager work looks at this node.
	 */
	spin_lock_irqsave(&card->lock, flags);
	device->node->data = शून्य;
	spin_unlock_irqrestore(&card->lock, flags);

	fw_node_put(device->node);
	kमुक्त(device->config_rom);
	kमुक्त(device);
	fw_card_put(card);
पूर्ण

अटल काष्ठा device_type fw_device_type = अणु
	.release = fw_device_release,
पूर्ण;

अटल bool is_fw_device(काष्ठा device *dev)
अणु
	वापस dev->type == &fw_device_type;
पूर्ण

अटल पूर्णांक update_unit(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा fw_unit *unit = fw_unit(dev);
	काष्ठा fw_driver *driver = (काष्ठा fw_driver *)dev->driver;

	अगर (is_fw_unit(dev) && driver != शून्य && driver->update != शून्य) अणु
		device_lock(dev);
		driver->update(unit);
		device_unlock(dev);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम fw_device_update(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा fw_device *device =
		container_of(work, काष्ठा fw_device, work.work);

	fw_device_cdev_update(device);
	device_क्रम_each_child(&device->device, शून्य, update_unit);
पूर्ण

/*
 * If a device was pending क्रम deletion because its node went away but its
 * bus info block and root directory header matches that of a newly discovered
 * device, revive the existing fw_device.
 * The newly allocated fw_device becomes obsolete instead.
 */
अटल पूर्णांक lookup_existing_device(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा fw_device *old = fw_device(dev);
	काष्ठा fw_device *new = data;
	काष्ठा fw_card *card = new->card;
	पूर्णांक match = 0;

	अगर (!is_fw_device(dev))
		वापस 0;

	करोwn_पढ़ो(&fw_device_rwsem); /* serialize config_rom access */
	spin_lock_irq(&card->lock);  /* serialize node access */

	अगर (स_भेद(old->config_rom, new->config_rom, 6 * 4) == 0 &&
	    atomic_cmpxchg(&old->state,
			   FW_DEVICE_GONE,
			   FW_DEVICE_RUNNING) == FW_DEVICE_GONE) अणु
		काष्ठा fw_node *current_node = new->node;
		काष्ठा fw_node *obsolete_node = old->node;

		new->node = obsolete_node;
		new->node->data = new;
		old->node = current_node;
		old->node->data = old;

		old->max_speed = new->max_speed;
		old->node_id = current_node->node_id;
		smp_wmb();  /* update node_id beक्रमe generation */
		old->generation = card->generation;
		old->config_rom_retries = 0;
		fw_notice(card, "rediscovered device %s\n", dev_name(dev));

		old->workfn = fw_device_update;
		fw_schedule_device_work(old, 0);

		अगर (current_node == card->root_node)
			fw_schedule_bm_work(card, 0);

		match = 1;
	पूर्ण

	spin_unlock_irq(&card->lock);
	up_पढ़ो(&fw_device_rwsem);

	वापस match;
पूर्ण

क्रमागत अणु BC_UNKNOWN = 0, BC_UNIMPLEMENTED, BC_IMPLEMENTED, पूर्ण;

अटल व्योम set_broadcast_channel(काष्ठा fw_device *device, पूर्णांक generation)
अणु
	काष्ठा fw_card *card = device->card;
	__be32 data;
	पूर्णांक rcode;

	अगर (!card->broadcast_channel_allocated)
		वापस;

	/*
	 * The Broadcast_Channel Valid bit is required by nodes which want to
	 * transmit on this channel.  Such transmissions are practically
	 * exclusive to IP over 1394 (RFC 2734).  IP capable nodes are required
	 * to be IRM capable and have a max_rec of 8 or more.  We use this fact
	 * to narrow करोwn to which nodes we send Broadcast_Channel updates.
	 */
	अगर (!device->irmc || device->max_rec < 8)
		वापस;

	/*
	 * Some 1394-1995 nodes crash अगर this 1394a-2000 रेजिस्टर is written.
	 * Perक्रमm a पढ़ो test first.
	 */
	अगर (device->bc_implemented == BC_UNKNOWN) अणु
		rcode = fw_run_transaction(card, TCODE_READ_QUADLET_REQUEST,
				device->node_id, generation, device->max_speed,
				CSR_REGISTER_BASE + CSR_BROADCAST_CHANNEL,
				&data, 4);
		चयन (rcode) अणु
		हाल RCODE_COMPLETE:
			अगर (data & cpu_to_be32(1 << 31)) अणु
				device->bc_implemented = BC_IMPLEMENTED;
				अवरोध;
			पूर्ण
			fallthrough;	/* to हाल address error */
		हाल RCODE_ADDRESS_ERROR:
			device->bc_implemented = BC_UNIMPLEMENTED;
		पूर्ण
	पूर्ण

	अगर (device->bc_implemented == BC_IMPLEMENTED) अणु
		data = cpu_to_be32(BROADCAST_CHANNEL_INITIAL |
				   BROADCAST_CHANNEL_VALID);
		fw_run_transaction(card, TCODE_WRITE_QUADLET_REQUEST,
				device->node_id, generation, device->max_speed,
				CSR_REGISTER_BASE + CSR_BROADCAST_CHANNEL,
				&data, 4);
	पूर्ण
पूर्ण

पूर्णांक fw_device_set_broadcast_channel(काष्ठा device *dev, व्योम *gen)
अणु
	अगर (is_fw_device(dev))
		set_broadcast_channel(fw_device(dev), (दीर्घ)gen);

	वापस 0;
पूर्ण

अटल व्योम fw_device_init(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा fw_device *device =
		container_of(work, काष्ठा fw_device, work.work);
	काष्ठा fw_card *card = device->card;
	काष्ठा device *revived_dev;
	पूर्णांक minor, ret;

	/*
	 * All failure paths here set node->data to शून्य, so that we
	 * करोn't try to do device_for_each_child() on a kfree()'d
	 * device.
	 */

	ret = पढ़ो_config_rom(device, device->generation);
	अगर (ret != RCODE_COMPLETE) अणु
		अगर (device->config_rom_retries < MAX_RETRIES &&
		    atomic_पढ़ो(&device->state) == FW_DEVICE_INITIALIZING) अणु
			device->config_rom_retries++;
			fw_schedule_device_work(device, RETRY_DELAY);
		पूर्ण अन्यथा अणु
			अगर (device->node->link_on)
				fw_notice(card, "giving up on node %x: reading config rom failed: %s\n",
					  device->node_id,
					  fw_rcode_string(ret));
			अगर (device->node == card->root_node)
				fw_schedule_bm_work(card, 0);
			fw_device_release(&device->device);
		पूर्ण
		वापस;
	पूर्ण

	revived_dev = device_find_child(card->device,
					device, lookup_existing_device);
	अगर (revived_dev) अणु
		put_device(revived_dev);
		fw_device_release(&device->device);

		वापस;
	पूर्ण

	device_initialize(&device->device);

	fw_device_get(device);
	करोwn_ग_लिखो(&fw_device_rwsem);
	minor = idr_alloc(&fw_device_idr, device, 0, 1 << MINORBITS,
			GFP_KERNEL);
	up_ग_लिखो(&fw_device_rwsem);

	अगर (minor < 0)
		जाओ error;

	device->device.bus = &fw_bus_type;
	device->device.type = &fw_device_type;
	device->device.parent = card->device;
	device->device.devt = MKDEV(fw_cdev_major, minor);
	dev_set_name(&device->device, "fw%d", minor);

	BUILD_BUG_ON(ARRAY_SIZE(device->attribute_group.attrs) <
			ARRAY_SIZE(fw_device_attributes) +
			ARRAY_SIZE(config_rom_attributes));
	init_fw_attribute_group(&device->device,
				fw_device_attributes,
				&device->attribute_group);

	अगर (device_add(&device->device)) अणु
		fw_err(card, "failed to add device\n");
		जाओ error_with_cdev;
	पूर्ण

	create_units(device);

	/*
	 * Transition the device to running state.  If it got pulled
	 * out from under us जबतक we did the initialization work, we
	 * have to shut करोwn the device again here.  Normally, though,
	 * fw_node_event will be responsible क्रम shutting it करोwn when
	 * necessary.  We have to use the atomic cmpxchg here to aव्योम
	 * racing with the FW_NODE_DESTROYED हाल in
	 * fw_node_event().
	 */
	अगर (atomic_cmpxchg(&device->state,
			   FW_DEVICE_INITIALIZING,
			   FW_DEVICE_RUNNING) == FW_DEVICE_GONE) अणु
		device->workfn = fw_device_shutकरोwn;
		fw_schedule_device_work(device, SHUTDOWN_DELAY);
	पूर्ण अन्यथा अणु
		fw_notice(card, "created device %s: GUID %08x%08x, S%d00\n",
			  dev_name(&device->device),
			  device->config_rom[3], device->config_rom[4],
			  1 << device->max_speed);
		device->config_rom_retries = 0;

		set_broadcast_channel(device, device->generation);

		add_device_अक्रमomness(&device->config_rom[3], 8);
	पूर्ण

	/*
	 * Reschedule the IRM work अगर we just finished पढ़ोing the
	 * root node config rom.  If this races with a bus reset we
	 * just end up running the IRM work a couple of extra बार -
	 * pretty harmless.
	 */
	अगर (device->node == card->root_node)
		fw_schedule_bm_work(card, 0);

	वापस;

 error_with_cdev:
	करोwn_ग_लिखो(&fw_device_rwsem);
	idr_हटाओ(&fw_device_idr, minor);
	up_ग_लिखो(&fw_device_rwsem);
 error:
	fw_device_put(device);		/* fw_device_idr's reference */

	put_device(&device->device);	/* our reference */
पूर्ण

/* Reपढ़ो and compare bus info block and header of root directory */
अटल पूर्णांक reपढ़ो_config_rom(काष्ठा fw_device *device, पूर्णांक generation,
			     bool *changed)
अणु
	u32 q;
	पूर्णांक i, rcode;

	क्रम (i = 0; i < 6; i++) अणु
		rcode = पढ़ो_rom(device, generation, i, &q);
		अगर (rcode != RCODE_COMPLETE)
			वापस rcode;

		अगर (i == 0 && q == 0)
			/* inaccessible (see पढ़ो_config_rom); retry later */
			वापस RCODE_BUSY;

		अगर (q != device->config_rom[i]) अणु
			*changed = true;
			वापस RCODE_COMPLETE;
		पूर्ण
	पूर्ण

	*changed = false;
	वापस RCODE_COMPLETE;
पूर्ण

अटल व्योम fw_device_refresh(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा fw_device *device =
		container_of(work, काष्ठा fw_device, work.work);
	काष्ठा fw_card *card = device->card;
	पूर्णांक ret, node_id = device->node_id;
	bool changed;

	ret = reपढ़ो_config_rom(device, device->generation, &changed);
	अगर (ret != RCODE_COMPLETE)
		जाओ failed_config_rom;

	अगर (!changed) अणु
		अगर (atomic_cmpxchg(&device->state,
				   FW_DEVICE_INITIALIZING,
				   FW_DEVICE_RUNNING) == FW_DEVICE_GONE)
			जाओ gone;

		fw_device_update(work);
		device->config_rom_retries = 0;
		जाओ out;
	पूर्ण

	/*
	 * Something changed.  We keep things simple and करोn't investigate
	 * further.  We just destroy all previous units and create new ones.
	 */
	device_क्रम_each_child(&device->device, शून्य, shutकरोwn_unit);

	ret = पढ़ो_config_rom(device, device->generation);
	अगर (ret != RCODE_COMPLETE)
		जाओ failed_config_rom;

	fw_device_cdev_update(device);
	create_units(device);

	/* Userspace may want to re-पढ़ो attributes. */
	kobject_uevent(&device->device.kobj, KOBJ_CHANGE);

	अगर (atomic_cmpxchg(&device->state,
			   FW_DEVICE_INITIALIZING,
			   FW_DEVICE_RUNNING) == FW_DEVICE_GONE)
		जाओ gone;

	fw_notice(card, "refreshed device %s\n", dev_name(&device->device));
	device->config_rom_retries = 0;
	जाओ out;

 failed_config_rom:
	अगर (device->config_rom_retries < MAX_RETRIES &&
	    atomic_पढ़ो(&device->state) == FW_DEVICE_INITIALIZING) अणु
		device->config_rom_retries++;
		fw_schedule_device_work(device, RETRY_DELAY);
		वापस;
	पूर्ण

	fw_notice(card, "giving up on refresh of device %s: %s\n",
		  dev_name(&device->device), fw_rcode_string(ret));
 gone:
	atomic_set(&device->state, FW_DEVICE_GONE);
	device->workfn = fw_device_shutकरोwn;
	fw_schedule_device_work(device, SHUTDOWN_DELAY);
 out:
	अगर (node_id == card->root_node->node_id)
		fw_schedule_bm_work(card, 0);
पूर्ण

अटल व्योम fw_device_workfn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा fw_device *device = container_of(to_delayed_work(work),
						काष्ठा fw_device, work);
	device->workfn(work);
पूर्ण

व्योम fw_node_event(काष्ठा fw_card *card, काष्ठा fw_node *node, पूर्णांक event)
अणु
	काष्ठा fw_device *device;

	चयन (event) अणु
	हाल FW_NODE_CREATED:
		/*
		 * Attempt to scan the node, regardless whether its self ID has
		 * the L (link active) flag set or not.  Some broken devices
		 * send L=0 but have an up-and-running link; others send L=1
		 * without actually having a link.
		 */
 create:
		device = kzalloc(माप(*device), GFP_ATOMIC);
		अगर (device == शून्य)
			अवरोध;

		/*
		 * Do minimal initialization of the device here, the
		 * rest will happen in fw_device_init().
		 *
		 * Attention:  A lot of things, even fw_device_get(),
		 * cannot be करोne beक्रमe fw_device_init() finished!
		 * You can basically just check device->state and
		 * schedule work until then, but only जबतक holding
		 * card->lock.
		 */
		atomic_set(&device->state, FW_DEVICE_INITIALIZING);
		device->card = fw_card_get(card);
		device->node = fw_node_get(node);
		device->node_id = node->node_id;
		device->generation = card->generation;
		device->is_local = node == card->local_node;
		mutex_init(&device->client_list_mutex);
		INIT_LIST_HEAD(&device->client_list);

		/*
		 * Set the node data to poपूर्णांक back to this device so
		 * FW_NODE_UPDATED callbacks can update the node_id
		 * and generation क्रम the device.
		 */
		node->data = device;

		/*
		 * Many devices are slow to respond after bus resets,
		 * especially अगर they are bus घातered and go through
		 * घातer-up after getting plugged in.  We schedule the
		 * first config rom scan half a second after bus reset.
		 */
		device->workfn = fw_device_init;
		INIT_DELAYED_WORK(&device->work, fw_device_workfn);
		fw_schedule_device_work(device, INITIAL_DELAY);
		अवरोध;

	हाल FW_NODE_INITIATED_RESET:
	हाल FW_NODE_LINK_ON:
		device = node->data;
		अगर (device == शून्य)
			जाओ create;

		device->node_id = node->node_id;
		smp_wmb();  /* update node_id beक्रमe generation */
		device->generation = card->generation;
		अगर (atomic_cmpxchg(&device->state,
			    FW_DEVICE_RUNNING,
			    FW_DEVICE_INITIALIZING) == FW_DEVICE_RUNNING) अणु
			device->workfn = fw_device_refresh;
			fw_schedule_device_work(device,
				device->is_local ? 0 : INITIAL_DELAY);
		पूर्ण
		अवरोध;

	हाल FW_NODE_UPDATED:
		device = node->data;
		अगर (device == शून्य)
			अवरोध;

		device->node_id = node->node_id;
		smp_wmb();  /* update node_id beक्रमe generation */
		device->generation = card->generation;
		अगर (atomic_पढ़ो(&device->state) == FW_DEVICE_RUNNING) अणु
			device->workfn = fw_device_update;
			fw_schedule_device_work(device, 0);
		पूर्ण
		अवरोध;

	हाल FW_NODE_DESTROYED:
	हाल FW_NODE_LINK_OFF:
		अगर (!node->data)
			अवरोध;

		/*
		 * Destroy the device associated with the node.  There
		 * are two हालs here: either the device is fully
		 * initialized (FW_DEVICE_RUNNING) or we're in the
		 * process of पढ़ोing its config rom
		 * (FW_DEVICE_INITIALIZING).  If it is fully
		 * initialized we can reuse device->work to schedule a
		 * full fw_device_shutकरोwn().  If not, there's work
		 * scheduled to पढ़ो it's config rom, and we just put
		 * the device in shutकरोwn state to have that code fail
		 * to create the device.
		 */
		device = node->data;
		अगर (atomic_xchg(&device->state,
				FW_DEVICE_GONE) == FW_DEVICE_RUNNING) अणु
			device->workfn = fw_device_shutकरोwn;
			fw_schedule_device_work(device,
				list_empty(&card->link) ? 0 : SHUTDOWN_DELAY);
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण
