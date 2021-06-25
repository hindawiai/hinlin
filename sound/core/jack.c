<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Jack असलtraction layer
 *
 *  Copyright 2008 Wolfson Microelectronics
 */

#समावेश <linux/input.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/mm.h>
#समावेश <linux/debugfs.h>
#समावेश <sound/jack.h>
#समावेश <sound/core.h>
#समावेश <sound/control.h>

काष्ठा snd_jack_kctl अणु
	काष्ठा snd_kcontrol *kctl;
	काष्ठा list_head list;  /* list of controls beदीर्घ to the same jack */
	अचिन्हित पूर्णांक mask_bits; /* only masked status bits are reported via kctl */
	काष्ठा snd_jack *jack;  /* poपूर्णांकer to काष्ठा snd_jack */
	bool sw_inject_enable;  /* allow to inject plug event via debugfs */
#अगर_घोषित CONFIG_SND_JACK_INJECTION_DEBUG
	काष्ठा dentry *jack_debugfs_root; /* jack_kctl debugfs root */
#पूर्ण_अगर
पूर्ण;

#अगर_घोषित CONFIG_SND_JACK_INPUT_DEV
अटल स्थिर पूर्णांक jack_चयन_types[SND_JACK_SWITCH_TYPES] = अणु
	SW_HEADPHONE_INSERT,
	SW_MICROPHONE_INSERT,
	SW_LINEOUT_INSERT,
	SW_JACK_PHYSICAL_INSERT,
	SW_VIDEOOUT_INSERT,
	SW_LINEIN_INSERT,
पूर्ण;
#पूर्ण_अगर /* CONFIG_SND_JACK_INPUT_DEV */

अटल पूर्णांक snd_jack_dev_disconnect(काष्ठा snd_device *device)
अणु
#अगर_घोषित CONFIG_SND_JACK_INPUT_DEV
	काष्ठा snd_jack *jack = device->device_data;

	अगर (!jack->input_dev)
		वापस 0;

	/* If the input device is रेजिस्टरed with the input subप्रणाली
	 * then we need to use a dअगरferent deallocator. */
	अगर (jack->रेजिस्टरed)
		input_unरेजिस्टर_device(jack->input_dev);
	अन्यथा
		input_मुक्त_device(jack->input_dev);
	jack->input_dev = शून्य;
#पूर्ण_अगर /* CONFIG_SND_JACK_INPUT_DEV */
	वापस 0;
पूर्ण

अटल पूर्णांक snd_jack_dev_मुक्त(काष्ठा snd_device *device)
अणु
	काष्ठा snd_jack *jack = device->device_data;
	काष्ठा snd_card *card = device->card;
	काष्ठा snd_jack_kctl *jack_kctl, *पंचांगp_jack_kctl;

	list_क्रम_each_entry_safe(jack_kctl, पंचांगp_jack_kctl, &jack->kctl_list, list) अणु
		list_del_init(&jack_kctl->list);
		snd_ctl_हटाओ(card, jack_kctl->kctl);
	पूर्ण
	अगर (jack->निजी_मुक्त)
		jack->निजी_मुक्त(jack);

	snd_jack_dev_disconnect(device);

	kमुक्त(jack->id);
	kमुक्त(jack);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_SND_JACK_INPUT_DEV
अटल पूर्णांक snd_jack_dev_रेजिस्टर(काष्ठा snd_device *device)
अणु
	काष्ठा snd_jack *jack = device->device_data;
	काष्ठा snd_card *card = device->card;
	पूर्णांक err, i;

	snम_लिखो(jack->name, माप(jack->name), "%s %s",
		 card->लघुname, jack->id);

	अगर (!jack->input_dev)
		वापस 0;

	jack->input_dev->name = jack->name;

	/* Default to the sound card device. */
	अगर (!jack->input_dev->dev.parent)
		jack->input_dev->dev.parent = snd_card_get_device_link(card);

	/* Add capabilities क्रम any keys that are enabled */
	क्रम (i = 0; i < ARRAY_SIZE(jack->key); i++) अणु
		पूर्णांक testbit = SND_JACK_BTN_0 >> i;

		अगर (!(jack->type & testbit))
			जारी;

		अगर (!jack->key[i])
			jack->key[i] = BTN_0 + i;

		input_set_capability(jack->input_dev, EV_KEY, jack->key[i]);
	पूर्ण

	err = input_रेजिस्टर_device(jack->input_dev);
	अगर (err == 0)
		jack->रेजिस्टरed = 1;

	वापस err;
