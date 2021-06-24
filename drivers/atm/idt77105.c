<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* drivers/aपंचांग/idt77105.c - IDT77105 (PHY) driver */
 
/* Written 1999 by Greg Banks, NEC Australia <gnb@linuxfan.com>. Based on suni.c */


#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/aपंचांगdev.h>
#समावेश <linux/sonet.h>
#समावेश <linux/delay.h>
#समावेश <linux/समयr.h>
#समावेश <linux/init.h>
#समावेश <linux/capability.h>
#समावेश <linux/aपंचांग_idt77105.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/param.h>
#समावेश <linux/uaccess.h>

#समावेश "idt77105.h"

#अघोषित GENERAL_DEBUG

#अगर_घोषित GENERAL_DEBUG
#घोषणा DPRINTK(क्रमmat,args...) prपूर्णांकk(KERN_DEBUG क्रमmat,##args)
#अन्यथा
#घोषणा DPRINTK(क्रमmat,args...)
#पूर्ण_अगर


काष्ठा idt77105_priv अणु
	काष्ठा idt77105_stats stats;    /* link diagnostics */
	काष्ठा aपंचांग_dev *dev;		/* device back-poपूर्णांकer */
	काष्ठा idt77105_priv *next;
        पूर्णांक loop_mode;
        अचिन्हित अक्षर old_mcr;          /* storage of MCR reg जबतक संकेत lost */
पूर्ण;

अटल DEFINE_SPINLOCK(idt77105_priv_lock);

#घोषणा PRIV(dev) ((काष्ठा idt77105_priv *) dev->phy_data)

#घोषणा PUT(val,reg) dev->ops->phy_put(dev,val,IDT77105_##reg)
#घोषणा GET(reg) dev->ops->phy_get(dev,IDT77105_##reg)

अटल व्योम idt77105_stats_समयr_func(काष्ठा समयr_list *);
अटल व्योम idt77105_restart_समयr_func(काष्ठा समयr_list *);


अटल DEFINE_TIMER(stats_समयr, idt77105_stats_समयr_func);
अटल DEFINE_TIMER(restart_समयr, idt77105_restart_समयr_func);
अटल पूर्णांक start_समयr = 1;
अटल काष्ठा idt77105_priv *idt77105_all = शून्य;

/*
 * Retrieve the value of one of the IDT77105's counters.
 * `counter' is one of the IDT77105_CTRSEL_* स्थिरants.
 */
अटल u16 get_counter(काष्ठा aपंचांग_dev *dev, पूर्णांक counter)
अणु
        u16 val;
        
        /* ग_लिखो the counter bit पूर्णांकo PHY रेजिस्टर 6 */
        PUT(counter, CTRSEL);
        /* पढ़ो the low 8 bits from रेजिस्टर 4 */
        val = GET(CTRLO);
        /* पढ़ो the high 8 bits from रेजिस्टर 5 */
        val |= GET(CTRHI)<<8;
        
        वापस val;
पूर्ण

/*
 * Timer function called every second to gather statistics
 * from the 77105. This is करोne because the h/w रेजिस्टरs
 * will overflow अगर not पढ़ो at least once per second. The
 * kernel's stats are much higher precision. Also, having
 * a separate copy of the stats allows implementation of
 * an ioctl which gathers the stats *without* zero'ing them.
 */
अटल व्योम idt77105_stats_समयr_func(काष्ठा समयr_list *unused)
अणु
	काष्ठा idt77105_priv *walk;
	काष्ठा aपंचांग_dev *dev;
	काष्ठा idt77105_stats *stats;

        DPRINTK("IDT77105 gathering statistics\n");
	क्रम (walk = idt77105_all; walk; walk = walk->next) अणु
		dev = walk->dev;
                
		stats = &walk->stats;
                stats->symbol_errors += get_counter(dev, IDT77105_CTRSEL_SEC);
                stats->tx_cells += get_counter(dev, IDT77105_CTRSEL_TCC);
                stats->rx_cells += get_counter(dev, IDT77105_CTRSEL_RCC);
                stats->rx_hec_errors += get_counter(dev, IDT77105_CTRSEL_RHEC);
	पूर्ण
        अगर (!start_समयr) mod_समयr(&stats_समयr,jअगरfies+IDT77105_STATS_TIMER_PERIOD);
