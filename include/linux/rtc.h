<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Generic RTC पूर्णांकerface.
 * This version contains the part of the user पूर्णांकerface to the Real Time Clock
 * service. It is used with both the legacy mc146818 and also  EFI
 * Struct rtc_समय and first 12 ioctl by Paul Gorपंचांगaker, 1996 - separated out
 * from <linux/mc146818rtc.h> to this file क्रम 2.4 kernels.
 *
 * Copyright (C) 1999 Hewlett-Packard Co.
 * Copyright (C) 1999 Stephane Eranian <eranian@hpl.hp.com>
 */
#अगर_अघोषित _LINUX_RTC_H_
#घोषणा _LINUX_RTC_H_


#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/nvmem-provider.h>
#समावेश <uapi/linux/rtc.h>

बाह्य पूर्णांक rtc_month_days(अचिन्हित पूर्णांक month, अचिन्हित पूर्णांक year);
बाह्य पूर्णांक rtc_year_days(अचिन्हित पूर्णांक day, अचिन्हित पूर्णांक month, अचिन्हित पूर्णांक year);
बाह्य पूर्णांक rtc_valid_पंचांग(काष्ठा rtc_समय *पंचांग);
बाह्य समय64_t rtc_पंचांग_to_समय64(काष्ठा rtc_समय *पंचांग);
बाह्य व्योम rtc_समय64_to_पंचांग(समय64_t समय, काष्ठा rtc_समय *पंचांग);
kसमय_प्रकार rtc_पंचांग_to_kसमय(काष्ठा rtc_समय पंचांग);
काष्ठा rtc_समय rtc_kसमय_प्रकारo_पंचांग(kसमय_प्रकार kt);

/*
 * rtc_पंचांग_sub - Return the dअगरference in seconds.
 */
अटल अंतरभूत समय64_t rtc_पंचांग_sub(काष्ठा rtc_समय *lhs, काष्ठा rtc_समय *rhs)
अणु
	वापस rtc_पंचांग_to_समय64(lhs) - rtc_पंचांग_to_समय64(rhs);
पूर्ण

#समावेश <linux/device.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/cdev.h>
#समावेश <linux/poll.h>
#समावेश <linux/mutex.h>
#समावेश <linux/समयrqueue.h>
#समावेश <linux/workqueue.h>

बाह्य काष्ठा class *rtc_class;

/*
 * For these RTC methods the device parameter is the physical device
 * on whatever bus holds the hardware (I2C, Platक्रमm, SPI, etc), which
 * was passed to rtc_device_रेजिस्टर().  Its driver_data normally holds
 * device state, including the rtc_device poपूर्णांकer क्रम the RTC.
 *
 * Most of these methods are called with rtc_device.ops_lock held,
 * through the rtc_*(काष्ठा rtc_device *, ...) calls.
 *
 * The (current) exceptions are mostly fileप्रणाली hooks:
 *   - the proc() hook क्रम procfs
 */
काष्ठा rtc_class_ops अणु
	पूर्णांक (*ioctl)(काष्ठा device *, अचिन्हित पूर्णांक, अचिन्हित दीर्घ);
	पूर्णांक (*पढ़ो_समय)(काष्ठा device *, काष्ठा rtc_समय *);
	पूर्णांक (*set_समय)(काष्ठा device *, काष्ठा rtc_समय *);
	पूर्णांक (*पढ़ो_alarm)(काष्ठा device *, काष्ठा rtc_wkalrm *);
	पूर्णांक (*set_alarm)(काष्ठा device *, काष्ठा rtc_wkalrm *);
	पूर्णांक (*proc)(काष्ठा device *, काष्ठा seq_file *);
	पूर्णांक (*alarm_irq_enable)(काष्ठा device *, अचिन्हित पूर्णांक enabled);
	पूर्णांक (*पढ़ो_offset)(काष्ठा device *, दीर्घ *offset);
	पूर्णांक (*set_offset)(काष्ठा device *, दीर्घ offset);
पूर्ण;

काष्ठा rtc_device;

काष्ठा rtc_समयr अणु
	काष्ठा समयrqueue_node node;
	kसमय_प्रकार period;
	व्योम (*func)(काष्ठा rtc_device *rtc);
	काष्ठा rtc_device *rtc;
	पूर्णांक enabled;
पूर्ण;

/* flags */
#घोषणा RTC_DEV_BUSY 0

