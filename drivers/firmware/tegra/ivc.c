<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2014-2016, NVIDIA CORPORATION.  All rights reserved.
 */

#समावेश <soc/tegra/ivc.h>

#घोषणा TEGRA_IVC_ALIGN 64

/*
 * IVC channel reset protocol.
 *
 * Each end uses its tx_channel.state to indicate its synchronization state.
 */
क्रमागत tegra_ivc_state अणु
	/*
	 * This value is zero क्रम backwards compatibility with services that
	 * assume channels to be initially zeroed. Such channels are in an
	 * initially valid state, but cannot be asynchronously reset, and must
	 * मुख्यtain a valid state at all बार.
	 *
	 * The transmitting end can enter the established state from the sync or
	 * ack state when it observes the receiving endpoपूर्णांक in the ack or
	 * established state, indicating that has cleared the counters in our
	 * rx_channel.
	 */
	TEGRA_IVC_STATE_ESTABLISHED = 0,

	/*
	 * If an endpoपूर्णांक is observed in the sync state, the remote endpoपूर्णांक is
	 * allowed to clear the counters it owns asynchronously with respect to
	 * the current endpoपूर्णांक. Thereक्रमe, the current endpoपूर्णांक is no दीर्घer
	 * allowed to communicate.
	 */
	TEGRA_IVC_STATE_SYNC,

	/*
	 * When the transmitting end observes the receiving end in the sync
	 * state, it can clear the w_count and r_count and transition to the ack
	 * state. If the remote endpoपूर्णांक observes us in the ack state, it can
	 * वापस to the established state once it has cleared its counters.
	 */
	TEGRA_IVC_STATE_ACK
पूर्ण;

/*
 * This काष्ठाure is भागided पूर्णांकo two-cache aligned parts, the first is only
 * written through the tx.channel poपूर्णांकer, जबतक the second is only written
 * through the rx.channel poपूर्णांकer. This delineates ownership of the cache
 * lines, which is critical to perक्रमmance and necessary in non-cache coherent
 * implementations.
 */
काष्ठा tegra_ivc_header अणु
	जोड़ अणु
		काष्ठा अणु
			/* fields owned by the transmitting end */
			u32 count;
			u32 state;
		पूर्ण;

		u8 pad[TEGRA_IVC_ALIGN];
	पूर्ण tx;

	जोड़ अणु
		/* fields owned by the receiving end */
		u32 count;
		u8 pad[TEGRA_IVC_ALIGN];
	पूर्ण rx;
पूर्ण;

अटल अंतरभूत व्योम tegra_ivc_invalidate(काष्ठा tegra_ivc *ivc, dma_addr_t phys)
अणु
	अगर (!ivc->peer)
		वापस;

	dma_sync_single_क्रम_cpu(ivc->peer, phys, TEGRA_IVC_ALIGN,
				DMA_FROM_DEVICE);
पूर्ण

अटल अंतरभूत व्योम tegra_ivc_flush(काष्ठा tegra_ivc *ivc, dma_addr_t phys)
अणु
	अगर (!ivc->peer)
		वापस;

	dma_sync_single_क्रम_device(ivc->peer, phys, TEGRA_IVC_ALIGN,
				   DMA_TO_DEVICE);
पूर्ण

अटल अंतरभूत bool tegra_ivc_empty(काष्ठा tegra_ivc *ivc,
				   काष्ठा tegra_ivc_header *header)
अणु
	/*
	 * This function perक्रमms multiple checks on the same values with
	 * security implications, so create snapshots with READ_ONCE() to
	 * ensure that these checks use the same values.
	 */
	u32 tx = READ_ONCE(header->tx.count);
	u32 rx = READ_ONCE(header->rx.count);

	/*
	 * Perक्रमm an over-full check to prevent denial of service attacks
	 * where a server could be easily fooled पूर्णांकo believing that there's
	 * an extremely large number of frames पढ़ोy, since receivers are not
	 * expected to check क्रम full or over-full conditions.
	 *
	 * Although the channel isn't empty, this is an invalid हाल caused by
	 * a potentially malicious peer, so वापसing empty is safer, because
	 * it gives the impression that the channel has gone silent.
	 */
	अगर (tx - rx > ivc->num_frames)
		वापस true;

	वापस tx == rx;
पूर्ण

अटल अंतरभूत bool tegra_ivc_full(काष्ठा tegra_ivc *ivc,
				  काष्ठा tegra_ivc_header *header)
