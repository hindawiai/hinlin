<शैली गुरु>
/*======================================================================

    Device driver क्रम Intel 82365 and compatible PC Card controllers.

    i82365.c 1.265 1999/11/10 18:36:21

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
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/समयr.h>
#समावेश <linux/ioport.h>
#समावेश <linux/delay.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/bitops.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/पन.स>

#समावेश <pcmcia/ss.h>

#समावेश <linux/isapnp.h>

/* ISA-bus controllers */
#समावेश "i82365.h"
#समावेश "cirrus.h"
#समावेश "vg468.h"
#समावेश "ricoh.h"


अटल irqवापस_t i365_count_irq(पूर्णांक, व्योम *);
अटल अंतरभूत पूर्णांक _check_irq(पूर्णांक irq, पूर्णांक flags)
अणु
    अगर (request_irq(irq, i365_count_irq, flags, "x", i365_count_irq) != 0)
	वापस -1;
    मुक्त_irq(irq, i365_count_irq);
    वापस 0;
पूर्ण

/*====================================================================*/

/* Parameters that can be set with 'insmod' */

/* Default base address क्रम i82365sl and other ISA chips */
अटल अचिन्हित दीर्घ i365_base = 0x3e0;
/* Should we probe at 0x3e2 क्रम an extra ISA controller? */
अटल पूर्णांक extra_sockets = 0;
/* Specअगरy a socket number to ignore */
अटल पूर्णांक ignore = -1;
/* Bit map or list of पूर्णांकerrupts to choose from */
अटल u_पूर्णांक irq_mask = 0xffff;
अटल पूर्णांक irq_list[16];
अटल अचिन्हित पूर्णांक irq_list_count;
/* The card status change पूर्णांकerrupt -- 0 means स्वतःselect */
अटल पूर्णांक cs_irq = 0;

/* Probe क्रम safe पूर्णांकerrupts? */
अटल पूर्णांक करो_scan = 1;
/* Poll status पूर्णांकerval -- 0 means शेष to पूर्णांकerrupt */
अटल पूर्णांक poll_पूर्णांकerval = 0;
/* External घड़ी समय, in nanoseconds.  120 ns = 8.33 MHz */
अटल पूर्णांक cycle_समय = 120;

/* Cirrus options */
अटल पूर्णांक has_dma = -1;
अटल पूर्णांक has_led = -1;
अटल पूर्णांक has_ring = -1;
अटल पूर्णांक dynamic_mode = 0;
अटल पूर्णांक freq_bypass = -1;
अटल पूर्णांक setup_समय = -1;
अटल पूर्णांक cmd_समय = -1;
अटल पूर्णांक recov_समय = -1;

/* Vadem options */
अटल पूर्णांक async_घड़ी = -1;
अटल पूर्णांक cable_mode = -1;
अटल पूर्णांक wakeup = 0;

module_param_hw(i365_base, uदीर्घ, ioport, 0444);
module_param(ignore, पूर्णांक, 0444);
module_param(extra_sockets, पूर्णांक, 0444);
module_param_hw(irq_mask, पूर्णांक, other, 0444);
module_param_hw_array(irq_list, पूर्णांक, irq, &irq_list_count, 0444);
module_param_hw(cs_irq, पूर्णांक, irq, 0444);
module_param(async_घड़ी, पूर्णांक, 0444);
module_param(cable_mode, पूर्णांक, 0444);
module_param(wakeup, पूर्णांक, 0444);

module_param(करो_scan, पूर्णांक, 0444);
module_param(poll_पूर्णांकerval, पूर्णांक, 0444);
module_param(cycle_समय, पूर्णांक, 0444);
module_param(has_dma, पूर्णांक, 0444);
module_param(has_led, पूर्णांक, 0444);
module_param(has_ring, पूर्णांक, 0444);
module_param(dynamic_mode, पूर्णांक, 0444);
module_param(freq_bypass, पूर्णांक, 0444);
module_param(setup_समय, पूर्णांक, 0444);
module_param(cmd_समय, पूर्णांक, 0444);
module_param(recov_समय, पूर्णांक, 0444);

/*====================================================================*/

काष्ठा cirrus_state अणु
    u_अक्षर		misc1, misc2;
    u_अक्षर		समयr[6];
पूर्ण;

काष्ठा vg46x_state अणु
    u_अक्षर		ctl, ema;
पूर्ण;

काष्ठा i82365_socket अणु
    u_लघु		type, flags;
    काष्ठा pcmcia_socket	socket;
    अचिन्हित पूर्णांक	number;
    अचिन्हित पूर्णांक	ioaddr;
    u_लघु		psock;
    u_अक्षर		cs_irq, पूर्णांकr;
    जोड़ अणु
	काष्ठा cirrus_state		cirrus;
	काष्ठा vg46x_state		vg46x;
    पूर्ण state;
पूर्ण;

/* Where we keep track of our sockets... */
अटल पूर्णांक sockets = 0;
अटल काष्ठा i82365_socket socket[8] = अणु
    अणु 0, पूर्ण, /* ... */
पूर्ण;

/* Default ISA पूर्णांकerrupt mask */
#घोषणा I365_MASK	0xdeb8	/* irq 15,14,12,11,10,9,7,5,4,3 */

अटल पूर्णांक grab_irq;
अटल DEFINE_SPINLOCK(isa_lock);
#घोषणा ISA_LOCK(n, f) spin_lock_irqsave(&isa_lock, f)
#घोषणा ISA_UNLOCK(n, f) spin_unlock_irqrestore(&isa_lock, f)

अटल काष्ठा समयr_list poll_समयr;

/*====================================================================*/

/* These definitions must match the pcic table! */
क्रमागत pcic_id अणु
    IS_I82365A, IS_I82365B, IS_I82365DF,
    IS_IBM, IS_RF5Cx96, IS_VLSI, IS_VG468, IS_VG469,
    IS_PD6710, IS_PD672X, IS_VT83C469,
पूर्ण;

/* Flags क्रम classअगरying groups of controllers */
#घोषणा IS_VADEM	0x0001
#घोषणा IS_CIRRUS	0x0002
#घोषणा IS_VIA		0x0010
#घोषणा IS_UNKNOWN	0x0400
#घोषणा IS_VG_PWR	0x0800
#घोषणा IS_DF_PWR	0x1000
#घोषणा IS_REGISTERED	0x2000
#घोषणा IS_ALIVE	0x8000

काष्ठा pcic अणु
    अक्षर		*name;
    u_लघु		flags;
पूर्ण;

अटल काष्ठा pcic pcic[] = अणु
    अणु "Intel i82365sl A step", 0 पूर्ण,
    अणु "Intel i82365sl B step", 0 पूर्ण,
    अणु "Intel i82365sl DF", IS_DF_PWR पूर्ण,
    अणु "IBM Clone", 0 पूर्ण,
    अणु "Ricoh RF5C296/396", 0 पूर्ण,
    अणु "VLSI 82C146", 0 पूर्ण,
    अणु "Vadem VG-468", IS_VADEM पूर्ण,
    अणु "Vadem VG-469", IS_VADEM|IS_VG_PWR पूर्ण,
    अणु "Cirrus PD6710", IS_CIRRUS पूर्ण,
    अणु "Cirrus PD672x", IS_CIRRUS पूर्ण,
    अणु "VIA VT83C469", IS_CIRRUS|IS_VIA पूर्ण,
