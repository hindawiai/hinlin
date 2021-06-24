<शैली गुरु>
/*
 * include/यंत्र-xtensa/platक्रमm-iss/simcall.h
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2001 Tensilica Inc.
 * Copyright (C) 2017 - 2021 Cadence Design Systems Inc.
 */

#अगर_अघोषित _XTENSA_PLATFORM_ISS_SIMCALL_H
#घोषणा _XTENSA_PLATFORM_ISS_SIMCALL_H

#समावेश <linux/bug.h>

#अगर_घोषित CONFIG_XTENSA_SIMCALL_ISS
#समावेश <platक्रमm/simcall-iss.h>
#पूर्ण_अगर
#अगर_घोषित CONFIG_XTENSA_SIMCALL_GDBIO
#समावेश <platक्रमm/simcall-gdbपन.स>
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक simc_निकास(पूर्णांक निकास_code)
अणु
#अगर_घोषित SYS_निकास
	वापस __simc(SYS_निकास, निकास_code, 0, 0);
#अन्यथा
	WARN_ONCE(1, "%s: not implemented\n", __func__);
	वापस -1;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत पूर्णांक simc_खोलो(स्थिर अक्षर *file, पूर्णांक flags, पूर्णांक mode)
अणु
	वापस __simc(SYS_खोलो, (पूर्णांक) file, flags, mode);
पूर्ण

अटल अंतरभूत पूर्णांक simc_बंद(पूर्णांक fd)
अणु
	वापस __simc(SYS_बंद, fd, 0, 0);
पूर्ण

अटल अंतरभूत पूर्णांक simc_ioctl(पूर्णांक fd, पूर्णांक request, व्योम *arg)
अणु
#अगर_घोषित SYS_ioctl
	वापस __simc(SYS_ioctl, fd, request, (पूर्णांक) arg);
#अन्यथा
	WARN_ONCE(1, "%s: not implemented\n", __func__);
	वापस -1;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत पूर्णांक simc_पढ़ो(पूर्णांक fd, व्योम *buf, माप_प्रकार count)
अणु
	वापस __simc(SYS_पढ़ो, fd, (पूर्णांक) buf, count);
पूर्ण

अटल अंतरभूत पूर्णांक simc_ग_लिखो(पूर्णांक fd, स्थिर व्योम *buf, माप_प्रकार count)
अणु
	वापस __simc(SYS_ग_लिखो, fd, (पूर्णांक) buf, count);
पूर्ण

अटल अंतरभूत पूर्णांक simc_poll(पूर्णांक fd)
अणु
#अगर_घोषित SYS_select_one
	दीर्घ समयval[2] = अणु 0, 0 पूर्ण;

	वापस __simc(SYS_select_one, fd, XTISS_SELECT_ONE_READ, (पूर्णांक)&समयval);
#अन्यथा
	WARN_ONCE(1, "%s: not implemented\n", __func__);
	वापस -1;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत पूर्णांक simc_lseek(पूर्णांक fd, uपूर्णांक32_t off, पूर्णांक whence)
अणु
	वापस __simc(SYS_lseek, fd, off, whence);
पूर्ण

अटल अंतरभूत पूर्णांक simc_argc(व्योम)
अणु
#अगर_घोषित SYS_iss_argc
	वापस __simc(SYS_iss_argc, 0, 0, 0);
#अन्यथा
	WARN_ONCE(1, "%s: not implemented\n", __func__);
	वापस 0;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत पूर्णांक simc_argv_size(व्योम)
अणु
#अगर_घोषित SYS_iss_argv_size
	वापस __simc(SYS_iss_argv_size, 0, 0, 0);
#अन्यथा
	WARN_ONCE(1, "%s: not implemented\n", __func__);
	वापस 0;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम simc_argv(व्योम *buf)
अणु
#अगर_घोषित SYS_iss_set_argv
	__simc(SYS_iss_set_argv, (पूर्णांक)buf, 0, 0);
#अन्यथा
	WARN_ONCE(1, "%s: not implemented\n", __func__);
#पूर्ण_अगर
पूर्ण

#पूर्ण_अगर /* _XTENSA_PLATFORM_ISS_SIMCALL_H */
