<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * debugfs.c - DesignWare USB3 DRD Controller DebugFS file
 *
 * Copyright (C) 2010-2011 Texas Instruments Incorporated - https://www.ti.com
 *
 * Authors: Felipe Balbi <balbi@ti.com>,
 *	    Sebastian Andrzej Siewior <bigeasy@linutronix.de>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/types.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/delay.h>
#समावेश <linux/uaccess.h>

#समावेश <linux/usb/ch9.h>

#समावेश "core.h"
#समावेश "gadget.h"
#समावेश "io.h"
#समावेश "debug.h"

#घोषणा DWC3_LSP_MUX_UNSELECTED 0xfffff

#घोषणा dump_रेजिस्टर(nm)				\
अणु							\
	.name	= __stringअगरy(nm),			\
	.offset	= DWC3_ ##nm,				\
पूर्ण

#घोषणा dump_ep_रेजिस्टर_set(n)			\
	अणु					\
		.name = "DEPCMDPAR2("__stringअगरy(n)")",	\
		.offset = DWC3_DEP_BASE(n) +	\
			DWC3_DEPCMDPAR2,	\
	पूर्ण,					\
	अणु					\
		.name = "DEPCMDPAR1("__stringअगरy(n)")",	\
		.offset = DWC3_DEP_BASE(n) +	\
			DWC3_DEPCMDPAR1,	\
	पूर्ण,					\
	अणु					\
		.name = "DEPCMDPAR0("__stringअगरy(n)")",	\
		.offset = DWC3_DEP_BASE(n) +	\
			DWC3_DEPCMDPAR0,	\
	पूर्ण,					\
	अणु					\
		.name = "DEPCMD("__stringअगरy(n)")",	\
		.offset = DWC3_DEP_BASE(n) +	\
			DWC3_DEPCMD,		\
	पूर्ण


