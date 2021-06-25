<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Thunderbolt XDoमुख्य property support
 *
 * Copyright (C) 2017, Intel Corporation
 * Authors: Michael Jamet <michael.jamet@पूर्णांकel.com>
 *          Mika Westerberg <mika.westerberg@linux.पूर्णांकel.com>
 */

#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/uuid.h>
#समावेश <linux/thunderbolt.h>

काष्ठा tb_property_entry अणु
	u32 key_hi;
	u32 key_lo;
	u16 length;
	u8 reserved;
	u8 type;
	u32 value;
पूर्ण;

काष्ठा tb_property_rootdir_entry अणु
	u32 magic;
	u32 length;
	काष्ठा tb_property_entry entries[];
पूर्ण;

काष्ठा tb_property_dir_entry अणु
	u32 uuid[4];
	काष्ठा tb_property_entry entries[];
पूर्ण;

#घोषणा TB_PROPERTY_ROOTसूची_MAGIC	0x55584401

अटल काष्ठा tb_property_dir *__tb_property_parse_dir(स्थिर u32 *block,
	माप_प्रकार block_len, अचिन्हित पूर्णांक dir_offset, माप_प्रकार dir_len,
	bool is_root);

अटल अंतरभूत व्योम parse_dwdata(व्योम *dst, स्थिर व्योम *src, माप_प्रकार dwords)
अणु
	be32_to_cpu_array(dst, src, dwords);
पूर्ण

अटल अंतरभूत व्योम क्रमmat_dwdata(व्योम *dst, स्थिर व्योम *src, माप_प्रकार dwords)
अणु
	cpu_to_be32_array(dst, src, dwords);
पूर्ण

अटल bool tb_property_entry_valid(स्थिर काष्ठा tb_property_entry *entry,
				  माप_प्रकार block_len)
अणु
	चयन (entry->type) अणु
	हाल TB_PROPERTY_TYPE_सूचीECTORY:
	हाल TB_PROPERTY_TYPE_DATA:
	हाल TB_PROPERTY_TYPE_TEXT:
		अगर (entry->length > block_len)
			वापस false;
		अगर (entry->value + entry->length > block_len)
			वापस false;
		अवरोध;

	हाल TB_PROPERTY_TYPE_VALUE:
		अगर (entry->length != 1)
			वापस false;
		अवरोध;
	पूर्ण

	वापस true;
पूर्ण

अटल bool tb_property_key_valid(स्थिर अक्षर *key)
अणु
	वापस key && म_माप(key) <= TB_PROPERTY_KEY_SIZE;
पूर्ण

अटल काष्ठा tb_property *
tb_property_alloc(स्थिर अक्षर *key, क्रमागत tb_property_type type)
अणु
	काष्ठा tb_property *property;

	property = kzalloc(माप(*property), GFP_KERNEL);
	अगर (!property)
		वापस शून्य;

	म_नकल(property->key, key);
	property->type = type;
	INIT_LIST_HEAD(&property->list);

	वापस property;
पूर्ण

अटल काष्ठा tb_property *tb_property_parse(स्थिर u32 *block, माप_प्रकार block_len,
					स्थिर काष्ठा tb_property_entry *entry)
