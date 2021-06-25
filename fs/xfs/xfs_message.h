<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __XFS_MESSAGE_H
#घोषणा __XFS_MESSAGE_H 1

काष्ठा xfs_mount;

बाह्य __म_लिखो(2, 3)
व्योम xfs_emerg(स्थिर काष्ठा xfs_mount *mp, स्थिर अक्षर *fmt, ...);
बाह्य __म_लिखो(2, 3)
व्योम xfs_alert(स्थिर काष्ठा xfs_mount *mp, स्थिर अक्षर *fmt, ...);
बाह्य __म_लिखो(3, 4)
व्योम xfs_alert_tag(स्थिर काष्ठा xfs_mount *mp, पूर्णांक tag, स्थिर अक्षर *fmt, ...);
बाह्य __म_लिखो(2, 3)
व्योम xfs_crit(स्थिर काष्ठा xfs_mount *mp, स्थिर अक्षर *fmt, ...);
बाह्य __म_लिखो(2, 3)
व्योम xfs_err(स्थिर काष्ठा xfs_mount *mp, स्थिर अक्षर *fmt, ...);
बाह्य __म_लिखो(2, 3)
व्योम xfs_warn(स्थिर काष्ठा xfs_mount *mp, स्थिर अक्षर *fmt, ...);
बाह्य __म_लिखो(2, 3)
व्योम xfs_notice(स्थिर काष्ठा xfs_mount *mp, स्थिर अक्षर *fmt, ...);
बाह्य __म_लिखो(2, 3)
व्योम xfs_info(स्थिर काष्ठा xfs_mount *mp, स्थिर अक्षर *fmt, ...);

#अगर_घोषित DEBUG
बाह्य __म_लिखो(2, 3)
व्योम xfs_debug(स्थिर काष्ठा xfs_mount *mp, स्थिर अक्षर *fmt, ...);
#अन्यथा
अटल अंतरभूत __म_लिखो(2, 3)
व्योम xfs_debug(स्थिर काष्ठा xfs_mount *mp, स्थिर अक्षर *fmt, ...)
अणु
पूर्ण
#पूर्ण_अगर

#घोषणा xfs_prपूर्णांकk_ratelimited(func, dev, fmt, ...)			\
करो अणु									\
	अटल DEFINE_RATELIMIT_STATE(_rs,				\
				      DEFAULT_RATELIMIT_INTERVAL,	\
				      DEFAULT_RATELIMIT_BURST);		\
	अगर (__ratelimit(&_rs))						\
		func(dev, fmt, ##__VA_ARGS__);				\
पूर्ण जबतक (0)

#घोषणा xfs_prपूर्णांकk_once(func, dev, fmt, ...)			\
(अणु								\
	अटल bool __section(".data.once") __prपूर्णांक_once;	\
	bool __ret_prपूर्णांक_once = !__prपूर्णांक_once; 			\
								\
	अगर (!__prपूर्णांक_once) अणु					\
		__prपूर्णांक_once = true;				\
		func(dev, fmt, ##__VA_ARGS__);			\
	पूर्ण							\
	unlikely(__ret_prपूर्णांक_once);				\
पूर्ण)

#घोषणा xfs_emerg_ratelimited(dev, fmt, ...)				\
	xfs_prपूर्णांकk_ratelimited(xfs_emerg, dev, fmt, ##__VA_ARGS__)
#घोषणा xfs_alert_ratelimited(dev, fmt, ...)				\
	xfs_prपूर्णांकk_ratelimited(xfs_alert, dev, fmt, ##__VA_ARGS__)
#घोषणा xfs_crit_ratelimited(dev, fmt, ...)				\
	xfs_prपूर्णांकk_ratelimited(xfs_crit, dev, fmt, ##__VA_ARGS__)
#घोषणा xfs_err_ratelimited(dev, fmt, ...)				\
	xfs_prपूर्णांकk_ratelimited(xfs_err, dev, fmt, ##__VA_ARGS__)
#घोषणा xfs_warn_ratelimited(dev, fmt, ...)				\
	xfs_prपूर्णांकk_ratelimited(xfs_warn, dev, fmt, ##__VA_ARGS__)
#घोषणा xfs_notice_ratelimited(dev, fmt, ...)				\
	xfs_prपूर्णांकk_ratelimited(xfs_notice, dev, fmt, ##__VA_ARGS__)
#घोषणा xfs_info_ratelimited(dev, fmt, ...)				\
	xfs_prपूर्णांकk_ratelimited(xfs_info, dev, fmt, ##__VA_ARGS__)
#घोषणा xfs_debug_ratelimited(dev, fmt, ...)				\
	xfs_prपूर्णांकk_ratelimited(xfs_debug, dev, fmt, ##__VA_ARGS__)

#घोषणा xfs_warn_once(dev, fmt, ...)				\
	xfs_prपूर्णांकk_once(xfs_warn, dev, fmt, ##__VA_ARGS__)
#घोषणा xfs_notice_once(dev, fmt, ...)				\
	xfs_prपूर्णांकk_once(xfs_notice, dev, fmt, ##__VA_ARGS__)
#घोषणा xfs_info_once(dev, fmt, ...)				\
	xfs_prपूर्णांकk_once(xfs_info, dev, fmt, ##__VA_ARGS__)

व्योम assfail(काष्ठा xfs_mount *mp, अक्षर *expr, अक्षर *f, पूर्णांक l);
व्योम asswarn(काष्ठा xfs_mount *mp, अक्षर *expr, अक्षर *f, पूर्णांक l);

बाह्य व्योम xfs_hex_dump(स्थिर व्योम *p, पूर्णांक length);

व्योम xfs_buf_alert_ratelimited(काष्ठा xfs_buf *bp, स्थिर अक्षर *rlmsg,
			       स्थिर अक्षर *fmt, ...);

#पूर्ण_अगर	/* __XFS_MESSAGE_H */
