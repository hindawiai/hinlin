<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c) 2020 Facebook */
#अगर_अघोषित __BTF_HELPERS_H
#घोषणा __BTF_HELPERS_H

#समावेश <मानकपन.स>
#समावेश <bpf/btf.h>

पूर्णांक ख_लिखो_btf_type_raw(खाता *out, स्थिर काष्ठा btf *btf, __u32 id);
स्थिर अक्षर *btf_type_raw_dump(स्थिर काष्ठा btf *btf, पूर्णांक type_id);
पूर्णांक btf_validate_raw(काष्ठा btf *btf, पूर्णांक nr_types, स्थिर अक्षर *exp_types[]);

#घोषणा VALIDATE_RAW_BTF(btf, raw_types...)				\
	btf_validate_raw(btf,						\
			 माप((स्थिर अक्षर *[])अणुraw_typesपूर्ण)/माप(व्योम *),\
			 (स्थिर अक्षर *[])अणुraw_typesपूर्ण)

स्थिर अक्षर *btf_type_c_dump(स्थिर काष्ठा btf *btf);
#पूर्ण_अगर
