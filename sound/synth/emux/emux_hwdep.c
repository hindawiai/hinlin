<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Interface क्रम hwdep device
 *
 *  Copyright (C) 2004 Takashi Iwai <tiwai@suse.de>
 */

#समावेश <sound/core.h>
#समावेश <sound/hwdep.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/nospec.h>
#समावेश "emux_voice.h"

#घोषणा TMP_CLIENT_ID	0x1001

/*
 * load patch
 */
अटल पूर्णांक
snd_emux_hwdep_load_patch(काष्ठा snd_emux *emu, व्योम __user *arg)
अणु
	पूर्णांक err;
	काष्ठा soundfont_patch_info patch;

	अगर (copy_from_user(&patch, arg, माप(patch)))
		वापस -EFAULT;

	अगर (patch.key == GUS_PATCH)
		वापस snd_soundfont_load_guspatch(emu->sflist, arg,
						   patch.len + माप(patch),
						   TMP_CLIENT_ID);

	अगर (patch.type >= SNDRV_SFNT_LOAD_INFO &&
	    patch.type <= SNDRV_SFNT_PROBE_DATA) अणु
		err = snd_soundfont_load(emu->sflist, arg, patch.len + माप(patch), TMP_CLIENT_ID);
		अगर (err < 0)
			वापस err;
	पूर्ण अन्यथा अणु
		अगर (emu->ops.load_fx)
			वापस emu->ops.load_fx(emu, patch.type, patch.optarg, arg, patch.len + माप(patch));
		अन्यथा
			वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * set misc mode
 */
अटल पूर्णांक
snd_emux_hwdep_misc_mode(काष्ठा snd_emux *emu, व्योम __user *arg)
अणु
	काष्ठा snd_emux_misc_mode info;
	पूर्णांक i;

	अगर (copy_from_user(&info, arg, माप(info)))
		वापस -EFAULT;
	अगर (info.mode < 0 || info.mode >= EMUX_MD_END)
		वापस -EINVAL;
	info.mode = array_index_nospec(info.mode, EMUX_MD_END);

	अगर (info.port < 0) अणु
		क्रम (i = 0; i < emu->num_ports; i++)
			emu->portptrs[i]->ctrls[info.mode] = info.value;
	पूर्ण अन्यथा अणु
		अगर (info.port < emu->num_ports) अणु
			info.port = array_index_nospec(info.port, emu->num_ports);
			emu->portptrs[info.port]->ctrls[info.mode] = info.value;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण


/*
 * ioctl
 */
अटल पूर्णांक
snd_emux_hwdep_ioctl(काष्ठा snd_hwdep * hw, काष्ठा file *file,
		     अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा snd_emux *emu = hw->निजी_data;

	चयन (cmd) अणु
	हाल SNDRV_EMUX_IOCTL_VERSION:
		वापस put_user(SNDRV_EMUX_VERSION, (अचिन्हित पूर्णांक __user *)arg);
	हाल SNDRV_EMUX_IOCTL_LOAD_PATCH:
		वापस snd_emux_hwdep_load_patch(emu, (व्योम __user *)arg);
	हाल SNDRV_EMUX_IOCTL_RESET_SAMPLES:
		snd_soundfont_हटाओ_samples(emu->sflist);
		अवरोध;
	हाल SNDRV_EMUX_IOCTL_REMOVE_LAST_SAMPLES:
		snd_soundfont_हटाओ_unlocked(emu->sflist);
		अवरोध;
	हाल SNDRV_EMUX_IOCTL_MEM_AVAIL:
		अगर (emu->memhdr) अणु
			पूर्णांक size = snd_util_mem_avail(emu->memhdr);
			वापस put_user(size, (अचिन्हित पूर्णांक __user *)arg);
		पूर्ण
		अवरोध;
	हाल SNDRV_EMUX_IOCTL_MISC_MODE:
		वापस snd_emux_hwdep_misc_mode(emu, (व्योम __user *)arg);
	पूर्ण

	वापस 0;
पूर्ण


/*
 * रेजिस्टर hwdep device
 */

पूर्णांक
snd_emux_init_hwdep(काष्ठा snd_emux *emu)
अणु
	काष्ठा snd_hwdep *hw;
	पूर्णांक err;

	अगर ((err = snd_hwdep_new(emu->card, SNDRV_EMUX_HWDEP_NAME, emu->hwdep_idx, &hw)) < 0)
		वापस err;
	emu->hwdep = hw;
	म_नकल(hw->name, SNDRV_EMUX_HWDEP_NAME);
	hw->अगरace = SNDRV_HWDEP_IFACE_EMUX_WAVETABLE;
	hw->ops.ioctl = snd_emux_hwdep_ioctl;
	/* The ioctl parameter types are compatible between 32- and
	 * 64-bit architectures, so use the same function. */
	hw->ops.ioctl_compat = snd_emux_hwdep_ioctl;
	hw->exclusive = 1;
	hw->निजी_data = emu;
	अगर ((err = snd_card_रेजिस्टर(emu->card)) < 0)
		वापस err;

	वापस 0;
पूर्ण


/*
 * unरेजिस्टर
 */
व्योम
snd_emux_delete_hwdep(काष्ठा snd_emux *emu)
अणु
	अगर (emu->hwdep) अणु
		snd_device_मुक्त(emu->card, emu->hwdep);
		emu->hwdep = शून्य;
	पूर्ण
पूर्ण
