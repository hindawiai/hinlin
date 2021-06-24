<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Device driver क्रम the Cuda and Egret प्रणाली controllers found on PowerMacs
 * and 68k Macs.
 *
 * The Cuda or Egret is a 6805 microcontroller पूर्णांकerfaced to the 6522 VIA.
 * This MCU controls प्रणाली घातer, Parameter RAM, Real Time Clock and the
 * Apple Desktop Bus (ADB) that connects to the keyboard and mouse.
 *
 * Copyright (C) 1996 Paul Mackerras.
 */
#समावेश <मानकतर्क.स>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/adb.h>
#समावेश <linux/cuda.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पूर्णांकerrupt.h>
#अगर_घोषित CONFIG_PPC
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/machdep.h>
#अन्यथा
#समावेश <यंत्र/macपूर्णांकosh.h>
#समावेश <यंत्र/macपूर्णांकs.h>
#समावेश <यंत्र/mac_via.h>
#पूर्ण_अगर
#समावेश <यंत्र/पन.स>
#समावेश <linux/init.h>

अटल अस्थिर अचिन्हित अक्षर __iomem *via;
अटल DEFINE_SPINLOCK(cuda_lock);

/* VIA रेजिस्टरs - spaced 0x200 bytes apart */
#घोषणा RS		0x200		/* skip between रेजिस्टरs */
#घोषणा B		0		/* B-side data */
#घोषणा A		RS		/* A-side data */
#घोषणा सूचीB		(2*RS)		/* B-side direction (1=output) */
#घोषणा सूचीA		(3*RS)		/* A-side direction (1=output) */
#घोषणा T1CL		(4*RS)		/* Timer 1 ctr/latch (low 8 bits) */
#घोषणा T1CH		(5*RS)		/* Timer 1 counter (high 8 bits) */
#घोषणा T1LL		(6*RS)		/* Timer 1 latch (low 8 bits) */
#घोषणा T1LH		(7*RS)		/* Timer 1 latch (high 8 bits) */
#घोषणा T2CL		(8*RS)		/* Timer 2 ctr/latch (low 8 bits) */
#घोषणा T2CH		(9*RS)		/* Timer 2 counter (high 8 bits) */
#घोषणा SR		(10*RS)		/* Shअगरt रेजिस्टर */
#घोषणा ACR		(11*RS)		/* Auxiliary control रेजिस्टर */
#घोषणा PCR		(12*RS)		/* Peripheral control रेजिस्टर */
#घोषणा IFR		(13*RS)		/* Interrupt flag रेजिस्टर */
#घोषणा IER		(14*RS)		/* Interrupt enable रेजिस्टर */
#घोषणा ANH		(15*RS)		/* A-side data, no handshake */

/*
 * When the Cuda design replaced the Egret, some संकेत names and
 * logic sense changed. They all serve the same purposes, however.
 *
 *   VIA pin       |  Egret pin
 * ----------------+------------------------------------------
 *   PB3 (input)   |  Transceiver session   (active low)
 *   PB4 (output)  |  VIA full              (active high)
 *   PB5 (output)  |  System session        (active high)
 *
 *   VIA pin       |  Cuda pin
 * ----------------+------------------------------------------
 *   PB3 (input)   |  Transfer request      (active low)
 *   PB4 (output)  |  Byte acknowledge      (active low)
 *   PB5 (output)  |  Transfer in progress  (active low)
 */

/* Bits in Port B data रेजिस्टर */
#घोषणा TREQ		0x08		/* Transfer request */
#घोषणा TACK		0x10		/* Transfer acknowledge */
#घोषणा TIP		0x20		/* Transfer in progress */

/* Bits in ACR */
#घोषणा SR_CTRL		0x1c		/* Shअगरt रेजिस्टर control bits */
#घोषणा SR_EXT		0x0c		/* Shअगरt on बाह्यal घड़ी */
#घोषणा SR_OUT		0x10		/* Shअगरt out अगर 1 */

