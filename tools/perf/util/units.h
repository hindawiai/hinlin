<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित PERF_UNIT_H
#घोषणा PERF_UNIT_H

#समावेश <मानकघोष.स>
#समावेश <linux/types.h>

काष्ठा parse_tag अणु
	अक्षर tag;
	पूर्णांक  mult;
पूर्ण;

अचिन्हित दीर्घ parse_tag_value(स्थिर अक्षर *str, काष्ठा parse_tag *tags);

द्विगुन convert_unit_द्विगुन(द्विगुन value, अक्षर *unit);
अचिन्हित दीर्घ convert_unit(अचिन्हित दीर्घ value, अक्षर *unit);
पूर्णांक unit_number__scnम_लिखो(अक्षर *buf, माप_प्रकार size, u64 n);

#पूर्ण_अगर /* PERF_UNIT_H */
