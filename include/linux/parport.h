<शैली गुरु>
/*
 * Any part of this program may be used in करोcuments licensed under
 * the GNU Free Documentation License, Version 1.1 or any later version
 * published by the Free Software Foundation.
 */
#अगर_अघोषित _PARPORT_H_
#घोषणा _PARPORT_H_


#समावेश <linux/jअगरfies.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/रुको.h>
#समावेश <linux/irqवापस.h>
#समावेश <linux/semaphore.h>
#समावेश <linux/device.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <uapi/linux/parport.h>

/* Define this later. */
काष्ठा parport;
काष्ठा pardevice;

काष्ठा pc_parport_state अणु
	अचिन्हित पूर्णांक ctr;
	अचिन्हित पूर्णांक ecr;
पूर्ण;

काष्ठा ax_parport_state अणु
	अचिन्हित पूर्णांक ctr;
	अचिन्हित पूर्णांक ecr;
	अचिन्हित पूर्णांक dcsr;
पूर्ण;

/* used by both parport_amiga and parport_mfc3 */
काष्ठा amiga_parport_state अणु
       अचिन्हित अक्षर data;     /* ciaa.prb */
       अचिन्हित अक्षर datadir;  /* ciaa.ddrb */
       अचिन्हित अक्षर status;   /* ciab.pra & 7 */
       अचिन्हित अक्षर statusdir;/* ciab.ddrb & 7 */
पूर्ण;

काष्ठा ax88796_parport_state अणु
	अचिन्हित अक्षर cpr;
पूर्ण;

काष्ठा ip32_parport_state अणु
	अचिन्हित पूर्णांक dcr;
	अचिन्हित पूर्णांक ecr;
पूर्ण;

काष्ठा parport_state अणु
	जोड़ अणु
		काष्ठा pc_parport_state pc;
		/* ARC has no state. */
		काष्ठा ax_parport_state ax;
		काष्ठा amiga_parport_state amiga;
		काष्ठा ax88796_parport_state ax88796;
		/* Atari has not state. */
		काष्ठा ip32_parport_state ip32;
		व्योम *misc; 
	पूर्ण u;
पूर्ण;

काष्ठा parport_operations अणु
	/* IBM PC-style भव रेजिस्टरs. */
	व्योम (*ग_लिखो_data)(काष्ठा parport *, अचिन्हित अक्षर);
	अचिन्हित अक्षर (*पढ़ो_data)(काष्ठा parport *);

	व्योम (*ग_लिखो_control)(काष्ठा parport *, अचिन्हित अक्षर);
	अचिन्हित अक्षर (*पढ़ो_control)(काष्ठा parport *);
	अचिन्हित अक्षर (*frob_control)(काष्ठा parport *, अचिन्हित अक्षर mask,
				      अचिन्हित अक्षर val);

	अचिन्हित अक्षर (*पढ़ो_status)(काष्ठा parport *);

	/* IRQs. */
	व्योम (*enable_irq)(काष्ठा parport *);
	व्योम (*disable_irq)(काष्ठा parport *);

	/* Data direction. */
	व्योम (*data_क्रमward) (काष्ठा parport *);
	व्योम (*data_reverse) (काष्ठा parport *);

	/* For core parport code. */
	व्योम (*init_state)(काष्ठा pardevice *, काष्ठा parport_state *);
	व्योम (*save_state)(काष्ठा parport *, काष्ठा parport_state *);
	व्योम (*restore_state)(काष्ठा parport *, काष्ठा parport_state *);

	/* Block पढ़ो/ग_लिखो */
	माप_प्रकार (*epp_ग_लिखो_data) (काष्ठा parport *port, स्थिर व्योम *buf,
				  माप_प्रकार len, पूर्णांक flags);
	माप_प्रकार (*epp_पढ़ो_data) (काष्ठा parport *port, व्योम *buf, माप_प्रकार len,
				 पूर्णांक flags);
	माप_प्रकार (*epp_ग_लिखो_addr) (काष्ठा parport *port, स्थिर व्योम *buf,
				  माप_प्रकार len, पूर्णांक flags);
	माप_प्रकार (*epp_पढ़ो_addr) (काष्ठा parport *port, व्योम *buf, माप_प्रकार len,
				 पूर्णांक flags);

	माप_प्रकार (*ecp_ग_लिखो_data) (काष्ठा parport *port, स्थिर व्योम *buf,
				  माप_प्रकार len, पूर्णांक flags);
	माप_प्रकार (*ecp_पढ़ो_data) (काष्ठा parport *port, व्योम *buf, माप_प्रकार len,
				 पूर्णांक flags);
	माप_प्रकार (*ecp_ग_लिखो_addr) (काष्ठा parport *port, स्थिर व्योम *buf,
				  माप_प्रकार len, पूर्णांक flags);

	माप_प्रकार (*compat_ग_लिखो_data) (काष्ठा parport *port, स्थिर व्योम *buf,
				     माप_प्रकार len, पूर्णांक flags);
	माप_प्रकार (*nibble_पढ़ो_data) (काष्ठा parport *port, व्योम *buf,
				    माप_प्रकार len, पूर्णांक flags);
	माप_प्रकार (*byte_पढ़ो_data) (काष्ठा parport *port, व्योम *buf,
				  माप_प्रकार len, पूर्णांक flags);
	काष्ठा module *owner;
