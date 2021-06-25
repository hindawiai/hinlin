<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * nvmem framework core.
 *
 * Copyright (C) 2015 Srinivas Kandagatla <srinivas.kandagatla@linaro.org>
 * Copyright (C) 2013 Maxime Ripard <maxime.ripard@मुक्त-electrons.com>
 */

#समावेश <linux/device.h>
#समावेश <linux/export.h>
#समावेश <linux/fs.h>
#समावेश <linux/idr.h>
#समावेश <linux/init.h>
#समावेश <linux/kref.h>
#समावेश <linux/module.h>
#समावेश <linux/nvmem-consumer.h>
#समावेश <linux/nvmem-provider.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/of.h>
#समावेश <linux/slab.h>

काष्ठा nvmem_device अणु
	काष्ठा module		*owner;
	काष्ठा device		dev;
	पूर्णांक			stride;
	पूर्णांक			word_size;
	पूर्णांक			id;
	काष्ठा kref		refcnt;
	माप_प्रकार			size;
	bool			पढ़ो_only;
	bool			root_only;
	पूर्णांक			flags;
	क्रमागत nvmem_type		type;
	काष्ठा bin_attribute	eeprom;
	काष्ठा device		*base_dev;
	काष्ठा list_head	cells;
	स्थिर काष्ठा nvmem_keepout *keepout;
	अचिन्हित पूर्णांक		nkeepout;
	nvmem_reg_पढ़ो_t	reg_पढ़ो;
	nvmem_reg_ग_लिखो_t	reg_ग_लिखो;
	काष्ठा gpio_desc	*wp_gpio;
	व्योम *priv;
पूर्ण;

#घोषणा to_nvmem_device(d) container_of(d, काष्ठा nvmem_device, dev)

#घोषणा FLAG_COMPAT		BIT(0)

काष्ठा nvmem_cell अणु
	स्थिर अक्षर		*name;
	पूर्णांक			offset;
	पूर्णांक			bytes;
	पूर्णांक			bit_offset;
	पूर्णांक			nbits;
	काष्ठा device_node	*np;
	काष्ठा nvmem_device	*nvmem;
	काष्ठा list_head	node;
पूर्ण;

अटल DEFINE_MUTEX(nvmem_mutex);
अटल DEFINE_IDA(nvmem_ida);

अटल DEFINE_MUTEX(nvmem_cell_mutex);
अटल LIST_HEAD(nvmem_cell_tables);

अटल DEFINE_MUTEX(nvmem_lookup_mutex);
अटल LIST_HEAD(nvmem_lookup_list);

अटल BLOCKING_NOTIFIER_HEAD(nvmem_notअगरier);

अटल पूर्णांक __nvmem_reg_पढ़ो(काष्ठा nvmem_device *nvmem, अचिन्हित पूर्णांक offset,
			    व्योम *val, माप_प्रकार bytes)
अणु
	अगर (nvmem->reg_पढ़ो)
		वापस nvmem->reg_पढ़ो(nvmem->priv, offset, val, bytes);

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक __nvmem_reg_ग_लिखो(काष्ठा nvmem_device *nvmem, अचिन्हित पूर्णांक offset,
			     व्योम *val, माप_प्रकार bytes)
अणु
	पूर्णांक ret;

	अगर (nvmem->reg_ग_लिखो) अणु
		gpiod_set_value_cansleep(nvmem->wp_gpio, 0);
		ret = nvmem->reg_ग_लिखो(nvmem->priv, offset, val, bytes);
		gpiod_set_value_cansleep(nvmem->wp_gpio, 1);
		वापस ret;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक nvmem_access_with_keepouts(काष्ठा nvmem_device *nvmem,
				      अचिन्हित पूर्णांक offset, व्योम *val,
				      माप_प्रकार bytes, पूर्णांक ग_लिखो)
अणु

	अचिन्हित पूर्णांक end = offset + bytes;
	अचिन्हित पूर्णांक kend, ksize;
	स्थिर काष्ठा nvmem_keepout *keepout = nvmem->keepout;
	स्थिर काष्ठा nvmem_keepout *keepoutend = keepout + nvmem->nkeepout;
	पूर्णांक rc;

	/*
	 * Skip all keepouts beक्रमe the range being accessed.
	 * Keepouts are sorted.
	 */
	जबतक ((keepout < keepoutend) && (keepout->end <= offset))
		keepout++;

	जबतक ((offset < end) && (keepout < keepoutend)) अणु
		/* Access the valid portion beक्रमe the keepout. */
		अगर (offset < keepout->start) अणु
			kend = min(end, keepout->start);
			ksize = kend - offset;
			अगर (ग_लिखो)
				rc = __nvmem_reg_ग_लिखो(nvmem, offset, val, ksize);
			अन्यथा
				rc = __nvmem_reg_पढ़ो(nvmem, offset, val, ksize);

			अगर (rc)
				वापस rc;

			offset += ksize;
			val += ksize;
		पूर्ण

		/*
		 * Now we're aligned to the start of this keepout zone. Go
		 * through it.
		 */
		kend = min(end, keepout->end);
		ksize = kend - offset;
		अगर (!ग_लिखो)
			स_रखो(val, keepout->value, ksize);

		val += ksize;
		offset += ksize;
		keepout++;
	पूर्ण

	/*
	 * If we ran out of keepouts but there's still stuff to करो, send it
	 * करोwn directly
	 */
	अगर (offset < end) अणु
		ksize = end - offset;
		अगर (ग_लिखो)
			वापस __nvmem_reg_ग_लिखो(nvmem, offset, val, ksize);
		अन्यथा
			वापस __nvmem_reg_पढ़ो(nvmem, offset, val, ksize);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nvmem_reg_पढ़ो(काष्ठा nvmem_device *nvmem, अचिन्हित पूर्णांक offset,
			  व्योम *val, माप_प्रकार bytes)
अणु
	अगर (!nvmem->nkeepout)
		वापस __nvmem_reg_पढ़ो(nvmem, offset, val, bytes);

	वापस nvmem_access_with_keepouts(nvmem, offset, val, bytes, false);
पूर्ण

अटल पूर्णांक nvmem_reg_ग_लिखो(काष्ठा nvmem_device *nvmem, अचिन्हित पूर्णांक offset,
			   व्योम *val, माप_प्रकार bytes)
अणु
	अगर (!nvmem->nkeepout)
		वापस __nvmem_reg_ग_लिखो(nvmem, offset, val, bytes);

	वापस nvmem_access_with_keepouts(nvmem, offset, val, bytes, true);
पूर्ण

#अगर_घोषित CONFIG_NVMEM_SYSFS
अटल स्थिर अक्षर * स्थिर nvmem_type_str[] = अणु
	[NVMEM_TYPE_UNKNOWN] = "Unknown",
	[NVMEM_TYPE_EEPROM] = "EEPROM",
	[NVMEM_TYPE_OTP] = "OTP",
	[NVMEM_TYPE_BATTERY_BACKED] = "Battery backed",
पूर्ण;

#अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC
अटल काष्ठा lock_class_key eeprom_lock_key;
#पूर्ण_अगर

