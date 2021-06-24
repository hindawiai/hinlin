<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Functions क्रम the OPL4 proc file
 * Copyright (c) 2003 by Clemens Ladisch <clemens@ladisch.de>
 */

#समावेश "opl4_local.h"
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/export.h>
#समावेश <sound/info.h>

अटल पूर्णांक snd_opl4_mem_proc_खोलो(काष्ठा snd_info_entry *entry,
				  अचिन्हित लघु mode, व्योम **file_निजी_data)
अणु
	काष्ठा snd_opl4 *opl4 = entry->निजी_data;

	mutex_lock(&opl4->access_mutex);
	अगर (opl4->memory_access) अणु
		mutex_unlock(&opl4->access_mutex);
		वापस -EBUSY;
	पूर्ण
	opl4->memory_access++;
	mutex_unlock(&opl4->access_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_opl4_mem_proc_release(काष्ठा snd_info_entry *entry,
				     अचिन्हित लघु mode, व्योम *file_निजी_data)
अणु
	काष्ठा snd_opl4 *opl4 = entry->निजी_data;

	mutex_lock(&opl4->access_mutex);
	opl4->memory_access--;
	mutex_unlock(&opl4->access_mutex);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार snd_opl4_mem_proc_पढ़ो(काष्ठा snd_info_entry *entry,
				      व्योम *file_निजी_data,
				      काष्ठा file *file, अक्षर __user *_buf,
				      माप_प्रकार count, loff_t pos)
अणु
	काष्ठा snd_opl4 *opl4 = entry->निजी_data;
	अक्षर* buf;

	buf = vदो_स्मृति(count);
	अगर (!buf)
		वापस -ENOMEM;
	snd_opl4_पढ़ो_memory(opl4, buf, pos, count);
	अगर (copy_to_user(_buf, buf, count)) अणु
		vमुक्त(buf);
		वापस -EFAULT;
	पूर्ण
	vमुक्त(buf);
	वापस count;
पूर्ण

अटल sमाप_प्रकार snd_opl4_mem_proc_ग_लिखो(काष्ठा snd_info_entry *entry,
				       व्योम *file_निजी_data,
				       काष्ठा file *file,
				       स्थिर अक्षर __user *_buf,
				       माप_प्रकार count, loff_t pos)
अणु
	काष्ठा snd_opl4 *opl4 = entry->निजी_data;
	अक्षर *buf;

	buf = vदो_स्मृति(count);
	अगर (!buf)
		वापस -ENOMEM;
	अगर (copy_from_user(buf, _buf, count)) अणु
		vमुक्त(buf);
		वापस -EFAULT;
	पूर्ण
	snd_opl4_ग_लिखो_memory(opl4, buf, pos, count);
	vमुक्त(buf);
	वापस count;
पूर्ण

अटल स्थिर काष्ठा snd_info_entry_ops snd_opl4_mem_proc_ops = अणु
	.खोलो = snd_opl4_mem_proc_खोलो,
	.release = snd_opl4_mem_proc_release,
	.पढ़ो = snd_opl4_mem_proc_पढ़ो,
	.ग_लिखो = snd_opl4_mem_proc_ग_लिखो,
पूर्ण;

पूर्णांक snd_opl4_create_proc(काष्ठा snd_opl4 *opl4)
अणु
	काष्ठा snd_info_entry *entry;

	entry = snd_info_create_card_entry(opl4->card, "opl4-mem", opl4->card->proc_root);
	अगर (entry) अणु
		अगर (opl4->hardware < OPL3_HW_OPL4_ML) अणु
			/* OPL4 can access 4 MB बाह्यal ROM/SRAM */
			entry->mode |= 0200;
			entry->size = 4 * 1024 * 1024;
		पूर्ण अन्यथा अणु
			/* OPL4-ML has 1 MB पूर्णांकernal ROM */
			entry->size = 1 * 1024 * 1024;
		पूर्ण
		entry->content = SNDRV_INFO_CONTENT_DATA;
		entry->c.ops = &snd_opl4_mem_proc_ops;
		entry->module = THIS_MODULE;
		entry->निजी_data = opl4;
	पूर्ण
	opl4->proc_entry = entry;
	वापस 0;
पूर्ण

व्योम snd_opl4_मुक्त_proc(काष्ठा snd_opl4 *opl4)
अणु
	snd_info_मुक्त_entry(opl4->proc_entry);
पूर्ण
