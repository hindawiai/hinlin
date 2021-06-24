<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_घोषित CONFIG_RTC_INTF_DEV

बाह्य व्योम __init rtc_dev_init(व्योम);
बाह्य व्योम __निकास rtc_dev_निकास(व्योम);
बाह्य व्योम rtc_dev_prepare(काष्ठा rtc_device *rtc);

#अन्यथा

अटल अंतरभूत व्योम rtc_dev_init(व्योम)
अणु
पूर्ण

अटल अंतरभूत व्योम rtc_dev_निकास(व्योम)
अणु
पूर्ण

अटल अंतरभूत व्योम rtc_dev_prepare(काष्ठा rtc_device *rtc)
अणु
पूर्ण

#पूर्ण_अगर

#अगर_घोषित CONFIG_RTC_INTF_PROC

बाह्य व्योम rtc_proc_add_device(काष्ठा rtc_device *rtc);
बाह्य व्योम rtc_proc_del_device(काष्ठा rtc_device *rtc);

#अन्यथा

अटल अंतरभूत व्योम rtc_proc_add_device(काष्ठा rtc_device *rtc)
अणु
पूर्ण

अटल अंतरभूत व्योम rtc_proc_del_device(काष्ठा rtc_device *rtc)
अणु
पूर्ण

#पूर्ण_अगर

#अगर_घोषित CONFIG_RTC_INTF_SYSFS
स्थिर काष्ठा attribute_group **rtc_get_dev_attribute_groups(व्योम);
#अन्यथा
अटल अंतरभूत स्थिर काष्ठा attribute_group **rtc_get_dev_attribute_groups(व्योम)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर
