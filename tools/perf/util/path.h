<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _PERF_PATH_H
#घोषणा _PERF_PATH_H

#समावेश <मानकघोष.स>
#समावेश <stdbool.h>

काष्ठा dirent;

पूर्णांक path__join(अक्षर *bf, माप_प्रकार size, स्थिर अक्षर *path1, स्थिर अक्षर *path2);
पूर्णांक path__join3(अक्षर *bf, माप_प्रकार size, स्थिर अक्षर *path1, स्थिर अक्षर *path2, स्थिर अक्षर *path3);

bool is_regular_file(स्थिर अक्षर *file);
bool is_directory(स्थिर अक्षर *base_path, स्थिर काष्ठा dirent *dent);

#पूर्ण_अगर /* _PERF_PATH_H */