काष्ठा rtc_device अणु
	काष्ठा device dev;
	काष्ठा module *owner;

	पूर्णांक id;

	स्थिर काष्ठा rtc_class_ops *ops;
	काष्ठा mutex ops_lock;

	काष्ठा cdev अक्षर_dev;
	अचिन्हित दीर्घ flags;

	अचिन्हित दीर्घ irq_data;
	spinlock_t irq_lock;
	रुको_queue_head_t irq_queue;
	काष्ठा fasync_काष्ठा *async_queue;

	पूर्णांक irq_freq;
	पूर्णांक max_user_freq;

	काष्ठा समयrqueue_head समयrqueue;
	काष्ठा rtc_समयr aie_समयr;
	काष्ठा rtc_समयr uie_rtस_समयr;
	काष्ठा hrसमयr pie_समयr; /* sub second exp, so needs hrसमयr */
	पूर्णांक pie_enabled;
	काष्ठा work_काष्ठा irqwork;
	/* Some hardware can't support UIE mode */
	पूर्णांक uie_unsupported;

	/*
	 * This offset specअगरies the update timing of the RTC.
	 *
	 * tsched     t1 ग_लिखो(t2.tv_sec - 1sec))  t2 RTC increments seconds
	 *
	 * The offset defines how tsched is computed so that the ग_लिखो to
	 * the RTC (t2.tv_sec - 1sec) is correct versus the समय required
	 * क्रम the transport of the ग_लिखो and the समय which the RTC needs
	 * to increment seconds the first समय after the ग_लिखो (t2).
	 *
	 * For direct accessible RTCs tsched ~= t1 because the ग_लिखो समय
	 * is negligible. For RTCs behind slow busses the transport समय is
	 * signअगरicant and has to be taken पूर्णांकo account.
	 *
	 * The समय between the ग_लिखो (t1) and the first increment after
	 * the ग_लिखो (t2) is RTC specअगरic. For a MC146818 RTC it's 500ms,
	 * क्रम many others it's exactly 1 second. Consult the datasheet.
	 *
	 * The value of this offset is also used to calculate the to be
	 * written value (t2.tv_sec - 1sec) at tsched.
	 *
	 * The शेष value क्रम this is NSEC_PER_SEC + 10 msec शेष
	 * transport समय. The offset can be adjusted by drivers so the
	 * calculation क्रम the to be written value at tsched becomes
	 * correct:
	 *
	 *	newval = tsched + set_offset_nsec - NSEC_PER_SEC
	 * and  (tsched + set_offset_nsec) % NSEC_PER_SEC == 0
	 */
	अचिन्हित दीर्घ set_offset_nsec;

	अचिन्हित दीर्घ features[BITS_TO_LONGS(RTC_FEATURE_CNT)];

	समय64_t range_min;
	समयu64_t range_max;
	समय64_t start_secs;
	समय64_t offset_secs;
	bool set_start_समय;

#अगर_घोषित CONFIG_RTC_INTF_DEV_UIE_EMUL
	काष्ठा work_काष्ठा uie_task;
	काष्ठा समयr_list uie_समयr;
	/* Those fields are रक्षित by rtc->irq_lock */
	अचिन्हित पूर्णांक oldsecs;
	अचिन्हित पूर्णांक uie_irq_active:1;
	अचिन्हित पूर्णांक stop_uie_polling:1;
	अचिन्हित पूर्णांक uie_task_active:1;
	अचिन्हित पूर्णांक uie_समयr_active:1;
#पूर्ण_अगर
पूर्ण;
#घोषणा to_rtc_device(d) container_of(d, काष्ठा rtc_device, dev)

#घोषणा rtc_lock(d) mutex_lock(&d->ops_lock)
#घोषणा rtc_unlock(d) mutex_unlock(&d->ops_lock)

/* useful बारtamps */
#घोषणा RTC_TIMESTAMP_BEGIN_0000	-62167219200ULL /* 0000-01-01 00:00:00 */
#घोषणा RTC_TIMESTAMP_BEGIN_1900	-2208988800LL /* 1900-01-01 00:00:00 */
#घोषणा RTC_TIMESTAMP_BEGIN_2000	946684800LL /* 2000-01-01 00:00:00 */
#घोषणा RTC_TIMESTAMP_END_2063		2966371199LL /* 2063-12-31 23:59:59 */
#घोषणा RTC_TIMESTAMP_END_2079		3471292799LL /* 2079-12-31 23:59:59 */
#घोषणा RTC_TIMESTAMP_END_2099		4102444799LL /* 2099-12-31 23:59:59 */
#घोषणा RTC_TIMESTAMP_END_2199		7258118399LL /* 2199-12-31 23:59:59 */
#घोषणा RTC_TIMESTAMP_END_9999		253402300799LL /* 9999-12-31 23:59:59 */

बाह्य काष्ठा rtc_device *devm_rtc_device_रेजिस्टर(काष्ठा device *dev,
					स्थिर अक्षर *name,
					स्थिर काष्ठा rtc_class_ops *ops,
					काष्ठा module *owner);
काष्ठा rtc_device *devm_rtc_allocate_device(काष्ठा device *dev);
पूर्णांक __devm_rtc_रेजिस्टर_device(काष्ठा module *owner, काष्ठा rtc_device *rtc);

