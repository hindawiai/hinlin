<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  LED state routines क्रम driver control पूर्णांकerface
 *  Copyright (c) 2021 by Jaroslav Kysela <perex@perex.cz>
 */

#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/leds.h>
#समावेश <sound/core.h>
#समावेश <sound/control.h>

MODULE_AUTHOR("Jaroslav Kysela <perex@perex.cz>");
MODULE_DESCRIPTION("ALSA control interface to LED trigger code.");
MODULE_LICENSE("GPL");

#घोषणा MAX_LED (((SNDRV_CTL_ELEM_ACCESS_MIC_LED - SNDRV_CTL_ELEM_ACCESS_SPK_LED) \
			>> SNDRV_CTL_ELEM_ACCESS_LED_SHIFT) + 1)

#घोषणा to_led_card_dev(_dev) \
	container_of(_dev, काष्ठा snd_ctl_led_card, dev)

क्रमागत snd_ctl_led_mode अणु
	 MODE_FOLLOW_MUTE = 0,
	 MODE_FOLLOW_ROUTE,
	 MODE_OFF,
	 MODE_ON,
पूर्ण;

काष्ठा snd_ctl_led_card अणु
	काष्ठा device dev;
	पूर्णांक number;
	काष्ठा snd_ctl_led *led;
पूर्ण;

काष्ठा snd_ctl_led अणु
	काष्ठा device dev;
	काष्ठा list_head controls;
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक group;
	क्रमागत led_audio trigger_type;
	क्रमागत snd_ctl_led_mode mode;
	काष्ठा snd_ctl_led_card *cards[SNDRV_CARDS];
पूर्ण;

काष्ठा snd_ctl_led_ctl अणु
	काष्ठा list_head list;
	काष्ठा snd_card *card;
	अचिन्हित पूर्णांक access;
	काष्ठा snd_kcontrol *kctl;
	अचिन्हित पूर्णांक index_offset;
पूर्ण;

अटल DEFINE_MUTEX(snd_ctl_led_mutex);
अटल bool snd_ctl_led_card_valid[SNDRV_CARDS];
अटल काष्ठा snd_ctl_led snd_ctl_leds[MAX_LED] = अणु
	अणु
		.name = "speaker",
		.group = (SNDRV_CTL_ELEM_ACCESS_SPK_LED >> SNDRV_CTL_ELEM_ACCESS_LED_SHIFT) - 1,
		.trigger_type = LED_AUDIO_MUTE,
		.mode = MODE_FOLLOW_MUTE,
	पूर्ण,
	अणु
		.name = "mic",
		.group = (SNDRV_CTL_ELEM_ACCESS_MIC_LED >> SNDRV_CTL_ELEM_ACCESS_LED_SHIFT) - 1,
		.trigger_type = LED_AUDIO_MICMUTE,
		.mode = MODE_FOLLOW_MUTE,
	पूर्ण,
पूर्ण;

अटल व्योम snd_ctl_led_sysfs_add(काष्ठा snd_card *card);
अटल व्योम snd_ctl_led_sysfs_हटाओ(काष्ठा snd_card *card);

#घोषणा UPDATE_ROUTE(route, cb) \
	करो अणु \
		पूर्णांक route2 = (cb); \
		अगर (route2 >= 0) \
			route = route < 0 ? route2 : (route | route2); \
	पूर्ण जबतक (0)

अटल अंतरभूत अचिन्हित पूर्णांक access_to_group(अचिन्हित पूर्णांक access)
अणु
	वापस ((access & SNDRV_CTL_ELEM_ACCESS_LED_MASK) >>
				SNDRV_CTL_ELEM_ACCESS_LED_SHIFT) - 1;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक group_to_access(अचिन्हित पूर्णांक group)
अणु
	वापस (group + 1) << SNDRV_CTL_ELEM_ACCESS_LED_SHIFT;
पूर्ण

अटल काष्ठा snd_ctl_led *snd_ctl_led_get_by_access(अचिन्हित पूर्णांक access)
अणु
	अचिन्हित पूर्णांक group = access_to_group(access);
	अगर (group >= MAX_LED)
		वापस शून्य;
	वापस &snd_ctl_leds[group];
