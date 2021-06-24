<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Inक्रमmation पूर्णांकerface क्रम ALSA driver
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 */

#समावेश <linux/slab.h>
#समावेश <linux/समय.स>
#समावेश <linux/माला.स>
#समावेश <linux/export.h>
#समावेश <sound/core.h>
#समावेश <sound/minors.h>
#समावेश <sound/info.h>
#समावेश <linux/utsname.h>
#समावेश <linux/mutex.h>

/*
 *  OSS compatible part
 */

अटल DEFINE_MUTEX(strings);
अटल अक्षर *snd_sndstat_strings[SNDRV_CARDS][SNDRV_OSS_INFO_DEV_COUNT];

पूर्णांक snd_oss_info_रेजिस्टर(पूर्णांक dev, पूर्णांक num, अक्षर *string)
अणु
	अक्षर *x;

	अगर (snd_BUG_ON(dev < 0 || dev >= SNDRV_OSS_INFO_DEV_COUNT))
		वापस -ENXIO;
	अगर (snd_BUG_ON(num < 0 || num >= SNDRV_CARDS))
		वापस -ENXIO;
	mutex_lock(&strings);
	अगर (string == शून्य) अणु
		अगर ((x = snd_sndstat_strings[num][dev]) != शून्य) अणु
			kमुक्त(x);
			x = शून्य;
		पूर्ण
	पूर्ण अन्यथा अणु
		x = kstrdup(string, GFP_KERNEL);
		अगर (x == शून्य) अणु
			mutex_unlock(&strings);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण
	snd_sndstat_strings[num][dev] = x;
	mutex_unlock(&strings);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(snd_oss_info_रेजिस्टर);

अटल पूर्णांक snd_sndstat_show_strings(काष्ठा snd_info_buffer *buf, अक्षर *id, पूर्णांक dev)
अणु
	पूर्णांक idx, ok = -1;
	अक्षर *str;

	snd_iम_लिखो(buf, "\n%s:", id);
	mutex_lock(&strings);
	क्रम (idx = 0; idx < SNDRV_CARDS; idx++) अणु
		str = snd_sndstat_strings[idx][dev];
		अगर (str) अणु
			अगर (ok < 0) अणु
				snd_iम_लिखो(buf, "\n");
				ok++;
			पूर्ण
			snd_iम_लिखो(buf, "%i: %s\n", idx, str);
		पूर्ण
	पूर्ण
	mutex_unlock(&strings);
	अगर (ok < 0)
		snd_iम_लिखो(buf, " NOT ENABLED IN CONFIG\n");
	वापस ok;
पूर्ण

अटल व्योम snd_sndstat_proc_पढ़ो(काष्ठा snd_info_entry *entry,
				  काष्ठा snd_info_buffer *buffer)
अणु
	snd_iम_लिखो(buffer, "Sound Driver:3.8.1a-980706 (ALSA emulation code)\n");
	snd_iम_लिखो(buffer, "Kernel: %s %s %s %s %s\n",
		    init_utsname()->sysname,
		    init_utsname()->nodename,
		    init_utsname()->release,
		    init_utsname()->version,
		    init_utsname()->machine);
	snd_iम_लिखो(buffer, "Config options: 0\n");
	snd_iम_लिखो(buffer, "\nInstalled drivers: \n");
	snd_iम_लिखो(buffer, "Type 10: ALSA emulation\n");
	snd_iम_लिखो(buffer, "\nCard config: \n");
	snd_card_info_पढ़ो_oss(buffer);
	snd_sndstat_show_strings(buffer, "Audio devices", SNDRV_OSS_INFO_DEV_AUDIO);
	snd_sndstat_show_strings(buffer, "Synth devices", SNDRV_OSS_INFO_DEV_SYNTH);
	snd_sndstat_show_strings(buffer, "Midi devices", SNDRV_OSS_INFO_DEV_MIDI);
	snd_sndstat_show_strings(buffer, "Timers", SNDRV_OSS_INFO_DEV_TIMERS);
	snd_sndstat_show_strings(buffer, "Mixers", SNDRV_OSS_INFO_DEV_MIXERS);
पूर्ण

पूर्णांक __init snd_info_minor_रेजिस्टर(व्योम)
अणु
	काष्ठा snd_info_entry *entry;

	स_रखो(snd_sndstat_strings, 0, माप(snd_sndstat_strings));
	entry = snd_info_create_module_entry(THIS_MODULE, "sndstat",
					     snd_oss_root);
	अगर (!entry)
		वापस -ENOMEM;
	entry->c.text.पढ़ो = snd_sndstat_proc_पढ़ो;
	वापस snd_info_रेजिस्टर(entry); /* मुक्तd in error path */
पूर्ण
