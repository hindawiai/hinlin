<शैली गुरु>
/*======================================================================

    Device driver क्रम Databook TCIC-2 PCMCIA controller

    tcic.c 1.111 2000/02/15 04:13:12

    The contents of this file are subject to the Mozilla Public
    License Version 1.1 (the "License"); you may not use this file
    except in compliance with the License. You may obtain a copy of
    the License at http://www.mozilla.org/MPL/

    Software distributed under the License is distributed on an "AS
    IS" basis, WITHOUT WARRANTY OF ANY KIND, either express or
    implied. See the License क्रम the specअगरic language governing
    rights and limitations under the License.

    The initial developer of the original code is David A. Hinds
    <dahinds@users.sourceक्रमge.net>.  Portions created by David A. Hinds
    are Copyright (C) 1999 David A. Hinds.  All Rights Reserved.

    Alternatively, the contents of this file may be used under the
    terms of the GNU General Public License version 2 (the "GPL"), in which
    हाल the provisions of the GPL are applicable instead of the
    above.  If you wish to allow the use of your version of this file
    only under the terms of the GPL and not to allow others to use
    your version of this file under the MPL, indicate your decision
    by deleting the provisions above and replace them with the notice
    and other provisions required by the GPL.  If you करो not delete
    the provisions above, a recipient may use your version of this
    file under either the MPL or the GPL.
    
======================================================================*/

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/समयr.h>
#समावेश <linux/ioport.h>
#समावेश <linux/delay.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/bitops.h>

#समावेश <यंत्र/पन.स>

#समावेश <pcmcia/ss.h>
#समावेश "tcic.h"

MODULE_AUTHOR("David Hinds <dahinds@users.sourceforge.net>");
MODULE_DESCRIPTION("Databook TCIC-2 PCMCIA socket driver");
MODULE_LICENSE("Dual MPL/GPL");

/*====================================================================*/

/* Parameters that can be set with 'insmod' */

/* The base port address of the TCIC-2 chip */
अटल अचिन्हित दीर्घ tcic_base = TCIC_BASE;

/* Specअगरy a socket number to ignore */
अटल पूर्णांक ignore = -1;

/* Probe क्रम safe पूर्णांकerrupts? */
अटल पूर्णांक करो_scan = 1;

/* Bit map of पूर्णांकerrupts to choose from */
अटल u_पूर्णांक irq_mask = 0xffff;
अटल पूर्णांक irq_list[16];
अटल अचिन्हित पूर्णांक irq_list_count;

/* The card status change पूर्णांकerrupt -- 0 means स्वतःselect */
अटल पूर्णांक cs_irq;

/* Poll status पूर्णांकerval -- 0 means शेष to पूर्णांकerrupt */
अटल पूर्णांक poll_पूर्णांकerval;

/* Delay क्रम card status द्विगुन-checking */
अटल पूर्णांक poll_quick = HZ/20;

/* CCLK बाह्यal घड़ी समय, in nanoseconds.  70 ns = 14.31818 MHz */
अटल पूर्णांक cycle_समय = 70;

module_param_hw(tcic_base, uदीर्घ, ioport, 0444);
module_param(ignore, पूर्णांक, 0444);
module_param(करो_scan, पूर्णांक, 0444);
module_param_hw(irq_mask, पूर्णांक, other, 0444);
module_param_hw_array(irq_list, पूर्णांक, irq, &irq_list_count, 0444);
module_param_hw(cs_irq, पूर्णांक, irq, 0444);
module_param(poll_पूर्णांकerval, पूर्णांक, 0444);
module_param(poll_quick, पूर्णांक, 0444);
module_param(cycle_समय, पूर्णांक, 0444);

/*====================================================================*/

अटल irqवापस_t tcic_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev);
अटल व्योम tcic_समयr(काष्ठा समयr_list *unused);
अटल काष्ठा pccard_operations tcic_operations;

काष्ठा tcic_socket अणु
    u_लघु	psock;
    u_अक्षर	last_sstat;
    u_अक्षर	id;
    काष्ठा pcmcia_socket	socket;
पूर्ण;

अटल काष्ठा समयr_list poll_समयr;
अटल पूर्णांक tcic_समयr_pending;

अटल पूर्णांक sockets;
अटल काष्ठा tcic_socket socket_table[2];

/*====================================================================*/

/* Trick when selecting पूर्णांकerrupts: the TCIC sktirq pin is supposed
   to map to irq 11, but is coded as 0 or 1 in the irq रेजिस्टरs. */
#घोषणा TCIC_IRQ(x) ((x) ? (((x) == 11) ? 1 : (x)) : 15)