अटल sमाप_प्रकार type_show(काष्ठा device *dev,
			 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nvmem_device *nvmem = to_nvmem_device(dev);

	वापस प्र_लिखो(buf, "%s\n", nvmem_type_str[nvmem->type]);
पूर्ण

अटल DEVICE_ATTR_RO(type);

अटल काष्ठा attribute *nvmem_attrs[] = अणु
	&dev_attr_type.attr,
	शून्य,
पूर्ण;

अटल sमाप_प्रकार bin_attr_nvmem_पढ़ो(काष्ठा file *filp, काष्ठा kobject *kobj,
				   काष्ठा bin_attribute *attr, अक्षर *buf,
				   loff_t pos, माप_प्रकार count)
अणु
	काष्ठा device *dev;
	काष्ठा nvmem_device *nvmem;
	पूर्णांक rc;

	अगर (attr->निजी)
		dev = attr->निजी;
	अन्यथा
		dev = kobj_to_dev(kobj);
	nvmem = to_nvmem_device(dev);

	/* Stop the user from पढ़ोing */
	अगर (pos >= nvmem->size)
		वापस 0;

	अगर (!IS_ALIGNED(pos, nvmem->stride))
		वापस -EINVAL;

	अगर (count < nvmem->word_size)
		वापस -EINVAL;

	अगर (pos + count > nvmem->size)
		count = nvmem->size - pos;

	count = round_करोwn(count, nvmem->word_size);

	अगर (!nvmem->reg_पढ़ो)
		वापस -EPERM;

	rc = nvmem_reg_पढ़ो(nvmem, pos, buf, count);

	अगर (rc)
		वापस rc;

	वापस count;
पूर्ण

अटल sमाप_प्रकार bin_attr_nvmem_ग_लिखो(काष्ठा file *filp, काष्ठा kobject *kobj,
				    काष्ठा bin_attribute *attr, अक्षर *buf,
				    loff_t pos, माप_प्रकार count)
अणु
	काष्ठा device *dev;
	काष्ठा nvmem_device *nvmem;
	पूर्णांक rc;

	अगर (attr->निजी)
		dev = attr->निजी;
	अन्यथा
		dev = kobj_to_dev(kobj);
	nvmem = to_nvmem_device(dev);

	/* Stop the user from writing */
	अगर (pos >= nvmem->size)
		वापस -EFBIG;

	अगर (!IS_ALIGNED(pos, nvmem->stride))
		वापस -EINVAL;

	अगर (count < nvmem->word_size)
		वापस -EINVAL;

	अगर (pos + count > nvmem->size)
		count = nvmem->size - pos;

	count = round_करोwn(count, nvmem->word_size);

	अगर (!nvmem->reg_ग_लिखो)
		वापस -EPERM;

	rc = nvmem_reg_ग_लिखो(nvmem, pos, buf, count);

	अगर (rc)
		वापस rc;

	वापस count;
पूर्ण

अटल umode_t nvmem_bin_attr_get_umode(काष्ठा nvmem_device *nvmem)
अणु
	umode_t mode = 0400;

	अगर (!nvmem->root_only)
		mode |= 0044;

	अगर (!nvmem->पढ़ो_only)
		mode |= 0200;

	अगर (!nvmem->reg_ग_लिखो)
		mode &= ~0200;

	अगर (!nvmem->reg_पढ़ो)
		mode &= ~0444;

	वापस mode;
पूर्ण

अटल umode_t nvmem_bin_attr_is_visible(काष्ठा kobject *kobj,
					 काष्ठा bin_attribute *attr, पूर्णांक i)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा nvmem_device *nvmem = to_nvmem_device(dev);

	वापस nvmem_bin_attr_get_umode(nvmem);
पूर्ण

/* शेष पढ़ो/ग_लिखो permissions */
अटल काष्ठा bin_attribute bin_attr_rw_nvmem = अणु
	.attr	= अणु
		.name	= "nvmem",
		.mode	= 0644,
	पूर्ण,
	.पढ़ो	= bin_attr_nvmem_पढ़ो,
	.ग_लिखो	= bin_attr_nvmem_ग_लिखो,
पूर्ण;

अटल काष्ठा bin_attribute *nvmem_bin_attributes[] = अणु
	&bin_attr_rw_nvmem,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group nvmem_bin_group = अणु
	.bin_attrs	= nvmem_bin_attributes,
	.attrs		= nvmem_attrs,
	.is_bin_visible = nvmem_bin_attr_is_visible,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *nvmem_dev_groups[] = अणु
	&nvmem_bin_group,
	शून्य,
पूर्ण;

अटल काष्ठा bin_attribute bin_attr_nvmem_eeprom_compat = अणु
	.attr	= अणु
		.name	= "eeprom",
	पूर्ण,
	.पढ़ो	= bin_attr_nvmem_पढ़ो,
	.ग_लिखो	= bin_attr_nvmem_ग_लिखो,
पूर्ण;

/*
 * nvmem_setup_compat() - Create an additional binary entry in
 * drivers sys directory, to be backwards compatible with the older
 * drivers/misc/eeprom drivers.
 */
अटल पूर्णांक nvmem_sysfs_setup_compat(काष्ठा nvmem_device *nvmem,
				    स्थिर काष्ठा nvmem_config *config)
अणु
	पूर्णांक rval;

	अगर (!config->compat)
		वापस 0;

	अगर (!config->base_dev)
		वापस -EINVAL;

	nvmem->eeprom = bin_attr_nvmem_eeprom_compat;
	nvmem->eeprom.attr.mode = nvmem_bin_attr_get_umode(nvmem);
	nvmem->eeprom.size = nvmem->size;
#अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC
	nvmem->eeprom.attr.key = &eeprom_lock_key;
#पूर्ण_अगर
	nvmem->eeprom.निजी = &nvmem->dev;
	nvmem->base_dev = config->base_dev;

	rval = device_create_bin_file(nvmem->base_dev, &nvmem->eeprom);
	अगर (rval) अणु
		dev_err(&nvmem->dev,
			"Failed to create eeprom binary file %d\n", rval);
		वापस rval;
	पूर्ण

	nvmem->flags |= FLAG_COMPAT;

	वापस 0;
पूर्ण

अटल व्योम nvmem_sysfs_हटाओ_compat(काष्ठा nvmem_device *nvmem,
			      स्थिर काष्ठा nvmem_config *config)
अणु
	अगर (config->compat)
		device_हटाओ_bin_file(nvmem->base_dev, &nvmem->eeprom);
पूर्ण

#अन्यथा /* CONFIG_NVMEM_SYSFS */

अटल पूर्णांक nvmem_sysfs_setup_compat(काष्ठा nvmem_device *nvmem,
				    स्थिर काष्ठा nvmem_config *config)
अणु
	वापस -ENOSYS;
पूर्ण
अटल व्योम nvmem_sysfs_हटाओ_compat(काष्ठा nvmem_device *nvmem,
				      स्थिर काष्ठा nvmem_config *config)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_NVMEM_SYSFS */

अटल व्योम nvmem_release(काष्ठा device *dev)
अणु
	काष्ठा nvmem_device *nvmem = to_nvmem_device(dev);

	ida_मुक्त(&nvmem_ida, nvmem->id);
	gpiod_put(nvmem->wp_gpio);
	kमुक्त(nvmem);
पूर्ण

अटल स्थिर काष्ठा device_type nvmem_provider_type = अणु
	.release	= nvmem_release,
पूर्ण;

अटल काष्ठा bus_type nvmem_bus_type = अणु
	.name		= "nvmem",
पूर्ण;

अटल व्योम nvmem_cell_drop(काष्ठा nvmem_cell *cell)
अणु
	blocking_notअगरier_call_chain(&nvmem_notअगरier, NVMEM_CELL_REMOVE, cell);
	mutex_lock(&nvmem_mutex);
	list_del(&cell->node);
	mutex_unlock(&nvmem_mutex);
	of_node_put(cell->np);
	kमुक्त_स्थिर(cell->name);
	kमुक्त(cell);
पूर्ण

अटल व्योम nvmem_device_हटाओ_all_cells(स्थिर काष्ठा nvmem_device *nvmem)
अणु
	काष्ठा nvmem_cell *cell, *p;

	list_क्रम_each_entry_safe(cell, p, &nvmem->cells, node)
		nvmem_cell_drop(cell);
पूर्ण

अटल व्योम nvmem_cell_add(काष्ठा nvmem_cell *cell)
अणु
	mutex_lock(&nvmem_mutex);
	list_add_tail(&cell->node, &cell->nvmem->cells);
	mutex_unlock(&nvmem_mutex);
	blocking_notअगरier_call_chain(&nvmem_notअगरier, NVMEM_CELL_ADD, cell);
पूर्ण

अटल पूर्णांक nvmem_cell_info_to_nvmem_cell_nodup(काष्ठा nvmem_device *nvmem,
					स्थिर काष्ठा nvmem_cell_info *info,
					काष्ठा nvmem_cell *cell)
अणु
	cell->nvmem = nvmem;
	cell->offset = info->offset;
	cell->bytes = info->bytes;
	cell->name = info->name;

	cell->bit_offset = info->bit_offset;
	cell->nbits = info->nbits;

	अगर (cell->nbits)
		cell->bytes = DIV_ROUND_UP(cell->nbits + cell->bit_offset,
					   BITS_PER_BYTE);

	अगर (!IS_ALIGNED(cell->offset, nvmem->stride)) अणु
		dev_err(&nvmem->dev,
			"cell %s unaligned to nvmem stride %d\n",
			cell->name ?: "<unknown>", nvmem->stride);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nvmem_cell_info_to_nvmem_cell(काष्ठा nvmem_device *nvmem,
				स्थिर काष्ठा nvmem_cell_info *info,
				काष्ठा nvmem_cell *cell)
अणु
	पूर्णांक err;

	err = nvmem_cell_info_to_nvmem_cell_nodup(nvmem, info, cell);
	अगर (err)
		वापस err;

	cell->name = kstrdup_स्थिर(info->name, GFP_KERNEL);
	अगर (!cell->name)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

/**
 * nvmem_add_cells() - Add cell inक्रमmation to an nvmem device
 *
 * @nvmem: nvmem device to add cells to.
 * @info: nvmem cell info to add to the device
 * @ncells: number of cells in info
 *
 * Return: 0 or negative error code on failure.
 */
अटल पूर्णांक nvmem_add_cells(काष्ठा nvmem_device *nvmem,
		    स्थिर काष्ठा nvmem_cell_info *info,
		    पूर्णांक ncells)
अणु
	काष्ठा nvmem_cell **cells;
	पूर्णांक i, rval;

	cells = kसुस्मृति(ncells, माप(*cells), GFP_KERNEL);
	अगर (!cells)
		वापस -ENOMEM;

	क्रम (i = 0; i < ncells; i++) अणु
		cells[i] = kzalloc(माप(**cells), GFP_KERNEL);
		अगर (!cells[i]) अणु
			rval = -ENOMEM;
			जाओ err;
		पूर्ण

		rval = nvmem_cell_info_to_nvmem_cell(nvmem, &info[i], cells[i]);
		अगर (rval) अणु
			kमुक्त(cells[i]);
			जाओ err;
		पूर्ण

		nvmem_cell_add(cells[i]);
	पूर्ण

	/* हटाओ पंचांगp array */
	kमुक्त(cells);

	वापस 0;
err:
	जबतक (i--)
		nvmem_cell_drop(cells[i]);

	kमुक्त(cells);

	वापस rval;
पूर्ण

/**
 * nvmem_रेजिस्टर_notअगरier() - Register a notअगरier block क्रम nvmem events.
 *
 * @nb: notअगरier block to be called on nvmem events.
 *
 * Return: 0 on success, negative error number on failure.
 */
पूर्णांक nvmem_रेजिस्टर_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस blocking_notअगरier_chain_रेजिस्टर(&nvmem_notअगरier, nb);
पूर्ण
EXPORT_SYMBOL_GPL(nvmem_रेजिस्टर_notअगरier);

/**
 * nvmem_unरेजिस्टर_notअगरier() - Unरेजिस्टर a notअगरier block क्रम nvmem events.
 *
 * @nb: notअगरier block to be unरेजिस्टरed.
 *
 * Return: 0 on success, negative error number on failure.
 */
पूर्णांक nvmem_unरेजिस्टर_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस blocking_notअगरier_chain_unरेजिस्टर(&nvmem_notअगरier, nb);
पूर्ण
EXPORT_SYMBOL_GPL(nvmem_unरेजिस्टर_notअगरier);

अटल पूर्णांक nvmem_add_cells_from_table(काष्ठा nvmem_device *nvmem)
अणु
	स्थिर काष्ठा nvmem_cell_info *info;
	काष्ठा nvmem_cell_table *table;
	काष्ठा nvmem_cell *cell;
	पूर्णांक rval = 0, i;

	mutex_lock(&nvmem_cell_mutex);
	list_क्रम_each_entry(table, &nvmem_cell_tables, node) अणु
		अगर (म_भेद(nvmem_dev_name(nvmem), table->nvmem_name) == 0) अणु
			क्रम (i = 0; i < table->ncells; i++) अणु
				info = &table->cells[i];

				cell = kzalloc(माप(*cell), GFP_KERNEL);
				अगर (!cell) अणु
					rval = -ENOMEM;
					जाओ out;
				पूर्ण

				rval = nvmem_cell_info_to_nvmem_cell(nvmem,
								     info,
								     cell);
				अगर (rval) अणु
					kमुक्त(cell);
					जाओ out;
				पूर्ण

				nvmem_cell_add(cell);
			पूर्ण
		पूर्ण
	पूर्ण

out:
	mutex_unlock(&nvmem_cell_mutex);
	वापस rval;
पूर्ण

अटल काष्ठा nvmem_cell *
nvmem_find_cell_by_name(काष्ठा nvmem_device *nvmem, स्थिर अक्षर *cell_id)
अणु
	काष्ठा nvmem_cell *iter, *cell = शून्य;

	mutex_lock(&nvmem_mutex);
	list_क्रम_each_entry(iter, &nvmem->cells, node) अणु
		अगर (म_भेद(cell_id, iter->name) == 0) अणु
			cell = iter;
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&nvmem_mutex);

	वापस cell;
