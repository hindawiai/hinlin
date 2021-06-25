<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Sharp SL-C7xx Series PCMCIA routines
 *
 * Copyright (c) 2004-2005 Riअक्षरd Purdie
 *
 * Based on Sharp's 2.4 kernel patches and pxa2xx_मुख्यstone.c
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <यंत्र/mach-types.h>
#समावेश <mach/hardware.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/hardware/scoop.h>

#समावेश "soc_common.h"

#घोषणा	NO_KEEP_VS 0x0001
#घोषणा SCOOP_DEV platक्रमm_scoop_config->devs

अटल व्योम sharpsl_pcmcia_init_reset(काष्ठा soc_pcmcia_socket *skt)
अणु
	काष्ठा scoop_pcmcia_dev *scoopdev = &SCOOP_DEV[skt->nr];

	reset_scoop(scoopdev->dev);

	/* Shared घातer controls need to be handled carefully */
	अगर (platक्रमm_scoop_config->घातer_ctrl)
		platक्रमm_scoop_config->घातer_ctrl(scoopdev->dev, 0x0000, skt->nr);
	अन्यथा
		ग_लिखो_scoop_reg(scoopdev->dev, SCOOP_CPR, 0x0000);

	scoopdev->keep_vs = NO_KEEP_VS;
	scoopdev->keep_rd = 0;
पूर्ण

अटल पूर्णांक sharpsl_pcmcia_hw_init(काष्ठा soc_pcmcia_socket *skt)
अणु
	अगर (SCOOP_DEV[skt->nr].cd_irq >= 0) अणु
		skt->stat[SOC_STAT_CD].irq = SCOOP_DEV[skt->nr].cd_irq;
		skt->stat[SOC_STAT_CD].name = SCOOP_DEV[skt->nr].cd_irq_str;
	पूर्ण

	skt->socket.pci_irq = SCOOP_DEV[skt->nr].irq;

	वापस 0;
पूर्ण

अटल व्योम sharpsl_pcmcia_socket_state(काष्ठा soc_pcmcia_socket *skt,
				    काष्ठा pcmcia_state *state)
अणु
	अचिन्हित लघु cpr, csr;
	काष्ठा device *scoop = SCOOP_DEV[skt->nr].dev;

	cpr = पढ़ो_scoop_reg(SCOOP_DEV[skt->nr].dev, SCOOP_CPR);

	ग_लिखो_scoop_reg(scoop, SCOOP_IRM, 0x00FF);
	ग_लिखो_scoop_reg(scoop, SCOOP_ISR, 0x0000);
	ग_लिखो_scoop_reg(scoop, SCOOP_IRM, 0x0000);
	csr = पढ़ो_scoop_reg(scoop, SCOOP_CSR);
	अगर (csr & 0x0004) अणु
		/* card eject */
		ग_लिखो_scoop_reg(scoop, SCOOP_CDR, 0x0000);
		SCOOP_DEV[skt->nr].keep_vs = NO_KEEP_VS;
	पूर्ण
	अन्यथा अगर (!(SCOOP_DEV[skt->nr].keep_vs & NO_KEEP_VS)) अणु
		/* keep vs1,vs2 */
		ग_लिखो_scoop_reg(scoop, SCOOP_CDR, 0x0000);
		csr |= SCOOP_DEV[skt->nr].keep_vs;
	पूर्ण
	अन्यथा अगर (cpr & 0x0003) अणु
		/* घातer on */
		ग_लिखो_scoop_reg(scoop, SCOOP_CDR, 0x0000);
		SCOOP_DEV[skt->nr].keep_vs = (csr & 0x00C0);
	पूर्ण
	अन्यथा अणु
		/* card detect */
	        अगर ((machine_is_spitz() || machine_is_borzoi()) && skt->nr == 1) अणु
	                ग_लिखो_scoop_reg(scoop, SCOOP_CDR, 0x0000);
	        पूर्ण अन्यथा अणु
		        ग_लिखो_scoop_reg(scoop, SCOOP_CDR, 0x0002);
	        पूर्ण
	पूर्ण

	state->detect = (csr & 0x0004) ? 0 : 1;
	state->पढ़ोy  = (csr & 0x0002) ? 1 : 0;
	state->bvd1   = (csr & 0x0010) ? 1 : 0;
	state->bvd2   = (csr & 0x0020) ? 1 : 0;
	state->wrprot = (csr & 0x0008) ? 1 : 0;
	state->vs_3v  = (csr & 0x0040) ? 0 : 1;
	state->vs_Xv  = (csr & 0x0080) ? 0 : 1;

	अगर ((cpr & 0x0080) && ((cpr & 0x8040) != 0x8040)) अणु
		prपूर्णांकk(KERN_ERR "sharpsl_pcmcia_socket_state(): CPR=%04X, Low voltage!\n", cpr);
	पूर्ण