पूर्ण

/*
 * A note क्रम callers:
 *   The two अटल variables info and value are रक्षित using snd_ctl_led_mutex.
 */
अटल पूर्णांक snd_ctl_led_get(काष्ठा snd_ctl_led_ctl *lctl)
अणु
	अटल काष्ठा snd_ctl_elem_info info;
	अटल काष्ठा snd_ctl_elem_value value;
	काष्ठा snd_kcontrol *kctl = lctl->kctl;
	अचिन्हित पूर्णांक i;
	पूर्णांक result;

	स_रखो(&info, 0, माप(info));
	info.id = kctl->id;
	info.id.index += lctl->index_offset;
	info.id.numid += lctl->index_offset;
	result = kctl->info(kctl, &info);
	अगर (result < 0)
		वापस -1;
	स_रखो(&value, 0, माप(value));
	value.id = info.id;
	result = kctl->get(kctl, &value);
	अगर (result < 0)
		वापस -1;
	अगर (info.type == SNDRV_CTL_ELEM_TYPE_BOOLEAN ||
	    info.type == SNDRV_CTL_ELEM_TYPE_INTEGER) अणु
		क्रम (i = 0; i < info.count; i++)
			अगर (value.value.पूर्णांकeger.value[i] != info.value.पूर्णांकeger.min)
				वापस 1;
	पूर्ण अन्यथा अगर (info.type == SNDRV_CTL_ELEM_TYPE_INTEGER64) अणु
		क्रम (i = 0; i < info.count; i++)
			अगर (value.value.पूर्णांकeger64.value[i] != info.value.पूर्णांकeger64.min)
				वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम snd_ctl_led_set_state(काष्ठा snd_card *card, अचिन्हित पूर्णांक access,
				  काष्ठा snd_kcontrol *kctl, अचिन्हित पूर्णांक ioff)
अणु
	काष्ठा snd_ctl_led *led;
	काष्ठा snd_ctl_led_ctl *lctl;
	पूर्णांक route;
	bool found;

	led = snd_ctl_led_get_by_access(access);
	अगर (!led)
		वापस;
	route = -1;
	found = false;
	mutex_lock(&snd_ctl_led_mutex);
	/* the card may not be रेजिस्टरed (active) at this poपूर्णांक */
	अगर (card && !snd_ctl_led_card_valid[card->number]) अणु
		mutex_unlock(&snd_ctl_led_mutex);
		वापस;
	पूर्ण
	list_क्रम_each_entry(lctl, &led->controls, list) अणु
		अगर (lctl->kctl == kctl && lctl->index_offset == ioff)
			found = true;
		UPDATE_ROUTE(route, snd_ctl_led_get(lctl));
	पूर्ण
	अगर (!found && kctl && card) अणु
		lctl = kzalloc(माप(*lctl), GFP_KERNEL);
		अगर (lctl) अणु
			lctl->card = card;
			lctl->access = access;
			lctl->kctl = kctl;
			lctl->index_offset = ioff;
			list_add(&lctl->list, &led->controls);
			UPDATE_ROUTE(route, snd_ctl_led_get(lctl));
		पूर्ण
	पूर्ण
	mutex_unlock(&snd_ctl_led_mutex);
	चयन (led->mode) अणु
	हाल MODE_OFF:		route = 1; अवरोध;
	हाल MODE_ON:		route = 0; अवरोध;
	हाल MODE_FOLLOW_ROUTE:	अगर (route >= 0) route ^= 1; अवरोध;
	हाल MODE_FOLLOW_MUTE:	/* noop */ अवरोध;
	पूर्ण
	अगर (route >= 0)
		ledtrig_audio_set(led->trigger_type, route ? LED_OFF : LED_ON);
पूर्ण

