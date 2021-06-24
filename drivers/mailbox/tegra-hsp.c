<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2016-2018, NVIDIA CORPORATION.  All rights reserved.
 */

#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/mailbox_controller.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm.h>
#समावेश <linux/slab.h>

#समावेश <soc/tegra/fuse.h>

#समावेश <dt-bindings/mailbox/tegra186-hsp.h>

#समावेश "mailbox.h"

#घोषणा HSP_INT_IE(x)		(0x100 + ((x) * 4))
#घोषणा HSP_INT_IV		0x300
#घोषणा HSP_INT_IR		0x304

#घोषणा HSP_INT_EMPTY_SHIFT	0
#घोषणा HSP_INT_EMPTY_MASK	0xff
#घोषणा HSP_INT_FULL_SHIFT	8
#घोषणा HSP_INT_FULL_MASK	0xff

#घोषणा HSP_INT_DIMENSIONING	0x380
#घोषणा HSP_nSM_SHIFT		0
#घोषणा HSP_nSS_SHIFT		4
#घोषणा HSP_nAS_SHIFT		8
#घोषणा HSP_nDB_SHIFT		12
#घोषणा HSP_nSI_SHIFT		16
#घोषणा HSP_nINT_MASK		0xf

#घोषणा HSP_DB_TRIGGER	0x0
#घोषणा HSP_DB_ENABLE	0x4
#घोषणा HSP_DB_RAW	0x8
#घोषणा HSP_DB_PENDING	0xc

#घोषणा HSP_SM_SHRD_MBOX	0x0
#घोषणा HSP_SM_SHRD_MBOX_FULL	BIT(31)
#घोषणा HSP_SM_SHRD_MBOX_FULL_INT_IE	0x04
#घोषणा HSP_SM_SHRD_MBOX_EMPTY_INT_IE	0x08

#घोषणा HSP_DB_CCPLEX		1
#घोषणा HSP_DB_BPMP		3
#घोषणा HSP_DB_MAX		7

काष्ठा tegra_hsp_channel;
काष्ठा tegra_hsp;

काष्ठा tegra_hsp_channel अणु
	काष्ठा tegra_hsp *hsp;
	काष्ठा mbox_chan *chan;
	व्योम __iomem *regs;
पूर्ण;

काष्ठा tegra_hsp_करोorbell अणु
	काष्ठा tegra_hsp_channel channel;
	काष्ठा list_head list;
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक master;
	अचिन्हित पूर्णांक index;
पूर्ण;

काष्ठा tegra_hsp_mailbox अणु
	काष्ठा tegra_hsp_channel channel;
	अचिन्हित पूर्णांक index;
	bool producer;
पूर्ण;

काष्ठा tegra_hsp_db_map अणु
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक master;
	अचिन्हित पूर्णांक index;
पूर्ण;

काष्ठा tegra_hsp_soc अणु
	स्थिर काष्ठा tegra_hsp_db_map *map;
	bool has_per_mb_ie;
पूर्ण;

काष्ठा tegra_hsp अणु
	काष्ठा device *dev;
	स्थिर काष्ठा tegra_hsp_soc *soc;
	काष्ठा mbox_controller mbox_db;
	काष्ठा mbox_controller mbox_sm;
	व्योम __iomem *regs;
	अचिन्हित पूर्णांक करोorbell_irq;
	अचिन्हित पूर्णांक *shared_irqs;
	अचिन्हित पूर्णांक shared_irq;
	अचिन्हित पूर्णांक num_sm;
	अचिन्हित पूर्णांक num_as;
	अचिन्हित पूर्णांक num_ss;
	अचिन्हित पूर्णांक num_db;
	अचिन्हित पूर्णांक num_si;

	spinlock_t lock;
	काष्ठा lock_class_key lock_key;

	काष्ठा list_head करोorbells;
	काष्ठा tegra_hsp_mailbox *mailboxes;

	अचिन्हित दीर्घ mask;
पूर्ण;

अटल अंतरभूत u32 tegra_hsp_पढ़ोl(काष्ठा tegra_hsp *hsp, अचिन्हित पूर्णांक offset)
अणु
	वापस पढ़ोl(hsp->regs + offset);
