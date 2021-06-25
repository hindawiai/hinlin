<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/******************************************************************************
 *
 *	(C)Copyright 1998,1999 SysKonnect,
 *	a business unit of Schneider & Koch & Co. Datenप्रणालीe GmbH.
 *
 *	The inक्रमmation in this file is provided "AS IS" without warranty.
 *
 ******************************************************************************/

#अगर_अघोषित	_FDDI_
#घोषणा _FDDI_

काष्ठा fddi_addr अणु
	u_अक्षर	a[6] ;
पूर्ण ;

#घोषणा GROUP_ADDR	0x80		/* MSB in a[0] */

काष्ठा fddi_mac अणु
	काष्ठा fddi_addr	mac_dest ;
	काष्ठा fddi_addr	mac_source ;
	u_अक्षर			mac_info[4478] ;
पूर्ण ;

#घोषणा FDDI_MAC_SIZE	(12)
#घोषणा FDDI_RAW_MTU	(4500-5)	/* exl. Pr,SD, ED/FS */
#घोषणा FDDI_RAW	(4500)

/*
 * FC values
 */
#घोषणा FC_VOID		0x40		/* व्योम frame */
#घोषणा FC_TOKEN	0x80		/* token */
#घोषणा FC_RES_TOKEN	0xc0		/* restricted token */
#घोषणा FC_SMT_INFO	0x41		/* SMT Info frame */
/*
 * FC_SMT_LAN_LOC && FC_SMT_LOC are SK specअगरic !
 */
#घोषणा FC_SMT_LAN_LOC	0x42		/* local SMT Info frame */
#घोषणा FC_SMT_LOC	0x43		/* local SMT Info frame */
#घोषणा FC_SMT_NSA	0x4f		/* SMT NSA frame */
#घोषणा FC_MAC		0xc0		/* MAC frame */
#घोषणा FC_BEACON	0xc2		/* MAC beacon frame */
#घोषणा FC_CLAIM	0xc3		/* MAC claim frame */
#घोषणा FC_SYNC_LLC	0xd0		/* sync. LLC frame */
#घोषणा FC_ASYNC_LLC	0x50		/* async. LLC frame */
#घोषणा FC_SYNC_BIT	0x80		/* sync. bit in FC */

#घोषणा FC_LLC_PRIOR	0x07		/* priority bits */

#घोषणा BEACON_INFO	0		/* beacon type */
#घोषणा DBEACON_INFO	1		/* beacon type सूचीECTED */


/*
 * indicator bits
 */
#घोषणा C_INDICATOR	(1<<0)
#घोषणा A_INDICATOR	(1<<1)
#घोषणा E_INDICATOR	(1<<2)
#घोषणा I_INDICATOR	(1<<6)		/* SK specअगरic */ 
#घोषणा L_INDICATOR	(1<<7)		/* SK specअगरic */

#पूर्ण_अगर	/* _FDDI_ */