पूर्ण

अटल पूर्णांक nvmem_validate_keepouts(काष्ठा nvmem_device *nvmem)
अणु
	अचिन्हित पूर्णांक cur = 0;
	स्थिर काष्ठा nvmem_keepout *keepout = nvmem->keepout;
	स्थिर काष्ठा nvmem_keepout *keepoutend = keepout + nvmem->nkeepout;

	जबतक (keepout < keepoutend) अणु
		/* Ensure keepouts are sorted and करोn't overlap. */
		अगर (keepout->start < cur) अणु
			dev_err(&nvmem->dev,
				"Keepout regions aren't sorted or overlap.\n");

			वापस -दुस्फल;
		पूर्ण

		अगर (keepout->end < keepout->start) अणु
			dev_err(&nvmem->dev,
				"Invalid keepout region.\n");

			वापस -EINVAL;
		पूर्ण

		/*
		 * Validate keepouts (and holes between) करोn't violate
		 * word_size स्थिरraपूर्णांकs.
		 */
		अगर ((keepout->end - keepout->start < nvmem->word_size) ||
		    ((keepout->start != cur) &&
		     (keepout->start - cur < nvmem->word_size))) अणु

			dev_err(&nvmem->dev,
				"Keepout regions violate word_size constraints.\n");

			वापस -दुस्फल;
		पूर्ण

		/* Validate keepouts करोn't violate stride (alignment). */
		अगर (!IS_ALIGNED(keepout->start, nvmem->stride) ||
		    !IS_ALIGNED(keepout->end, nvmem->stride)) अणु

			dev_err(&nvmem->dev,
				"Keepout regions violate stride.\n");

			वापस -EINVAL;
		पूर्ण

		cur = keepout->end;
		keepout++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nvmem_add_cells_from_of(काष्ठा nvmem_device *nvmem)
अणु
	काष्ठा device_node *parent, *child;
	काष्ठा device *dev = &nvmem->dev;
	काष्ठा nvmem_cell *cell;
	स्थिर __be32 *addr;
	पूर्णांक len;

	parent = dev->of_node;

	क्रम_each_child_of_node(parent, child) अणु
		addr = of_get_property(child, "reg", &len);
		अगर (!addr)
			जारी;
		अगर (len < 2 * माप(u32)) अणु
			dev_err(dev, "nvmem: invalid reg on %pOF\n", child);
			वापस -EINVAL;
		पूर्ण

		cell = kzalloc(माप(*cell), GFP_KERNEL);
		अगर (!cell)
			वापस -ENOMEM;

		cell->nvmem = nvmem;
		cell->np = of_node_get(child);
		cell->offset = be32_to_cpup(addr++);
		cell->bytes = be32_to_cpup(addr);
		cell->name = kaप्र_लिखो(GFP_KERNEL, "%pOFn", child);

		addr = of_get_property(child, "bits", &len);
		अगर (addr && len == (2 * माप(u32))) अणु
			cell->bit_offset = be32_to_cpup(addr++);
			cell->nbits = be32_to_cpup(addr);
		पूर्ण

		अगर (cell->nbits)
			cell->bytes = DIV_ROUND_UP(
					cell->nbits + cell->bit_offset,
					BITS_PER_BYTE);

		अगर (!IS_ALIGNED(cell->offset, nvmem->stride)) अणु
			dev_err(dev, "cell %s unaligned to nvmem stride %d\n",
				cell->name, nvmem->stride);
			/* Cells alपढ़ोy added will be मुक्तd later. */
			kमुक्त_स्थिर(cell->name);
			of_node_put(cell->np);
			kमुक्त(cell);
			वापस -EINVAL;
		पूर्ण

		nvmem_cell_add(cell);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * nvmem_रेजिस्टर() - Register a nvmem device क्रम given nvmem_config.
 * Also creates a binary entry in /sys/bus/nvmem/devices/dev-name/nvmem
 *
 * @config: nvmem device configuration with which nvmem device is created.
 *
 * Return: Will be an ERR_PTR() on error or a valid poपूर्णांकer to nvmem_device
 * on success.
 */

काष्ठा nvmem_device *nvmem_रेजिस्टर(स्थिर काष्ठा nvmem_config *config)
अणु
	काष्ठा nvmem_device *nvmem;
	पूर्णांक rval;

	अगर (!config->dev)
		वापस ERR_PTR(-EINVAL);

	अगर (!config->reg_पढ़ो && !config->reg_ग_लिखो)
		वापस ERR_PTR(-EINVAL);

	nvmem = kzalloc(माप(*nvmem), GFP_KERNEL);
	अगर (!nvmem)
		वापस ERR_PTR(-ENOMEM);

	rval  = ida_alloc(&nvmem_ida, GFP_KERNEL);
	अगर (rval < 0) अणु
		kमुक्त(nvmem);
		वापस ERR_PTR(rval);
	पूर्ण

	अगर (config->wp_gpio)
		nvmem->wp_gpio = config->wp_gpio;
	अन्यथा
		nvmem->wp_gpio = gpiod_get_optional(config->dev, "wp",
						    GPIOD_OUT_HIGH);
	अगर (IS_ERR(nvmem->wp_gpio)) अणु
		ida_मुक्त(&nvmem_ida, nvmem->id);
		rval = PTR_ERR(nvmem->wp_gpio);
		kमुक्त(nvmem);
		वापस ERR_PTR(rval);
	पूर्ण

	kref_init(&nvmem->refcnt);
	INIT_LIST_HEAD(&nvmem->cells);

	nvmem->id = rval;
	nvmem->owner = config->owner;
	अगर (!nvmem->owner && config->dev->driver)
		nvmem->owner = config->dev->driver->owner;
	nvmem->stride = config->stride ?: 1;
	nvmem->word_size = config->word_size ?: 1;
	nvmem->size = config->size;
	nvmem->dev.type = &nvmem_provider_type;
	nvmem->dev.bus = &nvmem_bus_type;
	nvmem->dev.parent = config->dev;
	nvmem->root_only = config->root_only;
	nvmem->priv = config->priv;
	nvmem->type = config->type;
	nvmem->reg_पढ़ो = config->reg_पढ़ो;
	nvmem->reg_ग_लिखो = config->reg_ग_लिखो;
	nvmem->keepout = config->keepout;
	nvmem->nkeepout = config->nkeepout;
	अगर (!config->no_of_node)
		nvmem->dev.of_node = config->dev->of_node;

	चयन (config->id) अणु
	हाल NVMEM_DEVID_NONE:
		dev_set_name(&nvmem->dev, "%s", config->name);
		अवरोध;
	हाल NVMEM_DEVID_AUTO:
		dev_set_name(&nvmem->dev, "%s%d", config->name, nvmem->id);
		अवरोध;
	शेष:
		dev_set_name(&nvmem->dev, "%s%d",
			     config->name ? : "nvmem",
			     config->name ? config->id : nvmem->id);
		अवरोध;
	पूर्ण

	nvmem->पढ़ो_only = device_property_present(config->dev, "read-only") ||
			   config->पढ़ो_only || !nvmem->reg_ग_लिखो;

#अगर_घोषित CONFIG_NVMEM_SYSFS
	nvmem->dev.groups = nvmem_dev_groups;
#पूर्ण_अगर

	अगर (nvmem->nkeepout) अणु
		rval = nvmem_validate_keepouts(nvmem);
		अगर (rval)
			जाओ err_put_device;
	पूर्ण

	dev_dbg(&nvmem->dev, "Registering nvmem device %s\n", config->name);

	rval = device_रेजिस्टर(&nvmem->dev);
	अगर (rval)
		जाओ err_put_device;

	अगर (config->compat) अणु
		rval = nvmem_sysfs_setup_compat(nvmem, config);
		अगर (rval)
			जाओ err_device_del;
	पूर्ण

	अगर (config->cells) अणु
		rval = nvmem_add_cells(nvmem, config->cells, config->ncells);
		अगर (rval)
			जाओ err_tearकरोwn_compat;
	पूर्ण

	rval = nvmem_add_cells_from_table(nvmem);
	अगर (rval)
		जाओ err_हटाओ_cells;

	rval = nvmem_add_cells_from_of(nvmem);
	अगर (rval)
		जाओ err_हटाओ_cells;

	blocking_notअगरier_call_chain(&nvmem_notअगरier, NVMEM_ADD, nvmem);

	वापस nvmem;

err_हटाओ_cells:
	nvmem_device_हटाओ_all_cells(nvmem);
err_tearकरोwn_compat:
	अगर (config->compat)
		nvmem_sysfs_हटाओ_compat(nvmem, config);
err_device_del:
	device_del(&nvmem->dev);
err_put_device:
	put_device(&nvmem->dev);

	वापस ERR_PTR(rval);
पूर्ण
EXPORT_SYMBOL_GPL(nvmem_रेजिस्टर);

अटल व्योम nvmem_device_release(काष्ठा kref *kref)
अणु
	काष्ठा nvmem_device *nvmem;

	nvmem = container_of(kref, काष्ठा nvmem_device, refcnt);

	blocking_notअगरier_call_chain(&nvmem_notअगरier, NVMEM_REMOVE, nvmem);

	अगर (nvmem->flags & FLAG_COMPAT)
		device_हटाओ_bin_file(nvmem->base_dev, &nvmem->eeprom);

	nvmem_device_हटाओ_all_cells(nvmem);
	device_unरेजिस्टर(&nvmem->dev);
पूर्ण

/**
 * nvmem_unरेजिस्टर() - Unरेजिस्टर previously रेजिस्टरed nvmem device
 *
 * @nvmem: Poपूर्णांकer to previously रेजिस्टरed nvmem device.
 */
व्योम nvmem_unरेजिस्टर(काष्ठा nvmem_device *nvmem)
अणु
	kref_put(&nvmem->refcnt, nvmem_device_release);
पूर्ण
EXPORT_SYMBOL_GPL(nvmem_unरेजिस्टर);

अटल व्योम devm_nvmem_release(काष्ठा device *dev, व्योम *res)
अणु
	nvmem_unरेजिस्टर(*(काष्ठा nvmem_device **)res);
पूर्ण

/**
 * devm_nvmem_रेजिस्टर() - Register a managed nvmem device क्रम given
 * nvmem_config.
 * Also creates a binary entry in /sys/bus/nvmem/devices/dev-name/nvmem
 *
 * @dev: Device that uses the nvmem device.
 * @config: nvmem device configuration with which nvmem device is created.
 *
 * Return: Will be an ERR_PTR() on error or a valid poपूर्णांकer to nvmem_device
 * on success.
 */
काष्ठा nvmem_device *devm_nvmem_रेजिस्टर(काष्ठा device *dev,
					 स्थिर काष्ठा nvmem_config *config)
अणु
	काष्ठा nvmem_device **ptr, *nvmem;

	ptr = devres_alloc(devm_nvmem_release, माप(*ptr), GFP_KERNEL);
	अगर (!ptr)
		वापस ERR_PTR(-ENOMEM);

	nvmem = nvmem_रेजिस्टर(config);

	अगर (!IS_ERR(nvmem)) अणु
		*ptr = nvmem;
		devres_add(dev, ptr);
	पूर्ण अन्यथा अणु
		devres_मुक्त(ptr);
	पूर्ण

	वापस nvmem;
पूर्ण
EXPORT_SYMBOL_GPL(devm_nvmem_रेजिस्टर);

अटल पूर्णांक devm_nvmem_match(काष्ठा device *dev, व्योम *res, व्योम *data)
अणु
	काष्ठा nvmem_device **r = res;

	वापस *r == data;
पूर्ण

/**
 * devm_nvmem_unरेजिस्टर() - Unरेजिस्टर previously रेजिस्टरed managed nvmem
 * device.
 *
 * @dev: Device that uses the nvmem device.
 * @nvmem: Poपूर्णांकer to previously रेजिस्टरed nvmem device.
 *
 * Return: Will be negative on error or zero on success.
 */
पूर्णांक devm_nvmem_unरेजिस्टर(काष्ठा device *dev, काष्ठा nvmem_device *nvmem)
अणु
	वापस devres_release(dev, devm_nvmem_release, devm_nvmem_match, nvmem);
पूर्ण
EXPORT_SYMBOL(devm_nvmem_unरेजिस्टर);

अटल काष्ठा nvmem_device *__nvmem_device_get(व्योम *data,
			पूर्णांक (*match)(काष्ठा device *dev, स्थिर व्योम *data))
अणु
	काष्ठा nvmem_device *nvmem = शून्य;
	काष्ठा device *dev;

	mutex_lock(&nvmem_mutex);
	dev = bus_find_device(&nvmem_bus_type, शून्य, data, match);
	अगर (dev)
		nvmem = to_nvmem_device(dev);
	mutex_unlock(&nvmem_mutex);
	अगर (!nvmem)
		वापस ERR_PTR(-EPROBE_DEFER);

	अगर (!try_module_get(nvmem->owner)) अणु
		dev_err(&nvmem->dev,
			"could not increase module refcount for cell %s\n",
			nvmem_dev_name(nvmem));

		put_device(&nvmem->dev);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	kref_get(&nvmem->refcnt);

	वापस nvmem;
