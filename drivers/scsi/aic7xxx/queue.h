<शैली गुरु>
/*
 * Copyright (c) 1991, 1993
 *	The Regents of the University of Calअगरornia.  All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    करोcumentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)queue.h	8.5 (Berkeley) 8/20/94
 * $FreeBSD: src/sys/sys/queue.h,v 1.38 2000/05/26 02:06:56 jake Exp $
 */

#अगर_अघोषित _SYS_QUEUE_H_
#घोषणा	_SYS_QUEUE_H_

/*
 * This file defines five types of data काष्ठाures: singly-linked lists,
 * singly-linked tail queues, lists, tail queues, and circular queues.
 *
 * A singly-linked list is headed by a single क्रमward poपूर्णांकer. The elements
 * are singly linked क्रम minimum space and poपूर्णांकer manipulation overhead at
 * the expense of O(n) removal क्रम arbitrary elements. New elements can be
 * added to the list after an existing element or at the head of the list.
 * Elements being हटाओd from the head of the list should use the explicit
 * macro क्रम this purpose क्रम optimum efficiency. A singly-linked list may
 * only be traversed in the क्रमward direction.  Singly-linked lists are ideal
 * क्रम applications with large datasets and few or no removals or क्रम
 * implementing a LIFO queue.
 *
 * A singly-linked tail queue is headed by a pair of poपूर्णांकers, one to the
 * head of the list and the other to the tail of the list. The elements are
 * singly linked क्रम minimum space and poपूर्णांकer manipulation overhead at the
 * expense of O(n) removal क्रम arbitrary elements. New elements can be added
 * to the list after an existing element, at the head of the list, or at the
 * end of the list. Elements being हटाओd from the head of the tail queue
 * should use the explicit macro क्रम this purpose क्रम optimum efficiency.
 * A singly-linked tail queue may only be traversed in the क्रमward direction.
 * Singly-linked tail queues are ideal क्रम applications with large datasets
 * and few or no removals or क्रम implementing a FIFO queue.
 *
 * A list is headed by a single क्रमward poपूर्णांकer (or an array of क्रमward
 * poपूर्णांकers क्रम a hash table header). The elements are करोubly linked
 * so that an arbitrary element can be हटाओd without a need to
 * traverse the list. New elements can be added to the list beक्रमe
 * or after an existing element or at the head of the list. A list
 * may only be traversed in the क्रमward direction.
 *
 * A tail queue is headed by a pair of poपूर्णांकers, one to the head of the
 * list and the other to the tail of the list. The elements are करोubly
 * linked so that an arbitrary element can be हटाओd without a need to
 * traverse the list. New elements can be added to the list beक्रमe or
 * after an existing element, at the head of the list, or at the end of
 * the list. A tail queue may be traversed in either direction.
 *
 * A circle queue is headed by a pair of poपूर्णांकers, one to the head of the
 * list and the other to the tail of the list. The elements are करोubly
 * linked so that an arbitrary element can be हटाओd without a need to
 * traverse the list. New elements can be added to the list beक्रमe or after
 * an existing element, at the head of the list, or at the end of the list.
 * A circle queue may be traversed in either direction, but has a more
 * complex end of list detection.
 *
 * For details on the use of these macros, see the queue(3) manual page.
 *
 *
 *			SLIST	LIST	STAILQ	TAILQ	CIRCLEQ
 * _HEAD		+	+	+	+	+
 * _HEAD_INITIALIZER	+	+	+	+	+
 * _ENTRY		+	+	+	+	+
 * _INIT		+	+	+	+	+
 * _EMPTY		+	+	+	+	+
 * _FIRST		+	+	+	+	+
 * _NEXT		+	+	+	+	+
 * _PREV		-	-	-	+	+
 * _LAST		-	-	+	+	+
 * _FOREACH		+	+	+	+	+
 * _FOREACH_REVERSE	-	-	-	+	+
 * _INSERT_HEAD		+	+	+	+	+
 * _INSERT_BEFORE	-	+	-	+	+
 * _INSERT_AFTER	+	+	+	+	+
 * _INSERT_TAIL		-	-	+	+	+
 * _REMOVE_HEAD		+	-	+	-	-
 * _REMOVE		+	+	+	+	+
 *
 */