अणु
	u32 tx = READ_ONCE(header->tx.count);
	u32 rx = READ_ONCE(header->rx.count);

	/*
	 * Invalid हालs where the counters indicate that the queue is over
	 * capacity also appear full.
	 */
	वापस tx - rx >= ivc->num_frames;
पूर्ण

अटल अंतरभूत u32 tegra_ivc_available(काष्ठा tegra_ivc *ivc,
				      काष्ठा tegra_ivc_header *header)
अणु
	u32 tx = READ_ONCE(header->tx.count);
	u32 rx = READ_ONCE(header->rx.count);

	/*
	 * This function isn't expected to be used in scenarios where an
	 * over-full situation can lead to denial of service attacks. See the
	 * comment in tegra_ivc_empty() क्रम an explanation about special
	 * over-full considerations.
	 */
	वापस tx - rx;
पूर्ण

अटल अंतरभूत व्योम tegra_ivc_advance_tx(काष्ठा tegra_ivc *ivc)
अणु
	WRITE_ONCE(ivc->tx.channel->tx.count,
		   READ_ONCE(ivc->tx.channel->tx.count) + 1);

	अगर (ivc->tx.position == ivc->num_frames - 1)
		ivc->tx.position = 0;
	अन्यथा
		ivc->tx.position++;
पूर्ण

अटल अंतरभूत व्योम tegra_ivc_advance_rx(काष्ठा tegra_ivc *ivc)
अणु
	WRITE_ONCE(ivc->rx.channel->rx.count,
		   READ_ONCE(ivc->rx.channel->rx.count) + 1);

	अगर (ivc->rx.position == ivc->num_frames - 1)
		ivc->rx.position = 0;
	अन्यथा
		ivc->rx.position++;
पूर्ण

अटल अंतरभूत पूर्णांक tegra_ivc_check_पढ़ो(काष्ठा tegra_ivc *ivc)
अणु
	अचिन्हित पूर्णांक offset = दुरत्व(काष्ठा tegra_ivc_header, tx.count);

	/*
	 * tx.channel->state is set locally, so it is not synchronized with
	 * state from the remote peer. The remote peer cannot reset its
	 * transmit counters until we've acknowledged its synchronization
	 * request, so no additional synchronization is required because an
	 * asynchronous transition of rx.channel->state to
	 * TEGRA_IVC_STATE_ACK is not allowed.
	 */
	अगर (ivc->tx.channel->tx.state != TEGRA_IVC_STATE_ESTABLISHED)
		वापस -ECONNRESET;

	/*
	 * Aव्योम unnecessary invalidations when perक्रमming repeated accesses
	 * to an IVC channel by checking the old queue poपूर्णांकers first.
	 *
	 * Synchronization is only necessary when these poपूर्णांकers indicate
	 * empty or full.
	 */
	अगर (!tegra_ivc_empty(ivc, ivc->rx.channel))
		वापस 0;

	tegra_ivc_invalidate(ivc, ivc->rx.phys + offset);

	अगर (tegra_ivc_empty(ivc, ivc->rx.channel))
		वापस -ENOSPC;

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक tegra_ivc_check_ग_लिखो(काष्ठा tegra_ivc *ivc)
अणु
	अचिन्हित पूर्णांक offset = दुरत्व(काष्ठा tegra_ivc_header, rx.count);

	अगर (ivc->tx.channel->tx.state != TEGRA_IVC_STATE_ESTABLISHED)
		वापस -ECONNRESET;

	अगर (!tegra_ivc_full(ivc, ivc->tx.channel))
		वापस 0;

	tegra_ivc_invalidate(ivc, ivc->tx.phys + offset);

	अगर (tegra_ivc_full(ivc, ivc->tx.channel))
		वापस -ENOSPC;

	वापस 0;
पूर्ण

अटल व्योम *tegra_ivc_frame_virt(काष्ठा tegra_ivc *ivc,
				  काष्ठा tegra_ivc_header *header,
				  अचिन्हित पूर्णांक frame)
अणु
	अगर (WARN_ON(frame >= ivc->num_frames))
		वापस ERR_PTR(-EINVAL);

	वापस (व्योम *)(header + 1) + ivc->frame_size * frame;
पूर्ण

अटल अंतरभूत dma_addr_t tegra_ivc_frame_phys(काष्ठा tegra_ivc *ivc,
					      dma_addr_t phys,
					      अचिन्हित पूर्णांक frame)
