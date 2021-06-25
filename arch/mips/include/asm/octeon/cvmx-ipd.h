<शैली गुरु>
/***********************license start***************
 * Author: Cavium Networks
 *
 * Contact: support@caviumnetworks.com
 * This file is part of the OCTEON SDK
 *
 * Copyright (c) 2003-2008 Cavium Networks
 *
 * This file is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License, Version 2, as
 * published by the Free Software Foundation.
 *
 * This file is distributed in the hope that it will be useful, but
 * AS-IS and WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE, TITLE, or
 * NONINFRINGEMENT.  See the GNU General Public License क्रम more
 * details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this file; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 51 Franklin St, Fअगरth Floor, Boston, MA 02110-1301 USA
 * or visit http://www.gnu.org/licenses/.
 *
 * This file may also be available under a dअगरferent license from Cavium.
 * Contact Cavium Networks क्रम more inक्रमmation
 ***********************license end**************************************/

/**
 *
 * Interface to the hardware Input Packet Data unit.
 */

#अगर_अघोषित __CVMX_IPD_H__
#घोषणा __CVMX_IPD_H__

#समावेश <यंत्र/octeon/octeon-feature.h>

#समावेश <यंत्र/octeon/cvmx-ipd-defs.h>
#समावेश <यंत्र/octeon/cvmx-pip-defs.h>

क्रमागत cvmx_ipd_mode अणु
   CVMX_IPD_OPC_MODE_STT = 0LL,	  /* All blocks DRAM, not cached in L2 */
   CVMX_IPD_OPC_MODE_STF = 1LL,	  /* All blocks पूर्णांकo  L2 */
   CVMX_IPD_OPC_MODE_STF1_STT = 2LL,   /* 1st block L2, rest DRAM */
   CVMX_IPD_OPC_MODE_STF2_STT = 3LL    /* 1st, 2nd blocks L2, rest DRAM */
पूर्ण;

#अगर_अघोषित CVMX_ENABLE_LEN_M8_FIX
#घोषणा CVMX_ENABLE_LEN_M8_FIX 0
#पूर्ण_अगर

/* CSR प्रकारs have been moved to cvmx-csr-*.h */
प्रकार जोड़ cvmx_ipd_1st_mbuff_skip cvmx_ipd_mbuff_first_skip_t;
प्रकार जोड़ cvmx_ipd_1st_next_ptr_back cvmx_ipd_first_next_ptr_back_t;

प्रकार cvmx_ipd_mbuff_first_skip_t cvmx_ipd_mbuff_not_first_skip_t;
प्रकार cvmx_ipd_first_next_ptr_back_t cvmx_ipd_second_next_ptr_back_t;

/**
 * Configure IPD
 *
 * @mbuff_size: Packets buffer size in 8 byte words
 * @first_mbuff_skip:
 *		     Number of 8 byte words to skip in the first buffer
 * @not_first_mbuff_skip:
 *		     Number of 8 byte words to skip in each following buffer
 * @first_back: Must be same as first_mbuff_skip / 128
 * @second_back:
 *		     Must be same as not_first_mbuff_skip / 128
 * @wqe_fpa_pool:
 *		     FPA pool to get work entries from
 * @cache_mode:
 * @back_pres_enable_flag:
 *		     Enable or disable port back pressure
 */
अटल अंतरभूत व्योम cvmx_ipd_config(uपूर्णांक64_t mbuff_size,
				   uपूर्णांक64_t first_mbuff_skip,
				   uपूर्णांक64_t not_first_mbuff_skip,
				   uपूर्णांक64_t first_back,
				   uपूर्णांक64_t second_back,
				   uपूर्णांक64_t wqe_fpa_pool,
				   क्रमागत cvmx_ipd_mode cache_mode,
				   uपूर्णांक64_t back_pres_enable_flag)
