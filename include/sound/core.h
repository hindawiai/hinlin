<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित __SOUND_CORE_H
#घोषणा __SOUND_CORE_H

/*
 *  Main header file क्रम the ALSA driver
 *  Copyright (c) 1994-2001 by Jaroslav Kysela <perex@perex.cz>
 */

#समावेश <linux/device.h>
#समावेश <linux/sched.h>		/* wake_up() */
#समावेश <linux/mutex.h>		/* काष्ठा mutex */
#समावेश <linux/rwsem.h>		/* काष्ठा rw_semaphore */
#समावेश <linux/pm.h>			/* pm_message_t */
#समावेश <linux/stringअगरy.h>
#समावेश <linux/prपूर्णांकk.h>

/* number of supported soundcards */
#अगर_घोषित CONFIG_SND_DYNAMIC_MINORS
#घोषणा SNDRV_CARDS CONFIG_SND_MAX_CARDS
#अन्यथा
#घोषणा SNDRV_CARDS 8		/* करोn't change - minor numbers */
#पूर्ण_अगर

#घोषणा CONFIG_SND_MAJOR	116	/* standard configuration */

/* क्रमward declarations */
काष्ठा pci_dev;
काष्ठा module;
काष्ठा completion;

/* device allocation stuff */

/* type of the object used in snd_device_*()
 * this also defines the calling order
 */
क्रमागत snd_device_type अणु
	SNDRV_DEV_LOWLEVEL,
	SNDRV_DEV_INFO,
	SNDRV_DEV_BUS,
	SNDRV_DEV_CODEC,
	SNDRV_DEV_PCM,
	SNDRV_DEV_COMPRESS,
	SNDRV_DEV_RAWMIDI,
	SNDRV_DEV_TIMER,
	SNDRV_DEV_SEQUENCER,
	SNDRV_DEV_HWDEP,
	SNDRV_DEV_JACK,
	SNDRV_DEV_CONTROL,	/* NOTE: this must be the last one */
पूर्ण;

क्रमागत snd_device_state अणु
	SNDRV_DEV_BUILD,
	SNDRV_DEV_REGISTERED,
	SNDRV_DEV_DISCONNECTED,
पूर्ण;

काष्ठा snd_device;

काष्ठा snd_device_ops अणु
	पूर्णांक (*dev_मुक्त)(काष्ठा snd_device *dev);
	पूर्णांक (*dev_रेजिस्टर)(काष्ठा snd_device *dev);
	पूर्णांक (*dev_disconnect)(काष्ठा snd_device *dev);
पूर्ण;

काष्ठा snd_device अणु
	काष्ठा list_head list;		/* list of रेजिस्टरed devices */
	काष्ठा snd_card *card;		/* card which holds this device */
	क्रमागत snd_device_state state;	/* state of the device */
	क्रमागत snd_device_type type;	/* device type */
	व्योम *device_data;		/* device काष्ठाure */
	स्थिर काष्ठा snd_device_ops *ops;	/* operations */
पूर्ण;

#घोषणा snd_device(n) list_entry(n, काष्ठा snd_device, list)

/* मुख्य काष्ठाure क्रम soundcard */

काष्ठा snd_card अणु
	पूर्णांक number;			/* number of soundcard (index to
								snd_cards) */

	अक्षर id[16];			/* id string of this card */
	अक्षर driver[16];		/* driver name */
	अक्षर लघुname[32];		/* लघु name of this soundcard */
	अक्षर दीर्घname[80];		/* name of this soundcard */
	अक्षर irq_descr[32];		/* Interrupt description */
	अक्षर mixername[80];		/* mixer name */
	अक्षर components[128];		/* card components delimited with
								space */
	काष्ठा module *module;		/* top-level module */

	व्योम *निजी_data;		/* निजी data क्रम soundcard */
	व्योम (*निजी_मुक्त) (काष्ठा snd_card *card); /* callback क्रम मुक्तing of
								निजी data */
	काष्ठा list_head devices;	/* devices */

	काष्ठा device ctl_dev;		/* control device */
	अचिन्हित पूर्णांक last_numid;	/* last used numeric ID */
	काष्ठा rw_semaphore controls_rwsem;	/* controls list lock */
	rwlock_t ctl_files_rwlock;	/* ctl_files list lock */
	पूर्णांक controls_count;		/* count of all controls */
	माप_प्रकार user_ctl_alloc_size;	// current memory allocation by user controls.
	काष्ठा list_head controls;	/* all controls क्रम this card */
	काष्ठा list_head ctl_files;	/* active control files */

	काष्ठा snd_info_entry *proc_root;	/* root क्रम soundcard specअगरic files */
	काष्ठा proc_dir_entry *proc_root_link;	/* number link to real id */

	काष्ठा list_head files_list;	/* all files associated to this card */
	काष्ठा snd_shutकरोwn_f_ops *s_f_ops; /* file operations in the shutकरोwn
								state */
	spinlock_t files_lock;		/* lock the files क्रम this card */
	पूर्णांक shutकरोwn;			/* this card is going करोwn */
	काष्ठा completion *release_completion;
	काष्ठा device *dev;		/* device asचिन्हित to this card */
	काष्ठा device card_dev;		/* cardX object क्रम sysfs */
	स्थिर काष्ठा attribute_group *dev_groups[4]; /* asचिन्हित sysfs attr */
	bool रेजिस्टरed;		/* card_dev is रेजिस्टरed? */
	पूर्णांक sync_irq;			/* asचिन्हित irq, used क्रम PCM sync */
	रुको_queue_head_t हटाओ_sleep;

	माप_प्रकार total_pcm_alloc_bytes;	/* total amount of allocated buffers */
	काष्ठा mutex memory_mutex;	/* protection क्रम the above */
#अगर_घोषित CONFIG_SND_DEBUG
	काष्ठा dentry *debugfs_root;    /* debugfs root क्रम card */
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM
	अचिन्हित पूर्णांक घातer_state;	/* घातer state */
	रुको_queue_head_t घातer_sleep;
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_SND_MIXER_OSS)
	काष्ठा snd_mixer_oss *mixer_oss;
	पूर्णांक mixer_oss_change_count;
#पूर्ण_अगर
पूर्ण;

#घोषणा dev_to_snd_card(p)	container_of(p, काष्ठा snd_card, card_dev)

#अगर_घोषित CONFIG_PM
अटल अंतरभूत अचिन्हित पूर्णांक snd_घातer_get_state(काष्ठा snd_card *card)
अणु
	वापस card->घातer_state;
पूर्ण

अटल अंतरभूत व्योम snd_घातer_change_state(काष्ठा snd_card *card, अचिन्हित पूर्णांक state)
अणु
	card->घातer_state = state;
	wake_up(&card->घातer_sleep);
पूर्ण

/* init.c */
पूर्णांक snd_घातer_रुको(काष्ठा snd_card *card, अचिन्हित पूर्णांक घातer_state);

#अन्यथा /* ! CONFIG_PM */

अटल अंतरभूत पूर्णांक snd_घातer_रुको(काष्ठा snd_card *card, अचिन्हित पूर्णांक state) अणु वापस 0; पूर्ण
#घोषणा snd_घातer_get_state(card)	(अणु (व्योम)(card); SNDRV_CTL_POWER_D0; पूर्ण)
#घोषणा snd_घातer_change_state(card, state)	करो अणु (व्योम)(card); पूर्ण जबतक (0)

#पूर्ण_अगर /* CONFIG_PM */

काष्ठा snd_minor अणु
	पूर्णांक type;			/* SNDRV_DEVICE_TYPE_XXX */
	पूर्णांक card;			/* card number */
	पूर्णांक device;			/* device number */
	स्थिर काष्ठा file_operations *f_ops;	/* file operations */
	व्योम *निजी_data;		/* निजी data क्रम f_ops->खोलो */
	काष्ठा device *dev;		/* device क्रम sysfs */
	काष्ठा snd_card *card_ptr;	/* asचिन्हित card instance */
पूर्ण;

/* वापस a device poपूर्णांकer linked to each sound device as a parent */
अटल अंतरभूत काष्ठा device *snd_card_get_device_link(काष्ठा snd_card *card)
अणु
	वापस card ? &card->card_dev : शून्य;
पूर्ण

/* sound.c */

बाह्य पूर्णांक snd_major;
बाह्य पूर्णांक snd_ecards_limit;
बाह्य काष्ठा class *sound_class;
#अगर_घोषित CONFIG_SND_DEBUG
बाह्य काष्ठा dentry *sound_debugfs_root;
#पूर्ण_अगर

व्योम snd_request_card(पूर्णांक card);

व्योम snd_device_initialize(काष्ठा device *dev, काष्ठा snd_card *card);

पूर्णांक snd_रेजिस्टर_device(पूर्णांक type, काष्ठा snd_card *card, पूर्णांक dev,
			स्थिर काष्ठा file_operations *f_ops,
			व्योम *निजी_data, काष्ठा device *device);
पूर्णांक snd_unरेजिस्टर_device(काष्ठा device *dev);
व्योम *snd_lookup_minor_data(अचिन्हित पूर्णांक minor, पूर्णांक type);

