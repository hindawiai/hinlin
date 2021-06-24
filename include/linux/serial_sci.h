<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_SERIAL_SCI_H
#घोषणा __LINUX_SERIAL_SCI_H

#समावेश <linux/bitops.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/sh_dma.h>

/*
 * Generic header क्रम SuperH (H)SCI(F) (used by sh/sh64 and related parts)
 */

/* Serial Control Register (@ = not supported by all parts) */
#घोषणा SCSCR_TIE	BIT(7)	/* Transmit Interrupt Enable */
#घोषणा SCSCR_RIE	BIT(6)	/* Receive Interrupt Enable */
#घोषणा SCSCR_TE	BIT(5)	/* Transmit Enable */
#घोषणा SCSCR_RE	BIT(4)	/* Receive Enable */
#घोषणा SCSCR_REIE	BIT(3)	/* Receive Error Interrupt Enable @ */
#घोषणा SCSCR_TOIE	BIT(2)	/* Timeout Interrupt Enable @ */
#घोषणा SCSCR_CKE1	BIT(1)	/* Clock Enable 1 */
#घोषणा SCSCR_CKE0	BIT(0)	/* Clock Enable 0 */


क्रमागत अणु
	SCIx_PROBE_REGTYPE,

	SCIx_SCI_REGTYPE,
	SCIx_IRDA_REGTYPE,
	SCIx_SCIFA_REGTYPE,
	SCIx_SCIFB_REGTYPE,
	SCIx_SH2_SCIF_FIFODATA_REGTYPE,
	SCIx_SH3_SCIF_REGTYPE,
	SCIx_SH4_SCIF_REGTYPE,
	SCIx_SH4_SCIF_BRG_REGTYPE,
	SCIx_SH4_SCIF_NO_SCSPTR_REGTYPE,
	SCIx_SH4_SCIF_FIFODATA_REGTYPE,
	SCIx_SH7705_SCIF_REGTYPE,
	SCIx_HSCIF_REGTYPE,
	SCIx_RZ_SCIFA_REGTYPE,

	SCIx_NR_REGTYPES,
पूर्ण;

काष्ठा plat_sci_port_ops अणु
	व्योम (*init_pins)(काष्ठा uart_port *, अचिन्हित पूर्णांक cflag);
पूर्ण;

/*
 * Platक्रमm device specअगरic platक्रमm_data काष्ठा
 */
काष्ठा plat_sci_port अणु
	अचिन्हित पूर्णांक	type;			/* SCI / SCIF / IRDA / HSCIF */
	upf_t		flags;			/* UPF_* flags */

	अचिन्हित पूर्णांक	sampling_rate;
	अचिन्हित पूर्णांक	scscr;			/* SCSCR initialization */

	/*
	 * Platक्रमm overrides अगर necessary, शेषs otherwise.
	 */
	अचिन्हित अक्षर	regtype;

	काष्ठा plat_sci_port_ops	*ops;
पूर्ण;

#पूर्ण_अगर /* __LINUX_SERIAL_SCI_H */
