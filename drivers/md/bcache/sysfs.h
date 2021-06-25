<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _BCACHE_SYSFS_H_
#घोषणा _BCACHE_SYSFS_H_

#घोषणा KTYPE(type)							\
काष्ठा kobj_type type ## _ktype = अणु					\
	.release	= type ## _release,				\
	.sysfs_ops	= &((स्थिर काष्ठा sysfs_ops) अणु			\
		.show	= type ## _show,				\
		.store	= type ## _store				\
	पूर्ण),								\
	.शेष_attrs	= type ## _files				\
पूर्ण

#घोषणा SHOW(fn)							\
अटल sमाप_प्रकार fn ## _show(काष्ठा kobject *kobj, काष्ठा attribute *attr,\
			   अक्षर *buf)					\

#घोषणा STORE(fn)							\
अटल sमाप_प्रकार fn ## _store(काष्ठा kobject *kobj, काष्ठा attribute *attr,\
			    स्थिर अक्षर *buf, माप_प्रकार size)		\

#घोषणा SHOW_LOCKED(fn)							\
SHOW(fn)								\
अणु									\
	sमाप_प्रकार ret;							\
	mutex_lock(&bch_रेजिस्टर_lock);					\
	ret = __ ## fn ## _show(kobj, attr, buf);			\
	mutex_unlock(&bch_रेजिस्टर_lock);				\
	वापस ret;							\
पूर्ण

#घोषणा STORE_LOCKED(fn)						\
STORE(fn)								\
अणु									\
	sमाप_प्रकार ret;							\
	mutex_lock(&bch_रेजिस्टर_lock);					\
	ret = __ ## fn ## _store(kobj, attr, buf, size);		\
	mutex_unlock(&bch_रेजिस्टर_lock);				\
	वापस ret;							\
पूर्ण

#घोषणा __sysfs_attribute(_name, _mode)					\
	अटल काष्ठा attribute sysfs_##_name =				\
		अणु .name = #_name, .mode = _mode पूर्ण

#घोषणा ग_लिखो_attribute(n)	__sysfs_attribute(n, 0200)
#घोषणा पढ़ो_attribute(n)	__sysfs_attribute(n, 0444)
#घोषणा rw_attribute(n)		__sysfs_attribute(n, 0644)

#घोषणा sysfs_म_लिखो(file, fmt, ...)					\
करो अणु									\
	अगर (attr == &sysfs_ ## file)					\
		वापस snम_लिखो(buf, PAGE_SIZE, fmt "\n", __VA_ARGS__);	\
पूर्ण जबतक (0)

#घोषणा sysfs_prपूर्णांक(file, var)						\
करो अणु									\
	अगर (attr == &sysfs_ ## file)					\
		वापस snprपूर्णांक(buf, PAGE_SIZE, var);			\
पूर्ण जबतक (0)

#घोषणा sysfs_hprपूर्णांक(file, val)						\
करो अणु									\
	अगर (attr == &sysfs_ ## file) अणु					\
		sमाप_प्रकार ret = bch_hprपूर्णांक(buf, val);			\
		म_जोड़ो(buf, "\n");					\
		वापस ret + 1;						\
	पूर्ण								\
पूर्ण जबतक (0)

#घोषणा var_म_लिखो(_var, fmt)	sysfs_म_लिखो(_var, fmt, var(_var))
#घोषणा var_prपूर्णांक(_var)		sysfs_prपूर्णांक(_var, var(_var))
#घोषणा var_hprपूर्णांक(_var)	sysfs_hprपूर्णांक(_var, var(_var))

#घोषणा sysfs_म_से_अदीर्घ(file, var)					\
करो अणु									\
	अगर (attr == &sysfs_ ## file)					\
		वापस म_से_अदीर्घ_safe(buf, var) ?: (sमाप_प्रकार) size;	\
पूर्ण जबतक (0)

#घोषणा sysfs_म_से_अदीर्घ_bool(file, var)					\
करो अणु									\
	अगर (attr == &sysfs_ ## file) अणु					\
		अचिन्हित दीर्घ v = म_से_अदीर्घ_or_वापस(buf);		\
									\
		var = v ? 1 : 0;					\
		वापस size;						\
	पूर्ण								\
पूर्ण जबतक (0)

#घोषणा sysfs_म_से_अदीर्घ_clamp(file, var, min, max)			\
करो अणु									\
	अगर (attr == &sysfs_ ## file) अणु					\
		अचिन्हित दीर्घ v = 0;					\
		sमाप_प्रकार ret;						\
		ret = म_से_अदीर्घ_safe_clamp(buf, v, min, max);		\
		अगर (!ret) अणु						\
			var = v;					\
			वापस size;					\
		पूर्ण							\
		वापस ret;						\
	पूर्ण								\
पूर्ण जबतक (0)

#घोषणा म_से_अदीर्घ_or_वापस(cp)						\
(अणु									\
	अचिन्हित दीर्घ _v;						\
	पूर्णांक _r = kम_से_अदीर्घ(cp, 10, &_v);					\
	अगर (_r)								\
		वापस _r;						\
	_v;								\
पूर्ण)

#घोषणा strtoi_h_or_वापस(cp, v)					\
करो अणु									\
	पूर्णांक _r = strtoi_h(cp, &v);					\
	अगर (_r)								\
		वापस _r;						\
पूर्ण जबतक (0)

#घोषणा sysfs_hम_से_प(file, var)						\
करो अणु									\
	अगर (attr == &sysfs_ ## file)					\
		वापस strtoi_h(buf, &var) ?: (sमाप_प्रकार) size;		\
पूर्ण जबतक (0)

#पूर्ण_अगर  /* _BCACHE_SYSFS_H_ */
