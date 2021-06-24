<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _MEMREGION_H_
#घोषणा _MEMREGION_H_
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>

काष्ठा memregion_info अणु
	पूर्णांक target_node;
पूर्ण;

#अगर_घोषित CONFIG_MEMREGION
पूर्णांक memregion_alloc(gfp_t gfp);
व्योम memregion_मुक्त(पूर्णांक id);
#अन्यथा
अटल अंतरभूत पूर्णांक memregion_alloc(gfp_t gfp)
अणु
	वापस -ENOMEM;
पूर्ण
व्योम memregion_मुक्त(पूर्णांक id)
अणु
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर /* _MEMREGION_H_ */