/* Bits in IFR and IER */
#घोषणा IER_SET		0x80		/* set bits in IER */
#घोषणा IER_CLR		0		/* clear bits in IER */
#घोषणा SR_INT		0x04		/* Shअगरt रेजिस्टर full/empty */

/* Duration of byte acknowledgement pulse (us) */
#घोषणा EGRET_TACK_ASSERTED_DELAY	300
#घोषणा EGRET_TACK_NEGATED_DELAY	400

/* Interval from पूर्णांकerrupt to start of session (us) */
#घोषणा EGRET_SESSION_DELAY		450

#अगर_घोषित CONFIG_PPC
#घोषणा mcu_is_egret	false
#अन्यथा
अटल bool mcu_is_egret;
#पूर्ण_अगर

अटल अंतरभूत bool TREQ_निश्चितed(u8 portb)
अणु
	वापस !(portb & TREQ);
पूर्ण

अटल अंतरभूत व्योम निश्चित_TIP(व्योम)
अणु
	अगर (mcu_is_egret) अणु
		udelay(EGRET_SESSION_DELAY);
		out_8(&via[B], in_8(&via[B]) | TIP);
	पूर्ण अन्यथा
		out_8(&via[B], in_8(&via[B]) & ~TIP);
पूर्ण

अटल अंतरभूत व्योम निश्चित_TIP_and_TACK(व्योम)
अणु
	अगर (mcu_is_egret) अणु
		udelay(EGRET_SESSION_DELAY);
		out_8(&via[B], in_8(&via[B]) | TIP | TACK);
	पूर्ण अन्यथा
		out_8(&via[B], in_8(&via[B]) & ~(TIP | TACK));
पूर्ण

अटल अंतरभूत व्योम निश्चित_TACK(व्योम)
अणु
	अगर (mcu_is_egret) अणु
		udelay(EGRET_TACK_NEGATED_DELAY);
		out_8(&via[B], in_8(&via[B]) | TACK);
	पूर्ण अन्यथा
		out_8(&via[B], in_8(&via[B]) & ~TACK);
पूर्ण

अटल अंतरभूत व्योम toggle_TACK(व्योम)
अणु
	out_8(&via[B], in_8(&via[B]) ^ TACK);
पूर्ण

अटल अंतरभूत व्योम negate_TACK(व्योम)
अणु
	अगर (mcu_is_egret) अणु
		udelay(EGRET_TACK_ASSERTED_DELAY);
		out_8(&via[B], in_8(&via[B]) & ~TACK);
	पूर्ण अन्यथा
		out_8(&via[B], in_8(&via[B]) | TACK);
पूर्ण

अटल अंतरभूत व्योम negate_TIP_and_TACK(व्योम)
अणु
	अगर (mcu_is_egret) अणु
		udelay(EGRET_TACK_ASSERTED_DELAY);
		out_8(&via[B], in_8(&via[B]) & ~(TIP | TACK));
	पूर्ण अन्यथा
		out_8(&via[B], in_8(&via[B]) | TIP | TACK);
पूर्ण

अटल क्रमागत cuda_state अणु
    idle,
    sent_first_byte,
    sending,
    पढ़ोing,
    पढ़ो_करोne,
    aरुकोing_reply
पूर्ण cuda_state;

अटल काष्ठा adb_request *current_req;
अटल काष्ठा adb_request *last_req;
अटल अचिन्हित अक्षर cuda_rbuf[16];
अटल अचिन्हित अक्षर *reply_ptr;
अटल पूर्णांक पढ़ोing_reply;
अटल पूर्णांक data_index;
अटल पूर्णांक cuda_irq;
#अगर_घोषित CONFIG_PPC
अटल काष्ठा device_node *vias;
#पूर्ण_अगर
अटल पूर्णांक cuda_fully_inited;

