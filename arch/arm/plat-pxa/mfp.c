<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/arch/arm/plat-pxa/mfp.c
 *
 *   Multi-Function Pin Support
 *
 * Copyright (C) 2007 Marvell Internation Ltd.
 *
 * 2007-08-21: eric miao <eric.miao@marvell.com>
 *             initial version
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>

#समावेश <plat/mfp.h>

#घोषणा MFPR_SIZE	(PAGE_SIZE)

/* MFPR रेजिस्टर bit definitions */
#घोषणा MFPR_PULL_SEL		(0x1 << 15)
#घोषणा MFPR_PULLUP_EN		(0x1 << 14)
#घोषणा MFPR_PULLDOWN_EN	(0x1 << 13)
#घोषणा MFPR_SLEEP_SEL		(0x1 << 9)
#घोषणा MFPR_SLEEP_OE_N		(0x1 << 7)
#घोषणा MFPR_EDGE_CLEAR		(0x1 << 6)
#घोषणा MFPR_EDGE_FALL_EN	(0x1 << 5)
#घोषणा MFPR_EDGE_RISE_EN	(0x1 << 4)

#घोषणा MFPR_SLEEP_DATA(x)	((x) << 8)
#घोषणा MFPR_DRIVE(x)		(((x) & 0x7) << 10)
#घोषणा MFPR_AF_SEL(x)		(((x) & 0x7) << 0)

#घोषणा MFPR_EDGE_NONE		(0)
#घोषणा MFPR_EDGE_RISE		(MFPR_EDGE_RISE_EN)
#घोषणा MFPR_EDGE_FALL		(MFPR_EDGE_FALL_EN)
#घोषणा MFPR_EDGE_BOTH		(MFPR_EDGE_RISE | MFPR_EDGE_FALL)

/*
 * Table that determines the low घातer modes outमाला_दो, with actual settings
 * used in parentheses क्रम करोn't-care values. Except क्रम the भग्न output,
 * the configured driven and pulled levels match, so अगर there is a need क्रम
 * non-LPM pulled output, the same configuration could probably be used.
 *
 * Output value  sleep_oe_n  sleep_data  pullup_en  pullकरोwn_en  pull_sel
 *                 (bit 7)    (bit 8)    (bit 14)     (bit 13)   (bit 15)
 *
 * Input            0          X(0)        X(0)        X(0)       0
 * Drive 0          0          0           0           X(1)       0
 * Drive 1          0          1           X(1)        0	  0
 * Pull hi (1)      1          X(1)        1           0	  0
 * Pull lo (0)      1          X(0)        0           1	  0
 * Z (भग्न)        1          X(0)        0           0	  0
 */
#घोषणा MFPR_LPM_INPUT		(0)
#घोषणा MFPR_LPM_DRIVE_LOW	(MFPR_SLEEP_DATA(0) | MFPR_PULLDOWN_EN)
#घोषणा MFPR_LPM_DRIVE_HIGH    	(MFPR_SLEEP_DATA(1) | MFPR_PULLUP_EN)
#घोषणा MFPR_LPM_PULL_LOW      	(MFPR_LPM_DRIVE_LOW  | MFPR_SLEEP_OE_N)
#घोषणा MFPR_LPM_PULL_HIGH     	(MFPR_LPM_DRIVE_HIGH | MFPR_SLEEP_OE_N)
#घोषणा MFPR_LPM_FLOAT         	(MFPR_SLEEP_OE_N)
#घोषणा MFPR_LPM_MASK		(0xe080)

/*
 * The pullup and pullकरोwn state of the MFP pin at run mode is by शेष
 * determined by the selected alternate function. In हाल that some buggy
 * devices need to override this शेष behavior,  the definitions below
 * indicates the setting of corresponding MFPR bits
 *
 * Definition       pull_sel  pullup_en  pullकरोwn_en
 * MFPR_PULL_NONE       0         0        0
 * MFPR_PULL_LOW        1         0        1
 * MFPR_PULL_HIGH       1         1        0
 * MFPR_PULL_BOTH       1         1        1
 * MFPR_PULL_FLOAT	1         0        0
 */
#घोषणा MFPR_PULL_NONE		(0)
#घोषणा MFPR_PULL_LOW		(MFPR_PULL_SEL | MFPR_PULLDOWN_EN)
#घोषणा MFPR_PULL_BOTH		(MFPR_PULL_LOW | MFPR_PULLUP_EN)
#घोषणा MFPR_PULL_HIGH		(MFPR_PULL_SEL | MFPR_PULLUP_EN)
#घोषणा MFPR_PULL_FLOAT		(MFPR_PULL_SEL)

/* mfp_spin_lock is used to ensure that MFP रेजिस्टर configuration
 * (most likely a पढ़ो-modअगरy-ग_लिखो operation) is atomic, and that
 * mfp_table[] is consistent
 */
अटल DEFINE_SPINLOCK(mfp_spin_lock);

अटल व्योम __iomem *mfpr_mmio_base;

काष्ठा mfp_pin अणु
	अचिन्हित दीर्घ	config;		/* -1 क्रम not configured */
	अचिन्हित दीर्घ	mfpr_off;	/* MFPRxx Register offset */
	अचिन्हित दीर्घ	mfpr_run;	/* Run-Mode Register Value */
	अचिन्हित दीर्घ	mfpr_lpm;	/* Low Power Mode Register Value */
पूर्ण;

अटल काष्ठा mfp_pin mfp_table[MFP_PIN_MAX];

/* mapping of MFP_LPM_* definitions to MFPR_LPM_* रेजिस्टर bits */
अटल स्थिर अचिन्हित दीर्घ mfpr_lpm[] = अणु
	MFPR_LPM_INPUT,
	MFPR_LPM_DRIVE_LOW,
	MFPR_LPM_DRIVE_HIGH,
	MFPR_LPM_PULL_LOW,
	MFPR_LPM_PULL_HIGH,
	MFPR_LPM_FLOAT,
	MFPR_LPM_INPUT,
पूर्ण;

/* mapping of MFP_PULL_* definitions to MFPR_PULL_* रेजिस्टर bits */
अटल स्थिर अचिन्हित दीर्घ mfpr_pull[] = अणु
	MFPR_PULL_NONE,
	MFPR_PULL_LOW,
	MFPR_PULL_HIGH,
	MFPR_PULL_BOTH,
	MFPR_PULL_FLOAT,
पूर्ण;

/* mapping of MFP_LPM_EDGE_* definitions to MFPR_EDGE_* रेजिस्टर bits */
अटल स्थिर अचिन्हित दीर्घ mfpr_edge[] = अणु
	MFPR_EDGE_NONE,
	MFPR_EDGE_RISE,
	MFPR_EDGE_FALL,
	MFPR_EDGE_BOTH,
पूर्ण;

#घोषणा mfpr_पढ़ोl(off)			\
	__raw_पढ़ोl(mfpr_mmio_base + (off))

#घोषणा mfpr_ग_लिखोl(off, val)		\
	__raw_ग_लिखोl(val, mfpr_mmio_base + (off))

#घोषणा mfp_configured(p)	((p)->config != -1)

/*
 * perक्रमm a पढ़ो-back of any valid MFPR रेजिस्टर to make sure the
 * previous writings are finished
 */
अटल अचिन्हित दीर्घ mfpr_off_पढ़ोback;
#घोषणा mfpr_sync()	(व्योम)__raw_पढ़ोl(mfpr_mmio_base + mfpr_off_पढ़ोback)

अटल अंतरभूत व्योम __mfp_config_run(काष्ठा mfp_pin *p)
अणु
	अगर (mfp_configured(p))
		mfpr_ग_लिखोl(p->mfpr_off, p->mfpr_run);
पूर्ण

अटल अंतरभूत व्योम __mfp_config_lpm(काष्ठा mfp_pin *p)
अणु
	अगर (mfp_configured(p)) अणु
		अचिन्हित दीर्घ mfpr_clr = (p->mfpr_run & ~MFPR_EDGE_BOTH) | MFPR_EDGE_CLEAR;
		अगर (mfpr_clr != p->mfpr_run)
			mfpr_ग_लिखोl(p->mfpr_off, mfpr_clr);
		अगर (p->mfpr_lpm != mfpr_clr)
			mfpr_ग_लिखोl(p->mfpr_off, p->mfpr_lpm);
	पूर्ण
पूर्ण

