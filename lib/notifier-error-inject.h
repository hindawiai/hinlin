<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#समावेश <linux/atomic.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/notअगरier.h>

काष्ठा notअगरier_err_inject_action अणु
	अचिन्हित दीर्घ val;
	पूर्णांक error;
	स्थिर अक्षर *name;
पूर्ण;

#घोषणा NOTIFIER_ERR_INJECT_ACTION(action)	\
	.name = #action, .val = (action),

काष्ठा notअगरier_err_inject अणु
	काष्ठा notअगरier_block nb;
	काष्ठा notअगरier_err_inject_action actions[];
	/* The last slot must be terminated with zero sentinel */
पूर्ण;

बाह्य काष्ठा dentry *notअगरier_err_inject_dir;

बाह्य काष्ठा dentry *notअगरier_err_inject_init(स्थिर अक्षर *name,
		काष्ठा dentry *parent, काष्ठा notअगरier_err_inject *err_inject,
		पूर्णांक priority);
