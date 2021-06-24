<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * vsp1_dl.c  --  R-Car VSP1 Display List
 *
 * Copyright (C) 2015 Renesas Corporation
 *
 * Contact: Laurent Pinअक्षरt (laurent.pinअक्षरt@ideasonboard.com)
 */

#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/gfp.h>
#समावेश <linux/refcount.h>
#समावेश <linux/slab.h>
#समावेश <linux/workqueue.h>

#समावेश "vsp1.h"
#समावेश "vsp1_dl.h"

#घोषणा VSP1_DL_NUM_ENTRIES		256

#घोषणा VSP1_DLH_INT_ENABLE		(1 << 1)
#घोषणा VSP1_DLH_AUTO_START		(1 << 0)

#घोषणा VSP1_DLH_EXT_PRE_CMD_EXEC	(1 << 9)
#घोषणा VSP1_DLH_EXT_POST_CMD_EXEC	(1 << 8)

काष्ठा vsp1_dl_header_list अणु
	u32 num_bytes;
	u32 addr;
पूर्ण __packed;

काष्ठा vsp1_dl_header अणु
	u32 num_lists;
	काष्ठा vsp1_dl_header_list lists[8];
	u32 next_header;
	u32 flags;
पूर्ण __packed;

/**
 * काष्ठा vsp1_dl_ext_header - Extended display list header
 * @padding: padding zero bytes क्रम alignment
 * @pre_ext_dl_num_cmd: number of pre-extended command bodies to parse
 * @flags: enables or disables execution of the pre and post command
 * @pre_ext_dl_plist: start address of pre-extended display list bodies
 * @post_ext_dl_num_cmd: number of post-extended command bodies to parse
 * @post_ext_dl_plist: start address of post-extended display list bodies
 */
काष्ठा vsp1_dl_ext_header अणु
	u32 padding;

	/*
	 * The datasheet represents flags as stored beक्रमe pre_ext_dl_num_cmd,
	 * expecting 32-bit accesses. The flags are appropriate to the whole
	 * header, not just the pre_ext command, and thus warrant being
	 * separated out. Due to byte ordering, and representing as 16 bit
	 * values here, the flags must be positioned after the
	 * pre_ext_dl_num_cmd.
	 */
	u16 pre_ext_dl_num_cmd;
	u16 flags;
	u32 pre_ext_dl_plist;

	u32 post_ext_dl_num_cmd;
	u32 post_ext_dl_plist;
पूर्ण __packed;

काष्ठा vsp1_dl_header_extended अणु
	काष्ठा vsp1_dl_header header;
	काष्ठा vsp1_dl_ext_header ext;
पूर्ण __packed;

काष्ठा vsp1_dl_entry अणु
	u32 addr;
	u32 data;
पूर्ण __packed;

/**
 * काष्ठा vsp1_pre_ext_dl_body - Pre Extended Display List Body
 * @opcode: Extended display list command operation code
 * @flags: Pre-extended command flags. These are specअगरic to each command
 * @address_set: Source address set poपूर्णांकer. Must have 16-byte alignment
 * @reserved: Zero bits क्रम alignment.
 */
काष्ठा vsp1_pre_ext_dl_body अणु
	u32 opcode;
	u32 flags;
	u32 address_set;
	u32 reserved;
पूर्ण __packed;

/**
 * काष्ठा vsp1_dl_body - Display list body
 * @list: entry in the display list list of bodies
 * @मुक्त: entry in the pool मुक्त body list
 * @refcnt: reference tracking क्रम the body
 * @pool: pool to which this body beदीर्घs
 * @entries: array of entries
 * @dma: DMA address of the entries
 * @size: size of the DMA memory in bytes
 * @num_entries: number of stored entries
 * @max_entries: number of entries available
 */
काष्ठा vsp1_dl_body अणु
	काष्ठा list_head list;
	काष्ठा list_head मुक्त;

	refcount_t refcnt;

	काष्ठा vsp1_dl_body_pool *pool;

	काष्ठा vsp1_dl_entry *entries;
	dma_addr_t dma;
	माप_प्रकार size;

	अचिन्हित पूर्णांक num_entries;
	अचिन्हित पूर्णांक max_entries;
पूर्ण;

/**
 * काष्ठा vsp1_dl_body_pool - display list body pool
 * @dma: DMA address of the entries
 * @size: size of the full DMA memory pool in bytes
 * @mem: CPU memory poपूर्णांकer क्रम the pool
 * @bodies: Array of DLB काष्ठाures क्रम the pool
 * @मुक्त: List of मुक्त DLB entries
 * @lock: Protects the मुक्त list
 * @vsp1: the VSP1 device
 */
काष्ठा vsp1_dl_body_pool अणु
	/* DMA allocation */
	dma_addr_t dma;
	माप_प्रकार size;
	व्योम *mem;

	/* Body management */
	काष्ठा vsp1_dl_body *bodies;
	काष्ठा list_head मुक्त;
	spinlock_t lock;

	काष्ठा vsp1_device *vsp1;
पूर्ण;

/**
 * काष्ठा vsp1_dl_cmd_pool - Display List commands pool
 * @dma: DMA address of the entries
 * @size: size of the full DMA memory pool in bytes
 * @mem: CPU memory poपूर्णांकer क्रम the pool
 * @cmds: Array of command काष्ठाures क्रम the pool
 * @मुक्त: Free pool entries
 * @lock: Protects the मुक्त list
 * @vsp1: the VSP1 device
 */
