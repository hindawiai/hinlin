<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * zfcp device driver
 *
 * Data काष्ठाure and helper functions क्रम tracking pending FSF
 * requests.
 *
 * Copyright IBM Corp. 2009, 2016
 */

#अगर_अघोषित ZFCP_REQLIST_H
#घोषणा ZFCP_REQLIST_H

/* number of hash buckets */
#घोषणा ZFCP_REQ_LIST_BUCKETS 128

/**
 * काष्ठा zfcp_reqlist - Container क्रम request list (reqlist)
 * @lock: Spinlock क्रम protecting the hash list
 * @buckets: Array of hashbuckets, each is a list of requests in this bucket
 */
काष्ठा zfcp_reqlist अणु
	spinlock_t lock;
	काष्ठा list_head buckets[ZFCP_REQ_LIST_BUCKETS];
पूर्ण;

अटल अंतरभूत पूर्णांक zfcp_reqlist_hash(अचिन्हित दीर्घ req_id)
अणु
	वापस req_id % ZFCP_REQ_LIST_BUCKETS;
पूर्ण

/**
 * zfcp_reqlist_alloc - Allocate and initialize reqlist
 *
 * Returns poपूर्णांकer to allocated reqlist on success, or शून्य on
 * allocation failure.
 */
अटल अंतरभूत काष्ठा zfcp_reqlist *zfcp_reqlist_alloc(व्योम)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा zfcp_reqlist *rl;

	rl = kzalloc(माप(काष्ठा zfcp_reqlist), GFP_KERNEL);
	अगर (!rl)
		वापस शून्य;

	spin_lock_init(&rl->lock);

	क्रम (i = 0; i < ZFCP_REQ_LIST_BUCKETS; i++)
		INIT_LIST_HEAD(&rl->buckets[i]);

	वापस rl;
पूर्ण

/**
 * zfcp_reqlist_isempty - Check whether the request list empty
 * @rl: poपूर्णांकer to reqlist
 *
 * Returns: 1 अगर list is empty, 0 अगर not
 */
अटल अंतरभूत पूर्णांक zfcp_reqlist_isempty(काष्ठा zfcp_reqlist *rl)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ZFCP_REQ_LIST_BUCKETS; i++)
		अगर (!list_empty(&rl->buckets[i]))
			वापस 0;
	वापस 1;
पूर्ण

/**
 * zfcp_reqlist_मुक्त - Free allocated memory क्रम reqlist
 * @rl: The reqlist where to मुक्त memory
 */
अटल अंतरभूत व्योम zfcp_reqlist_मुक्त(काष्ठा zfcp_reqlist *rl)
अणु
	/* sanity check */
	BUG_ON(!zfcp_reqlist_isempty(rl));

	kमुक्त(rl);
पूर्ण

अटल अंतरभूत काष्ठा zfcp_fsf_req *
_zfcp_reqlist_find(काष्ठा zfcp_reqlist *rl, अचिन्हित दीर्घ req_id)
अणु
	काष्ठा zfcp_fsf_req *req;
	अचिन्हित पूर्णांक i;

	i = zfcp_reqlist_hash(req_id);
	list_क्रम_each_entry(req, &rl->buckets[i], list)
		अगर (req->req_id == req_id)
			वापस req;
	वापस शून्य;
पूर्ण

/**
 * zfcp_reqlist_find - Lookup FSF request by its request id
 * @rl: The reqlist where to lookup the FSF request
 * @req_id: The request id to look क्रम
 *
 * Returns a poपूर्णांकer to the FSF request with the specअगरied request id
 * or शून्य अगर there is no known FSF request with this id.
 */
अटल अंतरभूत काष्ठा zfcp_fsf_req *
zfcp_reqlist_find(काष्ठा zfcp_reqlist *rl, अचिन्हित दीर्घ req_id)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा zfcp_fsf_req *req;

	spin_lock_irqsave(&rl->lock, flags);
	req = _zfcp_reqlist_find(rl, req_id);
	spin_unlock_irqrestore(&rl->lock, flags);

	वापस req;