#अगर_घोषित DEBUG_X
अटल u_अक्षर tcic_getb(u_अक्षर reg)
अणु
    u_अक्षर val = inb(tcic_base+reg);
    prपूर्णांकk(KERN_DEBUG "tcic_getb(%#lx) = %#x\n", tcic_base+reg, val);
    वापस val;
पूर्ण

अटल u_लघु tcic_getw(u_अक्षर reg)
अणु
    u_लघु val = inw(tcic_base+reg);
    prपूर्णांकk(KERN_DEBUG "tcic_getw(%#lx) = %#x\n", tcic_base+reg, val);
    वापस val;
पूर्ण

अटल व्योम tcic_setb(u_अक्षर reg, u_अक्षर data)
अणु
    prपूर्णांकk(KERN_DEBUG "tcic_setb(%#lx, %#x)\n", tcic_base+reg, data);
    outb(data, tcic_base+reg);
पूर्ण

अटल व्योम tcic_setw(u_अक्षर reg, u_लघु data)
अणु
    prपूर्णांकk(KERN_DEBUG "tcic_setw(%#lx, %#x)\n", tcic_base+reg, data);
    outw(data, tcic_base+reg);
पूर्ण
#अन्यथा
#घोषणा tcic_getb(reg) inb(tcic_base+reg)
#घोषणा tcic_getw(reg) inw(tcic_base+reg)
#घोषणा tcic_setb(reg, data) outb(data, tcic_base+reg)
#घोषणा tcic_setw(reg, data) outw(data, tcic_base+reg)
#पूर्ण_अगर

अटल व्योम tcic_setl(u_अक्षर reg, u_पूर्णांक data)
अणु
#अगर_घोषित DEBUG_X
    prपूर्णांकk(KERN_DEBUG "tcic_setl(%#x, %#lx)\n", tcic_base+reg, data);
#पूर्ण_अगर
    outw(data & 0xffff, tcic_base+reg);
    outw(data >> 16, tcic_base+reg+2);
पूर्ण

अटल व्योम tcic_aux_setb(u_लघु reg, u_अक्षर data)
अणु
    u_अक्षर mode = (tcic_getb(TCIC_MODE) & TCIC_MODE_PGMMASK) | reg;
    tcic_setb(TCIC_MODE, mode);
    tcic_setb(TCIC_AUX, data);
पूर्ण

अटल u_लघु tcic_aux_getw(u_लघु reg)
अणु
    u_अक्षर mode = (tcic_getb(TCIC_MODE) & TCIC_MODE_PGMMASK) | reg;
    tcic_setb(TCIC_MODE, mode);
    वापस tcic_getw(TCIC_AUX);
पूर्ण

अटल व्योम tcic_aux_setw(u_लघु reg, u_लघु data)
अणु
    u_अक्षर mode = (tcic_getb(TCIC_MODE) & TCIC_MODE_PGMMASK) | reg;
    tcic_setb(TCIC_MODE, mode);
    tcic_setw(TCIC_AUX, data);
पूर्ण

/*====================================================================*/

/* Time conversion functions */

अटल पूर्णांक to_cycles(पूर्णांक ns)
अणु
    अगर (ns < 14)
	वापस 0;
    अन्यथा
	वापस 2*(ns-14)/cycle_समय;
पूर्ण

/*====================================================================*/

अटल अस्थिर u_पूर्णांक irq_hits;

अटल irqवापस_t __init tcic_irq_count(पूर्णांक irq, व्योम *dev)
अणु
    irq_hits++;
    वापस IRQ_HANDLED;
पूर्ण

अटल u_पूर्णांक __init try_irq(पूर्णांक irq)
अणु
    u_लघु cfg;

    irq_hits = 0;
    अगर (request_irq(irq, tcic_irq_count, 0, "irq scan", tcic_irq_count) != 0)
	वापस -1;
    mdelay(10);
    अगर (irq_hits) अणु
	मुक्त_irq(irq, tcic_irq_count);
	वापस -1;
    पूर्ण

    /* Generate one पूर्णांकerrupt */
    cfg = TCIC_SYSCFG_AUTOBUSY | 0x0a00;
    tcic_aux_setw(TCIC_AUX_SYSCFG, cfg | TCIC_IRQ(irq));
    tcic_setb(TCIC_IENA, TCIC_IENA_ERR | TCIC_IENA_CFG_HIGH);
    tcic_setb(TCIC_ICSR, TCIC_ICSR_ERR | TCIC_ICSR_JAM);

    udelay(1000);
    मुक्त_irq(irq, tcic_irq_count);

    /* Turn off पूर्णांकerrupts */
    tcic_setb(TCIC_IENA, TCIC_IENA_CFG_OFF);
    जबतक (tcic_getb(TCIC_ICSR))
	tcic_setb(TCIC_ICSR, TCIC_ICSR_JAM);
    tcic_aux_setw(TCIC_AUX_SYSCFG, cfg);
    
    वापस (irq_hits != 1);
पूर्ण

अटल u_पूर्णांक __init irq_scan(u_पूर्णांक mask0)
अणु
    u_पूर्णांक mask1;
    पूर्णांक i;

#अगर_घोषित __alpha__
#घोषणा PIC 0x4d0
    /* Don't probe level-triggered पूर्णांकerrupts -- reserved क्रम PCI */
    पूर्णांक level_mask = inb_p(PIC) | (inb_p(PIC+1) << 8);
    अगर (level_mask)
	mask0 &= ~level_mask;
#पूर्ण_अगर

    mask1 = 0;
    अगर (करो_scan) अणु
	क्रम (i = 0; i < 16; i++)
	    अगर ((mask0 & (1 << i)) && (try_irq(i) == 0))
		mask1 |= (1 << i);
	क्रम (i = 0; i < 16; i++)
	    अगर ((mask1 & (1 << i)) && (try_irq(i) != 0)) अणु
		mask1 ^= (1 << i);
	    पूर्ण
    पूर्ण
    
    अगर (mask1) अणु
	prपूर्णांकk("scanned");
    पूर्ण अन्यथा अणु
	/* Fallback: just find पूर्णांकerrupts that aren't in use */
	क्रम (i = 0; i < 16; i++)
	    अगर ((mask0 & (1 << i)) &&
		(request_irq(i, tcic_irq_count, 0, "x", tcic_irq_count) == 0)) अणु
		mask1 |= (1 << i);
		मुक्त_irq(i, tcic_irq_count);
	    पूर्ण
	prपूर्णांकk("default");
    पूर्ण
    
    prपूर्णांकk(") = ");
    क्रम (i = 0; i < 16; i++)
	अगर (mask1 & (1<<i))
	    prपूर्णांकk("%s%d", ((mask1 & ((1<<i)-1)) ? "," : ""), i);
    prपूर्णांकk(" ");
    
    वापस mask1;
पूर्ण

/*======================================================================

    See अगर a card is present, घातered up, in IO mode, and alपढ़ोy
    bound to a (non-PCMCIA) Linux driver.

    We make an exception क्रम cards that look like serial devices.
    
======================================================================*/

अटल पूर्णांक __init is_active(पूर्णांक s)
अणु
    u_लघु scf1, ioctl, base, num;
    u_अक्षर pwr, sstat;
    u_पूर्णांक addr;
    
    tcic_setl(TCIC_ADDR, (s << TCIC_ADDR_SS_SHFT)
	      | TCIC_ADDR_INDREG | TCIC_SCF1(s));
    scf1 = tcic_getw(TCIC_DATA);
    pwr = tcic_getb(TCIC_PWR);
    sstat = tcic_getb(TCIC_SSTAT);
    addr = TCIC_IWIN(s, 0);
    tcic_setw(TCIC_ADDR, addr + TCIC_IBASE_X);
    base = tcic_getw(TCIC_DATA);
    tcic_setw(TCIC_ADDR, addr + TCIC_ICTL_X);
    ioctl = tcic_getw(TCIC_DATA);

    अगर (ioctl & TCIC_ICTL_TINY)
	num = 1;
    अन्यथा अणु
	num = (base ^ (base-1));
	base = base & (base-1);
    पूर्ण

    अगर ((sstat & TCIC_SSTAT_CD) && (pwr & TCIC_PWR_VCC(s)) &&
	(scf1 & TCIC_SCF1_IOSTS) && (ioctl & TCIC_ICTL_ENA) &&
	((base & 0xfeef) != 0x02e8)) अणु
	काष्ठा resource *res = request_region(base, num, "tcic-2");
	अगर (!res) /* region is busy */
	    वापस 1;
	release_region(base, num);
    पूर्ण

    वापस 0;
पूर्ण

/*======================================================================

    This वापसs the revision code क्रम the specअगरied socket.
    
======================================================================*/

अटल पूर्णांक __init get_tcic_id(व्योम)
अणु
    u_लघु id;
    
    tcic_aux_setw(TCIC_AUX_TEST, TCIC_TEST_DIAG);
    id = tcic_aux_getw(TCIC_AUX_ILOCK);
    id = (id & TCIC_ILOCKTEST_ID_MASK) >> TCIC_ILOCKTEST_ID_SH;
    tcic_aux_setw(TCIC_AUX_TEST, 0);
    वापस id;
पूर्ण