/*
 * Singly-linked List declarations.
 */
#घोषणा	SLIST_HEAD(name, type)						\
काष्ठा name अणु								\
	काष्ठा type *slh_first;	/* first element */			\
पूर्ण

#घोषणा	SLIST_HEAD_INITIALIZER(head)					\
	अणु शून्य पूर्ण
 
#घोषणा	SLIST_ENTRY(type)						\
काष्ठा अणु								\
	काष्ठा type *sle_next;	/* next element */			\
पूर्ण
 
/*
 * Singly-linked List functions.
 */
#घोषणा	SLIST_EMPTY(head)	((head)->slh_first == शून्य)

#घोषणा	SLIST_FIRST(head)	((head)->slh_first)

#घोषणा	SLIST_FOREACH(var, head, field)					\
	क्रम ((var) = SLIST_FIRST((head));				\
	    (var);							\
	    (var) = SLIST_NEXT((var), field))

#घोषणा	SLIST_INIT(head) करो अणु						\
	SLIST_FIRST((head)) = शून्य;					\
पूर्ण जबतक (0)

#घोषणा	SLIST_INSERT_AFTER(slistelm, elm, field) करो अणु			\
	SLIST_NEXT((elm), field) = SLIST_NEXT((slistelm), field);	\
	SLIST_NEXT((slistelm), field) = (elm);				\
पूर्ण जबतक (0)

#घोषणा	SLIST_INSERT_HEAD(head, elm, field) करो अणु			\
	SLIST_NEXT((elm), field) = SLIST_FIRST((head));			\
	SLIST_FIRST((head)) = (elm);					\
पूर्ण जबतक (0)

#घोषणा	SLIST_NEXT(elm, field)	((elm)->field.sle_next)

#घोषणा	SLIST_REMOVE(head, elm, type, field) करो अणु			\
	अगर (SLIST_FIRST((head)) == (elm)) अणु				\
		SLIST_REMOVE_HEAD((head), field);			\
	पूर्ण								\
	अन्यथा अणु								\
		काष्ठा type *curelm = SLIST_FIRST((head));		\
		जबतक (SLIST_NEXT(curelm, field) != (elm))		\
			curelm = SLIST_NEXT(curelm, field);		\
		SLIST_NEXT(curelm, field) =				\
		    SLIST_NEXT(SLIST_NEXT(curelm, field), field);	\
	पूर्ण								\
पूर्ण जबतक (0)

#घोषणा	SLIST_REMOVE_HEAD(head, field) करो अणु				\
	SLIST_FIRST((head)) = SLIST_NEXT(SLIST_FIRST((head)), field);	\
पूर्ण जबतक (0)

/*
 * Singly-linked Tail queue declarations.
 */
#घोषणा	STAILQ_HEAD(name, type)						\
काष्ठा name अणु								\
	काष्ठा type *stqh_first;/* first element */			\
	काष्ठा type **stqh_last;/* addr of last next element */		\
पूर्ण

#घोषणा	STAILQ_HEAD_INITIALIZER(head)					\
	अणु शून्य, &(head).stqh_first पूर्ण

#घोषणा	STAILQ_ENTRY(type)						\
काष्ठा अणु								\
	काष्ठा type *stqe_next;	/* next element */			\
पूर्ण

/*
 * Singly-linked Tail queue functions.
 */
#घोषणा	STAILQ_EMPTY(head)	((head)->stqh_first == शून्य)

#घोषणा	STAILQ_FIRST(head)	((head)->stqh_first)

#घोषणा	STAILQ_FOREACH(var, head, field)				\
	क्रम((var) = STAILQ_FIRST((head));				\
	   (var);							\
	   (var) = STAILQ_NEXT((var), field))

#घोषणा	STAILQ_INIT(head) करो अणु						\
	STAILQ_FIRST((head)) = शून्य;					\
	(head)->stqh_last = &STAILQ_FIRST((head));			\
