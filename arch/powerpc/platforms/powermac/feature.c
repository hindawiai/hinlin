<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (C) 1996-2001 Paul Mackerras (paulus@cs.anu.edu.au)
 *                          Ben. Herrenschmidt (benh@kernel.crashing.org)
 *
 *  TODO:
 *
 *   - Replace mdelay with some schedule loop अगर possible
 *   - Shorten some obfuscated delays on some routines (like modem
 *     घातer)
 *   - Refcount some घड़ीs (see darwin)
 *   - Split split split...
 */
#समावेश <linux/types.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/adb.h>
#समावेश <linux/pmu.h>
#समावेश <linux/ioport.h>
#समावेश <linux/export.h>
#समावेश <linux/pci.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/त्रुटिसं.स>
#समावेश <यंत्र/ohare.h>
#समावेश <यंत्र/heathrow.h>
#समावेश <यंत्र/keylargo.h>
#समावेश <यंत्र/uninorth.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/pmac_feature.h>
#समावेश <यंत्र/dbdma.h>
#समावेश <यंत्र/pci-bridge.h>
#समावेश <यंत्र/pmac_low_i2c.h>

#अघोषित DEBUG_FEATURE

#अगर_घोषित DEBUG_FEATURE
#घोषणा DBG(fmt...) prपूर्णांकk(KERN_DEBUG fmt)
#अन्यथा
#घोषणा DBG(fmt...)
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC_BOOK3S_32
बाह्य पूर्णांक घातersave_lowspeed;
#पूर्ण_अगर

बाह्य पूर्णांक घातersave_nap;
बाह्य काष्ठा device_node *k2_skiplist[2];

/*
 * We use a single global lock to protect accesses. Each driver has
 * to take care of its own locking
 */
DEFINE_RAW_SPINLOCK(feature_lock);

#घोषणा LOCK(flags)	raw_spin_lock_irqsave(&feature_lock, flags);
#घोषणा UNLOCK(flags)	raw_spin_unlock_irqrestore(&feature_lock, flags);


/*
 * Instance of some macio stuffs
 */
काष्ठा macio_chip macio_chips[MAX_MACIO_CHIPS];

काष्ठा macio_chip *macio_find(काष्ठा device_node *child, पूर्णांक type)
अणु
	जबतक(child) अणु
		पूर्णांक	i;

		क्रम (i=0; i < MAX_MACIO_CHIPS && macio_chips[i].of_node; i++)
			अगर (child == macio_chips[i].of_node &&
			    (!type || macio_chips[i].type == type))
				वापस &macio_chips[i];
		child = child->parent;
	पूर्ण
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(macio_find);

अटल स्थिर अक्षर *macio_names[] =
अणु
	"Unknown",
	"Grand Central",
	"OHare",
	"OHareII",
	"Heathrow",
	"Gatwick",
	"Paddington",
	"Keylargo",
	"Pangea",
	"Intrepid",
	"K2",
	"Shasta",
पूर्ण;


काष्ठा device_node *uninorth_node;
u32 __iomem *uninorth_base;

अटल u32 uninorth_rev;
अटल पूर्णांक uninorth_maj;
अटल व्योम __iomem *u3_ht_base;

/*
 * For each motherboard family, we have a table of functions poपूर्णांकers
 * that handle the various features.
 */

प्रकार दीर्घ (*feature_call)(काष्ठा device_node *node, दीर्घ param, दीर्घ value);

काष्ठा feature_table_entry अणु
	अचिन्हित पूर्णांक	selector;
	feature_call	function;
पूर्ण;

काष्ठा pmac_mb_def
अणु
	स्थिर अक्षर*			model_string;
	स्थिर अक्षर*			model_name;
	पूर्णांक				model_id;
	काष्ठा feature_table_entry*	features;
	अचिन्हित दीर्घ			board_flags;
पूर्ण;
अटल काष्ठा pmac_mb_def pmac_mb;

/*
 * Here are the chip specअगरic feature functions
 */

अटल अंतरभूत पूर्णांक simple_feature_tweak(काष्ठा device_node *node, पूर्णांक type,
				       पूर्णांक reg, u32 mask, पूर्णांक value)
अणु
	काष्ठा macio_chip*	macio;
	अचिन्हित दीर्घ		flags;

	macio = macio_find(node, type);
	अगर (!macio)
		वापस -ENODEV;
	LOCK(flags);
	अगर (value)
		MACIO_BIS(reg, mask);
	अन्यथा
		MACIO_BIC(reg, mask);
	(व्योम)MACIO_IN32(reg);
	UNLOCK(flags);

	वापस 0;
पूर्ण

#अगर_अघोषित CONFIG_PPC64

अटल दीर्घ ohare_htw_scc_enable(काष्ठा device_node *node, दीर्घ param,
				 दीर्घ value)
अणु
	काष्ठा macio_chip*	macio;
	अचिन्हित दीर्घ		chan_mask;
	अचिन्हित दीर्घ		fcr;
	अचिन्हित दीर्घ		flags;
	पूर्णांक			htw, trans;
	अचिन्हित दीर्घ		rmask;

	macio = macio_find(node, 0);
	अगर (!macio)
		वापस -ENODEV;
	अगर (of_node_name_eq(node, "ch-a"))
		chan_mask = MACIO_FLAG_SCCA_ON;
	अन्यथा अगर (of_node_name_eq(node, "ch-b"))
		chan_mask = MACIO_FLAG_SCCB_ON;
	अन्यथा
		वापस -ENODEV;

	htw = (macio->type == macio_heathrow || macio->type == macio_paddington
		|| macio->type == macio_gatwick);
	/* On these machines, the HRW_SCC_TRANS_EN_N bit mustn't be touched */
	trans = (pmac_mb.model_id != PMAC_TYPE_YOSEMITE &&
		 pmac_mb.model_id != PMAC_TYPE_YIKES);
	अगर (value) अणु
#अगर_घोषित CONFIG_ADB_PMU
		अगर ((param & 0xfff) == PMAC_SCC_IRDA)
			pmu_enable_irled(1);
#पूर्ण_अगर /* CONFIG_ADB_PMU */
		LOCK(flags);
		fcr = MACIO_IN32(OHARE_FCR);
		/* Check अगर scc cell need enabling */
		अगर (!(fcr & OH_SCC_ENABLE)) अणु
			fcr |= OH_SCC_ENABLE;
			अगर (htw) अणु
				/* Side effect: this will also घातer up the
				 * modem, but it's too messy to figure out on which
				 * ports this controls the transceiver and on which
				 * it controls the modem
				 */
				अगर (trans)
					fcr &= ~HRW_SCC_TRANS_EN_N;
				MACIO_OUT32(OHARE_FCR, fcr);
				fcr |= (rmask = HRW_RESET_SCC);
				MACIO_OUT32(OHARE_FCR, fcr);
			पूर्ण अन्यथा अणु
				fcr |= (rmask = OH_SCC_RESET);
				MACIO_OUT32(OHARE_FCR, fcr);
			पूर्ण
			UNLOCK(flags);
			(व्योम)MACIO_IN32(OHARE_FCR);
			mdelay(15);
			LOCK(flags);
			fcr &= ~rmask;
			MACIO_OUT32(OHARE_FCR, fcr);
		पूर्ण
		अगर (chan_mask & MACIO_FLAG_SCCA_ON)
			fcr |= OH_SCCA_IO;
		अगर (chan_mask & MACIO_FLAG_SCCB_ON)
			fcr |= OH_SCCB_IO;
		MACIO_OUT32(OHARE_FCR, fcr);
		macio->flags |= chan_mask;
		UNLOCK(flags);
		अगर (param & PMAC_SCC_FLAG_XMON)
			macio->flags |= MACIO_FLAG_SCC_LOCKED;
	पूर्ण अन्यथा अणु
		अगर (macio->flags & MACIO_FLAG_SCC_LOCKED)
			वापस -EPERM;
		LOCK(flags);
		fcr = MACIO_IN32(OHARE_FCR);
		अगर (chan_mask & MACIO_FLAG_SCCA_ON)
			fcr &= ~OH_SCCA_IO;
		अगर (chan_mask & MACIO_FLAG_SCCB_ON)
			fcr &= ~OH_SCCB_IO;
		MACIO_OUT32(OHARE_FCR, fcr);
		अगर ((fcr & (OH_SCCA_IO | OH_SCCB_IO)) == 0) अणु
			fcr &= ~OH_SCC_ENABLE;
			अगर (htw && trans)
				fcr |= HRW_SCC_TRANS_EN_N;
			MACIO_OUT32(OHARE_FCR, fcr);
		पूर्ण
		macio->flags &= ~(chan_mask);
		UNLOCK(flags);
		mdelay(10);
#अगर_घोषित CONFIG_ADB_PMU
		अगर ((param & 0xfff) == PMAC_SCC_IRDA)
			pmu_enable_irled(0);
#पूर्ण_अगर /* CONFIG_ADB_PMU */
	पूर्ण
	वापस 0;
पूर्ण

अटल दीर्घ ohare_floppy_enable(काष्ठा device_node *node, दीर्घ param,
				दीर्घ value)
अणु
	वापस simple_feature_tweak(node, macio_ohare,
		OHARE_FCR, OH_FLOPPY_ENABLE, value);
पूर्ण

अटल दीर्घ ohare_mesh_enable(काष्ठा device_node *node, दीर्घ param, दीर्घ value)
अणु
	वापस simple_feature_tweak(node, macio_ohare,
		OHARE_FCR, OH_MESH_ENABLE, value);
पूर्ण

अटल दीर्घ ohare_ide_enable(काष्ठा device_node *node, दीर्घ param, दीर्घ value)
अणु
	चयन(param) अणु
	हाल 0:
		/* For some reason, setting the bit in set_initial_features()
		 * करोesn't stick. I'm still investigating... --BenH.
		 */
		अगर (value)
			simple_feature_tweak(node, macio_ohare,
				OHARE_FCR, OH_IOBUS_ENABLE, 1);
		वापस simple_feature_tweak(node, macio_ohare,
			OHARE_FCR, OH_IDE0_ENABLE, value);
	हाल 1:
		वापस simple_feature_tweak(node, macio_ohare,
			OHARE_FCR, OH_BAY_IDE_ENABLE, value);
	शेष:
		वापस -ENODEV;
	पूर्ण
पूर्ण

अटल दीर्घ ohare_ide_reset(काष्ठा device_node *node, दीर्घ param, दीर्घ value)
अणु
	चयन(param) अणु
	हाल 0:
		वापस simple_feature_tweak(node, macio_ohare,
			OHARE_FCR, OH_IDE0_RESET_N, !value);
	हाल 1:
		वापस simple_feature_tweak(node, macio_ohare,
			OHARE_FCR, OH_IDE1_RESET_N, !value);
	शेष:
		वापस -ENODEV;
	पूर्ण
पूर्ण

अटल दीर्घ ohare_sleep_state(काष्ठा device_node *node, दीर्घ param, दीर्घ value)
अणु
	काष्ठा macio_chip*	macio = &macio_chips[0];

	अगर ((pmac_mb.board_flags & PMAC_MB_CAN_SLEEP) == 0)
		वापस -EPERM;
	अगर (value == 1) अणु
		MACIO_BIC(OHARE_FCR, OH_IOBUS_ENABLE);
	पूर्ण अन्यथा अगर (value == 0) अणु
		MACIO_BIS(OHARE_FCR, OH_IOBUS_ENABLE);
	पूर्ण

	वापस 0;
पूर्ण

अटल दीर्घ heathrow_modem_enable(काष्ठा device_node *node, दीर्घ param,
				  दीर्घ value)
अणु
	काष्ठा macio_chip*	macio;
	u8			gpio;
	अचिन्हित दीर्घ		flags;

	macio = macio_find(node, macio_unknown);
	अगर (!macio)
		वापस -ENODEV;
	gpio = MACIO_IN8(HRW_GPIO_MODEM_RESET) & ~1;
	अगर (!value) अणु
		LOCK(flags);
		MACIO_OUT8(HRW_GPIO_MODEM_RESET, gpio);
		UNLOCK(flags);
		(व्योम)MACIO_IN8(HRW_GPIO_MODEM_RESET);
		mdelay(250);
	पूर्ण
	अगर (pmac_mb.model_id != PMAC_TYPE_YOSEMITE &&
	    pmac_mb.model_id != PMAC_TYPE_YIKES) अणु
		LOCK(flags);
		अगर (value)
			MACIO_BIC(HEATHROW_FCR, HRW_SCC_TRANS_EN_N);
		अन्यथा
			MACIO_BIS(HEATHROW_FCR, HRW_SCC_TRANS_EN_N);
		UNLOCK(flags);
		(व्योम)MACIO_IN32(HEATHROW_FCR);
		mdelay(250);
	पूर्ण
	अगर (value) अणु
		LOCK(flags);
		MACIO_OUT8(HRW_GPIO_MODEM_RESET, gpio | 1);
		(व्योम)MACIO_IN8(HRW_GPIO_MODEM_RESET);
		UNLOCK(flags); mdelay(250); LOCK(flags);
		MACIO_OUT8(HRW_GPIO_MODEM_RESET, gpio);
		(व्योम)MACIO_IN8(HRW_GPIO_MODEM_RESET);
		UNLOCK(flags); mdelay(250); LOCK(flags);
		MACIO_OUT8(HRW_GPIO_MODEM_RESET, gpio | 1);
		(व्योम)MACIO_IN8(HRW_GPIO_MODEM_RESET);
		UNLOCK(flags); mdelay(250);
	पूर्ण
	वापस 0;
पूर्ण

अटल दीर्घ heathrow_floppy_enable(काष्ठा device_node *node, दीर्घ param,
				   दीर्घ value)
अणु
	वापस simple_feature_tweak(node, macio_unknown,
		HEATHROW_FCR,
		HRW_SWIM_ENABLE|HRW_BAY_FLOPPY_ENABLE,
		value);
पूर्ण

अटल दीर्घ heathrow_mesh_enable(काष्ठा device_node *node, दीर्घ param,
				 दीर्घ value)
अणु
	काष्ठा macio_chip*	macio;
	अचिन्हित दीर्घ		flags;

	macio = macio_find(node, macio_unknown);
	अगर (!macio)
		वापस -ENODEV;
	LOCK(flags);
	/* Set clear mesh cell enable */
	अगर (value)
		MACIO_BIS(HEATHROW_FCR, HRW_MESH_ENABLE);
	अन्यथा
		MACIO_BIC(HEATHROW_FCR, HRW_MESH_ENABLE);
	(व्योम)MACIO_IN32(HEATHROW_FCR);
	udelay(10);
	/* Set/Clear termination घातer */
	अगर (value)
		MACIO_BIC(HEATHROW_MBCR, 0x04000000);
	अन्यथा
		MACIO_BIS(HEATHROW_MBCR, 0x04000000);
	(व्योम)MACIO_IN32(HEATHROW_MBCR);
	udelay(10);
	UNLOCK(flags);

	वापस 0;
पूर्ण

अटल दीर्घ heathrow_ide_enable(काष्ठा device_node *node, दीर्घ param,
				दीर्घ value)
अणु
	चयन(param) अणु
	हाल 0:
		वापस simple_feature_tweak(node, macio_unknown,
			HEATHROW_FCR, HRW_IDE0_ENABLE, value);
	हाल 1:
		वापस simple_feature_tweak(node, macio_unknown,
			HEATHROW_FCR, HRW_BAY_IDE_ENABLE, value);
	शेष:
		वापस -ENODEV;
	पूर्ण
पूर्ण

अटल दीर्घ heathrow_ide_reset(काष्ठा device_node *node, दीर्घ param,
			       दीर्घ value)
अणु
	चयन(param) अणु
	हाल 0:
		वापस simple_feature_tweak(node, macio_unknown,
			HEATHROW_FCR, HRW_IDE0_RESET_N, !value);
	हाल 1:
		वापस simple_feature_tweak(node, macio_unknown,
			HEATHROW_FCR, HRW_IDE1_RESET_N, !value);
	शेष:
		वापस -ENODEV;
	पूर्ण
पूर्ण

अटल दीर्घ heathrow_bmac_enable(काष्ठा device_node *node, दीर्घ param,
				 दीर्घ value)
अणु
	काष्ठा macio_chip*	macio;
	अचिन्हित दीर्घ		flags;

	macio = macio_find(node, 0);
	अगर (!macio)
		वापस -ENODEV;
	अगर (value) अणु
		LOCK(flags);
		MACIO_BIS(HEATHROW_FCR, HRW_BMAC_IO_ENABLE);
		MACIO_BIS(HEATHROW_FCR, HRW_BMAC_RESET);
		UNLOCK(flags);
		(व्योम)MACIO_IN32(HEATHROW_FCR);
		mdelay(10);
		LOCK(flags);
		MACIO_BIC(HEATHROW_FCR, HRW_BMAC_RESET);
		UNLOCK(flags);
		(व्योम)MACIO_IN32(HEATHROW_FCR);
		mdelay(10);
	पूर्ण अन्यथा अणु
		LOCK(flags);
		MACIO_BIC(HEATHROW_FCR, HRW_BMAC_IO_ENABLE);
		UNLOCK(flags);
	पूर्ण
	वापस 0;
पूर्ण

अटल दीर्घ heathrow_sound_enable(काष्ठा device_node *node, दीर्घ param,
				  दीर्घ value)
अणु
	काष्ठा macio_chip*	macio;
	अचिन्हित दीर्घ		flags;

	/* B&W G3 and Yikes करोn't support that properly (the
	 * sound appear to never come back after being shut करोwn).
	 */
	अगर (pmac_mb.model_id == PMAC_TYPE_YOSEMITE ||
	    pmac_mb.model_id == PMAC_TYPE_YIKES)
		वापस 0;

	macio = macio_find(node, 0);
	अगर (!macio)
		वापस -ENODEV;
	अगर (value) अणु
		LOCK(flags);
		MACIO_BIS(HEATHROW_FCR, HRW_SOUND_CLK_ENABLE);
		MACIO_BIC(HEATHROW_FCR, HRW_SOUND_POWER_N);
		UNLOCK(flags);
		(व्योम)MACIO_IN32(HEATHROW_FCR);
	पूर्ण अन्यथा अणु
		LOCK(flags);
		MACIO_BIS(HEATHROW_FCR, HRW_SOUND_POWER_N);
		MACIO_BIC(HEATHROW_FCR, HRW_SOUND_CLK_ENABLE);
		UNLOCK(flags);
	पूर्ण
	वापस 0;
पूर्ण

अटल u32 save_fcr[6];
अटल u32 save_mbcr;
अटल काष्ठा dbdma_regs save_dbdma[13];
अटल काष्ठा dbdma_regs save_alt_dbdma[13];

अटल व्योम dbdma_save(काष्ठा macio_chip *macio, काष्ठा dbdma_regs *save)
अणु
	पूर्णांक i;

	/* Save state & config of DBDMA channels */
	क्रम (i = 0; i < 13; i++) अणु
		अस्थिर काष्ठा dbdma_regs __iomem * chan = (व्योम __iomem *)
			(macio->base + ((0x8000+i*0x100)>>2));
		save[i].cmdptr_hi = in_le32(&chan->cmdptr_hi);
		save[i].cmdptr = in_le32(&chan->cmdptr);
		save[i].पूर्णांकr_sel = in_le32(&chan->पूर्णांकr_sel);
		save[i].br_sel = in_le32(&chan->br_sel);
		save[i].रुको_sel = in_le32(&chan->रुको_sel);
	पूर्ण
पूर्ण

अटल व्योम dbdma_restore(काष्ठा macio_chip *macio, काष्ठा dbdma_regs *save)
अणु
	पूर्णांक i;

	/* Save state & config of DBDMA channels */
	क्रम (i = 0; i < 13; i++) अणु
		अस्थिर काष्ठा dbdma_regs __iomem * chan = (व्योम __iomem *)
			(macio->base + ((0x8000+i*0x100)>>2));
		out_le32(&chan->control, (ACTIVE|DEAD|WAKE|FLUSH|PAUSE|RUN)<<16);
		जबतक (in_le32(&chan->status) & ACTIVE)
			mb();
		out_le32(&chan->cmdptr_hi, save[i].cmdptr_hi);
		out_le32(&chan->cmdptr, save[i].cmdptr);
		out_le32(&chan->पूर्णांकr_sel, save[i].पूर्णांकr_sel);
		out_le32(&chan->br_sel, save[i].br_sel);
		out_le32(&chan->रुको_sel, save[i].रुको_sel);
	पूर्ण
पूर्ण

अटल व्योम heathrow_sleep(काष्ठा macio_chip *macio, पूर्णांक secondary)
अणु
	अगर (secondary) अणु
		dbdma_save(macio, save_alt_dbdma);
		save_fcr[2] = MACIO_IN32(0x38);
		save_fcr[3] = MACIO_IN32(0x3c);
	पूर्ण अन्यथा अणु
		dbdma_save(macio, save_dbdma);
		save_fcr[0] = MACIO_IN32(0x38);
		save_fcr[1] = MACIO_IN32(0x3c);
		save_mbcr = MACIO_IN32(0x34);
		/* Make sure sound is shut करोwn */
		MACIO_BIS(HEATHROW_FCR, HRW_SOUND_POWER_N);
		MACIO_BIC(HEATHROW_FCR, HRW_SOUND_CLK_ENABLE);
		/* This seems to be necessary as well or the fan
		 * keeps coming up and battery drains fast */
		MACIO_BIC(HEATHROW_FCR, HRW_IOBUS_ENABLE);
		MACIO_BIC(HEATHROW_FCR, HRW_IDE0_RESET_N);
		/* Make sure eth is करोwn even अगर module or sleep
		 * won't work properly */
		MACIO_BIC(HEATHROW_FCR, HRW_BMAC_IO_ENABLE | HRW_BMAC_RESET);
	पूर्ण
	/* Make sure modem is shut करोwn */
	MACIO_OUT8(HRW_GPIO_MODEM_RESET,
		MACIO_IN8(HRW_GPIO_MODEM_RESET) & ~1);
	MACIO_BIS(HEATHROW_FCR, HRW_SCC_TRANS_EN_N);
	MACIO_BIC(HEATHROW_FCR, OH_SCCA_IO|OH_SCCB_IO|HRW_SCC_ENABLE);

	/* Let things settle */
	(व्योम)MACIO_IN32(HEATHROW_FCR);
पूर्ण

अटल व्योम heathrow_wakeup(काष्ठा macio_chip *macio, पूर्णांक secondary)
अणु
	अगर (secondary) अणु
		MACIO_OUT32(0x38, save_fcr[2]);
		(व्योम)MACIO_IN32(0x38);
		mdelay(1);
		MACIO_OUT32(0x3c, save_fcr[3]);
		(व्योम)MACIO_IN32(0x38);
		mdelay(10);
		dbdma_restore(macio, save_alt_dbdma);
	पूर्ण अन्यथा अणु
		MACIO_OUT32(0x38, save_fcr[0] | HRW_IOBUS_ENABLE);
		(व्योम)MACIO_IN32(0x38);
		mdelay(1);
		MACIO_OUT32(0x3c, save_fcr[1]);
		(व्योम)MACIO_IN32(0x38);
		mdelay(1);
		MACIO_OUT32(0x34, save_mbcr);
		(व्योम)MACIO_IN32(0x38);
		mdelay(10);
		dbdma_restore(macio, save_dbdma);
	पूर्ण
पूर्ण

अटल दीर्घ heathrow_sleep_state(काष्ठा device_node *node, दीर्घ param,
				 दीर्घ value)
अणु
	अगर ((pmac_mb.board_flags & PMAC_MB_CAN_SLEEP) == 0)
		वापस -EPERM;
	अगर (value == 1) अणु
		अगर (macio_chips[1].type == macio_gatwick)
			heathrow_sleep(&macio_chips[0], 1);
		heathrow_sleep(&macio_chips[0], 0);
	पूर्ण अन्यथा अगर (value == 0) अणु
		heathrow_wakeup(&macio_chips[0], 0);
		अगर (macio_chips[1].type == macio_gatwick)
			heathrow_wakeup(&macio_chips[0], 1);
	पूर्ण
	वापस 0;
पूर्ण

अटल दीर्घ core99_scc_enable(काष्ठा device_node *node, दीर्घ param, दीर्घ value)
अणु
	काष्ठा macio_chip*	macio;
	अचिन्हित दीर्घ		flags;
	अचिन्हित दीर्घ		chan_mask;
	u32			fcr;

	macio = macio_find(node, 0);
	अगर (!macio)
		वापस -ENODEV;
	अगर (of_node_name_eq(node, "ch-a"))
		chan_mask = MACIO_FLAG_SCCA_ON;
	अन्यथा अगर (of_node_name_eq(node, "ch-b"))
		chan_mask = MACIO_FLAG_SCCB_ON;
	अन्यथा
		वापस -ENODEV;

	अगर (value) अणु
		पूर्णांक need_reset_scc = 0;
		पूर्णांक need_reset_irda = 0;

		LOCK(flags);
		fcr = MACIO_IN32(KEYLARGO_FCR0);
		/* Check अगर scc cell need enabling */
		अगर (!(fcr & KL0_SCC_CELL_ENABLE)) अणु
			fcr |= KL0_SCC_CELL_ENABLE;
			need_reset_scc = 1;
		पूर्ण
		अगर (chan_mask & MACIO_FLAG_SCCA_ON) अणु
			fcr |= KL0_SCCA_ENABLE;
			/* Don't enable line drivers क्रम I2S modem */
			अगर ((param & 0xfff) == PMAC_SCC_I2S1)
				fcr &= ~KL0_SCC_A_INTF_ENABLE;
			अन्यथा
				fcr |= KL0_SCC_A_INTF_ENABLE;
		पूर्ण
		अगर (chan_mask & MACIO_FLAG_SCCB_ON) अणु
			fcr |= KL0_SCCB_ENABLE;
			/* Perक्रमm irda specअगरic inits */
			अगर ((param & 0xfff) == PMAC_SCC_IRDA) अणु
				fcr &= ~KL0_SCC_B_INTF_ENABLE;
				fcr |= KL0_IRDA_ENABLE;
				fcr |= KL0_IRDA_CLK32_ENABLE | KL0_IRDA_CLK19_ENABLE;
				fcr |= KL0_IRDA_SOURCE1_SEL;
				fcr &= ~(KL0_IRDA_FAST_CONNECT|KL0_IRDA_DEFAULT1|KL0_IRDA_DEFAULT0);
				fcr &= ~(KL0_IRDA_SOURCE2_SEL|KL0_IRDA_HIGH_BAND);
				need_reset_irda = 1;
			पूर्ण अन्यथा
				fcr |= KL0_SCC_B_INTF_ENABLE;
		पूर्ण
		MACIO_OUT32(KEYLARGO_FCR0, fcr);
		macio->flags |= chan_mask;
		अगर (need_reset_scc)  अणु
			MACIO_BIS(KEYLARGO_FCR0, KL0_SCC_RESET);
			(व्योम)MACIO_IN32(KEYLARGO_FCR0);
			UNLOCK(flags);
			mdelay(15);
			LOCK(flags);
			MACIO_BIC(KEYLARGO_FCR0, KL0_SCC_RESET);
		पूर्ण
		अगर (need_reset_irda)  अणु
			MACIO_BIS(KEYLARGO_FCR0, KL0_IRDA_RESET);
			(व्योम)MACIO_IN32(KEYLARGO_FCR0);
			UNLOCK(flags);
			mdelay(15);
			LOCK(flags);
			MACIO_BIC(KEYLARGO_FCR0, KL0_IRDA_RESET);
		पूर्ण
		UNLOCK(flags);
		अगर (param & PMAC_SCC_FLAG_XMON)
			macio->flags |= MACIO_FLAG_SCC_LOCKED;
	पूर्ण अन्यथा अणु
		अगर (macio->flags & MACIO_FLAG_SCC_LOCKED)
			वापस -EPERM;
		LOCK(flags);
		fcr = MACIO_IN32(KEYLARGO_FCR0);
		अगर (chan_mask & MACIO_FLAG_SCCA_ON)
			fcr &= ~KL0_SCCA_ENABLE;
		अगर (chan_mask & MACIO_FLAG_SCCB_ON) अणु
			fcr &= ~KL0_SCCB_ENABLE;
			/* Perक्रमm irda specअगरic clears */
			अगर ((param & 0xfff) == PMAC_SCC_IRDA) अणु
				fcr &= ~KL0_IRDA_ENABLE;
				fcr &= ~(KL0_IRDA_CLK32_ENABLE | KL0_IRDA_CLK19_ENABLE);
				fcr &= ~(KL0_IRDA_FAST_CONNECT|KL0_IRDA_DEFAULT1|KL0_IRDA_DEFAULT0);
				fcr &= ~(KL0_IRDA_SOURCE1_SEL|KL0_IRDA_SOURCE2_SEL|KL0_IRDA_HIGH_BAND);
			पूर्ण
		पूर्ण
		MACIO_OUT32(KEYLARGO_FCR0, fcr);
		अगर ((fcr & (KL0_SCCA_ENABLE | KL0_SCCB_ENABLE)) == 0) अणु
			fcr &= ~KL0_SCC_CELL_ENABLE;
			MACIO_OUT32(KEYLARGO_FCR0, fcr);
		पूर्ण
		macio->flags &= ~(chan_mask);
		UNLOCK(flags);
		mdelay(10);
	पूर्ण
	वापस 0;
पूर्ण

अटल दीर्घ
core99_modem_enable(काष्ठा device_node *node, दीर्घ param, दीर्घ value)
अणु
	काष्ठा macio_chip*	macio;
	u8			gpio;
	अचिन्हित दीर्घ		flags;

	/* Hack क्रम पूर्णांकernal USB modem */
	अगर (node == शून्य) अणु
		अगर (macio_chips[0].type != macio_keylargo)
			वापस -ENODEV;
		node = macio_chips[0].of_node;
	पूर्ण
	macio = macio_find(node, 0);
	अगर (!macio)
		वापस -ENODEV;
	gpio = MACIO_IN8(KL_GPIO_MODEM_RESET);
	gpio |= KEYLARGO_GPIO_OUTPUT_ENABLE;
	gpio &= ~KEYLARGO_GPIO_OUTOUT_DATA;

	अगर (!value) अणु
		LOCK(flags);
		MACIO_OUT8(KL_GPIO_MODEM_RESET, gpio);
		UNLOCK(flags);
		(व्योम)MACIO_IN8(KL_GPIO_MODEM_RESET);
		mdelay(250);
	पूर्ण
	LOCK(flags);
	अगर (value) अणु
		MACIO_BIC(KEYLARGO_FCR2, KL2_ALT_DATA_OUT);
		UNLOCK(flags);
		(व्योम)MACIO_IN32(KEYLARGO_FCR2);
		mdelay(250);
	पूर्ण अन्यथा अणु
		MACIO_BIS(KEYLARGO_FCR2, KL2_ALT_DATA_OUT);
		UNLOCK(flags);
	पूर्ण
	अगर (value) अणु
		LOCK(flags);
		MACIO_OUT8(KL_GPIO_MODEM_RESET, gpio | KEYLARGO_GPIO_OUTOUT_DATA);
		(व्योम)MACIO_IN8(KL_GPIO_MODEM_RESET);
		UNLOCK(flags); mdelay(250); LOCK(flags);
		MACIO_OUT8(KL_GPIO_MODEM_RESET, gpio);
		(व्योम)MACIO_IN8(KL_GPIO_MODEM_RESET);
		UNLOCK(flags); mdelay(250); LOCK(flags);
		MACIO_OUT8(KL_GPIO_MODEM_RESET, gpio | KEYLARGO_GPIO_OUTOUT_DATA);
		(व्योम)MACIO_IN8(KL_GPIO_MODEM_RESET);
		UNLOCK(flags); mdelay(250);
	पूर्ण
	वापस 0;
पूर्ण

अटल दीर्घ
pangea_modem_enable(काष्ठा device_node *node, दीर्घ param, दीर्घ value)
अणु
	काष्ठा macio_chip*	macio;
	u8			gpio;
	अचिन्हित दीर्घ		flags;

	/* Hack क्रम पूर्णांकernal USB modem */
	अगर (node == शून्य) अणु
		अगर (macio_chips[0].type != macio_pangea &&
		    macio_chips[0].type != macio_पूर्णांकrepid)
			वापस -ENODEV;
		node = macio_chips[0].of_node;
	पूर्ण
	macio = macio_find(node, 0);
	अगर (!macio)
		वापस -ENODEV;
	gpio = MACIO_IN8(KL_GPIO_MODEM_RESET);
	gpio |= KEYLARGO_GPIO_OUTPUT_ENABLE;
	gpio &= ~KEYLARGO_GPIO_OUTOUT_DATA;

	अगर (!value) अणु
		LOCK(flags);
		MACIO_OUT8(KL_GPIO_MODEM_RESET, gpio);
		UNLOCK(flags);
		(व्योम)MACIO_IN8(KL_GPIO_MODEM_RESET);
		mdelay(250);
	पूर्ण
	LOCK(flags);
	अगर (value) अणु
		MACIO_OUT8(KL_GPIO_MODEM_POWER,
			KEYLARGO_GPIO_OUTPUT_ENABLE);
		UNLOCK(flags);
		(व्योम)MACIO_IN32(KEYLARGO_FCR2);
		mdelay(250);
	पूर्ण अन्यथा अणु
		MACIO_OUT8(KL_GPIO_MODEM_POWER,
			KEYLARGO_GPIO_OUTPUT_ENABLE | KEYLARGO_GPIO_OUTOUT_DATA);
		UNLOCK(flags);
	पूर्ण
	अगर (value) अणु
		LOCK(flags);
		MACIO_OUT8(KL_GPIO_MODEM_RESET, gpio | KEYLARGO_GPIO_OUTOUT_DATA);
		(व्योम)MACIO_IN8(KL_GPIO_MODEM_RESET);
		UNLOCK(flags); mdelay(250); LOCK(flags);
		MACIO_OUT8(KL_GPIO_MODEM_RESET, gpio);
		(व्योम)MACIO_IN8(KL_GPIO_MODEM_RESET);
		UNLOCK(flags); mdelay(250); LOCK(flags);
		MACIO_OUT8(KL_GPIO_MODEM_RESET, gpio | KEYLARGO_GPIO_OUTOUT_DATA);
		(व्योम)MACIO_IN8(KL_GPIO_MODEM_RESET);
		UNLOCK(flags); mdelay(250);
	पूर्ण
	वापस 0;
पूर्ण

अटल दीर्घ
core99_ata100_enable(काष्ठा device_node *node, दीर्घ value)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा pci_dev *pdev = शून्य;
	u8 pbus, pid;
	पूर्णांक rc;

	अगर (uninorth_rev < 0x24)
		वापस -ENODEV;

	LOCK(flags);
	अगर (value)
		UN_BIS(UNI_N_CLOCK_CNTL, UNI_N_CLOCK_CNTL_ATA100);
	अन्यथा
		UN_BIC(UNI_N_CLOCK_CNTL, UNI_N_CLOCK_CNTL_ATA100);
	(व्योम)UN_IN(UNI_N_CLOCK_CNTL);
	UNLOCK(flags);
	udelay(20);

	अगर (value) अणु
		अगर (pci_device_from_OF_node(node, &pbus, &pid) == 0)
			pdev = pci_get_करोमुख्य_bus_and_slot(0, pbus, pid);
		अगर (pdev == शून्य)
			वापस 0;
		rc = pci_enable_device(pdev);
		अगर (rc == 0)
			pci_set_master(pdev);
		pci_dev_put(pdev);
		अगर (rc)
			वापस rc;
	पूर्ण
	वापस 0;
पूर्ण

अटल दीर्घ
core99_ide_enable(काष्ठा device_node *node, दीर्घ param, दीर्घ value)
अणु
	/* Bus ID 0 to 2 are KeyLargo based IDE, busID 3 is U2
	 * based ata-100
	 */
	चयन(param) अणु
	    हाल 0:
		वापस simple_feature_tweak(node, macio_unknown,
			KEYLARGO_FCR1, KL1_EIDE0_ENABLE, value);
	    हाल 1:
		वापस simple_feature_tweak(node, macio_unknown,
			KEYLARGO_FCR1, KL1_EIDE1_ENABLE, value);
	    हाल 2:
		वापस simple_feature_tweak(node, macio_unknown,
			KEYLARGO_FCR1, KL1_UIDE_ENABLE, value);
	    हाल 3:
		वापस core99_ata100_enable(node, value);
	    शेष:
		वापस -ENODEV;
	पूर्ण
पूर्ण

अटल दीर्घ
core99_ide_reset(काष्ठा device_node *node, दीर्घ param, दीर्घ value)
अणु
	चयन(param) अणु
	    हाल 0:
		वापस simple_feature_tweak(node, macio_unknown,
			KEYLARGO_FCR1, KL1_EIDE0_RESET_N, !value);
	    हाल 1:
		वापस simple_feature_tweak(node, macio_unknown,
			KEYLARGO_FCR1, KL1_EIDE1_RESET_N, !value);
	    हाल 2:
		वापस simple_feature_tweak(node, macio_unknown,
			KEYLARGO_FCR1, KL1_UIDE_RESET_N, !value);
	    शेष:
		वापस -ENODEV;
	पूर्ण
पूर्ण

अटल दीर्घ
core99_gmac_enable(काष्ठा device_node *node, दीर्घ param, दीर्घ value)
अणु
	अचिन्हित दीर्घ flags;

	LOCK(flags);
	अगर (value)
		UN_BIS(UNI_N_CLOCK_CNTL, UNI_N_CLOCK_CNTL_GMAC);
	अन्यथा
		UN_BIC(UNI_N_CLOCK_CNTL, UNI_N_CLOCK_CNTL_GMAC);
	(व्योम)UN_IN(UNI_N_CLOCK_CNTL);
	UNLOCK(flags);
	udelay(20);

	वापस 0;
पूर्ण

अटल दीर्घ
core99_gmac_phy_reset(काष्ठा device_node *node, दीर्घ param, दीर्घ value)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा macio_chip *macio;

	macio = &macio_chips[0];
	अगर (macio->type != macio_keylargo && macio->type != macio_pangea &&
	    macio->type != macio_पूर्णांकrepid)
		वापस -ENODEV;

	LOCK(flags);
	MACIO_OUT8(KL_GPIO_ETH_PHY_RESET, KEYLARGO_GPIO_OUTPUT_ENABLE);
	(व्योम)MACIO_IN8(KL_GPIO_ETH_PHY_RESET);
	UNLOCK(flags);
	mdelay(10);
	LOCK(flags);
	MACIO_OUT8(KL_GPIO_ETH_PHY_RESET, /*KEYLARGO_GPIO_OUTPUT_ENABLE | */
		KEYLARGO_GPIO_OUTOUT_DATA);
	UNLOCK(flags);
	mdelay(10);

	वापस 0;
पूर्ण

अटल दीर्घ
core99_sound_chip_enable(काष्ठा device_node *node, दीर्घ param, दीर्घ value)
अणु
	काष्ठा macio_chip*	macio;
	अचिन्हित दीर्घ		flags;

	macio = macio_find(node, 0);
	अगर (!macio)
		वापस -ENODEV;

	/* Do a better probe code, screamer G4 desktops &
	 * iMacs can करो that too, add a recalibrate  in
	 * the driver as well
	 */
	अगर (pmac_mb.model_id == PMAC_TYPE_PISMO ||
	    pmac_mb.model_id == PMAC_TYPE_TITANIUM) अणु
		LOCK(flags);
		अगर (value)
			MACIO_OUT8(KL_GPIO_SOUND_POWER,
				KEYLARGO_GPIO_OUTPUT_ENABLE |
				KEYLARGO_GPIO_OUTOUT_DATA);
		अन्यथा
			MACIO_OUT8(KL_GPIO_SOUND_POWER,
				KEYLARGO_GPIO_OUTPUT_ENABLE);
		(व्योम)MACIO_IN8(KL_GPIO_SOUND_POWER);
		UNLOCK(flags);
	पूर्ण
	वापस 0;
पूर्ण

अटल दीर्घ
core99_airport_enable(काष्ठा device_node *node, दीर्घ param, दीर्घ value)
अणु
	काष्ठा macio_chip*	macio;
	अचिन्हित दीर्घ		flags;
	पूर्णांक			state;

	macio = macio_find(node, 0);
	अगर (!macio)
		वापस -ENODEV;

	/* Hपूर्णांक: we allow passing of macio itself क्रम the sake of the
	 * sleep code
	 */
	अगर (node != macio->of_node &&
	    (!node->parent || node->parent != macio->of_node))
		वापस -ENODEV;
	state = (macio->flags & MACIO_FLAG_AIRPORT_ON) != 0;
	अगर (value == state)
		वापस 0;
	अगर (value) अणु
		/* This code is a reproduction of OF enable-cardslot
		 * and init-wireless methods, slightly hacked until
		 * I got it working.
		 */
		LOCK(flags);
		MACIO_OUT8(KEYLARGO_GPIO_0+0xf, 5);
		(व्योम)MACIO_IN8(KEYLARGO_GPIO_0+0xf);
		UNLOCK(flags);
		mdelay(10);
		LOCK(flags);
		MACIO_OUT8(KEYLARGO_GPIO_0+0xf, 4);
		(व्योम)MACIO_IN8(KEYLARGO_GPIO_0+0xf);
		UNLOCK(flags);

		mdelay(10);

		LOCK(flags);
		MACIO_BIC(KEYLARGO_FCR2, KL2_CARDSEL_16);
		(व्योम)MACIO_IN32(KEYLARGO_FCR2);
		udelay(10);
		MACIO_OUT8(KEYLARGO_GPIO_EXTINT_0+0xb, 0);
		(व्योम)MACIO_IN8(KEYLARGO_GPIO_EXTINT_0+0xb);
		udelay(10);
		MACIO_OUT8(KEYLARGO_GPIO_EXTINT_0+0xa, 0x28);
		(व्योम)MACIO_IN8(KEYLARGO_GPIO_EXTINT_0+0xa);
		udelay(10);
		MACIO_OUT8(KEYLARGO_GPIO_EXTINT_0+0xd, 0x28);
		(व्योम)MACIO_IN8(KEYLARGO_GPIO_EXTINT_0+0xd);
		udelay(10);
		MACIO_OUT8(KEYLARGO_GPIO_0+0xd, 0x28);
		(व्योम)MACIO_IN8(KEYLARGO_GPIO_0+0xd);
		udelay(10);
		MACIO_OUT8(KEYLARGO_GPIO_0+0xe, 0x28);
		(व्योम)MACIO_IN8(KEYLARGO_GPIO_0+0xe);
		UNLOCK(flags);
		udelay(10);
		MACIO_OUT32(0x1c000, 0);
		mdelay(1);
		MACIO_OUT8(0x1a3e0, 0x41);
		(व्योम)MACIO_IN8(0x1a3e0);
		udelay(10);
		LOCK(flags);
		MACIO_BIS(KEYLARGO_FCR2, KL2_CARDSEL_16);
		(व्योम)MACIO_IN32(KEYLARGO_FCR2);
		UNLOCK(flags);
		mdelay(100);

		macio->flags |= MACIO_FLAG_AIRPORT_ON;
	पूर्ण अन्यथा अणु
		LOCK(flags);
		MACIO_BIC(KEYLARGO_FCR2, KL2_CARDSEL_16);
		(व्योम)MACIO_IN32(KEYLARGO_FCR2);
		MACIO_OUT8(KL_GPIO_AIRPORT_0, 0);
		MACIO_OUT8(KL_GPIO_AIRPORT_1, 0);
		MACIO_OUT8(KL_GPIO_AIRPORT_2, 0);
		MACIO_OUT8(KL_GPIO_AIRPORT_3, 0);
		MACIO_OUT8(KL_GPIO_AIRPORT_4, 0);
		(व्योम)MACIO_IN8(KL_GPIO_AIRPORT_4);
		UNLOCK(flags);

		macio->flags &= ~MACIO_FLAG_AIRPORT_ON;
	पूर्ण
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_SMP
अटल दीर्घ
core99_reset_cpu(काष्ठा device_node *node, दीर्घ param, दीर्घ value)
अणु
	अचिन्हित पूर्णांक reset_io = 0;
	अचिन्हित दीर्घ flags;
	काष्ठा macio_chip *macio;
	काष्ठा device_node *np;
	स्थिर पूर्णांक dflt_reset_lines[] = अणु	KL_GPIO_RESET_CPU0,
						KL_GPIO_RESET_CPU1,
						KL_GPIO_RESET_CPU2,
						KL_GPIO_RESET_CPU3 पूर्ण;

	macio = &macio_chips[0];
	अगर (macio->type != macio_keylargo)
		वापस -ENODEV;

	क्रम_each_of_cpu_node(np) अणु
		स्थिर u32 *num = of_get_property(np, "reg", शून्य);
		स्थिर u32 *rst = of_get_property(np, "soft-reset", शून्य);
		अगर (num == शून्य || rst == शून्य)
			जारी;
		अगर (param == *num) अणु
			reset_io = *rst;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (np == शून्य || reset_io == 0)
		reset_io = dflt_reset_lines[param];

	LOCK(flags);
	MACIO_OUT8(reset_io, KEYLARGO_GPIO_OUTPUT_ENABLE);
	(व्योम)MACIO_IN8(reset_io);
	udelay(1);
	MACIO_OUT8(reset_io, 0);
	(व्योम)MACIO_IN8(reset_io);
	UNLOCK(flags);

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_SMP */

अटल दीर्घ
core99_usb_enable(काष्ठा device_node *node, दीर्घ param, दीर्घ value)
अणु
	काष्ठा macio_chip *macio;
	अचिन्हित दीर्घ flags;
	स्थिर अक्षर *prop;
	पूर्णांक number;
	u32 reg;

	macio = &macio_chips[0];
	अगर (macio->type != macio_keylargo && macio->type != macio_pangea &&
	    macio->type != macio_पूर्णांकrepid)
		वापस -ENODEV;

	prop = of_get_property(node, "AAPL,clock-id", शून्य);
	अगर (!prop)
		वापस -ENODEV;
	अगर (म_भेदन(prop, "usb0u048", 8) == 0)
		number = 0;
	अन्यथा अगर (म_भेदन(prop, "usb1u148", 8) == 0)
		number = 2;
	अन्यथा अगर (म_भेदन(prop, "usb2u248", 8) == 0)
		number = 4;
	अन्यथा
		वापस -ENODEV;

	/* Sorry क्रम the brute-क्रमce locking, but this is only used during
	 * sleep and the timing seem to be critical
	 */
	LOCK(flags);
	अगर (value) अणु
		/* Turn ON */
		अगर (number == 0) अणु
			MACIO_BIC(KEYLARGO_FCR0, (KL0_USB0_PAD_SUSPEND0 | KL0_USB0_PAD_SUSPEND1));
			(व्योम)MACIO_IN32(KEYLARGO_FCR0);
			UNLOCK(flags);
			mdelay(1);
			LOCK(flags);
			MACIO_BIS(KEYLARGO_FCR0, KL0_USB0_CELL_ENABLE);
		पूर्ण अन्यथा अगर (number == 2) अणु
			MACIO_BIC(KEYLARGO_FCR0, (KL0_USB1_PAD_SUSPEND0 | KL0_USB1_PAD_SUSPEND1));
			UNLOCK(flags);
			(व्योम)MACIO_IN32(KEYLARGO_FCR0);
			mdelay(1);
			LOCK(flags);
			MACIO_BIS(KEYLARGO_FCR0, KL0_USB1_CELL_ENABLE);
		पूर्ण अन्यथा अगर (number == 4) अणु
			MACIO_BIC(KEYLARGO_FCR1, (KL1_USB2_PAD_SUSPEND0 | KL1_USB2_PAD_SUSPEND1));
			UNLOCK(flags);
			(व्योम)MACIO_IN32(KEYLARGO_FCR1);
			mdelay(1);
			LOCK(flags);
			MACIO_BIS(KEYLARGO_FCR1, KL1_USB2_CELL_ENABLE);
		पूर्ण
		अगर (number < 4) अणु
			reg = MACIO_IN32(KEYLARGO_FCR4);
			reg &=	~(KL4_PORT_WAKEUP_ENABLE(number) | KL4_PORT_RESUME_WAKE_EN(number) |
				KL4_PORT_CONNECT_WAKE_EN(number) | KL4_PORT_DISCONNECT_WAKE_EN(number));
			reg &=	~(KL4_PORT_WAKEUP_ENABLE(number+1) | KL4_PORT_RESUME_WAKE_EN(number+1) |
				KL4_PORT_CONNECT_WAKE_EN(number+1) | KL4_PORT_DISCONNECT_WAKE_EN(number+1));
			MACIO_OUT32(KEYLARGO_FCR4, reg);
			(व्योम)MACIO_IN32(KEYLARGO_FCR4);
			udelay(10);
		पूर्ण अन्यथा अणु
			reg = MACIO_IN32(KEYLARGO_FCR3);
			reg &=	~(KL3_IT_PORT_WAKEUP_ENABLE(0) | KL3_IT_PORT_RESUME_WAKE_EN(0) |
				KL3_IT_PORT_CONNECT_WAKE_EN(0) | KL3_IT_PORT_DISCONNECT_WAKE_EN(0));
			reg &=	~(KL3_IT_PORT_WAKEUP_ENABLE(1) | KL3_IT_PORT_RESUME_WAKE_EN(1) |
				KL3_IT_PORT_CONNECT_WAKE_EN(1) | KL3_IT_PORT_DISCONNECT_WAKE_EN(1));
			MACIO_OUT32(KEYLARGO_FCR3, reg);
			(व्योम)MACIO_IN32(KEYLARGO_FCR3);
			udelay(10);
		पूर्ण
		अगर (macio->type == macio_पूर्णांकrepid) अणु
			/* रुको क्रम घड़ी stopped bits to clear */
			u32 test0 = 0, test1 = 0;
			u32 status0, status1;
			पूर्णांक समयout = 1000;

			UNLOCK(flags);
			चयन (number) अणु
			हाल 0:
				test0 = UNI_N_CLOCK_STOPPED_USB0;
				test1 = UNI_N_CLOCK_STOPPED_USB0PCI;
				अवरोध;
			हाल 2:
				test0 = UNI_N_CLOCK_STOPPED_USB1;
				test1 = UNI_N_CLOCK_STOPPED_USB1PCI;
				अवरोध;
			हाल 4:
				test0 = UNI_N_CLOCK_STOPPED_USB2;
				test1 = UNI_N_CLOCK_STOPPED_USB2PCI;
				अवरोध;
			पूर्ण
			करो अणु
				अगर (--समयout <= 0) अणु
					prपूर्णांकk(KERN_ERR "core99_usb_enable: "
					       "Timeout waiting for clocks\n");
					अवरोध;
				पूर्ण
				mdelay(1);
				status0 = UN_IN(UNI_N_CLOCK_STOP_STATUS0);
				status1 = UN_IN(UNI_N_CLOCK_STOP_STATUS1);
			पूर्ण जबतक ((status0 & test0) | (status1 & test1));
			LOCK(flags);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Turn OFF */
		अगर (number < 4) अणु
			reg = MACIO_IN32(KEYLARGO_FCR4);
			reg |=	KL4_PORT_WAKEUP_ENABLE(number) | KL4_PORT_RESUME_WAKE_EN(number) |
				KL4_PORT_CONNECT_WAKE_EN(number) | KL4_PORT_DISCONNECT_WAKE_EN(number);
			reg |=	KL4_PORT_WAKEUP_ENABLE(number+1) | KL4_PORT_RESUME_WAKE_EN(number+1) |
				KL4_PORT_CONNECT_WAKE_EN(number+1) | KL4_PORT_DISCONNECT_WAKE_EN(number+1);
			MACIO_OUT32(KEYLARGO_FCR4, reg);
			(व्योम)MACIO_IN32(KEYLARGO_FCR4);
			udelay(1);
		पूर्ण अन्यथा अणु
			reg = MACIO_IN32(KEYLARGO_FCR3);
			reg |=	KL3_IT_PORT_WAKEUP_ENABLE(0) | KL3_IT_PORT_RESUME_WAKE_EN(0) |
				KL3_IT_PORT_CONNECT_WAKE_EN(0) | KL3_IT_PORT_DISCONNECT_WAKE_EN(0);
			reg |=	KL3_IT_PORT_WAKEUP_ENABLE(1) | KL3_IT_PORT_RESUME_WAKE_EN(1) |
				KL3_IT_PORT_CONNECT_WAKE_EN(1) | KL3_IT_PORT_DISCONNECT_WAKE_EN(1);
			MACIO_OUT32(KEYLARGO_FCR3, reg);
			(व्योम)MACIO_IN32(KEYLARGO_FCR3);
			udelay(1);
		पूर्ण
		अगर (number == 0) अणु
			अगर (macio->type != macio_पूर्णांकrepid)
				MACIO_BIC(KEYLARGO_FCR0, KL0_USB0_CELL_ENABLE);
			(व्योम)MACIO_IN32(KEYLARGO_FCR0);
			udelay(1);
			MACIO_BIS(KEYLARGO_FCR0, (KL0_USB0_PAD_SUSPEND0 | KL0_USB0_PAD_SUSPEND1));
			(व्योम)MACIO_IN32(KEYLARGO_FCR0);
		पूर्ण अन्यथा अगर (number == 2) अणु
			अगर (macio->type != macio_पूर्णांकrepid)
				MACIO_BIC(KEYLARGO_FCR0, KL0_USB1_CELL_ENABLE);
			(व्योम)MACIO_IN32(KEYLARGO_FCR0);
			udelay(1);
			MACIO_BIS(KEYLARGO_FCR0, (KL0_USB1_PAD_SUSPEND0 | KL0_USB1_PAD_SUSPEND1));
			(व्योम)MACIO_IN32(KEYLARGO_FCR0);
		पूर्ण अन्यथा अगर (number == 4) अणु
			udelay(1);
			MACIO_BIS(KEYLARGO_FCR1, (KL1_USB2_PAD_SUSPEND0 | KL1_USB2_PAD_SUSPEND1));
			(व्योम)MACIO_IN32(KEYLARGO_FCR1);
		पूर्ण
		udelay(1);
	पूर्ण
	UNLOCK(flags);

	वापस 0;
पूर्ण

अटल दीर्घ
core99_firewire_enable(काष्ठा device_node *node, दीर्घ param, दीर्घ value)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा macio_chip *macio;

	macio = &macio_chips[0];
	अगर (macio->type != macio_keylargo && macio->type != macio_pangea &&
	    macio->type != macio_पूर्णांकrepid)
		वापस -ENODEV;
	अगर (!(macio->flags & MACIO_FLAG_FW_SUPPORTED))
		वापस -ENODEV;

	LOCK(flags);
	अगर (value) अणु
		UN_BIS(UNI_N_CLOCK_CNTL, UNI_N_CLOCK_CNTL_FW);
		(व्योम)UN_IN(UNI_N_CLOCK_CNTL);
	पूर्ण अन्यथा अणु
		UN_BIC(UNI_N_CLOCK_CNTL, UNI_N_CLOCK_CNTL_FW);
		(व्योम)UN_IN(UNI_N_CLOCK_CNTL);
	पूर्ण
	UNLOCK(flags);
	mdelay(1);

	वापस 0;
पूर्ण

अटल दीर्घ
core99_firewire_cable_घातer(काष्ठा device_node *node, दीर्घ param, दीर्घ value)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा macio_chip *macio;

	/* Trick: we allow शून्य node */
	अगर ((pmac_mb.board_flags & PMAC_MB_HAS_FW_POWER) == 0)
		वापस -ENODEV;
	macio = &macio_chips[0];
	अगर (macio->type != macio_keylargo && macio->type != macio_pangea &&
	    macio->type != macio_पूर्णांकrepid)
		वापस -ENODEV;
	अगर (!(macio->flags & MACIO_FLAG_FW_SUPPORTED))
		वापस -ENODEV;

	LOCK(flags);
	अगर (value) अणु
		MACIO_OUT8(KL_GPIO_FW_CABLE_POWER , 0);
		MACIO_IN8(KL_GPIO_FW_CABLE_POWER);
		udelay(10);
	पूर्ण अन्यथा अणु
		MACIO_OUT8(KL_GPIO_FW_CABLE_POWER , 4);
		MACIO_IN8(KL_GPIO_FW_CABLE_POWER); udelay(10);
	पूर्ण
	UNLOCK(flags);
	mdelay(1);

	वापस 0;
पूर्ण

अटल दीर्घ
पूर्णांकrepid_aack_delay_enable(काष्ठा device_node *node, दीर्घ param, दीर्घ value)
अणु
	अचिन्हित दीर्घ flags;

	अगर (uninorth_rev < 0xd2)
		वापस -ENODEV;

	LOCK(flags);
	अगर (param)
		UN_BIS(UNI_N_AACK_DELAY, UNI_N_AACK_DELAY_ENABLE);
	अन्यथा
		UN_BIC(UNI_N_AACK_DELAY, UNI_N_AACK_DELAY_ENABLE);
	UNLOCK(flags);

	वापस 0;
पूर्ण


#पूर्ण_अगर /* CONFIG_PPC64 */

अटल दीर्घ
core99_पढ़ो_gpio(काष्ठा device_node *node, दीर्घ param, दीर्घ value)
अणु
	काष्ठा macio_chip *macio = &macio_chips[0];

	वापस MACIO_IN8(param);
पूर्ण


अटल दीर्घ
core99_ग_लिखो_gpio(काष्ठा device_node *node, दीर्घ param, दीर्घ value)
अणु
	काष्ठा macio_chip *macio = &macio_chips[0];

	MACIO_OUT8(param, (u8)(value & 0xff));
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PPC64
अटल दीर्घ g5_gmac_enable(काष्ठा device_node *node, दीर्घ param, दीर्घ value)
अणु
	काष्ठा macio_chip *macio = &macio_chips[0];
	अचिन्हित दीर्घ flags;

	अगर (node == शून्य)
		वापस -ENODEV;

	LOCK(flags);
	अगर (value) अणु
		MACIO_BIS(KEYLARGO_FCR1, K2_FCR1_GMAC_CLK_ENABLE);
		mb();
		k2_skiplist[0] = शून्य;
	पूर्ण अन्यथा अणु
		k2_skiplist[0] = node;
		mb();
		MACIO_BIC(KEYLARGO_FCR1, K2_FCR1_GMAC_CLK_ENABLE);
	पूर्ण
	
	UNLOCK(flags);
	mdelay(1);

	वापस 0;
पूर्ण

अटल दीर्घ g5_fw_enable(काष्ठा device_node *node, दीर्घ param, दीर्घ value)
अणु
	काष्ठा macio_chip *macio = &macio_chips[0];
	अचिन्हित दीर्घ flags;

	अगर (node == शून्य)
		वापस -ENODEV;

	LOCK(flags);
	अगर (value) अणु
		MACIO_BIS(KEYLARGO_FCR1, K2_FCR1_FW_CLK_ENABLE);
		mb();
		k2_skiplist[1] = शून्य;
	पूर्ण अन्यथा अणु
		k2_skiplist[1] = node;
		mb();
		MACIO_BIC(KEYLARGO_FCR1, K2_FCR1_FW_CLK_ENABLE);
	पूर्ण
	
	UNLOCK(flags);
	mdelay(1);

	वापस 0;
पूर्ण

अटल दीर्घ g5_mpic_enable(काष्ठा device_node *node, दीर्घ param, दीर्घ value)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा device_node *parent = of_get_parent(node);
	पूर्णांक is_u3;

	अगर (parent == शून्य)
		वापस 0;
	is_u3 = of_node_name_eq(parent, "u3") || of_node_name_eq(parent, "u4");
	of_node_put(parent);
	अगर (!is_u3)
		वापस 0;

	LOCK(flags);
	UN_BIS(U3_TOGGLE_REG, U3_MPIC_RESET | U3_MPIC_OUTPUT_ENABLE);
	UNLOCK(flags);

	वापस 0;
पूर्ण

अटल दीर्घ g5_eth_phy_reset(काष्ठा device_node *node, दीर्घ param, दीर्घ value)
अणु
	काष्ठा macio_chip *macio = &macio_chips[0];
	काष्ठा device_node *phy;
	पूर्णांक need_reset;

	/*
	 * We must not reset the combo PHYs, only the BCM5221 found in
	 * the iMac G5.
	 */
	phy = of_get_next_child(node, शून्य);
	अगर (!phy)
		वापस -ENODEV;
	need_reset = of_device_is_compatible(phy, "B5221");
	of_node_put(phy);
	अगर (!need_reset)
		वापस 0;

	/* PHY reset is GPIO 29, not in device-tree unक्रमtunately */
	MACIO_OUT8(K2_GPIO_EXTINT_0 + 29,
		   KEYLARGO_GPIO_OUTPUT_ENABLE | KEYLARGO_GPIO_OUTOUT_DATA);
	/* Thankfully, this is now always called at a समय when we can
	 * schedule by sungem.
	 */
	msleep(10);
	MACIO_OUT8(K2_GPIO_EXTINT_0 + 29, 0);

	वापस 0;
पूर्ण

अटल दीर्घ g5_i2s_enable(काष्ठा device_node *node, दीर्घ param, दीर्घ value)
अणु
	/* Very crude implementation क्रम now */
	काष्ठा macio_chip *macio = &macio_chips[0];
	अचिन्हित दीर्घ flags;
	पूर्णांक cell;
	u32 fcrs[3][3] = अणु
		अणु 0,
		  K2_FCR1_I2S0_CELL_ENABLE |
		  K2_FCR1_I2S0_CLK_ENABLE_BIT | K2_FCR1_I2S0_ENABLE,
		  KL3_I2S0_CLK18_ENABLE
		पूर्ण,
		अणु KL0_SCC_A_INTF_ENABLE,
		  K2_FCR1_I2S1_CELL_ENABLE |
		  K2_FCR1_I2S1_CLK_ENABLE_BIT | K2_FCR1_I2S1_ENABLE,
		  KL3_I2S1_CLK18_ENABLE
		पूर्ण,
		अणु KL0_SCC_B_INTF_ENABLE,
		  SH_FCR1_I2S2_CELL_ENABLE |
		  SH_FCR1_I2S2_CLK_ENABLE_BIT | SH_FCR1_I2S2_ENABLE,
		  SH_FCR3_I2S2_CLK18_ENABLE
		पूर्ण,
	पूर्ण;

	अगर (macio->type != macio_keylargo2 && macio->type != macio_shasta)
		वापस -ENODEV;
	अगर (म_भेदन(node->name, "i2s-", 4))
		वापस -ENODEV;
	cell = node->name[4] - 'a';
	चयन(cell) अणु
	हाल 0:
	हाल 1:
		अवरोध;
	हाल 2:
		अगर (macio->type == macio_shasta)
			अवरोध;
		fallthrough;
	शेष:
		वापस -ENODEV;
	पूर्ण

	LOCK(flags);
	अगर (value) अणु
		MACIO_BIC(KEYLARGO_FCR0, fcrs[cell][0]);
		MACIO_BIS(KEYLARGO_FCR1, fcrs[cell][1]);
		MACIO_BIS(KEYLARGO_FCR3, fcrs[cell][2]);
	पूर्ण अन्यथा अणु
		MACIO_BIC(KEYLARGO_FCR3, fcrs[cell][2]);
		MACIO_BIC(KEYLARGO_FCR1, fcrs[cell][1]);
		MACIO_BIS(KEYLARGO_FCR0, fcrs[cell][0]);
	पूर्ण
	udelay(10);
	UNLOCK(flags);

	वापस 0;
पूर्ण


#अगर_घोषित CONFIG_SMP
अटल दीर्घ g5_reset_cpu(काष्ठा device_node *node, दीर्घ param, दीर्घ value)
अणु
	अचिन्हित पूर्णांक reset_io = 0;
	अचिन्हित दीर्घ flags;
	काष्ठा macio_chip *macio;
	काष्ठा device_node *np;

	macio = &macio_chips[0];
	अगर (macio->type != macio_keylargo2 && macio->type != macio_shasta)
		वापस -ENODEV;

	क्रम_each_of_cpu_node(np) अणु
		स्थिर u32 *num = of_get_property(np, "reg", शून्य);
		स्थिर u32 *rst = of_get_property(np, "soft-reset", शून्य);
		अगर (num == शून्य || rst == शून्य)
			जारी;
		अगर (param == *num) अणु
			reset_io = *rst;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (np == शून्य || reset_io == 0)
		वापस -ENODEV;

	LOCK(flags);
	MACIO_OUT8(reset_io, KEYLARGO_GPIO_OUTPUT_ENABLE);
	(व्योम)MACIO_IN8(reset_io);
	udelay(1);
	MACIO_OUT8(reset_io, 0);
	(व्योम)MACIO_IN8(reset_io);
	UNLOCK(flags);

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_SMP */

/*
 * This can be called from pmac_smp so isn't अटल
 *
 * This takes the second CPU off the bus on dual CPU machines
 * running UP
 */
व्योम g5_phy_disable_cpu1(व्योम)
अणु
	अगर (uninorth_maj == 3)
		UN_OUT(U3_API_PHY_CONFIG_1, 0);
पूर्ण
#पूर्ण_अगर /* CONFIG_PPC64 */

#अगर_अघोषित CONFIG_PPC64


#अगर_घोषित CONFIG_PM
अटल u32 save_gpio_levels[2];
अटल u8 save_gpio_extपूर्णांक[KEYLARGO_GPIO_EXTINT_CNT];
अटल u8 save_gpio_normal[KEYLARGO_GPIO_CNT];
अटल u32 save_unin_घड़ी_ctl;

अटल व्योम keylargo_shutकरोwn(काष्ठा macio_chip *macio, पूर्णांक sleep_mode)
अणु
	u32 temp;

	अगर (sleep_mode) अणु
		mdelay(1);
		MACIO_BIS(KEYLARGO_FCR0, KL0_USB_REF_SUSPEND);
		(व्योम)MACIO_IN32(KEYLARGO_FCR0);
		mdelay(1);
	पूर्ण

	MACIO_BIC(KEYLARGO_FCR0,KL0_SCCA_ENABLE | KL0_SCCB_ENABLE |
				KL0_SCC_CELL_ENABLE |
				KL0_IRDA_ENABLE | KL0_IRDA_CLK32_ENABLE |
				KL0_IRDA_CLK19_ENABLE);

	MACIO_BIC(KEYLARGO_MBCR, KL_MBCR_MB0_DEV_MASK);
	MACIO_BIS(KEYLARGO_MBCR, KL_MBCR_MB0_IDE_ENABLE);

	MACIO_BIC(KEYLARGO_FCR1,
		KL1_AUDIO_SEL_22MCLK | KL1_AUDIO_CLK_ENABLE_BIT |
		KL1_AUDIO_CLK_OUT_ENABLE | KL1_AUDIO_CELL_ENABLE |
		KL1_I2S0_CELL_ENABLE | KL1_I2S0_CLK_ENABLE_BIT |
		KL1_I2S0_ENABLE | KL1_I2S1_CELL_ENABLE |
		KL1_I2S1_CLK_ENABLE_BIT | KL1_I2S1_ENABLE |
		KL1_EIDE0_ENABLE | KL1_EIDE0_RESET_N |
		KL1_EIDE1_ENABLE | KL1_EIDE1_RESET_N |
		KL1_UIDE_ENABLE);

	MACIO_BIS(KEYLARGO_FCR2, KL2_ALT_DATA_OUT);
	MACIO_BIC(KEYLARGO_FCR2, KL2_IOBUS_ENABLE);

	temp = MACIO_IN32(KEYLARGO_FCR3);
	अगर (macio->rev >= 2) अणु
		temp |= KL3_SHUTDOWN_PLL2X;
		अगर (sleep_mode)
			temp |= KL3_SHUTDOWN_PLL_TOTAL;
	पूर्ण

	temp |= KL3_SHUTDOWN_PLLKW6 | KL3_SHUTDOWN_PLLKW4 |
		KL3_SHUTDOWN_PLLKW35;
	अगर (sleep_mode)
		temp |= KL3_SHUTDOWN_PLLKW12;
	temp &= ~(KL3_CLK66_ENABLE | KL3_CLK49_ENABLE | KL3_CLK45_ENABLE
		| KL3_CLK31_ENABLE | KL3_I2S1_CLK18_ENABLE | KL3_I2S0_CLK18_ENABLE);
	अगर (sleep_mode)
		temp &= ~(KL3_TIMER_CLK18_ENABLE | KL3_VIA_CLK16_ENABLE);
	MACIO_OUT32(KEYLARGO_FCR3, temp);

	/* Flush posted ग_लिखोs & रुको a bit */
	(व्योम)MACIO_IN32(KEYLARGO_FCR0); mdelay(1);
पूर्ण

अटल व्योम pangea_shutकरोwn(काष्ठा macio_chip *macio, पूर्णांक sleep_mode)
अणु
	u32 temp;

	MACIO_BIC(KEYLARGO_FCR0,KL0_SCCA_ENABLE | KL0_SCCB_ENABLE |
				KL0_SCC_CELL_ENABLE |
				KL0_USB0_CELL_ENABLE | KL0_USB1_CELL_ENABLE);

	MACIO_BIC(KEYLARGO_FCR1,
		KL1_AUDIO_SEL_22MCLK | KL1_AUDIO_CLK_ENABLE_BIT |
		KL1_AUDIO_CLK_OUT_ENABLE | KL1_AUDIO_CELL_ENABLE |
		KL1_I2S0_CELL_ENABLE | KL1_I2S0_CLK_ENABLE_BIT |
		KL1_I2S0_ENABLE | KL1_I2S1_CELL_ENABLE |
		KL1_I2S1_CLK_ENABLE_BIT | KL1_I2S1_ENABLE |
		KL1_UIDE_ENABLE);
	अगर (pmac_mb.board_flags & PMAC_MB_MOBILE)
		MACIO_BIC(KEYLARGO_FCR1, KL1_UIDE_RESET_N);

	MACIO_BIS(KEYLARGO_FCR2, KL2_ALT_DATA_OUT);

	temp = MACIO_IN32(KEYLARGO_FCR3);
	temp |= KL3_SHUTDOWN_PLLKW6 | KL3_SHUTDOWN_PLLKW4 |
		KL3_SHUTDOWN_PLLKW35;
	temp &= ~(KL3_CLK49_ENABLE | KL3_CLK45_ENABLE | KL3_CLK31_ENABLE
		| KL3_I2S0_CLK18_ENABLE | KL3_I2S1_CLK18_ENABLE);
	अगर (sleep_mode)
		temp &= ~(KL3_VIA_CLK16_ENABLE | KL3_TIMER_CLK18_ENABLE);
	MACIO_OUT32(KEYLARGO_FCR3, temp);

	/* Flush posted ग_लिखोs & रुको a bit */
	(व्योम)MACIO_IN32(KEYLARGO_FCR0); mdelay(1);
पूर्ण

अटल व्योम पूर्णांकrepid_shutकरोwn(काष्ठा macio_chip *macio, पूर्णांक sleep_mode)
अणु
	u32 temp;

	MACIO_BIC(KEYLARGO_FCR0,KL0_SCCA_ENABLE | KL0_SCCB_ENABLE |
		  KL0_SCC_CELL_ENABLE);

	MACIO_BIC(KEYLARGO_FCR1,
		KL1_I2S0_CELL_ENABLE | KL1_I2S0_CLK_ENABLE_BIT |
		KL1_I2S0_ENABLE | KL1_I2S1_CELL_ENABLE |
		KL1_I2S1_CLK_ENABLE_BIT | KL1_I2S1_ENABLE |
		KL1_EIDE0_ENABLE);
	अगर (pmac_mb.board_flags & PMAC_MB_MOBILE)
		MACIO_BIC(KEYLARGO_FCR1, KL1_UIDE_RESET_N);

	temp = MACIO_IN32(KEYLARGO_FCR3);
	temp &= ~(KL3_CLK49_ENABLE | KL3_CLK45_ENABLE |
		  KL3_I2S1_CLK18_ENABLE | KL3_I2S0_CLK18_ENABLE);
	अगर (sleep_mode)
		temp &= ~(KL3_TIMER_CLK18_ENABLE | KL3_IT_VIA_CLK32_ENABLE);
	MACIO_OUT32(KEYLARGO_FCR3, temp);

	/* Flush posted ग_लिखोs & रुको a bit */
	(व्योम)MACIO_IN32(KEYLARGO_FCR0);
	mdelay(10);
पूर्ण


अटल पूर्णांक
core99_sleep(व्योम)
अणु
	काष्ठा macio_chip *macio;
	पूर्णांक i;

	macio = &macio_chips[0];
	अगर (macio->type != macio_keylargo && macio->type != macio_pangea &&
	    macio->type != macio_पूर्णांकrepid)
		वापस -ENODEV;

	/* We घातer off the wireless slot in हाल it was not करोne
	 * by the driver. We करोn't घातer it on स्वतःmatically however
	 */
	अगर (macio->flags & MACIO_FLAG_AIRPORT_ON)
		core99_airport_enable(macio->of_node, 0, 0);

	/* We घातer off the FW cable. Should be करोne by the driver... */
	अगर (macio->flags & MACIO_FLAG_FW_SUPPORTED) अणु
		core99_firewire_enable(शून्य, 0, 0);
		core99_firewire_cable_घातer(शून्य, 0, 0);
	पूर्ण

	/* We make sure पूर्णांक. modem is off (in हाल driver lost it) */
	अगर (macio->type == macio_keylargo)
		core99_modem_enable(macio->of_node, 0, 0);
	अन्यथा
		pangea_modem_enable(macio->of_node, 0, 0);

	/* We make sure the sound is off as well */
	core99_sound_chip_enable(macio->of_node, 0, 0);

	/*
	 * Save various bits of KeyLargo
	 */

	/* Save the state of the various GPIOs */
	save_gpio_levels[0] = MACIO_IN32(KEYLARGO_GPIO_LEVELS0);
	save_gpio_levels[1] = MACIO_IN32(KEYLARGO_GPIO_LEVELS1);
	क्रम (i=0; i<KEYLARGO_GPIO_EXTINT_CNT; i++)
		save_gpio_extपूर्णांक[i] = MACIO_IN8(KEYLARGO_GPIO_EXTINT_0+i);
	क्रम (i=0; i<KEYLARGO_GPIO_CNT; i++)
		save_gpio_normal[i] = MACIO_IN8(KEYLARGO_GPIO_0+i);

	/* Save the FCRs */
	अगर (macio->type == macio_keylargo)
		save_mbcr = MACIO_IN32(KEYLARGO_MBCR);
	save_fcr[0] = MACIO_IN32(KEYLARGO_FCR0);
	save_fcr[1] = MACIO_IN32(KEYLARGO_FCR1);
	save_fcr[2] = MACIO_IN32(KEYLARGO_FCR2);
	save_fcr[3] = MACIO_IN32(KEYLARGO_FCR3);
	save_fcr[4] = MACIO_IN32(KEYLARGO_FCR4);
	अगर (macio->type == macio_pangea || macio->type == macio_पूर्णांकrepid)
		save_fcr[5] = MACIO_IN32(KEYLARGO_FCR5);

	/* Save state & config of DBDMA channels */
	dbdma_save(macio, save_dbdma);

	/*
	 * Turn off as much as we can
	 */
	अगर (macio->type == macio_pangea)
		pangea_shutकरोwn(macio, 1);
	अन्यथा अगर (macio->type == macio_पूर्णांकrepid)
		पूर्णांकrepid_shutकरोwn(macio, 1);
	अन्यथा अगर (macio->type == macio_keylargo)
		keylargo_shutकरोwn(macio, 1);

	/*
	 * Put the host bridge to sleep
	 */

	save_unin_घड़ी_ctl = UN_IN(UNI_N_CLOCK_CNTL);
	/* Note: करो not चयन GMAC off, driver करोes it when necessary, WOL must keep it
	 * enabled !
	 */
	UN_OUT(UNI_N_CLOCK_CNTL, save_unin_घड़ी_ctl &
	       ~(/*UNI_N_CLOCK_CNTL_GMAC|*/UNI_N_CLOCK_CNTL_FW/*|UNI_N_CLOCK_CNTL_PCI*/));
	udelay(100);
	UN_OUT(UNI_N_HWINIT_STATE, UNI_N_HWINIT_STATE_SLEEPING);
	UN_OUT(UNI_N_POWER_MGT, UNI_N_POWER_MGT_SLEEP);
	mdelay(10);

	/*
	 * FIXME: A bit of black magic with OpenPIC (करोn't ask me why)
	 */
	अगर (pmac_mb.model_id == PMAC_TYPE_SAWTOOTH) अणु
		MACIO_BIS(0x506e0, 0x00400000);
		MACIO_BIS(0x506e0, 0x80000000);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
core99_wake_up(व्योम)
अणु
	काष्ठा macio_chip *macio;
	पूर्णांक i;

	macio = &macio_chips[0];
	अगर (macio->type != macio_keylargo && macio->type != macio_pangea &&
	    macio->type != macio_पूर्णांकrepid)
		वापस -ENODEV;

	/*
	 * Wakeup the host bridge
	 */
	UN_OUT(UNI_N_POWER_MGT, UNI_N_POWER_MGT_NORMAL);
	udelay(10);
	UN_OUT(UNI_N_HWINIT_STATE, UNI_N_HWINIT_STATE_RUNNING);
	udelay(10);

	/*
	 * Restore KeyLargo
	 */

	अगर (macio->type == macio_keylargo) अणु
		MACIO_OUT32(KEYLARGO_MBCR, save_mbcr);
		(व्योम)MACIO_IN32(KEYLARGO_MBCR); udelay(10);
	पूर्ण
	MACIO_OUT32(KEYLARGO_FCR0, save_fcr[0]);
	(व्योम)MACIO_IN32(KEYLARGO_FCR0); udelay(10);
	MACIO_OUT32(KEYLARGO_FCR1, save_fcr[1]);
	(व्योम)MACIO_IN32(KEYLARGO_FCR1); udelay(10);
	MACIO_OUT32(KEYLARGO_FCR2, save_fcr[2]);
	(व्योम)MACIO_IN32(KEYLARGO_FCR2); udelay(10);
	MACIO_OUT32(KEYLARGO_FCR3, save_fcr[3]);
	(व्योम)MACIO_IN32(KEYLARGO_FCR3); udelay(10);
	MACIO_OUT32(KEYLARGO_FCR4, save_fcr[4]);
	(व्योम)MACIO_IN32(KEYLARGO_FCR4); udelay(10);
	अगर (macio->type == macio_pangea || macio->type == macio_पूर्णांकrepid) अणु
		MACIO_OUT32(KEYLARGO_FCR5, save_fcr[5]);
		(व्योम)MACIO_IN32(KEYLARGO_FCR5); udelay(10);
	पूर्ण

	dbdma_restore(macio, save_dbdma);

	MACIO_OUT32(KEYLARGO_GPIO_LEVELS0, save_gpio_levels[0]);
	MACIO_OUT32(KEYLARGO_GPIO_LEVELS1, save_gpio_levels[1]);
	क्रम (i=0; i<KEYLARGO_GPIO_EXTINT_CNT; i++)
		MACIO_OUT8(KEYLARGO_GPIO_EXTINT_0+i, save_gpio_extपूर्णांक[i]);
	क्रम (i=0; i<KEYLARGO_GPIO_CNT; i++)
		MACIO_OUT8(KEYLARGO_GPIO_0+i, save_gpio_normal[i]);

	/* FIXME more black magic with OpenPIC ... */
	अगर (pmac_mb.model_id == PMAC_TYPE_SAWTOOTH) अणु
		MACIO_BIC(0x506e0, 0x00400000);
		MACIO_BIC(0x506e0, 0x80000000);
	पूर्ण

	UN_OUT(UNI_N_CLOCK_CNTL, save_unin_घड़ी_ctl);
	udelay(100);

	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_PM */

अटल दीर्घ
core99_sleep_state(काष्ठा device_node *node, दीर्घ param, दीर्घ value)
अणु
	/* Param == 1 means to enter the "fake sleep" mode that is
	 * used क्रम CPU speed चयन
	 */
	अगर (param == 1) अणु
		अगर (value == 1) अणु
			UN_OUT(UNI_N_HWINIT_STATE, UNI_N_HWINIT_STATE_SLEEPING);
			UN_OUT(UNI_N_POWER_MGT, UNI_N_POWER_MGT_IDLE2);
		पूर्ण अन्यथा अणु
			UN_OUT(UNI_N_POWER_MGT, UNI_N_POWER_MGT_NORMAL);
			udelay(10);
			UN_OUT(UNI_N_HWINIT_STATE, UNI_N_HWINIT_STATE_RUNNING);
			udelay(10);
		पूर्ण
		वापस 0;
	पूर्ण
	अगर ((pmac_mb.board_flags & PMAC_MB_CAN_SLEEP) == 0)
		वापस -EPERM;

#अगर_घोषित CONFIG_PM
	अगर (value == 1)
		वापस core99_sleep();
	अन्यथा अगर (value == 0)
		वापस core99_wake_up();

#पूर्ण_अगर /* CONFIG_PM */
	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_PPC64 */

अटल दीर्घ
generic_dev_can_wake(काष्ठा device_node *node, दीर्घ param, दीर्घ value)
अणु
	/* Toकरो: eventually check we are really dealing with on-board
	 * video device ...
	 */

	अगर (pmac_mb.board_flags & PMAC_MB_MAY_SLEEP)
		pmac_mb.board_flags |= PMAC_MB_CAN_SLEEP;
	वापस 0;
पूर्ण

अटल दीर्घ generic_get_mb_info(काष्ठा device_node *node, दीर्घ param, दीर्घ value)
अणु
	चयन(param) अणु
		हाल PMAC_MB_INFO_MODEL:
			वापस pmac_mb.model_id;
		हाल PMAC_MB_INFO_FLAGS:
			वापस pmac_mb.board_flags;
		हाल PMAC_MB_INFO_NAME:
			/* hack hack hack... but should work */
			*((स्थिर अक्षर **)value) = pmac_mb.model_name;
			वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण


/*
 * Table definitions
 */

/* Used on any machine
 */
अटल काष्ठा feature_table_entry any_features[] = अणु
	अणु PMAC_FTR_GET_MB_INFO,		generic_get_mb_info पूर्ण,
	अणु PMAC_FTR_DEVICE_CAN_WAKE,	generic_dev_can_wake पूर्ण,
	अणु 0, शून्य पूर्ण
पूर्ण;

#अगर_अघोषित CONFIG_PPC64

/* OHare based motherboards. Currently, we only use these on the
 * 2400,3400 and 3500 series घातerbooks. Some older desktops seem
 * to have issues with turning on/off those asic cells
 */
अटल काष्ठा feature_table_entry ohare_features[] = अणु
	अणु PMAC_FTR_SCC_ENABLE,		ohare_htw_scc_enable पूर्ण,
	अणु PMAC_FTR_SWIM3_ENABLE,	ohare_floppy_enable पूर्ण,
	अणु PMAC_FTR_MESH_ENABLE,		ohare_mesh_enable पूर्ण,
	अणु PMAC_FTR_IDE_ENABLE,		ohare_ide_enableपूर्ण,
	अणु PMAC_FTR_IDE_RESET,		ohare_ide_resetपूर्ण,
	अणु PMAC_FTR_SLEEP_STATE,		ohare_sleep_state पूर्ण,
	अणु 0, शून्य पूर्ण
पूर्ण;

/* Heathrow desktop machines (Beige G3).
 * Separated as some features couldn't be properly tested
 * and the serial port control bits appear to confuse it.
 */
अटल काष्ठा feature_table_entry heathrow_desktop_features[] = अणु
	अणु PMAC_FTR_SWIM3_ENABLE,	heathrow_floppy_enable पूर्ण,
	अणु PMAC_FTR_MESH_ENABLE,		heathrow_mesh_enable पूर्ण,
	अणु PMAC_FTR_IDE_ENABLE,		heathrow_ide_enable पूर्ण,
	अणु PMAC_FTR_IDE_RESET,		heathrow_ide_reset पूर्ण,
	अणु PMAC_FTR_BMAC_ENABLE,		heathrow_bmac_enable पूर्ण,
	अणु 0, शून्य पूर्ण
पूर्ण;

/* Heathrow based laptop, that is the Wallstreet and मुख्यstreet
 * घातerbooks.
 */
अटल काष्ठा feature_table_entry heathrow_laptop_features[] = अणु
	अणु PMAC_FTR_SCC_ENABLE,		ohare_htw_scc_enable पूर्ण,
	अणु PMAC_FTR_MODEM_ENABLE,	heathrow_modem_enable पूर्ण,
	अणु PMAC_FTR_SWIM3_ENABLE,	heathrow_floppy_enable पूर्ण,
	अणु PMAC_FTR_MESH_ENABLE,		heathrow_mesh_enable पूर्ण,
	अणु PMAC_FTR_IDE_ENABLE,		heathrow_ide_enable पूर्ण,
	अणु PMAC_FTR_IDE_RESET,		heathrow_ide_reset पूर्ण,
	अणु PMAC_FTR_BMAC_ENABLE,		heathrow_bmac_enable पूर्ण,
	अणु PMAC_FTR_SOUND_CHIP_ENABLE,	heathrow_sound_enable पूर्ण,
	अणु PMAC_FTR_SLEEP_STATE,		heathrow_sleep_state पूर्ण,
	अणु 0, शून्य पूर्ण
पूर्ण;

/* Paddington based machines
 * The lombard (101) घातerbook, first iMac models, B&W G3 and Yikes G4.
 */
अटल काष्ठा feature_table_entry paddington_features[] = अणु
	अणु PMAC_FTR_SCC_ENABLE,		ohare_htw_scc_enable पूर्ण,
	अणु PMAC_FTR_MODEM_ENABLE,	heathrow_modem_enable पूर्ण,
	अणु PMAC_FTR_SWIM3_ENABLE,	heathrow_floppy_enable पूर्ण,
	अणु PMAC_FTR_MESH_ENABLE,		heathrow_mesh_enable पूर्ण,
	अणु PMAC_FTR_IDE_ENABLE,		heathrow_ide_enable पूर्ण,
	अणु PMAC_FTR_IDE_RESET,		heathrow_ide_reset पूर्ण,
	अणु PMAC_FTR_BMAC_ENABLE,		heathrow_bmac_enable पूर्ण,
	अणु PMAC_FTR_SOUND_CHIP_ENABLE,	heathrow_sound_enable पूर्ण,
	अणु PMAC_FTR_SLEEP_STATE,		heathrow_sleep_state पूर्ण,
	अणु 0, शून्य पूर्ण
पूर्ण;

/* Core99 & MacRISC 2 machines (all machines released since the
 * iBook (included), that is all AGP machines, except pangea
 * chipset. The pangea chipset is the "combo" UniNorth/KeyLargo
 * used on iBook2 & iMac "flow power".
 */