पूर्ण


अटल पूर्णांक sharpsl_pcmcia_configure_socket(काष्ठा soc_pcmcia_socket *skt,
				       स्थिर socket_state_t *state)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा device *scoop = SCOOP_DEV[skt->nr].dev;

	अचिन्हित लघु cpr, ncpr, ccr, nccr, mcr, nmcr, imr, nimr;

	चयन (state->Vcc) अणु
	हाल	0:  	अवरोध;
	हाल 	33: 	अवरोध;
	हाल	50: 	अवरोध;
	शेष:
		 prपूर्णांकk(KERN_ERR "sharpsl_pcmcia_configure_socket(): bad Vcc %u\n", state->Vcc);
		 वापस -1;
	पूर्ण

	अगर ((state->Vpp!=state->Vcc) && (state->Vpp!=0)) अणु
		prपूर्णांकk(KERN_ERR "CF slot cannot support Vpp %u\n", state->Vpp);
		वापस -1;
	पूर्ण

	local_irq_save(flags);

	nmcr = (mcr = पढ़ो_scoop_reg(scoop, SCOOP_MCR)) & ~0x0010;
	ncpr = (cpr = पढ़ो_scoop_reg(scoop, SCOOP_CPR)) & ~0x0083;
	nccr = (ccr = पढ़ो_scoop_reg(scoop, SCOOP_CCR)) & ~0x0080;
	nimr = (imr = पढ़ो_scoop_reg(scoop, SCOOP_IMR)) & ~0x003E;

	अगर ((machine_is_spitz() || machine_is_borzoi() || machine_is_akita()) && skt->nr == 0) अणु
	        ncpr |= (state->Vcc == 33) ? 0x0002 :
		        (state->Vcc == 50) ? 0x0002 : 0;
	पूर्ण अन्यथा अणु
	        ncpr |= (state->Vcc == 33) ? 0x0001 :
		        (state->Vcc == 50) ? 0x0002 : 0;
	पूर्ण
	nmcr |= (state->flags&SS_IOCARD) ? 0x0010 : 0;
	ncpr |= (state->flags&SS_OUTPUT_ENA) ? 0x0080 : 0;
	nccr |= (state->flags&SS_RESET)? 0x0080: 0;
	nimr |=	((skt->status&SS_DETECT) ? 0x0004 : 0)|
			((skt->status&SS_READY)  ? 0x0002 : 0)|
			((skt->status&SS_BATDEAD)? 0x0010 : 0)|
			((skt->status&SS_BATWARN)? 0x0020 : 0)|
			((skt->status&SS_STSCHG) ? 0x0010 : 0)|
			((skt->status&SS_WRPROT) ? 0x0008 : 0);

	अगर (!(ncpr & 0x0003)) अणु
		SCOOP_DEV[skt->nr].keep_rd = 0;
	पूर्ण अन्यथा अगर (!SCOOP_DEV[skt->nr].keep_rd) अणु
		अगर (nccr & 0x0080)
			SCOOP_DEV[skt->nr].keep_rd = 1;
		अन्यथा
			nccr |= 0x0080;
	पूर्ण

	अगर (mcr != nmcr)
		ग_लिखो_scoop_reg(scoop, SCOOP_MCR, nmcr);
	अगर (cpr != ncpr) अणु
		अगर (platक्रमm_scoop_config->घातer_ctrl)
			platक्रमm_scoop_config->घातer_ctrl(scoop, ncpr , skt->nr);
		अन्यथा
		        ग_लिखो_scoop_reg(scoop, SCOOP_CPR, ncpr);
	पूर्ण
	अगर (ccr != nccr)
		ग_लिखो_scoop_reg(scoop, SCOOP_CCR, nccr);
	अगर (imr != nimr)
		ग_लिखो_scoop_reg(scoop, SCOOP_IMR, nimr);

	local_irq_restore(flags);

	वापस 0;
पूर्ण

अटल व्योम sharpsl_pcmcia_socket_init(काष्ठा soc_pcmcia_socket *skt)
अणु
	sharpsl_pcmcia_init_reset(skt);

	/* Enable पूर्णांकerrupt */
	ग_लिखो_scoop_reg(SCOOP_DEV[skt->nr].dev, SCOOP_IMR, 0x00C0);
	ग_लिखो_scoop_reg(SCOOP_DEV[skt->nr].dev, SCOOP_MCR, 0x0101);
	SCOOP_DEV[skt->nr].keep_vs = NO_KEEP_VS;
पूर्ण

अटल व्योम sharpsl_pcmcia_socket_suspend(काष्ठा soc_pcmcia_socket *skt)
अणु
	sharpsl_pcmcia_init_reset(skt);
पूर्ण

अटल काष्ठा pcmcia_low_level sharpsl_pcmcia_ops = अणु
	.owner                  = THIS_MODULE,
	.hw_init                = sharpsl_pcmcia_hw_init,
	.socket_state           = sharpsl_pcmcia_socket_state,
	.configure_socket       = sharpsl_pcmcia_configure_socket,
	.socket_init            = sharpsl_pcmcia_socket_init,
	.socket_suspend         = sharpsl_pcmcia_socket_suspend,
	.first                  = 0,
	.nr                     = 0,
पूर्ण;

#अगर_घोषित CONFIG_SA1100_COLLIE
#समावेश "sa11xx_base.h"

पूर्णांक pcmcia_collie_init(काष्ठा device *dev)
अणु
       पूर्णांक ret = -ENODEV;

       अगर (machine_is_collie())
               ret = sa11xx_drv_pcmcia_probe(dev, &sharpsl_pcmcia_ops, 0, 1);

       वापस ret;
पूर्ण

#अन्यथा

अटल काष्ठा platक्रमm_device *sharpsl_pcmcia_device;

अटल पूर्णांक __init sharpsl_pcmcia_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (!platक्रमm_scoop_config)
		वापस -ENODEV;

	sharpsl_pcmcia_ops.nr = platक्रमm_scoop_config->num_devs;
	sharpsl_pcmcia_device = platक्रमm_device_alloc("pxa2xx-pcmcia", -1);

	अगर (!sharpsl_pcmcia_device)
		वापस -ENOMEM;

	ret = platक्रमm_device_add_data(sharpsl_pcmcia_device,
			&sharpsl_pcmcia_ops, माप(sharpsl_pcmcia_ops));
	अगर (ret == 0) अणु
		sharpsl_pcmcia_device->dev.parent = platक्रमm_scoop_config->devs[0].dev;
		ret = platक्रमm_device_add(sharpsl_pcmcia_device);
	पूर्ण

	अगर (ret)
		platक्रमm_device_put(sharpsl_pcmcia_device);

	वापस ret;
पूर्ण

अटल व्योम __निकास sharpsl_pcmcia_निकास(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(sharpsl_pcmcia_device);
पूर्ण

fs_initcall(sharpsl_pcmcia_init);
module_निकास(sharpsl_pcmcia_निकास);
#पूर्ण_अगर

MODULE_DESCRIPTION("Sharp SL Series PCMCIA Support");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:pxa2xx-pcmcia");
