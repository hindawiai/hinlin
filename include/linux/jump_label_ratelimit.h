<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_JUMP_LABEL_RATELIMIT_H
#घोषणा _LINUX_JUMP_LABEL_RATELIMIT_H

#समावेश <linux/jump_label.h>
#समावेश <linux/workqueue.h>

#अगर defined(CONFIG_JUMP_LABEL)
काष्ठा अटल_key_deferred अणु
	काष्ठा अटल_key key;
	अचिन्हित दीर्घ समयout;
	काष्ठा delayed_work work;
पूर्ण;

काष्ठा अटल_key_true_deferred अणु
	काष्ठा अटल_key_true key;
	अचिन्हित दीर्घ समयout;
	काष्ठा delayed_work work;
पूर्ण;

काष्ठा अटल_key_false_deferred अणु
	काष्ठा अटल_key_false key;
	अचिन्हित दीर्घ समयout;
	काष्ठा delayed_work work;
पूर्ण;

#घोषणा अटल_key_slow_dec_deferred(x)					\
	__अटल_key_slow_dec_deferred(&(x)->key, &(x)->work, (x)->समयout)
#घोषणा अटल_branch_slow_dec_deferred(x)				\
	__अटल_key_slow_dec_deferred(&(x)->key.key, &(x)->work, (x)->समयout)

#घोषणा अटल_key_deferred_flush(x)					\
	__अटल_key_deferred_flush((x), &(x)->work)

बाह्य व्योम
__अटल_key_slow_dec_deferred(काष्ठा अटल_key *key,
			       काष्ठा delayed_work *work,
			       अचिन्हित दीर्घ समयout);
बाह्य व्योम __अटल_key_deferred_flush(व्योम *key, काष्ठा delayed_work *work);
बाह्य व्योम
jump_label_rate_limit(काष्ठा अटल_key_deferred *key, अचिन्हित दीर्घ rl);

बाह्य व्योम jump_label_update_समयout(काष्ठा work_काष्ठा *work);

#घोषणा DEFINE_STATIC_KEY_DEFERRED_TRUE(name, rl)			\
	काष्ठा अटल_key_true_deferred name = अणु			\
		.key =		अणु STATIC_KEY_INIT_TRUE पूर्ण,		\
		.समयout =	(rl),					\
		.work =	__DELAYED_WORK_INITIALIZER((name).work,		\
						   jump_label_update_समयout, \
						   0),			\
	पूर्ण

#घोषणा DEFINE_STATIC_KEY_DEFERRED_FALSE(name, rl)			\
	काष्ठा अटल_key_false_deferred name = अणु			\
		.key =		अणु STATIC_KEY_INIT_FALSE पूर्ण,		\
		.समयout =	(rl),					\
		.work =	__DELAYED_WORK_INITIALIZER((name).work,		\
						   jump_label_update_समयout, \
						   0),			\
	पूर्ण

#अन्यथा	/* !CONFIG_JUMP_LABEL */
काष्ठा अटल_key_deferred अणु
	काष्ठा अटल_key  key;
पूर्ण;
काष्ठा अटल_key_true_deferred अणु
	काष्ठा अटल_key_true key;
पूर्ण;
काष्ठा अटल_key_false_deferred अणु
	काष्ठा अटल_key_false key;
पूर्ण;
#घोषणा DEFINE_STATIC_KEY_DEFERRED_TRUE(name, rl)	\
	काष्ठा अटल_key_true_deferred name = अणु STATIC_KEY_TRUE_INIT पूर्ण
#घोषणा DEFINE_STATIC_KEY_DEFERRED_FALSE(name, rl)	\
	काष्ठा अटल_key_false_deferred name = अणु STATIC_KEY_FALSE_INIT पूर्ण

#घोषणा अटल_branch_slow_dec_deferred(x)	अटल_branch_dec(&(x)->key)

अटल अंतरभूत व्योम अटल_key_slow_dec_deferred(काष्ठा अटल_key_deferred *key)
अणु
	STATIC_KEY_CHECK_USE(key);
	अटल_key_slow_dec(&key->key);
पूर्ण
अटल अंतरभूत व्योम अटल_key_deferred_flush(व्योम *key)
अणु
	STATIC_KEY_CHECK_USE(key);
पूर्ण
अटल अंतरभूत व्योम
jump_label_rate_limit(काष्ठा अटल_key_deferred *key,
		अचिन्हित दीर्घ rl)
अणु
	STATIC_KEY_CHECK_USE(key);
पूर्ण
#पूर्ण_अगर	/* CONFIG_JUMP_LABEL */

#घोषणा अटल_branch_deferred_inc(x)	अटल_branch_inc(&(x)->key)

#पूर्ण_अगर	/* _LINUX_JUMP_LABEL_RATELIMIT_H */