पूर्ण
#पूर्ण_अगर /* CONFIG_SND_JACK_INPUT_DEV */

#अगर_घोषित CONFIG_SND_JACK_INJECTION_DEBUG
अटल व्योम snd_jack_inject_report(काष्ठा snd_jack_kctl *jack_kctl, पूर्णांक status)
अणु
	काष्ठा snd_jack *jack;
#अगर_घोषित CONFIG_SND_JACK_INPUT_DEV
	पूर्णांक i;
#पूर्ण_अगर
	अगर (!jack_kctl)
		वापस;

	jack = jack_kctl->jack;

	अगर (jack_kctl->sw_inject_enable)
		snd_kctl_jack_report(jack->card, jack_kctl->kctl,
				     status & jack_kctl->mask_bits);

#अगर_घोषित CONFIG_SND_JACK_INPUT_DEV
	अगर (!jack->input_dev)
		वापस;

	क्रम (i = 0; i < ARRAY_SIZE(jack->key); i++) अणु
		पूर्णांक testbit = ((SND_JACK_BTN_0 >> i) & jack_kctl->mask_bits);

		अगर (jack->type & testbit)
			input_report_key(jack->input_dev, jack->key[i],
					 status & testbit);
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(jack_चयन_types); i++) अणु
		पूर्णांक testbit = ((1 << i) & jack_kctl->mask_bits);

		अगर (jack->type & testbit)
			input_report_चयन(jack->input_dev,
					    jack_चयन_types[i],
					    status & testbit);
	पूर्ण

	input_sync(jack->input_dev);
#पूर्ण_अगर /* CONFIG_SND_JACK_INPUT_DEV */
पूर्ण