अणु
	अचिन्हित दीर्घ offset;

	offset = माप(काष्ठा tegra_ivc_header) + ivc->frame_size * frame;

	वापस phys + offset;
पूर्ण

अटल अंतरभूत व्योम tegra_ivc_invalidate_frame(काष्ठा tegra_ivc *ivc,
					      dma_addr_t phys,
					      अचिन्हित पूर्णांक frame,
					      अचिन्हित पूर्णांक offset,
					      माप_प्रकार size)
अणु
	अगर (!ivc->peer || WARN_ON(frame >= ivc->num_frames))
		वापस;

	phys = tegra_ivc_frame_phys(ivc, phys, frame) + offset;

	dma_sync_single_क्रम_cpu(ivc->peer, phys, size, DMA_FROM_DEVICE);
पूर्ण

अटल अंतरभूत व्योम tegra_ivc_flush_frame(काष्ठा tegra_ivc *ivc,
					 dma_addr_t phys,
					 अचिन्हित पूर्णांक frame,
					 अचिन्हित पूर्णांक offset,
					 माप_प्रकार size)
अणु
	अगर (!ivc->peer || WARN_ON(frame >= ivc->num_frames))
		वापस;

	phys = tegra_ivc_frame_phys(ivc, phys, frame) + offset;

	dma_sync_single_क्रम_device(ivc->peer, phys, size, DMA_TO_DEVICE);
पूर्ण

/* directly peek at the next frame rx'ed */
व्योम *tegra_ivc_पढ़ो_get_next_frame(काष्ठा tegra_ivc *ivc)
अणु
	पूर्णांक err;

	अगर (WARN_ON(ivc == शून्य))
		वापस ERR_PTR(-EINVAL);

	err = tegra_ivc_check_पढ़ो(ivc);
	अगर (err < 0)
		वापस ERR_PTR(err);

	/*
	 * Order observation of ivc->rx.position potentially indicating new
	 * data beक्रमe data पढ़ो.
	 */
	smp_rmb();

	tegra_ivc_invalidate_frame(ivc, ivc->rx.phys, ivc->rx.position, 0,
				   ivc->frame_size);

	वापस tegra_ivc_frame_virt(ivc, ivc->rx.channel, ivc->rx.position);
पूर्ण
EXPORT_SYMBOL(tegra_ivc_पढ़ो_get_next_frame);

पूर्णांक tegra_ivc_पढ़ो_advance(काष्ठा tegra_ivc *ivc)
अणु
	अचिन्हित पूर्णांक rx = दुरत्व(काष्ठा tegra_ivc_header, rx.count);
	अचिन्हित पूर्णांक tx = दुरत्व(काष्ठा tegra_ivc_header, tx.count);
	पूर्णांक err;

	/*
	 * No पढ़ो barriers or synchronization here: the caller is expected to
	 * have alपढ़ोy observed the channel non-empty. This check is just to
	 * catch programming errors.
	 */
	err = tegra_ivc_check_पढ़ो(ivc);
	अगर (err < 0)
		वापस err;

	tegra_ivc_advance_rx(ivc);

	tegra_ivc_flush(ivc, ivc->rx.phys + rx);

	/*
	 * Ensure our ग_लिखो to ivc->rx.position occurs beक्रमe our पढ़ो from
	 * ivc->tx.position.
	 */
	smp_mb();

	/*
	 * Notअगरy only upon transition from full to non-full. The available
	 * count can only asynchronously increase, so the worst possible
	 * side-effect will be a spurious notअगरication.
	 */
	tegra_ivc_invalidate(ivc, ivc->rx.phys + tx);

	अगर (tegra_ivc_available(ivc, ivc->rx.channel) == ivc->num_frames - 1)
		ivc->notअगरy(ivc, ivc->notअगरy_data);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(tegra_ivc_पढ़ो_advance);

/* directly poke at the next frame to be tx'ed */
व्योम *tegra_ivc_ग_लिखो_get_next_frame(काष्ठा tegra_ivc *ivc)
अणु
	पूर्णांक err;

	err = tegra_ivc_check_ग_लिखो(ivc);
	अगर (err < 0)
		वापस ERR_PTR(err);

	वापस tegra_ivc_frame_virt(ivc, ivc->tx.channel, ivc->tx.position);
पूर्ण
EXPORT_SYMBOL(tegra_ivc_ग_लिखो_get_next_frame);

