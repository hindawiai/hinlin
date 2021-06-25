<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_COREDUMP_H
#घोषणा _LINUX_COREDUMP_H

#समावेश <linux/types.h>
#समावेश <linux/mm.h>
#समावेश <linux/fs.h>
#समावेश <यंत्र/siginfo.h>

#अगर_घोषित CONFIG_COREDUMP
काष्ठा core_vma_metadata अणु
	अचिन्हित दीर्घ start, end;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ dump_size;
पूर्ण;

बाह्य पूर्णांक core_uses_pid;
बाह्य अक्षर core_pattern[];
बाह्य अचिन्हित पूर्णांक core_pipe_limit;

/*
 * These are the only things you should करो on a core-file: use only these
 * functions to ग_लिखो out all the necessary info.
 */
काष्ठा coredump_params;
बाह्य व्योम dump_skip_to(काष्ठा coredump_params *cprm, अचिन्हित दीर्घ to);
बाह्य व्योम dump_skip(काष्ठा coredump_params *cprm, माप_प्रकार nr);
बाह्य पूर्णांक dump_emit(काष्ठा coredump_params *cprm, स्थिर व्योम *addr, पूर्णांक nr);
बाह्य पूर्णांक dump_align(काष्ठा coredump_params *cprm, पूर्णांक align);
पूर्णांक dump_user_range(काष्ठा coredump_params *cprm, अचिन्हित दीर्घ start,
		    अचिन्हित दीर्घ len);
पूर्णांक dump_vma_snapshot(काष्ठा coredump_params *cprm, पूर्णांक *vma_count,
		      काष्ठा core_vma_metadata **vma_meta,
		      माप_प्रकार *vma_data_size_ptr);
बाह्य व्योम करो_coredump(स्थिर kernel_siginfo_t *siginfo);
#अन्यथा
अटल अंतरभूत व्योम करो_coredump(स्थिर kernel_siginfo_t *siginfo) अणुपूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _LINUX_COREDUMP_H */
