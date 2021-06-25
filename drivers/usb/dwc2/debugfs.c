<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * debugfs.c - Designware USB2 DRD controller debugfs
 *
 * Copyright (C) 2015 Intel Corporation
 * Mian Yousaf Kaukab <yousaf.kaukab@पूर्णांकel.com>
 */

#समावेश <linux/spinlock.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/uaccess.h>

#समावेश "core.h"
#समावेश "debug.h"

#अगर IS_ENABLED(CONFIG_USB_DWC2_PERIPHERAL) || \
	IS_ENABLED(CONFIG_USB_DWC2_DUAL_ROLE)

/**
 * tesपंचांगode_ग_लिखो() - change usb test mode state.
 * @file: The  file to ग_लिखो to.
 * @ubuf: The buffer where user wrote.
 * @count: The ubuf size.
 * @ppos: Unused parameter.
 */
अटल sमाप_प्रकार tesपंचांगode_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *ubuf, माप_प्रकार
		count, loff_t *ppos)
अणु
	काष्ठा seq_file		*s = file->निजी_data;
	काष्ठा dwc2_hsotg	*hsotg = s->निजी;
	अचिन्हित दीर्घ		flags;
	u32			tesपंचांगode = 0;
	अक्षर			buf[32];

	अगर (copy_from_user(&buf, ubuf, min_t(माप_प्रकार, माप(buf) - 1, count)))
		वापस -EFAULT;

	अगर (!म_भेदन(buf, "test_j", 6))
		tesपंचांगode = USB_TEST_J;
	अन्यथा अगर (!म_भेदन(buf, "test_k", 6))
		tesपंचांगode = USB_TEST_K;
	अन्यथा अगर (!म_भेदन(buf, "test_se0_nak", 12))
		tesपंचांगode = USB_TEST_SE0_NAK;
	अन्यथा अगर (!म_भेदन(buf, "test_packet", 11))
		tesपंचांगode = USB_TEST_PACKET;
	अन्यथा अगर (!म_भेदन(buf, "test_force_enable", 17))
		tesपंचांगode = USB_TEST_FORCE_ENABLE;
	अन्यथा
		tesपंचांगode = 0;

	spin_lock_irqsave(&hsotg->lock, flags);
	dwc2_hsotg_set_test_mode(hsotg, tesपंचांगode);
	spin_unlock_irqrestore(&hsotg->lock, flags);
	वापस count;
पूर्ण

/**
 * tesपंचांगode_show() - debugfs: show usb test mode state
 * @s: The seq file to ग_लिखो to.
 * @unused: Unused parameter.
 *
 * This debugfs entry shows which usb test mode is currently enabled.
 */
अटल पूर्णांक tesपंचांगode_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा dwc2_hsotg *hsotg = s->निजी;
	अचिन्हित दीर्घ flags;
	पूर्णांक dctl;

	spin_lock_irqsave(&hsotg->lock, flags);
	dctl = dwc2_पढ़ोl(hsotg, DCTL);
	dctl &= DCTL_TSTCTL_MASK;
	dctl >>= DCTL_TSTCTL_SHIFT;
	spin_unlock_irqrestore(&hsotg->lock, flags);

	चयन (dctl) अणु
	हाल 0:
		seq_माला_दो(s, "no test\n");
		अवरोध;
	हाल USB_TEST_J:
		seq_माला_दो(s, "test_j\n");
		अवरोध;
	हाल USB_TEST_K:
		seq_माला_दो(s, "test_k\n");
		अवरोध;
	हाल USB_TEST_SE0_NAK:
		seq_माला_दो(s, "test_se0_nak\n");
		अवरोध;
	हाल USB_TEST_PACKET:
		seq_माला_दो(s, "test_packet\n");
		अवरोध;
	हाल USB_TEST_FORCE_ENABLE:
		seq_माला_दो(s, "test_force_enable\n");
		अवरोध;
	शेष:
		seq_म_लिखो(s, "UNKNOWN %d\n", dctl);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tesपंचांगode_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, tesपंचांगode_show, inode->i_निजी);
पूर्ण

अटल स्थिर काष्ठा file_operations tesपंचांगode_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= tesपंचांगode_खोलो,
	.ग_लिखो		= tesपंचांगode_ग_लिखो,
	.पढ़ो		= seq_पढ़ो,
	.llseek		= seq_lseek,
	.release	= single_release,
पूर्ण;

/**
 * state_show - debugfs: show overall driver and device state.
 * @seq: The seq file to ग_लिखो to.
 * @v: Unused parameter.
 *
 * This debugfs entry shows the overall state of the hardware and
 * some general inक्रमmation about each of the endpoपूर्णांकs available
 * to the प्रणाली.
 */