पूर्ण;

#घोषणा PCIC_COUNT	ARRAY_SIZE(pcic)

/*====================================================================*/

अटल DEFINE_SPINLOCK(bus_lock);

अटल u_अक्षर i365_get(u_लघु sock, u_लघु reg)
अणु
    अचिन्हित दीर्घ flags;
    spin_lock_irqsave(&bus_lock,flags);
    अणु
	अचिन्हित पूर्णांक port = socket[sock].ioaddr;
	u_अक्षर val;
	reg = I365_REG(socket[sock].psock, reg);
	outb(reg, port); val = inb(port+1);
	spin_unlock_irqrestore(&bus_lock,flags);
	वापस val;
    पूर्ण
पूर्ण

अटल व्योम i365_set(u_लघु sock, u_लघु reg, u_अक्षर data)
अणु
    अचिन्हित दीर्घ flags;
    spin_lock_irqsave(&bus_lock,flags);
    अणु
	अचिन्हित पूर्णांक port = socket[sock].ioaddr;
	u_अक्षर val = I365_REG(socket[sock].psock, reg);
	outb(val, port); outb(data, port+1);
	spin_unlock_irqrestore(&bus_lock,flags);
    पूर्ण
पूर्ण

अटल व्योम i365_bset(u_लघु sock, u_लघु reg, u_अक्षर mask)
अणु
    u_अक्षर d = i365_get(sock, reg);
    d |= mask;
    i365_set(sock, reg, d);
पूर्ण

अटल व्योम i365_bclr(u_लघु sock, u_लघु reg, u_अक्षर mask)
अणु
    u_अक्षर d = i365_get(sock, reg);
    d &= ~mask;
    i365_set(sock, reg, d);
पूर्ण

अटल व्योम i365_bflip(u_लघु sock, u_लघु reg, u_अक्षर mask, पूर्णांक b)
अणु
    u_अक्षर d = i365_get(sock, reg);
    अगर (b)
	d |= mask;
    अन्यथा
	d &= ~mask;
    i365_set(sock, reg, d);
पूर्ण

अटल u_लघु i365_get_pair(u_लघु sock, u_लघु reg)
अणु
    u_लघु a, b;
    a = i365_get(sock, reg);
    b = i365_get(sock, reg+1);
    वापस (a + (b<<8));
पूर्ण

अटल व्योम i365_set_pair(u_लघु sock, u_लघु reg, u_लघु data)
अणु
    i365_set(sock, reg, data & 0xff);
    i365_set(sock, reg+1, data >> 8);
पूर्ण

/*======================================================================

    Code to save and restore global state inक्रमmation क्रम Cirrus
    PD67xx controllers, and to set and report global configuration
    options.

    The VIA controllers also use these routines, as they are mostly
    Cirrus lookalikes, without the timing रेजिस्टरs.
    
======================================================================*/

#घोषणा flip(v,b,f) (v = ((f)<0) ? v : ((f) ? ((v)|(b)) : ((v)&(~b))))

अटल व्योम cirrus_get_state(u_लघु s)
अणु
    पूर्णांक i;
    काष्ठा cirrus_state *p = &socket[s].state.cirrus;
    p->misc1 = i365_get(s, PD67_MISC_CTL_1);
    p->misc1 &= (PD67_MC1_MEDIA_ENA | PD67_MC1_INPACK_ENA);
    p->misc2 = i365_get(s, PD67_MISC_CTL_2);
    क्रम (i = 0; i < 6; i++)
	p->समयr[i] = i365_get(s, PD67_TIME_SETUP(0)+i);
पूर्ण

अटल व्योम cirrus_set_state(u_लघु s)
अणु
    पूर्णांक i;
    u_अक्षर misc;
    काष्ठा cirrus_state *p = &socket[s].state.cirrus;

    misc = i365_get(s, PD67_MISC_CTL_2);
    i365_set(s, PD67_MISC_CTL_2, p->misc2);
    अगर (misc & PD67_MC2_SUSPEND) mdelay(50);
    misc = i365_get(s, PD67_MISC_CTL_1);
    misc &= ~(PD67_MC1_MEDIA_ENA | PD67_MC1_INPACK_ENA);
    i365_set(s, PD67_MISC_CTL_1, misc | p->misc1);
    क्रम (i = 0; i < 6; i++)
	i365_set(s, PD67_TIME_SETUP(0)+i, p->समयr[i]);
पूर्ण

अटल u_पूर्णांक __init cirrus_set_opts(u_लघु s, अक्षर *buf)
अणु
    काष्ठा i82365_socket *t = &socket[s];
    काष्ठा cirrus_state *p = &socket[s].state.cirrus;
    u_पूर्णांक mask = 0xffff;

    अगर (has_ring == -1) has_ring = 1;
    flip(p->misc2, PD67_MC2_IRQ15_RI, has_ring);
    flip(p->misc2, PD67_MC2_DYNAMIC_MODE, dynamic_mode);
    flip(p->misc2, PD67_MC2_FREQ_BYPASS, freq_bypass);
    अगर (p->misc2 & PD67_MC2_IRQ15_RI)
	म_जोड़ो(buf, " [ring]");
    अगर (p->misc2 & PD67_MC2_DYNAMIC_MODE)
	म_जोड़ो(buf, " [dyn mode]");
    अगर (p->misc2 & PD67_MC2_FREQ_BYPASS)
	म_जोड़ो(buf, " [freq bypass]");
    अगर (p->misc1 & PD67_MC1_INPACK_ENA)
	म_जोड़ो(buf, " [inpack]");
    अगर (p->misc2 & PD67_MC2_IRQ15_RI)
	mask &= ~0x8000;
    अगर (has_led > 0) अणु
	म_जोड़ो(buf, " [led]");
	mask &= ~0x1000;
    पूर्ण
    अगर (has_dma > 0) अणु
	म_जोड़ो(buf, " [dma]");
	mask &= ~0x0600;
    पूर्ण
    अगर (!(t->flags & IS_VIA)) अणु
	अगर (setup_समय >= 0)
	    p->समयr[0] = p->समयr[3] = setup_समय;
	अगर (cmd_समय > 0) अणु
	    p->समयr[1] = cmd_समय;
	    p->समयr[4] = cmd_समय*2+4;
	पूर्ण
	अगर (p->समयr[1] == 0) अणु
	    p->समयr[1] = 6; p->समयr[4] = 16;
	    अगर (p->समयr[0] == 0)
		p->समयr[0] = p->समयr[3] = 1;
	पूर्ण
	अगर (recov_समय >= 0)
	    p->समयr[2] = p->समयr[5] = recov_समय;
	buf += म_माप(buf);
	प्र_लिखो(buf, " [%d/%d/%d] [%d/%d/%d]", p->समयr[0], p->समयr[1],
		p->समयr[2], p->समयr[3], p->समयr[4], p->समयr[5]);
    पूर्ण
    वापस mask;
