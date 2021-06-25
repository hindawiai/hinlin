<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_KASAN_CHECKS_H
#घोषणा _LINUX_KASAN_CHECKS_H

#समावेश <linux/types.h>

/*
 * The annotations present in this file are only relevant क्रम the software
 * KASAN modes that rely on compiler instrumentation, and will be optimized
 * away क्रम the hardware tag-based KASAN mode. Use kasan_check_byte() instead.
 */

/*
 * __kasan_check_*: Always available when KASAN is enabled. This may be used
 * even in compilation units that selectively disable KASAN, but must use KASAN
 * to validate access to an address.   Never use these in header files!
 */
#अगर defined(CONFIG_KASAN_GENERIC) || defined(CONFIG_KASAN_SW_TAGS)
bool __kasan_check_पढ़ो(स्थिर अस्थिर व्योम *p, अचिन्हित पूर्णांक size);
bool __kasan_check_ग_लिखो(स्थिर अस्थिर व्योम *p, अचिन्हित पूर्णांक size);
#अन्यथा
अटल अंतरभूत bool __kasan_check_पढ़ो(स्थिर अस्थिर व्योम *p, अचिन्हित पूर्णांक size)
अणु
	वापस true;
पूर्ण
अटल अंतरभूत bool __kasan_check_ग_लिखो(स्थिर अस्थिर व्योम *p, अचिन्हित पूर्णांक size)
अणु
	वापस true;
पूर्ण
#पूर्ण_अगर

/*
 * kasan_check_*: Only available when the particular compilation unit has KASAN
 * instrumentation enabled. May be used in header files.
 */
#अगर_घोषित __SANITIZE_ADDRESS__
#घोषणा kasan_check_पढ़ो __kasan_check_पढ़ो
#घोषणा kasan_check_ग_लिखो __kasan_check_ग_लिखो
#अन्यथा
अटल अंतरभूत bool kasan_check_पढ़ो(स्थिर अस्थिर व्योम *p, अचिन्हित पूर्णांक size)
अणु
	वापस true;
पूर्ण
अटल अंतरभूत bool kasan_check_ग_लिखो(स्थिर अस्थिर व्योम *p, अचिन्हित पूर्णांक size)
अणु
	वापस true;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
