<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* ldc.c: Logical Doमुख्य Channel link-layer protocol driver.
 *
 * Copyright (C) 2007, 2008 David S. Miller <davem@davemloft.net>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/scatterlist.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/list.h>
#समावेश <linux/init.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <यंत्र/iommu-common.h>

#समावेश <यंत्र/hypervisor.h>
#समावेश <यंत्र/iommu.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/ldc.h>
#समावेश <यंत्र/mdesc.h>

#घोषणा DRV_MODULE_NAME		"ldc"
#घोषणा PFX DRV_MODULE_NAME	": "
#घोषणा DRV_MODULE_VERSION	"1.1"
#घोषणा DRV_MODULE_RELDATE	"July 22, 2008"

#घोषणा COOKIE_PGSZ_CODE	0xf000000000000000ULL
#घोषणा COOKIE_PGSZ_CODE_SHIFT	60ULL


अटल अक्षर version[] =
	DRV_MODULE_NAME ".c:v" DRV_MODULE_VERSION " (" DRV_MODULE_RELDATE ")\n";

/* Packet header layout क्रम unreliable and reliable mode frames.
 * When in RAW mode, packets are simply straight 64-byte payloads
 * with no headers.
 */
काष्ठा ldc_packet अणु
	u8			type;
#घोषणा LDC_CTRL		0x01
#घोषणा LDC_DATA		0x02
#घोषणा LDC_ERR			0x10

	u8			stype;
#घोषणा LDC_INFO		0x01
#घोषणा LDC_ACK			0x02
#घोषणा LDC_NACK		0x04

	u8			ctrl;
#घोषणा LDC_VERS		0x01 /* Link Version		*/
#घोषणा LDC_RTS			0x02 /* Request To Send		*/
#घोषणा LDC_RTR			0x03 /* Ready To Receive	*/
#घोषणा LDC_RDX			0x04 /* Ready क्रम Data eXchange	*/
#घोषणा LDC_CTRL_MSK		0x0f

	u8			env;
#घोषणा LDC_LEN			0x3f
#घोषणा LDC_FRAG_MASK		0xc0
#घोषणा LDC_START		0x40
#घोषणा LDC_STOP		0x80

	u32			seqid;

	जोड़ अणु
		u8		u_data[LDC_PACKET_SIZE - 8];
		काष्ठा अणु
			u32	pad;
			u32	ackid;
			u8	r_data[LDC_PACKET_SIZE - 8 - 8];
		पूर्ण r;
	पूर्ण u;
पूर्ण;

काष्ठा ldc_version अणु
	u16 major;
	u16 minor;
पूर्ण;

/* Ordered from largest major to lowest.  */
अटल काष्ठा ldc_version ver_arr[] = अणु
	अणु .major = 1, .minor = 0 पूर्ण,
पूर्ण;

#घोषणा LDC_DEFAULT_MTU			(4 * LDC_PACKET_SIZE)
#घोषणा LDC_DEFAULT_NUM_ENTRIES		(PAGE_SIZE / LDC_PACKET_SIZE)

काष्ठा ldc_channel;

काष्ठा ldc_mode_ops अणु
	पूर्णांक (*ग_लिखो)(काष्ठा ldc_channel *, स्थिर व्योम *, अचिन्हित पूर्णांक);
	पूर्णांक (*पढ़ो)(काष्ठा ldc_channel *, व्योम *, अचिन्हित पूर्णांक);
पूर्ण;

अटल स्थिर काष्ठा ldc_mode_ops raw_ops;
अटल स्थिर काष्ठा ldc_mode_ops nonraw_ops;
अटल स्थिर काष्ठा ldc_mode_ops stream_ops;

पूर्णांक lकरोm_करोमुख्यing_enabled;

काष्ठा ldc_iommu अणु
	/* Protects ldc_unmap.  */
	spinlock_t			lock;
	काष्ठा ldc_mtable_entry		*page_table;
	काष्ठा iommu_map_table		iommu_map_table;
पूर्ण;

काष्ठा ldc_channel अणु
	/* Protects all operations that depend upon channel state.  */
	spinlock_t			lock;

	अचिन्हित दीर्घ			id;

	u8				*mssbuf;
	u32				mssbuf_len;
	u32				mssbuf_off;

	काष्ठा ldc_packet		*tx_base;
	अचिन्हित दीर्घ			tx_head;
	अचिन्हित दीर्घ			tx_tail;
	अचिन्हित दीर्घ			tx_num_entries;
	अचिन्हित दीर्घ			tx_ra;

	अचिन्हित दीर्घ			tx_acked;

	काष्ठा ldc_packet		*rx_base;
	अचिन्हित दीर्घ			rx_head;
	अचिन्हित दीर्घ			rx_tail;
	अचिन्हित दीर्घ			rx_num_entries;
	अचिन्हित दीर्घ			rx_ra;

	u32				rcv_nxt;
	u32				snd_nxt;

	अचिन्हित दीर्घ			chan_state;

	काष्ठा ldc_channel_config	cfg;
	व्योम				*event_arg;

	स्थिर काष्ठा ldc_mode_ops	*mops;

	काष्ठा ldc_iommu		iommu;

	काष्ठा ldc_version		ver;

	u8				hs_state;
#घोषणा LDC_HS_CLOSED			0x00
#घोषणा LDC_HS_OPEN			0x01
#घोषणा LDC_HS_GOTVERS			0x02
#घोषणा LDC_HS_SENTRTR			0x03
#घोषणा LDC_HS_GOTRTR			0x04
#घोषणा LDC_HS_COMPLETE			0x10

	u8				flags;
#घोषणा LDC_FLAG_ALLOCED_QUEUES		0x01
#घोषणा LDC_FLAG_REGISTERED_QUEUES	0x02
#घोषणा LDC_FLAG_REGISTERED_IRQS	0x04
#घोषणा LDC_FLAG_RESET			0x10

	u8				mss;
	u8				state;

#घोषणा LDC_IRQ_NAME_MAX		32
	अक्षर				rx_irq_name[LDC_IRQ_NAME_MAX];
	अक्षर				tx_irq_name[LDC_IRQ_NAME_MAX];

	काष्ठा hlist_head		mh_list;

	काष्ठा hlist_node		list;
पूर्ण;

#घोषणा ldcdbg(TYPE, f, a...) \
करो अणु	अगर (lp->cfg.debug & LDC_DEBUG_##TYPE) \
		prपूर्णांकk(KERN_INFO PFX "ID[%lu] " f, lp->id, ## a); \
पूर्ण जबतक (0)

#घोषणा	LDC_ABORT(lp)	ldc_पात((lp), __func__)

अटल स्थिर अक्षर *state_to_str(u8 state)
अणु
	चयन (state) अणु
	हाल LDC_STATE_INVALID:
		वापस "INVALID";
	हाल LDC_STATE_INIT:
		वापस "INIT";
	हाल LDC_STATE_BOUND:
		वापस "BOUND";
	हाल LDC_STATE_READY:
		वापस "READY";
	हाल LDC_STATE_CONNECTED:
		वापस "CONNECTED";
	शेष:
		वापस "<UNKNOWN>";
	पूर्ण
पूर्ण

अटल अचिन्हित दीर्घ __advance(अचिन्हित दीर्घ off, अचिन्हित दीर्घ num_entries)
अणु
	off += LDC_PACKET_SIZE;
	अगर (off == (num_entries * LDC_PACKET_SIZE))
		off = 0;

	वापस off;
पूर्ण

अटल अचिन्हित दीर्घ rx_advance(काष्ठा ldc_channel *lp, अचिन्हित दीर्घ off)
अणु
	वापस __advance(off, lp->rx_num_entries);
पूर्ण

अटल अचिन्हित दीर्घ tx_advance(काष्ठा ldc_channel *lp, अचिन्हित दीर्घ off)
अणु
	वापस __advance(off, lp->tx_num_entries);
पूर्ण

अटल काष्ठा ldc_packet *handshake_get_tx_packet(काष्ठा ldc_channel *lp,
						  अचिन्हित दीर्घ *new_tail)
अणु
	काष्ठा ldc_packet *p;
	अचिन्हित दीर्घ t;

	t = tx_advance(lp, lp->tx_tail);
	अगर (t == lp->tx_head)
		वापस शून्य;

	*new_tail = t;

	p = lp->tx_base;
	वापस p + (lp->tx_tail / LDC_PACKET_SIZE);
पूर्ण

/* When we are in reliable or stream mode, have to track the next packet
 * we haven't gotten an ACK क्रम in the TX queue using tx_acked.  We have
 * to be careful not to stomp over the queue past that poपूर्णांक.  During
 * the handshake, we करोn't have TX data packets pending in the queue
 * and that's why handshake_get_tx_packet() need not be mindful of
 * lp->tx_acked.
 */
अटल अचिन्हित दीर्घ head_क्रम_data(काष्ठा ldc_channel *lp)
अणु
	अगर (lp->cfg.mode == LDC_MODE_STREAM)
		वापस lp->tx_acked;
	वापस lp->tx_head;
पूर्ण

अटल पूर्णांक tx_has_space_क्रम(काष्ठा ldc_channel *lp, अचिन्हित पूर्णांक size)
अणु
	अचिन्हित दीर्घ limit, tail, new_tail, dअगरf;
	अचिन्हित पूर्णांक mss;

	limit = head_क्रम_data(lp);
	tail = lp->tx_tail;
	new_tail = tx_advance(lp, tail);
	अगर (new_tail == limit)
		वापस 0;

	अगर (limit > new_tail)
		dअगरf = limit - new_tail;
	अन्यथा
		dअगरf = (limit +
			((lp->tx_num_entries * LDC_PACKET_SIZE) - new_tail));
	dअगरf /= LDC_PACKET_SIZE;
	mss = lp->mss;

	अगर (dअगरf * mss < size)
		वापस 0;

	वापस 1;
पूर्ण

अटल काष्ठा ldc_packet *data_get_tx_packet(काष्ठा ldc_channel *lp,
					     अचिन्हित दीर्घ *new_tail)
अणु
	काष्ठा ldc_packet *p;
	अचिन्हित दीर्घ h, t;

	h = head_क्रम_data(lp);
	t = tx_advance(lp, lp->tx_tail);
	अगर (t == h)
		वापस शून्य;

	*new_tail = t;

	p = lp->tx_base;
	वापस p + (lp->tx_tail / LDC_PACKET_SIZE);
पूर्ण

अटल पूर्णांक set_tx_tail(काष्ठा ldc_channel *lp, अचिन्हित दीर्घ tail)
अणु
	अचिन्हित दीर्घ orig_tail = lp->tx_tail;
	पूर्णांक limit = 1000;

	lp->tx_tail = tail;
	जबतक (limit-- > 0) अणु
		अचिन्हित दीर्घ err;

		err = sun4v_ldc_tx_set_qtail(lp->id, tail);
		अगर (!err)
			वापस 0;

		अगर (err != HV_EWOULDBLOCK) अणु
			lp->tx_tail = orig_tail;
			वापस -EINVAL;
		पूर्ण
		udelay(1);
	पूर्ण

	lp->tx_tail = orig_tail;
	वापस -EBUSY;
पूर्ण

/* This just updates the head value in the hypervisor using
 * a polling loop with a समयout.  The caller takes care of
 * upating software state representing the head change, अगर any.
 */
अटल पूर्णांक __set_rx_head(काष्ठा ldc_channel *lp, अचिन्हित दीर्घ head)
अणु
	पूर्णांक limit = 1000;

	जबतक (limit-- > 0) अणु
		अचिन्हित दीर्घ err;

		err = sun4v_ldc_rx_set_qhead(lp->id, head);
		अगर (!err)
			वापस 0;

		अगर (err != HV_EWOULDBLOCK)
			वापस -EINVAL;

		udelay(1);
	पूर्ण

	वापस -EBUSY;
पूर्ण

अटल पूर्णांक send_tx_packet(काष्ठा ldc_channel *lp,
			  काष्ठा ldc_packet *p,
			  अचिन्हित दीर्घ new_tail)
अणु
	BUG_ON(p != (lp->tx_base + (lp->tx_tail / LDC_PACKET_SIZE)));

	वापस set_tx_tail(lp, new_tail);
पूर्ण

अटल काष्ठा ldc_packet *handshake_compose_ctrl(काष्ठा ldc_channel *lp,
						 u8 stype, u8 ctrl,
						 व्योम *data, पूर्णांक dlen,
						 अचिन्हित दीर्घ *new_tail)
अणु
	काष्ठा ldc_packet *p = handshake_get_tx_packet(lp, new_tail);

	अगर (p) अणु
		स_रखो(p, 0, माप(*p));
		p->type = LDC_CTRL;
		p->stype = stype;
		p->ctrl = ctrl;
		अगर (data)
			स_नकल(p->u.u_data, data, dlen);
	पूर्ण
	वापस p;
पूर्ण

अटल पूर्णांक start_handshake(काष्ठा ldc_channel *lp)
अणु
	काष्ठा ldc_packet *p;
	काष्ठा ldc_version *ver;
	अचिन्हित दीर्घ new_tail;

	ver = &ver_arr[0];

	ldcdbg(HS, "SEND VER INFO maj[%u] min[%u]\n",
	       ver->major, ver->minor);

	p = handshake_compose_ctrl(lp, LDC_INFO, LDC_VERS,
				   ver, माप(*ver), &new_tail);
	अगर (p) अणु
		पूर्णांक err = send_tx_packet(lp, p, new_tail);
		अगर (!err)
			lp->flags &= ~LDC_FLAG_RESET;
		वापस err;
	पूर्ण
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक send_version_nack(काष्ठा ldc_channel *lp,
			     u16 major, u16 minor)
अणु
	काष्ठा ldc_packet *p;
	काष्ठा ldc_version ver;
	अचिन्हित दीर्घ new_tail;

	ver.major = major;
	ver.minor = minor;

	p = handshake_compose_ctrl(lp, LDC_NACK, LDC_VERS,
				   &ver, माप(ver), &new_tail);
	अगर (p) अणु
		ldcdbg(HS, "SEND VER NACK maj[%u] min[%u]\n",
		       ver.major, ver.minor);

		वापस send_tx_packet(lp, p, new_tail);
	पूर्ण
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक send_version_ack(काष्ठा ldc_channel *lp,
			    काष्ठा ldc_version *vp)
अणु
	काष्ठा ldc_packet *p;
	अचिन्हित दीर्घ new_tail;

	p = handshake_compose_ctrl(lp, LDC_ACK, LDC_VERS,
				   vp, माप(*vp), &new_tail);
	अगर (p) अणु
		ldcdbg(HS, "SEND VER ACK maj[%u] min[%u]\n",
		       vp->major, vp->minor);

		वापस send_tx_packet(lp, p, new_tail);
	पूर्ण
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक send_rts(काष्ठा ldc_channel *lp)
अणु
	काष्ठा ldc_packet *p;
	अचिन्हित दीर्घ new_tail;

	p = handshake_compose_ctrl(lp, LDC_INFO, LDC_RTS, शून्य, 0,
				   &new_tail);
	अगर (p) अणु
		p->env = lp->cfg.mode;
		p->seqid = 0;
		lp->rcv_nxt = 0;

		ldcdbg(HS, "SEND RTS env[0x%x] seqid[0x%x]\n",
		       p->env, p->seqid);

		वापस send_tx_packet(lp, p, new_tail);
	पूर्ण
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक send_rtr(काष्ठा ldc_channel *lp)
अणु
	काष्ठा ldc_packet *p;
	अचिन्हित दीर्घ new_tail;

	p = handshake_compose_ctrl(lp, LDC_INFO, LDC_RTR, शून्य, 0,
				   &new_tail);
	अगर (p) अणु
		p->env = lp->cfg.mode;
		p->seqid = 0;

		ldcdbg(HS, "SEND RTR env[0x%x] seqid[0x%x]\n",
		       p->env, p->seqid);

		वापस send_tx_packet(lp, p, new_tail);
	पूर्ण
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक send_rdx(काष्ठा ldc_channel *lp)
अणु
	काष्ठा ldc_packet *p;
	अचिन्हित दीर्घ new_tail;

	p = handshake_compose_ctrl(lp, LDC_INFO, LDC_RDX, शून्य, 0,
				   &new_tail);
	अगर (p) अणु
		p->env = 0;
		p->seqid = ++lp->snd_nxt;
		p->u.r.ackid = lp->rcv_nxt;

		ldcdbg(HS, "SEND RDX env[0x%x] seqid[0x%x] ackid[0x%x]\n",
		       p->env, p->seqid, p->u.r.ackid);

		वापस send_tx_packet(lp, p, new_tail);
	पूर्ण
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक send_data_nack(काष्ठा ldc_channel *lp, काष्ठा ldc_packet *data_pkt)
अणु
	काष्ठा ldc_packet *p;
	अचिन्हित दीर्घ new_tail;
	पूर्णांक err;

	p = data_get_tx_packet(lp, &new_tail);
	अगर (!p)
		वापस -EBUSY;
	स_रखो(p, 0, माप(*p));
	p->type = data_pkt->type;
	p->stype = LDC_NACK;
	p->ctrl = data_pkt->ctrl & LDC_CTRL_MSK;
	p->seqid = lp->snd_nxt + 1;
	p->u.r.ackid = lp->rcv_nxt;

	ldcdbg(HS, "SEND DATA NACK type[0x%x] ctl[0x%x] seq[0x%x] ack[0x%x]\n",
	       p->type, p->ctrl, p->seqid, p->u.r.ackid);

	err = send_tx_packet(lp, p, new_tail);
	अगर (!err)
		lp->snd_nxt++;

	वापस err;
पूर्ण

अटल पूर्णांक ldc_पात(काष्ठा ldc_channel *lp, स्थिर अक्षर *msg)
अणु
	अचिन्हित दीर्घ hv_err;

	ldcdbg(STATE, "ABORT[%s]\n", msg);
	ldc_prपूर्णांक(lp);

	/* We report but करो not act upon the hypervisor errors because
	 * there really isn't much we can करो अगर they fail at this poपूर्णांक.
	 */
	hv_err = sun4v_ldc_tx_qconf(lp->id, lp->tx_ra, lp->tx_num_entries);
	अगर (hv_err)
		prपूर्णांकk(KERN_ERR PFX "ldc_abort: "
		       "sun4v_ldc_tx_qconf(%lx,%lx,%lx) failed, err=%lu\n",
		       lp->id, lp->tx_ra, lp->tx_num_entries, hv_err);

	hv_err = sun4v_ldc_tx_get_state(lp->id,
					&lp->tx_head,
					&lp->tx_tail,
					&lp->chan_state);
	अगर (hv_err)
		prपूर्णांकk(KERN_ERR PFX "ldc_abort: "
		       "sun4v_ldc_tx_get_state(%lx,...) failed, err=%lu\n",
		       lp->id, hv_err);

	hv_err = sun4v_ldc_rx_qconf(lp->id, lp->rx_ra, lp->rx_num_entries);
	अगर (hv_err)
		prपूर्णांकk(KERN_ERR PFX "ldc_abort: "
		       "sun4v_ldc_rx_qconf(%lx,%lx,%lx) failed, err=%lu\n",
		       lp->id, lp->rx_ra, lp->rx_num_entries, hv_err);

	/* Refetch the RX queue state as well, because we could be invoked
	 * here in the queue processing context.
	 */
	hv_err = sun4v_ldc_rx_get_state(lp->id,
					&lp->rx_head,
					&lp->rx_tail,
					&lp->chan_state);
	अगर (hv_err)
		prपूर्णांकk(KERN_ERR PFX "ldc_abort: "
		       "sun4v_ldc_rx_get_state(%lx,...) failed, err=%lu\n",
		       lp->id, hv_err);

	वापस -ECONNRESET;
पूर्ण

अटल काष्ठा ldc_version *find_by_major(u16 major)
अणु
	काष्ठा ldc_version *ret = शून्य;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(ver_arr); i++) अणु
		काष्ठा ldc_version *v = &ver_arr[i];
		अगर (v->major <= major) अणु
			ret = v;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक process_ver_info(काष्ठा ldc_channel *lp, काष्ठा ldc_version *vp)
अणु
	काष्ठा ldc_version *vap;
	पूर्णांक err;

	ldcdbg(HS, "GOT VERSION INFO major[%x] minor[%x]\n",
	       vp->major, vp->minor);

	अगर (lp->hs_state == LDC_HS_GOTVERS) अणु
		lp->hs_state = LDC_HS_OPEN;
		स_रखो(&lp->ver, 0, माप(lp->ver));
	पूर्ण

	vap = find_by_major(vp->major);
	अगर (!vap) अणु
		err = send_version_nack(lp, 0, 0);
	पूर्ण अन्यथा अगर (vap->major != vp->major) अणु
		err = send_version_nack(lp, vap->major, vap->minor);
	पूर्ण अन्यथा अणु
		काष्ठा ldc_version ver = *vp;
		अगर (ver.minor > vap->minor)
			ver.minor = vap->minor;
		err = send_version_ack(lp, &ver);
		अगर (!err) अणु
			lp->ver = ver;
			lp->hs_state = LDC_HS_GOTVERS;
		पूर्ण
	पूर्ण
	अगर (err)
		वापस LDC_ABORT(lp);

	वापस 0;
पूर्ण

अटल पूर्णांक process_ver_ack(काष्ठा ldc_channel *lp, काष्ठा ldc_version *vp)
अणु
	ldcdbg(HS, "GOT VERSION ACK major[%x] minor[%x]\n",
	       vp->major, vp->minor);

	अगर (lp->hs_state == LDC_HS_GOTVERS) अणु
		अगर (lp->ver.major != vp->major ||
		    lp->ver.minor != vp->minor)
			वापस LDC_ABORT(lp);
	पूर्ण अन्यथा अणु
		lp->ver = *vp;
		lp->hs_state = LDC_HS_GOTVERS;
	पूर्ण
	अगर (send_rts(lp))
		वापस LDC_ABORT(lp);
	वापस 0;
पूर्ण

अटल पूर्णांक process_ver_nack(काष्ठा ldc_channel *lp, काष्ठा ldc_version *vp)
अणु
	काष्ठा ldc_version *vap;
	काष्ठा ldc_packet *p;
	अचिन्हित दीर्घ new_tail;

	अगर (vp->major == 0 && vp->minor == 0)
		वापस LDC_ABORT(lp);

	vap = find_by_major(vp->major);
	अगर (!vap)
		वापस LDC_ABORT(lp);

	p = handshake_compose_ctrl(lp, LDC_INFO, LDC_VERS,
					   vap, माप(*vap),
					   &new_tail);
	अगर (!p)
		वापस LDC_ABORT(lp);

	वापस send_tx_packet(lp, p, new_tail);
पूर्ण

अटल पूर्णांक process_version(काष्ठा ldc_channel *lp,
			   काष्ठा ldc_packet *p)
अणु
	काष्ठा ldc_version *vp;

	vp = (काष्ठा ldc_version *) p->u.u_data;

	चयन (p->stype) अणु
	हाल LDC_INFO:
		वापस process_ver_info(lp, vp);

	हाल LDC_ACK:
		वापस process_ver_ack(lp, vp);

	हाल LDC_NACK:
		वापस process_ver_nack(lp, vp);

	शेष:
		वापस LDC_ABORT(lp);
	पूर्ण
पूर्ण

अटल पूर्णांक process_rts(काष्ठा ldc_channel *lp,
		       काष्ठा ldc_packet *p)
अणु
	ldcdbg(HS, "GOT RTS stype[%x] seqid[%x] env[%x]\n",
	       p->stype, p->seqid, p->env);

	अगर (p->stype     != LDC_INFO	   ||
	    lp->hs_state != LDC_HS_GOTVERS ||
	    p->env       != lp->cfg.mode)
		वापस LDC_ABORT(lp);

	lp->snd_nxt = p->seqid;
	lp->rcv_nxt = p->seqid;
	lp->hs_state = LDC_HS_SENTRTR;
	अगर (send_rtr(lp))
		वापस LDC_ABORT(lp);

	वापस 0;
पूर्ण

अटल पूर्णांक process_rtr(काष्ठा ldc_channel *lp,
		       काष्ठा ldc_packet *p)
अणु
	ldcdbg(HS, "GOT RTR stype[%x] seqid[%x] env[%x]\n",
	       p->stype, p->seqid, p->env);

	अगर (p->stype     != LDC_INFO ||
	    p->env       != lp->cfg.mode)
		वापस LDC_ABORT(lp);

	lp->snd_nxt = p->seqid;
	lp->hs_state = LDC_HS_COMPLETE;
	ldc_set_state(lp, LDC_STATE_CONNECTED);
	send_rdx(lp);

	वापस LDC_EVENT_UP;
पूर्ण

अटल पूर्णांक rx_seq_ok(काष्ठा ldc_channel *lp, u32 seqid)
अणु
	वापस lp->rcv_nxt + 1 == seqid;
पूर्ण

अटल पूर्णांक process_rdx(काष्ठा ldc_channel *lp,
		       काष्ठा ldc_packet *p)
अणु
	ldcdbg(HS, "GOT RDX stype[%x] seqid[%x] env[%x] ackid[%x]\n",
	       p->stype, p->seqid, p->env, p->u.r.ackid);

	अगर (p->stype != LDC_INFO ||
	    !(rx_seq_ok(lp, p->seqid)))
		वापस LDC_ABORT(lp);

	lp->rcv_nxt = p->seqid;

	lp->hs_state = LDC_HS_COMPLETE;
	ldc_set_state(lp, LDC_STATE_CONNECTED);

	वापस LDC_EVENT_UP;
पूर्ण

अटल पूर्णांक process_control_frame(काष्ठा ldc_channel *lp,
				 काष्ठा ldc_packet *p)
अणु
	चयन (p->ctrl) अणु
	हाल LDC_VERS:
		वापस process_version(lp, p);

	हाल LDC_RTS:
		वापस process_rts(lp, p);

	हाल LDC_RTR:
		वापस process_rtr(lp, p);

	हाल LDC_RDX:
		वापस process_rdx(lp, p);

	शेष:
		वापस LDC_ABORT(lp);
	पूर्ण
पूर्ण

अटल पूर्णांक process_error_frame(काष्ठा ldc_channel *lp,
			       काष्ठा ldc_packet *p)
अणु
	वापस LDC_ABORT(lp);
पूर्ण

अटल पूर्णांक process_data_ack(काष्ठा ldc_channel *lp,
			    काष्ठा ldc_packet *ack)
अणु
	अचिन्हित दीर्घ head = lp->tx_acked;
	u32 ackid = ack->u.r.ackid;

	जबतक (1) अणु
		काष्ठा ldc_packet *p = lp->tx_base + (head / LDC_PACKET_SIZE);

		head = tx_advance(lp, head);

		अगर (p->seqid == ackid) अणु
			lp->tx_acked = head;
			वापस 0;
		पूर्ण
		अगर (head == lp->tx_tail)
			वापस LDC_ABORT(lp);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम send_events(काष्ठा ldc_channel *lp, अचिन्हित पूर्णांक event_mask)
अणु
	अगर (event_mask & LDC_EVENT_RESET)
		lp->cfg.event(lp->event_arg, LDC_EVENT_RESET);
	अगर (event_mask & LDC_EVENT_UP)
		lp->cfg.event(lp->event_arg, LDC_EVENT_UP);
	अगर (event_mask & LDC_EVENT_DATA_READY)
		lp->cfg.event(lp->event_arg, LDC_EVENT_DATA_READY);
पूर्ण

अटल irqवापस_t ldc_rx(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा ldc_channel *lp = dev_id;
	अचिन्हित दीर्घ orig_state, flags;
	अचिन्हित पूर्णांक event_mask;

	spin_lock_irqsave(&lp->lock, flags);

	orig_state = lp->chan_state;

	/* We should probably check क्रम hypervisor errors here and
	 * reset the LDC channel अगर we get one.
	 */
	sun4v_ldc_rx_get_state(lp->id,
			       &lp->rx_head,
			       &lp->rx_tail,
			       &lp->chan_state);

	ldcdbg(RX, "RX state[0x%02lx:0x%02lx] head[0x%04lx] tail[0x%04lx]\n",
	       orig_state, lp->chan_state, lp->rx_head, lp->rx_tail);

	event_mask = 0;

	अगर (lp->cfg.mode == LDC_MODE_RAW &&
	    lp->chan_state == LDC_CHANNEL_UP) अणु
		lp->hs_state = LDC_HS_COMPLETE;
		ldc_set_state(lp, LDC_STATE_CONNECTED);

		/*
		 * Generate an LDC_EVENT_UP event अगर the channel
		 * was not alपढ़ोy up.
		 */
		अगर (orig_state != LDC_CHANNEL_UP) अणु
			event_mask |= LDC_EVENT_UP;
			orig_state = lp->chan_state;
		पूर्ण
	पूर्ण

	/* If we are in reset state, flush the RX queue and ignore
	 * everything.
	 */
	अगर (lp->flags & LDC_FLAG_RESET) अणु
		(व्योम) ldc_rx_reset(lp);
		जाओ out;
	पूर्ण

	/* Once we finish the handshake, we let the ldc_पढ़ो()
	 * paths करो all of the control frame and state management.
	 * Just trigger the callback.
	 */
	अगर (lp->hs_state == LDC_HS_COMPLETE) अणु
handshake_complete:
		अगर (lp->chan_state != orig_state) अणु
			अचिन्हित पूर्णांक event = LDC_EVENT_RESET;

			अगर (lp->chan_state == LDC_CHANNEL_UP)
				event = LDC_EVENT_UP;

			event_mask |= event;
		पूर्ण
		अगर (lp->rx_head != lp->rx_tail)
			event_mask |= LDC_EVENT_DATA_READY;

		जाओ out;
	पूर्ण

	अगर (lp->chan_state != orig_state)
		जाओ out;

	जबतक (lp->rx_head != lp->rx_tail) अणु
		काष्ठा ldc_packet *p;
		अचिन्हित दीर्घ new;
		पूर्णांक err;

		p = lp->rx_base + (lp->rx_head / LDC_PACKET_SIZE);

		चयन (p->type) अणु
		हाल LDC_CTRL:
			err = process_control_frame(lp, p);
			अगर (err > 0)
				event_mask |= err;
			अवरोध;

		हाल LDC_DATA:
			event_mask |= LDC_EVENT_DATA_READY;
			err = 0;
			अवरोध;

		हाल LDC_ERR:
			err = process_error_frame(lp, p);
			अवरोध;

		शेष:
			err = LDC_ABORT(lp);
			अवरोध;
		पूर्ण

		अगर (err < 0)
			अवरोध;

		new = lp->rx_head;
		new += LDC_PACKET_SIZE;
		अगर (new == (lp->rx_num_entries * LDC_PACKET_SIZE))
			new = 0;
		lp->rx_head = new;

		err = __set_rx_head(lp, new);
		अगर (err < 0) अणु
			(व्योम) LDC_ABORT(lp);
			अवरोध;
		पूर्ण
		अगर (lp->hs_state == LDC_HS_COMPLETE)
			जाओ handshake_complete;
	पूर्ण

out:
	spin_unlock_irqrestore(&lp->lock, flags);

	send_events(lp, event_mask);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t ldc_tx(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा ldc_channel *lp = dev_id;
	अचिन्हित दीर्घ flags, orig_state;
	अचिन्हित पूर्णांक event_mask = 0;

	spin_lock_irqsave(&lp->lock, flags);

	orig_state = lp->chan_state;

	/* We should probably check क्रम hypervisor errors here and
	 * reset the LDC channel अगर we get one.
	 */
	sun4v_ldc_tx_get_state(lp->id,
			       &lp->tx_head,
			       &lp->tx_tail,
			       &lp->chan_state);

	ldcdbg(TX, " TX state[0x%02lx:0x%02lx] head[0x%04lx] tail[0x%04lx]\n",
	       orig_state, lp->chan_state, lp->tx_head, lp->tx_tail);

	अगर (lp->cfg.mode == LDC_MODE_RAW &&
	    lp->chan_state == LDC_CHANNEL_UP) अणु
		lp->hs_state = LDC_HS_COMPLETE;
		ldc_set_state(lp, LDC_STATE_CONNECTED);

		/*
		 * Generate an LDC_EVENT_UP event अगर the channel
		 * was not alपढ़ोy up.
		 */
		अगर (orig_state != LDC_CHANNEL_UP) अणु
			event_mask |= LDC_EVENT_UP;
			orig_state = lp->chan_state;
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&lp->lock, flags);

	send_events(lp, event_mask);

	वापस IRQ_HANDLED;
पूर्ण

/* XXX ldc_alloc() and ldc_मुक्त() needs to run under a mutex so
 * XXX that addition and removal from the ldc_channel_list has
 * XXX atomicity, otherwise the __ldc_channel_exists() check is
 * XXX totally poपूर्णांकless as another thपढ़ो can slip पूर्णांकo ldc_alloc()
 * XXX and add a channel with the same ID.  There also needs to be
 * XXX a spinlock क्रम ldc_channel_list.
 */
अटल HLIST_HEAD(ldc_channel_list);

अटल पूर्णांक __ldc_channel_exists(अचिन्हित दीर्घ id)
अणु
	काष्ठा ldc_channel *lp;

	hlist_क्रम_each_entry(lp, &ldc_channel_list, list) अणु
		अगर (lp->id == id)
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक alloc_queue(स्थिर अक्षर *name, अचिन्हित दीर्घ num_entries,
		       काष्ठा ldc_packet **base, अचिन्हित दीर्घ *ra)
अणु
	अचिन्हित दीर्घ size, order;
	व्योम *q;

	size = num_entries * LDC_PACKET_SIZE;
	order = get_order(size);

	q = (व्योम *) __get_मुक्त_pages(GFP_KERNEL, order);
	अगर (!q) अणु
		prपूर्णांकk(KERN_ERR PFX "Alloc of %s queue failed with "
		       "size=%lu order=%lu\n", name, size, order);
		वापस -ENOMEM;
	पूर्ण

	स_रखो(q, 0, PAGE_SIZE << order);

	*base = q;
	*ra = __pa(q);

	वापस 0;
पूर्ण

अटल व्योम मुक्त_queue(अचिन्हित दीर्घ num_entries, काष्ठा ldc_packet *q)
अणु
	अचिन्हित दीर्घ size, order;

	अगर (!q)
		वापस;

	size = num_entries * LDC_PACKET_SIZE;
	order = get_order(size);

	मुक्त_pages((अचिन्हित दीर्घ)q, order);
पूर्ण

अटल अचिन्हित दीर्घ ldc_cookie_to_index(u64 cookie, व्योम *arg)
अणु
	u64 szcode = cookie >> COOKIE_PGSZ_CODE_SHIFT;
	/* काष्ठा ldc_iommu *ldc_iommu = (काष्ठा ldc_iommu *)arg; */

	cookie &= ~COOKIE_PGSZ_CODE;

	वापस (cookie >> (13ULL + (szcode * 3ULL)));
पूर्ण

अटल व्योम ldc_demap(काष्ठा ldc_iommu *iommu, अचिन्हित दीर्घ id, u64 cookie,
		      अचिन्हित दीर्घ entry, अचिन्हित दीर्घ npages)
अणु
	काष्ठा ldc_mtable_entry *base;
	अचिन्हित दीर्घ i, shअगरt;

	shअगरt = (cookie >> COOKIE_PGSZ_CODE_SHIFT) * 3;
	base = iommu->page_table + entry;
	क्रम (i = 0; i < npages; i++) अणु
		अगर (base->cookie)
			sun4v_ldc_revoke(id, cookie + (i << shअगरt),
					 base->cookie);
		base->mte = 0;
	पूर्ण
पूर्ण

/* XXX Make this configurable... XXX */
#घोषणा LDC_IOTABLE_SIZE	(8 * 1024)

अटल पूर्णांक ldc_iommu_init(स्थिर अक्षर *name, काष्ठा ldc_channel *lp)
अणु
	अचिन्हित दीर्घ sz, num_tsb_entries, tsbsize, order;
	काष्ठा ldc_iommu *ldc_iommu = &lp->iommu;
	काष्ठा iommu_map_table *iommu = &ldc_iommu->iommu_map_table;
	काष्ठा ldc_mtable_entry *table;
	अचिन्हित दीर्घ hv_err;
	पूर्णांक err;

	num_tsb_entries = LDC_IOTABLE_SIZE;
	tsbsize = num_tsb_entries * माप(काष्ठा ldc_mtable_entry);
	spin_lock_init(&ldc_iommu->lock);

	sz = num_tsb_entries / 8;
	sz = (sz + 7UL) & ~7UL;
	iommu->map = kzalloc(sz, GFP_KERNEL);
	अगर (!iommu->map) अणु
		prपूर्णांकk(KERN_ERR PFX "Alloc of arena map failed, sz=%lu\n", sz);
		वापस -ENOMEM;
	पूर्ण
	iommu_tbl_pool_init(iommu, num_tsb_entries, PAGE_SHIFT,
			    शून्य, false /* no large pool */,
			    1 /* npools */,
			    true /* skip span boundary check */);

	order = get_order(tsbsize);

	table = (काष्ठा ldc_mtable_entry *)
		__get_मुक्त_pages(GFP_KERNEL, order);
	err = -ENOMEM;
	अगर (!table) अणु
		prपूर्णांकk(KERN_ERR PFX "Alloc of MTE table failed, "
		       "size=%lu order=%lu\n", tsbsize, order);
		जाओ out_मुक्त_map;
	पूर्ण

	स_रखो(table, 0, PAGE_SIZE << order);

	ldc_iommu->page_table = table;

	hv_err = sun4v_ldc_set_map_table(lp->id, __pa(table),
					 num_tsb_entries);
	err = -EINVAL;
	अगर (hv_err)
		जाओ out_मुक्त_table;

	वापस 0;

out_मुक्त_table:
	मुक्त_pages((अचिन्हित दीर्घ) table, order);
	ldc_iommu->page_table = शून्य;

out_मुक्त_map:
	kमुक्त(iommu->map);
	iommu->map = शून्य;

	वापस err;
पूर्ण

अटल व्योम ldc_iommu_release(काष्ठा ldc_channel *lp)
अणु
	काष्ठा ldc_iommu *ldc_iommu = &lp->iommu;
	काष्ठा iommu_map_table *iommu = &ldc_iommu->iommu_map_table;
	अचिन्हित दीर्घ num_tsb_entries, tsbsize, order;

	(व्योम) sun4v_ldc_set_map_table(lp->id, 0, 0);

	num_tsb_entries = iommu->poolsize * iommu->nr_pools;
	tsbsize = num_tsb_entries * माप(काष्ठा ldc_mtable_entry);
	order = get_order(tsbsize);

	मुक्त_pages((अचिन्हित दीर्घ) ldc_iommu->page_table, order);
	ldc_iommu->page_table = शून्य;

	kमुक्त(iommu->map);
	iommu->map = शून्य;
पूर्ण

काष्ठा ldc_channel *ldc_alloc(अचिन्हित दीर्घ id,
			      स्थिर काष्ठा ldc_channel_config *cfgp,
			      व्योम *event_arg,
			      स्थिर अक्षर *name)
अणु
	काष्ठा ldc_channel *lp;
	स्थिर काष्ठा ldc_mode_ops *mops;
	अचिन्हित दीर्घ dummy1, dummy2, hv_err;
	u8 mss, *mssbuf;
	पूर्णांक err;

	err = -ENODEV;
	अगर (!lकरोm_करोमुख्यing_enabled)
		जाओ out_err;

	err = -EINVAL;
	अगर (!cfgp)
		जाओ out_err;
	अगर (!name)
		जाओ out_err;

	चयन (cfgp->mode) अणु
	हाल LDC_MODE_RAW:
		mops = &raw_ops;
		mss = LDC_PACKET_SIZE;
		अवरोध;

	हाल LDC_MODE_UNRELIABLE:
		mops = &nonraw_ops;
		mss = LDC_PACKET_SIZE - 8;
		अवरोध;

	हाल LDC_MODE_STREAM:
		mops = &stream_ops;
		mss = LDC_PACKET_SIZE - 8 - 8;
		अवरोध;

	शेष:
		जाओ out_err;
	पूर्ण

	अगर (!cfgp->event || !event_arg || !cfgp->rx_irq || !cfgp->tx_irq)
		जाओ out_err;

	hv_err = sun4v_ldc_tx_qinfo(id, &dummy1, &dummy2);
	err = -ENODEV;
	अगर (hv_err == HV_ECHANNEL)
		जाओ out_err;

	err = -EEXIST;
	अगर (__ldc_channel_exists(id))
		जाओ out_err;

	mssbuf = शून्य;

	lp = kzalloc(माप(*lp), GFP_KERNEL);
	err = -ENOMEM;
	अगर (!lp)
		जाओ out_err;

	spin_lock_init(&lp->lock);

	lp->id = id;

	err = ldc_iommu_init(name, lp);
	अगर (err)
		जाओ out_मुक्त_ldc;

	lp->mops = mops;
	lp->mss = mss;

	lp->cfg = *cfgp;
	अगर (!lp->cfg.mtu)
		lp->cfg.mtu = LDC_DEFAULT_MTU;

	अगर (lp->cfg.mode == LDC_MODE_STREAM) अणु
		mssbuf = kzalloc(lp->cfg.mtu, GFP_KERNEL);
		अगर (!mssbuf) अणु
			err = -ENOMEM;
			जाओ out_मुक्त_iommu;
		पूर्ण
		lp->mssbuf = mssbuf;
	पूर्ण

	lp->event_arg = event_arg;

	/* XXX allow setting via ldc_channel_config to override शेषs
	 * XXX or use some क्रमmula based upon mtu
	 */
	lp->tx_num_entries = LDC_DEFAULT_NUM_ENTRIES;
	lp->rx_num_entries = LDC_DEFAULT_NUM_ENTRIES;

	err = alloc_queue("TX", lp->tx_num_entries,
			  &lp->tx_base, &lp->tx_ra);
	अगर (err)
		जाओ out_मुक्त_mssbuf;

	err = alloc_queue("RX", lp->rx_num_entries,
			  &lp->rx_base, &lp->rx_ra);
	अगर (err)
		जाओ out_मुक्त_txq;

	lp->flags |= LDC_FLAG_ALLOCED_QUEUES;

	lp->hs_state = LDC_HS_CLOSED;
	ldc_set_state(lp, LDC_STATE_INIT);

	INIT_HLIST_NODE(&lp->list);
	hlist_add_head(&lp->list, &ldc_channel_list);

	INIT_HLIST_HEAD(&lp->mh_list);

	snम_लिखो(lp->rx_irq_name, LDC_IRQ_NAME_MAX, "%s RX", name);
	snम_लिखो(lp->tx_irq_name, LDC_IRQ_NAME_MAX, "%s TX", name);

	err = request_irq(lp->cfg.rx_irq, ldc_rx, 0,
			  lp->rx_irq_name, lp);
	अगर (err)
		जाओ out_मुक्त_txq;

	err = request_irq(lp->cfg.tx_irq, ldc_tx, 0,
			  lp->tx_irq_name, lp);
	अगर (err) अणु
		मुक्त_irq(lp->cfg.rx_irq, lp);
		जाओ out_मुक्त_txq;
	पूर्ण

	वापस lp;

out_मुक्त_txq:
	मुक्त_queue(lp->tx_num_entries, lp->tx_base);

out_मुक्त_mssbuf:
	kमुक्त(mssbuf);

out_मुक्त_iommu:
	ldc_iommu_release(lp);

out_मुक्त_ldc:
	kमुक्त(lp);

out_err:
	वापस ERR_PTR(err);
पूर्ण
EXPORT_SYMBOL(ldc_alloc);

व्योम ldc_unbind(काष्ठा ldc_channel *lp)
अणु
	अगर (lp->flags & LDC_FLAG_REGISTERED_IRQS) अणु
		मुक्त_irq(lp->cfg.rx_irq, lp);
		मुक्त_irq(lp->cfg.tx_irq, lp);
		lp->flags &= ~LDC_FLAG_REGISTERED_IRQS;
	पूर्ण

	अगर (lp->flags & LDC_FLAG_REGISTERED_QUEUES) अणु
		sun4v_ldc_tx_qconf(lp->id, 0, 0);
		sun4v_ldc_rx_qconf(lp->id, 0, 0);
		lp->flags &= ~LDC_FLAG_REGISTERED_QUEUES;
	पूर्ण
	अगर (lp->flags & LDC_FLAG_ALLOCED_QUEUES) अणु
		मुक्त_queue(lp->tx_num_entries, lp->tx_base);
		मुक्त_queue(lp->rx_num_entries, lp->rx_base);
		lp->flags &= ~LDC_FLAG_ALLOCED_QUEUES;
	पूर्ण

	ldc_set_state(lp, LDC_STATE_INIT);
पूर्ण
EXPORT_SYMBOL(ldc_unbind);

व्योम ldc_मुक्त(काष्ठा ldc_channel *lp)
अणु
	ldc_unbind(lp);
	hlist_del(&lp->list);
	kमुक्त(lp->mssbuf);
	ldc_iommu_release(lp);

	kमुक्त(lp);
पूर्ण
EXPORT_SYMBOL(ldc_मुक्त);

/* Bind the channel.  This रेजिस्टरs the LDC queues with
 * the hypervisor and माला_दो the channel पूर्णांकo a pseuकरो-listening
 * state.  This करोes not initiate a handshake, ldc_connect() करोes
 * that.
 */
पूर्णांक ldc_bind(काष्ठा ldc_channel *lp)
अणु
	अचिन्हित दीर्घ hv_err, flags;
	पूर्णांक err = -EINVAL;

	अगर (lp->state != LDC_STATE_INIT)
		वापस -EINVAL;

	spin_lock_irqsave(&lp->lock, flags);

	enable_irq(lp->cfg.rx_irq);
	enable_irq(lp->cfg.tx_irq);

	lp->flags |= LDC_FLAG_REGISTERED_IRQS;

	err = -ENODEV;
	hv_err = sun4v_ldc_tx_qconf(lp->id, 0, 0);
	अगर (hv_err)
		जाओ out_मुक्त_irqs;

	hv_err = sun4v_ldc_tx_qconf(lp->id, lp->tx_ra, lp->tx_num_entries);
	अगर (hv_err)
		जाओ out_मुक्त_irqs;

	hv_err = sun4v_ldc_rx_qconf(lp->id, 0, 0);
	अगर (hv_err)
		जाओ out_unmap_tx;

	hv_err = sun4v_ldc_rx_qconf(lp->id, lp->rx_ra, lp->rx_num_entries);
	अगर (hv_err)
		जाओ out_unmap_tx;

	lp->flags |= LDC_FLAG_REGISTERED_QUEUES;

	hv_err = sun4v_ldc_tx_get_state(lp->id,
					&lp->tx_head,
					&lp->tx_tail,
					&lp->chan_state);
	err = -EBUSY;
	अगर (hv_err)
		जाओ out_unmap_rx;

	lp->tx_acked = lp->tx_head;

	lp->hs_state = LDC_HS_OPEN;
	ldc_set_state(lp, LDC_STATE_BOUND);

	अगर (lp->cfg.mode == LDC_MODE_RAW) अणु
		/*
		 * There is no handshake in RAW mode, so handshake
		 * is completed.
		 */
		lp->hs_state = LDC_HS_COMPLETE;
	पूर्ण

	spin_unlock_irqrestore(&lp->lock, flags);

	वापस 0;

out_unmap_rx:
	lp->flags &= ~LDC_FLAG_REGISTERED_QUEUES;
	sun4v_ldc_rx_qconf(lp->id, 0, 0);

out_unmap_tx:
	sun4v_ldc_tx_qconf(lp->id, 0, 0);

out_मुक्त_irqs:
	lp->flags &= ~LDC_FLAG_REGISTERED_IRQS;
	मुक्त_irq(lp->cfg.tx_irq, lp);
	मुक्त_irq(lp->cfg.rx_irq, lp);

	spin_unlock_irqrestore(&lp->lock, flags);

	वापस err;
पूर्ण
EXPORT_SYMBOL(ldc_bind);

पूर्णांक ldc_connect(काष्ठा ldc_channel *lp)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक err;

	अगर (lp->cfg.mode == LDC_MODE_RAW)
		वापस -EINVAL;

	spin_lock_irqsave(&lp->lock, flags);

	अगर (!(lp->flags & LDC_FLAG_ALLOCED_QUEUES) ||
	    !(lp->flags & LDC_FLAG_REGISTERED_QUEUES) ||
	    lp->hs_state != LDC_HS_OPEN)
		err = ((lp->hs_state > LDC_HS_OPEN) ? 0 : -EINVAL);
	अन्यथा
		err = start_handshake(lp);

	spin_unlock_irqrestore(&lp->lock, flags);

	वापस err;
पूर्ण
EXPORT_SYMBOL(ldc_connect);

पूर्णांक ldc_disconnect(काष्ठा ldc_channel *lp)
अणु
	अचिन्हित दीर्घ hv_err, flags;
	पूर्णांक err;

	अगर (lp->cfg.mode == LDC_MODE_RAW)
		वापस -EINVAL;

	अगर (!(lp->flags & LDC_FLAG_ALLOCED_QUEUES) ||
	    !(lp->flags & LDC_FLAG_REGISTERED_QUEUES))
		वापस -EINVAL;

	spin_lock_irqsave(&lp->lock, flags);

	err = -ENODEV;
	hv_err = sun4v_ldc_tx_qconf(lp->id, 0, 0);
	अगर (hv_err)
		जाओ out_err;

	hv_err = sun4v_ldc_tx_qconf(lp->id, lp->tx_ra, lp->tx_num_entries);
	अगर (hv_err)
		जाओ out_err;

	hv_err = sun4v_ldc_rx_qconf(lp->id, 0, 0);
	अगर (hv_err)
		जाओ out_err;

	hv_err = sun4v_ldc_rx_qconf(lp->id, lp->rx_ra, lp->rx_num_entries);
	अगर (hv_err)
		जाओ out_err;

	ldc_set_state(lp, LDC_STATE_BOUND);
	lp->hs_state = LDC_HS_OPEN;
	lp->flags |= LDC_FLAG_RESET;

	spin_unlock_irqrestore(&lp->lock, flags);

	वापस 0;

out_err:
	sun4v_ldc_tx_qconf(lp->id, 0, 0);
	sun4v_ldc_rx_qconf(lp->id, 0, 0);
	मुक्त_irq(lp->cfg.tx_irq, lp);
	मुक्त_irq(lp->cfg.rx_irq, lp);
	lp->flags &= ~(LDC_FLAG_REGISTERED_IRQS |
		       LDC_FLAG_REGISTERED_QUEUES);
	ldc_set_state(lp, LDC_STATE_INIT);

	spin_unlock_irqrestore(&lp->lock, flags);

	वापस err;
पूर्ण
EXPORT_SYMBOL(ldc_disconnect);

पूर्णांक ldc_state(काष्ठा ldc_channel *lp)
अणु
	वापस lp->state;
पूर्ण
EXPORT_SYMBOL(ldc_state);

व्योम ldc_set_state(काष्ठा ldc_channel *lp, u8 state)
अणु
	ldcdbg(STATE, "STATE (%s) --> (%s)\n",
	       state_to_str(lp->state),
	       state_to_str(state));

	lp->state = state;
पूर्ण
EXPORT_SYMBOL(ldc_set_state);

पूर्णांक ldc_mode(काष्ठा ldc_channel *lp)
अणु
	वापस lp->cfg.mode;
पूर्ण
EXPORT_SYMBOL(ldc_mode);

पूर्णांक ldc_rx_reset(काष्ठा ldc_channel *lp)
अणु
	वापस __set_rx_head(lp, lp->rx_tail);
पूर्ण
EXPORT_SYMBOL(ldc_rx_reset);

व्योम __ldc_prपूर्णांक(काष्ठा ldc_channel *lp, स्थिर अक्षर *caller)
अणु
	pr_info("%s: id=0x%lx flags=0x%x state=%s cstate=0x%lx hsstate=0x%x\n"
		"\trx_h=0x%lx rx_t=0x%lx rx_n=%ld\n"
		"\ttx_h=0x%lx tx_t=0x%lx tx_n=%ld\n"
		"\trcv_nxt=%u snd_nxt=%u\n",
		caller, lp->id, lp->flags, state_to_str(lp->state),
		lp->chan_state, lp->hs_state,
		lp->rx_head, lp->rx_tail, lp->rx_num_entries,
		lp->tx_head, lp->tx_tail, lp->tx_num_entries,
		lp->rcv_nxt, lp->snd_nxt);
पूर्ण
EXPORT_SYMBOL(__ldc_prपूर्णांक);

अटल पूर्णांक ग_लिखो_raw(काष्ठा ldc_channel *lp, स्थिर व्योम *buf, अचिन्हित पूर्णांक size)
अणु
	काष्ठा ldc_packet *p;
	अचिन्हित दीर्घ new_tail, hv_err;
	पूर्णांक err;

	hv_err = sun4v_ldc_tx_get_state(lp->id, &lp->tx_head, &lp->tx_tail,
					&lp->chan_state);
	अगर (unlikely(hv_err))
		वापस -EBUSY;

	अगर (unlikely(lp->chan_state != LDC_CHANNEL_UP))
		वापस LDC_ABORT(lp);

	अगर (size > LDC_PACKET_SIZE)
		वापस -EMSGSIZE;

	p = data_get_tx_packet(lp, &new_tail);
	अगर (!p)
		वापस -EAGAIN;

	स_नकल(p, buf, size);

	err = send_tx_packet(lp, p, new_tail);
	अगर (!err)
		err = size;

	वापस err;
पूर्ण

अटल पूर्णांक पढ़ो_raw(काष्ठा ldc_channel *lp, व्योम *buf, अचिन्हित पूर्णांक size)
अणु
	काष्ठा ldc_packet *p;
	अचिन्हित दीर्घ hv_err, new;
	पूर्णांक err;

	अगर (size < LDC_PACKET_SIZE)
		वापस -EINVAL;

	hv_err = sun4v_ldc_rx_get_state(lp->id,
					&lp->rx_head,
					&lp->rx_tail,
					&lp->chan_state);
	अगर (hv_err)
		वापस LDC_ABORT(lp);

	अगर (lp->chan_state == LDC_CHANNEL_DOWN ||
	    lp->chan_state == LDC_CHANNEL_RESETTING)
		वापस -ECONNRESET;

	अगर (lp->rx_head == lp->rx_tail)
		वापस 0;

	p = lp->rx_base + (lp->rx_head / LDC_PACKET_SIZE);
	स_नकल(buf, p, LDC_PACKET_SIZE);

	new = rx_advance(lp, lp->rx_head);
	lp->rx_head = new;

	err = __set_rx_head(lp, new);
	अगर (err < 0)
		err = -ECONNRESET;
	अन्यथा
		err = LDC_PACKET_SIZE;

	वापस err;
पूर्ण

अटल स्थिर काष्ठा ldc_mode_ops raw_ops = अणु
	.ग_लिखो		=	ग_लिखो_raw,
	.पढ़ो		=	पढ़ो_raw,
पूर्ण;

अटल पूर्णांक ग_लिखो_nonraw(काष्ठा ldc_channel *lp, स्थिर व्योम *buf,
			अचिन्हित पूर्णांक size)
अणु
	अचिन्हित दीर्घ hv_err, tail;
	अचिन्हित पूर्णांक copied;
	u32 seq;
	पूर्णांक err;

	hv_err = sun4v_ldc_tx_get_state(lp->id, &lp->tx_head, &lp->tx_tail,
					&lp->chan_state);
	अगर (unlikely(hv_err))
		वापस -EBUSY;

	अगर (unlikely(lp->chan_state != LDC_CHANNEL_UP))
		वापस LDC_ABORT(lp);

	अगर (!tx_has_space_क्रम(lp, size))
		वापस -EAGAIN;

	seq = lp->snd_nxt;
	copied = 0;
	tail = lp->tx_tail;
	जबतक (copied < size) अणु
		काष्ठा ldc_packet *p = lp->tx_base + (tail / LDC_PACKET_SIZE);
		u8 *data = ((lp->cfg.mode == LDC_MODE_UNRELIABLE) ?
			    p->u.u_data :
			    p->u.r.r_data);
		पूर्णांक data_len;

		p->type = LDC_DATA;
		p->stype = LDC_INFO;
		p->ctrl = 0;

		data_len = size - copied;
		अगर (data_len > lp->mss)
			data_len = lp->mss;

		BUG_ON(data_len > LDC_LEN);

		p->env = (data_len |
			  (copied == 0 ? LDC_START : 0) |
			  (data_len == size - copied ? LDC_STOP : 0));

		p->seqid = ++seq;

		ldcdbg(DATA, "SENT DATA [%02x:%02x:%02x:%02x:%08x]\n",
		       p->type,
		       p->stype,
		       p->ctrl,
		       p->env,
		       p->seqid);

		स_नकल(data, buf, data_len);
		buf += data_len;
		copied += data_len;

		tail = tx_advance(lp, tail);
	पूर्ण

	err = set_tx_tail(lp, tail);
	अगर (!err) अणु
		lp->snd_nxt = seq;
		err = size;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक rx_bad_seq(काष्ठा ldc_channel *lp, काष्ठा ldc_packet *p,
		      काष्ठा ldc_packet *first_frag)
अणु
	पूर्णांक err;

	अगर (first_frag)
		lp->rcv_nxt = first_frag->seqid - 1;

	err = send_data_nack(lp, p);
	अगर (err)
		वापस err;

	err = ldc_rx_reset(lp);
	अगर (err < 0)
		वापस LDC_ABORT(lp);

	वापस 0;
पूर्ण

अटल पूर्णांक data_ack_nack(काष्ठा ldc_channel *lp, काष्ठा ldc_packet *p)
अणु
	अगर (p->stype & LDC_ACK) अणु
		पूर्णांक err = process_data_ack(lp, p);
		अगर (err)
			वापस err;
	पूर्ण
	अगर (p->stype & LDC_NACK)
		वापस LDC_ABORT(lp);

	वापस 0;
पूर्ण

अटल पूर्णांक rx_data_रुको(काष्ठा ldc_channel *lp, अचिन्हित दीर्घ cur_head)
अणु
	अचिन्हित दीर्घ dummy;
	पूर्णांक limit = 1000;

	ldcdbg(DATA, "DATA WAIT cur_head[%lx] rx_head[%lx] rx_tail[%lx]\n",
	       cur_head, lp->rx_head, lp->rx_tail);
	जबतक (limit-- > 0) अणु
		अचिन्हित दीर्घ hv_err;

		hv_err = sun4v_ldc_rx_get_state(lp->id,
						&dummy,
						&lp->rx_tail,
						&lp->chan_state);
		अगर (hv_err)
			वापस LDC_ABORT(lp);

		अगर (lp->chan_state == LDC_CHANNEL_DOWN ||
		    lp->chan_state == LDC_CHANNEL_RESETTING)
			वापस -ECONNRESET;

		अगर (cur_head != lp->rx_tail) अणु
			ldcdbg(DATA, "DATA WAIT DONE "
			       "head[%lx] tail[%lx] chan_state[%lx]\n",
			       dummy, lp->rx_tail, lp->chan_state);
			वापस 0;
		पूर्ण

		udelay(1);
	पूर्ण
	वापस -EAGAIN;
पूर्ण

अटल पूर्णांक rx_set_head(काष्ठा ldc_channel *lp, अचिन्हित दीर्घ head)
अणु
	पूर्णांक err = __set_rx_head(lp, head);

	अगर (err < 0)
		वापस LDC_ABORT(lp);

	lp->rx_head = head;
	वापस 0;
पूर्ण

अटल व्योम send_data_ack(काष्ठा ldc_channel *lp)
अणु
	अचिन्हित दीर्घ new_tail;
	काष्ठा ldc_packet *p;

	p = data_get_tx_packet(lp, &new_tail);
	अगर (likely(p)) अणु
		पूर्णांक err;

		स_रखो(p, 0, माप(*p));
		p->type = LDC_DATA;
		p->stype = LDC_ACK;
		p->ctrl = 0;
		p->seqid = lp->snd_nxt + 1;
		p->u.r.ackid = lp->rcv_nxt;

		err = send_tx_packet(lp, p, new_tail);
		अगर (!err)
			lp->snd_nxt++;
	पूर्ण
पूर्ण

अटल पूर्णांक पढ़ो_nonraw(काष्ठा ldc_channel *lp, व्योम *buf, अचिन्हित पूर्णांक size)
अणु
	काष्ठा ldc_packet *first_frag;
	अचिन्हित दीर्घ hv_err, new;
	पूर्णांक err, copied;

	hv_err = sun4v_ldc_rx_get_state(lp->id,
					&lp->rx_head,
					&lp->rx_tail,
					&lp->chan_state);
	अगर (hv_err)
		वापस LDC_ABORT(lp);

	अगर (lp->chan_state == LDC_CHANNEL_DOWN ||
	    lp->chan_state == LDC_CHANNEL_RESETTING)
		वापस -ECONNRESET;

	अगर (lp->rx_head == lp->rx_tail)
		वापस 0;

	first_frag = शून्य;
	copied = err = 0;
	new = lp->rx_head;
	जबतक (1) अणु
		काष्ठा ldc_packet *p;
		पूर्णांक pkt_len;

		BUG_ON(new == lp->rx_tail);
		p = lp->rx_base + (new / LDC_PACKET_SIZE);

		ldcdbg(RX, "RX read pkt[%02x:%02x:%02x:%02x:%08x:%08x] "
		       "rcv_nxt[%08x]\n",
		       p->type,
		       p->stype,
		       p->ctrl,
		       p->env,
		       p->seqid,
		       p->u.r.ackid,
		       lp->rcv_nxt);

		अगर (unlikely(!rx_seq_ok(lp, p->seqid))) अणु
			err = rx_bad_seq(lp, p, first_frag);
			copied = 0;
			अवरोध;
		पूर्ण

		अगर (p->type & LDC_CTRL) अणु
			err = process_control_frame(lp, p);
			अगर (err < 0)
				अवरोध;
			err = 0;
		पूर्ण

		lp->rcv_nxt = p->seqid;

		/*
		 * If this is a control-only packet, there is nothing
		 * अन्यथा to करो but advance the rx queue since the packet
		 * was alपढ़ोy processed above.
		 */
		अगर (!(p->type & LDC_DATA)) अणु
			new = rx_advance(lp, new);
			अवरोध;
		पूर्ण
		अगर (p->stype & (LDC_ACK | LDC_NACK)) अणु
			err = data_ack_nack(lp, p);
			अगर (err)
				अवरोध;
		पूर्ण
		अगर (!(p->stype & LDC_INFO)) अणु
			new = rx_advance(lp, new);
			err = rx_set_head(lp, new);
			अगर (err)
				अवरोध;
			जाओ no_data;
		पूर्ण

		pkt_len = p->env & LDC_LEN;

		/* Every initial packet starts with the START bit set.
		 *
		 * Singleton packets will have both START+STOP set.
		 *
		 * Fragments will have START set in the first frame, STOP
		 * set in the last frame, and neither bit set in middle
		 * frames of the packet.
		 *
		 * Thereक्रमe अगर we are at the beginning of a packet and
		 * we करोn't see START, or we are in the middle of a fragmented
		 * packet and करो see START, we are unsynchronized and should
		 * flush the RX queue.
		 */
		अगर ((first_frag == शून्य && !(p->env & LDC_START)) ||
		    (first_frag != शून्य &&  (p->env & LDC_START))) अणु
			अगर (!first_frag)
				new = rx_advance(lp, new);

			err = rx_set_head(lp, new);
			अगर (err)
				अवरोध;

			अगर (!first_frag)
				जाओ no_data;
		पूर्ण
		अगर (!first_frag)
			first_frag = p;

		अगर (pkt_len > size - copied) अणु
			/* User didn't give us a big enough buffer,
			 * what to करो?  This is a pretty serious error.
			 *
			 * Since we haven't updated the RX ring head to
			 * consume any of the packets, संकेत the error
			 * to the user and just leave the RX ring alone.
			 *
			 * This seems the best behavior because this allows
			 * a user of the LDC layer to start with a small
			 * RX buffer क्रम ldc_पढ़ो() calls and use -EMSGSIZE
			 * as a cue to enlarge it's पढ़ो buffer.
			 */
			err = -EMSGSIZE;
			अवरोध;
		पूर्ण

		/* Ok, we are gonna eat this one.  */
		new = rx_advance(lp, new);

		स_नकल(buf,
		       (lp->cfg.mode == LDC_MODE_UNRELIABLE ?
			p->u.u_data : p->u.r.r_data), pkt_len);
		buf += pkt_len;
		copied += pkt_len;

		अगर (p->env & LDC_STOP)
			अवरोध;

no_data:
		अगर (new == lp->rx_tail) अणु
			err = rx_data_रुको(lp, new);
			अगर (err)
				अवरोध;
		पूर्ण
	पूर्ण

	अगर (!err)
		err = rx_set_head(lp, new);

	अगर (err && first_frag)
		lp->rcv_nxt = first_frag->seqid - 1;

	अगर (!err) अणु
		err = copied;
		अगर (err > 0 && lp->cfg.mode != LDC_MODE_UNRELIABLE)
			send_data_ack(lp);
	पूर्ण

	वापस err;
पूर्ण

अटल स्थिर काष्ठा ldc_mode_ops nonraw_ops = अणु
	.ग_लिखो		=	ग_लिखो_nonraw,
	.पढ़ो		=	पढ़ो_nonraw,
पूर्ण;

अटल पूर्णांक ग_लिखो_stream(काष्ठा ldc_channel *lp, स्थिर व्योम *buf,
			अचिन्हित पूर्णांक size)
अणु
	अगर (size > lp->cfg.mtu)
		size = lp->cfg.mtu;
	वापस ग_लिखो_nonraw(lp, buf, size);
पूर्ण

अटल पूर्णांक पढ़ो_stream(काष्ठा ldc_channel *lp, व्योम *buf, अचिन्हित पूर्णांक size)
अणु
	अगर (!lp->mssbuf_len) अणु
		पूर्णांक err = पढ़ो_nonraw(lp, lp->mssbuf, lp->cfg.mtu);
		अगर (err < 0)
			वापस err;

		lp->mssbuf_len = err;
		lp->mssbuf_off = 0;
	पूर्ण

	अगर (size > lp->mssbuf_len)
		size = lp->mssbuf_len;
	स_नकल(buf, lp->mssbuf + lp->mssbuf_off, size);

	lp->mssbuf_off += size;
	lp->mssbuf_len -= size;

	वापस size;
पूर्ण

अटल स्थिर काष्ठा ldc_mode_ops stream_ops = अणु
	.ग_लिखो		=	ग_लिखो_stream,
	.पढ़ो		=	पढ़ो_stream,
पूर्ण;

पूर्णांक ldc_ग_लिखो(काष्ठा ldc_channel *lp, स्थिर व्योम *buf, अचिन्हित पूर्णांक size)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक err;

	अगर (!buf)
		वापस -EINVAL;

	अगर (!size)
		वापस 0;

	spin_lock_irqsave(&lp->lock, flags);

	अगर (lp->hs_state != LDC_HS_COMPLETE)
		err = -ENOTCONN;
	अन्यथा
		err = lp->mops->ग_लिखो(lp, buf, size);

	spin_unlock_irqrestore(&lp->lock, flags);

	वापस err;
पूर्ण
EXPORT_SYMBOL(ldc_ग_लिखो);

पूर्णांक ldc_पढ़ो(काष्ठा ldc_channel *lp, व्योम *buf, अचिन्हित पूर्णांक size)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक err;

	ldcdbg(RX, "%s: entered size=%d\n", __func__, size);

	अगर (!buf)
		वापस -EINVAL;

	अगर (!size)
		वापस 0;

	spin_lock_irqsave(&lp->lock, flags);

	अगर (lp->hs_state != LDC_HS_COMPLETE)
		err = -ENOTCONN;
	अन्यथा
		err = lp->mops->पढ़ो(lp, buf, size);

	spin_unlock_irqrestore(&lp->lock, flags);

	ldcdbg(RX, "%s: mode=%d, head=%lu, tail=%lu rv=%d\n", __func__,
	       lp->cfg.mode, lp->rx_head, lp->rx_tail, err);

	वापस err;
पूर्ण
EXPORT_SYMBOL(ldc_पढ़ो);

अटल u64 pagesize_code(व्योम)
अणु
	चयन (PAGE_SIZE) अणु
	शेष:
	हाल (8ULL * 1024ULL):
		वापस 0;
	हाल (64ULL * 1024ULL):
		वापस 1;
	हाल (512ULL * 1024ULL):
		वापस 2;
	हाल (4ULL * 1024ULL * 1024ULL):
		वापस 3;
	हाल (32ULL * 1024ULL * 1024ULL):
		वापस 4;
	हाल (256ULL * 1024ULL * 1024ULL):
		वापस 5;
	पूर्ण
पूर्ण

अटल u64 make_cookie(u64 index, u64 pgsz_code, u64 page_offset)
अणु
	वापस ((pgsz_code << COOKIE_PGSZ_CODE_SHIFT) |
		(index << PAGE_SHIFT) |
		page_offset);
पूर्ण


अटल काष्ठा ldc_mtable_entry *alloc_npages(काष्ठा ldc_iommu *iommu,
					     अचिन्हित दीर्घ npages)
अणु
	दीर्घ entry;

	entry = iommu_tbl_range_alloc(शून्य, &iommu->iommu_map_table,
				      npages, शून्य, (अचिन्हित दीर्घ)-1, 0);
	अगर (unlikely(entry == IOMMU_ERROR_CODE))
		वापस शून्य;

	वापस iommu->page_table + entry;
पूर्ण

अटल u64 perm_to_mte(अचिन्हित पूर्णांक map_perm)
अणु
	u64 mte_base;

	mte_base = pagesize_code();

	अगर (map_perm & LDC_MAP_SHADOW) अणु
		अगर (map_perm & LDC_MAP_R)
			mte_base |= LDC_MTE_COPY_R;
		अगर (map_perm & LDC_MAP_W)
			mte_base |= LDC_MTE_COPY_W;
	पूर्ण
	अगर (map_perm & LDC_MAP_सूचीECT) अणु
		अगर (map_perm & LDC_MAP_R)
			mte_base |= LDC_MTE_READ;
		अगर (map_perm & LDC_MAP_W)
			mte_base |= LDC_MTE_WRITE;
		अगर (map_perm & LDC_MAP_X)
			mte_base |= LDC_MTE_EXEC;
	पूर्ण
	अगर (map_perm & LDC_MAP_IO) अणु
		अगर (map_perm & LDC_MAP_R)
			mte_base |= LDC_MTE_IOMMU_R;
		अगर (map_perm & LDC_MAP_W)
			mte_base |= LDC_MTE_IOMMU_W;
	पूर्ण

	वापस mte_base;
पूर्ण

अटल पूर्णांक pages_in_region(अचिन्हित दीर्घ base, दीर्घ len)
अणु
	पूर्णांक count = 0;

	करो अणु
		अचिन्हित दीर्घ new = (base + PAGE_SIZE) & PAGE_MASK;

		len -= (new - base);
		base = new;
		count++;
	पूर्ण जबतक (len > 0);

	वापस count;
पूर्ण

काष्ठा cookie_state अणु
	काष्ठा ldc_mtable_entry		*page_table;
	काष्ठा ldc_trans_cookie		*cookies;
	u64				mte_base;
	u64				prev_cookie;
	u32				pte_idx;
	u32				nc;
पूर्ण;

अटल व्योम fill_cookies(काष्ठा cookie_state *sp, अचिन्हित दीर्घ pa,
			 अचिन्हित दीर्घ off, अचिन्हित दीर्घ len)
अणु
	करो अणु
		अचिन्हित दीर्घ tlen, new = pa + PAGE_SIZE;
		u64 this_cookie;

		sp->page_table[sp->pte_idx].mte = sp->mte_base | pa;

		tlen = PAGE_SIZE;
		अगर (off)
			tlen = PAGE_SIZE - off;
		अगर (tlen > len)
			tlen = len;

		this_cookie = make_cookie(sp->pte_idx,
					  pagesize_code(), off);

		off = 0;

		अगर (this_cookie == sp->prev_cookie) अणु
			sp->cookies[sp->nc - 1].cookie_size += tlen;
		पूर्ण अन्यथा अणु
			sp->cookies[sp->nc].cookie_addr = this_cookie;
			sp->cookies[sp->nc].cookie_size = tlen;
			sp->nc++;
		पूर्ण
		sp->prev_cookie = this_cookie + tlen;

		sp->pte_idx++;

		len -= tlen;
		pa = new;
	पूर्ण जबतक (len > 0);
पूर्ण

अटल पूर्णांक sg_count_one(काष्ठा scatterlist *sg)
अणु
	अचिन्हित दीर्घ base = page_to_pfn(sg_page(sg)) << PAGE_SHIFT;
	दीर्घ len = sg->length;

	अगर ((sg->offset | len) & (8UL - 1))
		वापस -EFAULT;

	वापस pages_in_region(base + sg->offset, len);
पूर्ण

अटल पूर्णांक sg_count_pages(काष्ठा scatterlist *sg, पूर्णांक num_sg)
अणु
	पूर्णांक count;
	पूर्णांक i;

	count = 0;
	क्रम (i = 0; i < num_sg; i++) अणु
		पूर्णांक err = sg_count_one(sg + i);
		अगर (err < 0)
			वापस err;
		count += err;
	पूर्ण

	वापस count;
पूर्ण

पूर्णांक ldc_map_sg(काष्ठा ldc_channel *lp,
	       काष्ठा scatterlist *sg, पूर्णांक num_sg,
	       काष्ठा ldc_trans_cookie *cookies, पूर्णांक ncookies,
	       अचिन्हित पूर्णांक map_perm)
अणु
	अचिन्हित दीर्घ i, npages;
	काष्ठा ldc_mtable_entry *base;
	काष्ठा cookie_state state;
	काष्ठा ldc_iommu *iommu;
	पूर्णांक err;
	काष्ठा scatterlist *s;

	अगर (map_perm & ~LDC_MAP_ALL)
		वापस -EINVAL;

	err = sg_count_pages(sg, num_sg);
	अगर (err < 0)
		वापस err;

	npages = err;
	अगर (err > ncookies)
		वापस -EMSGSIZE;

	iommu = &lp->iommu;

	base = alloc_npages(iommu, npages);

	अगर (!base)
		वापस -ENOMEM;

	state.page_table = iommu->page_table;
	state.cookies = cookies;
	state.mte_base = perm_to_mte(map_perm);
	state.prev_cookie = ~(u64)0;
	state.pte_idx = (base - iommu->page_table);
	state.nc = 0;

	क्रम_each_sg(sg, s, num_sg, i) अणु
		fill_cookies(&state, page_to_pfn(sg_page(s)) << PAGE_SHIFT,
			     s->offset, s->length);
	पूर्ण

	वापस state.nc;
पूर्ण
EXPORT_SYMBOL(ldc_map_sg);

पूर्णांक ldc_map_single(काष्ठा ldc_channel *lp,
		   व्योम *buf, अचिन्हित पूर्णांक len,
		   काष्ठा ldc_trans_cookie *cookies, पूर्णांक ncookies,
		   अचिन्हित पूर्णांक map_perm)
अणु
	अचिन्हित दीर्घ npages, pa;
	काष्ठा ldc_mtable_entry *base;
	काष्ठा cookie_state state;
	काष्ठा ldc_iommu *iommu;

	अगर ((map_perm & ~LDC_MAP_ALL) || (ncookies < 1))
		वापस -EINVAL;

	pa = __pa(buf);
	अगर ((pa | len) & (8UL - 1))
		वापस -EFAULT;

	npages = pages_in_region(pa, len);

	iommu = &lp->iommu;

	base = alloc_npages(iommu, npages);

	अगर (!base)
		वापस -ENOMEM;

	state.page_table = iommu->page_table;
	state.cookies = cookies;
	state.mte_base = perm_to_mte(map_perm);
	state.prev_cookie = ~(u64)0;
	state.pte_idx = (base - iommu->page_table);
	state.nc = 0;
	fill_cookies(&state, (pa & PAGE_MASK), (pa & ~PAGE_MASK), len);
	BUG_ON(state.nc > ncookies);

	वापस state.nc;
पूर्ण
EXPORT_SYMBOL(ldc_map_single);


अटल व्योम मुक्त_npages(अचिन्हित दीर्घ id, काष्ठा ldc_iommu *iommu,
			u64 cookie, u64 size)
अणु
	अचिन्हित दीर्घ npages, entry;

	npages = PAGE_ALIGN(((cookie & ~PAGE_MASK) + size)) >> PAGE_SHIFT;

	entry = ldc_cookie_to_index(cookie, iommu);
	ldc_demap(iommu, id, cookie, entry, npages);
	iommu_tbl_range_मुक्त(&iommu->iommu_map_table, cookie, npages, entry);
पूर्ण

व्योम ldc_unmap(काष्ठा ldc_channel *lp, काष्ठा ldc_trans_cookie *cookies,
	       पूर्णांक ncookies)
अणु
	काष्ठा ldc_iommu *iommu = &lp->iommu;
	पूर्णांक i;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&iommu->lock, flags);
	क्रम (i = 0; i < ncookies; i++) अणु
		u64 addr = cookies[i].cookie_addr;
		u64 size = cookies[i].cookie_size;

		मुक्त_npages(lp->id, iommu, addr, size);
	पूर्ण
	spin_unlock_irqrestore(&iommu->lock, flags);
पूर्ण
EXPORT_SYMBOL(ldc_unmap);

पूर्णांक ldc_copy(काष्ठा ldc_channel *lp, पूर्णांक copy_dir,
	     व्योम *buf, अचिन्हित पूर्णांक len, अचिन्हित दीर्घ offset,
	     काष्ठा ldc_trans_cookie *cookies, पूर्णांक ncookies)
अणु
	अचिन्हित पूर्णांक orig_len;
	अचिन्हित दीर्घ ra;
	पूर्णांक i;

	अगर (copy_dir != LDC_COPY_IN && copy_dir != LDC_COPY_OUT) अणु
		prपूर्णांकk(KERN_ERR PFX "ldc_copy: ID[%lu] Bad copy_dir[%d]\n",
		       lp->id, copy_dir);
		वापस -EINVAL;
	पूर्ण

	ra = __pa(buf);
	अगर ((ra | len | offset) & (8UL - 1)) अणु
		prपूर्णांकk(KERN_ERR PFX "ldc_copy: ID[%lu] Unaligned buffer "
		       "ra[%lx] len[%x] offset[%lx]\n",
		       lp->id, ra, len, offset);
		वापस -EFAULT;
	पूर्ण

	अगर (lp->hs_state != LDC_HS_COMPLETE ||
	    (lp->flags & LDC_FLAG_RESET)) अणु
		prपूर्णांकk(KERN_ERR PFX "ldc_copy: ID[%lu] Link down hs_state[%x] "
		       "flags[%x]\n", lp->id, lp->hs_state, lp->flags);
		वापस -ECONNRESET;
	पूर्ण

	orig_len = len;
	क्रम (i = 0; i < ncookies; i++) अणु
		अचिन्हित दीर्घ cookie_raddr = cookies[i].cookie_addr;
		अचिन्हित दीर्घ this_len = cookies[i].cookie_size;
		अचिन्हित दीर्घ actual_len;

		अगर (unlikely(offset)) अणु
			अचिन्हित दीर्घ this_off = offset;

			अगर (this_off > this_len)
				this_off = this_len;

			offset -= this_off;
			this_len -= this_off;
			अगर (!this_len)
				जारी;
			cookie_raddr += this_off;
		पूर्ण

		अगर (this_len > len)
			this_len = len;

		जबतक (1) अणु
			अचिन्हित दीर्घ hv_err;

			hv_err = sun4v_ldc_copy(lp->id, copy_dir,
						cookie_raddr, ra,
						this_len, &actual_len);
			अगर (unlikely(hv_err)) अणु
				prपूर्णांकk(KERN_ERR PFX "ldc_copy: ID[%lu] "
				       "HV error %lu\n",
				       lp->id, hv_err);
				अगर (lp->hs_state != LDC_HS_COMPLETE ||
				    (lp->flags & LDC_FLAG_RESET))
					वापस -ECONNRESET;
				अन्यथा
					वापस -EFAULT;
			पूर्ण

			cookie_raddr += actual_len;
			ra += actual_len;
			len -= actual_len;
			अगर (actual_len == this_len)
				अवरोध;

			this_len -= actual_len;
		पूर्ण

		अगर (!len)
			अवरोध;
	पूर्ण

	/* It is caller policy what to करो about लघु copies.
	 * For example, a networking driver can declare the
	 * packet a runt and drop it.
	 */

	वापस orig_len - len;
पूर्ण
EXPORT_SYMBOL(ldc_copy);

व्योम *ldc_alloc_exp_dring(काष्ठा ldc_channel *lp, अचिन्हित पूर्णांक len,
			  काष्ठा ldc_trans_cookie *cookies, पूर्णांक *ncookies,
			  अचिन्हित पूर्णांक map_perm)
अणु
	व्योम *buf;
	पूर्णांक err;

	अगर (len & (8UL - 1))
		वापस ERR_PTR(-EINVAL);

	buf = kzalloc(len, GFP_ATOMIC);
	अगर (!buf)
		वापस ERR_PTR(-ENOMEM);

	err = ldc_map_single(lp, buf, len, cookies, *ncookies, map_perm);
	अगर (err < 0) अणु
		kमुक्त(buf);
		वापस ERR_PTR(err);
	पूर्ण
	*ncookies = err;

	वापस buf;
पूर्ण
EXPORT_SYMBOL(ldc_alloc_exp_dring);

व्योम ldc_मुक्त_exp_dring(काष्ठा ldc_channel *lp, व्योम *buf, अचिन्हित पूर्णांक len,
			काष्ठा ldc_trans_cookie *cookies, पूर्णांक ncookies)
अणु
	ldc_unmap(lp, cookies, ncookies);
	kमुक्त(buf);
पूर्ण
EXPORT_SYMBOL(ldc_मुक्त_exp_dring);

अटल पूर्णांक __init ldc_init(व्योम)
अणु
	अचिन्हित दीर्घ major, minor;
	काष्ठा mdesc_handle *hp;
	स्थिर u64 *v;
	पूर्णांक err;
	u64 mp;

	hp = mdesc_grab();
	अगर (!hp)
		वापस -ENODEV;

	mp = mdesc_node_by_name(hp, MDESC_NODE_शून्य, "platform");
	err = -ENODEV;
	अगर (mp == MDESC_NODE_शून्य)
		जाओ out;

	v = mdesc_get_property(hp, mp, "domaining-enabled", शून्य);
	अगर (!v)
		जाओ out;

	major = 1;
	minor = 0;
	अगर (sun4v_hvapi_रेजिस्टर(HV_GRP_LDOM, major, &minor)) अणु
		prपूर्णांकk(KERN_INFO PFX "Could not register LDOM hvapi.\n");
		जाओ out;
	पूर्ण

	prपूर्णांकk(KERN_INFO "%s", version);

	अगर (!*v) अणु
		prपूर्णांकk(KERN_INFO PFX "Domaining disabled.\n");
		जाओ out;
	पूर्ण
	lकरोm_करोमुख्यing_enabled = 1;
	err = 0;

out:
	mdesc_release(hp);
	वापस err;
पूर्ण

core_initcall(ldc_init);
