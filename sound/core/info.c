<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Inक्रमmation पूर्णांकerface क्रम ALSA driver
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 */

#समावेश <linux/init.h>
#समावेश <linux/समय.स>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/module.h>
#समावेश <sound/core.h>
#समावेश <sound/minors.h>
#समावेश <sound/info.h>
#समावेश <linux/utsname.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/mutex.h>
#समावेश <मानकतर्क.स>

पूर्णांक snd_info_check_reserved_words(स्थिर अक्षर *str)
अणु
	अटल स्थिर अक्षर * स्थिर reserved[] =
	अणु
		"version",
		"meminfo",
		"memdebug",
		"detect",
		"devices",
		"oss",
		"cards",
		"timers",
		"synth",
		"pcm",
		"seq",
		शून्य
	पूर्ण;
	स्थिर अक्षर * स्थिर *xstr = reserved;

	जबतक (*xstr) अणु
		अगर (!म_भेद(*xstr, str))
			वापस 0;
		xstr++;
	पूर्ण
	अगर (!म_भेदन(str, "card", 4))
		वापस 0;
	वापस 1;
पूर्ण

अटल DEFINE_MUTEX(info_mutex);

काष्ठा snd_info_निजी_data अणु
	काष्ठा snd_info_buffer *rbuffer;
	काष्ठा snd_info_buffer *wbuffer;
	काष्ठा snd_info_entry *entry;
	व्योम *file_निजी_data;
पूर्ण;

अटल पूर्णांक snd_info_version_init(व्योम);
अटल व्योम snd_info_disconnect(काष्ठा snd_info_entry *entry);

/*

 */

अटल काष्ठा snd_info_entry *snd_proc_root;
काष्ठा snd_info_entry *snd_seq_root;
EXPORT_SYMBOL(snd_seq_root);

#अगर_घोषित CONFIG_SND_OSSEMUL
काष्ठा snd_info_entry *snd_oss_root;
#पूर्ण_अगर

अटल पूर्णांक alloc_info_निजी(काष्ठा snd_info_entry *entry,
			      काष्ठा snd_info_निजी_data **ret)
अणु
	काष्ठा snd_info_निजी_data *data;

	अगर (!entry || !entry->p)
		वापस -ENODEV;
	अगर (!try_module_get(entry->module))
		वापस -EFAULT;
	data = kzalloc(माप(*data), GFP_KERNEL);
	अगर (!data) अणु
		module_put(entry->module);
		वापस -ENOMEM;
	पूर्ण
	data->entry = entry;
	*ret = data;
	वापस 0;
पूर्ण

अटल bool valid_pos(loff_t pos, माप_प्रकार count)
अणु
	अगर (pos < 0 || (दीर्घ) pos != pos || (sमाप_प्रकार) count < 0)
		वापस false;
	अगर ((अचिन्हित दीर्घ) pos + (अचिन्हित दीर्घ) count < (अचिन्हित दीर्घ) pos)
		वापस false;
	वापस true;
पूर्ण

/*
 * file ops क्रम binary proc files
 */
अटल loff_t snd_info_entry_llseek(काष्ठा file *file, loff_t offset, पूर्णांक orig)
अणु
	काष्ठा snd_info_निजी_data *data;
	काष्ठा snd_info_entry *entry;
	loff_t ret = -EINVAL, size;

	data = file->निजी_data;
	entry = data->entry;
	mutex_lock(&entry->access);
	अगर (entry->c.ops->llseek) अणु
		offset = entry->c.ops->llseek(entry,
					      data->file_निजी_data,
					      file, offset, orig);
		जाओ out;
	पूर्ण

	size = entry->size;
	चयन (orig) अणु
	हाल शुरू_से:
		अवरोध;
	हाल प्रस्तुत_से:
		offset += file->f_pos;
		अवरोध;
	हाल अंत_से:
		अगर (!size)
			जाओ out;
		offset += size;
		अवरोध;
	शेष:
		जाओ out;
	पूर्ण
	अगर (offset < 0)
		जाओ out;
	अगर (size && offset > size)
		offset = size;
	file->f_pos = offset;
	ret = offset;
 out:
	mutex_unlock(&entry->access);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार snd_info_entry_पढ़ो(काष्ठा file *file, अक्षर __user *buffer,
				   माप_प्रकार count, loff_t * offset)
