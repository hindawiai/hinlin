<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#समावेश <linux/suspend.h>
#समावेश <linux/suspend_ioctls.h>
#समावेश <linux/utsname.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/compiler.h>

काष्ठा swsusp_info अणु
	काष्ठा new_utsname	uts;
	u32			version_code;
	अचिन्हित दीर्घ		num_physpages;
	पूर्णांक			cpus;
	अचिन्हित दीर्घ		image_pages;
	अचिन्हित दीर्घ		pages;
	अचिन्हित दीर्घ		size;
पूर्ण __aligned(PAGE_SIZE);

#अगर_घोषित CONFIG_HIBERNATION
/* kernel/घातer/snapshot.c */
बाह्य व्योम __init hibernate_reserved_size_init(व्योम);
बाह्य व्योम __init hibernate_image_size_init(व्योम);

#अगर_घोषित CONFIG_ARCH_HIBERNATION_HEADER
/* Maximum size of architecture specअगरic data in a hibernation header */
#घोषणा MAX_ARCH_HEADER_SIZE	(माप(काष्ठा new_utsname) + 4)

बाह्य पूर्णांक arch_hibernation_header_save(व्योम *addr, अचिन्हित पूर्णांक max_size);
बाह्य पूर्णांक arch_hibernation_header_restore(व्योम *addr);

अटल अंतरभूत पूर्णांक init_header_complete(काष्ठा swsusp_info *info)
अणु
	वापस arch_hibernation_header_save(info, MAX_ARCH_HEADER_SIZE);
पूर्ण

अटल अंतरभूत स्थिर अक्षर *check_image_kernel(काष्ठा swsusp_info *info)
अणु
	वापस arch_hibernation_header_restore(info) ?
			"architecture specific data" : शून्य;
पूर्ण
#पूर्ण_अगर /* CONFIG_ARCH_HIBERNATION_HEADER */

बाह्य पूर्णांक hibernate_resume_nonboot_cpu_disable(व्योम);

/*
 * Keep some memory मुक्त so that I/O operations can succeed without paging
 * [Might this be more than 4 MB?]
 */
#घोषणा PAGES_FOR_IO	((4096 * 1024) >> PAGE_SHIFT)

/*
 * Keep 1 MB of memory मुक्त so that device drivers can allocate some pages in
 * their .suspend() routines without अवरोधing the suspend to disk.
 */
#घोषणा SPARE_PAGES	((1024 * 1024) >> PAGE_SHIFT)

यंत्रlinkage पूर्णांक swsusp_save(व्योम);

/* kernel/घातer/hibernate.c */
बाह्य bool मुक्तzer_test_करोne;

बाह्य पूर्णांक hibernation_snapshot(पूर्णांक platक्रमm_mode);
बाह्य पूर्णांक hibernation_restore(पूर्णांक platक्रमm_mode);
बाह्य पूर्णांक hibernation_platक्रमm_enter(व्योम);

#अगर_घोषित CONFIG_STRICT_KERNEL_RWX
/* kernel/घातer/snapshot.c */
बाह्य व्योम enable_restore_image_protection(व्योम);
#अन्यथा
अटल अंतरभूत व्योम enable_restore_image_protection(व्योम) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_STRICT_KERNEL_RWX */

#अन्यथा /* !CONFIG_HIBERNATION */

