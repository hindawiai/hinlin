<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Driver क्रम CPM (SCC/SMC) serial ports
 *
 * definitions क्रम cpm2
 *
 */

#अगर_अघोषित CPM_UART_CPM2_H
#घोषणा CPM_UART_CPM2_H

#समावेश <यंत्र/cpm2.h>

अटल अंतरभूत व्योम cpm_set_brg(पूर्णांक brg, पूर्णांक baud)
अणु
	cpm_setbrg(brg, baud);
पूर्ण

अटल अंतरभूत व्योम cpm_set_scc_fcr(scc_uart_t __iomem *sup)
अणु
	out_8(&sup->scc_genscc.scc_rfcr, CPMFCR_GBL | CPMFCR_EB);
	out_8(&sup->scc_genscc.scc_tfcr, CPMFCR_GBL | CPMFCR_EB);
पूर्ण

अटल अंतरभूत व्योम cpm_set_smc_fcr(smc_uart_t __iomem *up)
अणु
	out_8(&up->smc_rfcr, CPMFCR_GBL | CPMFCR_EB);
	out_8(&up->smc_tfcr, CPMFCR_GBL | CPMFCR_EB);
पूर्ण

#घोषणा DPRAM_BASE	((u8 __iomem __क्रमce *)cpm_dpram_addr(0))

#पूर्ण_अगर
