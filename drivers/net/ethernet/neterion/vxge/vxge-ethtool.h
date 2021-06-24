<शैली गुरु>
/******************************************************************************
 * This software may be used and distributed according to the terms of
 * the GNU General Public License (GPL), incorporated herein by reference.
 * Drivers based on or derived from this code fall under the GPL and must
 * retain the authorship, copyright and license notice.  This file is not
 * a complete program and may only be used when the entire operating
 * प्रणाली is licensed under the GPL.
 * See the file COPYING in this distribution क्रम more inक्रमmation.
 *
 * vxge-ethtool.h: Driver क्रम Exar Corp's X3100 Series 10GbE PCIe I/O
 *                 Virtualized Server Adapter.
 * Copyright(c) 2002-2010 Exar Corp.
 ******************************************************************************/
#अगर_अघोषित _VXGE_ETHTOOL_H
#घोषणा _VXGE_ETHTOOL_H

#समावेश "vxge-main.h"

/* Ethtool related variables and Macros. */
अटल पूर्णांक vxge_ethtool_get_sset_count(काष्ठा net_device *dev, पूर्णांक sset);

#घोषणा VXGE_TITLE_LEN			5
#घोषणा VXGE_HW_VPATH_STATS_LEN 	27
#घोषणा VXGE_HW_AGGR_STATS_LEN  	13
#घोषणा VXGE_HW_PORT_STATS_LEN  	94
#घोषणा VXGE_HW_VPATH_TX_STATS_LEN	19
#घोषणा VXGE_HW_VPATH_RX_STATS_LEN	42
#घोषणा VXGE_SW_STATS_LEN		60
#घोषणा VXGE_HW_STATS_LEN	(VXGE_HW_VPATH_STATS_LEN +\
				VXGE_HW_AGGR_STATS_LEN +\
				VXGE_HW_PORT_STATS_LEN +\
				VXGE_HW_VPATH_TX_STATS_LEN +\
				VXGE_HW_VPATH_RX_STATS_LEN)

#घोषणा DRIVER_STAT_LEN (माप(ethtool_driver_stats_keys)/ETH_GSTRING_LEN)
#घोषणा STAT_LEN (VXGE_HW_STATS_LEN + DRIVER_STAT_LEN + VXGE_SW_STATS_LEN)

/* Maximum flicker समय of adapter LED */
#घोषणा VXGE_MAX_FLICKER_TIME (60 * HZ) /* 60 seconds */
#घोषणा VXGE_FLICKER_ON		1
#घोषणा VXGE_FLICKER_OFF	0

#घोषणा vxge_add_string(fmt, size, buf, ...) अणु\
	snम_लिखो(buf + *size, ETH_GSTRING_LEN, fmt, __VA_ARGS__); \
	*size += ETH_GSTRING_LEN; \
पूर्ण

#पूर्ण_अगर /*_VXGE_ETHTOOL_H*/