पूर्ण जबतक (0)

#घोषणा	STAILQ_INSERT_AFTER(head, tqelm, elm, field) करो अणु		\
	अगर ((STAILQ_NEXT((elm), field) = STAILQ_NEXT((tqelm), field)) == शून्य)\
		(head)->stqh_last = &STAILQ_NEXT((elm), field);		\
	STAILQ_NEXT((tqelm), field) = (elm);				\
पूर्ण जबतक (0)

#घोषणा	STAILQ_INSERT_HEAD(head, elm, field) करो अणु			\
	अगर ((STAILQ_NEXT((elm), field) = STAILQ_FIRST((head))) == शून्य)	\
		(head)->stqh_last = &STAILQ_NEXT((elm), field);		\
	STAILQ_FIRST((head)) = (elm);					\
पूर्ण जबतक (0)

#घोषणा	STAILQ_INSERT_TAIL(head, elm, field) करो अणु			\
	STAILQ_NEXT((elm), field) = शून्य;				\
	STAILQ_LAST((head)) = (elm);					\
	(head)->stqh_last = &STAILQ_NEXT((elm), field);			\
पूर्ण जबतक (0)

#घोषणा	STAILQ_LAST(head)	(*(head)->stqh_last)

#घोषणा	STAILQ_NEXT(elm, field)	((elm)->field.stqe_next)

#घोषणा	STAILQ_REMOVE(head, elm, type, field) करो अणु			\
	अगर (STAILQ_FIRST((head)) == (elm)) अणु				\
		STAILQ_REMOVE_HEAD(head, field);			\
	पूर्ण								\
	अन्यथा अणु								\
		काष्ठा type *curelm = STAILQ_FIRST((head));		\
		जबतक (STAILQ_NEXT(curelm, field) != (elm))		\
			curelm = STAILQ_NEXT(curelm, field);		\
		अगर ((STAILQ_NEXT(curelm, field) =			\
		     STAILQ_NEXT(STAILQ_NEXT(curelm, field), field)) == शून्य)\
			(head)->stqh_last = &STAILQ_NEXT((curelm), field);\
	पूर्ण								\
पूर्ण जबतक (0)

#घोषणा	STAILQ_REMOVE_HEAD(head, field) करो अणु				\
	अगर ((STAILQ_FIRST((head)) =					\
	     STAILQ_NEXT(STAILQ_FIRST((head)), field)) == शून्य)		\
		(head)->stqh_last = &STAILQ_FIRST((head));		\
पूर्ण जबतक (0)

#घोषणा	STAILQ_REMOVE_HEAD_UNTIL(head, elm, field) करो अणु			\
	अगर ((STAILQ_FIRST((head)) = STAILQ_NEXT((elm), field)) == शून्य)	\
		(head)->stqh_last = &STAILQ_FIRST((head));		\
पूर्ण जबतक (0)

/*
 * List declarations.
 */
#घोषणा	BSD_LIST_HEAD(name, type)					\
काष्ठा name अणु								\
	काष्ठा type *lh_first;	/* first element */			\
पूर्ण

#घोषणा	LIST_HEAD_INITIALIZER(head)					\
	अणु शून्य पूर्ण

#घोषणा	LIST_ENTRY(type)						\
काष्ठा अणु								\
	काष्ठा type *le_next;	/* next element */			\
	काष्ठा type **le_prev;	/* address of previous next element */	\
पूर्ण

/*
 * List functions.
 */

#घोषणा	LIST_EMPTY(head)	((head)->lh_first == शून्य)

#घोषणा	LIST_FIRST(head)	((head)->lh_first)

#घोषणा	LIST_FOREACH(var, head, field)					\
	क्रम ((var) = LIST_FIRST((head));				\
	    (var);							\
	    (var) = LIST_NEXT((var), field))

#घोषणा	LIST_INIT(head) करो अणु						\
	LIST_FIRST((head)) = शून्य;					\
पूर्ण जबतक (0)