अटल स्थिर काष्ठा debugfs_reg32 dwc3_regs[] = अणु
	dump_रेजिस्टर(GSBUSCFG0),
	dump_रेजिस्टर(GSBUSCFG1),
	dump_रेजिस्टर(GTXTHRCFG),
	dump_रेजिस्टर(GRXTHRCFG),
	dump_रेजिस्टर(GCTL),
	dump_रेजिस्टर(GEVTEN),
	dump_रेजिस्टर(GSTS),
	dump_रेजिस्टर(GUCTL1),
	dump_रेजिस्टर(GSNPSID),
	dump_रेजिस्टर(GGPIO),
	dump_रेजिस्टर(GUID),
	dump_रेजिस्टर(GUCTL),
	dump_रेजिस्टर(GBUSERRADDR0),
	dump_रेजिस्टर(GBUSERRADDR1),
	dump_रेजिस्टर(GPRTBIMAP0),
	dump_रेजिस्टर(GPRTBIMAP1),
	dump_रेजिस्टर(GHWPARAMS0),
	dump_रेजिस्टर(GHWPARAMS1),
	dump_रेजिस्टर(GHWPARAMS2),
	dump_रेजिस्टर(GHWPARAMS3),
	dump_रेजिस्टर(GHWPARAMS4),
	dump_रेजिस्टर(GHWPARAMS5),
	dump_रेजिस्टर(GHWPARAMS6),
	dump_रेजिस्टर(GHWPARAMS7),
	dump_रेजिस्टर(GDBGFIFOSPACE),
	dump_रेजिस्टर(GDBGLTSSM),
	dump_रेजिस्टर(GDBGBMU),
	dump_रेजिस्टर(GPRTBIMAP_HS0),
	dump_रेजिस्टर(GPRTBIMAP_HS1),
	dump_रेजिस्टर(GPRTBIMAP_FS0),
	dump_रेजिस्टर(GPRTBIMAP_FS1),

	dump_रेजिस्टर(GUSB2PHYCFG(0)),
	dump_रेजिस्टर(GUSB2PHYCFG(1)),
	dump_रेजिस्टर(GUSB2PHYCFG(2)),
	dump_रेजिस्टर(GUSB2PHYCFG(3)),
	dump_रेजिस्टर(GUSB2PHYCFG(4)),
	dump_रेजिस्टर(GUSB2PHYCFG(5)),
	dump_रेजिस्टर(GUSB2PHYCFG(6)),
	dump_रेजिस्टर(GUSB2PHYCFG(7)),
	dump_रेजिस्टर(GUSB2PHYCFG(8)),
	dump_रेजिस्टर(GUSB2PHYCFG(9)),
	dump_रेजिस्टर(GUSB2PHYCFG(10)),
	dump_रेजिस्टर(GUSB2PHYCFG(11)),
	dump_रेजिस्टर(GUSB2PHYCFG(12)),
	dump_रेजिस्टर(GUSB2PHYCFG(13)),
	dump_रेजिस्टर(GUSB2PHYCFG(14)),
	dump_रेजिस्टर(GUSB2PHYCFG(15)),

	dump_रेजिस्टर(GUSB2I2CCTL(0)),
	dump_रेजिस्टर(GUSB2I2CCTL(1)),
	dump_रेजिस्टर(GUSB2I2CCTL(2)),
	dump_रेजिस्टर(GUSB2I2CCTL(3)),
	dump_रेजिस्टर(GUSB2I2CCTL(4)),
	dump_रेजिस्टर(GUSB2I2CCTL(5)),
	dump_रेजिस्टर(GUSB2I2CCTL(6)),
	dump_रेजिस्टर(GUSB2I2CCTL(7)),
	dump_रेजिस्टर(GUSB2I2CCTL(8)),
	dump_रेजिस्टर(GUSB2I2CCTL(9)),
	dump_रेजिस्टर(GUSB2I2CCTL(10)),
	dump_रेजिस्टर(GUSB2I2CCTL(11)),
	dump_रेजिस्टर(GUSB2I2CCTL(12)),
	dump_रेजिस्टर(GUSB2I2CCTL(13)),
	dump_रेजिस्टर(GUSB2I2CCTL(14)),
	dump_रेजिस्टर(GUSB2I2CCTL(15)),

	dump_रेजिस्टर(GUSB2PHYACC(0)),
	dump_रेजिस्टर(GUSB2PHYACC(1)),
	dump_रेजिस्टर(GUSB2PHYACC(2)),
	dump_रेजिस्टर(GUSB2PHYACC(3)),
	dump_रेजिस्टर(GUSB2PHYACC(4)),
	dump_रेजिस्टर(GUSB2PHYACC(5)),
	dump_रेजिस्टर(GUSB2PHYACC(6)),
	dump_रेजिस्टर(GUSB2PHYACC(7)),
	dump_रेजिस्टर(GUSB2PHYACC(8)),
	dump_रेजिस्टर(GUSB2PHYACC(9)),
	dump_रेजिस्टर(GUSB2PHYACC(10)),
	dump_रेजिस्टर(GUSB2PHYACC(11)),
	dump_रेजिस्टर(GUSB2PHYACC(12)),
	dump_रेजिस्टर(GUSB2PHYACC(13)),
	dump_रेजिस्टर(GUSB2PHYACC(14)),
	dump_रेजिस्टर(GUSB2PHYACC(15)),

	dump_रेजिस्टर(GUSB3PIPECTL(0)),
	dump_रेजिस्टर(GUSB3PIPECTL(1)),
	dump_रेजिस्टर(GUSB3PIPECTL(2)),
	dump_रेजिस्टर(GUSB3PIPECTL(3)),
	dump_रेजिस्टर(GUSB3PIPECTL(4)),
	dump_रेजिस्टर(GUSB3PIPECTL(5)),
	dump_रेजिस्टर(GUSB3PIPECTL(6)),
	dump_रेजिस्टर(GUSB3PIPECTL(7)),
	dump_रेजिस्टर(GUSB3PIPECTL(8)),
	dump_रेजिस्टर(GUSB3PIPECTL(9)),
	dump_रेजिस्टर(GUSB3PIPECTL(10)),
	dump_रेजिस्टर(GUSB3PIPECTL(11)),
	dump_रेजिस्टर(GUSB3PIPECTL(12)),
	dump_रेजिस्टर(GUSB3PIPECTL(13)),
	dump_रेजिस्टर(GUSB3PIPECTL(14)),
	dump_रेजिस्टर(GUSB3PIPECTL(15)),

	dump_रेजिस्टर(GTXFIFOSIZ(0)),
	dump_रेजिस्टर(GTXFIFOSIZ(1)),
	dump_रेजिस्टर(GTXFIFOSIZ(2)),
	dump_रेजिस्टर(GTXFIFOSIZ(3)),
	dump_रेजिस्टर(GTXFIFOSIZ(4)),
	dump_रेजिस्टर(GTXFIFOSIZ(5)),
	dump_रेजिस्टर(GTXFIFOSIZ(6)),
	dump_रेजिस्टर(GTXFIFOSIZ(7)),
	dump_रेजिस्टर(GTXFIFOSIZ(8)),
	dump_रेजिस्टर(GTXFIFOSIZ(9)),
	dump_रेजिस्टर(GTXFIFOSIZ(10)),
	dump_रेजिस्टर(GTXFIFOSIZ(11)),
	dump_रेजिस्टर(GTXFIFOSIZ(12)),
	dump_रेजिस्टर(GTXFIFOSIZ(13)),
	dump_रेजिस्टर(GTXFIFOSIZ(14)),
	dump_रेजिस्टर(GTXFIFOSIZ(15)),
	dump_रेजिस्टर(GTXFIFOSIZ(16)),
	dump_रेजिस्टर(GTXFIFOSIZ(17)),
	dump_रेजिस्टर(GTXFIFOSIZ(18)),
	dump_रेजिस्टर(GTXFIFOSIZ(19)),
	dump_रेजिस्टर(GTXFIFOSIZ(20)),
	dump_रेजिस्टर(GTXFIFOSIZ(21)),
	dump_रेजिस्टर(GTXFIFOSIZ(22)),
	dump_रेजिस्टर(GTXFIFOSIZ(23)),
	dump_रेजिस्टर(GTXFIFOSIZ(24)),
	dump_रेजिस्टर(GTXFIFOSIZ(25)),
	dump_रेजिस्टर(GTXFIFOSIZ(26)),
	dump_रेजिस्टर(GTXFIFOSIZ(27)),
	dump_रेजिस्टर(GTXFIFOSIZ(28)),
	dump_रेजिस्टर(GTXFIFOSIZ(29)),
	dump_रेजिस्टर(GTXFIFOSIZ(30)),
	dump_रेजिस्टर(GTXFIFOSIZ(31)),

	dump_रेजिस्टर(GRXFIFOSIZ(0)),
	dump_रेजिस्टर(GRXFIFOSIZ(1)),
	dump_रेजिस्टर(GRXFIFOSIZ(2)),
	dump_रेजिस्टर(GRXFIFOSIZ(3)),
	dump_रेजिस्टर(GRXFIFOSIZ(4)),
	dump_रेजिस्टर(GRXFIFOSIZ(5)),
	dump_रेजिस्टर(GRXFIFOSIZ(6)),
	dump_रेजिस्टर(GRXFIFOSIZ(7)),
	dump_रेजिस्टर(GRXFIFOSIZ(8)),
	dump_रेजिस्टर(GRXFIFOSIZ(9)),
	dump_रेजिस्टर(GRXFIFOSIZ(10)),
	dump_रेजिस्टर(GRXFIFOSIZ(11)),
	dump_रेजिस्टर(GRXFIFOSIZ(12)),
	dump_रेजिस्टर(GRXFIFOSIZ(13)),
	dump_रेजिस्टर(GRXFIFOSIZ(14)),
	dump_रेजिस्टर(GRXFIFOSIZ(15)),
	dump_रेजिस्टर(GRXFIFOSIZ(16)),
	dump_रेजिस्टर(GRXFIFOSIZ(17)),
	dump_रेजिस्टर(GRXFIFOSIZ(18)),
	dump_रेजिस्टर(GRXFIFOSIZ(19)),
	dump_रेजिस्टर(GRXFIFOSIZ(20)),
	dump_रेजिस्टर(GRXFIFOSIZ(21)),
	dump_रेजिस्टर(GRXFIFOSIZ(22)),
	dump_रेजिस्टर(GRXFIFOSIZ(23)),
	dump_रेजिस्टर(GRXFIFOSIZ(24)),
	dump_रेजिस्टर(GRXFIFOSIZ(25)),
	dump_रेजिस्टर(GRXFIFOSIZ(26)),
	dump_रेजिस्टर(GRXFIFOSIZ(27)),
	dump_रेजिस्टर(GRXFIFOSIZ(28)),
	dump_रेजिस्टर(GRXFIFOSIZ(29)),
	dump_रेजिस्टर(GRXFIFOSIZ(30)),
	dump_रेजिस्टर(GRXFIFOSIZ(31)),

	dump_रेजिस्टर(GEVNTADRLO(0)),
	dump_रेजिस्टर(GEVNTADRHI(0)),
	dump_रेजिस्टर(GEVNTSIZ(0)),
	dump_रेजिस्टर(GEVNTCOUNT(0)),

	dump_रेजिस्टर(GHWPARAMS8),
	dump_रेजिस्टर(DCFG),
	dump_रेजिस्टर(DCTL),
	dump_रेजिस्टर(DEVTEN),
	dump_रेजिस्टर(DSTS),
	dump_रेजिस्टर(DGCMDPAR),
	dump_रेजिस्टर(DGCMD),
	dump_रेजिस्टर(DALEPENA),

	dump_ep_रेजिस्टर_set(0),
	dump_ep_रेजिस्टर_set(1),
	dump_ep_रेजिस्टर_set(2),
	dump_ep_रेजिस्टर_set(3),
	dump_ep_रेजिस्टर_set(4),
	dump_ep_रेजिस्टर_set(5),
	dump_ep_रेजिस्टर_set(6),
	dump_ep_रेजिस्टर_set(7),
	dump_ep_रेजिस्टर_set(8),
	dump_ep_रेजिस्टर_set(9),
	dump_ep_रेजिस्टर_set(10),
	dump_ep_रेजिस्टर_set(11),
	dump_ep_रेजिस्टर_set(12),
	dump_ep_रेजिस्टर_set(13),
	dump_ep_रेजिस्टर_set(14),
	dump_ep_रेजिस्टर_set(15),
	dump_ep_रेजिस्टर_set(16),
	dump_ep_रेजिस्टर_set(17),
	dump_ep_रेजिस्टर_set(18),
	dump_ep_रेजिस्टर_set(19),
	dump_ep_रेजिस्टर_set(20),
	dump_ep_रेजिस्टर_set(21),
	dump_ep_रेजिस्टर_set(22),
	dump_ep_रेजिस्टर_set(23),
	dump_ep_रेजिस्टर_set(24),
	dump_ep_रेजिस्टर_set(25),
	dump_ep_रेजिस्टर_set(26),
	dump_ep_रेजिस्टर_set(27),
	dump_ep_रेजिस्टर_set(28),
	dump_ep_रेजिस्टर_set(29),
	dump_ep_रेजिस्टर_set(30),
	dump_ep_रेजिस्टर_set(31),

	dump_रेजिस्टर(OCFG),
	dump_रेजिस्टर(OCTL),
	dump_रेजिस्टर(OEVT),
	dump_रेजिस्टर(OEVTEN),
	dump_रेजिस्टर(OSTS),
पूर्ण;

अटल व्योम dwc3_host_lsp(काष्ठा seq_file *s)
अणु
	काष्ठा dwc3		*dwc = s->निजी;
	bool			dbc_enabled;
	u32			sel;
	u32			reg;
	u32			val;

	dbc_enabled = !!(dwc->hwparams.hwparams1 & DWC3_GHWPARAMS1_ENDBC);

	sel = dwc->dbg_lsp_select;
	अगर (sel == DWC3_LSP_MUX_UNSELECTED) अणु
		seq_माला_दो(s, "Write LSP selection to print for host\n");
		वापस;
	पूर्ण

	reg = DWC3_GDBGLSPMUX_HOSTSELECT(sel);

	dwc3_ग_लिखोl(dwc->regs, DWC3_GDBGLSPMUX, reg);
	val = dwc3_पढ़ोl(dwc->regs, DWC3_GDBGLSP);
	seq_म_लिखो(s, "GDBGLSP[%d] = 0x%08x\n", sel, val);

	अगर (dbc_enabled && sel < 256) अणु
		reg |= DWC3_GDBGLSPMUX_ENDBC;
		dwc3_ग_लिखोl(dwc->regs, DWC3_GDBGLSPMUX, reg);
		val = dwc3_पढ़ोl(dwc->regs, DWC3_GDBGLSP);
		seq_म_लिखो(s, "GDBGLSP_DBC[%d] = 0x%08x\n", sel, val);
	पूर्ण