पूर्ण

/*======================================================================

    Code to save and restore global state inक्रमmation क्रम Vadem VG468
    and VG469 controllers, and to set and report global configuration
    options.
    
======================================================================*/

अटल व्योम vg46x_get_state(u_लघु s)
अणु
    काष्ठा vg46x_state *p = &socket[s].state.vg46x;
    p->ctl = i365_get(s, VG468_CTL);
    अगर (socket[s].type == IS_VG469)
	p->ema = i365_get(s, VG469_EXT_MODE);
पूर्ण

अटल व्योम vg46x_set_state(u_लघु s)
अणु
    काष्ठा vg46x_state *p = &socket[s].state.vg46x;
    i365_set(s, VG468_CTL, p->ctl);
    अगर (socket[s].type == IS_VG469)
	i365_set(s, VG469_EXT_MODE, p->ema);
पूर्ण

अटल u_पूर्णांक __init vg46x_set_opts(u_लघु s, अक्षर *buf)
अणु
    काष्ठा vg46x_state *p = &socket[s].state.vg46x;
    
    flip(p->ctl, VG468_CTL_ASYNC, async_घड़ी);
    flip(p->ema, VG469_MODE_CABLE, cable_mode);
    अगर (p->ctl & VG468_CTL_ASYNC)
	म_जोड़ो(buf, " [async]");
    अगर (p->ctl & VG468_CTL_INPACK)
	म_जोड़ो(buf, " [inpack]");
    अगर (socket[s].type == IS_VG469) अणु
	u_अक्षर vsel = i365_get(s, VG469_VSELECT);
	अगर (vsel & VG469_VSEL_EXT_STAT) अणु
	    म_जोड़ो(buf, " [ext mode]");
	    अगर (vsel & VG469_VSEL_EXT_BUS)
		म_जोड़ो(buf, " [isa buf]");
	पूर्ण
	अगर (p->ema & VG469_MODE_CABLE)
	    म_जोड़ो(buf, " [cable]");
	अगर (p->ema & VG469_MODE_COMPAT)
	    म_जोड़ो(buf, " [c step]");
    पूर्ण
    वापस 0xffff;
पूर्ण

/*======================================================================

    Generic routines to get and set controller options
    
======================================================================*/

अटल व्योम get_bridge_state(u_लघु s)
अणु
    काष्ठा i82365_socket *t = &socket[s];
    अगर (t->flags & IS_CIRRUS)
	cirrus_get_state(s);
    अन्यथा अगर (t->flags & IS_VADEM)
	vg46x_get_state(s);
पूर्ण

अटल व्योम set_bridge_state(u_लघु s)
अणु
    काष्ठा i82365_socket *t = &socket[s];
    अगर (t->flags & IS_CIRRUS)
	cirrus_set_state(s);
    अन्यथा अणु
	i365_set(s, I365_GBLCTL, 0x00);
	i365_set(s, I365_GENCTL, 0x00);
    पूर्ण
    i365_bflip(s, I365_INTCTL, I365_INTR_ENA, t->पूर्णांकr);
    अगर (t->flags & IS_VADEM)
	vg46x_set_state(s);
पूर्ण

अटल u_पूर्णांक __init set_bridge_opts(u_लघु s, u_लघु ns)
अणु
    u_लघु i;
    u_पूर्णांक m = 0xffff;
    अक्षर buf[128];

    क्रम (i = s; i < s+ns; i++) अणु
	अगर (socket[i].flags & IS_ALIVE) अणु
	    prपूर्णांकk(KERN_INFO "    host opts [%d]: already alive!\n", i);
	    जारी;
	पूर्ण
	buf[0] = '\0';
	get_bridge_state(i);
	अगर (socket[i].flags & IS_CIRRUS)
	    m = cirrus_set_opts(i, buf);
	अन्यथा अगर (socket[i].flags & IS_VADEM)
	    m = vg46x_set_opts(i, buf);
	set_bridge_state(i);
	prपूर्णांकk(KERN_INFO "    host opts [%d]:%s\n", i,
	       (*buf) ? buf : " none");
    पूर्ण
    वापस m;
पूर्ण

/*======================================================================

    Interrupt testing code, क्रम ISA and PCI पूर्णांकerrupts
    
======================================================================*/

अटल अस्थिर u_पूर्णांक irq_hits;
अटल u_लघु irq_sock;

अटल irqवापस_t i365_count_irq(पूर्णांक irq, व्योम *dev)
अणु
    i365_get(irq_sock, I365_CSC);
    irq_hits++;
    pr_debug("i82365: -> hit on irq %d\n", irq);
    वापस IRQ_HANDLED;
पूर्ण

अटल u_पूर्णांक __init test_irq(u_लघु sock, पूर्णांक irq)
अणु
    pr_debug("i82365:  testing ISA irq %d\n", irq);
    अगर (request_irq(irq, i365_count_irq, IRQF_PROBE_SHARED, "scan",
			i365_count_irq) != 0)
	वापस 1;
    irq_hits = 0; irq_sock = sock;
    msleep(10);
    अगर (irq_hits) अणु
	मुक्त_irq(irq, i365_count_irq);
	pr_debug("i82365:    spurious hit!\n");
	वापस 1;
    पूर्ण

    /* Generate one पूर्णांकerrupt */
    i365_set(sock, I365_CSCINT, I365_CSC_DETECT | (irq << 4));
    i365_bset(sock, I365_GENCTL, I365_CTL_SW_IRQ);
    udelay(1000);

    मुक्त_irq(irq, i365_count_irq);

    /* mask all पूर्णांकerrupts */
    i365_set(sock, I365_CSCINT, 0);
    pr_debug("i82365:    hits = %d\n", irq_hits);
    
    वापस (irq_hits != 1);
पूर्ण

अटल u_पूर्णांक __init isa_scan(u_लघु sock, u_पूर्णांक mask0)
अणु
    u_पूर्णांक mask1 = 0;
    पूर्णांक i;

#अगर_घोषित __alpha__
#घोषणा PIC 0x4d0
    /* Don't probe level-triggered पूर्णांकerrupts -- reserved क्रम PCI */
    mask0 &= ~(inb(PIC) | (inb(PIC+1) << 8));
#पूर्ण_अगर
    
    अगर (करो_scan) अणु
	set_bridge_state(sock);
	i365_set(sock, I365_CSCINT, 0);
	क्रम (i = 0; i < 16; i++)
	    अगर ((mask0 & (1 << i)) && (test_irq(sock, i) == 0))
		mask1 |= (1 << i);
	क्रम (i = 0; i < 16; i++)
	    अगर ((mask1 & (1 << i)) && (test_irq(sock, i) != 0))
		mask1 ^= (1 << i);
    पूर्ण
    
    prपूर्णांकk(KERN_INFO "    ISA irqs (");
    अगर (mask1) अणु
	prपूर्णांकk("scanned");
    पूर्ण अन्यथा अणु
	/* Fallback: just find पूर्णांकerrupts that aren't in use */
	क्रम (i = 0; i < 16; i++)
	    अगर ((mask0 & (1 << i)) && (_check_irq(i, IRQF_PROBE_SHARED) == 0))
		mask1 |= (1 << i);
	prपूर्णांकk("default");
	/* If scan failed, शेष to polled status */
	अगर (!cs_irq && (poll_पूर्णांकerval == 0)) poll_पूर्णांकerval = HZ;
    पूर्ण
    prपूर्णांकk(") = ");
    
    क्रम (i = 0; i < 16; i++)
	अगर (mask1 & (1<<i))
	    prपूर्णांकk("%s%d", ((mask1 & ((1<<i)-1)) ? "," : ""), i);
    अगर (mask1 == 0) prपूर्णांकk("none!");
    
    वापस mask1;