काष्ठा vsp1_dl_cmd_pool अणु
	/* DMA allocation */
	dma_addr_t dma;
	माप_प्रकार size;
	व्योम *mem;

	काष्ठा vsp1_dl_ext_cmd *cmds;
	काष्ठा list_head मुक्त;

	spinlock_t lock;

	काष्ठा vsp1_device *vsp1;
पूर्ण;

/**
 * काष्ठा vsp1_dl_list - Display list
 * @list: entry in the display list manager lists
 * @dlm: the display list manager
 * @header: display list header
 * @extension: extended display list header. शून्य क्रम normal lists
 * @dma: DMA address क्रम the header
 * @body0: first display list body
 * @bodies: list of extra display list bodies
 * @pre_cmd: pre command to be issued through extended dl header
 * @post_cmd: post command to be issued through extended dl header
 * @has_chain: अगर true, indicates that there's a partition chain
 * @chain: entry in the display list partition chain
 * @flags: display list flags, a combination of VSP1_DL_FRAME_END_*
 */
काष्ठा vsp1_dl_list अणु
	काष्ठा list_head list;
	काष्ठा vsp1_dl_manager *dlm;

	काष्ठा vsp1_dl_header *header;
	काष्ठा vsp1_dl_ext_header *extension;
	dma_addr_t dma;

	काष्ठा vsp1_dl_body *body0;
	काष्ठा list_head bodies;

	काष्ठा vsp1_dl_ext_cmd *pre_cmd;
	काष्ठा vsp1_dl_ext_cmd *post_cmd;

	bool has_chain;
	काष्ठा list_head chain;

	अचिन्हित पूर्णांक flags;
पूर्ण;

/**
 * काष्ठा vsp1_dl_manager - Display List manager
 * @index: index of the related WPF
 * @singleshot: execute the display list in single-shot mode
 * @vsp1: the VSP1 device
 * @lock: protects the मुक्त, active, queued, and pending lists
 * @मुक्त: array of all मुक्त display lists
 * @active: list currently being processed (loaded) by hardware
 * @queued: list queued to the hardware (written to the DL रेजिस्टरs)
 * @pending: list रुकोing to be queued to the hardware
 * @pool: body pool क्रम the display list bodies
 * @cmdpool: commands pool क्रम extended display list
 */
काष्ठा vsp1_dl_manager अणु
	अचिन्हित पूर्णांक index;
	bool singleshot;
	काष्ठा vsp1_device *vsp1;

	spinlock_t lock;
	काष्ठा list_head मुक्त;
	काष्ठा vsp1_dl_list *active;
	काष्ठा vsp1_dl_list *queued;
	काष्ठा vsp1_dl_list *pending;

	काष्ठा vsp1_dl_body_pool *pool;
	काष्ठा vsp1_dl_cmd_pool *cmdpool;
पूर्ण;

/* -----------------------------------------------------------------------------
 * Display List Body Management
 */

/**
 * vsp1_dl_body_pool_create - Create a pool of bodies from a single allocation
 * @vsp1: The VSP1 device
 * @num_bodies: The number of bodies to allocate
 * @num_entries: The maximum number of entries that a body can contain
 * @extra_size: Extra allocation provided क्रम the bodies
 *
 * Allocate a pool of display list bodies each with enough memory to contain the
 * requested number of entries plus the @extra_size.
 *
 * Return a poपूर्णांकer to a pool on success or शून्य अगर memory can't be allocated.
 */
काष्ठा vsp1_dl_body_pool *
vsp1_dl_body_pool_create(काष्ठा vsp1_device *vsp1, अचिन्हित पूर्णांक num_bodies,
			 अचिन्हित पूर्णांक num_entries, माप_प्रकार extra_size)
अणु
	काष्ठा vsp1_dl_body_pool *pool;
	माप_प्रकार dlb_size;
	अचिन्हित पूर्णांक i;

	pool = kzalloc(माप(*pool), GFP_KERNEL);
	अगर (!pool)
		वापस शून्य;

	pool->vsp1 = vsp1;

	/*
	 * TODO: 'extra_size' is only used by vsp1_dlm_create(), to allocate
	 * extra memory क्रम the display list header. We need only one header per
	 * display list, not per display list body, thus this allocation is
	 * extraneous and should be reworked in the future.
	 */
	dlb_size = num_entries * माप(काष्ठा vsp1_dl_entry) + extra_size;
	pool->size = dlb_size * num_bodies;

	pool->bodies = kसुस्मृति(num_bodies, माप(*pool->bodies), GFP_KERNEL);
	अगर (!pool->bodies) अणु
		kमुक्त(pool);
		वापस शून्य;
	पूर्ण

	pool->mem = dma_alloc_wc(vsp1->bus_master, pool->size, &pool->dma,
				 GFP_KERNEL);
	अगर (!pool->mem) अणु
		kमुक्त(pool->bodies);
		kमुक्त(pool);
		वापस शून्य;
	पूर्ण

	spin_lock_init(&pool->lock);
	INIT_LIST_HEAD(&pool->मुक्त);

	क्रम (i = 0; i < num_bodies; ++i) अणु
		काष्ठा vsp1_dl_body *dlb = &pool->bodies[i];

		dlb->pool = pool;
		dlb->max_entries = num_entries;

		dlb->dma = pool->dma + i * dlb_size;
		dlb->entries = pool->mem + i * dlb_size;

		list_add_tail(&dlb->मुक्त, &pool->मुक्त);
	पूर्ण

	वापस pool;
पूर्ण

