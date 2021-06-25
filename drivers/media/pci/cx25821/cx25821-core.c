<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Driver क्रम the Conexant CX25821 PCIe bridge
 *
 *  Copyright (C) 2009 Conexant Systems Inc.
 *  Authors  <shu.lin@conexant.com>, <hiep.huynh@conexant.com>
 *  Based on Steven Toth <stoth@linuxtv.org> cx23885 driver
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>
#समावेश "cx25821.h"
#समावेश "cx25821-sram.h"
#समावेश "cx25821-video.h"

MODULE_DESCRIPTION("Driver for Athena cards");
MODULE_AUTHOR("Shu Lin - Hiep Huynh");
MODULE_LICENSE("GPL");

अटल अचिन्हित पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "enable debug messages");

अटल अचिन्हित पूर्णांक card[] = अणु[0 ... (CX25821_MAXBOARDS - 1)] = UNSET पूर्ण;
module_param_array(card, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(card, "card type");

स्थिर काष्ठा sram_channel cx25821_sram_channels[] = अणु
	[SRAM_CH00] = अणु
		.i = SRAM_CH00,
		.name = "VID A",
		.cmds_start = VID_A_DOWN_CMDS,
		.ctrl_start = VID_A_IQ,
		.cdt = VID_A_CDT,
		.fअगरo_start = VID_A_DOWN_CLUSTER_1,
		.fअगरo_size = (VID_CLUSTER_SIZE << 2),
		.ptr1_reg = DMA1_PTR1,
		.ptr2_reg = DMA1_PTR2,
		.cnt1_reg = DMA1_CNT1,
		.cnt2_reg = DMA1_CNT2,
		.पूर्णांक_msk = VID_A_INT_MSK,
		.पूर्णांक_stat = VID_A_INT_STAT,
		.पूर्णांक_mstat = VID_A_INT_MSTAT,
		.dma_ctl = VID_DST_A_DMA_CTL,
		.gpcnt_ctl = VID_DST_A_GPCNT_CTL,
		.gpcnt = VID_DST_A_GPCNT,
		.vip_ctl = VID_DST_A_VIP_CTL,
		.pix_frmt = VID_DST_A_PIX_FRMT,
	पूर्ण,

	[SRAM_CH01] = अणु
		.i = SRAM_CH01,
		.name = "VID B",
		.cmds_start = VID_B_DOWN_CMDS,
		.ctrl_start = VID_B_IQ,
		.cdt = VID_B_CDT,
		.fअगरo_start = VID_B_DOWN_CLUSTER_1,
		.fअगरo_size = (VID_CLUSTER_SIZE << 2),
		.ptr1_reg = DMA2_PTR1,
		.ptr2_reg = DMA2_PTR2,
		.cnt1_reg = DMA2_CNT1,
		.cnt2_reg = DMA2_CNT2,
		.पूर्णांक_msk = VID_B_INT_MSK,
		.पूर्णांक_stat = VID_B_INT_STAT,
		.पूर्णांक_mstat = VID_B_INT_MSTAT,
		.dma_ctl = VID_DST_B_DMA_CTL,
		.gpcnt_ctl = VID_DST_B_GPCNT_CTL,
		.gpcnt = VID_DST_B_GPCNT,
		.vip_ctl = VID_DST_B_VIP_CTL,
		.pix_frmt = VID_DST_B_PIX_FRMT,
	पूर्ण,

	[SRAM_CH02] = अणु
		.i = SRAM_CH02,
		.name = "VID C",
		.cmds_start = VID_C_DOWN_CMDS,
		.ctrl_start = VID_C_IQ,
		.cdt = VID_C_CDT,
		.fअगरo_start = VID_C_DOWN_CLUSTER_1,
		.fअगरo_size = (VID_CLUSTER_SIZE << 2),
		.ptr1_reg = DMA3_PTR1,
		.ptr2_reg = DMA3_PTR2,
		.cnt1_reg = DMA3_CNT1,
		.cnt2_reg = DMA3_CNT2,
		.पूर्णांक_msk = VID_C_INT_MSK,
		.पूर्णांक_stat = VID_C_INT_STAT,
		.पूर्णांक_mstat = VID_C_INT_MSTAT,
		.dma_ctl = VID_DST_C_DMA_CTL,
		.gpcnt_ctl = VID_DST_C_GPCNT_CTL,
		.gpcnt = VID_DST_C_GPCNT,
		.vip_ctl = VID_DST_C_VIP_CTL,
		.pix_frmt = VID_DST_C_PIX_FRMT,
	पूर्ण,

	[SRAM_CH03] = अणु
		.i = SRAM_CH03,
		.name = "VID D",
		.cmds_start = VID_D_DOWN_CMDS,
		.ctrl_start = VID_D_IQ,
		.cdt = VID_D_CDT,
		.fअगरo_start = VID_D_DOWN_CLUSTER_1,
		.fअगरo_size = (VID_CLUSTER_SIZE << 2),
		.ptr1_reg = DMA4_PTR1,
		.ptr2_reg = DMA4_PTR2,
		.cnt1_reg = DMA4_CNT1,
		.cnt2_reg = DMA4_CNT2,
		.पूर्णांक_msk = VID_D_INT_MSK,
		.पूर्णांक_stat = VID_D_INT_STAT,
		.पूर्णांक_mstat = VID_D_INT_MSTAT,
		.dma_ctl = VID_DST_D_DMA_CTL,
		.gpcnt_ctl = VID_DST_D_GPCNT_CTL,
		.gpcnt = VID_DST_D_GPCNT,
		.vip_ctl = VID_DST_D_VIP_CTL,
		.pix_frmt = VID_DST_D_PIX_FRMT,
	पूर्ण,

	[SRAM_CH04] = अणु
		.i = SRAM_CH04,
		.name = "VID E",
		.cmds_start = VID_E_DOWN_CMDS,
		.ctrl_start = VID_E_IQ,
		.cdt = VID_E_CDT,
		.fअगरo_start = VID_E_DOWN_CLUSTER_1,
		.fअगरo_size = (VID_CLUSTER_SIZE << 2),
		.ptr1_reg = DMA5_PTR1,
		.ptr2_reg = DMA5_PTR2,
		.cnt1_reg = DMA5_CNT1,
		.cnt2_reg = DMA5_CNT2,
		.पूर्णांक_msk = VID_E_INT_MSK,
		.पूर्णांक_stat = VID_E_INT_STAT,
		.पूर्णांक_mstat = VID_E_INT_MSTAT,
		.dma_ctl = VID_DST_E_DMA_CTL,
		.gpcnt_ctl = VID_DST_E_GPCNT_CTL,
		.gpcnt = VID_DST_E_GPCNT,
		.vip_ctl = VID_DST_E_VIP_CTL,
		.pix_frmt = VID_DST_E_PIX_FRMT,
	पूर्ण,

	[SRAM_CH05] = अणु
		.i = SRAM_CH05,
		.name = "VID F",
		.cmds_start = VID_F_DOWN_CMDS,
		.ctrl_start = VID_F_IQ,
		.cdt = VID_F_CDT,
		.fअगरo_start = VID_F_DOWN_CLUSTER_1,
		.fअगरo_size = (VID_CLUSTER_SIZE << 2),
		.ptr1_reg = DMA6_PTR1,
		.ptr2_reg = DMA6_PTR2,
		.cnt1_reg = DMA6_CNT1,
		.cnt2_reg = DMA6_CNT2,
		.पूर्णांक_msk = VID_F_INT_MSK,
		.पूर्णांक_stat = VID_F_INT_STAT,
		.पूर्णांक_mstat = VID_F_INT_MSTAT,
		.dma_ctl = VID_DST_F_DMA_CTL,
		.gpcnt_ctl = VID_DST_F_GPCNT_CTL,
		.gpcnt = VID_DST_F_GPCNT,
		.vip_ctl = VID_DST_F_VIP_CTL,
		.pix_frmt = VID_DST_F_PIX_FRMT,
	पूर्ण,

	[SRAM_CH06] = अणु
		.i = SRAM_CH06,
		.name = "VID G",
		.cmds_start = VID_G_DOWN_CMDS,
		.ctrl_start = VID_G_IQ,
		.cdt = VID_G_CDT,
		.fअगरo_start = VID_G_DOWN_CLUSTER_1,
		.fअगरo_size = (VID_CLUSTER_SIZE << 2),
		.ptr1_reg = DMA7_PTR1,
		.ptr2_reg = DMA7_PTR2,
		.cnt1_reg = DMA7_CNT1,
		.cnt2_reg = DMA7_CNT2,
		.पूर्णांक_msk = VID_G_INT_MSK,
		.पूर्णांक_stat = VID_G_INT_STAT,
		.पूर्णांक_mstat = VID_G_INT_MSTAT,
		.dma_ctl = VID_DST_G_DMA_CTL,
		.gpcnt_ctl = VID_DST_G_GPCNT_CTL,
		.gpcnt = VID_DST_G_GPCNT,
		.vip_ctl = VID_DST_G_VIP_CTL,
		.pix_frmt = VID_DST_G_PIX_FRMT,
	पूर्ण,

	[SRAM_CH07] = अणु
		.i = SRAM_CH07,
		.name = "VID H",
		.cmds_start = VID_H_DOWN_CMDS,
		.ctrl_start = VID_H_IQ,
		.cdt = VID_H_CDT,
		.fअगरo_start = VID_H_DOWN_CLUSTER_1,
		.fअगरo_size = (VID_CLUSTER_SIZE << 2),
		.ptr1_reg = DMA8_PTR1,
		.ptr2_reg = DMA8_PTR2,
		.cnt1_reg = DMA8_CNT1,
		.cnt2_reg = DMA8_CNT2,
		.पूर्णांक_msk = VID_H_INT_MSK,
		.पूर्णांक_stat = VID_H_INT_STAT,
		.पूर्णांक_mstat = VID_H_INT_MSTAT,
		.dma_ctl = VID_DST_H_DMA_CTL,
		.gpcnt_ctl = VID_DST_H_GPCNT_CTL,
		.gpcnt = VID_DST_H_GPCNT,
		.vip_ctl = VID_DST_H_VIP_CTL,
		.pix_frmt = VID_DST_H_PIX_FRMT,
	पूर्ण,

	[SRAM_CH08] = अणु
		.name = "audio from",
		.cmds_start = AUD_A_DOWN_CMDS,
		.ctrl_start = AUD_A_IQ,
		.cdt = AUD_A_CDT,
		.fअगरo_start = AUD_A_DOWN_CLUSTER_1,
		.fअगरo_size = AUDIO_CLUSTER_SIZE * 3,
		.ptr1_reg = DMA17_PTR1,
		.ptr2_reg = DMA17_PTR2,
		.cnt1_reg = DMA17_CNT1,
		.cnt2_reg = DMA17_CNT2,
	पूर्ण,

	[SRAM_CH09] = अणु
		.i = SRAM_CH09,
		.name = "VID Upstream I",
		.cmds_start = VID_I_UP_CMDS,
		.ctrl_start = VID_I_IQ,
		.cdt = VID_I_CDT,
		.fअगरo_start = VID_I_UP_CLUSTER_1,
		.fअगरo_size = (VID_CLUSTER_SIZE << 2),
		.ptr1_reg = DMA15_PTR1,
		.ptr2_reg = DMA15_PTR2,
		.cnt1_reg = DMA15_CNT1,
		.cnt2_reg = DMA15_CNT2,
		.पूर्णांक_msk = VID_I_INT_MSK,
		.पूर्णांक_stat = VID_I_INT_STAT,
		.पूर्णांक_mstat = VID_I_INT_MSTAT,
		.dma_ctl = VID_SRC_I_DMA_CTL,
		.gpcnt_ctl = VID_SRC_I_GPCNT_CTL,
		.gpcnt = VID_SRC_I_GPCNT,

		.vid_fmt_ctl = VID_SRC_I_FMT_CTL,
		.vid_active_ctl1 = VID_SRC_I_ACTIVE_CTL1,
		.vid_active_ctl2 = VID_SRC_I_ACTIVE_CTL2,
		.vid_cdt_size = VID_SRC_I_CDT_SZ,
		.irq_bit = 8,
	पूर्ण,

	[SRAM_CH10] = अणु
		.i = SRAM_CH10,
		.name = "VID Upstream J",
		.cmds_start = VID_J_UP_CMDS,
		.ctrl_start = VID_J_IQ,
		.cdt = VID_J_CDT,
		.fअगरo_start = VID_J_UP_CLUSTER_1,
		.fअगरo_size = (VID_CLUSTER_SIZE << 2),
		.ptr1_reg = DMA16_PTR1,
		.ptr2_reg = DMA16_PTR2,
		.cnt1_reg = DMA16_CNT1,
		.cnt2_reg = DMA16_CNT2,
		.पूर्णांक_msk = VID_J_INT_MSK,
		.पूर्णांक_stat = VID_J_INT_STAT,
		.पूर्णांक_mstat = VID_J_INT_MSTAT,
		.dma_ctl = VID_SRC_J_DMA_CTL,
		.gpcnt_ctl = VID_SRC_J_GPCNT_CTL,
		.gpcnt = VID_SRC_J_GPCNT,

		.vid_fmt_ctl = VID_SRC_J_FMT_CTL,
		.vid_active_ctl1 = VID_SRC_J_ACTIVE_CTL1,
		.vid_active_ctl2 = VID_SRC_J_ACTIVE_CTL2,
		.vid_cdt_size = VID_SRC_J_CDT_SZ,
		.irq_bit = 9,
	पूर्ण,

	[SRAM_CH11] = अणु
		.i = SRAM_CH11,
		.name = "Audio Upstream Channel B",
		.cmds_start = AUD_B_UP_CMDS,
		.ctrl_start = AUD_B_IQ,
		.cdt = AUD_B_CDT,
		.fअगरo_start = AUD_B_UP_CLUSTER_1,
		.fअगरo_size = (AUDIO_CLUSTER_SIZE * 3),
		.ptr1_reg = DMA22_PTR1,
		.ptr2_reg = DMA22_PTR2,
		.cnt1_reg = DMA22_CNT1,
		.cnt2_reg = DMA22_CNT2,
		.पूर्णांक_msk = AUD_B_INT_MSK,
		.पूर्णांक_stat = AUD_B_INT_STAT,
		.पूर्णांक_mstat = AUD_B_INT_MSTAT,
		.dma_ctl = AUD_INT_DMA_CTL,
		.gpcnt_ctl = AUD_B_GPCNT_CTL,
		.gpcnt = AUD_B_GPCNT,
		.aud_length = AUD_B_LNGTH,
		.aud_cfg = AUD_B_CFG,
		.fld_aud_fअगरo_en = FLD_AUD_SRC_B_FIFO_EN,
		.fld_aud_risc_en = FLD_AUD_SRC_B_RISC_EN,
		.irq_bit = 11,
	पूर्ण,
पूर्ण;
EXPORT_SYMBOL(cx25821_sram_channels);

अटल पूर्णांक cx25821_risc_decode(u32 risc)
अणु
	अटल स्थिर अक्षर * स्थिर instr[16] = अणु
		[RISC_SYNC >> 28] = "sync",
		[RISC_WRITE >> 28] = "write",
		[RISC_WRITEC >> 28] = "writec",
		[RISC_READ >> 28] = "read",
		[RISC_READC >> 28] = "readc",
		[RISC_JUMP >> 28] = "jump",
		[RISC_SKIP >> 28] = "skip",
		[RISC_WRITERM >> 28] = "writerm",
		[RISC_WRITECM >> 28] = "writecm",
		[RISC_WRITECR >> 28] = "writecr",
	पूर्ण;
	अटल स्थिर पूर्णांक incr[16] = अणु
		[RISC_WRITE >> 28] = 3,
		[RISC_JUMP >> 28] = 3,
		[RISC_SKIP >> 28] = 1,
		[RISC_SYNC >> 28] = 1,
		[RISC_WRITERM >> 28] = 3,
		[RISC_WRITECM >> 28] = 3,
		[RISC_WRITECR >> 28] = 4,
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर bits[] = अणु
		"12", "13", "14", "resync",
		"cnt0", "cnt1", "18", "19",
		"20", "21", "22", "23",
		"irq1", "irq2", "eol", "sol",
	पूर्ण;
	पूर्णांक i;

	pr_cont("0x%08x [ %s",
		risc, instr[risc >> 28] ? instr[risc >> 28] : "INVALID");
	क्रम (i = ARRAY_SIZE(bits) - 1; i >= 0; i--) अणु
		अगर (risc & (1 << (i + 12)))
			pr_cont(" %s", bits[i]);
	पूर्ण
	pr_cont(" count=%d ]\n", risc & 0xfff);
	वापस incr[risc >> 28] ? incr[risc >> 28] : 1;
पूर्ण

अटल अंतरभूत पूर्णांक i2c_slave_did_ack(काष्ठा i2c_adapter *i2c_adap)
अणु
	काष्ठा cx25821_i2c *bus = i2c_adap->algo_data;
	काष्ठा cx25821_dev *dev = bus->dev;
	वापस cx_पढ़ो(bus->reg_stat) & 0x01;
पूर्ण

अटल व्योम cx25821_रेजिस्टरs_init(काष्ठा cx25821_dev *dev)
अणु
	u32 पंचांगp;

	/* enable RUN_RISC in Pecos */
	cx_ग_लिखो(DEV_CNTRL2, 0x20);

	/* Set the master PCI पूर्णांकerrupt masks to enable video, audio, MBIF,
	 * and GPIO पूर्णांकerrupts
	 * I2C पूर्णांकerrupt masking is handled by the I2C objects themselves. */
	cx_ग_लिखो(PCI_INT_MSK, 0x2001FFFF);

	पंचांगp = cx_पढ़ो(RDR_TLCTL0);
	पंचांगp &= ~FLD_CFG_RCB_CK_EN;	/* Clear the RCB_CK_EN bit */
	cx_ग_लिखो(RDR_TLCTL0, पंचांगp);

	/* PLL-A setting क्रम the Audio Master Clock */
	cx_ग_लिखो(PLL_A_INT_FRAC, 0x9807A58B);

	/* PLL_A_POST = 0x1C, PLL_A_OUT_TO_PIN = 0x1 */
	cx_ग_लिखो(PLL_A_POST_STAT_BIST, 0x8000019C);

	/* clear reset bit [31] */
	पंचांगp = cx_पढ़ो(PLL_A_INT_FRAC);
	cx_ग_लिखो(PLL_A_INT_FRAC, पंचांगp & 0x7FFFFFFF);

	/* PLL-B setting क्रम Mobilygen Host Bus Interface */
	cx_ग_लिखो(PLL_B_INT_FRAC, 0x9883A86F);

	/* PLL_B_POST = 0xD, PLL_B_OUT_TO_PIN = 0x0 */
	cx_ग_लिखो(PLL_B_POST_STAT_BIST, 0x8000018D);

	/* clear reset bit [31] */
	पंचांगp = cx_पढ़ो(PLL_B_INT_FRAC);
	cx_ग_लिखो(PLL_B_INT_FRAC, पंचांगp & 0x7FFFFFFF);

	/* PLL-C setting क्रम video upstream channel */
	cx_ग_लिखो(PLL_C_INT_FRAC, 0x96A0EA3F);

	/* PLL_C_POST = 0x3, PLL_C_OUT_TO_PIN = 0x0 */
	cx_ग_लिखो(PLL_C_POST_STAT_BIST, 0x80000103);

	/* clear reset bit [31] */
	पंचांगp = cx_पढ़ो(PLL_C_INT_FRAC);
	cx_ग_लिखो(PLL_C_INT_FRAC, पंचांगp & 0x7FFFFFFF);

	/* PLL-D setting क्रम audio upstream channel */
	cx_ग_लिखो(PLL_D_INT_FRAC, 0x98757F5B);

	/* PLL_D_POST = 0x13, PLL_D_OUT_TO_PIN = 0x0 */
	cx_ग_लिखो(PLL_D_POST_STAT_BIST, 0x80000113);

	/* clear reset bit [31] */
	पंचांगp = cx_पढ़ो(PLL_D_INT_FRAC);
	cx_ग_लिखो(PLL_D_INT_FRAC, पंचांगp & 0x7FFFFFFF);

	/* This selects the PLL C घड़ी source क्रम the video upstream channel
	 * I and J */
	पंचांगp = cx_पढ़ो(VID_CH_CLK_SEL);
	cx_ग_लिखो(VID_CH_CLK_SEL, (पंचांगp & 0x00FFFFFF) | 0x24000000);

	/* 656/VIP SRC Upstream Channel I & J and 7 - Host Bus Interface क्रम
	 * channel A-C
	 * select 656/VIP DST क्रम करोwnstream Channel A - C */
	पंचांगp = cx_पढ़ो(VID_CH_MODE_SEL);
	/* cx_ग_लिखो( VID_CH_MODE_SEL, पंचांगp | 0x1B0001FF); */
	cx_ग_लिखो(VID_CH_MODE_SEL, पंचांगp & 0xFFFFFE00);

	/* enables 656 port I and J as output */
	पंचांगp = cx_पढ़ो(CLK_RST);
	/* use बाह्यal ALT_PLL_REF pin as its reference घड़ी instead */
	पंचांगp |= FLD_USE_ALT_PLL_REF;
	cx_ग_लिखो(CLK_RST, पंचांगp & ~(FLD_VID_I_CLK_NOE | FLD_VID_J_CLK_NOE));

	msleep(100);
पूर्ण

पूर्णांक cx25821_sram_channel_setup(काष्ठा cx25821_dev *dev,
			       स्थिर काष्ठा sram_channel *ch,
			       अचिन्हित पूर्णांक bpl, u32 risc)
अणु
	अचिन्हित पूर्णांक i, lines;
	u32 cdt;

	अगर (ch->cmds_start == 0) अणु
		cx_ग_लिखो(ch->ptr1_reg, 0);
		cx_ग_लिखो(ch->ptr2_reg, 0);
		cx_ग_लिखो(ch->cnt2_reg, 0);
		cx_ग_लिखो(ch->cnt1_reg, 0);
		वापस 0;
	पूर्ण

	bpl = (bpl + 7) & ~7;	/* alignment */
	cdt = ch->cdt;
	lines = ch->fअगरo_size / bpl;

	अगर (lines > 4)
		lines = 4;

	BUG_ON(lines < 2);

	cx_ग_लिखो(8 + 0, RISC_JUMP | RISC_IRQ1 | RISC_CNT_INC);
	cx_ग_लिखो(8 + 4, 8);
	cx_ग_लिखो(8 + 8, 0);

	/* ग_लिखो CDT */
	क्रम (i = 0; i < lines; i++) अणु
		cx_ग_लिखो(cdt + 16 * i, ch->fअगरo_start + bpl * i);
		cx_ग_लिखो(cdt + 16 * i + 4, 0);
		cx_ग_लिखो(cdt + 16 * i + 8, 0);
		cx_ग_लिखो(cdt + 16 * i + 12, 0);
	पूर्ण

	/* init the first cdt buffer */
	क्रम (i = 0; i < 128; i++)
		cx_ग_लिखो(ch->fअगरo_start + 4 * i, i);

	/* ग_लिखो CMDS */
	अगर (ch->jumponly)
		cx_ग_लिखो(ch->cmds_start + 0, 8);
	अन्यथा
		cx_ग_लिखो(ch->cmds_start + 0, risc);

	cx_ग_लिखो(ch->cmds_start + 4, 0);	/* 64 bits 63-32 */
	cx_ग_लिखो(ch->cmds_start + 8, cdt);
	cx_ग_लिखो(ch->cmds_start + 12, (lines * 16) >> 3);
	cx_ग_लिखो(ch->cmds_start + 16, ch->ctrl_start);

	अगर (ch->jumponly)
		cx_ग_लिखो(ch->cmds_start + 20, 0x80000000 | (64 >> 2));
	अन्यथा
		cx_ग_लिखो(ch->cmds_start + 20, 64 >> 2);

	क्रम (i = 24; i < 80; i += 4)
		cx_ग_लिखो(ch->cmds_start + i, 0);

	/* fill रेजिस्टरs */
	cx_ग_लिखो(ch->ptr1_reg, ch->fअगरo_start);
	cx_ग_लिखो(ch->ptr2_reg, cdt);
	cx_ग_लिखो(ch->cnt2_reg, (lines * 16) >> 3);
	cx_ग_लिखो(ch->cnt1_reg, (bpl >> 3) - 1);

	वापस 0;
पूर्ण

पूर्णांक cx25821_sram_channel_setup_audio(काष्ठा cx25821_dev *dev,
				     स्थिर काष्ठा sram_channel *ch,
				     अचिन्हित पूर्णांक bpl, u32 risc)
अणु
	अचिन्हित पूर्णांक i, lines;
	u32 cdt;

	अगर (ch->cmds_start == 0) अणु
		cx_ग_लिखो(ch->ptr1_reg, 0);
		cx_ग_लिखो(ch->ptr2_reg, 0);
		cx_ग_लिखो(ch->cnt2_reg, 0);
		cx_ग_लिखो(ch->cnt1_reg, 0);
		वापस 0;
	पूर्ण

	bpl = (bpl + 7) & ~7;	/* alignment */
	cdt = ch->cdt;
	lines = ch->fअगरo_size / bpl;

	अगर (lines > 3)
		lines = 3;	/* क्रम AUDIO */

	BUG_ON(lines < 2);

	cx_ग_लिखो(8 + 0, RISC_JUMP | RISC_IRQ1 | RISC_CNT_INC);
	cx_ग_लिखो(8 + 4, 8);
	cx_ग_लिखो(8 + 8, 0);

	/* ग_लिखो CDT */
	क्रम (i = 0; i < lines; i++) अणु
		cx_ग_लिखो(cdt + 16 * i, ch->fअगरo_start + bpl * i);
		cx_ग_लिखो(cdt + 16 * i + 4, 0);
		cx_ग_लिखो(cdt + 16 * i + 8, 0);
		cx_ग_लिखो(cdt + 16 * i + 12, 0);
	पूर्ण

	/* ग_लिखो CMDS */
	अगर (ch->jumponly)
		cx_ग_लिखो(ch->cmds_start + 0, 8);
	अन्यथा
		cx_ग_लिखो(ch->cmds_start + 0, risc);

	cx_ग_लिखो(ch->cmds_start + 4, 0);	/* 64 bits 63-32 */
	cx_ग_लिखो(ch->cmds_start + 8, cdt);
	cx_ग_लिखो(ch->cmds_start + 12, (lines * 16) >> 3);
	cx_ग_लिखो(ch->cmds_start + 16, ch->ctrl_start);

	/* IQ size */
	अगर (ch->jumponly)
		cx_ग_लिखो(ch->cmds_start + 20, 0x80000000 | (64 >> 2));
	अन्यथा
		cx_ग_लिखो(ch->cmds_start + 20, 64 >> 2);

	/* zero out */
	क्रम (i = 24; i < 80; i += 4)
		cx_ग_लिखो(ch->cmds_start + i, 0);

	/* fill रेजिस्टरs */
	cx_ग_लिखो(ch->ptr1_reg, ch->fअगरo_start);
	cx_ग_लिखो(ch->ptr2_reg, cdt);
	cx_ग_लिखो(ch->cnt2_reg, (lines * 16) >> 3);
	cx_ग_लिखो(ch->cnt1_reg, (bpl >> 3) - 1);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(cx25821_sram_channel_setup_audio);

व्योम cx25821_sram_channel_dump(काष्ठा cx25821_dev *dev, स्थिर काष्ठा sram_channel *ch)
अणु
	अटल अक्षर *name[] = अणु
		"init risc lo",
		"init risc hi",
		"cdt base",
		"cdt size",
		"iq base",
		"iq size",
		"risc pc lo",
		"risc pc hi",
		"iq wr ptr",
		"iq rd ptr",
		"cdt current",
		"pci target lo",
		"pci target hi",
		"line / byte",
	पूर्ण;
	u32 risc;
	अचिन्हित पूर्णांक i, j, n;

	pr_warn("%s: %s - dma channel status dump\n", dev->name, ch->name);
	क्रम (i = 0; i < ARRAY_SIZE(name); i++)
		pr_warn("cmds + 0x%2x:   %-15s: 0x%08x\n",
			i * 4, name[i], cx_पढ़ो(ch->cmds_start + 4 * i));

	j = i * 4;
	क्रम (i = 0; i < 4;) अणु
		risc = cx_पढ़ो(ch->cmds_start + 4 * (i + 14));
		pr_warn("cmds + 0x%2x:   risc%d: ", j + i * 4, i);
		i += cx25821_risc_decode(risc);
	पूर्ण

	क्रम (i = 0; i < (64 >> 2); i += n) अणु
		risc = cx_पढ़ो(ch->ctrl_start + 4 * i);
		/* No consideration क्रम bits 63-32 */

		pr_warn("ctrl + 0x%2x (0x%08x): iq %x: ",
			i * 4, ch->ctrl_start + 4 * i, i);
		n = cx25821_risc_decode(risc);
		क्रम (j = 1; j < n; j++) अणु
			risc = cx_पढ़ो(ch->ctrl_start + 4 * (i + j));
			pr_warn("ctrl + 0x%2x :   iq %x: 0x%08x [ arg #%d ]\n",
				4 * (i + j), i + j, risc, j);
		पूर्ण
	पूर्ण

	pr_warn("        :   fifo: 0x%08x -> 0x%x\n",
		ch->fअगरo_start, ch->fअगरo_start + ch->fअगरo_size);
	pr_warn("        :   ctrl: 0x%08x -> 0x%x\n",
		ch->ctrl_start, ch->ctrl_start + 6 * 16);
	pr_warn("        :   ptr1_reg: 0x%08x\n",
		cx_पढ़ो(ch->ptr1_reg));
	pr_warn("        :   ptr2_reg: 0x%08x\n",
		cx_पढ़ो(ch->ptr2_reg));
	pr_warn("        :   cnt1_reg: 0x%08x\n",
		cx_पढ़ो(ch->cnt1_reg));
	pr_warn("        :   cnt2_reg: 0x%08x\n",
		cx_पढ़ो(ch->cnt2_reg));
पूर्ण

व्योम cx25821_sram_channel_dump_audio(काष्ठा cx25821_dev *dev,
				     स्थिर काष्ठा sram_channel *ch)
अणु
	अटल स्थिर अक्षर * स्थिर name[] = अणु
		"init risc lo",
		"init risc hi",
		"cdt base",
		"cdt size",
		"iq base",
		"iq size",
		"risc pc lo",
		"risc pc hi",
		"iq wr ptr",
		"iq rd ptr",
		"cdt current",
		"pci target lo",
		"pci target hi",
		"line / byte",
	पूर्ण;

	u32 risc, value, पंचांगp;
	अचिन्हित पूर्णांक i, j, n;

	pr_info("\n%s: %s - dma Audio channel status dump\n",
		dev->name, ch->name);

	क्रम (i = 0; i < ARRAY_SIZE(name); i++)
		pr_info("%s: cmds + 0x%2x:   %-15s: 0x%08x\n",
			dev->name, i * 4, name[i],
			cx_पढ़ो(ch->cmds_start + 4 * i));

	j = i * 4;
	क्रम (i = 0; i < 4;) अणु
		risc = cx_पढ़ो(ch->cmds_start + 4 * (i + 14));
		pr_warn("cmds + 0x%2x:   risc%d: ", j + i * 4, i);
		i += cx25821_risc_decode(risc);
	पूर्ण

	क्रम (i = 0; i < (64 >> 2); i += n) अणु
		risc = cx_पढ़ो(ch->ctrl_start + 4 * i);
		/* No consideration क्रम bits 63-32 */

		pr_warn("ctrl + 0x%2x (0x%08x): iq %x: ",
			i * 4, ch->ctrl_start + 4 * i, i);
		n = cx25821_risc_decode(risc);

		क्रम (j = 1; j < n; j++) अणु
			risc = cx_पढ़ो(ch->ctrl_start + 4 * (i + j));
			pr_warn("ctrl + 0x%2x :   iq %x: 0x%08x [ arg #%d ]\n",
				4 * (i + j), i + j, risc, j);
		पूर्ण
	पूर्ण

	pr_warn("        :   fifo: 0x%08x -> 0x%x\n",
		ch->fअगरo_start, ch->fअगरo_start + ch->fअगरo_size);
	pr_warn("        :   ctrl: 0x%08x -> 0x%x\n",
		ch->ctrl_start, ch->ctrl_start + 6 * 16);
	pr_warn("        :   ptr1_reg: 0x%08x\n",
		cx_पढ़ो(ch->ptr1_reg));
	pr_warn("        :   ptr2_reg: 0x%08x\n",
		cx_पढ़ो(ch->ptr2_reg));
	pr_warn("        :   cnt1_reg: 0x%08x\n",
		cx_पढ़ो(ch->cnt1_reg));
	pr_warn("        :   cnt2_reg: 0x%08x\n",
		cx_पढ़ो(ch->cnt2_reg));

	क्रम (i = 0; i < 4; i++) अणु
		risc = cx_पढ़ो(ch->cmds_start + 56 + (i * 4));
		pr_warn("instruction %d = 0x%x\n", i, risc);
	पूर्ण

	/* पढ़ो data from the first cdt buffer */
	risc = cx_पढ़ो(AUD_A_CDT);
	pr_warn("\nread cdt loc=0x%x\n", risc);
	क्रम (i = 0; i < 8; i++) अणु
		n = cx_पढ़ो(risc + i * 4);
		pr_cont("0x%x ", n);
	पूर्ण
	pr_cont("\n\n");

	value = cx_पढ़ो(CLK_RST);
	CX25821_INFO(" CLK_RST = 0x%x\n\n", value);

	value = cx_पढ़ो(PLL_A_POST_STAT_BIST);
	CX25821_INFO(" PLL_A_POST_STAT_BIST = 0x%x\n\n", value);
	value = cx_पढ़ो(PLL_A_INT_FRAC);
	CX25821_INFO(" PLL_A_INT_FRAC = 0x%x\n\n", value);

	value = cx_पढ़ो(PLL_B_POST_STAT_BIST);
	CX25821_INFO(" PLL_B_POST_STAT_BIST = 0x%x\n\n", value);
	value = cx_पढ़ो(PLL_B_INT_FRAC);
	CX25821_INFO(" PLL_B_INT_FRAC = 0x%x\n\n", value);

	value = cx_पढ़ो(PLL_C_POST_STAT_BIST);
	CX25821_INFO(" PLL_C_POST_STAT_BIST = 0x%x\n\n", value);
	value = cx_पढ़ो(PLL_C_INT_FRAC);
	CX25821_INFO(" PLL_C_INT_FRAC = 0x%x\n\n", value);

	value = cx_पढ़ो(PLL_D_POST_STAT_BIST);
	CX25821_INFO(" PLL_D_POST_STAT_BIST = 0x%x\n\n", value);
	value = cx_पढ़ो(PLL_D_INT_FRAC);
	CX25821_INFO(" PLL_D_INT_FRAC = 0x%x\n\n", value);

	value = cx25821_i2c_पढ़ो(&dev->i2c_bus[0], AFE_AB_DIAG_CTRL, &पंचांगp);
	CX25821_INFO(" AFE_AB_DIAG_CTRL (0x10900090) = 0x%x\n\n", value);
पूर्ण
EXPORT_SYMBOL(cx25821_sram_channel_dump_audio);

अटल व्योम cx25821_shutकरोwn(काष्ठा cx25821_dev *dev)
अणु
	पूर्णांक i;

	/* disable RISC controller */
	cx_ग_लिखो(DEV_CNTRL2, 0);

	/* Disable Video A/B activity */
	क्रम (i = 0; i < VID_CHANNEL_NUM; i++) अणु
		cx_ग_लिखो(dev->channels[i].sram_channels->dma_ctl, 0);
		cx_ग_लिखो(dev->channels[i].sram_channels->पूर्णांक_msk, 0);
	पूर्ण

	क्रम (i = VID_UPSTREAM_SRAM_CHANNEL_I;
		i <= VID_UPSTREAM_SRAM_CHANNEL_J; i++) अणु
		cx_ग_लिखो(dev->channels[i].sram_channels->dma_ctl, 0);
		cx_ग_लिखो(dev->channels[i].sram_channels->पूर्णांक_msk, 0);
	पूर्ण

	/* Disable Audio activity */
	cx_ग_लिखो(AUD_INT_DMA_CTL, 0);

	/* Disable Serial port */
	cx_ग_लिखो(UART_CTL, 0);

	/* Disable Interrupts */
	cx_ग_लिखो(PCI_INT_MSK, 0);
	cx_ग_लिखो(AUD_A_INT_MSK, 0);
पूर्ण

व्योम cx25821_set_pixel_क्रमmat(काष्ठा cx25821_dev *dev, पूर्णांक channel_select,
			      u32 क्रमmat)
अणु
	अगर (channel_select <= 7 && channel_select >= 0) अणु
		cx_ग_लिखो(dev->channels[channel_select].sram_channels->pix_frmt,
				क्रमmat);
	पूर्ण
	dev->channels[channel_select].pixel_क्रमmats = क्रमmat;
पूर्ण

अटल व्योम cx25821_set_vip_mode(काष्ठा cx25821_dev *dev,
				 स्थिर काष्ठा sram_channel *ch)
अणु
	cx_ग_लिखो(ch->pix_frmt, PIXEL_FRMT_422);
	cx_ग_लिखो(ch->vip_ctl, PIXEL_ENGINE_VIP1);
पूर्ण

अटल व्योम cx25821_initialize(काष्ठा cx25821_dev *dev)
अणु
	पूर्णांक i;

	dprपूर्णांकk(1, "%s()\n", __func__);

	cx25821_shutकरोwn(dev);
	cx_ग_लिखो(PCI_INT_STAT, 0xffffffff);

	क्रम (i = 0; i < VID_CHANNEL_NUM; i++)
		cx_ग_लिखो(dev->channels[i].sram_channels->पूर्णांक_stat, 0xffffffff);

	cx_ग_लिखो(AUD_A_INT_STAT, 0xffffffff);
	cx_ग_लिखो(AUD_B_INT_STAT, 0xffffffff);
	cx_ग_लिखो(AUD_C_INT_STAT, 0xffffffff);
	cx_ग_लिखो(AUD_D_INT_STAT, 0xffffffff);
	cx_ग_लिखो(AUD_E_INT_STAT, 0xffffffff);

	cx_ग_लिखो(CLK_DELAY, cx_पढ़ो(CLK_DELAY) & 0x80000000);
	cx_ग_लिखो(PAD_CTRL, 0x12);	/* क्रम I2C */
	cx25821_रेजिस्टरs_init(dev);	/* init Pecos रेजिस्टरs */
	msleep(100);

	क्रम (i = 0; i < VID_CHANNEL_NUM; i++) अणु
		cx25821_set_vip_mode(dev, dev->channels[i].sram_channels);
		cx25821_sram_channel_setup(dev, dev->channels[i].sram_channels,
						1440, 0);
		dev->channels[i].pixel_क्रमmats = PIXEL_FRMT_422;
		dev->channels[i].use_cअगर_resolution = 0;
	पूर्ण

	/* Probably only affect Downstream */
	क्रम (i = VID_UPSTREAM_SRAM_CHANNEL_I;
		i <= VID_UPSTREAM_SRAM_CHANNEL_J; i++) अणु
		dev->channels[i].pixel_क्रमmats = PIXEL_FRMT_422;
		cx25821_set_vip_mode(dev, dev->channels[i].sram_channels);
	पूर्ण

	cx25821_sram_channel_setup_audio(dev,
			dev->channels[SRAM_CH08].sram_channels, 128, 0);

	cx25821_gpio_init(dev);
पूर्ण

अटल पूर्णांक cx25821_get_resources(काष्ठा cx25821_dev *dev)
अणु
	अगर (request_mem_region(pci_resource_start(dev->pci, 0),
				pci_resource_len(dev->pci, 0), dev->name))
		वापस 0;

	pr_err("%s: can't get MMIO memory @ 0x%llx\n",
		dev->name, (अचिन्हित दीर्घ दीर्घ)pci_resource_start(dev->pci, 0));

	वापस -EBUSY;
पूर्ण

अटल व्योम cx25821_dev_checkrevision(काष्ठा cx25821_dev *dev)
अणु
	dev->hwrevision = cx_पढ़ो(RDR_CFG2) & 0xff;

	pr_info("Hardware revision = 0x%02x\n", dev->hwrevision);
पूर्ण

अटल व्योम cx25821_iounmap(काष्ठा cx25821_dev *dev)
अणु
	अगर (dev == शून्य)
		वापस;

	/* Releasing IO memory */
	अगर (dev->lmmio != शून्य) अणु
		iounmap(dev->lmmio);
		dev->lmmio = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक cx25821_dev_setup(काष्ठा cx25821_dev *dev)
अणु
	अटल अचिन्हित पूर्णांक cx25821_devcount;
	पूर्णांक i;

	mutex_init(&dev->lock);

	dev->nr = ++cx25821_devcount;
	प्र_लिखो(dev->name, "cx25821[%d]", dev->nr);

	अगर (dev->nr >= ARRAY_SIZE(card)) अणु
		CX25821_INFO("dev->nr >= %zd", ARRAY_SIZE(card));
		वापस -ENODEV;
	पूर्ण
	अगर (dev->pci->device != 0x8210) अणु
		pr_info("%s(): Exiting. Incorrect Hardware device = 0x%02x\n",
			__func__, dev->pci->device);
		वापस -ENODEV;
	पूर्ण
	pr_info("Athena Hardware device = 0x%02x\n", dev->pci->device);

	/* Apply a sensible घड़ी frequency क्रम the PCIe bridge */
	dev->clk_freq = 28000000;
	क्रम (i = 0; i < MAX_VID_CHANNEL_NUM; i++) अणु
		dev->channels[i].dev = dev;
		dev->channels[i].id = i;
		dev->channels[i].sram_channels = &cx25821_sram_channels[i];
	पूर्ण

	/* board config */
	dev->board = 1;		/* card[dev->nr]; */
	dev->_max_num_decoders = MAX_DECODERS;

	dev->pci_bus = dev->pci->bus->number;
	dev->pci_slot = PCI_SLOT(dev->pci->devfn);
	dev->pci_irqmask = 0x001f00;

	/* External Master 1 Bus */
	dev->i2c_bus[0].nr = 0;
	dev->i2c_bus[0].dev = dev;
	dev->i2c_bus[0].reg_stat = I2C1_STAT;
	dev->i2c_bus[0].reg_ctrl = I2C1_CTRL;
	dev->i2c_bus[0].reg_addr = I2C1_ADDR;
	dev->i2c_bus[0].reg_rdata = I2C1_RDATA;
	dev->i2c_bus[0].reg_wdata = I2C1_WDATA;
	dev->i2c_bus[0].i2c_period = (0x07 << 24);	/* 1.95MHz */

	अगर (cx25821_get_resources(dev) < 0) अणु
		pr_err("%s: No more PCIe resources for subsystem: %04x:%04x\n",
		       dev->name, dev->pci->subप्रणाली_venकरोr,
		       dev->pci->subप्रणाली_device);

		cx25821_devcount--;
		वापस -EBUSY;
	पूर्ण

	/* PCIe stuff */
	dev->base_io_addr = pci_resource_start(dev->pci, 0);

	अगर (!dev->base_io_addr) अणु
		CX25821_ERR("No PCI Memory resources, exiting!\n");
		वापस -ENODEV;
	पूर्ण

	dev->lmmio = ioremap(dev->base_io_addr, pci_resource_len(dev->pci, 0));

	अगर (!dev->lmmio) अणु
		CX25821_ERR("ioremap failed, maybe increasing __VMALLOC_RESERVE in page.h\n");
		cx25821_iounmap(dev);
		वापस -ENOMEM;
	पूर्ण

	dev->bmmio = (u8 __iomem *) dev->lmmio;

	pr_info("%s: subsystem: %04x:%04x, board: %s [card=%d,%s]\n",
		dev->name, dev->pci->subप्रणाली_venकरोr,
		dev->pci->subप्रणाली_device, cx25821_boards[dev->board].name,
		dev->board, card[dev->nr] == dev->board ?
		"insmod option" : "autodetected");

	/* init hardware */
	cx25821_initialize(dev);

	cx25821_i2c_रेजिस्टर(&dev->i2c_bus[0]);
/*  cx25821_i2c_रेजिस्टर(&dev->i2c_bus[1]);
 *  cx25821_i2c_रेजिस्टर(&dev->i2c_bus[2]); */

	अगर (medusa_video_init(dev) < 0)
		CX25821_ERR("%s(): Failed to initialize medusa!\n", __func__);

	cx25821_video_रेजिस्टर(dev);

	cx25821_dev_checkrevision(dev);
	वापस 0;
पूर्ण

व्योम cx25821_dev_unरेजिस्टर(काष्ठा cx25821_dev *dev)
अणु
	पूर्णांक i;

	अगर (!dev->base_io_addr)
		वापस;

	release_mem_region(dev->base_io_addr, pci_resource_len(dev->pci, 0));

	क्रम (i = 0; i < MAX_VID_CAP_CHANNEL_NUM - 1; i++) अणु
		अगर (i == SRAM_CH08) /* audio channel */
			जारी;
		/*
		 * TODO: enable when video output is properly
		 * supported.
		अगर (i == SRAM_CH09 || i == SRAM_CH10)
			cx25821_मुक्त_mem_upstream(&dev->channels[i]);
		 */
		cx25821_video_unरेजिस्टर(dev, i);
	पूर्ण

	cx25821_i2c_unरेजिस्टर(&dev->i2c_bus[0]);
	cx25821_iounmap(dev);
पूर्ण
EXPORT_SYMBOL(cx25821_dev_unरेजिस्टर);

पूर्णांक cx25821_riscmem_alloc(काष्ठा pci_dev *pci,
		       काष्ठा cx25821_riscmem *risc,
		       अचिन्हित पूर्णांक size)
अणु
	__le32 *cpu;
	dma_addr_t dma = 0;

	अगर (risc->cpu && risc->size < size) अणु
		dma_मुक्त_coherent(&pci->dev, risc->size, risc->cpu, risc->dma);
		risc->cpu = शून्य;
	पूर्ण
	अगर (शून्य == risc->cpu) अणु
		cpu = dma_alloc_coherent(&pci->dev, size, &dma, GFP_KERNEL);
		अगर (शून्य == cpu)
			वापस -ENOMEM;
		risc->cpu  = cpu;
		risc->dma  = dma;
		risc->size = size;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(cx25821_riscmem_alloc);

अटल __le32 *cx25821_risc_field(__le32 * rp, काष्ठा scatterlist *sglist,
				  अचिन्हित पूर्णांक offset, u32 sync_line,
				  अचिन्हित पूर्णांक bpl, अचिन्हित पूर्णांक padding,
				  अचिन्हित पूर्णांक lines, bool jump)
अणु
	काष्ठा scatterlist *sg;
	अचिन्हित पूर्णांक line, toकरो;

	अगर (jump) अणु
		*(rp++) = cpu_to_le32(RISC_JUMP);
		*(rp++) = cpu_to_le32(0);
		*(rp++) = cpu_to_le32(0); /* bits 63-32 */
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
		अगर (bpl <= sg_dma_len(sg) - offset) अणु
			/* fits पूर्णांकo current chunk */
			*(rp++) = cpu_to_le32(RISC_WRITE | RISC_SOL | RISC_EOL |
					bpl);
			*(rp++) = cpu_to_le32(sg_dma_address(sg) + offset);
			*(rp++) = cpu_to_le32(0);	/* bits 63-32 */
			offset += bpl;
		पूर्ण अन्यथा अणु
			/* scanline needs to be split */
			toकरो = bpl;
			*(rp++) = cpu_to_le32(RISC_WRITE | RISC_SOL |
					(sg_dma_len(sg) - offset));
			*(rp++) = cpu_to_le32(sg_dma_address(sg) + offset);
			*(rp++) = cpu_to_le32(0);	/* bits 63-32 */
			toकरो -= (sg_dma_len(sg) - offset);
			offset = 0;
			sg = sg_next(sg);
			जबतक (toकरो > sg_dma_len(sg)) अणु
				*(rp++) = cpu_to_le32(RISC_WRITE |
						sg_dma_len(sg));
				*(rp++) = cpu_to_le32(sg_dma_address(sg));
				*(rp++) = cpu_to_le32(0);	/* bits 63-32 */
				toकरो -= sg_dma_len(sg);
				sg = sg_next(sg);
			पूर्ण
			*(rp++) = cpu_to_le32(RISC_WRITE | RISC_EOL | toकरो);
			*(rp++) = cpu_to_le32(sg_dma_address(sg));
			*(rp++) = cpu_to_le32(0);	/* bits 63-32 */
			offset += toकरो;
		पूर्ण

		offset += padding;
	पूर्ण

	वापस rp;
पूर्ण

पूर्णांक cx25821_risc_buffer(काष्ठा pci_dev *pci, काष्ठा cx25821_riscmem *risc,
			काष्ठा scatterlist *sglist, अचिन्हित पूर्णांक top_offset,
			अचिन्हित पूर्णांक bottom_offset, अचिन्हित पूर्णांक bpl,
			अचिन्हित पूर्णांक padding, अचिन्हित पूर्णांक lines)
अणु
	u32 inकाष्ठाions;
	u32 fields;
	__le32 *rp;
	पूर्णांक rc;

	fields = 0;
	अगर (UNSET != top_offset)
		fields++;
	अगर (UNSET != bottom_offset)
		fields++;

	/* estimate risc mem: worst हाल is one ग_लिखो per page border +
	   one ग_लिखो per scan line + syncs + jump (all 3 dwords).  Padding
	   can cause next bpl to start बंद to a page border.  First DMA
	   region may be smaller than PAGE_SIZE */
	/* ग_लिखो and jump need and extra dword */
	inकाष्ठाions = fields * (1 + ((bpl + padding) * lines) / PAGE_SIZE +
			lines);
	inकाष्ठाions += 5;
	rc = cx25821_riscmem_alloc(pci, risc, inकाष्ठाions * 12);

	अगर (rc < 0)
		वापस rc;

	/* ग_लिखो risc inकाष्ठाions */
	rp = risc->cpu;

	अगर (UNSET != top_offset) अणु
		rp = cx25821_risc_field(rp, sglist, top_offset, 0, bpl, padding,
					lines, true);
	पूर्ण

	अगर (UNSET != bottom_offset) अणु
		rp = cx25821_risc_field(rp, sglist, bottom_offset, 0x200, bpl,
					padding, lines, UNSET == top_offset);
	पूर्ण

	/* save poपूर्णांकer to jmp inकाष्ठाion address */
	risc->jmp = rp;
	BUG_ON((risc->jmp - risc->cpu + 3) * माप(*risc->cpu) > risc->size);

	वापस 0;
पूर्ण

अटल __le32 *cx25821_risc_field_audio(__le32 * rp, काष्ठा scatterlist *sglist,
					अचिन्हित पूर्णांक offset, u32 sync_line,
					अचिन्हित पूर्णांक bpl, अचिन्हित पूर्णांक padding,
					अचिन्हित पूर्णांक lines, अचिन्हित पूर्णांक lpi)
अणु
	काष्ठा scatterlist *sg;
	अचिन्हित पूर्णांक line, toकरो, sol;

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
			*(rp++) = cpu_to_le32(RISC_WRITE | sol | RISC_EOL |
					bpl);
			*(rp++) = cpu_to_le32(sg_dma_address(sg) + offset);
			*(rp++) = cpu_to_le32(0);	/* bits 63-32 */
			offset += bpl;
		पूर्ण अन्यथा अणु
			/* scanline needs to be split */
			toकरो = bpl;
			*(rp++) = cpu_to_le32(RISC_WRITE | sol |
					(sg_dma_len(sg) - offset));
			*(rp++) = cpu_to_le32(sg_dma_address(sg) + offset);
			*(rp++) = cpu_to_le32(0);	/* bits 63-32 */
			toकरो -= (sg_dma_len(sg) - offset);
			offset = 0;
			sg = sg_next(sg);
			जबतक (toकरो > sg_dma_len(sg)) अणु
				*(rp++) = cpu_to_le32(RISC_WRITE |
						sg_dma_len(sg));
				*(rp++) = cpu_to_le32(sg_dma_address(sg));
				*(rp++) = cpu_to_le32(0);	/* bits 63-32 */
				toकरो -= sg_dma_len(sg);
				sg = sg_next(sg);
			पूर्ण
			*(rp++) = cpu_to_le32(RISC_WRITE | RISC_EOL | toकरो);
			*(rp++) = cpu_to_le32(sg_dma_address(sg));
			*(rp++) = cpu_to_le32(0);	/* bits 63-32 */
			offset += toकरो;
		पूर्ण
		offset += padding;
	पूर्ण

	वापस rp;
पूर्ण

पूर्णांक cx25821_risc_databuffer_audio(काष्ठा pci_dev *pci,
				  काष्ठा cx25821_riscmem *risc,
				  काष्ठा scatterlist *sglist,
				  अचिन्हित पूर्णांक bpl,
				  अचिन्हित पूर्णांक lines, अचिन्हित पूर्णांक lpi)
अणु
	u32 inकाष्ठाions;
	__le32 *rp;
	पूर्णांक rc;

	/* estimate risc mem: worst हाल is one ग_लिखो per page border +
	   one ग_लिखो per scan line + syncs + jump (all 2 dwords).  Here
	   there is no padding and no sync.  First DMA region may be smaller
	   than PAGE_SIZE */
	/* Jump and ग_लिखो need an extra dword */
	inकाष्ठाions = 1 + (bpl * lines) / PAGE_SIZE + lines;
	inकाष्ठाions += 1;

	rc = cx25821_riscmem_alloc(pci, risc, inकाष्ठाions * 12);
	अगर (rc < 0)
		वापस rc;

	/* ग_लिखो risc inकाष्ठाions */
	rp = risc->cpu;
	rp = cx25821_risc_field_audio(rp, sglist, 0, NO_SYNC_LINE, bpl, 0,
				      lines, lpi);

	/* save poपूर्णांकer to jmp inकाष्ठाion address */
	risc->jmp = rp;
	BUG_ON((risc->jmp - risc->cpu + 2) * माप(*risc->cpu) > risc->size);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(cx25821_risc_databuffer_audio);

व्योम cx25821_मुक्त_buffer(काष्ठा cx25821_dev *dev, काष्ठा cx25821_buffer *buf)
अणु
	अगर (WARN_ON(buf->risc.size == 0))
		वापस;
	dma_मुक्त_coherent(&dev->pci->dev, buf->risc.size, buf->risc.cpu,
			  buf->risc.dma);
	स_रखो(&buf->risc, 0, माप(buf->risc));
पूर्ण

अटल irqवापस_t cx25821_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा cx25821_dev *dev = dev_id;
	u32 pci_status;
	u32 vid_status;
	पूर्णांक i, handled = 0;
	u32 mask[8] = अणु 1, 2, 4, 8, 16, 32, 64, 128 पूर्ण;

	pci_status = cx_पढ़ो(PCI_INT_STAT);

	अगर (pci_status == 0)
		जाओ out;

	क्रम (i = 0; i < VID_CHANNEL_NUM; i++) अणु
		अगर (pci_status & mask[i]) अणु
			vid_status = cx_पढ़ो(dev->channels[i].
				sram_channels->पूर्णांक_stat);

			अगर (vid_status)
				handled += cx25821_video_irq(dev, i,
						vid_status);

			cx_ग_लिखो(PCI_INT_STAT, mask[i]);
		पूर्ण
	पूर्ण

out:
	वापस IRQ_RETVAL(handled);
पूर्ण

व्योम cx25821_prपूर्णांक_irqbits(अक्षर *name, अक्षर *tag, अक्षर **strings,
			   पूर्णांक len, u32 bits, u32 mask)
अणु
	अचिन्हित पूर्णांक i;

	prपूर्णांकk(KERN_DEBUG pr_fmt("%s: %s [0x%x]"), name, tag, bits);

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
EXPORT_SYMBOL(cx25821_prपूर्णांक_irqbits);

काष्ठा cx25821_dev *cx25821_dev_get(काष्ठा pci_dev *pci)
अणु
	काष्ठा cx25821_dev *dev = pci_get_drvdata(pci);
	वापस dev;
पूर्ण
EXPORT_SYMBOL(cx25821_dev_get);

अटल पूर्णांक cx25821_initdev(काष्ठा pci_dev *pci_dev,
			   स्थिर काष्ठा pci_device_id *pci_id)
अणु
	काष्ठा cx25821_dev *dev;
	पूर्णांक err = 0;

	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (शून्य == dev)
		वापस -ENOMEM;

	err = v4l2_device_रेजिस्टर(&pci_dev->dev, &dev->v4l2_dev);
	अगर (err < 0)
		जाओ fail_मुक्त;

	/* pci init */
	dev->pci = pci_dev;
	अगर (pci_enable_device(pci_dev)) अणु
		err = -EIO;

		pr_info("pci enable failed!\n");

		जाओ fail_unरेजिस्टर_device;
	पूर्ण

	err = cx25821_dev_setup(dev);
	अगर (err)
		जाओ fail_unरेजिस्टर_pci;

	/* prपूर्णांक pci info */
	pci_पढ़ो_config_byte(pci_dev, PCI_CLASS_REVISION, &dev->pci_rev);
	pci_पढ़ो_config_byte(pci_dev, PCI_LATENCY_TIMER, &dev->pci_lat);
	pr_info("%s/0: found at %s, rev: %d, irq: %d, latency: %d, mmio: 0x%llx\n",
		dev->name, pci_name(pci_dev), dev->pci_rev, pci_dev->irq,
		dev->pci_lat, (अचिन्हित दीर्घ दीर्घ)dev->base_io_addr);

	pci_set_master(pci_dev);
	err = dma_set_mask(&pci_dev->dev, 0xffffffff);
	अगर (err) अणु
		pr_err("%s/0: Oops: no 32bit PCI DMA ???\n", dev->name);
		err = -EIO;
		जाओ fail_irq;
	पूर्ण

	err = request_irq(pci_dev->irq, cx25821_irq,
			IRQF_SHARED, dev->name, dev);

	अगर (err < 0) अणु
		pr_err("%s: can't get IRQ %d\n", dev->name, pci_dev->irq);
		जाओ fail_irq;
	पूर्ण

	वापस 0;

fail_irq:
	pr_info("cx25821_initdev() can't get IRQ !\n");
	cx25821_dev_unरेजिस्टर(dev);

fail_unरेजिस्टर_pci:
	pci_disable_device(pci_dev);
fail_unरेजिस्टर_device:
	v4l2_device_unरेजिस्टर(&dev->v4l2_dev);

fail_मुक्त:
	kमुक्त(dev);
	वापस err;
पूर्ण

अटल व्योम cx25821_finidev(काष्ठा pci_dev *pci_dev)
अणु
	काष्ठा v4l2_device *v4l2_dev = pci_get_drvdata(pci_dev);
	काष्ठा cx25821_dev *dev = get_cx25821(v4l2_dev);

	cx25821_shutकरोwn(dev);
	pci_disable_device(pci_dev);

	/* unरेजिस्टर stuff */
	अगर (pci_dev->irq)
		मुक्त_irq(pci_dev->irq, dev);

	cx25821_dev_unरेजिस्टर(dev);
	v4l2_device_unरेजिस्टर(v4l2_dev);
	kमुक्त(dev);
पूर्ण

अटल स्थिर काष्ठा pci_device_id cx25821_pci_tbl[] = अणु
	अणु
		/* CX25821 Athena */
		.venकरोr = 0x14f1,
		.device = 0x8210,
		.subvenकरोr = 0x14f1,
		.subdevice = 0x0920,
	पूर्ण, अणु
		/* CX25821 No Bअक्रम */
		.venकरोr = 0x14f1,
		.device = 0x8210,
		.subvenकरोr = 0x0000,
		.subdevice = 0x0000,
	पूर्ण, अणु
		/* --- end of list --- */
	पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, cx25821_pci_tbl);

अटल काष्ठा pci_driver cx25821_pci_driver = अणु
	.name = "cx25821",
	.id_table = cx25821_pci_tbl,
	.probe = cx25821_initdev,
	.हटाओ = cx25821_finidev,
पूर्ण;

अटल पूर्णांक __init cx25821_init(व्योम)
अणु
	pr_info("driver loaded\n");
	वापस pci_रेजिस्टर_driver(&cx25821_pci_driver);
पूर्ण

अटल व्योम __निकास cx25821_fini(व्योम)
अणु
	pci_unरेजिस्टर_driver(&cx25821_pci_driver);
पूर्ण

module_init(cx25821_init);
module_निकास(cx25821_fini);