पूर्ण;

काष्ठा parport_device_info अणु
	parport_device_class class;
	स्थिर अक्षर *class_name;
	स्थिर अक्षर *mfr;
	स्थिर अक्षर *model;
	स्थिर अक्षर *cmdset;
	स्थिर अक्षर *description;
पूर्ण;

/* Each device can have two callback functions:
 *  1) a preemption function, called by the resource manager to request
 *     that the driver relinquish control of the port.  The driver should
 *     वापस zero अगर it agrees to release the port, and nonzero अगर it 
 *     refuses.  Do not call parport_release() - the kernel will करो this
 *     implicitly.
 *
 *  2) a wake-up function, called by the resource manager to tell drivers
 *     that the port is available to be claimed.  If a driver wants to use
 *     the port, it should call parport_claim() here.
 */

/* A parallel port device */
काष्ठा pardevice अणु
	स्थिर अक्षर *name;
	काष्ठा parport *port;
	पूर्णांक daisy;
	पूर्णांक (*preempt)(व्योम *);
	व्योम (*wakeup)(व्योम *);
	व्योम *निजी;
	व्योम (*irq_func)(व्योम *);
	अचिन्हित पूर्णांक flags;
	काष्ठा pardevice *next;
	काष्ठा pardevice *prev;
	काष्ठा device dev;
	bool devmodel;
	काष्ठा parport_state *state;     /* saved status over preemption */
	रुको_queue_head_t रुको_q;
	अचिन्हित दीर्घ पूर्णांक समय;
	अचिन्हित दीर्घ पूर्णांक बारlice;
	अस्थिर दीर्घ पूर्णांक समयout;
	अचिन्हित दीर्घ रुकोing;		 /* दीर्घ req'd क्रम set_bit --RR */
	काष्ठा pardevice *रुकोprev;
	काष्ठा pardevice *रुकोnext;
	व्योम * sysctl_table;
पूर्ण;

#घोषणा to_pardevice(n) container_of(n, काष्ठा pardevice, dev)

/* IEEE1284 inक्रमmation */

/* IEEE1284 phases. These are exposed to userland through ppdev IOCTL
 * PP[GS]ETPHASE, so करो not change existing values. */
क्रमागत ieee1284_phase अणु
	IEEE1284_PH_FWD_DATA,
	IEEE1284_PH_FWD_IDLE,
	IEEE1284_PH_TERMINATE,
	IEEE1284_PH_NEGOTIATION,
	IEEE1284_PH_HBUSY_DNA,
	IEEE1284_PH_REV_IDLE,
	IEEE1284_PH_HBUSY_DAVAIL,
	IEEE1284_PH_REV_DATA,
	IEEE1284_PH_ECP_SETUP,
	IEEE1284_PH_ECP_FWD_TO_REV,
	IEEE1284_PH_ECP_REV_TO_FWD,
	IEEE1284_PH_ECP_सूची_UNKNOWN,