पूर्ण

अटल अंतरभूत व्योम tegra_hsp_ग_लिखोl(काष्ठा tegra_hsp *hsp, u32 value,
				    अचिन्हित पूर्णांक offset)
अणु
	ग_लिखोl(value, hsp->regs + offset);
पूर्ण

अटल अंतरभूत u32 tegra_hsp_channel_पढ़ोl(काष्ठा tegra_hsp_channel *channel,
					  अचिन्हित पूर्णांक offset)
अणु
	वापस पढ़ोl(channel->regs + offset);
पूर्ण

अटल अंतरभूत व्योम tegra_hsp_channel_ग_लिखोl(काष्ठा tegra_hsp_channel *channel,
					    u32 value, अचिन्हित पूर्णांक offset)
अणु
	ग_लिखोl(value, channel->regs + offset);
पूर्ण

अटल bool tegra_hsp_करोorbell_can_ring(काष्ठा tegra_hsp_करोorbell *db)
अणु
	u32 value;

	value = tegra_hsp_channel_पढ़ोl(&db->channel, HSP_DB_ENABLE);

	वापस (value & BIT(TEGRA_HSP_DB_MASTER_CCPLEX)) != 0;
पूर्ण

अटल काष्ठा tegra_hsp_करोorbell *
__tegra_hsp_करोorbell_get(काष्ठा tegra_hsp *hsp, अचिन्हित पूर्णांक master)
अणु
	काष्ठा tegra_hsp_करोorbell *entry;

	list_क्रम_each_entry(entry, &hsp->करोorbells, list)
		अगर (entry->master == master)
			वापस entry;

	वापस शून्य;
पूर्ण

अटल काष्ठा tegra_hsp_करोorbell *
tegra_hsp_करोorbell_get(काष्ठा tegra_hsp *hsp, अचिन्हित पूर्णांक master)
अणु
	काष्ठा tegra_hsp_करोorbell *db;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&hsp->lock, flags);
	db = __tegra_hsp_करोorbell_get(hsp, master);
	spin_unlock_irqrestore(&hsp->lock, flags);

	वापस db;
पूर्ण

