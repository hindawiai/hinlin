<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2018 BayLibre, SAS
 * Author: Maxime Jourdan <mjourdan@baylibre.com>
 *
 * VDEC_1 is a video decoding block that allows decoding of
 * MPEG 1/2/4, H.263, H.264, MJPEG, VC1
 */

#समावेश <linux/firmware.h>
#समावेश <linux/clk.h>

#समावेश "vdec_1.h"
#समावेश "vdec_helpers.h"
#समावेश "dos_regs.h"

/* AO Registers */
#घोषणा AO_RTI_GEN_PWR_SLEEP0	0xe8
#घोषणा AO_RTI_GEN_PWR_ISO0	0xec
	#घोषणा GEN_PWR_VDEC_1 (BIT(3) | BIT(2))
	#घोषणा GEN_PWR_VDEC_1_SM1 (BIT(1))

#घोषणा MC_SIZE			(4096 * 4)

अटल पूर्णांक
vdec_1_load_firmware(काष्ठा amvdec_session *sess, स्थिर अक्षर *fwname)
अणु
	स्थिर काष्ठा firmware *fw;
	काष्ठा amvdec_core *core = sess->core;
	काष्ठा device *dev = core->dev_dec;
	काष्ठा amvdec_codec_ops *codec_ops = sess->fmt_out->codec_ops;
	अटल व्योम *mc_addr;
	अटल dma_addr_t mc_addr_map;
	पूर्णांक ret;
	u32 i = 1000;

	ret = request_firmware(&fw, fwname, dev);
	अगर (ret < 0)
		वापस -EINVAL;

	अगर (fw->size < MC_SIZE) अणु
		dev_err(dev, "Firmware size %zu is too small. Expected %u.\n",
			fw->size, MC_SIZE);
		ret = -EINVAL;
		जाओ release_firmware;
	पूर्ण

	mc_addr = dma_alloc_coherent(core->dev, MC_SIZE,
				     &mc_addr_map, GFP_KERNEL);
	अगर (!mc_addr) अणु
		ret = -ENOMEM;
		जाओ release_firmware;
	पूर्ण

	स_नकल(mc_addr, fw->data, MC_SIZE);

	amvdec_ग_लिखो_करोs(core, MPSR, 0);
	amvdec_ग_लिखो_करोs(core, CPSR, 0);

	amvdec_clear_करोs_bits(core, MDEC_PIC_DC_CTRL, BIT(31));

	amvdec_ग_लिखो_करोs(core, IMEM_DMA_ADR, mc_addr_map);
	amvdec_ग_लिखो_करोs(core, IMEM_DMA_COUNT, MC_SIZE / 4);
	amvdec_ग_लिखो_करोs(core, IMEM_DMA_CTRL, (0x8000 | (7 << 16)));

	जबतक (--i && amvdec_पढ़ो_करोs(core, IMEM_DMA_CTRL) & 0x8000);

	अगर (i == 0) अणु
		dev_err(dev, "Firmware load fail (DMA hang?)\n");
		ret = -EINVAL;
		जाओ मुक्त_mc;
	पूर्ण

	अगर (codec_ops->load_extended_firmware)
		ret = codec_ops->load_extended_firmware(sess,
							fw->data + MC_SIZE,
							fw->size - MC_SIZE);

मुक्त_mc:
	dma_मुक्त_coherent(core->dev, MC_SIZE, mc_addr, mc_addr_map);
release_firmware:
	release_firmware(fw);
	वापस ret;
पूर्ण

