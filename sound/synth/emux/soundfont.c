<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Soundfont generic routines.
 *	It is पूर्णांकended that these should be used by any driver that is willing
 *	to accept soundfont patches.
 *
 *  Copyright (C) 1999 Steve Ratclअगरfe
 *  Copyright (c) 1999-2000 Takashi Iwai <tiwai@suse.de>
 */
/*
 * Deal with पढ़ोing in of a soundfont.  Code follows the OSS way
 * of करोing things so that the old sfxload utility can be used.
 * Everything may change when there is an alsa way of करोing things.
 */
#समावेश <linux/uaccess.h>
#समावेश <linux/slab.h>
#समावेश <linux/export.h>
#समावेश <sound/core.h>
#समावेश <sound/soundfont.h>
#समावेश <sound/seq_oss_legacy.h>

/* Prototypes क्रम अटल functions */

अटल पूर्णांक खोलो_patch(काष्ठा snd_sf_list *sflist, स्थिर अक्षर __user *data,
		      पूर्णांक count, पूर्णांक client);
अटल काष्ठा snd_soundfont *newsf(काष्ठा snd_sf_list *sflist, पूर्णांक type, अक्षर *name);
अटल पूर्णांक is_identical_font(काष्ठा snd_soundfont *sf, पूर्णांक type, अचिन्हित अक्षर *name);
अटल पूर्णांक बंद_patch(काष्ठा snd_sf_list *sflist);
अटल पूर्णांक probe_data(काष्ठा snd_sf_list *sflist, पूर्णांक sample_id);
अटल व्योम set_zone_counter(काष्ठा snd_sf_list *sflist,
			     काष्ठा snd_soundfont *sf, काष्ठा snd_sf_zone *zp);
अटल काष्ठा snd_sf_zone *sf_zone_new(काष्ठा snd_sf_list *sflist,
				       काष्ठा snd_soundfont *sf);
अटल व्योम set_sample_counter(काष्ठा snd_sf_list *sflist,
			       काष्ठा snd_soundfont *sf, काष्ठा snd_sf_sample *sp);
अटल काष्ठा snd_sf_sample *sf_sample_new(काष्ठा snd_sf_list *sflist,
					   काष्ठा snd_soundfont *sf);
अटल व्योम sf_sample_delete(काष्ठा snd_sf_list *sflist,
			     काष्ठा snd_soundfont *sf, काष्ठा snd_sf_sample *sp);
अटल पूर्णांक load_map(काष्ठा snd_sf_list *sflist, स्थिर व्योम __user *data, पूर्णांक count);
अटल पूर्णांक load_info(काष्ठा snd_sf_list *sflist, स्थिर व्योम __user *data, दीर्घ count);
अटल पूर्णांक हटाओ_info(काष्ठा snd_sf_list *sflist, काष्ठा snd_soundfont *sf,
		       पूर्णांक bank, पूर्णांक instr);
अटल व्योम init_voice_info(काष्ठा soundfont_voice_info *avp);
अटल व्योम init_voice_parm(काष्ठा soundfont_voice_parm *pp);
अटल काष्ठा snd_sf_sample *set_sample(काष्ठा snd_soundfont *sf,
					काष्ठा soundfont_voice_info *avp);
अटल काष्ठा snd_sf_sample *find_sample(काष्ठा snd_soundfont *sf, पूर्णांक sample_id);
अटल पूर्णांक load_data(काष्ठा snd_sf_list *sflist, स्थिर व्योम __user *data, दीर्घ count);
अटल व्योम rebuild_presets(काष्ठा snd_sf_list *sflist);
अटल व्योम add_preset(काष्ठा snd_sf_list *sflist, काष्ठा snd_sf_zone *cur);
अटल व्योम delete_preset(काष्ठा snd_sf_list *sflist, काष्ठा snd_sf_zone *zp);
अटल काष्ठा snd_sf_zone *search_first_zone(काष्ठा snd_sf_list *sflist,
					     पूर्णांक bank, पूर्णांक preset, पूर्णांक key);
अटल पूर्णांक search_zones(काष्ठा snd_sf_list *sflist, पूर्णांक *notep, पूर्णांक vel,
			पूर्णांक preset, पूर्णांक bank, काष्ठा snd_sf_zone **table,
			पूर्णांक max_layers, पूर्णांक level);
अटल पूर्णांक get_index(पूर्णांक bank, पूर्णांक instr, पूर्णांक key);
अटल व्योम snd_sf_init(काष्ठा snd_sf_list *sflist);
अटल व्योम snd_sf_clear(काष्ठा snd_sf_list *sflist);

/*
 * lock access to sflist
 */
अटल व्योम
lock_preset(काष्ठा snd_sf_list *sflist)
अणु
	अचिन्हित दीर्घ flags;
	mutex_lock(&sflist->presets_mutex);
	spin_lock_irqsave(&sflist->lock, flags);
	sflist->presets_locked = 1;
	spin_unlock_irqrestore(&sflist->lock, flags);
पूर्ण


/*
 * हटाओ lock
 */
अटल व्योम
unlock_preset(काष्ठा snd_sf_list *sflist)
अणु
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&sflist->lock, flags);
	sflist->presets_locked = 0;
	spin_unlock_irqrestore(&sflist->lock, flags);
	mutex_unlock(&sflist->presets_mutex);
पूर्ण


/*
 * बंद the patch अगर the patch was खोलोed by this client.
 */
पूर्णांक
snd_soundfont_बंद_check(काष्ठा snd_sf_list *sflist, पूर्णांक client)
अणु
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&sflist->lock, flags);
	अगर (sflist->खोलो_client == client)  अणु
		spin_unlock_irqrestore(&sflist->lock, flags);
		वापस बंद_patch(sflist);
	पूर्ण
	spin_unlock_irqrestore(&sflist->lock, flags);
	वापस 0;
पूर्ण


/*
 * Deal with a soundfont patch.  Any driver could use these routines
 * although it was deचिन्हित क्रम the AWE64.
 *
 * The sample_ग_लिखो and callargs pararameters allow a callback पूर्णांकo
 * the actual driver to ग_लिखो sample data to the board or whatever
 * it wants to करो with it.
 */
पूर्णांक
snd_soundfont_load(काष्ठा snd_sf_list *sflist, स्थिर व्योम __user *data,
		   दीर्घ count, पूर्णांक client)
