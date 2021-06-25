<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright(c) 2004 - 2006 Intel Corporation. All rights reserved.
 */
#अगर_अघोषित LINUX_DMAENGINE_H
#घोषणा LINUX_DMAENGINE_H

#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/uपन.स>
#समावेश <linux/bug.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/types.h>
#समावेश <यंत्र/page.h>

/**
 * प्रकार dma_cookie_t - an opaque DMA cookie
 *
 * अगर dma_cookie_t is >0 it's a DMA request cookie, <0 it's an error code
 */
प्रकार s32 dma_cookie_t;
#घोषणा DMA_MIN_COOKIE	1

अटल अंतरभूत पूर्णांक dma_submit_error(dma_cookie_t cookie)
अणु
	वापस cookie < 0 ? cookie : 0;
पूर्ण

/**
 * क्रमागत dma_status - DMA transaction status
 * @DMA_COMPLETE: transaction completed
 * @DMA_IN_PROGRESS: transaction not yet processed
 * @DMA_PAUSED: transaction is छोड़ोd
 * @DMA_ERROR: transaction failed
 */
क्रमागत dma_status अणु
	DMA_COMPLETE,
	DMA_IN_PROGRESS,
	DMA_PAUSED,
	DMA_ERROR,
	DMA_OUT_OF_ORDER,
पूर्ण;

/**
 * क्रमागत dma_transaction_type - DMA transaction types/indexes
 *
 * Note: The DMA_ASYNC_TX capability is not to be set by drivers.  It is
 * स्वतःmatically set as dma devices are रेजिस्टरed.
 */
क्रमागत dma_transaction_type अणु
	DMA_MEMCPY,
	DMA_XOR,
	DMA_PQ,
	DMA_XOR_VAL,
	DMA_PQ_VAL,
	DMA_MEMSET,
	DMA_MEMSET_SG,
	DMA_INTERRUPT,
	DMA_PRIVATE,
	DMA_ASYNC_TX,
	DMA_SLAVE,
	DMA_CYCLIC,
	DMA_INTERLEAVE,
	DMA_COMPLETION_NO_ORDER,
	DMA_REPEAT,
	DMA_LOAD_EOT,
/* last transaction type क्रम creation of the capabilities mask */
	DMA_TX_TYPE_END,
पूर्ण;

/**
 * क्रमागत dma_transfer_direction - dma transfer mode and direction indicator
 * @DMA_MEM_TO_MEM: Async/Memcpy mode
 * @DMA_MEM_TO_DEV: Slave mode & From Memory to Device
 * @DMA_DEV_TO_MEM: Slave mode & From Device to Memory
 * @DMA_DEV_TO_DEV: Slave mode & From Device to Device
 */
क्रमागत dma_transfer_direction अणु
	DMA_MEM_TO_MEM,
	DMA_MEM_TO_DEV,
	DMA_DEV_TO_MEM,
	DMA_DEV_TO_DEV,
	DMA_TRANS_NONE,
पूर्ण;

/**
 * Interleaved Transfer Request
 * ----------------------------
 * A chunk is collection of contiguous bytes to be transferred.
 * The gap(in bytes) between two chunks is called पूर्णांकer-chunk-gap(ICG).
 * ICGs may or may not change between chunks.
 * A FRAME is the smallest series of contiguous अणुchunk,icgपूर्ण pairs,
 *  that when repeated an पूर्णांकegral number of बार, specअगरies the transfer.
 * A transfer ढाँचा is specअगरication of a Frame, the number of बार
 *  it is to be repeated and other per-transfer attributes.
 *
 * Practically, a client driver would have पढ़ोy a ढाँचा क्रम each
 *  type of transfer it is going to need during its lअगरeसमय and
 *  set only 'src_start' and 'dst_start' beक्रमe submitting the requests.
 *
 *
 *  |      Frame-1        |       Frame-2       | ~ |       Frame-'numf'  |
 *  |====....==.===...=...|====....==.===...=...| ~ |====....==.===...=...|
 *
 *    ==  Chunk size
 *    ... ICG
 */

/**
 * काष्ठा data_chunk - Element of scatter-gather list that makes a frame.
 * @size: Number of bytes to पढ़ो from source.
 *	  size_dst := fn(op, size_src), so करोesn't mean much क्रम destination.
 * @icg: Number of bytes to jump after last src/dst address of this
 *	 chunk and beक्रमe first src/dst address क्रम next chunk.
 *	 Ignored क्रम dst(assumed 0), अगर dst_inc is true and dst_sgl is false.
 *	 Ignored क्रम src(assumed 0), अगर src_inc is true and src_sgl is false.
 * @dst_icg: Number of bytes to jump after last dst address of this
 *	 chunk and beक्रमe the first dst address क्रम next chunk.
 *	 Ignored अगर dst_inc is true and dst_sgl is false.
 * @src_icg: Number of bytes to jump after last src address of this
 *	 chunk and beक्रमe the first src address क्रम next chunk.
 *	 Ignored अगर src_inc is true and src_sgl is false.
 */
काष्ठा data_chunk अणु
	माप_प्रकार size;
	माप_प्रकार icg;
	माप_प्रकार dst_icg;
	माप_प्रकार src_icg;
पूर्ण;

/**
 * काष्ठा dma_पूर्णांकerleaved_ढाँचा - Template to convey DMAC the transfer pattern
 *	 and attributes.
 * @src_start: Bus address of source क्रम the first chunk.
 * @dst_start: Bus address of destination क्रम the first chunk.
 * @dir: Specअगरies the type of Source and Destination.
 * @src_inc: If the source address increments after पढ़ोing from it.
 * @dst_inc: If the destination address increments after writing to it.
 * @src_sgl: If the 'icg' of sgl[] applies to Source (scattered पढ़ो).
 *		Otherwise, source is पढ़ो contiguously (icg ignored).
 *		Ignored अगर src_inc is false.
 * @dst_sgl: If the 'icg' of sgl[] applies to Destination (scattered ग_लिखो).
 *		Otherwise, destination is filled contiguously (icg ignored).
 *		Ignored अगर dst_inc is false.
 * @numf: Number of frames in this ढाँचा.
 * @frame_size: Number of chunks in a frame i.e, size of sgl[].
 * @sgl: Array of अणुchunk,icgपूर्ण pairs that make up a frame.
 */
काष्ठा dma_पूर्णांकerleaved_ढाँचा अणु
	dma_addr_t src_start;
	dma_addr_t dst_start;
	क्रमागत dma_transfer_direction dir;
	bool src_inc;
	bool dst_inc;
	bool src_sgl;
	bool dst_sgl;
	माप_प्रकार numf;
	माप_प्रकार frame_size;
	काष्ठा data_chunk sgl[];
पूर्ण;

/**
 * क्रमागत dma_ctrl_flags - DMA flags to augment operation preparation,
 *  control completion, and communicate status.
 * @DMA_PREP_INTERRUPT - trigger an पूर्णांकerrupt (callback) upon completion of
 *  this transaction
 * @DMA_CTRL_ACK - अगर clear, the descriptor cannot be reused until the client
 *  acknowledges receipt, i.e. has a chance to establish any dependency
 *  chains
 * @DMA_PREP_PQ_DISABLE_P - prevent generation of P जबतक generating Q
 * @DMA_PREP_PQ_DISABLE_Q - prevent generation of Q जबतक generating P
 * @DMA_PREP_CONTINUE - indicate to a driver that it is reusing buffers as
 *  sources that were the result of a previous operation, in the हाल of a PQ
 *  operation it जारीs the calculation with new sources
 * @DMA_PREP_FENCE - tell the driver that subsequent operations depend
 *  on the result of this operation
 * @DMA_CTRL_REUSE: client can reuse the descriptor and submit again till
 *  cleared or मुक्तd
 * @DMA_PREP_CMD: tell the driver that the data passed to DMA API is command
 *  data and the descriptor should be in dअगरferent क्रमmat from normal
 *  data descriptors.
 * @DMA_PREP_REPEAT: tell the driver that the transaction shall be स्वतःmatically
 *  repeated when it ends until a transaction is issued on the same channel
 *  with the DMA_PREP_LOAD_EOT flag set. This flag is only applicable to
 *  पूर्णांकerleaved transactions and is ignored क्रम all other transaction types.
 * @DMA_PREP_LOAD_EOT: tell the driver that the transaction shall replace any
 *  active repeated (as indicated by DMA_PREP_REPEAT) transaction when the
 *  repeated transaction ends. Not setting this flag when the previously queued
 *  transaction is marked with DMA_PREP_REPEAT will cause the new transaction
 *  to never be processed and stay in the issued queue क्रमever. The flag is
 *  ignored अगर the previous transaction is not a repeated transaction.
 */
क्रमागत dma_ctrl_flags अणु
	DMA_PREP_INTERRUPT = (1 << 0),
	DMA_CTRL_ACK = (1 << 1),
	DMA_PREP_PQ_DISABLE_P = (1 << 2),
	DMA_PREP_PQ_DISABLE_Q = (1 << 3),
	DMA_PREP_CONTINUE = (1 << 4),
	DMA_PREP_FENCE = (1 << 5),
	DMA_CTRL_REUSE = (1 << 6),
	DMA_PREP_CMD = (1 << 7),
	DMA_PREP_REPEAT = (1 << 8),
	DMA_PREP_LOAD_EOT = (1 << 9),
पूर्ण;

/**
 * क्रमागत sum_check_bits - bit position of pq_check_flags
 */