/*====================================================================*/

अटल काष्ठा platक्रमm_driver tcic_driver = अणु
	.driver = अणु
		.name = "tcic-pcmcia",
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device tcic_device = अणु
	.name = "tcic-pcmcia",
	.id = 0,
पूर्ण;


अटल पूर्णांक __init init_tcic(व्योम)
अणु
    पूर्णांक i, sock, ret = 0;
    u_पूर्णांक mask, scan;

    अगर (platक्रमm_driver_रेजिस्टर(&tcic_driver))
	वापस -1;
    
    prपूर्णांकk(KERN_INFO "Databook TCIC-2 PCMCIA probe: ");
    sock = 0;

    अगर (!request_region(tcic_base, 16, "tcic-2")) अणु
	prपूर्णांकk("could not allocate ports,\n ");
	platक्रमm_driver_unरेजिस्टर(&tcic_driver);
	वापस -ENODEV;
    पूर्ण
    अन्यथा अणु
	tcic_setw(TCIC_ADDR, 0);
	अगर (tcic_getw(TCIC_ADDR) == 0) अणु
	    tcic_setw(TCIC_ADDR, 0xc3a5);
	    अगर (tcic_getw(TCIC_ADDR) == 0xc3a5) sock = 2;
	पूर्ण
	अगर (sock == 0) अणु
	    /* See अगर resetting the controller करोes any good */
	    tcic_setb(TCIC_SCTRL, TCIC_SCTRL_RESET);
	    tcic_setb(TCIC_SCTRL, 0);
	    tcic_setw(TCIC_ADDR, 0);
	    अगर (tcic_getw(TCIC_ADDR) == 0) अणु
		tcic_setw(TCIC_ADDR, 0xc3a5);
		अगर (tcic_getw(TCIC_ADDR) == 0xc3a5) sock = 2;
	    पूर्ण
	पूर्ण
    पूर्ण
    अगर (sock == 0) अणु
	prपूर्णांकk("not found.\n");
	release_region(tcic_base, 16);
	platक्रमm_driver_unरेजिस्टर(&tcic_driver);
	वापस -ENODEV;
    पूर्ण

    sockets = 0;
    क्रम (i = 0; i < sock; i++) अणु
	अगर ((i == ignore) || is_active(i)) जारी;
	socket_table[sockets].psock = i;
	socket_table[sockets].id = get_tcic_id();

	socket_table[sockets].socket.owner = THIS_MODULE;
	/* only 16-bit cards, memory winकरोws must be size-aligned */
	/* No PCI or CardBus support */
	socket_table[sockets].socket.features = SS_CAP_PCCARD | SS_CAP_MEM_ALIGN;
	/* irq 14, 11, 10, 7, 6, 5, 4, 3 */
	socket_table[sockets].socket.irq_mask = 0x4cf8;
	/* 4K minimum winकरोw size */
	socket_table[sockets].socket.map_size = 0x1000;		
	sockets++;
    पूर्ण

    चयन (socket_table[0].id) अणु
    हाल TCIC_ID_DB86082:
	prपूर्णांकk("DB86082"); अवरोध;
    हाल TCIC_ID_DB86082A:
	prपूर्णांकk("DB86082A"); अवरोध;
    हाल TCIC_ID_DB86084:
	prपूर्णांकk("DB86084"); अवरोध;
    हाल TCIC_ID_DB86084A:
	prपूर्णांकk("DB86084A"); अवरोध;
    हाल TCIC_ID_DB86072:
	prपूर्णांकk("DB86072"); अवरोध;
    हाल TCIC_ID_DB86184:
	prपूर्णांकk("DB86184"); अवरोध;
    हाल TCIC_ID_DB86082B:
	prपूर्णांकk("DB86082B"); अवरोध;
    शेष:
	prपूर्णांकk("Unknown ID 0x%02x", socket_table[0].id);
    पूर्ण
    
    /* Set up polling */
    समयr_setup(&poll_समयr, &tcic_समयr, 0);

    /* Build पूर्णांकerrupt mask */
    prपूर्णांकk(KERN_CONT ", %d sockets\n", sockets);
    prपूर्णांकk(KERN_INFO "  irq list (");
    अगर (irq_list_count == 0)
	mask = irq_mask;
    अन्यथा
	क्रम (i = mask = 0; i < irq_list_count; i++)
	    mask |= (1<<irq_list[i]);

    /* irq 14, 11, 10, 7, 6, 5, 4, 3 */
    mask &= 0x4cf8;
    /* Scan पूर्णांकerrupts */
    mask = irq_scan(mask);
    क्रम (i=0;i<sockets;i++)
	    socket_table[i].socket.irq_mask = mask;
    
    /* Check क्रम only two पूर्णांकerrupts available */
    scan = (mask & (mask-1));
    अगर (((scan & (scan-1)) == 0) && (poll_पूर्णांकerval == 0))
	poll_पूर्णांकerval = HZ;
    
    अगर (poll_पूर्णांकerval == 0) अणु
	/* Aव्योम irq 12 unless it is explicitly requested */
	u_पूर्णांक cs_mask = mask & ((cs_irq) ? (1<<cs_irq) : ~(1<<12));
	क्रम (i = 15; i > 0; i--)
	    अगर ((cs_mask & (1 << i)) &&
		(request_irq(i, tcic_पूर्णांकerrupt, 0, "tcic",
			     tcic_पूर्णांकerrupt) == 0))
		अवरोध;
	cs_irq = i;
	अगर (cs_irq == 0) poll_पूर्णांकerval = HZ;
    पूर्ण
    
    अगर (socket_table[0].socket.irq_mask & (1 << 11))
	prपूर्णांकk("sktirq is irq 11, ");
    अगर (cs_irq != 0)
	prपूर्णांकk("status change on irq %d\n", cs_irq);
    अन्यथा
	prपूर्णांकk("polled status, interval = %d ms\n",
	       poll_पूर्णांकerval * 1000 / HZ);
    
    क्रम (i = 0; i < sockets; i++) अणु
	tcic_setw(TCIC_ADDR+2, socket_table[i].psock << TCIC_SS_SHFT);
	socket_table[i].last_sstat = tcic_getb(TCIC_SSTAT);
    पूर्ण
    
    /* jump start पूर्णांकerrupt handler, अगर needed */
    tcic_पूर्णांकerrupt(0, शून्य);

    platक्रमm_device_रेजिस्टर(&tcic_device);

    क्रम (i = 0; i < sockets; i++) अणु
	    socket_table[i].socket.ops = &tcic_operations;
	    socket_table[i].socket.resource_ops = &pccard_nonअटल_ops;
	    socket_table[i].socket.dev.parent = &tcic_device.dev;
	    ret = pcmcia_रेजिस्टर_socket(&socket_table[i].socket);
	    अगर (ret && i)
		    pcmcia_unरेजिस्टर_socket(&socket_table[0].socket);
    पूर्ण
    
    वापस ret;

    वापस 0;
    