अणु
	काष्ठा soundfont_patch_info patch;
	अचिन्हित दीर्घ flags;
	पूर्णांक  rc;

	अगर (count < (दीर्घ)माप(patch)) अणु
		snd_prपूर्णांकk(KERN_ERR "patch record too small %ld\n", count);
		वापस -EINVAL;
	पूर्ण
	अगर (copy_from_user(&patch, data, माप(patch)))
		वापस -EFAULT;

	count -= माप(patch);
	data += माप(patch);

	अगर (patch.key != SNDRV_OSS_SOUNDFONT_PATCH) अणु
		snd_prपूर्णांकk(KERN_ERR "The wrong kind of patch %x\n", patch.key);
		वापस -EINVAL;
	पूर्ण
	अगर (count < patch.len) अणु
		snd_prपूर्णांकk(KERN_ERR "Patch too short %ld, need %d\n",
			   count, patch.len);
		वापस -EINVAL;
	पूर्ण
	अगर (patch.len < 0) अणु
		snd_prपूर्णांकk(KERN_ERR "poor length %d\n", patch.len);
		वापस -EINVAL;
	पूर्ण

	अगर (patch.type == SNDRV_SFNT_OPEN_PATCH) अणु
		/* grab sflist to खोलो */
		lock_preset(sflist);
		rc = खोलो_patch(sflist, data, count, client);
		unlock_preset(sflist);
		वापस rc;
	पूर्ण

	/* check अगर other client alपढ़ोy खोलोed patch */
	spin_lock_irqsave(&sflist->lock, flags);
	अगर (sflist->खोलो_client != client) अणु
		spin_unlock_irqrestore(&sflist->lock, flags);
		वापस -EBUSY;
	पूर्ण
	spin_unlock_irqrestore(&sflist->lock, flags);

	lock_preset(sflist);
	rc = -EINVAL;
	चयन (patch.type) अणु
	हाल SNDRV_SFNT_LOAD_INFO:
		rc = load_info(sflist, data, count);
		अवरोध;
	हाल SNDRV_SFNT_LOAD_DATA:
		rc = load_data(sflist, data, count);
		अवरोध;
	हाल SNDRV_SFNT_CLOSE_PATCH:
		rc = बंद_patch(sflist);
		अवरोध;
	हाल SNDRV_SFNT_REPLACE_DATA:
		/*rc = replace_data(&patch, data, count);*/
		अवरोध;
	हाल SNDRV_SFNT_MAP_PRESET:
		rc = load_map(sflist, data, count);
		अवरोध;
	हाल SNDRV_SFNT_PROBE_DATA:
		rc = probe_data(sflist, patch.optarg);
		अवरोध;
	हाल SNDRV_SFNT_REMOVE_INFO:
		/* patch must be खोलोed */
		अगर (!sflist->currsf) अणु
			snd_prपूर्णांकk(KERN_ERR "soundfont: remove_info: "
				   "patch not opened\n");
			rc = -EINVAL;
		पूर्ण अन्यथा अणु
			पूर्णांक bank, instr;
			bank = ((अचिन्हित लघु)patch.optarg >> 8) & 0xff;
			instr = (अचिन्हित लघु)patch.optarg & 0xff;
			अगर (! हटाओ_info(sflist, sflist->currsf, bank, instr))
				rc = -EINVAL;
			अन्यथा
				rc = 0;
		पूर्ण
		अवरोध;
	पूर्ण
	unlock_preset(sflist);

	वापस rc;
पूर्ण


/* check अगर specअगरied type is special font (GUS or preset-alias) */
अटल अंतरभूत पूर्णांक
is_special_type(पूर्णांक type)
अणु
	type &= 0x0f;
	वापस (type == SNDRV_SFNT_PAT_TYPE_GUS ||
		type == SNDRV_SFNT_PAT_TYPE_MAP);
पूर्ण


/* खोलो patch; create sf list */
अटल पूर्णांक
खोलो_patch(काष्ठा snd_sf_list *sflist, स्थिर अक्षर __user *data,
	   पूर्णांक count, पूर्णांक client)
अणु
	काष्ठा soundfont_खोलो_parm parm;
	काष्ठा snd_soundfont *sf;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&sflist->lock, flags);
	अगर (sflist->खोलो_client >= 0 || sflist->currsf) अणु
		spin_unlock_irqrestore(&sflist->lock, flags);
		वापस -EBUSY;
	पूर्ण
	spin_unlock_irqrestore(&sflist->lock, flags);

	अगर (copy_from_user(&parm, data, माप(parm)))
		वापस -EFAULT;

	अगर (is_special_type(parm.type)) अणु
		parm.type |= SNDRV_SFNT_PAT_SHARED;
		sf = newsf(sflist, parm.type, शून्य);
	पूर्ण अन्यथा 
		sf = newsf(sflist, parm.type, parm.name);
	अगर (sf == शून्य) अणु
		वापस -ENOMEM;
	पूर्ण

	spin_lock_irqsave(&sflist->lock, flags);
	sflist->खोलो_client = client;
	sflist->currsf = sf;
	spin_unlock_irqrestore(&sflist->lock, flags);

	वापस 0;
पूर्ण

/*
 * Allocate a new soundfont काष्ठाure.
 */
अटल काष्ठा snd_soundfont *
newsf(काष्ठा snd_sf_list *sflist, पूर्णांक type, अक्षर *name)
अणु
	काष्ठा snd_soundfont *sf;

	/* check the shared fonts */
	अगर (type & SNDRV_SFNT_PAT_SHARED) अणु
		क्रम (sf = sflist->fonts; sf; sf = sf->next) अणु
			अगर (is_identical_font(sf, type, name)) अणु
				वापस sf;
			पूर्ण
		पूर्ण
	पूर्ण

	/* not found -- create a new one */
	sf = kzalloc(माप(*sf), GFP_KERNEL);
	अगर (sf == शून्य)
		वापस शून्य;
	sf->id = sflist->fonts_size;
	sflist->fonts_size++;

	/* prepend this record */
	sf->next = sflist->fonts;
	sflist->fonts = sf;

	sf->type = type;
	sf->zones = शून्य;
	sf->samples = शून्य;
	अगर (name)
		स_नकल(sf->name, name, SNDRV_SFNT_PATCH_NAME_LEN);

	वापस sf;
पूर्ण

/* check अगर the given name matches to the existing list */
अटल पूर्णांक
is_identical_font(काष्ठा snd_soundfont *sf, पूर्णांक type, अचिन्हित अक्षर *name)
अणु
	वापस ((sf->type & SNDRV_SFNT_PAT_SHARED) &&
		(sf->type & 0x0f) == (type & 0x0f) &&
		(name == शून्य ||
		 स_भेद(sf->name, name, SNDRV_SFNT_PATCH_NAME_LEN) == 0));
पूर्ण

/*
 * Close the current patch.
 */
अटल पूर्णांक
बंद_patch(काष्ठा snd_sf_list *sflist)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&sflist->lock, flags);
	sflist->currsf = शून्य;
	sflist->खोलो_client = -1;
	spin_unlock_irqrestore(&sflist->lock, flags);

	rebuild_presets(sflist);

	वापस 0;

पूर्ण

/* probe sample in the current list -- nothing to be loaded */
अटल पूर्णांक
probe_data(काष्ठा snd_sf_list *sflist, पूर्णांक sample_id)
अणु
	/* patch must be खोलोed */
	अगर (sflist->currsf) अणु
		/* search the specअगरied sample by optarg */
		अगर (find_sample(sflist->currsf, sample_id))
			वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

/*
 * increment zone counter
 */
अटल व्योम
set_zone_counter(काष्ठा snd_sf_list *sflist, काष्ठा snd_soundfont *sf,
		 काष्ठा snd_sf_zone *zp)
अणु
	zp->counter = sflist->zone_counter++;
	अगर (sf->type & SNDRV_SFNT_PAT_LOCKED)
		sflist->zone_locked = sflist->zone_counter;
पूर्ण

/*
 * allocate a new zone record
 */
अटल काष्ठा snd_sf_zone *
sf_zone_new(काष्ठा snd_sf_list *sflist, काष्ठा snd_soundfont *sf)
अणु
	काष्ठा snd_sf_zone *zp;

	अगर ((zp = kzalloc(माप(*zp), GFP_KERNEL)) == शून्य)
		वापस शून्य;
	zp->next = sf->zones;
	sf->zones = zp;

	init_voice_info(&zp->v);

	set_zone_counter(sflist, sf, zp);
	वापस zp;