बाह्य पूर्णांक rtc_पढ़ो_समय(काष्ठा rtc_device *rtc, काष्ठा rtc_समय *पंचांग);
बाह्य पूर्णांक rtc_set_समय(काष्ठा rtc_device *rtc, काष्ठा rtc_समय *पंचांग);
पूर्णांक __rtc_पढ़ो_alarm(काष्ठा rtc_device *rtc, काष्ठा rtc_wkalrm *alarm);
बाह्य पूर्णांक rtc_पढ़ो_alarm(काष्ठा rtc_device *rtc,
			काष्ठा rtc_wkalrm *alrm);
बाह्य पूर्णांक rtc_set_alarm(काष्ठा rtc_device *rtc,
				काष्ठा rtc_wkalrm *alrm);
बाह्य पूर्णांक rtc_initialize_alarm(काष्ठा rtc_device *rtc,
				काष्ठा rtc_wkalrm *alrm);
बाह्य व्योम rtc_update_irq(काष्ठा rtc_device *rtc,
			अचिन्हित दीर्घ num, अचिन्हित दीर्घ events);

बाह्य काष्ठा rtc_device *rtc_class_खोलो(स्थिर अक्षर *name);
बाह्य व्योम rtc_class_बंद(काष्ठा rtc_device *rtc);

बाह्य पूर्णांक rtc_irq_set_state(काष्ठा rtc_device *rtc, पूर्णांक enabled);
बाह्य पूर्णांक rtc_irq_set_freq(काष्ठा rtc_device *rtc, पूर्णांक freq);
बाह्य पूर्णांक rtc_update_irq_enable(काष्ठा rtc_device *rtc, अचिन्हित पूर्णांक enabled);
बाह्य पूर्णांक rtc_alarm_irq_enable(काष्ठा rtc_device *rtc, अचिन्हित पूर्णांक enabled);
बाह्य पूर्णांक rtc_dev_update_irq_enable_emul(काष्ठा rtc_device *rtc,
						अचिन्हित पूर्णांक enabled);

व्योम rtc_handle_legacy_irq(काष्ठा rtc_device *rtc, पूर्णांक num, पूर्णांक mode);
व्योम rtc_aie_update_irq(काष्ठा rtc_device *rtc);
व्योम rtc_uie_update_irq(काष्ठा rtc_device *rtc);
क्रमागत hrसमयr_restart rtc_pie_update_irq(काष्ठा hrसमयr *समयr);

व्योम rtc_समयr_init(काष्ठा rtc_समयr *समयr, व्योम (*f)(काष्ठा rtc_device *r),
		    काष्ठा rtc_device *rtc);
पूर्णांक rtc_समयr_start(काष्ठा rtc_device *rtc, काष्ठा rtc_समयr *समयr,
		    kसमय_प्रकार expires, kसमय_प्रकार period);
व्योम rtc_समयr_cancel(काष्ठा rtc_device *rtc, काष्ठा rtc_समयr *समयr);
पूर्णांक rtc_पढ़ो_offset(काष्ठा rtc_device *rtc, दीर्घ *offset);
पूर्णांक rtc_set_offset(काष्ठा rtc_device *rtc, दीर्घ offset);
व्योम rtc_समयr_करो_work(काष्ठा work_काष्ठा *work);

अटल अंतरभूत bool is_leap_year(अचिन्हित पूर्णांक year)
अणु
	वापस (!(year % 4) && (year % 100)) || !(year % 400);
पूर्ण

#घोषणा devm_rtc_रेजिस्टर_device(device) \
	__devm_rtc_रेजिस्टर_device(THIS_MODULE, device)

#अगर_घोषित CONFIG_RTC_HCTOSYS_DEVICE
बाह्य पूर्णांक rtc_hctosys_ret;
#अन्यथा
#घोषणा rtc_hctosys_ret -ENODEV
#पूर्ण_अगर

#अगर_घोषित CONFIG_RTC_NVMEM
पूर्णांक devm_rtc_nvmem_रेजिस्टर(काष्ठा rtc_device *rtc,
			    काष्ठा nvmem_config *nvmem_config);
#अन्यथा
अटल अंतरभूत पूर्णांक devm_rtc_nvmem_रेजिस्टर(काष्ठा rtc_device *rtc,
					  काष्ठा nvmem_config *nvmem_config)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_RTC_INTF_SYSFS
पूर्णांक rtc_add_group(काष्ठा rtc_device *rtc, स्थिर काष्ठा attribute_group *grp);
पूर्णांक rtc_add_groups(काष्ठा rtc_device *rtc, स्थिर काष्ठा attribute_group **grps);
#अन्यथा
अटल अंतरभूत
पूर्णांक rtc_add_group(काष्ठा rtc_device *rtc, स्थिर काष्ठा attribute_group *grp)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत
पूर्णांक rtc_add_groups(काष्ठा rtc_device *rtc, स्थिर काष्ठा attribute_group **grps)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर /* _LINUX_RTC_H_ */
