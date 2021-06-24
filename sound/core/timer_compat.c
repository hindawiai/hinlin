<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   32bit -> 64bit ioctl wrapper क्रम समयr API
 *   Copyright (c) by Takashi Iwai <tiwai@suse.de>
 */

/* This file included from समयr.c */

#समावेश <linux/compat.h>

/*
 * ILP32/LP64 has dअगरferent size क्रम 'long' type. Additionally, the size
 * of storage alignment dअगरfers depending on architectures. Here, '__packed'
 * qualअगरier is used so that the size of this काष्ठाure is multiple of 4 and
 * it fits to any architectures with 32 bit storage alignment.
 */
काष्ठा snd_समयr_gparams32 अणु
	काष्ठा snd_समयr_id tid;
	u32 period_num;
	u32 period_den;
	अचिन्हित अक्षर reserved[32];
पूर्ण __packed;

काष्ठा snd_समयr_info32 अणु
	u32 flags;
	s32 card;
	अचिन्हित अक्षर id[64];
	अचिन्हित अक्षर name[80];
	u32 reserved0;
	u32 resolution;
	अचिन्हित अक्षर reserved[64];
पूर्ण;

अटल पूर्णांक snd_समयr_user_gparams_compat(काष्ठा file *file,
					काष्ठा snd_समयr_gparams32 __user *user)
अणु
	काष्ठा snd_समयr_gparams gparams;

	अगर (copy_from_user(&gparams.tid, &user->tid, माप(gparams.tid)) ||
	    get_user(gparams.period_num, &user->period_num) ||
	    get_user(gparams.period_den, &user->period_den))
		वापस -EFAULT;

	वापस समयr_set_gparams(&gparams);
पूर्ण

अटल पूर्णांक snd_समयr_user_info_compat(काष्ठा file *file,
				      काष्ठा snd_समयr_info32 __user *_info)
अणु
	काष्ठा snd_समयr_user *tu;
	काष्ठा snd_समयr_info32 info;
	काष्ठा snd_समयr *t;

	tu = file->निजी_data;
	अगर (!tu->समयri)
		वापस -EBADFD;
	t = tu->समयri->समयr;
	अगर (!t)
		वापस -EBADFD;
	स_रखो(&info, 0, माप(info));
	info.card = t->card ? t->card->number : -1;
	अगर (t->hw.flags & SNDRV_TIMER_HW_SLAVE)
		info.flags |= SNDRV_TIMER_FLG_SLAVE;
	strscpy(info.id, t->id, माप(info.id));
	strscpy(info.name, t->name, माप(info.name));
	info.resolution = t->hw.resolution;
	अगर (copy_to_user(_info, &info, माप(*_info)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

क्रमागत अणु
	SNDRV_TIMER_IOCTL_GPARAMS32 = _IOW('T', 0x04, काष्ठा snd_समयr_gparams32),
	SNDRV_TIMER_IOCTL_INFO32 = _IOR('T', 0x11, काष्ठा snd_समयr_info32),
	SNDRV_TIMER_IOCTL_STATUS_COMPAT32 = _IOW('T', 0x14, काष्ठा snd_समयr_status32),
	SNDRV_TIMER_IOCTL_STATUS_COMPAT64 = _IOW('T', 0x14, काष्ठा snd_समयr_status64),
पूर्ण;

अटल दीर्घ __snd_समयr_user_ioctl_compat(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
					  अचिन्हित दीर्घ arg)
अणु
	व्योम __user *argp = compat_ptr(arg);

	चयन (cmd) अणु
	हाल SNDRV_TIMER_IOCTL_PVERSION:
	हाल SNDRV_TIMER_IOCTL_TREAD_OLD:
	हाल SNDRV_TIMER_IOCTL_TREAD64:
	हाल SNDRV_TIMER_IOCTL_GINFO:
	हाल SNDRV_TIMER_IOCTL_GSTATUS:
	हाल SNDRV_TIMER_IOCTL_SELECT:
	हाल SNDRV_TIMER_IOCTL_PARAMS:
	हाल SNDRV_TIMER_IOCTL_START:
	हाल SNDRV_TIMER_IOCTL_START_OLD:
	हाल SNDRV_TIMER_IOCTL_STOP:
	हाल SNDRV_TIMER_IOCTL_STOP_OLD:
	हाल SNDRV_TIMER_IOCTL_CONTINUE:
	हाल SNDRV_TIMER_IOCTL_CONTINUE_OLD:
	हाल SNDRV_TIMER_IOCTL_PAUSE:
	हाल SNDRV_TIMER_IOCTL_PAUSE_OLD:
	हाल SNDRV_TIMER_IOCTL_NEXT_DEVICE:
		वापस __snd_समयr_user_ioctl(file, cmd, (अचिन्हित दीर्घ)argp, true);
	हाल SNDRV_TIMER_IOCTL_GPARAMS32:
		वापस snd_समयr_user_gparams_compat(file, argp);
	हाल SNDRV_TIMER_IOCTL_INFO32:
		वापस snd_समयr_user_info_compat(file, argp);
	हाल SNDRV_TIMER_IOCTL_STATUS_COMPAT32:
		वापस snd_समयr_user_status32(file, argp);
	हाल SNDRV_TIMER_IOCTL_STATUS_COMPAT64:
		वापस snd_समयr_user_status64(file, argp);
	पूर्ण
	वापस -ENOIOCTLCMD;
पूर्ण

अटल दीर्घ snd_समयr_user_ioctl_compat(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
					अचिन्हित दीर्घ arg)
अणु
	काष्ठा snd_समयr_user *tu = file->निजी_data;
	दीर्घ ret;

	mutex_lock(&tu->ioctl_lock);
	ret = __snd_समयr_user_ioctl_compat(file, cmd, arg);
	mutex_unlock(&tu->ioctl_lock);
	वापस ret;
पूर्ण
