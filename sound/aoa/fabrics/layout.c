<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Apple Onboard Audio driver -- layout/machine id fabric
 *
 * Copyright 2006-2008 Johannes Berg <johannes@sipsolutions.net>
 *
 * This fabric module looks क्रम sound codecs based on the
 * layout-id or device-id property in the device tree.
 */
#समावेश <यंत्र/prom.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश "../aoa.h"
#समावेश "../soundbus/soundbus.h"

MODULE_AUTHOR("Johannes Berg <johannes@sipsolutions.net>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Layout-ID fabric for snd-aoa");

#घोषणा MAX_CODECS_PER_BUS	2

/* These are the connections the layout fabric
 * knows about. It करोesn't really care about the
 * input ones, but I thought I'd separate them
 * to give them proper names. The thing is that
 * Apple usually will distinguish the active output
 * by GPIOs, जबतक the active input is set directly
 * on the codec. Hence we here tell the codec what
 * we think is connected. This inक्रमmation is hard-
 * coded below ... */
#घोषणा CC_SPEAKERS	(1<<0)
#घोषणा CC_HEADPHONE	(1<<1)
#घोषणा CC_LINEOUT	(1<<2)
#घोषणा CC_DIGITALOUT	(1<<3)
#घोषणा CC_LINEIN	(1<<4)
#घोषणा CC_MICROPHONE	(1<<5)
#घोषणा CC_DIGITALIN	(1<<6)
/* pretty bogus but users complain...
 * This is a flag saying that the LINEOUT
 * should be नामd to HEADPHONE.
 * be careful with input detection! */
#घोषणा CC_LINEOUT_LABELLED_HEADPHONE	(1<<7)

काष्ठा codec_connection अणु
	/* CC_ flags from above */
	पूर्णांक connected;
	/* codec dependent bit to be set in the aoa_codec.connected field.
	 * This पूर्णांकentionally करोesn't have any generic flags because the
	 * fabric has to know the codec anyway and all codecs might have
	 * dअगरferent connectors */
	पूर्णांक codec_bit;
पूर्ण;

काष्ठा codec_connect_info अणु
	अक्षर *name;
	काष्ठा codec_connection *connections;
पूर्ण;

#घोषणा LAYOUT_FLAG_COMBO_LINEOUT_SPDIF	(1<<0)

काष्ठा layout अणु
	अचिन्हित पूर्णांक layout_id, device_id;
	काष्ठा codec_connect_info codecs[MAX_CODECS_PER_BUS];
	पूर्णांक flags;

	/* अगर busname is not asचिन्हित, we use 'Master' below,
	 * so that our layout table करोesn't need to be filled
	 * too much.
	 * We only assign these two अगर we expect to find more
	 * than one soundbus, i.e. on those machines with
	 * multiple layout-ids */
	अक्षर *busname;
	पूर्णांक pcmid;
पूर्ण;

MODULE_ALIAS("sound-layout-36");
MODULE_ALIAS("sound-layout-41");
MODULE_ALIAS("sound-layout-45");
MODULE_ALIAS("sound-layout-47");
MODULE_ALIAS("sound-layout-48");
MODULE_ALIAS("sound-layout-49");
MODULE_ALIAS("sound-layout-50");
MODULE_ALIAS("sound-layout-51");
MODULE_ALIAS("sound-layout-56");
MODULE_ALIAS("sound-layout-57");
MODULE_ALIAS("sound-layout-58");
MODULE_ALIAS("sound-layout-60");
MODULE_ALIAS("sound-layout-61");
MODULE_ALIAS("sound-layout-62");
MODULE_ALIAS("sound-layout-64");
MODULE_ALIAS("sound-layout-65");
MODULE_ALIAS("sound-layout-66");
MODULE_ALIAS("sound-layout-67");
MODULE_ALIAS("sound-layout-68");
MODULE_ALIAS("sound-layout-69");
MODULE_ALIAS("sound-layout-70");
MODULE_ALIAS("sound-layout-72");
MODULE_ALIAS("sound-layout-76");
MODULE_ALIAS("sound-layout-80");
MODULE_ALIAS("sound-layout-82");
MODULE_ALIAS("sound-layout-84");
MODULE_ALIAS("sound-layout-86");
MODULE_ALIAS("sound-layout-90");
MODULE_ALIAS("sound-layout-92");
MODULE_ALIAS("sound-layout-94");
MODULE_ALIAS("sound-layout-96");
MODULE_ALIAS("sound-layout-98");
MODULE_ALIAS("sound-layout-100");

MODULE_ALIAS("aoa-device-id-14");
MODULE_ALIAS("aoa-device-id-22");
MODULE_ALIAS("aoa-device-id-31");
MODULE_ALIAS("aoa-device-id-35");
MODULE_ALIAS("aoa-device-id-44");

/* onyx with all but microphone connected */
अटल काष्ठा codec_connection onyx_connections_nomic[] = अणु
	अणु
		.connected = CC_SPEAKERS | CC_HEADPHONE | CC_LINEOUT,
		.codec_bit = 0,
	पूर्ण,
	अणु
		.connected = CC_DIGITALOUT,
		.codec_bit = 1,
	पूर्ण,
	अणु
		.connected = CC_LINEIN,
		.codec_bit = 2,
	पूर्ण,
	अणुपूर्ण /* terminate array by .connected == 0 */
पूर्ण;

/* onyx on machines without headphone */
अटल काष्ठा codec_connection onyx_connections_noheadphones[] = अणु
	अणु
		.connected = CC_SPEAKERS | CC_LINEOUT |
			     CC_LINEOUT_LABELLED_HEADPHONE,
		.codec_bit = 0,
	पूर्ण,
	अणु
		.connected = CC_DIGITALOUT,
		.codec_bit = 1,
	पूर्ण,
	/* FIXME: are these correct? probably not क्रम all the machines
	 * below ... If not this will need separating. */
	अणु
		.connected = CC_LINEIN,
		.codec_bit = 2,
	पूर्ण,
	अणु
		.connected = CC_MICROPHONE,
		.codec_bit = 3,
	पूर्ण,
	अणुपूर्ण /* terminate array by .connected == 0 */
पूर्ण;

/* onyx on machines with real line-out */
अटल काष्ठा codec_connection onyx_connections_reallineout[] = अणु
	अणु
		.connected = CC_SPEAKERS | CC_LINEOUT | CC_HEADPHONE,
		.codec_bit = 0,
	पूर्ण,
	अणु
		.connected = CC_DIGITALOUT,
		.codec_bit = 1,
	पूर्ण,
	अणु
		.connected = CC_LINEIN,
		.codec_bit = 2,
	पूर्ण,
	अणुपूर्ण /* terminate array by .connected == 0 */
पूर्ण;

/* tas on machines without line out */
अटल काष्ठा codec_connection tas_connections_nolineout[] = अणु
	अणु
		.connected = CC_SPEAKERS | CC_HEADPHONE,
		.codec_bit = 0,
	पूर्ण,
	अणु
		.connected = CC_LINEIN,
		.codec_bit = 2,
	पूर्ण,
	अणु
		.connected = CC_MICROPHONE,
		.codec_bit = 3,
	पूर्ण,
	अणुपूर्ण /* terminate array by .connected == 0 */
पूर्ण;

/* tas on machines with neither line out nor line in */
अटल काष्ठा codec_connection tas_connections_noline[] = अणु
	अणु
		.connected = CC_SPEAKERS | CC_HEADPHONE,
		.codec_bit = 0,
	पूर्ण,
	अणु
		.connected = CC_MICROPHONE,
		.codec_bit = 3,
	पूर्ण,
	अणुपूर्ण /* terminate array by .connected == 0 */
पूर्ण;

/* tas on machines without microphone */
अटल काष्ठा codec_connection tas_connections_nomic[] = अणु
	अणु
		.connected = CC_SPEAKERS | CC_HEADPHONE | CC_LINEOUT,
		.codec_bit = 0,
	पूर्ण,
	अणु
		.connected = CC_LINEIN,
		.codec_bit = 2,
	पूर्ण,
	अणुपूर्ण /* terminate array by .connected == 0 */
पूर्ण;

/* tas on machines with everything connected */
अटल काष्ठा codec_connection tas_connections_all[] = अणु
	अणु
		.connected = CC_SPEAKERS | CC_HEADPHONE | CC_LINEOUT,
		.codec_bit = 0,
	पूर्ण,
	अणु
		.connected = CC_LINEIN,
		.codec_bit = 2,
	पूर्ण,
	अणु
		.connected = CC_MICROPHONE,
		.codec_bit = 3,
	पूर्ण,
	अणुपूर्ण /* terminate array by .connected == 0 */
पूर्ण;

अटल काष्ठा codec_connection toonie_connections[] = अणु
	अणु
		.connected = CC_SPEAKERS | CC_HEADPHONE,
		.codec_bit = 0,
	पूर्ण,
	अणुपूर्ण /* terminate array by .connected == 0 */
पूर्ण;

अटल काष्ठा codec_connection topaz_input[] = अणु
	अणु
		.connected = CC_DIGITALIN,
		.codec_bit = 0,
	पूर्ण,
	अणुपूर्ण /* terminate array by .connected == 0 */
पूर्ण;

अटल काष्ठा codec_connection topaz_output[] = अणु
	अणु
		.connected = CC_DIGITALOUT,
		.codec_bit = 1,
	पूर्ण,
	अणुपूर्ण /* terminate array by .connected == 0 */
पूर्ण;

अटल काष्ठा codec_connection topaz_inout[] = अणु
	अणु
		.connected = CC_DIGITALIN,
		.codec_bit = 0,
	पूर्ण,
	अणु
		.connected = CC_DIGITALOUT,
		.codec_bit = 1,
	पूर्ण,
	अणुपूर्ण /* terminate array by .connected == 0 */
पूर्ण;

अटल काष्ठा layout layouts[] = अणु
	/* last PowerBooks (15" Oct 2005) */
	अणु .layout_id = 82,
	  .flags = LAYOUT_FLAG_COMBO_LINEOUT_SPDIF,
	  .codecs[0] = अणु
		.name = "onyx",
		.connections = onyx_connections_noheadphones,
	  पूर्ण,
	  .codecs[1] = अणु
		.name = "topaz",
		.connections = topaz_input,
	  पूर्ण,
	पूर्ण,
	/* PowerMac9,1 */
	अणु .layout_id = 60,
	  .codecs[0] = अणु
		.name = "onyx",
		.connections = onyx_connections_reallineout,
	  पूर्ण,
	पूर्ण,
	/* PowerMac9,1 */
	अणु .layout_id = 61,
	  .codecs[0] = अणु
		.name = "topaz",
		.connections = topaz_input,
	  पूर्ण,
	पूर्ण,
	/* PowerBook5,7 */
	अणु .layout_id = 64,
	  .flags = LAYOUT_FLAG_COMBO_LINEOUT_SPDIF,
	  .codecs[0] = अणु
		.name = "onyx",
		.connections = onyx_connections_noheadphones,
	  पूर्ण,
	पूर्ण,
	/* PowerBook5,7 */
	अणु .layout_id = 65,
	  .codecs[0] = अणु
		.name = "topaz",
		.connections = topaz_input,
	  पूर्ण,
	पूर्ण,
	/* PowerBook5,9 [17" Oct 2005] */
	अणु .layout_id = 84,
	  .flags = LAYOUT_FLAG_COMBO_LINEOUT_SPDIF,
	  .codecs[0] = अणु
		.name = "onyx",
		.connections = onyx_connections_noheadphones,
	  पूर्ण,
	  .codecs[1] = अणु
		.name = "topaz",
		.connections = topaz_input,
	  पूर्ण,
	पूर्ण,
	/* PowerMac8,1 */
	अणु .layout_id = 45,
	  .codecs[0] = अणु
		.name = "onyx",
		.connections = onyx_connections_noheadphones,
	  पूर्ण,
	  .codecs[1] = अणु
		.name = "topaz",
		.connections = topaz_input,
	  पूर्ण,
	पूर्ण,
	/* Quad PowerMac (analog in, analog/digital out) */
	अणु .layout_id = 68,
	  .codecs[0] = अणु
		.name = "onyx",
		.connections = onyx_connections_nomic,
	  पूर्ण,
	पूर्ण,
	/* Quad PowerMac (digital in) */
	अणु .layout_id = 69,
	  .codecs[0] = अणु
		.name = "topaz",
		.connections = topaz_input,
	  पूर्ण,
	  .busname = "digital in", .pcmid = 1 पूर्ण,
	/* Early 2005 PowerBook (PowerBook 5,6) */
	अणु .layout_id = 70,
	  .codecs[0] = अणु
		.name = "tas",
		.connections = tas_connections_nolineout,
	  पूर्ण,
	पूर्ण,
	/* PowerBook 5,4 */
	अणु .layout_id = 51,
	  .codecs[0] = अणु
		.name = "tas",
		.connections = tas_connections_nolineout,
	  पूर्ण,
	पूर्ण,
	/* PowerBook6,1 */
	अणु .device_id = 31,
	  .codecs[0] = अणु
		.name = "tas",
		.connections = tas_connections_nolineout,
	  पूर्ण,
	पूर्ण,
	/* PowerBook6,5 */
	अणु .device_id = 44,
	  .codecs[0] = अणु
		.name = "tas",
		.connections = tas_connections_all,
	  पूर्ण,
	पूर्ण,
	/* PowerBook6,7 */
	अणु .layout_id = 80,
	  .codecs[0] = अणु
		.name = "tas",
		.connections = tas_connections_noline,
	  पूर्ण,
	पूर्ण,
	/* PowerBook6,8 */
	अणु .layout_id = 72,
	  .codecs[0] = अणु
		.name = "tas",
		.connections = tas_connections_nolineout,
	  पूर्ण,
	पूर्ण,
	/* PowerMac8,2 */
	अणु .layout_id = 86,
	  .codecs[0] = अणु
		.name = "onyx",
		.connections = onyx_connections_nomic,
	  पूर्ण,
	  .codecs[1] = अणु
		.name = "topaz",
		.connections = topaz_input,
	  पूर्ण,
	पूर्ण,
	/* PowerBook6,7 */
	अणु .layout_id = 92,
	  .codecs[0] = अणु
		.name = "tas",
		.connections = tas_connections_nolineout,
	  पूर्ण,
	पूर्ण,
	/* PowerMac10,1 (Mac Mini) */
	अणु .layout_id = 58,
	  .codecs[0] = अणु
		.name = "toonie",
		.connections = toonie_connections,
	  पूर्ण,
	पूर्ण,
	अणु
	  .layout_id = 96,
	  .codecs[0] = अणु
	  	.name = "onyx",
	  	.connections = onyx_connections_noheadphones,
	  पूर्ण,
	पूर्ण,
	/* unknown, untested, but this comes from Apple */
	अणु .layout_id = 41,
	  .codecs[0] = अणु
		.name = "tas",
		.connections = tas_connections_all,
	  पूर्ण,
	पूर्ण,
	अणु .layout_id = 36,
	  .codecs[0] = अणु
		.name = "tas",
		.connections = tas_connections_nomic,
	  पूर्ण,
	  .codecs[1] = अणु
		.name = "topaz",
		.connections = topaz_inout,
	  पूर्ण,
	पूर्ण,
	अणु .layout_id = 47,
	  .codecs[0] = अणु
		.name = "onyx",
		.connections = onyx_connections_noheadphones,
	  पूर्ण,
	पूर्ण,
	अणु .layout_id = 48,
	  .codecs[0] = अणु
		.name = "topaz",
		.connections = topaz_input,
	  पूर्ण,
	पूर्ण,
	अणु .layout_id = 49,
	  .codecs[0] = अणु
		.name = "onyx",
		.connections = onyx_connections_nomic,
	  पूर्ण,
	पूर्ण,
	अणु .layout_id = 50,
	  .codecs[0] = अणु
		.name = "topaz",
		.connections = topaz_input,
	  पूर्ण,
	पूर्ण,
	अणु .layout_id = 56,
	  .codecs[0] = अणु
		.name = "onyx",
		.connections = onyx_connections_noheadphones,
	  पूर्ण,
	पूर्ण,
	अणु .layout_id = 57,
	  .codecs[0] = अणु
		.name = "topaz",
		.connections = topaz_input,
	  पूर्ण,
	पूर्ण,
	अणु .layout_id = 62,
	  .codecs[0] = अणु
		.name = "onyx",
		.connections = onyx_connections_noheadphones,
	  पूर्ण,
	  .codecs[1] = अणु
		.name = "topaz",
		.connections = topaz_output,
	  पूर्ण,
	पूर्ण,
	अणु .layout_id = 66,
	  .codecs[0] = अणु
		.name = "onyx",
		.connections = onyx_connections_noheadphones,
	  पूर्ण,
	पूर्ण,
	अणु .layout_id = 67,
	  .codecs[0] = अणु
		.name = "topaz",
		.connections = topaz_input,
	  पूर्ण,
	पूर्ण,
	अणु .layout_id = 76,
	  .codecs[0] = अणु
		.name = "tas",
		.connections = tas_connections_nomic,
	  पूर्ण,
	  .codecs[1] = अणु
		.name = "topaz",
		.connections = topaz_inout,
	  पूर्ण,
	पूर्ण,
	अणु .layout_id = 90,
	  .codecs[0] = अणु
		.name = "tas",
		.connections = tas_connections_noline,
	  पूर्ण,
	पूर्ण,
	अणु .layout_id = 94,
	  .codecs[0] = अणु
		.name = "onyx",
		/* but it has an बाह्यal mic?? how to select? */
		.connections = onyx_connections_noheadphones,
	  पूर्ण,
	पूर्ण,
	अणु .layout_id = 98,
	  .codecs[0] = अणु
		.name = "toonie",
		.connections = toonie_connections,
	  पूर्ण,
	पूर्ण,
	अणु .layout_id = 100,
	  .codecs[0] = अणु
		.name = "topaz",
		.connections = topaz_input,
	  पूर्ण,
	  .codecs[1] = अणु
		.name = "onyx",
		.connections = onyx_connections_noheadphones,
	  पूर्ण,
	पूर्ण,
	/* PowerMac3,4 */
	अणु .device_id = 14,
	  .codecs[0] = अणु
		.name = "tas",
		.connections = tas_connections_noline,
	  पूर्ण,
	पूर्ण,
	/* PowerMac3,6 */
	अणु .device_id = 22,
	  .codecs[0] = अणु
		.name = "tas",
		.connections = tas_connections_all,
	  पूर्ण,
	पूर्ण,
	/* PowerBook5,2 */
	अणु .device_id = 35,
	  .codecs[0] = अणु
		.name = "tas",
		.connections = tas_connections_all,
	  पूर्ण,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा layout *find_layout_by_id(अचिन्हित पूर्णांक id)