पूर्ण

/*====================================================================*/

/* Time conversion functions */

अटल पूर्णांक to_cycles(पूर्णांक ns)
अणु
    वापस ns/cycle_समय;
पूर्ण

/*====================================================================*/

अटल पूर्णांक __init identअगरy(अचिन्हित पूर्णांक port, u_लघु sock)
अणु
    u_अक्षर val;
    पूर्णांक type = -1;

    /* Use the next मुक्त entry in the socket table */
    socket[sockets].ioaddr = port;
    socket[sockets].psock = sock;
    
    /* Wake up a sleepy Cirrus controller */
    अगर (wakeup) अणु
	i365_bclr(sockets, PD67_MISC_CTL_2, PD67_MC2_SUSPEND);
	/* Pause at least 50 ms */
	mdelay(50);
    पूर्ण
    
    अगर ((val = i365_get(sockets, I365_IDENT)) & 0x70)
	वापस -1;
    चयन (val) अणु
    हाल 0x82:
	type = IS_I82365A; अवरोध;
    हाल 0x83:
	type = IS_I82365B; अवरोध;
    हाल 0x84:
	type = IS_I82365DF; अवरोध;
    हाल 0x88: हाल 0x89: हाल 0x8a:
	type = IS_IBM; अवरोध;
    पूर्ण
    
    /* Check क्रम Vadem VG-468 chips */
    outb(0x0e, port);
    outb(0x37, port);
    i365_bset(sockets, VG468_MISC, VG468_MISC_VADEMREV);
    val = i365_get(sockets, I365_IDENT);
    अगर (val & I365_IDENT_VADEM) अणु
	i365_bclr(sockets, VG468_MISC, VG468_MISC_VADEMREV);
	type = ((val & 7) >= 4) ? IS_VG469 : IS_VG468;
    पूर्ण

    /* Check क्रम Ricoh chips */
    val = i365_get(sockets, RF5C_CHIP_ID);
    अगर ((val == RF5C_CHIP_RF5C296) || (val == RF5C_CHIP_RF5C396))
	type = IS_RF5Cx96;
    
    /* Check क्रम Cirrus CL-PD67xx chips */
    i365_set(sockets, PD67_CHIP_INFO, 0);
    val = i365_get(sockets, PD67_CHIP_INFO);
    अगर ((val & PD67_INFO_CHIP_ID) == PD67_INFO_CHIP_ID) अणु
	val = i365_get(sockets, PD67_CHIP_INFO);
	अगर ((val & PD67_INFO_CHIP_ID) == 0) अणु
	    type = (val & PD67_INFO_SLOTS) ? IS_PD672X : IS_PD6710;
	    i365_set(sockets, PD67_EXT_INDEX, 0xe5);
	    अगर (i365_get(sockets, PD67_EXT_INDEX) != 0xe5)
		type = IS_VT83C469;
	पूर्ण
    पूर्ण
    वापस type;
पूर्ण /* identअगरy */

/*======================================================================

    See अगर a card is present, घातered up, in IO mode, and alपढ़ोy
    bound to a (non PC Card) Linux driver.  We leave these alone.

    We make an exception क्रम cards that seem to be serial devices.
    
======================================================================*/

अटल पूर्णांक __init is_alive(u_लघु sock)
अणु
    u_अक्षर stat;
    अचिन्हित पूर्णांक start, stop;
    
    stat = i365_get(sock, I365_STATUS);
    start = i365_get_pair(sock, I365_IO(0)+I365_W_START);
    stop = i365_get_pair(sock, I365_IO(0)+I365_W_STOP);
    अगर ((stat & I365_CS_DETECT) && (stat & I365_CS_POWERON) &&
	(i365_get(sock, I365_INTCTL) & I365_PC_IOCARD) &&
	(i365_get(sock, I365_ADDRWIN) & I365_ENA_IO(0)) &&
	((start & 0xfeef) != 0x02e8)) अणु
	अगर (!request_region(start, stop-start+1, "i82365"))
	    वापस 1;
	release_region(start, stop-start+1);
    पूर्ण

    वापस 0;
पूर्ण

/*====================================================================*/

अटल व्योम __init add_socket(अचिन्हित पूर्णांक port, पूर्णांक psock, पूर्णांक type)
अणु
    socket[sockets].ioaddr = port;
    socket[sockets].psock = psock;
    socket[sockets].type = type;
    socket[sockets].flags = pcic[type].flags;
    अगर (is_alive(sockets))
	socket[sockets].flags |= IS_ALIVE;
    sockets++;
पूर्ण

अटल व्योम __init add_pcic(पूर्णांक ns, पूर्णांक type)
अणु
    u_पूर्णांक mask = 0, i, base;
    पूर्णांक isa_irq = 0;
    काष्ठा i82365_socket *t = &socket[sockets-ns];

    base = sockets-ns;
    अगर (base == 0) prपूर्णांकk("\n");
    prपूर्णांकk(KERN_INFO "  %s", pcic[type].name);
    prपूर्णांकk(" ISA-to-PCMCIA at port %#x ofs 0x%02x",
	       t->ioaddr, t->psock*0x40);
    prपूर्णांकk(", %d socket%s\n", ns, ((ns > 1) ? "s" : ""));

    /* Set host options, build basic पूर्णांकerrupt mask */
    अगर (irq_list_count == 0)
	mask = irq_mask;
    अन्यथा
	क्रम (i = mask = 0; i < irq_list_count; i++)
	    mask |= (1<<irq_list[i]);
    mask &= I365_MASK & set_bridge_opts(base, ns);
    /* Scan क्रम ISA पूर्णांकerrupts */
    mask = isa_scan(base, mask);
        
    /* Poll अगर only two पूर्णांकerrupts available */
    अगर (!poll_पूर्णांकerval) अणु
	u_पूर्णांक पंचांगp = (mask & 0xff20);
	पंचांगp = पंचांगp & (पंचांगp-1);
	अगर ((पंचांगp & (पंचांगp-1)) == 0)
	    poll_पूर्णांकerval = HZ;
    पूर्ण
    /* Only try an ISA cs_irq अगर this is the first controller */
    अगर (!grab_irq && (cs_irq || !poll_पूर्णांकerval)) अणु
	/* Aव्योम irq 12 unless it is explicitly requested */
	u_पूर्णांक cs_mask = mask & ((cs_irq) ? (1<<cs_irq) : ~(1<<12));
	क्रम (cs_irq = 15; cs_irq > 0; cs_irq--)
	    अगर ((cs_mask & (1 << cs_irq)) &&
		(_check_irq(cs_irq, IRQF_PROBE_SHARED) == 0))
		अवरोध;
	अगर (cs_irq) अणु
	    grab_irq = 1;
	    isa_irq = cs_irq;
	    prपूर्णांकk(" status change on irq %d\n", cs_irq);
	पूर्ण
    पूर्ण
    
    अगर (!isa_irq) अणु
	अगर (poll_पूर्णांकerval == 0)
	    poll_पूर्णांकerval = HZ;
	prपूर्णांकk(" polling interval = %d ms\n",
	       poll_पूर्णांकerval * 1000 / HZ);
	
    पूर्ण
    
    /* Update socket पूर्णांकerrupt inक्रमmation, capabilities */
    क्रम (i = 0; i < ns; i++) अणु
	t[i].socket.features |= SS_CAP_PCCARD;
	t[i].socket.map_size = 0x1000;
	t[i].socket.irq_mask = mask;
	t[i].cs_irq = isa_irq;
    पूर्ण