#अगर_घोषित CONFIG_ADB
अटल पूर्णांक cuda_probe(व्योम);
अटल पूर्णांक cuda_send_request(काष्ठा adb_request *req, पूर्णांक sync);
अटल पूर्णांक cuda_adb_स्वतःpoll(पूर्णांक devs);
अटल पूर्णांक cuda_reset_adb_bus(व्योम);
#पूर्ण_अगर /* CONFIG_ADB */

अटल पूर्णांक cuda_init_via(व्योम);
अटल व्योम cuda_start(व्योम);
अटल irqवापस_t cuda_पूर्णांकerrupt(पूर्णांक irq, व्योम *arg);
अटल व्योम cuda_input(अचिन्हित अक्षर *buf, पूर्णांक nb);
व्योम cuda_poll(व्योम);
अटल पूर्णांक cuda_ग_लिखो(काष्ठा adb_request *req);

पूर्णांक cuda_request(काष्ठा adb_request *req,
		 व्योम (*करोne)(काष्ठा adb_request *), पूर्णांक nbytes, ...);

#अगर_घोषित CONFIG_ADB
काष्ठा adb_driver via_cuda_driver = अणु
	.name         = "CUDA",
	.probe        = cuda_probe,
	.send_request = cuda_send_request,
	.स्वतःpoll     = cuda_adb_स्वतःpoll,
	.poll         = cuda_poll,
	.reset_bus    = cuda_reset_adb_bus,
पूर्ण;
#पूर्ण_अगर /* CONFIG_ADB */

#अगर_घोषित CONFIG_MAC
पूर्णांक __init find_via_cuda(व्योम)
अणु
    काष्ठा adb_request req;
    पूर्णांक err;

    अगर (macपूर्णांकosh_config->adb_type != MAC_ADB_CUDA &&
        macपूर्णांकosh_config->adb_type != MAC_ADB_EGRET)
	वापस 0;

    via = via1;
    cuda_state = idle;
    mcu_is_egret = macपूर्णांकosh_config->adb_type == MAC_ADB_EGRET;

    err = cuda_init_via();
    अगर (err) अणु
	prपूर्णांकk(KERN_ERR "cuda_init_via() failed\n");
	via = शून्य;
	वापस 0;
    पूर्ण

    /* enable स्वतःpoll */
    cuda_request(&req, शून्य, 3, CUDA_PACKET, CUDA_AUTOPOLL, 1);
    जबतक (!req.complete)
	cuda_poll();

    वापस 1;
पूर्ण
#अन्यथा
पूर्णांक __init find_via_cuda(व्योम)
अणु
    काष्ठा adb_request req;
    phys_addr_t taddr;
    स्थिर u32 *reg;
    पूर्णांक err;

    अगर (vias != 0)
	वापस 1;
    vias = of_find_node_by_name(शून्य, "via-cuda");
    अगर (vias == 0)
	वापस 0;

    reg = of_get_property(vias, "reg", शून्य);
    अगर (reg == शून्य) अणु
	    prपूर्णांकk(KERN_ERR "via-cuda: No \"reg\" property !\n");
	    जाओ fail;
    पूर्ण
    taddr = of_translate_address(vias, reg);
    अगर (taddr == 0) अणु
	    prपूर्णांकk(KERN_ERR "via-cuda: Can't translate address !\n");
	    जाओ fail;
    पूर्ण
    via = ioremap(taddr, 0x2000);
    अगर (via == शून्य) अणु
	    prपूर्णांकk(KERN_ERR "via-cuda: Can't map address !\n");
	    जाओ fail;
    पूर्ण

    cuda_state = idle;
    sys_ctrler = SYS_CTRLER_CUDA;

    err = cuda_init_via();
    अगर (err) अणु
	prपूर्णांकk(KERN_ERR "cuda_init_via() failed\n");
	via = शून्य;
	वापस 0;
    पूर्ण

    /* Clear and enable पूर्णांकerrupts, but only on PPC. On 68K it's करोne  */
    /* क्रम us by the मुख्य VIA driver in arch/m68k/mac/via.c        */

    out_8(&via[IFR], 0x7f);	/* clear पूर्णांकerrupts by writing 1s */
    out_8(&via[IER], IER_SET|SR_INT); /* enable पूर्णांकerrupt from SR */

    /* enable स्वतःpoll */
    cuda_request(&req, शून्य, 3, CUDA_PACKET, CUDA_AUTOPOLL, 1);
    जबतक (!req.complete)
	cuda_poll();

    वापस 1;

 fail:
    of_node_put(vias);
    vias = शून्य;
    वापस 0;