अटल अंतरभूत व्योम hibernate_reserved_size_init(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम hibernate_image_size_init(व्योम) अणुपूर्ण
#पूर्ण_अगर /* !CONFIG_HIBERNATION */

#घोषणा घातer_attr(_name) \
अटल काष्ठा kobj_attribute _name##_attr = अणु	\
	.attr	= अणु				\
		.name = __stringअगरy(_name),	\
		.mode = 0644,			\
	पूर्ण,					\
	.show	= _name##_show,			\
	.store	= _name##_store,		\
पूर्ण

#घोषणा घातer_attr_ro(_name) \
अटल काष्ठा kobj_attribute _name##_attr = अणु	\
	.attr	= अणु				\
		.name = __stringअगरy(_name),	\
		.mode = S_IRUGO,		\
	पूर्ण,					\
	.show	= _name##_show,			\
पूर्ण

/* Preferred image size in bytes (शेष 500 MB) */
बाह्य अचिन्हित दीर्घ image_size;
/* Size of memory reserved क्रम drivers (शेष SPARE_PAGES x PAGE_SIZE) */
बाह्य अचिन्हित दीर्घ reserved_size;
बाह्य पूर्णांक in_suspend;
बाह्य dev_t swsusp_resume_device;
बाह्य sector_t swsusp_resume_block;

बाह्य पूर्णांक create_basic_memory_biपंचांगaps(व्योम);
बाह्य व्योम मुक्त_basic_memory_biपंचांगaps(व्योम);
बाह्य पूर्णांक hibernate_pपुनः_स्मृतिate_memory(व्योम);

बाह्य व्योम clear_or_poison_मुक्त_pages(व्योम);

/**
 *	Auxiliary काष्ठाure used क्रम पढ़ोing the snapshot image data and
 *	metadata from and writing them to the list of page backup entries
 *	(PBEs) which is the मुख्य data काष्ठाure of swsusp.
 *
 *	Using काष्ठा snapshot_handle we can transfer the image, including its
 *	metadata, as a continuous sequence of bytes with the help of
 *	snapshot_पढ़ो_next() and snapshot_ग_लिखो_next().
 *
 *	The code that ग_लिखोs the image to a storage or transfers it to
 *	the user land is required to use snapshot_पढ़ो_next() क्रम this
 *	purpose and it should not make any assumptions regarding the पूर्णांकernal
 *	काष्ठाure of the image.  Similarly, the code that पढ़ोs the image from
 *	a storage or transfers it from the user land is required to use
 *	snapshot_ग_लिखो_next().
 *
 *	This may allow us to change the पूर्णांकernal काष्ठाure of the image
 *	in the future with considerably less efक्रमt.
 */

काष्ठा snapshot_handle अणु
	अचिन्हित पूर्णांक	cur;	/* number of the block of PAGE_SIZE bytes the
				 * next operation will refer to (ie. current)
				 */
	व्योम		*buffer;	/* address of the block to पढ़ो from
					 * or ग_लिखो to
					 */
	पूर्णांक		sync_पढ़ो;	/* Set to one to notअगरy the caller of
					 * snapshot_ग_लिखो_next() that it may
					 * need to call रुको_on_bio_chain()
					 */
पूर्ण;

/* This macro वापसs the address from/to which the caller of
 * snapshot_पढ़ो_next()/snapshot_ग_लिखो_next() is allowed to
 * पढ़ो/ग_लिखो data after the function वापसs
 */
#घोषणा data_of(handle)	((handle).buffer)

बाह्य अचिन्हित पूर्णांक snapshot_additional_pages(काष्ठा zone *zone);
बाह्य अचिन्हित दीर्घ snapshot_get_image_size(व्योम);
बाह्य पूर्णांक snapshot_पढ़ो_next(काष्ठा snapshot_handle *handle);
बाह्य पूर्णांक snapshot_ग_लिखो_next(काष्ठा snapshot_handle *handle);
बाह्य व्योम snapshot_ग_लिखो_finalize(काष्ठा snapshot_handle *handle);
बाह्य पूर्णांक snapshot_image_loaded(काष्ठा snapshot_handle *handle);

बाह्य bool hibernate_acquire(व्योम);
बाह्य व्योम hibernate_release(व्योम);

बाह्य sector_t alloc_swapdev_block(पूर्णांक swap);
बाह्य व्योम मुक्त_all_swap_pages(पूर्णांक swap);
बाह्य पूर्णांक swsusp_swap_in_use(व्योम);

/*
 * Flags that can be passed from the hibernatig hernel to the "boot" kernel in
 * the image header.
 */
#घोषणा SF_PLATFORM_MODE	1
#घोषणा SF_NOCOMPRESS_MODE	2
#घोषणा SF_CRC32_MODE	        4

/* kernel/घातer/hibernate.c */
बाह्य पूर्णांक swsusp_check(व्योम);
बाह्य व्योम swsusp_मुक्त(व्योम);
बाह्य पूर्णांक swsusp_पढ़ो(अचिन्हित पूर्णांक *flags_p);
बाह्य पूर्णांक swsusp_ग_लिखो(अचिन्हित पूर्णांक flags);
बाह्य व्योम swsusp_बंद(भ_शेषe_t);
#अगर_घोषित CONFIG_SUSPEND
बाह्य पूर्णांक swsusp_unmark(व्योम);
#पूर्ण_अगर

काष्ठा __kernel_old_समयval;
/* kernel/घातer/swsusp.c */
बाह्य व्योम swsusp_show_speed(kसमय_प्रकार, kसमय_प्रकार, अचिन्हित पूर्णांक, अक्षर *);

#अगर_घोषित CONFIG_SUSPEND
/* kernel/घातer/suspend.c */
बाह्य स्थिर अक्षर * स्थिर pm_labels[];
बाह्य स्थिर अक्षर *pm_states[];
बाह्य स्थिर अक्षर *mem_sleep_states[];

बाह्य पूर्णांक suspend_devices_and_enter(suspend_state_t state);
#अन्यथा /* !CONFIG_SUSPEND */
#घोषणा mem_sleep_current	PM_SUSPEND_ON

अटल अंतरभूत पूर्णांक suspend_devices_and_enter(suspend_state_t state)
अणु
	वापस -ENOSYS;
पूर्ण
#पूर्ण_अगर /* !CONFIG_SUSPEND */

#अगर_घोषित CONFIG_PM_TEST_SUSPEND
/* kernel/घातer/suspend_test.c */
बाह्य व्योम suspend_test_start(व्योम);
बाह्य व्योम suspend_test_finish(स्थिर अक्षर *label);
#अन्यथा /* !CONFIG_PM_TEST_SUSPEND */
अटल अंतरभूत व्योम suspend_test_start(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम suspend_test_finish(स्थिर अक्षर *label) अणुपूर्ण
#पूर्ण_अगर /* !CONFIG_PM_TEST_SUSPEND */

#अगर_घोषित CONFIG_PM_SLEEP
/* kernel/घातer/मुख्य.c */
बाह्य पूर्णांक pm_notअगरier_call_chain_robust(अचिन्हित दीर्घ val_up, अचिन्हित दीर्घ val_करोwn);
बाह्य पूर्णांक pm_notअगरier_call_chain(अचिन्हित दीर्घ val);
#पूर्ण_अगर

#अगर_घोषित CONFIG_HIGHMEM
पूर्णांक restore_highmem(व्योम);
#अन्यथा
अटल अंतरभूत अचिन्हित पूर्णांक count_highmem_pages(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक restore_highmem(व्योम) अणु वापस 0; पूर्ण
#पूर्ण_अगर

/*
 * Suspend test levels
 */
क्रमागत अणु
	/* keep first */
	TEST_NONE,
	TEST_CORE,
	TEST_CPUS,
	TEST_PLATFORM,
	TEST_DEVICES,
	TEST_FREEZER,
	/* keep last */
	__TEST_AFTER_LAST
पूर्ण;

#घोषणा TEST_FIRST	TEST_NONE
#घोषणा TEST_MAX	(__TEST_AFTER_LAST - 1)

#अगर_घोषित CONFIG_PM_SLEEP_DEBUG
बाह्य पूर्णांक pm_test_level;
#अन्यथा
#घोषणा pm_test_level	(TEST_NONE)
#पूर्ण_अगर

#अगर_घोषित CONFIG_SUSPEND_FREEZER
अटल अंतरभूत पूर्णांक suspend_मुक्तze_processes(व्योम)
अणु
	पूर्णांक error;

	error = मुक्तze_processes();
	/*
	 * मुक्तze_processes() स्वतःmatically thaws every task अगर मुक्तzing
	 * fails. So we need not करो anything extra upon error.
	 */
	अगर (error)
		वापस error;

	error = मुक्तze_kernel_thपढ़ोs();
	/*
	 * मुक्तze_kernel_thपढ़ोs() thaws only kernel thपढ़ोs upon मुक्तzing
	 * failure. So we have to thaw the userspace tasks ourselves.
	 */
	अगर (error)
		thaw_processes();

	वापस error;
पूर्ण

अटल अंतरभूत व्योम suspend_thaw_processes(व्योम)
अणु
	thaw_processes();
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक suspend_मुक्तze_processes(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम suspend_thaw_processes(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM_AUTOSLEEP

/* kernel/घातer/स्वतःsleep.c */
बाह्य पूर्णांक pm_स्वतःsleep_init(व्योम);
बाह्य पूर्णांक pm_स्वतःsleep_lock(व्योम);
बाह्य व्योम pm_स्वतःsleep_unlock(व्योम);
बाह्य suspend_state_t pm_स्वतःsleep_state(व्योम);
बाह्य पूर्णांक pm_स्वतःsleep_set_state(suspend_state_t state);

#अन्यथा /* !CONFIG_PM_AUTOSLEEP */

अटल अंतरभूत पूर्णांक pm_स्वतःsleep_init(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक pm_स्वतःsleep_lock(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम pm_स्वतःsleep_unlock(व्योम) अणुपूर्ण
अटल अंतरभूत suspend_state_t pm_स्वतःsleep_state(व्योम) अणु वापस PM_SUSPEND_ON; पूर्ण

#पूर्ण_अगर /* !CONFIG_PM_AUTOSLEEP */

#अगर_घोषित CONFIG_PM_WAKELOCKS

/* kernel/घातer/wakelock.c */
बाह्य sमाप_प्रकार pm_show_wakelocks(अक्षर *buf, bool show_active);
बाह्य पूर्णांक pm_wake_lock(स्थिर अक्षर *buf);
बाह्य पूर्णांक pm_wake_unlock(स्थिर अक्षर *buf);

#पूर्ण_अगर /* !CONFIG_PM_WAKELOCKS */
