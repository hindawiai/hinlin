<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __API_FS_TRACING_PATH_H
#घोषणा __API_FS_TRACING_PATH_H

#समावेश <linux/types.h>
#समावेश <dirent.h>

सूची *tracing_events__सूची_खोलो(व्योम);

व्योम tracing_path_set(स्थिर अक्षर *mountpoपूर्णांक);
स्थिर अक्षर *tracing_path_mount(व्योम);

अक्षर *get_tracing_file(स्थिर अक्षर *name);
व्योम put_tracing_file(अक्षर *file);

अक्षर *get_events_file(स्थिर अक्षर *name);
व्योम put_events_file(अक्षर *file);

#घोषणा zput_events_file(ptr) (अणु मुक्त(*ptr); *ptr = शून्य; पूर्ण)

पूर्णांक tracing_path__म_त्रुटि_खोलो_tp(पूर्णांक err, अक्षर *buf, माप_प्रकार size, स्थिर अक्षर *sys, स्थिर अक्षर *name);
#पूर्ण_अगर /* __API_FS_TRACING_PATH_H */