#घोषणा	LIST_INSERT_AFTER(listelm, elm, field) करो अणु			\
	अगर ((LIST_NEXT((elm), field) = LIST_NEXT((listelm), field)) != शून्य)\
		LIST_NEXT((listelm), field)->field.le_prev =		\
		    &LIST_NEXT((elm), field);				\
	LIST_NEXT((listelm), field) = (elm);				\
	(elm)->field.le_prev = &LIST_NEXT((listelm), field);		\
पूर्ण जबतक (0)

#घोषणा	LIST_INSERT_BEFORE(listelm, elm, field) करो अणु			\
	(elm)->field.le_prev = (listelm)->field.le_prev;		\
	LIST_NEXT((elm), field) = (listelm);				\
	*(listelm)->field.le_prev = (elm);				\
	(listelm)->field.le_prev = &LIST_NEXT((elm), field);		\
पूर्ण जबतक (0)

#घोषणा	LIST_INSERT_HEAD(head, elm, field) करो अणु				\
	अगर ((LIST_NEXT((elm), field) = LIST_FIRST((head))) != शून्य)	\
		LIST_FIRST((head))->field.le_prev = &LIST_NEXT((elm), field);\
	LIST_FIRST((head)) = (elm);					\
	(elm)->field.le_prev = &LIST_FIRST((head));			\
पूर्ण जबतक (0)

#घोषणा	LIST_NEXT(elm, field)	((elm)->field.le_next)

#घोषणा	LIST_REMOVE(elm, field) करो अणु					\
	अगर (LIST_NEXT((elm), field) != शून्य)				\
		LIST_NEXT((elm), field)->field.le_prev = 		\
		    (elm)->field.le_prev;				\
	*(elm)->field.le_prev = LIST_NEXT((elm), field);		\
पूर्ण जबतक (0)

/*
 * Tail queue declarations.
 */
#घोषणा	TAILQ_HEAD(name, type)						\
काष्ठा name अणु								\
	काष्ठा type *tqh_first;	/* first element */			\
	काष्ठा type **tqh_last;	/* addr of last next element */		\
पूर्ण

#घोषणा	TAILQ_HEAD_INITIALIZER(head)					\
	अणु शून्य, &(head).tqh_first पूर्ण

#घोषणा	TAILQ_ENTRY(type)						\
काष्ठा अणु								\
	काष्ठा type *tqe_next;	/* next element */			\
	काष्ठा type **tqe_prev;	/* address of previous next element */	\
पूर्ण

/*
 * Tail queue functions.
 */
#घोषणा	TAILQ_EMPTY(head)	((head)->tqh_first == शून्य)

#घोषणा	TAILQ_FIRST(head)	((head)->tqh_first)

#घोषणा	TAILQ_FOREACH(var, head, field)					\
	क्रम ((var) = TAILQ_FIRST((head));				\
	    (var);							\
	    (var) = TAILQ_NEXT((var), field))

#घोषणा	TAILQ_FOREACH_REVERSE(var, head, headname, field)		\
	क्रम ((var) = TAILQ_LAST((head), headname);			\
	    (var);							\
	    (var) = TAILQ_PREV((var), headname, field))

#घोषणा	TAILQ_INIT(head) करो अणु						\
	TAILQ_FIRST((head)) = शून्य;					\
	(head)->tqh_last = &TAILQ_FIRST((head));			\
पूर्ण जबतक (0)

#घोषणा	TAILQ_INSERT_AFTER(head, listelm, elm, field) करो अणु		\
	अगर ((TAILQ_NEXT((elm), field) = TAILQ_NEXT((listelm), field)) != शून्य)\
		TAILQ_NEXT((elm), field)->field.tqe_prev = 		\
		    &TAILQ_NEXT((elm), field);				\
	अन्यथा								\
		(head)->tqh_last = &TAILQ_NEXT((elm), field);		\
	TAILQ_NEXT((listelm), field) = (elm);				\
	(elm)->field.tqe_prev = &TAILQ_NEXT((listelm), field);		\
पूर्ण जबतक (0)

