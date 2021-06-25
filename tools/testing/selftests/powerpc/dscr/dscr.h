<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * POWER Data Stream Control Register (DSCR)
 *
 * This header file contains helper functions and macros
 * required क्रम all the DSCR related test हालs.
 *
 * Copyright 2012, Anton Blanअक्षरd, IBM Corporation.
 * Copyright 2015, Anshuman Khandual, IBM Corporation.
 */
#अगर_अघोषित _SELFTESTS_POWERPC_DSCR_DSCR_H
#घोषणा _SELFTESTS_POWERPC_DSCR_DSCR_H

#समावेश <unistd.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <fcntl.h>
#समावेश <dirent.h>
#समावेश <pthपढ़ो.h>
#समावेश <sched.h>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/रुको.h>

#समावेश "utils.h"

#घोषणा THREADS		100	/* Max thपढ़ोs */
#घोषणा COUNT		100	/* Max iterations */
#घोषणा DSCR_MAX	16	/* Max DSCR value */
#घोषणा LEN_MAX		100	/* Max name length */

#घोषणा DSCR_DEFAULT	"/sys/devices/system/cpu/dscr_default"
#घोषणा CPU_PATH	"/sys/devices/system/cpu/"

#घोषणा rmb()  यंत्र अस्थिर("lwsync":::"memory")
#घोषणा wmb()  यंत्र अस्थिर("lwsync":::"memory")

#घोषणा READ_ONCE(x) (*(अस्थिर typeof(x) *)&(x))

/* Prilvilege state DSCR access */
अंतरभूत अचिन्हित दीर्घ get_dscr(व्योम)
अणु
	अचिन्हित दीर्घ ret;

	यंत्र अस्थिर("mfspr %0,%1" : "=r" (ret) : "i" (SPRN_DSCR_PRIV));

	वापस ret;
पूर्ण

अंतरभूत व्योम set_dscr(अचिन्हित दीर्घ val)
अणु
	यंत्र अस्थिर("mtspr %1,%0" : : "r" (val), "i" (SPRN_DSCR_PRIV));
पूर्ण

/* Problem state DSCR access */
अंतरभूत अचिन्हित दीर्घ get_dscr_usr(व्योम)
अणु
	अचिन्हित दीर्घ ret;

	यंत्र अस्थिर("mfspr %0,%1" : "=r" (ret) : "i" (SPRN_DSCR));

	वापस ret;
पूर्ण

अंतरभूत व्योम set_dscr_usr(अचिन्हित दीर्घ val)
अणु
	यंत्र अस्थिर("mtspr %1,%0" : : "r" (val), "i" (SPRN_DSCR));
पूर्ण

/* Default DSCR access */
अचिन्हित दीर्घ get_शेष_dscr(व्योम)
अणु
	पूर्णांक fd = -1, ret;
	अक्षर buf[16];
	अचिन्हित दीर्घ val;

	अगर (fd == -1) अणु
		fd = खोलो(DSCR_DEFAULT, O_RDONLY);
		अगर (fd == -1) अणु
			लिखो_त्रुटि("open() failed");
			निकास(1);
		पूर्ण
	पूर्ण
	स_रखो(buf, 0, माप(buf));
	lseek(fd, 0, शुरू_से);
	ret = पढ़ो(fd, buf, माप(buf));
	अगर (ret == -1) अणु
		लिखो_त्रुटि("read() failed");
		निकास(1);
	पूर्ण
	माला_पूछो(buf, "%lx", &val);
	बंद(fd);
	वापस val;
पूर्ण

व्योम set_शेष_dscr(अचिन्हित दीर्घ val)
अणु
	पूर्णांक fd = -1, ret;
	अक्षर buf[16];

	अगर (fd == -1) अणु
		fd = खोलो(DSCR_DEFAULT, O_RDWR);
		अगर (fd == -1) अणु
			लिखो_त्रुटि("open() failed");
			निकास(1);
		पूर्ण
	पूर्ण
	प्र_लिखो(buf, "%lx\n", val);
	ret = ग_लिखो(fd, buf, म_माप(buf));
	अगर (ret == -1) अणु
		लिखो_त्रुटि("write() failed");
		निकास(1);
	पूर्ण
	बंद(fd);
पूर्ण

द्विगुन unअगरorm_deviate(पूर्णांक seed)
अणु
	वापस seed * (1.0 / (अक्रम_उच्च + 1.0));
पूर्ण
#पूर्ण_अगर	/* _SELFTESTS_POWERPC_DSCR_DSCR_H */
