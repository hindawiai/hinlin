<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _BATYPE_H_
#घोषणा _BATYPE_H_

#घोषणा	BA_SETUP_TIMEOUT	       200

#घोषणा	BA_POLICY_DELAYED		 0
#घोषणा	BA_POLICY_IMMEDIATE	         1

#घोषणा	ADDBA_STATUS_SUCCESS		 0
#घोषणा	ADDBA_STATUS_REFUSED		37
#घोषणा	ADDBA_STATUS_INVALID_PARAM	38

#घोषणा	DELBA_REASON_END_BA		37
#घोषणा	DELBA_REASON_UNKNOWN_BA	        38
#घोषणा	DELBA_REASON_TIMEOUT		39

जोड़ sequence_control अणु
	u16 लघु_data;
	काष्ठा अणु
		u16	frag_num:4;
		u16	seq_num:12;
	पूर्ण field;
पूर्ण;

जोड़ ba_param_set अणु
	u16 लघु_data;
	काष्ठा अणु
		u16	amsdu_support:1;
		u16	ba_policy:1;
		u16	tid:4;
		u16	buffer_size:10;
	पूर्ण field;
पूर्ण;

जोड़ delba_param_set अणु
	u16 लघु_data;
	काष्ठा अणु
		u16	reserved:11;
		u16	initiator:1;
		u16	tid:4;
	पूर्ण field;
पूर्ण;

काष्ठा ba_record अणु
	काष्ठा समयr_list	समयr;
	u8			valid;
	u8			dialog_token;
	जोड़ ba_param_set	param_set;
	u16			समयout_value;
	जोड़ sequence_control	start_seq_ctrl;
पूर्ण;

#पूर्ण_अगर //end _BATYPE_H_
