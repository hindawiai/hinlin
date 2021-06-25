<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ti_hdmi_4xxx_ip.c
 *
 * HDMI TI81xx, TI38xx, TI OMAP4 etc IP driver Library
 * Copyright (C) 2010-2011 Texas Instruments Incorporated - https://www.ti.com/
 * Authors: Yong Zhi
 *	Mythri pk <mythripk@ti.com>
 */

#घोषणा DSS_SUBSYS_NAME "HDMICORE"

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mutex.h>
#समावेश <linux/delay.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/माला.स>
#समावेश <linux/seq_file.h>
#समावेश <sound/asound.h>
#समावेश <sound/asoundef.h>

#समावेश "hdmi4_core.h"
#समावेश "dss_features.h"

#घोषणा HDMI_CORE_AV		0x500

अटल अंतरभूत व्योम __iomem *hdmi_av_base(काष्ठा hdmi_core_data *core)
अणु
	वापस core->base + HDMI_CORE_AV;
पूर्ण

अटल पूर्णांक hdmi_core_ddc_init(काष्ठा hdmi_core_data *core)
अणु
	व्योम __iomem *base = core->base;

	/* Turn on CLK क्रम DDC */
	REG_FLD_MOD(base, HDMI_CORE_AV_DPD, 0x7, 2, 0);

	/* IN_PROG */
	अगर (REG_GET(base, HDMI_CORE_DDC_STATUS, 4, 4) == 1) अणु
		/* Abort transaction */
		REG_FLD_MOD(base, HDMI_CORE_DDC_CMD, 0xf, 3, 0);
		/* IN_PROG */
		अगर (hdmi_रुको_क्रम_bit_change(base, HDMI_CORE_DDC_STATUS,
					4, 4, 0) != 0) अणु
			DSSERR("Timeout aborting DDC transaction\n");
			वापस -ETIMEDOUT;
		पूर्ण
	पूर्ण

	/* Clk SCL Devices */
	REG_FLD_MOD(base, HDMI_CORE_DDC_CMD, 0xA, 3, 0);

	/* HDMI_CORE_DDC_STATUS_IN_PROG */
	अगर (hdmi_रुको_क्रम_bit_change(base, HDMI_CORE_DDC_STATUS,
				4, 4, 0) != 0) अणु
		DSSERR("Timeout starting SCL clock\n");
		वापस -ETIMEDOUT;
	पूर्ण

	/* Clear FIFO */
	REG_FLD_MOD(base, HDMI_CORE_DDC_CMD, 0x9, 3, 0);

	/* HDMI_CORE_DDC_STATUS_IN_PROG */
	अगर (hdmi_रुको_क्रम_bit_change(base, HDMI_CORE_DDC_STATUS,
				4, 4, 0) != 0) अणु
		DSSERR("Timeout clearing DDC fifo\n");
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hdmi_core_ddc_edid(काष्ठा hdmi_core_data *core,
		u8 *pedid, पूर्णांक ext)