/**
 * vsp1_dl_body_pool_destroy - Release a body pool
 * @pool: The body pool
 *
 * Release all components of a pool allocation.
 */
व्योम vsp1_dl_body_pool_destroy(काष्ठा vsp1_dl_body_pool *pool)
अणु
	अगर (!pool)
		वापस;

	अगर (pool->mem)
		dma_मुक्त_wc(pool->vsp1->bus_master, pool->size, pool->mem,
			    pool->dma);

	kमुक्त(pool->bodies);
	kमुक्त(pool);
पूर्ण

/**
 * vsp1_dl_body_get - Obtain a body from a pool
 * @pool: The body pool
 *
 * Obtain a body from the pool without blocking.
 *
 * Returns a display list body or शून्य अगर there are none available.
 */
काष्ठा vsp1_dl_body *vsp1_dl_body_get(काष्ठा vsp1_dl_body_pool *pool)
अणु
	काष्ठा vsp1_dl_body *dlb = शून्य;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pool->lock, flags);

	अगर (!list_empty(&pool->मुक्त)) अणु
		dlb = list_first_entry(&pool->मुक्त, काष्ठा vsp1_dl_body, मुक्त);
		list_del(&dlb->मुक्त);
		refcount_set(&dlb->refcnt, 1);
	पूर्ण

	spin_unlock_irqrestore(&pool->lock, flags);

	वापस dlb;
पूर्ण

/**
 * vsp1_dl_body_put - Return a body back to its pool
 * @dlb: The display list body
 *
 * Return a body back to the pool, and reset the num_entries to clear the list.
 */
व्योम vsp1_dl_body_put(काष्ठा vsp1_dl_body *dlb)
अणु
	अचिन्हित दीर्घ flags;

	अगर (!dlb)
		वापस;

	अगर (!refcount_dec_and_test(&dlb->refcnt))
		वापस;

	dlb->num_entries = 0;

	spin_lock_irqsave(&dlb->pool->lock, flags);
	list_add_tail(&dlb->मुक्त, &dlb->pool->मुक्त);
	spin_unlock_irqrestore(&dlb->pool->lock, flags);
पूर्ण

/**
 * vsp1_dl_body_ग_लिखो - Write a रेजिस्टर to a display list body
 * @dlb: The body
 * @reg: The रेजिस्टर address
 * @data: The रेजिस्टर value
 *
 * Write the given रेजिस्टर and value to the display list body. The maximum
 * number of entries that can be written in a body is specअगरied when the body is
 * allocated by vsp1_dl_body_alloc().
 */
व्योम vsp1_dl_body_ग_लिखो(काष्ठा vsp1_dl_body *dlb, u32 reg, u32 data)
अणु
	अगर (WARN_ONCE(dlb->num_entries >= dlb->max_entries,
		      "DLB size exceeded (max %u)", dlb->max_entries))
		वापस;

	dlb->entries[dlb->num_entries].addr = reg;
	dlb->entries[dlb->num_entries].data = data;
	dlb->num_entries++;
पूर्ण

/* -----------------------------------------------------------------------------
 * Display List Extended Command Management
 */

क्रमागत vsp1_extcmd_type अणु
	VSP1_EXTCMD_AUTODISP,
	VSP1_EXTCMD_AUTOFLD,
पूर्ण;

काष्ठा vsp1_extended_command_info अणु
	u16 opcode;
	माप_प्रकार body_size;
पूर्ण;

अटल स्थिर काष्ठा vsp1_extended_command_info vsp1_extended_commands[] = अणु
	[VSP1_EXTCMD_AUTODISP] = अणु 0x02, 96 पूर्ण,
	[VSP1_EXTCMD_AUTOFLD]  = अणु 0x03, 160 पूर्ण,
पूर्ण;

/**
 * vsp1_dl_cmd_pool_create - Create a pool of commands from a single allocation
 * @vsp1: The VSP1 device
 * @type: The command pool type
 * @num_cmds: The number of commands to allocate
 *
 * Allocate a pool of commands each with enough memory to contain the निजी
 * data of each command. The allocation sizes are dependent upon the command
 * type.
 *
 * Return a poपूर्णांकer to the pool on success or शून्य अगर memory can't be allocated.
 */
अटल काष्ठा vsp1_dl_cmd_pool *
vsp1_dl_cmd_pool_create(काष्ठा vsp1_device *vsp1, क्रमागत vsp1_extcmd_type type,
			अचिन्हित पूर्णांक num_cmds)
अणु
	काष्ठा vsp1_dl_cmd_pool *pool;
	अचिन्हित पूर्णांक i;
	माप_प्रकार cmd_size;

	pool = kzalloc(माप(*pool), GFP_KERNEL);
	अगर (!pool)
		वापस शून्य;

	pool->vsp1 = vsp1;

	spin_lock_init(&pool->lock);
	INIT_LIST_HEAD(&pool->मुक्त);

	pool->cmds = kसुस्मृति(num_cmds, माप(*pool->cmds), GFP_KERNEL);
	अगर (!pool->cmds) अणु
		kमुक्त(pool);
		वापस शून्य;
	पूर्ण

	cmd_size = माप(काष्ठा vsp1_pre_ext_dl_body) +
		   vsp1_extended_commands[type].body_size;
	cmd_size = ALIGN(cmd_size, 16);

	pool->size = cmd_size * num_cmds;
	pool->mem = dma_alloc_wc(vsp1->bus_master, pool->size, &pool->dma,
				 GFP_KERNEL);
	अगर (!pool->mem) अणु
		kमुक्त(pool->cmds);
		kमुक्त(pool);
		वापस शून्य;
	पूर्ण

	क्रम (i = 0; i < num_cmds; ++i) अणु
		काष्ठा vsp1_dl_ext_cmd *cmd = &pool->cmds[i];
		माप_प्रकार cmd_offset = i * cmd_size;
		/* data_offset must be 16 byte aligned क्रम DMA. */
		माप_प्रकार data_offset = माप(काष्ठा vsp1_pre_ext_dl_body) +
				     cmd_offset;

		cmd->pool = pool;
		cmd->opcode = vsp1_extended_commands[type].opcode;

		/*
		 * TODO: Auto-disp can utilise more than one extended body
		 * command per cmd.
		 */
		cmd->num_cmds = 1;
		cmd->cmds = pool->mem + cmd_offset;
		cmd->cmd_dma = pool->dma + cmd_offset;

		cmd->data = pool->mem + data_offset;
		cmd->data_dma = pool->dma + data_offset;

		list_add_tail(&cmd->मुक्त, &pool->मुक्त);
	पूर्ण

	वापस pool;
