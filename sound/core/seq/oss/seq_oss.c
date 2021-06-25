<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * OSS compatible sequencer driver
 *
 * registration of device and proc
 *
 * Copyright (C) 1998,99 Takashi Iwai <tiwai@suse.de>
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/compat.h>
#समावेश <sound/core.h>
#समावेश <sound/minors.h>
#समावेश <sound/initval.h>
#समावेश "seq_oss_device.h"
#समावेश "seq_oss_synth.h"

/*
 * module option
 */
MODULE_AUTHOR("Takashi Iwai <tiwai@suse.de>");
MODULE_DESCRIPTION("OSS-compatible sequencer module");
MODULE_LICENSE("GPL");
/* Takashi says this is really only क्रम sound-service-0-, but this is OK. */
MODULE_ALIAS_SNDRV_MINOR(SNDRV_MINOR_OSS_SEQUENCER);
MODULE_ALIAS_SNDRV_MINOR(SNDRV_MINOR_OSS_MUSIC);


/*
 * prototypes
 */
अटल पूर्णांक रेजिस्टर_device(व्योम);
अटल व्योम unरेजिस्टर_device(व्योम);
#अगर_घोषित CONFIG_SND_PROC_FS
अटल पूर्णांक रेजिस्टर_proc(व्योम);
अटल व्योम unरेजिस्टर_proc(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक रेजिस्टर_proc(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम unरेजिस्टर_proc(व्योम) अणुपूर्ण
#पूर्ण_अगर

अटल पूर्णांक odev_खोलो(काष्ठा inode *inode, काष्ठा file *file);
अटल पूर्णांक odev_release(काष्ठा inode *inode, काष्ठा file *file);
अटल sमाप_प्रकार odev_पढ़ो(काष्ठा file *file, अक्षर __user *buf, माप_प्रकार count, loff_t *offset);
अटल sमाप_प्रकार odev_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf, माप_प्रकार count, loff_t *offset);
अटल दीर्घ odev_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);
अटल __poll_t odev_poll(काष्ठा file *file, poll_table * रुको);


/*
 * module पूर्णांकerface
 */

अटल काष्ठा snd_seq_driver seq_oss_synth_driver = अणु
	.driver = अणु
		.name = KBUILD_MODNAME,
		.probe = snd_seq_oss_synth_probe,
		.हटाओ = snd_seq_oss_synth_हटाओ,
	पूर्ण,
	.id = SNDRV_SEQ_DEV_ID_OSS,
	.argsize = माप(काष्ठा snd_seq_oss_reg),
पूर्ण;

अटल पूर्णांक __init alsa_seq_oss_init(व्योम)
अणु
	पूर्णांक rc;

	अगर ((rc = रेजिस्टर_device()) < 0)
		जाओ error;
	अगर ((rc = रेजिस्टर_proc()) < 0) अणु
		unरेजिस्टर_device();
		जाओ error;
	पूर्ण
	अगर ((rc = snd_seq_oss_create_client()) < 0) अणु
		unरेजिस्टर_proc();
		unरेजिस्टर_device();
		जाओ error;
	पूर्ण

	rc = snd_seq_driver_रेजिस्टर(&seq_oss_synth_driver);
	अगर (rc < 0) अणु
		snd_seq_oss_delete_client();
		unरेजिस्टर_proc();
		unरेजिस्टर_device();
		जाओ error;
	पूर्ण

	/* success */
	snd_seq_oss_synth_init();

 error:
	वापस rc;
पूर्ण

अटल व्योम __निकास alsa_seq_oss_निकास(व्योम)
अणु
	snd_seq_driver_unरेजिस्टर(&seq_oss_synth_driver);
	snd_seq_oss_delete_client();
	unरेजिस्टर_proc();
	unरेजिस्टर_device();
पूर्ण

module_init(alsa_seq_oss_init)
module_निकास(alsa_seq_oss_निकास)

/*
 * ALSA minor device पूर्णांकerface
 */

अटल DEFINE_MUTEX(रेजिस्टर_mutex);

अटल पूर्णांक
odev_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	पूर्णांक level, rc;

	अगर (iminor(inode) == SNDRV_MINOR_OSS_MUSIC)
		level = SNDRV_SEQ_OSS_MODE_MUSIC;
	अन्यथा
		level = SNDRV_SEQ_OSS_MODE_SYNTH;

	mutex_lock(&रेजिस्टर_mutex);
	rc = snd_seq_oss_खोलो(file, level);
	mutex_unlock(&रेजिस्टर_mutex);

	वापस rc;
पूर्ण

अटल पूर्णांक
odev_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा seq_oss_devinfo *dp;

	अगर ((dp = file->निजी_data) == शून्य)
		वापस 0;

	mutex_lock(&रेजिस्टर_mutex);
	snd_seq_oss_release(dp);
	mutex_unlock(&रेजिस्टर_mutex);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार
odev_पढ़ो(काष्ठा file *file, अक्षर __user *buf, माप_प्रकार count, loff_t *offset)
अणु
	काष्ठा seq_oss_devinfo *dp;
	dp = file->निजी_data;
	अगर (snd_BUG_ON(!dp))
		वापस -ENXIO;
	वापस snd_seq_oss_पढ़ो(dp, buf, count);
पूर्ण


अटल sमाप_प्रकार
odev_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf, माप_प्रकार count, loff_t *offset)
अणु
	काष्ठा seq_oss_devinfo *dp;
	dp = file->निजी_data;
	अगर (snd_BUG_ON(!dp))
		वापस -ENXIO;
	वापस snd_seq_oss_ग_लिखो(dp, buf, count, file);
पूर्ण

