<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * MMC definitions क्रम OMAP2
 *
 * Copyright (C) 2006 Nokia Corporation
 */

#घोषणा OMAP_MMC_MAX_SLOTS	2

काष्ठा mmc_card;

काष्ठा omap_mmc_platक्रमm_data अणु
	/* back-link to device */
	काष्ठा device *dev;

	/* number of slots per controller */
	अचिन्हित nr_slots:2;

	/* set अगर your board has components or wiring that limits the
	 * maximum frequency on the MMC bus */
	अचिन्हित पूर्णांक max_freq;

	/* चयन the bus to a new slot */
	पूर्णांक (*चयन_slot)(काष्ठा device *dev, पूर्णांक slot);
	/* initialize board-specअगरic MMC functionality, can be शून्य अगर
	 * not supported */
	पूर्णांक (*init)(काष्ठा device *dev);
	व्योम (*cleanup)(काष्ठा device *dev);
	व्योम (*shutकरोwn)(काष्ठा device *dev);

	/* Return context loss count due to PM states changing */
	पूर्णांक (*get_context_loss_count)(काष्ठा device *dev);

	/* Integrating attributes from the omap_hwmod layer */
	u8 controller_flags;

	/* Register offset deviation */
	u16 reg_offset;

	काष्ठा omap_mmc_slot_data अणु

		/*
		 * 4/8 wires and any additional host capabilities
		 * need to OR'd all capabilities (ref. linux/mmc/host.h)
		 */
		u8  wires;	/* Used क्रम the MMC driver on omap1 and 2420 */
		u32 caps;	/* Used क्रम the MMC driver on 2430 and later */
		u32 pm_caps;	/* PM capabilities of the mmc */

		/*
		 * nomux means "standard" muxing is wrong on this board, and
		 * that board-specअगरic code handled it beक्रमe common init logic.
		 */
		अचिन्हित nomux:1;

		/* चयन pin can be क्रम card detect (शेष) or card cover */
		अचिन्हित cover:1;

		/* use the पूर्णांकernal घड़ी */
		अचिन्हित पूर्णांकernal_घड़ी:1;

		/* nonremovable e.g. eMMC */
		अचिन्हित nonremovable:1;

		/* Try to sleep or घातer off when possible */
		अचिन्हित घातer_saving:1;

		/* If using घातer_saving and the MMC घातer is not to go off */
		अचिन्हित no_off:1;

		/* eMMC करोes not handle घातer off when not in sleep state */
		अचिन्हित no_regulator_off_init:1;

		/* Regulator off remapped to sleep */
		अचिन्हित vcc_aux_disable_is_sleep:1;

		/* we can put the features above पूर्णांकo this variable */
#घोषणा MMC_OMAP7XX		(1 << 3)
#घोषणा MMC_OMAP15XX		(1 << 4)
#घोषणा MMC_OMAP16XX		(1 << 5)
		अचिन्हित features;

		पूर्णांक चयन_pin;			/* gpio (card detect) */
		पूर्णांक gpio_wp;			/* gpio (ग_लिखो protect) */

		पूर्णांक (*set_bus_mode)(काष्ठा device *dev, पूर्णांक slot, पूर्णांक bus_mode);
		पूर्णांक (*set_घातer)(काष्ठा device *dev, पूर्णांक slot,
				 पूर्णांक घातer_on, पूर्णांक vdd);
		पूर्णांक (*get_ro)(काष्ठा device *dev, पूर्णांक slot);
		व्योम (*remux)(काष्ठा device *dev, पूर्णांक slot, पूर्णांक घातer_on);
		/* Call back beक्रमe enabling / disabling regulators */
		व्योम (*beक्रमe_set_reg)(काष्ठा device *dev, पूर्णांक slot,
				       पूर्णांक घातer_on, पूर्णांक vdd);
		/* Call back after enabling / disabling regulators */
		व्योम (*after_set_reg)(काष्ठा device *dev, पूर्णांक slot,
				      पूर्णांक घातer_on, पूर्णांक vdd);
		/* अगर we have special card, init it using this callback */
		व्योम (*init_card)(काष्ठा mmc_card *card);

		/* वापस MMC cover चयन state, can be शून्य अगर not supported.
		 *
		 * possible वापस values:
		 *   0 - बंदd
		 *   1 - खोलो
		 */
		पूर्णांक (*get_cover_state)(काष्ठा device *dev, पूर्णांक slot);

		स्थिर अक्षर *name;
		u32 ocr_mask;

		/* Card detection */
		पूर्णांक (*card_detect)(काष्ठा device *dev, पूर्णांक slot);

		अचिन्हित पूर्णांक ban_खोलोended:1;

	पूर्ण slots[OMAP_MMC_MAX_SLOTS];
पूर्ण;

बाह्य व्योम omap_mmc_notअगरy_cover_event(काष्ठा device *dev, पूर्णांक slot,
					पूर्णांक is_बंदd);
