<शैली गुरु>
/*
 * Access to HP-HIL MLC through HP System Device Controller.
 *
 * Copyright (c) 2001 Brian S. Julin
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions, and the following disclaimer,
 *    without modअगरication.
 * 2. The name of the author may not be used to enकरोrse or promote products
 *    derived from this software without specअगरic prior written permission.
 *
 * Alternatively, this software may be distributed under the terms of the
 * GNU General Public License ("GPL").
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR
 * ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 *
 * References:
 * HP-HIL Technical Reference Manual.  Hewlett Packard Product No. 45918A
 * System Device Controller Microprocessor Firmware Theory of Operation
 *      क्रम Part Number 1820-4784 Revision B.  Dwg No. A-1820-4784-2
 *
 */

#समावेश <linux/hil_mlc.h>
#समावेश <linux/hp_sdc.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/माला.स>
#समावेश <linux/semaphore.h>

#घोषणा PREFIX "HP SDC MLC: "

अटल hil_mlc hp_sdc_mlc;

MODULE_AUTHOR("Brian S. Julin <bri@calyx.com>");
MODULE_DESCRIPTION("Glue for onboard HIL MLC in HP-PARISC machines");
MODULE_LICENSE("Dual BSD/GPL");

अटल काष्ठा hp_sdc_mlc_priv_s अणु
	पूर्णांक emtesपंचांगode;
	hp_sdc_transaction trans;
	u8 tseq[16];
	पूर्णांक got5x;
पूर्ण hp_sdc_mlc_priv;

/************************* Interrupt context ******************************/
अटल व्योम hp_sdc_mlc_isr (पूर्णांक irq, व्योम *dev_id,
			    uपूर्णांक8_t status, uपूर्णांक8_t data)
अणु
	पूर्णांक idx;
	hil_mlc *mlc = &hp_sdc_mlc;

	ग_लिखो_lock(&mlc->lock);
	अगर (mlc->icount < 0) अणु
		prपूर्णांकk(KERN_WARNING PREFIX "HIL Overflow!\n");
		up(&mlc->isem);
		जाओ out;
	पूर्ण
	idx = 15 - mlc->icount;
	अगर ((status & HP_SDC_STATUS_IRQMASK) == HP_SDC_STATUS_HILDATA) अणु
		mlc->ipacket[idx] |= data | HIL_ERR_INT;
		mlc->icount--;
		अगर (hp_sdc_mlc_priv.got5x || !idx)
			जाओ check;
		अगर ((mlc->ipacket[idx - 1] & HIL_PKT_ADDR_MASK) !=
		    (mlc->ipacket[idx] & HIL_PKT_ADDR_MASK)) अणु
			mlc->ipacket[idx] &= ~HIL_PKT_ADDR_MASK;
			mlc->ipacket[idx] |= (mlc->ipacket[idx - 1]
						& HIL_PKT_ADDR_MASK);
		पूर्ण
		जाओ check;
	पूर्ण
	/* We know status is 5X */
	अगर (data & HP_SDC_HIL_ISERR)
		जाओ err;
	mlc->ipacket[idx] =
		(data & HP_SDC_HIL_R1MASK) << HIL_PKT_ADDR_SHIFT;
	hp_sdc_mlc_priv.got5x = 1;
	जाओ out;

 check:
	hp_sdc_mlc_priv.got5x = 0;
	अगर (mlc->imatch == 0)
		जाओ करोne;
	अगर ((mlc->imatch == (HIL_ERR_INT | HIL_PKT_CMD | HIL_CMD_POL))
	    && (mlc->ipacket[idx] == (mlc->imatch | idx)))
		जाओ करोne;
	अगर (mlc->ipacket[idx] == mlc->imatch)
		जाओ करोne;
	जाओ out;

 err:
	prपूर्णांकk(KERN_DEBUG PREFIX "err code %x\n", data);

	चयन (data) अणु
	हाल HP_SDC_HIL_RC_DONE:
		prपूर्णांकk(KERN_WARNING PREFIX "Bastard SDC reconfigured loop!\n");
		अवरोध;

	हाल HP_SDC_HIL_ERR:
		mlc->ipacket[idx] |= HIL_ERR_INT | HIL_ERR_PERR |
					HIL_ERR_FERR | HIL_ERR_FOF;
		अवरोध;

	हाल HP_SDC_HIL_TO:
		mlc->ipacket[idx] |= HIL_ERR_INT | HIL_ERR_LERR;
		अवरोध;

	हाल HP_SDC_HIL_RC:
		prपूर्णांकk(KERN_WARNING PREFIX "Bastard SDC decided to reconfigure loop!\n");
		अवरोध;

	शेष:
		prपूर्णांकk(KERN_WARNING PREFIX "Unknown HIL Error status (%x)!\n", data);
		अवरोध;
	पूर्ण

	/* No more data will be coming due to an error. */
 करोne:
	tasklet_schedule(mlc->tasklet);
	up(&mlc->isem);
 out:
	ग_लिखो_unlock(&mlc->lock);
