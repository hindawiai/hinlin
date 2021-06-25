<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*      cops.h: LocalTalk driver क्रम Linux.
 *
 *      Authors:
 *      - Jay Schulist <jschlst@samba.org>
 */

#अगर_अघोषित __LINUX_COPSLTALK_H
#घोषणा __LINUX_COPSLTALK_H

#अगर_घोषित __KERNEL__

/* Max LLAP size we will accept. */
#घोषणा MAX_LLAP_SIZE		603

/* Tangent */
#घोषणा TANG_CARD_STATUS        1
#घोषणा TANG_CLEAR_INT          1
#घोषणा TANG_RESET              3

#घोषणा TANG_TX_READY           1
#घोषणा TANG_RX_READY           2

/* Dayna */
#घोषणा DAYNA_CMD_DATA          0
#घोषणा DAYNA_CLEAR_INT         1
#घोषणा DAYNA_CARD_STATUS       2
#घोषणा DAYNA_INT_CARD          3
#घोषणा DAYNA_RESET             4

#घोषणा DAYNA_RX_READY          0
#घोषणा DAYNA_TX_READY          1
#घोषणा DAYNA_RX_REQUEST        3

/* Same on both card types */
#घोषणा COPS_CLEAR_INT  1

/* LAP response codes received from the cards. */
#घोषणा LAP_INIT        1       /* Init cmd */
#घोषणा LAP_INIT_RSP    2       /* Init response */
#घोषणा LAP_WRITE       3       /* Write cmd */
#घोषणा DATA_READ       4       /* Data पढ़ो */
#घोषणा LAP_RESPONSE    4       /* Received ALAP frame response */
#घोषणा LAP_GETSTAT     5       /* Get LAP and HW status */
#घोषणा LAP_RSPSTAT     6       /* Status response */

#पूर्ण_अगर

/*
 *	Structure to hold the firmware inक्रमmation.
 */
काष्ठा ltfirmware
अणु
        अचिन्हित पूर्णांक length;
        स्थिर अचिन्हित अक्षर *data;
पूर्ण;

#घोषणा DAYNA 1
#घोषणा TANGENT 2

#पूर्ण_अगर
