<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Device driver क्रम the SYMBIOS/LSILOGIC 53C8XX and 53C1010 family 
 * of PCI-SCSI IO processors.
 *
 * Copyright (C) 1999-2001  Gerard Roudier <groudier@मुक्त.fr>
 *
 * This driver is derived from the Linux sym53c8xx driver.
 * Copyright (C) 1998-2000  Gerard Roudier
 *
 * The sym53c8xx driver is derived from the ncr53c8xx driver that had been 
 * a port of the FreeBSD ncr driver to Linux-1.2.13.
 *
 * The original ncr driver has been written क्रम 386bsd and FreeBSD by
 *         Wolfgang Stanglmeier        <wolf@cologne.de>
 *         Stefan Esser                <se@mi.Uni-Koeln.de>
 * Copyright (C) 1994  Wolfgang Stanglmeier
 *
 * Other major contributions:
 *
 * NVRAM detection and पढ़ोing.
 * Copyright (C) 1997 Riअक्षरd Waltham <करोrmouse@farsrobt.demon.co.uk>
 *
 *-----------------------------------------------------------------------------
 */

#अगर_अघोषित SYM_MISC_H
#घोषणा SYM_MISC_H

/*
 *  A la VMS/CAM-3 queue management.
 */
प्रकार काष्ठा sym_quehead अणु
	काष्ठा sym_quehead *flink;	/* Forward  poपूर्णांकer */
	काष्ठा sym_quehead *blink;	/* Backward poपूर्णांकer */
पूर्ण SYM_QUEHEAD;

#घोषणा sym_que_init(ptr) करो अणु \
	(ptr)->flink = (ptr); (ptr)->blink = (ptr); \
पूर्ण जबतक (0)

अटल अंतरभूत काष्ठा sym_quehead *sym_que_first(काष्ठा sym_quehead *head)
अणु
	वापस (head->flink == head) ? 0 : head->flink;
पूर्ण

अटल अंतरभूत काष्ठा sym_quehead *sym_que_last(काष्ठा sym_quehead *head)
अणु
	वापस (head->blink == head) ? 0 : head->blink;
पूर्ण

अटल अंतरभूत व्योम __sym_que_add(काष्ठा sym_quehead * new,
	काष्ठा sym_quehead * blink,
	काष्ठा sym_quehead * flink)
अणु
	flink->blink	= new;
	new->flink	= flink;
	new->blink	= blink;
	blink->flink	= new;
पूर्ण

अटल अंतरभूत व्योम __sym_que_del(काष्ठा sym_quehead * blink,
	काष्ठा sym_quehead * flink)
अणु
	flink->blink = blink;
	blink->flink = flink;
पूर्ण

अटल अंतरभूत पूर्णांक sym_que_empty(काष्ठा sym_quehead *head)
अणु
	वापस head->flink == head;
पूर्ण

अटल अंतरभूत व्योम sym_que_splice(काष्ठा sym_quehead *list,
	काष्ठा sym_quehead *head)
अणु
	काष्ठा sym_quehead *first = list->flink;

	अगर (first != list) अणु
		काष्ठा sym_quehead *last = list->blink;
		काष्ठा sym_quehead *at   = head->flink;

		first->blink = head;
		head->flink  = first;

		last->flink = at;
		at->blink   = last;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम sym_que_move(काष्ठा sym_quehead *orig,
	काष्ठा sym_quehead *dest)
अणु
	काष्ठा sym_quehead *first, *last;

	first = orig->flink;
	अगर (first != orig) अणु
		first->blink = dest;
		dest->flink  = first;
		last = orig->blink;
		last->flink  = dest;
		dest->blink  = last;
		orig->flink  = orig;
		orig->blink  = orig;
	पूर्ण अन्यथा अणु
		dest->flink  = dest;
		dest->blink  = dest;
	पूर्ण
पूर्ण

#घोषणा sym_que_entry(ptr, type, member) container_of(ptr, type, member)

#घोषणा sym_insque(new, pos)		__sym_que_add(new, pos, (pos)->flink)

#घोषणा sym_remque(el)			__sym_que_del((el)->blink, (el)->flink)

#घोषणा sym_insque_head(new, head)	__sym_que_add(new, head, (head)->flink)

अटल अंतरभूत काष्ठा sym_quehead *sym_remque_head(काष्ठा sym_quehead *head)
अणु
	काष्ठा sym_quehead *elem = head->flink;

	अगर (elem != head)
		__sym_que_del(head, elem->flink);
	अन्यथा
		elem = शून्य;
	वापस elem;
पूर्ण

#घोषणा sym_insque_tail(new, head)	__sym_que_add(new, (head)->blink, head)

अटल अंतरभूत काष्ठा sym_quehead *sym_remque_tail(काष्ठा sym_quehead *head)
अणु
	काष्ठा sym_quehead *elem = head->blink;

	अगर (elem != head)
		__sym_que_del(elem->blink, head);
	अन्यथा
		elem = 0;
	वापस elem;
पूर्ण

/*
 *  This one may be useful.
 */
#घोषणा FOR_EACH_QUEUED_ELEMENT(head, qp) \
	क्रम (qp = (head)->flink; qp != (head); qp = qp->flink)
/*
 *  FreeBSD करोes not offer our kind of queue in the CAM CCB.
 *  So, we have to cast.
 */
#घोषणा sym_qptr(p)	((काष्ठा sym_quehead *) (p))

/*
 *  Simple biपंचांगap operations.
 */ 
#घोषणा sym_set_bit(p, n)	(((u32 *)(p))[(n)>>5] |=  (1<<((n)&0x1f)))
#घोषणा sym_clr_bit(p, n)	(((u32 *)(p))[(n)>>5] &= ~(1<<((n)&0x1f)))
#घोषणा sym_is_bit(p, n)	(((u32 *)(p))[(n)>>5] &   (1<<((n)&0x1f)))

/*
 * The below round up/करोwn macros are to be used with a स्थिरant 
 * as argument (माप(...) क्रम example), क्रम the compiler to 
 * optimize the whole thing.
 */
#घोषणा _U_(a,m)	(a)<=(1<<m)?m:

/*
 * Round up logarithm to base 2 of a 16 bit स्थिरant.
 */
#घोषणा _LGRU16_(a) \
( \
 _U_(a, 0)_U_(a, 1)_U_(a, 2)_U_(a, 3)_U_(a, 4)_U_(a, 5)_U_(a, 6)_U_(a, 7) \
 _U_(a, 8)_U_(a, 9)_U_(a,10)_U_(a,11)_U_(a,12)_U_(a,13)_U_(a,14)_U_(a,15) \
 16)

#पूर्ण_अगर /* SYM_MISC_H */
