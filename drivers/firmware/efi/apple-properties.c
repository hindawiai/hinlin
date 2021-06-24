<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * apple-properties.c - EFI device properties on Macs
 * Copyright (C) 2016 Lukas Wunner <lukas@wunner.de>
 *
 * Properties are stored either as:
 * u8 arrays which can be retrieved with device_property_पढ़ो_u8_array() or
 * booleans which can be queried with device_property_present().
 */

#घोषणा pr_fmt(fmt) "apple-properties: " fmt

#समावेश <linux/memblock.h>
#समावेश <linux/efi.h>
#समावेश <linux/पन.स>
#समावेश <linux/platक्रमm_data/x86/apple.h>
#समावेश <linux/property.h>
#समावेश <linux/slab.h>
#समावेश <linux/ucs2_माला.स>
#समावेश <यंत्र/setup.h>

अटल bool dump_properties __initdata;

अटल पूर्णांक __init dump_properties_enable(अक्षर *arg)
अणु
	dump_properties = true;
	वापस 0;
पूर्ण

__setup("dump_apple_properties", dump_properties_enable);

काष्ठा dev_header अणु
	u32 len;
	u32 prop_count;
	काष्ठा efi_dev_path path[];
	/*
	 * followed by key/value pairs, each key and value preceded by u32 len,
	 * len includes itself, value may be empty (in which हाल its len is 4)
	 */
पूर्ण;

काष्ठा properties_header अणु
	u32 len;
	u32 version;
	u32 dev_count;
	काष्ठा dev_header dev_header[];
पूर्ण;

अटल व्योम __init unmarshal_key_value_pairs(काष्ठा dev_header *dev_header,
					     काष्ठा device *dev, स्थिर व्योम *ptr,
					     काष्ठा property_entry entry[])
अणु
	पूर्णांक i;

	क्रम (i = 0; i < dev_header->prop_count; i++) अणु
		पूर्णांक reमुख्यing = dev_header->len - (ptr - (व्योम *)dev_header);
		u32 key_len, val_len, entry_len;
		स्थिर u8 *entry_data;
		अक्षर *key;

		अगर (माप(key_len) > reमुख्यing)
			अवरोध;

		key_len = *(typeof(key_len) *)ptr;
		अगर (key_len + माप(val_len) > reमुख्यing ||
		    key_len < माप(key_len) + माप(efi_अक्षर16_t) ||
		    *(efi_अक्षर16_t *)(ptr + माप(key_len)) == 0) अणु
			dev_err(dev, "invalid property name len at %#zx\n",
				ptr - (व्योम *)dev_header);
			अवरोध;
		पूर्ण

		val_len = *(typeof(val_len) *)(ptr + key_len);
		अगर (key_len + val_len > reमुख्यing ||
		    val_len < माप(val_len)) अणु
			dev_err(dev, "invalid property val len at %#zx\n",
				ptr - (व्योम *)dev_header + key_len);
			अवरोध;
		पूर्ण

		/* 4 bytes to accommodate UTF-8 code poपूर्णांकs + null byte */
		key = kzalloc((key_len - माप(key_len)) * 4 + 1, GFP_KERNEL);
		अगर (!key) अणु
			dev_err(dev, "cannot allocate property name\n");
			अवरोध;
		पूर्ण
		ucs2_as_utf8(key, ptr + माप(key_len),
			     key_len - माप(key_len));

		entry_data = ptr + key_len + माप(val_len);
		entry_len = val_len - माप(val_len);
		अगर (entry_len)
			entry[i] = PROPERTY_ENTRY_U8_ARRAY_LEN(key, entry_data,
							       entry_len);
		अन्यथा
			entry[i] = PROPERTY_ENTRY_BOOL(key);

		अगर (dump_properties) अणु
			dev_info(dev, "property: %s\n", key);
			prपूर्णांक_hex_dump(KERN_INFO, pr_fmt(), DUMP_PREFIX_OFFSET,
				16, 1, entry_data, entry_len, true);
		पूर्ण

		ptr += key_len + val_len;
	पूर्ण

	अगर (i != dev_header->prop_count) अणु
		dev_err(dev, "got %d device properties, expected %u\n", i,
			dev_header->prop_count);
		prपूर्णांक_hex_dump(KERN_ERR, pr_fmt(), DUMP_PREFIX_OFFSET,
			16, 1, dev_header, dev_header->len, true);
		वापस;
	पूर्ण

	dev_info(dev, "assigning %d device properties\n", i);
