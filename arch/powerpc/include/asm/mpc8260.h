<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Since there are many dअगरferent boards and no standard configuration,
 * we have a unique include file क्रम each.  Rather than change every
 * file that has to include MPC8260 configuration, they all include
 * this one and the configuration चयनing is करोne here.
 */
#अगर_घोषित __KERNEL__
#अगर_अघोषित __ASM_POWERPC_MPC8260_H__
#घोषणा __ASM_POWERPC_MPC8260_H__

#घोषणा MPC82XX_BCR_PLDP 0x00800000 /* Pipeline Maximum Depth */

#अगर_घोषित CONFIG_8260

#अगर defined(CONFIG_PQ2ADS) || defined (CONFIG_PQ2FADS)
#समावेश <platक्रमms/82xx/pq2ads.h>
#पूर्ण_अगर

#अगर_घोषित CONFIG_PCI_8260
#समावेश <platक्रमms/82xx/m82xx_pci.h>
#पूर्ण_अगर

#पूर्ण_अगर /* CONFIG_8260 */
#पूर्ण_अगर /* !__ASM_POWERPC_MPC8260_H__ */
#पूर्ण_अगर /* __KERNEL__ */
