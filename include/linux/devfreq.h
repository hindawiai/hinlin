<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * devfreq: Generic Dynamic Voltage and Frequency Scaling (DVFS) Framework
 *	    क्रम Non-CPU Devices.
 *
 * Copyright (C) 2011 Samsung Electronics
 *	MyungJoo Ham <myungjoo.ham@samsung.com>
 */

#अगर_अघोषित __LINUX_DEVFREQ_H__
#घोषणा __LINUX_DEVFREQ_H__

#समावेश <linux/device.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/pm_opp.h>
#समावेश <linux/pm_qos.h>

/* DEVFREQ governor name */
#घोषणा DEVFREQ_GOV_SIMPLE_ONDEMAND	"simple_ondemand"
#घोषणा DEVFREQ_GOV_PERFORMANCE		"performance"
#घोषणा DEVFREQ_GOV_POWERSAVE		"powersave"
#घोषणा DEVFREQ_GOV_USERSPACE		"userspace"
#घोषणा DEVFREQ_GOV_PASSIVE		"passive"

/* DEVFREQ notअगरier पूर्णांकerface */
#घोषणा DEVFREQ_TRANSITION_NOTIFIER	(0)

/* Transition notअगरiers of DEVFREQ_TRANSITION_NOTIFIER */
#घोषणा	DEVFREQ_PRECHANGE		(0)
#घोषणा DEVFREQ_POSTCHANGE		(1)

/* DEVFREQ work समयrs */
क्रमागत devfreq_समयr अणु
	DEVFREQ_TIMER_DEFERRABLE = 0,
	DEVFREQ_TIMER_DELAYED,
	DEVFREQ_TIMER_NUM,
पूर्ण;

काष्ठा devfreq;
काष्ठा devfreq_governor;
काष्ठा thermal_cooling_device;

/**
 * काष्ठा devfreq_dev_status - Data given from devfreq user device to
 *			     governors. Represents the perक्रमmance
 *			     statistics.
 * @total_समय:		The total समय represented by this instance of
 *			devfreq_dev_status
 * @busy_समय:		The समय that the device was working among the
 *			total_समय.
 * @current_frequency:	The operating frequency.
 * @निजी_data:	An entry not specअगरied by the devfreq framework.
 *			A device and a specअगरic governor may have their
 *			own protocol with निजी_data. However, because
 *			this is governor-specअगरic, a governor using this
 *			will be only compatible with devices aware of it.
 */
काष्ठा devfreq_dev_status अणु
	/* both since the last measure */
	अचिन्हित दीर्घ total_समय;
	अचिन्हित दीर्घ busy_समय;
	अचिन्हित दीर्घ current_frequency;
	व्योम *निजी_data;
पूर्ण;

/*
 * The resulting frequency should be at most this. (this bound is the
 * least upper bound; thus, the resulting freq should be lower or same)
 * If the flag is not set, the resulting frequency should be at most the
 * bound (greatest lower bound)
 */
#घोषणा DEVFREQ_FLAG_LEAST_UPPER_BOUND		0x1

/**
 * काष्ठा devfreq_dev_profile - Devfreq's user device profile
 * @initial_freq:	The operating frequency when devfreq_add_device() is
 *			called.
 * @polling_ms:		The polling पूर्णांकerval in ms. 0 disables polling.
 * @समयr:		Timer type is either deferrable or delayed समयr.
 * @target:		The device should set its operating frequency at
 *			freq or lowest-upper-than-freq value. If freq is
 *			higher than any operable frequency, set maximum.
 *			Beक्रमe वापसing, target function should set
 *			freq at the current frequency.
 *			The "flags" parameter's possible values are
 *			explained above with "DEVFREQ_FLAG_*" macros.
 * @get_dev_status:	The device should provide the current perक्रमmance
 *			status to devfreq. Governors are recommended not to
 *			use this directly. Instead, governors are recommended
 *			to use devfreq_update_stats() aदीर्घ with
 *			devfreq.last_status.
 * @get_cur_freq:	The device should provide the current frequency
 *			at which it is operating.
 * @निकास:		An optional callback that is called when devfreq
 *			is removing the devfreq object due to error or
 *			from devfreq_हटाओ_device() call. If the user
 *			has रेजिस्टरed devfreq->nb at a notअगरier-head,
 *			this is the समय to unरेजिस्टर it.
 * @freq_table:		Optional list of frequencies to support statistics
 *			and freq_table must be generated in ascending order.
 * @max_state:		The size of freq_table.
 *
 * @is_cooling_device: A self-explanatory boolean giving the device a
 *                     cooling effect property.
 */
