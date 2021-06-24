<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  Profiling infraकाष्ठाure declarations.
 *
 *  This file is based on gcc-पूर्णांकernal definitions. Data काष्ठाures are
 *  defined to be compatible with gcc counterparts. For a better
 *  understanding, refer to gcc source: gcc/gcov-पन.स.
 *
 *    Copyright IBM Corp. 2009
 *    Author(s): Peter Oberparleiter <oberpar@linux.vnet.ibm.com>
 *
 *    Uses gcc-पूर्णांकernal data definitions.
 */

#अगर_अघोषित GCOV_H
#घोषणा GCOV_H GCOV_H

#समावेश <linux/module.h>
#समावेश <linux/types.h>

/*
 * Profiling data types used क्रम gcc 3.4 and above - these are defined by
 * gcc and need to be kept as बंद to the original definition as possible to
 * reमुख्य compatible.
 */
#घोषणा GCOV_DATA_MAGIC		((अचिन्हित पूर्णांक) 0x67636461)
#घोषणा GCOV_TAG_FUNCTION	((अचिन्हित पूर्णांक) 0x01000000)
#घोषणा GCOV_TAG_COUNTER_BASE	((अचिन्हित पूर्णांक) 0x01a10000)
#घोषणा GCOV_TAG_FOR_COUNTER(count)					\
	(GCOV_TAG_COUNTER_BASE + ((अचिन्हित पूर्णांक) (count) << 17))

#अगर BITS_PER_LONG >= 64
प्रकार दीर्घ gcov_type;
#अन्यथा
प्रकार दीर्घ दीर्घ gcov_type;
#पूर्ण_अगर

/* Opaque gcov_info. The gcov काष्ठाures can change as क्रम example in gcc 4.7 so
 * we cannot use full definition here and they need to be placed in gcc specअगरic
 * implementation of gcov. This also means no direct access to the members in
 * generic code and usage of the पूर्णांकerface below.*/
काष्ठा gcov_info;

/* Interface to access gcov_info data  */
स्थिर अक्षर *gcov_info_filename(काष्ठा gcov_info *info);
अचिन्हित पूर्णांक gcov_info_version(काष्ठा gcov_info *info);
काष्ठा gcov_info *gcov_info_next(काष्ठा gcov_info *info);
व्योम gcov_info_link(काष्ठा gcov_info *info);
व्योम gcov_info_unlink(काष्ठा gcov_info *prev, काष्ठा gcov_info *info);
bool gcov_info_within_module(काष्ठा gcov_info *info, काष्ठा module *mod);
माप_प्रकार convert_to_gcda(अक्षर *buffer, काष्ठा gcov_info *info);

/* Base पूर्णांकerface. */
क्रमागत gcov_action अणु
	GCOV_ADD,
	GCOV_REMOVE,
पूर्ण;

व्योम gcov_event(क्रमागत gcov_action action, काष्ठा gcov_info *info);
व्योम gcov_enable_events(व्योम);

/* writing helpers */
माप_प्रकार store_gcov_u32(व्योम *buffer, माप_प्रकार off, u32 v);
माप_प्रकार store_gcov_u64(व्योम *buffer, माप_प्रकार off, u64 v);

/* gcov_info control. */
व्योम gcov_info_reset(काष्ठा gcov_info *info);
पूर्णांक gcov_info_is_compatible(काष्ठा gcov_info *info1, काष्ठा gcov_info *info2);
व्योम gcov_info_add(काष्ठा gcov_info *dest, काष्ठा gcov_info *source);
काष्ठा gcov_info *gcov_info_dup(काष्ठा gcov_info *info);
व्योम gcov_info_मुक्त(काष्ठा gcov_info *info);

काष्ठा gcov_link अणु
	क्रमागत अणु
		OBJ_TREE,
		SRC_TREE,
	पूर्ण dir;
	स्थिर अक्षर *ext;
पूर्ण;
बाह्य स्थिर काष्ठा gcov_link gcov_link[];

बाह्य पूर्णांक gcov_events_enabled;
बाह्य काष्ठा mutex gcov_lock;

#पूर्ण_अगर /* GCOV_H */
