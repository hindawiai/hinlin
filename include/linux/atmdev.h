<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* aपंचांगdev.h - ATM device driver declarations and various related items */
#अगर_अघोषित LINUX_ATMDEV_H
#घोषणा LINUX_ATMDEV_H


#समावेश <linux/रुको.h> /* रुको_queue_head_t */
#समावेश <linux/समय.स> /* काष्ठा समयval */
#समावेश <linux/net.h>
#समावेश <linux/bug.h>
#समावेश <linux/skbuff.h> /* काष्ठा sk_buff */
#समावेश <linux/uपन.स>
#समावेश <net/sock.h>
#समावेश <linux/atomic.h>
#समावेश <linux/refcount.h>
#समावेश <uapi/linux/aपंचांगdev.h>

#अगर_घोषित CONFIG_PROC_FS
#समावेश <linux/proc_fs.h>

बाह्य काष्ठा proc_dir_entry *aपंचांग_proc_root;
#पूर्ण_अगर

#अगर_घोषित CONFIG_COMPAT
#समावेश <linux/compat.h>
काष्ठा compat_aपंचांग_iobuf अणु
	पूर्णांक length;
	compat_uptr_t buffer;
पूर्ण;
#पूर्ण_अगर

काष्ठा k_aपंचांग_aal_stats अणु
#घोषणा __HANDLE_ITEM(i) atomic_t i
	__AAL_STAT_ITEMS
#अघोषित __HANDLE_ITEM
पूर्ण;


काष्ठा k_aपंचांग_dev_stats अणु
	काष्ठा k_aपंचांग_aal_stats aal0;
	काष्ठा k_aपंचांग_aal_stats aal34;
	काष्ठा k_aपंचांग_aal_stats aal5;
पूर्ण;

काष्ठा device;

क्रमागत अणु
	ATM_VF_ADDR,		/* Address is in use. Set by anybody, cleared
				   by device driver. */
	ATM_VF_READY,		/* VC is पढ़ोy to transfer data. Set by device
				   driver, cleared by anybody. */
	ATM_VF_PARTIAL,		/* resources are bound to PVC (partial PVC
				   setup), controlled by socket layer */
	ATM_VF_REGIS,		/* रेजिस्टरed with demon, controlled by SVC
				   socket layer */
	ATM_VF_BOUND,		/* local SAP is set, controlled by SVC socket
				   layer */
	ATM_VF_RELEASED,	/* demon has indicated/requested release,
				   controlled by SVC socket layer */
	ATM_VF_HASQOS,		/* QOS parameters have been set */
	ATM_VF_LISTEN,		/* socket is used क्रम listening */
	ATM_VF_META,		/* SVC socket isn't used क्रम normal data
				   traffic and करोesn't depend on संकेतing
				   to be available */
	ATM_VF_SESSION,		/* VCC is p2mp session control descriptor */
	ATM_VF_HASSAP,		/* SAP has been set */
	ATM_VF_CLOSE,		/* asynchronous बंद - treat like VF_RELEASED*/
	ATM_VF_WAITING,		/* रुकोing क्रम reply from sigd */
	ATM_VF_IS_CLIP,		/* in use by CLIP protocol */
पूर्ण;


#घोषणा ATM_VF2VS(flags) \
    (test_bit(ATM_VF_READY,&(flags)) ? ATM_VS_CONNECTED : \
     test_bit(ATM_VF_RELEASED,&(flags)) ? ATM_VS_CLOSING : \
     test_bit(ATM_VF_LISTEN,&(flags)) ? ATM_VS_LISTEN : \
     test_bit(ATM_VF_REGIS,&(flags)) ? ATM_VS_INUSE : \
     test_bit(ATM_VF_BOUND,&(flags)) ? ATM_VS_BOUND : ATM_VS_IDLE)


क्रमागत अणु
	ATM_DF_REMOVED,		/* device was हटाओd from aपंचांग_devs list */
पूर्ण;


#घोषणा ATM_PHY_SIG_LOST    0	/* no carrier/light */
#घोषणा ATM_PHY_SIG_UNKNOWN 1	/* carrier/light status is unknown */
#घोषणा ATM_PHY_SIG_FOUND   2	/* carrier/light okay */

#घोषणा ATM_ATMOPT_CLP	1	/* set CLP bit */

