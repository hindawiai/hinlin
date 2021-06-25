<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * UHCI-specअगरic debugging code. Invaluable when something
 * goes wrong, but करोn't get in my face.
 *
 * Kernel visible poपूर्णांकers are surrounded in []s and bus
 * visible poपूर्णांकers are surrounded in ()s
 *
 * (C) Copyright 1999 Linus Torvalds
 * (C) Copyright 1999-2001 Johannes Erdfelt
 */

#समावेश <linux/slab.h>
#समावेश <linux/kernel.h>
#समावेश <linux/debugfs.h>
#समावेश <यंत्र/पन.स>

#समावेश "uhci-hcd.h"

#घोषणा EXTRA_SPACE	1024

अटल काष्ठा dentry *uhci_debugfs_root;

#अगर_घोषित CONFIG_DYNAMIC_DEBUG

/* Handle REALLY large prपूर्णांकks so we करोn't overflow buffers */
अटल व्योम lprपूर्णांकk(अक्षर *buf)
अणु
	अक्षर *p;

	/* Just ग_लिखो one line at a समय */
	जबतक (buf) अणु
		p = म_अक्षर(buf, '\n');
		अगर (p)
			*p = 0;
		prपूर्णांकk(KERN_DEBUG "%s\n", buf);
		buf = p;
		अगर (buf)
			buf++;
	पूर्ण
पूर्ण

अटल पूर्णांक uhci_show_td(काष्ठा uhci_hcd *uhci, काष्ठा uhci_td *td, अक्षर *buf,
			पूर्णांक len, पूर्णांक space)
अणु
	अक्षर *out = buf;
	अक्षर *spid;
	u32 status, token;

	status = td_status(uhci, td);
	out += प्र_लिखो(out, "%*s[%p] link (%08x) ", space, "", td,
		hc32_to_cpu(uhci, td->link));
	out += प्र_लिखो(out, "e%d %s%s%s%s%s%s%s%s%s%sLength=%x ",
		((status >> 27) & 3),
		(status & TD_CTRL_SPD) ?      "SPD " : "",
		(status & TD_CTRL_LS) ?       "LS " : "",
		(status & TD_CTRL_IOC) ?      "IOC " : "",
		(status & TD_CTRL_ACTIVE) ?   "Active " : "",
		(status & TD_CTRL_STALLED) ?  "Stalled " : "",
		(status & TD_CTRL_DBUFERR) ?  "DataBufErr " : "",
		(status & TD_CTRL_BABBLE) ?   "Babble " : "",
		(status & TD_CTRL_NAK) ?      "NAK " : "",
		(status & TD_CTRL_CRCTIMEO) ? "CRC/Timeo " : "",
		(status & TD_CTRL_BITSTUFF) ? "BitStuff " : "",
		status & 0x7ff);
	अगर (out - buf > len)
		जाओ करोne;

	token = td_token(uhci, td);
	चयन (uhci_packetid(token)) अणु
		हाल USB_PID_SETUP:
			spid = "SETUP";
			अवरोध;
		हाल USB_PID_OUT:
			spid = "OUT";
			अवरोध;
		हाल USB_PID_IN:
			spid = "IN";
			अवरोध;
		शेष:
			spid = "?";
			अवरोध;
	पूर्ण

	out += प्र_लिखो(out, "MaxLen=%x DT%d EndPt=%x Dev=%x, PID=%x(%s) ",
		token >> 21,
		((token >> 19) & 1),
		(token >> 15) & 15,
		(token >> 8) & 127,
		(token & 0xff),
		spid);
	out += प्र_लिखो(out, "(buf=%08x)\n", hc32_to_cpu(uhci, td->buffer));

करोne:
	अगर (out - buf > len)
		out += प्र_लिखो(out, " ...\n");
	वापस out - buf;
पूर्ण

अटल पूर्णांक uhci_show_urbp(काष्ठा uhci_hcd *uhci, काष्ठा urb_priv *urbp,
			अक्षर *buf, पूर्णांक len, पूर्णांक space)
अणु
	अक्षर *out = buf;
	काष्ठा uhci_td *td;
	पूर्णांक i, nactive, ninactive;
	अक्षर *ptype;


	out += प्र_लिखो(out, "urb_priv [%p] ", urbp);
	out += प्र_लिखो(out, "urb [%p] ", urbp->urb);
	out += प्र_लिखो(out, "qh [%p] ", urbp->qh);
	out += प्र_लिखो(out, "Dev=%d ", usb_pipedevice(urbp->urb->pipe));
	out += प्र_लिखो(out, "EP=%x(%s) ", usb_pipeendpoपूर्णांक(urbp->urb->pipe),
			(usb_pipein(urbp->urb->pipe) ? "IN" : "OUT"));
	अगर (out - buf > len)
		जाओ करोne;

	चयन (usb_pipetype(urbp->urb->pipe)) अणु
	हाल PIPE_ISOCHRONOUS: ptype = "ISO"; अवरोध;
	हाल PIPE_INTERRUPT: ptype = "INT"; अवरोध;
	हाल PIPE_BULK: ptype = "BLK"; अवरोध;
	शेष:
	हाल PIPE_CONTROL: ptype = "CTL"; अवरोध;
	पूर्ण

	out += प्र_लिखो(out, "%s%s", ptype, (urbp->fsbr ? " FSBR" : ""));
	out += प्र_लिखो(out, " Actlen=%d%s", urbp->urb->actual_length,
			(urbp->qh->type == USB_ENDPOINT_XFER_CONTROL ?
				"-8" : ""));

	अगर (urbp->urb->unlinked)
		out += प्र_लिखो(out, " Unlinked=%d", urbp->urb->unlinked);
	out += प्र_लिखो(out, "\n");

	अगर (out - buf > len)
		जाओ करोne;

	i = nactive = ninactive = 0;
	list_क्रम_each_entry(td, &urbp->td_list, list) अणु
		अगर (urbp->qh->type != USB_ENDPOINT_XFER_ISOC &&
				(++i <= 10 || debug > 2)) अणु
			out += प्र_लिखो(out, "%*s%d: ", space + 2, "", i);
			out += uhci_show_td(uhci, td, out,
					len - (out - buf), 0);
			अगर (out - buf > len)
				जाओ tail;
		पूर्ण अन्यथा अणु
			अगर (td_status(uhci, td) & TD_CTRL_ACTIVE)
				++nactive;
			अन्यथा
				++ninactive;
		पूर्ण
	पूर्ण
	अगर (nactive + ninactive > 0)
		out += प्र_लिखो(out,
				"%*s[skipped %d inactive and %d active TDs]\n",
				space, "", ninactive, nactive);
करोne:
	अगर (out - buf > len)
		out += प्र_लिखो(out, " ...\n");
tail:
	वापस out - buf;
पूर्ण

अटल पूर्णांक uhci_show_qh(काष्ठा uhci_hcd *uhci,
		काष्ठा uhci_qh *qh, अक्षर *buf, पूर्णांक len, पूर्णांक space)
अणु
	अक्षर *out = buf;
	पूर्णांक i, nurbs;
	__hc32 element = qh_element(qh);
	अक्षर *qtype;

	चयन (qh->type) अणु
	हाल USB_ENDPOINT_XFER_ISOC: qtype = "ISO"; अवरोध;
	हाल USB_ENDPOINT_XFER_INT: qtype = "INT"; अवरोध;
	हाल USB_ENDPOINT_XFER_BULK: qtype = "BLK"; अवरोध;
	हाल USB_ENDPOINT_XFER_CONTROL: qtype = "CTL"; अवरोध;
	शेष: qtype = "Skel" ; अवरोध;
	पूर्ण

	out += प्र_लिखो(out, "%*s[%p] %s QH link (%08x) element (%08x)\n",
			space, "", qh, qtype,
			hc32_to_cpu(uhci, qh->link),
			hc32_to_cpu(uhci, element));
	अगर (qh->type == USB_ENDPOINT_XFER_ISOC)
		out += प्र_लिखो(out,
				"%*s    period %d phase %d load %d us, frame %x desc [%p]\n",
				space, "", qh->period, qh->phase, qh->load,
				qh->iso_frame, qh->iso_packet_desc);
	अन्यथा अगर (qh->type == USB_ENDPOINT_XFER_INT)
		out += प्र_लिखो(out, "%*s    period %d phase %d load %d us\n",
				space, "", qh->period, qh->phase, qh->load);
	अगर (out - buf > len)
		जाओ करोne;

	अगर (element & UHCI_PTR_QH(uhci))
		out += प्र_लिखो(out, "%*s  Element points to QH (bug?)\n", space, "");

	अगर (element & UHCI_PTR_DEPTH(uhci))
		out += प्र_लिखो(out, "%*s  Depth traverse\n", space, "");

	अगर (element & cpu_to_hc32(uhci, 8))
		out += प्र_लिखो(out, "%*s  Bit 3 set (bug?)\n", space, "");

	अगर (!(element & ~(UHCI_PTR_QH(uhci) | UHCI_PTR_DEPTH(uhci))))
		out += प्र_लिखो(out, "%*s  Element is NULL (bug?)\n", space, "");

	अगर (out - buf > len)
		जाओ करोne;

	अगर (list_empty(&qh->queue)) अणु
		out += प्र_लिखो(out, "%*s  queue is empty\n", space, "");
		अगर (qh == uhci->skel_async_qh) अणु
			out += uhci_show_td(uhci, uhci->term_td, out,
					len - (out - buf), 0);
			अगर (out - buf > len)
				जाओ tail;
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा urb_priv *urbp = list_entry(qh->queue.next,
				काष्ठा urb_priv, node);
		काष्ठा uhci_td *td = list_entry(urbp->td_list.next,
				काष्ठा uhci_td, list);

		अगर (element != LINK_TO_TD(uhci, td))
			out += प्र_लिखो(out, "%*s Element != First TD\n",
					space, "");
		i = nurbs = 0;
		list_क्रम_each_entry(urbp, &qh->queue, node) अणु
			अगर (++i <= 10) अणु
				out += uhci_show_urbp(uhci, urbp, out,
						len - (out - buf), space + 2);
				अगर (out - buf > len)
					जाओ tail;
			पूर्ण
			अन्यथा
				++nurbs;
		पूर्ण
		अगर (nurbs > 0)
			out += प्र_लिखो(out, "%*s Skipped %d URBs\n",
					space, "", nurbs);
	पूर्ण

	अगर (out - buf > len)
		जाओ करोne;

	अगर (qh->dummy_td) अणु
		out += प्र_लिखो(out, "%*s  Dummy TD\n", space, "");
		out += uhci_show_td(uhci, qh->dummy_td, out,
				len - (out - buf), 0);
		अगर (out - buf > len)
			जाओ tail;
	पूर्ण

करोne:
	अगर (out - buf > len)
		out += प्र_लिखो(out, " ...\n");
tail:
	वापस out - buf;
पूर्ण

अटल पूर्णांक uhci_show_sc(पूर्णांक port, अचिन्हित लघु status, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "  stat%d     =     %04x  %s%s%s%s%s%s%s%s%s%s\n",
		port,
		status,
		(status & USBPORTSC_SUSP) ?	" Suspend" : "",
		(status & USBPORTSC_OCC) ?	" OverCurrentChange" : "",
		(status & USBPORTSC_OC) ?	" OverCurrent" : "",
		(status & USBPORTSC_PR) ?	" Reset" : "",
		(status & USBPORTSC_LSDA) ?	" LowSpeed" : "",
		(status & USBPORTSC_RD) ?	" ResumeDetect" : "",
		(status & USBPORTSC_PEC) ?	" EnableChange" : "",
		(status & USBPORTSC_PE) ?	" Enabled" : "",
		(status & USBPORTSC_CSC) ?	" ConnectChange" : "",
		(status & USBPORTSC_CCS) ?	" Connected" : "");
पूर्ण

अटल पूर्णांक uhci_show_root_hub_state(काष्ठा uhci_hcd *uhci, अक्षर *buf)
अणु
	अक्षर *rh_state;

	चयन (uhci->rh_state) अणु
	    हाल UHCI_RH_RESET:
		rh_state = "reset";		अवरोध;
	    हाल UHCI_RH_SUSPENDED:
		rh_state = "suspended";		अवरोध;
	    हाल UHCI_RH_AUTO_STOPPED:
		rh_state = "auto-stopped";	अवरोध;
	    हाल UHCI_RH_RESUMING:
		rh_state = "resuming";		अवरोध;
	    हाल UHCI_RH_SUSPENDING:
		rh_state = "suspending";	अवरोध;
	    हाल UHCI_RH_RUNNING:
		rh_state = "running";		अवरोध;
	    हाल UHCI_RH_RUNNING_NODEVS:
		rh_state = "running, no devs";	अवरोध;
	    शेष:
		rh_state = "?";			अवरोध;
	पूर्ण
	वापस प्र_लिखो(buf, "Root-hub state: %s   FSBR: %d\n",
			rh_state, uhci->fsbr_is_on);