व्योम mfp_config(अचिन्हित दीर्घ *mfp_cfgs, पूर्णांक num)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	spin_lock_irqsave(&mfp_spin_lock, flags);

	क्रम (i = 0; i < num; i++, mfp_cfgs++) अणु
		अचिन्हित दीर्घ पंचांगp, c = *mfp_cfgs;
		काष्ठा mfp_pin *p;
		पूर्णांक pin, af, drv, lpm, edge, pull;

		pin = MFP_PIN(c);
		BUG_ON(pin >= MFP_PIN_MAX);
		p = &mfp_table[pin];

		af  = MFP_AF(c);
		drv = MFP_DS(c);
		lpm = MFP_LPM_STATE(c);
		edge = MFP_LPM_EDGE(c);
		pull = MFP_PULL(c);

		/* run-mode pull settings will conflict with MFPR bits of
		 * low घातer mode state,  calculate mfpr_run and mfpr_lpm
		 * inभागidually अगर pull != MFP_PULL_NONE
		 */
		पंचांगp = MFPR_AF_SEL(af) | MFPR_DRIVE(drv);

		अगर (likely(pull == MFP_PULL_NONE)) अणु
			p->mfpr_run = पंचांगp | mfpr_lpm[lpm] | mfpr_edge[edge];
			p->mfpr_lpm = p->mfpr_run;
		पूर्ण अन्यथा अणु
			p->mfpr_lpm = पंचांगp | mfpr_lpm[lpm] | mfpr_edge[edge];
			p->mfpr_run = पंचांगp | mfpr_pull[pull];
		पूर्ण

		p->config = c; __mfp_config_run(p);
	पूर्ण

	mfpr_sync();
	spin_unlock_irqrestore(&mfp_spin_lock, flags);
पूर्ण

अचिन्हित दीर्घ mfp_पढ़ो(पूर्णांक mfp)
अणु
	अचिन्हित दीर्घ val, flags;

	BUG_ON(mfp < 0 || mfp >= MFP_PIN_MAX);

	spin_lock_irqsave(&mfp_spin_lock, flags);
	val = mfpr_पढ़ोl(mfp_table[mfp].mfpr_off);
	spin_unlock_irqrestore(&mfp_spin_lock, flags);

	वापस val;
पूर्ण

व्योम mfp_ग_लिखो(पूर्णांक mfp, अचिन्हित दीर्घ val)
अणु
	अचिन्हित दीर्घ flags;

	BUG_ON(mfp < 0 || mfp >= MFP_PIN_MAX);

	spin_lock_irqsave(&mfp_spin_lock, flags);
	mfpr_ग_लिखोl(mfp_table[mfp].mfpr_off, val);
	mfpr_sync();
	spin_unlock_irqrestore(&mfp_spin_lock, flags);
पूर्ण

व्योम __init mfp_init_base(व्योम __iomem *mfpr_base)
अणु
	पूर्णांक i;

	/* initialize the table with शेष - unconfigured */
	क्रम (i = 0; i < ARRAY_SIZE(mfp_table); i++)
		mfp_table[i].config = -1;

	mfpr_mmio_base = mfpr_base;
पूर्ण

व्योम __init mfp_init_addr(काष्ठा mfp_addr_map *map)
अणु
	काष्ठा mfp_addr_map *p;
	अचिन्हित दीर्घ offset, flags;
	पूर्णांक i;

	spin_lock_irqsave(&mfp_spin_lock, flags);

	/* mfp offset क्रम पढ़ोback */
	mfpr_off_पढ़ोback = map[0].offset;

	क्रम (p = map; p->start != MFP_PIN_INVALID; p++) अणु
		offset = p->offset;
		i = p->start;

		करो अणु
			mfp_table[i].mfpr_off = offset;
			mfp_table[i].mfpr_run = 0;
			mfp_table[i].mfpr_lpm = 0;
			offset += 4; i++;
		पूर्ण जबतक ((i <= p->end) && (p->end != -1));
	पूर्ण

	spin_unlock_irqrestore(&mfp_spin_lock, flags);
पूर्ण

व्योम mfp_config_lpm(व्योम)
अणु
	काष्ठा mfp_pin *p = &mfp_table[0];
	पूर्णांक pin;

	क्रम (pin = 0; pin < ARRAY_SIZE(mfp_table); pin++, p++)
		__mfp_config_lpm(p);
पूर्ण

व्योम mfp_config_run(व्योम)
अणु
	काष्ठा mfp_pin *p = &mfp_table[0];
	पूर्णांक pin;

	क्रम (pin = 0; pin < ARRAY_SIZE(mfp_table); pin++, p++)
		__mfp_config_run(p);
पूर्ण