पूर्ण
#पूर्ण_अगर /* !defined CONFIG_MAC */

अटल पूर्णांक __init via_cuda_start(व्योम)
अणु
    अगर (via == शून्य)
	वापस -ENODEV;

#अगर_घोषित CONFIG_MAC
    cuda_irq = IRQ_MAC_ADB;
#अन्यथा
    cuda_irq = irq_of_parse_and_map(vias, 0);
    अगर (!cuda_irq) अणु
	prपूर्णांकk(KERN_ERR "via-cuda: can't map interrupts for %pOF\n",
	       vias);
	वापस -ENODEV;
    पूर्ण
#पूर्ण_अगर

    अगर (request_irq(cuda_irq, cuda_पूर्णांकerrupt, 0, "ADB", cuda_पूर्णांकerrupt)) अणु
	prपूर्णांकk(KERN_ERR "via-cuda: can't request irq %d\n", cuda_irq);
	वापस -EAGAIN;
    पूर्ण

    pr_info("Macintosh Cuda and Egret driver.\n");

    cuda_fully_inited = 1;
    वापस 0;
पूर्ण

device_initcall(via_cuda_start);

#अगर_घोषित CONFIG_ADB
अटल पूर्णांक
cuda_probe(व्योम)
अणु
#अगर_घोषित CONFIG_PPC
    अगर (sys_ctrler != SYS_CTRLER_CUDA)
	वापस -ENODEV;
#अन्यथा
    अगर (macपूर्णांकosh_config->adb_type != MAC_ADB_CUDA &&
        macपूर्णांकosh_config->adb_type != MAC_ADB_EGRET)
	वापस -ENODEV;
#पूर्ण_अगर
    अगर (via == शून्य)
	वापस -ENODEV;
    वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_ADB */

अटल पूर्णांक __init sync_egret(व्योम)
अणु
	अगर (TREQ_निश्चितed(in_8(&via[B]))) अणु
		/* Complete the inbound transfer */
		निश्चित_TIP_and_TACK();
		जबतक (1) अणु
			negate_TACK();
			mdelay(1);
			(व्योम)in_8(&via[SR]);
			निश्चित_TACK();
			अगर (!TREQ_निश्चितed(in_8(&via[B])))
				अवरोध;
		पूर्ण
		negate_TIP_and_TACK();
	पूर्ण अन्यथा अगर (in_8(&via[B]) & TIP) अणु
		/* Terminate the outbound transfer */
		negate_TACK();
		निश्चित_TACK();
		mdelay(1);
		negate_TIP_and_TACK();
	पूर्ण
	/* Clear shअगरt रेजिस्टर पूर्णांकerrupt */
	अगर (in_8(&via[IFR]) & SR_INT)
		(व्योम)in_8(&via[SR]);
	वापस 0;
पूर्ण

#घोषणा WAIT_FOR(cond, what)					\
    करो अणु                                                        \
    	पूर्णांक x;							\
	क्रम (x = 1000; !(cond); --x) अणु				\
	    अगर (x == 0) अणु					\
		pr_err("Timeout waiting for " what "\n");	\
		वापस -ENXIO;					\
	    पूर्ण							\
	    udelay(100);					\
	पूर्ण							\
    पूर्ण जबतक (0)

अटल पूर्णांक
__init cuda_init_via(व्योम)
अणु
#अगर_घोषित CONFIG_PPC
    out_8(&via[IER], 0x7f);					/* disable पूर्णांकerrupts from VIA */
    (व्योम)in_8(&via[IER]);
#अन्यथा
    out_8(&via[IER], SR_INT);					/* disable SR पूर्णांकerrupt from VIA */
#पूर्ण_अगर

    out_8(&via[सूचीB], (in_8(&via[सूचीB]) | TACK | TIP) & ~TREQ);	/* TACK & TIP out */
    out_8(&via[ACR], (in_8(&via[ACR]) & ~SR_CTRL) | SR_EXT);	/* SR data in */
    (व्योम)in_8(&via[SR]);					/* clear any left-over data */

    अगर (mcu_is_egret)
	वापस sync_egret();

    negate_TIP_and_TACK();

    /* delay 4ms and then clear any pending पूर्णांकerrupt */
    mdelay(4);
    (व्योम)in_8(&via[SR]);
    out_8(&via[IFR], SR_INT);

    /* sync with the CUDA - निश्चित TACK without TIP */
    निश्चित_TACK();

    /* रुको क्रम the CUDA to निश्चित TREQ in response */
    WAIT_FOR(TREQ_निश्चितed(in_8(&via[B])), "CUDA response to sync");

    /* रुको क्रम the पूर्णांकerrupt and then clear it */
    WAIT_FOR(in_8(&via[IFR]) & SR_INT, "CUDA response to sync (2)");
    (व्योम)in_8(&via[SR]);
    out_8(&via[IFR], SR_INT);

    /* finish the sync by negating TACK */
    negate_TACK();

    /* रुको क्रम the CUDA to negate TREQ and the corresponding पूर्णांकerrupt */
    WAIT_FOR(!TREQ_निश्चितed(in_8(&via[B])), "CUDA response to sync (3)");
    WAIT_FOR(in_8(&via[IFR]) & SR_INT, "CUDA response to sync (4)");
    (व्योम)in_8(&via[SR]);
    out_8(&via[IFR], SR_INT);

    वापस 0;
पूर्ण

#अगर_घोषित CONFIG_ADB
/* Send an ADB command */
अटल पूर्णांक
cuda_send_request(काष्ठा adb_request *req, पूर्णांक sync)
अणु
    पूर्णांक i;

    अगर ((via == शून्य) || !cuda_fully_inited) अणु
	req->complete = 1;
	वापस -ENXIO;
    पूर्ण
  
    req->reply_expected = 1;

    i = cuda_ग_लिखो(req);
    अगर (i)
	वापस i;

    अगर (sync) अणु
	जबतक (!req->complete)
	    cuda_poll();
    पूर्ण
    वापस 0;
पूर्ण


/* Enable/disable स्वतःpolling */
अटल पूर्णांक
cuda_adb_स्वतःpoll(पूर्णांक devs)
अणु
    काष्ठा adb_request req;

    अगर ((via == शून्य) || !cuda_fully_inited)
	वापस -ENXIO;

    cuda_request(&req, शून्य, 3, CUDA_PACKET, CUDA_AUTOPOLL, (devs? 1: 0));
    जबतक (!req.complete)
	cuda_poll();
    वापस 0;
पूर्ण

/* Reset adb bus - how करो we करो this?? */
अटल पूर्णांक
cuda_reset_adb_bus(व्योम)
अणु
    काष्ठा adb_request req;

    अगर ((via == शून्य) || !cuda_fully_inited)
	वापस -ENXIO;

    cuda_request(&req, शून्य, 2, ADB_PACKET, 0);		/* maybe? */
    जबतक (!req.complete)
	cuda_poll();
    वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_ADB */

/* Conकाष्ठा and send a cuda request */
पूर्णांक
cuda_request(काष्ठा adb_request *req, व्योम (*करोne)(काष्ठा adb_request *),
	     पूर्णांक nbytes, ...)
अणु
    बहु_सूची list;
    पूर्णांक i;

    अगर (via == शून्य) अणु
	req->complete = 1;
	वापस -ENXIO;
    पूर्ण

    req->nbytes = nbytes;
    req->करोne = करोne;
    बहु_शुरू(list, nbytes);
    क्रम (i = 0; i < nbytes; ++i)
	req->data[i] = बहु_तर्क(list, पूर्णांक);
    बहु_पूर्ण(list);
    req->reply_expected = 1;
    वापस cuda_ग_लिखो(req);
