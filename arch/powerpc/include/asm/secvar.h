<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2019 IBM Corporation
 * Author: Nayna Jain
 *
 * PowerPC secure variable operations.
 */
#अगर_अघोषित SECVAR_OPS_H
#घोषणा SECVAR_OPS_H

#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>

बाह्य स्थिर काष्ठा secvar_operations *secvar_ops;

काष्ठा secvar_operations अणु
	पूर्णांक (*get)(स्थिर अक्षर *key, uपूर्णांक64_t key_len, u8 *data,
		   uपूर्णांक64_t *data_size);
	पूर्णांक (*get_next)(स्थिर अक्षर *key, uपूर्णांक64_t *key_len,
			uपूर्णांक64_t keybufsize);
	पूर्णांक (*set)(स्थिर अक्षर *key, uपूर्णांक64_t key_len, u8 *data,
		   uपूर्णांक64_t data_size);
पूर्ण;

#अगर_घोषित CONFIG_PPC_SECURE_BOOT

बाह्य व्योम set_secvar_ops(स्थिर काष्ठा secvar_operations *ops);

#अन्यथा

अटल अंतरभूत व्योम set_secvar_ops(स्थिर काष्ठा secvar_operations *ops) अणु पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर
