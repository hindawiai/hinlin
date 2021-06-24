<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	Sound core.  This file is composed of two parts.  sound_class
 *	which is common to both OSS and ALSA and OSS sound core which
 *	is used OSS or emulation of it.
 */

/*
 * First, the common part.
 */
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/kdev_t.h>
#समावेश <linux/major.h>
#समावेश <sound/core.h>

#अगर_घोषित CONFIG_SOUND_OSS_CORE
अटल पूर्णांक __init init_oss_soundcore(व्योम);
अटल व्योम cleanup_oss_soundcore(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक init_oss_soundcore(व्योम)	अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम cleanup_oss_soundcore(व्योम)	अणु पूर्ण
#पूर्ण_अगर

काष्ठा class *sound_class;
EXPORT_SYMBOL(sound_class);

MODULE_DESCRIPTION("Core sound module");
MODULE_AUTHOR("Alan Cox");
MODULE_LICENSE("GPL");

अटल अक्षर *sound_devnode(काष्ठा device *dev, umode_t *mode)
अणु
	अगर (MAJOR(dev->devt) == SOUND_MAJOR)
		वापस शून्य;
	वापस kaप्र_लिखो(GFP_KERNEL, "snd/%s", dev_name(dev));
पूर्ण

अटल पूर्णांक __init init_soundcore(व्योम)
अणु
	पूर्णांक rc;

	rc = init_oss_soundcore();
	अगर (rc)
		वापस rc;

	sound_class = class_create(THIS_MODULE, "sound");
	अगर (IS_ERR(sound_class)) अणु
		cleanup_oss_soundcore();
		वापस PTR_ERR(sound_class);
	पूर्ण

	sound_class->devnode = sound_devnode;

	वापस 0;
पूर्ण

अटल व्योम __निकास cleanup_soundcore(व्योम)
अणु
	cleanup_oss_soundcore();
	class_destroy(sound_class);
पूर्ण

subsys_initcall(init_soundcore);
module_निकास(cleanup_soundcore);


#अगर_घोषित CONFIG_SOUND_OSS_CORE
/*
 *	OSS sound core handling. Breaks out sound functions to submodules
 *	
 *	Author:		Alan Cox <alan@lxorguk.ukuu.org.uk>
 *
 *	Fixes:
 *
 *                         --------------------
 * 
 *	Top level handler क्रम the sound subप्रणाली. Various devices can
 *	plug पूर्णांकo this. The fact they करोn't all go via OSS doesn't mean 
 *	they करोn't have to implement the OSS API. There is a lot of logic
 *	to keeping much of the OSS weight out of the code in a compatibility
 *	module, but it's up to the driver to rember to load it...
 *
 *	The code provides a set of functions क्रम registration of devices
 *	by type. This is करोne rather than providing a single call so that
 *	we can hide any future changes in the पूर्णांकernals (eg when we go to
 *	32bit dev_t) from the modules and their पूर्णांकerface.
 *
 *	Secondly we need to allocate the dsp, dsp16 and audio devices as
 *	one. Thus we misuse the chains a bit to simplअगरy this.
 *
 *	Thirdly to make it more fun and क्रम 2.3.x and above we करो all
 *	of this using fine grained locking.
 *
 *	FIXME: we have to resolve modules and fine grained load/unload
 *	locking at some poपूर्णांक in 2.3.x.
 */

#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sound.h>
#समावेश <linux/kmod.h>

#घोषणा SOUND_STEP 16

काष्ठा sound_unit
अणु
	पूर्णांक unit_minor;
	स्थिर काष्ठा file_operations *unit_fops;
	काष्ठा sound_unit *next;
	अक्षर name[32];
पूर्ण;

/*
 * By शेष, OSS sound_core claims full legacy minor range (0-255)
 * of SOUND_MAJOR to trap खोलो attempts to any sound minor and
 * requests modules using custom sound-slot/service-* module aliases.
 * The only benefit of करोing this is allowing use of custom module
 * aliases instead of the standard अक्षर-major-* ones.  This behavior
 * prevents alternative OSS implementation and is scheduled to be
 * हटाओd.
 *
 * CONFIG_SOUND_OSS_CORE_PRECLAIM and soundcore.preclaim_oss kernel
 * parameter are added to allow distros and developers to try and
 * चयन to alternative implementations without needing to rebuild
 * the kernel in the meanसमय.  If preclaim_oss is non-zero, the
 * kernel will behave the same as beक्रमe.  All SOUND_MAJOR minors are
 * preclaimed and the custom module aliases aदीर्घ with standard chrdev
 * ones are emitted अगर a missing device is खोलोed.  If preclaim_oss is
 * zero, sound_core only grअसल what's actually in use and क्रम missing
 * devices only the standard chrdev aliases are requested.
 *
 * All these clutters are scheduled to be हटाओd aदीर्घ with
 * sound-slot/service-* module aliases.
 */
#अगर_घोषित CONFIG_SOUND_OSS_CORE_PRECLAIM
अटल पूर्णांक preclaim_oss = 1;
#अन्यथा
अटल पूर्णांक preclaim_oss = 0;
#पूर्ण_अगर

module_param(preclaim_oss, पूर्णांक, 0444);

अटल पूर्णांक soundcore_खोलो(काष्ठा inode *, काष्ठा file *);

अटल स्थिर काष्ठा file_operations soundcore_fops =
अणु
	/* We must have an owner or the module locking fails */
	.owner	= THIS_MODULE,
	.खोलो	= soundcore_खोलो,
	.llseek = noop_llseek,
पूर्ण;

/*
 *	Low level list चालक. Scan the ordered list, find a hole and
 *	join पूर्णांकo it. Called with the lock निश्चितed
 */

अटल पूर्णांक __sound_insert_unit(काष्ठा sound_unit * s, काष्ठा sound_unit **list, स्थिर काष्ठा file_operations *fops, पूर्णांक index, पूर्णांक low, पूर्णांक top)
अणु
	पूर्णांक n=low;

	अगर (index < 0) अणु	/* first मुक्त */

		जबतक (*list && (*list)->unit_minor<n)
			list=&((*list)->next);

		जबतक(n<top)
		अणु
			/* Found a hole ? */
			अगर(*list==शून्य || (*list)->unit_minor>n)
				अवरोध;
			list=&((*list)->next);
			n+=SOUND_STEP;
		पूर्ण

		अगर(n>=top)
			वापस -ENOENT;
	पूर्ण अन्यथा अणु
		n = low+(index*16);
		जबतक (*list) अणु
			अगर ((*list)->unit_minor==n)
				वापस -EBUSY;
			अगर ((*list)->unit_minor>n)
				अवरोध;
			list=&((*list)->next);
		पूर्ण
	पूर्ण	
		
	/*
	 *	Fill it in
	 */
	 
	s->unit_minor=n;
	s->unit_fops=fops;
	
	/*
	 *	Link it
	 */
	 
	s->next=*list;
	*list=s;
	
	
	वापस n;
पूर्ण

/*
 *	Remove a node from the chain. Called with the lock निश्चितed
 */
 
अटल काष्ठा sound_unit *__sound_हटाओ_unit(काष्ठा sound_unit **list, पूर्णांक unit)
अणु
	जबतक(*list)
	अणु
		काष्ठा sound_unit *p=*list;
		अगर(p->unit_minor==unit)
		अणु
			*list=p->next;
			वापस p;
		पूर्ण
		list=&(p->next);
	पूर्ण
	prपूर्णांकk(KERN_ERR "Sound device %d went missing!\n", unit);
	वापस शून्य;
पूर्ण

/*
 *	This lock guards the sound loader list.
 */

अटल DEFINE_SPINLOCK(sound_loader_lock);

/*
 *	Allocate the controlling काष्ठाure and add it to the sound driver
 *	list. Acquires locks as needed
 */

अटल पूर्णांक sound_insert_unit(काष्ठा sound_unit **list, स्थिर काष्ठा file_operations *fops, पूर्णांक index, पूर्णांक low, पूर्णांक top, स्थिर अक्षर *name, umode_t mode, काष्ठा device *dev)
अणु
	काष्ठा sound_unit *s = kदो_स्मृति(माप(*s), GFP_KERNEL);
	पूर्णांक r;

	अगर (!s)
		वापस -ENOMEM;

	spin_lock(&sound_loader_lock);
retry:
	r = __sound_insert_unit(s, list, fops, index, low, top);
	spin_unlock(&sound_loader_lock);
	
	अगर (r < 0)
		जाओ fail;
	अन्यथा अगर (r < SOUND_STEP)
		प्र_लिखो(s->name, "sound/%s", name);
	अन्यथा
		प्र_लिखो(s->name, "sound/%s%d", name, r / SOUND_STEP);

	अगर (!preclaim_oss) अणु
		/*
		 * Something अन्यथा might have grabbed the minor.  If
		 * first मुक्त slot is requested, rescan with @low set
		 * to the next unit; otherwise, -EBUSY.
		 */
		r = __रेजिस्टर_chrdev(SOUND_MAJOR, s->unit_minor, 1, s->name,
				      &soundcore_fops);
		अगर (r < 0) अणु
			spin_lock(&sound_loader_lock);
			__sound_हटाओ_unit(list, s->unit_minor);
			अगर (index < 0) अणु
				low = s->unit_minor + SOUND_STEP;
				जाओ retry;
			पूर्ण
			spin_unlock(&sound_loader_lock);
			r = -EBUSY;
			जाओ fail;
		पूर्ण
	पूर्ण

	device_create(sound_class, dev, MKDEV(SOUND_MAJOR, s->unit_minor),
		      शून्य, "%s", s->name+6);
	वापस s->unit_minor;

fail:
	kमुक्त(s);
	वापस r;
पूर्ण

/*
 *	Remove a unit. Acquires locks as needed. The drivers MUST have
 *	completed the removal beक्रमe their file operations become
 *	invalid.
 */
 	
अटल व्योम sound_हटाओ_unit(काष्ठा sound_unit **list, पूर्णांक unit)
अणु
	काष्ठा sound_unit *p;

	spin_lock(&sound_loader_lock);
	p = __sound_हटाओ_unit(list, unit);
	spin_unlock(&sound_loader_lock);
	अगर (p) अणु
		अगर (!preclaim_oss)
			__unरेजिस्टर_chrdev(SOUND_MAJOR, p->unit_minor, 1,
					    p->name);
		device_destroy(sound_class, MKDEV(SOUND_MAJOR, p->unit_minor));
		kमुक्त(p);
	पूर्ण
पूर्ण

/*
 *	Allocations
 *
 *	0	*16		Mixers
 *	1	*8		Sequencers
 *	2	*16		Midi
 *	3	*16		DSP
 *	4	*16		SunDSP
 *	5	*16		DSP16
 *	6	--		sndstat (obsolete)
 *	7	*16		unused
 *	8	--		alternate sequencer (see above)
 *	9	*16		raw synthesizer access
 *	10	*16		unused
 *	11	*16		unused
 *	12	*16		unused
 *	13	*16		unused
 *	14	*16		unused
 *	15	*16		unused
 */

अटल काष्ठा sound_unit *chains[SOUND_STEP];

/**
 *	रेजिस्टर_sound_special_device - रेजिस्टर a special sound node
 *	@fops: File operations क्रम the driver
 *	@unit: Unit number to allocate
 *      @dev: device poपूर्णांकer
 *
 *	Allocate a special sound device by minor number from the sound
 *	subप्रणाली.
 *
 *	Return: The allocated number is वापसed on success. On failure,
 *	a negative error code is वापसed.
 */
 
पूर्णांक रेजिस्टर_sound_special_device(स्थिर काष्ठा file_operations *fops, पूर्णांक unit,
				  काष्ठा device *dev)
अणु
	स्थिर पूर्णांक chain = unit % SOUND_STEP;
	पूर्णांक max_unit = 256;
	स्थिर अक्षर *name;
	अक्षर _name[16];

	चयन (chain) अणु
	    हाल 0:
		name = "mixer";
		अवरोध;
	    हाल 1:
		name = "sequencer";
		अगर (unit >= SOUND_STEP)
			जाओ __unknown;
		max_unit = unit + 1;
		अवरोध;
	    हाल 2:
		name = "midi";
		अवरोध;
	    हाल 3:
		name = "dsp";
		अवरोध;
	    हाल 4:
		name = "audio";
		अवरोध;
	    हाल 5:
		name = "dspW";
		अवरोध;
	    हाल 8:
		name = "sequencer2";
		अगर (unit >= SOUND_STEP)
			जाओ __unknown;
		max_unit = unit + 1;
		अवरोध;
	    हाल 9:
		name = "dmmidi";
		अवरोध;
	    हाल 10:
		name = "dmfm";
		अवरोध;
	    हाल 12:
		name = "adsp";
		अवरोध;
	    हाल 13:
		name = "amidi";
		अवरोध;
	    हाल 14:
		name = "admmidi";
		अवरोध;
	    शेष:
	    	अणु
		    __unknown:
			प्र_लिखो(_name, "unknown%d", chain);
		    	अगर (unit >= SOUND_STEP)
		    		म_जोड़ो(_name, "-");
		    	name = _name;
		पूर्ण
		अवरोध;
	पूर्ण
	वापस sound_insert_unit(&chains[chain], fops, -1, unit, max_unit,
				 name, 0600, dev);
पूर्ण
 
EXPORT_SYMBOL(रेजिस्टर_sound_special_device);

पूर्णांक रेजिस्टर_sound_special(स्थिर काष्ठा file_operations *fops, पूर्णांक unit)
अणु
	वापस रेजिस्टर_sound_special_device(fops, unit, शून्य);
पूर्ण

EXPORT_SYMBOL(रेजिस्टर_sound_special);

/**
 *	रेजिस्टर_sound_mixer - रेजिस्टर a mixer device
 *	@fops: File operations क्रम the driver
 *	@dev: Unit number to allocate
 *
 *	Allocate a mixer device. Unit is the number of the mixer requested.
 *	Pass -1 to request the next मुक्त mixer unit.
 *
 *	Return: On success, the allocated number is वापसed. On failure,
 *	a negative error code is वापसed.
 */

पूर्णांक रेजिस्टर_sound_mixer(स्थिर काष्ठा file_operations *fops, पूर्णांक dev)
अणु
	वापस sound_insert_unit(&chains[0], fops, dev, 0, 128,
				 "mixer", 0600, शून्य);
पूर्ण

EXPORT_SYMBOL(रेजिस्टर_sound_mixer);

/*
 *	DSP's are रेजिस्टरed as a triple. Register only one and cheat
 *	in खोलो - see below.
 */
 
/**
 *	रेजिस्टर_sound_dsp - रेजिस्टर a DSP device
 *	@fops: File operations क्रम the driver
 *	@dev: Unit number to allocate
 *
 *	Allocate a DSP device. Unit is the number of the DSP requested.
 *	Pass -1 to request the next मुक्त DSP unit.
 *
 *	This function allocates both the audio and dsp device entries together
 *	and will always allocate them as a matching pair - eg dsp3/audio3
 *
 *	Return: On success, the allocated number is वापसed. On failure,
 *	a negative error code is वापसed.
 */

पूर्णांक रेजिस्टर_sound_dsp(स्थिर काष्ठा file_operations *fops, पूर्णांक dev)
अणु
	वापस sound_insert_unit(&chains[3], fops, dev, 3, 131,
				 "dsp", 0600, शून्य);
पूर्ण

EXPORT_SYMBOL(रेजिस्टर_sound_dsp);

/**
 *	unरेजिस्टर_sound_special - unरेजिस्टर a special sound device
 *	@unit: unit number to allocate
 *
 *	Release a sound device that was allocated with
 *	रेजिस्टर_sound_special(). The unit passed is the वापस value from
 *	the रेजिस्टर function.
 */


व्योम unरेजिस्टर_sound_special(पूर्णांक unit)
अणु
	sound_हटाओ_unit(&chains[unit % SOUND_STEP], unit);
पूर्ण
 
EXPORT_SYMBOL(unरेजिस्टर_sound_special);

/**
 *	unरेजिस्टर_sound_mixer - unरेजिस्टर a mixer
 *	@unit: unit number to allocate
 *
 *	Release a sound device that was allocated with रेजिस्टर_sound_mixer().
 *	The unit passed is the वापस value from the रेजिस्टर function.
 */

व्योम unरेजिस्टर_sound_mixer(पूर्णांक unit)
अणु
	sound_हटाओ_unit(&chains[0], unit);
पूर्ण

EXPORT_SYMBOL(unरेजिस्टर_sound_mixer);

/**
 *	unरेजिस्टर_sound_dsp - unरेजिस्टर a DSP device
 *	@unit: unit number to allocate
 *
 *	Release a sound device that was allocated with रेजिस्टर_sound_dsp().
 *	The unit passed is the वापस value from the रेजिस्टर function.
 *
 *	Both of the allocated units are released together स्वतःmatically.
 */

व्योम unरेजिस्टर_sound_dsp(पूर्णांक unit)
अणु
	sound_हटाओ_unit(&chains[3], unit);
पूर्ण


EXPORT_SYMBOL(unरेजिस्टर_sound_dsp);

अटल काष्ठा sound_unit *__look_क्रम_unit(पूर्णांक chain, पूर्णांक unit)
अणु
	काष्ठा sound_unit *s;
	
	s=chains[chain];
	जबतक(s && s->unit_minor <= unit)
	अणु
		अगर(s->unit_minor==unit)
			वापस s;
		s=s->next;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक soundcore_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	पूर्णांक chain;
	पूर्णांक unit = iminor(inode);
	काष्ठा sound_unit *s;
	स्थिर काष्ठा file_operations *new_fops = शून्य;

	chain=unit&0x0F;
	अगर(chain==4 || chain==5)	/* dsp/audio/dsp16 */
	अणु
		unit&=0xF0;
		unit|=3;
		chain=3;
	पूर्ण
	
	spin_lock(&sound_loader_lock);
	s = __look_क्रम_unit(chain, unit);
	अगर (s)
		new_fops = fops_get(s->unit_fops);
	अगर (preclaim_oss && !new_fops) अणु
		spin_unlock(&sound_loader_lock);

		/*
		 *  Please, करोn't change this order or code.
		 *  For ALSA slot means soundcard and OSS emulation code
		 *  comes as add-on modules which aren't depend on
		 *  ALSA toplevel modules क्रम soundcards, thus we need
		 *  load them at first.	  [Jaroslav Kysela <perex@jcu.cz>]
		 */
		request_module("sound-slot-%i", unit>>4);
		request_module("sound-service-%i-%i", unit>>4, chain);

		/*
		 * sound-slot/service-* module aliases are scheduled
		 * क्रम removal in favor of the standard अक्षर-major-*
		 * module aliases.  For the समय being, generate both
		 * the legacy and standard module aliases to ease
		 * transition.
		 */
		अगर (request_module("char-major-%d-%d", SOUND_MAJOR, unit) > 0)
			request_module("char-major-%d", SOUND_MAJOR);

		spin_lock(&sound_loader_lock);
		s = __look_क्रम_unit(chain, unit);
		अगर (s)
			new_fops = fops_get(s->unit_fops);
	पूर्ण
	spin_unlock(&sound_loader_lock);
	अगर (new_fops) अणु
		/*
		 * We rely upon the fact that we can't be unloaded जबतक the
		 * subdriver is there.
		 */
		पूर्णांक err = 0;
		replace_fops(file, new_fops);

		अगर (file->f_op->खोलो)
			err = file->f_op->खोलो(inode,file);

		वापस err;
	पूर्ण
	वापस -ENODEV;
पूर्ण

MODULE_ALIAS_CHARDEV_MAJOR(SOUND_MAJOR);

अटल व्योम cleanup_oss_soundcore(व्योम)
अणु
	/* We have nothing to really करो here - we know the lists must be
	   empty */
	unरेजिस्टर_chrdev(SOUND_MAJOR, "sound");
पूर्ण

अटल पूर्णांक __init init_oss_soundcore(व्योम)
अणु
	अगर (preclaim_oss &&
	    रेजिस्टर_chrdev(SOUND_MAJOR, "sound", &soundcore_fops) < 0) अणु
		prपूर्णांकk(KERN_ERR "soundcore: sound device already in use.\n");
		वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_SOUND_OSS_CORE */
