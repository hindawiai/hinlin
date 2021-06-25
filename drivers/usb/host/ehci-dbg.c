<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (c) 2001-2002 by David Brownell
 */

/* this file is part of ehci-hcd.c */

#अगर_घोषित CONFIG_DYNAMIC_DEBUG

/*
 * check the values in the HCSPARAMS रेजिस्टर
 * (host controller _Structural_ parameters)
 * see EHCI spec, Table 2-4 क्रम each value
 */
अटल व्योम dbg_hcs_params(काष्ठा ehci_hcd *ehci, अक्षर *label)
अणु
	u32	params = ehci_पढ़ोl(ehci, &ehci->caps->hcs_params);

	ehci_dbg(ehci,
		"%s hcs_params 0x%x dbg=%d%s cc=%d pcc=%d%s%s ports=%d\n",
		label, params,
		HCS_DEBUG_PORT(params),
		HCS_INDICATOR(params) ? " ind" : "",
		HCS_N_CC(params),
		HCS_N_PCC(params),
		HCS_PORTROUTED(params) ? "" : " ordered",
		HCS_PPC(params) ? "" : " !ppc",
		HCS_N_PORTS(params));
	/* Port routing, per EHCI 0.95 Spec, Section 2.2.5 */
	अगर (HCS_PORTROUTED(params)) अणु
		पूर्णांक i;
		अक्षर buf[46], पंचांगp[7], byte;

		buf[0] = 0;
		क्रम (i = 0; i < HCS_N_PORTS(params); i++) अणु
			/* FIXME MIPS won't पढ़ोb() ... */
			byte = पढ़ोb(&ehci->caps->portroute[(i >> 1)]);
			प्र_लिखो(पंचांगp, "%d ",
				(i & 0x1) ? byte & 0xf : (byte >> 4) & 0xf);
			म_जोड़ो(buf, पंचांगp);
		पूर्ण
		ehci_dbg(ehci, "%s portroute %s\n", label, buf);
	पूर्ण
पूर्ण

/*
 * check the values in the HCCPARAMS रेजिस्टर
 * (host controller _Capability_ parameters)
 * see EHCI Spec, Table 2-5 क्रम each value
 */
अटल व्योम dbg_hcc_params(काष्ठा ehci_hcd *ehci, अक्षर *label)
अणु
	u32	params = ehci_पढ़ोl(ehci, &ehci->caps->hcc_params);

	अगर (HCC_ISOC_CACHE(params)) अणु
		ehci_dbg(ehci,
			"%s hcc_params %04x caching frame %s%s%s\n",
			label, params,
			HCC_PGM_FRAMELISTLEN(params) ? "256/512/1024" : "1024",
			HCC_CANPARK(params) ? " park" : "",
			HCC_64BIT_ADDR(params) ? " 64 bit addr" : "");
	पूर्ण अन्यथा अणु
		ehci_dbg(ehci,
			"%s hcc_params %04x thresh %d uframes %s%s%s%s%s%s%s\n",
			label,
			params,
			HCC_ISOC_THRES(params),
			HCC_PGM_FRAMELISTLEN(params) ? "256/512/1024" : "1024",
			HCC_CANPARK(params) ? " park" : "",
			HCC_64BIT_ADDR(params) ? " 64 bit addr" : "",
			HCC_LPM(params) ? " LPM" : "",
			HCC_PER_PORT_CHANGE_EVENT(params) ? " ppce" : "",
			HCC_HW_PREFETCH(params) ? " hw prefetch" : "",
			HCC_32FRAME_PERIODIC_LIST(params) ?
				" 32 periodic list" : "");
	पूर्ण
पूर्ण

अटल व्योम __maybe_unused
dbg_qtd(स्थिर अक्षर *label, काष्ठा ehci_hcd *ehci, काष्ठा ehci_qtd *qtd)
अणु
	ehci_dbg(ehci, "%s td %p n%08x %08x t%08x p0=%08x\n", label, qtd,
		hc32_to_cpup(ehci, &qtd->hw_next),
		hc32_to_cpup(ehci, &qtd->hw_alt_next),
		hc32_to_cpup(ehci, &qtd->hw_token),
		hc32_to_cpup(ehci, &qtd->hw_buf[0]));
	अगर (qtd->hw_buf[1])
		ehci_dbg(ehci, "  p1=%08x p2=%08x p3=%08x p4=%08x\n",
			hc32_to_cpup(ehci, &qtd->hw_buf[1]),
			hc32_to_cpup(ehci, &qtd->hw_buf[2]),
			hc32_to_cpup(ehci, &qtd->hw_buf[3]),
			hc32_to_cpup(ehci, &qtd->hw_buf[4]));
पूर्ण

अटल व्योम __maybe_unused
dbg_qh(स्थिर अक्षर *label, काष्ठा ehci_hcd *ehci, काष्ठा ehci_qh *qh)
अणु
	काष्ठा ehci_qh_hw *hw = qh->hw;

	ehci_dbg(ehci, "%s qh %p n%08x info %x %x qtd %x\n", label,
		qh, hw->hw_next, hw->hw_info1, hw->hw_info2, hw->hw_current);
	dbg_qtd("overlay", ehci, (काष्ठा ehci_qtd *) &hw->hw_qtd_next);
पूर्ण

अटल व्योम __maybe_unused
dbg_itd(स्थिर अक्षर *label, काष्ठा ehci_hcd *ehci, काष्ठा ehci_itd *itd)
अणु
	ehci_dbg(ehci, "%s [%d] itd %p, next %08x, urb %p\n",
		label, itd->frame, itd, hc32_to_cpu(ehci, itd->hw_next),
		itd->urb);
	ehci_dbg(ehci,
		"  trans: %08x %08x %08x %08x %08x %08x %08x %08x\n",
		hc32_to_cpu(ehci, itd->hw_transaction[0]),
		hc32_to_cpu(ehci, itd->hw_transaction[1]),
		hc32_to_cpu(ehci, itd->hw_transaction[2]),
		hc32_to_cpu(ehci, itd->hw_transaction[3]),
		hc32_to_cpu(ehci, itd->hw_transaction[4]),
		hc32_to_cpu(ehci, itd->hw_transaction[5]),
		hc32_to_cpu(ehci, itd->hw_transaction[6]),
		hc32_to_cpu(ehci, itd->hw_transaction[7]));
	ehci_dbg(ehci,
		"  buf:   %08x %08x %08x %08x %08x %08x %08x\n",
		hc32_to_cpu(ehci, itd->hw_bufp[0]),
		hc32_to_cpu(ehci, itd->hw_bufp[1]),
		hc32_to_cpu(ehci, itd->hw_bufp[2]),
		hc32_to_cpu(ehci, itd->hw_bufp[3]),
		hc32_to_cpu(ehci, itd->hw_bufp[4]),
		hc32_to_cpu(ehci, itd->hw_bufp[5]),
		hc32_to_cpu(ehci, itd->hw_bufp[6]));
	ehci_dbg(ehci, "  index: %d %d %d %d %d %d %d %d\n",
		itd->index[0], itd->index[1], itd->index[2],
		itd->index[3], itd->index[4], itd->index[5],
		itd->index[6], itd->index[7]);
पूर्ण

अटल व्योम __maybe_unused
dbg_sitd(स्थिर अक्षर *label, काष्ठा ehci_hcd *ehci, काष्ठा ehci_sitd *sitd)
अणु
	ehci_dbg(ehci, "%s [%d] sitd %p, next %08x, urb %p\n",
		label, sitd->frame, sitd, hc32_to_cpu(ehci, sitd->hw_next),
		sitd->urb);
	ehci_dbg(ehci,
		"  addr %08x sched %04x result %08x buf %08x %08x\n",
		hc32_to_cpu(ehci, sitd->hw_fullspeed_ep),
		hc32_to_cpu(ehci, sitd->hw_uframe),
		hc32_to_cpu(ehci, sitd->hw_results),
		hc32_to_cpu(ehci, sitd->hw_buf[0]),
		hc32_to_cpu(ehci, sitd->hw_buf[1]));
पूर्ण

अटल पूर्णांक __maybe_unused
dbg_status_buf(अक्षर *buf, अचिन्हित len, स्थिर अक्षर *label, u32 status)
अणु
	वापस scnम_लिखो(buf, len,
		"%s%sstatus %04x%s%s%s%s%s%s%s%s%s%s%s",
		label, label[0] ? " " : "", status,
		(status & STS_PPCE_MASK) ? " PPCE" : "",
		(status & STS_ASS) ? " Async" : "",
		(status & STS_PSS) ? " Periodic" : "",
		(status & STS_RECL) ? " Recl" : "",
		(status & STS_HALT) ? " Halt" : "",
		(status & STS_IAA) ? " IAA" : "",
		(status & STS_FATAL) ? " FATAL" : "",
		(status & STS_FLR) ? " FLR" : "",
		(status & STS_PCD) ? " PCD" : "",
		(status & STS_ERR) ? " ERR" : "",
		(status & STS_INT) ? " INT" : "");
पूर्ण

अटल पूर्णांक __maybe_unused
dbg_पूर्णांकr_buf(अक्षर *buf, अचिन्हित len, स्थिर अक्षर *label, u32 enable)
अणु
	वापस scnम_लिखो(buf, len,
		"%s%sintrenable %02x%s%s%s%s%s%s%s",
		label, label[0] ? " " : "", enable,
		(enable & STS_PPCE_MASK) ? " PPCE" : "",
		(enable & STS_IAA) ? " IAA" : "",
		(enable & STS_FATAL) ? " FATAL" : "",
		(enable & STS_FLR) ? " FLR" : "",
		(enable & STS_PCD) ? " PCD" : "",
		(enable & STS_ERR) ? " ERR" : "",
		(enable & STS_INT) ? " INT" : "");
पूर्ण

अटल स्थिर अक्षर *स्थिर fls_strings[] = अणु "1024", "512", "256", "??" पूर्ण;

अटल पूर्णांक
dbg_command_buf(अक्षर *buf, अचिन्हित len, स्थिर अक्षर *label, u32 command)
अणु
	वापस scnम_लिखो(buf, len,
		"%s%scommand %07x %s%s%s%s%s%s=%d ithresh=%d%s%s%s%s "
		"period=%s%s %s",
		label, label[0] ? " " : "", command,
		(command & CMD_HIRD) ? " HIRD" : "",
		(command & CMD_PPCEE) ? " PPCEE" : "",
		(command & CMD_FSP) ? " FSP" : "",
		(command & CMD_ASPE) ? " ASPE" : "",
		(command & CMD_PSPE) ? " PSPE" : "",
		(command & CMD_PARK) ? " park" : "(park)",
		CMD_PARK_CNT(command),
		(command >> 16) & 0x3f,
		(command & CMD_LRESET) ? " LReset" : "",
		(command & CMD_IAAD) ? " IAAD" : "",
		(command & CMD_ASE) ? " Async" : "",
		(command & CMD_PSE) ? " Periodic" : "",
		fls_strings[(command >> 2) & 0x3],
		(command & CMD_RESET) ? " Reset" : "",
		(command & CMD_RUN) ? "RUN" : "HALT");
पूर्ण

अटल पूर्णांक
dbg_port_buf(अक्षर *buf, अचिन्हित len, स्थिर अक्षर *label, पूर्णांक port, u32 status)
अणु
	अक्षर	*sig;

	/* संकेतing state */
	चयन (status & (3 << 10)) अणु
	हाल 0 << 10:
		sig = "se0";
		अवरोध;
	हाल 1 << 10: /* low speed */
		sig = "k";
		अवरोध;
	हाल 2 << 10:
		sig = "j";
		अवरोध;
	शेष:
		sig = "?";
		अवरोध;
	पूर्ण

	वापस scnम_लिखो(buf, len,
		"%s%sport:%d status %06x %d %s%s%s%s%s%s "
		"sig=%s%s%s%s%s%s%s%s%s%s%s",
		label, label[0] ? " " : "", port, status,
		status >> 25, /*device address */
		(status & PORT_SSTS) >> 23 == PORTSC_SUSPEND_STS_ACK ?
						" ACK" : "",
		(status & PORT_SSTS) >> 23 == PORTSC_SUSPEND_STS_NYET ?
						" NYET" : "",
		(status & PORT_SSTS) >> 23 == PORTSC_SUSPEND_STS_STALL ?
						" STALL" : "",
		(status & PORT_SSTS) >> 23 == PORTSC_SUSPEND_STS_ERR ?
						" ERR" : "",
		(status & PORT_POWER) ? " POWER" : "",
		(status & PORT_OWNER) ? " OWNER" : "",
		sig,
		(status & PORT_LPM) ? " LPM" : "",
		(status & PORT_RESET) ? " RESET" : "",
		(status & PORT_SUSPEND) ? " SUSPEND" : "",
		(status & PORT_RESUME) ? " RESUME" : "",
		(status & PORT_OCC) ? " OCC" : "",
		(status & PORT_OC) ? " OC" : "",
		(status & PORT_PEC) ? " PEC" : "",
		(status & PORT_PE) ? " PE" : "",
		(status & PORT_CSC) ? " CSC" : "",
		(status & PORT_CONNECT) ? " CONNECT" : "");
पूर्ण

अटल अंतरभूत व्योम
dbg_status(काष्ठा ehci_hcd *ehci, स्थिर अक्षर *label, u32 status)
अणु
	अक्षर buf[80];

	dbg_status_buf(buf, माप(buf), label, status);
	ehci_dbg(ehci, "%s\n", buf);
पूर्ण

अटल अंतरभूत व्योम
dbg_cmd(काष्ठा ehci_hcd *ehci, स्थिर अक्षर *label, u32 command)
अणु
	अक्षर buf[80];

	dbg_command_buf(buf, माप(buf), label, command);
	ehci_dbg(ehci, "%s\n", buf);
पूर्ण

अटल अंतरभूत व्योम
dbg_port(काष्ठा ehci_hcd *ehci, स्थिर अक्षर *label, पूर्णांक port, u32 status)
अणु
	अक्षर buf[80];

	dbg_port_buf(buf, माप(buf), label, port, status);
	ehci_dbg(ehci, "%s\n", buf);
पूर्ण

/*-------------------------------------------------------------------------*/

/* troubleshooting help: expose state in debugfs */

अटल पूर्णांक debug_async_खोलो(काष्ठा inode *, काष्ठा file *);
अटल पूर्णांक debug_bandwidth_खोलो(काष्ठा inode *, काष्ठा file *);
अटल पूर्णांक debug_periodic_खोलो(काष्ठा inode *, काष्ठा file *);
अटल पूर्णांक debug_रेजिस्टरs_खोलो(काष्ठा inode *, काष्ठा file *);

अटल sमाप_प्रकार debug_output(काष्ठा file*, अक्षर __user*, माप_प्रकार, loff_t*);
अटल पूर्णांक debug_बंद(काष्ठा inode *, काष्ठा file *);

अटल स्थिर काष्ठा file_operations debug_async_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= debug_async_खोलो,
	.पढ़ो		= debug_output,
	.release	= debug_बंद,
	.llseek		= शेष_llseek,
पूर्ण;

अटल स्थिर काष्ठा file_operations debug_bandwidth_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= debug_bandwidth_खोलो,
	.पढ़ो		= debug_output,
	.release	= debug_बंद,
	.llseek		= शेष_llseek,
पूर्ण;

अटल स्थिर काष्ठा file_operations debug_periodic_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= debug_periodic_खोलो,
	.पढ़ो		= debug_output,
	.release	= debug_बंद,
	.llseek		= शेष_llseek,
पूर्ण;

अटल स्थिर काष्ठा file_operations debug_रेजिस्टरs_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= debug_रेजिस्टरs_खोलो,
	.पढ़ो		= debug_output,
	.release	= debug_बंद,
	.llseek		= शेष_llseek,
पूर्ण;

अटल काष्ठा dentry *ehci_debug_root;

काष्ठा debug_buffer अणु
	sमाप_प्रकार (*fill_func)(काष्ठा debug_buffer *);	/* fill method */
	काष्ठा usb_bus *bus;
	काष्ठा mutex mutex;	/* protect filling of buffer */
	माप_प्रकार count;		/* number of अक्षरacters filled पूर्णांकo buffer */
	अक्षर *output_buf;
	माप_प्रकार alloc_size;
पूर्ण;

अटल अंतरभूत अक्षर speed_अक्षर(u32 info1)
अणु
	चयन (info1 & (3 << 12)) अणु
	हाल QH_FULL_SPEED:
		वापस 'f';
	हाल QH_LOW_SPEED:
		वापस 'l';
	हाल QH_HIGH_SPEED:
		वापस 'h';
	शेष:
		वापस '?';
	पूर्ण
