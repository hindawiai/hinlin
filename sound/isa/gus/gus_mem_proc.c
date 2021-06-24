<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 *  GUS's memory access via proc fileप्रणाली
 */

#समावेश <linux/slab.h>
#समावेश <sound/core.h>
#समावेश <sound/gus.h>
#समावेश <sound/info.h>

काष्ठा gus_proc_निजी अणु
	पूर्णांक rom;		/* data are in ROM */
	अचिन्हित पूर्णांक address;
	अचिन्हित पूर्णांक size;
	काष्ठा snd_gus_card * gus;
पूर्ण;

अटल sमाप_प्रकार snd_gf1_mem_proc_dump(काष्ठा snd_info_entry *entry,
				     व्योम *file_निजी_data,
				     काष्ठा file *file, अक्षर __user *buf,
				     माप_प्रकार count, loff_t pos)
अणु
	काष्ठा gus_proc_निजी *priv = entry->निजी_data;
	काष्ठा snd_gus_card *gus = priv->gus;
	पूर्णांक err;

	err = snd_gus_dram_पढ़ो(gus, buf, pos, count, priv->rom);
	अगर (err < 0)
		वापस err;
	वापस count;
पूर्ण			

अटल व्योम snd_gf1_mem_proc_मुक्त(काष्ठा snd_info_entry *entry)
अणु
	काष्ठा gus_proc_निजी *priv = entry->निजी_data;
	kमुक्त(priv);
पूर्ण

अटल स्थिर काष्ठा snd_info_entry_ops snd_gf1_mem_proc_ops = अणु
	.पढ़ो = snd_gf1_mem_proc_dump,
पूर्ण;

पूर्णांक snd_gf1_mem_proc_init(काष्ठा snd_gus_card * gus)
अणु
	पूर्णांक idx;
	अक्षर name[16];
	काष्ठा gus_proc_निजी *priv;
	काष्ठा snd_info_entry *entry;

	क्रम (idx = 0; idx < 4; idx++) अणु
		अगर (gus->gf1.mem_alloc.banks_8[idx].size > 0) अणु
			priv = kzalloc(माप(*priv), GFP_KERNEL);
			अगर (priv == शून्य)
				वापस -ENOMEM;
			priv->gus = gus;
			प्र_लिखो(name, "gus-ram-%i", idx);
			अगर (! snd_card_proc_new(gus->card, name, &entry)) अणु
				entry->content = SNDRV_INFO_CONTENT_DATA;
				entry->निजी_data = priv;
				entry->निजी_मुक्त = snd_gf1_mem_proc_मुक्त;
				entry->c.ops = &snd_gf1_mem_proc_ops;
				priv->address = gus->gf1.mem_alloc.banks_8[idx].address;
				priv->size = entry->size = gus->gf1.mem_alloc.banks_8[idx].size;
			पूर्ण
		पूर्ण
	पूर्ण
	क्रम (idx = 0; idx < 4; idx++) अणु
		अगर (gus->gf1.rom_present & (1 << idx)) अणु
			priv = kzalloc(माप(*priv), GFP_KERNEL);
			अगर (priv == शून्य)
				वापस -ENOMEM;
			priv->rom = 1;
			priv->gus = gus;
			प्र_लिखो(name, "gus-rom-%i", idx);
			अगर (! snd_card_proc_new(gus->card, name, &entry)) अणु
				entry->content = SNDRV_INFO_CONTENT_DATA;
				entry->निजी_data = priv;
				entry->निजी_मुक्त = snd_gf1_mem_proc_मुक्त;
				entry->c.ops = &snd_gf1_mem_proc_ops;
				priv->address = idx * 4096 * 1024;
				priv->size = entry->size = gus->gf1.rom_memory;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण
