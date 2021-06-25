<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#समावेश "iscsi_target_core.h" /* काष्ठा iscsi_cmd */

काष्ठा sockaddr_storage;

काष्ठा iscsit_transport अणु
#घोषणा ISCSIT_TRANSPORT_NAME	16
	अक्षर name[ISCSIT_TRANSPORT_NAME];
	पूर्णांक transport_type;
	bool rdma_shutकरोwn;
	पूर्णांक priv_size;
	काष्ठा module *owner;
	काष्ठा list_head t_node;
	पूर्णांक (*iscsit_setup_np)(काष्ठा iscsi_np *, काष्ठा sockaddr_storage *);
	पूर्णांक (*iscsit_accept_np)(काष्ठा iscsi_np *, काष्ठा iscsi_conn *);
	व्योम (*iscsit_मुक्त_np)(काष्ठा iscsi_np *);
	व्योम (*iscsit_रुको_conn)(काष्ठा iscsi_conn *);
	व्योम (*iscsit_मुक्त_conn)(काष्ठा iscsi_conn *);
	पूर्णांक (*iscsit_get_login_rx)(काष्ठा iscsi_conn *, काष्ठा iscsi_login *);
	पूर्णांक (*iscsit_put_login_tx)(काष्ठा iscsi_conn *, काष्ठा iscsi_login *, u32);
	पूर्णांक (*iscsit_immediate_queue)(काष्ठा iscsi_conn *, काष्ठा iscsi_cmd *, पूर्णांक);
	पूर्णांक (*iscsit_response_queue)(काष्ठा iscsi_conn *, काष्ठा iscsi_cmd *, पूर्णांक);
	पूर्णांक (*iscsit_get_dataout)(काष्ठा iscsi_conn *, काष्ठा iscsi_cmd *, bool);
	पूर्णांक (*iscsit_queue_data_in)(काष्ठा iscsi_conn *, काष्ठा iscsi_cmd *);
	पूर्णांक (*iscsit_queue_status)(काष्ठा iscsi_conn *, काष्ठा iscsi_cmd *);
	व्योम (*iscsit_पातed_task)(काष्ठा iscsi_conn *, काष्ठा iscsi_cmd *);
	पूर्णांक (*iscsit_xmit_pdu)(काष्ठा iscsi_conn *, काष्ठा iscsi_cmd *,
			       काष्ठा iscsi_datain_req *, स्थिर व्योम *, u32);
	व्योम (*iscsit_unmap_cmd)(काष्ठा iscsi_conn *, काष्ठा iscsi_cmd *);
	व्योम (*iscsit_get_rx_pdu)(काष्ठा iscsi_conn *);
	पूर्णांक (*iscsit_validate_params)(काष्ठा iscsi_conn *);
	व्योम (*iscsit_get_r2t_ttt)(काष्ठा iscsi_conn *, काष्ठा iscsi_cmd *,
				   काष्ठा iscsi_r2t *);
	क्रमागत target_prot_op (*iscsit_get_sup_prot_ops)(काष्ठा iscsi_conn *);
पूर्ण;

अटल अंतरभूत व्योम *iscsit_priv_cmd(काष्ठा iscsi_cmd *cmd)
अणु
	वापस (व्योम *)(cmd + 1);
पूर्ण

/*
 * From iscsi_target_transport.c
 */

बाह्य व्योम iscsit_रेजिस्टर_transport(काष्ठा iscsit_transport *);
बाह्य व्योम iscsit_unरेजिस्टर_transport(काष्ठा iscsit_transport *);
बाह्य काष्ठा iscsit_transport *iscsit_get_transport(पूर्णांक);
बाह्य व्योम iscsit_put_transport(काष्ठा iscsit_transport *);

/*
 * From iscsi_target.c
 */
बाह्य पूर्णांक iscsit_setup_scsi_cmd(काष्ठा iscsi_conn *, काष्ठा iscsi_cmd *,
				अचिन्हित अक्षर *);
बाह्य व्योम iscsit_set_unsolicited_dataout(काष्ठा iscsi_cmd *);
बाह्य पूर्णांक iscsit_process_scsi_cmd(काष्ठा iscsi_conn *, काष्ठा iscsi_cmd *,
				काष्ठा iscsi_scsi_req *);
बाह्य पूर्णांक
__iscsit_check_dataout_hdr(काष्ठा iscsi_conn *, व्योम *,
			   काष्ठा iscsi_cmd *, u32, bool *);
बाह्य पूर्णांक
iscsit_check_dataout_hdr(काष्ठा iscsi_conn *conn, व्योम *buf,
			 काष्ठा iscsi_cmd **out_cmd);
बाह्य पूर्णांक iscsit_check_dataout_payload(काष्ठा iscsi_cmd *, काष्ठा iscsi_data *,
				bool);
बाह्य पूर्णांक iscsit_setup_nop_out(काष्ठा iscsi_conn *, काष्ठा iscsi_cmd *,
				काष्ठा iscsi_nopout *);
बाह्य पूर्णांक iscsit_process_nop_out(काष्ठा iscsi_conn *, काष्ठा iscsi_cmd *,
				काष्ठा iscsi_nopout *);
बाह्य पूर्णांक iscsit_handle_logout_cmd(काष्ठा iscsi_conn *, काष्ठा iscsi_cmd *,
				अचिन्हित अक्षर *);
बाह्य पूर्णांक iscsit_handle_task_mgt_cmd(काष्ठा iscsi_conn *, काष्ठा iscsi_cmd *,
				अचिन्हित अक्षर *);
