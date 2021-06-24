<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* User-mappable watch queue
 *
 * Copyright (C) 2020 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 *
 * See Documentation/watch_queue.rst
 */

#अगर_अघोषित _LINUX_WATCH_QUEUE_H
#घोषणा _LINUX_WATCH_QUEUE_H

#समावेश <uapi/linux/watch_queue.h>
#समावेश <linux/kref.h>
#समावेश <linux/rcupdate.h>

#अगर_घोषित CONFIG_WATCH_QUEUE

काष्ठा cred;

काष्ठा watch_type_filter अणु
	क्रमागत watch_notअगरication_type type;
	__u32		subtype_filter[1];	/* Biपंचांगask of subtypes to filter on */
	__u32		info_filter;		/* Filter on watch_notअगरication::info */
	__u32		info_mask;		/* Mask of relevant bits in info_filter */
पूर्ण;

काष्ठा watch_filter अणु
	जोड़ अणु
		काष्ठा rcu_head	rcu;
		अचिन्हित दीर्घ	type_filter[2];	/* Biपंचांगask of accepted types */
	पूर्ण;
	u32			nr_filters;	/* Number of filters */
	काष्ठा watch_type_filter filters[];
पूर्ण;

काष्ठा watch_queue अणु
	काष्ठा rcu_head		rcu;
	काष्ठा watch_filter __rcu *filter;
	काष्ठा pipe_inode_info	*pipe;		/* The pipe we're using as a buffer */
	काष्ठा hlist_head	watches;	/* Contributory watches */
	काष्ठा page		**notes;	/* Pपुनः_स्मृतिated notअगरications */
	अचिन्हित दीर्घ		*notes_biपंचांगap;	/* Allocation biपंचांगap क्रम notes */
	काष्ठा kref		usage;		/* Object usage count */
	spinlock_t		lock;
	अचिन्हित पूर्णांक		nr_notes;	/* Number of notes */
	अचिन्हित पूर्णांक		nr_pages;	/* Number of pages in notes[] */
	bool			defunct;	/* T when queues बंदd */
पूर्ण;

/*
 * Representation of a watch on an object.
 */
काष्ठा watch अणु
	जोड़ अणु
		काष्ठा rcu_head	rcu;
		u32		info_id;	/* ID to be OR'd in to info field */
	पूर्ण;
	काष्ठा watch_queue __rcu *queue;	/* Queue to post events to */
	काष्ठा hlist_node	queue_node;	/* Link in queue->watches */
	काष्ठा watch_list __rcu	*watch_list;
	काष्ठा hlist_node	list_node;	/* Link in watch_list->watchers */
	स्थिर काष्ठा cred	*cred;		/* Creds of the owner of the watch */
	व्योम			*निजी;	/* Private data क्रम the watched object */
	u64			id;		/* Internal identअगरier */
	काष्ठा kref		usage;		/* Object usage count */
पूर्ण;

/*
 * List of watches on an object.
 */
काष्ठा watch_list अणु
	काष्ठा rcu_head		rcu;
	काष्ठा hlist_head	watchers;
	व्योम (*release_watch)(काष्ठा watch *);
	spinlock_t		lock;
पूर्ण;

बाह्य व्योम __post_watch_notअगरication(काष्ठा watch_list *,
				      काष्ठा watch_notअगरication *,
				      स्थिर काष्ठा cred *,
				      u64);
बाह्य काष्ठा watch_queue *get_watch_queue(पूर्णांक);
बाह्य व्योम put_watch_queue(काष्ठा watch_queue *);
बाह्य व्योम init_watch(काष्ठा watch *, काष्ठा watch_queue *);
बाह्य पूर्णांक add_watch_to_object(काष्ठा watch *, काष्ठा watch_list *);
बाह्य पूर्णांक हटाओ_watch_from_object(काष्ठा watch_list *, काष्ठा watch_queue *, u64, bool);
बाह्य दीर्घ watch_queue_set_size(काष्ठा pipe_inode_info *, अचिन्हित पूर्णांक);
बाह्य दीर्घ watch_queue_set_filter(काष्ठा pipe_inode_info *,
				   काष्ठा watch_notअगरication_filter __user *);
बाह्य पूर्णांक watch_queue_init(काष्ठा pipe_inode_info *);
बाह्य व्योम watch_queue_clear(काष्ठा watch_queue *);

अटल अंतरभूत व्योम init_watch_list(काष्ठा watch_list *wlist,
				   व्योम (*release_watch)(काष्ठा watch *))
अणु
	INIT_HLIST_HEAD(&wlist->watchers);
	spin_lock_init(&wlist->lock);
	wlist->release_watch = release_watch;
पूर्ण

अटल अंतरभूत व्योम post_watch_notअगरication(काष्ठा watch_list *wlist,
					   काष्ठा watch_notअगरication *n,
					   स्थिर काष्ठा cred *cred,
					   u64 id)
अणु
	अगर (unlikely(wlist))
		__post_watch_notअगरication(wlist, n, cred, id);
पूर्ण

अटल अंतरभूत व्योम हटाओ_watch_list(काष्ठा watch_list *wlist, u64 id)
अणु
	अगर (wlist) अणु
		हटाओ_watch_from_object(wlist, शून्य, id, true);
		kमुक्त_rcu(wlist, rcu);
	पूर्ण
पूर्ण

/**
 * watch_माप - Calculate the inक्रमmation part of the size of a watch record,
 * given the काष्ठाure size.
 */
#घोषणा watch_माप(STRUCT) (माप(STRUCT) << WATCH_INFO_LENGTH__SHIFT)

#अन्यथा
अटल अंतरभूत पूर्णांक watch_queue_init(काष्ठा pipe_inode_info *pipe)
अणु
	वापस -ENOPKG;
पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर /* _LINUX_WATCH_QUEUE_H */
