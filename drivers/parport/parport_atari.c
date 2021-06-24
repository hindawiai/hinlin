<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Low-level parallel port routines क्रम the Atari builtin port
 *
 * Author: Andreas Schwab <schwab@issan.inक्रमmatik.uni-करोrपंचांगund.de>
 *
 * Based on parport_amiga.c.
 *
 * The built-in Atari parallel port provides one port at a fixed address
 * with 8 output data lines (D0 - D7), 1 output control line (STROBE)
 * and 1 input status line (BUSY) able to cause an पूर्णांकerrupt.
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/parport.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/atarihw.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/atariपूर्णांकs.h>

अटल काष्ठा parport *this_port;

अटल अचिन्हित अक्षर
parport_atari_पढ़ो_data(काष्ठा parport *p)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर data;

	local_irq_save(flags);
	sound_ym.rd_data_reg_sel = 15;
	data = sound_ym.rd_data_reg_sel;
	local_irq_restore(flags);
	वापस data;
पूर्ण

अटल व्योम
parport_atari_ग_लिखो_data(काष्ठा parport *p, अचिन्हित अक्षर data)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	sound_ym.rd_data_reg_sel = 15;
	sound_ym.wd_data = data;
	local_irq_restore(flags);
पूर्ण

अटल अचिन्हित अक्षर
parport_atari_पढ़ो_control(काष्ठा parport *p)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर control = 0;

	local_irq_save(flags);
	sound_ym.rd_data_reg_sel = 14;
	अगर (!(sound_ym.rd_data_reg_sel & (1 << 5)))
		control = PARPORT_CONTROL_STROBE;
	local_irq_restore(flags);
	वापस control;
पूर्ण

अटल व्योम
parport_atari_ग_लिखो_control(काष्ठा parport *p, अचिन्हित अक्षर control)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	sound_ym.rd_data_reg_sel = 14;
	अगर (control & PARPORT_CONTROL_STROBE)
		sound_ym.wd_data = sound_ym.rd_data_reg_sel & ~(1 << 5);
	अन्यथा
		sound_ym.wd_data = sound_ym.rd_data_reg_sel | (1 << 5);
	local_irq_restore(flags);
पूर्ण

अटल अचिन्हित अक्षर
parport_atari_frob_control(काष्ठा parport *p, अचिन्हित अक्षर mask,
			   अचिन्हित अक्षर val)
अणु
	अचिन्हित अक्षर old = parport_atari_पढ़ो_control(p);
	parport_atari_ग_लिखो_control(p, (old & ~mask) ^ val);
	वापस old;
पूर्ण

अटल अचिन्हित अक्षर
parport_atari_पढ़ो_status(काष्ठा parport *p)
अणु
	वापस ((st_mfp.par_dt_reg & 1 ? 0 : PARPORT_STATUS_BUSY) |
		PARPORT_STATUS_SELECT | PARPORT_STATUS_ERROR);
पूर्ण

अटल व्योम
parport_atari_init_state(काष्ठा pardevice *d, काष्ठा parport_state *s)
अणु
पूर्ण

अटल व्योम
parport_atari_save_state(काष्ठा parport *p, काष्ठा parport_state *s)
अणु
पूर्ण

अटल व्योम
parport_atari_restore_state(काष्ठा parport *p, काष्ठा parport_state *s)
अणु
पूर्ण

अटल व्योम
parport_atari_enable_irq(काष्ठा parport *p)
अणु
	enable_irq(IRQ_MFP_BUSY);
पूर्ण

अटल व्योम
parport_atari_disable_irq(काष्ठा parport *p)
अणु
	disable_irq(IRQ_MFP_BUSY);
पूर्ण

अटल व्योम
parport_atari_data_क्रमward(काष्ठा parport *p)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	/* Soundchip port B as output. */
	sound_ym.rd_data_reg_sel = 7;
	sound_ym.wd_data = sound_ym.rd_data_reg_sel | 0x40;
	local_irq_restore(flags);
पूर्ण

अटल व्योम
parport_atari_data_reverse(काष्ठा parport *p)
अणु
पूर्ण

अटल काष्ठा parport_operations parport_atari_ops = अणु
	.ग_लिखो_data	= parport_atari_ग_लिखो_data,
	.पढ़ो_data	= parport_atari_पढ़ो_data,

	.ग_लिखो_control	= parport_atari_ग_लिखो_control,
	.पढ़ो_control	= parport_atari_पढ़ो_control,
	.frob_control	= parport_atari_frob_control,

	.पढ़ो_status	= parport_atari_पढ़ो_status,

	.enable_irq	= parport_atari_enable_irq,
	.disable_irq	= parport_atari_disable_irq,

	.data_क्रमward	= parport_atari_data_क्रमward,
	.data_reverse	= parport_atari_data_reverse,

	.init_state	= parport_atari_init_state,
	.save_state	= parport_atari_save_state,
	.restore_state	= parport_atari_restore_state,

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


अटल पूर्णांक __init parport_atari_init(व्योम)
अणु
	काष्ठा parport *p;
	अचिन्हित दीर्घ flags;

	अगर (MACH_IS_ATARI) अणु
		local_irq_save(flags);
		/* Soundchip port A/B as output. */
		sound_ym.rd_data_reg_sel = 7;
		sound_ym.wd_data = (sound_ym.rd_data_reg_sel & 0x3f) | 0xc0;
		/* STROBE high. */
		sound_ym.rd_data_reg_sel = 14;
		sound_ym.wd_data = sound_ym.rd_data_reg_sel | (1 << 5);
		local_irq_restore(flags);
		/* MFP port I0 as input. */
		st_mfp.data_dir &= ~1;
		/* MFP port I0 पूर्णांकerrupt on high->low edge. */
		st_mfp.active_edge &= ~1;
		p = parport_रेजिस्टर_port((अचिन्हित दीर्घ)&sound_ym.wd_data,
					  IRQ_MFP_BUSY, PARPORT_DMA_NONE,
					  &parport_atari_ops);
		अगर (!p)
			वापस -ENODEV;
		अगर (request_irq(IRQ_MFP_BUSY, parport_irq_handler, 0, p->name,
				p)) अणु
			parport_put_port (p);
			वापस -ENODEV;
		पूर्ण

		this_port = p;
		pr_info("%s: Atari built-in port using irq\n", p->name);
		parport_announce_port (p);

		वापस 0;
	पूर्ण
	वापस -ENODEV;
पूर्ण

अटल व्योम __निकास parport_atari_निकास(व्योम)
अणु
	parport_हटाओ_port(this_port);
	अगर (this_port->irq != PARPORT_IRQ_NONE)
		मुक्त_irq(IRQ_MFP_BUSY, this_port);
	parport_put_port(this_port);
पूर्ण

MODULE_AUTHOR("Andreas Schwab");
MODULE_DESCRIPTION("Parport Driver for Atari builtin Port");
MODULE_LICENSE("GPL");

module_init(parport_atari_init)
module_निकास(parport_atari_निकास)