पूर्ण

अटल व्योम __nvmem_device_put(काष्ठा nvmem_device *nvmem)
अणु
	put_device(&nvmem->dev);
	module_put(nvmem->owner);
	kref_put(&nvmem->refcnt, nvmem_device_release);
पूर्ण

#अगर IS_ENABLED(CONFIG_OF)
/**
 * of_nvmem_device_get() - Get nvmem device from a given id
 *
 * @np: Device tree node that uses the nvmem device.
 * @id: nvmem name from nvmem-names property.
 *
 * Return: ERR_PTR() on error or a valid poपूर्णांकer to a काष्ठा nvmem_device
 * on success.
 */
काष्ठा nvmem_device *of_nvmem_device_get(काष्ठा device_node *np, स्थिर अक्षर *id)
अणु

	काष्ठा device_node *nvmem_np;
	काष्ठा nvmem_device *nvmem;
	पूर्णांक index = 0;

	अगर (id)
		index = of_property_match_string(np, "nvmem-names", id);

	nvmem_np = of_parse_phandle(np, "nvmem", index);
	अगर (!nvmem_np)
		वापस ERR_PTR(-ENOENT);

	nvmem = __nvmem_device_get(nvmem_np, device_match_of_node);
	of_node_put(nvmem_np);
	वापस nvmem;
पूर्ण
EXPORT_SYMBOL_GPL(of_nvmem_device_get);
#पूर्ण_अगर

/**
 * nvmem_device_get() - Get nvmem device from a given id
 *
 * @dev: Device that uses the nvmem device.
 * @dev_name: name of the requested nvmem device.
 *
 * Return: ERR_PTR() on error or a valid poपूर्णांकer to a काष्ठा nvmem_device
 * on success.
 */
काष्ठा nvmem_device *nvmem_device_get(काष्ठा device *dev, स्थिर अक्षर *dev_name)
अणु
	अगर (dev->of_node) अणु /* try dt first */
		काष्ठा nvmem_device *nvmem;

		nvmem = of_nvmem_device_get(dev->of_node, dev_name);

		अगर (!IS_ERR(nvmem) || PTR_ERR(nvmem) == -EPROBE_DEFER)
			वापस nvmem;

	पूर्ण

	वापस __nvmem_device_get((व्योम *)dev_name, device_match_name);
पूर्ण
EXPORT_SYMBOL_GPL(nvmem_device_get);

/**
 * nvmem_device_find() - Find nvmem device with matching function
 *
 * @data: Data to pass to match function
 * @match: Callback function to check device
 *
 * Return: ERR_PTR() on error or a valid poपूर्णांकer to a काष्ठा nvmem_device
 * on success.
 */
काष्ठा nvmem_device *nvmem_device_find(व्योम *data,
			पूर्णांक (*match)(काष्ठा device *dev, स्थिर व्योम *data))
अणु
	वापस __nvmem_device_get(data, match);
पूर्ण
EXPORT_SYMBOL_GPL(nvmem_device_find);

अटल पूर्णांक devm_nvmem_device_match(काष्ठा device *dev, व्योम *res, व्योम *data)
अणु
	काष्ठा nvmem_device **nvmem = res;

	अगर (WARN_ON(!nvmem || !*nvmem))
		वापस 0;

	वापस *nvmem == data;
पूर्ण

अटल व्योम devm_nvmem_device_release(काष्ठा device *dev, व्योम *res)
अणु
	nvmem_device_put(*(काष्ठा nvmem_device **)res);
पूर्ण

/**
 * devm_nvmem_device_put() - put alredy got nvmem device
 *
 * @dev: Device that uses the nvmem device.
 * @nvmem: poपूर्णांकer to nvmem device allocated by devm_nvmem_cell_get(),
 * that needs to be released.
 */
व्योम devm_nvmem_device_put(काष्ठा device *dev, काष्ठा nvmem_device *nvmem)
अणु
	पूर्णांक ret;

	ret = devres_release(dev, devm_nvmem_device_release,
			     devm_nvmem_device_match, nvmem);

	WARN_ON(ret);
पूर्ण
EXPORT_SYMBOL_GPL(devm_nvmem_device_put);

/**
 * nvmem_device_put() - put alredy got nvmem device
 *
 * @nvmem: poपूर्णांकer to nvmem device that needs to be released.
 */
व्योम nvmem_device_put(काष्ठा nvmem_device *nvmem)
अणु
	__nvmem_device_put(nvmem);
पूर्ण
EXPORT_SYMBOL_GPL(nvmem_device_put);

/**
 * devm_nvmem_device_get() - Get nvmem cell of device क्रमm a given id
 *
 * @dev: Device that requests the nvmem device.
 * @id: name id क्रम the requested nvmem device.
 *
 * Return: ERR_PTR() on error or a valid poपूर्णांकer to a काष्ठा nvmem_cell
 * on success.  The nvmem_cell will be मुक्तd by the स्वतःmatically once the
 * device is मुक्तd.
 */
काष्ठा nvmem_device *devm_nvmem_device_get(काष्ठा device *dev, स्थिर अक्षर *id)
अणु
	काष्ठा nvmem_device **ptr, *nvmem;

	ptr = devres_alloc(devm_nvmem_device_release, माप(*ptr), GFP_KERNEL);
	अगर (!ptr)
		वापस ERR_PTR(-ENOMEM);

	nvmem = nvmem_device_get(dev, id);
	अगर (!IS_ERR(nvmem)) अणु
		*ptr = nvmem;
		devres_add(dev, ptr);
	पूर्ण अन्यथा अणु
		devres_मुक्त(ptr);
	पूर्ण

	वापस nvmem;
पूर्ण
EXPORT_SYMBOL_GPL(devm_nvmem_device_get);

अटल काष्ठा nvmem_cell *
nvmem_cell_get_from_lookup(काष्ठा device *dev, स्थिर अक्षर *con_id)
अणु
	काष्ठा nvmem_cell *cell = ERR_PTR(-ENOENT);
	काष्ठा nvmem_cell_lookup *lookup;
	काष्ठा nvmem_device *nvmem;
	स्थिर अक्षर *dev_id;

	अगर (!dev)
		वापस ERR_PTR(-EINVAL);

	dev_id = dev_name(dev);

	mutex_lock(&nvmem_lookup_mutex);

	list_क्रम_each_entry(lookup, &nvmem_lookup_list, node) अणु
		अगर ((म_भेद(lookup->dev_id, dev_id) == 0) &&
		    (म_भेद(lookup->con_id, con_id) == 0)) अणु
			/* This is the right entry. */
			nvmem = __nvmem_device_get((व्योम *)lookup->nvmem_name,
						   device_match_name);
			अगर (IS_ERR(nvmem)) अणु
				/* Provider may not be रेजिस्टरed yet. */
				cell = ERR_CAST(nvmem);
				अवरोध;
			पूर्ण

			cell = nvmem_find_cell_by_name(nvmem,
						       lookup->cell_name);
			अगर (!cell) अणु
				__nvmem_device_put(nvmem);
				cell = ERR_PTR(-ENOENT);
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण

	mutex_unlock(&nvmem_lookup_mutex);
	वापस cell;
पूर्ण

#अगर IS_ENABLED(CONFIG_OF)
अटल काष्ठा nvmem_cell *
nvmem_find_cell_by_node(काष्ठा nvmem_device *nvmem, काष्ठा device_node *np)
अणु
	काष्ठा nvmem_cell *iter, *cell = शून्य;

	mutex_lock(&nvmem_mutex);
	list_क्रम_each_entry(iter, &nvmem->cells, node) अणु
		अगर (np == iter->np) अणु
			cell = iter;
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&nvmem_mutex);

	वापस cell;
पूर्ण

/**
 * of_nvmem_cell_get() - Get a nvmem cell from given device node and cell id
 *
 * @np: Device tree node that uses the nvmem cell.
 * @id: nvmem cell name from nvmem-cell-names property, or शून्य
 *      क्रम the cell at index 0 (the lone cell with no accompanying
 *      nvmem-cell-names property).
 *
 * Return: Will be an ERR_PTR() on error or a valid poपूर्णांकer
 * to a काष्ठा nvmem_cell.  The nvmem_cell will be मुक्तd by the
 * nvmem_cell_put().
 */
