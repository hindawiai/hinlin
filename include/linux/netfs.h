<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* Network fileप्रणाली support services.
 *
 * Copyright (C) 2021 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 *
 * See:
 *
 *	Documentation/fileप्रणालीs/netfs_library.rst
 *
 * क्रम a description of the network fileप्रणाली पूर्णांकerface declared here.
 */

#अगर_अघोषित _LINUX_NETFS_H
#घोषणा _LINUX_NETFS_H

#समावेश <linux/workqueue.h>
#समावेश <linux/fs.h>
#समावेश <linux/pagemap.h>

/*
 * Overload PG_निजी_2 to give us PG_fscache - this is used to indicate that
 * a page is currently backed by a local disk cache
 */
#घोषणा PageFsCache(page)		PagePrivate2((page))
#घोषणा SetPageFsCache(page)		SetPagePrivate2((page))
#घोषणा ClearPageFsCache(page)		ClearPagePrivate2((page))
#घोषणा TestSetPageFsCache(page)	TestSetPagePrivate2((page))
#घोषणा TestClearPageFsCache(page)	TestClearPagePrivate2((page))

/**
 * set_page_fscache - Set PG_fscache on a page and take a ref
 * @page: The page.
 *
 * Set the PG_fscache (PG_निजी_2) flag on a page and take the reference
 * needed क्रम the VM to handle its lअगरeसमय correctly.  This sets the flag and
 * takes the reference unconditionally, so care must be taken not to set the
 * flag again अगर it's alपढ़ोy set.
 */
अटल अंतरभूत व्योम set_page_fscache(काष्ठा page *page)
अणु
	set_page_निजी_2(page);
पूर्ण

/**
 * end_page_fscache - Clear PG_fscache and release any रुकोers
 * @page: The page
 *
 * Clear the PG_fscache (PG_निजी_2) bit on a page and wake up any sleepers
 * रुकोing क्रम this.  The page ref held क्रम PG_निजी_2 being set is released.
 *
 * This is, क्रम example, used when a netfs page is being written to a local
 * disk cache, thereby allowing ग_लिखोs to the cache क्रम the same page to be
 * serialised.
 */
अटल अंतरभूत व्योम end_page_fscache(काष्ठा page *page)
अणु
	end_page_निजी_2(page);
पूर्ण

/**
 * रुको_on_page_fscache - Wait क्रम PG_fscache to be cleared on a page
 * @page: The page to रुको on
 *
 * Wait क्रम PG_fscache (aka PG_निजी_2) to be cleared on a page.
 */
अटल अंतरभूत व्योम रुको_on_page_fscache(काष्ठा page *page)
अणु
	रुको_on_page_निजी_2(page);
पूर्ण

/**
 * रुको_on_page_fscache_समाप्तable - Wait क्रम PG_fscache to be cleared on a page
 * @page: The page to रुको on
 *
 * Wait क्रम PG_fscache (aka PG_निजी_2) to be cleared on a page or until a
 * fatal संकेत is received by the calling task.
 *
 * Return:
 * - 0 अगर successful.
 * - -EINTR अगर a fatal संकेत was encountered.
 */
अटल अंतरभूत पूर्णांक रुको_on_page_fscache_समाप्तable(काष्ठा page *page)
अणु
	वापस रुको_on_page_निजी_2_समाप्तable(page);
पूर्ण

क्रमागत netfs_पढ़ो_source अणु
	NETFS_FILL_WITH_ZEROES,
	NETFS_DOWNLOAD_FROM_SERVER,
	NETFS_READ_FROM_CACHE,
	NETFS_INVALID_READ,
पूर्ण __mode(byte);

प्रकार व्योम (*netfs_io_terminated_t)(व्योम *priv, sमाप_प्रकार transferred_or_error,
				      bool was_async);

/*
 * Resources required to करो operations on a cache.
 */
काष्ठा netfs_cache_resources अणु
	स्थिर काष्ठा netfs_cache_ops	*ops;
	व्योम				*cache_priv;
	व्योम				*cache_priv2;
पूर्ण;

/*
 * Descriptor क्रम a single component subrequest.
 */
काष्ठा netfs_पढ़ो_subrequest अणु
	काष्ठा netfs_पढ़ो_request *rreq;	/* Supervising पढ़ो request */
	काष्ठा list_head	rreq_link;	/* Link in rreq->subrequests */
	loff_t			start;		/* Where to start the I/O */
	माप_प्रकार			len;		/* Size of the I/O */
	माप_प्रकार			transferred;	/* Amount of data transferred */
	refcount_t		usage;
	लघु			error;		/* 0 or error that occurred */
	अचिन्हित लघु		debug_index;	/* Index in list (क्रम debugging output) */
	क्रमागत netfs_पढ़ो_source	source;		/* Where to पढ़ो from */
	अचिन्हित दीर्घ		flags;
#घोषणा NETFS_SREQ_WRITE_TO_CACHE	0	/* Set अगर should ग_लिखो to cache */
#घोषणा NETFS_SREQ_CLEAR_TAIL		1	/* Set अगर the rest of the पढ़ो should be cleared */
#घोषणा NETFS_SREQ_SHORT_READ		2	/* Set अगर there was a लघु पढ़ो from the cache */
#घोषणा NETFS_SREQ_SEEK_DATA_READ	3	/* Set अगर ->पढ़ो() should SEEK_DATA first */
#घोषणा NETFS_SREQ_NO_PROGRESS		4	/* Set अगर we didn't manage to पढ़ो any data */
पूर्ण;

/*
 * Descriptor क्रम a पढ़ो helper request.  This is used to make multiple I/O
 * requests on a variety of sources and then stitch the result together.
 */
काष्ठा netfs_पढ़ो_request अणु
	काष्ठा work_काष्ठा	work;
	काष्ठा inode		*inode;		/* The file being accessed */
	काष्ठा address_space	*mapping;	/* The mapping being accessed */
	काष्ठा netfs_cache_resources cache_resources;
	काष्ठा list_head	subrequests;	/* Requests to fetch I/O from disk or net */
	व्योम			*netfs_priv;	/* Private data क्रम the netfs */
	अचिन्हित पूर्णांक		debug_id;
	अचिन्हित पूर्णांक		cookie_debug_id;
	atomic_t		nr_rd_ops;	/* Number of पढ़ो ops in progress */
	atomic_t		nr_wr_ops;	/* Number of ग_लिखो ops in progress */
	माप_प्रकार			submitted;	/* Amount submitted क्रम I/O so far */
	माप_प्रकार			len;		/* Length of the request */
	लघु			error;		/* 0 or error that occurred */
	loff_t			i_size;		/* Size of the file */
	loff_t			start;		/* Start position */
	pgoff_t			no_unlock_page;	/* Don't unlock this page after पढ़ो */
	refcount_t		usage;
	अचिन्हित दीर्घ		flags;
#घोषणा NETFS_RREQ_INCOMPLETE_IO	0	/* Some ioreqs terminated लघु or with error */
#घोषणा NETFS_RREQ_WRITE_TO_CACHE	1	/* Need to ग_लिखो to the cache */
#घोषणा NETFS_RREQ_NO_UNLOCK_PAGE	2	/* Don't unlock no_unlock_page on completion */
#घोषणा NETFS_RREQ_DONT_UNLOCK_PAGES	3	/* Don't unlock the pages on completion */
#घोषणा NETFS_RREQ_FAILED		4	/* The request failed */
#घोषणा NETFS_RREQ_IN_PROGRESS		5	/* Unlocked when the request completes */
	स्थिर काष्ठा netfs_पढ़ो_request_ops *netfs_ops;
पूर्ण;

/*
 * Operations the network fileप्रणाली can/must provide to the helpers.
 */