अटल irqवापस_t tegra_hsp_करोorbell_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा tegra_hsp *hsp = data;
	काष्ठा tegra_hsp_करोorbell *db;
	अचिन्हित दीर्घ master, value;

	db = tegra_hsp_करोorbell_get(hsp, TEGRA_HSP_DB_MASTER_CCPLEX);
	अगर (!db)
		वापस IRQ_NONE;

	value = tegra_hsp_channel_पढ़ोl(&db->channel, HSP_DB_PENDING);
	tegra_hsp_channel_ग_लिखोl(&db->channel, value, HSP_DB_PENDING);

	spin_lock(&hsp->lock);

	क्रम_each_set_bit(master, &value, hsp->mbox_db.num_chans) अणु
		काष्ठा tegra_hsp_करोorbell *db;

		db = __tegra_hsp_करोorbell_get(hsp, master);
		/*
		 * Depending on the bootloader chain, the CCPLEX करोorbell will
		 * have some करोorbells enabled, which means that requesting an
		 * पूर्णांकerrupt will immediately fire.
		 *
		 * In that हाल, db->channel.chan will still be शून्य here and
		 * cause a crash अगर not properly guarded.
		 *
		 * It reमुख्यs to be seen अगर ignoring the करोorbell in that हाल
		 * is the correct solution.
		 */
		अगर (db && db->channel.chan)
			mbox_chan_received_data(db->channel.chan, शून्य);
	पूर्ण

	spin_unlock(&hsp->lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t tegra_hsp_shared_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा tegra_hsp *hsp = data;
	अचिन्हित दीर्घ bit, mask;
	u32 status, value;
	व्योम *msg;

	status = tegra_hsp_पढ़ोl(hsp, HSP_INT_IR) & hsp->mask;

	/* process EMPTY पूर्णांकerrupts first */
	mask = (status >> HSP_INT_EMPTY_SHIFT) & HSP_INT_EMPTY_MASK;

	क्रम_each_set_bit(bit, &mask, hsp->num_sm) अणु
		काष्ठा tegra_hsp_mailbox *mb = &hsp->mailboxes[bit];

		अगर (mb->producer) अणु
			/*
			 * Disable EMPTY पूर्णांकerrupts until data is sent with
			 * the next message. These पूर्णांकerrupts are level-
			 * triggered, so अगर we kept them enabled they would
			 * स्थिरantly trigger until we next ग_लिखो data पूर्णांकo
			 * the message.
			 */
			spin_lock(&hsp->lock);

			hsp->mask &= ~BIT(HSP_INT_EMPTY_SHIFT + mb->index);
			tegra_hsp_ग_लिखोl(hsp, hsp->mask,
					 HSP_INT_IE(hsp->shared_irq));

			spin_unlock(&hsp->lock);

			mbox_chan_txकरोne(mb->channel.chan, 0);
		पूर्ण
	पूर्ण

	/* process FULL पूर्णांकerrupts */
	mask = (status >> HSP_INT_FULL_SHIFT) & HSP_INT_FULL_MASK;

	क्रम_each_set_bit(bit, &mask, hsp->num_sm) अणु
		काष्ठा tegra_hsp_mailbox *mb = &hsp->mailboxes[bit];

		अगर (!mb->producer) अणु
			value = tegra_hsp_channel_पढ़ोl(&mb->channel,
							HSP_SM_SHRD_MBOX);
			value &= ~HSP_SM_SHRD_MBOX_FULL;
			msg = (व्योम *)(अचिन्हित दीर्घ)value;
			mbox_chan_received_data(mb->channel.chan, msg);

			/*
			 * Need to clear all bits here since some producers,
			 * such as TCU, depend on fields in the रेजिस्टर
			 * getting cleared by the consumer.
			 *
			 * The mailbox API करोesn't give the consumers a way
			 * of करोing that explicitly, so we have to make sure
			 * we cover all possible हालs.
			 */
			tegra_hsp_channel_ग_लिखोl(&mb->channel, 0x0,
						 HSP_SM_SHRD_MBOX);
		पूर्ण
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल काष्ठा tegra_hsp_channel *
tegra_hsp_करोorbell_create(काष्ठा tegra_hsp *hsp, स्थिर अक्षर *name,
			  अचिन्हित पूर्णांक master, अचिन्हित पूर्णांक index)
अणु
	काष्ठा tegra_hsp_करोorbell *db;
	अचिन्हित पूर्णांक offset;
	अचिन्हित दीर्घ flags;

	db = devm_kzalloc(hsp->dev, माप(*db), GFP_KERNEL);
	अगर (!db)
		वापस ERR_PTR(-ENOMEM);

	offset = (1 + (hsp->num_sm / 2) + hsp->num_ss + hsp->num_as) * SZ_64K;
	offset += index * 0x100;

	db->channel.regs = hsp->regs + offset;
	db->channel.hsp = hsp;

	db->name = devm_kstrdup_स्थिर(hsp->dev, name, GFP_KERNEL);
	db->master = master;
	db->index = index;

	spin_lock_irqsave(&hsp->lock, flags);
	list_add_tail(&db->list, &hsp->करोorbells);
	spin_unlock_irqrestore(&hsp->lock, flags);

	वापस &db->channel;
पूर्ण

अटल पूर्णांक tegra_hsp_करोorbell_send_data(काष्ठा mbox_chan *chan, व्योम *data)
अणु
	काष्ठा tegra_hsp_करोorbell *db = chan->con_priv;

	tegra_hsp_channel_ग_लिखोl(&db->channel, 1, HSP_DB_TRIGGER);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_hsp_करोorbell_startup(काष्ठा mbox_chan *chan)
अणु
	काष्ठा tegra_hsp_करोorbell *db = chan->con_priv;
	काष्ठा tegra_hsp *hsp = db->channel.hsp;
	काष्ठा tegra_hsp_करोorbell *ccplex;
	अचिन्हित दीर्घ flags;
	u32 value;

	अगर (db->master >= chan->mbox->num_chans) अणु
		dev_err(chan->mbox->dev,
			"invalid master ID %u for HSP channel\n",
			db->master);
		वापस -EINVAL;
	पूर्ण

	ccplex = tegra_hsp_करोorbell_get(hsp, TEGRA_HSP_DB_MASTER_CCPLEX);
	अगर (!ccplex)
		वापस -ENODEV;

	/*
	 * On simulation platक्रमms the BPMP hasn't had a chance yet to mark
	 * the करोorbell as ringable by the CCPLEX, so we want to skip extra
	 * checks here.
	 */
	अगर (tegra_is_silicon() && !tegra_hsp_करोorbell_can_ring(db))
		वापस -ENODEV;

	spin_lock_irqsave(&hsp->lock, flags);

	value = tegra_hsp_channel_पढ़ोl(&ccplex->channel, HSP_DB_ENABLE);
	value |= BIT(db->master);
	tegra_hsp_channel_ग_लिखोl(&ccplex->channel, value, HSP_DB_ENABLE);

	spin_unlock_irqrestore(&hsp->lock, flags);

	वापस 0;
पूर्ण

अटल व्योम tegra_hsp_करोorbell_shutकरोwn(काष्ठा mbox_chan *chan)
अणु
	काष्ठा tegra_hsp_करोorbell *db = chan->con_priv;
	काष्ठा tegra_hsp *hsp = db->channel.hsp;
	काष्ठा tegra_hsp_करोorbell *ccplex;
	अचिन्हित दीर्घ flags;
	u32 value;

	ccplex = tegra_hsp_करोorbell_get(hsp, TEGRA_HSP_DB_MASTER_CCPLEX);
	अगर (!ccplex)
		वापस;

	spin_lock_irqsave(&hsp->lock, flags);

	value = tegra_hsp_channel_पढ़ोl(&ccplex->channel, HSP_DB_ENABLE);
	value &= ~BIT(db->master);
	tegra_hsp_channel_ग_लिखोl(&ccplex->channel, value, HSP_DB_ENABLE);

	spin_unlock_irqrestore(&hsp->lock, flags);
पूर्ण

अटल स्थिर काष्ठा mbox_chan_ops tegra_hsp_db_ops = अणु
	.send_data = tegra_hsp_करोorbell_send_data,
	.startup = tegra_hsp_करोorbell_startup,
	.shutकरोwn = tegra_hsp_करोorbell_shutकरोwn,
पूर्ण;

अटल पूर्णांक tegra_hsp_mailbox_send_data(काष्ठा mbox_chan *chan, व्योम *data)
अणु
	काष्ठा tegra_hsp_mailbox *mb = chan->con_priv;
	काष्ठा tegra_hsp *hsp = mb->channel.hsp;
	अचिन्हित दीर्घ flags;
	u32 value;

	अगर (WARN_ON(!mb->producer))
		वापस -EPERM;

	/* copy data and mark mailbox full */
	value = (u32)(अचिन्हित दीर्घ)data;
	value |= HSP_SM_SHRD_MBOX_FULL;

	tegra_hsp_channel_ग_लिखोl(&mb->channel, value, HSP_SM_SHRD_MBOX);

	/* enable EMPTY पूर्णांकerrupt क्रम the shared mailbox */
	spin_lock_irqsave(&hsp->lock, flags);

	hsp->mask |= BIT(HSP_INT_EMPTY_SHIFT + mb->index);
	tegra_hsp_ग_लिखोl(hsp, hsp->mask, HSP_INT_IE(hsp->shared_irq));

	spin_unlock_irqrestore(&hsp->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_hsp_mailbox_flush(काष्ठा mbox_chan *chan,
				   अचिन्हित दीर्घ समयout)
अणु
	काष्ठा tegra_hsp_mailbox *mb = chan->con_priv;
	काष्ठा tegra_hsp_channel *ch = &mb->channel;
	u32 value;

	समयout = jअगरfies + msecs_to_jअगरfies(समयout);

	जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
		value = tegra_hsp_channel_पढ़ोl(ch, HSP_SM_SHRD_MBOX);
		अगर ((value & HSP_SM_SHRD_MBOX_FULL) == 0) अणु
			mbox_chan_txकरोne(chan, 0);
			वापस 0;
		पूर्ण

		udelay(1);
	पूर्ण

	वापस -ETIME;
पूर्ण

अटल पूर्णांक tegra_hsp_mailbox_startup(काष्ठा mbox_chan *chan)
अणु
	काष्ठा tegra_hsp_mailbox *mb = chan->con_priv;
	काष्ठा tegra_hsp_channel *ch = &mb->channel;
	काष्ठा tegra_hsp *hsp = mb->channel.hsp;
	अचिन्हित दीर्घ flags;

	chan->txकरोne_method = TXDONE_BY_IRQ;

	/*
	 * Shared mailboxes start out as consumers by शेष. FULL and EMPTY
	 * पूर्णांकerrupts are coalesced at the same shared पूर्णांकerrupt.
	 *
	 * Keep EMPTY पूर्णांकerrupts disabled at startup and only enable them when
	 * the mailbox is actually full. This is required because the FULL and
	 * EMPTY पूर्णांकerrupts are level-triggered, so keeping EMPTY पूर्णांकerrupts
	 * enabled all the समय would cause an पूर्णांकerrupt storm जबतक mailboxes
	 * are idle.
	 */

	spin_lock_irqsave(&hsp->lock, flags);

	अगर (mb->producer)
		hsp->mask &= ~BIT(HSP_INT_EMPTY_SHIFT + mb->index);
	अन्यथा
		hsp->mask |= BIT(HSP_INT_FULL_SHIFT + mb->index);

	tegra_hsp_ग_लिखोl(hsp, hsp->mask, HSP_INT_IE(hsp->shared_irq));

	spin_unlock_irqrestore(&hsp->lock, flags);

	अगर (hsp->soc->has_per_mb_ie) अणु
		अगर (mb->producer)
			tegra_hsp_channel_ग_लिखोl(ch, 0x0,
						 HSP_SM_SHRD_MBOX_EMPTY_INT_IE);
		अन्यथा
			tegra_hsp_channel_ग_लिखोl(ch, 0x1,
						 HSP_SM_SHRD_MBOX_FULL_INT_IE);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम tegra_hsp_mailbox_shutकरोwn(काष्ठा mbox_chan *chan)
अणु
	काष्ठा tegra_hsp_mailbox *mb = chan->con_priv;
	काष्ठा tegra_hsp_channel *ch = &mb->channel;
	काष्ठा tegra_hsp *hsp = mb->channel.hsp;
	अचिन्हित दीर्घ flags;

	अगर (hsp->soc->has_per_mb_ie) अणु
		अगर (mb->producer)
			tegra_hsp_channel_ग_लिखोl(ch, 0x0,
						 HSP_SM_SHRD_MBOX_EMPTY_INT_IE);
		अन्यथा
			tegra_hsp_channel_ग_लिखोl(ch, 0x0,
						 HSP_SM_SHRD_MBOX_FULL_INT_IE);
	पूर्ण

	spin_lock_irqsave(&hsp->lock, flags);

	अगर (mb->producer)
		hsp->mask &= ~BIT(HSP_INT_EMPTY_SHIFT + mb->index);
	अन्यथा
		hsp->mask &= ~BIT(HSP_INT_FULL_SHIFT + mb->index);

	tegra_hsp_ग_लिखोl(hsp, hsp->mask, HSP_INT_IE(hsp->shared_irq));

	spin_unlock_irqrestore(&hsp->lock, flags);
पूर्ण

अटल स्थिर काष्ठा mbox_chan_ops tegra_hsp_sm_ops = अणु
	.send_data = tegra_hsp_mailbox_send_data,
	.flush = tegra_hsp_mailbox_flush,
	.startup = tegra_hsp_mailbox_startup,
	.shutकरोwn = tegra_hsp_mailbox_shutकरोwn,
पूर्ण;

अटल काष्ठा mbox_chan *tegra_hsp_db_xlate(काष्ठा mbox_controller *mbox,
					    स्थिर काष्ठा of_phandle_args *args)
अणु
	काष्ठा tegra_hsp *hsp = container_of(mbox, काष्ठा tegra_hsp, mbox_db);
	अचिन्हित पूर्णांक type = args->args[0], master = args->args[1];
	काष्ठा tegra_hsp_channel *channel = ERR_PTR(-ENODEV);
	काष्ठा tegra_hsp_करोorbell *db;
	काष्ठा mbox_chan *chan;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक i;

	अगर (type != TEGRA_HSP_MBOX_TYPE_DB || !hsp->करोorbell_irq)
		वापस ERR_PTR(-ENODEV);

	db = tegra_hsp_करोorbell_get(hsp, master);
	अगर (db)
		channel = &db->channel;

	अगर (IS_ERR(channel))
		वापस ERR_CAST(channel);

	spin_lock_irqsave(&hsp->lock, flags);

	क्रम (i = 0; i < mbox->num_chans; i++) अणु
		chan = &mbox->chans[i];
		अगर (!chan->con_priv) अणु
			channel->chan = chan;
			chan->con_priv = db;
			अवरोध;
		पूर्ण

		chan = शून्य;
	पूर्ण

	spin_unlock_irqrestore(&hsp->lock, flags);

	वापस chan ?: ERR_PTR(-EBUSY);
पूर्ण

अटल काष्ठा mbox_chan *tegra_hsp_sm_xlate(काष्ठा mbox_controller *mbox,
					    स्थिर काष्ठा of_phandle_args *args)
अणु
	काष्ठा tegra_hsp *hsp = container_of(mbox, काष्ठा tegra_hsp, mbox_sm);
	अचिन्हित पूर्णांक type = args->args[0], index;
	काष्ठा tegra_hsp_mailbox *mb;

	index = args->args[1] & TEGRA_HSP_SM_MASK;

	अगर (type != TEGRA_HSP_MBOX_TYPE_SM || !hsp->shared_irqs ||
	    index >= hsp->num_sm)
		वापस ERR_PTR(-ENODEV);

	mb = &hsp->mailboxes[index];

	अगर ((args->args[1] & TEGRA_HSP_SM_FLAG_TX) == 0)
		mb->producer = false;
	अन्यथा
		mb->producer = true;

	वापस mb->channel.chan;
पूर्ण

अटल पूर्णांक tegra_hsp_add_करोorbells(काष्ठा tegra_hsp *hsp)
अणु
	स्थिर काष्ठा tegra_hsp_db_map *map = hsp->soc->map;
	काष्ठा tegra_hsp_channel *channel;

	जबतक (map->name) अणु
		channel = tegra_hsp_करोorbell_create(hsp, map->name,
						    map->master, map->index);
		अगर (IS_ERR(channel))
			वापस PTR_ERR(channel);

		map++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_hsp_add_mailboxes(काष्ठा tegra_hsp *hsp, काष्ठा device *dev)
अणु
	पूर्णांक i;

	hsp->mailboxes = devm_kसुस्मृति(dev, hsp->num_sm, माप(*hsp->mailboxes),
				      GFP_KERNEL);
	अगर (!hsp->mailboxes)
		वापस -ENOMEM;

	क्रम (i = 0; i < hsp->num_sm; i++) अणु
		काष्ठा tegra_hsp_mailbox *mb = &hsp->mailboxes[i];

		mb->index = i;

		mb->channel.hsp = hsp;
		mb->channel.regs = hsp->regs + SZ_64K + i * SZ_32K;
		mb->channel.chan = &hsp->mbox_sm.chans[i];
		mb->channel.chan->con_priv = mb;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_hsp_request_shared_irq(काष्ठा tegra_hsp *hsp)
अणु
	अचिन्हित पूर्णांक i, irq = 0;
	पूर्णांक err;

	क्रम (i = 0; i < hsp->num_si; i++) अणु
		irq = hsp->shared_irqs[i];
		अगर (irq <= 0)
			जारी;

		err = devm_request_irq(hsp->dev, irq, tegra_hsp_shared_irq, 0,
				       dev_name(hsp->dev), hsp);
		अगर (err < 0) अणु
			dev_err(hsp->dev, "failed to request interrupt: %d\n",
				err);
			जारी;
		पूर्ण

		hsp->shared_irq = i;

		/* disable all पूर्णांकerrupts */
		tegra_hsp_ग_लिखोl(hsp, 0, HSP_INT_IE(hsp->shared_irq));

		dev_dbg(hsp->dev, "interrupt requested: %u\n", irq);

		अवरोध;
	पूर्ण

	अगर (i == hsp->num_si) अणु
		dev_err(hsp->dev, "failed to find available interrupt\n");
		वापस -ENOENT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_hsp_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tegra_hsp *hsp;
	काष्ठा resource *res;
	अचिन्हित पूर्णांक i;
	u32 value;
	पूर्णांक err;

	hsp = devm_kzalloc(&pdev->dev, माप(*hsp), GFP_KERNEL);
	अगर (!hsp)
		वापस -ENOMEM;

	hsp->dev = &pdev->dev;
	hsp->soc = of_device_get_match_data(&pdev->dev);
	INIT_LIST_HEAD(&hsp->करोorbells);
	spin_lock_init(&hsp->lock);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	hsp->regs = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(hsp->regs))
		वापस PTR_ERR(hsp->regs);

	value = tegra_hsp_पढ़ोl(hsp, HSP_INT_DIMENSIONING);
	hsp->num_sm = (value >> HSP_nSM_SHIFT) & HSP_nINT_MASK;
	hsp->num_ss = (value >> HSP_nSS_SHIFT) & HSP_nINT_MASK;
	hsp->num_as = (value >> HSP_nAS_SHIFT) & HSP_nINT_MASK;
	hsp->num_db = (value >> HSP_nDB_SHIFT) & HSP_nINT_MASK;
	hsp->num_si = (value >> HSP_nSI_SHIFT) & HSP_nINT_MASK;

	err = platक्रमm_get_irq_byname_optional(pdev, "doorbell");
	अगर (err >= 0)
		hsp->करोorbell_irq = err;

	अगर (hsp->num_si > 0) अणु
		अचिन्हित पूर्णांक count = 0;

		hsp->shared_irqs = devm_kसुस्मृति(&pdev->dev, hsp->num_si,
						माप(*hsp->shared_irqs),
						GFP_KERNEL);
		अगर (!hsp->shared_irqs)
			वापस -ENOMEM;

		क्रम (i = 0; i < hsp->num_si; i++) अणु
			अक्षर *name;

			name = kaप्र_लिखो(GFP_KERNEL, "shared%u", i);
			अगर (!name)
				वापस -ENOMEM;

			err = platक्रमm_get_irq_byname_optional(pdev, name);
			अगर (err >= 0) अणु
				hsp->shared_irqs[i] = err;
				count++;
			पूर्ण

			kमुक्त(name);
		पूर्ण

		अगर (count == 0) अणु
			devm_kमुक्त(&pdev->dev, hsp->shared_irqs);
			hsp->shared_irqs = शून्य;
		पूर्ण
	पूर्ण

	/* setup the करोorbell controller */
	hsp->mbox_db.of_xlate = tegra_hsp_db_xlate;
	hsp->mbox_db.num_chans = 32;
	hsp->mbox_db.dev = &pdev->dev;
	hsp->mbox_db.ops = &tegra_hsp_db_ops;

	hsp->mbox_db.chans = devm_kसुस्मृति(&pdev->dev, hsp->mbox_db.num_chans,
					  माप(*hsp->mbox_db.chans),
					  GFP_KERNEL);
	अगर (!hsp->mbox_db.chans)
		वापस -ENOMEM;

	अगर (hsp->करोorbell_irq) अणु
		err = tegra_hsp_add_करोorbells(hsp);
		अगर (err < 0) अणु
			dev_err(&pdev->dev, "failed to add doorbells: %d\n",
			        err);
			वापस err;
		पूर्ण
	पूर्ण

	err = devm_mbox_controller_रेजिस्टर(&pdev->dev, &hsp->mbox_db);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "failed to register doorbell mailbox: %d\n",
			err);
		वापस err;
	पूर्ण

	/* setup the shared mailbox controller */
	hsp->mbox_sm.of_xlate = tegra_hsp_sm_xlate;
	hsp->mbox_sm.num_chans = hsp->num_sm;
	hsp->mbox_sm.dev = &pdev->dev;
	hsp->mbox_sm.ops = &tegra_hsp_sm_ops;

	hsp->mbox_sm.chans = devm_kसुस्मृति(&pdev->dev, hsp->mbox_sm.num_chans,
					  माप(*hsp->mbox_sm.chans),
					  GFP_KERNEL);
	अगर (!hsp->mbox_sm.chans)
		वापस -ENOMEM;

	अगर (hsp->shared_irqs) अणु
		err = tegra_hsp_add_mailboxes(hsp, &pdev->dev);
		अगर (err < 0) अणु
			dev_err(&pdev->dev, "failed to add mailboxes: %d\n",
			        err);
			वापस err;
		पूर्ण
	पूर्ण

	err = devm_mbox_controller_रेजिस्टर(&pdev->dev, &hsp->mbox_sm);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "failed to register shared mailbox: %d\n",
			err);
		वापस err;
	पूर्ण

	platक्रमm_set_drvdata(pdev, hsp);

	अगर (hsp->करोorbell_irq) अणु
		err = devm_request_irq(&pdev->dev, hsp->करोorbell_irq,
				       tegra_hsp_करोorbell_irq, IRQF_NO_SUSPEND,
				       dev_name(&pdev->dev), hsp);
		अगर (err < 0) अणु
			dev_err(&pdev->dev,
			        "failed to request doorbell IRQ#%u: %d\n",
				hsp->करोorbell_irq, err);
			वापस err;
		पूर्ण
	पूर्ण

	अगर (hsp->shared_irqs) अणु
		err = tegra_hsp_request_shared_irq(hsp);
		अगर (err < 0)
			वापस err;
	पूर्ण

	lockdep_रेजिस्टर_key(&hsp->lock_key);
	lockdep_set_class(&hsp->lock, &hsp->lock_key);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_hsp_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tegra_hsp *hsp = platक्रमm_get_drvdata(pdev);

	lockdep_unरेजिस्टर_key(&hsp->lock_key);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused tegra_hsp_resume(काष्ठा device *dev)