पूर्ण /* init_tcic */

/*====================================================================*/

अटल व्योम __निकास निकास_tcic(व्योम)
अणु
    पूर्णांक i;

    del_समयr_sync(&poll_समयr);
    अगर (cs_irq != 0) अणु
	tcic_aux_setw(TCIC_AUX_SYSCFG, TCIC_SYSCFG_AUTOBUSY|0x0a00);
	मुक्त_irq(cs_irq, tcic_पूर्णांकerrupt);
    पूर्ण
    release_region(tcic_base, 16);

    क्रम (i = 0; i < sockets; i++) अणु
	    pcmcia_unरेजिस्टर_socket(&socket_table[i].socket);	    
    पूर्ण

    platक्रमm_device_unरेजिस्टर(&tcic_device);
    platक्रमm_driver_unरेजिस्टर(&tcic_driver);
पूर्ण /* निकास_tcic */

/*====================================================================*/

अटल irqवापस_t tcic_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev)
अणु
    पूर्णांक i, quick = 0;
    u_अक्षर latch, sstat;
    u_लघु psock;
    u_पूर्णांक events;
    अटल अस्थिर पूर्णांक active = 0;

    अगर (active) अणु
	prपूर्णांकk(KERN_NOTICE "tcic: reentered interrupt handler!\n");
	वापस IRQ_NONE;
    पूर्ण अन्यथा
	active = 1;

    pr_debug("tcic_interrupt()\n");
    
    क्रम (i = 0; i < sockets; i++) अणु
	psock = socket_table[i].psock;
	tcic_setl(TCIC_ADDR, (psock << TCIC_ADDR_SS_SHFT)
		  | TCIC_ADDR_INDREG | TCIC_SCF1(psock));
	sstat = tcic_getb(TCIC_SSTAT);
	latch = sstat ^ socket_table[psock].last_sstat;
	socket_table[i].last_sstat = sstat;
	अगर (tcic_getb(TCIC_ICSR) & TCIC_ICSR_CDCHG) अणु
	    tcic_setb(TCIC_ICSR, TCIC_ICSR_CLEAR);
	    quick = 1;
	पूर्ण
	अगर (latch == 0)
	    जारी;
	events = (latch & TCIC_SSTAT_CD) ? SS_DETECT : 0;
	events |= (latch & TCIC_SSTAT_WP) ? SS_WRPROT : 0;
	अगर (tcic_getw(TCIC_DATA) & TCIC_SCF1_IOSTS) अणु
	    events |= (latch & TCIC_SSTAT_LBAT1) ? SS_STSCHG : 0;
	पूर्ण अन्यथा अणु
	    events |= (latch & TCIC_SSTAT_RDY) ? SS_READY : 0;
	    events |= (latch & TCIC_SSTAT_LBAT1) ? SS_BATDEAD : 0;
	    events |= (latch & TCIC_SSTAT_LBAT2) ? SS_BATWARN : 0;
	पूर्ण
	अगर (events) अणु
		pcmcia_parse_events(&socket_table[i].socket, events);
	पूर्ण
    पूर्ण

    /* Schedule next poll, अगर needed */
    अगर (((cs_irq == 0) || quick) && (!tcic_समयr_pending)) अणु
	poll_समयr.expires = jअगरfies + (quick ? poll_quick : poll_पूर्णांकerval);
	add_समयr(&poll_समयr);
	tcic_समयr_pending = 1;
    पूर्ण
    active = 0;
    
    pr_debug("interrupt done\n");
    वापस IRQ_HANDLED;