पूर्ण

अटल व्योम dwc3_gadget_lsp(काष्ठा seq_file *s)
अणु
	काष्ठा dwc3		*dwc = s->निजी;
	पूर्णांक			i;
	u32			reg;

	क्रम (i = 0; i < 16; i++) अणु
		reg = DWC3_GDBGLSPMUX_DEVSELECT(i);
		dwc3_ग_लिखोl(dwc->regs, DWC3_GDBGLSPMUX, reg);
		reg = dwc3_पढ़ोl(dwc->regs, DWC3_GDBGLSP);
		seq_म_लिखो(s, "GDBGLSP[%d] = 0x%08x\n", i, reg);
	पूर्ण
पूर्ण

अटल पूर्णांक dwc3_lsp_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा dwc3		*dwc = s->निजी;
	अचिन्हित पूर्णांक		current_mode;
	अचिन्हित दीर्घ		flags;
	u32			reg;

	spin_lock_irqsave(&dwc->lock, flags);
	reg = dwc3_पढ़ोl(dwc->regs, DWC3_GSTS);
	current_mode = DWC3_GSTS_CURMOD(reg);

	चयन (current_mode) अणु
	हाल DWC3_GSTS_CURMOD_HOST:
		dwc3_host_lsp(s);
		अवरोध;
	हाल DWC3_GSTS_CURMOD_DEVICE:
		dwc3_gadget_lsp(s);
		अवरोध;
	शेष:
		seq_माला_दो(s, "Mode is unknown, no LSP register printed\n");
		अवरोध;
	पूर्ण
	spin_unlock_irqrestore(&dwc->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक dwc3_lsp_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, dwc3_lsp_show, inode->i_निजी);
पूर्ण

अटल sमाप_प्रकार dwc3_lsp_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *ubuf,
			      माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा seq_file		*s = file->निजी_data;
	काष्ठा dwc3		*dwc = s->निजी;
	अचिन्हित दीर्घ		flags;
	अक्षर			buf[32] = अणु 0 पूर्ण;
	u32			sel;
	पूर्णांक			ret;

	अगर (copy_from_user(&buf, ubuf, min_t(माप_प्रकार, माप(buf) - 1, count)))
		वापस -EFAULT;

	ret = kstrtouपूर्णांक(buf, 0, &sel);
	अगर (ret)
		वापस ret;

	spin_lock_irqsave(&dwc->lock, flags);
	dwc->dbg_lsp_select = sel;
	spin_unlock_irqrestore(&dwc->lock, flags);

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations dwc3_lsp_fops = अणु
	.खोलो			= dwc3_lsp_खोलो,
	.ग_लिखो			= dwc3_lsp_ग_लिखो,
	.पढ़ो			= seq_पढ़ो,
	.llseek			= seq_lseek,
	.release		= single_release,
पूर्ण;