पूर्ण

अटल
काष्ठा vsp1_dl_ext_cmd *vsp1_dl_ext_cmd_get(काष्ठा vsp1_dl_cmd_pool *pool)
अणु
	काष्ठा vsp1_dl_ext_cmd *cmd = शून्य;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pool->lock, flags);

	अगर (!list_empty(&pool->मुक्त)) अणु
		cmd = list_first_entry(&pool->मुक्त, काष्ठा vsp1_dl_ext_cmd,
				       मुक्त);
		list_del(&cmd->मुक्त);
	पूर्ण

	spin_unlock_irqrestore(&pool->lock, flags);

	वापस cmd;
पूर्ण

अटल व्योम vsp1_dl_ext_cmd_put(काष्ठा vsp1_dl_ext_cmd *cmd)
अणु
	अचिन्हित दीर्घ flags;

	अगर (!cmd)
		वापस;

	/* Reset flags, these mark data usage. */
	cmd->flags = 0;

	spin_lock_irqsave(&cmd->pool->lock, flags);
	list_add_tail(&cmd->मुक्त, &cmd->pool->मुक्त);
	spin_unlock_irqrestore(&cmd->pool->lock, flags);
पूर्ण

अटल व्योम vsp1_dl_ext_cmd_pool_destroy(काष्ठा vsp1_dl_cmd_pool *pool)
अणु
	अगर (!pool)
		वापस;

	अगर (pool->mem)
		dma_मुक्त_wc(pool->vsp1->bus_master, pool->size, pool->mem,
			    pool->dma);

	kमुक्त(pool->cmds);
	kमुक्त(pool);
पूर्ण

काष्ठा vsp1_dl_ext_cmd *vsp1_dl_get_pre_cmd(काष्ठा vsp1_dl_list *dl)
अणु
	काष्ठा vsp1_dl_manager *dlm = dl->dlm;

	अगर (dl->pre_cmd)
		वापस dl->pre_cmd;

	dl->pre_cmd = vsp1_dl_ext_cmd_get(dlm->cmdpool);

	वापस dl->pre_cmd;
पूर्ण

/* ----------------------------------------------------------------------------
 * Display List Transaction Management
 */

अटल काष्ठा vsp1_dl_list *vsp1_dl_list_alloc(काष्ठा vsp1_dl_manager *dlm)
अणु
	काष्ठा vsp1_dl_list *dl;
	माप_प्रकार header_offset;

	dl = kzalloc(माप(*dl), GFP_KERNEL);
	अगर (!dl)
		वापस शून्य;

	INIT_LIST_HEAD(&dl->bodies);
	dl->dlm = dlm;

	/* Get a शेष body क्रम our list. */
	dl->body0 = vsp1_dl_body_get(dlm->pool);
	अगर (!dl->body0) अणु
		kमुक्त(dl);
		वापस शून्य;
	पूर्ण

	header_offset = dl->body0->max_entries * माप(*dl->body0->entries);

	dl->header = ((व्योम *)dl->body0->entries) + header_offset;
	dl->dma = dl->body0->dma + header_offset;

	स_रखो(dl->header, 0, माप(*dl->header));
	dl->header->lists[0].addr = dl->body0->dma;

	वापस dl;
पूर्ण

अटल व्योम vsp1_dl_list_bodies_put(काष्ठा vsp1_dl_list *dl)
अणु
	काष्ठा vsp1_dl_body *dlb, *पंचांगp;

	list_क्रम_each_entry_safe(dlb, पंचांगp, &dl->bodies, list) अणु
		list_del(&dlb->list);
		vsp1_dl_body_put(dlb);
	पूर्ण
पूर्ण

अटल व्योम vsp1_dl_list_मुक्त(काष्ठा vsp1_dl_list *dl)
अणु
	vsp1_dl_body_put(dl->body0);
	vsp1_dl_list_bodies_put(dl);

	kमुक्त(dl);
पूर्ण

/**
 * vsp1_dl_list_get - Get a मुक्त display list
 * @dlm: The display list manager
 *
 * Get a display list from the pool of मुक्त lists and वापस it.
 *
 * This function must be called without the display list manager lock held.
 */
