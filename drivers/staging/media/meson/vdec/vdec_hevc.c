<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2018 Maxime Jourdan <maxi.jourdan@wanaकरोo.fr>
 *
 * VDEC_HEVC is a video decoding block that allows decoding of
 * HEVC, VP9
 */

#समावेश <linux/firmware.h>
#समावेश <linux/clk.h>

#समावेश "vdec_1.h"
#समावेश "vdec_helpers.h"
#समावेश "vdec_hevc.h"
#समावेश "hevc_regs.h"
#समावेश "dos_regs.h"

/* AO Registers */
#घोषणा AO_RTI_GEN_PWR_SLEEP0	0xe8
#घोषणा AO_RTI_GEN_PWR_ISO0	0xec
	#घोषणा GEN_PWR_VDEC_HEVC (BIT(7) | BIT(6))
	#घोषणा GEN_PWR_VDEC_HEVC_SM1 (BIT(2))

#घोषणा MC_SIZE	(4096 * 4)

अटल पूर्णांक vdec_hevc_load_firmware(काष्ठा amvdec_session *sess,
				   स्थिर अक्षर *fwname)
अणु
	काष्ठा amvdec_core *core = sess->core;
	काष्ठा device *dev = core->dev_dec;
	स्थिर काष्ठा firmware *fw;
	अटल व्योम *mc_addr;
	अटल dma_addr_t mc_addr_map;
	पूर्णांक ret;
	u32 i = 100;

	ret = request_firmware(&fw, fwname, dev);
	अगर (ret < 0)  अणु
		dev_err(dev, "Unable to request firmware %s\n", fwname);
		वापस ret;
	पूर्ण

	अगर (fw->size < MC_SIZE) अणु
		dev_err(dev, "Firmware size %zu is too small. Expected %u.\n",
			fw->size, MC_SIZE);
		ret = -EINVAL;
		जाओ release_firmware;
	पूर्ण

	mc_addr = dma_alloc_coherent(core->dev, MC_SIZE, &mc_addr_map,
				     GFP_KERNEL);
	अगर (!mc_addr) अणु
		ret = -ENOMEM;
		जाओ release_firmware;
	पूर्ण

	स_नकल(mc_addr, fw->data, MC_SIZE);

	amvdec_ग_लिखो_करोs(core, HEVC_MPSR, 0);
	amvdec_ग_लिखो_करोs(core, HEVC_CPSR, 0);

	amvdec_ग_लिखो_करोs(core, HEVC_IMEM_DMA_ADR, mc_addr_map);
	amvdec_ग_लिखो_करोs(core, HEVC_IMEM_DMA_COUNT, MC_SIZE / 4);
	amvdec_ग_लिखो_करोs(core, HEVC_IMEM_DMA_CTRL, (0x8000 | (7 << 16)));

	जबतक (i && (पढ़ोl(core->करोs_base + HEVC_IMEM_DMA_CTRL) & 0x8000))
		i--;

	अगर (i == 0) अणु
		dev_err(dev, "Firmware load fail (DMA hang?)\n");
		ret = -ENODEV;
	पूर्ण

	dma_मुक्त_coherent(core->dev, MC_SIZE, mc_addr, mc_addr_map);
release_firmware:
	release_firmware(fw);
	वापस ret;
पूर्ण

अटल व्योम vdec_hevc_stbuf_init(काष्ठा amvdec_session *sess)
अणु
	काष्ठा amvdec_core *core = sess->core;

	amvdec_ग_लिखो_करोs(core, HEVC_STREAM_CONTROL,
			 amvdec_पढ़ो_करोs(core, HEVC_STREAM_CONTROL) & ~1);
	amvdec_ग_लिखो_करोs(core, HEVC_STREAM_START_ADDR, sess->vअगरअगरo_paddr);
	amvdec_ग_लिखो_करोs(core, HEVC_STREAM_END_ADDR,
			 sess->vअगरअगरo_paddr + sess->vअगरअगरo_size);
	amvdec_ग_लिखो_करोs(core, HEVC_STREAM_RD_PTR, sess->vअगरअगरo_paddr);
	amvdec_ग_लिखो_करोs(core, HEVC_STREAM_WR_PTR, sess->vअगरअगरo_paddr);
पूर्ण

/* VDEC_HEVC specअगरic ESPARSER configuration */
अटल व्योम vdec_hevc_conf_esparser(काष्ठा amvdec_session *sess)
अणु
	काष्ठा amvdec_core *core = sess->core;

	/* set vअगरअगरo_vbuf_rp_sel=>vdec_hevc */
	amvdec_ग_लिखो_करोs(core, DOS_GEN_CTRL0, 3 << 1);
	amvdec_ग_लिखो_करोs(core, HEVC_STREAM_CONTROL,
			 amvdec_पढ़ो_करोs(core, HEVC_STREAM_CONTROL) | BIT(3));
	amvdec_ग_लिखो_करोs(core, HEVC_STREAM_CONTROL,
			 amvdec_पढ़ो_करोs(core, HEVC_STREAM_CONTROL) | 1);
	amvdec_ग_लिखो_करोs(core, HEVC_STREAM_FIFO_CTL,
			 amvdec_पढ़ो_करोs(core, HEVC_STREAM_FIFO_CTL) | BIT(29));
पूर्ण

अटल u32 vdec_hevc_vअगरअगरo_level(काष्ठा amvdec_session *sess)
अणु
	वापस पढ़ोl_relaxed(sess->core->करोs_base + HEVC_STREAM_LEVEL);
पूर्ण

अटल पूर्णांक vdec_hevc_stop(काष्ठा amvdec_session *sess)
अणु
	काष्ठा amvdec_core *core = sess->core;
	काष्ठा amvdec_codec_ops *codec_ops = sess->fmt_out->codec_ops;

	/* Disable पूर्णांकerrupt */
	amvdec_ग_लिखो_करोs(core, HEVC_ASSIST_MBOX1_MASK, 0);
	/* Disable firmware processor */
	amvdec_ग_लिखो_करोs(core, HEVC_MPSR, 0);

	अगर (sess->priv)
		codec_ops->stop(sess);

	/* Enable VDEC_HEVC Isolation */
	अगर (core->platक्रमm->revision == VDEC_REVISION_SM1)
		regmap_update_bits(core->regmap_ao, AO_RTI_GEN_PWR_ISO0,
				   GEN_PWR_VDEC_HEVC_SM1,
				   GEN_PWR_VDEC_HEVC_SM1);
	अन्यथा
		regmap_update_bits(core->regmap_ao, AO_RTI_GEN_PWR_ISO0,
				   0xc00, 0xc00);

	/* VDEC_HEVC Memories */
	amvdec_ग_लिखो_करोs(core, DOS_MEM_PD_HEVC, 0xffffffffUL);

	अगर (core->platक्रमm->revision == VDEC_REVISION_SM1)
		regmap_update_bits(core->regmap_ao, AO_RTI_GEN_PWR_SLEEP0,
				   GEN_PWR_VDEC_HEVC_SM1,
				   GEN_PWR_VDEC_HEVC_SM1);
	अन्यथा
		regmap_update_bits(core->regmap_ao, AO_RTI_GEN_PWR_SLEEP0,
				   GEN_PWR_VDEC_HEVC, GEN_PWR_VDEC_HEVC);

	clk_disable_unprepare(core->vdec_hevc_clk);
	अगर (core->platक्रमm->revision == VDEC_REVISION_G12A ||
	    core->platक्रमm->revision == VDEC_REVISION_SM1)
		clk_disable_unprepare(core->vdec_hevcf_clk);

	वापस 0;
पूर्ण

अटल पूर्णांक vdec_hevc_start(काष्ठा amvdec_session *sess)
अणु
	पूर्णांक ret;
	काष्ठा amvdec_core *core = sess->core;
	काष्ठा amvdec_codec_ops *codec_ops = sess->fmt_out->codec_ops;

	अगर (core->platक्रमm->revision == VDEC_REVISION_G12A ||
	    core->platक्रमm->revision == VDEC_REVISION_SM1) अणु
		clk_set_rate(core->vdec_hevcf_clk, 666666666);
		ret = clk_prepare_enable(core->vdec_hevcf_clk);
		अगर (ret)
			वापस ret;
	पूर्ण

	clk_set_rate(core->vdec_hevc_clk, 666666666);
	ret = clk_prepare_enable(core->vdec_hevc_clk);
	अगर (ret)
		वापस ret;

	अगर (core->platक्रमm->revision == VDEC_REVISION_SM1)
		regmap_update_bits(core->regmap_ao, AO_RTI_GEN_PWR_SLEEP0,
				   GEN_PWR_VDEC_HEVC_SM1, 0);
	अन्यथा
		regmap_update_bits(core->regmap_ao, AO_RTI_GEN_PWR_SLEEP0,
				   GEN_PWR_VDEC_HEVC, 0);
	usleep_range(10, 20);

	/* Reset VDEC_HEVC*/
	amvdec_ग_लिखो_करोs(core, DOS_SW_RESET3, 0xffffffff);
	amvdec_ग_लिखो_करोs(core, DOS_SW_RESET3, 0x00000000);

	amvdec_ग_लिखो_करोs(core, DOS_GCLK_EN3, 0xffffffff);

	/* VDEC_HEVC Memories */
	amvdec_ग_लिखो_करोs(core, DOS_MEM_PD_HEVC, 0x00000000);

	/* Remove VDEC_HEVC Isolation */
	अगर (core->platक्रमm->revision == VDEC_REVISION_SM1)
		regmap_update_bits(core->regmap_ao, AO_RTI_GEN_PWR_ISO0,
				   GEN_PWR_VDEC_HEVC_SM1, 0);
	अन्यथा
		regmap_update_bits(core->regmap_ao, AO_RTI_GEN_PWR_ISO0,
				   0xc00, 0);

	amvdec_ग_लिखो_करोs(core, DOS_SW_RESET3, 0xffffffff);
	amvdec_ग_लिखो_करोs(core, DOS_SW_RESET3, 0x00000000);

	vdec_hevc_stbuf_init(sess);

	ret = vdec_hevc_load_firmware(sess, sess->fmt_out->firmware_path);
	अगर (ret)
		जाओ stop;

	ret = codec_ops->start(sess);
	अगर (ret)
		जाओ stop;

	amvdec_ग_लिखो_करोs(core, DOS_SW_RESET3, BIT(12) | BIT(11));
	amvdec_ग_लिखो_करोs(core, DOS_SW_RESET3, 0);
	amvdec_पढ़ो_करोs(core, DOS_SW_RESET3);

	amvdec_ग_लिखो_करोs(core, HEVC_MPSR, 1);
	/* Let the firmware settle */
	usleep_range(10, 20);

	वापस 0;

stop:
	vdec_hevc_stop(sess);
	वापस ret;
पूर्ण

काष्ठा amvdec_ops vdec_hevc_ops = अणु
	.start = vdec_hevc_start,
	.stop = vdec_hevc_stop,
	.conf_esparser = vdec_hevc_conf_esparser,
	.vअगरअगरo_level = vdec_hevc_vअगरअगरo_level,
पूर्ण;