पूर्ण /* add_pcic */

/*====================================================================*/

#अगर_घोषित CONFIG_PNP
अटल काष्ठा isapnp_device_id id_table[] __initdata = अणु
	अणु 	ISAPNP_ANY_ID, ISAPNP_ANY_ID, ISAPNP_VENDOR('P', 'N', 'P'),
		ISAPNP_FUNCTION(0x0e00), (अचिन्हित दीर्घ) "Intel 82365-Compatible" पूर्ण,
	अणु 	ISAPNP_ANY_ID, ISAPNP_ANY_ID, ISAPNP_VENDOR('P', 'N', 'P'),
		ISAPNP_FUNCTION(0x0e01), (अचिन्हित दीर्घ) "Cirrus Logic CL-PD6720" पूर्ण,
	अणु 	ISAPNP_ANY_ID, ISAPNP_ANY_ID, ISAPNP_VENDOR('P', 'N', 'P'),
		ISAPNP_FUNCTION(0x0e02), (अचिन्हित दीर्घ) "VLSI VL82C146" पूर्ण,
	अणु	0 पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(isapnp, id_table);

अटल काष्ठा pnp_dev *i82365_pnpdev;
#पूर्ण_अगर

अटल व्योम __init isa_probe(व्योम)
अणु
    पूर्णांक i, j, sock, k, ns, id;
    अचिन्हित पूर्णांक port;
#अगर_घोषित CONFIG_PNP
    काष्ठा isapnp_device_id *devid;
    काष्ठा pnp_dev *dev;

    क्रम (devid = id_table; devid->venकरोr; devid++) अणु
	अगर ((dev = pnp_find_dev(शून्य, devid->venकरोr, devid->function, शून्य))) अणु
	
	    अगर (pnp_device_attach(dev) < 0)
	    	जारी;

	    अगर (pnp_activate_dev(dev) < 0) अणु
		prपूर्णांकk("activate failed\n");
		pnp_device_detach(dev);
		अवरोध;
	    पूर्ण

	    अगर (!pnp_port_valid(dev, 0)) अणु
		prपूर्णांकk("invalid resources ?\n");
		pnp_device_detach(dev);
		अवरोध;
	    पूर्ण
	    i365_base = pnp_port_start(dev, 0);
	    i82365_pnpdev = dev;
	    अवरोध;
	पूर्ण
    पूर्ण
#पूर्ण_अगर

    अगर (!request_region(i365_base, 2, "i82365")) अणु
	अगर (sockets == 0)
	    prपूर्णांकk("port conflict at %#lx\n", i365_base);
	वापस;
    पूर्ण

    id = identअगरy(i365_base, 0);
    अगर ((id == IS_I82365DF) && (identअगरy(i365_base, 1) != id)) अणु
	क्रम (i = 0; i < 4; i++) अणु
	    अगर (i == ignore) जारी;
	    port = i365_base + ((i & 1) << 2) + ((i & 2) << 1);
	    sock = (i & 1) << 1;
	    अगर (identअगरy(port, sock) == IS_I82365DF) अणु
		add_socket(port, sock, IS_VLSI);
		add_pcic(1, IS_VLSI);
	    पूर्ण
	पूर्ण
    पूर्ण अन्यथा अणु
	क्रम (i = 0; i < 8; i += 2) अणु
	    अगर (sockets && !extra_sockets && (i == 4))
		अवरोध;
	    port = i365_base + 2*(i>>2);
	    sock = (i & 3);
	    id = identअगरy(port, sock);
	    अगर (id < 0) जारी;

	    क्रम (j = ns = 0; j < 2; j++) अणु
		/* Does the socket exist? */
		अगर ((ignore == i+j) || (identअगरy(port, sock+j) < 0))
		    जारी;
		/* Check क्रम bad socket decode */
		क्रम (k = 0; k <= sockets; k++)
		    i365_set(k, I365_MEM(0)+I365_W_OFF, k);
		क्रम (k = 0; k <= sockets; k++)
		    अगर (i365_get(k, I365_MEM(0)+I365_W_OFF) != k)
			अवरोध;
		अगर (k <= sockets) अवरोध;
		add_socket(port, sock+j, id); ns++;
	    पूर्ण
	    अगर (ns != 0) add_pcic(ns, id);
	पूर्ण
    पूर्ण
पूर्ण

/*====================================================================*/

अटल irqवापस_t pcic_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev)
अणु
    पूर्णांक i, j, csc;
    u_पूर्णांक events, active;
    u_दीर्घ flags = 0;
    पूर्णांक handled = 0;

    pr_debug("pcic_interrupt(%d)\n", irq);

    क्रम (j = 0; j < 20; j++) अणु
	active = 0;
	क्रम (i = 0; i < sockets; i++) अणु
	    अगर (socket[i].cs_irq != irq)
		जारी;
	    handled = 1;
	    ISA_LOCK(i, flags);
	    csc = i365_get(i, I365_CSC);
	    अगर ((csc == 0) || (i365_get(i, I365_IDENT) & 0x70)) अणु
		ISA_UNLOCK(i, flags);
		जारी;
	    पूर्ण
	    events = (csc & I365_CSC_DETECT) ? SS_DETECT : 0;

	    अगर (i365_get(i, I365_INTCTL) & I365_PC_IOCARD)
		events |= (csc & I365_CSC_STSCHG) ? SS_STSCHG : 0;
	    अन्यथा अणु
		events |= (csc & I365_CSC_BVD1) ? SS_BATDEAD : 0;
		events |= (csc & I365_CSC_BVD2) ? SS_BATWARN : 0;
		events |= (csc & I365_CSC_READY) ? SS_READY : 0;
	    पूर्ण
	    ISA_UNLOCK(i, flags);
	    pr_debug("socket %d event 0x%02x\n", i, events);

	    अगर (events)
		pcmcia_parse_events(&socket[i].socket, events);

	    active |= events;
	पूर्ण
	अगर (!active) अवरोध;
    पूर्ण
    अगर (j == 20)
	prपूर्णांकk(KERN_NOTICE "i82365: infinite loop in interrupt handler\n");

    pr_debug("pcic_interrupt done\n");
    वापस IRQ_RETVAL(handled);
