<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*****************************************************************************

    AudioScience HPI driver
    Copyright (C) 1997-2011  AudioScience Inc. <support@audioscience.com>


Debug macros.

*****************************************************************************/

#अगर_अघोषित _HPIDEBUG_H
#घोषणा _HPIDEBUG_H

#समावेश "hpi_internal.h"

/* Define debugging levels.  */
क्रमागत अणु HPI_DEBUG_LEVEL_ERROR = 0,	/* always log errors */
	HPI_DEBUG_LEVEL_WARNING = 1,
	HPI_DEBUG_LEVEL_NOTICE = 2,
	HPI_DEBUG_LEVEL_INFO = 3,
	HPI_DEBUG_LEVEL_DEBUG = 4,
	HPI_DEBUG_LEVEL_VERBOSE = 5	/* same prपूर्णांकk level as DEBUG */
पूर्ण;

#घोषणा HPI_DEBUG_LEVEL_DEFAULT HPI_DEBUG_LEVEL_NOTICE

/* an OS can define an extra flag string that is appended to
   the start of each message, eg see linux kernel hpios.h */

#अगर_घोषित SOURCEखाता_NAME
#घोषणा खाता_LINE  SOURCEखाता_NAME ":" __stringअगरy(__LINE__) " "
#अन्यथा
#घोषणा खाता_LINE  __खाता__ ":" __stringअगरy(__LINE__) " "
#पूर्ण_अगर

#घोषणा HPI_DEBUG_ASSERT(expression) \
	करो अणु \
		अगर (!(expression)) अणु \
			prपूर्णांकk(KERN_ERR  खाता_LINE \
				"ASSERT " __stringअगरy(expression)); \
		पूर्ण \
	पूर्ण जबतक (0)

#घोषणा HPI_DEBUG_LOG(level, ...) \
	करो अणु \
		अगर (hpi_debug_level >= HPI_DEBUG_LEVEL_##level) अणु \
			prपूर्णांकk(HPI_DEBUG_FLAG_##level \
			खाता_LINE  __VA_ARGS__); \
		पूर्ण \
	पूर्ण जबतक (0)

व्योम hpi_debug_init(व्योम);
पूर्णांक hpi_debug_level_set(पूर्णांक level);
पूर्णांक hpi_debug_level_get(व्योम);
/* needed by Linux driver क्रम dynamic debug level changes */
बाह्य पूर्णांक hpi_debug_level;

व्योम hpi_debug_message(काष्ठा hpi_message *phm, अक्षर *sz_fileline);

व्योम hpi_debug_data(u16 *pdata, u32 len);

#घोषणा HPI_DEBUG_DATA(pdata, len) \
	करो अणु \
		अगर (hpi_debug_level >= HPI_DEBUG_LEVEL_VERBOSE) \
			hpi_debug_data(pdata, len); \
	पूर्ण जबतक (0)

#घोषणा HPI_DEBUG_MESSAGE(level, phm) \
	करो अणु \
		अगर (hpi_debug_level >= HPI_DEBUG_LEVEL_##level) अणु \
			hpi_debug_message(phm, HPI_DEBUG_FLAG_##level \
				खाता_LINE __stringअगरy(level)); \
		पूर्ण \
	पूर्ण जबतक (0)

#घोषणा HPI_DEBUG_RESPONSE(phr) \
	करो अणु \
		अगर (((hpi_debug_level >= HPI_DEBUG_LEVEL_DEBUG) && \
			(phr->error)) ||\
		(hpi_debug_level >= HPI_DEBUG_LEVEL_VERBOSE)) \
			prपूर्णांकk(KERN_DEBUG "HPI_RES%d,%d,%d\n", \
				phr->version, phr->error, phr->specअगरic_error); \
	पूर्ण जबतक (0)

#अगर_अघोषित compile_समय_निश्चित
#घोषणा compile_समय_निश्चित(cond, msg) \
    प्रकार अक्षर msg[(cond) ? 1 : -1]
#पूर्ण_अगर

#पूर्ण_अगर				/* _HPIDEBUG_H_  */
