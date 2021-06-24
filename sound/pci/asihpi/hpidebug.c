<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/************************************************************************

    AudioScience HPI driver
    Copyright (C) 1997-2011  AudioScience Inc. <support@audioscience.com>


Debug macro translation.

************************************************************************/

#समावेश "hpi_internal.h"
#समावेश "hpidebug.h"

/* Debug level; 0 quiet; 1 inक्रमmative, 2 debug, 3 verbose debug.  */
पूर्णांक hpi_debug_level = HPI_DEBUG_LEVEL_DEFAULT;

व्योम hpi_debug_init(व्योम)
अणु
	prपूर्णांकk(KERN_INFO "debug start\n");
पूर्ण

पूर्णांक hpi_debug_level_set(पूर्णांक level)
अणु
	पूर्णांक old_level;

	old_level = hpi_debug_level;
	hpi_debug_level = level;
	वापस old_level;
पूर्ण

पूर्णांक hpi_debug_level_get(व्योम)
अणु
	वापस hpi_debug_level;
पूर्ण

व्योम hpi_debug_message(काष्ठा hpi_message *phm, अक्षर *sz_fileline)
अणु
	अगर (phm) अणु
		prपूर्णांकk(KERN_DEBUG "HPI_MSG%d,%d,%d,%d,%d\n", phm->version,
			phm->adapter_index, phm->obj_index, phm->function,
			phm->u.c.attribute);
	पूर्ण

पूर्ण

व्योम hpi_debug_data(u16 *pdata, u32 len)
अणु
	u32 i;
	पूर्णांक j;
	पूर्णांक k;
	पूर्णांक lines;
	पूर्णांक cols = 8;

	lines = DIV_ROUND_UP(len, cols);
	अगर (lines > 8)
		lines = 8;

	क्रम (i = 0, j = 0; j < lines; j++) अणु
		prपूर्णांकk(KERN_DEBUG "%p:", (pdata + i));

		क्रम (k = 0; k < cols && i < len; i++, k++)
			prपूर्णांकk(KERN_CONT "%s%04x", k == 0 ? "" : " ", pdata[i]);

		prपूर्णांकk(KERN_CONT "\n");
	पूर्ण
पूर्ण