काष्ठा vsp1_dl_list *vsp1_dl_list_get(काष्ठा vsp1_dl_manager *dlm)
अणु
	काष्ठा vsp1_dl_list *dl = शून्य;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dlm->lock, flags);

	अगर (!list_empty(&dlm->मुक्त)) अणु
		dl = list_first_entry(&dlm->मुक्त, काष्ठा vsp1_dl_list, list);
		list_del(&dl->list);

		/*
		 * The display list chain must be initialised to ensure every
		 * display list can निश्चित list_empty() अगर it is not in a chain.
		 */
		INIT_LIST_HEAD(&dl->chain);
	पूर्ण

	spin_unlock_irqrestore(&dlm->lock, flags);

	वापस dl;
पूर्ण

/* This function must be called with the display list manager lock held.*/
अटल व्योम __vsp1_dl_list_put(काष्ठा vsp1_dl_list *dl)
अणु
	काष्ठा vsp1_dl_list *dl_next;

	अगर (!dl)
		वापस;

	/*
	 * Release any linked display-lists which were chained क्रम a single
	 * hardware operation.
	 */
	अगर (dl->has_chain) अणु
		list_क्रम_each_entry(dl_next, &dl->chain, chain)
			__vsp1_dl_list_put(dl_next);
	पूर्ण

	dl->has_chain = false;

	vsp1_dl_list_bodies_put(dl);

	vsp1_dl_ext_cmd_put(dl->pre_cmd);
	vsp1_dl_ext_cmd_put(dl->post_cmd);

	dl->pre_cmd = शून्य;
	dl->post_cmd = शून्य;

	/*
	 * body0 is reused as as an optimisation as presently every display list
	 * has at least one body, thus we reinitialise the entries list.
	 */
	dl->body0->num_entries = 0;

	list_add_tail(&dl->list, &dl->dlm->मुक्त);
पूर्ण

/**
 * vsp1_dl_list_put - Release a display list
 * @dl: The display list
 *
 * Release the display list and वापस it to the pool of मुक्त lists.
 *
 * Passing a शून्य poपूर्णांकer to this function is safe, in that हाल no operation
 * will be perक्रमmed.
 */
व्योम vsp1_dl_list_put(काष्ठा vsp1_dl_list *dl)
अणु
	अचिन्हित दीर्घ flags;

	अगर (!dl)
		वापस;

	spin_lock_irqsave(&dl->dlm->lock, flags);
	__vsp1_dl_list_put(dl);
	spin_unlock_irqrestore(&dl->dlm->lock, flags);
पूर्ण

/**
 * vsp1_dl_list_get_body0 - Obtain the शेष body क्रम the display list
 * @dl: The display list
 *
 * Obtain a poपूर्णांकer to the पूर्णांकernal display list body allowing this to be passed
 * directly to configure operations.
 */
काष्ठा vsp1_dl_body *vsp1_dl_list_get_body0(काष्ठा vsp1_dl_list *dl)
अणु
	वापस dl->body0;
पूर्ण

/**
 * vsp1_dl_list_add_body - Add a body to the display list
 * @dl: The display list
 * @dlb: The body
 *
 * Add a display list body to a display list. Registers contained in bodies are
 * processed after रेजिस्टरs contained in the मुख्य display list, in the order in
 * which bodies are added.
 *
 * Adding a body to a display list passes ownership of the body to the list. The
 * caller retains its reference to the body when adding it to the display list,
 * but is not allowed to add new entries to the body.
 *
 * The reference must be explicitly released by a call to vsp1_dl_body_put()
 * when the body isn't needed anymore.
 */
पूर्णांक vsp1_dl_list_add_body(काष्ठा vsp1_dl_list *dl, काष्ठा vsp1_dl_body *dlb)
अणु
	refcount_inc(&dlb->refcnt);

	list_add_tail(&dlb->list, &dl->bodies);

	वापस 0;
पूर्ण

/**
 * vsp1_dl_list_add_chain - Add a display list to a chain
 * @head: The head display list
 * @dl: The new display list
 *
 * Add a display list to an existing display list chain. The chained lists
 * will be स्वतःmatically processed by the hardware without पूर्णांकervention from
 * the CPU. A display list end पूर्णांकerrupt will only complete after the last
 * display list in the chain has completed processing.
 *
 * Adding a display list to a chain passes ownership of the display list to
 * the head display list item. The chain is released when the head dl item is
 * put back with __vsp1_dl_list_put().
 */
पूर्णांक vsp1_dl_list_add_chain(काष्ठा vsp1_dl_list *head,
			   काष्ठा vsp1_dl_list *dl)
अणु
	head->has_chain = true;
	list_add_tail(&dl->chain, &head->chain);
	वापस 0;
पूर्ण

अटल व्योम vsp1_dl_ext_cmd_fill_header(काष्ठा vsp1_dl_ext_cmd *cmd)
अणु
	cmd->cmds[0].opcode = cmd->opcode;
	cmd->cmds[0].flags = cmd->flags;
	cmd->cmds[0].address_set = cmd->data_dma;
	cmd->cmds[0].reserved = 0;
पूर्ण

