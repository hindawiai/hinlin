<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * (C) COPYRIGHT 2018 ARM Limited. All rights reserved.
 * Author: James.Qian.Wang <james.qian.wang@arm.com>
 *
 */
#अगर_अघोषित _KOMEDA_DEV_H_
#घोषणा _KOMEDA_DEV_H_

#समावेश <linux/device.h>
#समावेश <linux/clk.h>
#समावेश "komeda_pipeline.h"
#समावेश "malidp_product.h"
#समावेश "komeda_format_caps.h"

#घोषणा KOMEDA_EVENT_VSYNC		BIT_ULL(0)
#घोषणा KOMEDA_EVENT_FLIP		BIT_ULL(1)
#घोषणा KOMEDA_EVENT_URUN		BIT_ULL(2)
#घोषणा KOMEDA_EVENT_IBSY		BIT_ULL(3)
#घोषणा KOMEDA_EVENT_OVR		BIT_ULL(4)
#घोषणा KOMEDA_EVENT_EOW		BIT_ULL(5)
#घोषणा KOMEDA_EVENT_MODE		BIT_ULL(6)
#घोषणा KOMEDA_EVENT_FULL		BIT_ULL(7)
#घोषणा KOMEDA_EVENT_EMPTY		BIT_ULL(8)

#घोषणा KOMEDA_ERR_TETO			BIT_ULL(14)
#घोषणा KOMEDA_ERR_TEMR			BIT_ULL(15)
#घोषणा KOMEDA_ERR_TITR			BIT_ULL(16)
#घोषणा KOMEDA_ERR_CPE			BIT_ULL(17)
#घोषणा KOMEDA_ERR_CFGE			BIT_ULL(18)
#घोषणा KOMEDA_ERR_AXIE			BIT_ULL(19)
#घोषणा KOMEDA_ERR_ACE0			BIT_ULL(20)
#घोषणा KOMEDA_ERR_ACE1			BIT_ULL(21)
#घोषणा KOMEDA_ERR_ACE2			BIT_ULL(22)
#घोषणा KOMEDA_ERR_ACE3			BIT_ULL(23)
#घोषणा KOMEDA_ERR_DRIFTTO		BIT_ULL(24)
#घोषणा KOMEDA_ERR_FRAMETO		BIT_ULL(25)
#घोषणा KOMEDA_ERR_CSCE			BIT_ULL(26)
#घोषणा KOMEDA_ERR_ZME			BIT_ULL(27)
#घोषणा KOMEDA_ERR_MERR			BIT_ULL(28)
#घोषणा KOMEDA_ERR_TCF			BIT_ULL(29)
#घोषणा KOMEDA_ERR_TTNG			BIT_ULL(30)
#घोषणा KOMEDA_ERR_TTF			BIT_ULL(31)

#घोषणा KOMEDA_ERR_EVENTS	\
	(KOMEDA_EVENT_URUN	| KOMEDA_EVENT_IBSY	| KOMEDA_EVENT_OVR |\
	KOMEDA_ERR_TETO		| KOMEDA_ERR_TEMR	| KOMEDA_ERR_TITR |\
	KOMEDA_ERR_CPE		| KOMEDA_ERR_CFGE	| KOMEDA_ERR_AXIE |\
	KOMEDA_ERR_ACE0		| KOMEDA_ERR_ACE1	| KOMEDA_ERR_ACE2 |\
	KOMEDA_ERR_ACE3		| KOMEDA_ERR_DRIFTTO	| KOMEDA_ERR_FRAMETO |\
	KOMEDA_ERR_ZME		| KOMEDA_ERR_MERR	| KOMEDA_ERR_TCF |\
	KOMEDA_ERR_TTNG		| KOMEDA_ERR_TTF)

#घोषणा KOMEDA_WARN_EVENTS	\
	(KOMEDA_ERR_CSCE | KOMEDA_EVENT_FULL | KOMEDA_EVENT_EMPTY)

#घोषणा KOMEDA_INFO_EVENTS (0 \
			    | KOMEDA_EVENT_VSYNC \
			    | KOMEDA_EVENT_FLIP \
			    | KOMEDA_EVENT_EOW \
			    | KOMEDA_EVENT_MODE \
			    )

/* pipeline DT ports */
क्रमागत अणु
	KOMEDA_OF_PORT_OUTPUT		= 0,
	KOMEDA_OF_PORT_COPROC		= 1,
पूर्ण;

काष्ठा komeda_chip_info अणु
	u32 arch_id;
	u32 core_id;
	u32 core_info;
	u32 bus_width;
पूर्ण;

काष्ठा komeda_dev;

काष्ठा komeda_events अणु
	u64 global;
	u64 pipes[KOMEDA_MAX_PIPELINES];
पूर्ण;

/**
 * काष्ठा komeda_dev_funcs
 *
 * Supplied by chip level and वापसed by the chip entry function xxx_identअगरy,
 */
काष्ठा komeda_dev_funcs अणु
	/**
	 * @init_क्रमmat_table:
	 *
	 * initialize &komeda_dev->क्रमmat_table, this function should be called
	 * beक्रमe the &क्रमागत_resource
	 */
	व्योम (*init_क्रमmat_table)(काष्ठा komeda_dev *mdev);
	/**
	 * @क्रमागत_resources:
	 *
	 * क्रम CHIP to report or add pipeline and component resources to CORE
	 */
	पूर्णांक (*क्रमागत_resources)(काष्ठा komeda_dev *mdev);
	/** @cleanup: call to chip to cleanup komeda_dev->chip data */
	व्योम (*cleanup)(काष्ठा komeda_dev *mdev);
	/** @connect_iommu: Optional, connect to बाह्यal iommu */
	पूर्णांक (*connect_iommu)(काष्ठा komeda_dev *mdev);
	/** @disconnect_iommu: Optional, disconnect to बाह्यal iommu */
	पूर्णांक (*disconnect_iommu)(काष्ठा komeda_dev *mdev);
	/**
	 * @irq_handler:
	 *
	 * क्रम CORE to get the HW event from the CHIP when पूर्णांकerrupt happened.
	 */
	irqवापस_t (*irq_handler)(काष्ठा komeda_dev *mdev,
				   काष्ठा komeda_events *events);
	/** @enable_irq: enable irq */
	पूर्णांक (*enable_irq)(काष्ठा komeda_dev *mdev);
	/** @disable_irq: disable irq */
	पूर्णांक (*disable_irq)(काष्ठा komeda_dev *mdev);
	/** @on_off_vblank: notअगरy HW to on/off vblank */
	व्योम (*on_off_vblank)(काष्ठा komeda_dev *mdev,
			      पूर्णांक master_pipe, bool on);

	/** @dump_रेजिस्टर: Optional, dump रेजिस्टरs to seq_file */
	व्योम (*dump_रेजिस्टर)(काष्ठा komeda_dev *mdev, काष्ठा seq_file *seq);
	/**
	 * @change_opmode:
	 *
	 * Notअगरy HW to चयन to a new display operation mode.
	 */
	पूर्णांक (*change_opmode)(काष्ठा komeda_dev *mdev, पूर्णांक new_mode);
	/** @flush: Notअगरy the HW to flush or kickoff the update */
	व्योम (*flush)(काष्ठा komeda_dev *mdev,
		      पूर्णांक master_pipe, u32 active_pipes);
पूर्ण;

/*
 * DISPLAY_MODE describes how many display been enabled, and which will be
 * passed to CHIP by &komeda_dev_funcs->change_opmode(), then CHIP can करो the
 * pipeline resources assignment according to this usage hपूर्णांक.
 * -   KOMEDA_MODE_DISP0: Only one display enabled, pipeline-0 work as master.
 * -   KOMEDA_MODE_DISP1: Only one display enabled, pipeline-0 work as master.
 * -   KOMEDA_MODE_DUAL_DISP: Dual display mode, both display has been enabled.
 * And D71 supports assign two pipelines to one single display on mode
 * KOMEDA_MODE_DISP0/DISP1
 */
क्रमागत अणु
	KOMEDA_MODE_INACTIVE	= 0,
	KOMEDA_MODE_DISP0	= BIT(0),
	KOMEDA_MODE_DISP1	= BIT(1),
	KOMEDA_MODE_DUAL_DISP	= KOMEDA_MODE_DISP0 | KOMEDA_MODE_DISP1,
पूर्ण;

/**
 * काष्ठा komeda_dev
 *
 * Pipeline and component are used to describe how to handle the pixel data.
 * komeda_device is क्रम describing the whole view of the device, and the
 * control-abilites of device.
 */
काष्ठा komeda_dev अणु
	/** @dev: the base device काष्ठाure */
	काष्ठा device *dev;
	/** @reg_base: the base address of komeda io space */
	u32 __iomem   *reg_base;

	/** @chip: the basic chip inक्रमmation */
	काष्ठा komeda_chip_info chip;
	/** @fmt_tbl: initialized by &komeda_dev_funcs->init_क्रमmat_table */
	काष्ठा komeda_क्रमmat_caps_table fmt_tbl;
	/** @aclk: HW मुख्य engine clk */
	काष्ठा clk *aclk;

	/** @irq: irq number */
	पूर्णांक irq;

	/** @lock: used to protect dpmode */
	काष्ठा mutex lock;
	/** @dpmode: current display mode */
	u32 dpmode;

	/** @n_pipelines: the number of pipe in @pipelines */
	पूर्णांक n_pipelines;
	/** @pipelines: the komeda pipelines */
	काष्ठा komeda_pipeline *pipelines[KOMEDA_MAX_PIPELINES];

	/** @funcs: chip funcs to access to HW */
	स्थिर काष्ठा komeda_dev_funcs *funcs;
	/**
	 * @chip_data:
	 *
	 * chip data will be added by &komeda_dev_funcs.क्रमागत_resources() and
	 * destroyed by &komeda_dev_funcs.cleanup()
	 */
	व्योम *chip_data;

	/** @iommu: iommu करोमुख्य */
	काष्ठा iommu_करोमुख्य *iommu;

	/** @debugfs_root: root directory of komeda debugfs */
	काष्ठा dentry *debugfs_root;
	/**
	 * @err_verbosity: biपंचांगask क्रम how much extra info to prपूर्णांक on error
	 *
	 * See KOMEDA_DEV_* macros क्रम details. Low byte contains the debug
	 * level categories, the high byte contains extra debug options.
	 */
	u16 err_verbosity;
	/* Prपूर्णांक a single line per error per frame with error events. */
#घोषणा KOMEDA_DEV_PRINT_ERR_EVENTS BIT(0)
	/* Prपूर्णांक a single line per warning per frame with error events. */
#घोषणा KOMEDA_DEV_PRINT_WARN_EVENTS BIT(1)
	/* Prपूर्णांक a single line per info event per frame with error events. */
#घोषणा KOMEDA_DEV_PRINT_INFO_EVENTS BIT(2)
	/* Dump DRM state on an error or warning event. */
#घोषणा KOMEDA_DEV_PRINT_DUMP_STATE_ON_EVENT BIT(8)
	/* Disable rate limiting of event prपूर्णांकs (normally one per commit) */
#घोषणा KOMEDA_DEV_PRINT_DISABLE_RATELIMIT BIT(12)
पूर्ण;

अटल अंतरभूत bool
komeda_product_match(काष्ठा komeda_dev *mdev, u32 target)
अणु
	वापस MALIDP_CORE_ID_PRODUCT_ID(mdev->chip.core_id) == target;
पूर्ण

प्रकार स्थिर काष्ठा komeda_dev_funcs *
(*komeda_identअगरy_func)(u32 __iomem *reg, काष्ठा komeda_chip_info *chip);

स्थिर काष्ठा komeda_dev_funcs *
d71_identअगरy(u32 __iomem *reg, काष्ठा komeda_chip_info *chip);

काष्ठा komeda_dev *komeda_dev_create(काष्ठा device *dev);
व्योम komeda_dev_destroy(काष्ठा komeda_dev *mdev);

काष्ठा komeda_dev *dev_to_mdev(काष्ठा device *dev);

व्योम komeda_prपूर्णांक_events(काष्ठा komeda_events *evts, काष्ठा drm_device *dev);

पूर्णांक komeda_dev_resume(काष्ठा komeda_dev *mdev);
पूर्णांक komeda_dev_suspend(काष्ठा komeda_dev *mdev);

#पूर्ण_अगर /*_KOMEDA_DEV_H_*/
