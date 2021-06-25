<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * cpuidle.h - The पूर्णांकernal header file
 */

#अगर_अघोषित __DRIVER_CPUIDLE_H
#घोषणा __DRIVER_CPUIDLE_H

/* For पूर्णांकernal use only */
बाह्य अक्षर param_governor[];
बाह्य काष्ठा cpuidle_governor *cpuidle_curr_governor;
बाह्य काष्ठा cpuidle_governor *cpuidle_prev_governor;
बाह्य काष्ठा list_head cpuidle_governors;
बाह्य काष्ठा list_head cpuidle_detected_devices;
बाह्य काष्ठा mutex cpuidle_lock;
बाह्य spinlock_t cpuidle_driver_lock;
बाह्य पूर्णांक cpuidle_disabled(व्योम);
बाह्य पूर्णांक cpuidle_enter_state(काष्ठा cpuidle_device *dev,
		काष्ठा cpuidle_driver *drv, पूर्णांक next_state);

/* idle loop */
बाह्य व्योम cpuidle_install_idle_handler(व्योम);
बाह्य व्योम cpuidle_uninstall_idle_handler(व्योम);

/* governors */
बाह्य काष्ठा cpuidle_governor *cpuidle_find_governor(स्थिर अक्षर *str);
बाह्य पूर्णांक cpuidle_चयन_governor(काष्ठा cpuidle_governor *gov);

/* sysfs */

काष्ठा device;

बाह्य पूर्णांक cpuidle_add_पूर्णांकerface(काष्ठा device *dev);
बाह्य व्योम cpuidle_हटाओ_पूर्णांकerface(काष्ठा device *dev);
बाह्य पूर्णांक cpuidle_add_device_sysfs(काष्ठा cpuidle_device *device);
बाह्य व्योम cpuidle_हटाओ_device_sysfs(काष्ठा cpuidle_device *device);
बाह्य पूर्णांक cpuidle_add_sysfs(काष्ठा cpuidle_device *dev);
बाह्य व्योम cpuidle_हटाओ_sysfs(काष्ठा cpuidle_device *dev);

#अगर_घोषित CONFIG_ARCH_NEEDS_CPU_IDLE_COUPLED
bool cpuidle_state_is_coupled(काष्ठा cpuidle_driver *drv, पूर्णांक state);
पूर्णांक cpuidle_coupled_state_verअगरy(काष्ठा cpuidle_driver *drv);
पूर्णांक cpuidle_enter_state_coupled(काष्ठा cpuidle_device *dev,
		काष्ठा cpuidle_driver *drv, पूर्णांक next_state);
पूर्णांक cpuidle_coupled_रेजिस्टर_device(काष्ठा cpuidle_device *dev);
व्योम cpuidle_coupled_unरेजिस्टर_device(काष्ठा cpuidle_device *dev);
#अन्यथा
अटल अंतरभूत
bool cpuidle_state_is_coupled(काष्ठा cpuidle_driver *drv, पूर्णांक state)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत पूर्णांक cpuidle_coupled_state_verअगरy(काष्ठा cpuidle_driver *drv)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक cpuidle_enter_state_coupled(काष्ठा cpuidle_device *dev,
		काष्ठा cpuidle_driver *drv, पूर्णांक next_state)
अणु
	वापस -1;
पूर्ण

अटल अंतरभूत पूर्णांक cpuidle_coupled_रेजिस्टर_device(काष्ठा cpuidle_device *dev)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम cpuidle_coupled_unरेजिस्टर_device(काष्ठा cpuidle_device *dev)
अणु
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __DRIVER_CPUIDLE_H */
