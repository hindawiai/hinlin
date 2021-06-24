<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __WATCHDOG_PRETIMEOUT_H
#घोषणा __WATCHDOG_PRETIMEOUT_H

#घोषणा WATCHDOG_GOV_NAME_MAXLEN	20

काष्ठा watchकरोg_device;

काष्ठा watchकरोg_governor अणु
	स्थिर अक्षर	name[WATCHDOG_GOV_NAME_MAXLEN];
	व्योम		(*preसमयout)(काष्ठा watchकरोg_device *wdd);
पूर्ण;

#अगर IS_ENABLED(CONFIG_WATCHDOG_PRETIMEOUT_GOV)
/* Interfaces to watchकरोg preसमयout governors */
पूर्णांक watchकरोg_रेजिस्टर_governor(काष्ठा watchकरोg_governor *gov);
व्योम watchकरोg_unरेजिस्टर_governor(काष्ठा watchकरोg_governor *gov);

/* Interfaces to watchकरोg_dev.c */
पूर्णांक watchकरोg_रेजिस्टर_preसमयout(काष्ठा watchकरोg_device *wdd);
व्योम watchकरोg_unरेजिस्टर_preसमयout(काष्ठा watchकरोg_device *wdd);
पूर्णांक watchकरोg_preसमयout_available_governors_get(अक्षर *buf);
पूर्णांक watchकरोg_preसमयout_governor_get(काष्ठा watchकरोg_device *wdd, अक्षर *buf);
पूर्णांक watchकरोg_preसमयout_governor_set(काष्ठा watchकरोg_device *wdd,
				     स्थिर अक्षर *buf);

#अगर IS_ENABLED(CONFIG_WATCHDOG_PRETIMEOUT_DEFAULT_GOV_NOOP)
#घोषणा WATCHDOG_PRETIMEOUT_DEFAULT_GOV		"noop"
#या_अगर IS_ENABLED(CONFIG_WATCHDOG_PRETIMEOUT_DEFAULT_GOV_PANIC)
#घोषणा WATCHDOG_PRETIMEOUT_DEFAULT_GOV		"panic"
#पूर्ण_अगर

#अन्यथा
अटल अंतरभूत पूर्णांक watchकरोg_रेजिस्टर_preसमयout(काष्ठा watchकरोg_device *wdd)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम watchकरोg_unरेजिस्टर_preसमयout(काष्ठा watchकरोg_device *wdd)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक watchकरोg_preसमयout_available_governors_get(अक्षर *buf)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक watchकरोg_preसमयout_governor_get(काष्ठा watchकरोg_device *wdd,
						   अक्षर *buf)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक watchकरोg_preसमयout_governor_set(काष्ठा watchकरोg_device *wdd,
						   स्थिर अक्षर *buf)
अणु
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