पूर्ण /* tcic_पूर्णांकerrupt */

अटल व्योम tcic_समयr(काष्ठा समयr_list *unused)
अणु
    pr_debug("tcic_timer()\n");
    tcic_समयr_pending = 0;
    tcic_पूर्णांकerrupt(0, शून्य);
पूर्ण /* tcic_समयr */

/*====================================================================*/

अटल पूर्णांक tcic_get_status(काष्ठा pcmcia_socket *sock, u_पूर्णांक *value)
अणु
    u_लघु psock = container_of(sock, काष्ठा tcic_socket, socket)->psock;
    u_अक्षर reg;

    tcic_setl(TCIC_ADDR, (psock << TCIC_ADDR_SS_SHFT)
	      | TCIC_ADDR_INDREG | TCIC_SCF1(psock));
    reg = tcic_getb(TCIC_SSTAT);
    *value  = (reg & TCIC_SSTAT_CD) ? SS_DETECT : 0;
    *value |= (reg & TCIC_SSTAT_WP) ? SS_WRPROT : 0;
    अगर (tcic_getw(TCIC_DATA) & TCIC_SCF1_IOSTS) अणु
	*value |= (reg & TCIC_SSTAT_LBAT1) ? SS_STSCHG : 0;
    पूर्ण अन्यथा अणु
	*value |= (reg & TCIC_SSTAT_RDY) ? SS_READY : 0;
	*value |= (reg & TCIC_SSTAT_LBAT1) ? SS_BATDEAD : 0;
	*value |= (reg & TCIC_SSTAT_LBAT2) ? SS_BATWARN : 0;
    पूर्ण
    reg = tcic_getb(TCIC_PWR);
    अगर (reg & (TCIC_PWR_VCC(psock)|TCIC_PWR_VPP(psock)))
	*value |= SS_POWERON;
    dev_dbg(&sock->dev, "GetStatus(%d) = %#2.2x\n", psock, *value);
    वापस 0;
पूर्ण /* tcic_get_status */

/*====================================================================*/

