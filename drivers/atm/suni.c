<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * drivers/aपंचांग/suni.c - S/UNI PHY driver
 *
 * Supports the following:
 * 	PMC PM5346 S/UNI LITE
 * 	PMC PM5350 S/UNI 155 ULTRA
 * 	PMC PM5355 S/UNI 622
 */
 
/* Written 1995-2000 by Werner Almesberger, EPFL LRC/ICA */

#समावेश <linux/module.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/aपंचांगdev.h>
#समावेश <linux/sonet.h>
#समावेश <linux/delay.h>
#समावेश <linux/समयr.h>
#समावेश <linux/init.h>
#समावेश <linux/capability.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/param.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/atomic.h>

#समावेश "suni.h"


#अगर 0
#घोषणा DPRINTK(क्रमmat,args...) prपूर्णांकk(KERN_DEBUG क्रमmat,##args)
#अन्यथा
#घोषणा DPRINTK(क्रमmat,args...)
#पूर्ण_अगर

#घोषणा PRIV(dev) ((काष्ठा suni_priv *) dev->phy_data)

#घोषणा PUT(val,reg) dev->ops->phy_put(dev,val,SUNI_##reg)
#घोषणा GET(reg) dev->ops->phy_get(dev,SUNI_##reg)
#घोषणा REG_CHANGE(mask,shअगरt,value,reg) \
  PUT((GET(reg) & ~(mask)) | ((value) << (shअगरt)),reg)


अटल काष्ठा समयr_list poll_समयr;
अटल काष्ठा suni_priv *sunis = शून्य;
अटल DEFINE_SPINLOCK(sunis_lock);


#घोषणा ADD_LIMITED(s,v) \
    atomic_add((v),&stats->s); \
    अगर (atomic_पढ़ो(&stats->s) < 0) atomic_set(&stats->s,पूर्णांक_उच्च);


अटल व्योम suni_hz(काष्ठा समयr_list *समयr)
अणु
	काष्ठा suni_priv *walk;
	काष्ठा aपंचांग_dev *dev;
	काष्ठा k_sonet_stats *stats;

	क्रम (walk = sunis; walk; walk = walk->next) अणु
		dev = walk->dev;
		stats = &walk->sonet_stats;
		PUT(0,MRI); /* latch counters */
		udelay(1);
		ADD_LIMITED(section_bip,(GET(RSOP_SBL) & 0xff) |
		    ((GET(RSOP_SBM) & 0xff) << 8));
		ADD_LIMITED(line_bip,(GET(RLOP_LBL) & 0xff) |
		    ((GET(RLOP_LB) & 0xff) << 8) |
		    ((GET(RLOP_LBM) & 0xf) << 16));
		ADD_LIMITED(path_bip,(GET(RPOP_PBL) & 0xff) |
		    ((GET(RPOP_PBM) & 0xff) << 8));
		ADD_LIMITED(line_febe,(GET(RLOP_LFL) & 0xff) |
		    ((GET(RLOP_LF) & 0xff) << 8) |
		    ((GET(RLOP_LFM) & 0xf) << 16));
		ADD_LIMITED(path_febe,(GET(RPOP_PFL) & 0xff) |
		    ((GET(RPOP_PFM) & 0xff) << 8));
		ADD_LIMITED(corr_hcs,GET(RACP_CHEC) & 0xff);
		ADD_LIMITED(uncorr_hcs,GET(RACP_UHEC) & 0xff);
		ADD_LIMITED(rx_cells,(GET(RACP_RCCL) & 0xff) |
		    ((GET(RACP_RCC) & 0xff) << 8) |
		    ((GET(RACP_RCCM) & 7) << 16));
		ADD_LIMITED(tx_cells,(GET(TACP_TCCL) & 0xff) |
		    ((GET(TACP_TCC) & 0xff) << 8) |
		    ((GET(TACP_TCCM) & 7) << 16));
	पूर्ण
	अगर (समयr) mod_समयr(&poll_समयr,jअगरfies+HZ);
पूर्ण


#अघोषित ADD_LIMITED


अटल पूर्णांक fetch_stats(काष्ठा aपंचांग_dev *dev,काष्ठा sonet_stats __user *arg,पूर्णांक zero)
अणु
	काष्ठा sonet_stats पंचांगp;
	पूर्णांक error = 0;

	sonet_copy_stats(&PRIV(dev)->sonet_stats,&पंचांगp);
	अगर (arg) error = copy_to_user(arg,&पंचांगp,माप(पंचांगp));
	अगर (zero && !error) sonet_subtract_stats(&PRIV(dev)->sonet_stats,&पंचांगp);
	वापस error ? -EFAULT : 0;