पूर्ण
EXPORT_SYMBOL(cuda_request);

अटल पूर्णांक
cuda_ग_लिखो(काष्ठा adb_request *req)
अणु
    अचिन्हित दीर्घ flags;

    अगर (req->nbytes < 2 || req->data[0] > CUDA_PACKET) अणु
	req->complete = 1;
	वापस -EINVAL;
    पूर्ण
    req->next = शून्य;
    req->sent = 0;
    req->complete = 0;
    req->reply_len = 0;

    spin_lock_irqsave(&cuda_lock, flags);
    अगर (current_req != 0) अणु
	last_req->next = req;
	last_req = req;
    पूर्ण अन्यथा अणु
	current_req = req;
	last_req = req;
	अगर (cuda_state == idle)
	    cuda_start();
    पूर्ण
    spin_unlock_irqrestore(&cuda_lock, flags);

    वापस 0;
पूर्ण

अटल व्योम
cuda_start(व्योम)
अणु
    /* निश्चित cuda_state == idle */
    अगर (current_req == शून्य)
	वापस;
    data_index = 0;
    अगर (TREQ_निश्चितed(in_8(&via[B])))
	वापस;			/* a byte is coming in from the CUDA */

    /* set the shअगरt रेजिस्टर to shअगरt out and send a byte */
    out_8(&via[ACR], in_8(&via[ACR]) | SR_OUT);
    out_8(&via[SR], current_req->data[data_index++]);
    अगर (mcu_is_egret)
	निश्चित_TIP_and_TACK();
    अन्यथा
	निश्चित_TIP();
    cuda_state = sent_first_byte;
पूर्ण

व्योम
cuda_poll(व्योम)
अणु
	cuda_पूर्णांकerrupt(0, शून्य);
पूर्ण
EXPORT_SYMBOL(cuda_poll);

#घोषणा ARRAY_FULL(a, p)	((p) - (a) == ARRAY_SIZE(a))

अटल irqवापस_t
cuda_पूर्णांकerrupt(पूर्णांक irq, व्योम *arg)
अणु
    अचिन्हित दीर्घ flags;
    u8 status;
    काष्ठा adb_request *req = शून्य;
    अचिन्हित अक्षर ibuf[16];
    पूर्णांक ibuf_len = 0;
    पूर्णांक complete = 0;
    bool full;
    
    spin_lock_irqsave(&cuda_lock, flags);

    /* On घातermacs, this handler is रेजिस्टरed क्रम the VIA IRQ. But they use
     * just the shअगरt रेजिस्टर IRQ -- other VIA पूर्णांकerrupt sources are disabled.
     * On m68k macs, the VIA IRQ sources are dispatched inभागidually. Unless
     * we are polling, the shअगरt रेजिस्टर IRQ flag has alपढ़ोy been cleared.
     */

#अगर_घोषित CONFIG_MAC
    अगर (!arg)
#पूर्ण_अगर
    अणु
        अगर ((in_8(&via[IFR]) & SR_INT) == 0) अणु
            spin_unlock_irqrestore(&cuda_lock, flags);
            वापस IRQ_NONE;
        पूर्ण अन्यथा अणु
            out_8(&via[IFR], SR_INT);
        पूर्ण
    पूर्ण

    status = in_8(&via[B]) & (TIP | TACK | TREQ);

    चयन (cuda_state) अणु
    हाल idle:
	/* System controller has unsolicited data क्रम us */
	(व्योम)in_8(&via[SR]);
