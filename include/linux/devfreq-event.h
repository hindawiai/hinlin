<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * devfreq-event: a framework to provide raw data and events of devfreq devices
 *
 * Copyright (C) 2014 Samsung Electronics
 * Author: Chanwoo Choi <cw00.choi@samsung.com>
 */

#अगर_अघोषित __LINUX_DEVFREQ_EVENT_H__
#घोषणा __LINUX_DEVFREQ_EVENT_H__

#समावेश <linux/device.h>

/**
 * काष्ठा devfreq_event_dev - the devfreq-event device
 *
 * @node	: Contain the devfreq-event device that have been रेजिस्टरed.
 * @dev		: the device रेजिस्टरed by devfreq-event class. dev.parent is
 *		  the device using devfreq-event.
 * @lock	: a mutex to protect accessing devfreq-event.
 * @enable_count: the number of enable function have been called.
 * @desc	: the description क्रम devfreq-event device.
 *
 * This काष्ठाure contains devfreq-event device inक्रमmation.
 */
काष्ठा devfreq_event_dev अणु
	काष्ठा list_head node;

	काष्ठा device dev;
	काष्ठा mutex lock;
	u32 enable_count;

	स्थिर काष्ठा devfreq_event_desc *desc;
पूर्ण;

/**
 * काष्ठा devfreq_event_data - the devfreq-event data
 *
 * @load_count	: load count of devfreq-event device क्रम the given period.
 * @total_count	: total count of devfreq-event device क्रम the given period.
 *		  each count may represent a घड़ी cycle, a समय unit
 *		  (ns/us/...), or anything the device driver wants.
 *		  Generally, utilization is load_count / total_count.
 *
 * This काष्ठाure contains the data of devfreq-event device क्रम polling period.
 */
काष्ठा devfreq_event_data अणु
	अचिन्हित दीर्घ load_count;
	अचिन्हित दीर्घ total_count;
पूर्ण;

/**
 * काष्ठा devfreq_event_ops - the operations of devfreq-event device
 *
 * @enable	: Enable the devfreq-event device.
 * @disable	: Disable the devfreq-event device.
 * @reset	: Reset all setting of the devfreq-event device.
 * @set_event	: Set the specअगरic event type क्रम the devfreq-event device.
 * @get_event	: Get the result of the devfreq-event devie with specअगरic
 *		  event type.
 *
 * This काष्ठाure contains devfreq-event device operations which can be
 * implemented by devfreq-event device drivers.
 */
काष्ठा devfreq_event_ops अणु
	/* Optional functions */
	पूर्णांक (*enable)(काष्ठा devfreq_event_dev *edev);
	पूर्णांक (*disable)(काष्ठा devfreq_event_dev *edev);
	पूर्णांक (*reset)(काष्ठा devfreq_event_dev *edev);

	/* Mandatory functions */
	पूर्णांक (*set_event)(काष्ठा devfreq_event_dev *edev);
	पूर्णांक (*get_event)(काष्ठा devfreq_event_dev *edev,
			 काष्ठा devfreq_event_data *edata);
पूर्ण;

/**
 * काष्ठा devfreq_event_desc - the descriptor of devfreq-event device
 *
 * @name	: the name of devfreq-event device.
 * @event_type	: the type of the event determined and used by driver
 * @driver_data	: the निजी data क्रम devfreq-event driver.
 * @ops		: the operation to control devfreq-event device.
 *
 * Each devfreq-event device is described with a this काष्ठाure.
 * This काष्ठाure contains the various data क्रम devfreq-event device.
 * The event_type describes what is going to be counted in the रेजिस्टर.
 * It might choose to count e.g. पढ़ो requests, ग_लिखो data in bytes, etc.
 * The full supported list of types is present in specyfic header in:
 * include/dt-bindings/pmu/.
 */
काष्ठा devfreq_event_desc अणु
	स्थिर अक्षर *name;
	u32 event_type;
	व्योम *driver_data;

	स्थिर काष्ठा devfreq_event_ops *ops;
पूर्ण;

#अगर defined(CONFIG_PM_DEVFREQ_EVENT)
बाह्य पूर्णांक devfreq_event_enable_edev(काष्ठा devfreq_event_dev *edev);
बाह्य पूर्णांक devfreq_event_disable_edev(काष्ठा devfreq_event_dev *edev);
बाह्य bool devfreq_event_is_enabled(काष्ठा devfreq_event_dev *edev);
बाह्य पूर्णांक devfreq_event_set_event(काष्ठा devfreq_event_dev *edev);
बाह्य पूर्णांक devfreq_event_get_event(काष्ठा devfreq_event_dev *edev,
				काष्ठा devfreq_event_data *edata);
बाह्य पूर्णांक devfreq_event_reset_event(काष्ठा devfreq_event_dev *edev);
बाह्य काष्ठा devfreq_event_dev *devfreq_event_get_edev_by_phandle(
				काष्ठा device *dev,
				स्थिर अक्षर *phandle_name,
				पूर्णांक index);
बाह्य पूर्णांक devfreq_event_get_edev_count(काष्ठा device *dev,
				स्थिर अक्षर *phandle_name);
बाह्य काष्ठा devfreq_event_dev *devfreq_event_add_edev(काष्ठा device *dev,
				काष्ठा devfreq_event_desc *desc);
बाह्य पूर्णांक devfreq_event_हटाओ_edev(काष्ठा devfreq_event_dev *edev);
बाह्य काष्ठा devfreq_event_dev *devm_devfreq_event_add_edev(काष्ठा device *dev,
				काष्ठा devfreq_event_desc *desc);
बाह्य व्योम devm_devfreq_event_हटाओ_edev(काष्ठा device *dev,
				काष्ठा devfreq_event_dev *edev);
अटल अंतरभूत व्योम *devfreq_event_get_drvdata(काष्ठा devfreq_event_dev *edev)
अणु
	वापस edev->desc->driver_data;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक devfreq_event_enable_edev(काष्ठा devfreq_event_dev *edev)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक devfreq_event_disable_edev(काष्ठा devfreq_event_dev *edev)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत bool devfreq_event_is_enabled(काष्ठा devfreq_event_dev *edev)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत पूर्णांक devfreq_event_set_event(काष्ठा devfreq_event_dev *edev)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक devfreq_event_get_event(काष्ठा devfreq_event_dev *edev,
					काष्ठा devfreq_event_data *edata)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक devfreq_event_reset_event(काष्ठा devfreq_event_dev *edev)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत काष्ठा devfreq_event_dev *devfreq_event_get_edev_by_phandle(
					काष्ठा device *dev,
					स्थिर अक्षर *phandle_name,
					पूर्णांक index)
अणु
	वापस ERR_PTR(-EINVAL);
पूर्ण

अटल अंतरभूत पूर्णांक devfreq_event_get_edev_count(काष्ठा device *dev,
					स्थिर अक्षर *phandle_name)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत काष्ठा devfreq_event_dev *devfreq_event_add_edev(काष्ठा device *dev,
					काष्ठा devfreq_event_desc *desc)
अणु
	वापस ERR_PTR(-EINVAL);
पूर्ण

अटल अंतरभूत पूर्णांक devfreq_event_हटाओ_edev(काष्ठा devfreq_event_dev *edev)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत काष्ठा devfreq_event_dev *devm_devfreq_event_add_edev(
					काष्ठा device *dev,
					काष्ठा devfreq_event_desc *desc)
अणु
	वापस ERR_PTR(-EINVAL);
पूर्ण

अटल अंतरभूत व्योम devm_devfreq_event_हटाओ_edev(काष्ठा device *dev,
					काष्ठा devfreq_event_dev *edev)
अणु
पूर्ण

अटल अंतरभूत व्योम *devfreq_event_get_drvdata(काष्ठा devfreq_event_dev *edev)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_DEVFREQ_EVENT */

#पूर्ण_अगर /* __LINUX_DEVFREQ_EVENT_H__ */