पूर्ण /* pcic_पूर्णांकerrupt */

अटल व्योम pcic_पूर्णांकerrupt_wrapper(काष्ठा समयr_list *unused)
अणु
    pcic_पूर्णांकerrupt(0, शून्य);
    poll_समयr.expires = jअगरfies + poll_पूर्णांकerval;
    add_समयr(&poll_समयr);
पूर्ण

/*====================================================================*/

अटल पूर्णांक i365_get_status(u_लघु sock, u_पूर्णांक *value)
अणु
    u_पूर्णांक status;
    
    status = i365_get(sock, I365_STATUS);
    *value = ((status & I365_CS_DETECT) == I365_CS_DETECT)
	? SS_DETECT : 0;
	
    अगर (i365_get(sock, I365_INTCTL) & I365_PC_IOCARD)
	*value |= (status & I365_CS_STSCHG) ? 0 : SS_STSCHG;
    अन्यथा अणु
	*value |= (status & I365_CS_BVD1) ? 0 : SS_BATDEAD;
	*value |= (status & I365_CS_BVD2) ? 0 : SS_BATWARN;
    पूर्ण
    *value |= (status & I365_CS_WRPROT) ? SS_WRPROT : 0;
    *value |= (status & I365_CS_READY) ? SS_READY : 0;
    *value |= (status & I365_CS_POWERON) ? SS_POWERON : 0;

    अगर (socket[sock].type == IS_VG469) अणु
	status = i365_get(sock, VG469_VSENSE);
	अगर (socket[sock].psock & 1) अणु
	    *value |= (status & VG469_VSENSE_B_VS1) ? 0 : SS_3VCARD;
	    *value |= (status & VG469_VSENSE_B_VS2) ? 0 : SS_XVCARD;
	पूर्ण अन्यथा अणु
	    *value |= (status & VG469_VSENSE_A_VS1) ? 0 : SS_3VCARD;
	    *value |= (status & VG469_VSENSE_A_VS2) ? 0 : SS_XVCARD;
	पूर्ण
    पूर्ण
    
    pr_debug("GetStatus(%d) = %#4.4x\n", sock, *value);
    वापस 0;
पूर्ण /* i365_get_status */

/*====================================================================*/

अटल पूर्णांक i365_set_socket(u_लघु sock, socket_state_t *state)
अणु
    काष्ठा i82365_socket *t = &socket[sock];
    u_अक्षर reg;
    
    pr_debug("SetSocket(%d, flags %#3.3x, Vcc %d, Vpp %d, "
	  "io_irq %d, csc_mask %#2.2x)\n", sock, state->flags,
	  state->Vcc, state->Vpp, state->io_irq, state->csc_mask);
    
    /* First set global controller options */
    set_bridge_state(sock);
    
    /* IO card, RESET flag, IO पूर्णांकerrupt */
    reg = t->पूर्णांकr;
    reg |= state->io_irq;
    reg |= (state->flags & SS_RESET) ? 0 : I365_PC_RESET;
    reg |= (state->flags & SS_IOCARD) ? I365_PC_IOCARD : 0;
    i365_set(sock, I365_INTCTL, reg);
    
    reg = I365_PWR_NORESET;
    अगर (state->flags & SS_PWR_AUTO) reg |= I365_PWR_AUTO;
    अगर (state->flags & SS_OUTPUT_ENA) reg |= I365_PWR_OUT;

    अगर (t->flags & IS_CIRRUS) अणु
	अगर (state->Vpp != 0) अणु
	    अगर (state->Vpp == 120)
		reg |= I365_VPP1_12V;
	    अन्यथा अगर (state->Vpp == state->Vcc)
		reg |= I365_VPP1_5V;
	    अन्यथा वापस -EINVAL;
	पूर्ण
	अगर (state->Vcc != 0) अणु
	    reg |= I365_VCC_5V;
	    अगर (state->Vcc == 33)
		i365_bset(sock, PD67_MISC_CTL_1, PD67_MC1_VCC_3V);
	    अन्यथा अगर (state->Vcc == 50)
		i365_bclr(sock, PD67_MISC_CTL_1, PD67_MC1_VCC_3V);
	    अन्यथा वापस -EINVAL;
	पूर्ण
    पूर्ण अन्यथा अगर (t->flags & IS_VG_PWR) अणु
	अगर (state->Vpp != 0) अणु
	    अगर (state->Vpp == 120)
		reg |= I365_VPP1_12V;
	    अन्यथा अगर (state->Vpp == state->Vcc)
		reg |= I365_VPP1_5V;
	    अन्यथा वापस -EINVAL;
	पूर्ण
	अगर (state->Vcc != 0) अणु
	    reg |= I365_VCC_5V;
	    अगर (state->Vcc == 33)
		i365_bset(sock, VG469_VSELECT, VG469_VSEL_VCC);
	    अन्यथा अगर (state->Vcc == 50)
		i365_bclr(sock, VG469_VSELECT, VG469_VSEL_VCC);
	    अन्यथा वापस -EINVAL;
	पूर्ण
    पूर्ण अन्यथा अगर (t->flags & IS_DF_PWR) अणु
	चयन (state->Vcc) अणु
	हाल 0:		अवरोध;
	हाल 33:   	reg |= I365_VCC_3V; अवरोध;
	हाल 50:	reg |= I365_VCC_5V; अवरोध;
	शेष:	वापस -EINVAL;
	पूर्ण
	चयन (state->Vpp) अणु
	हाल 0:		अवरोध;
	हाल 50:   	reg |= I365_VPP1_5V; अवरोध;
	हाल 120:	reg |= I365_VPP1_12V; अवरोध;
	शेष:	वापस -EINVAL;
	पूर्ण
    पूर्ण अन्यथा अणु
	चयन (state->Vcc) अणु
	हाल 0:		अवरोध;
	हाल 50:	reg |= I365_VCC_5V; अवरोध;
	शेष:	वापस -EINVAL;
	पूर्ण
	चयन (state->Vpp) अणु
	हाल 0:		अवरोध;
	हाल 50:	reg |= I365_VPP1_5V | I365_VPP2_5V; अवरोध;
	हाल 120:	reg |= I365_VPP1_12V | I365_VPP2_12V; अवरोध;
	शेष:	वापस -EINVAL;
	पूर्ण
    पूर्ण
    
    अगर (reg != i365_get(sock, I365_POWER))
	i365_set(sock, I365_POWER, reg);

    /* Chipset-specअगरic functions */
    अगर (t->flags & IS_CIRRUS) अणु
	/* Speaker control */
	i365_bflip(sock, PD67_MISC_CTL_1, PD67_MC1_SPKR_ENA,
		   state->flags & SS_SPKR_ENA);
    पूर्ण
    
    /* Card status change पूर्णांकerrupt mask */
    reg = t->cs_irq << 4;
    अगर (state->csc_mask & SS_DETECT) reg |= I365_CSC_DETECT;
    अगर (state->flags & SS_IOCARD) अणु
	अगर (state->csc_mask & SS_STSCHG) reg |= I365_CSC_STSCHG;
    पूर्ण अन्यथा अणु
	अगर (state->csc_mask & SS_BATDEAD) reg |= I365_CSC_BVD1;
	अगर (state->csc_mask & SS_BATWARN) reg |= I365_CSC_BVD2;
	अगर (state->csc_mask & SS_READY) reg |= I365_CSC_READY;
    पूर्ण
    i365_set(sock, I365_CSCINT, reg);
    i365_get(sock, I365_CSC);
    
    वापस 0;
