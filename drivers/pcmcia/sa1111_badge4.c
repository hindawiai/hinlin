<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/drivers/pcmcia/sa1100_badge4.c
 *
 * BadgePAD 4 PCMCIA specअगरic routines
 *
 *   Christopher Hoover <ch@hpl.hp.com>
 *
 * Copyright (C) 2002 Hewlett-Packard Company
 */
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>

#समावेश <mach/hardware.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <mach/badge4.h>
#समावेश <यंत्र/hardware/sa1111.h>

#समावेश "sa1111_generic.h"

/*
 * BadgePAD 4 Details
 *
 * PCM Vcc:
 *
 *  PCM Vcc on BadgePAD 4 can be jumpered क्रम 3v3 (लघु pins 1 and 3
 *  on JP6) or 5v0 (लघु pins 3 and 5 on JP6).
 *
 * PCM Vpp:
 *
 *  PCM Vpp on BadgePAD 4 can be jumpered क्रम 12v0 (लघु pins 4 and 6
 *  on JP6) or tied to PCM Vcc (लघु pins 2 and 4 on JP6).  N.B.,
 *  12v0 operation requires that the घातer supply actually supply 12v0
 *  via pin 7 of JP7.
 *
 * CF Vcc:
 *
 *  CF Vcc on BadgePAD 4 can be jumpered either क्रम 3v3 (लघु pins 1
 *  and 2 on JP10) or 5v0 (लघु pins 2 and 3 on JP10).
 *
 * Unक्रमtunately there's no way programmatically to determine how a
 * given board is jumpered.  This code assumes a शेष jumpering
 * as described below.
 *
 * If the शेषs aren't correct, you may override them with a pcmv
 * setup argument: pcmv=<pcm vcc>,<pcm vpp>,<cf vcc>.  The units are
 * tenths of volts; e.g. pcmv=33,120,50 indicates 3v3 PCM Vcc, 12v0
 * PCM Vpp, and 5v0 CF Vcc.
 *
 */

अटल पूर्णांक badge4_pcmvcc = 50;  /* pins 3 and 5 jumpered on JP6 */
अटल पूर्णांक badge4_pcmvpp = 50;  /* pins 2 and 4 jumpered on JP6 */
अटल पूर्णांक badge4_cfvcc = 33;   /* pins 1 and 2 jumpered on JP10 */

अटल व्योम complain_about_jumpering(स्थिर अक्षर *whom,
				     स्थिर अक्षर *supply,
				     पूर्णांक given, पूर्णांक wanted)
अणु
	prपूर्णांकk(KERN_ERR
	 "%s: %s %d.%dV wanted but board is jumpered for %s %d.%dV operation"
	 "; re-jumper the board and/or use pcmv=xx,xx,xx\n",
	       whom, supply,
	       wanted / 10, wanted % 10,
	       supply,
	       given / 10, given % 10);
पूर्ण

अटल पूर्णांक
badge4_pcmcia_configure_socket(काष्ठा soc_pcmcia_socket *skt, स्थिर socket_state_t *state)
अणु
	पूर्णांक ret;

	चयन (skt->nr) अणु
	हाल 0:
		अगर ((state->Vcc != 0) &&
		    (state->Vcc != badge4_pcmvcc)) अणु
			complain_about_jumpering(__func__, "pcmvcc",
						 badge4_pcmvcc, state->Vcc);
			// Apply घातer regardless of the jumpering.
			// वापस -1;
		पूर्ण
		अगर ((state->Vpp != 0) &&
		    (state->Vpp != badge4_pcmvpp)) अणु
			complain_about_jumpering(__func__, "pcmvpp",
						 badge4_pcmvpp, state->Vpp);
			वापस -1;
		पूर्ण
		अवरोध;

	हाल 1:
		अगर ((state->Vcc != 0) &&
		    (state->Vcc != badge4_cfvcc)) अणु
			complain_about_jumpering(__func__, "cfvcc",
						 badge4_cfvcc, state->Vcc);
			वापस -1;
		पूर्ण
		अवरोध;

	शेष:
		वापस -1;
	पूर्ण

	ret = sa1111_pcmcia_configure_socket(skt, state);
	अगर (ret == 0) अणु
		अचिन्हित दीर्घ flags;
		पूर्णांक need5V;

		local_irq_save(flags);

		need5V = ((state->Vcc == 50) || (state->Vpp == 50));

		badge4_set_5V(BADGE4_5V_PCMCIA_SOCK(skt->nr), need5V);

		local_irq_restore(flags);
	पूर्ण

	वापस ret;
पूर्ण

अटल काष्ठा pcmcia_low_level badge4_pcmcia_ops = अणु
	.owner			= THIS_MODULE,
	.configure_socket	= badge4_pcmcia_configure_socket,
	.first			= 0,
	.nr			= 2,
पूर्ण;

पूर्णांक pcmcia_badge4_init(काष्ठा sa1111_dev *dev)
अणु
	prपूर्णांकk(KERN_INFO
	       "%s: badge4_pcmvcc=%d, badge4_pcmvpp=%d, badge4_cfvcc=%d\n",
	       __func__,
	       badge4_pcmvcc, badge4_pcmvpp, badge4_cfvcc);

	sa11xx_drv_pcmcia_ops(&badge4_pcmcia_ops);
	वापस sa1111_pcmcia_add(dev, &badge4_pcmcia_ops,
				 sa11xx_drv_pcmcia_add_one);
पूर्ण

#अगर_अघोषित MODULE
अटल पूर्णांक __init pcmv_setup(अक्षर *s)
अणु
	पूर्णांक v[4];

	s = get_options(s, ARRAY_SIZE(v), v);

	अगर (v[0] >= 1) badge4_pcmvcc = v[1];
	अगर (v[0] >= 2) badge4_pcmvpp = v[2];
	अगर (v[0] >= 3) badge4_cfvcc = v[3];

	वापस 1;
पूर्ण

__setup("pcmv=", pcmv_setup);
#पूर्ण_अगर