पूर्ण


/*
 * increment sample counter
 */
अटल व्योम
set_sample_counter(काष्ठा snd_sf_list *sflist, काष्ठा snd_soundfont *sf,
		   काष्ठा snd_sf_sample *sp)
अणु
	sp->counter = sflist->sample_counter++;
	अगर (sf->type & SNDRV_SFNT_PAT_LOCKED)
		sflist->sample_locked = sflist->sample_counter;
पूर्ण

/*
 * allocate a new sample list record
 */
अटल काष्ठा snd_sf_sample *
sf_sample_new(काष्ठा snd_sf_list *sflist, काष्ठा snd_soundfont *sf)
अणु
	काष्ठा snd_sf_sample *sp;

	अगर ((sp = kzalloc(माप(*sp), GFP_KERNEL)) == शून्य)
		वापस शून्य;

	sp->next = sf->samples;
	sf->samples = sp;

	set_sample_counter(sflist, sf, sp);
	वापस sp;
पूर्ण

/*
 * delete sample list -- this is an exceptional job.
 * only the last allocated sample can be deleted.
 */
अटल व्योम
sf_sample_delete(काष्ठा snd_sf_list *sflist, काष्ठा snd_soundfont *sf,
		 काष्ठा snd_sf_sample *sp)
अणु
	/* only last sample is accepted */
	अगर (sp == sf->samples) अणु
		sf->samples = sp->next;
		kमुक्त(sp);
	पूर्ण
पूर्ण


/* load voice map */
अटल पूर्णांक
load_map(काष्ठा snd_sf_list *sflist, स्थिर व्योम __user *data, पूर्णांक count)
अणु
	काष्ठा snd_sf_zone *zp, *prevp;
	काष्ठा snd_soundfont *sf;
	काष्ठा soundfont_voice_map map;

	/* get the link info */
	अगर (count < (पूर्णांक)माप(map))
		वापस -EINVAL;
	अगर (copy_from_user(&map, data, माप(map)))
		वापस -EFAULT;

	अगर (map.map_instr < 0 || map.map_instr >= SF_MAX_INSTRUMENTS)
		वापस -EINVAL;
	
	sf = newsf(sflist, SNDRV_SFNT_PAT_TYPE_MAP|SNDRV_SFNT_PAT_SHARED, शून्य);
	अगर (sf == शून्य)
		वापस -ENOMEM;

	prevp = शून्य;
	क्रम (zp = sf->zones; zp; prevp = zp, zp = zp->next) अणु
		अगर (zp->mapped &&
		    zp->instr == map.map_instr &&
		    zp->bank == map.map_bank &&
		    zp->v.low == map.map_key &&
		    zp->v.start == map.src_instr &&
		    zp->v.end == map.src_bank &&
		    zp->v.fixkey == map.src_key) अणु
			/* the same mapping is alपढ़ोy present */
			/* relink this record to the link head */
			अगर (prevp) अणु
				prevp->next = zp->next;
				zp->next = sf->zones;
				sf->zones = zp;
			पूर्ण
			/* update the counter */
			set_zone_counter(sflist, sf, zp);
			वापस 0;
		पूर्ण
	पूर्ण

	/* create a new zone */
	अगर ((zp = sf_zone_new(sflist, sf)) == शून्य)
		वापस -ENOMEM;

	zp->bank = map.map_bank;
	zp->instr = map.map_instr;
	zp->mapped = 1;
	अगर (map.map_key >= 0) अणु
		zp->v.low = map.map_key;
		zp->v.high = map.map_key;
	पूर्ण
	zp->v.start = map.src_instr;
	zp->v.end = map.src_bank;
	zp->v.fixkey = map.src_key;
	zp->v.sf_id = sf->id;

	add_preset(sflist, zp);

	वापस 0;
पूर्ण


/* हटाओ the present instrument layers */
अटल पूर्णांक
हटाओ_info(काष्ठा snd_sf_list *sflist, काष्ठा snd_soundfont *sf,
	    पूर्णांक bank, पूर्णांक instr)
अणु
	काष्ठा snd_sf_zone *prev, *next, *p;
	पूर्णांक हटाओd = 0;

	prev = शून्य;
	क्रम (p = sf->zones; p; p = next) अणु
		next = p->next;
		अगर (! p->mapped &&
		    p->bank == bank && p->instr == instr) अणु
			/* हटाओ this layer */
			अगर (prev)
				prev->next = next;
			अन्यथा
				sf->zones = next;
			हटाओd++;
			kमुक्त(p);
		पूर्ण अन्यथा
			prev = p;
	पूर्ण
	अगर (हटाओd)
		rebuild_presets(sflist);
	वापस हटाओd;
पूर्ण


/*
 * Read an info record from the user buffer and save it on the current
 * खोलो soundfont.
 */
अटल पूर्णांक
load_info(काष्ठा snd_sf_list *sflist, स्थिर व्योम __user *data, दीर्घ count)
अणु
	काष्ठा snd_soundfont *sf;
	काष्ठा snd_sf_zone *zone;
	काष्ठा soundfont_voice_rec_hdr hdr;
	पूर्णांक i;

	/* patch must be खोलोed */
	अगर ((sf = sflist->currsf) == शून्य)
		वापस -EINVAL;

	अगर (is_special_type(sf->type))
		वापस -EINVAL;

	अगर (count < (दीर्घ)माप(hdr)) अणु
		prपूर्णांकk(KERN_ERR "Soundfont error: invalid patch zone length\n");
		वापस -EINVAL;
	पूर्ण
	अगर (copy_from_user((अक्षर*)&hdr, data, माप(hdr)))
		वापस -EFAULT;
	
	data += माप(hdr);
	count -= माप(hdr);

	अगर (hdr.nvoices <= 0 || hdr.nvoices >= 100) अणु
		prपूर्णांकk(KERN_ERR "Soundfont error: Illegal voice number %d\n",
		       hdr.nvoices);
		वापस -EINVAL;
	पूर्ण

	अगर (count < (दीर्घ)माप(काष्ठा soundfont_voice_info) * hdr.nvoices) अणु
		prपूर्णांकk(KERN_ERR "Soundfont Error: "
		       "patch length(%ld) is smaller than nvoices(%d)\n",
		       count, hdr.nvoices);
		वापस -EINVAL;
	पूर्ण

	चयन (hdr.ग_लिखो_mode) अणु
	हाल SNDRV_SFNT_WR_EXCLUSIVE:
		/* exclusive mode - अगर the instrument alपढ़ोy exists,
		   वापस error */
		क्रम (zone = sf->zones; zone; zone = zone->next) अणु
			अगर (!zone->mapped &&
			    zone->bank == hdr.bank &&
			    zone->instr == hdr.instr)
				वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल SNDRV_SFNT_WR_REPLACE:
		/* replace mode - हटाओ the instrument अगर it alपढ़ोy exists */
		हटाओ_info(sflist, sf, hdr.bank, hdr.instr);
		अवरोध;
	पूर्ण

	क्रम (i = 0; i < hdr.nvoices; i++) अणु
		काष्ठा snd_sf_zone पंचांगpzone;

		/* copy awe_voice_info parameters */
		अगर (copy_from_user(&पंचांगpzone.v, data, माप(पंचांगpzone.v))) अणु
			वापस -EFAULT;
		पूर्ण

		data += माप(पंचांगpzone.v);
		count -= माप(पंचांगpzone.v);

		पंचांगpzone.bank = hdr.bank;
		पंचांगpzone.instr = hdr.instr;
		पंचांगpzone.mapped = 0;
		पंचांगpzone.v.sf_id = sf->id;
		अगर (पंचांगpzone.v.mode & SNDRV_SFNT_MODE_INIT_PARM)
			init_voice_parm(&पंचांगpzone.v.parm);

		/* create a new zone */
		अगर ((zone = sf_zone_new(sflist, sf)) == शून्य) अणु
			वापस -ENOMEM;
		पूर्ण

		/* copy the temporary data */
		zone->bank = पंचांगpzone.bank;
		zone->instr = पंचांगpzone.instr;
		zone->v = पंचांगpzone.v;

		/* look up the sample */
		zone->sample = set_sample(sf, &zone->v);
	पूर्ण

	वापस 0;
