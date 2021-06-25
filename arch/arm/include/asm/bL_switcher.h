<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * arch/arm/include/यंत्र/bL_चयनer.h
 *
 * Created by:  Nicolas Pitre, April 2012
 * Copyright:   (C) 2012-2013  Linaro Limited
 */

#अगर_अघोषित ASM_BL_SWITCHER_H
#घोषणा ASM_BL_SWITCHER_H

#समावेश <linux/compiler.h>
#समावेश <linux/types.h>

प्रकार व्योम (*bL_चयन_completion_handler)(व्योम *cookie);

पूर्णांक bL_चयन_request_cb(अचिन्हित पूर्णांक cpu, अचिन्हित पूर्णांक new_cluster_id,
			 bL_चयन_completion_handler completer,
			 व्योम *completer_cookie);
अटल अंतरभूत पूर्णांक bL_चयन_request(अचिन्हित पूर्णांक cpu, अचिन्हित पूर्णांक new_cluster_id)
अणु
	वापस bL_चयन_request_cb(cpu, new_cluster_id, शून्य, शून्य);
पूर्ण

/*
 * Register here to be notअगरied about runसमय enabling/disabling of
 * the चयनer.
 *
 * The notअगरier chain is called with the चयनer activation lock held:
 * the चयनer will not be enabled or disabled during callbacks.
 * Callbacks must not call bL_चयनer_अणुget,putपूर्ण_enabled().
 */
#घोषणा BL_NOTIFY_PRE_ENABLE	0
#घोषणा BL_NOTIFY_POST_ENABLE	1
#घोषणा BL_NOTIFY_PRE_DISABLE	2
#घोषणा BL_NOTIFY_POST_DISABLE	3

#अगर_घोषित CONFIG_BL_SWITCHER

पूर्णांक bL_चयनer_रेजिस्टर_notअगरier(काष्ठा notअगरier_block *nb);
पूर्णांक bL_चयनer_unरेजिस्टर_notअगरier(काष्ठा notअगरier_block *nb);

/*
 * Use these functions to temporarily prevent enabling/disabling of
 * the चयनer.
 * bL_चयनer_get_enabled() वापसs true अगर the चयनer is currently
 * enabled.  Each call to bL_चयनer_get_enabled() must be followed
 * by a call to bL_चयनer_put_enabled().  These functions are not
 * recursive.
 */
bool bL_चयनer_get_enabled(व्योम);
व्योम bL_चयनer_put_enabled(व्योम);

पूर्णांक bL_चयनer_trace_trigger(व्योम);
पूर्णांक bL_चयनer_get_logical_index(u32 mpidr);

#अन्यथा
अटल अंतरभूत पूर्णांक bL_चयनer_रेजिस्टर_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक bL_चयनer_unरेजिस्टर_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत bool bL_चयनer_get_enabled(व्योम) अणु वापस false; पूर्ण
अटल अंतरभूत व्योम bL_चयनer_put_enabled(व्योम) अणु पूर्ण
अटल अंतरभूत पूर्णांक bL_चयनer_trace_trigger(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक bL_चयनer_get_logical_index(u32 mpidr) अणु वापस -EUNATCH; पूर्ण
#पूर्ण_अगर /* CONFIG_BL_SWITCHER */

#पूर्ण_अगर
