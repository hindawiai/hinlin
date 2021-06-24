<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#घोषणा NFS4_MAXTAGLEN		20

#घोषणा NFS4_enc_cb_null_sz		0
#घोषणा NFS4_dec_cb_null_sz		0
#घोषणा cb_compound_enc_hdr_sz		4
#घोषणा cb_compound_dec_hdr_sz		(3 + (NFS4_MAXTAGLEN >> 2))
#घोषणा sessionid_sz			(NFS4_MAX_SESSIONID_LEN >> 2)
#घोषणा cb_sequence_enc_sz		(sessionid_sz + 4 +             \
					1 /* no referring calls list yet */)
#घोषणा cb_sequence_dec_sz		(op_dec_sz + sessionid_sz + 4)

#घोषणा op_enc_sz			1
#घोषणा op_dec_sz			2
#घोषणा enc_nfs4_fh_sz			(1 + (NFS4_FHSIZE >> 2))
#घोषणा enc_stateid_sz			(NFS4_STATEID_SIZE >> 2)
#घोषणा NFS4_enc_cb_recall_sz		(cb_compound_enc_hdr_sz +       \
					cb_sequence_enc_sz +            \
					1 + enc_stateid_sz +            \
					enc_nfs4_fh_sz)

#घोषणा NFS4_dec_cb_recall_sz		(cb_compound_dec_hdr_sz  +      \
					cb_sequence_dec_sz +            \
					op_dec_sz)
#घोषणा NFS4_enc_cb_layout_sz		(cb_compound_enc_hdr_sz +       \
					cb_sequence_enc_sz +            \
					1 + 3 +                         \
					enc_nfs4_fh_sz + 4)
#घोषणा NFS4_dec_cb_layout_sz		(cb_compound_dec_hdr_sz  +      \
					cb_sequence_dec_sz +            \
					op_dec_sz)

#घोषणा NFS4_enc_cb_notअगरy_lock_sz	(cb_compound_enc_hdr_sz +        \
					cb_sequence_enc_sz +             \
					2 + 1 +				 \
					XDR_QUADLEN(NFS4_OPAQUE_LIMIT) + \
					enc_nfs4_fh_sz)
#घोषणा NFS4_dec_cb_notअगरy_lock_sz	(cb_compound_dec_hdr_sz  +      \
					cb_sequence_dec_sz +            \
					op_dec_sz)
#घोषणा enc_cb_offload_info_sz		(1 + 1 + 2 + 1 +		\
					XDR_QUADLEN(NFS4_VERIFIER_SIZE))
#घोषणा NFS4_enc_cb_offload_sz		(cb_compound_enc_hdr_sz +       \
					cb_sequence_enc_sz +            \
					enc_nfs4_fh_sz +		\
					enc_stateid_sz +		\
					enc_cb_offload_info_sz)
#घोषणा NFS4_dec_cb_offload_sz		(cb_compound_dec_hdr_sz  +      \
					cb_sequence_dec_sz +            \
					op_dec_sz)