पूर्ण

अटल पूर्णांक uhci_show_status(काष्ठा uhci_hcd *uhci, अक्षर *buf, पूर्णांक len)
अणु
	अक्षर *out = buf;
	अचिन्हित लघु usbcmd, usbstat, usbपूर्णांक, usbfrnum;
	अचिन्हित पूर्णांक flbaseadd;
	अचिन्हित अक्षर sof;
	अचिन्हित लघु portsc1, portsc2;


	usbcmd    = uhci_पढ़ोw(uhci, USBCMD);
	usbstat   = uhci_पढ़ोw(uhci, USBSTS);
	usbपूर्णांक    = uhci_पढ़ोw(uhci, USBINTR);
	usbfrnum  = uhci_पढ़ोw(uhci, USBFRNUM);
	flbaseadd = uhci_पढ़ोl(uhci, USBFLBASEADD);
	sof       = uhci_पढ़ोb(uhci, USBSOF);
	portsc1   = uhci_पढ़ोw(uhci, USBPORTSC1);
	portsc2   = uhci_पढ़ोw(uhci, USBPORTSC2);

	out += प्र_लिखो(out, "  usbcmd    =     %04x   %s%s%s%s%s%s%s%s\n",
		usbcmd,
		(usbcmd & USBCMD_MAXP) ?    "Maxp64 " : "Maxp32 ",
		(usbcmd & USBCMD_CF) ?      "CF " : "",
		(usbcmd & USBCMD_SWDBG) ?   "SWDBG " : "",
		(usbcmd & USBCMD_FGR) ?     "FGR " : "",
		(usbcmd & USBCMD_EGSM) ?    "EGSM " : "",
		(usbcmd & USBCMD_GRESET) ?  "GRESET " : "",
		(usbcmd & USBCMD_HCRESET) ? "HCRESET " : "",
		(usbcmd & USBCMD_RS) ?      "RS " : "");
	अगर (out - buf > len)
		जाओ करोne;

	out += प्र_लिखो(out, "  usbstat   =     %04x   %s%s%s%s%s%s\n",
		usbstat,
		(usbstat & USBSTS_HCH) ?    "HCHalted " : "",
		(usbstat & USBSTS_HCPE) ?   "HostControllerProcessError " : "",
		(usbstat & USBSTS_HSE) ?    "HostSystemError " : "",
		(usbstat & USBSTS_RD) ?     "ResumeDetect " : "",
		(usbstat & USBSTS_ERROR) ?  "USBError " : "",
		(usbstat & USBSTS_USBINT) ? "USBINT " : "");
	अगर (out - buf > len)
		जाओ करोne;

	out += प्र_लिखो(out, "  usbint    =     %04x\n", usbपूर्णांक);
	out += प्र_लिखो(out, "  usbfrnum  =   (%d)%03x\n", (usbfrnum >> 10) & 1,
		0xfff & (4*(अचिन्हित पूर्णांक)usbfrnum));
	out += प्र_लिखो(out, "  flbaseadd = %08x\n", flbaseadd);
	out += प्र_लिखो(out, "  sof       =       %02x\n", sof);
	अगर (out - buf > len)
		जाओ करोne;

	out += uhci_show_sc(1, portsc1, out);
	अगर (out - buf > len)
		जाओ करोne;

	out += uhci_show_sc(2, portsc2, out);
	अगर (out - buf > len)
		जाओ करोne;

	out += प्र_लिखो(out,
			"Most recent frame: %x (%d)   Last ISO frame: %x (%d)\n",
			uhci->frame_number, uhci->frame_number & 1023,
			uhci->last_iso_frame, uhci->last_iso_frame & 1023);

करोne:
	अगर (out - buf > len)
		out += प्र_लिखो(out, " ...\n");
	वापस out - buf;
पूर्ण

अटल पूर्णांक uhci_sprपूर्णांक_schedule(काष्ठा uhci_hcd *uhci, अक्षर *buf, पूर्णांक len)
अणु
	अक्षर *out = buf;
	पूर्णांक i, j;
	काष्ठा uhci_qh *qh;
	काष्ठा uhci_td *td;
	काष्ठा list_head *पंचांगp, *head;
	पूर्णांक nframes, nerrs;
	__hc32 link;
	__hc32 fsbr_link;

	अटल स्थिर अक्षर * स्थिर qh_names[] = अणु
		"unlink", "iso", "int128", "int64", "int32", "int16",
		"int8", "int4", "int2", "async", "term"
	पूर्ण;

	out += uhci_show_root_hub_state(uhci, out);
	अगर (out - buf > len)
		जाओ करोne;
	out += प्र_लिखो(out, "HC status\n");
	out += uhci_show_status(uhci, out, len - (out - buf));
	अगर (out - buf > len)
		जाओ tail;

	out += प्र_लिखो(out, "Periodic load table\n");
	क्रम (i = 0; i < MAX_PHASE; ++i) अणु
		out += प्र_लिखो(out, "\t%d", uhci->load[i]);
		अगर (i % 8 == 7)
			*out++ = '\n';
	पूर्ण
	out += प्र_लिखो(out, "Total: %d, #INT: %d, #ISO: %d\n",
			uhci->total_load,
			uhci_to_hcd(uhci)->self.bandwidth_पूर्णांक_reqs,
			uhci_to_hcd(uhci)->self.bandwidth_isoc_reqs);
	अगर (debug <= 1)
		जाओ tail;

	out += प्र_लिखो(out, "Frame List\n");
	nframes = 10;
	nerrs = 0;
	क्रम (i = 0; i < UHCI_NUMFRAMES; ++i) अणु
		__hc32 qh_dma;

		अगर (out - buf > len)
			जाओ करोne;
		j = 0;
		td = uhci->frame_cpu[i];
		link = uhci->frame[i];
		अगर (!td)
			जाओ check_link;

		अगर (nframes > 0) अणु
			out += प्र_लिखो(out, "- Frame %d -> (%08x)\n",
					i, hc32_to_cpu(uhci, link));
			j = 1;
		पूर्ण

		head = &td->fl_list;
		पंचांगp = head;
		करो अणु
			td = list_entry(पंचांगp, काष्ठा uhci_td, fl_list);
			पंचांगp = पंचांगp->next;
			अगर (link != LINK_TO_TD(uhci, td)) अणु
				अगर (nframes > 0) अणु
					out += प्र_लिखो(out,
						"    link does not match list entry!\n");
					अगर (out - buf > len)
						जाओ करोne;
				पूर्ण अन्यथा
					++nerrs;
			पूर्ण
			अगर (nframes > 0) अणु
				out += uhci_show_td(uhci, td, out,
						len - (out - buf), 4);
				अगर (out - buf > len)
					जाओ tail;
			पूर्ण
			link = td->link;
		पूर्ण जबतक (पंचांगp != head);

check_link:
		qh_dma = uhci_frame_skel_link(uhci, i);
		अगर (link != qh_dma) अणु
			अगर (nframes > 0) अणु
				अगर (!j) अणु
					out += प्र_लिखो(out,
						"- Frame %d -> (%08x)\n",
						i, hc32_to_cpu(uhci, link));
					j = 1;
				पूर्ण
				out += प्र_लिखो(out,
					"   link does not match QH (%08x)!\n",
					hc32_to_cpu(uhci, qh_dma));
				अगर (out - buf > len)
					जाओ करोne;
			पूर्ण अन्यथा
				++nerrs;
		पूर्ण
		nframes -= j;
	पूर्ण
	अगर (nerrs > 0)
		out += प्र_लिखो(out, "Skipped %d bad links\n", nerrs);

	out += प्र_लिखो(out, "Skeleton QHs\n");

	अगर (out - buf > len)
		जाओ करोne;

	fsbr_link = 0;
	क्रम (i = 0; i < UHCI_NUM_SKELQH; ++i) अणु
		पूर्णांक cnt = 0;

		qh = uhci->skelqh[i];
		out += प्र_लिखो(out, "- skel_%s_qh\n", qh_names[i]);
		out += uhci_show_qh(uhci, qh, out, len - (out - buf), 4);
		अगर (out - buf > len)
			जाओ tail;

		/* Last QH is the Terminating QH, it's dअगरferent */
		अगर (i == SKEL_TERM) अणु
			अगर (qh_element(qh) != LINK_TO_TD(uhci, uhci->term_td)) अणु
				out += प्र_लिखो(out,
					"    skel_term_qh element is not set to term_td!\n");
				अगर (out - buf > len)
					जाओ करोne;
			पूर्ण
			link = fsbr_link;
			अगर (!link)
				link = LINK_TO_QH(uhci, uhci->skel_term_qh);
			जाओ check_qh_link;
		पूर्ण

		head = &qh->node;
		पंचांगp = head->next;

		जबतक (पंचांगp != head) अणु
			qh = list_entry(पंचांगp, काष्ठा uhci_qh, node);
			पंचांगp = पंचांगp->next;
			अगर (++cnt <= 10) अणु
				out += uhci_show_qh(uhci, qh, out,
						len - (out - buf), 4);
				अगर (out - buf > len)
					जाओ tail;
			पूर्ण
			अगर (!fsbr_link && qh->skel >= SKEL_FSBR)
				fsbr_link = LINK_TO_QH(uhci, qh);
		पूर्ण
		अगर ((cnt -= 10) > 0)
			out += प्र_लिखो(out, "    Skipped %d QHs\n", cnt);

		link = UHCI_PTR_TERM(uhci);
		अगर (i <= SKEL_ISO)
			;
		अन्यथा अगर (i < SKEL_ASYNC)
			link = LINK_TO_QH(uhci, uhci->skel_async_qh);
		अन्यथा अगर (!uhci->fsbr_is_on)
			;
		अन्यथा
			link = LINK_TO_QH(uhci, uhci->skel_term_qh);