अणु
	काष्ठा tegra_hsp *hsp = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक i;
	काष्ठा tegra_hsp_करोorbell *db;

	list_क्रम_each_entry(db, &hsp->करोorbells, list) अणु
		अगर (db && db->channel.chan)
			tegra_hsp_करोorbell_startup(db->channel.chan);
	पूर्ण

	अगर (hsp->mailboxes) अणु
		क्रम (i = 0; i < hsp->num_sm; i++) अणु
			काष्ठा tegra_hsp_mailbox *mb = &hsp->mailboxes[i];

			अगर (mb->channel.chan->cl)
				tegra_hsp_mailbox_startup(mb->channel.chan);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops tegra_hsp_pm_ops = अणु
	.resume_noirq = tegra_hsp_resume,
पूर्ण;

अटल स्थिर काष्ठा tegra_hsp_db_map tegra186_hsp_db_map[] = अणु
	अणु "ccplex", TEGRA_HSP_DB_MASTER_CCPLEX, HSP_DB_CCPLEX, पूर्ण,
	अणु "bpmp",   TEGRA_HSP_DB_MASTER_BPMP,   HSP_DB_BPMP,   पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल स्थिर काष्ठा tegra_hsp_soc tegra186_hsp_soc = अणु
	.map = tegra186_hsp_db_map,
	.has_per_mb_ie = false,
पूर्ण;

अटल स्थिर काष्ठा tegra_hsp_soc tegra194_hsp_soc = अणु
	.map = tegra186_hsp_db_map,
	.has_per_mb_ie = true,
पूर्ण;

अटल स्थिर काष्ठा of_device_id tegra_hsp_match[] = अणु
	अणु .compatible = "nvidia,tegra186-hsp", .data = &tegra186_hsp_soc पूर्ण,
	अणु .compatible = "nvidia,tegra194-hsp", .data = &tegra194_hsp_soc पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver tegra_hsp_driver = अणु
	.driver = अणु
		.name = "tegra-hsp",
		.of_match_table = tegra_hsp_match,
		.pm = &tegra_hsp_pm_ops,
	पूर्ण,
	.probe = tegra_hsp_probe,
	.हटाओ = tegra_hsp_हटाओ,
पूर्ण;

अटल पूर्णांक __init tegra_hsp_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&tegra_hsp_driver);
पूर्ण
core_initcall(tegra_hsp_init);
