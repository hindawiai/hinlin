<शैली गुरु>
/* SPDX-License-Identअगरier: (LGPL-2.1 OR BSD-2-Clause) */

/* Copyright (c) 2021 Facebook */
#अगर_अघोषित __LIBBPF_STRSET_H
#घोषणा __LIBBPF_STRSET_H

#समावेश <stdbool.h>
#समावेश <मानकघोष.स>

काष्ठा strset;

काष्ठा strset *strset__new(माप_प्रकार max_data_sz, स्थिर अक्षर *init_data, माप_प्रकार init_data_sz);
व्योम strset__मुक्त(काष्ठा strset *set);

स्थिर अक्षर *strset__data(स्थिर काष्ठा strset *set);
माप_प्रकार strset__data_size(स्थिर काष्ठा strset *set);

पूर्णांक strset__find_str(काष्ठा strset *set, स्थिर अक्षर *s);
पूर्णांक strset__add_str(काष्ठा strset *set, स्थिर अक्षर *s);

#पूर्ण_अगर /* __LIBBPF_STRSET_H */