अटल पूर्णांक state_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा dwc2_hsotg *hsotg = seq->निजी;
	पूर्णांक idx;

	seq_म_लिखो(seq, "DCFG=0x%08x, DCTL=0x%08x, DSTS=0x%08x\n",
		   dwc2_पढ़ोl(hsotg, DCFG),
		 dwc2_पढ़ोl(hsotg, DCTL),
		 dwc2_पढ़ोl(hsotg, DSTS));

	seq_म_लिखो(seq, "DIEPMSK=0x%08x, DOEPMASK=0x%08x\n",
		   dwc2_पढ़ोl(hsotg, DIEPMSK), dwc2_पढ़ोl(hsotg, DOEPMSK));

	seq_म_लिखो(seq, "GINTMSK=0x%08x, GINTSTS=0x%08x\n",
		   dwc2_पढ़ोl(hsotg, GINTMSK),
		   dwc2_पढ़ोl(hsotg, GINTSTS));

	seq_म_लिखो(seq, "DAINTMSK=0x%08x, DAINT=0x%08x\n",
		   dwc2_पढ़ोl(hsotg, DAINTMSK),
		   dwc2_पढ़ोl(hsotg, DAINT));

	seq_म_लिखो(seq, "GNPTXSTS=0x%08x, GRXSTSR=%08x\n",
		   dwc2_पढ़ोl(hsotg, GNPTXSTS),
		   dwc2_पढ़ोl(hsotg, GRXSTSR));

	seq_माला_दो(seq, "\nEndpoint status:\n");

	क्रम (idx = 0; idx < hsotg->num_of_eps; idx++) अणु
		u32 in, out;

		in = dwc2_पढ़ोl(hsotg, DIEPCTL(idx));
		out = dwc2_पढ़ोl(hsotg, DOEPCTL(idx));

		seq_म_लिखो(seq, "ep%d: DIEPCTL=0x%08x, DOEPCTL=0x%08x",
			   idx, in, out);

		in = dwc2_पढ़ोl(hsotg, DIEPTSIZ(idx));
		out = dwc2_पढ़ोl(hsotg, DOEPTSIZ(idx));

		seq_म_लिखो(seq, ", DIEPTSIZ=0x%08x, DOEPTSIZ=0x%08x",
			   in, out);

		seq_माला_दो(seq, "\n");
	पूर्ण

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(state);

/**
 * fअगरo_show - debugfs: show the fअगरo inक्रमmation
 * @seq: The seq_file to ग_लिखो data to.
 * @v: Unused parameter.
 *
 * Show the FIFO inक्रमmation क्रम the overall fअगरo and all the
 * periodic transmission FIFOs.
 */
अटल पूर्णांक fअगरo_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा dwc2_hsotg *hsotg = seq->निजी;
	पूर्णांक fअगरo_count = dwc2_hsotg_tx_fअगरo_count(hsotg);
	u32 val;
	पूर्णांक idx;

	seq_माला_दो(seq, "Non-periodic FIFOs:\n");
	seq_म_लिखो(seq, "RXFIFO: Size %d\n", dwc2_पढ़ोl(hsotg, GRXFSIZ));

	val = dwc2_पढ़ोl(hsotg, GNPTXFSIZ);
	seq_म_लिखो(seq, "NPTXFIFO: Size %d, Start 0x%08x\n",
		   val >> FIFOSIZE_DEPTH_SHIFT,
		   val & FIFOSIZE_STARTADDR_MASK);

	seq_माला_दो(seq, "\nPeriodic TXFIFOs:\n");

	क्रम (idx = 1; idx <= fअगरo_count; idx++) अणु
		val = dwc2_पढ़ोl(hsotg, DPTXFSIZN(idx));

		seq_म_लिखो(seq, "\tDPTXFIFO%2d: Size %d, Start 0x%08x\n", idx,
			   val >> FIFOSIZE_DEPTH_SHIFT,
			   val & FIFOSIZE_STARTADDR_MASK);
	पूर्ण

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(fअगरo);

अटल स्थिर अक्षर *decode_direction(पूर्णांक is_in)
अणु
	वापस is_in ? "in" : "out";
पूर्ण

/**
 * ep_show - debugfs: show the state of an endpoपूर्णांक.
 * @seq: The seq_file to ग_लिखो data to.
 * @v: Unused parameter.
 *
 * This debugfs entry shows the state of the given endpoपूर्णांक (one is
 * रेजिस्टरed क्रम each available).
 */