अणु
	काष्ठा snd_info_निजी_data *data = file->निजी_data;
	काष्ठा snd_info_entry *entry = data->entry;
	माप_प्रकार size;
	loff_t pos;

	pos = *offset;
	अगर (!valid_pos(pos, count))
		वापस -EIO;
	अगर (pos >= entry->size)
		वापस 0;
	size = entry->size - pos;
	size = min(count, size);
	size = entry->c.ops->पढ़ो(entry, data->file_निजी_data,
				  file, buffer, size, pos);
	अगर ((sमाप_प्रकार) size > 0)
		*offset = pos + size;
	वापस size;
पूर्ण

अटल sमाप_प्रकार snd_info_entry_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buffer,
				    माप_प्रकार count, loff_t * offset)
अणु
	काष्ठा snd_info_निजी_data *data = file->निजी_data;
	काष्ठा snd_info_entry *entry = data->entry;
	sमाप_प्रकार size = 0;
	loff_t pos;

	pos = *offset;
	अगर (!valid_pos(pos, count))
		वापस -EIO;
	अगर (count > 0) अणु
		माप_प्रकार maxsize = entry->size - pos;
		count = min(count, maxsize);
		size = entry->c.ops->ग_लिखो(entry, data->file_निजी_data,
					   file, buffer, count, pos);
	पूर्ण
	अगर (size > 0)
		*offset = pos + size;
	वापस size;
पूर्ण

अटल __poll_t snd_info_entry_poll(काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा snd_info_निजी_data *data = file->निजी_data;
	काष्ठा snd_info_entry *entry = data->entry;
	__poll_t mask = 0;

	अगर (entry->c.ops->poll)
		वापस entry->c.ops->poll(entry,
					  data->file_निजी_data,
					  file, रुको);
	अगर (entry->c.ops->पढ़ो)
		mask |= EPOLLIN | EPOLLRDNORM;
	अगर (entry->c.ops->ग_लिखो)
		mask |= EPOLLOUT | EPOLLWRNORM;
	वापस mask;
पूर्ण

अटल दीर्घ snd_info_entry_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
				अचिन्हित दीर्घ arg)
अणु
	काष्ठा snd_info_निजी_data *data = file->निजी_data;
	काष्ठा snd_info_entry *entry = data->entry;

	अगर (!entry->c.ops->ioctl)
		वापस -ENOTTY;
	वापस entry->c.ops->ioctl(entry, data->file_निजी_data,
				   file, cmd, arg);
पूर्ण

अटल पूर्णांक snd_info_entry_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा snd_info_निजी_data *data;
	काष्ठा snd_info_entry *entry;

	data = file->निजी_data;
	अगर (data == शून्य)
		वापस 0;
	entry = data->entry;
	अगर (!entry->c.ops->mmap)
		वापस -ENXIO;
	वापस entry->c.ops->mmap(entry, data->file_निजी_data,
				  inode, file, vma);
पूर्ण

अटल पूर्णांक snd_info_entry_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा snd_info_entry *entry = PDE_DATA(inode);
	काष्ठा snd_info_निजी_data *data;
	पूर्णांक mode, err;

	mutex_lock(&info_mutex);
	err = alloc_info_निजी(entry, &data);
	अगर (err < 0)
		जाओ unlock;

	mode = file->f_flags & O_ACCMODE;
	अगर (((mode == O_RDONLY || mode == O_RDWR) && !entry->c.ops->पढ़ो) ||
	    ((mode == O_WRONLY || mode == O_RDWR) && !entry->c.ops->ग_लिखो)) अणु
		err = -ENODEV;
		जाओ error;
	पूर्ण

	अगर (entry->c.ops->खोलो) अणु
		err = entry->c.ops->खोलो(entry, mode, &data->file_निजी_data);
		अगर (err < 0)
			जाओ error;
	पूर्ण

	file->निजी_data = data;
	mutex_unlock(&info_mutex);
	वापस 0;

 error:
	kमुक्त(data);
	module_put(entry->module);
 unlock:
	mutex_unlock(&info_mutex);
	वापस err;
पूर्ण

