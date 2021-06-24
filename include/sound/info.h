<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित __SOUND_INFO_H
#घोषणा __SOUND_INFO_H

/*
 *  Header file क्रम info पूर्णांकerface
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 */

#समावेश <linux/poll.h>
#समावेश <linux/seq_file.h>
#समावेश <sound/core.h>

/* buffer क्रम inक्रमmation */
काष्ठा snd_info_buffer अणु
	अक्षर *buffer;		/* poपूर्णांकer to begin of buffer */
	अचिन्हित पूर्णांक curr;	/* current position in buffer */
	अचिन्हित पूर्णांक size;	/* current size */
	अचिन्हित पूर्णांक len;	/* total length of buffer */
	पूर्णांक stop;		/* stop flag */
	पूर्णांक error;		/* error code */
पूर्ण;

#घोषणा SNDRV_INFO_CONTENT_TEXT		0
#घोषणा SNDRV_INFO_CONTENT_DATA		1

काष्ठा snd_info_entry;

काष्ठा snd_info_entry_text अणु
	व्योम (*पढ़ो)(काष्ठा snd_info_entry *entry,
		     काष्ठा snd_info_buffer *buffer);
	व्योम (*ग_लिखो)(काष्ठा snd_info_entry *entry,
		      काष्ठा snd_info_buffer *buffer);
पूर्ण;

काष्ठा snd_info_entry_ops अणु
	पूर्णांक (*खोलो)(काष्ठा snd_info_entry *entry,
		    अचिन्हित लघु mode, व्योम **file_निजी_data);
	पूर्णांक (*release)(काष्ठा snd_info_entry *entry,
		       अचिन्हित लघु mode, व्योम *file_निजी_data);
	sमाप_प्रकार (*पढ़ो)(काष्ठा snd_info_entry *entry, व्योम *file_निजी_data,
			काष्ठा file *file, अक्षर __user *buf,
			माप_प्रकार count, loff_t pos);
	sमाप_प्रकार (*ग_लिखो)(काष्ठा snd_info_entry *entry, व्योम *file_निजी_data,
			 काष्ठा file *file, स्थिर अक्षर __user *buf,
			 माप_प्रकार count, loff_t pos);
	loff_t (*llseek)(काष्ठा snd_info_entry *entry,
			 व्योम *file_निजी_data, काष्ठा file *file,
			 loff_t offset, पूर्णांक orig);
	__poll_t (*poll)(काष्ठा snd_info_entry *entry,
			     व्योम *file_निजी_data, काष्ठा file *file,
			     poll_table *रुको);
	पूर्णांक (*ioctl)(काष्ठा snd_info_entry *entry, व्योम *file_निजी_data,
		     काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);
	पूर्णांक (*mmap)(काष्ठा snd_info_entry *entry, व्योम *file_निजी_data,
		    काष्ठा inode *inode, काष्ठा file *file,
		    काष्ठा vm_area_काष्ठा *vma);
पूर्ण;

काष्ठा snd_info_entry अणु
	स्थिर अक्षर *name;
	umode_t mode;
	दीर्घ size;
	अचिन्हित लघु content;
	जोड़ अणु
		काष्ठा snd_info_entry_text text;
		स्थिर काष्ठा snd_info_entry_ops *ops;
	पूर्ण c;
	काष्ठा snd_info_entry *parent;
	काष्ठा module *module;
	व्योम *निजी_data;
	व्योम (*निजी_मुक्त)(काष्ठा snd_info_entry *entry);
	काष्ठा proc_dir_entry *p;
	काष्ठा mutex access;
	काष्ठा list_head children;
	काष्ठा list_head list;
पूर्ण;

#अगर defined(CONFIG_SND_OSSEMUL) && defined(CONFIG_SND_PROC_FS)
पूर्णांक snd_info_minor_रेजिस्टर(व्योम);
#अन्यथा
#घोषणा snd_info_minor_रेजिस्टर()	0
#पूर्ण_अगर


#अगर_घोषित CONFIG_SND_PROC_FS

बाह्य काष्ठा snd_info_entry *snd_seq_root;
#अगर_घोषित CONFIG_SND_OSSEMUL
बाह्य काष्ठा snd_info_entry *snd_oss_root;
व्योम snd_card_info_पढ़ो_oss(काष्ठा snd_info_buffer *buffer);
#अन्यथा
#घोषणा snd_oss_root शून्य
अटल अंतरभूत व्योम snd_card_info_पढ़ो_oss(काष्ठा snd_info_buffer *buffer) अणुपूर्ण
#पूर्ण_अगर