अटल पूर्णांक ep_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा dwc2_hsotg_ep *ep = seq->निजी;
	काष्ठा dwc2_hsotg *hsotg = ep->parent;
	काष्ठा dwc2_hsotg_req *req;
	पूर्णांक index = ep->index;
	पूर्णांक show_limit = 15;
	अचिन्हित दीर्घ flags;

	seq_म_लिखो(seq, "Endpoint index %d, named %s,  dir %s:\n",
		   ep->index, ep->ep.name, decode_direction(ep->dir_in));

	/* first show the रेजिस्टर state */

	seq_म_लिखो(seq, "\tDIEPCTL=0x%08x, DOEPCTL=0x%08x\n",
		   dwc2_पढ़ोl(hsotg, DIEPCTL(index)),
		   dwc2_पढ़ोl(hsotg, DOEPCTL(index)));

	seq_म_लिखो(seq, "\tDIEPDMA=0x%08x, DOEPDMA=0x%08x\n",
		   dwc2_पढ़ोl(hsotg, DIEPDMA(index)),
		   dwc2_पढ़ोl(hsotg, DOEPDMA(index)));

	seq_म_लिखो(seq, "\tDIEPINT=0x%08x, DOEPINT=0x%08x\n",
		   dwc2_पढ़ोl(hsotg, DIEPINT(index)),
		   dwc2_पढ़ोl(hsotg, DOEPINT(index)));

	seq_म_लिखो(seq, "\tDIEPTSIZ=0x%08x, DOEPTSIZ=0x%08x\n",
		   dwc2_पढ़ोl(hsotg, DIEPTSIZ(index)),
		   dwc2_पढ़ोl(hsotg, DOEPTSIZ(index)));

	seq_माला_दो(seq, "\n");
	seq_म_लिखो(seq, "mps %d\n", ep->ep.maxpacket);
	seq_म_लिखो(seq, "total_data=%ld\n", ep->total_data);

	seq_म_लिखो(seq, "request list (%p,%p):\n",
		   ep->queue.next, ep->queue.prev);

	spin_lock_irqsave(&hsotg->lock, flags);

	list_क्रम_each_entry(req, &ep->queue, queue) अणु
		अगर (--show_limit < 0) अणु
			seq_माला_दो(seq, "not showing more requests...\n");
			अवरोध;
		पूर्ण

		seq_म_लिखो(seq, "%c req %p: %d bytes @%p, ",
			   req == ep->req ? '*' : ' ',
			   req, req->req.length, req->req.buf);
		seq_म_लिखो(seq, "%d done, res %d\n",
			   req->req.actual, req->req.status);
	पूर्ण

	spin_unlock_irqrestore(&hsotg->lock, flags);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(ep);

/**
 * dwc2_hsotg_create_debug - create debugfs directory and files
 * @hsotg: The driver state
 *
 * Create the debugfs files to allow the user to get inक्रमmation
 * about the state of the प्रणाली. The directory name is created
 * with the same name as the device itself, in हाल we end up
 * with multiple blocks in future प्रणालीs.
 */
अटल व्योम dwc2_hsotg_create_debug(काष्ठा dwc2_hsotg *hsotg)
अणु
	काष्ठा dentry *root;
	अचिन्हित पूर्णांक epidx;

	root = hsotg->debug_root;

	/* create general state file */
	debugfs_create_file("state", 0444, root, hsotg, &state_fops);
	debugfs_create_file("testmode", 0644, root, hsotg, &tesपंचांगode_fops);
	debugfs_create_file("fifo", 0444, root, hsotg, &fअगरo_fops);

	/* Create one file क्रम each out endpoपूर्णांक */
	क्रम (epidx = 0; epidx < hsotg->num_of_eps; epidx++) अणु
		काष्ठा dwc2_hsotg_ep *ep;

		ep = hsotg->eps_out[epidx];
		अगर (ep)
			debugfs_create_file(ep->name, 0444, root, ep, &ep_fops);
	पूर्ण
	/* Create one file क्रम each in endpoपूर्णांक. EP0 is handled with out eps */
	क्रम (epidx = 1; epidx < hsotg->num_of_eps; epidx++) अणु
		काष्ठा dwc2_hsotg_ep *ep;

		ep = hsotg->eps_in[epidx];
		अगर (ep)
			debugfs_create_file(ep->name, 0444, root, ep, &ep_fops);
	पूर्ण
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम dwc2_hsotg_create_debug(काष्ठा dwc2_hsotg *hsotg) अणुपूर्ण
#पूर्ण_अगर

/* dwc2_hsotg_delete_debug is हटाओd as cleanup in करोne in dwc2_debugfs_निकास */

#घोषणा dump_रेजिस्टर(nm)	\
अणु				\
	.name	= #nm,		\
	.offset	= nm,		\
पूर्ण

