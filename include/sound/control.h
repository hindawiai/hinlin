<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित __SOUND_CONTROL_H
#घोषणा __SOUND_CONTROL_H

/*
 *  Header file क्रम control पूर्णांकerface
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 */

#समावेश <linux/रुको.h>
#समावेश <linux/nospec.h>
#समावेश <sound/asound.h>

#घोषणा snd_kcontrol_chip(kcontrol) ((kcontrol)->निजी_data)

काष्ठा snd_kcontrol;
प्रकार पूर्णांक (snd_kcontrol_info_t) (काष्ठा snd_kcontrol * kcontrol, काष्ठा snd_ctl_elem_info * uinfo);
प्रकार पूर्णांक (snd_kcontrol_get_t) (काष्ठा snd_kcontrol * kcontrol, काष्ठा snd_ctl_elem_value * ucontrol);
प्रकार पूर्णांक (snd_kcontrol_put_t) (काष्ठा snd_kcontrol * kcontrol, काष्ठा snd_ctl_elem_value * ucontrol);
प्रकार पूर्णांक (snd_kcontrol_tlv_rw_t)(काष्ठा snd_kcontrol *kcontrol,
				    पूर्णांक op_flag, /* SNDRV_CTL_TLV_OP_XXX */
				    अचिन्हित पूर्णांक size,
				    अचिन्हित पूर्णांक __user *tlv);

/* पूर्णांकernal flag क्रम skipping validations */
#अगर_घोषित CONFIG_SND_CTL_VALIDATION
#घोषणा SNDRV_CTL_ELEM_ACCESS_SKIP_CHECK	(1 << 24)
#घोषणा snd_ctl_skip_validation(info) \
	((info)->access & SNDRV_CTL_ELEM_ACCESS_SKIP_CHECK)
#अन्यथा
#घोषणा SNDRV_CTL_ELEM_ACCESS_SKIP_CHECK	0
#घोषणा snd_ctl_skip_validation(info)		true
#पूर्ण_अगर

/* kernel only - LED bits */
#घोषणा SNDRV_CTL_ELEM_ACCESS_LED_SHIFT		25
#घोषणा SNDRV_CTL_ELEM_ACCESS_LED_MASK		(7<<25) /* kernel three bits - LED group */
#घोषणा SNDRV_CTL_ELEM_ACCESS_SPK_LED		(1<<25) /* kernel speaker (output) LED flag */
#घोषणा SNDRV_CTL_ELEM_ACCESS_MIC_LED		(2<<25) /* kernel microphone (input) LED flag */

क्रमागत अणु
	SNDRV_CTL_TLV_OP_READ = 0,
	SNDRV_CTL_TLV_OP_WRITE = 1,
	SNDRV_CTL_TLV_OP_CMD = -1,
पूर्ण;

काष्ठा snd_kcontrol_new अणु
	snd_ctl_elem_अगरace_t अगरace;	/* पूर्णांकerface identअगरier */
	अचिन्हित पूर्णांक device;		/* device/client number */
	अचिन्हित पूर्णांक subdevice;		/* subdevice (substream) number */
	स्थिर अक्षर *name;		/* ASCII name of item */
	अचिन्हित पूर्णांक index;		/* index of item */
	अचिन्हित पूर्णांक access;		/* access rights */
	अचिन्हित पूर्णांक count;		/* count of same elements */
	snd_kcontrol_info_t *info;
	snd_kcontrol_get_t *get;
	snd_kcontrol_put_t *put;
	जोड़ अणु
		snd_kcontrol_tlv_rw_t *c;
		स्थिर अचिन्हित पूर्णांक *p;
	पूर्ण tlv;
	अचिन्हित दीर्घ निजी_value;
पूर्ण;

काष्ठा snd_kcontrol_अस्थिर अणु
	काष्ठा snd_ctl_file *owner;	/* locked */
	अचिन्हित पूर्णांक access;	/* access rights */
पूर्ण;