काष्ठा devfreq_dev_profile अणु
	अचिन्हित दीर्घ initial_freq;
	अचिन्हित पूर्णांक polling_ms;
	क्रमागत devfreq_समयr समयr;
	bool is_cooling_device;

	पूर्णांक (*target)(काष्ठा device *dev, अचिन्हित दीर्घ *freq, u32 flags);
	पूर्णांक (*get_dev_status)(काष्ठा device *dev,
			      काष्ठा devfreq_dev_status *stat);
	पूर्णांक (*get_cur_freq)(काष्ठा device *dev, अचिन्हित दीर्घ *freq);
	व्योम (*निकास)(काष्ठा device *dev);

	अचिन्हित दीर्घ *freq_table;
	अचिन्हित पूर्णांक max_state;
पूर्ण;

/**
 * काष्ठा devfreq_stats - Statistics of devfreq device behavior
 * @total_trans:	Number of devfreq transitions.
 * @trans_table:	Statistics of devfreq transitions.
 * @समय_in_state:	Statistics of devfreq states.
 * @last_update:	The last समय stats were updated.
 */
काष्ठा devfreq_stats अणु
	अचिन्हित पूर्णांक total_trans;
	अचिन्हित पूर्णांक *trans_table;
	u64 *समय_in_state;
	u64 last_update;
पूर्ण;

/**
 * काष्ठा devfreq - Device devfreq काष्ठाure
 * @node:	list node - contains the devices with devfreq that have been
 *		रेजिस्टरed.
 * @lock:	a mutex to protect accessing devfreq.
 * @dev:	device रेजिस्टरed by devfreq class. dev.parent is the device
 *		using devfreq.
 * @profile:	device-specअगरic devfreq profile
 * @governor:	method how to choose frequency based on the usage.
 * @opp_table:	Reference to OPP table of dev.parent, अगर one exists.
 * @nb:		notअगरier block used to notअगरy devfreq object that it should
 *		reevaluate operable frequencies. Devfreq users may use
 *		devfreq.nb to the corresponding रेजिस्टर notअगरier call chain.
 * @work:	delayed work क्रम load monitoring.
 * @previous_freq:	previously configured frequency value.
 * @last_status:	devfreq user device info, perक्रमmance statistics
 * @data:	Private data of the governor. The devfreq framework करोes not
 *		touch this.
 * @user_min_freq_req:	PM QoS minimum frequency request from user (via sysfs)
 * @user_max_freq_req:	PM QoS maximum frequency request from user (via sysfs)
 * @scaling_min_freq:	Limit minimum frequency requested by OPP पूर्णांकerface
 * @scaling_max_freq:	Limit maximum frequency requested by OPP पूर्णांकerface
 * @stop_polling:	 devfreq polling status of a device.
 * @suspend_freq:	 frequency of a device set during suspend phase.
 * @resume_freq:	 frequency of a device set in resume phase.
 * @suspend_count:	 suspend requests counter क्रम a device.
 * @stats:	Statistics of devfreq device behavior
 * @transition_notअगरier_list: list head of DEVFREQ_TRANSITION_NOTIFIER notअगरier
 * @cdev:	Cooling device poपूर्णांकer अगर the devfreq has cooling property
 * @nb_min:		Notअगरier block क्रम DEV_PM_QOS_MIN_FREQUENCY
 * @nb_max:		Notअगरier block क्रम DEV_PM_QOS_MAX_FREQUENCY
 *
 * This काष्ठाure stores the devfreq inक्रमmation क्रम a given device.
 *
 * Note that when a governor accesses entries in काष्ठा devfreq in its
 * functions except क्रम the context of callbacks defined in काष्ठा
 * devfreq_governor, the governor should protect its access with the
 * काष्ठा mutex lock in काष्ठा devfreq. A governor may use this mutex
 * to protect its own निजी data in ``व्योम *data`` as well.
 */