अटल स्थिर काष्ठा debugfs_reg32 dwc2_regs[] = अणु
	/*
	 * Accessing रेजिस्टरs like this can trigger mode mismatch पूर्णांकerrupt.
	 * However, according to dwc2 databook, the रेजिस्टर access, in this
	 * हाल, is completed on the processor bus but is ignored by the core
	 * and करोes not affect its operation.
	 */
	dump_रेजिस्टर(GOTGCTL),
	dump_रेजिस्टर(GOTGINT),
	dump_रेजिस्टर(GAHBCFG),
	dump_रेजिस्टर(GUSBCFG),
	dump_रेजिस्टर(GRSTCTL),
	dump_रेजिस्टर(GINTSTS),
	dump_रेजिस्टर(GINTMSK),
	dump_रेजिस्टर(GRXSTSR),
	/* Omit GRXSTSP */
	dump_रेजिस्टर(GRXFSIZ),
	dump_रेजिस्टर(GNPTXFSIZ),
	dump_रेजिस्टर(GNPTXSTS),
	dump_रेजिस्टर(GI2CCTL),
	dump_रेजिस्टर(GPVNDCTL),
	dump_रेजिस्टर(GGPIO),
	dump_रेजिस्टर(GUID),
	dump_रेजिस्टर(GSNPSID),
	dump_रेजिस्टर(GHWCFG1),
	dump_रेजिस्टर(GHWCFG2),
	dump_रेजिस्टर(GHWCFG3),
	dump_रेजिस्टर(GHWCFG4),
	dump_रेजिस्टर(GLPMCFG),
	dump_रेजिस्टर(GPWRDN),
	dump_रेजिस्टर(GDFIFOCFG),
	dump_रेजिस्टर(ADPCTL),
	dump_रेजिस्टर(HPTXFSIZ),
	dump_रेजिस्टर(DPTXFSIZN(1)),
	dump_रेजिस्टर(DPTXFSIZN(2)),
	dump_रेजिस्टर(DPTXFSIZN(3)),
	dump_रेजिस्टर(DPTXFSIZN(4)),
	dump_रेजिस्टर(DPTXFSIZN(5)),
	dump_रेजिस्टर(DPTXFSIZN(6)),
	dump_रेजिस्टर(DPTXFSIZN(7)),
	dump_रेजिस्टर(DPTXFSIZN(8)),
	dump_रेजिस्टर(DPTXFSIZN(9)),
	dump_रेजिस्टर(DPTXFSIZN(10)),
	dump_रेजिस्टर(DPTXFSIZN(11)),
	dump_रेजिस्टर(DPTXFSIZN(12)),
	dump_रेजिस्टर(DPTXFSIZN(13)),
	dump_रेजिस्टर(DPTXFSIZN(14)),
	dump_रेजिस्टर(DPTXFSIZN(15)),
	dump_रेजिस्टर(DCFG),
	dump_रेजिस्टर(DCTL),
	dump_रेजिस्टर(DSTS),
	dump_रेजिस्टर(DIEPMSK),
	dump_रेजिस्टर(DOEPMSK),
	dump_रेजिस्टर(DAINT),
	dump_रेजिस्टर(DAINTMSK),
	dump_रेजिस्टर(DTKNQR1),
	dump_रेजिस्टर(DTKNQR2),
	dump_रेजिस्टर(DTKNQR3),
	dump_रेजिस्टर(DTKNQR4),
	dump_रेजिस्टर(DVBUSDIS),
	dump_रेजिस्टर(DVBUSPULSE),
	dump_रेजिस्टर(DIEPCTL(0)),
	dump_रेजिस्टर(DIEPCTL(1)),
	dump_रेजिस्टर(DIEPCTL(2)),
	dump_रेजिस्टर(DIEPCTL(3)),
	dump_रेजिस्टर(DIEPCTL(4)),
	dump_रेजिस्टर(DIEPCTL(5)),
	dump_रेजिस्टर(DIEPCTL(6)),
	dump_रेजिस्टर(DIEPCTL(7)),
	dump_रेजिस्टर(DIEPCTL(8)),
	dump_रेजिस्टर(DIEPCTL(9)),
	dump_रेजिस्टर(DIEPCTL(10)),
	dump_रेजिस्टर(DIEPCTL(11)),
	dump_रेजिस्टर(DIEPCTL(12)),
	dump_रेजिस्टर(DIEPCTL(13)),
	dump_रेजिस्टर(DIEPCTL(14)),
	dump_रेजिस्टर(DIEPCTL(15)),
	dump_रेजिस्टर(DOEPCTL(0)),
	dump_रेजिस्टर(DOEPCTL(1)),
	dump_रेजिस्टर(DOEPCTL(2)),
	dump_रेजिस्टर(DOEPCTL(3)),
	dump_रेजिस्टर(DOEPCTL(4)),
	dump_रेजिस्टर(DOEPCTL(5)),
	dump_रेजिस्टर(DOEPCTL(6)),
	dump_रेजिस्टर(DOEPCTL(7)),
	dump_रेजिस्टर(DOEPCTL(8)),
	dump_रेजिस्टर(DOEPCTL(9)),
	dump_रेजिस्टर(DOEPCTL(10)),
	dump_रेजिस्टर(DOEPCTL(11)),
	dump_रेजिस्टर(DOEPCTL(12)),
	dump_रेजिस्टर(DOEPCTL(13)),
	dump_रेजिस्टर(DOEPCTL(14)),
	dump_रेजिस्टर(DOEPCTL(15)),
	dump_रेजिस्टर(DIEPINT(0)),
	dump_रेजिस्टर(DIEPINT(1)),
	dump_रेजिस्टर(DIEPINT(2)),
	dump_रेजिस्टर(DIEPINT(3)),
	dump_रेजिस्टर(DIEPINT(4)),
	dump_रेजिस्टर(DIEPINT(5)),
	dump_रेजिस्टर(DIEPINT(6)),
	dump_रेजिस्टर(DIEPINT(7)),
	dump_रेजिस्टर(DIEPINT(8)),
	dump_रेजिस्टर(DIEPINT(9)),
	dump_रेजिस्टर(DIEPINT(10)),
	dump_रेजिस्टर(DIEPINT(11)),
	dump_रेजिस्टर(DIEPINT(12)),
	dump_रेजिस्टर(DIEPINT(13)),
	dump_रेजिस्टर(DIEPINT(14)),
	dump_रेजिस्टर(DIEPINT(15)),
	dump_रेजिस्टर(DOEPINT(0)),
	dump_रेजिस्टर(DOEPINT(1)),
	dump_रेजिस्टर(DOEPINT(2)),
	dump_रेजिस्टर(DOEPINT(3)),
	dump_रेजिस्टर(DOEPINT(4)),
	dump_रेजिस्टर(DOEPINT(5)),
	dump_रेजिस्टर(DOEPINT(6)),
	dump_रेजिस्टर(DOEPINT(7)),
	dump_रेजिस्टर(DOEPINT(8)),
	dump_रेजिस्टर(DOEPINT(9)),
	dump_रेजिस्टर(DOEPINT(10)),
	dump_रेजिस्टर(DOEPINT(11)),
	dump_रेजिस्टर(DOEPINT(12)),
	dump_रेजिस्टर(DOEPINT(13)),
	dump_रेजिस्टर(DOEPINT(14)),
	dump_रेजिस्टर(DOEPINT(15)),
	dump_रेजिस्टर(DIEPTSIZ(0)),
	dump_रेजिस्टर(DIEPTSIZ(1)),
	dump_रेजिस्टर(DIEPTSIZ(2)),
	dump_रेजिस्टर(DIEPTSIZ(3)),
	dump_रेजिस्टर(DIEPTSIZ(4)),
	dump_रेजिस्टर(DIEPTSIZ(5)),
	dump_रेजिस्टर(DIEPTSIZ(6)),
	dump_रेजिस्टर(DIEPTSIZ(7)),
	dump_रेजिस्टर(DIEPTSIZ(8)),
	dump_रेजिस्टर(DIEPTSIZ(9)),
	dump_रेजिस्टर(DIEPTSIZ(10)),
	dump_रेजिस्टर(DIEPTSIZ(11)),
	dump_रेजिस्टर(DIEPTSIZ(12)),
	dump_रेजिस्टर(DIEPTSIZ(13)),
	dump_रेजिस्टर(DIEPTSIZ(14)),
	dump_रेजिस्टर(DIEPTSIZ(15)),
	dump_रेजिस्टर(DOEPTSIZ(0)),
	dump_रेजिस्टर(DOEPTSIZ(1)),
	dump_रेजिस्टर(DOEPTSIZ(2)),
	dump_रेजिस्टर(DOEPTSIZ(3)),
	dump_रेजिस्टर(DOEPTSIZ(4)),
	dump_रेजिस्टर(DOEPTSIZ(5)),
	dump_रेजिस्टर(DOEPTSIZ(6)),
	dump_रेजिस्टर(DOEPTSIZ(7)),
	dump_रेजिस्टर(DOEPTSIZ(8)),
	dump_रेजिस्टर(DOEPTSIZ(9)),
	dump_रेजिस्टर(DOEPTSIZ(10)),
	dump_रेजिस्टर(DOEPTSIZ(11)),
	dump_रेजिस्टर(DOEPTSIZ(12)),
	dump_रेजिस्टर(DOEPTSIZ(13)),
	dump_रेजिस्टर(DOEPTSIZ(14)),
	dump_रेजिस्टर(DOEPTSIZ(15)),
	dump_रेजिस्टर(DIEPDMA(0)),
	dump_रेजिस्टर(DIEPDMA(1)),
	dump_रेजिस्टर(DIEPDMA(2)),
	dump_रेजिस्टर(DIEPDMA(3)),
	dump_रेजिस्टर(DIEPDMA(4)),
	dump_रेजिस्टर(DIEPDMA(5)),
	dump_रेजिस्टर(DIEPDMA(6)),
	dump_रेजिस्टर(DIEPDMA(7)),
	dump_रेजिस्टर(DIEPDMA(8)),
	dump_रेजिस्टर(DIEPDMA(9)),
	dump_रेजिस्टर(DIEPDMA(10)),
	dump_रेजिस्टर(DIEPDMA(11)),
	dump_रेजिस्टर(DIEPDMA(12)),
	dump_रेजिस्टर(DIEPDMA(13)),
	dump_रेजिस्टर(DIEPDMA(14)),
	dump_रेजिस्टर(DIEPDMA(15)),
	dump_रेजिस्टर(DOEPDMA(0)),
	dump_रेजिस्टर(DOEPDMA(1)),
	dump_रेजिस्टर(DOEPDMA(2)),
	dump_रेजिस्टर(DOEPDMA(3)),
	dump_रेजिस्टर(DOEPDMA(4)),
	dump_रेजिस्टर(DOEPDMA(5)),
	dump_रेजिस्टर(DOEPDMA(6)),
	dump_रेजिस्टर(DOEPDMA(7)),
	dump_रेजिस्टर(DOEPDMA(8)),
	dump_रेजिस्टर(DOEPDMA(9)),
	dump_रेजिस्टर(DOEPDMA(10)),
	dump_रेजिस्टर(DOEPDMA(11)),
	dump_रेजिस्टर(DOEPDMA(12)),
	dump_रेजिस्टर(DOEPDMA(13)),
	dump_रेजिस्टर(DOEPDMA(14)),
	dump_रेजिस्टर(DOEPDMA(15)),
	dump_रेजिस्टर(DTXFSTS(0)),
	dump_रेजिस्टर(DTXFSTS(1)),
	dump_रेजिस्टर(DTXFSTS(2)),
	dump_रेजिस्टर(DTXFSTS(3)),
	dump_रेजिस्टर(DTXFSTS(4)),
	dump_रेजिस्टर(DTXFSTS(5)),
	dump_रेजिस्टर(DTXFSTS(6)),
	dump_रेजिस्टर(DTXFSTS(7)),
	dump_रेजिस्टर(DTXFSTS(8)),
	dump_रेजिस्टर(DTXFSTS(9)),
	dump_रेजिस्टर(DTXFSTS(10)),
	dump_रेजिस्टर(DTXFSTS(11)),
	dump_रेजिस्टर(DTXFSTS(12)),
	dump_रेजिस्टर(DTXFSTS(13)),
	dump_रेजिस्टर(DTXFSTS(14)),
	dump_रेजिस्टर(DTXFSTS(15)),
	dump_रेजिस्टर(PCGCTL),
	dump_रेजिस्टर(HCFG),
	dump_रेजिस्टर(HFIR),
	dump_रेजिस्टर(HFNUM),
	dump_रेजिस्टर(HPTXSTS),
	dump_रेजिस्टर(HAINT),
	dump_रेजिस्टर(HAINTMSK),
	dump_रेजिस्टर(HFLBADDR),
	dump_रेजिस्टर(HPRT0),
	dump_रेजिस्टर(HCCHAR(0)),
	dump_रेजिस्टर(HCCHAR(1)),
	dump_रेजिस्टर(HCCHAR(2)),
	dump_रेजिस्टर(HCCHAR(3)),
	dump_रेजिस्टर(HCCHAR(4)),
	dump_रेजिस्टर(HCCHAR(5)),
	dump_रेजिस्टर(HCCHAR(6)),
	dump_रेजिस्टर(HCCHAR(7)),
	dump_रेजिस्टर(HCCHAR(8)),
	dump_रेजिस्टर(HCCHAR(9)),
	dump_रेजिस्टर(HCCHAR(10)),
	dump_रेजिस्टर(HCCHAR(11)),
	dump_रेजिस्टर(HCCHAR(12)),
	dump_रेजिस्टर(HCCHAR(13)),
	dump_रेजिस्टर(HCCHAR(14)),
	dump_रेजिस्टर(HCCHAR(15)),
	dump_रेजिस्टर(HCSPLT(0)),
	dump_रेजिस्टर(HCSPLT(1)),
	dump_रेजिस्टर(HCSPLT(2)),
	dump_रेजिस्टर(HCSPLT(3)),
	dump_रेजिस्टर(HCSPLT(4)),
	dump_रेजिस्टर(HCSPLT(5)),
	dump_रेजिस्टर(HCSPLT(6)),
	dump_रेजिस्टर(HCSPLT(7)),
	dump_रेजिस्टर(HCSPLT(8)),
	dump_रेजिस्टर(HCSPLT(9)),
	dump_रेजिस्टर(HCSPLT(10)),
	dump_रेजिस्टर(HCSPLT(11)),
	dump_रेजिस्टर(HCSPLT(12)),
	dump_रेजिस्टर(HCSPLT(13)),
	dump_रेजिस्टर(HCSPLT(14)),
	dump_रेजिस्टर(HCSPLT(15)),
	dump_रेजिस्टर(HCINT(0)),
	dump_रेजिस्टर(HCINT(1)),
	dump_रेजिस्टर(HCINT(2)),
	dump_रेजिस्टर(HCINT(3)),
	dump_रेजिस्टर(HCINT(4)),
	dump_रेजिस्टर(HCINT(5)),
	dump_रेजिस्टर(HCINT(6)),
	dump_रेजिस्टर(HCINT(7)),
	dump_रेजिस्टर(HCINT(8)),
	dump_रेजिस्टर(HCINT(9)),
	dump_रेजिस्टर(HCINT(10)),
	dump_रेजिस्टर(HCINT(11)),
	dump_रेजिस्टर(HCINT(12)),
	dump_रेजिस्टर(HCINT(13)),
	dump_रेजिस्टर(HCINT(14)),
	dump_रेजिस्टर(HCINT(15)),
	dump_रेजिस्टर(HCINTMSK(0)),
	dump_रेजिस्टर(HCINTMSK(1)),
	dump_रेजिस्टर(HCINTMSK(2)),
	dump_रेजिस्टर(HCINTMSK(3)),
	dump_रेजिस्टर(HCINTMSK(4)),
	dump_रेजिस्टर(HCINTMSK(5)),
	dump_रेजिस्टर(HCINTMSK(6)),
	dump_रेजिस्टर(HCINTMSK(7)),
	dump_रेजिस्टर(HCINTMSK(8)),
	dump_रेजिस्टर(HCINTMSK(9)),
	dump_रेजिस्टर(HCINTMSK(10)),
	dump_रेजिस्टर(HCINTMSK(11)),
	dump_रेजिस्टर(HCINTMSK(12)),
	dump_रेजिस्टर(HCINTMSK(13)),
	dump_रेजिस्टर(HCINTMSK(14)),
	dump_रेजिस्टर(HCINTMSK(15)),
	dump_रेजिस्टर(HCTSIZ(0)),
	dump_रेजिस्टर(HCTSIZ(1)),
	dump_रेजिस्टर(HCTSIZ(2)),
	dump_रेजिस्टर(HCTSIZ(3)),
	dump_रेजिस्टर(HCTSIZ(4)),
	dump_रेजिस्टर(HCTSIZ(5)),
	dump_रेजिस्टर(HCTSIZ(6)),
	dump_रेजिस्टर(HCTSIZ(7)),
	dump_रेजिस्टर(HCTSIZ(8)),
	dump_रेजिस्टर(HCTSIZ(9)),
	dump_रेजिस्टर(HCTSIZ(10)),
	dump_रेजिस्टर(HCTSIZ(11)),
	dump_रेजिस्टर(HCTSIZ(12)),
	dump_रेजिस्टर(HCTSIZ(13)),
	dump_रेजिस्टर(HCTSIZ(14)),
	dump_रेजिस्टर(HCTSIZ(15)),
	dump_रेजिस्टर(HCDMA(0)),
	dump_रेजिस्टर(HCDMA(1)),
	dump_रेजिस्टर(HCDMA(2)),
	dump_रेजिस्टर(HCDMA(3)),
	dump_रेजिस्टर(HCDMA(4)),
	dump_रेजिस्टर(HCDMA(5)),
	dump_रेजिस्टर(HCDMA(6)),
	dump_रेजिस्टर(HCDMA(7)),
	dump_रेजिस्टर(HCDMA(8)),
	dump_रेजिस्टर(HCDMA(9)),
	dump_रेजिस्टर(HCDMA(10)),
	dump_रेजिस्टर(HCDMA(11)),
	dump_रेजिस्टर(HCDMA(12)),
	dump_रेजिस्टर(HCDMA(13)),
	dump_रेजिस्टर(HCDMA(14)),
	dump_रेजिस्टर(HCDMA(15)),
	dump_रेजिस्टर(HCDMAB(0)),
	dump_रेजिस्टर(HCDMAB(1)),
	dump_रेजिस्टर(HCDMAB(2)),
	dump_रेजिस्टर(HCDMAB(3)),
	dump_रेजिस्टर(HCDMAB(4)),
	dump_रेजिस्टर(HCDMAB(5)),
	dump_रेजिस्टर(HCDMAB(6)),
	dump_रेजिस्टर(HCDMAB(7)),
	dump_रेजिस्टर(HCDMAB(8)),
	dump_रेजिस्टर(HCDMAB(9)),
	dump_रेजिस्टर(HCDMAB(10)),
	dump_रेजिस्टर(HCDMAB(11)),
	dump_रेजिस्टर(HCDMAB(12)),
	dump_रेजिस्टर(HCDMAB(13)),
	dump_रेजिस्टर(HCDMAB(14)),
	dump_रेजिस्टर(HCDMAB(15)),
