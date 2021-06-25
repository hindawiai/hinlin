<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Low-level parallel port routines क्रम the Amiga built-in port
 *
 * Author: Joerg Dorchain <joerg@करोrchain.net>
 *
 * This is a complete reग_लिखो of the code, but based heaviy upon the old
 * lp_पूर्णांकern. code.
 *
 * The built-in Amiga parallel port provides one port at a fixed address
 * with 8 bidirectional data lines (D0 - D7) and 3 bidirectional status
 * lines (BUSY, POUT, SEL), 1 output control line /STROBE (उठाओd स्वतःmatically
 * in hardware when the data रेजिस्टर is accessed), and 1 input control line
 * /ACK, able to cause an पूर्णांकerrupt, but both not directly settable by
 * software.
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/parport.h>
#समावेश <linux/ioport.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/amigahw.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/amigaपूर्णांकs.h>

#अघोषित DEBUG

अटल व्योम amiga_ग_लिखो_data(काष्ठा parport *p, अचिन्हित अक्षर data)
अणु
	pr_debug("write_data %c\n", data);
	/* Triggers also /STROBE. This behavior cannot be changed */
	ciaa.prb = data;
	mb();
पूर्ण

अटल अचिन्हित अक्षर amiga_पढ़ो_data(काष्ठा parport *p)
अणु
	/* Triggers also /STROBE. This behavior cannot be changed */
	वापस ciaa.prb;
पूर्ण

अटल अचिन्हित अक्षर control_amiga_to_pc(अचिन्हित अक्षर control)
अणु
	वापस PARPORT_CONTROL_SELECT |
	      PARPORT_CONTROL_AUTOFD | PARPORT_CONTROL_STROBE;
	/* fake value: पूर्णांकerrupt enable, select in, no reset,
	no स्वतःlf, no strobe - seems to be बंदst the wiring diagram */
पूर्ण

अटल व्योम amiga_ग_लिखो_control(काष्ठा parport *p, अचिन्हित अक्षर control)
अणु
	pr_debug("write_control %02x\n", control);
	/* No implementation possible */
पूर्ण
	
अटल अचिन्हित अक्षर amiga_पढ़ो_control( काष्ठा parport *p)
अणु
	pr_debug("read_control\n");
	वापस control_amiga_to_pc(0);
पूर्ण

अटल अचिन्हित अक्षर amiga_frob_control( काष्ठा parport *p, अचिन्हित अक्षर mask, अचिन्हित अक्षर val)
अणु
	अचिन्हित अक्षर old;

	pr_debug("frob_control mask %02x, value %02x\n", mask, val);
	old = amiga_पढ़ो_control(p);
	amiga_ग_लिखो_control(p, (old & ~mask) ^ val);
	वापस old;
पूर्ण

अटल अचिन्हित अक्षर status_amiga_to_pc(अचिन्हित अक्षर status)
अणु
	अचिन्हित अक्षर ret = PARPORT_STATUS_BUSY | PARPORT_STATUS_ACK | PARPORT_STATUS_ERROR;

	अगर (status & 1) /* Busy */
		ret &= ~PARPORT_STATUS_BUSY;
	अगर (status & 2) /* PaperOut */
		ret |= PARPORT_STATUS_PAPEROUT;
	अगर (status & 4) /* Selected */
		ret |= PARPORT_STATUS_SELECT;
	/* the rest is not connected or handled स्वतःnomously in hardware */

	वापस ret;
पूर्ण

अटल अचिन्हित अक्षर amiga_पढ़ो_status(काष्ठा parport *p)
अणु
	अचिन्हित अक्षर status;

	status = status_amiga_to_pc(ciab.pra & 7);
	pr_debug("read_status %02x\n", status);
	वापस status;
पूर्ण

अटल व्योम amiga_enable_irq(काष्ठा parport *p)
अणु
	enable_irq(IRQ_AMIGA_CIAA_FLG);
पूर्ण

अटल व्योम amiga_disable_irq(काष्ठा parport *p)
अणु
	disable_irq(IRQ_AMIGA_CIAA_FLG);
पूर्ण

अटल व्योम amiga_data_क्रमward(काष्ठा parport *p)
अणु
	pr_debug("forward\n");
	ciaa.ddrb = 0xff; /* all pins output */
	mb();
पूर्ण

अटल व्योम amiga_data_reverse(काष्ठा parport *p)
अणु
	pr_debug("reverse\n");
	ciaa.ddrb = 0; /* all pins input */
	mb();
पूर्ण

