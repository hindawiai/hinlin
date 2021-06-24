<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * MPC5200 PSC serial console support.
 *
 * Author: Grant Likely <grant.likely@secretlab.ca>
 *
 * Copyright (c) 2007 Secret Lab Technologies Ltd.
 * Copyright (c) 2007 Freescale Semiconductor, Inc.
 *
 * It is assumed that the firmware (or the platक्रमm file) has alपढ़ोy set
 * up the port.
 */

#समावेश "types.h"
#समावेश "io.h"
#समावेश "ops.h"

/* Programmable Serial Controller (PSC) status रेजिस्टर bits */
#घोषणा MPC52xx_PSC_SR		0x04
#घोषणा MPC52xx_PSC_SR_RXRDY		0x0100
#घोषणा MPC52xx_PSC_SR_RXFULL		0x0200
#घोषणा MPC52xx_PSC_SR_TXRDY		0x0400
#घोषणा MPC52xx_PSC_SR_TXEMP		0x0800

#घोषणा MPC52xx_PSC_BUFFER	0x0C

अटल व्योम *psc;

अटल पूर्णांक psc_खोलो(व्योम)
अणु
	/* Assume the firmware has alपढ़ोy configured the PSC पूर्णांकo
	 * uart mode */
	वापस 0;
पूर्ण

अटल व्योम psc_अ_दो(अचिन्हित अक्षर c)
अणु
	जबतक (!(in_be16(psc + MPC52xx_PSC_SR) & MPC52xx_PSC_SR_TXRDY)) ;
	out_8(psc + MPC52xx_PSC_BUFFER, c);
पूर्ण

अटल अचिन्हित अक्षर psc_tstc(व्योम)
अणु
	वापस (in_be16(psc + MPC52xx_PSC_SR) & MPC52xx_PSC_SR_RXRDY) != 0;
पूर्ण

अटल अचिन्हित अक्षर psc_अ_लो(व्योम)
अणु
	जबतक (!(in_be16(psc + MPC52xx_PSC_SR) & MPC52xx_PSC_SR_RXRDY)) ;
	वापस in_8(psc + MPC52xx_PSC_BUFFER);
पूर्ण

पूर्णांक mpc5200_psc_console_init(व्योम *devp, काष्ठा serial_console_data *scdp)
अणु
	/* Get the base address of the psc रेजिस्टरs */
	अगर (dt_get_भव_reg(devp, &psc, 1) < 1)
		वापस -1;

	scdp->खोलो = psc_खोलो;
	scdp->अ_दो = psc_अ_दो;
	scdp->अ_लो = psc_अ_लो;
	scdp->tstc = psc_tstc;

	वापस 0;
पूर्ण
