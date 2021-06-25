<शैली गुरु>
// SPDX-License-Identअगरier: GPL-1.0+
/*
 * OHCI HCD (Host Controller Driver) क्रम USB.
 *
 * (C) Copyright 1999 Roman Weissgaerber <weissg@vienna.at>
 * (C) Copyright 2000-2002 David Brownell <dbrownell@users.sourceक्रमge.net>
 *
 * This file is licenced under the GPL.
 */

/*-------------------------------------------------------------------------*/

#घोषणा edstring(ed_type) (अणु अक्षर *temp; \
	चयन (ed_type) अणु \
	हाल PIPE_CONTROL:	temp = "ctrl"; अवरोध; \
	हाल PIPE_BULK:		temp = "bulk"; अवरोध; \
	हाल PIPE_INTERRUPT:	temp = "intr"; अवरोध; \
	शेष:		temp = "isoc"; अवरोध; \
	पूर्ण temp;पूर्ण)
#घोषणा pipestring(pipe) edstring(usb_pipetype(pipe))


#घोषणा ohci_dbg_sw(ohci, next, size, क्रमmat, arg...) \
	करो अणु \
	अगर (next != शून्य) अणु \
		अचिन्हित s_len; \
		s_len = scnम_लिखो (*next, *size, क्रमmat, ## arg ); \
		*size -= s_len; *next += s_len; \
	पूर्ण अन्यथा \
		ohci_dbg(ohci,क्रमmat, ## arg ); \
	पूर्ण जबतक (0);

/* Version क्रम use where "next" is the address of a local variable */
#घोषणा ohci_dbg_nosw(ohci, next, size, क्रमmat, arg...) \
	करो अणु \
		अचिन्हित s_len; \
		s_len = scnम_लिखो(*next, *size, क्रमmat, ## arg); \
		*size -= s_len; *next += s_len; \
	पूर्ण जबतक (0);


अटल व्योम ohci_dump_पूर्णांकr_mask (
	काष्ठा ohci_hcd *ohci,
	अक्षर *label,
	u32 mask,
	अक्षर **next,
	अचिन्हित *size)
अणु
	ohci_dbg_sw (ohci, next, size, "%s 0x%08x%s%s%s%s%s%s%s%s%s\n",
		label,
		mask,
		(mask & OHCI_INTR_MIE) ? " MIE" : "",
		(mask & OHCI_INTR_OC) ? " OC" : "",
		(mask & OHCI_INTR_RHSC) ? " RHSC" : "",
		(mask & OHCI_INTR_FNO) ? " FNO" : "",
		(mask & OHCI_INTR_UE) ? " UE" : "",
		(mask & OHCI_INTR_RD) ? " RD" : "",
		(mask & OHCI_INTR_SF) ? " SF" : "",
		(mask & OHCI_INTR_WDH) ? " WDH" : "",
		(mask & OHCI_INTR_SO) ? " SO" : ""
		);
पूर्ण

अटल व्योम maybe_prपूर्णांक_eds (
	काष्ठा ohci_hcd *ohci,
	अक्षर *label,
	u32 value,
	अक्षर **next,
	अचिन्हित *size)
अणु
	अगर (value)
		ohci_dbg_sw (ohci, next, size, "%s %08x\n", label, value);
पूर्ण

अटल अक्षर *hcfs2string (पूर्णांक state)
अणु
	चयन (state) अणु
		हाल OHCI_USB_RESET:	वापस "reset";
		हाल OHCI_USB_RESUME:	वापस "resume";
		हाल OHCI_USB_OPER:	वापस "operational";
		हाल OHCI_USB_SUSPEND:	वापस "suspend";
	पूर्ण
	वापस "?";
पूर्ण

अटल स्थिर अक्षर *rh_state_string(काष्ठा ohci_hcd *ohci)
अणु
	चयन (ohci->rh_state) अणु
	हाल OHCI_RH_HALTED:
		वापस "halted";
	हाल OHCI_RH_SUSPENDED:
		वापस "suspended";
	हाल OHCI_RH_RUNNING:
		वापस "running";
	पूर्ण
	वापस "?";
पूर्ण

// dump control and status रेजिस्टरs
अटल व्योम
ohci_dump_status (काष्ठा ohci_hcd *controller, अक्षर **next, अचिन्हित *size)
अणु
	काष्ठा ohci_regs __iomem *regs = controller->regs;
	u32			temp;

	temp = ohci_पढ़ोl (controller, &regs->revision) & 0xff;
	ohci_dbg_sw (controller, next, size,
		"OHCI %d.%d, %s legacy support registers, rh state %s\n",
		0x03 & (temp >> 4), (temp & 0x0f),
		(temp & 0x0100) ? "with" : "NO",
		rh_state_string(controller));

	temp = ohci_पढ़ोl (controller, &regs->control);
	ohci_dbg_sw (controller, next, size,
		"control 0x%03x%s%s%s HCFS=%s%s%s%s%s CBSR=%d\n",
		temp,
		(temp & OHCI_CTRL_RWE) ? " RWE" : "",
		(temp & OHCI_CTRL_RWC) ? " RWC" : "",
		(temp & OHCI_CTRL_IR) ? " IR" : "",
		hcfs2string (temp & OHCI_CTRL_HCFS),
		(temp & OHCI_CTRL_BLE) ? " BLE" : "",
		(temp & OHCI_CTRL_CLE) ? " CLE" : "",
		(temp & OHCI_CTRL_IE) ? " IE" : "",
		(temp & OHCI_CTRL_PLE) ? " PLE" : "",
		temp & OHCI_CTRL_CBSR
		);

	temp = ohci_पढ़ोl (controller, &regs->cmdstatus);
	ohci_dbg_sw (controller, next, size,
		"cmdstatus 0x%05x SOC=%d%s%s%s%s\n", temp,
		(temp & OHCI_SOC) >> 16,
		(temp & OHCI_OCR) ? " OCR" : "",
		(temp & OHCI_BLF) ? " BLF" : "",
		(temp & OHCI_CLF) ? " CLF" : "",
		(temp & OHCI_HCR) ? " HCR" : ""
		);

	ohci_dump_पूर्णांकr_mask (controller, "intrstatus",
			ohci_पढ़ोl (controller, &regs->पूर्णांकrstatus),
			next, size);
	ohci_dump_पूर्णांकr_mask (controller, "intrenable",
			ohci_पढ़ोl (controller, &regs->पूर्णांकrenable),
			next, size);
	// पूर्णांकrdisable always same as पूर्णांकrenable

	maybe_prपूर्णांक_eds (controller, "ed_periodcurrent",
			ohci_पढ़ोl (controller, &regs->ed_periodcurrent),
			next, size);

	maybe_prपूर्णांक_eds (controller, "ed_controlhead",
			ohci_पढ़ोl (controller, &regs->ed_controlhead),
			next, size);
	maybe_prपूर्णांक_eds (controller, "ed_controlcurrent",
			ohci_पढ़ोl (controller, &regs->ed_controlcurrent),
			next, size);

	maybe_prपूर्णांक_eds (controller, "ed_bulkhead",
			ohci_पढ़ोl (controller, &regs->ed_bulkhead),
			next, size);
	maybe_prपूर्णांक_eds (controller, "ed_bulkcurrent",
			ohci_पढ़ोl (controller, &regs->ed_bulkcurrent),
			next, size);

	maybe_prपूर्णांक_eds (controller, "donehead",
			ohci_पढ़ोl (controller, &regs->करोnehead), next, size);
पूर्ण

#घोषणा dbg_port_sw(hc,num,value,next,size) \
	ohci_dbg_sw (hc, next, size, \
		"roothub.portstatus [%d] " \
		"0x%08x%s%s%s%s%s%s%s%s%s%s%s%s\n", \
		num, temp, \
		(temp & RH_PS_PRSC) ? " PRSC" : "", \
		(temp & RH_PS_OCIC) ? " OCIC" : "", \
		(temp & RH_PS_PSSC) ? " PSSC" : "", \
		(temp & RH_PS_PESC) ? " PESC" : "", \
		(temp & RH_PS_CSC) ? " CSC" : "", \
		\
		(temp & RH_PS_LSDA) ? " LSDA" : "", \
		(temp & RH_PS_PPS) ? " PPS" : "", \
		(temp & RH_PS_PRS) ? " PRS" : "", \
		(temp & RH_PS_POCI) ? " POCI" : "", \
		(temp & RH_PS_PSS) ? " PSS" : "", \
		\
		(temp & RH_PS_PES) ? " PES" : "", \
		(temp & RH_PS_CCS) ? " CCS" : "" \
		);


अटल व्योम
ohci_dump_roothub (
	काष्ठा ohci_hcd *controller,
	पूर्णांक verbose,
	अक्षर **next,
	अचिन्हित *size)
अणु
	u32			temp, i;

	temp = roothub_a (controller);
	अगर (temp == ~(u32)0)
		वापस;

	अगर (verbose) अणु
		ohci_dbg_sw (controller, next, size,
			"roothub.a %08x POTPGT=%d%s%s%s%s%s NDP=%d(%d)\n", temp,
			((temp & RH_A_POTPGT) >> 24) & 0xff,
			(temp & RH_A_NOCP) ? " NOCP" : "",
			(temp & RH_A_OCPM) ? " OCPM" : "",
			(temp & RH_A_DT) ? " DT" : "",
			(temp & RH_A_NPS) ? " NPS" : "",
			(temp & RH_A_PSM) ? " PSM" : "",
			(temp & RH_A_NDP), controller->num_ports
			);
		temp = roothub_b (controller);
		ohci_dbg_sw (controller, next, size,
			"roothub.b %08x PPCM=%04x DR=%04x\n",
			temp,
			(temp & RH_B_PPCM) >> 16,
			(temp & RH_B_DR)
			);
		temp = roothub_status (controller);
		ohci_dbg_sw (controller, next, size,
			"roothub.status %08x%s%s%s%s%s%s\n",
			temp,
			(temp & RH_HS_CRWE) ? " CRWE" : "",
			(temp & RH_HS_OCIC) ? " OCIC" : "",
			(temp & RH_HS_LPSC) ? " LPSC" : "",
			(temp & RH_HS_DRWE) ? " DRWE" : "",
			(temp & RH_HS_OCI) ? " OCI" : "",
			(temp & RH_HS_LPS) ? " LPS" : ""
			);
	पूर्ण

	क्रम (i = 0; i < controller->num_ports; i++) अणु
		temp = roothub_portstatus (controller, i);
		dbg_port_sw (controller, i, temp, next, size);
	पूर्ण
पूर्ण

अटल व्योम ohci_dump(काष्ठा ohci_hcd *controller)
अणु
	ohci_dbg (controller, "OHCI controller state\n");

	// dumps some of the state we know about
	ohci_dump_status (controller, शून्य, शून्य);
	अगर (controller->hcca)
		ohci_dbg (controller,
			"hcca frame #%04x\n", ohci_frame_no(controller));
	ohci_dump_roothub (controller, 1, शून्य, शून्य);
पूर्ण

अटल स्थिर अक्षर data0 [] = "DATA0";
अटल स्थिर अक्षर data1 [] = "DATA1";

अटल व्योम ohci_dump_td (स्थिर काष्ठा ohci_hcd *ohci, स्थिर अक्षर *label,
		स्थिर काष्ठा td *td)
अणु
	u32	पंचांगp = hc32_to_cpup (ohci, &td->hwINFO);

	ohci_dbg (ohci, "%s td %p%s; urb %p index %d; hw next td %08x\n",
		label, td,
		(पंचांगp & TD_DONE) ? " (DONE)" : "",
		td->urb, td->index,
		hc32_to_cpup (ohci, &td->hwNextTD));
	अगर ((पंचांगp & TD_ISO) == 0) अणु
		स्थिर अक्षर	*toggle, *pid;
		u32	cbp, be;

		चयन (पंचांगp & TD_T) अणु
		हाल TD_T_DATA0: toggle = data0; अवरोध;
		हाल TD_T_DATA1: toggle = data1; अवरोध;
		हाल TD_T_TOGGLE: toggle = "(CARRY)"; अवरोध;
		शेष: toggle = "(?)"; अवरोध;
		पूर्ण
		चयन (पंचांगp & TD_DP) अणु
		हाल TD_DP_SETUP: pid = "SETUP"; अवरोध;
		हाल TD_DP_IN: pid = "IN"; अवरोध;
		हाल TD_DP_OUT: pid = "OUT"; अवरोध;
		शेष: pid = "(bad pid)"; अवरोध;
		पूर्ण
		ohci_dbg (ohci, "     info %08x CC=%x %s DI=%d %s %s\n", पंचांगp,
			TD_CC_GET(पंचांगp), /* EC, */ toggle,
			(पंचांगp & TD_DI) >> 21, pid,
			(पंचांगp & TD_R) ? "R" : "");
		cbp = hc32_to_cpup (ohci, &td->hwCBP);
		be = hc32_to_cpup (ohci, &td->hwBE);
		ohci_dbg (ohci, "     cbp %08x be %08x (len %d)\n", cbp, be,
			cbp ? (be + 1 - cbp) : 0);
	पूर्ण अन्यथा अणु
		अचिन्हित	i;
		ohci_dbg (ohci, "  info %08x CC=%x FC=%d DI=%d SF=%04x\n", पंचांगp,
			TD_CC_GET(पंचांगp),
			(पंचांगp >> 24) & 0x07,
			(पंचांगp & TD_DI) >> 21,
			पंचांगp & 0x0000ffff);
		ohci_dbg (ohci, "  bp0 %08x be %08x\n",
			hc32_to_cpup (ohci, &td->hwCBP) & ~0x0fff,
			hc32_to_cpup (ohci, &td->hwBE));
		क्रम (i = 0; i < MAXPSW; i++) अणु
			u16	psw = ohci_hwPSW (ohci, td, i);
			पूर्णांक	cc = (psw >> 12) & 0x0f;
			ohci_dbg (ohci, "    psw [%d] = %2x, CC=%x %s=%d\n", i,
				psw, cc,
				(cc >= 0x0e) ? "OFFSET" : "SIZE",
				psw & 0x0fff);
		पूर्ण
	पूर्ण
पूर्ण

/* caller MUST own hcd spinlock अगर verbose is set! */
अटल व्योम __maybe_unused
ohci_dump_ed (स्थिर काष्ठा ohci_hcd *ohci, स्थिर अक्षर *label,
		स्थिर काष्ठा ed *ed, पूर्णांक verbose)
अणु
	u32	पंचांगp = hc32_to_cpu (ohci, ed->hwINFO);
	अक्षर	*type = "";

	ohci_dbg (ohci, "%s, ed %p state 0x%x type %s; next ed %08x\n",
		label,
		ed, ed->state, edstring (ed->type),
		hc32_to_cpup (ohci, &ed->hwNextED));
	चयन (पंचांगp & (ED_IN|ED_OUT)) अणु
	हाल ED_OUT: type = "-OUT"; अवरोध;
	हाल ED_IN: type = "-IN"; अवरोध;
	/* अन्यथा from TDs ... control */
	पूर्ण
	ohci_dbg (ohci,
		"  info %08x MAX=%d%s%s%s%s EP=%d%s DEV=%d\n", पंचांगp,
		0x03ff & (पंचांगp >> 16),
		(पंचांगp & ED_DEQUEUE) ? " DQ" : "",
		(पंचांगp & ED_ISO) ? " ISO" : "",
		(पंचांगp & ED_SKIP) ? " SKIP" : "",
		(पंचांगp & ED_LOWSPEED) ? " LOW" : "",
		0x000f & (पंचांगp >> 7),
		type,
		0x007f & पंचांगp);
	पंचांगp = hc32_to_cpup (ohci, &ed->hwHeadP);
	ohci_dbg (ohci, "  tds: head %08x %s%s tail %08x%s\n",
		पंचांगp,
		(पंचांगp & ED_C) ? data1 : data0,
		(पंचांगp & ED_H) ? " HALT" : "",
		hc32_to_cpup (ohci, &ed->hwTailP),
		verbose ? "" : " (not listing)");
	अगर (verbose) अणु
		काष्ठा list_head	*पंचांगp;

		/* use ed->td_list because HC concurrently modअगरies
		 * hwNextTD as it accumulates ed_करोnelist.
		 */
		list_क्रम_each (पंचांगp, &ed->td_list) अणु
			काष्ठा td		*td;
			td = list_entry (पंचांगp, काष्ठा td, td_list);
			ohci_dump_td (ohci, "  ->", td);
		पूर्ण
	पूर्ण
पूर्ण

/*-------------------------------------------------------------------------*/

अटल पूर्णांक debug_async_खोलो(काष्ठा inode *, काष्ठा file *);
अटल पूर्णांक debug_periodic_खोलो(काष्ठा inode *, काष्ठा file *);
अटल पूर्णांक debug_रेजिस्टरs_खोलो(काष्ठा inode *, काष्ठा file *);
अटल पूर्णांक debug_async_खोलो(काष्ठा inode *, काष्ठा file *);
अटल sमाप_प्रकार debug_output(काष्ठा file*, अक्षर __user*, माप_प्रकार, loff_t*);
अटल पूर्णांक debug_बंद(काष्ठा inode *, काष्ठा file *);

अटल स्थिर काष्ठा file_operations debug_async_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= debug_async_खोलो,
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

अटल काष्ठा dentry *ohci_debug_root;

काष्ठा debug_buffer अणु
	sमाप_प्रकार (*fill_func)(काष्ठा debug_buffer *);	/* fill method */
	काष्ठा ohci_hcd *ohci;
	काष्ठा mutex mutex;	/* protect filling of buffer */
	माप_प्रकार count;		/* number of अक्षरacters filled पूर्णांकo buffer */
	अक्षर *page;
पूर्ण;

अटल sमाप_प्रकार
show_list (काष्ठा ohci_hcd *ohci, अक्षर *buf, माप_प्रकार count, काष्ठा ed *ed)
अणु
	अचिन्हित		temp, size = count;

	अगर (!ed)
		वापस 0;

	/* prपूर्णांक first --> last */
	जबतक (ed->ed_prev)
		ed = ed->ed_prev;

	/* dump a snapshot of the bulk or control schedule */
	जबतक (ed) अणु
		u32		info = hc32_to_cpu (ohci, ed->hwINFO);
		u32		headp = hc32_to_cpu (ohci, ed->hwHeadP);
		काष्ठा list_head *entry;
		काष्ठा td	*td;

		temp = scnम_लिखो (buf, size,
			"ed/%p %cs dev%d ep%d%s max %d %08x%s%s %s",
			ed,
			(info & ED_LOWSPEED) ? 'l' : 'f',
			info & 0x7f,
			(info >> 7) & 0xf,
			(info & ED_IN) ? "in" : "out",
			0x03ff & (info >> 16),
			info,
			(info & ED_SKIP) ? " s" : "",
			(headp & ED_H) ? " H" : "",
			(headp & ED_C) ? data1 : data0);
		size -= temp;
		buf += temp;

		list_क्रम_each (entry, &ed->td_list) अणु
			u32		cbp, be;

			td = list_entry (entry, काष्ठा td, td_list);
			info = hc32_to_cpup (ohci, &td->hwINFO);
			cbp = hc32_to_cpup (ohci, &td->hwCBP);
			be = hc32_to_cpup (ohci, &td->hwBE);
			temp = scnम_लिखो (buf, size,
					"\n\ttd %p %s %d cc=%x urb %p (%08x)",
					td,
					(अणु अक्षर *pid;
					चयन (info & TD_DP) अणु
					हाल TD_DP_SETUP: pid = "setup"; अवरोध;
					हाल TD_DP_IN: pid = "in"; अवरोध;
					हाल TD_DP_OUT: pid = "out"; अवरोध;
					शेष: pid = "(?)"; अवरोध;
					 पूर्ण pid;पूर्ण),
					cbp ? (be + 1 - cbp) : 0,
					TD_CC_GET (info), td->urb, info);
			size -= temp;
			buf += temp;
		पूर्ण

		temp = scnम_लिखो (buf, size, "\n");
		size -= temp;
		buf += temp;

		ed = ed->ed_next;
	पूर्ण
	वापस count - size;
पूर्ण

अटल sमाप_प्रकार fill_async_buffer(काष्ठा debug_buffer *buf)
अणु
	काष्ठा ohci_hcd		*ohci;
	माप_प्रकार			temp, size;
	अचिन्हित दीर्घ		flags;

	ohci = buf->ohci;
	size = PAGE_SIZE;

	/* display control and bulk lists together, क्रम simplicity */
	spin_lock_irqsave (&ohci->lock, flags);
	temp = show_list(ohci, buf->page, size, ohci->ed_controltail);
	temp += show_list(ohci, buf->page + temp, size - temp,
			  ohci->ed_bulktail);
	spin_unlock_irqrestore (&ohci->lock, flags);

	वापस temp;
पूर्ण

#घोषणा DBG_SCHED_LIMIT 64

अटल sमाप_प्रकार fill_periodic_buffer(काष्ठा debug_buffer *buf)
अणु
	काष्ठा ohci_hcd		*ohci;
	काष्ठा ed		**seen, *ed;
	अचिन्हित दीर्घ		flags;
	अचिन्हित		temp, size, seen_count;
	अक्षर			*next;
	अचिन्हित		i;

	seen = kदो_स्मृति_array(DBG_SCHED_LIMIT, माप(*seen), GFP_ATOMIC);
	अगर (!seen)
		वापस 0;
	seen_count = 0;

	ohci = buf->ohci;
	next = buf->page;
	size = PAGE_SIZE;

	temp = scnम_लिखो (next, size, "size = %d\n", NUM_INTS);
	size -= temp;
	next += temp;

	/* dump a snapshot of the periodic schedule (and load) */
	spin_lock_irqsave (&ohci->lock, flags);
	क्रम (i = 0; i < NUM_INTS; i++) अणु
		ed = ohci->periodic[i];
		अगर (!ed)
			जारी;

		temp = scnम_लिखो (next, size, "%2d [%3d]:", i, ohci->load [i]);
		size -= temp;
		next += temp;

		करो अणु
			temp = scnम_लिखो (next, size, " ed%d/%p",
				ed->पूर्णांकerval, ed);
			size -= temp;
			next += temp;
			क्रम (temp = 0; temp < seen_count; temp++) अणु
				अगर (seen [temp] == ed)
					अवरोध;
			पूर्ण

			/* show more info the first समय around */
			अगर (temp == seen_count) अणु
				u32	info = hc32_to_cpu (ohci, ed->hwINFO);
				काष्ठा list_head	*entry;
				अचिन्हित		qlen = 0;

				/* qlen measured here in TDs, not urbs */
				list_क्रम_each (entry, &ed->td_list)
					qlen++;

				temp = scnम_लिखो (next, size,
					" (%cs dev%d ep%d%s-%s qlen %u"
					" max %d %08x%s%s)",
					(info & ED_LOWSPEED) ? 'l' : 'f',
					info & 0x7f,
					(info >> 7) & 0xf,
					(info & ED_IN) ? "in" : "out",
					(info & ED_ISO) ? "iso" : "int",
					qlen,
					0x03ff & (info >> 16),
					info,
					(info & ED_SKIP) ? " K" : "",
					(ed->hwHeadP &
						cpu_to_hc32(ohci, ED_H)) ?
							" H" : "");
				size -= temp;
				next += temp;

				अगर (seen_count < DBG_SCHED_LIMIT)
					seen [seen_count++] = ed;

				ed = ed->ed_next;

			पूर्ण अन्यथा अणु
				/* we've seen it and what's after */
				temp = 0;
				ed = शून्य;
			पूर्ण

		पूर्ण जबतक (ed);

		temp = scnम_लिखो (next, size, "\n");
		size -= temp;
		next += temp;
	पूर्ण
	spin_unlock_irqrestore (&ohci->lock, flags);
	kमुक्त (seen);

	वापस PAGE_SIZE - size;
पूर्ण
#अघोषित DBG_SCHED_LIMIT

अटल sमाप_प्रकार fill_रेजिस्टरs_buffer(काष्ठा debug_buffer *buf)
अणु
	काष्ठा usb_hcd		*hcd;
	काष्ठा ohci_hcd		*ohci;
	काष्ठा ohci_regs __iomem *regs;
	अचिन्हित दीर्घ		flags;
	अचिन्हित		temp, size;
	अक्षर			*next;
	u32			rdata;

	ohci = buf->ohci;
	hcd = ohci_to_hcd(ohci);
	regs = ohci->regs;
	next = buf->page;
	size = PAGE_SIZE;

	spin_lock_irqsave (&ohci->lock, flags);

	/* dump driver info, then रेजिस्टरs in spec order */

	ohci_dbg_nosw(ohci, &next, &size,
		"bus %s, device %s\n"
		"%s\n"
		"%s\n",
		hcd->self.controller->bus->name,
		dev_name(hcd->self.controller),
		hcd->product_desc,
		hcd_name);

	अगर (!HCD_HW_ACCESSIBLE(hcd)) अणु
		size -= scnम_लिखो (next, size,
			"SUSPENDED (no register access)\n");
		जाओ करोne;
	पूर्ण

	ohci_dump_status(ohci, &next, &size);

	/* hcca */
	अगर (ohci->hcca)
		ohci_dbg_nosw(ohci, &next, &size,
			"hcca frame 0x%04x\n", ohci_frame_no(ohci));

	/* other रेजिस्टरs mostly affect frame timings */
	rdata = ohci_पढ़ोl (ohci, &regs->fmपूर्णांकerval);
	temp = scnम_लिखो (next, size,
			"fmintvl 0x%08x %sFSMPS=0x%04x FI=0x%04x\n",
			rdata, (rdata >> 31) ? "FIT " : "",
			(rdata >> 16) & 0xefff, rdata & 0xffff);
	size -= temp;
	next += temp;

	rdata = ohci_पढ़ोl (ohci, &regs->fmreमुख्यing);
	temp = scnम_लिखो (next, size, "fmremaining 0x%08x %sFR=0x%04x\n",
			rdata, (rdata >> 31) ? "FRT " : "",
			rdata & 0x3fff);
	size -= temp;
	next += temp;

	rdata = ohci_पढ़ोl (ohci, &regs->periodicstart);
	temp = scnम_लिखो (next, size, "periodicstart 0x%04x\n",
			rdata & 0x3fff);
	size -= temp;
	next += temp;

	rdata = ohci_पढ़ोl (ohci, &regs->lsthresh);
	temp = scnम_लिखो (next, size, "lsthresh 0x%04x\n",
			rdata & 0x3fff);
	size -= temp;
	next += temp;

	temp = scnम_लिखो (next, size, "hub poll timer %s\n",
			HCD_POLL_RH(ohci_to_hcd(ohci)) ? "ON" : "off");
	size -= temp;
	next += temp;

	/* roothub */
	ohci_dump_roothub (ohci, 1, &next, &size);

करोne:
	spin_unlock_irqrestore (&ohci->lock, flags);

	वापस PAGE_SIZE - size;
पूर्ण

अटल काष्ठा debug_buffer *alloc_buffer(काष्ठा ohci_hcd *ohci,
				sमाप_प्रकार (*fill_func)(काष्ठा debug_buffer *))
अणु
	काष्ठा debug_buffer *buf;

	buf = kzalloc(माप(काष्ठा debug_buffer), GFP_KERNEL);

	अगर (buf) अणु
		buf->ohci = ohci;
		buf->fill_func = fill_func;
		mutex_init(&buf->mutex);
	पूर्ण

	वापस buf;
पूर्ण

अटल पूर्णांक fill_buffer(काष्ठा debug_buffer *buf)
अणु
	पूर्णांक ret = 0;

	अगर (!buf->page)
		buf->page = (अक्षर *)get_zeroed_page(GFP_KERNEL);

	अगर (!buf->page) अणु
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
				      buf->page, buf->count);

out:
	वापस ret;

पूर्ण

अटल पूर्णांक debug_बंद(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा debug_buffer *buf = file->निजी_data;

	अगर (buf) अणु
		अगर (buf->page)
			मुक्त_page((अचिन्हित दीर्घ)buf->page);
		kमुक्त(buf);
	पूर्ण

	वापस 0;
पूर्ण
अटल पूर्णांक debug_async_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	file->निजी_data = alloc_buffer(inode->i_निजी, fill_async_buffer);

	वापस file->निजी_data ? 0 : -ENOMEM;
पूर्ण

अटल पूर्णांक debug_periodic_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	file->निजी_data = alloc_buffer(inode->i_निजी,
					  fill_periodic_buffer);

	वापस file->निजी_data ? 0 : -ENOMEM;
पूर्ण

अटल पूर्णांक debug_रेजिस्टरs_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	file->निजी_data = alloc_buffer(inode->i_निजी,
					  fill_रेजिस्टरs_buffer);

	वापस file->निजी_data ? 0 : -ENOMEM;
पूर्ण
अटल अंतरभूत व्योम create_debug_files (काष्ठा ohci_hcd *ohci)
अणु
	काष्ठा usb_bus *bus = &ohci_to_hcd(ohci)->self;
	काष्ठा dentry *root;

	root = debugfs_create_dir(bus->bus_name, ohci_debug_root);
	ohci->debug_dir = root;

	debugfs_create_file("async", S_IRUGO, root, ohci, &debug_async_fops);
	debugfs_create_file("periodic", S_IRUGO, root, ohci,
			    &debug_periodic_fops);
	debugfs_create_file("registers", S_IRUGO, root, ohci,
			    &debug_रेजिस्टरs_fops);

	ohci_dbg (ohci, "created debug files\n");
पूर्ण

अटल अंतरभूत व्योम हटाओ_debug_files (काष्ठा ohci_hcd *ohci)
अणु
	debugfs_हटाओ_recursive(ohci->debug_dir);
पूर्ण

/*-------------------------------------------------------------------------*/