/* advance the tx buffer */
पूर्णांक tegra_ivc_ग_लिखो_advance(काष्ठा tegra_ivc *ivc)
अणु
	अचिन्हित पूर्णांक tx = दुरत्व(काष्ठा tegra_ivc_header, tx.count);
	अचिन्हित पूर्णांक rx = दुरत्व(काष्ठा tegra_ivc_header, rx.count);
	पूर्णांक err;

	err = tegra_ivc_check_ग_लिखो(ivc);
	अगर (err < 0)
		वापस err;

	tegra_ivc_flush_frame(ivc, ivc->tx.phys, ivc->tx.position, 0,
			      ivc->frame_size);

	/*
	 * Order any possible stores to the frame beक्रमe update of
	 * ivc->tx.position.
	 */
	smp_wmb();

	tegra_ivc_advance_tx(ivc);
	tegra_ivc_flush(ivc, ivc->tx.phys + tx);

	/*
	 * Ensure our ग_लिखो to ivc->tx.position occurs beक्रमe our पढ़ो from
	 * ivc->rx.position.
	 */
	smp_mb();

	/*
	 * Notअगरy only upon transition from empty to non-empty. The available
	 * count can only asynchronously decrease, so the worst possible
	 * side-effect will be a spurious notअगरication.
	 */
	tegra_ivc_invalidate(ivc, ivc->tx.phys + rx);

	अगर (tegra_ivc_available(ivc, ivc->tx.channel) == 1)
		ivc->notअगरy(ivc, ivc->notअगरy_data);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(tegra_ivc_ग_लिखो_advance);

व्योम tegra_ivc_reset(काष्ठा tegra_ivc *ivc)
अणु
	अचिन्हित पूर्णांक offset = दुरत्व(काष्ठा tegra_ivc_header, tx.count);

	ivc->tx.channel->tx.state = TEGRA_IVC_STATE_SYNC;
	tegra_ivc_flush(ivc, ivc->tx.phys + offset);
	ivc->notअगरy(ivc, ivc->notअगरy_data);
पूर्ण
EXPORT_SYMBOL(tegra_ivc_reset);

/*
 * =======================================================
 *  IVC State Transition Table - see tegra_ivc_notअगरied()
 * =======================================================
 *
 *	local	remote	action
 *	-----	------	-----------------------------------
 *	SYNC	EST	<none>
 *	SYNC	ACK	reset counters; move to EST; notअगरy
 *	SYNC	SYNC	reset counters; move to ACK; notअगरy
 *	ACK	EST	move to EST; notअगरy
 *	ACK	ACK	move to EST; notअगरy
 *	ACK	SYNC	reset counters; move to ACK; notअगरy
 *	EST	EST	<none>
 *	EST	ACK	<none>
 *	EST	SYNC	reset counters; move to ACK; notअगरy
 *
 * ===============================================================
 */

पूर्णांक tegra_ivc_notअगरied(काष्ठा tegra_ivc *ivc)
अणु
	अचिन्हित पूर्णांक offset = दुरत्व(काष्ठा tegra_ivc_header, tx.count);
	क्रमागत tegra_ivc_state state;

	/* Copy the receiver's state out of shared memory. */
	tegra_ivc_invalidate(ivc, ivc->rx.phys + offset);
	state = READ_ONCE(ivc->rx.channel->tx.state);

	अगर (state == TEGRA_IVC_STATE_SYNC) अणु
		offset = दुरत्व(काष्ठा tegra_ivc_header, tx.count);

		/*
		 * Order observation of TEGRA_IVC_STATE_SYNC beक्रमe stores
		 * clearing tx.channel.
		 */
		smp_rmb();

		/*
		 * Reset tx.channel counters. The remote end is in the SYNC
		 * state and won't make progress until we change our state,
		 * so the counters are not in use at this समय.
		 */
		ivc->tx.channel->tx.count = 0;
		ivc->rx.channel->rx.count = 0;

		ivc->tx.position = 0;
		ivc->rx.position = 0;

		/*
		 * Ensure that counters appear cleared beक्रमe new state can be
		 * observed.
		 */
		smp_wmb();

		/*
		 * Move to ACK state. We have just cleared our counters, so it
		 * is now safe क्रम the remote end to start using these values.
		 */
		ivc->tx.channel->tx.state = TEGRA_IVC_STATE_ACK;
		tegra_ivc_flush(ivc, ivc->tx.phys + offset);

		/*
		 * Notअगरy remote end to observe state transition.
		 */
		ivc->notअगरy(ivc, ivc->notअगरy_data);

	पूर्ण अन्यथा अगर (ivc->tx.channel->tx.state == TEGRA_IVC_STATE_SYNC &&
		   state == TEGRA_IVC_STATE_ACK) अणु
		offset = दुरत्व(काष्ठा tegra_ivc_header, tx.count);

		/*
		 * Order observation of ivc_state_sync beक्रमe stores clearing
		 * tx_channel.
		 */
		smp_rmb();

		/*
		 * Reset tx.channel counters. The remote end is in the ACK
		 * state and won't make progress until we change our state,
		 * so the counters are not in use at this समय.
		 */
		ivc->tx.channel->tx.count = 0;
		ivc->rx.channel->rx.count = 0;

		ivc->tx.position = 0;
		ivc->rx.position = 0;

		/*
		 * Ensure that counters appear cleared beक्रमe new state can be
		 * observed.
		 */
		smp_wmb();

		/*
		 * Move to ESTABLISHED state. We know that the remote end has
		 * alपढ़ोy cleared its counters, so it is safe to start
		 * writing/पढ़ोing on this channel.
		 */
		ivc->tx.channel->tx.state = TEGRA_IVC_STATE_ESTABLISHED;
		tegra_ivc_flush(ivc, ivc->tx.phys + offset);

		/*
		 * Notअगरy remote end to observe state transition.
		 */
		ivc->notअगरy(ivc, ivc->notअगरy_data);

	पूर्ण अन्यथा अगर (ivc->tx.channel->tx.state == TEGRA_IVC_STATE_ACK) अणु
		offset = दुरत्व(काष्ठा tegra_ivc_header, tx.count);

		/*
		 * At this poपूर्णांक, we have observed the peer to be in either
		 * the ACK or ESTABLISHED state. Next, order observation of
		 * peer state beक्रमe storing to tx.channel.
		 */
		smp_rmb();

		/*
		 * Move to ESTABLISHED state. We know that we have previously
		 * cleared our counters, and we know that the remote end has
		 * cleared its counters, so it is safe to start writing/पढ़ोing
		 * on this channel.
		 */
		ivc->tx.channel->tx.state = TEGRA_IVC_STATE_ESTABLISHED;
		tegra_ivc_flush(ivc, ivc->tx.phys + offset);

		/*
		 * Notअगरy remote end to observe state transition.
		 */
		ivc->notअगरy(ivc, ivc->notअगरy_data);

	पूर्ण अन्यथा अणु
		/*
		 * There is no need to handle any further action. Either the
		 * channel is alपढ़ोy fully established, or we are रुकोing क्रम
		 * the remote end to catch up with our current state. Refer
		 * to the diagram in "IVC State Transition Table" above.
		 */
	पूर्ण

	अगर (ivc->tx.channel->tx.state != TEGRA_IVC_STATE_ESTABLISHED)
		वापस -EAGAIN;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(tegra_ivc_notअगरied);

माप_प्रकार tegra_ivc_align(माप_प्रकार size)
अणु
	वापस ALIGN(size, TEGRA_IVC_ALIGN);
पूर्ण
EXPORT_SYMBOL(tegra_ivc_align);

अचिन्हित tegra_ivc_total_queue_size(अचिन्हित queue_size)
अणु
	अगर (!IS_ALIGNED(queue_size, TEGRA_IVC_ALIGN)) अणु
		pr_err("%s: queue_size (%u) must be %u-byte aligned\n",
		       __func__, queue_size, TEGRA_IVC_ALIGN);
		वापस 0;
	पूर्ण

	वापस queue_size + माप(काष्ठा tegra_ivc_header);
पूर्ण
EXPORT_SYMBOL(tegra_ivc_total_queue_size);

अटल पूर्णांक tegra_ivc_check_params(अचिन्हित दीर्घ rx, अचिन्हित दीर्घ tx,
				  अचिन्हित पूर्णांक num_frames, माप_प्रकार frame_size)