क्रमागत sum_check_bits अणु
	SUM_CHECK_P = 0,
	SUM_CHECK_Q = 1,
पूर्ण;

/**
 * क्रमागत pq_check_flags - result of async_अणुxor,pqपूर्ण_zero_sum operations
 * @SUM_CHECK_P_RESULT - 1 अगर xor zero sum error, 0 otherwise
 * @SUM_CHECK_Q_RESULT - 1 अगर reed-solomon zero sum error, 0 otherwise
 */
क्रमागत sum_check_flags अणु
	SUM_CHECK_P_RESULT = (1 << SUM_CHECK_P),
	SUM_CHECK_Q_RESULT = (1 << SUM_CHECK_Q),
पूर्ण;


/**
 * dma_cap_mask_t - capabilities biपंचांगap modeled after cpumask_t.
 * See linux/cpumask.h
 */
प्रकार काष्ठा अणु DECLARE_BITMAP(bits, DMA_TX_TYPE_END); पूर्ण dma_cap_mask_t;

/**
 * काष्ठा dma_chan_percpu - the per-CPU part of काष्ठा dma_chan
 * @स_नकल_count: transaction counter
 * @bytes_transferred: byte counter
 */

/**
 * क्रमागत dma_desc_metadata_mode - per descriptor metadata mode types supported
 * @DESC_METADATA_CLIENT - the metadata buffer is allocated/provided by the
 *  client driver and it is attached (via the dmaengine_desc_attach_metadata()
 *  helper) to the descriptor.
 *
 * Client drivers पूर्णांकerested to use this mode can follow:
 * - DMA_MEM_TO_DEV / DEV_MEM_TO_MEM:
 *   1. prepare the descriptor (dmaengine_prep_*)
 *	स्थिरruct the metadata in the client's buffer
 *   2. use dmaengine_desc_attach_metadata() to attach the buffer to the
 *	descriptor
 *   3. submit the transfer
 * - DMA_DEV_TO_MEM:
 *   1. prepare the descriptor (dmaengine_prep_*)
 *   2. use dmaengine_desc_attach_metadata() to attach the buffer to the
 *	descriptor
 *   3. submit the transfer
 *   4. when the transfer is completed, the metadata should be available in the
 *	attached buffer
 *
 * @DESC_METADATA_ENGINE - the metadata buffer is allocated/managed by the DMA
 *  driver. The client driver can ask क्रम the poपूर्णांकer, maximum size and the
 *  currently used size of the metadata and can directly update or पढ़ो it.
 *  dmaengine_desc_get_metadata_ptr() and dmaengine_desc_set_metadata_len() is
 *  provided as helper functions.
 *
 *  Note: the metadata area क्रम the descriptor is no दीर्घer valid after the
 *  transfer has been completed (valid up to the poपूर्णांक when the completion
 *  callback वापसs अगर used).
 *
 * Client drivers पूर्णांकerested to use this mode can follow:
 * - DMA_MEM_TO_DEV / DEV_MEM_TO_MEM:
 *   1. prepare the descriptor (dmaengine_prep_*)
 *   2. use dmaengine_desc_get_metadata_ptr() to get the poपूर्णांकer to the engine's
 *	metadata area
 *   3. update the metadata at the poपूर्णांकer
 *   4. use dmaengine_desc_set_metadata_len()  to tell the DMA engine the amount
 *	of data the client has placed पूर्णांकo the metadata buffer
 *   5. submit the transfer
 * - DMA_DEV_TO_MEM:
 *   1. prepare the descriptor (dmaengine_prep_*)
 *   2. submit the transfer
 *   3. on transfer completion, use dmaengine_desc_get_metadata_ptr() to get the
 *	poपूर्णांकer to the engine's metadata area
 *   4. Read out the metadata from the poपूर्णांकer
 *
 * Note: the two mode is not compatible and clients must use one mode क्रम a
 * descriptor.
 */
क्रमागत dma_desc_metadata_mode अणु
	DESC_METADATA_NONE = 0,
	DESC_METADATA_CLIENT = BIT(0),
	DESC_METADATA_ENGINE = BIT(1),
पूर्ण;

काष्ठा dma_chan_percpu अणु
	/* stats */
	अचिन्हित दीर्घ स_नकल_count;
	अचिन्हित दीर्घ bytes_transferred;
पूर्ण;

/**
 * काष्ठा dma_router - DMA router काष्ठाure
 * @dev: poपूर्णांकer to the DMA router device
 * @route_मुक्त: function to be called when the route can be disconnected
 */
काष्ठा dma_router अणु
	काष्ठा device *dev;
	व्योम (*route_मुक्त)(काष्ठा device *dev, व्योम *route_data);
पूर्ण;

/**
 * काष्ठा dma_chan - devices supply DMA channels, clients use them
 * @device: ptr to the dma device who supplies this channel, always !%शून्य
 * @slave: ptr to the device using this channel
 * @cookie: last cookie value वापसed to client
 * @completed_cookie: last completed cookie क्रम this channel
 * @chan_id: channel ID क्रम sysfs
 * @dev: class device क्रम sysfs
 * @name: backlink name क्रम sysfs
 * @dbg_client_name: slave name क्रम debugfs in क्रमmat:
 *	dev_name(requester's dev):channel name, क्रम example: "2b00000.mcasp:tx"
 * @device_node: used to add this to the device chan list
 * @local: per-cpu poपूर्णांकer to a काष्ठा dma_chan_percpu
 * @client_count: how many clients are using this channel
 * @table_count: number of appearances in the mem-to-mem allocation table
 * @router: poपूर्णांकer to the DMA router काष्ठाure
 * @route_data: channel specअगरic data क्रम the router
 * @निजी: निजी data क्रम certain client-channel associations
 */
काष्ठा dma_chan अणु
	काष्ठा dma_device *device;
	काष्ठा device *slave;
	dma_cookie_t cookie;
	dma_cookie_t completed_cookie;

	/* sysfs */
	पूर्णांक chan_id;
	काष्ठा dma_chan_dev *dev;
	स्थिर अक्षर *name;
#अगर_घोषित CONFIG_DEBUG_FS
	अक्षर *dbg_client_name;
#पूर्ण_अगर

	काष्ठा list_head device_node;
	काष्ठा dma_chan_percpu __percpu *local;
	पूर्णांक client_count;
	पूर्णांक table_count;

	/* DMA router */
	काष्ठा dma_router *router;
	व्योम *route_data;

	व्योम *निजी;
पूर्ण;

/**
 * काष्ठा dma_chan_dev - relate sysfs device node to backing channel device
 * @chan: driver channel device
 * @device: sysfs device
 * @dev_id: parent dma_device dev_id
 * @chan_dma_dev: The channel is using custom/dअगरferent dma-mapping
 * compared to the parent dma_device
 */
काष्ठा dma_chan_dev अणु
	काष्ठा dma_chan *chan;
	काष्ठा device device;
	पूर्णांक dev_id;
	bool chan_dma_dev;
पूर्ण;

/**
 * क्रमागत dma_slave_buswidth - defines bus width of the DMA slave
 * device, source or target buses
 */
क्रमागत dma_slave_buswidth अणु
	DMA_SLAVE_BUSWIDTH_UNDEFINED = 0,
	DMA_SLAVE_BUSWIDTH_1_BYTE = 1,
	DMA_SLAVE_BUSWIDTH_2_BYTES = 2,
	DMA_SLAVE_BUSWIDTH_3_BYTES = 3,
	DMA_SLAVE_BUSWIDTH_4_BYTES = 4,
	DMA_SLAVE_BUSWIDTH_8_BYTES = 8,
	DMA_SLAVE_BUSWIDTH_16_BYTES = 16,
	DMA_SLAVE_BUSWIDTH_32_BYTES = 32,
	DMA_SLAVE_BUSWIDTH_64_BYTES = 64,
पूर्ण;

/**
 * काष्ठा dma_slave_config - dma slave channel runसमय config
 * @direction: whether the data shall go in or out on this slave
 * channel, right now. DMA_MEM_TO_DEV and DMA_DEV_TO_MEM are
 * legal values. DEPRECATED, drivers should use the direction argument
 * to the device_prep_slave_sg and device_prep_dma_cyclic functions or
 * the dir field in the dma_पूर्णांकerleaved_ढाँचा काष्ठाure.
 * @src_addr: this is the physical address where DMA slave data
 * should be पढ़ो (RX), अगर the source is memory this argument is
 * ignored.
 * @dst_addr: this is the physical address where DMA slave data
 * should be written (TX), अगर the source is memory this argument
 * is ignored.
 * @src_addr_width: this is the width in bytes of the source (RX)
 * रेजिस्टर where DMA data shall be पढ़ो. If the source
 * is memory this may be ignored depending on architecture.
 * Legal values: 1, 2, 3, 4, 8, 16, 32, 64.
 * @dst_addr_width: same as src_addr_width but क्रम destination
 * target (TX) mutatis mutandis.
 * @src_maxburst: the maximum number of words (note: words, as in
 * units of the src_addr_width member, not bytes) that can be sent
 * in one burst to the device. Typically something like half the
 * FIFO depth on I/O peripherals so you करोn't overflow it. This
 * may or may not be applicable on memory sources.
 * @dst_maxburst: same as src_maxburst but क्रम destination target
 * mutatis mutandis.
 * @src_port_winकरोw_size: The length of the रेजिस्टर area in words the data need
 * to be accessed on the device side. It is only used क्रम devices which is using
 * an area instead of a single रेजिस्टर to receive the data. Typically the DMA
 * loops in this area in order to transfer the data.
 * @dst_port_winकरोw_size: same as src_port_winकरोw_size but क्रम the destination
 * port.
 * @device_fc: Flow Controller Settings. Only valid क्रम slave channels. Fill
 * with 'true' अगर peripheral should be flow controller. Direction will be
 * selected at Runसमय.
 * @slave_id: Slave requester id. Only valid क्रम slave channels. The dma
 * slave peripheral will have unique id as dma requester which need to be
 * pass as slave config.
 * @peripheral_config: peripheral configuration क्रम programming peripheral
 * क्रम dmaengine transfer
 * @peripheral_size: peripheral configuration buffer size
 *
 * This काष्ठा is passed in as configuration data to a DMA engine
 * in order to set up a certain channel क्रम DMA transport at runसमय.
 * The DMA device/engine has to provide support क्रम an additional
 * callback in the dma_device काष्ठाure, device_config and this काष्ठा
 * will then be passed in as an argument to the function.
 *
 * The rationale क्रम adding configuration inक्रमmation to this काष्ठा is as
 * follows: अगर it is likely that more than one DMA slave controllers in
 * the world will support the configuration option, then make it generic.
 * If not: अगर it is fixed so that it be sent in अटल from the platक्रमm
 * data, then prefer to करो that.
 */
