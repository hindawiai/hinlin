<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 *  include/यंत्र-sh/cpu-sh3/gpपन.स
 *
 *  Copyright (C) 2007  Markus Brunner, Mark Jonas
 *
 *  Addresses क्रम the Pin Function Controller
 */
#अगर_अघोषित _CPU_SH3_GPIO_H
#घोषणा _CPU_SH3_GPIO_H

#अगर defined(CONFIG_CPU_SUBTYPE_SH7720) || \
    defined(CONFIG_CPU_SUBTYPE_SH7721)

/* Control रेजिस्टरs */
#घोषणा PORT_PACR	0xA4050100UL
#घोषणा PORT_PBCR	0xA4050102UL
#घोषणा PORT_PCCR	0xA4050104UL
#घोषणा PORT_PDCR	0xA4050106UL
#घोषणा PORT_PECR	0xA4050108UL
#घोषणा PORT_PFCR	0xA405010AUL
#घोषणा PORT_PGCR	0xA405010CUL
#घोषणा PORT_PHCR	0xA405010EUL
#घोषणा PORT_PJCR	0xA4050110UL
#घोषणा PORT_PKCR	0xA4050112UL
#घोषणा PORT_PLCR	0xA4050114UL
#घोषणा PORT_PMCR	0xA4050116UL
#घोषणा PORT_PPCR	0xA4050118UL
#घोषणा PORT_PRCR	0xA405011AUL
#घोषणा PORT_PSCR	0xA405011CUL
#घोषणा PORT_PTCR	0xA405011EUL
#घोषणा PORT_PUCR	0xA4050120UL
#घोषणा PORT_PVCR	0xA4050122UL

/* Data रेजिस्टरs */
#घोषणा PORT_PADR	0xA4050140UL
/* Address of PORT_PBDR is wrong in the datasheet, see errata 2005-09-21 */
#घोषणा PORT_PBDR	0xA4050142UL
#घोषणा PORT_PCDR	0xA4050144UL
#घोषणा PORT_PDDR	0xA4050146UL
#घोषणा PORT_PEDR	0xA4050148UL
#घोषणा PORT_PFDR	0xA405014AUL
#घोषणा PORT_PGDR	0xA405014CUL
#घोषणा PORT_PHDR	0xA405014EUL
#घोषणा PORT_PJDR	0xA4050150UL
#घोषणा PORT_PKDR	0xA4050152UL
#घोषणा PORT_PLDR	0xA4050154UL
#घोषणा PORT_PMDR	0xA4050156UL
#घोषणा PORT_PPDR	0xA4050158UL
#घोषणा PORT_PRDR	0xA405015AUL
#घोषणा PORT_PSDR	0xA405015CUL
#घोषणा PORT_PTDR	0xA405015EUL
#घोषणा PORT_PUDR	0xA4050160UL
#घोषणा PORT_PVDR	0xA4050162UL

/* Pin Select Registers */
#घोषणा PORT_PSELA	0xA4050124UL
#घोषणा PORT_PSELB	0xA4050126UL
#घोषणा PORT_PSELC	0xA4050128UL
#घोषणा PORT_PSELD	0xA405012AUL

#या_अगर defined(CONFIG_CPU_SUBTYPE_SH7709)

/* Control रेजिस्टरs */
#घोषणा PORT_PACR       0xa4000100UL
#घोषणा PORT_PBCR       0xa4000102UL
#घोषणा PORT_PCCR       0xa4000104UL
#घोषणा PORT_PFCR       0xa400010aUL

/* Data रेजिस्टरs */
#घोषणा PORT_PADR       0xa4000120UL
#घोषणा PORT_PBDR       0xa4000122UL
#घोषणा PORT_PCDR       0xa4000124UL
#घोषणा PORT_PFDR       0xa400012aUL

#पूर्ण_अगर

#पूर्ण_अगर