अटल पूर्णांक dwc3_mode_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा dwc3		*dwc = s->निजी;
	अचिन्हित दीर्घ		flags;
	u32			reg;

	spin_lock_irqsave(&dwc->lock, flags);
	reg = dwc3_पढ़ोl(dwc->regs, DWC3_GCTL);
	spin_unlock_irqrestore(&dwc->lock, flags);

	चयन (DWC3_GCTL_PRTCAP(reg)) अणु
	हाल DWC3_GCTL_PRTCAP_HOST:
		seq_माला_दो(s, "host\n");
		अवरोध;
	हाल DWC3_GCTL_PRTCAP_DEVICE:
		seq_माला_दो(s, "device\n");
		अवरोध;
	हाल DWC3_GCTL_PRTCAP_OTG:
		seq_माला_दो(s, "otg\n");
		अवरोध;
	शेष:
		seq_म_लिखो(s, "UNKNOWN %08x\n", DWC3_GCTL_PRTCAP(reg));
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dwc3_mode_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, dwc3_mode_show, inode->i_निजी);
पूर्ण

अटल sमाप_प्रकार dwc3_mode_ग_लिखो(काष्ठा file *file,
		स्थिर अक्षर __user *ubuf, माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा seq_file		*s = file->निजी_data;
	काष्ठा dwc3		*dwc = s->निजी;
	u32			mode = 0;
	अक्षर			buf[32];

	अगर (copy_from_user(&buf, ubuf, min_t(माप_प्रकार, माप(buf) - 1, count)))
		वापस -EFAULT;

	अगर (dwc->dr_mode != USB_DR_MODE_OTG)
		वापस count;

	अगर (!म_भेदन(buf, "host", 4))
		mode = DWC3_GCTL_PRTCAP_HOST;

	अगर (!म_भेदन(buf, "device", 6))
		mode = DWC3_GCTL_PRTCAP_DEVICE;

	अगर (!म_भेदन(buf, "otg", 3))
		mode = DWC3_GCTL_PRTCAP_OTG;

	dwc3_set_mode(dwc, mode);

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations dwc3_mode_fops = अणु
	.खोलो			= dwc3_mode_खोलो,
	.ग_लिखो			= dwc3_mode_ग_लिखो,
	.पढ़ो			= seq_पढ़ो,
	.llseek			= seq_lseek,
	.release		= single_release,
पूर्ण;

अटल पूर्णांक dwc3_tesपंचांगode_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा dwc3		*dwc = s->निजी;
	अचिन्हित दीर्घ		flags;
	u32			reg;

	spin_lock_irqsave(&dwc->lock, flags);
	reg = dwc3_पढ़ोl(dwc->regs, DWC3_DCTL);
	reg &= DWC3_DCTL_TSTCTRL_MASK;
	reg >>= 1;
	spin_unlock_irqrestore(&dwc->lock, flags);

	चयन (reg) अणु
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
		seq_म_लिखो(s, "UNKNOWN %d\n", reg);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dwc3_tesपंचांगode_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, dwc3_tesपंचांगode_show, inode->i_निजी);
पूर्ण