काष्ठा nvmem_cell *of_nvmem_cell_get(काष्ठा device_node *np, स्थिर अक्षर *id)
अणु
	काष्ठा device_node *cell_np, *nvmem_np;
	काष्ठा nvmem_device *nvmem;
	काष्ठा nvmem_cell *cell;
	पूर्णांक index = 0;

	/* अगर cell name exists, find index to the name */
	अगर (id)
		index = of_property_match_string(np, "nvmem-cell-names", id);

	cell_np = of_parse_phandle(np, "nvmem-cells", index);
	अगर (!cell_np)
		वापस ERR_PTR(-ENOENT);

	nvmem_np = of_get_next_parent(cell_np);
	अगर (!nvmem_np)
		वापस ERR_PTR(-EINVAL);

	nvmem = __nvmem_device_get(nvmem_np, device_match_of_node);
	of_node_put(nvmem_np);
	अगर (IS_ERR(nvmem))
		वापस ERR_CAST(nvmem);

	cell = nvmem_find_cell_by_node(nvmem, cell_np);
	अगर (!cell) अणु
		__nvmem_device_put(nvmem);
		वापस ERR_PTR(-ENOENT);
	पूर्ण

	वापस cell;
पूर्ण
EXPORT_SYMBOL_GPL(of_nvmem_cell_get);
#पूर्ण_अगर

/**
 * nvmem_cell_get() - Get nvmem cell of device क्रमm a given cell name
 *
 * @dev: Device that requests the nvmem cell.
 * @id: nvmem cell name to get (this corresponds with the name from the
 *      nvmem-cell-names property क्रम DT प्रणालीs and with the con_id from
 *      the lookup entry क्रम non-DT प्रणालीs).
 *
 * Return: Will be an ERR_PTR() on error or a valid poपूर्णांकer
 * to a काष्ठा nvmem_cell.  The nvmem_cell will be मुक्तd by the
 * nvmem_cell_put().
 */
काष्ठा nvmem_cell *nvmem_cell_get(काष्ठा device *dev, स्थिर अक्षर *id)
अणु
	काष्ठा nvmem_cell *cell;

	अगर (dev->of_node) अणु /* try dt first */
		cell = of_nvmem_cell_get(dev->of_node, id);
		अगर (!IS_ERR(cell) || PTR_ERR(cell) == -EPROBE_DEFER)
			वापस cell;
	पूर्ण

	/* शून्य cell id only allowed क्रम device tree; invalid otherwise */
	अगर (!id)
		वापस ERR_PTR(-EINVAL);

	वापस nvmem_cell_get_from_lookup(dev, id);
पूर्ण
EXPORT_SYMBOL_GPL(nvmem_cell_get);

अटल व्योम devm_nvmem_cell_release(काष्ठा device *dev, व्योम *res)
अणु
	nvmem_cell_put(*(काष्ठा nvmem_cell **)res);
पूर्ण

/**
 * devm_nvmem_cell_get() - Get nvmem cell of device क्रमm a given id
 *
 * @dev: Device that requests the nvmem cell.
 * @id: nvmem cell name id to get.
 *
 * Return: Will be an ERR_PTR() on error or a valid poपूर्णांकer
 * to a काष्ठा nvmem_cell.  The nvmem_cell will be मुक्तd by the
 * स्वतःmatically once the device is मुक्तd.
 */
काष्ठा nvmem_cell *devm_nvmem_cell_get(काष्ठा device *dev, स्थिर अक्षर *id)
अणु
	काष्ठा nvmem_cell **ptr, *cell;

	ptr = devres_alloc(devm_nvmem_cell_release, माप(*ptr), GFP_KERNEL);
	अगर (!ptr)
		वापस ERR_PTR(-ENOMEM);

	cell = nvmem_cell_get(dev, id);
	अगर (!IS_ERR(cell)) अणु
		*ptr = cell;
		devres_add(dev, ptr);
	पूर्ण अन्यथा अणु
		devres_मुक्त(ptr);
	पूर्ण

	वापस cell;
पूर्ण
EXPORT_SYMBOL_GPL(devm_nvmem_cell_get);

अटल पूर्णांक devm_nvmem_cell_match(काष्ठा device *dev, व्योम *res, व्योम *data)
अणु
	काष्ठा nvmem_cell **c = res;

	अगर (WARN_ON(!c || !*c))
		वापस 0;

	वापस *c == data;
पूर्ण

/**
 * devm_nvmem_cell_put() - Release previously allocated nvmem cell
 * from devm_nvmem_cell_get.
 *
 * @dev: Device that requests the nvmem cell.
 * @cell: Previously allocated nvmem cell by devm_nvmem_cell_get().
 */
व्योम devm_nvmem_cell_put(काष्ठा device *dev, काष्ठा nvmem_cell *cell)
अणु
	पूर्णांक ret;

	ret = devres_release(dev, devm_nvmem_cell_release,
				devm_nvmem_cell_match, cell);

	WARN_ON(ret);
पूर्ण
EXPORT_SYMBOL(devm_nvmem_cell_put);

/**
 * nvmem_cell_put() - Release previously allocated nvmem cell.
 *
 * @cell: Previously allocated nvmem cell by nvmem_cell_get().
 */
व्योम nvmem_cell_put(काष्ठा nvmem_cell *cell)
अणु
	काष्ठा nvmem_device *nvmem = cell->nvmem;

	__nvmem_device_put(nvmem);
पूर्ण
EXPORT_SYMBOL_GPL(nvmem_cell_put);

अटल व्योम nvmem_shअगरt_पढ़ो_buffer_in_place(काष्ठा nvmem_cell *cell, व्योम *buf)
अणु
	u8 *p, *b;
	पूर्णांक i, extra, bit_offset = cell->bit_offset;

	p = b = buf;
	अगर (bit_offset) अणु
		/* First shअगरt */
		*b++ >>= bit_offset;

		/* setup rest of the bytes अगर any */
		क्रम (i = 1; i < cell->bytes; i++) अणु
			/* Get bits from next byte and shअगरt them towards msb */
			*p |= *b << (BITS_PER_BYTE - bit_offset);

			p = b;
			*b++ >>= bit_offset;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* poपूर्णांक to the msb */
		p += cell->bytes - 1;
	पूर्ण

	/* result fits in less bytes */
	extra = cell->bytes - DIV_ROUND_UP(cell->nbits, BITS_PER_BYTE);
	जबतक (--extra >= 0)
		*p-- = 0;

	/* clear msb bits अगर any leftover in the last byte */
	*p &= GENMASK((cell->nbits%BITS_PER_BYTE) - 1, 0);
पूर्ण

अटल पूर्णांक __nvmem_cell_पढ़ो(काष्ठा nvmem_device *nvmem,
		      काष्ठा nvmem_cell *cell,
		      व्योम *buf, माप_प्रकार *len)
अणु
	पूर्णांक rc;

	rc = nvmem_reg_पढ़ो(nvmem, cell->offset, buf, cell->bytes);

	अगर (rc)
		वापस rc;

	/* shअगरt bits in-place */
	अगर (cell->bit_offset || cell->nbits)
		nvmem_shअगरt_पढ़ो_buffer_in_place(cell, buf);

	अगर (len)
		*len = cell->bytes;

	वापस 0;
पूर्ण

/**
 * nvmem_cell_पढ़ो() - Read a given nvmem cell
 *
 * @cell: nvmem cell to be पढ़ो.
 * @len: poपूर्णांकer to length of cell which will be populated on successful पढ़ो;
 *	 can be शून्य.
 *
 * Return: ERR_PTR() on error or a valid poपूर्णांकer to a buffer on success. The
 * buffer should be मुक्तd by the consumer with a kमुक्त().
 */
व्योम *nvmem_cell_पढ़ो(काष्ठा nvmem_cell *cell, माप_प्रकार *len)
अणु
	काष्ठा nvmem_device *nvmem = cell->nvmem;
	u8 *buf;
	पूर्णांक rc;

	अगर (!nvmem)
		वापस ERR_PTR(-EINVAL);

	buf = kzalloc(cell->bytes, GFP_KERNEL);
	अगर (!buf)
		वापस ERR_PTR(-ENOMEM);

	rc = __nvmem_cell_पढ़ो(nvmem, cell, buf, len);
	अगर (rc) अणु
		kमुक्त(buf);
		वापस ERR_PTR(rc);
	पूर्ण

	वापस buf;
पूर्ण
EXPORT_SYMBOL_GPL(nvmem_cell_पढ़ो);

अटल व्योम *nvmem_cell_prepare_ग_लिखो_buffer(काष्ठा nvmem_cell *cell,
					     u8 *_buf, पूर्णांक len)