अणु
	अक्षर key[TB_PROPERTY_KEY_SIZE + 1];
	काष्ठा tb_property *property;
	काष्ठा tb_property_dir *dir;

	अगर (!tb_property_entry_valid(entry, block_len))
		वापस शून्य;

	parse_dwdata(key, entry, 2);
	key[TB_PROPERTY_KEY_SIZE] = '\0';

	property = tb_property_alloc(key, entry->type);
	अगर (!property)
		वापस शून्य;

	property->length = entry->length;

	चयन (property->type) अणु
	हाल TB_PROPERTY_TYPE_सूचीECTORY:
		dir = __tb_property_parse_dir(block, block_len, entry->value,
					      entry->length, false);
		अगर (!dir) अणु
			kमुक्त(property);
			वापस शून्य;
		पूर्ण
		property->value.dir = dir;
		अवरोध;

	हाल TB_PROPERTY_TYPE_DATA:
		property->value.data = kसुस्मृति(property->length, माप(u32),
					       GFP_KERNEL);
		अगर (!property->value.data) अणु
			kमुक्त(property);
			वापस शून्य;
		पूर्ण
		parse_dwdata(property->value.data, block + entry->value,
			     entry->length);
		अवरोध;

	हाल TB_PROPERTY_TYPE_TEXT:
		property->value.text = kसुस्मृति(property->length, माप(u32),
					       GFP_KERNEL);
		अगर (!property->value.text) अणु
			kमुक्त(property);
			वापस शून्य;
		पूर्ण
		parse_dwdata(property->value.text, block + entry->value,
			     entry->length);
		/* Force null termination */
		property->value.text[property->length * 4 - 1] = '\0';
		अवरोध;

	हाल TB_PROPERTY_TYPE_VALUE:
		property->value.immediate = entry->value;
		अवरोध;

	शेष:
		property->type = TB_PROPERTY_TYPE_UNKNOWN;
		अवरोध;
	पूर्ण

	वापस property;
पूर्ण

अटल काष्ठा tb_property_dir *__tb_property_parse_dir(स्थिर u32 *block,
	माप_प्रकार block_len, अचिन्हित पूर्णांक dir_offset, माप_प्रकार dir_len, bool is_root)
अणु
	स्थिर काष्ठा tb_property_entry *entries;
	माप_प्रकार i, content_len, nentries;
	अचिन्हित पूर्णांक content_offset;
	काष्ठा tb_property_dir *dir;

	dir = kzalloc(माप(*dir), GFP_KERNEL);
	अगर (!dir)
		वापस शून्य;

	अगर (is_root) अणु
		content_offset = dir_offset + 2;
		content_len = dir_len;
	पूर्ण अन्यथा अणु
		dir->uuid = kmemdup(&block[dir_offset], माप(*dir->uuid),
				    GFP_KERNEL);
		अगर (!dir->uuid) अणु
			tb_property_मुक्त_dir(dir);
			वापस शून्य;
		पूर्ण
		content_offset = dir_offset + 4;
		content_len = dir_len - 4; /* Length includes UUID */
	पूर्ण

	entries = (स्थिर काष्ठा tb_property_entry *)&block[content_offset];
	nentries = content_len / (माप(*entries) / 4);

	INIT_LIST_HEAD(&dir->properties);

	क्रम (i = 0; i < nentries; i++) अणु
		काष्ठा tb_property *property;

		property = tb_property_parse(block, block_len, &entries[i]);
		अगर (!property) अणु
			tb_property_मुक्त_dir(dir);
			वापस शून्य;
		पूर्ण

		list_add_tail(&property->list, &dir->properties);
	पूर्ण

	वापस dir;
पूर्ण

/**
 * tb_property_parse_dir() - Parses properties from given property block
 * @block: Property block to parse
 * @block_len: Number of dword elements in the property block
 *
 * This function parses the XDoमुख्य properties data block पूर्णांकo क्रमmat that
 * can be traversed using the helper functions provided by this module.
 * Upon success वापसs the parsed directory. In हाल of error वापसs
 * %शून्य. The resulting &काष्ठा tb_property_dir needs to be released by
 * calling tb_property_मुक्त_dir() when not needed anymore.
 *
 * The @block is expected to be root directory.
 */
काष्ठा tb_property_dir *tb_property_parse_dir(स्थिर u32 *block,
					      माप_प्रकार block_len)
अणु
	स्थिर काष्ठा tb_property_rootdir_entry *rootdir =
		(स्थिर काष्ठा tb_property_rootdir_entry *)block;

	अगर (rootdir->magic != TB_PROPERTY_ROOTसूची_MAGIC)
		वापस शून्य;
	अगर (rootdir->length > block_len)
		वापस शून्य;

	वापस __tb_property_parse_dir(block, block_len, 0, rootdir->length,
				       true);
पूर्ण

/**
 * tb_property_create_dir() - Creates new property directory
 * @uuid: UUID used to identअगरy the particular directory
 *
 * Creates new, empty property directory. If @uuid is %शून्य then the
 * directory is assumed to be root directory.
 */
