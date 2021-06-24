<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _INCLUDE_GUARD_PD6729_H_
#घोषणा _INCLUDE_GUARD_PD6729_H_

/* Flags क्रम I365_GENCTL */
#घोषणा I365_DF_VS1		0x40	/* DF-step Voltage Sense */
#घोषणा I365_DF_VS2		0x80

/* Fields in PD67_EXTERN_DATA */
#घोषणा PD67_EXD_VS1(s)		(0x01 << ((s) << 1))
#घोषणा PD67_EXD_VS2(s)		(0x02 << ((s) << 1))

/* Default ISA पूर्णांकerrupt mask */
#घोषणा PD67_MASK	0x0eb8	/* irq 11,10,9,7,5,4,3 */

काष्ठा pd6729_socket अणु
	पूर्णांक	number;
	पूर्णांक	card_irq;
	अचिन्हित दीर्घ io_base;	/* base io address of the socket */
	काष्ठा pcmcia_socket socket;
	काष्ठा समयr_list poll_समयr;
पूर्ण;

#पूर्ण_अगर