अटल पूर्णांक tcic_set_socket(काष्ठा pcmcia_socket *sock, socket_state_t *state)
अणु
    u_लघु psock = container_of(sock, काष्ठा tcic_socket, socket)->psock;
    u_अक्षर reg;
    u_लघु scf1, scf2;

    dev_dbg(&sock->dev, "SetSocket(%d, flags %#3.3x, Vcc %d, Vpp %d, "
	  "io_irq %d, csc_mask %#2.2x)\n", psock, state->flags,
	  state->Vcc, state->Vpp, state->io_irq, state->csc_mask);
    tcic_setw(TCIC_ADDR+2, (psock << TCIC_SS_SHFT) | TCIC_ADR2_INDREG);

    reg = tcic_getb(TCIC_PWR);
    reg &= ~(TCIC_PWR_VCC(psock) | TCIC_PWR_VPP(psock));

    अगर (state->Vcc == 50) अणु
	चयन (state->Vpp) अणु
	हाल 0:   reg |= TCIC_PWR_VCC(psock) | TCIC_PWR_VPP(psock); अवरोध;
	हाल 50:  reg |= TCIC_PWR_VCC(psock); अवरोध;
	हाल 120: reg |= TCIC_PWR_VPP(psock); अवरोध;
	शेष:  वापस -EINVAL;
	पूर्ण
    पूर्ण अन्यथा अगर (state->Vcc != 0)
	वापस -EINVAL;

    अगर (reg != tcic_getb(TCIC_PWR))
	tcic_setb(TCIC_PWR, reg);

    reg = TCIC_ILOCK_HOLD_CCLK | TCIC_ILOCK_CWAIT;
    अगर (state->flags & SS_OUTPUT_ENA) अणु
	tcic_setb(TCIC_SCTRL, TCIC_SCTRL_ENA);
	reg |= TCIC_ILOCK_CRESENA;
    पूर्ण अन्यथा
	tcic_setb(TCIC_SCTRL, 0);
    अगर (state->flags & SS_RESET)
	reg |= TCIC_ILOCK_CRESET;
    tcic_aux_setb(TCIC_AUX_ILOCK, reg);
    
    tcic_setw(TCIC_ADDR, TCIC_SCF1(psock));
    scf1 = TCIC_SCF1_FINPACK;
    scf1 |= TCIC_IRQ(state->io_irq);
    अगर (state->flags & SS_IOCARD) अणु
	scf1 |= TCIC_SCF1_IOSTS;
	अगर (state->flags & SS_SPKR_ENA)
	    scf1 |= TCIC_SCF1_SPKR;
	अगर (state->flags & SS_DMA_MODE)
	    scf1 |= TCIC_SCF1_DREQ2 << TCIC_SCF1_DMA_SHIFT;
    पूर्ण
    tcic_setw(TCIC_DATA, scf1);

    /* Some general setup stuff, and configure status पूर्णांकerrupt */
    reg = TCIC_WAIT_ASYNC | TCIC_WAIT_SENSE | to_cycles(250);
    tcic_aux_setb(TCIC_AUX_WCTL, reg);
    tcic_aux_setw(TCIC_AUX_SYSCFG, TCIC_SYSCFG_AUTOBUSY|0x0a00|
		  TCIC_IRQ(cs_irq));
    
    /* Card status change पूर्णांकerrupt mask */
    tcic_setw(TCIC_ADDR, TCIC_SCF2(psock));
    scf2 = TCIC_SCF2_MALL;
    अगर (state->csc_mask & SS_DETECT) scf2 &= ~TCIC_SCF2_MCD;
    अगर (state->flags & SS_IOCARD) अणु
	अगर (state->csc_mask & SS_STSCHG) reg &= ~TCIC_SCF2_MLBAT1;
    पूर्ण अन्यथा अणु
	अगर (state->csc_mask & SS_BATDEAD) reg &= ~TCIC_SCF2_MLBAT1;
	अगर (state->csc_mask & SS_BATWARN) reg &= ~TCIC_SCF2_MLBAT2;
	अगर (state->csc_mask & SS_READY) reg &= ~TCIC_SCF2_MRDY;
    पूर्ण
    tcic_setw(TCIC_DATA, scf2);
    /* For the ISA bus, the irq should be active-high totem-pole */
    tcic_setb(TCIC_IENA, TCIC_IENA_CDCHG | TCIC_IENA_CFG_HIGH);

    वापस 0;
पूर्ण /* tcic_set_socket */
  
/*====================================================================*/

अटल पूर्णांक tcic_set_io_map(काष्ठा pcmcia_socket *sock, काष्ठा pccard_io_map *io)
अणु
    u_लघु psock = container_of(sock, काष्ठा tcic_socket, socket)->psock;
    u_पूर्णांक addr;
    u_लघु base, len, ioctl;
    
    dev_dbg(&sock->dev, "SetIOMap(%d, %d, %#2.2x, %d ns, "
	  "%#llx-%#llx)\n", psock, io->map, io->flags, io->speed,
	  (अचिन्हित दीर्घ दीर्घ)io->start, (अचिन्हित दीर्घ दीर्घ)io->stop);
    अगर ((io->map > 1) || (io->start > 0xffff) || (io->stop > 0xffff) ||
	(io->stop < io->start)) वापस -EINVAL;
    tcic_setw(TCIC_ADDR+2, TCIC_ADR2_INDREG | (psock << TCIC_SS_SHFT));
    addr = TCIC_IWIN(psock, io->map);

    base = io->start; len = io->stop - io->start;
    /* Check to see that len+1 is घातer of two, etc */
    अगर ((len & (len+1)) || (base & len)) वापस -EINVAL;
    base |= (len+1)>>1;
    tcic_setw(TCIC_ADDR, addr + TCIC_IBASE_X);
    tcic_setw(TCIC_DATA, base);
    
    ioctl  = (psock << TCIC_ICTL_SS_SHFT);
    ioctl |= (len == 0) ? TCIC_ICTL_TINY : 0;
    ioctl |= (io->flags & MAP_ACTIVE) ? TCIC_ICTL_ENA : 0;
    ioctl |= to_cycles(io->speed) & TCIC_ICTL_WSCNT_MASK;
    अगर (!(io->flags & MAP_AUTOSZ)) अणु
	ioctl |= TCIC_ICTL_QUIET;
	ioctl |= (io->flags & MAP_16BIT) ? TCIC_ICTL_BW_16 : TCIC_ICTL_BW_8;
    पूर्ण
    tcic_setw(TCIC_ADDR, addr + TCIC_ICTL_X);
    tcic_setw(TCIC_DATA, ioctl);
    
    वापस 0;
पूर्ण /* tcic_set_io_map */

/*====================================================================*/

अटल पूर्णांक tcic_set_mem_map(काष्ठा pcmcia_socket *sock, काष्ठा pccard_mem_map *mem)
अणु
    u_लघु psock = container_of(sock, काष्ठा tcic_socket, socket)->psock;
    u_लघु addr, ctl;
    u_दीर्घ base, len, mmap;

    dev_dbg(&sock->dev, "SetMemMap(%d, %d, %#2.2x, %d ns, "
	  "%#llx-%#llx, %#x)\n", psock, mem->map, mem->flags,
	  mem->speed, (अचिन्हित दीर्घ दीर्घ)mem->res->start,
	  (अचिन्हित दीर्घ दीर्घ)mem->res->end, mem->card_start);
    अगर ((mem->map > 3) || (mem->card_start > 0x3ffffff) ||
	(mem->res->start > 0xffffff) || (mem->res->end > 0xffffff) ||
	(mem->res->start > mem->res->end) || (mem->speed > 1000))
	वापस -EINVAL;
    tcic_setw(TCIC_ADDR+2, TCIC_ADR2_INDREG | (psock << TCIC_SS_SHFT));
    addr = TCIC_MWIN(psock, mem->map);

    base = mem->res->start; len = mem->res->end - mem->res->start;
    अगर ((len & (len+1)) || (base & len)) वापस -EINVAL;
    अगर (len == 0x0fff)
	base = (base >> TCIC_MBASE_HA_SHFT) | TCIC_MBASE_4K_BIT;
    अन्यथा
	base = (base | (len+1)>>1) >> TCIC_MBASE_HA_SHFT;
    tcic_setw(TCIC_ADDR, addr + TCIC_MBASE_X);
    tcic_setw(TCIC_DATA, base);
    
    mmap = mem->card_start - mem->res->start;
    mmap = (mmap >> TCIC_MMAP_CA_SHFT) & TCIC_MMAP_CA_MASK;
    अगर (mem->flags & MAP_ATTRIB) mmap |= TCIC_MMAP_REG;
    tcic_setw(TCIC_ADDR, addr + TCIC_MMAP_X);
    tcic_setw(TCIC_DATA, mmap);

    ctl  = TCIC_MCTL_QUIET | (psock << TCIC_MCTL_SS_SHFT);
    ctl |= to_cycles(mem->speed) & TCIC_MCTL_WSCNT_MASK;
    ctl |= (mem->flags & MAP_16BIT) ? 0 : TCIC_MCTL_B8;
    ctl |= (mem->flags & MAP_WRPROT) ? TCIC_MCTL_WP : 0;
    ctl |= (mem->flags & MAP_ACTIVE) ? TCIC_MCTL_ENA : 0;
    tcic_setw(TCIC_ADDR, addr + TCIC_MCTL_X);
    tcic_setw(TCIC_DATA, ctl);
    
    वापस 0;
पूर्ण /* tcic_set_mem_map */

/*====================================================================*/

अटल पूर्णांक tcic_init(काष्ठा pcmcia_socket *s)
अणु
	पूर्णांक i;
	काष्ठा resource res = अणु .start = 0, .end = 0x1000 पूर्ण;
	pccard_io_map io = अणु 0, 0, 0, 0, 1 पूर्ण;
	pccard_mem_map mem = अणु .res = &res, पूर्ण;

	क्रम (i = 0; i < 2; i++) अणु
		io.map = i;
		tcic_set_io_map(s, &io);
	पूर्ण
	क्रम (i = 0; i < 5; i++) अणु
		mem.map = i;
		tcic_set_mem_map(s, &mem);
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा pccard_operations tcic_operations = अणु
	.init		   = tcic_init,
	.get_status	   = tcic_get_status,
	.set_socket	   = tcic_set_socket,
	.set_io_map	   = tcic_set_io_map,
	.set_mem_map	   = tcic_set_mem_map,
पूर्ण;

/*====================================================================*/

module_init(init_tcic);
module_निकास(निकास_tcic);