अटल काष्ठा feature_table_entry core99_features[] = अणु
	अणु PMAC_FTR_SCC_ENABLE,		core99_scc_enable पूर्ण,
	अणु PMAC_FTR_MODEM_ENABLE,	core99_modem_enable पूर्ण,
	अणु PMAC_FTR_IDE_ENABLE,		core99_ide_enable पूर्ण,
	अणु PMAC_FTR_IDE_RESET,		core99_ide_reset पूर्ण,
	अणु PMAC_FTR_GMAC_ENABLE,		core99_gmac_enable पूर्ण,
	अणु PMAC_FTR_GMAC_PHY_RESET,	core99_gmac_phy_reset पूर्ण,
	अणु PMAC_FTR_SOUND_CHIP_ENABLE,	core99_sound_chip_enable पूर्ण,
	अणु PMAC_FTR_AIRPORT_ENABLE,	core99_airport_enable पूर्ण,
	अणु PMAC_FTR_USB_ENABLE,		core99_usb_enable पूर्ण,
	अणु PMAC_FTR_1394_ENABLE,		core99_firewire_enable पूर्ण,
	अणु PMAC_FTR_1394_CABLE_POWER,	core99_firewire_cable_घातer पूर्ण,
#अगर_घोषित CONFIG_PM
	अणु PMAC_FTR_SLEEP_STATE,		core99_sleep_state पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_SMP
	अणु PMAC_FTR_RESET_CPU,		core99_reset_cpu पूर्ण,
#पूर्ण_अगर /* CONFIG_SMP */
	अणु PMAC_FTR_READ_GPIO,		core99_पढ़ो_gpio पूर्ण,
	अणु PMAC_FTR_WRITE_GPIO,		core99_ग_लिखो_gpio पूर्ण,
	अणु 0, शून्य पूर्ण
पूर्ण;

/* RackMac
 */
अटल काष्ठा feature_table_entry rackmac_features[] = अणु
	अणु PMAC_FTR_SCC_ENABLE,		core99_scc_enable पूर्ण,
	अणु PMAC_FTR_IDE_ENABLE,		core99_ide_enable पूर्ण,
	अणु PMAC_FTR_IDE_RESET,		core99_ide_reset पूर्ण,
	अणु PMAC_FTR_GMAC_ENABLE,		core99_gmac_enable पूर्ण,
	अणु PMAC_FTR_GMAC_PHY_RESET,	core99_gmac_phy_reset पूर्ण,
	अणु PMAC_FTR_USB_ENABLE,		core99_usb_enable पूर्ण,
	अणु PMAC_FTR_1394_ENABLE,		core99_firewire_enable पूर्ण,
	अणु PMAC_FTR_1394_CABLE_POWER,	core99_firewire_cable_घातer पूर्ण,
	अणु PMAC_FTR_SLEEP_STATE,		core99_sleep_state पूर्ण,
#अगर_घोषित CONFIG_SMP
	अणु PMAC_FTR_RESET_CPU,		core99_reset_cpu पूर्ण,
#पूर्ण_अगर /* CONFIG_SMP */
	अणु PMAC_FTR_READ_GPIO,		core99_पढ़ो_gpio पूर्ण,
	अणु PMAC_FTR_WRITE_GPIO,		core99_ग_लिखो_gpio पूर्ण,
	अणु 0, शून्य पूर्ण
पूर्ण;

/* Pangea features
 */
अटल काष्ठा feature_table_entry pangea_features[] = अणु
	अणु PMAC_FTR_SCC_ENABLE,		core99_scc_enable पूर्ण,
	अणु PMAC_FTR_MODEM_ENABLE,	pangea_modem_enable पूर्ण,
	अणु PMAC_FTR_IDE_ENABLE,		core99_ide_enable पूर्ण,
	अणु PMAC_FTR_IDE_RESET,		core99_ide_reset पूर्ण,
	अणु PMAC_FTR_GMAC_ENABLE,		core99_gmac_enable पूर्ण,
	अणु PMAC_FTR_GMAC_PHY_RESET,	core99_gmac_phy_reset पूर्ण,
	अणु PMAC_FTR_SOUND_CHIP_ENABLE,	core99_sound_chip_enable पूर्ण,
	अणु PMAC_FTR_AIRPORT_ENABLE,	core99_airport_enable पूर्ण,
	अणु PMAC_FTR_USB_ENABLE,		core99_usb_enable पूर्ण,
	अणु PMAC_FTR_1394_ENABLE,		core99_firewire_enable पूर्ण,
	अणु PMAC_FTR_1394_CABLE_POWER,	core99_firewire_cable_घातer पूर्ण,
	अणु PMAC_FTR_SLEEP_STATE,		core99_sleep_state पूर्ण,
	अणु PMAC_FTR_READ_GPIO,		core99_पढ़ो_gpio पूर्ण,
	अणु PMAC_FTR_WRITE_GPIO,		core99_ग_लिखो_gpio पूर्ण,
	अणु 0, शून्य पूर्ण
पूर्ण;

/* Intrepid features
 */
अटल काष्ठा feature_table_entry पूर्णांकrepid_features[] = अणु
	अणु PMAC_FTR_SCC_ENABLE,		core99_scc_enable पूर्ण,
	अणु PMAC_FTR_MODEM_ENABLE,	pangea_modem_enable पूर्ण,
	अणु PMAC_FTR_IDE_ENABLE,		core99_ide_enable पूर्ण,
	अणु PMAC_FTR_IDE_RESET,		core99_ide_reset पूर्ण,
	अणु PMAC_FTR_GMAC_ENABLE,		core99_gmac_enable पूर्ण,
	अणु PMAC_FTR_GMAC_PHY_RESET,	core99_gmac_phy_reset पूर्ण,
	अणु PMAC_FTR_SOUND_CHIP_ENABLE,	core99_sound_chip_enable पूर्ण,
	अणु PMAC_FTR_AIRPORT_ENABLE,	core99_airport_enable पूर्ण,
	अणु PMAC_FTR_USB_ENABLE,		core99_usb_enable पूर्ण,
	अणु PMAC_FTR_1394_ENABLE,		core99_firewire_enable पूर्ण,
	अणु PMAC_FTR_1394_CABLE_POWER,	core99_firewire_cable_घातer पूर्ण,
	अणु PMAC_FTR_SLEEP_STATE,		core99_sleep_state पूर्ण,
	अणु PMAC_FTR_READ_GPIO,		core99_पढ़ो_gpio पूर्ण,
	अणु PMAC_FTR_WRITE_GPIO,		core99_ग_लिखो_gpio पूर्ण,
	अणु PMAC_FTR_AACK_DELAY_ENABLE,	पूर्णांकrepid_aack_delay_enable पूर्ण,
	अणु 0, शून्य पूर्ण
पूर्ण;

#अन्यथा /* CONFIG_PPC64 */

/* G5 features
 */
अटल काष्ठा feature_table_entry g5_features[] = अणु
	अणु PMAC_FTR_GMAC_ENABLE,		g5_gmac_enable पूर्ण,
	अणु PMAC_FTR_1394_ENABLE,		g5_fw_enable पूर्ण,
	अणु PMAC_FTR_ENABLE_MPIC,		g5_mpic_enable पूर्ण,
	अणु PMAC_FTR_GMAC_PHY_RESET,	g5_eth_phy_reset पूर्ण,
	अणु PMAC_FTR_SOUND_CHIP_ENABLE,	g5_i2s_enable पूर्ण,
#अगर_घोषित CONFIG_SMP
	अणु PMAC_FTR_RESET_CPU,		g5_reset_cpu पूर्ण,
#पूर्ण_अगर /* CONFIG_SMP */
	अणु PMAC_FTR_READ_GPIO,		core99_पढ़ो_gpio पूर्ण,
	अणु PMAC_FTR_WRITE_GPIO,		core99_ग_लिखो_gpio पूर्ण,
	अणु 0, शून्य पूर्ण
पूर्ण;

#पूर्ण_अगर /* CONFIG_PPC64 */

अटल काष्ठा pmac_mb_def pmac_mb_defs[] = अणु
#अगर_अघोषित CONFIG_PPC64
	/*
	 * Desktops
	 */

	अणु	"AAPL,8500",			"PowerMac 8500/8600",
		PMAC_TYPE_PSURGE,		शून्य,
		0
	पूर्ण,
	अणु	"AAPL,9500",			"PowerMac 9500/9600",
		PMAC_TYPE_PSURGE,		शून्य,
		0
	पूर्ण,
	अणु	"AAPL,7200",			"PowerMac 7200",
		PMAC_TYPE_PSURGE,		शून्य,
		0
	पूर्ण,
	अणु	"AAPL,7300",			"PowerMac 7200/7300",
		PMAC_TYPE_PSURGE,		शून्य,
		0
	पूर्ण,
	अणु	"AAPL,7500",			"PowerMac 7500",
		PMAC_TYPE_PSURGE,		शून्य,
		0
	पूर्ण,
	अणु	"AAPL,ShinerESB",		"Apple Network Server",
		PMAC_TYPE_ANS,			शून्य,
		0
	पूर्ण,
	अणु	"AAPL,e407",			"Alchemy",
		PMAC_TYPE_ALCHEMY,		शून्य,
		0
	पूर्ण,
	अणु	"AAPL,e411",			"Gazelle",
		PMAC_TYPE_GAZELLE,		शून्य,
		0
	पूर्ण,
	अणु	"AAPL,Gossamer",		"PowerMac G3 (Gossamer)",
		PMAC_TYPE_GOSSAMER,		heathrow_desktop_features,
		0
	पूर्ण,
	अणु	"AAPL,PowerMac G3",		"PowerMac G3 (Silk)",
		PMAC_TYPE_SILK,			heathrow_desktop_features,
		0
	पूर्ण,
	अणु	"PowerMac1,1",			"Blue&White G3",
		PMAC_TYPE_YOSEMITE,		paddington_features,
		0
	पूर्ण,
	अणु	"PowerMac1,2",			"PowerMac G4 PCI Graphics",
		PMAC_TYPE_YIKES,		paddington_features,
		0
	पूर्ण,
	अणु	"PowerMac2,1",			"iMac FireWire",
		PMAC_TYPE_FW_IMAC,		core99_features,
		PMAC_MB_MAY_SLEEP | PMAC_MB_OLD_CORE99
	पूर्ण,
	अणु	"PowerMac2,2",			"iMac FireWire",
		PMAC_TYPE_FW_IMAC,		core99_features,
		PMAC_MB_MAY_SLEEP | PMAC_MB_OLD_CORE99
	पूर्ण,
	अणु	"PowerMac3,1",			"PowerMac G4 AGP Graphics",
		PMAC_TYPE_SAWTOOTH,		core99_features,
		PMAC_MB_OLD_CORE99
	पूर्ण,
	अणु	"PowerMac3,2",			"PowerMac G4 AGP Graphics",
		PMAC_TYPE_SAWTOOTH,		core99_features,
		PMAC_MB_MAY_SLEEP | PMAC_MB_OLD_CORE99
	पूर्ण,
	अणु	"PowerMac3,3",			"PowerMac G4 AGP Graphics",
		PMAC_TYPE_SAWTOOTH,		core99_features,
		PMAC_MB_MAY_SLEEP | PMAC_MB_OLD_CORE99
	पूर्ण,
	अणु	"PowerMac3,4",			"PowerMac G4 Silver",
		PMAC_TYPE_QUICKSILVER,		core99_features,
		PMAC_MB_MAY_SLEEP
	पूर्ण,
	अणु	"PowerMac3,5",			"PowerMac G4 Silver",
		PMAC_TYPE_QUICKSILVER,		core99_features,
		PMAC_MB_MAY_SLEEP
	पूर्ण,
	अणु	"PowerMac3,6",			"PowerMac G4 Windtunnel",
		PMAC_TYPE_WINDTUNNEL,		core99_features,
		PMAC_MB_MAY_SLEEP,
	पूर्ण,
	अणु	"PowerMac4,1",			"iMac \"Flower Power\"",
		PMAC_TYPE_PANGEA_IMAC,		pangea_features,
		PMAC_MB_MAY_SLEEP
	पूर्ण,
	अणु	"PowerMac4,2",			"Flat panel iMac",
		PMAC_TYPE_FLAT_PANEL_IMAC,	pangea_features,
		PMAC_MB_CAN_SLEEP
	पूर्ण,
	अणु	"PowerMac4,4",			"eMac",
		PMAC_TYPE_EMAC,			core99_features,
		PMAC_MB_MAY_SLEEP
	पूर्ण,
	अणु	"PowerMac5,1",			"PowerMac G4 Cube",
		PMAC_TYPE_CUBE,			core99_features,
		PMAC_MB_MAY_SLEEP | PMAC_MB_OLD_CORE99
	पूर्ण,
	अणु	"PowerMac6,1",			"Flat panel iMac",
		PMAC_TYPE_UNKNOWN_INTREPID,	पूर्णांकrepid_features,
		PMAC_MB_MAY_SLEEP,
	पूर्ण,
	अणु	"PowerMac6,3",			"Flat panel iMac",
		PMAC_TYPE_UNKNOWN_INTREPID,	पूर्णांकrepid_features,
		PMAC_MB_MAY_SLEEP,
	पूर्ण,
	अणु	"PowerMac6,4",			"eMac",
		PMAC_TYPE_UNKNOWN_INTREPID,	पूर्णांकrepid_features,
		PMAC_MB_MAY_SLEEP,
	पूर्ण,
	अणु	"PowerMac10,1",			"Mac mini",
		PMAC_TYPE_UNKNOWN_INTREPID,	पूर्णांकrepid_features,
		PMAC_MB_MAY_SLEEP,
	पूर्ण,
	अणु       "PowerMac10,2",                 "Mac mini (Late 2005)",
		PMAC_TYPE_UNKNOWN_INTREPID,     पूर्णांकrepid_features,
		PMAC_MB_MAY_SLEEP,
	पूर्ण,
 	अणु	"iMac,1",			"iMac (first generation)",
		PMAC_TYPE_ORIG_IMAC,		paddington_features,
		0
	पूर्ण,

	/*
	 * Xserve's
	 */

	अणु	"RackMac1,1",			"XServe",
		PMAC_TYPE_RACKMAC,		rackmac_features,
		0,
	पूर्ण,
	अणु	"RackMac1,2",			"XServe rev. 2",
		PMAC_TYPE_RACKMAC,		rackmac_features,
		0,
	पूर्ण,

	/*
	 * Laptops
	 */

	अणु	"AAPL,3400/2400",		"PowerBook 3400",
		PMAC_TYPE_HOOPER,		ohare_features,
		PMAC_MB_CAN_SLEEP | PMAC_MB_MOBILE
	पूर्ण,
	अणु	"AAPL,3500",			"PowerBook 3500",
		PMAC_TYPE_KANGA,		ohare_features,
		PMAC_MB_CAN_SLEEP | PMAC_MB_MOBILE
	पूर्ण,
	अणु	"AAPL,PowerBook1998",		"PowerBook Wallstreet",
		PMAC_TYPE_WALLSTREET,		heathrow_laptop_features,
		PMAC_MB_CAN_SLEEP | PMAC_MB_MOBILE
	पूर्ण,
	अणु	"PowerBook1,1",			"PowerBook 101 (Lombard)",
		PMAC_TYPE_101_PBOOK,		paddington_features,
		PMAC_MB_CAN_SLEEP | PMAC_MB_MOBILE
	पूर्ण,
	अणु	"PowerBook2,1",			"iBook (first generation)",
		PMAC_TYPE_ORIG_IBOOK,		core99_features,
		PMAC_MB_CAN_SLEEP | PMAC_MB_OLD_CORE99 | PMAC_MB_MOBILE
	पूर्ण,
	अणु	"PowerBook2,2",			"iBook FireWire",
		PMAC_TYPE_FW_IBOOK,		core99_features,
		PMAC_MB_MAY_SLEEP | PMAC_MB_HAS_FW_POWER |
		PMAC_MB_OLD_CORE99 | PMAC_MB_MOBILE
	पूर्ण,
	अणु	"PowerBook3,1",			"PowerBook Pismo",
		PMAC_TYPE_PISMO,		core99_features,
		PMAC_MB_MAY_SLEEP | PMAC_MB_HAS_FW_POWER |
		PMAC_MB_OLD_CORE99 | PMAC_MB_MOBILE
	पूर्ण,
	अणु	"PowerBook3,2",			"PowerBook Titanium",
		PMAC_TYPE_TITANIUM,		core99_features,
		PMAC_MB_MAY_SLEEP | PMAC_MB_HAS_FW_POWER | PMAC_MB_MOBILE
	पूर्ण,
	अणु	"PowerBook3,3",			"PowerBook Titanium II",
		PMAC_TYPE_TITANIUM2,		core99_features,
		PMAC_MB_MAY_SLEEP | PMAC_MB_HAS_FW_POWER | PMAC_MB_MOBILE
	पूर्ण,
	अणु	"PowerBook3,4",			"PowerBook Titanium III",
		PMAC_TYPE_TITANIUM3,		core99_features,
		PMAC_MB_MAY_SLEEP | PMAC_MB_HAS_FW_POWER | PMAC_MB_MOBILE
	पूर्ण,
	अणु	"PowerBook3,5",			"PowerBook Titanium IV",
		PMAC_TYPE_TITANIUM4,		core99_features,
		PMAC_MB_MAY_SLEEP | PMAC_MB_HAS_FW_POWER | PMAC_MB_MOBILE
	पूर्ण,
	अणु	"PowerBook4,1",			"iBook 2",
		PMAC_TYPE_IBOOK2,		pangea_features,
		PMAC_MB_MAY_SLEEP | PMAC_MB_HAS_FW_POWER | PMAC_MB_MOBILE
	पूर्ण,
	अणु	"PowerBook4,2",			"iBook 2",
		PMAC_TYPE_IBOOK2,		pangea_features,
		PMAC_MB_MAY_SLEEP | PMAC_MB_HAS_FW_POWER | PMAC_MB_MOBILE
	पूर्ण,
	अणु	"PowerBook4,3",			"iBook 2 rev. 2",
		PMAC_TYPE_IBOOK2,		pangea_features,
		PMAC_MB_MAY_SLEEP | PMAC_MB_HAS_FW_POWER | PMAC_MB_MOBILE
	पूर्ण,
	अणु	"PowerBook5,1",			"PowerBook G4 17\"",
		PMAC_TYPE_UNKNOWN_INTREPID,	पूर्णांकrepid_features,
		PMAC_MB_HAS_FW_POWER | PMAC_MB_MOBILE,
	पूर्ण,
	अणु	"PowerBook5,2",			"PowerBook G4 15\"",
		PMAC_TYPE_UNKNOWN_INTREPID,	पूर्णांकrepid_features,
		PMAC_MB_MAY_SLEEP | PMAC_MB_HAS_FW_POWER | PMAC_MB_MOBILE,
	पूर्ण,
	अणु	"PowerBook5,3",			"PowerBook G4 17\"",
		PMAC_TYPE_UNKNOWN_INTREPID,	पूर्णांकrepid_features,
		PMAC_MB_MAY_SLEEP | PMAC_MB_HAS_FW_POWER | PMAC_MB_MOBILE,
	पूर्ण,
	अणु	"PowerBook5,4",			"PowerBook G4 15\"",
		PMAC_TYPE_UNKNOWN_INTREPID,	पूर्णांकrepid_features,
		PMAC_MB_MAY_SLEEP | PMAC_MB_HAS_FW_POWER | PMAC_MB_MOBILE,
	पूर्ण,
	अणु	"PowerBook5,5",			"PowerBook G4 17\"",
		PMAC_TYPE_UNKNOWN_INTREPID,	पूर्णांकrepid_features,
		PMAC_MB_MAY_SLEEP | PMAC_MB_HAS_FW_POWER | PMAC_MB_MOBILE,
	पूर्ण,
	अणु	"PowerBook5,6",			"PowerBook G4 15\"",
		PMAC_TYPE_UNKNOWN_INTREPID,	पूर्णांकrepid_features,
		PMAC_MB_MAY_SLEEP | PMAC_MB_HAS_FW_POWER | PMAC_MB_MOBILE,
	पूर्ण,
	अणु	"PowerBook5,7",			"PowerBook G4 17\"",
		PMAC_TYPE_UNKNOWN_INTREPID,	पूर्णांकrepid_features,
		PMAC_MB_MAY_SLEEP | PMAC_MB_HAS_FW_POWER | PMAC_MB_MOBILE,
	पूर्ण,
	अणु	"PowerBook5,8",			"PowerBook G4 15\"",
		PMAC_TYPE_UNKNOWN_INTREPID,	पूर्णांकrepid_features,
		PMAC_MB_MAY_SLEEP  | PMAC_MB_MOBILE,
	पूर्ण,
	अणु	"PowerBook5,9",			"PowerBook G4 17\"",
		PMAC_TYPE_UNKNOWN_INTREPID,	पूर्णांकrepid_features,
		PMAC_MB_MAY_SLEEP | PMAC_MB_MOBILE,
	पूर्ण,
	अणु	"PowerBook6,1",			"PowerBook G4 12\"",
		PMAC_TYPE_UNKNOWN_INTREPID,	पूर्णांकrepid_features,
		PMAC_MB_MAY_SLEEP | PMAC_MB_HAS_FW_POWER | PMAC_MB_MOBILE,
	पूर्ण,
	अणु	"PowerBook6,2",			"PowerBook G4",
		PMAC_TYPE_UNKNOWN_INTREPID,	पूर्णांकrepid_features,
		PMAC_MB_MAY_SLEEP | PMAC_MB_HAS_FW_POWER | PMAC_MB_MOBILE,
	पूर्ण,
	अणु	"PowerBook6,3",			"iBook G4",
		PMAC_TYPE_UNKNOWN_INTREPID,	पूर्णांकrepid_features,
		PMAC_MB_MAY_SLEEP | PMAC_MB_HAS_FW_POWER | PMAC_MB_MOBILE,
	पूर्ण,
	अणु	"PowerBook6,4",			"PowerBook G4 12\"",
		PMAC_TYPE_UNKNOWN_INTREPID,	पूर्णांकrepid_features,
		PMAC_MB_MAY_SLEEP | PMAC_MB_HAS_FW_POWER | PMAC_MB_MOBILE,
	पूर्ण,
	अणु	"PowerBook6,5",			"iBook G4",
		PMAC_TYPE_UNKNOWN_INTREPID,	पूर्णांकrepid_features,
		PMAC_MB_MAY_SLEEP | PMAC_MB_HAS_FW_POWER | PMAC_MB_MOBILE,
	पूर्ण,
	अणु	"PowerBook6,7",			"iBook G4",
		PMAC_TYPE_UNKNOWN_INTREPID,	पूर्णांकrepid_features,
		PMAC_MB_MAY_SLEEP | PMAC_MB_HAS_FW_POWER | PMAC_MB_MOBILE,
	पूर्ण,
	अणु	"PowerBook6,8",			"PowerBook G4 12\"",
		PMAC_TYPE_UNKNOWN_INTREPID,	पूर्णांकrepid_features,
		PMAC_MB_MAY_SLEEP | PMAC_MB_HAS_FW_POWER | PMAC_MB_MOBILE,
	पूर्ण,
#अन्यथा /* CONFIG_PPC64 */
	अणु	"PowerMac7,2",			"PowerMac G5",
		PMAC_TYPE_POWERMAC_G5,		g5_features,
		0,
	पूर्ण,
#अगर_घोषित CONFIG_PPC64
	अणु	"PowerMac7,3",			"PowerMac G5",
		PMAC_TYPE_POWERMAC_G5,		g5_features,
		0,
	पूर्ण,
	अणु	"PowerMac8,1",			"iMac G5",
		PMAC_TYPE_IMAC_G5,		g5_features,
		0,
	पूर्ण,
	अणु	"PowerMac9,1",			"PowerMac G5",
		PMAC_TYPE_POWERMAC_G5_U3L,	g5_features,
		0,
	पूर्ण,
	अणु	"PowerMac11,2",			"PowerMac G5 Dual Core",
		PMAC_TYPE_POWERMAC_G5_U3L,	g5_features,
		0,
	पूर्ण,
	अणु	"PowerMac12,1",			"iMac G5 (iSight)",
		PMAC_TYPE_POWERMAC_G5_U3L,	g5_features,
		0,
	पूर्ण,
	अणु       "RackMac3,1",                   "XServe G5",
		PMAC_TYPE_XSERVE_G5,		g5_features,
		0,
	पूर्ण,
#पूर्ण_अगर /* CONFIG_PPC64 */
#पूर्ण_अगर /* CONFIG_PPC64 */
पूर्ण;

/*
 * The toplevel feature_call callback
 */
दीर्घ pmac_करो_feature_call(अचिन्हित पूर्णांक selector, ...)
अणु
	काष्ठा device_node *node;
	दीर्घ param, value;
	पूर्णांक i;
	feature_call func = शून्य;
	बहु_सूची args;

	अगर (pmac_mb.features)
		क्रम (i=0; pmac_mb.features[i].function; i++)
			अगर (pmac_mb.features[i].selector == selector) अणु
				func = pmac_mb.features[i].function;
				अवरोध;
			पूर्ण
	अगर (!func)
		क्रम (i=0; any_features[i].function; i++)
			अगर (any_features[i].selector == selector) अणु
				func = any_features[i].function;
				अवरोध;
			पूर्ण
	अगर (!func)
		वापस -ENODEV;

	बहु_शुरू(args, selector);
	node = (काष्ठा device_node*)बहु_तर्क(args, व्योम*);
	param = बहु_तर्क(args, दीर्घ);
	value = बहु_तर्क(args, दीर्घ);
	बहु_पूर्ण(args);

	वापस func(node, param, value);
पूर्ण

अटल पूर्णांक __init probe_motherboard(व्योम)
अणु
	पूर्णांक i;
	काष्ठा macio_chip *macio = &macio_chips[0];
	स्थिर अक्षर *model = शून्य;
	काष्ठा device_node *dt;
	पूर्णांक ret = 0;

	/* Lookup known motherboard type in device-tree. First try an
	 * exact match on the "model" property, then try a "compatible"
	 * match is none is found.
	 */
	dt = of_find_node_by_name(शून्य, "device-tree");
	अगर (dt != शून्य)
		model = of_get_property(dt, "model", शून्य);
	क्रम(i=0; model && i<ARRAY_SIZE(pmac_mb_defs); i++) अणु
	    अगर (म_भेद(model, pmac_mb_defs[i].model_string) == 0) अणु
		pmac_mb = pmac_mb_defs[i];
		जाओ found;
	    पूर्ण
	पूर्ण
	क्रम(i=0; i<ARRAY_SIZE(pmac_mb_defs); i++) अणु
	    अगर (of_machine_is_compatible(pmac_mb_defs[i].model_string)) अणु
		pmac_mb = pmac_mb_defs[i];
		जाओ found;
	    पूर्ण
	पूर्ण

	/* Fallback to selection depending on mac-io chip type */
	चयन(macio->type) अणु
#अगर_अघोषित CONFIG_PPC64
	    हाल macio_gअक्रम_central:
		pmac_mb.model_id = PMAC_TYPE_PSURGE;
		pmac_mb.model_name = "Unknown PowerSurge";
		अवरोध;
	    हाल macio_ohare:
		pmac_mb.model_id = PMAC_TYPE_UNKNOWN_OHARE;
		pmac_mb.model_name = "Unknown OHare-based";
		अवरोध;
	    हाल macio_heathrow:
		pmac_mb.model_id = PMAC_TYPE_UNKNOWN_HEATHROW;
		pmac_mb.model_name = "Unknown Heathrow-based";
		pmac_mb.features = heathrow_desktop_features;
		अवरोध;
	    हाल macio_paddington:
		pmac_mb.model_id = PMAC_TYPE_UNKNOWN_PADDINGTON;
		pmac_mb.model_name = "Unknown Paddington-based";
		pmac_mb.features = paddington_features;
		अवरोध;
	    हाल macio_keylargo:
		pmac_mb.model_id = PMAC_TYPE_UNKNOWN_CORE99;
		pmac_mb.model_name = "Unknown Keylargo-based";
		pmac_mb.features = core99_features;
		अवरोध;
	    हाल macio_pangea:
		pmac_mb.model_id = PMAC_TYPE_UNKNOWN_PANGEA;
		pmac_mb.model_name = "Unknown Pangea-based";
		pmac_mb.features = pangea_features;
		अवरोध;
	    हाल macio_पूर्णांकrepid:
		pmac_mb.model_id = PMAC_TYPE_UNKNOWN_INTREPID;
		pmac_mb.model_name = "Unknown Intrepid-based";
		pmac_mb.features = पूर्णांकrepid_features;
		अवरोध;
#अन्यथा /* CONFIG_PPC64 */
	हाल macio_keylargo2:
		pmac_mb.model_id = PMAC_TYPE_UNKNOWN_K2;
		pmac_mb.model_name = "Unknown K2-based";
		pmac_mb.features = g5_features;
		अवरोध;
	हाल macio_shasta:
		pmac_mb.model_id = PMAC_TYPE_UNKNOWN_SHASTA;
		pmac_mb.model_name = "Unknown Shasta-based";
		pmac_mb.features = g5_features;
		अवरोध;
#पूर्ण_अगर /* CONFIG_PPC64 */
	शेष:
		ret = -ENODEV;
		जाओ करोne;
	पूर्ण
found:
#अगर_अघोषित CONFIG_PPC64
	/* Fixup Hooper vs. Comet */
	अगर (pmac_mb.model_id == PMAC_TYPE_HOOPER) अणु
		u32 __iomem * mach_id_ptr = ioremap(0xf3000034, 4);
		अगर (!mach_id_ptr) अणु
			ret = -ENODEV;
			जाओ करोne;
		पूर्ण
		/* Here, I used to disable the media-bay on comet. It
		 * appears this is wrong, the floppy connector is actually
		 * a kind of media-bay and works with the current driver.
		 */
		अगर (__raw_पढ़ोl(mach_id_ptr) & 0x20000000UL)
			pmac_mb.model_id = PMAC_TYPE_COMET;
		iounmap(mach_id_ptr);
	पूर्ण

	/* Set शेष value of घातersave_nap on machines that support it.
	 * It appears that uninorth rev 3 has a problem with it, we करोn't
	 * enable it on those. In theory, the flush-on-lock property is
	 * supposed to be set when not supported, but I'm not very confident
	 * that all Apple OF revs did it properly, I करो it the paranoid way.
	 */
	अगर (uninorth_base && uninorth_rev > 3) अणु
		काष्ठा device_node *np;

		क्रम_each_of_cpu_node(np) अणु
			पूर्णांक cpu_count = 1;

			/* Nap mode not supported on SMP */
			अगर (of_get_property(np, "flush-on-lock", शून्य) ||
			    (cpu_count > 1)) अणु
				घातersave_nap = 0;
				of_node_put(np);
				अवरोध;
			पूर्ण

			cpu_count++;
			घातersave_nap = 1;
		पूर्ण
	पूर्ण
	अगर (घातersave_nap)
		prपूर्णांकk(KERN_DEBUG "Processor NAP mode on idle enabled.\n");

	/* On CPUs that support it (750FX), lowspeed by शेष during
	 * NAP mode
	 */
	घातersave_lowspeed = 1;

#अन्यथा /* CONFIG_PPC64 */
	घातersave_nap = 1;
#पूर्ण_अगर  /* CONFIG_PPC64 */

	/* Check क्रम "mobile" machine */
	अगर (model && (म_भेदन(model, "PowerBook", 9) == 0
		   || म_भेदन(model, "iBook", 5) == 0))
		pmac_mb.board_flags |= PMAC_MB_MOBILE;


	prपूर्णांकk(KERN_INFO "PowerMac motherboard: %s\n", pmac_mb.model_name);
करोne:
	of_node_put(dt);
	वापस ret;
पूर्ण

/* Initialize the Core99 UniNorth host bridge and memory controller
 */
अटल व्योम __init probe_uninorth(व्योम)
अणु
	स्थिर u32 *addrp;
	phys_addr_t address;
	अचिन्हित दीर्घ actrl;

	/* Locate core99 Uni-N */
	uninorth_node = of_find_node_by_name(शून्य, "uni-n");
	uninorth_maj = 1;

	/* Locate G5 u3 */
	अगर (uninorth_node == शून्य) अणु
		uninorth_node = of_find_node_by_name(शून्य, "u3");
		uninorth_maj = 3;
	पूर्ण
	/* Locate G5 u4 */
	अगर (uninorth_node == शून्य) अणु
		uninorth_node = of_find_node_by_name(शून्य, "u4");
		uninorth_maj = 4;
	पूर्ण
	अगर (uninorth_node == शून्य) अणु
		uninorth_maj = 0;
		वापस;
	पूर्ण

	addrp = of_get_property(uninorth_node, "reg", शून्य);
	अगर (addrp == शून्य)
		वापस;
	address = of_translate_address(uninorth_node, addrp);
	अगर (address == 0)
		वापस;
	uninorth_base = ioremap(address, 0x40000);
	अगर (uninorth_base == शून्य)
		वापस;
	uninorth_rev = in_be32(UN_REG(UNI_N_VERSION));
	अगर (uninorth_maj == 3 || uninorth_maj == 4) अणु
		u3_ht_base = ioremap(address + U3_HT_CONFIG_BASE, 0x1000);
		अगर (u3_ht_base == शून्य) अणु
			iounmap(uninorth_base);
			वापस;
		पूर्ण
	पूर्ण

	prपूर्णांकk(KERN_INFO "Found %s memory controller & host bridge"
	       " @ 0x%08x revision: 0x%02x\n", uninorth_maj == 3 ? "U3" :
	       uninorth_maj == 4 ? "U4" : "UniNorth",
	       (अचिन्हित पूर्णांक)address, uninorth_rev);
	prपूर्णांकk(KERN_INFO "Mapped at 0x%08lx\n", (अचिन्हित दीर्घ)uninorth_base);

	/* Set the arbitrer QAck delay according to what Apple करोes
	 */
	अगर (uninorth_rev < 0x11) अणु
		actrl = UN_IN(UNI_N_ARB_CTRL) & ~UNI_N_ARB_CTRL_QACK_DELAY_MASK;
		actrl |= ((uninorth_rev < 3) ? UNI_N_ARB_CTRL_QACK_DELAY105 :
			UNI_N_ARB_CTRL_QACK_DELAY) <<
			UNI_N_ARB_CTRL_QACK_DELAY_SHIFT;
		UN_OUT(UNI_N_ARB_CTRL, actrl);
	पूर्ण

	/* Some more magic as करोne by them in recent MacOS X on UniNorth
	 * revs 1.5 to 2.O and Pangea. Seem to toggle the UniN Maxbus/PCI
	 * memory समयout
	 */
	अगर ((uninorth_rev >= 0x11 && uninorth_rev <= 0x24) ||
	    uninorth_rev == 0xc0)
		UN_OUT(0x2160, UN_IN(0x2160) & 0x00ffffff);
पूर्ण