पूर्ण


#घोषणा HANDLE_FLAG(flag,reg,bit) \
  अगर (toकरो & flag) अणु \
    अगर (set) PUT(GET(reg) | bit,reg); \
    अन्यथा PUT(GET(reg) & ~bit,reg); \
    toकरो &= ~flag; \
  पूर्ण


अटल पूर्णांक change_diag(काष्ठा aपंचांग_dev *dev,व्योम __user *arg,पूर्णांक set)
अणु
	पूर्णांक toकरो;

	अगर (get_user(toकरो,(पूर्णांक __user *)arg)) वापस -EFAULT;
	HANDLE_FLAG(SONET_INS_SBIP,TSOP_DIAG,SUNI_TSOP_DIAG_DBIP8);
	HANDLE_FLAG(SONET_INS_LBIP,TLOP_DIAG,SUNI_TLOP_DIAG_DBIP);
	HANDLE_FLAG(SONET_INS_PBIP,TPOP_CD,SUNI_TPOP_DIAG_DB3);
	HANDLE_FLAG(SONET_INS_FRAME,RSOP_CIE,SUNI_RSOP_CIE_FOOF);
	HANDLE_FLAG(SONET_INS_LAIS,TSOP_CTRL,SUNI_TSOP_CTRL_LAIS);
	HANDLE_FLAG(SONET_INS_PAIS,TPOP_CD,SUNI_TPOP_DIAG_PAIS);
	HANDLE_FLAG(SONET_INS_LOS,TSOP_DIAG,SUNI_TSOP_DIAG_DLOS);
	HANDLE_FLAG(SONET_INS_HCS,TACP_CS,SUNI_TACP_CS_DHCS);
	वापस put_user(toकरो,(पूर्णांक __user *)arg) ? -EFAULT : 0;
पूर्ण


#अघोषित HANDLE_FLAG


अटल पूर्णांक get_diag(काष्ठा aपंचांग_dev *dev,व्योम __user *arg)
अणु
	पूर्णांक set;

	set = 0;
	अगर (GET(TSOP_DIAG) & SUNI_TSOP_DIAG_DBIP8) set |= SONET_INS_SBIP;
	अगर (GET(TLOP_DIAG) & SUNI_TLOP_DIAG_DBIP) set |= SONET_INS_LBIP;
	अगर (GET(TPOP_CD) & SUNI_TPOP_DIAG_DB3) set |= SONET_INS_PBIP;
	/* SONET_INS_FRAME is one-shot only */
	अगर (GET(TSOP_CTRL) & SUNI_TSOP_CTRL_LAIS) set |= SONET_INS_LAIS;
	अगर (GET(TPOP_CD) & SUNI_TPOP_DIAG_PAIS) set |= SONET_INS_PAIS;
	अगर (GET(TSOP_DIAG) & SUNI_TSOP_DIAG_DLOS) set |= SONET_INS_LOS;
	अगर (GET(TACP_CS) & SUNI_TACP_CS_DHCS) set |= SONET_INS_HCS;
	वापस put_user(set,(पूर्णांक __user *)arg) ? -EFAULT : 0;
पूर्ण


अटल पूर्णांक set_loopback(काष्ठा aपंचांग_dev *dev,पूर्णांक mode)
अणु
	अचिन्हित अक्षर control;
	पूर्णांक reg, dle, lle;

	अगर (PRIV(dev)->type == SUNI_MRI_TYPE_PM5355) अणु
		reg = SUNI_MCM;
		dle = SUNI_MCM_DLE;
		lle = SUNI_MCM_LLE;
	पूर्ण अन्यथा अणु
		reg = SUNI_MCT;
		dle = SUNI_MCT_DLE;
		lle = SUNI_MCT_LLE;
	पूर्ण

	control = dev->ops->phy_get(dev, reg) & ~(dle | lle);
	चयन (mode) अणु
		हाल ATM_LM_NONE:
			अवरोध;
		हाल ATM_LM_LOC_PHY:
			control |= dle;
			अवरोध;
		हाल ATM_LM_RMT_PHY:
			control |= lle;
			अवरोध;
		शेष:
			वापस -EINVAL;
	पूर्ण
	dev->ops->phy_put(dev, control, reg);
	PRIV(dev)->loop_mode = mode;
	वापस 0;
पूर्ण