idle_state:
	निश्चित_TIP();
	cuda_state = पढ़ोing;
	reply_ptr = cuda_rbuf;
	पढ़ोing_reply = 0;
	अवरोध;

    हाल aरुकोing_reply:
	/* System controller has reply data क्रम us */
	(व्योम)in_8(&via[SR]);
	निश्चित_TIP();
	cuda_state = पढ़ोing;
	reply_ptr = current_req->reply;
	पढ़ोing_reply = 1;
	अवरोध;

    हाल sent_first_byte:
	अगर (TREQ_निश्चितed(status)) अणु
	    /* collision */
	    out_8(&via[ACR], in_8(&via[ACR]) & ~SR_OUT);
	    (व्योम)in_8(&via[SR]);
	    negate_TIP_and_TACK();
	    cuda_state = idle;
	    /* Egret करोes not उठाओ an "aborted" पूर्णांकerrupt */
	    अगर (mcu_is_egret)
		जाओ idle_state;
	पूर्ण अन्यथा अणु
	    out_8(&via[SR], current_req->data[data_index++]);
	    toggle_TACK();
	    अगर (mcu_is_egret)
		निश्चित_TACK();
	    cuda_state = sending;
	पूर्ण
	अवरोध;

    हाल sending:
	req = current_req;
	अगर (data_index >= req->nbytes) अणु
	    out_8(&via[ACR], in_8(&via[ACR]) & ~SR_OUT);
	    (व्योम)in_8(&via[SR]);
	    negate_TIP_and_TACK();
	    req->sent = 1;
	    अगर (req->reply_expected) अणु
		cuda_state = aरुकोing_reply;
	    पूर्ण अन्यथा अणु
		current_req = req->next;
		complete = 1;
		/* not sure about this */
		cuda_state = idle;
		cuda_start();
	    पूर्ण
	पूर्ण अन्यथा अणु
	    out_8(&via[SR], req->data[data_index++]);
	    toggle_TACK();
	    अगर (mcu_is_egret)
		निश्चित_TACK();
	पूर्ण
	अवरोध;

    हाल पढ़ोing:
	full = पढ़ोing_reply ? ARRAY_FULL(current_req->reply, reply_ptr)
	                     : ARRAY_FULL(cuda_rbuf, reply_ptr);
	अगर (full)
	    (व्योम)in_8(&via[SR]);
	अन्यथा
	    *reply_ptr++ = in_8(&via[SR]);
	अगर (!TREQ_निश्चितed(status) || full) अणु
	    अगर (mcu_is_egret)
		निश्चित_TACK();
	    /* that's all folks */
	    negate_TIP_and_TACK();
	    cuda_state = पढ़ो_करोne;
	    /* Egret करोes not उठाओ a "read done" पूर्णांकerrupt */
	    अगर (mcu_is_egret)
		जाओ पढ़ो_करोne_state;
	पूर्ण अन्यथा अणु
	    toggle_TACK();
	    अगर (mcu_is_egret)
		negate_TACK();
	पूर्ण
	अवरोध;

    हाल पढ़ो_करोne:
	(व्योम)in_8(&via[SR]);
