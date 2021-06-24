<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2002 Steve Schmidtke
 */

#समावेश <linux/fs.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/sound.h>
#समावेश <linux/soundcard.h>
#समावेश <linux/mutex.h>
#समावेश <linux/uaccess.h>
#समावेश <init.h>
#समावेश <os.h>

काष्ठा hostaudio_state अणु
	पूर्णांक fd;
पूर्ण;

काष्ठा hosपंचांगixer_state अणु
	पूर्णांक fd;
पूर्ण;

#घोषणा HOSTAUDIO_DEV_DSP "/dev/sound/dsp"
#घोषणा HOSTAUDIO_DEV_MIXER "/dev/sound/mixer"

/*
 * Changed either at boot समय or module load समय.  At boot, this is
 * single-thपढ़ोed; at module load, multiple modules would each have
 * their own copy of these variables.
 */
अटल अक्षर *dsp = HOSTAUDIO_DEV_DSP;
अटल अक्षर *mixer = HOSTAUDIO_DEV_MIXER;

#घोषणा DSP_HELP \
"    This is used to specify the host dsp device to the hostaudio driver.\n" \
"    The default is \"" HOSTAUDIO_DEV_DSP "\".\n\n"

#घोषणा MIXER_HELP \
"    This is used to specify the host mixer device to the hostaudio driver.\n"\
"    The default is \"" HOSTAUDIO_DEV_MIXER "\".\n\n"

module_param(dsp, अक्षरp, 0644);
MODULE_PARM_DESC(dsp, DSP_HELP);
module_param(mixer, अक्षरp, 0644);
MODULE_PARM_DESC(mixer, MIXER_HELP);

#अगर_अघोषित MODULE
अटल पूर्णांक set_dsp(अक्षर *name, पूर्णांक *add)
अणु
	dsp = name;
	वापस 0;
पूर्ण

__uml_setup("dsp=", set_dsp, "dsp=<dsp device>\n" DSP_HELP);

अटल पूर्णांक set_mixer(अक्षर *name, पूर्णांक *add)
अणु
	mixer = name;
	वापस 0;
पूर्ण

__uml_setup("mixer=", set_mixer, "mixer=<mixer device>\n" MIXER_HELP);
#पूर्ण_अगर

अटल DEFINE_MUTEX(hostaudio_mutex);

/* /dev/dsp file operations */