अणु
	व्योम __iomem *base = core->base;
	u32 i;
	अक्षर checksum;
	u32 offset = 0;

	/* HDMI_CORE_DDC_STATUS_IN_PROG */
	अगर (hdmi_रुको_क्रम_bit_change(base, HDMI_CORE_DDC_STATUS,
				4, 4, 0) != 0) अणु
		DSSERR("Timeout waiting DDC to be ready\n");
		वापस -ETIMEDOUT;
	पूर्ण

	अगर (ext % 2 != 0)
		offset = 0x80;

	/* Load Segment Address Register */
	REG_FLD_MOD(base, HDMI_CORE_DDC_SEGM, ext / 2, 7, 0);

	/* Load Slave Address Register */
	REG_FLD_MOD(base, HDMI_CORE_DDC_ADDR, 0xA0 >> 1, 7, 1);

	/* Load Offset Address Register */
	REG_FLD_MOD(base, HDMI_CORE_DDC_OFFSET, offset, 7, 0);

	/* Load Byte Count */
	REG_FLD_MOD(base, HDMI_CORE_DDC_COUNT1, 0x80, 7, 0);
	REG_FLD_MOD(base, HDMI_CORE_DDC_COUNT2, 0x0, 1, 0);

	/* Set DDC_CMD */
	अगर (ext)
		REG_FLD_MOD(base, HDMI_CORE_DDC_CMD, 0x4, 3, 0);
	अन्यथा
		REG_FLD_MOD(base, HDMI_CORE_DDC_CMD, 0x2, 3, 0);

	/* HDMI_CORE_DDC_STATUS_BUS_LOW */
	अगर (REG_GET(base, HDMI_CORE_DDC_STATUS, 6, 6) == 1) अणु
		DSSERR("I2C Bus Low?\n");
		वापस -EIO;
	पूर्ण
	/* HDMI_CORE_DDC_STATUS_NO_ACK */
	अगर (REG_GET(base, HDMI_CORE_DDC_STATUS, 5, 5) == 1) अणु
		DSSERR("I2C No Ack\n");
		वापस -EIO;
	पूर्ण

	क्रम (i = 0; i < 0x80; ++i) अणु
		पूर्णांक t;

		/* IN_PROG */
		अगर (REG_GET(base, HDMI_CORE_DDC_STATUS, 4, 4) == 0) अणु
			DSSERR("operation stopped when reading edid\n");
			वापस -EIO;
		पूर्ण

		t = 0;
		/* FIFO_EMPTY */
		जबतक (REG_GET(base, HDMI_CORE_DDC_STATUS, 2, 2) == 1) अणु
			अगर (t++ > 10000) अणु
				DSSERR("timeout reading edid\n");
				वापस -ETIMEDOUT;
			पूर्ण
			udelay(1);
		पूर्ण

		pedid[i] = REG_GET(base, HDMI_CORE_DDC_DATA, 7, 0);
	पूर्ण

	checksum = 0;
	क्रम (i = 0; i < 0x80; ++i)
		checksum += pedid[i];

	अगर (checksum != 0) अणु
		DSSERR("E-EDID checksum failed!!\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक hdmi4_पढ़ो_edid(काष्ठा hdmi_core_data *core, u8 *edid, पूर्णांक len)
अणु
	पूर्णांक r, l;

	अगर (len < 128)
		वापस -EINVAL;

	r = hdmi_core_ddc_init(core);
	अगर (r)
		वापस r;

	r = hdmi_core_ddc_edid(core, edid, 0);
	अगर (r)
		वापस r;

	l = 128;

	अगर (len >= 128 * 2 && edid[0x7e] > 0) अणु
		r = hdmi_core_ddc_edid(core, edid + 0x80, 1);
		अगर (r)
			वापस r;
		l += 128;
	पूर्ण

	वापस l;
पूर्ण

अटल व्योम hdmi_core_init(काष्ठा hdmi_core_video_config *video_cfg)
अणु
	DSSDBG("Enter hdmi_core_init\n");

	/* video core */
	video_cfg->ip_bus_width = HDMI_INPUT_8BIT;
	video_cfg->op_dither_truc = HDMI_OUTPUTTRUNCATION_8BIT;
	video_cfg->deep_color_pkt = HDMI_DEEPCOLORPACKECTDISABLE;
	video_cfg->pkt_mode = HDMI_PACKETMODERESERVEDVALUE;
	video_cfg->hdmi_dvi = HDMI_DVI;
	video_cfg->tclk_sel_clkmult = HDMI_FPLL10IDCK;
पूर्ण

अटल व्योम hdmi_core_घातerकरोwn_disable(काष्ठा hdmi_core_data *core)
अणु
	DSSDBG("Enter hdmi_core_powerdown_disable\n");
	REG_FLD_MOD(core->base, HDMI_CORE_SYS_SYS_CTRL1, 0x0, 0, 0);
पूर्ण

अटल व्योम hdmi_core_swreset_release(काष्ठा hdmi_core_data *core)
अणु
	DSSDBG("Enter hdmi_core_swreset_release\n");
	REG_FLD_MOD(core->base, HDMI_CORE_SYS_SRST, 0x0, 0, 0);
पूर्ण

अटल व्योम hdmi_core_swreset_निश्चित(काष्ठा hdmi_core_data *core)
अणु
	DSSDBG("Enter hdmi_core_swreset_assert\n");
	REG_FLD_MOD(core->base, HDMI_CORE_SYS_SRST, 0x1, 0, 0);
पूर्ण

/* HDMI_CORE_VIDEO_CONFIG */
अटल व्योम hdmi_core_video_config(काष्ठा hdmi_core_data *core,
				काष्ठा hdmi_core_video_config *cfg)
अणु
	u32 r = 0;
	व्योम __iomem *core_sys_base = core->base;
	व्योम __iomem *core_av_base = hdmi_av_base(core);

	/* sys_ctrl1 शेष configuration not tunable */
	r = hdmi_पढ़ो_reg(core_sys_base, HDMI_CORE_SYS_SYS_CTRL1);
	r = FLD_MOD(r, HDMI_CORE_SYS_SYS_CTRL1_VEN_FOLLOWVSYNC, 5, 5);
	r = FLD_MOD(r, HDMI_CORE_SYS_SYS_CTRL1_HEN_FOLLOWHSYNC, 4, 4);
	r = FLD_MOD(r, HDMI_CORE_SYS_SYS_CTRL1_BSEL_24BITBUS, 2, 2);
	r = FLD_MOD(r, HDMI_CORE_SYS_SYS_CTRL1_EDGE_RISINGEDGE, 1, 1);
	hdmi_ग_लिखो_reg(core_sys_base, HDMI_CORE_SYS_SYS_CTRL1, r);

	REG_FLD_MOD(core_sys_base,
			HDMI_CORE_SYS_VID_ACEN, cfg->ip_bus_width, 7, 6);

	/* Vid_Mode */
	r = hdmi_पढ़ो_reg(core_sys_base, HDMI_CORE_SYS_VID_MODE);

	/* dither truncation configuration */
	अगर (cfg->op_dither_truc > HDMI_OUTPUTTRUNCATION_12BIT) अणु
		r = FLD_MOD(r, cfg->op_dither_truc - 3, 7, 6);
		r = FLD_MOD(r, 1, 5, 5);
	पूर्ण अन्यथा अणु
		r = FLD_MOD(r, cfg->op_dither_truc, 7, 6);
		r = FLD_MOD(r, 0, 5, 5);
	पूर्ण
	hdmi_ग_लिखो_reg(core_sys_base, HDMI_CORE_SYS_VID_MODE, r);

	/* HDMI_Ctrl */
	r = hdmi_पढ़ो_reg(core_av_base, HDMI_CORE_AV_HDMI_CTRL);
	r = FLD_MOD(r, cfg->deep_color_pkt, 6, 6);
	r = FLD_MOD(r, cfg->pkt_mode, 5, 3);
	r = FLD_MOD(r, cfg->hdmi_dvi, 0, 0);
	hdmi_ग_लिखो_reg(core_av_base, HDMI_CORE_AV_HDMI_CTRL, r);

	/* TMDS_CTRL */
	REG_FLD_MOD(core_sys_base,
			HDMI_CORE_SYS_TMDS_CTRL, cfg->tclk_sel_clkmult, 6, 5);
पूर्ण

अटल व्योम hdmi_core_ग_लिखो_avi_infoframe(काष्ठा hdmi_core_data *core,
	काष्ठा hdmi_avi_infoframe *frame)
अणु
	व्योम __iomem *av_base = hdmi_av_base(core);
	u8 data[HDMI_INFOFRAME_SIZE(AVI)];
	पूर्णांक i;

	hdmi_avi_infoframe_pack(frame, data, माप(data));

	prपूर्णांक_hex_dump_debug("AVI: ", DUMP_PREFIX_NONE, 16, 1, data,
		HDMI_INFOFRAME_SIZE(AVI), false);

	क्रम (i = 0; i < माप(data); ++i) अणु
		hdmi_ग_लिखो_reg(av_base, HDMI_CORE_AV_AVI_BASE + i * 4,
			data[i]);
	पूर्ण
पूर्ण

अटल व्योम hdmi_core_av_packet_config(काष्ठा hdmi_core_data *core,
		काष्ठा hdmi_core_packet_enable_repeat repeat_cfg)
अणु
	/* enable/repeat the infoframe */
	hdmi_ग_लिखो_reg(hdmi_av_base(core), HDMI_CORE_AV_PB_CTRL1,
		(repeat_cfg.audio_pkt << 5) |
		(repeat_cfg.audio_pkt_repeat << 4) |
		(repeat_cfg.avi_infoframe << 1) |
		(repeat_cfg.avi_infoframe_repeat));

	/* enable/repeat the packet */
	hdmi_ग_लिखो_reg(hdmi_av_base(core), HDMI_CORE_AV_PB_CTRL2,
		(repeat_cfg.gen_cntrl_pkt << 3) |
		(repeat_cfg.gen_cntrl_pkt_repeat << 2) |
		(repeat_cfg.generic_pkt << 1) |
		(repeat_cfg.generic_pkt_repeat));
पूर्ण

व्योम hdmi4_configure(काष्ठा hdmi_core_data *core,
	काष्ठा hdmi_wp_data *wp, काष्ठा hdmi_config *cfg)
अणु
	/* HDMI */
	काष्ठा omap_video_timings video_timing;
	काष्ठा hdmi_video_क्रमmat video_क्रमmat;
	/* HDMI core */
	काष्ठा hdmi_core_video_config v_core_cfg;
	काष्ठा hdmi_core_packet_enable_repeat repeat_cfg = अणु 0 पूर्ण;

	hdmi_core_init(&v_core_cfg);

	hdmi_wp_init_vid_fmt_timings(&video_क्रमmat, &video_timing, cfg);

	hdmi_wp_video_config_timing(wp, &video_timing);

	/* video config */
	video_क्रमmat.packing_mode = HDMI_PACK_24b_RGB_YUV444_YUV422;

	hdmi_wp_video_config_क्रमmat(wp, &video_क्रमmat);

	hdmi_wp_video_config_पूर्णांकerface(wp, &video_timing);

	/*
	 * configure core video part
	 * set software reset in the core
	 */
	hdmi_core_swreset_निश्चित(core);

	/* घातer करोwn off */
	hdmi_core_घातerकरोwn_disable(core);

	v_core_cfg.pkt_mode = HDMI_PACKETMODE24BITPERPIXEL;
	v_core_cfg.hdmi_dvi = cfg->hdmi_dvi_mode;

	hdmi_core_video_config(core, &v_core_cfg);

	/* release software reset in the core */
	hdmi_core_swreset_release(core);

	अगर (cfg->hdmi_dvi_mode == HDMI_HDMI) अणु
		hdmi_core_ग_लिखो_avi_infoframe(core, &cfg->infoframe);

		/* enable/repeat the infoframe */
		repeat_cfg.avi_infoframe = HDMI_PACKETENABLE;
		repeat_cfg.avi_infoframe_repeat = HDMI_PACKETREPEATON;
		/* wakeup */
		repeat_cfg.audio_pkt = HDMI_PACKETENABLE;
		repeat_cfg.audio_pkt_repeat = HDMI_PACKETREPEATON;
	पूर्ण

	hdmi_core_av_packet_config(core, repeat_cfg);
पूर्ण

व्योम hdmi4_core_dump(काष्ठा hdmi_core_data *core, काष्ठा seq_file *s)
अणु
	पूर्णांक i;

#घोषणा CORE_REG(i, name) name(i)
#घोषणा DUMPCORE(r) seq_म_लिखो(s, "%-35s %08x\n", #r,\
		hdmi_पढ़ो_reg(core->base, r))