पूर्ण


/*
 * A separate समयr func which handles restarting PHY chips which
 * have had the cable re-inserted after being pulled out. This is
 * करोne by polling the Good Signal Bit in the Interrupt Status
 * रेजिस्टर every 5 seconds. The other technique (checking Good
 * Signal Bit in the पूर्णांकerrupt handler) cannot be used because PHY
 * पूर्णांकerrupts need to be disabled when the cable is pulled out
 * to aव्योम lots of spurious cell error पूर्णांकerrupts.
 */
अटल व्योम idt77105_restart_समयr_func(काष्ठा समयr_list *unused)
अणु
	काष्ठा idt77105_priv *walk;
	काष्ठा aपंचांग_dev *dev;
        अचिन्हित अक्षर istat;

        DPRINTK("IDT77105 checking for cable re-insertion\n");
	क्रम (walk = idt77105_all; walk; walk = walk->next) अणु
		dev = walk->dev;
                
                अगर (dev->संकेत != ATM_PHY_SIG_LOST)
                    जारी;
                    
                istat = GET(ISTAT); /* side effect: clears all पूर्णांकerrupt status bits */
                अगर (istat & IDT77105_ISTAT_GOODSIG) अणु
                    /* Found संकेत again */
                    aपंचांग_dev_संकेत_change(dev, ATM_PHY_SIG_FOUND);
	            prपूर्णांकk(KERN_NOTICE "%s(itf %d): signal detected again\n",
                        dev->type,dev->number);
                    /* flush the receive FIFO */
                    PUT( GET(DIAG) | IDT77105_DIAG_RFLUSH, DIAG);
                    /* re-enable पूर्णांकerrupts */
	            PUT( walk->old_mcr ,MCR);
                पूर्ण
	पूर्ण
        अगर (!start_समयr) mod_समयr(&restart_समयr,jअगरfies+IDT77105_RESTART_TIMER_PERIOD);
पूर्ण


अटल पूर्णांक fetch_stats(काष्ठा aपंचांग_dev *dev,काष्ठा idt77105_stats __user *arg,पूर्णांक zero)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा idt77105_stats stats;

	spin_lock_irqsave(&idt77105_priv_lock, flags);
	स_नकल(&stats, &PRIV(dev)->stats, माप(काष्ठा idt77105_stats));
	अगर (zero)
		स_रखो(&PRIV(dev)->stats, 0, माप(काष्ठा idt77105_stats));
	spin_unlock_irqrestore(&idt77105_priv_lock, flags);
	अगर (arg == शून्य)
		वापस 0;
	वापस copy_to_user(arg, &stats,
		    माप(काष्ठा idt77105_stats)) ? -EFAULT : 0;
पूर्ण


अटल पूर्णांक set_loopback(काष्ठा aपंचांग_dev *dev,पूर्णांक mode)
अणु
	पूर्णांक diag;

	diag = GET(DIAG) & ~IDT77105_DIAG_LCMASK;
	चयन (mode) अणु
		हाल ATM_LM_NONE:
			अवरोध;
		हाल ATM_LM_LOC_ATM:
			diag |= IDT77105_DIAG_LC_PHY_LOOPBACK;
			अवरोध;
		हाल ATM_LM_RMT_ATM:
			diag |= IDT77105_DIAG_LC_LINE_LOOPBACK;
			अवरोध;
		शेष:
			वापस -EINVAL;
	पूर्ण
	PUT(diag,DIAG);
	prपूर्णांकk(KERN_NOTICE "%s(%d) Loopback mode is: %s\n", dev->type,
	    dev->number,
	    (mode == ATM_LM_NONE ? "NONE" : 
	      (mode == ATM_LM_LOC_ATM ? "DIAG (local)" :
		(mode == IDT77105_DIAG_LC_LINE_LOOPBACK ? "LOOP (remote)" :
		  "unknown")))
		    );
	PRIV(dev)->loop_mode = mode;
	वापस 0;
पूर्ण


