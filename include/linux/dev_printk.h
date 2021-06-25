<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * dev_prपूर्णांकk.h - prपूर्णांकk messages helpers क्रम devices
 *
 * Copyright (c) 2001-2003 Patrick Mochel <mochel@osdl.org>
 * Copyright (c) 2004-2009 Greg Kroah-Harपंचांगan <gregkh@suse.de>
 * Copyright (c) 2008-2009 Novell Inc.
 *
 */

#अगर_अघोषित _DEVICE_PRINTK_H_
#घोषणा _DEVICE_PRINTK_H_

#समावेश <linux/compiler.h>
#समावेश <linux/types.h>
#समावेश <linux/ratelimit.h>

#अगर_अघोषित dev_fmt
#घोषणा dev_fmt(fmt) fmt
#पूर्ण_अगर

काष्ठा device;

#घोषणा PRINTK_INFO_SUBSYSTEM_LEN	16
#घोषणा PRINTK_INFO_DEVICE_LEN		48

काष्ठा dev_prपूर्णांकk_info अणु
	अक्षर subप्रणाली[PRINTK_INFO_SUBSYSTEM_LEN];
	अक्षर device[PRINTK_INFO_DEVICE_LEN];
पूर्ण;

#अगर_घोषित CONFIG_PRINTK

__म_लिखो(3, 0) __cold
पूर्णांक dev_vprपूर्णांकk_emit(पूर्णांक level, स्थिर काष्ठा device *dev,
		     स्थिर अक्षर *fmt, बहु_सूची args);
__म_लिखो(3, 4) __cold
पूर्णांक dev_prपूर्णांकk_emit(पूर्णांक level, स्थिर काष्ठा device *dev, स्थिर अक्षर *fmt, ...);

__म_लिखो(3, 4) __cold
व्योम dev_prपूर्णांकk(स्थिर अक्षर *level, स्थिर काष्ठा device *dev,
		स्थिर अक्षर *fmt, ...);
__म_लिखो(2, 3) __cold
व्योम _dev_emerg(स्थिर काष्ठा device *dev, स्थिर अक्षर *fmt, ...);
__म_लिखो(2, 3) __cold
व्योम _dev_alert(स्थिर काष्ठा device *dev, स्थिर अक्षर *fmt, ...);
__म_लिखो(2, 3) __cold
व्योम _dev_crit(स्थिर काष्ठा device *dev, स्थिर अक्षर *fmt, ...);
__म_लिखो(2, 3) __cold
व्योम _dev_err(स्थिर काष्ठा device *dev, स्थिर अक्षर *fmt, ...);
__म_लिखो(2, 3) __cold
व्योम _dev_warn(स्थिर काष्ठा device *dev, स्थिर अक्षर *fmt, ...);
__म_लिखो(2, 3) __cold
व्योम _dev_notice(स्थिर काष्ठा device *dev, स्थिर अक्षर *fmt, ...);
__म_लिखो(2, 3) __cold
व्योम _dev_info(स्थिर काष्ठा device *dev, स्थिर अक्षर *fmt, ...);

#अन्यथा

अटल अंतरभूत __म_लिखो(3, 0)
पूर्णांक dev_vprपूर्णांकk_emit(पूर्णांक level, स्थिर काष्ठा device *dev,
		     स्थिर अक्षर *fmt, बहु_सूची args)
अणु वापस 0; पूर्ण
अटल अंतरभूत __म_लिखो(3, 4)
पूर्णांक dev_prपूर्णांकk_emit(पूर्णांक level, स्थिर काष्ठा device *dev, स्थिर अक्षर *fmt, ...)
अणु वापस 0; पूर्ण

अटल अंतरभूत व्योम __dev_prपूर्णांकk(स्थिर अक्षर *level, स्थिर काष्ठा device *dev,
				काष्ठा va_क्रमmat *vaf)
अणुपूर्ण
अटल अंतरभूत __म_लिखो(3, 4)
व्योम dev_prपूर्णांकk(स्थिर अक्षर *level, स्थिर काष्ठा device *dev,
		 स्थिर अक्षर *fmt, ...)
अणुपूर्ण

