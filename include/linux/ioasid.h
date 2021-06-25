<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_IOASID_H
#घोषणा __LINUX_IOASID_H

#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>

#घोषणा INVALID_IOASID ((ioasid_t)-1)
प्रकार अचिन्हित पूर्णांक ioasid_t;
प्रकार ioasid_t (*ioasid_alloc_fn_t)(ioasid_t min, ioasid_t max, व्योम *data);
प्रकार व्योम (*ioasid_मुक्त_fn_t)(ioasid_t ioasid, व्योम *data);

काष्ठा ioasid_set अणु
	पूर्णांक dummy;
पूर्ण;

/**
 * काष्ठा ioasid_allocator_ops - IOASID allocator helper functions and data
 *
 * @alloc:	helper function to allocate IOASID
 * @मुक्त:	helper function to मुक्त IOASID
 * @list:	क्रम tracking ops that share helper functions but not data
 * @pdata:	data beदीर्घ to the allocator, provided when calling alloc()
 */
काष्ठा ioasid_allocator_ops अणु
	ioasid_alloc_fn_t alloc;
	ioasid_मुक्त_fn_t मुक्त;
	काष्ठा list_head list;
	व्योम *pdata;
पूर्ण;

#घोषणा DECLARE_IOASID_SET(name) काष्ठा ioasid_set name = अणु 0 पूर्ण

#अगर IS_ENABLED(CONFIG_IOASID)
ioasid_t ioasid_alloc(काष्ठा ioasid_set *set, ioasid_t min, ioasid_t max,
		      व्योम *निजी);
व्योम ioasid_get(ioasid_t ioasid);
bool ioasid_put(ioasid_t ioasid);
व्योम *ioasid_find(काष्ठा ioasid_set *set, ioasid_t ioasid,
		  bool (*getter)(व्योम *));
पूर्णांक ioasid_रेजिस्टर_allocator(काष्ठा ioasid_allocator_ops *allocator);
व्योम ioasid_unरेजिस्टर_allocator(काष्ठा ioasid_allocator_ops *allocator);
पूर्णांक ioasid_set_data(ioasid_t ioasid, व्योम *data);

#अन्यथा /* !CONFIG_IOASID */
अटल अंतरभूत ioasid_t ioasid_alloc(काष्ठा ioasid_set *set, ioasid_t min,
				    ioasid_t max, व्योम *निजी)
अणु
	वापस INVALID_IOASID;
पूर्ण

अटल अंतरभूत व्योम ioasid_get(ioasid_t ioasid)
अणु
पूर्ण

अटल अंतरभूत bool ioasid_put(ioasid_t ioasid)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत व्योम *ioasid_find(काष्ठा ioasid_set *set, ioasid_t ioasid,
				bool (*getter)(व्योम *))
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक ioasid_रेजिस्टर_allocator(काष्ठा ioasid_allocator_ops *allocator)
अणु
	वापस -ENOTSUPP;
पूर्ण

अटल अंतरभूत व्योम ioasid_unरेजिस्टर_allocator(काष्ठा ioasid_allocator_ops *allocator)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक ioasid_set_data(ioasid_t ioasid, व्योम *data)
अणु
	वापस -ENOTSUPP;
पूर्ण

#पूर्ण_अगर /* CONFIG_IOASID */
#पूर्ण_अगर /* __LINUX_IOASID_H */
