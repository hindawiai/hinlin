<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित __LINUX_KMOD_H__
#घोषणा __LINUX_KMOD_H__

/*
 *	include/linux/kmod.h
 */

#समावेश <linux/umh.h>
#समावेश <linux/gfp.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/compiler.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/sysctl.h>

#घोषणा KMOD_PATH_LEN 256

#अगर_घोषित CONFIG_MODULES
बाह्य अक्षर modprobe_path[]; /* क्रम sysctl */
/* modprobe निकास status on success, -ve on error.  Return value
 * usually useless though. */
बाह्य __म_लिखो(2, 3)
पूर्णांक __request_module(bool रुको, स्थिर अक्षर *name, ...);
#घोषणा request_module(mod...) __request_module(true, mod)
#घोषणा request_module_noरुको(mod...) __request_module(false, mod)
#घोषणा try_then_request_module(x, mod...) \
	((x) ?: (__request_module(true, mod), (x)))
#अन्यथा
अटल अंतरभूत पूर्णांक request_module(स्थिर अक्षर *name, ...) अणु वापस -ENOSYS; पूर्ण
अटल अंतरभूत पूर्णांक request_module_noरुको(स्थिर अक्षर *name, ...) अणु वापस -ENOSYS; पूर्ण
#घोषणा try_then_request_module(x, mod...) (x)
#पूर्ण_अगर

#पूर्ण_अगर /* __LINUX_KMOD_H__ */