काष्ठा devfreq अणु
	काष्ठा list_head node;

	काष्ठा mutex lock;
	काष्ठा device dev;
	काष्ठा devfreq_dev_profile *profile;
	स्थिर काष्ठा devfreq_governor *governor;
	काष्ठा opp_table *opp_table;
	काष्ठा notअगरier_block nb;
	काष्ठा delayed_work work;

	अचिन्हित दीर्घ previous_freq;
	काष्ठा devfreq_dev_status last_status;

	व्योम *data; /* निजी data क्रम governors */

	काष्ठा dev_pm_qos_request user_min_freq_req;
	काष्ठा dev_pm_qos_request user_max_freq_req;
	अचिन्हित दीर्घ scaling_min_freq;
	अचिन्हित दीर्घ scaling_max_freq;
	bool stop_polling;

	अचिन्हित दीर्घ suspend_freq;
	अचिन्हित दीर्घ resume_freq;
	atomic_t suspend_count;

	/* inक्रमmation क्रम device frequency transitions */
	काष्ठा devfreq_stats stats;

	काष्ठा srcu_notअगरier_head transition_notअगरier_list;

	/* Poपूर्णांकer to the cooling device अगर used क्रम thermal mitigation */
	काष्ठा thermal_cooling_device *cdev;

	काष्ठा notअगरier_block nb_min;
	काष्ठा notअगरier_block nb_max;
पूर्ण;

काष्ठा devfreq_freqs अणु
	अचिन्हित दीर्घ old;
	अचिन्हित दीर्घ new;
पूर्ण;

#अगर defined(CONFIG_PM_DEVFREQ)
काष्ठा devfreq *devfreq_add_device(काष्ठा device *dev,
				काष्ठा devfreq_dev_profile *profile,
				स्थिर अक्षर *governor_name,
				व्योम *data);
पूर्णांक devfreq_हटाओ_device(काष्ठा devfreq *devfreq);
काष्ठा devfreq *devm_devfreq_add_device(काष्ठा device *dev,
				काष्ठा devfreq_dev_profile *profile,
				स्थिर अक्षर *governor_name,
				व्योम *data);
व्योम devm_devfreq_हटाओ_device(काष्ठा device *dev, काष्ठा devfreq *devfreq);

/* Supposed to be called by PM callbacks */
पूर्णांक devfreq_suspend_device(काष्ठा devfreq *devfreq);
पूर्णांक devfreq_resume_device(काष्ठा devfreq *devfreq);

व्योम devfreq_suspend(व्योम);
व्योम devfreq_resume(व्योम);

/* update_devfreq() - Reevaluate the device and configure frequency */
पूर्णांक update_devfreq(काष्ठा devfreq *devfreq);

/* Helper functions क्रम devfreq user device driver with OPP. */
काष्ठा dev_pm_opp *devfreq_recommended_opp(काष्ठा device *dev,
				अचिन्हित दीर्घ *freq, u32 flags);
पूर्णांक devfreq_रेजिस्टर_opp_notअगरier(काष्ठा device *dev,
				काष्ठा devfreq *devfreq);
पूर्णांक devfreq_unरेजिस्टर_opp_notअगरier(काष्ठा device *dev,
				काष्ठा devfreq *devfreq);
पूर्णांक devm_devfreq_रेजिस्टर_opp_notअगरier(काष्ठा device *dev,
				काष्ठा devfreq *devfreq);
व्योम devm_devfreq_unरेजिस्टर_opp_notअगरier(काष्ठा device *dev,
				काष्ठा devfreq *devfreq);
पूर्णांक devfreq_रेजिस्टर_notअगरier(काष्ठा devfreq *devfreq,
				काष्ठा notअगरier_block *nb,
				अचिन्हित पूर्णांक list);
पूर्णांक devfreq_unरेजिस्टर_notअगरier(काष्ठा devfreq *devfreq,
				काष्ठा notअगरier_block *nb,
				अचिन्हित पूर्णांक list);
पूर्णांक devm_devfreq_रेजिस्टर_notअगरier(काष्ठा device *dev,
				काष्ठा devfreq *devfreq,
				काष्ठा notअगरier_block *nb,
				अचिन्हित पूर्णांक list);
व्योम devm_devfreq_unरेजिस्टर_notअगरier(काष्ठा device *dev,
				काष्ठा devfreq *devfreq,
				काष्ठा notअगरier_block *nb,
				अचिन्हित पूर्णांक list);
काष्ठा devfreq *devfreq_get_devfreq_by_node(काष्ठा device_node *node);
काष्ठा devfreq *devfreq_get_devfreq_by_phandle(काष्ठा device *dev,
				स्थिर अक्षर *phandle_name, पूर्णांक index);

#अगर IS_ENABLED(CONFIG_DEVFREQ_GOV_SIMPLE_ONDEMAND)
/**
 * काष्ठा devfreq_simple_ondemand_data - ``व्योम *data`` fed to काष्ठा devfreq
 *	and devfreq_add_device
 * @upthreshold:	If the load is over this value, the frequency jumps.
 *			Specअगरy 0 to use the शेष. Valid value = 0 to 100.
 * @करोwndअगरferential:	If the load is under upthreshold - करोwndअगरferential,
 *			the governor may consider slowing the frequency करोwn.
 *			Specअगरy 0 to use the शेष. Valid value = 0 to 100.
 *			करोwndअगरferential < upthreshold must hold.
 *
 * If the fed devfreq_simple_ondemand_data poपूर्णांकer is शून्य to the governor,
 * the governor uses the शेष values.
 */
काष्ठा devfreq_simple_ondemand_data अणु
	अचिन्हित पूर्णांक upthreshold;
	अचिन्हित पूर्णांक करोwndअगरferential;
पूर्ण;
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_DEVFREQ_GOV_PASSIVE)
/**
 * काष्ठा devfreq_passive_data - ``व्योम *data`` fed to काष्ठा devfreq
 *	and devfreq_add_device
 * @parent:	the devfreq instance of parent device.
 * @get_target_freq:	Optional callback, Returns desired operating frequency
 *			क्रम the device using passive governor. That is called
 *			when passive governor should decide the next frequency
 *			by using the new frequency of parent devfreq device
 *			using governors except क्रम passive governor.
 *			If the devfreq device has the specअगरic method to decide
 *			the next frequency, should use this callback.
 * @this:	the devfreq instance of own device.
 * @nb:		the notअगरier block क्रम DEVFREQ_TRANSITION_NOTIFIER list
 *
 * The devfreq_passive_data have to set the devfreq instance of parent
 * device with governors except क्रम the passive governor. But, करोn't need to
 * initialize the 'this' and 'nb' field because the devfreq core will handle
 * them.
 */
काष्ठा devfreq_passive_data अणु
	/* Should set the devfreq instance of parent device */
	काष्ठा devfreq *parent;

	/* Optional callback to decide the next frequency of passvice device */
	पूर्णांक (*get_target_freq)(काष्ठा devfreq *this, अचिन्हित दीर्घ *freq);

	/* For passive governor's internal use. Don't need to set them */
	काष्ठा devfreq *this;
	काष्ठा notअगरier_block nb;