पूर्ण


/******************** Tasklet or userspace context functions ****************/

अटल पूर्णांक hp_sdc_mlc_in(hil_mlc *mlc, suseconds_t समयout)
अणु
	काष्ठा hp_sdc_mlc_priv_s *priv;
	पूर्णांक rc = 2;

	priv = mlc->priv;

	/* Try to करोwn the semaphore */
	अगर (करोwn_trylock(&mlc->isem)) अणु
		अगर (priv->emtesपंचांगode) अणु
			mlc->ipacket[0] =
				HIL_ERR_INT | (mlc->opacket &
					       (HIL_PKT_CMD |
						HIL_PKT_ADDR_MASK |
						HIL_PKT_DATA_MASK));
			mlc->icount = 14;
			/* prपूर्णांकk(KERN_DEBUG PREFIX ">[%x]\n", mlc->ipacket[0]); */
			जाओ wasup;
		पूर्ण
		अगर (समय_after(jअगरfies, mlc->instart + mlc->पूर्णांकimeout)) अणु
			/*	prपूर्णांकk("!%i %i",
				tv.tv_usec - mlc->instart.tv_usec,
				mlc->पूर्णांकimeout);
			 */
			rc = 1;
			up(&mlc->isem);
		पूर्ण
		जाओ करोne;
	पूर्ण
 wasup:
	up(&mlc->isem);
	rc = 0;
 करोne:
	वापस rc;
पूर्ण

अटल पूर्णांक hp_sdc_mlc_cts(hil_mlc *mlc)
अणु
	काष्ठा hp_sdc_mlc_priv_s *priv;

	priv = mlc->priv;

	/* Try to करोwn the semaphores -- they should be up. */
	BUG_ON(करोwn_trylock(&mlc->isem));
	BUG_ON(करोwn_trylock(&mlc->osem));

	up(&mlc->isem);
	up(&mlc->osem);

	अगर (करोwn_trylock(&mlc->csem)) अणु
		अगर (priv->trans.act.semaphore != &mlc->csem)
			जाओ poll;
		अन्यथा
			जाओ busy;
	पूर्ण

	अगर (!(priv->tseq[4] & HP_SDC_USE_LOOP))
		जाओ करोne;

 poll:
	priv->trans.act.semaphore = &mlc->csem;
	priv->trans.actidx = 0;
	priv->trans.idx = 1;
	priv->trans.endidx = 5;
	priv->tseq[0] =
		HP_SDC_ACT_POSTCMD | HP_SDC_ACT_DATAIN | HP_SDC_ACT_SEMAPHORE;
	priv->tseq[1] = HP_SDC_CMD_READ_USE;
	priv->tseq[2] = 1;
	priv->tseq[3] = 0;
	priv->tseq[4] = 0;
	वापस __hp_sdc_enqueue_transaction(&priv->trans);
 busy:
	वापस 1;
 करोne:
	priv->trans.act.semaphore = &mlc->osem;
	up(&mlc->csem);
	वापस 0;
पूर्ण

