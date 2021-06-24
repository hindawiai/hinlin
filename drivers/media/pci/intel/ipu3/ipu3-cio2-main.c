<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2017,2020 Intel Corporation
 *
 * Based partially on Intel IPU4 driver written by
 *  Sakari Ailus <sakari.ailus@linux.पूर्णांकel.com>
 *  Samu Onkalo <samu.onkalo@पूर्णांकel.com>
 *  Jouni Hथघgander <jouni.hogander@पूर्णांकel.com>
 *  Jouni Ukkonen <jouni.ukkonen@पूर्णांकel.com>
 *  Antti Laakso <antti.laakso@पूर्णांकel.com>
 * et al.
 */

#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/pfn.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/property.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-fwnode.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/videobuf2-dma-sg.h>

#समावेश "ipu3-cio2.h"

काष्ठा ipu3_cio2_fmt अणु
	u32 mbus_code;
	u32 fourcc;
	u8 mipicode;
	u8 bpp;
पूर्ण;

/*
 * These are raw क्रमmats used in Intel's third generation of
 * Image Processing Unit known as IPU3.
 * 10bit raw bayer packed, 32 bytes क्रम every 25 pixels,
 * last LSB 6 bits unused.
 */
अटल स्थिर काष्ठा ipu3_cio2_fmt क्रमmats[] = अणु
	अणु	/* put शेष entry at beginning */
		.mbus_code	= MEDIA_BUS_FMT_SGRBG10_1X10,
		.fourcc		= V4L2_PIX_FMT_IPU3_SGRBG10,
		.mipicode	= 0x2b,
		.bpp		= 10,
	पूर्ण, अणु
		.mbus_code	= MEDIA_BUS_FMT_SGBRG10_1X10,
		.fourcc		= V4L2_PIX_FMT_IPU3_SGBRG10,
		.mipicode	= 0x2b,
		.bpp		= 10,
	पूर्ण, अणु
		.mbus_code	= MEDIA_BUS_FMT_SBGGR10_1X10,
		.fourcc		= V4L2_PIX_FMT_IPU3_SBGGR10,
		.mipicode	= 0x2b,
		.bpp		= 10,
	पूर्ण, अणु
		.mbus_code	= MEDIA_BUS_FMT_SRGGB10_1X10,
		.fourcc		= V4L2_PIX_FMT_IPU3_SRGGB10,
		.mipicode	= 0x2b,
		.bpp		= 10,
	पूर्ण,
पूर्ण;

/*
 * cio2_find_क्रमmat - lookup color क्रमmat by fourcc or/and media bus code
 * @pixelक्रमmat: fourcc to match, ignored अगर null
 * @mbus_code: media bus code to match, ignored अगर null
 */
अटल स्थिर काष्ठा ipu3_cio2_fmt *cio2_find_क्रमmat(स्थिर u32 *pixelक्रमmat,
						    स्थिर u32 *mbus_code)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(क्रमmats); i++) अणु
		अगर (pixelक्रमmat && *pixelक्रमmat != क्रमmats[i].fourcc)
			जारी;
		अगर (mbus_code && *mbus_code != क्रमmats[i].mbus_code)
			जारी;

		वापस &क्रमmats[i];
	पूर्ण

	वापस शून्य;
पूर्ण

अटल अंतरभूत u32 cio2_bytesperline(स्थिर अचिन्हित पूर्णांक width)
अणु
	/*
	 * 64 bytes क्रम every 50 pixels, the line length
	 * in bytes is multiple of 64 (line end alignment).
	 */
	वापस DIV_ROUND_UP(width, 50) * 64;
पूर्ण

/**************** FBPT operations ****************/

अटल व्योम cio2_fbpt_निकास_dummy(काष्ठा cio2_device *cio2)
अणु
	अगर (cio2->dummy_lop) अणु
		dma_मुक्त_coherent(&cio2->pci_dev->dev, PAGE_SIZE,
				  cio2->dummy_lop, cio2->dummy_lop_bus_addr);
		cio2->dummy_lop = शून्य;
	पूर्ण
	अगर (cio2->dummy_page) अणु
		dma_मुक्त_coherent(&cio2->pci_dev->dev, PAGE_SIZE,
				  cio2->dummy_page, cio2->dummy_page_bus_addr);
		cio2->dummy_page = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक cio2_fbpt_init_dummy(काष्ठा cio2_device *cio2)
अणु
	अचिन्हित पूर्णांक i;

	cio2->dummy_page = dma_alloc_coherent(&cio2->pci_dev->dev, PAGE_SIZE,
					      &cio2->dummy_page_bus_addr,
					      GFP_KERNEL);
	cio2->dummy_lop = dma_alloc_coherent(&cio2->pci_dev->dev, PAGE_SIZE,
					     &cio2->dummy_lop_bus_addr,
					     GFP_KERNEL);
	अगर (!cio2->dummy_page || !cio2->dummy_lop) अणु
		cio2_fbpt_निकास_dummy(cio2);
		वापस -ENOMEM;
	पूर्ण
	/*
	 * List of Poपूर्णांकers(LOP) contains 1024x32b poपूर्णांकers to 4KB page each
	 * Initialize each entry to dummy_page bus base address.
	 */
	क्रम (i = 0; i < CIO2_LOP_ENTRIES; i++)
		cio2->dummy_lop[i] = PFN_DOWN(cio2->dummy_page_bus_addr);

	वापस 0;
पूर्ण

अटल व्योम cio2_fbpt_entry_enable(काष्ठा cio2_device *cio2,
				   काष्ठा cio2_fbpt_entry entry[CIO2_MAX_LOPS])
अणु
	/*
	 * The CPU first initializes some fields in fbpt, then sets
	 * the VALID bit, this barrier is to ensure that the DMA(device)
	 * करोes not see the VALID bit enabled beक्रमe other fields are
	 * initialized; otherwise it could lead to havoc.
	 */
	dma_wmb();

	/*
	 * Request पूर्णांकerrupts क्रम start and completion
	 * Valid bit is applicable only to 1st entry
	 */
	entry[0].first_entry.ctrl = CIO2_FBPT_CTRL_VALID |
		CIO2_FBPT_CTRL_IOC | CIO2_FBPT_CTRL_IOS;
पूर्ण

/* Initialize fpbt entries to poपूर्णांक to dummy frame */
अटल व्योम cio2_fbpt_entry_init_dummy(काष्ठा cio2_device *cio2,
				       काष्ठा cio2_fbpt_entry
				       entry[CIO2_MAX_LOPS])
अणु
	अचिन्हित पूर्णांक i;

	entry[0].first_entry.first_page_offset = 0;
	entry[1].second_entry.num_of_pages = CIO2_LOP_ENTRIES * CIO2_MAX_LOPS;
	entry[1].second_entry.last_page_available_bytes = PAGE_SIZE - 1;

	क्रम (i = 0; i < CIO2_MAX_LOPS; i++)
		entry[i].lop_page_addr = PFN_DOWN(cio2->dummy_lop_bus_addr);

	cio2_fbpt_entry_enable(cio2, entry);
पूर्ण

/* Initialize fpbt entries to poपूर्णांक to a given buffer */
अटल व्योम cio2_fbpt_entry_init_buf(काष्ठा cio2_device *cio2,
				     काष्ठा cio2_buffer *b,
				     काष्ठा cio2_fbpt_entry
				     entry[CIO2_MAX_LOPS])
अणु
	काष्ठा vb2_buffer *vb = &b->vbb.vb2_buf;
	अचिन्हित पूर्णांक length = vb->planes[0].length;
	पूर्णांक reमुख्यing, i;

	entry[0].first_entry.first_page_offset = b->offset;
	reमुख्यing = length + entry[0].first_entry.first_page_offset;
	entry[1].second_entry.num_of_pages = PFN_UP(reमुख्यing);
	/*
	 * last_page_available_bytes has the offset of the last byte in the
	 * last page which is still accessible by DMA. DMA cannot access
	 * beyond this poपूर्णांक. Valid range क्रम this is from 0 to 4095.
	 * 0 indicates 1st byte in the page is DMA accessible.
	 * 4095 (PAGE_SIZE - 1) means every single byte in the last page
	 * is available क्रम DMA transfer.
	 */
	reमुख्यing = offset_in_page(reमुख्यing) ?: PAGE_SIZE;
	entry[1].second_entry.last_page_available_bytes = reमुख्यing - 1;
	/* Fill FBPT */
	reमुख्यing = length;
	i = 0;
	जबतक (reमुख्यing > 0) अणु
		entry->lop_page_addr = PFN_DOWN(b->lop_bus_addr[i]);
		reमुख्यing -= CIO2_LOP_ENTRIES * PAGE_SIZE;
		entry++;
		i++;
	पूर्ण

	/*
	 * The first not meaningful FBPT entry should poपूर्णांक to a valid LOP
	 */
	entry->lop_page_addr = PFN_DOWN(cio2->dummy_lop_bus_addr);

	cio2_fbpt_entry_enable(cio2, entry);
पूर्ण

अटल पूर्णांक cio2_fbpt_init(काष्ठा cio2_device *cio2, काष्ठा cio2_queue *q)
अणु
	काष्ठा device *dev = &cio2->pci_dev->dev;

	q->fbpt = dma_alloc_coherent(dev, CIO2_FBPT_SIZE, &q->fbpt_bus_addr,
				     GFP_KERNEL);
	अगर (!q->fbpt)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम cio2_fbpt_निकास(काष्ठा cio2_queue *q, काष्ठा device *dev)
अणु
	dma_मुक्त_coherent(dev, CIO2_FBPT_SIZE, q->fbpt, q->fbpt_bus_addr);
पूर्ण

/**************** CSI2 hardware setup ****************/

/*
 * The CSI2 receiver has several parameters affecting
 * the receiver timings. These depend on the MIPI bus frequency
 * F in Hz (sensor transmitter rate) as follows:
 *     रेजिस्टर value = (A/1e9 + B * UI) / COUNT_ACC
 * where
 *      UI = 1 / (2 * F) in seconds
 *      COUNT_ACC = counter accuracy in seconds
 *      For IPU3 COUNT_ACC = 0.0625
 *
 * A and B are coefficients from the table below,
 * depending whether the रेजिस्टर minimum or maximum value is
 * calculated.
 *                                     Minimum     Maximum
 * Clock lane                          A     B     A     B
 * reg_rx_csi_dly_cnt_termen_clane     0     0    38     0
 * reg_rx_csi_dly_cnt_settle_clane    95    -8   300   -16
 * Data lanes
 * reg_rx_csi_dly_cnt_termen_dlane0    0     0    35     4
 * reg_rx_csi_dly_cnt_settle_dlane0   85    -2   145    -6
 * reg_rx_csi_dly_cnt_termen_dlane1    0     0    35     4
 * reg_rx_csi_dly_cnt_settle_dlane1   85    -2   145    -6
 * reg_rx_csi_dly_cnt_termen_dlane2    0     0    35     4
 * reg_rx_csi_dly_cnt_settle_dlane2   85    -2   145    -6
 * reg_rx_csi_dly_cnt_termen_dlane3    0     0    35     4
 * reg_rx_csi_dly_cnt_settle_dlane3   85    -2   145    -6
 *
 * We use the minimum values of both A and B.
 */

/*
 * shअगरt क्रम keeping value range suitable क्रम 32-bit पूर्णांकeger arithmetic
 */
#घोषणा LIMIT_SHIFT	8

