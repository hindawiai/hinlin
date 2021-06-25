<शैली गुरु>
/*
 * Copyright (C) 2003 Sistina Software
 * Copyright (C) 2004 - 2008 Red Hat, Inc. All rights reserved.
 *
 * Device-Mapper low-level I/O.
 *
 * This file is released under the GPL.
 */

#अगर_अघोषित _LINUX_DM_IO_H
#घोषणा _LINUX_DM_IO_H

#अगर_घोषित __KERNEL__

#समावेश <linux/types.h>

काष्ठा dm_io_region अणु
	काष्ठा block_device *bdev;
	sector_t sector;
	sector_t count;		/* If this is zero the region is ignored. */
पूर्ण;

काष्ठा page_list अणु
	काष्ठा page_list *next;
	काष्ठा page *page;
पूर्ण;

प्रकार व्योम (*io_notअगरy_fn)(अचिन्हित दीर्घ error, व्योम *context);

क्रमागत dm_io_mem_type अणु
	DM_IO_PAGE_LIST,/* Page list */
	DM_IO_BIO,	/* Bio vector */
	DM_IO_VMA,	/* Virtual memory area */
	DM_IO_KMEM,	/* Kernel memory */
पूर्ण;

काष्ठा dm_io_memory अणु
	क्रमागत dm_io_mem_type type;

	अचिन्हित offset;

	जोड़ अणु
		काष्ठा page_list *pl;
		काष्ठा bio *bio;
		व्योम *vma;
		व्योम *addr;
	पूर्ण ptr;
पूर्ण;

काष्ठा dm_io_notअगरy अणु
	io_notअगरy_fn fn;	/* Callback क्रम asynchronous requests */
	व्योम *context;		/* Passed to callback */
पूर्ण;

/*
 * IO request काष्ठाure
 */
काष्ठा dm_io_client;
काष्ठा dm_io_request अणु
	पूर्णांक bi_op;			/* REQ_OP */
	पूर्णांक bi_op_flags;		/* req_flag_bits */
	काष्ठा dm_io_memory mem;	/* Memory to use क्रम io */
	काष्ठा dm_io_notअगरy notअगरy;	/* Synchronous अगर notअगरy.fn is शून्य */
	काष्ठा dm_io_client *client;	/* Client memory handler */
पूर्ण;

/*
 * For async io calls, users can alternatively use the dm_io() function below
 * and dm_io_client_create() to create निजी mempools क्रम the client.
 *
 * Create/destroy may block.
 */
काष्ठा dm_io_client *dm_io_client_create(व्योम);
व्योम dm_io_client_destroy(काष्ठा dm_io_client *client);

/*
 * IO पूर्णांकerface using निजी per-client pools.
 * Each bit in the optional 'sync_error_bits' bitset indicates whether an
 * error occurred करोing io to the corresponding region.
 */
पूर्णांक dm_io(काष्ठा dm_io_request *io_req, अचिन्हित num_regions,
	  काष्ठा dm_io_region *region, अचिन्हित दीर्घ *sync_error_bits);

#पूर्ण_अगर	/* __KERNEL__ */
#पूर्ण_अगर	/* _LINUX_DM_IO_H */
