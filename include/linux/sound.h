<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_SOUND_H
#घोषणा _LINUX_SOUND_H

#समावेश <uapi/linux/sound.h>

/*
 *	Sound core पूर्णांकerface functions
 */
 
काष्ठा device;
बाह्य पूर्णांक रेजिस्टर_sound_special(स्थिर काष्ठा file_operations *fops, पूर्णांक unit);
बाह्य पूर्णांक रेजिस्टर_sound_special_device(स्थिर काष्ठा file_operations *fops, पूर्णांक unit, काष्ठा device *dev);
बाह्य पूर्णांक रेजिस्टर_sound_mixer(स्थिर काष्ठा file_operations *fops, पूर्णांक dev);
बाह्य पूर्णांक रेजिस्टर_sound_dsp(स्थिर काष्ठा file_operations *fops, पूर्णांक dev);

बाह्य व्योम unरेजिस्टर_sound_special(पूर्णांक unit);
बाह्य व्योम unरेजिस्टर_sound_mixer(पूर्णांक unit);
बाह्य व्योम unरेजिस्टर_sound_dsp(पूर्णांक unit);
#पूर्ण_अगर /* _LINUX_SOUND_H */
