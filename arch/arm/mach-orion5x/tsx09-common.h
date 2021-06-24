<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ARCH_ORION5X_TSX09_COMMON_H
#घोषणा __ARCH_ORION5X_TSX09_COMMON_H

/*
 * QNAP TS-x09 Boards घातer-off function
 */
बाह्य व्योम qnap_tsx09_घातer_off(व्योम);

/*
 * QNAP TS-x09 Boards function to find Ethernet MAC address in flash memory
 */
बाह्य व्योम __init qnap_tsx09_find_mac_addr(u32 mem_base, u32 size);

/*
 * QNAP TS-x09 Boards ethernet declaration
 */
बाह्य काष्ठा mv643xx_eth_platक्रमm_data qnap_tsx09_eth_data;


#पूर्ण_अगर
