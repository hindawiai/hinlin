<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _NET_DN_DEV_H
#घोषणा _NET_DN_DEV_H


काष्ठा dn_dev;

काष्ठा dn_अगरaddr अणु
	काष्ठा dn_अगरaddr __rcu *अगरa_next;
	काष्ठा dn_dev    *अगरa_dev;
	__le16            अगरa_local;
	__le16            अगरa_address;
	__u32             अगरa_flags;
	__u8              अगरa_scope;
	अक्षर              अगरa_label[IFNAMSIZ];
	काष्ठा rcu_head   rcu;
पूर्ण;

#घोषणा DN_DEV_S_RU  0 /* Run - working normally   */
#घोषणा DN_DEV_S_CR  1 /* Circuit Rejected         */
#घोषणा DN_DEV_S_DS  2 /* Data Link Start          */
#घोषणा DN_DEV_S_RI  3 /* Routing Layer Initialize */
#घोषणा DN_DEV_S_RV  4 /* Routing Layer Verअगरy     */
#घोषणा DN_DEV_S_RC  5 /* Routing Layer Complete   */
#घोषणा DN_DEV_S_OF  6 /* Off                      */
#घोषणा DN_DEV_S_HA  7 /* Halt                     */


/*
 * The dn_dev_parms काष्ठाure contains the set of parameters
 * क्रम each device (hence inclusion in the dn_dev काष्ठाure)
 * and an array is used to store the शेष types of supported
 * device (in dn_dev.c).
 *
 * The type field matches the ARPHRD_ स्थिरants and is used in
 * searching the list क्रम supported devices when new devices
 * come up.
 *
 * The mode field is used to find out अगर a device is broadcast,
 * multipoपूर्णांक, or poपूर्णांकopoपूर्णांक. Please note that DECnet thinks
 * dअगरferent ways about devices to the rest of the kernel
 * so the normal IFF_xxx flags are invalid here. For devices
 * which can be any combination of the previously mentioned
 * attributes, you can set this on a per device basis by
 * installing an up() routine.
 *
 * The device state field, defines the initial state in which the
 * device will come up. In the dn_dev काष्ठाure, it is the actual
 * state.
 *
 * Things have changed here. I've killed timer1 since it's a user space
 * issue क्रम a user space routing deamon to sort out. The kernel करोes
 * not need to be bothered with it.
 *
 * Timers:
 * t2 - Rate limit समयr, min समय between routing and hello messages
 * t3 - Hello समयr, send hello messages when it expires
 *
 * Callbacks:
 * up() - Called to initialize device, वापस value can veto use of
 *        device with DECnet.
 * करोwn() - Called to turn device off when it goes करोwn
 * समयr3() - Called once क्रम each अगरaddr when समयr 3 goes off
 * 
 * sysctl - Hook क्रम sysctl things
 *
 */
काष्ठा dn_dev_parms अणु
	पूर्णांक type;	          /* ARPHRD_xxx                         */
	पूर्णांक mode;	          /* Broadcast, Unicast, Mulitpoपूर्णांक     */
#घोषणा DN_DEV_BCAST  1
#घोषणा DN_DEV_UCAST  2
#घोषणा DN_DEV_MPOINT 4
	पूर्णांक state;                /* Initial state                      */
	पूर्णांक क्रमwarding;	          /* 0=EndNode, 1=L1Router, 2=L2Router  */
	अचिन्हित दीर्घ t2;         /* Default value of t2                */
	अचिन्हित दीर्घ t3;         /* Default value of t3                */
	पूर्णांक priority;             /* Priority to be a router            */
	अक्षर *name;               /* Name क्रम sysctl                    */
	पूर्णांक  (*up)(काष्ठा net_device *);
	व्योम (*करोwn)(काष्ठा net_device *);
	व्योम (*समयr3)(काष्ठा net_device *, काष्ठा dn_अगरaddr *अगरa);
	व्योम *sysctl;
पूर्ण;


काष्ठा dn_dev अणु
	काष्ठा dn_अगरaddr __rcu *अगरa_list;
	काष्ठा net_device *dev;
	काष्ठा dn_dev_parms parms;
	अक्षर use_दीर्घ;
	काष्ठा समयr_list समयr;
	अचिन्हित दीर्घ t3;
	काष्ठा neigh_parms *neigh_parms;
	__u8 addr[ETH_ALEN];
	काष्ठा neighbour *router; /* Default router on circuit */
	काष्ठा neighbour *peer;   /* Peer on poपूर्णांकopoपूर्णांक links */
	अचिन्हित दीर्घ upसमय;     /* Time device went up in jअगरfies */
पूर्ण;

काष्ठा dn_लघु_packet अणु
	__u8    msgflg;
	__le16 dstnode;
	__le16 srcnode;
	__u8   क्रमward;
पूर्ण __packed;

काष्ठा dn_दीर्घ_packet अणु
	__u8   msgflg;
	__u8   d_area;
	__u8   d_subarea;
	__u8   d_id[6];
	__u8   s_area;
	__u8   s_subarea;
	__u8   s_id[6];
	__u8   nl2;
	__u8   visit_ct;
	__u8   s_class;
	__u8   pt;
पूर्ण __packed;

/*------------------------- DRP - Routing messages ---------------------*/

काष्ठा endnode_hello_message अणु
	__u8   msgflg;
	__u8   tiver[3];
	__u8   id[6];
	__u8   iinfo;
	__le16 blksize;
	__u8   area;
	__u8   seed[8];
	__u8   neighbor[6];
	__le16 समयr;
	__u8   mpd;
	__u8   datalen;
	__u8   data[2];
पूर्ण __packed;

काष्ठा rtnode_hello_message अणु
	__u8   msgflg;
	__u8   tiver[3];
	__u8   id[6];
	__u8   iinfo;
	__le16  blksize;
	__u8   priority;
	__u8   area;
	__le16  समयr;
	__u8   mpd;
पूर्ण __packed;


व्योम dn_dev_init(व्योम);
व्योम dn_dev_cleanup(व्योम);

पूर्णांक dn_dev_ioctl(अचिन्हित पूर्णांक cmd, व्योम __user *arg);

व्योम dn_dev_devices_off(व्योम);
व्योम dn_dev_devices_on(व्योम);

व्योम dn_dev_init_pkt(काष्ठा sk_buff *skb);
व्योम dn_dev_veri_pkt(काष्ठा sk_buff *skb);
व्योम dn_dev_hello(काष्ठा sk_buff *skb);

व्योम dn_dev_up(काष्ठा net_device *);
व्योम dn_dev_करोwn(काष्ठा net_device *);

पूर्णांक dn_dev_set_शेष(काष्ठा net_device *dev, पूर्णांक क्रमce);
काष्ठा net_device *dn_dev_get_शेष(व्योम);
पूर्णांक dn_dev_bind_शेष(__le16 *addr);

पूर्णांक रेजिस्टर_dnaddr_notअगरier(काष्ठा notअगरier_block *nb);
पूर्णांक unरेजिस्टर_dnaddr_notअगरier(काष्ठा notअगरier_block *nb);

अटल अंतरभूत पूर्णांक dn_dev_islocal(काष्ठा net_device *dev, __le16 addr)
अणु
	काष्ठा dn_dev *dn_db;
	काष्ठा dn_अगरaddr *अगरa;
	पूर्णांक res = 0;

	rcu_पढ़ो_lock();
	dn_db = rcu_dereference(dev->dn_ptr);
	अगर (dn_db == शून्य) अणु
		prपूर्णांकk(KERN_DEBUG "dn_dev_islocal: Called for non DECnet device\n");
		जाओ out;
	पूर्ण

	क्रम (अगरa = rcu_dereference(dn_db->अगरa_list);
	     अगरa != शून्य;
	     अगरa = rcu_dereference(अगरa->अगरa_next))
		अगर ((addr ^ अगरa->अगरa_local) == 0) अणु
			res = 1;
			अवरोध;
		पूर्ण
out:
	rcu_पढ़ो_unlock();
	वापस res;
पूर्ण

#पूर्ण_अगर /* _NET_DN_DEV_H */