check_qh_link:
		अगर (qh->link != link)
			out += प्र_लिखो(out,
				"    last QH not linked to next skeleton!\n");

		अगर (out - buf > len)
			जाओ करोne;
	पूर्ण

करोne:
	अगर (out - buf > len)
		out += प्र_लिखो(out, " ...\n");
tail:
	वापस out - buf;
पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS

#घोषणा MAX_OUTPUT	(64 * 1024)

काष्ठा uhci_debug अणु
	पूर्णांक size;
	अक्षर *data;
पूर्ण;

अटल पूर्णांक uhci_debug_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा uhci_hcd *uhci = inode->i_निजी;
	काष्ठा uhci_debug *up;
	अचिन्हित दीर्घ flags;

	up = kदो_स्मृति(माप(*up), GFP_KERNEL);
	अगर (!up)
		वापस -ENOMEM;

	up->data = kदो_स्मृति(MAX_OUTPUT, GFP_KERNEL);
	अगर (!up->data) अणु
		kमुक्त(up);
		वापस -ENOMEM;
	पूर्ण

	up->size = 0;
	spin_lock_irqsave(&uhci->lock, flags);
	अगर (uhci->is_initialized)
		up->size = uhci_sprपूर्णांक_schedule(uhci, up->data,
					MAX_OUTPUT - EXTRA_SPACE);
	spin_unlock_irqrestore(&uhci->lock, flags);

	file->निजी_data = up;

	वापस 0;
पूर्ण

अटल loff_t uhci_debug_lseek(काष्ठा file *file, loff_t off, पूर्णांक whence)
अणु
	काष्ठा uhci_debug *up = file->निजी_data;
	वापस no_seek_end_llseek_size(file, off, whence, up->size);
पूर्ण

अटल sमाप_प्रकार uhci_debug_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
				माप_प्रकार nbytes, loff_t *ppos)
अणु
	काष्ठा uhci_debug *up = file->निजी_data;
	वापस simple_पढ़ो_from_buffer(buf, nbytes, ppos, up->data, up->size);
पूर्ण

अटल पूर्णांक uhci_debug_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा uhci_debug *up = file->निजी_data;

	kमुक्त(up->data);
	kमुक्त(up);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations uhci_debug_operations = अणु
	.owner =	THIS_MODULE,
	.खोलो =		uhci_debug_खोलो,
	.llseek =	uhci_debug_lseek,
	.पढ़ो =		uhci_debug_पढ़ो,
	.release =	uhci_debug_release,
पूर्ण;
#घोषणा UHCI_DEBUG_OPS

#पूर्ण_अगर	/* CONFIG_DEBUG_FS */

#अन्यथा	/* CONFIG_DYNAMIC_DEBUG*/

अटल अंतरभूत व्योम lprपूर्णांकk(अक्षर *buf)
अणुपूर्ण

अटल अंतरभूत पूर्णांक uhci_show_qh(काष्ठा uhci_hcd *uhci,
		काष्ठा uhci_qh *qh, अक्षर *buf, पूर्णांक len, पूर्णांक space)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक uhci_sprपूर्णांक_schedule(काष्ठा uhci_hcd *uhci,
		अक्षर *buf, पूर्णांक len)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर
