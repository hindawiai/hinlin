<शैली गुरु>
/*
 * Copyright 2012 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#अगर_अघोषित CIK_STRUCTS_H_
#घोषणा CIK_STRUCTS_H_

काष्ठा cik_mqd अणु
	uपूर्णांक32_t header;
	uपूर्णांक32_t compute_dispatch_initiator;
	uपूर्णांक32_t compute_dim_x;
	uपूर्णांक32_t compute_dim_y;
	uपूर्णांक32_t compute_dim_z;
	uपूर्णांक32_t compute_start_x;
	uपूर्णांक32_t compute_start_y;
	uपूर्णांक32_t compute_start_z;
	uपूर्णांक32_t compute_num_thपढ़ो_x;
	uपूर्णांक32_t compute_num_thपढ़ो_y;
	uपूर्णांक32_t compute_num_thपढ़ो_z;
	uपूर्णांक32_t compute_pipelinestat_enable;
	uपूर्णांक32_t compute_perfcount_enable;
	uपूर्णांक32_t compute_pgm_lo;
	uपूर्णांक32_t compute_pgm_hi;
	uपूर्णांक32_t compute_tba_lo;
	uपूर्णांक32_t compute_tba_hi;
	uपूर्णांक32_t compute_पंचांगa_lo;
	uपूर्णांक32_t compute_पंचांगa_hi;
	uपूर्णांक32_t compute_pgm_rsrc1;
	uपूर्णांक32_t compute_pgm_rsrc2;
	uपूर्णांक32_t compute_vmid;
	uपूर्णांक32_t compute_resource_limits;
	uपूर्णांक32_t compute_अटल_thपढ़ो_mgmt_se0;
	uपूर्णांक32_t compute_अटल_thपढ़ो_mgmt_se1;
	uपूर्णांक32_t compute_पंचांगpring_size;
	uपूर्णांक32_t compute_अटल_thपढ़ो_mgmt_se2;
	uपूर्णांक32_t compute_अटल_thपढ़ो_mgmt_se3;
	uपूर्णांक32_t compute_restart_x;
	uपूर्णांक32_t compute_restart_y;
	uपूर्णांक32_t compute_restart_z;
	uपूर्णांक32_t compute_thपढ़ो_trace_enable;
	uपूर्णांक32_t compute_misc_reserved;
	uपूर्णांक32_t compute_user_data_0;
	uपूर्णांक32_t compute_user_data_1;
	uपूर्णांक32_t compute_user_data_2;
	uपूर्णांक32_t compute_user_data_3;
	uपूर्णांक32_t compute_user_data_4;
	uपूर्णांक32_t compute_user_data_5;
	uपूर्णांक32_t compute_user_data_6;
	uपूर्णांक32_t compute_user_data_7;
	uपूर्णांक32_t compute_user_data_8;
	uपूर्णांक32_t compute_user_data_9;
	uपूर्णांक32_t compute_user_data_10;
	uपूर्णांक32_t compute_user_data_11;
	uपूर्णांक32_t compute_user_data_12;
	uपूर्णांक32_t compute_user_data_13;
	uपूर्णांक32_t compute_user_data_14;
	uपूर्णांक32_t compute_user_data_15;
	uपूर्णांक32_t cp_compute_csinvoc_count_lo;
	uपूर्णांक32_t cp_compute_csinvoc_count_hi;
	uपूर्णांक32_t cp_mqd_base_addr_lo;
	uपूर्णांक32_t cp_mqd_base_addr_hi;
	uपूर्णांक32_t cp_hqd_active;
	uपूर्णांक32_t cp_hqd_vmid;
	uपूर्णांक32_t cp_hqd_persistent_state;
	uपूर्णांक32_t cp_hqd_pipe_priority;
	uपूर्णांक32_t cp_hqd_queue_priority;
	uपूर्णांक32_t cp_hqd_quantum;
	uपूर्णांक32_t cp_hqd_pq_base_lo;
	uपूर्णांक32_t cp_hqd_pq_base_hi;
	uपूर्णांक32_t cp_hqd_pq_rptr;
	uपूर्णांक32_t cp_hqd_pq_rptr_report_addr_lo;
	uपूर्णांक32_t cp_hqd_pq_rptr_report_addr_hi;
	uपूर्णांक32_t cp_hqd_pq_wptr_poll_addr_lo;
	uपूर्णांक32_t cp_hqd_pq_wptr_poll_addr_hi;
	uपूर्णांक32_t cp_hqd_pq_करोorbell_control;
	uपूर्णांक32_t cp_hqd_pq_wptr;
	uपूर्णांक32_t cp_hqd_pq_control;
	uपूर्णांक32_t cp_hqd_ib_base_addr_lo;
	uपूर्णांक32_t cp_hqd_ib_base_addr_hi;
	uपूर्णांक32_t cp_hqd_ib_rptr;
	uपूर्णांक32_t cp_hqd_ib_control;
	uपूर्णांक32_t cp_hqd_iq_समयr;
	uपूर्णांक32_t cp_hqd_iq_rptr;
	uपूर्णांक32_t cp_hqd_dequeue_request;
	uपूर्णांक32_t cp_hqd_dma_offload;
	uपूर्णांक32_t cp_hqd_sema_cmd;
	uपूर्णांक32_t cp_hqd_msg_type;
	uपूर्णांक32_t cp_hqd_atomic0_preop_lo;
	uपूर्णांक32_t cp_hqd_atomic0_preop_hi;
	uपूर्णांक32_t cp_hqd_atomic1_preop_lo;
	uपूर्णांक32_t cp_hqd_atomic1_preop_hi;
	uपूर्णांक32_t cp_hqd_hq_status0;
	uपूर्णांक32_t cp_hqd_hq_control0;
	uपूर्णांक32_t cp_mqd_control;
	uपूर्णांक32_t cp_mqd_query_समय_lo;
	uपूर्णांक32_t cp_mqd_query_समय_hi;
	uपूर्णांक32_t cp_mqd_connect_start_समय_lo;
	uपूर्णांक32_t cp_mqd_connect_start_समय_hi;
	uपूर्णांक32_t cp_mqd_connect_end_समय_lo;
	uपूर्णांक32_t cp_mqd_connect_end_समय_hi;
	uपूर्णांक32_t cp_mqd_connect_end_wf_count;
	uपूर्णांक32_t cp_mqd_connect_end_pq_rptr;
	uपूर्णांक32_t cp_mqd_connect_end_pq_wptr;
	uपूर्णांक32_t cp_mqd_connect_end_ib_rptr;
	uपूर्णांक32_t reserved_96;
	uपूर्णांक32_t reserved_97;
	uपूर्णांक32_t reserved_98;
	uपूर्णांक32_t reserved_99;
	uपूर्णांक32_t iqसमयr_pkt_header;
	uपूर्णांक32_t iqसमयr_pkt_dw0;
	uपूर्णांक32_t iqसमयr_pkt_dw1;
	uपूर्णांक32_t iqसमयr_pkt_dw2;
	uपूर्णांक32_t iqसमयr_pkt_dw3;
	uपूर्णांक32_t iqसमयr_pkt_dw4;
	uपूर्णांक32_t iqसमयr_pkt_dw5;
	uपूर्णांक32_t iqसमयr_pkt_dw6;
	uपूर्णांक32_t reserved_108;
	uपूर्णांक32_t reserved_109;
	uपूर्णांक32_t reserved_110;
	uपूर्णांक32_t reserved_111;
	uपूर्णांक32_t queue_करोorbell_id0;
	uपूर्णांक32_t queue_करोorbell_id1;
	uपूर्णांक32_t queue_करोorbell_id2;
	uपूर्णांक32_t queue_करोorbell_id3;
	uपूर्णांक32_t queue_करोorbell_id4;
	uपूर्णांक32_t queue_करोorbell_id5;
	uपूर्णांक32_t queue_करोorbell_id6;
	uपूर्णांक32_t queue_करोorbell_id7;
	uपूर्णांक32_t queue_करोorbell_id8;
	uपूर्णांक32_t queue_करोorbell_id9;
	uपूर्णांक32_t queue_करोorbell_id10;
	uपूर्णांक32_t queue_करोorbell_id11;
	uपूर्णांक32_t queue_करोorbell_id12;
	uपूर्णांक32_t queue_करोorbell_id13;
	uपूर्णांक32_t queue_करोorbell_id14;
	uपूर्णांक32_t queue_करोorbell_id15;
पूर्ण;

काष्ठा cik_sdma_rlc_रेजिस्टरs अणु
	uपूर्णांक32_t sdma_rlc_rb_cntl;
	uपूर्णांक32_t sdma_rlc_rb_base;
	uपूर्णांक32_t sdma_rlc_rb_base_hi;
	uपूर्णांक32_t sdma_rlc_rb_rptr;
	uपूर्णांक32_t sdma_rlc_rb_wptr;
	uपूर्णांक32_t sdma_rlc_rb_wptr_poll_cntl;
	uपूर्णांक32_t sdma_rlc_rb_wptr_poll_addr_hi;
	uपूर्णांक32_t sdma_rlc_rb_wptr_poll_addr_lo;
	uपूर्णांक32_t sdma_rlc_rb_rptr_addr_hi;
	uपूर्णांक32_t sdma_rlc_rb_rptr_addr_lo;
	uपूर्णांक32_t sdma_rlc_ib_cntl;
	uपूर्णांक32_t sdma_rlc_ib_rptr;
	uपूर्णांक32_t sdma_rlc_ib_offset;
	uपूर्णांक32_t sdma_rlc_ib_base_lo;
	uपूर्णांक32_t sdma_rlc_ib_base_hi;
	uपूर्णांक32_t sdma_rlc_ib_size;
	uपूर्णांक32_t sdma_rlc_skip_cntl;
	uपूर्णांक32_t sdma_rlc_context_status;
	uपूर्णांक32_t sdma_rlc_करोorbell;
	uपूर्णांक32_t sdma_rlc_भव_addr;
	uपूर्णांक32_t sdma_rlc_ape1_cntl;
	uपूर्णांक32_t sdma_rlc_करोorbell_log;
	uपूर्णांक32_t reserved_22;
	uपूर्णांक32_t reserved_23;
	uपूर्णांक32_t reserved_24;
	uपूर्णांक32_t reserved_25;
	uपूर्णांक32_t reserved_26;
	uपूर्णांक32_t reserved_27;
	uपूर्णांक32_t reserved_28;
	uपूर्णांक32_t reserved_29;
	uपूर्णांक32_t reserved_30;
	uपूर्णांक32_t reserved_31;
	uपूर्णांक32_t reserved_32;
	uपूर्णांक32_t reserved_33;
	uपूर्णांक32_t reserved_34;
	uपूर्णांक32_t reserved_35;
	uपूर्णांक32_t reserved_36;
	uपूर्णांक32_t reserved_37;
	uपूर्णांक32_t reserved_38;
	uपूर्णांक32_t reserved_39;
	uपूर्णांक32_t reserved_40;
	uपूर्णांक32_t reserved_41;
	uपूर्णांक32_t reserved_42;
	uपूर्णांक32_t reserved_43;
	uपूर्णांक32_t reserved_44;
	uपूर्णांक32_t reserved_45;
	uपूर्णांक32_t reserved_46;
	uपूर्णांक32_t reserved_47;
	uपूर्णांक32_t reserved_48;
	uपूर्णांक32_t reserved_49;
	uपूर्णांक32_t reserved_50;
	uपूर्णांक32_t reserved_51;
	uपूर्णांक32_t reserved_52;
	uपूर्णांक32_t reserved_53;
	uपूर्णांक32_t reserved_54;
	uपूर्णांक32_t reserved_55;
	uपूर्णांक32_t reserved_56;
	uपूर्णांक32_t reserved_57;
	uपूर्णांक32_t reserved_58;
	uपूर्णांक32_t reserved_59;
	uपूर्णांक32_t reserved_60;
	uपूर्णांक32_t reserved_61;
	uपूर्णांक32_t reserved_62;
	uपूर्णांक32_t reserved_63;
	uपूर्णांक32_t reserved_64;
	uपूर्णांक32_t reserved_65;
	uपूर्णांक32_t reserved_66;
	uपूर्णांक32_t reserved_67;
	uपूर्णांक32_t reserved_68;
	uपूर्णांक32_t reserved_69;
	uपूर्णांक32_t reserved_70;
	uपूर्णांक32_t reserved_71;
	uपूर्णांक32_t reserved_72;
	uपूर्णांक32_t reserved_73;
	uपूर्णांक32_t reserved_74;
	uपूर्णांक32_t reserved_75;
	uपूर्णांक32_t reserved_76;
	uपूर्णांक32_t reserved_77;
	uपूर्णांक32_t reserved_78;
	uपूर्णांक32_t reserved_79;
	uपूर्णांक32_t reserved_80;
	uपूर्णांक32_t reserved_81;
	uपूर्णांक32_t reserved_82;
	uपूर्णांक32_t reserved_83;
	uपूर्णांक32_t reserved_84;
	uपूर्णांक32_t reserved_85;
	uपूर्णांक32_t reserved_86;
	uपूर्णांक32_t reserved_87;
	uपूर्णांक32_t reserved_88;
	uपूर्णांक32_t reserved_89;
	uपूर्णांक32_t reserved_90;
	uपूर्णांक32_t reserved_91;
	uपूर्णांक32_t reserved_92;
	uपूर्णांक32_t reserved_93;
	uपूर्णांक32_t reserved_94;
	uपूर्णांक32_t reserved_95;
	uपूर्णांक32_t reserved_96;
	uपूर्णांक32_t reserved_97;
	uपूर्णांक32_t reserved_98;
	uपूर्णांक32_t reserved_99;
	uपूर्णांक32_t reserved_100;
	uपूर्णांक32_t reserved_101;
	uपूर्णांक32_t reserved_102;
	uपूर्णांक32_t reserved_103;
	uपूर्णांक32_t reserved_104;
	uपूर्णांक32_t reserved_105;
	uपूर्णांक32_t reserved_106;
	uपूर्णांक32_t reserved_107;
	uपूर्णांक32_t reserved_108;
	uपूर्णांक32_t reserved_109;
	uपूर्णांक32_t reserved_110;
	uपूर्णांक32_t reserved_111;
	uपूर्णांक32_t reserved_112;
	uपूर्णांक32_t reserved_113;
	uपूर्णांक32_t reserved_114;
	uपूर्णांक32_t reserved_115;
	uपूर्णांक32_t reserved_116;
	uपूर्णांक32_t reserved_117;
	uपूर्णांक32_t reserved_118;
	uपूर्णांक32_t reserved_119;
	uपूर्णांक32_t reserved_120;
	uपूर्णांक32_t reserved_121;
	uपूर्णांक32_t reserved_122;
	uपूर्णांक32_t reserved_123;
	uपूर्णांक32_t reserved_124;
	uपूर्णांक32_t reserved_125;
	/* reserved_126,127: repurposed क्रम driver-पूर्णांकernal use */
	uपूर्णांक32_t sdma_engine_id;
	uपूर्णांक32_t sdma_queue_id;
पूर्ण;



#पूर्ण_अगर /* CIK_STRUCTS_H_ */