पूर्ण;
#पूर्ण_अगर

#अन्यथा /* !CONFIG_PM_DEVFREQ */
अटल अंतरभूत काष्ठा devfreq *devfreq_add_device(काष्ठा device *dev,
					काष्ठा devfreq_dev_profile *profile,
					स्थिर अक्षर *governor_name,
					व्योम *data)
अणु
	वापस ERR_PTR(-ENOSYS);
पूर्ण

अटल अंतरभूत पूर्णांक devfreq_हटाओ_device(काष्ठा devfreq *devfreq)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा devfreq *devm_devfreq_add_device(काष्ठा device *dev,
					काष्ठा devfreq_dev_profile *profile,
					स्थिर अक्षर *governor_name,
					व्योम *data)
अणु
	वापस ERR_PTR(-ENOSYS);
पूर्ण

अटल अंतरभूत व्योम devm_devfreq_हटाओ_device(काष्ठा device *dev,
					काष्ठा devfreq *devfreq)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक devfreq_suspend_device(काष्ठा devfreq *devfreq)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक devfreq_resume_device(काष्ठा devfreq *devfreq)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम devfreq_suspend(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम devfreq_resume(व्योम) अणुपूर्ण

अटल अंतरभूत काष्ठा dev_pm_opp *devfreq_recommended_opp(काष्ठा device *dev,
					अचिन्हित दीर्घ *freq, u32 flags)
अणु
	वापस ERR_PTR(-EINVAL);
पूर्ण

अटल अंतरभूत पूर्णांक devfreq_रेजिस्टर_opp_notअगरier(काष्ठा device *dev,
					काष्ठा devfreq *devfreq)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक devfreq_unरेजिस्टर_opp_notअगरier(काष्ठा device *dev,
					काष्ठा devfreq *devfreq)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक devm_devfreq_रेजिस्टर_opp_notअगरier(काष्ठा device *dev,
					काष्ठा devfreq *devfreq)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत व्योम devm_devfreq_unरेजिस्टर_opp_notअगरier(काष्ठा device *dev,
					काष्ठा devfreq *devfreq)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक devfreq_रेजिस्टर_notअगरier(काष्ठा devfreq *devfreq,
					काष्ठा notअगरier_block *nb,
					अचिन्हित पूर्णांक list)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक devfreq_unरेजिस्टर_notअगरier(काष्ठा devfreq *devfreq,
					काष्ठा notअगरier_block *nb,
					अचिन्हित पूर्णांक list)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक devm_devfreq_रेजिस्टर_notअगरier(काष्ठा device *dev,
					काष्ठा devfreq *devfreq,
					काष्ठा notअगरier_block *nb,
					अचिन्हित पूर्णांक list)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम devm_devfreq_unरेजिस्टर_notअगरier(काष्ठा device *dev,
					काष्ठा devfreq *devfreq,
					काष्ठा notअगरier_block *nb,
					अचिन्हित पूर्णांक list)
अणु
पूर्ण

अटल अंतरभूत काष्ठा devfreq *devfreq_get_devfreq_by_node(काष्ठा device_node *node)
अणु
	वापस ERR_PTR(-ENODEV);
पूर्ण

अटल अंतरभूत काष्ठा devfreq *devfreq_get_devfreq_by_phandle(काष्ठा device *dev,
					स्थिर अक्षर *phandle_name, पूर्णांक index)
अणु
	वापस ERR_PTR(-ENODEV);
पूर्ण

अटल अंतरभूत पूर्णांक devfreq_update_stats(काष्ठा devfreq *df)
अणु
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_DEVFREQ */

#पूर्ण_अगर /* __LINUX_DEVFREQ_H__ */