पूर्ण

/**
 * zfcp_reqlist_find_rm - Lookup request by id and हटाओ it from reqlist
 * @rl: reqlist where to search and हटाओ entry
 * @req_id: The request id of the request to look क्रम
 *
 * This functions tries to find the FSF request with the specअगरied
 * id and then हटाओs it from the reqlist. The reqlist lock is held
 * during both steps of the operation.
 *
 * Returns: Poपूर्णांकer to the FSF request अगर the request has been found,
 * शून्य अगर it has not been found.
 */
अटल अंतरभूत काष्ठा zfcp_fsf_req *
zfcp_reqlist_find_rm(काष्ठा zfcp_reqlist *rl, अचिन्हित दीर्घ req_id)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा zfcp_fsf_req *req;

	spin_lock_irqsave(&rl->lock, flags);
	req = _zfcp_reqlist_find(rl, req_id);
	अगर (req)
		list_del(&req->list);
	spin_unlock_irqrestore(&rl->lock, flags);

	वापस req;
पूर्ण

/**
 * zfcp_reqlist_add - Add entry to reqlist
 * @rl: reqlist where to add the entry
 * @req: The entry to add
 *
 * The request id always increases. As an optimization new requests
 * are added here with list_add_tail at the end of the bucket lists
 * जबतक old requests are looked up starting at the beginning of the
 * lists.
 */
अटल अंतरभूत व्योम zfcp_reqlist_add(काष्ठा zfcp_reqlist *rl,
				    काष्ठा zfcp_fsf_req *req)
अणु
	अचिन्हित पूर्णांक i;
	अचिन्हित दीर्घ flags;

	i = zfcp_reqlist_hash(req->req_id);

	spin_lock_irqsave(&rl->lock, flags);
	list_add_tail(&req->list, &rl->buckets[i]);
	spin_unlock_irqrestore(&rl->lock, flags);
पूर्ण

/**
 * zfcp_reqlist_move - Move all entries from reqlist to simple list
 * @rl: The zfcp_reqlist where to हटाओ all entries
 * @list: The list where to move all entries
 */
अटल अंतरभूत व्योम zfcp_reqlist_move(काष्ठा zfcp_reqlist *rl,
				     काष्ठा list_head *list)
अणु
	अचिन्हित पूर्णांक i;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&rl->lock, flags);
	क्रम (i = 0; i < ZFCP_REQ_LIST_BUCKETS; i++)
		list_splice_init(&rl->buckets[i], list);
	spin_unlock_irqrestore(&rl->lock, flags);
पूर्ण

/**
 * zfcp_reqlist_apply_क्रम_all() - apply a function to every request.
 * @rl: the requestlist that contains the target requests.
 * @f: the function to apply to each request; the first parameter of the
 *     function will be the target-request; the second parameter is the same
 *     poपूर्णांकer as given with the argument @data.
 * @data: मुक्तly chosen argument; passed through to @f as second parameter.
 *
 * Uses :c:macro:`list_क्रम_each_entry` to iterate over the lists in the hash-
 * table (not a 'safe' variant, so don't modअगरy the list).
 *
 * Holds @rl->lock over the entire request-iteration.
 */
अटल अंतरभूत व्योम
zfcp_reqlist_apply_क्रम_all(काष्ठा zfcp_reqlist *rl,
			   व्योम (*f)(काष्ठा zfcp_fsf_req *, व्योम *), व्योम *data)
अणु
	काष्ठा zfcp_fsf_req *req;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक i;

	spin_lock_irqsave(&rl->lock, flags);
	क्रम (i = 0; i < ZFCP_REQ_LIST_BUCKETS; i++)
		list_क्रम_each_entry(req, &rl->buckets[i], list)
			f(req, data);
	spin_unlock_irqrestore(&rl->lock, flags);
पूर्ण

#पूर्ण_अगर /* ZFCP_REQLIST_H */