पढ़ो_करोne_state:
	अगर (पढ़ोing_reply) अणु
	    req = current_req;
	    req->reply_len = reply_ptr - req->reply;
	    अगर (req->data[0] == ADB_PACKET) अणु
		/* Have to adjust the reply from ADB commands */
		अगर (req->reply_len <= 2 || (req->reply[1] & 2) != 0) अणु
		    /* the 0x2 bit indicates no response */
		    req->reply_len = 0;
		पूर्ण अन्यथा अणु
		    /* leave just the command and result bytes in the reply */
		    req->reply_len -= 2;
		    स_हटाओ(req->reply, req->reply + 2, req->reply_len);
		पूर्ण
	    पूर्ण
	    current_req = req->next;
	    complete = 1;
	    पढ़ोing_reply = 0;
	पूर्ण अन्यथा अणु
	    /* This is tricky. We must अवरोध the spinlock to call
	     * cuda_input. However, करोing so means we might get
	     * re-entered from another CPU getting an पूर्णांकerrupt
	     * or calling cuda_poll(). I ended up using the stack
	     * (it's only क्रम 16 bytes) and moving the actual
	     * call to cuda_input to outside of the lock.
	     */
	    ibuf_len = reply_ptr - cuda_rbuf;
	    स_नकल(ibuf, cuda_rbuf, ibuf_len);
	पूर्ण
	reply_ptr = cuda_rbuf;
	cuda_state = idle;
	cuda_start();
	अगर (cuda_state == idle && TREQ_निश्चितed(in_8(&via[B]))) अणु
	    निश्चित_TIP();
	    cuda_state = पढ़ोing;
	पूर्ण
	अवरोध;

    शेष:
	pr_err("cuda_interrupt: unknown cuda_state %d?\n", cuda_state);
    पूर्ण
    spin_unlock_irqrestore(&cuda_lock, flags);
    अगर (complete && req) अणु
    	व्योम (*करोne)(काष्ठा adb_request *) = req->करोne;
    	mb();
    	req->complete = 1;
    	/* Here, we assume that अगर the request has a करोne member, the
    	 * काष्ठा request will survive to setting req->complete to 1
    	 */
    	अगर (करोne)
		(*करोne)(req);
    पूर्ण
    अगर (ibuf_len)
	cuda_input(ibuf, ibuf_len);
    वापस IRQ_HANDLED;
पूर्ण

अटल व्योम
cuda_input(अचिन्हित अक्षर *buf, पूर्णांक nb)
अणु
    चयन (buf[0]) अणु
    हाल ADB_PACKET:
#अगर_घोषित CONFIG_XMON
	अगर (nb == 5 && buf[2] == 0x2c) अणु
	    बाह्य पूर्णांक xmon_wants_key, xmon_adb_keycode;
	    अगर (xmon_wants_key) अणु
		xmon_adb_keycode = buf[3];
		वापस;
	    पूर्ण
	पूर्ण
#पूर्ण_अगर /* CONFIG_XMON */
#अगर_घोषित CONFIG_ADB
	adb_input(buf+2, nb-2, buf[1] & 0x40);
#पूर्ण_अगर /* CONFIG_ADB */
	अवरोध;

    हाल TIMER_PACKET:
	/* Egret sends these periodically. Might be useful as a 'heartbeat'
	 * to trigger a recovery क्रम the VIA shअगरt रेजिस्टर errata.
	 */
	अवरोध;

    शेष:
	prपूर्णांक_hex_dump(KERN_INFO, "cuda_input: ", DUMP_PREFIX_NONE, 32, 1,
	               buf, nb, false);
    पूर्ण
पूर्ण

/* Offset between Unix समय (1970-based) and Mac समय (1904-based) */
#घोषणा RTC_OFFSET	2082844800

समय64_t cuda_get_समय(व्योम)
अणु
	काष्ठा adb_request req;
	u32 now;

	अगर (cuda_request(&req, शून्य, 2, CUDA_PACKET, CUDA_GET_TIME) < 0)
		वापस 0;
	जबतक (!req.complete)
		cuda_poll();
	अगर (req.reply_len != 7)
		pr_err("%s: got %d byte reply\n", __func__, req.reply_len);
	now = (req.reply[3] << 24) + (req.reply[4] << 16) +
	      (req.reply[5] << 8) + req.reply[6];
	वापस (समय64_t)now - RTC_OFFSET;
पूर्ण

पूर्णांक cuda_set_rtc_समय(काष्ठा rtc_समय *पंचांग)
अणु
	u32 now;
	काष्ठा adb_request req;

	now = lower_32_bits(rtc_पंचांग_to_समय64(पंचांग) + RTC_OFFSET);
	अगर (cuda_request(&req, शून्य, 6, CUDA_PACKET, CUDA_SET_TIME,
	                 now >> 24, now >> 16, now >> 8, now) < 0)
		वापस -ENXIO;
	जबतक (!req.complete)
		cuda_poll();
	अगर ((req.reply_len != 3) && (req.reply_len != 7))
		pr_err("%s: got %d byte reply\n", __func__, req.reply_len);
	वापस 0;
पूर्ण