पूर्ण


/* initialize voice_info record */
अटल व्योम
init_voice_info(काष्ठा soundfont_voice_info *avp)
अणु
	स_रखो(avp, 0, माप(*avp));

	avp->root = 60;
	avp->high = 127;
	avp->velhigh = 127;
	avp->fixkey = -1;
	avp->fixvel = -1;
	avp->fixpan = -1;
	avp->pan = -1;
	avp->amplitude = 127;
	avp->scaleTuning = 100;

	init_voice_parm(&avp->parm);
पूर्ण

/* initialize voice_parm record:
 * Env1/2: delay=0, attack=0, hold=0, sustain=0, decay=0, release=0.
 * Vibrato and Tremolo effects are zero.
 * Cutoff is maximum.
 * Chorus and Reverb effects are zero.
 */
अटल व्योम
init_voice_parm(काष्ठा soundfont_voice_parm *pp)
अणु
	स_रखो(pp, 0, माप(*pp));

	pp->moddelay = 0x8000;
	pp->modatkhld = 0x7f7f;
	pp->moddcysus = 0x7f7f;
	pp->modrelease = 0x807f;

	pp->voldelay = 0x8000;
	pp->volatkhld = 0x7f7f;
	pp->voldcysus = 0x7f7f;
	pp->volrelease = 0x807f;

	pp->lfo1delay = 0x8000;
	pp->lfo2delay = 0x8000;

	pp->cutoff = 0xff;
पूर्ण	

/* search the specअगरied sample */
अटल काष्ठा snd_sf_sample *
set_sample(काष्ठा snd_soundfont *sf, काष्ठा soundfont_voice_info *avp)
अणु
	काष्ठा snd_sf_sample *sample;

	sample = find_sample(sf, avp->sample);
	अगर (sample == शून्य)
		वापस शून्य;

	/* add in the actual sample offsets:
	 * The voice_info addresses define only the relative offset
	 * from sample poपूर्णांकers.  Here we calculate the actual DRAM
	 * offset from sample poपूर्णांकers.
	 */
	avp->start += sample->v.start;
	avp->end += sample->v.end;
	avp->loopstart += sample->v.loopstart;
	avp->loखोलोd += sample->v.loखोलोd;

	/* copy mode flags */
	avp->sample_mode = sample->v.mode_flags;

	वापस sample;
पूर्ण

/* find the sample poपूर्णांकer with the given id in the soundfont */
अटल काष्ठा snd_sf_sample *
find_sample(काष्ठा snd_soundfont *sf, पूर्णांक sample_id)
अणु
	काष्ठा snd_sf_sample *p;

	अगर (sf == शून्य)
		वापस शून्य;

	क्रम (p = sf->samples; p; p = p->next) अणु
		अगर (p->v.sample == sample_id)
			वापस p;
	पूर्ण
	वापस शून्य;
पूर्ण


/*
 * Load sample inक्रमmation, this can include data to be loaded onto
 * the soundcard.  It can also just be a poपूर्णांकer पूर्णांकo soundcard ROM.
 * If there is data it will be written to the soundcard via the callback
 * routine.
 */
अटल पूर्णांक
load_data(काष्ठा snd_sf_list *sflist, स्थिर व्योम __user *data, दीर्घ count)
अणु
	काष्ठा snd_soundfont *sf;
	काष्ठा soundfont_sample_info sample_info;
	काष्ठा snd_sf_sample *sp;
	दीर्घ off;

	/* patch must be खोलोed */
	अगर ((sf = sflist->currsf) == शून्य)
		वापस -EINVAL;

	अगर (is_special_type(sf->type))
		वापस -EINVAL;

	अगर (copy_from_user(&sample_info, data, माप(sample_info)))
		वापस -EFAULT;

	off = माप(sample_info);

	अगर (sample_info.size != (count-off)/2)
		वापस -EINVAL;

	/* Check क्रम dup */
	अगर (find_sample(sf, sample_info.sample)) अणु
		/* अगर shared sample, skip this data */
		अगर (sf->type & SNDRV_SFNT_PAT_SHARED)
			वापस 0;
		वापस -EINVAL;
	पूर्ण

	/* Allocate a new sample काष्ठाure */
	अगर ((sp = sf_sample_new(sflist, sf)) == शून्य)
		वापस -ENOMEM;

	sp->v = sample_info;
	sp->v.sf_id = sf->id;
	sp->v.dummy = 0;
	sp->v.truesize = sp->v.size;

	/*
	 * If there is wave data then load it.
	 */
	अगर (sp->v.size > 0) अणु
		पूर्णांक  rc;
		rc = sflist->callback.sample_new
			(sflist->callback.निजी_data, sp, sflist->memhdr,
			 data + off, count - off);
		अगर (rc < 0) अणु
			sf_sample_delete(sflist, sf, sp);
			वापस rc;
		पूर्ण
		sflist->mem_used += sp->v.truesize;
	पूर्ण

	वापस count;
पूर्ण


/* log2_tbl[i] = log2(i+128) * 0x10000 */
अटल स्थिर पूर्णांक log_tbl[129] = अणु
	0x70000, 0x702df, 0x705b9, 0x7088e, 0x70b5d, 0x70e26, 0x710eb, 0x713aa,
	0x71663, 0x71918, 0x71bc8, 0x71e72, 0x72118, 0x723b9, 0x72655, 0x728ed,
	0x72b80, 0x72e0e, 0x73098, 0x7331d, 0x7359e, 0x7381b, 0x73a93, 0x73d08,
	0x73f78, 0x741e4, 0x7444c, 0x746b0, 0x74910, 0x74b6c, 0x74dc4, 0x75019,
	0x75269, 0x754b6, 0x75700, 0x75946, 0x75b88, 0x75dc7, 0x76002, 0x7623a,
	0x7646e, 0x766a0, 0x768cd, 0x76af8, 0x76d1f, 0x76f43, 0x77164, 0x77382,
	0x7759d, 0x777b4, 0x779c9, 0x77bdb, 0x77dea, 0x77ff5, 0x781fe, 0x78404,
	0x78608, 0x78808, 0x78a06, 0x78c01, 0x78df9, 0x78fef, 0x791e2, 0x793d2,
	0x795c0, 0x797ab, 0x79993, 0x79b79, 0x79d5d, 0x79f3e, 0x7a11d, 0x7a2f9,
	0x7a4d3, 0x7a6ab, 0x7a880, 0x7aa53, 0x7ac24, 0x7adf2, 0x7afbe, 0x7b188,
	0x7b350, 0x7b515, 0x7b6d8, 0x7b899, 0x7ba58, 0x7bc15, 0x7bdd0, 0x7bf89,
	0x7c140, 0x7c2f5, 0x7c4a7, 0x7c658, 0x7c807, 0x7c9b3, 0x7cb5e, 0x7cd07,
	0x7ceae, 0x7d053, 0x7d1f7, 0x7d398, 0x7d538, 0x7d6d6, 0x7d872, 0x7da0c,
	0x7dba4, 0x7dd3b, 0x7ded0, 0x7e063, 0x7e1f4, 0x7e384, 0x7e512, 0x7e69f,
	0x7e829, 0x7e9b3, 0x7eb3a, 0x7ecc0, 0x7ee44, 0x7efc7, 0x7f148, 0x7f2c8,
	0x7f446, 0x7f5c2, 0x7f73d, 0x7f8b7, 0x7fa2f, 0x7fba5, 0x7fd1a, 0x7fe8d,
	0x80000,
