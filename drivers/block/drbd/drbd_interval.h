<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __DRBD_INTERVAL_H
#घोषणा __DRBD_INTERVAL_H

#समावेश <linux/types.h>
#समावेश <linux/rbtree.h>

काष्ठा drbd_पूर्णांकerval अणु
	काष्ठा rb_node rb;
	sector_t sector;		/* start sector of the पूर्णांकerval */
	अचिन्हित पूर्णांक size;		/* size in bytes */
	sector_t end;			/* highest पूर्णांकerval end in subtree */
	अचिन्हित पूर्णांक local:1		/* local or remote request? */;
	अचिन्हित पूर्णांक रुकोing:1;		/* someone is रुकोing क्रम completion */
	अचिन्हित पूर्णांक completed:1;	/* this has been completed alपढ़ोy;
					 * ignore क्रम conflict detection */
पूर्ण;

अटल अंतरभूत व्योम drbd_clear_पूर्णांकerval(काष्ठा drbd_पूर्णांकerval *i)
अणु
	RB_CLEAR_NODE(&i->rb);
पूर्ण

अटल अंतरभूत bool drbd_पूर्णांकerval_empty(काष्ठा drbd_पूर्णांकerval *i)
अणु
	वापस RB_EMPTY_NODE(&i->rb);
पूर्ण

बाह्य bool drbd_insert_पूर्णांकerval(काष्ठा rb_root *, काष्ठा drbd_पूर्णांकerval *);
बाह्य bool drbd_contains_पूर्णांकerval(काष्ठा rb_root *, sector_t,
				   काष्ठा drbd_पूर्णांकerval *);
बाह्य व्योम drbd_हटाओ_पूर्णांकerval(काष्ठा rb_root *, काष्ठा drbd_पूर्णांकerval *);
बाह्य काष्ठा drbd_पूर्णांकerval *drbd_find_overlap(काष्ठा rb_root *, sector_t,
					अचिन्हित पूर्णांक);
बाह्य काष्ठा drbd_पूर्णांकerval *drbd_next_overlap(काष्ठा drbd_पूर्णांकerval *, sector_t,
					अचिन्हित पूर्णांक);

#घोषणा drbd_क्रम_each_overlap(i, root, sector, size)		\
	क्रम (i = drbd_find_overlap(root, sector, size);		\
	     i;							\
	     i = drbd_next_overlap(i, sector, size))

#पूर्ण_अगर  /* __DRBD_INTERVAL_H */