काष्ठा tb_property_dir *tb_property_create_dir(स्थिर uuid_t *uuid)
अणु
	काष्ठा tb_property_dir *dir;

	dir = kzalloc(माप(*dir), GFP_KERNEL);
	अगर (!dir)
		वापस शून्य;

	INIT_LIST_HEAD(&dir->properties);
	अगर (uuid) अणु
		dir->uuid = kmemdup(uuid, माप(*dir->uuid), GFP_KERNEL);
		अगर (!dir->uuid) अणु
			kमुक्त(dir);
			वापस शून्य;
		पूर्ण
	पूर्ण

	वापस dir;
पूर्ण
EXPORT_SYMBOL_GPL(tb_property_create_dir);

अटल व्योम tb_property_मुक्त(काष्ठा tb_property *property)
अणु
	चयन (property->type) अणु
	हाल TB_PROPERTY_TYPE_सूचीECTORY:
		tb_property_मुक्त_dir(property->value.dir);
		अवरोध;

	हाल TB_PROPERTY_TYPE_DATA:
		kमुक्त(property->value.data);
		अवरोध;

	हाल TB_PROPERTY_TYPE_TEXT:
		kमुक्त(property->value.text);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	kमुक्त(property);
पूर्ण

/**
 * tb_property_मुक्त_dir() - Release memory allocated क्रम property directory
 * @dir: Directory to release
 *
 * This will release all the memory the directory occupies including all
 * descendants. It is OK to pass %शून्य @dir, then the function करोes
 * nothing.
 */
व्योम tb_property_मुक्त_dir(काष्ठा tb_property_dir *dir)
अणु
	काष्ठा tb_property *property, *पंचांगp;

	अगर (!dir)
		वापस;

	list_क्रम_each_entry_safe(property, पंचांगp, &dir->properties, list) अणु
		list_del(&property->list);
		tb_property_मुक्त(property);
	पूर्ण
	kमुक्त(dir->uuid);
	kमुक्त(dir);
पूर्ण
EXPORT_SYMBOL_GPL(tb_property_मुक्त_dir);

अटल माप_प्रकार tb_property_dir_length(स्थिर काष्ठा tb_property_dir *dir,
				     bool recurse, माप_प्रकार *data_len)
अणु
	स्थिर काष्ठा tb_property *property;
	माप_प्रकार len = 0;

	अगर (dir->uuid)
		len += माप(*dir->uuid) / 4;
	अन्यथा
		len += माप(काष्ठा tb_property_rootdir_entry) / 4;

	list_क्रम_each_entry(property, &dir->properties, list) अणु
		len += माप(काष्ठा tb_property_entry) / 4;

		चयन (property->type) अणु
		हाल TB_PROPERTY_TYPE_सूचीECTORY:
			अगर (recurse) अणु
				len += tb_property_dir_length(
					property->value.dir, recurse, data_len);
			पूर्ण
			/* Reserve dword padding after each directory */
			अगर (data_len)
				*data_len += 1;
			अवरोध;

		हाल TB_PROPERTY_TYPE_DATA:
		हाल TB_PROPERTY_TYPE_TEXT:
			अगर (data_len)
				*data_len += property->length;
			अवरोध;

		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	वापस len;
पूर्ण

अटल sमाप_प्रकार __tb_property_क्रमmat_dir(स्थिर काष्ठा tb_property_dir *dir,
	u32 *block, अचिन्हित पूर्णांक start_offset, माप_प्रकार block_len)