अटल काष्ठा snd_ctl_led_ctl *snd_ctl_led_find(काष्ठा snd_kcontrol *kctl, अचिन्हित पूर्णांक ioff)
अणु
	काष्ठा list_head *controls;
	काष्ठा snd_ctl_led_ctl *lctl;
	अचिन्हित पूर्णांक group;

	क्रम (group = 0; group < MAX_LED; group++) अणु
		controls = &snd_ctl_leds[group].controls;
		list_क्रम_each_entry(lctl, controls, list)
			अगर (lctl->kctl == kctl && lctl->index_offset == ioff)
				वापस lctl;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल अचिन्हित पूर्णांक snd_ctl_led_हटाओ(काष्ठा snd_kcontrol *kctl, अचिन्हित पूर्णांक ioff,
				       अचिन्हित पूर्णांक access)
अणु
	काष्ठा snd_ctl_led_ctl *lctl;
	अचिन्हित पूर्णांक ret = 0;

	mutex_lock(&snd_ctl_led_mutex);
	lctl = snd_ctl_led_find(kctl, ioff);
	अगर (lctl && (access == 0 || access != lctl->access)) अणु
		ret = lctl->access;
		list_del(&lctl->list);
		kमुक्त(lctl);
	पूर्ण
	mutex_unlock(&snd_ctl_led_mutex);
	वापस ret;
पूर्ण

अटल व्योम snd_ctl_led_notअगरy(काष्ठा snd_card *card, अचिन्हित पूर्णांक mask,
			       काष्ठा snd_kcontrol *kctl, अचिन्हित पूर्णांक ioff)
अणु
	काष्ठा snd_kcontrol_अस्थिर *vd;
	अचिन्हित पूर्णांक access, access2;

	अगर (mask == SNDRV_CTL_EVENT_MASK_REMOVE) अणु
		access = snd_ctl_led_हटाओ(kctl, ioff, 0);
		अगर (access)
			snd_ctl_led_set_state(card, access, शून्य, 0);
	पूर्ण अन्यथा अगर (mask & SNDRV_CTL_EVENT_MASK_INFO) अणु
		vd = &kctl->vd[ioff];
		access = vd->access & SNDRV_CTL_ELEM_ACCESS_LED_MASK;
		access2 = snd_ctl_led_हटाओ(kctl, ioff, access);
		अगर (access2)
			snd_ctl_led_set_state(card, access2, शून्य, 0);
		अगर (access)
			snd_ctl_led_set_state(card, access, kctl, ioff);
	पूर्ण अन्यथा अगर ((mask & (SNDRV_CTL_EVENT_MASK_ADD |
			    SNDRV_CTL_EVENT_MASK_VALUE)) != 0) अणु
		vd = &kctl->vd[ioff];
		access = vd->access & SNDRV_CTL_ELEM_ACCESS_LED_MASK;
		अगर (access)
			snd_ctl_led_set_state(card, access, kctl, ioff);
	पूर्ण
पूर्ण

अटल पूर्णांक snd_ctl_led_set_id(पूर्णांक card_number, काष्ठा snd_ctl_elem_id *id,
			      अचिन्हित पूर्णांक group, bool set)
अणु
	काष्ठा snd_card *card;
	काष्ठा snd_kcontrol *kctl;
	काष्ठा snd_kcontrol_अस्थिर *vd;
	अचिन्हित पूर्णांक ioff, access, new_access;
	पूर्णांक err = 0;

	card = snd_card_ref(card_number);
	अगर (card) अणु
		करोwn_ग_लिखो(&card->controls_rwsem);
		kctl = snd_ctl_find_id(card, id);
		अगर (kctl) अणु
			ioff = snd_ctl_get_ioff(kctl, id);
			vd = &kctl->vd[ioff];
			access = vd->access & SNDRV_CTL_ELEM_ACCESS_LED_MASK;
			अगर (access != 0 && access != group_to_access(group)) अणु
				err = -EXDEV;
				जाओ unlock;
			पूर्ण
			new_access = vd->access & ~SNDRV_CTL_ELEM_ACCESS_LED_MASK;
			अगर (set)
				new_access |= group_to_access(group);
			अगर (new_access != vd->access) अणु
				vd->access = new_access;
				snd_ctl_led_notअगरy(card, SNDRV_CTL_EVENT_MASK_INFO, kctl, ioff);
			पूर्ण
		पूर्ण अन्यथा अणु
			err = -ENOENT;
		पूर्ण
unlock:
		up_ग_लिखो(&card->controls_rwsem);
		snd_card_unref(card);
	पूर्ण अन्यथा अणु
		err = -ENXIO;
	पूर्ण
	वापस err;
पूर्ण

अटल व्योम snd_ctl_led_refresh(व्योम)
अणु
	अचिन्हित पूर्णांक group;

	क्रम (group = 0; group < MAX_LED; group++)
		snd_ctl_led_set_state(शून्य, group_to_access(group), शून्य, 0);
पूर्ण

अटल व्योम snd_ctl_led_ctl_destroy(काष्ठा snd_ctl_led_ctl *lctl)
अणु
	list_del(&lctl->list);
	kमुक्त(lctl);
पूर्ण

अटल व्योम snd_ctl_led_clean(काष्ठा snd_card *card)
अणु
	अचिन्हित पूर्णांक group;
	काष्ठा snd_ctl_led *led;
	काष्ठा snd_ctl_led_ctl *lctl;

	क्रम (group = 0; group < MAX_LED; group++) अणु
		led = &snd_ctl_leds[group];
repeat:
		list_क्रम_each_entry(lctl, &led->controls, list)
			अगर (!card || lctl->card == card) अणु
				snd_ctl_led_ctl_destroy(lctl);
				जाओ repeat;
			पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक snd_ctl_led_reset(पूर्णांक card_number, अचिन्हित पूर्णांक group)
अणु
	काष्ठा snd_card *card;
	काष्ठा snd_ctl_led *led;
	काष्ठा snd_ctl_led_ctl *lctl;
	काष्ठा snd_kcontrol_अस्थिर *vd;
	bool change = false;

	card = snd_card_ref(card_number);
	अगर (!card)
		वापस -ENXIO;

	mutex_lock(&snd_ctl_led_mutex);
	अगर (!snd_ctl_led_card_valid[card_number]) अणु
		mutex_unlock(&snd_ctl_led_mutex);
		snd_card_unref(card);
		वापस -ENXIO;
	पूर्ण
	led = &snd_ctl_leds[group];
repeat:
	list_क्रम_each_entry(lctl, &led->controls, list)
		अगर (lctl->card == card) अणु
			vd = &lctl->kctl->vd[lctl->index_offset];
			vd->access &= ~group_to_access(group);
			snd_ctl_led_ctl_destroy(lctl);
			change = true;
			जाओ repeat;
		पूर्ण
	mutex_unlock(&snd_ctl_led_mutex);
	अगर (change)
		snd_ctl_led_set_state(शून्य, group_to_access(group), शून्य, 0);
	snd_card_unref(card);
	वापस 0;
पूर्ण

अटल व्योम snd_ctl_led_रेजिस्टर(काष्ठा snd_card *card)
अणु
	काष्ठा snd_kcontrol *kctl;
	अचिन्हित पूर्णांक ioff;

	अगर (snd_BUG_ON(card->number < 0 ||
		       card->number >= ARRAY_SIZE(snd_ctl_led_card_valid)))
		वापस;
	mutex_lock(&snd_ctl_led_mutex);
	snd_ctl_led_card_valid[card->number] = true;
	mutex_unlock(&snd_ctl_led_mutex);
	/* the रेजिस्टर callback is alपढ़ोy called with held card->controls_rwsem */
	list_क्रम_each_entry(kctl, &card->controls, list)
		क्रम (ioff = 0; ioff < kctl->count; ioff++)
			snd_ctl_led_notअगरy(card, SNDRV_CTL_EVENT_MASK_VALUE, kctl, ioff);
	snd_ctl_led_refresh();
	snd_ctl_led_sysfs_add(card);
पूर्ण

अटल व्योम snd_ctl_led_disconnect(काष्ठा snd_card *card)
अणु
	snd_ctl_led_sysfs_हटाओ(card);
	mutex_lock(&snd_ctl_led_mutex);
	snd_ctl_led_card_valid[card->number] = false;
	snd_ctl_led_clean(card);
	mutex_unlock(&snd_ctl_led_mutex);
	snd_ctl_led_refresh();
पूर्ण

अटल व्योम snd_ctl_led_card_release(काष्ठा device *dev)
अणु
	काष्ठा snd_ctl_led_card *led_card = to_led_card_dev(dev);

	kमुक्त(led_card);
पूर्ण

अटल व्योम snd_ctl_led_release(काष्ठा device *dev)
अणु
पूर्ण

अटल व्योम snd_ctl_led_dev_release(काष्ठा device *dev)
अणु
पूर्ण

/*
 * sysfs
 */

अटल sमाप_प्रकार show_mode(काष्ठा device *dev,
			 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा snd_ctl_led *led = container_of(dev, काष्ठा snd_ctl_led, dev);
	स्थिर अक्षर *str;

	चयन (led->mode) अणु
	हाल MODE_FOLLOW_MUTE:	str = "follow-mute"; अवरोध;
	हाल MODE_FOLLOW_ROUTE:	str = "follow-route"; अवरोध;
	हाल MODE_ON:		str = "on"; अवरोध;
	हाल MODE_OFF:		str = "off"; अवरोध;
	पूर्ण
	वापस प्र_लिखो(buf, "%s\n", str);
पूर्ण

अटल sमाप_प्रकार store_mode(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा snd_ctl_led *led = container_of(dev, काष्ठा snd_ctl_led, dev);
	अक्षर _buf[16];
	माप_प्रकार l = min(count, माप(_buf) - 1);
	क्रमागत snd_ctl_led_mode mode;

	स_नकल(_buf, buf, l);
	_buf[l] = '\0';
	अगर (म_माला(_buf, "mute"))
		mode = MODE_FOLLOW_MUTE;
	अन्यथा अगर (म_माला(_buf, "route"))
		mode = MODE_FOLLOW_ROUTE;
	अन्यथा अगर (म_भेदन(_buf, "off", 3) == 0 || म_भेदन(_buf, "0", 1) == 0)
		mode = MODE_OFF;
	अन्यथा अगर (म_भेदन(_buf, "on", 2) == 0 || म_भेदन(_buf, "1", 1) == 0)
		mode = MODE_ON;
	अन्यथा
		वापस count;

	mutex_lock(&snd_ctl_led_mutex);
	led->mode = mode;
	mutex_unlock(&snd_ctl_led_mutex);

	snd_ctl_led_set_state(शून्य, group_to_access(led->group), शून्य, 0);
	वापस count;
पूर्ण

अटल sमाप_प्रकार show_brightness(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा snd_ctl_led *led = container_of(dev, काष्ठा snd_ctl_led, dev);

	वापस प्र_लिखो(buf, "%u\n", ledtrig_audio_get(led->trigger_type));
पूर्ण

अटल DEVICE_ATTR(mode, 0644, show_mode, store_mode);
अटल DEVICE_ATTR(brightness, 0444, show_brightness, शून्य);

अटल काष्ठा attribute *snd_ctl_led_dev_attrs[] = अणु
	&dev_attr_mode.attr,
	&dev_attr_brightness.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group snd_ctl_led_dev_attr_group = अणु
	.attrs = snd_ctl_led_dev_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *snd_ctl_led_dev_attr_groups[] = अणु
	&snd_ctl_led_dev_attr_group,
	शून्य,
पूर्ण;

अटल अक्षर *find_eos(अक्षर *s)
अणु
	जबतक (*s && *s != ',')
		s++;
	अगर (*s)
		s++;
	वापस s;
पूर्ण

अटल अक्षर *parse_uपूर्णांक(अक्षर *s, अचिन्हित पूर्णांक *val)
अणु
	अचिन्हित दीर्घ दीर्घ res;
	अगर (kम_से_अदीर्घl(s, 10, &res))
		res = 0;
	*val = res;
	वापस find_eos(s);
पूर्ण

अटल अक्षर *parse_string(अक्षर *s, अक्षर *val, माप_प्रकार val_size)
अणु
	अगर (*s == '"' || *s == '\'') अणु
		अक्षर c = *s;
		s++;
		जबतक (*s && *s != c) अणु
			अगर (val_size > 1) अणु
				*val++ = *s;
				val_size--;
			पूर्ण
			s++;
		पूर्ण
	पूर्ण अन्यथा अणु
		जबतक (*s && *s != ',') अणु
			अगर (val_size > 1) अणु
				*val++ = *s;
				val_size--;
			पूर्ण
			s++;
		पूर्ण
	पूर्ण
	*val = '\0';
	अगर (*s)
		s++;
	वापस s;
पूर्ण

अटल अक्षर *parse_अगरace(अक्षर *s, अचिन्हित पूर्णांक *val)
अणु
	अगर (!strnहालcmp(s, "card", 4))
		*val = SNDRV_CTL_ELEM_IFACE_CARD;
	अन्यथा अगर (!strnहालcmp(s, "mixer", 5))
		*val = SNDRV_CTL_ELEM_IFACE_MIXER;
	वापस find_eos(s);
पूर्ण

/*
 * These types of input strings are accepted:
 *
 *   अचिन्हित पूर्णांकeger - numid (equivaled to numid=UINT)
 *   string - basic mixer name (equivalent to अगरace=MIXER,name=STR)
 *   numid=UINT
 *   [अगरace=MIXER,][device=UINT,][subdevice=UINT,]name=STR[,index=UINT]
 */
अटल sमाप_प्रकार set_led_id(काष्ठा snd_ctl_led_card *led_card, स्थिर अक्षर *buf, माप_प्रकार count,
			  bool attach)
अणु
	अक्षर buf2[256], *s, *os;
	माप_प्रकार len = max(माप(s) - 1, count);
	काष्ठा snd_ctl_elem_id id;
	पूर्णांक err;

	म_नकलन(buf2, buf, len);
	buf2[len] = '\0';
	स_रखो(&id, 0, माप(id));
	id.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER;
	s = buf2;
	जबतक (*s) अणु
		os = s;
		अगर (!strnहालcmp(s, "numid=", 6)) अणु
			s = parse_uपूर्णांक(s + 6, &id.numid);
		पूर्ण अन्यथा अगर (!strnहालcmp(s, "iface=", 6)) अणु
			s = parse_अगरace(s + 6, &id.अगरace);
		पूर्ण अन्यथा अगर (!strnहालcmp(s, "device=", 7)) अणु
			s = parse_uपूर्णांक(s + 7, &id.device);
		पूर्ण अन्यथा अगर (!strnहालcmp(s, "subdevice=", 10)) अणु
			s = parse_uपूर्णांक(s + 10, &id.subdevice);
		पूर्ण अन्यथा अगर (!strnहालcmp(s, "name=", 5)) अणु
			s = parse_string(s + 5, id.name, माप(id.name));
		पूर्ण अन्यथा अगर (!strnहालcmp(s, "index=", 6)) अणु
			s = parse_uपूर्णांक(s + 6, &id.index);
		पूर्ण अन्यथा अगर (s == buf2) अणु
			जबतक (*s) अणु
				अगर (*s < '0' || *s > '9')
					अवरोध;
				s++;
			पूर्ण
			अगर (*s == '\0')
				parse_uपूर्णांक(buf2, &id.numid);
			अन्यथा अणु
				क्रम (; *s >= ' '; s++);
				*s = '\0';
				strlcpy(id.name, buf2, माप(id.name));
			पूर्ण
			अवरोध;
		पूर्ण
		अगर (*s == ',')
			s++;
		अगर (s == os)
			अवरोध;
	पूर्ण

	err = snd_ctl_led_set_id(led_card->number, &id, led_card->led->group, attach);
	अगर (err < 0)
		वापस err;

	वापस count;
पूर्ण

अटल sमाप_प्रकार parse_attach(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा snd_ctl_led_card *led_card = container_of(dev, काष्ठा snd_ctl_led_card, dev);
	वापस set_led_id(led_card, buf, count, true);
पूर्ण

अटल sमाप_प्रकार parse_detach(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा snd_ctl_led_card *led_card = container_of(dev, काष्ठा snd_ctl_led_card, dev);
	वापस set_led_id(led_card, buf, count, false);
पूर्ण

अटल sमाप_प्रकार ctl_reset(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा snd_ctl_led_card *led_card = container_of(dev, काष्ठा snd_ctl_led_card, dev);
	पूर्णांक err;

	अगर (count > 0 && buf[0] == '1') अणु
		err = snd_ctl_led_reset(led_card->number, led_card->led->group);
		अगर (err < 0)
			वापस err;
	पूर्ण
	वापस count;
पूर्ण

अटल sमाप_प्रकार ctl_list(काष्ठा device *dev,
			काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा snd_ctl_led_card *led_card = container_of(dev, काष्ठा snd_ctl_led_card, dev);
	काष्ठा snd_card *card;
	काष्ठा snd_ctl_led_ctl *lctl;
	अक्षर *buf2 = buf;
	माप_प्रकार l;

	card = snd_card_ref(led_card->number);
	अगर (!card)
		वापस -ENXIO;
	करोwn_पढ़ो(&card->controls_rwsem);
	mutex_lock(&snd_ctl_led_mutex);
	अगर (snd_ctl_led_card_valid[led_card->number]) अणु
		list_क्रम_each_entry(lctl, &led_card->led->controls, list)
			अगर (lctl->card == card) अणु
				अगर (buf2 - buf > PAGE_SIZE - 16)
					अवरोध;
				अगर (buf2 != buf)
					*buf2++ = ' ';
				l = scnम_लिखो(buf2, 15, "%u",
						lctl->kctl->id.numid +
							lctl->index_offset);
				buf2[l] = '\0';
				buf2 += l + 1;
			पूर्ण
	पूर्ण
	mutex_unlock(&snd_ctl_led_mutex);
	up_पढ़ो(&card->controls_rwsem);
	snd_card_unref(card);
	वापस buf2 - buf;
पूर्ण

अटल DEVICE_ATTR(attach, 0200, शून्य, parse_attach);
अटल DEVICE_ATTR(detach, 0200, शून्य, parse_detach);
अटल DEVICE_ATTR(reset, 0200, शून्य, ctl_reset);
अटल DEVICE_ATTR(list, 0444, ctl_list, शून्य);

अटल काष्ठा attribute *snd_ctl_led_card_attrs[] = अणु
	&dev_attr_attach.attr,
	&dev_attr_detach.attr,
	&dev_attr_reset.attr,
	&dev_attr_list.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group snd_ctl_led_card_attr_group = अणु
	.attrs = snd_ctl_led_card_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *snd_ctl_led_card_attr_groups[] = अणु
	&snd_ctl_led_card_attr_group,
	शून्य,
पूर्ण;

अटल काष्ठा device snd_ctl_led_dev;

अटल व्योम snd_ctl_led_sysfs_add(काष्ठा snd_card *card)
अणु
	अचिन्हित पूर्णांक group;
	काष्ठा snd_ctl_led_card *led_card;
	काष्ठा snd_ctl_led *led;
	अक्षर link_name[32];

	क्रम (group = 0; group < MAX_LED; group++) अणु
		led = &snd_ctl_leds[group];
		led_card = kzalloc(माप(*led_card), GFP_KERNEL);
		अगर (!led_card)
			जाओ cerr2;
		led_card->number = card->number;
		led_card->led = led;
		device_initialize(&led_card->dev);
		led_card->dev.release = snd_ctl_led_card_release;
		अगर (dev_set_name(&led_card->dev, "card%d", card->number) < 0)
			जाओ cerr;
		led_card->dev.parent = &led->dev;
		led_card->dev.groups = snd_ctl_led_card_attr_groups;
		अगर (device_add(&led_card->dev))
			जाओ cerr;
		led->cards[card->number] = led_card;
		snम_लिखो(link_name, माप(link_name), "led-%s", led->name);
		WARN(sysfs_create_link(&card->ctl_dev.kobj, &led_card->dev.kobj, link_name),
			"can't create symlink to controlC%i device\n", card->number);
		WARN(sysfs_create_link(&led_card->dev.kobj, &card->card_dev.kobj, "card"),
			"can't create symlink to card%i\n", card->number);

		जारी;
cerr:
		put_device(&led_card->dev);
cerr2:
		prपूर्णांकk(KERN_ERR "snd_ctl_led: unable to add card%d", card->number);
	पूर्ण
पूर्ण

अटल व्योम snd_ctl_led_sysfs_हटाओ(काष्ठा snd_card *card)
अणु
	अचिन्हित पूर्णांक group;
	काष्ठा snd_ctl_led_card *led_card;
	काष्ठा snd_ctl_led *led;
	अक्षर link_name[32];

	क्रम (group = 0; group < MAX_LED; group++) अणु
		led = &snd_ctl_leds[group];
		led_card = led->cards[card->number];
		अगर (!led_card)
			जारी;
		snम_लिखो(link_name, माप(link_name), "led-%s", led->name);
		sysfs_हटाओ_link(&card->ctl_dev.kobj, link_name);
		sysfs_हटाओ_link(&led_card->dev.kobj, "card");
		device_unरेजिस्टर(&led_card->dev);
		led->cards[card->number] = शून्य;
	पूर्ण
पूर्ण

/*
 * Control layer registration
 */
अटल काष्ठा snd_ctl_layer_ops snd_ctl_led_lops = अणु
	.module_name = SND_CTL_LAYER_MODULE_LED,
	.lरेजिस्टर = snd_ctl_led_रेजिस्टर,
	.ldisconnect = snd_ctl_led_disconnect,
	.lnotअगरy = snd_ctl_led_notअगरy,
पूर्ण;

अटल पूर्णांक __init snd_ctl_led_init(व्योम)
अणु
	काष्ठा snd_ctl_led *led;
	अचिन्हित पूर्णांक group;

	device_initialize(&snd_ctl_led_dev);
	snd_ctl_led_dev.class = sound_class;
	snd_ctl_led_dev.release = snd_ctl_led_dev_release;
	dev_set_name(&snd_ctl_led_dev, "ctl-led");
	अगर (device_add(&snd_ctl_led_dev)) अणु
		put_device(&snd_ctl_led_dev);
		वापस -ENOMEM;
	पूर्ण
	क्रम (group = 0; group < MAX_LED; group++) अणु
		led = &snd_ctl_leds[group];
		INIT_LIST_HEAD(&led->controls);
		device_initialize(&led->dev);
		led->dev.parent = &snd_ctl_led_dev;
		led->dev.release = snd_ctl_led_release;
		led->dev.groups = snd_ctl_led_dev_attr_groups;
		dev_set_name(&led->dev, led->name);
		अगर (device_add(&led->dev)) अणु
			put_device(&led->dev);
			क्रम (; group > 0; group--) अणु
				led = &snd_ctl_leds[group - 1];
				device_unरेजिस्टर(&led->dev);
			पूर्ण
			device_unरेजिस्टर(&snd_ctl_led_dev);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण
	snd_ctl_रेजिस्टर_layer(&snd_ctl_led_lops);
	वापस 0;
पूर्ण

अटल व्योम __निकास snd_ctl_led_निकास(व्योम)
अणु
	काष्ठा snd_ctl_led *led;
	काष्ठा snd_card *card;
	अचिन्हित पूर्णांक group, card_number;

	snd_ctl_disconnect_layer(&snd_ctl_led_lops);
	क्रम (card_number = 0; card_number < SNDRV_CARDS; card_number++) अणु
		अगर (!snd_ctl_led_card_valid[card_number])
			जारी;
		card = snd_card_ref(card_number);
		अगर (card) अणु
			snd_ctl_led_sysfs_हटाओ(card);
			snd_card_unref(card);
		पूर्ण
	पूर्ण
	क्रम (group = 0; group < MAX_LED; group++) अणु
		led = &snd_ctl_leds[group];
		device_unरेजिस्टर(&led->dev);
	पूर्ण
	device_unरेजिस्टर(&snd_ctl_led_dev);
	snd_ctl_led_clean(शून्य);
पूर्ण

module_init(snd_ctl_led_init)
module_निकास(snd_ctl_led_निकास)
