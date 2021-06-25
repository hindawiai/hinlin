<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Register definitions क्रम Aपंचांगel AC97C
 *
 * Copyright (C) 2005-2009 Aपंचांगel Corporation
 */
#अगर_अघोषित __SOUND_ATMEL_AC97C_H
#घोषणा __SOUND_ATMEL_AC97C_H

#घोषणा AC97C_MR		0x08
#घोषणा AC97C_ICA		0x10
#घोषणा AC97C_OCA		0x14
#घोषणा AC97C_CARHR		0x20
#घोषणा AC97C_CATHR		0x24
#घोषणा AC97C_CASR		0x28
#घोषणा AC97C_CAMR		0x2c
#घोषणा AC97C_CORHR		0x40
#घोषणा AC97C_COTHR		0x44
#घोषणा AC97C_COSR		0x48
#घोषणा AC97C_COMR		0x4c
#घोषणा AC97C_SR		0x50
#घोषणा AC97C_IER		0x54
#घोषणा AC97C_IDR		0x58
#घोषणा AC97C_IMR		0x5c
#घोषणा AC97C_VERSION		0xfc

#घोषणा AC97C_CATPR		PDC_TPR
#घोषणा AC97C_CATCR		PDC_TCR
#घोषणा AC97C_CATNPR		PDC_TNPR
#घोषणा AC97C_CATNCR		PDC_TNCR
#घोषणा AC97C_CARPR		PDC_RPR
#घोषणा AC97C_CARCR		PDC_RCR
#घोषणा AC97C_CARNPR		PDC_RNPR
#घोषणा AC97C_CARNCR		PDC_RNCR
#घोषणा AC97C_PTCR		PDC_PTCR

#घोषणा AC97C_MR_ENA		(1 << 0)
#घोषणा AC97C_MR_WRST		(1 << 1)
#घोषणा AC97C_MR_VRA		(1 << 2)

#घोषणा AC97C_CSR_TXRDY		(1 << 0)
#घोषणा AC97C_CSR_TXEMPTY	(1 << 1)
#घोषणा AC97C_CSR_UNRUN		(1 << 2)
#घोषणा AC97C_CSR_RXRDY		(1 << 4)
#घोषणा AC97C_CSR_OVRUN		(1 << 5)
#घोषणा AC97C_CSR_ENDTX		(1 << 10)
#घोषणा AC97C_CSR_ENDRX		(1 << 14)

#घोषणा AC97C_CMR_SIZE_20	(0 << 16)
#घोषणा AC97C_CMR_SIZE_18	(1 << 16)
#घोषणा AC97C_CMR_SIZE_16	(2 << 16)
#घोषणा AC97C_CMR_SIZE_10	(3 << 16)
#घोषणा AC97C_CMR_CEM_LITTLE	(1 << 18)
#घोषणा AC97C_CMR_CEM_BIG	(0 << 18)
#घोषणा AC97C_CMR_CENA		(1 << 21)
#घोषणा AC97C_CMR_DMAEN		(1 << 22)

#घोषणा AC97C_SR_CAEVT		(1 << 3)
#घोषणा AC97C_SR_COEVT		(1 << 2)
#घोषणा AC97C_SR_WKUP		(1 << 1)
#घोषणा AC97C_SR_SOF		(1 << 0)

#घोषणा AC97C_CH_MASK(slot)						\
	(0x7 << (3 * (AC97_SLOT_##slot - 3)))
#घोषणा AC97C_CH_ASSIGN(slot, channel)					\
	(AC97C_CHANNEL_##channel << (3 * (AC97_SLOT_##slot - 3)))
#घोषणा AC97C_CHANNEL_NONE	0x0
#घोषणा AC97C_CHANNEL_A		0x1

#पूर्ण_अगर /* __SOUND_ATMEL_AC97C_H */
