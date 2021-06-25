<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  CLPS711X प्रणाली रेजिस्टर bits definitions
 *
 *  Copyright (C) 2013 Alexander Shiyan <shc_work@mail.ru>
 */

#अगर_अघोषित _LINUX_MFD_SYSCON_CLPS711X_H_
#घोषणा _LINUX_MFD_SYSCON_CLPS711X_H_

#घोषणा SYSCON_OFFSET		(0x00)
#घोषणा SYSFLG_OFFSET		(0x40)

#घोषणा SYSCON1_KBDSCAN(x)	((x) & 15)
#घोषणा SYSCON1_KBDSCAN_MASK	(15)
#घोषणा SYSCON1_TC1M		(1 << 4)
#घोषणा SYSCON1_TC1S		(1 << 5)
#घोषणा SYSCON1_TC2M		(1 << 6)
#घोषणा SYSCON1_TC2S		(1 << 7)
#घोषणा SYSCON1_BZTOG		(1 << 9)
#घोषणा SYSCON1_BZMOD		(1 << 10)
#घोषणा SYSCON1_DBGEN		(1 << 11)
#घोषणा SYSCON1_LCDEN		(1 << 12)
#घोषणा SYSCON1_CDENTX		(1 << 13)
#घोषणा SYSCON1_CDENRX		(1 << 14)
#घोषणा SYSCON1_SIREN		(1 << 15)
#घोषणा SYSCON1_ADCKSEL(x)	(((x) & 3) << 16)
#घोषणा SYSCON1_ADCKSEL_MASK	(3 << 16)
#घोषणा SYSCON1_EXCKEN		(1 << 18)
#घोषणा SYSCON1_WAKEDIS		(1 << 19)
#घोषणा SYSCON1_IRTXM		(1 << 20)

#घोषणा SYSCON2_SERSEL		(1 << 0)
#घोषणा SYSCON2_KBD6		(1 << 1)
#घोषणा SYSCON2_DRAMZ		(1 << 2)
#घोषणा SYSCON2_KBWEN		(1 << 3)
#घोषणा SYSCON2_SS2TXEN		(1 << 4)
#घोषणा SYSCON2_PCCARD1		(1 << 5)
#घोषणा SYSCON2_PCCARD2		(1 << 6)
#घोषणा SYSCON2_SS2RXEN		(1 << 7)
#घोषणा SYSCON2_SS2MAEN		(1 << 9)
#घोषणा SYSCON2_OSTB		(1 << 12)
#घोषणा SYSCON2_CLKENSL		(1 << 13)
#घोषणा SYSCON2_BUZFREQ		(1 << 14)

#घोषणा SYSCON3_ADCCON		(1 << 0)
#घोषणा SYSCON3_CLKCTL0		(1 << 1)
#घोषणा SYSCON3_CLKCTL1		(1 << 2)
#घोषणा SYSCON3_DAISEL		(1 << 3)
#घोषणा SYSCON3_ADCCKNSEN	(1 << 4)
#घोषणा SYSCON3_VERSN(x)	(((x) >> 5) & 7)
#घोषणा SYSCON3_VERSN_MASK	(7 << 5)
#घोषणा SYSCON3_FASTWAKE	(1 << 8)
#घोषणा SYSCON3_DAIEN		(1 << 9)
#घोषणा SYSCON3_128FS		SYSCON3_DAIEN
#घोषणा SYSCON3_ENPD67		(1 << 10)

#घोषणा SYSCON_UARTEN		(1 << 8)

#घोषणा SYSFLG1_MCDR		(1 << 0)
#घोषणा SYSFLG1_DCDET		(1 << 1)
#घोषणा SYSFLG1_WUDR		(1 << 2)
#घोषणा SYSFLG1_WUON		(1 << 3)
#घोषणा SYSFLG1_CTS		(1 << 8)
#घोषणा SYSFLG1_DSR		(1 << 9)
#घोषणा SYSFLG1_DCD		(1 << 10)
#घोषणा SYSFLG1_NBFLG		(1 << 12)
#घोषणा SYSFLG1_RSTFLG		(1 << 13)
#घोषणा SYSFLG1_PFFLG		(1 << 14)
#घोषणा SYSFLG1_CLDFLG		(1 << 15)
#घोषणा SYSFLG1_CRXFE		(1 << 24)
#घोषणा SYSFLG1_CTXFF		(1 << 25)
#घोषणा SYSFLG1_SSIBUSY		(1 << 26)
#घोषणा SYSFLG1_ID		(1 << 29)
#घोषणा SYSFLG1_VERID(x)	(((x) >> 30) & 3)
#घोषणा SYSFLG1_VERID_MASK	(3 << 30)

#घोषणा SYSFLG2_SSRXOF		(1 << 0)
#घोषणा SYSFLG2_RESVAL		(1 << 1)
#घोषणा SYSFLG2_RESFRM		(1 << 2)
#घोषणा SYSFLG2_SS2RXFE		(1 << 3)
#घोषणा SYSFLG2_SS2TXFF		(1 << 4)
#घोषणा SYSFLG2_SS2TXUF		(1 << 5)
#घोषणा SYSFLG2_CKMODE		(1 << 6)

#घोषणा SYSFLG_UBUSY		(1 << 11)
#घोषणा SYSFLG_URXFE		(1 << 22)
#घोषणा SYSFLG_UTXFF		(1 << 23)

#पूर्ण_अगर
