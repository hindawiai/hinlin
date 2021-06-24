<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * compat ioctls क्रम control API
 *
 *   Copyright (c) by Takashi Iwai <tiwai@suse.de>
 */

/* this file included from control.c */

#समावेश <linux/compat.h>
#समावेश <linux/slab.h>

काष्ठा snd_ctl_elem_list32 अणु
	u32 offset;
	u32 space;
	u32 used;
	u32 count;
	u32 pids;
	अचिन्हित अक्षर reserved[50];
पूर्ण /* करोn't set packed attribute here */;

अटल पूर्णांक snd_ctl_elem_list_compat(काष्ठा snd_card *card,
				    काष्ठा snd_ctl_elem_list32 __user *data32)
अणु
	काष्ठा snd_ctl_elem_list data = अणुपूर्ण;
	compat_caddr_t ptr;
	पूर्णांक err;

	/* offset, space, used, count */
	अगर (copy_from_user(&data, data32, 4 * माप(u32)))
		वापस -EFAULT;
	/* pids */
	अगर (get_user(ptr, &data32->pids))
		वापस -EFAULT;
	data.pids = compat_ptr(ptr);
	err = snd_ctl_elem_list(card, &data);
	अगर (err < 0)
		वापस err;
	/* copy the result */
	अगर (copy_to_user(data32, &data, 4 * माप(u32)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

/*
 * control element info
 * it uses जोड़, so the things are not easy..
 */

काष्ठा snd_ctl_elem_info32 अणु
	काष्ठा snd_ctl_elem_id id; // the size of काष्ठा is same
	s32 type;
	u32 access;
	u32 count;
	s32 owner;
	जोड़ अणु
		काष्ठा अणु
			s32 min;
			s32 max;
			s32 step;
		पूर्ण पूर्णांकeger;
		काष्ठा अणु
			u64 min;
			u64 max;
			u64 step;
		पूर्ण पूर्णांकeger64;
		काष्ठा अणु
			u32 items;
			u32 item;
			अक्षर name[64];
			u64 names_ptr;
			u32 names_length;
		पूर्ण क्रमागतerated;
		अचिन्हित अक्षर reserved[128];
	पूर्ण value;
	अचिन्हित अक्षर reserved[64];
पूर्ण __attribute__((packed));

अटल पूर्णांक snd_ctl_elem_info_compat(काष्ठा snd_ctl_file *ctl,
				    काष्ठा snd_ctl_elem_info32 __user *data32)
अणु
	काष्ठा snd_ctl_elem_info *data;
	पूर्णांक err;

	data = kzalloc(माप(*data), GFP_KERNEL);
	अगर (! data)
		वापस -ENOMEM;

	err = -EFAULT;
	/* copy id */
	अगर (copy_from_user(&data->id, &data32->id, माप(data->id)))
		जाओ error;
	/* we need to copy the item index.
	 * hope this करोesn't अवरोध anything..
	 */
	अगर (get_user(data->value.क्रमागतerated.item, &data32->value.क्रमागतerated.item))
		जाओ error;

	err = snd_घातer_रुको(ctl->card, SNDRV_CTL_POWER_D0);
	अगर (err < 0)
		जाओ error;
	err = snd_ctl_elem_info(ctl, data);
	अगर (err < 0)
		जाओ error;
	/* restore info to 32bit */
	err = -EFAULT;
	/* id, type, access, count */
	अगर (copy_to_user(&data32->id, &data->id, माप(data->id)) ||
	    copy_to_user(&data32->type, &data->type, 3 * माप(u32)))
		जाओ error;
	अगर (put_user(data->owner, &data32->owner))
		जाओ error;
	चयन (data->type) अणु
	हाल SNDRV_CTL_ELEM_TYPE_BOOLEAN:
	हाल SNDRV_CTL_ELEM_TYPE_INTEGER:
		अगर (put_user(data->value.पूर्णांकeger.min, &data32->value.पूर्णांकeger.min) ||
		    put_user(data->value.पूर्णांकeger.max, &data32->value.पूर्णांकeger.max) ||
		    put_user(data->value.पूर्णांकeger.step, &data32->value.पूर्णांकeger.step))
			जाओ error;
		अवरोध;
	हाल SNDRV_CTL_ELEM_TYPE_INTEGER64:
		अगर (copy_to_user(&data32->value.पूर्णांकeger64,
				 &data->value.पूर्णांकeger64,
				 माप(data->value.पूर्णांकeger64)))
			जाओ error;
		अवरोध;
	हाल SNDRV_CTL_ELEM_TYPE_ENUMERATED:
		अगर (copy_to_user(&data32->value.क्रमागतerated,
				 &data->value.क्रमागतerated,
				 माप(data->value.क्रमागतerated)))
			जाओ error;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	err = 0;
 error:
	kमुक्त(data);
	वापस err;
पूर्ण

/* पढ़ो / ग_लिखो */
काष्ठा snd_ctl_elem_value32 अणु
	काष्ठा snd_ctl_elem_id id;
	अचिन्हित पूर्णांक indirect;	/* bit-field causes misalignment */
        जोड़ अणु
		s32 पूर्णांकeger[128];
		अचिन्हित अक्षर data[512];
#अगर_अघोषित CONFIG_X86_64
		s64 पूर्णांकeger64[64];
#पूर्ण_अगर
        पूर्ण value;
        अचिन्हित अक्षर reserved[128];
पूर्ण;

#अगर_घोषित CONFIG_X86_X32
/* x32 has a dअगरferent alignment क्रम 64bit values from ia32 */
काष्ठा snd_ctl_elem_value_x32 अणु
	काष्ठा snd_ctl_elem_id id;
	अचिन्हित पूर्णांक indirect;	/* bit-field causes misalignment */
	जोड़ अणु
		s32 पूर्णांकeger[128];
		अचिन्हित अक्षर data[512];
		s64 पूर्णांकeger64[64];
	पूर्ण value;
	अचिन्हित अक्षर reserved[128];
पूर्ण;
#पूर्ण_अगर /* CONFIG_X86_X32 */

/* get the value type and count of the control */
अटल पूर्णांक get_ctl_type(काष्ठा snd_card *card, काष्ठा snd_ctl_elem_id *id,
			पूर्णांक *countp)
अणु
	काष्ठा snd_kcontrol *kctl;
	काष्ठा snd_ctl_elem_info *info;
	पूर्णांक err;

	करोwn_पढ़ो(&card->controls_rwsem);
	kctl = snd_ctl_find_id(card, id);
	अगर (! kctl) अणु
		up_पढ़ो(&card->controls_rwsem);
		वापस -ENOENT;
	पूर्ण
	info = kzalloc(माप(*info), GFP_KERNEL);
	अगर (info == शून्य) अणु
		up_पढ़ो(&card->controls_rwsem);
		वापस -ENOMEM;
	पूर्ण
	info->id = *id;
	err = kctl->info(kctl, info);
	up_पढ़ो(&card->controls_rwsem);
	अगर (err >= 0) अणु
		err = info->type;
		*countp = info->count;
	पूर्ण
	kमुक्त(info);
	वापस err;
पूर्ण

अटल पूर्णांक get_elem_size(पूर्णांक type, पूर्णांक count)
अणु
	चयन (type) अणु
	हाल SNDRV_CTL_ELEM_TYPE_INTEGER64:
		वापस माप(s64) * count;
	हाल SNDRV_CTL_ELEM_TYPE_ENUMERATED:
		वापस माप(पूर्णांक) * count;
	हाल SNDRV_CTL_ELEM_TYPE_BYTES:
		वापस 512;
	हाल SNDRV_CTL_ELEM_TYPE_IEC958:
		वापस माप(काष्ठा snd_aes_iec958);
	शेष:
		वापस -1;
	पूर्ण
पूर्ण

अटल पूर्णांक copy_ctl_value_from_user(काष्ठा snd_card *card,
				    काष्ठा snd_ctl_elem_value *data,
				    व्योम __user *userdata,
				    व्योम __user *valuep,
				    पूर्णांक *typep, पूर्णांक *countp)
अणु
	काष्ठा snd_ctl_elem_value32 __user *data32 = userdata;
	पूर्णांक i, type, size;
	पूर्णांक count;
	अचिन्हित पूर्णांक indirect;

	अगर (copy_from_user(&data->id, &data32->id, माप(data->id)))
		वापस -EFAULT;
	अगर (get_user(indirect, &data32->indirect))
		वापस -EFAULT;
	अगर (indirect)
		वापस -EINVAL;
	type = get_ctl_type(card, &data->id, &count);
	अगर (type < 0)
		वापस type;

	अगर (type == SNDRV_CTL_ELEM_TYPE_BOOLEAN ||
	    type == SNDRV_CTL_ELEM_TYPE_INTEGER) अणु
		क्रम (i = 0; i < count; i++) अणु
			s32 __user *पूर्णांकp = valuep;
			पूर्णांक val;
			अगर (get_user(val, &पूर्णांकp[i]))
				वापस -EFAULT;
			data->value.पूर्णांकeger.value[i] = val;
		पूर्ण
	पूर्ण अन्यथा अणु
		size = get_elem_size(type, count);
		अगर (size < 0) अणु
			dev_err(card->dev, "snd_ioctl32_ctl_elem_value: unknown type %d\n", type);
			वापस -EINVAL;
		पूर्ण
		अगर (copy_from_user(data->value.bytes.data, valuep, size))
			वापस -EFAULT;
	पूर्ण

	*typep = type;
	*countp = count;
	वापस 0;
पूर्ण

/* restore the value to 32bit */
अटल पूर्णांक copy_ctl_value_to_user(व्योम __user *userdata,
				  व्योम __user *valuep,
				  काष्ठा snd_ctl_elem_value *data,
				  पूर्णांक type, पूर्णांक count)
अणु
	पूर्णांक i, size;

	अगर (type == SNDRV_CTL_ELEM_TYPE_BOOLEAN ||
	    type == SNDRV_CTL_ELEM_TYPE_INTEGER) अणु
		क्रम (i = 0; i < count; i++) अणु
			s32 __user *पूर्णांकp = valuep;
			पूर्णांक val;
			val = data->value.पूर्णांकeger.value[i];
			अगर (put_user(val, &पूर्णांकp[i]))
				वापस -EFAULT;
		पूर्ण
	पूर्ण अन्यथा अणु
		size = get_elem_size(type, count);
		अगर (copy_to_user(valuep, data->value.bytes.data, size))
			वापस -EFAULT;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ctl_elem_पढ़ो_user(काष्ठा snd_card *card,
			      व्योम __user *userdata, व्योम __user *valuep)
अणु
	काष्ठा snd_ctl_elem_value *data;
	पूर्णांक err, type, count;

	data = kzalloc(माप(*data), GFP_KERNEL);
	अगर (data == शून्य)
		वापस -ENOMEM;

	err = copy_ctl_value_from_user(card, data, userdata, valuep,
				       &type, &count);
	अगर (err < 0)
		जाओ error;

	err = snd_घातer_रुको(card, SNDRV_CTL_POWER_D0);
	अगर (err < 0)
		जाओ error;
	err = snd_ctl_elem_पढ़ो(card, data);
	अगर (err < 0)
		जाओ error;
	err = copy_ctl_value_to_user(userdata, valuep, data, type, count);
 error:
	kमुक्त(data);
	वापस err;
पूर्ण

अटल पूर्णांक ctl_elem_ग_लिखो_user(काष्ठा snd_ctl_file *file,
			       व्योम __user *userdata, व्योम __user *valuep)
अणु
	काष्ठा snd_ctl_elem_value *data;
	काष्ठा snd_card *card = file->card;
	पूर्णांक err, type, count;

	data = kzalloc(माप(*data), GFP_KERNEL);
	अगर (data == शून्य)
		वापस -ENOMEM;

	err = copy_ctl_value_from_user(card, data, userdata, valuep,
				       &type, &count);
	अगर (err < 0)
		जाओ error;

	err = snd_घातer_रुको(card, SNDRV_CTL_POWER_D0);
	अगर (err < 0)
		जाओ error;
	err = snd_ctl_elem_ग_लिखो(card, file, data);
	अगर (err < 0)
		जाओ error;
	err = copy_ctl_value_to_user(userdata, valuep, data, type, count);
 error:
	kमुक्त(data);
	वापस err;
पूर्ण

अटल पूर्णांक snd_ctl_elem_पढ़ो_user_compat(काष्ठा snd_card *card,
					 काष्ठा snd_ctl_elem_value32 __user *data32)
अणु
	वापस ctl_elem_पढ़ो_user(card, data32, &data32->value);
पूर्ण

अटल पूर्णांक snd_ctl_elem_ग_लिखो_user_compat(काष्ठा snd_ctl_file *file,
					  काष्ठा snd_ctl_elem_value32 __user *data32)
अणु
	वापस ctl_elem_ग_लिखो_user(file, data32, &data32->value);
पूर्ण

#अगर_घोषित CONFIG_X86_X32
अटल पूर्णांक snd_ctl_elem_पढ़ो_user_x32(काष्ठा snd_card *card,
				      काष्ठा snd_ctl_elem_value_x32 __user *data32)
अणु
	वापस ctl_elem_पढ़ो_user(card, data32, &data32->value);
पूर्ण

अटल पूर्णांक snd_ctl_elem_ग_लिखो_user_x32(काष्ठा snd_ctl_file *file,
				       काष्ठा snd_ctl_elem_value_x32 __user *data32)
अणु
	वापस ctl_elem_ग_लिखो_user(file, data32, &data32->value);
पूर्ण
#पूर्ण_अगर /* CONFIG_X86_X32 */

/* add or replace a user control */
अटल पूर्णांक snd_ctl_elem_add_compat(काष्ठा snd_ctl_file *file,
				   काष्ठा snd_ctl_elem_info32 __user *data32,
				   पूर्णांक replace)
अणु
	काष्ठा snd_ctl_elem_info *data;
	पूर्णांक err;

	data = kzalloc(माप(*data), GFP_KERNEL);
	अगर (! data)
		वापस -ENOMEM;

	err = -EFAULT;
	/* id, type, access, count */ \
	अगर (copy_from_user(&data->id, &data32->id, माप(data->id)) ||
	    copy_from_user(&data->type, &data32->type, 3 * माप(u32)))
		जाओ error;
	अगर (get_user(data->owner, &data32->owner))
		जाओ error;
	चयन (data->type) अणु
	हाल SNDRV_CTL_ELEM_TYPE_BOOLEAN:
	हाल SNDRV_CTL_ELEM_TYPE_INTEGER:
		अगर (get_user(data->value.पूर्णांकeger.min, &data32->value.पूर्णांकeger.min) ||
		    get_user(data->value.पूर्णांकeger.max, &data32->value.पूर्णांकeger.max) ||
		    get_user(data->value.पूर्णांकeger.step, &data32->value.पूर्णांकeger.step))
			जाओ error;
		अवरोध;
	हाल SNDRV_CTL_ELEM_TYPE_INTEGER64:
		अगर (copy_from_user(&data->value.पूर्णांकeger64,
				   &data32->value.पूर्णांकeger64,
				   माप(data->value.पूर्णांकeger64)))
			जाओ error;
		अवरोध;
	हाल SNDRV_CTL_ELEM_TYPE_ENUMERATED:
		अगर (copy_from_user(&data->value.क्रमागतerated,
				   &data32->value.क्रमागतerated,
				   माप(data->value.क्रमागतerated)))
			जाओ error;
		data->value.क्रमागतerated.names_ptr =
			(uपूर्णांकptr_t)compat_ptr(data->value.क्रमागतerated.names_ptr);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	err = snd_ctl_elem_add(file, data, replace);
 error:
	kमुक्त(data);
	वापस err;
पूर्ण  

क्रमागत अणु
	SNDRV_CTL_IOCTL_ELEM_LIST32 = _IOWR('U', 0x10, काष्ठा snd_ctl_elem_list32),
	SNDRV_CTL_IOCTL_ELEM_INFO32 = _IOWR('U', 0x11, काष्ठा snd_ctl_elem_info32),
	SNDRV_CTL_IOCTL_ELEM_READ32 = _IOWR('U', 0x12, काष्ठा snd_ctl_elem_value32),
	SNDRV_CTL_IOCTL_ELEM_WRITE32 = _IOWR('U', 0x13, काष्ठा snd_ctl_elem_value32),
	SNDRV_CTL_IOCTL_ELEM_ADD32 = _IOWR('U', 0x17, काष्ठा snd_ctl_elem_info32),
	SNDRV_CTL_IOCTL_ELEM_REPLACE32 = _IOWR('U', 0x18, काष्ठा snd_ctl_elem_info32),
#अगर_घोषित CONFIG_X86_X32
	SNDRV_CTL_IOCTL_ELEM_READ_X32 = _IOWR('U', 0x12, काष्ठा snd_ctl_elem_value_x32),
	SNDRV_CTL_IOCTL_ELEM_WRITE_X32 = _IOWR('U', 0x13, काष्ठा snd_ctl_elem_value_x32),
#पूर्ण_अगर /* CONFIG_X86_X32 */
पूर्ण;

अटल अंतरभूत दीर्घ snd_ctl_ioctl_compat(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा snd_ctl_file *ctl;
	काष्ठा snd_kctl_ioctl *p;
	व्योम __user *argp = compat_ptr(arg);
	पूर्णांक err;

	ctl = file->निजी_data;
	अगर (snd_BUG_ON(!ctl || !ctl->card))
		वापस -ENXIO;

	चयन (cmd) अणु
	हाल SNDRV_CTL_IOCTL_PVERSION:
	हाल SNDRV_CTL_IOCTL_CARD_INFO:
	हाल SNDRV_CTL_IOCTL_SUBSCRIBE_EVENTS:
	हाल SNDRV_CTL_IOCTL_POWER:
	हाल SNDRV_CTL_IOCTL_POWER_STATE:
	हाल SNDRV_CTL_IOCTL_ELEM_LOCK:
	हाल SNDRV_CTL_IOCTL_ELEM_UNLOCK:
	हाल SNDRV_CTL_IOCTL_ELEM_REMOVE:
	हाल SNDRV_CTL_IOCTL_TLV_READ:
	हाल SNDRV_CTL_IOCTL_TLV_WRITE:
	हाल SNDRV_CTL_IOCTL_TLV_COMMAND:
		वापस snd_ctl_ioctl(file, cmd, (अचिन्हित दीर्घ)argp);
	हाल SNDRV_CTL_IOCTL_ELEM_LIST32:
		वापस snd_ctl_elem_list_compat(ctl->card, argp);
	हाल SNDRV_CTL_IOCTL_ELEM_INFO32:
		वापस snd_ctl_elem_info_compat(ctl, argp);
	हाल SNDRV_CTL_IOCTL_ELEM_READ32:
		वापस snd_ctl_elem_पढ़ो_user_compat(ctl->card, argp);
	हाल SNDRV_CTL_IOCTL_ELEM_WRITE32:
		वापस snd_ctl_elem_ग_लिखो_user_compat(ctl, argp);
	हाल SNDRV_CTL_IOCTL_ELEM_ADD32:
		वापस snd_ctl_elem_add_compat(ctl, argp, 0);
	हाल SNDRV_CTL_IOCTL_ELEM_REPLACE32:
		वापस snd_ctl_elem_add_compat(ctl, argp, 1);
#अगर_घोषित CONFIG_X86_X32
	हाल SNDRV_CTL_IOCTL_ELEM_READ_X32:
		वापस snd_ctl_elem_पढ़ो_user_x32(ctl->card, argp);
	हाल SNDRV_CTL_IOCTL_ELEM_WRITE_X32:
		वापस snd_ctl_elem_ग_लिखो_user_x32(ctl, argp);
#पूर्ण_अगर /* CONFIG_X86_X32 */
	पूर्ण

	करोwn_पढ़ो(&snd_ioctl_rwsem);
	list_क्रम_each_entry(p, &snd_control_compat_ioctls, list) अणु
		अगर (p->fioctl) अणु
			err = p->fioctl(ctl->card, ctl, cmd, arg);
			अगर (err != -ENOIOCTLCMD) अणु
				up_पढ़ो(&snd_ioctl_rwsem);
				वापस err;
			पूर्ण
		पूर्ण
	पूर्ण
	up_पढ़ो(&snd_ioctl_rwsem);
	वापस -ENOIOCTLCMD;
पूर्ण