अणु
	काष्ठा nvmem_device *nvmem = cell->nvmem;
	पूर्णांक i, rc, nbits, bit_offset = cell->bit_offset;
	u8 v, *p, *buf, *b, pbyte, pbits;

	nbits = cell->nbits;
	buf = kzalloc(cell->bytes, GFP_KERNEL);
	अगर (!buf)
		वापस ERR_PTR(-ENOMEM);

	स_नकल(buf, _buf, len);
	p = b = buf;

	अगर (bit_offset) अणु
		pbyte = *b;
		*b <<= bit_offset;

		/* setup the first byte with lsb bits from nvmem */
		rc = nvmem_reg_पढ़ो(nvmem, cell->offset, &v, 1);
		अगर (rc)
			जाओ err;
		*b++ |= GENMASK(bit_offset - 1, 0) & v;

		/* setup rest of the byte अगर any */
		क्रम (i = 1; i < cell->bytes; i++) अणु
			/* Get last byte bits and shअगरt them towards lsb */
			pbits = pbyte >> (BITS_PER_BYTE - 1 - bit_offset);
			pbyte = *b;
			p = b;
			*b <<= bit_offset;
			*b++ |= pbits;
		पूर्ण
	पूर्ण

	/* अगर it's not end on byte boundary */
	अगर ((nbits + bit_offset) % BITS_PER_BYTE) अणु
		/* setup the last byte with msb bits from nvmem */
		rc = nvmem_reg_पढ़ो(nvmem,
				    cell->offset + cell->bytes - 1, &v, 1);
		अगर (rc)
			जाओ err;
		*p |= GENMASK(7, (nbits + bit_offset) % BITS_PER_BYTE) & v;

	पूर्ण

	वापस buf;
err:
	kमुक्त(buf);
	वापस ERR_PTR(rc);
पूर्ण

/**
 * nvmem_cell_ग_लिखो() - Write to a given nvmem cell
 *
 * @cell: nvmem cell to be written.
 * @buf: Buffer to be written.
 * @len: length of buffer to be written to nvmem cell.
 *
 * Return: length of bytes written or negative on failure.
 */
पूर्णांक nvmem_cell_ग_लिखो(काष्ठा nvmem_cell *cell, व्योम *buf, माप_प्रकार len)
अणु
	काष्ठा nvmem_device *nvmem = cell->nvmem;
	पूर्णांक rc;

	अगर (!nvmem || nvmem->पढ़ो_only ||
	    (cell->bit_offset == 0 && len != cell->bytes))
		वापस -EINVAL;

	अगर (cell->bit_offset || cell->nbits) अणु
		buf = nvmem_cell_prepare_ग_लिखो_buffer(cell, buf, len);
		अगर (IS_ERR(buf))
			वापस PTR_ERR(buf);
	पूर्ण

	rc = nvmem_reg_ग_लिखो(nvmem, cell->offset, buf, cell->bytes);

	/* मुक्त the पंचांगp buffer */
	अगर (cell->bit_offset || cell->nbits)
		kमुक्त(buf);

	अगर (rc)
		वापस rc;

	वापस len;
पूर्ण
EXPORT_SYMBOL_GPL(nvmem_cell_ग_लिखो);

अटल पूर्णांक nvmem_cell_पढ़ो_common(काष्ठा device *dev, स्थिर अक्षर *cell_id,
				  व्योम *val, माप_प्रकार count)
अणु
	काष्ठा nvmem_cell *cell;
	व्योम *buf;
	माप_प्रकार len;

	cell = nvmem_cell_get(dev, cell_id);
	अगर (IS_ERR(cell))
		वापस PTR_ERR(cell);

	buf = nvmem_cell_पढ़ो(cell, &len);
	अगर (IS_ERR(buf)) अणु
		nvmem_cell_put(cell);
		वापस PTR_ERR(buf);
	पूर्ण
	अगर (len != count) अणु
		kमुक्त(buf);
		nvmem_cell_put(cell);
		वापस -EINVAL;
	पूर्ण
	स_नकल(val, buf, count);
	kमुक्त(buf);
	nvmem_cell_put(cell);

	वापस 0;
पूर्ण

/**
 * nvmem_cell_पढ़ो_u8() - Read a cell value as a u8
 *
 * @dev: Device that requests the nvmem cell.
 * @cell_id: Name of nvmem cell to पढ़ो.
 * @val: poपूर्णांकer to output value.
 *
 * Return: 0 on success or negative त्रुटि_सं.
 */
पूर्णांक nvmem_cell_पढ़ो_u8(काष्ठा device *dev, स्थिर अक्षर *cell_id, u8 *val)
अणु
	वापस nvmem_cell_पढ़ो_common(dev, cell_id, val, माप(*val));
पूर्ण
EXPORT_SYMBOL_GPL(nvmem_cell_पढ़ो_u8);

/**
 * nvmem_cell_पढ़ो_u16() - Read a cell value as a u16
 *
 * @dev: Device that requests the nvmem cell.
 * @cell_id: Name of nvmem cell to पढ़ो.
 * @val: poपूर्णांकer to output value.
 *
 * Return: 0 on success or negative त्रुटि_सं.
 */
पूर्णांक nvmem_cell_पढ़ो_u16(काष्ठा device *dev, स्थिर अक्षर *cell_id, u16 *val)
अणु
	वापस nvmem_cell_पढ़ो_common(dev, cell_id, val, माप(*val));
पूर्ण
EXPORT_SYMBOL_GPL(nvmem_cell_पढ़ो_u16);

/**
 * nvmem_cell_पढ़ो_u32() - Read a cell value as a u32
 *
 * @dev: Device that requests the nvmem cell.
 * @cell_id: Name of nvmem cell to पढ़ो.
 * @val: poपूर्णांकer to output value.
 *
 * Return: 0 on success or negative त्रुटि_सं.
 */
पूर्णांक nvmem_cell_पढ़ो_u32(काष्ठा device *dev, स्थिर अक्षर *cell_id, u32 *val)
अणु
	वापस nvmem_cell_पढ़ो_common(dev, cell_id, val, माप(*val));
पूर्ण
EXPORT_SYMBOL_GPL(nvmem_cell_पढ़ो_u32);

/**
 * nvmem_cell_पढ़ो_u64() - Read a cell value as a u64
 *
 * @dev: Device that requests the nvmem cell.
 * @cell_id: Name of nvmem cell to पढ़ो.
 * @val: poपूर्णांकer to output value.
 *
 * Return: 0 on success or negative त्रुटि_सं.
 */
पूर्णांक nvmem_cell_पढ़ो_u64(काष्ठा device *dev, स्थिर अक्षर *cell_id, u64 *val)
अणु
	वापस nvmem_cell_पढ़ो_common(dev, cell_id, val, माप(*val));
पूर्ण
EXPORT_SYMBOL_GPL(nvmem_cell_पढ़ो_u64);

अटल व्योम *nvmem_cell_पढ़ो_variable_common(काष्ठा device *dev,
					     स्थिर अक्षर *cell_id,
					     माप_प्रकार max_len, माप_प्रकार *len)
अणु
	काष्ठा nvmem_cell *cell;
	पूर्णांक nbits;
	व्योम *buf;

	cell = nvmem_cell_get(dev, cell_id);
	अगर (IS_ERR(cell))
		वापस cell;

	nbits = cell->nbits;
	buf = nvmem_cell_पढ़ो(cell, len);
	nvmem_cell_put(cell);
	अगर (IS_ERR(buf))
		वापस buf;

	/*
	 * If nbits is set then nvmem_cell_पढ़ो() can signअगरicantly exaggerate
	 * the length of the real data. Throw away the extra junk.
	 */
	अगर (nbits)
		*len = DIV_ROUND_UP(nbits, 8);

	अगर (*len > max_len) अणु
		kमुक्त(buf);
		वापस ERR_PTR(-दुस्फल);
	पूर्ण

	वापस buf;
पूर्ण

/**
 * nvmem_cell_पढ़ो_variable_le_u32() - Read up to 32-bits of data as a little endian number.
 *
 * @dev: Device that requests the nvmem cell.
 * @cell_id: Name of nvmem cell to पढ़ो.
 * @val: poपूर्णांकer to output value.
 *
 * Return: 0 on success or negative त्रुटि_सं.
 */
पूर्णांक nvmem_cell_पढ़ो_variable_le_u32(काष्ठा device *dev, स्थिर अक्षर *cell_id,
				    u32 *val)
