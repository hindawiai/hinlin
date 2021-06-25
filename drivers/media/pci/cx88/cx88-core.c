<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * device driver क्रम Conexant 2388x based TV cards
 * driver core
 *
 * (c) 2003 Gerd Knorr <kraxel@bytesex.org> [SuSE Lअसल]
 *
 * (c) 2005-2006 Mauro Carvalho Chehab <mchehab@kernel.org>
 *     - Multituner support
 *     - video_ioctl2 conversion
 *     - PAL/M fixes
 */

#समावेश "cx88.h"

#समावेश <linux/init.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/kmod.h>
#समावेश <linux/sound.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/mutex.h>

#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-ioctl.h>

MODULE_DESCRIPTION("v4l2 driver module for cx2388x based TV cards");
MODULE_AUTHOR("Gerd Knorr <kraxel@bytesex.org> [SuSE Labs]");
MODULE_LICENSE("GPL v2");

/* ------------------------------------------------------------------ */

अचिन्हित पूर्णांक cx88_core_debug;
module_param_named(core_debug, cx88_core_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(core_debug, "enable debug messages [core]");

अटल अचिन्हित पूर्णांक nicam;
module_param(nicam, पूर्णांक, 0644);
MODULE_PARM_DESC(nicam, "tv audio is nicam");

अटल अचिन्हित पूर्णांक nocomb;
module_param(nocomb, पूर्णांक, 0644);
MODULE_PARM_DESC(nocomb, "disable comb filter");

#घोषणा dprपूर्णांकk0(fmt, arg...)				\
	prपूर्णांकk(KERN_DEBUG pr_fmt("%s: core:" fmt),	\
		__func__, ##arg)			\

#घोषणा dprपूर्णांकk(level, fmt, arg...)	करो अणु			\
	अगर (cx88_core_debug >= level)				\
		prपूर्णांकk(KERN_DEBUG pr_fmt("%s: core:" fmt),	\
		       __func__, ##arg);			\
पूर्ण जबतक (0)

अटल अचिन्हित पूर्णांक cx88_devcount;
अटल LIST_HEAD(cx88_devlist);
अटल DEFINE_MUTEX(devlist);

#घोषणा NO_SYNC_LINE (-1U)

/*
 * @lpi: lines per IRQ, or 0 to not generate irqs. Note: IRQ to be
 * generated _after_ lpi lines are transferred.
 */
अटल __le32 *cx88_risc_field(__le32 *rp, काष्ठा scatterlist *sglist,
			       अचिन्हित पूर्णांक offset, u32 sync_line,
			       अचिन्हित पूर्णांक bpl, अचिन्हित पूर्णांक padding,
			       अचिन्हित पूर्णांक lines, अचिन्हित पूर्णांक lpi, bool jump)
अणु
	काष्ठा scatterlist *sg;
	अचिन्हित पूर्णांक line, toकरो, sol;

	अगर (jump) अणु
		(*rp++) = cpu_to_le32(RISC_JUMP);
		(*rp++) = 0;
	पूर्ण

	/* sync inकाष्ठाion */
	अगर (sync_line != NO_SYNC_LINE)
		*(rp++) = cpu_to_le32(RISC_RESYNC | sync_line);

	/* scan lines */
	sg = sglist;
	क्रम (line = 0; line < lines; line++) अणु
		जबतक (offset && offset >= sg_dma_len(sg)) अणु
			offset -= sg_dma_len(sg);
			sg = sg_next(sg);
		पूर्ण
		अगर (lpi && line > 0 && !(line % lpi))
			sol = RISC_SOL | RISC_IRQ1 | RISC_CNT_INC;
		अन्यथा
			sol = RISC_SOL;
		अगर (bpl <= sg_dma_len(sg) - offset) अणु
			/* fits पूर्णांकo current chunk */
			*(rp++) = cpu_to_le32(RISC_WRITE | sol |
					      RISC_EOL | bpl);
			*(rp++) = cpu_to_le32(sg_dma_address(sg) + offset);
			offset += bpl;
		पूर्ण अन्यथा अणु
			/* scanline needs to be split */
			toकरो = bpl;
			*(rp++) = cpu_to_le32(RISC_WRITE | sol |
					      (sg_dma_len(sg) - offset));
			*(rp++) = cpu_to_le32(sg_dma_address(sg) + offset);
			toकरो -= (sg_dma_len(sg) - offset);
			offset = 0;
			sg = sg_next(sg);
			जबतक (toकरो > sg_dma_len(sg)) अणु
				*(rp++) = cpu_to_le32(RISC_WRITE |
						      sg_dma_len(sg));
				*(rp++) = cpu_to_le32(sg_dma_address(sg));
				toकरो -= sg_dma_len(sg);
				sg = sg_next(sg);
			पूर्ण
			*(rp++) = cpu_to_le32(RISC_WRITE | RISC_EOL | toकरो);
			*(rp++) = cpu_to_le32(sg_dma_address(sg));
			offset += toकरो;
		पूर्ण
		offset += padding;
	पूर्ण

	वापस rp;
पूर्ण

पूर्णांक cx88_risc_buffer(काष्ठा pci_dev *pci, काष्ठा cx88_riscmem *risc,
		     काष्ठा scatterlist *sglist,
		     अचिन्हित पूर्णांक top_offset, अचिन्हित पूर्णांक bottom_offset,
		     अचिन्हित पूर्णांक bpl, अचिन्हित पूर्णांक padding, अचिन्हित पूर्णांक lines)
अणु
	u32 inकाष्ठाions, fields;
	__le32 *rp;

	fields = 0;
	अगर (top_offset != UNSET)
		fields++;
	अगर (bottom_offset != UNSET)
		fields++;

	/*
	 * estimate risc mem: worst हाल is one ग_लिखो per page border +
	 * one ग_लिखो per scan line + syncs + jump (all 2 dwords).  Padding
	 * can cause next bpl to start बंद to a page border.  First DMA
	 * region may be smaller than PAGE_SIZE
	 */
	inकाष्ठाions  = fields * (1 + ((bpl + padding) * lines) /
				  PAGE_SIZE + lines);
	inकाष्ठाions += 4;
	risc->size = inकाष्ठाions * 8;
	risc->dma = 0;
	risc->cpu = pci_zalloc_consistent(pci, risc->size, &risc->dma);
	अगर (!risc->cpu)
		वापस -ENOMEM;

	/* ग_लिखो risc inकाष्ठाions */
	rp = risc->cpu;
	अगर (top_offset != UNSET)
		rp = cx88_risc_field(rp, sglist, top_offset, 0,
				     bpl, padding, lines, 0, true);
	अगर (bottom_offset != UNSET)
		rp = cx88_risc_field(rp, sglist, bottom_offset, 0x200,
				     bpl, padding, lines, 0,
				     top_offset == UNSET);

	/* save poपूर्णांकer to jmp inकाष्ठाion address */
	risc->jmp = rp;
	WARN_ON((risc->jmp - risc->cpu + 2) * माप(*risc->cpu) > risc->size);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(cx88_risc_buffer);

पूर्णांक cx88_risc_databuffer(काष्ठा pci_dev *pci, काष्ठा cx88_riscmem *risc,
			 काष्ठा scatterlist *sglist, अचिन्हित पूर्णांक bpl,
			 अचिन्हित पूर्णांक lines, अचिन्हित पूर्णांक lpi)
अणु
	u32 inकाष्ठाions;
	__le32 *rp;

	/*
	 * estimate risc mem: worst हाल is one ग_लिखो per page border +
	 * one ग_लिखो per scan line + syncs + jump (all 2 dwords).  Here
	 * there is no padding and no sync.  First DMA region may be smaller
	 * than PAGE_SIZE
	 */
	inकाष्ठाions  = 1 + (bpl * lines) / PAGE_SIZE + lines;
	inकाष्ठाions += 3;
	risc->size = inकाष्ठाions * 8;
	risc->dma = 0;
	risc->cpu = pci_zalloc_consistent(pci, risc->size, &risc->dma);
	अगर (!risc->cpu)
		वापस -ENOMEM;

	/* ग_लिखो risc inकाष्ठाions */
	rp = risc->cpu;
	rp = cx88_risc_field(rp, sglist, 0, NO_SYNC_LINE, bpl, 0,
			     lines, lpi, !lpi);

	/* save poपूर्णांकer to jmp inकाष्ठाion address */
	risc->jmp = rp;
	WARN_ON((risc->jmp - risc->cpu + 2) * माप(*risc->cpu) > risc->size);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(cx88_risc_databuffer);

/*
 * our SRAM memory layout
 */

/*
 * we are going to put all thr risc programs पूर्णांकo host memory, so we
 * can use the whole SDRAM क्रम the DMA fअगरos.  To simplअगरy things, we
 * use a अटल memory layout.  That surely will waste memory in हाल
 * we करोn't use all DMA channels at the same समय (which will be the
 * हाल most of the समय).  But that still gives us enough FIFO space
 * to be able to deal with insane दीर्घ pci latencies ...
 *
 * FIFO space allocations:
 *    channel  21    (y video)  - 10.0k
 *    channel  22    (u video)  -  2.0k
 *    channel  23    (v video)  -  2.0k
 *    channel  24    (vbi)      -  4.0k
 *    channels 25+26 (audio)    -  4.0k
 *    channel  28    (mpeg)     -  4.0k
 *    channel  27    (audio rds)-  3.0k
 *    TOTAL                     = 29.0k
 *
 * Every channel has 160 bytes control data (64 bytes inकाष्ठाion
 * queue and 6 CDT entries), which is बंद to 2k total.
 *
 * Address layout:
 *    0x0000 - 0x03ff    CMDs / reserved
 *    0x0400 - 0x0bff    inकाष्ठाion queues + CDs
 *    0x0c00 -           FIFOs
 */

स्थिर काष्ठा sram_channel cx88_sram_channels[] = अणु
	[SRAM_CH21] = अणु
		.name       = "video y / packed",
		.cmds_start = 0x180040,
		.ctrl_start = 0x180400,
		.cdt        = 0x180400 + 64,
		.fअगरo_start = 0x180c00,
		.fअगरo_size  = 0x002800,
		.ptr1_reg   = MO_DMA21_PTR1,
		.ptr2_reg   = MO_DMA21_PTR2,
		.cnt1_reg   = MO_DMA21_CNT1,
		.cnt2_reg   = MO_DMA21_CNT2,
	पूर्ण,
	[SRAM_CH22] = अणु
		.name       = "video u",
		.cmds_start = 0x180080,
		.ctrl_start = 0x1804a0,
		.cdt        = 0x1804a0 + 64,
		.fअगरo_start = 0x183400,
		.fअगरo_size  = 0x000800,
		.ptr1_reg   = MO_DMA22_PTR1,
		.ptr2_reg   = MO_DMA22_PTR2,
		.cnt1_reg   = MO_DMA22_CNT1,
		.cnt2_reg   = MO_DMA22_CNT2,
	पूर्ण,
	[SRAM_CH23] = अणु
		.name       = "video v",
		.cmds_start = 0x1800c0,
		.ctrl_start = 0x180540,
		.cdt        = 0x180540 + 64,
		.fअगरo_start = 0x183c00,
		.fअगरo_size  = 0x000800,
		.ptr1_reg   = MO_DMA23_PTR1,
		.ptr2_reg   = MO_DMA23_PTR2,
		.cnt1_reg   = MO_DMA23_CNT1,
		.cnt2_reg   = MO_DMA23_CNT2,
	पूर्ण,
	[SRAM_CH24] = अणु
		.name       = "vbi",
		.cmds_start = 0x180100,
		.ctrl_start = 0x1805e0,
		.cdt        = 0x1805e0 + 64,
		.fअगरo_start = 0x184400,
		.fअगरo_size  = 0x001000,
		.ptr1_reg   = MO_DMA24_PTR1,
		.ptr2_reg   = MO_DMA24_PTR2,
		.cnt1_reg   = MO_DMA24_CNT1,
		.cnt2_reg   = MO_DMA24_CNT2,
	पूर्ण,
	[SRAM_CH25] = अणु
		.name       = "audio from",
		.cmds_start = 0x180140,
		.ctrl_start = 0x180680,
		.cdt        = 0x180680 + 64,
		.fअगरo_start = 0x185400,
		.fअगरo_size  = 0x001000,
		.ptr1_reg   = MO_DMA25_PTR1,
		.ptr2_reg   = MO_DMA25_PTR2,
		.cnt1_reg   = MO_DMA25_CNT1,
		.cnt2_reg   = MO_DMA25_CNT2,
	पूर्ण,
	[SRAM_CH26] = अणु
		.name       = "audio to",
		.cmds_start = 0x180180,
		.ctrl_start = 0x180720,
		.cdt        = 0x180680 + 64,  /* same as audio IN */
		.fअगरo_start = 0x185400,       /* same as audio IN */
		.fअगरo_size  = 0x001000,       /* same as audio IN */
		.ptr1_reg   = MO_DMA26_PTR1,
		.ptr2_reg   = MO_DMA26_PTR2,
		.cnt1_reg   = MO_DMA26_CNT1,
		.cnt2_reg   = MO_DMA26_CNT2,
	पूर्ण,
	[SRAM_CH28] = अणु
		.name       = "mpeg",
		.cmds_start = 0x180200,
		.ctrl_start = 0x1807C0,
		.cdt        = 0x1807C0 + 64,
		.fअगरo_start = 0x186400,
		.fअगरo_size  = 0x001000,
		.ptr1_reg   = MO_DMA28_PTR1,
		.ptr2_reg   = MO_DMA28_PTR2,
		.cnt1_reg   = MO_DMA28_CNT1,
		.cnt2_reg   = MO_DMA28_CNT2,
	पूर्ण,
	[SRAM_CH27] = अणु
		.name       = "audio rds",
		.cmds_start = 0x1801C0,
		.ctrl_start = 0x180860,
		.cdt        = 0x180860 + 64,
		.fअगरo_start = 0x187400,
		.fअगरo_size  = 0x000C00,
		.ptr1_reg   = MO_DMA27_PTR1,
		.ptr2_reg   = MO_DMA27_PTR2,
		.cnt1_reg   = MO_DMA27_CNT1,
		.cnt2_reg   = MO_DMA27_CNT2,
	पूर्ण,
पूर्ण;
EXPORT_SYMBOL(cx88_sram_channels);

पूर्णांक cx88_sram_channel_setup(काष्ठा cx88_core *core,
			    स्थिर काष्ठा sram_channel *ch,
			    अचिन्हित पूर्णांक bpl, u32 risc)
अणु
	अचिन्हित पूर्णांक i, lines;
	u32 cdt;

	bpl   = (bpl + 7) & ~7; /* alignment */
	cdt   = ch->cdt;
	lines = ch->fअगरo_size / bpl;
	अगर (lines > 6)
		lines = 6;
	WARN_ON(lines < 2);

	/* ग_लिखो CDT */
	क्रम (i = 0; i < lines; i++)
		cx_ग_लिखो(cdt + 16 * i, ch->fअगरo_start + bpl * i);

	/* ग_लिखो CMDS */
	cx_ग_लिखो(ch->cmds_start +  0, risc);
	cx_ग_लिखो(ch->cmds_start +  4, cdt);
	cx_ग_लिखो(ch->cmds_start +  8, (lines * 16) >> 3);
	cx_ग_लिखो(ch->cmds_start + 12, ch->ctrl_start);
	cx_ग_लिखो(ch->cmds_start + 16, 64 >> 2);
	क्रम (i = 20; i < 64; i += 4)
		cx_ग_लिखो(ch->cmds_start + i, 0);

	/* fill रेजिस्टरs */
	cx_ग_लिखो(ch->ptr1_reg, ch->fअगरo_start);
	cx_ग_लिखो(ch->ptr2_reg, cdt);
	cx_ग_लिखो(ch->cnt1_reg, (bpl >> 3) - 1);
	cx_ग_लिखो(ch->cnt2_reg, (lines * 16) >> 3);

	dprपूर्णांकk(2, "sram setup %s: bpl=%d lines=%d\n", ch->name, bpl, lines);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(cx88_sram_channel_setup);

/* ------------------------------------------------------------------ */
/* debug helper code                                                  */

अटल पूर्णांक cx88_risc_decode(u32 risc)
अणु
	अटल स्थिर अक्षर * स्थिर instr[16] = अणु
		[RISC_SYNC    >> 28] = "sync",
		[RISC_WRITE   >> 28] = "write",
		[RISC_WRITEC  >> 28] = "writec",
		[RISC_READ    >> 28] = "read",
		[RISC_READC   >> 28] = "readc",
		[RISC_JUMP    >> 28] = "jump",
		[RISC_SKIP    >> 28] = "skip",
		[RISC_WRITERM >> 28] = "writerm",
		[RISC_WRITECM >> 28] = "writecm",
		[RISC_WRITECR >> 28] = "writecr",
	पूर्ण;
	अटल पूर्णांक स्थिर incr[16] = अणु
		[RISC_WRITE   >> 28] = 2,
		[RISC_JUMP    >> 28] = 2,
		[RISC_WRITERM >> 28] = 3,
		[RISC_WRITECM >> 28] = 3,
		[RISC_WRITECR >> 28] = 4,
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर bits[] = अणु
		"12",   "13",   "14",   "resync",
		"cnt0", "cnt1", "18",   "19",
		"20",   "21",   "22",   "23",
		"irq1", "irq2", "eol",  "sol",
	पूर्ण;
	पूर्णांक i;

	dprपूर्णांकk0("0x%08x [ %s", risc,
		 instr[risc >> 28] ? instr[risc >> 28] : "INVALID");
	क्रम (i = ARRAY_SIZE(bits) - 1; i >= 0; i--)
		अगर (risc & (1 << (i + 12)))
			pr_cont(" %s", bits[i]);
	pr_cont(" count=%d ]\n", risc & 0xfff);
	वापस incr[risc >> 28] ? incr[risc >> 28] : 1;
पूर्ण

व्योम cx88_sram_channel_dump(काष्ठा cx88_core *core,
			    स्थिर काष्ठा sram_channel *ch)
अणु
	अटल स्थिर अक्षर * स्थिर name[] = अणु
		"initial risc",
		"cdt base",
		"cdt size",
		"iq base",
		"iq size",
		"risc pc",
		"iq wr ptr",
		"iq rd ptr",
		"cdt current",
		"pci target",
		"line / byte",
	पूर्ण;
	u32 risc;
	अचिन्हित पूर्णांक i, j, n;

	dprपूर्णांकk0("%s - dma channel status dump\n", ch->name);
	क्रम (i = 0; i < ARRAY_SIZE(name); i++)
		dprपूर्णांकk0("   cmds: %-12s: 0x%08x\n",
			 name[i], cx_पढ़ो(ch->cmds_start + 4 * i));
	क्रम (n = 1, i = 0; i < 4; i++) अणु
		risc = cx_पढ़ो(ch->cmds_start + 4 * (i + 11));
		pr_cont("  risc%d: ", i);
		अगर (--n)
			pr_cont("0x%08x [ arg #%d ]\n", risc, n);
		अन्यथा
			n = cx88_risc_decode(risc);
	पूर्ण
	क्रम (i = 0; i < 16; i += n) अणु
		risc = cx_पढ़ो(ch->ctrl_start + 4 * i);
		dprपूर्णांकk0("  iq %x: ", i);
		n = cx88_risc_decode(risc);
		क्रम (j = 1; j < n; j++) अणु
			risc = cx_पढ़ो(ch->ctrl_start + 4 * (i + j));
			pr_cont("  iq %x: 0x%08x [ arg #%d ]\n",
				i + j, risc, j);
		पूर्ण
	पूर्ण

	dprपूर्णांकk0("fifo: 0x%08x -> 0x%x\n",
		 ch->fअगरo_start, ch->fअगरo_start + ch->fअगरo_size);
	dprपूर्णांकk0("ctrl: 0x%08x -> 0x%x\n",
		 ch->ctrl_start, ch->ctrl_start + 6 * 16);
	dprपूर्णांकk0("  ptr1_reg: 0x%08x\n", cx_पढ़ो(ch->ptr1_reg));
	dprपूर्णांकk0("  ptr2_reg: 0x%08x\n", cx_पढ़ो(ch->ptr2_reg));
	dprपूर्णांकk0("  cnt1_reg: 0x%08x\n", cx_पढ़ो(ch->cnt1_reg));
	dprपूर्णांकk0("  cnt2_reg: 0x%08x\n", cx_पढ़ो(ch->cnt2_reg));
पूर्ण
EXPORT_SYMBOL(cx88_sram_channel_dump);

अटल स्थिर अक्षर *cx88_pci_irqs[32] = अणु
	"vid", "aud", "ts", "vip", "hst", "5", "6", "tm1",
	"src_dma", "dst_dma", "risc_rd_err", "risc_wr_err",
	"brdg_err", "src_dma_err", "dst_dma_err", "ipb_dma_err",
	"i2c", "i2c_rack", "ir_smp", "gpio0", "gpio1"
पूर्ण;

व्योम cx88_prपूर्णांक_irqbits(स्थिर अक्षर *tag, स्थिर अक्षर *strings[],
			पूर्णांक len, u32 bits, u32 mask)
अणु
	अचिन्हित पूर्णांक i;

	dprपूर्णांकk0("%s [0x%x]", tag, bits);
	क्रम (i = 0; i < len; i++) अणु
		अगर (!(bits & (1 << i)))
			जारी;
		अगर (strings[i])
			pr_cont(" %s", strings[i]);
		अन्यथा
			pr_cont(" %d", i);
		अगर (!(mask & (1 << i)))
			जारी;
		pr_cont("*");
	पूर्ण
	pr_cont("\n");
पूर्ण
EXPORT_SYMBOL(cx88_prपूर्णांक_irqbits);

/* ------------------------------------------------------------------ */

पूर्णांक cx88_core_irq(काष्ठा cx88_core *core, u32 status)
अणु
	पूर्णांक handled = 0;

	अगर (status & PCI_INT_IR_SMPINT) अणु
		cx88_ir_irq(core);
		handled++;
	पूर्ण
	अगर (!handled)
		cx88_prपूर्णांक_irqbits("irq pci",
				   cx88_pci_irqs, ARRAY_SIZE(cx88_pci_irqs),
				   status, core->pci_irqmask);
	वापस handled;
पूर्ण
EXPORT_SYMBOL(cx88_core_irq);

व्योम cx88_wakeup(काष्ठा cx88_core *core,
		 काष्ठा cx88_dmaqueue *q, u32 count)
अणु
	काष्ठा cx88_buffer *buf;

	buf = list_entry(q->active.next,
			 काष्ठा cx88_buffer, list);
	buf->vb.vb2_buf.बारtamp = kसमय_get_ns();
	buf->vb.field = core->field;
	buf->vb.sequence = q->count++;
	list_del(&buf->list);
	vb2_buffer_करोne(&buf->vb.vb2_buf, VB2_BUF_STATE_DONE);
पूर्ण
EXPORT_SYMBOL(cx88_wakeup);

व्योम cx88_shutकरोwn(काष्ठा cx88_core *core)
अणु
	/* disable RISC controller + IRQs */
	cx_ग_लिखो(MO_DEV_CNTRL2, 0);

	/* stop dma transfers */
	cx_ग_लिखो(MO_VID_DMACNTRL, 0x0);
	cx_ग_लिखो(MO_AUD_DMACNTRL, 0x0);
	cx_ग_लिखो(MO_TS_DMACNTRL, 0x0);
	cx_ग_लिखो(MO_VIP_DMACNTRL, 0x0);
	cx_ग_लिखो(MO_GPHST_DMACNTRL, 0x0);

	/* stop पूर्णांकerrupts */
	cx_ग_लिखो(MO_PCI_INTMSK, 0x0);
	cx_ग_लिखो(MO_VID_INTMSK, 0x0);
	cx_ग_लिखो(MO_AUD_INTMSK, 0x0);
	cx_ग_लिखो(MO_TS_INTMSK, 0x0);
	cx_ग_लिखो(MO_VIP_INTMSK, 0x0);
	cx_ग_लिखो(MO_GPHST_INTMSK, 0x0);

	/* stop capturing */
	cx_ग_लिखो(VID_CAPTURE_CONTROL, 0);
पूर्ण
EXPORT_SYMBOL(cx88_shutकरोwn);

पूर्णांक cx88_reset(काष्ठा cx88_core *core)
अणु
	dprपूर्णांकk(1, "");
	cx88_shutकरोwn(core);

	/* clear irq status */
	cx_ग_लिखो(MO_VID_INTSTAT, 0xFFFFFFFF); // Clear PIV पूर्णांक
	cx_ग_लिखो(MO_PCI_INTSTAT, 0xFFFFFFFF); // Clear PCI पूर्णांक
	cx_ग_लिखो(MO_INT1_STAT,   0xFFFFFFFF); // Clear RISC पूर्णांक

	/* रुको a bit */
	msleep(100);

	/* init sram */
	cx88_sram_channel_setup(core, &cx88_sram_channels[SRAM_CH21],
				720 * 4, 0);
	cx88_sram_channel_setup(core, &cx88_sram_channels[SRAM_CH22], 128, 0);
	cx88_sram_channel_setup(core, &cx88_sram_channels[SRAM_CH23], 128, 0);
	cx88_sram_channel_setup(core, &cx88_sram_channels[SRAM_CH24], 128, 0);
	cx88_sram_channel_setup(core, &cx88_sram_channels[SRAM_CH25], 128, 0);
	cx88_sram_channel_setup(core, &cx88_sram_channels[SRAM_CH26], 128, 0);
	cx88_sram_channel_setup(core, &cx88_sram_channels[SRAM_CH28],
				188 * 4, 0);
	cx88_sram_channel_setup(core, &cx88_sram_channels[SRAM_CH27], 128, 0);

	/* misc init ... */
	cx_ग_लिखो(MO_INPUT_FORMAT, ((1 << 13) |   // agc enable
				   (1 << 12) |   // agc gain
				   (1 << 11) |   // adaptibe agc
				   (0 << 10) |   // chroma agc
				   (0 <<  9) |   // cसमाप्तen
				   (7)));

	/* setup image क्रमmat */
	cx_anकरोr(MO_COLOR_CTRL, 0x4000, 0x4000);

	/* setup FIFO Thresholds */
	cx_ग_लिखो(MO_PDMA_STHRSH,   0x0807);
	cx_ग_लिखो(MO_PDMA_DTHRSH,   0x0807);

	/* fixes flashing of image */
	cx_ग_लिखो(MO_AGC_SYNC_TIP1, 0x0380000F);
	cx_ग_लिखो(MO_AGC_BACK_VBI,  0x00E00555);

	cx_ग_लिखो(MO_VID_INTSTAT,   0xFFFFFFFF); // Clear PIV पूर्णांक
	cx_ग_लिखो(MO_PCI_INTSTAT,   0xFFFFFFFF); // Clear PCI पूर्णांक
	cx_ग_लिखो(MO_INT1_STAT,     0xFFFFFFFF); // Clear RISC पूर्णांक

	/* Reset on-board parts */
	cx_ग_लिखो(MO_SRST_IO, 0);
	usleep_range(10000, 20000);
	cx_ग_लिखो(MO_SRST_IO, 1);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(cx88_reset);

/* ------------------------------------------------------------------ */

अटल अंतरभूत अचिन्हित पूर्णांक norm_swidth(v4l2_std_id norm)
अणु
	वापस (norm & (V4L2_STD_MN & ~V4L2_STD_PAL_Nc)) ? 754 : 922;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक norm_hdelay(v4l2_std_id norm)
अणु
	वापस (norm & (V4L2_STD_MN & ~V4L2_STD_PAL_Nc)) ? 135 : 186;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक norm_vdelay(v4l2_std_id norm)
अणु
	वापस (norm & V4L2_STD_625_50) ? 0x24 : 0x18;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक norm_fsc8(v4l2_std_id norm)
अणु
	अगर (norm & V4L2_STD_PAL_M)
		वापस 28604892;      // 3.575611 MHz

	अगर (norm & (V4L2_STD_PAL_Nc))
		वापस 28656448;      // 3.582056 MHz

	अगर (norm & V4L2_STD_NTSC) // All NTSC/M and variants
		वापस 28636360;      // 3.57954545 MHz +/- 10 Hz

	/*
	 * SECAM have also dअगरferent sub carrier क्रम chroma,
	 * but step_db and step_dr, at cx88_set_tvnorm alपढ़ोy handles that.
	 *
	 * The same FSC applies to PAL/BGDKIH, PAL/60, NTSC/4.43 and PAL/N
	 */

	वापस 35468950;      // 4.43361875 MHz +/- 5 Hz
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक norm_htotal(v4l2_std_id norm)
अणु
	अचिन्हित पूर्णांक fsc4 = norm_fsc8(norm) / 2;

	/* वापसs 4*FSC / vtotal / frames per seconds */
	वापस (norm & V4L2_STD_625_50) ?
				((fsc4 + 312) / 625 + 12) / 25 :
				((fsc4 + 262) / 525 * 1001 + 15000) / 30000;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक norm_vbipack(v4l2_std_id norm)
अणु
	वापस (norm & V4L2_STD_625_50) ? 511 : 400;
पूर्ण

पूर्णांक cx88_set_scale(काष्ठा cx88_core *core, अचिन्हित पूर्णांक width,
		   अचिन्हित पूर्णांक height, क्रमागत v4l2_field field)
अणु
	अचिन्हित पूर्णांक swidth  = norm_swidth(core->tvnorm);
	अचिन्हित पूर्णांक sheight = norm_maxh(core->tvnorm);
	u32 value;

	dprपूर्णांकk(1, "set_scale: %dx%d [%s%s,%s]\n", width, height,
		V4L2_FIELD_HAS_TOP(field)    ? "T" : "",
		V4L2_FIELD_HAS_BOTTOM(field) ? "B" : "",
		v4l2_norm_to_name(core->tvnorm));
	अगर (!V4L2_FIELD_HAS_BOTH(field))
		height *= 2;

	// recalc H delay and scale रेजिस्टरs
	value = (width * norm_hdelay(core->tvnorm)) / swidth;
	value &= 0x3fe;
	cx_ग_लिखो(MO_HDELAY_EVEN,  value);
	cx_ग_लिखो(MO_HDELAY_ODD,   value);
	dprपूर्णांकk(1, "set_scale: hdelay  0x%04x (width %d)\n", value, swidth);

	value = (swidth * 4096 / width) - 4096;
	cx_ग_लिखो(MO_HSCALE_EVEN,  value);
	cx_ग_लिखो(MO_HSCALE_ODD,   value);
	dprपूर्णांकk(1, "set_scale: hscale  0x%04x\n", value);

	cx_ग_लिखो(MO_HACTIVE_EVEN, width);
	cx_ग_लिखो(MO_HACTIVE_ODD,  width);
	dprपूर्णांकk(1, "set_scale: hactive 0x%04x\n", width);

	// recalc V scale Register (delay is स्थिरant)
	cx_ग_लिखो(MO_VDELAY_EVEN, norm_vdelay(core->tvnorm));
	cx_ग_लिखो(MO_VDELAY_ODD,  norm_vdelay(core->tvnorm));
	dprपूर्णांकk(1, "set_scale: vdelay  0x%04x\n", norm_vdelay(core->tvnorm));

	value = (0x10000 - (sheight * 512 / height - 512)) & 0x1fff;
	cx_ग_लिखो(MO_VSCALE_EVEN,  value);
	cx_ग_लिखो(MO_VSCALE_ODD,   value);
	dprपूर्णांकk(1, "set_scale: vscale  0x%04x\n", value);

	cx_ग_लिखो(MO_VACTIVE_EVEN, sheight);
	cx_ग_लिखो(MO_VACTIVE_ODD,  sheight);
	dprपूर्णांकk(1, "set_scale: vactive 0x%04x\n", sheight);

	// setup filters
	value = 0;
	value |= (1 << 19);        // CFILT (शेष)
	अगर (core->tvnorm & V4L2_STD_SECAM) अणु
		value |= (1 << 15);
		value |= (1 << 16);
	पूर्ण
	अगर (INPUT(core->input).type == CX88_VMUX_SVIDEO)
		value |= (1 << 13) | (1 << 5);
	अगर (field == V4L2_FIELD_INTERLACED)
		value |= (1 << 3); // VINT (पूर्णांकerlaced vertical scaling)
	अगर (width < 385)
		value |= (1 << 0); // 3-tap पूर्णांकerpolation
	अगर (width < 193)
		value |= (1 << 1); // 5-tap पूर्णांकerpolation
	अगर (nocomb)
		value |= (3 << 5); // disable comb filter

	cx_anकरोr(MO_FILTER_EVEN,  0x7ffc7f, value); /* preserve PEAKEN, PSEL */
	cx_anकरोr(MO_FILTER_ODD,   0x7ffc7f, value);
	dprपूर्णांकk(1, "set_scale: filter  0x%04x\n", value);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(cx88_set_scale);

अटल स्थिर u32 xtal = 28636363;

अटल पूर्णांक set_pll(काष्ठा cx88_core *core, पूर्णांक prescale, u32 ofreq)
अणु
	अटल स्थिर u32 pre[] = अणु 0, 0, 0, 3, 2, 1 पूर्ण;
	u64 pll;
	u32 reg;
	पूर्णांक i;

	अगर (prescale < 2)
		prescale = 2;
	अगर (prescale > 5)
		prescale = 5;

	pll = ofreq * 8 * prescale * (u64)(1 << 20);
	करो_भाग(pll, xtal);
	reg = (pll & 0x3ffffff) | (pre[prescale] << 26);
	अगर (((reg >> 20) & 0x3f) < 14) अणु
		pr_err("pll out of range\n");
		वापस -1;
	पूर्ण

	dprपूर्णांकk(1, "set_pll:    MO_PLL_REG       0x%08x [old=0x%08x,freq=%d]\n",
		reg, cx_पढ़ो(MO_PLL_REG), ofreq);
	cx_ग_लिखो(MO_PLL_REG, reg);
	क्रम (i = 0; i < 100; i++) अणु
		reg = cx_पढ़ो(MO_DEVICE_STATUS);
		अगर (reg & (1 << 2)) अणु
			dprपूर्णांकk(1, "pll locked [pre=%d,ofreq=%d]\n",
				prescale, ofreq);
			वापस 0;
		पूर्ण
		dprपूर्णांकk(1, "pll not locked yet, waiting ...\n");
		usleep_range(10000, 20000);
	पूर्ण
	dprपूर्णांकk(1, "pll NOT locked [pre=%d,ofreq=%d]\n", prescale, ofreq);
	वापस -1;
पूर्ण

पूर्णांक cx88_start_audio_dma(काष्ठा cx88_core *core)
अणु
	/* स्थिरant 128 made buzz in analog Nicam-stereo क्रम bigger fअगरo_size */
	पूर्णांक bpl = cx88_sram_channels[SRAM_CH25].fअगरo_size / 4;

	पूर्णांक rds_bpl = cx88_sram_channels[SRAM_CH27].fअगरo_size / AUD_RDS_LINES;

	/* If करोwnstream RISC is enabled, bail out; ALSA is managing DMA */
	अगर (cx_पढ़ो(MO_AUD_DMACNTRL) & 0x10)
		वापस 0;

	/* setup fअगरo + क्रमmat */
	cx88_sram_channel_setup(core, &cx88_sram_channels[SRAM_CH25], bpl, 0);
	cx88_sram_channel_setup(core, &cx88_sram_channels[SRAM_CH26], bpl, 0);
	cx88_sram_channel_setup(core, &cx88_sram_channels[SRAM_CH27],
				rds_bpl, 0);

	cx_ग_लिखो(MO_AUDD_LNGTH, bpl); /* fअगरo bpl size */
	cx_ग_लिखो(MO_AUDR_LNGTH, rds_bpl); /* fअगरo bpl size */

	/* enable Up, Down and Audio RDS fअगरo */
	cx_ग_लिखो(MO_AUD_DMACNTRL, 0x0007);

	वापस 0;
पूर्ण

पूर्णांक cx88_stop_audio_dma(काष्ठा cx88_core *core)
अणु
	/* If करोwnstream RISC is enabled, bail out; ALSA is managing DMA */
	अगर (cx_पढ़ो(MO_AUD_DMACNTRL) & 0x10)
		वापस 0;

	/* stop dma */
	cx_ग_लिखो(MO_AUD_DMACNTRL, 0x0000);

	वापस 0;
पूर्ण

अटल पूर्णांक set_tvaudio(काष्ठा cx88_core *core)
अणु
	v4l2_std_id norm = core->tvnorm;

	अगर (INPUT(core->input).type != CX88_VMUX_TELEVISION &&
	    INPUT(core->input).type != CX88_VMUX_CABLE)
		वापस 0;

	अगर (V4L2_STD_PAL_BG & norm) अणु
		core->tvaudio = WW_BG;

	पूर्ण अन्यथा अगर (V4L2_STD_PAL_DK & norm) अणु
		core->tvaudio = WW_DK;

	पूर्ण अन्यथा अगर (V4L2_STD_PAL_I & norm) अणु
		core->tvaudio = WW_I;

	पूर्ण अन्यथा अगर (V4L2_STD_SECAM_L & norm) अणु
		core->tvaudio = WW_L;

	पूर्ण अन्यथा अगर ((V4L2_STD_SECAM_B | V4L2_STD_SECAM_G | V4L2_STD_SECAM_H) &
		   norm) अणु
		core->tvaudio = WW_BG;

	पूर्ण अन्यथा अगर (V4L2_STD_SECAM_DK & norm) अणु
		core->tvaudio = WW_DK;

	पूर्ण अन्यथा अगर ((V4L2_STD_NTSC_M & norm) ||
		   (V4L2_STD_PAL_M  & norm)) अणु
		core->tvaudio = WW_BTSC;

	पूर्ण अन्यथा अगर (V4L2_STD_NTSC_M_JP & norm) अणु
		core->tvaudio = WW_EIAJ;

	पूर्ण अन्यथा अणु
		pr_info("tvaudio support needs work for this tv norm [%s], sorry\n",
			v4l2_norm_to_name(core->tvnorm));
		core->tvaudio = WW_NONE;
		वापस 0;
	पूर्ण

	cx_anकरोr(MO_AFECFG_IO, 0x1f, 0x0);
	cx88_set_tvaudio(core);
	/* cx88_set_stereo(dev,V4L2_TUNER_MODE_STEREO); */

/*
 * This should be needed only on cx88-alsa. It seems that some cx88 chips have
 * bugs and करोes require DMA enabled क्रम it to work.
 */
	cx88_start_audio_dma(core);
	वापस 0;
पूर्ण

पूर्णांक cx88_set_tvnorm(काष्ठा cx88_core *core, v4l2_std_id norm)
अणु
	u32 fsc8;
	u32 adc_घड़ी;
	u32 vdec_घड़ी;
	u32 step_db, step_dr;
	u64 पंचांगp64;
	u32 bdelay, agcdelay, htotal;
	u32 cxअगरormat, cxoक्रमmat;

	अगर (norm == core->tvnorm)
		वापस 0;
	अगर (core->v4ldev && (vb2_is_busy(&core->v4ldev->vb2_vidq) ||
			     vb2_is_busy(&core->v4ldev->vb2_vbiq)))
		वापस -EBUSY;
	अगर (core->dvbdev && vb2_is_busy(&core->dvbdev->vb2_mpegq))
		वापस -EBUSY;
	core->tvnorm = norm;
	fsc8       = norm_fsc8(norm);
	adc_घड़ी  = xtal;
	vdec_घड़ी = fsc8;
	step_db    = fsc8;
	step_dr    = fsc8;

	अगर (norm & V4L2_STD_NTSC_M_JP) अणु
		cxअगरormat = VideoFormatNTSCJapan;
		cxoक्रमmat = 0x181f0008;
	पूर्ण अन्यथा अगर (norm & V4L2_STD_NTSC_443) अणु
		cxअगरormat = VideoFormatNTSC443;
		cxoक्रमmat = 0x181f0008;
	पूर्ण अन्यथा अगर (norm & V4L2_STD_PAL_M) अणु
		cxअगरormat = VideoFormatPALM;
		cxoक्रमmat = 0x1c1f0008;
	पूर्ण अन्यथा अगर (norm & V4L2_STD_PAL_N) अणु
		cxअगरormat = VideoFormatPALN;
		cxoक्रमmat = 0x1c1f0008;
	पूर्ण अन्यथा अगर (norm & V4L2_STD_PAL_Nc) अणु
		cxअगरormat = VideoFormatPALNC;
		cxoक्रमmat = 0x1c1f0008;
	पूर्ण अन्यथा अगर (norm & V4L2_STD_PAL_60) अणु
		cxअगरormat = VideoFormatPAL60;
		cxoक्रमmat = 0x181f0008;
	पूर्ण अन्यथा अगर (norm & V4L2_STD_NTSC) अणु
		cxअगरormat = VideoFormatNTSC;
		cxoक्रमmat = 0x181f0008;
	पूर्ण अन्यथा अगर (norm & V4L2_STD_SECAM) अणु
		step_db = 4250000 * 8;
		step_dr = 4406250 * 8;

		cxअगरormat = VideoFormatSECAM;
		cxoक्रमmat = 0x181f0008;
	पूर्ण अन्यथा अणु /* PAL */
		cxअगरormat = VideoFormatPAL;
		cxoक्रमmat = 0x181f0008;
	पूर्ण

	dprपूर्णांकk(1, "set_tvnorm: \"%s\" fsc8=%d adc=%d vdec=%d db/dr=%d/%d\n",
		v4l2_norm_to_name(core->tvnorm), fsc8, adc_घड़ी, vdec_घड़ी,
		step_db, step_dr);
	set_pll(core, 2, vdec_घड़ी);

	dprपूर्णांकk(1, "set_tvnorm: MO_INPUT_FORMAT  0x%08x [old=0x%08x]\n",
		cxअगरormat, cx_पढ़ो(MO_INPUT_FORMAT) & 0x0f);
	/*
	 * Chroma AGC must be disabled अगर SECAM is used, we enable it
	 * by शेष on PAL and NTSC
	 */
	cx_anकरोr(MO_INPUT_FORMAT, 0x40f,
		 norm & V4L2_STD_SECAM ? cxअगरormat : cxअगरormat | 0x400);

	// FIXME: as-is from DScaler
	dprपूर्णांकk(1, "set_tvnorm: MO_OUTPUT_FORMAT 0x%08x [old=0x%08x]\n",
		cxoक्रमmat, cx_पढ़ो(MO_OUTPUT_FORMAT));
	cx_ग_लिखो(MO_OUTPUT_FORMAT, cxoक्रमmat);

	// MO_SCONV_REG = adc घड़ी / video dec घड़ी * 2^17
	पंचांगp64  = adc_घड़ी * (u64)(1 << 17);
	करो_भाग(पंचांगp64, vdec_घड़ी);
	dprपूर्णांकk(1, "set_tvnorm: MO_SCONV_REG     0x%08x [old=0x%08x]\n",
		(u32)पंचांगp64, cx_पढ़ो(MO_SCONV_REG));
	cx_ग_लिखो(MO_SCONV_REG, (u32)पंचांगp64);

	// MO_SUB_STEP = 8 * fsc / video dec घड़ी * 2^22
	पंचांगp64  = step_db * (u64)(1 << 22);
	करो_भाग(पंचांगp64, vdec_घड़ी);
	dprपूर्णांकk(1, "set_tvnorm: MO_SUB_STEP      0x%08x [old=0x%08x]\n",
		(u32)पंचांगp64, cx_पढ़ो(MO_SUB_STEP));
	cx_ग_लिखो(MO_SUB_STEP, (u32)पंचांगp64);

	// MO_SUB_STEP_DR = 8 * 4406250 / video dec घड़ी * 2^22
	पंचांगp64  = step_dr * (u64)(1 << 22);
	करो_भाग(पंचांगp64, vdec_घड़ी);
	dprपूर्णांकk(1, "set_tvnorm: MO_SUB_STEP_DR   0x%08x [old=0x%08x]\n",
		(u32)पंचांगp64, cx_पढ़ो(MO_SUB_STEP_DR));
	cx_ग_लिखो(MO_SUB_STEP_DR, (u32)पंचांगp64);

	// bdelay + agcdelay
	bdelay   = vdec_घड़ी * 65 / 20000000 + 21;
	agcdelay = vdec_घड़ी * 68 / 20000000 + 15;
	dprपूर्णांकk(1,
		"set_tvnorm: MO_AGC_BURST     0x%08x [old=0x%08x,bdelay=%d,agcdelay=%d]\n",
		(bdelay << 8) | agcdelay, cx_पढ़ो(MO_AGC_BURST),
		bdelay, agcdelay);
	cx_ग_लिखो(MO_AGC_BURST, (bdelay << 8) | agcdelay);

	// htotal
	पंचांगp64 = norm_htotal(norm) * (u64)vdec_घड़ी;
	करो_भाग(पंचांगp64, fsc8);
	htotal = (u32)पंचांगp64;
	dprपूर्णांकk(1,
		"set_tvnorm: MO_HTOTAL        0x%08x [old=0x%08x,htotal=%d]\n",
		htotal, cx_पढ़ो(MO_HTOTAL), (u32)पंचांगp64);
	cx_anकरोr(MO_HTOTAL, 0x07ff, htotal);

	// vbi stuff, set vbi offset to 10 (क्रम 20 Clk*2 pixels), this makes
	// the effective vbi offset ~244 samples, the same as the Bt8x8
	cx_ग_लिखो(MO_VBI_PACKET, (10 << 11) | norm_vbipack(norm));

	// this is needed as well to set all tvnorm parameter
	cx88_set_scale(core, 320, 240, V4L2_FIELD_INTERLACED);

	// audio
	set_tvaudio(core);

	// tell i2c chips
	call_all(core, video, s_std, norm);

	/*
	 * The chroma_agc control should be inaccessible
	 * अगर the video क्रमmat is SECAM
	 */
	v4l2_ctrl_grab(core->chroma_agc, cxअगरormat == VideoFormatSECAM);

	// करोne
	वापस 0;
पूर्ण
EXPORT_SYMBOL(cx88_set_tvnorm);

/* ------------------------------------------------------------------ */

व्योम cx88_vdev_init(काष्ठा cx88_core *core,
		    काष्ठा pci_dev *pci,
		    काष्ठा video_device *vfd,
		    स्थिर काष्ठा video_device *ढाँचा_,
		    स्थिर अक्षर *type)
अणु
	*vfd = *ढाँचा_;

	/*
	 * The dev poपूर्णांकer of v4l2_device is शून्य, instead we set the
	 * video_device dev_parent poपूर्णांकer to the correct PCI bus device.
	 * This driver is a rare example where there is one v4l2_device,
	 * but the video nodes have dअगरferent parent (PCI) devices.
	 */
	vfd->v4l2_dev = &core->v4l2_dev;
	vfd->dev_parent = &pci->dev;
	vfd->release = video_device_release_empty;
	vfd->lock = &core->lock;
	snम_लिखो(vfd->name, माप(vfd->name), "%s %s (%s)",
		 core->name, type, core->board.name);
पूर्ण
EXPORT_SYMBOL(cx88_vdev_init);

काष्ठा cx88_core *cx88_core_get(काष्ठा pci_dev *pci)
अणु
	काष्ठा cx88_core *core;

	mutex_lock(&devlist);
	list_क्रम_each_entry(core, &cx88_devlist, devlist) अणु
		अगर (pci->bus->number != core->pci_bus)
			जारी;
		अगर (PCI_SLOT(pci->devfn) != core->pci_slot)
			जारी;

		अगर (cx88_get_resources(core, pci) != 0) अणु
			mutex_unlock(&devlist);
			वापस शून्य;
		पूर्ण
		refcount_inc(&core->refcount);
		mutex_unlock(&devlist);
		वापस core;
	पूर्ण

	core = cx88_core_create(pci, cx88_devcount);
	अगर (core) अणु
		cx88_devcount++;
		list_add_tail(&core->devlist, &cx88_devlist);
	पूर्ण

	mutex_unlock(&devlist);
	वापस core;
पूर्ण
EXPORT_SYMBOL(cx88_core_get);

व्योम cx88_core_put(काष्ठा cx88_core *core, काष्ठा pci_dev *pci)
अणु
	release_mem_region(pci_resource_start(pci, 0),
			   pci_resource_len(pci, 0));

	अगर (!refcount_dec_and_test(&core->refcount))
		वापस;

	mutex_lock(&devlist);
	cx88_ir_fini(core);
	अगर (core->i2c_rc == 0) अणु
		i2c_unरेजिस्टर_device(core->i2c_rtc);
		i2c_del_adapter(&core->i2c_adap);
	पूर्ण
	list_del(&core->devlist);
	iounmap(core->lmmio);
	cx88_devcount--;
	mutex_unlock(&devlist);
	v4l2_ctrl_handler_मुक्त(&core->video_hdl);
	v4l2_ctrl_handler_मुक्त(&core->audio_hdl);
	v4l2_device_unरेजिस्टर(&core->v4l2_dev);
	kमुक्त(core);
पूर्ण
EXPORT_SYMBOL(cx88_core_put);
