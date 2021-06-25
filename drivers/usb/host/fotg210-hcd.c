<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/* Faraday FOTG210 EHCI-like driver
 *
 * Copyright (c) 2013 Faraday Technology Corporation
 *
 * Author: Yuan-Hsin Chen <yhchen@faraday-tech.com>
 *	   Feng-Hsin Chiang <john453@faraday-tech.com>
 *	   Po-Yu Chuang <ratbert.chuang@gmail.com>
 *
 * Most of code borrowed from the Linux-3.7 EHCI driver
 */
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/device.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/ioport.h>
#समावेश <linux/sched.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/list.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/hcd.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/clk.h>

#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/unaligned.h>

#घोषणा DRIVER_AUTHOR "Yuan-Hsin Chen"
#घोषणा DRIVER_DESC "FOTG210 Host Controller (EHCI) Driver"
अटल स्थिर अक्षर hcd_name[] = "fotg210_hcd";

#अघोषित FOTG210_URB_TRACE
#घोषणा FOTG210_STATS

/* magic numbers that can affect प्रणाली perक्रमmance */
#घोषणा FOTG210_TUNE_CERR	3 /* 0-3 qtd retries; 0 == करोn't stop */
#घोषणा FOTG210_TUNE_RL_HS	4 /* nak throttle; see 4.9 */
#घोषणा FOTG210_TUNE_RL_TT	0
#घोषणा FOTG210_TUNE_MULT_HS	1 /* 1-3 transactions/uframe; 4.10.3 */
#घोषणा FOTG210_TUNE_MULT_TT	1

/* Some drivers think it's safe to schedule isochronous transfers more than 256
 * ms पूर्णांकo the future (partly as a result of an old bug in the scheduling
 * code).  In an attempt to aव्योम trouble, we will use a minimum scheduling
 * length of 512 frames instead of 256.
 */
#घोषणा FOTG210_TUNE_FLS 1 /* (medium) 512-frame schedule */

