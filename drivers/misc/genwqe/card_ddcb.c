<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * IBM Accelerator Family 'GenWQE'
 *
 * (C) Copyright IBM Corp. 2013
 *
 * Author: Frank Haverkamp <haver@linux.vnet.ibm.com>
 * Author: Joerg-Stephan Vogt <jsvogt@de.ibm.com>
 * Author: Michael Jung <mijung@gmx.net>
 * Author: Michael Ruettger <michael@ibmra.de>
 */

/*
 * Device Driver Control Block (DDCB) queue support. Definition of
 * पूर्णांकerrupt handlers क्रम queue support as well as triggering the
 * health monitor code in हाल of problems. The current hardware uses
 * an MSI पूर्णांकerrupt which is shared between error handling and
 * functional code.
 */

#समावेश <linux/types.h>
#समावेश <linux/sched.h>
#समावेश <linux/रुको.h>
#समावेश <linux/pci.h>
#समावेश <linux/माला.स>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/crc-itu-t.h>

#समावेश "card_base.h"
#समावेश "card_ddcb.h"

/*
 * N: next DDCB, this is where the next DDCB will be put.
 * A: active DDCB, this is where the code will look क्रम the next completion.
 * x: DDCB is enqueued, we are रुकोing क्रम its completion.

 * Situation (1): Empty queue
 *  +---+---+---+---+---+---+---+---+
 *  | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
 *  |   |   |   |   |   |   |   |   |
 *  +---+---+---+---+---+---+---+---+
 *           A/N
 *  enqueued_ddcbs = A - N = 2 - 2 = 0
 *
 * Situation (2): Wrapped, N > A
 *  +---+---+---+---+---+---+---+---+
 *  | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
 *  |   |   | x | x |   |   |   |   |
 *  +---+---+---+---+---+---+---+---+
 *            A       N
 *  enqueued_ddcbs = N - A = 4 - 2 = 2
 *
 * Situation (3): Queue wrapped, A > N
 *  +---+---+---+---+---+---+---+---+
 *  | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
 *  | x | x |   |   | x | x | x | x |
 *  +---+---+---+---+---+---+---+---+
 *            N       A
 *  enqueued_ddcbs = queue_max  - (A - N) = 8 - (4 - 2) = 6
 *
 * Situation (4a): Queue full N > A
 *  +---+---+---+---+---+---+---+---+
 *  | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
 *  | x | x | x | x | x | x | x |   |
 *  +---+---+---+---+---+---+---+---+
 *    A                           N
 *
 *  enqueued_ddcbs = N - A = 7 - 0 = 7
 *
 * Situation (4a): Queue full A > N
 *  +---+---+---+---+---+---+---+---+
 *  | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
 *  | x | x | x |   | x | x | x | x |
 *  +---+---+---+---+---+---+---+---+
 *                N   A
 *  enqueued_ddcbs = queue_max - (A - N) = 8 - (4 - 3) = 7
 */

अटल पूर्णांक queue_empty(काष्ठा ddcb_queue *queue)
अणु
	वापस queue->ddcb_next == queue->ddcb_act;
पूर्ण

अटल पूर्णांक queue_enqueued_ddcbs(काष्ठा ddcb_queue *queue)
अणु
	अगर (queue->ddcb_next >= queue->ddcb_act)
		वापस queue->ddcb_next - queue->ddcb_act;

	वापस queue->ddcb_max - (queue->ddcb_act - queue->ddcb_next);
पूर्ण

अटल पूर्णांक queue_मुक्त_ddcbs(काष्ठा ddcb_queue *queue)
अणु
	पूर्णांक मुक्त_ddcbs = queue->ddcb_max - queue_enqueued_ddcbs(queue) - 1;

	अगर (WARN_ON_ONCE(मुक्त_ddcbs < 0)) अणु /* must never ever happen! */
		वापस 0;
	पूर्ण
	वापस मुक्त_ddcbs;
पूर्ण

/*
 * Use of the PRIV field in the DDCB क्रम queue debugging:
 *
 * (1) Trying to get rid of a DDCB which saw a समयout:
 *     pddcb->priv[6] = 0xcc;   # cleared
 *
 * (2) Append a DDCB via NEXT bit:
 *     pddcb->priv[7] = 0xaa;	# appended
 *
 * (3) DDCB needed tapping:
 *     pddcb->priv[7] = 0xbb;   # tapped
 *
 * (4) DDCB marked as correctly finished:
 *     pddcb->priv[6] = 0xff;	# finished
 */

अटल अंतरभूत व्योम ddcb_mark_tapped(काष्ठा ddcb *pddcb)
अणु
	pddcb->priv[7] = 0xbb;  /* tapped */
पूर्ण

अटल अंतरभूत व्योम ddcb_mark_appended(काष्ठा ddcb *pddcb)
अणु
	pddcb->priv[7] = 0xaa;	/* appended */
पूर्ण

अटल अंतरभूत व्योम ddcb_mark_cleared(काष्ठा ddcb *pddcb)
अणु
	pddcb->priv[6] = 0xcc; /* cleared */
पूर्ण

अटल अंतरभूत व्योम ddcb_mark_finished(काष्ठा ddcb *pddcb)
अणु
	pddcb->priv[6] = 0xff;	/* finished */
पूर्ण

अटल अंतरभूत व्योम ddcb_mark_unused(काष्ठा ddcb *pddcb)
अणु
	pddcb->priv_64 = cpu_to_be64(0); /* not tapped */
पूर्ण

/**
 * genwqe_crc16() - Generate 16-bit crc as required क्रम DDCBs
 * @buff:       poपूर्णांकer to data buffer
 * @len:        length of data क्रम calculation
 * @init:       initial crc (0xffff at start)
 *
 * Polynomial = x^16 + x^12 + x^5 + 1   (0x1021)
 * Example: 4 bytes 0x01 0x02 0x03 0x04 with init = 0xffff
 *          should result in a crc16 of 0x89c3
 *
 * Return: crc16 checksum in big endian क्रमmat !
 */
अटल अंतरभूत u16 genwqe_crc16(स्थिर u8 *buff, माप_प्रकार len, u16 init)
अणु
	वापस crc_itu_t(init, buff, len);
पूर्ण

अटल व्योम prपूर्णांक_ddcb_info(काष्ठा genwqe_dev *cd, काष्ठा ddcb_queue *queue)
अणु
	पूर्णांक i;
	काष्ठा ddcb *pddcb;
	अचिन्हित दीर्घ flags;
	काष्ठा pci_dev *pci_dev = cd->pci_dev;

	spin_lock_irqsave(&cd->prपूर्णांक_lock, flags);

	dev_info(&pci_dev->dev,
		 "DDCB list for card #%d (ddcb_act=%d / ddcb_next=%d):\n",
		 cd->card_idx, queue->ddcb_act, queue->ddcb_next);

	pddcb = queue->ddcb_vaddr;
	क्रम (i = 0; i < queue->ddcb_max; i++) अणु
		dev_err(&pci_dev->dev,
			"  %c %-3d: RETC=%03x SEQ=%04x HSI=%02X SHI=%02x PRIV=%06llx CMD=%03x\n",
			i == queue->ddcb_act ? '>' : ' ',
			i,
			be16_to_cpu(pddcb->retc_16),
			be16_to_cpu(pddcb->seqnum_16),
			pddcb->hsi,
			pddcb->shi,
			be64_to_cpu(pddcb->priv_64),
			pddcb->cmd);
		pddcb++;
	पूर्ण
	spin_unlock_irqrestore(&cd->prपूर्णांक_lock, flags);