काष्ठा snd_kcontrol अणु
	काष्ठा list_head list;		/* list of controls */
	काष्ठा snd_ctl_elem_id id;
	अचिन्हित पूर्णांक count;		/* count of same elements */
	snd_kcontrol_info_t *info;
	snd_kcontrol_get_t *get;
	snd_kcontrol_put_t *put;
	जोड़ अणु
		snd_kcontrol_tlv_rw_t *c;
		स्थिर अचिन्हित पूर्णांक *p;
	पूर्ण tlv;
	अचिन्हित दीर्घ निजी_value;
	व्योम *निजी_data;
	व्योम (*निजी_मुक्त)(काष्ठा snd_kcontrol *kcontrol);
	काष्ठा snd_kcontrol_अस्थिर vd[];	/* अस्थिर data */
पूर्ण;

#घोषणा snd_kcontrol(n) list_entry(n, काष्ठा snd_kcontrol, list)

काष्ठा snd_kctl_event अणु
	काष्ठा list_head list;	/* list of events */
	काष्ठा snd_ctl_elem_id id;
	अचिन्हित पूर्णांक mask;
पूर्ण;

#घोषणा snd_kctl_event(n) list_entry(n, काष्ठा snd_kctl_event, list)

काष्ठा pid;

क्रमागत अणु
	SND_CTL_SUBDEV_PCM,
	SND_CTL_SUBDEV_RAWMIDI,
	SND_CTL_SUBDEV_ITEMS,
पूर्ण;

काष्ठा snd_ctl_file अणु
	काष्ठा list_head list;		/* list of all control files */
	काष्ठा snd_card *card;
	काष्ठा pid *pid;
	पूर्णांक preferred_subdevice[SND_CTL_SUBDEV_ITEMS];
	रुको_queue_head_t change_sleep;
	spinlock_t पढ़ो_lock;
	काष्ठा fasync_काष्ठा *fasync;
	पूर्णांक subscribed;			/* पढ़ो पूर्णांकerface is activated */
	काष्ठा list_head events;	/* रुकोing events क्रम पढ़ो */
पूर्ण;

काष्ठा snd_ctl_layer_ops अणु
	काष्ठा snd_ctl_layer_ops *next;
	स्थिर अक्षर *module_name;
	व्योम (*lरेजिस्टर)(काष्ठा snd_card *card);
	व्योम (*ldisconnect)(काष्ठा snd_card *card);
	व्योम (*lnotअगरy)(काष्ठा snd_card *card, अचिन्हित पूर्णांक mask, काष्ठा snd_kcontrol *kctl, अचिन्हित पूर्णांक ioff);
पूर्ण;

#घोषणा snd_ctl_file(n) list_entry(n, काष्ठा snd_ctl_file, list)

प्रकार पूर्णांक (*snd_kctl_ioctl_func_t) (काष्ठा snd_card * card,
				      काष्ठा snd_ctl_file * control,
				      अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);

व्योम snd_ctl_notअगरy(काष्ठा snd_card * card, अचिन्हित पूर्णांक mask, काष्ठा snd_ctl_elem_id * id);
व्योम snd_ctl_notअगरy_one(काष्ठा snd_card * card, अचिन्हित पूर्णांक mask, काष्ठा snd_kcontrol * kctl, अचिन्हित पूर्णांक ioff);

