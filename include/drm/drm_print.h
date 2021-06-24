<शैली गुरु>
/*
 * Copyright (C) 2016 Red Hat
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors:
 * Rob Clark <robdclark@gmail.com>
 */

#अगर_अघोषित DRM_PRINT_H_
#घोषणा DRM_PRINT_H_

#समावेश <linux/compiler.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/device.h>
#समावेश <linux/debugfs.h>

#समावेश <drm/drm.h>

/* Do *not* use outside of drm_prपूर्णांक.[ch]! */
बाह्य अचिन्हित पूर्णांक __drm_debug;

/**
 * DOC: prपूर्णांक
 *
 * A simple wrapper क्रम dev_prपूर्णांकk(), seq_म_लिखो(), etc.  Allows same
 * debug code to be used क्रम both debugfs and prपूर्णांकk logging.
 *
 * For example::
 *
 *     व्योम log_some_info(काष्ठा drm_prपूर्णांकer *p)
 *     अणु
 *             drm_म_लिखो(p, "foo=%d\n", foo);
 *             drm_म_लिखो(p, "bar=%d\n", bar);
 *     पूर्ण
 *
 *     #अगर_घोषित CONFIG_DEBUG_FS
 *     व्योम debugfs_show(काष्ठा seq_file *f)
 *     अणु
 *             काष्ठा drm_prपूर्णांकer p = drm_seq_file_prपूर्णांकer(f);
 *             log_some_info(&p);
 *     पूर्ण
 *     #पूर्ण_अगर
 *
 *     व्योम some_other_function(...)
 *     अणु
 *             काष्ठा drm_prपूर्णांकer p = drm_info_prपूर्णांकer(drm->dev);
 *             log_some_info(&p);
 *     पूर्ण
 */

/**
 * काष्ठा drm_prपूर्णांकer - drm output "stream"
 *
 * Do not use काष्ठा members directly.  Use drm_prपूर्णांकer_seq_file(),
 * drm_prपूर्णांकer_info(), etc to initialize.  And drm_म_लिखो() क्रम output.
 */
काष्ठा drm_prपूर्णांकer अणु
	/* निजी: */
	व्योम (*म_लिखोn)(काष्ठा drm_prपूर्णांकer *p, काष्ठा va_क्रमmat *vaf);
	व्योम (*माला_दो)(काष्ठा drm_prपूर्णांकer *p, स्थिर अक्षर *str);
	व्योम *arg;
	स्थिर अक्षर *prefix;
पूर्ण;

व्योम __drm_म_लिखोn_coredump(काष्ठा drm_prपूर्णांकer *p, काष्ठा va_क्रमmat *vaf);
व्योम __drm_माला_दो_coredump(काष्ठा drm_prपूर्णांकer *p, स्थिर अक्षर *str);
व्योम __drm_म_लिखोn_seq_file(काष्ठा drm_prपूर्णांकer *p, काष्ठा va_क्रमmat *vaf);
व्योम __drm_माला_दो_seq_file(काष्ठा drm_prपूर्णांकer *p, स्थिर अक्षर *str);
व्योम __drm_म_लिखोn_info(काष्ठा drm_prपूर्णांकer *p, काष्ठा va_क्रमmat *vaf);
व्योम __drm_म_लिखोn_debug(काष्ठा drm_prपूर्णांकer *p, काष्ठा va_क्रमmat *vaf);
व्योम __drm_म_लिखोn_err(काष्ठा drm_prपूर्णांकer *p, काष्ठा va_क्रमmat *vaf);

__म_लिखो(2, 3)
व्योम drm_म_लिखो(काष्ठा drm_prपूर्णांकer *p, स्थिर अक्षर *f, ...);
व्योम drm_माला_दो(काष्ठा drm_prपूर्णांकer *p, स्थिर अक्षर *str);
व्योम drm_prपूर्णांक_regset32(काष्ठा drm_prपूर्णांकer *p, काष्ठा debugfs_regset32 *regset);
व्योम drm_prपूर्णांक_bits(काष्ठा drm_prपूर्णांकer *p, अचिन्हित दीर्घ value,
		    स्थिर अक्षर * स्थिर bits[], अचिन्हित पूर्णांक nbits);

__म_लिखो(2, 0)
/**
 * drm_भ_लिखो - prपूर्णांक to a &drm_prपूर्णांकer stream
 * @p: the &drm_prपूर्णांकer
 * @fmt: क्रमmat string
 * @va: the बहु_सूची
 */