अटल पूर्णांक hp_sdc_mlc_out(hil_mlc *mlc)
अणु
	काष्ठा hp_sdc_mlc_priv_s *priv;

	priv = mlc->priv;

	/* Try to करोwn the semaphore -- it should be up. */
	BUG_ON(करोwn_trylock(&mlc->osem));

	अगर (mlc->opacket & HIL_DO_ALTER_CTRL)
		जाओ करो_control;

 करो_data:
	अगर (priv->emtesपंचांगode) अणु
		up(&mlc->osem);
		वापस 0;
	पूर्ण
	/* Shouldn't be sending commands when loop may be busy */
	BUG_ON(करोwn_trylock(&mlc->csem));
	up(&mlc->csem);

	priv->trans.actidx = 0;
	priv->trans.idx = 1;
	priv->trans.act.semaphore = &mlc->osem;
	priv->trans.endidx = 6;
	priv->tseq[0] =
		HP_SDC_ACT_DATAREG | HP_SDC_ACT_POSTCMD | HP_SDC_ACT_SEMAPHORE;
	priv->tseq[1] = 0x7;
	priv->tseq[2] =
		(mlc->opacket &
		 (HIL_PKT_ADDR_MASK | HIL_PKT_CMD))
		   >> HIL_PKT_ADDR_SHIFT;
	priv->tseq[3] =
		(mlc->opacket & HIL_PKT_DATA_MASK)
		  >> HIL_PKT_DATA_SHIFT;
	priv->tseq[4] = 0;  /* No समयout */
	अगर (priv->tseq[3] == HIL_CMD_DHR)
		priv->tseq[4] = 1;
	priv->tseq[5] = HP_SDC_CMD_DO_HIL;
	जाओ enqueue;

 करो_control:
	priv->emtesपंचांगode = mlc->opacket & HIL_CTRL_TEST;

	/* we cannot emulate this, it should not be used. */
	BUG_ON((mlc->opacket & (HIL_CTRL_APE | HIL_CTRL_IPF)) == HIL_CTRL_APE);

	अगर ((mlc->opacket & HIL_CTRL_ONLY) == HIL_CTRL_ONLY)
		जाओ control_only;

	/* Should not send command/data after engaging APE */
	BUG_ON(mlc->opacket & HIL_CTRL_APE);

	/* Disengaging APE this way would not be valid either since
	 * the loop must be allowed to idle.
	 *
	 * So, it works out that we really never actually send control
	 * and data when using SDC, we just send the data.
	 */
	जाओ करो_data;

 control_only:
	priv->trans.actidx = 0;
	priv->trans.idx = 1;
	priv->trans.act.semaphore = &mlc->osem;
	priv->trans.endidx = 4;
	priv->tseq[0] =
	  HP_SDC_ACT_PRECMD | HP_SDC_ACT_DATAOUT | HP_SDC_ACT_SEMAPHORE;
	priv->tseq[1] = HP_SDC_CMD_SET_LPC;
	priv->tseq[2] = 1;
	/* priv->tseq[3] = (mlc->ddc + 1) | HP_SDC_LPS_ACSUCC; */
	priv->tseq[3] = 0;
	अगर (mlc->opacket & HIL_CTRL_APE) अणु
		priv->tseq[3] |= HP_SDC_LPC_APE_IPF;
		BUG_ON(करोwn_trylock(&mlc->csem));
	पूर्ण
 enqueue:
	वापस hp_sdc_enqueue_transaction(&priv->trans);
पूर्ण

अटल पूर्णांक __init hp_sdc_mlc_init(व्योम)
अणु
	hil_mlc *mlc = &hp_sdc_mlc;
	पूर्णांक err;

#अगर_घोषित __mc68000__
	अगर (!MACH_IS_HP300)
		वापस -ENODEV;
#पूर्ण_अगर

	prपूर्णांकk(KERN_INFO PREFIX "Registering the System Domain Controller's HIL MLC.\n");

	hp_sdc_mlc_priv.emtesपंचांगode = 0;
	hp_sdc_mlc_priv.trans.seq = hp_sdc_mlc_priv.tseq;
	hp_sdc_mlc_priv.trans.act.semaphore = &mlc->osem;
	hp_sdc_mlc_priv.got5x = 0;

	mlc->cts = &hp_sdc_mlc_cts;
	mlc->in	= &hp_sdc_mlc_in;
	mlc->out = &hp_sdc_mlc_out;
	mlc->priv = &hp_sdc_mlc_priv;

	err = hil_mlc_रेजिस्टर(mlc);
	अगर (err) अणु
		prपूर्णांकk(KERN_WARNING PREFIX "Failed to register MLC structure with hil_mlc\n");
		वापस err;
	पूर्ण

	अगर (hp_sdc_request_hil_irq(&hp_sdc_mlc_isr)) अणु
		prपूर्णांकk(KERN_WARNING PREFIX "Request for raw HIL ISR hook denied\n");
		अगर (hil_mlc_unरेजिस्टर(mlc))
			prपूर्णांकk(KERN_ERR PREFIX "Failed to unregister MLC structure with hil_mlc.\n"
				"This is bad.  Could cause an oops.\n");
		वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास hp_sdc_mlc_निकास(व्योम)
अणु
	hil_mlc *mlc = &hp_sdc_mlc;

	अगर (hp_sdc_release_hil_irq(&hp_sdc_mlc_isr))
		prपूर्णांकk(KERN_ERR PREFIX "Failed to release the raw HIL ISR hook.\n"
			"This is bad.  Could cause an oops.\n");

	अगर (hil_mlc_unरेजिस्टर(mlc))
		prपूर्णांकk(KERN_ERR PREFIX "Failed to unregister MLC structure with hil_mlc.\n"
			"This is bad.  Could cause an oops.\n");
पूर्ण

module_init(hp_sdc_mlc_init);
module_निकास(hp_sdc_mlc_निकास);
