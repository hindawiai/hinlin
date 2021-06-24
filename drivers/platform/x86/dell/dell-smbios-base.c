<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Common functions क्रम kernel modules using Dell SMBIOS
 *
 *  Copyright (c) Red Hat <mjg@redhat.com>
 *  Copyright (c) 2014 Gabriele Mazzotta <gabriele.mzt@gmail.com>
 *  Copyright (c) 2014 Pali Rohथँr <pali@kernel.org>
 *
 *  Based on करोcumentation in the libsmbios package:
 *  Copyright (C) 2005-2014 Dell Inc.
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/capability.h>
#समावेश <linux/dmi.h>
#समावेश <linux/err.h>
#समावेश <linux/mutex.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश "dell-smbios.h"

अटल u32 da_supported_commands;
अटल पूर्णांक da_num_tokens;
अटल काष्ठा platक्रमm_device *platक्रमm_device;
अटल काष्ठा calling_पूर्णांकerface_token *da_tokens;
अटल काष्ठा device_attribute *token_location_attrs;
अटल काष्ठा device_attribute *token_value_attrs;
अटल काष्ठा attribute **token_attrs;
अटल DEFINE_MUTEX(smbios_mutex);

काष्ठा smbios_device अणु
	काष्ठा list_head list;
	काष्ठा device *device;
	पूर्णांक (*call_fn)(काष्ठा calling_पूर्णांकerface_buffer *arg);
पूर्ण;

काष्ठा smbios_call अणु
	u32 need_capability;
	पूर्णांक cmd_class;
	पूर्णांक cmd_select;
पूर्ण;

/* calls that are whitelisted क्रम given capabilities */
अटल काष्ठा smbios_call call_whitelist[] = अणु
	/* generally tokens are allowed, but may be further filtered or
	 * restricted by token blacklist or whitelist
	 */
	अणुCAP_SYS_ADMIN,	CLASS_TOKEN_READ,	SELECT_TOKEN_STDपूर्ण,
	अणुCAP_SYS_ADMIN,	CLASS_TOKEN_READ,	SELECT_TOKEN_ACपूर्ण,
	अणुCAP_SYS_ADMIN,	CLASS_TOKEN_READ,	SELECT_TOKEN_BATपूर्ण,
	अणुCAP_SYS_ADMIN,	CLASS_TOKEN_WRITE,	SELECT_TOKEN_STDपूर्ण,
	अणुCAP_SYS_ADMIN,	CLASS_TOKEN_WRITE,	SELECT_TOKEN_ACपूर्ण,
	अणुCAP_SYS_ADMIN,	CLASS_TOKEN_WRITE,	SELECT_TOKEN_BATपूर्ण,
	/* used by userspace: fwupdate */
	अणुCAP_SYS_ADMIN, CLASS_ADMIN_PROP,	SELECT_ADMIN_PROPपूर्ण,
	/* used by userspace: fwupd */
	अणुCAP_SYS_ADMIN,	CLASS_INFO,		SELECT_DOCKपूर्ण,
	अणुCAP_SYS_ADMIN,	CLASS_FLASH_INTERFACE,	SELECT_FLASH_INTERFACEपूर्ण,
पूर्ण;

/* calls that are explicitly blacklisted */
अटल काष्ठा smbios_call call_blacklist[] = अणु
	अणु0x0000,  1,  7पूर्ण, /* manufacturing use */
	अणु0x0000,  6,  5पूर्ण, /* manufacturing use */
	अणु0x0000, 11,  3पूर्ण, /* ग_लिखो once */
	अणु0x0000, 11,  7पूर्ण, /* ग_लिखो once */
	अणु0x0000, 11, 11पूर्ण, /* ग_लिखो once */
	अणु0x0000, 19, -1पूर्ण, /* diagnostics */
	/* handled by kernel: dell-laptop */
	अणु0x0000, CLASS_INFO, SELECT_RFKILLपूर्ण,
	अणु0x0000, CLASS_KBD_BACKLIGHT, SELECT_KBD_BACKLIGHTपूर्ण,
पूर्ण;

काष्ठा token_range अणु
	u32 need_capability;
	u16 min;
	u16 max;
पूर्ण;

/* tokens that are whitelisted क्रम given capabilities */
अटल काष्ठा token_range token_whitelist[] = अणु
	/* used by userspace: fwupdate */
	अणुCAP_SYS_ADMIN,	CAPSULE_EN_TOKEN,	CAPSULE_DIS_TOKENपूर्ण,
	/* can indicate to userspace that WMI is needed */
	अणु0x0000,	WSMT_EN_TOKEN,		WSMT_DIS_TOKENपूर्ण
पूर्ण;

/* tokens that are explicitly blacklisted */
अटल काष्ठा token_range token_blacklist[] = अणु
	अणु0x0000, 0x0058, 0x0059पूर्ण, /* ME use */
	अणु0x0000, 0x00CD, 0x00D0पूर्ण, /* raid shaकरोw copy */
	अणु0x0000, 0x013A, 0x01FFपूर्ण, /* sata shaकरोw copy */
	अणु0x0000, 0x0175, 0x0176पूर्ण, /* ग_लिखो once */
	अणु0x0000, 0x0195, 0x0197पूर्ण, /* diagnostics */
	अणु0x0000, 0x01DC, 0x01DDपूर्ण, /* manufacturing use */
	अणु0x0000, 0x027D, 0x0284पूर्ण, /* diagnostics */
	अणु0x0000, 0x02E3, 0x02E3पूर्ण, /* manufacturing use */
	अणु0x0000, 0x02FF, 0x02FFपूर्ण, /* manufacturing use */
	अणु0x0000, 0x0300, 0x0302पूर्ण, /* manufacturing use */
	अणु0x0000, 0x0325, 0x0326पूर्ण, /* manufacturing use */
	अणु0x0000, 0x0332, 0x0335पूर्ण, /* fan control */
	अणु0x0000, 0x0350, 0x0350पूर्ण, /* manufacturing use */
	अणु0x0000, 0x0363, 0x0363पूर्ण, /* manufacturing use */
	अणु0x0000, 0x0368, 0x0368पूर्ण, /* manufacturing use */
	अणु0x0000, 0x03F6, 0x03F7पूर्ण, /* manufacturing use */
	अणु0x0000, 0x049E, 0x049Fपूर्ण, /* manufacturing use */
	अणु0x0000, 0x04A0, 0x04A3पूर्ण, /* disagnostics */
	अणु0x0000, 0x04E6, 0x04E7पूर्ण, /* manufacturing use */
	अणु0x0000, 0x4000, 0x7FFFपूर्ण, /* पूर्णांकernal BIOS use */
	अणु0x0000, 0x9000, 0x9001पूर्ण, /* पूर्णांकernal BIOS use */
	अणु0x0000, 0xA000, 0xBFFFपूर्ण, /* ग_लिखो only */
	अणु0x0000, 0xEFF0, 0xEFFFपूर्ण, /* पूर्णांकernal BIOS use */
	/* handled by kernel: dell-laptop */
	अणु0x0000, BRIGHTNESS_TOKEN,	BRIGHTNESS_TOKENपूर्ण,
	अणु0x0000, KBD_LED_OFF_TOKEN,	KBD_LED_AUTO_TOKENपूर्ण,
	अणु0x0000, KBD_LED_AC_TOKEN,	KBD_LED_AC_TOKENपूर्ण,
	अणु0x0000, KBD_LED_AUTO_25_TOKEN,	KBD_LED_AUTO_75_TOKENपूर्ण,
	अणु0x0000, KBD_LED_AUTO_100_TOKEN,	KBD_LED_AUTO_100_TOKENपूर्ण,
	अणु0x0000, GLOBAL_MIC_MUTE_ENABLE,	GLOBAL_MIC_MUTE_DISABLEपूर्ण,
पूर्ण;

अटल LIST_HEAD(smbios_device_list);

पूर्णांक dell_smbios_error(पूर्णांक value)
अणु
	चयन (value) अणु
	हाल 0: /* Completed successfully */
		वापस 0;
	हाल -1: /* Completed with error */
		वापस -EIO;
	हाल -2: /* Function not supported */
		वापस -ENXIO;
	शेष: /* Unknown error */
		वापस -EINVAL;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(dell_smbios_error);

पूर्णांक dell_smbios_रेजिस्टर_device(काष्ठा device *d, व्योम *call_fn)
अणु
	काष्ठा smbios_device *priv;

	priv = devm_kzalloc(d, माप(काष्ठा smbios_device), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;
	get_device(d);
	priv->device = d;
	priv->call_fn = call_fn;
	mutex_lock(&smbios_mutex);
	list_add_tail(&priv->list, &smbios_device_list);
	mutex_unlock(&smbios_mutex);
	dev_dbg(d, "Added device: %s\n", d->driver->name);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(dell_smbios_रेजिस्टर_device);

व्योम dell_smbios_unरेजिस्टर_device(काष्ठा device *d)
अणु
	काष्ठा smbios_device *priv;

	mutex_lock(&smbios_mutex);
	list_क्रम_each_entry(priv, &smbios_device_list, list) अणु
		अगर (priv->device == d) अणु
			list_del(&priv->list);
			put_device(d);
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&smbios_mutex);
	dev_dbg(d, "Remove device: %s\n", d->driver->name);