/* Initial IRQ latency:  faster than hw शेष */
अटल पूर्णांक log2_irq_thresh; /* 0 to 6 */
module_param(log2_irq_thresh, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(log2_irq_thresh, "log2 IRQ latency, 1-64 microframes");

/* initial park setting:  slower than hw शेष */
अटल अचिन्हित park;
module_param(park, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(park, "park setting; 1-3 back-to-back async packets");

/* क्रम link घातer management(LPM) feature */
अटल अचिन्हित पूर्णांक hird;
module_param(hird, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(hird, "host initiated resume duration, +1 for each 75us");

#घोषणा INTR_MASK (STS_IAA | STS_FATAL | STS_PCD | STS_ERR | STS_INT)

#समावेश "fotg210.h"

#घोषणा fotg210_dbg(fotg210, fmt, args...) \
	dev_dbg(fotg210_to_hcd(fotg210)->self.controller, fmt, ## args)
#घोषणा fotg210_err(fotg210, fmt, args...) \
	dev_err(fotg210_to_hcd(fotg210)->self.controller, fmt, ## args)
#घोषणा fotg210_info(fotg210, fmt, args...) \
	dev_info(fotg210_to_hcd(fotg210)->self.controller, fmt, ## args)
#घोषणा fotg210_warn(fotg210, fmt, args...) \
	dev_warn(fotg210_to_hcd(fotg210)->self.controller, fmt, ## args)

/* check the values in the HCSPARAMS रेजिस्टर (host controller _Structural_
 * parameters) see EHCI spec, Table 2-4 क्रम each value
 */
अटल व्योम dbg_hcs_params(काष्ठा fotg210_hcd *fotg210, अक्षर *label)
अणु
	u32 params = fotg210_पढ़ोl(fotg210, &fotg210->caps->hcs_params);

	fotg210_dbg(fotg210, "%s hcs_params 0x%x ports=%d\n", label, params,
			HCS_N_PORTS(params));
पूर्ण

/* check the values in the HCCPARAMS रेजिस्टर (host controller _Capability_
 * parameters) see EHCI Spec, Table 2-5 क्रम each value
 */
अटल व्योम dbg_hcc_params(काष्ठा fotg210_hcd *fotg210, अक्षर *label)
अणु
	u32 params = fotg210_पढ़ोl(fotg210, &fotg210->caps->hcc_params);

	fotg210_dbg(fotg210, "%s hcc_params %04x uframes %s%s\n", label,
			params,
			HCC_PGM_FRAMELISTLEN(params) ? "256/512/1024" : "1024",
			HCC_CANPARK(params) ? " park" : "");
पूर्ण

अटल व्योम __maybe_unused
dbg_qtd(स्थिर अक्षर *label, काष्ठा fotg210_hcd *fotg210, काष्ठा fotg210_qtd *qtd)
अणु
	fotg210_dbg(fotg210, "%s td %p n%08x %08x t%08x p0=%08x\n", label, qtd,
			hc32_to_cpup(fotg210, &qtd->hw_next),
			hc32_to_cpup(fotg210, &qtd->hw_alt_next),
			hc32_to_cpup(fotg210, &qtd->hw_token),
			hc32_to_cpup(fotg210, &qtd->hw_buf[0]));
	अगर (qtd->hw_buf[1])
		fotg210_dbg(fotg210, "  p1=%08x p2=%08x p3=%08x p4=%08x\n",
				hc32_to_cpup(fotg210, &qtd->hw_buf[1]),
				hc32_to_cpup(fotg210, &qtd->hw_buf[2]),
				hc32_to_cpup(fotg210, &qtd->hw_buf[3]),
				hc32_to_cpup(fotg210, &qtd->hw_buf[4]));
पूर्ण

अटल व्योम __maybe_unused
dbg_qh(स्थिर अक्षर *label, काष्ठा fotg210_hcd *fotg210, काष्ठा fotg210_qh *qh)
अणु
	काष्ठा fotg210_qh_hw *hw = qh->hw;

	fotg210_dbg(fotg210, "%s qh %p n%08x info %x %x qtd %x\n", label, qh,
			hw->hw_next, hw->hw_info1, hw->hw_info2,
			hw->hw_current);

	dbg_qtd("overlay", fotg210, (काष्ठा fotg210_qtd *) &hw->hw_qtd_next);
पूर्ण

अटल व्योम __maybe_unused
dbg_itd(स्थिर अक्षर *label, काष्ठा fotg210_hcd *fotg210, काष्ठा fotg210_itd *itd)
अणु
	fotg210_dbg(fotg210, "%s[%d] itd %p, next %08x, urb %p\n", label,
			itd->frame, itd, hc32_to_cpu(fotg210, itd->hw_next),
			itd->urb);

	fotg210_dbg(fotg210,
			"  trans: %08x %08x %08x %08x %08x %08x %08x %08x\n",
			hc32_to_cpu(fotg210, itd->hw_transaction[0]),
			hc32_to_cpu(fotg210, itd->hw_transaction[1]),
			hc32_to_cpu(fotg210, itd->hw_transaction[2]),
			hc32_to_cpu(fotg210, itd->hw_transaction[3]),
			hc32_to_cpu(fotg210, itd->hw_transaction[4]),
			hc32_to_cpu(fotg210, itd->hw_transaction[5]),
			hc32_to_cpu(fotg210, itd->hw_transaction[6]),
			hc32_to_cpu(fotg210, itd->hw_transaction[7]));

	fotg210_dbg(fotg210,
			"  buf:   %08x %08x %08x %08x %08x %08x %08x\n",
			hc32_to_cpu(fotg210, itd->hw_bufp[0]),
			hc32_to_cpu(fotg210, itd->hw_bufp[1]),
			hc32_to_cpu(fotg210, itd->hw_bufp[2]),
			hc32_to_cpu(fotg210, itd->hw_bufp[3]),
			hc32_to_cpu(fotg210, itd->hw_bufp[4]),
			hc32_to_cpu(fotg210, itd->hw_bufp[5]),
			hc32_to_cpu(fotg210, itd->hw_bufp[6]));

	fotg210_dbg(fotg210, "  index: %d %d %d %d %d %d %d %d\n",
			itd->index[0], itd->index[1], itd->index[2],
			itd->index[3], itd->index[4], itd->index[5],
			itd->index[6], itd->index[7]);
पूर्ण

अटल पूर्णांक __maybe_unused
dbg_status_buf(अक्षर *buf, अचिन्हित len, स्थिर अक्षर *label, u32 status)
अणु
	वापस scnम_लिखो(buf, len, "%s%sstatus %04x%s%s%s%s%s%s%s%s%s%s",
			label, label[0] ? " " : "", status,
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
	वापस scnम_लिखो(buf, len, "%s%sintrenable %02x%s%s%s%s%s%s",
			label, label[0] ? " " : "", enable,
			(enable & STS_IAA) ? " IAA" : "",
			(enable & STS_FATAL) ? " FATAL" : "",
			(enable & STS_FLR) ? " FLR" : "",
			(enable & STS_PCD) ? " PCD" : "",
			(enable & STS_ERR) ? " ERR" : "",
			(enable & STS_INT) ? " INT" : "");
पूर्ण

अटल स्थिर अक्षर *स्थिर fls_strings[] = अणु "1024", "512", "256", "??" पूर्ण;

अटल पूर्णांक dbg_command_buf(अक्षर *buf, अचिन्हित len, स्थिर अक्षर *label,
		u32 command)
अणु
	वापस scnम_लिखो(buf, len,
			"%s%scommand %07x %s=%d ithresh=%d%s%s%s period=%s%s %s",
			label, label[0] ? " " : "", command,
			(command & CMD_PARK) ? " park" : "(park)",
			CMD_PARK_CNT(command),
			(command >> 16) & 0x3f,
			(command & CMD_IAAD) ? " IAAD" : "",
			(command & CMD_ASE) ? " Async" : "",
			(command & CMD_PSE) ? " Periodic" : "",
			fls_strings[(command >> 2) & 0x3],
			(command & CMD_RESET) ? " Reset" : "",
			(command & CMD_RUN) ? "RUN" : "HALT");
पूर्ण

अटल अक्षर *dbg_port_buf(अक्षर *buf, अचिन्हित len, स्थिर अक्षर *label, पूर्णांक port,
		u32 status)
अणु
	अक्षर *sig;

	/* संकेतing state */
	चयन (status & (3 << 10)) अणु
	हाल 0 << 10:
		sig = "se0";
		अवरोध;
	हाल 1 << 10:
		sig = "k";
		अवरोध; /* low speed */
	हाल 2 << 10:
		sig = "j";
		अवरोध;
	शेष:
		sig = "?";
		अवरोध;
	पूर्ण

	scnम_लिखो(buf, len, "%s%sport:%d status %06x %d sig=%s%s%s%s%s%s%s%s",
			label, label[0] ? " " : "", port, status,
			status >> 25, /*device address */
			sig,
			(status & PORT_RESET) ? " RESET" : "",
			(status & PORT_SUSPEND) ? " SUSPEND" : "",
			(status & PORT_RESUME) ? " RESUME" : "",
			(status & PORT_PEC) ? " PEC" : "",
			(status & PORT_PE) ? " PE" : "",
			(status & PORT_CSC) ? " CSC" : "",
			(status & PORT_CONNECT) ? " CONNECT" : "");

	वापस buf;
पूर्ण

/* functions have the "wrong" filename when they're output... */
#घोषणा dbg_status(fotg210, label, status) अणु			\
	अक्षर _buf[80];						\
	dbg_status_buf(_buf, माप(_buf), label, status);	\
	fotg210_dbg(fotg210, "%s\n", _buf);			\
पूर्ण

#घोषणा dbg_cmd(fotg210, label, command) अणु			\
	अक्षर _buf[80];						\
	dbg_command_buf(_buf, माप(_buf), label, command);	\
	fotg210_dbg(fotg210, "%s\n", _buf);			\
पूर्ण

#घोषणा dbg_port(fotg210, label, port, status) अणु			       \
	अक्षर _buf[80];							       \
	fotg210_dbg(fotg210, "%s\n",					       \
			dbg_port_buf(_buf, माप(_buf), label, port, status));\
पूर्ण

/* troubleshooting help: expose state in debugfs */
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

अटल काष्ठा dentry *fotg210_debug_root;

काष्ठा debug_buffer अणु
	sमाप_प्रकार (*fill_func)(काष्ठा debug_buffer *);	/* fill method */
	काष्ठा usb_bus *bus;
	काष्ठा mutex mutex;	/* protect filling of buffer */
	माप_प्रकार count;		/* number of अक्षरacters filled पूर्णांकo buffer */
	अक्षर *output_buf;
	माप_प्रकार alloc_size;
पूर्ण;

अटल अंतरभूत अक्षर speed_अक्षर(u32 scratch)
अणु
	चयन (scratch & (3 << 12)) अणु
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

अटल अंतरभूत अक्षर token_mark(काष्ठा fotg210_hcd *fotg210, __hc32 token)
अणु
	__u32 v = hc32_to_cpu(fotg210, token);

	अगर (v & QTD_STS_ACTIVE)
		वापस '*';
	अगर (v & QTD_STS_HALT)
		वापस '-';
	अगर (!IS_SHORT_READ(v))
		वापस ' ';
	/* tries to advance through hw_alt_next */
	वापस '/';
पूर्ण

अटल व्योम qh_lines(काष्ठा fotg210_hcd *fotg210, काष्ठा fotg210_qh *qh,
		अक्षर **nextp, अचिन्हित *sizep)
अणु
	u32 scratch;
	u32 hw_curr;
	काष्ठा fotg210_qtd *td;
	अचिन्हित temp;
	अचिन्हित size = *sizep;
	अक्षर *next = *nextp;
	अक्षर mark;
	__le32 list_end = FOTG210_LIST_END(fotg210);
	काष्ठा fotg210_qh_hw *hw = qh->hw;

	अगर (hw->hw_qtd_next == list_end) /* NEC करोes this */
		mark = '@';
	अन्यथा
		mark = token_mark(fotg210, hw->hw_token);
	अगर (mark == '/') अणु /* qh_alt_next controls qh advance? */
		अगर ((hw->hw_alt_next & QTD_MASK(fotg210)) ==
		    fotg210->async->hw->hw_alt_next)
			mark = '#'; /* blocked */
		अन्यथा अगर (hw->hw_alt_next == list_end)
			mark = '.'; /* use hw_qtd_next */
		/* अन्यथा alt_next poपूर्णांकs to some other qtd */
	पूर्ण
	scratch = hc32_to_cpup(fotg210, &hw->hw_info1);
	hw_curr = (mark == '*') ? hc32_to_cpup(fotg210, &hw->hw_current) : 0;
	temp = scnम_लिखो(next, size,
			"qh/%p dev%d %cs ep%d %08x %08x(%08x%c %s nak%d)",
			qh, scratch & 0x007f,
			speed_अक्षर(scratch),
			(scratch >> 8) & 0x000f,
			scratch, hc32_to_cpup(fotg210, &hw->hw_info2),
			hc32_to_cpup(fotg210, &hw->hw_token), mark,
			(cpu_to_hc32(fotg210, QTD_TOGGLE) & hw->hw_token)
				? "data1" : "data0",
			(hc32_to_cpup(fotg210, &hw->hw_alt_next) >> 1) & 0x0f);
	size -= temp;
	next += temp;

	/* hc may be modअगरying the list as we पढ़ो it ... */
	list_क्रम_each_entry(td, &qh->qtd_list, qtd_list) अणु
		scratch = hc32_to_cpup(fotg210, &td->hw_token);
		mark = ' ';
		अगर (hw_curr == td->qtd_dma)
			mark = '*';
		अन्यथा अगर (hw->hw_qtd_next == cpu_to_hc32(fotg210, td->qtd_dma))
			mark = '+';
		अन्यथा अगर (QTD_LENGTH(scratch)) अणु
			अगर (td->hw_alt_next == fotg210->async->hw->hw_alt_next)
				mark = '#';
			अन्यथा अगर (td->hw_alt_next != list_end)
				mark = '/';
		पूर्ण
		temp = snम_लिखो(next, size,
				"\n\t%p%c%s len=%d %08x urb %p",
				td, mark, (अणु अक्षर *पंचांगp;
				चयन ((scratch>>8)&0x03) अणु
				हाल 0:
					पंचांगp = "out";
					अवरोध;
				हाल 1:
					पंचांगp = "in";
					अवरोध;
				हाल 2:
					पंचांगp = "setup";
					अवरोध;
				शेष:
					पंचांगp = "?";
					अवरोध;
				 पूर्ण पंचांगp; पूर्ण),
				(scratch >> 16) & 0x7fff,
				scratch,
				td->urb);
		अगर (size < temp)
			temp = size;
		size -= temp;
		next += temp;
		अगर (temp == size)
			जाओ करोne;
	पूर्ण

	temp = snम_लिखो(next, size, "\n");
	अगर (size < temp)
		temp = size;

	size -= temp;
	next += temp;

करोne:
	*sizep = size;
	*nextp = next;
पूर्ण

अटल sमाप_प्रकार fill_async_buffer(काष्ठा debug_buffer *buf)
अणु
	काष्ठा usb_hcd *hcd;
	काष्ठा fotg210_hcd *fotg210;
	अचिन्हित दीर्घ flags;
	अचिन्हित temp, size;
	अक्षर *next;
	काष्ठा fotg210_qh *qh;

	hcd = bus_to_hcd(buf->bus);
	fotg210 = hcd_to_fotg210(hcd);
	next = buf->output_buf;
	size = buf->alloc_size;

	*next = 0;

	/* dumps a snapshot of the async schedule.
	 * usually empty except क्रम दीर्घ-term bulk पढ़ोs, or head.
	 * one QH per line, and TDs we know about
	 */
	spin_lock_irqsave(&fotg210->lock, flags);
	क्रम (qh = fotg210->async->qh_next.qh; size > 0 && qh;
			qh = qh->qh_next.qh)
		qh_lines(fotg210, qh, &next, &size);
	अगर (fotg210->async_unlink && size > 0) अणु
		temp = scnम_लिखो(next, size, "\nunlink =\n");
		size -= temp;
		next += temp;

		क्रम (qh = fotg210->async_unlink; size > 0 && qh;
				qh = qh->unlink_next)
			qh_lines(fotg210, qh, &next, &size);
	पूर्ण
	spin_unlock_irqrestore(&fotg210->lock, flags);

	वापस म_माप(buf->output_buf);
पूर्ण

/* count tds, get ep direction */
अटल अचिन्हित output_buf_tds_dir(अक्षर *buf, काष्ठा fotg210_hcd *fotg210,
		काष्ठा fotg210_qh_hw *hw, काष्ठा fotg210_qh *qh, अचिन्हित size)
अणु
	u32 scratch = hc32_to_cpup(fotg210, &hw->hw_info1);
	काष्ठा fotg210_qtd *qtd;
	अक्षर *type = "";
	अचिन्हित temp = 0;

	/* count tds, get ep direction */
	list_क्रम_each_entry(qtd, &qh->qtd_list, qtd_list) अणु
		temp++;
		चयन ((hc32_to_cpu(fotg210, qtd->hw_token) >> 8) & 0x03) अणु
		हाल 0:
			type = "out";
			जारी;
		हाल 1:
			type = "in";
			जारी;
		पूर्ण
	पूर्ण

	वापस scnम_लिखो(buf, size, "(%c%d ep%d%s [%d/%d] q%d p%d)",
			speed_अक्षर(scratch), scratch & 0x007f,
			(scratch >> 8) & 0x000f, type, qh->usecs,
			qh->c_usecs, temp, (scratch >> 16) & 0x7ff);
पूर्ण

#घोषणा DBG_SCHED_LIMIT 64
अटल sमाप_प्रकार fill_periodic_buffer(काष्ठा debug_buffer *buf)
अणु
	काष्ठा usb_hcd *hcd;
	काष्ठा fotg210_hcd *fotg210;
	अचिन्हित दीर्घ flags;
	जोड़ fotg210_shaकरोw p, *seen;
	अचिन्हित temp, size, seen_count;
	अक्षर *next;
	अचिन्हित i;
	__hc32 tag;

	seen = kदो_स्मृति_array(DBG_SCHED_LIMIT, माप(*seen), GFP_ATOMIC);
	अगर (!seen)
		वापस 0;

	seen_count = 0;

	hcd = bus_to_hcd(buf->bus);
	fotg210 = hcd_to_fotg210(hcd);
	next = buf->output_buf;
	size = buf->alloc_size;

	temp = scnम_लिखो(next, size, "size = %d\n", fotg210->periodic_size);
	size -= temp;
	next += temp;

	/* dump a snapshot of the periodic schedule.
	 * iso changes, पूर्णांकerrupt usually करोesn't.
	 */
	spin_lock_irqsave(&fotg210->lock, flags);
	क्रम (i = 0; i < fotg210->periodic_size; i++) अणु
		p = fotg210->pshaकरोw[i];
		अगर (likely(!p.ptr))
			जारी;

		tag = Q_NEXT_TYPE(fotg210, fotg210->periodic[i]);

		temp = scnम_लिखो(next, size, "%4d: ", i);
		size -= temp;
		next += temp;

		करो अणु
			काष्ठा fotg210_qh_hw *hw;

			चयन (hc32_to_cpu(fotg210, tag)) अणु
			हाल Q_TYPE_QH:
				hw = p.qh->hw;
				temp = scnम_लिखो(next, size, " qh%d-%04x/%p",
						p.qh->period,
						hc32_to_cpup(fotg210,
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
					temp = output_buf_tds_dir(next,
							fotg210, hw,
							p.qh, size);

					अगर (seen_count < DBG_SCHED_LIMIT)
						seen[seen_count++].qh = p.qh;
				पूर्ण अन्यथा
					temp = 0;
				tag = Q_NEXT_TYPE(fotg210, hw->hw_next);
				p = p.qh->qh_next;
				अवरोध;
			हाल Q_TYPE_FSTN:
				temp = scnम_लिखो(next, size,
						" fstn-%8x/%p",
						p.fstn->hw_prev, p.fstn);
				tag = Q_NEXT_TYPE(fotg210, p.fstn->hw_next);
				p = p.fstn->fstn_next;
				अवरोध;
			हाल Q_TYPE_ITD:
				temp = scnम_लिखो(next, size,
						" itd/%p", p.itd);
				tag = Q_NEXT_TYPE(fotg210, p.itd->hw_next);
				p = p.itd->itd_next;
				अवरोध;
			पूर्ण
			size -= temp;
			next += temp;
		पूर्ण जबतक (p.ptr);

		temp = scnम_लिखो(next, size, "\n");
		size -= temp;
		next += temp;
	पूर्ण
	spin_unlock_irqrestore(&fotg210->lock, flags);
	kमुक्त(seen);

	वापस buf->alloc_size - size;
पूर्ण
#अघोषित DBG_SCHED_LIMIT

अटल स्थिर अक्षर *rh_state_string(काष्ठा fotg210_hcd *fotg210)
अणु
	चयन (fotg210->rh_state) अणु
	हाल FOTG210_RH_HALTED:
		वापस "halted";
	हाल FOTG210_RH_SUSPENDED:
		वापस "suspended";
	हाल FOTG210_RH_RUNNING:
		वापस "running";
	हाल FOTG210_RH_STOPPING:
		वापस "stopping";
	पूर्ण
	वापस "?";
पूर्ण

अटल sमाप_प्रकार fill_रेजिस्टरs_buffer(काष्ठा debug_buffer *buf)
अणु
	काष्ठा usb_hcd *hcd;
	काष्ठा fotg210_hcd *fotg210;
	अचिन्हित दीर्घ flags;
	अचिन्हित temp, size, i;
	अक्षर *next, scratch[80];
	अटल स्थिर अक्षर fmt[] = "%*s\n";
	अटल स्थिर अक्षर label[] = "";

	hcd = bus_to_hcd(buf->bus);
	fotg210 = hcd_to_fotg210(hcd);
	next = buf->output_buf;
	size = buf->alloc_size;

	spin_lock_irqsave(&fotg210->lock, flags);

	अगर (!HCD_HW_ACCESSIBLE(hcd)) अणु
		size = scnम_लिखो(next, size,
				"bus %s, device %s\n"
				"%s\n"
				"SUSPENDED(no register access)\n",
				hcd->self.controller->bus->name,
				dev_name(hcd->self.controller),
				hcd->product_desc);
		जाओ करोne;
	पूर्ण

	/* Capability Registers */
	i = HC_VERSION(fotg210, fotg210_पढ़ोl(fotg210,
			&fotg210->caps->hc_capbase));
	temp = scnम_लिखो(next, size,
			"bus %s, device %s\n"
			"%s\n"
			"EHCI %x.%02x, rh state %s\n",
			hcd->self.controller->bus->name,
			dev_name(hcd->self.controller),
			hcd->product_desc,
			i >> 8, i & 0x0ff, rh_state_string(fotg210));
	size -= temp;
	next += temp;

	/* FIXME पूर्णांकerpret both types of params */
	i = fotg210_पढ़ोl(fotg210, &fotg210->caps->hcs_params);
	temp = scnम_लिखो(next, size, "structural params 0x%08x\n", i);
	size -= temp;
	next += temp;

	i = fotg210_पढ़ोl(fotg210, &fotg210->caps->hcc_params);
	temp = scnम_लिखो(next, size, "capability params 0x%08x\n", i);
	size -= temp;
	next += temp;

	/* Operational Registers */
	temp = dbg_status_buf(scratch, माप(scratch), label,
			fotg210_पढ़ोl(fotg210, &fotg210->regs->status));
	temp = scnम_लिखो(next, size, fmt, temp, scratch);
	size -= temp;
	next += temp;

	temp = dbg_command_buf(scratch, माप(scratch), label,
			fotg210_पढ़ोl(fotg210, &fotg210->regs->command));
	temp = scnम_लिखो(next, size, fmt, temp, scratch);
	size -= temp;
	next += temp;

	temp = dbg_पूर्णांकr_buf(scratch, माप(scratch), label,
			fotg210_पढ़ोl(fotg210, &fotg210->regs->पूर्णांकr_enable));
	temp = scnम_लिखो(next, size, fmt, temp, scratch);
	size -= temp;
	next += temp;

	temp = scnम_लिखो(next, size, "uframe %04x\n",
			fotg210_पढ़ो_frame_index(fotg210));
	size -= temp;
	next += temp;

	अगर (fotg210->async_unlink) अणु
		temp = scnम_लिखो(next, size, "async unlink qh %p\n",
				fotg210->async_unlink);
		size -= temp;
		next += temp;
	पूर्ण

#अगर_घोषित FOTG210_STATS
	temp = scnम_लिखो(next, size,
			"irq normal %ld err %ld iaa %ld(lost %ld)\n",
			fotg210->stats.normal, fotg210->stats.error,
			fotg210->stats.iaa, fotg210->stats.lost_iaa);
	size -= temp;
	next += temp;

	temp = scnम_लिखो(next, size, "complete %ld unlink %ld\n",
			fotg210->stats.complete, fotg210->stats.unlink);
	size -= temp;
	next += temp;
#पूर्ण_अगर

करोne:
	spin_unlock_irqrestore(&fotg210->lock, flags);

	वापस buf->alloc_size - size;
पूर्ण

अटल काष्ठा debug_buffer
*alloc_buffer(काष्ठा usb_bus *bus, sमाप_प्रकार (*fill_func)(काष्ठा debug_buffer *))
अणु
	काष्ठा debug_buffer *buf;

	buf = kzalloc(माप(काष्ठा debug_buffer), GFP_KERNEL);

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

अटल पूर्णांक debug_periodic_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा debug_buffer *buf;

	buf = alloc_buffer(inode->i_निजी, fill_periodic_buffer);
	अगर (!buf)
		वापस -ENOMEM;

	buf->alloc_size = (माप(व्योम *) == 4 ? 6 : 8)*PAGE_SIZE;
	file->निजी_data = buf;
	वापस 0;
पूर्ण

अटल पूर्णांक debug_रेजिस्टरs_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	file->निजी_data = alloc_buffer(inode->i_निजी,
			fill_रेजिस्टरs_buffer);

	वापस file->निजी_data ? 0 : -ENOMEM;
पूर्ण

अटल अंतरभूत व्योम create_debug_files(काष्ठा fotg210_hcd *fotg210)
अणु
	काष्ठा usb_bus *bus = &fotg210_to_hcd(fotg210)->self;
	काष्ठा dentry *root;

	root = debugfs_create_dir(bus->bus_name, fotg210_debug_root);
	fotg210->debug_dir = root;

	debugfs_create_file("async", S_IRUGO, root, bus, &debug_async_fops);
	debugfs_create_file("periodic", S_IRUGO, root, bus,
			    &debug_periodic_fops);
	debugfs_create_file("registers", S_IRUGO, root, bus,
			    &debug_रेजिस्टरs_fops);
पूर्ण

अटल अंतरभूत व्योम हटाओ_debug_files(काष्ठा fotg210_hcd *fotg210)
अणु
	debugfs_हटाओ_recursive(fotg210->debug_dir);
पूर्ण

/* handshake - spin पढ़ोing hc until handshake completes or fails
 * @ptr: address of hc रेजिस्टर to be पढ़ो
 * @mask: bits to look at in result of पढ़ो
 * @करोne: value of those bits when handshake succeeds
 * @usec: समयout in microseconds
 *
 * Returns negative त्रुटि_सं, or zero on success
 *
 * Success happens when the "mask" bits have the specअगरied value (hardware
 * handshake करोne).  There are two failure modes:  "usec" have passed (major
 * hardware flakeout), or the रेजिस्टर पढ़ोs as all-ones (hardware हटाओd).
 *
 * That last failure should_only happen in हालs like physical cardbus eject
 * beक्रमe driver shutकरोwn. But it also seems to be caused by bugs in cardbus
 * bridge shutकरोwn:  shutting करोwn the bridge beक्रमe the devices using it.
 */
अटल पूर्णांक handshake(काष्ठा fotg210_hcd *fotg210, व्योम __iomem *ptr,
		u32 mask, u32 करोne, पूर्णांक usec)
अणु
	u32 result;
	पूर्णांक ret;

	ret = पढ़ोl_poll_समयout_atomic(ptr, result,
					((result & mask) == करोne ||
					 result == U32_MAX), 1, usec);
	अगर (result == U32_MAX)		/* card हटाओd */
		वापस -ENODEV;

	वापस ret;
पूर्ण

/* Force HC to halt state from unknown (EHCI spec section 2.3).
 * Must be called with पूर्णांकerrupts enabled and the lock not held.
 */
अटल पूर्णांक fotg210_halt(काष्ठा fotg210_hcd *fotg210)
अणु
	u32 temp;

	spin_lock_irq(&fotg210->lock);

	/* disable any irqs left enabled by previous code */
	fotg210_ग_लिखोl(fotg210, 0, &fotg210->regs->पूर्णांकr_enable);

	/*
	 * This routine माला_लो called during probe beक्रमe fotg210->command
	 * has been initialized, so we can't rely on its value.
	 */
	fotg210->command &= ~CMD_RUN;
	temp = fotg210_पढ़ोl(fotg210, &fotg210->regs->command);
	temp &= ~(CMD_RUN | CMD_IAAD);
	fotg210_ग_लिखोl(fotg210, temp, &fotg210->regs->command);

	spin_unlock_irq(&fotg210->lock);
	synchronize_irq(fotg210_to_hcd(fotg210)->irq);

	वापस handshake(fotg210, &fotg210->regs->status,
			STS_HALT, STS_HALT, 16 * 125);
पूर्ण

/* Reset a non-running (STS_HALT == 1) controller.
 * Must be called with पूर्णांकerrupts enabled and the lock not held.
 */
अटल पूर्णांक fotg210_reset(काष्ठा fotg210_hcd *fotg210)
अणु
	पूर्णांक retval;
	u32 command = fotg210_पढ़ोl(fotg210, &fotg210->regs->command);

	/* If the EHCI debug controller is active, special care must be
	 * taken beक्रमe and after a host controller reset
	 */
	अगर (fotg210->debug && !dbgp_reset_prep(fotg210_to_hcd(fotg210)))
		fotg210->debug = शून्य;

	command |= CMD_RESET;
	dbg_cmd(fotg210, "reset", command);
	fotg210_ग_लिखोl(fotg210, command, &fotg210->regs->command);
	fotg210->rh_state = FOTG210_RH_HALTED;
	fotg210->next_statechange = jअगरfies;
	retval = handshake(fotg210, &fotg210->regs->command,
			CMD_RESET, 0, 250 * 1000);

	अगर (retval)
		वापस retval;

	अगर (fotg210->debug)
		dbgp_बाह्यal_startup(fotg210_to_hcd(fotg210));

	fotg210->port_c_suspend = fotg210->suspended_ports =
			fotg210->resuming_ports = 0;
	वापस retval;
पूर्ण

/* Idle the controller (turn off the schedules).
 * Must be called with पूर्णांकerrupts enabled and the lock not held.
 */
अटल व्योम fotg210_quiesce(काष्ठा fotg210_hcd *fotg210)
अणु
	u32 temp;

	अगर (fotg210->rh_state != FOTG210_RH_RUNNING)
		वापस;

	/* रुको क्रम any schedule enables/disables to take effect */
	temp = (fotg210->command << 10) & (STS_ASS | STS_PSS);
	handshake(fotg210, &fotg210->regs->status, STS_ASS | STS_PSS, temp,
			16 * 125);

	/* then disable anything that's still active */
	spin_lock_irq(&fotg210->lock);
	fotg210->command &= ~(CMD_ASE | CMD_PSE);
	fotg210_ग_लिखोl(fotg210, fotg210->command, &fotg210->regs->command);
	spin_unlock_irq(&fotg210->lock);

	/* hardware can take 16 microframes to turn off ... */
	handshake(fotg210, &fotg210->regs->status, STS_ASS | STS_PSS, 0,
			16 * 125);
पूर्ण

अटल व्योम end_unlink_async(काष्ठा fotg210_hcd *fotg210);
अटल व्योम unlink_empty_async(काष्ठा fotg210_hcd *fotg210);
अटल व्योम fotg210_work(काष्ठा fotg210_hcd *fotg210);
अटल व्योम start_unlink_पूर्णांकr(काष्ठा fotg210_hcd *fotg210,
			      काष्ठा fotg210_qh *qh);
अटल व्योम end_unlink_पूर्णांकr(काष्ठा fotg210_hcd *fotg210, काष्ठा fotg210_qh *qh);

/* Set a bit in the USBCMD रेजिस्टर */
अटल व्योम fotg210_set_command_bit(काष्ठा fotg210_hcd *fotg210, u32 bit)
अणु
	fotg210->command |= bit;
	fotg210_ग_लिखोl(fotg210, fotg210->command, &fotg210->regs->command);

	/* unblock posted ग_लिखो */
	fotg210_पढ़ोl(fotg210, &fotg210->regs->command);
पूर्ण

/* Clear a bit in the USBCMD रेजिस्टर */
अटल व्योम fotg210_clear_command_bit(काष्ठा fotg210_hcd *fotg210, u32 bit)
अणु
	fotg210->command &= ~bit;
	fotg210_ग_लिखोl(fotg210, fotg210->command, &fotg210->regs->command);

	/* unblock posted ग_लिखो */
	fotg210_पढ़ोl(fotg210, &fotg210->regs->command);
पूर्ण

/* EHCI समयr support...  Now using hrसमयrs.
 *
 * Lots of dअगरferent events are triggered from fotg210->hrसमयr.  Whenever
 * the समयr routine runs, it checks each possible event; events that are
 * currently enabled and whose expiration समय has passed get handled.
 * The set of enabled events is stored as a collection of bitflags in
 * fotg210->enabled_hrसमयr_events, and they are numbered in order of
 * increasing delay values (ranging between 1 ms and 100 ms).
 *
 * Rather than implementing a sorted list or tree of all pending events,
 * we keep track only of the lowest-numbered pending event, in
 * fotg210->next_hrसमयr_event.  Whenever fotg210->hrसमयr माला_लो restarted, its
 * expiration समय is set to the समयout value क्रम this event.
 *
 * As a result, events might not get handled right away; the actual delay
 * could be anywhere up to twice the requested delay.  This करोesn't
 * matter, because none of the events are especially समय-critical.  The
 * ones that matter most all have a delay of 1 ms, so they will be
 * handled after 2 ms at most, which is okay.  In addition to this, we
 * allow क्रम an expiration range of 1 ms.
 */

/* Delay lengths क्रम the hrसमयr event types.
 * Keep this list sorted by delay length, in the same order as
 * the event types indexed by क्रमागत fotg210_hrसमयr_event in fotg210.h.
 */
अटल अचिन्हित event_delays_ns[] = अणु
	1 * NSEC_PER_MSEC,	/* FOTG210_HRTIMER_POLL_ASS */
	1 * NSEC_PER_MSEC,	/* FOTG210_HRTIMER_POLL_PSS */
	1 * NSEC_PER_MSEC,	/* FOTG210_HRTIMER_POLL_DEAD */
	1125 * NSEC_PER_USEC,	/* FOTG210_HRTIMER_UNLINK_INTR */
	2 * NSEC_PER_MSEC,	/* FOTG210_HRTIMER_FREE_ITDS */
	6 * NSEC_PER_MSEC,	/* FOTG210_HRTIMER_ASYNC_UNLINKS */
	10 * NSEC_PER_MSEC,	/* FOTG210_HRTIMER_IAA_WATCHDOG */
	10 * NSEC_PER_MSEC,	/* FOTG210_HRTIMER_DISABLE_PERIODIC */
	15 * NSEC_PER_MSEC,	/* FOTG210_HRTIMER_DISABLE_ASYNC */
	100 * NSEC_PER_MSEC,	/* FOTG210_HRTIMER_IO_WATCHDOG */
पूर्ण;

/* Enable a pending hrसमयr event */
अटल व्योम fotg210_enable_event(काष्ठा fotg210_hcd *fotg210, अचिन्हित event,
		bool resched)
अणु
	kसमय_प्रकार *समयout = &fotg210->hr_समयouts[event];

	अगर (resched)
		*समयout = kसमय_add(kसमय_get(), event_delays_ns[event]);
	fotg210->enabled_hrसमयr_events |= (1 << event);

	/* Track only the lowest-numbered pending event */
	अगर (event < fotg210->next_hrसमयr_event) अणु
		fotg210->next_hrसमयr_event = event;
		hrसमयr_start_range_ns(&fotg210->hrसमयr, *समयout,
				NSEC_PER_MSEC, HRTIMER_MODE_ABS);
	पूर्ण
पूर्ण


/* Poll the STS_ASS status bit; see when it agrees with CMD_ASE */
अटल व्योम fotg210_poll_ASS(काष्ठा fotg210_hcd *fotg210)
अणु
	अचिन्हित actual, want;

	/* Don't enable anything if the controller isn't running (e.g., died) */
	अगर (fotg210->rh_state != FOTG210_RH_RUNNING)
		वापस;

	want = (fotg210->command & CMD_ASE) ? STS_ASS : 0;
	actual = fotg210_पढ़ोl(fotg210, &fotg210->regs->status) & STS_ASS;

	अगर (want != actual) अणु

		/* Poll again later, but give up after about 20 ms */
		अगर (fotg210->ASS_poll_count++ < 20) अणु
			fotg210_enable_event(fotg210, FOTG210_HRTIMER_POLL_ASS,
					true);
			वापस;
		पूर्ण
		fotg210_dbg(fotg210, "Waited too long for the async schedule status (%x/%x), giving up\n",
				want, actual);
	पूर्ण
	fotg210->ASS_poll_count = 0;

	/* The status is up-to-date; restart or stop the schedule as needed */
	अगर (want == 0) अणु	/* Stopped */
		अगर (fotg210->async_count > 0)
			fotg210_set_command_bit(fotg210, CMD_ASE);

	पूर्ण अन्यथा अणु		/* Running */
		अगर (fotg210->async_count == 0) अणु

			/* Turn off the schedule after a जबतक */
			fotg210_enable_event(fotg210,
					FOTG210_HRTIMER_DISABLE_ASYNC,
					true);
		पूर्ण
	पूर्ण
पूर्ण

/* Turn off the async schedule after a brief delay */
अटल व्योम fotg210_disable_ASE(काष्ठा fotg210_hcd *fotg210)
अणु
	fotg210_clear_command_bit(fotg210, CMD_ASE);
पूर्ण


/* Poll the STS_PSS status bit; see when it agrees with CMD_PSE */
अटल व्योम fotg210_poll_PSS(काष्ठा fotg210_hcd *fotg210)
अणु
	अचिन्हित actual, want;

	/* Don't do anything if the controller isn't running (e.g., died) */
	अगर (fotg210->rh_state != FOTG210_RH_RUNNING)
		वापस;

	want = (fotg210->command & CMD_PSE) ? STS_PSS : 0;
	actual = fotg210_पढ़ोl(fotg210, &fotg210->regs->status) & STS_PSS;

	अगर (want != actual) अणु

		/* Poll again later, but give up after about 20 ms */
		अगर (fotg210->PSS_poll_count++ < 20) अणु
			fotg210_enable_event(fotg210, FOTG210_HRTIMER_POLL_PSS,
					true);
			वापस;
		पूर्ण
		fotg210_dbg(fotg210, "Waited too long for the periodic schedule status (%x/%x), giving up\n",
				want, actual);
	पूर्ण
	fotg210->PSS_poll_count = 0;

	/* The status is up-to-date; restart or stop the schedule as needed */
	अगर (want == 0) अणु	/* Stopped */
		अगर (fotg210->periodic_count > 0)
			fotg210_set_command_bit(fotg210, CMD_PSE);

	पूर्ण अन्यथा अणु		/* Running */
		अगर (fotg210->periodic_count == 0) अणु

			/* Turn off the schedule after a जबतक */
			fotg210_enable_event(fotg210,
					FOTG210_HRTIMER_DISABLE_PERIODIC,
					true);
		पूर्ण
	पूर्ण
पूर्ण

/* Turn off the periodic schedule after a brief delay */
अटल व्योम fotg210_disable_PSE(काष्ठा fotg210_hcd *fotg210)
अणु
	fotg210_clear_command_bit(fotg210, CMD_PSE);
पूर्ण


/* Poll the STS_HALT status bit; see when a dead controller stops */
अटल व्योम fotg210_handle_controller_death(काष्ठा fotg210_hcd *fotg210)
अणु
	अगर (!(fotg210_पढ़ोl(fotg210, &fotg210->regs->status) & STS_HALT)) अणु

		/* Give up after a few milliseconds */
		अगर (fotg210->died_poll_count++ < 5) अणु
			/* Try again later */
			fotg210_enable_event(fotg210,
					FOTG210_HRTIMER_POLL_DEAD, true);
			वापस;
		पूर्ण
		fotg210_warn(fotg210, "Waited too long for the controller to stop, giving up\n");
	पूर्ण

	/* Clean up the mess */
	fotg210->rh_state = FOTG210_RH_HALTED;
	fotg210_ग_लिखोl(fotg210, 0, &fotg210->regs->पूर्णांकr_enable);
	fotg210_work(fotg210);
	end_unlink_async(fotg210);

	/* Not in process context, so करोn't try to reset the controller */
पूर्ण


/* Handle unlinked पूर्णांकerrupt QHs once they are gone from the hardware */
अटल व्योम fotg210_handle_पूर्णांकr_unlinks(काष्ठा fotg210_hcd *fotg210)
अणु
	bool stopped = (fotg210->rh_state < FOTG210_RH_RUNNING);

	/*
	 * Process all the QHs on the पूर्णांकr_unlink list that were added
	 * beक्रमe the current unlink cycle began.  The list is in
	 * temporal order, so stop when we reach the first entry in the
	 * current cycle.  But अगर the root hub isn't running then
	 * process all the QHs on the list.
	 */
	fotg210->पूर्णांकr_unlinking = true;
	जबतक (fotg210->पूर्णांकr_unlink) अणु
		काष्ठा fotg210_qh *qh = fotg210->पूर्णांकr_unlink;

		अगर (!stopped && qh->unlink_cycle == fotg210->पूर्णांकr_unlink_cycle)
			अवरोध;
		fotg210->पूर्णांकr_unlink = qh->unlink_next;
		qh->unlink_next = शून्य;
		end_unlink_पूर्णांकr(fotg210, qh);
	पूर्ण

	/* Handle reमुख्यing entries later */
	अगर (fotg210->पूर्णांकr_unlink) अणु
		fotg210_enable_event(fotg210, FOTG210_HRTIMER_UNLINK_INTR,
				true);
		++fotg210->पूर्णांकr_unlink_cycle;
	पूर्ण
	fotg210->पूर्णांकr_unlinking = false;
पूर्ण


/* Start another मुक्त-iTDs/siTDs cycle */
अटल व्योम start_मुक्त_itds(काष्ठा fotg210_hcd *fotg210)
अणु
	अगर (!(fotg210->enabled_hrसमयr_events &
			BIT(FOTG210_HRTIMER_FREE_ITDS))) अणु
		fotg210->last_itd_to_मुक्त = list_entry(
				fotg210->cached_itd_list.prev,
				काष्ठा fotg210_itd, itd_list);
		fotg210_enable_event(fotg210, FOTG210_HRTIMER_FREE_ITDS, true);
	पूर्ण
पूर्ण

/* Wait क्रम controller to stop using old iTDs and siTDs */
अटल व्योम end_मुक्त_itds(काष्ठा fotg210_hcd *fotg210)
अणु
	काष्ठा fotg210_itd *itd, *n;

	अगर (fotg210->rh_state < FOTG210_RH_RUNNING)
		fotg210->last_itd_to_मुक्त = शून्य;

	list_क्रम_each_entry_safe(itd, n, &fotg210->cached_itd_list, itd_list) अणु
		list_del(&itd->itd_list);
		dma_pool_मुक्त(fotg210->itd_pool, itd, itd->itd_dma);
		अगर (itd == fotg210->last_itd_to_मुक्त)
			अवरोध;
	पूर्ण

	अगर (!list_empty(&fotg210->cached_itd_list))
		start_मुक्त_itds(fotg210);
पूर्ण


/* Handle lost (or very late) IAA पूर्णांकerrupts */
अटल व्योम fotg210_iaa_watchकरोg(काष्ठा fotg210_hcd *fotg210)
अणु
	अगर (fotg210->rh_state != FOTG210_RH_RUNNING)
		वापस;

	/*
	 * Lost IAA irqs wedge things badly; seen first with a vt8235.
	 * So we need this watchकरोg, but must protect it against both
	 * (a) SMP races against real IAA firing and retriggering, and
	 * (b) clean HC shutकरोwn, when IAA watchकरोg was pending.
	 */
	अगर (fotg210->async_iaa) अणु
		u32 cmd, status;

		/* If we get here, IAA is *REALLY* late.  It's barely
		 * conceivable that the प्रणाली is so busy that CMD_IAAD
		 * is still legitimately set, so let's be sure it's
		 * clear beक्रमe we पढ़ो STS_IAA.  (The HC should clear
		 * CMD_IAAD when it sets STS_IAA.)
		 */
		cmd = fotg210_पढ़ोl(fotg210, &fotg210->regs->command);

		/*
		 * If IAA is set here it either legitimately triggered
		 * after the watchकरोg समयr expired (_way_ late, so we'll
		 * still count it as lost) ... or a silicon erratum:
		 * - VIA seems to set IAA without triggering the IRQ;
		 * - IAAD potentially cleared without setting IAA.
		 */
		status = fotg210_पढ़ोl(fotg210, &fotg210->regs->status);
		अगर ((status & STS_IAA) || !(cmd & CMD_IAAD)) अणु
			INCR(fotg210->stats.lost_iaa);
			fotg210_ग_लिखोl(fotg210, STS_IAA,
					&fotg210->regs->status);
		पूर्ण

		fotg210_dbg(fotg210, "IAA watchdog: status %x cmd %x\n",
				status, cmd);
		end_unlink_async(fotg210);
	पूर्ण
पूर्ण


/* Enable the I/O watchकरोg, अगर appropriate */
अटल व्योम turn_on_io_watchकरोg(काष्ठा fotg210_hcd *fotg210)
अणु
	/* Not needed अगर the controller isn't running or it's alपढ़ोy enabled */
	अगर (fotg210->rh_state != FOTG210_RH_RUNNING ||
			(fotg210->enabled_hrसमयr_events &
			BIT(FOTG210_HRTIMER_IO_WATCHDOG)))
		वापस;

	/*
	 * Isochronous transfers always need the watchकरोg.
	 * For other sorts we use it only अगर the flag is set.
	 */
	अगर (fotg210->isoc_count > 0 || (fotg210->need_io_watchकरोg &&
			fotg210->async_count + fotg210->पूर्णांकr_count > 0))
		fotg210_enable_event(fotg210, FOTG210_HRTIMER_IO_WATCHDOG,
				true);
पूर्ण


/* Handler functions क्रम the hrसमयr event types.
 * Keep this array in the same order as the event types indexed by
 * क्रमागत fotg210_hrसमयr_event in fotg210.h.
 */
अटल व्योम (*event_handlers[])(काष्ठा fotg210_hcd *) = अणु
	fotg210_poll_ASS,			/* FOTG210_HRTIMER_POLL_ASS */
	fotg210_poll_PSS,			/* FOTG210_HRTIMER_POLL_PSS */
	fotg210_handle_controller_death,	/* FOTG210_HRTIMER_POLL_DEAD */
	fotg210_handle_पूर्णांकr_unlinks,	/* FOTG210_HRTIMER_UNLINK_INTR */
	end_मुक्त_itds,			/* FOTG210_HRTIMER_FREE_ITDS */
	unlink_empty_async,		/* FOTG210_HRTIMER_ASYNC_UNLINKS */
	fotg210_iaa_watchकरोg,		/* FOTG210_HRTIMER_IAA_WATCHDOG */
	fotg210_disable_PSE,		/* FOTG210_HRTIMER_DISABLE_PERIODIC */
	fotg210_disable_ASE,		/* FOTG210_HRTIMER_DISABLE_ASYNC */
	fotg210_work,			/* FOTG210_HRTIMER_IO_WATCHDOG */
पूर्ण;

अटल क्रमागत hrसमयr_restart fotg210_hrसमयr_func(काष्ठा hrसमयr *t)
अणु
	काष्ठा fotg210_hcd *fotg210 =
			container_of(t, काष्ठा fotg210_hcd, hrसमयr);
	kसमय_प्रकार now;
	अचिन्हित दीर्घ events;
	अचिन्हित दीर्घ flags;
	अचिन्हित e;

	spin_lock_irqsave(&fotg210->lock, flags);

	events = fotg210->enabled_hrसमयr_events;
	fotg210->enabled_hrसमयr_events = 0;
	fotg210->next_hrसमयr_event = FOTG210_HRTIMER_NO_EVENT;

	/*
	 * Check each pending event.  If its समय has expired, handle
	 * the event; otherwise re-enable it.
	 */
	now = kसमय_get();
	क्रम_each_set_bit(e, &events, FOTG210_HRTIMER_NUM_EVENTS) अणु
		अगर (kसमय_compare(now, fotg210->hr_समयouts[e]) >= 0)
			event_handlers[e](fotg210);
		अन्यथा
			fotg210_enable_event(fotg210, e, false);
	पूर्ण

	spin_unlock_irqrestore(&fotg210->lock, flags);
	वापस HRTIMER_NORESTART;
पूर्ण

#घोषणा fotg210_bus_suspend शून्य
#घोषणा fotg210_bus_resume शून्य

अटल पूर्णांक check_reset_complete(काष्ठा fotg210_hcd *fotg210, पूर्णांक index,
		u32 __iomem *status_reg, पूर्णांक port_status)
अणु
	अगर (!(port_status & PORT_CONNECT))
		वापस port_status;

	/* अगर reset finished and it's still not enabled -- hanकरोff */
	अगर (!(port_status & PORT_PE))
		/* with पूर्णांकegrated TT, there's nobody to hand it to! */
		fotg210_dbg(fotg210, "Failed to enable port %d on root hub TT\n",
				index + 1);
	अन्यथा
		fotg210_dbg(fotg210, "port %d reset complete, port enabled\n",
				index + 1);

	वापस port_status;
पूर्ण


/* build "status change" packet (one or two bytes) from HC रेजिस्टरs */

अटल पूर्णांक fotg210_hub_status_data(काष्ठा usb_hcd *hcd, अक्षर *buf)
अणु
	काष्ठा fotg210_hcd *fotg210 = hcd_to_fotg210(hcd);
	u32 temp, status;
	u32 mask;
	पूर्णांक retval = 1;
	अचिन्हित दीर्घ flags;

	/* init status to no-changes */
	buf[0] = 0;

	/* Inक्रमm the core about resumes-in-progress by वापसing
	 * a non-zero value even अगर there are no status changes.
	 */
	status = fotg210->resuming_ports;

	mask = PORT_CSC | PORT_PEC;
	/* PORT_RESUME from hardware ~= PORT_STAT_C_SUSPEND */

	/* no hub change reports (bit 0) क्रम now (घातer, ...) */

	/* port N changes (bit N)? */
	spin_lock_irqsave(&fotg210->lock, flags);

	temp = fotg210_पढ़ोl(fotg210, &fotg210->regs->port_status);

	/*
	 * Return status inक्रमmation even क्रम ports with OWNER set.
	 * Otherwise hub_wq wouldn't see the disconnect event when a
	 * high-speed device is चयनed over to the companion
	 * controller by the user.
	 */

	अगर ((temp & mask) != 0 || test_bit(0, &fotg210->port_c_suspend) ||
			(fotg210->reset_करोne[0] &&
			समय_after_eq(jअगरfies, fotg210->reset_करोne[0]))) अणु
		buf[0] |= 1 << 1;
		status = STS_PCD;
	पूर्ण
	/* FIXME स्वतःsuspend idle root hubs */
	spin_unlock_irqrestore(&fotg210->lock, flags);
	वापस status ? retval : 0;
पूर्ण

अटल व्योम fotg210_hub_descriptor(काष्ठा fotg210_hcd *fotg210,
		काष्ठा usb_hub_descriptor *desc)
अणु
	पूर्णांक ports = HCS_N_PORTS(fotg210->hcs_params);
	u16 temp;

	desc->bDescriptorType = USB_DT_HUB;
	desc->bPwrOn2PwrGood = 10;	/* fotg210 1.0, 2.3.9 says 20ms max */
	desc->bHubContrCurrent = 0;

	desc->bNbrPorts = ports;
	temp = 1 + (ports / 8);
	desc->bDescLength = 7 + 2 * temp;

	/* two biपंचांगaps:  ports removable, and usb 1.0 legacy PortPwrCtrlMask */
	स_रखो(&desc->u.hs.DeviceRemovable[0], 0, temp);
	स_रखो(&desc->u.hs.DeviceRemovable[temp], 0xff, temp);

	temp = HUB_CHAR_INDV_PORT_OCPM;	/* per-port overcurrent reporting */
	temp |= HUB_CHAR_NO_LPSM;	/* no घातer चयनing */
	desc->wHubCharacteristics = cpu_to_le16(temp);
पूर्ण

अटल पूर्णांक fotg210_hub_control(काष्ठा usb_hcd *hcd, u16 typeReq, u16 wValue,
		u16 wIndex, अक्षर *buf, u16 wLength)
अणु
	काष्ठा fotg210_hcd *fotg210 = hcd_to_fotg210(hcd);
	पूर्णांक ports = HCS_N_PORTS(fotg210->hcs_params);
	u32 __iomem *status_reg = &fotg210->regs->port_status;
	u32 temp, temp1, status;
	अचिन्हित दीर्घ flags;
	पूर्णांक retval = 0;
	अचिन्हित selector;

	/*
	 * FIXME:  support SetPortFeatures USB_PORT_FEAT_INDICATOR.
	 * HCS_INDICATOR may say we can change LEDs to off/amber/green.
	 * (track current state ourselves) ... blink क्रम diagnostics,
	 * घातer, "this is the one", etc.  EHCI spec supports this.
	 */

	spin_lock_irqsave(&fotg210->lock, flags);
	चयन (typeReq) अणु
	हाल ClearHubFeature:
		चयन (wValue) अणु
		हाल C_HUB_LOCAL_POWER:
		हाल C_HUB_OVER_CURRENT:
			/* no hub-wide feature/status flags */
			अवरोध;
		शेष:
			जाओ error;
		पूर्ण
		अवरोध;
	हाल ClearPortFeature:
		अगर (!wIndex || wIndex > ports)
			जाओ error;
		wIndex--;
		temp = fotg210_पढ़ोl(fotg210, status_reg);
		temp &= ~PORT_RWC_BITS;

		/*
		 * Even अगर OWNER is set, so the port is owned by the
		 * companion controller, hub_wq needs to be able to clear
		 * the port-change status bits (especially
		 * USB_PORT_STAT_C_CONNECTION).
		 */

		चयन (wValue) अणु
		हाल USB_PORT_FEAT_ENABLE:
			fotg210_ग_लिखोl(fotg210, temp & ~PORT_PE, status_reg);
			अवरोध;
		हाल USB_PORT_FEAT_C_ENABLE:
			fotg210_ग_लिखोl(fotg210, temp | PORT_PEC, status_reg);
			अवरोध;
		हाल USB_PORT_FEAT_SUSPEND:
			अगर (temp & PORT_RESET)
				जाओ error;
			अगर (!(temp & PORT_SUSPEND))
				अवरोध;
			अगर ((temp & PORT_PE) == 0)
				जाओ error;

			/* resume संकेतing क्रम 20 msec */
			fotg210_ग_लिखोl(fotg210, temp | PORT_RESUME, status_reg);
			fotg210->reset_करोne[wIndex] = jअगरfies
					+ msecs_to_jअगरfies(USB_RESUME_TIMEOUT);
			अवरोध;
		हाल USB_PORT_FEAT_C_SUSPEND:
			clear_bit(wIndex, &fotg210->port_c_suspend);
			अवरोध;
		हाल USB_PORT_FEAT_C_CONNECTION:
			fotg210_ग_लिखोl(fotg210, temp | PORT_CSC, status_reg);
			अवरोध;
		हाल USB_PORT_FEAT_C_OVER_CURRENT:
			fotg210_ग_लिखोl(fotg210, temp | OTGISR_OVC,
					&fotg210->regs->otgisr);
			अवरोध;
		हाल USB_PORT_FEAT_C_RESET:
			/* GetPortStatus clears reset */
			अवरोध;
		शेष:
			जाओ error;
		पूर्ण
		fotg210_पढ़ोl(fotg210, &fotg210->regs->command);
		अवरोध;
	हाल GetHubDescriptor:
		fotg210_hub_descriptor(fotg210, (काष्ठा usb_hub_descriptor *)
				buf);
		अवरोध;
	हाल GetHubStatus:
		/* no hub-wide feature/status flags */
		स_रखो(buf, 0, 4);
		/*cpu_to_le32s ((u32 *) buf); */
		अवरोध;
	हाल GetPortStatus:
		अगर (!wIndex || wIndex > ports)
			जाओ error;
		wIndex--;
		status = 0;
		temp = fotg210_पढ़ोl(fotg210, status_reg);

		/* wPortChange bits */
		अगर (temp & PORT_CSC)
			status |= USB_PORT_STAT_C_CONNECTION << 16;
		अगर (temp & PORT_PEC)
			status |= USB_PORT_STAT_C_ENABLE << 16;

		temp1 = fotg210_पढ़ोl(fotg210, &fotg210->regs->otgisr);
		अगर (temp1 & OTGISR_OVC)
			status |= USB_PORT_STAT_C_OVERCURRENT << 16;

		/* whoever resumes must GetPortStatus to complete it!! */
		अगर (temp & PORT_RESUME) अणु

			/* Remote Wakeup received? */
			अगर (!fotg210->reset_करोne[wIndex]) अणु
				/* resume संकेतing क्रम 20 msec */
				fotg210->reset_करोne[wIndex] = jअगरfies
						+ msecs_to_jअगरfies(20);
				/* check the port again */
				mod_समयr(&fotg210_to_hcd(fotg210)->rh_समयr,
						fotg210->reset_करोne[wIndex]);
			पूर्ण

			/* resume completed? */
			अन्यथा अगर (समय_after_eq(jअगरfies,
					fotg210->reset_करोne[wIndex])) अणु
				clear_bit(wIndex, &fotg210->suspended_ports);
				set_bit(wIndex, &fotg210->port_c_suspend);
				fotg210->reset_करोne[wIndex] = 0;

				/* stop resume संकेतing */
				temp = fotg210_पढ़ोl(fotg210, status_reg);
				fotg210_ग_लिखोl(fotg210, temp &
						~(PORT_RWC_BITS | PORT_RESUME),
						status_reg);
				clear_bit(wIndex, &fotg210->resuming_ports);
				retval = handshake(fotg210, status_reg,
						PORT_RESUME, 0, 2000);/* 2ms */
				अगर (retval != 0) अणु
					fotg210_err(fotg210,
							"port %d resume error %d\n",
							wIndex + 1, retval);
					जाओ error;
				पूर्ण
				temp &= ~(PORT_SUSPEND|PORT_RESUME|(3<<10));
			पूर्ण
		पूर्ण

		/* whoever resets must GetPortStatus to complete it!! */
		अगर ((temp & PORT_RESET) && समय_after_eq(jअगरfies,
				fotg210->reset_करोne[wIndex])) अणु
			status |= USB_PORT_STAT_C_RESET << 16;
			fotg210->reset_करोne[wIndex] = 0;
			clear_bit(wIndex, &fotg210->resuming_ports);

			/* क्रमce reset to complete */
			fotg210_ग_लिखोl(fotg210,
					temp & ~(PORT_RWC_BITS | PORT_RESET),
					status_reg);
			/* REVISIT:  some hardware needs 550+ usec to clear
			 * this bit; seems too दीर्घ to spin routinely...
			 */
			retval = handshake(fotg210, status_reg,
					PORT_RESET, 0, 1000);
			अगर (retval != 0) अणु
				fotg210_err(fotg210, "port %d reset error %d\n",
						wIndex + 1, retval);
				जाओ error;
			पूर्ण

			/* see what we found out */
			temp = check_reset_complete(fotg210, wIndex, status_reg,
					fotg210_पढ़ोl(fotg210, status_reg));

			/* restart schedule */
			fotg210->command |= CMD_RUN;
			fotg210_ग_लिखोl(fotg210, fotg210->command, &fotg210->regs->command);
		पूर्ण

		अगर (!(temp & (PORT_RESUME|PORT_RESET))) अणु
			fotg210->reset_करोne[wIndex] = 0;
			clear_bit(wIndex, &fotg210->resuming_ports);
		पूर्ण

		/* transfer dedicated ports to the companion hc */
		अगर ((temp & PORT_CONNECT) &&
				test_bit(wIndex, &fotg210->companion_ports)) अणु
			temp &= ~PORT_RWC_BITS;
			fotg210_ग_लिखोl(fotg210, temp, status_reg);
			fotg210_dbg(fotg210, "port %d --> companion\n",
					wIndex + 1);
			temp = fotg210_पढ़ोl(fotg210, status_reg);
		पूर्ण

		/*
		 * Even अगर OWNER is set, there's no harm letting hub_wq
		 * see the wPortStatus values (they should all be 0 except
		 * क्रम PORT_POWER anyway).
		 */

		अगर (temp & PORT_CONNECT) अणु
			status |= USB_PORT_STAT_CONNECTION;
			status |= fotg210_port_speed(fotg210, temp);
		पूर्ण
		अगर (temp & PORT_PE)
			status |= USB_PORT_STAT_ENABLE;

		/* maybe the port was unsuspended without our knowledge */
		अगर (temp & (PORT_SUSPEND|PORT_RESUME)) अणु
			status |= USB_PORT_STAT_SUSPEND;
		पूर्ण अन्यथा अगर (test_bit(wIndex, &fotg210->suspended_ports)) अणु
			clear_bit(wIndex, &fotg210->suspended_ports);
			clear_bit(wIndex, &fotg210->resuming_ports);
			fotg210->reset_करोne[wIndex] = 0;
			अगर (temp & PORT_PE)
				set_bit(wIndex, &fotg210->port_c_suspend);
		पूर्ण

		temp1 = fotg210_पढ़ोl(fotg210, &fotg210->regs->otgisr);
		अगर (temp1 & OTGISR_OVC)
			status |= USB_PORT_STAT_OVERCURRENT;
		अगर (temp & PORT_RESET)
			status |= USB_PORT_STAT_RESET;
		अगर (test_bit(wIndex, &fotg210->port_c_suspend))
			status |= USB_PORT_STAT_C_SUSPEND << 16;

		अगर (status & ~0xffff)	/* only अगर wPortChange is पूर्णांकeresting */
			dbg_port(fotg210, "GetStatus", wIndex + 1, temp);
		put_unaligned_le32(status, buf);
		अवरोध;
	हाल SetHubFeature:
		चयन (wValue) अणु
		हाल C_HUB_LOCAL_POWER:
		हाल C_HUB_OVER_CURRENT:
			/* no hub-wide feature/status flags */
			अवरोध;
		शेष:
			जाओ error;
		पूर्ण
		अवरोध;
	हाल SetPortFeature:
		selector = wIndex >> 8;
		wIndex &= 0xff;

		अगर (!wIndex || wIndex > ports)
			जाओ error;
		wIndex--;
		temp = fotg210_पढ़ोl(fotg210, status_reg);
		temp &= ~PORT_RWC_BITS;
		चयन (wValue) अणु
		हाल USB_PORT_FEAT_SUSPEND:
			अगर ((temp & PORT_PE) == 0
					|| (temp & PORT_RESET) != 0)
				जाओ error;

			/* After above check the port must be connected.
			 * Set appropriate bit thus could put phy पूर्णांकo low घातer
			 * mode अगर we have hostpc feature
			 */
			fotg210_ग_लिखोl(fotg210, temp | PORT_SUSPEND,
					status_reg);
			set_bit(wIndex, &fotg210->suspended_ports);
			अवरोध;
		हाल USB_PORT_FEAT_RESET:
			अगर (temp & PORT_RESUME)
				जाओ error;
			/* line status bits may report this as low speed,
			 * which can be fine अगर this root hub has a
			 * transaction translator built in.
			 */
			fotg210_dbg(fotg210, "port %d reset\n", wIndex + 1);
			temp |= PORT_RESET;
			temp &= ~PORT_PE;

			/*
			 * caller must रुको, then call GetPortStatus
			 * usb 2.0 spec says 50 ms resets on root
			 */
			fotg210->reset_करोne[wIndex] = jअगरfies
					+ msecs_to_jअगरfies(50);
			fotg210_ग_लिखोl(fotg210, temp, status_reg);
			अवरोध;

		/* For करोwnstream facing ports (these):  one hub port is put
		 * पूर्णांकo test mode according to USB2 11.24.2.13, then the hub
		 * must be reset (which क्रम root hub now means rmmod+modprobe,
		 * or अन्यथा प्रणाली reboot).  See EHCI 2.3.9 and 4.14 क्रम info
		 * about the EHCI-specअगरic stuff.
		 */
		हाल USB_PORT_FEAT_TEST:
			अगर (!selector || selector > 5)
				जाओ error;
			spin_unlock_irqrestore(&fotg210->lock, flags);
			fotg210_quiesce(fotg210);
			spin_lock_irqsave(&fotg210->lock, flags);

			/* Put all enabled ports पूर्णांकo suspend */
			temp = fotg210_पढ़ोl(fotg210, status_reg) &
				~PORT_RWC_BITS;
			अगर (temp & PORT_PE)
				fotg210_ग_लिखोl(fotg210, temp | PORT_SUSPEND,
						status_reg);

			spin_unlock_irqrestore(&fotg210->lock, flags);
			fotg210_halt(fotg210);
			spin_lock_irqsave(&fotg210->lock, flags);

			temp = fotg210_पढ़ोl(fotg210, status_reg);
			temp |= selector << 16;
			fotg210_ग_लिखोl(fotg210, temp, status_reg);
			अवरोध;

		शेष:
			जाओ error;
		पूर्ण
		fotg210_पढ़ोl(fotg210, &fotg210->regs->command);
		अवरोध;

	शेष:
error:
		/* "stall" on error */
		retval = -EPIPE;
	पूर्ण
	spin_unlock_irqrestore(&fotg210->lock, flags);
	वापस retval;
पूर्ण

अटल व्योम __maybe_unused fotg210_relinquish_port(काष्ठा usb_hcd *hcd,
		पूर्णांक portnum)
अणु
	वापस;
पूर्ण

अटल पूर्णांक __maybe_unused fotg210_port_handed_over(काष्ठा usb_hcd *hcd,
		पूर्णांक portnum)
अणु
	वापस 0;
पूर्ण

/* There's basically three types of memory:
 *	- data used only by the HCD ... kदो_स्मृति is fine
 *	- async and periodic schedules, shared by HC and HCD ... these
 *	  need to use dma_pool or dma_alloc_coherent
 *	- driver buffers, पढ़ो/written by HC ... single shot DMA mapped
 *
 * There's also "register" data (e.g. PCI or SOC), which is memory mapped.
 * No memory seen by this driver is pageable.
 */

/* Allocate the key transfer काष्ठाures from the previously allocated pool */
अटल अंतरभूत व्योम fotg210_qtd_init(काष्ठा fotg210_hcd *fotg210,
		काष्ठा fotg210_qtd *qtd, dma_addr_t dma)
अणु
	स_रखो(qtd, 0, माप(*qtd));
	qtd->qtd_dma = dma;
	qtd->hw_token = cpu_to_hc32(fotg210, QTD_STS_HALT);
	qtd->hw_next = FOTG210_LIST_END(fotg210);
	qtd->hw_alt_next = FOTG210_LIST_END(fotg210);
	INIT_LIST_HEAD(&qtd->qtd_list);
पूर्ण

अटल काष्ठा fotg210_qtd *fotg210_qtd_alloc(काष्ठा fotg210_hcd *fotg210,
		gfp_t flags)
अणु
	काष्ठा fotg210_qtd *qtd;
	dma_addr_t dma;

	qtd = dma_pool_alloc(fotg210->qtd_pool, flags, &dma);
	अगर (qtd != शून्य)
		fotg210_qtd_init(fotg210, qtd, dma);

	वापस qtd;
पूर्ण

अटल अंतरभूत व्योम fotg210_qtd_मुक्त(काष्ठा fotg210_hcd *fotg210,
		काष्ठा fotg210_qtd *qtd)
अणु
	dma_pool_मुक्त(fotg210->qtd_pool, qtd, qtd->qtd_dma);
पूर्ण


अटल व्योम qh_destroy(काष्ठा fotg210_hcd *fotg210, काष्ठा fotg210_qh *qh)
अणु
	/* clean qtds first, and know this is not linked */
	अगर (!list_empty(&qh->qtd_list) || qh->qh_next.ptr) अणु
		fotg210_dbg(fotg210, "unused qh not empty!\n");
		BUG();
	पूर्ण
	अगर (qh->dummy)
		fotg210_qtd_मुक्त(fotg210, qh->dummy);
	dma_pool_मुक्त(fotg210->qh_pool, qh->hw, qh->qh_dma);
	kमुक्त(qh);
पूर्ण

अटल काष्ठा fotg210_qh *fotg210_qh_alloc(काष्ठा fotg210_hcd *fotg210,
		gfp_t flags)
अणु
	काष्ठा fotg210_qh *qh;
	dma_addr_t dma;

	qh = kzalloc(माप(*qh), GFP_ATOMIC);
	अगर (!qh)
		जाओ करोne;
	qh->hw = dma_pool_zalloc(fotg210->qh_pool, flags, &dma);
	अगर (!qh->hw)
		जाओ fail;
	qh->qh_dma = dma;
	INIT_LIST_HEAD(&qh->qtd_list);

	/* dummy td enables safe urb queuing */
	qh->dummy = fotg210_qtd_alloc(fotg210, flags);
	अगर (qh->dummy == शून्य) अणु
		fotg210_dbg(fotg210, "no dummy td\n");
		जाओ fail1;
	पूर्ण
करोne:
	वापस qh;
fail1:
	dma_pool_मुक्त(fotg210->qh_pool, qh->hw, qh->qh_dma);
fail:
	kमुक्त(qh);
	वापस शून्य;
पूर्ण

/* The queue heads and transfer descriptors are managed from pools tied
 * to each of the "per device" काष्ठाures.
 * This is the initialisation and cleanup code.
 */

अटल व्योम fotg210_mem_cleanup(काष्ठा fotg210_hcd *fotg210)
अणु
	अगर (fotg210->async)
		qh_destroy(fotg210, fotg210->async);
	fotg210->async = शून्य;

	अगर (fotg210->dummy)
		qh_destroy(fotg210, fotg210->dummy);
	fotg210->dummy = शून्य;

	/* DMA consistent memory and pools */
	dma_pool_destroy(fotg210->qtd_pool);
	fotg210->qtd_pool = शून्य;

	dma_pool_destroy(fotg210->qh_pool);
	fotg210->qh_pool = शून्य;

	dma_pool_destroy(fotg210->itd_pool);
	fotg210->itd_pool = शून्य;

	अगर (fotg210->periodic)
		dma_मुक्त_coherent(fotg210_to_hcd(fotg210)->self.controller,
				fotg210->periodic_size * माप(u32),
				fotg210->periodic, fotg210->periodic_dma);
	fotg210->periodic = शून्य;

	/* shaकरोw periodic table */
	kमुक्त(fotg210->pshaकरोw);
	fotg210->pshaकरोw = शून्य;
पूर्ण

/* remember to add cleanup code (above) अगर you add anything here */
अटल पूर्णांक fotg210_mem_init(काष्ठा fotg210_hcd *fotg210, gfp_t flags)
अणु
	पूर्णांक i;

	/* QTDs क्रम control/bulk/पूर्णांकr transfers */
	fotg210->qtd_pool = dma_pool_create("fotg210_qtd",
			fotg210_to_hcd(fotg210)->self.controller,
			माप(काष्ठा fotg210_qtd),
			32 /* byte alignment (क्रम hw parts) */,
			4096 /* can't cross 4K */);
	अगर (!fotg210->qtd_pool)
		जाओ fail;

	/* QHs क्रम control/bulk/पूर्णांकr transfers */
	fotg210->qh_pool = dma_pool_create("fotg210_qh",
			fotg210_to_hcd(fotg210)->self.controller,
			माप(काष्ठा fotg210_qh_hw),
			32 /* byte alignment (क्रम hw parts) */,
			4096 /* can't cross 4K */);
	अगर (!fotg210->qh_pool)
		जाओ fail;

	fotg210->async = fotg210_qh_alloc(fotg210, flags);
	अगर (!fotg210->async)
		जाओ fail;

	/* ITD क्रम high speed ISO transfers */
	fotg210->itd_pool = dma_pool_create("fotg210_itd",
			fotg210_to_hcd(fotg210)->self.controller,
			माप(काष्ठा fotg210_itd),
			64 /* byte alignment (क्रम hw parts) */,
			4096 /* can't cross 4K */);
	अगर (!fotg210->itd_pool)
		जाओ fail;

	/* Hardware periodic table */
	fotg210->periodic =
		dma_alloc_coherent(fotg210_to_hcd(fotg210)->self.controller,
				fotg210->periodic_size * माप(__le32),
				&fotg210->periodic_dma, 0);
	अगर (fotg210->periodic == शून्य)
		जाओ fail;

	क्रम (i = 0; i < fotg210->periodic_size; i++)
		fotg210->periodic[i] = FOTG210_LIST_END(fotg210);

	/* software shaकरोw of hardware table */
	fotg210->pshaकरोw = kसुस्मृति(fotg210->periodic_size, माप(व्योम *),
			flags);
	अगर (fotg210->pshaकरोw != शून्य)
		वापस 0;

fail:
	fotg210_dbg(fotg210, "couldn't init memory\n");
	fotg210_mem_cleanup(fotg210);
	वापस -ENOMEM;
पूर्ण
/* EHCI hardware queue manipulation ... the core.  QH/QTD manipulation.
 *
 * Control, bulk, and पूर्णांकerrupt traffic all use "qh" lists.  They list "qtd"
 * entries describing USB transactions, max 16-20kB/entry (with 4kB-aligned
 * buffers needed क्रम the larger number).  We use one QH per endpoपूर्णांक, queue
 * multiple urbs (all three types) per endpoपूर्णांक.  URBs may need several qtds.
 *
 * ISO traffic uses "ISO TD" (itd) records, and (aदीर्घ with
 * पूर्णांकerrupts) needs careful scheduling.  Perक्रमmance improvements can be
 * an ongoing challenge.  That's in "ehci-sched.c".
 *
 * USB 1.1 devices are handled (a) by "companion" OHCI or UHCI root hubs,
 * or otherwise through transaction translators (TTs) in USB 2.0 hubs using
 * (b) special fields in qh entries or (c) split iso entries.  TTs will
 * buffer low/full speed data so the host collects it at high speed.
 */

/* fill a qtd, वापसing how much of the buffer we were able to queue up */
अटल पूर्णांक qtd_fill(काष्ठा fotg210_hcd *fotg210, काष्ठा fotg210_qtd *qtd,
		dma_addr_t buf, माप_प्रकार len, पूर्णांक token, पूर्णांक maxpacket)
अणु
	पूर्णांक i, count;
	u64 addr = buf;

	/* one buffer entry per 4K ... first might be लघु or unaligned */
	qtd->hw_buf[0] = cpu_to_hc32(fotg210, (u32)addr);
	qtd->hw_buf_hi[0] = cpu_to_hc32(fotg210, (u32)(addr >> 32));
	count = 0x1000 - (buf & 0x0fff);	/* rest of that page */
	अगर (likely(len < count))		/* ... अगरf needed */
		count = len;
	अन्यथा अणु
		buf +=  0x1000;
		buf &= ~0x0fff;

		/* per-qtd limit: from 16K to 20K (best alignment) */
		क्रम (i = 1; count < len && i < 5; i++) अणु
			addr = buf;
			qtd->hw_buf[i] = cpu_to_hc32(fotg210, (u32)addr);
			qtd->hw_buf_hi[i] = cpu_to_hc32(fotg210,
					(u32)(addr >> 32));
			buf += 0x1000;
			अगर ((count + 0x1000) < len)
				count += 0x1000;
			अन्यथा
				count = len;
		पूर्ण

		/* लघु packets may only terminate transfers */
		अगर (count != len)
			count -= (count % maxpacket);
	पूर्ण
	qtd->hw_token = cpu_to_hc32(fotg210, (count << 16) | token);
	qtd->length = count;

	वापस count;
पूर्ण

अटल अंतरभूत व्योम qh_update(काष्ठा fotg210_hcd *fotg210,
		काष्ठा fotg210_qh *qh, काष्ठा fotg210_qtd *qtd)
अणु
	काष्ठा fotg210_qh_hw *hw = qh->hw;

	/* ग_लिखोs to an active overlay are unsafe */
	BUG_ON(qh->qh_state != QH_STATE_IDLE);

	hw->hw_qtd_next = QTD_NEXT(fotg210, qtd->qtd_dma);
	hw->hw_alt_next = FOTG210_LIST_END(fotg210);

	/* Except क्रम control endpoपूर्णांकs, we make hardware मुख्यtain data
	 * toggle (like OHCI) ... here (re)initialize the toggle in the QH,
	 * and set the pseuकरो-toggle in udev. Only usb_clear_halt() will
	 * ever clear it.
	 */
	अगर (!(hw->hw_info1 & cpu_to_hc32(fotg210, QH_TOGGLE_CTL))) अणु
		अचिन्हित is_out, epnum;

		is_out = qh->is_out;
		epnum = (hc32_to_cpup(fotg210, &hw->hw_info1) >> 8) & 0x0f;
		अगर (unlikely(!usb_gettoggle(qh->dev, epnum, is_out))) अणु
			hw->hw_token &= ~cpu_to_hc32(fotg210, QTD_TOGGLE);
			usb_settoggle(qh->dev, epnum, is_out, 1);
		पूर्ण
	पूर्ण

	hw->hw_token &= cpu_to_hc32(fotg210, QTD_TOGGLE | QTD_STS_PING);
पूर्ण

/* अगर it weren't क्रम a common silicon quirk (writing the dummy पूर्णांकo the qh
 * overlay, so qh->hw_token wrongly becomes inactive/halted), only fault
 * recovery (including urb dequeue) would need software changes to a QH...
 */
अटल व्योम qh_refresh(काष्ठा fotg210_hcd *fotg210, काष्ठा fotg210_qh *qh)
अणु
	काष्ठा fotg210_qtd *qtd;

	अगर (list_empty(&qh->qtd_list))
		qtd = qh->dummy;
	अन्यथा अणु
		qtd = list_entry(qh->qtd_list.next,
				काष्ठा fotg210_qtd, qtd_list);
		/*
		 * first qtd may alपढ़ोy be partially processed.
		 * If we come here during unlink, the QH overlay region
		 * might have reference to the just unlinked qtd. The
		 * qtd is updated in qh_completions(). Update the QH
		 * overlay here.
		 */
		अगर (cpu_to_hc32(fotg210, qtd->qtd_dma) == qh->hw->hw_current) अणु
			qh->hw->hw_qtd_next = qtd->hw_next;
			qtd = शून्य;
		पूर्ण
	पूर्ण

	अगर (qtd)
		qh_update(fotg210, qh, qtd);
पूर्ण

अटल व्योम qh_link_async(काष्ठा fotg210_hcd *fotg210, काष्ठा fotg210_qh *qh);

अटल व्योम fotg210_clear_tt_buffer_complete(काष्ठा usb_hcd *hcd,
		काष्ठा usb_host_endpoपूर्णांक *ep)
अणु
	काष्ठा fotg210_hcd *fotg210 = hcd_to_fotg210(hcd);
	काष्ठा fotg210_qh *qh = ep->hcpriv;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&fotg210->lock, flags);
	qh->clearing_tt = 0;
	अगर (qh->qh_state == QH_STATE_IDLE && !list_empty(&qh->qtd_list)
			&& fotg210->rh_state == FOTG210_RH_RUNNING)
		qh_link_async(fotg210, qh);
	spin_unlock_irqrestore(&fotg210->lock, flags);
पूर्ण

अटल व्योम fotg210_clear_tt_buffer(काष्ठा fotg210_hcd *fotg210,
		काष्ठा fotg210_qh *qh, काष्ठा urb *urb, u32 token)
अणु

	/* If an async split transaction माला_लो an error or is unlinked,
	 * the TT buffer may be left in an indeterminate state.  We
	 * have to clear the TT buffer.
	 *
	 * Note: this routine is never called क्रम Isochronous transfers.
	 */
	अगर (urb->dev->tt && !usb_pipeपूर्णांक(urb->pipe) && !qh->clearing_tt) अणु
		काष्ठा usb_device *tt = urb->dev->tt->hub;

		dev_dbg(&tt->dev,
				"clear tt buffer port %d, a%d ep%d t%08x\n",
				urb->dev->ttport, urb->dev->devnum,
				usb_pipeendpoपूर्णांक(urb->pipe), token);

		अगर (urb->dev->tt->hub !=
				fotg210_to_hcd(fotg210)->self.root_hub) अणु
			अगर (usb_hub_clear_tt_buffer(urb) == 0)
				qh->clearing_tt = 1;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक qtd_copy_status(काष्ठा fotg210_hcd *fotg210, काष्ठा urb *urb,
		माप_प्रकार length, u32 token)
अणु
	पूर्णांक status = -EINPROGRESS;

	/* count IN/OUT bytes, not SETUP (even लघु packets) */
	अगर (likely(QTD_PID(token) != 2))
		urb->actual_length += length - QTD_LENGTH(token);

	/* करोn't modअगरy error codes */
	अगर (unlikely(urb->unlinked))
		वापस status;

	/* क्रमce cleanup after लघु पढ़ो; not always an error */
	अगर (unlikely(IS_SHORT_READ(token)))
		status = -EREMOTEIO;

	/* serious "can't proceed" faults reported by the hardware */
	अगर (token & QTD_STS_HALT) अणु
		अगर (token & QTD_STS_BABBLE) अणु
			/* FIXME "must" disable babbling device's port too */
			status = -EOVERFLOW;
		/* CERR nonzero + halt --> stall */
		पूर्ण अन्यथा अगर (QTD_CERR(token)) अणु
			status = -EPIPE;

		/* In theory, more than one of the following bits can be set
		 * since they are sticky and the transaction is retried.
		 * Which to test first is rather arbitrary.
		 */
		पूर्ण अन्यथा अगर (token & QTD_STS_MMF) अणु
			/* fs/ls पूर्णांकerrupt xfer missed the complete-split */
			status = -EPROTO;
		पूर्ण अन्यथा अगर (token & QTD_STS_DBE) अणु
			status = (QTD_PID(token) == 1) /* IN ? */
				? -ENOSR  /* hc couldn't पढ़ो data */
				: -ECOMM; /* hc couldn't ग_लिखो data */
		पूर्ण अन्यथा अगर (token & QTD_STS_XACT) अणु
			/* समयout, bad CRC, wrong PID, etc */
			fotg210_dbg(fotg210, "devpath %s ep%d%s 3strikes\n",
					urb->dev->devpath,
					usb_pipeendpoपूर्णांक(urb->pipe),
					usb_pipein(urb->pipe) ? "in" : "out");
			status = -EPROTO;
		पूर्ण अन्यथा अणु	/* unknown */
			status = -EPROTO;
		पूर्ण

		fotg210_dbg(fotg210,
				"dev%d ep%d%s qtd token %08x --> status %d\n",
				usb_pipedevice(urb->pipe),
				usb_pipeendpoपूर्णांक(urb->pipe),
				usb_pipein(urb->pipe) ? "in" : "out",
				token, status);
	पूर्ण

	वापस status;
पूर्ण

अटल व्योम fotg210_urb_करोne(काष्ठा fotg210_hcd *fotg210, काष्ठा urb *urb,
		पूर्णांक status)
__releases(fotg210->lock)
__acquires(fotg210->lock)
अणु
	अगर (likely(urb->hcpriv != शून्य)) अणु
		काष्ठा fotg210_qh *qh = (काष्ठा fotg210_qh *) urb->hcpriv;

		/* S-mask in a QH means it's an पूर्णांकerrupt urb */
		अगर ((qh->hw->hw_info2 & cpu_to_hc32(fotg210, QH_SMASK)) != 0) अणु

			/* ... update hc-wide periodic stats (क्रम usbfs) */
			fotg210_to_hcd(fotg210)->self.bandwidth_पूर्णांक_reqs--;
		पूर्ण
	पूर्ण

	अगर (unlikely(urb->unlinked)) अणु
		INCR(fotg210->stats.unlink);
	पूर्ण अन्यथा अणु
		/* report non-error and लघु पढ़ो status as zero */
		अगर (status == -EINPROGRESS || status == -EREMOTEIO)
			status = 0;
		INCR(fotg210->stats.complete);
	पूर्ण

#अगर_घोषित FOTG210_URB_TRACE
	fotg210_dbg(fotg210,
			"%s %s urb %p ep%d%s status %d len %d/%d\n",
			__func__, urb->dev->devpath, urb,
			usb_pipeendpoपूर्णांक(urb->pipe),
			usb_pipein(urb->pipe) ? "in" : "out",
			status,
			urb->actual_length, urb->transfer_buffer_length);
#पूर्ण_अगर

	/* complete() can reenter this HCD */
	usb_hcd_unlink_urb_from_ep(fotg210_to_hcd(fotg210), urb);
	spin_unlock(&fotg210->lock);
	usb_hcd_giveback_urb(fotg210_to_hcd(fotg210), urb, status);
	spin_lock(&fotg210->lock);
पूर्ण

अटल पूर्णांक qh_schedule(काष्ठा fotg210_hcd *fotg210, काष्ठा fotg210_qh *qh);

/* Process and मुक्त completed qtds क्रम a qh, वापसing URBs to drivers.
 * Chases up to qh->hw_current.  Returns number of completions called,
 * indicating how much "real" work we did.
 */
अटल अचिन्हित qh_completions(काष्ठा fotg210_hcd *fotg210,
		काष्ठा fotg210_qh *qh)
अणु
	काष्ठा fotg210_qtd *last, *end = qh->dummy;
	काष्ठा fotg210_qtd *qtd, *पंचांगp;
	पूर्णांक last_status;
	पूर्णांक stopped;
	अचिन्हित count = 0;
	u8 state;
	काष्ठा fotg210_qh_hw *hw = qh->hw;

	अगर (unlikely(list_empty(&qh->qtd_list)))
		वापस count;

	/* completions (or tasks on other cpus) must never clobber HALT
	 * till we've gone through and cleaned everything up, even when
	 * they add urbs to this qh's queue or mark them क्रम unlinking.
	 *
	 * NOTE:  unlinking expects to be करोne in queue order.
	 *
	 * It's a bug क्रम qh->qh_state to be anything other than
	 * QH_STATE_IDLE, unless our caller is scan_async() or
	 * scan_पूर्णांकr().
	 */
	state = qh->qh_state;
	qh->qh_state = QH_STATE_COMPLETING;
	stopped = (state == QH_STATE_IDLE);

rescan:
	last = शून्य;
	last_status = -EINPROGRESS;
	qh->needs_rescan = 0;

	/* हटाओ de-activated QTDs from front of queue.
	 * after faults (including लघु पढ़ोs), cleanup this urb
	 * then let the queue advance.
	 * अगर queue is stopped, handles unlinks.
	 */
	list_क्रम_each_entry_safe(qtd, पंचांगp, &qh->qtd_list, qtd_list) अणु
		काष्ठा urb *urb;
		u32 token = 0;

		urb = qtd->urb;

		/* clean up any state from previous QTD ...*/
		अगर (last) अणु
			अगर (likely(last->urb != urb)) अणु
				fotg210_urb_करोne(fotg210, last->urb,
						last_status);
				count++;
				last_status = -EINPROGRESS;
			पूर्ण
			fotg210_qtd_मुक्त(fotg210, last);
			last = शून्य;
		पूर्ण

		/* ignore urbs submitted during completions we reported */
		अगर (qtd == end)
			अवरोध;

		/* hardware copies qtd out of qh overlay */
		rmb();
		token = hc32_to_cpu(fotg210, qtd->hw_token);

		/* always clean up qtds the hc de-activated */
retry_xacterr:
		अगर ((token & QTD_STS_ACTIVE) == 0) अणु

			/* Report Data Buffer Error: non-fatal but useful */
			अगर (token & QTD_STS_DBE)
				fotg210_dbg(fotg210,
					"detected DataBufferErr for urb %p ep%d%s len %d, qtd %p [qh %p]\n",
					urb, usb_endpoपूर्णांक_num(&urb->ep->desc),
					usb_endpoपूर्णांक_dir_in(&urb->ep->desc)
						? "in" : "out",
					urb->transfer_buffer_length, qtd, qh);

			/* on STALL, error, and लघु पढ़ोs this urb must
			 * complete and all its qtds must be recycled.
			 */
			अगर ((token & QTD_STS_HALT) != 0) अणु

				/* retry transaction errors until we
				 * reach the software xacterr limit
				 */
				अगर ((token & QTD_STS_XACT) &&
						QTD_CERR(token) == 0 &&
						++qh->xacterrs < QH_XACTERR_MAX &&
						!urb->unlinked) अणु
					fotg210_dbg(fotg210,
						"detected XactErr len %zu/%zu retry %d\n",
						qtd->length - QTD_LENGTH(token),
						qtd->length,
						qh->xacterrs);

					/* reset the token in the qtd and the
					 * qh overlay (which still contains
					 * the qtd) so that we pick up from
					 * where we left off
					 */
					token &= ~QTD_STS_HALT;
					token |= QTD_STS_ACTIVE |
						 (FOTG210_TUNE_CERR << 10);
					qtd->hw_token = cpu_to_hc32(fotg210,
							token);
					wmb();
					hw->hw_token = cpu_to_hc32(fotg210,
							token);
					जाओ retry_xacterr;
				पूर्ण
				stopped = 1;

			/* magic dummy क्रम some लघु पढ़ोs; qh won't advance.
			 * that silicon quirk can kick in with this dummy too.
			 *
			 * other लघु पढ़ोs won't stop the queue, including
			 * control transfers (status stage handles that) or
			 * most other single-qtd पढ़ोs ... the queue stops अगर
			 * URB_SHORT_NOT_OK was set so the driver submitting
			 * the urbs could clean it up.
			 */
			पूर्ण अन्यथा अगर (IS_SHORT_READ(token) &&
					!(qtd->hw_alt_next &
					FOTG210_LIST_END(fotg210))) अणु
				stopped = 1;
			पूर्ण

		/* stop scanning when we reach qtds the hc is using */
		पूर्ण अन्यथा अगर (likely(!stopped
				&& fotg210->rh_state >= FOTG210_RH_RUNNING)) अणु
			अवरोध;

		/* scan the whole queue क्रम unlinks whenever it stops */
		पूर्ण अन्यथा अणु
			stopped = 1;

			/* cancel everything अगर we halt, suspend, etc */
			अगर (fotg210->rh_state < FOTG210_RH_RUNNING)
				last_status = -ESHUTDOWN;

			/* this qtd is active; skip it unless a previous qtd
			 * क्रम its urb faulted, or its urb was canceled.
			 */
			अन्यथा अगर (last_status == -EINPROGRESS && !urb->unlinked)
				जारी;

			/* qh unlinked; token in overlay may be most current */
			अगर (state == QH_STATE_IDLE &&
					cpu_to_hc32(fotg210, qtd->qtd_dma)
					== hw->hw_current) अणु
				token = hc32_to_cpu(fotg210, hw->hw_token);

				/* An unlink may leave an incomplete
				 * async transaction in the TT buffer.
				 * We have to clear it.
				 */
				fotg210_clear_tt_buffer(fotg210, qh, urb,
						token);
			पूर्ण
		पूर्ण

		/* unless we alपढ़ोy know the urb's status, collect qtd status
		 * and update count of bytes transferred.  in common लघु पढ़ो
		 * हालs with only one data qtd (including control transfers),
		 * queue processing won't halt.  but with two or more qtds (क्रम
		 * example, with a 32 KB transfer), when the first qtd माला_लो a
		 * लघु पढ़ो the second must be हटाओd by hand.
		 */
		अगर (last_status == -EINPROGRESS) अणु
			last_status = qtd_copy_status(fotg210, urb,
					qtd->length, token);
			अगर (last_status == -EREMOTEIO &&
					(qtd->hw_alt_next &
					FOTG210_LIST_END(fotg210)))
				last_status = -EINPROGRESS;

			/* As part of low/full-speed endpoपूर्णांक-halt processing
			 * we must clear the TT buffer (11.17.5).
			 */
			अगर (unlikely(last_status != -EINPROGRESS &&
					last_status != -EREMOTEIO)) अणु
				/* The TT's in some hubs malfunction when they
				 * receive this request following a STALL (they
				 * stop sending isochronous packets).  Since a
				 * STALL can't leave the TT buffer in a busy
				 * state (अगर you believe Figures 11-48 - 11-51
				 * in the USB 2.0 spec), we won't clear the TT
				 * buffer in this हाल.  Strictly speaking this
				 * is a violation of the spec.
				 */
				अगर (last_status != -EPIPE)
					fotg210_clear_tt_buffer(fotg210, qh,
							urb, token);
			पूर्ण
		पूर्ण

		/* अगर we're removing something not at the queue head,
		 * patch the hardware queue poपूर्णांकer.
		 */
		अगर (stopped && qtd->qtd_list.prev != &qh->qtd_list) अणु
			last = list_entry(qtd->qtd_list.prev,
					काष्ठा fotg210_qtd, qtd_list);
			last->hw_next = qtd->hw_next;
		पूर्ण

		/* हटाओ qtd; it's recycled after possible urb completion */
		list_del(&qtd->qtd_list);
		last = qtd;

		/* reinit the xacterr counter क्रम the next qtd */
		qh->xacterrs = 0;
	पूर्ण

	/* last urb's completion might still need calling */
	अगर (likely(last != शून्य)) अणु
		fotg210_urb_करोne(fotg210, last->urb, last_status);
		count++;
		fotg210_qtd_मुक्त(fotg210, last);
	पूर्ण

	/* Do we need to rescan क्रम URBs dequeued during a giveback? */
	अगर (unlikely(qh->needs_rescan)) अणु
		/* If the QH is alपढ़ोy unlinked, करो the rescan now. */
		अगर (state == QH_STATE_IDLE)
			जाओ rescan;

		/* Otherwise we have to रुको until the QH is fully unlinked.
		 * Our caller will start an unlink अगर qh->needs_rescan is
		 * set.  But अगर an unlink has alपढ़ोy started, nothing needs
		 * to be करोne.
		 */
		अगर (state != QH_STATE_LINKED)
			qh->needs_rescan = 0;
	पूर्ण

	/* restore original state; caller must unlink or relink */
	qh->qh_state = state;

	/* be sure the hardware's करोne with the qh beक्रमe refreshing
	 * it after fault cleanup, or recovering from silicon wrongly
	 * overlaying the dummy qtd (which reduces DMA chatter).
	 */
	अगर (stopped != 0 || hw->hw_qtd_next == FOTG210_LIST_END(fotg210)) अणु
		चयन (state) अणु
		हाल QH_STATE_IDLE:
			qh_refresh(fotg210, qh);
			अवरोध;
		हाल QH_STATE_LINKED:
			/* We won't refresh a QH that's linked (after the HC
			 * stopped the queue).  That aव्योमs a race:
			 *  - HC पढ़ोs first part of QH;
			 *  - CPU updates that first part and the token;
			 *  - HC पढ़ोs rest of that QH, including token
			 * Result:  HC माला_लो an inconsistent image, and then
			 * DMAs to/from the wrong memory (corrupting it).
			 *
			 * That should be rare क्रम पूर्णांकerrupt transfers,
			 * except maybe high bandwidth ...
			 */

			/* Tell the caller to start an unlink */
			qh->needs_rescan = 1;
			अवरोध;
		/* otherwise, unlink alपढ़ोy started */
		पूर्ण
	पूर्ण

	वापस count;
पूर्ण

/* high bandwidth multiplier, as encoded in highspeed endpoपूर्णांक descriptors */
#घोषणा hb_mult(wMaxPacketSize) (1 + (((wMaxPacketSize) >> 11) & 0x03))
/* ... and packet size, क्रम any kind of endpoपूर्णांक descriptor */
#घोषणा max_packet(wMaxPacketSize) ((wMaxPacketSize) & 0x07ff)

/* reverse of qh_urb_transaction:  मुक्त a list of TDs.
 * used क्रम cleanup after errors, beक्रमe HC sees an URB's TDs.
 */
अटल व्योम qtd_list_मुक्त(काष्ठा fotg210_hcd *fotg210, काष्ठा urb *urb,
		काष्ठा list_head *head)
अणु
	काष्ठा fotg210_qtd *qtd, *temp;

	list_क्रम_each_entry_safe(qtd, temp, head, qtd_list) अणु
		list_del(&qtd->qtd_list);
		fotg210_qtd_मुक्त(fotg210, qtd);
	पूर्ण
पूर्ण

/* create a list of filled qtds क्रम this URB; won't link पूर्णांकo qh.
 */
अटल काष्ठा list_head *qh_urb_transaction(काष्ठा fotg210_hcd *fotg210,
		काष्ठा urb *urb, काष्ठा list_head *head, gfp_t flags)
अणु
	काष्ठा fotg210_qtd *qtd, *qtd_prev;
	dma_addr_t buf;
	पूर्णांक len, this_sg_len, maxpacket;
	पूर्णांक is_input;
	u32 token;
	पूर्णांक i;
	काष्ठा scatterlist *sg;

	/*
	 * URBs map to sequences of QTDs:  one logical transaction
	 */
	qtd = fotg210_qtd_alloc(fotg210, flags);
	अगर (unlikely(!qtd))
		वापस शून्य;
	list_add_tail(&qtd->qtd_list, head);
	qtd->urb = urb;

	token = QTD_STS_ACTIVE;
	token |= (FOTG210_TUNE_CERR << 10);
	/* क्रम split transactions, SplitXState initialized to zero */

	len = urb->transfer_buffer_length;
	is_input = usb_pipein(urb->pipe);
	अगर (usb_pipecontrol(urb->pipe)) अणु
		/* SETUP pid */
		qtd_fill(fotg210, qtd, urb->setup_dma,
				माप(काष्ठा usb_ctrlrequest),
				token | (2 /* "setup" */ << 8), 8);

		/* ... and always at least one more pid */
		token ^= QTD_TOGGLE;
		qtd_prev = qtd;
		qtd = fotg210_qtd_alloc(fotg210, flags);
		अगर (unlikely(!qtd))
			जाओ cleanup;
		qtd->urb = urb;
		qtd_prev->hw_next = QTD_NEXT(fotg210, qtd->qtd_dma);
		list_add_tail(&qtd->qtd_list, head);

		/* क्रम zero length DATA stages, STATUS is always IN */
		अगर (len == 0)
			token |= (1 /* "in" */ << 8);
	पूर्ण

	/*
	 * data transfer stage:  buffer setup
	 */
	i = urb->num_mapped_sgs;
	अगर (len > 0 && i > 0) अणु
		sg = urb->sg;
		buf = sg_dma_address(sg);

		/* urb->transfer_buffer_length may be smaller than the
		 * size of the scatterlist (or vice versa)
		 */
		this_sg_len = min_t(पूर्णांक, sg_dma_len(sg), len);
	पूर्ण अन्यथा अणु
		sg = शून्य;
		buf = urb->transfer_dma;
		this_sg_len = len;
	पूर्ण

	अगर (is_input)
		token |= (1 /* "in" */ << 8);
	/* अन्यथा it's alपढ़ोy initted to "out" pid (0 << 8) */

	maxpacket = max_packet(usb_maxpacket(urb->dev, urb->pipe, !is_input));

	/*
	 * buffer माला_लो wrapped in one or more qtds;
	 * last one may be "short" (including zero len)
	 * and may serve as a control status ack
	 */
	क्रम (;;) अणु
		पूर्णांक this_qtd_len;

		this_qtd_len = qtd_fill(fotg210, qtd, buf, this_sg_len, token,
				maxpacket);
		this_sg_len -= this_qtd_len;
		len -= this_qtd_len;
		buf += this_qtd_len;

		/*
		 * लघु पढ़ोs advance to a "magic" dummy instead of the next
		 * qtd ... that क्रमces the queue to stop, क्रम manual cleanup.
		 * (this will usually be overridden later.)
		 */
		अगर (is_input)
			qtd->hw_alt_next = fotg210->async->hw->hw_alt_next;

		/* qh makes control packets use qtd toggle; maybe चयन it */
		अगर ((maxpacket & (this_qtd_len + (maxpacket - 1))) == 0)
			token ^= QTD_TOGGLE;

		अगर (likely(this_sg_len <= 0)) अणु
			अगर (--i <= 0 || len <= 0)
				अवरोध;
			sg = sg_next(sg);
			buf = sg_dma_address(sg);
			this_sg_len = min_t(पूर्णांक, sg_dma_len(sg), len);
		पूर्ण

		qtd_prev = qtd;
		qtd = fotg210_qtd_alloc(fotg210, flags);
		अगर (unlikely(!qtd))
			जाओ cleanup;
		qtd->urb = urb;
		qtd_prev->hw_next = QTD_NEXT(fotg210, qtd->qtd_dma);
		list_add_tail(&qtd->qtd_list, head);
	पूर्ण

	/*
	 * unless the caller requires manual cleanup after लघु पढ़ोs,
	 * have the alt_next mechanism keep the queue running after the
	 * last data qtd (the only one, क्रम control and most other हालs).
	 */
	अगर (likely((urb->transfer_flags & URB_SHORT_NOT_OK) == 0 ||
			usb_pipecontrol(urb->pipe)))
		qtd->hw_alt_next = FOTG210_LIST_END(fotg210);

	/*
	 * control requests may need a terminating data "status" ack;
	 * other OUT ones may need a terminating लघु packet
	 * (zero length).
	 */
	अगर (likely(urb->transfer_buffer_length != 0)) अणु
		पूर्णांक one_more = 0;

		अगर (usb_pipecontrol(urb->pipe)) अणु
			one_more = 1;
			token ^= 0x0100;	/* "in" <--> "out"  */
			token |= QTD_TOGGLE;	/* क्रमce DATA1 */
		पूर्ण अन्यथा अगर (usb_pipeout(urb->pipe)
				&& (urb->transfer_flags & URB_ZERO_PACKET)
				&& !(urb->transfer_buffer_length % maxpacket)) अणु
			one_more = 1;
		पूर्ण
		अगर (one_more) अणु
			qtd_prev = qtd;
			qtd = fotg210_qtd_alloc(fotg210, flags);
			अगर (unlikely(!qtd))
				जाओ cleanup;
			qtd->urb = urb;
			qtd_prev->hw_next = QTD_NEXT(fotg210, qtd->qtd_dma);
			list_add_tail(&qtd->qtd_list, head);

			/* never any data in such packets */
			qtd_fill(fotg210, qtd, 0, 0, token, 0);
		पूर्ण
	पूर्ण

	/* by शेष, enable पूर्णांकerrupt on urb completion */
	अगर (likely(!(urb->transfer_flags & URB_NO_INTERRUPT)))
		qtd->hw_token |= cpu_to_hc32(fotg210, QTD_IOC);
	वापस head;

cleanup:
	qtd_list_मुक्त(fotg210, urb, head);
	वापस शून्य;
पूर्ण

/* Would be best to create all qh's from config descriptors,
 * when each पूर्णांकerface/altsetting is established.  Unlink
 * any previous qh and cancel its urbs first; endpoपूर्णांकs are
 * implicitly reset then (data toggle too).
 * That'd mean updating how usbcore talks to HCDs. (2.7?)
 */


/* Each QH holds a qtd list; a QH is used क्रम everything except iso.
 *
 * For पूर्णांकerrupt urbs, the scheduler must set the microframe scheduling
 * mask(s) each समय the QH माला_लो scheduled.  For highspeed, that's
 * just one microframe in the s-mask.  For split पूर्णांकerrupt transactions
 * there are additional complications: c-mask, maybe FSTNs.
 */
अटल काष्ठा fotg210_qh *qh_make(काष्ठा fotg210_hcd *fotg210, काष्ठा urb *urb,
		gfp_t flags)
अणु
	काष्ठा fotg210_qh *qh = fotg210_qh_alloc(fotg210, flags);
	u32 info1 = 0, info2 = 0;
	पूर्णांक is_input, type;
	पूर्णांक maxp = 0;
	काष्ठा usb_tt *tt = urb->dev->tt;
	काष्ठा fotg210_qh_hw *hw;

	अगर (!qh)
		वापस qh;

	/*
	 * init endpoपूर्णांक/device data क्रम this QH
	 */
	info1 |= usb_pipeendpoपूर्णांक(urb->pipe) << 8;
	info1 |= usb_pipedevice(urb->pipe) << 0;

	is_input = usb_pipein(urb->pipe);
	type = usb_pipetype(urb->pipe);
	maxp = usb_maxpacket(urb->dev, urb->pipe, !is_input);

	/* 1024 byte maxpacket is a hardware उच्चमानing.  High bandwidth
	 * acts like up to 3KB, but is built from smaller packets.
	 */
	अगर (max_packet(maxp) > 1024) अणु
		fotg210_dbg(fotg210, "bogus qh maxpacket %d\n",
				max_packet(maxp));
		जाओ करोne;
	पूर्ण

	/* Compute पूर्णांकerrupt scheduling parameters just once, and save.
	 * - allowing क्रम high bandwidth, how many nsec/uframe are used?
	 * - split transactions need a second CSPLIT uframe; same question
	 * - splits also need a schedule gap (क्रम full/low speed I/O)
	 * - qh has a polling पूर्णांकerval
	 *
	 * For control/bulk requests, the HC or TT handles these.
	 */
	अगर (type == PIPE_INTERRUPT) अणु
		qh->usecs = NS_TO_US(usb_calc_bus_समय(USB_SPEED_HIGH,
				is_input, 0,
				hb_mult(maxp) * max_packet(maxp)));
		qh->start = NO_FRAME;

		अगर (urb->dev->speed == USB_SPEED_HIGH) अणु
			qh->c_usecs = 0;
			qh->gap_uf = 0;

			qh->period = urb->पूर्णांकerval >> 3;
			अगर (qh->period == 0 && urb->पूर्णांकerval != 1) अणु
				/* NOTE पूर्णांकerval 2 or 4 uframes could work.
				 * But पूर्णांकerval 1 scheduling is simpler, and
				 * includes high bandwidth.
				 */
				urb->पूर्णांकerval = 1;
			पूर्ण अन्यथा अगर (qh->period > fotg210->periodic_size) अणु
				qh->period = fotg210->periodic_size;
				urb->पूर्णांकerval = qh->period << 3;
			पूर्ण
		पूर्ण अन्यथा अणु
			पूर्णांक think_समय;

			/* gap is f(FS/LS transfer बार) */
			qh->gap_uf = 1 + usb_calc_bus_समय(urb->dev->speed,
					is_input, 0, maxp) / (125 * 1000);

			/* FIXME this just approximates SPLIT/CSPLIT बार */
			अगर (is_input) अणु		/* SPLIT, gap, CSPLIT+DATA */
				qh->c_usecs = qh->usecs + HS_USECS(0);
				qh->usecs = HS_USECS(1);
			पूर्ण अन्यथा अणु		/* SPLIT+DATA, gap, CSPLIT */
				qh->usecs += HS_USECS(1);
				qh->c_usecs = HS_USECS(0);
			पूर्ण

			think_समय = tt ? tt->think_समय : 0;
			qh->tt_usecs = NS_TO_US(think_समय +
					usb_calc_bus_समय(urb->dev->speed,
					is_input, 0, max_packet(maxp)));
			qh->period = urb->पूर्णांकerval;
			अगर (qh->period > fotg210->periodic_size) अणु
				qh->period = fotg210->periodic_size;
				urb->पूर्णांकerval = qh->period;
			पूर्ण
		पूर्ण
	पूर्ण

	/* support क्रम tt scheduling, and access to toggles */
	qh->dev = urb->dev;

	/* using TT? */
	चयन (urb->dev->speed) अणु
	हाल USB_SPEED_LOW:
		info1 |= QH_LOW_SPEED;
		fallthrough;

	हाल USB_SPEED_FULL:
		/* EPS 0 means "full" */
		अगर (type != PIPE_INTERRUPT)
			info1 |= (FOTG210_TUNE_RL_TT << 28);
		अगर (type == PIPE_CONTROL) अणु
			info1 |= QH_CONTROL_EP;		/* क्रम TT */
			info1 |= QH_TOGGLE_CTL;		/* toggle from qtd */
		पूर्ण
		info1 |= maxp << 16;

		info2 |= (FOTG210_TUNE_MULT_TT << 30);

		/* Some Freescale processors have an erratum in which the
		 * port number in the queue head was 0..N-1 instead of 1..N.
		 */
		अगर (fotg210_has_fsl_portno_bug(fotg210))
			info2 |= (urb->dev->ttport-1) << 23;
		अन्यथा
			info2 |= urb->dev->ttport << 23;

		/* set the address of the TT; क्रम TDI's पूर्णांकegrated
		 * root hub tt, leave it zeroed.
		 */
		अगर (tt && tt->hub != fotg210_to_hcd(fotg210)->self.root_hub)
			info2 |= tt->hub->devnum << 16;

		/* NOTE:  अगर (PIPE_INTERRUPT) अणु scheduler sets c-mask पूर्ण */

		अवरोध;

	हाल USB_SPEED_HIGH:		/* no TT involved */
		info1 |= QH_HIGH_SPEED;
		अगर (type == PIPE_CONTROL) अणु
			info1 |= (FOTG210_TUNE_RL_HS << 28);
			info1 |= 64 << 16;	/* usb2 fixed maxpacket */
			info1 |= QH_TOGGLE_CTL;	/* toggle from qtd */
			info2 |= (FOTG210_TUNE_MULT_HS << 30);
		पूर्ण अन्यथा अगर (type == PIPE_BULK) अणु
			info1 |= (FOTG210_TUNE_RL_HS << 28);
			/* The USB spec says that high speed bulk endpoपूर्णांकs
			 * always use 512 byte maxpacket.  But some device
			 * venकरोrs decided to ignore that, and MSFT is happy
			 * to help them करो so.  So now people expect to use
			 * such nonconक्रमmant devices with Linux too; sigh.
			 */
			info1 |= max_packet(maxp) << 16;
			info2 |= (FOTG210_TUNE_MULT_HS << 30);
		पूर्ण अन्यथा अणु		/* PIPE_INTERRUPT */
			info1 |= max_packet(maxp) << 16;
			info2 |= hb_mult(maxp) << 30;
		पूर्ण
		अवरोध;
	शेष:
		fotg210_dbg(fotg210, "bogus dev %p speed %d\n", urb->dev,
				urb->dev->speed);
करोne:
		qh_destroy(fotg210, qh);
		वापस शून्य;
	पूर्ण

	/* NOTE:  अगर (PIPE_INTERRUPT) अणु scheduler sets s-mask पूर्ण */

	/* init as live, toggle clear, advance to dummy */
	qh->qh_state = QH_STATE_IDLE;
	hw = qh->hw;
	hw->hw_info1 = cpu_to_hc32(fotg210, info1);
	hw->hw_info2 = cpu_to_hc32(fotg210, info2);
	qh->is_out = !is_input;
	usb_settoggle(urb->dev, usb_pipeendpoपूर्णांक(urb->pipe), !is_input, 1);
	qh_refresh(fotg210, qh);
	वापस qh;
पूर्ण

अटल व्योम enable_async(काष्ठा fotg210_hcd *fotg210)
अणु
	अगर (fotg210->async_count++)
		वापस;

	/* Stop रुकोing to turn off the async schedule */
	fotg210->enabled_hrसमयr_events &= ~BIT(FOTG210_HRTIMER_DISABLE_ASYNC);

	/* Don't start the schedule until ASS is 0 */
	fotg210_poll_ASS(fotg210);
	turn_on_io_watchकरोg(fotg210);
पूर्ण

अटल व्योम disable_async(काष्ठा fotg210_hcd *fotg210)
अणु
	अगर (--fotg210->async_count)
		वापस;

	/* The async schedule and async_unlink list are supposed to be empty */
	WARN_ON(fotg210->async->qh_next.qh || fotg210->async_unlink);

	/* Don't turn off the schedule until ASS is 1 */
	fotg210_poll_ASS(fotg210);
पूर्ण

/* move qh (and its qtds) onto async queue; maybe enable queue.  */

अटल व्योम qh_link_async(काष्ठा fotg210_hcd *fotg210, काष्ठा fotg210_qh *qh)
अणु
	__hc32 dma = QH_NEXT(fotg210, qh->qh_dma);
	काष्ठा fotg210_qh *head;

	/* Don't link a QH if there's a Clear-TT-Buffer pending */
	अगर (unlikely(qh->clearing_tt))
		वापस;

	WARN_ON(qh->qh_state != QH_STATE_IDLE);

	/* clear halt and/or toggle; and maybe recover from silicon quirk */
	qh_refresh(fotg210, qh);

	/* splice right after start */
	head = fotg210->async;
	qh->qh_next = head->qh_next;
	qh->hw->hw_next = head->hw->hw_next;
	wmb();

	head->qh_next.qh = qh;
	head->hw->hw_next = dma;

	qh->xacterrs = 0;
	qh->qh_state = QH_STATE_LINKED;
	/* qtd completions reported later by पूर्णांकerrupt */

	enable_async(fotg210);
पूर्ण

/* For control/bulk/पूर्णांकerrupt, वापस QH with these TDs appended.
 * Allocates and initializes the QH अगर necessary.
 * Returns null अगर it can't allocate a QH it needs to.
 * If the QH has TDs (urbs) alपढ़ोy, that's great.
 */
अटल काष्ठा fotg210_qh *qh_append_tds(काष्ठा fotg210_hcd *fotg210,
		काष्ठा urb *urb, काष्ठा list_head *qtd_list,
		पूर्णांक epnum, व्योम **ptr)
अणु
	काष्ठा fotg210_qh *qh = शून्य;
	__hc32 qh_addr_mask = cpu_to_hc32(fotg210, 0x7f);

	qh = (काष्ठा fotg210_qh *) *ptr;
	अगर (unlikely(qh == शून्य)) अणु
		/* can't sleep here, we have fotg210->lock... */
		qh = qh_make(fotg210, urb, GFP_ATOMIC);
		*ptr = qh;
	पूर्ण
	अगर (likely(qh != शून्य)) अणु
		काष्ठा fotg210_qtd *qtd;

		अगर (unlikely(list_empty(qtd_list)))
			qtd = शून्य;
		अन्यथा
			qtd = list_entry(qtd_list->next, काष्ठा fotg210_qtd,
					qtd_list);

		/* control qh may need patching ... */
		अगर (unlikely(epnum == 0)) अणु
			/* usb_reset_device() briefly reverts to address 0 */
			अगर (usb_pipedevice(urb->pipe) == 0)
				qh->hw->hw_info1 &= ~qh_addr_mask;
		पूर्ण

		/* just one way to queue requests: swap with the dummy qtd.
		 * only hc or qh_refresh() ever modअगरy the overlay.
		 */
		अगर (likely(qtd != शून्य)) अणु
			काष्ठा fotg210_qtd *dummy;
			dma_addr_t dma;
			__hc32 token;

			/* to aव्योम racing the HC, use the dummy td instead of
			 * the first td of our list (becomes new dummy).  both
			 * tds stay deactivated until we're करोne, when the
			 * HC is allowed to fetch the old dummy (4.10.2).
			 */
			token = qtd->hw_token;
			qtd->hw_token = HALT_BIT(fotg210);

			dummy = qh->dummy;

			dma = dummy->qtd_dma;
			*dummy = *qtd;
			dummy->qtd_dma = dma;

			list_del(&qtd->qtd_list);
			list_add(&dummy->qtd_list, qtd_list);
			list_splice_tail(qtd_list, &qh->qtd_list);

			fotg210_qtd_init(fotg210, qtd, qtd->qtd_dma);
			qh->dummy = qtd;

			/* hc must see the new dummy at list end */
			dma = qtd->qtd_dma;
			qtd = list_entry(qh->qtd_list.prev,
					काष्ठा fotg210_qtd, qtd_list);
			qtd->hw_next = QTD_NEXT(fotg210, dma);

			/* let the hc process these next qtds */
			wmb();
			dummy->hw_token = token;

			urb->hcpriv = qh;
		पूर्ण
	पूर्ण
	वापस qh;
पूर्ण

अटल पूर्णांक submit_async(काष्ठा fotg210_hcd *fotg210, काष्ठा urb *urb,
		काष्ठा list_head *qtd_list, gfp_t mem_flags)
अणु
	पूर्णांक epnum;
	अचिन्हित दीर्घ flags;
	काष्ठा fotg210_qh *qh = शून्य;
	पूर्णांक rc;

	epnum = urb->ep->desc.bEndpoपूर्णांकAddress;

#अगर_घोषित FOTG210_URB_TRACE
	अणु
		काष्ठा fotg210_qtd *qtd;

		qtd = list_entry(qtd_list->next, काष्ठा fotg210_qtd, qtd_list);
		fotg210_dbg(fotg210,
				"%s %s urb %p ep%d%s len %d, qtd %p [qh %p]\n",
				__func__, urb->dev->devpath, urb,
				epnum & 0x0f, (epnum & USB_सूची_IN)
					? "in" : "out",
				urb->transfer_buffer_length,
				qtd, urb->ep->hcpriv);
	पूर्ण
#पूर्ण_अगर

	spin_lock_irqsave(&fotg210->lock, flags);
	अगर (unlikely(!HCD_HW_ACCESSIBLE(fotg210_to_hcd(fotg210)))) अणु
		rc = -ESHUTDOWN;
		जाओ करोne;
	पूर्ण
	rc = usb_hcd_link_urb_to_ep(fotg210_to_hcd(fotg210), urb);
	अगर (unlikely(rc))
		जाओ करोne;

	qh = qh_append_tds(fotg210, urb, qtd_list, epnum, &urb->ep->hcpriv);
	अगर (unlikely(qh == शून्य)) अणु
		usb_hcd_unlink_urb_from_ep(fotg210_to_hcd(fotg210), urb);
		rc = -ENOMEM;
		जाओ करोne;
	पूर्ण

	/* Control/bulk operations through TTs करोn't need scheduling,
	 * the HC and TT handle it when the TT has a buffer पढ़ोy.
	 */
	अगर (likely(qh->qh_state == QH_STATE_IDLE))
		qh_link_async(fotg210, qh);
करोne:
	spin_unlock_irqrestore(&fotg210->lock, flags);
	अगर (unlikely(qh == शून्य))
		qtd_list_मुक्त(fotg210, urb, qtd_list);
	वापस rc;
पूर्ण

अटल व्योम single_unlink_async(काष्ठा fotg210_hcd *fotg210,
		काष्ठा fotg210_qh *qh)
अणु
	काष्ठा fotg210_qh *prev;

	/* Add to the end of the list of QHs रुकोing क्रम the next IAAD */
	qh->qh_state = QH_STATE_UNLINK;
	अगर (fotg210->async_unlink)
		fotg210->async_unlink_last->unlink_next = qh;
	अन्यथा
		fotg210->async_unlink = qh;
	fotg210->async_unlink_last = qh;

	/* Unlink it from the schedule */
	prev = fotg210->async;
	जबतक (prev->qh_next.qh != qh)
		prev = prev->qh_next.qh;

	prev->hw->hw_next = qh->hw->hw_next;
	prev->qh_next = qh->qh_next;
	अगर (fotg210->qh_scan_next == qh)
		fotg210->qh_scan_next = qh->qh_next.qh;
पूर्ण

अटल व्योम start_iaa_cycle(काष्ठा fotg210_hcd *fotg210, bool nested)
अणु
	/*
	 * Do nothing अगर an IAA cycle is alपढ़ोy running or
	 * अगर one will be started लघुly.
	 */
	अगर (fotg210->async_iaa || fotg210->async_unlinking)
		वापस;

	/* Do all the रुकोing QHs at once */
	fotg210->async_iaa = fotg210->async_unlink;
	fotg210->async_unlink = शून्य;

	/* If the controller isn't running, we don't have to रुको क्रम it */
	अगर (unlikely(fotg210->rh_state < FOTG210_RH_RUNNING)) अणु
		अगर (!nested)		/* Aव्योम recursion */
			end_unlink_async(fotg210);

	/* Otherwise start a new IAA cycle */
	पूर्ण अन्यथा अगर (likely(fotg210->rh_state == FOTG210_RH_RUNNING)) अणु
		/* Make sure the unlinks are all visible to the hardware */
		wmb();

		fotg210_ग_लिखोl(fotg210, fotg210->command | CMD_IAAD,
				&fotg210->regs->command);
		fotg210_पढ़ोl(fotg210, &fotg210->regs->command);
		fotg210_enable_event(fotg210, FOTG210_HRTIMER_IAA_WATCHDOG,
				true);
	पूर्ण
पूर्ण

/* the async qh क्रम the qtds being unlinked are now gone from the HC */

अटल व्योम end_unlink_async(काष्ठा fotg210_hcd *fotg210)
अणु
	काष्ठा fotg210_qh *qh;

	/* Process the idle QHs */
restart:
	fotg210->async_unlinking = true;
	जबतक (fotg210->async_iaa) अणु
		qh = fotg210->async_iaa;
		fotg210->async_iaa = qh->unlink_next;
		qh->unlink_next = शून्य;

		qh->qh_state = QH_STATE_IDLE;
		qh->qh_next.qh = शून्य;

		qh_completions(fotg210, qh);
		अगर (!list_empty(&qh->qtd_list) &&
				fotg210->rh_state == FOTG210_RH_RUNNING)
			qh_link_async(fotg210, qh);
		disable_async(fotg210);
	पूर्ण
	fotg210->async_unlinking = false;

	/* Start a new IAA cycle अगर any QHs are रुकोing क्रम it */
	अगर (fotg210->async_unlink) अणु
		start_iaa_cycle(fotg210, true);
		अगर (unlikely(fotg210->rh_state < FOTG210_RH_RUNNING))
			जाओ restart;
	पूर्ण
पूर्ण

अटल व्योम unlink_empty_async(काष्ठा fotg210_hcd *fotg210)
अणु
	काष्ठा fotg210_qh *qh, *next;
	bool stopped = (fotg210->rh_state < FOTG210_RH_RUNNING);
	bool check_unlinks_later = false;

	/* Unlink all the async QHs that have been empty क्रम a समयr cycle */
	next = fotg210->async->qh_next.qh;
	जबतक (next) अणु
		qh = next;
		next = qh->qh_next.qh;

		अगर (list_empty(&qh->qtd_list) &&
				qh->qh_state == QH_STATE_LINKED) अणु
			अगर (!stopped && qh->unlink_cycle ==
					fotg210->async_unlink_cycle)
				check_unlinks_later = true;
			अन्यथा
				single_unlink_async(fotg210, qh);
		पूर्ण
	पूर्ण

	/* Start a new IAA cycle अगर any QHs are रुकोing क्रम it */
	अगर (fotg210->async_unlink)
		start_iaa_cycle(fotg210, false);

	/* QHs that haven't been empty क्रम दीर्घ enough will be handled later */
	अगर (check_unlinks_later) अणु
		fotg210_enable_event(fotg210, FOTG210_HRTIMER_ASYNC_UNLINKS,
				true);
		++fotg210->async_unlink_cycle;
	पूर्ण
पूर्ण

/* makes sure the async qh will become idle */
/* caller must own fotg210->lock */

अटल व्योम start_unlink_async(काष्ठा fotg210_hcd *fotg210,
		काष्ठा fotg210_qh *qh)
अणु
	/*
	 * If the QH isn't linked then there's nothing we can करो
	 * unless we were called during a giveback, in which हाल
	 * qh_completions() has to deal with it.
	 */
	अगर (qh->qh_state != QH_STATE_LINKED) अणु
		अगर (qh->qh_state == QH_STATE_COMPLETING)
			qh->needs_rescan = 1;
		वापस;
	पूर्ण

	single_unlink_async(fotg210, qh);
	start_iaa_cycle(fotg210, false);
पूर्ण

अटल व्योम scan_async(काष्ठा fotg210_hcd *fotg210)
अणु
	काष्ठा fotg210_qh *qh;
	bool check_unlinks_later = false;

	fotg210->qh_scan_next = fotg210->async->qh_next.qh;
	जबतक (fotg210->qh_scan_next) अणु
		qh = fotg210->qh_scan_next;
		fotg210->qh_scan_next = qh->qh_next.qh;
rescan:
		/* clean any finished work क्रम this qh */
		अगर (!list_empty(&qh->qtd_list)) अणु
			पूर्णांक temp;

			/*
			 * Unlinks could happen here; completion reporting
			 * drops the lock.  That's why fotg210->qh_scan_next
			 * always holds the next qh to scan; अगर the next qh
			 * माला_लो unlinked then fotg210->qh_scan_next is adjusted
			 * in single_unlink_async().
			 */
			temp = qh_completions(fotg210, qh);
			अगर (qh->needs_rescan) अणु
				start_unlink_async(fotg210, qh);
			पूर्ण अन्यथा अगर (list_empty(&qh->qtd_list)
					&& qh->qh_state == QH_STATE_LINKED) अणु
				qh->unlink_cycle = fotg210->async_unlink_cycle;
				check_unlinks_later = true;
			पूर्ण अन्यथा अगर (temp != 0)
				जाओ rescan;
		पूर्ण
	पूर्ण

	/*
	 * Unlink empty entries, reducing DMA usage as well
	 * as HCD schedule-scanning costs.  Delay क्रम any qh
	 * we just scanned, there's a not-unusual हाल that it
	 * करोesn't stay idle क्रम दीर्घ.
	 */
	अगर (check_unlinks_later && fotg210->rh_state == FOTG210_RH_RUNNING &&
			!(fotg210->enabled_hrसमयr_events &
			BIT(FOTG210_HRTIMER_ASYNC_UNLINKS))) अणु
		fotg210_enable_event(fotg210,
				FOTG210_HRTIMER_ASYNC_UNLINKS, true);
		++fotg210->async_unlink_cycle;
	पूर्ण
पूर्ण
/* EHCI scheduled transaction support:  पूर्णांकerrupt, iso, split iso
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
अटल पूर्णांक fotg210_get_frame(काष्ठा usb_hcd *hcd);

/* periodic_next_shaकरोw - वापस "next" poपूर्णांकer on shaकरोw list
 * @periodic: host poपूर्णांकer to qh/itd
 * @tag: hardware tag क्रम type of this record
 */
अटल जोड़ fotg210_shaकरोw *periodic_next_shaकरोw(काष्ठा fotg210_hcd *fotg210,
		जोड़ fotg210_shaकरोw *periodic, __hc32 tag)
अणु
	चयन (hc32_to_cpu(fotg210, tag)) अणु
	हाल Q_TYPE_QH:
		वापस &periodic->qh->qh_next;
	हाल Q_TYPE_FSTN:
		वापस &periodic->fstn->fstn_next;
	शेष:
		वापस &periodic->itd->itd_next;
	पूर्ण
पूर्ण

अटल __hc32 *shaकरोw_next_periodic(काष्ठा fotg210_hcd *fotg210,
		जोड़ fotg210_shaकरोw *periodic, __hc32 tag)
अणु
	चयन (hc32_to_cpu(fotg210, tag)) अणु
	/* our fotg210_shaकरोw.qh is actually software part */
	हाल Q_TYPE_QH:
		वापस &periodic->qh->hw->hw_next;
	/* others are hw parts */
	शेष:
		वापस periodic->hw_next;
	पूर्ण
पूर्ण

/* caller must hold fotg210->lock */
अटल व्योम periodic_unlink(काष्ठा fotg210_hcd *fotg210, अचिन्हित frame,
		व्योम *ptr)
अणु
	जोड़ fotg210_shaकरोw *prev_p = &fotg210->pshaकरोw[frame];
	__hc32 *hw_p = &fotg210->periodic[frame];
	जोड़ fotg210_shaकरोw here = *prev_p;

	/* find predecessor of "ptr"; hw and shaकरोw lists are in sync */
	जबतक (here.ptr && here.ptr != ptr) अणु
		prev_p = periodic_next_shaकरोw(fotg210, prev_p,
				Q_NEXT_TYPE(fotg210, *hw_p));
		hw_p = shaकरोw_next_periodic(fotg210, &here,
				Q_NEXT_TYPE(fotg210, *hw_p));
		here = *prev_p;
	पूर्ण
	/* an पूर्णांकerrupt entry (at list end) could have been shared */
	अगर (!here.ptr)
		वापस;

	/* update shaकरोw and hardware lists ... the old "next" poपूर्णांकers
	 * from ptr may still be in use, the caller updates them.
	 */
	*prev_p = *periodic_next_shaकरोw(fotg210, &here,
			Q_NEXT_TYPE(fotg210, *hw_p));

	*hw_p = *shaकरोw_next_periodic(fotg210, &here,
			Q_NEXT_TYPE(fotg210, *hw_p));
पूर्ण

/* how many of the uframe's 125 usecs are allocated? */
अटल अचिन्हित लघु periodic_usecs(काष्ठा fotg210_hcd *fotg210,
		अचिन्हित frame, अचिन्हित uframe)
अणु
	__hc32 *hw_p = &fotg210->periodic[frame];
	जोड़ fotg210_shaकरोw *q = &fotg210->pshaकरोw[frame];
	अचिन्हित usecs = 0;
	काष्ठा fotg210_qh_hw *hw;

	जबतक (q->ptr) अणु
		चयन (hc32_to_cpu(fotg210, Q_NEXT_TYPE(fotg210, *hw_p))) अणु
		हाल Q_TYPE_QH:
			hw = q->qh->hw;
			/* is it in the S-mask? */
			अगर (hw->hw_info2 & cpu_to_hc32(fotg210, 1 << uframe))
				usecs += q->qh->usecs;
			/* ... or C-mask? */
			अगर (hw->hw_info2 & cpu_to_hc32(fotg210,
					1 << (8 + uframe)))
				usecs += q->qh->c_usecs;
			hw_p = &hw->hw_next;
			q = &q->qh->qh_next;
			अवरोध;
		/* हाल Q_TYPE_FSTN: */
		शेष:
			/* क्रम "save place" FSTNs, count the relevant INTR
			 * bandwidth from the previous frame
			 */
			अगर (q->fstn->hw_prev != FOTG210_LIST_END(fotg210))
				fotg210_dbg(fotg210, "ignoring FSTN cost ...\n");

			hw_p = &q->fstn->hw_next;
			q = &q->fstn->fstn_next;
			अवरोध;
		हाल Q_TYPE_ITD:
			अगर (q->itd->hw_transaction[uframe])
				usecs += q->itd->stream->usecs;
			hw_p = &q->itd->hw_next;
			q = &q->itd->itd_next;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (usecs > fotg210->uframe_periodic_max)
		fotg210_err(fotg210, "uframe %d sched overrun: %d usecs\n",
				frame * 8 + uframe, usecs);
	वापस usecs;
पूर्ण

अटल पूर्णांक same_tt(काष्ठा usb_device *dev1, काष्ठा usb_device *dev2)
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

/* वापस true अगरf the device's transaction translator is available
 * क्रम a periodic transfer starting at the specअगरied frame, using
 * all the uframes in the mask.
 */
अटल पूर्णांक tt_no_collision(काष्ठा fotg210_hcd *fotg210, अचिन्हित period,
		काष्ठा usb_device *dev, अचिन्हित frame, u32 uf_mask)
अणु
	अगर (period == 0)	/* error */
		वापस 0;

	/* note bandwidth wastage:  split never follows csplit
	 * (dअगरferent dev or endpoपूर्णांक) until the next uframe.
	 * calling convention करोesn't make that distinction.
	 */
	क्रम (; frame < fotg210->periodic_size; frame += period) अणु
		जोड़ fotg210_shaकरोw here;
		__hc32 type;
		काष्ठा fotg210_qh_hw *hw;

		here = fotg210->pshaकरोw[frame];
		type = Q_NEXT_TYPE(fotg210, fotg210->periodic[frame]);
		जबतक (here.ptr) अणु
			चयन (hc32_to_cpu(fotg210, type)) अणु
			हाल Q_TYPE_ITD:
				type = Q_NEXT_TYPE(fotg210, here.itd->hw_next);
				here = here.itd->itd_next;
				जारी;
			हाल Q_TYPE_QH:
				hw = here.qh->hw;
				अगर (same_tt(dev, here.qh->dev)) अणु
					u32 mask;

					mask = hc32_to_cpu(fotg210,
							hw->hw_info2);
					/* "knows" no gap is needed */
					mask |= mask >> 8;
					अगर (mask & uf_mask)
						अवरोध;
				पूर्ण
				type = Q_NEXT_TYPE(fotg210, hw->hw_next);
				here = here.qh->qh_next;
				जारी;
			/* हाल Q_TYPE_FSTN: */
			शेष:
				fotg210_dbg(fotg210,
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

अटल व्योम enable_periodic(काष्ठा fotg210_hcd *fotg210)
अणु
	अगर (fotg210->periodic_count++)
		वापस;

	/* Stop रुकोing to turn off the periodic schedule */
	fotg210->enabled_hrसमयr_events &=
		~BIT(FOTG210_HRTIMER_DISABLE_PERIODIC);

	/* Don't start the schedule until PSS is 0 */
	fotg210_poll_PSS(fotg210);
	turn_on_io_watchकरोg(fotg210);
पूर्ण

अटल व्योम disable_periodic(काष्ठा fotg210_hcd *fotg210)
अणु
	अगर (--fotg210->periodic_count)
		वापस;

	/* Don't turn off the schedule until PSS is 1 */
	fotg210_poll_PSS(fotg210);
पूर्ण

/* periodic schedule slots have iso tds (normal or split) first, then a
 * sparse tree क्रम active पूर्णांकerrupt transfers.
 *
 * this just links in a qh; caller guarantees uframe masks are set right.
 * no FSTN support (yet; fotg210 0.96+)
 */
अटल व्योम qh_link_periodic(काष्ठा fotg210_hcd *fotg210, काष्ठा fotg210_qh *qh)
अणु
	अचिन्हित i;
	अचिन्हित period = qh->period;

	dev_dbg(&qh->dev->dev,
			"link qh%d-%04x/%p start %d [%d/%d us]\n", period,
			hc32_to_cpup(fotg210, &qh->hw->hw_info2) &
			(QH_CMASK | QH_SMASK), qh, qh->start, qh->usecs,
			qh->c_usecs);

	/* high bandwidth, or otherwise every microframe */
	अगर (period == 0)
		period = 1;

	क्रम (i = qh->start; i < fotg210->periodic_size; i += period) अणु
		जोड़ fotg210_shaकरोw *prev = &fotg210->pshaकरोw[i];
		__hc32 *hw_p = &fotg210->periodic[i];
		जोड़ fotg210_shaकरोw here = *prev;
		__hc32 type = 0;

		/* skip the iso nodes at list head */
		जबतक (here.ptr) अणु
			type = Q_NEXT_TYPE(fotg210, *hw_p);
			अगर (type == cpu_to_hc32(fotg210, Q_TYPE_QH))
				अवरोध;
			prev = periodic_next_shaकरोw(fotg210, prev, type);
			hw_p = shaकरोw_next_periodic(fotg210, &here, type);
			here = *prev;
		पूर्ण

		/* sorting each branch by period (slow-->fast)
		 * enables sharing पूर्णांकerior tree nodes
		 */
		जबतक (here.ptr && qh != here.qh) अणु
			अगर (qh->period > here.qh->period)
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
			*hw_p = QH_NEXT(fotg210, qh->qh_dma);
		पूर्ण
	पूर्ण
	qh->qh_state = QH_STATE_LINKED;
	qh->xacterrs = 0;

	/* update per-qh bandwidth क्रम usbfs */
	fotg210_to_hcd(fotg210)->self.bandwidth_allocated += qh->period
		? ((qh->usecs + qh->c_usecs) / qh->period)
		: (qh->usecs * 8);

	list_add(&qh->पूर्णांकr_node, &fotg210->पूर्णांकr_qh_list);

	/* maybe enable periodic schedule processing */
	++fotg210->पूर्णांकr_count;
	enable_periodic(fotg210);
पूर्ण

अटल व्योम qh_unlink_periodic(काष्ठा fotg210_hcd *fotg210,
		काष्ठा fotg210_qh *qh)
अणु
	अचिन्हित i;
	अचिन्हित period;

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
	period = qh->period;
	अगर (!period)
		period = 1;

	क्रम (i = qh->start; i < fotg210->periodic_size; i += period)
		periodic_unlink(fotg210, i, qh);

	/* update per-qh bandwidth क्रम usbfs */
	fotg210_to_hcd(fotg210)->self.bandwidth_allocated -= qh->period
		? ((qh->usecs + qh->c_usecs) / qh->period)
		: (qh->usecs * 8);

	dev_dbg(&qh->dev->dev,
			"unlink qh%d-%04x/%p start %d [%d/%d us]\n",
			qh->period, hc32_to_cpup(fotg210, &qh->hw->hw_info2) &
			(QH_CMASK | QH_SMASK), qh, qh->start, qh->usecs,
			qh->c_usecs);

	/* qh->qh_next still "live" to HC */
	qh->qh_state = QH_STATE_UNLINK;
	qh->qh_next.ptr = शून्य;

	अगर (fotg210->qh_scan_next == qh)
		fotg210->qh_scan_next = list_entry(qh->पूर्णांकr_node.next,
				काष्ठा fotg210_qh, पूर्णांकr_node);
	list_del(&qh->पूर्णांकr_node);
पूर्ण

अटल व्योम start_unlink_पूर्णांकr(काष्ठा fotg210_hcd *fotg210,
		काष्ठा fotg210_qh *qh)
अणु
	/* If the QH isn't linked then there's nothing we can करो
	 * unless we were called during a giveback, in which हाल
	 * qh_completions() has to deal with it.
	 */
	अगर (qh->qh_state != QH_STATE_LINKED) अणु
		अगर (qh->qh_state == QH_STATE_COMPLETING)
			qh->needs_rescan = 1;
		वापस;
	पूर्ण

	qh_unlink_periodic(fotg210, qh);

	/* Make sure the unlinks are visible beक्रमe starting the समयr */
	wmb();

	/*
	 * The EHCI spec करोesn't say how दीर्घ it takes the controller to
	 * stop accessing an unlinked पूर्णांकerrupt QH.  The समयr delay is
	 * 9 uframes; presumably that will be दीर्घ enough.
	 */
	qh->unlink_cycle = fotg210->पूर्णांकr_unlink_cycle;

	/* New entries go at the end of the पूर्णांकr_unlink list */
	अगर (fotg210->पूर्णांकr_unlink)
		fotg210->पूर्णांकr_unlink_last->unlink_next = qh;
	अन्यथा
		fotg210->पूर्णांकr_unlink = qh;
	fotg210->पूर्णांकr_unlink_last = qh;

	अगर (fotg210->पूर्णांकr_unlinking)
		;	/* Aव्योम recursive calls */
	अन्यथा अगर (fotg210->rh_state < FOTG210_RH_RUNNING)
		fotg210_handle_पूर्णांकr_unlinks(fotg210);
	अन्यथा अगर (fotg210->पूर्णांकr_unlink == qh) अणु
		fotg210_enable_event(fotg210, FOTG210_HRTIMER_UNLINK_INTR,
				true);
		++fotg210->पूर्णांकr_unlink_cycle;
	पूर्ण
पूर्ण

अटल व्योम end_unlink_पूर्णांकr(काष्ठा fotg210_hcd *fotg210, काष्ठा fotg210_qh *qh)
अणु
	काष्ठा fotg210_qh_hw *hw = qh->hw;
	पूर्णांक rc;

	qh->qh_state = QH_STATE_IDLE;
	hw->hw_next = FOTG210_LIST_END(fotg210);

	qh_completions(fotg210, qh);

	/* reschedule QH अगरf another request is queued */
	अगर (!list_empty(&qh->qtd_list) &&
			fotg210->rh_state == FOTG210_RH_RUNNING) अणु
		rc = qh_schedule(fotg210, qh);

		/* An error here likely indicates handshake failure
		 * or no space left in the schedule.  Neither fault
		 * should happen often ...
		 *
		 * FIXME समाप्त the now-dysfunctional queued urbs
		 */
		अगर (rc != 0)
			fotg210_err(fotg210, "can't reschedule qh %p, err %d\n",
					qh, rc);
	पूर्ण

	/* maybe turn off periodic schedule */
	--fotg210->पूर्णांकr_count;
	disable_periodic(fotg210);
पूर्ण

अटल पूर्णांक check_period(काष्ठा fotg210_hcd *fotg210, अचिन्हित frame,
		अचिन्हित uframe, अचिन्हित period, अचिन्हित usecs)
अणु
	पूर्णांक claimed;

	/* complete split running पूर्णांकo next frame?
	 * given FSTN support, we could someबार check...
	 */
	अगर (uframe >= 8)
		वापस 0;

	/* convert "usecs we need" to "max already claimed" */
	usecs = fotg210->uframe_periodic_max - usecs;

	/* we "know" 2 and 4 uframe पूर्णांकervals were rejected; so
	 * क्रम period 0, check _every_ microframe in the schedule.
	 */
	अगर (unlikely(period == 0)) अणु
		करो अणु
			क्रम (uframe = 0; uframe < 7; uframe++) अणु
				claimed = periodic_usecs(fotg210, frame,
						uframe);
				अगर (claimed > usecs)
					वापस 0;
			पूर्ण
		पूर्ण जबतक ((frame += 1) < fotg210->periodic_size);

	/* just check the specअगरied uframe, at that period */
	पूर्ण अन्यथा अणु
		करो अणु
			claimed = periodic_usecs(fotg210, frame, uframe);
			अगर (claimed > usecs)
				वापस 0;
		पूर्ण जबतक ((frame += period) < fotg210->periodic_size);
	पूर्ण

	/* success! */
	वापस 1;
पूर्ण

अटल पूर्णांक check_पूर्णांकr_schedule(काष्ठा fotg210_hcd *fotg210, अचिन्हित frame,
		अचिन्हित uframe, स्थिर काष्ठा fotg210_qh *qh, __hc32 *c_maskp)
अणु
	पूर्णांक retval = -ENOSPC;
	u8 mask = 0;

	अगर (qh->c_usecs && uframe >= 6)		/* FSTN territory? */
		जाओ करोne;

	अगर (!check_period(fotg210, frame, uframe, qh->period, qh->usecs))
		जाओ करोne;
	अगर (!qh->c_usecs) अणु
		retval = 0;
		*c_maskp = 0;
		जाओ करोne;
	पूर्ण

	/* Make sure this tt's buffer is also available क्रम CSPLITs.
	 * We pessimize a bit; probably the typical full speed हाल
	 * करोesn't need the second CSPLIT.
	 *
	 * NOTE:  both SPLIT and CSPLIT could be checked in just
	 * one smart pass...
	 */
	mask = 0x03 << (uframe + qh->gap_uf);
	*c_maskp = cpu_to_hc32(fotg210, mask << 8);

	mask |= 1 << uframe;
	अगर (tt_no_collision(fotg210, qh->period, qh->dev, frame, mask)) अणु
		अगर (!check_period(fotg210, frame, uframe + qh->gap_uf + 1,
				qh->period, qh->c_usecs))
			जाओ करोne;
		अगर (!check_period(fotg210, frame, uframe + qh->gap_uf,
				qh->period, qh->c_usecs))
			जाओ करोne;
		retval = 0;
	पूर्ण
करोne:
	वापस retval;
पूर्ण

/* "first fit" scheduling policy used the first समय through,
 * or when the previous schedule slot can't be re-used.
 */
अटल पूर्णांक qh_schedule(काष्ठा fotg210_hcd *fotg210, काष्ठा fotg210_qh *qh)
अणु
	पूर्णांक status;
	अचिन्हित uframe;
	__hc32 c_mask;
	अचिन्हित frame;	/* 0..(qh->period - 1), or NO_FRAME */
	काष्ठा fotg210_qh_hw *hw = qh->hw;

	qh_refresh(fotg210, qh);
	hw->hw_next = FOTG210_LIST_END(fotg210);
	frame = qh->start;

	/* reuse the previous schedule slots, अगर we can */
	अगर (frame < qh->period) अणु
		uframe = ffs(hc32_to_cpup(fotg210, &hw->hw_info2) & QH_SMASK);
		status = check_पूर्णांकr_schedule(fotg210, frame, --uframe,
				qh, &c_mask);
	पूर्ण अन्यथा अणु
		uframe = 0;
		c_mask = 0;
		status = -ENOSPC;
	पूर्ण

	/* अन्यथा scan the schedule to find a group of slots such that all
	 * uframes have enough periodic bandwidth available.
	 */
	अगर (status) अणु
		/* "normal" हाल, uframing flexible except with splits */
		अगर (qh->period) अणु
			पूर्णांक i;

			क्रम (i = qh->period; status && i > 0; --i) अणु
				frame = ++fotg210->अक्रमom_frame % qh->period;
				क्रम (uframe = 0; uframe < 8; uframe++) अणु
					status = check_पूर्णांकr_schedule(fotg210,
							frame, uframe, qh,
							&c_mask);
					अगर (status == 0)
						अवरोध;
				पूर्ण
			पूर्ण

		/* qh->period == 0 means every uframe */
		पूर्ण अन्यथा अणु
			frame = 0;
			status = check_पूर्णांकr_schedule(fotg210, 0, 0, qh,
					&c_mask);
		पूर्ण
		अगर (status)
			जाओ करोne;
		qh->start = frame;

		/* reset S-frame and (maybe) C-frame masks */
		hw->hw_info2 &= cpu_to_hc32(fotg210, ~(QH_CMASK | QH_SMASK));
		hw->hw_info2 |= qh->period
			? cpu_to_hc32(fotg210, 1 << uframe)
			: cpu_to_hc32(fotg210, QH_SMASK);
		hw->hw_info2 |= c_mask;
	पूर्ण अन्यथा
		fotg210_dbg(fotg210, "reused qh %p schedule\n", qh);

	/* stuff पूर्णांकo the periodic schedule */
	qh_link_periodic(fotg210, qh);
करोne:
	वापस status;
पूर्ण

अटल पूर्णांक पूर्णांकr_submit(काष्ठा fotg210_hcd *fotg210, काष्ठा urb *urb,
		काष्ठा list_head *qtd_list, gfp_t mem_flags)
अणु
	अचिन्हित epnum;
	अचिन्हित दीर्घ flags;
	काष्ठा fotg210_qh *qh;
	पूर्णांक status;
	काष्ठा list_head empty;

	/* get endpoपूर्णांक and transfer/schedule data */
	epnum = urb->ep->desc.bEndpoपूर्णांकAddress;

	spin_lock_irqsave(&fotg210->lock, flags);

	अगर (unlikely(!HCD_HW_ACCESSIBLE(fotg210_to_hcd(fotg210)))) अणु
		status = -ESHUTDOWN;
		जाओ करोne_not_linked;
	पूर्ण
	status = usb_hcd_link_urb_to_ep(fotg210_to_hcd(fotg210), urb);
	अगर (unlikely(status))
		जाओ करोne_not_linked;

	/* get qh and क्रमce any scheduling errors */
	INIT_LIST_HEAD(&empty);
	qh = qh_append_tds(fotg210, urb, &empty, epnum, &urb->ep->hcpriv);
	अगर (qh == शून्य) अणु
		status = -ENOMEM;
		जाओ करोne;
	पूर्ण
	अगर (qh->qh_state == QH_STATE_IDLE) अणु
		status = qh_schedule(fotg210, qh);
		अगर (status)
			जाओ करोne;
	पूर्ण

	/* then queue the urb's tds to the qh */
	qh = qh_append_tds(fotg210, urb, qtd_list, epnum, &urb->ep->hcpriv);
	BUG_ON(qh == शून्य);

	/* ... update usbfs periodic stats */
	fotg210_to_hcd(fotg210)->self.bandwidth_पूर्णांक_reqs++;

करोne:
	अगर (unlikely(status))
		usb_hcd_unlink_urb_from_ep(fotg210_to_hcd(fotg210), urb);
करोne_not_linked:
	spin_unlock_irqrestore(&fotg210->lock, flags);
	अगर (status)
		qtd_list_मुक्त(fotg210, urb, qtd_list);

	वापस status;
पूर्ण

अटल व्योम scan_पूर्णांकr(काष्ठा fotg210_hcd *fotg210)
अणु
	काष्ठा fotg210_qh *qh;

	list_क्रम_each_entry_safe(qh, fotg210->qh_scan_next,
			&fotg210->पूर्णांकr_qh_list, पूर्णांकr_node) अणु
rescan:
		/* clean any finished work क्रम this qh */
		अगर (!list_empty(&qh->qtd_list)) अणु
			पूर्णांक temp;

			/*
			 * Unlinks could happen here; completion reporting
			 * drops the lock.  That's why fotg210->qh_scan_next
			 * always holds the next qh to scan; अगर the next qh
			 * माला_लो unlinked then fotg210->qh_scan_next is adjusted
			 * in qh_unlink_periodic().
			 */
			temp = qh_completions(fotg210, qh);
			अगर (unlikely(qh->needs_rescan ||
					(list_empty(&qh->qtd_list) &&
					qh->qh_state == QH_STATE_LINKED)))
				start_unlink_पूर्णांकr(fotg210, qh);
			अन्यथा अगर (temp != 0)
				जाओ rescan;
		पूर्ण
	पूर्ण
पूर्ण

/* fotg210_iso_stream ops work with both ITD and SITD */

अटल काष्ठा fotg210_iso_stream *iso_stream_alloc(gfp_t mem_flags)
अणु
	काष्ठा fotg210_iso_stream *stream;

	stream = kzalloc(माप(*stream), mem_flags);
	अगर (likely(stream != शून्य)) अणु
		INIT_LIST_HEAD(&stream->td_list);
		INIT_LIST_HEAD(&stream->मुक्त_list);
		stream->next_uframe = -1;
	पूर्ण
	वापस stream;
पूर्ण

अटल व्योम iso_stream_init(काष्ठा fotg210_hcd *fotg210,
		काष्ठा fotg210_iso_stream *stream, काष्ठा usb_device *dev,
		पूर्णांक pipe, अचिन्हित पूर्णांकerval)
अणु
	u32 buf1;
	अचिन्हित epnum, maxp;
	पूर्णांक is_input;
	दीर्घ bandwidth;
	अचिन्हित multi;

	/*
	 * this might be a "high bandwidth" highspeed endpoपूर्णांक,
	 * as encoded in the ep descriptor's wMaxPacket field
	 */
	epnum = usb_pipeendpoपूर्णांक(pipe);
	is_input = usb_pipein(pipe) ? USB_सूची_IN : 0;
	maxp = usb_maxpacket(dev, pipe, !is_input);
	अगर (is_input)
		buf1 = (1 << 11);
	अन्यथा
		buf1 = 0;

	maxp = max_packet(maxp);
	multi = hb_mult(maxp);
	buf1 |= maxp;
	maxp *= multi;

	stream->buf0 = cpu_to_hc32(fotg210, (epnum << 8) | dev->devnum);
	stream->buf1 = cpu_to_hc32(fotg210, buf1);
	stream->buf2 = cpu_to_hc32(fotg210, multi);

	/* usbfs wants to report the average usecs per frame tied up
	 * when transfers on this endpoपूर्णांक are scheduled ...
	 */
	अगर (dev->speed == USB_SPEED_FULL) अणु
		पूर्णांकerval <<= 3;
		stream->usecs = NS_TO_US(usb_calc_bus_समय(dev->speed,
				is_input, 1, maxp));
		stream->usecs /= 8;
	पूर्ण अन्यथा अणु
		stream->highspeed = 1;
		stream->usecs = HS_USECS_ISO(maxp);
	पूर्ण
	bandwidth = stream->usecs * 8;
	bandwidth /= पूर्णांकerval;

	stream->bandwidth = bandwidth;
	stream->udev = dev;
	stream->bEndpoपूर्णांकAddress = is_input | epnum;
	stream->पूर्णांकerval = पूर्णांकerval;
	stream->maxp = maxp;
पूर्ण

अटल काष्ठा fotg210_iso_stream *iso_stream_find(काष्ठा fotg210_hcd *fotg210,
		काष्ठा urb *urb)
अणु
	अचिन्हित epnum;
	काष्ठा fotg210_iso_stream *stream;
	काष्ठा usb_host_endpoपूर्णांक *ep;
	अचिन्हित दीर्घ flags;

	epnum = usb_pipeendpoपूर्णांक(urb->pipe);
	अगर (usb_pipein(urb->pipe))
		ep = urb->dev->ep_in[epnum];
	अन्यथा
		ep = urb->dev->ep_out[epnum];

	spin_lock_irqsave(&fotg210->lock, flags);
	stream = ep->hcpriv;

	अगर (unlikely(stream == शून्य)) अणु
		stream = iso_stream_alloc(GFP_ATOMIC);
		अगर (likely(stream != शून्य)) अणु
			ep->hcpriv = stream;
			stream->ep = ep;
			iso_stream_init(fotg210, stream, urb->dev, urb->pipe,
					urb->पूर्णांकerval);
		पूर्ण

	/* अगर dev->ep[epnum] is a QH, hw is set */
	पूर्ण अन्यथा अगर (unlikely(stream->hw != शून्य)) अणु
		fotg210_dbg(fotg210, "dev %s ep%d%s, not iso??\n",
				urb->dev->devpath, epnum,
				usb_pipein(urb->pipe) ? "in" : "out");
		stream = शून्य;
	पूर्ण

	spin_unlock_irqrestore(&fotg210->lock, flags);
	वापस stream;
पूर्ण

/* fotg210_iso_sched ops can be ITD-only or SITD-only */

अटल काष्ठा fotg210_iso_sched *iso_sched_alloc(अचिन्हित packets,
		gfp_t mem_flags)
अणु
	काष्ठा fotg210_iso_sched *iso_sched;
	पूर्णांक size = माप(*iso_sched);

	size += packets * माप(काष्ठा fotg210_iso_packet);
	iso_sched = kzalloc(size, mem_flags);
	अगर (likely(iso_sched != शून्य))
		INIT_LIST_HEAD(&iso_sched->td_list);

	वापस iso_sched;
पूर्ण

अटल अंतरभूत व्योम itd_sched_init(काष्ठा fotg210_hcd *fotg210,
		काष्ठा fotg210_iso_sched *iso_sched,
		काष्ठा fotg210_iso_stream *stream, काष्ठा urb *urb)
अणु
	अचिन्हित i;
	dma_addr_t dma = urb->transfer_dma;

	/* how many uframes are needed क्रम these transfers */
	iso_sched->span = urb->number_of_packets * stream->पूर्णांकerval;

	/* figure out per-uframe itd fields that we'll need later
	 * when we fit new itds पूर्णांकo the schedule.
	 */
	क्रम (i = 0; i < urb->number_of_packets; i++) अणु
		काष्ठा fotg210_iso_packet *uframe = &iso_sched->packet[i];
		अचिन्हित length;
		dma_addr_t buf;
		u32 trans;

		length = urb->iso_frame_desc[i].length;
		buf = dma + urb->iso_frame_desc[i].offset;

		trans = FOTG210_ISOC_ACTIVE;
		trans |= buf & 0x0fff;
		अगर (unlikely(((i + 1) == urb->number_of_packets))
				&& !(urb->transfer_flags & URB_NO_INTERRUPT))
			trans |= FOTG210_ITD_IOC;
		trans |= length << 16;
		uframe->transaction = cpu_to_hc32(fotg210, trans);

		/* might need to cross a buffer page within a uframe */
		uframe->bufp = (buf & ~(u64)0x0fff);
		buf += length;
		अगर (unlikely((uframe->bufp != (buf & ~(u64)0x0fff))))
			uframe->cross = 1;
	पूर्ण
पूर्ण

अटल व्योम iso_sched_मुक्त(काष्ठा fotg210_iso_stream *stream,
		काष्ठा fotg210_iso_sched *iso_sched)
अणु
	अगर (!iso_sched)
		वापस;
	/* caller must hold fotg210->lock!*/
	list_splice(&iso_sched->td_list, &stream->मुक्त_list);
	kमुक्त(iso_sched);
पूर्ण

अटल पूर्णांक itd_urb_transaction(काष्ठा fotg210_iso_stream *stream,
		काष्ठा fotg210_hcd *fotg210, काष्ठा urb *urb, gfp_t mem_flags)
अणु
	काष्ठा fotg210_itd *itd;
	dma_addr_t itd_dma;
	पूर्णांक i;
	अचिन्हित num_itds;
	काष्ठा fotg210_iso_sched *sched;
	अचिन्हित दीर्घ flags;

	sched = iso_sched_alloc(urb->number_of_packets, mem_flags);
	अगर (unlikely(sched == शून्य))
		वापस -ENOMEM;

	itd_sched_init(fotg210, sched, stream, urb);

	अगर (urb->पूर्णांकerval < 8)
		num_itds = 1 + (sched->span + 7) / 8;
	अन्यथा
		num_itds = urb->number_of_packets;

	/* allocate/init ITDs */
	spin_lock_irqsave(&fotg210->lock, flags);
	क्रम (i = 0; i < num_itds; i++) अणु

		/*
		 * Use iTDs from the मुक्त list, but not iTDs that may
		 * still be in use by the hardware.
		 */
		अगर (likely(!list_empty(&stream->मुक्त_list))) अणु
			itd = list_first_entry(&stream->मुक्त_list,
					काष्ठा fotg210_itd, itd_list);
			अगर (itd->frame == fotg210->now_frame)
				जाओ alloc_itd;
			list_del(&itd->itd_list);
			itd_dma = itd->itd_dma;
		पूर्ण अन्यथा अणु
alloc_itd:
			spin_unlock_irqrestore(&fotg210->lock, flags);
			itd = dma_pool_zalloc(fotg210->itd_pool, mem_flags,
					&itd_dma);
			spin_lock_irqsave(&fotg210->lock, flags);
			अगर (!itd) अणु
				iso_sched_मुक्त(stream, sched);
				spin_unlock_irqrestore(&fotg210->lock, flags);
				वापस -ENOMEM;
			पूर्ण
		पूर्ण

		itd->itd_dma = itd_dma;
		list_add(&itd->itd_list, &sched->td_list);
	पूर्ण
	spin_unlock_irqrestore(&fotg210->lock, flags);

	/* temporarily store schedule info in hcpriv */
	urb->hcpriv = sched;
	urb->error_count = 0;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक itd_slot_ok(काष्ठा fotg210_hcd *fotg210, u32 mod, u32 uframe,
		u8 usecs, u32 period)
अणु
	uframe %= period;
	करो अणु
		/* can't commit more than uframe_periodic_max usec */
		अगर (periodic_usecs(fotg210, uframe >> 3, uframe & 0x7)
				> (fotg210->uframe_periodic_max - usecs))
			वापस 0;

		/* we know urb->पूर्णांकerval is 2^N uframes */
		uframe += period;
	पूर्ण जबतक (uframe < mod);
	वापस 1;
पूर्ण

/* This scheduler plans almost as far पूर्णांकo the future as it has actual
 * periodic schedule slots.  (Affected by TUNE_FLS, which शेषs to
 * "as small as possible" to be cache-मित्रlier.)  That limits the size
 * transfers you can stream reliably; aव्योम more than 64 msec per urb.
 * Also aव्योम queue depths of less than fotg210's worst irq latency (affected
 * by the per-urb URB_NO_INTERRUPT hपूर्णांक, the log2_irq_thresh module parameter,
 * and other factors); or more than about 230 msec total (क्रम portability,
 * given FOTG210_TUNE_FLS and the slop).  Or, ग_लिखो a smarter scheduler!
 */

#घोषणा SCHEDULE_SLOP 80 /* microframes */

अटल पूर्णांक iso_stream_schedule(काष्ठा fotg210_hcd *fotg210, काष्ठा urb *urb,
		काष्ठा fotg210_iso_stream *stream)
अणु
	u32 now, next, start, period, span;
	पूर्णांक status;
	अचिन्हित mod = fotg210->periodic_size << 3;
	काष्ठा fotg210_iso_sched *sched = urb->hcpriv;

	period = urb->पूर्णांकerval;
	span = sched->span;

	अगर (span > mod - SCHEDULE_SLOP) अणु
		fotg210_dbg(fotg210, "iso request %p too long\n", urb);
		status = -EFBIG;
		जाओ fail;
	पूर्ण

	now = fotg210_पढ़ो_frame_index(fotg210) & (mod - 1);

	/* Typical हाल: reuse current schedule, stream is still active.
	 * Hopefully there are no gaps from the host falling behind
	 * (irq delays etc), but अगर there are we'll take the next
	 * slot in the schedule, implicitly assuming URB_ISO_ASAP.
	 */
	अगर (likely(!list_empty(&stream->td_list))) अणु
		u32 excess;

		/* For high speed devices, allow scheduling within the
		 * isochronous scheduling threshold.  For full speed devices
		 * and Intel PCI-based controllers, करोn't (work around क्रम
		 * Intel ICH9 bug).
		 */
		अगर (!stream->highspeed && fotg210->fs_i_thresh)
			next = now + fotg210->i_thresh;
		अन्यथा
			next = now;

		/* Fell behind (by up to twice the slop amount)?
		 * We decide based on the समय of the last currently-scheduled
		 * slot, not the समय of the next available slot.
		 */
		excess = (stream->next_uframe - period - next) & (mod - 1);
		अगर (excess >= mod - 2 * SCHEDULE_SLOP)
			start = next + excess - mod + period *
					DIV_ROUND_UP(mod - excess, period);
		अन्यथा
			start = next + excess + period;
		अगर (start - now >= mod) अणु
			fotg210_dbg(fotg210, "request %p would overflow (%d+%d >= %d)\n",
					urb, start - now - period, period,
					mod);
			status = -EFBIG;
			जाओ fail;
		पूर्ण
	पूर्ण

	/* need to schedule; when's the next (u)frame we could start?
	 * this is bigger than fotg210->i_thresh allows; scheduling itself
	 * isn't मुक्त, the slop should handle reasonably slow cpus.  it
	 * can also help high bandwidth अगर the dma and irq loads करोn't
	 * jump until after the queue is primed.
	 */
	अन्यथा अणु
		पूर्णांक करोne = 0;

		start = SCHEDULE_SLOP + (now & ~0x07);

		/* NOTE:  assumes URB_ISO_ASAP, to limit complनिकासy/bugs */

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
			अगर (itd_slot_ok(fotg210, mod, start,
					stream->usecs, period))
				करोne = 1;
		पूर्ण जबतक (start > next && !करोne);

		/* no room in the schedule */
		अगर (!करोne) अणु
			fotg210_dbg(fotg210, "iso resched full %p (now %d max %d)\n",
					urb, now, now + mod);
			status = -ENOSPC;
			जाओ fail;
		पूर्ण
	पूर्ण

	/* Tried to schedule too far पूर्णांकo the future? */
	अगर (unlikely(start - now + span - period >=
			mod - 2 * SCHEDULE_SLOP)) अणु
		fotg210_dbg(fotg210, "request %p would overflow (%d+%d >= %d)\n",
				urb, start - now, span - period,
				mod - 2 * SCHEDULE_SLOP);
		status = -EFBIG;
		जाओ fail;
	पूर्ण

	stream->next_uframe = start & (mod - 1);

	/* report high speed start in uframes; full speed, in frames */
	urb->start_frame = stream->next_uframe;
	अगर (!stream->highspeed)
		urb->start_frame >>= 3;

	/* Make sure scan_isoc() sees these */
	अगर (fotg210->isoc_count == 0)
		fotg210->next_frame = now >> 3;
	वापस 0;

fail:
	iso_sched_मुक्त(stream, sched);
	urb->hcpriv = शून्य;
	वापस status;
पूर्ण

अटल अंतरभूत व्योम itd_init(काष्ठा fotg210_hcd *fotg210,
		काष्ठा fotg210_iso_stream *stream, काष्ठा fotg210_itd *itd)
अणु
	पूर्णांक i;

	/* it's been recently zeroed */
	itd->hw_next = FOTG210_LIST_END(fotg210);
	itd->hw_bufp[0] = stream->buf0;
	itd->hw_bufp[1] = stream->buf1;
	itd->hw_bufp[2] = stream->buf2;

	क्रम (i = 0; i < 8; i++)
		itd->index[i] = -1;

	/* All other fields are filled when scheduling */
पूर्ण

अटल अंतरभूत व्योम itd_patch(काष्ठा fotg210_hcd *fotg210,
		काष्ठा fotg210_itd *itd, काष्ठा fotg210_iso_sched *iso_sched,
		अचिन्हित index, u16 uframe)
अणु
	काष्ठा fotg210_iso_packet *uf = &iso_sched->packet[index];
	अचिन्हित pg = itd->pg;

	uframe &= 0x07;
	itd->index[uframe] = index;

	itd->hw_transaction[uframe] = uf->transaction;
	itd->hw_transaction[uframe] |= cpu_to_hc32(fotg210, pg << 12);
	itd->hw_bufp[pg] |= cpu_to_hc32(fotg210, uf->bufp & ~(u32)0);
	itd->hw_bufp_hi[pg] |= cpu_to_hc32(fotg210, (u32)(uf->bufp >> 32));

	/* iso_frame_desc[].offset must be strictly increasing */
	अगर (unlikely(uf->cross)) अणु
		u64 bufp = uf->bufp + 4096;

		itd->pg = ++pg;
		itd->hw_bufp[pg] |= cpu_to_hc32(fotg210, bufp & ~(u32)0);
		itd->hw_bufp_hi[pg] |= cpu_to_hc32(fotg210, (u32)(bufp >> 32));
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम itd_link(काष्ठा fotg210_hcd *fotg210, अचिन्हित frame,
		काष्ठा fotg210_itd *itd)
अणु
	जोड़ fotg210_shaकरोw *prev = &fotg210->pshaकरोw[frame];
	__hc32 *hw_p = &fotg210->periodic[frame];
	जोड़ fotg210_shaकरोw here = *prev;
	__hc32 type = 0;

	/* skip any iso nodes which might beदीर्घ to previous microframes */
	जबतक (here.ptr) अणु
		type = Q_NEXT_TYPE(fotg210, *hw_p);
		अगर (type == cpu_to_hc32(fotg210, Q_TYPE_QH))
			अवरोध;
		prev = periodic_next_shaकरोw(fotg210, prev, type);
		hw_p = shaकरोw_next_periodic(fotg210, &here, type);
		here = *prev;
	पूर्ण

	itd->itd_next = here;
	itd->hw_next = *hw_p;
	prev->itd = itd;
	itd->frame = frame;
	wmb();
	*hw_p = cpu_to_hc32(fotg210, itd->itd_dma | Q_TYPE_ITD);
पूर्ण

/* fit urb's itds पूर्णांकo the selected schedule slot; activate as needed */
अटल व्योम itd_link_urb(काष्ठा fotg210_hcd *fotg210, काष्ठा urb *urb,
		अचिन्हित mod, काष्ठा fotg210_iso_stream *stream)
अणु
	पूर्णांक packet;
	अचिन्हित next_uframe, uframe, frame;
	काष्ठा fotg210_iso_sched *iso_sched = urb->hcpriv;
	काष्ठा fotg210_itd *itd;

	next_uframe = stream->next_uframe & (mod - 1);

	अगर (unlikely(list_empty(&stream->td_list))) अणु
		fotg210_to_hcd(fotg210)->self.bandwidth_allocated
				+= stream->bandwidth;
		fotg210_dbg(fotg210,
			"schedule devp %s ep%d%s-iso period %d start %d.%d\n",
			urb->dev->devpath, stream->bEndpoपूर्णांकAddress & 0x0f,
			(stream->bEndpoपूर्णांकAddress & USB_सूची_IN) ? "in" : "out",
			urb->पूर्णांकerval,
			next_uframe >> 3, next_uframe & 0x7);
	पूर्ण

	/* fill iTDs uframe by uframe */
	क्रम (packet = 0, itd = शून्य; packet < urb->number_of_packets;) अणु
		अगर (itd == शून्य) अणु
			/* ASSERT:  we have all necessary itds */

			/* ASSERT:  no itds क्रम this endpoपूर्णांक in this uframe */

			itd = list_entry(iso_sched->td_list.next,
					काष्ठा fotg210_itd, itd_list);
			list_move_tail(&itd->itd_list, &stream->td_list);
			itd->stream = stream;
			itd->urb = urb;
			itd_init(fotg210, stream, itd);
		पूर्ण

		uframe = next_uframe & 0x07;
		frame = next_uframe >> 3;

		itd_patch(fotg210, itd, iso_sched, packet, uframe);

		next_uframe += stream->पूर्णांकerval;
		next_uframe &= mod - 1;
		packet++;

		/* link completed itds पूर्णांकo the schedule */
		अगर (((next_uframe >> 3) != frame)
				|| packet == urb->number_of_packets) अणु
			itd_link(fotg210, frame & (fotg210->periodic_size - 1),
					itd);
			itd = शून्य;
		पूर्ण
	पूर्ण
	stream->next_uframe = next_uframe;

	/* करोn't need that schedule data any more */
	iso_sched_मुक्त(stream, iso_sched);
	urb->hcpriv = शून्य;

	++fotg210->isoc_count;
	enable_periodic(fotg210);
पूर्ण

#घोषणा ISO_ERRS (FOTG210_ISOC_BUF_ERR | FOTG210_ISOC_BABBLE |\
		FOTG210_ISOC_XACTERR)

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
अटल bool itd_complete(काष्ठा fotg210_hcd *fotg210, काष्ठा fotg210_itd *itd)
अणु
	काष्ठा urb *urb = itd->urb;
	काष्ठा usb_iso_packet_descriptor *desc;
	u32 t;
	अचिन्हित uframe;
	पूर्णांक urb_index = -1;
	काष्ठा fotg210_iso_stream *stream = itd->stream;
	काष्ठा usb_device *dev;
	bool retval = false;

	/* क्रम each uframe with a packet */
	क्रम (uframe = 0; uframe < 8; uframe++) अणु
		अगर (likely(itd->index[uframe] == -1))
			जारी;
		urb_index = itd->index[uframe];
		desc = &urb->iso_frame_desc[urb_index];

		t = hc32_to_cpup(fotg210, &itd->hw_transaction[uframe]);
		itd->hw_transaction[uframe] = 0;

		/* report transfer status */
		अगर (unlikely(t & ISO_ERRS)) अणु
			urb->error_count++;
			अगर (t & FOTG210_ISOC_BUF_ERR)
				desc->status = usb_pipein(urb->pipe)
					? -ENOSR  /* hc couldn't पढ़ो */
					: -ECOMM; /* hc couldn't ग_लिखो */
			अन्यथा अगर (t & FOTG210_ISOC_BABBLE)
				desc->status = -EOVERFLOW;
			अन्यथा /* (t & FOTG210_ISOC_XACTERR) */
				desc->status = -EPROTO;

			/* HC need not update length with this error */
			अगर (!(t & FOTG210_ISOC_BABBLE)) अणु
				desc->actual_length =
					fotg210_itdlen(urb, desc, t);
				urb->actual_length += desc->actual_length;
			पूर्ण
		पूर्ण अन्यथा अगर (likely((t & FOTG210_ISOC_ACTIVE) == 0)) अणु
			desc->status = 0;
			desc->actual_length = fotg210_itdlen(urb, desc, t);
			urb->actual_length += desc->actual_length;
		पूर्ण अन्यथा अणु
			/* URB was too late */
			desc->status = -EXDEV;
		पूर्ण
	पूर्ण

	/* handle completion now? */
	अगर (likely((urb_index + 1) != urb->number_of_packets))
		जाओ करोne;

	/* ASSERT: it's really the last itd क्रम this urb
	 * list_क्रम_each_entry (itd, &stream->td_list, itd_list)
	 *	BUG_ON (itd->urb == urb);
	 */

	/* give urb back to the driver; completion often (re)submits */
	dev = urb->dev;
	fotg210_urb_करोne(fotg210, urb, 0);
	retval = true;
	urb = शून्य;

	--fotg210->isoc_count;
	disable_periodic(fotg210);

	अगर (unlikely(list_is_singular(&stream->td_list))) अणु
		fotg210_to_hcd(fotg210)->self.bandwidth_allocated
				-= stream->bandwidth;
		fotg210_dbg(fotg210,
			"deschedule devp %s ep%d%s-iso\n",
			dev->devpath, stream->bEndpoपूर्णांकAddress & 0x0f,
			(stream->bEndpoपूर्णांकAddress & USB_सूची_IN) ? "in" : "out");
	पूर्ण

करोne:
	itd->urb = शून्य;

	/* Add to the end of the मुक्त list क्रम later reuse */
	list_move_tail(&itd->itd_list, &stream->मुक्त_list);

	/* Recycle the iTDs when the pipeline is empty (ep no दीर्घer in use) */
	अगर (list_empty(&stream->td_list)) अणु
		list_splice_tail_init(&stream->मुक्त_list,
				&fotg210->cached_itd_list);
		start_मुक्त_itds(fotg210);
	पूर्ण

	वापस retval;
पूर्ण

अटल पूर्णांक itd_submit(काष्ठा fotg210_hcd *fotg210, काष्ठा urb *urb,
		gfp_t mem_flags)
अणु
	पूर्णांक status = -EINVAL;
	अचिन्हित दीर्घ flags;
	काष्ठा fotg210_iso_stream *stream;

	/* Get iso_stream head */
	stream = iso_stream_find(fotg210, urb);
	अगर (unlikely(stream == शून्य)) अणु
		fotg210_dbg(fotg210, "can't get iso stream\n");
		वापस -ENOMEM;
	पूर्ण
	अगर (unlikely(urb->पूर्णांकerval != stream->पूर्णांकerval &&
			fotg210_port_speed(fotg210, 0) ==
			USB_PORT_STAT_HIGH_SPEED)) अणु
		fotg210_dbg(fotg210, "can't change iso interval %d --> %d\n",
				stream->पूर्णांकerval, urb->पूर्णांकerval);
		जाओ करोne;
	पूर्ण

#अगर_घोषित FOTG210_URB_TRACE
	fotg210_dbg(fotg210,
			"%s %s urb %p ep%d%s len %d, %d pkts %d uframes[%p]\n",
			__func__, urb->dev->devpath, urb,
			usb_pipeendpoपूर्णांक(urb->pipe),
			usb_pipein(urb->pipe) ? "in" : "out",
			urb->transfer_buffer_length,
			urb->number_of_packets, urb->पूर्णांकerval,
			stream);
#पूर्ण_अगर

	/* allocate ITDs w/o locking anything */
	status = itd_urb_transaction(stream, fotg210, urb, mem_flags);
	अगर (unlikely(status < 0)) अणु
		fotg210_dbg(fotg210, "can't init itds\n");
		जाओ करोne;
	पूर्ण

	/* schedule ... need to lock */
	spin_lock_irqsave(&fotg210->lock, flags);
	अगर (unlikely(!HCD_HW_ACCESSIBLE(fotg210_to_hcd(fotg210)))) अणु
		status = -ESHUTDOWN;
		जाओ करोne_not_linked;
	पूर्ण
	status = usb_hcd_link_urb_to_ep(fotg210_to_hcd(fotg210), urb);
	अगर (unlikely(status))
		जाओ करोne_not_linked;
	status = iso_stream_schedule(fotg210, urb, stream);
	अगर (likely(status == 0))
		itd_link_urb(fotg210, urb, fotg210->periodic_size << 3, stream);
	अन्यथा
		usb_hcd_unlink_urb_from_ep(fotg210_to_hcd(fotg210), urb);
करोne_not_linked:
	spin_unlock_irqrestore(&fotg210->lock, flags);
करोne:
	वापस status;
पूर्ण

अटल अंतरभूत पूर्णांक scan_frame_queue(काष्ठा fotg210_hcd *fotg210, अचिन्हित frame,
		अचिन्हित now_frame, bool live)
अणु
	अचिन्हित uf;
	bool modअगरied;
	जोड़ fotg210_shaकरोw q, *q_p;
	__hc32 type, *hw_p;

	/* scan each element in frame's queue क्रम completions */
	q_p = &fotg210->pshaकरोw[frame];
	hw_p = &fotg210->periodic[frame];
	q.ptr = q_p->ptr;
	type = Q_NEXT_TYPE(fotg210, *hw_p);
	modअगरied = false;

	जबतक (q.ptr) अणु
		चयन (hc32_to_cpu(fotg210, type)) अणु
		हाल Q_TYPE_ITD:
			/* If this ITD is still active, leave it क्रम
			 * later processing ... check the next entry.
			 * No need to check क्रम activity unless the
			 * frame is current.
			 */
			अगर (frame == now_frame && live) अणु
				rmb();
				क्रम (uf = 0; uf < 8; uf++) अणु
					अगर (q.itd->hw_transaction[uf] &
							ITD_ACTIVE(fotg210))
						अवरोध;
				पूर्ण
				अगर (uf < 8) अणु
					q_p = &q.itd->itd_next;
					hw_p = &q.itd->hw_next;
					type = Q_NEXT_TYPE(fotg210,
							q.itd->hw_next);
					q = *q_p;
					अवरोध;
				पूर्ण
			पूर्ण

			/* Take finished ITDs out of the schedule
			 * and process them:  recycle, maybe report
			 * URB completion.  HC won't cache the
			 * poपूर्णांकer क्रम much दीर्घer, अगर at all.
			 */
			*q_p = q.itd->itd_next;
			*hw_p = q.itd->hw_next;
			type = Q_NEXT_TYPE(fotg210, q.itd->hw_next);
			wmb();
			modअगरied = itd_complete(fotg210, q.itd);
			q = *q_p;
			अवरोध;
		शेष:
			fotg210_dbg(fotg210, "corrupt type %d frame %d shadow %p\n",
					type, frame, q.ptr);
			fallthrough;
		हाल Q_TYPE_QH:
		हाल Q_TYPE_FSTN:
			/* End of the iTDs and siTDs */
			q.ptr = शून्य;
			अवरोध;
		पूर्ण

		/* assume completion callbacks modअगरy the queue */
		अगर (unlikely(modअगरied && fotg210->isoc_count > 0))
			वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम scan_isoc(काष्ठा fotg210_hcd *fotg210)
अणु
	अचिन्हित uf, now_frame, frame, ret;
	अचिन्हित fmask = fotg210->periodic_size - 1;
	bool live;

	/*
	 * When running, scan from last scan poपूर्णांक up to "now"
	 * अन्यथा clean up by scanning everything that's left.
	 * Touches as few pages as possible:  cache-मित्रly.
	 */
	अगर (fotg210->rh_state >= FOTG210_RH_RUNNING) अणु
		uf = fotg210_पढ़ो_frame_index(fotg210);
		now_frame = (uf >> 3) & fmask;
		live = true;
	पूर्ण अन्यथा  अणु
		now_frame = (fotg210->next_frame - 1) & fmask;
		live = false;
	पूर्ण
	fotg210->now_frame = now_frame;

	frame = fotg210->next_frame;
	क्रम (;;) अणु
		ret = 1;
		जबतक (ret != 0)
			ret = scan_frame_queue(fotg210, frame,
					now_frame, live);

		/* Stop when we have reached the current frame */
		अगर (frame == now_frame)
			अवरोध;
		frame = (frame + 1) & fmask;
	पूर्ण
	fotg210->next_frame = now_frame;
पूर्ण

/* Display / Set uframe_periodic_max
 */
अटल sमाप_प्रकार uframe_periodic_max_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा fotg210_hcd *fotg210;
	पूर्णांक n;

	fotg210 = hcd_to_fotg210(bus_to_hcd(dev_get_drvdata(dev)));
	n = scnम_लिखो(buf, PAGE_SIZE, "%d\n", fotg210->uframe_periodic_max);
	वापस n;
पूर्ण


अटल sमाप_प्रकार uframe_periodic_max_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा fotg210_hcd *fotg210;
	अचिन्हित uframe_periodic_max;
	अचिन्हित frame, uframe;
	अचिन्हित लघु allocated_max;
	अचिन्हित दीर्घ flags;
	sमाप_प्रकार ret;

	fotg210 = hcd_to_fotg210(bus_to_hcd(dev_get_drvdata(dev)));
	अगर (kstrtouपूर्णांक(buf, 0, &uframe_periodic_max) < 0)
		वापस -EINVAL;

	अगर (uframe_periodic_max < 100 || uframe_periodic_max >= 125) अणु
		fotg210_info(fotg210, "rejecting invalid request for uframe_periodic_max=%u\n",
				uframe_periodic_max);
		वापस -EINVAL;
	पूर्ण

	ret = -EINVAL;

	/*
	 * lock, so that our checking करोes not race with possible periodic
	 * bandwidth allocation through submitting new urbs.
	 */
	spin_lock_irqsave(&fotg210->lock, flags);

	/*
	 * क्रम request to decrease max periodic bandwidth, we have to check
	 * every microframe in the schedule to see whether the decrease is
	 * possible.
	 */
	अगर (uframe_periodic_max < fotg210->uframe_periodic_max) अणु
		allocated_max = 0;

		क्रम (frame = 0; frame < fotg210->periodic_size; ++frame)
			क्रम (uframe = 0; uframe < 7; ++uframe)
				allocated_max = max(allocated_max,
						periodic_usecs(fotg210, frame,
						uframe));

		अगर (allocated_max > uframe_periodic_max) अणु
			fotg210_info(fotg210,
					"cannot decrease uframe_periodic_max because periodic bandwidth is already allocated (%u > %u)\n",
					allocated_max, uframe_periodic_max);
			जाओ out_unlock;
		पूर्ण
	पूर्ण

	/* increasing is always ok */

	fotg210_info(fotg210,
			"setting max periodic bandwidth to %u%% (== %u usec/uframe)\n",
			100 * uframe_periodic_max/125, uframe_periodic_max);

	अगर (uframe_periodic_max != 100)
		fotg210_warn(fotg210, "max periodic bandwidth set is non-standard\n");

	fotg210->uframe_periodic_max = uframe_periodic_max;
	ret = count;

out_unlock:
	spin_unlock_irqrestore(&fotg210->lock, flags);
	वापस ret;
पूर्ण

अटल DEVICE_ATTR_RW(uframe_periodic_max);

अटल अंतरभूत पूर्णांक create_sysfs_files(काष्ठा fotg210_hcd *fotg210)
अणु
	काष्ठा device *controller = fotg210_to_hcd(fotg210)->self.controller;

	वापस device_create_file(controller, &dev_attr_uframe_periodic_max);
पूर्ण

अटल अंतरभूत व्योम हटाओ_sysfs_files(काष्ठा fotg210_hcd *fotg210)
अणु
	काष्ठा device *controller = fotg210_to_hcd(fotg210)->self.controller;

	device_हटाओ_file(controller, &dev_attr_uframe_periodic_max);
पूर्ण
/* On some प्रणालीs, leaving remote wakeup enabled prevents प्रणाली shutकरोwn.
 * The firmware seems to think that घातering off is a wakeup event!
 * This routine turns off remote wakeup and everything अन्यथा, on all ports.
 */
अटल व्योम fotg210_turn_off_all_ports(काष्ठा fotg210_hcd *fotg210)
अणु
	u32 __iomem *status_reg = &fotg210->regs->port_status;

	fotg210_ग_लिखोl(fotg210, PORT_RWC_BITS, status_reg);
पूर्ण

/* Halt HC, turn off all ports, and let the BIOS use the companion controllers.
 * Must be called with पूर्णांकerrupts enabled and the lock not held.
 */
अटल व्योम fotg210_silence_controller(काष्ठा fotg210_hcd *fotg210)
अणु
	fotg210_halt(fotg210);

	spin_lock_irq(&fotg210->lock);
	fotg210->rh_state = FOTG210_RH_HALTED;
	fotg210_turn_off_all_ports(fotg210);
	spin_unlock_irq(&fotg210->lock);
पूर्ण

/* fotg210_shutकरोwn kick in क्रम silicon on any bus (not just pci, etc).
 * This क्रमcibly disables dma and IRQs, helping kexec and other हालs
 * where the next प्रणाली software may expect clean state.
 */
अटल व्योम fotg210_shutकरोwn(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा fotg210_hcd *fotg210 = hcd_to_fotg210(hcd);

	spin_lock_irq(&fotg210->lock);
	fotg210->shutकरोwn = true;
	fotg210->rh_state = FOTG210_RH_STOPPING;
	fotg210->enabled_hrसमयr_events = 0;
	spin_unlock_irq(&fotg210->lock);

	fotg210_silence_controller(fotg210);

	hrसमयr_cancel(&fotg210->hrसमयr);
पूर्ण

/* fotg210_work is called from some पूर्णांकerrupts, समयrs, and so on.
 * it calls driver completion functions, after dropping fotg210->lock.
 */
अटल व्योम fotg210_work(काष्ठा fotg210_hcd *fotg210)
अणु
	/* another CPU may drop fotg210->lock during a schedule scan जबतक
	 * it reports urb completions.  this flag guards against bogus
	 * attempts at re-entrant schedule scanning.
	 */
	अगर (fotg210->scanning) अणु
		fotg210->need_rescan = true;
		वापस;
	पूर्ण
	fotg210->scanning = true;

rescan:
	fotg210->need_rescan = false;
	अगर (fotg210->async_count)
		scan_async(fotg210);
	अगर (fotg210->पूर्णांकr_count > 0)
		scan_पूर्णांकr(fotg210);
	अगर (fotg210->isoc_count > 0)
		scan_isoc(fotg210);
	अगर (fotg210->need_rescan)
		जाओ rescan;
	fotg210->scanning = false;

	/* the IO watchकरोg guards against hardware or driver bugs that
	 * misplace IRQs, and should let us run completely without IRQs.
	 * such lossage has been observed on both VT6202 and VT8235.
	 */
	turn_on_io_watchकरोg(fotg210);
पूर्ण

/* Called when the fotg210_hcd module is हटाओd.
 */
अटल व्योम fotg210_stop(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा fotg210_hcd *fotg210 = hcd_to_fotg210(hcd);

	fotg210_dbg(fotg210, "stop\n");

	/* no more पूर्णांकerrupts ... */

	spin_lock_irq(&fotg210->lock);
	fotg210->enabled_hrसमयr_events = 0;
	spin_unlock_irq(&fotg210->lock);

	fotg210_quiesce(fotg210);
	fotg210_silence_controller(fotg210);
	fotg210_reset(fotg210);

	hrसमयr_cancel(&fotg210->hrसमयr);
	हटाओ_sysfs_files(fotg210);
	हटाओ_debug_files(fotg210);

	/* root hub is shut करोwn separately (first, when possible) */
	spin_lock_irq(&fotg210->lock);
	end_मुक्त_itds(fotg210);
	spin_unlock_irq(&fotg210->lock);
	fotg210_mem_cleanup(fotg210);

#अगर_घोषित FOTG210_STATS
	fotg210_dbg(fotg210, "irq normal %ld err %ld iaa %ld (lost %ld)\n",
			fotg210->stats.normal, fotg210->stats.error,
			fotg210->stats.iaa, fotg210->stats.lost_iaa);
	fotg210_dbg(fotg210, "complete %ld unlink %ld\n",
			fotg210->stats.complete, fotg210->stats.unlink);
#पूर्ण_अगर

	dbg_status(fotg210, "fotg210_stop completed",
			fotg210_पढ़ोl(fotg210, &fotg210->regs->status));
पूर्ण

/* one-समय init, only क्रम memory state */
अटल पूर्णांक hcd_fotg210_init(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा fotg210_hcd *fotg210 = hcd_to_fotg210(hcd);
	u32 temp;
	पूर्णांक retval;
	u32 hcc_params;
	काष्ठा fotg210_qh_hw *hw;

	spin_lock_init(&fotg210->lock);

	/*
	 * keep io watchकरोg by शेष, those good HCDs could turn off it later
	 */
	fotg210->need_io_watchकरोg = 1;

	hrसमयr_init(&fotg210->hrसमयr, CLOCK_MONOTONIC, HRTIMER_MODE_ABS);
	fotg210->hrसमयr.function = fotg210_hrसमयr_func;
	fotg210->next_hrसमयr_event = FOTG210_HRTIMER_NO_EVENT;

	hcc_params = fotg210_पढ़ोl(fotg210, &fotg210->caps->hcc_params);

	/*
	 * by शेष set standard 80% (== 100 usec/uframe) max periodic
	 * bandwidth as required by USB 2.0
	 */
	fotg210->uframe_periodic_max = 100;

	/*
	 * hw शेष: 1K periodic list heads, one per frame.
	 * periodic_size can shrink by USBCMD update अगर hcc_params allows.
	 */
	fotg210->periodic_size = DEFAULT_I_TDPS;
	INIT_LIST_HEAD(&fotg210->पूर्णांकr_qh_list);
	INIT_LIST_HEAD(&fotg210->cached_itd_list);

	अगर (HCC_PGM_FRAMELISTLEN(hcc_params)) अणु
		/* periodic schedule size can be smaller than शेष */
		चयन (FOTG210_TUNE_FLS) अणु
		हाल 0:
			fotg210->periodic_size = 1024;
			अवरोध;
		हाल 1:
			fotg210->periodic_size = 512;
			अवरोध;
		हाल 2:
			fotg210->periodic_size = 256;
			अवरोध;
		शेष:
			BUG();
		पूर्ण
	पूर्ण
	retval = fotg210_mem_init(fotg210, GFP_KERNEL);
	अगर (retval < 0)
		वापस retval;

	/* controllers may cache some of the periodic schedule ... */
	fotg210->i_thresh = 2;

	/*
	 * dedicate a qh क्रम the async ring head, since we couldn't unlink
	 * a 'real' qh without stopping the async schedule [4.8].  use it
	 * as the 'reclamation list head' too.
	 * its dummy is used in hw_alt_next of many tds, to prevent the qh
	 * from स्वतःmatically advancing to the next td after लघु पढ़ोs.
	 */
	fotg210->async->qh_next.qh = शून्य;
	hw = fotg210->async->hw;
	hw->hw_next = QH_NEXT(fotg210, fotg210->async->qh_dma);
	hw->hw_info1 = cpu_to_hc32(fotg210, QH_HEAD);
	hw->hw_token = cpu_to_hc32(fotg210, QTD_STS_HALT);
	hw->hw_qtd_next = FOTG210_LIST_END(fotg210);
	fotg210->async->qh_state = QH_STATE_LINKED;
	hw->hw_alt_next = QTD_NEXT(fotg210, fotg210->async->dummy->qtd_dma);

	/* clear पूर्णांकerrupt enables, set irq latency */
	अगर (log2_irq_thresh < 0 || log2_irq_thresh > 6)
		log2_irq_thresh = 0;
	temp = 1 << (16 + log2_irq_thresh);
	अगर (HCC_CANPARK(hcc_params)) अणु
		/* HW शेष park == 3, on hardware that supports it (like
		 * NVidia and ALI silicon), maximizes throughput on the async
		 * schedule by aव्योमing QH fetches between transfers.
		 *
		 * With fast usb storage devices and NForce2, "park" seems to
		 * make problems:  throughput reduction (!), data errors...
		 */
		अगर (park) अणु
			park = min_t(अचिन्हित, park, 3);
			temp |= CMD_PARK;
			temp |= park << 8;
		पूर्ण
		fotg210_dbg(fotg210, "park %d\n", park);
	पूर्ण
	अगर (HCC_PGM_FRAMELISTLEN(hcc_params)) अणु
		/* periodic schedule size can be smaller than शेष */
		temp &= ~(3 << 2);
		temp |= (FOTG210_TUNE_FLS << 2);
	पूर्ण
	fotg210->command = temp;

	/* Accept arbitrarily दीर्घ scatter-gather lists */
	अगर (!hcd->localmem_pool)
		hcd->self.sg_tablesize = ~0;
	वापस 0;
पूर्ण

/* start HC running; it's halted, hcd_fotg210_init() has been run (once) */
अटल पूर्णांक fotg210_run(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा fotg210_hcd *fotg210 = hcd_to_fotg210(hcd);
	u32 temp;

	hcd->uses_new_polling = 1;

	/* EHCI spec section 4.1 */

	fotg210_ग_लिखोl(fotg210, fotg210->periodic_dma,
			&fotg210->regs->frame_list);
	fotg210_ग_लिखोl(fotg210, (u32)fotg210->async->qh_dma,
			&fotg210->regs->async_next);

	/*
	 * hcc_params controls whether fotg210->regs->segment must (!!!)
	 * be used; it स्थिरrains QH/ITD/SITD and QTD locations.
	 * dma_pool consistent memory always uses segment zero.
	 * streaming mappings क्रम I/O buffers, like pci_map_single(),
	 * can वापस segments above 4GB, अगर the device allows.
	 *
	 * NOTE:  the dma mask is visible through dev->dma_mask, so
	 * drivers can pass this info aदीर्घ ... like NETIF_F_HIGHDMA,
	 * Scsi_Host.highmem_io, and so क्रमth.  It's पढ़ोonly to all
	 * host side drivers though.
	 */
	fotg210_पढ़ोl(fotg210, &fotg210->caps->hcc_params);

	/*
	 * Philips, Intel, and maybe others need CMD_RUN beक्रमe the
	 * root hub will detect new devices (why?); NEC करोesn't
	 */
	fotg210->command &= ~(CMD_IAAD|CMD_PSE|CMD_ASE|CMD_RESET);
	fotg210->command |= CMD_RUN;
	fotg210_ग_लिखोl(fotg210, fotg210->command, &fotg210->regs->command);
	dbg_cmd(fotg210, "init", fotg210->command);

	/*
	 * Start, enabling full USB 2.0 functionality ... usb 1.1 devices
	 * are explicitly handed to companion controller(s), so no TT is
	 * involved with the root hub.  (Except where one is पूर्णांकegrated,
	 * and there's no companion controller unless maybe क्रम USB OTG.)
	 *
	 * Turning on the CF flag will transfer ownership of all ports
	 * from the companions to the EHCI controller.  If any of the
	 * companions are in the middle of a port reset at the समय, it
	 * could cause trouble.  Write-locking ehci_cf_port_reset_rwsem
	 * guarantees that no resets are in progress.  After we set CF,
	 * a लघु delay lets the hardware catch up; new resets shouldn't
	 * be started beक्रमe the port चयनing actions could complete.
	 */
	करोwn_ग_लिखो(&ehci_cf_port_reset_rwsem);
	fotg210->rh_state = FOTG210_RH_RUNNING;
	/* unblock posted ग_लिखोs */
	fotg210_पढ़ोl(fotg210, &fotg210->regs->command);
	usleep_range(5000, 10000);
	up_ग_लिखो(&ehci_cf_port_reset_rwsem);
	fotg210->last_periodic_enable = kसमय_get_real();

	temp = HC_VERSION(fotg210,
			fotg210_पढ़ोl(fotg210, &fotg210->caps->hc_capbase));
	fotg210_info(fotg210,
			"USB %x.%x started, EHCI %x.%02x\n",
			((fotg210->sbrn & 0xf0) >> 4), (fotg210->sbrn & 0x0f),
			temp >> 8, temp & 0xff);

	fotg210_ग_लिखोl(fotg210, INTR_MASK,
			&fotg210->regs->पूर्णांकr_enable); /* Turn On Interrupts */

	/* GRR this is run-once init(), being करोne every समय the HC starts.
	 * So दीर्घ as they're part of class devices, we can't करो it init()
	 * since the class device isn't created that early.
	 */
	create_debug_files(fotg210);
	create_sysfs_files(fotg210);

	वापस 0;
पूर्ण

अटल पूर्णांक fotg210_setup(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा fotg210_hcd *fotg210 = hcd_to_fotg210(hcd);
	पूर्णांक retval;

	fotg210->regs = (व्योम __iomem *)fotg210->caps +
			HC_LENGTH(fotg210,
			fotg210_पढ़ोl(fotg210, &fotg210->caps->hc_capbase));
	dbg_hcs_params(fotg210, "reset");
	dbg_hcc_params(fotg210, "reset");

	/* cache this पढ़ोonly data; minimize chip पढ़ोs */
	fotg210->hcs_params = fotg210_पढ़ोl(fotg210,
			&fotg210->caps->hcs_params);

	fotg210->sbrn = HCD_USB2;

	/* data काष्ठाure init */
	retval = hcd_fotg210_init(hcd);
	अगर (retval)
		वापस retval;

	retval = fotg210_halt(fotg210);
	अगर (retval)
		वापस retval;

	fotg210_reset(fotg210);

	वापस 0;
पूर्ण

अटल irqवापस_t fotg210_irq(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा fotg210_hcd *fotg210 = hcd_to_fotg210(hcd);
	u32 status, masked_status, pcd_status = 0, cmd;
	पूर्णांक bh;

	spin_lock(&fotg210->lock);

	status = fotg210_पढ़ोl(fotg210, &fotg210->regs->status);

	/* e.g. cardbus physical eject */
	अगर (status == ~(u32) 0) अणु
		fotg210_dbg(fotg210, "device removed\n");
		जाओ dead;
	पूर्ण

	/*
	 * We करोn't use STS_FLR, but some controllers don't like it to
	 * reमुख्य on, so mask it out aदीर्घ with the other status bits.
	 */
	masked_status = status & (INTR_MASK | STS_FLR);

	/* Shared IRQ? */
	अगर (!masked_status ||
			unlikely(fotg210->rh_state == FOTG210_RH_HALTED)) अणु
		spin_unlock(&fotg210->lock);
		वापस IRQ_NONE;
	पूर्ण

	/* clear (just) पूर्णांकerrupts */
	fotg210_ग_लिखोl(fotg210, masked_status, &fotg210->regs->status);
	cmd = fotg210_पढ़ोl(fotg210, &fotg210->regs->command);
	bh = 0;

	/* unrequested/ignored: Frame List Rollover */
	dbg_status(fotg210, "irq", status);

	/* INT, ERR, and IAA पूर्णांकerrupt rates can be throttled */

	/* normal [4.15.1.2] or error [4.15.1.1] completion */
	अगर (likely((status & (STS_INT|STS_ERR)) != 0)) अणु
		अगर (likely((status & STS_ERR) == 0))
			INCR(fotg210->stats.normal);
		अन्यथा
			INCR(fotg210->stats.error);
		bh = 1;
	पूर्ण

	/* complete the unlinking of some qh [4.15.2.3] */
	अगर (status & STS_IAA) अणु

		/* Turn off the IAA watchकरोg */
		fotg210->enabled_hrसमयr_events &=
			~BIT(FOTG210_HRTIMER_IAA_WATCHDOG);

		/*
		 * Mild optimization: Allow another IAAD to reset the
		 * hrसमयr, अगर one occurs beक्रमe the next expiration.
		 * In theory we could always cancel the hrसमयr, but
		 * tests show that about half the समय it will be reset
		 * क्रम some other event anyway.
		 */
		अगर (fotg210->next_hrसमयr_event == FOTG210_HRTIMER_IAA_WATCHDOG)
			++fotg210->next_hrसमयr_event;

		/* guard against (alleged) silicon errata */
		अगर (cmd & CMD_IAAD)
			fotg210_dbg(fotg210, "IAA with IAAD still set?\n");
		अगर (fotg210->async_iaa) अणु
			INCR(fotg210->stats.iaa);
			end_unlink_async(fotg210);
		पूर्ण अन्यथा
			fotg210_dbg(fotg210, "IAA with nothing unlinked?\n");
	पूर्ण

	/* remote wakeup [4.3.1] */
	अगर (status & STS_PCD) अणु
		पूर्णांक pstatus;
		u32 __iomem *status_reg = &fotg210->regs->port_status;

		/* kick root hub later */
		pcd_status = status;

		/* resume root hub? */
		अगर (fotg210->rh_state == FOTG210_RH_SUSPENDED)
			usb_hcd_resume_root_hub(hcd);

		pstatus = fotg210_पढ़ोl(fotg210, status_reg);

		अगर (test_bit(0, &fotg210->suspended_ports) &&
				((pstatus & PORT_RESUME) ||
				!(pstatus & PORT_SUSPEND)) &&
				(pstatus & PORT_PE) &&
				fotg210->reset_करोne[0] == 0) अणु

			/* start 20 msec resume संकेतing from this port,
			 * and make hub_wq collect PORT_STAT_C_SUSPEND to
			 * stop that संकेतing.  Use 5 ms extra क्रम safety,
			 * like usb_port_resume() करोes.
			 */
			fotg210->reset_करोne[0] = jअगरfies + msecs_to_jअगरfies(25);
			set_bit(0, &fotg210->resuming_ports);
			fotg210_dbg(fotg210, "port 1 remote wakeup\n");
			mod_समयr(&hcd->rh_समयr, fotg210->reset_करोne[0]);
		पूर्ण
	पूर्ण

	/* PCI errors [4.15.2.4] */
	अगर (unlikely((status & STS_FATAL) != 0)) अणु
		fotg210_err(fotg210, "fatal error\n");
		dbg_cmd(fotg210, "fatal", cmd);
		dbg_status(fotg210, "fatal", status);
dead:
		usb_hc_died(hcd);

		/* Don't let the controller करो anything more */
		fotg210->shutकरोwn = true;
		fotg210->rh_state = FOTG210_RH_STOPPING;
		fotg210->command &= ~(CMD_RUN | CMD_ASE | CMD_PSE);
		fotg210_ग_लिखोl(fotg210, fotg210->command,
				&fotg210->regs->command);
		fotg210_ग_लिखोl(fotg210, 0, &fotg210->regs->पूर्णांकr_enable);
		fotg210_handle_controller_death(fotg210);

		/* Handle completions when the controller stops */
		bh = 0;
	पूर्ण

	अगर (bh)
		fotg210_work(fotg210);
	spin_unlock(&fotg210->lock);
	अगर (pcd_status)
		usb_hcd_poll_rh_status(hcd);
	वापस IRQ_HANDLED;
पूर्ण

/* non-error वापसs are a promise to giveback() the urb later
 * we drop ownership so next owner (or urb unlink) can get it
 *
 * urb + dev is in hcd.self.controller.urb_list
 * we're queueing TDs onto software and hardware lists
 *
 * hcd-specअगरic init क्रम hcpriv hasn't been करोne yet
 *
 * NOTE:  control, bulk, and पूर्णांकerrupt share the same code to append TDs
 * to a (possibly active) QH, and the same QH scanning code.
 */
अटल पूर्णांक fotg210_urb_enqueue(काष्ठा usb_hcd *hcd, काष्ठा urb *urb,
		gfp_t mem_flags)
अणु
	काष्ठा fotg210_hcd *fotg210 = hcd_to_fotg210(hcd);
	काष्ठा list_head qtd_list;

	INIT_LIST_HEAD(&qtd_list);

	चयन (usb_pipetype(urb->pipe)) अणु
	हाल PIPE_CONTROL:
		/* qh_completions() code करोesn't handle all the fault हालs
		 * in multi-TD control transfers.  Even 1KB is rare anyway.
		 */
		अगर (urb->transfer_buffer_length > (16 * 1024))
			वापस -EMSGSIZE;
		fallthrough;
	/* हाल PIPE_BULK: */
	शेष:
		अगर (!qh_urb_transaction(fotg210, urb, &qtd_list, mem_flags))
			वापस -ENOMEM;
		वापस submit_async(fotg210, urb, &qtd_list, mem_flags);

	हाल PIPE_INTERRUPT:
		अगर (!qh_urb_transaction(fotg210, urb, &qtd_list, mem_flags))
			वापस -ENOMEM;
		वापस पूर्णांकr_submit(fotg210, urb, &qtd_list, mem_flags);

	हाल PIPE_ISOCHRONOUS:
		वापस itd_submit(fotg210, urb, mem_flags);
	पूर्ण
पूर्ण

/* हटाओ from hardware lists
 * completions normally happen asynchronously
 */

अटल पूर्णांक fotg210_urb_dequeue(काष्ठा usb_hcd *hcd, काष्ठा urb *urb, पूर्णांक status)
अणु
	काष्ठा fotg210_hcd *fotg210 = hcd_to_fotg210(hcd);
	काष्ठा fotg210_qh *qh;
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;

	spin_lock_irqsave(&fotg210->lock, flags);
	rc = usb_hcd_check_unlink_urb(hcd, urb, status);
	अगर (rc)
		जाओ करोne;

	चयन (usb_pipetype(urb->pipe)) अणु
	/* हाल PIPE_CONTROL: */
	/* हाल PIPE_BULK:*/
	शेष:
		qh = (काष्ठा fotg210_qh *) urb->hcpriv;
		अगर (!qh)
			अवरोध;
		चयन (qh->qh_state) अणु
		हाल QH_STATE_LINKED:
		हाल QH_STATE_COMPLETING:
			start_unlink_async(fotg210, qh);
			अवरोध;
		हाल QH_STATE_UNLINK:
		हाल QH_STATE_UNLINK_WAIT:
			/* alपढ़ोy started */
			अवरोध;
		हाल QH_STATE_IDLE:
			/* QH might be रुकोing क्रम a Clear-TT-Buffer */
			qh_completions(fotg210, qh);
			अवरोध;
		पूर्ण
		अवरोध;

	हाल PIPE_INTERRUPT:
		qh = (काष्ठा fotg210_qh *) urb->hcpriv;
		अगर (!qh)
			अवरोध;
		चयन (qh->qh_state) अणु
		हाल QH_STATE_LINKED:
		हाल QH_STATE_COMPLETING:
			start_unlink_पूर्णांकr(fotg210, qh);
			अवरोध;
		हाल QH_STATE_IDLE:
			qh_completions(fotg210, qh);
			अवरोध;
		शेष:
			fotg210_dbg(fotg210, "bogus qh %p state %d\n",
					qh, qh->qh_state);
			जाओ करोne;
		पूर्ण
		अवरोध;

	हाल PIPE_ISOCHRONOUS:
		/* itd... */

		/* रुको till next completion, करो it then. */
		/* completion irqs can रुको up to 1024 msec, */
		अवरोध;
	पूर्ण
करोne:
	spin_unlock_irqrestore(&fotg210->lock, flags);
	वापस rc;
पूर्ण

/* bulk qh holds the data toggle */

अटल व्योम fotg210_endpoपूर्णांक_disable(काष्ठा usb_hcd *hcd,
		काष्ठा usb_host_endpoपूर्णांक *ep)
अणु
	काष्ठा fotg210_hcd *fotg210 = hcd_to_fotg210(hcd);
	अचिन्हित दीर्घ flags;
	काष्ठा fotg210_qh *qh, *पंचांगp;

	/* ASSERT:  any requests/urbs are being unlinked */
	/* ASSERT:  nobody can be submitting urbs क्रम this any more */

rescan:
	spin_lock_irqsave(&fotg210->lock, flags);
	qh = ep->hcpriv;
	अगर (!qh)
		जाओ करोne;

	/* endpoपूर्णांकs can be iso streams.  क्रम now, we करोn't
	 * accelerate iso completions ... so spin a जबतक.
	 */
	अगर (qh->hw == शून्य) अणु
		काष्ठा fotg210_iso_stream *stream = ep->hcpriv;

		अगर (!list_empty(&stream->td_list))
			जाओ idle_समयout;

		/* BUG_ON(!list_empty(&stream->मुक्त_list)); */
		kमुक्त(stream);
		जाओ करोne;
	पूर्ण

	अगर (fotg210->rh_state < FOTG210_RH_RUNNING)
		qh->qh_state = QH_STATE_IDLE;
	चयन (qh->qh_state) अणु
	हाल QH_STATE_LINKED:
	हाल QH_STATE_COMPLETING:
		क्रम (पंचांगp = fotg210->async->qh_next.qh;
				पंचांगp && पंचांगp != qh;
				पंचांगp = पंचांगp->qh_next.qh)
			जारी;
		/* periodic qh self-unlinks on empty, and a COMPLETING qh
		 * may alपढ़ोy be unlinked.
		 */
		अगर (पंचांगp)
			start_unlink_async(fotg210, qh);
		fallthrough;
	हाल QH_STATE_UNLINK:		/* रुको क्रम hw to finish? */
	हाल QH_STATE_UNLINK_WAIT:
idle_समयout:
		spin_unlock_irqrestore(&fotg210->lock, flags);
		schedule_समयout_unपूर्णांकerruptible(1);
		जाओ rescan;
	हाल QH_STATE_IDLE:		/* fully unlinked */
		अगर (qh->clearing_tt)
			जाओ idle_समयout;
		अगर (list_empty(&qh->qtd_list)) अणु
			qh_destroy(fotg210, qh);
			अवरोध;
		पूर्ण
		fallthrough;
	शेष:
		/* caller was supposed to have unlinked any requests;
		 * that's not our job.  just leak this memory.
		 */
		fotg210_err(fotg210, "qh %p (#%02x) state %d%s\n",
				qh, ep->desc.bEndpoपूर्णांकAddress, qh->qh_state,
				list_empty(&qh->qtd_list) ? "" : "(has tds)");
		अवरोध;
	पूर्ण
करोne:
	ep->hcpriv = शून्य;
	spin_unlock_irqrestore(&fotg210->lock, flags);
पूर्ण

अटल व्योम fotg210_endpoपूर्णांक_reset(काष्ठा usb_hcd *hcd,
		काष्ठा usb_host_endpoपूर्णांक *ep)
अणु
	काष्ठा fotg210_hcd *fotg210 = hcd_to_fotg210(hcd);
	काष्ठा fotg210_qh *qh;
	पूर्णांक eptype = usb_endpoपूर्णांक_type(&ep->desc);
	पूर्णांक epnum = usb_endpoपूर्णांक_num(&ep->desc);
	पूर्णांक is_out = usb_endpoपूर्णांक_dir_out(&ep->desc);
	अचिन्हित दीर्घ flags;

	अगर (eptype != USB_ENDPOINT_XFER_BULK && eptype != USB_ENDPOINT_XFER_INT)
		वापस;

	spin_lock_irqsave(&fotg210->lock, flags);
	qh = ep->hcpriv;

	/* For Bulk and Interrupt endpoपूर्णांकs we मुख्यtain the toggle state
	 * in the hardware; the toggle bits in udev aren't used at all.
	 * When an endpoपूर्णांक is reset by usb_clear_halt() we must reset
	 * the toggle bit in the QH.
	 */
	अगर (qh) अणु
		usb_settoggle(qh->dev, epnum, is_out, 0);
		अगर (!list_empty(&qh->qtd_list)) अणु
			WARN_ONCE(1, "clear_halt for a busy endpoint\n");
		पूर्ण अन्यथा अगर (qh->qh_state == QH_STATE_LINKED ||
				qh->qh_state == QH_STATE_COMPLETING) अणु

			/* The toggle value in the QH can't be updated
			 * जबतक the QH is active.  Unlink it now;
			 * re-linking will call qh_refresh().
			 */
			अगर (eptype == USB_ENDPOINT_XFER_BULK)
				start_unlink_async(fotg210, qh);
			अन्यथा
				start_unlink_पूर्णांकr(fotg210, qh);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&fotg210->lock, flags);
पूर्ण

अटल पूर्णांक fotg210_get_frame(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा fotg210_hcd *fotg210 = hcd_to_fotg210(hcd);

	वापस (fotg210_पढ़ो_frame_index(fotg210) >> 3) %
		fotg210->periodic_size;
पूर्ण

/* The EHCI in ChipIdea HDRC cannot be a separate module or device,
 * because its रेजिस्टरs (and irq) are shared between host/gadget/otg
 * functions  and in order to facilitate role चयनing we cannot
 * give the fotg210 driver exclusive access to those.
 */
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_LICENSE("GPL");

अटल स्थिर काष्ठा hc_driver fotg210_fotg210_hc_driver = अणु
	.description		= hcd_name,
	.product_desc		= "Faraday USB2.0 Host Controller",
	.hcd_priv_size		= माप(काष्ठा fotg210_hcd),

	/*
	 * generic hardware linkage
	 */
	.irq			= fotg210_irq,
	.flags			= HCD_MEMORY | HCD_DMA | HCD_USB2,

	/*
	 * basic lअगरecycle operations
	 */
	.reset			= hcd_fotg210_init,
	.start			= fotg210_run,
	.stop			= fotg210_stop,
	.shutकरोwn		= fotg210_shutकरोwn,

	/*
	 * managing i/o requests and associated device resources
	 */
	.urb_enqueue		= fotg210_urb_enqueue,
	.urb_dequeue		= fotg210_urb_dequeue,
	.endpoपूर्णांक_disable	= fotg210_endpoपूर्णांक_disable,
	.endpoपूर्णांक_reset		= fotg210_endpoपूर्णांक_reset,

	/*
	 * scheduling support
	 */
	.get_frame_number	= fotg210_get_frame,

	/*
	 * root hub support
	 */
	.hub_status_data	= fotg210_hub_status_data,
	.hub_control		= fotg210_hub_control,
	.bus_suspend		= fotg210_bus_suspend,
	.bus_resume		= fotg210_bus_resume,

	.relinquish_port	= fotg210_relinquish_port,
	.port_handed_over	= fotg210_port_handed_over,

	.clear_tt_buffer_complete = fotg210_clear_tt_buffer_complete,
पूर्ण;

अटल व्योम fotg210_init(काष्ठा fotg210_hcd *fotg210)
अणु
	u32 value;

	ioग_लिखो32(GMIR_MDEV_INT | GMIR_MOTG_INT | GMIR_INT_POLARITY,
			&fotg210->regs->gmir);

	value = ioपढ़ो32(&fotg210->regs->otgcsr);
	value &= ~OTGCSR_A_BUS_DROP;
	value |= OTGCSR_A_BUS_REQ;
	ioग_लिखो32(value, &fotg210->regs->otgcsr);
पूर्ण

/*
 * fotg210_hcd_probe - initialize faraday FOTG210 HCDs
 *
 * Allocates basic resources क्रम this USB host controller, and
 * then invokes the start() method क्रम the HCD associated with it
 * through the hotplug entry's driver_data.
 */
अटल पूर्णांक fotg210_hcd_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा usb_hcd *hcd;
	काष्ठा resource *res;
	पूर्णांक irq;
	पूर्णांक retval;
	काष्ठा fotg210_hcd *fotg210;

	अगर (usb_disabled())
		वापस -ENODEV;

	pdev->dev.घातer.घातer_state = PMSG_ON;

	res = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
	अगर (!res) अणु
		dev_err(dev, "Found HC with no IRQ. Check %s setup!\n",
				dev_name(dev));
		वापस -ENODEV;
	पूर्ण

	irq = res->start;

	hcd = usb_create_hcd(&fotg210_fotg210_hc_driver, dev,
			dev_name(dev));
	अगर (!hcd) अणु
		dev_err(dev, "failed to create hcd\n");
		retval = -ENOMEM;
		जाओ fail_create_hcd;
	पूर्ण

	hcd->has_tt = 1;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	hcd->regs = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(hcd->regs)) अणु
		retval = PTR_ERR(hcd->regs);
		जाओ failed_put_hcd;
	पूर्ण

	hcd->rsrc_start = res->start;
	hcd->rsrc_len = resource_size(res);

	fotg210 = hcd_to_fotg210(hcd);

	fotg210->caps = hcd->regs;

	/* It's OK not to supply this घड़ी */
	fotg210->pclk = clk_get(dev, "PCLK");
	अगर (!IS_ERR(fotg210->pclk)) अणु
		retval = clk_prepare_enable(fotg210->pclk);
		अगर (retval) अणु
			dev_err(dev, "failed to enable PCLK\n");
			जाओ failed_put_hcd;
		पूर्ण
	पूर्ण अन्यथा अगर (PTR_ERR(fotg210->pclk) == -EPROBE_DEFER) अणु
		/*
		 * Percolate deferrals, क्रम anything अन्यथा,
		 * just live without the घड़ीing.
		 */
		retval = PTR_ERR(fotg210->pclk);
		जाओ failed_dis_clk;
	पूर्ण

	retval = fotg210_setup(hcd);
	अगर (retval)
		जाओ failed_dis_clk;

	fotg210_init(fotg210);

	retval = usb_add_hcd(hcd, irq, IRQF_SHARED);
	अगर (retval) अणु
		dev_err(dev, "failed to add hcd with err %d\n", retval);
		जाओ failed_dis_clk;
	पूर्ण
	device_wakeup_enable(hcd->self.controller);
	platक्रमm_set_drvdata(pdev, hcd);

	वापस retval;

failed_dis_clk:
	अगर (!IS_ERR(fotg210->pclk)) अणु
		clk_disable_unprepare(fotg210->pclk);
		clk_put(fotg210->pclk);
	पूर्ण
failed_put_hcd:
	usb_put_hcd(hcd);
fail_create_hcd:
	dev_err(dev, "init %s fail, %d\n", dev_name(dev), retval);
	वापस retval;
पूर्ण

/*
 * fotg210_hcd_हटाओ - shutकरोwn processing क्रम EHCI HCDs
 * @dev: USB Host Controller being हटाओd
 *
 */
अटल पूर्णांक fotg210_hcd_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा usb_hcd *hcd = platक्रमm_get_drvdata(pdev);
	काष्ठा fotg210_hcd *fotg210 = hcd_to_fotg210(hcd);

	अगर (!IS_ERR(fotg210->pclk)) अणु
		clk_disable_unprepare(fotg210->pclk);
		clk_put(fotg210->pclk);
	पूर्ण

	usb_हटाओ_hcd(hcd);
	usb_put_hcd(hcd);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id fotg210_of_match[] = अणु
	अणु .compatible = "faraday,fotg210" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, fotg210_of_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver fotg210_hcd_driver = अणु
	.driver = अणु
		.name   = "fotg210-hcd",
		.of_match_table = of_match_ptr(fotg210_of_match),
	पूर्ण,
	.probe  = fotg210_hcd_probe,
	.हटाओ = fotg210_hcd_हटाओ,
पूर्ण;

अटल पूर्णांक __init fotg210_hcd_init(व्योम)
अणु
	पूर्णांक retval = 0;

	अगर (usb_disabled())
		वापस -ENODEV;

	pr_info("%s: " DRIVER_DESC "\n", hcd_name);
	set_bit(USB_EHCI_LOADED, &usb_hcds_loaded);
	अगर (test_bit(USB_UHCI_LOADED, &usb_hcds_loaded) ||
			test_bit(USB_OHCI_LOADED, &usb_hcds_loaded))
		pr_warn("Warning! fotg210_hcd should always be loaded before uhci_hcd and ohci_hcd, not after\n");

	pr_debug("%s: block sizes: qh %zd qtd %zd itd %zd\n",
			hcd_name, माप(काष्ठा fotg210_qh),
			माप(काष्ठा fotg210_qtd),
			माप(काष्ठा fotg210_itd));

	fotg210_debug_root = debugfs_create_dir("fotg210", usb_debug_root);

	retval = platक्रमm_driver_रेजिस्टर(&fotg210_hcd_driver);
	अगर (retval < 0)
		जाओ clean;
	वापस retval;

clean:
	debugfs_हटाओ(fotg210_debug_root);
	fotg210_debug_root = शून्य;

	clear_bit(USB_EHCI_LOADED, &usb_hcds_loaded);
	वापस retval;
पूर्ण
module_init(fotg210_hcd_init);

अटल व्योम __निकास fotg210_hcd_cleanup(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&fotg210_hcd_driver);
	debugfs_हटाओ(fotg210_debug_root);
	clear_bit(USB_EHCI_LOADED, &usb_hcds_loaded);
पूर्ण
module_निकास(fotg210_hcd_cleanup);