पूर्ण;

/* convert from linear to log value
 *
 * conversion: value = log2(amount / base) * ratio
 *
 * argument:
 *   amount = linear value (अचिन्हित, 32bit max)
 *   offset = base offset (:= log2(base) * 0x10000)
 *   ratio = भागision ratio
 *
 */
पूर्णांक
snd_sf_linear_to_log(अचिन्हित पूर्णांक amount, पूर्णांक offset, पूर्णांक ratio)
अणु
	पूर्णांक v;
	पूर्णांक s, low, bit;
	
	अगर (amount < 2)
		वापस 0;
	क्रम (bit = 0; ! (amount & 0x80000000L); bit++)
		amount <<= 1;
	s = (amount >> 24) & 0x7f;
	low = (amount >> 16) & 0xff;
	/* linear approxmimation by lower 8 bit */
	v = (log_tbl[s + 1] * low + log_tbl[s] * (0x100 - low)) >> 8;
	v -= offset;
	v = (v * ratio) >> 16;
	v += (24 - bit) * ratio;
	वापस v;
पूर्ण

EXPORT_SYMBOL(snd_sf_linear_to_log);


#घोषणा OFFSET_MSEC		653117		/* base = 1000 */
#घोषणा OFFSET_ABSCENT		851781		/* base = 8176 */
#घोषणा OFFSET_SAMPLERATE	1011119		/* base = 44100 */

#घोषणा ABSCENT_RATIO		1200
#घोषणा TIMECENT_RATIO		1200
#घोषणा SAMPLERATE_RATIO	4096

/*
 * mHz to असलcent
 * conversion: असलcent = log2(MHz / 8176) * 1200
 */
अटल पूर्णांक
freq_to_note(पूर्णांक mhz)
अणु
	वापस snd_sf_linear_to_log(mhz, OFFSET_ABSCENT, ABSCENT_RATIO);
पूर्ण

/* convert Hz to AWE32 rate offset:
 * sample pitch offset क्रम the specअगरied sample rate
 * rate=44100 is no offset, each 4096 is 1 octave (twice).
 * eg, when rate is 22050, this offset becomes -4096.
 *
 * conversion: offset = log2(Hz / 44100) * 4096
 */
अटल पूर्णांक
calc_rate_offset(पूर्णांक hz)
अणु
	वापस snd_sf_linear_to_log(hz, OFFSET_SAMPLERATE, SAMPLERATE_RATIO);
पूर्ण


/* calculate GUS envelope समय */
अटल पूर्णांक
calc_gus_envelope_समय(पूर्णांक rate, पूर्णांक start, पूर्णांक end)
अणु
	पूर्णांक r, p, t;
	r = (3 - ((rate >> 6) & 3)) * 3;
	p = rate & 0x3f;
	अगर (!p)
		p = 1;
	t = end - start;
	अगर (t < 0) t = -t;
	अगर (13 > r)
		t = t << (13 - r);
	अन्यथा
		t = t >> (r - 13);
	वापस (t * 10) / (p * 441);
पूर्ण

/* convert envelope समय parameter to soundfont parameters */

/* attack & decay/release समय table (msec) */
अटल स्थिर लघु attack_समय_प्रकारbl[128] = अणु
32767, 32767, 5989, 4235, 2994, 2518, 2117, 1780, 1497, 1373, 1259, 1154, 1058, 970, 890, 816,
707, 691, 662, 634, 607, 581, 557, 533, 510, 489, 468, 448, 429, 411, 393, 377,
361, 345, 331, 317, 303, 290, 278, 266, 255, 244, 234, 224, 214, 205, 196, 188,
180, 172, 165, 158, 151, 145, 139, 133, 127, 122, 117, 112, 107, 102, 98, 94,
90, 86, 82, 79, 75, 72, 69, 66, 63, 61, 58, 56, 53, 51, 49, 47,
45, 43, 41, 39, 37, 36, 34, 33, 31, 30, 29, 28, 26, 25, 24, 23,
22, 21, 20, 19, 19, 18, 17, 16, 16, 15, 15, 14, 13, 13, 12, 12,
11, 11, 10, 10, 10, 9, 9, 8, 8, 8, 8, 7, 7, 7, 6, 0,
पूर्ण;

अटल स्थिर लघु decay_समय_प्रकारbl[128] = अणु
32767, 32767, 22614, 15990, 11307, 9508, 7995, 6723, 5653, 5184, 4754, 4359, 3997, 3665, 3361, 3082,
2828, 2765, 2648, 2535, 2428, 2325, 2226, 2132, 2042, 1955, 1872, 1793, 1717, 1644, 1574, 1507,
1443, 1382, 1324, 1267, 1214, 1162, 1113, 1066, 978, 936, 897, 859, 822, 787, 754, 722,
691, 662, 634, 607, 581, 557, 533, 510, 489, 468, 448, 429, 411, 393, 377, 361,
345, 331, 317, 303, 290, 278, 266, 255, 244, 234, 224, 214, 205, 196, 188, 180,
172, 165, 158, 151, 145, 139, 133, 127, 122, 117, 112, 107, 102, 98, 94, 90,
86, 82, 79, 75, 72, 69, 66, 63, 61, 58, 56, 53, 51, 49, 47, 45,
43, 41, 39, 37, 36, 34, 33, 31, 30, 29, 28, 26, 25, 24, 23, 22,
पूर्ण;

/* delay समय = 0x8000 - msec/92 */
पूर्णांक
snd_sf_calc_parm_hold(पूर्णांक msec)
अणु
	पूर्णांक val = (0x7f * 92 - msec) / 92;
	अगर (val < 1) val = 1;
	अगर (val >= 126) val = 126;
	वापस val;
पूर्ण

/* search an index क्रम specअगरied समय from given समय table */
अटल पूर्णांक
calc_parm_search(पूर्णांक msec, स्थिर लघु *table)
अणु
	पूर्णांक left = 1, right = 127, mid;
	जबतक (left < right) अणु
		mid = (left + right) / 2;
		अगर (msec < (पूर्णांक)table[mid])
			left = mid + 1;
		अन्यथा
			right = mid;
	पूर्ण
	वापस left;