अणु
	काष्ठा layout *l;

	l = layouts;
	जबतक (l->codecs[0].name) अणु
		अगर (l->layout_id == id)
			वापस l;
		l++;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा layout *find_layout_by_device(अचिन्हित पूर्णांक id)
अणु
	काष्ठा layout *l;

	l = layouts;
	जबतक (l->codecs[0].name) अणु
		अगर (l->device_id == id)
			वापस l;
		l++;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम use_layout(काष्ठा layout *l)
अणु
	पूर्णांक i;

	क्रम (i=0; i<MAX_CODECS_PER_BUS; i++) अणु
		अगर (l->codecs[i].name) अणु
			request_module("snd-aoa-codec-%s", l->codecs[i].name);
		पूर्ण
	पूर्ण
	/* now we रुको क्रम the codecs to call us back */
पूर्ण

काष्ठा layout_dev;

काष्ठा layout_dev_ptr अणु
	काष्ठा layout_dev *ptr;
पूर्ण;

काष्ठा layout_dev अणु
	काष्ठा list_head list;
	काष्ठा soundbus_dev *sdev;
	काष्ठा device_node *sound;
	काष्ठा aoa_codec *codecs[MAX_CODECS_PER_BUS];
	काष्ठा layout *layout;
	काष्ठा gpio_runसमय gpio;

	/* we need these क्रम headphone/lineout detection */
	काष्ठा snd_kcontrol *headphone_ctrl;
	काष्ठा snd_kcontrol *lineout_ctrl;
	काष्ठा snd_kcontrol *speaker_ctrl;
	काष्ठा snd_kcontrol *master_ctrl;
	काष्ठा snd_kcontrol *headphone_detected_ctrl;
	काष्ठा snd_kcontrol *lineout_detected_ctrl;

	काष्ठा layout_dev_ptr selfptr_headphone;
	काष्ठा layout_dev_ptr selfptr_lineout;

	u32 have_lineout_detect:1,
	    have_headphone_detect:1,
	    चयन_on_headphone:1,
	    चयन_on_lineout:1;