अटल व्योम __init probe_one_macio(स्थिर अक्षर *name, स्थिर अक्षर *compat, पूर्णांक type)
अणु
	काष्ठा device_node*	node;
	पूर्णांक			i;
	अस्थिर u32 __iomem	*base;
	स्थिर u32		*addrp, *revp;
	phys_addr_t		addr;
	u64			size;

	क्रम_each_node_by_name(node, name) अणु
		अगर (!compat)
			अवरोध;
		अगर (of_device_is_compatible(node, compat))
			अवरोध;
	पूर्ण
	अगर (!node)
		वापस;
	क्रम(i=0; i<MAX_MACIO_CHIPS; i++) अणु
		अगर (!macio_chips[i].of_node)
			अवरोध;
		अगर (macio_chips[i].of_node == node)
			वापस;
	पूर्ण

	अगर (i >= MAX_MACIO_CHIPS) अणु
		prपूर्णांकk(KERN_ERR "pmac_feature: Please increase MAX_MACIO_CHIPS !\n");
		prपूर्णांकk(KERN_ERR "pmac_feature: %pOF skipped\n", node);
		वापस;
	पूर्ण
	addrp = of_get_pci_address(node, 0, &size, शून्य);
	अगर (addrp == शून्य) अणु
		prपूर्णांकk(KERN_ERR "pmac_feature: %pOF: can't find base !\n",
		       node);
		वापस;
	पूर्ण
	addr = of_translate_address(node, addrp);
	अगर (addr == 0) अणु
		prपूर्णांकk(KERN_ERR "pmac_feature: %pOF, can't translate base !\n",
		       node);
		वापस;
	पूर्ण
	base = ioremap(addr, (अचिन्हित दीर्घ)size);
	अगर (!base) अणु
		prपूर्णांकk(KERN_ERR "pmac_feature: %pOF, can't map mac-io chip !\n",
		       node);
		वापस;
	पूर्ण
	अगर (type == macio_keylargo || type == macio_keylargo2) अणु
		स्थिर u32 *did = of_get_property(node, "device-id", शून्य);
		अगर (*did == 0x00000025)
			type = macio_pangea;
		अगर (*did == 0x0000003e)
			type = macio_पूर्णांकrepid;
		अगर (*did == 0x0000004f)
			type = macio_shasta;
	पूर्ण
	macio_chips[i].of_node	= node;
	macio_chips[i].type	= type;
	macio_chips[i].base	= base;
	macio_chips[i].flags	= MACIO_FLAG_SCCA_ON | MACIO_FLAG_SCCB_ON;
	macio_chips[i].name	= macio_names[type];
	revp = of_get_property(node, "revision-id", शून्य);
	अगर (revp)
		macio_chips[i].rev = *revp;
	prपूर्णांकk(KERN_INFO "Found a %s mac-io controller, rev: %d, mapped at 0x%p\n",
		macio_names[type], macio_chips[i].rev, macio_chips[i].base);
पूर्ण

अटल पूर्णांक __init
probe_macios(व्योम)
अणु
	/* Warning, ordering is important */
	probe_one_macio("gc", शून्य, macio_gअक्रम_central);
	probe_one_macio("ohare", शून्य, macio_ohare);
	probe_one_macio("pci106b,7", शून्य, macio_ohareII);
	probe_one_macio("mac-io", "keylargo", macio_keylargo);
	probe_one_macio("mac-io", "paddington", macio_paddington);
	probe_one_macio("mac-io", "gatwick", macio_gatwick);
	probe_one_macio("mac-io", "heathrow", macio_heathrow);
	probe_one_macio("mac-io", "K2-Keylargo", macio_keylargo2);

	/* Make sure the "main" macio chip appear first */
	अगर (macio_chips[0].type == macio_gatwick
	    && macio_chips[1].type == macio_heathrow) अणु
		काष्ठा macio_chip temp = macio_chips[0];
		macio_chips[0] = macio_chips[1];
		macio_chips[1] = temp;
	पूर्ण
	अगर (macio_chips[0].type == macio_ohareII
	    && macio_chips[1].type == macio_ohare) अणु
		काष्ठा macio_chip temp = macio_chips[0];
		macio_chips[0] = macio_chips[1];
		macio_chips[1] = temp;
	पूर्ण
	macio_chips[0].lbus.index = 0;
	macio_chips[1].lbus.index = 1;

	वापस (macio_chips[0].of_node == शून्य) ? -ENODEV : 0;
पूर्ण

अटल व्योम __init
initial_serial_shutकरोwn(काष्ठा device_node *np)
अणु
	पूर्णांक len;
	स्थिर काष्ठा slot_names_prop अणु
		पूर्णांक	count;
		अक्षर	name[1];
	पूर्ण *slots;
	स्थिर अक्षर *conn;
	पूर्णांक port_type = PMAC_SCC_ASYNC;
	पूर्णांक modem = 0;

	slots = of_get_property(np, "slot-names", &len);
	conn = of_get_property(np, "AAPL,connector", &len);
	अगर (conn && (म_भेद(conn, "infrared") == 0))
		port_type = PMAC_SCC_IRDA;
	अन्यथा अगर (of_device_is_compatible(np, "cobalt"))
		modem = 1;
	अन्यथा अगर (slots && slots->count > 0) अणु
		अगर (म_भेद(slots->name, "IrDA") == 0)
			port_type = PMAC_SCC_IRDA;
		अन्यथा अगर (म_भेद(slots->name, "Modem") == 0)
			modem = 1;
	पूर्ण
	अगर (modem)
		pmac_call_feature(PMAC_FTR_MODEM_ENABLE, np, 0, 0);
	pmac_call_feature(PMAC_FTR_SCC_ENABLE, np, port_type, 0);
पूर्ण

अटल व्योम __init
set_initial_features(व्योम)
अणु
	काष्ठा device_node *np;

	/* That hack appears to be necessary क्रम some StarMax motherboards
	 * but I'm not too sure it was audited क्रम side-effects on other
	 * ohare based machines...
	 * Since I still have dअगरficulties figuring the right way to
	 * dअगरferentiate them all and since that hack was there क्रम a दीर्घ
	 * समय, I'll keep it around
	 */
	अगर (macio_chips[0].type == macio_ohare) अणु
		काष्ठा macio_chip *macio = &macio_chips[0];
		np = of_find_node_by_name(शून्य, "via-pmu");
		अगर (np)
			MACIO_BIS(OHARE_FCR, OH_IOBUS_ENABLE);
		अन्यथा
			MACIO_OUT32(OHARE_FCR, STARMAX_FEATURES);
		of_node_put(np);
	पूर्ण अन्यथा अगर (macio_chips[1].type == macio_ohare) अणु
		काष्ठा macio_chip *macio = &macio_chips[1];
		MACIO_BIS(OHARE_FCR, OH_IOBUS_ENABLE);
	पूर्ण

#अगर_घोषित CONFIG_PPC64
	अगर (macio_chips[0].type == macio_keylargo2 ||
	    macio_chips[0].type == macio_shasta) अणु
#अगर_अघोषित CONFIG_SMP
		/* On SMP machines running UP, we have the second CPU eating
		 * bus cycles. We need to take it off the bus. This is करोne
		 * from pmac_smp क्रम SMP kernels running on one CPU
		 */
		np = of_find_node_by_type(शून्य, "cpu");
		अगर (np != शून्य)
			np = of_find_node_by_type(np, "cpu");
		अगर (np != शून्य) अणु
			g5_phy_disable_cpu1();
			of_node_put(np);
		पूर्ण
#पूर्ण_अगर /* CONFIG_SMP */
		/* Enable GMAC क्रम now क्रम PCI probing. It will be disabled
		 * later on after PCI probe
		 */
		क्रम_each_node_by_name(np, "ethernet")
			अगर (of_device_is_compatible(np, "K2-GMAC"))
				g5_gmac_enable(np, 0, 1);

		/* Enable FW beक्रमe PCI probe. Will be disabled later on
		 * Note: We should have a batter way to check that we are
		 * dealing with uninorth पूर्णांकernal cell and not a PCI cell
		 * on the बाह्यal PCI. The code below works though.
		 */
		क्रम_each_node_by_name(np, "firewire") अणु
			अगर (of_device_is_compatible(np, "pci106b,5811")) अणु
				macio_chips[0].flags |= MACIO_FLAG_FW_SUPPORTED;
				g5_fw_enable(np, 0, 1);
			पूर्ण
		पूर्ण
	पूर्ण
#अन्यथा /* CONFIG_PPC64 */

	अगर (macio_chips[0].type == macio_keylargo ||
	    macio_chips[0].type == macio_pangea ||
	    macio_chips[0].type == macio_पूर्णांकrepid) अणु
		/* Enable GMAC क्रम now क्रम PCI probing. It will be disabled
		 * later on after PCI probe
		 */
		क्रम_each_node_by_name(np, "ethernet") अणु
			अगर (np->parent
			    && of_device_is_compatible(np->parent, "uni-north")
			    && of_device_is_compatible(np, "gmac"))
				core99_gmac_enable(np, 0, 1);
		पूर्ण

		/* Enable FW beक्रमe PCI probe. Will be disabled later on
		 * Note: We should have a batter way to check that we are
		 * dealing with uninorth पूर्णांकernal cell and not a PCI cell
		 * on the बाह्यal PCI. The code below works though.
		 */
		क्रम_each_node_by_name(np, "firewire") अणु
			अगर (np->parent
			    && of_device_is_compatible(np->parent, "uni-north")
			    && (of_device_is_compatible(np, "pci106b,18") ||
			        of_device_is_compatible(np, "pci106b,30") ||
			        of_device_is_compatible(np, "pci11c1,5811"))) अणु
				macio_chips[0].flags |= MACIO_FLAG_FW_SUPPORTED;
				core99_firewire_enable(np, 0, 1);
			पूर्ण
		पूर्ण

		/* Enable ATA-100 beक्रमe PCI probe. */
		क्रम_each_node_by_name(np, "ata-6") अणु
			अगर (np->parent
			    && of_device_is_compatible(np->parent, "uni-north")
			    && of_device_is_compatible(np, "kauai-ata")) अणु
				core99_ata100_enable(np, 1);
			पूर्ण
		पूर्ण

		/* Switch airport off */
		क्रम_each_node_by_name(np, "radio") अणु
			अगर (np->parent == macio_chips[0].of_node) अणु
				macio_chips[0].flags |= MACIO_FLAG_AIRPORT_ON;
				core99_airport_enable(np, 0, 0);
			पूर्ण
		पूर्ण
	पूर्ण

	/* On all machines that support sound PM, चयन sound off */
	अगर (macio_chips[0].of_node)
		pmac_करो_feature_call(PMAC_FTR_SOUND_CHIP_ENABLE,
			macio_chips[0].of_node, 0, 0);

	/* While on some desktop G3s, we turn it back on */
	अगर (macio_chips[0].of_node && macio_chips[0].type == macio_heathrow
		&& (pmac_mb.model_id == PMAC_TYPE_GOSSAMER ||
		    pmac_mb.model_id == PMAC_TYPE_SILK)) अणु
		काष्ठा macio_chip *macio = &macio_chips[0];
		MACIO_BIS(HEATHROW_FCR, HRW_SOUND_CLK_ENABLE);
		MACIO_BIC(HEATHROW_FCR, HRW_SOUND_POWER_N);
	पूर्ण

#पूर्ण_अगर /* CONFIG_PPC64 */

	/* On all machines, चयन modem & serial ports off */
	क्रम_each_node_by_name(np, "ch-a")
		initial_serial_shutकरोwn(np);
	क्रम_each_node_by_name(np, "ch-b")
		initial_serial_shutकरोwn(np);
पूर्ण

व्योम __init
pmac_feature_init(व्योम)
अणु
	/* Detect the UniNorth memory controller */
	probe_uninorth();

	/* Probe mac-io controllers */
	अगर (probe_macios()) अणु
		prपूर्णांकk(KERN_WARNING "No mac-io chip found\n");
		वापस;
	पूर्ण

	/* Probe machine type */
	अगर (probe_motherboard())
		prपूर्णांकk(KERN_WARNING "Unknown PowerMac !\n");

	/* Set some initial features (turn off some chips that will
	 * be later turned on)
	 */
	set_initial_features();
पूर्ण

#अगर 0
अटल व्योम dump_HT_speeds(अक्षर *name, u32 cfg, u32 frq)
अणु
	पूर्णांक	freqs[16] = अणु 200,300,400,500,600,800,1000,0,0,0,0,0,0,0,0,0 पूर्ण;
	पूर्णांक	bits[8] = अणु 8,16,0,32,2,4,0,0 पूर्ण;
	पूर्णांक	freq = (frq >> 8) & 0xf;

	अगर (freqs[freq] == 0)
		prपूर्णांकk("%s: Unknown HT link frequency %x\n", name, freq);
	अन्यथा
		prपूर्णांकk("%s: %d MHz on main link, (%d in / %d out) bits width\n",
		       name, freqs[freq],
		       bits[(cfg >> 28) & 0x7], bits[(cfg >> 24) & 0x7]);
पूर्ण

व्योम __init pmac_check_ht_link(व्योम)
अणु
	u32	ufreq, freq, ucfg, cfg;
	काष्ठा device_node *pcix_node;
	u8	px_bus, px_devfn;
	काष्ठा pci_controller *px_hose;

	(व्योम)in_be32(u3_ht_base + U3_HT_LINK_COMMAND);
	ucfg = cfg = in_be32(u3_ht_base + U3_HT_LINK_CONFIG);
	ufreq = freq = in_be32(u3_ht_base + U3_HT_LINK_FREQ);
	dump_HT_speeds("U3 HyperTransport", cfg, freq);

	pcix_node = of_find_compatible_node(शून्य, "pci", "pci-x");
	अगर (pcix_node == शून्य) अणु
		prपूर्णांकk("No PCI-X bridge found\n");
		वापस;
	पूर्ण
	अगर (pci_device_from_OF_node(pcix_node, &px_bus, &px_devfn) != 0) अणु
		prपूर्णांकk("PCI-X bridge found but not matched to pci\n");
		वापस;
	पूर्ण
	px_hose = pci_find_hose_क्रम_OF_device(pcix_node);
	अगर (px_hose == शून्य) अणु
		prपूर्णांकk("PCI-X bridge found but not matched to host\n");
		वापस;
	पूर्ण	
	early_पढ़ो_config_dword(px_hose, px_bus, px_devfn, 0xc4, &cfg);
	early_पढ़ो_config_dword(px_hose, px_bus, px_devfn, 0xcc, &freq);
	dump_HT_speeds("PCI-X HT Uplink", cfg, freq);
	early_पढ़ो_config_dword(px_hose, px_bus, px_devfn, 0xc8, &cfg);
	early_पढ़ो_config_dword(px_hose, px_bus, px_devfn, 0xd0, &freq);
	dump_HT_speeds("PCI-X HT Downlink", cfg, freq);
पूर्ण
#पूर्ण_अगर /* 0 */

/*
 * Early video resume hook
 */

अटल व्योम (*pmac_early_vresume_proc)(व्योम *data);
अटल व्योम *pmac_early_vresume_data;

व्योम pmac_set_early_video_resume(व्योम (*proc)(व्योम *data), व्योम *data)
अणु
	अगर (!machine_is(घातermac))
		वापस;
	preempt_disable();
	pmac_early_vresume_proc = proc;
	pmac_early_vresume_data = data;
	preempt_enable();
पूर्ण
EXPORT_SYMBOL(pmac_set_early_video_resume);

व्योम pmac_call_early_video_resume(व्योम)
अणु
	अगर (pmac_early_vresume_proc)
		pmac_early_vresume_proc(pmac_early_vresume_data);
पूर्ण

/*
 * AGP related suspend/resume code
 */

अटल काष्ठा pci_dev *pmac_agp_bridge;
अटल पूर्णांक (*pmac_agp_suspend)(काष्ठा pci_dev *bridge);
अटल पूर्णांक (*pmac_agp_resume)(काष्ठा pci_dev *bridge);

व्योम pmac_रेजिस्टर_agp_pm(काष्ठा pci_dev *bridge,
				 पूर्णांक (*suspend)(काष्ठा pci_dev *bridge),
				 पूर्णांक (*resume)(काष्ठा pci_dev *bridge))
अणु
	अगर (suspend || resume) अणु
		pmac_agp_bridge = bridge;
		pmac_agp_suspend = suspend;
		pmac_agp_resume = resume;
		वापस;
	पूर्ण
	अगर (bridge != pmac_agp_bridge)
		वापस;
	pmac_agp_suspend = pmac_agp_resume = शून्य;
	वापस;
पूर्ण
EXPORT_SYMBOL(pmac_रेजिस्टर_agp_pm);

व्योम pmac_suspend_agp_क्रम_card(काष्ठा pci_dev *dev)
अणु
	अगर (pmac_agp_bridge == शून्य || pmac_agp_suspend == शून्य)
		वापस;
	अगर (pmac_agp_bridge->bus != dev->bus)
		वापस;
	pmac_agp_suspend(pmac_agp_bridge);
पूर्ण
EXPORT_SYMBOL(pmac_suspend_agp_क्रम_card);

व्योम pmac_resume_agp_क्रम_card(काष्ठा pci_dev *dev)
अणु
	अगर (pmac_agp_bridge == शून्य || pmac_agp_resume == शून्य)
		वापस;
	अगर (pmac_agp_bridge->bus != dev->bus)
		वापस;
	pmac_agp_resume(pmac_agp_bridge);
पूर्ण
EXPORT_SYMBOL(pmac_resume_agp_क्रम_card);

पूर्णांक pmac_get_uninorth_variant(व्योम)
अणु
	वापस uninorth_maj;
पूर्ण