अटल sमाप_प्रकार dwc3_tesपंचांगode_ग_लिखो(काष्ठा file *file,
		स्थिर अक्षर __user *ubuf, माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा seq_file		*s = file->निजी_data;
	काष्ठा dwc3		*dwc = s->निजी;
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

	spin_lock_irqsave(&dwc->lock, flags);
	dwc3_gadget_set_test_mode(dwc, tesपंचांगode);
	spin_unlock_irqrestore(&dwc->lock, flags);

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations dwc3_tesपंचांगode_fops = अणु
	.खोलो			= dwc3_tesपंचांगode_खोलो,
	.ग_लिखो			= dwc3_tesपंचांगode_ग_लिखो,
	.पढ़ो			= seq_पढ़ो,
	.llseek			= seq_lseek,
	.release		= single_release,
पूर्ण;

अटल पूर्णांक dwc3_link_state_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा dwc3		*dwc = s->निजी;
	अचिन्हित दीर्घ		flags;
	क्रमागत dwc3_link_state	state;
	u32			reg;
	u8			speed;

	spin_lock_irqsave(&dwc->lock, flags);
	reg = dwc3_पढ़ोl(dwc->regs, DWC3_GSTS);
	अगर (DWC3_GSTS_CURMOD(reg) != DWC3_GSTS_CURMOD_DEVICE) अणु
		seq_माला_दो(s, "Not available\n");
		spin_unlock_irqrestore(&dwc->lock, flags);
		वापस 0;
	पूर्ण

	reg = dwc3_पढ़ोl(dwc->regs, DWC3_DSTS);
	state = DWC3_DSTS_USBLNKST(reg);
	speed = reg & DWC3_DSTS_CONNECTSPD;

	seq_म_लिखो(s, "%s\n", (speed >= DWC3_DSTS_SUPERSPEED) ?
		   dwc3_gadget_link_string(state) :
		   dwc3_gadget_hs_link_string(state));
	spin_unlock_irqrestore(&dwc->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक dwc3_link_state_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, dwc3_link_state_show, inode->i_निजी);
पूर्ण

अटल sमाप_प्रकार dwc3_link_state_ग_लिखो(काष्ठा file *file,
		स्थिर अक्षर __user *ubuf, माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा seq_file		*s = file->निजी_data;
	काष्ठा dwc3		*dwc = s->निजी;
	अचिन्हित दीर्घ		flags;
	क्रमागत dwc3_link_state	state = 0;
	अक्षर			buf[32];
	u32			reg;
	u8			speed;

	अगर (copy_from_user(&buf, ubuf, min_t(माप_प्रकार, माप(buf) - 1, count)))
		वापस -EFAULT;

	अगर (!म_भेदन(buf, "SS.Disabled", 11))
		state = DWC3_LINK_STATE_SS_DIS;
	अन्यथा अगर (!म_भेदन(buf, "Rx.Detect", 9))
		state = DWC3_LINK_STATE_RX_DET;
	अन्यथा अगर (!म_भेदन(buf, "SS.Inactive", 11))
		state = DWC3_LINK_STATE_SS_INACT;
	अन्यथा अगर (!म_भेदन(buf, "Recovery", 8))
		state = DWC3_LINK_STATE_RECOV;
	अन्यथा अगर (!म_भेदन(buf, "Compliance", 10))
		state = DWC3_LINK_STATE_CMPLY;
	अन्यथा अगर (!म_भेदन(buf, "Loopback", 8))
		state = DWC3_LINK_STATE_LPBK;
	अन्यथा
		वापस -EINVAL;

	spin_lock_irqsave(&dwc->lock, flags);
	reg = dwc3_पढ़ोl(dwc->regs, DWC3_GSTS);
	अगर (DWC3_GSTS_CURMOD(reg) != DWC3_GSTS_CURMOD_DEVICE) अणु
		spin_unlock_irqrestore(&dwc->lock, flags);
		वापस -EINVAL;
	पूर्ण

	reg = dwc3_पढ़ोl(dwc->regs, DWC3_DSTS);
	speed = reg & DWC3_DSTS_CONNECTSPD;

	अगर (speed < DWC3_DSTS_SUPERSPEED &&
	    state != DWC3_LINK_STATE_RECOV) अणु
		spin_unlock_irqrestore(&dwc->lock, flags);
		वापस -EINVAL;
	पूर्ण

	dwc3_gadget_set_link_state(dwc, state);
	spin_unlock_irqrestore(&dwc->lock, flags);

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations dwc3_link_state_fops = अणु
	.खोलो			= dwc3_link_state_खोलो,
	.ग_लिखो			= dwc3_link_state_ग_लिखो,
	.पढ़ो			= seq_पढ़ो,
	.llseek			= seq_lseek,
	.release		= single_release,
पूर्ण;

काष्ठा dwc3_ep_file_map अणु
	स्थिर अक्षर name[25];
	स्थिर काष्ठा file_operations *स्थिर fops;
पूर्ण;

अटल पूर्णांक dwc3_tx_fअगरo_size_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा dwc3_ep		*dep = s->निजी;
	काष्ठा dwc3		*dwc = dep->dwc;
	अचिन्हित दीर्घ		flags;
	u32			mdwidth;
	u32			val;

	spin_lock_irqsave(&dwc->lock, flags);
	val = dwc3_core_fअगरo_space(dep, DWC3_TXFIFO);

	/* Convert to bytes */
	mdwidth = dwc3_mdwidth(dwc);

	val *= mdwidth;
	val >>= 3;
	seq_म_लिखो(s, "%u\n", val);
	spin_unlock_irqrestore(&dwc->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक dwc3_rx_fअगरo_size_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा dwc3_ep		*dep = s->निजी;
	काष्ठा dwc3		*dwc = dep->dwc;
	अचिन्हित दीर्घ		flags;
	u32			mdwidth;
	u32			val;

	spin_lock_irqsave(&dwc->lock, flags);
	val = dwc3_core_fअगरo_space(dep, DWC3_RXFIFO);

	/* Convert to bytes */
	mdwidth = dwc3_mdwidth(dwc);

	val *= mdwidth;
	val >>= 3;
	seq_म_लिखो(s, "%u\n", val);
	spin_unlock_irqrestore(&dwc->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक dwc3_tx_request_queue_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा dwc3_ep		*dep = s->निजी;
	काष्ठा dwc3		*dwc = dep->dwc;
	अचिन्हित दीर्घ		flags;
	u32			val;

	spin_lock_irqsave(&dwc->lock, flags);
	val = dwc3_core_fअगरo_space(dep, DWC3_TXREQQ);
	seq_म_लिखो(s, "%u\n", val);
	spin_unlock_irqrestore(&dwc->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक dwc3_rx_request_queue_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा dwc3_ep		*dep = s->निजी;
	काष्ठा dwc3		*dwc = dep->dwc;
	अचिन्हित दीर्घ		flags;
	u32			val;

	spin_lock_irqsave(&dwc->lock, flags);
	val = dwc3_core_fअगरo_space(dep, DWC3_RXREQQ);
	seq_म_लिखो(s, "%u\n", val);
	spin_unlock_irqrestore(&dwc->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक dwc3_rx_info_queue_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा dwc3_ep		*dep = s->निजी;
	काष्ठा dwc3		*dwc = dep->dwc;
	अचिन्हित दीर्घ		flags;
	u32			val;

	spin_lock_irqsave(&dwc->lock, flags);
	val = dwc3_core_fअगरo_space(dep, DWC3_RXINFOQ);
	seq_म_लिखो(s, "%u\n", val);
	spin_unlock_irqrestore(&dwc->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक dwc3_descriptor_fetch_queue_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा dwc3_ep		*dep = s->निजी;
	काष्ठा dwc3		*dwc = dep->dwc;
	अचिन्हित दीर्घ		flags;
	u32			val;

	spin_lock_irqsave(&dwc->lock, flags);
	val = dwc3_core_fअगरo_space(dep, DWC3_DESCFETCHQ);
	seq_म_लिखो(s, "%u\n", val);
	spin_unlock_irqrestore(&dwc->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक dwc3_event_queue_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा dwc3_ep		*dep = s->निजी;
	काष्ठा dwc3		*dwc = dep->dwc;
	अचिन्हित दीर्घ		flags;
	u32			val;

	spin_lock_irqsave(&dwc->lock, flags);
	val = dwc3_core_fअगरo_space(dep, DWC3_EVENTQ);
	seq_म_लिखो(s, "%u\n", val);
	spin_unlock_irqrestore(&dwc->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक dwc3_transfer_type_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा dwc3_ep		*dep = s->निजी;
	काष्ठा dwc3		*dwc = dep->dwc;
	अचिन्हित दीर्घ		flags;

	spin_lock_irqsave(&dwc->lock, flags);
	अगर (!(dep->flags & DWC3_EP_ENABLED) || !dep->endpoपूर्णांक.desc) अणु
		seq_माला_दो(s, "--\n");
		जाओ out;
	पूर्ण

	चयन (usb_endpoपूर्णांक_type(dep->endpoपूर्णांक.desc)) अणु
	हाल USB_ENDPOINT_XFER_CONTROL:
		seq_माला_दो(s, "control\n");
		अवरोध;
	हाल USB_ENDPOINT_XFER_ISOC:
		seq_माला_दो(s, "isochronous\n");
		अवरोध;
	हाल USB_ENDPOINT_XFER_BULK:
		seq_माला_दो(s, "bulk\n");
		अवरोध;
	हाल USB_ENDPOINT_XFER_INT:
		seq_माला_दो(s, "interrupt\n");
		अवरोध;
	शेष:
		seq_माला_दो(s, "--\n");
	पूर्ण

out:
	spin_unlock_irqrestore(&dwc->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक dwc3_trb_ring_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा dwc3_ep		*dep = s->निजी;
	काष्ठा dwc3		*dwc = dep->dwc;
	अचिन्हित दीर्घ		flags;
	पूर्णांक			i;

	spin_lock_irqsave(&dwc->lock, flags);
	अगर (dep->number <= 1) अणु
		seq_माला_दो(s, "--\n");
		जाओ out;
	पूर्ण

	seq_माला_दो(s, "buffer_addr,size,type,ioc,isp_imi,csp,chn,lst,hwo\n");

	क्रम (i = 0; i < DWC3_TRB_NUM; i++) अणु
		काष्ठा dwc3_trb *trb = &dep->trb_pool[i];
		अचिन्हित पूर्णांक type = DWC3_TRBCTL_TYPE(trb->ctrl);

		seq_म_लिखो(s, "%08x%08x,%d,%s,%d,%d,%d,%d,%d,%d       %c%c\n",
				trb->bph, trb->bpl, trb->size,
				dwc3_trb_type_string(type),
				!!(trb->ctrl & DWC3_TRB_CTRL_IOC),
				!!(trb->ctrl & DWC3_TRB_CTRL_ISP_IMI),
				!!(trb->ctrl & DWC3_TRB_CTRL_CSP),
				!!(trb->ctrl & DWC3_TRB_CTRL_CHN),
				!!(trb->ctrl & DWC3_TRB_CTRL_LST),
				!!(trb->ctrl & DWC3_TRB_CTRL_HWO),
				dep->trb_enqueue == i ? 'E' : ' ',
				dep->trb_dequeue == i ? 'D' : ' ');
	पूर्ण

out:
	spin_unlock_irqrestore(&dwc->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक dwc3_ep_info_रेजिस्टर_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा dwc3_ep		*dep = s->निजी;
	काष्ठा dwc3		*dwc = dep->dwc;
	अचिन्हित दीर्घ		flags;
	u64			ep_info;
	u32			lower_32_bits;
	u32			upper_32_bits;
	u32			reg;

	spin_lock_irqsave(&dwc->lock, flags);
	reg = DWC3_GDBGLSPMUX_EPSELECT(dep->number);
	dwc3_ग_लिखोl(dwc->regs, DWC3_GDBGLSPMUX, reg);

	lower_32_bits = dwc3_पढ़ोl(dwc->regs, DWC3_GDBGEPINFO0);
	upper_32_bits = dwc3_पढ़ोl(dwc->regs, DWC3_GDBGEPINFO1);

	ep_info = ((u64)upper_32_bits << 32) | lower_32_bits;
	seq_म_लिखो(s, "0x%016llx\n", ep_info);
	spin_unlock_irqrestore(&dwc->lock, flags);

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(dwc3_tx_fअगरo_size);
DEFINE_SHOW_ATTRIBUTE(dwc3_rx_fअगरo_size);
DEFINE_SHOW_ATTRIBUTE(dwc3_tx_request_queue);
DEFINE_SHOW_ATTRIBUTE(dwc3_rx_request_queue);
DEFINE_SHOW_ATTRIBUTE(dwc3_rx_info_queue);
DEFINE_SHOW_ATTRIBUTE(dwc3_descriptor_fetch_queue);
DEFINE_SHOW_ATTRIBUTE(dwc3_event_queue);
DEFINE_SHOW_ATTRIBUTE(dwc3_transfer_type);
DEFINE_SHOW_ATTRIBUTE(dwc3_trb_ring);
DEFINE_SHOW_ATTRIBUTE(dwc3_ep_info_रेजिस्टर);

अटल स्थिर काष्ठा dwc3_ep_file_map dwc3_ep_file_map[] = अणु
	अणु "tx_fifo_size", &dwc3_tx_fअगरo_size_fops, पूर्ण,
	अणु "rx_fifo_size", &dwc3_rx_fअगरo_size_fops, पूर्ण,
	अणु "tx_request_queue", &dwc3_tx_request_queue_fops, पूर्ण,
	अणु "rx_request_queue", &dwc3_rx_request_queue_fops, पूर्ण,
	अणु "rx_info_queue", &dwc3_rx_info_queue_fops, पूर्ण,
	अणु "descriptor_fetch_queue", &dwc3_descriptor_fetch_queue_fops, पूर्ण,
	अणु "event_queue", &dwc3_event_queue_fops, पूर्ण,
	अणु "transfer_type", &dwc3_transfer_type_fops, पूर्ण,
	अणु "trb_ring", &dwc3_trb_ring_fops, पूर्ण,
	अणु "GDBGEPINFO", &dwc3_ep_info_रेजिस्टर_fops, पूर्ण,
पूर्ण;

अटल व्योम dwc3_debugfs_create_endpoपूर्णांक_files(काष्ठा dwc3_ep *dep,
		काष्ठा dentry *parent)
अणु
	पूर्णांक			i;

	क्रम (i = 0; i < ARRAY_SIZE(dwc3_ep_file_map); i++) अणु
		स्थिर काष्ठा file_operations *fops = dwc3_ep_file_map[i].fops;
		स्थिर अक्षर *name = dwc3_ep_file_map[i].name;

		debugfs_create_file(name, 0444, parent, dep, fops);
	पूर्ण
पूर्ण

व्योम dwc3_debugfs_create_endpoपूर्णांक_dir(काष्ठा dwc3_ep *dep)
अणु
	काष्ठा dentry		*dir;

	dir = debugfs_create_dir(dep->name, dep->dwc->root);
	dwc3_debugfs_create_endpoपूर्णांक_files(dep, dir);
पूर्ण

व्योम dwc3_debugfs_init(काष्ठा dwc3 *dwc)
अणु
	काष्ठा dentry		*root;

	dwc->regset = kzalloc(माप(*dwc->regset), GFP_KERNEL);
	अगर (!dwc->regset)
		वापस;

	dwc->dbg_lsp_select = DWC3_LSP_MUX_UNSELECTED;

	dwc->regset->regs = dwc3_regs;
	dwc->regset->nregs = ARRAY_SIZE(dwc3_regs);
	dwc->regset->base = dwc->regs - DWC3_GLOBALS_REGS_START;

	root = debugfs_create_dir(dev_name(dwc->dev), usb_debug_root);
	dwc->root = root;

	debugfs_create_regset32("regdump", 0444, root, dwc->regset);
	debugfs_create_file("lsp_dump", 0644, root, dwc, &dwc3_lsp_fops);

	अगर (IS_ENABLED(CONFIG_USB_DWC3_DUAL_ROLE))
		debugfs_create_file("mode", 0644, root, dwc,
				    &dwc3_mode_fops);

	अगर (IS_ENABLED(CONFIG_USB_DWC3_DUAL_ROLE) ||
			IS_ENABLED(CONFIG_USB_DWC3_GADGET)) अणु
		debugfs_create_file("testmode", 0644, root, dwc,
				&dwc3_tesपंचांगode_fops);
		debugfs_create_file("link_state", 0644, root, dwc,
				    &dwc3_link_state_fops);
	पूर्ण
पूर्ण

व्योम dwc3_debugfs_निकास(काष्ठा dwc3 *dwc)
अणु
	debugfs_हटाओ_recursive(dwc->root);
	kमुक्त(dwc->regset);
पूर्ण