अणु
	अचिन्हित पूर्णांक data_offset, dir_end;
	स्थिर काष्ठा tb_property *property;
	काष्ठा tb_property_entry *entry;
	माप_प्रकार dir_len, data_len = 0;
	पूर्णांक ret;

	/*
	 * The काष्ठाure of property block looks like following. Leaf
	 * data/text is included right after the directory and each
	 * directory follows each other (even nested ones).
	 *
	 * +----------+ <-- start_offset
	 * |  header  | <-- root directory header
	 * +----------+ ---
	 * |  entry 0 | -^--------------------.
	 * +----------+  |                    |
	 * |  entry 1 | -|--------------------|--.
	 * +----------+  |                    |  |
	 * |  entry 2 | -|-----------------.  |  |
	 * +----------+  |                 |  |  |
	 * :          :  |  dir_len        |  |  |
	 * .          .  |                 |  |  |
	 * :          :  |                 |  |  |
	 * +----------+  |                 |  |  |
	 * |  entry n |  v                 |  |  |
	 * +----------+ <-- data_offset    |  |  |
	 * |  data 0  | <------------------|--'  |
	 * +----------+                    |     |
	 * |  data 1  | <------------------|-----'
	 * +----------+                    |
	 * | 00000000 | padding            |
	 * +----------+ <-- dir_end <------'
	 * |   UUID   | <-- directory UUID (child directory)
	 * +----------+
	 * |  entry 0 |
	 * +----------+
	 * |  entry 1 |
	 * +----------+
	 * :          :
	 * .          .
	 * :          :
	 * +----------+
	 * |  entry n |
	 * +----------+
	 * |  data 0  |
	 * +----------+
	 *
	 * We use dir_end to hold poपूर्णांकer to the end of the directory. It
	 * will increase as we add directories and each directory should be
	 * added starting from previous dir_end.
	 */
	dir_len = tb_property_dir_length(dir, false, &data_len);
	data_offset = start_offset + dir_len;
	dir_end = start_offset + data_len + dir_len;

	अगर (data_offset > dir_end)
		वापस -EINVAL;
	अगर (dir_end > block_len)
		वापस -EINVAL;

	/* Write headers first */
	अगर (dir->uuid) अणु
		काष्ठा tb_property_dir_entry *pe;

		pe = (काष्ठा tb_property_dir_entry *)&block[start_offset];
		स_नकल(pe->uuid, dir->uuid, माप(pe->uuid));
		entry = pe->entries;
	पूर्ण अन्यथा अणु
		काष्ठा tb_property_rootdir_entry *re;

		re = (काष्ठा tb_property_rootdir_entry *)&block[start_offset];
		re->magic = TB_PROPERTY_ROOTसूची_MAGIC;
		re->length = dir_len - माप(*re) / 4;
		entry = re->entries;
	पूर्ण

	list_क्रम_each_entry(property, &dir->properties, list) अणु
		स्थिर काष्ठा tb_property_dir *child;

		क्रमmat_dwdata(entry, property->key, 2);
		entry->type = property->type;

		चयन (property->type) अणु
		हाल TB_PROPERTY_TYPE_सूचीECTORY:
			child = property->value.dir;
			ret = __tb_property_क्रमmat_dir(child, block, dir_end,
						       block_len);
			अगर (ret < 0)
				वापस ret;
			entry->length = tb_property_dir_length(child, false,
							       शून्य);
			entry->value = dir_end;
			dir_end = ret;
			अवरोध;

		हाल TB_PROPERTY_TYPE_DATA:
			क्रमmat_dwdata(&block[data_offset], property->value.data,
				      property->length);
			entry->length = property->length;
			entry->value = data_offset;
			data_offset += entry->length;
			अवरोध;

		हाल TB_PROPERTY_TYPE_TEXT:
			क्रमmat_dwdata(&block[data_offset], property->value.text,
				      property->length);
			entry->length = property->length;
			entry->value = data_offset;
			data_offset += entry->length;
			अवरोध;

		हाल TB_PROPERTY_TYPE_VALUE:
			entry->length = property->length;
			entry->value = property->value.immediate;
			अवरोध;

		शेष:
			अवरोध;
		पूर्ण

		entry++;
	पूर्ण

	वापस dir_end;
पूर्ण

/**
 * tb_property_क्रमmat_dir() - Formats directory to the packed XDoमुख्य क्रमmat
 * @dir: Directory to क्रमmat
 * @block: Property block where the packed data is placed
 * @block_len: Length of the property block
 *
 * This function क्रमmats the directory to the packed क्रमmat that can be
 * then send over the thunderbolt fabric to receiving host. Returns %0 in
 * हाल of success and negative त्रुटि_सं on faulure. Passing %शून्य in @block
 * वापसs number of entries the block takes.
 */