अणु
	cvmx_ipd_mbuff_first_skip_t first_skip;
	cvmx_ipd_mbuff_not_first_skip_t not_first_skip;
	जोड़ cvmx_ipd_packet_mbuff_size size;
	cvmx_ipd_first_next_ptr_back_t first_back_काष्ठा;
	cvmx_ipd_second_next_ptr_back_t second_back_काष्ठा;
	जोड़ cvmx_ipd_wqe_fpa_queue wqe_pool;
	जोड़ cvmx_ipd_ctl_status ipd_ctl_reg;

	first_skip.u64 = 0;
	first_skip.s.skip_sz = first_mbuff_skip;
	cvmx_ग_लिखो_csr(CVMX_IPD_1ST_MBUFF_SKIP, first_skip.u64);

	not_first_skip.u64 = 0;
	not_first_skip.s.skip_sz = not_first_mbuff_skip;
	cvmx_ग_लिखो_csr(CVMX_IPD_NOT_1ST_MBUFF_SKIP, not_first_skip.u64);

	size.u64 = 0;
	size.s.mb_size = mbuff_size;
	cvmx_ग_लिखो_csr(CVMX_IPD_PACKET_MBUFF_SIZE, size.u64);

	first_back_काष्ठा.u64 = 0;
	first_back_काष्ठा.s.back = first_back;
	cvmx_ग_लिखो_csr(CVMX_IPD_1st_NEXT_PTR_BACK, first_back_काष्ठा.u64);

	second_back_काष्ठा.u64 = 0;
	second_back_काष्ठा.s.back = second_back;
	cvmx_ग_लिखो_csr(CVMX_IPD_2nd_NEXT_PTR_BACK, second_back_काष्ठा.u64);

	wqe_pool.u64 = 0;
	wqe_pool.s.wqe_pool = wqe_fpa_pool;
	cvmx_ग_लिखो_csr(CVMX_IPD_WQE_FPA_QUEUE, wqe_pool.u64);

	ipd_ctl_reg.u64 = cvmx_पढ़ो_csr(CVMX_IPD_CTL_STATUS);
	ipd_ctl_reg.s.opc_mode = cache_mode;
	ipd_ctl_reg.s.pbp_en = back_pres_enable_flag;
	cvmx_ग_लिखो_csr(CVMX_IPD_CTL_STATUS, ipd_ctl_reg.u64);

	/* Note: the example RED code that used to be here has been moved to
	   cvmx_helper_setup_red */
पूर्ण

/**
 * Enable IPD
 */
अटल अंतरभूत व्योम cvmx_ipd_enable(व्योम)
अणु
	जोड़ cvmx_ipd_ctl_status ipd_reg;
	ipd_reg.u64 = cvmx_पढ़ो_csr(CVMX_IPD_CTL_STATUS);
	अगर (ipd_reg.s.ipd_en) अणु
		cvmx_dम_लिखो
		    ("Warning: Enabling IPD when IPD already enabled.\n");
	पूर्ण
	ipd_reg.s.ipd_en = 1;
#अगर  CVMX_ENABLE_LEN_M8_FIX
	अगर (!OCTEON_IS_MODEL(OCTEON_CN38XX_PASS2))
		ipd_reg.s.len_m8 = TRUE;
#पूर्ण_अगर
	cvmx_ग_लिखो_csr(CVMX_IPD_CTL_STATUS, ipd_reg.u64);
पूर्ण

/**
 * Disable IPD
 */
अटल अंतरभूत व्योम cvmx_ipd_disable(व्योम)
अणु
	जोड़ cvmx_ipd_ctl_status ipd_reg;
	ipd_reg.u64 = cvmx_पढ़ो_csr(CVMX_IPD_CTL_STATUS);
	ipd_reg.s.ipd_en = 0;
	cvmx_ग_लिखो_csr(CVMX_IPD_CTL_STATUS, ipd_reg.u64);
पूर्ण

/**
 * Supportive function क्रम cvmx_fpa_shutकरोwn_pool.
 */