पूर्ण

/* attack समय: search from समय table */
पूर्णांक
snd_sf_calc_parm_attack(पूर्णांक msec)
अणु
	वापस calc_parm_search(msec, attack_समय_प्रकारbl);
पूर्ण

/* decay/release समय: search from समय table */
पूर्णांक
snd_sf_calc_parm_decay(पूर्णांक msec)
अणु
	वापस calc_parm_search(msec, decay_समय_प्रकारbl);
पूर्ण

पूर्णांक snd_sf_vol_table[128] = अणु
	255,111,95,86,79,74,70,66,63,61,58,56,54,52,50,49,
	47,46,45,43,42,41,40,39,38,37,36,35,34,34,33,32,
	31,31,30,29,29,28,27,27,26,26,25,24,24,23,23,22,
	22,21,21,21,20,20,19,19,18,18,18,17,17,16,16,16,
	15,15,15,14,14,14,13,13,13,12,12,12,11,11,11,10,
	10,10,10,9,9,9,8,8,8,8,7,7,7,7,6,6,
	6,6,5,5,5,5,5,4,4,4,4,3,3,3,3,3,
	2,2,2,2,2,1,1,1,1,1,0,0,0,0,0,0,
पूर्ण;


#घोषणा calc_gus_sustain(val)  (0x7f - snd_sf_vol_table[(val)/2])
#घोषणा calc_gus_attenuation(val)	snd_sf_vol_table[(val)/2]

/* load GUS patch */
अटल पूर्णांक
load_guspatch(काष्ठा snd_sf_list *sflist, स्थिर अक्षर __user *data,
	      दीर्घ count, पूर्णांक client)
अणु
	काष्ठा patch_info patch;
	काष्ठा snd_soundfont *sf;
	काष्ठा snd_sf_zone *zone;
	काष्ठा snd_sf_sample *smp;
	पूर्णांक note, sample_id;
	पूर्णांक rc;

	अगर (count < (दीर्घ)माप(patch)) अणु
		snd_prपूर्णांकk(KERN_ERR "patch record too small %ld\n", count);
		वापस -EINVAL;
	पूर्ण
	अगर (copy_from_user(&patch, data, माप(patch)))
		वापस -EFAULT;
	
	count -= माप(patch);
	data += माप(patch);

	sf = newsf(sflist, SNDRV_SFNT_PAT_TYPE_GUS|SNDRV_SFNT_PAT_SHARED, शून्य);
	अगर (sf == शून्य)
		वापस -ENOMEM;
	अगर ((smp = sf_sample_new(sflist, sf)) == शून्य)
		वापस -ENOMEM;
	sample_id = sflist->sample_counter;
	smp->v.sample = sample_id;
	smp->v.start = 0;
	smp->v.end = patch.len;
	smp->v.loopstart = patch.loop_start;
	smp->v.loखोलोd = patch.loop_end;
	smp->v.size = patch.len;

	/* set up mode flags */
	smp->v.mode_flags = 0;
	अगर (!(patch.mode & WAVE_16_BITS))
		smp->v.mode_flags |= SNDRV_SFNT_SAMPLE_8BITS;
	अगर (patch.mode & WAVE_UNSIGNED)
		smp->v.mode_flags |= SNDRV_SFNT_SAMPLE_UNSIGNED;
	smp->v.mode_flags |= SNDRV_SFNT_SAMPLE_NO_BLANK;
	अगर (!(patch.mode & (WAVE_LOOPING|WAVE_BIसूची_LOOP|WAVE_LOOP_BACK)))
		smp->v.mode_flags |= SNDRV_SFNT_SAMPLE_SINGLESHOT;
	अगर (patch.mode & WAVE_BIसूची_LOOP)
		smp->v.mode_flags |= SNDRV_SFNT_SAMPLE_BIसूची_LOOP;
	अगर (patch.mode & WAVE_LOOP_BACK)
		smp->v.mode_flags |= SNDRV_SFNT_SAMPLE_REVERSE_LOOP;

	अगर (patch.mode & WAVE_16_BITS) अणु
		/* convert to word offsets */
		smp->v.size /= 2;
		smp->v.end /= 2;
		smp->v.loopstart /= 2;
		smp->v.loखोलोd /= 2;
	पूर्ण
	/*smp->v.loखोलोd++;*/

	smp->v.dummy = 0;
	smp->v.truesize = 0;
	smp->v.sf_id = sf->id;

	/* set up voice info */
	अगर ((zone = sf_zone_new(sflist, sf)) == शून्य) अणु
		sf_sample_delete(sflist, sf, smp);
		वापस -ENOMEM;
	पूर्ण

	/*
	 * load wave data
	 */
	अगर (sflist->callback.sample_new) अणु
		rc = sflist->callback.sample_new
			(sflist->callback.निजी_data, smp, sflist->memhdr,
			 data, count);
		अगर (rc < 0) अणु
			sf_sample_delete(sflist, sf, smp);
			kमुक्त(zone);
			वापस rc;
		पूर्ण
		/* memory offset is updated after */
	पूर्ण

	/* update the memory offset here */
	sflist->mem_used += smp->v.truesize;

	zone->v.sample = sample_id; /* the last sample */
	zone->v.rate_offset = calc_rate_offset(patch.base_freq);
	note = freq_to_note(patch.base_note);
	zone->v.root = note / 100;
	zone->v.tune = -(note % 100);
	zone->v.low = (freq_to_note(patch.low_note) + 99) / 100;
	zone->v.high = freq_to_note(patch.high_note) / 100;
	/* panning position; -128 - 127 => 0-127 */
	zone->v.pan = (patch.panning + 128) / 2;
#अगर 0
	snd_prपूर्णांकk(KERN_DEBUG
		   "gus: basefrq=%d (ofs=%d) root=%d,tune=%d, range:%d-%d\n",
		   (पूर्णांक)patch.base_freq, zone->v.rate_offset,
		   zone->v.root, zone->v.tune, zone->v.low, zone->v.high);
#पूर्ण_अगर

	/* detuning is ignored */
	/* 6poपूर्णांकs volume envelope */
	अगर (patch.mode & WAVE_ENVELOPES) अणु
		पूर्णांक attack, hold, decay, release;
		attack = calc_gus_envelope_समय
			(patch.env_rate[0], 0, patch.env_offset[0]);
		hold = calc_gus_envelope_समय
			(patch.env_rate[1], patch.env_offset[0],
			 patch.env_offset[1]);
		decay = calc_gus_envelope_समय
			(patch.env_rate[2], patch.env_offset[1],
			 patch.env_offset[2]);
		release = calc_gus_envelope_समय
			(patch.env_rate[3], patch.env_offset[1],
			 patch.env_offset[4]);
		release += calc_gus_envelope_समय
			(patch.env_rate[4], patch.env_offset[3],
			 patch.env_offset[4]);
		release += calc_gus_envelope_समय
			(patch.env_rate[5], patch.env_offset[4],
			 patch.env_offset[5]);
		zone->v.parm.volatkhld = 
			(snd_sf_calc_parm_hold(hold) << 8) |
			snd_sf_calc_parm_attack(attack);
		zone->v.parm.voldcysus = (calc_gus_sustain(patch.env_offset[2]) << 8) |
			snd_sf_calc_parm_decay(decay);
		zone->v.parm.volrelease = 0x8000 | snd_sf_calc_parm_decay(release);
		zone->v.attenuation = calc_gus_attenuation(patch.env_offset[0]);