अटल पूर्णांक vdec_1_stbuf_घातer_up(काष्ठा amvdec_session *sess)
अणु
	काष्ठा amvdec_core *core = sess->core;

	amvdec_ग_लिखो_करोs(core, VLD_MEM_VIFIFO_CONTROL, 0);
	amvdec_ग_लिखो_करोs(core, VLD_MEM_VIFIFO_WRAP_COUNT, 0);
	amvdec_ग_लिखो_करोs(core, POWER_CTL_VLD, BIT(4));

	amvdec_ग_लिखो_करोs(core, VLD_MEM_VIFIFO_START_PTR, sess->vअगरअगरo_paddr);
	amvdec_ग_लिखो_करोs(core, VLD_MEM_VIFIFO_CURR_PTR, sess->vअगरअगरo_paddr);
	amvdec_ग_लिखो_करोs(core, VLD_MEM_VIFIFO_END_PTR,
			 sess->vअगरअगरo_paddr + sess->vअगरअगरo_size - 8);

	amvdec_ग_लिखो_करोs_bits(core, VLD_MEM_VIFIFO_CONTROL, 1);
	amvdec_clear_करोs_bits(core, VLD_MEM_VIFIFO_CONTROL, 1);

	amvdec_ग_लिखो_करोs(core, VLD_MEM_VIFIFO_BUF_CNTL, MEM_BUFCTRL_MANUAL);
	amvdec_ग_लिखो_करोs(core, VLD_MEM_VIFIFO_WP, sess->vअगरअगरo_paddr);

	amvdec_ग_लिखो_करोs_bits(core, VLD_MEM_VIFIFO_BUF_CNTL, 1);
	amvdec_clear_करोs_bits(core, VLD_MEM_VIFIFO_BUF_CNTL, 1);

	amvdec_ग_लिखो_करोs_bits(core, VLD_MEM_VIFIFO_CONTROL,
			      (0x11 << MEM_FIFO_CNT_BIT) | MEM_FILL_ON_LEVEL |
			      MEM_CTRL_FILL_EN | MEM_CTRL_EMPTY_EN);

	वापस 0;
पूर्ण

अटल व्योम vdec_1_conf_esparser(काष्ठा amvdec_session *sess)
अणु
	काष्ठा amvdec_core *core = sess->core;

	/* VDEC_1 specअगरic ESPARSER stuff */
	amvdec_ग_लिखो_करोs(core, DOS_GEN_CTRL0, 0);
	amvdec_ग_लिखो_करोs(core, VLD_MEM_VIFIFO_BUF_CNTL, 1);
	amvdec_clear_करोs_bits(core, VLD_MEM_VIFIFO_BUF_CNTL, 1);
पूर्ण

अटल u32 vdec_1_vअगरअगरo_level(काष्ठा amvdec_session *sess)
अणु
	काष्ठा amvdec_core *core = sess->core;

	वापस amvdec_पढ़ो_करोs(core, VLD_MEM_VIFIFO_LEVEL);
पूर्ण

अटल पूर्णांक vdec_1_stop(काष्ठा amvdec_session *sess)
अणु
	काष्ठा amvdec_core *core = sess->core;
	काष्ठा amvdec_codec_ops *codec_ops = sess->fmt_out->codec_ops;

	amvdec_ग_लिखो_करोs(core, MPSR, 0);
	amvdec_ग_लिखो_करोs(core, CPSR, 0);
	amvdec_ग_लिखो_करोs(core, ASSIST_MBOX1_MASK, 0);

	amvdec_ग_लिखो_करोs(core, DOS_SW_RESET0, BIT(12) | BIT(11));
	amvdec_ग_लिखो_करोs(core, DOS_SW_RESET0, 0);
	amvdec_पढ़ो_करोs(core, DOS_SW_RESET0);

	/* enable vdec1 isolation */
	अगर (core->platक्रमm->revision == VDEC_REVISION_SM1)
		regmap_update_bits(core->regmap_ao, AO_RTI_GEN_PWR_ISO0,
				   GEN_PWR_VDEC_1_SM1, GEN_PWR_VDEC_1_SM1);
	अन्यथा
		regmap_ग_लिखो(core->regmap_ao, AO_RTI_GEN_PWR_ISO0, 0xc0);
	/* घातer off vdec1 memories */
	amvdec_ग_लिखो_करोs(core, DOS_MEM_PD_VDEC, 0xffffffff);
	/* घातer off vdec1 */
	अगर (core->platक्रमm->revision == VDEC_REVISION_SM1)
		regmap_update_bits(core->regmap_ao, AO_RTI_GEN_PWR_SLEEP0,
				   GEN_PWR_VDEC_1_SM1, GEN_PWR_VDEC_1_SM1);
	अन्यथा
		regmap_update_bits(core->regmap_ao, AO_RTI_GEN_PWR_SLEEP0,
				   GEN_PWR_VDEC_1, GEN_PWR_VDEC_1);

	clk_disable_unprepare(core->vdec_1_clk);

	अगर (sess->priv)
		codec_ops->stop(sess);

	वापस 0;
पूर्ण

अटल पूर्णांक vdec_1_start(काष्ठा amvdec_session *sess)
अणु
	पूर्णांक ret;
	काष्ठा amvdec_core *core = sess->core;
	काष्ठा amvdec_codec_ops *codec_ops = sess->fmt_out->codec_ops;

	/* Configure the vdec clk to the maximum available */
	clk_set_rate(core->vdec_1_clk, 666666666);
	ret = clk_prepare_enable(core->vdec_1_clk);
	अगर (ret)
		वापस ret;

	/* Enable घातer क्रम VDEC_1 */
	अगर (core->platक्रमm->revision == VDEC_REVISION_SM1)
		regmap_update_bits(core->regmap_ao, AO_RTI_GEN_PWR_SLEEP0,
				   GEN_PWR_VDEC_1_SM1, 0);
	अन्यथा
		regmap_update_bits(core->regmap_ao, AO_RTI_GEN_PWR_SLEEP0,
				   GEN_PWR_VDEC_1, 0);
	usleep_range(10, 20);

	/* Reset VDEC1 */
	amvdec_ग_लिखो_करोs(core, DOS_SW_RESET0, 0xfffffffc);
	amvdec_ग_लिखो_करोs(core, DOS_SW_RESET0, 0x00000000);

	amvdec_ग_लिखो_करोs(core, DOS_GCLK_EN0, 0x3ff);

	/* enable VDEC Memories */
	amvdec_ग_लिखो_करोs(core, DOS_MEM_PD_VDEC, 0);
	/* Remove VDEC1 Isolation */
	अगर (core->platक्रमm->revision == VDEC_REVISION_SM1)
		regmap_update_bits(core->regmap_ao, AO_RTI_GEN_PWR_ISO0,
				   GEN_PWR_VDEC_1_SM1, 0);
	अन्यथा
		regmap_ग_लिखो(core->regmap_ao, AO_RTI_GEN_PWR_ISO0, 0);
	/* Reset DOS top रेजिस्टरs */
	amvdec_ग_लिखो_करोs(core, DOS_VDEC_MCRCC_STALL_CTRL, 0);

	amvdec_ग_लिखो_करोs(core, GCLK_EN, 0x3ff);
	amvdec_clear_करोs_bits(core, MDEC_PIC_DC_CTRL, BIT(31));

	vdec_1_stbuf_घातer_up(sess);

	ret = vdec_1_load_firmware(sess, sess->fmt_out->firmware_path);
	अगर (ret)
		जाओ stop;

	ret = codec_ops->start(sess);
	अगर (ret)
		जाओ stop;

	/* Enable IRQ */
	amvdec_ग_लिखो_करोs(core, ASSIST_MBOX1_CLR_REG, 1);
	amvdec_ग_लिखो_करोs(core, ASSIST_MBOX1_MASK, 1);

	/* Enable 2-plane output */
	अगर (sess->pixfmt_cap == V4L2_PIX_FMT_NV12M)
		amvdec_ग_लिखो_करोs_bits(core, MDEC_PIC_DC_CTRL, BIT(17));
	अन्यथा
		amvdec_clear_करोs_bits(core, MDEC_PIC_DC_CTRL, BIT(17));

	/* Enable firmware processor */
	amvdec_ग_लिखो_करोs(core, MPSR, 1);
	/* Let the firmware settle */
	usleep_range(10, 20);

	वापस 0;

stop:
	vdec_1_stop(sess);
	वापस ret;
पूर्ण

काष्ठा amvdec_ops vdec_1_ops = अणु
	.start = vdec_1_start,
	.stop = vdec_1_stop,
	.conf_esparser = vdec_1_conf_esparser,
	.vअगरअगरo_level = vdec_1_vअगरअगरo_level,
पूर्ण;
