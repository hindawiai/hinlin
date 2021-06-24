<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  linux/include/linux/mmc/host.h
 *
 *  Host driver specअगरic definitions.
 */
#अगर_अघोषित LINUX_MMC_HOST_H
#घोषणा LINUX_MMC_HOST_H

#समावेश <linux/sched.h>
#समावेश <linux/device.h>
#समावेश <linux/fault-inject.h>

#समावेश <linux/mmc/core.h>
#समावेश <linux/mmc/card.h>
#समावेश <linux/mmc/pm.h>
#समावेश <linux/dma-direction.h>
#समावेश <linux/keyslot-manager.h>

काष्ठा mmc_ios अणु
	अचिन्हित पूर्णांक	घड़ी;			/* घड़ी rate */
	अचिन्हित लघु	vdd;
	अचिन्हित पूर्णांक	घातer_delay_ms;		/* रुकोing क्रम stable घातer */

/* vdd stores the bit number of the selected voltage range from below. */

	अचिन्हित अक्षर	bus_mode;		/* command output mode */

#घोषणा MMC_BUSMODE_OPENDRAIN	1
#घोषणा MMC_BUSMODE_PUSHPULL	2

	अचिन्हित अक्षर	chip_select;		/* SPI chip select */

#घोषणा MMC_CS_DONTCARE		0
#घोषणा MMC_CS_HIGH		1
#घोषणा MMC_CS_LOW		2

	अचिन्हित अक्षर	घातer_mode;		/* घातer supply mode */

#घोषणा MMC_POWER_OFF		0
#घोषणा MMC_POWER_UP		1
#घोषणा MMC_POWER_ON		2
#घोषणा MMC_POWER_UNDEFINED	3

	अचिन्हित अक्षर	bus_width;		/* data bus width */

#घोषणा MMC_BUS_WIDTH_1		0
#घोषणा MMC_BUS_WIDTH_4		2
#घोषणा MMC_BUS_WIDTH_8		3

	अचिन्हित अक्षर	timing;			/* timing specअगरication used */

#घोषणा MMC_TIMING_LEGACY	0
#घोषणा MMC_TIMING_MMC_HS	1
#घोषणा MMC_TIMING_SD_HS	2
#घोषणा MMC_TIMING_UHS_SDR12	3
#घोषणा MMC_TIMING_UHS_SDR25	4
#घोषणा MMC_TIMING_UHS_SDR50	5
#घोषणा MMC_TIMING_UHS_SDR104	6
#घोषणा MMC_TIMING_UHS_DDR50	7
#घोषणा MMC_TIMING_MMC_DDR52	8
#घोषणा MMC_TIMING_MMC_HS200	9
#घोषणा MMC_TIMING_MMC_HS400	10
#घोषणा MMC_TIMING_SD_EXP	11
#घोषणा MMC_TIMING_SD_EXP_1_2V	12

	अचिन्हित अक्षर	संकेत_voltage;		/* संकेतling voltage (1.8V or 3.3V) */

#घोषणा MMC_SIGNAL_VOLTAGE_330	0
#घोषणा MMC_SIGNAL_VOLTAGE_180	1
#घोषणा MMC_SIGNAL_VOLTAGE_120	2

	अचिन्हित अक्षर	drv_type;		/* driver type (A, B, C, D) */

#घोषणा MMC_SET_DRIVER_TYPE_B	0
#घोषणा MMC_SET_DRIVER_TYPE_A	1
#घोषणा MMC_SET_DRIVER_TYPE_C	2
#घोषणा MMC_SET_DRIVER_TYPE_D	3

	bool enhanced_strobe;			/* hs400es selection */
पूर्ण;

काष्ठा mmc_clk_phase अणु
	bool valid;
	u16 in_deg;
	u16 out_deg;
पूर्ण;

#घोषणा MMC_NUM_CLK_PHASES (MMC_TIMING_MMC_HS400 + 1)
काष्ठा mmc_clk_phase_map अणु
	काष्ठा mmc_clk_phase phase[MMC_NUM_CLK_PHASES];
पूर्ण;

काष्ठा mmc_host;

काष्ठा mmc_host_ops अणु
	/*
	 * It is optional क्रम the host to implement pre_req and post_req in
	 * order to support द्विगुन buffering of requests (prepare one
	 * request जबतक another request is active).
	 * pre_req() must always be followed by a post_req().
	 * To unकरो a call made to pre_req(), call post_req() with
	 * a nonzero err condition.
	 */
	व्योम	(*post_req)(काष्ठा mmc_host *host, काष्ठा mmc_request *req,
			    पूर्णांक err);
	व्योम	(*pre_req)(काष्ठा mmc_host *host, काष्ठा mmc_request *req);
	व्योम	(*request)(काष्ठा mmc_host *host, काष्ठा mmc_request *req);
	/* Submit one request to host in atomic context. */
	पूर्णांक	(*request_atomic)(काष्ठा mmc_host *host,
				  काष्ठा mmc_request *req);

	/*
	 * Aव्योम calling the next three functions too often or in a "fast
	 * path", since underlaying controller might implement them in an
	 * expensive and/or slow way. Also note that these functions might
	 * sleep, so करोn't call them in the atomic contexts!
	 */

	/*
	 * Notes to the set_ios callback:
	 * ios->घड़ी might be 0. For some controllers, setting 0Hz
	 * as any other frequency works. However, some controllers
	 * explicitly need to disable the घड़ी. Otherwise e.g. voltage
	 * चयनing might fail because the SDCLK is not really quiet.
	 */
	व्योम	(*set_ios)(काष्ठा mmc_host *host, काष्ठा mmc_ios *ios);

	/*
	 * Return values क्रम the get_ro callback should be:
	 *   0 क्रम a पढ़ो/ग_लिखो card
	 *   1 क्रम a पढ़ो-only card
	 *   -ENOSYS when not supported (equal to शून्य callback)
	 *   or a negative त्रुटि_सं value when something bad happened
	 */
	पूर्णांक	(*get_ro)(काष्ठा mmc_host *host);

	/*
	 * Return values क्रम the get_cd callback should be:
	 *   0 क्रम a असलent card
	 *   1 क्रम a present card
	 *   -ENOSYS when not supported (equal to शून्य callback)
	 *   or a negative त्रुटि_सं value when something bad happened
	 */
	पूर्णांक	(*get_cd)(काष्ठा mmc_host *host);

	व्योम	(*enable_sdio_irq)(काष्ठा mmc_host *host, पूर्णांक enable);
	/* Mandatory callback when using MMC_CAP2_SDIO_IRQ_NOTHREAD. */
	व्योम	(*ack_sdio_irq)(काष्ठा mmc_host *host);

	/* optional callback क्रम HC quirks */
	व्योम	(*init_card)(काष्ठा mmc_host *host, काष्ठा mmc_card *card);

	पूर्णांक	(*start_संकेत_voltage_चयन)(काष्ठा mmc_host *host, काष्ठा mmc_ios *ios);

	/* Check अगर the card is pulling dat[0:3] low */
	पूर्णांक	(*card_busy)(काष्ठा mmc_host *host);

	/* The tuning command opcode value is dअगरferent क्रम SD and eMMC cards */
	पूर्णांक	(*execute_tuning)(काष्ठा mmc_host *host, u32 opcode);

	/* Prepare HS400 target operating frequency depending host driver */
	पूर्णांक	(*prepare_hs400_tuning)(काष्ठा mmc_host *host, काष्ठा mmc_ios *ios);

	/* Prepare चयन to DDR during the HS400 init sequence */
	पूर्णांक	(*hs400_prepare_ddr)(काष्ठा mmc_host *host);

	/* Prepare क्रम चयनing from HS400 to HS200 */
	व्योम	(*hs400_करोwngrade)(काष्ठा mmc_host *host);

	/* Complete selection of HS400 */
	व्योम	(*hs400_complete)(काष्ठा mmc_host *host);

	/* Prepare enhanced strobe depending host driver */
	व्योम	(*hs400_enhanced_strobe)(काष्ठा mmc_host *host,
					 काष्ठा mmc_ios *ios);
	पूर्णांक	(*select_drive_strength)(काष्ठा mmc_card *card,
					 अचिन्हित पूर्णांक max_dtr, पूर्णांक host_drv,
					 पूर्णांक card_drv, पूर्णांक *drv_type);
	/* Reset the eMMC card via RST_n */
	व्योम	(*hw_reset)(काष्ठा mmc_host *host);
	व्योम	(*card_event)(काष्ठा mmc_host *host);

	/*
	 * Optional callback to support controllers with HW issues क्रम multiple
	 * I/O. Returns the number of supported blocks क्रम the request.
	 */
	पूर्णांक	(*multi_io_quirk)(काष्ठा mmc_card *card,
				  अचिन्हित पूर्णांक direction, पूर्णांक blk_size);

	/* Initialize an SD express card, mandatory क्रम MMC_CAP2_SD_EXP. */
	पूर्णांक	(*init_sd_express)(काष्ठा mmc_host *host, काष्ठा mmc_ios *ios);
पूर्ण;

काष्ठा mmc_cqe_ops अणु
	/* Allocate resources, and make the CQE operational */
	पूर्णांक	(*cqe_enable)(काष्ठा mmc_host *host, काष्ठा mmc_card *card);
	/* Free resources, and make the CQE non-operational */
	व्योम	(*cqe_disable)(काष्ठा mmc_host *host);
	/*
	 * Issue a पढ़ो, ग_लिखो or DCMD request to the CQE. Also deal with the
	 * effect of ->cqe_off().
	 */
	पूर्णांक	(*cqe_request)(काष्ठा mmc_host *host, काष्ठा mmc_request *mrq);
	/* Free resources (e.g. DMA mapping) associated with the request */
	व्योम	(*cqe_post_req)(काष्ठा mmc_host *host, काष्ठा mmc_request *mrq);
	/*
	 * Prepare the CQE and host controller to accept non-CQ commands. There
	 * is no corresponding ->cqe_on(), instead ->cqe_request() is required
	 * to deal with that.
	 */
	व्योम	(*cqe_off)(काष्ठा mmc_host *host);
	/*
	 * Wait क्रम all CQE tasks to complete. Return an error अगर recovery
	 * becomes necessary.
	 */
	पूर्णांक	(*cqe_रुको_क्रम_idle)(काष्ठा mmc_host *host);
	/*
	 * Notअगरy CQE that a request has समयd out. Return false अगर the request
	 * completed or true अगर a समयout happened in which हाल indicate अगर
	 * recovery is needed.
	 */
	bool	(*cqe_समयout)(काष्ठा mmc_host *host, काष्ठा mmc_request *mrq,
			       bool *recovery_needed);
	/*
	 * Stop all CQE activity and prepare the CQE and host controller to
	 * accept recovery commands.
	 */
	व्योम	(*cqe_recovery_start)(काष्ठा mmc_host *host);
	/*
	 * Clear the queue and call mmc_cqe_request_करोne() on all requests.
	 * Requests that errored will have the error set on the mmc_request
	 * (data->error or cmd->error क्रम DCMD).  Requests that did not error
	 * will have zero data bytes transferred.
	 */
	व्योम	(*cqe_recovery_finish)(काष्ठा mmc_host *host);
पूर्ण;

काष्ठा mmc_async_req अणु
	/* active mmc request */
	काष्ठा mmc_request	*mrq;
	/*
	 * Check error status of completed mmc request.
	 * Returns 0 अगर success otherwise non zero.
	 */
	क्रमागत mmc_blk_status (*err_check)(काष्ठा mmc_card *, काष्ठा mmc_async_req *);
पूर्ण;

/**
 * काष्ठा mmc_slot - MMC slot functions
 *
 * @cd_irq:		MMC/SD-card slot hotplug detection IRQ or -EINVAL
 * @handler_priv:	MMC/SD-card slot context
 *
 * Some MMC/SD host controllers implement slot-functions like card and
 * ग_लिखो-protect detection natively. However, a large number of controllers
 * leave these functions to the CPU. This काष्ठा provides a hook to attach
 * such slot-function drivers.
 */
काष्ठा mmc_slot अणु
	पूर्णांक cd_irq;
	bool cd_wake_enabled;
	व्योम *handler_priv;
पूर्ण;

/**
 * mmc_context_info - synchronization details क्रम mmc context
 * @is_करोne_rcv		wake up reason was करोne request
 * @is_new_req		wake up reason was new request
 * @is_रुकोing_last_req	mmc context रुकोing क्रम single running request
 * @रुको		रुको queue
 */
काष्ठा mmc_context_info अणु
	bool			is_करोne_rcv;
	bool			is_new_req;
	bool			is_रुकोing_last_req;
	रुको_queue_head_t	रुको;
पूर्ण;

काष्ठा regulator;
काष्ठा mmc_pwrseq;

काष्ठा mmc_supply अणु
	काष्ठा regulator *vmmc;		/* Card घातer supply */
	काष्ठा regulator *vqmmc;	/* Optional Vccq supply */
पूर्ण;

काष्ठा mmc_ctx अणु
	काष्ठा task_काष्ठा *task;
पूर्ण;

काष्ठा mmc_host अणु
	काष्ठा device		*parent;
	काष्ठा device		class_dev;
	पूर्णांक			index;
	स्थिर काष्ठा mmc_host_ops *ops;
	काष्ठा mmc_pwrseq	*pwrseq;
	अचिन्हित पूर्णांक		f_min;
	अचिन्हित पूर्णांक		f_max;
	अचिन्हित पूर्णांक		f_init;
	u32			ocr_avail;
	u32			ocr_avail_sdio;	/* SDIO-specअगरic OCR */
	u32			ocr_avail_sd;	/* SD-specअगरic OCR */
	u32			ocr_avail_mmc;	/* MMC-specअगरic OCR */
	काष्ठा wakeup_source	*ws;		/* Enable consume of uevents */
	u32			max_current_330;
	u32			max_current_300;
	u32			max_current_180;

#घोषणा MMC_VDD_165_195		0x00000080	/* VDD voltage 1.65 - 1.95 */
#घोषणा MMC_VDD_20_21		0x00000100	/* VDD voltage 2.0 ~ 2.1 */
#घोषणा MMC_VDD_21_22		0x00000200	/* VDD voltage 2.1 ~ 2.2 */
#घोषणा MMC_VDD_22_23		0x00000400	/* VDD voltage 2.2 ~ 2.3 */
#घोषणा MMC_VDD_23_24		0x00000800	/* VDD voltage 2.3 ~ 2.4 */
#घोषणा MMC_VDD_24_25		0x00001000	/* VDD voltage 2.4 ~ 2.5 */
#घोषणा MMC_VDD_25_26		0x00002000	/* VDD voltage 2.5 ~ 2.6 */
#घोषणा MMC_VDD_26_27		0x00004000	/* VDD voltage 2.6 ~ 2.7 */
#घोषणा MMC_VDD_27_28		0x00008000	/* VDD voltage 2.7 ~ 2.8 */
#घोषणा MMC_VDD_28_29		0x00010000	/* VDD voltage 2.8 ~ 2.9 */
#घोषणा MMC_VDD_29_30		0x00020000	/* VDD voltage 2.9 ~ 3.0 */
#घोषणा MMC_VDD_30_31		0x00040000	/* VDD voltage 3.0 ~ 3.1 */
#घोषणा MMC_VDD_31_32		0x00080000	/* VDD voltage 3.1 ~ 3.2 */
#घोषणा MMC_VDD_32_33		0x00100000	/* VDD voltage 3.2 ~ 3.3 */
#घोषणा MMC_VDD_33_34		0x00200000	/* VDD voltage 3.3 ~ 3.4 */
#घोषणा MMC_VDD_34_35		0x00400000	/* VDD voltage 3.4 ~ 3.5 */
#घोषणा MMC_VDD_35_36		0x00800000	/* VDD voltage 3.5 ~ 3.6 */

	u32			caps;		/* Host capabilities */

#घोषणा MMC_CAP_4_BIT_DATA	(1 << 0)	/* Can the host करो 4 bit transfers */
#घोषणा MMC_CAP_MMC_HIGHSPEED	(1 << 1)	/* Can करो MMC high-speed timing */
#घोषणा MMC_CAP_SD_HIGHSPEED	(1 << 2)	/* Can करो SD high-speed timing */
#घोषणा MMC_CAP_SDIO_IRQ	(1 << 3)	/* Can संकेत pending SDIO IRQs */
#घोषणा MMC_CAP_SPI		(1 << 4)	/* Talks only SPI protocols */
#घोषणा MMC_CAP_NEEDS_POLL	(1 << 5)	/* Needs polling क्रम card-detection */
#घोषणा MMC_CAP_8_BIT_DATA	(1 << 6)	/* Can the host करो 8 bit transfers */
#घोषणा MMC_CAP_AGGRESSIVE_PM	(1 << 7)	/* Suspend (e)MMC/SD at idle  */
#घोषणा MMC_CAP_NONREMOVABLE	(1 << 8)	/* Nonremovable e.g. eMMC */
#घोषणा MMC_CAP_WAIT_WHILE_BUSY	(1 << 9)	/* Waits जबतक card is busy */
#घोषणा MMC_CAP_3_3V_DDR	(1 << 11)	/* Host supports eMMC DDR 3.3V */
#घोषणा MMC_CAP_1_8V_DDR	(1 << 12)	/* Host supports eMMC DDR 1.8V */
#घोषणा MMC_CAP_1_2V_DDR	(1 << 13)	/* Host supports eMMC DDR 1.2V */
#घोषणा MMC_CAP_DDR		(MMC_CAP_3_3V_DDR | MMC_CAP_1_8V_DDR | \
				 MMC_CAP_1_2V_DDR)
#घोषणा MMC_CAP_POWER_OFF_CARD	(1 << 14)	/* Can घातer off after boot */
#घोषणा MMC_CAP_BUS_WIDTH_TEST	(1 << 15)	/* CMD14/CMD19 bus width ok */
#घोषणा MMC_CAP_UHS_SDR12	(1 << 16)	/* Host supports UHS SDR12 mode */
#घोषणा MMC_CAP_UHS_SDR25	(1 << 17)	/* Host supports UHS SDR25 mode */
#घोषणा MMC_CAP_UHS_SDR50	(1 << 18)	/* Host supports UHS SDR50 mode */
#घोषणा MMC_CAP_UHS_SDR104	(1 << 19)	/* Host supports UHS SDR104 mode */
#घोषणा MMC_CAP_UHS_DDR50	(1 << 20)	/* Host supports UHS DDR50 mode */
#घोषणा MMC_CAP_UHS		(MMC_CAP_UHS_SDR12 | MMC_CAP_UHS_SDR25 | \
				 MMC_CAP_UHS_SDR50 | MMC_CAP_UHS_SDR104 | \
				 MMC_CAP_UHS_DDR50)
#घोषणा MMC_CAP_SYNC_RUNTIME_PM	(1 << 21)	/* Synced runसमय PM suspends. */
#घोषणा MMC_CAP_NEED_RSP_BUSY	(1 << 22)	/* Commands with R1B can't use R1. */
#घोषणा MMC_CAP_DRIVER_TYPE_A	(1 << 23)	/* Host supports Driver Type A */
#घोषणा MMC_CAP_DRIVER_TYPE_C	(1 << 24)	/* Host supports Driver Type C */
#घोषणा MMC_CAP_DRIVER_TYPE_D	(1 << 25)	/* Host supports Driver Type D */
#घोषणा MMC_CAP_DONE_COMPLETE	(1 << 27)	/* RW reqs can be completed within mmc_request_करोne() */
#घोषणा MMC_CAP_CD_WAKE		(1 << 28)	/* Enable card detect wake */
#घोषणा MMC_CAP_CMD_DURING_TFR	(1 << 29)	/* Commands during data transfer */
#घोषणा MMC_CAP_CMD23		(1 << 30)	/* CMD23 supported. */
#घोषणा MMC_CAP_HW_RESET	(1 << 31)	/* Reset the eMMC card via RST_n */

	u32			caps2;		/* More host capabilities */

#घोषणा MMC_CAP2_BOOTPART_NOACC	(1 << 0)	/* Boot partition no access */
#घोषणा MMC_CAP2_FULL_PWR_CYCLE	(1 << 2)	/* Can करो full घातer cycle */
#घोषणा MMC_CAP2_FULL_PWR_CYCLE_IN_SUSPEND (1 << 3) /* Can करो full घातer cycle in suspend */
#घोषणा MMC_CAP2_HS200_1_8V_SDR	(1 << 5)        /* can support */
#घोषणा MMC_CAP2_HS200_1_2V_SDR	(1 << 6)        /* can support */
#घोषणा MMC_CAP2_HS200		(MMC_CAP2_HS200_1_8V_SDR | \
				 MMC_CAP2_HS200_1_2V_SDR)
#घोषणा MMC_CAP2_SD_EXP		(1 << 7)	/* SD express via PCIe */
#घोषणा MMC_CAP2_SD_EXP_1_2V	(1 << 8)	/* SD express 1.2V */
#घोषणा MMC_CAP2_CD_ACTIVE_HIGH	(1 << 10)	/* Card-detect संकेत active high */
#घोषणा MMC_CAP2_RO_ACTIVE_HIGH	(1 << 11)	/* Write-protect संकेत active high */
#घोषणा MMC_CAP2_NO_PRESCAN_POWERUP (1 << 14)	/* Don't घातer up beक्रमe scan */
#घोषणा MMC_CAP2_HS400_1_8V	(1 << 15)	/* Can support HS400 1.8V */
#घोषणा MMC_CAP2_HS400_1_2V	(1 << 16)	/* Can support HS400 1.2V */
#घोषणा MMC_CAP2_HS400		(MMC_CAP2_HS400_1_8V | \
				 MMC_CAP2_HS400_1_2V)
#घोषणा MMC_CAP2_HSX00_1_8V	(MMC_CAP2_HS200_1_8V_SDR | MMC_CAP2_HS400_1_8V)
#घोषणा MMC_CAP2_HSX00_1_2V	(MMC_CAP2_HS200_1_2V_SDR | MMC_CAP2_HS400_1_2V)
#घोषणा MMC_CAP2_SDIO_IRQ_NOTHREAD (1 << 17)
#घोषणा MMC_CAP2_NO_WRITE_PROTECT (1 << 18)	/* No physical ग_लिखो protect pin, assume that card is always पढ़ो-ग_लिखो */
#घोषणा MMC_CAP2_NO_SDIO	(1 << 19)	/* Do not send SDIO commands during initialization */
#घोषणा MMC_CAP2_HS400_ES	(1 << 20)	/* Host supports enhanced strobe */
#घोषणा MMC_CAP2_NO_SD		(1 << 21)	/* Do not send SD commands during initialization */
#घोषणा MMC_CAP2_NO_MMC		(1 << 22)	/* Do not send (e)MMC commands during initialization */
#घोषणा MMC_CAP2_CQE		(1 << 23)	/* Has eMMC command queue engine */
#घोषणा MMC_CAP2_CQE_DCMD	(1 << 24)	/* CQE can issue a direct command */
#घोषणा MMC_CAP2_AVOID_3_3V	(1 << 25)	/* Host must negotiate करोwn from 3.3V */
#घोषणा MMC_CAP2_MERGE_CAPABLE	(1 << 26)	/* Host can merge a segment over the segment size */
#अगर_घोषित CONFIG_MMC_CRYPTO
#घोषणा MMC_CAP2_CRYPTO		(1 << 27)	/* Host supports अंतरभूत encryption */
#अन्यथा
#घोषणा MMC_CAP2_CRYPTO		0
#पूर्ण_अगर

	पूर्णांक			fixed_drv_type;	/* fixed driver type क्रम non-removable media */

	mmc_pm_flag_t		pm_caps;	/* supported pm features */

	/* host specअगरic block data */
	अचिन्हित पूर्णांक		max_seg_size;	/* see blk_queue_max_segment_size */
	अचिन्हित लघु		max_segs;	/* see blk_queue_max_segments */
	अचिन्हित लघु		unused;
	अचिन्हित पूर्णांक		max_req_size;	/* maximum number of bytes in one req */
	अचिन्हित पूर्णांक		max_blk_size;	/* maximum size of one mmc block */
	अचिन्हित पूर्णांक		max_blk_count;	/* maximum number of blocks in one req */
	अचिन्हित पूर्णांक		max_busy_समयout; /* max busy समयout in ms */

	/* निजी data */
	spinlock_t		lock;		/* lock क्रम claim and bus ops */

	काष्ठा mmc_ios		ios;		/* current io bus settings */

	/* group bitfields together to minimize padding */
	अचिन्हित पूर्णांक		use_spi_crc:1;
	अचिन्हित पूर्णांक		claimed:1;	/* host exclusively claimed */
	अचिन्हित पूर्णांक		करोing_init_tune:1; /* initial tuning in progress */
	अचिन्हित पूर्णांक		can_retune:1;	/* re-tuning can be used */
	अचिन्हित पूर्णांक		करोing_retune:1;	/* re-tuning in progress */
	अचिन्हित पूर्णांक		retune_now:1;	/* करो re-tuning at next req */
	अचिन्हित पूर्णांक		retune_छोड़ोd:1; /* re-tuning is temporarily disabled */
	अचिन्हित पूर्णांक		retune_crc_disable:1; /* करोn't trigger retune upon crc */
	अचिन्हित पूर्णांक		can_dma_map_merge:1; /* merging can be used */

	पूर्णांक			rescan_disable;	/* disable card detection */
	पूर्णांक			rescan_entered;	/* used with nonremovable devices */

	पूर्णांक			need_retune;	/* re-tuning is needed */
	पूर्णांक			hold_retune;	/* hold off re-tuning */
	अचिन्हित पूर्णांक		retune_period;	/* re-tuning period in secs */
	काष्ठा समयr_list	retune_समयr;	/* क्रम periodic re-tuning */

	bool			trigger_card_event; /* card_event necessary */

	काष्ठा mmc_card		*card;		/* device attached to this host */

	रुको_queue_head_t	wq;
	काष्ठा mmc_ctx		*claimer;	/* context that has host claimed */
	पूर्णांक			claim_cnt;	/* "claim" nesting count */
	काष्ठा mmc_ctx		शेष_ctx;	/* शेष context */

	काष्ठा delayed_work	detect;
	पूर्णांक			detect_change;	/* card detect flag */
	काष्ठा mmc_slot		slot;

	स्थिर काष्ठा mmc_bus_ops *bus_ops;	/* current bus driver */

	अचिन्हित पूर्णांक		sdio_irqs;
	काष्ठा task_काष्ठा	*sdio_irq_thपढ़ो;
	काष्ठा delayed_work	sdio_irq_work;
	bool			sdio_irq_pending;
	atomic_t		sdio_irq_thपढ़ो_पात;

	mmc_pm_flag_t		pm_flags;	/* requested pm features */

	काष्ठा led_trigger	*led;		/* activity led */

#अगर_घोषित CONFIG_REGULATOR
	bool			regulator_enabled; /* regulator state */
#पूर्ण_अगर
	काष्ठा mmc_supply	supply;

	काष्ठा dentry		*debugfs_root;

	/* Ongoing data transfer that allows commands during transfer */
	काष्ठा mmc_request	*ongoing_mrq;

#अगर_घोषित CONFIG_FAIL_MMC_REQUEST
	काष्ठा fault_attr	fail_mmc_request;
#पूर्ण_अगर

	अचिन्हित पूर्णांक		actual_घड़ी;	/* Actual HC घड़ी rate */

	अचिन्हित पूर्णांक		slotno;	/* used क्रम sdio acpi binding */

	पूर्णांक			dsr_req;	/* DSR value is valid */
	u32			dsr;	/* optional driver stage (DSR) value */

	/* Command Queue Engine (CQE) support */
	स्थिर काष्ठा mmc_cqe_ops *cqe_ops;
	व्योम			*cqe_निजी;
	पूर्णांक			cqe_qdepth;
	bool			cqe_enabled;
	bool			cqe_on;

	/* Inline encryption support */
#अगर_घोषित CONFIG_MMC_CRYPTO
	काष्ठा blk_keyslot_manager ksm;
#पूर्ण_अगर

	/* Host Software Queue support */
	bool			hsq_enabled;

	अचिन्हित दीर्घ		निजी[] ____cacheline_aligned;
पूर्ण;

काष्ठा device_node;

काष्ठा mmc_host *mmc_alloc_host(पूर्णांक extra, काष्ठा device *);
पूर्णांक mmc_add_host(काष्ठा mmc_host *);
व्योम mmc_हटाओ_host(काष्ठा mmc_host *);
व्योम mmc_मुक्त_host(काष्ठा mmc_host *);
व्योम mmc_of_parse_clk_phase(काष्ठा mmc_host *host,
			    काष्ठा mmc_clk_phase_map *map);
पूर्णांक mmc_of_parse(काष्ठा mmc_host *host);
पूर्णांक mmc_of_parse_voltage(काष्ठा mmc_host *host, u32 *mask);

अटल अंतरभूत व्योम *mmc_priv(काष्ठा mmc_host *host)
अणु
	वापस (व्योम *)host->निजी;
पूर्ण

अटल अंतरभूत काष्ठा mmc_host *mmc_from_priv(व्योम *priv)
अणु
	वापस container_of(priv, काष्ठा mmc_host, निजी);
पूर्ण

#घोषणा mmc_host_is_spi(host)	((host)->caps & MMC_CAP_SPI)

#घोषणा mmc_dev(x)	((x)->parent)
#घोषणा mmc_classdev(x)	(&(x)->class_dev)
#घोषणा mmc_hostname(x)	(dev_name(&(x)->class_dev))

व्योम mmc_detect_change(काष्ठा mmc_host *, अचिन्हित दीर्घ delay);
व्योम mmc_request_करोne(काष्ठा mmc_host *, काष्ठा mmc_request *);
व्योम mmc_command_करोne(काष्ठा mmc_host *host, काष्ठा mmc_request *mrq);

व्योम mmc_cqe_request_करोne(काष्ठा mmc_host *host, काष्ठा mmc_request *mrq);

/*
 * May be called from host driver's प्रणाली/runसमय suspend/resume callbacks,
 * to know अगर SDIO IRQs has been claimed.
 */
अटल अंतरभूत bool sdio_irq_claimed(काष्ठा mmc_host *host)
अणु
	वापस host->sdio_irqs > 0;
पूर्ण

अटल अंतरभूत व्योम mmc_संकेत_sdio_irq(काष्ठा mmc_host *host)
अणु
	host->ops->enable_sdio_irq(host, 0);
	host->sdio_irq_pending = true;
	अगर (host->sdio_irq_thपढ़ो)
		wake_up_process(host->sdio_irq_thपढ़ो);
पूर्ण

व्योम sdio_संकेत_irq(काष्ठा mmc_host *host);

#अगर_घोषित CONFIG_REGULATOR
पूर्णांक mmc_regulator_set_ocr(काष्ठा mmc_host *mmc,
			काष्ठा regulator *supply,
			अचिन्हित लघु vdd_bit);
पूर्णांक mmc_regulator_set_vqmmc(काष्ठा mmc_host *mmc, काष्ठा mmc_ios *ios);
#अन्यथा
अटल अंतरभूत पूर्णांक mmc_regulator_set_ocr(काष्ठा mmc_host *mmc,
				 काष्ठा regulator *supply,
				 अचिन्हित लघु vdd_bit)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक mmc_regulator_set_vqmmc(काष्ठा mmc_host *mmc,
					  काष्ठा mmc_ios *ios)
अणु
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर

पूर्णांक mmc_regulator_get_supply(काष्ठा mmc_host *mmc);

अटल अंतरभूत पूर्णांक mmc_card_is_removable(काष्ठा mmc_host *host)
अणु
	वापस !(host->caps & MMC_CAP_NONREMOVABLE);
पूर्ण

अटल अंतरभूत पूर्णांक mmc_card_keep_घातer(काष्ठा mmc_host *host)
अणु
	वापस host->pm_flags & MMC_PM_KEEP_POWER;
पूर्ण

अटल अंतरभूत पूर्णांक mmc_card_wake_sdio_irq(काष्ठा mmc_host *host)
अणु
	वापस host->pm_flags & MMC_PM_WAKE_SDIO_IRQ;
पूर्ण

/* TODO: Move to निजी header */
अटल अंतरभूत पूर्णांक mmc_card_hs(काष्ठा mmc_card *card)
अणु
	वापस card->host->ios.timing == MMC_TIMING_SD_HS ||
		card->host->ios.timing == MMC_TIMING_MMC_HS;
पूर्ण

/* TODO: Move to निजी header */
अटल अंतरभूत पूर्णांक mmc_card_uhs(काष्ठा mmc_card *card)
अणु
	वापस card->host->ios.timing >= MMC_TIMING_UHS_SDR12 &&
		card->host->ios.timing <= MMC_TIMING_UHS_DDR50;
पूर्ण

व्योम mmc_retune_समयr_stop(काष्ठा mmc_host *host);

अटल अंतरभूत व्योम mmc_retune_needed(काष्ठा mmc_host *host)
अणु
	अगर (host->can_retune)
		host->need_retune = 1;
पूर्ण

अटल अंतरभूत bool mmc_can_retune(काष्ठा mmc_host *host)
अणु
	वापस host->can_retune == 1;
पूर्ण

अटल अंतरभूत bool mmc_करोing_retune(काष्ठा mmc_host *host)
अणु
	वापस host->करोing_retune == 1;
पूर्ण

अटल अंतरभूत bool mmc_करोing_tune(काष्ठा mmc_host *host)
अणु
	वापस host->करोing_retune == 1 || host->करोing_init_tune == 1;
पूर्ण

अटल अंतरभूत क्रमागत dma_data_direction mmc_get_dma_dir(काष्ठा mmc_data *data)
अणु
	वापस data->flags & MMC_DATA_WRITE ? DMA_TO_DEVICE : DMA_FROM_DEVICE;
पूर्ण

पूर्णांक mmc_send_tuning(काष्ठा mmc_host *host, u32 opcode, पूर्णांक *cmd_error);
पूर्णांक mmc_पात_tuning(काष्ठा mmc_host *host, u32 opcode);

#पूर्ण_अगर /* LINUX_MMC_HOST_H */