पूर्ण /* i365_set_socket */

/*====================================================================*/

अटल पूर्णांक i365_set_io_map(u_लघु sock, काष्ठा pccard_io_map *io)
अणु
    u_अक्षर map, ioctl;
    
    pr_debug("SetIOMap(%d, %d, %#2.2x, %d ns, "
	  "%#llx-%#llx)\n", sock, io->map, io->flags, io->speed,
	  (अचिन्हित दीर्घ दीर्घ)io->start, (अचिन्हित दीर्घ दीर्घ)io->stop);
    map = io->map;
    अगर ((map > 1) || (io->start > 0xffff) || (io->stop > 0xffff) ||
	(io->stop < io->start)) वापस -EINVAL;
    /* Turn off the winकरोw beक्रमe changing anything */
    अगर (i365_get(sock, I365_ADDRWIN) & I365_ENA_IO(map))
	i365_bclr(sock, I365_ADDRWIN, I365_ENA_IO(map));
    i365_set_pair(sock, I365_IO(map)+I365_W_START, io->start);
    i365_set_pair(sock, I365_IO(map)+I365_W_STOP, io->stop);
    ioctl = i365_get(sock, I365_IOCTL) & ~I365_IOCTL_MASK(map);
    अगर (io->speed) ioctl |= I365_IOCTL_WAIT(map);
    अगर (io->flags & MAP_0WS) ioctl |= I365_IOCTL_0WS(map);
    अगर (io->flags & MAP_16BIT) ioctl |= I365_IOCTL_16BIT(map);
    अगर (io->flags & MAP_AUTOSZ) ioctl |= I365_IOCTL_IOCS16(map);
    i365_set(sock, I365_IOCTL, ioctl);
    /* Turn on the winकरोw अगर necessary */
    अगर (io->flags & MAP_ACTIVE)
	i365_bset(sock, I365_ADDRWIN, I365_ENA_IO(map));
    वापस 0;
पूर्ण /* i365_set_io_map */

/*====================================================================*/

अटल पूर्णांक i365_set_mem_map(u_लघु sock, काष्ठा pccard_mem_map *mem)
अणु
    u_लघु base, i;
    u_अक्षर map;
    
    pr_debug("SetMemMap(%d, %d, %#2.2x, %d ns, %#llx-%#llx, "
	  "%#x)\n", sock, mem->map, mem->flags, mem->speed,
	  (अचिन्हित दीर्घ दीर्घ)mem->res->start,
	  (अचिन्हित दीर्घ दीर्घ)mem->res->end, mem->card_start);

    map = mem->map;
    अगर ((map > 4) || (mem->card_start > 0x3ffffff) ||
	(mem->res->start > mem->res->end) || (mem->speed > 1000))
	वापस -EINVAL;
    अगर ((mem->res->start > 0xffffff) || (mem->res->end > 0xffffff))
	वापस -EINVAL;
	
    /* Turn off the winकरोw beक्रमe changing anything */
    अगर (i365_get(sock, I365_ADDRWIN) & I365_ENA_MEM(map))
	i365_bclr(sock, I365_ADDRWIN, I365_ENA_MEM(map));
    
    base = I365_MEM(map);
    i = (mem->res->start >> 12) & 0x0fff;
    अगर (mem->flags & MAP_16BIT) i |= I365_MEM_16BIT;
    अगर (mem->flags & MAP_0WS) i |= I365_MEM_0WS;
    i365_set_pair(sock, base+I365_W_START, i);
    
    i = (mem->res->end >> 12) & 0x0fff;
    चयन (to_cycles(mem->speed)) अणु
    हाल 0:	अवरोध;
    हाल 1:	i |= I365_MEM_WS0; अवरोध;
    हाल 2:	i |= I365_MEM_WS1; अवरोध;
    शेष:	i |= I365_MEM_WS1 | I365_MEM_WS0; अवरोध;
    पूर्ण
    i365_set_pair(sock, base+I365_W_STOP, i);
    
    i = ((mem->card_start - mem->res->start) >> 12) & 0x3fff;
    अगर (mem->flags & MAP_WRPROT) i |= I365_MEM_WRPROT;
    अगर (mem->flags & MAP_ATTRIB) i |= I365_MEM_REG;
    i365_set_pair(sock, base+I365_W_OFF, i);
    
    /* Turn on the winकरोw अगर necessary */
    अगर (mem->flags & MAP_ACTIVE)
	i365_bset(sock, I365_ADDRWIN, I365_ENA_MEM(map));
    वापस 0;
पूर्ण /* i365_set_mem_map */

#अगर 0 /* driver model ordering issue */
/*======================================================================

    Routines क्रम accessing socket inक्रमmation and रेजिस्टर dumps via
    /sys/class/pcmcia_socket/...
    
======================================================================*/

अटल sमाप_प्रकार show_info(काष्ठा class_device *class_dev, अक्षर *buf)
अणु
	काष्ठा i82365_socket *s = container_of(class_dev, काष्ठा i82365_socket, socket.dev);
	वापस प्र_लिखो(buf, "type:     %s\npsock:    %d\n",
		       pcic[s->type].name, s->psock);
पूर्ण

अटल sमाप_प्रकार show_exca(काष्ठा class_device *class_dev, अक्षर *buf)
अणु
	काष्ठा i82365_socket *s = container_of(class_dev, काष्ठा i82365_socket, socket.dev);
	अचिन्हित लघु sock;
	पूर्णांक i;
	sमाप_प्रकार ret = 0;
	अचिन्हित दीर्घ flags = 0;

	sock = s->number;

	ISA_LOCK(sock, flags);
	क्रम (i = 0; i < 0x40; i += 4) अणु
		ret += प्र_लिखो(buf, "%02x %02x %02x %02x%s",
			       i365_get(sock,i), i365_get(sock,i+1),
			       i365_get(sock,i+2), i365_get(sock,i+3),
			       ((i % 16) == 12) ? "\n" : " ");
		buf += ret;
	पूर्ण
	ISA_UNLOCK(sock, flags);

	वापस ret;
पूर्ण

अटल CLASS_DEVICE_ATTR(exca, S_IRUGO, show_exca, शून्य);
अटल CLASS_DEVICE_ATTR(info, S_IRUGO, show_info, शून्य);
#पूर्ण_अगर

/*====================================================================*/

/* this is horribly ugly... proper locking needs to be करोne here at 
 * some समय... */
#घोषणा LOCKED(x) करो अणु \
	पूर्णांक retval; \
	अचिन्हित दीर्घ flags; \
	spin_lock_irqsave(&isa_lock, flags); \
	retval = x; \
	spin_unlock_irqrestore(&isa_lock, flags); \
	वापस retval; \
पूर्ण जबतक (0)
	

