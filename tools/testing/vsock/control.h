<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
#अगर_अघोषित CONTROL_H
#घोषणा CONTROL_H

#समावेश <stdbool.h>

व्योम control_init(स्थिर अक्षर *control_host, स्थिर अक्षर *control_port,
		  bool server);
व्योम control_cleanup(व्योम);
व्योम control_ग_लिखोln(स्थिर अक्षर *str);
अक्षर *control_पढ़ोln(व्योम);
व्योम control_expectln(स्थिर अक्षर *str);
bool control_cmpln(अक्षर *line, स्थिर अक्षर *str, bool fail);

#पूर्ण_अगर /* CONTROL_H */