पूर्ण
EXPORT_SYMBOL_GPL(dell_smbios_unरेजिस्टर_device);

पूर्णांक dell_smbios_call_filter(काष्ठा device *d,
			    काष्ठा calling_पूर्णांकerface_buffer *buffer)
अणु
	u16 t = 0;
	पूर्णांक i;

	/* can't make calls over 30 */
	अगर (buffer->cmd_class > 30) अणु
		dev_dbg(d, "class too big: %u\n", buffer->cmd_class);
		वापस -EINVAL;
	पूर्ण

	/* supported calls on the particular प्रणाली */
	अगर (!(da_supported_commands & (1 << buffer->cmd_class))) अणु
		dev_dbg(d, "invalid command, supported commands: 0x%8x\n",
			da_supported_commands);
		वापस -EINVAL;
	पूर्ण

	/* match against call blacklist  */
	क्रम (i = 0; i < ARRAY_SIZE(call_blacklist); i++) अणु
		अगर (buffer->cmd_class != call_blacklist[i].cmd_class)
			जारी;
		अगर (buffer->cmd_select != call_blacklist[i].cmd_select &&
		    call_blacklist[i].cmd_select != -1)
			जारी;
		dev_dbg(d, "blacklisted command: %u/%u\n",
			buffer->cmd_class, buffer->cmd_select);
		वापस -EINVAL;
	पूर्ण

	/* अगर a token call, find token ID */

	अगर ((buffer->cmd_class == CLASS_TOKEN_READ ||
	     buffer->cmd_class == CLASS_TOKEN_WRITE) &&
	     buffer->cmd_select < 3) अणु
		/* tokens enabled ? */
		अगर (!da_tokens) अणु
			dev_dbg(d, "no token support on this system\n");
			वापस -EINVAL;
		पूर्ण

		/* find the matching token ID */
		क्रम (i = 0; i < da_num_tokens; i++) अणु
			अगर (da_tokens[i].location != buffer->input[0])
				जारी;
			t = da_tokens[i].tokenID;
			अवरोध;
		पूर्ण

		/* token call; but token didn't exist */
		अगर (!t) अणु
			dev_dbg(d, "token at location %04x doesn't exist\n",
				buffer->input[0]);
			वापस -EINVAL;
		पूर्ण

		/* match against token blacklist */
		क्रम (i = 0; i < ARRAY_SIZE(token_blacklist); i++) अणु
			अगर (!token_blacklist[i].min || !token_blacklist[i].max)
				जारी;
			अगर (t >= token_blacklist[i].min &&
			    t <= token_blacklist[i].max)
				वापस -EINVAL;
		पूर्ण

		/* match against token whitelist */
		क्रम (i = 0; i < ARRAY_SIZE(token_whitelist); i++) अणु
			अगर (!token_whitelist[i].min || !token_whitelist[i].max)
				जारी;
			अगर (t < token_whitelist[i].min ||
			    t > token_whitelist[i].max)
				जारी;
			अगर (!token_whitelist[i].need_capability ||
			    capable(token_whitelist[i].need_capability)) अणु
				dev_dbg(d, "whitelisted token: %x\n", t);
				वापस 0;
			पूर्ण

		पूर्ण
	पूर्ण
	/* match against call whitelist */
	क्रम (i = 0; i < ARRAY_SIZE(call_whitelist); i++) अणु
		अगर (buffer->cmd_class != call_whitelist[i].cmd_class)
			जारी;
		अगर (buffer->cmd_select != call_whitelist[i].cmd_select)
			जारी;
		अगर (!call_whitelist[i].need_capability ||
		    capable(call_whitelist[i].need_capability)) अणु
			dev_dbg(d, "whitelisted capable command: %u/%u\n",
			buffer->cmd_class, buffer->cmd_select);
			वापस 0;
		पूर्ण
		dev_dbg(d, "missing capability %d for %u/%u\n",
			call_whitelist[i].need_capability,
			buffer->cmd_class, buffer->cmd_select);

	पूर्ण

	/* not in a whitelist, only allow processes with capabilities */
	अगर (capable(CAP_SYS_RAWIO)) अणु
		dev_dbg(d, "Allowing %u/%u due to CAP_SYS_RAWIO\n",
			buffer->cmd_class, buffer->cmd_select);
		वापस 0;
	पूर्ण

	वापस -EACCES;