बाह्य पूर्णांक iscsit_setup_text_cmd(काष्ठा iscsi_conn *, काष्ठा iscsi_cmd *,
				 काष्ठा iscsi_text *);
बाह्य पूर्णांक iscsit_process_text_cmd(काष्ठा iscsi_conn *, काष्ठा iscsi_cmd *,
				   काष्ठा iscsi_text *);
बाह्य व्योम iscsit_build_rsp_pdu(काष्ठा iscsi_cmd *, काष्ठा iscsi_conn *,
				bool, काष्ठा iscsi_scsi_rsp *);
बाह्य व्योम iscsit_build_nopin_rsp(काष्ठा iscsi_cmd *, काष्ठा iscsi_conn *,
				काष्ठा iscsi_nopin *, bool);
बाह्य व्योम iscsit_build_task_mgt_rsp(काष्ठा iscsi_cmd *, काष्ठा iscsi_conn *,
				काष्ठा iscsi_पंचांग_rsp *);
बाह्य पूर्णांक iscsit_build_text_rsp(काष्ठा iscsi_cmd *, काष्ठा iscsi_conn *,
				काष्ठा iscsi_text_rsp *,
				क्रमागत iscsit_transport_type);
बाह्य व्योम iscsit_build_reject(काष्ठा iscsi_cmd *, काष्ठा iscsi_conn *,
				काष्ठा iscsi_reject *);
बाह्य पूर्णांक iscsit_build_logout_rsp(काष्ठा iscsi_cmd *, काष्ठा iscsi_conn *,
				काष्ठा iscsi_logout_rsp *);
बाह्य पूर्णांक iscsit_logout_post_handler(काष्ठा iscsi_cmd *, काष्ठा iscsi_conn *);
बाह्य पूर्णांक iscsit_queue_rsp(काष्ठा iscsi_conn *, काष्ठा iscsi_cmd *);
बाह्य व्योम iscsit_पातed_task(काष्ठा iscsi_conn *, काष्ठा iscsi_cmd *);
बाह्य पूर्णांक iscsit_add_reject(काष्ठा iscsi_conn *, u8, अचिन्हित अक्षर *);
बाह्य पूर्णांक iscsit_reject_cmd(काष्ठा iscsi_cmd *, u8, अचिन्हित अक्षर *);
बाह्य पूर्णांक iscsit_handle_snack(काष्ठा iscsi_conn *, अचिन्हित अक्षर *);
बाह्य व्योम iscsit_build_datain_pdu(काष्ठा iscsi_cmd *, काष्ठा iscsi_conn *,
				    काष्ठा iscsi_datain *,
				    काष्ठा iscsi_data_rsp *, bool);
बाह्य पूर्णांक iscsit_build_r2ts_क्रम_cmd(काष्ठा iscsi_conn *, काष्ठा iscsi_cmd *,
				     bool);
बाह्य पूर्णांक iscsit_immediate_queue(काष्ठा iscsi_conn *, काष्ठा iscsi_cmd *, पूर्णांक);
बाह्य पूर्णांक iscsit_response_queue(काष्ठा iscsi_conn *, काष्ठा iscsi_cmd *, पूर्णांक);
/*
 * From iscsi_target_device.c
 */
बाह्य व्योम iscsit_increment_maxcmdsn(काष्ठा iscsi_cmd *, काष्ठा iscsi_session *);
/*
 * From iscsi_target_erl0.c
 */
बाह्य व्योम iscsit_cause_connection_reinstatement(काष्ठा iscsi_conn *, पूर्णांक);
/*
 * From iscsi_target_erl1.c
 */
बाह्य व्योम iscsit_stop_dataout_समयr(काष्ठा iscsi_cmd *);

/*
 * From iscsi_target_पंचांगr.c
 */
बाह्य पूर्णांक iscsit_पंचांगr_post_handler(काष्ठा iscsi_cmd *, काष्ठा iscsi_conn *);

/*
 * From iscsi_target_util.c
 */
बाह्य काष्ठा iscsi_cmd *iscsit_allocate_cmd(काष्ठा iscsi_conn *, पूर्णांक);
बाह्य पूर्णांक iscsit_sequence_cmd(काष्ठा iscsi_conn *, काष्ठा iscsi_cmd *,
			       अचिन्हित अक्षर *, __be32);
बाह्य व्योम iscsit_release_cmd(काष्ठा iscsi_cmd *);
बाह्य व्योम iscsit_मुक्त_cmd(काष्ठा iscsi_cmd *, bool);
बाह्य व्योम iscsit_add_cmd_to_immediate_queue(काष्ठा iscsi_cmd *,
					      काष्ठा iscsi_conn *, u8);
बाह्य काष्ठा iscsi_cmd *
iscsit_find_cmd_from_itt_or_dump(काष्ठा iscsi_conn *conn,
				 itt_t init_task_tag, u32 length);

/*
 * From iscsi_target_nego.c
 */
बाह्य पूर्णांक iscsi_target_check_login_request(काष्ठा iscsi_conn *,
					    काष्ठा iscsi_login *);

/*
 * From iscsi_target_login.c
 */
बाह्य __म_लिखो(2, 3) पूर्णांक iscsi_change_param_प्र_लिखो(
	काष्ठा iscsi_conn *, स्थिर अक्षर *, ...);

/*
 * From iscsi_target_parameters.c
 */
बाह्य काष्ठा iscsi_param *iscsi_find_param_from_key(
	अक्षर *, काष्ठा iscsi_param_list *);
