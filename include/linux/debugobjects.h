<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_DEBUGOBJECTS_H
#घोषणा _LINUX_DEBUGOBJECTS_H

#समावेश <linux/list.h>
#समावेश <linux/spinlock.h>

क्रमागत debug_obj_state अणु
	ODEBUG_STATE_NONE,
	ODEBUG_STATE_INIT,
	ODEBUG_STATE_INACTIVE,
	ODEBUG_STATE_ACTIVE,
	ODEBUG_STATE_DESTROYED,
	ODEBUG_STATE_NOTAVAILABLE,
	ODEBUG_STATE_MAX,
पूर्ण;

काष्ठा debug_obj_descr;

/**
 * काष्ठा debug_obj - representaion of an tracked object
 * @node:	hlist node to link the object पूर्णांकo the tracker list
 * @state:	tracked object state
 * @astate:	current active state
 * @object:	poपूर्णांकer to the real object
 * @descr:	poपूर्णांकer to an object type specअगरic debug description काष्ठाure
 */
काष्ठा debug_obj अणु
	काष्ठा hlist_node	node;
	क्रमागत debug_obj_state	state;
	अचिन्हित पूर्णांक		astate;
	व्योम			*object;
	स्थिर काष्ठा debug_obj_descr *descr;
पूर्ण;

/**
 * काष्ठा debug_obj_descr - object type specअगरic debug description काष्ठाure
 *
 * @name:		name of the object typee
 * @debug_hपूर्णांक:		function वापसing address, which have associated
 *			kernel symbol, to allow identअगरy the object
 * @is_अटल_object:	वापस true अगर the obj is अटल, otherwise वापस false
 * @fixup_init:		fixup function, which is called when the init check
 *			fails. All fixup functions must वापस true अगर fixup
 *			was successful, otherwise वापस false
 * @fixup_activate:	fixup function, which is called when the activate check
 *			fails
 * @fixup_destroy:	fixup function, which is called when the destroy check
 *			fails
 * @fixup_मुक्त:		fixup function, which is called when the मुक्त check
 *			fails
 * @fixup_निश्चित_init:  fixup function, which is called when the निश्चित_init
 *			check fails
 */
काष्ठा debug_obj_descr अणु
	स्थिर अक्षर		*name;
	व्योम *(*debug_hपूर्णांक)(व्योम *addr);
	bool (*is_अटल_object)(व्योम *addr);
	bool (*fixup_init)(व्योम *addr, क्रमागत debug_obj_state state);
	bool (*fixup_activate)(व्योम *addr, क्रमागत debug_obj_state state);
	bool (*fixup_destroy)(व्योम *addr, क्रमागत debug_obj_state state);
	bool (*fixup_मुक्त)(व्योम *addr, क्रमागत debug_obj_state state);
	bool (*fixup_निश्चित_init)(व्योम *addr, क्रमागत debug_obj_state state);
पूर्ण;

#अगर_घोषित CONFIG_DEBUG_OBJECTS
बाह्य व्योम debug_object_init      (व्योम *addr, स्थिर काष्ठा debug_obj_descr *descr);
बाह्य व्योम
debug_object_init_on_stack(व्योम *addr, स्थिर काष्ठा debug_obj_descr *descr);
बाह्य पूर्णांक debug_object_activate  (व्योम *addr, स्थिर काष्ठा debug_obj_descr *descr);
बाह्य व्योम debug_object_deactivate(व्योम *addr, स्थिर काष्ठा debug_obj_descr *descr);
बाह्य व्योम debug_object_destroy   (व्योम *addr, स्थिर काष्ठा debug_obj_descr *descr);
बाह्य व्योम debug_object_मुक्त      (व्योम *addr, स्थिर काष्ठा debug_obj_descr *descr);
बाह्य व्योम debug_object_निश्चित_init(व्योम *addr, स्थिर काष्ठा debug_obj_descr *descr);

/*
 * Active state:
 * - Set at 0 upon initialization.
 * - Must वापस to 0 beक्रमe deactivation.
 */
बाह्य व्योम
debug_object_active_state(व्योम *addr, स्थिर काष्ठा debug_obj_descr *descr,
			  अचिन्हित पूर्णांक expect, अचिन्हित पूर्णांक next);

बाह्य व्योम debug_objects_early_init(व्योम);
बाह्य व्योम debug_objects_mem_init(व्योम);
#अन्यथा
अटल अंतरभूत व्योम
debug_object_init      (व्योम *addr, स्थिर काष्ठा debug_obj_descr *descr) अणु पूर्ण
अटल अंतरभूत व्योम
debug_object_init_on_stack(व्योम *addr, स्थिर काष्ठा debug_obj_descr *descr) अणु पूर्ण
अटल अंतरभूत पूर्णांक
debug_object_activate  (व्योम *addr, स्थिर काष्ठा debug_obj_descr *descr) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम
debug_object_deactivate(व्योम *addr, स्थिर काष्ठा debug_obj_descr *descr) अणु पूर्ण
अटल अंतरभूत व्योम
debug_object_destroy   (व्योम *addr, स्थिर काष्ठा debug_obj_descr *descr) अणु पूर्ण
अटल अंतरभूत व्योम
debug_object_मुक्त      (व्योम *addr, स्थिर काष्ठा debug_obj_descr *descr) अणु पूर्ण
अटल अंतरभूत व्योम
debug_object_निश्चित_init(व्योम *addr, स्थिर काष्ठा debug_obj_descr *descr) अणु पूर्ण

अटल अंतरभूत व्योम debug_objects_early_init(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम debug_objects_mem_init(व्योम) अणु पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_DEBUG_OBJECTS_FREE
बाह्य व्योम debug_check_no_obj_मुक्तd(स्थिर व्योम *address, अचिन्हित दीर्घ size);
#अन्यथा
अटल अंतरभूत व्योम
debug_check_no_obj_मुक्तd(स्थिर व्योम *address, अचिन्हित दीर्घ size) अणु पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
