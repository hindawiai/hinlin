<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   32bit -> 64bit ioctl wrapper क्रम hwdep API
 *   Copyright (c) by Takashi Iwai <tiwai@suse.de>
 */

/* This file is included from hwdep.c */

#समावेश <linux/compat.h>

काष्ठा snd_hwdep_dsp_image32 अणु
	u32 index;
	अचिन्हित अक्षर name[64];
	u32 image;	/* poपूर्णांकer */
	u32 length;
	u32 driver_data;
पूर्ण /* करोn't set packed attribute here */;

अटल पूर्णांक snd_hwdep_dsp_load_compat(काष्ठा snd_hwdep *hw,
				     काष्ठा snd_hwdep_dsp_image32 __user *src)
अणु
	काष्ठा snd_hwdep_dsp_image info = अणुपूर्ण;
	compat_caddr_t ptr;

	अगर (copy_from_user(&info, src, 4 + 64) ||
	    get_user(ptr, &src->image) ||
	    get_user(info.length, &src->length) ||
	    get_user(info.driver_data, &src->driver_data))
		वापस -EFAULT;
	info.image = compat_ptr(ptr);

	वापस snd_hwdep_dsp_load(hw, &info);
पूर्ण

क्रमागत अणु
	SNDRV_HWDEP_IOCTL_DSP_LOAD32   = _IOW('H', 0x03, काष्ठा snd_hwdep_dsp_image32)
पूर्ण;

अटल दीर्घ snd_hwdep_ioctl_compat(काष्ठा file * file, अचिन्हित पूर्णांक cmd,
				   अचिन्हित दीर्घ arg)
अणु
	काष्ठा snd_hwdep *hw = file->निजी_data;
	व्योम __user *argp = compat_ptr(arg);
	चयन (cmd) अणु
	हाल SNDRV_HWDEP_IOCTL_PVERSION:
	हाल SNDRV_HWDEP_IOCTL_INFO:
	हाल SNDRV_HWDEP_IOCTL_DSP_STATUS:
		वापस snd_hwdep_ioctl(file, cmd, (अचिन्हित दीर्घ)argp);
	हाल SNDRV_HWDEP_IOCTL_DSP_LOAD32:
		वापस snd_hwdep_dsp_load_compat(hw, argp);
	पूर्ण
	अगर (hw->ops.ioctl_compat)
		वापस hw->ops.ioctl_compat(hw, file, cmd, arg);
	वापस -ENOIOCTLCMD;
पूर्ण
