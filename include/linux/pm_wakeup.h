<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  pm_wakeup.h - Power management wakeup पूर्णांकerface
 *
 *  Copyright (C) 2008 Alan Stern
 *  Copyright (C) 2010 Rafael J. Wysocki, Novell Inc.
 */

#अगर_अघोषित _LINUX_PM_WAKEUP_H
#घोषणा _LINUX_PM_WAKEUP_H

#अगर_अघोषित _DEVICE_H_
# error "please don't include this file directly"
#पूर्ण_अगर

#समावेश <linux/types.h>

काष्ठा wake_irq;

/**
 * काष्ठा wakeup_source - Representation of wakeup sources
 *
 * @name: Name of the wakeup source
 * @id: Wakeup source id
 * @entry: Wakeup source list entry
 * @lock: Wakeup source lock
 * @wakeirq: Optional device specअगरic wakeirq
 * @समयr: Wakeup समयr list
 * @समयr_expires: Wakeup समयr expiration
 * @total_समय: Total समय this wakeup source has been active.
 * @max_समय: Maximum समय this wakeup source has been continuously active.
 * @last_समय: Monotonic घड़ी when the wakeup source's was touched last समय.
 * @prevent_sleep_समय: Total समय this source has been preventing स्वतःsleep.
 * @event_count: Number of संकेतed wakeup events.
 * @active_count: Number of बार the wakeup source was activated.
 * @relax_count: Number of बार the wakeup source was deactivated.
 * @expire_count: Number of बार the wakeup source's समयout has expired.
 * @wakeup_count: Number of बार the wakeup source might पात suspend.
 * @dev: Struct device क्रम sysfs statistics about the wakeup source.
 * @active: Status of the wakeup source.
 * @स्वतःsleep_enabled: Autosleep is active, so update @prevent_sleep_समय.
 */
काष्ठा wakeup_source अणु
	स्थिर अक्षर 		*name;
	पूर्णांक			id;
	काष्ठा list_head	entry;
	spinlock_t		lock;
	काष्ठा wake_irq		*wakeirq;
	काष्ठा समयr_list	समयr;
	अचिन्हित दीर्घ		समयr_expires;
	kसमय_प्रकार total_समय;
	kसमय_प्रकार max_समय;
	kसमय_प्रकार last_समय;
	kसमय_प्रकार start_prevent_समय;
	kसमय_प्रकार prevent_sleep_समय;
	अचिन्हित दीर्घ		event_count;
	अचिन्हित दीर्घ		active_count;
	अचिन्हित दीर्घ		relax_count;
	अचिन्हित दीर्घ		expire_count;
	अचिन्हित दीर्घ		wakeup_count;
	काष्ठा device		*dev;
	bool			active:1;
	bool			स्वतःsleep_enabled:1;
पूर्ण;

#घोषणा क्रम_each_wakeup_source(ws) \
	क्रम ((ws) = wakeup_sources_walk_start();	\
	     (ws);					\
	     (ws) = wakeup_sources_walk_next((ws)))

#अगर_घोषित CONFIG_PM_SLEEP

/*
 * Changes to device_may_wakeup take effect on the next pm state change.
 */

अटल अंतरभूत bool device_can_wakeup(काष्ठा device *dev)
अणु
	वापस dev->घातer.can_wakeup;
पूर्ण

अटल अंतरभूत bool device_may_wakeup(काष्ठा device *dev)
अणु
	वापस dev->घातer.can_wakeup && !!dev->घातer.wakeup;
पूर्ण

अटल अंतरभूत bool device_wakeup_path(काष्ठा device *dev)
अणु
	वापस dev->घातer.wakeup_path;
पूर्ण

अटल अंतरभूत व्योम device_set_wakeup_path(काष्ठा device *dev)
अणु
	dev->घातer.wakeup_path = true;
पूर्ण

/* drivers/base/घातer/wakeup.c */
बाह्य काष्ठा wakeup_source *wakeup_source_create(स्थिर अक्षर *name);
बाह्य व्योम wakeup_source_destroy(काष्ठा wakeup_source *ws);
बाह्य व्योम wakeup_source_add(काष्ठा wakeup_source *ws);
बाह्य व्योम wakeup_source_हटाओ(काष्ठा wakeup_source *ws);
बाह्य काष्ठा wakeup_source *wakeup_source_रेजिस्टर(काष्ठा device *dev,
						    स्थिर अक्षर *name);
