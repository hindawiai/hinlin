<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/***********************************
 * $Id: quicc_simple.h,v 1.1 2002/03/02 15:01:10 gerg Exp $
 ***********************************
 *
 ***************************************
 * Simple drivers common header
 ***************************************
 */

#अगर_अघोषित __SIMPLE_H
#घोषणा __SIMPLE_H

/* #समावेश "quicc.h" */

#घोषणा GLB_SCC_0   0
#घोषणा GLB_SCC_1   1
#घोषणा GLB_SCC_2   2
#घोषणा GLB_SCC_3   3

प्रकार व्योम (पूर्णांक_routine)(अचिन्हित लघु पूर्णांकerrupt_event);
प्रकार पूर्णांक_routine *पूर्णांक_routine_ptr; 
प्रकार व्योम *(alloc_routine)(पूर्णांक length);
प्रकार व्योम (मुक्त_routine)(पूर्णांक scc_num, पूर्णांक channel_num, व्योम *buf);
प्रकार व्योम (store_rx_buffer_routine)(पूर्णांक scc_num, पूर्णांक channel_num, व्योम *buff, पूर्णांक length);
प्रकार पूर्णांक  (handle_tx_error_routine)(पूर्णांक scc_num, पूर्णांक channel_num, QUICC_BD *tbd);
प्रकार व्योम (handle_rx_error_routine)(पूर्णांक scc_num, पूर्णांक channel_num, QUICC_BD *rbd);
प्रकार व्योम (handle_lost_error_routine)(पूर्णांक scc_num, पूर्णांक channel_num);

/* user defined functions क्रम global errors */
प्रकार व्योम (handle_glob_overrun_routine)(पूर्णांक scc_number);
प्रकार व्योम (handle_glob_underrun_routine)(पूर्णांक scc_number);
प्रकार व्योम (glob_पूर्णांकr_q_overflow_routine)(पूर्णांक scc_number);

/*
 * General initialization and command routines
 */
व्योम quicc_issue_cmd (अचिन्हित लघु cmd, पूर्णांक scc_num);
व्योम quicc_init(व्योम);
व्योम quicc_scc_init(पूर्णांक scc_number, पूर्णांक number_of_rx_buf, पूर्णांक number_of_tx_buf);
व्योम quicc_smc_init(पूर्णांक smc_number, पूर्णांक number_of_rx_buf, पूर्णांक number_of_tx_buf);
व्योम quicc_scc_start(पूर्णांक scc_num);
व्योम quicc_scc_loopback(पूर्णांक scc_num);

/* Interrupt enable/disable routines क्रम critical pieces of code*/
अचिन्हित लघु  IntrDis(व्योम);
व्योम            IntrEna(अचिन्हित लघु old_sr);

/* For debugging */
व्योम prपूर्णांक_rbd(पूर्णांक scc_num);
व्योम prपूर्णांक_tbd(पूर्णांक scc_num);

#पूर्ण_अगर