अटल अंतरभूत व्योम cvmx_ipd_मुक्त_ptr(व्योम)
अणु
	/* Only CN38XXpअणु1,2पूर्ण cannot पढ़ो poपूर्णांकer out of the IPD */
	अगर (!OCTEON_IS_MODEL(OCTEON_CN38XX_PASS1)
	    && !OCTEON_IS_MODEL(OCTEON_CN38XX_PASS2)) अणु
		पूर्णांक no_wptr = 0;
		जोड़ cvmx_ipd_ptr_count ipd_ptr_count;
		ipd_ptr_count.u64 = cvmx_पढ़ो_csr(CVMX_IPD_PTR_COUNT);

		/* Handle Work Queue Entry in cn56xx and cn52xx */
		अगर (octeon_has_feature(OCTEON_FEATURE_NO_WPTR)) अणु
			जोड़ cvmx_ipd_ctl_status ipd_ctl_status;
			ipd_ctl_status.u64 = cvmx_पढ़ो_csr(CVMX_IPD_CTL_STATUS);
			अगर (ipd_ctl_status.s.no_wptr)
				no_wptr = 1;
		पूर्ण

		/* Free the prefetched WQE */
		अगर (ipd_ptr_count.s.wqev_cnt) अणु
			जोड़ cvmx_ipd_wqe_ptr_valid ipd_wqe_ptr_valid;
			ipd_wqe_ptr_valid.u64 =
			    cvmx_पढ़ो_csr(CVMX_IPD_WQE_PTR_VALID);
			अगर (no_wptr)
				cvmx_fpa_मुक्त(cvmx_phys_to_ptr
					      ((uपूर्णांक64_t) ipd_wqe_ptr_valid.s.
					       ptr << 7), CVMX_FPA_PACKET_POOL,
					      0);
			अन्यथा
				cvmx_fpa_मुक्त(cvmx_phys_to_ptr
					      ((uपूर्णांक64_t) ipd_wqe_ptr_valid.s.
					       ptr << 7), CVMX_FPA_WQE_POOL, 0);
		पूर्ण

		/* Free all WQE in the fअगरo */
		अगर (ipd_ptr_count.s.wqe_pcnt) अणु
			पूर्णांक i;
			जोड़ cvmx_ipd_pwp_ptr_fअगरo_ctl ipd_pwp_ptr_fअगरo_ctl;
			ipd_pwp_ptr_fअगरo_ctl.u64 =
			    cvmx_पढ़ो_csr(CVMX_IPD_PWP_PTR_FIFO_CTL);
			क्रम (i = 0; i < ipd_ptr_count.s.wqe_pcnt; i++) अणु
				ipd_pwp_ptr_fअगरo_ctl.s.cena = 0;
				ipd_pwp_ptr_fअगरo_ctl.s.raddr =
				    ipd_pwp_ptr_fअगरo_ctl.s.max_cnts +
				    (ipd_pwp_ptr_fअगरo_ctl.s.wraddr +
				     i) % ipd_pwp_ptr_fअगरo_ctl.s.max_cnts;
				cvmx_ग_लिखो_csr(CVMX_IPD_PWP_PTR_FIFO_CTL,
					       ipd_pwp_ptr_fअगरo_ctl.u64);
				ipd_pwp_ptr_fअगरo_ctl.u64 =
				    cvmx_पढ़ो_csr(CVMX_IPD_PWP_PTR_FIFO_CTL);
				अगर (no_wptr)
					cvmx_fpa_मुक्त(cvmx_phys_to_ptr
						      ((uपूर्णांक64_t)
						       ipd_pwp_ptr_fअगरo_ctl.s.
						       ptr << 7),
						      CVMX_FPA_PACKET_POOL, 0);
				अन्यथा
					cvmx_fpa_मुक्त(cvmx_phys_to_ptr
						      ((uपूर्णांक64_t)
						       ipd_pwp_ptr_fअगरo_ctl.s.
						       ptr << 7),
						      CVMX_FPA_WQE_POOL, 0);
			पूर्ण
			ipd_pwp_ptr_fअगरo_ctl.s.cena = 1;
			cvmx_ग_लिखो_csr(CVMX_IPD_PWP_PTR_FIFO_CTL,
				       ipd_pwp_ptr_fअगरo_ctl.u64);
		पूर्ण

		/* Free the prefetched packet */
		अगर (ipd_ptr_count.s.pktv_cnt) अणु
			जोड़ cvmx_ipd_pkt_ptr_valid ipd_pkt_ptr_valid;
			ipd_pkt_ptr_valid.u64 =
			    cvmx_पढ़ो_csr(CVMX_IPD_PKT_PTR_VALID);
			cvmx_fpa_मुक्त(cvmx_phys_to_ptr
				      (ipd_pkt_ptr_valid.s.ptr << 7),
				      CVMX_FPA_PACKET_POOL, 0);
		पूर्ण

		/* Free the per port prefetched packets */
		अगर (1) अणु
			पूर्णांक i;
			जोड़ cvmx_ipd_prc_port_ptr_fअगरo_ctl
			    ipd_prc_port_ptr_fअगरo_ctl;
			ipd_prc_port_ptr_fअगरo_ctl.u64 =
			    cvmx_पढ़ो_csr(CVMX_IPD_PRC_PORT_PTR_FIFO_CTL);

			क्रम (i = 0; i < ipd_prc_port_ptr_fअगरo_ctl.s.max_pkt;
			     i++) अणु
				ipd_prc_port_ptr_fअगरo_ctl.s.cena = 0;
				ipd_prc_port_ptr_fअगरo_ctl.s.raddr =
				    i % ipd_prc_port_ptr_fअगरo_ctl.s.max_pkt;
				cvmx_ग_लिखो_csr(CVMX_IPD_PRC_PORT_PTR_FIFO_CTL,
					       ipd_prc_port_ptr_fअगरo_ctl.u64);
				ipd_prc_port_ptr_fअगरo_ctl.u64 =
				    cvmx_पढ़ो_csr
				    (CVMX_IPD_PRC_PORT_PTR_FIFO_CTL);
				cvmx_fpa_मुक्त(cvmx_phys_to_ptr
					      ((uपूर्णांक64_t)
					       ipd_prc_port_ptr_fअगरo_ctl.s.
					       ptr << 7), CVMX_FPA_PACKET_POOL,
					      0);
			पूर्ण
			ipd_prc_port_ptr_fअगरo_ctl.s.cena = 1;
			cvmx_ग_लिखो_csr(CVMX_IPD_PRC_PORT_PTR_FIFO_CTL,
				       ipd_prc_port_ptr_fअगरo_ctl.u64);
		पूर्ण

		/* Free all packets in the holding fअगरo */
		अगर (ipd_ptr_count.s.pfअगर_cnt) अणु
			पूर्णांक i;
			जोड़ cvmx_ipd_prc_hold_ptr_fअगरo_ctl
			    ipd_prc_hold_ptr_fअगरo_ctl;

			ipd_prc_hold_ptr_fअगरo_ctl.u64 =
			    cvmx_पढ़ो_csr(CVMX_IPD_PRC_HOLD_PTR_FIFO_CTL);

			क्रम (i = 0; i < ipd_ptr_count.s.pfअगर_cnt; i++) अणु
				ipd_prc_hold_ptr_fअगरo_ctl.s.cena = 0;
				ipd_prc_hold_ptr_fअगरo_ctl.s.raddr =
				    (ipd_prc_hold_ptr_fअगरo_ctl.s.praddr +
				     i) % ipd_prc_hold_ptr_fअगरo_ctl.s.max_pkt;
				cvmx_ग_लिखो_csr(CVMX_IPD_PRC_HOLD_PTR_FIFO_CTL,
					       ipd_prc_hold_ptr_fअगरo_ctl.u64);
				ipd_prc_hold_ptr_fअगरo_ctl.u64 =
				    cvmx_पढ़ो_csr
				    (CVMX_IPD_PRC_HOLD_PTR_FIFO_CTL);
				cvmx_fpa_मुक्त(cvmx_phys_to_ptr
					      ((uपूर्णांक64_t)
					       ipd_prc_hold_ptr_fअगरo_ctl.s.
					       ptr << 7), CVMX_FPA_PACKET_POOL,
					      0);
			पूर्ण
			ipd_prc_hold_ptr_fअगरo_ctl.s.cena = 1;
			cvmx_ग_लिखो_csr(CVMX_IPD_PRC_HOLD_PTR_FIFO_CTL,
				       ipd_prc_hold_ptr_fअगरo_ctl.u64);
		पूर्ण

		/* Free all packets in the fअगरo */
		अगर (ipd_ptr_count.s.pkt_pcnt) अणु
			पूर्णांक i;
			जोड़ cvmx_ipd_pwp_ptr_fअगरo_ctl ipd_pwp_ptr_fअगरo_ctl;
			ipd_pwp_ptr_fअगरo_ctl.u64 =
			    cvmx_पढ़ो_csr(CVMX_IPD_PWP_PTR_FIFO_CTL);

			क्रम (i = 0; i < ipd_ptr_count.s.pkt_pcnt; i++) अणु
				ipd_pwp_ptr_fअगरo_ctl.s.cena = 0;
				ipd_pwp_ptr_fअगरo_ctl.s.raddr =
				    (ipd_pwp_ptr_fअगरo_ctl.s.praddr +
				     i) % ipd_pwp_ptr_fअगरo_ctl.s.max_cnts;
				cvmx_ग_लिखो_csr(CVMX_IPD_PWP_PTR_FIFO_CTL,
					       ipd_pwp_ptr_fअगरo_ctl.u64);
				ipd_pwp_ptr_fअगरo_ctl.u64 =
				    cvmx_पढ़ो_csr(CVMX_IPD_PWP_PTR_FIFO_CTL);
				cvmx_fpa_मुक्त(cvmx_phys_to_ptr
					      ((uपूर्णांक64_t) ipd_pwp_ptr_fअगरo_ctl.
					       s.ptr << 7),
					      CVMX_FPA_PACKET_POOL, 0);
			पूर्ण
			ipd_pwp_ptr_fअगरo_ctl.s.cena = 1;
			cvmx_ग_लिखो_csr(CVMX_IPD_PWP_PTR_FIFO_CTL,
				       ipd_pwp_ptr_fअगरo_ctl.u64);
		पूर्ण

		/* Reset the IPD to get all buffers out of it */
		अणु
			जोड़ cvmx_ipd_ctl_status ipd_ctl_status;
			ipd_ctl_status.u64 = cvmx_पढ़ो_csr(CVMX_IPD_CTL_STATUS);
			ipd_ctl_status.s.reset = 1;
			cvmx_ग_लिखो_csr(CVMX_IPD_CTL_STATUS, ipd_ctl_status.u64);
		पूर्ण

		/* Reset the PIP */
		अणु
			जोड़ cvmx_pip_sft_rst pip_sft_rst;
			pip_sft_rst.u64 = cvmx_पढ़ो_csr(CVMX_PIP_SFT_RST);
			pip_sft_rst.s.rst = 1;
			cvmx_ग_लिखो_csr(CVMX_PIP_SFT_RST, pip_sft_rst.u64);
		पूर्ण
	पूर्ण
पूर्ण

#पूर्ण_अगर /*  __CVMX_IPD_H__ */