अटल sमाप_प्रकार hostaudio_पढ़ो(काष्ठा file *file, अक्षर __user *buffer,
			      माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा hostaudio_state *state = file->निजी_data;
	व्योम *kbuf;
	पूर्णांक err;

#अगर_घोषित DEBUG
	prपूर्णांकk(KERN_DEBUG "hostaudio: read called, count = %d\n", count);
#पूर्ण_अगर

	kbuf = kदो_स्मृति(count, GFP_KERNEL);
	अगर (kbuf == शून्य)
		वापस -ENOMEM;

	err = os_पढ़ो_file(state->fd, kbuf, count);
	अगर (err < 0)
		जाओ out;

	अगर (copy_to_user(buffer, kbuf, err))
		err = -EFAULT;

out:
	kमुक्त(kbuf);
	वापस err;
पूर्ण

अटल sमाप_प्रकार hostaudio_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buffer,
			       माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा hostaudio_state *state = file->निजी_data;
	व्योम *kbuf;
	पूर्णांक err;

#अगर_घोषित DEBUG
	prपूर्णांकk(KERN_DEBUG "hostaudio: write called, count = %d\n", count);
#पूर्ण_अगर

	kbuf = memdup_user(buffer, count);
	अगर (IS_ERR(kbuf))
		वापस PTR_ERR(kbuf);

	err = os_ग_लिखो_file(state->fd, kbuf, count);
	अगर (err < 0)
		जाओ out;
	*ppos += err;

 out:
	kमुक्त(kbuf);
	वापस err;
पूर्ण

अटल __poll_t hostaudio_poll(काष्ठा file *file,
				काष्ठा poll_table_काष्ठा *रुको)
अणु
#अगर_घोषित DEBUG
	prपूर्णांकk(KERN_DEBUG "hostaudio: poll called (unimplemented)\n");
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल दीर्घ hostaudio_ioctl(काष्ठा file *file,
			   अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा hostaudio_state *state = file->निजी_data;
	अचिन्हित दीर्घ data = 0;
	पूर्णांक err;

#अगर_घोषित DEBUG
	prपूर्णांकk(KERN_DEBUG "hostaudio: ioctl called, cmd = %u\n", cmd);
#पूर्ण_अगर
	चयन(cmd)अणु
	हाल SNDCTL_DSP_SPEED:
	हाल SNDCTL_DSP_STEREO:
	हाल SNDCTL_DSP_GETBLKSIZE:
	हाल SNDCTL_DSP_CHANNELS:
	हाल SNDCTL_DSP_SUBDIVIDE:
	हाल SNDCTL_DSP_SETFRAGMENT:
		अगर (get_user(data, (पूर्णांक __user *) arg))
			वापस -EFAULT;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	err = os_ioctl_generic(state->fd, cmd, (अचिन्हित दीर्घ) &data);

	चयन(cmd)अणु
	हाल SNDCTL_DSP_SPEED:
	हाल SNDCTL_DSP_STEREO:
	हाल SNDCTL_DSP_GETBLKSIZE:
	हाल SNDCTL_DSP_CHANNELS:
	हाल SNDCTL_DSP_SUBDIVIDE:
	हाल SNDCTL_DSP_SETFRAGMENT:
		अगर (put_user(data, (पूर्णांक __user *) arg))
			वापस -EFAULT;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक hostaudio_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा hostaudio_state *state;
	पूर्णांक r = 0, w = 0;
	पूर्णांक ret;

#अगर_घोषित DEBUG
	kernel_param_lock(THIS_MODULE);
	prपूर्णांकk(KERN_DEBUG "hostaudio: open called (host: %s)\n", dsp);
	kernel_param_unlock(THIS_MODULE);
#पूर्ण_अगर

	state = kदो_स्मृति(माप(काष्ठा hostaudio_state), GFP_KERNEL);
	अगर (state == शून्य)
		वापस -ENOMEM;

	अगर (file->f_mode & FMODE_READ)
		r = 1;
	अगर (file->f_mode & FMODE_WRITE)
		w = 1;

	kernel_param_lock(THIS_MODULE);
	mutex_lock(&hostaudio_mutex);
	ret = os_खोलो_file(dsp, of_set_rw(OPENFLAGS(), r, w), 0);
	mutex_unlock(&hostaudio_mutex);
	kernel_param_unlock(THIS_MODULE);

	अगर (ret < 0) अणु
		kमुक्त(state);
		वापस ret;
	पूर्ण
	state->fd = ret;
	file->निजी_data = state;
	वापस 0;
पूर्ण

अटल पूर्णांक hostaudio_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा hostaudio_state *state = file->निजी_data;

#अगर_घोषित DEBUG
	prपूर्णांकk(KERN_DEBUG "hostaudio: release called\n");
#पूर्ण_अगर
	os_बंद_file(state->fd);
	kमुक्त(state);

	वापस 0;
पूर्ण

/* /dev/mixer file operations */

अटल दीर्घ hosपंचांगixer_ioctl_mixdev(काष्ठा file *file,
				  अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा hosपंचांगixer_state *state = file->निजी_data;

#अगर_घोषित DEBUG
	prपूर्णांकk(KERN_DEBUG "hostmixer: ioctl called\n");
#पूर्ण_अगर

	वापस os_ioctl_generic(state->fd, cmd, arg);
पूर्ण

अटल पूर्णांक hosपंचांगixer_खोलो_mixdev(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा hosपंचांगixer_state *state;
	पूर्णांक r = 0, w = 0;
	पूर्णांक ret;

#अगर_घोषित DEBUG
	prपूर्णांकk(KERN_DEBUG "hostmixer: open called (host: %s)\n", mixer);
#पूर्ण_अगर

	state = kदो_स्मृति(माप(काष्ठा hosपंचांगixer_state), GFP_KERNEL);
	अगर (state == शून्य)
		वापस -ENOMEM;

	अगर (file->f_mode & FMODE_READ)
		r = 1;
	अगर (file->f_mode & FMODE_WRITE)
		w = 1;

	kernel_param_lock(THIS_MODULE);
	mutex_lock(&hostaudio_mutex);
	ret = os_खोलो_file(mixer, of_set_rw(OPENFLAGS(), r, w), 0);
	mutex_unlock(&hostaudio_mutex);
	kernel_param_unlock(THIS_MODULE);

	अगर (ret < 0) अणु
		kernel_param_lock(THIS_MODULE);
		prपूर्णांकk(KERN_ERR "hostaudio_open_mixdev failed to open '%s', "
		       "err = %d\n", dsp, -ret);
		kernel_param_unlock(THIS_MODULE);
		kमुक्त(state);
		वापस ret;
	पूर्ण

	file->निजी_data = state;
	वापस 0;
पूर्ण

अटल पूर्णांक hosपंचांगixer_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा hosपंचांगixer_state *state = file->निजी_data;

#अगर_घोषित DEBUG
	prपूर्णांकk(KERN_DEBUG "hostmixer: release called\n");
#पूर्ण_अगर

	os_बंद_file(state->fd);
	kमुक्त(state);

	वापस 0;
पूर्ण

/* kernel module operations */

अटल स्थिर काष्ठा file_operations hostaudio_fops = अणु
	.owner          = THIS_MODULE,
	.llseek         = no_llseek,
	.पढ़ो           = hostaudio_पढ़ो,
	.ग_लिखो          = hostaudio_ग_लिखो,
	.poll           = hostaudio_poll,
	.unlocked_ioctl	= hostaudio_ioctl,
	.compat_ioctl	= compat_ptr_ioctl,
	.mmap           = शून्य,
	.खोलो           = hostaudio_खोलो,
	.release        = hostaudio_release,
पूर्ण;

अटल स्थिर काष्ठा file_operations hosपंचांगixer_fops = अणु
	.owner          = THIS_MODULE,
	.llseek         = no_llseek,
	.unlocked_ioctl	= hosपंचांगixer_ioctl_mixdev,
	.खोलो           = hosपंचांगixer_खोलो_mixdev,
	.release        = hosपंचांगixer_release,
पूर्ण;

काष्ठा अणु
	पूर्णांक dev_audio;
	पूर्णांक dev_mixer;
पूर्ण module_data;

MODULE_AUTHOR("Steve Schmidtke");
MODULE_DESCRIPTION("UML Audio Relay");
MODULE_LICENSE("GPL");

अटल पूर्णांक __init hostaudio_init_module(व्योम)
अणु
	kernel_param_lock(THIS_MODULE);
	prपूर्णांकk(KERN_INFO "UML Audio Relay (host dsp = %s, host mixer = %s)\n",
	       dsp, mixer);
	kernel_param_unlock(THIS_MODULE);

	module_data.dev_audio = रेजिस्टर_sound_dsp(&hostaudio_fops, -1);
	अगर (module_data.dev_audio < 0) अणु
		prपूर्णांकk(KERN_ERR "hostaudio: couldn't register DSP device!\n");
		वापस -ENODEV;
	पूर्ण

	module_data.dev_mixer = रेजिस्टर_sound_mixer(&hosपंचांगixer_fops, -1);
	अगर (module_data.dev_mixer < 0) अणु
		prपूर्णांकk(KERN_ERR "hostmixer: couldn't register mixer "
		       "device!\n");
		unरेजिस्टर_sound_dsp(module_data.dev_audio);
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास hostaudio_cleanup_module (व्योम)
अणु
	unरेजिस्टर_sound_mixer(module_data.dev_mixer);
	unरेजिस्टर_sound_dsp(module_data.dev_audio);
पूर्ण

module_init(hostaudio_init_module);
module_निकास(hostaudio_cleanup_module);