sमाप_प्रकार tb_property_क्रमmat_dir(स्थिर काष्ठा tb_property_dir *dir, u32 *block,
			       माप_प्रकार block_len)
अणु
	sमाप_प्रकार ret;

	अगर (!block) अणु
		माप_प्रकार dir_len, data_len = 0;

		dir_len = tb_property_dir_length(dir, true, &data_len);
		वापस dir_len + data_len;
	पूर्ण

	ret = __tb_property_क्रमmat_dir(dir, block, 0, block_len);
	वापस ret < 0 ? ret : 0;
पूर्ण

/**
 * tb_property_copy_dir() - Take a deep copy of directory
 * @dir: Directory to copy
 *
 * This function takes a deep copy of @dir and वापसs back the copy. In
 * हाल of error वापसs %शून्य. The resulting directory needs to be
 * released by calling tb_property_मुक्त_dir().
 */
काष्ठा tb_property_dir *tb_property_copy_dir(स्थिर काष्ठा tb_property_dir *dir)
अणु
	काष्ठा tb_property *property, *p = शून्य;
	काष्ठा tb_property_dir *d;

	अगर (!dir)
		वापस शून्य;

	d = tb_property_create_dir(dir->uuid);
	अगर (!d)
		वापस शून्य;

	list_क्रम_each_entry(property, &dir->properties, list) अणु
		काष्ठा tb_property *p;

		p = tb_property_alloc(property->key, property->type);
		अगर (!p)
			जाओ err_मुक्त;

		p->length = property->length;

		चयन (property->type) अणु
		हाल TB_PROPERTY_TYPE_सूचीECTORY:
			p->value.dir = tb_property_copy_dir(property->value.dir);
			अगर (!p->value.dir)
				जाओ err_मुक्त;
			अवरोध;

		हाल TB_PROPERTY_TYPE_DATA:
			p->value.data = kmemdup(property->value.data,
						property->length * 4,
						GFP_KERNEL);
			अगर (!p->value.data)
				जाओ err_मुक्त;
			अवरोध;

		हाल TB_PROPERTY_TYPE_TEXT:
			p->value.text = kzalloc(p->length * 4, GFP_KERNEL);
			अगर (!p->value.text)
				जाओ err_मुक्त;
			म_नकल(p->value.text, property->value.text);
			अवरोध;

		हाल TB_PROPERTY_TYPE_VALUE:
			p->value.immediate = property->value.immediate;
			अवरोध;

		शेष:
			अवरोध;
		पूर्ण

		list_add_tail(&p->list, &d->properties);
	पूर्ण

	वापस d;

err_मुक्त:
	kमुक्त(p);
	tb_property_मुक्त_dir(d);

	वापस शून्य;
पूर्ण

/**
 * tb_property_add_immediate() - Add immediate property to directory
 * @parent: Directory to add the property
 * @key: Key क्रम the property
 * @value: Immediate value to store with the property
 */
पूर्णांक tb_property_add_immediate(काष्ठा tb_property_dir *parent, स्थिर अक्षर *key,
			      u32 value)
अणु
	काष्ठा tb_property *property;

	अगर (!tb_property_key_valid(key))
		वापस -EINVAL;

	property = tb_property_alloc(key, TB_PROPERTY_TYPE_VALUE);
	अगर (!property)
		वापस -ENOMEM;

	property->length = 1;
	property->value.immediate = value;

	list_add_tail(&property->list, &parent->properties);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(tb_property_add_immediate);

/**
 * tb_property_add_data() - Adds arbitrary data property to directory
 * @parent: Directory to add the property
 * @key: Key क्रम the property
 * @buf: Data buffer to add
 * @buflen: Number of bytes in the data buffer
 *
 * Function takes a copy of @buf and adds it to the directory.
 */
पूर्णांक tb_property_add_data(काष्ठा tb_property_dir *parent, स्थिर अक्षर *key,
			 स्थिर व्योम *buf, माप_प्रकार buflen)