पूर्ण

काष्ठा genwqe_ddcb_cmd *ddcb_requ_alloc(व्योम)
अणु
	काष्ठा ddcb_requ *req;

	req = kzalloc(माप(*req), GFP_KERNEL);
	अगर (!req)
		वापस शून्य;

	वापस &req->cmd;
पूर्ण

व्योम ddcb_requ_मुक्त(काष्ठा genwqe_ddcb_cmd *cmd)
अणु
	काष्ठा ddcb_requ *req = container_of(cmd, काष्ठा ddcb_requ, cmd);

	kमुक्त(req);
पूर्ण

अटल अंतरभूत क्रमागत genwqe_requ_state ddcb_requ_get_state(काष्ठा ddcb_requ *req)
अणु
	वापस req->req_state;
पूर्ण

अटल अंतरभूत व्योम ddcb_requ_set_state(काष्ठा ddcb_requ *req,
				       क्रमागत genwqe_requ_state new_state)
अणु
	req->req_state = new_state;
पूर्ण

अटल अंतरभूत पूर्णांक ddcb_requ_collect_debug_data(काष्ठा ddcb_requ *req)
अणु
	वापस req->cmd.ddata_addr != 0x0;
पूर्ण

/**
 * ddcb_requ_finished() - Returns the hardware state of the associated DDCB
 * @cd:          poपूर्णांकer to genwqe device descriptor
 * @req:         DDCB work request
 *
 * Status of ddcb_requ mirrors this hardware state, but is copied in
 * the ddcb_requ on पूर्णांकerrupt/polling function. The lowlevel code
 * should check the hardware state directly, the higher level code
 * should check the copy.
 *
 * This function will also वापस true अगर the state of the queue is
 * not GENWQE_CARD_USED. This enables us to purge all DDCBs in the
 * shutकरोwn हाल.
 */
अटल पूर्णांक ddcb_requ_finished(काष्ठा genwqe_dev *cd, काष्ठा ddcb_requ *req)
अणु
	वापस (ddcb_requ_get_state(req) == GENWQE_REQU_FINISHED) ||
		(cd->card_state != GENWQE_CARD_USED);
पूर्ण

#घोषणा RET_DDCB_APPENDED 1
#घोषणा RET_DDCB_TAPPED   2
/**
 * enqueue_ddcb() - Enqueue a DDCB
 * @cd:         poपूर्णांकer to genwqe device descriptor
 * @queue:	queue this operation should be करोne on
 * @pddcb:      poपूर्णांकer to ddcb काष्ठाure
 * @ddcb_no:    poपूर्णांकer to ddcb number being tapped
 *
 * Start execution of DDCB by tapping or append to queue via NEXT
 * bit. This is करोne by an atomic 'compare and swap' inकाष्ठाion and
 * checking SHI and HSI of the previous DDCB.
 *
 * This function must only be called with ddcb_lock held.
 *
 * Return: 1 अगर new DDCB is appended to previous
 *         2 अगर DDCB queue is tapped via रेजिस्टर/simulation
 */
अटल पूर्णांक enqueue_ddcb(काष्ठा genwqe_dev *cd, काष्ठा ddcb_queue *queue,
			काष्ठा ddcb *pddcb, पूर्णांक ddcb_no)
अणु
	अचिन्हित पूर्णांक try;
	पूर्णांक prev_no;
	काष्ठा ddcb *prev_ddcb;
	__be32 old, new, icrc_hsi_shi;
	u64 num;

	/*
	 * For perक्रमmance checks a Dispatch Timestamp can be put पूर्णांकo
	 * DDCB It is supposed to use the SLU's मुक्त running counter,
	 * but this requires PCIe cycles.
	 */
	ddcb_mark_unused(pddcb);

	/* check previous DDCB अगर alपढ़ोy fetched */
	prev_no = (ddcb_no == 0) ? queue->ddcb_max - 1 : ddcb_no - 1;
	prev_ddcb = &queue->ddcb_vaddr[prev_no];

	/*
	 * It might have happened that the HSI.FETCHED bit is
	 * set. Retry in this हाल. Thereक्रमe I expect maximum 2 बार
	 * trying.
	 */
	ddcb_mark_appended(pddcb);
	क्रम (try = 0; try < 2; try++) अणु
		old = prev_ddcb->icrc_hsi_shi_32; /* पढ़ो SHI/HSI in BE32 */

		/* try to append via NEXT bit अगर prev DDCB is not completed */
		अगर ((old & DDCB_COMPLETED_BE32) != 0x00000000)
			अवरोध;

		new = (old | DDCB_NEXT_BE32);

		wmb();		/* need to ensure ग_लिखो ordering */
		icrc_hsi_shi = cmpxchg(&prev_ddcb->icrc_hsi_shi_32, old, new);

		अगर (icrc_hsi_shi == old)
			वापस RET_DDCB_APPENDED; /* appended to queue */
	पूर्ण

	/* Queue must be re-started by updating QUEUE_OFFSET */
	ddcb_mark_tapped(pddcb);
	num = (u64)ddcb_no << 8;

	wmb();			/* need to ensure ग_लिखो ordering */
	__genwqe_ग_लिखोq(cd, queue->IO_QUEUE_OFFSET, num); /* start queue */

	वापस RET_DDCB_TAPPED;
पूर्ण

/**
 * copy_ddcb_results() - Copy output state from real DDCB to request
 * @req:        poपूर्णांकer to requested DDCB parameters
 * @ddcb_no:    poपूर्णांकer to ddcb number being tapped
 *
 * Copy DDCB ASV to request काष्ठा. There is no endian
 * conversion made, since data काष्ठाure in ASV is still
 * unknown here.
 *
 * This is needed by:
 *   - genwqe_purge_ddcb()
 *   - genwqe_check_ddcb_queue()
 */
अटल व्योम copy_ddcb_results(काष्ठा ddcb_requ *req, पूर्णांक ddcb_no)
अणु
	काष्ठा ddcb_queue *queue = req->queue;
	काष्ठा ddcb *pddcb = &queue->ddcb_vaddr[req->num];

	स_नकल(&req->cmd.asv[0], &pddcb->asv[0], DDCB_ASV_LENGTH);

	/* copy status flags of the variant part */
	req->cmd.vcrc     = be16_to_cpu(pddcb->vcrc_16);
	req->cmd.deque_ts = be64_to_cpu(pddcb->deque_ts_64);
	req->cmd.cmplt_ts = be64_to_cpu(pddcb->cmplt_ts_64);

	req->cmd.attn     = be16_to_cpu(pddcb->attn_16);
	req->cmd.progress = be32_to_cpu(pddcb->progress_32);
	req->cmd.retc     = be16_to_cpu(pddcb->retc_16);

	अगर (ddcb_requ_collect_debug_data(req)) अणु
		पूर्णांक prev_no = (ddcb_no == 0) ?
			queue->ddcb_max - 1 : ddcb_no - 1;
		काष्ठा ddcb *prev_pddcb = &queue->ddcb_vaddr[prev_no];

		स_नकल(&req->debug_data.ddcb_finished, pddcb,
		       माप(req->debug_data.ddcb_finished));
		स_नकल(&req->debug_data.ddcb_prev, prev_pddcb,
		       माप(req->debug_data.ddcb_prev));
	पूर्ण
पूर्ण

/**
 * genwqe_check_ddcb_queue() - Checks DDCB queue क्रम completed work requests.
 * @cd:         poपूर्णांकer to genwqe device descriptor
 * @queue:	queue to be checked
 *
 * Return: Number of DDCBs which were finished
 */
अटल पूर्णांक genwqe_check_ddcb_queue(काष्ठा genwqe_dev *cd,
				   काष्ठा ddcb_queue *queue)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ddcbs_finished = 0;
	काष्ठा pci_dev *pci_dev = cd->pci_dev;

	spin_lock_irqsave(&queue->ddcb_lock, flags);

	/* FIXME aव्योम soft locking CPU */
	जबतक (!queue_empty(queue) && (ddcbs_finished < queue->ddcb_max)) अणु

		काष्ठा ddcb *pddcb;
		काष्ठा ddcb_requ *req;
		u16 vcrc, vcrc_16, retc_16;

		pddcb = &queue->ddcb_vaddr[queue->ddcb_act];

		अगर ((pddcb->icrc_hsi_shi_32 & DDCB_COMPLETED_BE32) ==
		    0x00000000)
			जाओ go_home; /* not completed, जारी रुकोing */

		wmb();  /*  Add sync to decouple prev. पढ़ो operations */

		/* Note: DDCB could be purged */
		req = queue->ddcb_req[queue->ddcb_act];
		अगर (req == शून्य) अणु
			/* this occurs अगर DDCB is purged, not an error */
			/* Move active DDCB further; Nothing to करो anymore. */
			जाओ pick_next_one;
		पूर्ण

		/*
		 * HSI=0x44 (fetched and completed), but RETC is
		 * 0x101, or even worse 0x000.
		 *
		 * In हाल of seeing the queue in inconsistent state
		 * we पढ़ो the errcnts and the queue status to provide
		 * a trigger क्रम our PCIe analyzer stop capturing.
		 */
		retc_16 = be16_to_cpu(pddcb->retc_16);
		अगर ((pddcb->hsi == 0x44) && (retc_16 <= 0x101)) अणु
			u64 errcnts, status;
			u64 ddcb_offs = (u64)pddcb - (u64)queue->ddcb_vaddr;

			errcnts = __genwqe_पढ़ोq(cd, queue->IO_QUEUE_ERRCNTS);
			status  = __genwqe_पढ़ोq(cd, queue->IO_QUEUE_STATUS);

			dev_err(&pci_dev->dev,
				"[%s] SEQN=%04x HSI=%02x RETC=%03x Q_ERRCNTS=%016llx Q_STATUS=%016llx DDCB_DMA_ADDR=%016llx\n",
				__func__, be16_to_cpu(pddcb->seqnum_16),
				pddcb->hsi, retc_16, errcnts, status,
				queue->ddcb_daddr + ddcb_offs);
		पूर्ण

		copy_ddcb_results(req, queue->ddcb_act);
		queue->ddcb_req[queue->ddcb_act] = शून्य; /* take from queue */

		dev_dbg(&pci_dev->dev, "FINISHED DDCB#%d\n", req->num);
		genwqe_hexdump(pci_dev, pddcb, माप(*pddcb));

		ddcb_mark_finished(pddcb);

		/* calculate CRC_16 to see अगर VCRC is correct */
		vcrc = genwqe_crc16(pddcb->asv,
				   VCRC_LENGTH(req->cmd.asv_length),
				   0xffff);
		vcrc_16 = be16_to_cpu(pddcb->vcrc_16);
		अगर (vcrc != vcrc_16) अणु
			prपूर्णांकk_ratelimited(KERN_ERR
				"%s %s: err: wrong VCRC pre=%02x vcrc_len=%d bytes vcrc_data=%04x is not vcrc_card=%04x\n",
				GENWQE_DEVNAME, dev_name(&pci_dev->dev),
				pddcb->pre, VCRC_LENGTH(req->cmd.asv_length),
				vcrc, vcrc_16);
		पूर्ण

		ddcb_requ_set_state(req, GENWQE_REQU_FINISHED);
		queue->ddcbs_completed++;
		queue->ddcbs_in_flight--;

		/* wake up process रुकोing क्रम this DDCB, and
                   processes on the busy queue */
		wake_up_पूर्णांकerruptible(&queue->ddcb_रुकोqs[queue->ddcb_act]);
		wake_up_पूर्णांकerruptible(&queue->busy_रुकोq);

pick_next_one:
		queue->ddcb_act = (queue->ddcb_act + 1) % queue->ddcb_max;
		ddcbs_finished++;
	पूर्ण

 go_home:
	spin_unlock_irqrestore(&queue->ddcb_lock, flags);
	वापस ddcbs_finished;
पूर्ण

/**
 * __genwqe_रुको_ddcb(): Waits until DDCB is completed
 * @cd:         poपूर्णांकer to genwqe device descriptor
 * @req:        poपूर्णांकer to requsted DDCB parameters
 *
 * The Service Layer will update the RETC in DDCB when processing is
 * pending or करोne.
 *
 * Return: > 0 reमुख्यing jअगरfies, DDCB completed
 *           -ETIMEDOUT	when समयout
 *           -ERESTARTSYS when ^C
 *           -EINVAL when unknown error condition
 *
 * When an error is वापसed the called needs to ensure that
 * purge_ddcb() is being called to get the &req हटाओd from the
 * queue.
 */
पूर्णांक __genwqe_रुको_ddcb(काष्ठा genwqe_dev *cd, काष्ठा ddcb_requ *req)
अणु
	पूर्णांक rc;
	अचिन्हित पूर्णांक ddcb_no;
	काष्ठा ddcb_queue *queue;
	काष्ठा pci_dev *pci_dev = cd->pci_dev;

	अगर (req == शून्य)
		वापस -EINVAL;

	queue = req->queue;
	अगर (queue == शून्य)
		वापस -EINVAL;

	ddcb_no = req->num;
	अगर (ddcb_no >= queue->ddcb_max)
		वापस -EINVAL;

	rc = रुको_event_पूर्णांकerruptible_समयout(queue->ddcb_रुकोqs[ddcb_no],
				ddcb_requ_finished(cd, req),
				GENWQE_DDCB_SOFTWARE_TIMEOUT * HZ);

	/*
	 * We need to distinguish 3 हालs here:
	 *   1. rc == 0              समयout occurred
	 *   2. rc == -ERESTARTSYS   संकेत received
	 *   3. rc > 0               reमुख्यing jअगरfies condition is true
	 */
	अगर (rc == 0) अणु
		काष्ठा ddcb_queue *queue = req->queue;
		काष्ठा ddcb *pddcb;

		/*
		 * Timeout may be caused by दीर्घ task चयनing समय.
		 * When समयout happens, check अगर the request has
		 * meanजबतक completed.
		 */
		genwqe_check_ddcb_queue(cd, req->queue);
		अगर (ddcb_requ_finished(cd, req))
			वापस rc;

		dev_err(&pci_dev->dev,
			"[%s] err: DDCB#%d timeout rc=%d state=%d req @ %p\n",
			__func__, req->num, rc,	ddcb_requ_get_state(req),
			req);
		dev_err(&pci_dev->dev,
			"[%s]      IO_QUEUE_STATUS=0x%016llx\n", __func__,
			__genwqe_पढ़ोq(cd, queue->IO_QUEUE_STATUS));

		pddcb = &queue->ddcb_vaddr[req->num];
		genwqe_hexdump(pci_dev, pddcb, माप(*pddcb));

		prपूर्णांक_ddcb_info(cd, req->queue);
		वापस -ETIMEDOUT;

	पूर्ण अन्यथा अगर (rc == -ERESTARTSYS) अणु
		वापस rc;
		/*
		 * EINTR:       Stops the application
		 * ERESTARTSYS: Restartable प्रणालीcall; called again
		 */

	पूर्ण अन्यथा अगर (rc < 0) अणु
		dev_err(&pci_dev->dev,
			"[%s] err: DDCB#%d unknown result (rc=%d) %d!\n",
			__func__, req->num, rc, ddcb_requ_get_state(req));
		वापस -EINVAL;
	पूर्ण

	/* Severe error occured. Driver is क्रमced to stop operation */
	अगर (cd->card_state != GENWQE_CARD_USED) अणु
		dev_err(&pci_dev->dev,
			"[%s] err: DDCB#%d forced to stop (rc=%d)\n",
			__func__, req->num, rc);
		वापस -EIO;
	पूर्ण
	वापस rc;
पूर्ण

/**
 * get_next_ddcb() - Get next available DDCB
 * @cd:         poपूर्णांकer to genwqe device descriptor
 * @queue:      DDCB queue
 * @num:        पूर्णांकernal DDCB number
 *
 * DDCB's content is completely cleared but presets क्रम PRE and
 * SEQNUM. This function must only be called when ddcb_lock is held.
 *
 * Return: शून्य अगर no empty DDCB available otherwise ptr to next DDCB.
 */
अटल काष्ठा ddcb *get_next_ddcb(काष्ठा genwqe_dev *cd,
				  काष्ठा ddcb_queue *queue,
				  पूर्णांक *num)
अणु
	u64 *pu64;
	काष्ठा ddcb *pddcb;

	अगर (queue_मुक्त_ddcbs(queue) == 0) /* queue is  full */
		वापस शून्य;

	/* find new ddcb */
	pddcb = &queue->ddcb_vaddr[queue->ddcb_next];

	/* अगर it is not completed, we are not allowed to use it */
	/* barrier(); */
	अगर ((pddcb->icrc_hsi_shi_32 & DDCB_COMPLETED_BE32) == 0x00000000)
		वापस शून्य;

	*num = queue->ddcb_next;	/* पूर्णांकernal DDCB number */
	queue->ddcb_next = (queue->ddcb_next + 1) % queue->ddcb_max;

	/* clear important DDCB fields */
	pu64 = (u64 *)pddcb;
	pu64[0] = 0ULL;		/* offs 0x00 (ICRC,HSI,SHI,...) */
	pu64[1] = 0ULL;		/* offs 0x01 (ACFUNC,CMD...) */

	/* destroy previous results in ASV */
	pu64[0x80/8] = 0ULL;	/* offs 0x80 (ASV + 0) */
	pu64[0x88/8] = 0ULL;	/* offs 0x88 (ASV + 0x08) */
	pu64[0x90/8] = 0ULL;	/* offs 0x90 (ASV + 0x10) */
	pu64[0x98/8] = 0ULL;	/* offs 0x98 (ASV + 0x18) */
	pu64[0xd0/8] = 0ULL;	/* offs 0xd0 (RETC,ATTN...) */

	pddcb->pre = DDCB_PRESET_PRE; /* 128 */
	pddcb->seqnum_16 = cpu_to_be16(queue->ddcb_seq++);
	वापस pddcb;
पूर्ण

/**
 * __genwqe_purge_ddcb() - Remove a DDCB from the workqueue
 * @cd:         genwqe device descriptor
 * @req:        DDCB request
 *
 * This will fail when the request was alपढ़ोy FETCHED. In this हाल
 * we need to रुको until it is finished. Else the DDCB can be
 * reused. This function also ensures that the request data काष्ठाure
 * is हटाओd from ddcb_req[].
 *
 * Do not क्रमget to call this function when genwqe_रुको_ddcb() fails,
 * such that the request माला_लो really हटाओd from ddcb_req[].
 *
 * Return: 0 success
 */
पूर्णांक __genwqe_purge_ddcb(काष्ठा genwqe_dev *cd, काष्ठा ddcb_requ *req)
अणु
	काष्ठा ddcb *pddcb = शून्य;
	अचिन्हित पूर्णांक t;
	अचिन्हित दीर्घ flags;
	काष्ठा ddcb_queue *queue = req->queue;
	काष्ठा pci_dev *pci_dev = cd->pci_dev;
	u64 queue_status;
	__be32 icrc_hsi_shi = 0x0000;
	__be32 old, new;

	/* अचिन्हित दीर्घ flags; */
	अगर (GENWQE_DDCB_SOFTWARE_TIMEOUT <= 0) अणु
		dev_err(&pci_dev->dev,
			"[%s] err: software timeout is not set!\n", __func__);
		वापस -EFAULT;
	पूर्ण

	pddcb = &queue->ddcb_vaddr[req->num];

	क्रम (t = 0; t < GENWQE_DDCB_SOFTWARE_TIMEOUT * 10; t++) अणु

		spin_lock_irqsave(&queue->ddcb_lock, flags);

		/* Check अगर req was meanजबतक finished */
		अगर (ddcb_requ_get_state(req) == GENWQE_REQU_FINISHED)
			जाओ go_home;

		/* try to set PURGE bit अगर FETCHED/COMPLETED are not set */
		old = pddcb->icrc_hsi_shi_32;	/* पढ़ो SHI/HSI in BE32 */
		अगर ((old & DDCB_FETCHED_BE32) == 0x00000000) अणु

			new = (old | DDCB_PURGE_BE32);
			icrc_hsi_shi = cmpxchg(&pddcb->icrc_hsi_shi_32,
					       old, new);
			अगर (icrc_hsi_shi == old)
				जाओ finish_ddcb;
		पूर्ण

		/* normal finish with HSI bit */
		barrier();
		icrc_hsi_shi = pddcb->icrc_hsi_shi_32;
		अगर (icrc_hsi_shi & DDCB_COMPLETED_BE32)
			जाओ finish_ddcb;

		spin_unlock_irqrestore(&queue->ddcb_lock, flags);

		/*
		 * Here the check_ddcb() function will most likely
		 * discover this DDCB to be finished some poपूर्णांक in
		 * समय. It will mark the req finished and मुक्त it up
		 * in the list.
		 */

		copy_ddcb_results(req, req->num); /* क्रम the failing हाल */
		msleep(100); /* sleep क्रम 1/10 second and try again */
		जारी;

finish_ddcb:
		copy_ddcb_results(req, req->num);
		ddcb_requ_set_state(req, GENWQE_REQU_FINISHED);
		queue->ddcbs_in_flight--;
		queue->ddcb_req[req->num] = शून्य; /* delete from array */
		ddcb_mark_cleared(pddcb);

		/* Move active DDCB further; Nothing to करो here anymore. */

		/*
		 * We need to ensure that there is at least one मुक्त
		 * DDCB in the queue. To करो that, we must update
		 * ddcb_act only अगर the COMPLETED bit is set क्रम the
		 * DDCB we are working on अन्यथा we treat that DDCB even
		 * अगर we PURGED it as occupied (hardware is supposed
		 * to set the COMPLETED bit yet!).
		 */
		icrc_hsi_shi = pddcb->icrc_hsi_shi_32;
		अगर ((icrc_hsi_shi & DDCB_COMPLETED_BE32) &&
		    (queue->ddcb_act == req->num)) अणु
			queue->ddcb_act = ((queue->ddcb_act + 1) %
					   queue->ddcb_max);
		पूर्ण
go_home:
		spin_unlock_irqrestore(&queue->ddcb_lock, flags);
		वापस 0;
	पूर्ण

	/*
	 * If the card is dead and the queue is क्रमced to stop, we
	 * might see this in the queue status रेजिस्टर.
	 */
	queue_status = __genwqe_पढ़ोq(cd, queue->IO_QUEUE_STATUS);

	dev_dbg(&pci_dev->dev, "UN/FINISHED DDCB#%d\n", req->num);
	genwqe_hexdump(pci_dev, pddcb, माप(*pddcb));

	dev_err(&pci_dev->dev,
		"[%s] err: DDCB#%d not purged and not completed after %d seconds QSTAT=%016llx!!\n",
		__func__, req->num, GENWQE_DDCB_SOFTWARE_TIMEOUT,
		queue_status);

	prपूर्णांक_ddcb_info(cd, req->queue);

	वापस -EFAULT;
पूर्ण

पूर्णांक genwqe_init_debug_data(काष्ठा genwqe_dev *cd, काष्ठा genwqe_debug_data *d)
अणु
	पूर्णांक len;
	काष्ठा pci_dev *pci_dev = cd->pci_dev;

	अगर (d == शून्य) अणु
		dev_err(&pci_dev->dev,
			"[%s] err: invalid memory for debug data!\n",
			__func__);
		वापस -EFAULT;
	पूर्ण

	len  = माप(d->driver_version);
	snम_लिखो(d->driver_version, len, "%s", DRV_VERSION);
	d->slu_unitcfg = cd->slu_unitcfg;
	d->app_unitcfg = cd->app_unitcfg;
	वापस 0;
पूर्ण

/**
 * __genwqe_enqueue_ddcb() - Enqueue a DDCB
 * @cd:         poपूर्णांकer to genwqe device descriptor
 * @req:        poपूर्णांकer to DDCB execution request
 * @f_flags:    file mode: blocking, non-blocking
 *
 * Return: 0 अगर enqueuing succeeded
 *         -EIO अगर card is unusable/PCIe problems
 *         -EBUSY अगर enqueuing failed
 */
पूर्णांक __genwqe_enqueue_ddcb(काष्ठा genwqe_dev *cd, काष्ठा ddcb_requ *req,
			  अचिन्हित पूर्णांक f_flags)
अणु
	काष्ठा ddcb *pddcb;
	अचिन्हित दीर्घ flags;
	काष्ठा ddcb_queue *queue;
	काष्ठा pci_dev *pci_dev = cd->pci_dev;
	u16 icrc;

 retry:
	अगर (cd->card_state != GENWQE_CARD_USED) अणु
		prपूर्णांकk_ratelimited(KERN_ERR
			"%s %s: [%s] Card is unusable/PCIe problem Req#%d\n",
			GENWQE_DEVNAME, dev_name(&pci_dev->dev),
			__func__, req->num);
		वापस -EIO;
	पूर्ण

	queue = req->queue = &cd->queue;

	/* FIXME circumvention to improve perक्रमmance when no irq is
	 * there.
	 */
	अगर (GENWQE_POLLING_ENABLED)
		genwqe_check_ddcb_queue(cd, queue);

	/*
	 * It must be ensured to process all DDCBs in successive
	 * order. Use a lock here in order to prevent nested DDCB
	 * enqueuing.
	 */
	spin_lock_irqsave(&queue->ddcb_lock, flags);

	pddcb = get_next_ddcb(cd, queue, &req->num);	/* get ptr and num */
	अगर (pddcb == शून्य) अणु
		पूर्णांक rc;

		spin_unlock_irqrestore(&queue->ddcb_lock, flags);

		अगर (f_flags & O_NONBLOCK) अणु
			queue->वापस_on_busy++;
			वापस -EBUSY;
		पूर्ण

		queue->रुको_on_busy++;
		rc = रुको_event_पूर्णांकerruptible(queue->busy_रुकोq,
					      queue_मुक्त_ddcbs(queue) != 0);
		dev_dbg(&pci_dev->dev, "[%s] waiting for free DDCB: rc=%d\n",
			__func__, rc);
		अगर (rc == -ERESTARTSYS)
			वापस rc;  /* पूर्णांकerrupted by a संकेत */

		जाओ retry;
	पूर्ण

	अगर (queue->ddcb_req[req->num] != शून्य) अणु
		spin_unlock_irqrestore(&queue->ddcb_lock, flags);

		dev_err(&pci_dev->dev,
			"[%s] picked DDCB %d with req=%p still in use!!\n",
			__func__, req->num, req);
		वापस -EFAULT;
	पूर्ण
	ddcb_requ_set_state(req, GENWQE_REQU_ENQUEUED);
	queue->ddcb_req[req->num] = req;

	pddcb->cmकरोpts_16 = cpu_to_be16(req->cmd.cmकरोpts);
	pddcb->cmd = req->cmd.cmd;
	pddcb->acfunc = req->cmd.acfunc;	/* functional unit */

	/*
	 * We know that we can get retc 0x104 with CRC error, करो not
	 * stop the queue in those हालs क्रम this command. Xसूची = 1
	 * करोes not work क्रम old SLU versions.
	 *
	 * Last bitstream with the old Xसूची behavior had SLU_ID
	 * 0x34199.
	 */
	अगर ((cd->slu_unitcfg & 0xFFFF0ull) > 0x34199ull)
		pddcb->xdir = 0x1;
	अन्यथा
		pddcb->xdir = 0x0;


	pddcb->psp = (((req->cmd.asiv_length / 8) << 4) |
		      ((req->cmd.asv_length  / 8)));
	pddcb->disp_ts_64 = cpu_to_be64(req->cmd.disp_ts);

	/*
	 * If copying the whole DDCB_ASIV_LENGTH is impacting
	 * perक्रमmance we need to change it to
	 * req->cmd.asiv_length. But simulation benefits from some
	 * non-architectured bits behind the architectured content.
	 *
	 * How much data is copied depends on the availability of the
	 * ATS field, which was पूर्णांकroduced late. If the ATS field is
	 * supported ASIV is 8 bytes लघुer than it used to be. Since
	 * the ATS field is copied too, the code should करो exactly
	 * what it did beक्रमe, but I wanted to make copying of the ATS
	 * field very explicit.
	 */
	अगर (genwqe_get_slu_id(cd) <= 0x2) अणु
		स_नकल(&pddcb->__asiv[0],	/* destination */
		       &req->cmd.__asiv[0],	/* source */
		       DDCB_ASIV_LENGTH);	/* req->cmd.asiv_length */
	पूर्ण अन्यथा अणु
		pddcb->n.ats_64 = cpu_to_be64(req->cmd.ats);
		स_नकल(&pddcb->n.asiv[0],	/* destination */
			&req->cmd.asiv[0],	/* source */
			DDCB_ASIV_LENGTH_ATS);	/* req->cmd.asiv_length */
	पूर्ण

	pddcb->icrc_hsi_shi_32 = cpu_to_be32(0x00000000); /* क्रम crc */

	/*
	 * Calculate CRC_16 क्रम corresponding range PSP(7:4). Include
	 * empty 4 bytes prior to the data.
	 */
	icrc = genwqe_crc16((स्थिर u8 *)pddcb,
			   ICRC_LENGTH(req->cmd.asiv_length), 0xffff);
	pddcb->icrc_hsi_shi_32 = cpu_to_be32((u32)icrc << 16);

	/* enable DDCB completion irq */
	अगर (!GENWQE_POLLING_ENABLED)
		pddcb->icrc_hsi_shi_32 |= DDCB_INTR_BE32;

	dev_dbg(&pci_dev->dev, "INPUT DDCB#%d\n", req->num);
	genwqe_hexdump(pci_dev, pddcb, माप(*pddcb));

	अगर (ddcb_requ_collect_debug_data(req)) अणु
		/* use the kernel copy of debug data. copying back to
		   user buffer happens later */

		genwqe_init_debug_data(cd, &req->debug_data);
		स_नकल(&req->debug_data.ddcb_beक्रमe, pddcb,
		       माप(req->debug_data.ddcb_beक्रमe));
	पूर्ण

	enqueue_ddcb(cd, queue, pddcb, req->num);
	queue->ddcbs_in_flight++;

	अगर (queue->ddcbs_in_flight > queue->ddcbs_max_in_flight)
		queue->ddcbs_max_in_flight = queue->ddcbs_in_flight;

	ddcb_requ_set_state(req, GENWQE_REQU_TAPPED);
	spin_unlock_irqrestore(&queue->ddcb_lock, flags);
	wake_up_पूर्णांकerruptible(&cd->queue_रुकोq);

	वापस 0;
पूर्ण

/**
 * __genwqe_execute_raw_ddcb() - Setup and execute DDCB
 * @cd:         poपूर्णांकer to genwqe device descriptor
 * @cmd:        user provided DDCB command
 * @f_flags:    file mode: blocking, non-blocking
 */
पूर्णांक __genwqe_execute_raw_ddcb(काष्ठा genwqe_dev *cd,
			      काष्ठा genwqe_ddcb_cmd *cmd,
			      अचिन्हित पूर्णांक f_flags)
अणु
	पूर्णांक rc = 0;
	काष्ठा pci_dev *pci_dev = cd->pci_dev;
	काष्ठा ddcb_requ *req = container_of(cmd, काष्ठा ddcb_requ, cmd);

	अगर (cmd->asiv_length > DDCB_ASIV_LENGTH) अणु
		dev_err(&pci_dev->dev, "[%s] err: wrong asiv_length of %d\n",
			__func__, cmd->asiv_length);
		वापस -EINVAL;
	पूर्ण
	अगर (cmd->asv_length > DDCB_ASV_LENGTH) अणु
		dev_err(&pci_dev->dev, "[%s] err: wrong asv_length of %d\n",
			__func__, cmd->asiv_length);
		वापस -EINVAL;
	पूर्ण
	rc = __genwqe_enqueue_ddcb(cd, req, f_flags);
	अगर (rc != 0)
		वापस rc;

	rc = __genwqe_रुको_ddcb(cd, req);
	अगर (rc < 0)		/* error or संकेत पूर्णांकerrupt */
		जाओ err_निकास;

	अगर (ddcb_requ_collect_debug_data(req)) अणु
		अगर (copy_to_user((काष्ठा genwqe_debug_data __user *)
				 (अचिन्हित दीर्घ)cmd->ddata_addr,
				 &req->debug_data,
				 माप(काष्ठा genwqe_debug_data)))
			वापस -EFAULT;
	पूर्ण

	/*
	 * Higher values than 0x102 indicate completion with faults,
	 * lower values than 0x102 indicate processing faults. Note
	 * that DDCB might have been purged. E.g. Cntl+C.
	 */
	अगर (cmd->retc != DDCB_RETC_COMPLETE) अणु
		/* This might happen e.g. flash पढ़ो, and needs to be
		   handled by the upper layer code. */
		rc = -EBADMSG;	/* not processed/error retc */
	पूर्ण

	वापस rc;

 err_निकास:
	__genwqe_purge_ddcb(cd, req);

	अगर (ddcb_requ_collect_debug_data(req)) अणु
		अगर (copy_to_user((काष्ठा genwqe_debug_data __user *)
				 (अचिन्हित दीर्घ)cmd->ddata_addr,
				 &req->debug_data,
				 माप(काष्ठा genwqe_debug_data)))
			वापस -EFAULT;
	पूर्ण
	वापस rc;
पूर्ण

/**
 * genwqe_next_ddcb_पढ़ोy() - Figure out अगर the next DDCB is alपढ़ोy finished
 * @cd:         poपूर्णांकer to genwqe device descriptor
 *
 * We use this as condition क्रम our रुको-queue code.
 */
अटल पूर्णांक genwqe_next_ddcb_पढ़ोy(काष्ठा genwqe_dev *cd)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा ddcb *pddcb;
	काष्ठा ddcb_queue *queue = &cd->queue;

	spin_lock_irqsave(&queue->ddcb_lock, flags);

	अगर (queue_empty(queue)) अणु /* empty queue */
		spin_unlock_irqrestore(&queue->ddcb_lock, flags);
		वापस 0;
	पूर्ण

	pddcb = &queue->ddcb_vaddr[queue->ddcb_act];
	अगर (pddcb->icrc_hsi_shi_32 & DDCB_COMPLETED_BE32) अणु /* ddcb पढ़ोy */
		spin_unlock_irqrestore(&queue->ddcb_lock, flags);
		वापस 1;
	पूर्ण

	spin_unlock_irqrestore(&queue->ddcb_lock, flags);
	वापस 0;
पूर्ण

/**
 * genwqe_ddcbs_in_flight() - Check how many DDCBs are in flight
 * @cd:         poपूर्णांकer to genwqe device descriptor
 *
 * Keep track on the number of DDCBs which ware currently in the
 * queue. This is needed क्रम statistics as well as condition अगर we want
 * to रुको or better करो polling in हाल of no पूर्णांकerrupts available.
 */
पूर्णांक genwqe_ddcbs_in_flight(काष्ठा genwqe_dev *cd)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ddcbs_in_flight = 0;
	काष्ठा ddcb_queue *queue = &cd->queue;

	spin_lock_irqsave(&queue->ddcb_lock, flags);
	ddcbs_in_flight += queue->ddcbs_in_flight;
	spin_unlock_irqrestore(&queue->ddcb_lock, flags);

	वापस ddcbs_in_flight;
पूर्ण