काष्ठा dma_slave_config अणु
	क्रमागत dma_transfer_direction direction;
	phys_addr_t src_addr;
	phys_addr_t dst_addr;
	क्रमागत dma_slave_buswidth src_addr_width;
	क्रमागत dma_slave_buswidth dst_addr_width;
	u32 src_maxburst;
	u32 dst_maxburst;
	u32 src_port_winकरोw_size;
	u32 dst_port_winकरोw_size;
	bool device_fc;
	अचिन्हित पूर्णांक slave_id;
	व्योम *peripheral_config;
	माप_प्रकार peripheral_size;
पूर्ण;

/**
 * क्रमागत dma_residue_granularity - Granularity of the reported transfer residue
 * @DMA_RESIDUE_GRANULARITY_DESCRIPTOR: Residue reporting is not support. The
 *  DMA channel is only able to tell whether a descriptor has been completed or
 *  not, which means residue reporting is not supported by this channel. The
 *  residue field of the dma_tx_state field will always be 0.
 * @DMA_RESIDUE_GRANULARITY_SEGMENT: Residue is updated after each successfully
 *  completed segment of the transfer (For cyclic transfers this is after each
 *  period). This is typically implemented by having the hardware generate an
 *  पूर्णांकerrupt after each transferred segment and then the drivers updates the
 *  outstanding residue by the size of the segment. Another possibility is अगर
 *  the hardware supports scatter-gather and the segment descriptor has a field
 *  which माला_लो set after the segment has been completed. The driver then counts
 *  the number of segments without the flag set to compute the residue.
 * @DMA_RESIDUE_GRANULARITY_BURST: Residue is updated after each transferred
 *  burst. This is typically only supported अगर the hardware has a progress
 *  रेजिस्टर of some sort (E.g. a रेजिस्टर with the current पढ़ो/ग_लिखो address
 *  or a रेजिस्टर with the amount of bursts/beats/bytes that have been
 *  transferred or still need to be transferred).
 */
क्रमागत dma_residue_granularity अणु
	DMA_RESIDUE_GRANULARITY_DESCRIPTOR = 0,
	DMA_RESIDUE_GRANULARITY_SEGMENT = 1,
	DMA_RESIDUE_GRANULARITY_BURST = 2,
पूर्ण;

/**
 * काष्ठा dma_slave_caps - expose capabilities of a slave channel only
 * @src_addr_widths: bit mask of src addr widths the channel supports.
 *	Width is specअगरied in bytes, e.g. क्रम a channel supporting
 *	a width of 4 the mask should have BIT(4) set.
 * @dst_addr_widths: bit mask of dst addr widths the channel supports
 * @directions: bit mask of slave directions the channel supports.
 *	Since the क्रमागत dma_transfer_direction is not defined as bit flag क्रम
 *	each type, the dma controller should set BIT(<TYPE>) and same
 *	should be checked by controller as well
 * @min_burst: min burst capability per-transfer
 * @max_burst: max burst capability per-transfer
 * @max_sg_burst: max number of SG list entries executed in a single burst
 *	DMA tansaction with no software पूर्णांकervention क्रम reinitialization.
 *	Zero value means unlimited number of entries.
 * @cmd_छोड़ो: true, अगर छोड़ो is supported (i.e. क्रम पढ़ोing residue or
 *	       क्रम resume later)
 * @cmd_resume: true, अगर resume is supported
 * @cmd_terminate: true, अगर terminate cmd is supported
 * @residue_granularity: granularity of the reported transfer residue
 * @descriptor_reuse: अगर a descriptor can be reused by client and
 * resubmitted multiple बार
 */
काष्ठा dma_slave_caps अणु
	u32 src_addr_widths;
	u32 dst_addr_widths;
	u32 directions;
	u32 min_burst;
	u32 max_burst;
	u32 max_sg_burst;
	bool cmd_छोड़ो;
	bool cmd_resume;
	bool cmd_terminate;
	क्रमागत dma_residue_granularity residue_granularity;
	bool descriptor_reuse;
पूर्ण;

अटल अंतरभूत स्थिर अक्षर *dma_chan_name(काष्ठा dma_chan *chan)
अणु
	वापस dev_name(&chan->dev->device);
पूर्ण

व्योम dma_chan_cleanup(काष्ठा kref *kref);

/**
 * प्रकार dma_filter_fn - callback filter क्रम dma_request_channel
 * @chan: channel to be reviewed
 * @filter_param: opaque parameter passed through dma_request_channel
 *
 * When this optional parameter is specअगरied in a call to dma_request_channel a
 * suitable channel is passed to this routine क्रम further dispositioning beक्रमe
 * being वापसed.  Where 'suitable' indicates a non-busy channel that
 * satisfies the given capability mask.  It वापसs 'true' to indicate that the
 * channel is suitable.
 */
प्रकार bool (*dma_filter_fn)(काष्ठा dma_chan *chan, व्योम *filter_param);

प्रकार व्योम (*dma_async_tx_callback)(व्योम *dma_async_param);

क्रमागत dmaengine_tx_result अणु
	DMA_TRANS_NOERROR = 0,		/* SUCCESS */
	DMA_TRANS_READ_FAILED,		/* Source DMA पढ़ो failed */
	DMA_TRANS_WRITE_FAILED,		/* Destination DMA ग_लिखो failed */
	DMA_TRANS_ABORTED,		/* Op never submitted / पातed */
पूर्ण;

काष्ठा dmaengine_result अणु
	क्रमागत dmaengine_tx_result result;
	u32 residue;
पूर्ण;

प्रकार व्योम (*dma_async_tx_callback_result)(व्योम *dma_async_param,
				स्थिर काष्ठा dmaengine_result *result);

काष्ठा dmaengine_unmap_data अणु
#अगर IS_ENABLED(CONFIG_DMA_ENGINE_RAID)
	u16 map_cnt;
#अन्यथा
	u8 map_cnt;
#पूर्ण_अगर
	u8 to_cnt;
	u8 from_cnt;
	u8 bidi_cnt;
	काष्ठा device *dev;
	काष्ठा kref kref;
	माप_प्रकार len;
	dma_addr_t addr[];
पूर्ण;

काष्ठा dma_async_tx_descriptor;

काष्ठा dma_descriptor_metadata_ops अणु
	पूर्णांक (*attach)(काष्ठा dma_async_tx_descriptor *desc, व्योम *data,
		      माप_प्रकार len);

	व्योम *(*get_ptr)(काष्ठा dma_async_tx_descriptor *desc,
			 माप_प्रकार *payload_len, माप_प्रकार *max_len);
	पूर्णांक (*set_len)(काष्ठा dma_async_tx_descriptor *desc,
		       माप_प्रकार payload_len);
पूर्ण;

/**
 * काष्ठा dma_async_tx_descriptor - async transaction descriptor
 * ---dma generic offload fields---
 * @cookie: tracking cookie क्रम this transaction, set to -EBUSY अगर
 *	this tx is sitting on a dependency list
 * @flags: flags to augment operation preparation, control completion, and
 *	communicate status
 * @phys: physical address of the descriptor
 * @chan: target channel क्रम this operation
 * @tx_submit: accept the descriptor, assign ordered cookie and mark the
 * descriptor pending. To be pushed on .issue_pending() call
 * @callback: routine to call after this operation is complete
 * @callback_param: general parameter to pass to the callback routine
 * @desc_metadata_mode: core managed metadata mode to protect mixed use of
 *	DESC_METADATA_CLIENT or DESC_METADATA_ENGINE. Otherwise
 *	DESC_METADATA_NONE
 * @metadata_ops: DMA driver provided metadata mode ops, need to be set by the
 *	DMA driver अगर metadata mode is supported with the descriptor
 * ---async_tx api specअगरic fields---
 * @next: at completion submit this descriptor
 * @parent: poपूर्णांकer to the next level up in the dependency chain
 * @lock: protect the parent and next poपूर्णांकers
 */
काष्ठा dma_async_tx_descriptor अणु
	dma_cookie_t cookie;
	क्रमागत dma_ctrl_flags flags; /* not a 'long' to pack with cookie */
	dma_addr_t phys;
	काष्ठा dma_chan *chan;
	dma_cookie_t (*tx_submit)(काष्ठा dma_async_tx_descriptor *tx);
	पूर्णांक (*desc_मुक्त)(काष्ठा dma_async_tx_descriptor *tx);
	dma_async_tx_callback callback;
	dma_async_tx_callback_result callback_result;
	व्योम *callback_param;
	काष्ठा dmaengine_unmap_data *unmap;
	क्रमागत dma_desc_metadata_mode desc_metadata_mode;
	काष्ठा dma_descriptor_metadata_ops *metadata_ops;
#अगर_घोषित CONFIG_ASYNC_TX_ENABLE_CHANNEL_SWITCH
	काष्ठा dma_async_tx_descriptor *next;
	काष्ठा dma_async_tx_descriptor *parent;
	spinlock_t lock;
#पूर्ण_अगर
पूर्ण;

#अगर_घोषित CONFIG_DMA_ENGINE
अटल अंतरभूत व्योम dma_set_unmap(काष्ठा dma_async_tx_descriptor *tx,
				 काष्ठा dmaengine_unmap_data *unmap)
अणु
	kref_get(&unmap->kref);
	tx->unmap = unmap;
पूर्ण

काष्ठा dmaengine_unmap_data *
dmaengine_get_unmap_data(काष्ठा device *dev, पूर्णांक nr, gfp_t flags);
व्योम dmaengine_unmap_put(काष्ठा dmaengine_unmap_data *unmap);
#अन्यथा
अटल अंतरभूत व्योम dma_set_unmap(काष्ठा dma_async_tx_descriptor *tx,
				 काष्ठा dmaengine_unmap_data *unmap)
अणु
पूर्ण
अटल अंतरभूत काष्ठा dmaengine_unmap_data *
dmaengine_get_unmap_data(काष्ठा device *dev, पूर्णांक nr, gfp_t flags)
अणु
	वापस शून्य;
पूर्ण
अटल अंतरभूत व्योम dmaengine_unmap_put(काष्ठा dmaengine_unmap_data *unmap)
अणु
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत व्योम dma_descriptor_unmap(काष्ठा dma_async_tx_descriptor *tx)
अणु
	अगर (!tx->unmap)
		वापस;

	dmaengine_unmap_put(tx->unmap);
	tx->unmap = शून्य;
पूर्ण

#अगर_अघोषित CONFIG_ASYNC_TX_ENABLE_CHANNEL_SWITCH
अटल अंतरभूत व्योम txd_lock(काष्ठा dma_async_tx_descriptor *txd)
अणु
पूर्ण
अटल अंतरभूत व्योम txd_unlock(काष्ठा dma_async_tx_descriptor *txd)
अणु
पूर्ण
अटल अंतरभूत व्योम txd_chain(काष्ठा dma_async_tx_descriptor *txd, काष्ठा dma_async_tx_descriptor *next)
अणु
	BUG();
पूर्ण
अटल अंतरभूत व्योम txd_clear_parent(काष्ठा dma_async_tx_descriptor *txd)
अणु
पूर्ण
अटल अंतरभूत व्योम txd_clear_next(काष्ठा dma_async_tx_descriptor *txd)
अणु
पूर्ण
अटल अंतरभूत काष्ठा dma_async_tx_descriptor *txd_next(काष्ठा dma_async_tx_descriptor *txd)
अणु
	वापस शून्य;
पूर्ण
अटल अंतरभूत काष्ठा dma_async_tx_descriptor *txd_parent(काष्ठा dma_async_tx_descriptor *txd)
अणु
	वापस शून्य;
पूर्ण

#अन्यथा
अटल अंतरभूत व्योम txd_lock(काष्ठा dma_async_tx_descriptor *txd)
अणु
	spin_lock_bh(&txd->lock);
पूर्ण
अटल अंतरभूत व्योम txd_unlock(काष्ठा dma_async_tx_descriptor *txd)
अणु
	spin_unlock_bh(&txd->lock);
पूर्ण
अटल अंतरभूत व्योम txd_chain(काष्ठा dma_async_tx_descriptor *txd, काष्ठा dma_async_tx_descriptor *next)
अणु
	txd->next = next;
	next->parent = txd;
पूर्ण
अटल अंतरभूत व्योम txd_clear_parent(काष्ठा dma_async_tx_descriptor *txd)
अणु
	txd->parent = शून्य;
पूर्ण
अटल अंतरभूत व्योम txd_clear_next(काष्ठा dma_async_tx_descriptor *txd)
अणु
	txd->next = शून्य;
पूर्ण
अटल अंतरभूत काष्ठा dma_async_tx_descriptor *txd_parent(काष्ठा dma_async_tx_descriptor *txd)
अणु
	वापस txd->parent;
पूर्ण
अटल अंतरभूत काष्ठा dma_async_tx_descriptor *txd_next(काष्ठा dma_async_tx_descriptor *txd)
अणु
	वापस txd->next;
पूर्ण
#पूर्ण_अगर

/**
 * काष्ठा dma_tx_state - filled in to report the status of
 * a transfer.
 * @last: last completed DMA cookie
 * @used: last issued DMA cookie (i.e. the one in progress)
 * @residue: the reमुख्यing number of bytes left to transmit
 *	on the selected transfer क्रम states DMA_IN_PROGRESS and
 *	DMA_PAUSED अगर this is implemented in the driver, अन्यथा 0
 * @in_flight_bytes: amount of data in bytes cached by the DMA.
 */
काष्ठा dma_tx_state अणु
	dma_cookie_t last;
	dma_cookie_t used;
	u32 residue;
	u32 in_flight_bytes;
पूर्ण;

/**
 * क्रमागत dmaengine_alignment - defines alignment of the DMA async tx
 * buffers
 */
क्रमागत dmaengine_alignment अणु
	DMAENGINE_ALIGN_1_BYTE = 0,
	DMAENGINE_ALIGN_2_BYTES = 1,
	DMAENGINE_ALIGN_4_BYTES = 2,
	DMAENGINE_ALIGN_8_BYTES = 3,
	DMAENGINE_ALIGN_16_BYTES = 4,
	DMAENGINE_ALIGN_32_BYTES = 5,
	DMAENGINE_ALIGN_64_BYTES = 6,
	DMAENGINE_ALIGN_128_BYTES = 7,
	DMAENGINE_ALIGN_256_BYTES = 8,
पूर्ण;

/**
 * काष्ठा dma_slave_map - associates slave device and it's slave channel with
 * parameter to be used by a filter function
 * @devname: name of the device
 * @slave: slave channel name
 * @param: opaque parameter to pass to काष्ठा dma_filter.fn
 */
काष्ठा dma_slave_map अणु
	स्थिर अक्षर *devname;
	स्थिर अक्षर *slave;
	व्योम *param;
पूर्ण;

/**
 * काष्ठा dma_filter - inक्रमmation क्रम slave device/channel to filter_fn/param
 * mapping
 * @fn: filter function callback
 * @mapcnt: number of slave device/channel in the map
 * @map: array of channel to filter mapping data
 */
काष्ठा dma_filter अणु
	dma_filter_fn fn;
	पूर्णांक mapcnt;
	स्थिर काष्ठा dma_slave_map *map;
पूर्ण;

/**
 * काष्ठा dma_device - info on the entity supplying DMA services
 * @chancnt: how many DMA channels are supported
 * @निजीcnt: how many DMA channels are requested by dma_request_channel
 * @channels: the list of काष्ठा dma_chan
 * @global_node: list_head क्रम global dma_device_list
 * @filter: inक्रमmation क्रम device/slave to filter function/param mapping
 * @cap_mask: one or more dma_capability flags
 * @desc_metadata_modes: supported metadata modes by the DMA device
 * @max_xor: maximum number of xor sources, 0 अगर no capability
 * @max_pq: maximum number of PQ sources and PQ-जारी capability
 * @copy_align: alignment shअगरt क्रम स_नकल operations
 * @xor_align: alignment shअगरt क्रम xor operations
 * @pq_align: alignment shअगरt क्रम pq operations
 * @fill_align: alignment shअगरt क्रम स_रखो operations
 * @dev_id: unique device ID
 * @dev: काष्ठा device reference क्रम dma mapping api
 * @owner: owner module (स्वतःmatically set based on the provided dev)
 * @src_addr_widths: bit mask of src addr widths the device supports
 *	Width is specअगरied in bytes, e.g. क्रम a device supporting
 *	a width of 4 the mask should have BIT(4) set.
 * @dst_addr_widths: bit mask of dst addr widths the device supports
 * @directions: bit mask of slave directions the device supports.
 *	Since the क्रमागत dma_transfer_direction is not defined as bit flag क्रम
 *	each type, the dma controller should set BIT(<TYPE>) and same
 *	should be checked by controller as well
 * @min_burst: min burst capability per-transfer
 * @max_burst: max burst capability per-transfer
 * @max_sg_burst: max number of SG list entries executed in a single burst
 *	DMA tansaction with no software पूर्णांकervention क्रम reinitialization.
 *	Zero value means unlimited number of entries.
 * @residue_granularity: granularity of the transfer residue reported
 *	by tx_status
 * @device_alloc_chan_resources: allocate resources and वापस the
 *	number of allocated descriptors
 * @device_router_config: optional callback क्रम DMA router configuration
 * @device_मुक्त_chan_resources: release DMA channel's resources
 * @device_prep_dma_स_नकल: prepares a स_नकल operation
 * @device_prep_dma_xor: prepares a xor operation
 * @device_prep_dma_xor_val: prepares a xor validation operation
 * @device_prep_dma_pq: prepares a pq operation
 * @device_prep_dma_pq_val: prepares a pqzero_sum operation
 * @device_prep_dma_स_रखो: prepares a स_रखो operation
 * @device_prep_dma_स_रखो_sg: prepares a स_रखो operation over a scatter list
 * @device_prep_dma_पूर्णांकerrupt: prepares an end of chain पूर्णांकerrupt operation
 * @device_prep_slave_sg: prepares a slave dma operation
 * @device_prep_dma_cyclic: prepare a cyclic dma operation suitable क्रम audio.
 *	The function takes a buffer of size buf_len. The callback function will
 *	be called after period_len bytes have been transferred.
 * @device_prep_पूर्णांकerleaved_dma: Transfer expression in a generic way.
 * @device_prep_dma_imm_data: DMA's 8 byte immediate data to the dst address
 * @device_caps: May be used to override the generic DMA slave capabilities
 *	with per-channel specअगरic ones
 * @device_config: Pushes a new configuration to a channel, वापस 0 or an error
 *	code
 * @device_छोड़ो: Pauses any transfer happening on a channel. Returns
 *	0 or an error code
 * @device_resume: Resumes any transfer on a channel previously
 *	छोड़ोd. Returns 0 or an error code
 * @device_terminate_all: Aborts all transfers on a channel. Returns 0
 *	or an error code
 * @device_synchronize: Synchronizes the termination of a transfers to the
 *  current context.
 * @device_tx_status: poll क्रम transaction completion, the optional
 *	txstate parameter can be supplied with a poपूर्णांकer to get a
 *	काष्ठा with auxiliary transfer status inक्रमmation, otherwise the call
 *	will just वापस a simple status code
 * @device_issue_pending: push pending transactions to hardware
 * @descriptor_reuse: a submitted transfer can be resubmitted after completion
 * @device_release: called someसमय atfer dma_async_device_unरेजिस्टर() is
 *     called and there are no further references to this काष्ठाure. This
 *     must be implemented to मुक्त resources however many existing drivers
 *     करो not and are thereक्रमe not safe to unbind जबतक in use.
 * @dbg_summary_show: optional routine to show contents in debugfs; शेष code
 *     will be used when this is omitted, but custom code can show extra,
 *     controller specअगरic inक्रमmation.
 */
काष्ठा dma_device अणु
	काष्ठा kref ref;
	अचिन्हित पूर्णांक chancnt;
	अचिन्हित पूर्णांक निजीcnt;
	काष्ठा list_head channels;
	काष्ठा list_head global_node;
	काष्ठा dma_filter filter;
	dma_cap_mask_t  cap_mask;
	क्रमागत dma_desc_metadata_mode desc_metadata_modes;
	अचिन्हित लघु max_xor;
	अचिन्हित लघु max_pq;
	क्रमागत dmaengine_alignment copy_align;
	क्रमागत dmaengine_alignment xor_align;
	क्रमागत dmaengine_alignment pq_align;
	क्रमागत dmaengine_alignment fill_align;
	#घोषणा DMA_HAS_PQ_CONTINUE (1 << 15)

	पूर्णांक dev_id;
	काष्ठा device *dev;
	काष्ठा module *owner;
	काष्ठा ida chan_ida;
	काष्ठा mutex chan_mutex;	/* to protect chan_ida */

	u32 src_addr_widths;
	u32 dst_addr_widths;
	u32 directions;
	u32 min_burst;
	u32 max_burst;
	u32 max_sg_burst;
	bool descriptor_reuse;
	क्रमागत dma_residue_granularity residue_granularity;

	पूर्णांक (*device_alloc_chan_resources)(काष्ठा dma_chan *chan);
	पूर्णांक (*device_router_config)(काष्ठा dma_chan *chan);
	व्योम (*device_मुक्त_chan_resources)(काष्ठा dma_chan *chan);

	काष्ठा dma_async_tx_descriptor *(*device_prep_dma_स_नकल)(
		काष्ठा dma_chan *chan, dma_addr_t dst, dma_addr_t src,
		माप_प्रकार len, अचिन्हित दीर्घ flags);
	काष्ठा dma_async_tx_descriptor *(*device_prep_dma_xor)(
		काष्ठा dma_chan *chan, dma_addr_t dst, dma_addr_t *src,
		अचिन्हित पूर्णांक src_cnt, माप_प्रकार len, अचिन्हित दीर्घ flags);
	काष्ठा dma_async_tx_descriptor *(*device_prep_dma_xor_val)(
		काष्ठा dma_chan *chan, dma_addr_t *src,	अचिन्हित पूर्णांक src_cnt,
		माप_प्रकार len, क्रमागत sum_check_flags *result, अचिन्हित दीर्घ flags);
	काष्ठा dma_async_tx_descriptor *(*device_prep_dma_pq)(
		काष्ठा dma_chan *chan, dma_addr_t *dst, dma_addr_t *src,
		अचिन्हित पूर्णांक src_cnt, स्थिर अचिन्हित अक्षर *scf,
		माप_प्रकार len, अचिन्हित दीर्घ flags);
	काष्ठा dma_async_tx_descriptor *(*device_prep_dma_pq_val)(
		काष्ठा dma_chan *chan, dma_addr_t *pq, dma_addr_t *src,
		अचिन्हित पूर्णांक src_cnt, स्थिर अचिन्हित अक्षर *scf, माप_प्रकार len,
		क्रमागत sum_check_flags *pqres, अचिन्हित दीर्घ flags);
	काष्ठा dma_async_tx_descriptor *(*device_prep_dma_स_रखो)(
		काष्ठा dma_chan *chan, dma_addr_t dest, पूर्णांक value, माप_प्रकार len,
		अचिन्हित दीर्घ flags);
	काष्ठा dma_async_tx_descriptor *(*device_prep_dma_स_रखो_sg)(
		काष्ठा dma_chan *chan, काष्ठा scatterlist *sg,
		अचिन्हित पूर्णांक nents, पूर्णांक value, अचिन्हित दीर्घ flags);
	काष्ठा dma_async_tx_descriptor *(*device_prep_dma_पूर्णांकerrupt)(
		काष्ठा dma_chan *chan, अचिन्हित दीर्घ flags);

	काष्ठा dma_async_tx_descriptor *(*device_prep_slave_sg)(
		काष्ठा dma_chan *chan, काष्ठा scatterlist *sgl,
		अचिन्हित पूर्णांक sg_len, क्रमागत dma_transfer_direction direction,
		अचिन्हित दीर्घ flags, व्योम *context);
	काष्ठा dma_async_tx_descriptor *(*device_prep_dma_cyclic)(
		काष्ठा dma_chan *chan, dma_addr_t buf_addr, माप_प्रकार buf_len,
		माप_प्रकार period_len, क्रमागत dma_transfer_direction direction,
		अचिन्हित दीर्घ flags);
	काष्ठा dma_async_tx_descriptor *(*device_prep_पूर्णांकerleaved_dma)(
		काष्ठा dma_chan *chan, काष्ठा dma_पूर्णांकerleaved_ढाँचा *xt,
		अचिन्हित दीर्घ flags);
	काष्ठा dma_async_tx_descriptor *(*device_prep_dma_imm_data)(
		काष्ठा dma_chan *chan, dma_addr_t dst, u64 data,
		अचिन्हित दीर्घ flags);

	व्योम (*device_caps)(काष्ठा dma_chan *chan,
			    काष्ठा dma_slave_caps *caps);
	पूर्णांक (*device_config)(काष्ठा dma_chan *chan,
			     काष्ठा dma_slave_config *config);
	पूर्णांक (*device_छोड़ो)(काष्ठा dma_chan *chan);
	पूर्णांक (*device_resume)(काष्ठा dma_chan *chan);
	पूर्णांक (*device_terminate_all)(काष्ठा dma_chan *chan);
	व्योम (*device_synchronize)(काष्ठा dma_chan *chan);

	क्रमागत dma_status (*device_tx_status)(काष्ठा dma_chan *chan,
					    dma_cookie_t cookie,
					    काष्ठा dma_tx_state *txstate);
	व्योम (*device_issue_pending)(काष्ठा dma_chan *chan);
	व्योम (*device_release)(काष्ठा dma_device *dev);
	/* debugfs support */
#अगर_घोषित CONFIG_DEBUG_FS
	व्योम (*dbg_summary_show)(काष्ठा seq_file *s, काष्ठा dma_device *dev);
	काष्ठा dentry *dbg_dev_root;
#पूर्ण_अगर
पूर्ण;

अटल अंतरभूत पूर्णांक dmaengine_slave_config(काष्ठा dma_chan *chan,
					  काष्ठा dma_slave_config *config)
अणु
	अगर (chan->device->device_config)
		वापस chan->device->device_config(chan, config);

	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत bool is_slave_direction(क्रमागत dma_transfer_direction direction)
अणु
	वापस (direction == DMA_MEM_TO_DEV) || (direction == DMA_DEV_TO_MEM);
पूर्ण

अटल अंतरभूत काष्ठा dma_async_tx_descriptor *dmaengine_prep_slave_single(
	काष्ठा dma_chan *chan, dma_addr_t buf, माप_प्रकार len,
	क्रमागत dma_transfer_direction dir, अचिन्हित दीर्घ flags)
अणु
	काष्ठा scatterlist sg;
	sg_init_table(&sg, 1);
	sg_dma_address(&sg) = buf;
	sg_dma_len(&sg) = len;

	अगर (!chan || !chan->device || !chan->device->device_prep_slave_sg)
		वापस शून्य;

	वापस chan->device->device_prep_slave_sg(chan, &sg, 1,
						  dir, flags, शून्य);
पूर्ण

अटल अंतरभूत काष्ठा dma_async_tx_descriptor *dmaengine_prep_slave_sg(
	काष्ठा dma_chan *chan, काष्ठा scatterlist *sgl,	अचिन्हित पूर्णांक sg_len,
	क्रमागत dma_transfer_direction dir, अचिन्हित दीर्घ flags)
अणु
	अगर (!chan || !chan->device || !chan->device->device_prep_slave_sg)
		वापस शून्य;

	वापस chan->device->device_prep_slave_sg(chan, sgl, sg_len,
						  dir, flags, शून्य);
पूर्ण

#अगर_घोषित CONFIG_RAPIDIO_DMA_ENGINE
काष्ठा rio_dma_ext;
अटल अंतरभूत काष्ठा dma_async_tx_descriptor *dmaengine_prep_rio_sg(
	काष्ठा dma_chan *chan, काष्ठा scatterlist *sgl,	अचिन्हित पूर्णांक sg_len,
	क्रमागत dma_transfer_direction dir, अचिन्हित दीर्घ flags,
	काष्ठा rio_dma_ext *rio_ext)
अणु
	अगर (!chan || !chan->device || !chan->device->device_prep_slave_sg)
		वापस शून्य;

	वापस chan->device->device_prep_slave_sg(chan, sgl, sg_len,
						  dir, flags, rio_ext);
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत काष्ठा dma_async_tx_descriptor *dmaengine_prep_dma_cyclic(
		काष्ठा dma_chan *chan, dma_addr_t buf_addr, माप_प्रकार buf_len,
		माप_प्रकार period_len, क्रमागत dma_transfer_direction dir,
		अचिन्हित दीर्घ flags)
अणु
	अगर (!chan || !chan->device || !chan->device->device_prep_dma_cyclic)
		वापस शून्य;

	वापस chan->device->device_prep_dma_cyclic(chan, buf_addr, buf_len,
						period_len, dir, flags);
पूर्ण

अटल अंतरभूत काष्ठा dma_async_tx_descriptor *dmaengine_prep_पूर्णांकerleaved_dma(
		काष्ठा dma_chan *chan, काष्ठा dma_पूर्णांकerleaved_ढाँचा *xt,
		अचिन्हित दीर्घ flags)
अणु
	अगर (!chan || !chan->device || !chan->device->device_prep_पूर्णांकerleaved_dma)
		वापस शून्य;
	अगर (flags & DMA_PREP_REPEAT &&
	    !test_bit(DMA_REPEAT, chan->device->cap_mask.bits))
		वापस शून्य;

	वापस chan->device->device_prep_पूर्णांकerleaved_dma(chan, xt, flags);
पूर्ण

अटल अंतरभूत काष्ठा dma_async_tx_descriptor *dmaengine_prep_dma_स_रखो(
		काष्ठा dma_chan *chan, dma_addr_t dest, पूर्णांक value, माप_प्रकार len,
		अचिन्हित दीर्घ flags)
अणु
	अगर (!chan || !chan->device || !chan->device->device_prep_dma_स_रखो)
		वापस शून्य;

	वापस chan->device->device_prep_dma_स_रखो(chan, dest, value,
						    len, flags);
पूर्ण

अटल अंतरभूत काष्ठा dma_async_tx_descriptor *dmaengine_prep_dma_स_नकल(
		काष्ठा dma_chan *chan, dma_addr_t dest, dma_addr_t src,
		माप_प्रकार len, अचिन्हित दीर्घ flags)
अणु
	अगर (!chan || !chan->device || !chan->device->device_prep_dma_स_नकल)
		वापस शून्य;

	वापस chan->device->device_prep_dma_स_नकल(chan, dest, src,
						    len, flags);
पूर्ण

अटल अंतरभूत bool dmaengine_is_metadata_mode_supported(काष्ठा dma_chan *chan,
		क्रमागत dma_desc_metadata_mode mode)
अणु
	अगर (!chan)
		वापस false;

	वापस !!(chan->device->desc_metadata_modes & mode);
पूर्ण

#अगर_घोषित CONFIG_DMA_ENGINE
पूर्णांक dmaengine_desc_attach_metadata(काष्ठा dma_async_tx_descriptor *desc,
				   व्योम *data, माप_प्रकार len);
व्योम *dmaengine_desc_get_metadata_ptr(काष्ठा dma_async_tx_descriptor *desc,
				      माप_प्रकार *payload_len, माप_प्रकार *max_len);
पूर्णांक dmaengine_desc_set_metadata_len(काष्ठा dma_async_tx_descriptor *desc,
				    माप_प्रकार payload_len);
#अन्यथा /* CONFIG_DMA_ENGINE */
अटल अंतरभूत पूर्णांक dmaengine_desc_attach_metadata(
		काष्ठा dma_async_tx_descriptor *desc, व्योम *data, माप_प्रकार len)
अणु
	वापस -EINVAL;
पूर्ण
अटल अंतरभूत व्योम *dmaengine_desc_get_metadata_ptr(
		काष्ठा dma_async_tx_descriptor *desc, माप_प्रकार *payload_len,
		माप_प्रकार *max_len)
अणु
	वापस शून्य;
पूर्ण
अटल अंतरभूत पूर्णांक dmaengine_desc_set_metadata_len(
		काष्ठा dma_async_tx_descriptor *desc, माप_प्रकार payload_len)
अणु
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर /* CONFIG_DMA_ENGINE */

/**
 * dmaengine_terminate_all() - Terminate all active DMA transfers
 * @chan: The channel क्रम which to terminate the transfers
 *
 * This function is DEPRECATED use either dmaengine_terminate_sync() or
 * dmaengine_terminate_async() instead.
 */
अटल अंतरभूत पूर्णांक dmaengine_terminate_all(काष्ठा dma_chan *chan)
अणु
	अगर (chan->device->device_terminate_all)
		वापस chan->device->device_terminate_all(chan);

	वापस -ENOSYS;
पूर्ण

/**
 * dmaengine_terminate_async() - Terminate all active DMA transfers
 * @chan: The channel क्रम which to terminate the transfers
 *
 * Calling this function will terminate all active and pending descriptors
 * that have previously been submitted to the channel. It is not guaranteed
 * though that the transfer क्रम the active descriptor has stopped when the
 * function वापसs. Furthermore it is possible the complete callback of a
 * submitted transfer is still running when this function वापसs.
 *
 * dmaengine_synchronize() needs to be called beक्रमe it is safe to मुक्त
 * any memory that is accessed by previously submitted descriptors or beक्रमe
 * मुक्तing any resources accessed from within the completion callback of any
 * previously submitted descriptors.
 *
 * This function can be called from atomic context as well as from within a
 * complete callback of a descriptor submitted on the same channel.
 *
 * If none of the two conditions above apply consider using
 * dmaengine_terminate_sync() instead.
 */
अटल अंतरभूत पूर्णांक dmaengine_terminate_async(काष्ठा dma_chan *chan)
अणु
	अगर (chan->device->device_terminate_all)
		वापस chan->device->device_terminate_all(chan);

	वापस -EINVAL;
पूर्ण

/**
 * dmaengine_synchronize() - Synchronize DMA channel termination
 * @chan: The channel to synchronize
 *
 * Synchronizes to the DMA channel termination to the current context. When this
 * function वापसs it is guaranteed that all transfers क्रम previously issued
 * descriptors have stopped and it is safe to मुक्त the memory associated
 * with them. Furthermore it is guaranteed that all complete callback functions
 * क्रम a previously submitted descriptor have finished running and it is safe to
 * मुक्त resources accessed from within the complete callbacks.
 *
 * The behavior of this function is undefined अगर dma_async_issue_pending() has
 * been called between dmaengine_terminate_async() and this function.
 *
 * This function must only be called from non-atomic context and must not be
 * called from within a complete callback of a descriptor submitted on the same
 * channel.
 */
अटल अंतरभूत व्योम dmaengine_synchronize(काष्ठा dma_chan *chan)
अणु
	might_sleep();

	अगर (chan->device->device_synchronize)
		chan->device->device_synchronize(chan);
पूर्ण

/**
 * dmaengine_terminate_sync() - Terminate all active DMA transfers
 * @chan: The channel क्रम which to terminate the transfers
 *
 * Calling this function will terminate all active and pending transfers
 * that have previously been submitted to the channel. It is similar to
 * dmaengine_terminate_async() but guarantees that the DMA transfer has actually
 * stopped and that all complete callbacks have finished running when the
 * function वापसs.
 *
 * This function must only be called from non-atomic context and must not be
 * called from within a complete callback of a descriptor submitted on the same
 * channel.
 */
अटल अंतरभूत पूर्णांक dmaengine_terminate_sync(काष्ठा dma_chan *chan)
अणु
	पूर्णांक ret;

	ret = dmaengine_terminate_async(chan);
	अगर (ret)
		वापस ret;

	dmaengine_synchronize(chan);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक dmaengine_छोड़ो(काष्ठा dma_chan *chan)