पूर्ण

अटल अंतरभूत अक्षर token_mark(काष्ठा ehci_hcd *ehci, __hc32 token)
अणु
	__u32 v = hc32_to_cpu(ehci, token);

	अगर (v & QTD_STS_ACTIVE)
		वापस '*';
	अगर (v & QTD_STS_HALT)
		वापस '-';
	अगर (!IS_SHORT_READ(v))
		वापस ' ';
	/* tries to advance through hw_alt_next */
	वापस '/';
पूर्ण

अटल व्योम qh_lines(काष्ठा ehci_hcd *ehci, काष्ठा ehci_qh *qh,
		अक्षर **nextp, अचिन्हित *sizep)
अणु
	u32			scratch;
	u32			hw_curr;
	काष्ठा list_head	*entry;
	काष्ठा ehci_qtd		*td;
	अचिन्हित		temp;
	अचिन्हित		size = *sizep;
	अक्षर			*next = *nextp;
	अक्षर			mark;
	__le32			list_end = EHCI_LIST_END(ehci);
	काष्ठा ehci_qh_hw	*hw = qh->hw;

	अगर (hw->hw_qtd_next == list_end)	/* NEC करोes this */
		mark = '@';
	अन्यथा
		mark = token_mark(ehci, hw->hw_token);
	अगर (mark == '/') अणु	/* qh_alt_next controls qh advance? */
		अगर ((hw->hw_alt_next & QTD_MASK(ehci))
				== ehci->async->hw->hw_alt_next)
			mark = '#';	/* blocked */
		अन्यथा अगर (hw->hw_alt_next == list_end)
			mark = '.';	/* use hw_qtd_next */
		/* अन्यथा alt_next poपूर्णांकs to some other qtd */
	पूर्ण
	scratch = hc32_to_cpup(ehci, &hw->hw_info1);
	hw_curr = (mark == '*') ? hc32_to_cpup(ehci, &hw->hw_current) : 0;
	temp = scnम_लिखो(next, size,
			"qh/%p dev%d %cs ep%d %08x %08x (%08x%c %s nak%d)"
			" [cur %08x next %08x buf[0] %08x]",
			qh, scratch & 0x007f,
			speed_अक्षर (scratch),
			(scratch >> 8) & 0x000f,
			scratch, hc32_to_cpup(ehci, &hw->hw_info2),
			hc32_to_cpup(ehci, &hw->hw_token), mark,
			(cpu_to_hc32(ehci, QTD_TOGGLE) & hw->hw_token)
				? "data1" : "data0",
			(hc32_to_cpup(ehci, &hw->hw_alt_next) >> 1) & 0x0f,
			hc32_to_cpup(ehci, &hw->hw_current),
			hc32_to_cpup(ehci, &hw->hw_qtd_next),
			hc32_to_cpup(ehci, &hw->hw_buf[0]));
	size -= temp;
	next += temp;

	/* hc may be modअगरying the list as we पढ़ो it ... */
	list_क्रम_each(entry, &qh->qtd_list) अणु
		अक्षर *type;

		td = list_entry(entry, काष्ठा ehci_qtd, qtd_list);
		scratch = hc32_to_cpup(ehci, &td->hw_token);
		mark = ' ';
		अगर (hw_curr == td->qtd_dma) अणु
			mark = '*';
		पूर्ण अन्यथा अगर (hw->hw_qtd_next == cpu_to_hc32(ehci, td->qtd_dma)) अणु
			mark = '+';
		पूर्ण अन्यथा अगर (QTD_LENGTH(scratch)) अणु
			अगर (td->hw_alt_next == ehci->async->hw->hw_alt_next)
				mark = '#';
			अन्यथा अगर (td->hw_alt_next != list_end)
				mark = '/';
		पूर्ण
		चयन ((scratch >> 8) & 0x03) अणु
		हाल 0:
			type = "out";
			अवरोध;
		हाल 1:
			type = "in";
			अवरोध;
		हाल 2:
			type = "setup";
			अवरोध;
		शेष:
			type = "?";
			अवरोध;
		पूर्ण
		temp = scnम_लिखो(next, size,
				"\n\t%p%c%s len=%d %08x urb %p"
				" [td %08x buf[0] %08x]",
				td, mark, type,
				(scratch >> 16) & 0x7fff,
				scratch,
				td->urb,
				(u32) td->qtd_dma,
				hc32_to_cpup(ehci, &td->hw_buf[0]));
		size -= temp;
		next += temp;
		अगर (temp == size)
			जाओ करोne;
	पूर्ण

	temp = scnम_लिखो(next, size, "\n");
	size -= temp;
	next += temp;

करोne:
	*sizep = size;
	*nextp = next;
पूर्ण

अटल sमाप_प्रकार fill_async_buffer(काष्ठा debug_buffer *buf)
अणु
	काष्ठा usb_hcd		*hcd;
	काष्ठा ehci_hcd		*ehci;
	अचिन्हित दीर्घ		flags;
	अचिन्हित		temp, size;
	अक्षर			*next;
	काष्ठा ehci_qh		*qh;

	hcd = bus_to_hcd(buf->bus);
	ehci = hcd_to_ehci(hcd);
	next = buf->output_buf;
	size = buf->alloc_size;

	*next = 0;

	/*
	 * dumps a snapshot of the async schedule.
	 * usually empty except क्रम दीर्घ-term bulk पढ़ोs, or head.
	 * one QH per line, and TDs we know about
	 */
	spin_lock_irqsave(&ehci->lock, flags);
	क्रम (qh = ehci->async->qh_next.qh; size > 0 && qh; qh = qh->qh_next.qh)
		qh_lines(ehci, qh, &next, &size);
	अगर (!list_empty(&ehci->async_unlink) && size > 0) अणु
		temp = scnम_लिखो(next, size, "\nunlink =\n");
		size -= temp;
		next += temp;

		list_क्रम_each_entry(qh, &ehci->async_unlink, unlink_node) अणु
			अगर (size <= 0)
				अवरोध;
			qh_lines(ehci, qh, &next, &size);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&ehci->lock, flags);

	वापस म_माप(buf->output_buf);
पूर्ण

अटल sमाप_प्रकार fill_bandwidth_buffer(काष्ठा debug_buffer *buf)
अणु
	काष्ठा ehci_hcd		*ehci;
	काष्ठा ehci_tt		*tt;
	काष्ठा ehci_per_sched	*ps;
	अचिन्हित		temp, size;
	अक्षर			*next;
	अचिन्हित		i;
	u8			*bw;
	u16			*bf;
	u8			budget[EHCI_BANDWIDTH_SIZE];

	ehci = hcd_to_ehci(bus_to_hcd(buf->bus));
	next = buf->output_buf;
	size = buf->alloc_size;

	*next = 0;

	spin_lock_irq(&ehci->lock);

	/* Dump the HS bandwidth table */
	temp = scnम_लिखो(next, size,
			"HS bandwidth allocation (us per microframe)\n");
	size -= temp;
	next += temp;
	क्रम (i = 0; i < EHCI_BANDWIDTH_SIZE; i += 8) अणु
		bw = &ehci->bandwidth[i];
		temp = scnम_लिखो(next, size,
				"%2u: %4u%4u%4u%4u%4u%4u%4u%4u\n",
				i, bw[0], bw[1], bw[2], bw[3],
					bw[4], bw[5], bw[6], bw[7]);
		size -= temp;
		next += temp;
	पूर्ण

	/* Dump all the FS/LS tables */
	list_क्रम_each_entry(tt, &ehci->tt_list, tt_list) अणु
		temp = scnम_लिखो(next, size,
				"\nTT %s port %d  FS/LS bandwidth allocation (us per frame)\n",
				dev_name(&tt->usb_tt->hub->dev),
				tt->tt_port + !!tt->usb_tt->multi);
		size -= temp;
		next += temp;

		bf = tt->bandwidth;
		temp = scnम_लिखो(next, size,
				"  %5u%5u%5u%5u%5u%5u%5u%5u\n",
				bf[0], bf[1], bf[2], bf[3],
					bf[4], bf[5], bf[6], bf[7]);
		size -= temp;
		next += temp;

		temp = scnम_लिखो(next, size,
				"FS/LS budget (us per microframe)\n");
		size -= temp;
		next += temp;
		compute_tt_budget(budget, tt);
		क्रम (i = 0; i < EHCI_BANDWIDTH_SIZE; i += 8) अणु
			bw = &budget[i];
			temp = scnम_लिखो(next, size,
					"%2u: %4u%4u%4u%4u%4u%4u%4u%4u\n",
					i, bw[0], bw[1], bw[2], bw[3],
						bw[4], bw[5], bw[6], bw[7]);
			size -= temp;
			next += temp;
		पूर्ण
		list_क्रम_each_entry(ps, &tt->ps_list, ps_list) अणु
			temp = scnम_लिखो(next, size,
					"%s ep %02x:  %4u @ %2u.%u+%u mask %04x\n",
					dev_name(&ps->udev->dev),
					ps->ep->desc.bEndpoपूर्णांकAddress,
					ps->tt_usecs,
					ps->bw_phase, ps->phase_uf,
					ps->bw_period, ps->cs_mask);
			size -= temp;
			next += temp;
		पूर्ण
	पूर्ण
	spin_unlock_irq(&ehci->lock);

	वापस next - buf->output_buf;
पूर्ण

अटल अचिन्हित output_buf_tds_dir(अक्षर *buf, काष्ठा ehci_hcd *ehci,
		काष्ठा ehci_qh_hw *hw, काष्ठा ehci_qh *qh, अचिन्हित size)
अणु
	u32			scratch = hc32_to_cpup(ehci, &hw->hw_info1);
	काष्ठा ehci_qtd		*qtd;
	अक्षर			*type = "";
	अचिन्हित		temp = 0;

	/* count tds, get ep direction */
	list_क्रम_each_entry(qtd, &qh->qtd_list, qtd_list) अणु
		temp++;
		चयन ((hc32_to_cpu(ehci, qtd->hw_token) >> 8)	& 0x03) अणु
		हाल 0:
			type = "out";
			जारी;
		हाल 1:
			type = "in";
			जारी;
		पूर्ण
	पूर्ण

	वापस scnम_लिखो(buf, size, " (%c%d ep%d%s [%d/%d] q%d p%d)",
			speed_अक्षर(scratch), scratch & 0x007f,
			(scratch >> 8) & 0x000f, type, qh->ps.usecs,
			qh->ps.c_usecs, temp, 0x7ff & (scratch >> 16));
पूर्ण