अटल व्योम amiga_init_state(काष्ठा pardevice *dev, काष्ठा parport_state *s)
अणु
	s->u.amiga.data = 0;
	s->u.amiga.datadir = 255;
	s->u.amiga.status = 0;
	s->u.amiga.statusdir = 0;
पूर्ण

अटल व्योम amiga_save_state(काष्ठा parport *p, काष्ठा parport_state *s)
अणु
	mb();
	s->u.amiga.data = ciaa.prb;
	s->u.amiga.datadir = ciaa.ddrb;
	s->u.amiga.status = ciab.pra & 7;
	s->u.amiga.statusdir = ciab.ddra & 7;
	mb();
पूर्ण

अटल व्योम amiga_restore_state(काष्ठा parport *p, काष्ठा parport_state *s)
अणु
	mb();
	ciaa.prb = s->u.amiga.data;
	ciaa.ddrb = s->u.amiga.datadir;
	ciab.pra |= (ciab.pra & 0xf8) | s->u.amiga.status;
	ciab.ddra |= (ciab.ddra & 0xf8) | s->u.amiga.statusdir;
	mb();
पूर्ण

अटल काष्ठा parport_operations pp_amiga_ops = अणु
	.ग_लिखो_data	= amiga_ग_लिखो_data,
	.पढ़ो_data	= amiga_पढ़ो_data,

	.ग_लिखो_control	= amiga_ग_लिखो_control,
	.पढ़ो_control	= amiga_पढ़ो_control,
	.frob_control	= amiga_frob_control,

	.पढ़ो_status	= amiga_पढ़ो_status,

	.enable_irq	= amiga_enable_irq,
	.disable_irq	= amiga_disable_irq,

	.data_क्रमward	= amiga_data_क्रमward,
	.data_reverse	= amiga_data_reverse,

	.init_state	= amiga_init_state,
	.save_state	= amiga_save_state,
	.restore_state	= amiga_restore_state,

	.epp_ग_लिखो_data	= parport_ieee1284_epp_ग_लिखो_data,
	.epp_पढ़ो_data	= parport_ieee1284_epp_पढ़ो_data,
	.epp_ग_लिखो_addr	= parport_ieee1284_epp_ग_लिखो_addr,
	.epp_पढ़ो_addr	= parport_ieee1284_epp_पढ़ो_addr,

	.ecp_ग_लिखो_data	= parport_ieee1284_ecp_ग_लिखो_data,
	.ecp_पढ़ो_data	= parport_ieee1284_ecp_पढ़ो_data,
	.ecp_ग_लिखो_addr	= parport_ieee1284_ecp_ग_लिखो_addr,

	.compat_ग_लिखो_data	= parport_ieee1284_ग_लिखो_compat,
	.nibble_पढ़ो_data	= parport_ieee1284_पढ़ो_nibble,
	.byte_पढ़ो_data		= parport_ieee1284_पढ़ो_byte,

	.owner		= THIS_MODULE,
पूर्ण;

/* ----------- Initialisation code --------------------------------- */

अटल पूर्णांक __init amiga_parallel_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा parport *p;
	पूर्णांक err;

	ciaa.ddrb = 0xff;
	ciab.ddra &= 0xf8;
	mb();

	p = parport_रेजिस्टर_port((अचिन्हित दीर्घ)&ciaa.prb, IRQ_AMIGA_CIAA_FLG,
				   PARPORT_DMA_NONE, &pp_amiga_ops);
	अगर (!p)
		वापस -EBUSY;

	err = request_irq(IRQ_AMIGA_CIAA_FLG, parport_irq_handler, 0, p->name,
			  p);
	अगर (err)
		जाओ out_irq;

	pr_info("%s: Amiga built-in port using irq\n", p->name);
	/* XXX: set operating mode */
	parport_announce_port(p);

	platक्रमm_set_drvdata(pdev, p);

	वापस 0;

out_irq:
	parport_put_port(p);
	वापस err;
पूर्ण

अटल पूर्णांक __निकास amiga_parallel_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा parport *port = platक्रमm_get_drvdata(pdev);

	parport_हटाओ_port(port);
	अगर (port->irq != PARPORT_IRQ_NONE)
		मुक्त_irq(IRQ_AMIGA_CIAA_FLG, port);
	parport_put_port(port);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver amiga_parallel_driver = अणु
	.हटाओ = __निकास_p(amiga_parallel_हटाओ),
	.driver   = अणु
		.name	= "amiga-parallel",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver_probe(amiga_parallel_driver, amiga_parallel_probe);

MODULE_AUTHOR("Joerg Dorchain <joerg@dorchain.net>");
MODULE_DESCRIPTION("Parport Driver for Amiga builtin Port");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:amiga-parallel");