पूर्ण;
काष्ठा ieee1284_info अणु
	पूर्णांक mode;
	अस्थिर क्रमागत ieee1284_phase phase;
	काष्ठा semaphore irq;
पूर्ण;

/* A parallel port */
काष्ठा parport अणु
	अचिन्हित दीर्घ base;	/* base address */
	अचिन्हित दीर्घ base_hi;  /* base address (hi - ECR) */
	अचिन्हित पूर्णांक size;	/* IO extent */
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक modes;
	पूर्णांक irq;		/* पूर्णांकerrupt (or -1 क्रम none) */
	पूर्णांक dma;
	पूर्णांक muxport;		/* which muxport (अगर any) this is */
	पूर्णांक portnum;		/* which physical parallel port (not mux) */
	काष्ठा device *dev;	/* Physical device associated with IO/DMA.
				 * This may unक्रमtulately be null अगर the
				 * port has a legacy driver.
				 */
	काष्ठा device bus_dev;	/* to link with the bus */
	काष्ठा parport *physport;
				/* If this is a non-शेष mux
				   parport, i.e. we're a clone of a real
				   physical port, this is a poपूर्णांकer to that
				   port. The locking is only करोne in the
				   real port.  For a clone port, the
				   following काष्ठाure members are
				   meaningless: devices, cad, muxsel,
				   रुकोhead, रुकोtail, flags, pdir,
				   dev, ieee1284, *_lock.

				   It this is a शेष mux parport, or
				   there is no mux involved, this poपूर्णांकs to
				   ourself. */

	काष्ठा pardevice *devices;
	काष्ठा pardevice *cad;	/* port owner */
	पूर्णांक daisy;		/* currently selected daisy addr */
	पूर्णांक muxsel;		/* currently selected mux port */

	काष्ठा pardevice *रुकोhead;
	काष्ठा pardevice *रुकोtail;

	काष्ठा list_head list;
	काष्ठा समयr_list समयr;
	अचिन्हित पूर्णांक flags;

	व्योम *sysctl_table;
	काष्ठा parport_device_info probe_info[5]; /* 0-3 + non-IEEE1284.3 */
	काष्ठा ieee1284_info ieee1284;

	काष्ठा parport_operations *ops;
	व्योम *निजी_data;     /* क्रम lowlevel driver */

	पूर्णांक number;		/* port index - the `n' in `parportn' */
	spinlock_t pardevice_lock;
	spinlock_t रुकोlist_lock;
	rwlock_t cad_lock;

	पूर्णांक spपूर्णांकime;
	atomic_t ref_count;

	अचिन्हित दीर्घ devflags;
#घोषणा PARPORT_DEVPROC_REGISTERED	0
	काष्ठा pardevice *proc_device;	/* Currently रेजिस्टर proc device */

	काष्ठा list_head full_list;
	काष्ठा parport *slaves[3];
पूर्ण;

#घोषणा to_parport_dev(n) container_of(n, काष्ठा parport, bus_dev)

#घोषणा DEFAULT_SPIN_TIME 500 /* us */

काष्ठा parport_driver अणु
	स्थिर अक्षर *name;
	व्योम (*attach) (काष्ठा parport *);
	व्योम (*detach) (काष्ठा parport *);
	व्योम (*match_port)(काष्ठा parport *);
	पूर्णांक (*probe)(काष्ठा pardevice *);
	काष्ठा device_driver driver;
	bool devmodel;
	काष्ठा list_head list;
पूर्ण;

#घोषणा to_parport_driver(n) container_of(n, काष्ठा parport_driver, driver)

पूर्णांक parport_bus_init(व्योम);
व्योम parport_bus_निकास(व्योम);

/* parport_रेजिस्टर_port रेजिस्टरs a new parallel port at the given
   address (अगर one करोes not alपढ़ोy exist) and वापसs a poपूर्णांकer to it.
   This entails claiming the I/O region, IRQ and DMA.  शून्य is वापसed
   अगर initialisation fails. */
काष्ठा parport *parport_रेजिस्टर_port(अचिन्हित दीर्घ base, पूर्णांक irq, पूर्णांक dma,
				      काष्ठा parport_operations *ops);

/* Once a रेजिस्टरed port is पढ़ोy क्रम high-level drivers to use, the
   low-level driver that रेजिस्टरed it should announce it.  This will
   call the high-level drivers' attach() functions (after things like
   determining the IEEE 1284.3 topology of the port and collecting
   DeviceIDs). */
व्योम parport_announce_port (काष्ठा parport *port);

/* Unरेजिस्टर a port. */
बाह्य व्योम parport_हटाओ_port(काष्ठा parport *port);

/* Register a new high-level driver. */

पूर्णांक __must_check __parport_रेजिस्टर_driver(काष्ठा parport_driver *,
					   काष्ठा module *,
					   स्थिर अक्षर *mod_name);
/*
 * parport_रेजिस्टर_driver must be a macro so that KBUILD_MODNAME can
 * be expanded
 */

/**
 *	parport_रेजिस्टर_driver - रेजिस्टर a parallel port device driver
 *	@driver: काष्ठाure describing the driver
 *
 *	This can be called by a parallel port device driver in order
 *	to receive notअगरications about ports being found in the
 *	प्रणाली, as well as ports no दीर्घer available.
 *
 *	If devmodel is true then the new device model is used
 *	क्रम registration.
 *
 *	The @driver काष्ठाure is allocated by the caller and must not be
 *	deallocated until after calling parport_unरेजिस्टर_driver().
 *
 *	If using the non device model:
 *	The driver's attach() function may block.  The port that
 *	attach() is given will be valid क्रम the duration of the
 *	callback, but अगर the driver wants to take a copy of the
 *	poपूर्णांकer it must call parport_get_port() to करो so.  Calling
 *	parport_रेजिस्टर_device() on that port will करो this क्रम you.
 *
 *	The driver's detach() function may block.  The port that
 *	detach() is given will be valid क्रम the duration of the
 *	callback, but अगर the driver wants to take a copy of the
 *	poपूर्णांकer it must call parport_get_port() to करो so.
 *
 *
 *	Returns 0 on success. The non device model will always succeeds.
 *	but the new device model can fail and will वापस the error code.
 **/
#घोषणा parport_रेजिस्टर_driver(driver)             \
	__parport_रेजिस्टर_driver(driver, THIS_MODULE, KBUILD_MODNAME)

/* Unरेजिस्टर a high-level driver. */
व्योम parport_unरेजिस्टर_driver(काष्ठा parport_driver *);

/**
 * module_parport_driver() - Helper macro क्रम रेजिस्टरing a modular parport driver
 * @__parport_driver: काष्ठा parport_driver to be used
 *
 * Helper macro क्रम parport drivers which करो not करो anything special in module
 * init and निकास. This eliminates a lot of boilerplate. Each module may only
 * use this macro once, and calling it replaces module_init() and module_निकास().
 */
#घोषणा module_parport_driver(__parport_driver) \
	module_driver(__parport_driver, parport_रेजिस्टर_driver, parport_unरेजिस्टर_driver)

/* If parport_रेजिस्टर_driver करोesn't fit your needs, perhaps
 * parport_find_xxx करोes. */
बाह्य काष्ठा parport *parport_find_number (पूर्णांक);
बाह्य काष्ठा parport *parport_find_base (अचिन्हित दीर्घ);

/* generic irq handler, अगर it suits your needs */
बाह्य irqवापस_t parport_irq_handler(पूर्णांक irq, व्योम *dev_id);

/* Reference counting क्रम ports. */
बाह्य काष्ठा parport *parport_get_port (काष्ठा parport *);
बाह्य व्योम parport_put_port (काष्ठा parport *);
व्योम parport_del_port(काष्ठा parport *);