#घोषणा DUMPCOREAV(r) seq_म_लिखो(s, "%-35s %08x\n", #r,\
		hdmi_पढ़ो_reg(hdmi_av_base(core), r))
#घोषणा DUMPCOREAV2(i, r) seq_म_लिखो(s, "%s[%d]%*s %08x\n", #r, i, \
		(i < 10) ? 32 - (पूर्णांक)म_माप(#r) : 31 - (पूर्णांक)म_माप(#r), " ", \
		hdmi_पढ़ो_reg(hdmi_av_base(core), CORE_REG(i, r)))

	DUMPCORE(HDMI_CORE_SYS_VND_IDL);
	DUMPCORE(HDMI_CORE_SYS_DEV_IDL);
	DUMPCORE(HDMI_CORE_SYS_DEV_IDH);
	DUMPCORE(HDMI_CORE_SYS_DEV_REV);
	DUMPCORE(HDMI_CORE_SYS_SRST);
	DUMPCORE(HDMI_CORE_SYS_SYS_CTRL1);
	DUMPCORE(HDMI_CORE_SYS_SYS_STAT);
	DUMPCORE(HDMI_CORE_SYS_SYS_CTRL3);
	DUMPCORE(HDMI_CORE_SYS_DE_DLY);
	DUMPCORE(HDMI_CORE_SYS_DE_CTRL);
	DUMPCORE(HDMI_CORE_SYS_DE_TOP);
	DUMPCORE(HDMI_CORE_SYS_DE_CNTL);
	DUMPCORE(HDMI_CORE_SYS_DE_CNTH);
	DUMPCORE(HDMI_CORE_SYS_DE_LINL);
	DUMPCORE(HDMI_CORE_SYS_DE_LINH_1);
	DUMPCORE(HDMI_CORE_SYS_HRES_L);
	DUMPCORE(HDMI_CORE_SYS_HRES_H);
	DUMPCORE(HDMI_CORE_SYS_VRES_L);
	DUMPCORE(HDMI_CORE_SYS_VRES_H);
	DUMPCORE(HDMI_CORE_SYS_IADJUST);
	DUMPCORE(HDMI_CORE_SYS_POLDETECT);
	DUMPCORE(HDMI_CORE_SYS_HWIDTH1);
	DUMPCORE(HDMI_CORE_SYS_HWIDTH2);
	DUMPCORE(HDMI_CORE_SYS_VWIDTH);
	DUMPCORE(HDMI_CORE_SYS_VID_CTRL);
	DUMPCORE(HDMI_CORE_SYS_VID_ACEN);
	DUMPCORE(HDMI_CORE_SYS_VID_MODE);
	DUMPCORE(HDMI_CORE_SYS_VID_BLANK1);
	DUMPCORE(HDMI_CORE_SYS_VID_BLANK3);
	DUMPCORE(HDMI_CORE_SYS_VID_BLANK1);
	DUMPCORE(HDMI_CORE_SYS_DC_HEADER);
	DUMPCORE(HDMI_CORE_SYS_VID_DITHER);
	DUMPCORE(HDMI_CORE_SYS_RGB2XVYCC_CT);
	DUMPCORE(HDMI_CORE_SYS_R2Y_COEFF_LOW);
	DUMPCORE(HDMI_CORE_SYS_R2Y_COEFF_UP);
	DUMPCORE(HDMI_CORE_SYS_G2Y_COEFF_LOW);
	DUMPCORE(HDMI_CORE_SYS_G2Y_COEFF_UP);
	DUMPCORE(HDMI_CORE_SYS_B2Y_COEFF_LOW);
	DUMPCORE(HDMI_CORE_SYS_B2Y_COEFF_UP);
	DUMPCORE(HDMI_CORE_SYS_R2CB_COEFF_LOW);
	DUMPCORE(HDMI_CORE_SYS_R2CB_COEFF_UP);
	DUMPCORE(HDMI_CORE_SYS_G2CB_COEFF_LOW);
	DUMPCORE(HDMI_CORE_SYS_G2CB_COEFF_UP);
	DUMPCORE(HDMI_CORE_SYS_B2CB_COEFF_LOW);
	DUMPCORE(HDMI_CORE_SYS_B2CB_COEFF_UP);
	DUMPCORE(HDMI_CORE_SYS_R2CR_COEFF_LOW);
	DUMPCORE(HDMI_CORE_SYS_R2CR_COEFF_UP);
	DUMPCORE(HDMI_CORE_SYS_G2CR_COEFF_LOW);
	DUMPCORE(HDMI_CORE_SYS_G2CR_COEFF_UP);
	DUMPCORE(HDMI_CORE_SYS_B2CR_COEFF_LOW);
	DUMPCORE(HDMI_CORE_SYS_B2CR_COEFF_UP);
	DUMPCORE(HDMI_CORE_SYS_RGB_OFFSET_LOW);
	DUMPCORE(HDMI_CORE_SYS_RGB_OFFSET_UP);
	DUMPCORE(HDMI_CORE_SYS_Y_OFFSET_LOW);
	DUMPCORE(HDMI_CORE_SYS_Y_OFFSET_UP);
	DUMPCORE(HDMI_CORE_SYS_CBCR_OFFSET_LOW);
	DUMPCORE(HDMI_CORE_SYS_CBCR_OFFSET_UP);
	DUMPCORE(HDMI_CORE_SYS_INTR_STATE);
	DUMPCORE(HDMI_CORE_SYS_INTR1);
	DUMPCORE(HDMI_CORE_SYS_INTR2);
	DUMPCORE(HDMI_CORE_SYS_INTR3);
	DUMPCORE(HDMI_CORE_SYS_INTR4);
	DUMPCORE(HDMI_CORE_SYS_INTR_UNMASK1);
	DUMPCORE(HDMI_CORE_SYS_INTR_UNMASK2);
	DUMPCORE(HDMI_CORE_SYS_INTR_UNMASK3);
	DUMPCORE(HDMI_CORE_SYS_INTR_UNMASK4);
	DUMPCORE(HDMI_CORE_SYS_INTR_CTRL);
	DUMPCORE(HDMI_CORE_SYS_TMDS_CTRL);

	DUMPCORE(HDMI_CORE_DDC_ADDR);
	DUMPCORE(HDMI_CORE_DDC_SEGM);
	DUMPCORE(HDMI_CORE_DDC_OFFSET);
	DUMPCORE(HDMI_CORE_DDC_COUNT1);
	DUMPCORE(HDMI_CORE_DDC_COUNT2);
	DUMPCORE(HDMI_CORE_DDC_STATUS);
	DUMPCORE(HDMI_CORE_DDC_CMD);
	DUMPCORE(HDMI_CORE_DDC_DATA);

	DUMPCOREAV(HDMI_CORE_AV_ACR_CTRL);
	DUMPCOREAV(HDMI_CORE_AV_FREQ_SVAL);
	DUMPCOREAV(HDMI_CORE_AV_N_SVAL1);
	DUMPCOREAV(HDMI_CORE_AV_N_SVAL2);
	DUMPCOREAV(HDMI_CORE_AV_N_SVAL3);
	DUMPCOREAV(HDMI_CORE_AV_CTS_SVAL1);
	DUMPCOREAV(HDMI_CORE_AV_CTS_SVAL2);
	DUMPCOREAV(HDMI_CORE_AV_CTS_SVAL3);
	DUMPCOREAV(HDMI_CORE_AV_CTS_HVAL1);
	DUMPCOREAV(HDMI_CORE_AV_CTS_HVAL2);
	DUMPCOREAV(HDMI_CORE_AV_CTS_HVAL3);
	DUMPCOREAV(HDMI_CORE_AV_AUD_MODE);
	DUMPCOREAV(HDMI_CORE_AV_SPDIF_CTRL);
	DUMPCOREAV(HDMI_CORE_AV_HW_SPDIF_FS);
	DUMPCOREAV(HDMI_CORE_AV_SWAP_I2S);
	DUMPCOREAV(HDMI_CORE_AV_SPDIF_ERTH);
	DUMPCOREAV(HDMI_CORE_AV_I2S_IN_MAP);
	DUMPCOREAV(HDMI_CORE_AV_I2S_IN_CTRL);
	DUMPCOREAV(HDMI_CORE_AV_I2S_CHST0);
	DUMPCOREAV(HDMI_CORE_AV_I2S_CHST1);
	DUMPCOREAV(HDMI_CORE_AV_I2S_CHST2);
	DUMPCOREAV(HDMI_CORE_AV_I2S_CHST4);
	DUMPCOREAV(HDMI_CORE_AV_I2S_CHST5);
	DUMPCOREAV(HDMI_CORE_AV_ASRC);
	DUMPCOREAV(HDMI_CORE_AV_I2S_IN_LEN);
	DUMPCOREAV(HDMI_CORE_AV_HDMI_CTRL);
	DUMPCOREAV(HDMI_CORE_AV_AUDO_TXSTAT);
	DUMPCOREAV(HDMI_CORE_AV_AUD_PAR_BUSCLK_1);
	DUMPCOREAV(HDMI_CORE_AV_AUD_PAR_BUSCLK_2);
	DUMPCOREAV(HDMI_CORE_AV_AUD_PAR_BUSCLK_3);
	DUMPCOREAV(HDMI_CORE_AV_TEST_TXCTRL);
	DUMPCOREAV(HDMI_CORE_AV_DPD);
	DUMPCOREAV(HDMI_CORE_AV_PB_CTRL1);
	DUMPCOREAV(HDMI_CORE_AV_PB_CTRL2);
	DUMPCOREAV(HDMI_CORE_AV_AVI_TYPE);
	DUMPCOREAV(HDMI_CORE_AV_AVI_VERS);
	DUMPCOREAV(HDMI_CORE_AV_AVI_LEN);
	DUMPCOREAV(HDMI_CORE_AV_AVI_CHSUM);

	क्रम (i = 0; i < HDMI_CORE_AV_AVI_DBYTE_NELEMS; i++)
		DUMPCOREAV2(i, HDMI_CORE_AV_AVI_DBYTE);

	DUMPCOREAV(HDMI_CORE_AV_SPD_TYPE);
	DUMPCOREAV(HDMI_CORE_AV_SPD_VERS);
	DUMPCOREAV(HDMI_CORE_AV_SPD_LEN);
	DUMPCOREAV(HDMI_CORE_AV_SPD_CHSUM);

	क्रम (i = 0; i < HDMI_CORE_AV_SPD_DBYTE_NELEMS; i++)
		DUMPCOREAV2(i, HDMI_CORE_AV_SPD_DBYTE);

	DUMPCOREAV(HDMI_CORE_AV_AUDIO_TYPE);
	DUMPCOREAV(HDMI_CORE_AV_AUDIO_VERS);
	DUMPCOREAV(HDMI_CORE_AV_AUDIO_LEN);
	DUMPCOREAV(HDMI_CORE_AV_AUDIO_CHSUM);

	क्रम (i = 0; i < HDMI_CORE_AV_AUD_DBYTE_NELEMS; i++)
		DUMPCOREAV2(i, HDMI_CORE_AV_AUD_DBYTE);

	DUMPCOREAV(HDMI_CORE_AV_MPEG_TYPE);
	DUMPCOREAV(HDMI_CORE_AV_MPEG_VERS);
	DUMPCOREAV(HDMI_CORE_AV_MPEG_LEN);
	DUMPCOREAV(HDMI_CORE_AV_MPEG_CHSUM);

	क्रम (i = 0; i < HDMI_CORE_AV_MPEG_DBYTE_NELEMS; i++)
		DUMPCOREAV2(i, HDMI_CORE_AV_MPEG_DBYTE);

	क्रम (i = 0; i < HDMI_CORE_AV_GEN_DBYTE_NELEMS; i++)
		DUMPCOREAV2(i, HDMI_CORE_AV_GEN_DBYTE);

	DUMPCOREAV(HDMI_CORE_AV_CP_BYTE1);

	क्रम (i = 0; i < HDMI_CORE_AV_GEN2_DBYTE_NELEMS; i++)
		DUMPCOREAV2(i, HDMI_CORE_AV_GEN2_DBYTE);

	DUMPCOREAV(HDMI_CORE_AV_CEC_ADDR_ID);
पूर्ण

अटल व्योम hdmi_core_audio_config(काष्ठा hdmi_core_data *core,
					काष्ठा hdmi_core_audio_config *cfg)
अणु
	u32 r;
	व्योम __iomem *av_base = hdmi_av_base(core);

	/*
	 * Parameters क्रम generation of Audio Clock Recovery packets
	 */
	REG_FLD_MOD(av_base, HDMI_CORE_AV_N_SVAL1, cfg->n, 7, 0);
	REG_FLD_MOD(av_base, HDMI_CORE_AV_N_SVAL2, cfg->n >> 8, 7, 0);
	REG_FLD_MOD(av_base, HDMI_CORE_AV_N_SVAL3, cfg->n >> 16, 7, 0);

	अगर (cfg->cts_mode == HDMI_AUDIO_CTS_MODE_SW) अणु
		REG_FLD_MOD(av_base, HDMI_CORE_AV_CTS_SVAL1, cfg->cts, 7, 0);
		REG_FLD_MOD(av_base,
				HDMI_CORE_AV_CTS_SVAL2, cfg->cts >> 8, 7, 0);
		REG_FLD_MOD(av_base,
				HDMI_CORE_AV_CTS_SVAL3, cfg->cts >> 16, 7, 0);
	पूर्ण अन्यथा अणु
		REG_FLD_MOD(av_base, HDMI_CORE_AV_AUD_PAR_BUSCLK_1,
				cfg->aud_par_busclk, 7, 0);
		REG_FLD_MOD(av_base, HDMI_CORE_AV_AUD_PAR_BUSCLK_2,
				(cfg->aud_par_busclk >> 8), 7, 0);
		REG_FLD_MOD(av_base, HDMI_CORE_AV_AUD_PAR_BUSCLK_3,
				(cfg->aud_par_busclk >> 16), 7, 0);
	पूर्ण

	/* Set ACR घड़ी भागisor */
	REG_FLD_MOD(av_base,
			HDMI_CORE_AV_FREQ_SVAL, cfg->mclk_mode, 2, 0);

	r = hdmi_पढ़ो_reg(av_base, HDMI_CORE_AV_ACR_CTRL);
	/*
	 * Use TMDS घड़ी क्रम ACR packets. For devices that use
	 * the MCLK, this is the first part of the MCLK initialization.
	 */
	r = FLD_MOD(r, 0, 2, 2);

	r = FLD_MOD(r, cfg->en_acr_pkt, 1, 1);
	r = FLD_MOD(r, cfg->cts_mode, 0, 0);
	hdmi_ग_लिखो_reg(av_base, HDMI_CORE_AV_ACR_CTRL, r);

	/* For devices using MCLK, this completes its initialization. */
	अगर (cfg->use_mclk)
		REG_FLD_MOD(av_base, HDMI_CORE_AV_ACR_CTRL, 1, 2, 2);

	/* Override of SPDIF sample frequency with value in I2S_CHST4 */
	REG_FLD_MOD(av_base, HDMI_CORE_AV_SPDIF_CTRL,
						cfg->fs_override, 1, 1);

	/*
	 * Set IEC-60958-3 channel status word. It is passed to the IP
	 * just as it is received. The user of the driver is responsible
	 * क्रम its contents.
	 */
	hdmi_ग_लिखो_reg(av_base, HDMI_CORE_AV_I2S_CHST0,
		       cfg->iec60958_cfg->status[0]);
	hdmi_ग_लिखो_reg(av_base, HDMI_CORE_AV_I2S_CHST1,
		       cfg->iec60958_cfg->status[1]);
	hdmi_ग_लिखो_reg(av_base, HDMI_CORE_AV_I2S_CHST2,
		       cfg->iec60958_cfg->status[2]);
	/* yes, this is correct: status[3] goes to CHST4 रेजिस्टर */
	hdmi_ग_लिखो_reg(av_base, HDMI_CORE_AV_I2S_CHST4,
		       cfg->iec60958_cfg->status[3]);
	/* yes, this is correct: status[4] goes to CHST5 रेजिस्टर */
	hdmi_ग_लिखो_reg(av_base, HDMI_CORE_AV_I2S_CHST5,
		       cfg->iec60958_cfg->status[4]);

	/* set I2S parameters */
	r = hdmi_पढ़ो_reg(av_base, HDMI_CORE_AV_I2S_IN_CTRL);
	r = FLD_MOD(r, cfg->i2s_cfg.sck_edge_mode, 6, 6);
	r = FLD_MOD(r, cfg->i2s_cfg.vbit, 4, 4);
	r = FLD_MOD(r, cfg->i2s_cfg.justअगरication, 2, 2);
	r = FLD_MOD(r, cfg->i2s_cfg.direction, 1, 1);
	r = FLD_MOD(r, cfg->i2s_cfg.shअगरt, 0, 0);
	hdmi_ग_लिखो_reg(av_base, HDMI_CORE_AV_I2S_IN_CTRL, r);

	REG_FLD_MOD(av_base, HDMI_CORE_AV_I2S_IN_LEN,
			cfg->i2s_cfg.in_length_bits, 3, 0);

	/* Audio channels and mode parameters */
	REG_FLD_MOD(av_base, HDMI_CORE_AV_HDMI_CTRL, cfg->layout, 2, 1);
	r = hdmi_पढ़ो_reg(av_base, HDMI_CORE_AV_AUD_MODE);
	r = FLD_MOD(r, cfg->i2s_cfg.active_sds, 7, 4);
	r = FLD_MOD(r, cfg->en_dsd_audio, 3, 3);
	r = FLD_MOD(r, cfg->en_parallel_aud_input, 2, 2);
	r = FLD_MOD(r, cfg->en_spdअगर, 1, 1);
	hdmi_ग_लिखो_reg(av_base, HDMI_CORE_AV_AUD_MODE, r);

	/* Audio channel mappings */
	/* TODO: Make channel mapping dynamic. For now, map channels
	 * in the ALSA order: FL/FR/RL/RR/C/LFE/SL/SR. Remapping is needed as
	 * HDMI speaker order is dअगरferent. See CEA-861 Section 6.6.2.
	 */
	hdmi_ग_लिखो_reg(av_base, HDMI_CORE_AV_I2S_IN_MAP, 0x78);
	REG_FLD_MOD(av_base, HDMI_CORE_AV_SWAP_I2S, 1, 5, 5);
पूर्ण

अटल व्योम hdmi_core_audio_infoframe_cfg(काष्ठा hdmi_core_data *core,
		काष्ठा snd_cea_861_aud_अगर *info_aud)
अणु
	u8 sum = 0, checksum = 0;
	व्योम __iomem *av_base = hdmi_av_base(core);

	/*
	 * Set audio info frame type, version and length as
	 * described in HDMI 1.4a Section 8.2.2 specअगरication.
	 * Checksum calculation is defined in Section 5.3.5.
	 */
	hdmi_ग_लिखो_reg(av_base, HDMI_CORE_AV_AUDIO_TYPE, 0x84);
	hdmi_ग_लिखो_reg(av_base, HDMI_CORE_AV_AUDIO_VERS, 0x01);
	hdmi_ग_लिखो_reg(av_base, HDMI_CORE_AV_AUDIO_LEN, 0x0a);
	sum += 0x84 + 0x001 + 0x00a;

	hdmi_ग_लिखो_reg(av_base, HDMI_CORE_AV_AUD_DBYTE(0),
		       info_aud->db1_ct_cc);
	sum += info_aud->db1_ct_cc;

	hdmi_ग_लिखो_reg(av_base, HDMI_CORE_AV_AUD_DBYTE(1),
		       info_aud->db2_sf_ss);
	sum += info_aud->db2_sf_ss;

	hdmi_ग_लिखो_reg(av_base, HDMI_CORE_AV_AUD_DBYTE(2), info_aud->db3);
	sum += info_aud->db3;

	/*
	 * The OMAP HDMI IP requires to use the 8-channel channel code when
	 * transmitting more than two channels.
	 */
	अगर (info_aud->db4_ca != 0x00)
		info_aud->db4_ca = 0x13;

	hdmi_ग_लिखो_reg(av_base, HDMI_CORE_AV_AUD_DBYTE(3), info_aud->db4_ca);
	sum += info_aud->db4_ca;

	hdmi_ग_लिखो_reg(av_base, HDMI_CORE_AV_AUD_DBYTE(4),
		       info_aud->db5_dminh_lsv);
	sum += info_aud->db5_dminh_lsv;

	hdmi_ग_लिखो_reg(av_base, HDMI_CORE_AV_AUD_DBYTE(5), 0x00);
	hdmi_ग_लिखो_reg(av_base, HDMI_CORE_AV_AUD_DBYTE(6), 0x00);
	hdmi_ग_लिखो_reg(av_base, HDMI_CORE_AV_AUD_DBYTE(7), 0x00);
	hdmi_ग_लिखो_reg(av_base, HDMI_CORE_AV_AUD_DBYTE(8), 0x00);
	hdmi_ग_लिखो_reg(av_base, HDMI_CORE_AV_AUD_DBYTE(9), 0x00);

	checksum = 0x100 - sum;
	hdmi_ग_लिखो_reg(av_base,
					HDMI_CORE_AV_AUDIO_CHSUM, checksum);

	/*
	 * TODO: Add MPEG and SPD enable and repeat cfg when EDID parsing
	 * is available.
	 */
पूर्ण

पूर्णांक hdmi4_audio_config(काष्ठा hdmi_core_data *core, काष्ठा hdmi_wp_data *wp,
		काष्ठा omap_dss_audio *audio, u32 pclk)
अणु
	काष्ठा hdmi_audio_क्रमmat audio_क्रमmat;
	काष्ठा hdmi_audio_dma audio_dma;
	काष्ठा hdmi_core_audio_config acore;
	पूर्णांक n, cts, channel_count;
	अचिन्हित पूर्णांक fs_nr;
	bool word_length_16b = false;

	अगर (!audio || !audio->iec || !audio->cea || !core)
		वापस -EINVAL;

	acore.iec60958_cfg = audio->iec;
	/*
	 * In the IEC-60958 status word, check अगर the audio sample word length
	 * is 16-bit as several optimizations can be perक्रमmed in such हाल.
	 */
	अगर (!(audio->iec->status[4] & IEC958_AES4_CON_MAX_WORDLEN_24))
		अगर (audio->iec->status[4] & IEC958_AES4_CON_WORDLEN_20_16)
			word_length_16b = true;

	/* I2S configuration. See Phillips' specअगरication */
	अगर (word_length_16b)
		acore.i2s_cfg.justअगरication = HDMI_AUDIO_JUSTIFY_LEFT;
	अन्यथा
		acore.i2s_cfg.justअगरication = HDMI_AUDIO_JUSTIFY_RIGHT;
	/*
	 * The I2S input word length is twice the length given in the IEC-60958
	 * status word. If the word size is greater than
	 * 20 bits, increment by one.
	 */
	acore.i2s_cfg.in_length_bits = audio->iec->status[4]
		& IEC958_AES4_CON_WORDLEN;
	अगर (audio->iec->status[4] & IEC958_AES4_CON_MAX_WORDLEN_24)
		acore.i2s_cfg.in_length_bits++;
	acore.i2s_cfg.sck_edge_mode = HDMI_AUDIO_I2S_SCK_EDGE_RISING;
	acore.i2s_cfg.vbit = HDMI_AUDIO_I2S_VBIT_FOR_PCM;
	acore.i2s_cfg.direction = HDMI_AUDIO_I2S_MSB_SHIFTED_FIRST;
	acore.i2s_cfg.shअगरt = HDMI_AUDIO_I2S_FIRST_BIT_SHIFT;

	/* convert sample frequency to a number */
	चयन (audio->iec->status[3] & IEC958_AES3_CON_FS) अणु
	हाल IEC958_AES3_CON_FS_32000:
		fs_nr = 32000;
		अवरोध;
	हाल IEC958_AES3_CON_FS_44100:
		fs_nr = 44100;
		अवरोध;
	हाल IEC958_AES3_CON_FS_48000:
		fs_nr = 48000;
		अवरोध;
	हाल IEC958_AES3_CON_FS_88200:
		fs_nr = 88200;
		अवरोध;
	हाल IEC958_AES3_CON_FS_96000:
		fs_nr = 96000;
		अवरोध;
	हाल IEC958_AES3_CON_FS_176400:
		fs_nr = 176400;
		अवरोध;
	हाल IEC958_AES3_CON_FS_192000:
		fs_nr = 192000;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	hdmi_compute_acr(pclk, fs_nr, &n, &cts);

	/* Audio घड़ी regeneration settings */
	acore.n = n;
	acore.cts = cts;
	अगर (dss_has_feature(FEAT_HDMI_CTS_SWMODE)) अणु
		acore.aud_par_busclk = 0;
		acore.cts_mode = HDMI_AUDIO_CTS_MODE_SW;
		acore.use_mclk = dss_has_feature(FEAT_HDMI_AUDIO_USE_MCLK);
	पूर्ण अन्यथा अणु
		acore.aud_par_busclk = (((128 * 31) - 1) << 8);
		acore.cts_mode = HDMI_AUDIO_CTS_MODE_HW;
		acore.use_mclk = true;
	पूर्ण

	अगर (acore.use_mclk)
		acore.mclk_mode = HDMI_AUDIO_MCLK_128FS;

	/* Audio channels settings */
	channel_count = (audio->cea->db1_ct_cc &
			 CEA861_AUDIO_INFOFRAME_DB1CC) + 1;

	चयन (channel_count) अणु
	हाल 2:
		audio_क्रमmat.active_chnnls_msk = 0x03;
		अवरोध;
	हाल 3:
		audio_क्रमmat.active_chnnls_msk = 0x07;
		अवरोध;
	हाल 4:
		audio_क्रमmat.active_chnnls_msk = 0x0f;
		अवरोध;
	हाल 5:
		audio_क्रमmat.active_chnnls_msk = 0x1f;
		अवरोध;
	हाल 6:
		audio_क्रमmat.active_chnnls_msk = 0x3f;
		अवरोध;
	हाल 7:
		audio_क्रमmat.active_chnnls_msk = 0x7f;
		अवरोध;
	हाल 8:
		audio_क्रमmat.active_chnnls_msk = 0xff;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/*
	 * the HDMI IP needs to enable four stereo channels when transmitting
	 * more than 2 audio channels.  Similarly, the channel count in the
	 * Audio InfoFrame has to match the sample_present bits (some channels
	 * are padded with zeroes)
	 */
	अगर (channel_count == 2) अणु
		audio_क्रमmat.stereo_channels = HDMI_AUDIO_STEREO_ONECHANNEL;
		acore.i2s_cfg.active_sds = HDMI_AUDIO_I2S_SD0_EN;
		acore.layout = HDMI_AUDIO_LAYOUT_2CH;
	पूर्ण अन्यथा अणु
		audio_क्रमmat.stereo_channels = HDMI_AUDIO_STEREO_FOURCHANNELS;
		acore.i2s_cfg.active_sds = HDMI_AUDIO_I2S_SD0_EN |
				HDMI_AUDIO_I2S_SD1_EN | HDMI_AUDIO_I2S_SD2_EN |
				HDMI_AUDIO_I2S_SD3_EN;
		acore.layout = HDMI_AUDIO_LAYOUT_8CH;
		audio->cea->db1_ct_cc = 7;
	पूर्ण

	acore.en_spdअगर = false;
	/* use sample frequency from channel status word */
	acore.fs_override = true;
	/* enable ACR packets */
	acore.en_acr_pkt = true;
	/* disable direct streaming digital audio */
	acore.en_dsd_audio = false;
	/* use parallel audio पूर्णांकerface */
	acore.en_parallel_aud_input = true;

	/* DMA settings */
	अगर (word_length_16b)
		audio_dma.transfer_size = 0x10;
	अन्यथा
		audio_dma.transfer_size = 0x20;
	audio_dma.block_size = 0xC0;
	audio_dma.mode = HDMI_AUDIO_TRANSF_DMA;
	audio_dma.fअगरo_threshold = 0x20; /* in number of samples */

	/* audio FIFO क्रमmat settings */
	अगर (word_length_16b) अणु
		audio_क्रमmat.samples_per_word = HDMI_AUDIO_ONEWORD_TWOSAMPLES;
		audio_क्रमmat.sample_size = HDMI_AUDIO_SAMPLE_16BITS;
		audio_क्रमmat.justअगरication = HDMI_AUDIO_JUSTIFY_LEFT;
	पूर्ण अन्यथा अणु
		audio_क्रमmat.samples_per_word = HDMI_AUDIO_ONEWORD_ONESAMPLE;
		audio_क्रमmat.sample_size = HDMI_AUDIO_SAMPLE_24BITS;
		audio_क्रमmat.justअगरication = HDMI_AUDIO_JUSTIFY_RIGHT;
	पूर्ण
	audio_क्रमmat.type = HDMI_AUDIO_TYPE_LPCM;
	audio_क्रमmat.sample_order = HDMI_AUDIO_SAMPLE_LEFT_FIRST;
	/* disable start/stop संकेतs of IEC 60958 blocks */
	audio_क्रमmat.en_sig_blk_strt_end = HDMI_AUDIO_BLOCK_SIG_STARTEND_ON;

	/* configure DMA and audio FIFO क्रमmat*/
	hdmi_wp_audio_config_dma(wp, &audio_dma);
	hdmi_wp_audio_config_क्रमmat(wp, &audio_क्रमmat);

	/* configure the core*/
	hdmi_core_audio_config(core, &acore);

	/* configure CEA 861 audio infoframe*/
	hdmi_core_audio_infoframe_cfg(core, audio->cea);

	वापस 0;
पूर्ण

पूर्णांक hdmi4_audio_start(काष्ठा hdmi_core_data *core, काष्ठा hdmi_wp_data *wp)
अणु
	REG_FLD_MOD(hdmi_av_base(core),
		    HDMI_CORE_AV_AUD_MODE, true, 0, 0);

	hdmi_wp_audio_core_req_enable(wp, true);

	वापस 0;
पूर्ण

व्योम hdmi4_audio_stop(काष्ठा hdmi_core_data *core, काष्ठा hdmi_wp_data *wp)
अणु
	REG_FLD_MOD(hdmi_av_base(core),
		    HDMI_CORE_AV_AUD_MODE, false, 0, 0);

	hdmi_wp_audio_core_req_enable(wp, false);
पूर्ण

पूर्णांक hdmi4_core_init(काष्ठा platक्रमm_device *pdev, काष्ठा hdmi_core_data *core)
अणु
	core->base = devm_platक्रमm_ioremap_resource_byname(pdev, "core");
	अगर (IS_ERR(core->base)) अणु
		DSSERR("can't ioremap CORE\n");
		वापस PTR_ERR(core->base);
	पूर्ण

	वापस 0;
पूर्ण