/*
 * SONET vs. SDH Configuration
 *
 * Z0INS (रेजिस्टर 0x06): 0 क्रम SONET, 1 क्रम SDH
 * ENSS (रेजिस्टर 0x3D): 0 क्रम SONET, 1 क्रम SDH
 * LEN16 (रेजिस्टर 0x28): 0 क्रम SONET, 1 क्रम SDH (n/a क्रम S/UNI 155 QUAD)
 * LEN16 (रेजिस्टर 0x50): 0 क्रम SONET, 1 क्रम SDH (n/a क्रम S/UNI 155 QUAD)
 * S[1:0] (रेजिस्टर 0x46): 00 क्रम SONET, 10 क्रम SDH
 */

अटल पूर्णांक set_sonet(काष्ठा aपंचांग_dev *dev)
अणु
	अगर (PRIV(dev)->type == SUNI_MRI_TYPE_PM5355) अणु
		PUT(GET(RPOP_RC) & ~SUNI_RPOP_RC_ENSS, RPOP_RC);
		PUT(GET(SSTB_CTRL) & ~SUNI_SSTB_CTRL_LEN16, SSTB_CTRL);
		PUT(GET(SPTB_CTRL) & ~SUNI_SPTB_CTRL_LEN16, SPTB_CTRL);
	पूर्ण

	REG_CHANGE(SUNI_TPOP_APM_S, SUNI_TPOP_APM_S_SHIFT,
		   SUNI_TPOP_S_SONET, TPOP_APM);

	वापस 0;
पूर्ण

अटल पूर्णांक set_sdh(काष्ठा aपंचांग_dev *dev)
अणु
	अगर (PRIV(dev)->type == SUNI_MRI_TYPE_PM5355) अणु
		PUT(GET(RPOP_RC) | SUNI_RPOP_RC_ENSS, RPOP_RC);
		PUT(GET(SSTB_CTRL) | SUNI_SSTB_CTRL_LEN16, SSTB_CTRL);
		PUT(GET(SPTB_CTRL) | SUNI_SPTB_CTRL_LEN16, SPTB_CTRL);
	पूर्ण

	REG_CHANGE(SUNI_TPOP_APM_S, SUNI_TPOP_APM_S_SHIFT,
		   SUNI_TPOP_S_SDH, TPOP_APM);

	वापस 0;
पूर्ण


अटल पूर्णांक get_framing(काष्ठा aपंचांग_dev *dev, व्योम __user *arg)
अणु
	पूर्णांक framing;
	अचिन्हित अक्षर s;


	s = (GET(TPOP_APM) & SUNI_TPOP_APM_S) >> SUNI_TPOP_APM_S_SHIFT;
	अगर (s == SUNI_TPOP_S_SONET)
		framing = SONET_FRAME_SONET;
	अन्यथा
		framing = SONET_FRAME_SDH;

	वापस put_user(framing, (पूर्णांक __user *) arg) ? -EFAULT : 0;
पूर्ण

अटल पूर्णांक set_framing(काष्ठा aपंचांग_dev *dev, व्योम __user *arg)
अणु
	पूर्णांक mode;

	अगर (get_user(mode, (पूर्णांक __user *) arg))
		वापस -EFAULT;

	अगर (mode == SONET_FRAME_SONET)
		वापस set_sonet(dev);
	अन्यथा अगर (mode == SONET_FRAME_SDH)
		वापस set_sdh(dev);

	वापस -EINVAL;
पूर्ण


अटल पूर्णांक suni_ioctl(काष्ठा aपंचांग_dev *dev,अचिन्हित पूर्णांक cmd,व्योम __user *arg)
अणु
	चयन (cmd) अणु
		हाल SONET_GETSTATZ:
		हाल SONET_GETSTAT:
			वापस fetch_stats(dev, arg, cmd == SONET_GETSTATZ);
		हाल SONET_SETDIAG:
			वापस change_diag(dev,arg,1);
		हाल SONET_CLRDIAG:
			वापस change_diag(dev,arg,0);
		हाल SONET_GETDIAG:
			वापस get_diag(dev,arg);
		हाल SONET_SETFRAMING:
			अगर (!capable(CAP_NET_ADMIN))
				वापस -EPERM;
			वापस set_framing(dev, arg);
		हाल SONET_GETFRAMING:
			वापस get_framing(dev, arg);
		हाल SONET_GETFRSENSE:
			वापस -EINVAL;
		हाल ATM_SETLOOP:
			अगर (!capable(CAP_NET_ADMIN))
				वापस -EPERM;
			वापस set_loopback(dev,(पूर्णांक)(अचिन्हित दीर्घ)arg);
		हाल ATM_GETLOOP:
			वापस put_user(PRIV(dev)->loop_mode,(पूर्णांक __user *)arg) ?
			    -EFAULT : 0;
		हाल ATM_QUERYLOOP:
			वापस put_user(ATM_LM_LOC_PHY | ATM_LM_RMT_PHY,
			    (पूर्णांक __user *) arg) ? -EFAULT : 0;
		शेष:
			वापस -ENOIOCTLCMD;
	पूर्ण