अटल s32 cio2_rx_timing(s32 a, s32 b, s64 freq, पूर्णांक def)
अणु
	स्थिर u32 accinv = 16; /* invert of counter resolution */
	स्थिर u32 uiinv = 500000000; /* 1e9 / 2 */
	s32 r;

	freq >>= LIMIT_SHIFT;

	अगर (WARN_ON(freq <= 0 || freq > S32_MAX))
		वापस def;
	/*
	 * b could be 0, -2 or -8, so |accinv * b| is always
	 * less than (1 << ds) and thus |r| < 500000000.
	 */
	r = accinv * b * (uiinv >> LIMIT_SHIFT);
	r = r / (s32)freq;
	/* max value of a is 95 */
	r += accinv * a;

	वापस r;
पूर्ण;

/* Calculate the delay value क्रम termination enable of घड़ी lane HS Rx */
अटल पूर्णांक cio2_csi2_calc_timing(काष्ठा cio2_device *cio2, काष्ठा cio2_queue *q,
				 काष्ठा cio2_csi2_timing *timing,
				 अचिन्हित पूर्णांक bpp, अचिन्हित पूर्णांक lanes)
अणु
	काष्ठा device *dev = &cio2->pci_dev->dev;
	s64 freq;

	अगर (!q->sensor)
		वापस -ENODEV;

	freq = v4l2_get_link_freq(q->sensor->ctrl_handler, bpp, lanes * 2);
	अगर (freq < 0) अणु
		dev_err(dev, "error %lld, invalid link_freq\n", freq);
		वापस freq;
	पूर्ण

	timing->clk_termen = cio2_rx_timing(CIO2_CSIRX_DLY_CNT_TERMEN_CLANE_A,
					    CIO2_CSIRX_DLY_CNT_TERMEN_CLANE_B,
					    freq,
					    CIO2_CSIRX_DLY_CNT_TERMEN_DEFAULT);
	timing->clk_settle = cio2_rx_timing(CIO2_CSIRX_DLY_CNT_SETTLE_CLANE_A,
					    CIO2_CSIRX_DLY_CNT_SETTLE_CLANE_B,
					    freq,
					    CIO2_CSIRX_DLY_CNT_SETTLE_DEFAULT);
	timing->dat_termen = cio2_rx_timing(CIO2_CSIRX_DLY_CNT_TERMEN_DLANE_A,
					    CIO2_CSIRX_DLY_CNT_TERMEN_DLANE_B,
					    freq,
					    CIO2_CSIRX_DLY_CNT_TERMEN_DEFAULT);
	timing->dat_settle = cio2_rx_timing(CIO2_CSIRX_DLY_CNT_SETTLE_DLANE_A,
					    CIO2_CSIRX_DLY_CNT_SETTLE_DLANE_B,
					    freq,
					    CIO2_CSIRX_DLY_CNT_SETTLE_DEFAULT);

	dev_dbg(dev, "freq ct value is %d\n", timing->clk_termen);
	dev_dbg(dev, "freq cs value is %d\n", timing->clk_settle);
	dev_dbg(dev, "freq dt value is %d\n", timing->dat_termen);
	dev_dbg(dev, "freq ds value is %d\n", timing->dat_settle);

	वापस 0;
पूर्ण;

अटल पूर्णांक cio2_hw_init(काष्ठा cio2_device *cio2, काष्ठा cio2_queue *q)
अणु
	अटल स्थिर पूर्णांक NUM_VCS = 4;
	अटल स्थिर पूर्णांक SID;	/* Stream id */
	अटल स्थिर पूर्णांक ENTRY;
	अटल स्थिर पूर्णांक FBPT_WIDTH = DIV_ROUND_UP(CIO2_MAX_LOPS,
					CIO2_FBPT_SUBENTRY_UNIT);
	स्थिर u32 num_buffers1 = CIO2_MAX_BUFFERS - 1;
	स्थिर काष्ठा ipu3_cio2_fmt *fmt;
	व्योम __iomem *स्थिर base = cio2->base;
	u8 lanes, csi2bus = q->csi2.port;
	u8 sensor_vc = SENSOR_VIR_CH_DFLT;
	काष्ठा cio2_csi2_timing timing;
	पूर्णांक i, r;

	fmt = cio2_find_क्रमmat(शून्य, &q->subdev_fmt.code);
	अगर (!fmt)
		वापस -EINVAL;

	lanes = q->csi2.lanes;

	r = cio2_csi2_calc_timing(cio2, q, &timing, fmt->bpp, lanes);
	अगर (r)
		वापस r;

	ग_लिखोl(timing.clk_termen, q->csi_rx_base +
		CIO2_REG_CSIRX_DLY_CNT_TERMEN(CIO2_CSIRX_DLY_CNT_CLANE_IDX));
	ग_लिखोl(timing.clk_settle, q->csi_rx_base +
		CIO2_REG_CSIRX_DLY_CNT_SETTLE(CIO2_CSIRX_DLY_CNT_CLANE_IDX));

	क्रम (i = 0; i < lanes; i++) अणु
		ग_लिखोl(timing.dat_termen, q->csi_rx_base +
			CIO2_REG_CSIRX_DLY_CNT_TERMEN(i));
		ग_लिखोl(timing.dat_settle, q->csi_rx_base +
			CIO2_REG_CSIRX_DLY_CNT_SETTLE(i));
	पूर्ण

	ग_लिखोl(CIO2_PBM_WMCTRL1_MIN_2CK |
	       CIO2_PBM_WMCTRL1_MID1_2CK |
	       CIO2_PBM_WMCTRL1_MID2_2CK, base + CIO2_REG_PBM_WMCTRL1);
	ग_लिखोl(CIO2_PBM_WMCTRL2_HWM_2CK << CIO2_PBM_WMCTRL2_HWM_2CK_SHIFT |
	       CIO2_PBM_WMCTRL2_LWM_2CK << CIO2_PBM_WMCTRL2_LWM_2CK_SHIFT |
	       CIO2_PBM_WMCTRL2_OBFFWM_2CK <<
	       CIO2_PBM_WMCTRL2_OBFFWM_2CK_SHIFT |
	       CIO2_PBM_WMCTRL2_TRANSDYN << CIO2_PBM_WMCTRL2_TRANSDYN_SHIFT |
	       CIO2_PBM_WMCTRL2_OBFF_MEM_EN, base + CIO2_REG_PBM_WMCTRL2);
	ग_लिखोl(CIO2_PBM_ARB_CTRL_LANES_DIV <<
	       CIO2_PBM_ARB_CTRL_LANES_DIV_SHIFT |
	       CIO2_PBM_ARB_CTRL_LE_EN |
	       CIO2_PBM_ARB_CTRL_PLL_POST_SHTDN <<
	       CIO2_PBM_ARB_CTRL_PLL_POST_SHTDN_SHIFT |
	       CIO2_PBM_ARB_CTRL_PLL_AHD_WK_UP <<
	       CIO2_PBM_ARB_CTRL_PLL_AHD_WK_UP_SHIFT,
	       base + CIO2_REG_PBM_ARB_CTRL);
	ग_लिखोl(CIO2_CSIRX_STATUS_DLANE_HS_MASK,
	       q->csi_rx_base + CIO2_REG_CSIRX_STATUS_DLANE_HS);
	ग_लिखोl(CIO2_CSIRX_STATUS_DLANE_LP_MASK,
	       q->csi_rx_base + CIO2_REG_CSIRX_STATUS_DLANE_LP);

	ग_लिखोl(CIO2_FB_HPLL_FREQ, base + CIO2_REG_FB_HPLL_FREQ);
	ग_लिखोl(CIO2_ISCLK_RATIO, base + CIO2_REG_ISCLK_RATIO);

	/* Configure MIPI backend */
	क्रम (i = 0; i < NUM_VCS; i++)
		ग_लिखोl(1, q->csi_rx_base + CIO2_REG_MIPIBE_SP_LUT_ENTRY(i));

	/* There are 16 लघु packet LUT entry */
	क्रम (i = 0; i < 16; i++)
		ग_लिखोl(CIO2_MIPIBE_LP_LUT_ENTRY_DISREGARD,
		       q->csi_rx_base + CIO2_REG_MIPIBE_LP_LUT_ENTRY(i));
	ग_लिखोl(CIO2_MIPIBE_GLOBAL_LUT_DISREGARD,
	       q->csi_rx_base + CIO2_REG_MIPIBE_GLOBAL_LUT_DISREGARD);

	ग_लिखोl(CIO2_INT_EN_EXT_IE_MASK, base + CIO2_REG_INT_EN_EXT_IE);
	ग_लिखोl(CIO2_IRQCTRL_MASK, q->csi_rx_base + CIO2_REG_IRQCTRL_MASK);
	ग_लिखोl(CIO2_IRQCTRL_MASK, q->csi_rx_base + CIO2_REG_IRQCTRL_ENABLE);
	ग_लिखोl(0, q->csi_rx_base + CIO2_REG_IRQCTRL_EDGE);
	ग_लिखोl(0, q->csi_rx_base + CIO2_REG_IRQCTRL_LEVEL_NOT_PULSE);
	ग_लिखोl(CIO2_INT_EN_EXT_OE_MASK, base + CIO2_REG_INT_EN_EXT_OE);

	ग_लिखोl(CIO2_REG_INT_EN_IRQ | CIO2_INT_IOC(CIO2_DMA_CHAN) |
	       CIO2_REG_INT_EN_IOS(CIO2_DMA_CHAN),
	       base + CIO2_REG_INT_EN);

	ग_लिखोl((CIO2_PXM_PXF_FMT_CFG_BPP_10 | CIO2_PXM_PXF_FMT_CFG_PCK_64B)
	       << CIO2_PXM_PXF_FMT_CFG_SID0_SHIFT,
	       base + CIO2_REG_PXM_PXF_FMT_CFG0(csi2bus));
	ग_लिखोl(SID << CIO2_MIPIBE_LP_LUT_ENTRY_SID_SHIFT |
	       sensor_vc << CIO2_MIPIBE_LP_LUT_ENTRY_VC_SHIFT |
	       fmt->mipicode << CIO2_MIPIBE_LP_LUT_ENTRY_FORMAT_TYPE_SHIFT,
	       q->csi_rx_base + CIO2_REG_MIPIBE_LP_LUT_ENTRY(ENTRY));
	ग_लिखोl(0, q->csi_rx_base + CIO2_REG_MIPIBE_COMP_FORMAT(sensor_vc));
	ग_लिखोl(0, q->csi_rx_base + CIO2_REG_MIPIBE_FORCE_RAW8);
	ग_लिखोl(0, base + CIO2_REG_PXM_SID2BID0(csi2bus));

	ग_लिखोl(lanes, q->csi_rx_base + CIO2_REG_CSIRX_NOF_ENABLED_LANES);
	ग_लिखोl(CIO2_CGC_PRIM_TGE |
	       CIO2_CGC_SIDE_TGE |
	       CIO2_CGC_XOSC_TGE |
	       CIO2_CGC_D3I3_TGE |
	       CIO2_CGC_CSI2_INTERFRAME_TGE |
	       CIO2_CGC_CSI2_PORT_DCGE |
	       CIO2_CGC_SIDE_DCGE |
	       CIO2_CGC_PRIM_DCGE |
	       CIO2_CGC_ROSC_DCGE |
	       CIO2_CGC_XOSC_DCGE |
	       CIO2_CGC_CLKGATE_HOLDOFF << CIO2_CGC_CLKGATE_HOLDOFF_SHIFT |
	       CIO2_CGC_CSI_CLKGATE_HOLDOFF
	       << CIO2_CGC_CSI_CLKGATE_HOLDOFF_SHIFT, base + CIO2_REG_CGC);
	ग_लिखोl(CIO2_LTRCTRL_LTRDYNEN, base + CIO2_REG_LTRCTRL);
	ग_लिखोl(CIO2_LTRVAL0_VAL << CIO2_LTRVAL02_VAL_SHIFT |
	       CIO2_LTRVAL0_SCALE << CIO2_LTRVAL02_SCALE_SHIFT |
	       CIO2_LTRVAL1_VAL << CIO2_LTRVAL13_VAL_SHIFT |
	       CIO2_LTRVAL1_SCALE << CIO2_LTRVAL13_SCALE_SHIFT,
	       base + CIO2_REG_LTRVAL01);
	ग_लिखोl(CIO2_LTRVAL2_VAL << CIO2_LTRVAL02_VAL_SHIFT |
	       CIO2_LTRVAL2_SCALE << CIO2_LTRVAL02_SCALE_SHIFT |
	       CIO2_LTRVAL3_VAL << CIO2_LTRVAL13_VAL_SHIFT |
	       CIO2_LTRVAL3_SCALE << CIO2_LTRVAL13_SCALE_SHIFT,
	       base + CIO2_REG_LTRVAL23);

	क्रम (i = 0; i < CIO2_NUM_DMA_CHAN; i++) अणु
		ग_लिखोl(0, base + CIO2_REG_CDMABA(i));
		ग_लिखोl(0, base + CIO2_REG_CDMAC0(i));
		ग_लिखोl(0, base + CIO2_REG_CDMAC1(i));
	पूर्ण

	/* Enable DMA */
	ग_लिखोl(PFN_DOWN(q->fbpt_bus_addr), base + CIO2_REG_CDMABA(CIO2_DMA_CHAN));

	ग_लिखोl(num_buffers1 << CIO2_CDMAC0_FBPT_LEN_SHIFT |
	       FBPT_WIDTH << CIO2_CDMAC0_FBPT_WIDTH_SHIFT |
	       CIO2_CDMAC0_DMA_INTR_ON_FE |
	       CIO2_CDMAC0_FBPT_UPDATE_FIFO_FULL |
	       CIO2_CDMAC0_DMA_EN |
	       CIO2_CDMAC0_DMA_INTR_ON_FS |
	       CIO2_CDMAC0_DMA_HALTED, base + CIO2_REG_CDMAC0(CIO2_DMA_CHAN));

	ग_लिखोl(1 << CIO2_CDMAC1_LINENUMUPDATE_SHIFT,
	       base + CIO2_REG_CDMAC1(CIO2_DMA_CHAN));

	ग_लिखोl(0, base + CIO2_REG_PBM_FOPN_ABORT);

	ग_लिखोl(CIO2_PXM_FRF_CFG_CRC_TH << CIO2_PXM_FRF_CFG_CRC_TH_SHIFT |
	       CIO2_PXM_FRF_CFG_MSK_ECC_DPHY_NR |
	       CIO2_PXM_FRF_CFG_MSK_ECC_RE |
	       CIO2_PXM_FRF_CFG_MSK_ECC_DPHY_NE,
	       base + CIO2_REG_PXM_FRF_CFG(q->csi2.port));

	/* Clear पूर्णांकerrupts */
	ग_लिखोl(CIO2_IRQCTRL_MASK, q->csi_rx_base + CIO2_REG_IRQCTRL_CLEAR);
	ग_लिखोl(~0, base + CIO2_REG_INT_STS_EXT_OE);
	ग_लिखोl(~0, base + CIO2_REG_INT_STS_EXT_IE);
	ग_लिखोl(~0, base + CIO2_REG_INT_STS);

	/* Enable devices, starting from the last device in the pipe */
	ग_लिखोl(1, q->csi_rx_base + CIO2_REG_MIPIBE_ENABLE);
	ग_लिखोl(1, q->csi_rx_base + CIO2_REG_CSIRX_ENABLE);

	वापस 0;
पूर्ण

अटल व्योम cio2_hw_निकास(काष्ठा cio2_device *cio2, काष्ठा cio2_queue *q)
अणु
	व्योम __iomem *स्थिर base = cio2->base;
	अचिन्हित पूर्णांक i;
	u32 value;
	पूर्णांक ret;

	/* Disable CSI receiver and MIPI backend devices */
	ग_लिखोl(0, q->csi_rx_base + CIO2_REG_IRQCTRL_MASK);
	ग_लिखोl(0, q->csi_rx_base + CIO2_REG_IRQCTRL_ENABLE);
	ग_लिखोl(0, q->csi_rx_base + CIO2_REG_CSIRX_ENABLE);
	ग_लिखोl(0, q->csi_rx_base + CIO2_REG_MIPIBE_ENABLE);

	/* Halt DMA */
	ग_लिखोl(0, base + CIO2_REG_CDMAC0(CIO2_DMA_CHAN));
	ret = पढ़ोl_poll_समयout(base + CIO2_REG_CDMAC0(CIO2_DMA_CHAN),
				 value, value & CIO2_CDMAC0_DMA_HALTED,
				 4000, 2000000);
	अगर (ret)
		dev_err(&cio2->pci_dev->dev,
			"DMA %i can not be halted\n", CIO2_DMA_CHAN);

	क्रम (i = 0; i < CIO2_NUM_PORTS; i++) अणु
		ग_लिखोl(पढ़ोl(base + CIO2_REG_PXM_FRF_CFG(i)) |
		       CIO2_PXM_FRF_CFG_ABORT, base + CIO2_REG_PXM_FRF_CFG(i));
		ग_लिखोl(पढ़ोl(base + CIO2_REG_PBM_FOPN_ABORT) |
		       CIO2_PBM_FOPN_ABORT(i), base + CIO2_REG_PBM_FOPN_ABORT);
	पूर्ण
पूर्ण

अटल व्योम cio2_buffer_करोne(काष्ठा cio2_device *cio2, अचिन्हित पूर्णांक dma_chan)
अणु
	काष्ठा device *dev = &cio2->pci_dev->dev;
	काष्ठा cio2_queue *q = cio2->cur_queue;
	काष्ठा cio2_fbpt_entry *entry;
	u64 ns = kसमय_get_ns();

	अगर (dma_chan >= CIO2_QUEUES) अणु
		dev_err(dev, "bad DMA channel %i\n", dma_chan);
		वापस;
	पूर्ण

	entry = &q->fbpt[q->bufs_first * CIO2_MAX_LOPS];
	अगर (entry->first_entry.ctrl & CIO2_FBPT_CTRL_VALID) अणु
		dev_warn(&cio2->pci_dev->dev,
			 "no ready buffers found on DMA channel %u\n",
			 dma_chan);
		वापस;
	पूर्ण

	/* Find out which buffer(s) are पढ़ोy */
	करो अणु
		काष्ठा cio2_buffer *b;

		b = q->bufs[q->bufs_first];
		अगर (b) अणु
			अचिन्हित पूर्णांक received = entry[1].second_entry.num_of_bytes;
			अचिन्हित दीर्घ payload =
				vb2_get_plane_payload(&b->vbb.vb2_buf, 0);

			q->bufs[q->bufs_first] = शून्य;
			atomic_dec(&q->bufs_queued);
			dev_dbg(&cio2->pci_dev->dev,
				"buffer %i done\n", b->vbb.vb2_buf.index);

			b->vbb.vb2_buf.बारtamp = ns;
			b->vbb.field = V4L2_FIELD_NONE;
			b->vbb.sequence = atomic_पढ़ो(&q->frame_sequence);
			अगर (payload != received)
				dev_warn(dev,
					 "payload length is %lu, received %u\n",
					 payload, received);
			vb2_buffer_करोne(&b->vbb.vb2_buf, VB2_BUF_STATE_DONE);
		पूर्ण
		atomic_inc(&q->frame_sequence);
		cio2_fbpt_entry_init_dummy(cio2, entry);
		q->bufs_first = (q->bufs_first + 1) % CIO2_MAX_BUFFERS;
		entry = &q->fbpt[q->bufs_first * CIO2_MAX_LOPS];
	पूर्ण जबतक (!(entry->first_entry.ctrl & CIO2_FBPT_CTRL_VALID));
पूर्ण

अटल व्योम cio2_queue_event_sof(काष्ठा cio2_device *cio2, काष्ठा cio2_queue *q)
अणु
	/*
	 * For the user space camera control algorithms it is essential
	 * to know when the reception of a frame has begun. That's often
	 * the best timing inक्रमmation to get from the hardware.
	 */
	काष्ठा v4l2_event event = अणु
		.type = V4L2_EVENT_FRAME_SYNC,
		.u.frame_sync.frame_sequence = atomic_पढ़ो(&q->frame_sequence),
	पूर्ण;

	v4l2_event_queue(q->subdev.devnode, &event);
पूर्ण

अटल स्थिर अक्षर *स्थिर cio2_irq_errs[] = अणु
	"single packet header error corrected",
	"multiple packet header errors detected",
	"payload checksum (CRC) error",
	"fifo overflow",
	"reserved short packet data type detected",
	"reserved long packet data type detected",
	"incomplete long packet detected",
	"frame sync error",
	"line sync error",
	"DPHY start of transmission error",
	"DPHY synchronization error",
	"escape mode error",
	"escape mode trigger event",
	"escape mode ultra-low power state for data lane(s)",
	"escape mode ultra-low power state exit for clock lane",
	"inter-frame short packet discarded",
	"inter-frame long packet discarded",
	"non-matching Long Packet stalled",
पूर्ण;

अटल स्थिर अक्षर *स्थिर cio2_port_errs[] = अणु
	"ECC recoverable",
	"DPHY not recoverable",
	"ECC not recoverable",
	"CRC error",
	"INTERFRAMEDATA",
	"PKT2SHORT",
	"PKT2LONG",
पूर्ण;