अटल व्योम vsp1_dl_list_fill_header(काष्ठा vsp1_dl_list *dl, bool is_last)
अणु
	काष्ठा vsp1_dl_manager *dlm = dl->dlm;
	काष्ठा vsp1_dl_header_list *hdr = dl->header->lists;
	काष्ठा vsp1_dl_body *dlb;
	अचिन्हित पूर्णांक num_lists = 0;

	/*
	 * Fill the header with the display list bodies addresses and sizes. The
	 * address of the first body has alपढ़ोy been filled when the display
	 * list was allocated.
	 */

	hdr->num_bytes = dl->body0->num_entries
		       * माप(*dl->header->lists);

	list_क्रम_each_entry(dlb, &dl->bodies, list) अणु
		num_lists++;
		hdr++;

		hdr->addr = dlb->dma;
		hdr->num_bytes = dlb->num_entries
			       * माप(*dl->header->lists);
	पूर्ण

	dl->header->num_lists = num_lists;
	dl->header->flags = 0;

	/*
	 * Enable the पूर्णांकerrupt क्रम the end of each frame. In continuous mode
	 * chained lists are used with one list per frame, so enable the
	 * पूर्णांकerrupt क्रम each list. In singleshot mode chained lists are used
	 * to partition a single frame, so enable the पूर्णांकerrupt क्रम the last
	 * list only.
	 */
	अगर (!dlm->singleshot || is_last)
		dl->header->flags |= VSP1_DLH_INT_ENABLE;

	/*
	 * In continuous mode enable स्वतः-start क्रम all lists, as the VSP must
	 * loop on the same list until a new one is queued. In singleshot mode
	 * enable स्वतः-start क्रम all lists but the last to chain processing of
	 * partitions without software पूर्णांकervention.
	 */
	अगर (!dlm->singleshot || !is_last)
		dl->header->flags |= VSP1_DLH_AUTO_START;

	अगर (!is_last) अणु
		/*
		 * If this is not the last display list in the chain, queue the
		 * next item क्रम स्वतःmatic processing by the hardware.
		 */
		काष्ठा vsp1_dl_list *next = list_next_entry(dl, chain);

		dl->header->next_header = next->dma;
	पूर्ण अन्यथा अगर (!dlm->singleshot) अणु
		/*
		 * अगर the display list manager works in continuous mode, the VSP
		 * should loop over the display list continuously until
		 * inकाष्ठाed to करो otherwise.
		 */
		dl->header->next_header = dl->dma;
	पूर्ण

	अगर (!dl->extension)
		वापस;

	dl->extension->flags = 0;

	अगर (dl->pre_cmd) अणु
		dl->extension->pre_ext_dl_plist = dl->pre_cmd->cmd_dma;
		dl->extension->pre_ext_dl_num_cmd = dl->pre_cmd->num_cmds;
		dl->extension->flags |= VSP1_DLH_EXT_PRE_CMD_EXEC;

		vsp1_dl_ext_cmd_fill_header(dl->pre_cmd);
	पूर्ण

	अगर (dl->post_cmd) अणु
		dl->extension->post_ext_dl_plist = dl->post_cmd->cmd_dma;
		dl->extension->post_ext_dl_num_cmd = dl->post_cmd->num_cmds;
		dl->extension->flags |= VSP1_DLH_EXT_POST_CMD_EXEC;

		vsp1_dl_ext_cmd_fill_header(dl->post_cmd);
	पूर्ण
पूर्ण

अटल bool vsp1_dl_list_hw_update_pending(काष्ठा vsp1_dl_manager *dlm)
अणु
	काष्ठा vsp1_device *vsp1 = dlm->vsp1;

	अगर (!dlm->queued)
		वापस false;

	/*
	 * Check whether the VSP1 has taken the update. The hardware indicates
	 * this by clearing the UPDHDR bit in the CMD रेजिस्टर.
	 */
	वापस !!(vsp1_पढ़ो(vsp1, VI6_CMD(dlm->index)) & VI6_CMD_UPDHDR);
पूर्ण

अटल व्योम vsp1_dl_list_hw_enqueue(काष्ठा vsp1_dl_list *dl)
अणु
	काष्ठा vsp1_dl_manager *dlm = dl->dlm;
	काष्ठा vsp1_device *vsp1 = dlm->vsp1;

	/*
	 * Program the display list header address. If the hardware is idle
	 * (single-shot mode or first frame in continuous mode) it will then be
	 * started independently. If the hardware is operating, the
	 * VI6_DL_HDR_REF_ADDR रेजिस्टर will be updated with the display list
	 * address.
	 */
	vsp1_ग_लिखो(vsp1, VI6_DL_HDR_ADDR(dlm->index), dl->dma);
पूर्ण

अटल व्योम vsp1_dl_list_commit_continuous(काष्ठा vsp1_dl_list *dl)
अणु
	काष्ठा vsp1_dl_manager *dlm = dl->dlm;

	/*
	 * If a previous display list has been queued to the hardware but not
	 * processed yet, the VSP can start processing it at any समय. In that
	 * हाल we can't replace the queued list by the new one, as we could
	 * race with the hardware. We thus mark the update as pending, it will
	 * be queued up to the hardware by the frame end पूर्णांकerrupt handler.
	 *
	 * If a display list is alपढ़ोy pending we simply drop it as the new
	 * display list is assumed to contain a more recent configuration. It is
	 * an error अगर the alपढ़ोy pending list has the
	 * VSP1_DL_FRAME_END_INTERNAL flag set, as there is then a process
	 * रुकोing क्रम that list to complete. This shouldn't happen as the
	 * रुकोing process should perक्रमm proper locking, but warn just in
	 * हाल.
	 */
	अगर (vsp1_dl_list_hw_update_pending(dlm)) अणु
		WARN_ON(dlm->pending &&
			(dlm->pending->flags & VSP1_DL_FRAME_END_INTERNAL));
		__vsp1_dl_list_put(dlm->pending);
		dlm->pending = dl;
		वापस;
	पूर्ण

	/*
	 * Pass the new display list to the hardware and mark it as queued. It
	 * will become active when the hardware starts processing it.
	 */
	vsp1_dl_list_hw_enqueue(dl);

	__vsp1_dl_list_put(dlm->queued);
	dlm->queued = dl;
