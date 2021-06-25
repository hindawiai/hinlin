<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __COW_SYS_H__
#घोषणा __COW_SYS_H__

#समावेश <kern_util.h>
#समावेश <os.h>
#समावेश <um_दो_स्मृति.h>

अटल अंतरभूत व्योम *cow_दो_स्मृति(पूर्णांक size)
अणु
	वापस uml_kदो_स्मृति(size, UM_GFP_KERNEL);
पूर्ण

अटल अंतरभूत व्योम cow_मुक्त(व्योम *ptr)
अणु
	kमुक्त(ptr);
पूर्ण

#घोषणा cow_म_लिखो prपूर्णांकk

अटल अंतरभूत अक्षर *cow_strdup(अक्षर *str)
अणु
	वापस uml_strdup(str);
पूर्ण

अटल अंतरभूत पूर्णांक cow_seek_file(पूर्णांक fd, __u64 offset)
अणु
	वापस os_seek_file(fd, offset);
पूर्ण

अटल अंतरभूत पूर्णांक cow_file_size(अक्षर *file, अचिन्हित दीर्घ दीर्घ *size_out)
अणु
	वापस os_file_size(file, size_out);
पूर्ण

अटल अंतरभूत पूर्णांक cow_ग_लिखो_file(पूर्णांक fd, व्योम *buf, पूर्णांक size)
अणु
	वापस os_ग_लिखो_file(fd, buf, size);
पूर्ण

#पूर्ण_अगर
