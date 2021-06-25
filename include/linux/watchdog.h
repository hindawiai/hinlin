<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *	Generic watchकरोg defines. Derived from..
 *
 * Berkshire PC Watchकरोg Defines
 * by Ken Hollis <khollis@bitgate.com>
 *
 */
#अगर_अघोषित _LINUX_WATCHDOG_H
#घोषणा _LINUX_WATCHDOG_H


#समावेश <linux/bitops.h>
#समावेश <linux/cdev.h>
#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/notअगरier.h>
#समावेश <uapi/linux/watchकरोg.h>

काष्ठा watchकरोg_ops;
काष्ठा watchकरोg_device;
काष्ठा watchकरोg_core_data;
काष्ठा watchकरोg_governor;

/** काष्ठा watchकरोg_ops - The watchकरोg-devices operations
 *
 * @owner:	The module owner.
 * @start:	The routine क्रम starting the watchकरोg device.
 * @stop:	The routine क्रम stopping the watchकरोg device.
 * @ping:	The routine that sends a keepalive ping to the watchकरोg device.
 * @status:	The routine that shows the status of the watchकरोg device.
 * @set_समयout:The routine क्रम setting the watchकरोg devices समयout value (in seconds).
 * @set_preसमयout:The routine क्रम setting the watchकरोg devices preसमयout.
 * @get_समयleft:The routine that माला_लो the समय left beक्रमe a reset (in seconds).
 * @restart:	The routine क्रम restarting the machine.
 * @ioctl:	The routines that handles extra ioctl calls.
 *
 * The watchकरोg_ops काष्ठाure contains a list of low-level operations
 * that control a watchकरोg device. It also contains the module that owns
 * these operations. The start function is mandatory, all other
 * functions are optional.
 */
काष्ठा watchकरोg_ops अणु
	काष्ठा module *owner;
	/* mandatory operations */
	पूर्णांक (*start)(काष्ठा watchकरोg_device *);
	/* optional operations */
	पूर्णांक (*stop)(काष्ठा watchकरोg_device *);
	पूर्णांक (*ping)(काष्ठा watchकरोg_device *);
	अचिन्हित पूर्णांक (*status)(काष्ठा watchकरोg_device *);
	पूर्णांक (*set_समयout)(काष्ठा watchकरोg_device *, अचिन्हित पूर्णांक);
	पूर्णांक (*set_preसमयout)(काष्ठा watchकरोg_device *, अचिन्हित पूर्णांक);
	अचिन्हित पूर्णांक (*get_समयleft)(काष्ठा watchकरोg_device *);
	पूर्णांक (*restart)(काष्ठा watchकरोg_device *, अचिन्हित दीर्घ, व्योम *);
	दीर्घ (*ioctl)(काष्ठा watchकरोg_device *, अचिन्हित पूर्णांक, अचिन्हित दीर्घ);
पूर्ण;

