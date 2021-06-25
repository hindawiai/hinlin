<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_OPTION_H__
#घोषणा __NVKM_OPTION_H__
#समावेश <core/os.h>

स्थिर अक्षर *nvkm_stropt(स्थिर अक्षर *optstr, स्थिर अक्षर *opt, पूर्णांक *len);
bool nvkm_boolopt(स्थिर अक्षर *optstr, स्थिर अक्षर *opt, bool value);
दीर्घ nvkm_दीर्घopt(स्थिर अक्षर *optstr, स्थिर अक्षर *opt, दीर्घ value);
पूर्णांक  nvkm_dbgopt(स्थिर अक्षर *optstr, स्थिर अक्षर *sub);

/* compares unterminated string 'str' with zero-terminated string 'cmp' */
अटल अंतरभूत पूर्णांक
strnहालcmpz(स्थिर अक्षर *str, स्थिर अक्षर *cmp, माप_प्रकार len)
अणु
	अगर (म_माप(cmp) != len)
		वापस len;
	वापस strnहालcmp(str, cmp, len);
पूर्ण
#पूर्ण_अगर
