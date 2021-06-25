<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#समावेश <linux/pm_qos.h>

अटल अंतरभूत व्योम device_pm_init_common(काष्ठा device *dev)
अणु
	अगर (!dev->घातer.early_init) अणु
		spin_lock_init(&dev->घातer.lock);
		dev->घातer.qos = शून्य;
		dev->घातer.early_init = true;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_PM

अटल अंतरभूत व्योम pm_runसमय_early_init(काष्ठा device *dev)
अणु
	dev->घातer.disable_depth = 1;
	device_pm_init_common(dev);
पूर्ण

बाह्य व्योम pm_runसमय_init(काष्ठा device *dev);
बाह्य व्योम pm_runसमय_reinit(काष्ठा device *dev);
बाह्य व्योम pm_runसमय_हटाओ(काष्ठा device *dev);
बाह्य u64 pm_runसमय_active_समय(काष्ठा device *dev);

#घोषणा WAKE_IRQ_DEDICATED_ALLOCATED	BIT(0)
#घोषणा WAKE_IRQ_DEDICATED_MANAGED	BIT(1)
#घोषणा WAKE_IRQ_DEDICATED_MASK		(WAKE_IRQ_DEDICATED_ALLOCATED | \
					 WAKE_IRQ_DEDICATED_MANAGED)

काष्ठा wake_irq अणु
	काष्ठा device *dev;
	अचिन्हित पूर्णांक status;
	पूर्णांक irq;
	स्थिर अक्षर *name;
पूर्ण;

बाह्य व्योम dev_pm_arm_wake_irq(काष्ठा wake_irq *wirq);
बाह्य व्योम dev_pm_disarm_wake_irq(काष्ठा wake_irq *wirq);
बाह्य व्योम dev_pm_enable_wake_irq_check(काष्ठा device *dev,
					 bool can_change_status);
बाह्य व्योम dev_pm_disable_wake_irq_check(काष्ठा device *dev);

#अगर_घोषित CONFIG_PM_SLEEP

बाह्य व्योम device_wakeup_attach_irq(काष्ठा device *dev, काष्ठा wake_irq *wakeirq);
बाह्य व्योम device_wakeup_detach_irq(काष्ठा device *dev);
बाह्य व्योम device_wakeup_arm_wake_irqs(व्योम);
बाह्य व्योम device_wakeup_disarm_wake_irqs(व्योम);

#अन्यथा

अटल अंतरभूत व्योम device_wakeup_attach_irq(काष्ठा device *dev,
					    काष्ठा wake_irq *wakeirq) अणुपूर्ण

अटल अंतरभूत व्योम device_wakeup_detach_irq(काष्ठा device *dev)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_PM_SLEEP */

/*
 * sysfs.c
 */

बाह्य पूर्णांक dpm_sysfs_add(काष्ठा device *dev);
बाह्य व्योम dpm_sysfs_हटाओ(काष्ठा device *dev);
बाह्य व्योम rpm_sysfs_हटाओ(काष्ठा device *dev);
बाह्य पूर्णांक wakeup_sysfs_add(काष्ठा device *dev);
बाह्य व्योम wakeup_sysfs_हटाओ(काष्ठा device *dev);
बाह्य पूर्णांक pm_qos_sysfs_add_resume_latency(काष्ठा device *dev);
बाह्य व्योम pm_qos_sysfs_हटाओ_resume_latency(काष्ठा device *dev);
बाह्य पूर्णांक pm_qos_sysfs_add_flags(काष्ठा device *dev);
बाह्य व्योम pm_qos_sysfs_हटाओ_flags(काष्ठा device *dev);
बाह्य पूर्णांक pm_qos_sysfs_add_latency_tolerance(काष्ठा device *dev);
बाह्य व्योम pm_qos_sysfs_हटाओ_latency_tolerance(काष्ठा device *dev);
बाह्य पूर्णांक dpm_sysfs_change_owner(काष्ठा device *dev, kuid_t kuid, kgid_t kgid);

#अन्यथा /* CONFIG_PM */

अटल अंतरभूत व्योम pm_runसमय_early_init(काष्ठा device *dev)
अणु
	device_pm_init_common(dev);
पूर्ण

अटल अंतरभूत व्योम pm_runसमय_init(काष्ठा device *dev) अणुपूर्ण
अटल अंतरभूत व्योम pm_runसमय_reinit(काष्ठा device *dev) अणुपूर्ण
अटल अंतरभूत व्योम pm_runसमय_हटाओ(काष्ठा device *dev) अणुपूर्ण

अटल अंतरभूत पूर्णांक dpm_sysfs_add(काष्ठा device *dev) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम dpm_sysfs_हटाओ(काष्ठा device *dev) अणुपूर्ण
अटल अंतरभूत पूर्णांक dpm_sysfs_change_owner(काष्ठा device *dev, kuid_t kuid,
					 kgid_t kgid) अणु वापस 0; पूर्ण

#पूर्ण_अगर

#अगर_घोषित CONFIG_PM_SLEEP

/* kernel/घातer/मुख्य.c */
बाह्य पूर्णांक pm_async_enabled;

/* drivers/base/घातer/मुख्य.c */
बाह्य काष्ठा list_head dpm_list;	/* The active device list */

अटल अंतरभूत काष्ठा device *to_device(काष्ठा list_head *entry)
अणु
	वापस container_of(entry, काष्ठा device, घातer.entry);
पूर्ण

बाह्य व्योम device_pm_sleep_init(काष्ठा device *dev);
बाह्य व्योम device_pm_add(काष्ठा device *);
बाह्य व्योम device_pm_हटाओ(काष्ठा device *);
बाह्य व्योम device_pm_move_beक्रमe(काष्ठा device *, काष्ठा device *);
बाह्य व्योम device_pm_move_after(काष्ठा device *, काष्ठा device *);
बाह्य व्योम device_pm_move_last(काष्ठा device *);
बाह्य व्योम device_pm_check_callbacks(काष्ठा device *dev);

अटल अंतरभूत bool device_pm_initialized(काष्ठा device *dev)
अणु
	वापस dev->घातer.in_dpm_list;
पूर्ण

/* drivers/base/घातer/wakeup_stats.c */
बाह्य पूर्णांक wakeup_source_sysfs_add(काष्ठा device *parent,
				   काष्ठा wakeup_source *ws);
बाह्य व्योम wakeup_source_sysfs_हटाओ(काष्ठा wakeup_source *ws);

बाह्य पूर्णांक pm_wakeup_source_sysfs_add(काष्ठा device *parent);

#अन्यथा /* !CONFIG_PM_SLEEP */

अटल अंतरभूत व्योम device_pm_sleep_init(काष्ठा device *dev) अणुपूर्ण

अटल अंतरभूत व्योम device_pm_add(काष्ठा device *dev) अणुपूर्ण

अटल अंतरभूत व्योम device_pm_हटाओ(काष्ठा device *dev)
अणु
	pm_runसमय_हटाओ(dev);
पूर्ण

अटल अंतरभूत व्योम device_pm_move_beक्रमe(काष्ठा device *deva,
					 काष्ठा device *devb) अणुपूर्ण
अटल अंतरभूत व्योम device_pm_move_after(काष्ठा device *deva,
					काष्ठा device *devb) अणुपूर्ण
अटल अंतरभूत व्योम device_pm_move_last(काष्ठा device *dev) अणुपूर्ण

अटल अंतरभूत व्योम device_pm_check_callbacks(काष्ठा device *dev) अणुपूर्ण

अटल अंतरभूत bool device_pm_initialized(काष्ठा device *dev)
अणु
	वापस device_is_रेजिस्टरed(dev);
पूर्ण

अटल अंतरभूत पूर्णांक pm_wakeup_source_sysfs_add(काष्ठा device *parent)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर /* !CONFIG_PM_SLEEP */

अटल अंतरभूत व्योम device_pm_init(काष्ठा device *dev)
अणु
	device_pm_init_common(dev);
	device_pm_sleep_init(dev);
	pm_runसमय_init(dev);
पूर्ण
