<शैली गुरु>
/*
 * Platक्रमm inक्रमmation definitions क्रम the CPM Uart driver.
 *
 * 2006 (c) MontaVista Software, Inc.
 * Vitaly Bordug <vbordug@ru.mvista.com>
 *
 * This file is licensed under the terms of the GNU General Public License
 * version 2. This program is licensed "as is" without any warranty of any
 * kind, whether express or implied.
 */

#अगर_अघोषित FS_UART_PD_H
#घोषणा FS_UART_PD_H

#समावेश <यंत्र/types.h>

क्रमागत fs_uart_id अणु
	fsid_smc1_uart,
	fsid_smc2_uart,
	fsid_scc1_uart,
	fsid_scc2_uart,
	fsid_scc3_uart,
	fsid_scc4_uart,
	fs_uart_nr,
पूर्ण;

अटल अंतरभूत पूर्णांक fs_uart_id_scc2fsid(पूर्णांक id)
अणु
    वापस fsid_scc1_uart + id - 1;
पूर्ण

अटल अंतरभूत पूर्णांक fs_uart_id_fsid2scc(पूर्णांक id)
अणु
    वापस id - fsid_scc1_uart + 1;
पूर्ण

अटल अंतरभूत पूर्णांक fs_uart_id_smc2fsid(पूर्णांक id)
अणु
    वापस fsid_smc1_uart + id - 1;
पूर्ण

अटल अंतरभूत पूर्णांक fs_uart_id_fsid2smc(पूर्णांक id)
अणु
    वापस id - fsid_smc1_uart + 1;
पूर्ण

काष्ठा fs_uart_platक्रमm_info अणु
        व्योम(*init_ioports)(काष्ठा fs_uart_platक्रमm_info *);
	/* device specअगरic inक्रमmation */
	पूर्णांक fs_no;		/* controller index */
	अक्षर fs_type[4];        /* controller type  */
	u32 uart_clk;
	u8 tx_num_fअगरo;
	u8 tx_buf_size;
	u8 rx_num_fअगरo;
	u8 rx_buf_size;
	u8 brg;
	u8 clk_rx;
	u8 clk_tx;
पूर्ण;

अटल अंतरभूत पूर्णांक fs_uart_get_id(काष्ठा fs_uart_platक्रमm_info *fpi)
अणु
        अगर(म_माला(fpi->fs_type, "SMC"))
                वापस fs_uart_id_smc2fsid(fpi->fs_no);
        अगर(म_माला(fpi->fs_type, "SCC"))
                वापस fs_uart_id_scc2fsid(fpi->fs_no);
        वापस fpi->fs_no;
पूर्ण

#पूर्ण_अगर