अटल पूर्णांक snd_info_entry_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा snd_info_निजी_data *data = file->निजी_data;
	काष्ठा snd_info_entry *entry = data->entry;

	अगर (entry->c.ops->release)
		entry->c.ops->release(entry, file->f_flags & O_ACCMODE,
				      data->file_निजी_data);
	module_put(entry->module);
	kमुक्त(data);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा proc_ops snd_info_entry_operations =
अणु
	.proc_lseek	= snd_info_entry_llseek,
	.proc_पढ़ो	= snd_info_entry_पढ़ो,
	.proc_ग_लिखो	= snd_info_entry_ग_लिखो,
	.proc_poll	= snd_info_entry_poll,
	.proc_ioctl	= snd_info_entry_ioctl,
	.proc_mmap	= snd_info_entry_mmap,
	.proc_खोलो	= snd_info_entry_खोलो,
	.proc_release	= snd_info_entry_release,
पूर्ण;

/*
 * file ops क्रम text proc files
 */
अटल sमाप_प्रकार snd_info_text_entry_ग_लिखो(काष्ठा file *file,
					 स्थिर अक्षर __user *buffer,
					 माप_प्रकार count, loff_t *offset)
अणु
	काष्ठा seq_file *m = file->निजी_data;
	काष्ठा snd_info_निजी_data *data = m->निजी;
	काष्ठा snd_info_entry *entry = data->entry;
	काष्ठा snd_info_buffer *buf;
	loff_t pos;
	माप_प्रकार next;
	पूर्णांक err = 0;

	अगर (!entry->c.text.ग_लिखो)
		वापस -EIO;
	pos = *offset;
	अगर (!valid_pos(pos, count))
		वापस -EIO;
	next = pos + count;
	/* करोn't handle too large text inमाला_दो */
	अगर (next > 16 * 1024)
		वापस -EIO;
	mutex_lock(&entry->access);
	buf = data->wbuffer;
	अगर (!buf) अणु
		data->wbuffer = buf = kzalloc(माप(*buf), GFP_KERNEL);
		अगर (!buf) अणु
			err = -ENOMEM;
			जाओ error;
		पूर्ण
	पूर्ण
	अगर (next > buf->len) अणु
		अक्षर *nbuf = kvzalloc(PAGE_ALIGN(next), GFP_KERNEL);
		अगर (!nbuf) अणु
			err = -ENOMEM;
			जाओ error;
		पूर्ण
		kvमुक्त(buf->buffer);
		buf->buffer = nbuf;
		buf->len = PAGE_ALIGN(next);
	पूर्ण
	अगर (copy_from_user(buf->buffer + pos, buffer, count)) अणु
		err = -EFAULT;
		जाओ error;
	पूर्ण
	buf->size = next;
 error:
	mutex_unlock(&entry->access);
	अगर (err < 0)
		वापस err;
	*offset = next;
	वापस count;
पूर्ण

अटल पूर्णांक snd_info_seq_show(काष्ठा seq_file *seq, व्योम *p)
अणु
	काष्ठा snd_info_निजी_data *data = seq->निजी;
	काष्ठा snd_info_entry *entry = data->entry;

	अगर (!entry->c.text.पढ़ो) अणु
		वापस -EIO;
	पूर्ण अन्यथा अणु
		data->rbuffer->buffer = (अक्षर *)seq; /* XXX hack! */
		entry->c.text.पढ़ो(entry, data->rbuffer);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_info_text_entry_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा snd_info_entry *entry = PDE_DATA(inode);
	काष्ठा snd_info_निजी_data *data;
	पूर्णांक err;

	mutex_lock(&info_mutex);
	err = alloc_info_निजी(entry, &data);
	अगर (err < 0)
		जाओ unlock;

	data->rbuffer = kzalloc(माप(*data->rbuffer), GFP_KERNEL);
	अगर (!data->rbuffer) अणु
		err = -ENOMEM;
		जाओ error;
	पूर्ण
	अगर (entry->size)
		err = single_खोलो_size(file, snd_info_seq_show, data,
				       entry->size);
	अन्यथा
		err = single_खोलो(file, snd_info_seq_show, data);
	अगर (err < 0)
		जाओ error;
	mutex_unlock(&info_mutex);
	वापस 0;

 error:
	kमुक्त(data->rbuffer);
	kमुक्त(data);
	module_put(entry->module);
 unlock:
	mutex_unlock(&info_mutex);
	वापस err;
पूर्ण

अटल पूर्णांक snd_info_text_entry_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा seq_file *m = file->निजी_data;
	काष्ठा snd_info_निजी_data *data = m->निजी;
	काष्ठा snd_info_entry *entry = data->entry;

	अगर (data->wbuffer && entry->c.text.ग_लिखो)
		entry->c.text.ग_लिखो(entry, data->wbuffer);

	single_release(inode, file);
	kमुक्त(data->rbuffer);
	अगर (data->wbuffer) अणु
		kvमुक्त(data->wbuffer->buffer);
		kमुक्त(data->wbuffer);
	पूर्ण

	module_put(entry->module);
	kमुक्त(data);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा proc_ops snd_info_text_entry_ops =
अणु
	.proc_खोलो	= snd_info_text_entry_खोलो,
	.proc_release	= snd_info_text_entry_release,
	.proc_ग_लिखो	= snd_info_text_entry_ग_लिखो,
	.proc_lseek	= seq_lseek,
	.proc_पढ़ो	= seq_पढ़ो,
पूर्ण;

अटल काष्ठा snd_info_entry *create_subdir(काष्ठा module *mod,
					    स्थिर अक्षर *name)
अणु
	काष्ठा snd_info_entry *entry;

	entry = snd_info_create_module_entry(mod, name, शून्य);
	अगर (!entry)
		वापस शून्य;
	entry->mode = S_IFसूची | 0555;
	अगर (snd_info_रेजिस्टर(entry) < 0) अणु
		snd_info_मुक्त_entry(entry);
		वापस शून्य;
	पूर्ण
	वापस entry;
पूर्ण

अटल काष्ठा snd_info_entry *
snd_info_create_entry(स्थिर अक्षर *name, काष्ठा snd_info_entry *parent,
		      काष्ठा module *module);

पूर्णांक __init snd_info_init(व्योम)
अणु
	snd_proc_root = snd_info_create_entry("asound", शून्य, THIS_MODULE);
	अगर (!snd_proc_root)
		वापस -ENOMEM;
	snd_proc_root->mode = S_IFसूची | 0555;
	snd_proc_root->p = proc_सूची_गढ़ो("asound", शून्य);
	अगर (!snd_proc_root->p)
		जाओ error;
#अगर_घोषित CONFIG_SND_OSSEMUL
	snd_oss_root = create_subdir(THIS_MODULE, "oss");
	अगर (!snd_oss_root)
		जाओ error;
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_SND_SEQUENCER)
	snd_seq_root = create_subdir(THIS_MODULE, "seq");
	अगर (!snd_seq_root)
		जाओ error;
#पूर्ण_अगर
	अगर (snd_info_version_init() < 0 ||
	    snd_minor_info_init() < 0 ||
	    snd_minor_info_oss_init() < 0 ||
	    snd_card_info_init() < 0 ||
	    snd_info_minor_रेजिस्टर() < 0)
		जाओ error;
	वापस 0;

 error:
	snd_info_मुक्त_entry(snd_proc_root);
	वापस -ENOMEM;
पूर्ण

पूर्णांक __निकास snd_info_करोne(व्योम)
अणु
	snd_info_मुक्त_entry(snd_proc_root);
	वापस 0;
पूर्ण

