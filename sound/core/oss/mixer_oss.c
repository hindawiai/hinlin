<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  OSS emulation layer क्रम the mixer पूर्णांकerface
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 */

#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/समय.स>
#समावेश <linux/माला.स>
#समावेश <linux/module.h>
#समावेश <linux/compat.h>
#समावेश <sound/core.h>
#समावेश <sound/minors.h>
#समावेश <sound/control.h>
#समावेश <sound/info.h>
#समावेश <sound/mixer_oss.h>
#समावेश <linux/soundcard.h>

#घोषणा OSS_ALSAEMULVER         _SIOR ('M', 249, पूर्णांक)

MODULE_AUTHOR("Jaroslav Kysela <perex@perex.cz>");
MODULE_DESCRIPTION("Mixer OSS emulation for ALSA.");
MODULE_LICENSE("GPL");
MODULE_ALIAS_SNDRV_MINOR(SNDRV_MINOR_OSS_MIXER);

अटल पूर्णांक snd_mixer_oss_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा snd_card *card;
	काष्ठा snd_mixer_oss_file *fmixer;
	पूर्णांक err;

	err = nonseekable_खोलो(inode, file);
	अगर (err < 0)
		वापस err;

	card = snd_lookup_oss_minor_data(iminor(inode),
					 SNDRV_OSS_DEVICE_TYPE_MIXER);
	अगर (card == शून्य)
		वापस -ENODEV;
	अगर (card->mixer_oss == शून्य) अणु
		snd_card_unref(card);
		वापस -ENODEV;
	पूर्ण
	err = snd_card_file_add(card, file);
	अगर (err < 0) अणु
		snd_card_unref(card);
		वापस err;
	पूर्ण
	fmixer = kzalloc(माप(*fmixer), GFP_KERNEL);
	अगर (fmixer == शून्य) अणु
		snd_card_file_हटाओ(card, file);
		snd_card_unref(card);
		वापस -ENOMEM;
	पूर्ण
	fmixer->card = card;
	fmixer->mixer = card->mixer_oss;
	file->निजी_data = fmixer;
	अगर (!try_module_get(card->module)) अणु
		kमुक्त(fmixer);
		snd_card_file_हटाओ(card, file);
		snd_card_unref(card);
		वापस -EFAULT;
	पूर्ण
	snd_card_unref(card);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_mixer_oss_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा snd_mixer_oss_file *fmixer;

	अगर (file->निजी_data) अणु
		fmixer = file->निजी_data;
		module_put(fmixer->card->module);
		snd_card_file_हटाओ(fmixer->card, file);
		kमुक्त(fmixer);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_mixer_oss_info(काष्ठा snd_mixer_oss_file *fmixer,
			      mixer_info __user *_info)