काष्ठा pardev_cb अणु
	पूर्णांक (*preempt)(व्योम *);
	व्योम (*wakeup)(व्योम *);
	व्योम *निजी;
	व्योम (*irq_func)(व्योम *);
	अचिन्हित पूर्णांक flags;
पूर्ण;

/*
 * parport_रेजिस्टर_dev_model declares that a device is connected to a
 * port, and tells the kernel all it needs to know.
 */
काष्ठा pardevice *
parport_रेजिस्टर_dev_model(काष्ठा parport *port, स्थिर अक्षर *name,
			   स्थिर काष्ठा pardev_cb *par_dev_cb, पूर्णांक cnt);

/* parport_unरेजिस्टर unlinks a device from the chain. */
बाह्य व्योम parport_unरेजिस्टर_device(काष्ठा pardevice *dev);

/* parport_claim tries to gain ownership of the port क्रम a particular
   driver.  This may fail (वापस non-zero) अगर another driver is busy.
   If this driver has रेजिस्टरed an पूर्णांकerrupt handler, it will be
   enabled.  */
बाह्य पूर्णांक parport_claim(काष्ठा pardevice *dev);

/* parport_claim_or_block is the same, but sleeps अगर the port cannot
   be claimed.  Return value is 1 अगर it slept, 0 normally and -त्रुटि_सं
   on error.  */
बाह्य पूर्णांक parport_claim_or_block(काष्ठा pardevice *dev);

/* parport_release reverses a previous parport_claim.  This can never
   fail, though the effects are undefined (except that they are bad)
   अगर you didn't previously own the port.  Once you have released the
   port you should make sure that neither your code nor the hardware
   on the port tries to initiate any communication without first
   re-claiming the port.  If you mess with the port state (enabling
   ECP क्रम example) you should clean up beक्रमe releasing the port. */

बाह्य व्योम parport_release(काष्ठा pardevice *dev);

/**
 * parport_yield - relinquish a parallel port temporarily
 * @dev: a device on the parallel port
 *
 * This function relinquishes the port अगर it would be helpful to other
 * drivers to करो so.  Afterwards it tries to reclaim the port using
 * parport_claim(), and the वापस value is the same as क्रम
 * parport_claim().  If it fails, the port is left unclaimed and it is
 * the driver's responsibility to reclaim the port.
 *
 * The parport_yield() and parport_yield_blocking() functions are क्रम
 * marking poपूर्णांकs in the driver at which other drivers may claim the
 * port and use their devices.  Yielding the port is similar to
 * releasing it and reclaiming it, but is more efficient because no
 * action is taken अगर there are no other devices needing the port.  In
 * fact, nothing is करोne even अगर there are other devices रुकोing but
 * the current device is still within its "timeslice".  The शेष
 * बारlice is half a second, but it can be adjusted via the /proc
 * पूर्णांकerface.
 **/
अटल __अंतरभूत__ पूर्णांक parport_yield(काष्ठा pardevice *dev)
अणु
	अचिन्हित दीर्घ पूर्णांक बारlip = (jअगरfies - dev->समय);
	अगर ((dev->port->रुकोhead == शून्य) || (बारlip < dev->बारlice))
		वापस 0;
	parport_release(dev);
	वापस parport_claim(dev);
पूर्ण

/**
 * parport_yield_blocking - relinquish a parallel port temporarily
 * @dev: a device on the parallel port
 *
 * This function relinquishes the port अगर it would be helpful to other
 * drivers to करो so.  Afterwards it tries to reclaim the port using
 * parport_claim_or_block(), and the वापस value is the same as क्रम
 * parport_claim_or_block().
 **/
अटल __अंतरभूत__ पूर्णांक parport_yield_blocking(काष्ठा pardevice *dev)
अणु
	अचिन्हित दीर्घ पूर्णांक बारlip = (jअगरfies - dev->समय);
	अगर ((dev->port->रुकोhead == शून्य) || (बारlip < dev->बारlice))
		वापस 0;
	parport_release(dev);
	वापस parport_claim_or_block(dev);