अटल व्योम snd_card_id_पढ़ो(काष्ठा snd_info_entry *entry,
			     काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा snd_card *card = entry->निजी_data;

	snd_iम_लिखो(buffer, "%s\n", card->id);
पूर्ण

/*
 * create a card proc file
 * called from init.c
 */
पूर्णांक snd_info_card_create(काष्ठा snd_card *card)
अणु
	अक्षर str[8];
	काष्ठा snd_info_entry *entry;

	अगर (snd_BUG_ON(!card))
		वापस -ENXIO;

	प्र_लिखो(str, "card%i", card->number);
	entry = create_subdir(card->module, str);
	अगर (!entry)
		वापस -ENOMEM;
	card->proc_root = entry;

	वापस snd_card_ro_proc_new(card, "id", card, snd_card_id_पढ़ो);
पूर्ण

/*
 * रेजिस्टर the card proc file
 * called from init.c
 * can be called multiple बार क्रम reinitialization
 */
पूर्णांक snd_info_card_रेजिस्टर(काष्ठा snd_card *card)
अणु
	काष्ठा proc_dir_entry *p;
	पूर्णांक err;

	अगर (snd_BUG_ON(!card))
		वापस -ENXIO;

	err = snd_info_रेजिस्टर(card->proc_root);
	अगर (err < 0)
		वापस err;

	अगर (!म_भेद(card->id, card->proc_root->name))
		वापस 0;

	अगर (card->proc_root_link)
		वापस 0;
	p = proc_symlink(card->id, snd_proc_root->p, card->proc_root->name);
	अगर (!p)
		वापस -ENOMEM;
	card->proc_root_link = p;
	वापस 0;
पूर्ण

/*
 * called on card->id change
 */
व्योम snd_info_card_id_change(काष्ठा snd_card *card)
अणु
	mutex_lock(&info_mutex);
	अगर (card->proc_root_link) अणु
		proc_हटाओ(card->proc_root_link);
		card->proc_root_link = शून्य;
	पूर्ण
	अगर (म_भेद(card->id, card->proc_root->name))
		card->proc_root_link = proc_symlink(card->id,
						    snd_proc_root->p,
						    card->proc_root->name);
	mutex_unlock(&info_mutex);
पूर्ण

/*
 * de-रेजिस्टर the card proc file
 * called from init.c
 */
व्योम snd_info_card_disconnect(काष्ठा snd_card *card)
अणु
	अगर (!card)
		वापस;
	mutex_lock(&info_mutex);
	proc_हटाओ(card->proc_root_link);
	card->proc_root_link = शून्य;
	अगर (card->proc_root)
		snd_info_disconnect(card->proc_root);
	mutex_unlock(&info_mutex);
पूर्ण

/*
 * release the card proc file resources
 * called from init.c
 */
पूर्णांक snd_info_card_मुक्त(काष्ठा snd_card *card)
अणु
	अगर (!card)
		वापस 0;
	snd_info_मुक्त_entry(card->proc_root);
	card->proc_root = शून्य;
	वापस 0;
पूर्ण


/**
 * snd_info_get_line - पढ़ो one line from the procfs buffer
 * @buffer: the procfs buffer
 * @line: the buffer to store
 * @len: the max. buffer size
 *
 * Reads one line from the buffer and stores the string.
 *
 * Return: Zero अगर successful, or 1 अगर error or खातापूर्ण.
 */
पूर्णांक snd_info_get_line(काष्ठा snd_info_buffer *buffer, अक्षर *line, पूर्णांक len)
अणु
	पूर्णांक c;

	अगर (snd_BUG_ON(!buffer))
		वापस 1;
	अगर (!buffer->buffer)
		वापस 1;
	अगर (len <= 0 || buffer->stop || buffer->error)
		वापस 1;
	जबतक (!buffer->stop) अणु
		c = buffer->buffer[buffer->curr++];
		अगर (buffer->curr >= buffer->size)
			buffer->stop = 1;
		अगर (c == '\n')
			अवरोध;
		अगर (len > 1) अणु
			len--;
			*line++ = c;
		पूर्ण
	पूर्ण
	*line = '\0';
	वापस 0;
पूर्ण
EXPORT_SYMBOL(snd_info_get_line);

/**
 * snd_info_get_str - parse a string token
 * @dest: the buffer to store the string token
 * @src: the original string
 * @len: the max. length of token - 1
 *
 * Parses the original string and copy a token to the given
 * string buffer.
 *
 * Return: The updated poपूर्णांकer of the original string so that
 * it can be used क्रम the next call.
 */
स्थिर अक्षर *snd_info_get_str(अक्षर *dest, स्थिर अक्षर *src, पूर्णांक len)
अणु
	पूर्णांक c;

	जबतक (*src == ' ' || *src == '\t')
		src++;
	अगर (*src == '"' || *src == '\'') अणु
		c = *src++;
		जबतक (--len > 0 && *src && *src != c) अणु
			*dest++ = *src++;
		पूर्ण
		अगर (*src == c)
			src++;
	पूर्ण अन्यथा अणु
		जबतक (--len > 0 && *src && *src != ' ' && *src != '\t') अणु
			*dest++ = *src++;
		पूर्ण
	पूर्ण
	*dest = 0;
	जबतक (*src == ' ' || *src == '\t')
		src++;
	वापस src;
पूर्ण
EXPORT_SYMBOL(snd_info_get_str);

/*
 * snd_info_create_entry - create an info entry
 * @name: the proc file name
 * @parent: the parent directory
 *
 * Creates an info entry with the given file name and initializes as
 * the शेष state.
 *
 * Usually called from other functions such as
 * snd_info_create_card_entry().
 *
 * Return: The poपूर्णांकer of the new instance, or %शून्य on failure.
 */
अटल काष्ठा snd_info_entry *
snd_info_create_entry(स्थिर अक्षर *name, काष्ठा snd_info_entry *parent,
		      काष्ठा module *module)
अणु
	काष्ठा snd_info_entry *entry;
	entry = kzalloc(माप(*entry), GFP_KERNEL);
	अगर (entry == शून्य)
		वापस शून्य;
	entry->name = kstrdup(name, GFP_KERNEL);
	अगर (entry->name == शून्य) अणु
		kमुक्त(entry);
		वापस शून्य;
	पूर्ण
	entry->mode = S_IFREG | 0444;
	entry->content = SNDRV_INFO_CONTENT_TEXT;
	mutex_init(&entry->access);
	INIT_LIST_HEAD(&entry->children);
	INIT_LIST_HEAD(&entry->list);
	entry->parent = parent;
	entry->module = module;
	अगर (parent) अणु
		mutex_lock(&parent->access);
		list_add_tail(&entry->list, &parent->children);
		mutex_unlock(&parent->access);
	पूर्ण
	वापस entry;
पूर्ण

/**
 * snd_info_create_module_entry - create an info entry क्रम the given module
 * @module: the module poपूर्णांकer
 * @name: the file name
 * @parent: the parent directory
 *
 * Creates a new info entry and assigns it to the given module.
 *
 * Return: The poपूर्णांकer of the new instance, or %शून्य on failure.
 */
काष्ठा snd_info_entry *snd_info_create_module_entry(काष्ठा module * module,
					       स्थिर अक्षर *name,
					       काष्ठा snd_info_entry *parent)
अणु
	अगर (!parent)
		parent = snd_proc_root;
	वापस snd_info_create_entry(name, parent, module);
पूर्ण
EXPORT_SYMBOL(snd_info_create_module_entry);

/**
 * snd_info_create_card_entry - create an info entry क्रम the given card
 * @card: the card instance
 * @name: the file name
 * @parent: the parent directory
 *
 * Creates a new info entry and assigns it to the given card.
 *
 * Return: The poपूर्णांकer of the new instance, or %शून्य on failure.
 */
काष्ठा snd_info_entry *snd_info_create_card_entry(काष्ठा snd_card *card,
					     स्थिर अक्षर *name,
					     काष्ठा snd_info_entry * parent)
अणु
	अगर (!parent)
		parent = card->proc_root;
	वापस snd_info_create_entry(name, parent, card->module);
पूर्ण
EXPORT_SYMBOL(snd_info_create_card_entry);

अटल व्योम snd_info_disconnect(काष्ठा snd_info_entry *entry)
अणु
	काष्ठा snd_info_entry *p;

	अगर (!entry->p)
		वापस;
	list_क्रम_each_entry(p, &entry->children, list)
		snd_info_disconnect(p);
	proc_हटाओ(entry->p);
	entry->p = शून्य;
पूर्ण

/**
 * snd_info_मुक्त_entry - release the info entry
 * @entry: the info entry
 *
 * Releases the info entry.
 */
व्योम snd_info_मुक्त_entry(काष्ठा snd_info_entry * entry)
अणु
	काष्ठा snd_info_entry *p, *n;

	अगर (!entry)
		वापस;
	अगर (entry->p) अणु
		mutex_lock(&info_mutex);
		snd_info_disconnect(entry);
		mutex_unlock(&info_mutex);
	पूर्ण

	/* मुक्त all children at first */
	list_क्रम_each_entry_safe(p, n, &entry->children, list)
		snd_info_मुक्त_entry(p);

	p = entry->parent;
	अगर (p) अणु
		mutex_lock(&p->access);
		list_del(&entry->list);
		mutex_unlock(&p->access);
	पूर्ण
	kमुक्त(entry->name);
	अगर (entry->निजी_मुक्त)
		entry->निजी_मुक्त(entry);
	kमुक्त(entry);
पूर्ण
EXPORT_SYMBOL(snd_info_मुक्त_entry);

अटल पूर्णांक __snd_info_रेजिस्टर(काष्ठा snd_info_entry *entry)
अणु
	काष्ठा proc_dir_entry *root, *p = शून्य;

	अगर (snd_BUG_ON(!entry))
		वापस -ENXIO;
	root = entry->parent == शून्य ? snd_proc_root->p : entry->parent->p;
	mutex_lock(&info_mutex);
	अगर (entry->p || !root)
		जाओ unlock;
	अगर (S_ISसूची(entry->mode)) अणु
		p = proc_सूची_गढ़ो_mode(entry->name, entry->mode, root);
		अगर (!p) अणु
			mutex_unlock(&info_mutex);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण अन्यथा अणु
		स्थिर काष्ठा proc_ops *ops;
		अगर (entry->content == SNDRV_INFO_CONTENT_DATA)
			ops = &snd_info_entry_operations;
		अन्यथा
			ops = &snd_info_text_entry_ops;
		p = proc_create_data(entry->name, entry->mode, root,
				     ops, entry);
		अगर (!p) अणु
			mutex_unlock(&info_mutex);
			वापस -ENOMEM;
		पूर्ण
		proc_set_size(p, entry->size);
	पूर्ण
	entry->p = p;
 unlock:
	mutex_unlock(&info_mutex);
	वापस 0;
पूर्ण

/**
 * snd_info_रेजिस्टर - रेजिस्टर the info entry
 * @entry: the info entry
 *
 * Registers the proc info entry.
 * The all children entries are रेजिस्टरed recursively.
 *
 * Return: Zero अगर successful, or a negative error code on failure.
 */
पूर्णांक snd_info_रेजिस्टर(काष्ठा snd_info_entry *entry)
अणु
	काष्ठा snd_info_entry *p;
	पूर्णांक err;

	अगर (!entry->p) अणु
		err = __snd_info_रेजिस्टर(entry);
		अगर (err < 0)
			वापस err;
	पूर्ण

	list_क्रम_each_entry(p, &entry->children, list) अणु
		err = snd_info_रेजिस्टर(p);
		अगर (err < 0)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(snd_info_रेजिस्टर);

/**
 * snd_card_rw_proc_new - Create a पढ़ो/ग_लिखो text proc file entry क्रम the card
 * @card: the card instance
 * @name: the file name
 * @निजी_data: the arbitrary निजी data
 * @पढ़ो: the पढ़ो callback
 * @ग_लिखो: the ग_लिखो callback, शून्य क्रम पढ़ो-only
 *
 * This proc file entry will be रेजिस्टरed via snd_card_रेजिस्टर() call, and
 * it will be हटाओd स्वतःmatically at the card removal, too.
 */
पूर्णांक snd_card_rw_proc_new(काष्ठा snd_card *card, स्थिर अक्षर *name,
			 व्योम *निजी_data,
			 व्योम (*पढ़ो)(काष्ठा snd_info_entry *,
				      काष्ठा snd_info_buffer *),
			 व्योम (*ग_लिखो)(काष्ठा snd_info_entry *entry,
				       काष्ठा snd_info_buffer *buffer))
अणु
	काष्ठा snd_info_entry *entry;

	entry = snd_info_create_card_entry(card, name, card->proc_root);
	अगर (!entry)
		वापस -ENOMEM;
	snd_info_set_text_ops(entry, निजी_data, पढ़ो);
	अगर (ग_लिखो) अणु
		entry->mode |= 0200;
		entry->c.text.ग_लिखो = ग_लिखो;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_card_rw_proc_new);

/*

 */

अटल व्योम snd_info_version_पढ़ो(काष्ठा snd_info_entry *entry, काष्ठा snd_info_buffer *buffer)
अणु
	snd_iम_लिखो(buffer,
		    "Advanced Linux Sound Architecture Driver Version k%s.\n",
		    init_utsname()->release);
पूर्ण

अटल पूर्णांक __init snd_info_version_init(व्योम)
अणु
	काष्ठा snd_info_entry *entry;

	entry = snd_info_create_module_entry(THIS_MODULE, "version", शून्य);
	अगर (entry == शून्य)
		वापस -ENOMEM;
	entry->c.text.पढ़ो = snd_info_version_पढ़ो;
	वापस snd_info_रेजिस्टर(entry); /* मुक्तd in error path */
पूर्ण