अटल पूर्णांक pcic_get_status(काष्ठा pcmcia_socket *s, u_पूर्णांक *value)
अणु
	अचिन्हित पूर्णांक sock = container_of(s, काष्ठा i82365_socket, socket)->number;

	अगर (socket[sock].flags & IS_ALIVE) अणु
		*value = 0;
		वापस -EINVAL;
	पूर्ण

	LOCKED(i365_get_status(sock, value));
पूर्ण

अटल पूर्णांक pcic_set_socket(काष्ठा pcmcia_socket *s, socket_state_t *state)
अणु
	अचिन्हित पूर्णांक sock = container_of(s, काष्ठा i82365_socket, socket)->number;

	अगर (socket[sock].flags & IS_ALIVE)
		वापस -EINVAL;

	LOCKED(i365_set_socket(sock, state));
पूर्ण

अटल पूर्णांक pcic_set_io_map(काष्ठा pcmcia_socket *s, काष्ठा pccard_io_map *io)
अणु
	अचिन्हित पूर्णांक sock = container_of(s, काष्ठा i82365_socket, socket)->number;
	अगर (socket[sock].flags & IS_ALIVE)
		वापस -EINVAL;

	LOCKED(i365_set_io_map(sock, io));
पूर्ण

अटल पूर्णांक pcic_set_mem_map(काष्ठा pcmcia_socket *s, काष्ठा pccard_mem_map *mem)
अणु
	अचिन्हित पूर्णांक sock = container_of(s, काष्ठा i82365_socket, socket)->number;
	अगर (socket[sock].flags & IS_ALIVE)
		वापस -EINVAL;

	LOCKED(i365_set_mem_map(sock, mem));
पूर्ण

अटल पूर्णांक pcic_init(काष्ठा pcmcia_socket *s)
अणु
	पूर्णांक i;
	काष्ठा resource res = अणु .start = 0, .end = 0x1000 पूर्ण;
	pccard_io_map io = अणु 0, 0, 0, 0, 1 पूर्ण;
	pccard_mem_map mem = अणु .res = &res, पूर्ण;

	क्रम (i = 0; i < 2; i++) अणु
		io.map = i;
		pcic_set_io_map(s, &io);
	पूर्ण
	क्रम (i = 0; i < 5; i++) अणु
		mem.map = i;
		pcic_set_mem_map(s, &mem);
	पूर्ण
	वापस 0;
पूर्ण


अटल काष्ठा pccard_operations pcic_operations = अणु
	.init			= pcic_init,
	.get_status		= pcic_get_status,
	.set_socket		= pcic_set_socket,
	.set_io_map		= pcic_set_io_map,
	.set_mem_map		= pcic_set_mem_map,
पूर्ण;

/*====================================================================*/

अटल काष्ठा platक्रमm_driver i82365_driver = अणु
	.driver = अणु
		.name = "i82365",
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device *i82365_device;

अटल पूर्णांक __init init_i82365(व्योम)
अणु
    पूर्णांक i, ret;

    ret = platक्रमm_driver_रेजिस्टर(&i82365_driver);
    अगर (ret)
	जाओ err_out;

    i82365_device = platक्रमm_device_alloc("i82365", 0);
    अगर (i82365_device) अणु
	    ret = platक्रमm_device_add(i82365_device);
	    अगर (ret)
		    platक्रमm_device_put(i82365_device);
    पूर्ण अन्यथा
	    ret = -ENOMEM;

    अगर (ret)
	जाओ err_driver_unरेजिस्टर;

    prपूर्णांकk(KERN_INFO "Intel ISA PCIC probe: ");
    sockets = 0;

    isa_probe();

    अगर (sockets == 0) अणु
	prपूर्णांकk("not found.\n");
	ret = -ENODEV;
	जाओ err_dev_unरेजिस्टर;
    पूर्ण

    /* Set up पूर्णांकerrupt handler(s) */
    अगर (grab_irq != 0)
	ret = request_irq(cs_irq, pcic_पूर्णांकerrupt, 0, "i82365", pcic_पूर्णांकerrupt);

    अगर (ret)
	जाओ err_socket_release;

    /* रेजिस्टर sockets with the pcmcia core */
    क्रम (i = 0; i < sockets; i++) अणु
	    socket[i].socket.dev.parent = &i82365_device->dev;
	    socket[i].socket.ops = &pcic_operations;
	    socket[i].socket.resource_ops = &pccard_nonअटल_ops;
	    socket[i].socket.owner = THIS_MODULE;
	    socket[i].number = i;
	    ret = pcmcia_रेजिस्टर_socket(&socket[i].socket);
	    अगर (!ret)
		    socket[i].flags |= IS_REGISTERED;
    पूर्ण

    /* Finally, schedule a polling पूर्णांकerrupt */
    अगर (poll_पूर्णांकerval != 0) अणु
	समयr_setup(&poll_समयr, pcic_पूर्णांकerrupt_wrapper, 0);
    	poll_समयr.expires = jअगरfies + poll_पूर्णांकerval;
	add_समयr(&poll_समयr);
    पूर्ण
    
    वापस 0;
err_socket_release:
    क्रम (i = 0; i < sockets; i++) अणु
	/* Turn off all पूर्णांकerrupt sources! */
	i365_set(i, I365_CSCINT, 0);
	release_region(socket[i].ioaddr, 2);
    पूर्ण
err_dev_unरेजिस्टर:
    platक्रमm_device_unरेजिस्टर(i82365_device);
    release_region(i365_base, 2);
#अगर_घोषित CONFIG_PNP
    अगर (i82365_pnpdev)
	pnp_disable_dev(i82365_pnpdev);
#पूर्ण_अगर
err_driver_unरेजिस्टर:
    platक्रमm_driver_unरेजिस्टर(&i82365_driver);
err_out:
    वापस ret;
पूर्ण /* init_i82365 */

अटल व्योम __निकास निकास_i82365(व्योम)
अणु
    पूर्णांक i;

    क्रम (i = 0; i < sockets; i++) अणु
	    अगर (socket[i].flags & IS_REGISTERED)
		    pcmcia_unरेजिस्टर_socket(&socket[i].socket);
    पूर्ण
    platक्रमm_device_unरेजिस्टर(i82365_device);
    अगर (poll_पूर्णांकerval != 0)
	del_समयr_sync(&poll_समयr);
    अगर (grab_irq != 0)
	मुक्त_irq(cs_irq, pcic_पूर्णांकerrupt);
    क्रम (i = 0; i < sockets; i++) अणु
	/* Turn off all पूर्णांकerrupt sources! */
	i365_set(i, I365_CSCINT, 0);
	release_region(socket[i].ioaddr, 2);
    पूर्ण
    release_region(i365_base, 2);
#अगर_घोषित CONFIG_PNP
    अगर (i82365_pnpdev)
    		pnp_disable_dev(i82365_pnpdev);
#पूर्ण_अगर
    platक्रमm_driver_unरेजिस्टर(&i82365_driver);
पूर्ण /* निकास_i82365 */

module_init(init_i82365);
module_निकास(निकास_i82365);
MODULE_LICENSE("Dual MPL/GPL");
/*====================================================================*/