अटल पूर्णांक idt77105_ioctl(काष्ठा aपंचांग_dev *dev,अचिन्हित पूर्णांक cmd,व्योम __user *arg)
अणु
        prपूर्णांकk(KERN_NOTICE "%s(%d) idt77105_ioctl() called\n",dev->type,dev->number);
	चयन (cmd) अणु
		हाल IDT77105_GETSTATZ:
			अगर (!capable(CAP_NET_ADMIN)) वापस -EPERM;
			fallthrough;
		हाल IDT77105_GETSTAT:
			वापस fetch_stats(dev, arg, cmd == IDT77105_GETSTATZ);
		हाल ATM_SETLOOP:
			वापस set_loopback(dev,(पूर्णांक)(अचिन्हित दीर्घ) arg);
		हाल ATM_GETLOOP:
			वापस put_user(PRIV(dev)->loop_mode,(पूर्णांक __user *)arg) ?
			    -EFAULT : 0;
		हाल ATM_QUERYLOOP:
			वापस put_user(ATM_LM_LOC_ATM | ATM_LM_RMT_ATM,
			    (पूर्णांक __user *) arg) ? -EFAULT : 0;
		शेष:
			वापस -ENOIOCTLCMD;
	पूर्ण
पूर्ण



अटल व्योम idt77105_पूर्णांक(काष्ठा aपंचांग_dev *dev)
अणु
        अचिन्हित अक्षर istat;
        
        istat = GET(ISTAT); /* side effect: clears all पूर्णांकerrupt status bits */
     
        DPRINTK("IDT77105 generated an interrupt, istat=%02x\n", (अचिन्हित)istat);
                
        अगर (istat & IDT77105_ISTAT_RSCC) अणु
            /* Rx Signal Condition Change - line went up or करोwn */
            अगर (istat & IDT77105_ISTAT_GOODSIG) अणु   /* संकेत detected again */
                /* This should not happen (restart समयr करोes it) but JIC */
		aपंचांग_dev_संकेत_change(dev, ATM_PHY_SIG_FOUND);
            पूर्ण अन्यथा अणु    /* संकेत lost */
                /*
                 * Disable पूर्णांकerrupts and stop all transmission and
                 * reception - the restart समयr will restore these.
                 */
                PRIV(dev)->old_mcr = GET(MCR);
	        PUT(
                    (PRIV(dev)->old_mcr|
                    IDT77105_MCR_DREC|
                    IDT77105_MCR_DRIC|
                    IDT77105_MCR_HALTTX
                    ) & ~IDT77105_MCR_EIP, MCR);
		aपंचांग_dev_संकेत_change(dev, ATM_PHY_SIG_LOST);
	        prपूर्णांकk(KERN_NOTICE "%s(itf %d): signal lost\n",
                    dev->type,dev->number);
            पूर्ण
        पूर्ण
        
        अगर (istat & IDT77105_ISTAT_RFO) अणु
            /* Rx FIFO Overrun -- perक्रमm a FIFO flush */
            PUT( GET(DIAG) | IDT77105_DIAG_RFLUSH, DIAG);
	    prपूर्णांकk(KERN_NOTICE "%s(itf %d): receive FIFO overrun\n",
                dev->type,dev->number);
        पूर्ण
#अगर_घोषित GENERAL_DEBUG
        अगर (istat & (IDT77105_ISTAT_HECERR | IDT77105_ISTAT_SCR |
                     IDT77105_ISTAT_RSE)) अणु
            /* normally करोn't care - just report in stats */
	    prपूर्णांकk(KERN_NOTICE "%s(itf %d): received cell with error\n",
                dev->type,dev->number);
        पूर्ण
#पूर्ण_अगर
पूर्ण


