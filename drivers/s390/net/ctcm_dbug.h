<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *	Copyright IBM Corp. 2001, 2007
 *	Authors:	Peter Tiedemann (ptiedem@de.ibm.com)
 *
 */

#अगर_अघोषित _CTCM_DBUG_H_
#घोषणा _CTCM_DBUG_H_

/*
 * Debug Facility stuff
 */

#समावेश <यंत्र/debug.h>

#अगर_घोषित DEBUG
 #घोषणा करो_debug 1
#अन्यथा
 #घोषणा करो_debug 0
#पूर्ण_अगर
#अगर_घोषित DEBUGCCW
 #घोषणा करो_debug_ccw 1
 #घोषणा DEBUGDATA 1
#अन्यथा
 #घोषणा करो_debug_ccw 0
#पूर्ण_अगर
#अगर_घोषित DEBUGDATA
 #घोषणा करो_debug_data 1
#अन्यथा
 #घोषणा करो_debug_data 0
#पूर्ण_अगर

/* define dbf debug levels similar to kernel msg levels */
#घोषणा	CTC_DBF_ALWAYS	0	/* always prपूर्णांक this 			*/
#घोषणा	CTC_DBF_EMERG	0	/* प्रणाली is unusable			*/
#घोषणा	CTC_DBF_ALERT	1	/* action must be taken immediately	*/
#घोषणा	CTC_DBF_CRIT	2	/* critical conditions			*/
#घोषणा	CTC_DBF_ERROR	3	/* error conditions			*/
#घोषणा	CTC_DBF_WARN	4	/* warning conditions			*/
#घोषणा	CTC_DBF_NOTICE	5	/* normal but signअगरicant condition	*/
#घोषणा	CTC_DBF_INFO	5	/* inक्रमmational			*/
#घोषणा	CTC_DBF_DEBUG	6	/* debug-level messages			*/

क्रमागत ctcm_dbf_names अणु
	CTCM_DBF_SETUP,
	CTCM_DBF_ERROR,
	CTCM_DBF_TRACE,
	CTCM_DBF_MPC_SETUP,
	CTCM_DBF_MPC_ERROR,
	CTCM_DBF_MPC_TRACE,
	CTCM_DBF_INFOS	/* must be last element */
पूर्ण;

काष्ठा ctcm_dbf_info अणु
	अक्षर name[DEBUG_MAX_NAME_LEN];
	पूर्णांक pages;
	पूर्णांक areas;
	पूर्णांक len;
	पूर्णांक level;
	debug_info_t *id;
पूर्ण;

बाह्य काष्ठा ctcm_dbf_info ctcm_dbf[CTCM_DBF_INFOS];

पूर्णांक ctcm_रेजिस्टर_dbf_views(व्योम);
व्योम ctcm_unरेजिस्टर_dbf_views(व्योम);
व्योम ctcm_dbf_दीर्घtext(क्रमागत ctcm_dbf_names dbf_nix, पूर्णांक level, अक्षर *text, ...);

अटल अंतरभूत स्थिर अक्षर *strtail(स्थिर अक्षर *s, पूर्णांक n)
अणु
	पूर्णांक l = म_माप(s);
	वापस (l > n) ? s + (l - n) : s;
पूर्ण

#घोषणा CTCM_FUNTAIL strtail((अक्षर *)__func__, 16)

#घोषणा CTCM_DBF_TEXT(name, level, text) \
	करो अणु \
		debug_text_event(ctcm_dbf[CTCM_DBF_##name].id, level, text); \
	पूर्ण जबतक (0)

#घोषणा CTCM_DBF_HEX(name, level, addr, len) \
	करो अणु \
		debug_event(ctcm_dbf[CTCM_DBF_##name].id, \
					level, (व्योम *)(addr), len); \
	पूर्ण जबतक (0)

#घोषणा CTCM_DBF_TEXT_(name, level, text...) \
	ctcm_dbf_दीर्घtext(CTCM_DBF_##name, level, text)

/*
 * cat : one of अणुsetup, mpc_setup, trace, mpc_trace, error, mpc_errorपूर्ण.
 * dev : netdevice with valid name field.
 * text: any text string.
 */
#घोषणा CTCM_DBF_DEV_NAME(cat, dev, text) \
	करो अणु \
		CTCM_DBF_TEXT_(cat, CTC_DBF_INFO, "%s(%s) :- %s", \
			CTCM_FUNTAIL, dev->name, text); \
	पूर्ण जबतक (0)

#घोषणा MPC_DBF_DEV_NAME(cat, dev, text) \
	करो अणु \
		CTCM_DBF_TEXT_(MPC_##cat, CTC_DBF_INFO, "%s(%s) := %s", \
			CTCM_FUNTAIL, dev->name, text); \
	पूर्ण जबतक (0)

#घोषणा CTCMY_DBF_DEV_NAME(cat, dev, text) \
	करो अणु \
		अगर (IS_MPCDEV(dev)) \
			MPC_DBF_DEV_NAME(cat, dev, text); \
		अन्यथा \
			CTCM_DBF_DEV_NAME(cat, dev, text); \
	पूर्ण जबतक (0)

/*
 * cat : one of अणुsetup, mpc_setup, trace, mpc_trace, error, mpc_errorपूर्ण.
 * dev : netdevice.
 * text: any text string.
 */
#घोषणा CTCM_DBF_DEV(cat, dev, text) \
	करो अणु \
		CTCM_DBF_TEXT_(cat, CTC_DBF_INFO, "%s(%p) :-: %s", \
			CTCM_FUNTAIL, dev, text); \
	पूर्ण जबतक (0)

#घोषणा MPC_DBF_DEV(cat, dev, text) \
	करो अणु \
		CTCM_DBF_TEXT_(MPC_##cat, CTC_DBF_INFO, "%s(%p) :=: %s", \
			CTCM_FUNTAIL, dev, text); \
	पूर्ण जबतक (0)

#घोषणा CTCMY_DBF_DEV(cat, dev, text) \
	करो अणु \
		अगर (IS_MPCDEV(dev)) \
			MPC_DBF_DEV(cat, dev, text); \
		अन्यथा \
			CTCM_DBF_DEV(cat, dev, text); \
	पूर्ण जबतक (0)

#पूर्ण_अगर