पूर्ण

/* Flags used to identअगरy what a device करोes. */
#घोषणा PARPORT_DEV_TRAN		0	/* WARNING !! DEPRECATED !! */
#घोषणा PARPORT_DEV_LURK		(1<<0)	/* WARNING !! DEPRECATED !! */
#घोषणा PARPORT_DEV_EXCL		(1<<1)	/* Need exclusive access. */

#घोषणा PARPORT_FLAG_EXCL		(1<<1)	/* EXCL driver रेजिस्टरed. */

/* IEEE1284 functions */
बाह्य व्योम parport_ieee1284_पूर्णांकerrupt (व्योम *);
बाह्य पूर्णांक parport_negotiate (काष्ठा parport *, पूर्णांक mode);
बाह्य sमाप_प्रकार parport_ग_लिखो (काष्ठा parport *, स्थिर व्योम *buf, माप_प्रकार len);
बाह्य sमाप_प्रकार parport_पढ़ो (काष्ठा parport *, व्योम *buf, माप_प्रकार len);

#घोषणा PARPORT_INACTIVITY_O_NONBLOCK 1
बाह्य दीर्घ parport_set_समयout (काष्ठा pardevice *, दीर्घ inactivity);

बाह्य पूर्णांक parport_रुको_event (काष्ठा parport *, दीर्घ समयout);
बाह्य पूर्णांक parport_रुको_peripheral (काष्ठा parport *port,
				    अचिन्हित अक्षर mask,
				    अचिन्हित अक्षर val);
बाह्य पूर्णांक parport_poll_peripheral (काष्ठा parport *port,
				    अचिन्हित अक्षर mask,
				    अचिन्हित अक्षर val,
				    पूर्णांक usec);

/* For architectural drivers */
बाह्य माप_प्रकार parport_ieee1284_ग_लिखो_compat (काष्ठा parport *,
					     स्थिर व्योम *, माप_प्रकार, पूर्णांक);
बाह्य माप_प्रकार parport_ieee1284_पढ़ो_nibble (काष्ठा parport *,
					    व्योम *, माप_प्रकार, पूर्णांक);
बाह्य माप_प्रकार parport_ieee1284_पढ़ो_byte (काष्ठा parport *,
					  व्योम *, माप_प्रकार, पूर्णांक);
बाह्य माप_प्रकार parport_ieee1284_ecp_पढ़ो_data (काष्ठा parport *,
					      व्योम *, माप_प्रकार, पूर्णांक);
बाह्य माप_प्रकार parport_ieee1284_ecp_ग_लिखो_data (काष्ठा parport *,
					       स्थिर व्योम *, माप_प्रकार, पूर्णांक);
बाह्य माप_प्रकार parport_ieee1284_ecp_ग_लिखो_addr (काष्ठा parport *,
					       स्थिर व्योम *, माप_प्रकार, पूर्णांक);
बाह्य माप_प्रकार parport_ieee1284_epp_ग_लिखो_data (काष्ठा parport *,
					       स्थिर व्योम *, माप_प्रकार, पूर्णांक);
बाह्य माप_प्रकार parport_ieee1284_epp_पढ़ो_data (काष्ठा parport *,
					      व्योम *, माप_प्रकार, पूर्णांक);
बाह्य माप_प्रकार parport_ieee1284_epp_ग_लिखो_addr (काष्ठा parport *,
					       स्थिर व्योम *, माप_प्रकार, पूर्णांक);
बाह्य माप_प्रकार parport_ieee1284_epp_पढ़ो_addr (काष्ठा parport *,
					      व्योम *, माप_प्रकार, पूर्णांक);