पूर्ण
EXPORT_SYMBOL_GPL(dell_smbios_call_filter);

पूर्णांक dell_smbios_call(काष्ठा calling_पूर्णांकerface_buffer *buffer)
अणु
	पूर्णांक (*call_fn)(काष्ठा calling_पूर्णांकerface_buffer *) = शून्य;
	काष्ठा device *selected_dev = शून्य;
	काष्ठा smbios_device *priv;
	पूर्णांक ret;

	mutex_lock(&smbios_mutex);
	list_क्रम_each_entry(priv, &smbios_device_list, list) अणु
		अगर (!selected_dev || priv->device->id >= selected_dev->id) अणु
			dev_dbg(priv->device, "Trying device ID: %d\n",
				priv->device->id);
			call_fn = priv->call_fn;
			selected_dev = priv->device;
		पूर्ण
	पूर्ण

	अगर (!selected_dev) अणु
		ret = -ENODEV;
		pr_err("No dell-smbios drivers are loaded\n");
		जाओ out_smbios_call;
	पूर्ण

	ret = call_fn(buffer);

out_smbios_call:
	mutex_unlock(&smbios_mutex);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(dell_smbios_call);

काष्ठा calling_पूर्णांकerface_token *dell_smbios_find_token(पूर्णांक tokenid)
अणु
	पूर्णांक i;

	अगर (!da_tokens)
		वापस शून्य;

	क्रम (i = 0; i < da_num_tokens; i++) अणु
		अगर (da_tokens[i].tokenID == tokenid)
			वापस &da_tokens[i];
	पूर्ण

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(dell_smbios_find_token);

अटल BLOCKING_NOTIFIER_HEAD(dell_laptop_chain_head);

पूर्णांक dell_laptop_रेजिस्टर_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस blocking_notअगरier_chain_रेजिस्टर(&dell_laptop_chain_head, nb);
पूर्ण
EXPORT_SYMBOL_GPL(dell_laptop_रेजिस्टर_notअगरier);

पूर्णांक dell_laptop_unरेजिस्टर_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस blocking_notअगरier_chain_unरेजिस्टर(&dell_laptop_chain_head, nb);
पूर्ण
EXPORT_SYMBOL_GPL(dell_laptop_unरेजिस्टर_notअगरier);

व्योम dell_laptop_call_notअगरier(अचिन्हित दीर्घ action, व्योम *data)
अणु
	blocking_notअगरier_call_chain(&dell_laptop_chain_head, action, data);
पूर्ण
EXPORT_SYMBOL_GPL(dell_laptop_call_notअगरier);

अटल व्योम __init parse_da_table(स्थिर काष्ठा dmi_header *dm)
अणु
	/* Final token is a terminator, so we करोn't want to copy it */
	पूर्णांक tokens = (dm->length-11)/माप(काष्ठा calling_पूर्णांकerface_token)-1;
	काष्ठा calling_पूर्णांकerface_token *new_da_tokens;
	काष्ठा calling_पूर्णांकerface_काष्ठाure *table =
		container_of(dm, काष्ठा calling_पूर्णांकerface_काष्ठाure, header);

	/*
	 * 4 bytes of table header, plus 7 bytes of Dell header
	 * plus at least 6 bytes of entry
	 */

	अगर (dm->length < 17)
		वापस;

	da_supported_commands = table->supportedCmds;

	new_da_tokens = kपुनः_स्मृति(da_tokens, (da_num_tokens + tokens) *
				 माप(काष्ठा calling_पूर्णांकerface_token),
				 GFP_KERNEL);

	अगर (!new_da_tokens)
		वापस;
	da_tokens = new_da_tokens;

	स_नकल(da_tokens+da_num_tokens, table->tokens,
	       माप(काष्ठा calling_पूर्णांकerface_token) * tokens);

	da_num_tokens += tokens;
पूर्ण

अटल व्योम zero_duplicates(काष्ठा device *dev)
अणु
	पूर्णांक i, j;

	क्रम (i = 0; i < da_num_tokens; i++) अणु
		अगर (da_tokens[i].tokenID == 0)
			जारी;
		क्रम (j = i+1; j < da_num_tokens; j++) अणु
			अगर (da_tokens[j].tokenID == 0)
				जारी;
			अगर (da_tokens[i].tokenID == da_tokens[j].tokenID) अणु
				dev_dbg(dev, "Zeroing dup token ID %x(%x/%x)\n",
					da_tokens[j].tokenID,
					da_tokens[j].location,
					da_tokens[j].value);
				da_tokens[j].tokenID = 0;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम __init find_tokens(स्थिर काष्ठा dmi_header *dm, व्योम *dummy)