काष्ठा aपंचांग_vcc अणु
	/* काष्ठा sock has to be the first member of aपंचांग_vcc */
	काष्ठा sock	sk;
	अचिन्हित दीर्घ	flags;		/* VCC flags (ATM_VF_*) */
	लघु		vpi;		/* VPI and VCI (types must be equal */
					/* with sockaddr) */
	पूर्णांक 		vci;
	अचिन्हित दीर्घ	aal_options;	/* AAL layer options */
	अचिन्हित दीर्घ	aपंचांग_options;	/* ATM layer options */
	काष्ठा aपंचांग_dev	*dev;		/* device back poपूर्णांकer */
	काष्ठा aपंचांग_qos	qos;		/* QOS */
	काष्ठा aपंचांग_sap	sap;		/* SAP */
	व्योम (*release_cb)(काष्ठा aपंचांग_vcc *vcc); /* release_sock callback */
	व्योम (*push)(काष्ठा aपंचांग_vcc *vcc,काष्ठा sk_buff *skb);
	व्योम (*pop)(काष्ठा aपंचांग_vcc *vcc,काष्ठा sk_buff *skb); /* optional */
	पूर्णांक (*push_oam)(काष्ठा aपंचांग_vcc *vcc,व्योम *cell);
	पूर्णांक (*send)(काष्ठा aपंचांग_vcc *vcc,काष्ठा sk_buff *skb);
	व्योम		*dev_data;	/* per-device data */
	व्योम		*proto_data;	/* per-protocol data */
	काष्ठा k_aपंचांग_aal_stats *stats;	/* poपूर्णांकer to AAL stats group */
	काष्ठा module *owner;		/* owner of ->push function */
	/* SVC part --- may move later ------------------------------------- */
	लघु		itf;		/* पूर्णांकerface number */
	काष्ठा sockaddr_aपंचांगsvc local;
	काष्ठा sockaddr_aपंचांगsvc remote;
	/* Multipoपूर्णांक part ------------------------------------------------- */
	काष्ठा aपंचांग_vcc	*session;	/* session VCC descriptor */
	/* Other stuff ----------------------------------------------------- */
	व्योम		*user_back;	/* user backlink - not touched by */
					/* native ATM stack. Currently used */
					/* by CLIP and sch_aपंचांग. */
पूर्ण;

अटल अंतरभूत काष्ठा aपंचांग_vcc *aपंचांग_sk(काष्ठा sock *sk)
अणु
	वापस (काष्ठा aपंचांग_vcc *)sk;
पूर्ण

अटल अंतरभूत काष्ठा aपंचांग_vcc *ATM_SD(काष्ठा socket *sock)
अणु
	वापस aपंचांग_sk(sock->sk);
पूर्ण

अटल अंतरभूत काष्ठा sock *sk_aपंचांग(काष्ठा aपंचांग_vcc *vcc)
अणु
	वापस (काष्ठा sock *)vcc;
पूर्ण

काष्ठा aपंचांग_dev_addr अणु
	काष्ठा sockaddr_aपंचांगsvc addr;	/* ATM address */
	काष्ठा list_head entry;		/* next address */
पूर्ण;

क्रमागत aपंचांग_addr_type_t अणु ATM_ADDR_LOCAL, ATM_ADDR_LECS पूर्ण;

काष्ठा aपंचांग_dev अणु
	स्थिर काष्ठा aपंचांगdev_ops *ops;	/* device operations; शून्य अगर unused */
	स्थिर काष्ठा aपंचांगphy_ops *phy;	/* PHY operations, may be undefined */
					/* (शून्य) */
	स्थिर अक्षर	*type;		/* device type name */
	पूर्णांक		number;		/* device index */
	व्योम		*dev_data;	/* per-device data */
	व्योम		*phy_data;	/* निजी PHY data */
	अचिन्हित दीर्घ	flags;		/* device flags (ATM_DF_*) */
	काष्ठा list_head local;		/* local ATM addresses */
	काष्ठा list_head lecs;		/* LECS ATM addresses learned via ILMI */
	अचिन्हित अक्षर	esi[ESI_LEN];	/* ESI ("MAC" addr) */
	काष्ठा aपंचांग_cirange ci_range;	/* VPI/VCI range */
	काष्ठा k_aपंचांग_dev_stats stats;	/* statistics */
	अक्षर		संकेत;		/* संकेत status (ATM_PHY_SIG_*) */
	पूर्णांक		link_rate;	/* link rate (शेष: OC3) */
	refcount_t	refcnt;		/* reference count */
	spinlock_t	lock;		/* protect पूर्णांकernal members */
#अगर_घोषित CONFIG_PROC_FS
	काष्ठा proc_dir_entry *proc_entry; /* proc entry */
	अक्षर *proc_name;		/* proc entry name */
#पूर्ण_अगर
	काष्ठा device class_dev;	/* sysfs device */
	काष्ठा list_head dev_list;	/* linkage */
पूर्ण;

 
/* OF: send_Oam Flags */

#घोषणा ATM_OF_IMMED  1		/* Attempt immediate delivery */
#घोषणा ATM_OF_INRATE 2		/* Attempt in-rate delivery */

काष्ठा aपंचांगdev_ops अणु /* only send is required */
	व्योम (*dev_बंद)(काष्ठा aपंचांग_dev *dev);
	पूर्णांक (*खोलो)(काष्ठा aपंचांग_vcc *vcc);
	व्योम (*बंद)(काष्ठा aपंचांग_vcc *vcc);
	पूर्णांक (*ioctl)(काष्ठा aपंचांग_dev *dev,अचिन्हित पूर्णांक cmd,व्योम __user *arg);
#अगर_घोषित CONFIG_COMPAT
	पूर्णांक (*compat_ioctl)(काष्ठा aपंचांग_dev *dev,अचिन्हित पूर्णांक cmd,
			    व्योम __user *arg);
#पूर्ण_अगर
	पूर्णांक (*send)(काष्ठा aपंचांग_vcc *vcc,काष्ठा sk_buff *skb);
	पूर्णांक (*send_bh)(काष्ठा aपंचांग_vcc *vcc, काष्ठा sk_buff *skb);
	पूर्णांक (*send_oam)(काष्ठा aपंचांग_vcc *vcc,व्योम *cell,पूर्णांक flags);
	व्योम (*phy_put)(काष्ठा aपंचांग_dev *dev,अचिन्हित अक्षर value,
	    अचिन्हित दीर्घ addr);
	अचिन्हित अक्षर (*phy_get)(काष्ठा aपंचांग_dev *dev,अचिन्हित दीर्घ addr);
	पूर्णांक (*change_qos)(काष्ठा aपंचांग_vcc *vcc,काष्ठा aपंचांग_qos *qos,पूर्णांक flags);
	पूर्णांक (*proc_पढ़ो)(काष्ठा aपंचांग_dev *dev,loff_t *pos,अक्षर *page);
	काष्ठा module *owner;
पूर्ण;

काष्ठा aपंचांगphy_ops अणु
	पूर्णांक (*start)(काष्ठा aपंचांग_dev *dev);
	पूर्णांक (*ioctl)(काष्ठा aपंचांग_dev *dev,अचिन्हित पूर्णांक cmd,व्योम __user *arg);
	व्योम (*पूर्णांकerrupt)(काष्ठा aपंचांग_dev *dev);
	पूर्णांक (*stop)(काष्ठा aपंचांग_dev *dev);
पूर्ण;

काष्ठा aपंचांग_skb_data अणु
	काष्ठा aपंचांग_vcc	*vcc;		/* ATM VCC */
	अचिन्हित दीर्घ	aपंचांग_options;	/* ATM layer options */
	अचिन्हित पूर्णांक	acct_truesize;  /* truesize accounted to vcc */
पूर्ण __packed;

#घोषणा VCC_HTABLE_SIZE 32

बाह्य काष्ठा hlist_head vcc_hash[VCC_HTABLE_SIZE];
बाह्य rwlock_t vcc_sklist_lock;

#घोषणा ATM_SKB(skb) (((काष्ठा aपंचांग_skb_data *) (skb)->cb))

काष्ठा aपंचांग_dev *aपंचांग_dev_रेजिस्टर(स्थिर अक्षर *type, काष्ठा device *parent,
				 स्थिर काष्ठा aपंचांगdev_ops *ops,
				 पूर्णांक number, /* -1 == pick first available */
				 अचिन्हित दीर्घ *flags);
काष्ठा aपंचांग_dev *aपंचांग_dev_lookup(पूर्णांक number);
व्योम aपंचांग_dev_deरेजिस्टर(काष्ठा aपंचांग_dev *dev);

/* aपंचांग_dev_संकेत_change
 *
 * Propagate lower layer संकेत change in aपंचांग_dev->संकेत to netdevice.
 * The event will be sent via a notअगरier call chain.
 */
व्योम aपंचांग_dev_संकेत_change(काष्ठा aपंचांग_dev *dev, अक्षर संकेत);

व्योम vcc_insert_socket(काष्ठा sock *sk);

व्योम aपंचांग_dev_release_vccs(काष्ठा aपंचांग_dev *dev);

अटल अंतरभूत व्योम aपंचांग_account_tx(काष्ठा aपंचांग_vcc *vcc, काष्ठा sk_buff *skb)
अणु
	/*
	 * Because ATM skbs may not beदीर्घ to a sock (and we करोn't
	 * necessarily want to), skb->truesize may be adjusted,
	 * escaping the hack in pskb_expand_head() which aव्योमs
	 * करोing so क्रम some हालs. So stash the value of truesize
	 * at the समय we accounted it, and aपंचांग_pop_raw() can use
	 * that value later, in हाल it changes.
	 */
	refcount_add(skb->truesize, &sk_aपंचांग(vcc)->sk_wmem_alloc);
	ATM_SKB(skb)->acct_truesize = skb->truesize;
	ATM_SKB(skb)->aपंचांग_options = vcc->aपंचांग_options;
पूर्ण

अटल अंतरभूत व्योम aपंचांग_क्रमce_अक्षरge(काष्ठा aपंचांग_vcc *vcc,पूर्णांक truesize)
अणु
	atomic_add(truesize, &sk_aपंचांग(vcc)->sk_rmem_alloc);
पूर्ण


अटल अंतरभूत व्योम aपंचांग_वापस(काष्ठा aपंचांग_vcc *vcc,पूर्णांक truesize)
अणु
	atomic_sub(truesize, &sk_aपंचांग(vcc)->sk_rmem_alloc);
पूर्ण


अटल अंतरभूत पूर्णांक aपंचांग_may_send(काष्ठा aपंचांग_vcc *vcc,अचिन्हित पूर्णांक size)
अणु
	वापस (size + refcount_पढ़ो(&sk_aपंचांग(vcc)->sk_wmem_alloc)) <
	       sk_aपंचांग(vcc)->sk_sndbuf;
पूर्ण


अटल अंतरभूत व्योम aपंचांग_dev_hold(काष्ठा aपंचांग_dev *dev)
अणु
	refcount_inc(&dev->refcnt);
पूर्ण


अटल अंतरभूत व्योम aपंचांग_dev_put(काष्ठा aपंचांग_dev *dev)
अणु
	अगर (refcount_dec_and_test(&dev->refcnt)) अणु
		BUG_ON(!test_bit(ATM_DF_REMOVED, &dev->flags));
		अगर (dev->ops->dev_बंद)
			dev->ops->dev_बंद(dev);
		put_device(&dev->class_dev);
	पूर्ण
पूर्ण


पूर्णांक aपंचांग_अक्षरge(काष्ठा aपंचांग_vcc *vcc,पूर्णांक truesize);
काष्ठा sk_buff *aपंचांग_alloc_अक्षरge(काष्ठा aपंचांग_vcc *vcc,पूर्णांक pdu_size,
    gfp_t gfp_flags);
पूर्णांक aपंचांग_pcr_goal(स्थिर काष्ठा aपंचांग_trafprm *tp);

व्योम vcc_release_async(काष्ठा aपंचांग_vcc *vcc, पूर्णांक reply);

काष्ठा aपंचांग_ioctl अणु
	काष्ठा module *owner;
	/* A module reference is kept अगर appropriate over this call.
	 * Return -ENOIOCTLCMD अगर you करोn't handle it. */
	पूर्णांक (*ioctl)(काष्ठा socket *, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);
	काष्ठा list_head list;
पूर्ण;

/**
 * रेजिस्टर_aपंचांग_ioctl - रेजिस्टर handler क्रम ioctl operations
 *
 * Special (non-device) handlers of ioctl's should
 * रेजिस्टर here. If you're a normal device, you should
 * set .ioctl in your aपंचांगdev_ops instead.
 */
व्योम रेजिस्टर_aपंचांग_ioctl(काष्ठा aपंचांग_ioctl *);

/**
 * deरेजिस्टर_aपंचांग_ioctl - हटाओ the ioctl handler
 */
व्योम deरेजिस्टर_aपंचांग_ioctl(काष्ठा aपंचांग_ioctl *);


/* रेजिस्टर_aपंचांगdevice_notअगरier - रेजिस्टर aपंचांग_dev notअगरy events
 *
 * Clients like br2684 will रेजिस्टर notअगरy events
 * Currently we notअगरy of संकेत found/lost
 */
पूर्णांक रेजिस्टर_aपंचांगdevice_notअगरier(काष्ठा notअगरier_block *nb);
व्योम unरेजिस्टर_aपंचांगdevice_notअगरier(काष्ठा notअगरier_block *nb);

#पूर्ण_अगर