पूर्ण

अटल व्योम vsp1_dl_list_commit_singleshot(काष्ठा vsp1_dl_list *dl)
अणु
	काष्ठा vsp1_dl_manager *dlm = dl->dlm;

	/*
	 * When working in single-shot mode, the caller guarantees that the
	 * hardware is idle at this poपूर्णांक. Just commit the head display list
	 * to hardware. Chained lists will be started स्वतःmatically.
	 */
	vsp1_dl_list_hw_enqueue(dl);

	dlm->active = dl;
पूर्ण

व्योम vsp1_dl_list_commit(काष्ठा vsp1_dl_list *dl, अचिन्हित पूर्णांक dl_flags)
अणु
	काष्ठा vsp1_dl_manager *dlm = dl->dlm;
	काष्ठा vsp1_dl_list *dl_next;
	अचिन्हित दीर्घ flags;

	/* Fill the header क्रम the head and chained display lists. */
	vsp1_dl_list_fill_header(dl, list_empty(&dl->chain));

	list_क्रम_each_entry(dl_next, &dl->chain, chain) अणु
		bool last = list_is_last(&dl_next->chain, &dl->chain);

		vsp1_dl_list_fill_header(dl_next, last);
	पूर्ण

	dl->flags = dl_flags & ~VSP1_DL_FRAME_END_COMPLETED;

	spin_lock_irqsave(&dlm->lock, flags);

	अगर (dlm->singleshot)
		vsp1_dl_list_commit_singleshot(dl);
	अन्यथा
		vsp1_dl_list_commit_continuous(dl);

	spin_unlock_irqrestore(&dlm->lock, flags);
पूर्ण

/* -----------------------------------------------------------------------------
 * Display List Manager
 */

/**
 * vsp1_dlm_irq_frame_end - Display list handler क्रम the frame end पूर्णांकerrupt
 * @dlm: the display list manager
 *
 * Return a set of flags that indicates display list completion status.
 *
 * The VSP1_DL_FRAME_END_COMPLETED flag indicates that the previous display list
 * has completed at frame end. If the flag is not वापसed display list
 * completion has been delayed by one frame because the display list commit
 * raced with the frame end पूर्णांकerrupt. The function always वापसs with the flag
 * set in single-shot mode as display list processing is then not continuous and
 * races never occur.
 *
 * The following flags are only supported क्रम continuous mode.
 *
 * The VSP1_DL_FRAME_END_INTERNAL flag indicates that the display list that just
 * became active had been queued with the पूर्णांकernal notअगरication flag.
 *
 * The VSP1_DL_FRAME_END_WRITEBACK flag indicates that the previously active
 * display list had been queued with the ग_लिखोback flag.
 */
अचिन्हित पूर्णांक vsp1_dlm_irq_frame_end(काष्ठा vsp1_dl_manager *dlm)
अणु
	काष्ठा vsp1_device *vsp1 = dlm->vsp1;
	u32 status = vsp1_पढ़ो(vsp1, VI6_STATUS);
	अचिन्हित पूर्णांक flags = 0;

	spin_lock(&dlm->lock);

	/*
	 * The mem-to-mem pipelines work in single-shot mode. No new display
	 * list can be queued, we करोn't have to करो anything.
	 */
	अगर (dlm->singleshot) अणु
		__vsp1_dl_list_put(dlm->active);
		dlm->active = शून्य;
		flags |= VSP1_DL_FRAME_END_COMPLETED;
		जाओ करोne;
	पूर्ण

	/*
	 * If the commit operation raced with the पूर्णांकerrupt and occurred after
	 * the frame end event but beक्रमe पूर्णांकerrupt processing, the hardware
	 * hasn't taken the update पूर्णांकo account yet. We have to skip one frame
	 * and retry.
	 */
	अगर (vsp1_dl_list_hw_update_pending(dlm))
		जाओ करोne;

	/*
	 * Progressive streams report only TOP fields. If we have a BOTTOM
	 * field, we are पूर्णांकerlaced, and expect the frame to complete on the
	 * next frame end पूर्णांकerrupt.
	 */
	अगर (status & VI6_STATUS_FLD_STD(dlm->index))
		जाओ करोne;

	/*
	 * If the active display list has the ग_लिखोback flag set, the frame
	 * completion marks the end of the ग_लिखोback capture. Return the
	 * VSP1_DL_FRAME_END_WRITEBACK flag and reset the display list's
	 * ग_लिखोback flag.
	 */
	अगर (dlm->active && (dlm->active->flags & VSP1_DL_FRAME_END_WRITEBACK)) अणु
		flags |= VSP1_DL_FRAME_END_WRITEBACK;
		dlm->active->flags &= ~VSP1_DL_FRAME_END_WRITEBACK;
	पूर्ण

	/*
	 * The device starts processing the queued display list right after the
	 * frame end पूर्णांकerrupt. The display list thus becomes active.
	 */
	अगर (dlm->queued) अणु
		अगर (dlm->queued->flags & VSP1_DL_FRAME_END_INTERNAL)
			flags |= VSP1_DL_FRAME_END_INTERNAL;
		dlm->queued->flags &= ~VSP1_DL_FRAME_END_INTERNAL;

		__vsp1_dl_list_put(dlm->active);
		dlm->active = dlm->queued;
		dlm->queued = शून्य;
		flags |= VSP1_DL_FRAME_END_COMPLETED;
	पूर्ण

	/*
	 * Now that the VSP has started processing the queued display list, we
	 * can queue the pending display list to the hardware अगर one has been
	 * prepared.
	 */
	अगर (dlm->pending) अणु
		vsp1_dl_list_hw_enqueue(dlm->pending);
		dlm->queued = dlm->pending;
		dlm->pending = शून्य;
	पूर्ण