#घोषणा	TAILQ_INSERT_BEFORE(listelm, elm, field) करो अणु			\
	(elm)->field.tqe_prev = (listelm)->field.tqe_prev;		\
	TAILQ_NEXT((elm), field) = (listelm);				\
	*(listelm)->field.tqe_prev = (elm);				\
	(listelm)->field.tqe_prev = &TAILQ_NEXT((elm), field);		\
पूर्ण जबतक (0)

#घोषणा	TAILQ_INSERT_HEAD(head, elm, field) करो अणु			\
	अगर ((TAILQ_NEXT((elm), field) = TAILQ_FIRST((head))) != शून्य)	\
		TAILQ_FIRST((head))->field.tqe_prev =			\
		    &TAILQ_NEXT((elm), field);				\
	अन्यथा								\
		(head)->tqh_last = &TAILQ_NEXT((elm), field);		\
	TAILQ_FIRST((head)) = (elm);					\
	(elm)->field.tqe_prev = &TAILQ_FIRST((head));			\
पूर्ण जबतक (0)

#घोषणा	TAILQ_INSERT_TAIL(head, elm, field) करो अणु			\
	TAILQ_NEXT((elm), field) = शून्य;				\
	(elm)->field.tqe_prev = (head)->tqh_last;			\
	*(head)->tqh_last = (elm);					\
	(head)->tqh_last = &TAILQ_NEXT((elm), field);			\
पूर्ण जबतक (0)

#घोषणा	TAILQ_LAST(head, headname)					\
	(*(((काष्ठा headname *)((head)->tqh_last))->tqh_last))

#घोषणा	TAILQ_NEXT(elm, field) ((elm)->field.tqe_next)

#घोषणा	TAILQ_PREV(elm, headname, field)				\
	(*(((काष्ठा headname *)((elm)->field.tqe_prev))->tqh_last))

#घोषणा	TAILQ_REMOVE(head, elm, field) करो अणु				\
	अगर ((TAILQ_NEXT((elm), field)) != शून्य)				\
		TAILQ_NEXT((elm), field)->field.tqe_prev = 		\
		    (elm)->field.tqe_prev;				\
	अन्यथा								\
		(head)->tqh_last = (elm)->field.tqe_prev;		\
	*(elm)->field.tqe_prev = TAILQ_NEXT((elm), field);		\
पूर्ण जबतक (0)

/*
 * Circular queue declarations.
 */
#घोषणा	CIRCLEQ_HEAD(name, type)					\
काष्ठा name अणु								\
	काष्ठा type *cqh_first;		/* first element */		\
	काष्ठा type *cqh_last;		/* last element */		\
पूर्ण

#घोषणा	CIRCLEQ_HEAD_INITIALIZER(head)					\
	अणु (व्योम *)&(head), (व्योम *)&(head) पूर्ण

#घोषणा	CIRCLEQ_ENTRY(type)						\
काष्ठा अणु								\
	काष्ठा type *cqe_next;		/* next element */		\
	काष्ठा type *cqe_prev;		/* previous element */		\
पूर्ण

/*
 * Circular queue functions.
 */
#घोषणा	CIRCLEQ_EMPTY(head)	((head)->cqh_first == (व्योम *)(head))

#घोषणा	CIRCLEQ_FIRST(head)	((head)->cqh_first)

#घोषणा	CIRCLEQ_FOREACH(var, head, field)				\
	क्रम ((var) = CIRCLEQ_FIRST((head));				\
	    (var) != (व्योम *)(head);					\
	    (var) = CIRCLEQ_NEXT((var), field))

#घोषणा	CIRCLEQ_FOREACH_REVERSE(var, head, field)			\
	क्रम ((var) = CIRCLEQ_LAST((head));				\
	    (var) != (व्योम *)(head);					\
	    (var) = CIRCLEQ_PREV((var), field))

#घोषणा	CIRCLEQ_INIT(head) करो अणु						\
	CIRCLEQ_FIRST((head)) = (व्योम *)(head);				\
	CIRCLEQ_LAST((head)) = (व्योम *)(head);				\
पूर्ण जबतक (0)

#घोषणा	CIRCLEQ_INSERT_AFTER(head, listelm, elm, field) करो अणु		\
	CIRCLEQ_NEXT((elm), field) = CIRCLEQ_NEXT((listelm), field);	\
	CIRCLEQ_PREV((elm), field) = (listelm);				\
	अगर (CIRCLEQ_NEXT((listelm), field) == (व्योम *)(head))		\
		CIRCLEQ_LAST((head)) = (elm);				\
	अन्यथा								\
		CIRCLEQ_PREV(CIRCLEQ_NEXT((listelm), field), field) = (elm);\
	CIRCLEQ_NEXT((listelm), field) = (elm);				\
पूर्ण जबतक (0)

#घोषणा	CIRCLEQ_INSERT_BEFORE(head, listelm, elm, field) करो अणु		\
	CIRCLEQ_NEXT((elm), field) = (listelm);				\
	CIRCLEQ_PREV((elm), field) = CIRCLEQ_PREV((listelm), field);	\
	अगर (CIRCLEQ_PREV((listelm), field) == (व्योम *)(head))		\
		CIRCLEQ_FIRST((head)) = (elm);				\
	अन्यथा								\
		CIRCLEQ_NEXT(CIRCLEQ_PREV((listelm), field), field) = (elm);\
	CIRCLEQ_PREV((listelm), field) = (elm);				\
पूर्ण जबतक (0)

#घोषणा	CIRCLEQ_INSERT_HEAD(head, elm, field) करो अणु			\
	CIRCLEQ_NEXT((elm), field) = CIRCLEQ_FIRST((head));		\
	CIRCLEQ_PREV((elm), field) = (व्योम *)(head);			\
	अगर (CIRCLEQ_LAST((head)) == (व्योम *)(head))			\
		CIRCLEQ_LAST((head)) = (elm);				\
	अन्यथा								\
		CIRCLEQ_PREV(CIRCLEQ_FIRST((head)), field) = (elm);	\
	CIRCLEQ_FIRST((head)) = (elm);					\
पूर्ण जबतक (0)

#घोषणा	CIRCLEQ_INSERT_TAIL(head, elm, field) करो अणु			\
	CIRCLEQ_NEXT((elm), field) = (व्योम *)(head);			\
	CIRCLEQ_PREV((elm), field) = CIRCLEQ_LAST((head));		\
	अगर (CIRCLEQ_FIRST((head)) == (व्योम *)(head))			\
		CIRCLEQ_FIRST((head)) = (elm);				\
	अन्यथा								\
		CIRCLEQ_NEXT(CIRCLEQ_LAST((head)), field) = (elm);	\
	CIRCLEQ_LAST((head)) = (elm);					\
पूर्ण जबतक (0)

#घोषणा	CIRCLEQ_LAST(head)	((head)->cqh_last)

#घोषणा	CIRCLEQ_NEXT(elm,field)	((elm)->field.cqe_next)

#घोषणा	CIRCLEQ_PREV(elm,field)	((elm)->field.cqe_prev)

#घोषणा	CIRCLEQ_REMOVE(head, elm, field) करो अणु				\
	अगर (CIRCLEQ_NEXT((elm), field) == (व्योम *)(head))		\
		CIRCLEQ_LAST((head)) = CIRCLEQ_PREV((elm), field);	\
	अन्यथा								\
		CIRCLEQ_PREV(CIRCLEQ_NEXT((elm), field), field) =	\
		    CIRCLEQ_PREV((elm), field);				\
	अगर (CIRCLEQ_PREV((elm), field) == (व्योम *)(head))		\
		CIRCLEQ_FIRST((head)) = CIRCLEQ_NEXT((elm), field);	\
	अन्यथा								\
		CIRCLEQ_NEXT(CIRCLEQ_PREV((elm), field), field) =	\
		    CIRCLEQ_NEXT((elm), field);				\
पूर्ण जबतक (0)

#पूर्ण_अगर /* !_SYS_QUEUE_H_ */
