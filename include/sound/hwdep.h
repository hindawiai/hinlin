<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित __SOUND_HWDEP_H
#घोषणा __SOUND_HWDEP_H

/*
 *  Hardware dependent layer 
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 */

#समावेश <sound/asound.h>
#समावेश <linux/poll.h>

काष्ठा snd_hwdep;

/* hwdep file ops; all ops can be शून्य */
काष्ठा snd_hwdep_ops अणु
	दीर्घ दीर्घ (*llseek)(काष्ठा snd_hwdep *hw, काष्ठा file *file,
			    दीर्घ दीर्घ offset, पूर्णांक orig);
	दीर्घ (*पढ़ो)(काष्ठा snd_hwdep *hw, अक्षर __user *buf,
		     दीर्घ count, loff_t *offset);
	दीर्घ (*ग_लिखो)(काष्ठा snd_hwdep *hw, स्थिर अक्षर __user *buf,
		      दीर्घ count, loff_t *offset);
	पूर्णांक (*खोलो)(काष्ठा snd_hwdep *hw, काष्ठा file * file);
	पूर्णांक (*release)(काष्ठा snd_hwdep *hw, काष्ठा file * file);
	__poll_t (*poll)(काष्ठा snd_hwdep *hw, काष्ठा file *file,
			     poll_table *रुको);
	पूर्णांक (*ioctl)(काष्ठा snd_hwdep *hw, काष्ठा file *file,
		     अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);
	पूर्णांक (*ioctl_compat)(काष्ठा snd_hwdep *hw, काष्ठा file *file,
			    अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);
	पूर्णांक (*mmap)(काष्ठा snd_hwdep *hw, काष्ठा file *file,
		    काष्ठा vm_area_काष्ठा *vma);
	पूर्णांक (*dsp_status)(काष्ठा snd_hwdep *hw,
			  काष्ठा snd_hwdep_dsp_status *status);
	पूर्णांक (*dsp_load)(काष्ठा snd_hwdep *hw,
			काष्ठा snd_hwdep_dsp_image *image);
पूर्ण;

काष्ठा snd_hwdep अणु
	काष्ठा snd_card *card;
	काष्ठा list_head list;
	पूर्णांक device;
	अक्षर id[32];
	अक्षर name[80];
	पूर्णांक अगरace;

#अगर_घोषित CONFIG_SND_OSSEMUL
	पूर्णांक oss_type;
	पूर्णांक ossreg;
#पूर्ण_अगर

	काष्ठा snd_hwdep_ops ops;
	रुको_queue_head_t खोलो_रुको;
	व्योम *निजी_data;
	व्योम (*निजी_मुक्त) (काष्ठा snd_hwdep *hwdep);
	काष्ठा device dev;

	काष्ठा mutex खोलो_mutex;
	पूर्णांक used;			/* reference counter */
	अचिन्हित पूर्णांक dsp_loaded;	/* bit fields of loaded dsp indices */
	अचिन्हित पूर्णांक exclusive:1;	/* exclusive access mode */
पूर्ण;

बाह्य पूर्णांक snd_hwdep_new(काष्ठा snd_card *card, अक्षर *id, पूर्णांक device,
			 काष्ठा snd_hwdep **rhwdep);

#पूर्ण_अगर /* __SOUND_HWDEP_H */