#अगर_घोषित CONFIG_SND_OSSEMUL
पूर्णांक snd_रेजिस्टर_oss_device(पूर्णांक type, काष्ठा snd_card *card, पूर्णांक dev,
			    स्थिर काष्ठा file_operations *f_ops, व्योम *निजी_data);
पूर्णांक snd_unरेजिस्टर_oss_device(पूर्णांक type, काष्ठा snd_card *card, पूर्णांक dev);
व्योम *snd_lookup_oss_minor_data(अचिन्हित पूर्णांक minor, पूर्णांक type);
#पूर्ण_अगर

पूर्णांक snd_minor_info_init(व्योम);

/* sound_oss.c */

#अगर_घोषित CONFIG_SND_OSSEMUL
पूर्णांक snd_minor_info_oss_init(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक snd_minor_info_oss_init(व्योम) अणु वापस 0; पूर्ण
#पूर्ण_अगर

/* memory.c */

पूर्णांक copy_to_user_fromio(व्योम __user *dst, स्थिर अस्थिर व्योम __iomem *src, माप_प्रकार count);
पूर्णांक copy_from_user_toio(अस्थिर व्योम __iomem *dst, स्थिर व्योम __user *src, माप_प्रकार count);

/* init.c */

पूर्णांक snd_card_locked(पूर्णांक card);
#अगर IS_ENABLED(CONFIG_SND_MIXER_OSS)
#घोषणा SND_MIXER_OSS_NOTIFY_REGISTER	0
#घोषणा SND_MIXER_OSS_NOTIFY_DISCONNECT	1
#घोषणा SND_MIXER_OSS_NOTIFY_FREE	2
बाह्य पूर्णांक (*snd_mixer_oss_notअगरy_callback)(काष्ठा snd_card *card, पूर्णांक cmd);
#पूर्ण_अगर

पूर्णांक snd_card_new(काष्ठा device *parent, पूर्णांक idx, स्थिर अक्षर *xid,
		 काष्ठा module *module, पूर्णांक extra_size,
		 काष्ठा snd_card **card_ret);

पूर्णांक snd_card_disconnect(काष्ठा snd_card *card);
व्योम snd_card_disconnect_sync(काष्ठा snd_card *card);
पूर्णांक snd_card_मुक्त(काष्ठा snd_card *card);
पूर्णांक snd_card_मुक्त_when_बंदd(काष्ठा snd_card *card);
व्योम snd_card_set_id(काष्ठा snd_card *card, स्थिर अक्षर *id);
पूर्णांक snd_card_रेजिस्टर(काष्ठा snd_card *card);
पूर्णांक snd_card_info_init(व्योम);
पूर्णांक snd_card_add_dev_attr(काष्ठा snd_card *card,
			  स्थिर काष्ठा attribute_group *group);
पूर्णांक snd_component_add(काष्ठा snd_card *card, स्थिर अक्षर *component);
पूर्णांक snd_card_file_add(काष्ठा snd_card *card, काष्ठा file *file);
पूर्णांक snd_card_file_हटाओ(काष्ठा snd_card *card, काष्ठा file *file);

काष्ठा snd_card *snd_card_ref(पूर्णांक card);

/**
 * snd_card_unref - Unreference the card object
 * @card: the card object to unreference
 *
 * Call this function क्रम the card object that was obtained via snd_card_ref()
 * or snd_lookup_minor_data().
 */
अटल अंतरभूत व्योम snd_card_unref(काष्ठा snd_card *card)
अणु
	put_device(&card->card_dev);
पूर्ण

#घोषणा snd_card_set_dev(card, devptr) ((card)->dev = (devptr))

/* device.c */

पूर्णांक snd_device_new(काष्ठा snd_card *card, क्रमागत snd_device_type type,
		   व्योम *device_data, स्थिर काष्ठा snd_device_ops *ops);
पूर्णांक snd_device_रेजिस्टर(काष्ठा snd_card *card, व्योम *device_data);
पूर्णांक snd_device_रेजिस्टर_all(काष्ठा snd_card *card);
व्योम snd_device_disconnect(काष्ठा snd_card *card, व्योम *device_data);
व्योम snd_device_disconnect_all(काष्ठा snd_card *card);
व्योम snd_device_मुक्त(काष्ठा snd_card *card, व्योम *device_data);
व्योम snd_device_मुक्त_all(काष्ठा snd_card *card);
पूर्णांक snd_device_get_state(काष्ठा snd_card *card, व्योम *device_data);

/* isadma.c */

#अगर_घोषित CONFIG_ISA_DMA_API
#घोषणा DMA_MODE_NO_ENABLE	0x0100

व्योम snd_dma_program(अचिन्हित दीर्घ dma, अचिन्हित दीर्घ addr, अचिन्हित पूर्णांक size, अचिन्हित लघु mode);
व्योम snd_dma_disable(अचिन्हित दीर्घ dma);
अचिन्हित पूर्णांक snd_dma_poपूर्णांकer(अचिन्हित दीर्घ dma, अचिन्हित पूर्णांक size);
#पूर्ण_अगर

/* misc.c */
काष्ठा resource;
व्योम release_and_मुक्त_resource(काष्ठा resource *res);

/* --- */

/* sound prपूर्णांकk debug levels */
क्रमागत अणु
	SND_PR_ALWAYS,
	SND_PR_DEBUG,
	SND_PR_VERBOSE,
पूर्ण;

#अगर defined(CONFIG_SND_DEBUG) || defined(CONFIG_SND_VERBOSE_PRINTK)
__म_लिखो(4, 5)
व्योम __snd_prपूर्णांकk(अचिन्हित पूर्णांक level, स्थिर अक्षर *file, पूर्णांक line,
		  स्थिर अक्षर *क्रमmat, ...);
#अन्यथा
#घोषणा __snd_prपूर्णांकk(level, file, line, क्रमmat, ...) \
	prपूर्णांकk(क्रमmat, ##__VA_ARGS__)
#पूर्ण_अगर

/**
 * snd_prपूर्णांकk - prपूर्णांकk wrapper
 * @fmt: क्रमmat string
 *
 * Works like prपूर्णांकk() but prपूर्णांकs the file and the line of the caller
 * when configured with CONFIG_SND_VERBOSE_PRINTK.
 */
#घोषणा snd_prपूर्णांकk(fmt, ...) \
	__snd_prपूर्णांकk(0, __खाता__, __LINE__, fmt, ##__VA_ARGS__)

#अगर_घोषित CONFIG_SND_DEBUG
/**
 * snd_prपूर्णांकd - debug prपूर्णांकk
 * @fmt: क्रमmat string
 *
 * Works like snd_prपूर्णांकk() क्रम debugging purposes.
 * Ignored when CONFIG_SND_DEBUG is not set.
 */
#घोषणा snd_prपूर्णांकd(fmt, ...) \
	__snd_prपूर्णांकk(1, __खाता__, __LINE__, fmt, ##__VA_ARGS__)
#घोषणा _snd_prपूर्णांकd(level, fmt, ...) \
	__snd_prपूर्णांकk(level, __खाता__, __LINE__, fmt, ##__VA_ARGS__)

/**
 * snd_BUG - give a BUG warning message and stack trace
 *
 * Calls WARN() अगर CONFIG_SND_DEBUG is set.
 * Ignored when CONFIG_SND_DEBUG is not set.
 */
#घोषणा snd_BUG()		WARN(1, "BUG?\n")

/**
 * snd_prपूर्णांकd_ratelimit - Suppress high rates of output when
 * 			  CONFIG_SND_DEBUG is enabled.
 */
#घोषणा snd_prपूर्णांकd_ratelimit() prपूर्णांकk_ratelimit()

/**
 * snd_BUG_ON - debugging check macro
 * @cond: condition to evaluate
 *
 * Has the same behavior as WARN_ON when CONFIG_SND_DEBUG is set,
 * otherwise just evaluates the conditional and वापसs the value.
 */
#घोषणा snd_BUG_ON(cond)	WARN_ON((cond))

#अन्यथा /* !CONFIG_SND_DEBUG */

__म_लिखो(1, 2)
अटल अंतरभूत व्योम snd_prपूर्णांकd(स्थिर अक्षर *क्रमmat, ...) अणुपूर्ण
__म_लिखो(2, 3)
अटल अंतरभूत व्योम _snd_prपूर्णांकd(पूर्णांक level, स्थिर अक्षर *क्रमmat, ...) अणुपूर्ण

#घोषणा snd_BUG()			करो अणु पूर्ण जबतक (0)

#घोषणा snd_BUG_ON(condition) (अणु \
	पूर्णांक __ret_warn_on = !!(condition); \
	unlikely(__ret_warn_on); \
पूर्ण)

अटल अंतरभूत bool snd_prपूर्णांकd_ratelimit(व्योम) अणु वापस false; पूर्ण

#पूर्ण_अगर /* CONFIG_SND_DEBUG */

#अगर_घोषित CONFIG_SND_DEBUG_VERBOSE
/**
 * snd_prपूर्णांकdd - debug prपूर्णांकk
 * @क्रमmat: क्रमmat string
 *
 * Works like snd_prपूर्णांकk() क्रम debugging purposes.
 * Ignored when CONFIG_SND_DEBUG_VERBOSE is not set.
 */
#घोषणा snd_prपूर्णांकdd(क्रमmat, ...) \
	__snd_prपूर्णांकk(2, __खाता__, __LINE__, क्रमmat, ##__VA_ARGS__)
#अन्यथा
__म_लिखो(1, 2)
अटल अंतरभूत व्योम snd_prपूर्णांकdd(स्थिर अक्षर *क्रमmat, ...) अणुपूर्ण
#पूर्ण_अगर


#घोषणा SNDRV_OSS_VERSION         ((3<<16)|(8<<8)|(1<<4)|(0))	/* 3.8.1a */

/* क्रम easier backward-porting */
#अगर IS_ENABLED(CONFIG_GAMEPORT)
#घोषणा gameport_set_dev_parent(gp,xdev) ((gp)->dev.parent = (xdev))
#घोषणा gameport_set_port_data(gp,r) ((gp)->port_data = (r))
#घोषणा gameport_get_port_data(gp) (gp)->port_data
#पूर्ण_अगर

/* PCI quirk list helper */
काष्ठा snd_pci_quirk अणु
	अचिन्हित लघु subvenकरोr;	/* PCI subvenकरोr ID */
	अचिन्हित लघु subdevice;	/* PCI subdevice ID */
	अचिन्हित लघु subdevice_mask;	/* biपंचांगask to match */
	पूर्णांक value;			/* value */
#अगर_घोषित CONFIG_SND_DEBUG_VERBOSE
	स्थिर अक्षर *name;		/* name of the device (optional) */
#पूर्ण_अगर
पूर्ण;

#घोषणा _SND_PCI_QUIRK_ID_MASK(vend, mask, dev)	\
	.subvenकरोr = (vend), .subdevice = (dev), .subdevice_mask = (mask)
#घोषणा _SND_PCI_QUIRK_ID(vend, dev) \
	_SND_PCI_QUIRK_ID_MASK(vend, 0xffff, dev)
#घोषणा SND_PCI_QUIRK_ID(vend,dev) अणु_SND_PCI_QUIRK_ID(vend, dev)पूर्ण
#अगर_घोषित CONFIG_SND_DEBUG_VERBOSE
#घोषणा SND_PCI_QUIRK(vend,dev,xname,val) \
	अणु_SND_PCI_QUIRK_ID(vend, dev), .value = (val), .name = (xname)पूर्ण
#घोषणा SND_PCI_QUIRK_VENDOR(vend, xname, val)			\
	अणु_SND_PCI_QUIRK_ID_MASK(vend, 0, 0), .value = (val), .name = (xname)पूर्ण
#घोषणा SND_PCI_QUIRK_MASK(vend, mask, dev, xname, val)			\
	अणु_SND_PCI_QUIRK_ID_MASK(vend, mask, dev),			\
			.value = (val), .name = (xname)पूर्ण
#घोषणा snd_pci_quirk_name(q)	((q)->name)
#अन्यथा
#घोषणा SND_PCI_QUIRK(vend,dev,xname,val) \
	अणु_SND_PCI_QUIRK_ID(vend, dev), .value = (val)पूर्ण
#घोषणा SND_PCI_QUIRK_MASK(vend, mask, dev, xname, val)			\
	अणु_SND_PCI_QUIRK_ID_MASK(vend, mask, dev), .value = (val)पूर्ण
#घोषणा SND_PCI_QUIRK_VENDOR(vend, xname, val)			\
	अणु_SND_PCI_QUIRK_ID_MASK(vend, 0, 0), .value = (val)पूर्ण
#घोषणा snd_pci_quirk_name(q)	""
#पूर्ण_अगर

#अगर_घोषित CONFIG_PCI
स्थिर काष्ठा snd_pci_quirk *
snd_pci_quirk_lookup(काष्ठा pci_dev *pci, स्थिर काष्ठा snd_pci_quirk *list);

स्थिर काष्ठा snd_pci_quirk *
snd_pci_quirk_lookup_id(u16 venकरोr, u16 device,
			स्थिर काष्ठा snd_pci_quirk *list);
#अन्यथा
अटल अंतरभूत स्थिर काष्ठा snd_pci_quirk *
snd_pci_quirk_lookup(काष्ठा pci_dev *pci, स्थिर काष्ठा snd_pci_quirk *list)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत स्थिर काष्ठा snd_pci_quirk *
snd_pci_quirk_lookup_id(u16 venकरोr, u16 device,
			स्थिर काष्ठा snd_pci_quirk *list)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __SOUND_CORE_H */