अटल व्योम cio2_irq_handle_once(काष्ठा cio2_device *cio2, u32 पूर्णांक_status)
अणु
	व्योम __iomem *स्थिर base = cio2->base;
	काष्ठा device *dev = &cio2->pci_dev->dev;

	अगर (पूर्णांक_status & CIO2_INT_IOOE) अणु
		/*
		 * Interrupt on Output Error:
		 * 1) SRAM is full and FS received, or
		 * 2) An invalid bit detected by DMA.
		 */
		u32 oe_status, oe_clear;

		oe_clear = पढ़ोl(base + CIO2_REG_INT_STS_EXT_OE);
		oe_status = oe_clear;

		अगर (oe_status & CIO2_INT_EXT_OE_DMAOE_MASK) अणु
			dev_err(dev, "DMA output error: 0x%x\n",
				(oe_status & CIO2_INT_EXT_OE_DMAOE_MASK)
				>> CIO2_INT_EXT_OE_DMAOE_SHIFT);
			oe_status &= ~CIO2_INT_EXT_OE_DMAOE_MASK;
		पूर्ण
		अगर (oe_status & CIO2_INT_EXT_OE_OES_MASK) अणु
			dev_err(dev, "DMA output error on CSI2 buses: 0x%x\n",
				(oe_status & CIO2_INT_EXT_OE_OES_MASK)
				>> CIO2_INT_EXT_OE_OES_SHIFT);
			oe_status &= ~CIO2_INT_EXT_OE_OES_MASK;
		पूर्ण
		ग_लिखोl(oe_clear, base + CIO2_REG_INT_STS_EXT_OE);
		अगर (oe_status)
			dev_warn(dev, "unknown interrupt 0x%x on OE\n",
				 oe_status);
		पूर्णांक_status &= ~CIO2_INT_IOOE;
	पूर्ण

	अगर (पूर्णांक_status & CIO2_INT_IOC_MASK) अणु
		/* DMA IO करोne -- frame पढ़ोy */
		u32 clr = 0;
		अचिन्हित पूर्णांक d;

		क्रम (d = 0; d < CIO2_NUM_DMA_CHAN; d++)
			अगर (पूर्णांक_status & CIO2_INT_IOC(d)) अणु
				clr |= CIO2_INT_IOC(d);
				cio2_buffer_करोne(cio2, d);
			पूर्ण
		पूर्णांक_status &= ~clr;
	पूर्ण

	अगर (पूर्णांक_status & CIO2_INT_IOS_IOLN_MASK) अणु
		/* DMA IO starts or reached specअगरied line */
		u32 clr = 0;
		अचिन्हित पूर्णांक d;

		क्रम (d = 0; d < CIO2_NUM_DMA_CHAN; d++)
			अगर (पूर्णांक_status & CIO2_INT_IOS_IOLN(d)) अणु
				clr |= CIO2_INT_IOS_IOLN(d);
				अगर (d == CIO2_DMA_CHAN)
					cio2_queue_event_sof(cio2,
							     cio2->cur_queue);
			पूर्ण
		पूर्णांक_status &= ~clr;
	पूर्ण

	अगर (पूर्णांक_status & (CIO2_INT_IOIE | CIO2_INT_IOIRQ)) अणु
		/* CSI2 receiver (error) पूर्णांकerrupt */
		u32 ie_status, ie_clear;
		अचिन्हित पूर्णांक port;

		ie_clear = पढ़ोl(base + CIO2_REG_INT_STS_EXT_IE);
		ie_status = ie_clear;

		क्रम (port = 0; port < CIO2_NUM_PORTS; port++) अणु
			u32 port_status = (ie_status >> (port * 8)) & 0xff;
			u32 err_mask = BIT_MASK(ARRAY_SIZE(cio2_port_errs)) - 1;
			व्योम __iomem *स्थिर csi_rx_base =
						base + CIO2_REG_PIPE_BASE(port);
			अचिन्हित पूर्णांक i;

			जबतक (port_status & err_mask) अणु
				i = ffs(port_status) - 1;
				dev_err(dev, "port %i error %s\n",
					port, cio2_port_errs[i]);
				ie_status &= ~BIT(port * 8 + i);
				port_status &= ~BIT(i);
			पूर्ण

			अगर (ie_status & CIO2_INT_EXT_IE_IRQ(port)) अणु
				u32 csi2_status, csi2_clear;

				csi2_status = पढ़ोl(csi_rx_base +
						CIO2_REG_IRQCTRL_STATUS);
				csi2_clear = csi2_status;
				err_mask =
					BIT_MASK(ARRAY_SIZE(cio2_irq_errs)) - 1;

				जबतक (csi2_status & err_mask) अणु
					i = ffs(csi2_status) - 1;
					dev_err(dev,
						"CSI-2 receiver port %i: %s\n",
							port, cio2_irq_errs[i]);
					csi2_status &= ~BIT(i);
				पूर्ण

				ग_लिखोl(csi2_clear,
				       csi_rx_base + CIO2_REG_IRQCTRL_CLEAR);
				अगर (csi2_status)
					dev_warn(dev,
						 "unknown CSI2 error 0x%x on port %i\n",
						 csi2_status, port);

				ie_status &= ~CIO2_INT_EXT_IE_IRQ(port);
			पूर्ण
		पूर्ण

		ग_लिखोl(ie_clear, base + CIO2_REG_INT_STS_EXT_IE);
		अगर (ie_status)
			dev_warn(dev, "unknown interrupt 0x%x on IE\n",
				 ie_status);

		पूर्णांक_status &= ~(CIO2_INT_IOIE | CIO2_INT_IOIRQ);
	पूर्ण

	अगर (पूर्णांक_status)
		dev_warn(dev, "unknown interrupt 0x%x on INT\n", पूर्णांक_status);
पूर्ण

अटल irqवापस_t cio2_irq(पूर्णांक irq, व्योम *cio2_ptr)
अणु
	काष्ठा cio2_device *cio2 = cio2_ptr;
	व्योम __iomem *स्थिर base = cio2->base;
	काष्ठा device *dev = &cio2->pci_dev->dev;
	u32 पूर्णांक_status;

	पूर्णांक_status = पढ़ोl(base + CIO2_REG_INT_STS);
	dev_dbg(dev, "isr enter - interrupt status 0x%x\n", पूर्णांक_status);
	अगर (!पूर्णांक_status)
		वापस IRQ_NONE;

	करो अणु
		ग_लिखोl(पूर्णांक_status, base + CIO2_REG_INT_STS);
		cio2_irq_handle_once(cio2, पूर्णांक_status);
		पूर्णांक_status = पढ़ोl(base + CIO2_REG_INT_STS);
		अगर (पूर्णांक_status)
			dev_dbg(dev, "pending status 0x%x\n", पूर्णांक_status);
	पूर्ण जबतक (पूर्णांक_status);

	वापस IRQ_HANDLED;
पूर्ण

/**************** Videobuf2 पूर्णांकerface ****************/

अटल व्योम cio2_vb2_वापस_all_buffers(काष्ठा cio2_queue *q,
					क्रमागत vb2_buffer_state state)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < CIO2_MAX_BUFFERS; i++) अणु
		अगर (q->bufs[i]) अणु
			atomic_dec(&q->bufs_queued);
			vb2_buffer_करोne(&q->bufs[i]->vbb.vb2_buf,
					state);
			q->bufs[i] = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक cio2_vb2_queue_setup(काष्ठा vb2_queue *vq,
				अचिन्हित पूर्णांक *num_buffers,
				अचिन्हित पूर्णांक *num_planes,
				अचिन्हित पूर्णांक sizes[],
				काष्ठा device *alloc_devs[])
अणु
	काष्ठा cio2_device *cio2 = vb2_get_drv_priv(vq);
	काष्ठा cio2_queue *q = vb2q_to_cio2_queue(vq);
	अचिन्हित पूर्णांक i;

	*num_planes = q->क्रमmat.num_planes;

	क्रम (i = 0; i < *num_planes; ++i) अणु
		sizes[i] = q->क्रमmat.plane_fmt[i].sizeimage;
		alloc_devs[i] = &cio2->pci_dev->dev;
	पूर्ण

	*num_buffers = clamp_val(*num_buffers, 1, CIO2_MAX_BUFFERS);

	/* Initialize buffer queue */
	क्रम (i = 0; i < CIO2_MAX_BUFFERS; i++) अणु
		q->bufs[i] = शून्य;
		cio2_fbpt_entry_init_dummy(cio2, &q->fbpt[i * CIO2_MAX_LOPS]);
	पूर्ण
	atomic_set(&q->bufs_queued, 0);
	q->bufs_first = 0;
	q->bufs_next = 0;

	वापस 0;
पूर्ण

/* Called after each buffer is allocated */
अटल पूर्णांक cio2_vb2_buf_init(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा cio2_device *cio2 = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा device *dev = &cio2->pci_dev->dev;
	काष्ठा cio2_buffer *b =
		container_of(vb, काष्ठा cio2_buffer, vbb.vb2_buf);
	अचिन्हित पूर्णांक pages = PFN_UP(vb->planes[0].length);
	अचिन्हित पूर्णांक lops = DIV_ROUND_UP(pages + 1, CIO2_LOP_ENTRIES);
	काष्ठा sg_table *sg;
	काष्ठा sg_dma_page_iter sg_iter;
	अचिन्हित पूर्णांक i, j;

	अगर (lops <= 0 || lops > CIO2_MAX_LOPS) अणु
		dev_err(dev, "%s: bad buffer size (%i)\n", __func__,
			vb->planes[0].length);
		वापस -ENOSPC;		/* Should never happen */
	पूर्ण

	स_रखो(b->lop, 0, माप(b->lop));
	/* Allocate LOP table */
	क्रम (i = 0; i < lops; i++) अणु
		b->lop[i] = dma_alloc_coherent(dev, PAGE_SIZE,
					       &b->lop_bus_addr[i], GFP_KERNEL);
		अगर (!b->lop[i])
			जाओ fail;
	पूर्ण

	/* Fill LOP */
	sg = vb2_dma_sg_plane_desc(vb, 0);
	अगर (!sg)
		वापस -ENOMEM;

	अगर (sg->nents && sg->sgl)
		b->offset = sg->sgl->offset;

	i = j = 0;
	क्रम_each_sg_dma_page(sg->sgl, &sg_iter, sg->nents, 0) अणु
		अगर (!pages--)
			अवरोध;
		b->lop[i][j] = PFN_DOWN(sg_page_iter_dma_address(&sg_iter));
		j++;
		अगर (j == CIO2_LOP_ENTRIES) अणु
			i++;
			j = 0;
		पूर्ण
	पूर्ण

	b->lop[i][j] = PFN_DOWN(cio2->dummy_page_bus_addr);
	वापस 0;
fail:
	जबतक (i--)
		dma_मुक्त_coherent(dev, PAGE_SIZE, b->lop[i], b->lop_bus_addr[i]);
	वापस -ENOMEM;
पूर्ण

/* Transfer buffer ownership to cio2 */
अटल व्योम cio2_vb2_buf_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा cio2_device *cio2 = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा cio2_queue *q =
		container_of(vb->vb2_queue, काष्ठा cio2_queue, vbq);
	काष्ठा cio2_buffer *b =
		container_of(vb, काष्ठा cio2_buffer, vbb.vb2_buf);
	काष्ठा cio2_fbpt_entry *entry;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक i, j, next = q->bufs_next;
	पूर्णांक bufs_queued = atomic_inc_वापस(&q->bufs_queued);
	u32 fbpt_rp;

	dev_dbg(&cio2->pci_dev->dev, "queue buffer %d\n", vb->index);

	/*
	 * This code queues the buffer to the CIO2 DMA engine, which starts
	 * running once streaming has started. It is possible that this code
	 * माला_लो pre-empted due to increased CPU load. Upon this, the driver
	 * करोes not get an opportunity to queue new buffers to the CIO2 DMA
	 * engine. When the DMA engine encounters an FBPT entry without the
	 * VALID bit set, the DMA engine halts, which requires a restart of
	 * the DMA engine and sensor, to जारी streaming.
	 * This is not desired and is highly unlikely given that there are
	 * 32 FBPT entries that the DMA engine needs to process, to run पूर्णांकo
	 * an FBPT entry, without the VALID bit set. We try to mitigate this
	 * by disabling पूर्णांकerrupts क्रम the duration of this queueing.
	 */
	local_irq_save(flags);

	fbpt_rp = (पढ़ोl(cio2->base + CIO2_REG_CDMARI(CIO2_DMA_CHAN))
		   >> CIO2_CDMARI_FBPT_RP_SHIFT)
		   & CIO2_CDMARI_FBPT_RP_MASK;

	/*
	 * fbpt_rp is the fbpt entry that the dma is currently working
	 * on, but since it could jump to next entry at any समय,
	 * assume that we might alपढ़ोy be there.
	 */
	fbpt_rp = (fbpt_rp + 1) % CIO2_MAX_BUFFERS;

	अगर (bufs_queued <= 1 || fbpt_rp == next)
		/* Buffers were drained */
		next = (fbpt_rp + 1) % CIO2_MAX_BUFFERS;

	क्रम (i = 0; i < CIO2_MAX_BUFFERS; i++) अणु
		/*
		 * We have allocated CIO2_MAX_BUFFERS circularly क्रम the
		 * hw, the user has requested N buffer queue. The driver
		 * ensures N <= CIO2_MAX_BUFFERS and guarantees that whenever
		 * user queues a buffer, there necessarily is a मुक्त buffer.
		 */
		अगर (!q->bufs[next]) अणु
			q->bufs[next] = b;
			entry = &q->fbpt[next * CIO2_MAX_LOPS];
			cio2_fbpt_entry_init_buf(cio2, b, entry);
			local_irq_restore(flags);
			q->bufs_next = (next + 1) % CIO2_MAX_BUFFERS;
			क्रम (j = 0; j < vb->num_planes; j++)
				vb2_set_plane_payload(vb, j,
					q->क्रमmat.plane_fmt[j].sizeimage);
			वापस;
		पूर्ण

		dev_dbg(&cio2->pci_dev->dev, "entry %i was full!\n", next);
		next = (next + 1) % CIO2_MAX_BUFFERS;
	पूर्ण

	local_irq_restore(flags);
	dev_err(&cio2->pci_dev->dev, "error: all cio2 entries were full!\n");
	atomic_dec(&q->bufs_queued);
	vb2_buffer_करोne(vb, VB2_BUF_STATE_ERROR);
पूर्ण

/* Called when each buffer is मुक्तd */
अटल व्योम cio2_vb2_buf_cleanup(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा cio2_device *cio2 = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा cio2_buffer *b =
		container_of(vb, काष्ठा cio2_buffer, vbb.vb2_buf);
	अचिन्हित पूर्णांक i;

	/* Free LOP table */
	क्रम (i = 0; i < CIO2_MAX_LOPS; i++) अणु
		अगर (b->lop[i])
			dma_मुक्त_coherent(&cio2->pci_dev->dev, PAGE_SIZE,
					  b->lop[i], b->lop_bus_addr[i]);
	पूर्ण
पूर्ण

अटल पूर्णांक cio2_vb2_start_streaming(काष्ठा vb2_queue *vq, अचिन्हित पूर्णांक count)
अणु
	काष्ठा cio2_queue *q = vb2q_to_cio2_queue(vq);
	काष्ठा cio2_device *cio2 = vb2_get_drv_priv(vq);
	पूर्णांक r;

	cio2->cur_queue = q;
	atomic_set(&q->frame_sequence, 0);

	r = pm_runसमय_get_sync(&cio2->pci_dev->dev);
	अगर (r < 0) अणु
		dev_info(&cio2->pci_dev->dev, "failed to set power %d\n", r);
		pm_runसमय_put_noidle(&cio2->pci_dev->dev);
		वापस r;
	पूर्ण

	r = media_pipeline_start(&q->vdev.entity, &q->pipe);
	अगर (r)
		जाओ fail_pipeline;

	r = cio2_hw_init(cio2, q);
	अगर (r)
		जाओ fail_hw;

	/* Start streaming on sensor */
	r = v4l2_subdev_call(q->sensor, video, s_stream, 1);
	अगर (r)
		जाओ fail_csi2_subdev;

	cio2->streaming = true;

	वापस 0;

fail_csi2_subdev:
	cio2_hw_निकास(cio2, q);
fail_hw:
	media_pipeline_stop(&q->vdev.entity);
fail_pipeline:
	dev_dbg(&cio2->pci_dev->dev, "failed to start streaming (%d)\n", r);
	cio2_vb2_वापस_all_buffers(q, VB2_BUF_STATE_QUEUED);
	pm_runसमय_put(&cio2->pci_dev->dev);

	वापस r;
पूर्ण

अटल व्योम cio2_vb2_stop_streaming(काष्ठा vb2_queue *vq)
अणु
	काष्ठा cio2_queue *q = vb2q_to_cio2_queue(vq);
	काष्ठा cio2_device *cio2 = vb2_get_drv_priv(vq);

	अगर (v4l2_subdev_call(q->sensor, video, s_stream, 0))
		dev_err(&cio2->pci_dev->dev,
			"failed to stop sensor streaming\n");

	cio2_hw_निकास(cio2, q);
	synchronize_irq(cio2->pci_dev->irq);
	cio2_vb2_वापस_all_buffers(q, VB2_BUF_STATE_ERROR);
	media_pipeline_stop(&q->vdev.entity);
	pm_runसमय_put(&cio2->pci_dev->dev);
	cio2->streaming = false;
पूर्ण

अटल स्थिर काष्ठा vb2_ops cio2_vb2_ops = अणु
	.buf_init = cio2_vb2_buf_init,
	.buf_queue = cio2_vb2_buf_queue,
	.buf_cleanup = cio2_vb2_buf_cleanup,
	.queue_setup = cio2_vb2_queue_setup,
	.start_streaming = cio2_vb2_start_streaming,
	.stop_streaming = cio2_vb2_stop_streaming,
	.रुको_prepare = vb2_ops_रुको_prepare,
	.रुको_finish = vb2_ops_रुको_finish,
पूर्ण;

/**************** V4L2 पूर्णांकerface ****************/

अटल पूर्णांक cio2_v4l2_querycap(काष्ठा file *file, व्योम *fh,
			      काष्ठा v4l2_capability *cap)
अणु
	काष्ठा cio2_device *cio2 = video_drvdata(file);

	strscpy(cap->driver, CIO2_NAME, माप(cap->driver));
	strscpy(cap->card, CIO2_DEVICE_NAME, माप(cap->card));
	snम_लिखो(cap->bus_info, माप(cap->bus_info),
		 "PCI:%s", pci_name(cio2->pci_dev));

	वापस 0;
पूर्ण

अटल पूर्णांक cio2_v4l2_क्रमागत_fmt(काष्ठा file *file, व्योम *fh,
			      काष्ठा v4l2_fmtdesc *f)
अणु
	अगर (f->index >= ARRAY_SIZE(क्रमmats))
		वापस -EINVAL;

	f->pixelक्रमmat = क्रमmats[f->index].fourcc;

	वापस 0;
पूर्ण

/* The क्रमmat is validated in cio2_video_link_validate() */
अटल पूर्णांक cio2_v4l2_g_fmt(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा cio2_queue *q = file_to_cio2_queue(file);

	f->fmt.pix_mp = q->क्रमmat;

	वापस 0;
पूर्ण

अटल पूर्णांक cio2_v4l2_try_fmt(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_क्रमmat *f)
अणु
	स्थिर काष्ठा ipu3_cio2_fmt *fmt;
	काष्ठा v4l2_pix_क्रमmat_mplane *mpix = &f->fmt.pix_mp;

	fmt = cio2_find_क्रमmat(&mpix->pixelक्रमmat, शून्य);
	अगर (!fmt)
		fmt = &क्रमmats[0];

	/* Only supports up to 4224x3136 */
	अगर (mpix->width > CIO2_IMAGE_MAX_WIDTH)
		mpix->width = CIO2_IMAGE_MAX_WIDTH;
	अगर (mpix->height > CIO2_IMAGE_MAX_HEIGHT)
		mpix->height = CIO2_IMAGE_MAX_HEIGHT;

	mpix->num_planes = 1;
	mpix->pixelक्रमmat = fmt->fourcc;
	mpix->colorspace = V4L2_COLORSPACE_RAW;
	mpix->field = V4L2_FIELD_NONE;
	mpix->plane_fmt[0].bytesperline = cio2_bytesperline(mpix->width);
	mpix->plane_fmt[0].sizeimage = mpix->plane_fmt[0].bytesperline *
							mpix->height;

	/* use शेष */
	mpix->ycbcr_enc = V4L2_YCBCR_ENC_DEFAULT;
	mpix->quantization = V4L2_QUANTIZATION_DEFAULT;
	mpix->xfer_func = V4L2_XFER_FUNC_DEFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक cio2_v4l2_s_fmt(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा cio2_queue *q = file_to_cio2_queue(file);

	cio2_v4l2_try_fmt(file, fh, f);
	q->क्रमmat = f->fmt.pix_mp;

	वापस 0;
पूर्ण

अटल पूर्णांक
cio2_video_क्रमागत_input(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_input *input)
अणु
	अगर (input->index > 0)
		वापस -EINVAL;

	strscpy(input->name, "camera", माप(input->name));
	input->type = V4L2_INPUT_TYPE_CAMERA;

	वापस 0;
पूर्ण

अटल पूर्णांक
cio2_video_g_input(काष्ठा file *file, व्योम *fh, अचिन्हित पूर्णांक *input)
अणु
	*input = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक
cio2_video_s_input(काष्ठा file *file, व्योम *fh, अचिन्हित पूर्णांक input)
अणु
	वापस input == 0 ? 0 : -EINVAL;
पूर्ण

अटल स्थिर काष्ठा v4l2_file_operations cio2_v4l2_fops = अणु
	.owner = THIS_MODULE,
	.unlocked_ioctl = video_ioctl2,
	.खोलो = v4l2_fh_खोलो,
	.release = vb2_fop_release,
	.poll = vb2_fop_poll,
	.mmap = vb2_fop_mmap,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ioctl_ops cio2_v4l2_ioctl_ops = अणु
	.vidioc_querycap = cio2_v4l2_querycap,
	.vidioc_क्रमागत_fmt_vid_cap = cio2_v4l2_क्रमागत_fmt,
	.vidioc_g_fmt_vid_cap_mplane = cio2_v4l2_g_fmt,
	.vidioc_s_fmt_vid_cap_mplane = cio2_v4l2_s_fmt,
	.vidioc_try_fmt_vid_cap_mplane = cio2_v4l2_try_fmt,
	.vidioc_reqbufs = vb2_ioctl_reqbufs,
	.vidioc_create_bufs = vb2_ioctl_create_bufs,
	.vidioc_prepare_buf = vb2_ioctl_prepare_buf,
	.vidioc_querybuf = vb2_ioctl_querybuf,
	.vidioc_qbuf = vb2_ioctl_qbuf,
	.vidioc_dqbuf = vb2_ioctl_dqbuf,
	.vidioc_streamon = vb2_ioctl_streamon,
	.vidioc_streamoff = vb2_ioctl_streamoff,
	.vidioc_expbuf = vb2_ioctl_expbuf,
	.vidioc_क्रमागत_input = cio2_video_क्रमागत_input,
	.vidioc_g_input	= cio2_video_g_input,
	.vidioc_s_input	= cio2_video_s_input,
पूर्ण;

अटल पूर्णांक cio2_subdev_subscribe_event(काष्ठा v4l2_subdev *sd,
				       काष्ठा v4l2_fh *fh,
				       काष्ठा v4l2_event_subscription *sub)
अणु
	अगर (sub->type != V4L2_EVENT_FRAME_SYNC)
		वापस -EINVAL;

	/* Line number. For now only zero accepted. */
	अगर (sub->id != 0)
		वापस -EINVAL;

	वापस v4l2_event_subscribe(fh, sub, 0, शून्य);
पूर्ण

अटल पूर्णांक cio2_subdev_खोलो(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_subdev_fh *fh)
अणु
	काष्ठा v4l2_mbus_framefmt *क्रमmat;
	स्थिर काष्ठा v4l2_mbus_framefmt fmt_शेष = अणु
		.width = 1936,
		.height = 1096,
		.code = क्रमmats[0].mbus_code,
		.field = V4L2_FIELD_NONE,
		.colorspace = V4L2_COLORSPACE_RAW,
		.ycbcr_enc = V4L2_YCBCR_ENC_DEFAULT,
		.quantization = V4L2_QUANTIZATION_DEFAULT,
		.xfer_func = V4L2_XFER_FUNC_DEFAULT,
	पूर्ण;

	/* Initialize try_fmt */
	क्रमmat = v4l2_subdev_get_try_क्रमmat(sd, fh->pad, CIO2_PAD_SINK);
	*क्रमmat = fmt_शेष;

	/* same as sink */
	क्रमmat = v4l2_subdev_get_try_क्रमmat(sd, fh->pad, CIO2_PAD_SOURCE);
	*क्रमmat = fmt_शेष;

	वापस 0;
पूर्ण

/*
 * cio2_subdev_get_fmt - Handle get क्रमmat by pads subdev method
 * @sd : poपूर्णांकer to v4l2 subdev काष्ठाure
 * @cfg: V4L2 subdev pad config
 * @fmt: poपूर्णांकer to v4l2 subdev क्रमmat काष्ठाure
 * वापस -EINVAL or zero on success
 */
अटल पूर्णांक cio2_subdev_get_fmt(काष्ठा v4l2_subdev *sd,
			       काष्ठा v4l2_subdev_pad_config *cfg,
			       काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा cio2_queue *q = container_of(sd, काष्ठा cio2_queue, subdev);

	mutex_lock(&q->subdev_lock);

	अगर (fmt->which == V4L2_SUBDEV_FORMAT_TRY)
		fmt->क्रमmat = *v4l2_subdev_get_try_क्रमmat(sd, cfg, fmt->pad);
	अन्यथा
		fmt->क्रमmat = q->subdev_fmt;

	mutex_unlock(&q->subdev_lock);

	वापस 0;
पूर्ण

/*
 * cio2_subdev_set_fmt - Handle set क्रमmat by pads subdev method
 * @sd : poपूर्णांकer to v4l2 subdev काष्ठाure
 * @cfg: V4L2 subdev pad config
 * @fmt: poपूर्णांकer to v4l2 subdev क्रमmat काष्ठाure
 * वापस -EINVAL or zero on success
 */
अटल पूर्णांक cio2_subdev_set_fmt(काष्ठा v4l2_subdev *sd,
			       काष्ठा v4l2_subdev_pad_config *cfg,
			       काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा cio2_queue *q = container_of(sd, काष्ठा cio2_queue, subdev);
	काष्ठा v4l2_mbus_framefmt *mbus;
	u32 mbus_code = fmt->क्रमmat.code;
	अचिन्हित पूर्णांक i;

	/*
	 * Only allow setting sink pad क्रमmat;
	 * source always propagates from sink
	 */
	अगर (fmt->pad == CIO2_PAD_SOURCE)
		वापस cio2_subdev_get_fmt(sd, cfg, fmt);

	अगर (fmt->which == V4L2_SUBDEV_FORMAT_TRY)
		mbus = v4l2_subdev_get_try_क्रमmat(sd, cfg, fmt->pad);
	अन्यथा
		mbus = &q->subdev_fmt;

	fmt->क्रमmat.code = क्रमmats[0].mbus_code;

	क्रम (i = 0; i < ARRAY_SIZE(क्रमmats); i++) अणु
		अगर (क्रमmats[i].mbus_code == mbus_code) अणु
			fmt->क्रमmat.code = mbus_code;
			अवरोध;
		पूर्ण
	पूर्ण

	fmt->क्रमmat.width = min(fmt->क्रमmat.width, CIO2_IMAGE_MAX_WIDTH);
	fmt->क्रमmat.height = min(fmt->क्रमmat.height, CIO2_IMAGE_MAX_HEIGHT);
	fmt->क्रमmat.field = V4L2_FIELD_NONE;

	mutex_lock(&q->subdev_lock);
	*mbus = fmt->क्रमmat;
	mutex_unlock(&q->subdev_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक cio2_subdev_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
				      काष्ठा v4l2_subdev_pad_config *cfg,
				      काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	अगर (code->index >= ARRAY_SIZE(क्रमmats))
		वापस -EINVAL;

	code->code = क्रमmats[code->index].mbus_code;
	वापस 0;
पूर्ण

अटल पूर्णांक cio2_subdev_link_validate_get_क्रमmat(काष्ठा media_pad *pad,
						काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	अगर (is_media_entity_v4l2_subdev(pad->entity)) अणु
		काष्ठा v4l2_subdev *sd =
			media_entity_to_v4l2_subdev(pad->entity);

		fmt->which = V4L2_SUBDEV_FORMAT_ACTIVE;
		fmt->pad = pad->index;
		वापस v4l2_subdev_call(sd, pad, get_fmt, शून्य, fmt);
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक cio2_video_link_validate(काष्ठा media_link *link)
अणु
	काष्ठा video_device *vd = container_of(link->sink->entity,
						काष्ठा video_device, entity);
	काष्ठा cio2_queue *q = container_of(vd, काष्ठा cio2_queue, vdev);
	काष्ठा cio2_device *cio2 = video_get_drvdata(vd);
	काष्ठा v4l2_subdev_क्रमmat source_fmt;
	पूर्णांक ret;

	अगर (!media_entity_remote_pad(link->sink->entity->pads)) अणु
		dev_info(&cio2->pci_dev->dev,
			 "video node %s pad not connected\n", vd->name);
		वापस -ENOTCONN;
	पूर्ण

	ret = cio2_subdev_link_validate_get_क्रमmat(link->source, &source_fmt);
	अगर (ret < 0)
		वापस 0;

	अगर (source_fmt.क्रमmat.width != q->क्रमmat.width ||
	    source_fmt.क्रमmat.height != q->क्रमmat.height) अणु
		dev_err(&cio2->pci_dev->dev,
			"Wrong width or height %ux%u (%ux%u expected)\n",
			q->क्रमmat.width, q->क्रमmat.height,
			source_fmt.क्रमmat.width, source_fmt.क्रमmat.height);
		वापस -EINVAL;
	पूर्ण

	अगर (!cio2_find_क्रमmat(&q->क्रमmat.pixelक्रमmat, &source_fmt.क्रमmat.code))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_core_ops cio2_subdev_core_ops = अणु
	.subscribe_event = cio2_subdev_subscribe_event,
	.unsubscribe_event = v4l2_event_subdev_unsubscribe,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_पूर्णांकernal_ops cio2_subdev_पूर्णांकernal_ops = अणु
	.खोलो = cio2_subdev_खोलो,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops cio2_subdev_pad_ops = अणु
	.link_validate = v4l2_subdev_link_validate_शेष,
	.get_fmt = cio2_subdev_get_fmt,
	.set_fmt = cio2_subdev_set_fmt,
	.क्रमागत_mbus_code = cio2_subdev_क्रमागत_mbus_code,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops cio2_subdev_ops = अणु
	.core = &cio2_subdev_core_ops,
	.pad = &cio2_subdev_pad_ops,
पूर्ण;

/******* V4L2 sub-device asynchronous registration callbacks***********/

काष्ठा sensor_async_subdev अणु
	काष्ठा v4l2_async_subdev asd;
	काष्ठा csi2_bus_info csi2;
पूर्ण;

/* The .bound() notअगरier callback when a match is found */
अटल पूर्णांक cio2_notअगरier_bound(काष्ठा v4l2_async_notअगरier *notअगरier,
			       काष्ठा v4l2_subdev *sd,
			       काष्ठा v4l2_async_subdev *asd)
अणु
	काष्ठा cio2_device *cio2 = container_of(notअगरier,
					काष्ठा cio2_device, notअगरier);
	काष्ठा sensor_async_subdev *s_asd = container_of(asd,
					काष्ठा sensor_async_subdev, asd);
	काष्ठा cio2_queue *q;

	अगर (cio2->queue[s_asd->csi2.port].sensor)
		वापस -EBUSY;

	q = &cio2->queue[s_asd->csi2.port];

	q->csi2 = s_asd->csi2;
	q->sensor = sd;
	q->csi_rx_base = cio2->base + CIO2_REG_PIPE_BASE(q->csi2.port);

	वापस 0;
पूर्ण

/* The .unbind callback */
अटल व्योम cio2_notअगरier_unbind(काष्ठा v4l2_async_notअगरier *notअगरier,
				 काष्ठा v4l2_subdev *sd,
				 काष्ठा v4l2_async_subdev *asd)
अणु
	काष्ठा cio2_device *cio2 = container_of(notअगरier,
						काष्ठा cio2_device, notअगरier);
	काष्ठा sensor_async_subdev *s_asd = container_of(asd,
					काष्ठा sensor_async_subdev, asd);

	cio2->queue[s_asd->csi2.port].sensor = शून्य;
पूर्ण

/* .complete() is called after all subdevices have been located */
अटल पूर्णांक cio2_notअगरier_complete(काष्ठा v4l2_async_notअगरier *notअगरier)
अणु
	काष्ठा cio2_device *cio2 = container_of(notअगरier, काष्ठा cio2_device,
						notअगरier);
	काष्ठा sensor_async_subdev *s_asd;
	काष्ठा v4l2_async_subdev *asd;
	काष्ठा cio2_queue *q;
	अचिन्हित पूर्णांक pad;
	पूर्णांक ret;

	list_क्रम_each_entry(asd, &cio2->notअगरier.asd_list, asd_list) अणु
		s_asd = container_of(asd, काष्ठा sensor_async_subdev, asd);
		q = &cio2->queue[s_asd->csi2.port];

		क्रम (pad = 0; pad < q->sensor->entity.num_pads; pad++)
			अगर (q->sensor->entity.pads[pad].flags &
						MEDIA_PAD_FL_SOURCE)
				अवरोध;

		अगर (pad == q->sensor->entity.num_pads) अणु
			dev_err(&cio2->pci_dev->dev,
				"failed to find src pad for %s\n",
				q->sensor->name);
			वापस -ENXIO;
		पूर्ण

		ret = media_create_pad_link(
				&q->sensor->entity, pad,
				&q->subdev.entity, CIO2_PAD_SINK,
				0);
		अगर (ret) अणु
			dev_err(&cio2->pci_dev->dev,
				"failed to create link for %s\n",
				q->sensor->name);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस v4l2_device_रेजिस्टर_subdev_nodes(&cio2->v4l2_dev);
पूर्ण

अटल स्थिर काष्ठा v4l2_async_notअगरier_operations cio2_async_ops = अणु
	.bound = cio2_notअगरier_bound,
	.unbind = cio2_notअगरier_unbind,
	.complete = cio2_notअगरier_complete,
पूर्ण;

अटल पूर्णांक cio2_parse_firmware(काष्ठा cio2_device *cio2)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	क्रम (i = 0; i < CIO2_NUM_PORTS; i++) अणु
		काष्ठा v4l2_fwnode_endpoपूर्णांक vep = अणु
			.bus_type = V4L2_MBUS_CSI2_DPHY
		पूर्ण;
		काष्ठा sensor_async_subdev *s_asd;
		काष्ठा fwnode_handle *ep;

		ep = fwnode_graph_get_endpoपूर्णांक_by_id(
			dev_fwnode(&cio2->pci_dev->dev), i, 0,
			FWNODE_GRAPH_ENDPOINT_NEXT);

		अगर (!ep)
			जारी;

		ret = v4l2_fwnode_endpoपूर्णांक_parse(ep, &vep);
		अगर (ret)
			जाओ err_parse;

		s_asd = v4l2_async_notअगरier_add_fwnode_remote_subdev(
				&cio2->notअगरier, ep, काष्ठा sensor_async_subdev);
		अगर (IS_ERR(s_asd)) अणु
			ret = PTR_ERR(s_asd);
			जाओ err_parse;
		पूर्ण

		s_asd->csi2.port = vep.base.port;
		s_asd->csi2.lanes = vep.bus.mipi_csi2.num_data_lanes;

		fwnode_handle_put(ep);

		जारी;

err_parse:
		fwnode_handle_put(ep);
		वापस ret;
	पूर्ण

	/*
	 * Proceed even without sensors connected to allow the device to
	 * suspend.
	 */
	cio2->notअगरier.ops = &cio2_async_ops;
	ret = v4l2_async_notअगरier_रेजिस्टर(&cio2->v4l2_dev, &cio2->notअगरier);
	अगर (ret)
		dev_err(&cio2->pci_dev->dev,
			"failed to register async notifier : %d\n", ret);

	वापस ret;
पूर्ण

/**************** Queue initialization ****************/
अटल स्थिर काष्ठा media_entity_operations cio2_media_ops = अणु
	.link_validate = v4l2_subdev_link_validate,
पूर्ण;

अटल स्थिर काष्ठा media_entity_operations cio2_video_entity_ops = अणु
	.link_validate = cio2_video_link_validate,
पूर्ण;

अटल पूर्णांक cio2_queue_init(काष्ठा cio2_device *cio2, काष्ठा cio2_queue *q)
अणु
	अटल स्थिर u32 शेष_width = 1936;
	अटल स्थिर u32 शेष_height = 1096;
	स्थिर काष्ठा ipu3_cio2_fmt dflt_fmt = क्रमmats[0];

	काष्ठा video_device *vdev = &q->vdev;
	काष्ठा vb2_queue *vbq = &q->vbq;
	काष्ठा v4l2_subdev *subdev = &q->subdev;
	काष्ठा v4l2_mbus_framefmt *fmt;
	पूर्णांक r;

	/* Initialize miscellaneous variables */
	mutex_init(&q->lock);
	mutex_init(&q->subdev_lock);

	/* Initialize क्रमmats to शेष values */
	fmt = &q->subdev_fmt;
	fmt->width = शेष_width;
	fmt->height = शेष_height;
	fmt->code = dflt_fmt.mbus_code;
	fmt->field = V4L2_FIELD_NONE;

	q->क्रमmat.width = शेष_width;
	q->क्रमmat.height = शेष_height;
	q->क्रमmat.pixelक्रमmat = dflt_fmt.fourcc;
	q->क्रमmat.colorspace = V4L2_COLORSPACE_RAW;
	q->क्रमmat.field = V4L2_FIELD_NONE;
	q->क्रमmat.num_planes = 1;
	q->क्रमmat.plane_fmt[0].bytesperline =
				cio2_bytesperline(q->क्रमmat.width);
	q->क्रमmat.plane_fmt[0].sizeimage = q->क्रमmat.plane_fmt[0].bytesperline *
						q->क्रमmat.height;

	/* Initialize fbpt */
	r = cio2_fbpt_init(cio2, q);
	अगर (r)
		जाओ fail_fbpt;

	/* Initialize media entities */
	q->subdev_pads[CIO2_PAD_SINK].flags = MEDIA_PAD_FL_SINK |
		MEDIA_PAD_FL_MUST_CONNECT;
	q->subdev_pads[CIO2_PAD_SOURCE].flags = MEDIA_PAD_FL_SOURCE;
	subdev->entity.ops = &cio2_media_ops;
	subdev->पूर्णांकernal_ops = &cio2_subdev_पूर्णांकernal_ops;
	r = media_entity_pads_init(&subdev->entity, CIO2_PADS, q->subdev_pads);
	अगर (r) अणु
		dev_err(&cio2->pci_dev->dev,
			"failed initialize subdev media entity (%d)\n", r);
		जाओ fail_subdev_media_entity;
	पूर्ण

	q->vdev_pad.flags = MEDIA_PAD_FL_SINK | MEDIA_PAD_FL_MUST_CONNECT;
	vdev->entity.ops = &cio2_video_entity_ops;
	r = media_entity_pads_init(&vdev->entity, 1, &q->vdev_pad);
	अगर (r) अणु
		dev_err(&cio2->pci_dev->dev,
			"failed initialize videodev media entity (%d)\n", r);
		जाओ fail_vdev_media_entity;
	पूर्ण

	/* Initialize subdev */
	v4l2_subdev_init(subdev, &cio2_subdev_ops);
	subdev->flags = V4L2_SUBDEV_FL_HAS_DEVNODE | V4L2_SUBDEV_FL_HAS_EVENTS;
	subdev->owner = THIS_MODULE;
	snम_लिखो(subdev->name, माप(subdev->name),
		 CIO2_ENTITY_NAME " %td", q - cio2->queue);
	subdev->entity.function = MEDIA_ENT_F_VID_IF_BRIDGE;
	v4l2_set_subdevdata(subdev, cio2);
	r = v4l2_device_रेजिस्टर_subdev(&cio2->v4l2_dev, subdev);
	अगर (r) अणु
		dev_err(&cio2->pci_dev->dev,
			"failed initialize subdev (%d)\n", r);
		जाओ fail_subdev;
	पूर्ण

	/* Initialize vbq */
	vbq->type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
	vbq->io_modes = VB2_USERPTR | VB2_MMAP | VB2_DMABUF;
	vbq->ops = &cio2_vb2_ops;
	vbq->mem_ops = &vb2_dma_sg_memops;
	vbq->buf_काष्ठा_size = माप(काष्ठा cio2_buffer);
	vbq->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	vbq->min_buffers_needed = 1;
	vbq->drv_priv = cio2;
	vbq->lock = &q->lock;
	r = vb2_queue_init(vbq);
	अगर (r) अणु
		dev_err(&cio2->pci_dev->dev,
			"failed to initialize videobuf2 queue (%d)\n", r);
		जाओ fail_subdev;
	पूर्ण

	/* Initialize vdev */
	snम_लिखो(vdev->name, माप(vdev->name),
		 "%s %td", CIO2_NAME, q - cio2->queue);
	vdev->release = video_device_release_empty;
	vdev->fops = &cio2_v4l2_fops;
	vdev->ioctl_ops = &cio2_v4l2_ioctl_ops;
	vdev->lock = &cio2->lock;
	vdev->v4l2_dev = &cio2->v4l2_dev;
	vdev->queue = &q->vbq;
	vdev->device_caps = V4L2_CAP_VIDEO_CAPTURE_MPLANE | V4L2_CAP_STREAMING;
	video_set_drvdata(vdev, cio2);
	r = video_रेजिस्टर_device(vdev, VFL_TYPE_VIDEO, -1);
	अगर (r) अणु
		dev_err(&cio2->pci_dev->dev,
			"failed to register video device (%d)\n", r);
		जाओ fail_vdev;
	पूर्ण

	/* Create link from CIO2 subdev to output node */
	r = media_create_pad_link(
		&subdev->entity, CIO2_PAD_SOURCE, &vdev->entity, 0,
		MEDIA_LNK_FL_ENABLED | MEDIA_LNK_FL_IMMUTABLE);
	अगर (r)
		जाओ fail_link;

	वापस 0;

fail_link:
	vb2_video_unरेजिस्टर_device(&q->vdev);
fail_vdev:
	v4l2_device_unरेजिस्टर_subdev(subdev);
fail_subdev:
	media_entity_cleanup(&vdev->entity);
fail_vdev_media_entity:
	media_entity_cleanup(&subdev->entity);
fail_subdev_media_entity:
	cio2_fbpt_निकास(q, &cio2->pci_dev->dev);
fail_fbpt:
	mutex_destroy(&q->subdev_lock);
	mutex_destroy(&q->lock);

	वापस r;
पूर्ण

अटल व्योम cio2_queue_निकास(काष्ठा cio2_device *cio2, काष्ठा cio2_queue *q)
अणु
	vb2_video_unरेजिस्टर_device(&q->vdev);
	media_entity_cleanup(&q->vdev.entity);
	v4l2_device_unरेजिस्टर_subdev(&q->subdev);
	media_entity_cleanup(&q->subdev.entity);
	cio2_fbpt_निकास(q, &cio2->pci_dev->dev);
	mutex_destroy(&q->subdev_lock);
	mutex_destroy(&q->lock);
पूर्ण

अटल पूर्णांक cio2_queues_init(काष्ठा cio2_device *cio2)
अणु
	पूर्णांक i, r;

	क्रम (i = 0; i < CIO2_QUEUES; i++) अणु
		r = cio2_queue_init(cio2, &cio2->queue[i]);
		अगर (r)
			अवरोध;
	पूर्ण

	अगर (i == CIO2_QUEUES)
		वापस 0;

	क्रम (i--; i >= 0; i--)
		cio2_queue_निकास(cio2, &cio2->queue[i]);

	वापस r;
पूर्ण

अटल व्योम cio2_queues_निकास(काष्ठा cio2_device *cio2)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < CIO2_QUEUES; i++)
		cio2_queue_निकास(cio2, &cio2->queue[i]);
पूर्ण

अटल पूर्णांक cio2_check_fwnode_graph(काष्ठा fwnode_handle *fwnode)
अणु
	काष्ठा fwnode_handle *endpoपूर्णांक;

	अगर (IS_ERR_OR_शून्य(fwnode))
		वापस -EINVAL;

	endpoपूर्णांक = fwnode_graph_get_next_endpoपूर्णांक(fwnode, शून्य);
	अगर (endpoपूर्णांक) अणु
		fwnode_handle_put(endpoपूर्णांक);
		वापस 0;
	पूर्ण

	वापस cio2_check_fwnode_graph(fwnode->secondary);
पूर्ण

/**************** PCI पूर्णांकerface ****************/

अटल पूर्णांक cio2_pci_probe(काष्ठा pci_dev *pci_dev,
			  स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा fwnode_handle *fwnode = dev_fwnode(&pci_dev->dev);
	काष्ठा cio2_device *cio2;
	पूर्णांक r;

	cio2 = devm_kzalloc(&pci_dev->dev, माप(*cio2), GFP_KERNEL);
	अगर (!cio2)
		वापस -ENOMEM;
	cio2->pci_dev = pci_dev;

	/*
	 * On some platक्रमms no connections to sensors are defined in firmware,
	 * अगर the device has no endpoपूर्णांकs then we can try to build those as
	 * software_nodes parsed from SSDB.
	 */
	r = cio2_check_fwnode_graph(fwnode);
	अगर (r) अणु
		अगर (fwnode && !IS_ERR_OR_शून्य(fwnode->secondary)) अणु
			dev_err(&pci_dev->dev, "fwnode graph has no endpoints connected\n");
			वापस -EINVAL;
		पूर्ण

		r = cio2_bridge_init(pci_dev);
		अगर (r)
			वापस r;
	पूर्ण

	r = pcim_enable_device(pci_dev);
	अगर (r) अणु
		dev_err(&pci_dev->dev, "failed to enable device (%d)\n", r);
		वापस r;
	पूर्ण

	dev_info(&pci_dev->dev, "device 0x%x (rev: 0x%x)\n",
		 pci_dev->device, pci_dev->revision);

	r = pcim_iomap_regions(pci_dev, 1 << CIO2_PCI_BAR, pci_name(pci_dev));
	अगर (r) अणु
		dev_err(&pci_dev->dev, "failed to remap I/O memory (%d)\n", r);
		वापस -ENODEV;
	पूर्ण

	cio2->base = pcim_iomap_table(pci_dev)[CIO2_PCI_BAR];

	pci_set_drvdata(pci_dev, cio2);

	pci_set_master(pci_dev);

	r = pci_set_dma_mask(pci_dev, CIO2_DMA_MASK);
	अगर (r) अणु
		dev_err(&pci_dev->dev, "failed to set DMA mask (%d)\n", r);
		वापस -ENODEV;
	पूर्ण

	r = pci_enable_msi(pci_dev);
	अगर (r) अणु
		dev_err(&pci_dev->dev, "failed to enable MSI (%d)\n", r);
		वापस r;
	पूर्ण

	r = cio2_fbpt_init_dummy(cio2);
	अगर (r)
		वापस r;

	mutex_init(&cio2->lock);

	cio2->media_dev.dev = &cio2->pci_dev->dev;
	strscpy(cio2->media_dev.model, CIO2_DEVICE_NAME,
		माप(cio2->media_dev.model));
	snम_लिखो(cio2->media_dev.bus_info, माप(cio2->media_dev.bus_info),
		 "PCI:%s", pci_name(cio2->pci_dev));
	cio2->media_dev.hw_revision = 0;

	media_device_init(&cio2->media_dev);
	r = media_device_रेजिस्टर(&cio2->media_dev);
	अगर (r < 0)
		जाओ fail_mutex_destroy;

	cio2->v4l2_dev.mdev = &cio2->media_dev;
	r = v4l2_device_रेजिस्टर(&pci_dev->dev, &cio2->v4l2_dev);
	अगर (r) अणु
		dev_err(&pci_dev->dev,
			"failed to register V4L2 device (%d)\n", r);
		जाओ fail_media_device_unरेजिस्टर;
	पूर्ण

	r = cio2_queues_init(cio2);
	अगर (r)
		जाओ fail_v4l2_device_unरेजिस्टर;

	v4l2_async_notअगरier_init(&cio2->notअगरier);

	/* Register notअगरier क्रम subdevices we care */
	r = cio2_parse_firmware(cio2);
	अगर (r)
		जाओ fail_clean_notअगरier;

	r = devm_request_irq(&pci_dev->dev, pci_dev->irq, cio2_irq,
			     IRQF_SHARED, CIO2_NAME, cio2);
	अगर (r) अणु
		dev_err(&pci_dev->dev, "failed to request IRQ (%d)\n", r);
		जाओ fail_clean_notअगरier;
	पूर्ण

	pm_runसमय_put_noidle(&pci_dev->dev);
	pm_runसमय_allow(&pci_dev->dev);

	वापस 0;

fail_clean_notअगरier:
	v4l2_async_notअगरier_unरेजिस्टर(&cio2->notअगरier);
	v4l2_async_notअगरier_cleanup(&cio2->notअगरier);
	cio2_queues_निकास(cio2);
fail_v4l2_device_unरेजिस्टर:
	v4l2_device_unरेजिस्टर(&cio2->v4l2_dev);
fail_media_device_unरेजिस्टर:
	media_device_unरेजिस्टर(&cio2->media_dev);
	media_device_cleanup(&cio2->media_dev);
fail_mutex_destroy:
	mutex_destroy(&cio2->lock);
	cio2_fbpt_निकास_dummy(cio2);

	वापस r;
पूर्ण

अटल व्योम cio2_pci_हटाओ(काष्ठा pci_dev *pci_dev)
अणु
	काष्ठा cio2_device *cio2 = pci_get_drvdata(pci_dev);

	media_device_unरेजिस्टर(&cio2->media_dev);
	v4l2_async_notअगरier_unरेजिस्टर(&cio2->notअगरier);
	v4l2_async_notअगरier_cleanup(&cio2->notअगरier);
	cio2_queues_निकास(cio2);
	cio2_fbpt_निकास_dummy(cio2);
	v4l2_device_unरेजिस्टर(&cio2->v4l2_dev);
	media_device_cleanup(&cio2->media_dev);
	mutex_destroy(&cio2->lock);
पूर्ण

अटल पूर्णांक __maybe_unused cio2_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pci_dev = to_pci_dev(dev);
	काष्ठा cio2_device *cio2 = pci_get_drvdata(pci_dev);
	व्योम __iomem *स्थिर base = cio2->base;
	u16 pm;

	ग_लिखोl(CIO2_D0I3C_I3, base + CIO2_REG_D0I3C);
	dev_dbg(dev, "cio2 runtime suspend.\n");

	pci_पढ़ो_config_word(pci_dev, pci_dev->pm_cap + CIO2_PMCSR_OFFSET, &pm);
	pm = (pm >> CIO2_PMCSR_D0D3_SHIFT) << CIO2_PMCSR_D0D3_SHIFT;
	pm |= CIO2_PMCSR_D3;
	pci_ग_लिखो_config_word(pci_dev, pci_dev->pm_cap + CIO2_PMCSR_OFFSET, pm);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused cio2_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pci_dev = to_pci_dev(dev);
	काष्ठा cio2_device *cio2 = pci_get_drvdata(pci_dev);
	व्योम __iomem *स्थिर base = cio2->base;
	u16 pm;

	ग_लिखोl(CIO2_D0I3C_RR, base + CIO2_REG_D0I3C);
	dev_dbg(dev, "cio2 runtime resume.\n");

	pci_पढ़ो_config_word(pci_dev, pci_dev->pm_cap + CIO2_PMCSR_OFFSET, &pm);
	pm = (pm >> CIO2_PMCSR_D0D3_SHIFT) << CIO2_PMCSR_D0D3_SHIFT;
	pci_ग_लिखो_config_word(pci_dev, pci_dev->pm_cap + CIO2_PMCSR_OFFSET, pm);

	वापस 0;
पूर्ण

/*
 * Helper function to advance all the elements of a circular buffer by "start"
 * positions
 */
अटल व्योम arrange(व्योम *ptr, माप_प्रकार elem_size, माप_प्रकार elems, माप_प्रकार start)
अणु
	काष्ठा अणु
		माप_प्रकार begin, end;
	पूर्ण arr[2] = अणु
		अणु 0, start - 1 पूर्ण,
		अणु start, elems - 1 पूर्ण,
	पूर्ण;

#घोषणा CHUNK_SIZE(a) ((a)->end - (a)->begin + 1)

	/* Loop as दीर्घ as we have out-of-place entries */
	जबतक (CHUNK_SIZE(&arr[0]) && CHUNK_SIZE(&arr[1])) अणु
		माप_प्रकार size0, i;

		/*
		 * Find the number of entries that can be arranged on this
		 * iteration.
		 */
		size0 = min(CHUNK_SIZE(&arr[0]), CHUNK_SIZE(&arr[1]));

		/* Swap the entries in two parts of the array. */
		क्रम (i = 0; i < size0; i++) अणु
			u8 *d = ptr + elem_size * (arr[1].begin + i);
			u8 *s = ptr + elem_size * (arr[0].begin + i);
			माप_प्रकार j;

			क्रम (j = 0; j < elem_size; j++)
				swap(d[j], s[j]);
		पूर्ण

		अगर (CHUNK_SIZE(&arr[0]) > CHUNK_SIZE(&arr[1])) अणु
			/* The end of the first array reमुख्यs unarranged. */
			arr[0].begin += size0;
		पूर्ण अन्यथा अणु
			/*
			 * The first array is fully arranged so we proceed
			 * handling the next one.
			 */
			arr[0].begin = arr[1].begin;
			arr[0].end = arr[1].begin + size0 - 1;
			arr[1].begin += size0;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम cio2_fbpt_rearrange(काष्ठा cio2_device *cio2, काष्ठा cio2_queue *q)
अणु
	अचिन्हित पूर्णांक i, j;

	क्रम (i = 0, j = q->bufs_first; i < CIO2_MAX_BUFFERS;
		i++, j = (j + 1) % CIO2_MAX_BUFFERS)
		अगर (q->bufs[j])
			अवरोध;

	अगर (i == CIO2_MAX_BUFFERS)
		वापस;

	अगर (j) अणु
		arrange(q->fbpt, माप(काष्ठा cio2_fbpt_entry) * CIO2_MAX_LOPS,
			CIO2_MAX_BUFFERS, j);
		arrange(q->bufs, माप(काष्ठा cio2_buffer *),
			CIO2_MAX_BUFFERS, j);
	पूर्ण

	/*
	 * DMA clears the valid bit when accessing the buffer.
	 * When stopping stream in suspend callback, some of the buffers
	 * may be in invalid state. After resume, when DMA meets the invalid
	 * buffer, it will halt and stop receiving new data.
	 * To aव्योम DMA halting, set the valid bit क्रम all buffers in FBPT.
	 */
	क्रम (i = 0; i < CIO2_MAX_BUFFERS; i++)
		cio2_fbpt_entry_enable(cio2, q->fbpt + i * CIO2_MAX_LOPS);
पूर्ण

अटल पूर्णांक __maybe_unused cio2_suspend(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pci_dev = to_pci_dev(dev);
	काष्ठा cio2_device *cio2 = pci_get_drvdata(pci_dev);
	काष्ठा cio2_queue *q = cio2->cur_queue;

	dev_dbg(dev, "cio2 suspend\n");
	अगर (!cio2->streaming)
		वापस 0;

	/* Stop stream */
	cio2_hw_निकास(cio2, q);
	synchronize_irq(pci_dev->irq);

	pm_runसमय_क्रमce_suspend(dev);

	/*
	 * Upon resume, hw starts to process the fbpt entries from beginning,
	 * so relocate the queued buffs to the fbpt head beक्रमe suspend.
	 */
	cio2_fbpt_rearrange(cio2, q);
	q->bufs_first = 0;
	q->bufs_next = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused cio2_resume(काष्ठा device *dev)
अणु
	काष्ठा cio2_device *cio2 = dev_get_drvdata(dev);
	काष्ठा cio2_queue *q = cio2->cur_queue;
	पूर्णांक r;

	dev_dbg(dev, "cio2 resume\n");
	अगर (!cio2->streaming)
		वापस 0;
	/* Start stream */
	r = pm_runसमय_क्रमce_resume(&cio2->pci_dev->dev);
	अगर (r < 0) अणु
		dev_err(&cio2->pci_dev->dev,
			"failed to set power %d\n", r);
		वापस r;
	पूर्ण

	r = cio2_hw_init(cio2, q);
	अगर (r)
		dev_err(dev, "fail to init cio2 hw\n");

	वापस r;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops cio2_pm_ops = अणु
	SET_RUNTIME_PM_OPS(&cio2_runसमय_suspend, &cio2_runसमय_resume, शून्य)
	SET_SYSTEM_SLEEP_PM_OPS(&cio2_suspend, &cio2_resume)
पूर्ण;

अटल स्थिर काष्ठा pci_device_id cio2_pci_id_table[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, CIO2_PCI_ID) पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, cio2_pci_id_table);

अटल काष्ठा pci_driver cio2_pci_driver = अणु
	.name = CIO2_NAME,
	.id_table = cio2_pci_id_table,
	.probe = cio2_pci_probe,
	.हटाओ = cio2_pci_हटाओ,
	.driver = अणु
		.pm = &cio2_pm_ops,
	पूर्ण,
पूर्ण;

module_pci_driver(cio2_pci_driver);

MODULE_AUTHOR("Tuukka Toivonen <tuukka.toivonen@intel.com>");
MODULE_AUTHOR("Tianshu Qiu <tian.shu.qiu@intel.com>");
MODULE_AUTHOR("Jian Xu Zheng");
MODULE_AUTHOR("Yuning Pu <yuning.pu@intel.com>");
MODULE_AUTHOR("Yong Zhi <yong.zhi@intel.com>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("IPU3 CIO2 driver");