#घोषणा DBG_SCHED_LIMIT 64
अटल sमाप_प्रकार fill_periodic_buffer(काष्ठा debug_buffer *buf)
अणु
	काष्ठा usb_hcd		*hcd;
	काष्ठा ehci_hcd		*ehci;
	अचिन्हित दीर्घ		flags;
	जोड़ ehci_shaकरोw	p, *seen;
	अचिन्हित		temp, size, seen_count;
	अक्षर			*next;
	अचिन्हित		i;
	__hc32			tag;

	seen = kदो_स्मृति_array(DBG_SCHED_LIMIT, माप(*seen), GFP_ATOMIC);
	अगर (!seen)
		वापस 0;
	seen_count = 0;

	hcd = bus_to_hcd(buf->bus);
	ehci = hcd_to_ehci(hcd);
	next = buf->output_buf;
	size = buf->alloc_size;

	temp = scnम_लिखो(next, size, "size = %d\n", ehci->periodic_size);
	size -= temp;
	next += temp;

	/*
	 * dump a snapshot of the periodic schedule.
	 * iso changes, पूर्णांकerrupt usually करोesn't.
	 */
	spin_lock_irqsave(&ehci->lock, flags);
	क्रम (i = 0; i < ehci->periodic_size; i++) अणु
		p = ehci->pshaकरोw[i];
		अगर (likely(!p.ptr))
			जारी;
		tag = Q_NEXT_TYPE(ehci, ehci->periodic[i]);

		temp = scnम_लिखो(next, size, "%4d: ", i);
		size -= temp;
		next += temp;

		करो अणु
			काष्ठा ehci_qh_hw *hw;

			चयन (hc32_to_cpu(ehci, tag)) अणु
			हाल Q_TYPE_QH:
				hw = p.qh->hw;
				temp = scnम_लिखो(next, size, " qh%d-%04x/%p",
						p.qh->ps.period,
						hc32_to_cpup(ehci,
							&hw->hw_info2)
							/* uframe masks */
							& (QH_CMASK | QH_SMASK),
						p.qh);
				size -= temp;
				next += temp;
				/* करोn't repeat what follows this qh */
				क्रम (temp = 0; temp < seen_count; temp++) अणु
					अगर (seen[temp].ptr != p.ptr)
						जारी;
					अगर (p.qh->qh_next.ptr) अणु
						temp = scnम_लिखो(next, size,
							" ...");
						size -= temp;
						next += temp;
					पूर्ण
					अवरोध;
				पूर्ण
				/* show more info the first समय around */
				अगर (temp == seen_count) अणु
					temp = output_buf_tds_dir(next, ehci,
						hw, p.qh, size);

					अगर (seen_count < DBG_SCHED_LIMIT)
						seen[seen_count++].qh = p.qh;
				पूर्ण अन्यथा अणु
					temp = 0;
				पूर्ण
				tag = Q_NEXT_TYPE(ehci, hw->hw_next);
				p = p.qh->qh_next;
				अवरोध;
			हाल Q_TYPE_FSTN:
				temp = scnम_लिखो(next, size,
					" fstn-%8x/%p", p.fstn->hw_prev,
					p.fstn);
				tag = Q_NEXT_TYPE(ehci, p.fstn->hw_next);
				p = p.fstn->fstn_next;
				अवरोध;
			हाल Q_TYPE_ITD:
				temp = scnम_लिखो(next, size,
					" itd/%p", p.itd);
				tag = Q_NEXT_TYPE(ehci, p.itd->hw_next);
				p = p.itd->itd_next;
				अवरोध;
			हाल Q_TYPE_SITD:
				temp = scnम_लिखो(next, size,
					" sitd%d-%04x/%p",
					p.sitd->stream->ps.period,
					hc32_to_cpup(ehci, &p.sitd->hw_uframe)
						& 0x0000ffff,
					p.sitd);
				tag = Q_NEXT_TYPE(ehci, p.sitd->hw_next);
				p = p.sitd->sitd_next;
				अवरोध;
			पूर्ण
			size -= temp;
			next += temp;
		पूर्ण जबतक (p.ptr);

		temp = scnम_लिखो(next, size, "\n");
		size -= temp;
		next += temp;
	पूर्ण
	spin_unlock_irqrestore(&ehci->lock, flags);
	kमुक्त(seen);

	वापस buf->alloc_size - size;
पूर्ण
#अघोषित DBG_SCHED_LIMIT

अटल स्थिर अक्षर *rh_state_string(काष्ठा ehci_hcd *ehci)
अणु
	चयन (ehci->rh_state) अणु
	हाल EHCI_RH_HALTED:
		वापस "halted";
	हाल EHCI_RH_SUSPENDED:
		वापस "suspended";
	हाल EHCI_RH_RUNNING:
		वापस "running";
	हाल EHCI_RH_STOPPING:
		वापस "stopping";
	पूर्ण
	वापस "?";
पूर्ण

अटल sमाप_प्रकार fill_रेजिस्टरs_buffer(काष्ठा debug_buffer *buf)
अणु
	काष्ठा usb_hcd		*hcd;
	काष्ठा ehci_hcd		*ehci;
	अचिन्हित दीर्घ		flags;
	अचिन्हित		temp, size, i;
	अक्षर			*next, scratch[80];
	अटल अक्षर		fmt[] = "%*s\n";
	अटल अक्षर		label[] = "";

	hcd = bus_to_hcd(buf->bus);
	ehci = hcd_to_ehci(hcd);
	next = buf->output_buf;
	size = buf->alloc_size;

	spin_lock_irqsave(&ehci->lock, flags);

	अगर (!HCD_HW_ACCESSIBLE(hcd)) अणु
		size = scnम_लिखो(next, size,
			"bus %s, device %s\n"
			"%s\n"
			"SUSPENDED (no register access)\n",
			hcd->self.controller->bus->name,
			dev_name(hcd->self.controller),
			hcd->product_desc);
		जाओ करोne;
	पूर्ण

	/* Capability Registers */
	i = HC_VERSION(ehci, ehci_पढ़ोl(ehci, &ehci->caps->hc_capbase));
	temp = scnम_लिखो(next, size,
		"bus %s, device %s\n"
		"%s\n"
		"EHCI %x.%02x, rh state %s\n",
		hcd->self.controller->bus->name,
		dev_name(hcd->self.controller),
		hcd->product_desc,
		i >> 8, i & 0x0ff, rh_state_string(ehci));
	size -= temp;
	next += temp;