/** काष्ठा watchकरोg_device - The काष्ठाure that defines a watchकरोg device
 *
 * @id:		The watchकरोg's ID. (Allocated by watchकरोg_रेजिस्टर_device)
 * @parent:	The parent bus device
 * @groups:	List of sysfs attribute groups to create when creating the
 *		watchकरोg device.
 * @info:	Poपूर्णांकer to a watchकरोg_info काष्ठाure.
 * @ops:	Poपूर्णांकer to the list of watchकरोg operations.
 * @gov:	Poपूर्णांकer to watchकरोg preसमयout governor.
 * @bootstatus:	Status of the watchकरोg device at boot.
 * @समयout:	The watchकरोg devices समयout value (in seconds).
 * @preसमयout: The watchकरोg devices pre_समयout value.
 * @min_समयout:The watchकरोg devices minimum समयout value (in seconds).
 * @max_समयout:The watchकरोg devices maximum समयout value (in seconds)
 *		as configurable from user space. Only relevant अगर
 *		max_hw_heartbeat_ms is not provided.
 * @min_hw_heartbeat_ms:
 *		Hardware limit क्रम minimum समय between heartbeats,
 *		in milli-seconds.
 * @max_hw_heartbeat_ms:
 *		Hardware limit क्रम maximum समयout, in milli-seconds.
 *		Replaces max_समयout अगर specअगरied.
 * @reboot_nb:	The notअगरier block to stop watchकरोg on reboot.
 * @restart_nb:	The notअगरier block to रेजिस्टर a restart function.
 * @driver_data:Poपूर्णांकer to the drivers निजी data.
 * @wd_data:	Poपूर्णांकer to watchकरोg core पूर्णांकernal data.
 * @status:	Field that contains the devices पूर्णांकernal status bits.
 * @deferred:	Entry in wtd_deferred_reg_list which is used to
 *		रेजिस्टर early initialized watchकरोgs.
 *
 * The watchकरोg_device काष्ठाure contains all inक्रमmation about a
 * watchकरोg समयr device.
 *
 * The driver-data field may not be accessed directly. It must be accessed
 * via the watchकरोg_set_drvdata and watchकरोg_get_drvdata helpers.
 */
काष्ठा watchकरोg_device अणु
	पूर्णांक id;
	काष्ठा device *parent;
	स्थिर काष्ठा attribute_group **groups;
	स्थिर काष्ठा watchकरोg_info *info;
	स्थिर काष्ठा watchकरोg_ops *ops;
	स्थिर काष्ठा watchकरोg_governor *gov;
	अचिन्हित पूर्णांक bootstatus;
	अचिन्हित पूर्णांक समयout;
	अचिन्हित पूर्णांक preसमयout;
	अचिन्हित पूर्णांक min_समयout;
	अचिन्हित पूर्णांक max_समयout;
	अचिन्हित पूर्णांक min_hw_heartbeat_ms;
	अचिन्हित पूर्णांक max_hw_heartbeat_ms;
	काष्ठा notअगरier_block reboot_nb;
	काष्ठा notअगरier_block restart_nb;
	व्योम *driver_data;
	काष्ठा watchकरोg_core_data *wd_data;
	अचिन्हित दीर्घ status;
/* Bit numbers क्रम status flags */
#घोषणा WDOG_ACTIVE		0	/* Is the watchकरोg running/active */
#घोषणा WDOG_NO_WAY_OUT		1	/* Is 'nowayout' feature set ? */
#घोषणा WDOG_STOP_ON_REBOOT	2	/* Should be stopped on reboot */
#घोषणा WDOG_HW_RUNNING		3	/* True अगर HW watchकरोg running */
#घोषणा WDOG_STOP_ON_UNREGISTER	4	/* Should be stopped on unरेजिस्टर */
	काष्ठा list_head deferred;
पूर्ण;

#घोषणा WATCHDOG_NOWAYOUT		IS_BUILTIN(CONFIG_WATCHDOG_NOWAYOUT)
#घोषणा WATCHDOG_NOWAYOUT_INIT_STATUS	(WATCHDOG_NOWAYOUT << WDOG_NO_WAY_OUT)

/* Use the following function to check whether or not the watchकरोg is active */
अटल अंतरभूत bool watchकरोg_active(काष्ठा watchकरोg_device *wdd)
अणु
	वापस test_bit(WDOG_ACTIVE, &wdd->status);
पूर्ण

/*
 * Use the following function to check whether or not the hardware watchकरोg
 * is running
 */
अटल अंतरभूत bool watchकरोg_hw_running(काष्ठा watchकरोg_device *wdd)
अणु
	वापस test_bit(WDOG_HW_RUNNING, &wdd->status);
पूर्ण

/* Use the following function to set the nowayout feature */
अटल अंतरभूत व्योम watchकरोg_set_nowayout(काष्ठा watchकरोg_device *wdd, bool nowayout)
अणु
	अगर (nowayout)
		set_bit(WDOG_NO_WAY_OUT, &wdd->status);
पूर्ण

/* Use the following function to stop the watchकरोg on reboot */
अटल अंतरभूत व्योम watchकरोg_stop_on_reboot(काष्ठा watchकरोg_device *wdd)
अणु
	set_bit(WDOG_STOP_ON_REBOOT, &wdd->status);
पूर्ण

/* Use the following function to stop the watchकरोg when unरेजिस्टरing it */
अटल अंतरभूत व्योम watchकरोg_stop_on_unरेजिस्टर(काष्ठा watchकरोg_device *wdd)
अणु
	set_bit(WDOG_STOP_ON_UNREGISTER, &wdd->status);
पूर्ण

/* Use the following function to check अगर a समयout value is invalid */
अटल अंतरभूत bool watchकरोg_समयout_invalid(काष्ठा watchकरोg_device *wdd, अचिन्हित पूर्णांक t)
अणु
	/*
	 * The समयout is invalid अगर
	 * - the requested value is larger than अच_पूर्णांक_उच्च / 1000
	 *   (since पूर्णांकernal calculations are करोne in milli-seconds),
	 * or
	 * - the requested value is smaller than the configured minimum समयout,
	 * or
	 * - a maximum hardware समयout is not configured, a maximum समयout
	 *   is configured, and the requested value is larger than the
	 *   configured maximum समयout.
	 */
	वापस t > अच_पूर्णांक_उच्च / 1000 || t < wdd->min_समयout ||
		(!wdd->max_hw_heartbeat_ms && wdd->max_समयout &&
		 t > wdd->max_समयout);
पूर्ण

/* Use the following function to check अगर a preसमयout value is invalid */
अटल अंतरभूत bool watchकरोg_preसमयout_invalid(काष्ठा watchकरोg_device *wdd,
					       अचिन्हित पूर्णांक t)
अणु
	वापस t && wdd->समयout && t >= wdd->समयout;
पूर्ण

/* Use the following functions to manipulate watchकरोg driver specअगरic data */
अटल अंतरभूत व्योम watchकरोg_set_drvdata(काष्ठा watchकरोg_device *wdd, व्योम *data)
अणु
	wdd->driver_data = data;
पूर्ण

अटल अंतरभूत व्योम *watchकरोg_get_drvdata(काष्ठा watchकरोg_device *wdd)
अणु
	वापस wdd->driver_data;
पूर्ण

/* Use the following functions to report watchकरोg preसमयout event */
#अगर IS_ENABLED(CONFIG_WATCHDOG_PRETIMEOUT_GOV)
व्योम watchकरोg_notअगरy_preसमयout(काष्ठा watchकरोg_device *wdd);
#अन्यथा
अटल अंतरभूत व्योम watchकरोg_notअगरy_preसमयout(काष्ठा watchकरोg_device *wdd)
अणु
	pr_alert("watchdog%d: pretimeout event\n", wdd->id);
पूर्ण
#पूर्ण_अगर

/* drivers/watchकरोg/watchकरोg_core.c */
व्योम watchकरोg_set_restart_priority(काष्ठा watchकरोg_device *wdd, पूर्णांक priority);
बाह्य पूर्णांक watchकरोg_init_समयout(काष्ठा watchकरोg_device *wdd,
				  अचिन्हित पूर्णांक समयout_parm, काष्ठा device *dev);
बाह्य पूर्णांक watchकरोg_रेजिस्टर_device(काष्ठा watchकरोg_device *);
बाह्य व्योम watchकरोg_unरेजिस्टर_device(काष्ठा watchकरोg_device *);

पूर्णांक watchकरोg_set_last_hw_keepalive(काष्ठा watchकरोg_device *, अचिन्हित पूर्णांक);

/* devres रेजिस्टर variant */
पूर्णांक devm_watchकरोg_रेजिस्टर_device(काष्ठा device *dev, काष्ठा watchकरोg_device *);

#पूर्ण_अगर  /* अगरndef _LINUX_WATCHDOG_H */