काष्ठा netfs_पढ़ो_request_ops अणु
	bool (*is_cache_enabled)(काष्ठा inode *inode);
	व्योम (*init_rreq)(काष्ठा netfs_पढ़ो_request *rreq, काष्ठा file *file);
	पूर्णांक (*begin_cache_operation)(काष्ठा netfs_पढ़ो_request *rreq);
	व्योम (*expand_पढ़ोahead)(काष्ठा netfs_पढ़ो_request *rreq);
	bool (*clamp_length)(काष्ठा netfs_पढ़ो_subrequest *subreq);
	व्योम (*issue_op)(काष्ठा netfs_पढ़ो_subrequest *subreq);
	bool (*is_still_valid)(काष्ठा netfs_पढ़ो_request *rreq);
	पूर्णांक (*check_ग_लिखो_begin)(काष्ठा file *file, loff_t pos, अचिन्हित len,
				 काष्ठा page *page, व्योम **_fsdata);
	व्योम (*करोne)(काष्ठा netfs_पढ़ो_request *rreq);
	व्योम (*cleanup)(काष्ठा address_space *mapping, व्योम *netfs_priv);
पूर्ण;

/*
 * Table of operations क्रम access to a cache.  This is obtained by
 * rreq->ops->begin_cache_operation().
 */
काष्ठा netfs_cache_ops अणु
	/* End an operation */
	व्योम (*end_operation)(काष्ठा netfs_cache_resources *cres);

	/* Read data from the cache */
	पूर्णांक (*पढ़ो)(काष्ठा netfs_cache_resources *cres,
		    loff_t start_pos,
		    काष्ठा iov_iter *iter,
		    bool seek_data,
		    netfs_io_terminated_t term_func,
		    व्योम *term_func_priv);

	/* Write data to the cache */
	पूर्णांक (*ग_लिखो)(काष्ठा netfs_cache_resources *cres,
		     loff_t start_pos,
		     काष्ठा iov_iter *iter,
		     netfs_io_terminated_t term_func,
		     व्योम *term_func_priv);

	/* Expand पढ़ोahead request */
	व्योम (*expand_पढ़ोahead)(काष्ठा netfs_cache_resources *cres,
				 loff_t *_start, माप_प्रकार *_len, loff_t i_size);

	/* Prepare a पढ़ो operation, लघुening it to a cached/uncached
	 * boundary as appropriate.
	 */
	क्रमागत netfs_पढ़ो_source (*prepare_पढ़ो)(काष्ठा netfs_पढ़ो_subrequest *subreq,
					       loff_t i_size);

	/* Prepare a ग_लिखो operation, working out what part of the ग_लिखो we can
	 * actually करो.
	 */
	पूर्णांक (*prepare_ग_लिखो)(काष्ठा netfs_cache_resources *cres,
			     loff_t *_start, माप_प्रकार *_len, loff_t i_size);
पूर्ण;

काष्ठा पढ़ोahead_control;
बाह्य व्योम netfs_पढ़ोahead(काष्ठा पढ़ोahead_control *,
			    स्थिर काष्ठा netfs_पढ़ो_request_ops *,
			    व्योम *);
बाह्य पूर्णांक netfs_पढ़ोpage(काष्ठा file *,
			  काष्ठा page *,
			  स्थिर काष्ठा netfs_पढ़ो_request_ops *,
			  व्योम *);
बाह्य पूर्णांक netfs_ग_लिखो_begin(काष्ठा file *, काष्ठा address_space *,
			     loff_t, अचिन्हित पूर्णांक, अचिन्हित पूर्णांक, काष्ठा page **,
			     व्योम **,
			     स्थिर काष्ठा netfs_पढ़ो_request_ops *,
			     व्योम *);

बाह्य व्योम netfs_subreq_terminated(काष्ठा netfs_पढ़ो_subrequest *, sमाप_प्रकार, bool);
बाह्य व्योम netfs_stats_show(काष्ठा seq_file *);

#पूर्ण_अगर /* _LINUX_NETFS_H */
