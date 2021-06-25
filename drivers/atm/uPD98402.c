<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* drivers/aपंचांग/uPD98402.c - NEC uPD98402 (PHY) declarations */
 
/* Written 1995-2000 by Werner Almesberger, EPFL LRC/ICA */
 

#समावेश <linux/module.h>
#समावेश <linux/mm.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/aपंचांगdev.h>
#समावेश <linux/sonet.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/atomic.h>

#समावेश "uPD98402.h"


#अगर 0
#घोषणा DPRINTK(क्रमmat,args...) prपूर्णांकk(KERN_DEBUG क्रमmat,##args)
#अन्यथा
#घोषणा DPRINTK(क्रमmat,args...)
#पूर्ण_अगर


काष्ठा uPD98402_priv अणु
	काष्ठा k_sonet_stats sonet_stats;/* link diagnostics */
	अचिन्हित अक्षर framing;		/* SONET/SDH framing */
	पूर्णांक loop_mode;			/* loopback mode */
	spinlock_t lock;
पूर्ण;


#घोषणा PRIV(dev) ((काष्ठा uPD98402_priv *) dev->phy_data)

#घोषणा PUT(val,reg) dev->ops->phy_put(dev,val,uPD98402_##reg)
#घोषणा GET(reg) dev->ops->phy_get(dev,uPD98402_##reg)


अटल पूर्णांक fetch_stats(काष्ठा aपंचांग_dev *dev,काष्ठा sonet_stats __user *arg,पूर्णांक zero)
अणु
	काष्ठा sonet_stats पंचांगp;
 	पूर्णांक error = 0;

	atomic_add(GET(HECCT),&PRIV(dev)->sonet_stats.uncorr_hcs);
	sonet_copy_stats(&PRIV(dev)->sonet_stats,&पंचांगp);
	अगर (arg) error = copy_to_user(arg,&पंचांगp,माप(पंचांगp));
	अगर (zero && !error) अणु
		/* unused fields are reported as -1, but we must not "adjust"
		   them */
		पंचांगp.corr_hcs = पंचांगp.tx_cells = पंचांगp.rx_cells = 0;
		sonet_subtract_stats(&PRIV(dev)->sonet_stats,&पंचांगp);
	पूर्ण
	वापस error ? -EFAULT : 0;
पूर्ण


अटल पूर्णांक set_framing(काष्ठा aपंचांग_dev *dev,अचिन्हित अक्षर framing)
अणु
	अटल स्थिर अचिन्हित अक्षर sonet[] = अणु 1,2,3,0 पूर्ण;
	अटल स्थिर अचिन्हित अक्षर sdh[] = अणु 1,0,0,2 पूर्ण;
	स्थिर अक्षर *set;
	अचिन्हित दीर्घ flags;
 
	चयन (framing) अणु
		हाल SONET_FRAME_SONET:
			set = sonet;
			अवरोध;
		हाल SONET_FRAME_SDH:
			set = sdh;
			अवरोध;
		शेष:
			वापस -EINVAL;
	पूर्ण
	spin_lock_irqsave(&PRIV(dev)->lock, flags);
	PUT(set[0],C11T);
	PUT(set[1],C12T);
	PUT(set[2],C13T);
	PUT((GET(MDR) & ~uPD98402_MDR_SS_MASK) | (set[3] <<
	    uPD98402_MDR_SS_SHIFT),MDR);
	spin_unlock_irqrestore(&PRIV(dev)->lock, flags);
	वापस 0;
पूर्ण


अटल पूर्णांक get_sense(काष्ठा aपंचांग_dev *dev,u8 __user *arg)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर s[3];

	spin_lock_irqsave(&PRIV(dev)->lock, flags);
	s[0] = GET(C11R);
	s[1] = GET(C12R);
	s[2] = GET(C13R);
	spin_unlock_irqrestore(&PRIV(dev)->lock, flags);
	वापस (put_user(s[0], arg) || put_user(s[1], arg+1) ||
	    put_user(s[2], arg+2) || put_user(0xff, arg+3) ||
	    put_user(0xff, arg+4) || put_user(0xff, arg+5)) ? -EFAULT : 0;
पूर्ण


अटल पूर्णांक set_loopback(काष्ठा aपंचांग_dev *dev,पूर्णांक mode)
अणु
	अचिन्हित अक्षर mode_reg;

	mode_reg = GET(MDR) & ~(uPD98402_MDR_TPLP | uPD98402_MDR_ALP |
	    uPD98402_MDR_RPLP);
	चयन (__ATM_LM_XTLOC(mode)) अणु
		हाल __ATM_LM_NONE:
			अवरोध;
		हाल __ATM_LM_PHY:
			mode_reg |= uPD98402_MDR_TPLP;
			अवरोध;
		हाल __ATM_LM_ATM:
			mode_reg |= uPD98402_MDR_ALP;
			अवरोध;
		शेष:
			वापस -EINVAL;
	पूर्ण
	चयन (__ATM_LM_XTRMT(mode)) अणु
		हाल __ATM_LM_NONE:
			अवरोध;
		हाल __ATM_LM_PHY:
			mode_reg |= uPD98402_MDR_RPLP;
			अवरोध;
		शेष:
			वापस -EINVAL;
	पूर्ण
	PUT(mode_reg,MDR);
	PRIV(dev)->loop_mode = mode;
	वापस 0;
पूर्ण


अटल पूर्णांक uPD98402_ioctl(काष्ठा aपंचांग_dev *dev,अचिन्हित पूर्णांक cmd,व्योम __user *arg)
अणु
	चयन (cmd) अणु

		हाल SONET_GETSTATZ:
                हाल SONET_GETSTAT:
			वापस fetch_stats(dev,arg, cmd == SONET_GETSTATZ);
		हाल SONET_SETFRAMING:
			वापस set_framing(dev, (पूर्णांक)(अचिन्हित दीर्घ)arg);
		हाल SONET_GETFRAMING:
			वापस put_user(PRIV(dev)->framing,(पूर्णांक __user *)arg) ?
			    -EFAULT : 0;
		हाल SONET_GETFRSENSE:
			वापस get_sense(dev,arg);
		हाल ATM_SETLOOP:
			वापस set_loopback(dev, (पूर्णांक)(अचिन्हित दीर्घ)arg);
		हाल ATM_GETLOOP:
			वापस put_user(PRIV(dev)->loop_mode,(पूर्णांक __user *)arg) ?
			    -EFAULT : 0;
		हाल ATM_QUERYLOOP:
			वापस put_user(ATM_LM_LOC_PHY | ATM_LM_LOC_ATM |
			    ATM_LM_RMT_PHY,(पूर्णांक __user *)arg) ? -EFAULT : 0;
		शेष:
			वापस -ENOIOCTLCMD;
	पूर्ण
पूर्ण


#घोषणा ADD_LIMITED(s,v) \
    अणु atomic_add(GET(v),&PRIV(dev)->sonet_stats.s); \
    अगर (atomic_पढ़ो(&PRIV(dev)->sonet_stats.s) < 0) \
	atomic_set(&PRIV(dev)->sonet_stats.s,पूर्णांक_उच्च); पूर्ण


अटल व्योम stat_event(काष्ठा aपंचांग_dev *dev)
अणु
	अचिन्हित अक्षर events;

	events = GET(PCR);
	अगर (events & uPD98402_PFM_PFEB) ADD_LIMITED(path_febe,PFECB);
	अगर (events & uPD98402_PFM_LFEB) ADD_LIMITED(line_febe,LECCT);
	अगर (events & uPD98402_PFM_B3E) ADD_LIMITED(path_bip,B3ECT);
	अगर (events & uPD98402_PFM_B2E) ADD_LIMITED(line_bip,B2ECT);
	अगर (events & uPD98402_PFM_B1E) ADD_LIMITED(section_bip,B1ECT);