/* IEEE1284.3 functions */
#घोषणा daisy_dev_name "Device ID probe"
बाह्य पूर्णांक parport_daisy_init (काष्ठा parport *port);
बाह्य व्योम parport_daisy_fini (काष्ठा parport *port);
बाह्य काष्ठा pardevice *parport_खोलो (पूर्णांक devnum, स्थिर अक्षर *name);
बाह्य व्योम parport_बंद (काष्ठा pardevice *dev);
बाह्य sमाप_प्रकार parport_device_id (पूर्णांक devnum, अक्षर *buffer, माप_प्रकार len);
बाह्य व्योम parport_daisy_deselect_all (काष्ठा parport *port);
बाह्य पूर्णांक parport_daisy_select (काष्ठा parport *port, पूर्णांक daisy, पूर्णांक mode);

/* Lowlevel drivers _can_ call this support function to handle irqs.  */
अटल अंतरभूत व्योम parport_generic_irq(काष्ठा parport *port)
अणु
	parport_ieee1284_पूर्णांकerrupt (port);
	पढ़ो_lock(&port->cad_lock);
	अगर (port->cad && port->cad->irq_func)
		port->cad->irq_func(port->cad->निजी);
	पढ़ो_unlock(&port->cad_lock);
पूर्ण

/* Prototypes from parport_procfs */
बाह्य पूर्णांक parport_proc_रेजिस्टर(काष्ठा parport *pp);
बाह्य पूर्णांक parport_proc_unरेजिस्टर(काष्ठा parport *pp);
बाह्य पूर्णांक parport_device_proc_रेजिस्टर(काष्ठा pardevice *device);
बाह्य पूर्णांक parport_device_proc_unरेजिस्टर(काष्ठा pardevice *device);

/* If PC hardware is the only type supported, we can optimise a bit.  */
#अगर !defined(CONFIG_PARPORT_NOT_PC)

#समावेश <linux/parport_pc.h>
#घोषणा parport_ग_लिखो_data(p,x)            parport_pc_ग_लिखो_data(p,x)
#घोषणा parport_पढ़ो_data(p)               parport_pc_पढ़ो_data(p)
#घोषणा parport_ग_लिखो_control(p,x)         parport_pc_ग_लिखो_control(p,x)
#घोषणा parport_पढ़ो_control(p)            parport_pc_पढ़ो_control(p)
#घोषणा parport_frob_control(p,m,v)        parport_pc_frob_control(p,m,v)
#घोषणा parport_पढ़ो_status(p)             parport_pc_पढ़ो_status(p)
#घोषणा parport_enable_irq(p)              parport_pc_enable_irq(p)
#घोषणा parport_disable_irq(p)             parport_pc_disable_irq(p)
#घोषणा parport_data_क्रमward(p)            parport_pc_data_क्रमward(p)
#घोषणा parport_data_reverse(p)            parport_pc_data_reverse(p)

#अन्यथा  /*  !CONFIG_PARPORT_NOT_PC  */

/* Generic operations vector through the dispatch table. */
#घोषणा parport_ग_लिखो_data(p,x)            (p)->ops->ग_लिखो_data(p,x)
#घोषणा parport_पढ़ो_data(p)               (p)->ops->पढ़ो_data(p)
#घोषणा parport_ग_लिखो_control(p,x)         (p)->ops->ग_लिखो_control(p,x)
#घोषणा parport_पढ़ो_control(p)            (p)->ops->पढ़ो_control(p)
#घोषणा parport_frob_control(p,m,v)        (p)->ops->frob_control(p,m,v)
#घोषणा parport_पढ़ो_status(p)             (p)->ops->पढ़ो_status(p)
#घोषणा parport_enable_irq(p)              (p)->ops->enable_irq(p)
#घोषणा parport_disable_irq(p)             (p)->ops->disable_irq(p)
#घोषणा parport_data_क्रमward(p)            (p)->ops->data_क्रमward(p)
#घोषणा parport_data_reverse(p)            (p)->ops->data_reverse(p)

#पूर्ण_अगर /*  !CONFIG_PARPORT_NOT_PC  */

बाह्य अचिन्हित दीर्घ parport_शेष_बारlice;
बाह्य पूर्णांक parport_शेष_spपूर्णांकime;

#पूर्ण_अगर /* _PARPORT_H_ */