अणु
	काष्ठा snd_card *card = fmixer->card;
	काष्ठा snd_mixer_oss *mixer = fmixer->mixer;
	काष्ठा mixer_info info;
	
	स_रखो(&info, 0, माप(info));
	strscpy(info.id, mixer && mixer->id[0] ? mixer->id : card->driver, माप(info.id));
	strscpy(info.name, mixer && mixer->name[0] ? mixer->name : card->mixername, माप(info.name));
	info.modअगरy_counter = card->mixer_oss_change_count;
	अगर (copy_to_user(_info, &info, माप(info)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_mixer_oss_info_obsolete(काष्ठा snd_mixer_oss_file *fmixer,
				       _old_mixer_info __user *_info)
अणु
	काष्ठा snd_card *card = fmixer->card;
	काष्ठा snd_mixer_oss *mixer = fmixer->mixer;
	_old_mixer_info info;
	
	स_रखो(&info, 0, माप(info));
	strscpy(info.id, mixer && mixer->id[0] ? mixer->id : card->driver, माप(info.id));
	strscpy(info.name, mixer && mixer->name[0] ? mixer->name : card->mixername, माप(info.name));
	अगर (copy_to_user(_info, &info, माप(info)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_mixer_oss_caps(काष्ठा snd_mixer_oss_file *fmixer)
अणु
	काष्ठा snd_mixer_oss *mixer = fmixer->mixer;
	पूर्णांक result = 0;

	अगर (mixer == शून्य)
		वापस -EIO;
	अगर (mixer->get_recsrc && mixer->put_recsrc)
		result |= SOUND_CAP_EXCL_INPUT;
	वापस result;
पूर्ण

अटल पूर्णांक snd_mixer_oss_devmask(काष्ठा snd_mixer_oss_file *fmixer)
अणु
	काष्ठा snd_mixer_oss *mixer = fmixer->mixer;
	काष्ठा snd_mixer_oss_slot *pslot;
	पूर्णांक result = 0, chn;

	अगर (mixer == शून्य)
		वापस -EIO;
	क्रम (chn = 0; chn < 31; chn++) अणु
		pslot = &mixer->slots[chn];
		अगर (pslot->put_volume || pslot->put_recsrc)
			result |= 1 << chn;
	पूर्ण
	वापस result;
पूर्ण

अटल पूर्णांक snd_mixer_oss_stereodevs(काष्ठा snd_mixer_oss_file *fmixer)
अणु
	काष्ठा snd_mixer_oss *mixer = fmixer->mixer;
	काष्ठा snd_mixer_oss_slot *pslot;
	पूर्णांक result = 0, chn;

	अगर (mixer == शून्य)
		वापस -EIO;
	क्रम (chn = 0; chn < 31; chn++) अणु
		pslot = &mixer->slots[chn];
		अगर (pslot->put_volume && pslot->stereo)
			result |= 1 << chn;
	पूर्ण
	वापस result;
पूर्ण

अटल पूर्णांक snd_mixer_oss_recmask(काष्ठा snd_mixer_oss_file *fmixer)
अणु
	काष्ठा snd_mixer_oss *mixer = fmixer->mixer;
	पूर्णांक result = 0;

	अगर (mixer == शून्य)
		वापस -EIO;
	अगर (mixer->put_recsrc && mixer->get_recsrc) अणु	/* exclusive */
		result = mixer->mask_recsrc;
	पूर्ण अन्यथा अणु
		काष्ठा snd_mixer_oss_slot *pslot;
		पूर्णांक chn;
		क्रम (chn = 0; chn < 31; chn++) अणु
			pslot = &mixer->slots[chn];
			अगर (pslot->put_recsrc)
				result |= 1 << chn;
		पूर्ण
	पूर्ण
	वापस result;
पूर्ण

अटल पूर्णांक snd_mixer_oss_get_recsrc(काष्ठा snd_mixer_oss_file *fmixer)
अणु
	काष्ठा snd_mixer_oss *mixer = fmixer->mixer;
	पूर्णांक result = 0;

	अगर (mixer == शून्य)
		वापस -EIO;
	अगर (mixer->put_recsrc && mixer->get_recsrc) अणु	/* exclusive */
		पूर्णांक err;
		अचिन्हित पूर्णांक index;
		अगर ((err = mixer->get_recsrc(fmixer, &index)) < 0)
			वापस err;
		result = 1 << index;
	पूर्ण अन्यथा अणु
		काष्ठा snd_mixer_oss_slot *pslot;
		पूर्णांक chn;
		क्रम (chn = 0; chn < 31; chn++) अणु
			pslot = &mixer->slots[chn];
			अगर (pslot->get_recsrc) अणु
				पूर्णांक active = 0;
				pslot->get_recsrc(fmixer, pslot, &active);
				अगर (active)
					result |= 1 << chn;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस mixer->oss_recsrc = result;
पूर्ण

अटल पूर्णांक snd_mixer_oss_set_recsrc(काष्ठा snd_mixer_oss_file *fmixer, पूर्णांक recsrc)
अणु
	काष्ठा snd_mixer_oss *mixer = fmixer->mixer;
	काष्ठा snd_mixer_oss_slot *pslot;
	पूर्णांक chn, active;
	अचिन्हित पूर्णांक index;
	पूर्णांक result = 0;

	अगर (mixer == शून्य)
		वापस -EIO;
	अगर (mixer->get_recsrc && mixer->put_recsrc) अणु	/* exclusive input */
		अगर (recsrc & ~mixer->oss_recsrc)
			recsrc &= ~mixer->oss_recsrc;
		mixer->put_recsrc(fmixer, ffz(~recsrc));
		mixer->get_recsrc(fmixer, &index);
		result = 1 << index;
	पूर्ण
	क्रम (chn = 0; chn < 31; chn++) अणु
		pslot = &mixer->slots[chn];
		अगर (pslot->put_recsrc) अणु
			active = (recsrc & (1 << chn)) ? 1 : 0;
			pslot->put_recsrc(fmixer, pslot, active);
		पूर्ण
	पूर्ण
	अगर (! result) अणु
		क्रम (chn = 0; chn < 31; chn++) अणु
			pslot = &mixer->slots[chn];
			अगर (pslot->get_recsrc) अणु
				active = 0;
				pslot->get_recsrc(fmixer, pslot, &active);
				अगर (active)
					result |= 1 << chn;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस result;
पूर्ण

अटल पूर्णांक snd_mixer_oss_get_volume(काष्ठा snd_mixer_oss_file *fmixer, पूर्णांक slot)
अणु
	काष्ठा snd_mixer_oss *mixer = fmixer->mixer;
	काष्ठा snd_mixer_oss_slot *pslot;
	पूर्णांक result = 0, left, right;

	अगर (mixer == शून्य || slot > 30)
		वापस -EIO;
	pslot = &mixer->slots[slot];
	left = pslot->volume[0];
	right = pslot->volume[1];
	अगर (pslot->get_volume)
		result = pslot->get_volume(fmixer, pslot, &left, &right);
	अगर (!pslot->stereo)
		right = left;
	अगर (snd_BUG_ON(left < 0 || left > 100))
		वापस -EIO;
	अगर (snd_BUG_ON(right < 0 || right > 100))
		वापस -EIO;
	अगर (result >= 0) अणु
		pslot->volume[0] = left;
		pslot->volume[1] = right;
	 	result = (left & 0xff) | ((right & 0xff) << 8);
	पूर्ण
	वापस result;
पूर्ण

अटल पूर्णांक snd_mixer_oss_set_volume(काष्ठा snd_mixer_oss_file *fmixer,
				    पूर्णांक slot, पूर्णांक volume)
अणु
	काष्ठा snd_mixer_oss *mixer = fmixer->mixer;
	काष्ठा snd_mixer_oss_slot *pslot;
	पूर्णांक result = 0, left = volume & 0xff, right = (volume >> 8) & 0xff;

	अगर (mixer == शून्य || slot > 30)
		वापस -EIO;
	pslot = &mixer->slots[slot];
	अगर (left > 100)
		left = 100;
	अगर (right > 100)
		right = 100;
	अगर (!pslot->stereo)
		right = left;
	अगर (pslot->put_volume)
		result = pslot->put_volume(fmixer, pslot, left, right);
	अगर (result < 0)
		वापस result;
	pslot->volume[0] = left;
	pslot->volume[1] = right;
 	वापस (left & 0xff) | ((right & 0xff) << 8);
पूर्ण

अटल पूर्णांक snd_mixer_oss_ioctl1(काष्ठा snd_mixer_oss_file *fmixer, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	व्योम __user *argp = (व्योम __user *)arg;
	पूर्णांक __user *p = argp;
	पूर्णांक पंचांगp;

	अगर (snd_BUG_ON(!fmixer))
		वापस -ENXIO;
	अगर (((cmd >> 8) & 0xff) == 'M') अणु
		चयन (cmd) अणु
		हाल SOUND_MIXER_INFO:
			वापस snd_mixer_oss_info(fmixer, argp);
		हाल SOUND_OLD_MIXER_INFO:
 			वापस snd_mixer_oss_info_obsolete(fmixer, argp);
		हाल SOUND_MIXER_WRITE_RECSRC:
			अगर (get_user(पंचांगp, p))
				वापस -EFAULT;
			पंचांगp = snd_mixer_oss_set_recsrc(fmixer, पंचांगp);
			अगर (पंचांगp < 0)
				वापस पंचांगp;
			वापस put_user(पंचांगp, p);
		हाल OSS_GETVERSION:
			वापस put_user(SNDRV_OSS_VERSION, p);
		हाल OSS_ALSAEMULVER:
			वापस put_user(1, p);
		हाल SOUND_MIXER_READ_DEVMASK:
			पंचांगp = snd_mixer_oss_devmask(fmixer);
			अगर (पंचांगp < 0)
				वापस पंचांगp;
			वापस put_user(पंचांगp, p);
		हाल SOUND_MIXER_READ_STEREODEVS:
			पंचांगp = snd_mixer_oss_stereodevs(fmixer);
			अगर (पंचांगp < 0)
				वापस पंचांगp;
			वापस put_user(पंचांगp, p);
		हाल SOUND_MIXER_READ_RECMASK:
			पंचांगp = snd_mixer_oss_recmask(fmixer);
			अगर (पंचांगp < 0)
				वापस पंचांगp;
			वापस put_user(पंचांगp, p);
		हाल SOUND_MIXER_READ_CAPS:
			पंचांगp = snd_mixer_oss_caps(fmixer);
			अगर (पंचांगp < 0)
				वापस पंचांगp;
			वापस put_user(पंचांगp, p);
		हाल SOUND_MIXER_READ_RECSRC:
			पंचांगp = snd_mixer_oss_get_recsrc(fmixer);
			अगर (पंचांगp < 0)
				वापस पंचांगp;
			वापस put_user(पंचांगp, p);
		पूर्ण
	पूर्ण
	अगर (cmd & SIOC_IN) अणु
		अगर (get_user(पंचांगp, p))
			वापस -EFAULT;
		पंचांगp = snd_mixer_oss_set_volume(fmixer, cmd & 0xff, पंचांगp);
		अगर (पंचांगp < 0)
			वापस पंचांगp;
		वापस put_user(पंचांगp, p);
	पूर्ण अन्यथा अगर (cmd & SIOC_OUT) अणु
		पंचांगp = snd_mixer_oss_get_volume(fmixer, cmd & 0xff);
		अगर (पंचांगp < 0)
			वापस पंचांगp;
		वापस put_user(पंचांगp, p);
	पूर्ण
	वापस -ENXIO;
पूर्ण

अटल दीर्घ snd_mixer_oss_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	वापस snd_mixer_oss_ioctl1(file->निजी_data, cmd, arg);
पूर्ण

पूर्णांक snd_mixer_oss_ioctl_card(काष्ठा snd_card *card, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा snd_mixer_oss_file fmixer;
	
	अगर (snd_BUG_ON(!card))
		वापस -ENXIO;
	अगर (card->mixer_oss == शून्य)
		वापस -ENXIO;
	स_रखो(&fmixer, 0, माप(fmixer));
	fmixer.card = card;
	fmixer.mixer = card->mixer_oss;
	वापस snd_mixer_oss_ioctl1(&fmixer, cmd, arg);
पूर्ण
EXPORT_SYMBOL(snd_mixer_oss_ioctl_card);

#अगर_घोषित CONFIG_COMPAT
/* all compatible */
अटल दीर्घ snd_mixer_oss_ioctl_compat(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
				       अचिन्हित दीर्घ arg)
अणु
	वापस snd_mixer_oss_ioctl1(file->निजी_data, cmd,
				    (अचिन्हित दीर्घ)compat_ptr(arg));
पूर्ण
#अन्यथा
#घोषणा snd_mixer_oss_ioctl_compat	शून्य
#पूर्ण_अगर

/*
 *  REGISTRATION PART
 */

अटल स्थिर काष्ठा file_operations snd_mixer_oss_f_ops =
अणु
	.owner =	THIS_MODULE,
	.खोलो =		snd_mixer_oss_खोलो,
	.release =	snd_mixer_oss_release,
	.llseek =	no_llseek,
	.unlocked_ioctl =	snd_mixer_oss_ioctl,
	.compat_ioctl =	snd_mixer_oss_ioctl_compat,
पूर्ण;

/*
 *  utilities
 */

अटल दीर्घ snd_mixer_oss_conv(दीर्घ val, दीर्घ omin, दीर्घ omax, दीर्घ nmin, दीर्घ nmax)
अणु
	दीर्घ orange = omax - omin, nrange = nmax - nmin;
	
	अगर (orange == 0)
		वापस 0;
	वापस DIV_ROUND_CLOSEST(nrange * (val - omin), orange) + nmin;
पूर्ण

/* convert from alsa native to oss values (0-100) */
अटल दीर्घ snd_mixer_oss_conv1(दीर्घ val, दीर्घ min, दीर्घ max, पूर्णांक *old)
अणु
	अगर (val == snd_mixer_oss_conv(*old, 0, 100, min, max))
		वापस *old;
	वापस snd_mixer_oss_conv(val, min, max, 0, 100);
पूर्ण

/* convert from oss to alsa native values */
अटल दीर्घ snd_mixer_oss_conv2(दीर्घ val, दीर्घ min, दीर्घ max)
अणु
	वापस snd_mixer_oss_conv(val, 0, 100, min, max);
पूर्ण

#अगर 0
अटल व्योम snd_mixer_oss_recsrce_set(काष्ठा snd_card *card, पूर्णांक slot)
अणु
	काष्ठा snd_mixer_oss *mixer = card->mixer_oss;
	अगर (mixer)
		mixer->mask_recsrc |= 1 << slot;
पूर्ण

अटल पूर्णांक snd_mixer_oss_recsrce_get(काष्ठा snd_card *card, पूर्णांक slot)
अणु
	काष्ठा snd_mixer_oss *mixer = card->mixer_oss;
	अगर (mixer && (mixer->mask_recsrc & (1 << slot)))
		वापस 1;
	वापस 0;
पूर्ण
#पूर्ण_अगर

#घोषणा SNDRV_MIXER_OSS_SIGNATURE		0x65999250

#घोषणा SNDRV_MIXER_OSS_ITEM_GLOBAL	0
#घोषणा SNDRV_MIXER_OSS_ITEM_GSWITCH	1
#घोषणा SNDRV_MIXER_OSS_ITEM_GROUTE	2
#घोषणा SNDRV_MIXER_OSS_ITEM_GVOLUME	3
#घोषणा SNDRV_MIXER_OSS_ITEM_PSWITCH	4
#घोषणा SNDRV_MIXER_OSS_ITEM_PROUTE	5
#घोषणा SNDRV_MIXER_OSS_ITEM_PVOLUME	6
#घोषणा SNDRV_MIXER_OSS_ITEM_CSWITCH	7
#घोषणा SNDRV_MIXER_OSS_ITEM_CROUTE	8
#घोषणा SNDRV_MIXER_OSS_ITEM_CVOLUME	9
#घोषणा SNDRV_MIXER_OSS_ITEM_CAPTURE	10

#घोषणा SNDRV_MIXER_OSS_ITEM_COUNT	11

#घोषणा SNDRV_MIXER_OSS_PRESENT_GLOBAL	(1<<0)
#घोषणा SNDRV_MIXER_OSS_PRESENT_GSWITCH	(1<<1)
#घोषणा SNDRV_MIXER_OSS_PRESENT_GROUTE	(1<<2)
#घोषणा SNDRV_MIXER_OSS_PRESENT_GVOLUME	(1<<3)
#घोषणा SNDRV_MIXER_OSS_PRESENT_PSWITCH	(1<<4)
#घोषणा SNDRV_MIXER_OSS_PRESENT_PROUTE	(1<<5)
#घोषणा SNDRV_MIXER_OSS_PRESENT_PVOLUME	(1<<6)
#घोषणा SNDRV_MIXER_OSS_PRESENT_CSWITCH	(1<<7)
#घोषणा SNDRV_MIXER_OSS_PRESENT_CROUTE	(1<<8)
#घोषणा SNDRV_MIXER_OSS_PRESENT_CVOLUME	(1<<9)
#घोषणा SNDRV_MIXER_OSS_PRESENT_CAPTURE	(1<<10)

काष्ठा slot अणु
	अचिन्हित पूर्णांक signature;
	अचिन्हित पूर्णांक present;
	अचिन्हित पूर्णांक channels;
	अचिन्हित पूर्णांक numid[SNDRV_MIXER_OSS_ITEM_COUNT];
	अचिन्हित पूर्णांक capture_item;
	स्थिर काष्ठा snd_mixer_oss_assign_table *asचिन्हित;
	अचिन्हित पूर्णांक allocated: 1;
पूर्ण;

#घोषणा ID_UNKNOWN	((अचिन्हित पूर्णांक)-1)

अटल काष्ठा snd_kcontrol *snd_mixer_oss_test_id(काष्ठा snd_mixer_oss *mixer, स्थिर अक्षर *name, पूर्णांक index)
अणु
	काष्ठा snd_card *card = mixer->card;
	काष्ठा snd_ctl_elem_id id;
	
	स_रखो(&id, 0, माप(id));
	id.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER;
	strscpy(id.name, name, माप(id.name));
	id.index = index;
	वापस snd_ctl_find_id(card, &id);
पूर्ण

अटल व्योम snd_mixer_oss_get_volume1_vol(काष्ठा snd_mixer_oss_file *fmixer,
					  काष्ठा snd_mixer_oss_slot *pslot,
					  अचिन्हित पूर्णांक numid,
					  पूर्णांक *left, पूर्णांक *right)
अणु
	काष्ठा snd_ctl_elem_info *uinfo;
	काष्ठा snd_ctl_elem_value *uctl;
	काष्ठा snd_kcontrol *kctl;
	काष्ठा snd_card *card = fmixer->card;

	अगर (numid == ID_UNKNOWN)
		वापस;
	करोwn_पढ़ो(&card->controls_rwsem);
	अगर ((kctl = snd_ctl_find_numid(card, numid)) == शून्य) अणु
		up_पढ़ो(&card->controls_rwsem);
		वापस;
	पूर्ण
	uinfo = kzalloc(माप(*uinfo), GFP_KERNEL);
	uctl = kzalloc(माप(*uctl), GFP_KERNEL);
	अगर (uinfo == शून्य || uctl == शून्य)
		जाओ __unalloc;
	अगर (kctl->info(kctl, uinfo))
		जाओ __unalloc;
	अगर (kctl->get(kctl, uctl))
		जाओ __unalloc;
	अगर (uinfo->type == SNDRV_CTL_ELEM_TYPE_BOOLEAN &&
	    uinfo->value.पूर्णांकeger.min == 0 && uinfo->value.पूर्णांकeger.max == 1)
		जाओ __unalloc;
	*left = snd_mixer_oss_conv1(uctl->value.पूर्णांकeger.value[0], uinfo->value.पूर्णांकeger.min, uinfo->value.पूर्णांकeger.max, &pslot->volume[0]);
	अगर (uinfo->count > 1)
		*right = snd_mixer_oss_conv1(uctl->value.पूर्णांकeger.value[1], uinfo->value.पूर्णांकeger.min, uinfo->value.पूर्णांकeger.max, &pslot->volume[1]);
      __unalloc:
	up_पढ़ो(&card->controls_rwsem);
      	kमुक्त(uctl);
      	kमुक्त(uinfo);
पूर्ण

अटल व्योम snd_mixer_oss_get_volume1_sw(काष्ठा snd_mixer_oss_file *fmixer,
					 काष्ठा snd_mixer_oss_slot *pslot,
					 अचिन्हित पूर्णांक numid,
					 पूर्णांक *left, पूर्णांक *right,
					 पूर्णांक route)
अणु
	काष्ठा snd_ctl_elem_info *uinfo;
	काष्ठा snd_ctl_elem_value *uctl;
	काष्ठा snd_kcontrol *kctl;
	काष्ठा snd_card *card = fmixer->card;

	अगर (numid == ID_UNKNOWN)
		वापस;
	करोwn_पढ़ो(&card->controls_rwsem);
	अगर ((kctl = snd_ctl_find_numid(card, numid)) == शून्य) अणु
		up_पढ़ो(&card->controls_rwsem);
		वापस;
	पूर्ण
	uinfo = kzalloc(माप(*uinfo), GFP_KERNEL);
	uctl = kzalloc(माप(*uctl), GFP_KERNEL);
	अगर (uinfo == शून्य || uctl == शून्य)
		जाओ __unalloc;
	अगर (kctl->info(kctl, uinfo))
		जाओ __unalloc;
	अगर (kctl->get(kctl, uctl))
		जाओ __unalloc;
	अगर (!uctl->value.पूर्णांकeger.value[0]) अणु
		*left = 0;
		अगर (uinfo->count == 1)
			*right = 0;
	पूर्ण
	अगर (uinfo->count > 1 && !uctl->value.पूर्णांकeger.value[route ? 3 : 1])
		*right = 0;
      __unalloc:
	up_पढ़ो(&card->controls_rwsem);
      	kमुक्त(uctl);
	kमुक्त(uinfo);
पूर्ण

अटल पूर्णांक snd_mixer_oss_get_volume1(काष्ठा snd_mixer_oss_file *fmixer,
				     काष्ठा snd_mixer_oss_slot *pslot,
				     पूर्णांक *left, पूर्णांक *right)
अणु
	काष्ठा slot *slot = pslot->निजी_data;
	
	*left = *right = 100;
	अगर (slot->present & SNDRV_MIXER_OSS_PRESENT_PVOLUME) अणु
		snd_mixer_oss_get_volume1_vol(fmixer, pslot, slot->numid[SNDRV_MIXER_OSS_ITEM_PVOLUME], left, right);
	पूर्ण अन्यथा अगर (slot->present & SNDRV_MIXER_OSS_PRESENT_GVOLUME) अणु
		snd_mixer_oss_get_volume1_vol(fmixer, pslot, slot->numid[SNDRV_MIXER_OSS_ITEM_GVOLUME], left, right);
	पूर्ण अन्यथा अगर (slot->present & SNDRV_MIXER_OSS_PRESENT_GLOBAL) अणु
		snd_mixer_oss_get_volume1_vol(fmixer, pslot, slot->numid[SNDRV_MIXER_OSS_ITEM_GLOBAL], left, right);
	पूर्ण
	अगर (slot->present & SNDRV_MIXER_OSS_PRESENT_PSWITCH) अणु
		snd_mixer_oss_get_volume1_sw(fmixer, pslot, slot->numid[SNDRV_MIXER_OSS_ITEM_PSWITCH], left, right, 0);
	पूर्ण अन्यथा अगर (slot->present & SNDRV_MIXER_OSS_PRESENT_GSWITCH) अणु
		snd_mixer_oss_get_volume1_sw(fmixer, pslot, slot->numid[SNDRV_MIXER_OSS_ITEM_GSWITCH], left, right, 0);
	पूर्ण अन्यथा अगर (slot->present & SNDRV_MIXER_OSS_PRESENT_PROUTE) अणु
		snd_mixer_oss_get_volume1_sw(fmixer, pslot, slot->numid[SNDRV_MIXER_OSS_ITEM_PROUTE], left, right, 1);
	पूर्ण अन्यथा अगर (slot->present & SNDRV_MIXER_OSS_PRESENT_GROUTE) अणु
		snd_mixer_oss_get_volume1_sw(fmixer, pslot, slot->numid[SNDRV_MIXER_OSS_ITEM_GROUTE], left, right, 1);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम snd_mixer_oss_put_volume1_vol(काष्ठा snd_mixer_oss_file *fmixer,
					  काष्ठा snd_mixer_oss_slot *pslot,
					  अचिन्हित पूर्णांक numid,
					  पूर्णांक left, पूर्णांक right)
अणु
	काष्ठा snd_ctl_elem_info *uinfo;
	काष्ठा snd_ctl_elem_value *uctl;
	काष्ठा snd_kcontrol *kctl;
	काष्ठा snd_card *card = fmixer->card;
	पूर्णांक res;

	अगर (numid == ID_UNKNOWN)
		वापस;
	करोwn_पढ़ो(&card->controls_rwsem);
	अगर ((kctl = snd_ctl_find_numid(card, numid)) == शून्य) अणु
		up_पढ़ो(&card->controls_rwsem);
		वापस;
	पूर्ण
	uinfo = kzalloc(माप(*uinfo), GFP_KERNEL);
	uctl = kzalloc(माप(*uctl), GFP_KERNEL);
	अगर (uinfo == शून्य || uctl == शून्य)
		जाओ __unalloc;
	अगर (kctl->info(kctl, uinfo))
		जाओ __unalloc;
	अगर (uinfo->type == SNDRV_CTL_ELEM_TYPE_BOOLEAN &&
	    uinfo->value.पूर्णांकeger.min == 0 && uinfo->value.पूर्णांकeger.max == 1)
		जाओ __unalloc;
	uctl->value.पूर्णांकeger.value[0] = snd_mixer_oss_conv2(left, uinfo->value.पूर्णांकeger.min, uinfo->value.पूर्णांकeger.max);
	अगर (uinfo->count > 1)
		uctl->value.पूर्णांकeger.value[1] = snd_mixer_oss_conv2(right, uinfo->value.पूर्णांकeger.min, uinfo->value.पूर्णांकeger.max);
	अगर ((res = kctl->put(kctl, uctl)) < 0)
		जाओ __unalloc;
	अगर (res > 0)
		snd_ctl_notअगरy(card, SNDRV_CTL_EVENT_MASK_VALUE, &kctl->id);
      __unalloc:
	up_पढ़ो(&card->controls_rwsem);
      	kमुक्त(uctl);
	kमुक्त(uinfo);
पूर्ण

अटल व्योम snd_mixer_oss_put_volume1_sw(काष्ठा snd_mixer_oss_file *fmixer,
					 काष्ठा snd_mixer_oss_slot *pslot,
					 अचिन्हित पूर्णांक numid,
					 पूर्णांक left, पूर्णांक right,
					 पूर्णांक route)
अणु
	काष्ठा snd_ctl_elem_info *uinfo;
	काष्ठा snd_ctl_elem_value *uctl;
	काष्ठा snd_kcontrol *kctl;
	काष्ठा snd_card *card = fmixer->card;
	पूर्णांक res;

	अगर (numid == ID_UNKNOWN)
		वापस;
	करोwn_पढ़ो(&card->controls_rwsem);
	अगर ((kctl = snd_ctl_find_numid(card, numid)) == शून्य) अणु
		up_पढ़ो(&card->controls_rwsem);
		वापस;
	पूर्ण
	uinfo = kzalloc(माप(*uinfo), GFP_KERNEL);
	uctl = kzalloc(माप(*uctl), GFP_KERNEL);
	अगर (uinfo == शून्य || uctl == शून्य)
		जाओ __unalloc;
	अगर (kctl->info(kctl, uinfo))
		जाओ __unalloc;
	अगर (uinfo->count > 1) अणु
		uctl->value.पूर्णांकeger.value[0] = left > 0 ? 1 : 0;
		uctl->value.पूर्णांकeger.value[route ? 3 : 1] = right > 0 ? 1 : 0;
		अगर (route) अणु
			uctl->value.पूर्णांकeger.value[1] =
			uctl->value.पूर्णांकeger.value[2] = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		uctl->value.पूर्णांकeger.value[0] = (left > 0 || right > 0) ? 1 : 0;
	पूर्ण
	अगर ((res = kctl->put(kctl, uctl)) < 0)
		जाओ __unalloc;
	अगर (res > 0)
		snd_ctl_notअगरy(card, SNDRV_CTL_EVENT_MASK_VALUE, &kctl->id);
      __unalloc:
	up_पढ़ो(&card->controls_rwsem);
      	kमुक्त(uctl);
	kमुक्त(uinfo);
पूर्ण

अटल पूर्णांक snd_mixer_oss_put_volume1(काष्ठा snd_mixer_oss_file *fmixer,
				     काष्ठा snd_mixer_oss_slot *pslot,
				     पूर्णांक left, पूर्णांक right)
अणु
	काष्ठा slot *slot = pslot->निजी_data;
	
	अगर (slot->present & SNDRV_MIXER_OSS_PRESENT_PVOLUME) अणु
		snd_mixer_oss_put_volume1_vol(fmixer, pslot, slot->numid[SNDRV_MIXER_OSS_ITEM_PVOLUME], left, right);
		अगर (slot->present & SNDRV_MIXER_OSS_PRESENT_CVOLUME)
			snd_mixer_oss_put_volume1_vol(fmixer, pslot, slot->numid[SNDRV_MIXER_OSS_ITEM_CVOLUME], left, right);
	पूर्ण अन्यथा अगर (slot->present & SNDRV_MIXER_OSS_PRESENT_CVOLUME) अणु
		snd_mixer_oss_put_volume1_vol(fmixer, pslot,
			slot->numid[SNDRV_MIXER_OSS_ITEM_CVOLUME], left, right);
	पूर्ण अन्यथा अगर (slot->present & SNDRV_MIXER_OSS_PRESENT_GVOLUME) अणु
		snd_mixer_oss_put_volume1_vol(fmixer, pslot, slot->numid[SNDRV_MIXER_OSS_ITEM_GVOLUME], left, right);
	पूर्ण अन्यथा अगर (slot->present & SNDRV_MIXER_OSS_PRESENT_GLOBAL) अणु
		snd_mixer_oss_put_volume1_vol(fmixer, pslot, slot->numid[SNDRV_MIXER_OSS_ITEM_GLOBAL], left, right);
	पूर्ण
	अगर (left || right) अणु
		अगर (slot->present & SNDRV_MIXER_OSS_PRESENT_PSWITCH)
			snd_mixer_oss_put_volume1_sw(fmixer, pslot, slot->numid[SNDRV_MIXER_OSS_ITEM_PSWITCH], left, right, 0);
		अगर (slot->present & SNDRV_MIXER_OSS_PRESENT_CSWITCH)
			snd_mixer_oss_put_volume1_sw(fmixer, pslot, slot->numid[SNDRV_MIXER_OSS_ITEM_CSWITCH], left, right, 0);
		अगर (slot->present & SNDRV_MIXER_OSS_PRESENT_GSWITCH)
			snd_mixer_oss_put_volume1_sw(fmixer, pslot, slot->numid[SNDRV_MIXER_OSS_ITEM_GSWITCH], left, right, 0);
		अगर (slot->present & SNDRV_MIXER_OSS_PRESENT_PROUTE)
			snd_mixer_oss_put_volume1_sw(fmixer, pslot, slot->numid[SNDRV_MIXER_OSS_ITEM_PROUTE], left, right, 1);
		अगर (slot->present & SNDRV_MIXER_OSS_PRESENT_CROUTE)
			snd_mixer_oss_put_volume1_sw(fmixer, pslot, slot->numid[SNDRV_MIXER_OSS_ITEM_CROUTE], left, right, 1);
		अगर (slot->present & SNDRV_MIXER_OSS_PRESENT_GROUTE)
			snd_mixer_oss_put_volume1_sw(fmixer, pslot, slot->numid[SNDRV_MIXER_OSS_ITEM_GROUTE], left, right, 1);
	पूर्ण अन्यथा अणु
		अगर (slot->present & SNDRV_MIXER_OSS_PRESENT_PSWITCH) अणु
			snd_mixer_oss_put_volume1_sw(fmixer, pslot, slot->numid[SNDRV_MIXER_OSS_ITEM_PSWITCH], left, right, 0);
		पूर्ण अन्यथा अगर (slot->present & SNDRV_MIXER_OSS_PRESENT_CSWITCH) अणु
			snd_mixer_oss_put_volume1_sw(fmixer, pslot, slot->numid[SNDRV_MIXER_OSS_ITEM_CSWITCH], left, right, 0);
		पूर्ण अन्यथा अगर (slot->present & SNDRV_MIXER_OSS_PRESENT_GSWITCH) अणु
			snd_mixer_oss_put_volume1_sw(fmixer, pslot, slot->numid[SNDRV_MIXER_OSS_ITEM_GSWITCH], left, right, 0);
		पूर्ण अन्यथा अगर (slot->present & SNDRV_MIXER_OSS_PRESENT_PROUTE) अणु
			snd_mixer_oss_put_volume1_sw(fmixer, pslot, slot->numid[SNDRV_MIXER_OSS_ITEM_PROUTE], left, right, 1);
		पूर्ण अन्यथा अगर (slot->present & SNDRV_MIXER_OSS_PRESENT_CROUTE) अणु
			snd_mixer_oss_put_volume1_sw(fmixer, pslot, slot->numid[SNDRV_MIXER_OSS_ITEM_CROUTE], left, right, 1);
		पूर्ण अन्यथा अगर (slot->present & SNDRV_MIXER_OSS_PRESENT_GROUTE) अणु
			snd_mixer_oss_put_volume1_sw(fmixer, pslot, slot->numid[SNDRV_MIXER_OSS_ITEM_GROUTE], left, right, 1);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_mixer_oss_get_recsrc1_sw(काष्ठा snd_mixer_oss_file *fmixer,
					काष्ठा snd_mixer_oss_slot *pslot,
					पूर्णांक *active)
अणु
	काष्ठा slot *slot = pslot->निजी_data;
	पूर्णांक left, right;
	
	left = right = 1;
	snd_mixer_oss_get_volume1_sw(fmixer, pslot, slot->numid[SNDRV_MIXER_OSS_ITEM_CSWITCH], &left, &right, 0);
	*active = (left || right) ? 1 : 0;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_mixer_oss_get_recsrc1_route(काष्ठा snd_mixer_oss_file *fmixer,
					   काष्ठा snd_mixer_oss_slot *pslot,
					   पूर्णांक *active)
अणु
	काष्ठा slot *slot = pslot->निजी_data;
	पूर्णांक left, right;
	
	left = right = 1;
	snd_mixer_oss_get_volume1_sw(fmixer, pslot, slot->numid[SNDRV_MIXER_OSS_ITEM_CROUTE], &left, &right, 1);
	*active = (left || right) ? 1 : 0;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_mixer_oss_put_recsrc1_sw(काष्ठा snd_mixer_oss_file *fmixer,
					काष्ठा snd_mixer_oss_slot *pslot,
					पूर्णांक active)
अणु
	काष्ठा slot *slot = pslot->निजी_data;
	
	snd_mixer_oss_put_volume1_sw(fmixer, pslot, slot->numid[SNDRV_MIXER_OSS_ITEM_CSWITCH], active, active, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_mixer_oss_put_recsrc1_route(काष्ठा snd_mixer_oss_file *fmixer,
					   काष्ठा snd_mixer_oss_slot *pslot,
					   पूर्णांक active)
अणु
	काष्ठा slot *slot = pslot->निजी_data;
	
	snd_mixer_oss_put_volume1_sw(fmixer, pslot, slot->numid[SNDRV_MIXER_OSS_ITEM_CROUTE], active, active, 1);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_mixer_oss_get_recsrc2(काष्ठा snd_mixer_oss_file *fmixer, अचिन्हित पूर्णांक *active_index)
अणु
	काष्ठा snd_card *card = fmixer->card;
	काष्ठा snd_mixer_oss *mixer = fmixer->mixer;
	काष्ठा snd_kcontrol *kctl;
	काष्ठा snd_mixer_oss_slot *pslot;
	काष्ठा slot *slot;
	काष्ठा snd_ctl_elem_info *uinfo;
	काष्ठा snd_ctl_elem_value *uctl;
	पूर्णांक err, idx;
	
	uinfo = kzalloc(माप(*uinfo), GFP_KERNEL);
	uctl = kzalloc(माप(*uctl), GFP_KERNEL);
	अगर (uinfo == शून्य || uctl == शून्य) अणु
		err = -ENOMEM;
		जाओ __मुक्त_only;
	पूर्ण
	करोwn_पढ़ो(&card->controls_rwsem);
	kctl = snd_mixer_oss_test_id(mixer, "Capture Source", 0);
	अगर (! kctl) अणु
		err = -ENOENT;
		जाओ __unlock;
	पूर्ण
	अगर ((err = kctl->info(kctl, uinfo)) < 0)
		जाओ __unlock;
	अगर ((err = kctl->get(kctl, uctl)) < 0)
		जाओ __unlock;
	क्रम (idx = 0; idx < 32; idx++) अणु
		अगर (!(mixer->mask_recsrc & (1 << idx)))
			जारी;
		pslot = &mixer->slots[idx];
		slot = pslot->निजी_data;
		अगर (slot->signature != SNDRV_MIXER_OSS_SIGNATURE)
			जारी;
		अगर (!(slot->present & SNDRV_MIXER_OSS_PRESENT_CAPTURE))
			जारी;
		अगर (slot->capture_item == uctl->value.क्रमागतerated.item[0]) अणु
			*active_index = idx;
			अवरोध;
		पूर्ण
	पूर्ण
	err = 0;
      __unlock:
     	up_पढ़ो(&card->controls_rwsem);
      __मुक्त_only:
      	kमुक्त(uctl);
      	kमुक्त(uinfo);
      	वापस err;
पूर्ण

अटल पूर्णांक snd_mixer_oss_put_recsrc2(काष्ठा snd_mixer_oss_file *fmixer, अचिन्हित पूर्णांक active_index)
अणु
	काष्ठा snd_card *card = fmixer->card;
	काष्ठा snd_mixer_oss *mixer = fmixer->mixer;
	काष्ठा snd_kcontrol *kctl;
	काष्ठा snd_mixer_oss_slot *pslot;
	काष्ठा slot *slot = शून्य;
	काष्ठा snd_ctl_elem_info *uinfo;
	काष्ठा snd_ctl_elem_value *uctl;
	पूर्णांक err;
	अचिन्हित पूर्णांक idx;

	uinfo = kzalloc(माप(*uinfo), GFP_KERNEL);
	uctl = kzalloc(माप(*uctl), GFP_KERNEL);
	अगर (uinfo == शून्य || uctl == शून्य) अणु
		err = -ENOMEM;
		जाओ __मुक्त_only;
	पूर्ण
	करोwn_पढ़ो(&card->controls_rwsem);
	kctl = snd_mixer_oss_test_id(mixer, "Capture Source", 0);
	अगर (! kctl) अणु
		err = -ENOENT;
		जाओ __unlock;
	पूर्ण
	अगर ((err = kctl->info(kctl, uinfo)) < 0)
		जाओ __unlock;
	क्रम (idx = 0; idx < 32; idx++) अणु
		अगर (!(mixer->mask_recsrc & (1 << idx)))
			जारी;
		pslot = &mixer->slots[idx];
		slot = pslot->निजी_data;
		अगर (slot->signature != SNDRV_MIXER_OSS_SIGNATURE)
			जारी;
		अगर (!(slot->present & SNDRV_MIXER_OSS_PRESENT_CAPTURE))
			जारी;
		अगर (idx == active_index)
			अवरोध;
		slot = शून्य;
	पूर्ण
	अगर (! slot)
		जाओ __unlock;
	क्रम (idx = 0; idx < uinfo->count; idx++)
		uctl->value.क्रमागतerated.item[idx] = slot->capture_item;
	err = kctl->put(kctl, uctl);
	अगर (err > 0)
		snd_ctl_notअगरy(fmixer->card, SNDRV_CTL_EVENT_MASK_VALUE, &kctl->id);
	err = 0;
      __unlock:
	up_पढ़ो(&card->controls_rwsem);
      __मुक्त_only:
	kमुक्त(uctl);
	kमुक्त(uinfo);
	वापस err;
पूर्ण

काष्ठा snd_mixer_oss_assign_table अणु
	पूर्णांक oss_id;
	स्थिर अक्षर *name;
	पूर्णांक index;
पूर्ण;

अटल पूर्णांक snd_mixer_oss_build_test(काष्ठा snd_mixer_oss *mixer, काष्ठा slot *slot, स्थिर अक्षर *name, पूर्णांक index, पूर्णांक item)
अणु
	काष्ठा snd_ctl_elem_info *info;
	काष्ठा snd_kcontrol *kcontrol;
	काष्ठा snd_card *card = mixer->card;
	पूर्णांक err;

	करोwn_पढ़ो(&card->controls_rwsem);
	kcontrol = snd_mixer_oss_test_id(mixer, name, index);
	अगर (kcontrol == शून्य) अणु
		up_पढ़ो(&card->controls_rwsem);
		वापस 0;
	पूर्ण
	info = kदो_स्मृति(माप(*info), GFP_KERNEL);
	अगर (! info) अणु
		up_पढ़ो(&card->controls_rwsem);
		वापस -ENOMEM;
	पूर्ण
	अगर ((err = kcontrol->info(kcontrol, info)) < 0) अणु
		up_पढ़ो(&card->controls_rwsem);
		kमुक्त(info);
		वापस err;
	पूर्ण
	slot->numid[item] = kcontrol->id.numid;
	up_पढ़ो(&card->controls_rwsem);
	अगर (info->count > slot->channels)
		slot->channels = info->count;
	slot->present |= 1 << item;
	kमुक्त(info);
	वापस 0;
पूर्ण

अटल व्योम snd_mixer_oss_slot_मुक्त(काष्ठा snd_mixer_oss_slot *chn)
अणु
	काष्ठा slot *p = chn->निजी_data;
	अगर (p) अणु
		अगर (p->allocated && p->asचिन्हित) अणु
			kमुक्त_स्थिर(p->asचिन्हित->name);
			kमुक्त_स्थिर(p->asचिन्हित);
		पूर्ण
		kमुक्त(p);
	पूर्ण
पूर्ण

अटल व्योम mixer_slot_clear(काष्ठा snd_mixer_oss_slot *rslot)
अणु
	पूर्णांक idx = rslot->number; /* remember this */
	अगर (rslot->निजी_मुक्त)
		rslot->निजी_मुक्त(rslot);
	स_रखो(rslot, 0, माप(*rslot));
	rslot->number = idx;
पूर्ण

/* In a separate function to keep gcc 3.2 happy - करो NOT merge this in
   snd_mixer_oss_build_input! */
अटल पूर्णांक snd_mixer_oss_build_test_all(काष्ठा snd_mixer_oss *mixer,
					स्थिर काष्ठा snd_mixer_oss_assign_table *ptr,
					काष्ठा slot *slot)
अणु
	अक्षर str[64];
	पूर्णांक err;

	err = snd_mixer_oss_build_test(mixer, slot, ptr->name, ptr->index,
				       SNDRV_MIXER_OSS_ITEM_GLOBAL);
	अगर (err)
		वापस err;
	प्र_लिखो(str, "%s Switch", ptr->name);
	err = snd_mixer_oss_build_test(mixer, slot, str, ptr->index,
				       SNDRV_MIXER_OSS_ITEM_GSWITCH);
	अगर (err)
		वापस err;
	प्र_लिखो(str, "%s Route", ptr->name);
	err = snd_mixer_oss_build_test(mixer, slot, str, ptr->index,
				       SNDRV_MIXER_OSS_ITEM_GROUTE);
	अगर (err)
		वापस err;
	प्र_लिखो(str, "%s Volume", ptr->name);
	err = snd_mixer_oss_build_test(mixer, slot, str, ptr->index,
				       SNDRV_MIXER_OSS_ITEM_GVOLUME);
	अगर (err)
		वापस err;
	प्र_लिखो(str, "%s Playback Switch", ptr->name);
	err = snd_mixer_oss_build_test(mixer, slot, str, ptr->index,
				       SNDRV_MIXER_OSS_ITEM_PSWITCH);
	अगर (err)
		वापस err;
	प्र_लिखो(str, "%s Playback Route", ptr->name);
	err = snd_mixer_oss_build_test(mixer, slot, str, ptr->index,
				       SNDRV_MIXER_OSS_ITEM_PROUTE);
	अगर (err)
		वापस err;
	प्र_लिखो(str, "%s Playback Volume", ptr->name);
	err = snd_mixer_oss_build_test(mixer, slot, str, ptr->index,
				       SNDRV_MIXER_OSS_ITEM_PVOLUME);
	अगर (err)
		वापस err;
	प्र_लिखो(str, "%s Capture Switch", ptr->name);
	err = snd_mixer_oss_build_test(mixer, slot, str, ptr->index,
				       SNDRV_MIXER_OSS_ITEM_CSWITCH);
	अगर (err)
		वापस err;
	प्र_लिखो(str, "%s Capture Route", ptr->name);
	err = snd_mixer_oss_build_test(mixer, slot, str, ptr->index,
				       SNDRV_MIXER_OSS_ITEM_CROUTE);
	अगर (err)
		वापस err;
	प्र_लिखो(str, "%s Capture Volume", ptr->name);
	err = snd_mixer_oss_build_test(mixer, slot, str, ptr->index,
				       SNDRV_MIXER_OSS_ITEM_CVOLUME);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

/*
 * build an OSS mixer element.
 * ptr_allocated means the entry is dynamically allocated (change via proc file).
 * when replace_old = 1, the old entry is replaced with the new one.
 */
अटल पूर्णांक snd_mixer_oss_build_input(काष्ठा snd_mixer_oss *mixer,
				     स्थिर काष्ठा snd_mixer_oss_assign_table *ptr,
				     पूर्णांक ptr_allocated, पूर्णांक replace_old)
अणु
	काष्ठा slot slot;
	काष्ठा slot *pslot;
	काष्ठा snd_kcontrol *kctl;
	काष्ठा snd_mixer_oss_slot *rslot;
	अक्षर str[64];	
	
	/* check अगर alपढ़ोy asचिन्हित */
	अगर (mixer->slots[ptr->oss_id].get_volume && ! replace_old)
		वापस 0;

	स_रखो(&slot, 0, माप(slot));
	स_रखो(slot.numid, 0xff, माप(slot.numid)); /* ID_UNKNOWN */
	अगर (snd_mixer_oss_build_test_all(mixer, ptr, &slot))
		वापस 0;
	करोwn_पढ़ो(&mixer->card->controls_rwsem);
	अगर (ptr->index == 0 && (kctl = snd_mixer_oss_test_id(mixer, "Capture Source", 0)) != शून्य) अणु
		काष्ठा snd_ctl_elem_info *uinfo;

		uinfo = kzalloc(माप(*uinfo), GFP_KERNEL);
		अगर (! uinfo) अणु
			up_पढ़ो(&mixer->card->controls_rwsem);
			वापस -ENOMEM;
		पूर्ण
			
		अगर (kctl->info(kctl, uinfo)) अणु
			up_पढ़ो(&mixer->card->controls_rwsem);
			kमुक्त(uinfo);
			वापस 0;
		पूर्ण
		म_नकल(str, ptr->name);
		अगर (!म_भेद(str, "Master"))
			म_नकल(str, "Mix");
		अगर (!म_भेद(str, "Master Mono"))
			म_नकल(str, "Mix Mono");
		slot.capture_item = 0;
		अगर (!म_भेद(uinfo->value.क्रमागतerated.name, str)) अणु
			slot.present |= SNDRV_MIXER_OSS_PRESENT_CAPTURE;
		पूर्ण अन्यथा अणु
			क्रम (slot.capture_item = 1; slot.capture_item < uinfo->value.क्रमागतerated.items; slot.capture_item++) अणु
				uinfo->value.क्रमागतerated.item = slot.capture_item;
				अगर (kctl->info(kctl, uinfo)) अणु
					up_पढ़ो(&mixer->card->controls_rwsem);
					kमुक्त(uinfo);
					वापस 0;
				पूर्ण
				अगर (!म_भेद(uinfo->value.क्रमागतerated.name, str)) अणु
					slot.present |= SNDRV_MIXER_OSS_PRESENT_CAPTURE;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
		kमुक्त(uinfo);
	पूर्ण
	up_पढ़ो(&mixer->card->controls_rwsem);
	अगर (slot.present != 0) अणु
		pslot = kदो_स्मृति(माप(slot), GFP_KERNEL);
		अगर (! pslot)
			वापस -ENOMEM;
		*pslot = slot;
		pslot->signature = SNDRV_MIXER_OSS_SIGNATURE;
		pslot->asचिन्हित = ptr;
		pslot->allocated = ptr_allocated;
		rslot = &mixer->slots[ptr->oss_id];
		mixer_slot_clear(rslot);
		rslot->stereo = slot.channels > 1 ? 1 : 0;
		rslot->get_volume = snd_mixer_oss_get_volume1;
		rslot->put_volume = snd_mixer_oss_put_volume1;
		/* note: ES18xx have both Capture Source and XX Capture Volume !!! */
		अगर (slot.present & SNDRV_MIXER_OSS_PRESENT_CSWITCH) अणु
			rslot->get_recsrc = snd_mixer_oss_get_recsrc1_sw;
			rslot->put_recsrc = snd_mixer_oss_put_recsrc1_sw;
		पूर्ण अन्यथा अगर (slot.present & SNDRV_MIXER_OSS_PRESENT_CROUTE) अणु
			rslot->get_recsrc = snd_mixer_oss_get_recsrc1_route;
			rslot->put_recsrc = snd_mixer_oss_put_recsrc1_route;
		पूर्ण अन्यथा अगर (slot.present & SNDRV_MIXER_OSS_PRESENT_CAPTURE) अणु
			mixer->mask_recsrc |= 1 << ptr->oss_id;
		पूर्ण
		rslot->निजी_data = pslot;
		rslot->निजी_मुक्त = snd_mixer_oss_slot_मुक्त;
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_SND_PROC_FS
/*
 */
#घोषणा MIXER_VOL(name) [SOUND_MIXER_##name] = #name
अटल स्थिर अक्षर * स्थिर oss_mixer_names[SNDRV_OSS_MAX_MIXERS] = अणु
	MIXER_VOL(VOLUME),
	MIXER_VOL(BASS),
	MIXER_VOL(TREBLE),
	MIXER_VOL(SYNTH),
	MIXER_VOL(PCM),
	MIXER_VOL(SPEAKER),
	MIXER_VOL(LINE),
	MIXER_VOL(MIC),
	MIXER_VOL(CD),
	MIXER_VOL(IMIX),
	MIXER_VOL(ALTPCM),
	MIXER_VOL(RECLEV),
	MIXER_VOL(IGAIN),
	MIXER_VOL(OGAIN),
	MIXER_VOL(LINE1),
	MIXER_VOL(LINE2),
	MIXER_VOL(LINE3),
	MIXER_VOL(DIGITAL1),
	MIXER_VOL(DIGITAL2),
	MIXER_VOL(DIGITAL3),
	MIXER_VOL(PHONEIN),
	MIXER_VOL(PHONEOUT),
	MIXER_VOL(VIDEO),
	MIXER_VOL(RADIO),
	MIXER_VOL(MONITOR),
पूर्ण;
	
/*
 *  /proc पूर्णांकerface
 */

अटल व्योम snd_mixer_oss_proc_पढ़ो(काष्ठा snd_info_entry *entry,
				    काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा snd_mixer_oss *mixer = entry->निजी_data;
	पूर्णांक i;

	mutex_lock(&mixer->reg_mutex);
	क्रम (i = 0; i < SNDRV_OSS_MAX_MIXERS; i++) अणु
		काष्ठा slot *p;

		अगर (! oss_mixer_names[i])
			जारी;
		p = (काष्ठा slot *)mixer->slots[i].निजी_data;
		snd_iम_लिखो(buffer, "%s ", oss_mixer_names[i]);
		अगर (p && p->asचिन्हित)
			snd_iम_लिखो(buffer, "\"%s\" %d\n",
				    p->asचिन्हित->name,
				    p->asचिन्हित->index);
		अन्यथा
			snd_iम_लिखो(buffer, "\"\" 0\n");
	पूर्ण
	mutex_unlock(&mixer->reg_mutex);
पूर्ण

अटल व्योम snd_mixer_oss_proc_ग_लिखो(काष्ठा snd_info_entry *entry,
				     काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा snd_mixer_oss *mixer = entry->निजी_data;
	अक्षर line[128], str[32], idxstr[16];
	स्थिर अक्षर *cptr;
	अचिन्हित पूर्णांक idx;
	पूर्णांक ch;
	काष्ठा snd_mixer_oss_assign_table *tbl;
	काष्ठा slot *slot;

	जबतक (!snd_info_get_line(buffer, line, माप(line))) अणु
		cptr = snd_info_get_str(str, line, माप(str));
		क्रम (ch = 0; ch < SNDRV_OSS_MAX_MIXERS; ch++)
			अगर (oss_mixer_names[ch] && म_भेद(oss_mixer_names[ch], str) == 0)
				अवरोध;
		अगर (ch >= SNDRV_OSS_MAX_MIXERS) अणु
			pr_err("ALSA: mixer_oss: invalid OSS volume '%s'\n",
			       str);
			जारी;
		पूर्ण
		cptr = snd_info_get_str(str, cptr, माप(str));
		अगर (! *str) अणु
			/* हटाओ the entry */
			mutex_lock(&mixer->reg_mutex);
			mixer_slot_clear(&mixer->slots[ch]);
			mutex_unlock(&mixer->reg_mutex);
			जारी;
		पूर्ण
		snd_info_get_str(idxstr, cptr, माप(idxstr));
		idx = simple_म_से_अदीर्घ(idxstr, शून्य, 10);
		अगर (idx >= 0x4000) अणु /* too big */
			pr_err("ALSA: mixer_oss: invalid index %d\n", idx);
			जारी;
		पूर्ण
		mutex_lock(&mixer->reg_mutex);
		slot = (काष्ठा slot *)mixer->slots[ch].निजी_data;
		अगर (slot && slot->asचिन्हित &&
		    slot->asचिन्हित->index == idx && ! म_भेद(slot->asचिन्हित->name, str))
			/* not changed */
			जाओ __unlock;
		tbl = kदो_स्मृति(माप(*tbl), GFP_KERNEL);
		अगर (!tbl)
			जाओ __unlock;
		tbl->oss_id = ch;
		tbl->name = kstrdup(str, GFP_KERNEL);
		अगर (! tbl->name) अणु
			kमुक्त(tbl);
			जाओ __unlock;
		पूर्ण
		tbl->index = idx;
		अगर (snd_mixer_oss_build_input(mixer, tbl, 1, 1) <= 0) अणु
			kमुक्त(tbl->name);
			kमुक्त(tbl);
		पूर्ण
	__unlock:
		mutex_unlock(&mixer->reg_mutex);
	पूर्ण
पूर्ण

अटल व्योम snd_mixer_oss_proc_init(काष्ठा snd_mixer_oss *mixer)
अणु
	काष्ठा snd_info_entry *entry;

	entry = snd_info_create_card_entry(mixer->card, "oss_mixer",
					   mixer->card->proc_root);
	अगर (! entry)
		वापस;
	entry->content = SNDRV_INFO_CONTENT_TEXT;
	entry->mode = S_IFREG | 0644;
	entry->c.text.पढ़ो = snd_mixer_oss_proc_पढ़ो;
	entry->c.text.ग_लिखो = snd_mixer_oss_proc_ग_लिखो;
	entry->निजी_data = mixer;
	अगर (snd_info_रेजिस्टर(entry) < 0) अणु
		snd_info_मुक्त_entry(entry);
		entry = शून्य;
	पूर्ण
	mixer->proc_entry = entry;
पूर्ण

अटल व्योम snd_mixer_oss_proc_करोne(काष्ठा snd_mixer_oss *mixer)
अणु
	snd_info_मुक्त_entry(mixer->proc_entry);
	mixer->proc_entry = शून्य;
पूर्ण
#अन्यथा /* !CONFIG_SND_PROC_FS */
#घोषणा snd_mixer_oss_proc_init(mix)
#घोषणा snd_mixer_oss_proc_करोne(mix)
#पूर्ण_अगर /* CONFIG_SND_PROC_FS */

अटल व्योम snd_mixer_oss_build(काष्ठा snd_mixer_oss *mixer)
अणु
	अटल स्थिर काष्ठा snd_mixer_oss_assign_table table[] = अणु
		अणु SOUND_MIXER_VOLUME, 	"Master",		0 पूर्ण,
		अणु SOUND_MIXER_VOLUME, 	"Front",		0 पूर्ण, /* fallback */
		अणु SOUND_MIXER_BASS,	"Tone Control - Bass",	0 पूर्ण,
		अणु SOUND_MIXER_TREBLE,	"Tone Control - Treble", 0 पूर्ण,
		अणु SOUND_MIXER_SYNTH,	"Synth",		0 पूर्ण,
		अणु SOUND_MIXER_SYNTH,	"FM",			0 पूर्ण, /* fallback */
		अणु SOUND_MIXER_SYNTH,	"Music",		0 पूर्ण, /* fallback */
		अणु SOUND_MIXER_PCM,	"PCM",			0 पूर्ण,
		अणु SOUND_MIXER_SPEAKER,	"Beep", 		0 पूर्ण,
		अणु SOUND_MIXER_SPEAKER,	"PC Speaker", 		0 पूर्ण, /* fallback */
		अणु SOUND_MIXER_SPEAKER,	"Speaker", 		0 पूर्ण, /* fallback */
		अणु SOUND_MIXER_LINE,	"Line", 		0 पूर्ण,
		अणु SOUND_MIXER_MIC,	"Mic", 			0 पूर्ण,
		अणु SOUND_MIXER_CD,	"CD", 			0 पूर्ण,
		अणु SOUND_MIXER_IMIX,	"Monitor Mix", 		0 पूर्ण,
		अणु SOUND_MIXER_ALTPCM,	"PCM",			1 पूर्ण,
		अणु SOUND_MIXER_ALTPCM,	"Headphone",		0 पूर्ण, /* fallback */
		अणु SOUND_MIXER_ALTPCM,	"Wave",			0 पूर्ण, /* fallback */
		अणु SOUND_MIXER_RECLEV,	"-- nothing --",	0 पूर्ण,
		अणु SOUND_MIXER_IGAIN,	"Capture",		0 पूर्ण,
		अणु SOUND_MIXER_OGAIN,	"Playback",		0 पूर्ण,
		अणु SOUND_MIXER_LINE1,	"Aux",			0 पूर्ण,
		अणु SOUND_MIXER_LINE2,	"Aux",			1 पूर्ण,
		अणु SOUND_MIXER_LINE3,	"Aux",			2 पूर्ण,
		अणु SOUND_MIXER_DIGITAL1,	"Digital",		0 पूर्ण,
		अणु SOUND_MIXER_DIGITAL1,	"IEC958",		0 पूर्ण, /* fallback */
		अणु SOUND_MIXER_DIGITAL1,	"IEC958 Optical",	0 पूर्ण, /* fallback */
		अणु SOUND_MIXER_DIGITAL1,	"IEC958 Coaxial",	0 पूर्ण, /* fallback */
		अणु SOUND_MIXER_DIGITAL2,	"Digital",		1 पूर्ण,
		अणु SOUND_MIXER_DIGITAL3,	"Digital",		2 पूर्ण,
		अणु SOUND_MIXER_PHONEIN,	"Phone",		0 पूर्ण,
		अणु SOUND_MIXER_PHONEOUT,	"Master Mono",		0 पूर्ण,
		अणु SOUND_MIXER_PHONEOUT,	"Speaker",		0 पूर्ण, /*fallback*/
		अणु SOUND_MIXER_PHONEOUT,	"Mono",			0 पूर्ण, /*fallback*/
		अणु SOUND_MIXER_PHONEOUT,	"Phone",		0 पूर्ण, /* fallback */
		अणु SOUND_MIXER_VIDEO,	"Video",		0 पूर्ण,
		अणु SOUND_MIXER_RADIO,	"Radio",		0 पूर्ण,
		अणु SOUND_MIXER_MONITOR,	"Monitor",		0 पूर्ण
	पूर्ण;
	अचिन्हित पूर्णांक idx;
	
	क्रम (idx = 0; idx < ARRAY_SIZE(table); idx++)
		snd_mixer_oss_build_input(mixer, &table[idx], 0, 0);
	अगर (mixer->mask_recsrc) अणु
		mixer->get_recsrc = snd_mixer_oss_get_recsrc2;
		mixer->put_recsrc = snd_mixer_oss_put_recsrc2;
	पूर्ण
पूर्ण

/*
 *
 */

अटल पूर्णांक snd_mixer_oss_मुक्त1(व्योम *निजी)
अणु
	काष्ठा snd_mixer_oss *mixer = निजी;
	काष्ठा snd_card *card;
	पूर्णांक idx;
 
	अगर (!mixer)
		वापस 0;
	card = mixer->card;
	अगर (snd_BUG_ON(mixer != card->mixer_oss))
		वापस -ENXIO;
	card->mixer_oss = शून्य;
	क्रम (idx = 0; idx < SNDRV_OSS_MAX_MIXERS; idx++) अणु
		काष्ठा snd_mixer_oss_slot *chn = &mixer->slots[idx];
		अगर (chn->निजी_मुक्त)
			chn->निजी_मुक्त(chn);
	पूर्ण
	kमुक्त(mixer);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_mixer_oss_notअगरy_handler(काष्ठा snd_card *card, पूर्णांक cmd)
अणु
	काष्ठा snd_mixer_oss *mixer;

	अगर (cmd == SND_MIXER_OSS_NOTIFY_REGISTER) अणु
		पूर्णांक idx, err;

		mixer = kसुस्मृति(2, माप(*mixer), GFP_KERNEL);
		अगर (mixer == शून्य)
			वापस -ENOMEM;
		mutex_init(&mixer->reg_mutex);
		अगर ((err = snd_रेजिस्टर_oss_device(SNDRV_OSS_DEVICE_TYPE_MIXER,
						   card, 0,
						   &snd_mixer_oss_f_ops, card)) < 0) अणु
			dev_err(card->dev,
				"unable to register OSS mixer device %i:%i\n",
				card->number, 0);
			kमुक्त(mixer);
			वापस err;
		पूर्ण
		mixer->oss_dev_alloc = 1;
		mixer->card = card;
		अगर (*card->mixername)
			strscpy(mixer->name, card->mixername, माप(mixer->name));
		अन्यथा
			snम_लिखो(mixer->name, माप(mixer->name),
				 "mixer%i", card->number);
#अगर_घोषित SNDRV_OSS_INFO_DEV_MIXERS
		snd_oss_info_रेजिस्टर(SNDRV_OSS_INFO_DEV_MIXERS,
				      card->number,
				      mixer->name);
#पूर्ण_अगर
		क्रम (idx = 0; idx < SNDRV_OSS_MAX_MIXERS; idx++)
			mixer->slots[idx].number = idx;
		card->mixer_oss = mixer;
		snd_mixer_oss_build(mixer);
		snd_mixer_oss_proc_init(mixer);
	पूर्ण अन्यथा अणु
		mixer = card->mixer_oss;
		अगर (mixer == शून्य)
			वापस 0;
		अगर (mixer->oss_dev_alloc) अणु
#अगर_घोषित SNDRV_OSS_INFO_DEV_MIXERS
			snd_oss_info_unरेजिस्टर(SNDRV_OSS_INFO_DEV_MIXERS, mixer->card->number);
#पूर्ण_अगर
			snd_unरेजिस्टर_oss_device(SNDRV_OSS_DEVICE_TYPE_MIXER, mixer->card, 0);
			mixer->oss_dev_alloc = 0;
		पूर्ण
		अगर (cmd == SND_MIXER_OSS_NOTIFY_DISCONNECT)
			वापस 0;
		snd_mixer_oss_proc_करोne(mixer);
		वापस snd_mixer_oss_मुक्त1(mixer);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __init alsa_mixer_oss_init(व्योम)
अणु
	काष्ठा snd_card *card;
	पूर्णांक idx;
	
	snd_mixer_oss_notअगरy_callback = snd_mixer_oss_notअगरy_handler;
	क्रम (idx = 0; idx < SNDRV_CARDS; idx++) अणु
		card = snd_card_ref(idx);
		अगर (card) अणु
			snd_mixer_oss_notअगरy_handler(card, SND_MIXER_OSS_NOTIFY_REGISTER);
			snd_card_unref(card);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम __निकास alsa_mixer_oss_निकास(व्योम)
अणु
	काष्ठा snd_card *card;
	पूर्णांक idx;

	snd_mixer_oss_notअगरy_callback = शून्य;
	क्रम (idx = 0; idx < SNDRV_CARDS; idx++) अणु
		card = snd_card_ref(idx);
		अगर (card) अणु
			snd_mixer_oss_notअगरy_handler(card, SND_MIXER_OSS_NOTIFY_FREE);
			snd_card_unref(card);
		पूर्ण
	पूर्ण
पूर्ण

module_init(alsa_mixer_oss_init)
module_निकास(alsa_mixer_oss_निकास)
