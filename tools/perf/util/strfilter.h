<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __PERF_STRFILTER_H
#घोषणा __PERF_STRFILTER_H
/* General purpose glob matching filter */

#समावेश <linux/list.h>
#समावेश <stdbool.h>

/* A node of string filter */
काष्ठा strfilter_node अणु
	काष्ठा strfilter_node *l;	/* Tree left branch (क्रम &,|) */
	काष्ठा strfilter_node *r;	/* Tree right branch (क्रम !,&,|) */
	स्थिर अक्षर *p;		/* Operator or rule */
पूर्ण;

/* String filter */
काष्ठा strfilter अणु
	काष्ठा strfilter_node *root;
पूर्ण;

/**
 * strfilter__new - Create a new string filter
 * @rules: Filter rule, which is a combination of glob expressions.
 * @err: Poपूर्णांकer which poपूर्णांकs an error detected on @rules
 *
 * Parse @rules and वापस new strfilter. Return शून्य अगर an error detected.
 * In that हाल, *@err will indicate where it is detected, and *@err is शून्य
 * अगर a memory allocation is failed.
 */
काष्ठा strfilter *strfilter__new(स्थिर अक्षर *rules, स्थिर अक्षर **err);

/**
 * strfilter__or - Append an additional rule by logical-or
 * @filter: Original string filter
 * @rules: Filter rule to be appended at left of the root of
 *         @filter by using logical-or.
 * @err: Poपूर्णांकer which poपूर्णांकs an error detected on @rules
 *
 * Parse @rules and join it to the @filter by using logical-or.
 * Return 0 अगर success, or वापस the error code.
 */
पूर्णांक strfilter__or(काष्ठा strfilter *filter,
		  स्थिर अक्षर *rules, स्थिर अक्षर **err);

/**
 * strfilter__add - Append an additional rule by logical-and
 * @filter: Original string filter
 * @rules: Filter rule to be appended at left of the root of
 *         @filter by using logical-and.
 * @err: Poपूर्णांकer which poपूर्णांकs an error detected on @rules
 *
 * Parse @rules and join it to the @filter by using logical-and.
 * Return 0 अगर success, or वापस the error code.
 */
पूर्णांक strfilter__and(काष्ठा strfilter *filter,
		   स्थिर अक्षर *rules, स्थिर अक्षर **err);

/**
 * strfilter__compare - compare given string and a string filter
 * @filter: String filter
 * @str: target string
 *
 * Compare @str and @filter. Return true अगर the str match the rule
 */
bool strfilter__compare(काष्ठा strfilter *filter, स्थिर अक्षर *str);

/**
 * strfilter__delete - delete a string filter
 * @filter: String filter to delete
 *
 * Delete @filter.
 */
व्योम strfilter__delete(काष्ठा strfilter *filter);

/**
 * strfilter__string - Reस्थिरruct a rule string from filter
 * @filter: String filter to reस्थिरruct
 *
 * Reस्थिरruct a rule string from @filter. This will be good क्रम
 * debug messages. Note that वापसing string must be मुक्तd afterward.
 */
अक्षर *strfilter__string(काष्ठा strfilter *filter);

#पूर्ण_अगर