#अगर 0
		snd_prपूर्णांकk(KERN_DEBUG
			   "gus: atkhld=%x, dcysus=%x, volrel=%x, att=%d\n",
			   zone->v.parm.volatkhld,
			   zone->v.parm.voldcysus,
			   zone->v.parm.volrelease,
			   zone->v.attenuation);
#पूर्ण_अगर
	पूर्ण

	/* fast release */
	अगर (patch.mode & WAVE_FAST_RELEASE) अणु
		zone->v.parm.volrelease = 0x807f;
	पूर्ण

	/* tremolo effect */
	अगर (patch.mode & WAVE_TREMOLO) अणु
		पूर्णांक rate = (patch.tremolo_rate * 1000 / 38) / 42;
		zone->v.parm.tremfrq = ((patch.tremolo_depth / 2) << 8) | rate;
	पूर्ण
	/* vibrato effect */
	अगर (patch.mode & WAVE_VIBRATO) अणु
		पूर्णांक rate = (patch.vibrato_rate * 1000 / 38) / 42;
		zone->v.parm.fm2frq2 = ((patch.vibrato_depth / 6) << 8) | rate;
	पूर्ण
	
	/* scale_freq, scale_factor, volume, and fractions not implemented */

	अगर (!(smp->v.mode_flags & SNDRV_SFNT_SAMPLE_SINGLESHOT))
		zone->v.mode = SNDRV_SFNT_MODE_LOOPING;
	अन्यथा
		zone->v.mode = 0;

	/* append to the tail of the list */
	/*zone->bank = ctrls[AWE_MD_GUS_BANK];*/
	zone->bank = 0;
	zone->instr = patch.instr_no;
	zone->mapped = 0;
	zone->v.sf_id = sf->id;

	zone->sample = set_sample(sf, &zone->v);

	/* rebuild preset now */
	add_preset(sflist, zone);

	वापस 0;
पूर्ण

/* load GUS patch */
पूर्णांक
snd_soundfont_load_guspatch(काष्ठा snd_sf_list *sflist, स्थिर अक्षर __user *data,
			    दीर्घ count, पूर्णांक client)
अणु
	पूर्णांक rc;
	lock_preset(sflist);
	rc = load_guspatch(sflist, data, count, client);
	unlock_preset(sflist);
	वापस rc;
पूर्ण


/*
 * Rebuild the preset table.  This is like a hash table in that it allows
 * quick access to the zone inक्रमmation.  For each preset there are zone
 * काष्ठाures linked by next_instr and by next_zone.  Former is the whole
 * link क्रम this preset, and latter is the link क्रम zone (i.e. instrument/
 * bank/key combination).
 */
अटल व्योम
rebuild_presets(काष्ठा snd_sf_list *sflist)
अणु
	काष्ठा snd_soundfont *sf;
	काष्ठा snd_sf_zone *cur;

	/* clear preset table */
	स_रखो(sflist->presets, 0, माप(sflist->presets));

	/* search all fonts and insert each font */
	क्रम (sf = sflist->fonts; sf; sf = sf->next) अणु
		क्रम (cur = sf->zones; cur; cur = cur->next) अणु
			अगर (! cur->mapped && cur->sample == शून्य) अणु
				/* try again to search the corresponding sample */
				cur->sample = set_sample(sf, &cur->v);
				अगर (cur->sample == शून्य)
					जारी;
			पूर्ण

			add_preset(sflist, cur);
		पूर्ण
	पूर्ण
पूर्ण


/*
 * add the given zone to preset table
 */
अटल व्योम
add_preset(काष्ठा snd_sf_list *sflist, काष्ठा snd_sf_zone *cur)
अणु
	काष्ठा snd_sf_zone *zone;
	पूर्णांक index;

	zone = search_first_zone(sflist, cur->bank, cur->instr, cur->v.low);
	अगर (zone && zone->v.sf_id != cur->v.sf_id) अणु
		/* dअगरferent instrument was alपढ़ोy defined */
		काष्ठा snd_sf_zone *p;
		/* compare the allocated समय */
		क्रम (p = zone; p; p = p->next_zone) अणु
			अगर (p->counter > cur->counter)
				/* the current is older.. skipped */
				वापस;
		पूर्ण
		/* हटाओ old zones */
		delete_preset(sflist, zone);
		zone = शून्य; /* करो not क्रमget to clear this! */
	पूर्ण

	/* prepend this zone */
	अगर ((index = get_index(cur->bank, cur->instr, cur->v.low)) < 0)
		वापस;
	cur->next_zone = zone; /* zone link */
	cur->next_instr = sflist->presets[index]; /* preset table link */
	sflist->presets[index] = cur;
पूर्ण

/*
 * delete the given zones from preset_table
 */
अटल व्योम
delete_preset(काष्ठा snd_sf_list *sflist, काष्ठा snd_sf_zone *zp)
अणु
	पूर्णांक index;
	काष्ठा snd_sf_zone *p;

	अगर ((index = get_index(zp->bank, zp->instr, zp->v.low)) < 0)
		वापस;
	क्रम (p = sflist->presets[index]; p; p = p->next_instr) अणु
		जबतक (p->next_instr == zp) अणु
			p->next_instr = zp->next_instr;
			zp = zp->next_zone;
			अगर (zp == शून्य)
				वापस;
		पूर्ण
	पूर्ण
पूर्ण


/*
 * Search matching zones from preset table.
 * The note can be rewritten by preset mapping (alias).
 * The found zones are stored on 'table' array.  max_layers defines
 * the maximum number of elements in this array.
 * This function वापसs the number of found zones.  0 अगर not found.
 */
पूर्णांक
snd_soundfont_search_zone(काष्ठा snd_sf_list *sflist, पूर्णांक *notep, पूर्णांक vel,
			  पूर्णांक preset, पूर्णांक bank,
			  पूर्णांक def_preset, पूर्णांक def_bank,
			  काष्ठा snd_sf_zone **table, पूर्णांक max_layers)
अणु
	पूर्णांक nvoices;
	अचिन्हित दीर्घ flags;

	/* this function is supposed to be called atomically,
	 * so we check the lock.  अगर it's busy, just वापसs 0 to
	 * tell the caller the busy state
	 */
	spin_lock_irqsave(&sflist->lock, flags);
	अगर (sflist->presets_locked) अणु
		spin_unlock_irqrestore(&sflist->lock, flags);
		वापस 0;
	पूर्ण
	nvoices = search_zones(sflist, notep, vel, preset, bank,
			       table, max_layers, 0);
	अगर (! nvoices) अणु
		अगर (preset != def_preset || bank != def_bank)
			nvoices = search_zones(sflist, notep, vel,
					       def_preset, def_bank,
					       table, max_layers, 0);
	पूर्ण
	spin_unlock_irqrestore(&sflist->lock, flags);
	वापस nvoices;
पूर्ण


/*
 * search the first matching zone
 */
अटल काष्ठा snd_sf_zone *
search_first_zone(काष्ठा snd_sf_list *sflist, पूर्णांक bank, पूर्णांक preset, पूर्णांक key)
अणु
	पूर्णांक index;
	काष्ठा snd_sf_zone *zp;

	अगर ((index = get_index(bank, preset, key)) < 0)
		वापस शून्य;
	क्रम (zp = sflist->presets[index]; zp; zp = zp->next_instr) अणु
		अगर (zp->instr == preset && zp->bank == bank)
			वापस zp;
	पूर्ण
	वापस शून्य;
पूर्ण


/*
 * search matching zones from sflist.  can be called recursively.
 */
अटल पूर्णांक
search_zones(काष्ठा snd_sf_list *sflist, पूर्णांक *notep, पूर्णांक vel,
	     पूर्णांक preset, पूर्णांक bank, काष्ठा snd_sf_zone **table,
	     पूर्णांक max_layers, पूर्णांक level)
अणु
	काष्ठा snd_sf_zone *zp;
	पूर्णांक nvoices;

	zp = search_first_zone(sflist, bank, preset, *notep);
	nvoices = 0;
	क्रम (; zp; zp = zp->next_zone) अणु
		अगर (*notep >= zp->v.low && *notep <= zp->v.high &&
		    vel >= zp->v.vellow && vel <= zp->v.velhigh) अणु
			अगर (zp->mapped) अणु
				/* search preset mapping (aliasing) */
				पूर्णांक key = zp->v.fixkey;
				preset = zp->v.start;
				bank = zp->v.end;

				अगर (level > 5) /* too deep alias level */
					वापस 0;
				अगर (key < 0)
					key = *notep;
				nvoices = search_zones(sflist, &key, vel,
						       preset, bank, table,
						       max_layers, level + 1);
				अगर (nvoices > 0)
					*notep = key;
				अवरोध;
			पूर्ण
			table[nvoices++] = zp;
			अगर (nvoices >= max_layers)
				अवरोध;
		पूर्ण
	पूर्ण

	वापस nvoices;
पूर्ण


/* calculate the index of preset table:
 * drums are mapped from 128 to 255 according to its note key.
 * other instruments are mapped from 0 to 127.
 * अगर the index is out of range, वापस -1.
 */
अटल पूर्णांक
get_index(पूर्णांक bank, पूर्णांक instr, पूर्णांक key)
अणु
	पूर्णांक index;
	अगर (SF_IS_DRUM_BANK(bank))
		index = key + SF_MAX_INSTRUMENTS;
	अन्यथा
		index = instr;
	index = index % SF_MAX_PRESETS;
	अगर (index < 0)
		वापस -1;
	वापस index;
पूर्ण

/*
 * Initialise the sflist काष्ठाure.
 */
अटल व्योम
snd_sf_init(काष्ठा snd_sf_list *sflist)
अणु
	स_रखो(sflist->presets, 0, माप(sflist->presets));

	sflist->mem_used = 0;
	sflist->currsf = शून्य;
	sflist->खोलो_client = -1;
	sflist->fonts = शून्य;
	sflist->fonts_size = 0;
	sflist->zone_counter = 0;
	sflist->sample_counter = 0;
	sflist->zone_locked = 0;
	sflist->sample_locked = 0;
पूर्ण

/*
 * Release all list records
 */
अटल व्योम
snd_sf_clear(काष्ठा snd_sf_list *sflist)
अणु
	काष्ठा snd_soundfont *sf, *nextsf;
	काष्ठा snd_sf_zone *zp, *nextzp;
	काष्ठा snd_sf_sample *sp, *nextsp;

	क्रम (sf = sflist->fonts; sf; sf = nextsf) अणु
		nextsf = sf->next;
		क्रम (zp = sf->zones; zp; zp = nextzp) अणु
			nextzp = zp->next;
			kमुक्त(zp);
		पूर्ण
		क्रम (sp = sf->samples; sp; sp = nextsp) अणु
			nextsp = sp->next;
			अगर (sflist->callback.sample_मुक्त)
				sflist->callback.sample_मुक्त(sflist->callback.निजी_data,
							     sp, sflist->memhdr);
			kमुक्त(sp);
		पूर्ण
		kमुक्त(sf);
	पूर्ण

	snd_sf_init(sflist);
पूर्ण


/*
 * Create a new sflist काष्ठाure
 */
काष्ठा snd_sf_list *
snd_sf_new(काष्ठा snd_sf_callback *callback, काष्ठा snd_util_memhdr *hdr)
अणु
	काष्ठा snd_sf_list *sflist;

	अगर ((sflist = kzalloc(माप(*sflist), GFP_KERNEL)) == शून्य)
		वापस शून्य;

	mutex_init(&sflist->presets_mutex);
	spin_lock_init(&sflist->lock);
	sflist->memhdr = hdr;

	अगर (callback)
		sflist->callback = *callback;

	snd_sf_init(sflist);
	वापस sflist;
पूर्ण


/*
 * Free everything allocated off the sflist काष्ठाure.
 */
व्योम
snd_sf_मुक्त(काष्ठा snd_sf_list *sflist)
अणु
	अगर (sflist == शून्य)
		वापस;
	
	lock_preset(sflist);
	अगर (sflist->callback.sample_reset)
		sflist->callback.sample_reset(sflist->callback.निजी_data);
	snd_sf_clear(sflist);
	unlock_preset(sflist);

	kमुक्त(sflist);
पूर्ण

/*
 * Remove all samples
 * The soundcard should be silet beक्रमe calling this function.
 */
पूर्णांक
snd_soundfont_हटाओ_samples(काष्ठा snd_sf_list *sflist)
अणु
	lock_preset(sflist);
	अगर (sflist->callback.sample_reset)
		sflist->callback.sample_reset(sflist->callback.निजी_data);
	snd_sf_clear(sflist);
	unlock_preset(sflist);

	वापस 0;
पूर्ण

/*
 * Remove unlocked samples.
 * The soundcard should be silent beक्रमe calling this function.
 */
पूर्णांक
snd_soundfont_हटाओ_unlocked(काष्ठा snd_sf_list *sflist)
अणु
	काष्ठा snd_soundfont *sf;
	काष्ठा snd_sf_zone *zp, *nextzp;
	काष्ठा snd_sf_sample *sp, *nextsp;

	lock_preset(sflist);

	अगर (sflist->callback.sample_reset)
		sflist->callback.sample_reset(sflist->callback.निजी_data);

	/* to be sure */
	स_रखो(sflist->presets, 0, माप(sflist->presets));

	क्रम (sf = sflist->fonts; sf; sf = sf->next) अणु
		क्रम (zp = sf->zones; zp; zp = nextzp) अणु
			अगर (zp->counter < sflist->zone_locked)
				अवरोध;
			nextzp = zp->next;
			sf->zones = nextzp;
			kमुक्त(zp);
		पूर्ण

		क्रम (sp = sf->samples; sp; sp = nextsp) अणु
			अगर (sp->counter < sflist->sample_locked)
				अवरोध;
			nextsp = sp->next;
			sf->samples = nextsp;
			sflist->mem_used -= sp->v.truesize;
			अगर (sflist->callback.sample_मुक्त)
				sflist->callback.sample_मुक्त(sflist->callback.निजी_data,
							     sp, sflist->memhdr);
			kमुक्त(sp);
		पूर्ण
	पूर्ण

	sflist->zone_counter = sflist->zone_locked;
	sflist->sample_counter = sflist->sample_locked;

	rebuild_presets(sflist);

	unlock_preset(sflist);
	वापस 0;
पूर्ण
