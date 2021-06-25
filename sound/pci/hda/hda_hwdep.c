<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * HWDEP Interface क्रम HD-audio codec
 *
 * Copyright (c) 2007 Takashi Iwai <tiwai@suse.de>
 */

#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/compat.h>
#समावेश <linux/nospec.h>
#समावेश <sound/core.h>
#समावेश <sound/hda_codec.h>
#समावेश "hda_local.h"
#समावेश <sound/hda_hwdep.h>
#समावेश <sound/minors.h>

/*
 * ग_लिखो/पढ़ो an out-of-bound verb
 */
अटल पूर्णांक verb_ग_लिखो_ioctl(काष्ठा hda_codec *codec,
			    काष्ठा hda_verb_ioctl __user *arg)
अणु
	u32 verb, res;

	अगर (get_user(verb, &arg->verb))
		वापस -EFAULT;
	res = snd_hda_codec_पढ़ो(codec, verb >> 24, 0,
				 (verb >> 8) & 0xffff, verb & 0xff);
	अगर (put_user(res, &arg->res))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक get_wcap_ioctl(काष्ठा hda_codec *codec,
			  काष्ठा hda_verb_ioctl __user *arg)
अणु
	u32 verb, res;
	
	अगर (get_user(verb, &arg->verb))
		वापस -EFAULT;
	/* खोलो-code get_wcaps(verb>>24) with nospec */
	verb >>= 24;
	अगर (verb < codec->core.start_nid ||
	    verb >= codec->core.start_nid + codec->core.num_nodes) अणु
		res = 0;
	पूर्ण अन्यथा अणु
		verb -= codec->core.start_nid;
		verb = array_index_nospec(verb, codec->core.num_nodes);
		res = codec->wcaps[verb];
	पूर्ण
	अगर (put_user(res, &arg->res))
		वापस -EFAULT;
	वापस 0;
पूर्ण


/*
 */
अटल पूर्णांक hda_hwdep_ioctl(काष्ठा snd_hwdep *hw, काष्ठा file *file,
			   अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा hda_codec *codec = hw->निजी_data;
	व्योम __user *argp = (व्योम __user *)arg;

	चयन (cmd) अणु
	हाल HDA_IOCTL_PVERSION:
		वापस put_user(HDA_HWDEP_VERSION, (पूर्णांक __user *)argp);
	हाल HDA_IOCTL_VERB_WRITE:
		वापस verb_ग_लिखो_ioctl(codec, argp);
	हाल HDA_IOCTL_GET_WCAP:
		वापस get_wcap_ioctl(codec, argp);
	पूर्ण
	वापस -ENOIOCTLCMD;
पूर्ण

#अगर_घोषित CONFIG_COMPAT
अटल पूर्णांक hda_hwdep_ioctl_compat(काष्ठा snd_hwdep *hw, काष्ठा file *file,
				  अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	वापस hda_hwdep_ioctl(hw, file, cmd, (अचिन्हित दीर्घ)compat_ptr(arg));
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक hda_hwdep_खोलो(काष्ठा snd_hwdep *hw, काष्ठा file *file)
अणु
#अगर_अघोषित CONFIG_SND_DEBUG_VERBOSE
	अगर (!capable(CAP_SYS_RAWIO))
		वापस -EACCES;
#पूर्ण_अगर
	वापस 0;
पूर्ण

पूर्णांक snd_hda_create_hwdep(काष्ठा hda_codec *codec)
अणु
	अक्षर hwname[16];
	काष्ठा snd_hwdep *hwdep;
	पूर्णांक err;

	प्र_लिखो(hwname, "HDA Codec %d", codec->addr);
	err = snd_hwdep_new(codec->card, hwname, codec->addr, &hwdep);
	अगर (err < 0)
		वापस err;
	codec->hwdep = hwdep;
	प्र_लिखो(hwdep->name, "HDA Codec %d", codec->addr);
	hwdep->अगरace = SNDRV_HWDEP_IFACE_HDA;
	hwdep->निजी_data = codec;
	hwdep->exclusive = 1;

	hwdep->ops.खोलो = hda_hwdep_खोलो;
	hwdep->ops.ioctl = hda_hwdep_ioctl;
#अगर_घोषित CONFIG_COMPAT
	hwdep->ops.ioctl_compat = hda_hwdep_ioctl_compat;
#पूर्ण_अगर

	/* क्रम sysfs */
	hwdep->dev.groups = snd_hda_dev_attr_groups;
	dev_set_drvdata(&hwdep->dev, codec);

	वापस 0;
पूर्ण