अणु
	माप_प्रकार len;
	u8 *buf;
	पूर्णांक i;

	buf = nvmem_cell_पढ़ो_variable_common(dev, cell_id, माप(*val), &len);
	अगर (IS_ERR(buf))
		वापस PTR_ERR(buf);

	/* Copy w/ implicit endian conversion */
	*val = 0;
	क्रम (i = 0; i < len; i++)
		*val |= buf[i] << (8 * i);

	kमुक्त(buf);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nvmem_cell_पढ़ो_variable_le_u32);

/**
 * nvmem_cell_पढ़ो_variable_le_u64() - Read up to 64-bits of data as a little endian number.
 *
 * @dev: Device that requests the nvmem cell.
 * @cell_id: Name of nvmem cell to पढ़ो.
 * @val: poपूर्णांकer to output value.
 *
 * Return: 0 on success or negative त्रुटि_सं.
 */
पूर्णांक nvmem_cell_पढ़ो_variable_le_u64(काष्ठा device *dev, स्थिर अक्षर *cell_id,
				    u64 *val)
अणु
	माप_प्रकार len;
	u8 *buf;
	पूर्णांक i;

	buf = nvmem_cell_पढ़ो_variable_common(dev, cell_id, माप(*val), &len);
	अगर (IS_ERR(buf))
		वापस PTR_ERR(buf);

	/* Copy w/ implicit endian conversion */
	*val = 0;
	क्रम (i = 0; i < len; i++)
		*val |= (uपूर्णांक64_t)buf[i] << (8 * i);

	kमुक्त(buf);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nvmem_cell_पढ़ो_variable_le_u64);

/**
 * nvmem_device_cell_पढ़ो() - Read a given nvmem device and cell
 *
 * @nvmem: nvmem device to पढ़ो from.
 * @info: nvmem cell info to be पढ़ो.
 * @buf: buffer poपूर्णांकer which will be populated on successful पढ़ो.
 *
 * Return: length of successful bytes पढ़ो on success and negative
 * error code on error.
 */
sमाप_प्रकार nvmem_device_cell_पढ़ो(काष्ठा nvmem_device *nvmem,
			   काष्ठा nvmem_cell_info *info, व्योम *buf)
अणु
	काष्ठा nvmem_cell cell;
	पूर्णांक rc;
	sमाप_प्रकार len;

	अगर (!nvmem)
		वापस -EINVAL;

	rc = nvmem_cell_info_to_nvmem_cell_nodup(nvmem, info, &cell);
	अगर (rc)
		वापस rc;

	rc = __nvmem_cell_पढ़ो(nvmem, &cell, buf, &len);
	अगर (rc)
		वापस rc;

	वापस len;
पूर्ण
EXPORT_SYMBOL_GPL(nvmem_device_cell_पढ़ो);

/**
 * nvmem_device_cell_ग_लिखो() - Write cell to a given nvmem device
 *
 * @nvmem: nvmem device to be written to.
 * @info: nvmem cell info to be written.
 * @buf: buffer to be written to cell.
 *
 * Return: length of bytes written or negative error code on failure.
 */
पूर्णांक nvmem_device_cell_ग_लिखो(काष्ठा nvmem_device *nvmem,
			    काष्ठा nvmem_cell_info *info, व्योम *buf)
अणु
	काष्ठा nvmem_cell cell;
	पूर्णांक rc;

	अगर (!nvmem)
		वापस -EINVAL;

	rc = nvmem_cell_info_to_nvmem_cell_nodup(nvmem, info, &cell);
	अगर (rc)
		वापस rc;

	वापस nvmem_cell_ग_लिखो(&cell, buf, cell.bytes);
पूर्ण
EXPORT_SYMBOL_GPL(nvmem_device_cell_ग_लिखो);

/**
 * nvmem_device_पढ़ो() - Read from a given nvmem device
 *
 * @nvmem: nvmem device to पढ़ो from.
 * @offset: offset in nvmem device.
 * @bytes: number of bytes to पढ़ो.
 * @buf: buffer poपूर्णांकer which will be populated on successful पढ़ो.
 *
 * Return: length of successful bytes पढ़ो on success and negative
 * error code on error.
 */
पूर्णांक nvmem_device_पढ़ो(काष्ठा nvmem_device *nvmem,
		      अचिन्हित पूर्णांक offset,
		      माप_प्रकार bytes, व्योम *buf)
अणु
	पूर्णांक rc;

	अगर (!nvmem)
		वापस -EINVAL;

	rc = nvmem_reg_पढ़ो(nvmem, offset, buf, bytes);

	अगर (rc)
		वापस rc;

	वापस bytes;
पूर्ण
EXPORT_SYMBOL_GPL(nvmem_device_पढ़ो);

/**
 * nvmem_device_ग_लिखो() - Write cell to a given nvmem device
 *
 * @nvmem: nvmem device to be written to.
 * @offset: offset in nvmem device.
 * @bytes: number of bytes to ग_लिखो.
 * @buf: buffer to be written.
 *
 * Return: length of bytes written or negative error code on failure.
 */
पूर्णांक nvmem_device_ग_लिखो(काष्ठा nvmem_device *nvmem,
		       अचिन्हित पूर्णांक offset,
		       माप_प्रकार bytes, व्योम *buf)
अणु
	पूर्णांक rc;

	अगर (!nvmem)
		वापस -EINVAL;

	rc = nvmem_reg_ग_लिखो(nvmem, offset, buf, bytes);

	अगर (rc)
		वापस rc;


	वापस bytes;
पूर्ण
EXPORT_SYMBOL_GPL(nvmem_device_ग_लिखो);

/**
 * nvmem_add_cell_table() - रेजिस्टर a table of cell info entries
 *
 * @table: table of cell info entries
 */
व्योम nvmem_add_cell_table(काष्ठा nvmem_cell_table *table)
अणु
	mutex_lock(&nvmem_cell_mutex);
	list_add_tail(&table->node, &nvmem_cell_tables);
	mutex_unlock(&nvmem_cell_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(nvmem_add_cell_table);

/**
 * nvmem_del_cell_table() - हटाओ a previously रेजिस्टरed cell info table
 *
 * @table: table of cell info entries
 */
व्योम nvmem_del_cell_table(काष्ठा nvmem_cell_table *table)
अणु
	mutex_lock(&nvmem_cell_mutex);
	list_del(&table->node);
	mutex_unlock(&nvmem_cell_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(nvmem_del_cell_table);

/**
 * nvmem_add_cell_lookups() - रेजिस्टर a list of cell lookup entries
 *
 * @entries: array of cell lookup entries
 * @nentries: number of cell lookup entries in the array
 */
व्योम nvmem_add_cell_lookups(काष्ठा nvmem_cell_lookup *entries, माप_प्रकार nentries)
अणु
	पूर्णांक i;

	mutex_lock(&nvmem_lookup_mutex);
	क्रम (i = 0; i < nentries; i++)
		list_add_tail(&entries[i].node, &nvmem_lookup_list);
	mutex_unlock(&nvmem_lookup_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(nvmem_add_cell_lookups);

/**
 * nvmem_del_cell_lookups() - हटाओ a list of previously added cell lookup
 *                            entries
 *
 * @entries: array of cell lookup entries
 * @nentries: number of cell lookup entries in the array
 */
व्योम nvmem_del_cell_lookups(काष्ठा nvmem_cell_lookup *entries, माप_प्रकार nentries)
अणु
	पूर्णांक i;

	mutex_lock(&nvmem_lookup_mutex);
	क्रम (i = 0; i < nentries; i++)
		list_del(&entries[i].node);
	mutex_unlock(&nvmem_lookup_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(nvmem_del_cell_lookups);

/**
 * nvmem_dev_name() - Get the name of a given nvmem device.
 *
 * @nvmem: nvmem device.
 *
 * Return: name of the nvmem device.
 */
स्थिर अक्षर *nvmem_dev_name(काष्ठा nvmem_device *nvmem)
अणु
	वापस dev_name(&nvmem->dev);
पूर्ण
EXPORT_SYMBOL_GPL(nvmem_dev_name);

अटल पूर्णांक __init nvmem_init(व्योम)
अणु
	वापस bus_रेजिस्टर(&nvmem_bus_type);
पूर्ण

अटल व्योम __निकास nvmem_निकास(व्योम)
अणु
	bus_unरेजिस्टर(&nvmem_bus_type);
पूर्ण

subsys_initcall(nvmem_init);
module_निकास(nvmem_निकास);

MODULE_AUTHOR("Srinivas Kandagatla <srinivas.kandagatla@linaro.org");
MODULE_AUTHOR("Maxime Ripard <maxime.ripard@free-electrons.com");
MODULE_DESCRIPTION("nvmem Driver Core");
MODULE_LICENSE("GPL v2");