अणु
	BUILD_BUG_ON(!IS_ALIGNED(दुरत्व(काष्ठा tegra_ivc_header, tx.count),
				 TEGRA_IVC_ALIGN));
	BUILD_BUG_ON(!IS_ALIGNED(दुरत्व(काष्ठा tegra_ivc_header, rx.count),
				 TEGRA_IVC_ALIGN));
	BUILD_BUG_ON(!IS_ALIGNED(माप(काष्ठा tegra_ivc_header),
				 TEGRA_IVC_ALIGN));

	अगर ((uपूर्णांक64_t)num_frames * (uपूर्णांक64_t)frame_size >= 0x100000000UL) अणु
		pr_err("num_frames * frame_size overflows\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!IS_ALIGNED(frame_size, TEGRA_IVC_ALIGN)) अणु
		pr_err("frame size not adequately aligned: %zu\n", frame_size);
		वापस -EINVAL;
	पूर्ण

	/*
	 * The headers must at least be aligned enough क्रम counters
	 * to be accessed atomically.
	 */
	अगर (!IS_ALIGNED(rx, TEGRA_IVC_ALIGN)) अणु
		pr_err("IVC channel start not aligned: %#lx\n", rx);
		वापस -EINVAL;
	पूर्ण

	अगर (!IS_ALIGNED(tx, TEGRA_IVC_ALIGN)) अणु
		pr_err("IVC channel start not aligned: %#lx\n", tx);
		वापस -EINVAL;
	पूर्ण

	अगर (rx < tx) अणु
		अगर (rx + frame_size * num_frames > tx) अणु
			pr_err("queue regions overlap: %#lx + %zx > %#lx\n",
			       rx, frame_size * num_frames, tx);
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (tx + frame_size * num_frames > rx) अणु
			pr_err("queue regions overlap: %#lx + %zx > %#lx\n",
			       tx, frame_size * num_frames, rx);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक tegra_ivc_init(काष्ठा tegra_ivc *ivc, काष्ठा device *peer, व्योम *rx,
		   dma_addr_t rx_phys, व्योम *tx, dma_addr_t tx_phys,
		   अचिन्हित पूर्णांक num_frames, माप_प्रकार frame_size,
		   व्योम (*notअगरy)(काष्ठा tegra_ivc *ivc, व्योम *data),
		   व्योम *data)
अणु
	माप_प्रकार queue_size;
	पूर्णांक err;

	अगर (WARN_ON(!ivc || !notअगरy))
		वापस -EINVAL;

	/*
	 * All sizes that can be वापसed by communication functions should
	 * fit in an पूर्णांक.
	 */
	अगर (frame_size > पूर्णांक_उच्च)
		वापस -E2BIG;

	err = tegra_ivc_check_params((अचिन्हित दीर्घ)rx, (अचिन्हित दीर्घ)tx,
				     num_frames, frame_size);
	अगर (err < 0)
		वापस err;

	queue_size = tegra_ivc_total_queue_size(num_frames * frame_size);

	अगर (peer) अणु
		ivc->rx.phys = dma_map_single(peer, rx, queue_size,
					      DMA_BIसूचीECTIONAL);
		अगर (dma_mapping_error(peer, ivc->rx.phys))
			वापस -ENOMEM;

		ivc->tx.phys = dma_map_single(peer, tx, queue_size,
					      DMA_BIसूचीECTIONAL);
		अगर (dma_mapping_error(peer, ivc->tx.phys)) अणु
			dma_unmap_single(peer, ivc->rx.phys, queue_size,
					 DMA_BIसूचीECTIONAL);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण अन्यथा अणु
		ivc->rx.phys = rx_phys;
		ivc->tx.phys = tx_phys;
	पूर्ण

	ivc->rx.channel = rx;
	ivc->tx.channel = tx;
	ivc->peer = peer;
	ivc->notअगरy = notअगरy;
	ivc->notअगरy_data = data;
	ivc->frame_size = frame_size;
	ivc->num_frames = num_frames;

	/*
	 * These values aren't necessarily correct until the channel has been
	 * reset.
	 */
	ivc->tx.position = 0;
	ivc->rx.position = 0;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(tegra_ivc_init);

व्योम tegra_ivc_cleanup(काष्ठा tegra_ivc *ivc)
अणु
	अगर (ivc->peer) अणु
		माप_प्रकार size = tegra_ivc_total_queue_size(ivc->num_frames *
							 ivc->frame_size);

		dma_unmap_single(ivc->peer, ivc->rx.phys, size,
				 DMA_BIसूचीECTIONAL);
		dma_unmap_single(ivc->peer, ivc->tx.phys, size,
				 DMA_BIसूचीECTIONAL);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(tegra_ivc_cleanup);