#अगर_घोषित	CONFIG_USB_PCI
	/* EHCI 0.96 and later may have "extended capabilities" */
	अगर (dev_is_pci(hcd->self.controller)) अणु
		काष्ठा pci_dev	*pdev;
		u32		offset, cap, cap2;
		अचिन्हित	count = 256 / 4;

		pdev = to_pci_dev(ehci_to_hcd(ehci)->self.controller);
		offset = HCC_EXT_CAPS(ehci_पढ़ोl(ehci,
				&ehci->caps->hcc_params));
		जबतक (offset && count--) अणु
			pci_पढ़ो_config_dword(pdev, offset, &cap);
			चयन (cap & 0xff) अणु
			हाल 1:
				temp = scnम_लिखो(next, size,
					"ownership %08x%s%s\n", cap,
					(cap & (1 << 24)) ? " linux" : "",
					(cap & (1 << 16)) ? " firmware" : "");
				size -= temp;
				next += temp;

				offset += 4;
				pci_पढ़ो_config_dword(pdev, offset, &cap2);
				temp = scnम_लिखो(next, size,
					"SMI sts/enable 0x%08x\n", cap2);
				size -= temp;
				next += temp;
				अवरोध;
			हाल 0:		/* illegal reserved capability */
				cap = 0;
				fallthrough;
			शेष:		/* unknown */
				अवरोध;
			पूर्ण
			offset = (cap >> 8) & 0xff;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	/* FIXME पूर्णांकerpret both types of params */
	i = ehci_पढ़ोl(ehci, &ehci->caps->hcs_params);
	temp = scnम_लिखो(next, size, "structural params 0x%08x\n", i);
	size -= temp;
	next += temp;

	i = ehci_पढ़ोl(ehci, &ehci->caps->hcc_params);
	temp = scnम_लिखो(next, size, "capability params 0x%08x\n", i);
	size -= temp;
	next += temp;

	/* Operational Registers */
	temp = dbg_status_buf(scratch, माप(scratch), label,
			ehci_पढ़ोl(ehci, &ehci->regs->status));
	temp = scnम_लिखो(next, size, fmt, temp, scratch);
	size -= temp;
	next += temp;

	temp = dbg_command_buf(scratch, माप(scratch), label,
			ehci_पढ़ोl(ehci, &ehci->regs->command));
	temp = scnम_लिखो(next, size, fmt, temp, scratch);
	size -= temp;
	next += temp;

	temp = dbg_पूर्णांकr_buf(scratch, माप(scratch), label,
			ehci_पढ़ोl(ehci, &ehci->regs->पूर्णांकr_enable));
	temp = scnम_लिखो(next, size, fmt, temp, scratch);
	size -= temp;
	next += temp;

	temp = scnम_लिखो(next, size, "uframe %04x\n",
			ehci_पढ़ो_frame_index(ehci));
	size -= temp;
	next += temp;

	क्रम (i = 1; i <= HCS_N_PORTS(ehci->hcs_params); i++) अणु
		temp = dbg_port_buf(scratch, माप(scratch), label, i,
				ehci_पढ़ोl(ehci,
					&ehci->regs->port_status[i - 1]));
		temp = scnम_लिखो(next, size, fmt, temp, scratch);
		size -= temp;
		next += temp;
		अगर (i == HCS_DEBUG_PORT(ehci->hcs_params) && ehci->debug) अणु
			temp = scnम_लिखो(next, size,
					"    debug control %08x\n",
					ehci_पढ़ोl(ehci,
						&ehci->debug->control));
			size -= temp;
			next += temp;
		पूर्ण
	पूर्ण

	अगर (!list_empty(&ehci->async_unlink)) अणु
		temp = scnम_लिखो(next, size, "async unlink qh %p\n",
				list_first_entry(&ehci->async_unlink,
						काष्ठा ehci_qh, unlink_node));
		size -= temp;
		next += temp;
	पूर्ण

#अगर_घोषित EHCI_STATS
	temp = scnम_लिखो(next, size,
		"irq normal %ld err %ld iaa %ld (lost %ld)\n",
		ehci->stats.normal, ehci->stats.error, ehci->stats.iaa,
		ehci->stats.lost_iaa);
	size -= temp;
	next += temp;

	temp = scnम_लिखो(next, size, "complete %ld unlink %ld\n",
		ehci->stats.complete, ehci->stats.unlink);
	size -= temp;
	next += temp;
#पूर्ण_अगर

करोne:
	spin_unlock_irqrestore(&ehci->lock, flags);

	वापस buf->alloc_size - size;
पूर्ण

अटल काष्ठा debug_buffer *alloc_buffer(काष्ठा usb_bus *bus,
		sमाप_प्रकार (*fill_func)(काष्ठा debug_buffer *))
अणु
	काष्ठा debug_buffer *buf;

	buf = kzalloc(माप(*buf), GFP_KERNEL);

	अगर (buf) अणु
		buf->bus = bus;
		buf->fill_func = fill_func;
		mutex_init(&buf->mutex);
		buf->alloc_size = PAGE_SIZE;
	पूर्ण

	वापस buf;
पूर्ण

अटल पूर्णांक fill_buffer(काष्ठा debug_buffer *buf)
अणु
	पूर्णांक ret = 0;

	अगर (!buf->output_buf)
		buf->output_buf = vदो_स्मृति(buf->alloc_size);

	अगर (!buf->output_buf) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	ret = buf->fill_func(buf);

	अगर (ret >= 0) अणु
		buf->count = ret;
		ret = 0;
	पूर्ण

out:
	वापस ret;
पूर्ण

अटल sमाप_प्रकार debug_output(काष्ठा file *file, अक्षर __user *user_buf,
		माप_प्रकार len, loff_t *offset)
अणु
	काष्ठा debug_buffer *buf = file->निजी_data;
	पूर्णांक ret = 0;

	mutex_lock(&buf->mutex);
	अगर (buf->count == 0) अणु
		ret = fill_buffer(buf);
		अगर (ret != 0) अणु
			mutex_unlock(&buf->mutex);
			जाओ out;
		पूर्ण
	पूर्ण
	mutex_unlock(&buf->mutex);

	ret = simple_पढ़ो_from_buffer(user_buf, len, offset,
				      buf->output_buf, buf->count);

out:
	वापस ret;
पूर्ण

अटल पूर्णांक debug_बंद(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा debug_buffer *buf = file->निजी_data;

	अगर (buf) अणु
		vमुक्त(buf->output_buf);
		kमुक्त(buf);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक debug_async_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	file->निजी_data = alloc_buffer(inode->i_निजी, fill_async_buffer);

	वापस file->निजी_data ? 0 : -ENOMEM;
पूर्ण

अटल पूर्णांक debug_bandwidth_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	file->निजी_data = alloc_buffer(inode->i_निजी,
			fill_bandwidth_buffer);

	वापस file->निजी_data ? 0 : -ENOMEM;
पूर्ण

अटल पूर्णांक debug_periodic_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा debug_buffer *buf;

	buf = alloc_buffer(inode->i_निजी, fill_periodic_buffer);
	अगर (!buf)
		वापस -ENOMEM;

	buf->alloc_size = (माप(व्योम *) == 4 ? 6 : 8) * PAGE_SIZE;
	file->निजी_data = buf;
	वापस 0;
पूर्ण

अटल पूर्णांक debug_रेजिस्टरs_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	file->निजी_data = alloc_buffer(inode->i_निजी,
					  fill_रेजिस्टरs_buffer);

	वापस file->निजी_data ? 0 : -ENOMEM;
पूर्ण

अटल अंतरभूत व्योम create_debug_files(काष्ठा ehci_hcd *ehci)
अणु
	काष्ठा usb_bus *bus = &ehci_to_hcd(ehci)->self;

	ehci->debug_dir = debugfs_create_dir(bus->bus_name, ehci_debug_root);

	debugfs_create_file("async", S_IRUGO, ehci->debug_dir, bus,
			    &debug_async_fops);
	debugfs_create_file("bandwidth", S_IRUGO, ehci->debug_dir, bus,
			    &debug_bandwidth_fops);
	debugfs_create_file("periodic", S_IRUGO, ehci->debug_dir, bus,
			    &debug_periodic_fops);
	debugfs_create_file("registers", S_IRUGO, ehci->debug_dir, bus,
			    &debug_रेजिस्टरs_fops);
पूर्ण

अटल अंतरभूत व्योम हटाओ_debug_files(काष्ठा ehci_hcd *ehci)
अणु
	debugfs_हटाओ_recursive(ehci->debug_dir);
पूर्ण

#अन्यथा /* CONFIG_DYNAMIC_DEBUG */

अटल अंतरभूत व्योम dbg_hcs_params(काष्ठा ehci_hcd *ehci, अक्षर *label) अणु पूर्ण
अटल अंतरभूत व्योम dbg_hcc_params(काष्ठा ehci_hcd *ehci, अक्षर *label) अणु पूर्ण

अटल अंतरभूत व्योम __maybe_unused dbg_qh(स्थिर अक्षर *label,
		काष्ठा ehci_hcd *ehci, काष्ठा ehci_qh *qh) अणु पूर्ण

अटल अंतरभूत पूर्णांक __maybe_unused dbg_status_buf(स्थिर अक्षर *buf,
		अचिन्हित पूर्णांक len, स्थिर अक्षर *label, u32 status)
अणु वापस 0; पूर्ण

अटल अंतरभूत पूर्णांक __maybe_unused dbg_command_buf(स्थिर अक्षर *buf,
		अचिन्हित पूर्णांक len, स्थिर अक्षर *label, u32 command)
अणु वापस 0; पूर्ण

अटल अंतरभूत पूर्णांक __maybe_unused dbg_पूर्णांकr_buf(स्थिर अक्षर *buf,
		अचिन्हित पूर्णांक len, स्थिर अक्षर *label, u32 enable)
अणु वापस 0; पूर्ण

अटल अंतरभूत पूर्णांक __maybe_unused dbg_port_buf(अक्षर *buf,
		अचिन्हित पूर्णांक len, स्थिर अक्षर *label, पूर्णांक port, u32 status)
अणु वापस 0; पूर्ण

अटल अंतरभूत व्योम dbg_status(काष्ठा ehci_hcd *ehci, स्थिर अक्षर *label,
		u32 status) अणु पूर्ण
अटल अंतरभूत व्योम dbg_cmd(काष्ठा ehci_hcd *ehci, स्थिर अक्षर *label,
		u32 command) अणु पूर्ण
अटल अंतरभूत व्योम dbg_port(काष्ठा ehci_hcd *ehci, स्थिर अक्षर *label,
		पूर्णांक port, u32 status) अणु पूर्ण

अटल अंतरभूत व्योम create_debug_files(काष्ठा ehci_hcd *bus) अणु पूर्ण
अटल अंतरभूत व्योम हटाओ_debug_files(काष्ठा ehci_hcd *bus) अणु पूर्ण

#पूर्ण_अगर /* CONFIG_DYNAMIC_DEBUG */
