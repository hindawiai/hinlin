<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LIBLOCKDEP_COMMON_H
#घोषणा _LIBLOCKDEP_COMMON_H

#समावेश <pthपढ़ो.h>

#घोषणा NR_LOCKDEP_CACHING_CLASSES 2
#घोषणा MAX_LOCKDEP_SUBCLASSES 8UL

#अगर_अघोषित CALLER_ADDR0
#घोषणा CALLER_ADDR0 ((अचिन्हित दीर्घ)__builtin_वापस_address(0))
#पूर्ण_अगर

#अगर_अघोषित _RET_IP_
#घोषणा _RET_IP_ CALLER_ADDR0
#पूर्ण_अगर

#अगर_अघोषित _THIS_IP_
#घोषणा _THIS_IP_ (अणु __label__ __here; __here: (अचिन्हित दीर्घ)&&__here; पूर्ण)
#पूर्ण_अगर

काष्ठा lockdep_subclass_key अणु
	अक्षर __one_byte;
पूर्ण;

काष्ठा lock_class_key अणु
	काष्ठा lockdep_subclass_key subkeys[MAX_LOCKDEP_SUBCLASSES];
पूर्ण;

काष्ठा lockdep_map अणु
	काष्ठा lock_class_key	*key;
	काष्ठा lock_class	*class_cache[NR_LOCKDEP_CACHING_CLASSES];
	स्थिर अक्षर		*name;
#अगर_घोषित CONFIG_LOCK_STAT
	पूर्णांक			cpu;
	अचिन्हित दीर्घ		ip;
#पूर्ण_अगर
पूर्ण;

व्योम lockdep_init_map(काष्ठा lockdep_map *lock, स्थिर अक्षर *name,
			काष्ठा lock_class_key *key, पूर्णांक subclass);
व्योम lock_acquire(काष्ठा lockdep_map *lock, अचिन्हित पूर्णांक subclass,
			पूर्णांक trylock, पूर्णांक पढ़ो, पूर्णांक check,
			काष्ठा lockdep_map *nest_lock, अचिन्हित दीर्घ ip);
व्योम lock_release(काष्ठा lockdep_map *lock, अचिन्हित दीर्घ ip);
व्योम lockdep_reset_lock(काष्ठा lockdep_map *lock);
व्योम lockdep_रेजिस्टर_key(काष्ठा lock_class_key *key);
व्योम lockdep_unरेजिस्टर_key(काष्ठा lock_class_key *key);
बाह्य व्योम debug_check_no_locks_मुक्तd(स्थिर व्योम *from, अचिन्हित दीर्घ len);

#घोषणा STATIC_LOCKDEP_MAP_INIT(_name, _key) \
	अणु .name = (_name), .key = (व्योम *)(_key), पूर्ण

#पूर्ण_अगर