पूर्ण;

अटल LIST_HEAD(layouts_list);
अटल पूर्णांक layouts_list_items;
/* this can go away but only अगर we allow multiple cards,
 * make the fabric handle all the card stuff, etc... */
अटल काष्ठा layout_dev *layout_device;

#घोषणा control_info	snd_ctl_boolean_mono_info

#घोषणा AMP_CONTROL(n, description)					\
अटल पूर्णांक n##_control_get(काष्ठा snd_kcontrol *kcontrol,		\
			   काष्ठा snd_ctl_elem_value *ucontrol)		\
अणु									\
	काष्ठा gpio_runसमय *gpio = snd_kcontrol_chip(kcontrol);	\
	अगर (gpio->methods && gpio->methods->get_##n)			\
		ucontrol->value.पूर्णांकeger.value[0] =			\
			gpio->methods->get_##n(gpio);			\
	वापस 0;							\
पूर्ण									\
अटल पूर्णांक n##_control_put(काष्ठा snd_kcontrol *kcontrol,		\
			   काष्ठा snd_ctl_elem_value *ucontrol)		\
अणु									\
	काष्ठा gpio_runसमय *gpio = snd_kcontrol_chip(kcontrol);	\
	अगर (gpio->methods && gpio->methods->set_##n)			\
		gpio->methods->set_##n(gpio,				\
			!!ucontrol->value.पूर्णांकeger.value[0]);		\
	वापस 1;							\
पूर्ण									\
अटल स्थिर काष्ठा snd_kcontrol_new n##_ctl = अणु			\
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,				\
	.name = description,						\
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,                      \
	.info = control_info,						\
	.get = n##_control_get,						\
	.put = n##_control_put,						\
पूर्ण

AMP_CONTROL(headphone, "Headphone Switch");
AMP_CONTROL(speakers, "Speakers Switch");
AMP_CONTROL(lineout, "Line-Out Switch");
AMP_CONTROL(master, "Master Switch");