पूर्ण

अटल पूर्णांक __init unmarshal_devices(काष्ठा properties_header *properties)
अणु
	माप_प्रकार offset = दुरत्व(काष्ठा properties_header, dev_header[0]);

	जबतक (offset + माप(काष्ठा dev_header) < properties->len) अणु
		काष्ठा dev_header *dev_header = (व्योम *)properties + offset;
		काष्ठा property_entry *entry = शून्य;
		स्थिर काष्ठा efi_dev_path *ptr;
		काष्ठा device *dev;
		माप_प्रकार len;
		पूर्णांक ret, i;

		अगर (offset + dev_header->len > properties->len ||
		    dev_header->len <= माप(*dev_header)) अणु
			pr_err("invalid len in dev_header at %#zx\n", offset);
			वापस -EINVAL;
		पूर्ण

		ptr = dev_header->path;
		len = dev_header->len - माप(*dev_header);

		dev = efi_get_device_by_path(&ptr, &len);
		अगर (IS_ERR(dev)) अणु
			pr_err("device path parse error %ld at %#zx:\n",
			       PTR_ERR(dev), (व्योम *)ptr - (व्योम *)dev_header);
			prपूर्णांक_hex_dump(KERN_ERR, pr_fmt(), DUMP_PREFIX_OFFSET,
			       16, 1, dev_header, dev_header->len, true);
			dev = शून्य;
			जाओ skip_device;
		पूर्ण

		entry = kसुस्मृति(dev_header->prop_count + 1, माप(*entry),
				GFP_KERNEL);
		अगर (!entry) अणु
			dev_err(dev, "cannot allocate properties\n");
			जाओ skip_device;
		पूर्ण

		unmarshal_key_value_pairs(dev_header, dev, ptr, entry);
		अगर (!entry[0].name)
			जाओ skip_device;

		ret = device_add_properties(dev, entry); /* makes deep copy */
		अगर (ret)
			dev_err(dev, "error %d assigning properties\n", ret);

		क्रम (i = 0; entry[i].name; i++)
			kमुक्त(entry[i].name);

skip_device:
		kमुक्त(entry);
		put_device(dev);
		offset += dev_header->len;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __init map_properties(व्योम)
अणु
	काष्ठा properties_header *properties;
	काष्ठा setup_data *data;
	u32 data_len;
	u64 pa_data;
	पूर्णांक ret;

	अगर (!x86_apple_machine)
		वापस 0;

	pa_data = boot_params.hdr.setup_data;
	जबतक (pa_data) अणु
		data = memremap(pa_data, माप(*data), MEMREMAP_WB);
		अगर (!data) अणु
			pr_err("cannot map setup_data header\n");
			वापस -ENOMEM;
		पूर्ण

		अगर (data->type != SETUP_APPLE_PROPERTIES) अणु
			pa_data = data->next;
			memunmap(data);
			जारी;
		पूर्ण

		data_len = data->len;
		memunmap(data);

		data = memremap(pa_data, माप(*data) + data_len, MEMREMAP_WB);
		अगर (!data) अणु
			pr_err("cannot map setup_data payload\n");
			वापस -ENOMEM;
		पूर्ण

		properties = (काष्ठा properties_header *)data->data;
		अगर (properties->version != 1) अणु
			pr_err("unsupported version:\n");
			prपूर्णांक_hex_dump(KERN_ERR, pr_fmt(), DUMP_PREFIX_OFFSET,
			       16, 1, properties, data_len, true);
			ret = -ENOTSUPP;
		पूर्ण अन्यथा अगर (properties->len != data_len) अणु
			pr_err("length mismatch, expected %u\n", data_len);
			prपूर्णांक_hex_dump(KERN_ERR, pr_fmt(), DUMP_PREFIX_OFFSET,
			       16, 1, properties, data_len, true);
			ret = -EINVAL;
		पूर्ण अन्यथा
			ret = unmarshal_devices(properties);

		/*
		 * Can only मुक्त the setup_data payload but not its header
		 * to aव्योम अवरोधing the chain of ->next poपूर्णांकers.
		 */
		data->len = 0;
		memunmap(data);
		memblock_मुक्त_late(pa_data + माप(*data), data_len);

		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

fs_initcall(map_properties);