बाह्य व्योम wakeup_source_unरेजिस्टर(काष्ठा wakeup_source *ws);
बाह्य पूर्णांक wakeup_sources_पढ़ो_lock(व्योम);
बाह्य व्योम wakeup_sources_पढ़ो_unlock(पूर्णांक idx);
बाह्य काष्ठा wakeup_source *wakeup_sources_walk_start(व्योम);
बाह्य काष्ठा wakeup_source *wakeup_sources_walk_next(काष्ठा wakeup_source *ws);
बाह्य पूर्णांक device_wakeup_enable(काष्ठा device *dev);
बाह्य पूर्णांक device_wakeup_disable(काष्ठा device *dev);
बाह्य व्योम device_set_wakeup_capable(काष्ठा device *dev, bool capable);
बाह्य पूर्णांक device_init_wakeup(काष्ठा device *dev, bool val);
बाह्य पूर्णांक device_set_wakeup_enable(काष्ठा device *dev, bool enable);
बाह्य व्योम __pm_stay_awake(काष्ठा wakeup_source *ws);
बाह्य व्योम pm_stay_awake(काष्ठा device *dev);
बाह्य व्योम __pm_relax(काष्ठा wakeup_source *ws);
बाह्य व्योम pm_relax(काष्ठा device *dev);
बाह्य व्योम pm_wakeup_ws_event(काष्ठा wakeup_source *ws, अचिन्हित पूर्णांक msec, bool hard);
बाह्य व्योम pm_wakeup_dev_event(काष्ठा device *dev, अचिन्हित पूर्णांक msec, bool hard);

#अन्यथा /* !CONFIG_PM_SLEEP */

अटल अंतरभूत व्योम device_set_wakeup_capable(काष्ठा device *dev, bool capable)
अणु
	dev->घातer.can_wakeup = capable;
पूर्ण

अटल अंतरभूत bool device_can_wakeup(काष्ठा device *dev)
अणु
	वापस dev->घातer.can_wakeup;
पूर्ण

अटल अंतरभूत काष्ठा wakeup_source *wakeup_source_create(स्थिर अक्षर *name)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम wakeup_source_destroy(काष्ठा wakeup_source *ws) अणुपूर्ण

अटल अंतरभूत व्योम wakeup_source_add(काष्ठा wakeup_source *ws) अणुपूर्ण

अटल अंतरभूत व्योम wakeup_source_हटाओ(काष्ठा wakeup_source *ws) अणुपूर्ण

अटल अंतरभूत काष्ठा wakeup_source *wakeup_source_रेजिस्टर(काष्ठा device *dev,
							   स्थिर अक्षर *name)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम wakeup_source_unरेजिस्टर(काष्ठा wakeup_source *ws) अणुपूर्ण

अटल अंतरभूत पूर्णांक device_wakeup_enable(काष्ठा device *dev)
अणु
	dev->घातer.should_wakeup = true;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक device_wakeup_disable(काष्ठा device *dev)
अणु
	dev->घातer.should_wakeup = false;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक device_set_wakeup_enable(काष्ठा device *dev, bool enable)
अणु
	dev->घातer.should_wakeup = enable;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक device_init_wakeup(काष्ठा device *dev, bool val)
अणु
	device_set_wakeup_capable(dev, val);
	device_set_wakeup_enable(dev, val);
	वापस 0;
पूर्ण

अटल अंतरभूत bool device_may_wakeup(काष्ठा device *dev)
अणु
	वापस dev->घातer.can_wakeup && dev->घातer.should_wakeup;
पूर्ण

अटल अंतरभूत bool device_wakeup_path(काष्ठा device *dev)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत व्योम device_set_wakeup_path(काष्ठा device *dev) अणुपूर्ण

अटल अंतरभूत व्योम __pm_stay_awake(काष्ठा wakeup_source *ws) अणुपूर्ण

अटल अंतरभूत व्योम pm_stay_awake(काष्ठा device *dev) अणुपूर्ण

अटल अंतरभूत व्योम __pm_relax(काष्ठा wakeup_source *ws) अणुपूर्ण

अटल अंतरभूत व्योम pm_relax(काष्ठा device *dev) अणुपूर्ण

अटल अंतरभूत व्योम pm_wakeup_ws_event(काष्ठा wakeup_source *ws,
				      अचिन्हित पूर्णांक msec, bool hard) अणुपूर्ण

अटल अंतरभूत व्योम pm_wakeup_dev_event(काष्ठा device *dev, अचिन्हित पूर्णांक msec,
				       bool hard) अणुपूर्ण

#पूर्ण_अगर /* !CONFIG_PM_SLEEP */

अटल अंतरभूत व्योम __pm_wakeup_event(काष्ठा wakeup_source *ws, अचिन्हित पूर्णांक msec)
अणु
	वापस pm_wakeup_ws_event(ws, msec, false);
पूर्ण

अटल अंतरभूत व्योम pm_wakeup_event(काष्ठा device *dev, अचिन्हित पूर्णांक msec)
अणु
	वापस pm_wakeup_dev_event(dev, msec, false);
पूर्ण

अटल अंतरभूत व्योम pm_wakeup_hard_event(काष्ठा device *dev)
अणु
	वापस pm_wakeup_dev_event(dev, 0, true);
पूर्ण

#पूर्ण_अगर /* _LINUX_PM_WAKEUP_H */