अटल पूर्णांक detect_choice_get(काष्ठा snd_kcontrol *kcontrol,
			     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा layout_dev *ldev = snd_kcontrol_chip(kcontrol);

	चयन (kcontrol->निजी_value) अणु
	हाल 0:
		ucontrol->value.पूर्णांकeger.value[0] = ldev->चयन_on_headphone;
		अवरोध;
	हाल 1:
		ucontrol->value.पूर्णांकeger.value[0] = ldev->चयन_on_lineout;
		अवरोध;
	शेष:
		वापस -ENODEV;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक detect_choice_put(काष्ठा snd_kcontrol *kcontrol,
			     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा layout_dev *ldev = snd_kcontrol_chip(kcontrol);

	चयन (kcontrol->निजी_value) अणु
	हाल 0:
		ldev->चयन_on_headphone = !!ucontrol->value.पूर्णांकeger.value[0];
		अवरोध;
	हाल 1:
		ldev->चयन_on_lineout = !!ucontrol->value.पूर्णांकeger.value[0];
		अवरोध;
	शेष:
		वापस -ENODEV;
	पूर्ण
	वापस 1;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new headphone_detect_choice = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "Headphone Detect Autoswitch",
	.info = control_info,
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,
	.get = detect_choice_get,
	.put = detect_choice_put,
	.निजी_value = 0,
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new lineout_detect_choice = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "Line-Out Detect Autoswitch",
	.info = control_info,
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,
	.get = detect_choice_get,
	.put = detect_choice_put,
	.निजी_value = 1,
पूर्ण;

अटल पूर्णांक detected_get(काष्ठा snd_kcontrol *kcontrol,
			काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा layout_dev *ldev = snd_kcontrol_chip(kcontrol);
	पूर्णांक v;

	चयन (kcontrol->निजी_value) अणु
	हाल 0:
		v = ldev->gpio.methods->get_detect(&ldev->gpio,
						   AOA_NOTIFY_HEADPHONE);
		अवरोध;
	हाल 1:
		v = ldev->gpio.methods->get_detect(&ldev->gpio,
						   AOA_NOTIFY_LINE_OUT);
		अवरोध;
	शेष:
		वापस -ENODEV;
	पूर्ण
	ucontrol->value.पूर्णांकeger.value[0] = v;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new headphone_detected = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "Headphone Detected",
	.info = control_info,
	.access = SNDRV_CTL_ELEM_ACCESS_READ,
	.get = detected_get,
	.निजी_value = 0,
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new lineout_detected = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "Line-Out Detected",
	.info = control_info,
	.access = SNDRV_CTL_ELEM_ACCESS_READ,
	.get = detected_get,
	.निजी_value = 1,
पूर्ण;

अटल पूर्णांक check_codec(काष्ठा aoa_codec *codec,
		       काष्ठा layout_dev *ldev,
		       काष्ठा codec_connect_info *cci)
अणु
	स्थिर u32 *ref;
	अक्षर propname[32];
	काष्ठा codec_connection *cc;

	/* अगर the codec has a 'codec' node, we require a reference */
	अगर (of_node_name_eq(codec->node, "codec")) अणु
		snम_लिखो(propname, माप(propname),
			 "platform-%s-codec-ref", codec->name);
		ref = of_get_property(ldev->sound, propname, शून्य);
		अगर (!ref) अणु
			prपूर्णांकk(KERN_INFO "snd-aoa-fabric-layout: "
				"required property %s not present\n", propname);
			वापस -ENODEV;
		पूर्ण
		अगर (*ref != codec->node->phandle) अणु
			prपूर्णांकk(KERN_INFO "snd-aoa-fabric-layout: "
				"%s doesn't match!\n", propname);
			वापस -ENODEV;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (layouts_list_items != 1) अणु
			prपूर्णांकk(KERN_INFO "snd-aoa-fabric-layout: "
				"more than one soundbus, but no references.\n");
			वापस -ENODEV;
		पूर्ण
	पूर्ण
	codec->soundbus_dev = ldev->sdev;
	codec->gpio = &ldev->gpio;

	cc = cci->connections;
	अगर (!cc)
		वापस -EINVAL;

	prपूर्णांकk(KERN_INFO "snd-aoa-fabric-layout: can use this codec\n");

	codec->connected = 0;
	codec->fabric_data = cc;

	जबतक (cc->connected) अणु
		codec->connected |= 1<<cc->codec_bit;
		cc++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक layout_found_codec(काष्ठा aoa_codec *codec)
अणु
	काष्ठा layout_dev *ldev;
	पूर्णांक i;

	list_क्रम_each_entry(ldev, &layouts_list, list) अणु
		क्रम (i=0; i<MAX_CODECS_PER_BUS; i++) अणु
			अगर (!ldev->layout->codecs[i].name)
				जारी;
			अगर (म_भेद(ldev->layout->codecs[i].name, codec->name) == 0) अणु
				अगर (check_codec(codec,
						ldev,
						&ldev->layout->codecs[i]) == 0)
					वापस 0;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस -ENODEV;
पूर्ण

अटल व्योम layout_हटाओ_codec(काष्ठा aoa_codec *codec)
अणु
	पूर्णांक i;
	/* here हटाओ the codec from the layout dev's
	 * codec reference */

	codec->soundbus_dev = शून्य;
	codec->gpio = शून्य;
	क्रम (i=0; i<MAX_CODECS_PER_BUS; i++) अणु
	पूर्ण
पूर्ण

अटल व्योम layout_notअगरy(व्योम *data)
अणु
	काष्ठा layout_dev_ptr *dptr = data;
	काष्ठा layout_dev *ldev;
	पूर्णांक v, update;
	काष्ठा snd_kcontrol *detected, *c;
	काष्ठा snd_card *card = aoa_get_card();

	ldev = dptr->ptr;
	अगर (data == &ldev->selfptr_headphone) अणु
		v = ldev->gpio.methods->get_detect(&ldev->gpio, AOA_NOTIFY_HEADPHONE);
		detected = ldev->headphone_detected_ctrl;
		update = ldev->चयन_on_headphone;
		अगर (update) अणु
			ldev->gpio.methods->set_speakers(&ldev->gpio, !v);
			ldev->gpio.methods->set_headphone(&ldev->gpio, v);
			ldev->gpio.methods->set_lineout(&ldev->gpio, 0);
		पूर्ण
	पूर्ण अन्यथा अगर (data == &ldev->selfptr_lineout) अणु
		v = ldev->gpio.methods->get_detect(&ldev->gpio, AOA_NOTIFY_LINE_OUT);
		detected = ldev->lineout_detected_ctrl;
		update = ldev->चयन_on_lineout;
		अगर (update) अणु
			ldev->gpio.methods->set_speakers(&ldev->gpio, !v);
			ldev->gpio.methods->set_headphone(&ldev->gpio, 0);
			ldev->gpio.methods->set_lineout(&ldev->gpio, v);
		पूर्ण
	पूर्ण अन्यथा
		वापस;

	अगर (detected)
		snd_ctl_notअगरy(card, SNDRV_CTL_EVENT_MASK_VALUE, &detected->id);
	अगर (update) अणु
		c = ldev->headphone_ctrl;
		अगर (c)
			snd_ctl_notअगरy(card, SNDRV_CTL_EVENT_MASK_VALUE, &c->id);
		c = ldev->speaker_ctrl;
		अगर (c)
			snd_ctl_notअगरy(card, SNDRV_CTL_EVENT_MASK_VALUE, &c->id);
		c = ldev->lineout_ctrl;
		अगर (c)
			snd_ctl_notअगरy(card, SNDRV_CTL_EVENT_MASK_VALUE, &c->id);
	पूर्ण
पूर्ण

अटल व्योम layout_attached_codec(काष्ठा aoa_codec *codec)
अणु
	काष्ठा codec_connection *cc;
	काष्ठा snd_kcontrol *ctl;
	पूर्णांक headphones, lineout;
	काष्ठा layout_dev *ldev = layout_device;

	/* need to add this codec to our codec array! */

	cc = codec->fabric_data;

	headphones = codec->gpio->methods->get_detect(codec->gpio,
						      AOA_NOTIFY_HEADPHONE);
 	lineout = codec->gpio->methods->get_detect(codec->gpio,
						   AOA_NOTIFY_LINE_OUT);

	अगर (codec->gpio->methods->set_master) अणु
		ctl = snd_ctl_new1(&master_ctl, codec->gpio);
		ldev->master_ctrl = ctl;
		aoa_snd_ctl_add(ctl);
	पूर्ण
	जबतक (cc->connected) अणु
		अगर (cc->connected & CC_SPEAKERS) अणु
			अगर (headphones <= 0 && lineout <= 0)
				ldev->gpio.methods->set_speakers(codec->gpio, 1);
			ctl = snd_ctl_new1(&speakers_ctl, codec->gpio);
			ldev->speaker_ctrl = ctl;
			aoa_snd_ctl_add(ctl);
		पूर्ण
		अगर (cc->connected & CC_HEADPHONE) अणु
			अगर (headphones == 1)
				ldev->gpio.methods->set_headphone(codec->gpio, 1);
			ctl = snd_ctl_new1(&headphone_ctl, codec->gpio);
			ldev->headphone_ctrl = ctl;
			aoa_snd_ctl_add(ctl);
			ldev->have_headphone_detect =
				!ldev->gpio.methods
					->set_notअगरy(&ldev->gpio,
						     AOA_NOTIFY_HEADPHONE,
						     layout_notअगरy,
						     &ldev->selfptr_headphone);
			अगर (ldev->have_headphone_detect) अणु
				ctl = snd_ctl_new1(&headphone_detect_choice,
						   ldev);
				aoa_snd_ctl_add(ctl);
				ctl = snd_ctl_new1(&headphone_detected,
						   ldev);
				ldev->headphone_detected_ctrl = ctl;
				aoa_snd_ctl_add(ctl);
			पूर्ण
		पूर्ण
		अगर (cc->connected & CC_LINEOUT) अणु
			अगर (lineout == 1)
				ldev->gpio.methods->set_lineout(codec->gpio, 1);
			ctl = snd_ctl_new1(&lineout_ctl, codec->gpio);
			अगर (cc->connected & CC_LINEOUT_LABELLED_HEADPHONE)
				strscpy(ctl->id.name,
					"Headphone Switch", माप(ctl->id.name));
			ldev->lineout_ctrl = ctl;
			aoa_snd_ctl_add(ctl);
			ldev->have_lineout_detect =
				!ldev->gpio.methods
					->set_notअगरy(&ldev->gpio,
						     AOA_NOTIFY_LINE_OUT,
						     layout_notअगरy,
						     &ldev->selfptr_lineout);
			अगर (ldev->have_lineout_detect) अणु
				ctl = snd_ctl_new1(&lineout_detect_choice,
						   ldev);
				अगर (cc->connected & CC_LINEOUT_LABELLED_HEADPHONE)
					strscpy(ctl->id.name,
						"Headphone Detect Autoswitch",
						माप(ctl->id.name));
				aoa_snd_ctl_add(ctl);
				ctl = snd_ctl_new1(&lineout_detected,
						   ldev);
				अगर (cc->connected & CC_LINEOUT_LABELLED_HEADPHONE)
					strscpy(ctl->id.name,
						"Headphone Detected",
						माप(ctl->id.name));
				ldev->lineout_detected_ctrl = ctl;
				aoa_snd_ctl_add(ctl);
			पूर्ण
		पूर्ण
		cc++;
	पूर्ण
	/* now update initial state */
	अगर (ldev->have_headphone_detect)
		layout_notअगरy(&ldev->selfptr_headphone);
	अगर (ldev->have_lineout_detect)
		layout_notअगरy(&ldev->selfptr_lineout);
पूर्ण

अटल काष्ठा aoa_fabric layout_fabric = अणु
	.name = "SoundByLayout",
	.owner = THIS_MODULE,
	.found_codec = layout_found_codec,
	.हटाओ_codec = layout_हटाओ_codec,
	.attached_codec = layout_attached_codec,
पूर्ण;

अटल पूर्णांक aoa_fabric_layout_probe(काष्ठा soundbus_dev *sdev)
अणु
	काष्ठा device_node *sound = शून्य;
	स्थिर अचिन्हित पूर्णांक *id;
	काष्ठा layout *layout = शून्य;
	काष्ठा layout_dev *ldev = शून्य;
	पूर्णांक err;

	/* hm, currently we can only have one ... */
	अगर (layout_device)
		वापस -ENODEV;

	/* by अवरोधing out we keep a reference */
	क्रम_each_child_of_node(sdev->ofdev.dev.of_node, sound) अणु
		अगर (of_node_is_type(sound, "soundchip"))
			अवरोध;
	पूर्ण
	अगर (!sound)
		वापस -ENODEV;

	id = of_get_property(sound, "layout-id", शून्य);
	अगर (id) अणु
		layout = find_layout_by_id(*id);
	पूर्ण अन्यथा अणु
		id = of_get_property(sound, "device-id", शून्य);
		अगर (id)
			layout = find_layout_by_device(*id);
	पूर्ण

	अगर (!layout) अणु
		prपूर्णांकk(KERN_ERR "snd-aoa-fabric-layout: unknown layout\n");
		जाओ outnodev;
	पूर्ण

	ldev = kzalloc(माप(काष्ठा layout_dev), GFP_KERNEL);
	अगर (!ldev)
		जाओ outnodev;

	layout_device = ldev;
	ldev->sdev = sdev;
	ldev->sound = sound;
	ldev->layout = layout;
	ldev->gpio.node = sound->parent;
	चयन (layout->layout_id) अणु
	हाल 0:  /* anything with device_id, not layout_id */
	हाल 41: /* that unknown machine no one seems to have */
	हाल 51: /* PowerBook5,4 */
	हाल 58: /* Mac Mini */
		ldev->gpio.methods = ftr_gpio_methods;
		prपूर्णांकk(KERN_DEBUG
		       "snd-aoa-fabric-layout: Using direct GPIOs\n");
		अवरोध;
	शेष:
		ldev->gpio.methods = pmf_gpio_methods;
		prपूर्णांकk(KERN_DEBUG
		       "snd-aoa-fabric-layout: Using PMF GPIOs\n");
	पूर्ण
	ldev->selfptr_headphone.ptr = ldev;
	ldev->selfptr_lineout.ptr = ldev;
	dev_set_drvdata(&sdev->ofdev.dev, ldev);
	list_add(&ldev->list, &layouts_list);
	layouts_list_items++;

	/* assign these beक्रमe रेजिस्टरing ourselves, so
	 * callbacks that are करोne during registration
	 * alपढ़ोy have the values */
	sdev->pcmid = ldev->layout->pcmid;
	अगर (ldev->layout->busname) अणु
		sdev->pcmname = ldev->layout->busname;
	पूर्ण अन्यथा अणु
		sdev->pcmname = "Master";
	पूर्ण

	ldev->gpio.methods->init(&ldev->gpio);

	err = aoa_fabric_रेजिस्टर(&layout_fabric, &sdev->ofdev.dev);
	अगर (err && err != -EALREADY) अणु
		prपूर्णांकk(KERN_INFO "snd-aoa-fabric-layout: can't use,"
				 " another fabric is active!\n");
		जाओ outlistdel;
	पूर्ण

	use_layout(layout);
	ldev->चयन_on_headphone = 1;
	ldev->चयन_on_lineout = 1;
	वापस 0;
 outlistdel:
	/* we won't be using these then... */
	ldev->gpio.methods->निकास(&ldev->gpio);
	/* reset अगर we didn't use it */
	sdev->pcmname = शून्य;
	sdev->pcmid = -1;
	list_del(&ldev->list);
	layouts_list_items--;
	kमुक्त(ldev);
 outnodev:
 	of_node_put(sound);
 	layout_device = शून्य;
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक aoa_fabric_layout_हटाओ(काष्ठा soundbus_dev *sdev)
अणु
	काष्ठा layout_dev *ldev = dev_get_drvdata(&sdev->ofdev.dev);
	पूर्णांक i;

	क्रम (i=0; i<MAX_CODECS_PER_BUS; i++) अणु
		अगर (ldev->codecs[i]) अणु
			aoa_fabric_unlink_codec(ldev->codecs[i]);
		पूर्ण
		ldev->codecs[i] = शून्य;
	पूर्ण
	list_del(&ldev->list);
	layouts_list_items--;
	of_node_put(ldev->sound);

	ldev->gpio.methods->set_notअगरy(&ldev->gpio,
				       AOA_NOTIFY_HEADPHONE,
				       शून्य,
				       शून्य);
	ldev->gpio.methods->set_notअगरy(&ldev->gpio,
				       AOA_NOTIFY_LINE_OUT,
				       शून्य,
				       शून्य);

	ldev->gpio.methods->निकास(&ldev->gpio);
	layout_device = शून्य;
	kमुक्त(ldev);
	sdev->pcmid = -1;
	sdev->pcmname = शून्य;
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक aoa_fabric_layout_suspend(काष्ठा device *dev)
अणु
	काष्ठा layout_dev *ldev = dev_get_drvdata(dev);

	अगर (ldev->gpio.methods && ldev->gpio.methods->all_amps_off)
		ldev->gpio.methods->all_amps_off(&ldev->gpio);

	वापस 0;
पूर्ण

अटल पूर्णांक aoa_fabric_layout_resume(काष्ठा device *dev)
अणु
	काष्ठा layout_dev *ldev = dev_get_drvdata(dev);

	अगर (ldev->gpio.methods && ldev->gpio.methods->all_amps_restore)
		ldev->gpio.methods->all_amps_restore(&ldev->gpio);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(aoa_fabric_layout_pm_ops,
	aoa_fabric_layout_suspend, aoa_fabric_layout_resume);

#पूर्ण_अगर

अटल काष्ठा soundbus_driver aoa_soundbus_driver = अणु
	.name = "snd_aoa_soundbus_drv",
	.owner = THIS_MODULE,
	.probe = aoa_fabric_layout_probe,
	.हटाओ = aoa_fabric_layout_हटाओ,
	.driver = अणु
		.owner = THIS_MODULE,
#अगर_घोषित CONFIG_PM_SLEEP
		.pm = &aoa_fabric_layout_pm_ops,
#पूर्ण_अगर
	पूर्ण
पूर्ण;

अटल पूर्णांक __init aoa_fabric_layout_init(व्योम)
अणु
	वापस soundbus_रेजिस्टर_driver(&aoa_soundbus_driver);
पूर्ण

अटल व्योम __निकास aoa_fabric_layout_निकास(व्योम)
अणु
	soundbus_unरेजिस्टर_driver(&aoa_soundbus_driver);
	aoa_fabric_unरेजिस्टर(&layout_fabric);
पूर्ण

module_init(aoa_fabric_layout_init);
module_निकास(aoa_fabric_layout_निकास);