अटल पूर्णांक idt77105_start(काष्ठा aपंचांग_dev *dev)
अणु
	अचिन्हित दीर्घ flags;

	अगर (!(dev->phy_data = kदो_स्मृति(माप(काष्ठा idt77105_priv),GFP_KERNEL)))
		वापस -ENOMEM;
	PRIV(dev)->dev = dev;
	spin_lock_irqsave(&idt77105_priv_lock, flags);
	PRIV(dev)->next = idt77105_all;
	idt77105_all = PRIV(dev);
	spin_unlock_irqrestore(&idt77105_priv_lock, flags);
	स_रखो(&PRIV(dev)->stats,0,माप(काष्ठा idt77105_stats));
        
        /* initialise dev->संकेत from Good Signal Bit */
	aपंचांग_dev_संकेत_change(dev,
		GET(ISTAT) & IDT77105_ISTAT_GOODSIG ?
		ATM_PHY_SIG_FOUND : ATM_PHY_SIG_LOST);
	अगर (dev->संकेत == ATM_PHY_SIG_LOST)
		prपूर्णांकk(KERN_WARNING "%s(itf %d): no signal\n",dev->type,
		    dev->number);

        /* initialise loop mode from hardware */
        चयन ( GET(DIAG) & IDT77105_DIAG_LCMASK ) अणु
        हाल IDT77105_DIAG_LC_NORMAL:
            PRIV(dev)->loop_mode = ATM_LM_NONE;
            अवरोध;
        हाल IDT77105_DIAG_LC_PHY_LOOPBACK:
            PRIV(dev)->loop_mode = ATM_LM_LOC_ATM;
            अवरोध;
        हाल IDT77105_DIAG_LC_LINE_LOOPBACK:
            PRIV(dev)->loop_mode = ATM_LM_RMT_ATM;
            अवरोध;
        पूर्ण
        
        /* enable पूर्णांकerrupts, e.g. on loss of संकेत */
        PRIV(dev)->old_mcr = GET(MCR);
        अगर (dev->संकेत == ATM_PHY_SIG_FOUND) अणु
            PRIV(dev)->old_mcr |= IDT77105_MCR_EIP;
	    PUT(PRIV(dev)->old_mcr, MCR);
        पूर्ण

                    
	idt77105_stats_समयr_func(0); /* clear 77105 counters */
	(व्योम) fetch_stats(dev,शून्य,1); /* clear kernel counters */
        
	spin_lock_irqsave(&idt77105_priv_lock, flags);
	अगर (start_समयr) अणु
		start_समयr = 0;
                
		stats_समयr.expires = jअगरfies+IDT77105_STATS_TIMER_PERIOD;
		add_समयr(&stats_समयr);
                
		restart_समयr.expires = jअगरfies+IDT77105_RESTART_TIMER_PERIOD;
		add_समयr(&restart_समयr);
	पूर्ण
	spin_unlock_irqrestore(&idt77105_priv_lock, flags);
	वापस 0;
पूर्ण


अटल पूर्णांक idt77105_stop(काष्ठा aपंचांग_dev *dev)
अणु
	काष्ठा idt77105_priv *walk, *prev;

        DPRINTK("%s(itf %d): stopping IDT77105\n",dev->type,dev->number);
        
        /* disable पूर्णांकerrupts */
	PUT( GET(MCR) & ~IDT77105_MCR_EIP, MCR );
        
        /* detach निजी काष्ठा from aपंचांग_dev & मुक्त */
	क्रम (prev = शून्य, walk = idt77105_all ;
             walk != शून्य;
             prev = walk, walk = walk->next) अणु
            अगर (walk->dev == dev) अणु
                अगर (prev != शून्य)
                    prev->next = walk->next;
                अन्यथा
                    idt77105_all = walk->next;
	        dev->phy = शून्य;
                dev->phy_data = शून्य;
                kमुक्त(walk);
                अवरोध;
            पूर्ण
        पूर्ण

	वापस 0;
पूर्ण


अटल स्थिर काष्ठा aपंचांगphy_ops idt77105_ops = अणु
	.start = 	idt77105_start,
	.ioctl =	idt77105_ioctl,
	.पूर्णांकerrupt =	idt77105_पूर्णांक,
	.stop =		idt77105_stop,
पूर्ण;


पूर्णांक idt77105_init(काष्ठा aपंचांग_dev *dev)
अणु
	dev->phy = &idt77105_ops;
	वापस 0;
पूर्ण

EXPORT_SYMBOL(idt77105_init);

अटल व्योम __निकास idt77105_निकास(व्योम)
अणु
	/* turn off समयrs */
	del_समयr_sync(&stats_समयr);
	del_समयr_sync(&restart_समयr);
पूर्ण

module_निकास(idt77105_निकास);

MODULE_LICENSE("GPL");
