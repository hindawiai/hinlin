<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000-2006 Silicon Graphics, Inc.
 * All Rights Reserved.
 */
#अगर_अघोषित __XFS_SUPPORT_MRLOCK_H__
#घोषणा __XFS_SUPPORT_MRLOCK_H__

#समावेश <linux/rwsem.h>

प्रकार काष्ठा अणु
	काष्ठा rw_semaphore	mr_lock;
#अगर defined(DEBUG) || defined(XFS_WARN)
	पूर्णांक			mr_ग_लिखोr;
#पूर्ण_अगर
पूर्ण mrlock_t;

#अगर defined(DEBUG) || defined(XFS_WARN)
#घोषणा mrinit(mrp, name)	\
	करो अणु (mrp)->mr_ग_लिखोr = 0; init_rwsem(&(mrp)->mr_lock); पूर्ण जबतक (0)
#अन्यथा
#घोषणा mrinit(mrp, name)	\
	करो अणु init_rwsem(&(mrp)->mr_lock); पूर्ण जबतक (0)
#पूर्ण_अगर

#घोषणा mrlock_init(mrp, t,n,s)	mrinit(mrp, n)
#घोषणा mrमुक्त(mrp)		करो अणु पूर्ण जबतक (0)

अटल अंतरभूत व्योम mraccess_nested(mrlock_t *mrp, पूर्णांक subclass)
अणु
	करोwn_पढ़ो_nested(&mrp->mr_lock, subclass);
पूर्ण

अटल अंतरभूत व्योम mrupdate_nested(mrlock_t *mrp, पूर्णांक subclass)
अणु
	करोwn_ग_लिखो_nested(&mrp->mr_lock, subclass);
#अगर defined(DEBUG) || defined(XFS_WARN)
	mrp->mr_ग_लिखोr = 1;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत पूर्णांक mrtryaccess(mrlock_t *mrp)
अणु
	वापस करोwn_पढ़ो_trylock(&mrp->mr_lock);
पूर्ण

अटल अंतरभूत पूर्णांक mrtryupdate(mrlock_t *mrp)
अणु
	अगर (!करोwn_ग_लिखो_trylock(&mrp->mr_lock))
		वापस 0;
#अगर defined(DEBUG) || defined(XFS_WARN)
	mrp->mr_ग_लिखोr = 1;
#पूर्ण_अगर
	वापस 1;
पूर्ण

अटल अंतरभूत व्योम mrunlock_excl(mrlock_t *mrp)
अणु
#अगर defined(DEBUG) || defined(XFS_WARN)
	mrp->mr_ग_लिखोr = 0;
#पूर्ण_अगर
	up_ग_लिखो(&mrp->mr_lock);
पूर्ण

अटल अंतरभूत व्योम mrunlock_shared(mrlock_t *mrp)
अणु
	up_पढ़ो(&mrp->mr_lock);
पूर्ण

अटल अंतरभूत व्योम mrdemote(mrlock_t *mrp)
अणु
#अगर defined(DEBUG) || defined(XFS_WARN)
	mrp->mr_ग_लिखोr = 0;
#पूर्ण_अगर
	करोwngrade_ग_लिखो(&mrp->mr_lock);
पूर्ण

#पूर्ण_अगर /* __XFS_SUPPORT_MRLOCK_H__ */