अटल पूर्णांक setup_ddcb_queue(काष्ठा genwqe_dev *cd, काष्ठा ddcb_queue *queue)
अणु
	पूर्णांक rc, i;
	काष्ठा ddcb *pddcb;
	u64 val64;
	अचिन्हित पूर्णांक queue_size;
	काष्ठा pci_dev *pci_dev = cd->pci_dev;

	अगर (GENWQE_DDCB_MAX < 2)
		वापस -EINVAL;

	queue_size = roundup(GENWQE_DDCB_MAX * माप(काष्ठा ddcb), PAGE_SIZE);

	queue->ddcbs_in_flight = 0;  /* statistics */
	queue->ddcbs_max_in_flight = 0;
	queue->ddcbs_completed = 0;
	queue->वापस_on_busy = 0;
	queue->रुको_on_busy = 0;

	queue->ddcb_seq	  = 0x100; /* start sequence number */
	queue->ddcb_max	  = GENWQE_DDCB_MAX;
	queue->ddcb_vaddr = __genwqe_alloc_consistent(cd, queue_size,
						&queue->ddcb_daddr);
	अगर (queue->ddcb_vaddr == शून्य) अणु
		dev_err(&pci_dev->dev,
			"[%s] **err: could not allocate DDCB **\n", __func__);
		वापस -ENOMEM;
	पूर्ण
	queue->ddcb_req = kसुस्मृति(queue->ddcb_max, माप(काष्ठा ddcb_requ *),
				  GFP_KERNEL);
	अगर (!queue->ddcb_req) अणु
		rc = -ENOMEM;
		जाओ मुक्त_ddcbs;
	पूर्ण

	queue->ddcb_रुकोqs = kसुस्मृति(queue->ddcb_max,
				     माप(रुको_queue_head_t),
				     GFP_KERNEL);
	अगर (!queue->ddcb_रुकोqs) अणु
		rc = -ENOMEM;
		जाओ मुक्त_requs;
	पूर्ण

	क्रम (i = 0; i < queue->ddcb_max; i++) अणु
		pddcb = &queue->ddcb_vaddr[i];		     /* DDCBs */
		pddcb->icrc_hsi_shi_32 = DDCB_COMPLETED_BE32;
		pddcb->retc_16 = cpu_to_be16(0xfff);

		queue->ddcb_req[i] = शून्य;		     /* requests */
		init_रुकोqueue_head(&queue->ddcb_रुकोqs[i]); /* रुकोqueues */
	पूर्ण

	queue->ddcb_act  = 0;
	queue->ddcb_next = 0;	/* queue is empty */

	spin_lock_init(&queue->ddcb_lock);
	init_रुकोqueue_head(&queue->busy_रुकोq);

	val64 = ((u64)(queue->ddcb_max - 1) <<  8); /* lastptr */
	__genwqe_ग_लिखोq(cd, queue->IO_QUEUE_CONFIG,  0x07);  /* iCRC/vCRC */
	__genwqe_ग_लिखोq(cd, queue->IO_QUEUE_SEGMENT, queue->ddcb_daddr);
	__genwqe_ग_लिखोq(cd, queue->IO_QUEUE_INITSQN, queue->ddcb_seq);
	__genwqe_ग_लिखोq(cd, queue->IO_QUEUE_WRAP,    val64);
	वापस 0;

 मुक्त_requs:
	kमुक्त(queue->ddcb_req);
	queue->ddcb_req = शून्य;
 मुक्त_ddcbs:
	__genwqe_मुक्त_consistent(cd, queue_size, queue->ddcb_vaddr,
				queue->ddcb_daddr);
	queue->ddcb_vaddr = शून्य;
	queue->ddcb_daddr = 0ull;
	वापस rc;

पूर्ण

अटल पूर्णांक ddcb_queue_initialized(काष्ठा ddcb_queue *queue)
अणु
	वापस queue->ddcb_vaddr != शून्य;
पूर्ण

अटल व्योम मुक्त_ddcb_queue(काष्ठा genwqe_dev *cd, काष्ठा ddcb_queue *queue)
अणु
	अचिन्हित पूर्णांक queue_size;

	queue_size = roundup(queue->ddcb_max * माप(काष्ठा ddcb), PAGE_SIZE);

	kमुक्त(queue->ddcb_req);
	queue->ddcb_req = शून्य;

	अगर (queue->ddcb_vaddr) अणु
		__genwqe_मुक्त_consistent(cd, queue_size, queue->ddcb_vaddr,
					queue->ddcb_daddr);
		queue->ddcb_vaddr = शून्य;
		queue->ddcb_daddr = 0ull;
	पूर्ण
पूर्ण

अटल irqवापस_t genwqe_pf_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	u64 gfir;
	काष्ठा genwqe_dev *cd = (काष्ठा genwqe_dev *)dev_id;
	काष्ठा pci_dev *pci_dev = cd->pci_dev;

	/*
	 * In हाल of fatal FIR error the queue is stopped, such that
	 * we can safely check it without risking anything.
	 */
	cd->irqs_processed++;
	wake_up_पूर्णांकerruptible(&cd->queue_रुकोq);

	/*
	 * Checking क्रम errors beक्रमe kicking the queue might be
	 * safer, but slower क्रम the good-हाल ... See above.
	 */
	gfir = __genwqe_पढ़ोq(cd, IO_SLC_CFGREG_GFIR);
	अगर (((gfir & GFIR_ERR_TRIGGER) != 0x0) &&
	    !pci_channel_offline(pci_dev)) अणु

		अगर (cd->use_platक्रमm_recovery) अणु
			/*
			 * Since we use raw accessors, EEH errors won't be
			 * detected by the platक्रमm until we करो a non-raw
			 * MMIO or config space पढ़ो
			 */
			पढ़ोq(cd->mmio + IO_SLC_CFGREG_GFIR);

			/* Don't करो anything अगर the PCI channel is frozen */
			अगर (pci_channel_offline(pci_dev))
				जाओ निकास;
		पूर्ण

		wake_up_पूर्णांकerruptible(&cd->health_रुकोq);

		/*
		 * By शेष GFIRs causes recovery actions. This
		 * count is just क्रम debug when recovery is masked.
		 */
		dev_err_ratelimited(&pci_dev->dev,
				    "[%s] GFIR=%016llx\n",
				    __func__, gfir);
	पूर्ण

 निकास:
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t genwqe_vf_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा genwqe_dev *cd = (काष्ठा genwqe_dev *)dev_id;

	cd->irqs_processed++;
	wake_up_पूर्णांकerruptible(&cd->queue_रुकोq);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * genwqe_card_thपढ़ो() - Work thपढ़ो क्रम the DDCB queue
 * @data:         poपूर्णांकer to genwqe device descriptor
 *
 * The idea is to check अगर there are DDCBs in processing. If there are
 * some finished DDCBs, we process them and wakeup the
 * requestors. Otherwise we give other processes समय using
 * cond_resched().
 */
अटल पूर्णांक genwqe_card_thपढ़ो(व्योम *data)
अणु
	पूर्णांक should_stop = 0;
	काष्ठा genwqe_dev *cd = (काष्ठा genwqe_dev *)data;

	जबतक (!kthपढ़ो_should_stop()) अणु

		genwqe_check_ddcb_queue(cd, &cd->queue);

		अगर (GENWQE_POLLING_ENABLED) अणु
			रुको_event_पूर्णांकerruptible_समयout(
				cd->queue_रुकोq,
				genwqe_ddcbs_in_flight(cd) ||
				(should_stop = kthपढ़ो_should_stop()), 1);
		पूर्ण अन्यथा अणु
			रुको_event_पूर्णांकerruptible_समयout(
				cd->queue_रुकोq,
				genwqe_next_ddcb_पढ़ोy(cd) ||
				(should_stop = kthपढ़ो_should_stop()), HZ);
		पूर्ण
		अगर (should_stop)
			अवरोध;

		/*
		 * Aव्योम soft lockups on heavy loads; we करो not want
		 * to disable our पूर्णांकerrupts.
		 */
		cond_resched();
	पूर्ण
	वापस 0;
पूर्ण

/**
 * genwqe_setup_service_layer() - Setup DDCB queue
 * @cd:         poपूर्णांकer to genwqe device descriptor
 *
 * Allocate DDCBs. Configure Service Layer Controller (SLC).
 *
 * Return: 0 success
 */