पूर्ण


#अघोषित ADD_LIMITED


अटल व्योम uPD98402_पूर्णांक(काष्ठा aपंचांग_dev *dev)
अणु
	अटल अचिन्हित दीर्घ silence = 0;
	अचिन्हित अक्षर reason;

	जबतक ((reason = GET(PICR))) अणु
		अगर (reason & uPD98402_INT_LOS)
			prपूर्णांकk(KERN_NOTICE "%s(itf %d): signal lost\n",
			    dev->type,dev->number);
		अगर (reason & uPD98402_INT_PFM) stat_event(dev);
		अगर (reason & uPD98402_INT_PCO) अणु
			(व्योम) GET(PCOCR); /* clear पूर्णांकerrupt cause */
			atomic_add(GET(HECCT),
			    &PRIV(dev)->sonet_stats.uncorr_hcs);
		पूर्ण
		अगर ((reason & uPD98402_INT_RFO) && 
		    (समय_after(jअगरfies, silence) || silence == 0)) अणु
			prपूर्णांकk(KERN_WARNING "%s(itf %d): uPD98402 receive "
			    "FIFO overflow\n",dev->type,dev->number);
			silence = (jअगरfies+HZ/2)|1;
		पूर्ण
	पूर्ण
पूर्ण


अटल पूर्णांक uPD98402_start(काष्ठा aपंचांग_dev *dev)
अणु
	DPRINTK("phy_start\n");
	अगर (!(dev->phy_data = kदो_स्मृति(माप(काष्ठा uPD98402_priv),GFP_KERNEL)))
		वापस -ENOMEM;
	spin_lock_init(&PRIV(dev)->lock);
	स_रखो(&PRIV(dev)->sonet_stats,0,माप(काष्ठा k_sonet_stats));
	(व्योम) GET(PCR); /* clear perक्रमmance events */
	PUT(uPD98402_PFM_FJ,PCMR); /* ignore frequency adj */
	(व्योम) GET(PCOCR); /* clear overflows */
	PUT(~uPD98402_PCO_HECC,PCOMR);
	(व्योम) GET(PICR); /* clear पूर्णांकerrupts */
	PUT(~(uPD98402_INT_PFM | uPD98402_INT_ALM | uPD98402_INT_RFO |
	  uPD98402_INT_LOS),PIMR); /* enable them */
	(व्योम) fetch_stats(dev,शून्य,1); /* clear kernel counters */
	atomic_set(&PRIV(dev)->sonet_stats.corr_hcs,-1);
	atomic_set(&PRIV(dev)->sonet_stats.tx_cells,-1);
	atomic_set(&PRIV(dev)->sonet_stats.rx_cells,-1);
	वापस 0;
पूर्ण


अटल पूर्णांक uPD98402_stop(काष्ठा aपंचांग_dev *dev)
अणु
	/* let SAR driver worry about stopping पूर्णांकerrupts */
	kमुक्त(PRIV(dev));
	वापस 0;
पूर्ण


अटल स्थिर काष्ठा aपंचांगphy_ops uPD98402_ops = अणु
	.start		= uPD98402_start,
	.ioctl		= uPD98402_ioctl,
	.पूर्णांकerrupt	= uPD98402_पूर्णांक,
	.stop		= uPD98402_stop,
पूर्ण;


पूर्णांक uPD98402_init(काष्ठा aपंचांग_dev *dev)
अणु
DPRINTK("phy_init\n");
	dev->phy = &uPD98402_ops;
	वापस 0;
पूर्ण


MODULE_LICENSE("GPL");

EXPORT_SYMBOL(uPD98402_init);

अटल __init पूर्णांक uPD98402_module_init(व्योम)
अणु
	वापस 0;
पूर्ण
module_init(uPD98402_module_init);
/* module_निकास not defined so not unloadable */
