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

#घोषणा PHYS			0		/* physical addr */
#घोषणा PERM_ADDR		0x80		/* permanet address */
#घोषणा SB_STATIC		0x00000001
#घोषणा MAX_PAYLOAD		1562
#घोषणा PRIMARY_RING		0x00000001
#अगर_अघोषित शून्य
#घोषणा शून्य			0x00
#पूर्ण_अगर

/*********************** SB_Input Variable Values ***********************/
/*	 may be needed when ever the SBA state machine is called	*/

#घोषणा UNKNOWN_SYNC_SOURCE	0x0001
#घोषणा REQ_ALLOCATION		0x0002
#घोषणा REPORT_RESP		0x0003
#घोषणा CHANGE_RESP		0x0004
#घोषणा TNEG			0x0005
#घोषणा NIF			0x0006
#घोषणा SB_STOP			0x0007
#घोषणा SB_START		0x0008
#घोषणा REPORT_TIMER		0x0009
#घोषणा CHANGE_REQUIRED		0x000A

#घोषणा DEFAULT_OV		50

#अगर_घोषित SBA
/**************************** SBA STATES *****************************/

#घोषणा SBA_STANDBY		0x00000000
#घोषणा SBA_ACTIVE		0x00000001
#घोषणा SBA_RECOVERY		0x00000002
#घोषणा SBA_REPORT		0x00000003
#घोषणा SBA_CHANGE		0x00000004

/**************************** OTHERS *********************************/

#घोषणा FIFTY_PERCENT		50		/* bytes per second */
#घोषणा MAX_SESSIONS		150	
#घोषणा TWO_MINUTES		13079		/* 9.175 ms/tick */
#घोषणा FIFTY_BYTES		50
#घोषणा SBA_DENIED		0x0000000D
#घोषणा I_NEED_ONE		0x00000000
#घोषणा MAX_NODES		50
/*#घोषणा T_REPORT		0x59682F00L*/	/* 120s/80ns in Hex */
#घोषणा	TWO_MIN			120		/* seconds */
#घोषणा SBA_ST_UNKNOWN		0x00000002
#घोषणा SBA_ST_ACTIVE		0x00000001
#घोषणा S_CLEAR			0x00000000L
#घोषणा ZERO			0x00000000
#घोषणा FULL			0x00000000	/* old: 0xFFFFFFFFF */
#घोषणा S_SET			0x00000001L
#घोषणा LOW_PRIO		0x02		/* ??????? */
#घोषणा OK			0x01		/* ??????? */
#घोषणा NOT_OK			0x00		/* ??????? */

/****************************************/
/* deallocate_status[ni][si] values	*/
/****************************************/
#घोषणा TX_CHANGE		0X00000001L
#घोषणा PENDING			0x00000002L
#घोषणा NONE			0X00000000L
#पूर्ण_अगर