अटल sमाप_प्रकार sw_inject_enable_पढ़ो(काष्ठा file *file,
				     अक्षर __user *to, माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा snd_jack_kctl *jack_kctl = file->निजी_data;
	पूर्णांक len, ret;
	अक्षर buf[128];

	len = scnम_लिखो(buf, माप(buf), "%s: %s\t\t%s: %i\n", "Jack", jack_kctl->kctl->id.name,
			"Inject Enabled", jack_kctl->sw_inject_enable);
	ret = simple_पढ़ो_from_buffer(to, count, ppos, buf, len);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार sw_inject_enable_ग_लिखो(काष्ठा file *file,
				      स्थिर अक्षर __user *from, माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा snd_jack_kctl *jack_kctl = file->निजी_data;
	पूर्णांक ret, err;
	अचिन्हित दीर्घ enable;
	अक्षर buf[8] = अणु 0 पूर्ण;

	ret = simple_ग_लिखो_to_buffer(buf, माप(buf) - 1, ppos, from, count);
	err = kम_से_अदीर्घ(buf, 0, &enable);
	अगर (err)
		वापस err;

	अगर (jack_kctl->sw_inject_enable == (!!enable))
		वापस ret;

	jack_kctl->sw_inject_enable = !!enable;

	अगर (!jack_kctl->sw_inject_enable)
		snd_jack_report(jack_kctl->jack, jack_kctl->jack->hw_status_cache);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार jackin_inject_ग_लिखो(काष्ठा file *file,
				   स्थिर अक्षर __user *from, माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा snd_jack_kctl *jack_kctl = file->निजी_data;
	पूर्णांक ret, err;
	अचिन्हित दीर्घ enable;
	अक्षर buf[8] = अणु 0 पूर्ण;

	अगर (!jack_kctl->sw_inject_enable)
		वापस -EINVAL;

	ret = simple_ग_लिखो_to_buffer(buf, माप(buf) - 1, ppos, from, count);
	err = kम_से_अदीर्घ(buf, 0, &enable);
	अगर (err)
		वापस err;

	snd_jack_inject_report(jack_kctl, !!enable ? jack_kctl->mask_bits : 0);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार jack_kctl_id_पढ़ो(काष्ठा file *file,
				 अक्षर __user *to, माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा snd_jack_kctl *jack_kctl = file->निजी_data;
	अक्षर buf[64];
	पूर्णांक len, ret;

	len = scnम_लिखो(buf, माप(buf), "%s\n", jack_kctl->kctl->id.name);
	ret = simple_पढ़ो_from_buffer(to, count, ppos, buf, len);

	वापस ret;
पूर्ण

/* the bit definition is aligned with snd_jack_types in jack.h */
अटल स्थिर अक्षर * स्थिर jack_events_name[] = अणु
	"HEADPHONE(0x0001)", "MICROPHONE(0x0002)", "LINEOUT(0x0004)",
	"MECHANICAL(0x0008)", "VIDEOOUT(0x0010)", "LINEIN(0x0020)",
	"", "", "", "BTN_5(0x0200)", "BTN_4(0x0400)", "BTN_3(0x0800)",
	"BTN_2(0x1000)", "BTN_1(0x2000)", "BTN_0(0x4000)", "",
पूर्ण;

/* the recommended buffer size is 256 */
अटल पूर्णांक parse_mask_bits(अचिन्हित पूर्णांक mask_bits, अक्षर *buf, माप_प्रकार buf_size)
अणु
	पूर्णांक i;

	scnम_लिखो(buf, buf_size, "0x%04x", mask_bits);

	क्रम (i = 0; i < ARRAY_SIZE(jack_events_name); i++)
		अगर (mask_bits & (1 << i)) अणु
			strlcat(buf, " ", buf_size);
			strlcat(buf, jack_events_name[i], buf_size);
		पूर्ण
	strlcat(buf, "\n", buf_size);

	वापस म_माप(buf);
पूर्ण

अटल sमाप_प्रकार jack_kctl_mask_bits_पढ़ो(काष्ठा file *file,
					अक्षर __user *to, माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा snd_jack_kctl *jack_kctl = file->निजी_data;
	अक्षर buf[256];
	पूर्णांक len, ret;

	len = parse_mask_bits(jack_kctl->mask_bits, buf, माप(buf));
	ret = simple_पढ़ो_from_buffer(to, count, ppos, buf, len);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार jack_kctl_status_पढ़ो(काष्ठा file *file,
				     अक्षर __user *to, माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा snd_jack_kctl *jack_kctl = file->निजी_data;
	अक्षर buf[16];
	पूर्णांक len, ret;

	len = scnम_लिखो(buf, माप(buf), "%s\n", jack_kctl->kctl->निजी_value ?
			"Plugged" : "Unplugged");
	ret = simple_पढ़ो_from_buffer(to, count, ppos, buf, len);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_SND_JACK_INPUT_DEV
अटल sमाप_प्रकार jack_type_पढ़ो(काष्ठा file *file,
			      अक्षर __user *to, माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा snd_jack_kctl *jack_kctl = file->निजी_data;
	अक्षर buf[256];
	पूर्णांक len, ret;

	len = parse_mask_bits(jack_kctl->jack->type, buf, माप(buf));
	ret = simple_पढ़ो_from_buffer(to, count, ppos, buf, len);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations jack_type_fops = अणु
	.खोलो = simple_खोलो,
	.पढ़ो = jack_type_पढ़ो,
	.llseek = शेष_llseek,
पूर्ण;
#पूर्ण_अगर

अटल स्थिर काष्ठा file_operations sw_inject_enable_fops = अणु
	.खोलो = simple_खोलो,
	.पढ़ो = sw_inject_enable_पढ़ो,
	.ग_लिखो = sw_inject_enable_ग_लिखो,
	.llseek = शेष_llseek,
पूर्ण;

अटल स्थिर काष्ठा file_operations jackin_inject_fops = अणु
	.खोलो = simple_खोलो,
	.ग_लिखो = jackin_inject_ग_लिखो,
	.llseek = शेष_llseek,
पूर्ण;

अटल स्थिर काष्ठा file_operations jack_kctl_id_fops = अणु
	.खोलो = simple_खोलो,
	.पढ़ो = jack_kctl_id_पढ़ो,
	.llseek = शेष_llseek,
पूर्ण;

अटल स्थिर काष्ठा file_operations jack_kctl_mask_bits_fops = अणु
	.खोलो = simple_खोलो,
	.पढ़ो = jack_kctl_mask_bits_पढ़ो,
	.llseek = शेष_llseek,
पूर्ण;

अटल स्थिर काष्ठा file_operations jack_kctl_status_fops = अणु
	.खोलो = simple_खोलो,
	.पढ़ो = jack_kctl_status_पढ़ो,
	.llseek = शेष_llseek,
पूर्ण;

अटल पूर्णांक snd_jack_debugfs_add_inject_node(काष्ठा snd_jack *jack,
					    काष्ठा snd_jack_kctl *jack_kctl)
अणु
	अक्षर *tname;
	पूर्णांक i;

	/* Don't create injection पूर्णांकerface क्रम Phantom jacks */
	अगर (म_माला(jack_kctl->kctl->id.name, "Phantom"))
		वापस 0;

	tname = kstrdup(jack_kctl->kctl->id.name, GFP_KERNEL);
	अगर (!tname)
		वापस -ENOMEM;

	/* replace the अक्षरs which are not suitable क्रम folder's name with _ */
	क्रम (i = 0; tname[i]; i++)
		अगर (!है_अक्षर_अंक(tname[i]))
			tname[i] = '_';

	jack_kctl->jack_debugfs_root = debugfs_create_dir(tname, jack->card->debugfs_root);
	kमुक्त(tname);

	debugfs_create_file("sw_inject_enable", 0644, jack_kctl->jack_debugfs_root, jack_kctl,
			    &sw_inject_enable_fops);

	debugfs_create_file("jackin_inject", 0200, jack_kctl->jack_debugfs_root, jack_kctl,
			    &jackin_inject_fops);

	debugfs_create_file("kctl_id", 0444, jack_kctl->jack_debugfs_root, jack_kctl,
			    &jack_kctl_id_fops);

	debugfs_create_file("mask_bits", 0444, jack_kctl->jack_debugfs_root, jack_kctl,
			    &jack_kctl_mask_bits_fops);

	debugfs_create_file("status", 0444, jack_kctl->jack_debugfs_root, jack_kctl,
			    &jack_kctl_status_fops);

#अगर_घोषित CONFIG_SND_JACK_INPUT_DEV
	debugfs_create_file("type", 0444, jack_kctl->jack_debugfs_root, jack_kctl,
			    &jack_type_fops);
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल व्योम snd_jack_debugfs_clear_inject_node(काष्ठा snd_jack_kctl *jack_kctl)
अणु
	debugfs_हटाओ(jack_kctl->jack_debugfs_root);
	jack_kctl->jack_debugfs_root = शून्य;
पूर्ण
#अन्यथा /* CONFIG_SND_JACK_INJECTION_DEBUG */
अटल पूर्णांक snd_jack_debugfs_add_inject_node(काष्ठा snd_jack *jack,
					    काष्ठा snd_jack_kctl *jack_kctl)
अणु
	वापस 0;
पूर्ण

अटल व्योम snd_jack_debugfs_clear_inject_node(काष्ठा snd_jack_kctl *jack_kctl)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_SND_JACK_INJECTION_DEBUG */

अटल व्योम snd_jack_kctl_निजी_मुक्त(काष्ठा snd_kcontrol *kctl)
अणु
	काष्ठा snd_jack_kctl *jack_kctl;

	jack_kctl = kctl->निजी_data;
	अगर (jack_kctl) अणु
		snd_jack_debugfs_clear_inject_node(jack_kctl);
		list_del(&jack_kctl->list);
		kमुक्त(jack_kctl);
	पूर्ण
पूर्ण

अटल व्योम snd_jack_kctl_add(काष्ठा snd_jack *jack, काष्ठा snd_jack_kctl *jack_kctl)
अणु
	jack_kctl->jack = jack;
	list_add_tail(&jack_kctl->list, &jack->kctl_list);
	snd_jack_debugfs_add_inject_node(jack, jack_kctl);
पूर्ण

अटल काष्ठा snd_jack_kctl * snd_jack_kctl_new(काष्ठा snd_card *card, स्थिर अक्षर *name, अचिन्हित पूर्णांक mask)
अणु
	काष्ठा snd_kcontrol *kctl;
	काष्ठा snd_jack_kctl *jack_kctl;
	पूर्णांक err;

	kctl = snd_kctl_jack_new(name, card);
	अगर (!kctl)
		वापस शून्य;

	err = snd_ctl_add(card, kctl);
	अगर (err < 0)
		वापस शून्य;

	jack_kctl = kzalloc(माप(*jack_kctl), GFP_KERNEL);

	अगर (!jack_kctl)
		जाओ error;

	jack_kctl->kctl = kctl;
	jack_kctl->mask_bits = mask;

	kctl->निजी_data = jack_kctl;
	kctl->निजी_मुक्त = snd_jack_kctl_निजी_मुक्त;

	वापस jack_kctl;
error:
	snd_ctl_मुक्त_one(kctl);
	वापस शून्य;
पूर्ण

/**
 * snd_jack_add_new_kctl - Create a new snd_jack_kctl and add it to jack
 * @jack:  the jack instance which the kctl will attaching to
 * @name:  the name क्रम the snd_kcontrol object
 * @mask:  a biपंचांगask of क्रमागत snd_jack_type values that can be detected
 *         by this snd_jack_kctl object.
 *
 * Creates a new snd_kcontrol object and adds it to the jack kctl_list.
 *
 * Return: Zero अगर successful, or a negative error code on failure.
 */
पूर्णांक snd_jack_add_new_kctl(काष्ठा snd_jack *jack, स्थिर अक्षर * name, पूर्णांक mask)
अणु
	काष्ठा snd_jack_kctl *jack_kctl;

	jack_kctl = snd_jack_kctl_new(jack->card, name, mask);
	अगर (!jack_kctl)
		वापस -ENOMEM;

	snd_jack_kctl_add(jack, jack_kctl);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(snd_jack_add_new_kctl);

/**
 * snd_jack_new - Create a new jack
 * @card:  the card instance
 * @id:    an identअगरying string क्रम this jack
 * @type:  a biपंचांगask of क्रमागत snd_jack_type values that can be detected by
 *         this jack
 * @jjack: Used to provide the allocated jack object to the caller.
 * @initial_kctl: अगर true, create a kcontrol and add it to the jack list.
 * @phantom_jack: Don't create a input device क्रम phantom jacks.
 *
 * Creates a new jack object.
 *
 * Return: Zero अगर successful, or a negative error code on failure.
 * On success @jjack will be initialised.
 */
पूर्णांक snd_jack_new(काष्ठा snd_card *card, स्थिर अक्षर *id, पूर्णांक type,
		 काष्ठा snd_jack **jjack, bool initial_kctl, bool phantom_jack)
अणु
	काष्ठा snd_jack *jack;
	काष्ठा snd_jack_kctl *jack_kctl = शून्य;
	पूर्णांक err;
	अटल स्थिर काष्ठा snd_device_ops ops = अणु
		.dev_मुक्त = snd_jack_dev_मुक्त,
#अगर_घोषित CONFIG_SND_JACK_INPUT_DEV
		.dev_रेजिस्टर = snd_jack_dev_रेजिस्टर,
		.dev_disconnect = snd_jack_dev_disconnect,
#पूर्ण_अगर /* CONFIG_SND_JACK_INPUT_DEV */
	पूर्ण;

	अगर (initial_kctl) अणु
		jack_kctl = snd_jack_kctl_new(card, id, type);
		अगर (!jack_kctl)
			वापस -ENOMEM;
	पूर्ण

	jack = kzalloc(माप(काष्ठा snd_jack), GFP_KERNEL);
	अगर (jack == शून्य)
		वापस -ENOMEM;

	jack->id = kstrdup(id, GFP_KERNEL);

	/* करोn't creat input device क्रम phantom jack */
	अगर (!phantom_jack) अणु
#अगर_घोषित CONFIG_SND_JACK_INPUT_DEV
		पूर्णांक i;

		jack->input_dev = input_allocate_device();
		अगर (jack->input_dev == शून्य) अणु
			err = -ENOMEM;
			जाओ fail_input;
		पूर्ण

		jack->input_dev->phys = "ALSA";

		jack->type = type;

		क्रम (i = 0; i < SND_JACK_SWITCH_TYPES; i++)
			अगर (type & (1 << i))
				input_set_capability(jack->input_dev, EV_SW,
						     jack_चयन_types[i]);

#पूर्ण_अगर /* CONFIG_SND_JACK_INPUT_DEV */
	पूर्ण

	err = snd_device_new(card, SNDRV_DEV_JACK, jack, &ops);
	अगर (err < 0)
		जाओ fail_input;

	jack->card = card;
	INIT_LIST_HEAD(&jack->kctl_list);

	अगर (initial_kctl)
		snd_jack_kctl_add(jack, jack_kctl);

	*jjack = jack;

	वापस 0;

fail_input:
#अगर_घोषित CONFIG_SND_JACK_INPUT_DEV
	input_मुक्त_device(jack->input_dev);
#पूर्ण_अगर
	kमुक्त(jack->id);
	kमुक्त(jack);
	वापस err;
पूर्ण
EXPORT_SYMBOL(snd_jack_new);

#अगर_घोषित CONFIG_SND_JACK_INPUT_DEV
/**
 * snd_jack_set_parent - Set the parent device क्रम a jack
 *
 * @jack:   The jack to configure
 * @parent: The device to set as parent क्रम the jack.
 *
 * Set the parent क्रम the jack devices in the device tree.  This
 * function is only valid prior to registration of the jack.  If no
 * parent is configured then the parent device will be the sound card.
 */
व्योम snd_jack_set_parent(काष्ठा snd_jack *jack, काष्ठा device *parent)
अणु
	WARN_ON(jack->रेजिस्टरed);
	अगर (!jack->input_dev)
		वापस;

	jack->input_dev->dev.parent = parent;
पूर्ण
EXPORT_SYMBOL(snd_jack_set_parent);

/**
 * snd_jack_set_key - Set a key mapping on a jack
 *
 * @jack:    The jack to configure
 * @type:    Jack report type क्रम this key
 * @keytype: Input layer key type to be reported
 *
 * Map a SND_JACK_BTN_* button type to an input layer key, allowing
 * reporting of keys on accessories via the jack असलtraction.  If no
 * mapping is provided but keys are enabled in the jack type then
 * BTN_n numeric buttons will be reported.
 *
 * If jacks are not reporting via the input API this call will have no
 * effect.
 *
 * Note that this is पूर्णांकended to be use by simple devices with small
 * numbers of keys that can be reported.  It is also possible to
 * access the input device directly - devices with complex input
 * capabilities on accessories should consider करोing this rather than
 * using this असलtraction.
 *
 * This function may only be called prior to registration of the jack.
 *
 * Return: Zero अगर successful, or a negative error code on failure.
 */
पूर्णांक snd_jack_set_key(काष्ठा snd_jack *jack, क्रमागत snd_jack_types type,
		     पूर्णांक keytype)
अणु
	पूर्णांक key = fls(SND_JACK_BTN_0) - fls(type);

	WARN_ON(jack->रेजिस्टरed);

	अगर (!keytype || key >= ARRAY_SIZE(jack->key))
		वापस -EINVAL;

	jack->type |= type;
	jack->key[key] = keytype;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(snd_jack_set_key);
#पूर्ण_अगर /* CONFIG_SND_JACK_INPUT_DEV */

/**
 * snd_jack_report - Report the current status of a jack
 *
 * @jack:   The jack to report status क्रम
 * @status: The current status of the jack
 */
व्योम snd_jack_report(काष्ठा snd_jack *jack, पूर्णांक status)
अणु
	काष्ठा snd_jack_kctl *jack_kctl;
	अचिन्हित पूर्णांक mask_bits = 0;
#अगर_घोषित CONFIG_SND_JACK_INPUT_DEV
	पूर्णांक i;
#पूर्ण_अगर

	अगर (!jack)
		वापस;

	jack->hw_status_cache = status;

	list_क्रम_each_entry(jack_kctl, &jack->kctl_list, list)
		अगर (jack_kctl->sw_inject_enable)
			mask_bits |= jack_kctl->mask_bits;
		अन्यथा
			snd_kctl_jack_report(jack->card, jack_kctl->kctl,
					     status & jack_kctl->mask_bits);

#अगर_घोषित CONFIG_SND_JACK_INPUT_DEV
	अगर (!jack->input_dev)
		वापस;

	क्रम (i = 0; i < ARRAY_SIZE(jack->key); i++) अणु
		पूर्णांक testbit = ((SND_JACK_BTN_0 >> i) & ~mask_bits);

		अगर (jack->type & testbit)
			input_report_key(jack->input_dev, jack->key[i],
					 status & testbit);
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(jack_चयन_types); i++) अणु
		पूर्णांक testbit = ((1 << i) & ~mask_bits);

		अगर (jack->type & testbit)
			input_report_चयन(jack->input_dev,
					    jack_चयन_types[i],
					    status & testbit);
	पूर्ण

	input_sync(jack->input_dev);
#पूर्ण_अगर /* CONFIG_SND_JACK_INPUT_DEV */
पूर्ण
EXPORT_SYMBOL(snd_jack_report);