अणु
	अगर (chan->device->device_छोड़ो)
		वापस chan->device->device_छोड़ो(chan);

	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत पूर्णांक dmaengine_resume(काष्ठा dma_chan *chan)
अणु
	अगर (chan->device->device_resume)
		वापस chan->device->device_resume(chan);

	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत क्रमागत dma_status dmaengine_tx_status(काष्ठा dma_chan *chan,
	dma_cookie_t cookie, काष्ठा dma_tx_state *state)
अणु
	वापस chan->device->device_tx_status(chan, cookie, state);
पूर्ण

अटल अंतरभूत dma_cookie_t dmaengine_submit(काष्ठा dma_async_tx_descriptor *desc)
अणु
	वापस desc->tx_submit(desc);
पूर्ण

अटल अंतरभूत bool dmaengine_check_align(क्रमागत dmaengine_alignment align,
					 माप_प्रकार off1, माप_प्रकार off2, माप_प्रकार len)
अणु
	वापस !(((1 << align) - 1) & (off1 | off2 | len));
पूर्ण

अटल अंतरभूत bool is_dma_copy_aligned(काष्ठा dma_device *dev, माप_प्रकार off1,
				       माप_प्रकार off2, माप_प्रकार len)
अणु
	वापस dmaengine_check_align(dev->copy_align, off1, off2, len);
पूर्ण

अटल अंतरभूत bool is_dma_xor_aligned(काष्ठा dma_device *dev, माप_प्रकार off1,
				      माप_प्रकार off2, माप_प्रकार len)
अणु
	वापस dmaengine_check_align(dev->xor_align, off1, off2, len);
पूर्ण

अटल अंतरभूत bool is_dma_pq_aligned(काष्ठा dma_device *dev, माप_प्रकार off1,
				     माप_प्रकार off2, माप_प्रकार len)
अणु
	वापस dmaengine_check_align(dev->pq_align, off1, off2, len);
पूर्ण

अटल अंतरभूत bool is_dma_fill_aligned(काष्ठा dma_device *dev, माप_प्रकार off1,
				       माप_प्रकार off2, माप_प्रकार len)
अणु
	वापस dmaengine_check_align(dev->fill_align, off1, off2, len);
पूर्ण

अटल अंतरभूत व्योम
dma_set_maxpq(काष्ठा dma_device *dma, पूर्णांक maxpq, पूर्णांक has_pq_जारी)
अणु
	dma->max_pq = maxpq;
	अगर (has_pq_जारी)
		dma->max_pq |= DMA_HAS_PQ_CONTINUE;
पूर्ण

अटल अंतरभूत bool dmaf_जारी(क्रमागत dma_ctrl_flags flags)
अणु
	वापस (flags & DMA_PREP_CONTINUE) == DMA_PREP_CONTINUE;
पूर्ण

अटल अंतरभूत bool dmaf_p_disabled_जारी(क्रमागत dma_ctrl_flags flags)
अणु
	क्रमागत dma_ctrl_flags mask = DMA_PREP_CONTINUE | DMA_PREP_PQ_DISABLE_P;

	वापस (flags & mask) == mask;
पूर्ण

अटल अंतरभूत bool dma_dev_has_pq_जारी(काष्ठा dma_device *dma)
अणु
	वापस (dma->max_pq & DMA_HAS_PQ_CONTINUE) == DMA_HAS_PQ_CONTINUE;
पूर्ण

अटल अंतरभूत अचिन्हित लघु dma_dev_to_maxpq(काष्ठा dma_device *dma)
अणु
	वापस dma->max_pq & ~DMA_HAS_PQ_CONTINUE;
पूर्ण

/* dma_maxpq - reduce maxpq in the face of जारीd operations
 * @dma - dma device with PQ capability
 * @flags - to check अगर DMA_PREP_CONTINUE and DMA_PREP_PQ_DISABLE_P are set
 *
 * When an engine करोes not support native continuation we need 3 extra
 * source slots to reuse P and Q with the following coefficients:
 * 1/ अणु00पूर्ण * P : हटाओ P from Q', but use it as a source for P'
 * 2/ अणु01पूर्ण * Q : use Q to जारी Q' calculation
 * 3/ अणु00पूर्ण * Q : subtract Q from P' to cancel (2)
 *
 * In the हाल where P is disabled we only need 1 extra source:
 * 1/ अणु01पूर्ण * Q : use Q to जारी Q' calculation
 */
अटल अंतरभूत पूर्णांक dma_maxpq(काष्ठा dma_device *dma, क्रमागत dma_ctrl_flags flags)
अणु
	अगर (dma_dev_has_pq_जारी(dma) || !dmaf_जारी(flags))
		वापस dma_dev_to_maxpq(dma);
	अगर (dmaf_p_disabled_जारी(flags))
		वापस dma_dev_to_maxpq(dma) - 1;
	अगर (dmaf_जारी(flags))
		वापस dma_dev_to_maxpq(dma) - 3;
	BUG();
पूर्ण

अटल अंतरभूत माप_प्रकार dmaengine_get_icg(bool inc, bool sgl, माप_प्रकार icg,
				      माप_प्रकार dir_icg)
अणु
	अगर (inc) अणु
		अगर (dir_icg)
			वापस dir_icg;
		अगर (sgl)
			वापस icg;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत माप_प्रकार dmaengine_get_dst_icg(काष्ठा dma_पूर्णांकerleaved_ढाँचा *xt,
					   काष्ठा data_chunk *chunk)
अणु
	वापस dmaengine_get_icg(xt->dst_inc, xt->dst_sgl,
				 chunk->icg, chunk->dst_icg);
पूर्ण

अटल अंतरभूत माप_प्रकार dmaengine_get_src_icg(काष्ठा dma_पूर्णांकerleaved_ढाँचा *xt,
					   काष्ठा data_chunk *chunk)
अणु
	वापस dmaengine_get_icg(xt->src_inc, xt->src_sgl,
				 chunk->icg, chunk->src_icg);
पूर्ण

/* --- खुला DMA engine API --- */

#अगर_घोषित CONFIG_DMA_ENGINE
व्योम dmaengine_get(व्योम);
व्योम dmaengine_put(व्योम);
#अन्यथा
अटल अंतरभूत व्योम dmaengine_get(व्योम)
अणु
पूर्ण
अटल अंतरभूत व्योम dmaengine_put(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_ASYNC_TX_DMA
#घोषणा async_dmaengine_get()	dmaengine_get()
#घोषणा async_dmaengine_put()	dmaengine_put()
#अगर_अघोषित CONFIG_ASYNC_TX_ENABLE_CHANNEL_SWITCH
#घोषणा async_dma_find_channel(type) dma_find_channel(DMA_ASYNC_TX)
#अन्यथा
#घोषणा async_dma_find_channel(type) dma_find_channel(type)
#पूर्ण_अगर /* CONFIG_ASYNC_TX_ENABLE_CHANNEL_SWITCH */
#अन्यथा
अटल अंतरभूत व्योम async_dmaengine_get(व्योम)
अणु
पूर्ण
अटल अंतरभूत व्योम async_dmaengine_put(व्योम)
अणु
पूर्ण
अटल अंतरभूत काष्ठा dma_chan *
async_dma_find_channel(क्रमागत dma_transaction_type type)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर /* CONFIG_ASYNC_TX_DMA */
व्योम dma_async_tx_descriptor_init(काष्ठा dma_async_tx_descriptor *tx,
				  काष्ठा dma_chan *chan);

अटल अंतरभूत व्योम async_tx_ack(काष्ठा dma_async_tx_descriptor *tx)
अणु
	tx->flags |= DMA_CTRL_ACK;
पूर्ण

अटल अंतरभूत व्योम async_tx_clear_ack(काष्ठा dma_async_tx_descriptor *tx)
अणु
	tx->flags &= ~DMA_CTRL_ACK;
पूर्ण

अटल अंतरभूत bool async_tx_test_ack(काष्ठा dma_async_tx_descriptor *tx)
अणु
	वापस (tx->flags & DMA_CTRL_ACK) == DMA_CTRL_ACK;
पूर्ण

#घोषणा dma_cap_set(tx, mask) __dma_cap_set((tx), &(mask))
अटल अंतरभूत व्योम
__dma_cap_set(क्रमागत dma_transaction_type tx_type, dma_cap_mask_t *dstp)
अणु
	set_bit(tx_type, dstp->bits);
पूर्ण

#घोषणा dma_cap_clear(tx, mask) __dma_cap_clear((tx), &(mask))
अटल अंतरभूत व्योम
__dma_cap_clear(क्रमागत dma_transaction_type tx_type, dma_cap_mask_t *dstp)
अणु
	clear_bit(tx_type, dstp->bits);
पूर्ण

#घोषणा dma_cap_zero(mask) __dma_cap_zero(&(mask))
अटल अंतरभूत व्योम __dma_cap_zero(dma_cap_mask_t *dstp)
अणु
	biपंचांगap_zero(dstp->bits, DMA_TX_TYPE_END);
पूर्ण

#घोषणा dma_has_cap(tx, mask) __dma_has_cap((tx), &(mask))
अटल अंतरभूत पूर्णांक
__dma_has_cap(क्रमागत dma_transaction_type tx_type, dma_cap_mask_t *srcp)
अणु
	वापस test_bit(tx_type, srcp->bits);
पूर्ण

#घोषणा क्रम_each_dma_cap_mask(cap, mask) \
	क्रम_each_set_bit(cap, mask.bits, DMA_TX_TYPE_END)

/**
 * dma_async_issue_pending - flush pending transactions to HW
 * @chan: target DMA channel
 *
 * This allows drivers to push copies to HW in batches,
 * reducing MMIO ग_लिखोs where possible.
 */
अटल अंतरभूत व्योम dma_async_issue_pending(काष्ठा dma_chan *chan)
अणु
	chan->device->device_issue_pending(chan);
पूर्ण

/**
 * dma_async_is_tx_complete - poll क्रम transaction completion
 * @chan: DMA channel
 * @cookie: transaction identअगरier to check status of
 * @last: वापसs last completed cookie, can be शून्य
 * @used: वापसs last issued cookie, can be शून्य
 *
 * If @last and @used are passed in, upon वापस they reflect the driver
 * पूर्णांकernal state and can be used with dma_async_is_complete() to check
 * the status of multiple cookies without re-checking hardware state.
 */
अटल अंतरभूत क्रमागत dma_status dma_async_is_tx_complete(काष्ठा dma_chan *chan,
	dma_cookie_t cookie, dma_cookie_t *last, dma_cookie_t *used)
अणु
	काष्ठा dma_tx_state state;
	क्रमागत dma_status status;

	status = chan->device->device_tx_status(chan, cookie, &state);
	अगर (last)
		*last = state.last;
	अगर (used)
		*used = state.used;
	वापस status;
पूर्ण

/**
 * dma_async_is_complete - test a cookie against chan state
 * @cookie: transaction identअगरier to test status of
 * @last_complete: last know completed transaction
 * @last_used: last cookie value handed out
 *
 * dma_async_is_complete() is used in dma_async_is_tx_complete()
 * the test logic is separated क्रम lightweight testing of multiple cookies
 */
अटल अंतरभूत क्रमागत dma_status dma_async_is_complete(dma_cookie_t cookie,
			dma_cookie_t last_complete, dma_cookie_t last_used)
अणु
	अगर (last_complete <= last_used) अणु
		अगर ((cookie <= last_complete) || (cookie > last_used))
			वापस DMA_COMPLETE;
	पूर्ण अन्यथा अणु
		अगर ((cookie <= last_complete) && (cookie > last_used))
			वापस DMA_COMPLETE;
	पूर्ण
	वापस DMA_IN_PROGRESS;
पूर्ण

अटल अंतरभूत व्योम
dma_set_tx_state(काष्ठा dma_tx_state *st, dma_cookie_t last, dma_cookie_t used, u32 residue)
अणु
	अगर (!st)
		वापस;

	st->last = last;
	st->used = used;
	st->residue = residue;
पूर्ण

#अगर_घोषित CONFIG_DMA_ENGINE
काष्ठा dma_chan *dma_find_channel(क्रमागत dma_transaction_type tx_type);
क्रमागत dma_status dma_sync_रुको(काष्ठा dma_chan *chan, dma_cookie_t cookie);
क्रमागत dma_status dma_रुको_क्रम_async_tx(काष्ठा dma_async_tx_descriptor *tx);
व्योम dma_issue_pending_all(व्योम);
काष्ठा dma_chan *__dma_request_channel(स्थिर dma_cap_mask_t *mask,
				       dma_filter_fn fn, व्योम *fn_param,
				       काष्ठा device_node *np);

काष्ठा dma_chan *dma_request_chan(काष्ठा device *dev, स्थिर अक्षर *name);
काष्ठा dma_chan *dma_request_chan_by_mask(स्थिर dma_cap_mask_t *mask);

व्योम dma_release_channel(काष्ठा dma_chan *chan);
पूर्णांक dma_get_slave_caps(काष्ठा dma_chan *chan, काष्ठा dma_slave_caps *caps);
#अन्यथा
अटल अंतरभूत काष्ठा dma_chan *dma_find_channel(क्रमागत dma_transaction_type tx_type)
अणु
	वापस शून्य;
पूर्ण
अटल अंतरभूत क्रमागत dma_status dma_sync_रुको(काष्ठा dma_chan *chan, dma_cookie_t cookie)
अणु
	वापस DMA_COMPLETE;
पूर्ण
अटल अंतरभूत क्रमागत dma_status dma_रुको_क्रम_async_tx(काष्ठा dma_async_tx_descriptor *tx)
अणु
	वापस DMA_COMPLETE;
पूर्ण
अटल अंतरभूत व्योम dma_issue_pending_all(व्योम)
अणु
पूर्ण
अटल अंतरभूत काष्ठा dma_chan *__dma_request_channel(स्थिर dma_cap_mask_t *mask,
						     dma_filter_fn fn,
						     व्योम *fn_param,
						     काष्ठा device_node *np)
अणु
	वापस शून्य;
पूर्ण
अटल अंतरभूत काष्ठा dma_chan *dma_request_chan(काष्ठा device *dev,
						स्थिर अक्षर *name)
अणु
	वापस ERR_PTR(-ENODEV);
पूर्ण
अटल अंतरभूत काष्ठा dma_chan *dma_request_chan_by_mask(
						स्थिर dma_cap_mask_t *mask)
अणु
	वापस ERR_PTR(-ENODEV);
पूर्ण
अटल अंतरभूत व्योम dma_release_channel(काष्ठा dma_chan *chan)
अणु
पूर्ण
अटल अंतरभूत पूर्णांक dma_get_slave_caps(काष्ठा dma_chan *chan,
				     काष्ठा dma_slave_caps *caps)
अणु
	वापस -ENXIO;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक dmaengine_desc_set_reuse(काष्ठा dma_async_tx_descriptor *tx)
अणु
	काष्ठा dma_slave_caps caps;
	पूर्णांक ret;

	ret = dma_get_slave_caps(tx->chan, &caps);
	अगर (ret)
		वापस ret;

	अगर (!caps.descriptor_reuse)
		वापस -EPERM;

	tx->flags |= DMA_CTRL_REUSE;
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम dmaengine_desc_clear_reuse(काष्ठा dma_async_tx_descriptor *tx)
अणु
	tx->flags &= ~DMA_CTRL_REUSE;
पूर्ण

अटल अंतरभूत bool dmaengine_desc_test_reuse(काष्ठा dma_async_tx_descriptor *tx)
अणु
	वापस (tx->flags & DMA_CTRL_REUSE) == DMA_CTRL_REUSE;
पूर्ण

अटल अंतरभूत पूर्णांक dmaengine_desc_मुक्त(काष्ठा dma_async_tx_descriptor *desc)
अणु
	/* this is supported क्रम reusable desc, so check that */
	अगर (!dmaengine_desc_test_reuse(desc))
		वापस -EPERM;

	वापस desc->desc_मुक्त(desc);
पूर्ण

/* --- DMA device --- */

पूर्णांक dma_async_device_रेजिस्टर(काष्ठा dma_device *device);
पूर्णांक dmaenginem_async_device_रेजिस्टर(काष्ठा dma_device *device);
व्योम dma_async_device_unरेजिस्टर(काष्ठा dma_device *device);
पूर्णांक dma_async_device_channel_रेजिस्टर(काष्ठा dma_device *device,
				      काष्ठा dma_chan *chan);
व्योम dma_async_device_channel_unरेजिस्टर(काष्ठा dma_device *device,
					 काष्ठा dma_chan *chan);
व्योम dma_run_dependencies(काष्ठा dma_async_tx_descriptor *tx);
#घोषणा dma_request_channel(mask, x, y) \
	__dma_request_channel(&(mask), x, y, शून्य)

/* Deprecated, please use dma_request_chan() directly */
अटल अंतरभूत काष्ठा dma_chan * __deprecated
dma_request_slave_channel(काष्ठा device *dev, स्थिर अक्षर *name)
अणु
	काष्ठा dma_chan *ch = dma_request_chan(dev, name);

	वापस IS_ERR(ch) ? शून्य : ch;
पूर्ण

अटल अंतरभूत काष्ठा dma_chan
*dma_request_slave_channel_compat(स्थिर dma_cap_mask_t mask,
				  dma_filter_fn fn, व्योम *fn_param,
				  काष्ठा device *dev, स्थिर अक्षर *name)
अणु
	काष्ठा dma_chan *chan;

	chan = dma_request_slave_channel(dev, name);
	अगर (chan)
		वापस chan;

	अगर (!fn || !fn_param)
		वापस शून्य;

	वापस __dma_request_channel(&mask, fn, fn_param, शून्य);
पूर्ण

अटल अंतरभूत अक्षर *
dmaengine_get_direction_text(क्रमागत dma_transfer_direction dir)
अणु
	चयन (dir) अणु
	हाल DMA_DEV_TO_MEM:
		वापस "DEV_TO_MEM";
	हाल DMA_MEM_TO_DEV:
		वापस "MEM_TO_DEV";
	हाल DMA_MEM_TO_MEM:
		वापस "MEM_TO_MEM";
	हाल DMA_DEV_TO_DEV:
		वापस "DEV_TO_DEV";
	शेष:
		वापस "invalid";
	पूर्ण
पूर्ण

अटल अंतरभूत काष्ठा device *dmaengine_get_dma_device(काष्ठा dma_chan *chan)
अणु
	अगर (chan->dev->chan_dma_dev)
		वापस &chan->dev->device;

	वापस chan->device->dev;
पूर्ण

#पूर्ण_अगर /* DMAENGINE_H */