अटल दीर्घ
odev_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा seq_oss_devinfo *dp;
	दीर्घ rc;

	dp = file->निजी_data;
	अगर (snd_BUG_ON(!dp))
		वापस -ENXIO;

	अगर (cmd != SNDCTL_SEQ_SYNC &&
	    mutex_lock_पूर्णांकerruptible(&रेजिस्टर_mutex))
		वापस -ERESTARTSYS;
	rc = snd_seq_oss_ioctl(dp, cmd, arg);
	अगर (cmd != SNDCTL_SEQ_SYNC)
		mutex_unlock(&रेजिस्टर_mutex);
	वापस rc;
पूर्ण

#अगर_घोषित CONFIG_COMPAT
अटल दीर्घ odev_ioctl_compat(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
			      अचिन्हित दीर्घ arg)
अणु
	वापस odev_ioctl(file, cmd, (अचिन्हित दीर्घ)compat_ptr(arg));
पूर्ण
#अन्यथा
#घोषणा odev_ioctl_compat	शून्य
#पूर्ण_अगर

अटल __poll_t
odev_poll(काष्ठा file *file, poll_table * रुको)
अणु
	काष्ठा seq_oss_devinfo *dp;
	dp = file->निजी_data;
	अगर (snd_BUG_ON(!dp))
		वापस EPOLLERR;
	वापस snd_seq_oss_poll(dp, file, रुको);
पूर्ण

/*
 * registration of sequencer minor device
 */

अटल स्थिर काष्ठा file_operations seq_oss_f_ops =
अणु
	.owner =	THIS_MODULE,
	.पढ़ो =		odev_पढ़ो,
	.ग_लिखो =	odev_ग_लिखो,
	.खोलो =		odev_खोलो,
	.release =	odev_release,
	.poll =		odev_poll,
	.unlocked_ioctl =	odev_ioctl,
	.compat_ioctl =	odev_ioctl_compat,
	.llseek =	noop_llseek,
पूर्ण;

अटल पूर्णांक __init
रेजिस्टर_device(व्योम)
अणु
	पूर्णांक rc;

	mutex_lock(&रेजिस्टर_mutex);
	अगर ((rc = snd_रेजिस्टर_oss_device(SNDRV_OSS_DEVICE_TYPE_SEQUENCER,
					  शून्य, 0,
					  &seq_oss_f_ops, शून्य)) < 0) अणु
		pr_err("ALSA: seq_oss: can't register device seq\n");
		mutex_unlock(&रेजिस्टर_mutex);
		वापस rc;
	पूर्ण
	अगर ((rc = snd_रेजिस्टर_oss_device(SNDRV_OSS_DEVICE_TYPE_MUSIC,
					  शून्य, 0,
					  &seq_oss_f_ops, शून्य)) < 0) अणु
		pr_err("ALSA: seq_oss: can't register device music\n");
		snd_unरेजिस्टर_oss_device(SNDRV_OSS_DEVICE_TYPE_SEQUENCER, शून्य, 0);
		mutex_unlock(&रेजिस्टर_mutex);
		वापस rc;
	पूर्ण
	mutex_unlock(&रेजिस्टर_mutex);
	वापस 0;
पूर्ण

अटल व्योम
unरेजिस्टर_device(व्योम)
अणु
	mutex_lock(&रेजिस्टर_mutex);
	अगर (snd_unरेजिस्टर_oss_device(SNDRV_OSS_DEVICE_TYPE_MUSIC, शून्य, 0) < 0)		
		pr_err("ALSA: seq_oss: error unregister device music\n");
	अगर (snd_unरेजिस्टर_oss_device(SNDRV_OSS_DEVICE_TYPE_SEQUENCER, शून्य, 0) < 0)
		pr_err("ALSA: seq_oss: error unregister device seq\n");
	mutex_unlock(&रेजिस्टर_mutex);
पूर्ण

/*
 * /proc पूर्णांकerface
 */

#अगर_घोषित CONFIG_SND_PROC_FS

अटल काष्ठा snd_info_entry *info_entry;

अटल व्योम
info_पढ़ो(काष्ठा snd_info_entry *entry, काष्ठा snd_info_buffer *buf)
अणु
	mutex_lock(&रेजिस्टर_mutex);
	snd_iम_लिखो(buf, "OSS sequencer emulation version %s\n", SNDRV_SEQ_OSS_VERSION_STR);
	snd_seq_oss_प्रणाली_info_पढ़ो(buf);
	snd_seq_oss_synth_info_पढ़ो(buf);
	snd_seq_oss_midi_info_पढ़ो(buf);
	mutex_unlock(&रेजिस्टर_mutex);
पूर्ण


अटल पूर्णांक __init
रेजिस्टर_proc(व्योम)
अणु
	काष्ठा snd_info_entry *entry;

	entry = snd_info_create_module_entry(THIS_MODULE, SNDRV_SEQ_OSS_PROCNAME, snd_seq_root);
	अगर (entry == शून्य)
		वापस -ENOMEM;

	entry->content = SNDRV_INFO_CONTENT_TEXT;
	entry->निजी_data = शून्य;
	entry->c.text.पढ़ो = info_पढ़ो;
	अगर (snd_info_रेजिस्टर(entry) < 0) अणु
		snd_info_मुक्त_entry(entry);
		वापस -ENOMEM;
	पूर्ण
	info_entry = entry;
	वापस 0;
पूर्ण

अटल व्योम
unरेजिस्टर_proc(व्योम)
अणु
	snd_info_मुक्त_entry(info_entry);
	info_entry = शून्य;
पूर्ण
#पूर्ण_अगर /* CONFIG_SND_PROC_FS */