करोne:
	spin_unlock(&dlm->lock);

	वापस flags;
पूर्ण

/* Hardware Setup */
व्योम vsp1_dlm_setup(काष्ठा vsp1_device *vsp1)
अणु
	अचिन्हित पूर्णांक i;
	u32 ctrl = (256 << VI6_DL_CTRL_AR_WAIT_SHIFT)
		 | VI6_DL_CTRL_DC2 | VI6_DL_CTRL_DC1 | VI6_DL_CTRL_DC0
		 | VI6_DL_CTRL_DLE;
	u32 ext_dl = (0x02 << VI6_DL_EXT_CTRL_POLINT_SHIFT)
		   | VI6_DL_EXT_CTRL_DLPRI | VI6_DL_EXT_CTRL_EXT;

	अगर (vsp1_feature(vsp1, VSP1_HAS_EXT_DL)) अणु
		क्रम (i = 0; i < vsp1->info->wpf_count; ++i)
			vsp1_ग_लिखो(vsp1, VI6_DL_EXT_CTRL(i), ext_dl);
	पूर्ण

	vsp1_ग_लिखो(vsp1, VI6_DL_CTRL, ctrl);
	vsp1_ग_लिखो(vsp1, VI6_DL_SWAP, VI6_DL_SWAP_LWS);
पूर्ण

व्योम vsp1_dlm_reset(काष्ठा vsp1_dl_manager *dlm)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dlm->lock, flags);

	__vsp1_dl_list_put(dlm->active);
	__vsp1_dl_list_put(dlm->queued);
	__vsp1_dl_list_put(dlm->pending);

	spin_unlock_irqrestore(&dlm->lock, flags);

	dlm->active = शून्य;
	dlm->queued = शून्य;
	dlm->pending = शून्य;
पूर्ण

काष्ठा vsp1_dl_body *vsp1_dlm_dl_body_get(काष्ठा vsp1_dl_manager *dlm)
अणु
	वापस vsp1_dl_body_get(dlm->pool);
पूर्ण

काष्ठा vsp1_dl_manager *vsp1_dlm_create(काष्ठा vsp1_device *vsp1,
					अचिन्हित पूर्णांक index,
					अचिन्हित पूर्णांक pपुनः_स्मृति)
अणु
	काष्ठा vsp1_dl_manager *dlm;
	माप_प्रकार header_size;
	अचिन्हित पूर्णांक i;

	dlm = devm_kzalloc(vsp1->dev, माप(*dlm), GFP_KERNEL);
	अगर (!dlm)
		वापस शून्य;

	dlm->index = index;
	dlm->singleshot = vsp1->info->uapi;
	dlm->vsp1 = vsp1;

	spin_lock_init(&dlm->lock);
	INIT_LIST_HEAD(&dlm->मुक्त);

	/*
	 * Initialize the display list body and allocate DMA memory क्रम the body
	 * and the header. Both are allocated together to aव्योम memory
	 * fragmentation, with the header located right after the body in
	 * memory. An extra body is allocated on top of the pपुनः_स्मृति to account
	 * क्रम the cached body used by the vsp1_pipeline object.
	 */
	header_size = vsp1_feature(vsp1, VSP1_HAS_EXT_DL) ?
			माप(काष्ठा vsp1_dl_header_extended) :
			माप(काष्ठा vsp1_dl_header);

	header_size = ALIGN(header_size, 8);

	dlm->pool = vsp1_dl_body_pool_create(vsp1, pपुनः_स्मृति + 1,
					     VSP1_DL_NUM_ENTRIES, header_size);
	अगर (!dlm->pool)
		वापस शून्य;

	क्रम (i = 0; i < pपुनः_स्मृति; ++i) अणु
		काष्ठा vsp1_dl_list *dl;

		dl = vsp1_dl_list_alloc(dlm);
		अगर (!dl) अणु
			vsp1_dlm_destroy(dlm);
			वापस शून्य;
		पूर्ण

		/* The extended header immediately follows the header. */
		अगर (vsp1_feature(vsp1, VSP1_HAS_EXT_DL))
			dl->extension = (व्योम *)dl->header
				      + माप(*dl->header);

		list_add_tail(&dl->list, &dlm->मुक्त);
	पूर्ण

	अगर (vsp1_feature(vsp1, VSP1_HAS_EXT_DL)) अणु
		dlm->cmdpool = vsp1_dl_cmd_pool_create(vsp1,
					VSP1_EXTCMD_AUTOFLD, pपुनः_स्मृति);
		अगर (!dlm->cmdpool) अणु
			vsp1_dlm_destroy(dlm);
			वापस शून्य;
		पूर्ण
	पूर्ण

	वापस dlm;
पूर्ण

व्योम vsp1_dlm_destroy(काष्ठा vsp1_dl_manager *dlm)
अणु
	काष्ठा vsp1_dl_list *dl, *next;

	अगर (!dlm)
		वापस;

	list_क्रम_each_entry_safe(dl, next, &dlm->मुक्त, list) अणु
		list_del(&dl->list);
		vsp1_dl_list_मुक्त(dl);
	पूर्ण

	vsp1_dl_body_pool_destroy(dlm->pool);
	vsp1_dl_ext_cmd_pool_destroy(dlm->cmdpool);
पूर्ण