/**
 * snd_iम_लिखो - म_लिखो on the procfs buffer
 * @buf: the procfs buffer
 * @fmt: the म_लिखो क्रमmat
 *
 * Outमाला_दो the string on the procfs buffer just like म_लिखो().
 *
 * Return: zero क्रम success, or a negative error code.
 */
#घोषणा snd_iम_लिखो(buf, fmt, args...) \
	seq_म_लिखो((काष्ठा seq_file *)(buf)->buffer, fmt, ##args)

पूर्णांक snd_info_init(व्योम);
पूर्णांक snd_info_करोne(व्योम);

पूर्णांक snd_info_get_line(काष्ठा snd_info_buffer *buffer, अक्षर *line, पूर्णांक len);
स्थिर अक्षर *snd_info_get_str(अक्षर *dest, स्थिर अक्षर *src, पूर्णांक len);
काष्ठा snd_info_entry *snd_info_create_module_entry(काष्ठा module *module,
					       स्थिर अक्षर *name,
					       काष्ठा snd_info_entry *parent);
काष्ठा snd_info_entry *snd_info_create_card_entry(काष्ठा snd_card *card,
					     स्थिर अक्षर *name,
					     काष्ठा snd_info_entry *parent);
व्योम snd_info_मुक्त_entry(काष्ठा snd_info_entry *entry);
पूर्णांक snd_info_store_text(काष्ठा snd_info_entry *entry);
पूर्णांक snd_info_restore_text(काष्ठा snd_info_entry *entry);

पूर्णांक snd_info_card_create(काष्ठा snd_card *card);
पूर्णांक snd_info_card_रेजिस्टर(काष्ठा snd_card *card);
पूर्णांक snd_info_card_मुक्त(काष्ठा snd_card *card);
व्योम snd_info_card_disconnect(काष्ठा snd_card *card);
व्योम snd_info_card_id_change(काष्ठा snd_card *card);
पूर्णांक snd_info_रेजिस्टर(काष्ठा snd_info_entry *entry);

/* क्रम card drivers */
अटल अंतरभूत पूर्णांक snd_card_proc_new(काष्ठा snd_card *card, स्थिर अक्षर *name,
				    काष्ठा snd_info_entry **entryp)
अणु
	*entryp = snd_info_create_card_entry(card, name, card->proc_root);
	वापस *entryp ? 0 : -ENOMEM;
पूर्ण

अटल अंतरभूत व्योम snd_info_set_text_ops(काष्ठा snd_info_entry *entry, 
	व्योम *निजी_data,
	व्योम (*पढ़ो)(काष्ठा snd_info_entry *, काष्ठा snd_info_buffer *))
अणु
	entry->निजी_data = निजी_data;
	entry->c.text.पढ़ो = पढ़ो;
पूर्ण

पूर्णांक snd_card_rw_proc_new(काष्ठा snd_card *card, स्थिर अक्षर *name,
			 व्योम *निजी_data,
			 व्योम (*पढ़ो)(काष्ठा snd_info_entry *,
				      काष्ठा snd_info_buffer *),
			 व्योम (*ग_लिखो)(काष्ठा snd_info_entry *entry,
				       काष्ठा snd_info_buffer *buffer));

पूर्णांक snd_info_check_reserved_words(स्थिर अक्षर *str);

#अन्यथा

#घोषणा snd_seq_root शून्य
#घोषणा snd_oss_root शून्य

अटल अंतरभूत पूर्णांक snd_iम_लिखो(काष्ठा snd_info_buffer *buffer, अक्षर *fmt, ...) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक snd_info_init(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक snd_info_करोne(व्योम) अणु वापस 0; पूर्ण

अटल अंतरभूत पूर्णांक snd_info_get_line(काष्ठा snd_info_buffer *buffer, अक्षर *line, पूर्णांक len) अणु वापस 0; पूर्ण
अटल अंतरभूत अक्षर *snd_info_get_str(अक्षर *dest, अक्षर *src, पूर्णांक len) अणु वापस शून्य; पूर्ण
अटल अंतरभूत काष्ठा snd_info_entry *snd_info_create_module_entry(काष्ठा module *module, स्थिर अक्षर *name, काष्ठा snd_info_entry *parent) अणु वापस शून्य; पूर्ण
अटल अंतरभूत काष्ठा snd_info_entry *snd_info_create_card_entry(काष्ठा snd_card *card, स्थिर अक्षर *name, काष्ठा snd_info_entry *parent) अणु वापस शून्य; पूर्ण
अटल अंतरभूत व्योम snd_info_मुक्त_entry(काष्ठा snd_info_entry *entry) अणु ; पूर्ण

अटल अंतरभूत पूर्णांक snd_info_card_create(काष्ठा snd_card *card) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक snd_info_card_रेजिस्टर(काष्ठा snd_card *card) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक snd_info_card_मुक्त(काष्ठा snd_card *card) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम snd_info_card_disconnect(काष्ठा snd_card *card) अणु पूर्ण
अटल अंतरभूत व्योम snd_info_card_id_change(काष्ठा snd_card *card) अणु पूर्ण
अटल अंतरभूत पूर्णांक snd_info_रेजिस्टर(काष्ठा snd_info_entry *entry) अणु वापस 0; पूर्ण

अटल अंतरभूत पूर्णांक snd_card_proc_new(काष्ठा snd_card *card, स्थिर अक्षर *name,
				    काष्ठा snd_info_entry **entryp) अणु वापस -EINVAL; पूर्ण
अटल अंतरभूत व्योम snd_info_set_text_ops(काष्ठा snd_info_entry *entry __attribute__((unused)),
					 व्योम *निजी_data,
					 व्योम (*पढ़ो)(काष्ठा snd_info_entry *, काष्ठा snd_info_buffer *)) अणुपूर्ण
अटल अंतरभूत पूर्णांक snd_card_rw_proc_new(काष्ठा snd_card *card, स्थिर अक्षर *name,
				       व्योम *निजी_data,
				       व्योम (*पढ़ो)(काष्ठा snd_info_entry *,
						    काष्ठा snd_info_buffer *),
				       व्योम (*ग_लिखो)(काष्ठा snd_info_entry *entry,
						     काष्ठा snd_info_buffer *buffer))
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक snd_info_check_reserved_words(स्थिर अक्षर *str) अणु वापस 1; पूर्ण

#पूर्ण_अगर

/**
 * snd_card_ro_proc_new - Create a पढ़ो-only text proc file entry क्रम the card
 * @card: the card instance
 * @name: the file name
 * @निजी_data: the arbitrary निजी data
 * @पढ़ो: the पढ़ो callback
 *
 * This proc file entry will be रेजिस्टरed via snd_card_रेजिस्टर() call, and
 * it will be हटाओd स्वतःmatically at the card removal, too.
 */
अटल अंतरभूत पूर्णांक
snd_card_ro_proc_new(काष्ठा snd_card *card, स्थिर अक्षर *name,
		     व्योम *निजी_data,
		     व्योम (*पढ़ो)(काष्ठा snd_info_entry *,
				  काष्ठा snd_info_buffer *))
अणु
	वापस snd_card_rw_proc_new(card, name, निजी_data, पढ़ो, शून्य);
पूर्ण

/*
 * OSS info part
 */

#अगर defined(CONFIG_SND_OSSEMUL) && defined(CONFIG_SND_PROC_FS)

#घोषणा SNDRV_OSS_INFO_DEV_AUDIO	0
#घोषणा SNDRV_OSS_INFO_DEV_SYNTH	1
#घोषणा SNDRV_OSS_INFO_DEV_MIDI		2
#घोषणा SNDRV_OSS_INFO_DEV_TIMERS	4
#घोषणा SNDRV_OSS_INFO_DEV_MIXERS	5

#घोषणा SNDRV_OSS_INFO_DEV_COUNT	6

पूर्णांक snd_oss_info_रेजिस्टर(पूर्णांक dev, पूर्णांक num, अक्षर *string);
#घोषणा snd_oss_info_unरेजिस्टर(dev, num) snd_oss_info_रेजिस्टर(dev, num, शून्य)

#पूर्ण_अगर /* CONFIG_SND_OSSEMUL && CONFIG_SND_PROC_FS */

#पूर्ण_अगर /* __SOUND_INFO_H */