पूर्ण;

#घोषणा prपूर्णांक_param(_seq, _ptr, _param) \
seq_म_लिखो((_seq), "%-30s: %d\n", #_param, (_ptr)->_param)

#घोषणा prपूर्णांक_param_hex(_seq, _ptr, _param) \
seq_म_लिखो((_seq), "%-30s: 0x%x\n", #_param, (_ptr)->_param)

अटल पूर्णांक params_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा dwc2_hsotg *hsotg = seq->निजी;
	काष्ठा dwc2_core_params *p = &hsotg->params;
	पूर्णांक i;

	prपूर्णांक_param(seq, p, otg_cap);
	prपूर्णांक_param(seq, p, dma_desc_enable);
	prपूर्णांक_param(seq, p, dma_desc_fs_enable);
	prपूर्णांक_param(seq, p, speed);
	prपूर्णांक_param(seq, p, enable_dynamic_fअगरo);
	prपूर्णांक_param(seq, p, en_multiple_tx_fअगरo);
	prपूर्णांक_param(seq, p, host_rx_fअगरo_size);
	prपूर्णांक_param(seq, p, host_nperio_tx_fअगरo_size);
	prपूर्णांक_param(seq, p, host_perio_tx_fअगरo_size);
	prपूर्णांक_param(seq, p, max_transfer_size);
	prपूर्णांक_param(seq, p, max_packet_count);
	prपूर्णांक_param(seq, p, host_channels);
	prपूर्णांक_param(seq, p, phy_type);
	prपूर्णांक_param(seq, p, phy_uपंचांगi_width);
	prपूर्णांक_param(seq, p, phy_ulpi_ddr);
	prपूर्णांक_param(seq, p, phy_ulpi_ext_vbus);
	prपूर्णांक_param(seq, p, i2c_enable);
	prपूर्णांक_param(seq, p, ipg_isoc_en);
	prपूर्णांक_param(seq, p, ulpi_fs_ls);
	prपूर्णांक_param(seq, p, host_support_fs_ls_low_घातer);
	prपूर्णांक_param(seq, p, host_ls_low_घातer_phy_clk);
	prपूर्णांक_param(seq, p, activate_sपंचांग_fs_transceiver);
	prपूर्णांक_param(seq, p, activate_sपंचांग_id_vb_detection);
	prपूर्णांक_param(seq, p, ts_dline);
	prपूर्णांक_param(seq, p, reload_ctl);
	prपूर्णांक_param_hex(seq, p, ahbcfg);
	prपूर्णांक_param(seq, p, uframe_sched);
	prपूर्णांक_param(seq, p, बाह्यal_id_pin_ctl);
	prपूर्णांक_param(seq, p, घातer_करोwn);
	prपूर्णांक_param(seq, p, lpm);
	prपूर्णांक_param(seq, p, lpm_घड़ी_gating);
	prपूर्णांक_param(seq, p, besl);
	prपूर्णांक_param(seq, p, hird_threshold_en);
	prपूर्णांक_param(seq, p, hird_threshold);
	prपूर्णांक_param(seq, p, service_पूर्णांकerval);
	prपूर्णांक_param(seq, p, host_dma);
	prपूर्णांक_param(seq, p, g_dma);
	prपूर्णांक_param(seq, p, g_dma_desc);
	prपूर्णांक_param(seq, p, g_rx_fअगरo_size);
	prपूर्णांक_param(seq, p, g_np_tx_fअगरo_size);

	क्रम (i = 0; i < MAX_EPS_CHANNELS; i++) अणु
		अक्षर str[32];

		snम_लिखो(str, 32, "g_tx_fifo_size[%d]", i);
		seq_म_लिखो(seq, "%-30s: %d\n", str, p->g_tx_fअगरo_size[i]);
	पूर्ण

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(params);

अटल पूर्णांक hw_params_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा dwc2_hsotg *hsotg = seq->निजी;
	काष्ठा dwc2_hw_params *hw = &hsotg->hw_params;

	prपूर्णांक_param(seq, hw, op_mode);
	prपूर्णांक_param(seq, hw, arch);
	prपूर्णांक_param(seq, hw, dma_desc_enable);
	prपूर्णांक_param(seq, hw, enable_dynamic_fअगरo);
	prपूर्णांक_param(seq, hw, en_multiple_tx_fअगरo);
	prपूर्णांक_param(seq, hw, rx_fअगरo_size);
	prपूर्णांक_param(seq, hw, host_nperio_tx_fअगरo_size);
	prपूर्णांक_param(seq, hw, dev_nperio_tx_fअगरo_size);
	prपूर्णांक_param(seq, hw, host_perio_tx_fअगरo_size);
	prपूर्णांक_param(seq, hw, nperio_tx_q_depth);
	prपूर्णांक_param(seq, hw, host_perio_tx_q_depth);
	prपूर्णांक_param(seq, hw, dev_token_q_depth);
	prपूर्णांक_param(seq, hw, max_transfer_size);
	prपूर्णांक_param(seq, hw, max_packet_count);
	prपूर्णांक_param(seq, hw, host_channels);
	prपूर्णांक_param(seq, hw, hs_phy_type);
	prपूर्णांक_param(seq, hw, fs_phy_type);
	prपूर्णांक_param(seq, hw, i2c_enable);
	prपूर्णांक_param(seq, hw, num_dev_ep);
	prपूर्णांक_param(seq, hw, num_dev_perio_in_ep);
	prपूर्णांक_param(seq, hw, total_fअगरo_size);
	prपूर्णांक_param(seq, hw, घातer_optimized);
	prपूर्णांक_param(seq, hw, uपंचांगi_phy_data_width);
	prपूर्णांक_param_hex(seq, hw, snpsid);
	prपूर्णांक_param_hex(seq, hw, dev_ep_dirs);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(hw_params);

अटल पूर्णांक dr_mode_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा dwc2_hsotg *hsotg = seq->निजी;
	स्थिर अक्षर *dr_mode = "";

	device_property_पढ़ो_string(hsotg->dev, "dr_mode", &dr_mode);
	seq_म_लिखो(seq, "%s\n", dr_mode);
	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(dr_mode);

पूर्णांक dwc2_debugfs_init(काष्ठा dwc2_hsotg *hsotg)
अणु
	पूर्णांक			ret;
	काष्ठा dentry		*root;

	root = debugfs_create_dir(dev_name(hsotg->dev), usb_debug_root);
	hsotg->debug_root = root;

	debugfs_create_file("params", 0444, root, hsotg, &params_fops);
	debugfs_create_file("hw_params", 0444, root, hsotg, &hw_params_fops);
	debugfs_create_file("dr_mode", 0444, root, hsotg, &dr_mode_fops);

	/* Add gadget debugfs nodes */
	dwc2_hsotg_create_debug(hsotg);

	hsotg->regset = devm_kzalloc(hsotg->dev, माप(*hsotg->regset),
								GFP_KERNEL);
	अगर (!hsotg->regset) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	hsotg->regset->regs = dwc2_regs;
	hsotg->regset->nregs = ARRAY_SIZE(dwc2_regs);
	hsotg->regset->base = hsotg->regs;

	debugfs_create_regset32("regdump", 0444, root, hsotg->regset);

	वापस 0;
err:
	debugfs_हटाओ_recursive(hsotg->debug_root);
	वापस ret;
पूर्ण

व्योम dwc2_debugfs_निकास(काष्ठा dwc2_hsotg *hsotg)
अणु
	debugfs_हटाओ_recursive(hsotg->debug_root);
	hsotg->debug_root = शून्य;
पूर्ण
