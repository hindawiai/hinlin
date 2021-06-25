<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम Xilinx MIPI CSI-2 Rx Subप्रणाली
 *
 * Copyright (C) 2016 - 2020 Xilinx, Inc.
 *
 * Contacts: Vishal Sagar <vishal.sagar@xilinx.com>
 *
 */
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/v4l2-subdev.h>
#समावेश <media/media-entity.h>
#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-fwnode.h>
#समावेश <media/v4l2-subdev.h>
#समावेश "xilinx-vip.h"

/* Register रेजिस्टर map */
#घोषणा XCSI_CCR_OFFSET		0x00
#घोषणा XCSI_CCR_SOFTRESET	BIT(1)
#घोषणा XCSI_CCR_ENABLE		BIT(0)

#घोषणा XCSI_PCR_OFFSET		0x04
#घोषणा XCSI_PCR_MAXLANES_MASK	GENMASK(4, 3)
#घोषणा XCSI_PCR_ACTLANES_MASK	GENMASK(1, 0)

#घोषणा XCSI_CSR_OFFSET		0x10
#घोषणा XCSI_CSR_PKTCNT		GENMASK(31, 16)
#घोषणा XCSI_CSR_SPFIFOFULL	BIT(3)
#घोषणा XCSI_CSR_SPFIFONE	BIT(2)
#घोषणा XCSI_CSR_SLBF		BIT(1)
#घोषणा XCSI_CSR_RIPCD		BIT(0)

#घोषणा XCSI_GIER_OFFSET	0x20
#घोषणा XCSI_GIER_GIE		BIT(0)

#घोषणा XCSI_ISR_OFFSET		0x24
#घोषणा XCSI_IER_OFFSET		0x28

#घोषणा XCSI_ISR_FR		BIT(31)
#घोषणा XCSI_ISR_VCXFE		BIT(30)
#घोषणा XCSI_ISR_WCC		BIT(22)
#घोषणा XCSI_ISR_ILC		BIT(21)
#घोषणा XCSI_ISR_SPFIFOF	BIT(20)
#घोषणा XCSI_ISR_SPFIFONE	BIT(19)
#घोषणा XCSI_ISR_SLBF		BIT(18)
#घोषणा XCSI_ISR_STOP		BIT(17)
#घोषणा XCSI_ISR_SOTERR		BIT(13)
#घोषणा XCSI_ISR_SOTSYNCERR	BIT(12)
#घोषणा XCSI_ISR_ECC2BERR	BIT(11)
#घोषणा XCSI_ISR_ECC1BERR	BIT(10)
#घोषणा XCSI_ISR_CRCERR		BIT(9)
#घोषणा XCSI_ISR_DATAIDERR	BIT(8)
#घोषणा XCSI_ISR_VC3FSYNCERR	BIT(7)
#घोषणा XCSI_ISR_VC3FLVLERR	BIT(6)
#घोषणा XCSI_ISR_VC2FSYNCERR	BIT(5)
#घोषणा XCSI_ISR_VC2FLVLERR	BIT(4)
#घोषणा XCSI_ISR_VC1FSYNCERR	BIT(3)
#घोषणा XCSI_ISR_VC1FLVLERR	BIT(2)
#घोषणा XCSI_ISR_VC0FSYNCERR	BIT(1)
#घोषणा XCSI_ISR_VC0FLVLERR	BIT(0)

#घोषणा XCSI_ISR_ALLINTR_MASK	(0xc07e3fff)

/*
 * Removed VCXFE mask as it करोesn't exist in IER
 * Removed STOP state irq as this will keep driver in irq handler only
 */
#घोषणा XCSI_IER_INTR_MASK	(XCSI_ISR_ALLINTR_MASK &\
				 ~(XCSI_ISR_STOP | XCSI_ISR_VCXFE))

#घोषणा XCSI_SPKTR_OFFSET	0x30
#घोषणा XCSI_SPKTR_DATA		GENMASK(23, 8)
#घोषणा XCSI_SPKTR_VC		GENMASK(7, 6)
#घोषणा XCSI_SPKTR_DT		GENMASK(5, 0)
#घोषणा XCSI_SPKT_FIFO_DEPTH	31

#घोषणा XCSI_VCXR_OFFSET	0x34
#घोषणा XCSI_VCXR_VCERR		GENMASK(23, 0)
#घोषणा XCSI_VCXR_FSYNCERR	BIT(1)
#घोषणा XCSI_VCXR_FLVLERR	BIT(0)

#घोषणा XCSI_CLKINFR_OFFSET	0x3C
#घोषणा XCSI_CLKINFR_STOP	BIT(1)

#घोषणा XCSI_DLXINFR_OFFSET	0x40
#घोषणा XCSI_DLXINFR_STOP	BIT(5)
#घोषणा XCSI_DLXINFR_SOTERR	BIT(1)
#घोषणा XCSI_DLXINFR_SOTSYNCERR	BIT(0)
#घोषणा XCSI_MAXDL_COUNT	0x4

#घोषणा XCSI_VCXINF1R_OFFSET		0x60
#घोषणा XCSI_VCXINF1R_LINECOUNT		GENMASK(31, 16)
#घोषणा XCSI_VCXINF1R_LINECOUNT_SHIFT	16
#घोषणा XCSI_VCXINF1R_BYTECOUNT		GENMASK(15, 0)

#घोषणा XCSI_VCXINF2R_OFFSET	0x64
#घोषणा XCSI_VCXINF2R_DT	GENMASK(5, 0)
#घोषणा XCSI_MAXVCX_COUNT	16

/*
 * Sink pad connected to sensor source pad.
 * Source pad connected to next module like demosaic.
 */
#घोषणा XCSI_MEDIA_PADS		2
#घोषणा XCSI_DEFAULT_WIDTH	1920
#घोषणा XCSI_DEFAULT_HEIGHT	1080

/* MIPI CSI-2 Data Types from spec */
#घोषणा XCSI_DT_YUV4228B	0x1e
#घोषणा XCSI_DT_YUV42210B	0x1f
#घोषणा XCSI_DT_RGB444		0x20
#घोषणा XCSI_DT_RGB555		0x21
#घोषणा XCSI_DT_RGB565		0x22
#घोषणा XCSI_DT_RGB666		0x23
#घोषणा XCSI_DT_RGB888		0x24
#घोषणा XCSI_DT_RAW6		0x28
#घोषणा XCSI_DT_RAW7		0x29
#घोषणा XCSI_DT_RAW8		0x2a
#घोषणा XCSI_DT_RAW10		0x2b
#घोषणा XCSI_DT_RAW12		0x2c
#घोषणा XCSI_DT_RAW14		0x2d
#घोषणा XCSI_DT_RAW16		0x2e
#घोषणा XCSI_DT_RAW20		0x2f

#घोषणा XCSI_VCX_START		4
#घोषणा XCSI_MAX_VC		4
#घोषणा XCSI_MAX_VCX		16

#घोषणा XCSI_NEXTREG_OFFSET	4

/* There are 2 events frame sync and frame level error per VC */
#घोषणा XCSI_VCX_NUM_EVENTS	((XCSI_MAX_VCX - XCSI_MAX_VC) * 2)

/**
 * काष्ठा xcsi2rxss_event - Event log काष्ठाure
 * @mask: Event mask
 * @name: Name of the event
 */
काष्ठा xcsi2rxss_event अणु
	u32 mask;
	स्थिर अक्षर *name;
पूर्ण;

अटल स्थिर काष्ठा xcsi2rxss_event xcsi2rxss_events[] = अणु
	अणु XCSI_ISR_FR, "Frame Received" पूर्ण,
	अणु XCSI_ISR_VCXFE, "VCX Frame Errors" पूर्ण,
	अणु XCSI_ISR_WCC, "Word Count Errors" पूर्ण,
	अणु XCSI_ISR_ILC, "Invalid Lane Count Error" पूर्ण,
	अणु XCSI_ISR_SPFIFOF, "Short Packet FIFO OverFlow Error" पूर्ण,
	अणु XCSI_ISR_SPFIFONE, "Short Packet FIFO Not Empty" पूर्ण,
	अणु XCSI_ISR_SLBF, "Streamline Buffer Full Error" पूर्ण,
	अणु XCSI_ISR_STOP, "Lane Stop State" पूर्ण,
	अणु XCSI_ISR_SOTERR, "SOT Error" पूर्ण,
	अणु XCSI_ISR_SOTSYNCERR, "SOT Sync Error" पूर्ण,
	अणु XCSI_ISR_ECC2BERR, "2 Bit ECC Unrecoverable Error" पूर्ण,
	अणु XCSI_ISR_ECC1BERR, "1 Bit ECC Recoverable Error" पूर्ण,
	अणु XCSI_ISR_CRCERR, "CRC Error" पूर्ण,
	अणु XCSI_ISR_DATAIDERR, "Data Id Error" पूर्ण,
	अणु XCSI_ISR_VC3FSYNCERR, "Virtual Channel 3 Frame Sync Error" पूर्ण,
	अणु XCSI_ISR_VC3FLVLERR, "Virtual Channel 3 Frame Level Error" पूर्ण,
	अणु XCSI_ISR_VC2FSYNCERR, "Virtual Channel 2 Frame Sync Error" पूर्ण,
	अणु XCSI_ISR_VC2FLVLERR, "Virtual Channel 2 Frame Level Error" पूर्ण,
	अणु XCSI_ISR_VC1FSYNCERR, "Virtual Channel 1 Frame Sync Error" पूर्ण,
	अणु XCSI_ISR_VC1FLVLERR, "Virtual Channel 1 Frame Level Error" पूर्ण,
	अणु XCSI_ISR_VC0FSYNCERR, "Virtual Channel 0 Frame Sync Error" पूर्ण,
	अणु XCSI_ISR_VC0FLVLERR, "Virtual Channel 0 Frame Level Error" पूर्ण
पूर्ण;

#घोषणा XCSI_NUM_EVENTS		ARRAY_SIZE(xcsi2rxss_events)

/*
 * This table provides a mapping between CSI-2 Data type
 * and media bus क्रमmats
 */
अटल स्थिर u32 xcsi2dt_mbus_lut[][2] = अणु
	अणु XCSI_DT_YUV4228B, MEDIA_BUS_FMT_UYVY8_1X16 पूर्ण,
	अणु XCSI_DT_YUV42210B, MEDIA_BUS_FMT_UYVY10_1X20 पूर्ण,
	अणु XCSI_DT_RGB444, 0 पूर्ण,
	अणु XCSI_DT_RGB555, 0 पूर्ण,
	अणु XCSI_DT_RGB565, 0 पूर्ण,
	अणु XCSI_DT_RGB666, 0 पूर्ण,
	अणु XCSI_DT_RGB888, MEDIA_BUS_FMT_RBG888_1X24 पूर्ण,
	अणु XCSI_DT_RAW6, 0 पूर्ण,
	अणु XCSI_DT_RAW7, 0 पूर्ण,
	अणु XCSI_DT_RAW8, MEDIA_BUS_FMT_SRGGB8_1X8 पूर्ण,
	अणु XCSI_DT_RAW8, MEDIA_BUS_FMT_SBGGR8_1X8 पूर्ण,
	अणु XCSI_DT_RAW8, MEDIA_BUS_FMT_SGBRG8_1X8 पूर्ण,
	अणु XCSI_DT_RAW8, MEDIA_BUS_FMT_SGRBG8_1X8 पूर्ण,
	अणु XCSI_DT_RAW10, MEDIA_BUS_FMT_SRGGB10_1X10 पूर्ण,
	अणु XCSI_DT_RAW10, MEDIA_BUS_FMT_SBGGR10_1X10 पूर्ण,
	अणु XCSI_DT_RAW10, MEDIA_BUS_FMT_SGBRG10_1X10 पूर्ण,
	अणु XCSI_DT_RAW10, MEDIA_BUS_FMT_SGRBG10_1X10 पूर्ण,
	अणु XCSI_DT_RAW12, MEDIA_BUS_FMT_SRGGB12_1X12 पूर्ण,
	अणु XCSI_DT_RAW12, MEDIA_BUS_FMT_SBGGR12_1X12 पूर्ण,
	अणु XCSI_DT_RAW12, MEDIA_BUS_FMT_SGBRG12_1X12 पूर्ण,
	अणु XCSI_DT_RAW12, MEDIA_BUS_FMT_SGRBG12_1X12 पूर्ण,
	अणु XCSI_DT_RAW16, MEDIA_BUS_FMT_SRGGB16_1X16 पूर्ण,
	अणु XCSI_DT_RAW16, MEDIA_BUS_FMT_SBGGR16_1X16 पूर्ण,
	अणु XCSI_DT_RAW16, MEDIA_BUS_FMT_SGBRG16_1X16 पूर्ण,
	अणु XCSI_DT_RAW16, MEDIA_BUS_FMT_SGRBG16_1X16 पूर्ण,
	अणु XCSI_DT_RAW20, 0 पूर्ण,
पूर्ण;

/**
 * काष्ठा xcsi2rxss_state - CSI-2 Rx Subप्रणाली device काष्ठाure
 * @subdev: The v4l2 subdev काष्ठाure
 * @क्रमmat: Active V4L2 क्रमmats on each pad
 * @शेष_क्रमmat: Default V4L2 क्रमmat
 * @events: counter क्रम events
 * @vcx_events: counter क्रम vcx_events
 * @dev: Platक्रमm काष्ठाure
 * @rsubdev: Remote subdev connected to sink pad
 * @rst_gpio: reset to video_aresetn
 * @clks: array of घड़ीs
 * @iomem: Base address of subप्रणाली
 * @max_num_lanes: Maximum number of lanes present
 * @datatype: Data type filter
 * @lock: mutex क्रम accessing this काष्ठाure
 * @pads: media pads
 * @streaming: Flag क्रम storing streaming state
 * @enable_active_lanes: If number of active lanes can be modअगरied
 * @en_vcx: If more than 4 VC are enabled
 *
 * This काष्ठाure contains the device driver related parameters
 */
काष्ठा xcsi2rxss_state अणु
	काष्ठा v4l2_subdev subdev;
	काष्ठा v4l2_mbus_framefmt क्रमmat;
	काष्ठा v4l2_mbus_framefmt शेष_क्रमmat;
	u32 events[XCSI_NUM_EVENTS];
	u32 vcx_events[XCSI_VCX_NUM_EVENTS];
	काष्ठा device *dev;
	काष्ठा v4l2_subdev *rsubdev;
	काष्ठा gpio_desc *rst_gpio;
	काष्ठा clk_bulk_data *clks;
	व्योम __iomem *iomem;
	u32 max_num_lanes;
	u32 datatype;
	/* used to protect access to this काष्ठा */
	काष्ठा mutex lock;
	काष्ठा media_pad pads[XCSI_MEDIA_PADS];
	bool streaming;
	bool enable_active_lanes;
	bool en_vcx;
पूर्ण;

अटल स्थिर काष्ठा clk_bulk_data xcsi2rxss_clks[] = अणु
	अणु .id = "lite_aclk" पूर्ण,
	अणु .id = "video_aclk" पूर्ण,
पूर्ण;

अटल अंतरभूत काष्ठा xcsi2rxss_state *
to_xcsi2rxssstate(काष्ठा v4l2_subdev *subdev)
अणु
	वापस container_of(subdev, काष्ठा xcsi2rxss_state, subdev);
पूर्ण

/*
 * Register related operations
 */
अटल अंतरभूत u32 xcsi2rxss_पढ़ो(काष्ठा xcsi2rxss_state *xcsi2rxss, u32 addr)
अणु
	वापस ioपढ़ो32(xcsi2rxss->iomem + addr);
पूर्ण

अटल अंतरभूत व्योम xcsi2rxss_ग_लिखो(काष्ठा xcsi2rxss_state *xcsi2rxss, u32 addr,
				   u32 value)
अणु
	ioग_लिखो32(value, xcsi2rxss->iomem + addr);
पूर्ण

अटल अंतरभूत व्योम xcsi2rxss_clr(काष्ठा xcsi2rxss_state *xcsi2rxss, u32 addr,
				 u32 clr)
अणु
	xcsi2rxss_ग_लिखो(xcsi2rxss, addr,
			xcsi2rxss_पढ़ो(xcsi2rxss, addr) & ~clr);
पूर्ण

अटल अंतरभूत व्योम xcsi2rxss_set(काष्ठा xcsi2rxss_state *xcsi2rxss, u32 addr,
				 u32 set)
अणु
	xcsi2rxss_ग_लिखो(xcsi2rxss, addr, xcsi2rxss_पढ़ो(xcsi2rxss, addr) | set);
पूर्ण

/*
 * This function वापसs the nth mbus क्रम a data type.
 * In हाल of error, mbus code वापसed is 0.
 */
अटल u32 xcsi2rxss_get_nth_mbus(u32 dt, u32 n)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(xcsi2dt_mbus_lut); i++) अणु
		अगर (xcsi2dt_mbus_lut[i][0] == dt) अणु
			अगर (n-- == 0)
				वापस xcsi2dt_mbus_lut[i][1];
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* This वापसs the data type क्रम a media bus क्रमmat अन्यथा 0 */
अटल u32 xcsi2rxss_get_dt(u32 mbus)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(xcsi2dt_mbus_lut); i++) अणु
		अगर (xcsi2dt_mbus_lut[i][1] == mbus)
			वापस xcsi2dt_mbus_lut[i][0];
	पूर्ण

	वापस 0;
पूर्ण

/**
 * xcsi2rxss_soft_reset - Does a soft reset of the MIPI CSI-2 Rx Subप्रणाली
 * @state: Xilinx CSI-2 Rx Subप्रणाली काष्ठाure poपूर्णांकer
 *
 * Core takes less than 100 video घड़ी cycles to reset.
 * So a larger समयout value is chosen क्रम margin.
 *
 * Return: 0 - on success OR -ETIME अगर reset बार out
 */
अटल पूर्णांक xcsi2rxss_soft_reset(काष्ठा xcsi2rxss_state *state)
अणु
	u32 समयout = 1000; /* us */

	xcsi2rxss_set(state, XCSI_CCR_OFFSET, XCSI_CCR_SOFTRESET);

	जबतक (xcsi2rxss_पढ़ो(state, XCSI_CSR_OFFSET) & XCSI_CSR_RIPCD) अणु
		अगर (समयout == 0) अणु
			dev_err(state->dev, "soft reset timed out!\n");
			वापस -ETIME;
		पूर्ण

		समयout--;
		udelay(1);
	पूर्ण

	xcsi2rxss_clr(state, XCSI_CCR_OFFSET, XCSI_CCR_SOFTRESET);
	वापस 0;
पूर्ण

अटल व्योम xcsi2rxss_hard_reset(काष्ठा xcsi2rxss_state *state)
अणु
	अगर (!state->rst_gpio)
		वापस;

	/* minimum of 40 dphy_clk_200M cycles */
	gpiod_set_value_cansleep(state->rst_gpio, 1);
	usleep_range(1, 2);
	gpiod_set_value_cansleep(state->rst_gpio, 0);
पूर्ण

अटल व्योम xcsi2rxss_reset_event_counters(काष्ठा xcsi2rxss_state *state)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < XCSI_NUM_EVENTS; i++)
		state->events[i] = 0;

	क्रम (i = 0; i < XCSI_VCX_NUM_EVENTS; i++)
		state->vcx_events[i] = 0;
पूर्ण

/* Prपूर्णांक event counters */
अटल व्योम xcsi2rxss_log_counters(काष्ठा xcsi2rxss_state *state)
अणु
	काष्ठा device *dev = state->dev;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < XCSI_NUM_EVENTS; i++) अणु
		अगर (state->events[i] > 0) अणु
			dev_info(dev, "%s events: %d\n",
				 xcsi2rxss_events[i].name,
				 state->events[i]);
		पूर्ण
	पूर्ण

	अगर (state->en_vcx) अणु
		क्रम (i = 0; i < XCSI_VCX_NUM_EVENTS; i++) अणु
			अगर (state->vcx_events[i] > 0) अणु
				dev_info(dev,
					 "VC %d Frame %s err vcx events: %d\n",
					 (i / 2) + XCSI_VCX_START,
					 i & 1 ? "Sync" : "Level",
					 state->vcx_events[i]);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/**
 * xcsi2rxss_log_status - Logs the status of the CSI-2 Receiver
 * @sd: Poपूर्णांकer to V4L2 subdevice काष्ठाure
 *
 * This function prपूर्णांकs the current status of Xilinx MIPI CSI-2
 *
 * Return: 0 on success
 */
अटल पूर्णांक xcsi2rxss_log_status(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा xcsi2rxss_state *xcsi2rxss = to_xcsi2rxssstate(sd);
	काष्ठा device *dev = xcsi2rxss->dev;
	u32 reg, data;
	अचिन्हित पूर्णांक i, max_vc;

	mutex_lock(&xcsi2rxss->lock);

	xcsi2rxss_log_counters(xcsi2rxss);

	dev_info(dev, "***** Core Status *****\n");
	data = xcsi2rxss_पढ़ो(xcsi2rxss, XCSI_CSR_OFFSET);
	dev_info(dev, "Short Packet FIFO Full = %s\n",
		 data & XCSI_CSR_SPFIFOFULL ? "true" : "false");
	dev_info(dev, "Short Packet FIFO Not Empty = %s\n",
		 data & XCSI_CSR_SPFIFONE ? "true" : "false");
	dev_info(dev, "Stream line buffer full = %s\n",
		 data & XCSI_CSR_SLBF ? "true" : "false");
	dev_info(dev, "Soft reset/Core disable in progress = %s\n",
		 data & XCSI_CSR_RIPCD ? "true" : "false");

	/* Clk & Lane Info  */
	dev_info(dev, "******** Clock Lane Info *********\n");
	data = xcsi2rxss_पढ़ो(xcsi2rxss, XCSI_CLKINFR_OFFSET);
	dev_info(dev, "Clock Lane in Stop State = %s\n",
		 data & XCSI_CLKINFR_STOP ? "true" : "false");

	dev_info(dev, "******** Data Lane Info *********\n");
	dev_info(dev, "Lane\tSoT Error\tSoT Sync Error\tStop State\n");
	reg = XCSI_DLXINFR_OFFSET;
	क्रम (i = 0; i < XCSI_MAXDL_COUNT; i++) अणु
		data = xcsi2rxss_पढ़ो(xcsi2rxss, reg);

		dev_info(dev, "%d\t%s\t\t%s\t\t%s\n", i,
			 data & XCSI_DLXINFR_SOTERR ? "true" : "false",
			 data & XCSI_DLXINFR_SOTSYNCERR ? "true" : "false",
			 data & XCSI_DLXINFR_STOP ? "true" : "false");

		reg += XCSI_NEXTREG_OFFSET;
	पूर्ण

	/* Virtual Channel Image Inक्रमmation */
	dev_info(dev, "********** Virtual Channel Info ************\n");
	dev_info(dev, "VC\tLine Count\tByte Count\tData Type\n");
	अगर (xcsi2rxss->en_vcx)
		max_vc = XCSI_MAX_VCX;
	अन्यथा
		max_vc = XCSI_MAX_VC;

	reg = XCSI_VCXINF1R_OFFSET;
	क्रम (i = 0; i < max_vc; i++) अणु
		u32 line_count, byte_count, data_type;

		/* Get line and byte count from VCXINFR1 Register */
		data = xcsi2rxss_पढ़ो(xcsi2rxss, reg);
		byte_count = data & XCSI_VCXINF1R_BYTECOUNT;
		line_count = data & XCSI_VCXINF1R_LINECOUNT;
		line_count >>= XCSI_VCXINF1R_LINECOUNT_SHIFT;

		/* Get data type from VCXINFR2 Register */
		reg += XCSI_NEXTREG_OFFSET;
		data = xcsi2rxss_पढ़ो(xcsi2rxss, reg);
		data_type = data & XCSI_VCXINF2R_DT;

		dev_info(dev, "%d\t%d\t\t%d\t\t0x%x\n", i, line_count,
			 byte_count, data_type);

		/* Move to next pair of VC Info रेजिस्टरs */
		reg += XCSI_NEXTREG_OFFSET;
	पूर्ण

	mutex_unlock(&xcsi2rxss->lock);

	वापस 0;
पूर्ण

अटल काष्ठा v4l2_subdev *xcsi2rxss_get_remote_subdev(काष्ठा media_pad *local)
अणु
	काष्ठा media_pad *remote;

	remote = media_entity_remote_pad(local);
	अगर (!remote || !is_media_entity_v4l2_subdev(remote->entity))
		वापस शून्य;

	वापस media_entity_to_v4l2_subdev(remote->entity);
पूर्ण

अटल पूर्णांक xcsi2rxss_start_stream(काष्ठा xcsi2rxss_state *state)
अणु
	पूर्णांक ret = 0;

	/* enable core */
	xcsi2rxss_set(state, XCSI_CCR_OFFSET, XCSI_CCR_ENABLE);

	ret = xcsi2rxss_soft_reset(state);
	अगर (ret) अणु
		state->streaming = false;
		वापस ret;
	पूर्ण

	/* enable पूर्णांकerrupts */
	xcsi2rxss_clr(state, XCSI_GIER_OFFSET, XCSI_GIER_GIE);
	xcsi2rxss_ग_लिखो(state, XCSI_IER_OFFSET, XCSI_IER_INTR_MASK);
	xcsi2rxss_set(state, XCSI_GIER_OFFSET, XCSI_GIER_GIE);

	state->streaming = true;

	state->rsubdev =
		xcsi2rxss_get_remote_subdev(&state->pads[XVIP_PAD_SINK]);

	ret = v4l2_subdev_call(state->rsubdev, video, s_stream, 1);
	अगर (ret) अणु
		/* disable पूर्णांकerrupts */
		xcsi2rxss_clr(state, XCSI_IER_OFFSET, XCSI_IER_INTR_MASK);
		xcsi2rxss_clr(state, XCSI_GIER_OFFSET, XCSI_GIER_GIE);

		/* disable core */
		xcsi2rxss_clr(state, XCSI_CCR_OFFSET, XCSI_CCR_ENABLE);
		state->streaming = false;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम xcsi2rxss_stop_stream(काष्ठा xcsi2rxss_state *state)
अणु
	v4l2_subdev_call(state->rsubdev, video, s_stream, 0);

	/* disable पूर्णांकerrupts */
	xcsi2rxss_clr(state, XCSI_IER_OFFSET, XCSI_IER_INTR_MASK);
	xcsi2rxss_clr(state, XCSI_GIER_OFFSET, XCSI_GIER_GIE);

	/* disable core */
	xcsi2rxss_clr(state, XCSI_CCR_OFFSET, XCSI_CCR_ENABLE);
	state->streaming = false;
पूर्ण

/**
 * xcsi2rxss_irq_handler - Interrupt handler क्रम CSI-2
 * @irq: IRQ number
 * @data: Poपूर्णांकer to device state
 *
 * In the पूर्णांकerrupt handler, a list of event counters are updated क्रम
 * corresponding पूर्णांकerrupts. This is useful to get status / debug.
 *
 * Return: IRQ_HANDLED after handling पूर्णांकerrupts
 */
अटल irqवापस_t xcsi2rxss_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा xcsi2rxss_state *state = (काष्ठा xcsi2rxss_state *)data;
	काष्ठा device *dev = state->dev;
	u32 status;

	status = xcsi2rxss_पढ़ो(state, XCSI_ISR_OFFSET) & XCSI_ISR_ALLINTR_MASK;
	xcsi2rxss_ग_लिखो(state, XCSI_ISR_OFFSET, status);

	/* Received a लघु packet */
	अगर (status & XCSI_ISR_SPFIFONE) अणु
		u32 count = 0;

		/*
		 * Drain generic लघु packet FIFO by पढ़ोing max 31
		 * (fअगरo depth) लघु packets from fअगरo or till fअगरo is empty.
		 */
		क्रम (count = 0; count < XCSI_SPKT_FIFO_DEPTH; ++count) अणु
			u32 spfअगरostat, spkt;

			spkt = xcsi2rxss_पढ़ो(state, XCSI_SPKTR_OFFSET);
			dev_dbg(dev, "Short packet = 0x%08x\n", spkt);
			spfअगरostat = xcsi2rxss_पढ़ो(state, XCSI_ISR_OFFSET);
			spfअगरostat &= XCSI_ISR_SPFIFONE;
			अगर (!spfअगरostat)
				अवरोध;
			xcsi2rxss_ग_लिखो(state, XCSI_ISR_OFFSET, spfअगरostat);
		पूर्ण
	पूर्ण

	/* Short packet FIFO overflow */
	अगर (status & XCSI_ISR_SPFIFOF)
		dev_dbg_ratelimited(dev, "Short packet FIFO overflowed\n");

	/*
	 * Stream line buffer full
	 * This means there is a backpressure from करोwnstream IP
	 */
	अगर (status & XCSI_ISR_SLBF) अणु
		dev_alert_ratelimited(dev, "Stream Line Buffer Full!\n");

		/* disable पूर्णांकerrupts */
		xcsi2rxss_clr(state, XCSI_IER_OFFSET, XCSI_IER_INTR_MASK);
		xcsi2rxss_clr(state, XCSI_GIER_OFFSET, XCSI_GIER_GIE);

		/* disable core */
		xcsi2rxss_clr(state, XCSI_CCR_OFFSET, XCSI_CCR_ENABLE);

		/*
		 * The IP needs to be hard reset beक्रमe it can be used now.
		 * This will be करोne in streamoff.
		 */

		/*
		 * TODO: Notअगरy the whole pipeline with v4l2_subdev_notअगरy() to
		 * inक्रमm userspace.
		 */
	पूर्ण

	/* Increment event counters */
	अगर (status & XCSI_ISR_ALLINTR_MASK) अणु
		अचिन्हित पूर्णांक i;

		क्रम (i = 0; i < XCSI_NUM_EVENTS; i++) अणु
			अगर (!(status & xcsi2rxss_events[i].mask))
				जारी;
			state->events[i]++;
			dev_dbg_ratelimited(dev, "%s: %u\n",
					    xcsi2rxss_events[i].name,
					    state->events[i]);
		पूर्ण

		अगर (status & XCSI_ISR_VCXFE && state->en_vcx) अणु
			u32 vcxstatus;

			vcxstatus = xcsi2rxss_पढ़ो(state, XCSI_VCXR_OFFSET);
			vcxstatus &= XCSI_VCXR_VCERR;
			क्रम (i = 0; i < XCSI_VCX_NUM_EVENTS; i++) अणु
				अगर (!(vcxstatus & BIT(i)))
					जारी;
				state->vcx_events[i]++;
			पूर्ण
			xcsi2rxss_ग_लिखो(state, XCSI_VCXR_OFFSET, vcxstatus);
		पूर्ण
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/**
 * xcsi2rxss_s_stream - It is used to start/stop the streaming.
 * @sd: V4L2 Sub device
 * @enable: Flag (True / False)
 *
 * This function controls the start or stop of streaming क्रम the
 * Xilinx MIPI CSI-2 Rx Subप्रणाली.
 *
 * Return: 0 on success, errors otherwise
 */
अटल पूर्णांक xcsi2rxss_s_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	काष्ठा xcsi2rxss_state *xcsi2rxss = to_xcsi2rxssstate(sd);
	पूर्णांक ret = 0;

	mutex_lock(&xcsi2rxss->lock);

	अगर (enable == xcsi2rxss->streaming)
		जाओ stream_करोne;

	अगर (enable) अणु
		xcsi2rxss_reset_event_counters(xcsi2rxss);
		ret = xcsi2rxss_start_stream(xcsi2rxss);
	पूर्ण अन्यथा अणु
		xcsi2rxss_stop_stream(xcsi2rxss);
		xcsi2rxss_hard_reset(xcsi2rxss);
	पूर्ण

stream_करोne:
	mutex_unlock(&xcsi2rxss->lock);
	वापस ret;
पूर्ण

अटल काष्ठा v4l2_mbus_framefmt *
__xcsi2rxss_get_pad_क्रमmat(काष्ठा xcsi2rxss_state *xcsi2rxss,
			   काष्ठा v4l2_subdev_pad_config *cfg,
			   अचिन्हित पूर्णांक pad, u32 which)
अणु
	चयन (which) अणु
	हाल V4L2_SUBDEV_FORMAT_TRY:
		वापस v4l2_subdev_get_try_क्रमmat(&xcsi2rxss->subdev, cfg, pad);
	हाल V4L2_SUBDEV_FORMAT_ACTIVE:
		वापस &xcsi2rxss->क्रमmat;
	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण

/**
 * xcsi2rxss_init_cfg - Initialise the pad क्रमmat config to शेष
 * @sd: Poपूर्णांकer to V4L2 Sub device काष्ठाure
 * @cfg: Poपूर्णांकer to sub device pad inक्रमmation काष्ठाure
 *
 * This function is used to initialize the pad क्रमmat with the शेष
 * values.
 *
 * Return: 0 on success
 */
अटल पूर्णांक xcsi2rxss_init_cfg(काष्ठा v4l2_subdev *sd,
			      काष्ठा v4l2_subdev_pad_config *cfg)
अणु
	काष्ठा xcsi2rxss_state *xcsi2rxss = to_xcsi2rxssstate(sd);
	काष्ठा v4l2_mbus_framefmt *क्रमmat;
	अचिन्हित पूर्णांक i;

	mutex_lock(&xcsi2rxss->lock);
	क्रम (i = 0; i < XCSI_MEDIA_PADS; i++) अणु
		क्रमmat = v4l2_subdev_get_try_क्रमmat(sd, cfg, i);
		*क्रमmat = xcsi2rxss->शेष_क्रमmat;
	पूर्ण
	mutex_unlock(&xcsi2rxss->lock);

	वापस 0;
पूर्ण

/**
 * xcsi2rxss_get_क्रमmat - Get the pad क्रमmat
 * @sd: Poपूर्णांकer to V4L2 Sub device काष्ठाure
 * @cfg: Poपूर्णांकer to sub device pad inक्रमmation काष्ठाure
 * @fmt: Poपूर्णांकer to pad level media bus क्रमmat
 *
 * This function is used to get the pad क्रमmat inक्रमmation.
 *
 * Return: 0 on success
 */
अटल पूर्णांक xcsi2rxss_get_क्रमmat(काष्ठा v4l2_subdev *sd,
				काष्ठा v4l2_subdev_pad_config *cfg,
				काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा xcsi2rxss_state *xcsi2rxss = to_xcsi2rxssstate(sd);

	mutex_lock(&xcsi2rxss->lock);
	fmt->क्रमmat = *__xcsi2rxss_get_pad_क्रमmat(xcsi2rxss, cfg, fmt->pad,
						  fmt->which);
	mutex_unlock(&xcsi2rxss->lock);

	वापस 0;
पूर्ण

/**
 * xcsi2rxss_set_क्रमmat - This is used to set the pad क्रमmat
 * @sd: Poपूर्णांकer to V4L2 Sub device काष्ठाure
 * @cfg: Poपूर्णांकer to sub device pad inक्रमmation काष्ठाure
 * @fmt: Poपूर्णांकer to pad level media bus क्रमmat
 *
 * This function is used to set the pad क्रमmat. Since the pad क्रमmat is fixed
 * in hardware, it can't be modअगरied on run समय. So when a क्रमmat set is
 * requested by application, all parameters except the क्रमmat type is saved
 * क्रम the pad and the original pad क्रमmat is sent back to the application.
 *
 * Return: 0 on success
 */
अटल पूर्णांक xcsi2rxss_set_क्रमmat(काष्ठा v4l2_subdev *sd,
				काष्ठा v4l2_subdev_pad_config *cfg,
				काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा xcsi2rxss_state *xcsi2rxss = to_xcsi2rxssstate(sd);
	काष्ठा v4l2_mbus_framefmt *__क्रमmat;
	u32 dt;

	mutex_lock(&xcsi2rxss->lock);

	/*
	 * Only the क्रमmat->code parameter matters क्रम CSI as the
	 * CSI क्रमmat cannot be changed at runसमय.
	 * Ensure that क्रमmat to set is copied to over to CSI pad क्रमmat
	 */
	__क्रमmat = __xcsi2rxss_get_pad_क्रमmat(xcsi2rxss, cfg,
					      fmt->pad, fmt->which);

	/* only sink pad क्रमmat can be updated */
	अगर (fmt->pad == XVIP_PAD_SOURCE) अणु
		fmt->क्रमmat = *__क्रमmat;
		mutex_unlock(&xcsi2rxss->lock);
		वापस 0;
	पूर्ण

	/*
	 * RAW8 is supported in all datatypes. So अगर requested media bus क्रमmat
	 * is of RAW8 type, then allow to be set. In हाल core is configured to
	 * other RAW, YUV422 8/10 or RGB888, set appropriate media bus क्रमmat.
	 */
	dt = xcsi2rxss_get_dt(fmt->क्रमmat.code);
	अगर (dt != xcsi2rxss->datatype && dt != XCSI_DT_RAW8) अणु
		dev_dbg(xcsi2rxss->dev, "Unsupported media bus format");
		/* set the शेष क्रमmat क्रम the data type */
		fmt->क्रमmat.code = xcsi2rxss_get_nth_mbus(xcsi2rxss->datatype,
							  0);
	पूर्ण

	*__क्रमmat = fmt->क्रमmat;
	mutex_unlock(&xcsi2rxss->lock);

	वापस 0;
पूर्ण

/*
 * xcsi2rxss_क्रमागत_mbus_code - Handle pixel क्रमmat क्रमागतeration
 * @sd: poपूर्णांकer to v4l2 subdev काष्ठाure
 * @cfg: V4L2 subdev pad configuration
 * @code: poपूर्णांकer to v4l2_subdev_mbus_code_क्रमागत काष्ठाure
 *
 * Return: -EINVAL or zero on success
 */
अटल पूर्णांक xcsi2rxss_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
				    काष्ठा v4l2_subdev_pad_config *cfg,
				    काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	काष्ठा xcsi2rxss_state *state = to_xcsi2rxssstate(sd);
	u32 dt, n;
	पूर्णांक ret = 0;

	/* RAW8 dt packets are available in all DT configurations */
	अगर (code->index < 4) अणु
		n = code->index;
		dt = XCSI_DT_RAW8;
	पूर्ण अन्यथा अगर (state->datatype != XCSI_DT_RAW8) अणु
		n = code->index - 4;
		dt = state->datatype;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	code->code = xcsi2rxss_get_nth_mbus(dt, n);
	अगर (!code->code)
		ret = -EINVAL;

	वापस ret;
पूर्ण

/* -----------------------------------------------------------------------------
 * Media Operations
 */

अटल स्थिर काष्ठा media_entity_operations xcsi2rxss_media_ops = अणु
	.link_validate = v4l2_subdev_link_validate
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_core_ops xcsi2rxss_core_ops = अणु
	.log_status = xcsi2rxss_log_status,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_video_ops xcsi2rxss_video_ops = अणु
	.s_stream = xcsi2rxss_s_stream
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops xcsi2rxss_pad_ops = अणु
	.init_cfg = xcsi2rxss_init_cfg,
	.get_fmt = xcsi2rxss_get_क्रमmat,
	.set_fmt = xcsi2rxss_set_क्रमmat,
	.क्रमागत_mbus_code = xcsi2rxss_क्रमागत_mbus_code,
	.link_validate = v4l2_subdev_link_validate_शेष,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops xcsi2rxss_ops = अणु
	.core = &xcsi2rxss_core_ops,
	.video = &xcsi2rxss_video_ops,
	.pad = &xcsi2rxss_pad_ops
पूर्ण;

अटल पूर्णांक xcsi2rxss_parse_of(काष्ठा xcsi2rxss_state *xcsi2rxss)
अणु
	काष्ठा device *dev = xcsi2rxss->dev;
	काष्ठा device_node *node = dev->of_node;

	काष्ठा fwnode_handle *ep;
	काष्ठा v4l2_fwnode_endpoपूर्णांक vep = अणु
		.bus_type = V4L2_MBUS_CSI2_DPHY
	पूर्ण;
	bool en_csi_v20, vfb;
	पूर्णांक ret;

	en_csi_v20 = of_property_पढ़ो_bool(node, "xlnx,en-csi-v2-0");
	अगर (en_csi_v20)
		xcsi2rxss->en_vcx = of_property_पढ़ो_bool(node, "xlnx,en-vcx");

	xcsi2rxss->enable_active_lanes =
		of_property_पढ़ो_bool(node, "xlnx,en-active-lanes");

	ret = of_property_पढ़ो_u32(node, "xlnx,csi-pxl-format",
				   &xcsi2rxss->datatype);
	अगर (ret < 0) अणु
		dev_err(dev, "missing xlnx,csi-pxl-format property\n");
		वापस ret;
	पूर्ण

	चयन (xcsi2rxss->datatype) अणु
	हाल XCSI_DT_YUV4228B:
	हाल XCSI_DT_RGB444:
	हाल XCSI_DT_RGB555:
	हाल XCSI_DT_RGB565:
	हाल XCSI_DT_RGB666:
	हाल XCSI_DT_RGB888:
	हाल XCSI_DT_RAW6:
	हाल XCSI_DT_RAW7:
	हाल XCSI_DT_RAW8:
	हाल XCSI_DT_RAW10:
	हाल XCSI_DT_RAW12:
	हाल XCSI_DT_RAW14:
		अवरोध;
	हाल XCSI_DT_YUV42210B:
	हाल XCSI_DT_RAW16:
	हाल XCSI_DT_RAW20:
		अगर (!en_csi_v20) अणु
			ret = -EINVAL;
			dev_dbg(dev, "enable csi v2 for this pixel format");
		पूर्ण
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण
	अगर (ret < 0) अणु
		dev_err(dev, "invalid csi-pxl-format property!\n");
		वापस ret;
	पूर्ण

	vfb = of_property_पढ़ो_bool(node, "xlnx,vfb");
	अगर (!vfb) अणु
		dev_err(dev, "operation without VFB is not supported\n");
		वापस -EINVAL;
	पूर्ण

	ep = fwnode_graph_get_endpoपूर्णांक_by_id(dev_fwnode(dev),
					     XVIP_PAD_SINK, 0,
					     FWNODE_GRAPH_ENDPOINT_NEXT);
	अगर (!ep) अणु
		dev_err(dev, "no sink port found");
		वापस -EINVAL;
	पूर्ण

	ret = v4l2_fwnode_endpoपूर्णांक_parse(ep, &vep);
	fwnode_handle_put(ep);
	अगर (ret) अणु
		dev_err(dev, "error parsing sink port");
		वापस ret;
	पूर्ण

	dev_dbg(dev, "mipi number lanes = %d\n",
		vep.bus.mipi_csi2.num_data_lanes);

	xcsi2rxss->max_num_lanes = vep.bus.mipi_csi2.num_data_lanes;

	ep = fwnode_graph_get_endpoपूर्णांक_by_id(dev_fwnode(dev),
					     XVIP_PAD_SOURCE, 0,
					     FWNODE_GRAPH_ENDPOINT_NEXT);
	अगर (!ep) अणु
		dev_err(dev, "no source port found");
		वापस -EINVAL;
	पूर्ण

	fwnode_handle_put(ep);

	dev_dbg(dev, "vcx %s, %u data lanes (%s), data type 0x%02x\n",
		xcsi2rxss->en_vcx ? "enabled" : "disabled",
		xcsi2rxss->max_num_lanes,
		xcsi2rxss->enable_active_lanes ? "dynamic" : "static",
		xcsi2rxss->datatype);

	वापस 0;
पूर्ण

अटल पूर्णांक xcsi2rxss_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा v4l2_subdev *subdev;
	काष्ठा xcsi2rxss_state *xcsi2rxss;
	पूर्णांक num_clks = ARRAY_SIZE(xcsi2rxss_clks);
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक irq, ret;

	xcsi2rxss = devm_kzalloc(dev, माप(*xcsi2rxss), GFP_KERNEL);
	अगर (!xcsi2rxss)
		वापस -ENOMEM;

	xcsi2rxss->dev = dev;

	xcsi2rxss->clks = devm_kmemdup(dev, xcsi2rxss_clks,
				       माप(xcsi2rxss_clks), GFP_KERNEL);
	अगर (!xcsi2rxss->clks)
		वापस -ENOMEM;

	/* Reset GPIO */
	xcsi2rxss->rst_gpio = devm_gpiod_get_optional(dev, "video-reset",
						      GPIOD_OUT_HIGH);
	अगर (IS_ERR(xcsi2rxss->rst_gpio)) अणु
		अगर (PTR_ERR(xcsi2rxss->rst_gpio) != -EPROBE_DEFER)
			dev_err(dev, "Video Reset GPIO not setup in DT");
		वापस PTR_ERR(xcsi2rxss->rst_gpio);
	पूर्ण

	ret = xcsi2rxss_parse_of(xcsi2rxss);
	अगर (ret < 0)
		वापस ret;

	xcsi2rxss->iomem = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(xcsi2rxss->iomem))
		वापस PTR_ERR(xcsi2rxss->iomem);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	ret = devm_request_thपढ़ोed_irq(dev, irq, शून्य,
					xcsi2rxss_irq_handler, IRQF_ONESHOT,
					dev_name(dev), xcsi2rxss);
	अगर (ret) अणु
		dev_err(dev, "Err = %d Interrupt handler reg failed!\n", ret);
		वापस ret;
	पूर्ण

	ret = clk_bulk_get(dev, num_clks, xcsi2rxss->clks);
	अगर (ret)
		वापस ret;

	/* TODO: Enable/disable घड़ीs at stream on/off समय. */
	ret = clk_bulk_prepare_enable(num_clks, xcsi2rxss->clks);
	अगर (ret)
		जाओ err_clk_put;

	mutex_init(&xcsi2rxss->lock);

	xcsi2rxss_hard_reset(xcsi2rxss);
	xcsi2rxss_soft_reset(xcsi2rxss);

	/* Initialize V4L2 subdevice and media entity */
	xcsi2rxss->pads[XVIP_PAD_SINK].flags = MEDIA_PAD_FL_SINK;
	xcsi2rxss->pads[XVIP_PAD_SOURCE].flags = MEDIA_PAD_FL_SOURCE;

	/* Initialize the शेष क्रमmat */
	xcsi2rxss->शेष_क्रमmat.code =
		xcsi2rxss_get_nth_mbus(xcsi2rxss->datatype, 0);
	xcsi2rxss->शेष_क्रमmat.field = V4L2_FIELD_NONE;
	xcsi2rxss->शेष_क्रमmat.colorspace = V4L2_COLORSPACE_SRGB;
	xcsi2rxss->शेष_क्रमmat.width = XCSI_DEFAULT_WIDTH;
	xcsi2rxss->शेष_क्रमmat.height = XCSI_DEFAULT_HEIGHT;
	xcsi2rxss->क्रमmat = xcsi2rxss->शेष_क्रमmat;

	/* Initialize V4L2 subdevice and media entity */
	subdev = &xcsi2rxss->subdev;
	v4l2_subdev_init(subdev, &xcsi2rxss_ops);
	subdev->dev = dev;
	strscpy(subdev->name, dev_name(dev), माप(subdev->name));
	subdev->flags |= V4L2_SUBDEV_FL_HAS_EVENTS | V4L2_SUBDEV_FL_HAS_DEVNODE;
	subdev->entity.ops = &xcsi2rxss_media_ops;
	v4l2_set_subdevdata(subdev, xcsi2rxss);

	ret = media_entity_pads_init(&subdev->entity, XCSI_MEDIA_PADS,
				     xcsi2rxss->pads);
	अगर (ret < 0)
		जाओ error;

	platक्रमm_set_drvdata(pdev, xcsi2rxss);

	ret = v4l2_async_रेजिस्टर_subdev(subdev);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to register subdev\n");
		जाओ error;
	पूर्ण

	वापस 0;
error:
	media_entity_cleanup(&subdev->entity);
	mutex_destroy(&xcsi2rxss->lock);
	clk_bulk_disable_unprepare(num_clks, xcsi2rxss->clks);
err_clk_put:
	clk_bulk_put(num_clks, xcsi2rxss->clks);
	वापस ret;
पूर्ण

अटल पूर्णांक xcsi2rxss_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा xcsi2rxss_state *xcsi2rxss = platक्रमm_get_drvdata(pdev);
	काष्ठा v4l2_subdev *subdev = &xcsi2rxss->subdev;
	पूर्णांक num_clks = ARRAY_SIZE(xcsi2rxss_clks);

	v4l2_async_unरेजिस्टर_subdev(subdev);
	media_entity_cleanup(&subdev->entity);
	mutex_destroy(&xcsi2rxss->lock);
	clk_bulk_disable_unprepare(num_clks, xcsi2rxss->clks);
	clk_bulk_put(num_clks, xcsi2rxss->clks);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id xcsi2rxss_of_id_table[] = अणु
	अणु .compatible = "xlnx,mipi-csi2-rx-subsystem-5.0", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, xcsi2rxss_of_id_table);

अटल काष्ठा platक्रमm_driver xcsi2rxss_driver = अणु
	.driver = अणु
		.name		= "xilinx-csi2rxss",
		.of_match_table	= xcsi2rxss_of_id_table,
	पूर्ण,
	.probe			= xcsi2rxss_probe,
	.हटाओ			= xcsi2rxss_हटाओ,
पूर्ण;

module_platक्रमm_driver(xcsi2rxss_driver);

MODULE_AUTHOR("Vishal Sagar <vsagar@xilinx.com>");
MODULE_DESCRIPTION("Xilinx MIPI CSI-2 Rx Subsystem Driver");
MODULE_LICENSE("GPL v2");