अटल अंतरभूत व्योम
drm_भ_लिखो(काष्ठा drm_prपूर्णांकer *p, स्थिर अक्षर *fmt, बहु_सूची *va)
अणु
	काष्ठा va_क्रमmat vaf = अणु .fmt = fmt, .va = va पूर्ण;

	p->म_लिखोn(p, &vaf);
पूर्ण

/**
 * drm_म_लिखो_indent - Prपूर्णांक to a &drm_prपूर्णांकer stream with indentation
 * @prपूर्णांकer: DRM prपूर्णांकer
 * @indent: Tab indentation level (max 5)
 * @fmt: Format string
 */
#घोषणा drm_म_लिखो_indent(prपूर्णांकer, indent, fmt, ...) \
	drm_म_लिखो((prपूर्णांकer), "%.*s" fmt, (indent), "\t\t\t\t\tX", ##__VA_ARGS__)

/**
 * काष्ठा drm_prपूर्णांक_iterator - local काष्ठा used with drm_prपूर्णांकer_coredump
 * @data: Poपूर्णांकer to the devcoredump output buffer
 * @start: The offset within the buffer to start writing
 * @reमुख्य: The number of bytes to ग_लिखो क्रम this iteration
 */
काष्ठा drm_prपूर्णांक_iterator अणु
	व्योम *data;
	sमाप_प्रकार start;
	sमाप_प्रकार reमुख्य;
	/* निजी: */
	sमाप_प्रकार offset;
पूर्ण;

/**
 * drm_coredump_prपूर्णांकer - स्थिरruct a &drm_prपूर्णांकer that can output to a buffer
 * from the पढ़ो function क्रम devcoredump
 * @iter: A poपूर्णांकer to a काष्ठा drm_prपूर्णांक_iterator क्रम the पढ़ो instance
 *
 * This wrapper extends drm_म_लिखो() to work with a dev_coredumpm() callback
 * function. The passed in drm_prपूर्णांक_iterator काष्ठा contains the buffer
 * poपूर्णांकer, size and offset as passed in from devcoredump.
 *
 * For example::
 *
 *	व्योम coredump_पढ़ो(अक्षर *buffer, loff_t offset, माप_प्रकार count,
 *		व्योम *data, माप_प्रकार datalen)
 *	अणु
 *		काष्ठा drm_prपूर्णांक_iterator iter;
 *		काष्ठा drm_prपूर्णांकer p;
 *
 *		iter.data = buffer;
 *		iter.start = offset;
 *		iter.reमुख्य = count;
 *
 *		p = drm_coredump_prपूर्णांकer(&iter);
 *
 *		drm_म_लिखो(p, "foo=%d\n", foo);
 *	पूर्ण
 *
 *	व्योम makecoredump(...)
 *	अणु
 *		...
 *		dev_coredumpm(dev, THIS_MODULE, data, 0, GFP_KERNEL,
 *			coredump_पढ़ो, ...)
 *	पूर्ण
 *
 * RETURNS:
 * The &drm_prपूर्णांकer object
 */
अटल अंतरभूत काष्ठा drm_prपूर्णांकer
drm_coredump_prपूर्णांकer(काष्ठा drm_prपूर्णांक_iterator *iter)
अणु
	काष्ठा drm_prपूर्णांकer p = अणु
		.म_लिखोn = __drm_म_लिखोn_coredump,
		.माला_दो = __drm_माला_दो_coredump,
		.arg = iter,
	पूर्ण;

	/* Set the पूर्णांकernal offset of the iterator to zero */
	iter->offset = 0;

	वापस p;
पूर्ण

/**
 * drm_seq_file_prपूर्णांकer - स्थिरruct a &drm_prपूर्णांकer that outमाला_दो to &seq_file
 * @f:  the &काष्ठा seq_file to output to
 *
 * RETURNS:
 * The &drm_prपूर्णांकer object
 */
अटल अंतरभूत काष्ठा drm_prपूर्णांकer drm_seq_file_prपूर्णांकer(काष्ठा seq_file *f)
अणु
	काष्ठा drm_prपूर्णांकer p = अणु
		.म_लिखोn = __drm_म_लिखोn_seq_file,
		.माला_दो = __drm_माला_दो_seq_file,
		.arg = f,
	पूर्ण;
	वापस p;
पूर्ण

/**
 * drm_info_prपूर्णांकer - स्थिरruct a &drm_prपूर्णांकer that outमाला_दो to dev_prपूर्णांकk()
 * @dev: the &काष्ठा device poपूर्णांकer
 *
 * RETURNS:
 * The &drm_prपूर्णांकer object
 */
अटल अंतरभूत काष्ठा drm_prपूर्णांकer drm_info_prपूर्णांकer(काष्ठा device *dev)
अणु
	काष्ठा drm_prपूर्णांकer p = अणु
		.म_लिखोn = __drm_म_लिखोn_info,
		.arg = dev,
	पूर्ण;
	वापस p;
पूर्ण

/**
 * drm_debug_prपूर्णांकer - स्थिरruct a &drm_prपूर्णांकer that outमाला_दो to pr_debug()
 * @prefix: debug output prefix
 *
 * RETURNS:
 * The &drm_prपूर्णांकer object
 */
अटल अंतरभूत काष्ठा drm_prपूर्णांकer drm_debug_prपूर्णांकer(स्थिर अक्षर *prefix)
अणु
	काष्ठा drm_prपूर्णांकer p = अणु
		.म_लिखोn = __drm_म_लिखोn_debug,
		.prefix = prefix
	पूर्ण;
	वापस p;
पूर्ण

/**
 * drm_err_prपूर्णांकer - स्थिरruct a &drm_prपूर्णांकer that outमाला_दो to pr_err()
 * @prefix: debug output prefix
 *
 * RETURNS:
 * The &drm_prपूर्णांकer object
 */
अटल अंतरभूत काष्ठा drm_prपूर्णांकer drm_err_prपूर्णांकer(स्थिर अक्षर *prefix)
अणु
	काष्ठा drm_prपूर्णांकer p = अणु
		.म_लिखोn = __drm_म_लिखोn_err,
		.prefix = prefix
	पूर्ण;
	वापस p;
पूर्ण

/**
 * क्रमागत drm_debug_category - The DRM debug categories
 *
 * Each of the DRM debug logging macros use a specअगरic category, and the logging
 * is filtered by the drm.debug module parameter. This क्रमागत specअगरies the values
 * क्रम the पूर्णांकerface.
 *
 * Each DRM_DEBUG_<CATEGORY> macro logs to DRM_UT_<CATEGORY> category, except
 * DRM_DEBUG() logs to DRM_UT_CORE.
 *
 * Enabling verbose debug messages is करोne through the drm.debug parameter, each
 * category being enabled by a bit:
 *
 *  - drm.debug=0x1 will enable CORE messages
 *  - drm.debug=0x2 will enable DRIVER messages
 *  - drm.debug=0x3 will enable CORE and DRIVER messages
 *  - ...
 *  - drm.debug=0x1ff will enable all messages
 *
 * An पूर्णांकeresting feature is that it's possible to enable verbose logging at
 * run-समय by echoing the debug value in its sysfs node::
 *
 *   # echo 0xf > /sys/module/drm/parameters/debug
 *
 */
क्रमागत drm_debug_category अणु
	/**
	 * @DRM_UT_CORE: Used in the generic drm code: drm_ioctl.c, drm_mm.c,
	 * drm_memory.c, ...
	 */
	DRM_UT_CORE		= 0x01,
	/**
	 * @DRM_UT_DRIVER: Used in the venकरोr specअगरic part of the driver: i915,
	 * radeon, ... macro.
	 */
	DRM_UT_DRIVER		= 0x02,
	/**
	 * @DRM_UT_KMS: Used in the modesetting code.
	 */
	DRM_UT_KMS		= 0x04,
	/**
	 * @DRM_UT_PRIME: Used in the prime code.
	 */
	DRM_UT_PRIME		= 0x08,
	/**
	 * @DRM_UT_ATOMIC: Used in the atomic code.
	 */
	DRM_UT_ATOMIC		= 0x10,
	/**
	 * @DRM_UT_VBL: Used क्रम verbose debug message in the vblank code.
	 */
	DRM_UT_VBL		= 0x20,
	/**
	 * @DRM_UT_STATE: Used क्रम verbose atomic state debugging.
	 */
	DRM_UT_STATE		= 0x40,
	/**
	 * @DRM_UT_LEASE: Used in the lease code.
	 */
	DRM_UT_LEASE		= 0x80,
	/**
	 * @DRM_UT_DP: Used in the DP code.
	 */
	DRM_UT_DP		= 0x100,
	/**
	 * @DRM_UT_DRMRES: Used in the drm managed resources code.
	 */
	DRM_UT_DRMRES		= 0x200,
पूर्ण;

अटल अंतरभूत bool drm_debug_enabled(क्रमागत drm_debug_category category)
अणु
	वापस unlikely(__drm_debug & category);
पूर्ण

/*
 * काष्ठा device based logging
 *
 * Prefer drm_device based logging over device or prink based logging.
 */

__म_लिखो(3, 4)
व्योम drm_dev_prपूर्णांकk(स्थिर काष्ठा device *dev, स्थिर अक्षर *level,
		    स्थिर अक्षर *क्रमmat, ...);
__म_लिखो(3, 4)
व्योम drm_dev_dbg(स्थिर काष्ठा device *dev, क्रमागत drm_debug_category category,
		 स्थिर अक्षर *क्रमmat, ...);

/**
 * DRM_DEV_ERROR() - Error output.
 *
 * @dev: device poपूर्णांकer
 * @fmt: म_लिखो() like क्रमmat string.
 */
#घोषणा DRM_DEV_ERROR(dev, fmt, ...)					\
	drm_dev_prपूर्णांकk(dev, KERN_ERR, "*ERROR* " fmt, ##__VA_ARGS__)

/**
 * DRM_DEV_ERROR_RATELIMITED() - Rate limited error output.
 *
 * @dev: device poपूर्णांकer
 * @fmt: म_लिखो() like क्रमmat string.
 *
 * Like DRM_ERROR() but won't flood the log.
 */
#घोषणा DRM_DEV_ERROR_RATELIMITED(dev, fmt, ...)			\
(अणु									\
	अटल DEFINE_RATELIMIT_STATE(_rs,				\
				      DEFAULT_RATELIMIT_INTERVAL,	\
				      DEFAULT_RATELIMIT_BURST);		\
									\
	अगर (__ratelimit(&_rs))						\
		DRM_DEV_ERROR(dev, fmt, ##__VA_ARGS__);			\
पूर्ण)

#घोषणा DRM_DEV_INFO(dev, fmt, ...)				\
	drm_dev_prपूर्णांकk(dev, KERN_INFO, fmt, ##__VA_ARGS__)

#घोषणा DRM_DEV_INFO_ONCE(dev, fmt, ...)				\
(अणु									\
	अटल bool __prपूर्णांक_once __पढ़ो_mostly;				\
	अगर (!__prपूर्णांक_once) अणु						\
		__prपूर्णांक_once = true;					\
		DRM_DEV_INFO(dev, fmt, ##__VA_ARGS__);			\
	पूर्ण								\
पूर्ण)

/**
 * DRM_DEV_DEBUG() - Debug output क्रम generic drm code
 *
 * @dev: device poपूर्णांकer
 * @fmt: म_लिखो() like क्रमmat string.
 */
#घोषणा DRM_DEV_DEBUG(dev, fmt, ...)					\
	drm_dev_dbg(dev, DRM_UT_CORE, fmt, ##__VA_ARGS__)
/**
 * DRM_DEV_DEBUG_DRIVER() - Debug output क्रम venकरोr specअगरic part of the driver
 *
 * @dev: device poपूर्णांकer
 * @fmt: म_लिखो() like क्रमmat string.
 */
#घोषणा DRM_DEV_DEBUG_DRIVER(dev, fmt, ...)				\
	drm_dev_dbg(dev, DRM_UT_DRIVER,	fmt, ##__VA_ARGS__)
/**
 * DRM_DEV_DEBUG_KMS() - Debug output क्रम modesetting code
 *
 * @dev: device poपूर्णांकer
 * @fmt: म_लिखो() like क्रमmat string.
 */
#घोषणा DRM_DEV_DEBUG_KMS(dev, fmt, ...)				\
	drm_dev_dbg(dev, DRM_UT_KMS, fmt, ##__VA_ARGS__)

/*
 * काष्ठा drm_device based logging
 *
 * Prefer drm_device based logging over device or prink based logging.
 */

/* Helper क्रम काष्ठा drm_device based logging. */
#घोषणा __drm_prपूर्णांकk(drm, level, type, fmt, ...)			\
	dev_##level##type((drm)->dev, "[drm] " fmt, ##__VA_ARGS__)


#घोषणा drm_info(drm, fmt, ...)					\
	__drm_prपूर्णांकk((drm), info,, fmt, ##__VA_ARGS__)

#घोषणा drm_notice(drm, fmt, ...)				\
	__drm_prपूर्णांकk((drm), notice,, fmt, ##__VA_ARGS__)

#घोषणा drm_warn(drm, fmt, ...)					\
	__drm_prपूर्णांकk((drm), warn,, fmt, ##__VA_ARGS__)

#घोषणा drm_err(drm, fmt, ...)					\
	__drm_prपूर्णांकk((drm), err,, "*ERROR* " fmt, ##__VA_ARGS__)


#घोषणा drm_info_once(drm, fmt, ...)				\
	__drm_prपूर्णांकk((drm), info, _once, fmt, ##__VA_ARGS__)

#घोषणा drm_notice_once(drm, fmt, ...)				\
	__drm_prपूर्णांकk((drm), notice, _once, fmt, ##__VA_ARGS__)

#घोषणा drm_warn_once(drm, fmt, ...)				\
	__drm_prपूर्णांकk((drm), warn, _once, fmt, ##__VA_ARGS__)

#घोषणा drm_err_once(drm, fmt, ...)				\
	__drm_prपूर्णांकk((drm), err, _once, "*ERROR* " fmt, ##__VA_ARGS__)


#घोषणा drm_err_ratelimited(drm, fmt, ...)				\
	__drm_prपूर्णांकk((drm), err, _ratelimited, "*ERROR* " fmt, ##__VA_ARGS__)


#घोषणा drm_dbg_core(drm, fmt, ...)					\
	drm_dev_dbg((drm)->dev, DRM_UT_CORE, fmt, ##__VA_ARGS__)
#घोषणा drm_dbg(drm, fmt, ...)						\
	drm_dev_dbg((drm)->dev, DRM_UT_DRIVER, fmt, ##__VA_ARGS__)
#घोषणा drm_dbg_kms(drm, fmt, ...)					\
	drm_dev_dbg((drm)->dev, DRM_UT_KMS, fmt, ##__VA_ARGS__)
#घोषणा drm_dbg_prime(drm, fmt, ...)					\
	drm_dev_dbg((drm)->dev, DRM_UT_PRIME, fmt, ##__VA_ARGS__)
#घोषणा drm_dbg_atomic(drm, fmt, ...)					\
	drm_dev_dbg((drm)->dev, DRM_UT_ATOMIC, fmt, ##__VA_ARGS__)
#घोषणा drm_dbg_vbl(drm, fmt, ...)					\
	drm_dev_dbg((drm)->dev, DRM_UT_VBL, fmt, ##__VA_ARGS__)
#घोषणा drm_dbg_state(drm, fmt, ...)					\
	drm_dev_dbg((drm)->dev, DRM_UT_STATE, fmt, ##__VA_ARGS__)
#घोषणा drm_dbg_lease(drm, fmt, ...)					\
	drm_dev_dbg((drm)->dev, DRM_UT_LEASE, fmt, ##__VA_ARGS__)
#घोषणा drm_dbg_dp(drm, fmt, ...)					\
	drm_dev_dbg((drm)->dev, DRM_UT_DP, fmt, ##__VA_ARGS__)
#घोषणा drm_dbg_drmres(drm, fmt, ...)					\
	drm_dev_dbg((drm)->dev, DRM_UT_DRMRES, fmt, ##__VA_ARGS__)


/*
 * prपूर्णांकk based logging
 *
 * Prefer drm_device based logging over device or prink based logging.
 */

__म_लिखो(2, 3)
व्योम __drm_dbg(क्रमागत drm_debug_category category, स्थिर अक्षर *क्रमmat, ...);
__म_लिखो(1, 2)
व्योम __drm_err(स्थिर अक्षर *क्रमmat, ...);

/* Macros to make prपूर्णांकk easier */

#घोषणा _DRM_PRINTK(once, level, fmt, ...)				\
	prपूर्णांकk##once(KERN_##level "[" DRM_NAME "] " fmt, ##__VA_ARGS__)

#घोषणा DRM_INFO(fmt, ...)						\
	_DRM_PRINTK(, INFO, fmt, ##__VA_ARGS__)
#घोषणा DRM_NOTE(fmt, ...)						\
	_DRM_PRINTK(, NOTICE, fmt, ##__VA_ARGS__)
#घोषणा DRM_WARN(fmt, ...)						\
	_DRM_PRINTK(, WARNING, fmt, ##__VA_ARGS__)

#घोषणा DRM_INFO_ONCE(fmt, ...)						\
	_DRM_PRINTK(_once, INFO, fmt, ##__VA_ARGS__)
#घोषणा DRM_NOTE_ONCE(fmt, ...)						\
	_DRM_PRINTK(_once, NOTICE, fmt, ##__VA_ARGS__)
#घोषणा DRM_WARN_ONCE(fmt, ...)						\
	_DRM_PRINTK(_once, WARNING, fmt, ##__VA_ARGS__)

#घोषणा DRM_ERROR(fmt, ...)						\
	__drm_err(fmt, ##__VA_ARGS__)

#घोषणा DRM_ERROR_RATELIMITED(fmt, ...)					\
	DRM_DEV_ERROR_RATELIMITED(शून्य, fmt, ##__VA_ARGS__)

#घोषणा DRM_DEBUG(fmt, ...)						\
	__drm_dbg(DRM_UT_CORE, fmt, ##__VA_ARGS__)

#घोषणा DRM_DEBUG_DRIVER(fmt, ...)					\
	__drm_dbg(DRM_UT_DRIVER, fmt, ##__VA_ARGS__)

#घोषणा DRM_DEBUG_KMS(fmt, ...)						\
	__drm_dbg(DRM_UT_KMS, fmt, ##__VA_ARGS__)

#घोषणा DRM_DEBUG_PRIME(fmt, ...)					\
	__drm_dbg(DRM_UT_PRIME, fmt, ##__VA_ARGS__)

#घोषणा DRM_DEBUG_ATOMIC(fmt, ...)					\
	__drm_dbg(DRM_UT_ATOMIC, fmt, ##__VA_ARGS__)

#घोषणा DRM_DEBUG_VBL(fmt, ...)						\
	__drm_dbg(DRM_UT_VBL, fmt, ##__VA_ARGS__)

#घोषणा DRM_DEBUG_LEASE(fmt, ...)					\
	__drm_dbg(DRM_UT_LEASE, fmt, ##__VA_ARGS__)

#घोषणा DRM_DEBUG_DP(fmt, ...)						\
	__drm_dbg(DRM_UT_DP, fmt, ## __VA_ARGS__)

#घोषणा __DRM_DEFINE_DBG_RATELIMITED(category, drm, fmt, ...)					\
(अणु												\
	अटल DEFINE_RATELIMIT_STATE(rs_, DEFAULT_RATELIMIT_INTERVAL, DEFAULT_RATELIMIT_BURST);\
	स्थिर काष्ठा drm_device *drm_ = (drm);							\
												\
	अगर (drm_debug_enabled(DRM_UT_ ## category) && __ratelimit(&rs_))			\
		drm_dev_prपूर्णांकk(drm_ ? drm_->dev : शून्य, KERN_DEBUG, fmt, ## __VA_ARGS__);	\
पूर्ण)

#घोषणा drm_dbg_kms_ratelimited(drm, fmt, ...) \
	__DRM_DEFINE_DBG_RATELIMITED(KMS, drm, fmt, ## __VA_ARGS__)

#घोषणा DRM_DEBUG_KMS_RATELIMITED(fmt, ...) drm_dbg_kms_ratelimited(शून्य, fmt, ## __VA_ARGS__)

/*
 * काष्ठा drm_device based WARNs
 *
 * drm_WARN*() acts like WARN*(), but with the key dअगरference of
 * using device specअगरic inक्रमmation so that we know from which device
 * warning is originating from.
 *
 * Prefer drm_device based drm_WARN* over regular WARN*
 */

/* Helper क्रम काष्ठा drm_device based WARNs */
#घोषणा drm_WARN(drm, condition, क्रमmat, arg...)			\
	WARN(condition, "%s %s: " क्रमmat,				\
			dev_driver_string((drm)->dev),			\
			dev_name((drm)->dev), ## arg)

#घोषणा drm_WARN_ONCE(drm, condition, क्रमmat, arg...)			\
	WARN_ONCE(condition, "%s %s: " क्रमmat,				\
			dev_driver_string((drm)->dev),			\
			dev_name((drm)->dev), ## arg)

#घोषणा drm_WARN_ON(drm, x)						\
	drm_WARN((drm), (x), "%s",					\
		 "drm_WARN_ON(" __stringअगरy(x) ")")

#घोषणा drm_WARN_ON_ONCE(drm, x)					\
	drm_WARN_ONCE((drm), (x), "%s",					\
		      "drm_WARN_ON_ONCE(" __stringअगरy(x) ")")

#पूर्ण_अगर /* DRM_PRINT_H_ */