काष्ठा snd_kcontrol *snd_ctl_new1(स्थिर काष्ठा snd_kcontrol_new * kcontrolnew, व्योम * निजी_data);
व्योम snd_ctl_मुक्त_one(काष्ठा snd_kcontrol * kcontrol);
पूर्णांक snd_ctl_add(काष्ठा snd_card * card, काष्ठा snd_kcontrol * kcontrol);
पूर्णांक snd_ctl_हटाओ(काष्ठा snd_card * card, काष्ठा snd_kcontrol * kcontrol);
पूर्णांक snd_ctl_replace(काष्ठा snd_card *card, काष्ठा snd_kcontrol *kcontrol, bool add_on_replace);
पूर्णांक snd_ctl_हटाओ_id(काष्ठा snd_card * card, काष्ठा snd_ctl_elem_id *id);
पूर्णांक snd_ctl_नाम_id(काष्ठा snd_card * card, काष्ठा snd_ctl_elem_id *src_id, काष्ठा snd_ctl_elem_id *dst_id);
पूर्णांक snd_ctl_activate_id(काष्ठा snd_card *card, काष्ठा snd_ctl_elem_id *id, पूर्णांक active);
काष्ठा snd_kcontrol *snd_ctl_find_numid(काष्ठा snd_card * card, अचिन्हित पूर्णांक numid);
काष्ठा snd_kcontrol *snd_ctl_find_id(काष्ठा snd_card * card, काष्ठा snd_ctl_elem_id *id);

पूर्णांक snd_ctl_create(काष्ठा snd_card *card);

पूर्णांक snd_ctl_रेजिस्टर_ioctl(snd_kctl_ioctl_func_t fcn);
पूर्णांक snd_ctl_unरेजिस्टर_ioctl(snd_kctl_ioctl_func_t fcn);
#अगर_घोषित CONFIG_COMPAT
पूर्णांक snd_ctl_रेजिस्टर_ioctl_compat(snd_kctl_ioctl_func_t fcn);
पूर्णांक snd_ctl_unरेजिस्टर_ioctl_compat(snd_kctl_ioctl_func_t fcn);
#अन्यथा
#घोषणा snd_ctl_रेजिस्टर_ioctl_compat(fcn)
#घोषणा snd_ctl_unरेजिस्टर_ioctl_compat(fcn)
#पूर्ण_अगर

पूर्णांक snd_ctl_request_layer(स्थिर अक्षर *module_name);
व्योम snd_ctl_रेजिस्टर_layer(काष्ठा snd_ctl_layer_ops *lops);
व्योम snd_ctl_disconnect_layer(काष्ठा snd_ctl_layer_ops *lops);

पूर्णांक snd_ctl_get_preferred_subdevice(काष्ठा snd_card *card, पूर्णांक type);

अटल अंतरभूत अचिन्हित पूर्णांक snd_ctl_get_ioffnum(काष्ठा snd_kcontrol *kctl, काष्ठा snd_ctl_elem_id *id)
अणु
	अचिन्हित पूर्णांक ioff = id->numid - kctl->id.numid;
	वापस array_index_nospec(ioff, kctl->count);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक snd_ctl_get_ioffidx(काष्ठा snd_kcontrol *kctl, काष्ठा snd_ctl_elem_id *id)
अणु
	अचिन्हित पूर्णांक ioff = id->index - kctl->id.index;
	वापस array_index_nospec(ioff, kctl->count);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक snd_ctl_get_ioff(काष्ठा snd_kcontrol *kctl, काष्ठा snd_ctl_elem_id *id)
अणु
	अगर (id->numid) अणु
		वापस snd_ctl_get_ioffnum(kctl, id);
	पूर्ण अन्यथा अणु
		वापस snd_ctl_get_ioffidx(kctl, id);
	पूर्ण
पूर्ण

अटल अंतरभूत काष्ठा snd_ctl_elem_id *snd_ctl_build_ioff(काष्ठा snd_ctl_elem_id *dst_id,
						    काष्ठा snd_kcontrol *src_kctl,
						    अचिन्हित पूर्णांक offset)
अणु
	*dst_id = src_kctl->id;
	dst_id->index += offset;
	dst_id->numid += offset;
	वापस dst_id;
पूर्ण

/*
 * Frequently used control callbacks/helpers
 */
पूर्णांक snd_ctl_boolean_mono_info(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_info *uinfo);
पूर्णांक snd_ctl_boolean_stereo_info(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_info *uinfo);
पूर्णांक snd_ctl_क्रमागत_info(काष्ठा snd_ctl_elem_info *info, अचिन्हित पूर्णांक channels,
		      अचिन्हित पूर्णांक items, स्थिर अक्षर *स्थिर names[]);

/*
 * भव master control
 */
काष्ठा snd_kcontrol *snd_ctl_make_भव_master(अक्षर *name,
						 स्थिर अचिन्हित पूर्णांक *tlv);
पूर्णांक _snd_ctl_add_follower(काष्ठा snd_kcontrol *master,
			  काष्ठा snd_kcontrol *follower,
			  अचिन्हित पूर्णांक flags);
/* optional flags क्रम follower */
#घोषणा SND_CTL_FOLLOWER_NEED_UPDATE	(1 << 0)

/**
 * snd_ctl_add_follower - Add a भव follower control
 * @master: vmaster element
 * @follower: follower element to add
 *
 * Add a भव follower control to the given master element created via
 * snd_ctl_create_भव_master() beक्रमehand.
 *
 * All followers must be the same type (वापसing the same inक्रमmation
 * via info callback).  The function करोesn't check it, so it's your
 * responsibility.
 *
 * Also, some additional limitations:
 * at most two channels,
 * logarithmic volume control (dB level) thus no linear volume,
 * master can only attenuate the volume without gain
 *
 * Return: Zero अगर successful or a negative error code.
 */
अटल अंतरभूत पूर्णांक
snd_ctl_add_follower(काष्ठा snd_kcontrol *master, काष्ठा snd_kcontrol *follower)
अणु
	वापस _snd_ctl_add_follower(master, follower, 0);
पूर्ण

/**
 * snd_ctl_add_follower_uncached - Add a भव follower control
 * @master: vmaster element
 * @follower: follower element to add
 *
 * Add a भव follower control to the given master.
 * Unlike snd_ctl_add_follower(), the element added via this function
 * is supposed to have अस्थिर values, and get callback is called
 * at each समय queried from the master.
 *
 * When the control peeks the hardware values directly and the value
 * can be changed by other means than the put callback of the element,
 * this function should be used to keep the value always up-to-date.
 *
 * Return: Zero अगर successful or a negative error code.
 */
अटल अंतरभूत पूर्णांक
snd_ctl_add_follower_uncached(काष्ठा snd_kcontrol *master,
			      काष्ठा snd_kcontrol *follower)
अणु
	वापस _snd_ctl_add_follower(master, follower, SND_CTL_FOLLOWER_NEED_UPDATE);
पूर्ण

पूर्णांक snd_ctl_add_vmaster_hook(काष्ठा snd_kcontrol *kctl,
			     व्योम (*hook)(व्योम *निजी_data, पूर्णांक),
			     व्योम *निजी_data);
व्योम snd_ctl_sync_vmaster(काष्ठा snd_kcontrol *kctl, bool hook_only);
#घोषणा snd_ctl_sync_vmaster_hook(kctl)	snd_ctl_sync_vmaster(kctl, true)
पूर्णांक snd_ctl_apply_vmaster_followers(काष्ठा snd_kcontrol *kctl,
				    पूर्णांक (*func)(काष्ठा snd_kcontrol *vfollower,
						काष्ठा snd_kcontrol *follower,
						व्योम *arg),
				    व्योम *arg);

/*
 * Control LED trigger layer
 */
#घोषणा SND_CTL_LAYER_MODULE_LED	"snd-ctl-led"

#अगर IS_MODULE(CONFIG_SND_CTL_LED)
अटल अंतरभूत पूर्णांक snd_ctl_led_request(व्योम) अणु वापस snd_ctl_request_layer(SND_CTL_LAYER_MODULE_LED); पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक snd_ctl_led_request(व्योम) अणु वापस 0; पूर्ण
#पूर्ण_अगर

/*
 * Helper functions क्रम jack-detection controls
 */
काष्ठा snd_kcontrol *
snd_kctl_jack_new(स्थिर अक्षर *name, काष्ठा snd_card *card);
व्योम snd_kctl_jack_report(काष्ठा snd_card *card,
			  काष्ठा snd_kcontrol *kctl, bool status);

#पूर्ण_अगर	/* __SOUND_CONTROL_H */