अटल अंतरभूत __म_लिखो(2, 3)
व्योम _dev_emerg(स्थिर काष्ठा device *dev, स्थिर अक्षर *fmt, ...)
अणुपूर्ण
अटल अंतरभूत __म_लिखो(2, 3)
व्योम _dev_crit(स्थिर काष्ठा device *dev, स्थिर अक्षर *fmt, ...)
अणुपूर्ण
अटल अंतरभूत __म_लिखो(2, 3)
व्योम _dev_alert(स्थिर काष्ठा device *dev, स्थिर अक्षर *fmt, ...)
अणुपूर्ण
अटल अंतरभूत __म_लिखो(2, 3)
व्योम _dev_err(स्थिर काष्ठा device *dev, स्थिर अक्षर *fmt, ...)
अणुपूर्ण
अटल अंतरभूत __म_लिखो(2, 3)
व्योम _dev_warn(स्थिर काष्ठा device *dev, स्थिर अक्षर *fmt, ...)
अणुपूर्ण
अटल अंतरभूत __म_लिखो(2, 3)
व्योम _dev_notice(स्थिर काष्ठा device *dev, स्थिर अक्षर *fmt, ...)
अणुपूर्ण
अटल अंतरभूत __म_लिखो(2, 3)
व्योम _dev_info(स्थिर काष्ठा device *dev, स्थिर अक्षर *fmt, ...)
अणुपूर्ण

#पूर्ण_अगर

/*
 * #घोषणाs क्रम all the dev_<level> macros to prefix with whatever
 * possible use of #घोषणा dev_fmt(fmt) ...
 */

#घोषणा dev_emerg(dev, fmt, ...)					\
	_dev_emerg(dev, dev_fmt(fmt), ##__VA_ARGS__)
#घोषणा dev_crit(dev, fmt, ...)						\
	_dev_crit(dev, dev_fmt(fmt), ##__VA_ARGS__)
#घोषणा dev_alert(dev, fmt, ...)					\
	_dev_alert(dev, dev_fmt(fmt), ##__VA_ARGS__)
#घोषणा dev_err(dev, fmt, ...)						\
	_dev_err(dev, dev_fmt(fmt), ##__VA_ARGS__)
#घोषणा dev_warn(dev, fmt, ...)						\
	_dev_warn(dev, dev_fmt(fmt), ##__VA_ARGS__)
#घोषणा dev_notice(dev, fmt, ...)					\
	_dev_notice(dev, dev_fmt(fmt), ##__VA_ARGS__)
#घोषणा dev_info(dev, fmt, ...)						\
	_dev_info(dev, dev_fmt(fmt), ##__VA_ARGS__)

#अगर defined(CONFIG_DYNAMIC_DEBUG) || \
	(defined(CONFIG_DYNAMIC_DEBUG_CORE) && defined(DYNAMIC_DEBUG_MODULE))
#घोषणा dev_dbg(dev, fmt, ...)						\
	dynamic_dev_dbg(dev, dev_fmt(fmt), ##__VA_ARGS__)
#या_अगर defined(DEBUG)
#घोषणा dev_dbg(dev, fmt, ...)						\
	dev_prपूर्णांकk(KERN_DEBUG, dev, dev_fmt(fmt), ##__VA_ARGS__)
#अन्यथा
#घोषणा dev_dbg(dev, fmt, ...)						\
(अणु									\
	अगर (0)								\
		dev_prपूर्णांकk(KERN_DEBUG, dev, dev_fmt(fmt), ##__VA_ARGS__); \
पूर्ण)
#पूर्ण_अगर

#अगर_घोषित CONFIG_PRINTK
#घोषणा dev_level_once(dev_level, dev, fmt, ...)			\
करो अणु									\
	अटल bool __prपूर्णांक_once __पढ़ो_mostly;				\
									\
	अगर (!__prपूर्णांक_once) अणु						\
		__prपूर्णांक_once = true;					\
		dev_level(dev, fmt, ##__VA_ARGS__);			\
	पूर्ण								\
पूर्ण जबतक (0)
#अन्यथा
#घोषणा dev_level_once(dev_level, dev, fmt, ...)			\
करो अणु									\
	अगर (0)								\
		dev_level(dev, fmt, ##__VA_ARGS__);			\
पूर्ण जबतक (0)
#पूर्ण_अगर

#घोषणा dev_emerg_once(dev, fmt, ...)					\
	dev_level_once(dev_emerg, dev, fmt, ##__VA_ARGS__)
#घोषणा dev_alert_once(dev, fmt, ...)					\
	dev_level_once(dev_alert, dev, fmt, ##__VA_ARGS__)
#घोषणा dev_crit_once(dev, fmt, ...)					\
	dev_level_once(dev_crit, dev, fmt, ##__VA_ARGS__)
#घोषणा dev_err_once(dev, fmt, ...)					\
	dev_level_once(dev_err, dev, fmt, ##__VA_ARGS__)
#घोषणा dev_warn_once(dev, fmt, ...)					\
	dev_level_once(dev_warn, dev, fmt, ##__VA_ARGS__)
#घोषणा dev_notice_once(dev, fmt, ...)					\
	dev_level_once(dev_notice, dev, fmt, ##__VA_ARGS__)
#घोषणा dev_info_once(dev, fmt, ...)					\
	dev_level_once(dev_info, dev, fmt, ##__VA_ARGS__)
#घोषणा dev_dbg_once(dev, fmt, ...)					\
	dev_level_once(dev_dbg, dev, fmt, ##__VA_ARGS__)

#घोषणा dev_level_ratelimited(dev_level, dev, fmt, ...)			\
करो अणु									\
	अटल DEFINE_RATELIMIT_STATE(_rs,				\
				      DEFAULT_RATELIMIT_INTERVAL,	\
				      DEFAULT_RATELIMIT_BURST);		\
	अगर (__ratelimit(&_rs))						\
		dev_level(dev, fmt, ##__VA_ARGS__);			\
पूर्ण जबतक (0)

#घोषणा dev_emerg_ratelimited(dev, fmt, ...)				\
	dev_level_ratelimited(dev_emerg, dev, fmt, ##__VA_ARGS__)
#घोषणा dev_alert_ratelimited(dev, fmt, ...)				\
	dev_level_ratelimited(dev_alert, dev, fmt, ##__VA_ARGS__)
#घोषणा dev_crit_ratelimited(dev, fmt, ...)				\
	dev_level_ratelimited(dev_crit, dev, fmt, ##__VA_ARGS__)
#घोषणा dev_err_ratelimited(dev, fmt, ...)				\
	dev_level_ratelimited(dev_err, dev, fmt, ##__VA_ARGS__)
#घोषणा dev_warn_ratelimited(dev, fmt, ...)				\
	dev_level_ratelimited(dev_warn, dev, fmt, ##__VA_ARGS__)
#घोषणा dev_notice_ratelimited(dev, fmt, ...)				\
	dev_level_ratelimited(dev_notice, dev, fmt, ##__VA_ARGS__)
#घोषणा dev_info_ratelimited(dev, fmt, ...)				\
	dev_level_ratelimited(dev_info, dev, fmt, ##__VA_ARGS__)
#अगर defined(CONFIG_DYNAMIC_DEBUG) || \
	(defined(CONFIG_DYNAMIC_DEBUG_CORE) && defined(DYNAMIC_DEBUG_MODULE))
/* descriptor check is first to prevent flooding with "callbacks suppressed" */
#घोषणा dev_dbg_ratelimited(dev, fmt, ...)				\
करो अणु									\
	अटल DEFINE_RATELIMIT_STATE(_rs,				\
				      DEFAULT_RATELIMIT_INTERVAL,	\
				      DEFAULT_RATELIMIT_BURST);		\
	DEFINE_DYNAMIC_DEBUG_METADATA(descriptor, fmt);			\
	अगर (DYNAMIC_DEBUG_BRANCH(descriptor) &&				\
	    __ratelimit(&_rs))						\
		__dynamic_dev_dbg(&descriptor, dev, dev_fmt(fmt),	\
				  ##__VA_ARGS__);			\
पूर्ण जबतक (0)
#या_अगर defined(DEBUG)
#घोषणा dev_dbg_ratelimited(dev, fmt, ...)				\
करो अणु									\
	अटल DEFINE_RATELIMIT_STATE(_rs,				\
				      DEFAULT_RATELIMIT_INTERVAL,	\
				      DEFAULT_RATELIMIT_BURST);		\
	अगर (__ratelimit(&_rs))						\
		dev_prपूर्णांकk(KERN_DEBUG, dev, dev_fmt(fmt), ##__VA_ARGS__); \
पूर्ण जबतक (0)
#अन्यथा
#घोषणा dev_dbg_ratelimited(dev, fmt, ...)				\
करो अणु									\
	अगर (0)								\
		dev_prपूर्णांकk(KERN_DEBUG, dev, dev_fmt(fmt), ##__VA_ARGS__); \
पूर्ण जबतक (0)
#पूर्ण_अगर

#अगर_घोषित VERBOSE_DEBUG
#घोषणा dev_vdbg	dev_dbg
#अन्यथा
#घोषणा dev_vdbg(dev, fmt, ...)						\
(अणु									\
	अगर (0)								\
		dev_prपूर्णांकk(KERN_DEBUG, dev, dev_fmt(fmt), ##__VA_ARGS__); \
पूर्ण)
#पूर्ण_अगर

/*
 * dev_WARN*() acts like dev_prपूर्णांकk(), but with the key dअगरference of
 * using WARN/WARN_ONCE to include file/line inक्रमmation and a backtrace.
 */
#घोषणा dev_WARN(dev, क्रमmat, arg...) \
	WARN(1, "%s %s: " क्रमmat, dev_driver_string(dev), dev_name(dev), ## arg);

#घोषणा dev_WARN_ONCE(dev, condition, क्रमmat, arg...) \
	WARN_ONCE(condition, "%s %s: " क्रमmat, \
			dev_driver_string(dev), dev_name(dev), ## arg)

#पूर्ण_अगर /* _DEVICE_PRINTK_H_ */