पूर्ण


अटल व्योम poll_los(काष्ठा aपंचांग_dev *dev)
अणु
	aपंचांग_dev_संकेत_change(dev,
		GET(RSOP_SIS) & SUNI_RSOP_SIS_LOSV ?
		ATM_PHY_SIG_LOST : ATM_PHY_SIG_FOUND);
पूर्ण


अटल व्योम suni_पूर्णांक(काष्ठा aपंचांग_dev *dev)
अणु
	poll_los(dev);
	prपूर्णांकk(KERN_NOTICE "%s(itf %d): signal %s\n",dev->type,dev->number,
	    dev->संकेत == ATM_PHY_SIG_LOST ?  "lost" : "detected again");
पूर्ण


अटल पूर्णांक suni_start(काष्ठा aपंचांग_dev *dev)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक first;

	spin_lock_irqsave(&sunis_lock,flags);
	first = !sunis;
	PRIV(dev)->next = sunis;
	sunis = PRIV(dev);
	spin_unlock_irqrestore(&sunis_lock,flags);
	स_रखो(&PRIV(dev)->sonet_stats,0,माप(काष्ठा k_sonet_stats));
	PUT(GET(RSOP_CIE) | SUNI_RSOP_CIE_LOSE,RSOP_CIE);
		/* पूर्णांकerrupt on loss of संकेत */
	poll_los(dev); /* ... and clear SUNI पूर्णांकerrupts */
	अगर (dev->संकेत == ATM_PHY_SIG_LOST)
		prपूर्णांकk(KERN_WARNING "%s(itf %d): no signal\n",dev->type,
		    dev->number);
	PRIV(dev)->loop_mode = ATM_LM_NONE;
	suni_hz(शून्य); /* clear SUNI counters */
	(व्योम) fetch_stats(dev,शून्य,1); /* clear kernel counters */
	अगर (first) अणु
		समयr_setup(&poll_समयr, suni_hz, 0);
		poll_समयr.expires = jअगरfies+HZ;
#अगर 0
prपूर्णांकk(KERN_DEBUG "[u] p=0x%lx,n=0x%lx\n",(अचिन्हित दीर्घ) poll_समयr.list.prev,
    (अचिन्हित दीर्घ) poll_समयr.list.next);
#पूर्ण_अगर
		add_समयr(&poll_समयr);
	पूर्ण
	वापस 0;
पूर्ण


अटल पूर्णांक suni_stop(काष्ठा aपंचांग_dev *dev)
अणु
	काष्ठा suni_priv **walk;
	अचिन्हित दीर्घ flags;

	/* let SAR driver worry about stopping पूर्णांकerrupts */
	spin_lock_irqsave(&sunis_lock,flags);
	क्रम (walk = &sunis; *walk != PRIV(dev);
	    walk = &PRIV((*walk)->dev)->next);
	*walk = PRIV((*walk)->dev)->next;
	अगर (!sunis) del_समयr_sync(&poll_समयr);
	spin_unlock_irqrestore(&sunis_lock,flags);
	kमुक्त(PRIV(dev));

	वापस 0;
पूर्ण


अटल स्थिर काष्ठा aपंचांगphy_ops suni_ops = अणु
	.start		= suni_start,
	.ioctl		= suni_ioctl,
	.पूर्णांकerrupt	= suni_पूर्णांक,
	.stop		= suni_stop,
पूर्ण;


पूर्णांक suni_init(काष्ठा aपंचांग_dev *dev)
अणु
	अचिन्हित अक्षर mri;

	अगर (!(dev->phy_data = kदो_स्मृति(माप(काष्ठा suni_priv),GFP_KERNEL)))
		वापस -ENOMEM;
	PRIV(dev)->dev = dev;

	mri = GET(MRI); /* reset SUNI */
	PRIV(dev)->type = (mri & SUNI_MRI_TYPE) >> SUNI_MRI_TYPE_SHIFT;
	PUT(mri | SUNI_MRI_RESET,MRI);
	PUT(mri,MRI);
	PUT((GET(MT) & SUNI_MT_DS27_53),MT); /* disable all tests */
        set_sonet(dev);
	REG_CHANGE(SUNI_TACP_IUCHP_CLP,0,SUNI_TACP_IUCHP_CLP,
	    TACP_IUCHP); /* idle cells */
	PUT(SUNI_IDLE_PATTERN,TACP_IUCPOP);
	dev->phy = &suni_ops;

	वापस 0;
पूर्ण

EXPORT_SYMBOL(suni_init);

MODULE_LICENSE("GPL");