पूर्णांक genwqe_setup_service_layer(काष्ठा genwqe_dev *cd)
अणु
	पूर्णांक rc;
	काष्ठा ddcb_queue *queue;
	काष्ठा pci_dev *pci_dev = cd->pci_dev;

	अगर (genwqe_is_privileged(cd)) अणु
		rc = genwqe_card_reset(cd);
		अगर (rc < 0) अणु
			dev_err(&pci_dev->dev,
				"[%s] err: reset failed.\n", __func__);
			वापस rc;
		पूर्ण
		genwqe_पढ़ो_softreset(cd);
	पूर्ण

	queue = &cd->queue;
	queue->IO_QUEUE_CONFIG  = IO_SLC_QUEUE_CONFIG;
	queue->IO_QUEUE_STATUS  = IO_SLC_QUEUE_STATUS;
	queue->IO_QUEUE_SEGMENT = IO_SLC_QUEUE_SEGMENT;
	queue->IO_QUEUE_INITSQN = IO_SLC_QUEUE_INITSQN;
	queue->IO_QUEUE_OFFSET  = IO_SLC_QUEUE_OFFSET;
	queue->IO_QUEUE_WRAP    = IO_SLC_QUEUE_WRAP;
	queue->IO_QUEUE_WTIME   = IO_SLC_QUEUE_WTIME;
	queue->IO_QUEUE_ERRCNTS = IO_SLC_QUEUE_ERRCNTS;
	queue->IO_QUEUE_LRW     = IO_SLC_QUEUE_LRW;

	rc = setup_ddcb_queue(cd, queue);
	अगर (rc != 0) अणु
		rc = -ENODEV;
		जाओ err_out;
	पूर्ण

	init_रुकोqueue_head(&cd->queue_रुकोq);
	cd->card_thपढ़ो = kthपढ़ो_run(genwqe_card_thपढ़ो, cd,
				      GENWQE_DEVNAME "%d_thread",
				      cd->card_idx);
	अगर (IS_ERR(cd->card_thपढ़ो)) अणु
		rc = PTR_ERR(cd->card_thपढ़ो);
		cd->card_thपढ़ो = शून्य;
		जाओ stop_मुक्त_queue;
	पूर्ण

	rc = genwqe_set_पूर्णांकerrupt_capability(cd, GENWQE_MSI_IRQS);
	अगर (rc)
		जाओ stop_kthपढ़ो;

	/*
	 * We must have all रुको-queues initialized when we enable the
	 * पूर्णांकerrupts. Otherwise we might crash अगर we get an early
	 * irq.
	 */
	init_रुकोqueue_head(&cd->health_रुकोq);

	अगर (genwqe_is_privileged(cd)) अणु
		rc = request_irq(pci_dev->irq, genwqe_pf_isr, IRQF_SHARED,
				 GENWQE_DEVNAME, cd);
	पूर्ण अन्यथा अणु
		rc = request_irq(pci_dev->irq, genwqe_vf_isr, IRQF_SHARED,
				 GENWQE_DEVNAME, cd);
	पूर्ण
	अगर (rc < 0) अणु
		dev_err(&pci_dev->dev, "irq %d not free.\n", pci_dev->irq);
		जाओ stop_irq_cap;
	पूर्ण

	cd->card_state = GENWQE_CARD_USED;
	वापस 0;

 stop_irq_cap:
	genwqe_reset_पूर्णांकerrupt_capability(cd);
 stop_kthपढ़ो:
	kthपढ़ो_stop(cd->card_thपढ़ो);
	cd->card_thपढ़ो = शून्य;
 stop_मुक्त_queue:
	मुक्त_ddcb_queue(cd, queue);
 err_out:
	वापस rc;
पूर्ण

/**
 * queue_wake_up_all() - Handles fatal error हाल
 * @cd:         poपूर्णांकer to genwqe device descriptor
 *
 * The PCI device got unusable and we have to stop all pending
 * requests as fast as we can. The code after this must purge the
 * DDCBs in question and ensure that all mappings are मुक्तd.
 */
अटल पूर्णांक queue_wake_up_all(काष्ठा genwqe_dev *cd)
अणु
	अचिन्हित पूर्णांक i;
	अचिन्हित दीर्घ flags;
	काष्ठा ddcb_queue *queue = &cd->queue;

	spin_lock_irqsave(&queue->ddcb_lock, flags);

	क्रम (i = 0; i < queue->ddcb_max; i++)
		wake_up_पूर्णांकerruptible(&queue->ddcb_रुकोqs[queue->ddcb_act]);

	wake_up_पूर्णांकerruptible(&queue->busy_रुकोq);
	spin_unlock_irqrestore(&queue->ddcb_lock, flags);

	वापस 0;
पूर्ण

/**
 * genwqe_finish_queue() - Remove any genwqe devices and user-पूर्णांकerfaces
 * @cd:         poपूर्णांकer to genwqe device descriptor
 *
 * Relies on the pre-condition that there are no users of the card
 * device anymore e.g. with खोलो file-descriptors.
 *
 * This function must be robust enough to be called twice.
 */
पूर्णांक genwqe_finish_queue(काष्ठा genwqe_dev *cd)
अणु
	पूर्णांक i, rc = 0, in_flight;
	पूर्णांक रुकोmax = GENWQE_DDCB_SOFTWARE_TIMEOUT;
	काष्ठा pci_dev *pci_dev = cd->pci_dev;
	काष्ठा ddcb_queue *queue = &cd->queue;

	अगर (!ddcb_queue_initialized(queue))
		वापस 0;

	/* Do not wipe out the error state. */
	अगर (cd->card_state == GENWQE_CARD_USED)
		cd->card_state = GENWQE_CARD_UNUSED;

	/* Wake up all requests in the DDCB queue such that they
	   should be हटाओd nicely. */
	queue_wake_up_all(cd);

	/* We must रुको to get rid of the DDCBs in flight */
	क्रम (i = 0; i < रुकोmax; i++) अणु
		in_flight = genwqe_ddcbs_in_flight(cd);

		अगर (in_flight == 0)
			अवरोध;

		dev_dbg(&pci_dev->dev,
			"  DEBUG [%d/%d] waiting for queue to get empty: %d requests!\n",
			i, रुकोmax, in_flight);

		/*
		 * Severe severe error situation: The card itself has
		 * 16 DDCB queues, each queue has e.g. 32 entries,
		 * each DDBC has a hardware समयout of currently 250
		 * msec but the PFs have a hardware समयout of 8 sec
		 * ... so I take something large.
		 */
		msleep(1000);
	पूर्ण
	अगर (i == रुकोmax) अणु
		dev_err(&pci_dev->dev, "  [%s] err: queue is not empty!!\n",
			__func__);
		rc = -EIO;
	पूर्ण
	वापस rc;
पूर्ण

/**
 * genwqe_release_service_layer() - Shutकरोwn DDCB queue
 * @cd:       genwqe device descriptor
 *
 * This function must be robust enough to be called twice.
 */
पूर्णांक genwqe_release_service_layer(काष्ठा genwqe_dev *cd)
अणु
	काष्ठा pci_dev *pci_dev = cd->pci_dev;

	अगर (!ddcb_queue_initialized(&cd->queue))
		वापस 1;

	मुक्त_irq(pci_dev->irq, cd);
	genwqe_reset_पूर्णांकerrupt_capability(cd);

	अगर (cd->card_thपढ़ो != शून्य) अणु
		kthपढ़ो_stop(cd->card_thपढ़ो);
		cd->card_thपढ़ो = शून्य;
	पूर्ण

	मुक्त_ddcb_queue(cd, &cd->queue);
	वापस 0;
पूर्ण
