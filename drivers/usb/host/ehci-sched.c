<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (c) 2001-2004 by David Brownell
 * Copyright (c) 2003 Michal Sojka, क्रम high-speed iso transfers
 */

/* this file is part of ehci-hcd.c */

/*-------------------------------------------------------------------------*/

/*
 * EHCI scheduled transaction support:  पूर्णांकerrupt, iso, split iso
 * These are called "periodic" transactions in the EHCI spec.
 *
 * Note that क्रम पूर्णांकerrupt transfers, the QH/QTD manipulation is shared
 * with the "asynchronous" transaction support (control/bulk transfers).
 * The only real dअगरference is in how पूर्णांकerrupt transfers are scheduled.
 *
 * For ISO, we make an "iso_stream" head to serve the same role as a QH.
 * It keeps track of every ITD (or SITD) that's linked, and holds enough
 * pre-calculated schedule data to make appending to the queue be quick.
 */

अटल पूर्णांक ehci_get_frame(काष्ठा usb_hcd *hcd);

/*
 * periodic_next_shaकरोw - वापस "next" poपूर्णांकer on shaकरोw list
 * @periodic: host poपूर्णांकer to qh/itd/sitd
 * @tag: hardware tag क्रम type of this record
 */
अटल जोड़ ehci_shaकरोw *
periodic_next_shaकरोw(काष्ठा ehci_hcd *ehci, जोड़ ehci_shaकरोw *periodic,
		__hc32 tag)
अणु
	चयन (hc32_to_cpu(ehci, tag)) अणु
	हाल Q_TYPE_QH:
		वापस &periodic->qh->qh_next;
	हाल Q_TYPE_FSTN:
		वापस &periodic->fstn->fstn_next;
	हाल Q_TYPE_ITD:
		वापस &periodic->itd->itd_next;
	/* हाल Q_TYPE_SITD: */
	शेष:
		वापस &periodic->sitd->sitd_next;
	पूर्ण
पूर्ण

अटल __hc32 *
shaकरोw_next_periodic(काष्ठा ehci_hcd *ehci, जोड़ ehci_shaकरोw *periodic,
		__hc32 tag)
अणु
	चयन (hc32_to_cpu(ehci, tag)) अणु
	/* our ehci_shaकरोw.qh is actually software part */
	हाल Q_TYPE_QH:
		वापस &periodic->qh->hw->hw_next;
	/* others are hw parts */
	शेष:
		वापस periodic->hw_next;
	पूर्ण
पूर्ण

/* caller must hold ehci->lock */
अटल व्योम periodic_unlink(काष्ठा ehci_hcd *ehci, अचिन्हित frame, व्योम *ptr)
अणु
	जोड़ ehci_shaकरोw	*prev_p = &ehci->pshaकरोw[frame];
	__hc32			*hw_p = &ehci->periodic[frame];
	जोड़ ehci_shaकरोw	here = *prev_p;

	/* find predecessor of "ptr"; hw and shaकरोw lists are in sync */
	जबतक (here.ptr && here.ptr != ptr) अणु
		prev_p = periodic_next_shaकरोw(ehci, prev_p,
				Q_NEXT_TYPE(ehci, *hw_p));
		hw_p = shaकरोw_next_periodic(ehci, &here,
				Q_NEXT_TYPE(ehci, *hw_p));
		here = *prev_p;
	पूर्ण
	/* an पूर्णांकerrupt entry (at list end) could have been shared */
	अगर (!here.ptr)
		वापस;

	/* update shaकरोw and hardware lists ... the old "next" poपूर्णांकers
	 * from ptr may still be in use, the caller updates them.
	 */
	*prev_p = *periodic_next_shaकरोw(ehci, &here,
			Q_NEXT_TYPE(ehci, *hw_p));

	अगर (!ehci->use_dummy_qh ||
	    *shaकरोw_next_periodic(ehci, &here, Q_NEXT_TYPE(ehci, *hw_p))
			!= EHCI_LIST_END(ehci))
		*hw_p = *shaकरोw_next_periodic(ehci, &here,
				Q_NEXT_TYPE(ehci, *hw_p));
	अन्यथा
		*hw_p = cpu_to_hc32(ehci, ehci->dummy->qh_dma);
पूर्ण

/*-------------------------------------------------------------------------*/

/* Bandwidth and TT management */

/* Find the TT data काष्ठाure क्रम this device; create it अगर necessary */
अटल काष्ठा ehci_tt *find_tt(काष्ठा usb_device *udev)
अणु
	काष्ठा usb_tt		*utt = udev->tt;
	काष्ठा ehci_tt		*tt, **tt_index, **ptt;
	अचिन्हित		port;
	bool			allocated_index = false;

	अगर (!utt)
		वापस शून्य;		/* Not below a TT */

	/*
	 * Find/create our data काष्ठाure.
	 * For hubs with a single TT, we get it directly.
	 * For hubs with multiple TTs, there's an extra level of poपूर्णांकers.
	 */
	tt_index = शून्य;
	अगर (utt->multi) अणु
		tt_index = utt->hcpriv;
		अगर (!tt_index) अणु		/* Create the index array */
			tt_index = kसुस्मृति(utt->hub->maxchild,
					   माप(*tt_index),
					   GFP_ATOMIC);
			अगर (!tt_index)
				वापस ERR_PTR(-ENOMEM);
			utt->hcpriv = tt_index;
			allocated_index = true;
		पूर्ण
		port = udev->ttport - 1;
		ptt = &tt_index[port];
	पूर्ण अन्यथा अणु
		port = 0;
		ptt = (काष्ठा ehci_tt **) &utt->hcpriv;
	पूर्ण

	tt = *ptt;
	अगर (!tt) अणु				/* Create the ehci_tt */
		काष्ठा ehci_hcd		*ehci =
				hcd_to_ehci(bus_to_hcd(udev->bus));

		tt = kzalloc(माप(*tt), GFP_ATOMIC);
		अगर (!tt) अणु
			अगर (allocated_index) अणु
				utt->hcpriv = शून्य;
				kमुक्त(tt_index);
			पूर्ण
			वापस ERR_PTR(-ENOMEM);
		पूर्ण
		list_add_tail(&tt->tt_list, &ehci->tt_list);
		INIT_LIST_HEAD(&tt->ps_list);
		tt->usb_tt = utt;
		tt->tt_port = port;
		*ptt = tt;
	पूर्ण

	वापस tt;
पूर्ण

/* Release the TT above udev, अगर it's not in use */
अटल व्योम drop_tt(काष्ठा usb_device *udev)
अणु
	काष्ठा usb_tt		*utt = udev->tt;
	काष्ठा ehci_tt		*tt, **tt_index, **ptt;
	पूर्णांक			cnt, i;

	अगर (!utt || !utt->hcpriv)
		वापस;		/* Not below a TT, or never allocated */

	cnt = 0;
	अगर (utt->multi) अणु
		tt_index = utt->hcpriv;
		ptt = &tt_index[udev->ttport - 1];

		/* How many entries are left in tt_index? */
		क्रम (i = 0; i < utt->hub->maxchild; ++i)
			cnt += !!tt_index[i];
	पूर्ण अन्यथा अणु
		tt_index = शून्य;
		ptt = (काष्ठा ehci_tt **) &utt->hcpriv;
	पूर्ण

	tt = *ptt;
	अगर (!tt || !list_empty(&tt->ps_list))
		वापस;		/* never allocated, or still in use */

	list_del(&tt->tt_list);
	*ptt = शून्य;
	kमुक्त(tt);
	अगर (cnt == 1) अणु
		utt->hcpriv = शून्य;
		kमुक्त(tt_index);
	पूर्ण
पूर्ण

अटल व्योम bandwidth_dbg(काष्ठा ehci_hcd *ehci, पूर्णांक sign, अक्षर *type,
		काष्ठा ehci_per_sched *ps)
अणु
	dev_dbg(&ps->udev->dev,
			"ep %02x: %s %s @ %u+%u (%u.%u+%u) [%u/%u us] mask %04x\n",
			ps->ep->desc.bEndpoपूर्णांकAddress,
			(sign >= 0 ? "reserve" : "release"), type,
			(ps->bw_phase << 3) + ps->phase_uf, ps->bw_uperiod,
			ps->phase, ps->phase_uf, ps->period,
			ps->usecs, ps->c_usecs, ps->cs_mask);
पूर्ण

अटल व्योम reserve_release_पूर्णांकr_bandwidth(काष्ठा ehci_hcd *ehci,
		काष्ठा ehci_qh *qh, पूर्णांक sign)
अणु
	अचिन्हित		start_uf;
	अचिन्हित		i, j, m;
	पूर्णांक			usecs = qh->ps.usecs;
	पूर्णांक			c_usecs = qh->ps.c_usecs;
	पूर्णांक			tt_usecs = qh->ps.tt_usecs;
	काष्ठा ehci_tt		*tt;

	अगर (qh->ps.phase == NO_FRAME)	/* Bandwidth wasn't reserved */
		वापस;
	start_uf = qh->ps.bw_phase << 3;

	bandwidth_dbg(ehci, sign, "intr", &qh->ps);

	अगर (sign < 0) अणु		/* Release bandwidth */
		usecs = -usecs;
		c_usecs = -c_usecs;
		tt_usecs = -tt_usecs;
	पूर्ण

	/* Entire transaction (high speed) or start-split (full/low speed) */
	क्रम (i = start_uf + qh->ps.phase_uf; i < EHCI_BANDWIDTH_SIZE;
			i += qh->ps.bw_uperiod)
		ehci->bandwidth[i] += usecs;

	/* Complete-split (full/low speed) */
	अगर (qh->ps.c_usecs) अणु
		/* NOTE: adjusपंचांगents needed क्रम FSTN */
		क्रम (i = start_uf; i < EHCI_BANDWIDTH_SIZE;
				i += qh->ps.bw_uperiod) अणु
			क्रम ((j = 2, m = 1 << (j+8)); j < 8; (++j, m <<= 1)) अणु
				अगर (qh->ps.cs_mask & m)
					ehci->bandwidth[i+j] += c_usecs;
			पूर्ण
		पूर्ण
	पूर्ण

	/* FS/LS bus bandwidth */
	अगर (tt_usecs) अणु
		/*
		 * find_tt() will not वापस any error here as we have
		 * alपढ़ोy called find_tt() beक्रमe calling this function
		 * and checked क्रम any error वापस. The previous call
		 * would have created the data काष्ठाure.
		 */
		tt = find_tt(qh->ps.udev);
		अगर (sign > 0)
			list_add_tail(&qh->ps.ps_list, &tt->ps_list);
		अन्यथा
			list_del(&qh->ps.ps_list);

		क्रम (i = start_uf >> 3; i < EHCI_BANDWIDTH_FRAMES;
				i += qh->ps.bw_period)
			tt->bandwidth[i] += tt_usecs;
	पूर्ण
पूर्ण

/*-------------------------------------------------------------------------*/

अटल व्योम compute_tt_budget(u8 budget_table[EHCI_BANDWIDTH_SIZE],
		काष्ठा ehci_tt *tt)
अणु
	काष्ठा ehci_per_sched	*ps;
	अचिन्हित		uframe, uf, x;
	u8			*budget_line;

	अगर (!tt)
		वापस;
	स_रखो(budget_table, 0, EHCI_BANDWIDTH_SIZE);

	/* Add up the contributions from all the endpoपूर्णांकs using this TT */
	list_क्रम_each_entry(ps, &tt->ps_list, ps_list) अणु
		क्रम (uframe = ps->bw_phase << 3; uframe < EHCI_BANDWIDTH_SIZE;
				uframe += ps->bw_uperiod) अणु
			budget_line = &budget_table[uframe];
			x = ps->tt_usecs;

			/* propagate the समय क्रमward */
			क्रम (uf = ps->phase_uf; uf < 8; ++uf) अणु
				x += budget_line[uf];

				/* Each microframe lasts 125 us */
				अगर (x <= 125) अणु
					budget_line[uf] = x;
					अवरोध;
				पूर्ण
				budget_line[uf] = 125;
				x -= 125;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक __maybe_unused same_tt(काष्ठा usb_device *dev1,
		काष्ठा usb_device *dev2)
अणु
	अगर (!dev1->tt || !dev2->tt)
		वापस 0;
	अगर (dev1->tt != dev2->tt)
		वापस 0;
	अगर (dev1->tt->multi)
		वापस dev1->ttport == dev2->ttport;
	अन्यथा
		वापस 1;
पूर्ण

#अगर_घोषित CONFIG_USB_EHCI_TT_NEWSCHED

अटल स्थिर अचिन्हित अक्षर
max_tt_usecs[] = अणु 125, 125, 125, 125, 125, 125, 30, 0 पूर्ण;

/* carryover low/fullspeed bandwidth that crosses uframe boundries */
अटल अंतरभूत व्योम carryover_tt_bandwidth(अचिन्हित लघु tt_usecs[8])
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 7; i++) अणु
		अगर (max_tt_usecs[i] < tt_usecs[i]) अणु
			tt_usecs[i+1] += tt_usecs[i] - max_tt_usecs[i];
			tt_usecs[i] = max_tt_usecs[i];
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Return true अगर the device's tt's करोwnstream bus is available क्रम a
 * periodic transfer of the specअगरied length (usecs), starting at the
 * specअगरied frame/uframe.  Note that (as summarized in section 11.19
 * of the usb 2.0 spec) TTs can buffer multiple transactions क्रम each
 * uframe.
 *
 * The uframe parameter is when the fullspeed/lowspeed transfer
 * should be executed in "B-frame" terms, which is the same as the
 * highspeed ssplit's uframe (which is in "H-frame" terms).  For example
 * a ssplit in "H-frame" 0 causes a transfer in "B-frame" 0.
 * See the EHCI spec sec 4.5 and fig 4.7.
 *
 * This checks अगर the full/lowspeed bus, at the specअगरied starting uframe,
 * has the specअगरied bandwidth available, according to rules listed
 * in USB 2.0 spec section 11.18.1 fig 11-60.
 *
 * This करोes not check अगर the transfer would exceed the max ssplit
 * limit of 16, specअगरied in USB 2.0 spec section 11.18.4 requirement #4,
 * since proper scheduling limits ssplits to less than 16 per uframe.
 */
अटल पूर्णांक tt_available(
	काष्ठा ehci_hcd		*ehci,
	काष्ठा ehci_per_sched	*ps,
	काष्ठा ehci_tt		*tt,
	अचिन्हित		frame,
	अचिन्हित		uframe
)
अणु
	अचिन्हित		period = ps->bw_period;
	अचिन्हित		usecs = ps->tt_usecs;

	अगर ((period == 0) || (uframe >= 7))	/* error */
		वापस 0;

	क्रम (frame &= period - 1; frame < EHCI_BANDWIDTH_FRAMES;
			frame += period) अणु
		अचिन्हित	i, uf;
		अचिन्हित लघु	tt_usecs[8];

		अगर (tt->bandwidth[frame] + usecs > 900)
			वापस 0;

		uf = frame << 3;
		क्रम (i = 0; i < 8; (++i, ++uf))
			tt_usecs[i] = ehci->tt_budget[uf];

		अगर (max_tt_usecs[uframe] <= tt_usecs[uframe])
			वापस 0;

		/* special हाल क्रम isoc transfers larger than 125us:
		 * the first and each subsequent fully used uframe
		 * must be empty, so as to not illegally delay
		 * alपढ़ोy scheduled transactions
		 */
		अगर (usecs > 125) अणु
			पूर्णांक ufs = (usecs / 125);

			क्रम (i = uframe; i < (uframe + ufs) && i < 8; i++)
				अगर (tt_usecs[i] > 0)
					वापस 0;
		पूर्ण

		tt_usecs[uframe] += usecs;

		carryover_tt_bandwidth(tt_usecs);

		/* fail अगर the carryover pushed bw past the last uframe's limit */
		अगर (max_tt_usecs[7] < tt_usecs[7])
			वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

#अन्यथा

/* वापस true अगरf the device's transaction translator is available
 * क्रम a periodic transfer starting at the specअगरied frame, using
 * all the uframes in the mask.
 */
अटल पूर्णांक tt_no_collision(
	काष्ठा ehci_hcd		*ehci,
	अचिन्हित		period,
	काष्ठा usb_device	*dev,
	अचिन्हित		frame,
	u32			uf_mask
)
अणु
	अगर (period == 0)	/* error */
		वापस 0;

	/* note bandwidth wastage:  split never follows csplit
	 * (dअगरferent dev or endpoपूर्णांक) until the next uframe.
	 * calling convention करोesn't make that distinction.
	 */
	क्रम (; frame < ehci->periodic_size; frame += period) अणु
		जोड़ ehci_shaकरोw	here;
		__hc32			type;
		काष्ठा ehci_qh_hw	*hw;

		here = ehci->pshaकरोw[frame];
		type = Q_NEXT_TYPE(ehci, ehci->periodic[frame]);
		जबतक (here.ptr) अणु
			चयन (hc32_to_cpu(ehci, type)) अणु
			हाल Q_TYPE_ITD:
				type = Q_NEXT_TYPE(ehci, here.itd->hw_next);
				here = here.itd->itd_next;
				जारी;
			हाल Q_TYPE_QH:
				hw = here.qh->hw;
				अगर (same_tt(dev, here.qh->ps.udev)) अणु
					u32		mask;

					mask = hc32_to_cpu(ehci,
							hw->hw_info2);
					/* "knows" no gap is needed */
					mask |= mask >> 8;
					अगर (mask & uf_mask)
						अवरोध;
				पूर्ण
				type = Q_NEXT_TYPE(ehci, hw->hw_next);
				here = here.qh->qh_next;
				जारी;
			हाल Q_TYPE_SITD:
				अगर (same_tt(dev, here.sitd->urb->dev)) अणु
					u16		mask;

					mask = hc32_to_cpu(ehci, here.sitd
								->hw_uframe);
					/* FIXME assumes no gap क्रम IN! */
					mask |= mask >> 8;
					अगर (mask & uf_mask)
						अवरोध;
				पूर्ण
				type = Q_NEXT_TYPE(ehci, here.sitd->hw_next);
				here = here.sitd->sitd_next;
				जारी;
			/* हाल Q_TYPE_FSTN: */
			शेष:
				ehci_dbg(ehci,
					"periodic frame %d bogus type %d\n",
					frame, type);
			पूर्ण

			/* collision or error */
			वापस 0;
		पूर्ण
	पूर्ण

	/* no collision */
	वापस 1;
पूर्ण

#पूर्ण_अगर /* CONFIG_USB_EHCI_TT_NEWSCHED */

/*-------------------------------------------------------------------------*/

अटल व्योम enable_periodic(काष्ठा ehci_hcd *ehci)
अणु
	अगर (ehci->periodic_count++)
		वापस;

	/* Stop रुकोing to turn off the periodic schedule */
	ehci->enabled_hrसमयr_events &= ~BIT(EHCI_HRTIMER_DISABLE_PERIODIC);

	/* Don't start the schedule until PSS is 0 */
	ehci_poll_PSS(ehci);
	turn_on_io_watchकरोg(ehci);
पूर्ण

अटल व्योम disable_periodic(काष्ठा ehci_hcd *ehci)
अणु
	अगर (--ehci->periodic_count)
		वापस;

	/* Don't turn off the schedule until PSS is 1 */
	ehci_poll_PSS(ehci);
पूर्ण

/*-------------------------------------------------------------------------*/

/* periodic schedule slots have iso tds (normal or split) first, then a
 * sparse tree क्रम active पूर्णांकerrupt transfers.
 *
 * this just links in a qh; caller guarantees uframe masks are set right.
 * no FSTN support (yet; ehci 0.96+)
 */
अटल व्योम qh_link_periodic(काष्ठा ehci_hcd *ehci, काष्ठा ehci_qh *qh)
अणु
	अचिन्हित	i;
	अचिन्हित	period = qh->ps.period;

	dev_dbg(&qh->ps.udev->dev,
		"link qh%d-%04x/%p start %d [%d/%d us]\n",
		period, hc32_to_cpup(ehci, &qh->hw->hw_info2)
			& (QH_CMASK | QH_SMASK),
		qh, qh->ps.phase, qh->ps.usecs, qh->ps.c_usecs);

	/* high bandwidth, or otherwise every microframe */
	अगर (period == 0)
		period = 1;

	क्रम (i = qh->ps.phase; i < ehci->periodic_size; i += period) अणु
		जोड़ ehci_shaकरोw	*prev = &ehci->pshaकरोw[i];
		__hc32			*hw_p = &ehci->periodic[i];
		जोड़ ehci_shaकरोw	here = *prev;
		__hc32			type = 0;

		/* skip the iso nodes at list head */
		जबतक (here.ptr) अणु
			type = Q_NEXT_TYPE(ehci, *hw_p);
			अगर (type == cpu_to_hc32(ehci, Q_TYPE_QH))
				अवरोध;
			prev = periodic_next_shaकरोw(ehci, prev, type);
			hw_p = shaकरोw_next_periodic(ehci, &here, type);
			here = *prev;
		पूर्ण

		/* sorting each branch by period (slow-->fast)
		 * enables sharing पूर्णांकerior tree nodes
		 */
		जबतक (here.ptr && qh != here.qh) अणु
			अगर (qh->ps.period > here.qh->ps.period)
				अवरोध;
			prev = &here.qh->qh_next;
			hw_p = &here.qh->hw->hw_next;
			here = *prev;
		पूर्ण
		/* link in this qh, unless some earlier pass did that */
		अगर (qh != here.qh) अणु
			qh->qh_next = here;
			अगर (here.qh)
				qh->hw->hw_next = *hw_p;
			wmb();
			prev->qh = qh;
			*hw_p = QH_NEXT(ehci, qh->qh_dma);
		पूर्ण
	पूर्ण
	qh->qh_state = QH_STATE_LINKED;
	qh->xacterrs = 0;
	qh->unlink_reason = 0;

	/* update per-qh bandwidth क्रम debugfs */
	ehci_to_hcd(ehci)->self.bandwidth_allocated += qh->ps.bw_period
		? ((qh->ps.usecs + qh->ps.c_usecs) / qh->ps.bw_period)
		: (qh->ps.usecs * 8);

	list_add(&qh->पूर्णांकr_node, &ehci->पूर्णांकr_qh_list);

	/* maybe enable periodic schedule processing */
	++ehci->पूर्णांकr_count;
	enable_periodic(ehci);
पूर्ण

अटल व्योम qh_unlink_periodic(काष्ठा ehci_hcd *ehci, काष्ठा ehci_qh *qh)
अणु
	अचिन्हित	i;
	अचिन्हित	period;

	/*
	 * If qh is क्रम a low/full-speed device, simply unlinking it
	 * could पूर्णांकerfere with an ongoing split transaction.  To unlink
	 * it safely would require setting the QH_INACTIVATE bit and
	 * रुकोing at least one frame, as described in EHCI 4.12.2.5.
	 *
	 * We won't bother with any of this.  Instead, we assume that the
	 * only reason क्रम unlinking an पूर्णांकerrupt QH जबतक the current URB
	 * is still active is to dequeue all the URBs (flush the whole
	 * endpoपूर्णांक queue).
	 *
	 * If rebalancing the periodic schedule is ever implemented, this
	 * approach will no दीर्घer be valid.
	 */

	/* high bandwidth, or otherwise part of every microframe */
	period = qh->ps.period ? : 1;

	क्रम (i = qh->ps.phase; i < ehci->periodic_size; i += period)
		periodic_unlink(ehci, i, qh);

	/* update per-qh bandwidth क्रम debugfs */
	ehci_to_hcd(ehci)->self.bandwidth_allocated -= qh->ps.bw_period
		? ((qh->ps.usecs + qh->ps.c_usecs) / qh->ps.bw_period)
		: (qh->ps.usecs * 8);

	dev_dbg(&qh->ps.udev->dev,
		"unlink qh%d-%04x/%p start %d [%d/%d us]\n",
		qh->ps.period,
		hc32_to_cpup(ehci, &qh->hw->hw_info2) & (QH_CMASK | QH_SMASK),
		qh, qh->ps.phase, qh->ps.usecs, qh->ps.c_usecs);

	/* qh->qh_next still "live" to HC */
	qh->qh_state = QH_STATE_UNLINK;
	qh->qh_next.ptr = शून्य;

	अगर (ehci->qh_scan_next == qh)
		ehci->qh_scan_next = list_entry(qh->पूर्णांकr_node.next,
				काष्ठा ehci_qh, पूर्णांकr_node);
	list_del(&qh->पूर्णांकr_node);
पूर्ण

अटल व्योम cancel_unlink_रुको_पूर्णांकr(काष्ठा ehci_hcd *ehci, काष्ठा ehci_qh *qh)
अणु
	अगर (qh->qh_state != QH_STATE_LINKED ||
			list_empty(&qh->unlink_node))
		वापस;

	list_del_init(&qh->unlink_node);

	/*
	 * TODO: disable the event of EHCI_HRTIMER_START_UNLINK_INTR क्रम
	 * aव्योमing unnecessary CPU wakeup
	 */
पूर्ण

अटल व्योम start_unlink_पूर्णांकr(काष्ठा ehci_hcd *ehci, काष्ठा ehci_qh *qh)
अणु
	/* If the QH isn't linked then there's nothing we can करो. */
	अगर (qh->qh_state != QH_STATE_LINKED)
		वापस;

	/* अगर the qh is रुकोing क्रम unlink, cancel it now */
	cancel_unlink_रुको_पूर्णांकr(ehci, qh);

	qh_unlink_periodic(ehci, qh);

	/* Make sure the unlinks are visible beक्रमe starting the समयr */
	wmb();

	/*
	 * The EHCI spec करोesn't say how दीर्घ it takes the controller to
	 * stop accessing an unlinked पूर्णांकerrupt QH.  The समयr delay is
	 * 9 uframes; presumably that will be दीर्घ enough.
	 */
	qh->unlink_cycle = ehci->पूर्णांकr_unlink_cycle;

	/* New entries go at the end of the पूर्णांकr_unlink list */
	list_add_tail(&qh->unlink_node, &ehci->पूर्णांकr_unlink);

	अगर (ehci->पूर्णांकr_unlinking)
		;	/* Aव्योम recursive calls */
	अन्यथा अगर (ehci->rh_state < EHCI_RH_RUNNING)
		ehci_handle_पूर्णांकr_unlinks(ehci);
	अन्यथा अगर (ehci->पूर्णांकr_unlink.next == &qh->unlink_node) अणु
		ehci_enable_event(ehci, EHCI_HRTIMER_UNLINK_INTR, true);
		++ehci->पूर्णांकr_unlink_cycle;
	पूर्ण
पूर्ण

/*
 * It is common only one पूर्णांकr URB is scheduled on one qh, and
 * given complete() is run in tasklet context, पूर्णांकroduce a bit
 * delay to aव्योम unlink qh too early.
 */
अटल व्योम start_unlink_पूर्णांकr_रुको(काष्ठा ehci_hcd *ehci,
				   काष्ठा ehci_qh *qh)
अणु
	qh->unlink_cycle = ehci->पूर्णांकr_unlink_रुको_cycle;

	/* New entries go at the end of the पूर्णांकr_unlink_रुको list */
	list_add_tail(&qh->unlink_node, &ehci->पूर्णांकr_unlink_रुको);

	अगर (ehci->rh_state < EHCI_RH_RUNNING)
		ehci_handle_start_पूर्णांकr_unlinks(ehci);
	अन्यथा अगर (ehci->पूर्णांकr_unlink_रुको.next == &qh->unlink_node) अणु
		ehci_enable_event(ehci, EHCI_HRTIMER_START_UNLINK_INTR, true);
		++ehci->पूर्णांकr_unlink_रुको_cycle;
	पूर्ण
पूर्ण

अटल व्योम end_unlink_पूर्णांकr(काष्ठा ehci_hcd *ehci, काष्ठा ehci_qh *qh)
अणु
	काष्ठा ehci_qh_hw	*hw = qh->hw;
	पूर्णांक			rc;

	qh->qh_state = QH_STATE_IDLE;
	hw->hw_next = EHCI_LIST_END(ehci);

	अगर (!list_empty(&qh->qtd_list))
		qh_completions(ehci, qh);

	/* reschedule QH अगरf another request is queued */
	अगर (!list_empty(&qh->qtd_list) && ehci->rh_state == EHCI_RH_RUNNING) अणु
		rc = qh_schedule(ehci, qh);
		अगर (rc == 0) अणु
			qh_refresh(ehci, qh);
			qh_link_periodic(ehci, qh);
		पूर्ण

		/* An error here likely indicates handshake failure
		 * or no space left in the schedule.  Neither fault
		 * should happen often ...
		 *
		 * FIXME समाप्त the now-dysfunctional queued urbs
		 */
		अन्यथा अणु
			ehci_err(ehci, "can't reschedule qh %p, err %d\n",
					qh, rc);
		पूर्ण
	पूर्ण

	/* maybe turn off periodic schedule */
	--ehci->पूर्णांकr_count;
	disable_periodic(ehci);
पूर्ण

/*-------------------------------------------------------------------------*/

अटल पूर्णांक check_period(
	काष्ठा ehci_hcd *ehci,
	अचिन्हित	frame,
	अचिन्हित	uframe,
	अचिन्हित	uperiod,
	अचिन्हित	usecs
) अणु
	/* complete split running पूर्णांकo next frame?
	 * given FSTN support, we could someबार check...
	 */
	अगर (uframe >= 8)
		वापस 0;

	/* convert "usecs we need" to "max already claimed" */
	usecs = ehci->uframe_periodic_max - usecs;

	क्रम (uframe += frame << 3; uframe < EHCI_BANDWIDTH_SIZE;
			uframe += uperiod) अणु
		अगर (ehci->bandwidth[uframe] > usecs)
			वापस 0;
	पूर्ण

	/* success! */
	वापस 1;
पूर्ण

अटल पूर्णांक check_पूर्णांकr_schedule(
	काष्ठा ehci_hcd		*ehci,
	अचिन्हित		frame,
	अचिन्हित		uframe,
	काष्ठा ehci_qh		*qh,
	अचिन्हित		*c_maskp,
	काष्ठा ehci_tt		*tt
)
अणु
	पूर्णांक		retval = -ENOSPC;
	u8		mask = 0;

	अगर (qh->ps.c_usecs && uframe >= 6)	/* FSTN territory? */
		जाओ करोne;

	अगर (!check_period(ehci, frame, uframe, qh->ps.bw_uperiod, qh->ps.usecs))
		जाओ करोne;
	अगर (!qh->ps.c_usecs) अणु
		retval = 0;
		*c_maskp = 0;
		जाओ करोne;
	पूर्ण

#अगर_घोषित CONFIG_USB_EHCI_TT_NEWSCHED
	अगर (tt_available(ehci, &qh->ps, tt, frame, uframe)) अणु
		अचिन्हित i;

		/* TODO : this may need FSTN क्रम SSPLIT in uframe 5. */
		क्रम (i = uframe+2; i < 8 && i <= uframe+4; i++)
			अगर (!check_period(ehci, frame, i,
					qh->ps.bw_uperiod, qh->ps.c_usecs))
				जाओ करोne;
			अन्यथा
				mask |= 1 << i;

		retval = 0;

		*c_maskp = mask;
	पूर्ण
#अन्यथा
	/* Make sure this tt's buffer is also available क्रम CSPLITs.
	 * We pessimize a bit; probably the typical full speed हाल
	 * करोesn't need the second CSPLIT.
	 *
	 * NOTE:  both SPLIT and CSPLIT could be checked in just
	 * one smart pass...
	 */
	mask = 0x03 << (uframe + qh->gap_uf);
	*c_maskp = mask;

	mask |= 1 << uframe;
	अगर (tt_no_collision(ehci, qh->ps.bw_period, qh->ps.udev, frame, mask)) अणु
		अगर (!check_period(ehci, frame, uframe + qh->gap_uf + 1,
				qh->ps.bw_uperiod, qh->ps.c_usecs))
			जाओ करोne;
		अगर (!check_period(ehci, frame, uframe + qh->gap_uf,
				qh->ps.bw_uperiod, qh->ps.c_usecs))
			जाओ करोne;
		retval = 0;
	पूर्ण
#पूर्ण_अगर
करोne:
	वापस retval;
पूर्ण

/* "first fit" scheduling policy used the first समय through,
 * or when the previous schedule slot can't be re-used.
 */
अटल पूर्णांक qh_schedule(काष्ठा ehci_hcd *ehci, काष्ठा ehci_qh *qh)
अणु
	पूर्णांक		status = 0;
	अचिन्हित	uframe;
	अचिन्हित	c_mask;
	काष्ठा ehci_qh_hw	*hw = qh->hw;
	काष्ठा ehci_tt		*tt;

	hw->hw_next = EHCI_LIST_END(ehci);

	/* reuse the previous schedule slots, अगर we can */
	अगर (qh->ps.phase != NO_FRAME) अणु
		ehci_dbg(ehci, "reused qh %p schedule\n", qh);
		वापस 0;
	पूर्ण

	uframe = 0;
	c_mask = 0;
	tt = find_tt(qh->ps.udev);
	अगर (IS_ERR(tt)) अणु
		status = PTR_ERR(tt);
		जाओ करोne;
	पूर्ण
	compute_tt_budget(ehci->tt_budget, tt);

	/* अन्यथा scan the schedule to find a group of slots such that all
	 * uframes have enough periodic bandwidth available.
	 */
	/* "normal" हाल, uframing flexible except with splits */
	अगर (qh->ps.bw_period) अणु
		पूर्णांक		i;
		अचिन्हित	frame;

		क्रम (i = qh->ps.bw_period; i > 0; --i) अणु
			frame = ++ehci->अक्रमom_frame & (qh->ps.bw_period - 1);
			क्रम (uframe = 0; uframe < 8; uframe++) अणु
				status = check_पूर्णांकr_schedule(ehci,
						frame, uframe, qh, &c_mask, tt);
				अगर (status == 0)
					जाओ got_it;
			पूर्ण
		पूर्ण

	/* qh->ps.bw_period == 0 means every uframe */
	पूर्ण अन्यथा अणु
		status = check_पूर्णांकr_schedule(ehci, 0, 0, qh, &c_mask, tt);
	पूर्ण
	अगर (status)
		जाओ करोne;

 got_it:
	qh->ps.phase = (qh->ps.period ? ehci->अक्रमom_frame &
			(qh->ps.period - 1) : 0);
	qh->ps.bw_phase = qh->ps.phase & (qh->ps.bw_period - 1);
	qh->ps.phase_uf = uframe;
	qh->ps.cs_mask = qh->ps.period ?
			(c_mask << 8) | (1 << uframe) :
			QH_SMASK;

	/* reset S-frame and (maybe) C-frame masks */
	hw->hw_info2 &= cpu_to_hc32(ehci, ~(QH_CMASK | QH_SMASK));
	hw->hw_info2 |= cpu_to_hc32(ehci, qh->ps.cs_mask);
	reserve_release_पूर्णांकr_bandwidth(ehci, qh, 1);

करोne:
	वापस status;
पूर्ण

अटल पूर्णांक पूर्णांकr_submit(
	काष्ठा ehci_hcd		*ehci,
	काष्ठा urb		*urb,
	काष्ठा list_head	*qtd_list,
	gfp_t			mem_flags
) अणु
	अचिन्हित		epnum;
	अचिन्हित दीर्घ		flags;
	काष्ठा ehci_qh		*qh;
	पूर्णांक			status;
	काष्ठा list_head	empty;

	/* get endpoपूर्णांक and transfer/schedule data */
	epnum = urb->ep->desc.bEndpoपूर्णांकAddress;

	spin_lock_irqsave(&ehci->lock, flags);

	अगर (unlikely(!HCD_HW_ACCESSIBLE(ehci_to_hcd(ehci)))) अणु
		status = -ESHUTDOWN;
		जाओ करोne_not_linked;
	पूर्ण
	status = usb_hcd_link_urb_to_ep(ehci_to_hcd(ehci), urb);
	अगर (unlikely(status))
		जाओ करोne_not_linked;

	/* get qh and क्रमce any scheduling errors */
	INIT_LIST_HEAD(&empty);
	qh = qh_append_tds(ehci, urb, &empty, epnum, &urb->ep->hcpriv);
	अगर (qh == शून्य) अणु
		status = -ENOMEM;
		जाओ करोne;
	पूर्ण
	अगर (qh->qh_state == QH_STATE_IDLE) अणु
		status = qh_schedule(ehci, qh);
		अगर (status)
			जाओ करोne;
	पूर्ण

	/* then queue the urb's tds to the qh */
	qh = qh_append_tds(ehci, urb, qtd_list, epnum, &urb->ep->hcpriv);
	BUG_ON(qh == शून्य);

	/* stuff पूर्णांकo the periodic schedule */
	अगर (qh->qh_state == QH_STATE_IDLE) अणु
		qh_refresh(ehci, qh);
		qh_link_periodic(ehci, qh);
	पूर्ण अन्यथा अणु
		/* cancel unlink रुको क्रम the qh */
		cancel_unlink_रुको_पूर्णांकr(ehci, qh);
	पूर्ण

	/* ... update usbfs periodic stats */
	ehci_to_hcd(ehci)->self.bandwidth_पूर्णांक_reqs++;

करोne:
	अगर (unlikely(status))
		usb_hcd_unlink_urb_from_ep(ehci_to_hcd(ehci), urb);
करोne_not_linked:
	spin_unlock_irqrestore(&ehci->lock, flags);
	अगर (status)
		qtd_list_मुक्त(ehci, urb, qtd_list);

	वापस status;
पूर्ण

अटल व्योम scan_पूर्णांकr(काष्ठा ehci_hcd *ehci)
अणु
	काष्ठा ehci_qh		*qh;

	list_क्रम_each_entry_safe(qh, ehci->qh_scan_next, &ehci->पूर्णांकr_qh_list,
			पूर्णांकr_node) अणु

		/* clean any finished work क्रम this qh */
		अगर (!list_empty(&qh->qtd_list)) अणु
			पूर्णांक temp;

			/*
			 * Unlinks could happen here; completion reporting
			 * drops the lock.  That's why ehci->qh_scan_next
			 * always holds the next qh to scan; अगर the next qh
			 * माला_लो unlinked then ehci->qh_scan_next is adjusted
			 * in qh_unlink_periodic().
			 */
			temp = qh_completions(ehci, qh);
			अगर (unlikely(temp))
				start_unlink_पूर्णांकr(ehci, qh);
			अन्यथा अगर (unlikely(list_empty(&qh->qtd_list) &&
					qh->qh_state == QH_STATE_LINKED))
				start_unlink_पूर्णांकr_रुको(ehci, qh);
		पूर्ण
	पूर्ण
पूर्ण

/*-------------------------------------------------------------------------*/

/* ehci_iso_stream ops work with both ITD and SITD */

अटल काष्ठा ehci_iso_stream *
iso_stream_alloc(gfp_t mem_flags)
अणु
	काष्ठा ehci_iso_stream *stream;

	stream = kzalloc(माप(*stream), mem_flags);
	अगर (likely(stream != शून्य)) अणु
		INIT_LIST_HEAD(&stream->td_list);
		INIT_LIST_HEAD(&stream->मुक्त_list);
		stream->next_uframe = NO_FRAME;
		stream->ps.phase = NO_FRAME;
	पूर्ण
	वापस stream;
पूर्ण

अटल व्योम
iso_stream_init(
	काष्ठा ehci_hcd		*ehci,
	काष्ठा ehci_iso_stream	*stream,
	काष्ठा urb		*urb
)
अणु
	अटल स्थिर u8 smask_out[] = अणु 0x01, 0x03, 0x07, 0x0f, 0x1f, 0x3f पूर्ण;

	काष्ठा usb_device	*dev = urb->dev;
	u32			buf1;
	अचिन्हित		epnum, maxp;
	पूर्णांक			is_input;
	अचिन्हित		पंचांगp;

	/*
	 * this might be a "high bandwidth" highspeed endpoपूर्णांक,
	 * as encoded in the ep descriptor's wMaxPacket field
	 */
	epnum = usb_pipeendpoपूर्णांक(urb->pipe);
	is_input = usb_pipein(urb->pipe) ? USB_सूची_IN : 0;
	maxp = usb_endpoपूर्णांक_maxp(&urb->ep->desc);
	buf1 = is_input ? 1 << 11 : 0;

	/* knows about ITD vs SITD */
	अगर (dev->speed == USB_SPEED_HIGH) अणु
		अचिन्हित multi = usb_endpoपूर्णांक_maxp_mult(&urb->ep->desc);

		stream->highspeed = 1;

		buf1 |= maxp;
		maxp *= multi;

		stream->buf0 = cpu_to_hc32(ehci, (epnum << 8) | dev->devnum);
		stream->buf1 = cpu_to_hc32(ehci, buf1);
		stream->buf2 = cpu_to_hc32(ehci, multi);

		/* usbfs wants to report the average usecs per frame tied up
		 * when transfers on this endpoपूर्णांक are scheduled ...
		 */
		stream->ps.usecs = HS_USECS_ISO(maxp);

		/* period क्रम bandwidth allocation */
		पंचांगp = min_t(अचिन्हित, EHCI_BANDWIDTH_SIZE,
				1 << (urb->ep->desc.bInterval - 1));

		/* Allow urb->पूर्णांकerval to override */
		stream->ps.bw_uperiod = min_t(अचिन्हित, पंचांगp, urb->पूर्णांकerval);

		stream->uperiod = urb->पूर्णांकerval;
		stream->ps.period = urb->पूर्णांकerval >> 3;
		stream->bandwidth = stream->ps.usecs * 8 /
				stream->ps.bw_uperiod;

	पूर्ण अन्यथा अणु
		u32		addr;
		पूर्णांक		think_समय;
		पूर्णांक		hs_transfers;

		addr = dev->ttport << 24;
		अगर (!ehci_is_TDI(ehci)
				|| (dev->tt->hub !=
					ehci_to_hcd(ehci)->self.root_hub))
			addr |= dev->tt->hub->devnum << 16;
		addr |= epnum << 8;
		addr |= dev->devnum;
		stream->ps.usecs = HS_USECS_ISO(maxp);
		think_समय = dev->tt->think_समय;
		stream->ps.tt_usecs = NS_TO_US(think_समय + usb_calc_bus_समय(
				dev->speed, is_input, 1, maxp));
		hs_transfers = max(1u, (maxp + 187) / 188);
		अगर (is_input) अणु
			u32	पंचांगp;

			addr |= 1 << 31;
			stream->ps.c_usecs = stream->ps.usecs;
			stream->ps.usecs = HS_USECS_ISO(1);
			stream->ps.cs_mask = 1;

			/* c-mask as specअगरied in USB 2.0 11.18.4 3.c */
			पंचांगp = (1 << (hs_transfers + 2)) - 1;
			stream->ps.cs_mask |= पंचांगp << (8 + 2);
		पूर्ण अन्यथा
			stream->ps.cs_mask = smask_out[hs_transfers - 1];

		/* period क्रम bandwidth allocation */
		पंचांगp = min_t(अचिन्हित, EHCI_BANDWIDTH_FRAMES,
				1 << (urb->ep->desc.bInterval - 1));

		/* Allow urb->पूर्णांकerval to override */
		stream->ps.bw_period = min_t(अचिन्हित, पंचांगp, urb->पूर्णांकerval);
		stream->ps.bw_uperiod = stream->ps.bw_period << 3;

		stream->ps.period = urb->पूर्णांकerval;
		stream->uperiod = urb->पूर्णांकerval << 3;
		stream->bandwidth = (stream->ps.usecs + stream->ps.c_usecs) /
				stream->ps.bw_period;

		/* stream->splits माला_लो created from cs_mask later */
		stream->address = cpu_to_hc32(ehci, addr);
	पूर्ण

	stream->ps.udev = dev;
	stream->ps.ep = urb->ep;

	stream->bEndpoपूर्णांकAddress = is_input | epnum;
	stream->maxp = maxp;
पूर्ण

अटल काष्ठा ehci_iso_stream *
iso_stream_find(काष्ठा ehci_hcd *ehci, काष्ठा urb *urb)
अणु
	अचिन्हित		epnum;
	काष्ठा ehci_iso_stream	*stream;
	काष्ठा usb_host_endpoपूर्णांक *ep;
	अचिन्हित दीर्घ		flags;

	epnum = usb_pipeendpoपूर्णांक (urb->pipe);
	अगर (usb_pipein(urb->pipe))
		ep = urb->dev->ep_in[epnum];
	अन्यथा
		ep = urb->dev->ep_out[epnum];

	spin_lock_irqsave(&ehci->lock, flags);
	stream = ep->hcpriv;

	अगर (unlikely(stream == शून्य)) अणु
		stream = iso_stream_alloc(GFP_ATOMIC);
		अगर (likely(stream != शून्य)) अणु
			ep->hcpriv = stream;
			iso_stream_init(ehci, stream, urb);
		पूर्ण

	/* अगर dev->ep [epnum] is a QH, hw is set */
	पूर्ण अन्यथा अगर (unlikely(stream->hw != शून्य)) अणु
		ehci_dbg(ehci, "dev %s ep%d%s, not iso??\n",
			urb->dev->devpath, epnum,
			usb_pipein(urb->pipe) ? "in" : "out");
		stream = शून्य;
	पूर्ण

	spin_unlock_irqrestore(&ehci->lock, flags);
	वापस stream;
पूर्ण

/*-------------------------------------------------------------------------*/

/* ehci_iso_sched ops can be ITD-only or SITD-only */

अटल काष्ठा ehci_iso_sched *
iso_sched_alloc(अचिन्हित packets, gfp_t mem_flags)
अणु
	काष्ठा ehci_iso_sched	*iso_sched;
	पूर्णांक			size = माप(*iso_sched);

	size += packets * माप(काष्ठा ehci_iso_packet);
	iso_sched = kzalloc(size, mem_flags);
	अगर (likely(iso_sched != शून्य))
		INIT_LIST_HEAD(&iso_sched->td_list);

	वापस iso_sched;
पूर्ण

अटल अंतरभूत व्योम
itd_sched_init(
	काष्ठा ehci_hcd		*ehci,
	काष्ठा ehci_iso_sched	*iso_sched,
	काष्ठा ehci_iso_stream	*stream,
	काष्ठा urb		*urb
)
अणु
	अचिन्हित	i;
	dma_addr_t	dma = urb->transfer_dma;

	/* how many uframes are needed क्रम these transfers */
	iso_sched->span = urb->number_of_packets * stream->uperiod;

	/* figure out per-uframe itd fields that we'll need later
	 * when we fit new itds पूर्णांकo the schedule.
	 */
	क्रम (i = 0; i < urb->number_of_packets; i++) अणु
		काष्ठा ehci_iso_packet	*uframe = &iso_sched->packet[i];
		अचिन्हित		length;
		dma_addr_t		buf;
		u32			trans;

		length = urb->iso_frame_desc[i].length;
		buf = dma + urb->iso_frame_desc[i].offset;

		trans = EHCI_ISOC_ACTIVE;
		trans |= buf & 0x0fff;
		अगर (unlikely(((i + 1) == urb->number_of_packets))
				&& !(urb->transfer_flags & URB_NO_INTERRUPT))
			trans |= EHCI_ITD_IOC;
		trans |= length << 16;
		uframe->transaction = cpu_to_hc32(ehci, trans);

		/* might need to cross a buffer page within a uframe */
		uframe->bufp = (buf & ~(u64)0x0fff);
		buf += length;
		अगर (unlikely((uframe->bufp != (buf & ~(u64)0x0fff))))
			uframe->cross = 1;
	पूर्ण
पूर्ण

अटल व्योम
iso_sched_मुक्त(
	काष्ठा ehci_iso_stream	*stream,
	काष्ठा ehci_iso_sched	*iso_sched
)
अणु
	अगर (!iso_sched)
		वापस;
	/* caller must hold ehci->lock! */
	list_splice(&iso_sched->td_list, &stream->मुक्त_list);
	kमुक्त(iso_sched);
पूर्ण

अटल पूर्णांक
itd_urb_transaction(
	काष्ठा ehci_iso_stream	*stream,
	काष्ठा ehci_hcd		*ehci,
	काष्ठा urb		*urb,
	gfp_t			mem_flags
)
अणु
	काष्ठा ehci_itd		*itd;
	dma_addr_t		itd_dma;
	पूर्णांक			i;
	अचिन्हित		num_itds;
	काष्ठा ehci_iso_sched	*sched;
	अचिन्हित दीर्घ		flags;

	sched = iso_sched_alloc(urb->number_of_packets, mem_flags);
	अगर (unlikely(sched == शून्य))
		वापस -ENOMEM;

	itd_sched_init(ehci, sched, stream, urb);

	अगर (urb->पूर्णांकerval < 8)
		num_itds = 1 + (sched->span + 7) / 8;
	अन्यथा
		num_itds = urb->number_of_packets;

	/* allocate/init ITDs */
	spin_lock_irqsave(&ehci->lock, flags);
	क्रम (i = 0; i < num_itds; i++) अणु

		/*
		 * Use iTDs from the मुक्त list, but not iTDs that may
		 * still be in use by the hardware.
		 */
		अगर (likely(!list_empty(&stream->मुक्त_list))) अणु
			itd = list_first_entry(&stream->मुक्त_list,
					काष्ठा ehci_itd, itd_list);
			अगर (itd->frame == ehci->now_frame)
				जाओ alloc_itd;
			list_del(&itd->itd_list);
			itd_dma = itd->itd_dma;
		पूर्ण अन्यथा अणु
 alloc_itd:
			spin_unlock_irqrestore(&ehci->lock, flags);
			itd = dma_pool_alloc(ehci->itd_pool, mem_flags,
					&itd_dma);
			spin_lock_irqsave(&ehci->lock, flags);
			अगर (!itd) अणु
				iso_sched_मुक्त(stream, sched);
				spin_unlock_irqrestore(&ehci->lock, flags);
				वापस -ENOMEM;
			पूर्ण
		पूर्ण

		स_रखो(itd, 0, माप(*itd));
		itd->itd_dma = itd_dma;
		itd->frame = NO_FRAME;
		list_add(&itd->itd_list, &sched->td_list);
	पूर्ण
	spin_unlock_irqrestore(&ehci->lock, flags);

	/* temporarily store schedule info in hcpriv */
	urb->hcpriv = sched;
	urb->error_count = 0;
	वापस 0;
पूर्ण

/*-------------------------------------------------------------------------*/

अटल व्योम reserve_release_iso_bandwidth(काष्ठा ehci_hcd *ehci,
		काष्ठा ehci_iso_stream *stream, पूर्णांक sign)
अणु
	अचिन्हित		uframe;
	अचिन्हित		i, j;
	अचिन्हित		s_mask, c_mask, m;
	पूर्णांक			usecs = stream->ps.usecs;
	पूर्णांक			c_usecs = stream->ps.c_usecs;
	पूर्णांक			tt_usecs = stream->ps.tt_usecs;
	काष्ठा ehci_tt		*tt;

	अगर (stream->ps.phase == NO_FRAME)	/* Bandwidth wasn't reserved */
		वापस;
	uframe = stream->ps.bw_phase << 3;

	bandwidth_dbg(ehci, sign, "iso", &stream->ps);

	अगर (sign < 0) अणु		/* Release bandwidth */
		usecs = -usecs;
		c_usecs = -c_usecs;
		tt_usecs = -tt_usecs;
	पूर्ण

	अगर (!stream->splits) अणु		/* High speed */
		क्रम (i = uframe + stream->ps.phase_uf; i < EHCI_BANDWIDTH_SIZE;
				i += stream->ps.bw_uperiod)
			ehci->bandwidth[i] += usecs;

	पूर्ण अन्यथा अणु			/* Full speed */
		s_mask = stream->ps.cs_mask;
		c_mask = s_mask >> 8;

		/* NOTE: adjusपंचांगent needed क्रम frame overflow */
		क्रम (i = uframe; i < EHCI_BANDWIDTH_SIZE;
				i += stream->ps.bw_uperiod) अणु
			क्रम ((j = stream->ps.phase_uf, m = 1 << j); j < 8;
					(++j, m <<= 1)) अणु
				अगर (s_mask & m)
					ehci->bandwidth[i+j] += usecs;
				अन्यथा अगर (c_mask & m)
					ehci->bandwidth[i+j] += c_usecs;
			पूर्ण
		पूर्ण

		/*
		 * find_tt() will not वापस any error here as we have
		 * alपढ़ोy called find_tt() beक्रमe calling this function
		 * and checked क्रम any error वापस. The previous call
		 * would have created the data काष्ठाure.
		 */
		tt = find_tt(stream->ps.udev);
		अगर (sign > 0)
			list_add_tail(&stream->ps.ps_list, &tt->ps_list);
		अन्यथा
			list_del(&stream->ps.ps_list);

		क्रम (i = uframe >> 3; i < EHCI_BANDWIDTH_FRAMES;
				i += stream->ps.bw_period)
			tt->bandwidth[i] += tt_usecs;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक
itd_slot_ok(
	काष्ठा ehci_hcd		*ehci,
	काष्ठा ehci_iso_stream	*stream,
	अचिन्हित		uframe
)
अणु
	अचिन्हित		usecs;

	/* convert "usecs we need" to "max already claimed" */
	usecs = ehci->uframe_periodic_max - stream->ps.usecs;

	क्रम (uframe &= stream->ps.bw_uperiod - 1; uframe < EHCI_BANDWIDTH_SIZE;
			uframe += stream->ps.bw_uperiod) अणु
		अगर (ehci->bandwidth[uframe] > usecs)
			वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

अटल अंतरभूत पूर्णांक
sitd_slot_ok(
	काष्ठा ehci_hcd		*ehci,
	काष्ठा ehci_iso_stream	*stream,
	अचिन्हित		uframe,
	काष्ठा ehci_iso_sched	*sched,
	काष्ठा ehci_tt		*tt
)
अणु
	अचिन्हित		mask, पंचांगp;
	अचिन्हित		frame, uf;

	mask = stream->ps.cs_mask << (uframe & 7);

	/* क्रम OUT, करोn't wrap SSPLIT पूर्णांकo H-microframe 7 */
	अगर (((stream->ps.cs_mask & 0xff) << (uframe & 7)) >= (1 << 7))
		वापस 0;

	/* क्रम IN, करोn't wrap CSPLIT पूर्णांकo the next frame */
	अगर (mask & ~0xffff)
		वापस 0;

	/* check bandwidth */
	uframe &= stream->ps.bw_uperiod - 1;
	frame = uframe >> 3;

#अगर_घोषित CONFIG_USB_EHCI_TT_NEWSCHED
	/* The tt's fullspeed bus bandwidth must be available.
	 * tt_available scheduling guarantees 10+% क्रम control/bulk.
	 */
	uf = uframe & 7;
	अगर (!tt_available(ehci, &stream->ps, tt, frame, uf))
		वापस 0;
#अन्यथा
	/* tt must be idle क्रम start(s), any gap, and csplit.
	 * assume scheduling slop leaves 10+% क्रम control/bulk.
	 */
	अगर (!tt_no_collision(ehci, stream->ps.bw_period,
			stream->ps.udev, frame, mask))
		वापस 0;
#पूर्ण_अगर

	करो अणु
		अचिन्हित	max_used;
		अचिन्हित	i;

		/* check starts (OUT uses more than one) */
		uf = uframe;
		max_used = ehci->uframe_periodic_max - stream->ps.usecs;
		क्रम (पंचांगp = stream->ps.cs_mask & 0xff; पंचांगp; पंचांगp >>= 1, uf++) अणु
			अगर (ehci->bandwidth[uf] > max_used)
				वापस 0;
		पूर्ण

		/* क्रम IN, check CSPLIT */
		अगर (stream->ps.c_usecs) अणु
			max_used = ehci->uframe_periodic_max -
					stream->ps.c_usecs;
			uf = uframe & ~7;
			पंचांगp = 1 << (2+8);
			क्रम (i = (uframe & 7) + 2; i < 8; (++i, पंचांगp <<= 1)) अणु
				अगर ((stream->ps.cs_mask & पंचांगp) == 0)
					जारी;
				अगर (ehci->bandwidth[uf+i] > max_used)
					वापस 0;
			पूर्ण
		पूर्ण

		uframe += stream->ps.bw_uperiod;
	पूर्ण जबतक (uframe < EHCI_BANDWIDTH_SIZE);

	stream->ps.cs_mask <<= uframe & 7;
	stream->splits = cpu_to_hc32(ehci, stream->ps.cs_mask);
	वापस 1;
पूर्ण

/*
 * This scheduler plans almost as far पूर्णांकo the future as it has actual
 * periodic schedule slots.  (Affected by TUNE_FLS, which शेषs to
 * "as small as possible" to be cache-मित्रlier.)  That limits the size
 * transfers you can stream reliably; aव्योम more than 64 msec per urb.
 * Also aव्योम queue depths of less than ehci's worst irq latency (affected
 * by the per-urb URB_NO_INTERRUPT hपूर्णांक, the log2_irq_thresh module parameter,
 * and other factors); or more than about 230 msec total (क्रम portability,
 * given EHCI_TUNE_FLS and the slop).  Or, ग_लिखो a smarter scheduler!
 */

अटल पूर्णांक
iso_stream_schedule(
	काष्ठा ehci_hcd		*ehci,
	काष्ठा urb		*urb,
	काष्ठा ehci_iso_stream	*stream
)
अणु
	u32			now, base, next, start, period, span, now2;
	u32			wrap = 0, skip = 0;
	पूर्णांक			status = 0;
	अचिन्हित		mod = ehci->periodic_size << 3;
	काष्ठा ehci_iso_sched	*sched = urb->hcpriv;
	bool			empty = list_empty(&stream->td_list);
	bool			new_stream = false;

	period = stream->uperiod;
	span = sched->span;
	अगर (!stream->highspeed)
		span <<= 3;

	/* Start a new isochronous stream? */
	अगर (unlikely(empty && !hcd_periodic_completion_in_progress(
			ehci_to_hcd(ehci), urb->ep))) अणु

		/* Schedule the endpoपूर्णांक */
		अगर (stream->ps.phase == NO_FRAME) अणु
			पूर्णांक		करोne = 0;
			काष्ठा ehci_tt	*tt = find_tt(stream->ps.udev);

			अगर (IS_ERR(tt)) अणु
				status = PTR_ERR(tt);
				जाओ fail;
			पूर्ण
			compute_tt_budget(ehci->tt_budget, tt);

			start = ((-(++ehci->अक्रमom_frame)) << 3) & (period - 1);

			/* find a uframe slot with enough bandwidth.
			 * Early uframes are more precious because full-speed
			 * iso IN transfers can't use late uframes,
			 * and thereक्रमe they should be allocated last.
			 */
			next = start;
			start += period;
			करो अणु
				start--;
				/* check schedule: enough space? */
				अगर (stream->highspeed) अणु
					अगर (itd_slot_ok(ehci, stream, start))
						करोne = 1;
				पूर्ण अन्यथा अणु
					अगर ((start % 8) >= 6)
						जारी;
					अगर (sitd_slot_ok(ehci, stream, start,
							sched, tt))
						करोne = 1;
				पूर्ण
			पूर्ण जबतक (start > next && !करोne);

			/* no room in the schedule */
			अगर (!करोne) अणु
				ehci_dbg(ehci, "iso sched full %p", urb);
				status = -ENOSPC;
				जाओ fail;
			पूर्ण
			stream->ps.phase = (start >> 3) &
					(stream->ps.period - 1);
			stream->ps.bw_phase = stream->ps.phase &
					(stream->ps.bw_period - 1);
			stream->ps.phase_uf = start & 7;
			reserve_release_iso_bandwidth(ehci, stream, 1);
		पूर्ण

		/* New stream is alपढ़ोy scheduled; use the upcoming slot */
		अन्यथा अणु
			start = (stream->ps.phase << 3) + stream->ps.phase_uf;
		पूर्ण

		stream->next_uframe = start;
		new_stream = true;
	पूर्ण

	now = ehci_पढ़ो_frame_index(ehci) & (mod - 1);

	/* Take the isochronous scheduling threshold पूर्णांकo account */
	अगर (ehci->i_thresh)
		next = now + ehci->i_thresh;	/* uframe cache */
	अन्यथा
		next = (now + 2 + 7) & ~0x07;	/* full frame cache */

	/* If needed, initialize last_iso_frame so that this URB will be seen */
	अगर (ehci->isoc_count == 0)
		ehci->last_iso_frame = now >> 3;

	/*
	 * Use ehci->last_iso_frame as the base.  There can't be any
	 * TDs scheduled क्रम earlier than that.
	 */
	base = ehci->last_iso_frame << 3;
	next = (next - base) & (mod - 1);
	start = (stream->next_uframe - base) & (mod - 1);

	अगर (unlikely(new_stream))
		जाओ करो_ASAP;

	/*
	 * Typical हाल: reuse current schedule, stream may still be active.
	 * Hopefully there are no gaps from the host falling behind
	 * (irq delays etc).  If there are, the behavior depends on
	 * whether URB_ISO_ASAP is set.
	 */
	now2 = (now - base) & (mod - 1);

	/* Is the schedule about to wrap around? */
	अगर (unlikely(!empty && start < period)) अणु
		ehci_dbg(ehci, "request %p would overflow (%u-%u < %u mod %u)\n",
				urb, stream->next_uframe, base, period, mod);
		status = -EFBIG;
		जाओ fail;
	पूर्ण

	/* Is the next packet scheduled after the base समय? */
	अगर (likely(!empty || start <= now2 + period)) अणु

		/* URB_ISO_ASAP: make sure that start >= next */
		अगर (unlikely(start < next &&
				(urb->transfer_flags & URB_ISO_ASAP)))
			जाओ करो_ASAP;

		/* Otherwise use start, अगर it's not in the past */
		अगर (likely(start >= now2))
			जाओ use_start;

	/* Otherwise we got an underrun जबतक the queue was empty */
	पूर्ण अन्यथा अणु
		अगर (urb->transfer_flags & URB_ISO_ASAP)
			जाओ करो_ASAP;
		wrap = mod;
		now2 += mod;
	पूर्ण

	/* How many uframes and packets करो we need to skip? */
	skip = (now2 - start + period - 1) & -period;
	अगर (skip >= span) अणु		/* Entirely in the past? */
		ehci_dbg(ehci, "iso underrun %p (%u+%u < %u) [%u]\n",
				urb, start + base, span - period, now2 + base,
				base);

		/* Try to keep the last TD पूर्णांकact क्रम scanning later */
		skip = span - period;

		/* Will it come beक्रमe the current scan position? */
		अगर (empty) अणु
			skip = span;	/* Skip the entire URB */
			status = 1;	/* and give it back immediately */
			iso_sched_मुक्त(stream, sched);
			sched = शून्य;
		पूर्ण
	पूर्ण
	urb->error_count = skip / period;
	अगर (sched)
		sched->first_packet = urb->error_count;
	जाओ use_start;

 करो_ASAP:
	/* Use the first slot after "next" */
	start = next + ((start - next) & (period - 1));

 use_start:
	/* Tried to schedule too far पूर्णांकo the future? */
	अगर (unlikely(start + span - period >= mod + wrap)) अणु
		ehci_dbg(ehci, "request %p would overflow (%u+%u >= %u)\n",
				urb, start, span - period, mod + wrap);
		status = -EFBIG;
		जाओ fail;
	पूर्ण

	start += base;
	stream->next_uframe = (start + skip) & (mod - 1);

	/* report high speed start in uframes; full speed, in frames */
	urb->start_frame = start & (mod - 1);
	अगर (!stream->highspeed)
		urb->start_frame >>= 3;
	वापस status;

 fail:
	iso_sched_मुक्त(stream, sched);
	urb->hcpriv = शून्य;
	वापस status;
पूर्ण

/*-------------------------------------------------------------------------*/

अटल अंतरभूत व्योम
itd_init(काष्ठा ehci_hcd *ehci, काष्ठा ehci_iso_stream *stream,
		काष्ठा ehci_itd *itd)
अणु
	पूर्णांक i;

	/* it's been recently zeroed */
	itd->hw_next = EHCI_LIST_END(ehci);
	itd->hw_bufp[0] = stream->buf0;
	itd->hw_bufp[1] = stream->buf1;
	itd->hw_bufp[2] = stream->buf2;

	क्रम (i = 0; i < 8; i++)
		itd->index[i] = -1;

	/* All other fields are filled when scheduling */
पूर्ण

अटल अंतरभूत व्योम
itd_patch(
	काष्ठा ehci_hcd		*ehci,
	काष्ठा ehci_itd		*itd,
	काष्ठा ehci_iso_sched	*iso_sched,
	अचिन्हित		index,
	u16			uframe
)
अणु
	काष्ठा ehci_iso_packet	*uf = &iso_sched->packet[index];
	अचिन्हित		pg = itd->pg;

	/* BUG_ON(pg == 6 && uf->cross); */

	uframe &= 0x07;
	itd->index[uframe] = index;

	itd->hw_transaction[uframe] = uf->transaction;
	itd->hw_transaction[uframe] |= cpu_to_hc32(ehci, pg << 12);
	itd->hw_bufp[pg] |= cpu_to_hc32(ehci, uf->bufp & ~(u32)0);
	itd->hw_bufp_hi[pg] |= cpu_to_hc32(ehci, (u32)(uf->bufp >> 32));

	/* iso_frame_desc[].offset must be strictly increasing */
	अगर (unlikely(uf->cross)) अणु
		u64	bufp = uf->bufp + 4096;

		itd->pg = ++pg;
		itd->hw_bufp[pg] |= cpu_to_hc32(ehci, bufp & ~(u32)0);
		itd->hw_bufp_hi[pg] |= cpu_to_hc32(ehci, (u32)(bufp >> 32));
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम
itd_link(काष्ठा ehci_hcd *ehci, अचिन्हित frame, काष्ठा ehci_itd *itd)
अणु
	जोड़ ehci_shaकरोw	*prev = &ehci->pshaकरोw[frame];
	__hc32			*hw_p = &ehci->periodic[frame];
	जोड़ ehci_shaकरोw	here = *prev;
	__hc32			type = 0;

	/* skip any iso nodes which might beदीर्घ to previous microframes */
	जबतक (here.ptr) अणु
		type = Q_NEXT_TYPE(ehci, *hw_p);
		अगर (type == cpu_to_hc32(ehci, Q_TYPE_QH))
			अवरोध;
		prev = periodic_next_shaकरोw(ehci, prev, type);
		hw_p = shaकरोw_next_periodic(ehci, &here, type);
		here = *prev;
	पूर्ण

	itd->itd_next = here;
	itd->hw_next = *hw_p;
	prev->itd = itd;
	itd->frame = frame;
	wmb();
	*hw_p = cpu_to_hc32(ehci, itd->itd_dma | Q_TYPE_ITD);
पूर्ण

/* fit urb's itds पूर्णांकo the selected schedule slot; activate as needed */
अटल व्योम itd_link_urb(
	काष्ठा ehci_hcd		*ehci,
	काष्ठा urb		*urb,
	अचिन्हित		mod,
	काष्ठा ehci_iso_stream	*stream
)
अणु
	पूर्णांक			packet;
	अचिन्हित		next_uframe, uframe, frame;
	काष्ठा ehci_iso_sched	*iso_sched = urb->hcpriv;
	काष्ठा ehci_itd		*itd;

	next_uframe = stream->next_uframe & (mod - 1);

	अगर (unlikely(list_empty(&stream->td_list)))
		ehci_to_hcd(ehci)->self.bandwidth_allocated
				+= stream->bandwidth;

	अगर (ehci_to_hcd(ehci)->self.bandwidth_isoc_reqs == 0) अणु
		अगर (ehci->amd_pll_fix == 1)
			usb_amd_quirk_pll_disable();
	पूर्ण

	ehci_to_hcd(ehci)->self.bandwidth_isoc_reqs++;

	/* fill iTDs uframe by uframe */
	क्रम (packet = iso_sched->first_packet, itd = शून्य;
			packet < urb->number_of_packets;) अणु
		अगर (itd == शून्य) अणु
			/* ASSERT:  we have all necessary itds */
			/* BUG_ON(list_empty(&iso_sched->td_list)); */

			/* ASSERT:  no itds क्रम this endpoपूर्णांक in this uframe */

			itd = list_entry(iso_sched->td_list.next,
					काष्ठा ehci_itd, itd_list);
			list_move_tail(&itd->itd_list, &stream->td_list);
			itd->stream = stream;
			itd->urb = urb;
			itd_init(ehci, stream, itd);
		पूर्ण

		uframe = next_uframe & 0x07;
		frame = next_uframe >> 3;

		itd_patch(ehci, itd, iso_sched, packet, uframe);

		next_uframe += stream->uperiod;
		next_uframe &= mod - 1;
		packet++;

		/* link completed itds पूर्णांकo the schedule */
		अगर (((next_uframe >> 3) != frame)
				|| packet == urb->number_of_packets) अणु
			itd_link(ehci, frame & (ehci->periodic_size - 1), itd);
			itd = शून्य;
		पूर्ण
	पूर्ण
	stream->next_uframe = next_uframe;

	/* करोn't need that schedule data any more */
	iso_sched_मुक्त(stream, iso_sched);
	urb->hcpriv = stream;

	++ehci->isoc_count;
	enable_periodic(ehci);
पूर्ण

#घोषणा	ISO_ERRS (EHCI_ISOC_BUF_ERR | EHCI_ISOC_BABBLE | EHCI_ISOC_XACTERR)

/* Process and recycle a completed ITD.  Return true अगरf its urb completed,
 * and hence its completion callback probably added things to the hardware
 * schedule.
 *
 * Note that we carefully aव्योम recycling this descriptor until after any
 * completion callback runs, so that it won't be reused quickly.  That is,
 * assuming (a) no more than two urbs per frame on this endpoपूर्णांक, and also
 * (b) only this endpoपूर्णांक's completions submit URBs.  It seems some silicon
 * corrupts things अगर you reuse completed descriptors very quickly...
 */
अटल bool itd_complete(काष्ठा ehci_hcd *ehci, काष्ठा ehci_itd *itd)
अणु
	काष्ठा urb				*urb = itd->urb;
	काष्ठा usb_iso_packet_descriptor	*desc;
	u32					t;
	अचिन्हित				uframe;
	पूर्णांक					urb_index = -1;
	काष्ठा ehci_iso_stream			*stream = itd->stream;
	bool					retval = false;

	/* क्रम each uframe with a packet */
	क्रम (uframe = 0; uframe < 8; uframe++) अणु
		अगर (likely(itd->index[uframe] == -1))
			जारी;
		urb_index = itd->index[uframe];
		desc = &urb->iso_frame_desc[urb_index];

		t = hc32_to_cpup(ehci, &itd->hw_transaction[uframe]);
		itd->hw_transaction[uframe] = 0;

		/* report transfer status */
		अगर (unlikely(t & ISO_ERRS)) अणु
			urb->error_count++;
			अगर (t & EHCI_ISOC_BUF_ERR)
				desc->status = usb_pipein(urb->pipe)
					? -ENOSR  /* hc couldn't पढ़ो */
					: -ECOMM; /* hc couldn't ग_लिखो */
			अन्यथा अगर (t & EHCI_ISOC_BABBLE)
				desc->status = -EOVERFLOW;
			अन्यथा /* (t & EHCI_ISOC_XACTERR) */
				desc->status = -EPROTO;

			/* HC need not update length with this error */
			अगर (!(t & EHCI_ISOC_BABBLE)) अणु
				desc->actual_length = EHCI_ITD_LENGTH(t);
				urb->actual_length += desc->actual_length;
			पूर्ण
		पूर्ण अन्यथा अगर (likely((t & EHCI_ISOC_ACTIVE) == 0)) अणु
			desc->status = 0;
			desc->actual_length = EHCI_ITD_LENGTH(t);
			urb->actual_length += desc->actual_length;
		पूर्ण अन्यथा अणु
			/* URB was too late */
			urb->error_count++;
		पूर्ण
	पूर्ण

	/* handle completion now? */
	अगर (likely((urb_index + 1) != urb->number_of_packets))
		जाओ करोne;

	/*
	 * ASSERT: it's really the last itd क्रम this urb
	 * list_क्रम_each_entry (itd, &stream->td_list, itd_list)
	 *	 BUG_ON(itd->urb == urb);
	 */

	/* give urb back to the driver; completion often (re)submits */
	ehci_urb_करोne(ehci, urb, 0);
	retval = true;
	urb = शून्य;

	--ehci->isoc_count;
	disable_periodic(ehci);

	ehci_to_hcd(ehci)->self.bandwidth_isoc_reqs--;
	अगर (ehci_to_hcd(ehci)->self.bandwidth_isoc_reqs == 0) अणु
		अगर (ehci->amd_pll_fix == 1)
			usb_amd_quirk_pll_enable();
	पूर्ण

	अगर (unlikely(list_is_singular(&stream->td_list)))
		ehci_to_hcd(ehci)->self.bandwidth_allocated
				-= stream->bandwidth;

करोne:
	itd->urb = शून्य;

	/* Add to the end of the मुक्त list क्रम later reuse */
	list_move_tail(&itd->itd_list, &stream->मुक्त_list);

	/* Recycle the iTDs when the pipeline is empty (ep no दीर्घer in use) */
	अगर (list_empty(&stream->td_list)) अणु
		list_splice_tail_init(&stream->मुक्त_list,
				&ehci->cached_itd_list);
		start_मुक्त_itds(ehci);
	पूर्ण

	वापस retval;
पूर्ण

/*-------------------------------------------------------------------------*/

अटल पूर्णांक itd_submit(काष्ठा ehci_hcd *ehci, काष्ठा urb *urb,
	gfp_t mem_flags)
अणु
	पूर्णांक			status = -EINVAL;
	अचिन्हित दीर्घ		flags;
	काष्ठा ehci_iso_stream	*stream;

	/* Get iso_stream head */
	stream = iso_stream_find(ehci, urb);
	अगर (unlikely(stream == शून्य)) अणु
		ehci_dbg(ehci, "can't get iso stream\n");
		वापस -ENOMEM;
	पूर्ण
	अगर (unlikely(urb->पूर्णांकerval != stream->uperiod)) अणु
		ehci_dbg(ehci, "can't change iso interval %d --> %d\n",
			stream->uperiod, urb->पूर्णांकerval);
		जाओ करोne;
	पूर्ण

#अगर_घोषित EHCI_URB_TRACE
	ehci_dbg(ehci,
		"%s %s urb %p ep%d%s len %d, %d pkts %d uframes [%p]\n",
		__func__, urb->dev->devpath, urb,
		usb_pipeendpoपूर्णांक(urb->pipe),
		usb_pipein(urb->pipe) ? "in" : "out",
		urb->transfer_buffer_length,
		urb->number_of_packets, urb->पूर्णांकerval,
		stream);
#पूर्ण_अगर

	/* allocate ITDs w/o locking anything */
	status = itd_urb_transaction(stream, ehci, urb, mem_flags);
	अगर (unlikely(status < 0)) अणु
		ehci_dbg(ehci, "can't init itds\n");
		जाओ करोne;
	पूर्ण

	/* schedule ... need to lock */
	spin_lock_irqsave(&ehci->lock, flags);
	अगर (unlikely(!HCD_HW_ACCESSIBLE(ehci_to_hcd(ehci)))) अणु
		status = -ESHUTDOWN;
		जाओ करोne_not_linked;
	पूर्ण
	status = usb_hcd_link_urb_to_ep(ehci_to_hcd(ehci), urb);
	अगर (unlikely(status))
		जाओ करोne_not_linked;
	status = iso_stream_schedule(ehci, urb, stream);
	अगर (likely(status == 0)) अणु
		itd_link_urb(ehci, urb, ehci->periodic_size << 3, stream);
	पूर्ण अन्यथा अगर (status > 0) अणु
		status = 0;
		ehci_urb_करोne(ehci, urb, 0);
	पूर्ण अन्यथा अणु
		usb_hcd_unlink_urb_from_ep(ehci_to_hcd(ehci), urb);
	पूर्ण
 करोne_not_linked:
	spin_unlock_irqrestore(&ehci->lock, flags);
 करोne:
	वापस status;
पूर्ण

/*-------------------------------------------------------------------------*/

/*
 * "Split ISO TDs" ... used क्रम USB 1.1 devices going through the
 * TTs in USB 2.0 hubs.  These need microframe scheduling.
 */

अटल अंतरभूत व्योम
sitd_sched_init(
	काष्ठा ehci_hcd		*ehci,
	काष्ठा ehci_iso_sched	*iso_sched,
	काष्ठा ehci_iso_stream	*stream,
	काष्ठा urb		*urb
)
अणु
	अचिन्हित	i;
	dma_addr_t	dma = urb->transfer_dma;

	/* how many frames are needed क्रम these transfers */
	iso_sched->span = urb->number_of_packets * stream->ps.period;

	/* figure out per-frame sitd fields that we'll need later
	 * when we fit new sitds पूर्णांकo the schedule.
	 */
	क्रम (i = 0; i < urb->number_of_packets; i++) अणु
		काष्ठा ehci_iso_packet	*packet = &iso_sched->packet[i];
		अचिन्हित		length;
		dma_addr_t		buf;
		u32			trans;

		length = urb->iso_frame_desc[i].length & 0x03ff;
		buf = dma + urb->iso_frame_desc[i].offset;

		trans = SITD_STS_ACTIVE;
		अगर (((i + 1) == urb->number_of_packets)
				&& !(urb->transfer_flags & URB_NO_INTERRUPT))
			trans |= SITD_IOC;
		trans |= length << 16;
		packet->transaction = cpu_to_hc32(ehci, trans);

		/* might need to cross a buffer page within a td */
		packet->bufp = buf;
		packet->buf1 = (buf + length) & ~0x0fff;
		अगर (packet->buf1 != (buf & ~(u64)0x0fff))
			packet->cross = 1;

		/* OUT uses multiple start-splits */
		अगर (stream->bEndpoपूर्णांकAddress & USB_सूची_IN)
			जारी;
		length = (length + 187) / 188;
		अगर (length > 1) /* BEGIN vs ALL */
			length |= 1 << 3;
		packet->buf1 |= length;
	पूर्ण
पूर्ण

अटल पूर्णांक
sitd_urb_transaction(
	काष्ठा ehci_iso_stream	*stream,
	काष्ठा ehci_hcd		*ehci,
	काष्ठा urb		*urb,
	gfp_t			mem_flags
)
अणु
	काष्ठा ehci_sitd	*sitd;
	dma_addr_t		sitd_dma;
	पूर्णांक			i;
	काष्ठा ehci_iso_sched	*iso_sched;
	अचिन्हित दीर्घ		flags;

	iso_sched = iso_sched_alloc(urb->number_of_packets, mem_flags);
	अगर (iso_sched == शून्य)
		वापस -ENOMEM;

	sitd_sched_init(ehci, iso_sched, stream, urb);

	/* allocate/init sITDs */
	spin_lock_irqsave(&ehci->lock, flags);
	क्रम (i = 0; i < urb->number_of_packets; i++) अणु

		/* NOTE:  क्रम now, we करोn't try to handle wraparound हालs
		 * क्रम IN (using sitd->hw_backpoपूर्णांकer, like a FSTN), which
		 * means we never need two sitds क्रम full speed packets.
		 */

		/*
		 * Use siTDs from the मुक्त list, but not siTDs that may
		 * still be in use by the hardware.
		 */
		अगर (likely(!list_empty(&stream->मुक्त_list))) अणु
			sitd = list_first_entry(&stream->मुक्त_list,
					 काष्ठा ehci_sitd, sitd_list);
			अगर (sitd->frame == ehci->now_frame)
				जाओ alloc_sitd;
			list_del(&sitd->sitd_list);
			sitd_dma = sitd->sitd_dma;
		पूर्ण अन्यथा अणु
 alloc_sitd:
			spin_unlock_irqrestore(&ehci->lock, flags);
			sitd = dma_pool_alloc(ehci->sitd_pool, mem_flags,
					&sitd_dma);
			spin_lock_irqsave(&ehci->lock, flags);
			अगर (!sitd) अणु
				iso_sched_मुक्त(stream, iso_sched);
				spin_unlock_irqrestore(&ehci->lock, flags);
				वापस -ENOMEM;
			पूर्ण
		पूर्ण

		स_रखो(sitd, 0, माप(*sitd));
		sitd->sitd_dma = sitd_dma;
		sitd->frame = NO_FRAME;
		list_add(&sitd->sitd_list, &iso_sched->td_list);
	पूर्ण

	/* temporarily store schedule info in hcpriv */
	urb->hcpriv = iso_sched;
	urb->error_count = 0;

	spin_unlock_irqrestore(&ehci->lock, flags);
	वापस 0;
पूर्ण

/*-------------------------------------------------------------------------*/

अटल अंतरभूत व्योम
sitd_patch(
	काष्ठा ehci_hcd		*ehci,
	काष्ठा ehci_iso_stream	*stream,
	काष्ठा ehci_sitd	*sitd,
	काष्ठा ehci_iso_sched	*iso_sched,
	अचिन्हित		index
)
अणु
	काष्ठा ehci_iso_packet	*uf = &iso_sched->packet[index];
	u64			bufp;

	sitd->hw_next = EHCI_LIST_END(ehci);
	sitd->hw_fullspeed_ep = stream->address;
	sitd->hw_uframe = stream->splits;
	sitd->hw_results = uf->transaction;
	sitd->hw_backpoपूर्णांकer = EHCI_LIST_END(ehci);

	bufp = uf->bufp;
	sitd->hw_buf[0] = cpu_to_hc32(ehci, bufp);
	sitd->hw_buf_hi[0] = cpu_to_hc32(ehci, bufp >> 32);

	sitd->hw_buf[1] = cpu_to_hc32(ehci, uf->buf1);
	अगर (uf->cross)
		bufp += 4096;
	sitd->hw_buf_hi[1] = cpu_to_hc32(ehci, bufp >> 32);
	sitd->index = index;
पूर्ण

अटल अंतरभूत व्योम
sitd_link(काष्ठा ehci_hcd *ehci, अचिन्हित frame, काष्ठा ehci_sitd *sitd)
अणु
	/* note: sitd ordering could matter (CSPLIT then SSPLIT) */
	sitd->sitd_next = ehci->pshaकरोw[frame];
	sitd->hw_next = ehci->periodic[frame];
	ehci->pshaकरोw[frame].sitd = sitd;
	sitd->frame = frame;
	wmb();
	ehci->periodic[frame] = cpu_to_hc32(ehci, sitd->sitd_dma | Q_TYPE_SITD);
पूर्ण

/* fit urb's sitds पूर्णांकo the selected schedule slot; activate as needed */
अटल व्योम sitd_link_urb(
	काष्ठा ehci_hcd		*ehci,
	काष्ठा urb		*urb,
	अचिन्हित		mod,
	काष्ठा ehci_iso_stream	*stream
)
अणु
	पूर्णांक			packet;
	अचिन्हित		next_uframe;
	काष्ठा ehci_iso_sched	*sched = urb->hcpriv;
	काष्ठा ehci_sitd	*sitd;

	next_uframe = stream->next_uframe;

	अगर (list_empty(&stream->td_list))
		/* usbfs ignores TT bandwidth */
		ehci_to_hcd(ehci)->self.bandwidth_allocated
				+= stream->bandwidth;

	अगर (ehci_to_hcd(ehci)->self.bandwidth_isoc_reqs == 0) अणु
		अगर (ehci->amd_pll_fix == 1)
			usb_amd_quirk_pll_disable();
	पूर्ण

	ehci_to_hcd(ehci)->self.bandwidth_isoc_reqs++;

	/* fill sITDs frame by frame */
	क्रम (packet = sched->first_packet, sitd = शून्य;
			packet < urb->number_of_packets;
			packet++) अणु

		/* ASSERT:  we have all necessary sitds */
		BUG_ON(list_empty(&sched->td_list));

		/* ASSERT:  no itds क्रम this endpoपूर्णांक in this frame */

		sitd = list_entry(sched->td_list.next,
				काष्ठा ehci_sitd, sitd_list);
		list_move_tail(&sitd->sitd_list, &stream->td_list);
		sitd->stream = stream;
		sitd->urb = urb;

		sitd_patch(ehci, stream, sitd, sched, packet);
		sitd_link(ehci, (next_uframe >> 3) & (ehci->periodic_size - 1),
				sitd);

		next_uframe += stream->uperiod;
	पूर्ण
	stream->next_uframe = next_uframe & (mod - 1);

	/* करोn't need that schedule data any more */
	iso_sched_मुक्त(stream, sched);
	urb->hcpriv = stream;

	++ehci->isoc_count;
	enable_periodic(ehci);
पूर्ण

/*-------------------------------------------------------------------------*/

#घोषणा	SITD_ERRS (SITD_STS_ERR | SITD_STS_DBE | SITD_STS_BABBLE \
				| SITD_STS_XACT | SITD_STS_MMF)

/* Process and recycle a completed SITD.  Return true अगरf its urb completed,
 * and hence its completion callback probably added things to the hardware
 * schedule.
 *
 * Note that we carefully aव्योम recycling this descriptor until after any
 * completion callback runs, so that it won't be reused quickly.  That is,
 * assuming (a) no more than two urbs per frame on this endpoपूर्णांक, and also
 * (b) only this endpoपूर्णांक's completions submit URBs.  It seems some silicon
 * corrupts things अगर you reuse completed descriptors very quickly...
 */
अटल bool sitd_complete(काष्ठा ehci_hcd *ehci, काष्ठा ehci_sitd *sitd)
अणु
	काष्ठा urb				*urb = sitd->urb;
	काष्ठा usb_iso_packet_descriptor	*desc;
	u32					t;
	पूर्णांक					urb_index;
	काष्ठा ehci_iso_stream			*stream = sitd->stream;
	bool					retval = false;

	urb_index = sitd->index;
	desc = &urb->iso_frame_desc[urb_index];
	t = hc32_to_cpup(ehci, &sitd->hw_results);

	/* report transfer status */
	अगर (unlikely(t & SITD_ERRS)) अणु
		urb->error_count++;
		अगर (t & SITD_STS_DBE)
			desc->status = usb_pipein(urb->pipe)
				? -ENOSR  /* hc couldn't पढ़ो */
				: -ECOMM; /* hc couldn't ग_लिखो */
		अन्यथा अगर (t & SITD_STS_BABBLE)
			desc->status = -EOVERFLOW;
		अन्यथा /* XACT, MMF, etc */
			desc->status = -EPROTO;
	पूर्ण अन्यथा अगर (unlikely(t & SITD_STS_ACTIVE)) अणु
		/* URB was too late */
		urb->error_count++;
	पूर्ण अन्यथा अणु
		desc->status = 0;
		desc->actual_length = desc->length - SITD_LENGTH(t);
		urb->actual_length += desc->actual_length;
	पूर्ण

	/* handle completion now? */
	अगर ((urb_index + 1) != urb->number_of_packets)
		जाओ करोne;

	/*
	 * ASSERT: it's really the last sitd क्रम this urb
	 * list_क्रम_each_entry (sitd, &stream->td_list, sitd_list)
	 *	 BUG_ON(sitd->urb == urb);
	 */

	/* give urb back to the driver; completion often (re)submits */
	ehci_urb_करोne(ehci, urb, 0);
	retval = true;
	urb = शून्य;

	--ehci->isoc_count;
	disable_periodic(ehci);

	ehci_to_hcd(ehci)->self.bandwidth_isoc_reqs--;
	अगर (ehci_to_hcd(ehci)->self.bandwidth_isoc_reqs == 0) अणु
		अगर (ehci->amd_pll_fix == 1)
			usb_amd_quirk_pll_enable();
	पूर्ण

	अगर (list_is_singular(&stream->td_list))
		ehci_to_hcd(ehci)->self.bandwidth_allocated
				-= stream->bandwidth;

करोne:
	sitd->urb = शून्य;

	/* Add to the end of the मुक्त list क्रम later reuse */
	list_move_tail(&sitd->sitd_list, &stream->मुक्त_list);

	/* Recycle the siTDs when the pipeline is empty (ep no दीर्घer in use) */
	अगर (list_empty(&stream->td_list)) अणु
		list_splice_tail_init(&stream->मुक्त_list,
				&ehci->cached_sitd_list);
		start_मुक्त_itds(ehci);
	पूर्ण

	वापस retval;
पूर्ण


अटल पूर्णांक sitd_submit(काष्ठा ehci_hcd *ehci, काष्ठा urb *urb,
	gfp_t mem_flags)
अणु
	पूर्णांक			status = -EINVAL;
	अचिन्हित दीर्घ		flags;
	काष्ठा ehci_iso_stream	*stream;

	/* Get iso_stream head */
	stream = iso_stream_find(ehci, urb);
	अगर (stream == शून्य) अणु
		ehci_dbg(ehci, "can't get iso stream\n");
		वापस -ENOMEM;
	पूर्ण
	अगर (urb->पूर्णांकerval != stream->ps.period) अणु
		ehci_dbg(ehci, "can't change iso interval %d --> %d\n",
			stream->ps.period, urb->पूर्णांकerval);
		जाओ करोne;
	पूर्ण

#अगर_घोषित EHCI_URB_TRACE
	ehci_dbg(ehci,
		"submit %p dev%s ep%d%s-iso len %d\n",
		urb, urb->dev->devpath,
		usb_pipeendpoपूर्णांक(urb->pipe),
		usb_pipein(urb->pipe) ? "in" : "out",
		urb->transfer_buffer_length);
#पूर्ण_अगर

	/* allocate SITDs */
	status = sitd_urb_transaction(stream, ehci, urb, mem_flags);
	अगर (status < 0) अणु
		ehci_dbg(ehci, "can't init sitds\n");
		जाओ करोne;
	पूर्ण

	/* schedule ... need to lock */
	spin_lock_irqsave(&ehci->lock, flags);
	अगर (unlikely(!HCD_HW_ACCESSIBLE(ehci_to_hcd(ehci)))) अणु
		status = -ESHUTDOWN;
		जाओ करोne_not_linked;
	पूर्ण
	status = usb_hcd_link_urb_to_ep(ehci_to_hcd(ehci), urb);
	अगर (unlikely(status))
		जाओ करोne_not_linked;
	status = iso_stream_schedule(ehci, urb, stream);
	अगर (likely(status == 0)) अणु
		sitd_link_urb(ehci, urb, ehci->periodic_size << 3, stream);
	पूर्ण अन्यथा अगर (status > 0) अणु
		status = 0;
		ehci_urb_करोne(ehci, urb, 0);
	पूर्ण अन्यथा अणु
		usb_hcd_unlink_urb_from_ep(ehci_to_hcd(ehci), urb);
	पूर्ण
 करोne_not_linked:
	spin_unlock_irqrestore(&ehci->lock, flags);
 करोne:
	वापस status;
पूर्ण

/*-------------------------------------------------------------------------*/

अटल व्योम scan_isoc(काष्ठा ehci_hcd *ehci)
अणु
	अचिन्हित		uf, now_frame, frame;
	अचिन्हित		fmask = ehci->periodic_size - 1;
	bool			modअगरied, live;
	जोड़ ehci_shaकरोw	q, *q_p;
	__hc32			type, *hw_p;

	/*
	 * When running, scan from last scan poपूर्णांक up to "now"
	 * अन्यथा clean up by scanning everything that's left.
	 * Touches as few pages as possible:  cache-मित्रly.
	 */
	अगर (ehci->rh_state >= EHCI_RH_RUNNING) अणु
		uf = ehci_पढ़ो_frame_index(ehci);
		now_frame = (uf >> 3) & fmask;
		live = true;
	पूर्ण अन्यथा  अणु
		now_frame = (ehci->last_iso_frame - 1) & fmask;
		live = false;
	पूर्ण
	ehci->now_frame = now_frame;

	frame = ehci->last_iso_frame;

restart:
	/* Scan each element in frame's queue क्रम completions */
	q_p = &ehci->pshaकरोw[frame];
	hw_p = &ehci->periodic[frame];
	q.ptr = q_p->ptr;
	type = Q_NEXT_TYPE(ehci, *hw_p);
	modअगरied = false;

	जबतक (q.ptr != शून्य) अणु
		चयन (hc32_to_cpu(ehci, type)) अणु
		हाल Q_TYPE_ITD:
			/*
			 * If this ITD is still active, leave it क्रम
			 * later processing ... check the next entry.
			 * No need to check क्रम activity unless the
			 * frame is current.
			 */
			अगर (frame == now_frame && live) अणु
				rmb();
				क्रम (uf = 0; uf < 8; uf++) अणु
					अगर (q.itd->hw_transaction[uf] &
							ITD_ACTIVE(ehci))
						अवरोध;
				पूर्ण
				अगर (uf < 8) अणु
					q_p = &q.itd->itd_next;
					hw_p = &q.itd->hw_next;
					type = Q_NEXT_TYPE(ehci,
							q.itd->hw_next);
					q = *q_p;
					अवरोध;
				पूर्ण
			पूर्ण

			/*
			 * Take finished ITDs out of the schedule
			 * and process them:  recycle, maybe report
			 * URB completion.  HC won't cache the
			 * poपूर्णांकer क्रम much दीर्घer, अगर at all.
			 */
			*q_p = q.itd->itd_next;
			अगर (!ehci->use_dummy_qh ||
					q.itd->hw_next != EHCI_LIST_END(ehci))
				*hw_p = q.itd->hw_next;
			अन्यथा
				*hw_p = cpu_to_hc32(ehci, ehci->dummy->qh_dma);
			type = Q_NEXT_TYPE(ehci, q.itd->hw_next);
			wmb();
			modअगरied = itd_complete(ehci, q.itd);
			q = *q_p;
			अवरोध;
		हाल Q_TYPE_SITD:
			/*
			 * If this SITD is still active, leave it क्रम
			 * later processing ... check the next entry.
			 * No need to check क्रम activity unless the
			 * frame is current.
			 */
			अगर (((frame == now_frame) ||
					(((frame + 1) & fmask) == now_frame))
				&& live
				&& (q.sitd->hw_results & SITD_ACTIVE(ehci))) अणु

				q_p = &q.sitd->sitd_next;
				hw_p = &q.sitd->hw_next;
				type = Q_NEXT_TYPE(ehci, q.sitd->hw_next);
				q = *q_p;
				अवरोध;
			पूर्ण

			/*
			 * Take finished SITDs out of the schedule
			 * and process them:  recycle, maybe report
			 * URB completion.
			 */
			*q_p = q.sitd->sitd_next;
			अगर (!ehci->use_dummy_qh ||
					q.sitd->hw_next != EHCI_LIST_END(ehci))
				*hw_p = q.sitd->hw_next;
			अन्यथा
				*hw_p = cpu_to_hc32(ehci, ehci->dummy->qh_dma);
			type = Q_NEXT_TYPE(ehci, q.sitd->hw_next);
			wmb();
			modअगरied = sitd_complete(ehci, q.sitd);
			q = *q_p;
			अवरोध;
		शेष:
			ehci_dbg(ehci, "corrupt type %d frame %d shadow %p\n",
					type, frame, q.ptr);
			/* BUG(); */
			fallthrough;
		हाल Q_TYPE_QH:
		हाल Q_TYPE_FSTN:
			/* End of the iTDs and siTDs */
			q.ptr = शून्य;
			अवरोध;
		पूर्ण

		/* Assume completion callbacks modअगरy the queue */
		अगर (unlikely(modअगरied && ehci->isoc_count > 0))
			जाओ restart;
	पूर्ण

	/* Stop when we have reached the current frame */
	अगर (frame == now_frame)
		वापस;

	/* The last frame may still have active siTDs */
	ehci->last_iso_frame = frame;
	frame = (frame + 1) & fmask;

	जाओ restart;
पूर्ण