अणु
	/* Need to pad to dword boundary */
	माप_प्रकार size = round_up(buflen, 4);
	काष्ठा tb_property *property;

	अगर (!tb_property_key_valid(key))
		वापस -EINVAL;

	property = tb_property_alloc(key, TB_PROPERTY_TYPE_DATA);
	अगर (!property)
		वापस -ENOMEM;

	property->length = size / 4;
	property->value.data = kzalloc(size, GFP_KERNEL);
	अगर (!property->value.data) अणु
		kमुक्त(property);
		वापस -ENOMEM;
	पूर्ण

	स_नकल(property->value.data, buf, buflen);

	list_add_tail(&property->list, &parent->properties);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(tb_property_add_data);

/**
 * tb_property_add_text() - Adds string property to directory
 * @parent: Directory to add the property
 * @key: Key क्रम the property
 * @text: String to add
 *
 * Function takes a copy of @text and adds it to the directory.
 */
पूर्णांक tb_property_add_text(काष्ठा tb_property_dir *parent, स्थिर अक्षर *key,
			 स्थिर अक्षर *text)
अणु
	/* Need to pad to dword boundary */
	माप_प्रकार size = round_up(म_माप(text) + 1, 4);
	काष्ठा tb_property *property;

	अगर (!tb_property_key_valid(key))
		वापस -EINVAL;

	property = tb_property_alloc(key, TB_PROPERTY_TYPE_TEXT);
	अगर (!property)
		वापस -ENOMEM;

	property->length = size / 4;
	property->value.text = kzalloc(size, GFP_KERNEL);
	अगर (!property->value.text) अणु
		kमुक्त(property);
		वापस -ENOMEM;
	पूर्ण

	म_नकल(property->value.text, text);

	list_add_tail(&property->list, &parent->properties);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(tb_property_add_text);

/**
 * tb_property_add_dir() - Adds a directory to the parent directory
 * @parent: Directory to add the property
 * @key: Key क्रम the property
 * @dir: Directory to add
 */
पूर्णांक tb_property_add_dir(काष्ठा tb_property_dir *parent, स्थिर अक्षर *key,
			काष्ठा tb_property_dir *dir)
अणु
	काष्ठा tb_property *property;

	अगर (!tb_property_key_valid(key))
		वापस -EINVAL;

	property = tb_property_alloc(key, TB_PROPERTY_TYPE_सूचीECTORY);
	अगर (!property)
		वापस -ENOMEM;

	property->value.dir = dir;

	list_add_tail(&property->list, &parent->properties);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(tb_property_add_dir);

/**
 * tb_property_हटाओ() - Removes property from a parent directory
 * @property: Property to हटाओ
 *
 * Note memory क्रम @property is released as well so it is not allowed to
 * touch the object after call to this function.
 */
व्योम tb_property_हटाओ(काष्ठा tb_property *property)
अणु
	list_del(&property->list);
	kमुक्त(property);
पूर्ण
EXPORT_SYMBOL_GPL(tb_property_हटाओ);

/**
 * tb_property_find() - Find a property from a directory
 * @dir: Directory where the property is searched
 * @key: Key to look क्रम
 * @type: Type of the property
 *
 * Finds and वापसs property from the given directory. Does not recurse
 * पूर्णांकo sub-directories. Returns %शून्य अगर the property was not found.
 */
काष्ठा tb_property *tb_property_find(काष्ठा tb_property_dir *dir,
	स्थिर अक्षर *key, क्रमागत tb_property_type type)
अणु
	काष्ठा tb_property *property;

	list_क्रम_each_entry(property, &dir->properties, list) अणु
		अगर (property->type == type && !म_भेद(property->key, key))
			वापस property;
	पूर्ण

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(tb_property_find);

/**
 * tb_property_get_next() - Get next property from directory
 * @dir: Directory holding properties
 * @prev: Previous property in the directory (%शून्य वापसs the first)
 */
काष्ठा tb_property *tb_property_get_next(काष्ठा tb_property_dir *dir,
					 काष्ठा tb_property *prev)
अणु
	अगर (prev) अणु
		अगर (list_is_last(&prev->list, &dir->properties))
			वापस शून्य;
		वापस list_next_entry(prev, list);
	पूर्ण
	वापस list_first_entry_or_null(&dir->properties, काष्ठा tb_property,
					list);
पूर्ण
EXPORT_SYMBOL_GPL(tb_property_get_next);