अणु
	चयन (dm->type) अणु
	हाल 0xd4: /* Indexed IO */
	हाल 0xd5: /* Protected Area Type 1 */
	हाल 0xd6: /* Protected Area Type 2 */
		अवरोध;
	हाल 0xda: /* Calling पूर्णांकerface */
		parse_da_table(dm);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक match_attribute(काष्ठा device *dev,
			   काष्ठा device_attribute *attr)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < da_num_tokens * 2; i++) अणु
		अगर (!token_attrs[i])
			जारी;
		अगर (म_भेद(token_attrs[i]->name, attr->attr.name) == 0)
			वापस i/2;
	पूर्ण
	dev_dbg(dev, "couldn't match: %s\n", attr->attr.name);
	वापस -EINVAL;
पूर्ण

अटल sमाप_प्रकार location_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक i;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	i = match_attribute(dev, attr);
	अगर (i > 0)
		वापस scnम_लिखो(buf, PAGE_SIZE, "%08x", da_tokens[i].location);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार value_show(काष्ठा device *dev,
			  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक i;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	i = match_attribute(dev, attr);
	अगर (i > 0)
		वापस scnम_लिखो(buf, PAGE_SIZE, "%08x", da_tokens[i].value);
	वापस 0;
पूर्ण

अटल काष्ठा attribute_group smbios_attribute_group = अणु
	.name = "tokens"
पूर्ण;

अटल काष्ठा platक्रमm_driver platक्रमm_driver = अणु
	.driver = अणु
		.name = "dell-smbios",
	पूर्ण,
पूर्ण;

अटल पूर्णांक build_tokens_sysfs(काष्ठा platक्रमm_device *dev)
अणु
	अक्षर *location_name;
	अक्षर *value_name;
	माप_प्रकार size;
	पूर्णांक ret;
	पूर्णांक i, j;

	/* (number of tokens  + 1 क्रम null terminated */
	size = माप(काष्ठा device_attribute) * (da_num_tokens + 1);
	token_location_attrs = kzalloc(size, GFP_KERNEL);
	अगर (!token_location_attrs)
		वापस -ENOMEM;
	token_value_attrs = kzalloc(size, GFP_KERNEL);
	अगर (!token_value_attrs)
		जाओ out_allocate_value;

	/* need to store both location and value + terminator*/
	size = माप(काष्ठा attribute *) * ((2 * da_num_tokens) + 1);
	token_attrs = kzalloc(size, GFP_KERNEL);
	अगर (!token_attrs)
		जाओ out_allocate_attrs;

	क्रम (i = 0, j = 0; i < da_num_tokens; i++) अणु
		/* skip empty */
		अगर (da_tokens[i].tokenID == 0)
			जारी;
		/* add location */
		location_name = kaप्र_लिखो(GFP_KERNEL, "%04x_location",
					  da_tokens[i].tokenID);
		अगर (location_name == शून्य)
			जाओ out_unwind_strings;
		sysfs_attr_init(&token_location_attrs[i].attr);
		token_location_attrs[i].attr.name = location_name;
		token_location_attrs[i].attr.mode = 0444;
		token_location_attrs[i].show = location_show;
		token_attrs[j++] = &token_location_attrs[i].attr;

		/* add value */
		value_name = kaप्र_लिखो(GFP_KERNEL, "%04x_value",
				       da_tokens[i].tokenID);
		अगर (value_name == शून्य)
			जाओ loop_fail_create_value;
		sysfs_attr_init(&token_value_attrs[i].attr);
		token_value_attrs[i].attr.name = value_name;
		token_value_attrs[i].attr.mode = 0444;
		token_value_attrs[i].show = value_show;
		token_attrs[j++] = &token_value_attrs[i].attr;
		जारी;

loop_fail_create_value:
		kमुक्त(location_name);
		जाओ out_unwind_strings;
	पूर्ण
	smbios_attribute_group.attrs = token_attrs;

	ret = sysfs_create_group(&dev->dev.kobj, &smbios_attribute_group);
	अगर (ret)
		जाओ out_unwind_strings;
	वापस 0;

out_unwind_strings:
	जबतक (i--) अणु
		kमुक्त(token_location_attrs[i].attr.name);
		kमुक्त(token_value_attrs[i].attr.name);
	पूर्ण
	kमुक्त(token_attrs);
out_allocate_attrs:
	kमुक्त(token_value_attrs);
out_allocate_value:
	kमुक्त(token_location_attrs);

	वापस -ENOMEM;
पूर्ण

अटल व्योम मुक्त_group(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक i;

	sysfs_हटाओ_group(&pdev->dev.kobj,
				&smbios_attribute_group);
	क्रम (i = 0; i < da_num_tokens; i++) अणु
		kमुक्त(token_location_attrs[i].attr.name);
		kमुक्त(token_value_attrs[i].attr.name);
	पूर्ण
	kमुक्त(token_attrs);
	kमुक्त(token_value_attrs);
	kमुक्त(token_location_attrs);
पूर्ण

अटल पूर्णांक __init dell_smbios_init(व्योम)
अणु
	पूर्णांक ret, wmi, smm;

	अगर (!dmi_find_device(DMI_DEV_TYPE_OEM_STRING, "Dell System", शून्य) &&
	    !dmi_find_device(DMI_DEV_TYPE_OEM_STRING, "www.dell.com", शून्य)) अणु
		pr_err("Unable to run on non-Dell system\n");
		वापस -ENODEV;
	पूर्ण

	dmi_walk(find_tokens, शून्य);

	ret = platक्रमm_driver_रेजिस्टर(&platक्रमm_driver);
	अगर (ret)
		जाओ fail_platक्रमm_driver;

	platक्रमm_device = platक्रमm_device_alloc("dell-smbios", 0);
	अगर (!platक्रमm_device) अणु
		ret = -ENOMEM;
		जाओ fail_platक्रमm_device_alloc;
	पूर्ण
	ret = platक्रमm_device_add(platक्रमm_device);
	अगर (ret)
		जाओ fail_platक्रमm_device_add;

	/* रेजिस्टर backends */
	wmi = init_dell_smbios_wmi();
	अगर (wmi)
		pr_debug("Failed to initialize WMI backend: %d\n", wmi);
	smm = init_dell_smbios_smm();
	अगर (smm)
		pr_debug("Failed to initialize SMM backend: %d\n", smm);
	अगर (wmi && smm) अणु
		pr_err("No SMBIOS backends available (wmi: %d, smm: %d)\n",
			wmi, smm);
		ret = -ENODEV;
		जाओ fail_create_group;
	पूर्ण

	अगर (da_tokens)  अणु
		/* duplicate tokens will cause problems building sysfs files */
		zero_duplicates(&platक्रमm_device->dev);

		ret = build_tokens_sysfs(platक्रमm_device);
		अगर (ret)
			जाओ fail_sysfs;
	पूर्ण

	वापस 0;

fail_sysfs:
	मुक्त_group(platक्रमm_device);

fail_create_group:
	platक्रमm_device_del(platक्रमm_device);

fail_platक्रमm_device_add:
	platक्रमm_device_put(platक्रमm_device);

fail_platक्रमm_device_alloc:
	platक्रमm_driver_unरेजिस्टर(&platक्रमm_driver);

fail_platक्रमm_driver:
	kमुक्त(da_tokens);
	वापस ret;
पूर्ण

अटल व्योम __निकास dell_smbios_निकास(व्योम)
अणु
	निकास_dell_smbios_wmi();
	निकास_dell_smbios_smm();
	mutex_lock(&smbios_mutex);
	अगर (platक्रमm_device) अणु
		अगर (da_tokens)
			मुक्त_group(platक्रमm_device);
		platक्रमm_device_unरेजिस्टर(platक्रमm_device);
		platक्रमm_driver_unरेजिस्टर(&platक्रमm_driver);
	पूर्ण
	kमुक्त(da_tokens);
	mutex_unlock(&smbios_mutex);
पूर्ण

module_init(dell_smbios_init);
module_निकास(dell_smbios_निकास);

MODULE_AUTHOR("Matthew Garrett <mjg@redhat.com>");
MODULE_AUTHOR("Gabriele Mazzotta <gabriele.mzt@gmail.com>");
MODULE_AUTHOR("Pali Rohथँr <pali@kernel.org>");
MODULE_AUTHOR("Mario Limonciello <mario.limonciello@outlook.com>");
MODULE_DESCRIPTION("Common functions for kernel modules using Dell SMBIOS");
MODULE_LICENSE("GPL");
